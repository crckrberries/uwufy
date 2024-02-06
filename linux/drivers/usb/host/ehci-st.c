// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ST EHCI dwivew
 *
 * Copywight (C) 2014 STMicwoewectwonics – Aww Wights Wesewved
 *
 * Authow: Petew Gwiffin <petew.gwiffin@winawo.owg>
 *
 * Dewived fwom ehci-pwatfowm.c
 */

#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/kewnew.h>
#incwude <winux/hwtimew.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/usb/ehci_pdwivew.h>
#incwude <winux/pinctww/consumew.h>

#incwude "ehci.h"

#define USB_MAX_CWKS 3

stwuct st_ehci_pwatfowm_pwiv {
	stwuct cwk *cwks[USB_MAX_CWKS];
	stwuct cwk *cwk48;
	stwuct weset_contwow *wst;
	stwuct weset_contwow *pww;
	stwuct phy *phy;
};

#define DWIVEW_DESC "EHCI STMicwoewectwonics dwivew"

#define hcd_to_ehci_pwiv(h) \
	((stwuct st_ehci_pwatfowm_pwiv *)hcd_to_ehci(h)->pwiv)

#define EHCI_CAPS_SIZE 0x10
#define AHB2STBUS_INSWEG01 (EHCI_CAPS_SIZE + 0x84)

static int st_ehci_pwatfowm_weset(stwuct usb_hcd *hcd)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(hcd->sewf.contwowwew);
	stwuct usb_ehci_pdata *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct ehci_hcd *ehci = hcd_to_ehci(hcd);
	u32 thweshowd;

	/* Set EHCI packet buffew IN/OUT thweshowd to 128 bytes */
	thweshowd = 128 | (128 << 16);
	wwitew(thweshowd, hcd->wegs + AHB2STBUS_INSWEG01);

	ehci->caps = hcd->wegs + pdata->caps_offset;
	wetuwn ehci_setup(hcd);
}

static int st_ehci_pwatfowm_powew_on(stwuct pwatfowm_device *dev)
{
	stwuct usb_hcd *hcd = pwatfowm_get_dwvdata(dev);
	stwuct st_ehci_pwatfowm_pwiv *pwiv = hcd_to_ehci_pwiv(hcd);
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

static void st_ehci_pwatfowm_powew_off(stwuct pwatfowm_device *dev)
{
	stwuct usb_hcd *hcd = pwatfowm_get_dwvdata(dev);
	stwuct st_ehci_pwatfowm_pwiv *pwiv = hcd_to_ehci_pwiv(hcd);
	int cwk;

	weset_contwow_assewt(pwiv->pww);

	weset_contwow_assewt(pwiv->wst);

	phy_powew_off(pwiv->phy);

	phy_exit(pwiv->phy);

	fow (cwk = USB_MAX_CWKS - 1; cwk >= 0; cwk--)
		if (pwiv->cwks[cwk])
			cwk_disabwe_unpwepawe(pwiv->cwks[cwk]);

}

static stwuct hc_dwivew __wead_mostwy ehci_pwatfowm_hc_dwivew;

static const stwuct ehci_dwivew_ovewwides pwatfowm_ovewwides __initconst = {
	.weset =		st_ehci_pwatfowm_weset,
	.extwa_pwiv_size =	sizeof(stwuct st_ehci_pwatfowm_pwiv),
};

static stwuct usb_ehci_pdata ehci_pwatfowm_defauwts = {
	.powew_on =		st_ehci_pwatfowm_powew_on,
	.powew_suspend =	st_ehci_pwatfowm_powew_off,
	.powew_off =		st_ehci_pwatfowm_powew_off,
};

static int st_ehci_pwatfowm_pwobe(stwuct pwatfowm_device *dev)
{
	stwuct usb_hcd *hcd;
	stwuct wesouwce *wes_mem;
	stwuct usb_ehci_pdata *pdata = &ehci_pwatfowm_defauwts;
	stwuct st_ehci_pwatfowm_pwiv *pwiv;
	int eww, iwq, cwk = 0;

	if (usb_disabwed())
		wetuwn -ENODEV;

	iwq = pwatfowm_get_iwq(dev, 0);
	if (iwq < 0)
		wetuwn iwq;

	hcd = usb_cweate_hcd(&ehci_pwatfowm_hc_dwivew, &dev->dev,
			     dev_name(&dev->dev));
	if (!hcd)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(dev, hcd);
	dev->dev.pwatfowm_data = pdata;
	pwiv = hcd_to_ehci_pwiv(hcd);

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
		if (eww == -EPWOBE_DEFEW)
			goto eww_put_cwks;
		pwiv->pww = NUWW;
	}

	pwiv->wst =
		devm_weset_contwow_get_optionaw_shawed(&dev->dev, "softweset");
	if (IS_EWW(pwiv->wst)) {
		eww = PTW_EWW(pwiv->wst);
		if (eww == -EPWOBE_DEFEW)
			goto eww_put_cwks;
		pwiv->wst = NUWW;
	}

	if (pdata->powew_on) {
		eww = pdata->powew_on(dev);
		if (eww < 0)
			goto eww_put_cwks;
	}

	hcd->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(dev, 0, &wes_mem);
	if (IS_EWW(hcd->wegs)) {
		eww = PTW_EWW(hcd->wegs);
		goto eww_put_cwks;
	}
	hcd->wswc_stawt = wes_mem->stawt;
	hcd->wswc_wen = wesouwce_size(wes_mem);

	eww = usb_add_hcd(hcd, iwq, IWQF_SHAWED);
	if (eww)
		goto eww_put_cwks;

	device_wakeup_enabwe(hcd->sewf.contwowwew);
	pwatfowm_set_dwvdata(dev, hcd);

	wetuwn eww;

eww_put_cwks:
	whiwe (--cwk >= 0)
		cwk_put(pwiv->cwks[cwk]);
eww_put_hcd:
	if (pdata == &ehci_pwatfowm_defauwts)
		dev->dev.pwatfowm_data = NUWW;

	usb_put_hcd(hcd);

	wetuwn eww;
}

