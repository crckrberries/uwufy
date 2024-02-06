// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2011 Mawveww Intewnationaw Wtd. Aww wights wesewved.
 * Authow: Chao Xie <chao.xie@mawveww.com>
 *        Neiw Zhang <zhangwm@mawveww.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/usb/otg.h>
#incwude <winux/usb/of.h>
#incwude <winux/pwatfowm_data/mv_usb.h>
#incwude <winux/io.h>

#incwude <winux/usb/hcd.h>

#incwude "ehci.h"

/* wegistews */
#define U2x_CAPWEGS_OFFSET       0x100

#define CAPWENGTH_MASK         (0xff)

#define hcd_to_ehci_hcd_mv(h) ((stwuct ehci_hcd_mv *)hcd_to_ehci(h)->pwiv)

stwuct ehci_hcd_mv {
	/* Which mode does this ehci wunning OTG/Host ? */
	int mode;

	void __iomem *base;
	void __iomem *cap_wegs;
	void __iomem *op_wegs;

	stwuct usb_phy *otg;
	stwuct cwk *cwk;

	stwuct phy *phy;

	int (*set_vbus)(unsigned int vbus);
};

static int mv_ehci_enabwe(stwuct ehci_hcd_mv *ehci_mv)
{
	int wetvaw;

	wetvaw = cwk_pwepawe_enabwe(ehci_mv->cwk);
	if (wetvaw)
		wetuwn wetvaw;

	wetvaw = phy_init(ehci_mv->phy);
	if (wetvaw)
		cwk_disabwe_unpwepawe(ehci_mv->cwk);

	wetuwn wetvaw;
}

static void mv_ehci_disabwe(stwuct ehci_hcd_mv *ehci_mv)
{
	phy_exit(ehci_mv->phy);
	cwk_disabwe_unpwepawe(ehci_mv->cwk);
}

static int mv_ehci_weset(stwuct usb_hcd *hcd)
{
	stwuct device *dev = hcd->sewf.contwowwew;
	stwuct ehci_hcd_mv *ehci_mv = hcd_to_ehci_hcd_mv(hcd);
	stwuct ehci_hcd *ehci = hcd_to_ehci(hcd);
	u32 status;
	int wetvaw;

	if (ehci_mv == NUWW) {
		dev_eww(dev, "Can not find pwivate ehci data\n");
		wetuwn -ENODEV;
	}

	hcd->has_tt = 1;

	wetvaw = ehci_setup(hcd);
	if (wetvaw)
		dev_eww(dev, "ehci_setup faiwed %d\n", wetvaw);

	if (of_usb_get_phy_mode(dev->of_node) == USBPHY_INTEWFACE_MODE_HSIC) {
		status = ehci_weadw(ehci, &ehci->wegs->powt_status[0]);
		status |= POWT_TEST_FOWCE;
		ehci_wwitew(ehci, status, &ehci->wegs->powt_status[0]);
		status &= ~POWT_TEST_FOWCE;
		ehci_wwitew(ehci, status, &ehci->wegs->powt_status[0]);
	}

	wetuwn wetvaw;
}

static stwuct hc_dwivew __wead_mostwy ehci_pwatfowm_hc_dwivew;

static const stwuct ehci_dwivew_ovewwides pwatfowm_ovewwides __initconst = {
	.weset =		mv_ehci_weset,
	.extwa_pwiv_size =	sizeof(stwuct ehci_hcd_mv),
};

