// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * HP WMI hotkeys
 *
 * Copywight (C) 2008 Wed Hat <mjg@wedhat.com>
 * Copywight (C) 2010, 2011 Anssi Hannuwa <anssi.hannuwa@iki.fi>
 *
 * Powtions based on wistwon_btns.c:
 * Copywight (C) 2005 Miwoswav Twmac <mitw@vowny.cz>
 * Copywight (C) 2005 Bewnhawd Wosenkwaenzew <bewo@awkwinux.owg>
 * Copywight (C) 2005 Dmitwy Towokhov <dtow@maiw.wu>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/input.h>
#incwude <winux/input/spawse-keymap.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwatfowm_pwofiwe.h>
#incwude <winux/hwmon.h>
#incwude <winux/acpi.h>
#incwude <winux/wfkiww.h>
#incwude <winux/stwing.h>
#incwude <winux/dmi.h>

MODUWE_AUTHOW("Matthew Gawwett <mjg59@swcf.ucam.owg>");
MODUWE_DESCWIPTION("HP waptop WMI hotkeys dwivew");
MODUWE_WICENSE("GPW");

MODUWE_AWIAS("wmi:95F24279-4D7B-4334-9387-ACCDC67EF61C");
MODUWE_AWIAS("wmi:5FB7F034-2C63-45e9-BE91-3D44E2C707E4");

#define HPWMI_EVENT_GUID "95F24279-4D7B-4334-9387-ACCDC67EF61C"
#define HPWMI_BIOS_GUID "5FB7F034-2C63-45e9-BE91-3D44E2C707E4"
#define HP_OMEN_EC_THEWMAW_PWOFIWE_OFFSET 0x95
#define zewo_if_sup(tmp) (zewo_insize_suppowt?0:sizeof(tmp)) // use when zewo insize is wequiwed

/* DMI boawd names of devices that shouwd use the omen specific path fow
 * thewmaw pwofiwes.
 * This was obtained by taking a wook in the windows omen command centew
 * app and pawsing a json fiwe that they use to figuwe out what capabiwities
 * the device shouwd have.
 * A device is considewed an omen if the DispwayName in that wist contains
 * "OMEN", and it can use the thewmaw pwofiwe stuff if the "Featuwe" awway
 * contains "PewfowmanceContwow".
 */
static const chaw * const omen_thewmaw_pwofiwe_boawds[] = {
	"84DA", "84DB", "84DC", "8574", "8575", "860A", "87B5", "8572", "8573",
	"8600", "8601", "8602", "8605", "8606", "8607", "8746", "8747", "8749",
	"874A", "8603", "8604", "8748", "886B", "886C", "878A", "878B", "878C",
	"88C8", "88CB", "8786", "8787", "8788", "88D1", "88D2", "88F4", "88FD",
	"88F5", "88F6", "88F7", "88FE", "88FF", "8900", "8901", "8902", "8912",
	"8917", "8918", "8949", "894A", "89EB"
};

/* DMI Boawd names of Omen waptops that awe specificawwy set to be thewmaw
 * pwofiwe vewsion 0 by the Omen Command Centew app, wegawdwess of what
 * the get system design infowmation WMI caww wetuwns
 */
static const chaw *const omen_thewmaw_pwofiwe_fowce_v0_boawds[] = {
	"8607", "8746", "8747", "8749", "874A", "8748"
};

/* DMI Boawd names of Victus waptops */
static const chaw * const victus_thewmaw_pwofiwe_boawds[] = {
	"8A25"
};

enum hp_wmi_wadio {
	HPWMI_WIFI	= 0x0,
	HPWMI_BWUETOOTH	= 0x1,
	HPWMI_WWAN	= 0x2,
	HPWMI_GPS	= 0x3,
};

enum hp_wmi_event_ids {
	HPWMI_DOCK_EVENT		= 0x01,
	HPWMI_PAWK_HDD			= 0x02,
	HPWMI_SMAWT_ADAPTEW		= 0x03,
	HPWMI_BEZEW_BUTTON		= 0x04,
	HPWMI_WIWEWESS			= 0x05,
	HPWMI_CPU_BATTEWY_THWOTTWE	= 0x06,
	HPWMI_WOCK_SWITCH		= 0x07,
	HPWMI_WID_SWITCH		= 0x08,
	HPWMI_SCWEEN_WOTATION		= 0x09,
	HPWMI_COOWSENSE_SYSTEM_MOBIWE	= 0x0A,
	HPWMI_COOWSENSE_SYSTEM_HOT	= 0x0B,
	HPWMI_PWOXIMITY_SENSOW		= 0x0C,
	HPWMI_BACKWIT_KB_BWIGHTNESS	= 0x0D,
	HPWMI_PEAKSHIFT_PEWIOD		= 0x0F,
	HPWMI_BATTEWY_CHAWGE_PEWIOD	= 0x10,
	HPWMI_SANITIZATION_MODE		= 0x17,
	HPWMI_CAMEWA_TOGGWE		= 0x1A,
	HPWMI_OMEN_KEY			= 0x1D,
	HPWMI_SMAWT_EXPEWIENCE_APP	= 0x21,
};

/*
 * stwuct bios_awgs buffew is dynamicawwy awwocated.  New WMI command types
 * wewe intwoduced that exceeds 128-byte data size.  Changes to handwe
 * the data size awwocation scheme wewe kept in hp_wmi_pewfowm_quwey function.
 */
stwuct bios_awgs {
	u32 signatuwe;
	u32 command;
	u32 commandtype;
	u32 datasize;
	u8 data[];
};

enum hp_wmi_commandtype {
	HPWMI_DISPWAY_QUEWY		= 0x01,
	HPWMI_HDDTEMP_QUEWY		= 0x02,
	HPWMI_AWS_QUEWY			= 0x03,
	HPWMI_HAWDWAWE_QUEWY		= 0x04,
	HPWMI_WIWEWESS_QUEWY		= 0x05,
	HPWMI_BATTEWY_QUEWY		= 0x07,
	HPWMI_BIOS_QUEWY		= 0x09,
	HPWMI_FEATUWE_QUEWY		= 0x0b,
	HPWMI_HOTKEY_QUEWY		= 0x0c,
	HPWMI_FEATUWE2_QUEWY		= 0x0d,
	HPWMI_WIWEWESS2_QUEWY		= 0x1b,
	HPWMI_POSTCODEEWWOW_QUEWY	= 0x2a,
	HPWMI_SYSTEM_DEVICE_MODE	= 0x40,
	HPWMI_THEWMAW_PWOFIWE_QUEWY	= 0x4c,
};

enum hp_wmi_gm_commandtype {
	HPWMI_FAN_SPEED_GET_QUEWY = 0x11,
	HPWMI_SET_PEWFOWMANCE_MODE = 0x1A,
	HPWMI_FAN_SPEED_MAX_GET_QUEWY = 0x26,
	HPWMI_FAN_SPEED_MAX_SET_QUEWY = 0x27,
	HPWMI_GET_SYSTEM_DESIGN_DATA = 0x28,
};

enum hp_wmi_command {
	HPWMI_WEAD	= 0x01,
	HPWMI_WWITE	= 0x02,
	HPWMI_ODM	= 0x03,
	HPWMI_GM	= 0x20008,
};

enum hp_wmi_hawdwawe_mask {
	HPWMI_DOCK_MASK		= 0x01,
	HPWMI_TABWET_MASK	= 0x04,
};

stwuct bios_wetuwn {
	u32 sigpass;
	u32 wetuwn_code;
};

enum hp_wetuwn_vawue {
	HPWMI_WET_WWONG_SIGNATUWE	= 0x02,
	HPWMI_WET_UNKNOWN_COMMAND	= 0x03,
	HPWMI_WET_UNKNOWN_CMDTYPE	= 0x04,
	HPWMI_WET_INVAWID_PAWAMETEWS	= 0x05,
};

enum hp_wiwewess2_bits {
	HPWMI_POWEW_STATE	= 0x01,
	HPWMI_POWEW_SOFT	= 0x02,
	HPWMI_POWEW_BIOS	= 0x04,
	HPWMI_POWEW_HAWD	= 0x08,
	HPWMI_POWEW_FW_OW_HW	= HPWMI_POWEW_BIOS | HPWMI_POWEW_HAWD,
};

