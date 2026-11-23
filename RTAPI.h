///----------------------------------------------------------------------------------------------------
/// Copyright (c) Raidcore.GG - Licensed under the MIT license.
///
/// Name         :  RTAPI.h
/// Description  :  Definitions for public-facing real-time API.
/// Authors      :  K. Bieniek
///----------------------------------------------------------------------------------------------------

#ifndef RTAPI_H
#define RTAPI_H

#define RTAPI_SIG                     0x2501A02C
#define DL_RTAPI                      "RTAPI"                      // DataLink is RealTimeData struct
#define EV_RTAPI_GROUP_MEMBER_JOINED  "RTAPI_GROUP_MEMBER_JOINED"  // Payload is GroupMember*
#define EV_RTAPI_GROUP_MEMBER_LEFT    "RTAPI_GROUP_MEMBER_LEFT"    // Payload is GroupMember*
#define EV_RTAPI_GROUP_MEMBER_UPDATED "RTAPI_GROUP_MEMBER_UPDATED" // Payload is GroupMember*
#define RTAPI_BOON_SLOTS              16                           // Length of the Boons arrays, indexed by EBoon. Room for boons the game may add.
#define DL_RTAPI_GROUP                "RTAPI_GROUP"                // DataLink is RealTimeGroupData struct. Frame-synchronized like DL_RTAPI.

#define EV_RTAPI_BUILD_CHANGED        "RTAPI_BUILD_CHANGED"        // Payload is BuildData*. Raised on change, and to addons loaded later.
#define EV_RTAPI_GEAR_CHANGED         "RTAPI_GEAR_CHANGED"         // Payload is GearData*. Raised on change, and to addons loaded later.
#define EV_RTAPI_GUILDS_CHANGED       "RTAPI_GUILDS_CHANGED"       // Payload is GuildList*. Raised on change, and to addons loaded later.

