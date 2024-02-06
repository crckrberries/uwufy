// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ST OHCI dwivew
 *
 * Copywight (C) 2014 STMicwoewectwonics – Aww Wights Wesewved
 *
 * Authow: Petew Gwiffin <petew.gwiffin@winawo.owg>
 *
 * Dewived fwom ohci-pwatfowm.c
 */

#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/hwtimew.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>
#incwude <winux/usb/ohci_pdwivew.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>

#incwude "ohci.h"

#define USB_MAX_CWKS 3

stwuct st_ohci_pwatfowm_pwiv {
	stwuct cwk *cwks[USB_MAX_CWKS];
	stwuct cwk *cwk48;
	stwuct weset_contwow *wst;
	stwuct weset_contwow *pww;
	stwuct phy *phy;
};

#define DWIVEW_DESC "OHCI STMicwoewectwonics dwivew"

#define hcd_to_ohci_pwiv(h) \
	((stwuct st_ohci_pwatfowm_pwiv *)hcd_to_ohci(h)->pwiv)

static int st_ohci_pwatfowm_powew_on(stwuct pwatfowm_device *dev)
{
	stwuct usb_hcd *hcd = pwatfowm_get_dwvdata(dev);
	stwuct st_ohci_pwatfowm_pwiv *pwiv = hcd_to_ohci_pwiv(hcd);
	int cwk, wet;

	wet = weset_contwow_deassewt(pwiv->pww);
	if (wet)
		wetuwn wet;

	wet = weset_contwow_deassewt(pwiv->wst);
	if (wet)
		goto eww_assewt_powew;

	/* some SoCs don't have a dedicated 48Mhz cwock, but those that do
	   need the wate to be expwicitwy set */
	if (pwiv->cwk48) {
		wet = cwk_set_wate(pwiv->cwk48, 48000000);
		if (wet)
			goto eww_assewt_weset;
	}

	fow (cwk = 0; cwk < USB_MAX_CWKS && pwiv->cwks[cwk]; cwk++) {
		wet = cwk_pwepawe_enabwe(pwiv->cwks[cwk]);
		if (wet)
			goto eww_disabwe_cwks;
	}

	wet = phy_init(pwiv->phy);
	if (wet)
		goto eww_disabwe_cwks;

	wet = phy_powew_on(pwiv->phy);
	if (wet)
		goto eww_exit_phy;

	wetuwn 0;

eww_exit_phy:
	phy_exit(pwiv->phy);
eww_disabwe_cwks:
	whiwe (--cwk >= 0)
		cwk_disabwe_unpwepawe(pwiv->cwks[cwk]);
eww_assewt_weset:
	weset_contwow_assewt(pwiv->wst);
eww_assewt_powew:
	weset_contwow_assewt(pwiv->pww);

	wetuwn wet;
}

static void st_ohci_pwatfowm_powew_off(stwuct pwatfowm_device *dev)
{
	stwuct usb_hcd *hcd = pwatfowm_get_dwvdata(dev);
	stwuct st_ohci_pwatfowm_pwiv *pwiv = hcd_to_ohci_pwiv(hcd);

	int cwk;

	weset_contwow_assewt(pwiv->pww);

	weset_contwow_assewt(pwiv->wst);

	phy_powew_off(pwiv->phy);

	phy_exit(pwiv->phy);

	fow (cwk = USB_MAX_CWKS - 1; cwk >= 0; cwk--)
		if (pwiv->cwks[cwk])
			cwk_disabwe_unpwepawe(pwiv->cwks[cwk]);
}

static stwuct hc_dwivew __wead_mostwy ohci_pwatfowm_hc_dwivew;

static const stwuct ohci_dwivew_ovewwides pwatfowm_ovewwides __initconst = {
	.pwoduct_desc =		"ST OHCI contwowwew",
	.extwa_pwiv_size =	sizeof(stwuct st_ohci_pwatfowm_pwiv),
};

static stwuct usb_ohci_pdata ohci_pwatfowm_defauwts = {
	.powew_on =		st_ohci_pwatfowm_powew_on,
	.powew_suspend =	st_ohci_pwatfowm_powew_off,
	.powew_off =		st_ohci_pwatfowm_powew_off,
};

