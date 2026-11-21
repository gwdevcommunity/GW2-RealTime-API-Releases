# Disclaimer
> [!CAUTION]
> ## Modifying Guild Wars 2 through any third party software is not supported by ArenaNet nor by any of its partners.
> ## You are using this addon at your own risk.

> [!IMPORTANT]
> This addon was built with appropriate limitations to ensure that it is within the official [Third Party Program Policy](https://help.guildwars2.com/hc/en-us/articles/360013625034-Policy-Third-Party-Programs).
> If you believe this addon is violating the third party policy, please [create an issue](../../issues) here on this repository voicing your concerns.
> 
> Portions or the entirety of the codebase remain closed-source in compliance with requests by ArenaNet.

## To ArenaNet
### Please reach out to us by [creating an issue](../../issues) for concerns, takedown requests or review requests for the codebase.

---

![](https://img.shields.io/github/license/RaidcoreGG/GW2-RealTime-API-Releases?style=for-the-badge&labelColor=%23131519&color=%230F79AA)
![](https://img.shields.io/github/v/release/RaidcoreGG/GW2-RealTime-API-Releases?style=for-the-badge&labelColor=%23131519&color=%230F79AA)
![](https://img.shields.io/github/downloads/RaidcoreGG/GW2-RealTime-API-Releases/total?style=for-the-badge&labelColor=%23131519&color=%230F79AA)

# GW2 RealTime API - RTAPI
RTAPI provides real-time information about Guild Wars 2.
Additionally, running RTAPI fixes the long standing "bug", that the Mumble API delivers "laggy" player positions.

## Features
- Client Info
- Instance Info
- Group Info
- Character Info
- Camera Info
- Build, Equipment and Attributes
- Target Info
- Group Vitals
- Guilds
- Combat Events

Anything missing? Please open an issue and it may be added in a future update.

## Using RTAPI
The primary object `struct RealTimeData` can be obtained using Nexus' DataLink API. The name of the data link is defined in the header `DL_RTAPI`.

As Nexus allows for hot-loading and as such RTAPI can be unloaded at runtime, for example to be updated, the addon has to check that the data has not gone stale.
You can do this by checking if `RTAPI->GameBuild == 0`.
If the Game Build is set to 0, RTAPI was unloaded.

It is recommended to also listen to `EV_ADDON_LOADED` and `EV_ADDON_UNLOADED` events, and checking against the signature of RTAPI to automatically switch back to using the realtime data.
The signature of the addon is also defined in the API header `RTAPI_SIG`.

### Timing
RTAPI delivers data on two different clocks:

| Data | Timing | Meaning |
| --- | --- | --- |
| `RealTimeData` (DataLink) | **Frame-synchronized** | Updated when a frame is presented. Character position and facing, camera position, facing and FOV, cursor and squad marker positions always match the frame currently on screen. Use this for anything rendered in the world. |
| `RealTimeGroupData` (DataLink `DL_RTAPI_GROUP`) | **Frame-synchronized** | Health of group members, updated together with `RealTimeData`. |
| Events (`EV_RTAPI_*`) | **Real-time (engine tick)** | Raised on the game's engine tick, as soon as the game processes them. The game renders a few frames behind its simulation, so an event can arrive before the frame showing it. Each event carries its own timestamp where relevant. |

Do not use an event's arrival to decide what is on screen. Use the DataLink for that.

### Versioning
`RealTimeData::Size` holds `sizeof(RealTimeData)` as RTAPI wrote it, and is `0` for RTAPI versions from before it existed.
Fields are only ever appended. Before reading a field newer than the RTAPI version you require, check that `Size` covers it:
```cpp
bool HasTarget = G::RTAPI->Size >= offsetof(RTAPI::RealTimeData, TargetBreakbar) + sizeof(uint32_t);
```
The fields appended to `GroupMember` (`IsAlive`, `IsDowned`, `IsInstanceOwner`, `Nickname`) are filled whenever `Size` is not `0`.

### Example implementation (Addon load events)
```cpp
void OnAddonLoaded(int* aSignature)
{
  if (!aSignature) { return; }
  
  if (*aSignature == RTAPI_SIG)
  {
    G::RTAPI = (RTAPI::RealTimeData*)G::APIDefs->DataLink.Get(DL_RTAPI);
  }
}
void OnAddonUnloaded(int* aSignature)
{
  if (!aSignature) { return; }

  if (*aSignature == RTAPI_SIG)
  {
    G::RTAPI = nullptr;
  }
}
```

### Group Data
Real-time group data is individually sent to any addon that loaded after RTAPI.

The following events are provided. The payload is `GroupMember*`.
```cpp
#define EV_RTAPI_GROUP_MEMBER_JOINED  "RTAPI_GROUP_MEMBER_JOINED"
#define EV_RTAPI_GROUP_MEMBER_LEFT    "RTAPI_GROUP_MEMBER_LEFT"
#define EV_RTAPI_GROUP_MEMBER_UPDATED "RTAPI_GROUP_MEMBER_UPDATED"
```

Each `GroupMember` also carries `IsAlive` and `IsDowned` (only valid if `IsInInstance`), `IsInstanceOwner`, and `Nickname`, the player's own contact nickname for that account.
A change to any of them raises `EV_RTAPI_GROUP_MEMBER_UPDATED`.

Health is read every frame, so it is not an event but its own DataLink, `DL_RTAPI_GROUP` with a `RealTimeGroupData` struct.
Entries are matched to `GroupMember` by account name. Health is a percentage from `0` to `100` as a `float`, `0` for members outside the player's instance.
Look members up by name every frame, never keep an index: the DataLink follows the presented frame, while the member events are raised in real time, so a member who just joined can be missing for a few frames, and one who just left can still be listed.

Both DataLinks are written together on the game's render thread, right before the frame is presented. Read them from `RT_Render` (or another render callback) to always see one complete frame. Reading from another thread, e.g. an event callback, can see a write in progress.

#### Reading from other threads
Reading in a render callback is the rule. If you must read from another thread, both structs end with a `Frame` counter (check `Size` first, it is `0` before RTAPI versions that have it).
`Frame` is odd while RTAPI writes a frame and even once it is complete, and both DataLinks share the same value. Copy the struct and keep the copy only if `Frame` was the same even number before and after:
```cpp
RTAPI::RealTimeData copy;
for (;;)
{
  uint32_t before = std::atomic_ref<uint32_t>(G::RTAPI->Frame).load(std::memory_order_acquire);
  if (before & 1) { continue; }              // RTAPI is writing.
  memcpy(&copy, G::RTAPI, sizeof(copy));
  std::atomic_thread_fence(std::memory_order_acquire);
  if (std::atomic_ref<uint32_t>(G::RTAPI->Frame).load(std::memory_order_relaxed) == before) { break; }
}
```
Like `RealTimeData`, its `Size` is set to `0` when RTAPI is unloaded.

### Build, Equipment and Attributes
The player's build and equipment are raised on change, and individually sent to any addon that loaded after RTAPI. Payloads are only valid for the duration of the callback.
```cpp
#define EV_RTAPI_BUILD_CHANGED "RTAPI_BUILD_CHANGED" // BuildData*: template index, profession, specializations and their major traits.
#define EV_RTAPI_GEAR_CHANGED  "RTAPI_GEAR_CHANGED"  // GearData*: template index, and per EGearSlot the item, stat, upgrade and infusion IDs.
```
IDs match the official API (`/v2/specializations`, `/v2/traits`, `/v2/items`, `/v2/itemstats`). Equipment is always the PvE equipment, also in PvP.

`RealTimeData` carries the current `BuildTemplateIndex` and `GearTemplateIndex`, plus `BaseAttributes` (level and equipment) and `EffectiveAttributes` (as the hero panel shows them, including boons such as Might).

### Target
`RealTimeData` describes the selected target as the target frame shows it: `TargetID` (the same agent ID as the combat events), type, species, attitude, and health, barrier and breakbar as percentages from `0` to `100`. `TargetID` is `0` without a target.

All percentages are `float`s, currently rounded to whole numbers as the game shows them. Should more precision become allowed, the values get finer without the layout changing.

### Guilds
`RealTimeData` carries the represented guild (`RepresentedGuildID`, `RepresentedGuildName`). The ID is the GUID as the official API writes it.
The account's guilds are raised as `EV_RTAPI_GUILDS_CHANGED` with a `GuildList*` payload, on change and to addons loaded later.
The payload has a variable length: `Guilds` holds `Count` entries and `Size` covers them all, so copy `Size` bytes if you keep it. `Count` is the number of guilds the account is in, and can be `0`.
Each entry has the guild's ID. Its name is only known for the represented guild, and tags are not known at all, so look them up with the official API (`/v2/guild/:id`).

### Combat Events
Combat events mirror the player's own combat log. They contain nothing the combat log does not show, and nothing at all in PvP except score events. Hostile players are anonymous, as in the game.

Every combat event type has its own event, so you only subscribe to what you need, e.g. `EV_RTAPI_COMBAT_HEALTH` with a `CombatHealthEvent*` payload. Every payload starts with `CombatEvent`, which holds the type, a Unix timestamp in milliseconds, and the IDs of the source, destination and skill. See the API header for the full list.

Agents and skills are referenced by ID. Their details are sent once:
- `EV_RTAPI_COMBAT_AGENT_ADDED` / `EV_RTAPI_COMBAT_SKILL_ADDED` are raised before the first event referencing them.
- `EV_RTAPI_COMBAT_AGENT_UPDATED` / `EV_RTAPI_COMBAT_SKILL_UPDATED` follow when something changes, e.g. a name was decoded or an attitude changed.
- `EV_RTAPI_COMBAT_AGENT_REMOVED` is raised when an agent ID becomes invalid: the agent despawned, or the map changed. Agent IDs are only unique within a map instance.

Keep your own copy of what you need: **every payload is only valid for the duration of the event callback.**

Every payload starts with a `Size` field. Fields are only ever appended, so check `Size` before reading a field that was added after the RTAPI version you require.