#define EV_RTAPI_COMBAT_AGENT_ADDED            "RTAPI_COMBAT_AGENT_ADDED"            // Payload is CombatAgent*. Agent seen for the first time. Raised before any event that references it.
#define EV_RTAPI_COMBAT_AGENT_UPDATED          "RTAPI_COMBAT_AGENT_UPDATED"          // Payload is CombatAgent*. Agent data changed, e.g. its name was decoded.
#define EV_RTAPI_COMBAT_AGENT_REMOVED          "RTAPI_COMBAT_AGENT_REMOVED"          // Payload is CombatAgent*. Agent left the combat log, or the map changed. Its ID may be reused after.
#define EV_RTAPI_COMBAT_SKILL_ADDED            "RTAPI_COMBAT_SKILL_ADDED"            // Payload is CombatSkill*. Skill seen for the first time. Raised before any event that references it.
#define EV_RTAPI_COMBAT_SKILL_UPDATED          "RTAPI_COMBAT_SKILL_UPDATED"          // Payload is CombatSkill*. Skill data changed, e.g. its name was decoded.
#define EV_RTAPI_COMBAT_BLOCK                  "RTAPI_COMBAT_BLOCK"                  // Payload is CombatEvent*.
#define EV_RTAPI_COMBAT_BREAKBAR               "RTAPI_COMBAT_BREAKBAR"               // Payload is CombatBreakbarEvent*.
#define EV_RTAPI_COMBAT_COMBO                  "RTAPI_COMBAT_COMBO"                  // Payload is CombatEvent*.
#define EV_RTAPI_COMBAT_DEATH                  "RTAPI_COMBAT_DEATH"                  // Payload is CombatEvent*.
#define EV_RTAPI_COMBAT_DOWN                   "RTAPI_COMBAT_DOWN"                   // Payload is CombatEvent*.
#define EV_RTAPI_COMBAT_ENERGY                 "RTAPI_COMBAT_ENERGY"                 // Payload is CombatEnergyEvent*.
#define EV_RTAPI_COMBAT_EVADE                  "RTAPI_COMBAT_EVADE"                  // Payload is CombatEvent*.
#define EV_RTAPI_COMBAT_EXPERIENCE             "RTAPI_COMBAT_EXPERIENCE"             // Payload is CombatExperienceEvent*.
#define EV_RTAPI_COMBAT_HEALTH                 "RTAPI_COMBAT_HEALTH"                 // Payload is CombatHealthEvent*.
#define EV_RTAPI_COMBAT_INTERRUPT              "RTAPI_COMBAT_INTERRUPT"              // Payload is CombatEvent*.
#define EV_RTAPI_COMBAT_INVULNERABILITY_ABSORB "RTAPI_COMBAT_INVULNERABILITY_ABSORB" // Payload is CombatEvent*.
#define EV_RTAPI_COMBAT_KARMA                  "RTAPI_COMBAT_KARMA"                  // Payload is CombatKarmaEvent*.
#define EV_RTAPI_COMBAT_LUCK                   "RTAPI_COMBAT_LUCK"                   // Payload is CombatLuckEvent*.
#define EV_RTAPI_COMBAT_MISSED_BY_SOURCE       "RTAPI_COMBAT_MISSED_BY_SOURCE"       // Payload is CombatEvent*.
#define EV_RTAPI_COMBAT_MISSED_TARGET          "RTAPI_COMBAT_MISSED_TARGET"          // Payload is CombatEvent*.
#define EV_RTAPI_COMBAT_PVP_SCORE              "RTAPI_COMBAT_PVP_SCORE"              // Payload is CombatScoreEvent*.
#define EV_RTAPI_COMBAT_RESIST                 "RTAPI_COMBAT_RESIST"                 // Payload is CombatResistEvent*.
#define EV_RTAPI_COMBAT_SKILL_ABSORBED         "RTAPI_COMBAT_SKILL_ABSORBED"         // Payload is CombatEvent*.
#define EV_RTAPI_COMBAT_SKILL_BEGIN            "RTAPI_COMBAT_SKILL_BEGIN"            // Payload is CombatEvent*.
#define EV_RTAPI_COMBAT_SKILL_END              "RTAPI_COMBAT_SKILL_END"              // Payload is CombatEvent*.
#define EV_RTAPI_COMBAT_SKILL_OBSTRUCTED       "RTAPI_COMBAT_SKILL_OBSTRUCTED"       // Payload is CombatEvent*.
#define EV_RTAPI_COMBAT_SKILL_OUT_OF_RANGE     "RTAPI_COMBAT_SKILL_OUT_OF_RANGE"     // Payload is CombatEvent*.
#define EV_RTAPI_COMBAT_WVW_SCORE              "RTAPI_COMBAT_WVW_SCORE"              // Payload is CombatScoreEvent*. Type is CET_WvWScoreRed, CET_WvWScoreBlue or CET_WvWScoreGreen.
#define EV_RTAPI_COMBAT_WVW_EXPERIENCE         "RTAPI_COMBAT_WVW_EXPERIENCE"         // Payload is CombatWvWExperienceEvent*.

#include <stdint.h>

///----------------------------------------------------------------------------------------------------
/// EGameState Enumeration
///----------------------------------------------------------------------------------------------------
enum EGameState
{
	GS_CharacterSelection,
	GS_CharacterCreation,
	GS_Cinematic,
	GS_LoadingScreen,
	GS_Gameplay
};

///----------------------------------------------------------------------------------------------------
/// EGameLanguage Enumeration
///----------------------------------------------------------------------------------------------------
enum EGameLanguage
{
	GL_English,
	GL_Korean,
	GL_French,
	GL_German,
	GL_Spanish,
	GL_Chinese
};

///----------------------------------------------------------------------------------------------------
/// ETimeOfDay Enumeration
///----------------------------------------------------------------------------------------------------
enum ETimeOfDay
{
	TOD_Dawn,
	TOD_Day,
	TOD_Dusk,
	TOD_Night
};

///----------------------------------------------------------------------------------------------------
/// ECharacterState Enumeration
///----------------------------------------------------------------------------------------------------
enum ECharacterState
{
	CS_IsAlive      = 1 << 0,
	CS_IsDowned     = 1 << 1,
	CS_IsInCombat   = 1 << 2,
	CS_IsSwimming   = 1 << 3, // aka. Is on water surface
	CS_IsUnderwater = 1 << 4, // aka. Is diving
	CS_IsGliding    = 1 << 5,
	CS_IsFlying     = 1 << 6
};

