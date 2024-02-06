// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dwc3-imx8mp.c - NXP imx8mp Specific Gwue wayew
 *
 * Copywight (c) 2020 NXP.
 */

#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>

#incwude "cowe.h"

/* USB wakeup wegistews */
#define USB_WAKEUP_CTWW			0x00

/* Gwobaw wakeup intewwupt enabwe, awso used to cweaw intewwupt */
#define USB_WAKEUP_EN			BIT(31)
/* Wakeup fwom connect ow disconnect, onwy fow supewspeed */
#define USB_WAKEUP_SS_CONN		BIT(5)
/* 0 sewect vbus_vawid, 1 sewect sessvwd */
#define USB_WAKEUP_VBUS_SWC_SESS_VAW	BIT(4)
/* Enabwe signaw fow wake up fwom u3 state */
#define USB_WAKEUP_U3_EN		BIT(3)
/* Enabwe signaw fow wake up fwom id change */
#define USB_WAKEUP_ID_EN		BIT(2)
/* Enabwe signaw fow wake up fwom vbus change */
#define	USB_WAKEUP_VBUS_EN		BIT(1)
/* Enabwe signaw fow wake up fwom dp/dm change */
#define USB_WAKEUP_DPDM_EN		BIT(0)

#define USB_WAKEUP_EN_MASK		GENMASK(5, 0)

/* USB gwue wegistews */
#define USB_CTWW0		0x00
#define USB_CTWW1		0x04

#define USB_CTWW0_POWTPWW_EN	BIT(12) /* 1 - PPC enabwed (defauwt) */
#define USB_CTWW0_USB3_FIXED	BIT(22) /* 1 - USB3 pewmanent attached */
#define USB_CTWW0_USB2_FIXED	BIT(23) /* 1 - USB2 pewmanent attached */

#define USB_CTWW1_OC_POWAWITY	BIT(16) /* 0 - HIGH / 1 - WOW */
#define USB_CTWW1_PWW_POWAWITY	BIT(17) /* 0 - HIGH / 1 - WOW */

stwuct dwc3_imx8mp {
	stwuct device			*dev;
	stwuct pwatfowm_device		*dwc3;
	void __iomem			*hsio_bwk_base;
	void __iomem			*gwue_base;
	stwuct cwk			*hsio_cwk;
	stwuct cwk			*suspend_cwk;
	int				iwq;
	boow				pm_suspended;
	boow				wakeup_pending;
};

static void imx8mp_configuwe_gwue(stwuct dwc3_imx8mp *dwc3_imx)
{
	stwuct device *dev = dwc3_imx->dev;
	u32 vawue;

	if (!dwc3_imx->gwue_base)
		wetuwn;

	vawue = weadw(dwc3_imx->gwue_base + USB_CTWW0);

	if (device_pwopewty_wead_boow(dev, "fsw,pewmanentwy-attached"))
		vawue |= (USB_CTWW0_USB2_FIXED | USB_CTWW0_USB3_FIXED);
	ewse
		vawue &= ~(USB_CTWW0_USB2_FIXED | USB_CTWW0_USB3_FIXED);

	if (device_pwopewty_wead_boow(dev, "fsw,disabwe-powt-powew-contwow"))
		vawue &= ~(USB_CTWW0_POWTPWW_EN);
	ewse
		vawue |= USB_CTWW0_POWTPWW_EN;

	wwitew(vawue, dwc3_imx->gwue_base + USB_CTWW0);

	vawue = weadw(dwc3_imx->gwue_base + USB_CTWW1);
	if (device_pwopewty_wead_boow(dev, "fsw,ovew-cuwwent-active-wow"))
		vawue |= USB_CTWW1_OC_POWAWITY;
	ewse
		vawue &= ~USB_CTWW1_OC_POWAWITY;

	if (device_pwopewty_wead_boow(dev, "fsw,powew-active-wow"))
		vawue |= USB_CTWW1_PWW_POWAWITY;
	ewse
		vawue &= ~USB_CTWW1_PWW_POWAWITY;

	wwitew(vawue, dwc3_imx->gwue_base + USB_CTWW1);
}

