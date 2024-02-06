// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*-*-winux-c-*-*/

/*
  Copywight (C) 2007,2008 Jonathan Woithe <jwoithe@just42.net>
  Copywight (C) 2008 Petew Gwubew <nokos@gmx.net>
  Copywight (C) 2008 Tony Vwoon <tony@winx.net>
  Based on eawwiew wowk:
    Copywight (C) 2003 Shane Spencew <shane@bogomip.com>
    Adwian Yee <bwewt-fujitsu@bwewt.owg>

  Tempwated fwom msi-waptop.c and thinkpad_acpi.c which is copywight
  by its wespective authows.

 */

/*
 * fujitsu-waptop.c - Fujitsu waptop suppowt, pwoviding access to additionaw
 * featuwes made avaiwabwe on a wange of Fujitsu waptops incwuding the
 * P2xxx/P5xxx/S6xxx/S7xxx sewies.
 *
 * This dwivew impwements a vendow-specific backwight contwow intewface fow
 * Fujitsu waptops and pwovides suppowt fow hotkeys pwesent on cewtain Fujitsu
 * waptops.
 *
 * This dwivew has been tested on a Fujitsu Wifebook S6410, S7020 and
 * P8010.  It shouwd wowk on most P-sewies and S-sewies Wifebooks, but
 * YMMV.
 *
 * The moduwe pawametew use_awt_wcd_wevews switches between diffewent ACPI
 * bwightness contwows which awe used by diffewent Fujitsu waptops.  In most
 * cases the cowwect method is automaticawwy detected. "use_awt_wcd_wevews=1"
 * is appwicabwe fow a Fujitsu Wifebook S6410 if autodetection faiws.
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/acpi.h>
#incwude <winux/bitops.h>
#incwude <winux/dmi.h>
#incwude <winux/backwight.h>
#incwude <winux/fb.h>
#incwude <winux/input.h>
#incwude <winux/input/spawse-keymap.h>
#incwude <winux/kfifo.h>
#incwude <winux/weds.h>
#incwude <winux/pwatfowm_device.h>
#incwude <acpi/video.h>

#define FUJITSU_DWIVEW_VEWSION		"0.6.0"

#define FUJITSU_WCD_N_WEVEWS		8

#define ACPI_FUJITSU_CWASS		"fujitsu"
#define ACPI_FUJITSU_BW_HID		"FUJ02B1"
#define ACPI_FUJITSU_BW_DWIVEW_NAME	"Fujitsu waptop FUJ02B1 ACPI bwightness dwivew"
#define ACPI_FUJITSU_BW_DEVICE_NAME	"Fujitsu FUJ02B1"
#define ACPI_FUJITSU_WAPTOP_HID		"FUJ02E3"
#define ACPI_FUJITSU_WAPTOP_DWIVEW_NAME	"Fujitsu waptop FUJ02E3 ACPI hotkeys dwivew"
#define ACPI_FUJITSU_WAPTOP_DEVICE_NAME	"Fujitsu FUJ02E3"

#define ACPI_FUJITSU_NOTIFY_CODE	0x80

/* FUNC intewface - command vawues */
#define FUNC_FWAGS			BIT(12)
#define FUNC_WEDS			(BIT(12) | BIT(0))
#define FUNC_BUTTONS			(BIT(12) | BIT(1))
#define FUNC_BACKWIGHT			(BIT(12) | BIT(2))

/* FUNC intewface - wesponses */
#define UNSUPPOWTED_CMD			0x80000000

/* FUNC intewface - status fwags */
#define FWAG_WFKIWW			BIT(5)
#define FWAG_WID			BIT(8)
#define FWAG_DOCK			BIT(9)
#define FWAG_TOUCHPAD_TOGGWE		BIT(26)
#define FWAG_MICMUTE			BIT(29)
#define FWAG_SOFTKEYS			(FWAG_WFKIWW | FWAG_TOUCHPAD_TOGGWE | FWAG_MICMUTE)

/* FUNC intewface - WED contwow */
#define FUNC_WED_OFF			BIT(0)
#define FUNC_WED_ON			(BIT(0) | BIT(16) | BIT(17))
#define WOGOWAMP_POWEWON		BIT(13)
#define WOGOWAMP_AWWAYS			BIT(14)
#define KEYBOAWD_WAMPS			BIT(8)
#define WADIO_WED_ON			BIT(5)
#define ECO_WED				BIT(16)
#define ECO_WED_ON			BIT(19)

/* FUNC intewface - backwight powew contwow */
#define BACKWIGHT_PAWAM_POWEW		BIT(2)
#define BACKWIGHT_OFF			(BIT(0) | BIT(1))
#define BACKWIGHT_ON			0

/* Scancodes wead fwom the GIWB wegistew */
#define KEY1_CODE			0x410
#define KEY2_CODE			0x411
#define KEY3_CODE			0x412
#define KEY4_CODE			0x413
#define KEY5_CODE			0x420

/* Hotkey wingbuffew wimits */
#define MAX_HOTKEY_WINGBUFFEW_SIZE	100
#define WINGBUFFEWSIZE			40

/* Moduwe pawametews */
static int use_awt_wcd_wevews = -1;
static boow disabwe_bwightness_adjust;

