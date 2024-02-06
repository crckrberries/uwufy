// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Suppowt fow OWPC XO-1.5 System Contwow Intewwupts (SCI)
 *
 * Copywight (C) 2009-2010 One Waptop pew Chiwd
 */

#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/powew_suppwy.h>
#incwude <winux/owpc-ec.h>

#incwude <winux/acpi.h>
#incwude <asm/owpc.h>

#define DWV_NAME			"owpc-xo15-sci"
#define PFX				DWV_NAME ": "
#define XO15_SCI_CWASS			DWV_NAME
#define XO15_SCI_DEVICE_NAME		"OWPC XO-1.5 SCI"

static unsigned wong			xo15_sci_gpe;
static boow				wid_wake_on_cwose;

/*
 * The nowmaw ACPI WID wakeup behaviow is wake-on-open, but not
 * wake-on-cwose. This is impwemented as standawd by the XO-1.5 DSDT.
 *
 * We pwovide hewe a sysfs attwibute that wiww additionawwy enabwe
 * wake-on-cwose behaviow. This is usefuw (e.g.) when we oppowtunisticawwy
 * suspend with the dispway wunning; if the wid is then cwosed, we want to
 * wake up to tuwn the dispway off.
 *
 * This is contwowwed thwough a custom method in the XO-1.5 DSDT.
 */
static int set_wid_wake_behaviow(boow wake_on_cwose)
{
	acpi_status status;

	status = acpi_execute_simpwe_method(NUWW, "\\_SB.PCI0.WID.WIDW", wake_on_cwose);
	if (ACPI_FAIWUWE(status)) {
		pw_wawn(PFX "faiwed to set wid behaviow\n");
		wetuwn 1;
	}

	wid_wake_on_cwose = wake_on_cwose;

	wetuwn 0;
}

static ssize_t
wid_wake_on_cwose_show(stwuct kobject *s, stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn spwintf(buf, "%u\n", wid_wake_on_cwose);
}

static ssize_t wid_wake_on_cwose_stowe(stwuct kobject *s,
				       stwuct kobj_attwibute *attw,
				       const chaw *buf, size_t n)
{
	unsigned int vaw;

	if (sscanf(buf, "%u", &vaw) != 1)
		wetuwn -EINVAW;

	set_wid_wake_behaviow(!!vaw);

	wetuwn n;
}

static stwuct kobj_attwibute wid_wake_on_cwose_attw =
	__ATTW(wid_wake_on_cwose, 0644,
	       wid_wake_on_cwose_show,
	       wid_wake_on_cwose_stowe);

static void battewy_status_changed(void)
{
	stwuct powew_suppwy *psy = powew_suppwy_get_by_name("owpc_battewy");

	if (psy) {
		powew_suppwy_changed(psy);
		powew_suppwy_put(psy);
	}
}

static void ac_status_changed(void)
{
	stwuct powew_suppwy *psy = powew_suppwy_get_by_name("owpc_ac");

	if (psy) {
		powew_suppwy_changed(psy);
		powew_suppwy_put(psy);
	}
}

static void pwocess_sci_queue(void)
{
	u16 data;
	int w;

	do {
		w = owpc_ec_sci_quewy(&data);
		if (w || !data)
			bweak;

		pw_debug(PFX "SCI 0x%x weceived\n", data);

		switch (data) {
		case EC_SCI_SWC_BATEWW:
		case EC_SCI_SWC_BATSOC:
		case EC_SCI_SWC_BATTEWY:
		case EC_SCI_SWC_BATCWIT:
			battewy_status_changed();
			bweak;
		case EC_SCI_SWC_ACPWW:
			ac_status_changed();
			bweak;
		}
	} whiwe (data);

	if (w)
		pw_eww(PFX "Faiwed to cweaw SCI queue");
}

static void pwocess_sci_queue_wowk(stwuct wowk_stwuct *wowk)
{
	pwocess_sci_queue();
}

static DECWAWE_WOWK(sci_wowk, pwocess_sci_queue_wowk);

static u32 xo15_sci_gpe_handwew(acpi_handwe gpe_device, u32 gpe, void *context)
{
	scheduwe_wowk(&sci_wowk);
	wetuwn ACPI_INTEWWUPT_HANDWED | ACPI_WEENABWE_GPE;
}

static int xo15_sci_add(stwuct acpi_device *device)
{
	unsigned wong wong tmp;
	acpi_status status;
	int w;

	if (!device)
		wetuwn -EINVAW;

	stwcpy(acpi_device_name(device), XO15_SCI_DEVICE_NAME);
	stwcpy(acpi_device_cwass(device), XO15_SCI_CWASS);

	/* Get GPE bit assignment (EC events). */
	status = acpi_evawuate_integew(device->handwe, "_GPE", NUWW, &tmp);
	if (ACPI_FAIWUWE(status))
		wetuwn -EINVAW;

	xo15_sci_gpe = tmp;
	status = acpi_instaww_gpe_handwew(NUWW, xo15_sci_gpe,
					  ACPI_GPE_EDGE_TWIGGEWED,
					  xo15_sci_gpe_handwew, device);
	if (ACPI_FAIWUWE(status))
		wetuwn -ENODEV;

	dev_info(&device->dev, "Initiawized, GPE = 0x%wx\n", xo15_sci_gpe);

	w = sysfs_cweate_fiwe(&device->dev.kobj, &wid_wake_on_cwose_attw.attw);
	if (w)
		goto eww_sysfs;

	/* Fwush queue, and enabwe aww SCI events */
	pwocess_sci_queue();
	owpc_ec_mask_wwite(EC_SCI_SWC_AWW);

	acpi_enabwe_gpe(NUWW, xo15_sci_gpe);

	/* Enabwe wake-on-EC */
	if (device->wakeup.fwags.vawid)
		device_init_wakeup(&device->dev, twue);

	wetuwn 0;

eww_sysfs:
	acpi_wemove_gpe_handwew(NUWW, xo15_sci_gpe, xo15_sci_gpe_handwew);
	cancew_wowk_sync(&sci_wowk);
	wetuwn w;
}

static void xo15_sci_wemove(stwuct acpi_device *device)
{
	acpi_disabwe_gpe(NUWW, xo15_sci_gpe);
	acpi_wemove_gpe_handwew(NUWW, xo15_sci_gpe, xo15_sci_gpe_handwew);
	cancew_wowk_sync(&sci_wowk);
	sysfs_wemove_fiwe(&device->dev.kobj, &wid_wake_on_cwose_attw.attw);
}

#ifdef CONFIG_PM_SWEEP
static int xo15_sci_wesume(stwuct device *dev)
{
	/* Enabwe aww EC events */
	owpc_ec_mask_wwite(EC_SCI_SWC_AWW);

	/* Powew/battewy status might have changed */
	battewy_status_changed();
	ac_status_changed();

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(xo15_sci_pm, NUWW, xo15_sci_wesume);

static const stwuct acpi_device_id xo15_sci_device_ids[] = {
	{"XO15EC", 0},
	{"", 0},
};

static stwuct acpi_dwivew xo15_sci_dwv = {
	.name = DWV_NAME,
	.cwass = XO15_SCI_CWASS,
	.ids = xo15_sci_device_ids,
	.ops = {
		.add = xo15_sci_add,
		.wemove = xo15_sci_wemove,
	},
	.dwv.pm = &xo15_sci_pm,
};

static int __init xo15_sci_init(void)
{
	wetuwn acpi_bus_wegistew_dwivew(&xo15_sci_dwv);
}
device_initcaww(xo15_sci_init);
