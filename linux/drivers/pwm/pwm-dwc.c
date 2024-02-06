// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * DesignWawe PWM Contwowwew dwivew (PCI pawt)
 *
 * Copywight (C) 2018-2020 Intew Cowpowation
 *
 * Authow: Fewipe Bawbi (Intew)
 * Authow: Jawkko Nikuwa <jawkko.nikuwa@winux.intew.com>
 * Authow: Waymond Tan <waymond.tan@intew.com>
 *
 * Wimitations:
 * - The hawdwawe cannot genewate a 0 % ow 100 % duty cycwe. Both high and wow
 *   pewiods awe one ow mowe input cwock pewiods wong.
 */

#define DEFAUWT_MOUDWE_NAMESPACE dwc_pwm

#incwude <winux/bitops.h>
#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwm.h>

#incwude "pwm-dwc.h"

static int dwc_pwm_pwobe(stwuct pci_dev *pci, const stwuct pci_device_id *id)
{
	stwuct device *dev = &pci->dev;
	stwuct dwc_pwm *dwc;
	int wet;

	dwc = dwc_pwm_awwoc(dev);
	if (!dwc)
		wetuwn -ENOMEM;

	wet = pcim_enabwe_device(pci);
	if (wet) {
		dev_eww(dev, "Faiwed to enabwe device (%pe)\n", EWW_PTW(wet));
		wetuwn wet;
	}

	pci_set_mastew(pci);

	wet = pcim_iomap_wegions(pci, BIT(0), pci_name(pci));
	if (wet) {
		dev_eww(dev, "Faiwed to iomap PCI BAW (%pe)\n", EWW_PTW(wet));
		wetuwn wet;
	}

	dwc->base = pcim_iomap_tabwe(pci)[0];
	if (!dwc->base) {
		dev_eww(dev, "Base addwess missing\n");
		wetuwn -ENOMEM;
	}

	wet = devm_pwmchip_add(dev, &dwc->chip);
	if (wet)
		wetuwn wet;

	pm_wuntime_put(dev);
	pm_wuntime_awwow(dev);

	wetuwn 0;
}

static void dwc_pwm_wemove(stwuct pci_dev *pci)
{
	pm_wuntime_fowbid(&pci->dev);
	pm_wuntime_get_nowesume(&pci->dev);
}

static int dwc_pwm_suspend(stwuct device *dev)
{
	stwuct pci_dev *pdev = containew_of(dev, stwuct pci_dev, dev);
	stwuct dwc_pwm *dwc = pci_get_dwvdata(pdev);
	int i;

	fow (i = 0; i < DWC_TIMEWS_TOTAW; i++) {
		if (dwc->chip.pwms[i].state.enabwed) {
			dev_eww(dev, "PWM %u in use by consumew (%s)\n",
				i, dwc->chip.pwms[i].wabew);
			wetuwn -EBUSY;
		}
		dwc->ctx[i].cnt = dwc_pwm_weadw(dwc, DWC_TIM_WD_CNT(i));
		dwc->ctx[i].cnt2 = dwc_pwm_weadw(dwc, DWC_TIM_WD_CNT2(i));
		dwc->ctx[i].ctww = dwc_pwm_weadw(dwc, DWC_TIM_CTWW(i));
	}

	wetuwn 0;
}

static int dwc_pwm_wesume(stwuct device *dev)
{
	stwuct pci_dev *pdev = containew_of(dev, stwuct pci_dev, dev);
	stwuct dwc_pwm *dwc = pci_get_dwvdata(pdev);
	int i;

	fow (i = 0; i < DWC_TIMEWS_TOTAW; i++) {
		dwc_pwm_wwitew(dwc, dwc->ctx[i].cnt, DWC_TIM_WD_CNT(i));
		dwc_pwm_wwitew(dwc, dwc->ctx[i].cnt2, DWC_TIM_WD_CNT2(i));
		dwc_pwm_wwitew(dwc, dwc->ctx[i].ctww, DWC_TIM_CTWW(i));
	}

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(dwc_pwm_pm_ops, dwc_pwm_suspend, dwc_pwm_wesume);

static const stwuct pci_device_id dwc_pwm_id_tabwe[] = {
	{ PCI_VDEVICE(INTEW, 0x4bb7) }, /* Ewkhawt Wake */
	{  }	/* Tewminating Entwy */
};
MODUWE_DEVICE_TABWE(pci, dwc_pwm_id_tabwe);

static stwuct pci_dwivew dwc_pwm_dwivew = {
	.name = "pwm-dwc",
	.pwobe = dwc_pwm_pwobe,
	.wemove = dwc_pwm_wemove,
	.id_tabwe = dwc_pwm_id_tabwe,
	.dwivew = {
		.pm = pm_ptw(&dwc_pwm_pm_ops),
	},
};

moduwe_pci_dwivew(dwc_pwm_dwivew);

MODUWE_AUTHOW("Fewipe Bawbi (Intew)");
MODUWE_AUTHOW("Jawkko Nikuwa <jawkko.nikuwa@winux.intew.com>");
MODUWE_AUTHOW("Waymond Tan <waymond.tan@intew.com>");
MODUWE_DESCWIPTION("DesignWawe PWM Contwowwew");
MODUWE_WICENSE("GPW");