///----------------------------------------------------------------------------------------------------
/// EMapType Enumeration
///----------------------------------------------------------------------------------------------------
enum EMapType
{
	MT_AutoRedirect,
	MT_CharacterCreation,
	MT_PvP,
	MT_GvG,
	MT_Instance,
	MT_Public,
	MT_Tournament,
	MT_Tutorial,
	MT_UserTournament,
	MT_WvW_EternalBattlegrounds,
	MT_WvW_BlueBorderlands,
	MT_WvW_GreenBorderlands,
	MT_WvW_RedBorderlands,
	MT_WVW_FortunesVale,
	MT_WvW_ObsidianSanctum,
	MT_WvW_EdgeOfTheMists,
	MT_Public_Mini,
	MT_BigBattle,
	MT_WvW_Lounge
};

///----------------------------------------------------------------------------------------------------
/// EGroupType Enumeration
///----------------------------------------------------------------------------------------------------
enum EGroupType
{
	GT_None,
	GT_Party,
	GT_RaidSquad,
	GT_Squad
};

///----------------------------------------------------------------------------------------------------
/// GroupMember Struct
///----------------------------------------------------------------------------------------------------
typedef struct GroupMember
{
	char     AccountName[140];
	char     CharacterName[140];
	uint32_t Subgroup;            // 0 for parties, 1-15 according to the squad's subgroup
	uint32_t Profession;          // 1-9 = Profession; 0 Unknown -> e.g. on loading screen or logged out
	uint32_t EliteSpecialization; // Third Spec ID, not necessarily elite; or 0 Unknown -> e.g. on loading screen or logged out
	uint32_t IsSelf       : 1;
	uint32_t IsInInstance : 1;    // Is in the same map instance as the player.
	uint32_t IsCommander  : 1;
	uint32_t IsLieutenant : 1;

	/* Appended. Only filled if RealTimeData::Size is not 0. */
	uint32_t IsAlive         : 1; // Only valid if IsInInstance.
	uint32_t IsDowned        : 1; // Only valid if IsInInstance.
	uint32_t IsInstanceOwner : 1; // Owns the map instance the group is in.
	char     Nickname[140];       // UTF-8. The player's contact nickname for this account; empty if none.
} GroupMember;

///----------------------------------------------------------------------------------------------------
/// EVitalState Enumeration
///----------------------------------------------------------------------------------------------------
enum EVitalState
{
	VS_Unknown,  // Not in the player's instance.
	VS_Alive,
	VS_Downed,
	VS_Defeated
};

///----------------------------------------------------------------------------------------------------
/// EBoon Enumeration
/// 	Index into the Boons arrays. Only ever appended.
///----------------------------------------------------------------------------------------------------
enum EBoon
{
	BN_Aegis,
	BN_Alacrity,
	BN_Fury,
	BN_Might,
	BN_Protection,
	BN_Quickness,
	BN_Regeneration,
	BN_Resistance,
	BN_Resolution,
	BN_Stability,
	BN_Swiftness,
	BN_Vigor,
	BN_COUNT
};

///----------------------------------------------------------------------------------------------------
/// GroupMemberVitals Struct
///----------------------------------------------------------------------------------------------------
typedef struct GroupMemberVitals
{
	char     AccountName[140];         // Matches GroupMember::AccountName.
	float    Health;                   // Percent, 0-100. Currently whole numbers, as the game shows them. 0 if not in the player's instance.
	uint32_t State;                    // EVitalState
	uint32_t Profession;               // 1-9 = Profession; 0 Unknown, e.g. logged out.
	uint32_t EliteSpecialization;      // Third spec ID, not necessarily elite; 0 if unknown or not in the player's instance.
	uint32_t HasBoons : 1;             // Boons are visible: the player's own party, or own squad subgroup, as the game shows them. Otherwise Boons is all 0.
	uint8_t  Boons[RTAPI_BOON_SLOTS];  // Stacks per EBoon, 0 if inactive. Might and Stability count their stacks, the others are 1 while active.
} GroupMemberVitals;

