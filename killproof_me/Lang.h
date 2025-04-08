#pragma once

#include "ArcdpsExtension/arcdps_structs.h"

#include <magic_enum.hpp>

#include "ArcdpsExtension/ExtensionTranslations.h"
#include "ArcdpsExtension/Localization.h"

template<size_t A, size_t B> struct TAssertEquality {
  static_assert(A==B, "Not equal");
  static constexpr bool _cResult = (A==B);
};

constexpr auto enumMax = magic_enum::detail::max_v<ArcdpsExtension::ExtensionTranslation, magic_enum::as_common<>>;

static constexpr bool _cIsEqual = 
  TAssertEquality<enumMax, 47>::_cResult;
// static_assert(enumMax == 48);

enum KillproofMeTranslations {
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
	KMT_LanguageGermanTooltip,
	KMT_LanguageFrenchTooltip,
	KMT_LanguageSpanishTooltip,
	KMT_Raids,
	KMT_Fractals,
	KMT_Strikes,
	KMT_Misc,
};

constexpr std::array KILLPROOF_ME_TRANSLATION_ENGLISH = std::to_array({
	u8"Account", // KMT_AccountName
	u8"Character", // KMT_CharacterName
	u8"ID", // KMT_KillproofId
	u8"Group", // KMT_SubgroupText
	u8"LI", // KMT_Li_Short
	u8"LD", // KMT_Ld_Short
	u8"LI+LD", // KMT_LiLd_Short
	u8"UCE", // KMT_Uce_Short
	u8"UFE", // KMT_Ufe_Short
	u8"VG", // KMT_Vg_Short
	u8"Vale Guardian", // KMT_Vg_Long
	u8"Gorse", // KMT_Gorse_Short
	u8"Gorseval the Multifarious", // KMT_Gorse_Long
	u8"Sabetha", // KMT_Sabetha_Short
	u8"Sabetha the Saboteur", // KMT_Sabetha_Long
	u8"Sloth", // KMT_Sloth_Short
	u8"Matthias", // KMT_Matthias_Short
	u8"Matthias Gabrel", // KMT_Matthias_Long
	u8"Escort", // KMT_Escort_Short
	u8"KC", // KMT_Kc_Short
	u8"Keep Construct", // KMT_Kc_Long
	u8"Xera", // KMT_Xera_Short
	u8"Cairn", // KMT_Cairn_Short
	u8"Cairn the Indomitable", // KMT_Cairn_Long
	u8"MO", // KMT_Mo_Short
	u8"Mursaat Overseer", // KMT_Mo_Long
	u8"Samarog", // KMT_Samarog_Short
	u8"Deimos", // KMT_Deimos_Short
	u8"Desmina", // KMT_Desmina_Short
	u8"Soulless Horror (Desmina)", // KMT_Desmina_Long
	u8"River", // KMT_River_Short
	u8"River of Souls", // KMT_River_Long
	u8"Statues", // KMT_Statues_Short
	u8"Dhuum", // KMT_Dhuum_Short
	u8"CA", // KMT_Ca_Short
	u8"Conjured Amalgamate", // KMT_Ca_Long
	u8"Twins", // KMT_Twins_Short
	u8"Twin Largos", // KMT_Twins_Long
	u8"Qadim", // KMT_Qadim_Short
	u8"Sabir", // KMT_Sabir_Short
	u8"Adina", // KMT_Adina_Short
	u8"Qadim2", // KMT_Qadim2_Short
	u8"Qadim the Peerless", // KMT_Qadim2_Long
	u8"Greer", // KMT_Greer_Short,
	u8"Greer CM", // KMT_GreerCM_Short,
	u8"Greer, the Blightbringer", // KMT_Greer_Long,
	u8"Greer, the Blightbringer CM", // KMT_Greer_Long,
	u8"Decima", // KMT_Decima_Short,
	u8"Decima CM", // KMT_DecimaCM_Short,
	u8"Decima, the Stormsinger", // KMT_Decima_Long,
	u8"Decima, the Stormsinger CM", // KMT_DecimaCM_Long,
	u8"Ura", // KMT_Ura_Short,
	u8"Ura CM", // KMT_UraCM_Short,
	u8"Vial", // KMT_BoneskinnerVial_Short
	u8"Boneskinner Ritual Vial", // KMT_BoneskinnerVial_Long
	u8"Ankka", // KMT_Ankka_Short
	u8"Xunlai Jade Junkyard (Ankka)", // KMT_Ankka_Long
	u8"KO", // KMT_MinisterLi_Short
	u8"Kaineng Overlook (Minister Li)", // KMT_MinisterLi_Long
	u8"HT", // KMT_Harvest_Short
	u8"Harvest Temple (Dragonvoid)", // KMT_Harvest_Long
	u8"Mai", // KMT_MaiTrin_Short
	u8"Aetherblade Hideout (Mai Trin)", // KMT_MaiTrin_Long
	u8"Mai CM", // KMT_MaiTrinCM_Short
	u8"Aetherblade Hideout (Mai Trin) CM", // KMT_MaiTrinCM_Long
	u8"Ankka CM", // KMT_AnkkaCM_Short
	u8"Xunlai Jade Junkyard (Ankka) CM", // KMT_AnkkaCM_Long
	u8"KO CM", // KMT_MinisterLiCM_Short
	u8"Kaineng Overlook (Minister Li) CM", // KMT_MinisterLiCM_Long
	u8"HT CM", // KMT_HarvestCM_Short
	u8"Harvest Temple (Dragonvoid) CM", // KMT_HarvestCM_Long
	u8"OLC", // KMT_OLC_Short
	u8"Old Lion's Court (Assault Knights)", //KMT_OLC_Long
	u8"OLC CM", // KMT_OLCCM_Short
	u8"Old Lion's Court CM (Assault Knights)", // KMT_OLCCM_Long,
	u8"CO", // KMT_CO_Short,
	u8"Cosmic Observatory (Dagda)", // KMT_CO_Long,
	u8"CO CM", // KMT_COCM_Short,
	u8"Cosmic Observatory (Dagda) CM", // KMT_COCM_Long,
	u8"Febe", // KMT_FEBE_Short,
	u8"Temple of Febe (Cerus)", // KMT_FEBE_Long,
	u8"Febe CM", // KMT_FEBECM_Short,
	u8"Temple of Febe (Cerus) CM", // KMT_FEBECM_Long,
	u8"Bananas", // KMT_Bananas
	u8"Killproof.me", // KMT_KpWindowNameDefault
	u8"Killproof.me", // KMT_AppearAsInOptionDefault
	u8"Private accounts", // KMT_SettingsShowPrivateText
	u8"Show controls", // KMT_SettingsShowControls
	u8"Show linked accounts by default", // KMT_SettingsShowLinkedByDefault
	u8"Show Commander Tag", // KMT_SettingsShowCommander
	u8"Text to display when data is unavailable/private", // KMT_SettingsBlockedText
	u8"Show linked totals directly", // KMT_ShowLinkedTotals
	u8"Unofficial extras plugin is not installed.\nInstall it to enable tracking of players on other instances.", // KMT_UnofficialExtrasNotInstalled
	u8"Accountname, killproof.me ID or Charactername to search and add to the list", // KMT_AddPlayerTooltip
	u8"Add", // KMT_AddPlayerText
	u8"Clear", // KMT_ClearText
	u8"Remove all manually added users", // KMT_ClearTooltip
	u8"Copy own KP ID", // KMT_CopyKpIdText
	u8"Overall", // KMT_Overall
	u8"Killproofs", // KMT_Killproofs
	u8"Coffers", // KMT_Coffers
	u8"Do NOT close killproof.me window on ESC", // KMT_SettingsDisableESCText
	u8"Killproofs per coffer", // KMT_SettingsCofferValue
	u8"Hide Unofficial Extras Message", // KMT_SettingsHideExtrasMessage
	u8"Clear Cache", // KMT_SettingsClearCacheText
	u8"Clear the cache and reload killproof.me data for all players", // KMT_SettingsClearCacheTooltip
	u8"Only works if Unofficial Extras is installed. Will fall back to English.", // KMT_LanguageAsIngameTooltip
	u8"Rough German translation, please report any wrong translations.", // KMT_LanguageGermanTooltip
	u8"Translated with deepl.com. Please report any wrong translations.", // KMT_LanguageFrenchTooltip
	u8"Translated with deepl.com. Please report any wrong translations.", // KMT_LanguageSpanishTooltip
	u8"Raids", // KMT_Raids
	u8"Fractals", // KMT_Fractals
	u8"Strikes", // KMT_Strikes
	u8"Miscellaneous", // KMT_Misc
});

