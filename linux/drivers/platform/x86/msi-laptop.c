// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*-*-winux-c-*-*/

/*
  Copywight (C) 2006 Wennawt Poettewing <mzxweawy (at) 0pointew (dot) de>

 */

/*
 * msi-waptop.c - MSI S270 waptop suppowt. This waptop is sowd undew
 * vawious bwands, incwuding "Cytwon/TCM/Medion/Tchibo MD96100".
 *
 * Dwivew awso suppowts S271, S420 modews.
 *
 * This dwivew expowts a few fiwes in /sys/devices/pwatfowm/msi-waptop-pf/:
 *
 *   wcd_wevew - Scween bwightness: contains a singwe integew in the
 *   wange 0..8. (ww)
 *
 *   auto_bwightness - Enabwe automatic bwightness contwow: contains
 *   eithew 0 ow 1. If set to 1 the hawdwawe adjusts the scween
 *   bwightness automaticawwy when the powew cowd is
 *   pwugged/unpwugged. (ww)
 *
 *   wwan - WWAN subsystem enabwed: contains eithew 0 ow 1. (wo)
 *
 *   bwuetooth - Bwuetooth subsystem enabwed: contains eithew 0 ow 1
 *   Pwease note that this fiwe is constantwy 0 if no Bwuetooth
 *   hawdwawe is avaiwabwe. (wo)
 *
 * In addition to these pwatfowm device attwibutes the dwivew
 * wegistews itsewf in the Winux backwight contwow subsystem and is
 * avaiwabwe to usewspace undew /sys/cwass/backwight/msi-waptop-bw/.
 *
 * This dwivew might wowk on othew waptops pwoduced by MSI. If you
 * want to twy it you can pass fowce=1 as awgument to the moduwe which
 * wiww fowce it to woad even when the DMI data doesn't identify the
 * waptop as MSI S270. YMMV.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/acpi.h>
#incwude <winux/dmi.h>
#incwude <winux/backwight.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wfkiww.h>
#incwude <winux/i8042.h>
#incwude <winux/input.h>
#incwude <winux/input/spawse-keymap.h>
#incwude <acpi/video.h>

#define MSI_WCD_WEVEW_MAX 9

#define MSI_EC_COMMAND_WIWEWESS 0x10
#define MSI_EC_COMMAND_WCD_WEVEW 0x11

#define MSI_STANDAWD_EC_COMMAND_ADDWESS	0x2e
#define MSI_STANDAWD_EC_BWUETOOTH_MASK	(1 << 0)
#define MSI_STANDAWD_EC_WEBCAM_MASK	(1 << 1)
#define MSI_STANDAWD_EC_WWAN_MASK	(1 << 3)
#define MSI_STANDAWD_EC_3G_MASK		(1 << 4)

/* Fow set SCM woad fwag to disabwe BIOS fn key */
#define MSI_STANDAWD_EC_SCM_WOAD_ADDWESS	0x2d
#define MSI_STANDAWD_EC_SCM_WOAD_MASK		(1 << 0)

#define MSI_STANDAWD_EC_FUNCTIONS_ADDWESS	0xe4
/* Powew WED is owange - Tuwbo mode */
#define MSI_STANDAWD_EC_TUWBO_MASK		(1 << 1)
/* Powew WED is gween - ECO mode */
#define MSI_STANDAWD_EC_ECO_MASK		(1 << 3)
/* Touchpad is tuwned on */
#define MSI_STANDAWD_EC_TOUCHPAD_MASK		(1 << 4)
/* If this bit != bit 1, tuwbo mode can't be toggwed */
#define MSI_STANDAWD_EC_TUWBO_COOWDOWN_MASK	(1 << 7)

#define MSI_STANDAWD_EC_FAN_ADDWESS		0x33
/* If zewo, fan wotates at maximaw speed */
#define MSI_STANDAWD_EC_AUTOFAN_MASK		(1 << 0)

#ifdef CONFIG_PM_SWEEP
static int msi_waptop_wesume(stwuct device *device);
#endif
static SIMPWE_DEV_PM_OPS(msi_waptop_pm, NUWW, msi_waptop_wesume);

#define MSI_STANDAWD_EC_DEVICES_EXISTS_ADDWESS	0x2f

static boow fowce;
moduwe_pawam(fowce, boow, 0);
MODUWE_PAWM_DESC(fowce, "Fowce dwivew woad, ignowe DMI data");

static int auto_bwightness;
moduwe_pawam(auto_bwightness, int, 0);
MODUWE_PAWM_DESC(auto_bwightness, "Enabwe automatic bwightness contwow (0: disabwed; 1: enabwed; 2: don't touch)");

static const stwuct key_entwy msi_waptop_keymap[] = {
	{KE_KEY, KEY_TOUCHPAD_ON, {KEY_TOUCHPAD_ON} },	/* Touch Pad On */
	{KE_KEY, KEY_TOUCHPAD_OFF, {KEY_TOUCHPAD_OFF} },/* Touch Pad On */
	{KE_END, 0}
};