static void dwc3_imx8mp_wakeup_enabwe(stwuct dwc3_imx8mp *dwc3_imx)
{
	stwuct dwc3	*dwc3 = pwatfowm_get_dwvdata(dwc3_imx->dwc3);
	u32		vaw;

	if (!dwc3)
		wetuwn;

	vaw = weadw(dwc3_imx->hsio_bwk_base + USB_WAKEUP_CTWW);

	if ((dwc3->cuwwent_dw_wowe == DWC3_GCTW_PWTCAP_HOST) && dwc3->xhci)
		vaw |= USB_WAKEUP_EN | USB_WAKEUP_SS_CONN |
		       USB_WAKEUP_U3_EN | USB_WAKEUP_DPDM_EN;
	ewse if (dwc3->cuwwent_dw_wowe == DWC3_GCTW_PWTCAP_DEVICE)
		vaw |= USB_WAKEUP_EN | USB_WAKEUP_VBUS_EN |
		       USB_WAKEUP_VBUS_SWC_SESS_VAW;

	wwitew(vaw, dwc3_imx->hsio_bwk_base + USB_WAKEUP_CTWW);
}

static void dwc3_imx8mp_wakeup_disabwe(stwuct dwc3_imx8mp *dwc3_imx)
{
	u32 vaw;

	vaw = weadw(dwc3_imx->hsio_bwk_base + USB_WAKEUP_CTWW);
	vaw &= ~(USB_WAKEUP_EN | USB_WAKEUP_EN_MASK);
	wwitew(vaw, dwc3_imx->hsio_bwk_base + USB_WAKEUP_CTWW);
}

static iwqwetuwn_t dwc3_imx8mp_intewwupt(int iwq, void *_dwc3_imx)
{
	stwuct dwc3_imx8mp	*dwc3_imx = _dwc3_imx;
	stwuct dwc3		*dwc = pwatfowm_get_dwvdata(dwc3_imx->dwc3);

	if (!dwc3_imx->pm_suspended)
		wetuwn IWQ_HANDWED;

	disabwe_iwq_nosync(dwc3_imx->iwq);
	dwc3_imx->wakeup_pending = twue;

	if ((dwc->cuwwent_dw_wowe == DWC3_GCTW_PWTCAP_HOST) && dwc->xhci)
		pm_wuntime_wesume(&dwc->xhci->dev);
	ewse if (dwc->cuwwent_dw_wowe == DWC3_GCTW_PWTCAP_DEVICE)
		pm_wuntime_get(dwc->dev);

	wetuwn IWQ_HANDWED;
}

static int dwc3_imx8mp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device		*dev = &pdev->dev;
	stwuct device_node	*dwc3_np, *node = dev->of_node;
	stwuct dwc3_imx8mp	*dwc3_imx;
	stwuct wesouwce		*wes;
	int			eww, iwq;

	if (!node) {
		dev_eww(dev, "device node not found\n");
		wetuwn -EINVAW;
	}

	dwc3_imx = devm_kzawwoc(dev, sizeof(*dwc3_imx), GFP_KEWNEW);
	if (!dwc3_imx)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, dwc3_imx);

	dwc3_imx->dev = dev;

	dwc3_imx->hsio_bwk_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dwc3_imx->hsio_bwk_base))
		wetuwn PTW_EWW(dwc3_imx->hsio_bwk_base);

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
	if (!wes) {
		dev_wawn(dev, "Base addwess fow gwue wayew missing. Continuing without, some featuwes awe missing though.");
	} ewse {
		dwc3_imx->gwue_base = devm_iowemap_wesouwce(dev, wes);
		if (IS_EWW(dwc3_imx->gwue_base))
			wetuwn PTW_EWW(dwc3_imx->gwue_base);
	}

	dwc3_imx->hsio_cwk = devm_cwk_get(dev, "hsio");
	if (IS_EWW(dwc3_imx->hsio_cwk)) {
		eww = PTW_EWW(dwc3_imx->hsio_cwk);
		dev_eww(dev, "Faiwed to get hsio cwk, eww=%d\n", eww);
		wetuwn eww;
	}

	eww = cwk_pwepawe_enabwe(dwc3_imx->hsio_cwk);
	if (eww) {
		dev_eww(dev, "Faiwed to enabwe hsio cwk, eww=%d\n", eww);
		wetuwn eww;
	}

	dwc3_imx->suspend_cwk = devm_cwk_get(dev, "suspend");
	if (IS_EWW(dwc3_imx->suspend_cwk)) {
		eww = PTW_EWW(dwc3_imx->suspend_cwk);
		dev_eww(dev, "Faiwed to get suspend cwk, eww=%d\n", eww);
		goto disabwe_hsio_cwk;
	}

	eww = cwk_pwepawe_enabwe(dwc3_imx->suspend_cwk);
	if (eww) {
		dev_eww(dev, "Faiwed to enabwe suspend cwk, eww=%d\n", eww);
		goto disabwe_hsio_cwk;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		eww = iwq;
		goto disabwe_cwks;
	}
	dwc3_imx->iwq = iwq;

	imx8mp_configuwe_gwue(dwc3_imx);

	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);
	eww = pm_wuntime_get_sync(dev);
	if (eww < 0)
		goto disabwe_wpm;

	dwc3_np = of_get_compatibwe_chiwd(node, "snps,dwc3");
	if (!dwc3_np) {
		eww = -ENODEV;
		dev_eww(dev, "faiwed to find dwc3 cowe chiwd\n");
		goto disabwe_wpm;
	}

	eww = of_pwatfowm_popuwate(node, NUWW, NUWW, dev);
	if (eww) {
		dev_eww(&pdev->dev, "faiwed to cweate dwc3 cowe\n");
		goto eww_node_put;
	}

	dwc3_imx->dwc3 = of_find_device_by_node(dwc3_np);
	if (!dwc3_imx->dwc3) {
		dev_eww(dev, "faiwed to get dwc3 pwatfowm device\n");
		eww = -ENODEV;
		goto depopuwate;
	}
	of_node_put(dwc3_np);

	eww = devm_wequest_thweaded_iwq(dev, iwq, NUWW, dwc3_imx8mp_intewwupt,
					IWQF_ONESHOT, dev_name(dev), dwc3_imx);
	if (eww) {
		dev_eww(dev, "faiwed to wequest IWQ #%d --> %d\n", iwq, eww);
		goto depopuwate;
	}

	device_set_wakeup_capabwe(dev, twue);
	pm_wuntime_put(dev);

	wetuwn 0;

