///----------------------------------------------------------------------------------------------------
/// Copyright (c) Raidcore.GG - Licensed under the MIT license.
///
/// Name         :  RTAPI.hpp
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
#define DL_RTAPI_GROUP                "RTAPI_GROUP"                // DataLink is RTAPI::RealTimeGroupData struct. Frame-synchronized like DL_RTAPI.

#define EV_RTAPI_BUILD_CHANGED        "RTAPI_BUILD_CHANGED"        // Payload is RTAPI::BuildData*. Raised on change, and to addons loaded later.
#define EV_RTAPI_GEAR_CHANGED         "RTAPI_GEAR_CHANGED"         // Payload is RTAPI::GearData*. Raised on change, and to addons loaded later.
#define EV_RTAPI_GUILDS_CHANGED       "RTAPI_GUILDS_CHANGED"       // Payload is RTAPI::GuildList*. Raised on change, and to addons loaded later.




#define EV_RTAPI_COMBAT_AGENT_ADDED            "RTAPI_COMBAT_AGENT_ADDED"            // Payload is RTAPI::CombatAgent*. Agent seen for the first time. Raised before any event that references it.
#define EV_RTAPI_COMBAT_AGENT_UPDATED          "RTAPI_COMBAT_AGENT_UPDATED"          // Payload is RTAPI::CombatAgent*. Agent data changed, e.g. its name was decoded.
#define EV_RTAPI_COMBAT_AGENT_REMOVED          "RTAPI_COMBAT_AGENT_REMOVED"          // Payload is RTAPI::CombatAgent*. Agent left the combat log, or the map changed. Its ID may be reused after.
#define EV_RTAPI_COMBAT_SKILL_ADDED            "RTAPI_COMBAT_SKILL_ADDED"            // Payload is RTAPI::CombatSkill*. Skill seen for the first time. Raised before any event that references it.
#define EV_RTAPI_COMBAT_SKILL_UPDATED          "RTAPI_COMBAT_SKILL_UPDATED"          // Payload is RTAPI::CombatSkill*. Skill data changed, e.g. its name was decoded.
#define EV_RTAPI_COMBAT_BLOCK                  "RTAPI_COMBAT_BLOCK"                  // Payload is RTAPI::CombatEvent*.
#define EV_RTAPI_COMBAT_BREAKBAR               "RTAPI_COMBAT_BREAKBAR"               // Payload is RTAPI::CombatBreakbarEvent*.
#define EV_RTAPI_COMBAT_COMBO                  "RTAPI_COMBAT_COMBO"                  // Payload is RTAPI::CombatEvent*.
#define EV_RTAPI_COMBAT_DEATH                  "RTAPI_COMBAT_DEATH"                  // Payload is RTAPI::CombatEvent*.
#define EV_RTAPI_COMBAT_DOWN                   "RTAPI_COMBAT_DOWN"                   // Payload is RTAPI::CombatEvent*.
#define EV_RTAPI_COMBAT_ENERGY                 "RTAPI_COMBAT_ENERGY"                 // Payload is RTAPI::CombatEnergyEvent*.
#define EV_RTAPI_COMBAT_EVADE                  "RTAPI_COMBAT_EVADE"                  // Payload is RTAPI::CombatEvent*.
#define EV_RTAPI_COMBAT_EXPERIENCE             "RTAPI_COMBAT_EXPERIENCE"             // Payload is RTAPI::CombatExperienceEvent*.
#define EV_RTAPI_COMBAT_HEALTH                 "RTAPI_COMBAT_HEALTH"                 // Payload is RTAPI::CombatHealthEvent*.
#define EV_RTAPI_COMBAT_INTERRUPT              "RTAPI_COMBAT_INTERRUPT"              // Payload is RTAPI::CombatEvent*.
#define EV_RTAPI_COMBAT_INVULNERABILITY_ABSORB "RTAPI_COMBAT_INVULNERABILITY_ABSORB" // Payload is RTAPI::CombatEvent*.
#define EV_RTAPI_COMBAT_KARMA                  "RTAPI_COMBAT_KARMA"                  // Payload is RTAPI::CombatKarmaEvent*.
#define EV_RTAPI_COMBAT_LUCK                   "RTAPI_COMBAT_LUCK"                   // Payload is RTAPI::CombatLuckEvent*.
#define EV_RTAPI_COMBAT_MISSED_BY_SOURCE       "RTAPI_COMBAT_MISSED_BY_SOURCE"       // Payload is RTAPI::CombatEvent*.
#define EV_RTAPI_COMBAT_MISSED_TARGET          "RTAPI_COMBAT_MISSED_TARGET"          // Payload is RTAPI::CombatEvent*.
#define EV_RTAPI_COMBAT_PVP_SCORE              "RTAPI_COMBAT_PVP_SCORE"              // Payload is RTAPI::CombatScoreEvent*.
#define EV_RTAPI_COMBAT_RESIST                 "RTAPI_COMBAT_RESIST"                 // Payload is RTAPI::CombatResistEvent*.
#define EV_RTAPI_COMBAT_SKILL_ABSORBED         "RTAPI_COMBAT_SKILL_ABSORBED"         // Payload is RTAPI::CombatEvent*.
#define EV_RTAPI_COMBAT_SKILL_BEGIN            "RTAPI_COMBAT_SKILL_BEGIN"            // Payload is RTAPI::CombatEvent*.
#define EV_RTAPI_COMBAT_SKILL_END              "RTAPI_COMBAT_SKILL_END"              // Payload is RTAPI::CombatEvent*.
#define EV_RTAPI_COMBAT_SKILL_OBSTRUCTED       "RTAPI_COMBAT_SKILL_OBSTRUCTED"       // Payload is RTAPI::CombatEvent*.
#define EV_RTAPI_COMBAT_SKILL_OUT_OF_RANGE     "RTAPI_COMBAT_SKILL_OUT_OF_RANGE"     // Payload is RTAPI::CombatEvent*.
#define EV_RTAPI_COMBAT_WVW_SCORE              "RTAPI_COMBAT_WVW_SCORE"              // Payload is RTAPI::CombatScoreEvent*. Type is WvWScoreRed, WvWScoreBlue or WvWScoreGreen.
#define EV_RTAPI_COMBAT_WVW_EXPERIENCE         "RTAPI_COMBAT_WVW_EXPERIENCE"         // Payload is RTAPI::CombatWvWExperienceEvent*.