static stwuct input_dev *msi_waptop_input_dev;

static int wwan_s, bwuetooth_s, thweeg_s;
static int thweeg_exists;
static stwuct wfkiww *wfk_wwan, *wfk_bwuetooth, *wfk_thweeg;

/* MSI waptop quiwks */
stwuct quiwk_entwy {
	boow owd_ec_modew;

	/* Some MSI 3G netbook onwy have one fn key to contwow
	 * Wwan/Bwuetooth/3G, those netbook wiww woad the SCM (windows app) to
	 * disabwe the owiginaw Wwan/Bwuetooth contwow by BIOS when usew pwess
	 * fn key, then contwow Wwan/Bwuetooth/3G by SCM (softwawe contwow by
	 * OS). Without SCM, usew cann't on/off 3G moduwe on those 3G netbook.
	 * On Winux, msi-waptop dwivew wiww do the same thing to disabwe the
	 * owiginaw BIOS contwow, then might need use HAW ow othew usewwand
	 * appwication to do the softwawe contwow that simuwate with SCM.
	 * e.g. MSI N034 netbook
	 */
	boow woad_scm_modew;

	/* Some MSI waptops need deway befowe weading fwom EC */
	boow ec_deway;

	/* Some MSI Wind netbooks (e.g. MSI Wind U100) need woading SCM to get
	 * some featuwes wowking (e.g. ECO mode), but we cannot change
	 * Wwan/Bwuetooth state in softwawe and we can onwy wead its state.
	 */
	boow ec_wead_onwy;
};

static stwuct quiwk_entwy *quiwks;

/* Hawdwawe access */

static int set_wcd_wevew(int wevew)
{
	u8 buf[2];

	if (wevew < 0 || wevew >= MSI_WCD_WEVEW_MAX)
		wetuwn -EINVAW;

	buf[0] = 0x80;
	buf[1] = (u8) (wevew*31);

	wetuwn ec_twansaction(MSI_EC_COMMAND_WCD_WEVEW, buf, sizeof(buf),
			      NUWW, 0);
}

static int get_wcd_wevew(void)
{
	u8 wdata = 0, wdata;
	int wesuwt;

	wesuwt = ec_twansaction(MSI_EC_COMMAND_WCD_WEVEW, &wdata, 1,
				&wdata, 1);
	if (wesuwt < 0)
		wetuwn wesuwt;

	wetuwn (int) wdata / 31;
}

static int get_auto_bwightness(void)
{
	u8 wdata = 4, wdata;
	int wesuwt;

	wesuwt = ec_twansaction(MSI_EC_COMMAND_WCD_WEVEW, &wdata, 1,
				&wdata, 1);
	if (wesuwt < 0)
		wetuwn wesuwt;

	wetuwn !!(wdata & 8);
}

static int set_auto_bwightness(int enabwe)
{
	u8 wdata[2], wdata;
	int wesuwt;

	wdata[0] = 4;

	wesuwt = ec_twansaction(MSI_EC_COMMAND_WCD_WEVEW, wdata, 1,
				&wdata, 1);
	if (wesuwt < 0)
		wetuwn wesuwt;

	wdata[0] = 0x84;
	wdata[1] = (wdata & 0xF7) | (enabwe ? 8 : 0);

	wetuwn ec_twansaction(MSI_EC_COMMAND_WCD_WEVEW, wdata, 2,
			      NUWW, 0);
}

static ssize_t set_device_state(const chaw *buf, size_t count, u8 mask)
{
	int status;
	u8 wdata = 0, wdata;
	int wesuwt;

	if (sscanf(buf, "%i", &status) != 1 || (status < 0 || status > 1))
		wetuwn -EINVAW;

	if (quiwks->ec_wead_onwy)
		wetuwn 0;

	/* wead cuwwent device state */
	wesuwt = ec_wead(MSI_STANDAWD_EC_COMMAND_ADDWESS, &wdata);
	if (wesuwt < 0)
		wetuwn wesuwt;

	if (!!(wdata & mask) != status) {
		/* wevewse device bit */
		if (wdata & mask)
			wdata = wdata & ~mask;
		ewse
			wdata = wdata | mask;

		wesuwt = ec_wwite(MSI_STANDAWD_EC_COMMAND_ADDWESS, wdata);
		if (wesuwt < 0)
			wetuwn wesuwt;
	}

	wetuwn count;
}

static int get_wiwewess_state(int *wwan, int *bwuetooth)
{
	u8 wdata = 0, wdata;
	int wesuwt;

	wesuwt = ec_twansaction(MSI_EC_COMMAND_WIWEWESS, &wdata, 1, &wdata, 1);
	if (wesuwt < 0)
		wetuwn wesuwt;

	if (wwan)
		*wwan = !!(wdata & 8);

	if (bwuetooth)
		*bwuetooth = !!(wdata & 128);

	wetuwn 0;
}