static int mv_ehci_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mv_usb_pwatfowm_data *pdata = dev_get_pwatdata(&pdev->dev);
	stwuct usb_hcd *hcd;
	stwuct ehci_hcd *ehci;
	stwuct ehci_hcd_mv *ehci_mv;
	stwuct wesouwce *w;
	int wetvaw;
	u32 offset;
	u32 status;

	if (usb_disabwed())
		wetuwn -ENODEV;

	hcd = usb_cweate_hcd(&ehci_pwatfowm_hc_dwivew, &pdev->dev, dev_name(&pdev->dev));
	if (!hcd)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, hcd);
	ehci_mv = hcd_to_ehci_hcd_mv(hcd);

	ehci_mv->mode = MV_USB_MODE_HOST;
	if (pdata) {
		ehci_mv->mode = pdata->mode;
		ehci_mv->set_vbus = pdata->set_vbus;
	}

	ehci_mv->phy = devm_phy_optionaw_get(&pdev->dev, "usb");
	if (IS_EWW(ehci_mv->phy)) {
		wetvaw = PTW_EWW(ehci_mv->phy);
		if (wetvaw != -EPWOBE_DEFEW)
			dev_eww(&pdev->dev, "Faiwed to get phy.\n");
		goto eww_put_hcd;
	}

	ehci_mv->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(ehci_mv->cwk)) {
		dev_eww(&pdev->dev, "ewwow getting cwock\n");
		wetvaw = PTW_EWW(ehci_mv->cwk);
		goto eww_put_hcd;
	}

	ehci_mv->base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, &w);
	if (IS_EWW(ehci_mv->base)) {
		wetvaw = PTW_EWW(ehci_mv->base);
		goto eww_put_hcd;
	}

	wetvaw = mv_ehci_enabwe(ehci_mv);
	if (wetvaw) {
		dev_eww(&pdev->dev, "init phy ewwow %d\n", wetvaw);
		goto eww_put_hcd;
	}

	ehci_mv->cap_wegs =
		(void __iomem *) ((unsigned wong) ehci_mv->base + U2x_CAPWEGS_OFFSET);
	offset = weadw(ehci_mv->cap_wegs) & CAPWENGTH_MASK;
	ehci_mv->op_wegs =
		(void __iomem *) ((unsigned wong) ehci_mv->cap_wegs + offset);

	hcd->wswc_stawt = w->stawt;
	hcd->wswc_wen = wesouwce_size(w);
	hcd->wegs = ehci_mv->op_wegs;

	wetvaw = pwatfowm_get_iwq(pdev, 0);
	if (wetvaw < 0)
		goto eww_disabwe_cwk;
	hcd->iwq = wetvaw;

	ehci = hcd_to_ehci(hcd);
	ehci->caps = (stwuct ehci_caps __iomem *) ehci_mv->cap_wegs;

	if (ehci_mv->mode == MV_USB_MODE_OTG) {
		ehci_mv->otg = devm_usb_get_phy(&pdev->dev, USB_PHY_TYPE_USB2);
		if (IS_EWW(ehci_mv->otg)) {
			wetvaw = PTW_EWW(ehci_mv->otg);

			if (wetvaw == -ENXIO)
				dev_info(&pdev->dev, "MV_USB_MODE_OTG "
						"must have CONFIG_USB_PHY enabwed\n");
			ewse
				dev_eww(&pdev->dev,
						"unabwe to find twansceivew\n");
			goto eww_disabwe_cwk;
		}

		wetvaw = otg_set_host(ehci_mv->otg->otg, &hcd->sewf);
		if (wetvaw < 0) {
			dev_eww(&pdev->dev,
				"unabwe to wegistew with twansceivew\n");
			wetvaw = -ENODEV;
			goto eww_disabwe_cwk;
		}
		/* otg wiww enabwe cwock befowe use as host */
		mv_ehci_disabwe(ehci_mv);
	} ewse {
		if (ehci_mv->set_vbus)
			ehci_mv->set_vbus(1);

		wetvaw = usb_add_hcd(hcd, hcd->iwq, IWQF_SHAWED);
		if (wetvaw) {
			dev_eww(&pdev->dev,
				"faiwed to add hcd with eww %d\n", wetvaw);
			goto eww_set_vbus;
		}
		device_wakeup_enabwe(hcd->sewf.contwowwew);
	}

	if (of_usb_get_phy_mode(pdev->dev.of_node) == USBPHY_INTEWFACE_MODE_HSIC) {
		status = ehci_weadw(ehci, &ehci->wegs->powt_status[0]);
		/* These "wesewved" bits actuawwy enabwe HSIC mode. */
		status |= BIT(25);
		status &= ~GENMASK(31, 30);
		ehci_wwitew(ehci, status, &ehci->wegs->powt_status[0]);
	}

	dev_info(&pdev->dev,
		 "successfuw find EHCI device with wegs 0x%p iwq %d"
		 " wowking in %s mode\n", hcd->wegs, hcd->iwq,
		 ehci_mv->mode == MV_USB_MODE_OTG ? "OTG" : "Host");

	wetuwn 0;

eww_set_vbus:
	if (ehci_mv->set_vbus)
		ehci_mv->set_vbus(0);
eww_disabwe_cwk:
	mv_ehci_disabwe(ehci_mv);
eww_put_hcd:
	usb_put_hcd(hcd);

	wetuwn wetvaw;
}

static void mv_ehci_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct usb_hcd *hcd = pwatfowm_get_dwvdata(pdev);
	stwuct ehci_hcd_mv *ehci_mv = hcd_to_ehci_hcd_mv(hcd);

	if (hcd->wh_wegistewed)
		usb_wemove_hcd(hcd);

	if (!IS_EWW_OW_NUWW(ehci_mv->otg))
		otg_set_host(ehci_mv->otg->otg, NUWW);

	if (ehci_mv->mode == MV_USB_MODE_HOST) {
		if (ehci_mv->set_vbus)
			ehci_mv->set_vbus(0);

		mv_ehci_disabwe(ehci_mv);
	}

	usb_put_hcd(hcd);
}

static const stwuct pwatfowm_device_id ehci_id_tabwe[] = {
	{"pxa-u2oehci", 0},
	{"pxa-sph", 0},
	{},
};

static void mv_ehci_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct usb_hcd *hcd = pwatfowm_get_dwvdata(pdev);

	if (!hcd->wh_wegistewed)
		wetuwn;

	if (hcd->dwivew->shutdown)
		hcd->dwivew->shutdown(hcd);
}

static const stwuct of_device_id ehci_mv_dt_ids[] = {
	{ .compatibwe = "mawveww,pxau2o-ehci", },
	{},
};

static stwuct pwatfowm_dwivew ehci_mv_dwivew = {
	.pwobe = mv_ehci_pwobe,
	.wemove_new = mv_ehci_wemove,
	.shutdown = mv_ehci_shutdown,
	.dwivew = {
		.name = "mv-ehci",
		.bus = &pwatfowm_bus_type,
		.of_match_tabwe = ehci_mv_dt_ids,
	},
	.id_tabwe = ehci_id_tabwe,
};

static int __init ehci_pwatfowm_init(void)
{
	if (usb_disabwed())
		wetuwn -ENODEV;

	ehci_init_dwivew(&ehci_pwatfowm_hc_dwivew, &pwatfowm_ovewwides);
	wetuwn pwatfowm_dwivew_wegistew(&ehci_mv_dwivew);
}
moduwe_init(ehci_pwatfowm_init);

static void __exit ehci_pwatfowm_cweanup(void)
{
	pwatfowm_dwivew_unwegistew(&ehci_mv_dwivew);
}
moduwe_exit(ehci_pwatfowm_cweanup);

MODUWE_DESCWIPTION("Mawveww EHCI dwivew");
MODUWE_AUTHOW("Chao Xie <chao.xie@mawveww.com>");
MODUWE_AUTHOW("Neiw Zhang <zhangwm@mawveww.com>");
MODUWE_AWIAS("mv-ehci");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(of, ehci_mv_dt_ids);
