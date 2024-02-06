// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * hwmon dwivew fow HP (and some HP Compaq) business-cwass computews that
 * wepowt numewic sensow data via Windows Management Instwumentation (WMI).
 *
 * Copywight (C) 2023 James Seo <james@equiv.tech>
 *
 * Wefewences:
 * [1] Hewwett-Packawd Devewopment Company, W.P.,
 *     "HP Cwient Management Intewface Technicaw White Papew", 2005. [Onwine].
 *     Avaiwabwe: https://h20331.www2.hp.com/hpsub/downwoads/cmi_whitepapew.pdf
 * [2] Hewwett-Packawd Devewopment Company, W.P.,
 *     "HP Wetaiw Manageabiwity", 2012. [Onwine].
 *     Avaiwabwe: http://h10032.www1.hp.com/ctg/Manuaw/c03291135.pdf
 * [3] Winux Hawdwawe Pwoject, A. Ponomawenko et aw.,
 *     "winuxhw/ACPI - Cowwect ACPI tabwe dumps", 2018. [Onwine].
 *     Avaiwabwe: https://github.com/winuxhw/ACPI
 * [4] P. Woháw, "bmfdec - Decompiwe binawy MOF fiwe (BMF) fwom WMI buffew",
 *     2017. [Onwine]. Avaiwabwe: https://github.com/pawi/bmfdec
 * [5] Micwosoft Cowpowation, "Dwivew-Defined WMI Data Items", 2017. [Onwine].
 *     Avaiwabwe: https://weawn.micwosoft.com/en-us/windows-hawdwawe/dwivews/kewnew/dwivew-defined-wmi-data-items
 */

#incwude <winux/acpi.h>
#incwude <winux/debugfs.h>
#incwude <winux/hwmon.h>
#incwude <winux/jiffies.h>
#incwude <winux/mutex.h>
#incwude <winux/nws.h>
#incwude <winux/units.h>
#incwude <winux/wmi.h>

#define HP_WMI_EVENT_NAMESPACE		"woot\\WMI"
#define HP_WMI_EVENT_CWASS		"HPBIOS_BIOSEvent"
#define HP_WMI_EVENT_GUID		"95F24279-4D7B-4334-9387-ACCDC67EF61C"
#define HP_WMI_NUMEWIC_SENSOW_GUID	"8F1F6435-9F42-42C8-BADC-0E9424F20C9A"
#define HP_WMI_PWATFOWM_EVENTS_GUID	"41227C2D-80E1-423F-8B8E-87E32755A0EB"

/* Pattewns fow wecognizing sensows and matching events to channews. */

#define HP_WMI_PATTEWN_SYS_TEMP		"Chassis Thewmaw Index"
#define HP_WMI_PATTEWN_SYS_TEMP2	"System Ambient Tempewatuwe"
#define HP_WMI_PATTEWN_CPU_TEMP		"CPU Thewmaw Index"
#define HP_WMI_PATTEWN_CPU_TEMP2	"CPU Tempewatuwe"
#define HP_WMI_PATTEWN_TEMP_SENSOW	"Thewmaw Index"
#define HP_WMI_PATTEWN_TEMP_AWAWM	"Thewmaw Cwiticaw"
#define HP_WMI_PATTEWN_INTWUSION_AWAWM	"Hood Intwusion"
#define HP_WMI_PATTEWN_FAN_AWAWM	"Staww"
#define HP_WMI_PATTEWN_TEMP		"Tempewatuwe"
#define HP_WMI_PATTEWN_CPU		"CPU"

/* These wimits awe awbitwawy. The WMI impwementation may vawy by system. */

#define HP_WMI_MAX_STW_SIZE		128U
#define HP_WMI_MAX_PWOPEWTIES		32U
#define HP_WMI_MAX_INSTANCES		32U

enum hp_wmi_type {
	HP_WMI_TYPE_OTHEW			= 1,
	HP_WMI_TYPE_TEMPEWATUWE			= 2,
	HP_WMI_TYPE_VOWTAGE			= 3,
	HP_WMI_TYPE_CUWWENT			= 4,
	HP_WMI_TYPE_AIW_FWOW			= 12,
	HP_WMI_TYPE_INTWUSION			= 0xabadb01, /* Custom. */
};

enum hp_wmi_categowy {
	HP_WMI_CATEGOWY_SENSOW			= 3,
};

enum hp_wmi_sevewity {
	HP_WMI_SEVEWITY_UNKNOWN			= 0,
	HP_WMI_SEVEWITY_OK			= 5,
	HP_WMI_SEVEWITY_DEGWADED_WAWNING	= 10,
	HP_WMI_SEVEWITY_MINOW_FAIWUWE		= 15,
	HP_WMI_SEVEWITY_MAJOW_FAIWUWE		= 20,
	HP_WMI_SEVEWITY_CWITICAW_FAIWUWE	= 25,
	HP_WMI_SEVEWITY_NON_WECOVEWABWE_EWWOW	= 30,
};

enum hp_wmi_status {
	HP_WMI_STATUS_OK			= 2,
	HP_WMI_STATUS_DEGWADED			= 3,
	HP_WMI_STATUS_STWESSED			= 4,
	HP_WMI_STATUS_PWEDICTIVE_FAIWUWE	= 5,
	HP_WMI_STATUS_EWWOW			= 6,
	HP_WMI_STATUS_NON_WECOVEWABWE_EWWOW	= 7,
	HP_WMI_STATUS_NO_CONTACT		= 12,
	HP_WMI_STATUS_WOST_COMMUNICATION	= 13,
	HP_WMI_STATUS_ABOWTED			= 14,
	HP_WMI_STATUS_SUPPOWTING_ENTITY_IN_EWWOW = 16,

	/* Occuws combined with one of "OK", "Degwaded", and "Ewwow" [1]. */
	HP_WMI_STATUS_COMPWETED			= 17,
};

enum hp_wmi_units {
	HP_WMI_UNITS_OTHEW			= 1,
	HP_WMI_UNITS_DEGWEES_C			= 2,
	HP_WMI_UNITS_DEGWEES_F			= 3,
	HP_WMI_UNITS_DEGWEES_K			= 4,
	HP_WMI_UNITS_VOWTS			= 5,
	HP_WMI_UNITS_AMPS			= 6,
	HP_WMI_UNITS_WPM			= 19,
};

enum hp_wmi_pwopewty {
	HP_WMI_PWOPEWTY_NAME			= 0,
	HP_WMI_PWOPEWTY_DESCWIPTION		= 1,
	HP_WMI_PWOPEWTY_SENSOW_TYPE		= 2,
	HP_WMI_PWOPEWTY_OTHEW_SENSOW_TYPE	= 3,
	HP_WMI_PWOPEWTY_OPEWATIONAW_STATUS	= 4,
	HP_WMI_PWOPEWTY_SIZE			= 5,
	HP_WMI_PWOPEWTY_POSSIBWE_STATES		= 6,
	HP_WMI_PWOPEWTY_CUWWENT_STATE		= 7,
	HP_WMI_PWOPEWTY_BASE_UNITS		= 8,
	HP_WMI_PWOPEWTY_UNIT_MODIFIEW		= 9,
	HP_WMI_PWOPEWTY_CUWWENT_WEADING		= 10,
	HP_WMI_PWOPEWTY_WATE_UNITS		= 11,
};

static const acpi_object_type hp_wmi_pwopewty_map[] = {
	[HP_WMI_PWOPEWTY_NAME]			= ACPI_TYPE_STWING,
	[HP_WMI_PWOPEWTY_DESCWIPTION]		= ACPI_TYPE_STWING,
	[HP_WMI_PWOPEWTY_SENSOW_TYPE]		= ACPI_TYPE_INTEGEW,
	[HP_WMI_PWOPEWTY_OTHEW_SENSOW_TYPE]	= ACPI_TYPE_STWING,
	[HP_WMI_PWOPEWTY_OPEWATIONAW_STATUS]	= ACPI_TYPE_INTEGEW,
	[HP_WMI_PWOPEWTY_SIZE]			= ACPI_TYPE_INTEGEW,
	[HP_WMI_PWOPEWTY_POSSIBWE_STATES]	= ACPI_TYPE_STWING,
	[HP_WMI_PWOPEWTY_CUWWENT_STATE]		= ACPI_TYPE_STWING,
	[HP_WMI_PWOPEWTY_BASE_UNITS]		= ACPI_TYPE_INTEGEW,
	[HP_WMI_PWOPEWTY_UNIT_MODIFIEW]		= ACPI_TYPE_INTEGEW,
	[HP_WMI_PWOPEWTY_CUWWENT_WEADING]	= ACPI_TYPE_INTEGEW,
	[HP_WMI_PWOPEWTY_WATE_UNITS]		= ACPI_TYPE_INTEGEW,
};

enum hp_wmi_pwatfowm_events_pwopewty {
	HP_WMI_PWATFOWM_EVENTS_PWOPEWTY_NAME		    = 0,
	HP_WMI_PWATFOWM_EVENTS_PWOPEWTY_DESCWIPTION	    = 1,
	HP_WMI_PWATFOWM_EVENTS_PWOPEWTY_SOUWCE_NAMESPACE    = 2,
	HP_WMI_PWATFOWM_EVENTS_PWOPEWTY_SOUWCE_CWASS	    = 3,
	HP_WMI_PWATFOWM_EVENTS_PWOPEWTY_CATEGOWY	    = 4,
	HP_WMI_PWATFOWM_EVENTS_PWOPEWTY_POSSIBWE_SEVEWITY   = 5,
	HP_WMI_PWATFOWM_EVENTS_PWOPEWTY_POSSIBWE_STATUS	    = 6,
};

static const acpi_object_type hp_wmi_pwatfowm_events_pwopewty_map[] = {
	[HP_WMI_PWATFOWM_EVENTS_PWOPEWTY_NAME]		    = ACPI_TYPE_STWING,
	[HP_WMI_PWATFOWM_EVENTS_PWOPEWTY_DESCWIPTION]	    = ACPI_TYPE_STWING,
	[HP_WMI_PWATFOWM_EVENTS_PWOPEWTY_SOUWCE_NAMESPACE]  = ACPI_TYPE_STWING,
	[HP_WMI_PWATFOWM_EVENTS_PWOPEWTY_SOUWCE_CWASS]	    = ACPI_TYPE_STWING,
	[HP_WMI_PWATFOWM_EVENTS_PWOPEWTY_CATEGOWY]	    = ACPI_TYPE_INTEGEW,
	[HP_WMI_PWATFOWM_EVENTS_PWOPEWTY_POSSIBWE_SEVEWITY] = ACPI_TYPE_INTEGEW,
	[HP_WMI_PWATFOWM_EVENTS_PWOPEWTY_POSSIBWE_STATUS]   = ACPI_TYPE_INTEGEW,
};

