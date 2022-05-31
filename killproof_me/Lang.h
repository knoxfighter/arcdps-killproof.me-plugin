#pragma once

#include "extension/arcdps_structs.h"

#include <magic_enum.hpp>

#include "extension/ExtensionTranslations.h"
#include "extension/Localization.h"

constexpr auto enumMax = magic_enum::detail::max_v<ExtensionTranslation>;
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
};

constexpr std::array KILLPROOF_ME_TRANSLATION_ENGLISH = std::to_array({
	"Account", // KMT_AccountName
	"Character", // KMT_CharacterName
	"ID", // KMT_KillproofId
	"Group", // KMT_SubgroupText
	"LI", // KMT_Li_Short
	"LD", // KMT_Ld_Short
	"LI+LD", // KMT_LiLd_Short
	"UCE", // KMT_Uce_Short
	"UFE", // KMT_Ufe_Short
	"VG", // KMT_Vg_Short
	"Vale Guardian", // KMT_Vg_Long
	"Gorse", // KMT_Gorse_Short
	"Gorseval the Multifarious", // KMT_Gorse_Long
	"Sabetha", // KMT_Sabetha_Short
	"Sabetha the Saboteur", // KMT_Sabetha_Long
	"Sloth", // KMT_Sloth_Short
	"Matthias", // KMT_Matthias_Short
	"Matthias Gabrel", // KMT_Matthias_Long
	"Escort", // KMT_Escort_Short
	"KC", // KMT_Kc_Short
	"Keep Construct", // KMT_Kc_Long
	"Xera", // KMT_Xera_Short
	"Cairn", // KMT_Cairn_Short
	"Cairn the Indomitable", // KMT_Cairn_Long
	"MO", // KMT_Mo_Short
	"Mursaat Overseer", // KMT_Mo_Long
	"Samarog", // KMT_Samarog_Short
	"Deimos", // KMT_Deimos_Short
	"Desmina", // KMT_Desmina_Short
	"Soulless Horror (Desmina)", // KMT_Desmina_Long
	"River", // KMT_River_Short
	"River of Souls", // KMT_River_Long
	"Statues", // KMT_Statues_Short
	"Dhuum", // KMT_Dhuum_Short
	"CA", // KMT_Ca_Short
	"Conjured Amalgamate", // KMT_Ca_Long
	"Twins", // KMT_Twins_Short
	"Twin Largos", // KMT_Twins_Long
	"Qadim", // KMT_Qadim_Short
	"Sabir", // KMT_Sabir_Short
	"Adina", // KMT_Adina_Short
	"Qadim2", // KMT_Qadim2_Short
	"Qadim the Peerless", // KMT_Qadim2_Long
	"Vial", // KMT_BoneskinnerVial_Short
	"Boneskinner Ritual Vial", // KMT_BoneskinnerVial_Long
	"Ankka", // KMT_Ankka_Short
	"Xunlai Jade Junkyard (Ankka)", // KMT_Ankka_Long
	"KO", // KMT_MinisterLi_Short
	"Kaineng Overlook (Minister Li)", // KMT_MinisterLi_Long
	"Harvest Temple", // KMT_Harvest_Short
	"Harvest Temple (Dragonvoid)", // KMT_Harvest_Long
	"Mai", // KMT_MaiTrin_Short
	"Aetherblade Hideout (Mai Trin)", // KMT_MaiTrin_Long
	"Mai CM", // KMT_MaiTrinCM_Short
	"Aetherblade Hideout (Mai Trin) CM", // KMT_MaiTrinCM_Long
	"Ankka CM", // KMT_AnkkaCM_Short
	"Xunlai Jade Junkyard (Ankka) CM", // KMT_AnkkaCM_Long
	"KO CM", // KMT_MinisterLiCM_Short
	"Kaineng Overlook (Minister Li) CM", // KMT_MinisterLiCM_Long
	"Killproof.me", // KMT_KpWindowNameDefault
	"Killproof.me", // KMT_AppearAsInOptionDefault
	"Private accounts", // KMT_SettingsShowPrivateText
	"Show controls", // KMT_SettingsShowControls
	"Show linked accounts by default", // KMT_SettingsShowLinkedByDefault
	"Show Commander Tag", // KMT_SettingsShowCommander
	"Text to display when data is unavailable/private", // KMT_SettingsBlockedText
	"Show linked totals directly", // KMT_ShowLinkedTotals
	"Unofficial extras plugin is not installed.\nInstall it to enable tracking of players on other instances.", // KMT_UnofficialExtrasNotInstalled
	"Accountname, killproof.me ID or Charactername to search and add to the list", // KMT_AddPlayerTooltip
	"Add", // KMT_AddPlayerText
	"Clear", // KMT_ClearText
	"Remove all manually added users", // KMT_ClearTooltip
	"Copy own KP ID", // KMT_CopyKpIdText
	"Overall", // KMT_Overall
	"Killproofs", // KMT_Killproofs
	"Coffers", // KMT_Coffers
	"Do NOT close killproof.me window on ESC", // KMT_SettingsDisableESCText
	"Killproofs per coffer", // KMT_SettingsCofferValue
	"Hide Unofficial Extras Message", // KMT_SettingsHideExtrasMessage
	"Clear Cache", // KMT_SettingsClearCacheText
	"Clear the cache and reload killproof.me data for all players", // KMT_SettingsClearCacheTooltip
	"Only works if Unofficial Extras is installed. Will fall back to English.", // KMT_LanguageAsIngameTooltip
	"Rough German translation, please report any wrong translations.", // KMT_LanguageGermanTooltip
	"Translated with deepl.com. Please report any wrong translations.", // KMT_LanguageFrenchTooltip
	"Translated with deepl.com. Please report any wrong translations.", // KMT_LanguageSpanishTooltip
	"Raids", // KMT_Raids
	"Fractals", // KMT_Fractals
	"Strikes", // KMT_Strikes
});