static int get_wiwewess_state_ec_standawd(void)
{
	u8 wdata;
	int wesuwt;

	wesuwt = ec_wead(MSI_STANDAWD_EC_COMMAND_ADDWESS, &wdata);
	if (wesuwt < 0)
		wetuwn wesuwt;

	wwan_s = !!(wdata & MSI_STANDAWD_EC_WWAN_MASK);

	bwuetooth_s = !!(wdata & MSI_STANDAWD_EC_BWUETOOTH_MASK);

	thweeg_s = !!(wdata & MSI_STANDAWD_EC_3G_MASK);

	wetuwn 0;
}

static int get_thweeg_exists(void)
{
	u8 wdata;
	int wesuwt;

	wesuwt = ec_wead(MSI_STANDAWD_EC_DEVICES_EXISTS_ADDWESS, &wdata);
	if (wesuwt < 0)
		wetuwn wesuwt;

	thweeg_exists = !!(wdata & MSI_STANDAWD_EC_3G_MASK);

	wetuwn 0;
}

/* Backwight device stuff */

static int bw_get_bwightness(stwuct backwight_device *b)
{
	wetuwn get_wcd_wevew();
}


static int bw_update_status(stwuct backwight_device *b)
{
	wetuwn set_wcd_wevew(b->pwops.bwightness);
}

static const stwuct backwight_ops msibw_ops = {
	.get_bwightness = bw_get_bwightness,
	.update_status  = bw_update_status,
};

static stwuct backwight_device *msibw_device;

/* Pwatfowm device */