///----------------------------------------------------------------------------------------------------
/// RealTimeGroupData Struct
/// 	DataLink DL_RTAPI_GROUP. Frame-synchronized.
///----------------------------------------------------------------------------------------------------
typedef struct RealTimeGroupData
{
	uint32_t          Size;        // sizeof(RealTimeGroupData) as written. 0 when RTAPI is unloaded.
	uint32_t          Count;       // Used entries in Members.
	GroupMemberVitals Members[50];
	uint32_t          Frame; // Frame counter. Odd while RTAPI writes a frame, even when it is complete. See README, reading from other threads.
} RealTimeGroupData;

///----------------------------------------------------------------------------------------------------
/// EAgentType Enumeration
///----------------------------------------------------------------------------------------------------
enum EAgentType
{
	AT_Character,
	AT_Gadget,
	AT_AttackTarget
};

///----------------------------------------------------------------------------------------------------
/// EAttitude Enumeration
///----------------------------------------------------------------------------------------------------
enum EAttitude
{
	ATT_Friendly,
	ATT_Hostile,
	ATT_Indifferent,
	ATT_Neutral
};

///----------------------------------------------------------------------------------------------------
/// CombatAgent Struct
/// 	Payload of the EV_RTAPI_COMBAT_AGENT_* events.
///----------------------------------------------------------------------------------------------------
typedef struct CombatAgent
{
	uint32_t Size;             // sizeof(CombatAgent) as raised. Fields are only ever appended.
	uint32_t ID;               // Agent ID, unique within the current map instance.
	uint32_t Type;             // EAgentType
	uint32_t SpeciesID;        // Character: Species ID; Gadget/AttackTarget: Gadget ID.
	uint32_t OwnerID;          // Agent ID of the top-most owner, if IsMinion; otherwise 0.
	uint32_t Attitude;         // EAttitude. Characters only. Towards the player. Checked on every event, a change raises AGENT_UPDATED.
	uint32_t Profession;       // 1-9 = Profession, if IsPlayer; otherwise 0.
	char     Name[140];        // UTF-8. Empty until decoded (see EV_RTAPI_COMBAT_AGENT_UPDATED), and for hostile players.
	char     AccountName[140]; // UTF-8. Only for players known to the player, e.g. party, squad, contacts. Never for hostile players.
	uint32_t IsSelf   : 1;     // Is the player's own character.
	uint32_t IsPlayer : 1;
	uint32_t IsMinion : 1;     // Is owned by another agent, e.g. a pet, clone or summon.
} CombatAgent;

///----------------------------------------------------------------------------------------------------
/// CombatSkill Struct
/// 	Payload of the EV_RTAPI_COMBAT_SKILL_* events.
///----------------------------------------------------------------------------------------------------
typedef struct CombatSkill
{
	uint32_t Size;      // sizeof(CombatSkill) as raised. Fields are only ever appended.
	uint32_t ID;
	char     Name[140]; // UTF-8. Empty until decoded, see EV_RTAPI_COMBAT_SKILL_UPDATED.
} CombatSkill;

///----------------------------------------------------------------------------------------------------
/// ECombatEventType Enumeration
///----------------------------------------------------------------------------------------------------
enum ECombatEventType
{
	CET_Block,
	CET_Breakbar,
	CET_Combo,
	CET_Death,
	CET_Down,
	CET_Energy,
	CET_Evade,
	CET_Experience,
	CET_Health,
	CET_Interrupt,
	CET_InvulnerabilityAbsorb,
	CET_Karma,
	CET_Luck,
	CET_MissedBySource,
	CET_MissedTarget,
	CET_PvPScore,
	CET_Resist,
	CET_SkillAbsorbed,
	CET_SkillBegin,
	CET_SkillEnd,
	CET_SkillObstructed,
	CET_SkillOutOfRange,
	CET_WvWScoreRed,
	CET_WvWScoreBlue,
	CET_WvWScoreGreen,
	CET_WvWExperience
};