constexpr std::array KILLPROOF_ME_TRANSLATION_GERMAN = std::to_array({
	u8"Account", // KMT_AccountName
	u8"Charakter", // KMT_CharacterName
	u8"ID", // KMT_KillproofId
	u8"Gruppe", // KMT_SubgroupText
	u8"LI", // KMT_Li_Short
	u8"LD", // KMT_Ld_Short
	u8"LI+LD", // KMT_LiLd_Short
	u8"UCE", // KMT_Uce_Short
	u8"UFE", // KMT_Ufe_Short
	u8"VG", // KMT_Vg_Short
	u8"Talwächter", // KMT_Vg_Long
	u8"Gorse", // KMT_Gorse_Short
	u8"Gorseval der Facettenreiche", // KMT_Gorse_Long
	u8"Sabetha", // KMT_Sabetha_Short
	u8"Sabetha die Saboteurin", // KMT_Sabetha_Long
	u8"Faulterion", // KMT_Sloth_Short
	u8"Matthias", // KMT_Matthias_Short
	u8"Matthias Gabrel", // KMT_Matthias_Long
	u8"Escort", // KMT_Escort_Short
	u8"KC", // KMT_Kc_Short
	u8"Festenkonstrukt", // KMT_Kc_Long
	u8"Xera", // KMT_Xera_Short
	u8"Cairn", // KMT_Cairn_Short
	u8"Cairn der Unbeugsame", // KMT_Cairn_Long
	u8"MO", // KMT_Mo_Short
	u8"Mursaat-Aufseher", // KMT_Mo_Long
	u8"Samarog", // KMT_Samarog_Short
	u8"Deimos", // KMT_Deimos_Short
	u8"Desmina", // KMT_Desmina_Short
	u8"Seelenloser Schrecken (Desmina)", // KMT_Desmina_Long
	u8"River", // KMT_River_Short
	u8"Fluss der Seelen", // KMT_River_Long
	u8"Statues", // KMT_Statues_Short
	u8"Dhuum", // KMT_Dhuum_Short
	u8"CA", // KMT_Ca_Short
	u8"Beschworene Verschmelzung", // KMT_Ca_Long
	u8"Twins", // KMT_Twins_Short
	u8"Largos-Assassinen", // KMT_Twins_Long
	u8"Qadim", // KMT_Qadim_Short
	u8"Sabir", // KMT_Sabir_Short
	u8"Adina", // KMT_Adina_Short
	u8"Qadim2", // KMT_Qadim2_Short
	u8"Qadim der Unvergleichliche", // KMT_Qadim2_Long
	u8"Greer", // KMT_Greer_Short,
	u8"Greer CM", // KMT_GreerCM_Short,
	u8"Greer, der Pestilenzbringer", // KMT_Greer_Long,
	u8"Greer, der Pestilenzbringer CM", // KMT_GreerCM_Long,
	u8"Decima", // KMT_Decima_Short,
	u8"Decima CM", // KMT_DecimaCM_Short,
	u8"Decima, die Sturmsängerin", // KMT_Decima_Long,
	u8"Decima, die Sturmsängerin CM", // KMT_DecimaCM_Long,
	u8"Ura", // KMT_Ura_Short,
	u8"Ura CM", // KMT_UraCM_Short,
	u8"Phiole", // KMT_BoneskinnerVial_Short
	u8"Knochenhäuter-Ritual-Phiole", // KMT_BoneskinnerVial_Long
	u8"Ankka", // KMT_Ankka_Short
	u8"Xunlai-Jade-Schrottplatz (Ankka)", // KMT_Ankka_Long
	u8"KO", // KMT_MinisterLi_Short
	u8"Kaineng-Aussichtspunkt (Minister Li)", // KMT_MinisterLi_Short
	u8"Erntetempel", // KMT_Harvest_Short
	u8"Erntetempel (Drachenleere)", // KMT_Harvest_Long
	u8"Mai", // KMT_MaiTrin_Short
	u8"Ätherklinger-Unterschlupf (Mai Trin)", // KMT_MaiTrin_Long
	u8"Mai CM", // KMT_MaiTrinCM_Short
	u8"Ätherklinger-Unterschlupf (Mai Trin) CM", // KMT_MaiTrinCM_Long
	u8"Ankka CM", // KMT_AnkkaCM_Short
	u8"Xunlai-Jade-Schrottplatz (Ankka) CM", // KMT_AnkkaCM_Long
	u8"KO CM", // KMT_MinisterLiCM_Short
	u8"Kaineng-Aussichtspunkt (Minsiter Li) CM", // KMT_MinisterLiCM_Long
	u8"Erntetempel CM", // KMT_HarvestCM_Short
	u8"Erntetempel (Drachenleere) CM", // KMT_HarvestCM_Long
	u8"OLC", // KMT_OLC_Short
	u8"Alter Löwenhof (Sturmritter)", //KMT_OLC_Long
	u8"OLC CM", // KMT_OLCCM_Short
	u8"Alter Löwenhof CM (Sturmritter)", // KMT_OLCCM_Long,
	u8"CO", // KMT_CO_Short,
	u8"Kosmisches Observatorium (Dagda)", // KMT_CO_Long,
	u8"CO CM", // KMT_COCM_Short,
	u8"Kosmisches Observatorium (Dagda) CM", // KMT_COCM_Long,
	u8"Febe", // KMT_FEBE_Short,
	u8"Tempel von Febe (Cerus)", // KMT_FEBE_Long,
	u8"Febe CM", // KMT_FEBECM_Short,
	u8"Tempel von Febe (Cerus) CM", // KMT_FEBECM_Long,
	u8"Bananen", // KMT_Bananas
	u8"Killproof.me", // KMT_KpWindowNameDefault
	u8"Killproof.me", // KMT_AppearAsInOptionDefault
	u8"Private Accounts", // KMT_SettingsShowPrivateText
	u8"Zeige Bedienelemente", // KMT_SettingsShowControls
	u8"Zeige verknüpfte Account Standardmäßig", // KMT_SettingsShowLinkedByDefault
	u8"Zeige Kommandeurssymbol", // KMT_SettingsShowCommander
	u8"Anzeigetext, wenn Daten nicht verfügbar/privat sind", // KMT_SettingsBlockedText
	u8"Zeige verknüpfte Gesamtwerte direkt", // KMT_ShowLinkedTotals
	u8"Das \"Unofficial extras plugin\" ist nicht installiert.\nInstalliere es, um Spiler auf anderen Instanzen sehen zu können.", // KMT_UnofficialExtrasNotInstalled
	u8"Suche nach Accountname, killproof.me ID oder Charaktername und füge es der Tabelle hinzu", // KMT_AddPlayerTooltip
	u8"Hinzufügen", // KMT_AddPlayerText
	u8"Löschen", // KMT_ClearText
	u8"Entferne alle manuell hinzugefügten Einträge", // KMT_ClearTooltip
	u8"Kopiere die eigene ID", // KMT_CopyKpIdText
	u8"Gesamt", // KMT_Overall
	u8"Killproofs", // KMT_Killproofs
	u8"Koffer", // KMT_Coffers
	u8"Schließe das killproof.me Fenster NICHT mit ESC", // KMT_SettingsDisableESCText
	u8"Killproofs pro Koffer", // KMT_SettingsCofferValue
	u8"Verstecke die \"Unofficial Extras\" Fehlernachricht", // KMT_SettingsHideExtrasMessage
	u8"Lösche Cache", // KMT_SettingsClearCacheText
	u8"Lösche den Cache und lade alle Spieler neu", // KMT_SettingsClearCacheTooltip
	u8"Funktioniert nur, wenn das \"Unofficial Extras Addon\" installiert ist. Falls nicht, wird Englisch verwendet.", // KMT_LanguageAsIngameTooltip
	u8"Grobe Deutsche Übersetzung. Bitte melde alle falschen/schlechten Übersetzungen.", // KMT_LanguageGermanTooltip
	u8"Übersetzt mit deepl.com. Bitte melde alle falschen/schlechten Übersetzungen.", // KMT_LanguageFrenchTooltip
	u8"Übersetzt mit deepl.com. Bitte melde alle falschen/schlechten Übersetzungen.", // KMT_LanguageSpanishTooltip
	u8"Schlachtzüge", // KMT_Raids
	u8"Fraktale", // KMT_Fractals
	u8"Angriffsmissionen", // KMT_Strikes
	u8"Sonstiges", // KMT_Misc
});

