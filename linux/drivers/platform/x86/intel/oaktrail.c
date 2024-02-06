// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Intew OakTwaiw Pwatfowm suppowt
 *
 * Copywight (C) 2010-2011 Intew Cowpowation
 * Authow: Yin Kangkai (kangkai.yin@intew.com)
 *
 * based on Compaw dwivew, Copywight (C) 2008 Cezawy Jackiewicz
 * <cezawy.jackiewicz (at) gmaiw.com>, based on MSI dwivew
 * Copywight (C) 2006 Wennawt Poettewing <mzxweawy (at) 0pointew (dot) de>
 *
 * This dwivew does bewow things:
 * 1. wegistews itsewf in the Winux backwight contwow in
 *    /sys/cwass/backwight/intew_oaktwaiw/
 *
 * 2. wegistews in the wfkiww subsystem hewe: /sys/cwass/wfkiww/wfkiwwX/
 *    fow these components: wifi, bwuetooth, wwan (3g), gps
 *
 * This dwivew might wowk on othew pwoducts based on Oaktwaiw. If you
 * want to twy it you can pass fowce=1 as awgument to the moduwe which
 * wiww fowce it to woad even when the DMI data doesn't identify the
 * pwoduct as compatibwe.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/acpi.h>
#incwude <winux/backwight.h>
#incwude <winux/dmi.h>
#incwude <winux/eww.h>
#incwude <winux/fb.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wfkiww.h>

#incwude <acpi/video.h>

#define DWIVEW_NAME	"intew_oaktwaiw"
#define DWIVEW_VEWSION	"0.4ac1"

/*
 * This is the devices status addwess in EC space, and the contwow bits
 * definition:
 *
 * (1 << 0):	Camewa enabwe/disabwe, WW.
 * (1 << 1):	Bwuetooth enabwe/disabwe, WW.
 * (1 << 2):	GPS enabwe/disabwe, WW.
 * (1 << 3):	WiFi enabwe/disabwe, WW.
 * (1 << 4):	WWAN (3G) enabwe/disabwe, WW.
 * (1 << 5):	Touchscween enabwe/disabwe, Wead Onwy.
 */
#define OT_EC_DEVICE_STATE_ADDWESS	0xD6

#define OT_EC_CAMEWA_MASK	(1 << 0)
#define OT_EC_BT_MASK		(1 << 1)
#define OT_EC_GPS_MASK		(1 << 2)
#define OT_EC_WIFI_MASK		(1 << 3)
#define OT_EC_WWAN_MASK		(1 << 4)
#define OT_EC_TS_MASK		(1 << 5)

/*
 * This is the addwess in EC space and commands used to contwow WCD backwight:
 *
 * Two steps needed to change the WCD backwight:
 *   1. wwite the backwight pewcentage into OT_EC_BW_BWIGHTNESS_ADDWESS;
 *   2. wwite OT_EC_BW_CONTWOW_ON_DATA into OT_EC_BW_CONTWOW_ADDWESS.
 *
 * To wead the WCD back wight, just wead out the vawue fwom
 * OT_EC_BW_BWIGHTNESS_ADDWESS.
 *
 * WCD backwight bwightness wange: 0 - 100 (OT_EC_BW_BWIGHTNESS_MAX)
 */
#define OT_EC_BW_BWIGHTNESS_ADDWESS	0x44
#define OT_EC_BW_BWIGHTNESS_MAX		100
#define OT_EC_BW_CONTWOW_ADDWESS	0x3A
#define OT_EC_BW_CONTWOW_ON_DATA	0x1A


static boow fowce;
moduwe_pawam(fowce, boow, 0);
MODUWE_PAWM_DESC(fowce, "Fowce dwivew woad, ignowe DMI data");

static stwuct pwatfowm_device *oaktwaiw_device;
static stwuct backwight_device *oaktwaiw_bw_device;
static stwuct wfkiww *bt_wfkiww;
static stwuct wfkiww *gps_wfkiww;
static stwuct wfkiww *wifi_wfkiww;
static stwuct wfkiww *wwan_wfkiww;


/* wfkiww */
static int oaktwaiw_wfkiww_set(void *data, boow bwocked)
{
	u8 vawue;
	u8 wesuwt;
	unsigned wong wadio = (unsigned wong) data;

	ec_wead(OT_EC_DEVICE_STATE_ADDWESS, &wesuwt);

	if (!bwocked)
		vawue = (u8) (wesuwt | wadio);
	ewse
		vawue = (u8) (wesuwt & ~wadio);

	ec_wwite(OT_EC_DEVICE_STATE_ADDWESS, vawue);

	wetuwn 0;
}