///----------------------------------------------------------------------------------------------------
/// CombatEvent Struct
/// 	Common to all combat events, and the payload of events without values.
/// 	Only contains events from the player's own combat log.
/// 	Every payload is only valid for the duration of the event callback.
///----------------------------------------------------------------------------------------------------
typedef struct CombatEvent
{
	uint32_t Size;                  // sizeof the full payload, e.g. sizeof(CombatHealthEvent). Fields are only ever appended.
	uint32_t Type;                  // ECombatEventType
	uint64_t Time;                  // Unix timestamp in milliseconds.
	uint32_t SourceID;              // Agent ID, see EV_RTAPI_COMBAT_AGENT_*. 0 if there is none.
	uint32_t DestinationID;         // Agent ID, see EV_RTAPI_COMBAT_AGENT_*. 0 if there is none.
	uint32_t SkillID;               // Skill ID, see EV_RTAPI_COMBAT_SKILL_*. 0 if there is none.
	uint32_t IsBonus           : 1;
	uint32_t IsCritical        : 1;
	uint32_t IsFumble          : 1;
	uint32_t IsConditionDamage : 1;
} CombatEvent;

///----------------------------------------------------------------------------------------------------
/// CombatBreakbarEvent Struct
/// 	Payload of EV_RTAPI_COMBAT_BREAKBAR.
///----------------------------------------------------------------------------------------------------
typedef struct CombatBreakbarEvent
{
	CombatEvent Base;
	float       Points; // Breakbar change, in the game's breakbar points.
} CombatBreakbarEvent;

///----------------------------------------------------------------------------------------------------
/// CombatEnergyEvent Struct
/// 	Payload of EV_RTAPI_COMBAT_ENERGY.
///----------------------------------------------------------------------------------------------------
typedef struct CombatEnergyEvent
{
	CombatEvent Base;
	float       Energy;
} CombatEnergyEvent;

///----------------------------------------------------------------------------------------------------
/// CombatExperienceEvent Struct
/// 	Payload of EV_RTAPI_COMBAT_EXPERIENCE.
///----------------------------------------------------------------------------------------------------
typedef struct CombatExperienceEvent
{
	CombatEvent Base;
	float       Experience;
	float       BonusExperience;
} CombatExperienceEvent;

///----------------------------------------------------------------------------------------------------
/// CombatHealthEvent Struct
/// 	Payload of EV_RTAPI_COMBAT_HEALTH.
///----------------------------------------------------------------------------------------------------
typedef struct CombatHealthEvent
{
	CombatEvent Base;
	float       Health;  // Change in health. Negative is damage, positive is healing.
	float       Barrier; // Change in barrier. Negative is damage, positive is barrier gained.
} CombatHealthEvent;

///----------------------------------------------------------------------------------------------------
/// CombatKarmaEvent Struct
/// 	Payload of EV_RTAPI_COMBAT_KARMA.
///----------------------------------------------------------------------------------------------------
typedef struct CombatKarmaEvent
{
	CombatEvent Base;
	float       Karma;
} CombatKarmaEvent;

///----------------------------------------------------------------------------------------------------
/// CombatLuckEvent Struct
/// 	Payload of EV_RTAPI_COMBAT_LUCK.
///----------------------------------------------------------------------------------------------------
typedef struct CombatLuckEvent
{
	CombatEvent Base;
	float       Luck;
} CombatLuckEvent;

///----------------------------------------------------------------------------------------------------
/// CombatResistEvent Struct
/// 	Payload of EV_RTAPI_COMBAT_RESIST.
///----------------------------------------------------------------------------------------------------
typedef struct CombatResistEvent
{
	CombatEvent Base;
	uint32_t    Effect; // Game ID of the resisted effect, e.g. a condition or crowd control.
} CombatResistEvent;

///----------------------------------------------------------------------------------------------------
/// CombatScoreEvent Struct
/// 	Payload of EV_RTAPI_COMBAT_PVP_SCORE and EV_RTAPI_COMBAT_WVW_SCORE.
///----------------------------------------------------------------------------------------------------
typedef struct CombatScoreEvent
{
	CombatEvent Base;
	int32_t     Score;
} CombatScoreEvent;