constexpr std::array KILLPROOF_ME_TRANSLATION_FRENCH = std::to_array({
	u8"Compte", // KMT_AccountName
	u8"Personnage", // KMT_CharacterName
	u8"ID", // KMT_KillproofId
	u8"Groupe", // KMT_SubgroupText
	u8"LI", // KMT_Li_Short
	u8"LD", // KMT_Ld_Short
	u8"LI+LD", // KMT_LiLd_Short
	u8"UCE", // KMT_Uce_Short
	u8"UFE", // KMT_Ufe_Short
	u8"VG", // KMT_Vg_Short
	u8"Gardien de la Vallée", // KMT_Vg_Long
	u8"Gorse", // KMT_Gorse_Short
	u8"Gorseval le Disparate", // KMT_Gorse_Long
	u8"Sabetha", // KMT_Sabetha_Short
	u8"Sabetha la saboteuse", // KMT_Sabetha_Long
	u8"Paressor", // KMT_Sloth_Short
	u8"Matthias", // KMT_Matthias_Short
	u8"Matthias Gabrel", // KMT_Matthias_Long
	u8"Escorte", // KMT_Escort_Short
	u8"KC", // KMT_Kc_Short
	u8"Titan du fort", // KMT_Kc_Long
	u8"Xera", // KMT_Xera_Short
	u8"Cairn", // KMT_Cairn_Short
	u8"Cairn l'Indomptable", // KMT_Cairn_Long
	u8"MO", // KMT_Mo_Short
	u8"Surveillant mursaat", // KMT_Mo_Long
	u8"Samarog", // KMT_Samarog_Short
	u8"Deimos", // KMT_Deimos_Short
	u8"Desmina", // KMT_Desmina_Short
	u8"Horreur sans âme (Desmina)", // KMT_Desmina_Long
	u8"Rivière", // KMT_River_Short
	u8"Rivière des âmes", // KMT_River_Long
	u8"Statues", // KMT_Statues_Short
	u8"Dhuum", // KMT_Dhuum_Short
	u8"CA", // KMT_Ca_Short
	u8"Amalgame conjuré", // KMT_Ca_Long
	u8"Jumeaux", // KMT_Twins_Short
	u8"Jumeaux Largos", // KMT_Twins_Long
	u8"Qadim", // KMT_Qadim_Short
	u8"Sabir", // KMT_Sabir_Short
	u8"Adina", // KMT_Adina_Short
	u8"Qadim2", // KMT_Qadim2_Short
	u8"Qadim l'Inégalé", // KMT_Qadim2_Long
	u8"Greer", // KMT_Greer_Short,
	u8"Greer CM", // KMT_GreerCM_Short,
	u8"Greer, le porte-fléau", // KMT_Greer_Long,
	u8"Greer, le porte-fléau CM", // KMT_GreerCM_Long,
	u8"Decima", // KMT_Decima_Short,
	u8"Decima CM", // KMT_DecimaCM_Short,
	u8"Decima, l'antienne de la tempête", // KMT_Decima_Long,
	u8"Decima, l'antienne de la tempête CM", // KMT_DecimaCM_Long,
	u8"Ura", // KMT_Ura_Short,
	u8"Ura CM", // KMT_UraCM_Short,
	u8"Fiole", // KMT_BoneskinnerVial_Short
	u8"Fiole du rituel du désosseur", // KMT_BoneskinnerVial_Long
	u8"Ankka", // KMT_Ankka_Short
	u8"Décharge de Xunlai Jade (Ankka)", // KMT_Ankka_Long
	u8"KO", // KMT_MinisterLi_Short
	u8"Belvédère de Kaineng (Ministre  Li)", // KMT_MinisterLi_Long
	u8"Temple des moissons", // KMT_Harvest_Short
	u8"Temple des moissons (Vide draconique)", // KMT_Harvest_Short
	u8"Mai", // KMT_MaiTrin_Short
	u8"Cachette des Étherlames (Mai Trin)", // KMT_MaiTrin_Long
	u8"Mai CM", // KMT_MaiTrinCM_Short
	u8"Cachette des Étherlames (Mai Trin) CM", // KMT_MaiTrinCM_Long
	u8"Ankka CM", // KMT_AnkkaCM_Short
	u8"Décharge de Xunlai Jade (Ankka) CM", // KMT_AnkkaCM_Long
	u8"KO CM", // KMT_MinisterLiCM_Short
	u8"Belvédère de Kaineng (Ministre Li) CM", // KMT_MinisterLiCM_Long
	u8"Temple des moissons CM", // KMT_HarvestCM_Short
	u8"Temple des moissons (Vide draconique) CM", // KMT_HarvestCM_Long
	u8"OLC", // KMT_OLC_Short
	u8"Cour du vieux Lion (chevaliers d'assaut)", //KMT_OLC_Long
	u8"OLC CM", // KMT_OLCCM_Short
	u8"Cour du vieux Lion CM (Chevaliers d'assaut)", // KMT_OLCCM_Long,
	u8"CO", // KMT_CO_Short,
	u8"Observatoire cosmique (Dagda)", // KMT_CO_Long,
	u8"CO CM", // KMT_COCM_Short,
	u8"Observatoire cosmique (Dagda) CM", // KMT_COCM_Long,
	u8"Febe", // KMT_FEBE_Short,
	u8"Temple de Febe (Cerus)", // KMT_FEBE_Long,
	u8"Febe CM", // KMT_FEBECM_Short,
	u8"Temple de Febe (Cerus) CM", // KMT_FEBECM_Long,
	u8"Bananes", // KMT_Bananas
	u8"Killproof.me", // KMT_KpWindowNameDefault
	u8"Killproof.me", // KMT_AppearAsInOptionDefault
	u8"Comptes privés", // KMT_SettingsShowPrivateText
	u8"Afficher les contrôles", // KMT_SettingsShowControls
	u8"Afficher les comptes liés par défaut", // KMT_SettingsShowLinkedByDefault
	u8"Afficher le tag du Commandant", // KMT_SettingsShowCommander
	u8"Texte à afficher lorsque les données sont indisponibles/privées", // KMT_SettingsBlockedText
	u8"Afficher directement les totaux liés", // KMT_ShowLinkedTotals
	u8"Le plugin d'extras non officiels n'est pas installé.\nInstallez-le pour permettre le suivi des joueurs sur d'autres instances.", // KMT_UnofficialExtrasNotInstalled
	u8"Nom de compte, ID de killproof.me ou Nom de personnage pour rechercher et ajouter à la liste", // KMT_AddPlayerTooltip
	u8"Ajouter", // KMT_AddPlayerText
	u8"Effacer", // KMT_ClearText
	u8"Supprimer tous les utilisateurs ajoutés manuellement", // KMT_ClearTooltip
	u8"Copier votre KP ID", // KMT_CopyKpIdText
	u8"En général", // KMT_Overall
	u8"Killproofs", // KMT_Killproofs
	u8"Coffres", // KMT_Coffers
	u8"Ne PAS fermer la fenêtre killproof.me en appuyant sur ESC.", // KMT_SettingsDisableESCText
	u8"Killproofs par coffre", // KMT_SettingsCofferValue
	u8"Cacher le message des extras non officiels", // KMT_SettingsHideExtrasMessage
	u8"Effacer le cache", // KMT_SettingsClearCacheText
	u8"Videz le cache et rechargez les données de killproof.me pour tous les joueurs.", // KMT_SettingsClearCacheTooltip
	u8"Ne fonctionne que si Unofficial Extras est installé. Retour à l'anglais.", // KMT_LanguageAsIngameTooltip
	u8"Traduction allemande approximative, veuillez signaler toute traduction erronée.", // KMT_LanguageGermanTooltip
	u8"Traduit avec deepl.com. Veuillez signaler toute traduction erronée.", // KMT_LanguageFrenchTooltip
	u8"Traduit avec deepl.com. Veuillez signaler toute traduction erronée.", // KMT_LanguageSpanishTooltip
	u8"Raids", // KMT_Raids
	u8"Fractales", // KMT_Fractals
	u8"Missions d'attaque", // KMT_Strikes
	u8"Divers", // KMT_Misc
});

