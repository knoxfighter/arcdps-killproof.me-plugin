#include "Lang.h"

#include <modernIni/modernIni.h>
// marked as unused, but actually needed ...
#include <magic_enum/magic_enum_format.hpp>

namespace
{
	constexpr std::array KILLPROOF_ME_TRANSLATION_ENGLISH = std::to_array<std::pair<KillproofMeTranslations, const char*>>({
		{KMT_AccountName, "Account"},
		{KMT_CharacterName, "Character"},
		{KMT_KillproofId, "ID"},
		{KMT_SubgroupText, "Group"},
		{KMT_Li_Short, "LI"},
		{KMT_Ld_Short, "LD"},
		{KMT_LiLd_Short, "LI+LD"},
		{KMT_Uce_Short, "UCE"},
		{KMT_Ufe_Short, "UFE"},
		{KMT_Vg_Short, "VG"},
		{KMT_Vg_Long, "Vale Guardian"},
		{KMT_Gorse_Short, "Gorse"},
		{KMT_Gorse_Long, "Gorseval the Multifarious"},
		{KMT_Sabetha_Short, "Sabetha"},
		{KMT_Sabetha_Long, "Sabetha the Saboteur"},
		{KMT_Sloth_Short, "Sloth"},
		{KMT_Matthias_Short, "Matthias"},
		{KMT_Matthias_Long, "Matthias Gabrel"},
		{KMT_Escort_Short, "Escort"},
		{KMT_Kc_Short, "KC"},
		{KMT_Kc_Long, "Keep Construct"},
		{KMT_Xera_Short, "Xera"},
		{KMT_Cairn_Short, "Cairn"},
		{KMT_Cairn_Long, "Cairn the Indomitable"},
		{KMT_Mo_Short, "MO"},
		{KMT_Mo_Long, "Mursaat Overseer"},
		{KMT_Samarog_Short, "Samarog"},
		{KMT_Deimos_Short, "Deimos"},
		{KMT_Desmina_Short, "Desmina"},
		{KMT_Desmina_Long, "Soulless Horror (Desmina)"},
		{KMT_River_Short, "River"},
		{KMT_River_Long, "River of Souls"},
		{KMT_Statues_Short, "Statues"},
		{KMT_Dhuum_Short, "Dhuum"},
		{KMT_Ca_Short, "CA"},
		{KMT_Ca_Long, "Conjured Amalgamate"},
		{KMT_Twins_Short, "Twins"},
		{KMT_Twins_Long, "Twin Largos"},
		{KMT_Qadim_Short, "Qadim"},
		{KMT_Sabir_Short, "Sabir"},
		{KMT_Adina_Short, "Adina"},
		{KMT_Qadim2_Short, "Qadim2"},
		{KMT_Qadim2_Long, "Qadim the Peerless"},
		{KMT_Greer_Short, "Greer"},
		{KMT_GreerCM_Short, "Greer CM"},
		{KMT_Greer_Long, "Greer, the Blightbringer"},
		{KMT_GreerCM_Long, "Greer, the Blightbringer CM"},
		{KMT_Decima_Short, "Decima"},
		{KMT_DecimaCM_Short, "Decima CM"},
		{KMT_Decima_Long, "Decima, the Stormsinger"},
		{KMT_DecimaCM_Long, "Decima, the Stormsinger CM"},
		{KMT_Ura_Short, "Ura"},
		{KMT_UraCM_Short, "Ura CM"},
		{KMT_BoneskinnerVial_Short, "Vial"},
		{KMT_BoneskinnerVial_Long, "Boneskinner Ritual Vial"},
		{KMT_Ankka_Short, "Ankka"},
		{KMT_Ankka_Long, "Xunlai Jade Junkyard (Ankka)"},
		{KMT_MinisterLi_Short, "KO"},
		{KMT_MinisterLi_Long, "Kaineng Overlook (Minister Li)"},
		{KMT_Harvest_Short, "HT"},
		{KMT_Harvest_Long, "Harvest Temple (Dragonvoid)"},
		{KMT_MaiTrin_Short, "Mai"},
		{KMT_MaiTrin_Long, "Aetherblade Hideout (Mai Trin)"},
		{KMT_MaiTrinCM_Short, "Mai CM"},
		{KMT_MaiTrinCM_Long, "Aetherblade Hideout (Mai Trin) CM"},
		{KMT_AnkkaCM_Short, "Ankka CM"},
		{KMT_AnkkaCM_Long, "Xunlai Jade Junkyard (Ankka) CM"},
		{KMT_MinisterLiCM_Short, "KO CM"},
		{KMT_MinisterLiCM_Long, "Kaineng Overlook (Minister Li) CM"},
		{KMT_HarvestCM_Short, "HT CM"},
		{KMT_HarvestCM_Long, "Harvest Temple (Dragonvoid) CM"},
		{KMT_OLC_Short, "OLC"},
		{KMT_OLC_Long, "Old Lion's Court (Assault Knights)"},
		{KMT_OLCCM_Short, "OLC CM"},
		{KMT_OLCCM_Long, "Old Lion's Court CM (Assault Knights)"},
		{KMT_CO_Short, "CO"},
		{KMT_CO_Long, "Cosmic Observatory (Dagda)"},
		{KMT_COCM_Short, "CO CM"},
		{KMT_COCM_Long, "Cosmic Observatory (Dagda) CM"},
		{KMT_FEBE_Short, "Febe"},
		{KMT_FEBE_Long, "Temple of Febe (Cerus)"},
		{KMT_FEBECM_Short, "Febe CM"},
		{KMT_FEBECM_Long, "Temple of Febe (Cerus) CM"},
		{KMT_Kela_Short, "Kela"},
		{KMT_Kela_Long, "Kela, Seneschal of Waves"},
		{KMT_KelaCM_Short, "Kela CM"},
		{KMT_KelaCM_Long, "Kela, Seneschal of Waves CM"},
		{KMT_Bananas, "Bananas"},
		{KMT_KpWindowNameDefault, "Killproof.me"},
		{KMT_AppearAsInOptionDefault, "Killproof.me"},
		{KMT_SettingsShowPrivateText, "Private accounts"},
		{KMT_SettingsShowControls, "Show controls"},
		{KMT_SettingsShowLinkedByDefault, "Show linked accounts by default"},
		{KMT_SettingsShowCommander, "Show Commander Tag"},
		{KMT_SettingsBlockedText, "Text to display when data is unavailable/private"},
		{KMT_ShowLinkedTotals, "Show linked totals directly"},
		{
			KMT_UnofficialExtrasNotInstalled,
			"Unofficial extras plugin is not installed.\nInstall it to enable tracking of players on other instances."
		},
		{KMT_AddPlayerTooltip, "Accountname, killproof.me ID or Charactername to search and add to the list"},
		{KMT_AddPlayerText, "Add"},
		{KMT_ClearText, "Clear"},
		{KMT_ClearTooltip, "Remove all manually added users"},
		{KMT_CopyKpIdText, "Copy own KP ID"},
		{KMT_Overall, "Overall"},
		{KMT_Killproofs, "Killproofs"},
		{KMT_Coffers, "Coffers"},
		{KMT_SettingsDisableESCText, "Do NOT close killproof.me window on ESC"},
		{KMT_SettingsCofferValue, "Killproofs per coffer"},
		{KMT_SettingsHideExtrasMessage, "Hide Unofficial Extras Message"},
		{KMT_SettingsClearCacheText, "Clear Cache"},
		{KMT_SettingsClearCacheTooltip, "Clear the cache and reload killproof.me data for all players"},
		{KMT_LanguageAsIngameTooltip, "Only works if Unofficial Extras is installed. Will fall back to English."},
		{KMT_Raids, "Raids"},
		{KMT_Fractals, "Fractals"},
		{KMT_Strikes, "Strikes"},
		{KMT_Misc, "Miscellaneous"},
		{KMT_MapBasedStrikes, "Show Strikes"},
		{KMT_UseCustomColumns, "Show Columns based on map"},
	});