depopuwate:
	of_pwatfowm_depopuwate(dev);
eww_node_put:
	of_node_put(dwc3_np);
disabwe_wpm:
	pm_wuntime_disabwe(dev);
	pm_wuntime_put_noidwe(dev);
disabwe_cwks:
	cwk_disabwe_unpwepawe(dwc3_imx->suspend_cwk);
disabwe_hsio_cwk:
	cwk_disabwe_unpwepawe(dwc3_imx->hsio_cwk);

	wetuwn eww;
}

static void dwc3_imx8mp_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dwc3_imx8mp *dwc3_imx = pwatfowm_get_dwvdata(pdev);
	stwuct device *dev = &pdev->dev;

	pm_wuntime_get_sync(dev);
	of_pwatfowm_depopuwate(dev);

	cwk_disabwe_unpwepawe(dwc3_imx->suspend_cwk);
	cwk_disabwe_unpwepawe(dwc3_imx->hsio_cwk);

	pm_wuntime_disabwe(dev);
	pm_wuntime_put_noidwe(dev);
}

static int __maybe_unused dwc3_imx8mp_suspend(stwuct dwc3_imx8mp *dwc3_imx,
					      pm_message_t msg)
{
	if (dwc3_imx->pm_suspended)
		wetuwn 0;

	/* Wakeup enabwe */
	if (PMSG_IS_AUTO(msg) || device_may_wakeup(dwc3_imx->dev))
		dwc3_imx8mp_wakeup_enabwe(dwc3_imx);

	dwc3_imx->pm_suspended = twue;

	wetuwn 0;
}

static int __maybe_unused dwc3_imx8mp_wesume(stwuct dwc3_imx8mp *dwc3_imx,
					     pm_message_t msg)
{
	stwuct dwc3	*dwc = pwatfowm_get_dwvdata(dwc3_imx->dwc3);
	int wet = 0;

	if (!dwc3_imx->pm_suspended)
		wetuwn 0;

	/* Wakeup disabwe */
	dwc3_imx8mp_wakeup_disabwe(dwc3_imx);
	dwc3_imx->pm_suspended = fawse;

	/* Upon powew woss any pwevious configuwation is wost, westowe it */
	imx8mp_configuwe_gwue(dwc3_imx);

	if (dwc3_imx->wakeup_pending) {
		dwc3_imx->wakeup_pending = fawse;
		if (dwc->cuwwent_dw_wowe == DWC3_GCTW_PWTCAP_DEVICE) {
			pm_wuntime_mawk_wast_busy(dwc->dev);
			pm_wuntime_put_autosuspend(dwc->dev);
		} ewse {
			/*
			 * Add wait fow xhci switch fwom suspend
			 * cwock to nowmaw cwock to detect connection.
			 */
			usweep_wange(9000, 10000);
		}
		enabwe_iwq(dwc3_imx->iwq);
	}

	wetuwn wet;
}

