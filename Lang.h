#pragma once

#include "extension/arcdps_structs.h"

#include <map>
#include <string>
#include <nlohmann/json.hpp>
#include <magic_enum.hpp>

#include "extension/map.h"
#include "extension/ExtensionTranslations.h"
#include "extension/Localization.h"

constexpr auto enumMax = magic_enum::detail::max_v<ExtensionTranslation>;
enum KillproofMeTranslations {
	KMT_AccountName = enumMax + 1,
	KMT_CharacterName,
	KMT_KillproofId,
	KMT_SubgroupText,
	KMT_LI,
	KMT_Ld,
	KMT_LiLd,
	KMT_Uce,
	KMT_Ufe,
	KMT_Vg,
	KMT_Gorse,
	KMT_Sabetha,
	KMT_Sloth,
	KMT_Matthias,
	KMT_Escort,
	KMT_Kc,
	KMT_Xera,
	KMT_Cairn,
	KMT_Mo,
	KMT_Samarog,
	KMT_Deimos,
	KMT_Desmina,
	KMT_River,
	KMT_Statues,
	KMT_Dhuum,
	KMT_Ca,
	KMT_Twins,
	KMT_Qadim,
	KMT_Sabir,
	KMT_Adina,
	KMT_Qadim2,
	KMT_BoneskinnerVial,
	KMT_Ankka,
	KMT_MinisterLi,
	KMT_Harvest,
	KMT_MaiTrin,
	KMT_MaiTrinCM,
	KMT_AnkkaCM,
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
	"LI", // KMT_LI
	"LD", // KMT_Ld
	"LI/LD", // KMT_LiLd
	"UCE", // KMT_Uce
	"UFE", // KMT_Ufe
	"VG", // KMT_Vg
	"Gorse", // KMT_Gorse
	"Sabetha", // KMT_Sabetha
	"Sloth", // KMT_Sloth
	"Matthias", // KMT_Matthias
	"Escort", // KMT_Escort
	"KC", // KMT_Kc
	"Xera", // KMT_Xera
	"Cairn", // KMT_Cairn
	"MO", // KMT_Mo
	"Samarog", // KMT_Samarog
	"Deimos", // KMT_Deimos
	"Desmina", // KMT_Desmina
	"River", // KMT_River
	"Statues", // KMT_Statues
	"Dhuum", // KMT_Dhuum
	"CA", // KMT_Ca
	"Twins", // KMT_Twins
	"Qadim", // KMT_Qadim
	"Sabir", // KMT_Sabir
	"Adina", // KMT_Adina
	"Qadim2", // KMT_Qadim2
	"Boneskinner Ritual Vial", // KMT_BoneskinnerVial
	"Ankka", // KMT_Ankka
	"Minister Li", // KMT_MinisterLi
	"Harvest Tempel", // KMT_Harvest
	"Mai Trin", // KMT_MaiTrin
	"Mai Trin CM", // KMT_MaiTrinCM
	"Ankka CM", // KMT_AnkkaCM
	"Killproof.me", // KMT_KpWindowNameDefault
	"Killproof.me", // KMT_AppearAsInOptionDefault
	"Private accounts", // KMT_SettingsShowPrivateText
	"Show controls", // KMT_SettingsShowControls
	"Show linked accounts by default", // KMT_SettingsShowLinkedByDefault
	"Show commander Tag", // KMT_SettingsShowCommander
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
	"LI", // KMT_LI
	"LD", // KMT_Ld
	"LI/LD", // KMT_LiLd
	"UCE", // KMT_Uce
	"UFE", // KMT_Ufe
	"VG", // KMT_Vg
	"Gorse", // KMT_Gorse
	"Sabetha", // KMT_Sabetha
	"Faulterion", // KMT_Sloth
	"Matthias", // KMT_Matthias
	"Escort", // KMT_Escort
	"KC", // KMT_Kc
	"Xera", // KMT_Xera
	"Cairn", // KMT_Cairn
	"MO", // KMT_Mo
	"Samarog", // KMT_Samarog
	"Deimos", // KMT_Deimos
	"Desmina", // KMT_Desmina
	"River", // KMT_River
	"Statues", // KMT_Statues
	"Dhuum", // KMT_Dhuum
	"CA", // KMT_Ca
	"Twins", // KMT_Twins
	"Qadim", // KMT_Qadim
	"Sabir", // KMT_Sabir
	"Adina", // KMT_Adina
	"Qadim2", // KMT_Qadim2
	"Knochenhäuter-Ritual-Phiole", // KMT_BoneskinnerVial
	"Ankka", // KMT_Ankka
	"Minister Li", // KMT_MinisterLi
	"Erntetempel", // KMT_Harvest
	"Mai Trin", // KMT_MaiTrin
	"Mai Trin CM", // KMT_MaiTrinCM
	"Ankka CM", // KMT_AnkkaCM
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
	"LI", // KMT_LI
	"LD", // KMT_Ld
	"LI/LD", // KMT_LiLd
	"UCE", // KMT_Uce
	"UFE", // KMT_Ufe
	"VG", // KMT_Vg
	"Gorse", // KMT_Gorse
	"Sabetha", // KMT_Sabetha
	"Paressor", // KMT_Sloth
	"Matthias", // KMT_Matthias
	"Escorte", // KMT_Escort
	"KC", // KMT_Kc
	"Xera", // KMT_Xera
	"Cairn", // KMT_Cairn
	"MO", // KMT_Mo
	"Samarog", // KMT_Samarog
	"Deimos", // KMT_Deimos
	"Desmina", // KMT_Desmina
	"Rivière", // KMT_River
	"Statues", // KMT_Statues
	"Dhuum", // KMT_Dhuum
	"CA", // KMT_Ca
	"Jumeaux", // KMT_Twins
	"Qadim", // KMT_Qadim
	"Sabir", // KMT_Sabir
	"Adina", // KMT_Adina
	"Qadim2", // KMT_Qadim2
	"Fiole du rituel du désosseur", // KMT_BoneskinnerVial
	"Ankka", // KMT_Ankka
	"Ministre Li", // KMT_MinisterLi
	"Tempête de la moisson", // KMT_Harvest
	"Mai Trin", // KMT_MaiTrin
	"Mai Trin CM", // KMT_MaiTrinCM
	"Ankka CM", // KMT_AnkkaCM
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
	"LI", // KMT_LI
	"LD", // KMT_Ld
	"LI/LD", // KMT_LiLd
	"UCE", // KMT_Uce
	"UFE", // KMT_Ufe
	"VG", // KMT_Vg
	"Gorse", // KMT_Gorse
	"Sabetha", // KMT_Sabetha
	"Perezón", // KMT_Sloth
	"Matías ", // KMT_Matthias
	"Escolta", // KMT_Escort
	"KC", // KMT_Kc
	"Xera", // KMT_Xera
	"Cairn", // KMT_Cairn
	"MO", // KMT_Mo
	"Samarog", // KMT_Samarog
	"Deimos", // KMT_Deimos
	"Desmina", // KMT_Desmina
	"Río", // KMT_River
	"Estatuas", // KMT_Statues
	"Dhuum", // KMT_Dhuum
	"CA", // KMT_Ca
	"Gemelos", // KMT_Twins
	"Qadim", // KMT_Qadim
	"Sabir", // KMT_Sabir
	"Adina", // KMT_Adina
	"Qadim2", // KMT_Qadim2
	"Vial del ritual del pelahuesos", // KMT_BoneskinnerVial
	"Ankka", // KMT_Ankka
	"Ministro Li", // KMT_MinisterLi
	"Templo de la Cosecha", // KMT_Harvest
	"Mai Trin", // KMT_MaiTrin
	"Mai Trin CM", // KMT_MaiTrinCM
	"Ankka CM", // KMT_AnkkaCM
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
