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
#define EV_RTAPI_GROUP_MEMBER_JOINED  "RTAPI_GROUP_MEMBER_JOINED"  // Payload is RTAPI::GroupMember*
#define EV_RTAPI_GROUP_MEMBER_LEFT    "RTAPI_GROUP_MEMBER_LEFT"    // Payload is RTAPI::GroupMember*
#define EV_RTAPI_GROUP_MEMBER_UPDATED "RTAPI_GROUP_MEMBER_UPDATED" // Payload is RTAPI::GroupMember*



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
} GroupMember;

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
	uint32_t RESERVED1;
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
} RealTimeData;

#endif