constexpr std::array KILLPROOF_ME_TRANSLATION_SPANISH = std::to_array({
	u8"Cuenta", // KMT_AccountName
	u8"Carácter", // KMT_CharacterName
	u8"ID", // KMT_KillproofId
	u8"Grupo", // KMT_SubgroupText
	u8"LI", // KMT_Li_Short
	u8"LD", // KMT_Ld_Short
	u8"LI+LD", // KMT_LiLd_Short
	u8"UCE", // KMT_Uce_Short
	u8"UFE", // KMT_Ufe_Short
	u8"VG", // KMT_Vg_Short
	u8"Guardián del valle", // KMT_Vg_Long
	u8"Gorse", // KMT_Gorse_Short
	u8"Gorseval el Múltiple", // KMT_Gorse_Long
	u8"Sabetha", // KMT_Sabetha_Short
	u8"Sabetha la Saboteadora", // KMT_Sabetha_Long
	u8"Perezón", // KMT_Sloth_Short
	u8"Matías", // KMT_Matthias_Short
	u8"Matías Gabrel", // KMT_Matthias_Long
	u8"Escolta", // KMT_Escort_Short
	u8"KC", // KMT_Kc_Short
	u8"Ensamblaje de la Fortaleza", // KMT_Kc_Long
	u8"Xera", // KMT_Xera_Short
	u8"Cairn", // KMT_Cairn_Short
	u8"Cairn el Indomable", // KMT_Cairn_Long
	u8"MO", // KMT_Mo_Short
	u8"Dirigente mursaat", // KMT_Mo_Long
	u8"Samarog", // KMT_Samarog_Short
	u8"Deimos", // KMT_Deimos_Short
	u8"Desmina", // KMT_Desmina_Short
	u8"Horror sin alma", // KMT_Desmina_Long
	u8"Río", // KMT_River_Short
	u8"Río de Almas", // KMT_River_Long
	u8"Estatuas", // KMT_Statues_Short
	u8"Dhuum", // KMT_Dhuum_Short
	u8"CA", // KMT_Ca_Short
	u8"Amalgamado conjurado", // KMT_Ca_Long
	u8"Gemelos", // KMT_Twins_Short
	u8"Largos gemelos", // KMT_Twins_Long
	u8"Qadim", // KMT_Qadim_Short
	u8"Sabir", // KMT_Sabir_Short
	u8"Adina", // KMT_Adina_Short
	u8"Qadim2", // KMT_Qadim2_Short
	u8"Qadim el Simpar", // KMT_Qadim2_Long
	u8"Greer", // KMT_Greer_Short,
	u8"Greer CM", // KMT_GreerCM_Short,
	u8"Greer, el Portarruina",
	u8"Greer, el Portarruina CM",
	u8"Decima", // KMT_Decima_Short,
	u8"Decima CM", // KMT_DecimaCM_Short,
	u8"Decima, la Invocatormentas", // KMT_Decima_Long,
	u8"Decima, la Invocatormentas CM", // KMT_DecimaCM_Long,
	u8"Ura", // KMT_Ura_Short,
	u8"Ura CM", // KMT_UraCM_Short,
	u8"Vial", // KMT_BoneskinnerVial_Short
	u8"Vial del ritual del pelahuesos", // KMT_BoneskinnerVial_Long
	u8"Ankka", // KMT_Ankka_Short
	u8"Chatarreria de Xunlay Jade (Ankka)", // KMT_Ankka_Long
	u8"KO", // KMT_MinisterLi_Short
	u8"Mirador de Kaineng (Ministro Li)", // KMT_MinisterLi_Long
	u8"Templo de la Cosecha", // KMT_Harvest_Short
	u8"Templo de la Cosecha", // KMT_Harvest_Long
	u8"Mai", // KMT_MaiTrin_Short
	u8"Escondite Filoetéreo (Mai Trin)", // KMT_MaiTrin_Long
	u8"Mai CM", // KMT_MaiTrinCM_Short
	u8"Escondite Filoetéreo (Mai Trin) CM", // KMT_MaiTrinCM_Long
	u8"Ankka CM", // KMT_AnkkaCM_Short
	u8"Chatarreria de Xunlay Jade (Ankka) CM", // KMT_AnkkaCM_Long
	u8"KO CM", // KMT_MinisterLiCM_Short
	u8"Mirador de Kaineng (Ministro Li) CM", // KMT_MinisterLiCM_Long
	u8"Templo de la Cosecha CM", // KMT_HarvestCM_Short
	u8"Templo de la Cosecha CM", // KMT_HarvestCM_Long
	u8"OLC", // KMT_OLC_Short
	u8"Vieja Corte del León (caballeras de asalto)", //KMT_OLC_Long
	u8"OLC CM", // KMT_OLCCM_Short
	u8"Vieja Corte del León CM (caballeras de asalto)", // KMT_OLCCM_Long,
	u8"CO", // KMT_CO_Short,
	u8"Observatorio Cósmico (Dagda)", // KMT_CO_Long,
	u8"CO CM", // KMT_COCM_Short,
	u8"Observatorio Cósmico (Dagda) CM", // KMT_COCM_Long,
	u8"Febe", // KMT_FEBE_Short,
	u8"Templo de Febe (Cerus)", // KMT_FEBE_Long,
	u8"Febe CM", // KMT_FEBECM_Short,
	u8"Templo de Febe (Cerus) CM", // KMT_FEBECM_Long,
	u8"Plátanos", // KMT_Bananas
	u8"Killproof.me", // KMT_KpWindowNameDefault
	u8"Killproof.me", // KMT_AppearAsInOptionDefault
	u8"Cuentas privadas", // KMT_SettingsShowPrivateText
	u8"Mostrar controles", // KMT_SettingsShowControls
	u8"Mostrar las cuentas vinculadas por defecto", // KMT_SettingsShowLinkedByDefault
	u8"Mostrar etiqueta de comandante", // KMT_SettingsShowCommander
	u8"Texto a mostrar cuando los datos no están disponibles/privados", // KMT_SettingsBlockedText
	u8"Mostrar directamente los totales vinculados", // KMT_ShowLinkedTotals
	u8"El plugin de extras no oficiales no está instalado.\nInstálalo para permitir el seguimiento de los jugadores en otras instancias.", // KMT_UnofficialExtrasNotInstalled
	u8"Nombre de la cuenta, ID de killproof.me o nombre del personaje para buscar y añadir a la lista", // KMT_AddPlayerTooltip
	u8"Añadir", // KMT_AddPlayerText
	u8"Borrar", // KMT_ClearText
	u8"Eliminar todos los usuarios añadidos manualmente", // KMT_ClearTooltip
	u8"Copiar el propio KP ID", // KMT_CopyKpIdText
	u8"En general", // KMT_Overall
	u8"Killproofs", // KMT_Killproofs
	u8"Cofres", // KMT_Coffers
	u8"NO cerrar la ventana de killproof.me con ESC", // KMT_SettingsDisableESCText
	u8"Killproofs por cofre", // KMT_SettingsCofferValue
	u8"Ocultar el mensaje de los extras no oficiales", // KMT_SettingsHideExtrasMessage
	u8"Borrar caché", // KMT_SettingsClearCacheText
	u8"Borrar la caché y recargar los datos de killproof.me para todos los jugadores", // KMT_SettingsClearCacheTooltip
	u8"Sólo funciona si se instalan los Extras no oficiales. Volverá a funcionar en inglés.", // KMT_LanguageAsIngameTooltip
	u8"Traducción aproximada al alemán, por favor informe de cualquier traducción errónea.", // KMT_LanguageGermanTooltip
	u8"Traducido con deepl.com. Por favor, informe de cualquier traducción incorrecta.", // KMT_LanguageFrenchTooltip
	u8"Traducido con deepl.com. Por favor, informe de cualquier traducción incorrecta.", // KMT_LanguageSpanishTooltip
	u8"Incursión", // KMT_Raids
	u8"Fractales", // KMT_Fractals
	u8"Misión de ataque", // KMT_Strikes
	u8"Varios", // KMT_Misc
});

static_assert(KILLPROOF_ME_TRANSLATION_ENGLISH.size() == magic_enum::enum_count<KillproofMeTranslations>());
static_assert(KILLPROOF_ME_TRANSLATION_ENGLISH.size() == KILLPROOF_ME_TRANSLATION_GERMAN.size());
static_assert(KILLPROOF_ME_TRANSLATION_ENGLISH.size() == KILLPROOF_ME_TRANSLATION_FRENCH.size());
static_assert(KILLPROOF_ME_TRANSLATION_ENGLISH.size() == KILLPROOF_ME_TRANSLATION_SPANISH.size());

inline void LoadAdditionalTranslations() {
	ArcdpsExtension::Localization& localization = ArcdpsExtension::Localization::instance();
	localization.Load(GWL_ENG, KILLPROOF_ME_TRANSLATION_ENGLISH);
	localization.Load(GWL_GEM, KILLPROOF_ME_TRANSLATION_GERMAN);
	localization.Load(GWL_FRE, KILLPROOF_ME_TRANSLATION_FRENCH);
	localization.Load(GWL_SPA, KILLPROOF_ME_TRANSLATION_SPANISH);
}