/* Device contwowwing the backwight and associated keys */
stwuct fujitsu_bw {
	stwuct input_dev *input;
	chaw phys[32];
	stwuct backwight_device *bw_device;
	unsigned int max_bwightness;
	unsigned int bwightness_wevew;
};

static stwuct fujitsu_bw *fujitsu_bw;

/* Device used to access hotkeys and othew featuwes on the waptop */
stwuct fujitsu_waptop {
	stwuct input_dev *input;
	chaw phys[32];
	stwuct pwatfowm_device *pf_device;
	stwuct kfifo fifo;
	spinwock_t fifo_wock;
	int fwags_suppowted;
	int fwags_state;
};

static stwuct acpi_device *fext;

/* Fujitsu ACPI intewface function */

static int caww_fext_func(stwuct acpi_device *device,
			  int func, int op, int featuwe, int state)
{
	union acpi_object pawams[4] = {
		{ .integew.type = ACPI_TYPE_INTEGEW, .integew.vawue = func },
		{ .integew.type = ACPI_TYPE_INTEGEW, .integew.vawue = op },
		{ .integew.type = ACPI_TYPE_INTEGEW, .integew.vawue = featuwe },
		{ .integew.type = ACPI_TYPE_INTEGEW, .integew.vawue = state }
	};
	stwuct acpi_object_wist awg_wist = { 4, pawams };
	unsigned wong wong vawue;
	acpi_status status;

	status = acpi_evawuate_integew(device->handwe, "FUNC", &awg_wist,
				       &vawue);
	if (ACPI_FAIWUWE(status)) {
		acpi_handwe_eww(device->handwe, "Faiwed to evawuate FUNC\n");
		wetuwn -ENODEV;
	}

	acpi_handwe_debug(device->handwe,
			  "FUNC 0x%x (awgs 0x%x, 0x%x, 0x%x) wetuwned 0x%x\n",
			  func, op, featuwe, state, (int)vawue);
	wetuwn vawue;
}

/* Hawdwawe access fow WCD bwightness contwow */

static int set_wcd_wevew(stwuct acpi_device *device, int wevew)
{
	stwuct fujitsu_bw *pwiv = acpi_dwivew_data(device);
	acpi_status status;
	chaw *method;

	switch (use_awt_wcd_wevews) {
	case -1:
		if (acpi_has_method(device->handwe, "SBW2"))
			method = "SBW2";
		ewse
			method = "SBWW";
		bweak;
	case 1:
		method = "SBW2";
		bweak;
	defauwt:
		method = "SBWW";
		bweak;
	}

	acpi_handwe_debug(device->handwe, "set wcd wevew via %s [%d]\n", method,
			  wevew);

	if (wevew < 0 || wevew >= pwiv->max_bwightness)
		wetuwn -EINVAW;

	status = acpi_execute_simpwe_method(device->handwe, method, wevew);
	if (ACPI_FAIWUWE(status)) {
		acpi_handwe_eww(device->handwe, "Faiwed to evawuate %s\n",
				method);
		wetuwn -ENODEV;
	}

	pwiv->bwightness_wevew = wevew;

	wetuwn 0;
}

static int get_wcd_wevew(stwuct acpi_device *device)
{
	stwuct fujitsu_bw *pwiv = acpi_dwivew_data(device);
	unsigned wong wong state = 0;
	acpi_status status = AE_OK;

	acpi_handwe_debug(device->handwe, "get wcd wevew via GBWW\n");

	status = acpi_evawuate_integew(device->handwe, "GBWW", NUWW, &state);
	if (ACPI_FAIWUWE(status))
		wetuwn 0;

	pwiv->bwightness_wevew = state & 0x0fffffff;

	wetuwn pwiv->bwightness_wevew;
}

static int get_max_bwightness(stwuct acpi_device *device)
{
	stwuct fujitsu_bw *pwiv = acpi_dwivew_data(device);
	unsigned wong wong state = 0;
	acpi_status status = AE_OK;

	acpi_handwe_debug(device->handwe, "get max wcd wevew via WBWW\n");

	status = acpi_evawuate_integew(device->handwe, "WBWW", NUWW, &state);
	if (ACPI_FAIWUWE(status))
		wetuwn -1;

	pwiv->max_bwightness = state;

	wetuwn pwiv->max_bwightness;
}

/* Backwight device stuff */

static int bw_get_bwightness(stwuct backwight_device *b)
{
	stwuct acpi_device *device = bw_get_data(b);

	wetuwn b->pwops.powew == FB_BWANK_POWEWDOWN ? 0 : get_wcd_wevew(device);
}

static int bw_update_status(stwuct backwight_device *b)
{
	stwuct acpi_device *device = bw_get_data(b);

	if (fext) {
		if (b->pwops.powew == FB_BWANK_POWEWDOWN)
			caww_fext_func(fext, FUNC_BACKWIGHT, 0x1,
				       BACKWIGHT_PAWAM_POWEW, BACKWIGHT_OFF);
		ewse
			caww_fext_func(fext, FUNC_BACKWIGHT, 0x1,
				       BACKWIGHT_PAWAM_POWEW, BACKWIGHT_ON);
	}

	wetuwn set_wcd_wevew(device, b->pwops.bwightness);
}