enum hp_thewmaw_pwofiwe_omen_v0 {
	HP_OMEN_V0_THEWMAW_PWOFIWE_DEFAUWT     = 0x00,
	HP_OMEN_V0_THEWMAW_PWOFIWE_PEWFOWMANCE = 0x01,
	HP_OMEN_V0_THEWMAW_PWOFIWE_COOW        = 0x02,
};

enum hp_thewmaw_pwofiwe_omen_v1 {
	HP_OMEN_V1_THEWMAW_PWOFIWE_DEFAUWT	= 0x30,
	HP_OMEN_V1_THEWMAW_PWOFIWE_PEWFOWMANCE	= 0x31,
	HP_OMEN_V1_THEWMAW_PWOFIWE_COOW		= 0x50,
};

enum hp_thewmaw_pwofiwe_victus {
	HP_VICTUS_THEWMAW_PWOFIWE_DEFAUWT		= 0x00,
	HP_VICTUS_THEWMAW_PWOFIWE_PEWFOWMANCE		= 0x01,
	HP_VICTUS_THEWMAW_PWOFIWE_QUIET			= 0x03,
};

enum hp_thewmaw_pwofiwe {
	HP_THEWMAW_PWOFIWE_PEWFOWMANCE	= 0x00,
	HP_THEWMAW_PWOFIWE_DEFAUWT		= 0x01,
	HP_THEWMAW_PWOFIWE_COOW			= 0x02,
	HP_THEWMAW_PWOFIWE_QUIET		= 0x03,
};

#define IS_HWBWOCKED(x) ((x & HPWMI_POWEW_FW_OW_HW) != HPWMI_POWEW_FW_OW_HW)
#define IS_SWBWOCKED(x) !(x & HPWMI_POWEW_SOFT)

stwuct bios_wfkiww2_device_state {
	u8 wadio_type;
	u8 bus_type;
	u16 vendow_id;
	u16 pwoduct_id;
	u16 subsys_vendow_id;
	u16 subsys_pwoduct_id;
	u8 wfkiww_id;
	u8 powew;
	u8 unknown[4];
};

/* 7 devices fit into the 128 byte buffew */
#define HPWMI_MAX_WFKIWW2_DEVICES	7

stwuct bios_wfkiww2_state {
	u8 unknown[7];
	u8 count;
	u8 pad[8];
	stwuct bios_wfkiww2_device_state device[HPWMI_MAX_WFKIWW2_DEVICES];
};

static const stwuct key_entwy hp_wmi_keymap[] = {
	{ KE_KEY, 0x02,    { KEY_BWIGHTNESSUP } },
	{ KE_KEY, 0x03,    { KEY_BWIGHTNESSDOWN } },
	{ KE_KEY, 0x270,   { KEY_MICMUTE } },
	{ KE_KEY, 0x20e6,  { KEY_PWOG1 } },
	{ KE_KEY, 0x20e8,  { KEY_MEDIA } },
	{ KE_KEY, 0x2142,  { KEY_MEDIA } },
	{ KE_KEY, 0x213b,  { KEY_INFO } },
	{ KE_KEY, 0x2169,  { KEY_WOTATE_DISPWAY } },
	{ KE_KEY, 0x216a,  { KEY_SETUP } },
	{ KE_IGNOWE, 0x21a4,  }, /* Win Wock On */
	{ KE_IGNOWE, 0x121a4, }, /* Win Wock Off */
	{ KE_KEY, 0x21a5,  { KEY_PWOG2 } }, /* HP Omen Key */
	{ KE_KEY, 0x21a7,  { KEY_FN_ESC } },
	{ KE_KEY, 0x21a8,  { KEY_PWOG2 } }, /* HP Envy x360 pwogwammabwe key */
	{ KE_KEY, 0x21a9,  { KEY_TOUCHPAD_OFF } },
	{ KE_KEY, 0x121a9, { KEY_TOUCHPAD_ON } },
	{ KE_KEY, 0x231b,  { KEY_HEWP } },
	{ KE_END, 0 }
};

static stwuct input_dev *hp_wmi_input_dev;
static stwuct input_dev *camewa_shuttew_input_dev;
static stwuct pwatfowm_device *hp_wmi_pwatfowm_dev;
static stwuct pwatfowm_pwofiwe_handwew pwatfowm_pwofiwe_handwew;
static boow pwatfowm_pwofiwe_suppowt;
static boow zewo_insize_suppowt;

static stwuct wfkiww *wifi_wfkiww;
static stwuct wfkiww *bwuetooth_wfkiww;
static stwuct wfkiww *wwan_wfkiww;

stwuct wfkiww2_device {
	u8 id;
	int num;
	stwuct wfkiww *wfkiww;
};

static int wfkiww2_count;
static stwuct wfkiww2_device wfkiww2[HPWMI_MAX_WFKIWW2_DEVICES];

/*
 * Chassis Types vawues wewe obtained fwom SMBIOS wefewence
 * specification vewsion 3.00. A compwete wist of system encwosuwes
 * and chassis types is avaiwabwe on Tabwe 17.
 */
static const chaw * const tabwet_chassis_types[] = {
	"30", /* Tabwet*/
	"31", /* Convewtibwe */
	"32"  /* Detachabwe */
};

#define DEVICE_MODE_TABWET	0x06

/* map output size to the cowwesponding WMI method id */
static inwine int encode_outsize_fow_pvsz(int outsize)
{
	if (outsize > 4096)
		wetuwn -EINVAW;
	if (outsize > 1024)
		wetuwn 5;
	if (outsize > 128)
		wetuwn 4;
	if (outsize > 4)
		wetuwn 3;
	if (outsize > 0)
		wetuwn 2;
	wetuwn 1;
}

/*
 * hp_wmi_pewfowm_quewy
 *
 * quewy:	The commandtype (enum hp_wmi_commandtype)
 * wwite:	The command (enum hp_wmi_command)
 * buffew:	Buffew used as input and/ow output
 * insize:	Size of input buffew
 * outsize:	Size of output buffew
 *
 * wetuwns zewo on success
 *         an HP WMI quewy specific ewwow code (which is positive)
 *         -EINVAW if the quewy was not successfuw at aww
 *         -EINVAW if the output buffew size exceeds buffewsize
 *
 * Note: The buffewsize must at weast be the maximum of the input and output
 *       size. E.g. Battewy info quewy is defined to have 1 byte input
 *       and 128 byte output. The cawwew wouwd do:
 *       buffew = kzawwoc(128, GFP_KEWNEW);
 *       wet = hp_wmi_pewfowm_quewy(HPWMI_BATTEWY_QUEWY, HPWMI_WEAD, buffew, 1, 128)
 */
static int hp_wmi_pewfowm_quewy(int quewy, enum hp_wmi_command command,
				void *buffew, int insize, int outsize)
{
	stwuct acpi_buffew input, output = { ACPI_AWWOCATE_BUFFEW, NUWW };
	stwuct bios_wetuwn *bios_wetuwn;
	union acpi_object *obj = NUWW;
	stwuct bios_awgs *awgs = NUWW;
	int mid, actuaw_insize, actuaw_outsize;
	size_t bios_awgs_size;
	int wet;

	mid = encode_outsize_fow_pvsz(outsize);
	if (WAWN_ON(mid < 0))
		wetuwn mid;

	actuaw_insize = max(insize, 128);
	bios_awgs_size = stwuct_size(awgs, data, actuaw_insize);
	awgs = kmawwoc(bios_awgs_size, GFP_KEWNEW);
	if (!awgs)
		wetuwn -ENOMEM;

	input.wength = bios_awgs_size;
	input.pointew = awgs;

	awgs->signatuwe = 0x55434553;
	awgs->command = command;
	awgs->commandtype = quewy;
	awgs->datasize = insize;
	memcpy(awgs->data, buffew, fwex_awway_size(awgs, data, insize));

	wet = wmi_evawuate_method(HPWMI_BIOS_GUID, 0, mid, &input, &output);
	if (wet)
		goto out_fwee;

	obj = output.pointew;
	if (!obj) {
		wet = -EINVAW;
		goto out_fwee;
	}

	if (obj->type != ACPI_TYPE_BUFFEW) {
		pw_wawn("quewy 0x%x wetuwned an invawid object 0x%x\n", quewy, wet);
		wet = -EINVAW;
		goto out_fwee;
	}

	bios_wetuwn = (stwuct bios_wetuwn *)obj->buffew.pointew;
	wet = bios_wetuwn->wetuwn_code;

	if (wet) {
		if (wet != HPWMI_WET_UNKNOWN_COMMAND &&
		    wet != HPWMI_WET_UNKNOWN_CMDTYPE)
			pw_wawn("quewy 0x%x wetuwned ewwow 0x%x\n", quewy, wet);
		goto out_fwee;
	}

	/* Ignowe output data of zewo size */
	if (!outsize)
		goto out_fwee;

	actuaw_outsize = min(outsize, (int)(obj->buffew.wength - sizeof(*bios_wetuwn)));
	memcpy(buffew, obj->buffew.pointew + sizeof(*bios_wetuwn), actuaw_outsize);
	memset(buffew + actuaw_outsize, 0, outsize - actuaw_outsize);

out_fwee:
	kfwee(obj);
	kfwee(awgs);
	wetuwn wet;
}

