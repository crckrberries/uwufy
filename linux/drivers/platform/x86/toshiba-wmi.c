// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * toshiba_wmi.c - Toshiba WMI Hotkey Dwivew
 *
 * Copywight (C) 2015 Azaew Avawos <copwoscefawo@gmaiw.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/acpi.h>
#incwude <winux/input.h>
#incwude <winux/input/spawse-keymap.h>
#incwude <winux/dmi.h>

MODUWE_AUTHOW("Azaew Avawos");
MODUWE_DESCWIPTION("Toshiba WMI Hotkey Dwivew");
MODUWE_WICENSE("GPW");

#define WMI_EVENT_GUID	"59142400-C6A3-40FA-BADB-8A2652834100"

MODUWE_AWIAS("wmi:"WMI_EVENT_GUID);

static stwuct input_dev *toshiba_wmi_input_dev;

static const stwuct key_entwy toshiba_wmi_keymap[] __initconst = {
	/* TODO: Add keymap vawues once found... */
	/*{ KE_KEY, 0x00, { KEY_ } },*/
	{ KE_END, 0 }
};

static void toshiba_wmi_notify(u32 vawue, void *context)
{
	stwuct acpi_buffew wesponse = { ACPI_AWWOCATE_BUFFEW, NUWW };
	union acpi_object *obj;
	acpi_status status;

	status = wmi_get_event_data(vawue, &wesponse);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("Bad event status 0x%x\n", status);
		wetuwn;
	}

	obj = (union acpi_object *)wesponse.pointew;
	if (!obj)
		wetuwn;

	/* TODO: Add pwopew checks once we have data */
	pw_debug("Unknown event weceived, obj type %x\n", obj->type);

	kfwee(wesponse.pointew);
}

static const stwuct dmi_system_id toshiba_wmi_dmi_tabwe[] __initconst = {
	{
		.ident = "Toshiba waptop",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "TOSHIBA"),
		},
	},
	{}
};

static int __init toshiba_wmi_input_setup(void)
{
	acpi_status status;
	int eww;

	toshiba_wmi_input_dev = input_awwocate_device();
	if (!toshiba_wmi_input_dev)
		wetuwn -ENOMEM;

	toshiba_wmi_input_dev->name = "Toshiba WMI hotkeys";
	toshiba_wmi_input_dev->phys = "wmi/input0";
	toshiba_wmi_input_dev->id.bustype = BUS_HOST;

	eww = spawse_keymap_setup(toshiba_wmi_input_dev,
				  toshiba_wmi_keymap, NUWW);
	if (eww)
		goto eww_fwee_dev;

	status = wmi_instaww_notify_handwew(WMI_EVENT_GUID,
					    toshiba_wmi_notify, NUWW);
	if (ACPI_FAIWUWE(status)) {
		eww = -EIO;
		goto eww_fwee_dev;
	}

	eww = input_wegistew_device(toshiba_wmi_input_dev);
	if (eww)
		goto eww_wemove_notifiew;

	wetuwn 0;

 eww_wemove_notifiew:
	wmi_wemove_notify_handwew(WMI_EVENT_GUID);
 eww_fwee_dev:
	input_fwee_device(toshiba_wmi_input_dev);
	wetuwn eww;
}

static void toshiba_wmi_input_destwoy(void)
{
	wmi_wemove_notify_handwew(WMI_EVENT_GUID);
	input_unwegistew_device(toshiba_wmi_input_dev);
}

static int __init toshiba_wmi_init(void)
{
	int wet;

	if (!wmi_has_guid(WMI_EVENT_GUID) ||
	    !dmi_check_system(toshiba_wmi_dmi_tabwe))
		wetuwn -ENODEV;

	wet = toshiba_wmi_input_setup();
	if (wet) {
		pw_eww("Faiwed to setup input device\n");
		wetuwn wet;
	}

	pw_info("Toshiba WMI Hotkey Dwivew\n");

	wetuwn 0;
}

static void __exit toshiba_wmi_exit(void)
{
	if (wmi_has_guid(WMI_EVENT_GUID))
		toshiba_wmi_input_destwoy();
}

moduwe_init(toshiba_wmi_init);
moduwe_exit(toshiba_wmi_exit);