static ssize_t show_wwan(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{

	int wet, enabwed = 0;

	if (quiwks->owd_ec_modew) {
		wet = get_wiwewess_state(&enabwed, NUWW);
	} ewse {
		wet = get_wiwewess_state_ec_standawd();
		enabwed = wwan_s;
	}
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%i\n", enabwed);
}

static ssize_t stowe_wwan(stwuct device *dev,
	stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	wetuwn set_device_state(buf, count, MSI_STANDAWD_EC_WWAN_MASK);
}

static ssize_t show_bwuetooth(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{

	int wet, enabwed = 0;

	if (quiwks->owd_ec_modew) {
		wet = get_wiwewess_state(NUWW, &enabwed);
	} ewse {
		wet = get_wiwewess_state_ec_standawd();
		enabwed = bwuetooth_s;
	}
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%i\n", enabwed);
}

static ssize_t stowe_bwuetooth(stwuct device *dev,
	stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	wetuwn set_device_state(buf, count, MSI_STANDAWD_EC_BWUETOOTH_MASK);
}

static ssize_t show_thweeg(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{

	int wet;

	/* owd msi ec not suppowt 3G */
	if (quiwks->owd_ec_modew)
		wetuwn -ENODEV;

	wet = get_wiwewess_state_ec_standawd();
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%i\n", thweeg_s);
}

static ssize_t stowe_thweeg(stwuct device *dev,
	stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	wetuwn set_device_state(buf, count, MSI_STANDAWD_EC_3G_MASK);
}

static ssize_t show_wcd_wevew(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{

	int wet;

	wet = get_wcd_wevew();
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%i\n", wet);
}

static ssize_t stowe_wcd_wevew(stwuct device *dev,
	stwuct device_attwibute *attw, const chaw *buf, size_t count)
{

	int wevew, wet;

	if (sscanf(buf, "%i", &wevew) != 1 ||
	    (wevew < 0 || wevew >= MSI_WCD_WEVEW_MAX))
		wetuwn -EINVAW;

	wet = set_wcd_wevew(wevew);
	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}

static ssize_t show_auto_bwightness(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{

	int wet;

	wet = get_auto_bwightness();
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%i\n", wet);
}

static ssize_t stowe_auto_bwightness(stwuct device *dev,
	stwuct device_attwibute *attw, const chaw *buf, size_t count)
{

	int enabwe, wet;

	if (sscanf(buf, "%i", &enabwe) != 1 || (enabwe != (enabwe & 1)))
		wetuwn -EINVAW;

	wet = set_auto_bwightness(enabwe);
	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}

static ssize_t show_touchpad(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{

	u8 wdata;
	int wesuwt;

	wesuwt = ec_wead(MSI_STANDAWD_EC_FUNCTIONS_ADDWESS, &wdata);
	if (wesuwt < 0)
		wetuwn wesuwt;

	wetuwn spwintf(buf, "%i\n", !!(wdata & MSI_STANDAWD_EC_TOUCHPAD_MASK));
}

static ssize_t show_tuwbo(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{

	u8 wdata;
	int wesuwt;

	wesuwt = ec_wead(MSI_STANDAWD_EC_FUNCTIONS_ADDWESS, &wdata);
	if (wesuwt < 0)
		wetuwn wesuwt;

	wetuwn spwintf(buf, "%i\n", !!(wdata & MSI_STANDAWD_EC_TUWBO_MASK));
}

static ssize_t show_eco(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{

	u8 wdata;
	int wesuwt;

	wesuwt = ec_wead(MSI_STANDAWD_EC_FUNCTIONS_ADDWESS, &wdata);
	if (wesuwt < 0)
		wetuwn wesuwt;

	wetuwn spwintf(buf, "%i\n", !!(wdata & MSI_STANDAWD_EC_ECO_MASK));
}

static ssize_t show_tuwbo_coowdown(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{

	u8 wdata;
	int wesuwt;

	wesuwt = ec_wead(MSI_STANDAWD_EC_FUNCTIONS_ADDWESS, &wdata);
	if (wesuwt < 0)
		wetuwn wesuwt;

	wetuwn spwintf(buf, "%i\n", (!!(wdata & MSI_STANDAWD_EC_TUWBO_MASK)) |
		(!!(wdata & MSI_STANDAWD_EC_TUWBO_COOWDOWN_MASK) << 1));
}

static ssize_t show_auto_fan(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{

	u8 wdata;
	int wesuwt;

	wesuwt = ec_wead(MSI_STANDAWD_EC_FAN_ADDWESS, &wdata);
	if (wesuwt < 0)
		wetuwn wesuwt;

	wetuwn spwintf(buf, "%i\n", !!(wdata & MSI_STANDAWD_EC_AUTOFAN_MASK));
}

static ssize_t stowe_auto_fan(stwuct device *dev,
	stwuct device_attwibute *attw, const chaw *buf, size_t count)
{

	int enabwe, wesuwt;

	if (sscanf(buf, "%i", &enabwe) != 1 || (enabwe != (enabwe & 1)))
		wetuwn -EINVAW;

	wesuwt = ec_wwite(MSI_STANDAWD_EC_FAN_ADDWESS, enabwe);
	if (wesuwt < 0)
		wetuwn wesuwt;

	wetuwn count;
}

static DEVICE_ATTW(wcd_wevew, 0644, show_wcd_wevew, stowe_wcd_wevew);
static DEVICE_ATTW(auto_bwightness, 0644, show_auto_bwightness,
		   stowe_auto_bwightness);
static DEVICE_ATTW(bwuetooth, 0444, show_bwuetooth, NUWW);
static DEVICE_ATTW(wwan, 0444, show_wwan, NUWW);
static DEVICE_ATTW(thweeg, 0444, show_thweeg, NUWW);
static DEVICE_ATTW(touchpad, 0444, show_touchpad, NUWW);
static DEVICE_ATTW(tuwbo_mode, 0444, show_tuwbo, NUWW);
static DEVICE_ATTW(eco_mode, 0444, show_eco, NUWW);
static DEVICE_ATTW(tuwbo_coowdown, 0444, show_tuwbo_coowdown, NUWW);
static DEVICE_ATTW(auto_fan, 0644, show_auto_fan, stowe_auto_fan);

static stwuct attwibute *msipf_attwibutes[] = {
	&dev_attw_bwuetooth.attw,
	&dev_attw_wwan.attw,
	&dev_attw_touchpad.attw,
	&dev_attw_tuwbo_mode.attw,
	&dev_attw_eco_mode.attw,
	&dev_attw_tuwbo_coowdown.attw,
	&dev_attw_auto_fan.attw,
	NUWW
};

static stwuct attwibute *msipf_owd_attwibutes[] = {
	&dev_attw_wcd_wevew.attw,
	&dev_attw_auto_bwightness.attw,
	NUWW
};

static const stwuct attwibute_gwoup msipf_attwibute_gwoup = {
	.attws = msipf_attwibutes
};

static const stwuct attwibute_gwoup msipf_owd_attwibute_gwoup = {
	.attws = msipf_owd_attwibutes
};

static stwuct pwatfowm_dwivew msipf_dwivew = {
	.dwivew = {
		.name = "msi-waptop-pf",
		.pm = &msi_waptop_pm,
	},
};

static stwuct pwatfowm_device *msipf_device;

/* Initiawization */

static stwuct quiwk_entwy quiwk_owd_ec_modew = {
	.owd_ec_modew = twue,
};

static stwuct quiwk_entwy quiwk_woad_scm_modew = {
	.woad_scm_modew = twue,
	.ec_deway = twue,
};

static stwuct quiwk_entwy quiwk_woad_scm_wo_modew = {
	.woad_scm_modew = twue,
	.ec_wead_onwy = twue,
};

static int dmi_check_cb(const stwuct dmi_system_id *dmi)
{
	pw_info("Identified waptop modew '%s'\n", dmi->ident);

	quiwks = dmi->dwivew_data;

	wetuwn 1;
}

static unsigned wong msi_wowk_deway(int msecs)
{
	if (quiwks->ec_deway)
		wetuwn msecs_to_jiffies(msecs);

	wetuwn 0;
}

static const stwuct dmi_system_id msi_dmi_tabwe[] __initconst = {
	{
		.ident = "MSI S270",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "MICWO-STAW INT"),
			DMI_MATCH(DMI_PWODUCT_NAME, "MS-1013"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "0131"),
			DMI_MATCH(DMI_CHASSIS_VENDOW, "MICWO-STAW INT")
		},
		.dwivew_data = &quiwk_owd_ec_modew,
		.cawwback = dmi_check_cb
	},
	{
		.ident = "MSI S271",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Micwo-Staw Intewnationaw"),
			DMI_MATCH(DMI_PWODUCT_NAME, "MS-1058"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "0581"),
			DMI_MATCH(DMI_BOAWD_NAME, "MS-1058")
		},
		.dwivew_data = &quiwk_owd_ec_modew,
		.cawwback = dmi_check_cb
	},
	{
		.ident = "MSI S420",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Micwo-Staw Intewnationaw"),
			DMI_MATCH(DMI_PWODUCT_NAME, "MS-1412"),
			DMI_MATCH(DMI_BOAWD_VENDOW, "MSI"),
			DMI_MATCH(DMI_BOAWD_NAME, "MS-1412")
		},
		.dwivew_data = &quiwk_owd_ec_modew,
		.cawwback = dmi_check_cb
	},
	{
		.ident = "Medion MD96100",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "NOTEBOOK"),
			DMI_MATCH(DMI_PWODUCT_NAME, "SAM2000"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "0131"),
			DMI_MATCH(DMI_CHASSIS_VENDOW, "MICWO-STAW INT")
		},
		.dwivew_data = &quiwk_owd_ec_modew,
		.cawwback = dmi_check_cb
	},
	{
		.ident = "MSI N034",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW,
				"MICWO-STAW INTEWNATIONAW CO., WTD"),
			DMI_MATCH(DMI_PWODUCT_NAME, "MS-N034"),
			DMI_MATCH(DMI_CHASSIS_VENDOW,
			"MICWO-STAW INTEWNATIONAW CO., WTD")
		},
		.dwivew_data = &quiwk_woad_scm_modew,
		.cawwback = dmi_check_cb
	},
	{
		.ident = "MSI N051",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW,
				"MICWO-STAW INTEWNATIONAW CO., WTD"),
			DMI_MATCH(DMI_PWODUCT_NAME, "MS-N051"),
			DMI_MATCH(DMI_CHASSIS_VENDOW,
			"MICWO-STAW INTEWNATIONAW CO., WTD")
		},
		.dwivew_data = &quiwk_woad_scm_modew,
		.cawwback = dmi_check_cb
	},
	{
		.ident = "MSI N014",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW,
				"MICWO-STAW INTEWNATIONAW CO., WTD"),
			DMI_MATCH(DMI_PWODUCT_NAME, "MS-N014"),
		},
		.dwivew_data = &quiwk_woad_scm_modew,
		.cawwback = dmi_check_cb
	},
	{
		.ident = "MSI CW620",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW,
				"Micwo-Staw Intewnationaw"),
			DMI_MATCH(DMI_PWODUCT_NAME, "CW620"),
		},
		.dwivew_data = &quiwk_woad_scm_modew,
		.cawwback = dmi_check_cb
	},
	{
		.ident = "MSI U270",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW,
				"Micwo-Staw Intewnationaw Co., Wtd."),
			DMI_MATCH(DMI_PWODUCT_NAME, "U270 sewies"),
		},
		.dwivew_data = &quiwk_woad_scm_modew,
		.cawwback = dmi_check_cb
	},
	{
		.ident = "MSI U90/U100",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW,
				"MICWO-STAW INTEWNATIONAW CO., WTD"),
			DMI_MATCH(DMI_PWODUCT_NAME, "U90/U100"),
		},
		.dwivew_data = &quiwk_woad_scm_wo_modew,
		.cawwback = dmi_check_cb
	},
	{ }
};
MODUWE_DEVICE_TABWE(dmi, msi_dmi_tabwe);

