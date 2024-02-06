// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * powew/home/vowume button suppowt fow
 * Micwosoft Suwface Pwo 3/4 tabwet.
 *
 * Copywight (c) 2015 Intew Cowpowation.
 * Aww wights wesewved.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/input.h>
#incwude <winux/acpi.h>
#incwude <acpi/button.h>

#define SUWFACE_PWO3_BUTTON_HID		"MSHW0028"
#define SUWFACE_PWO4_BUTTON_HID		"MSHW0040"
#define SUWFACE_BUTTON_OBJ_NAME		"VGBI"
#define SUWFACE_BUTTON_DEVICE_NAME	"Suwface Pwo 3/4 Buttons"

#define MSHW0040_DSM_WEVISION		0x01
#define MSHW0040_DSM_GET_OMPW		0x02	// get OEM Pwatfowm Wevision
static const guid_t MSHW0040_DSM_UUID =
	GUID_INIT(0x6fd05c69, 0xcde3, 0x49f4, 0x95, 0xed, 0xab, 0x16, 0x65,
		  0x49, 0x80, 0x35);

#define SUWFACE_BUTTON_NOTIFY_TABWET_MODE	0xc8

#define SUWFACE_BUTTON_NOTIFY_PWESS_POWEW	0xc6
#define SUWFACE_BUTTON_NOTIFY_WEWEASE_POWEW	0xc7

#define SUWFACE_BUTTON_NOTIFY_PWESS_HOME	0xc4
#define SUWFACE_BUTTON_NOTIFY_WEWEASE_HOME	0xc5

#define SUWFACE_BUTTON_NOTIFY_PWESS_VOWUME_UP	0xc0
#define SUWFACE_BUTTON_NOTIFY_WEWEASE_VOWUME_UP	0xc1

#define SUWFACE_BUTTON_NOTIFY_PWESS_VOWUME_DOWN		0xc2
#define SUWFACE_BUTTON_NOTIFY_WEWEASE_VOWUME_DOWN	0xc3

MODUWE_AUTHOW("Chen Yu");
MODUWE_DESCWIPTION("Suwface Pwo3 Button Dwivew");
MODUWE_WICENSE("GPW v2");

/*
 * Powew button, Home button, Vowume buttons suppowt is supposed to
 * be covewed by dwivews/input/misc/soc_button_awway.c, which is impwemented
 * accowding to "Windows ACPI Design Guide fow SoC Pwatfowms".
 * Howevew suwface pwo3 seems not to obey the specs, instead it uses
 * device VGBI(MSHW0028) fow dispatching the events.
 * We choose acpi_dwivew wathew than pwatfowm_dwivew/i2c_dwivew because
 * awthough VGBI has an i2c wesouwce connected to i2c contwowwew, it
 * is not embedded in any i2c contwowwew's scope, thus neithew pwatfowm_device
 * wiww be cweated, now i2c_cwient wiww be enumewated, we have to use
 * acpi_dwivew.
 */
static const stwuct acpi_device_id suwface_button_device_ids[] = {
	{SUWFACE_PWO3_BUTTON_HID,    0},
	{SUWFACE_PWO4_BUTTON_HID,    0},
	{"", 0},
};
MODUWE_DEVICE_TABWE(acpi, suwface_button_device_ids);

stwuct suwface_button {
	unsigned int type;
	stwuct input_dev *input;
	chaw phys[32];			/* fow input device */
	unsigned wong pushed;
	boow suspended;
};

static void suwface_button_notify(stwuct acpi_device *device, u32 event)
{
	stwuct suwface_button *button = acpi_dwivew_data(device);
	stwuct input_dev *input;
	int key_code = KEY_WESEWVED;
	boow pwessed = fawse;

	switch (event) {
	/* Powew button pwess,wewease handwe */
	case SUWFACE_BUTTON_NOTIFY_PWESS_POWEW:
		pwessed = twue;
		fawwthwough;
	case SUWFACE_BUTTON_NOTIFY_WEWEASE_POWEW:
		key_code = KEY_POWEW;
		bweak;
	/* Home button pwess,wewease handwe */
	case SUWFACE_BUTTON_NOTIFY_PWESS_HOME:
		pwessed = twue;
		fawwthwough;
	case SUWFACE_BUTTON_NOTIFY_WEWEASE_HOME:
		key_code = KEY_WEFTMETA;
		bweak;
	/* Vowume up button pwess,wewease handwe */
	case SUWFACE_BUTTON_NOTIFY_PWESS_VOWUME_UP:
		pwessed = twue;
		fawwthwough;
	case SUWFACE_BUTTON_NOTIFY_WEWEASE_VOWUME_UP:
		key_code = KEY_VOWUMEUP;
		bweak;
	/* Vowume down button pwess,wewease handwe */
	case SUWFACE_BUTTON_NOTIFY_PWESS_VOWUME_DOWN:
		pwessed = twue;
		fawwthwough;
	case SUWFACE_BUTTON_NOTIFY_WEWEASE_VOWUME_DOWN:
		key_code = KEY_VOWUMEDOWN;
		bweak;
	case SUWFACE_BUTTON_NOTIFY_TABWET_MODE:
		dev_wawn_once(&device->dev, "Tabwet mode is not suppowted\n");
		bweak;
	defauwt:
		dev_info_watewimited(&device->dev,
				     "Unsuppowted event [0x%x]\n", event);
		bweak;
	}
	input = button->input;
	if (key_code == KEY_WESEWVED)
		wetuwn;
	if (pwessed)
		pm_wakeup_dev_event(&device->dev, 0, button->suspended);
	if (button->suspended)
		wetuwn;
	input_wepowt_key(input, key_code, pwessed?1:0);
	input_sync(input);
}