#include <cstdint>

///----------------------------------------------------------------------------------------------------
/// RTAPI Namespace
///----------------------------------------------------------------------------------------------------
namespace RTAPI
{
	///----------------------------------------------------------------------------------------------------
	/// EGameState Enumeration
	///----------------------------------------------------------------------------------------------------
	enum class EGameState : uint32_t
	{
		CharacterSelection,
		CharacterCreation,
		Cinematic,
		LoadingScreen,
		Gameplay
	};

	///----------------------------------------------------------------------------------------------------
	/// EGameLanguage Enumeration
	///----------------------------------------------------------------------------------------------------
	enum class EGameLanguage : uint32_t
	{
		English,
		Korean,
		French,
		German,
		Spanish,
		Chinese
	};

	///----------------------------------------------------------------------------------------------------
	/// ETimeOfDay Enumeration
	///----------------------------------------------------------------------------------------------------
	enum class ETimeOfDay : uint32_t
	{
		Dawn,
		Day,
		Dusk,
		Night
	};

	///----------------------------------------------------------------------------------------------------
	/// ECharacterState Enumeration
	///----------------------------------------------------------------------------------------------------
	enum class ECharacterState : uint32_t
	{
		IsAlive      = 1 << 0,
		IsDowned     = 1 << 1,
		IsInCombat   = 1 << 2,
		IsSwimming   = 1 << 3, // aka. Is on water surface
		IsUnderwater = 1 << 4, // aka. Is diving
		IsGliding    = 1 << 5,
		IsFlying     = 1 << 6
	};