	constexpr std::array KILLPROOF_ME_TRANSLATION_GERMAN = std::to_array<std::pair<KillproofMeTranslations, const char8_t*>>({
		{KMT_AccountName, u8"Account"},
		{KMT_CharacterName, u8"Charakter"},
		{KMT_KillproofId, u8"ID"},
		{KMT_SubgroupText, u8"Gruppe"},
		{KMT_Li_Short, u8"LI"},
		{KMT_Ld_Short, u8"LD"},
		{KMT_LiLd_Short, u8"LI+LD"},
		{KMT_Uce_Short, u8"UCE"},
		{KMT_Ufe_Short, u8"UFE"},
		{KMT_Vg_Short, u8"VG"},
		{KMT_Vg_Long, u8"Talwächter"},
		{KMT_Gorse_Short, u8"Gorse"},
		{KMT_Gorse_Long, u8"Gorseval der Facettenreiche"},
		{KMT_Sabetha_Short, u8"Sabetha"},
		{KMT_Sabetha_Long, u8"Sabetha die Saboteurin"},
		{KMT_Sloth_Short, u8"Faulterion"},
		{KMT_Matthias_Short, u8"Matthias"},
		{KMT_Matthias_Long, u8"Matthias Gabrel"},
		{KMT_Escort_Short, u8"Escort"},
		{KMT_Kc_Short, u8"KC"},
		{KMT_Kc_Long, u8"Festenkonstrukt"},
		{KMT_Xera_Short, u8"Xera"},
		{KMT_Cairn_Short, u8"Cairn"},
		{KMT_Cairn_Long, u8"Cairn der Unbeugsame"},
		{KMT_Mo_Short, u8"MO"},
		{KMT_Mo_Long, u8"Mursaat-Aufseher"},
		{KMT_Samarog_Short, u8"Samarog"},
		{KMT_Deimos_Short, u8"Deimos"},
		{KMT_Desmina_Short, u8"Desmina"},
		{KMT_Desmina_Long, u8"Seelenloser Schrecken (Desmina)"},
		{KMT_River_Short, u8"River"},
		{KMT_River_Long, u8"Fluss der Seelen"},
		{KMT_Statues_Short, u8"Statues"},
		{KMT_Dhuum_Short, u8"Dhuum"},
		{KMT_Ca_Short, u8"CA"},
		{KMT_Ca_Long, u8"Beschworene Verschmelzung"},
		{KMT_Twins_Short, u8"Twins"},
		{KMT_Twins_Long, u8"Largos-Assassinen"},
		{KMT_Qadim_Short, u8"Qadim"},
		{KMT_Sabir_Short, u8"Sabir"},
		{KMT_Adina_Short, u8"Adina"},
		{KMT_Qadim2_Short, u8"Qadim2"},
		{KMT_Qadim2_Long, u8"Qadim der Unvergleichliche"},
		{KMT_Greer_Short, u8"Greer"},
		{KMT_GreerCM_Short, u8"Greer CM"},
		{KMT_Greer_Long, u8"Greer, der Pestilenzbringer"},
		{KMT_GreerCM_Long, u8"Greer, der Pestilenzbringer CM"},
		{KMT_Decima_Short, u8"Decima"},
		{KMT_DecimaCM_Short, u8"Decima CM"},
		{KMT_Decima_Long, u8"Decima, die Sturmsängerin"},
		{KMT_DecimaCM_Long, u8"Decima, die Sturmsängerin CM"},
		{KMT_Ura_Short, u8"Ura"},
		{KMT_UraCM_Short, u8"Ura CM"},
		{KMT_BoneskinnerVial_Short, u8"Phiole"},
		{KMT_BoneskinnerVial_Long, u8"Knochenhäuter-Ritual-Phiole"},
		{KMT_Ankka_Short, u8"Ankka"},
		{KMT_Ankka_Long, u8"Xunlai-Jade-Schrottplatz (Ankka)"},
		{KMT_MinisterLi_Short, u8"KO"},
		{KMT_MinisterLi_Short, u8"Kaineng-Aussichtspunkt (Minister Li)"},
		{KMT_Harvest_Short, u8"Erntetempel"},
		{KMT_Harvest_Long, u8"Erntetempel (Drachenleere)"},
		{KMT_MaiTrin_Short, u8"Mai"},
		{KMT_MaiTrin_Long, u8"Ätherklinger-Unterschlupf (Mai Trin)"},
		{KMT_MaiTrinCM_Short, u8"Mai CM"},
		{KMT_MaiTrinCM_Long, u8"Ätherklinger-Unterschlupf (Mai Trin) CM"},
		{KMT_AnkkaCM_Short, u8"Ankka CM"},
		{KMT_AnkkaCM_Long, u8"Xunlai-Jade-Schrottplatz (Ankka) CM"},
		{KMT_MinisterLiCM_Short, u8"KO CM"},
		{KMT_MinisterLiCM_Long, u8"Kaineng-Aussichtspunkt (Minsiter Li) CM"},
		{KMT_HarvestCM_Short, u8"Erntetempel CM"},
		{KMT_HarvestCM_Long, u8"Erntetempel (Drachenleere) CM"},
		{KMT_OLC_Short, u8"OLC"},
		{KMT_OLC_Long, u8"Alter Löwenhof (Sturmritter)"},
		{KMT_OLCCM_Short, u8"OLC CM"},
		{KMT_OLCCM_Long, u8"Alter Löwenhof CM (Sturmritter)"},
		{KMT_CO_Short, u8"CO"},
		{KMT_CO_Long, u8"Kosmisches Observatorium (Dagda)"},
		{KMT_COCM_Short, u8"CO CM"},
		{KMT_COCM_Long, u8"Kosmisches Observatorium (Dagda) CM"},
		{KMT_FEBE_Short, u8"Febe"},
		{KMT_FEBE_Long, u8"Tempel von Febe (Cerus)"},
		{KMT_FEBECM_Short, u8"Febe CM"},
		{KMT_FEBECM_Long, u8"Tempel von Febe (Cerus) CM"},
		{KMT_Kela_Short, u8"Kela"},
		{KMT_Kela_Long, u8"Kela, Seneschall der Wogen"},
		{KMT_KelaCM_Short, u8"Kela CM"},
		{KMT_KelaCM_Long, u8"Kela, Seneschall der Wogen CM"},
		{KMT_Bananas, u8"Bananen"},
		{KMT_KpWindowNameDefault, u8"Killproof.me"},
		{KMT_AppearAsInOptionDefault, u8"Killproof.me"},
		{KMT_SettingsShowPrivateText, u8"Private Accounts anzeigen"},
		{KMT_SettingsShowControls, u8"Bedienelemente anzeigen"},
		{KMT_SettingsShowLinkedByDefault, u8"Verknüpfte Accounts anzeigen"},
		{KMT_SettingsShowCommander, u8"Kommandeursymbol anzeigen"},
		{KMT_SettingsBlockedText, u8"Anzeigetext, wenn Daten nicht verfügbar/privat sind"},
		{KMT_ShowLinkedTotals, u8"Zeige verknüpfte Gesamtwerte"},
		{
			KMT_UnofficialExtrasNotInstalled,
			u8"Das \"Unofficial extras plugin\" ist nicht installiert.\nInstalliere es, um Spieler in anderen Instanzen sehen zu können."
		},
		{KMT_AddPlayerTooltip, u8"Suche nach Accountnamen, killproof.me IDs oder Charakternamen um sie hinzuzufügen."},
		{KMT_AddPlayerText, u8"Hinzufügen"},
		{KMT_ClearText, u8"Löschen"},
		{KMT_ClearTooltip, u8"Entferne alle manuell hinzugefügten Einträge"},
		{KMT_CopyKpIdText, u8"Kopiere die eigene ID"},
		{KMT_Overall, u8"Gesamt"},
		{KMT_Killproofs, u8"Killproofs"},
		{KMT_Coffers, u8"Koffer"},
		{KMT_SettingsDisableESCText, u8"Schließe das killproof.me Fenster NICHT mit ESC"},
		{KMT_SettingsCofferValue, u8"Killproofs pro Koffer"},
		{KMT_SettingsHideExtrasMessage, u8"Verstecke die \"Unofficial Extras\" Fehlernachricht"},
		{KMT_SettingsClearCacheText, u8"Lösche Cache"},
		{KMT_SettingsClearCacheTooltip, u8"Lösche den Cache und lade alle Spieler neu"},
		{
			KMT_LanguageAsIngameTooltip,
			u8"Funktioniert nur, wenn das \"Unofficial Extras Addon\" installiert ist. Falls nicht, wird Englisch verwendet."
		},
		{KMT_Raids, u8"Schlachtzüge"},
		{KMT_Fractals, u8"Fraktale"},
		{KMT_Strikes, u8"Angriffsmissionen"},
		{KMT_Misc, u8"Sonstiges"},
		{KMT_MapBasedStrikes, u8"Strikes anzeigen"},
		{KMT_UseCustomColumns, u8"Zeige Spalten basierend auf der aktuellen Karte"},
	});

