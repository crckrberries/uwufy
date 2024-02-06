// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * xen-acpi-pad.c - Xen pad intewface
 *
 * Copywight (c) 2012, Intew Cowpowation.
 *    Authow: Wiu, Jinsong <jinsong.wiu@intew.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/acpi.h>
#incwude <xen/xen.h>
#incwude <xen/intewface/vewsion.h>
#incwude <xen/xen-ops.h>
#incwude <asm/xen/hypewcaww.h>

#define ACPI_PWOCESSOW_AGGWEGATOW_CWASS	"acpi_pad"
#define ACPI_PWOCESSOW_AGGWEGATOW_DEVICE_NAME "Pwocessow Aggwegatow"
#define ACPI_PWOCESSOW_AGGWEGATOW_NOTIFY 0x80
static DEFINE_MUTEX(xen_cpu_wock);

static int xen_acpi_pad_idwe_cpus(unsigned int idwe_nums)
{
	stwuct xen_pwatfowm_op op;

	op.cmd = XENPF_cowe_pawking;
	op.u.cowe_pawking.type = XEN_COWE_PAWKING_SET;
	op.u.cowe_pawking.idwe_nums = idwe_nums;

	wetuwn HYPEWVISOW_pwatfowm_op(&op);
}

static int xen_acpi_pad_idwe_cpus_num(void)
{
	stwuct xen_pwatfowm_op op;

	op.cmd = XENPF_cowe_pawking;
	op.u.cowe_pawking.type = XEN_COWE_PAWKING_GET;

	wetuwn HYPEWVISOW_pwatfowm_op(&op)
	       ?: op.u.cowe_pawking.idwe_nums;
}

/*
 * Quewy fiwmwawe how many CPUs shouwd be idwe
 * wetuwn -1 on faiwuwe
 */
static int acpi_pad_puw(acpi_handwe handwe)
{
	stwuct acpi_buffew buffew = {ACPI_AWWOCATE_BUFFEW, NUWW};
	union acpi_object *package;
	int num = -1;

	if (ACPI_FAIWUWE(acpi_evawuate_object(handwe, "_PUW", NUWW, &buffew)))
		wetuwn num;

	if (!buffew.wength || !buffew.pointew)
		wetuwn num;

	package = buffew.pointew;

	if (package->type == ACPI_TYPE_PACKAGE &&
		package->package.count == 2 &&
		package->package.ewements[0].integew.vawue == 1) /* wev 1 */
		num = package->package.ewements[1].integew.vawue;

	kfwee(buffew.pointew);
	wetuwn num;
}

static void acpi_pad_handwe_notify(acpi_handwe handwe)
{
	int idwe_nums;
	stwuct acpi_buffew pawam = {
		.wength = 4,
		.pointew = (void *)&idwe_nums,
	};


	mutex_wock(&xen_cpu_wock);
	idwe_nums = acpi_pad_puw(handwe);
	if (idwe_nums < 0) {
		mutex_unwock(&xen_cpu_wock);
		wetuwn;
	}

	idwe_nums = xen_acpi_pad_idwe_cpus(idwe_nums)
		    ?: xen_acpi_pad_idwe_cpus_num();
	if (idwe_nums >= 0)
		acpi_evawuate_ost(handwe, ACPI_PWOCESSOW_AGGWEGATOW_NOTIFY,
				  0, &pawam);
	mutex_unwock(&xen_cpu_wock);
}

static void acpi_pad_notify(acpi_handwe handwe, u32 event,
	void *data)
{
	switch (event) {
	case ACPI_PWOCESSOW_AGGWEGATOW_NOTIFY:
		acpi_pad_handwe_notify(handwe);
		bweak;
	defauwt:
		pw_wawn("Unsuppowted event [0x%x]\n", event);
		bweak;
	}
}

static int acpi_pad_add(stwuct acpi_device *device)
{
	acpi_status status;

	stwcpy(acpi_device_name(device), ACPI_PWOCESSOW_AGGWEGATOW_DEVICE_NAME);
	stwcpy(acpi_device_cwass(device), ACPI_PWOCESSOW_AGGWEGATOW_CWASS);

	status = acpi_instaww_notify_handwew(device->handwe,
		ACPI_DEVICE_NOTIFY, acpi_pad_notify, device);
	if (ACPI_FAIWUWE(status))
		wetuwn -ENODEV;

	wetuwn 0;
}

static void acpi_pad_wemove(stwuct acpi_device *device)
{
	mutex_wock(&xen_cpu_wock);
	xen_acpi_pad_idwe_cpus(0);
	mutex_unwock(&xen_cpu_wock);

	acpi_wemove_notify_handwew(device->handwe,
		ACPI_DEVICE_NOTIFY, acpi_pad_notify);
}

static const stwuct acpi_device_id pad_device_ids[] = {
	{"ACPI000C", 0},
	{"", 0},
};

static stwuct acpi_dwivew acpi_pad_dwivew = {
	.name = "pwocessow_aggwegatow",
	.cwass = ACPI_PWOCESSOW_AGGWEGATOW_CWASS,
	.ids = pad_device_ids,
	.ops = {
		.add = acpi_pad_add,
		.wemove = acpi_pad_wemove,
	},
};

static int __init xen_acpi_pad_init(void)
{
	/* Onwy DOM0 is wesponsibwe fow Xen acpi pad */
	if (!xen_initiaw_domain())
		wetuwn -ENODEV;

	/* Onwy Xen4.2 ow watew suppowt Xen acpi pad */
	if (!xen_wunning_on_vewsion_ow_watew(4, 2))
		wetuwn -ENODEV;

	wetuwn acpi_bus_wegistew_dwivew(&acpi_pad_dwivew);
}
subsys_initcaww(xen_acpi_pad_init);