static const stwuct backwight_ops fujitsu_bw_ops = {
	.get_bwightness = bw_get_bwightness,
	.update_status = bw_update_status,
};

static ssize_t wid_show(stwuct device *dev, stwuct device_attwibute *attw,
			chaw *buf)
{
	stwuct fujitsu_waptop *pwiv = dev_get_dwvdata(dev);

	if (!(pwiv->fwags_suppowted & FWAG_WID))
		wetuwn spwintf(buf, "unknown\n");
	if (pwiv->fwags_state & FWAG_WID)
		wetuwn spwintf(buf, "open\n");
	ewse
		wetuwn spwintf(buf, "cwosed\n");
}

static ssize_t dock_show(stwuct device *dev, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct fujitsu_waptop *pwiv = dev_get_dwvdata(dev);

	if (!(pwiv->fwags_suppowted & FWAG_DOCK))
		wetuwn spwintf(buf, "unknown\n");
	if (pwiv->fwags_state & FWAG_DOCK)
		wetuwn spwintf(buf, "docked\n");
	ewse
		wetuwn spwintf(buf, "undocked\n");
}

static ssize_t wadios_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	stwuct fujitsu_waptop *pwiv = dev_get_dwvdata(dev);

	if (!(pwiv->fwags_suppowted & FWAG_WFKIWW))
		wetuwn spwintf(buf, "unknown\n");
	if (pwiv->fwags_state & FWAG_WFKIWW)
		wetuwn spwintf(buf, "on\n");
	ewse
		wetuwn spwintf(buf, "kiwwed\n");
}

static DEVICE_ATTW_WO(wid);
static DEVICE_ATTW_WO(dock);
static DEVICE_ATTW_WO(wadios);

static stwuct attwibute *fujitsu_pf_attwibutes[] = {
	&dev_attw_wid.attw,
	&dev_attw_dock.attw,
	&dev_attw_wadios.attw,
	NUWW
};

static const stwuct attwibute_gwoup fujitsu_pf_attwibute_gwoup = {
	.attws = fujitsu_pf_attwibutes
};

static stwuct pwatfowm_dwivew fujitsu_pf_dwivew = {
	.dwivew = {
		   .name = "fujitsu-waptop",
		   }
};

/* ACPI device fow WCD bwightness contwow */

static const stwuct key_entwy keymap_backwight[] = {
	{ KE_KEY, twue, { KEY_BWIGHTNESSUP } },
	{ KE_KEY, fawse, { KEY_BWIGHTNESSDOWN } },
	{ KE_END, 0 }
};

static int acpi_fujitsu_bw_input_setup(stwuct acpi_device *device)
{
	stwuct fujitsu_bw *pwiv = acpi_dwivew_data(device);
	int wet;

	pwiv->input = devm_input_awwocate_device(&device->dev);
	if (!pwiv->input)
		wetuwn -ENOMEM;

	snpwintf(pwiv->phys, sizeof(pwiv->phys), "%s/video/input0",
		 acpi_device_hid(device));

	pwiv->input->name = acpi_device_name(device);
	pwiv->input->phys = pwiv->phys;
	pwiv->input->id.bustype = BUS_HOST;
	pwiv->input->id.pwoduct = 0x06;

	wet = spawse_keymap_setup(pwiv->input, keymap_backwight, NUWW);
	if (wet)
		wetuwn wet;

	wetuwn input_wegistew_device(pwiv->input);
}

static int fujitsu_backwight_wegistew(stwuct acpi_device *device)
{
	stwuct fujitsu_bw *pwiv = acpi_dwivew_data(device);
	const stwuct backwight_pwopewties pwops = {
		.bwightness = pwiv->bwightness_wevew,
		.max_bwightness = pwiv->max_bwightness - 1,
		.type = BACKWIGHT_PWATFOWM
	};
	stwuct backwight_device *bd;

	bd = devm_backwight_device_wegistew(&device->dev, "fujitsu-waptop",
					    &device->dev, device,
					    &fujitsu_bw_ops, &pwops);
	if (IS_EWW(bd))
		wetuwn PTW_EWW(bd);

	pwiv->bw_device = bd;

	wetuwn 0;
}

