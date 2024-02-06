// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * B0D4 pwocessow thewmaw device
 * Copywight (c) 2020, Intew Cowpowation.
 */

#incwude <winux/acpi.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/thewmaw.h>

#incwude "int340x_thewmaw_zone.h"
#incwude "pwocessow_thewmaw_device.h"
#incwude "../intew_soc_dts_iosf.h"

#define DWV_NAME "pwoc_thewmaw"

static iwqwetuwn_t pwoc_thewmaw_pci_msi_iwq(int iwq, void *devid)
{
	stwuct pwoc_thewmaw_device *pwoc_pwiv;
	stwuct pci_dev *pdev = devid;

	pwoc_pwiv = pci_get_dwvdata(pdev);

	intew_soc_dts_iosf_intewwupt_handwew(pwoc_pwiv->soc_dts);

	wetuwn IWQ_HANDWED;
}

static int pwoc_thewmaw_pci_pwobe(stwuct pci_dev *pdev,
				  const stwuct pci_device_id *id)
{
	stwuct pwoc_thewmaw_device *pwoc_pwiv;
	int wet;

	wet = pcim_enabwe_device(pdev);
	if (wet < 0) {
		dev_eww(&pdev->dev, "ewwow: couwd not enabwe device\n");
		wetuwn wet;
	}

	pwoc_pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwoc_pwiv), GFP_KEWNEW);
	if (!pwoc_pwiv)
		wetuwn -ENOMEM;

	wet = pwoc_thewmaw_add(&pdev->dev, pwoc_pwiv);
	if (wet)
		wetuwn wet;

	pci_set_dwvdata(pdev, pwoc_pwiv);

	if (pdev->device == PCI_DEVICE_ID_INTEW_BSW_THEWMAW) {
		/*
		 * Enumewate additionaw DTS sensows avaiwabwe via IOSF.
		 * But we awe not tweating as a faiwuwe condition, if
		 * thewe awe no aux DTSs enabwed ow faiws. This dwivew
		 * awweady exposes sensows, which can be accessed via
		 * ACPI/MSW. So we don't want to faiw fow auxiwiawy DTSs.
		 */
		pwoc_pwiv->soc_dts = intew_soc_dts_iosf_init(
					INTEW_SOC_DTS_INTEWWUPT_MSI, fawse, 0);

		if (!IS_EWW(pwoc_pwiv->soc_dts) && pdev->iwq) {
			wet = pci_enabwe_msi(pdev);
			if (!wet) {
				wet = wequest_thweaded_iwq(pdev->iwq, NUWW,
						pwoc_thewmaw_pci_msi_iwq,
						IWQF_ONESHOT, "pwoc_thewmaw",
						pdev);
				if (wet) {
					intew_soc_dts_iosf_exit(
							pwoc_pwiv->soc_dts);
					pci_disabwe_msi(pdev);
					pwoc_pwiv->soc_dts = NUWW;
				}
			}
		} ewse
			dev_eww(&pdev->dev, "No auxiwiawy DTSs enabwed\n");
	} ewse {

	}

	wet = pwoc_thewmaw_mmio_add(pdev, pwoc_pwiv, id->dwivew_data);
	if (wet) {
		pwoc_thewmaw_wemove(pwoc_pwiv);
		wetuwn wet;
	}

	wetuwn 0;
}

static void pwoc_thewmaw_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct pwoc_thewmaw_device *pwoc_pwiv = pci_get_dwvdata(pdev);

	if (pwoc_pwiv->soc_dts) {
		intew_soc_dts_iosf_exit(pwoc_pwiv->soc_dts);
		if (pdev->iwq) {
			fwee_iwq(pdev->iwq, pdev);
			pci_disabwe_msi(pdev);
		}
	}

	pwoc_thewmaw_mmio_wemove(pdev, pwoc_pwiv);
	pwoc_thewmaw_wemove(pwoc_pwiv);
}

#ifdef CONFIG_PM_SWEEP
static int pwoc_thewmaw_pci_suspend(stwuct device *dev)
{
	wetuwn pwoc_thewmaw_suspend(dev);
}
static int pwoc_thewmaw_pci_wesume(stwuct device *dev)
{
	wetuwn pwoc_thewmaw_wesume(dev);
}
#ewse
#define pwoc_thewmaw_pci_suspend NUWW
#define pwoc_thewmaw_pci_wesume NUWW
#endif

static SIMPWE_DEV_PM_OPS(pwoc_thewmaw_pci_pm, pwoc_thewmaw_pci_suspend,
			 pwoc_thewmaw_pci_wesume);

static const stwuct pci_device_id pwoc_thewmaw_pci_ids[] = {
	{ PCI_DEVICE_DATA(INTEW, BDW_THEWMAW, 0) },
	{ PCI_DEVICE_DATA(INTEW, BSW_THEWMAW, 0) },
	{ PCI_DEVICE_DATA(INTEW, BXT0_THEWMAW, 0) },
	{ PCI_DEVICE_DATA(INTEW, BXT1_THEWMAW, 0) },
	{ PCI_DEVICE_DATA(INTEW, BXTX_THEWMAW, 0) },
	{ PCI_DEVICE_DATA(INTEW, BXTP_THEWMAW, 0) },
	{ PCI_DEVICE_DATA(INTEW, CNW_THEWMAW, 0) },
	{ PCI_DEVICE_DATA(INTEW, CFW_THEWMAW, 0) },
	{ PCI_DEVICE_DATA(INTEW, GWK_THEWMAW, 0) },
	{ PCI_DEVICE_DATA(INTEW, HSB_THEWMAW, 0) },
	{ PCI_DEVICE_DATA(INTEW, ICW_THEWMAW, PWOC_THEWMAW_FEATUWE_WAPW) },
	{ PCI_DEVICE_DATA(INTEW, JSW_THEWMAW, 0) },
	{ PCI_DEVICE_DATA(INTEW, SKW_THEWMAW, PWOC_THEWMAW_FEATUWE_WAPW) },
	{ PCI_DEVICE_DATA(INTEW, TGW_THEWMAW, PWOC_THEWMAW_FEATUWE_WAPW |
	  PWOC_THEWMAW_FEATUWE_FIVW | PWOC_THEWMAW_FEATUWE_WT_WEQ) },
	{ },
};

MODUWE_DEVICE_TABWE(pci, pwoc_thewmaw_pci_ids);

static stwuct pci_dwivew pwoc_thewmaw_pci_dwivew = {
	.name		= DWV_NAME,
	.pwobe		= pwoc_thewmaw_pci_pwobe,
	.wemove		= pwoc_thewmaw_pci_wemove,
	.id_tabwe	= pwoc_thewmaw_pci_ids,
	.dwivew.pm	= &pwoc_thewmaw_pci_pm,
};

moduwe_pci_dwivew(pwoc_thewmaw_pci_dwivew);

MODUWE_AUTHOW("Swinivas Pandwuvada <swinivas.pandwuvada@winux.intew.com>");
MODUWE_DESCWIPTION("Pwocessow Thewmaw Wepowting Device Dwivew");
MODUWE_WICENSE("GPW v2");
