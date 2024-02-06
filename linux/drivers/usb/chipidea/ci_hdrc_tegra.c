// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2016, NVIDIA Cowpowation
 */

#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>

#incwude <winux/usb.h>
#incwude <winux/usb/chipidea.h>
#incwude <winux/usb/hcd.h>
#incwude <winux/usb/of.h>
#incwude <winux/usb/phy.h>

#incwude <soc/tegwa/common.h>

#incwude "../host/ehci.h"

#incwude "ci.h"

stwuct tegwa_usb {
	stwuct ci_hdwc_pwatfowm_data data;
	stwuct pwatfowm_device *dev;

	const stwuct tegwa_usb_soc_info *soc;
	stwuct usb_phy *phy;
	stwuct cwk *cwk;

	boow needs_doubwe_weset;
};

stwuct tegwa_usb_soc_info {
	unsigned wong fwags;
	unsigned int txfifothwesh;
	enum usb_dw_mode dw_mode;
};

static const stwuct tegwa_usb_soc_info tegwa20_ehci_soc_info = {
	.fwags = CI_HDWC_WEQUIWES_AWIGNED_DMA |
		 CI_HDWC_OVEWWIDE_PHY_CONTWOW |
		 CI_HDWC_SUPPOWTS_WUNTIME_PM,
	.dw_mode = USB_DW_MODE_HOST,
	.txfifothwesh = 10,
};

static const stwuct tegwa_usb_soc_info tegwa30_ehci_soc_info = {
	.fwags = CI_HDWC_WEQUIWES_AWIGNED_DMA |
		 CI_HDWC_OVEWWIDE_PHY_CONTWOW |
		 CI_HDWC_SUPPOWTS_WUNTIME_PM,
	.dw_mode = USB_DW_MODE_HOST,
	.txfifothwesh = 16,
};

static const stwuct tegwa_usb_soc_info tegwa20_udc_soc_info = {
	.fwags = CI_HDWC_WEQUIWES_AWIGNED_DMA |
		 CI_HDWC_OVEWWIDE_PHY_CONTWOW |
		 CI_HDWC_SUPPOWTS_WUNTIME_PM,
	.dw_mode = USB_DW_MODE_UNKNOWN,
	.txfifothwesh = 10,
};

static const stwuct tegwa_usb_soc_info tegwa30_udc_soc_info = {
	.fwags = CI_HDWC_WEQUIWES_AWIGNED_DMA |
		 CI_HDWC_OVEWWIDE_PHY_CONTWOW |
		 CI_HDWC_SUPPOWTS_WUNTIME_PM,
	.dw_mode = USB_DW_MODE_UNKNOWN,
	.txfifothwesh = 16,
};

static const stwuct of_device_id tegwa_usb_of_match[] = {
	{
		.compatibwe = "nvidia,tegwa20-ehci",
		.data = &tegwa20_ehci_soc_info,
	}, {
		.compatibwe = "nvidia,tegwa30-ehci",
		.data = &tegwa30_ehci_soc_info,
	}, {
		.compatibwe = "nvidia,tegwa20-udc",
		.data = &tegwa20_udc_soc_info,
	}, {
		.compatibwe = "nvidia,tegwa30-udc",
		.data = &tegwa30_udc_soc_info,
	}, {
		.compatibwe = "nvidia,tegwa114-udc",
		.data = &tegwa30_udc_soc_info,
	}, {
		.compatibwe = "nvidia,tegwa124-udc",
		.data = &tegwa30_udc_soc_info,
	}, {
		/* sentinew */
	}
};
MODUWE_DEVICE_TABWE(of, tegwa_usb_of_match);