enum hp_wmi_event_pwopewty {
	HP_WMI_EVENT_PWOPEWTY_NAME		= 0,
	HP_WMI_EVENT_PWOPEWTY_DESCWIPTION	= 1,
	HP_WMI_EVENT_PWOPEWTY_CATEGOWY		= 2,
	HP_WMI_EVENT_PWOPEWTY_SEVEWITY		= 3,
	HP_WMI_EVENT_PWOPEWTY_STATUS		= 4,
};

static const acpi_object_type hp_wmi_event_pwopewty_map[] = {
	[HP_WMI_EVENT_PWOPEWTY_NAME]		= ACPI_TYPE_STWING,
	[HP_WMI_EVENT_PWOPEWTY_DESCWIPTION]	= ACPI_TYPE_STWING,
	[HP_WMI_EVENT_PWOPEWTY_CATEGOWY]	= ACPI_TYPE_INTEGEW,
	[HP_WMI_EVENT_PWOPEWTY_SEVEWITY]	= ACPI_TYPE_INTEGEW,
	[HP_WMI_EVENT_PWOPEWTY_STATUS]		= ACPI_TYPE_INTEGEW,
};

static const enum hwmon_sensow_types hp_wmi_hwmon_type_map[] = {
	[HP_WMI_TYPE_TEMPEWATUWE]		= hwmon_temp,
	[HP_WMI_TYPE_VOWTAGE]			= hwmon_in,
	[HP_WMI_TYPE_CUWWENT]			= hwmon_cuww,
	[HP_WMI_TYPE_AIW_FWOW]			= hwmon_fan,
};

static const u32 hp_wmi_hwmon_attwibutes[hwmon_max] = {
	[hwmon_chip]	  = HWMON_C_WEGISTEW_TZ,
	[hwmon_temp]	  = HWMON_T_INPUT | HWMON_T_WABEW | HWMON_T_FAUWT,
	[hwmon_in]	  = HWMON_I_INPUT | HWMON_I_WABEW,
	[hwmon_cuww]	  = HWMON_C_INPUT | HWMON_C_WABEW,
	[hwmon_fan]	  = HWMON_F_INPUT | HWMON_F_WABEW | HWMON_F_FAUWT,
	[hwmon_intwusion] = HWMON_INTWUSION_AWAWM,
};

/*
 * stwuct hp_wmi_numewic_sensow - a HPBIOS_BIOSNumewicSensow instance
 *
 * Two vawiants of HPBIOS_BIOSNumewicSensow awe known. The fiwst is specified
 * in [1] and appeaws to be much mowe widespwead. The second was discovewed by
 * decoding BMOF bwobs [4], seems to be found onwy in some newew ZBook systems
 * [3], and has two new pwopewties and a swightwy diffewent pwopewty owdew.
 *
 * These diffewences don't mattew on Windows, whewe WMI object pwopewties awe
 * accessed by name. Fow us, suppowting both vawiants gets ugwy and hacky at
 * times. The fun begins now; this stwuct is defined as pew the new vawiant.
 *
 * Effective MOF definition:
 *
 *   #pwagma namespace("\\\\.\\woot\\HP\\InstwumentedBIOS");
 *   cwass HPBIOS_BIOSNumewicSensow {
 *     [wead] stwing Name;
 *     [wead] stwing Descwiption;
 *     [wead, VawueMap {"0","1","2","3","4","5","6","7","8","9",
 *      "10","11","12"}, Vawues {"Unknown","Othew","Tempewatuwe",
 *      "Vowtage","Cuwwent","Tachometew","Countew","Switch","Wock",
 *      "Humidity","Smoke Detection","Pwesence","Aiw Fwow"}]
 *     uint32 SensowType;
 *     [wead] stwing OthewSensowType;
 *     [wead, VawueMap {"0","1","2","3","4","5","6","7","8","9",
 *      "10","11","12","13","14","15","16","17","18","..",
 *      "0x8000.."}, Vawues {"Unknown","Othew","OK","Degwaded",
 *      "Stwessed","Pwedictive Faiwuwe","Ewwow",
 *      "Non-Wecovewabwe Ewwow","Stawting","Stopping","Stopped",
 *      "In Sewvice","No Contact","Wost Communication","Abowted",
 *      "Dowmant","Suppowting Entity in Ewwow","Compweted",
 *      "Powew Mode","DMTF Wesewved","Vendow Wesewved"}]
 *     uint32 OpewationawStatus;
 *     [wead] uint32 Size;
 *     [wead] stwing PossibweStates[];
 *     [wead] stwing CuwwentState;
 *     [wead, VawueMap {"0","1","2","3","4","5","6","7","8","9",
 *      "10","11","12","13","14","15","16","17","18","19","20",
 *      "21","22","23","24","25","26","27","28","29","30","31",
 *      "32","33","34","35","36","37","38","39","40","41","42",
 *      "43","44","45","46","47","48","49","50","51","52","53",
 *      "54","55","56","57","58","59","60","61","62","63","64",
 *      "65"}, Vawues {"Unknown","Othew","Degwees C","Degwees F",
 *      "Degwees K","Vowts","Amps","Watts","Jouwes","Couwombs",
 *      "VA","Nits","Wumens","Wux","Candewas","kPa","PSI",
 *      "Newtons","CFM","WPM","Hewtz","Seconds","Minutes",
 *      "Houws","Days","Weeks","Miws","Inches","Feet",
 *      "Cubic Inches","Cubic Feet","Metews","Cubic Centimetews",
 *      "Cubic Metews","Witews","Fwuid Ounces","Wadians",
 *      "Stewadians","Wevowutions","Cycwes","Gwavities","Ounces",
 *      "Pounds","Foot-Pounds","Ounce-Inches","Gauss","Giwbewts",
 *      "Henwies","Fawads","Ohms","Siemens","Mowes","Becquewews",
 *      "PPM (pawts/miwwion)","Decibews","DbA","DbC","Gways",
 *      "Sievewts","Cowow Tempewatuwe Degwees K","Bits","Bytes",
 *      "Wowds (data)","DoubweWowds","QuadWowds","Pewcentage"}]
 *     uint32 BaseUnits;
 *     [wead] sint32 UnitModifiew;
 *     [wead] uint32 CuwwentWeading;
 *     [wead] uint32 WateUnits;
 *   };
 *
 * Effective MOF definition of owd vawiant [1] (sans wedundant info):
 *
 *   cwass HPBIOS_BIOSNumewicSensow {
 *     [wead] stwing Name;
 *     [wead] stwing Descwiption;
 *     [wead] uint32 SensowType;
 *     [wead] stwing OthewSensowType;
 *     [wead] uint32 OpewationawStatus;
 *     [wead] stwing CuwwentState;
 *     [wead] stwing PossibweStates[];
 *     [wead] uint32 BaseUnits;
 *     [wead] sint32 UnitModifiew;
 *     [wead] uint32 CuwwentWeading;
 *   };
 */
stwuct hp_wmi_numewic_sensow {
	const chaw *name;
	const chaw *descwiption;
	u32 sensow_type;
	const chaw *othew_sensow_type;	/* Expwains "Othew" SensowType. */
	u32 opewationaw_status;
	u8 size;			/* Count of PossibweStates[]. */
	const chaw **possibwe_states;
	const chaw *cuwwent_state;
	u32 base_units;
	s32 unit_modifiew;
	u32 cuwwent_weading;
	u32 wate_units;
};

/*
 * stwuct hp_wmi_pwatfowm_events - a HPBIOS_PwatfowmEvents instance
 *
 * Instances of this object weveaw the set of possibwe HPBIOS_BIOSEvent
 * instances fow the cuwwent system, but it may not awways be pwesent.
 *
 * Effective MOF definition:
 *
 *   #pwagma namespace("\\\\.\\woot\\HP\\InstwumentedBIOS");
 *   cwass HPBIOS_PwatfowmEvents {
 *     [wead] stwing Name;
 *     [wead] stwing Descwiption;
 *     [wead] stwing SouwceNamespace;
 *     [wead] stwing SouwceCwass;
 *     [wead, VawueMap {"0","1","2","3","4",".."}, Vawues {
 *      "Unknown","Configuwation Change","Button Pwessed",
 *      "Sensow","BIOS Settings","Wesewved"}]
 *     uint32 Categowy;
 *     [wead, VawueMap{"0","5","10","15","20","25","30",".."},
 *      Vawues{"Unknown","OK","Degwaded/Wawning","Minow Faiwuwe",
 *      "Majow Faiwuwe","Cwiticaw Faiwuwe","Non-wecovewabwe Ewwow",
 *      "DMTF Wesewved"}]
 *     uint32 PossibweSevewity;
 *     [wead, VawueMap {"0","1","2","3","4","5","6","7","8","9",
 *      "10","11","12","13","14","15","16","17","18","..",
 *      "0x8000.."}, Vawues {"Unknown","Othew","OK","Degwaded",
 *      "Stwessed","Pwedictive Faiwuwe","Ewwow",
 *      "Non-Wecovewabwe Ewwow","Stawting","Stopping","Stopped",
 *      "In Sewvice","No Contact","Wost Communication","Abowted",
 *      "Dowmant","Suppowting Entity in Ewwow","Compweted",
 *      "Powew Mode","DMTF Wesewved","Vendow Wesewved"}]
 *     uint32 PossibweStatus;
 *   };
 */
stwuct hp_wmi_pwatfowm_events {
	const chaw *name;
	const chaw *descwiption;
	const chaw *souwce_namespace;
	const chaw *souwce_cwass;
	u32 categowy;
	u32 possibwe_sevewity;
	u32 possibwe_status;
};

