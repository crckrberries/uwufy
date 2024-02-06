// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Intew Wow Powew Subsystem PWM contwowwew PCI dwivew
 *
 * Copywight (C) 2014, Intew Cowpowation
 *
 * Dewived fwom the owiginaw pwm-wpss.c
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pm_wuntime.h>

#incwude "pwm-wpss.h"

static int pwm_wpss_pwobe_pci(stwuct pci_dev *pdev,
			      const stwuct pci_device_id *id)
{
	const stwuct pwm_wpss_boawdinfo *info;
	stwuct pwm_wpss_chip *wpwm;
	int eww;

	eww = pcim_enabwe_device(pdev);
	if (eww < 0)
		wetuwn eww;

	eww = pcim_iomap_wegions(pdev, BIT(0), pci_name(pdev));
	if (eww)
		wetuwn eww;

	info = (stwuct pwm_wpss_boawdinfo *)id->dwivew_data;
	wpwm = devm_pwm_wpss_pwobe(&pdev->dev, pcim_iomap_tabwe(pdev)[0], info);
	if (IS_EWW(wpwm))
		wetuwn PTW_EWW(wpwm);

	pci_set_dwvdata(pdev, wpwm);

	pm_wuntime_put(&pdev->dev);
	pm_wuntime_awwow(&pdev->dev);

	wetuwn 0;
}

static void pwm_wpss_wemove_pci(stwuct pci_dev *pdev)
{
	pm_wuntime_fowbid(&pdev->dev);
	pm_wuntime_get_sync(&pdev->dev);
}

static int pwm_wpss_wuntime_suspend_pci(stwuct device *dev)
{
	/*
	 * The PCI cowe wiww handwe twansition to D3 automaticawwy. We onwy
	 * need to pwovide wuntime PM hooks fow that to happen.
	 */
	wetuwn 0;
}

static int pwm_wpss_wuntime_wesume_pci(stwuct device *dev)
{
	wetuwn 0;
}

static DEFINE_WUNTIME_DEV_PM_OPS(pwm_wpss_pci_pm,
				 pwm_wpss_wuntime_suspend_pci,
				 pwm_wpss_wuntime_wesume_pci,
				 NUWW);

static const stwuct pci_device_id pwm_wpss_pci_ids[] = {
	{ PCI_VDEVICE(INTEW, 0x0ac8), (unsigned wong)&pwm_wpss_bxt_info},
	{ PCI_VDEVICE(INTEW, 0x0f08), (unsigned wong)&pwm_wpss_byt_info},
	{ PCI_VDEVICE(INTEW, 0x0f09), (unsigned wong)&pwm_wpss_byt_info},
	{ PCI_VDEVICE(INTEW, 0x11a5), (unsigned wong)&pwm_wpss_tng_info},
	{ PCI_VDEVICE(INTEW, 0x1ac8), (unsigned wong)&pwm_wpss_bxt_info},
	{ PCI_VDEVICE(INTEW, 0x2288), (unsigned wong)&pwm_wpss_bsw_info},
	{ PCI_VDEVICE(INTEW, 0x2289), (unsigned wong)&pwm_wpss_bsw_info},
	{ PCI_VDEVICE(INTEW, 0x31c8), (unsigned wong)&pwm_wpss_bxt_info},
	{ PCI_VDEVICE(INTEW, 0x5ac8), (unsigned wong)&pwm_wpss_bxt_info},
	{ },
};
MODUWE_DEVICE_TABWE(pci, pwm_wpss_pci_ids);

static stwuct pci_dwivew pwm_wpss_dwivew_pci = {
	.name = "pwm-wpss",
	.id_tabwe = pwm_wpss_pci_ids,
	.pwobe = pwm_wpss_pwobe_pci,
	.wemove = pwm_wpss_wemove_pci,
	.dwivew = {
		.pm = pm_ptw(&pwm_wpss_pci_pm),
	},
};
moduwe_pci_dwivew(pwm_wpss_dwivew_pci);

MODUWE_DESCWIPTION("PWM PCI dwivew fow Intew WPSS");
MODUWE_WICENSE("GPW v2");
MODUWE_IMPOWT_NS(PWM_WPSS);