///----------------------------------------------------------------------------------------------------
/// CombatWvWExperienceEvent Struct
/// 	Payload of EV_RTAPI_COMBAT_WVW_EXPERIENCE.
///----------------------------------------------------------------------------------------------------
typedef struct CombatWvWExperienceEvent
{
	CombatEvent Base;
	float       Experience;
} CombatWvWExperienceEvent;

///----------------------------------------------------------------------------------------------------
/// Specialization Struct
///----------------------------------------------------------------------------------------------------
typedef struct Specialization
{
	uint32_t ID;        // Specialization ID, 0 if the line is empty.
	uint32_t Traits[3]; // Trait IDs of the selected major traits: adept, master, grandmaster. 0 if none.
} Specialization;

///----------------------------------------------------------------------------------------------------
/// BuildData Struct
/// 	Payload of EV_RTAPI_BUILD_CHANGED.
///----------------------------------------------------------------------------------------------------
typedef struct BuildData
{
	uint32_t       Size;               // sizeof(BuildData) as raised. Fields are only ever appended.
	uint32_t       TemplateIndex;      // 0-based build template tab.
	uint32_t       Profession;         // 1-9 = Profession.
	Specialization Specializations[3];
} BuildData;

///----------------------------------------------------------------------------------------------------
/// EGearSlot Enumeration
///----------------------------------------------------------------------------------------------------
enum EGearSlot
{
	GSL_Helm,
	GSL_Shoulders,
	GSL_Coat,
	GSL_Gloves,
	GSL_Leggings,
	GSL_Boots,
	GSL_Back,
	GSL_Amulet,
	GSL_Accessory1,
	GSL_Accessory2,
	GSL_Ring1,
	GSL_Ring2,
	GSL_WeaponA1,
	GSL_WeaponA2,
	GSL_WeaponB1,
	GSL_WeaponB2,
	GSL_AquaticHelm,
	GSL_AquaticWeaponA,
	GSL_AquaticWeaponB,
	GSL_Relic,
	GSL_COUNT
};

///----------------------------------------------------------------------------------------------------
/// GearSlot Struct
/// 	IDs match the official API (/v2/items, /v2/itemstats).
///----------------------------------------------------------------------------------------------------
typedef struct GearSlot
{
	uint32_t ItemID;       // 0 if the slot is empty.
	uint32_t StatID;       // Itemstat ID, 0 if none.
	uint32_t Upgrades[2];  // Rune, or sigils. 0 if empty.
	uint32_t Infusions[3]; // Infusion or enrichment item IDs. 0 if empty.
} GearSlot;

///----------------------------------------------------------------------------------------------------
/// GearData Struct
/// 	Payload of EV_RTAPI_GEAR_CHANGED. Always the PvE equipment, also in PvP.
///----------------------------------------------------------------------------------------------------
typedef struct GearData
{
	uint32_t Size;             // sizeof(GearData) as raised. Fields are only ever appended.
	uint32_t TemplateIndex;    // 0-based equipment template tab.
	GearSlot Slots[GSL_COUNT]; // Indexed by EGearSlot.
} GearData;

///----------------------------------------------------------------------------------------------------
/// Guild Struct
///----------------------------------------------------------------------------------------------------
typedef struct Guild
{
	char ID[40];    // GUID as the official API writes it, e.g. "4BBB52AA-D768-4FC6-8EDE-C299F2822F0F".
	char Name[140]; // UTF-8. Only known for the represented guild, otherwise empty: look it up with the official API, /v2/guild/:id.
	char Tag[8];    // UTF-8, without brackets. Not known yet, always empty: look it up with the official API.
} Guild;

///----------------------------------------------------------------------------------------------------
/// GuildList Struct
/// 	Payload of EV_RTAPI_GUILDS_CHANGED. Variable length: Guilds holds Count entries, Size covers them all.
///----------------------------------------------------------------------------------------------------
typedef struct GuildList
{
	uint32_t Size;      // Size of the whole payload in bytes, including all Count entries of Guilds.
	uint32_t Count;     // Entries in Guilds, one per guild the account is in. May be 0.
	Guild    Guilds[1]; // Count entries. Declared with one, the payload is as long as Count needs.
} GuildList;

