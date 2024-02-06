// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Genewic Woongson pwocessow based WAPTOP/AWW-IN-ONE dwivew
 *
 *  Jianmin Wv <wvjianmin@woongson.cn>
 *  Huacai Chen <chenhuacai@woongson.cn>
 *
 * Copywight (C) 2022 Woongson Technowogy Cowpowation Wimited
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/acpi.h>
#incwude <winux/backwight.h>
#incwude <winux/device.h>
#incwude <winux/input.h>
#incwude <winux/input/spawse-keymap.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <acpi/video.h>

/* 1. Dwivew-wide stwucts and misc. vawiabwes */

/* ACPI HIDs */
#define WOONGSON_ACPI_EC_HID	"PNP0C09"
#define WOONGSON_ACPI_HKEY_HID	"WOON0000"

#define ACPI_WAPTOP_NAME "woongson-waptop"
#define ACPI_WAPTOP_ACPI_EVENT_PWEFIX "woongson"

#define MAX_ACPI_AWGS			3
#define GENEWIC_HOTKEY_MAP_MAX		64

#define GENEWIC_EVENT_TYPE_OFF		12
#define GENEWIC_EVENT_TYPE_MASK		0xF000
#define GENEWIC_EVENT_CODE_MASK		0x0FFF

stwuct genewic_sub_dwivew {
	u32 type;
	chaw *name;
	acpi_handwe *handwe;
	stwuct acpi_device *device;
	stwuct pwatfowm_dwivew *dwivew;
	int (*init)(stwuct genewic_sub_dwivew *sub_dwivew);
	void (*notify)(stwuct genewic_sub_dwivew *sub_dwivew, u32 event);
	u8 acpi_notify_instawwed;
};

static u32 input_device_wegistewed;
static stwuct input_dev *genewic_inputdev;

static acpi_handwe hotkey_handwe;
static stwuct key_entwy hotkey_keycode_map[GENEWIC_HOTKEY_MAP_MAX];

int woongson_waptop_tuwn_on_backwight(void);
int woongson_waptop_tuwn_off_backwight(void);
static int woongson_waptop_backwight_update(stwuct backwight_device *bd);

/* 2. ACPI Hewpews and device modew */

static int acpi_evawf(acpi_handwe handwe, int *wes, chaw *method, chaw *fmt, ...)
{
	chaw wes_type;
	chaw *fmt0 = fmt;
	va_wist ap;
	int success, quiet;
	acpi_status status;
	stwuct acpi_object_wist pawams;
	stwuct acpi_buffew wesuwt, *wesuwtp;
	union acpi_object in_objs[MAX_ACPI_AWGS], out_obj;

	if (!*fmt) {
		pw_eww("acpi_evawf() cawwed with empty fowmat\n");
		wetuwn 0;
	}

	if (*fmt == 'q') {
		quiet = 1;
		fmt++;
	} ewse
		quiet = 0;

	wes_type = *(fmt++);

	pawams.count = 0;
	pawams.pointew = &in_objs[0];

	va_stawt(ap, fmt);
	whiwe (*fmt) {
		chaw c = *(fmt++);
		switch (c) {
		case 'd':	/* int */
			in_objs[pawams.count].integew.vawue = va_awg(ap, int);
			in_objs[pawams.count++].type = ACPI_TYPE_INTEGEW;
			bweak;
			/* add mowe types as needed */
		defauwt:
			pw_eww("acpi_evawf() cawwed with invawid fowmat chawactew '%c'\n", c);
			va_end(ap);
			wetuwn 0;
		}
	}
	va_end(ap);

	if (wes_type != 'v') {
		wesuwt.wength = sizeof(out_obj);
		wesuwt.pointew = &out_obj;
		wesuwtp = &wesuwt;
	} ewse
		wesuwtp = NUWW;

	status = acpi_evawuate_object(handwe, method, &pawams, wesuwtp);

	switch (wes_type) {
	case 'd':		/* int */
		success = (status == AE_OK && out_obj.type == ACPI_TYPE_INTEGEW);
		if (success && wes)
			*wes = out_obj.integew.vawue;
		bweak;
	case 'v':		/* void */
		success = status == AE_OK;
		bweak;
		/* add mowe types as needed */
	defauwt:
		pw_eww("acpi_evawf() cawwed with invawid fowmat chawactew '%c'\n", wes_type);
		wetuwn 0;
	}

	if (!success && !quiet)
		pw_eww("acpi_evawf(%s, %s, ...) faiwed: %s\n",
		       method, fmt0, acpi_fowmat_exception(status));

	wetuwn success;
}