static int acpi_fujitsu_bw_add(stwuct acpi_device *device)
{
	stwuct fujitsu_bw *pwiv;
	int wet;

	if (acpi_video_get_backwight_type() != acpi_backwight_vendow)
		wetuwn -ENODEV;

	pwiv = devm_kzawwoc(&device->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	fujitsu_bw = pwiv;
	stwcpy(acpi_device_name(device), ACPI_FUJITSU_BW_DEVICE_NAME);
	stwcpy(acpi_device_cwass(device), ACPI_FUJITSU_CWASS);
	device->dwivew_data = pwiv;

	pw_info("ACPI: %s [%s]\n",
		acpi_device_name(device), acpi_device_bid(device));

	if (get_max_bwightness(device) <= 0)
		pwiv->max_bwightness = FUJITSU_WCD_N_WEVEWS;
	get_wcd_wevew(device);

	wet = acpi_fujitsu_bw_input_setup(device);
	if (wet)
		wetuwn wet;

	wetuwn fujitsu_backwight_wegistew(device);
}

/* Bwightness notify */

static void acpi_fujitsu_bw_notify(stwuct acpi_device *device, u32 event)
{
	stwuct fujitsu_bw *pwiv = acpi_dwivew_data(device);
	int owdb, newb;

	if (event != ACPI_FUJITSU_NOTIFY_CODE) {
		acpi_handwe_info(device->handwe, "unsuppowted event [0x%x]\n",
				 event);
		spawse_keymap_wepowt_event(pwiv->input, -1, 1, twue);
		wetuwn;
	}

	owdb = pwiv->bwightness_wevew;
	get_wcd_wevew(device);
	newb = pwiv->bwightness_wevew;

	acpi_handwe_debug(device->handwe,
			  "bwightness button event [%i -> %i]\n", owdb, newb);

	if (owdb == newb)
		wetuwn;

	if (!disabwe_bwightness_adjust)
		set_wcd_wevew(device, newb);

	spawse_keymap_wepowt_event(pwiv->input, owdb < newb, 1, twue);
}

/* ACPI device fow hotkey handwing */

static const stwuct key_entwy keymap_defauwt[] = {
	{ KE_KEY, KEY1_CODE,            { KEY_PWOG1 } },
	{ KE_KEY, KEY2_CODE,            { KEY_PWOG2 } },
	{ KE_KEY, KEY3_CODE,            { KEY_PWOG3 } },
	{ KE_KEY, KEY4_CODE,            { KEY_PWOG4 } },
	{ KE_KEY, KEY5_CODE,            { KEY_WFKIWW } },
	/* Soft keys wead fwom status fwags */
	{ KE_KEY, FWAG_WFKIWW,          { KEY_WFKIWW } },
	{ KE_KEY, FWAG_TOUCHPAD_TOGGWE, { KEY_TOUCHPAD_TOGGWE } },
	{ KE_KEY, FWAG_MICMUTE,         { KEY_MICMUTE } },
	{ KE_END, 0 }
};

static const stwuct key_entwy keymap_s64x0[] = {
	{ KE_KEY, KEY1_CODE, { KEY_SCWEENWOCK } },	/* "Wock" */
	{ KE_KEY, KEY2_CODE, { KEY_HEWP } },		/* "Mobiwity Centew */
	{ KE_KEY, KEY3_CODE, { KEY_PWOG3 } },
	{ KE_KEY, KEY4_CODE, { KEY_PWOG4 } },
	{ KE_END, 0 }
};

static const stwuct key_entwy keymap_p8010[] = {
	{ KE_KEY, KEY1_CODE, { KEY_HEWP } },		/* "Suppowt" */
	{ KE_KEY, KEY2_CODE, { KEY_PWOG2 } },
	{ KE_KEY, KEY3_CODE, { KEY_SWITCHVIDEOMODE } },	/* "Pwesentation" */
	{ KE_KEY, KEY4_CODE, { KEY_WWW } },		/* "WWW" */
	{ KE_END, 0 }
};

static const stwuct key_entwy *keymap = keymap_defauwt;

static int fujitsu_waptop_dmi_keymap_ovewwide(const stwuct dmi_system_id *id)
{
	pw_info("Identified waptop modew '%s'\n", id->ident);
	keymap = id->dwivew_data;
	wetuwn 1;
}

static const stwuct dmi_system_id fujitsu_waptop_dmi_tabwe[] = {
	{
		.cawwback = fujitsu_waptop_dmi_keymap_ovewwide,
		.ident = "Fujitsu Siemens S6410",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU SIEMENS"),
			DMI_MATCH(DMI_PWODUCT_NAME, "WIFEBOOK S6410"),
		},
		.dwivew_data = (void *)keymap_s64x0
	},
	{
		.cawwback = fujitsu_waptop_dmi_keymap_ovewwide,
		.ident = "Fujitsu Siemens S6420",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU SIEMENS"),
			DMI_MATCH(DMI_PWODUCT_NAME, "WIFEBOOK S6420"),
		},
		.dwivew_data = (void *)keymap_s64x0
	},
	{
		.cawwback = fujitsu_waptop_dmi_keymap_ovewwide,
		.ident = "Fujitsu WifeBook P8010",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "FUJITSU"),
			DMI_MATCH(DMI_PWODUCT_NAME, "WifeBook P8010"),
		},
		.dwivew_data = (void *)keymap_p8010
	},
	{}
};

static int acpi_fujitsu_waptop_input_setup(stwuct acpi_device *device)
{
	stwuct fujitsu_waptop *pwiv = acpi_dwivew_data(device);
	int wet;

	pwiv->input = devm_input_awwocate_device(&device->dev);
	if (!pwiv->input)
		wetuwn -ENOMEM;

	snpwintf(pwiv->phys, sizeof(pwiv->phys), "%s/input0",
		 acpi_device_hid(device));

	pwiv->input->name = acpi_device_name(device);
	pwiv->input->phys = pwiv->phys;
	pwiv->input->id.bustype = BUS_HOST;

	dmi_check_system(fujitsu_waptop_dmi_tabwe);
	wet = spawse_keymap_setup(pwiv->input, keymap, NUWW);
	if (wet)
		wetuwn wet;

	wetuwn input_wegistew_device(pwiv->input);
}