	constexpr std::array KILLPROOF_ME_TRANSLATION_FRENCH = std::to_array<std::pair<KillproofMeTranslations, const char8_t*>>({
		{KMT_AccountName, u8"Compte"},
		{KMT_CharacterName, u8"Personnage"},
		{KMT_KillproofId, u8"ID"},
		{KMT_SubgroupText, u8"Groupe"},
		{KMT_Li_Short, u8"LI"},
		{KMT_Ld_Short, u8"LD"},
		{KMT_LiLd_Short, u8"LI+LD"},
		{KMT_Uce_Short, u8"UCE"},
		{KMT_Ufe_Short, u8"UFE"},
		{KMT_Vg_Short, u8"VG"},
		{KMT_Vg_Long, u8"Gardien de la Vallée"},
		{KMT_Gorse_Short, u8"Gorse"},
		{KMT_Gorse_Long, u8"Gorseval le Disparate"},
		{KMT_Sabetha_Short, u8"Sabetha"},
		{KMT_Sabetha_Long, u8"Sabetha la saboteuse"},
		{KMT_Sloth_Short, u8"Paressor"},
		{KMT_Matthias_Short, u8"Matthias"},
		{KMT_Matthias_Long, u8"Matthias Gabrel"},
		{KMT_Escort_Short, u8"Escorte"},
		{KMT_Kc_Short, u8"KC"},
		{KMT_Kc_Long, u8"Titan du fort"},
		{KMT_Xera_Short, u8"Xera"},
		{KMT_Cairn_Short, u8"Cairn"},
		{KMT_Cairn_Long, u8"Cairn l'Indomptable"},
		{KMT_Mo_Short, u8"MO"},
		{KMT_Mo_Long, u8"Surveillant mursaat"},
		{KMT_Samarog_Short, u8"Samarog"},
		{KMT_Deimos_Short, u8"Deimos"},
		{KMT_Desmina_Short, u8"Desmina"},
		{KMT_Desmina_Long, u8"Horreur sans âme (Desmina)"},
		{KMT_River_Short, u8"Rivière"},
		{KMT_River_Long, u8"Rivière des âmes"},
		{KMT_Statues_Short, u8"Statues"},
		{KMT_Dhuum_Short, u8"Dhuum"},
		{KMT_Ca_Short, u8"CA"},
		{KMT_Ca_Long, u8"Amalgame conjuré"},
		{KMT_Twins_Short, u8"Jumeaux"},
		{KMT_Twins_Long, u8"Jumeaux Largos"},
		{KMT_Qadim_Short, u8"Qadim"},
		{KMT_Sabir_Short, u8"Sabir"},
		{KMT_Adina_Short, u8"Adina"},
		{KMT_Qadim2_Short, u8"Qadim2"},
		{KMT_Qadim2_Long, u8"Qadim l'Inégalé"},
		{KMT_Greer_Short, u8"Greer"},
		{KMT_GreerCM_Short, u8"Greer CM"},
		{KMT_Greer_Long, u8"Greer, le porte-fléau"},
		{KMT_GreerCM_Long, u8"Greer, le porte-fléau CM"},
		{KMT_Decima_Short, u8"Decima"},
		{KMT_DecimaCM_Short, u8"Decima CM"},
		{KMT_Decima_Long, u8"Decima, l'antienne de la tempête"},
		{KMT_DecimaCM_Long, u8"Decima, l'antienne de la tempête CM"},
		{KMT_Ura_Short, u8"Ura"},
		{KMT_UraCM_Short, u8"Ura CM"},
		{KMT_BoneskinnerVial_Short, u8"Fiole"},
		{KMT_BoneskinnerVial_Long, u8"Fiole du rituel du désosseur"},
		{KMT_Ankka_Short, u8"Ankka"},
		{KMT_Ankka_Long, u8"Décharge de Xunlai Jade (Ankka)"},
		{KMT_MinisterLi_Short, u8"KO"},
		{KMT_MinisterLi_Long, u8"Belvédère de Kaineng (Ministre  Li)"},
		{KMT_Harvest_Short, u8"Temple des moissons"},
		{KMT_Harvest_Short, u8"Temple des moissons (Vide draconique)"},
		{KMT_MaiTrin_Short, u8"Mai"},
		{KMT_MaiTrin_Long, u8"Cachette des Étherlames (Mai Trin)"},
		{KMT_MaiTrinCM_Short, u8"Mai CM"},
		{KMT_MaiTrinCM_Long, u8"Cachette des Étherlames (Mai Trin) CM"},
		{KMT_AnkkaCM_Short, u8"Ankka CM"},
		{KMT_AnkkaCM_Long, u8"Décharge de Xunlai Jade (Ankka) CM"},
		{KMT_MinisterLiCM_Short, u8"KO CM"},
		{KMT_MinisterLiCM_Long, u8"Belvédère de Kaineng (Ministre Li) CM"},
		{KMT_HarvestCM_Short, u8"Temple des moissons CM"},
		{KMT_HarvestCM_Long, u8"Temple des moissons (Vide draconique) CM"},
		{KMT_OLC_Short, u8"OLC"},
		{KMT_OLC_Long, u8"Cour du vieux Lion (chevaliers d'assaut)"},
		{KMT_OLCCM_Short, u8"OLC CM"},
		{KMT_OLCCM_Long, u8"Cour du vieux Lion CM (Chevaliers d'assaut)"},
		{KMT_CO_Short, u8"CO"},
		{KMT_CO_Long, u8"Observatoire cosmique (Dagda)"},
		{KMT_COCM_Short, u8"CO CM"},
		{KMT_COCM_Long, u8"Observatoire cosmique (Dagda) CM"},
		{KMT_FEBE_Short, u8"Febe"},
		{KMT_FEBE_Long, u8"Temple de Febe (Cerus)"},
		{KMT_FEBECM_Short, u8"Febe CM"},
		{KMT_FEBECM_Long, u8"Temple de Febe (Cerus) CM"},
		{KMT_Kela_Short, u8"Kela"},
		{KMT_Kela_Long, u8"Kela, sénéchal des vagues"},
		{KMT_KelaCM_Short, u8"Kela CM"},
		{KMT_KelaCM_Long, u8"Kela, sénéchal des vagues CM"},
		{KMT_Bananas, u8"Bananes"},
		{KMT_KpWindowNameDefault, u8"Killproof.me"},
		{KMT_AppearAsInOptionDefault, u8"Killproof.me"},
		{KMT_SettingsShowPrivateText, u8"Comptes privés"},
		{KMT_SettingsShowControls, u8"Afficher les contrôles"},
		{KMT_SettingsShowLinkedByDefault, u8"Afficher les comptes liés par défaut"},
		{KMT_SettingsShowCommander, u8"Afficher le tag du Commandant"},
		{KMT_SettingsBlockedText, u8"Texte à afficher lorsque les données sont indisponibles/privées"},
		{KMT_ShowLinkedTotals, u8"Afficher directement les totaux liés"},
		{
			KMT_UnofficialExtrasNotInstalled,
			u8"Le plugin d'extras non officiels n'est pas installé.\nInstallez-le pour permettre le suivi des joueurs sur d'autres instances."
		},
		{
			KMT_AddPlayerTooltip,
			u8"Nom de compte, ID de killproof.me ou Nom de personnage pour rechercher et ajouter à la liste"
		},
		{KMT_AddPlayerText, u8"Ajouter"},
		{KMT_ClearText, u8"Effacer"},
		{KMT_ClearTooltip, u8"Supprimer tous les utilisateurs ajoutés manuellement"},
		{KMT_CopyKpIdText, u8"Copier votre KP ID"},
		{KMT_Overall, u8"En général"},
		{KMT_Killproofs, u8"Killproofs"},
		{KMT_Coffers, u8"Coffres"},
		{KMT_SettingsDisableESCText, u8"Ne PAS fermer la fenêtre killproof.me en appuyant sur ESC."},
		{KMT_SettingsCofferValue, u8"Killproofs par coffre"},
		{KMT_SettingsHideExtrasMessage, u8"Cacher le message des extras non officiels"},
		{KMT_SettingsClearCacheText, u8"Effacer le cache"},
		{
			KMT_SettingsClearCacheTooltip,
			u8"Videz le cache et rechargez les données de killproof.me pour tous les joueurs."
		},
		{KMT_LanguageAsIngameTooltip, u8"Ne fonctionne que si Unofficial Extras est installé. Retour à l'anglais."},
		{KMT_Raids, u8"Raids"},
		{KMT_Fractals, u8"Fractales"},
		{KMT_Strikes, u8"Missions d'attaque"},
		{KMT_Misc, u8"Divers"},
		{KMT_MapBasedStrikes, u8"Afficher les missions d’attaque"},
		{KMT_UseCustomColumns, u8"Afficher les colonnes en fonction de la carte"},
	});

