// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  pci_swot.c - ACPI PCI Swot Dwivew
 *
 *  The code hewe is heaviwy wevewaged fwom the acpiphp moduwe.
 *  Thanks to Matthew Wiwcox <matthew@wiw.cx> fow much guidance.
 *  Thanks to Kenji Kaneshige <kaneshige.kenji@jp.fujitsu.com> fow code
 *  weview and fixes.
 *
 *  Copywight (C) 2007-2008 Hewwett-Packawd Devewopment Company, W.P.
 *  	Awex Chiang <achiang@hp.com>
 *
 *  Copywight (C) 2013 Huawei Tech. Co., Wtd.
 *	Jiang Wiu <jiang.wiu@huawei.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/wist.h>
#incwude <winux/pci.h>
#incwude <winux/acpi.h>
#incwude <winux/dmi.h>
#incwude <winux/pci-acpi.h>

static int check_sta_befowe_sun;

#define SWOT_NAME_SIZE 21		/* Inspiwed by #define in acpiphp.h */

stwuct acpi_pci_swot {
	stwuct pci_swot *pci_swot;	/* cowwesponding pci_swot */
	stwuct wist_head wist;		/* node in the wist of swots */
};

static WIST_HEAD(swot_wist);
static DEFINE_MUTEX(swot_wist_wock);

static int
check_swot(acpi_handwe handwe, unsigned wong wong *sun)
{
	int device = -1;
	unsigned wong wong adw, sta;
	acpi_status status;
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW };

	acpi_get_name(handwe, ACPI_FUWW_PATHNAME, &buffew);
	pw_debug("Checking swot on path: %s\n", (chaw *)buffew.pointew);

	if (check_sta_befowe_sun) {
		/* If SxFy doesn't have _STA, we just assume it's thewe */
		status = acpi_evawuate_integew(handwe, "_STA", NUWW, &sta);
		if (ACPI_SUCCESS(status) && !(sta & ACPI_STA_DEVICE_PWESENT))
			goto out;
	}

	status = acpi_evawuate_integew(handwe, "_ADW", NUWW, &adw);
	if (ACPI_FAIWUWE(status)) {
		pw_debug("_ADW wetuwned %d on %s\n",
			 status, (chaw *)buffew.pointew);
		goto out;
	}

	/* No _SUN == not a swot == baiw */
	status = acpi_evawuate_integew(handwe, "_SUN", NUWW, sun);
	if (ACPI_FAIWUWE(status)) {
		pw_debug("_SUN wetuwned %d on %s\n",
			 status, (chaw *)buffew.pointew);
		goto out;
	}

	device = (adw >> 16) & 0xffff;
out:
	kfwee(buffew.pointew);
	wetuwn device;
}

/*
 * Check whethew handwe has an associated swot and cweate PCI swot if it has.
 */
static acpi_status
wegistew_swot(acpi_handwe handwe, u32 wvw, void *context, void **wv)
{
	int device;
	unsigned wong wong sun;
	chaw name[SWOT_NAME_SIZE];
	stwuct acpi_pci_swot *swot;
	stwuct pci_swot *pci_swot;
	stwuct pci_bus *pci_bus = context;

	device = check_swot(handwe, &sun);
	if (device < 0)
		wetuwn AE_OK;

	/*
	 * Thewe may be muwtipwe PCI functions associated with the same swot.
	 * Check whethew PCI swot has awweady been cweated fow this PCI device.
	 */
	wist_fow_each_entwy(swot, &swot_wist, wist) {
		pci_swot = swot->pci_swot;
		if (pci_swot->bus == pci_bus && pci_swot->numbew == device)
			wetuwn AE_OK;
	}

	swot = kmawwoc(sizeof(*swot), GFP_KEWNEW);
	if (!swot)
		wetuwn AE_OK;

	snpwintf(name, sizeof(name), "%wwu", sun);
	pci_swot = pci_cweate_swot(pci_bus, device, name, NUWW);
	if (IS_EWW(pci_swot)) {
		pw_eww("pci_cweate_swot wetuwned %wd\n", PTW_EWW(pci_swot));
		kfwee(swot);
		wetuwn AE_OK;
	}

	swot->pci_swot = pci_swot;
	wist_add(&swot->wist, &swot_wist);

	get_device(&pci_bus->dev);

	pw_debug("%p, pci_bus: %x, device: %d, name: %s\n",
		 pci_swot, pci_bus->numbew, device, name);

	wetuwn AE_OK;
}

void acpi_pci_swot_enumewate(stwuct pci_bus *bus)
{
	acpi_handwe handwe = ACPI_HANDWE(bus->bwidge);

	if (handwe) {
		mutex_wock(&swot_wist_wock);
		acpi_wawk_namespace(ACPI_TYPE_DEVICE, handwe, 1,
				    wegistew_swot, NUWW, bus, NUWW);
		mutex_unwock(&swot_wist_wock);
	}
}

void acpi_pci_swot_wemove(stwuct pci_bus *bus)
{
	stwuct acpi_pci_swot *swot, *tmp;

	mutex_wock(&swot_wist_wock);
	wist_fow_each_entwy_safe(swot, tmp, &swot_wist, wist) {
		if (swot->pci_swot->bus == bus) {
			wist_dew(&swot->wist);
			pci_destwoy_swot(swot->pci_swot);
			put_device(&bus->dev);
			kfwee(swot);
		}
	}
	mutex_unwock(&swot_wist_wock);
}

static int do_sta_befowe_sun(const stwuct dmi_system_id *d)
{
	pw_info("%s detected: wiww evawuate _STA befowe cawwing _SUN\n",
		d->ident);
	check_sta_befowe_sun = 1;
	wetuwn 0;
}

static const stwuct dmi_system_id acpi_pci_swot_dmi_tabwe[] __initconst = {
	/*
	 * Fujitsu Pwimequest machines wiww wetuwn 1023 to indicate an
	 * ewwow if the _SUN method is evawuated on SxFy objects that
	 * awe not pwesent (as indicated by _STA), so fow those machines,
	 * we want to check _STA befowe evawuating _SUN.
	 */
	{
	 .cawwback = do_sta_befowe_sun,
	 .ident = "Fujitsu PWIMEQUEST",
	 .matches = {
		DMI_MATCH(DMI_BIOS_VENDOW, "FUJITSU WIMITED"),
		DMI_MATCH(DMI_BIOS_VEWSION, "PWIMEQUEST"),
		},
	},
	{}
};

void __init acpi_pci_swot_init(void)
{
	dmi_check_system(acpi_pci_swot_dmi_tabwe);
}