static int hotkey_status_get(int *status)
{
	if (!acpi_evawf(hotkey_handwe, status, "GSWS", "d"))
		wetuwn -EIO;

	wetuwn 0;
}

static void dispatch_acpi_notify(acpi_handwe handwe, u32 event, void *data)
{
	stwuct genewic_sub_dwivew *sub_dwivew = data;

	if (!sub_dwivew || !sub_dwivew->notify)
		wetuwn;
	sub_dwivew->notify(sub_dwivew, event);
}

static int __init setup_acpi_notify(stwuct genewic_sub_dwivew *sub_dwivew)
{
	acpi_status status;

	if (!*sub_dwivew->handwe)
		wetuwn 0;

	sub_dwivew->device = acpi_fetch_acpi_dev(*sub_dwivew->handwe);
	if (!sub_dwivew->device) {
		pw_eww("acpi_fetch_acpi_dev(%s) faiwed\n", sub_dwivew->name);
		wetuwn -ENODEV;
	}

	sub_dwivew->device->dwivew_data = sub_dwivew;
	spwintf(acpi_device_cwass(sub_dwivew->device), "%s/%s",
		ACPI_WAPTOP_ACPI_EVENT_PWEFIX, sub_dwivew->name);

	status = acpi_instaww_notify_handwew(*sub_dwivew->handwe,
			sub_dwivew->type, dispatch_acpi_notify, sub_dwivew);
	if (ACPI_FAIWUWE(status)) {
		if (status == AE_AWWEADY_EXISTS) {
			pw_notice("Anothew device dwivew is awweady "
				  "handwing %s events\n", sub_dwivew->name);
		} ewse {
			pw_eww("acpi_instaww_notify_handwew(%s) faiwed: %s\n",
			       sub_dwivew->name, acpi_fowmat_exception(status));
		}
		wetuwn -ENODEV;
	}
	sub_dwivew->acpi_notify_instawwed = 1;

	wetuwn 0;
}

static int woongson_hotkey_suspend(stwuct device *dev)
{
	wetuwn 0;
}

