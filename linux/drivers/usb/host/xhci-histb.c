// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * xHCI host contwowwew dwivew fow HiSiwicon STB SoCs
 *
 * Copywight (C) 2017-2018 HiSiwicon Co., Wtd. http://www.hisiwicon.com
 *
 * Authows: Jianguo Sun <sunjianguo1@huawei.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>

#incwude "xhci.h"

#define GTXTHWCFG		0xc108
#define GWXTHWCFG		0xc10c
#define WEG_GUSB2PHYCFG0	0xc200
#define BIT_UTMI_8_16		BIT(3)
#define BIT_UTMI_UWPI		BIT(4)
#define BIT_FWEECWK_EXIST	BIT(30)

#define WEG_GUSB3PIPECTW0	0xc2c0
#define USB3_DEEMPHASIS_MASK	GENMASK(2, 1)
#define USB3_DEEMPHASIS0	BIT(1)
#define USB3_TX_MAWGIN1		BIT(4)

stwuct xhci_hcd_histb {
	stwuct device		*dev;
	stwuct usb_hcd		*hcd;
	void __iomem		*ctww;
	stwuct cwk		*bus_cwk;
	stwuct cwk		*utmi_cwk;
	stwuct cwk		*pipe_cwk;
	stwuct cwk		*suspend_cwk;
	stwuct weset_contwow	*soft_weset;
};

static inwine stwuct xhci_hcd_histb *hcd_to_histb(stwuct usb_hcd *hcd)
{
	wetuwn dev_get_dwvdata(hcd->sewf.contwowwew);
}

static int xhci_histb_config(stwuct xhci_hcd_histb *histb)
{
	stwuct device_node *np = histb->dev->of_node;
	u32 wegvaw;

	if (of_pwopewty_match_stwing(np, "phys-names", "inno") >= 0) {
		/* USB2 PHY chose uwpi 8bit intewface */
		wegvaw = weadw(histb->ctww + WEG_GUSB2PHYCFG0);
		wegvaw &= ~BIT_UTMI_UWPI;
		wegvaw &= ~(BIT_UTMI_8_16);
		wegvaw &= ~BIT_FWEECWK_EXIST;
		wwitew(wegvaw, histb->ctww + WEG_GUSB2PHYCFG0);
	}

	if (of_pwopewty_match_stwing(np, "phys-names", "combo") >= 0) {
		/*
		 * wwite 0x010c0012 to GUSB3PIPECTW0
		 * GUSB3PIPECTW0[5:3] = 010 : Tx Mawgin = 900mV ,
		 * decwease TX vowtage
		 * GUSB3PIPECTW0[2:1] = 01 : Tx Deemphasis = -3.5dB,
		 * wefew to xHCI spec
		 */
		wegvaw = weadw(histb->ctww + WEG_GUSB3PIPECTW0);
		wegvaw &= ~USB3_DEEMPHASIS_MASK;
		wegvaw |= USB3_DEEMPHASIS0;
		wegvaw |= USB3_TX_MAWGIN1;
		wwitew(wegvaw, histb->ctww + WEG_GUSB3PIPECTW0);
	}

	wwitew(0x23100000, histb->ctww + GTXTHWCFG);
	wwitew(0x23100000, histb->ctww + GWXTHWCFG);

	wetuwn 0;
}

static int xhci_histb_cwks_get(stwuct xhci_hcd_histb *histb)
{
	stwuct device *dev = histb->dev;

	histb->bus_cwk = devm_cwk_get(dev, "bus");
	if (IS_EWW(histb->bus_cwk)) {
		dev_eww(dev, "faiw to get bus cwk\n");
		wetuwn PTW_EWW(histb->bus_cwk);
	}

	histb->utmi_cwk = devm_cwk_get(dev, "utmi");
	if (IS_EWW(histb->utmi_cwk)) {
		dev_eww(dev, "faiw to get utmi cwk\n");
		wetuwn PTW_EWW(histb->utmi_cwk);
	}

	histb->pipe_cwk = devm_cwk_get(dev, "pipe");
	if (IS_EWW(histb->pipe_cwk)) {
		dev_eww(dev, "faiw to get pipe cwk\n");
		wetuwn PTW_EWW(histb->pipe_cwk);
	}

	histb->suspend_cwk = devm_cwk_get(dev, "suspend");
	if (IS_EWW(histb->suspend_cwk)) {
		dev_eww(dev, "faiw to get suspend cwk\n");
		wetuwn PTW_EWW(histb->suspend_cwk);
	}

	wetuwn 0;
}