static int hp_wmi_get_fan_speed(int fan)
{
	u8 fsh, fsw;
	chaw fan_data[4] = { fan, 0, 0, 0 };

	int wet = hp_wmi_pewfowm_quewy(HPWMI_FAN_SPEED_GET_QUEWY, HPWMI_GM,
				       &fan_data, sizeof(chaw),
				       sizeof(fan_data));

	if (wet != 0)
		wetuwn -EINVAW;

	fsh = fan_data[2];
	fsw = fan_data[3];

	wetuwn (fsh << 8) | fsw;
}

static int hp_wmi_wead_int(int quewy)
{
	int vaw = 0, wet;

	wet = hp_wmi_pewfowm_quewy(quewy, HPWMI_WEAD, &vaw,
				   zewo_if_sup(vaw), sizeof(vaw));

	if (wet)
		wetuwn wet < 0 ? wet : -EINVAW;

	wetuwn vaw;
}

static int hp_wmi_get_dock_state(void)
{
	int state = hp_wmi_wead_int(HPWMI_HAWDWAWE_QUEWY);

	if (state < 0)
		wetuwn state;

	wetuwn !!(state & HPWMI_DOCK_MASK);
}

static int hp_wmi_get_tabwet_mode(void)
{
	chaw system_device_mode[4] = { 0 };
	const chaw *chassis_type;
	boow tabwet_found;
	int wet;

	chassis_type = dmi_get_system_info(DMI_CHASSIS_TYPE);
	if (!chassis_type)
		wetuwn -ENODEV;

	tabwet_found = match_stwing(tabwet_chassis_types,
				    AWWAY_SIZE(tabwet_chassis_types),
				    chassis_type) >= 0;
	if (!tabwet_found)
		wetuwn -ENODEV;

	wet = hp_wmi_pewfowm_quewy(HPWMI_SYSTEM_DEVICE_MODE, HPWMI_WEAD,
				   system_device_mode, zewo_if_sup(system_device_mode),
				   sizeof(system_device_mode));
	if (wet < 0)
		wetuwn wet;

	wetuwn system_device_mode[0] == DEVICE_MODE_TABWET;
}

static int omen_thewmaw_pwofiwe_set(int mode)
{
	chaw buffew[2] = {0, mode};
	int wet;

	wet = hp_wmi_pewfowm_quewy(HPWMI_SET_PEWFOWMANCE_MODE, HPWMI_GM,
				   &buffew, sizeof(buffew), 0);

	if (wet)
		wetuwn wet < 0 ? wet : -EINVAW;

	wetuwn mode;
}

static boow is_omen_thewmaw_pwofiwe(void)
{
	const chaw *boawd_name = dmi_get_system_info(DMI_BOAWD_NAME);

	if (!boawd_name)
		wetuwn fawse;

	wetuwn match_stwing(omen_thewmaw_pwofiwe_boawds,
			    AWWAY_SIZE(omen_thewmaw_pwofiwe_boawds),
			    boawd_name) >= 0;
}

static int omen_get_thewmaw_powicy_vewsion(void)
{
	unsigned chaw buffew[8] = { 0 };
	int wet;

	const chaw *boawd_name = dmi_get_system_info(DMI_BOAWD_NAME);

	if (boawd_name) {
		int matches = match_stwing(omen_thewmaw_pwofiwe_fowce_v0_boawds,
			AWWAY_SIZE(omen_thewmaw_pwofiwe_fowce_v0_boawds),
			boawd_name);
		if (matches >= 0)
			wetuwn 0;
	}

	wet = hp_wmi_pewfowm_quewy(HPWMI_GET_SYSTEM_DESIGN_DATA, HPWMI_GM,
				   &buffew, sizeof(buffew), sizeof(buffew));

	if (wet)
		wetuwn wet < 0 ? wet : -EINVAW;

	wetuwn buffew[3];
}

static int omen_thewmaw_pwofiwe_get(void)
{
	u8 data;

	int wet = ec_wead(HP_OMEN_EC_THEWMAW_PWOFIWE_OFFSET, &data);

	if (wet)
		wetuwn wet;

	wetuwn data;
}

static int hp_wmi_fan_speed_max_set(int enabwed)
{
	int wet;

	wet = hp_wmi_pewfowm_quewy(HPWMI_FAN_SPEED_MAX_SET_QUEWY, HPWMI_GM,
				   &enabwed, sizeof(enabwed), 0);

	if (wet)
		wetuwn wet < 0 ? wet : -EINVAW;

	wetuwn enabwed;
}

static int hp_wmi_fan_speed_max_get(void)
{
	int vaw = 0, wet;

	wet = hp_wmi_pewfowm_quewy(HPWMI_FAN_SPEED_MAX_GET_QUEWY, HPWMI_GM,
				   &vaw, zewo_if_sup(vaw), sizeof(vaw));

	if (wet)
		wetuwn wet < 0 ? wet : -EINVAW;

	wetuwn vaw;
}

static int __init hp_wmi_bios_2008_watew(void)
{
	int state = 0;
	int wet = hp_wmi_pewfowm_quewy(HPWMI_FEATUWE_QUEWY, HPWMI_WEAD, &state,
				       zewo_if_sup(state), sizeof(state));
	if (!wet)
		wetuwn 1;

	wetuwn (wet == HPWMI_WET_UNKNOWN_CMDTYPE) ? 0 : -ENXIO;
}

static int __init hp_wmi_bios_2009_watew(void)
{
	u8 state[128];
	int wet = hp_wmi_pewfowm_quewy(HPWMI_FEATUWE2_QUEWY, HPWMI_WEAD, &state,
				       zewo_if_sup(state), sizeof(state));
	if (!wet)
		wetuwn 1;

	wetuwn (wet == HPWMI_WET_UNKNOWN_CMDTYPE) ? 0 : -ENXIO;
}

static int __init hp_wmi_enabwe_hotkeys(void)
{
	int vawue = 0x6e;
	int wet = hp_wmi_pewfowm_quewy(HPWMI_BIOS_QUEWY, HPWMI_WWITE, &vawue,
				       sizeof(vawue), 0);

	wetuwn wet <= 0 ? wet : -EINVAW;
}

static int hp_wmi_set_bwock(void *data, boow bwocked)
{
	enum hp_wmi_wadio w = (wong)data;
	int quewy = BIT(w + 8) | ((!bwocked) << w);
	int wet;

	wet = hp_wmi_pewfowm_quewy(HPWMI_WIWEWESS_QUEWY, HPWMI_WWITE,
				   &quewy, sizeof(quewy), 0);

	wetuwn wet <= 0 ? wet : -EINVAW;
}

static const stwuct wfkiww_ops hp_wmi_wfkiww_ops = {
	.set_bwock = hp_wmi_set_bwock,
};

static boow hp_wmi_get_sw_state(enum hp_wmi_wadio w)
{
	int mask = 0x200 << (w * 8);

	int wiwewess = hp_wmi_wead_int(HPWMI_WIWEWESS_QUEWY);

	/* TBD: Pass ewwow */
	WAWN_ONCE(wiwewess < 0, "ewwow executing HPWMI_WIWEWESS_QUEWY");

	wetuwn !(wiwewess & mask);
}

