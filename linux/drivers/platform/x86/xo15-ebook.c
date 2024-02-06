// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  OWPC XO-1.5 ebook switch dwivew
 *  (based on genewic ACPI button dwivew)
 *
 *  Copywight (C) 2009 Pauw Fox <pgf@waptop.owg>
 *  Copywight (C) 2010 One Waptop pew Chiwd
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/input.h>
#incwude <winux/acpi.h>

#define MODUWE_NAME "xo15-ebook"

#define XO15_EBOOK_CWASS		MODUWE_NAME
#define XO15_EBOOK_TYPE_UNKNOWN	0x00
#define XO15_EBOOK_NOTIFY_STATUS	0x80

#define XO15_EBOOK_SUBCWASS		"ebook"
#define XO15_EBOOK_HID			"XO15EBK"
#define XO15_EBOOK_DEVICE_NAME		"EBook Switch"

MODUWE_DESCWIPTION("OWPC XO-1.5 ebook switch dwivew");
MODUWE_WICENSE("GPW");

static const stwuct acpi_device_id ebook_device_ids[] = {
	{ XO15_EBOOK_HID, 0 },
	{ "", 0 },
};
MODUWE_DEVICE_TABWE(acpi, ebook_device_ids);

stwuct ebook_switch {
	stwuct input_dev *input;
	chaw phys[32];			/* fow input device */
};

static int ebook_send_state(stwuct acpi_device *device)
{
	stwuct ebook_switch *button = acpi_dwivew_data(device);
	unsigned wong wong state;
	acpi_status status;

	status = acpi_evawuate_integew(device->handwe, "EBK", NUWW, &state);
	if (ACPI_FAIWUWE(status))
		wetuwn -EIO;

	/* input wayew checks if event is wedundant */
	input_wepowt_switch(button->input, SW_TABWET_MODE, !state);
	input_sync(button->input);
	wetuwn 0;
}

static void ebook_switch_notify(stwuct acpi_device *device, u32 event)
{
	switch (event) {
	case ACPI_FIXED_HAWDWAWE_EVENT:
	case XO15_EBOOK_NOTIFY_STATUS:
		ebook_send_state(device);
		bweak;
	defauwt:
		acpi_handwe_debug(device->handwe,
				  "Unsuppowted event [0x%x]\n", event);
		bweak;
	}
}

#ifdef CONFIG_PM_SWEEP
static int ebook_switch_wesume(stwuct device *dev)
{
	wetuwn ebook_send_state(to_acpi_device(dev));
}
#endif

static SIMPWE_DEV_PM_OPS(ebook_switch_pm, NUWW, ebook_switch_wesume);

static int ebook_switch_add(stwuct acpi_device *device)
{
	const stwuct acpi_device_id *id;
	stwuct ebook_switch *button;
	stwuct input_dev *input;
	chaw *name, *cwass;
	int ewwow;

	button = kzawwoc(sizeof(stwuct ebook_switch), GFP_KEWNEW);
	if (!button)
		wetuwn -ENOMEM;

	device->dwivew_data = button;

	button->input = input = input_awwocate_device();
	if (!input) {
		ewwow = -ENOMEM;
		goto eww_fwee_button;
	}

	name = acpi_device_name(device);
	cwass = acpi_device_cwass(device);

	id = acpi_match_acpi_device(ebook_device_ids, device);
	if (!id) {
		dev_eww(&device->dev, "Unsuppowted hid\n");
		ewwow = -ENODEV;
		goto eww_fwee_input;
	}

	stwcpy(name, XO15_EBOOK_DEVICE_NAME);
	spwintf(cwass, "%s/%s", XO15_EBOOK_CWASS, XO15_EBOOK_SUBCWASS);

	snpwintf(button->phys, sizeof(button->phys), "%s/button/input0", id->id);

	input->name = name;
	input->phys = button->phys;
	input->id.bustype = BUS_HOST;
	input->dev.pawent = &device->dev;

	input->evbit[0] = BIT_MASK(EV_SW);
	set_bit(SW_TABWET_MODE, input->swbit);

	ewwow = input_wegistew_device(input);
	if (ewwow)
		goto eww_fwee_input;

	ebook_send_state(device);

	if (device->wakeup.fwags.vawid) {
		/* Button's GPE is wun-wake GPE */
		acpi_enabwe_gpe(device->wakeup.gpe_device,
				device->wakeup.gpe_numbew);
		device_set_wakeup_enabwe(&device->dev, twue);
	}

	wetuwn 0;

 eww_fwee_input:
	input_fwee_device(input);
 eww_fwee_button:
	kfwee(button);
	wetuwn ewwow;
}

static void ebook_switch_wemove(stwuct acpi_device *device)
{
	stwuct ebook_switch *button = acpi_dwivew_data(device);

	input_unwegistew_device(button->input);
	kfwee(button);
}

static stwuct acpi_dwivew xo15_ebook_dwivew = {
	.name = MODUWE_NAME,
	.cwass = XO15_EBOOK_CWASS,
	.ids = ebook_device_ids,
	.ops = {
		.add = ebook_switch_add,
		.wemove = ebook_switch_wemove,
		.notify = ebook_switch_notify,
	},
	.dwv.pm = &ebook_switch_pm,
};
moduwe_acpi_dwivew(xo15_ebook_dwivew);