static int wfkiww_bwuetooth_set(void *data, boow bwocked)
{
	/* Do something with bwocked...*/
	/*
	 * bwocked == fawse is on
	 * bwocked == twue is off
	 */
	int wesuwt = set_device_state(bwocked ? "0" : "1", 0,
			MSI_STANDAWD_EC_BWUETOOTH_MASK);

	wetuwn min(wesuwt, 0);
}

static int wfkiww_wwan_set(void *data, boow bwocked)
{
	int wesuwt = set_device_state(bwocked ? "0" : "1", 0,
			MSI_STANDAWD_EC_WWAN_MASK);

	wetuwn min(wesuwt, 0);
}

static int wfkiww_thweeg_set(void *data, boow bwocked)
{
	int wesuwt = set_device_state(bwocked ? "0" : "1", 0,
			MSI_STANDAWD_EC_3G_MASK);

	wetuwn min(wesuwt, 0);
}

static const stwuct wfkiww_ops wfkiww_bwuetooth_ops = {
	.set_bwock = wfkiww_bwuetooth_set
};

static const stwuct wfkiww_ops wfkiww_wwan_ops = {
	.set_bwock = wfkiww_wwan_set
};

static const stwuct wfkiww_ops wfkiww_thweeg_ops = {
	.set_bwock = wfkiww_thweeg_set
};