	///----------------------------------------------------------------------------------------------------
	/// EMapType Enumeration
	///----------------------------------------------------------------------------------------------------
	enum class EMapType : uint32_t
	{
		AutoRedirect,
		CharacterCreation,
		PvP,
		GvG,
		Instance,
		Public,
		Tournament,
		Tutorial,
		UserTournament,
		WvW_EternalBattlegrounds,
		WvW_BlueBorderlands,
		WvW_GreenBorderlands,
		WvW_RedBorderlands,
		WVW_FortunesVale,
		WvW_ObsidianSanctum,
		WvW_EdgeOfTheMists,
		Public_Mini,
		BigBattle,
		WvW_Lounge
	};

	///----------------------------------------------------------------------------------------------------
	/// EGroupType Enumeration
	///----------------------------------------------------------------------------------------------------
	enum class EGroupType : uint32_t
	{
		None,
		Party,
		RaidSquad,
		Squad
	};

	///----------------------------------------------------------------------------------------------------
	/// GroupMember Struct
	///----------------------------------------------------------------------------------------------------
	struct GroupMember
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
	};

	///----------------------------------------------------------------------------------------------------
	/// GroupMemberVitals Struct
	///----------------------------------------------------------------------------------------------------
	struct GroupMemberVitals
	{
		char     AccountName[140]; // Matches GroupMember::AccountName.
		float    Health;           // Percent, 0-100. Currently whole numbers, as the game shows them. 0 if not in the player's instance.
	};

	///----------------------------------------------------------------------------------------------------
	/// RealTimeGroupData Struct
	/// 	DataLink DL_RTAPI_GROUP. Frame-synchronized.
	///----------------------------------------------------------------------------------------------------
	struct RealTimeGroupData
	{
		uint32_t          Size;        // sizeof(RealTimeGroupData) as written. 0 when RTAPI is unloaded.
		uint32_t          Count;       // Used entries in Members.
		GroupMemberVitals Members[50];
		uint32_t          Frame; // Frame counter. Odd while RTAPI writes a frame, even when it is complete. See README, reading from other threads.
	};

	///----------------------------------------------------------------------------------------------------
	/// EAgentType Enumeration
	///----------------------------------------------------------------------------------------------------
	enum class EAgentType : uint32_t
	{
		Character,
		Gadget,
		AttackTarget
	};

	///----------------------------------------------------------------------------------------------------
	/// EAttitude Enumeration
	///----------------------------------------------------------------------------------------------------
	enum class EAttitude : uint32_t
	{
		Friendly,
		Hostile,
		Indifferent,
		Neutral
	};

	///----------------------------------------------------------------------------------------------------
	/// CombatAgent Struct
	/// 	Payload of the EV_RTAPI_COMBAT_AGENT_* events.
	///----------------------------------------------------------------------------------------------------
	struct CombatAgent
	{
		uint32_t   Size;             // sizeof(CombatAgent) as raised. Fields are only ever appended.
		uint32_t   ID;               // Agent ID, unique within the current map instance.
		EAgentType Type;
		uint32_t   SpeciesID;        // Character: Species ID; Gadget/AttackTarget: Gadget ID.
		uint32_t   OwnerID;          // Agent ID of the top-most owner, if IsMinion; otherwise 0.
		EAttitude  Attitude;         // Characters only. Towards the player. Checked on every event, a change raises AGENT_UPDATED.
		uint32_t   Profession;       // 1-9 = Profession, if IsPlayer; otherwise 0.
		char       Name[140];        // UTF-8. Empty until decoded (see EV_RTAPI_COMBAT_AGENT_UPDATED), and for hostile players.
		char       AccountName[140]; // UTF-8. Only for players known to the player, e.g. party, squad, contacts. Never for hostile players.
		uint32_t   IsSelf   : 1;     // Is the player's own character.
		uint32_t   IsPlayer : 1;
		uint32_t   IsMinion : 1;     // Is owned by another agent, e.g. a pet, clone or summon.
	};

	///----------------------------------------------------------------------------------------------------
	/// CombatSkill Struct
	/// 	Payload of the EV_RTAPI_COMBAT_SKILL_* events.
	///----------------------------------------------------------------------------------------------------
	struct CombatSkill
	{
		uint32_t Size;      // sizeof(CombatSkill) as raised. Fields are only ever appended.
		uint32_t ID;
		char     Name[140]; // UTF-8. Empty until decoded, see EV_RTAPI_COMBAT_SKILL_UPDATED.
	};

	///----------------------------------------------------------------------------------------------------
	/// ECombatEventType Enumeration
	///----------------------------------------------------------------------------------------------------
	enum class ECombatEventType : uint32_t
	{
		Block,
		Breakbar,
		Combo,
		Death,
		Down,
		Energy,
		Evade,
		Experience,
		Health,
		Interrupt,
		InvulnerabilityAbsorb,
		Karma,
		Luck,
		MissedBySource,
		MissedTarget,
		PvPScore,
		Resist,
		SkillAbsorbed,
		SkillBegin,
		SkillEnd,
		SkillObstructed,
		SkillOutOfRange,
		WvWScoreRed,
		WvWScoreBlue,
		WvWScoreGreen,
		WvWExperience
	};

	///----------------------------------------------------------------------------------------------------
	/// CombatEvent Struct
	/// 	Common to all combat events, and the payload of events without values.
	/// 	Only contains events from the player's own combat log.
	/// 	Every payload is only valid for the duration of the event callback.
	///----------------------------------------------------------------------------------------------------
	struct CombatEvent
	{
		uint32_t         Size;                  // sizeof the full payload, e.g. sizeof(CombatHealthEvent). Fields are only ever appended.
		ECombatEventType Type;
		uint64_t         Time;                  // Unix timestamp in milliseconds.
		uint32_t         SourceID;              // Agent ID, see EV_RTAPI_COMBAT_AGENT_*. 0 if there is none.
		uint32_t         DestinationID;         // Agent ID, see EV_RTAPI_COMBAT_AGENT_*. 0 if there is none.
		uint32_t         SkillID;               // Skill ID, see EV_RTAPI_COMBAT_SKILL_*. 0 if there is none.
		uint32_t         IsBonus           : 1;
		uint32_t         IsCritical        : 1;
		uint32_t         IsFumble          : 1;
		uint32_t         IsConditionDamage : 1;
	};

	///----------------------------------------------------------------------------------------------------
	/// CombatBreakbarEvent Struct
	/// 	Payload of EV_RTAPI_COMBAT_BREAKBAR.
	///----------------------------------------------------------------------------------------------------
	struct CombatBreakbarEvent
	{
		CombatEvent Base;
		float       Points; // Breakbar change, in the game's breakbar points.
	};

	///----------------------------------------------------------------------------------------------------
	/// CombatEnergyEvent Struct
	/// 	Payload of EV_RTAPI_COMBAT_ENERGY.
	///----------------------------------------------------------------------------------------------------
	struct CombatEnergyEvent
	{
		CombatEvent Base;
		float       Energy;
	};

	///----------------------------------------------------------------------------------------------------
	/// CombatExperienceEvent Struct
	/// 	Payload of EV_RTAPI_COMBAT_EXPERIENCE.
	///----------------------------------------------------------------------------------------------------
	struct CombatExperienceEvent
	{
		CombatEvent Base;
		float       Experience;
		float       BonusExperience;
	};

	///----------------------------------------------------------------------------------------------------
	/// CombatHealthEvent Struct
	/// 	Payload of EV_RTAPI_COMBAT_HEALTH.
	///----------------------------------------------------------------------------------------------------
	struct CombatHealthEvent
	{
		CombatEvent Base;
		float       Health;  // Change in health. Negative is damage, positive is healing.
		float       Barrier; // Change in barrier. Negative is damage, positive is barrier gained.
	};

	///----------------------------------------------------------------------------------------------------
	/// CombatKarmaEvent Struct
	/// 	Payload of EV_RTAPI_COMBAT_KARMA.
	///----------------------------------------------------------------------------------------------------
	struct CombatKarmaEvent
	{
		CombatEvent Base;
		float       Karma;
	};

	///----------------------------------------------------------------------------------------------------
	/// CombatLuckEvent Struct
	/// 	Payload of EV_RTAPI_COMBAT_LUCK.
	///----------------------------------------------------------------------------------------------------
	struct CombatLuckEvent
	{
		CombatEvent Base;
		float       Luck;
	};

	///----------------------------------------------------------------------------------------------------
	/// CombatResistEvent Struct
	/// 	Payload of EV_RTAPI_COMBAT_RESIST.
	///----------------------------------------------------------------------------------------------------
	struct CombatResistEvent
	{
		CombatEvent Base;
		uint32_t    Effect; // Game ID of the resisted effect, e.g. a condition or crowd control.
	};

	///----------------------------------------------------------------------------------------------------
	/// CombatScoreEvent Struct
	/// 	Payload of EV_RTAPI_COMBAT_PVP_SCORE and EV_RTAPI_COMBAT_WVW_SCORE.
	///----------------------------------------------------------------------------------------------------
	struct CombatScoreEvent
	{
		CombatEvent Base;
		int32_t     Score;
	};

	///----------------------------------------------------------------------------------------------------
	/// CombatWvWExperienceEvent Struct
	/// 	Payload of EV_RTAPI_COMBAT_WVW_EXPERIENCE.
	///----------------------------------------------------------------------------------------------------
	struct CombatWvWExperienceEvent
	{
		CombatEvent Base;
		float       Experience;
	};

	///----------------------------------------------------------------------------------------------------
	/// Specialization Struct
	///----------------------------------------------------------------------------------------------------
	struct Specialization
	{
		uint32_t ID;        // Specialization ID, 0 if the line is empty.
		uint32_t Traits[3]; // Trait IDs of the selected major traits: adept, master, grandmaster. 0 if none.
	};

	///----------------------------------------------------------------------------------------------------
	/// BuildData Struct
	/// 	Payload of EV_RTAPI_BUILD_CHANGED.
	///----------------------------------------------------------------------------------------------------
	struct BuildData
	{
		uint32_t       Size;               // sizeof(BuildData) as raised. Fields are only ever appended.
		uint32_t       TemplateIndex;      // 0-based build template tab.
		uint32_t       Profession;         // 1-9 = Profession.
		Specialization Specializations[3];
	};

	///----------------------------------------------------------------------------------------------------
	/// EGearSlot Enumeration
	///----------------------------------------------------------------------------------------------------
	enum class EGearSlot : uint32_t
	{
		Helm,
		Shoulders,
		Coat,
		Gloves,
		Leggings,
		Boots,
		Back,
		Amulet,
		Accessory1,
		Accessory2,
		Ring1,
		Ring2,
		WeaponA1,
		WeaponA2,
		WeaponB1,
		WeaponB2,
		AquaticHelm,
		AquaticWeaponA,
		AquaticWeaponB,
		Relic,
		COUNT
	};

	///----------------------------------------------------------------------------------------------------
	/// GearSlot Struct
	/// 	IDs match the official API (/v2/items, /v2/itemstats).
	///----------------------------------------------------------------------------------------------------
	struct GearSlot
	{
		uint32_t ItemID;       // 0 if the slot is empty.
		uint32_t StatID;       // Itemstat ID, 0 if none.
		uint32_t Upgrades[2];  // Rune, or sigils. 0 if empty.
		uint32_t Infusions[3]; // Infusion or enrichment item IDs. 0 if empty.
	};

	///----------------------------------------------------------------------------------------------------
	/// GearData Struct
	/// 	Payload of EV_RTAPI_GEAR_CHANGED. Always the PvE equipment, also in PvP.
	///----------------------------------------------------------------------------------------------------
	struct GearData
	{
		uint32_t Size;                                // sizeof(GearData) as raised. Fields are only ever appended.
		uint32_t TemplateIndex;                       // 0-based equipment template tab.
		GearSlot Slots[(uint32_t)EGearSlot::COUNT];   // Indexed by EGearSlot.
	};

	///----------------------------------------------------------------------------------------------------
	/// Guild Struct
	///----------------------------------------------------------------------------------------------------
	struct Guild
	{
		char ID[40];    // GUID as the official API writes it, e.g. "4BBB52AA-D768-4FC6-8EDE-C299F2822F0F".
		char Name[140]; // UTF-8. Only known for the represented guild, otherwise empty: look it up with the official API, /v2/guild/:id.
		char Tag[8];    // UTF-8, without brackets. Not known yet, always empty: look it up with the official API.
	};

	///----------------------------------------------------------------------------------------------------
	/// GuildList Struct
	/// 	Payload of EV_RTAPI_GUILDS_CHANGED. Variable length: Guilds holds Count entries, Size covers them all.
	///----------------------------------------------------------------------------------------------------
	struct GuildList
	{
		uint32_t Size;      // Size of the whole payload in bytes, including all Count entries of Guilds.
		uint32_t Count;     // Entries in Guilds, one per guild the account is in. May be 0.
		Guild    Guilds[1]; // Count entries. Declared with one, the payload is as long as Count needs.
	};

	///----------------------------------------------------------------------------------------------------
	/// Attributes Struct
	///----------------------------------------------------------------------------------------------------
	struct Attributes
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
	};

	///----------------------------------------------------------------------------------------------------
	/// EBreakbarState Enumeration
	///----------------------------------------------------------------------------------------------------
	enum class EBreakbarState : uint32_t
	{
		None, // No breakbar.
		Active,
		Recovering,
		Immune
	};

	///----------------------------------------------------------------------------------------------------
	/// RealTimeData Struct
	///----------------------------------------------------------------------------------------------------
	struct RealTimeData
	{
		/* Game Data */
		uint32_t        GameBuild; // Set to 0 when RTAPI is unloaded.
		EGameState      GameState;
		EGameLanguage   Language;

		/* Instance/World Data */
		ETimeOfDay      TimeOfDay;
		uint32_t        MapID;
		EMapType        MapType;
		uint8_t         IPAddress[4];
		float           Cursor[3];          // Location of cursor in the world
		float           SquadMarkers[8][3]; // Locations of squad markers
		EGroupType      GroupType;
		uint32_t        GroupMemberCount;
		uint32_t        RESERVED2;

		/* Player Data */
		uint32_t        Size;               // sizeof(RealTimeData) as written. 0 on builds before Size existed. Check it before reading appended fields.
		char            AccountName[140];
		char            CharacterName[140];
		float           CharacterPosition[3];
		float           CharacterFacing[3];
		uint32_t        Profession;
		uint32_t        EliteSpecialization;
		uint32_t        MountIndex;
		ECharacterState CharacterState;

		/* Camera Data */
		float           CameraPosition[3];
		float           CameraFacing[3];
		float           CameraFOV;
		uint32_t        IsActionCamera : 1;

		/* Additions. Just slapped on. */
		uint32_t        CharacterLevel;
		uint32_t        CharacterEffectiveLevel;

		/* Build & Gear. Full data in EV_RTAPI_BUILD_CHANGED and EV_RTAPI_GEAR_CHANGED. */
		uint32_t        BuildTemplateIndex; // 0-based.
		uint32_t        GearTemplateIndex;  // 0-based.

		/* Attributes */
		Attributes      BaseAttributes;      // From level and equipment, before scaling and effects.
		Attributes      EffectiveAttributes; // As the hero panel shows them: scaled, including boons such as Might.

		/* Target */
		uint32_t        TargetID;            // Agent ID, same as the combat API. 0 if nothing is selected.
		EAgentType      TargetType;
		uint32_t        TargetSpeciesID;     // Character: Species ID; Gadget/AttackTarget: Gadget ID. Same as CombatAgent::SpeciesID.
		EAttitude       TargetAttitude;
		float           TargetHealth;        // Percent, 0-100. Currently whole numbers, as the game shows them.
		float           TargetBarrier;       // Percent of max health, 0-100. Currently whole numbers, as the game shows them.
		EBreakbarState  TargetBreakbarState;
		float           TargetBreakbar;      // Percent, 0-100. Currently whole numbers, as the game shows them.

		/* Guild */
		char            RepresentedGuildID[40];    // Empty if not representing a guild.
		char            RepresentedGuildName[140]; // UTF-8.

		/* Synchronisation */
		uint32_t        Frame; // Frame counter. Odd while RTAPI writes a frame, even when it is complete. See README, reading from other threads.
	};
}

#endif