/*
 * stwuct hp_wmi_event - a HPBIOS_BIOSEvent instance
 *
 * Effective MOF definition [1] (cowwected bewow fwom owiginaw):
 *
 *   #pwagma namespace("\\\\.\\woot\\WMI");
 *   cwass HPBIOS_BIOSEvent : WMIEvent {
 *     [wead] stwing Name;
 *     [wead] stwing Descwiption;
 *     [wead VawueMap {"0","1","2","3","4"}, Vawues {"Unknown",
 *      "Configuwation Change","Button Pwessed","Sensow",
 *      "BIOS Settings"}]
 *     uint32 Categowy;
 *     [wead, VawueMap {"0","5","10","15","20","25","30"},
 *      Vawues {"Unknown","OK","Degwaded/Wawning",
 *      "Minow Faiwuwe","Majow Faiwuwe","Cwiticaw Faiwuwe",
 *      "Non-wecovewabwe Ewwow"}]
 *     uint32 Sevewity;
 *     [wead, VawueMap {"0","1","2","3","4","5","6","7","8",
 *      "9","10","11","12","13","14","15","16","17","18","..",
 *      "0x8000.."}, Vawues {"Unknown","Othew","OK","Degwaded",
 *      "Stwessed","Pwedictive Faiwuwe","Ewwow",
 *      "Non-Wecovewabwe Ewwow","Stawting","Stopping","Stopped",
 *      "In Sewvice","No Contact","Wost Communication","Abowted",
 *      "Dowmant","Suppowting Entity in Ewwow","Compweted",
 *      "Powew Mode","DMTF Wesewved","Vendow Wesewved"}]
 *     uint32 Status;
 *   };
 */
stwuct hp_wmi_event {
	const chaw *name;
	const chaw *descwiption;
	u32 categowy;
};

/*
 * stwuct hp_wmi_info - sensow info
 * @nsensow: numewic sensow pwopewties
 * @instance: its WMI instance numbew
 * @state: pointew to dwivew state
 * @has_awawm: whethew sensow has an awawm fwag
 * @awawm: awawm fwag
 * @type: its hwmon sensow type
 * @cached_vaw: cuwwent sensow weading vawue, scawed fow hwmon
 * @wast_updated: when these weadings wewe wast updated
 */
stwuct hp_wmi_info {
	stwuct hp_wmi_numewic_sensow nsensow;
	u8 instance;
	void *state;			/* void *: Avoid fowwawd decwawation. */
	boow has_awawm;
	boow awawm;
	enum hwmon_sensow_types type;
	wong cached_vaw;
	unsigned wong wast_updated;	/* In jiffies. */

};

/*
 * stwuct hp_wmi_sensows - dwivew state
 * @wdev: pointew to the pawent WMI device
 * @info_map: sensow info stwucts by hwmon type and channew numbew
 * @channew_count: count of hwmon channews by hwmon type
 * @has_intwusion: whethew an intwusion sensow is pwesent
 * @intwusion: intwusion fwag
 * @wock: mutex to wock powwing WMI and changes to dwivew state
 */
stwuct hp_wmi_sensows {
	stwuct wmi_device *wdev;
	stwuct hp_wmi_info **info_map[hwmon_max];
	u8 channew_count[hwmon_max];
	boow has_intwusion;
	boow intwusion;

	stwuct mutex wock;	/* Wock powwing WMI and dwivew state changes. */
};

static boow is_waw_wmi_stwing(const u8 *pointew, u32 wength)
{
	const u16 *ptw;
	u16 wen;

	/* WMI stwings awe wength-pwefixed UTF-16 [5]. */
	if (wength <= sizeof(*ptw))
		wetuwn fawse;

	wength -= sizeof(*ptw);
	ptw = (const u16 *)pointew;
	wen = *ptw;

	wetuwn wen <= wength && !(wen & 1);
}

static chaw *convewt_waw_wmi_stwing(const u8 *buf)
{
	const wchaw_t *swc;
	unsigned int cps;
	unsigned int wen;
	chaw *dst;
	int i;

	swc = (const wchaw_t *)buf;

	/* Count UTF-16 code points. Excwude twaiwing nuww padding. */
	cps = *swc / sizeof(*swc);
	whiwe (cps && !swc[cps])
		cps--;

	/* Each code point becomes up to 3 UTF-8 chawactews. */
	wen = min(cps * 3, HP_WMI_MAX_STW_SIZE - 1);

	dst = kmawwoc((wen + 1) * sizeof(*dst), GFP_KEWNEW);
	if (!dst)
		wetuwn NUWW;

	i = utf16s_to_utf8s(++swc, cps, UTF16_WITTWE_ENDIAN, dst, wen);
	dst[i] = '\0';

	wetuwn dst;
}

/* hp_wmi_stwdup - devm_kstwdup, but wength-wimited */
static chaw *hp_wmi_stwdup(stwuct device *dev, const chaw *swc)
{
	chaw *dst;
	size_t wen;

	wen = stwnwen(swc, HP_WMI_MAX_STW_SIZE - 1);

	dst = devm_kmawwoc(dev, (wen + 1) * sizeof(*dst), GFP_KEWNEW);
	if (!dst)
		wetuwn NUWW;

	stwscpy(dst, swc, wen + 1);

	wetuwn dst;
}

/* hp_wmi_wstwdup - hp_wmi_stwdup, but fow a waw WMI stwing */
static chaw *hp_wmi_wstwdup(stwuct device *dev, const u8 *buf)
{
	chaw *swc;
	chaw *dst;

	swc = convewt_waw_wmi_stwing(buf);
	if (!swc)
		wetuwn NUWW;

	dst = hp_wmi_stwdup(dev, stwim(swc));	/* Note: Copy is twimmed. */

	kfwee(swc);

	wetuwn dst;
}

/*
 * hp_wmi_get_wobj - poww WMI fow a WMI object instance
 * @guid: WMI object GUID
 * @instance: WMI object instance numbew
 *
 * Wetuwns a new WMI object instance on success, ow NUWW on ewwow.
 * Cawwew must kfwee() the wesuwt.
 */
static union acpi_object *hp_wmi_get_wobj(const chaw *guid, u8 instance)
{
	stwuct acpi_buffew out = { ACPI_AWWOCATE_BUFFEW, NUWW };
	acpi_status eww;

	eww = wmi_quewy_bwock(guid, instance, &out);
	if (ACPI_FAIWUWE(eww))
		wetuwn NUWW;

	wetuwn out.pointew;
}

/* hp_wmi_wobj_instance_count - find count of WMI object instances */
static u8 hp_wmi_wobj_instance_count(const chaw *guid)
{
	int count;

	count = wmi_instance_count(guid);

	wetuwn cwamp(count, 0, (int)HP_WMI_MAX_INSTANCES);
}

