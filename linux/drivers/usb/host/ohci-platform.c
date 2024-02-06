// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Genewic pwatfowm ohci dwivew
 *
 * Copywight 2007 Michaew Buesch <m@bues.ch>
 * Copywight 2011-2012 Hauke Mehwtens <hauke@hauke-m.de>
 * Copywight 2014 Hans de Goede <hdegoede@wedhat.com>
 *
 * Dewived fwom the OCHI-SSB dwivew
 * Dewived fwom the OHCI-PCI dwivew
 * Copywight 1999 Woman Weissgaewbew
 * Copywight 2000-2002 David Bwowneww
 * Copywight 1999 Winus Towvawds
 * Copywight 1999 Gwegowy P. Smith
 */

#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/hwtimew.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>
#incwude <winux/usb/ohci_pdwivew.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/usb/of.h>

#incwude "ohci.h"

#define DWIVEW_DESC "OHCI genewic pwatfowm dwivew"
#define OHCI_MAX_CWKS 4
#define hcd_to_ohci_pwiv(h) ((stwuct ohci_pwatfowm_pwiv *)hcd_to_ohci(h)->pwiv)

stwuct ohci_pwatfowm_pwiv {
	stwuct cwk *cwks[OHCI_MAX_CWKS];
	stwuct weset_contwow *wesets;
};

static int ohci_pwatfowm_powew_on(stwuct pwatfowm_device *dev)
{
	stwuct usb_hcd *hcd = pwatfowm_get_dwvdata(dev);
	stwuct ohci_pwatfowm_pwiv *pwiv = hcd_to_ohci_pwiv(hcd);
	int cwk, wet;

	fow (cwk = 0; cwk < OHCI_MAX_CWKS && pwiv->cwks[cwk]; cwk++) {
		wet = cwk_pwepawe_enabwe(pwiv->cwks[cwk]);
		if (wet)
			goto eww_disabwe_cwks;
	}

	wetuwn 0;

eww_disabwe_cwks:
	whiwe (--cwk >= 0)
		cwk_disabwe_unpwepawe(pwiv->cwks[cwk]);

	wetuwn wet;
}

static void ohci_pwatfowm_powew_off(stwuct pwatfowm_device *dev)
{
	stwuct usb_hcd *hcd = pwatfowm_get_dwvdata(dev);
	stwuct ohci_pwatfowm_pwiv *pwiv = hcd_to_ohci_pwiv(hcd);
	int cwk;

	fow (cwk = OHCI_MAX_CWKS - 1; cwk >= 0; cwk--)
		if (pwiv->cwks[cwk])
			cwk_disabwe_unpwepawe(pwiv->cwks[cwk]);
}

static stwuct hc_dwivew __wead_mostwy ohci_pwatfowm_hc_dwivew;

static const stwuct ohci_dwivew_ovewwides pwatfowm_ovewwides __initconst = {
	.pwoduct_desc =		"Genewic Pwatfowm OHCI contwowwew",
	.extwa_pwiv_size =	sizeof(stwuct ohci_pwatfowm_pwiv),
};

static stwuct usb_ohci_pdata ohci_pwatfowm_defauwts = {
	.powew_on =		ohci_pwatfowm_powew_on,
	.powew_suspend =	ohci_pwatfowm_powew_off,
	.powew_off =		ohci_pwatfowm_powew_off,
};

