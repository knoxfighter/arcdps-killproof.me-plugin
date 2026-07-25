#pragma once

#include <fstream>
#include <ArcdpsExtension/arcdps_structs.h>
#include <ArcdpsExtension/ExtensionTranslations.h>
#include <ArcdpsExtension/Localization.h>
#include <ArcdpsExtension/UETranslations.h>
#include <magic_enum/magic_enum.hpp>
#include <nlohmann/json.hpp>

namespace Lang
{
	static std::string LikeGame = "LikeGame";
}

template<size_t A, size_t B> struct TAssertEquality {
  static_assert(A==B, "Not equal");
  static constexpr bool _cResult = (A==B);
};

template <>
struct magic_enum::customize::enum_range<ArcdpsExtension::UETranslation>
{
	static constexpr int min = 0;
	static constexpr int max = 500;
	// (max - min) must be less than UINT16_MAX.
};

constexpr auto enumMax = magic_enum::detail::max_v<ArcdpsExtension::UETranslation, magic_enum::as_common<>>;

// static constexpr bool _cIsEqual = 
// TAssertEquality<enumMax, 47>::_cResult;

// static_assert(enumMax == 49);

enum KillproofMeTranslations
{
	KMT_UseCustomColumns = ArcdpsExtension::ET_UseCustomColumns,
	KMT_AccountName = enumMax + 1,
	KMT_CharacterName,
	KMT_KillproofId,
	KMT_SubgroupText,
	KMT_Li_Short,
	KMT_Ld_Short,
	KMT_LiLd_Short,
	KMT_Uce_Short,
	KMT_Ufe_Short,
	KMT_Vg_Short,
	KMT_Vg_Long,
	KMT_Gorse_Short,
	KMT_Gorse_Long,
	KMT_Sabetha_Short,
	KMT_Sabetha_Long,
	KMT_Sloth_Short,
	KMT_Matthias_Short,
	KMT_Matthias_Long,
	KMT_Escort_Short,
	KMT_Kc_Short,
	KMT_Kc_Long,
	KMT_Xera_Short,
	KMT_Cairn_Short,
	KMT_Cairn_Long,
	KMT_Mo_Short,
	KMT_Mo_Long,
	KMT_Samarog_Short,
	KMT_Deimos_Short,
	KMT_Desmina_Short,
	KMT_Desmina_Long,
	KMT_River_Short,
	KMT_River_Long,
	KMT_Statues_Short,
	KMT_Dhuum_Short,
	KMT_Ca_Short,
	KMT_Ca_Long,
	KMT_Twins_Short,
	KMT_Twins_Long,
	KMT_Qadim_Short,
	KMT_Sabir_Short,
	KMT_Adina_Short,
	KMT_Qadim2_Short,
	KMT_Qadim2_Long,
	KMT_Greer_Short,
	KMT_GreerCM_Short,
	KMT_Greer_Long,
	KMT_GreerCM_Long,
	KMT_Decima_Short,
	KMT_DecimaCM_Short,
	KMT_Decima_Long,
	KMT_DecimaCM_Long,
	KMT_Ura_Short,
	KMT_UraCM_Short,
	KMT_BoneskinnerVial_Short,
	KMT_BoneskinnerVial_Long,
	KMT_Ankka_Short,
	KMT_Ankka_Long,
	KMT_MinisterLi_Short,
	KMT_MinisterLi_Long,
	KMT_Harvest_Short,
	KMT_Harvest_Long,
	KMT_MaiTrin_Short,
	KMT_MaiTrin_Long,
	KMT_MaiTrinCM_Short,
	KMT_MaiTrinCM_Long,
	KMT_AnkkaCM_Short,
	KMT_AnkkaCM_Long,
	KMT_MinisterLiCM_Short,
	KMT_MinisterLiCM_Long,
	KMT_HarvestCM_Short,
	KMT_HarvestCM_Long,
	KMT_OLC_Short,
	KMT_OLC_Long,
	KMT_OLCCM_Short,
	KMT_OLCCM_Long,
	KMT_CO_Short,
	KMT_CO_Long,
	KMT_COCM_Short,
	KMT_COCM_Long,
	KMT_FEBE_Short,
	KMT_FEBE_Long,
	KMT_FEBECM_Short,
	KMT_FEBECM_Long,
	KMT_Kela_Short,
	KMT_Kela_Long,
	KMT_KelaCM_Short,
	KMT_KelaCM_Long,
	KMT_Bananas,
	KMT_KpWindowNameDefault,
	KMT_AppearAsInOptionDefault,
	KMT_SettingsShowPrivateText,
	KMT_SettingsShowControls,
	KMT_SettingsShowLinkedByDefault,
	KMT_SettingsShowCommander,
	KMT_SettingsBlockedText,
	KMT_ShowLinkedTotals,
	KMT_UnofficialExtrasNotInstalled,
	KMT_AddPlayerTooltip,
	KMT_AddPlayerText,
	KMT_ClearText,
	KMT_ClearTooltip,
	KMT_CopyKpIdText,
	KMT_Overall,
	KMT_Killproofs,
	KMT_Coffers,
	KMT_SettingsDisableESCText,
	KMT_SettingsCofferValue,
	KMT_SettingsHideExtrasMessage,
	KMT_SettingsClearCacheText,
	KMT_SettingsClearCacheTooltip,
	KMT_LanguageAsIngameTooltip,
	KMT_Raids,
	KMT_Fractals,
	KMT_Strikes,
	KMT_Misc,
	KMT_MapBasedStrikes,
};

template <>
struct magic_enum::customize::enum_range<KillproofMeTranslations>
{
	static constexpr int min = 0;
	static constexpr int max = 1000;
	// (max - min) must be less than UINT16_MAX.
};

void LoadAdditionalTranslations();
void LoadTranslationFiles();
void SaveTranslationFile();