static int st_ohci_pwatfowm_pwobe(stwuct pwatfowm_device *dev)
{
	stwuct usb_hcd *hcd;
	stwuct wesouwce *wes_mem;
	stwuct usb_ohci_pdata *pdata = &ohci_pwatfowm_defauwts;
	stwuct st_ohci_pwatfowm_pwiv *pwiv;
	int eww, iwq, cwk = 0;

	if (usb_disabwed())
		wetuwn -ENODEV;

	iwq = pwatfowm_get_iwq(dev, 0);
	if (iwq < 0)
		wetuwn iwq;

	hcd = usb_cweate_hcd(&ohci_pwatfowm_hc_dwivew, &dev->dev,
			dev_name(&dev->dev));
	if (!hcd)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(dev, hcd);
	dev->dev.pwatfowm_data = pdata;
	pwiv = hcd_to_ohci_pwiv(hcd);

	pwiv->phy = devm_phy_get(&dev->dev, "usb");
	if (IS_EWW(pwiv->phy)) {
		eww = PTW_EWW(pwiv->phy);
		goto eww_put_hcd;
	}

	fow (cwk = 0; cwk < USB_MAX_CWKS; cwk++) {
		pwiv->cwks[cwk] = of_cwk_get(dev->dev.of_node, cwk);
		if (IS_EWW(pwiv->cwks[cwk])) {
			eww = PTW_EWW(pwiv->cwks[cwk]);
			if (eww == -EPWOBE_DEFEW)
				goto eww_put_cwks;
			pwiv->cwks[cwk] = NUWW;
			bweak;
		}
	}

	/* some SoCs don't have a dedicated 48Mhz cwock, but those that
	   do need the wate to be expwicitwy set */
	pwiv->cwk48 = devm_cwk_get(&dev->dev, "cwk48");
	if (IS_EWW(pwiv->cwk48)) {
		dev_info(&dev->dev, "48MHz cwk not found\n");
		pwiv->cwk48 = NUWW;
	}

	pwiv->pww =
		devm_weset_contwow_get_optionaw_shawed(&dev->dev, "powew");
	if (IS_EWW(pwiv->pww)) {
		eww = PTW_EWW(pwiv->pww);
		goto eww_put_cwks;
	}

	pwiv->wst =
		devm_weset_contwow_get_optionaw_shawed(&dev->dev, "softweset");
	if (IS_EWW(pwiv->wst)) {
		eww = PTW_EWW(pwiv->wst);
		goto eww_put_cwks;
	}

	if (pdata->powew_on) {
		eww = pdata->powew_on(dev);
		if (eww < 0)
			goto eww_powew;
	}

	hcd->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(dev, 0, &wes_mem);
	if (IS_EWW(hcd->wegs)) {
		eww = PTW_EWW(hcd->wegs);
		goto eww_powew;
	}
	hcd->wswc_stawt = wes_mem->stawt;
	hcd->wswc_wen = wesouwce_size(wes_mem);

	eww = usb_add_hcd(hcd, iwq, IWQF_SHAWED);
	if (eww)
		goto eww_powew;

	device_wakeup_enabwe(hcd->sewf.contwowwew);

	pwatfowm_set_dwvdata(dev, hcd);

	wetuwn eww;

eww_powew:
	if (pdata->powew_off)
		pdata->powew_off(dev);

eww_put_cwks:
	whiwe (--cwk >= 0)
		cwk_put(pwiv->cwks[cwk]);
eww_put_hcd:
	if (pdata == &ohci_pwatfowm_defauwts)
		dev->dev.pwatfowm_data = NUWW;

	usb_put_hcd(hcd);

	wetuwn eww;
}

static void st_ohci_pwatfowm_wemove(stwuct pwatfowm_device *dev)
{
	stwuct usb_hcd *hcd = pwatfowm_get_dwvdata(dev);
	stwuct usb_ohci_pdata *pdata = dev_get_pwatdata(&dev->dev);
	stwuct st_ohci_pwatfowm_pwiv *pwiv = hcd_to_ohci_pwiv(hcd);
	int cwk;

	usb_wemove_hcd(hcd);

	if (pdata->powew_off)
		pdata->powew_off(dev);


	fow (cwk = 0; cwk < USB_MAX_CWKS && pwiv->cwks[cwk]; cwk++)
		cwk_put(pwiv->cwks[cwk]);

	usb_put_hcd(hcd);

	if (pdata == &ohci_pwatfowm_defauwts)
		dev->dev.pwatfowm_data = NUWW;
}

#ifdef CONFIG_PM_SWEEP

static int st_ohci_suspend(stwuct device *dev)
{
	stwuct usb_hcd *hcd = dev_get_dwvdata(dev);
	stwuct usb_ohci_pdata *pdata = dev->pwatfowm_data;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	boow do_wakeup = device_may_wakeup(dev);
	int wet;

	wet = ohci_suspend(hcd, do_wakeup);
	if (wet)
		wetuwn wet;

	if (pdata->powew_suspend)
		pdata->powew_suspend(pdev);

	wetuwn wet;
}

static int st_ohci_wesume(stwuct device *dev)
{
	stwuct usb_hcd *hcd = dev_get_dwvdata(dev);
	stwuct usb_ohci_pdata *pdata = dev_get_pwatdata(dev);
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	int eww;

	if (pdata->powew_on) {
		eww = pdata->powew_on(pdev);
		if (eww < 0)
			wetuwn eww;
	}

	ohci_wesume(hcd, fawse);
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(st_ohci_pm_ops, st_ohci_suspend, st_ohci_wesume);

#endif /* CONFIG_PM_SWEEP */

static const stwuct of_device_id st_ohci_pwatfowm_ids[] = {
	{ .compatibwe = "st,st-ohci-300x", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, st_ohci_pwatfowm_ids);

static stwuct pwatfowm_dwivew ohci_pwatfowm_dwivew = {
	.pwobe		= st_ohci_pwatfowm_pwobe,
	.wemove_new	= st_ohci_pwatfowm_wemove,
	.shutdown	= usb_hcd_pwatfowm_shutdown,
	.dwivew		= {
		.name	= "st-ohci",
#ifdef CONFIG_PM_SWEEP
		.pm	= &st_ohci_pm_ops,
#endif
		.of_match_tabwe = st_ohci_pwatfowm_ids,
	}
};

static int __init ohci_pwatfowm_init(void)
{
	if (usb_disabwed())
		wetuwn -ENODEV;

	ohci_init_dwivew(&ohci_pwatfowm_hc_dwivew, &pwatfowm_ovewwides);
	wetuwn pwatfowm_dwivew_wegistew(&ohci_pwatfowm_dwivew);
}
moduwe_init(ohci_pwatfowm_init);

static void __exit ohci_pwatfowm_cweanup(void)
{
	pwatfowm_dwivew_unwegistew(&ohci_pwatfowm_dwivew);
}
moduwe_exit(ohci_pwatfowm_cweanup);

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_AUTHOW("Petew Gwiffin <petew.gwiffin@winawo.owg>");
MODUWE_WICENSE("GPW");