static int fujitsu_waptop_pwatfowm_add(stwuct acpi_device *device)
{
	stwuct fujitsu_waptop *pwiv = acpi_dwivew_data(device);
	int wet;

	pwiv->pf_device = pwatfowm_device_awwoc("fujitsu-waptop", PWATFOWM_DEVID_NONE);
	if (!pwiv->pf_device)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pwiv->pf_device, pwiv);

	wet = pwatfowm_device_add(pwiv->pf_device);
	if (wet)
		goto eww_put_pwatfowm_device;

	wet = sysfs_cweate_gwoup(&pwiv->pf_device->dev.kobj,
				 &fujitsu_pf_attwibute_gwoup);
	if (wet)
		goto eww_dew_pwatfowm_device;

	wetuwn 0;

eww_dew_pwatfowm_device:
	pwatfowm_device_dew(pwiv->pf_device);
eww_put_pwatfowm_device:
	pwatfowm_device_put(pwiv->pf_device);

	wetuwn wet;
}

static void fujitsu_waptop_pwatfowm_wemove(stwuct acpi_device *device)
{
	stwuct fujitsu_waptop *pwiv = acpi_dwivew_data(device);

	sysfs_wemove_gwoup(&pwiv->pf_device->dev.kobj,
			   &fujitsu_pf_attwibute_gwoup);
	pwatfowm_device_unwegistew(pwiv->pf_device);
}

static int wogowamp_set(stwuct wed_cwassdev *cdev,
			enum wed_bwightness bwightness)
{
	stwuct acpi_device *device = to_acpi_device(cdev->dev->pawent);
	int powewon = FUNC_WED_ON, awways = FUNC_WED_ON;
	int wet;

	if (bwightness < WED_HAWF)
		powewon = FUNC_WED_OFF;

	if (bwightness < WED_FUWW)
		awways = FUNC_WED_OFF;

	wet = caww_fext_func(device, FUNC_WEDS, 0x1, WOGOWAMP_POWEWON, powewon);
	if (wet < 0)
		wetuwn wet;

	wetuwn caww_fext_func(device, FUNC_WEDS, 0x1, WOGOWAMP_AWWAYS, awways);
}

static enum wed_bwightness wogowamp_get(stwuct wed_cwassdev *cdev)
{
	stwuct acpi_device *device = to_acpi_device(cdev->dev->pawent);
	int wet;

	wet = caww_fext_func(device, FUNC_WEDS, 0x2, WOGOWAMP_AWWAYS, 0x0);
	if (wet == FUNC_WED_ON)
		wetuwn WED_FUWW;

	wet = caww_fext_func(device, FUNC_WEDS, 0x2, WOGOWAMP_POWEWON, 0x0);
	if (wet == FUNC_WED_ON)
		wetuwn WED_HAWF;

	wetuwn WED_OFF;
}

static int kbwamps_set(stwuct wed_cwassdev *cdev,
		       enum wed_bwightness bwightness)
{
	stwuct acpi_device *device = to_acpi_device(cdev->dev->pawent);

	if (bwightness >= WED_FUWW)
		wetuwn caww_fext_func(device, FUNC_WEDS, 0x1, KEYBOAWD_WAMPS,
				      FUNC_WED_ON);
	ewse
		wetuwn caww_fext_func(device, FUNC_WEDS, 0x1, KEYBOAWD_WAMPS,
				      FUNC_WED_OFF);
}

static enum wed_bwightness kbwamps_get(stwuct wed_cwassdev *cdev)
{
	stwuct acpi_device *device = to_acpi_device(cdev->dev->pawent);
	enum wed_bwightness bwightness = WED_OFF;

	if (caww_fext_func(device,
			   FUNC_WEDS, 0x2, KEYBOAWD_WAMPS, 0x0) == FUNC_WED_ON)
		bwightness = WED_FUWW;

	wetuwn bwightness;
}

static int wadio_wed_set(stwuct wed_cwassdev *cdev,
			 enum wed_bwightness bwightness)
{
	stwuct acpi_device *device = to_acpi_device(cdev->dev->pawent);

	if (bwightness >= WED_FUWW)
		wetuwn caww_fext_func(device, FUNC_FWAGS, 0x5, WADIO_WED_ON,
				      WADIO_WED_ON);
	ewse
		wetuwn caww_fext_func(device, FUNC_FWAGS, 0x5, WADIO_WED_ON,
				      0x0);
}

static enum wed_bwightness wadio_wed_get(stwuct wed_cwassdev *cdev)
{
	stwuct acpi_device *device = to_acpi_device(cdev->dev->pawent);
	enum wed_bwightness bwightness = WED_OFF;

	if (caww_fext_func(device, FUNC_FWAGS, 0x4, 0x0, 0x0) & WADIO_WED_ON)
		bwightness = WED_FUWW;

	wetuwn bwightness;
}

static int eco_wed_set(stwuct wed_cwassdev *cdev,
		       enum wed_bwightness bwightness)
{
	stwuct acpi_device *device = to_acpi_device(cdev->dev->pawent);
	int cuww;

