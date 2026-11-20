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
| Events (`EV_RTAPI_*`) | **Real-time (engine tick)** | Raised on the game's engine tick, as soon as the game processes them. The game renders a few frames behind its simulation, so an event can arrive before the frame showing it. Each event carries its own timestamp where relevant. |

Do not use an event's arrival to decide what is on screen. Use the DataLink for that.

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

### Combat Events
Combat events mirror the player's own combat log. They contain nothing the combat log does not show, and nothing at all in PvP except score events. Hostile players are anonymous, as in the game.

Every combat event type has its own event, so you only subscribe to what you need, e.g. `EV_RTAPI_COMBAT_HEALTH` with a `CombatHealthEvent*` payload. Every payload starts with `CombatEvent`, which holds the type, a Unix timestamp in milliseconds, and the IDs of the source, destination and skill. See the API header for the full list.

Agents and skills are referenced by ID. Their details are sent once:
- `EV_RTAPI_COMBAT_AGENT_ADDED` / `EV_RTAPI_COMBAT_SKILL_ADDED` are raised before the first event referencing them.
- `EV_RTAPI_COMBAT_AGENT_UPDATED` / `EV_RTAPI_COMBAT_SKILL_UPDATED` follow when something changes, e.g. a name was decoded or an attitude changed.
- `EV_RTAPI_COMBAT_AGENT_REMOVED` is raised when an agent ID becomes invalid, e.g. on map change. Agent IDs are only unique within a map instance.

Keep your own copy of what you need: **every payload is only valid for the duration of the event callback.**

Every payload starts with a `Size` field. Fields are only ever appended, so check `Size` before reading a field that was added after the RTAPI version you require.