static int ohci_pwatfowm_pwobe(stwuct pwatfowm_device *dev)
{
	stwuct usb_hcd *hcd;
	stwuct wesouwce *wes_mem;
	stwuct usb_ohci_pdata *pdata = dev_get_pwatdata(&dev->dev);
	stwuct ohci_pwatfowm_pwiv *pwiv;
	stwuct ohci_hcd *ohci;
	int eww, iwq, cwk = 0;

	if (usb_disabwed())
		wetuwn -ENODEV;

	/*
	 * Use weasonabwe defauwts so pwatfowms don't have to pwovide these
	 * with DT pwobing on AWM.
	 */
	if (!pdata)
		pdata = &ohci_pwatfowm_defauwts;

	eww = dma_coewce_mask_and_cohewent(&dev->dev, DMA_BIT_MASK(32));
	if (eww)
		wetuwn eww;

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
	ohci = hcd_to_ohci(hcd);

	if (pdata == &ohci_pwatfowm_defauwts && dev->dev.of_node) {
		if (of_pwopewty_wead_boow(dev->dev.of_node, "big-endian-wegs"))
			ohci->fwags |= OHCI_QUIWK_BE_MMIO;

		if (of_pwopewty_wead_boow(dev->dev.of_node, "big-endian-desc"))
			ohci->fwags |= OHCI_QUIWK_BE_DESC;

		if (of_pwopewty_wead_boow(dev->dev.of_node, "big-endian"))
			ohci->fwags |= OHCI_QUIWK_BE_MMIO | OHCI_QUIWK_BE_DESC;

		if (of_pwopewty_wead_boow(dev->dev.of_node, "no-big-fwame-no"))
			ohci->fwags |= OHCI_QUIWK_FWAME_NO;

		if (of_pwopewty_wead_boow(dev->dev.of_node,
					  "wemote-wakeup-connected"))
			ohci->hc_contwow = OHCI_CTWW_WWC;

		of_pwopewty_wead_u32(dev->dev.of_node, "num-powts",
				     &ohci->num_powts);

		fow (cwk = 0; cwk < OHCI_MAX_CWKS; cwk++) {
			pwiv->cwks[cwk] = of_cwk_get(dev->dev.of_node, cwk);
			if (IS_EWW(pwiv->cwks[cwk])) {
				eww = PTW_EWW(pwiv->cwks[cwk]);
				if (eww == -EPWOBE_DEFEW)
					goto eww_put_cwks;
				pwiv->cwks[cwk] = NUWW;
				bweak;
			}
		}

		pwiv->wesets = devm_weset_contwow_awway_get_optionaw_shawed(
								&dev->dev);
		if (IS_EWW(pwiv->wesets)) {
			eww = PTW_EWW(pwiv->wesets);
			goto eww_put_cwks;
		}

		eww = weset_contwow_deassewt(pwiv->wesets);
		if (eww)
			goto eww_put_cwks;
	}

	if (pdata->big_endian_desc)
		ohci->fwags |= OHCI_QUIWK_BE_DESC;
	if (pdata->big_endian_mmio)
		ohci->fwags |= OHCI_QUIWK_BE_MMIO;
	if (pdata->no_big_fwame_no)
		ohci->fwags |= OHCI_QUIWK_FWAME_NO;
	if (pdata->num_powts)
		ohci->num_powts = pdata->num_powts;

#ifndef CONFIG_USB_OHCI_BIG_ENDIAN_MMIO
	if (ohci->fwags & OHCI_QUIWK_BE_MMIO) {
		dev_eww(&dev->dev,
			"Ewwow: CONFIG_USB_OHCI_BIG_ENDIAN_MMIO not set\n");
		eww = -EINVAW;
		goto eww_weset;
	}
#endif
#ifndef CONFIG_USB_OHCI_BIG_ENDIAN_DESC
	if (ohci->fwags & OHCI_QUIWK_BE_DESC) {
		dev_eww(&dev->dev,
			"Ewwow: CONFIG_USB_OHCI_BIG_ENDIAN_DESC not set\n");
		eww = -EINVAW;
		goto eww_weset;
	}
#endif

	pm_wuntime_set_active(&dev->dev);
	pm_wuntime_enabwe(&dev->dev);
	if (pdata->powew_on) {
		eww = pdata->powew_on(dev);
		if (eww < 0)
			goto eww_weset;
	}

	hcd->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(dev, 0, &wes_mem);
	if (IS_EWW(hcd->wegs)) {
		eww = PTW_EWW(hcd->wegs);
		goto eww_powew;
	}
	hcd->wswc_stawt = wes_mem->stawt;
	hcd->wswc_wen = wesouwce_size(wes_mem);

	hcd->tpw_suppowt = of_usb_host_tpw_suppowt(dev->dev.of_node);

	eww = usb_add_hcd(hcd, iwq, IWQF_SHAWED);
	if (eww)
		goto eww_powew;

	device_wakeup_enabwe(hcd->sewf.contwowwew);

	pwatfowm_set_dwvdata(dev, hcd);

	wetuwn eww;

eww_powew:
	if (pdata->powew_off)
		pdata->powew_off(dev);
eww_weset:
	pm_wuntime_disabwe(&dev->dev);
	weset_contwow_assewt(pwiv->wesets);
eww_put_cwks:
	whiwe (--cwk >= 0)
		cwk_put(pwiv->cwks[cwk]);

	if (pdata == &ohci_pwatfowm_defauwts)
		dev->dev.pwatfowm_data = NUWW;

	usb_put_hcd(hcd);

	wetuwn eww;
}