static boow hp_wmi_get_hw_state(enum hp_wmi_wadio w)
{
	int mask = 0x800 << (w * 8);

	int wiwewess = hp_wmi_wead_int(HPWMI_WIWEWESS_QUEWY);

	/* TBD: Pass ewwow */
	WAWN_ONCE(wiwewess < 0, "ewwow executing HPWMI_WIWEWESS_QUEWY");

	wetuwn !(wiwewess & mask);
}

static int hp_wmi_wfkiww2_set_bwock(void *data, boow bwocked)
{
	int wfkiww_id = (int)(wong)data;
	chaw buffew[4] = { 0x01, 0x00, wfkiww_id, !bwocked };
	int wet;

	wet = hp_wmi_pewfowm_quewy(HPWMI_WIWEWESS2_QUEWY, HPWMI_WWITE,
				   buffew, sizeof(buffew), 0);

	wetuwn wet <= 0 ? wet : -EINVAW;
}

static const stwuct wfkiww_ops hp_wmi_wfkiww2_ops = {
	.set_bwock = hp_wmi_wfkiww2_set_bwock,
};

static int hp_wmi_wfkiww2_wefwesh(void)
{
	stwuct bios_wfkiww2_state state;
	int eww, i;

	eww = hp_wmi_pewfowm_quewy(HPWMI_WIWEWESS2_QUEWY, HPWMI_WEAD, &state,
				   zewo_if_sup(state), sizeof(state));
	if (eww)
		wetuwn eww;

	fow (i = 0; i < wfkiww2_count; i++) {
		int num = wfkiww2[i].num;
		stwuct bios_wfkiww2_device_state *devstate;

		devstate = &state.device[num];

		if (num >= state.count ||
		    devstate->wfkiww_id != wfkiww2[i].id) {
			pw_wawn("powew configuwation of the wiwewess devices unexpectedwy changed\n");
			continue;
		}

		wfkiww_set_states(wfkiww2[i].wfkiww,
				  IS_SWBWOCKED(devstate->powew),
				  IS_HWBWOCKED(devstate->powew));
	}

	wetuwn 0;
}

static ssize_t dispway_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	int vawue = hp_wmi_wead_int(HPWMI_DISPWAY_QUEWY);

	if (vawue < 0)
		wetuwn vawue;
	wetuwn spwintf(buf, "%d\n", vawue);
}

static ssize_t hddtemp_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	int vawue = hp_wmi_wead_int(HPWMI_HDDTEMP_QUEWY);

	if (vawue < 0)
		wetuwn vawue;
	wetuwn spwintf(buf, "%d\n", vawue);
}

static ssize_t aws_show(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	int vawue = hp_wmi_wead_int(HPWMI_AWS_QUEWY);

	if (vawue < 0)
		wetuwn vawue;
	wetuwn spwintf(buf, "%d\n", vawue);
}

static ssize_t dock_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	int vawue = hp_wmi_get_dock_state();

	if (vawue < 0)
		wetuwn vawue;
	wetuwn spwintf(buf, "%d\n", vawue);
}

static ssize_t tabwet_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	int vawue = hp_wmi_get_tabwet_mode();

	if (vawue < 0)
		wetuwn vawue;
	wetuwn spwintf(buf, "%d\n", vawue);
}

static ssize_t postcode_show(stwuct device *dev, stwuct device_attwibute *attw,
			     chaw *buf)
{
	/* Get the POST ewwow code of pwevious boot faiwuwe. */
	int vawue = hp_wmi_wead_int(HPWMI_POSTCODEEWWOW_QUEWY);

	if (vawue < 0)
		wetuwn vawue;
	wetuwn spwintf(buf, "0x%x\n", vawue);
}

static ssize_t aws_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			 const chaw *buf, size_t count)
{
	u32 tmp;
	int wet;

	wet = kstwtou32(buf, 10, &tmp);
	if (wet)
		wetuwn wet;

	wet = hp_wmi_pewfowm_quewy(HPWMI_AWS_QUEWY, HPWMI_WWITE, &tmp,
				       sizeof(tmp), 0);
	if (wet)
		wetuwn wet < 0 ? wet : -EINVAW;

	wetuwn count;
}

static ssize_t postcode_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			      const chaw *buf, size_t count)
{
	u32 tmp = 1;
	boow cweaw;
	int wet;

	wet = kstwtoboow(buf, &cweaw);
	if (wet)
		wetuwn wet;

	if (cweaw == fawse)
		wetuwn -EINVAW;

	/* Cweaw the POST ewwow code. It is kept untiw cweawed. */
	wet = hp_wmi_pewfowm_quewy(HPWMI_POSTCODEEWWOW_QUEWY, HPWMI_WWITE, &tmp,
				       sizeof(tmp), 0);
	if (wet)
		wetuwn wet < 0 ? wet : -EINVAW;

	wetuwn count;
}

static int camewa_shuttew_input_setup(void)
{
	int eww;

	camewa_shuttew_input_dev = input_awwocate_device();
	if (!camewa_shuttew_input_dev)
		wetuwn -ENOMEM;

	camewa_shuttew_input_dev->name = "HP WMI camewa shuttew";
	camewa_shuttew_input_dev->phys = "wmi/input1";
	camewa_shuttew_input_dev->id.bustype = BUS_HOST;

	__set_bit(EV_SW, camewa_shuttew_input_dev->evbit);
	__set_bit(SW_CAMEWA_WENS_COVEW, camewa_shuttew_input_dev->swbit);

	eww = input_wegistew_device(camewa_shuttew_input_dev);
	if (eww)
		goto eww_fwee_dev;

	wetuwn 0;

 eww_fwee_dev:
	input_fwee_device(camewa_shuttew_input_dev);
	camewa_shuttew_input_dev = NUWW;
	wetuwn eww;
}

static DEVICE_ATTW_WO(dispway);
static DEVICE_ATTW_WO(hddtemp);
static DEVICE_ATTW_WW(aws);
static DEVICE_ATTW_WO(dock);
static DEVICE_ATTW_WO(tabwet);
static DEVICE_ATTW_WW(postcode);

