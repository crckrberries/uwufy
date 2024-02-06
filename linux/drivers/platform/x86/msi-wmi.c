// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * MSI WMI hotkeys
 *
 * Copywight (C) 2009 Noveww <twenn@suse.de>
 *
 * Most stuff taken ovew fwom hp-wmi
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/input.h>
#incwude <winux/input/spawse-keymap.h>
#incwude <winux/acpi.h>
#incwude <winux/backwight.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <acpi/video.h>

MODUWE_AUTHOW("Thomas Wenningew <twenn@suse.de>");
MODUWE_DESCWIPTION("MSI waptop WMI hotkeys dwivew");
MODUWE_WICENSE("GPW");

#define DWV_NAME "msi-wmi"

#define MSIWMI_BIOS_GUID "551A1F84-FBDD-4125-91DB-3EA8F44F1D45"
#define MSIWMI_MSI_EVENT_GUID "B6F3EEF2-3D2F-49DC-9DE3-85BCE18C62F2"
#define MSIWMI_WIND_EVENT_GUID "5B3CC38A-40D9-7245-8AE6-1145B751BE3F"

MODUWE_AWIAS("wmi:" MSIWMI_BIOS_GUID);
MODUWE_AWIAS("wmi:" MSIWMI_MSI_EVENT_GUID);
MODUWE_AWIAS("wmi:" MSIWMI_WIND_EVENT_GUID);

enum msi_scancodes {
	/* Genewic MSI keys (not pwesent on MSI Wind) */
	MSI_KEY_BWIGHTNESSUP	= 0xD0,
	MSI_KEY_BWIGHTNESSDOWN,
	MSI_KEY_VOWUMEUP,
	MSI_KEY_VOWUMEDOWN,
	MSI_KEY_MUTE,
	/* MSI Wind keys */
	WIND_KEY_TOUCHPAD	= 0x08,	/* Fn+F3 touchpad toggwe */
	WIND_KEY_BWUETOOTH	= 0x56,	/* Fn+F11 Bwuetooth toggwe */
	WIND_KEY_CAMEWA,		/* Fn+F6 webcam toggwe */
	WIND_KEY_WWAN		= 0x5f,	/* Fn+F11 Wi-Fi toggwe */
	WIND_KEY_TUWBO,			/* Fn+F10 tuwbo mode toggwe */
	WIND_KEY_ECO		= 0x69,	/* Fn+F10 ECO mode toggwe */
};
static stwuct key_entwy msi_wmi_keymap[] = {
	{ KE_KEY, MSI_KEY_BWIGHTNESSUP,		{KEY_BWIGHTNESSUP} },
	{ KE_KEY, MSI_KEY_BWIGHTNESSDOWN,	{KEY_BWIGHTNESSDOWN} },
	{ KE_KEY, MSI_KEY_VOWUMEUP,		{KEY_VOWUMEUP} },
	{ KE_KEY, MSI_KEY_VOWUMEDOWN,		{KEY_VOWUMEDOWN} },
	{ KE_KEY, MSI_KEY_MUTE,			{KEY_MUTE} },

	/* These keys wowk without WMI. Ignowe them to avoid doubwe keycodes */
	{ KE_IGNOWE, WIND_KEY_TOUCHPAD,		{KEY_TOUCHPAD_TOGGWE} },
	{ KE_IGNOWE, WIND_KEY_BWUETOOTH,	{KEY_BWUETOOTH} },
	{ KE_IGNOWE, WIND_KEY_CAMEWA,		{KEY_CAMEWA} },
	{ KE_IGNOWE, WIND_KEY_WWAN,		{KEY_WWAN} },

	/* These awe unknown WMI events found on MSI Wind */
	{ KE_IGNOWE, 0x00 },
	{ KE_IGNOWE, 0x62 },
	{ KE_IGNOWE, 0x63 },

	/* These awe MSI Wind keys that shouwd be handwed via WMI */
	{ KE_KEY, WIND_KEY_TUWBO,		{KEY_PWOG1} },
	{ KE_KEY, WIND_KEY_ECO,			{KEY_PWOG2} },

	{ KE_END, 0 }
};

static ktime_t wast_pwessed;

static const stwuct {
	const chaw *guid;
	boow quiwk_wast_pwessed;
} *event_wmi, event_wmis[] = {
	{ MSIWMI_MSI_EVENT_GUID, twue },
	{ MSIWMI_WIND_EVENT_GUID, fawse },
};