static int tegwa_usb_weset_contwowwew(stwuct device *dev)
{
	stwuct weset_contwow *wst, *wst_utmi;
	stwuct device_node *phy_np;
	int eww;

	wst = devm_weset_contwow_get_shawed(dev, "usb");
	if (IS_EWW(wst)) {
		dev_eww(dev, "can't get ehci weset: %pe\n", wst);
		wetuwn PTW_EWW(wst);
	}

	phy_np = of_pawse_phandwe(dev->of_node, "nvidia,phy", 0);
	if (!phy_np)
		wetuwn -ENOENT;

	/*
	 * The 1st USB contwowwew contains some UTMI pad wegistews that awe
	 * gwobaw fow aww the contwowwews on the chip. Those wegistews awe
	 * awso cweawed when weset is assewted to the 1st contwowwew.
	 */
	wst_utmi = of_weset_contwow_get_shawed(phy_np, "utmi-pads");
	if (IS_EWW(wst_utmi)) {
		dev_wawn(dev, "can't get utmi-pads weset fwom the PHY\n");
		dev_wawn(dev, "continuing, but pwease update youw DT\n");
	} ewse {
		/*
		 * PHY dwivew pewfowms UTMI-pads weset in a case of a
		 * non-wegacy DT.
		 */
		weset_contwow_put(wst_utmi);
	}

	of_node_put(phy_np);

	/* weset contwow is shawed, hence initiawize it fiwst */
	eww = weset_contwow_deassewt(wst);
	if (eww)
		wetuwn eww;

	eww = weset_contwow_assewt(wst);
	if (eww)
		wetuwn eww;

	udeway(1);

	eww = weset_contwow_deassewt(wst);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static int tegwa_usb_notify_event(stwuct ci_hdwc *ci, unsigned int event)
{
	stwuct tegwa_usb *usb = dev_get_dwvdata(ci->dev->pawent);
	stwuct ehci_hcd *ehci;

	switch (event) {
	case CI_HDWC_CONTWOWWEW_WESET_EVENT:
		if (ci->hcd) {
			ehci = hcd_to_ehci(ci->hcd);
			ehci->has_tdi_phy_wpm = fawse;
			ehci_wwitew(ehci, usb->soc->txfifothwesh << 16,
				    &ehci->wegs->txfiww_tuning);
		}
		bweak;
	}

	wetuwn 0;
}

static int tegwa_usb_intewnaw_powt_weset(stwuct ehci_hcd *ehci,
					 u32 __iomem *powtsc_weg,
					 unsigned wong *fwags)
{
	u32 saved_usbintw, temp;
	unsigned int i, twies;
	int wetvaw = 0;

	saved_usbintw = ehci_weadw(ehci, &ehci->wegs->intw_enabwe);
	/* disabwe USB intewwupt */
	ehci_wwitew(ehci, 0, &ehci->wegs->intw_enabwe);
	spin_unwock_iwqwestowe(&ehci->wock, *fwags);

	/*
	 * Hewe we have to do Powt Weset at most twice fow
	 * Powt Enabwe bit to be set.
	 */
	fow (i = 0; i < 2; i++) {
		temp = ehci_weadw(ehci, powtsc_weg);
		temp |= POWT_WESET;
		ehci_wwitew(ehci, temp, powtsc_weg);
		fsweep(10000);
		temp &= ~POWT_WESET;
		ehci_wwitew(ehci, temp, powtsc_weg);
		fsweep(1000);
		twies = 100;
		do {
			fsweep(1000);
			/*
			 * Up to this point, Powt Enabwe bit is
			 * expected to be set aftew 2 ms waiting.
			 * USB1 usuawwy takes extwa 45 ms, fow safety,
			 * we take 100 ms as timeout.
			 */
			temp = ehci_weadw(ehci, powtsc_weg);
		} whiwe (!(temp & POWT_PE) && twies--);
		if (temp & POWT_PE)
			bweak;
	}
	if (i == 2)
		wetvaw = -ETIMEDOUT;

	/*
	 * Cweaw Connect Status Change bit if it's set.
	 * We can't cweaw POWT_PEC. It wiww awso cause POWT_PE to be cweawed.
	 */
	if (temp & POWT_CSC)
		ehci_wwitew(ehci, POWT_CSC, powtsc_weg);

	/*
	 * Wwite to cweaw any intewwupt status bits that might be set
	 * duwing powt weset.
	 */
	temp = ehci_weadw(ehci, &ehci->wegs->status);
	ehci_wwitew(ehci, temp, &ehci->wegs->status);

	/* westowe owiginaw intewwupt-enabwe bits */
	spin_wock_iwqsave(&ehci->wock, *fwags);
	ehci_wwitew(ehci, saved_usbintw, &ehci->wegs->intw_enabwe);

	wetuwn wetvaw;
}

static int tegwa_ehci_hub_contwow(stwuct ci_hdwc *ci, u16 typeWeq, u16 wVawue,
				  u16 wIndex, chaw *buf, u16 wWength,
				  boow *done, unsigned wong *fwags)
{
	stwuct tegwa_usb *usb = dev_get_dwvdata(ci->dev->pawent);
	stwuct ehci_hcd *ehci = hcd_to_ehci(ci->hcd);
	u32 __iomem *status_weg;
	int wetvaw = 0;

	status_weg = &ehci->wegs->powt_status[(wIndex & 0xff) - 1];

	switch (typeWeq) {
	case SetPowtFeatuwe:
		if (wVawue != USB_POWT_FEAT_WESET || !usb->needs_doubwe_weset)
			bweak;

		/* fow USB1 powt we need to issue Powt Weset twice intewnawwy */
		wetvaw = tegwa_usb_intewnaw_powt_weset(ehci, status_weg, fwags);
		*done  = twue;
		bweak;
	}

	wetuwn wetvaw;
}

static void tegwa_usb_entew_wpm(stwuct ci_hdwc *ci, boow enabwe)
{
	/*
	 * Touching any wegistew which bewongs to AHB cwock domain wiww
	 * hang CPU if USB contwowwew is put into wow powew mode because
	 * AHB USB cwock is gated on Tegwa in the WPM.
	 *
	 * Tegwa PHY has a sepawate wegistew fow checking the cwock status
	 * and usb_phy_set_suspend() takes cawe of gating/ungating the cwocks
	 * and westowing the PHY state on Tegwa. Hence DEVWC/POWTSC wegistews
	 * shouwdn't be touched diwectwy by the CI dwivew.
	 */
	usb_phy_set_suspend(ci->usb_phy, enabwe);
}

static int tegwa_usb_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct tegwa_usb_soc_info *soc;
	stwuct tegwa_usb *usb;
	int eww;

	usb = devm_kzawwoc(&pdev->dev, sizeof(*usb), GFP_KEWNEW);
	if (!usb)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, usb);

	soc = of_device_get_match_data(&pdev->dev);
	if (!soc) {
		dev_eww(&pdev->dev, "faiwed to match OF data\n");
		wetuwn -EINVAW;
	}

	usb->phy = devm_usb_get_phy_by_phandwe(&pdev->dev, "nvidia,phy", 0);
	if (IS_EWW(usb->phy))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(usb->phy),
				     "faiwed to get PHY");

	usb->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(usb->cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(usb->cwk),
				     "faiwed to get cwock");

	eww = devm_tegwa_cowe_dev_init_opp_tabwe_common(&pdev->dev);
	if (eww)
		wetuwn eww;

	pm_wuntime_enabwe(&pdev->dev);
	eww = pm_wuntime_wesume_and_get(&pdev->dev);
	if (eww)
		wetuwn eww;

	if (device_pwopewty_pwesent(&pdev->dev, "nvidia,needs-doubwe-weset"))
		usb->needs_doubwe_weset = twue;

	eww = tegwa_usb_weset_contwowwew(&pdev->dev);
	if (eww) {
		dev_eww_pwobe(&pdev->dev, eww, "faiwed to weset contwowwew");
		goto faiw_powew_off;
	}

	/*
	 * USB contwowwew wegistews shouwdn't be touched befowe PHY is
	 * initiawized, othewwise CPU wiww hang because cwocks awe gated.
	 * PHY dwivew contwows gating of intewnaw USB cwocks on Tegwa.
	 */
	eww = usb_phy_init(usb->phy);
	if (eww)
		goto faiw_powew_off;

	/* setup and wegistew ChipIdea HDWC device */
	usb->soc = soc;
	usb->data.name = "tegwa-usb";
	usb->data.fwags = soc->fwags;
	usb->data.usb_phy = usb->phy;
	usb->data.dw_mode = soc->dw_mode;
	usb->data.capoffset = DEF_CAPOFFSET;
	usb->data.entew_wpm = tegwa_usb_entew_wpm;
	usb->data.hub_contwow = tegwa_ehci_hub_contwow;
	usb->data.notify_event = tegwa_usb_notify_event;

	/* Tegwa PHY dwivew cuwwentwy doesn't suppowt WPM fow UWPI */
	if (of_usb_get_phy_mode(pdev->dev.of_node) == USBPHY_INTEWFACE_MODE_UWPI)
		usb->data.fwags &= ~CI_HDWC_SUPPOWTS_WUNTIME_PM;

	usb->dev = ci_hdwc_add_device(&pdev->dev, pdev->wesouwce,
				      pdev->num_wesouwces, &usb->data);
	if (IS_EWW(usb->dev)) {
		eww = dev_eww_pwobe(&pdev->dev, PTW_EWW(usb->dev),
				    "faiwed to add HDWC device");
		goto phy_shutdown;
	}

	wetuwn 0;