	constexpr std::array KILLPROOF_ME_TRANSLATION_SPANISH = std::to_array<std::pair<KillproofMeTranslations, const char8_t*>>({
		{KMT_AccountName, u8"Cuenta"},
		{KMT_CharacterName, u8"Carácter"},
		{KMT_KillproofId, u8"ID"},
		{KMT_SubgroupText, u8"Grupo"},
		{KMT_Li_Short, u8"LI"},
		{KMT_Ld_Short, u8"LD"},
		{KMT_LiLd_Short, u8"LI+LD"},
		{KMT_Uce_Short, u8"UCE"},
		{KMT_Ufe_Short, u8"UFE"},
		{KMT_Vg_Short, u8"VG"},
		{KMT_Vg_Long, u8"Guardián del valle"},
		{KMT_Gorse_Short, u8"Gorse"},
		{KMT_Gorse_Long, u8"Gorseval el Múltiple"},
		{KMT_Sabetha_Short, u8"Sabetha"},
		{KMT_Sabetha_Long, u8"Sabetha la Saboteadora"},
		{KMT_Sloth_Short, u8"Perezón"},
		{KMT_Matthias_Short, u8"Matías"},
		{KMT_Matthias_Long, u8"Matías Gabrel"},
		{KMT_Escort_Short, u8"Escolta"},
		{KMT_Kc_Short, u8"KC"},
		{KMT_Kc_Long, u8"Ensamblaje de la Fortaleza"},
		{KMT_Xera_Short, u8"Xera"},
		{KMT_Cairn_Short, u8"Cairn"},
		{KMT_Cairn_Long, u8"Cairn el Indomable"},
		{KMT_Mo_Short, u8"MO"},
		{KMT_Mo_Long, u8"Dirigente mursaat"},
		{KMT_Samarog_Short, u8"Samarog"},
		{KMT_Deimos_Short, u8"Deimos"},
		{KMT_Desmina_Short, u8"Desmina"},
		{KMT_Desmina_Long, u8"Horror sin alma"},
		{KMT_River_Short, u8"Río"},
		{KMT_River_Long, u8"Río de Almas"},
		{KMT_Statues_Short, u8"Estatuas"},
		{KMT_Dhuum_Short, u8"Dhuum"},
		{KMT_Ca_Short, u8"CA"},
		{KMT_Ca_Long, u8"Amalgamado conjurado"},
		{KMT_Twins_Short, u8"Gemelos"},
		{KMT_Twins_Long, u8"Largos gemelos"},
		{KMT_Qadim_Short, u8"Qadim"},
		{KMT_Sabir_Short, u8"Sabir"},
		{KMT_Adina_Short, u8"Adina"},
		{KMT_Qadim2_Short, u8"Qadim2"},
		{KMT_Qadim2_Long, u8"Qadim el Simpar"},
		{KMT_Greer_Short, u8"Greer"},
		{KMT_GreerCM_Short, u8"Greer CM"},
		{KMT_Greer_Long, u8"Greer, el Portarruina"},
		{KMT_GreerCM_Long, u8"Greer, el Portarruina CM"},
		{KMT_Decima_Short, u8"Decima"},
		{KMT_DecimaCM_Short, u8"Decima CM"},
		{KMT_Decima_Long, u8"Decima, la Invocatormentas"},
		{KMT_DecimaCM_Long, u8"Decima, la Invocatormentas CM"},
		{KMT_Ura_Short, u8"Ura"},
		{KMT_UraCM_Short, u8"Ura CM"},
		{KMT_BoneskinnerVial_Short, u8"Vial"},
		{KMT_BoneskinnerVial_Long, u8"Vial del ritual del pelahuesos"},
		{KMT_Ankka_Short, u8"Ankka"},
		{KMT_Ankka_Long, u8"Chatarreria de Xunlay Jade (Ankka)"},
		{KMT_MinisterLi_Short, u8"KO"},
		{KMT_MinisterLi_Long, u8"Mirador de Kaineng (Ministro Li)"},
		{KMT_Harvest_Short, u8"Templo de la Cosecha"},
		{KMT_Harvest_Long, u8"Templo de la Cosecha"},
		{KMT_MaiTrin_Short, u8"Mai"},
		{KMT_MaiTrin_Long, u8"Escondite Filoetéreo (Mai Trin)"},
		{KMT_MaiTrinCM_Short, u8"Mai CM"},
		{KMT_MaiTrinCM_Long, u8"Escondite Filoetéreo (Mai Trin) CM"},
		{KMT_AnkkaCM_Short, u8"Ankka CM"},
		{KMT_AnkkaCM_Long, u8"Chatarreria de Xunlay Jade (Ankka) CM"},
		{KMT_MinisterLiCM_Short, u8"KO CM"},
		{KMT_MinisterLiCM_Long, u8"Mirador de Kaineng (Ministro Li) CM"},
		{KMT_HarvestCM_Short, u8"Templo de la Cosecha CM"},
		{KMT_HarvestCM_Long, u8"Templo de la Cosecha CM"},
		{KMT_OLC_Short, u8"OLC"},
		{KMT_OLC_Long, u8"Vieja Corte del León (caballeras de asalto)"},
		{KMT_OLCCM_Short, u8"OLC CM"},
		{KMT_OLCCM_Long, u8"Vieja Corte del León CM (caballeras de asalto)"},
		{KMT_CO_Short, u8"CO"},
		{KMT_CO_Long, u8"Observatorio Cósmico (Dagda)"},
		{KMT_COCM_Short, u8"CO CM"},
		{KMT_COCM_Long, u8"Observatorio Cósmico (Dagda) CM"},
		{KMT_FEBE_Short, u8"Febe"},
		{KMT_FEBE_Long, u8"Templo de Febe (Cerus)"},
		{KMT_FEBECM_Short, u8"Febe CM"},
		{KMT_FEBECM_Long, u8"Templo de Febe (Cerus) CM"},
		{KMT_Kela_Short, u8"Kela"},
		{KMT_Kela_Long, u8"Kela, Senescal de las Olas"},
		{KMT_KelaCM_Short, u8"Kela CM"},
		{KMT_KelaCM_Long, u8"Kela, Senescal de las Olas CM"},
		{KMT_Bananas, u8"Plátanos"},
		{KMT_KpWindowNameDefault, u8"Killproof.me"},
		{KMT_AppearAsInOptionDefault, u8"Killproof.me"},
		{KMT_SettingsShowPrivateText, u8"Cuentas privadas"},
		{KMT_SettingsShowControls, u8"Mostrar controles"},
		{KMT_SettingsShowLinkedByDefault, u8"Mostrar las cuentas vinculadas por defecto"},
		{KMT_SettingsShowCommander, u8"Mostrar etiqueta de comandante"},
		{KMT_SettingsBlockedText, u8"Texto a mostrar cuando los datos no están disponibles/privados"},
		{KMT_ShowLinkedTotals, u8"Mostrar directamente los totales vinculados"},
		{
			KMT_UnofficialExtrasNotInstalled,
			u8"El plugin de extras no oficiales no está instalado.\nInstálalo para permitir el seguimiento de los jugadores en otras instancias."
		},
		{
			KMT_AddPlayerTooltip,
			u8"Nombre de la cuenta, ID de killproof.me o nombre del personaje para buscar y añadir a la lista"
		},
		{KMT_AddPlayerText, u8"Añadir"},
		{KMT_ClearText, u8"Borrar"},
		{KMT_ClearTooltip, u8"Eliminar todos los usuarios añadidos manualmente"},
		{KMT_CopyKpIdText, u8"Copiar el propio KP ID"},
		{KMT_Overall, u8"En general"},
		{KMT_Killproofs, u8"Killproofs"},
		{KMT_Coffers, u8"Cofres"},
		{KMT_SettingsDisableESCText, u8"NO cerrar la ventana de killproof.me con ESC"},
		{KMT_SettingsCofferValue, u8"Killproofs por cofre"},
		{KMT_SettingsHideExtrasMessage, u8"Ocultar el mensaje de los extras no oficiales"},
		{KMT_SettingsClearCacheText, u8"Borrar caché"},
		{
			KMT_SettingsClearCacheTooltip,
			u8"Borrar la caché y recargar los datos de killproof.me para todos los jugadores"
		},
		{
			KMT_LanguageAsIngameTooltip,
			u8"Sólo funciona si se instalan los Extras no oficiales. Volverá a funcionar en inglés."
		},
		{KMT_Raids, u8"Incursión"},
		{KMT_Fractals, u8"Fractales"},
		{KMT_Strikes, u8"Misión de ataque"},
		{KMT_Misc, u8"Varios"},
		{KMT_MapBasedStrikes, u8"Mostrar misiones de ataque"},
		{KMT_UseCustomColumns, u8"Mostrar columnas basadas en el mapa"},
	});