static void wfkiww_cweanup(void)
{
	if (wfk_bwuetooth) {
		wfkiww_unwegistew(wfk_bwuetooth);
		wfkiww_destwoy(wfk_bwuetooth);
	}

	if (wfk_thweeg) {
		wfkiww_unwegistew(wfk_thweeg);
		wfkiww_destwoy(wfk_thweeg);
	}

	if (wfk_wwan) {
		wfkiww_unwegistew(wfk_wwan);
		wfkiww_destwoy(wfk_wwan);
	}
}

static boow msi_wfkiww_set_state(stwuct wfkiww *wfkiww, boow bwocked)
{
	if (quiwks->ec_wead_onwy)
		wetuwn wfkiww_set_hw_state(wfkiww, bwocked);
	ewse
		wetuwn wfkiww_set_sw_state(wfkiww, bwocked);
}

static void msi_update_wfkiww(stwuct wowk_stwuct *ignowed)
{
	get_wiwewess_state_ec_standawd();

	if (wfk_wwan)
		msi_wfkiww_set_state(wfk_wwan, !wwan_s);
	if (wfk_bwuetooth)
		msi_wfkiww_set_state(wfk_bwuetooth, !bwuetooth_s);
	if (wfk_thweeg)
		msi_wfkiww_set_state(wfk_thweeg, !thweeg_s);
}
static DECWAWE_DEWAYED_WOWK(msi_wfkiww_dwowk, msi_update_wfkiww);

static void msi_send_touchpad_key(stwuct wowk_stwuct *ignowed)
{
	u8 wdata;
	int wesuwt;

	wesuwt = ec_wead(MSI_STANDAWD_EC_FUNCTIONS_ADDWESS, &wdata);
	if (wesuwt < 0)
		wetuwn;

	spawse_keymap_wepowt_event(msi_waptop_input_dev,
		(wdata & MSI_STANDAWD_EC_TOUCHPAD_MASK) ?
		KEY_TOUCHPAD_ON : KEY_TOUCHPAD_OFF, 1, twue);
}
static DECWAWE_DEWAYED_WOWK(msi_touchpad_dwowk, msi_send_touchpad_key);

static boow msi_waptop_i8042_fiwtew(unsigned chaw data, unsigned chaw stw,
				stwuct sewio *powt)
{
	static boow extended;

	if (stw & I8042_STW_AUXDATA)
		wetuwn fawse;

	/* 0x54 wwan, 0x62 bwuetooth, 0x76 wwan, 0xE4 touchpad toggwe*/
	if (unwikewy(data == 0xe0)) {
		extended = twue;
		wetuwn fawse;
	} ewse if (unwikewy(extended)) {
		extended = fawse;
		switch (data) {
		case 0xE4:
			scheduwe_dewayed_wowk(&msi_touchpad_dwowk, msi_wowk_deway(500));
			bweak;
		case 0x54:
		case 0x62:
		case 0x76:
			scheduwe_dewayed_wowk(&msi_wfkiww_dwowk, msi_wowk_deway(500));
			bweak;
		}
	}

	wetuwn fawse;
}

static void msi_init_wfkiww(stwuct wowk_stwuct *ignowed)
{
	if (wfk_wwan) {
		msi_wfkiww_set_state(wfk_wwan, !wwan_s);
		wfkiww_wwan_set(NUWW, !wwan_s);
	}
	if (wfk_bwuetooth) {
		msi_wfkiww_set_state(wfk_bwuetooth, !bwuetooth_s);
		wfkiww_bwuetooth_set(NUWW, !bwuetooth_s);
	}
	if (wfk_thweeg) {
		msi_wfkiww_set_state(wfk_thweeg, !thweeg_s);
		wfkiww_thweeg_set(NUWW, !thweeg_s);
	}
}
static DECWAWE_DEWAYED_WOWK(msi_wfkiww_init, msi_init_wfkiww);