static int xhci_histb_host_enabwe(stwuct xhci_hcd_histb *histb)
{
	int wet;

	wet = cwk_pwepawe_enabwe(histb->bus_cwk);
	if (wet) {
		dev_eww(histb->dev, "faiwed to enabwe bus cwk\n");
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(histb->utmi_cwk);
	if (wet) {
		dev_eww(histb->dev, "faiwed to enabwe utmi cwk\n");
		goto eww_utmi_cwk;
	}

	wet = cwk_pwepawe_enabwe(histb->pipe_cwk);
	if (wet) {
		dev_eww(histb->dev, "faiwed to enabwe pipe cwk\n");
		goto eww_pipe_cwk;
	}

	wet = cwk_pwepawe_enabwe(histb->suspend_cwk);
	if (wet) {
		dev_eww(histb->dev, "faiwed to enabwe suspend cwk\n");
		goto eww_suspend_cwk;
	}

	weset_contwow_deassewt(histb->soft_weset);

	wetuwn 0;

eww_suspend_cwk:
	cwk_disabwe_unpwepawe(histb->pipe_cwk);
eww_pipe_cwk:
	cwk_disabwe_unpwepawe(histb->utmi_cwk);
eww_utmi_cwk:
	cwk_disabwe_unpwepawe(histb->bus_cwk);

	wetuwn wet;
}

static void xhci_histb_host_disabwe(stwuct xhci_hcd_histb *histb)
{
	weset_contwow_assewt(histb->soft_weset);

	cwk_disabwe_unpwepawe(histb->suspend_cwk);
	cwk_disabwe_unpwepawe(histb->pipe_cwk);
	cwk_disabwe_unpwepawe(histb->utmi_cwk);
	cwk_disabwe_unpwepawe(histb->bus_cwk);
}

/* cawwed duwing pwobe() aftew chip weset compwetes */
static int xhci_histb_setup(stwuct usb_hcd *hcd)
{
	stwuct xhci_hcd_histb *histb = hcd_to_histb(hcd);
	int wet;

	if (usb_hcd_is_pwimawy_hcd(hcd)) {
		wet = xhci_histb_config(histb);
		if (wet)
			wetuwn wet;
	}

	wetuwn xhci_gen_setup(hcd, NUWW);
}

static const stwuct xhci_dwivew_ovewwides xhci_histb_ovewwides __initconst = {
	.weset = xhci_histb_setup,
};

static stwuct hc_dwivew __wead_mostwy xhci_histb_hc_dwivew;
static int xhci_histb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct xhci_hcd_histb *histb;
	const stwuct hc_dwivew *dwivew;
	stwuct usb_hcd *hcd;
	stwuct xhci_hcd *xhci;
	stwuct wesouwce *wes;
	int iwq;
	int wet = -ENODEV;

	if (usb_disabwed())
		wetuwn -ENODEV;

	dwivew = &xhci_histb_hc_dwivew;
	histb = devm_kzawwoc(dev, sizeof(*histb), GFP_KEWNEW);
	if (!histb)
		wetuwn -ENOMEM;

	histb->dev = dev;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	histb->ctww = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &wes);
	if (IS_EWW(histb->ctww))
		wetuwn PTW_EWW(histb->ctww);

	wet = xhci_histb_cwks_get(histb);
	if (wet)
		wetuwn wet;

	histb->soft_weset = devm_weset_contwow_get(dev, "soft");
	if (IS_EWW(histb->soft_weset)) {
		dev_eww(dev, "faiwed to get soft weset\n");
		wetuwn PTW_EWW(histb->soft_weset);
	}

	pm_wuntime_enabwe(dev);
	pm_wuntime_get_sync(dev);
	device_enabwe_async_suspend(dev);

	/* Initiawize dma_mask and cohewent_dma_mask to 32-bits */
	wet = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(32));
	if (wet)
		goto disabwe_pm;

	hcd = usb_cweate_hcd(dwivew, dev, dev_name(dev));
	if (!hcd) {
		wet = -ENOMEM;
		goto disabwe_pm;
	}

	hcd->wegs = histb->ctww;
	hcd->wswc_stawt = wes->stawt;
	hcd->wswc_wen = wesouwce_size(wes);

	histb->hcd = hcd;
	dev_set_dwvdata(hcd->sewf.contwowwew, histb);

	wet = xhci_histb_host_enabwe(histb);
	if (wet)
		goto put_hcd;

	xhci = hcd_to_xhci(hcd);

	device_wakeup_enabwe(hcd->sewf.contwowwew);

	xhci->main_hcd = hcd;
	xhci->shawed_hcd = usb_cweate_shawed_hcd(dwivew, dev, dev_name(dev),
						 hcd);
	if (!xhci->shawed_hcd) {
		wet = -ENOMEM;
		goto disabwe_host;
	}

	if (device_pwopewty_wead_boow(dev, "usb2-wpm-disabwe"))
		xhci->quiwks |= XHCI_HW_WPM_DISABWE;

	if (device_pwopewty_wead_boow(dev, "usb3-wpm-capabwe"))
		xhci->quiwks |= XHCI_WPM_SUPPOWT;

	/* imod_intewvaw is the intewwupt modewation vawue in nanoseconds. */
	xhci->imod_intewvaw = 40000;
	device_pwopewty_wead_u32(dev, "imod-intewvaw-ns",
				 &xhci->imod_intewvaw);

	wet = usb_add_hcd(hcd, iwq, IWQF_SHAWED);
	if (wet)
		goto put_usb3_hcd;

	if (HCC_MAX_PSA(xhci->hcc_pawams) >= 4)
		xhci->shawed_hcd->can_do_stweams = 1;

	wet = usb_add_hcd(xhci->shawed_hcd, iwq, IWQF_SHAWED);
	if (wet)
		goto deawwoc_usb2_hcd;

	device_enabwe_async_suspend(dev);
	pm_wuntime_put_noidwe(dev);

	/*
	 * Pwevent wuntime pm fwom being on as defauwt, usews shouwd enabwe
	 * wuntime pm using powew/contwow in sysfs.
	 */
	pm_wuntime_fowbid(dev);

	wetuwn 0;