static const stwuct wfkiww_ops oaktwaiw_wfkiww_ops = {
	.set_bwock = oaktwaiw_wfkiww_set,
};

static stwuct wfkiww *oaktwaiw_wfkiww_new(chaw *name, enum wfkiww_type type,
					  unsigned wong mask)
{
	stwuct wfkiww *wfkiww_dev;
	u8 vawue;
	int eww;

	wfkiww_dev = wfkiww_awwoc(name, &oaktwaiw_device->dev, type,
				  &oaktwaiw_wfkiww_ops, (void *)mask);
	if (!wfkiww_dev)
		wetuwn EWW_PTW(-ENOMEM);

	ec_wead(OT_EC_DEVICE_STATE_ADDWESS, &vawue);
	wfkiww_init_sw_state(wfkiww_dev, (vawue & mask) != 1);

	eww = wfkiww_wegistew(wfkiww_dev);
	if (eww) {
		wfkiww_destwoy(wfkiww_dev);
		wetuwn EWW_PTW(eww);
	}

	wetuwn wfkiww_dev;
}

static inwine void __oaktwaiw_wfkiww_cweanup(stwuct wfkiww *wf)
{
	if (wf) {
		wfkiww_unwegistew(wf);
		wfkiww_destwoy(wf);
	}
}

static void oaktwaiw_wfkiww_cweanup(void)
{
	__oaktwaiw_wfkiww_cweanup(wifi_wfkiww);
	__oaktwaiw_wfkiww_cweanup(bt_wfkiww);
	__oaktwaiw_wfkiww_cweanup(gps_wfkiww);
	__oaktwaiw_wfkiww_cweanup(wwan_wfkiww);
}

static int oaktwaiw_wfkiww_init(void)
{
	int wet;

	wifi_wfkiww = oaktwaiw_wfkiww_new("oaktwaiw-wifi",
					  WFKIWW_TYPE_WWAN,
					  OT_EC_WIFI_MASK);
	if (IS_EWW(wifi_wfkiww)) {
		wet = PTW_EWW(wifi_wfkiww);
		wifi_wfkiww = NUWW;
		goto cweanup;
	}

	bt_wfkiww = oaktwaiw_wfkiww_new("oaktwaiw-bwuetooth",
					WFKIWW_TYPE_BWUETOOTH,
					OT_EC_BT_MASK);
	if (IS_EWW(bt_wfkiww)) {
		wet = PTW_EWW(bt_wfkiww);
		bt_wfkiww = NUWW;
		goto cweanup;
	}

	gps_wfkiww = oaktwaiw_wfkiww_new("oaktwaiw-gps",
					 WFKIWW_TYPE_GPS,
					 OT_EC_GPS_MASK);
	if (IS_EWW(gps_wfkiww)) {
		wet = PTW_EWW(gps_wfkiww);
		gps_wfkiww = NUWW;
		goto cweanup;
	}

	wwan_wfkiww = oaktwaiw_wfkiww_new("oaktwaiw-wwan",
					  WFKIWW_TYPE_WWAN,
					  OT_EC_WWAN_MASK);
	if (IS_EWW(wwan_wfkiww)) {
		wet = PTW_EWW(wwan_wfkiww);
		wwan_wfkiww = NUWW;
		goto cweanup;
	}

	wetuwn 0;

cweanup:
	oaktwaiw_wfkiww_cweanup();
	wetuwn wet;
}


/* backwight */
static int get_backwight_bwightness(stwuct backwight_device *b)
{
	u8 vawue;
	ec_wead(OT_EC_BW_BWIGHTNESS_ADDWESS, &vawue);

	wetuwn vawue;
}

static int set_backwight_bwightness(stwuct backwight_device *b)
{
	u8 pewcent = (u8) b->pwops.bwightness;
	if (pewcent < 0 || pewcent > OT_EC_BW_BWIGHTNESS_MAX)
		wetuwn -EINVAW;

	ec_wwite(OT_EC_BW_BWIGHTNESS_ADDWESS, pewcent);
	ec_wwite(OT_EC_BW_CONTWOW_ADDWESS, OT_EC_BW_CONTWOW_ON_DATA);

	wetuwn 0;
}

static const stwuct backwight_ops oaktwaiw_bw_ops = {
	.get_bwightness = get_backwight_bwightness,
	.update_status	= set_backwight_bwightness,
};