constexpr std::array KILLPROOF_ME_TRANSLATION_GERMAN = std::to_array({
	"Account", // KMT_AccountName
	"Charakter", // KMT_CharacterName
	"ID", // KMT_KillproofId
	"Gruppe", // KMT_SubgroupText
	"LI", // KMT_Li_Short
	"LD", // KMT_Ld_Short
	"LI+LD", // KMT_LiLd_Short
	"UCE", // KMT_Uce_Short
	"UFE", // KMT_Ufe_Short
	"VG", // KMT_Vg_Short
	"Talwächter", // KMT_Vg_Long
	"Gorse", // KMT_Gorse_Short
	"Gorseval der Facettenreiche", // KMT_Gorse_Long
	"Sabetha", // KMT_Sabetha_Short
	"Sabetha die Saboteurin", // KMT_Sabetha_Long
	"Faulterion", // KMT_Sloth_Short
	"Matthias", // KMT_Matthias_Short
	"Matthias Gabrel", // KMT_Matthias_Long
	"Escort", // KMT_Escort_Short
	"KC", // KMT_Kc_Short
	"Festenkonstrukt", // KMT_Kc_Long
	"Xera", // KMT_Xera_Short
	"Cairn", // KMT_Cairn_Short
	"Cairn der Unbeugsame", // KMT_Cairn_Long
	"MO", // KMT_Mo_Short
	"Mursaat-Aufseher", // KMT_Mo_Long
	"Samarog", // KMT_Samarog_Short
	"Deimos", // KMT_Deimos_Short
	"Desmina", // KMT_Desmina_Short
	"Seelenloser Schrecken (Desmina)", // KMT_Desmina_Long
	"River", // KMT_River_Short
	"Fluss der Seelen", // KMT_River_Long
	"Statues", // KMT_Statues_Short
	"Dhuum", // KMT_Dhuum_Short
	"CA", // KMT_Ca_Short
	"Beschworene Verschmelzung", // KMT_Ca_Long
	"Twins", // KMT_Twins_Short
	"Largos-Assassinen", // KMT_Twins_Long
	"Qadim", // KMT_Qadim_Short
	"Sabir", // KMT_Sabir_Short
	"Adina", // KMT_Adina_Short
	"Qadim2", // KMT_Qadim2_Short
	"Qadim der Unvergleichliche", // KMT_Qadim2_Long
	"Phiole", // KMT_BoneskinnerVial_Short
	"Knochenhäuter-Ritual-Phiole", // KMT_BoneskinnerVial_Long
	"Ankka", // KMT_Ankka_Short
	"Xunlai-Jade-Schrottplatz (Ankka)", // KMT_Ankka_Long
	"KO", // KMT_MinisterLi_Short
	"Kaineng-Aussichtspunkt (Minister Li)", // KMT_MinisterLi_Short
	"Erntetempel", // KMT_Harvest_Short
	"Erntetempel (Drachenleere)", // KMT_Harvest_Long
	"Mai", // KMT_MaiTrin_Short
	"Ätherklinger-Unterschlupf (Mai Trin)", // KMT_MaiTrin_Long
	"Mai CM", // KMT_MaiTrinCM_Short
	"Ätherklinger-Unterschlupf (Mai Trin) CM", // KMT_MaiTrinCM_Long
	"Ankka CM", // KMT_AnkkaCM_Short
	"Xunlai-Jade-Schrottplatz (Ankka) CM", // KMT_AnkkaCM_Long
	"KO CM", // KMT_MinisterLiCM_Short
	"Kaineng-Aussichtspunkt (Minsiter Li) CM", // KMT_MinisterLiCM_Long
	"Killproof.me", // KMT_KpWindowNameDefault
	"Killproof.me", // KMT_AppearAsInOptionDefault
	"Private Accounts", // KMT_SettingsShowPrivateText
	"Zeige Bedienelemente", // KMT_SettingsShowControls
	"Zeige verknüpfte Account Standardmäßig", // KMT_SettingsShowLinkedByDefault
	"Zeige Kommandeurssymbol", // KMT_SettingsShowCommander
	"Anzeigetext, wenn Daten nicht verfügbar/privat sind", // KMT_SettingsBlockedText
	"Zeige verknüpfte Gesamtwerte direkt", // KMT_ShowLinkedTotals
	"Das \"Unofficial extras plugin\" ist nicht installiert.\nInstalliere es, um Spiler auf anderen Instanzen sehen zu können.", // KMT_UnofficialExtrasNotInstalled
	"Suche nach Accountname, killproof.me ID oder Charaktername und füge es der Tabelle hinzu", // KMT_AddPlayerTooltip
	"Hinzufügen", // KMT_AddPlayerText
	"Löschen", // KMT_ClearText
	"Entferne alle manuell hinzugefügten Einträge", // KMT_ClearTooltip
	"Kopiere die eigene ID", // KMT_CopyKpIdText
	"Gesamt", // KMT_Overall
	"Killproofs", // KMT_Killproofs
	"Koffer", // KMT_Coffers
	"Schließe das killproof.me Fenster NICHT mit ESC", // KMT_SettingsDisableESCText
	"Killproofs pro Koffer", // KMT_SettingsCofferValue
	"Verstecke die \"Unofficial Extras\" Fehlernachricht", // KMT_SettingsHideExtrasMessage
	"Lösche Cache", // KMT_SettingsClearCacheText
	"Lösche den Cache und lade alle Spieler neu", // KMT_SettingsClearCacheTooltip
	"Funktioniert nur, wenn das \"Unofficial Extras Addon\" installiert ist. Falls nicht, wird Englisch verwendet.", // KMT_LanguageAsIngameTooltip
	"Grobe Deutsche Übersetzung. Bitte melde alle falschen/schlechten Übersetzungen.", // KMT_LanguageGermanTooltip
	"Übersetzt mit deepl.com. Bitte melde alle falschen/schlechten Übersetzungen.", // KMT_LanguageFrenchTooltip
	"Übersetzt mit deepl.com. Bitte melde alle falschen/schlechten Übersetzungen.", // KMT_LanguageSpanishTooltip
	"Schlachtzüge", // KMT_Raids
	"Fraktale", // KMT_Fractals
	"Angriffsmissionen", // KMT_Strikes
});