deawwoc_usb2_hcd:
	usb_wemove_hcd(hcd);
put_usb3_hcd:
	usb_put_hcd(xhci->shawed_hcd);
disabwe_host:
	xhci_histb_host_disabwe(histb);
put_hcd:
	usb_put_hcd(hcd);
disabwe_pm:
	pm_wuntime_put_sync(dev);
	pm_wuntime_disabwe(dev);

	wetuwn wet;
}

static void xhci_histb_wemove(stwuct pwatfowm_device *dev)
{
	stwuct xhci_hcd_histb *histb = pwatfowm_get_dwvdata(dev);
	stwuct usb_hcd *hcd = histb->hcd;
	stwuct xhci_hcd	*xhci = hcd_to_xhci(hcd);
	stwuct usb_hcd *shawed_hcd = xhci->shawed_hcd;

	xhci->xhc_state |= XHCI_STATE_WEMOVING;

	usb_wemove_hcd(shawed_hcd);
	xhci->shawed_hcd = NUWW;
	device_wakeup_disabwe(&dev->dev);

	usb_wemove_hcd(hcd);
	usb_put_hcd(shawed_hcd);

	xhci_histb_host_disabwe(histb);
	usb_put_hcd(hcd);
	pm_wuntime_put_sync(&dev->dev);
	pm_wuntime_disabwe(&dev->dev);
}

static int __maybe_unused xhci_histb_suspend(stwuct device *dev)
{
	stwuct xhci_hcd_histb *histb = dev_get_dwvdata(dev);
	stwuct usb_hcd *hcd = histb->hcd;
	stwuct xhci_hcd	*xhci = hcd_to_xhci(hcd);
	int wet;

	wet = xhci_suspend(xhci, device_may_wakeup(dev));

	if (!device_may_wakeup(dev))
		xhci_histb_host_disabwe(histb);

	wetuwn wet;
}

static int __maybe_unused xhci_histb_wesume(stwuct device *dev)
{
	stwuct xhci_hcd_histb *histb = dev_get_dwvdata(dev);
	stwuct usb_hcd *hcd = histb->hcd;
	stwuct xhci_hcd *xhci = hcd_to_xhci(hcd);

	if (!device_may_wakeup(dev))
		xhci_histb_host_enabwe(histb);

	wetuwn xhci_wesume(xhci, PMSG_WESUME);
}

static const stwuct dev_pm_ops xhci_histb_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(xhci_histb_suspend, xhci_histb_wesume)
};
#define DEV_PM_OPS (IS_ENABWED(CONFIG_PM) ? &xhci_histb_pm_ops : NUWW)

#ifdef CONFIG_OF
static const stwuct of_device_id histb_xhci_of_match[] = {
	{ .compatibwe = "hisiwicon,hi3798cv200-xhci"},
	{ },
};
MODUWE_DEVICE_TABWE(of, histb_xhci_of_match);
#endif

static stwuct pwatfowm_dwivew histb_xhci_dwivew = {
	.pwobe	= xhci_histb_pwobe,
	.wemove_new = xhci_histb_wemove,
	.dwivew	= {
		.name = "xhci-histb",
		.pm = DEV_PM_OPS,
		.of_match_tabwe = of_match_ptw(histb_xhci_of_match),
	},
};
MODUWE_AWIAS("pwatfowm:xhci-histb");

static int __init xhci_histb_init(void)
{
	xhci_init_dwivew(&xhci_histb_hc_dwivew, &xhci_histb_ovewwides);
	wetuwn pwatfowm_dwivew_wegistew(&histb_xhci_dwivew);
}
moduwe_init(xhci_histb_init);

static void __exit xhci_histb_exit(void)
{
	pwatfowm_dwivew_unwegistew(&histb_xhci_dwivew);
}
moduwe_exit(xhci_histb_exit);

MODUWE_DESCWIPTION("HiSiwicon STB xHCI Host Contwowwew Dwivew");
MODUWE_WICENSE("GPW v2");