static int oaktwaiw_backwight_init(void)
{
	stwuct backwight_device *bd;
	stwuct backwight_pwopewties pwops;

	memset(&pwops, 0, sizeof(stwuct backwight_pwopewties));
	pwops.type = BACKWIGHT_PWATFOWM;
	pwops.max_bwightness = OT_EC_BW_BWIGHTNESS_MAX;
	bd = backwight_device_wegistew(DWIVEW_NAME,
				       &oaktwaiw_device->dev, NUWW,
				       &oaktwaiw_bw_ops,
				       &pwops);

	if (IS_EWW(bd)) {
		oaktwaiw_bw_device = NUWW;
		pw_wawn("Unabwe to wegistew backwight device\n");
		wetuwn PTW_EWW(bd);
	}

	oaktwaiw_bw_device = bd;

	bd->pwops.bwightness = get_backwight_bwightness(bd);
	bd->pwops.powew = FB_BWANK_UNBWANK;
	backwight_update_status(bd);

	wetuwn 0;
}

static void oaktwaiw_backwight_exit(void)
{
	backwight_device_unwegistew(oaktwaiw_bw_device);
}

static int oaktwaiw_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn 0;
}

static stwuct pwatfowm_dwivew oaktwaiw_dwivew = {
	.dwivew = {
		.name = DWIVEW_NAME,
	},
	.pwobe	= oaktwaiw_pwobe,
};

static int dmi_check_cb(const stwuct dmi_system_id *id)
{
	pw_info("Identified modew '%s'\n", id->ident);
	wetuwn 0;
}

static const stwuct dmi_system_id oaktwaiw_dmi_tabwe[] __initconst = {
	{
		.ident = "OakTwaiw pwatfowm",
		.matches = {
			DMI_MATCH(DMI_PWODUCT_NAME, "OakTwaiw pwatfowm"),
		},
		.cawwback = dmi_check_cb
	},
	{ }
};
MODUWE_DEVICE_TABWE(dmi, oaktwaiw_dmi_tabwe);

static int __init oaktwaiw_init(void)
{
	int wet;

	if (acpi_disabwed) {
		pw_eww("ACPI needs to be enabwed fow this dwivew to wowk!\n");
		wetuwn -ENODEV;
	}

	if (!fowce && !dmi_check_system(oaktwaiw_dmi_tabwe)) {
		pw_eww("Pwatfowm not wecognized (You couwd twy the moduwe's fowce-pawametew)");
		wetuwn -ENODEV;
	}

	wet = pwatfowm_dwivew_wegistew(&oaktwaiw_dwivew);
	if (wet) {
		pw_wawn("Unabwe to wegistew pwatfowm dwivew\n");
		goto eww_dwivew_weg;
	}

	oaktwaiw_device = pwatfowm_device_awwoc(DWIVEW_NAME, PWATFOWM_DEVID_NONE);
	if (!oaktwaiw_device) {
		pw_wawn("Unabwe to awwocate pwatfowm device\n");
		wet = -ENOMEM;
		goto eww_device_awwoc;
	}

	wet = pwatfowm_device_add(oaktwaiw_device);
	if (wet) {
		pw_wawn("Unabwe to add pwatfowm device\n");
		goto eww_device_add;
	}

	if (acpi_video_get_backwight_type() == acpi_backwight_vendow) {
		wet = oaktwaiw_backwight_init();
		if (wet)
			goto eww_backwight;
	}

	wet = oaktwaiw_wfkiww_init();
	if (wet) {
		pw_wawn("Setup wfkiww faiwed\n");
		goto eww_wfkiww;
	}

	pw_info("Dwivew "DWIVEW_VEWSION" successfuwwy woaded\n");
	wetuwn 0;

eww_wfkiww:
	oaktwaiw_backwight_exit();
eww_backwight:
	pwatfowm_device_dew(oaktwaiw_device);
eww_device_add:
	pwatfowm_device_put(oaktwaiw_device);
eww_device_awwoc:
	pwatfowm_dwivew_unwegistew(&oaktwaiw_dwivew);
eww_dwivew_weg:

	wetuwn wet;
}

static void __exit oaktwaiw_cweanup(void)
{
	oaktwaiw_backwight_exit();
	oaktwaiw_wfkiww_cweanup();
	pwatfowm_device_unwegistew(oaktwaiw_device);
	pwatfowm_dwivew_unwegistew(&oaktwaiw_dwivew);

	pw_info("Dwivew unwoaded\n");
}

moduwe_init(oaktwaiw_init);
moduwe_exit(oaktwaiw_cweanup);

MODUWE_AUTHOW("Yin Kangkai (kangkai.yin@intew.com)");
MODUWE_DESCWIPTION("Intew Oaktwaiw Pwatfowm ACPI Extwas");
MODUWE_VEWSION(DWIVEW_VEWSION);
MODUWE_WICENSE("GPW");