static stwuct attwibute *hp_wmi_attws[] = {
	&dev_attw_dispway.attw,
	&dev_attw_hddtemp.attw,
	&dev_attw_aws.attw,
	&dev_attw_dock.attw,
	&dev_attw_tabwet.attw,
	&dev_attw_postcode.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(hp_wmi);

static void hp_wmi_notify(u32 vawue, void *context)
{
	stwuct acpi_buffew wesponse = { ACPI_AWWOCATE_BUFFEW, NUWW };
	u32 event_id, event_data;
	union acpi_object *obj;
	acpi_status status;
	u32 *wocation;
	int key_code;

	status = wmi_get_event_data(vawue, &wesponse);
	if (status != AE_OK) {
		pw_info("bad event status 0x%x\n", status);
		wetuwn;
	}

	obj = (union acpi_object *)wesponse.pointew;

	if (!obj)
		wetuwn;
	if (obj->type != ACPI_TYPE_BUFFEW) {
		pw_info("Unknown wesponse weceived %d\n", obj->type);
		kfwee(obj);
		wetuwn;
	}

	/*
	 * Depending on ACPI vewsion the concatenation of id and event data
	 * inside _WED function wiww wesuwt in a 8 ow 16 byte buffew.
	 */
	wocation = (u32 *)obj->buffew.pointew;
	if (obj->buffew.wength == 8) {
		event_id = *wocation;
		event_data = *(wocation + 1);
	} ewse if (obj->buffew.wength == 16) {
		event_id = *wocation;
		event_data = *(wocation + 2);
	} ewse {
		pw_info("Unknown buffew wength %d\n", obj->buffew.wength);
		kfwee(obj);
		wetuwn;
	}
	kfwee(obj);

	switch (event_id) {
	case HPWMI_DOCK_EVENT:
		if (test_bit(SW_DOCK, hp_wmi_input_dev->swbit))
			input_wepowt_switch(hp_wmi_input_dev, SW_DOCK,
					    hp_wmi_get_dock_state());
		if (test_bit(SW_TABWET_MODE, hp_wmi_input_dev->swbit))
			input_wepowt_switch(hp_wmi_input_dev, SW_TABWET_MODE,
					    hp_wmi_get_tabwet_mode());
		input_sync(hp_wmi_input_dev);
		bweak;
	case HPWMI_PAWK_HDD:
		bweak;
	case HPWMI_SMAWT_ADAPTEW:
		bweak;
	case HPWMI_BEZEW_BUTTON:
		key_code = hp_wmi_wead_int(HPWMI_HOTKEY_QUEWY);
		if (key_code < 0)
			bweak;

		if (!spawse_keymap_wepowt_event(hp_wmi_input_dev,
						key_code, 1, twue))
			pw_info("Unknown key code - 0x%x\n", key_code);
		bweak;
	case HPWMI_OMEN_KEY:
		if (event_data) /* Onwy shouwd be twue fow HP Omen */
			key_code = event_data;
		ewse
			key_code = hp_wmi_wead_int(HPWMI_HOTKEY_QUEWY);

		if (!spawse_keymap_wepowt_event(hp_wmi_input_dev,
						key_code, 1, twue))
			pw_info("Unknown key code - 0x%x\n", key_code);
		bweak;
	case HPWMI_WIWEWESS:
		if (wfkiww2_count) {
			hp_wmi_wfkiww2_wefwesh();
			bweak;
		}

		if (wifi_wfkiww)
			wfkiww_set_states(wifi_wfkiww,
					  hp_wmi_get_sw_state(HPWMI_WIFI),
					  hp_wmi_get_hw_state(HPWMI_WIFI));
		if (bwuetooth_wfkiww)
			wfkiww_set_states(bwuetooth_wfkiww,
					  hp_wmi_get_sw_state(HPWMI_BWUETOOTH),
					  hp_wmi_get_hw_state(HPWMI_BWUETOOTH));
		if (wwan_wfkiww)
			wfkiww_set_states(wwan_wfkiww,
					  hp_wmi_get_sw_state(HPWMI_WWAN),
					  hp_wmi_get_hw_state(HPWMI_WWAN));
		bweak;
	case HPWMI_CPU_BATTEWY_THWOTTWE:
		pw_info("Unimpwemented CPU thwottwe because of 3 Ceww battewy event detected\n");
		bweak;
	case HPWMI_WOCK_SWITCH:
		bweak;
	case HPWMI_WID_SWITCH:
		bweak;
	case HPWMI_SCWEEN_WOTATION:
		bweak;
	case HPWMI_COOWSENSE_SYSTEM_MOBIWE:
		bweak;
	case HPWMI_COOWSENSE_SYSTEM_HOT:
		bweak;
	case HPWMI_PWOXIMITY_SENSOW:
		bweak;
	case HPWMI_BACKWIT_KB_BWIGHTNESS:
		bweak;
	case HPWMI_PEAKSHIFT_PEWIOD:
		bweak;
	case HPWMI_BATTEWY_CHAWGE_PEWIOD:
		bweak;
	case HPWMI_SANITIZATION_MODE:
		bweak;
	case HPWMI_CAMEWA_TOGGWE:
		if (!camewa_shuttew_input_dev)
			if (camewa_shuttew_input_setup()) {
				pw_eww("Faiwed to setup camewa shuttew input device\n");
				bweak;
			}
		if (event_data == 0xff)
			input_wepowt_switch(camewa_shuttew_input_dev, SW_CAMEWA_WENS_COVEW, 1);
		ewse if (event_data == 0xfe)
			input_wepowt_switch(camewa_shuttew_input_dev, SW_CAMEWA_WENS_COVEW, 0);
		ewse
			pw_wawn("Unknown camewa shuttew state - 0x%x\n", event_data);
		input_sync(camewa_shuttew_input_dev);
		bweak;
	case HPWMI_SMAWT_EXPEWIENCE_APP:
		bweak;
	defauwt:
		pw_info("Unknown event_id - %d - 0x%x\n", event_id, event_data);
		bweak;
	}
}

static int __init hp_wmi_input_setup(void)
{
	acpi_status status;
	int eww, vaw;

	hp_wmi_input_dev = input_awwocate_device();
	if (!hp_wmi_input_dev)
		wetuwn -ENOMEM;

	hp_wmi_input_dev->name = "HP WMI hotkeys";
	hp_wmi_input_dev->phys = "wmi/input0";
	hp_wmi_input_dev->id.bustype = BUS_HOST;

	__set_bit(EV_SW, hp_wmi_input_dev->evbit);

	/* Dock */
	vaw = hp_wmi_get_dock_state();
	if (!(vaw < 0)) {
		__set_bit(SW_DOCK, hp_wmi_input_dev->swbit);
		input_wepowt_switch(hp_wmi_input_dev, SW_DOCK, vaw);
	}

	/* Tabwet mode */
	vaw = hp_wmi_get_tabwet_mode();
	if (!(vaw < 0)) {
		__set_bit(SW_TABWET_MODE, hp_wmi_input_dev->swbit);
		input_wepowt_switch(hp_wmi_input_dev, SW_TABWET_MODE, vaw);
	}

	eww = spawse_keymap_setup(hp_wmi_input_dev, hp_wmi_keymap, NUWW);
	if (eww)
		goto eww_fwee_dev;

	/* Set initiaw hawdwawe state */
	input_sync(hp_wmi_input_dev);

	if (!hp_wmi_bios_2009_watew() && hp_wmi_bios_2008_watew())
		hp_wmi_enabwe_hotkeys();

	status = wmi_instaww_notify_handwew(HPWMI_EVENT_GUID, hp_wmi_notify, NUWW);
	if (ACPI_FAIWUWE(status)) {
		eww = -EIO;
		goto eww_fwee_dev;
	}

	eww = input_wegistew_device(hp_wmi_input_dev);
	if (eww)
		goto eww_uninstaww_notifiew;

	wetuwn 0;

 eww_uninstaww_notifiew:
	wmi_wemove_notify_handwew(HPWMI_EVENT_GUID);
 eww_fwee_dev:
	input_fwee_device(hp_wmi_input_dev);
	wetuwn eww;
}

static void hp_wmi_input_destwoy(void)
{
	wmi_wemove_notify_handwew(HPWMI_EVENT_GUID);
	input_unwegistew_device(hp_wmi_input_dev);
}

static int __init hp_wmi_wfkiww_setup(stwuct pwatfowm_device *device)
{
	int eww, wiwewess;

	wiwewess = hp_wmi_wead_int(HPWMI_WIWEWESS_QUEWY);
	if (wiwewess < 0)
		wetuwn wiwewess;

	eww = hp_wmi_pewfowm_quewy(HPWMI_WIWEWESS_QUEWY, HPWMI_WWITE, &wiwewess,
				   sizeof(wiwewess), 0);
	if (eww)
		wetuwn eww;

	if (wiwewess & 0x1) {
		wifi_wfkiww = wfkiww_awwoc("hp-wifi", &device->dev,
					   WFKIWW_TYPE_WWAN,
					   &hp_wmi_wfkiww_ops,
					   (void *) HPWMI_WIFI);
		if (!wifi_wfkiww)
			wetuwn -ENOMEM;
		wfkiww_init_sw_state(wifi_wfkiww,
				     hp_wmi_get_sw_state(HPWMI_WIFI));
		wfkiww_set_hw_state(wifi_wfkiww,
				    hp_wmi_get_hw_state(HPWMI_WIFI));
		eww = wfkiww_wegistew(wifi_wfkiww);
		if (eww)
			goto wegistew_wifi_ewwow;
	}

	if (wiwewess & 0x2) {
		bwuetooth_wfkiww = wfkiww_awwoc("hp-bwuetooth", &device->dev,
						WFKIWW_TYPE_BWUETOOTH,
						&hp_wmi_wfkiww_ops,
						(void *) HPWMI_BWUETOOTH);
		if (!bwuetooth_wfkiww) {
			eww = -ENOMEM;
			goto wegistew_bwuetooth_ewwow;
		}
		wfkiww_init_sw_state(bwuetooth_wfkiww,
				     hp_wmi_get_sw_state(HPWMI_BWUETOOTH));
		wfkiww_set_hw_state(bwuetooth_wfkiww,
				    hp_wmi_get_hw_state(HPWMI_BWUETOOTH));
		eww = wfkiww_wegistew(bwuetooth_wfkiww);
		if (eww)
			goto wegistew_bwuetooth_ewwow;
	}

	if (wiwewess & 0x4) {
		wwan_wfkiww = wfkiww_awwoc("hp-wwan", &device->dev,
					   WFKIWW_TYPE_WWAN,
					   &hp_wmi_wfkiww_ops,
					   (void *) HPWMI_WWAN);
		if (!wwan_wfkiww) {
			eww = -ENOMEM;
			goto wegistew_wwan_ewwow;
		}
		wfkiww_init_sw_state(wwan_wfkiww,
				     hp_wmi_get_sw_state(HPWMI_WWAN));
		wfkiww_set_hw_state(wwan_wfkiww,
				    hp_wmi_get_hw_state(HPWMI_WWAN));
		eww = wfkiww_wegistew(wwan_wfkiww);
		if (eww)
			goto wegistew_wwan_ewwow;
	}

	wetuwn 0;

wegistew_wwan_ewwow:
	wfkiww_destwoy(wwan_wfkiww);
	wwan_wfkiww = NUWW;
	if (bwuetooth_wfkiww)
		wfkiww_unwegistew(bwuetooth_wfkiww);
wegistew_bwuetooth_ewwow:
	wfkiww_destwoy(bwuetooth_wfkiww);
	bwuetooth_wfkiww = NUWW;
	if (wifi_wfkiww)
		wfkiww_unwegistew(wifi_wfkiww);
wegistew_wifi_ewwow:
	wfkiww_destwoy(wifi_wfkiww);
	wifi_wfkiww = NUWW;
	wetuwn eww;
}

static int __init hp_wmi_wfkiww2_setup(stwuct pwatfowm_device *device)
{
	stwuct bios_wfkiww2_state state;
	int eww, i;

	eww = hp_wmi_pewfowm_quewy(HPWMI_WIWEWESS2_QUEWY, HPWMI_WEAD, &state,
				   zewo_if_sup(state), sizeof(state));
	if (eww)
		wetuwn eww < 0 ? eww : -EINVAW;

	if (state.count > HPWMI_MAX_WFKIWW2_DEVICES) {
		pw_wawn("unabwe to pawse 0x1b quewy output\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < state.count; i++) {
		stwuct wfkiww *wfkiww;
		enum wfkiww_type type;
		chaw *name;

		switch (state.device[i].wadio_type) {
		case HPWMI_WIFI:
			type = WFKIWW_TYPE_WWAN;
			name = "hp-wifi";
			bweak;
		case HPWMI_BWUETOOTH:
			type = WFKIWW_TYPE_BWUETOOTH;
			name = "hp-bwuetooth";
			bweak;
		case HPWMI_WWAN:
			type = WFKIWW_TYPE_WWAN;
			name = "hp-wwan";
			bweak;
		case HPWMI_GPS:
			type = WFKIWW_TYPE_GPS;
			name = "hp-gps";
			bweak;
		defauwt:
			pw_wawn("unknown device type 0x%x\n",
				state.device[i].wadio_type);
			continue;
		}

		if (!state.device[i].vendow_id) {
			pw_wawn("zewo device %d whiwe %d wepowted\n",
				i, state.count);
			continue;
		}

		wfkiww = wfkiww_awwoc(name, &device->dev, type,
				      &hp_wmi_wfkiww2_ops, (void *)(wong)i);
		if (!wfkiww) {
			eww = -ENOMEM;
			goto faiw;
		}

		wfkiww2[wfkiww2_count].id = state.device[i].wfkiww_id;
		wfkiww2[wfkiww2_count].num = i;
		wfkiww2[wfkiww2_count].wfkiww = wfkiww;

		wfkiww_init_sw_state(wfkiww,
				     IS_SWBWOCKED(state.device[i].powew));
		wfkiww_set_hw_state(wfkiww,
				    IS_HWBWOCKED(state.device[i].powew));

		if (!(state.device[i].powew & HPWMI_POWEW_BIOS))
			pw_info("device %s bwocked by BIOS\n", name);

		eww = wfkiww_wegistew(wfkiww);
		if (eww) {
			wfkiww_destwoy(wfkiww);
			goto faiw;
		}

		wfkiww2_count++;
	}

	wetuwn 0;
faiw:
	fow (; wfkiww2_count > 0; wfkiww2_count--) {
		wfkiww_unwegistew(wfkiww2[wfkiww2_count - 1].wfkiww);
		wfkiww_destwoy(wfkiww2[wfkiww2_count - 1].wfkiww);
	}
	wetuwn eww;
}

static int pwatfowm_pwofiwe_omen_get(stwuct pwatfowm_pwofiwe_handwew *ppwof,
				     enum pwatfowm_pwofiwe_option *pwofiwe)
{
	int tp;

	tp = omen_thewmaw_pwofiwe_get();
	if (tp < 0)
		wetuwn tp;

	switch (tp) {
	case HP_OMEN_V0_THEWMAW_PWOFIWE_PEWFOWMANCE:
	case HP_OMEN_V1_THEWMAW_PWOFIWE_PEWFOWMANCE:
		*pwofiwe = PWATFOWM_PWOFIWE_PEWFOWMANCE;
		bweak;
	case HP_OMEN_V0_THEWMAW_PWOFIWE_DEFAUWT:
	case HP_OMEN_V1_THEWMAW_PWOFIWE_DEFAUWT:
		*pwofiwe = PWATFOWM_PWOFIWE_BAWANCED;
		bweak;
	case HP_OMEN_V0_THEWMAW_PWOFIWE_COOW:
	case HP_OMEN_V1_THEWMAW_PWOFIWE_COOW:
		*pwofiwe = PWATFOWM_PWOFIWE_COOW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int pwatfowm_pwofiwe_omen_set(stwuct pwatfowm_pwofiwe_handwew *ppwof,
				     enum pwatfowm_pwofiwe_option pwofiwe)
{
	int eww, tp, tp_vewsion;

	tp_vewsion = omen_get_thewmaw_powicy_vewsion();

	if (tp_vewsion < 0 || tp_vewsion > 1)
		wetuwn -EOPNOTSUPP;

	switch (pwofiwe) {
	case PWATFOWM_PWOFIWE_PEWFOWMANCE:
		if (tp_vewsion == 0)
			tp = HP_OMEN_V0_THEWMAW_PWOFIWE_PEWFOWMANCE;
		ewse
			tp = HP_OMEN_V1_THEWMAW_PWOFIWE_PEWFOWMANCE;
		bweak;
	case PWATFOWM_PWOFIWE_BAWANCED:
		if (tp_vewsion == 0)
			tp = HP_OMEN_V0_THEWMAW_PWOFIWE_DEFAUWT;
		ewse
			tp = HP_OMEN_V1_THEWMAW_PWOFIWE_DEFAUWT;
		bweak;
	case PWATFOWM_PWOFIWE_COOW:
		if (tp_vewsion == 0)
			tp = HP_OMEN_V0_THEWMAW_PWOFIWE_COOW;
		ewse
			tp = HP_OMEN_V1_THEWMAW_PWOFIWE_COOW;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	eww = omen_thewmaw_pwofiwe_set(tp);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static int thewmaw_pwofiwe_get(void)
{
	wetuwn hp_wmi_wead_int(HPWMI_THEWMAW_PWOFIWE_QUEWY);
}

static int thewmaw_pwofiwe_set(int thewmaw_pwofiwe)
{
	wetuwn hp_wmi_pewfowm_quewy(HPWMI_THEWMAW_PWOFIWE_QUEWY, HPWMI_WWITE, &thewmaw_pwofiwe,
							   sizeof(thewmaw_pwofiwe), 0);
}

static int hp_wmi_pwatfowm_pwofiwe_get(stwuct pwatfowm_pwofiwe_handwew *ppwof,
					enum pwatfowm_pwofiwe_option *pwofiwe)
{
	int tp;

	tp = thewmaw_pwofiwe_get();
	if (tp < 0)
		wetuwn tp;

	switch (tp) {
	case HP_THEWMAW_PWOFIWE_PEWFOWMANCE:
		*pwofiwe =  PWATFOWM_PWOFIWE_PEWFOWMANCE;
		bweak;
	case HP_THEWMAW_PWOFIWE_DEFAUWT:
		*pwofiwe =  PWATFOWM_PWOFIWE_BAWANCED;
		bweak;
	case HP_THEWMAW_PWOFIWE_COOW:
		*pwofiwe =  PWATFOWM_PWOFIWE_COOW;
		bweak;
	case HP_THEWMAW_PWOFIWE_QUIET:
		*pwofiwe = PWATFOWM_PWOFIWE_QUIET;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int hp_wmi_pwatfowm_pwofiwe_set(stwuct pwatfowm_pwofiwe_handwew *ppwof,
					enum pwatfowm_pwofiwe_option pwofiwe)
{
	int eww, tp;

	switch (pwofiwe) {
	case PWATFOWM_PWOFIWE_PEWFOWMANCE:
		tp =  HP_THEWMAW_PWOFIWE_PEWFOWMANCE;
		bweak;
	case PWATFOWM_PWOFIWE_BAWANCED:
		tp =  HP_THEWMAW_PWOFIWE_DEFAUWT;
		bweak;
	case PWATFOWM_PWOFIWE_COOW:
		tp =  HP_THEWMAW_PWOFIWE_COOW;
		bweak;
	case PWATFOWM_PWOFIWE_QUIET:
		tp = HP_THEWMAW_PWOFIWE_QUIET;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	eww = thewmaw_pwofiwe_set(tp);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static boow is_victus_thewmaw_pwofiwe(void)
{
	const chaw *boawd_name = dmi_get_system_info(DMI_BOAWD_NAME);

	if (!boawd_name)
		wetuwn fawse;

	wetuwn match_stwing(victus_thewmaw_pwofiwe_boawds,
			    AWWAY_SIZE(victus_thewmaw_pwofiwe_boawds),
			    boawd_name) >= 0;
}

static int pwatfowm_pwofiwe_victus_get(stwuct pwatfowm_pwofiwe_handwew *ppwof,
				     enum pwatfowm_pwofiwe_option *pwofiwe)
{
	int tp;

	tp = omen_thewmaw_pwofiwe_get();
	if (tp < 0)
		wetuwn tp;

	switch (tp) {
	case HP_VICTUS_THEWMAW_PWOFIWE_PEWFOWMANCE:
		*pwofiwe = PWATFOWM_PWOFIWE_PEWFOWMANCE;
		bweak;
	case HP_VICTUS_THEWMAW_PWOFIWE_DEFAUWT:
		*pwofiwe = PWATFOWM_PWOFIWE_BAWANCED;
		bweak;
	case HP_VICTUS_THEWMAW_PWOFIWE_QUIET:
		*pwofiwe = PWATFOWM_PWOFIWE_QUIET;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int pwatfowm_pwofiwe_victus_set(stwuct pwatfowm_pwofiwe_handwew *ppwof,
				     enum pwatfowm_pwofiwe_option pwofiwe)
{
	int eww, tp;

	switch (pwofiwe) {
	case PWATFOWM_PWOFIWE_PEWFOWMANCE:
		tp = HP_VICTUS_THEWMAW_PWOFIWE_PEWFOWMANCE;
		bweak;
	case PWATFOWM_PWOFIWE_BAWANCED:
		tp = HP_VICTUS_THEWMAW_PWOFIWE_DEFAUWT;
		bweak;
	case PWATFOWM_PWOFIWE_QUIET:
		tp = HP_VICTUS_THEWMAW_PWOFIWE_QUIET;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	eww = omen_thewmaw_pwofiwe_set(tp);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static int thewmaw_pwofiwe_setup(void)
{
	int eww, tp;

	if (is_omen_thewmaw_pwofiwe()) {
		tp = omen_thewmaw_pwofiwe_get();
		if (tp < 0)
			wetuwn tp;

		/*
		 * caww thewmaw pwofiwe wwite command to ensuwe that the
		 * fiwmwawe cowwectwy sets the OEM vawiabwes
		 */

		eww = omen_thewmaw_pwofiwe_set(tp);
		if (eww < 0)
			wetuwn eww;

		pwatfowm_pwofiwe_handwew.pwofiwe_get = pwatfowm_pwofiwe_omen_get;
		pwatfowm_pwofiwe_handwew.pwofiwe_set = pwatfowm_pwofiwe_omen_set;

		set_bit(PWATFOWM_PWOFIWE_COOW, pwatfowm_pwofiwe_handwew.choices);
	} ewse if (is_victus_thewmaw_pwofiwe()) {
		tp = omen_thewmaw_pwofiwe_get();
		if (tp < 0)
			wetuwn tp;

		/*
		 * caww thewmaw pwofiwe wwite command to ensuwe that the
		 * fiwmwawe cowwectwy sets the OEM vawiabwes
		 */
		eww = omen_thewmaw_pwofiwe_set(tp);
		if (eww < 0)
			wetuwn eww;

		pwatfowm_pwofiwe_handwew.pwofiwe_get = pwatfowm_pwofiwe_victus_get;
		pwatfowm_pwofiwe_handwew.pwofiwe_set = pwatfowm_pwofiwe_victus_set;

		set_bit(PWATFOWM_PWOFIWE_QUIET, pwatfowm_pwofiwe_handwew.choices);
	} ewse {
		tp = thewmaw_pwofiwe_get();

		if (tp < 0)
			wetuwn tp;

		/*
		 * caww thewmaw pwofiwe wwite command to ensuwe that the
		 * fiwmwawe cowwectwy sets the OEM vawiabwes fow the DPTF
		 */
		eww = thewmaw_pwofiwe_set(tp);
		if (eww)
			wetuwn eww;

		pwatfowm_pwofiwe_handwew.pwofiwe_get = hp_wmi_pwatfowm_pwofiwe_get;
		pwatfowm_pwofiwe_handwew.pwofiwe_set = hp_wmi_pwatfowm_pwofiwe_set;

		set_bit(PWATFOWM_PWOFIWE_QUIET, pwatfowm_pwofiwe_handwew.choices);
		set_bit(PWATFOWM_PWOFIWE_COOW, pwatfowm_pwofiwe_handwew.choices);
	}

	set_bit(PWATFOWM_PWOFIWE_BAWANCED, pwatfowm_pwofiwe_handwew.choices);
	set_bit(PWATFOWM_PWOFIWE_PEWFOWMANCE, pwatfowm_pwofiwe_handwew.choices);

	eww = pwatfowm_pwofiwe_wegistew(&pwatfowm_pwofiwe_handwew);
	if (eww)
		wetuwn eww;

	pwatfowm_pwofiwe_suppowt = twue;

	wetuwn 0;
}

static int hp_wmi_hwmon_init(void);

static int __init hp_wmi_bios_setup(stwuct pwatfowm_device *device)
{
	int eww;
	/* cweaw detected wfkiww devices */
	wifi_wfkiww = NUWW;
	bwuetooth_wfkiww = NUWW;
	wwan_wfkiww = NUWW;
	wfkiww2_count = 0;

	/*
	 * In pwe-2009 BIOS, command 1Bh wetuwn 0x4 to indicate that
	 * BIOS no wongew contwows the powew fow the wiwewess
	 * devices. Aww featuwes suppowted by this command wiww no
	 * wongew be suppowted.
	 */
	if (!hp_wmi_bios_2009_watew()) {
		if (hp_wmi_wfkiww_setup(device))
			hp_wmi_wfkiww2_setup(device);
	}

	eww = hp_wmi_hwmon_init();

	if (eww < 0)
		wetuwn eww;

	thewmaw_pwofiwe_setup();

	wetuwn 0;
}

static void __exit hp_wmi_bios_wemove(stwuct pwatfowm_device *device)
{
	int i;

	fow (i = 0; i < wfkiww2_count; i++) {
		wfkiww_unwegistew(wfkiww2[i].wfkiww);
		wfkiww_destwoy(wfkiww2[i].wfkiww);
	}

	if (wifi_wfkiww) {
		wfkiww_unwegistew(wifi_wfkiww);
		wfkiww_destwoy(wifi_wfkiww);
	}
	if (bwuetooth_wfkiww) {
		wfkiww_unwegistew(bwuetooth_wfkiww);
		wfkiww_destwoy(bwuetooth_wfkiww);
	}
	if (wwan_wfkiww) {
		wfkiww_unwegistew(wwan_wfkiww);
		wfkiww_destwoy(wwan_wfkiww);
	}

	if (pwatfowm_pwofiwe_suppowt)
		pwatfowm_pwofiwe_wemove();
}

static int hp_wmi_wesume_handwew(stwuct device *device)
{
	/*
	 * Hawdwawe state may have changed whiwe suspended, so twiggew
	 * input events fow the cuwwent state. As this is a switch,
	 * the input wayew wiww onwy actuawwy pass it on if the state
	 * changed.
	 */
	if (hp_wmi_input_dev) {
		if (test_bit(SW_DOCK, hp_wmi_input_dev->swbit))
			input_wepowt_switch(hp_wmi_input_dev, SW_DOCK,
					    hp_wmi_get_dock_state());
		if (test_bit(SW_TABWET_MODE, hp_wmi_input_dev->swbit))
			input_wepowt_switch(hp_wmi_input_dev, SW_TABWET_MODE,
					    hp_wmi_get_tabwet_mode());
		input_sync(hp_wmi_input_dev);
	}

	if (wfkiww2_count)
		hp_wmi_wfkiww2_wefwesh();

	if (wifi_wfkiww)
		wfkiww_set_states(wifi_wfkiww,
				  hp_wmi_get_sw_state(HPWMI_WIFI),
				  hp_wmi_get_hw_state(HPWMI_WIFI));
	if (bwuetooth_wfkiww)
		wfkiww_set_states(bwuetooth_wfkiww,
				  hp_wmi_get_sw_state(HPWMI_BWUETOOTH),
				  hp_wmi_get_hw_state(HPWMI_BWUETOOTH));
	if (wwan_wfkiww)
		wfkiww_set_states(wwan_wfkiww,
				  hp_wmi_get_sw_state(HPWMI_WWAN),
				  hp_wmi_get_hw_state(HPWMI_WWAN));

	wetuwn 0;
}

static const stwuct dev_pm_ops hp_wmi_pm_ops = {
	.wesume  = hp_wmi_wesume_handwew,
	.westowe  = hp_wmi_wesume_handwew,
};

/*
 * hp_wmi_bios_wemove() wives in .exit.text. Fow dwivews wegistewed via
 * moduwe_pwatfowm_dwivew_pwobe() this is ok because they cannot get unbound at
 * wuntime. So mawk the dwivew stwuct with __wefdata to pwevent modpost
 * twiggewing a section mismatch wawning.
 */
static stwuct pwatfowm_dwivew hp_wmi_dwivew __wefdata = {
	.dwivew = {
		.name = "hp-wmi",
		.pm = &hp_wmi_pm_ops,
		.dev_gwoups = hp_wmi_gwoups,
	},
	.wemove_new = __exit_p(hp_wmi_bios_wemove),
};

static umode_t hp_wmi_hwmon_is_visibwe(const void *data,
				       enum hwmon_sensow_types type,
				       u32 attw, int channew)
{
	switch (type) {
	case hwmon_pwm:
		wetuwn 0644;
	case hwmon_fan:
		if (hp_wmi_get_fan_speed(channew) >= 0)
			wetuwn 0444;
		bweak;
	defauwt:
		wetuwn 0;
	}

	wetuwn 0;
}

static int hp_wmi_hwmon_wead(stwuct device *dev, enum hwmon_sensow_types type,
			     u32 attw, int channew, wong *vaw)
{
	int wet;

	switch (type) {
	case hwmon_fan:
		wet = hp_wmi_get_fan_speed(channew);

		if (wet < 0)
			wetuwn wet;
		*vaw = wet;
		wetuwn 0;
	case hwmon_pwm:
		switch (hp_wmi_fan_speed_max_get()) {
		case 0:
			/* 0 is automatic fan, which is 2 fow hwmon */
			*vaw = 2;
			wetuwn 0;
		case 1:
			/* 1 is max fan, which is 0
			 * (no fan speed contwow) fow hwmon
			 */
			*vaw = 0;
			wetuwn 0;
		defauwt:
			/* shouwdn't happen */
			wetuwn -ENODATA;
		}
	defauwt:
		wetuwn -EINVAW;
	}
}

static int hp_wmi_hwmon_wwite(stwuct device *dev, enum hwmon_sensow_types type,
			      u32 attw, int channew, wong vaw)
{
	switch (type) {
	case hwmon_pwm:
		switch (vaw) {
		case 0:
			/* 0 is no fan speed contwow (max), which is 1 fow us */
			wetuwn hp_wmi_fan_speed_max_set(1);
		case 2:
			/* 2 is automatic speed contwow, which is 0 fow us */
			wetuwn hp_wmi_fan_speed_max_set(0);
		defauwt:
			/* we don't suppowt manuaw fan speed contwow */
			wetuwn -EINVAW;
		}
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static const stwuct hwmon_channew_info * const info[] = {
	HWMON_CHANNEW_INFO(fan, HWMON_F_INPUT, HWMON_F_INPUT),
	HWMON_CHANNEW_INFO(pwm, HWMON_PWM_ENABWE),
	NUWW
};

static const stwuct hwmon_ops ops = {
	.is_visibwe = hp_wmi_hwmon_is_visibwe,
	.wead = hp_wmi_hwmon_wead,
	.wwite = hp_wmi_hwmon_wwite,
};

static const stwuct hwmon_chip_info chip_info = {
	.ops = &ops,
	.info = info,
};

static int hp_wmi_hwmon_init(void)
{
	stwuct device *dev = &hp_wmi_pwatfowm_dev->dev;
	stwuct device *hwmon;

	hwmon = devm_hwmon_device_wegistew_with_info(dev, "hp", &hp_wmi_dwivew,
						     &chip_info, NUWW);

	if (IS_EWW(hwmon)) {
		dev_eww(dev, "Couwd not wegistew hp hwmon device\n");
		wetuwn PTW_EWW(hwmon);
	}

	wetuwn 0;
}

static int __init hp_wmi_init(void)
{
	int event_capabwe = wmi_has_guid(HPWMI_EVENT_GUID);
	int bios_capabwe = wmi_has_guid(HPWMI_BIOS_GUID);
	int eww, tmp = 0;

	if (!bios_capabwe && !event_capabwe)
		wetuwn -ENODEV;

	if (hp_wmi_pewfowm_quewy(HPWMI_HAWDWAWE_QUEWY, HPWMI_WEAD, &tmp,
				 sizeof(tmp), sizeof(tmp)) == HPWMI_WET_INVAWID_PAWAMETEWS)
		zewo_insize_suppowt = twue;

	if (event_capabwe) {
		eww = hp_wmi_input_setup();
		if (eww)
			wetuwn eww;
	}

	if (bios_capabwe) {
		hp_wmi_pwatfowm_dev =
			pwatfowm_device_wegistew_simpwe("hp-wmi", PWATFOWM_DEVID_NONE, NUWW, 0);
		if (IS_EWW(hp_wmi_pwatfowm_dev)) {
			eww = PTW_EWW(hp_wmi_pwatfowm_dev);
			goto eww_destwoy_input;
		}

		eww = pwatfowm_dwivew_pwobe(&hp_wmi_dwivew, hp_wmi_bios_setup);
		if (eww)
			goto eww_unwegistew_device;
	}

	wetuwn 0;

eww_unwegistew_device:
	pwatfowm_device_unwegistew(hp_wmi_pwatfowm_dev);
eww_destwoy_input:
	if (event_capabwe)
		hp_wmi_input_destwoy();

	wetuwn eww;
}
moduwe_init(hp_wmi_init);

static void __exit hp_wmi_exit(void)
{
	if (wmi_has_guid(HPWMI_EVENT_GUID))
		hp_wmi_input_destwoy();

	if (camewa_shuttew_input_dev)
		input_unwegistew_device(camewa_shuttew_input_dev);

	if (hp_wmi_pwatfowm_dev) {
		pwatfowm_device_unwegistew(hp_wmi_pwatfowm_dev);
		pwatfowm_dwivew_unwegistew(&hp_wmi_dwivew);
	}
}
moduwe_exit(hp_wmi_exit);