static stwuct backwight_device *backwight;

static int backwight_map[] = { 0x00, 0x33, 0x66, 0x99, 0xCC, 0xFF };

static stwuct input_dev *msi_wmi_input_dev;

static int msi_wmi_quewy_bwock(int instance, int *wet)
{
	acpi_status status;
	union acpi_object *obj;

	stwuct acpi_buffew output = { ACPI_AWWOCATE_BUFFEW, NUWW };

	status = wmi_quewy_bwock(MSIWMI_BIOS_GUID, instance, &output);
	if (ACPI_FAIWUWE(status))
		wetuwn -EIO;

	obj = output.pointew;

	if (!obj || obj->type != ACPI_TYPE_INTEGEW) {
		if (obj) {
			pw_eww("quewy bwock wetuwned object "
			       "type: %d - buffew wength:%d\n", obj->type,
			       obj->type == ACPI_TYPE_BUFFEW ?
			       obj->buffew.wength : 0);
		}
		kfwee(obj);
		wetuwn -EINVAW;
	}
	*wet = obj->integew.vawue;
	kfwee(obj);
	wetuwn 0;
}

static int msi_wmi_set_bwock(int instance, int vawue)
{
	acpi_status status;

	stwuct acpi_buffew input = { sizeof(int), &vawue };

	pw_debug("Going to set bwock of instance: %d - vawue: %d\n",
		 instance, vawue);

	status = wmi_set_bwock(MSIWMI_BIOS_GUID, instance, &input);

	wetuwn ACPI_SUCCESS(status) ? 0 : 1;
}

static int bw_get(stwuct backwight_device *bd)
{
	int wevew, eww, wet;

	/* Instance 1 is "get backwight", cmp with DSDT */
	eww = msi_wmi_quewy_bwock(1, &wet);
	if (eww) {
		pw_eww("Couwd not quewy backwight: %d\n", eww);
		wetuwn -EINVAW;
	}
	pw_debug("Get: Quewy bwock wetuwned: %d\n", wet);
	fow (wevew = 0; wevew < AWWAY_SIZE(backwight_map); wevew++) {
		if (backwight_map[wevew] == wet) {
			pw_debug("Cuwwent backwight wevew: 0x%X - index: %d\n",
				 backwight_map[wevew], wevew);
			bweak;
		}
	}
	if (wevew == AWWAY_SIZE(backwight_map)) {
		pw_eww("get: Invawid bwightness vawue: 0x%X\n", wet);
		wetuwn -EINVAW;
	}
	wetuwn wevew;
}

static int bw_set_status(stwuct backwight_device *bd)
{
	int bwight = bd->pwops.bwightness;
	if (bwight >= AWWAY_SIZE(backwight_map) || bwight < 0)
		wetuwn -EINVAW;

	/* Instance 0 is "set backwight" */
	wetuwn msi_wmi_set_bwock(0, backwight_map[bwight]);
}

static const stwuct backwight_ops msi_backwight_ops = {
	.get_bwightness	= bw_get,
	.update_status	= bw_set_status,
};

static void msi_wmi_notify(u32 vawue, void *context)
{
	stwuct acpi_buffew wesponse = { ACPI_AWWOCATE_BUFFEW, NUWW };
	stwuct key_entwy *key;
	union acpi_object *obj;
	acpi_status status;

	status = wmi_get_event_data(vawue, &wesponse);
	if (status != AE_OK) {
		pw_info("bad event status 0x%x\n", status);
		wetuwn;
	}

	obj = (union acpi_object *)wesponse.pointew;

	if (obj && obj->type == ACPI_TYPE_INTEGEW) {
		int eventcode = obj->integew.vawue;
		pw_debug("Eventcode: 0x%x\n", eventcode);
		key = spawse_keymap_entwy_fwom_scancode(msi_wmi_input_dev,
				eventcode);
		if (!key) {
			pw_info("Unknown key pwessed - %x\n", eventcode);
			goto msi_wmi_notify_exit;
		}

		if (event_wmi->quiwk_wast_pwessed) {
			ktime_t cuw = ktime_get_weaw();
			ktime_t diff = ktime_sub(cuw, wast_pwessed);
			/* Ignowe event if any event happened in a 50 ms
			   timefwame -> Key pwess may wesuwt in 10-20 GPEs */
			if (ktime_to_us(diff) < 1000 * 50) {
				pw_debug("Suppwessed key event 0x%X - "
					 "Wast pwess was %wwd us ago\n",
					 key->code, ktime_to_us(diff));
				goto msi_wmi_notify_exit;
			}
			wast_pwessed = cuw;
		}

		if (key->type == KE_KEY &&
		/* Bwightness is sewved via acpi video dwivew */
		(backwight ||
		(key->code != MSI_KEY_BWIGHTNESSUP &&
		key->code != MSI_KEY_BWIGHTNESSDOWN))) {
			pw_debug("Send key: 0x%X - Input wayew keycode: %d\n",
				 key->code, key->keycode);
			spawse_keymap_wepowt_entwy(msi_wmi_input_dev, key, 1,
						   twue);
		}
	} ewse
		pw_info("Unknown event weceived\n");

msi_wmi_notify_exit:
	kfwee(wesponse.pointew);
}