	static_assert(KILLPROOF_ME_TRANSLATION_ENGLISH.size() == magic_enum::enum_count<KillproofMeTranslations>());
	static_assert(KILLPROOF_ME_TRANSLATION_ENGLISH.size() == KILLPROOF_ME_TRANSLATION_GERMAN.size());
	static_assert(KILLPROOF_ME_TRANSLATION_ENGLISH.size() == KILLPROOF_ME_TRANSLATION_FRENCH.size());
	static_assert(KILLPROOF_ME_TRANSLATION_ENGLISH.size() == KILLPROOF_ME_TRANSLATION_SPANISH.size());
}

void LoadAdditionalTranslations()
{
	ArcdpsExtension::Localization& localization = ArcdpsExtension::Localization::instance();
	localization.Load(ArcdpsExtension::Lang::English);
	localization.Load(ArcdpsExtension::Lang::French);
	localization.Load(ArcdpsExtension::Lang::German);
	localization.Load(ArcdpsExtension::Lang::Spanish);

	localization.Load(ArcdpsExtension::Lang::English, ArcdpsExtension::UE_TRANSLATIONS_ENGLISH);
	localization.Load(ArcdpsExtension::Lang::French, ArcdpsExtension::UE_TRANSLATIONS_FRENCH);
	localization.Load(ArcdpsExtension::Lang::German, ArcdpsExtension::UE_TRANSLATIONS_GERMAN);
	localization.Load(ArcdpsExtension::Lang::Spanish, ArcdpsExtension::UE_TRANSLATIONS_SPANISH);

	localization.Load(ArcdpsExtension::Lang::English, KILLPROOF_ME_TRANSLATION_ENGLISH);
	localization.Load(ArcdpsExtension::Lang::French, KILLPROOF_ME_TRANSLATION_FRENCH);
	localization.Load(ArcdpsExtension::Lang::German, KILLPROOF_ME_TRANSLATION_GERMAN);
	localization.Load(ArcdpsExtension::Lang::Spanish, KILLPROOF_ME_TRANSLATION_SPANISH);
}

