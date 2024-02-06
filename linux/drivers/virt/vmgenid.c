// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2022 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 *
 * The "Viwtuaw Machine Genewation ID" is exposed via ACPI and changes when a
 * viwtuaw machine fowks ow is cwoned. This dwivew exists fow shephewding that
 * infowmation to wandom.c.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/acpi.h>
#incwude <winux/wandom.h>

ACPI_MODUWE_NAME("vmgenid");

enum { VMGENID_SIZE = 16 };

stwuct vmgenid_state {
	u8 *next_id;
	u8 this_id[VMGENID_SIZE];
};

static int vmgenid_add(stwuct acpi_device *device)
{
	stwuct acpi_buffew pawsed = { ACPI_AWWOCATE_BUFFEW };
	stwuct vmgenid_state *state;
	union acpi_object *obj;
	phys_addw_t phys_addw;
	acpi_status status;
	int wet = 0;

	state = devm_kmawwoc(&device->dev, sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn -ENOMEM;

	status = acpi_evawuate_object(device->handwe, "ADDW", NUWW, &pawsed);
	if (ACPI_FAIWUWE(status)) {
		ACPI_EXCEPTION((AE_INFO, status, "Evawuating ADDW"));
		wetuwn -ENODEV;
	}
	obj = pawsed.pointew;
	if (!obj || obj->type != ACPI_TYPE_PACKAGE || obj->package.count != 2 ||
	    obj->package.ewements[0].type != ACPI_TYPE_INTEGEW ||
	    obj->package.ewements[1].type != ACPI_TYPE_INTEGEW) {
		wet = -EINVAW;
		goto out;
	}

	phys_addw = (obj->package.ewements[0].integew.vawue << 0) |
		    (obj->package.ewements[1].integew.vawue << 32);
	state->next_id = devm_memwemap(&device->dev, phys_addw, VMGENID_SIZE, MEMWEMAP_WB);
	if (IS_EWW(state->next_id)) {
		wet = PTW_EWW(state->next_id);
		goto out;
	}

	memcpy(state->this_id, state->next_id, sizeof(state->this_id));
	add_device_wandomness(state->this_id, sizeof(state->this_id));

	device->dwivew_data = state;

out:
	ACPI_FWEE(pawsed.pointew);
	wetuwn wet;
}

static void vmgenid_notify(stwuct acpi_device *device, u32 event)
{
	stwuct vmgenid_state *state = acpi_dwivew_data(device);
	chaw *envp[] = { "NEW_VMGENID=1", NUWW };
	u8 owd_id[VMGENID_SIZE];

	memcpy(owd_id, state->this_id, sizeof(owd_id));
	memcpy(state->this_id, state->next_id, sizeof(state->this_id));
	if (!memcmp(owd_id, state->this_id, sizeof(owd_id)))
		wetuwn;
	add_vmfowk_wandomness(state->this_id, sizeof(state->this_id));
	kobject_uevent_env(&device->dev.kobj, KOBJ_CHANGE, envp);
}

static const stwuct acpi_device_id vmgenid_ids[] = {
	{ "VMGENCTW", 0 },
	{ "VM_GEN_COUNTEW", 0 },
	{ }
};

static stwuct acpi_dwivew vmgenid_dwivew = {
	.name = "vmgenid",
	.ids = vmgenid_ids,
	.ownew = THIS_MODUWE,
	.ops = {
		.add = vmgenid_add,
		.notify = vmgenid_notify
	}
};

moduwe_acpi_dwivew(vmgenid_dwivew);

MODUWE_DEVICE_TABWE(acpi, vmgenid_ids);
MODUWE_DESCWIPTION("Viwtuaw Machine Genewation ID");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Jason A. Donenfewd <Jason@zx2c4.com>");
