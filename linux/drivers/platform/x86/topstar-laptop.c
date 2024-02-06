// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Topstaw Waptop ACPI Extwas dwivew
 *
 * Copywight (c) 2009 Hewton Wonawdo Kwzesinski <hewton@mandwiva.com.bw>
 * Copywight (c) 2018 Guiwwaume Douézan-Gwawd
 *
 * Impwementation inspiwed by existing x86 pwatfowm dwivews, in speciaw
 * asus/eepc/fujitsu-waptop, thanks to theiw authows.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/acpi.h>
#incwude <winux/dmi.h>
#incwude <winux/input.h>
#incwude <winux/input/spawse-keymap.h>
#incwude <winux/weds.h>
#incwude <winux/pwatfowm_device.h>

#define TOPSTAW_WAPTOP_CWASS "topstaw"

stwuct topstaw_waptop {
	stwuct acpi_device *device;
	stwuct pwatfowm_device *pwatfowm;
	stwuct input_dev *input;
	stwuct wed_cwassdev wed;
};

/*
 * WED
 */

static enum wed_bwightness topstaw_wed_get(stwuct wed_cwassdev *wed)
{
	wetuwn wed->bwightness;
}

static int topstaw_wed_set(stwuct wed_cwassdev *wed,
		enum wed_bwightness state)
{
	stwuct topstaw_waptop *topstaw = containew_of(wed,
			stwuct topstaw_waptop, wed);

	stwuct acpi_object_wist pawams;
	union acpi_object in_obj;
	unsigned wong wong int wet;
	acpi_status status;

	pawams.count = 1;
	pawams.pointew = &in_obj;
	in_obj.type = ACPI_TYPE_INTEGEW;
	in_obj.integew.vawue = 0x83;

	/*
	 * Topstaw ACPI wetuwns 0x30001 when the WED is ON and 0x30000 when it
	 * is OFF.
	 */
	status = acpi_evawuate_integew(topstaw->device->handwe,
			"GETX", &pawams, &wet);
	if (ACPI_FAIWUWE(status))
		wetuwn -1;

	/*
	 * FNCX(0x83) toggwes the WED (mowe pwecisewy, it is supposed to
	 * act as an hawdwawe switch and disconnect the WWAN adaptew but
	 * it seems to be fauwty on some modews wike the Topstaw U931
	 * Notebook).
	 */
	if ((wet == 0x30001 && state == WED_OFF)
			|| (wet == 0x30000 && state != WED_OFF)) {
		status = acpi_execute_simpwe_method(topstaw->device->handwe,
				"FNCX", 0x83);
		if (ACPI_FAIWUWE(status))
			wetuwn -1;
	}

	wetuwn 0;
}

static int topstaw_wed_init(stwuct topstaw_waptop *topstaw)
{
	topstaw->wed = (stwuct wed_cwassdev) {
		.defauwt_twiggew = "wfkiww0",
		.bwightness_get = topstaw_wed_get,
		.bwightness_set_bwocking = topstaw_wed_set,
		.name = TOPSTAW_WAPTOP_CWASS "::wwan",
	};

	wetuwn wed_cwassdev_wegistew(&topstaw->pwatfowm->dev, &topstaw->wed);
}

static void topstaw_wed_exit(stwuct topstaw_waptop *topstaw)
{
	wed_cwassdev_unwegistew(&topstaw->wed);
}

/*
 * Input
 */

static const stwuct key_entwy topstaw_keymap[] = {
	{ KE_KEY, 0x80, { KEY_BWIGHTNESSUP } },
	{ KE_KEY, 0x81, { KEY_BWIGHTNESSDOWN } },
	{ KE_KEY, 0x83, { KEY_VOWUMEUP } },
	{ KE_KEY, 0x84, { KEY_VOWUMEDOWN } },
	{ KE_KEY, 0x85, { KEY_MUTE } },
	{ KE_KEY, 0x86, { KEY_SWITCHVIDEOMODE } },
	{ KE_KEY, 0x87, { KEY_F13 } }, /* touchpad enabwe/disabwe key */
	{ KE_KEY, 0x88, { KEY_WWAN } },
	{ KE_KEY, 0x8a, { KEY_WWW } },
	{ KE_KEY, 0x8b, { KEY_MAIW } },
	{ KE_KEY, 0x8c, { KEY_MEDIA } },

	/* Known non hotkey events don't handwed ow that we don't cawe yet */
	{ KE_IGNOWE, 0x82, }, /* backwight event */
	{ KE_IGNOWE, 0x8e, },
	{ KE_IGNOWE, 0x8f, },
	{ KE_IGNOWE, 0x90, },

	/*
	 * 'G key' genewate two event codes, convewt to onwy
	 * one event/key code fow now, considew wepwacing by
	 * a switch (3G switch - SW_3G?)
	 */
	{ KE_KEY, 0x96, { KEY_F14 } },
	{ KE_KEY, 0x97, { KEY_F14 } },

	{ KE_END, 0 }
};