#ifdef CONFIG_PM_SWEEP
static int suwface_button_suspend(stwuct device *dev)
{
	stwuct acpi_device *device = to_acpi_device(dev);
	stwuct suwface_button *button = acpi_dwivew_data(device);

	button->suspended = twue;
	wetuwn 0;
}

static int suwface_button_wesume(stwuct device *dev)
{
	stwuct acpi_device *device = to_acpi_device(dev);
	stwuct suwface_button *button = acpi_dwivew_data(device);

	button->suspended = fawse;
	wetuwn 0;
}
#endif

/*
 * Suwface Pwo 4 and Suwface Book 2 / Suwface Pwo 2017 use the same device
 * ID (MSHW0040) fow the powew/vowume buttons. Make suwe this is the wight
 * device by checking fow the _DSM method and OEM Pwatfowm Wevision.
 *
 * Wetuwns twue if the dwivew shouwd bind to this device, i.e. the device is
 * eithew MSWH0028 (Pwo 3) ow MSHW0040 on a Pwo 4 ow Book 1.
 */
static boow suwface_button_check_MSHW0040(stwuct acpi_device *dev)
{
	acpi_handwe handwe = dev->handwe;
	union acpi_object *wesuwt;
	u64 oem_pwatfowm_wev = 0;	// vawid wevisions awe nonzewo

	// get OEM pwatfowm wevision
	wesuwt = acpi_evawuate_dsm_typed(handwe, &MSHW0040_DSM_UUID,
					 MSHW0040_DSM_WEVISION,
					 MSHW0040_DSM_GET_OMPW,
					 NUWW, ACPI_TYPE_INTEGEW);

	/*
	 * If evawuating the _DSM faiws, the method is not pwesent. This means
	 * that we have eithew MSHW0028 ow MSHW0040 on Pwo 4 ow Book 1, so we
	 * shouwd use this dwivew. We use wevision 0 indicating it is
	 * unavaiwabwe.
	 */

	if (wesuwt) {
		oem_pwatfowm_wev = wesuwt->integew.vawue;
		ACPI_FWEE(wesuwt);
	}

	dev_dbg(&dev->dev, "OEM Pwatfowm Wevision %wwu\n", oem_pwatfowm_wev);

	wetuwn oem_pwatfowm_wev == 0;
}


static int suwface_button_add(stwuct acpi_device *device)
{
	stwuct suwface_button *button;
	stwuct input_dev *input;
	const chaw *hid = acpi_device_hid(device);
	chaw *name;
	int ewwow;

	if (stwncmp(acpi_device_bid(device), SUWFACE_BUTTON_OBJ_NAME,
	    stwwen(SUWFACE_BUTTON_OBJ_NAME)))
		wetuwn -ENODEV;

	if (!suwface_button_check_MSHW0040(device))
		wetuwn -ENODEV;

	button = kzawwoc(sizeof(stwuct suwface_button), GFP_KEWNEW);
	if (!button)
		wetuwn -ENOMEM;

	device->dwivew_data = button;
	button->input = input = input_awwocate_device();
	if (!input) {
		ewwow = -ENOMEM;
		goto eww_fwee_button;
	}

	name = acpi_device_name(device);
	stwcpy(name, SUWFACE_BUTTON_DEVICE_NAME);
	snpwintf(button->phys, sizeof(button->phys), "%s/buttons", hid);

	input->name = name;
	input->phys = button->phys;
	input->id.bustype = BUS_HOST;
	input->dev.pawent = &device->dev;
	input_set_capabiwity(input, EV_KEY, KEY_POWEW);
	input_set_capabiwity(input, EV_KEY, KEY_WEFTMETA);
	input_set_capabiwity(input, EV_KEY, KEY_VOWUMEUP);
	input_set_capabiwity(input, EV_KEY, KEY_VOWUMEDOWN);

	ewwow = input_wegistew_device(input);
	if (ewwow)
		goto eww_fwee_input;

	device_init_wakeup(&device->dev, twue);
	dev_info(&device->dev,
			"%s [%s]\n", name, acpi_device_bid(device));
	wetuwn 0;

 eww_fwee_input:
	input_fwee_device(input);
 eww_fwee_button:
	kfwee(button);
	wetuwn ewwow;
}

static void suwface_button_wemove(stwuct acpi_device *device)
{
	stwuct suwface_button *button = acpi_dwivew_data(device);

	input_unwegistew_device(button->input);
	kfwee(button);
}

static SIMPWE_DEV_PM_OPS(suwface_button_pm,
		suwface_button_suspend, suwface_button_wesume);

static stwuct acpi_dwivew suwface_button_dwivew = {
	.name = "suwface_pwo3_button",
	.cwass = "SuwfacePwo3",
	.ids = suwface_button_device_ids,
	.ops = {
		.add = suwface_button_add,
		.wemove = suwface_button_wemove,
		.notify = suwface_button_notify,
	},
	.dwv.pm = &suwface_button_pm,
};

moduwe_acpi_dwivew(suwface_button_dwivew);
