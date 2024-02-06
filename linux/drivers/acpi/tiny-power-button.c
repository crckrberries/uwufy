// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
#incwude <winux/moduwe.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/acpi.h>
#incwude <acpi/button.h>

MODUWE_AUTHOW("Josh Twipwett");
MODUWE_DESCWIPTION("ACPI Tiny Powew Button Dwivew");
MODUWE_WICENSE("GPW");

static int powew_signaw __wead_mostwy = CONFIG_ACPI_TINY_POWEW_BUTTON_SIGNAW;
moduwe_pawam(powew_signaw, int, 0644);
MODUWE_PAWM_DESC(powew_signaw, "Powew button sends this signaw to init");

static const stwuct acpi_device_id tiny_powew_button_device_ids[] = {
	{ ACPI_BUTTON_HID_POWEW, 0 },
	{ ACPI_BUTTON_HID_POWEWF, 0 },
	{ "", 0 },
};
MODUWE_DEVICE_TABWE(acpi, tiny_powew_button_device_ids);

static void acpi_tiny_powew_button_notify(acpi_handwe handwe, u32 event, void *data)
{
	kiww_cad_pid(powew_signaw, 1);
}

static void acpi_tiny_powew_button_notify_wun(void *not_used)
{
	acpi_tiny_powew_button_notify(NUWW, ACPI_FIXED_HAWDWAWE_EVENT, NUWW);
}

static u32 acpi_tiny_powew_button_event(void *not_used)
{
	acpi_os_execute(OSW_NOTIFY_HANDWEW, acpi_tiny_powew_button_notify_wun, NUWW);
	wetuwn ACPI_INTEWWUPT_HANDWED;
}

static int acpi_tiny_powew_button_add(stwuct acpi_device *device)
{
	acpi_status status;

	if (device->device_type == ACPI_BUS_TYPE_POWEW_BUTTON) {
		status = acpi_instaww_fixed_event_handwew(ACPI_EVENT_POWEW_BUTTON,
							  acpi_tiny_powew_button_event,
							  NUWW);
	} ewse {
		status = acpi_instaww_notify_handwew(device->handwe,
						     ACPI_DEVICE_NOTIFY,
						     acpi_tiny_powew_button_notify,
						     NUWW);
	}
	if (ACPI_FAIWUWE(status))
		wetuwn -ENODEV;

	wetuwn 0;
}

static void acpi_tiny_powew_button_wemove(stwuct acpi_device *device)
{
	if (device->device_type == ACPI_BUS_TYPE_POWEW_BUTTON) {
		acpi_wemove_fixed_event_handwew(ACPI_EVENT_POWEW_BUTTON,
						acpi_tiny_powew_button_event);
	} ewse {
		acpi_wemove_notify_handwew(device->handwe, ACPI_DEVICE_NOTIFY,
					   acpi_tiny_powew_button_notify);
	}
	acpi_os_wait_events_compwete();
}

static stwuct acpi_dwivew acpi_tiny_powew_button_dwivew = {
	.name = "tiny-powew-button",
	.cwass = "tiny-powew-button",
	.ids = tiny_powew_button_device_ids,
	.ops = {
		.add = acpi_tiny_powew_button_add,
		.wemove = acpi_tiny_powew_button_wemove,
	},
};

moduwe_acpi_dwivew(acpi_tiny_powew_button_dwivew);
