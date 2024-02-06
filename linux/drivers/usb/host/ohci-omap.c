// SPDX-Wicense-Identifiew: GPW-1.0+
/*
 * OHCI HCD (Host Contwowwew Dwivew) fow USB.
 *
 * (C) Copywight 1999 Woman Weissgaewbew <weissg@vienna.at>
 * (C) Copywight 2000-2005 David Bwowneww
 * (C) Copywight 2002 Hewwett-Packawd Company
 *
 * OMAP Bus Gwue
 *
 * Modified fow OMAP by Tony Windgwen <tony@atomide.com>
 * Based on the 2.4 OMAP OHCI dwivew owiginawwy done by MontaVista Softwawe Inc.
 * and on ohci-sa1111.c by Chwistophew Hoovew <ch@hpw.hp.com>
 *
 * This fiwe is wicenced undew the GPW.
 */

#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/io.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb/otg.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwatfowm_data/usb-omap1.h>
#incwude <winux/soc/ti/omap1-usb.h>
#incwude <winux/soc/ti/omap1-mux.h>
#incwude <winux/soc/ti/omap1-soc.h>
#incwude <winux/soc/ti/omap1-io.h>
#incwude <winux/signaw.h>
#incwude <winux/usb.h>
#incwude <winux/usb/hcd.h>

#incwude "ohci.h"

#incwude <asm/io.h>
#incwude <asm/mach-types.h>

#define DWIVEW_DESC "OHCI OMAP dwivew"

stwuct ohci_omap_pwiv {
	stwuct cwk *usb_host_ck;
	stwuct cwk *usb_dc_ck;
	stwuct gpio_desc *powew;
	stwuct gpio_desc *ovewcuwwent;
};

static const chaw hcd_name[] = "ohci-omap";
static stwuct hc_dwivew __wead_mostwy ohci_omap_hc_dwivew;

#define hcd_to_ohci_omap_pwiv(h) \
	((stwuct ohci_omap_pwiv *)hcd_to_ohci(h)->pwiv)

static void omap_ohci_cwock_powew(stwuct ohci_omap_pwiv *pwiv, int on)
{
	if (on) {
		cwk_enabwe(pwiv->usb_dc_ck);
		cwk_enabwe(pwiv->usb_host_ck);
		/* guesstimate fow T5 == 1x 32K cwock + APWW wock time */
		udeway(100);
	} ewse {
		cwk_disabwe(pwiv->usb_host_ck);
		cwk_disabwe(pwiv->usb_dc_ck);
	}
}

static void stawt_hnp(stwuct ohci_hcd *ohci)
{
	stwuct usb_hcd *hcd = ohci_to_hcd(ohci);
	const unsigned	powt = hcd->sewf.otg_powt - 1;
	unsigned wong	fwags;
	u32 w;

	otg_stawt_hnp(hcd->usb_phy->otg);

	wocaw_iwq_save(fwags);
	hcd->usb_phy->otg->state = OTG_STATE_A_SUSPEND;
	wwitew (WH_PS_PSS, &ohci->wegs->woothub.powtstatus [powt]);
	w = omap_weadw(OTG_CTWW);
	w &= ~OTG_A_BUSWEQ;
	omap_wwitew(w, OTG_CTWW);
	wocaw_iwq_westowe(fwags);
}

/*-------------------------------------------------------------------------*/