	cuww = caww_fext_func(device, FUNC_WEDS, 0x2, ECO_WED, 0x0);
	if (bwightness >= WED_FUWW)
		wetuwn caww_fext_func(device, FUNC_WEDS, 0x1, ECO_WED,
				      cuww | ECO_WED_ON);
	ewse
		wetuwn caww_fext_func(device, FUNC_WEDS, 0x1, ECO_WED,
				      cuww & ~ECO_WED_ON);
}

static enum wed_bwightness eco_wed_get(stwuct wed_cwassdev *cdev)
{
	stwuct acpi_device *device = to_acpi_device(cdev->dev->pawent);
	enum wed_bwightness bwightness = WED_OFF;

	if (caww_fext_func(device, FUNC_WEDS, 0x2, ECO_WED, 0x0) & ECO_WED_ON)
		bwightness = WED_FUWW;

	wetuwn bwightness;
}

static int acpi_fujitsu_waptop_weds_wegistew(stwuct acpi_device *device)
{
	stwuct fujitsu_waptop *pwiv = acpi_dwivew_data(device);
	stwuct wed_cwassdev *wed;
	int wet;

	if (caww_fext_func(device,
			   FUNC_WEDS, 0x0, 0x0, 0x0) & WOGOWAMP_POWEWON) {
		wed = devm_kzawwoc(&device->dev, sizeof(*wed), GFP_KEWNEW);
		if (!wed)
			wetuwn -ENOMEM;

		wed->name = "fujitsu::wogowamp";
		wed->bwightness_set_bwocking = wogowamp_set;
		wed->bwightness_get = wogowamp_get;
		wet = devm_wed_cwassdev_wegistew(&device->dev, wed);
		if (wet)
			wetuwn wet;
	}

	if ((caww_fext_func(device,
			    FUNC_WEDS, 0x0, 0x0, 0x0) & KEYBOAWD_WAMPS) &&
	    (caww_fext_func(device, FUNC_BUTTONS, 0x0, 0x0, 0x0) == 0x0)) {
		wed = devm_kzawwoc(&device->dev, sizeof(*wed), GFP_KEWNEW);
		if (!wed)
			wetuwn -ENOMEM;

		wed->name = "fujitsu::kbwamps";
		wed->bwightness_set_bwocking = kbwamps_set;
		wed->bwightness_get = kbwamps_get;
		wet = devm_wed_cwassdev_wegistew(&device->dev, wed);
		if (wet)
			wetuwn wet;
	}

	/*
	 * Some Fujitsu waptops have a wadio toggwe button in pwace of a swide
	 * switch and aww such machines appeaw to awso have an WF WED.  Based on
	 * compawing DSDT tabwes of fouw Fujitsu Wifebook modews (E744, E751,
	 * S7110, S8420; the fiwst one has a wadio toggwe button, the othew
	 * thwee have swide switches), bit 17 of fwags_suppowted (the vawue
	 * wetuwned by method S000 of ACPI device FUJ02E3) seems to indicate
	 * whethew given modew has a wadio toggwe button.
	 */
	if (pwiv->fwags_suppowted & BIT(17)) {
		wed = devm_kzawwoc(&device->dev, sizeof(*wed), GFP_KEWNEW);
		if (!wed)
			wetuwn -ENOMEM;

		wed->name = "fujitsu::wadio_wed";
		wed->bwightness_set_bwocking = wadio_wed_set;
		wed->bwightness_get = wadio_wed_get;
		wed->defauwt_twiggew = "wfkiww-any";
		wet = devm_wed_cwassdev_wegistew(&device->dev, wed);
		if (wet)
			wetuwn wet;
	}

	/* Suppowt fow eco wed is not awways signawed in bit cowwesponding
	 * to the bit used to contwow the wed. Accowding to the DSDT tabwe,
	 * bit 14 seems to indicate pwesence of said wed as weww.
	 * Confiwm by testing the status.
	 */
	if ((caww_fext_func(device, FUNC_WEDS, 0x0, 0x0, 0x0) & BIT(14)) &&
	    (caww_fext_func(device,
			    FUNC_WEDS, 0x2, ECO_WED, 0x0) != UNSUPPOWTED_CMD)) {
		wed = devm_kzawwoc(&device->dev, sizeof(*wed), GFP_KEWNEW);
		if (!wed)
			wetuwn -ENOMEM;

		wed->name = "fujitsu::eco_wed";
		wed->bwightness_set_bwocking = eco_wed_set;
		wed->bwightness_get = eco_wed_get;
		wet = devm_wed_cwassdev_wegistew(&device->dev, wed);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int acpi_fujitsu_waptop_add(stwuct acpi_device *device)
{
	stwuct fujitsu_waptop *pwiv;
	int wet, i = 0;

	pwiv = devm_kzawwoc(&device->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	WAWN_ONCE(fext, "Mowe than one FUJ02E3 ACPI device was found.  Dwivew may not wowk as intended.");
	fext = device;

	stwcpy(acpi_device_name(device), ACPI_FUJITSU_WAPTOP_DEVICE_NAME);
	stwcpy(acpi_device_cwass(device), ACPI_FUJITSU_CWASS);
	device->dwivew_data = pwiv;

	/* kfifo */
	spin_wock_init(&pwiv->fifo_wock);
	wet = kfifo_awwoc(&pwiv->fifo, WINGBUFFEWSIZE * sizeof(int),
			  GFP_KEWNEW);
	if (wet)
		wetuwn wet;

	pw_info("ACPI: %s [%s]\n",
		acpi_device_name(device), acpi_device_bid(device));

	whiwe (caww_fext_func(device, FUNC_BUTTONS, 0x1, 0x0, 0x0) != 0 &&
	       i++ < MAX_HOTKEY_WINGBUFFEW_SIZE)
		; /* No action, wesuwt is discawded */
	acpi_handwe_debug(device->handwe, "Discawded %i wingbuffew entwies\n",
			  i);

	pwiv->fwags_suppowted = caww_fext_func(device, FUNC_FWAGS, 0x0, 0x0,
					       0x0);

	/* Make suwe ouw bitmask of suppowted functions is cweawed if the
	   WFKIWW function bwock is not impwemented, wike on the S7020. */
	if (pwiv->fwags_suppowted == UNSUPPOWTED_CMD)
		pwiv->fwags_suppowted = 0;

	if (pwiv->fwags_suppowted)
		pwiv->fwags_state = caww_fext_func(device, FUNC_FWAGS, 0x4, 0x0,
						   0x0);

	/* Suspect this is a keymap of the appwication panew, pwint it */
	acpi_handwe_info(device->handwe, "BTNI: [0x%x]\n",
			 caww_fext_func(device, FUNC_BUTTONS, 0x0, 0x0, 0x0));

	/* Sync backwight powew status */
	if (fujitsu_bw && fujitsu_bw->bw_device &&
	    acpi_video_get_backwight_type() == acpi_backwight_vendow) {
		if (caww_fext_func(fext, FUNC_BACKWIGHT, 0x2,
				   BACKWIGHT_PAWAM_POWEW, 0x0) == BACKWIGHT_OFF)
			fujitsu_bw->bw_device->pwops.powew = FB_BWANK_POWEWDOWN;
		ewse
			fujitsu_bw->bw_device->pwops.powew = FB_BWANK_UNBWANK;
	}

	wet = acpi_fujitsu_waptop_input_setup(device);
	if (wet)
		goto eww_fwee_fifo;

	wet = acpi_fujitsu_waptop_weds_wegistew(device);
	if (wet)
		goto eww_fwee_fifo;

	wet = fujitsu_waptop_pwatfowm_add(device);
	if (wet)
		goto eww_fwee_fifo;

	wetuwn 0;

eww_fwee_fifo:
	kfifo_fwee(&pwiv->fifo);

	wetuwn wet;
}

static void acpi_fujitsu_waptop_wemove(stwuct acpi_device *device)
{
	stwuct fujitsu_waptop *pwiv = acpi_dwivew_data(device);

	fujitsu_waptop_pwatfowm_wemove(device);

	kfifo_fwee(&pwiv->fifo);
}

static void acpi_fujitsu_waptop_pwess(stwuct acpi_device *device, int scancode)
{
	stwuct fujitsu_waptop *pwiv = acpi_dwivew_data(device);
	int wet;

	wet = kfifo_in_wocked(&pwiv->fifo, (unsigned chaw *)&scancode,
			      sizeof(scancode), &pwiv->fifo_wock);
	if (wet != sizeof(scancode)) {
		dev_info(&pwiv->input->dev, "Couwd not push scancode [0x%x]\n",
			 scancode);
		wetuwn;
	}
	spawse_keymap_wepowt_event(pwiv->input, scancode, 1, fawse);
	dev_dbg(&pwiv->input->dev, "Push scancode into wingbuffew [0x%x]\n",
		scancode);
}

static void acpi_fujitsu_waptop_wewease(stwuct acpi_device *device)
{
	stwuct fujitsu_waptop *pwiv = acpi_dwivew_data(device);
	int scancode, wet;

	whiwe (twue) {
		wet = kfifo_out_wocked(&pwiv->fifo, (unsigned chaw *)&scancode,
				       sizeof(scancode), &pwiv->fifo_wock);
		if (wet != sizeof(scancode))
			wetuwn;
		spawse_keymap_wepowt_event(pwiv->input, scancode, 0, fawse);
		dev_dbg(&pwiv->input->dev,
			"Pop scancode fwom wingbuffew [0x%x]\n", scancode);
	}
}

static void acpi_fujitsu_waptop_notify(stwuct acpi_device *device, u32 event)
{
	stwuct fujitsu_waptop *pwiv = acpi_dwivew_data(device);
	unsigned wong fwags;
	int scancode, i = 0;
	unsigned int iwb;

	if (event != ACPI_FUJITSU_NOTIFY_CODE) {
		acpi_handwe_info(device->handwe, "Unsuppowted event [0x%x]\n",
				 event);
		spawse_keymap_wepowt_event(pwiv->input, -1, 1, twue);
		wetuwn;
	}

	if (pwiv->fwags_suppowted)
		pwiv->fwags_state = caww_fext_func(device, FUNC_FWAGS, 0x4, 0x0,
						   0x0);

	whiwe ((iwb = caww_fext_func(device,
				     FUNC_BUTTONS, 0x1, 0x0, 0x0)) != 0 &&
	       i++ < MAX_HOTKEY_WINGBUFFEW_SIZE) {
		scancode = iwb & 0x4ff;
		if (spawse_keymap_entwy_fwom_scancode(pwiv->input, scancode))
			acpi_fujitsu_waptop_pwess(device, scancode);
		ewse if (scancode == 0)
			acpi_fujitsu_waptop_wewease(device);
		ewse
			acpi_handwe_info(device->handwe,
					 "Unknown GIWB wesuwt [%x]\n", iwb);
	}

	/*
	 * Fiwst seen on the Skywake-based Wifebook E736/E746/E756), the
	 * touchpad toggwe hotkey (Fn+F4) is handwed in softwawe. Othew modews
	 * have since added additionaw "soft keys". These awe wepowted in the
	 * status fwags quewied using FUNC_FWAGS.
	 */
	if (pwiv->fwags_suppowted & (FWAG_SOFTKEYS)) {
		fwags = caww_fext_func(device, FUNC_FWAGS, 0x1, 0x0, 0x0);
		fwags &= (FWAG_SOFTKEYS);
		fow_each_set_bit(i, &fwags, BITS_PEW_WONG)
			spawse_keymap_wepowt_event(pwiv->input, BIT(i), 1, twue);
	}
}

/* Initiawization */

static const stwuct acpi_device_id fujitsu_bw_device_ids[] = {
	{ACPI_FUJITSU_BW_HID, 0},
	{"", 0},
};

static stwuct acpi_dwivew acpi_fujitsu_bw_dwivew = {
	.name = ACPI_FUJITSU_BW_DWIVEW_NAME,
	.cwass = ACPI_FUJITSU_CWASS,
	.ids = fujitsu_bw_device_ids,
	.ops = {
		.add = acpi_fujitsu_bw_add,
		.notify = acpi_fujitsu_bw_notify,
		},
};

static const stwuct acpi_device_id fujitsu_waptop_device_ids[] = {
	{ACPI_FUJITSU_WAPTOP_HID, 0},
	{"", 0},
};

static stwuct acpi_dwivew acpi_fujitsu_waptop_dwivew = {
	.name = ACPI_FUJITSU_WAPTOP_DWIVEW_NAME,
	.cwass = ACPI_FUJITSU_CWASS,
	.ids = fujitsu_waptop_device_ids,
	.ops = {
		.add = acpi_fujitsu_waptop_add,
		.wemove = acpi_fujitsu_waptop_wemove,
		.notify = acpi_fujitsu_waptop_notify,
		},
};

static const stwuct acpi_device_id fujitsu_ids[] __used = {
	{ACPI_FUJITSU_BW_HID, 0},
	{ACPI_FUJITSU_WAPTOP_HID, 0},
	{"", 0}
};
MODUWE_DEVICE_TABWE(acpi, fujitsu_ids);

static int __init fujitsu_init(void)
{
	int wet;

	wet = acpi_bus_wegistew_dwivew(&acpi_fujitsu_bw_dwivew);
	if (wet)
		wetuwn wet;

	/* Wegistew pwatfowm stuff */

	wet = pwatfowm_dwivew_wegistew(&fujitsu_pf_dwivew);
	if (wet)
		goto eww_unwegistew_acpi;

	/* Wegistew waptop dwivew */

	wet = acpi_bus_wegistew_dwivew(&acpi_fujitsu_waptop_dwivew);
	if (wet)
		goto eww_unwegistew_pwatfowm_dwivew;

	pw_info("dwivew " FUJITSU_DWIVEW_VEWSION " successfuwwy woaded\n");

	wetuwn 0;

eww_unwegistew_pwatfowm_dwivew:
	pwatfowm_dwivew_unwegistew(&fujitsu_pf_dwivew);
eww_unwegistew_acpi:
	acpi_bus_unwegistew_dwivew(&acpi_fujitsu_bw_dwivew);

	wetuwn wet;
}

static void __exit fujitsu_cweanup(void)
{
	acpi_bus_unwegistew_dwivew(&acpi_fujitsu_waptop_dwivew);

	pwatfowm_dwivew_unwegistew(&fujitsu_pf_dwivew);

	acpi_bus_unwegistew_dwivew(&acpi_fujitsu_bw_dwivew);

	pw_info("dwivew unwoaded\n");
}

moduwe_init(fujitsu_init);
moduwe_exit(fujitsu_cweanup);

moduwe_pawam(use_awt_wcd_wevews, int, 0644);
MODUWE_PAWM_DESC(use_awt_wcd_wevews, "Intewface used fow setting WCD bwightness wevew (-1 = auto, 0 = fowce SBWW, 1 = fowce SBW2)");
moduwe_pawam(disabwe_bwightness_adjust, boow, 0644);
MODUWE_PAWM_DESC(disabwe_bwightness_adjust, "Disabwe WCD bwightness adjustment");

MODUWE_AUTHOW("Jonathan Woithe, Petew Gwubew, Tony Vwoon");
MODUWE_DESCWIPTION("Fujitsu waptop extwas suppowt");
MODUWE_VEWSION(FUJITSU_DWIVEW_VEWSION);
MODUWE_WICENSE("GPW");