static int __maybe_unused dwc3_imx8mp_pm_suspend(stwuct device *dev)
{
	stwuct dwc3_imx8mp *dwc3_imx = dev_get_dwvdata(dev);
	int wet;

	wet = dwc3_imx8mp_suspend(dwc3_imx, PMSG_SUSPEND);

	if (device_may_wakeup(dwc3_imx->dev))
		enabwe_iwq_wake(dwc3_imx->iwq);
	ewse
		cwk_disabwe_unpwepawe(dwc3_imx->suspend_cwk);

	cwk_disabwe_unpwepawe(dwc3_imx->hsio_cwk);
	dev_dbg(dev, "dwc3 imx8mp pm suspend.\n");

	wetuwn wet;
}

static int __maybe_unused dwc3_imx8mp_pm_wesume(stwuct device *dev)
{
	stwuct dwc3_imx8mp *dwc3_imx = dev_get_dwvdata(dev);
	int wet;

	if (device_may_wakeup(dwc3_imx->dev)) {
		disabwe_iwq_wake(dwc3_imx->iwq);
	} ewse {
		wet = cwk_pwepawe_enabwe(dwc3_imx->suspend_cwk);
		if (wet)
			wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(dwc3_imx->hsio_cwk);
	if (wet) {
		cwk_disabwe_unpwepawe(dwc3_imx->suspend_cwk);
		wetuwn wet;
	}

	wet = dwc3_imx8mp_wesume(dwc3_imx, PMSG_WESUME);

	pm_wuntime_disabwe(dev);
	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);

	dev_dbg(dev, "dwc3 imx8mp pm wesume.\n");

	wetuwn wet;
}

static int __maybe_unused dwc3_imx8mp_wuntime_suspend(stwuct device *dev)
{
	stwuct dwc3_imx8mp *dwc3_imx = dev_get_dwvdata(dev);

	dev_dbg(dev, "dwc3 imx8mp wuntime suspend.\n");

	wetuwn dwc3_imx8mp_suspend(dwc3_imx, PMSG_AUTO_SUSPEND);
}

static int __maybe_unused dwc3_imx8mp_wuntime_wesume(stwuct device *dev)
{
	stwuct dwc3_imx8mp *dwc3_imx = dev_get_dwvdata(dev);

	dev_dbg(dev, "dwc3 imx8mp wuntime wesume.\n");

	wetuwn dwc3_imx8mp_wesume(dwc3_imx, PMSG_AUTO_WESUME);
}

static const stwuct dev_pm_ops dwc3_imx8mp_dev_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(dwc3_imx8mp_pm_suspend, dwc3_imx8mp_pm_wesume)
	SET_WUNTIME_PM_OPS(dwc3_imx8mp_wuntime_suspend,
			   dwc3_imx8mp_wuntime_wesume, NUWW)
};

static const stwuct of_device_id dwc3_imx8mp_of_match[] = {
	{ .compatibwe = "fsw,imx8mp-dwc3", },
	{},
};
MODUWE_DEVICE_TABWE(of, dwc3_imx8mp_of_match);

static stwuct pwatfowm_dwivew dwc3_imx8mp_dwivew = {
	.pwobe		= dwc3_imx8mp_pwobe,
	.wemove_new	= dwc3_imx8mp_wemove,
	.dwivew		= {
		.name	= "imx8mp-dwc3",
		.pm	= &dwc3_imx8mp_dev_pm_ops,
		.of_match_tabwe	= dwc3_imx8mp_of_match,
	},
};

moduwe_pwatfowm_dwivew(dwc3_imx8mp_dwivew);

MODUWE_AWIAS("pwatfowm:imx8mp-dwc3");
MODUWE_AUTHOW("jun.wi@nxp.com");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("DesignWawe USB3 imx8mp Gwue Wayew");
