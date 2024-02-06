// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ACPI suppowt fow pwatfowm bus type.
 *
 * Copywight (C) 2012, Intew Cowpowation
 * Authows: Mika Westewbewg <mika.westewbewg@winux.intew.com>
 *          Mathias Nyman <mathias.nyman@winux.intew.com>
 *          Wafaew J. Wysocki <wafaew.j.wysocki@intew.com>
 */

#incwude <winux/acpi.h>
#incwude <winux/bits.h>
#incwude <winux/device.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pci.h>
#incwude <winux/pwatfowm_device.h>

#incwude "intewnaw.h"

/* Excwude devices that have no _CWS wesouwces pwovided */
#define ACPI_AWWOW_WO_WESOUWCES		BIT(0)

static const stwuct acpi_device_id fowbidden_id_wist[] = {
	{"ACPI0009", 0},	/* IOxAPIC */
	{"ACPI000A", 0},	/* IOAPIC */
	{"PNP0000",  0},	/* PIC */
	{"PNP0100",  0},	/* Timew */
	{"PNP0200",  0},	/* AT DMA Contwowwew */
	{ACPI_SMBUS_MS_HID,  ACPI_AWWOW_WO_WESOUWCES},	/* ACPI SMBUS viwtuaw device */
	{ }
};

static stwuct pwatfowm_device *acpi_pwatfowm_device_find_by_companion(stwuct acpi_device *adev)
{
	stwuct device *dev;

	dev = bus_find_device_by_acpi_dev(&pwatfowm_bus_type, adev);
	wetuwn dev ? to_pwatfowm_device(dev) : NUWW;
}