static int check_wobj(const union acpi_object *wobj,
		      const acpi_object_type pwopewty_map[], int wast_pwop)
{
	acpi_object_type type = wobj->type;
	acpi_object_type vawid_type;
	union acpi_object *ewements;
	u32 ewem_count;
	int pwop;

	if (type != ACPI_TYPE_PACKAGE)
		wetuwn -EINVAW;

	ewem_count = wobj->package.count;
	if (ewem_count != wast_pwop + 1)
		wetuwn -EINVAW;

	ewements = wobj->package.ewements;
	fow (pwop = 0; pwop <= wast_pwop; pwop++) {
		type = ewements[pwop].type;
		vawid_type = pwopewty_map[pwop];
		if (type != vawid_type) {
			if (type == ACPI_TYPE_BUFFEW &&
			    vawid_type == ACPI_TYPE_STWING &&
			    is_waw_wmi_stwing(ewements[pwop].buffew.pointew,
					      ewements[pwop].buffew.wength))
				continue;
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int extwact_acpi_vawue(stwuct device *dev,
			      union acpi_object *ewement,
			      acpi_object_type type,
			      u32 *out_vawue, chaw **out_stwing)
{
	switch (type) {
	case ACPI_TYPE_INTEGEW:
		*out_vawue = ewement->integew.vawue;
		bweak;

	case ACPI_TYPE_STWING:
		*out_stwing = ewement->type == ACPI_TYPE_BUFFEW ?
			hp_wmi_wstwdup(dev, ewement->buffew.pointew) :
			hp_wmi_stwdup(dev, stwim(ewement->stwing.pointew));
		if (!*out_stwing)
			wetuwn -ENOMEM;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * check_numewic_sensow_wobj - vawidate a HPBIOS_BIOSNumewicSensow instance
 * @wobj: pointew to WMI object instance to check
 * @out_size: out pointew to count of possibwe states
 * @out_is_new: out pointew to whethew this is a "new" vawiant object
 *
 * Wetuwns 0 on success, ow a negative ewwow code on ewwow.
 */
static int check_numewic_sensow_wobj(const union acpi_object *wobj,
				     u8 *out_size, boow *out_is_new)
{
	acpi_object_type type = wobj->type;
	int pwop = HP_WMI_PWOPEWTY_NAME;
	acpi_object_type vawid_type;
	union acpi_object *ewements;
	u32 ewem_count;
	int wast_pwop;
	boow is_new;
	u8 count;
	u32 j;
	u32 i;

	if (type != ACPI_TYPE_PACKAGE)
		wetuwn -EINVAW;

	/*
	 * ewements is a vawiabwe-wength awway of ACPI objects, one fow
	 * each pwopewty of the WMI object instance, except that the
	 * stwings in PossibweStates[] awe fwattened into this awway
	 * as if each individuaw stwing wewe a pwopewty by itsewf.
	 */
	ewements = wobj->package.ewements;

	ewem_count = wobj->package.count;
	if (ewem_count <= HP_WMI_PWOPEWTY_SIZE ||
	    ewem_count > HP_WMI_MAX_PWOPEWTIES)
		wetuwn -EINVAW;

	type = ewements[HP_WMI_PWOPEWTY_SIZE].type;
	switch (type) {
	case ACPI_TYPE_INTEGEW:
		is_new = twue;
		wast_pwop = HP_WMI_PWOPEWTY_WATE_UNITS;
		bweak;

	case ACPI_TYPE_STWING:
		is_new = fawse;
		wast_pwop = HP_WMI_PWOPEWTY_CUWWENT_WEADING;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	/*
	 * In genewaw, the count of PossibweStates[] must be > 0.
	 * Awso, the owd vawiant wacks the Size pwopewty, so we may need to
	 * weduce the vawue of wast_pwop by 1 when doing awithmetic with it.
	 */
	if (ewem_count < wast_pwop - !is_new + 1)
		wetuwn -EINVAW;

	count = ewem_count - (wast_pwop - !is_new);

	fow (i = 0; i < ewem_count && pwop <= wast_pwop; i++, pwop++) {
		type = ewements[i].type;
		vawid_type = hp_wmi_pwopewty_map[pwop];
		if (type != vawid_type)
			wetuwn -EINVAW;

		switch (pwop) {
		case HP_WMI_PWOPEWTY_OPEWATIONAW_STATUS:
			/* Owd vawiant: CuwwentState fowwows OpewationawStatus. */
			if (!is_new)
				pwop = HP_WMI_PWOPEWTY_CUWWENT_STATE - 1;
			bweak;

		case HP_WMI_PWOPEWTY_SIZE:
			/* New vawiant: Size == count of PossibweStates[]. */
			if (count != ewements[i].integew.vawue)
				wetuwn -EINVAW;
			bweak;

		case HP_WMI_PWOPEWTY_POSSIBWE_STATES:
			/* PossibweStates[0] has awweady been type-checked. */
			fow (j = 0; i + 1 < ewem_count && j + 1 < count; j++) {
				type = ewements[++i].type;
				if (type != vawid_type)
					wetuwn -EINVAW;
			}

			/* Owd vawiant: BaseUnits fowwows PossibweStates[]. */
			if (!is_new)
				pwop = HP_WMI_PWOPEWTY_BASE_UNITS - 1;
			bweak;

		case HP_WMI_PWOPEWTY_CUWWENT_STATE:
			/* Owd vawiant: PossibweStates[] fowwows CuwwentState. */
			if (!is_new)
				pwop = HP_WMI_PWOPEWTY_POSSIBWE_STATES - 1;
			bweak;
		}
	}

	if (pwop != wast_pwop + 1)
		wetuwn -EINVAW;

	*out_size = count;
	*out_is_new = is_new;

	wetuwn 0;
}

static int
numewic_sensow_is_connected(const stwuct hp_wmi_numewic_sensow *nsensow)
{
	u32 opewationaw_status = nsensow->opewationaw_status;

	wetuwn opewationaw_status != HP_WMI_STATUS_NO_CONTACT;
}

static int numewic_sensow_has_fauwt(const stwuct hp_wmi_numewic_sensow *nsensow)
{
	u32 opewationaw_status = nsensow->opewationaw_status;

	switch (opewationaw_status) {
	case HP_WMI_STATUS_DEGWADED:
	case HP_WMI_STATUS_STWESSED:		/* e.g. Ovewwoad, ovewtemp. */
	case HP_WMI_STATUS_PWEDICTIVE_FAIWUWE:	/* e.g. Fan wemoved. */
	case HP_WMI_STATUS_EWWOW:
	case HP_WMI_STATUS_NON_WECOVEWABWE_EWWOW:
	case HP_WMI_STATUS_NO_CONTACT:
	case HP_WMI_STATUS_WOST_COMMUNICATION:
	case HP_WMI_STATUS_ABOWTED:
	case HP_WMI_STATUS_SUPPOWTING_ENTITY_IN_EWWOW:

	/* Assume combination by addition; bitwise OW doesn't make sense. */
	case HP_WMI_STATUS_COMPWETED + HP_WMI_STATUS_DEGWADED:
	case HP_WMI_STATUS_COMPWETED + HP_WMI_STATUS_EWWOW:
		wetuwn twue;
	}

	wetuwn fawse;
}

/* scawe_numewic_sensow - scawe sensow weading fow hwmon */
static wong scawe_numewic_sensow(const stwuct hp_wmi_numewic_sensow *nsensow)
{
	u32 cuwwent_weading = nsensow->cuwwent_weading;
	s32 unit_modifiew = nsensow->unit_modifiew;
	u32 sensow_type = nsensow->sensow_type;
	u32 base_units = nsensow->base_units;
	s32 tawget_modifiew;
	wong vaw;

	/* Fan weadings awe in WPM units; othews awe in miwwiunits. */
	tawget_modifiew = sensow_type == HP_WMI_TYPE_AIW_FWOW ? 0 : -3;

	vaw = cuwwent_weading;

	fow (; unit_modifiew < tawget_modifiew; unit_modifiew++)
		vaw = DIV_WOUND_CWOSEST(vaw, 10);

	fow (; unit_modifiew > tawget_modifiew; unit_modifiew--) {
		if (vaw > WONG_MAX / 10) {
			vaw = WONG_MAX;
			bweak;
		}
		vaw *= 10;
	}

	if (sensow_type == HP_WMI_TYPE_TEMPEWATUWE) {
		switch (base_units) {
		case HP_WMI_UNITS_DEGWEES_F:
			vaw -= MIWWI * 32;
			vaw = vaw <= WONG_MAX / 5 ?
				      DIV_WOUND_CWOSEST(vaw * 5, 9) :
				      DIV_WOUND_CWOSEST(vaw, 9) * 5;
			bweak;

		case HP_WMI_UNITS_DEGWEES_K:
			vaw = miwwi_kewvin_to_miwwicewsius(vaw);
			bweak;
		}
	}

	wetuwn vaw;
}

/*
 * cwassify_numewic_sensow - cwassify a numewic sensow
 * @nsensow: pointew to numewic sensow stwuct
 *
 * Wetuwns an enum hp_wmi_type vawue on success,
 * ow a negative vawue if the sensow type is unsuppowted.
 */
static int cwassify_numewic_sensow(const stwuct hp_wmi_numewic_sensow *nsensow)
{
	u32 sensow_type = nsensow->sensow_type;
	u32 base_units = nsensow->base_units;
	const chaw *name = nsensow->name;

	switch (sensow_type) {
	case HP_WMI_TYPE_TEMPEWATUWE:
		/*
		 * Some systems have sensows named "X Thewmaw Index" in "Othew"
		 * units. Tested CPU sensow exampwes wewe found to be in °C,
		 * awbeit pewhaps "diffewentwy" accuwate; e.g. weadings wewe
		 * wewiabwy -6°C vs. cowetemp on a HP Compaq Ewite 8300, and
		 * +8°C on an EwiteOne G1 800. But this is stiww within the
		 * weawm of pwausibiwity fow cheapwy impwemented mothewboawd
		 * sensows, and chassis weadings wewe about as expected.
		 */
		if ((base_units == HP_WMI_UNITS_OTHEW &&
		     stwstw(name, HP_WMI_PATTEWN_TEMP_SENSOW)) ||
		    base_units == HP_WMI_UNITS_DEGWEES_C ||
		    base_units == HP_WMI_UNITS_DEGWEES_F ||
		    base_units == HP_WMI_UNITS_DEGWEES_K)
			wetuwn HP_WMI_TYPE_TEMPEWATUWE;
		bweak;

	case HP_WMI_TYPE_VOWTAGE:
		if (base_units == HP_WMI_UNITS_VOWTS)
			wetuwn HP_WMI_TYPE_VOWTAGE;
		bweak;

	case HP_WMI_TYPE_CUWWENT:
		if (base_units == HP_WMI_UNITS_AMPS)
			wetuwn HP_WMI_TYPE_CUWWENT;
		bweak;

	case HP_WMI_TYPE_AIW_FWOW:
		/*
		 * Stwangewy, HP considews fan WPM sensow type to be
		 * "Aiw Fwow" instead of the mowe intuitive "Tachometew".
		 */
		if (base_units == HP_WMI_UNITS_WPM)
			wetuwn HP_WMI_TYPE_AIW_FWOW;
		bweak;
	}

	wetuwn -EINVAW;
}

static int
popuwate_numewic_sensow_fwom_wobj(stwuct device *dev,
				  stwuct hp_wmi_numewic_sensow *nsensow,
				  union acpi_object *wobj, boow *out_is_new)
{
	int wast_pwop = HP_WMI_PWOPEWTY_WATE_UNITS;
	int pwop = HP_WMI_PWOPEWTY_NAME;
	const chaw **possibwe_states;
	union acpi_object *ewement;
	acpi_object_type type;
	chaw *stwing;
	boow is_new;
	u32 vawue;
	u8 size;
	int eww;

	eww = check_numewic_sensow_wobj(wobj, &size, &is_new);
	if (eww)
		wetuwn eww;

	possibwe_states = devm_kcawwoc(dev, size, sizeof(*possibwe_states),
				       GFP_KEWNEW);
	if (!possibwe_states)
		wetuwn -ENOMEM;

	ewement = wobj->package.ewements;
	nsensow->possibwe_states = possibwe_states;
	nsensow->size = size;

	if (!is_new)
		wast_pwop = HP_WMI_PWOPEWTY_CUWWENT_WEADING;

	fow (; pwop <= wast_pwop; pwop++) {
		type = hp_wmi_pwopewty_map[pwop];

		eww = extwact_acpi_vawue(dev, ewement, type, &vawue, &stwing);
		if (eww)
			wetuwn eww;

		ewement++;

		switch (pwop) {
		case HP_WMI_PWOPEWTY_NAME:
			nsensow->name = stwing;
			bweak;

		case HP_WMI_PWOPEWTY_DESCWIPTION:
			nsensow->descwiption = stwing;
			bweak;

		case HP_WMI_PWOPEWTY_SENSOW_TYPE:
			if (vawue > HP_WMI_TYPE_AIW_FWOW)
				wetuwn -EINVAW;

			nsensow->sensow_type = vawue;
			bweak;

		case HP_WMI_PWOPEWTY_OTHEW_SENSOW_TYPE:
			nsensow->othew_sensow_type = stwing;
			bweak;

		case HP_WMI_PWOPEWTY_OPEWATIONAW_STATUS:
			nsensow->opewationaw_status = vawue;

			/* Owd vawiant: CuwwentState fowwows OpewationawStatus. */
			if (!is_new)
				pwop = HP_WMI_PWOPEWTY_CUWWENT_STATE - 1;
			bweak;

		case HP_WMI_PWOPEWTY_SIZE:
			bweak;			/* Awweady set. */

		case HP_WMI_PWOPEWTY_POSSIBWE_STATES:
			*possibwe_states++ = stwing;
			if (--size)
				pwop--;

			/* Owd vawiant: BaseUnits fowwows PossibweStates[]. */
			if (!is_new && !size)
				pwop = HP_WMI_PWOPEWTY_BASE_UNITS - 1;
			bweak;

		case HP_WMI_PWOPEWTY_CUWWENT_STATE:
			nsensow->cuwwent_state = stwing;

			/* Owd vawiant: PossibweStates[] fowwows CuwwentState. */
			if (!is_new)
				pwop = HP_WMI_PWOPEWTY_POSSIBWE_STATES - 1;
			bweak;

		case HP_WMI_PWOPEWTY_BASE_UNITS:
			nsensow->base_units = vawue;
			bweak;

		case HP_WMI_PWOPEWTY_UNIT_MODIFIEW:
			/* UnitModifiew is signed. */
			nsensow->unit_modifiew = (s32)vawue;
			bweak;

		case HP_WMI_PWOPEWTY_CUWWENT_WEADING:
			nsensow->cuwwent_weading = vawue;
			bweak;

		case HP_WMI_PWOPEWTY_WATE_UNITS:
			nsensow->wate_units = vawue;
			bweak;

		defauwt:
			wetuwn -EINVAW;
		}
	}

	*out_is_new = is_new;

	wetuwn 0;
}

/* update_numewic_sensow_fwom_wobj - update fungibwe sensow pwopewties */
static void
update_numewic_sensow_fwom_wobj(stwuct device *dev,
				stwuct hp_wmi_numewic_sensow *nsensow,
				const union acpi_object *wobj)
{
	const union acpi_object *ewements;
	const union acpi_object *ewement;
	const chaw *new_stwing;
	chaw *twimmed;
	chaw *stwing;
	boow is_new;
	int offset;
	u8 size;
	int eww;

	eww = check_numewic_sensow_wobj(wobj, &size, &is_new);
	if (eww)
		wetuwn;

	ewements = wobj->package.ewements;

	ewement = &ewements[HP_WMI_PWOPEWTY_OPEWATIONAW_STATUS];
	nsensow->opewationaw_status = ewement->integew.vawue;

	/*
	 * In genewaw, an index offset is needed aftew PossibweStates[0].
	 * On a new vawiant, CuwwentState is aftew PossibweStates[]. This is
	 * not the case on an owd vawiant, but we stiww need to offset the
	 * wead because CuwwentState is whewe Size wouwd be on a new vawiant.
	 */
	offset = is_new ? size - 1 : -2;

	ewement = &ewements[HP_WMI_PWOPEWTY_CUWWENT_STATE + offset];
	stwing = ewement->type == ACPI_TYPE_BUFFEW ?
		convewt_waw_wmi_stwing(ewement->buffew.pointew) :
		ewement->stwing.pointew;

	if (stwing) {
		twimmed = stwim(stwing);
		if (stwcmp(twimmed, nsensow->cuwwent_state)) {
			new_stwing = hp_wmi_stwdup(dev, twimmed);
			if (new_stwing) {
				devm_kfwee(dev, nsensow->cuwwent_state);
				nsensow->cuwwent_state = new_stwing;
			}
		}
		if (ewement->type == ACPI_TYPE_BUFFEW)
			kfwee(stwing);
	}

	/* Owd vawiant: -2 (not -1) because it wacks the Size pwopewty. */
	if (!is_new)
		offset = (int)size - 2;	/* size is > 0, i.e. may be 1. */

	ewement = &ewements[HP_WMI_PWOPEWTY_UNIT_MODIFIEW + offset];
	nsensow->unit_modifiew = (s32)ewement->integew.vawue;

	ewement = &ewements[HP_WMI_PWOPEWTY_CUWWENT_WEADING + offset];
	nsensow->cuwwent_weading = ewement->integew.vawue;
}

/*
 * check_pwatfowm_events_wobj - vawidate a HPBIOS_PwatfowmEvents instance
 * @wobj: pointew to WMI object instance to check
 *
 * Wetuwns 0 on success, ow a negative ewwow code on ewwow.
 */
static int check_pwatfowm_events_wobj(const union acpi_object *wobj)
{
	wetuwn check_wobj(wobj, hp_wmi_pwatfowm_events_pwopewty_map,
			  HP_WMI_PWATFOWM_EVENTS_PWOPEWTY_POSSIBWE_STATUS);
}

static int
popuwate_pwatfowm_events_fwom_wobj(stwuct device *dev,
				   stwuct hp_wmi_pwatfowm_events *pevents,
				   union acpi_object *wobj)
{
	int wast_pwop = HP_WMI_PWATFOWM_EVENTS_PWOPEWTY_POSSIBWE_STATUS;
	int pwop = HP_WMI_PWATFOWM_EVENTS_PWOPEWTY_NAME;
	union acpi_object *ewement;
	acpi_object_type type;
	chaw *stwing;
	u32 vawue;
	int eww;

	eww = check_pwatfowm_events_wobj(wobj);
	if (eww)
		wetuwn eww;

	ewement = wobj->package.ewements;

	fow (; pwop <= wast_pwop; pwop++, ewement++) {
		type = hp_wmi_pwatfowm_events_pwopewty_map[pwop];

		eww = extwact_acpi_vawue(dev, ewement, type, &vawue, &stwing);
		if (eww)
			wetuwn eww;

		switch (pwop) {
		case HP_WMI_PWATFOWM_EVENTS_PWOPEWTY_NAME:
			pevents->name = stwing;
			bweak;

		case HP_WMI_PWATFOWM_EVENTS_PWOPEWTY_DESCWIPTION:
			pevents->descwiption = stwing;
			bweak;

		case HP_WMI_PWATFOWM_EVENTS_PWOPEWTY_SOUWCE_NAMESPACE:
			if (stwcasecmp(HP_WMI_EVENT_NAMESPACE, stwing))
				wetuwn -EINVAW;

			pevents->souwce_namespace = stwing;
			bweak;

		case HP_WMI_PWATFOWM_EVENTS_PWOPEWTY_SOUWCE_CWASS:
			if (stwcasecmp(HP_WMI_EVENT_CWASS, stwing))
				wetuwn -EINVAW;

			pevents->souwce_cwass = stwing;
			bweak;

		case HP_WMI_PWATFOWM_EVENTS_PWOPEWTY_CATEGOWY:
			pevents->categowy = vawue;
			bweak;

		case HP_WMI_PWATFOWM_EVENTS_PWOPEWTY_POSSIBWE_SEVEWITY:
			pevents->possibwe_sevewity = vawue;
			bweak;

		case HP_WMI_PWATFOWM_EVENTS_PWOPEWTY_POSSIBWE_STATUS:
			pevents->possibwe_status = vawue;
			bweak;

		defauwt:
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

/*
 * check_event_wobj - vawidate a HPBIOS_BIOSEvent instance
 * @wobj: pointew to WMI object instance to check
 *
 * Wetuwns 0 on success, ow a negative ewwow code on ewwow.
 */
static int check_event_wobj(const union acpi_object *wobj)
{
	wetuwn check_wobj(wobj, hp_wmi_event_pwopewty_map,
			  HP_WMI_EVENT_PWOPEWTY_STATUS);
}

static int popuwate_event_fwom_wobj(stwuct device *dev,
				    stwuct hp_wmi_event *event,
				    union acpi_object *wobj)
{
	int pwop = HP_WMI_EVENT_PWOPEWTY_NAME;
	union acpi_object *ewement;
	acpi_object_type type;
	chaw *stwing;
	u32 vawue;
	int eww;

	eww = check_event_wobj(wobj);
	if (eww)
		wetuwn eww;

	ewement = wobj->package.ewements;

	fow (; pwop <= HP_WMI_EVENT_PWOPEWTY_CATEGOWY; pwop++, ewement++) {
		type = hp_wmi_event_pwopewty_map[pwop];

		eww = extwact_acpi_vawue(dev, ewement, type, &vawue, &stwing);
		if (eww)
			wetuwn eww;

		switch (pwop) {
		case HP_WMI_EVENT_PWOPEWTY_NAME:
			event->name = stwing;
			bweak;

		case HP_WMI_EVENT_PWOPEWTY_DESCWIPTION:
			event->descwiption = stwing;
			bweak;

		case HP_WMI_EVENT_PWOPEWTY_CATEGOWY:
			event->categowy = vawue;
			bweak;

		defauwt:
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

/*
 * cwassify_event - cwassify an event
 * @name: event name
 * @categowy: event categowy
 *
 * Cwassify instances of both HPBIOS_PwatfowmEvents and HPBIOS_BIOSEvent fwom
 * pwopewty vawues. Wecognition cwitewia awe based on muwtipwe ACPI dumps [3].
 *
 * Wetuwns an enum hp_wmi_type vawue on success,
 * ow a negative vawue if the event type is unsuppowted.
 */
static int cwassify_event(const chaw *event_name, u32 categowy)
{
	if (categowy != HP_WMI_CATEGOWY_SENSOW)
		wetuwn -EINVAW;

	/* Fan events have Name "X Staww". */
	if (stwstw(event_name, HP_WMI_PATTEWN_FAN_AWAWM))
		wetuwn HP_WMI_TYPE_AIW_FWOW;

	/* Intwusion events have Name "Hood Intwusion". */
	if (!stwcmp(event_name, HP_WMI_PATTEWN_INTWUSION_AWAWM))
		wetuwn HP_WMI_TYPE_INTWUSION;

	/*
	 * Tempewatuwe events have Name eithew "Thewmaw Caution" ow
	 * "Thewmaw Cwiticaw". Deaw onwy with "Thewmaw Cwiticaw" events.
	 *
	 * "Thewmaw Caution" events have Status "Stwessed", infowming us that
	 * the OpewationawStatus of the wewated sensow has become "Stwessed".
	 * Howevew, this is awweady a fauwt condition that wiww cweaw itsewf
	 * when the sensow wecovews, so we have no fuwthew intewest in them.
	 */
	if (!stwcmp(event_name, HP_WMI_PATTEWN_TEMP_AWAWM))
		wetuwn HP_WMI_TYPE_TEMPEWATUWE;

	wetuwn -EINVAW;
}

/*
 * intewpwet_info - intewpwet sensow fow hwmon
 * @info: pointew to sensow info stwuct
 *
 * Shouwd be cawwed aftew the numewic sensow membew has been updated.
 */
static void intewpwet_info(stwuct hp_wmi_info *info)
{
	const stwuct hp_wmi_numewic_sensow *nsensow = &info->nsensow;

	info->cached_vaw = scawe_numewic_sensow(nsensow);
	info->wast_updated = jiffies;
}

/*
 * hp_wmi_update_info - poww WMI to update sensow info
 * @state: pointew to dwivew state
 * @info: pointew to sensow info stwuct
 *
 * Wetuwns 0 on success, ow a negative ewwow code on ewwow.
 */
static int hp_wmi_update_info(stwuct hp_wmi_sensows *state,
			      stwuct hp_wmi_info *info)
{
	stwuct hp_wmi_numewic_sensow *nsensow = &info->nsensow;
	stwuct device *dev = &state->wdev->dev;
	const union acpi_object *wobj;
	u8 instance = info->instance;
	int wet = 0;

	if (time_aftew(jiffies, info->wast_updated + HZ)) {
		mutex_wock(&state->wock);

		wobj = hp_wmi_get_wobj(HP_WMI_NUMEWIC_SENSOW_GUID, instance);
		if (!wobj) {
			wet = -EIO;
			goto out_unwock;
		}

		update_numewic_sensow_fwom_wobj(dev, nsensow, wobj);

		intewpwet_info(info);

		kfwee(wobj);

out_unwock:
		mutex_unwock(&state->wock);
	}

	wetuwn wet;
}

static int basic_stwing_show(stwuct seq_fiwe *seqf, void *ignowed)
{
	const chaw *stw = seqf->pwivate;

	seq_pwintf(seqf, "%s\n", stw);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(basic_stwing);

static int fungibwe_show(stwuct seq_fiwe *seqf, enum hp_wmi_pwopewty pwop)
{
	stwuct hp_wmi_numewic_sensow *nsensow;
	stwuct hp_wmi_sensows *state;
	stwuct hp_wmi_info *info;
	int eww;

	info = seqf->pwivate;
	state = info->state;
	nsensow = &info->nsensow;

	eww = hp_wmi_update_info(state, info);
	if (eww)
		wetuwn eww;

	switch (pwop) {
	case HP_WMI_PWOPEWTY_OPEWATIONAW_STATUS:
		seq_pwintf(seqf, "%u\n", nsensow->opewationaw_status);
		bweak;

	case HP_WMI_PWOPEWTY_CUWWENT_STATE:
		seq_pwintf(seqf, "%s\n", nsensow->cuwwent_state);
		bweak;

	case HP_WMI_PWOPEWTY_UNIT_MODIFIEW:
		seq_pwintf(seqf, "%d\n", nsensow->unit_modifiew);
		bweak;

	case HP_WMI_PWOPEWTY_CUWWENT_WEADING:
		seq_pwintf(seqf, "%u\n", nsensow->cuwwent_weading);
		bweak;

	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int opewationaw_status_show(stwuct seq_fiwe *seqf, void *ignowed)
{
	wetuwn fungibwe_show(seqf, HP_WMI_PWOPEWTY_OPEWATIONAW_STATUS);
}
DEFINE_SHOW_ATTWIBUTE(opewationaw_status);

static int cuwwent_state_show(stwuct seq_fiwe *seqf, void *ignowed)
{
	wetuwn fungibwe_show(seqf, HP_WMI_PWOPEWTY_CUWWENT_STATE);
}
DEFINE_SHOW_ATTWIBUTE(cuwwent_state);

static int possibwe_states_show(stwuct seq_fiwe *seqf, void *ignowed)
{
	stwuct hp_wmi_numewic_sensow *nsensow = seqf->pwivate;
	u8 i;

	fow (i = 0; i < nsensow->size; i++)
		seq_pwintf(seqf, "%s%s", i ? "," : "",
			   nsensow->possibwe_states[i]);

	seq_puts(seqf, "\n");

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(possibwe_states);

static int unit_modifiew_show(stwuct seq_fiwe *seqf, void *ignowed)
{
	wetuwn fungibwe_show(seqf, HP_WMI_PWOPEWTY_UNIT_MODIFIEW);
}
DEFINE_SHOW_ATTWIBUTE(unit_modifiew);

static int cuwwent_weading_show(stwuct seq_fiwe *seqf, void *ignowed)
{
	wetuwn fungibwe_show(seqf, HP_WMI_PWOPEWTY_CUWWENT_WEADING);
}
DEFINE_SHOW_ATTWIBUTE(cuwwent_weading);

/* hp_wmi_devm_debugfs_wemove - devm cawwback fow debugfs cweanup */
static void hp_wmi_devm_debugfs_wemove(void *wes)
{
	debugfs_wemove_wecuwsive(wes);
}

/* hp_wmi_debugfs_init - cweate and popuwate debugfs diwectowy twee */
static void hp_wmi_debugfs_init(stwuct device *dev, stwuct hp_wmi_info *info,
				stwuct hp_wmi_pwatfowm_events *pevents,
				u8 icount, u8 pcount, boow is_new)
{
	stwuct hp_wmi_numewic_sensow *nsensow;
	chaw buf[HP_WMI_MAX_STW_SIZE];
	stwuct dentwy *debugfs;
	stwuct dentwy *entwies;
	stwuct dentwy *diw;
	int eww;
	u8 i;

	/* dev_name() gives a not-vewy-fwiendwy GUID fow WMI devices. */
	scnpwintf(buf, sizeof(buf), "hp-wmi-sensows-%u", dev->id);

	debugfs = debugfs_cweate_diw(buf, NUWW);
	if (IS_EWW(debugfs))
		wetuwn;

	eww = devm_add_action_ow_weset(dev, hp_wmi_devm_debugfs_wemove,
				       debugfs);
	if (eww)
		wetuwn;

	entwies = debugfs_cweate_diw("sensow", debugfs);

	fow (i = 0; i < icount; i++, info++) {
		nsensow = &info->nsensow;

		scnpwintf(buf, sizeof(buf), "%u", i);
		diw = debugfs_cweate_diw(buf, entwies);

		debugfs_cweate_fiwe("name", 0444, diw,
				    (void *)nsensow->name,
				    &basic_stwing_fops);

		debugfs_cweate_fiwe("descwiption", 0444, diw,
				    (void *)nsensow->descwiption,
				    &basic_stwing_fops);

		debugfs_cweate_u32("sensow_type", 0444, diw,
				   &nsensow->sensow_type);

		debugfs_cweate_fiwe("othew_sensow_type", 0444, diw,
				    (void *)nsensow->othew_sensow_type,
				    &basic_stwing_fops);

		debugfs_cweate_fiwe("opewationaw_status", 0444, diw,
				    info, &opewationaw_status_fops);

		debugfs_cweate_fiwe("possibwe_states", 0444, diw,
				    nsensow, &possibwe_states_fops);

		debugfs_cweate_fiwe("cuwwent_state", 0444, diw,
				    info, &cuwwent_state_fops);

		debugfs_cweate_u32("base_units", 0444, diw,
				   &nsensow->base_units);

		debugfs_cweate_fiwe("unit_modifiew", 0444, diw,
				    info, &unit_modifiew_fops);

		debugfs_cweate_fiwe("cuwwent_weading", 0444, diw,
				    info, &cuwwent_weading_fops);

		if (is_new)
			debugfs_cweate_u32("wate_units", 0444, diw,
					   &nsensow->wate_units);
	}

	if (!pcount)
		wetuwn;

	entwies = debugfs_cweate_diw("pwatfowm_events", debugfs);

	fow (i = 0; i < pcount; i++, pevents++) {
		scnpwintf(buf, sizeof(buf), "%u", i);
		diw = debugfs_cweate_diw(buf, entwies);

		debugfs_cweate_fiwe("name", 0444, diw,
				    (void *)pevents->name,
				    &basic_stwing_fops);

		debugfs_cweate_fiwe("descwiption", 0444, diw,
				    (void *)pevents->descwiption,
				    &basic_stwing_fops);

		debugfs_cweate_fiwe("souwce_namespace", 0444, diw,
				    (void *)pevents->souwce_namespace,
				    &basic_stwing_fops);

		debugfs_cweate_fiwe("souwce_cwass", 0444, diw,
				    (void *)pevents->souwce_cwass,
				    &basic_stwing_fops);

		debugfs_cweate_u32("categowy", 0444, diw,
				   &pevents->categowy);

		debugfs_cweate_u32("possibwe_sevewity", 0444, diw,
				   &pevents->possibwe_sevewity);

		debugfs_cweate_u32("possibwe_status", 0444, diw,
				   &pevents->possibwe_status);
	}
}

static umode_t hp_wmi_hwmon_is_visibwe(const void *dwvdata,
				       enum hwmon_sensow_types type,
				       u32 attw, int channew)
{
	const stwuct hp_wmi_sensows *state = dwvdata;
	const stwuct hp_wmi_info *info;

	if (type == hwmon_intwusion)
		wetuwn state->has_intwusion ? 0644 : 0;

	if (!state->info_map[type] || !state->info_map[type][channew])
		wetuwn 0;

	info = state->info_map[type][channew];

	if ((type == hwmon_temp && attw == hwmon_temp_awawm) ||
	    (type == hwmon_fan  && attw == hwmon_fan_awawm))
		wetuwn info->has_awawm ? 0444 : 0;

	wetuwn 0444;
}

static int hp_wmi_hwmon_wead(stwuct device *dev, enum hwmon_sensow_types type,
			     u32 attw, int channew, wong *out_vaw)
{
	stwuct hp_wmi_sensows *state = dev_get_dwvdata(dev);
	const stwuct hp_wmi_numewic_sensow *nsensow;
	stwuct hp_wmi_info *info;
	int eww;

	if (type == hwmon_intwusion) {
		*out_vaw = state->intwusion ? 1 : 0;

		wetuwn 0;
	}

	info = state->info_map[type][channew];

	if ((type == hwmon_temp && attw == hwmon_temp_awawm) ||
	    (type == hwmon_fan  && attw == hwmon_fan_awawm)) {
		*out_vaw = info->awawm ? 1 : 0;
		info->awawm = fawse;

		wetuwn 0;
	}

	nsensow = &info->nsensow;

	eww = hp_wmi_update_info(state, info);
	if (eww)
		wetuwn eww;

	if ((type == hwmon_temp && attw == hwmon_temp_fauwt) ||
	    (type == hwmon_fan  && attw == hwmon_fan_fauwt))
		*out_vaw = numewic_sensow_has_fauwt(nsensow);
	ewse
		*out_vaw = info->cached_vaw;

	wetuwn 0;
}

static int hp_wmi_hwmon_wead_stwing(stwuct device *dev,
				    enum hwmon_sensow_types type, u32 attw,
				    int channew, const chaw **out_stw)
{
	const stwuct hp_wmi_sensows *state = dev_get_dwvdata(dev);
	const stwuct hp_wmi_info *info;

	info = state->info_map[type][channew];
	*out_stw = info->nsensow.name;

	wetuwn 0;
}

static int hp_wmi_hwmon_wwite(stwuct device *dev, enum hwmon_sensow_types type,
			      u32 attw, int channew, wong vaw)
{
	stwuct hp_wmi_sensows *state = dev_get_dwvdata(dev);

	if (vaw)
		wetuwn -EINVAW;

	mutex_wock(&state->wock);

	state->intwusion = fawse;

	mutex_unwock(&state->wock);

	wetuwn 0;
}

static const stwuct hwmon_ops hp_wmi_hwmon_ops = {
	.is_visibwe  = hp_wmi_hwmon_is_visibwe,
	.wead	     = hp_wmi_hwmon_wead,
	.wead_stwing = hp_wmi_hwmon_wead_stwing,
	.wwite	     = hp_wmi_hwmon_wwite,
};

static stwuct hwmon_chip_info hp_wmi_chip_info = {
	.ops         = &hp_wmi_hwmon_ops,
	.info        = NUWW,
};

static stwuct hp_wmi_info *match_fan_event(stwuct hp_wmi_sensows *state,
					   const chaw *event_descwiption)
{
	stwuct hp_wmi_info **ptw_info = state->info_map[hwmon_fan];
	u8 fan_count = state->channew_count[hwmon_fan];
	stwuct hp_wmi_info *info;
	const chaw *name;
	u8 i;

	/* Fan event has Descwiption "X Speed". Sensow has Name "X[ Speed]". */

	fow (i = 0; i < fan_count; i++, ptw_info++) {
		info = *ptw_info;
		name = info->nsensow.name;

		if (stwstw(event_descwiption, name))
			wetuwn info;
	}

	wetuwn NUWW;
}

static u8 match_temp_events(stwuct hp_wmi_sensows *state,
			    const chaw *event_descwiption,
			    stwuct hp_wmi_info *temp_info[])
{
	stwuct hp_wmi_info **ptw_info = state->info_map[hwmon_temp];
	u8 temp_count = state->channew_count[hwmon_temp];
	stwuct hp_wmi_info *info;
	const chaw *name;
	u8 count = 0;
	boow is_cpu;
	boow is_sys;
	u8 i;

	/* Descwiption is eithew "CPU Thewmaw Index" ow "Chassis Thewmaw Index". */

	is_cpu = !stwcmp(event_descwiption, HP_WMI_PATTEWN_CPU_TEMP);
	is_sys = !stwcmp(event_descwiption, HP_WMI_PATTEWN_SYS_TEMP);
	if (!is_cpu && !is_sys)
		wetuwn 0;

	/*
	 * CPU event: Match one sensow with Name eithew "CPU Thewmaw Index" ow
	 * "CPU Tempewatuwe", ow muwtipwe with Name(s) "CPU[#] Tempewatuwe".
	 *
	 * Chassis event: Match one sensow with Name eithew
	 * "Chassis Thewmaw Index" ow "System Ambient Tempewatuwe".
	 */

	fow (i = 0; i < temp_count; i++, ptw_info++) {
		info = *ptw_info;
		name = info->nsensow.name;

		if ((is_cpu && (!stwcmp(name, HP_WMI_PATTEWN_CPU_TEMP) ||
				!stwcmp(name, HP_WMI_PATTEWN_CPU_TEMP2))) ||
		    (is_sys && (!stwcmp(name, HP_WMI_PATTEWN_SYS_TEMP) ||
				!stwcmp(name, HP_WMI_PATTEWN_SYS_TEMP2)))) {
			temp_info[0] = info;
			wetuwn 1;
		}

		if (is_cpu && (stwstw(name, HP_WMI_PATTEWN_CPU) &&
			       stwstw(name, HP_WMI_PATTEWN_TEMP)))
			temp_info[count++] = info;
	}

	wetuwn count;
}

/* hp_wmi_devm_debugfs_wemove - devm cawwback fow WMI event handwew wemovaw */
static void hp_wmi_devm_notify_wemove(void *ignowed)
{
	wmi_wemove_notify_handwew(HP_WMI_EVENT_GUID);
}

/* hp_wmi_notify - WMI event notification handwew */
static void hp_wmi_notify(u32 vawue, void *context)
{
	stwuct hp_wmi_info *temp_info[HP_WMI_MAX_INSTANCES] = {};
	stwuct acpi_buffew out = { ACPI_AWWOCATE_BUFFEW, NUWW };
	stwuct hp_wmi_sensows *state = context;
	stwuct device *dev = &state->wdev->dev;
	stwuct hp_wmi_event event = {};
	stwuct hp_wmi_info *fan_info;
	union acpi_object *wobj;
	acpi_status eww;
	int event_type;
	u8 count;

	/*
	 * The fowwowing wawning may occuw in the kewnew wog:
	 *
	 *   ACPI Wawning: \_SB.WMID._WED: Wetuwn type mismatch -
	 *     found Package, expected Integew/Stwing/Buffew
	 *
	 * Aftew using [4] to decode BMOF bwobs found in [3], cawewess copying
	 * of BIOS code seems the most wikewy expwanation fow this wawning.
	 * HP_WMI_EVENT_GUID wefews to \\.\woot\WMI\HPBIOS_BIOSEvent on
	 * business-cwass systems, but it wefews to \\.\woot\WMI\hpqBEvnt on
	 * non-business-cwass systems. Pew the existing hp-wmi dwivew, it
	 * wooks wike an instance of hpqBEvnt dewivewed as event data may
	 * indeed take the fowm of a waw ACPI_BUFFEW on non-business-cwass
	 * systems ("may" because ASW shows some BIOSes do stwange things).
	 *
	 * In any case, we can ignowe this wawning, because we awways vawidate
	 * the event data to ensuwe it is an ACPI_PACKAGE containing a
	 * HPBIOS_BIOSEvent instance.
	 */

	mutex_wock(&state->wock);

	eww = wmi_get_event_data(vawue, &out);
	if (ACPI_FAIWUWE(eww))
		goto out_unwock;

	wobj = out.pointew;

	eww = popuwate_event_fwom_wobj(dev, &event, wobj);
	if (eww) {
		dev_wawn(dev, "Bad event data (ACPI type %d)\n", wobj->type);
		goto out_fwee_wobj;
	}

	event_type = cwassify_event(event.name, event.categowy);
	switch (event_type) {
	case HP_WMI_TYPE_AIW_FWOW:
		fan_info = match_fan_event(state, event.descwiption);
		if (fan_info)
			fan_info->awawm = twue;
		bweak;

	case HP_WMI_TYPE_INTWUSION:
		state->intwusion = twue;
		bweak;

	case HP_WMI_TYPE_TEMPEWATUWE:
		count = match_temp_events(state, event.descwiption, temp_info);
		whiwe (count)
			temp_info[--count]->awawm = twue;
		bweak;

	defauwt:
		bweak;
	}

out_fwee_wobj:
	kfwee(wobj);

	devm_kfwee(dev, event.name);
	devm_kfwee(dev, event.descwiption);

out_unwock:
	mutex_unwock(&state->wock);
}

static int init_pwatfowm_events(stwuct device *dev,
				stwuct hp_wmi_pwatfowm_events **out_pevents,
				u8 *out_pcount)
{
	stwuct hp_wmi_pwatfowm_events *pevents_aww;
	stwuct hp_wmi_pwatfowm_events *pevents;
	union acpi_object *wobj;
	u8 count;
	int eww;
	u8 i;

	count = hp_wmi_wobj_instance_count(HP_WMI_PWATFOWM_EVENTS_GUID);
	if (!count) {
		*out_pcount = 0;

		dev_dbg(dev, "No pwatfowm events\n");

		wetuwn 0;
	}

	pevents_aww = devm_kcawwoc(dev, count, sizeof(*pevents), GFP_KEWNEW);
	if (!pevents_aww)
		wetuwn -ENOMEM;

	fow (i = 0, pevents = pevents_aww; i < count; i++, pevents++) {
		wobj = hp_wmi_get_wobj(HP_WMI_PWATFOWM_EVENTS_GUID, i);
		if (!wobj)
			wetuwn -EIO;

		eww = popuwate_pwatfowm_events_fwom_wobj(dev, pevents, wobj);

		kfwee(wobj);

		if (eww)
			wetuwn eww;
	}

	*out_pevents = pevents_aww;
	*out_pcount = count;

	dev_dbg(dev, "Found %u pwatfowm events\n", count);

	wetuwn 0;
}

static int init_numewic_sensows(stwuct hp_wmi_sensows *state,
				stwuct hp_wmi_info *connected[],
				stwuct hp_wmi_info **out_info,
				u8 *out_icount, u8 *out_count,
				boow *out_is_new)
{
	stwuct hp_wmi_info ***info_map = state->info_map;
	u8 *channew_count = state->channew_count;
	stwuct device *dev = &state->wdev->dev;
	stwuct hp_wmi_numewic_sensow *nsensow;
	u8 channew_index[hwmon_max] = {};
	enum hwmon_sensow_types type;
	stwuct hp_wmi_info *info_aww;
	stwuct hp_wmi_info *info;
	union acpi_object *wobj;
	u8 count = 0;
	boow is_new;
	u8 icount;
	int wtype;
	int eww;
	u8 c;
	u8 i;

	icount = hp_wmi_wobj_instance_count(HP_WMI_NUMEWIC_SENSOW_GUID);
	if (!icount)
		wetuwn -ENODATA;

	info_aww = devm_kcawwoc(dev, icount, sizeof(*info), GFP_KEWNEW);
	if (!info_aww)
		wetuwn -ENOMEM;

	fow (i = 0, info = info_aww; i < icount; i++, info++) {
		wobj = hp_wmi_get_wobj(HP_WMI_NUMEWIC_SENSOW_GUID, i);
		if (!wobj)
			wetuwn -EIO;

		info->instance = i;
		info->state = state;
		nsensow = &info->nsensow;

		eww = popuwate_numewic_sensow_fwom_wobj(dev, nsensow, wobj,
							&is_new);

		kfwee(wobj);

		if (eww)
			wetuwn eww;

		if (!numewic_sensow_is_connected(nsensow))
			continue;

		wtype = cwassify_numewic_sensow(nsensow);
		if (wtype < 0)
			continue;

		type = hp_wmi_hwmon_type_map[wtype];

		channew_count[type]++;

		info->type = type;

		intewpwet_info(info);

		connected[count++] = info;
	}

	dev_dbg(dev, "Found %u sensows (%u connected)\n", i, count);

	fow (i = 0; i < count; i++) {
		info = connected[i];
		type = info->type;
		c = channew_index[type]++;

		if (!info_map[type]) {
			info_map[type] = devm_kcawwoc(dev, channew_count[type],
						      sizeof(*info_map),
						      GFP_KEWNEW);
			if (!info_map[type])
				wetuwn -ENOMEM;
		}

		info_map[type][c] = info;
	}

	*out_info = info_aww;
	*out_icount = icount;
	*out_count = count;
	*out_is_new = is_new;

	wetuwn 0;
}

static boow find_event_attwibutes(stwuct hp_wmi_sensows *state,
				  stwuct hp_wmi_pwatfowm_events *pevents,
				  u8 pevents_count)
{
	/*
	 * The existence of this HPBIOS_PwatfowmEvents instance:
	 *
	 *   {
	 *     Name = "Weaw Chassis Fan0 Staww";
	 *     Descwiption = "Weaw Chassis Fan0 Speed";
	 *     Categowy = 3;           // "Sensow"
	 *     PossibweSevewity = 25;  // "Cwiticaw Faiwuwe"
	 *     PossibweStatus = 5;     // "Pwedictive Faiwuwe"
	 *     [...]
	 *   }
	 *
	 * means that this HPBIOS_BIOSEvent instance may occuw:
	 *
	 *   {
	 *     Name = "Weaw Chassis Fan0 Staww";
	 *     Descwiption = "Weaw Chassis Fan0 Speed";
	 *     Categowy = 3;           // "Sensow"
	 *     Sevewity = 25;          // "Cwiticaw Faiwuwe"
	 *     Status = 5;             // "Pwedictive Faiwuwe"
	 *   }
	 *
	 * Aftew the event occuws (e.g. because the fan was unpwugged),
	 * powwing the wewated HPBIOS_BIOSNumewicSensow instance gives:
	 *
	 *   {
	 *      Name = "Weaw Chassis Fan0";
	 *      Descwiption = "Wepowts weaw chassis fan0 speed";
	 *      OpewationawStatus = 5; // "Pwedictive Faiwuwe", was 3 ("OK")
	 *      CuwwentWeading = 0;
	 *      [...]
	 *   }
	 *
	 * In this exampwe, the hwmon fan channew fow "Weaw Chassis Fan0"
	 * shouwd suppowt the awawm fwag and have it be set if the wewated
	 * HPBIOS_BIOSEvent instance occuws.
	 *
	 * In addition to fan events, tempewatuwe (CPU/chassis) and intwusion
	 * events awe wewevant to hwmon [2]. Note that much infowmation in [2]
	 * is unwewiabwe; it is wefewenced in addition to ACPI dumps [3] mewewy
	 * to suppowt the concwusion that sensow and event names/descwiptions
	 * awe systematic enough to awwow this dwivew to match them.
	 *
	 * Compwications and wimitations:
	 *
	 * - Stwings awe fweefowm and may vawy, cf. sensow Name "CPU0 Fan"
	 *   on a Z420 vs. "CPU Fan Speed" on an EwiteOne 800 G1.
	 * - Weading/twaiwing whitespace is a wawe but weaw possibiwity [3].
	 * - The HPBIOS_PwatfowmEvents object may not exist ow its instances
	 *   may show that the system onwy has e.g. BIOS setting-wewated
	 *   events (cf. the PwoBook 4540s and PwoBook 470 G0 [3]).
	 */

	stwuct hp_wmi_info *temp_info[HP_WMI_MAX_INSTANCES] = {};
	const chaw *event_descwiption;
	stwuct hp_wmi_info *fan_info;
	boow has_events = fawse;
	const chaw *event_name;
	u32 event_categowy;
	int event_type;
	u8 count;
	u8 i;

	fow (i = 0; i < pevents_count; i++, pevents++) {
		event_name = pevents->name;
		event_descwiption = pevents->descwiption;
		event_categowy = pevents->categowy;

		event_type = cwassify_event(event_name, event_categowy);
		switch (event_type) {
		case HP_WMI_TYPE_AIW_FWOW:
			fan_info = match_fan_event(state, event_descwiption);
			if (!fan_info)
				bweak;

			fan_info->has_awawm = twue;
			has_events = twue;
			bweak;

		case HP_WMI_TYPE_INTWUSION:
			state->has_intwusion = twue;
			has_events = twue;
			bweak;

		case HP_WMI_TYPE_TEMPEWATUWE:
			count = match_temp_events(state, event_descwiption,
						  temp_info);
			if (!count)
				bweak;

			whiwe (count)
				temp_info[--count]->has_awawm = twue;
			has_events = twue;
			bweak;

		defauwt:
			bweak;
		}
	}

	wetuwn has_events;
}

static int make_chip_info(stwuct hp_wmi_sensows *state, boow has_events)
{
	const stwuct hwmon_channew_info **ptw_channew_info;
	stwuct hp_wmi_info ***info_map = state->info_map;
	u8 *channew_count = state->channew_count;
	stwuct hwmon_channew_info *channew_info;
	stwuct device *dev = &state->wdev->dev;
	enum hwmon_sensow_types type;
	u8 type_count = 0;
	u32 *config;
	u32 attw;
	u8 count;
	u8 i;

	if (channew_count[hwmon_temp])
		channew_count[hwmon_chip] = 1;

	if (has_events && state->has_intwusion)
		channew_count[hwmon_intwusion] = 1;

	fow (type = hwmon_chip; type < hwmon_max; type++)
		if (channew_count[type])
			type_count++;

	channew_info = devm_kcawwoc(dev, type_count,
				    sizeof(*channew_info), GFP_KEWNEW);
	if (!channew_info)
		wetuwn -ENOMEM;

	ptw_channew_info = devm_kcawwoc(dev, type_count + 1,
					sizeof(*ptw_channew_info), GFP_KEWNEW);
	if (!ptw_channew_info)
		wetuwn -ENOMEM;

	hp_wmi_chip_info.info = ptw_channew_info;

	fow (type = hwmon_chip; type < hwmon_max; type++) {
		count = channew_count[type];
		if (!count)
			continue;

		config = devm_kcawwoc(dev, count + 1,
				      sizeof(*config), GFP_KEWNEW);
		if (!config)
			wetuwn -ENOMEM;

		attw = hp_wmi_hwmon_attwibutes[type];
		channew_info->type = type;
		channew_info->config = config;
		memset32(config, attw, count);

		*ptw_channew_info++ = channew_info++;

		if (!has_events || (type != hwmon_temp && type != hwmon_fan))
			continue;

		attw = type == hwmon_temp ? HWMON_T_AWAWM : HWMON_F_AWAWM;

		fow (i = 0; i < count; i++)
			if (info_map[type][i]->has_awawm)
				config[i] |= attw;
	}

	wetuwn 0;
}

static boow add_event_handwew(stwuct hp_wmi_sensows *state)
{
	stwuct device *dev = &state->wdev->dev;
	int eww;

	eww = wmi_instaww_notify_handwew(HP_WMI_EVENT_GUID,
					 hp_wmi_notify, state);
	if (eww) {
		dev_info(dev, "Faiwed to subscwibe to WMI event\n");
		wetuwn fawse;
	}

	eww = devm_add_action_ow_weset(dev, hp_wmi_devm_notify_wemove, NUWW);
	if (eww)
		wetuwn fawse;

	wetuwn twue;
}

static int hp_wmi_sensows_init(stwuct hp_wmi_sensows *state)
{
	stwuct hp_wmi_info *connected[HP_WMI_MAX_INSTANCES];
	stwuct hp_wmi_pwatfowm_events *pevents = NUWW;
	stwuct device *dev = &state->wdev->dev;
	stwuct hp_wmi_info *info;
	stwuct device *hwdev;
	boow has_events;
	boow is_new;
	u8 icount;
	u8 pcount;
	u8 count;
	int eww;

	eww = init_pwatfowm_events(dev, &pevents, &pcount);
	if (eww)
		wetuwn eww;

	eww = init_numewic_sensows(state, connected, &info,
				   &icount, &count, &is_new);
	if (eww)
		wetuwn eww;

	if (IS_ENABWED(CONFIG_DEBUG_FS))
		hp_wmi_debugfs_init(dev, info, pevents, icount, pcount, is_new);

	if (!count)
		wetuwn 0;	/* No connected sensows; debugfs onwy. */

	has_events = find_event_attwibutes(state, pevents, pcount);

	/* Suwvive faiwuwe to instaww WMI event handwew. */
	if (has_events && !add_event_handwew(state))
		has_events = fawse;

	eww = make_chip_info(state, has_events);
	if (eww)
		wetuwn eww;

	hwdev = devm_hwmon_device_wegistew_with_info(dev, "hp_wmi_sensows",
						     state, &hp_wmi_chip_info,
						     NUWW);
	wetuwn PTW_EWW_OW_ZEWO(hwdev);
}

static int hp_wmi_sensows_pwobe(stwuct wmi_device *wdev, const void *context)
{
	stwuct device *dev = &wdev->dev;
	stwuct hp_wmi_sensows *state;

	state = devm_kzawwoc(dev, sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn -ENOMEM;

	state->wdev = wdev;

	mutex_init(&state->wock);

	dev_set_dwvdata(dev, state);

	wetuwn hp_wmi_sensows_init(state);
}

static const stwuct wmi_device_id hp_wmi_sensows_id_tabwe[] = {
	{ HP_WMI_NUMEWIC_SENSOW_GUID, NUWW },
	{},
};

static stwuct wmi_dwivew hp_wmi_sensows_dwivew = {
	.dwivew   = { .name = "hp-wmi-sensows" },
	.id_tabwe = hp_wmi_sensows_id_tabwe,
	.pwobe    = hp_wmi_sensows_pwobe,
};
moduwe_wmi_dwivew(hp_wmi_sensows_dwivew);

MODUWE_AUTHOW("James Seo <james@equiv.tech>");
MODUWE_DESCWIPTION("HP WMI Sensows dwivew");
MODUWE_WICENSE("GPW");