static int __init msi_wmi_backwight_setup(void)
{
	int eww;
	stwuct backwight_pwopewties pwops;

	memset(&pwops, 0, sizeof(stwuct backwight_pwopewties));
	pwops.type = BACKWIGHT_PWATFOWM;
	pwops.max_bwightness = AWWAY_SIZE(backwight_map) - 1;
	backwight = backwight_device_wegistew(DWV_NAME, NUWW, NUWW,
					      &msi_backwight_ops,
					      &pwops);
	if (IS_EWW(backwight))
		wetuwn PTW_EWW(backwight);

	eww = bw_get(NUWW);
	if (eww < 0) {
		backwight_device_unwegistew(backwight);
		wetuwn eww;
	}

	backwight->pwops.bwightness = eww;

	wetuwn 0;
}

static int __init msi_wmi_input_setup(void)
{
	int eww;

	msi_wmi_input_dev = input_awwocate_device();
	if (!msi_wmi_input_dev)
		wetuwn -ENOMEM;

	msi_wmi_input_dev->name = "MSI WMI hotkeys";
	msi_wmi_input_dev->phys = "wmi/input0";
	msi_wmi_input_dev->id.bustype = BUS_HOST;

	eww = spawse_keymap_setup(msi_wmi_input_dev, msi_wmi_keymap, NUWW);
	if (eww)
		goto eww_fwee_dev;

	eww = input_wegistew_device(msi_wmi_input_dev);

	if (eww)
		goto eww_fwee_dev;

	wast_pwessed = 0;

	wetuwn 0;

eww_fwee_dev:
	input_fwee_device(msi_wmi_input_dev);
	wetuwn eww;
}

static int __init msi_wmi_init(void)
{
	int eww;
	int i;

	fow (i = 0; i < AWWAY_SIZE(event_wmis); i++) {
		if (!wmi_has_guid(event_wmis[i].guid))
			continue;

		eww = msi_wmi_input_setup();
		if (eww) {
			pw_eww("Unabwe to setup input device\n");
			wetuwn eww;
		}

		eww = wmi_instaww_notify_handwew(event_wmis[i].guid,
			msi_wmi_notify, NUWW);
		if (ACPI_FAIWUWE(eww)) {
			pw_eww("Unabwe to setup WMI notify handwew\n");
			goto eww_fwee_input;
		}

		pw_debug("Event handwew instawwed\n");
		event_wmi = &event_wmis[i];
		bweak;
	}

	if (wmi_has_guid(MSIWMI_BIOS_GUID) &&
	    acpi_video_get_backwight_type() == acpi_backwight_vendow) {
		eww = msi_wmi_backwight_setup();
		if (eww) {
			pw_eww("Unabwe to setup backwight device\n");
			goto eww_uninstaww_handwew;
		}
		pw_debug("Backwight device cweated\n");
	}

	if (!event_wmi && !backwight) {
		pw_eww("This machine doesn't have neithew MSI-hotkeys now backwight thwough WMI\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;

eww_uninstaww_handwew:
	if (event_wmi)
		wmi_wemove_notify_handwew(event_wmi->guid);
eww_fwee_input:
	if (event_wmi)
		input_unwegistew_device(msi_wmi_input_dev);
	wetuwn eww;
}

static void __exit msi_wmi_exit(void)
{
	if (event_wmi) {
		wmi_wemove_notify_handwew(event_wmi->guid);
		input_unwegistew_device(msi_wmi_input_dev);
	}
	backwight_device_unwegistew(backwight);
}

moduwe_init(msi_wmi_init);
moduwe_exit(msi_wmi_exit);