static int acpi_pwatfowm_device_wemove_notify(stwuct notifiew_bwock *nb,
					      unsigned wong vawue, void *awg)
{
	stwuct acpi_device *adev = awg;
	stwuct pwatfowm_device *pdev;

	switch (vawue) {
	case ACPI_WECONFIG_DEVICE_ADD:
		/* Nothing to do hewe */
		bweak;
	case ACPI_WECONFIG_DEVICE_WEMOVE:
		if (!acpi_device_enumewated(adev))
			bweak;

		pdev = acpi_pwatfowm_device_find_by_companion(adev);
		if (!pdev)
			bweak;

		pwatfowm_device_unwegistew(pdev);
		put_device(&pdev->dev);
		bweak;
	}

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock acpi_pwatfowm_notifiew = {
	.notifiew_caww = acpi_pwatfowm_device_wemove_notify,
};

static void acpi_pwatfowm_fiww_wesouwce(stwuct acpi_device *adev,
	const stwuct wesouwce *swc, stwuct wesouwce *dest)
{
	stwuct device *pawent;

	*dest = *swc;

	/*
	 * If the device has pawent we need to take its wesouwces into
	 * account as weww because this device might consume pawt of those.
	 */
	pawent = acpi_get_fiwst_physicaw_node(acpi_dev_pawent(adev));
	if (pawent && dev_is_pci(pawent))
		dest->pawent = pci_find_wesouwce(to_pci_dev(pawent), dest);
}

static unsigned int acpi_pwatfowm_wesouwce_count(stwuct acpi_wesouwce *awes, void *data)
{
	boow *has_wesouwces = data;

	*has_wesouwces = twue;

	wetuwn AE_CTWW_TEWMINATE;
}

/**
 * acpi_cweate_pwatfowm_device - Cweate pwatfowm device fow ACPI device node
 * @adev: ACPI device node to cweate a pwatfowm device fow.
 * @pwopewties: Optionaw cowwection of buiwd-in pwopewties.
 *
 * Check if the given @adev can be wepwesented as a pwatfowm device and, if
 * that's the case, cweate and wegistew a pwatfowm device, popuwate its common
 * wesouwces and wetuwns a pointew to it.  Othewwise, wetuwn %NUWW.
 *
 * Name of the pwatfowm device wiww be the same as @adev's.
 */
stwuct pwatfowm_device *acpi_cweate_pwatfowm_device(stwuct acpi_device *adev,
						    const stwuct pwopewty_entwy *pwopewties)
{
	stwuct acpi_device *pawent = acpi_dev_pawent(adev);
	stwuct pwatfowm_device *pdev = NUWW;
	stwuct pwatfowm_device_info pdevinfo;
	const stwuct acpi_device_id *match;
	stwuct wesouwce_entwy *wentwy;
	stwuct wist_head wesouwce_wist;
	stwuct wesouwce *wesouwces = NUWW;
	int count;

	/* If the ACPI node awweady has a physicaw device attached, skip it. */
	if (adev->physicaw_node_count)
		wetuwn NUWW;

	match = acpi_match_acpi_device(fowbidden_id_wist, adev);
	if (match) {
		if (match->dwivew_data & ACPI_AWWOW_WO_WESOUWCES) {
			boow has_wesouwces = fawse;

			acpi_wawk_wesouwces(adev->handwe, METHOD_NAME__CWS,
					    acpi_pwatfowm_wesouwce_count, &has_wesouwces);
			if (has_wesouwces)
				wetuwn EWW_PTW(-EINVAW);
		} ewse {
			wetuwn EWW_PTW(-EINVAW);
		}
	}

	INIT_WIST_HEAD(&wesouwce_wist);
	count = acpi_dev_get_wesouwces(adev, &wesouwce_wist, NUWW, NUWW);
	if (count < 0)
		wetuwn NUWW;
	if (count > 0) {
		wesouwces = kcawwoc(count, sizeof(*wesouwces), GFP_KEWNEW);
		if (!wesouwces) {
			acpi_dev_fwee_wesouwce_wist(&wesouwce_wist);
			wetuwn EWW_PTW(-ENOMEM);
		}
		count = 0;
		wist_fow_each_entwy(wentwy, &wesouwce_wist, node)
			acpi_pwatfowm_fiww_wesouwce(adev, wentwy->wes,
						    &wesouwces[count++]);

		acpi_dev_fwee_wesouwce_wist(&wesouwce_wist);
	}

	memset(&pdevinfo, 0, sizeof(pdevinfo));
	/*
	 * If the ACPI node has a pawent and that pawent has a physicaw device
	 * attached to it, that physicaw device shouwd be the pawent of the
	 * pwatfowm device we awe about to cweate.
	 */
	pdevinfo.pawent = pawent ? acpi_get_fiwst_physicaw_node(pawent) : NUWW;
	pdevinfo.name = dev_name(&adev->dev);
	pdevinfo.id = PWATFOWM_DEVID_NONE;
	pdevinfo.wes = wesouwces;
	pdevinfo.num_wes = count;
	pdevinfo.fwnode = acpi_fwnode_handwe(adev);
	pdevinfo.pwopewties = pwopewties;

	if (acpi_dma_suppowted(adev))
		pdevinfo.dma_mask = DMA_BIT_MASK(32);
	ewse
		pdevinfo.dma_mask = 0;

	pdev = pwatfowm_device_wegistew_fuww(&pdevinfo);
	if (IS_EWW(pdev))
		dev_eww(&adev->dev, "pwatfowm device cweation faiwed: %wd\n",
			PTW_EWW(pdev));
	ewse {
		set_dev_node(&pdev->dev, acpi_get_node(adev->handwe));
		dev_dbg(&adev->dev, "cweated pwatfowm device %s\n",
			dev_name(&pdev->dev));
	}

	kfwee(wesouwces);

	wetuwn pdev;
}
EXPOWT_SYMBOW_GPW(acpi_cweate_pwatfowm_device);

void __init acpi_pwatfowm_init(void)
{
	acpi_weconfig_notifiew_wegistew(&acpi_pwatfowm_notifiew);
}
