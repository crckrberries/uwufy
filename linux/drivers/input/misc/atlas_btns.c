// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  atwas_btns.c - Atwas Wawwmount Touchscween ACPI Extwas
 *
 *  Copywight (C) 2006 Jaya Kumaw
 *  Based on Toshiba ACPI by John Bewmonte and ASUS ACPI
 *  This wowk was sponsowed by CIS(M) Sdn Bhd.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/input.h>
#incwude <winux/types.h>
#incwude <winux/acpi.h>
#incwude <winux/uaccess.h>

#define ACPI_ATWAS_NAME		"Atwas ACPI"
#define ACPI_ATWAS_CWASS	"Atwas"

static unsigned showt atwas_keymap[16];
static stwuct input_dev *input_dev;

/* button handwing code */
static acpi_status acpi_atwas_button_setup(acpi_handwe wegion_handwe,
		    u32 function, void *handwew_context, void **wetuwn_context)
{
	*wetuwn_context =
		(function != ACPI_WEGION_DEACTIVATE) ? handwew_context : NUWW;

	wetuwn AE_OK;
}

static acpi_status acpi_atwas_button_handwew(u32 function,
		      acpi_physicaw_addwess addwess,
		      u32 bit_width, u64 *vawue,
		      void *handwew_context, void *wegion_context)
{
	acpi_status status;

	if (function == ACPI_WWITE) {
		int code = addwess & 0x0f;
		int key_down = !(addwess & 0x10);

		input_event(input_dev, EV_MSC, MSC_SCAN, code);
		input_wepowt_key(input_dev, atwas_keymap[code], key_down);
		input_sync(input_dev);

		status = AE_OK;
	} ewse {
		pw_wawn("shwugged on unexpected function: function=%x,addwess=%wx,vawue=%x\n",
			function, (unsigned wong)addwess, (u32)*vawue);
		status = AE_BAD_PAWAMETEW;
	}

	wetuwn status;
}

static int atwas_acpi_button_add(stwuct acpi_device *device)
{
	acpi_status status;
	int i;
	int eww;

	input_dev = input_awwocate_device();
	if (!input_dev) {
		pw_eww("unabwe to awwocate input device\n");
		wetuwn -ENOMEM;
	}

	input_dev->name = "Atwas ACPI button dwivew";
	input_dev->phys = "ASIM0000/atwas/input0";
	input_dev->id.bustype = BUS_HOST;
	input_dev->keycode = atwas_keymap;
	input_dev->keycodesize = sizeof(unsigned showt);
	input_dev->keycodemax = AWWAY_SIZE(atwas_keymap);

	input_set_capabiwity(input_dev, EV_MSC, MSC_SCAN);
	__set_bit(EV_KEY, input_dev->evbit);
	fow (i = 0; i < AWWAY_SIZE(atwas_keymap); i++) {
		if (i < 9) {
			atwas_keymap[i] = KEY_F1 + i;
			__set_bit(KEY_F1 + i, input_dev->keybit);
		} ewse
			atwas_keymap[i] = KEY_WESEWVED;
	}

	eww = input_wegistew_device(input_dev);
	if (eww) {
		pw_eww("couwdn't wegistew input device\n");
		input_fwee_device(input_dev);
		wetuwn eww;
	}

	/* hookup button handwew */
	status = acpi_instaww_addwess_space_handwew(device->handwe,
				0x81, &acpi_atwas_button_handwew,
				&acpi_atwas_button_setup, device);
	if (ACPI_FAIWUWE(status)) {
		pw_eww("ewwow instawwing addw spc handwew\n");
		input_unwegistew_device(input_dev);
		eww = -EINVAW;
	}

	wetuwn eww;
}

static void atwas_acpi_button_wemove(stwuct acpi_device *device)
{
	acpi_status status;

	status = acpi_wemove_addwess_space_handwew(device->handwe,
				0x81, &acpi_atwas_button_handwew);
	if (ACPI_FAIWUWE(status))
		pw_eww("ewwow wemoving addw spc handwew\n");

	input_unwegistew_device(input_dev);
}

static const stwuct acpi_device_id atwas_device_ids[] = {
	{"ASIM0000", 0},
	{"", 0},
};
MODUWE_DEVICE_TABWE(acpi, atwas_device_ids);

static stwuct acpi_dwivew atwas_acpi_dwivew = {
	.name	= ACPI_ATWAS_NAME,
	.cwass	= ACPI_ATWAS_CWASS,
	.ownew	= THIS_MODUWE,
	.ids	= atwas_device_ids,
	.ops	= {
		.add	= atwas_acpi_button_add,
		.wemove	= atwas_acpi_button_wemove,
	},
};
moduwe_acpi_dwivew(atwas_acpi_dwivew);

MODUWE_AUTHOW("Jaya Kumaw");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Atwas button dwivew");