///----------------------------------------------------------------------------------------------------
/// Attributes Struct
///----------------------------------------------------------------------------------------------------
typedef struct Attributes
{
	uint32_t Power;
	uint32_t Precision;
	uint32_t Toughness;
	uint32_t Vitality;
	uint32_t Ferocity;
	uint32_t HealingPower;
	uint32_t ConditionDamage;
	uint32_t Concentration;
	uint32_t Expertise;
	uint32_t AgonyResistance;
} Attributes;

///----------------------------------------------------------------------------------------------------
/// EBreakbarState Enumeration
///----------------------------------------------------------------------------------------------------
enum EBreakbarState
{
	BBS_None,       // No breakbar.
	BBS_Active,
	BBS_Recovering,
	BBS_Immune
};

///----------------------------------------------------------------------------------------------------
/// RealTimeData Struct
///----------------------------------------------------------------------------------------------------
typedef struct RealTimeData
{
	/* Game Data */
	uint32_t GameBuild; // Set to 0 when RTAPI is unloaded.
	uint32_t GameState;
	uint32_t Language;

	/* Instance/World Data */
	uint32_t TimeOfDay;
	uint32_t MapID;
	uint32_t MapType;
	uint8_t  IPAddress[4];
	float    Cursor[3];          // Location of cursor in the world
	float    SquadMarkers[8][3]; // Locations of squad markers
	uint32_t GroupType;
	uint32_t GroupMemberCount;
	uint32_t RESERVED2;

	/* Player Data */
	uint32_t Size;              // sizeof(RealTimeData) as written. 0 on builds before Size existed. Check it before reading appended fields.
	char     AccountName[140];
	char     CharacterName[140];
	float    CharacterPosition[3];
	float    CharacterFacing[3];
	uint32_t Profession;
	uint32_t EliteSpecialization;
	uint32_t MountIndex;
	uint32_t CharacterState;

	/* Camera Data */
	float    CameraPosition[3];
	float    CameraFacing[3];
	float    CameraFOV;
	uint32_t IsActionCamera : 1;

	/* Additions. Just slapped on. */
	uint32_t CharacterLevel;
	uint32_t CharacterEffectiveLevel;

	/* Build & Gear. Full data in EV_RTAPI_BUILD_CHANGED and EV_RTAPI_GEAR_CHANGED. */
	uint32_t BuildTemplateIndex; // 0-based.
	uint32_t GearTemplateIndex;  // 0-based.

	/* Attributes */
	Attributes BaseAttributes;      // From level and equipment, before scaling and effects.
	Attributes EffectiveAttributes; // As the hero panel shows them: scaled, including boons such as Might.

	/* Target */
	uint32_t TargetID;            // Agent ID, same as the combat API. 0 if nothing is selected.
	uint32_t TargetType;          // EAgentType
	uint32_t TargetSpeciesID;     // Character: Species ID; Gadget/AttackTarget: Gadget ID. Same as CombatAgent::SpeciesID.
	uint32_t TargetAttitude;      // EAttitude
	float    TargetHealth;        // Percent, 0-100. Currently whole numbers, as the game shows them.
	float    TargetBarrier;       // Percent of max health, 0-100. Currently whole numbers, as the game shows them.
	uint32_t TargetBreakbarState; // EBreakbarState
	float    TargetBreakbar;      // Percent, 0-100. Currently whole numbers, as the game shows them.

	/* Guild */
	char     RepresentedGuildID[40];    // Empty if not representing a guild.
	char     RepresentedGuildName[140]; // UTF-8.

	/* Boons */
	uint8_t  Boons[RTAPI_BOON_SLOTS]; // The player's own boons. Stacks per EBoon, 0 if inactive. Might and Stability count their stacks, the others are 1 while active.

	/* Synchronisation */
	uint32_t Frame; // Frame counter. Odd while RTAPI writes a frame, even when it is complete. See README, reading from other threads.
} RealTimeData;

#endif