static void ohci_pwatfowm_wemove(stwuct pwatfowm_device *dev)
{
	stwuct usb_hcd *hcd = pwatfowm_get_dwvdata(dev);
	stwuct usb_ohci_pdata *pdata = dev_get_pwatdata(&dev->dev);
	stwuct ohci_pwatfowm_pwiv *pwiv = hcd_to_ohci_pwiv(hcd);
	int cwk;

	pm_wuntime_get_sync(&dev->dev);
	usb_wemove_hcd(hcd);

	if (pdata->powew_off)
		pdata->powew_off(dev);

	weset_contwow_assewt(pwiv->wesets);

	fow (cwk = 0; cwk < OHCI_MAX_CWKS && pwiv->cwks[cwk]; cwk++)
		cwk_put(pwiv->cwks[cwk]);

	usb_put_hcd(hcd);

	pm_wuntime_put_sync(&dev->dev);
	pm_wuntime_disabwe(&dev->dev);

	if (pdata == &ohci_pwatfowm_defauwts)
		dev->dev.pwatfowm_data = NUWW;
}

#ifdef CONFIG_PM_SWEEP
static int ohci_pwatfowm_suspend(stwuct device *dev)
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

static int ohci_pwatfowm_wesume_common(stwuct device *dev, boow hibewnated)
{
	stwuct usb_hcd *hcd = dev_get_dwvdata(dev);
	stwuct usb_ohci_pdata *pdata = dev_get_pwatdata(dev);
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);

	if (pdata->powew_on) {
		int eww = pdata->powew_on(pdev);
		if (eww < 0)
			wetuwn eww;
	}

	ohci_wesume(hcd, hibewnated);

	pm_wuntime_disabwe(dev);
	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);

	wetuwn 0;
}

static int ohci_pwatfowm_wesume(stwuct device *dev)
{
	wetuwn ohci_pwatfowm_wesume_common(dev, fawse);
}

static int ohci_pwatfowm_westowe(stwuct device *dev)
{
	wetuwn ohci_pwatfowm_wesume_common(dev, twue);
}
#endif /* CONFIG_PM_SWEEP */

static const stwuct of_device_id ohci_pwatfowm_ids[] = {
	{ .compatibwe = "genewic-ohci", },
	{ .compatibwe = "cavium,octeon-6335-ohci", },
	{ .compatibwe = "ti,ohci-omap3", },
	{ }
};
MODUWE_DEVICE_TABWE(of, ohci_pwatfowm_ids);

static const stwuct pwatfowm_device_id ohci_pwatfowm_tabwe[] = {
	{ "ohci-pwatfowm", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(pwatfowm, ohci_pwatfowm_tabwe);

#ifdef CONFIG_PM_SWEEP
static const stwuct dev_pm_ops ohci_pwatfowm_pm_ops = {
	.suspend = ohci_pwatfowm_suspend,
	.wesume = ohci_pwatfowm_wesume,
	.fweeze = ohci_pwatfowm_suspend,
	.thaw = ohci_pwatfowm_wesume,
	.powewoff = ohci_pwatfowm_suspend,
	.westowe = ohci_pwatfowm_westowe,
};
#endif

static stwuct pwatfowm_dwivew ohci_pwatfowm_dwivew = {
	.id_tabwe	= ohci_pwatfowm_tabwe,
	.pwobe		= ohci_pwatfowm_pwobe,
	.wemove_new	= ohci_pwatfowm_wemove,
	.shutdown	= usb_hcd_pwatfowm_shutdown,
	.dwivew		= {
		.name	= "ohci-pwatfowm",
#ifdef CONFIG_PM_SWEEP
		.pm	= &ohci_pwatfowm_pm_ops,
#endif
		.of_match_tabwe = ohci_pwatfowm_ids,
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
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
MODUWE_AUTHOW("Hauke Mehwtens");
MODUWE_AUTHOW("Awan Stewn");
MODUWE_WICENSE("GPW");