void LoadTranslationFiles()
{
	constexpr std::string_view prefix = "arcdps_killproof_lang_";
	constexpr std::string_view suffix = ".ini";

	for (const auto& entry : std::filesystem::directory_iterator("addons/arcdps"))
	{
		const std::string nameStr = entry.path().filename().string();
		std::string_view name = nameStr;

		if (name.starts_with(prefix) && name.ends_with(suffix))
		{
			name.remove_prefix(prefix.length());
			name.remove_suffix(suffix.length());

			std::string id(name);

			// Normalize to lowercase
			std::ranges::transform(id, id.begin(), ::tolower);

			std::unordered_map<ArcdpsExtension::ExtensionTranslation, std::string> extensionTranslations;
			std::unordered_map<ArcdpsExtension::UETranslation, std::string> unofficialExtrasTranslations;
			std::unordered_map<KillproofMeTranslations, std::string> killproofMeTranslations;

			std::ifstream input(entry.path());
			modernIni::Ini ini;
			input >> ini;

			auto load = [&entry](const modernIni::Ini& ini, const std::string& key,
			                     auto& out) -> modernIni::Result<void>
			{
				auto transRes = ini.at(key);
				if (!transRes)
				{
					ARC_LOG(std::format("Error ({}) loading {} from file '{}'", transRes.error(), key,
					                    entry.path().string()).c_str());
					ARC_LOG_FILE(std::format("Error ({}) loading {} from file '{}'", transRes.error(), key,
					                         entry.path().string()).c_str());
					return std::unexpected(transRes.error());
				}
				auto valueRes = transRes.value().get().get_to(out);
				if (!valueRes)
				{
					ARC_LOG(std::format("Error ({}) loading {} from file '{}'", valueRes.error(), key,
					                    entry.path().string()).c_str());
					ARC_LOG_FILE(std::format("Error ({}) loading {} from file '{}'", valueRes.error(), key,
					                         entry.path().string()).c_str());
					return std::unexpected(transRes.error());
				}
				return std::expected<void, modernIni::Error>(std::in_place);
			};

			// We can ignore errors here, worst case is just that the fallback of english will be used.
			std::ignore = load(ini, "extensionTranslations", extensionTranslations);
			std::ignore = load(ini, "unofficialExtrasTranslations", unofficialExtrasTranslations);
			std::ignore = load(ini, "killproofMeTranslations", killproofMeTranslations);

			auto& localization = ArcdpsExtension::Localization::instance();
			localization.Load(id, extensionTranslations);
			localization.Load(id, unofficialExtrasTranslations);
			localization.Load(id, killproofMeTranslations);
		}
	}
}

void SaveTranslationFile()
{
	modernIni::Ini ini;
	ini["extensionTranslations"] = ArcdpsExtension::EXTENSION_TRANSLATION_ENGLISH;
	ini["unofficialExtrasTranslations"] = ArcdpsExtension::UE_TRANSLATIONS_ENGLISH;
	ini["killproofMeTranslations"] = KILLPROOF_ME_TRANSLATION_ENGLISH;

	std::ofstream out("addons/arcdps/arcdps_killproof_lang_en.ini");
	out << ini;
	out.flush();
}