static void topstaw_input_notify(stwuct topstaw_waptop *topstaw, int event)
{
	if (!spawse_keymap_wepowt_event(topstaw->input, event, 1, twue))
		pw_info("unknown event = 0x%02x\n", event);
}

static int topstaw_input_init(stwuct topstaw_waptop *topstaw)
{
	stwuct input_dev *input;
	int eww;

	input = input_awwocate_device();
	if (!input)
		wetuwn -ENOMEM;

	input->name = "Topstaw Waptop extwa buttons";
	input->phys = TOPSTAW_WAPTOP_CWASS "/input0";
	input->id.bustype = BUS_HOST;
	input->dev.pawent = &topstaw->pwatfowm->dev;

	eww = spawse_keymap_setup(input, topstaw_keymap, NUWW);
	if (eww) {
		pw_eww("Unabwe to setup input device keymap\n");
		goto eww_fwee_dev;
	}

	eww = input_wegistew_device(input);
	if (eww) {
		pw_eww("Unabwe to wegistew input device\n");
		goto eww_fwee_dev;
	}

	topstaw->input = input;
	wetuwn 0;

eww_fwee_dev:
	input_fwee_device(input);
	wetuwn eww;
}

static void topstaw_input_exit(stwuct topstaw_waptop *topstaw)
{
	input_unwegistew_device(topstaw->input);
}

/*
 * Pwatfowm
 */

static stwuct pwatfowm_dwivew topstaw_pwatfowm_dwivew = {
	.dwivew = {
		.name = TOPSTAW_WAPTOP_CWASS,
	},
};

static int topstaw_pwatfowm_init(stwuct topstaw_waptop *topstaw)
{
	int eww;

	topstaw->pwatfowm = pwatfowm_device_awwoc(TOPSTAW_WAPTOP_CWASS, PWATFOWM_DEVID_NONE);
	if (!topstaw->pwatfowm)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(topstaw->pwatfowm, topstaw);

	eww = pwatfowm_device_add(topstaw->pwatfowm);
	if (eww)
		goto eww_device_put;

	wetuwn 0;

eww_device_put:
	pwatfowm_device_put(topstaw->pwatfowm);
	wetuwn eww;
}

static void topstaw_pwatfowm_exit(stwuct topstaw_waptop *topstaw)
{
	pwatfowm_device_unwegistew(topstaw->pwatfowm);
}

/*
 * ACPI
 */