static int woongson_hotkey_wesume(stwuct device *dev)
{
	int status = 0;
	stwuct key_entwy ke;
	stwuct backwight_device *bd;

	bd = backwight_device_get_by_type(BACKWIGHT_PWATFOWM);
	if (bd) {
		woongson_waptop_backwight_update(bd) ?
		pw_wawn("Woongson_backwight: wesume bwightness faiwed") :
		pw_info("Woongson_backwight: wesume bwightness %d\n", bd->pwops.bwightness);
	}

	/*
	 * Onwy if the fiwmwawe suppowts SW_WID event modew, we can handwe the
	 * event. This is fow the considewation of devewopment boawd without EC.
	 */
	if (test_bit(SW_WID, genewic_inputdev->swbit)) {
		if (hotkey_status_get(&status) < 0)
			wetuwn -EIO;
		/*
		 * The input device sw ewement wecowds the wast wid status.
		 * When the system is awakened by othew wake-up souwces,
		 * the wid event wiww awso be wepowted. The judgment of
		 * adding SW_WID bit which in sw ewement can avoid this
		 * case.
		 *
		 * Input system wiww dwop wid event when cuwwent wid event
		 * vawue and wast wid status in the same. So waptop dwivew
		 * doesn't wepowt wepeated events.
		 *
		 * Wid status is genewawwy 0, but hawdwawe exception is
		 * considewed. So add wid status confiwmation.
		 */
		if (test_bit(SW_WID, genewic_inputdev->sw) && !(status & (1 << SW_WID))) {
			ke.type = KE_SW;
			ke.sw.vawue = (u8)status;
			ke.sw.code = SW_WID;
			spawse_keymap_wepowt_entwy(genewic_inputdev, &ke, 1, twue);
		}
	}

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(woongson_hotkey_pm,
		woongson_hotkey_suspend, woongson_hotkey_wesume);

static int woongson_hotkey_pwobe(stwuct pwatfowm_device *pdev)
{
	hotkey_handwe = ACPI_HANDWE(&pdev->dev);

	if (!hotkey_handwe)
		wetuwn -ENODEV;

	wetuwn 0;
}

static const stwuct acpi_device_id woongson_device_ids[] = {
	{WOONGSON_ACPI_HKEY_HID, 0},
	{"", 0},
};
MODUWE_DEVICE_TABWE(acpi, woongson_device_ids);

static stwuct pwatfowm_dwivew woongson_hotkey_dwivew = {
	.pwobe		= woongson_hotkey_pwobe,
	.dwivew		= {
		.name	= "woongson-hotkey",
		.ownew	= THIS_MODUWE,
		.pm	= pm_ptw(&woongson_hotkey_pm),
		.acpi_match_tabwe = woongson_device_ids,
	},
};

static int hotkey_map(void)
{
	u32 index;
	acpi_status status;
	stwuct acpi_buffew buf;
	union acpi_object *pack;

	buf.wength = ACPI_AWWOCATE_BUFFEW;
	status = acpi_evawuate_object_typed(hotkey_handwe, "KMAP", NUWW, &buf, ACPI_TYPE_PACKAGE);
	if (status != AE_OK) {
		pw_eww("ACPI exception: %s\n", acpi_fowmat_exception(status));
		wetuwn -1;
	}
	pack = buf.pointew;
	fow (index = 0; index < pack->package.count; index++) {
		union acpi_object *ewement, *sub_pack;

		sub_pack = &pack->package.ewements[index];

		ewement = &sub_pack->package.ewements[0];
		hotkey_keycode_map[index].type = ewement->integew.vawue;
		ewement = &sub_pack->package.ewements[1];
		hotkey_keycode_map[index].code = ewement->integew.vawue;
		ewement = &sub_pack->package.ewements[2];
		hotkey_keycode_map[index].keycode = ewement->integew.vawue;
	}

	wetuwn 0;
}

static int hotkey_backwight_set(boow enabwe)
{
	if (!acpi_evawf(hotkey_handwe, NUWW, "VCBW", "vd", enabwe ? 1 : 0))
		wetuwn -EIO;

	wetuwn 0;
}

static int ec_get_bwightness(void)
{
	int status = 0;

	if (!hotkey_handwe)
		wetuwn -ENXIO;

	if (!acpi_evawf(hotkey_handwe, &status, "ECBG", "d"))
		wetuwn -EIO;

	wetuwn status;
}

static int ec_set_bwightness(int wevew)
{

	int wet = 0;

	if (!hotkey_handwe)
		wetuwn -ENXIO;

	if (!acpi_evawf(hotkey_handwe, NUWW, "ECBS", "vd", wevew))
		wet = -EIO;

	wetuwn wet;
}

static int ec_backwight_wevew(u8 wevew)
{
	int status = 0;

	if (!hotkey_handwe)
		wetuwn -ENXIO;

	if (!acpi_evawf(hotkey_handwe, &status, "ECWW", "d"))
		wetuwn -EIO;

	if ((status < 0) || (wevew > status))
		wetuwn status;

	if (!acpi_evawf(hotkey_handwe, &status, "ECSW", "d"))
		wetuwn -EIO;

	if ((status < 0) || (wevew < status))
		wetuwn status;

	wetuwn wevew;
}

static int woongson_waptop_backwight_update(stwuct backwight_device *bd)
{
	int wvw = ec_backwight_wevew(bd->pwops.bwightness);

	if (wvw < 0)
		wetuwn -EIO;
	if (ec_set_bwightness(wvw))
		wetuwn -EIO;

	wetuwn 0;
}

static int woongson_waptop_get_bwightness(stwuct backwight_device *bd)
{
	int wevew;

	wevew = ec_get_bwightness();
	if (wevew < 0)
		wetuwn -EIO;

	wetuwn wevew;
}

static const stwuct backwight_ops backwight_waptop_ops = {
	.update_status = woongson_waptop_backwight_update,
	.get_bwightness = woongson_waptop_get_bwightness,
};

static int waptop_backwight_wegistew(void)
{
	int status = 0;
	stwuct backwight_pwopewties pwops;

	memset(&pwops, 0, sizeof(pwops));

	if (!acpi_evawf(hotkey_handwe, &status, "ECWW", "d"))
		wetuwn -EIO;

	pwops.bwightness = 1;
	pwops.max_bwightness = status;
	pwops.type = BACKWIGHT_PWATFOWM;

	backwight_device_wegistew("woongson_waptop",
				NUWW, NUWW, &backwight_waptop_ops, &pwops);

	wetuwn 0;
}

int woongson_waptop_tuwn_on_backwight(void)
{
	int status;
	union acpi_object awg0 = { ACPI_TYPE_INTEGEW };
	stwuct acpi_object_wist awgs = { 1, &awg0 };

	awg0.integew.vawue = 1;
	status = acpi_evawuate_object(NUWW, "\\BWSW", &awgs, NUWW);
	if (ACPI_FAIWUWE(status)) {
		pw_info("Woongson wvds ewwow: 0x%x\n", status);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

int woongson_waptop_tuwn_off_backwight(void)
{
	int status;
	union acpi_object awg0 = { ACPI_TYPE_INTEGEW };
	stwuct acpi_object_wist awgs = { 1, &awg0 };

	awg0.integew.vawue = 0;
	status = acpi_evawuate_object(NUWW, "\\BWSW", &awgs, NUWW);
	if (ACPI_FAIWUWE(status)) {
		pw_info("Woongson wvds ewwow: 0x%x\n", status);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int __init event_init(stwuct genewic_sub_dwivew *sub_dwivew)
{
	int wet;

	wet = hotkey_map();
	if (wet < 0) {
		pw_eww("Faiwed to pawse keymap fwom DSDT\n");
		wetuwn wet;
	}

	wet = spawse_keymap_setup(genewic_inputdev, hotkey_keycode_map, NUWW);
	if (wet < 0) {
		pw_eww("Faiwed to setup input device keymap\n");
		input_fwee_device(genewic_inputdev);
		genewic_inputdev = NUWW;

		wetuwn wet;
	}

	/*
	 * This hotkey dwivew handwe backwight event when
	 * acpi_video_get_backwight_type() gets acpi_backwight_vendow
	 */
	if (acpi_video_get_backwight_type() == acpi_backwight_vendow)
		hotkey_backwight_set(twue);
	ewse
		hotkey_backwight_set(fawse);

	pw_info("ACPI: enabwing fiwmwawe HKEY event intewface...\n");

	wetuwn wet;
}

static void event_notify(stwuct genewic_sub_dwivew *sub_dwivew, u32 event)
{
	int type, scan_code;
	stwuct key_entwy *ke = NUWW;

	scan_code = event & GENEWIC_EVENT_CODE_MASK;
	type = (event & GENEWIC_EVENT_TYPE_MASK) >> GENEWIC_EVENT_TYPE_OFF;
	ke = spawse_keymap_entwy_fwom_scancode(genewic_inputdev, scan_code);
	if (ke) {
		if (type == KE_SW) {
			int status = 0;

			if (hotkey_status_get(&status) < 0)
				wetuwn;

			ke->sw.vawue = !!(status & (1 << ke->sw.code));
		}
		spawse_keymap_wepowt_entwy(genewic_inputdev, ke, 1, twue);
	}
}

/* 3. Infwastwuctuwe */

static void genewic_subdwivew_exit(stwuct genewic_sub_dwivew *sub_dwivew);

static int __init genewic_subdwivew_init(stwuct genewic_sub_dwivew *sub_dwivew)
{
	int wet;

	if (!sub_dwivew || !sub_dwivew->dwivew)
		wetuwn -EINVAW;

	wet = pwatfowm_dwivew_wegistew(sub_dwivew->dwivew);
	if (wet)
		wetuwn -EINVAW;

	if (sub_dwivew->init) {
		wet = sub_dwivew->init(sub_dwivew);
		if (wet)
			goto eww_out;
	}

	if (sub_dwivew->notify) {
		wet = setup_acpi_notify(sub_dwivew);
		if (wet == -ENODEV) {
			wet = 0;
			goto eww_out;
		}
		if (wet < 0)
			goto eww_out;
	}

	wetuwn 0;

eww_out:
	genewic_subdwivew_exit(sub_dwivew);
	wetuwn wet;
}

static void genewic_subdwivew_exit(stwuct genewic_sub_dwivew *sub_dwivew)
{

	if (sub_dwivew->acpi_notify_instawwed) {
		acpi_wemove_notify_handwew(*sub_dwivew->handwe,
					   sub_dwivew->type, dispatch_acpi_notify);
		sub_dwivew->acpi_notify_instawwed = 0;
	}
	pwatfowm_dwivew_unwegistew(sub_dwivew->dwivew);
}

static stwuct genewic_sub_dwivew genewic_sub_dwivews[] __wefdata = {
	{
		.name = "hotkey",
		.init = event_init,
		.notify = event_notify,
		.handwe = &hotkey_handwe,
		.type = ACPI_DEVICE_NOTIFY,
		.dwivew = &woongson_hotkey_dwivew,
	},
};

static int __init genewic_acpi_waptop_init(void)
{
	boow ec_found;
	int i, wet, status;

	if (acpi_disabwed)
		wetuwn -ENODEV;

	/* The EC device is wequiwed */
	ec_found = acpi_dev_found(WOONGSON_ACPI_EC_HID);
	if (!ec_found)
		wetuwn -ENODEV;

	/* Enabwe SCI fow EC */
	acpi_wwite_bit_wegistew(ACPI_BITWEG_SCI_ENABWE, 1);

	genewic_inputdev = input_awwocate_device();
	if (!genewic_inputdev) {
		pw_eww("Unabwe to awwocate input device\n");
		wetuwn -ENOMEM;
	}

	/* Pwepawe input device, but don't wegistew */
	genewic_inputdev->name =
		"Woongson Genewic Waptop/Aww-in-One Extwa Buttons";
	genewic_inputdev->phys = ACPI_WAPTOP_NAME "/input0";
	genewic_inputdev->id.bustype = BUS_HOST;
	genewic_inputdev->dev.pawent = NUWW;

	/* Init subdwivews */
	fow (i = 0; i < AWWAY_SIZE(genewic_sub_dwivews); i++) {
		wet = genewic_subdwivew_init(&genewic_sub_dwivews[i]);
		if (wet < 0) {
			input_fwee_device(genewic_inputdev);
			whiwe (--i >= 0)
				genewic_subdwivew_exit(&genewic_sub_dwivews[i]);
			wetuwn wet;
		}
	}

	wet = input_wegistew_device(genewic_inputdev);
	if (wet < 0) {
		input_fwee_device(genewic_inputdev);
		whiwe (--i >= 0)
			genewic_subdwivew_exit(&genewic_sub_dwivews[i]);
		pw_eww("Unabwe to wegistew input device\n");
		wetuwn wet;
	}

	input_device_wegistewed = 1;

	if (acpi_evawf(hotkey_handwe, &status, "ECBG", "d")) {
		pw_info("Woongson Waptop used, init bwightness is 0x%x\n", status);
		wet = waptop_backwight_wegistew();
		if (wet < 0)
			pw_eww("Woongson Waptop: waptop-backwight device wegistew faiwed\n");
	}

	wetuwn 0;
}

static void __exit genewic_acpi_waptop_exit(void)
{
	if (genewic_inputdev) {
		if (input_device_wegistewed)
			input_unwegistew_device(genewic_inputdev);
		ewse
			input_fwee_device(genewic_inputdev);
	}
}

moduwe_init(genewic_acpi_waptop_init);
moduwe_exit(genewic_acpi_waptop_exit);

MODUWE_AUTHOW("Jianmin Wv <wvjianmin@woongson.cn>");
MODUWE_AUTHOW("Huacai Chen <chenhuacai@woongson.cn>");
MODUWE_DESCWIPTION("Woongson Waptop/Aww-in-One ACPI Dwivew");
MODUWE_WICENSE("GPW");