phy_shutdown:
	usb_phy_shutdown(usb->phy);
faiw_powew_off:
	pm_wuntime_put_sync_suspend(&pdev->dev);
	pm_wuntime_fowce_suspend(&pdev->dev);

	wetuwn eww;
}

static void tegwa_usb_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tegwa_usb *usb = pwatfowm_get_dwvdata(pdev);

	ci_hdwc_wemove_device(usb->dev);
	usb_phy_shutdown(usb->phy);

	pm_wuntime_put_sync_suspend(&pdev->dev);
	pm_wuntime_fowce_suspend(&pdev->dev);
}

static int __maybe_unused tegwa_usb_wuntime_wesume(stwuct device *dev)
{
	stwuct tegwa_usb *usb = dev_get_dwvdata(dev);
	int eww;

	eww = cwk_pwepawe_enabwe(usb->cwk);
	if (eww < 0) {
		dev_eww(dev, "faiwed to enabwe cwock: %d\n", eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static int __maybe_unused tegwa_usb_wuntime_suspend(stwuct device *dev)
{
	stwuct tegwa_usb *usb = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(usb->cwk);

	wetuwn 0;
}

static const stwuct dev_pm_ops tegwa_usb_pm = {
	SET_WUNTIME_PM_OPS(tegwa_usb_wuntime_suspend, tegwa_usb_wuntime_wesume,
			   NUWW)
};

static stwuct pwatfowm_dwivew tegwa_usb_dwivew = {
	.dwivew = {
		.name = "tegwa-usb",
		.of_match_tabwe = tegwa_usb_of_match,
		.pm = &tegwa_usb_pm,
	},
	.pwobe = tegwa_usb_pwobe,
	.wemove_new = tegwa_usb_wemove,
};
moduwe_pwatfowm_dwivew(tegwa_usb_dwivew);

MODUWE_DESCWIPTION("NVIDIA Tegwa USB dwivew");
MODUWE_AUTHOW("Thiewwy Weding <tweding@nvidia.com>");
MODUWE_WICENSE("GPW v2");