constexpr std::array KILLPROOF_ME_TRANSLATION_FRENCH = std::to_array({
	"Compte", // KMT_AccountName
	"Caractère", // KMT_CharacterName
	"ID", // KMT_KillproofId
	"Groupe", // KMT_SubgroupText
	"LI", // KMT_Li_Short
	"LD", // KMT_Ld_Short
	"LI+LD", // KMT_LiLd_Short
	"UCE", // KMT_Uce_Short
	"UFE", // KMT_Ufe_Short
	"VG", // KMT_Vg_Short
	"Gardien de la Vallée", // KMT_Vg_Long
	"Gorse", // KMT_Gorse_Short
	"Gorseval le Disparate", // KMT_Gorse_Long
	"Sabetha", // KMT_Sabetha_Short
	"Sabetha la saboteuse", // KMT_Sabetha_Long
	"Paressor", // KMT_Sloth_Short
	"Matthias", // KMT_Matthias_Short
	"Matthias Gabrel", // KMT_Matthias_Long
	"Escorte", // KMT_Escort_Short
	"KC", // KMT_Kc_Short
	"Titan du fort", // KMT_Kc_Long
	"Xera", // KMT_Xera_Short
	"Cairn", // KMT_Cairn_Short
	"Cairn l'Indomptable", // KMT_Cairn_Long
	"MO", // KMT_Mo_Short
	"Surveillant mursaat", // KMT_Mo_Long
	"Samarog", // KMT_Samarog_Short
	"Deimos", // KMT_Deimos_Short
	"Desmina", // KMT_Desmina_Short
	"Horreur sans âme (Desmina)", // KMT_Desmina_Long
	"Rivière", // KMT_River_Short
	"Rivière des âmes", // KMT_River_Long
	"Statues", // KMT_Statues_Short
	"Dhuum", // KMT_Dhuum_Short
	"CA", // KMT_Ca_Short
	"Amalgame conjuré", // KMT_Ca_Long
	"Jumeaux", // KMT_Twins_Short
	"Jumeaux Largos", // KMT_Twins_Long
	"Qadim", // KMT_Qadim_Short
	"Sabir", // KMT_Sabir_Short
	"Adina", // KMT_Adina_Short
	"Qadim2", // KMT_Qadim2_Short
	"Qadim l'incomparable", // KMT_Qadim2_Long
	"Fiole", // KMT_BoneskinnerVial_Short
	"Fiole du rituel du désosseur", // KMT_BoneskinnerVial_Long
	"Ankka", // KMT_Ankka_Short
	"Décharge de Xunlai Jade (Ankka)", // KMT_Ankka_Long
	"KO", // KMT_MinisterLi_Short
	"Belvédère de Kaineng (Ministère  Li)", // KMT_MinisterLi_Long
	"Temple des moissons", // KMT_Harvest_Short
	"Temple des moissons (Dragonvoid)", // KMT_Harvest_Short
	"Mai", // KMT_MaiTrin_Short
	"Cachette des Étherlames (Mai Trin)", // KMT_MaiTrin_Long
	"Mai CM", // KMT_MaiTrinCM_Short
	"Cachette des Étherlames (Mai Trin) CM", // KMT_MaiTrinCM_Long
	"Ankka CM", // KMT_AnkkaCM_Short
	"Décharge de Xunlai Jade (Ankka) CM", // KMT_AnkkaCM_Long
	"KO CM", // KMT_MinisterLiCM_Short
	"Belvédère de Kaineng (Ministère Li) CM", // KMT_MinisterLiCM_Long
	"Killproof.me", // KMT_KpWindowNameDefault
	"Killproof.me", // KMT_AppearAsInOptionDefault
	"Comptes privés", // KMT_SettingsShowPrivateText
	"Afficher les contrôles", // KMT_SettingsShowControls
	"Afficher les comptes liés par défaut", // KMT_SettingsShowLinkedByDefault
	"Afficher le commandant Tag", // KMT_SettingsShowCommander
	"Texte à afficher lorsque les données sont indisponibles/privées", // KMT_SettingsBlockedText
	"Afficher directement les totaux liés", // KMT_ShowLinkedTotals
	"Le plugin d'extras non officiels n'est pas installé.\nInstallez-le pour permettre le suivi des joueurs sur d'autres instances.", // KMT_UnofficialExtrasNotInstalled
	"Nom de compte, ID de killproof.me ou Nom de personnage pour rechercher et ajouter à la liste", // KMT_AddPlayerTooltip
	"Ajouter", // KMT_AddPlayerText
	"Clair", // KMT_ClearText
	"Supprimer tous les utilisateurs ajoutés manuellement", // KMT_ClearTooltip
	"Copie de votre propre KP ID", // KMT_CopyKpIdText
	"En général", // KMT_Overall
	"Killproofs", // KMT_Killproofs
	"Coffres", // KMT_Coffers
	"Ne PAS fermer la fenêtre killproof.me en appuyant sur ESC.", // KMT_SettingsDisableESCText
	"Killproofs par caisson", // KMT_SettingsCofferValue
	"Cacher le message des extras non officiels", // KMT_SettingsHideExtrasMessage
	"Effacer le cache", // KMT_SettingsClearCacheText
	"Videz le cache et rechargez les données de killproof.me pour tous les joueurs.", // KMT_SettingsClearCacheTooltip
	"Ne fonctionne que si Unofficial Extras est installé. Retour à l'anglais.", // KMT_LanguageAsIngameTooltip
	"Traduction allemande approximative, veuillez signaler toute traduction erronée.", // KMT_LanguageGermanTooltip
	"Traduit avec deepl.com. Veuillez signaler toute traduction erronée.", // KMT_LanguageFrenchTooltip
	"Traduit avec deepl.com. Veuillez signaler toute traduction erronée.", // KMT_LanguageSpanishTooltip
	"Raids", // KMT_Raids
	"Fractals", // KMT_Fractals
	"Mission d'attaque", // KMT_Strikes
});