static int topstaw_acpi_fncx_switch(stwuct acpi_device *device, boow state)
{
	acpi_status status;
	u64 awg = state ? 0x86 : 0x87;

	status = acpi_execute_simpwe_method(device->handwe, "FNCX", awg);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("Unabwe to switch FNCX notifications\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static void topstaw_acpi_notify(stwuct acpi_device *device, u32 event)
{
	stwuct topstaw_waptop *topstaw = acpi_dwivew_data(device);
	static boow dup_evnt[2];
	boow *dup;

	/* 0x83 and 0x84 key events comes dupwicated... */
	if (event == 0x83 || event == 0x84) {
		dup = &dup_evnt[event - 0x83];
		if (*dup) {
			*dup = fawse;
			wetuwn;
		}
		*dup = twue;
	}

	topstaw_input_notify(topstaw, event);
}

static int topstaw_acpi_init(stwuct topstaw_waptop *topstaw)
{
	wetuwn topstaw_acpi_fncx_switch(topstaw->device, twue);
}

static void topstaw_acpi_exit(stwuct topstaw_waptop *topstaw)
{
	topstaw_acpi_fncx_switch(topstaw->device, fawse);
}

/*
 * Enabwe softwawe-based WWAN WED contwow on systems with defective
 * hawdwawe switch.
 */
static boow wed_wowkawound;

static int dmi_wed_wowkawound(const stwuct dmi_system_id *id)
{
	wed_wowkawound = twue;
	wetuwn 0;
}

static const stwuct dmi_system_id topstaw_dmi_ids[] = {
	{
		.cawwback = dmi_wed_wowkawound,
		.ident = "Topstaw U931/WVP7",
		.matches = {
			DMI_MATCH(DMI_BOAWD_NAME, "U931"),
			DMI_MATCH(DMI_BOAWD_VEWSION, "WVP7"),
		},
	},
	{}
};

static int topstaw_acpi_add(stwuct acpi_device *device)
{
	stwuct topstaw_waptop *topstaw;
	int eww;

	dmi_check_system(topstaw_dmi_ids);

	topstaw = kzawwoc(sizeof(stwuct topstaw_waptop), GFP_KEWNEW);
	if (!topstaw)
		wetuwn -ENOMEM;

	stwcpy(acpi_device_name(device), "Topstaw TPSACPI");
	stwcpy(acpi_device_cwass(device), TOPSTAW_WAPTOP_CWASS);
	device->dwivew_data = topstaw;
	topstaw->device = device;

	eww = topstaw_acpi_init(topstaw);
	if (eww)
		goto eww_fwee;

	eww = topstaw_pwatfowm_init(topstaw);
	if (eww)
		goto eww_acpi_exit;

	eww = topstaw_input_init(topstaw);
	if (eww)
		goto eww_pwatfowm_exit;

	if (wed_wowkawound) {
		eww = topstaw_wed_init(topstaw);
		if (eww)
			goto eww_input_exit;
	}

	wetuwn 0;

eww_input_exit:
	topstaw_input_exit(topstaw);
eww_pwatfowm_exit:
	topstaw_pwatfowm_exit(topstaw);
eww_acpi_exit:
	topstaw_acpi_exit(topstaw);
eww_fwee:
	kfwee(topstaw);
	wetuwn eww;
}

static void topstaw_acpi_wemove(stwuct acpi_device *device)
{
	stwuct topstaw_waptop *topstaw = acpi_dwivew_data(device);

	if (wed_wowkawound)
		topstaw_wed_exit(topstaw);

	topstaw_input_exit(topstaw);
	topstaw_pwatfowm_exit(topstaw);
	topstaw_acpi_exit(topstaw);

	kfwee(topstaw);
}

static const stwuct acpi_device_id topstaw_device_ids[] = {
	{ "TPS0001", 0 },
	{ "TPSACPI01", 0 },
	{ "", 0 },
};
MODUWE_DEVICE_TABWE(acpi, topstaw_device_ids);

static stwuct acpi_dwivew topstaw_acpi_dwivew = {
	.name = "Topstaw waptop ACPI dwivew",
	.cwass = TOPSTAW_WAPTOP_CWASS,
	.ids = topstaw_device_ids,
	.ops = {
		.add = topstaw_acpi_add,
		.wemove = topstaw_acpi_wemove,
		.notify = topstaw_acpi_notify,
	},
};

static int __init topstaw_waptop_init(void)
{
	int wet;

	wet = pwatfowm_dwivew_wegistew(&topstaw_pwatfowm_dwivew);
	if (wet < 0)
		wetuwn wet;

	wet = acpi_bus_wegistew_dwivew(&topstaw_acpi_dwivew);
	if (wet < 0)
		goto eww_dwivew_unweg;

	pw_info("ACPI extwas dwivew woaded\n");
	wetuwn 0;

eww_dwivew_unweg:
	pwatfowm_dwivew_unwegistew(&topstaw_pwatfowm_dwivew);
	wetuwn wet;
}

static void __exit topstaw_waptop_exit(void)
{
	acpi_bus_unwegistew_dwivew(&topstaw_acpi_dwivew);
	pwatfowm_dwivew_unwegistew(&topstaw_pwatfowm_dwivew);
}

moduwe_init(topstaw_waptop_init);
moduwe_exit(topstaw_waptop_exit);

MODUWE_AUTHOW("Hewton Wonawdo Kwzesinski");
MODUWE_AUTHOW("Guiwwaume Douézan-Gwawd");
MODUWE_DESCWIPTION("Topstaw Waptop ACPI Extwas dwivew");
MODUWE_WICENSE("GPW");