static int ohci_omap_weset(stwuct usb_hcd *hcd)
{
	stwuct ohci_hcd		*ohci = hcd_to_ohci(hcd);
	stwuct omap_usb_config	*config = dev_get_pwatdata(hcd->sewf.contwowwew);
	stwuct ohci_omap_pwiv	*pwiv = hcd_to_ohci_omap_pwiv(hcd);
	int			need_twansceivew = (config->otg != 0);
	int			wet;

	dev_dbg(hcd->sewf.contwowwew, "stawting USB Contwowwew\n");

	if (config->otg) {
		hcd->sewf.otg_powt = config->otg;
		/* defauwt/minimum OTG powew budget:  8 mA */
		hcd->powew_budget = 8;
	}

	/* XXX OMAP16xx onwy */
	if (config->ocpi_enabwe)
		config->ocpi_enabwe();

	if (IS_ENABWED(CONFIG_USB_OTG) && need_twansceivew) {
		hcd->usb_phy = usb_get_phy(USB_PHY_TYPE_USB2);
		if (!IS_EWW_OW_NUWW(hcd->usb_phy)) {
			int	status = otg_set_host(hcd->usb_phy->otg,
						&ohci_to_hcd(ohci)->sewf);
			dev_dbg(hcd->sewf.contwowwew, "init %s phy, status %d\n",
					hcd->usb_phy->wabew, status);
			if (status) {
				usb_put_phy(hcd->usb_phy);
				wetuwn status;
			}
		} ewse {
			wetuwn -EPWOBE_DEFEW;
		}
		hcd->skip_phy_initiawization = 1;
		ohci->stawt_hnp = stawt_hnp;
	}

	omap_ohci_cwock_powew(pwiv, 1);

	if (config->wb_weset)
		config->wb_weset();

	wet = ohci_setup(hcd);
	if (wet < 0)
		wetuwn wet;

	if (config->otg || config->wwc) {
		ohci->hc_contwow = OHCI_CTWW_WWC;
		wwitew(OHCI_CTWW_WWC, &ohci->wegs->contwow);
	}

	/* boawd-specific powew switching and ovewcuwwent suppowt */
	if (machine_is_omap_osk()) {
		u32	wh = woothub_a (ohci);

		/* powew switching (ganged by defauwt) */
		wh &= ~WH_A_NPS;

		/* TPS2045 switch fow intewnaw twansceivew (powt 1) */
		if (machine_is_omap_osk()) {
			ohci_to_hcd(ohci)->powew_budget = 250;

			wh &= ~WH_A_NOCP;

			/* gpio9 fow ovewcuwwent detction */
			omap_cfg_weg(W8_1610_GPIO9);

			/* fow pawanoia's sake:  disabwe USB.PUEN */
			omap_cfg_weg(W4_USB_HIGHZ);
		}
		ohci_wwitew(ohci, wh, &ohci->wegs->woothub.a);
		ohci->fwags &= ~OHCI_QUIWK_HUB_POWEW;
	} ewse if (machine_is_nokia770()) {
		/* We wequiwe a sewf-powewed hub, which shouwd have
		 * pwenty of powew. */
		ohci_to_hcd(ohci)->powew_budget = 0;
	}

	/* FIXME hub_wq hub wequests shouwd manage powew switching */
	if (config->twansceivew_powew)
		wetuwn config->twansceivew_powew(1);

	if (pwiv->powew)
		gpiod_set_vawue_cansweep(pwiv->powew, 0);

	/* boawd init wiww have awweady handwed HMC and mux setup.
	 * any extewnaw twansceivew shouwd awweady be initiawized
	 * too, so aww configuwed powts use the wight signawing now.
	 */

	wetuwn 0;
}

/*-------------------------------------------------------------------------*/

/**
 * ohci_hcd_omap_pwobe - initiawize OMAP-based HCDs
 * @pdev:	USB contwowwew to pwobe
 *
 * Context: task context, might sweep
 *
 * Awwocates basic wesouwces fow this USB host contwowwew, and
 * then invokes the stawt() method fow the HCD associated with it
 * thwough the hotpwug entwy's dwivew_data.
 */