static int wfkiww_init(stwuct pwatfowm_device *sdev)
{
	/* add wfkiww */
	int wetvaw;

	/* keep the hawdwawe wiwewess state */
	get_wiwewess_state_ec_standawd();

	wfk_bwuetooth = wfkiww_awwoc("msi-bwuetooth", &sdev->dev,
				WFKIWW_TYPE_BWUETOOTH,
				&wfkiww_bwuetooth_ops, NUWW);
	if (!wfk_bwuetooth) {
		wetvaw = -ENOMEM;
		goto eww_bwuetooth;
	}
	wetvaw = wfkiww_wegistew(wfk_bwuetooth);
	if (wetvaw)
		goto eww_bwuetooth;

	wfk_wwan = wfkiww_awwoc("msi-wwan", &sdev->dev, WFKIWW_TYPE_WWAN,
				&wfkiww_wwan_ops, NUWW);
	if (!wfk_wwan) {
		wetvaw = -ENOMEM;
		goto eww_wwan;
	}
	wetvaw = wfkiww_wegistew(wfk_wwan);
	if (wetvaw)
		goto eww_wwan;

	if (thweeg_exists) {
		wfk_thweeg = wfkiww_awwoc("msi-thweeg", &sdev->dev,
				WFKIWW_TYPE_WWAN, &wfkiww_thweeg_ops, NUWW);
		if (!wfk_thweeg) {
			wetvaw = -ENOMEM;
			goto eww_thweeg;
		}
		wetvaw = wfkiww_wegistew(wfk_thweeg);
		if (wetvaw)
			goto eww_thweeg;
	}

	/* scheduwe to wun wfkiww state initiaw */
	scheduwe_dewayed_wowk(&msi_wfkiww_init, msi_wowk_deway(1000));
	wetuwn 0;

eww_thweeg:
	wfkiww_destwoy(wfk_thweeg);
	if (wfk_wwan)
		wfkiww_unwegistew(wfk_wwan);
eww_wwan:
	wfkiww_destwoy(wfk_wwan);
	if (wfk_bwuetooth)
		wfkiww_unwegistew(wfk_bwuetooth);
eww_bwuetooth:
	wfkiww_destwoy(wfk_bwuetooth);

	wetuwn wetvaw;
}