constexpr std::array KILLPROOF_ME_TRANSLATION_SPANISH = std::to_array({
	"Cuenta", // KMT_AccountName
	"Carácter", // KMT_CharacterName
	"ID", // KMT_KillproofId
	"Grupo", // KMT_SubgroupText
	"LI", // KMT_Li_Short
	"LD", // KMT_Ld_Short
	"LI+LD", // KMT_LiLd_Short
	"UCE", // KMT_Uce_Short
	"UFE", // KMT_Ufe_Short
	"VG", // KMT_Vg_Short
	"Guardián del valle", // KMT_Vg_Long
	"Gorse", // KMT_Gorse_Short
	"Gorseval el Múltiple", // KMT_Gorse_Long
	"Sabetha", // KMT_Sabetha_Short
	"Sabetha la Saboteadora", // KMT_Sabetha_Long
	"Perezón", // KMT_Sloth_Short
	"Matías", // KMT_Matthias_Short
	"Matías Gabrel", // KMT_Matthias_Long
	"Escolta", // KMT_Escort_Short
	"KC", // KMT_Kc_Short
	"Ensamblaje de la Fortaleza", // KMT_Kc_Long
	"Xera", // KMT_Xera_Short
	"Cairn", // KMT_Cairn_Short
	"Cairn el Indomable", // KMT_Cairn_Long
	"MO", // KMT_Mo_Short
	"Dirigente mursaat", // KMT_Mo_Long
	"Samarog", // KMT_Samarog_Short
	"Deimos", // KMT_Deimos_Short
	"Desmina", // KMT_Desmina_Short
	"Horror sin alma", // KMT_Desmina_Long
	"Río", // KMT_River_Short
	"Río de Almas", // KMT_River_Long
	"Estatuas", // KMT_Statues_Short
	"Dhuum", // KMT_Dhuum_Short
	"CA", // KMT_Ca_Short
	"Amalgamado conjurado", // KMT_Ca_Long
	"Gemelos", // KMT_Twins_Short
	"Largos gemelos", // KMT_Twins_Long
	"Qadim", // KMT_Qadim_Short
	"Sabir", // KMT_Sabir_Short
	"Adina", // KMT_Adina_Short
	"Qadim2", // KMT_Qadim2_Short
	"Qadim el Simpar", // KMT_Qadim2_Long
	"Vial", // KMT_BoneskinnerVial_Short
	"Vial del ritual del pelahuesos", // KMT_BoneskinnerVial_Long
	"Ankka", // KMT_Ankka_Short
	"Chatarreria de Xunlay Jade (Ankka)", // KMT_Ankka_Long
	"KO", // KMT_MinisterLi_Short
	"Mirador de Kaineng (Ministro Li)", // KMT_MinisterLi_Long
	"Templo de la Cosecha", // KMT_Harvest_Short
	"Templo de la Cosecha", // KMT_Harvest_Long
	"Mai", // KMT_MaiTrin_Short
	"Escondite Filoetéreo (Mai Trin)", // KMT_MaiTrin_Long
	"Mai CM", // KMT_MaiTrinCM_Short
	"Escondite Filoetéreo (Mai Trin) CM", // KMT_MaiTrinCM_Long
	"Ankka CM", // KMT_AnkkaCM_Short
	"Chatarreria de Xunlay Jade (Ankka) CM", // KMT_AnkkaCM_Long
	"KO CM", // KMT_MinisterLiCM_Short
	"Mirador de Kaineng (Ministro Li) CM", // KMT_MinisterLiCM_Long
	"Killproof.me", // KMT_KpWindowNameDefault
	"Killproof.me", // KMT_AppearAsInOptionDefault
	"Cuentas privadas", // KMT_SettingsShowPrivateText
	"Mostrar controles", // KMT_SettingsShowControls
	"Mostrar las cuentas vinculadas por defecto", // KMT_SettingsShowLinkedByDefault
	"Mostrar etiqueta de comandante", // KMT_SettingsShowCommander
	"Texto a mostrar cuando los datos no están disponibles/privados", // KMT_SettingsBlockedText
	"Mostrar directamente los totales vinculados", // KMT_ShowLinkedTotals
	"El plugin de extras no oficiales no está instalado.\nInstálalo para permitir el seguimiento de los jugadores en otras instancias.", // KMT_UnofficialExtrasNotInstalled
	"Nombre de la cuenta, ID de killproof.me o nombre del personaje para buscar y añadir a la lista", // KMT_AddPlayerTooltip
	"Añadir", // KMT_AddPlayerText
	"Borrar", // KMT_ClearText
	"Eliminar todos los usuarios añadidos manualmente", // KMT_ClearTooltip
	"Copiar el propio KP ID", // KMT_CopyKpIdText
	"En general", // KMT_Overall
	"Killproofs", // KMT_Killproofs
	"Cofres", // KMT_Coffers
	"NO cerrar la ventana de killproof.me con ESC", // KMT_SettingsDisableESCText
	"Killproofs por cofre", // KMT_SettingsCofferValue
	"Ocultar el mensaje de los extras no oficiales", // KMT_SettingsHideExtrasMessage
	"Borrar caché", // KMT_SettingsClearCacheText
	"Borrar la caché y recargar los datos de killproof.me para todos los jugadores", // KMT_SettingsClearCacheTooltip
	"Sólo funciona si se instalan los Extras no oficiales. Volverá a funcionar en inglés.", // KMT_LanguageAsIngameTooltip
	"Traducción aproximada al alemán, por favor informe de cualquier traducción errónea.", // KMT_LanguageGermanTooltip
	"Traducido con deepl.com. Por favor, informe de cualquier traducción incorrecta.", // KMT_LanguageFrenchTooltip
	"Traducido con deepl.com. Por favor, informe de cualquier traducción incorrecta.", // KMT_LanguageSpanishTooltip
	"Incursión", // KMT_Raids
	"Fractales", // KMT_Fractals
	"Misión de ataque", // KMT_Strikes
});

static_assert(KILLPROOF_ME_TRANSLATION_ENGLISH.size() == magic_enum::enum_count<KillproofMeTranslations>());
static_assert(KILLPROOF_ME_TRANSLATION_ENGLISH.size() == KILLPROOF_ME_TRANSLATION_GERMAN.size());
static_assert(KILLPROOF_ME_TRANSLATION_ENGLISH.size() == KILLPROOF_ME_TRANSLATION_FRENCH.size());
static_assert(KILLPROOF_ME_TRANSLATION_ENGLISH.size() == KILLPROOF_ME_TRANSLATION_SPANISH.size());

inline void LoadAdditionalTranslations() {
	Localization& localization = Localization::instance();
	localization.Load(GWL_ENG, KILLPROOF_ME_TRANSLATION_ENGLISH);
	localization.Load(GWL_GEM, KILLPROOF_ME_TRANSLATION_GERMAN);
	localization.Load(GWL_FRE, KILLPROOF_ME_TRANSLATION_FRENCH);
	localization.Load(GWL_SPA, KILLPROOF_ME_TRANSLATION_SPANISH);
}