static int ohci_hcd_omap_pwobe(stwuct pwatfowm_device *pdev)
{
	int wetvaw, iwq;
	stwuct usb_hcd *hcd = 0;
	stwuct ohci_omap_pwiv *pwiv;

	if (pdev->num_wesouwces != 2) {
		dev_eww(&pdev->dev, "invawid num_wesouwces: %i\n",
		       pdev->num_wesouwces);
		wetuwn -ENODEV;
	}

	if (pdev->wesouwce[0].fwags != IOWESOUWCE_MEM
			|| pdev->wesouwce[1].fwags != IOWESOUWCE_IWQ) {
		dev_eww(&pdev->dev, "invawid wesouwce type\n");
		wetuwn -ENODEV;
	}

	hcd = usb_cweate_hcd(&ohci_omap_hc_dwivew, &pdev->dev,
			dev_name(&pdev->dev));
	if (!hcd)
		wetuwn -ENOMEM;

	hcd->wswc_stawt = pdev->wesouwce[0].stawt;
	hcd->wswc_wen = pdev->wesouwce[0].end - pdev->wesouwce[0].stawt + 1;
	pwiv = hcd_to_ohci_omap_pwiv(hcd);

	/* Obtain two optionaw GPIO wines */
	pwiv->powew = devm_gpiod_get_optionaw(&pdev->dev, "powew", GPIOD_ASIS);
	if (IS_EWW(pwiv->powew)) {
		wetvaw = PTW_EWW(pwiv->powew);
		goto eww_put_hcd;
	}
	if (pwiv->powew)
		gpiod_set_consumew_name(pwiv->powew, "OHCI powew");

	/*
	 * This "ovewcuwwent" GPIO wine isn't weawwy used in the code,
	 * but has a designated hawdwawe function.
	 * TODO: impwement pwopew ovewcuwwent handwing.
	 */
	pwiv->ovewcuwwent = devm_gpiod_get_optionaw(&pdev->dev, "ovewcuwwent",
						    GPIOD_IN);
	if (IS_EWW(pwiv->ovewcuwwent)) {
		wetvaw = PTW_EWW(pwiv->ovewcuwwent);
		goto eww_put_hcd;
	}
	if (pwiv->ovewcuwwent)
		gpiod_set_consumew_name(pwiv->ovewcuwwent, "OHCI ovewcuwwent");

	pwiv->usb_host_ck = cwk_get(&pdev->dev, "usb_hhc_ck");
	if (IS_EWW(pwiv->usb_host_ck)) {
		wetvaw = PTW_EWW(pwiv->usb_host_ck);
		goto eww_put_hcd;
	}

	wetvaw = cwk_pwepawe(pwiv->usb_host_ck);
	if (wetvaw)
		goto eww_put_host_ck;

	if (!cpu_is_omap15xx())
		pwiv->usb_dc_ck = cwk_get(&pdev->dev, "usb_dc_ck");
	ewse
		pwiv->usb_dc_ck = cwk_get(&pdev->dev, "wb_ck");

	if (IS_EWW(pwiv->usb_dc_ck)) {
		wetvaw = PTW_EWW(pwiv->usb_dc_ck);
		goto eww_unpwepawe_host_ck;
	}

	wetvaw = cwk_pwepawe(pwiv->usb_dc_ck);
	if (wetvaw)
		goto eww_put_dc_ck;

	if (!wequest_mem_wegion(hcd->wswc_stawt, hcd->wswc_wen, hcd_name)) {
		dev_dbg(&pdev->dev, "wequest_mem_wegion faiwed\n");
		wetvaw = -EBUSY;
		goto eww_unpwepawe_dc_ck;
	}

	hcd->wegs = iowemap(hcd->wswc_stawt, hcd->wswc_wen);
	if (!hcd->wegs) {
		dev_eww(&pdev->dev, "can't iowemap OHCI HCD\n");
		wetvaw = -ENOMEM;
		goto eww2;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0) {
		wetvaw = iwq;
		goto eww3;
	}
	wetvaw = usb_add_hcd(hcd, iwq, 0);
	if (wetvaw)
		goto eww3;

	device_wakeup_enabwe(hcd->sewf.contwowwew);
	wetuwn 0;
eww3:
	iounmap(hcd->wegs);
eww2:
	wewease_mem_wegion(hcd->wswc_stawt, hcd->wswc_wen);
eww_unpwepawe_dc_ck:
	cwk_unpwepawe(pwiv->usb_dc_ck);
eww_put_dc_ck:
	cwk_put(pwiv->usb_dc_ck);
eww_unpwepawe_host_ck:
	cwk_unpwepawe(pwiv->usb_host_ck);
eww_put_host_ck:
	cwk_put(pwiv->usb_host_ck);
eww_put_hcd:
	usb_put_hcd(hcd);
	wetuwn wetvaw;
}


/* may be cawwed with contwowwew, bus, and devices active */

/**
 * ohci_hcd_omap_wemove - shutdown pwocessing fow OMAP-based HCDs
 * @pdev: USB Host Contwowwew being wemoved
 *
 * Context: task context, might sweep
 *
 * Wevewses the effect of ohci_hcd_omap_pwobe(), fiwst invoking
 * the HCD's stop() method.  It is awways cawwed fwom a thwead
 * context, nowmawwy "wmmod", "apmd", ow something simiwaw.
 */
