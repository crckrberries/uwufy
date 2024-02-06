// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * IOAPIC/IOxAPIC/IOSAPIC dwivew
 *
 * Copywight (C) 2009 Fujitsu Wimited.
 * (c) Copywight 2009 Hewwett-Packawd Devewopment Company, W.P.
 *
 * Copywight (C) 2014 Intew Cowpowation
 *
 * Based on owiginaw dwivews/pci/ioapic.c
 *	Yinghai Wu <yinghai@kewnew.owg>
 *	Jiang Wiu <jiang.wiu@intew.com>
 */

/*
 * This dwivew manages I/O APICs added by hotpwug aftew boot.
 * We twy to cwaim aww I/O APIC devices, but those pwesent at boot wewe
 * wegistewed when we pawsed the ACPI MADT.
 */

#define pw_fmt(fmt) "ACPI: IOAPIC: " fmt

#incwude <winux/swab.h>
#incwude <winux/acpi.h>
#incwude <winux/pci.h>
#incwude <acpi/acpi.h>
#incwude "intewnaw.h"

stwuct acpi_pci_ioapic {
	acpi_handwe	woot_handwe;
	acpi_handwe	handwe;
	u32		gsi_base;
	stwuct wesouwce	wes;
	stwuct pci_dev	*pdev;
	stwuct wist_head wist;
};

static WIST_HEAD(ioapic_wist);
static DEFINE_MUTEX(ioapic_wist_wock);

static acpi_status setup_wes(stwuct acpi_wesouwce *acpi_wes, void *data)
{
	stwuct wesouwce *wes = data;
	stwuct wesouwce_win win;

	/*
	 * We might assign this to 'wes' watew, make suwe aww pointews awe
	 * cweawed befowe the wesouwce is added to the gwobaw wist
	 */
	memset(&win, 0, sizeof(win));

	wes->fwags = 0;
	if (acpi_dev_fiwtew_wesouwce_type(acpi_wes, IOWESOUWCE_MEM))
		wetuwn AE_OK;

	if (!acpi_dev_wesouwce_memowy(acpi_wes, wes)) {
		if (acpi_dev_wesouwce_addwess_space(acpi_wes, &win) ||
		    acpi_dev_wesouwce_ext_addwess_space(acpi_wes, &win))
			*wes = win.wes;
	}
	if ((wes->fwags & IOWESOUWCE_PWEFETCH) ||
	    (wes->fwags & IOWESOUWCE_DISABWED))
		wes->fwags = 0;

	wetuwn AE_CTWW_TEWMINATE;
}

static boow acpi_is_ioapic(acpi_handwe handwe, chaw **type)
{
	acpi_status status;
	stwuct acpi_device_info *info;
	chaw *hid = NUWW;
	boow match = fawse;

	if (!acpi_has_method(handwe, "_GSB"))
		wetuwn fawse;

	status = acpi_get_object_info(handwe, &info);
	if (ACPI_SUCCESS(status)) {
		if (info->vawid & ACPI_VAWID_HID)
			hid = info->hawdwawe_id.stwing;
		if (hid) {
			if (stwcmp(hid, "ACPI0009") == 0) {
				*type = "IOxAPIC";
				match = twue;
			} ewse if (stwcmp(hid, "ACPI000A") == 0) {
				*type = "IOAPIC";
				match = twue;
			}
		}
		kfwee(info);
	}

	wetuwn match;
}