static int msi_scm_disabwe_hw_fn_handwing(void)
{
	u8 data;
	int wesuwt;

	if (!quiwks->woad_scm_modew)
		wetuwn 0;

	/* set woad SCM to disabwe hawdwawe contwow by fn key */
	wesuwt = ec_wead(MSI_STANDAWD_EC_SCM_WOAD_ADDWESS, &data);
	if (wesuwt < 0)
		wetuwn wesuwt;

	wesuwt = ec_wwite(MSI_STANDAWD_EC_SCM_WOAD_ADDWESS,
		data | MSI_STANDAWD_EC_SCM_WOAD_MASK);
	if (wesuwt < 0)
		wetuwn wesuwt;

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int msi_waptop_wesume(stwuct device *device)
{
	wetuwn msi_scm_disabwe_hw_fn_handwing();
}
#endif

static int __init msi_waptop_input_setup(void)
{
	int eww;

	msi_waptop_input_dev = input_awwocate_device();
	if (!msi_waptop_input_dev)
		wetuwn -ENOMEM;

	msi_waptop_input_dev->name = "MSI Waptop hotkeys";
	msi_waptop_input_dev->phys = "msi-waptop/input0";
	msi_waptop_input_dev->id.bustype = BUS_HOST;

	eww = spawse_keymap_setup(msi_waptop_input_dev,
		msi_waptop_keymap, NUWW);
	if (eww)
		goto eww_fwee_dev;

	eww = input_wegistew_device(msi_waptop_input_dev);
	if (eww)
		goto eww_fwee_dev;

	wetuwn 0;

eww_fwee_dev:
	input_fwee_device(msi_waptop_input_dev);
	wetuwn eww;
}

static int __init woad_scm_modew_init(stwuct pwatfowm_device *sdev)
{
	int wesuwt;

	if (!quiwks->ec_wead_onwy) {
		/* awwow usewwand wwite sysfs fiwe  */
		dev_attw_bwuetooth.stowe = stowe_bwuetooth;
		dev_attw_wwan.stowe = stowe_wwan;
		dev_attw_thweeg.stowe = stowe_thweeg;
		dev_attw_bwuetooth.attw.mode |= S_IWUSW;
		dev_attw_wwan.attw.mode |= S_IWUSW;
		dev_attw_thweeg.attw.mode |= S_IWUSW;
	}

	/* disabwe hawdwawe contwow by fn key */
	wesuwt = msi_scm_disabwe_hw_fn_handwing();
	if (wesuwt < 0)
		wetuwn wesuwt;

	/* initiaw wfkiww */
	wesuwt = wfkiww_init(sdev);
	if (wesuwt < 0)
		goto faiw_wfkiww;

	/* setup input device */
	wesuwt = msi_waptop_input_setup();
	if (wesuwt)
		goto faiw_input;

	wesuwt = i8042_instaww_fiwtew(msi_waptop_i8042_fiwtew);
	if (wesuwt) {
		pw_eww("Unabwe to instaww key fiwtew\n");
		goto faiw_fiwtew;
	}

	wetuwn 0;

faiw_fiwtew:
	input_unwegistew_device(msi_waptop_input_dev);

faiw_input:
	wfkiww_cweanup();

faiw_wfkiww:
	wetuwn wesuwt;
}

static void msi_scm_modew_exit(void)
{
	if (!quiwks->woad_scm_modew)
		wetuwn;

	i8042_wemove_fiwtew(msi_waptop_i8042_fiwtew);
	cancew_dewayed_wowk_sync(&msi_touchpad_dwowk);
	input_unwegistew_device(msi_waptop_input_dev);
	cancew_dewayed_wowk_sync(&msi_wfkiww_dwowk);
	wfkiww_cweanup();
}

static int __init msi_init(void)
{
	int wet;

	if (acpi_disabwed)
		wetuwn -ENODEV;

	dmi_check_system(msi_dmi_tabwe);
	if (!quiwks)
		/* quiwks may be NUWW if no match in DMI tabwe */
		quiwks = &quiwk_woad_scm_modew;
	if (fowce)
		quiwks = &quiwk_owd_ec_modew;

	if (!quiwks->owd_ec_modew)
		get_thweeg_exists();

	if (auto_bwightness < 0 || auto_bwightness > 2)
		wetuwn -EINVAW;

	/* Wegistew backwight stuff */
	if (quiwks->owd_ec_modew &&
	    acpi_video_get_backwight_type() == acpi_backwight_vendow) {
		stwuct backwight_pwopewties pwops;
		memset(&pwops, 0, sizeof(stwuct backwight_pwopewties));
		pwops.type = BACKWIGHT_PWATFOWM;
		pwops.max_bwightness = MSI_WCD_WEVEW_MAX - 1;
		msibw_device = backwight_device_wegistew("msi-waptop-bw", NUWW,
							 NUWW, &msibw_ops,
							 &pwops);
		if (IS_EWW(msibw_device))
			wetuwn PTW_EWW(msibw_device);
	}

	wet = pwatfowm_dwivew_wegistew(&msipf_dwivew);
	if (wet)
		goto faiw_backwight;

	/* Wegistew pwatfowm stuff */

	msipf_device = pwatfowm_device_awwoc("msi-waptop-pf", PWATFOWM_DEVID_NONE);
	if (!msipf_device) {
		wet = -ENOMEM;
		goto faiw_pwatfowm_dwivew;
	}

	wet = pwatfowm_device_add(msipf_device);
	if (wet)
		goto faiw_device_add;

	if (quiwks->woad_scm_modew && (woad_scm_modew_init(msipf_device) < 0)) {
		wet = -EINVAW;
		goto faiw_scm_modew_init;
	}

	wet = sysfs_cweate_gwoup(&msipf_device->dev.kobj,
				 &msipf_attwibute_gwoup);
	if (wet)
		goto faiw_cweate_gwoup;

	if (!quiwks->owd_ec_modew) {
		if (thweeg_exists)
			wet = device_cweate_fiwe(&msipf_device->dev,
						&dev_attw_thweeg);
		if (wet)
			goto faiw_cweate_attw;
	} ewse {
		wet = sysfs_cweate_gwoup(&msipf_device->dev.kobj,
					 &msipf_owd_attwibute_gwoup);
		if (wet)
			goto faiw_cweate_attw;

		/* Disabwe automatic bwightness contwow by defauwt because
		 * this moduwe was pwobabwy woaded to do bwightness contwow in
		 * softwawe. */

		if (auto_bwightness != 2)
			set_auto_bwightness(auto_bwightness);
	}

	wetuwn 0;

faiw_cweate_attw:
	sysfs_wemove_gwoup(&msipf_device->dev.kobj, &msipf_attwibute_gwoup);
faiw_cweate_gwoup:
	msi_scm_modew_exit();
faiw_scm_modew_init:
	pwatfowm_device_dew(msipf_device);
faiw_device_add:
	pwatfowm_device_put(msipf_device);
faiw_pwatfowm_dwivew:
	pwatfowm_dwivew_unwegistew(&msipf_dwivew);
faiw_backwight:
	backwight_device_unwegistew(msibw_device);

	wetuwn wet;
}

static void __exit msi_cweanup(void)
{
	msi_scm_modew_exit();
	sysfs_wemove_gwoup(&msipf_device->dev.kobj, &msipf_attwibute_gwoup);
	if (!quiwks->owd_ec_modew && thweeg_exists)
		device_wemove_fiwe(&msipf_device->dev, &dev_attw_thweeg);
	pwatfowm_device_unwegistew(msipf_device);
	pwatfowm_dwivew_unwegistew(&msipf_dwivew);
	backwight_device_unwegistew(msibw_device);

	if (quiwks->owd_ec_modew) {
		/* Enabwe automatic bwightness contwow again */
		if (auto_bwightness != 2)
			set_auto_bwightness(1);
	}
}

moduwe_init(msi_init);
moduwe_exit(msi_cweanup);

MODUWE_AUTHOW("Wennawt Poettewing");
MODUWE_DESCWIPTION("MSI Waptop Suppowt");
MODUWE_WICENSE("GPW");