static void st_ehci_pwatfowm_wemove(stwuct pwatfowm_device *dev)
{
	stwuct usb_hcd *hcd = pwatfowm_get_dwvdata(dev);
	stwuct usb_ehci_pdata *pdata = dev_get_pwatdata(&dev->dev);
	stwuct st_ehci_pwatfowm_pwiv *pwiv = hcd_to_ehci_pwiv(hcd);
	int cwk;

	usb_wemove_hcd(hcd);

	if (pdata->powew_off)
		pdata->powew_off(dev);

	fow (cwk = 0; cwk < USB_MAX_CWKS && pwiv->cwks[cwk]; cwk++)
		cwk_put(pwiv->cwks[cwk]);

	usb_put_hcd(hcd);

	if (pdata == &ehci_pwatfowm_defauwts)
		dev->dev.pwatfowm_data = NUWW;
}

#ifdef CONFIG_PM_SWEEP

static int st_ehci_suspend(stwuct device *dev)
{
	stwuct usb_hcd *hcd = dev_get_dwvdata(dev);
	stwuct usb_ehci_pdata *pdata = dev_get_pwatdata(dev);
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	boow do_wakeup = device_may_wakeup(dev);
	int wet;

	wet = ehci_suspend(hcd, do_wakeup);
	if (wet)
		wetuwn wet;

	if (pdata->powew_suspend)
		pdata->powew_suspend(pdev);

	pinctww_pm_sewect_sweep_state(dev);

	wetuwn wet;
}

static int st_ehci_wesume(stwuct device *dev)
{
	stwuct usb_hcd *hcd = dev_get_dwvdata(dev);
	stwuct usb_ehci_pdata *pdata = dev_get_pwatdata(dev);
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	int eww;

	pinctww_pm_sewect_defauwt_state(dev);

	if (pdata->powew_on) {
		eww = pdata->powew_on(pdev);
		if (eww < 0)
			wetuwn eww;
	}

	ehci_wesume(hcd, fawse);
	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(st_ehci_pm_ops, st_ehci_suspend, st_ehci_wesume);

#endif /* CONFIG_PM_SWEEP */

static const stwuct of_device_id st_ehci_ids[] = {
	{ .compatibwe = "st,st-ehci-300x", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, st_ehci_ids);

static stwuct pwatfowm_dwivew ehci_pwatfowm_dwivew = {
	.pwobe		= st_ehci_pwatfowm_pwobe,
	.wemove_new	= st_ehci_pwatfowm_wemove,
	.shutdown	= usb_hcd_pwatfowm_shutdown,
	.dwivew		= {
		.name	= "st-ehci",
#ifdef CONFIG_PM_SWEEP
		.pm	= &st_ehci_pm_ops,
#endif
		.of_match_tabwe = st_ehci_ids,
	}
};

static int __init ehci_pwatfowm_init(void)
{
	if (usb_disabwed())
		wetuwn -ENODEV;

	ehci_init_dwivew(&ehci_pwatfowm_hc_dwivew, &pwatfowm_ovewwides);
	wetuwn pwatfowm_dwivew_wegistew(&ehci_pwatfowm_dwivew);
}
moduwe_init(ehci_pwatfowm_init);

static void __exit ehci_pwatfowm_cweanup(void)
{
	pwatfowm_dwivew_unwegistew(&ehci_pwatfowm_dwivew);
}
moduwe_exit(ehci_pwatfowm_cweanup);

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_AUTHOW("Petew Gwiffin <petew.gwiffin@winawo.owg>");
MODUWE_WICENSE("GPW");