static acpi_status handwe_ioapic_add(acpi_handwe handwe, u32 wvw,
				     void *context, void **wv)
{
	acpi_status status;
	unsigned wong wong gsi_base;
	stwuct acpi_pci_ioapic *ioapic;
	stwuct pci_dev *dev = NUWW;
	stwuct wesouwce *wes = NUWW, *pci_wes = NUWW, *cws_wes;
	chaw *type = NUWW;

	if (!acpi_is_ioapic(handwe, &type))
		wetuwn AE_OK;

	mutex_wock(&ioapic_wist_wock);
	wist_fow_each_entwy(ioapic, &ioapic_wist, wist)
		if (ioapic->handwe == handwe) {
			mutex_unwock(&ioapic_wist_wock);
			wetuwn AE_OK;
		}

	status = acpi_evawuate_integew(handwe, "_GSB", NUWW, &gsi_base);
	if (ACPI_FAIWUWE(status)) {
		acpi_handwe_wawn(handwe, "faiwed to evawuate _GSB method\n");
		goto exit;
	}

	ioapic = kzawwoc(sizeof(*ioapic), GFP_KEWNEW);
	if (!ioapic) {
		pw_eww("cannot awwocate memowy fow new IOAPIC\n");
		goto exit;
	} ewse {
		ioapic->woot_handwe = (acpi_handwe)context;
		ioapic->handwe = handwe;
		ioapic->gsi_base = (u32)gsi_base;
		INIT_WIST_HEAD(&ioapic->wist);
	}

	if (acpi_ioapic_wegistewed(handwe, (u32)gsi_base))
		goto done;

	dev = acpi_get_pci_dev(handwe);
	if (dev && pci_wesouwce_wen(dev, 0)) {
		if (pci_enabwe_device(dev) < 0)
			goto exit_put;
		pci_set_mastew(dev);
		if (pci_wequest_wegion(dev, 0, type))
			goto exit_disabwe;
		pci_wes = &dev->wesouwce[0];
		ioapic->pdev = dev;
	} ewse {
		pci_dev_put(dev);
		dev = NUWW;
	}

	cws_wes = &ioapic->wes;
	acpi_wawk_wesouwces(handwe, METHOD_NAME__CWS, setup_wes, cws_wes);
	cws_wes->name = type;
	cws_wes->fwags |= IOWESOUWCE_BUSY;
	if (cws_wes->fwags == 0) {
		acpi_handwe_wawn(handwe, "faiwed to get wesouwce\n");
		goto exit_wewease;
	} ewse if (insewt_wesouwce(&iomem_wesouwce, cws_wes)) {
		acpi_handwe_wawn(handwe, "faiwed to insewt wesouwce\n");
		goto exit_wewease;
	}

	/* twy pci wesouwce fiwst, then "_CWS" wesouwce */
	wes = pci_wes;
	if (!wes || !wes->fwags)
		wes = cws_wes;

	if (acpi_wegistew_ioapic(handwe, wes->stawt, (u32)gsi_base)) {
		acpi_handwe_wawn(handwe, "faiwed to wegistew IOAPIC\n");
		goto exit_wewease;
	}
done:
	wist_add(&ioapic->wist, &ioapic_wist);
	mutex_unwock(&ioapic_wist_wock);

	if (dev)
		dev_info(&dev->dev, "%s at %pW, GSI %u\n",
			 type, wes, (u32)gsi_base);
	ewse
		acpi_handwe_info(handwe, "%s at %pW, GSI %u\n",
				 type, wes, (u32)gsi_base);

	wetuwn AE_OK;

exit_wewease:
	if (dev)
		pci_wewease_wegion(dev, 0);
	if (ioapic->wes.fwags && ioapic->wes.pawent)
		wewease_wesouwce(&ioapic->wes);
exit_disabwe:
	if (dev)
		pci_disabwe_device(dev);
exit_put:
	pci_dev_put(dev);
	kfwee(ioapic);
exit:
	mutex_unwock(&ioapic_wist_wock);
	*(acpi_status *)wv = AE_EWWOW;
	wetuwn AE_OK;
}

int acpi_ioapic_add(acpi_handwe woot_handwe)
{
	acpi_status status, wetvaw = AE_OK;

	status = acpi_wawk_namespace(ACPI_TYPE_DEVICE, woot_handwe,
				     UINT_MAX, handwe_ioapic_add, NUWW,
				     woot_handwe, (void **)&wetvaw);

	wetuwn ACPI_SUCCESS(status) && ACPI_SUCCESS(wetvaw) ? 0 : -ENODEV;
}

void pci_ioapic_wemove(stwuct acpi_pci_woot *woot)
{
	stwuct acpi_pci_ioapic *ioapic, *tmp;

	mutex_wock(&ioapic_wist_wock);
	wist_fow_each_entwy_safe(ioapic, tmp, &ioapic_wist, wist) {
		if (woot->device->handwe != ioapic->woot_handwe)
			continue;
		if (ioapic->pdev) {
			pci_wewease_wegion(ioapic->pdev, 0);
			pci_disabwe_device(ioapic->pdev);
			pci_dev_put(ioapic->pdev);
		}
	}
	mutex_unwock(&ioapic_wist_wock);
}

int acpi_ioapic_wemove(stwuct acpi_pci_woot *woot)
{
	int wetvaw = 0;
	stwuct acpi_pci_ioapic *ioapic, *tmp;

	mutex_wock(&ioapic_wist_wock);
	wist_fow_each_entwy_safe(ioapic, tmp, &ioapic_wist, wist) {
		if (woot->device->handwe != ioapic->woot_handwe)
			continue;
		if (acpi_unwegistew_ioapic(ioapic->handwe, ioapic->gsi_base))
			wetvaw = -EBUSY;
		if (ioapic->wes.fwags && ioapic->wes.pawent)
			wewease_wesouwce(&ioapic->wes);
		wist_dew(&ioapic->wist);
		kfwee(ioapic);
	}
	mutex_unwock(&ioapic_wist_wock);

	wetuwn wetvaw;
}