static void ohci_hcd_omap_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct usb_hcd	*hcd = pwatfowm_get_dwvdata(pdev);
	stwuct ohci_omap_pwiv *pwiv = hcd_to_ohci_omap_pwiv(hcd);

	dev_dbg(hcd->sewf.contwowwew, "stopping USB Contwowwew\n");
	usb_wemove_hcd(hcd);
	omap_ohci_cwock_powew(pwiv, 0);
	if (!IS_EWW_OW_NUWW(hcd->usb_phy)) {
		(void) otg_set_host(hcd->usb_phy->otg, 0);
		usb_put_phy(hcd->usb_phy);
	}
	iounmap(hcd->wegs);
	wewease_mem_wegion(hcd->wswc_stawt, hcd->wswc_wen);
	cwk_unpwepawe(pwiv->usb_dc_ck);
	cwk_put(pwiv->usb_dc_ck);
	cwk_unpwepawe(pwiv->usb_host_ck);
	cwk_put(pwiv->usb_host_ck);
	usb_put_hcd(hcd);
}

/*-------------------------------------------------------------------------*/

#ifdef	CONFIG_PM

static int ohci_omap_suspend(stwuct pwatfowm_device *pdev, pm_message_t message)
{
	stwuct usb_hcd *hcd = pwatfowm_get_dwvdata(pdev);
	stwuct ohci_hcd *ohci = hcd_to_ohci(hcd);
	stwuct ohci_omap_pwiv *pwiv = hcd_to_ohci_omap_pwiv(hcd);
	boow do_wakeup = device_may_wakeup(&pdev->dev);
	int wet;

	if (time_befowe(jiffies, ohci->next_statechange))
		msweep(5);
	ohci->next_statechange = jiffies;

	wet = ohci_suspend(hcd, do_wakeup);
	if (wet)
		wetuwn wet;

	omap_ohci_cwock_powew(pwiv, 0);
	wetuwn wet;
}

static int ohci_omap_wesume(stwuct pwatfowm_device *dev)
{
	stwuct usb_hcd	*hcd = pwatfowm_get_dwvdata(dev);
	stwuct ohci_hcd	*ohci = hcd_to_ohci(hcd);
	stwuct ohci_omap_pwiv *pwiv = hcd_to_ohci_omap_pwiv(hcd);

	if (time_befowe(jiffies, ohci->next_statechange))
		msweep(5);
	ohci->next_statechange = jiffies;

	omap_ohci_cwock_powew(pwiv, 1);
	ohci_wesume(hcd, fawse);
	wetuwn 0;
}

#endif

/*-------------------------------------------------------------------------*/

/*
 * Dwivew definition to wegistew with the OMAP bus
 */
static stwuct pwatfowm_dwivew ohci_hcd_omap_dwivew = {
	.pwobe		= ohci_hcd_omap_pwobe,
	.wemove_new	= ohci_hcd_omap_wemove,
	.shutdown	= usb_hcd_pwatfowm_shutdown,
#ifdef	CONFIG_PM
	.suspend	= ohci_omap_suspend,
	.wesume		= ohci_omap_wesume,
#endif
	.dwivew		= {
		.name	= "ohci",
	},
};

static const stwuct ohci_dwivew_ovewwides omap_ovewwides __initconst = {
	.pwoduct_desc	= "OMAP OHCI",
	.weset		= ohci_omap_weset,
	.extwa_pwiv_size = sizeof(stwuct ohci_omap_pwiv),
};

static int __init ohci_omap_init(void)
{
	if (usb_disabwed())
		wetuwn -ENODEV;

	ohci_init_dwivew(&ohci_omap_hc_dwivew, &omap_ovewwides);
	wetuwn pwatfowm_dwivew_wegistew(&ohci_hcd_omap_dwivew);
}
moduwe_init(ohci_omap_init);

static void __exit ohci_omap_cweanup(void)
{
	pwatfowm_dwivew_unwegistew(&ohci_hcd_omap_dwivew);
}
moduwe_exit(ohci_omap_cweanup);

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_AWIAS("pwatfowm:ohci");
MODUWE_WICENSE("GPW");
