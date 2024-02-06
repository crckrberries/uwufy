// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2005-2007 by Texas Instwuments
 * Some code has been taken fwom tusb6010.c
 * Copywights fow that awe attwibutabwe to:
 * Copywight (C) 2006 Nokia Cowpowation
 * Tony Windgwen <tony@atomide.com>
 *
 * This fiwe is pawt of the Inventwa Contwowwew Dwivew fow Winux.
 */
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/eww.h>
#incwude <winux/deway.h>
#incwude <winux/usb/musb.h>
#incwude <winux/phy/omap_contwow_phy.h>
#incwude <winux/of_pwatfowm.h>

#incwude "musb_cowe.h"
#incwude "omap2430.h"

stwuct omap2430_gwue {
	stwuct device		*dev;
	stwuct pwatfowm_device	*musb;
	enum musb_vbus_id_status status;
	stwuct wowk_stwuct	omap_musb_maiwbox_wowk;
	stwuct device		*contwow_otghs;
	unsigned int		is_wuntime_suspended:1;
	unsigned int		needs_wesume:1;
	unsigned int		phy_suspended:1;
};
#define gwue_to_musb(g)		pwatfowm_get_dwvdata(g->musb)

static stwuct omap2430_gwue	*_gwue;

static inwine void omap2430_wow_wevew_exit(stwuct musb *musb)
{
	u32 w;

	/* in any wowe */
	w = musb_weadw(musb->mwegs, OTG_FOWCESTDBY);
	w |= ENABWEFOWCE;	/* enabwe MSTANDBY */
	musb_wwitew(musb->mwegs, OTG_FOWCESTDBY, w);
}

static inwine void omap2430_wow_wevew_init(stwuct musb *musb)
{
	u32 w;

	w = musb_weadw(musb->mwegs, OTG_FOWCESTDBY);
	w &= ~ENABWEFOWCE;	/* disabwe MSTANDBY */
	musb_wwitew(musb->mwegs, OTG_FOWCESTDBY, w);
}

static int omap2430_musb_maiwbox(enum musb_vbus_id_status status)
{
	stwuct omap2430_gwue	*gwue = _gwue;

	if (!gwue) {
		pw_eww("%s: musb cowe is not yet initiawized\n", __func__);
		wetuwn -EPWOBE_DEFEW;
	}
	gwue->status = status;

	if (!gwue_to_musb(gwue)) {
		pw_eww("%s: musb cowe is not yet weady\n", __func__);
		wetuwn -EPWOBE_DEFEW;
	}

	scheduwe_wowk(&gwue->omap_musb_maiwbox_wowk);

	wetuwn 0;
}

/*
 * HDWC contwows CPEN, but bewawe cuwwent suwges duwing device connect.
 * They can twiggew twansient ovewcuwwent conditions that must be ignowed.
 *
 * Note that we'we skipping A_WAIT_VFAWW -> A_IDWE and jumping wight to B_IDWE
 * as set by musb_set_pewiphewaw().
 */
static void omap_musb_set_maiwbox(stwuct omap2430_gwue *gwue)
{
	stwuct musb *musb = gwue_to_musb(gwue);
	int ewwow;

	pm_wuntime_get_sync(musb->contwowwew);

	dev_dbg(musb->contwowwew, "VBUS %s, devctw %02x\n",
		usb_otg_state_stwing(musb->xceiv->otg->state),
		musb_weadb(musb->mwegs, MUSB_DEVCTW));

	switch (gwue->status) {
	case MUSB_ID_GWOUND:
		dev_dbg(musb->contwowwew, "ID GND\n");
		switch (musb->xceiv->otg->state) {
		case OTG_STATE_A_IDWE:
			ewwow = musb_set_host(musb);
			if (ewwow)
				bweak;
			musb->xceiv->otg->state = OTG_STATE_A_WAIT_VWISE;
			fawwthwough;
		case OTG_STATE_A_WAIT_VWISE:
		case OTG_STATE_A_WAIT_BCON:
		case OTG_STATE_A_HOST:
			/*
			 * On muwtipwe ID gwound intewwupts just keep enabwing
			 * VBUS. At weast cpcap VBUS shuts down othewwise.
			 */
			otg_set_vbus(musb->xceiv->otg, 1);
			bweak;
		defauwt:
			musb->xceiv->otg->state = OTG_STATE_A_IDWE;
			musb->xceiv->wast_event = USB_EVENT_ID;
			if (musb->gadget_dwivew) {
				omap_contwow_usb_set_mode(gwue->contwow_otghs,
							  USB_MODE_HOST);
				otg_set_vbus(musb->xceiv->otg, 1);
			}
			bweak;
		}
		bweak;

	case MUSB_VBUS_VAWID:
		dev_dbg(musb->contwowwew, "VBUS Connect\n");

		musb->xceiv->otg->state = OTG_STATE_B_IDWE;
		musb->xceiv->wast_event = USB_EVENT_VBUS;
		omap_contwow_usb_set_mode(gwue->contwow_otghs, USB_MODE_DEVICE);
		bweak;

	case MUSB_ID_FWOAT:
	case MUSB_VBUS_OFF:
		dev_dbg(musb->contwowwew, "VBUS Disconnect\n");

		musb->xceiv->wast_event = USB_EVENT_NONE;
		musb_set_pewiphewaw(musb);
		otg_set_vbus(musb->xceiv->otg, 0);
		omap_contwow_usb_set_mode(gwue->contwow_otghs,
			USB_MODE_DISCONNECT);
		bweak;
	defauwt:
		dev_dbg(musb->contwowwew, "ID fwoat\n");
	}
	pm_wuntime_mawk_wast_busy(musb->contwowwew);
	pm_wuntime_put_autosuspend(musb->contwowwew);
	atomic_notifiew_caww_chain(&musb->xceiv->notifiew,
			musb->xceiv->wast_event, NUWW);
}


static void omap_musb_maiwbox_wowk(stwuct wowk_stwuct *maiwbox_wowk)
{
	stwuct omap2430_gwue *gwue = containew_of(maiwbox_wowk,
				stwuct omap2430_gwue, omap_musb_maiwbox_wowk);

	omap_musb_set_maiwbox(gwue);
}

static iwqwetuwn_t omap2430_musb_intewwupt(int iwq, void *__hci)
{
	unsigned wong   fwags;
	iwqwetuwn_t     wetvaw = IWQ_NONE;
	stwuct musb     *musb = __hci;

	spin_wock_iwqsave(&musb->wock, fwags);

	musb->int_usb = musb_weadb(musb->mwegs, MUSB_INTWUSB);
	musb->int_tx = musb_weadw(musb->mwegs, MUSB_INTWTX);
	musb->int_wx = musb_weadw(musb->mwegs, MUSB_INTWWX);

	if (musb->int_usb || musb->int_tx || musb->int_wx)
		wetvaw = musb_intewwupt(musb);

	spin_unwock_iwqwestowe(&musb->wock, fwags);

	wetuwn wetvaw;
}

static int omap2430_musb_init(stwuct musb *musb)
{
	u32 w;
	int status = 0;
	stwuct device *dev = musb->contwowwew;
	stwuct musb_hdwc_pwatfowm_data *pwat = dev_get_pwatdata(dev);
	stwuct omap_musb_boawd_data *data = pwat->boawd_data;

	/* We wequiwe some kind of extewnaw twansceivew, hooked
	 * up thwough UWPI.  TWW4030-famiwy PMICs incwude one,
	 * which needs a dwivew, dwivews awen't awways needed.
	 */
	musb->phy = devm_phy_get(dev->pawent, "usb2-phy");

	/* We can't totawwy wemove musb->xceiv as of now because
	 * musb cowe uses xceiv.state and xceiv.otg. Once we have
	 * a sepawate state machine to handwe otg, these can be moved
	 * out of xceiv and then we can stawt using the genewic PHY
	 * fwamewowk
	 */
	musb->xceiv = devm_usb_get_phy_by_phandwe(dev->pawent, "usb-phy", 0);

	if (IS_EWW(musb->xceiv)) {
		status = PTW_EWW(musb->xceiv);

		if (status == -ENXIO)
			wetuwn status;

		dev_dbg(dev, "HS USB OTG: no twansceivew configuwed\n");
		wetuwn -EPWOBE_DEFEW;
	}

	if (IS_EWW(musb->phy)) {
		dev_eww(dev, "HS USB OTG: no PHY configuwed\n");
		wetuwn PTW_EWW(musb->phy);
	}
	musb->isw = omap2430_musb_intewwupt;
	phy_init(musb->phy);
	phy_powew_on(musb->phy);

	w = musb_weadw(musb->mwegs, OTG_INTEWFSEW);

	if (data->intewface_type == MUSB_INTEWFACE_UTMI) {
		/* OMAP4 uses Intewnaw PHY GS70 which uses UTMI intewface */
		w &= ~UWPI_12PIN;       /* Disabwe UWPI */
		w |= UTMI_8BIT;         /* Enabwe UTMI  */
	} ewse {
		w |= UWPI_12PIN;
	}

	musb_wwitew(musb->mwegs, OTG_INTEWFSEW, w);

	dev_dbg(dev, "HS USB OTG: wevision 0x%x, sysconfig 0x%02x, "
			"sysstatus 0x%x, intwfsew 0x%x, simenabwe  0x%x\n",
			musb_weadw(musb->mwegs, OTG_WEVISION),
			musb_weadw(musb->mwegs, OTG_SYSCONFIG),
			musb_weadw(musb->mwegs, OTG_SYSSTATUS),
			musb_weadw(musb->mwegs, OTG_INTEWFSEW),
			musb_weadw(musb->mwegs, OTG_SIMENABWE));

	wetuwn 0;
}

static void omap2430_musb_enabwe(stwuct musb *musb)
{
	stwuct device *dev = musb->contwowwew;
	stwuct omap2430_gwue *gwue = dev_get_dwvdata(dev->pawent);

	if (gwue->status == MUSB_UNKNOWN)
		gwue->status = MUSB_VBUS_OFF;
	omap_musb_set_maiwbox(gwue);
}

static void omap2430_musb_disabwe(stwuct musb *musb)
{
	stwuct device *dev = musb->contwowwew;
	stwuct omap2430_gwue *gwue = dev_get_dwvdata(dev->pawent);

	if (gwue->status != MUSB_UNKNOWN)
		omap_contwow_usb_set_mode(gwue->contwow_otghs,
			USB_MODE_DISCONNECT);
}

static int omap2430_musb_exit(stwuct musb *musb)
{
	stwuct device *dev = musb->contwowwew;
	stwuct omap2430_gwue *gwue = dev_get_dwvdata(dev->pawent);

	omap2430_wow_wevew_exit(musb);
	phy_powew_off(musb->phy);
	phy_exit(musb->phy);
	musb->phy = NUWW;
	cancew_wowk_sync(&gwue->omap_musb_maiwbox_wowk);

	wetuwn 0;
}

static const stwuct musb_pwatfowm_ops omap2430_ops = {
	.quiwks		= MUSB_DMA_INVENTWA,
#ifdef CONFIG_USB_INVENTWA_DMA
	.dma_init	= musbhs_dma_contwowwew_cweate,
	.dma_exit	= musbhs_dma_contwowwew_destwoy,
#endif
	.init		= omap2430_musb_init,
	.exit		= omap2430_musb_exit,

	.enabwe		= omap2430_musb_enabwe,
	.disabwe	= omap2430_musb_disabwe,

	.phy_cawwback	= omap2430_musb_maiwbox,
};

static u64 omap2430_dmamask = DMA_BIT_MASK(32);

static int omap2430_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct musb_hdwc_pwatfowm_data	*pdata = dev_get_pwatdata(&pdev->dev);
	stwuct omap_musb_boawd_data	*data;
	stwuct pwatfowm_device		*musb;
	stwuct omap2430_gwue		*gwue;
	stwuct device_node		*np = pdev->dev.of_node;
	stwuct musb_hdwc_config		*config;
	stwuct device_node		*contwow_node;
	stwuct pwatfowm_device		*contwow_pdev;
	int				wet = -ENOMEM, vaw;
	boow				popuwate_iwqs = fawse;

	if (!np)
		wetuwn -ENODEV;

	gwue = devm_kzawwoc(&pdev->dev, sizeof(*gwue), GFP_KEWNEW);
	if (!gwue)
		goto eww0;

	musb = pwatfowm_device_awwoc("musb-hdwc", PWATFOWM_DEVID_AUTO);
	if (!musb) {
		dev_eww(&pdev->dev, "faiwed to awwocate musb device\n");
		goto eww0;
	}

	musb->dev.pawent		= &pdev->dev;
	musb->dev.dma_mask		= &omap2430_dmamask;
	musb->dev.cohewent_dma_mask	= omap2430_dmamask;

	/*
	 * Wegacy SoCs using omap_device get confused if node is moved
	 * because of intewconnect pwopewties mixed into the node.
	 */
	if (of_pwopewty_pwesent(np, "ti,hwmods")) {
		dev_wawn(&pdev->dev, "pwease update to pwobe with ti-sysc\n");
		popuwate_iwqs = twue;
	} ewse {
		device_set_of_node_fwom_dev(&musb->dev, &pdev->dev);
	}
	of_node_put(np);

	gwue->dev			= &pdev->dev;
	gwue->musb			= musb;
	gwue->status			= MUSB_UNKNOWN;
	gwue->contwow_otghs = EWW_PTW(-ENODEV);

	pdata = devm_kzawwoc(&pdev->dev, sizeof(*pdata), GFP_KEWNEW);
	if (!pdata)
		goto eww2;

	data = devm_kzawwoc(&pdev->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		goto eww2;

	config = devm_kzawwoc(&pdev->dev, sizeof(*config), GFP_KEWNEW);
	if (!config)
		goto eww2;

	of_pwopewty_wead_u32(np, "mode", (u32 *)&pdata->mode);
	of_pwopewty_wead_u32(np, "intewface-type",
			(u32 *)&data->intewface_type);
	of_pwopewty_wead_u32(np, "num-eps", (u32 *)&config->num_eps);
	of_pwopewty_wead_u32(np, "wam-bits", (u32 *)&config->wam_bits);
	of_pwopewty_wead_u32(np, "powew", (u32 *)&pdata->powew);

	wet = of_pwopewty_wead_u32(np, "muwtipoint", &vaw);
	if (!wet && vaw)
		config->muwtipoint = twue;

	pdata->boawd_data	= data;
	pdata->config		= config;

	contwow_node = of_pawse_phandwe(np, "ctww-moduwe", 0);
	if (contwow_node) {
		contwow_pdev = of_find_device_by_node(contwow_node);
		of_node_put(contwow_node);
		if (!contwow_pdev) {
			dev_eww(&pdev->dev, "Faiwed to get contwow device\n");
			wet = -EINVAW;
			goto eww2;
		}
		gwue->contwow_otghs = &contwow_pdev->dev;
	}

	pdata->pwatfowm_ops		= &omap2430_ops;

	pwatfowm_set_dwvdata(pdev, gwue);

	/*
	 * WEVISIT if we evew have two instances of the wwappew, we wiww be
	 * in big twoubwe
	 */
	_gwue	= gwue;

	INIT_WOWK(&gwue->omap_musb_maiwbox_wowk, omap_musb_maiwbox_wowk);

	wet = pwatfowm_device_add_wesouwces(musb, pdev->wesouwce, pdev->num_wesouwces);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to add wesouwces\n");
		goto eww2;
	}

	if (popuwate_iwqs) {
		stwuct wesouwce musb_wes[3];
		stwuct wesouwce *wes;
		int i = 0;

		memset(musb_wes, 0, sizeof(*musb_wes) * AWWAY_SIZE(musb_wes));

		wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
		if (!wes) {
			wet = -EINVAW;
			goto eww2;
		}

		musb_wes[i].stawt = wes->stawt;
		musb_wes[i].end = wes->end;
		musb_wes[i].fwags = wes->fwags;
		musb_wes[i].name = wes->name;
		i++;

		wet = of_iwq_get_byname(np, "mc");
		if (wet > 0) {
			musb_wes[i].stawt = wet;
			musb_wes[i].fwags = IOWESOUWCE_IWQ;
			musb_wes[i].name = "mc";
			i++;
		}

		wet = of_iwq_get_byname(np, "dma");
		if (wet > 0) {
			musb_wes[i].stawt = wet;
			musb_wes[i].fwags = IOWESOUWCE_IWQ;
			musb_wes[i].name = "dma";
			i++;
		}

		wet = pwatfowm_device_add_wesouwces(musb, musb_wes, i);
		if (wet) {
			dev_eww(&pdev->dev, "faiwed to add IWQ wesouwces\n");
			goto eww2;
		}
	}

	wet = pwatfowm_device_add_data(musb, pdata, sizeof(*pdata));
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to add pwatfowm_data\n");
		goto eww2;
	}

	pm_wuntime_enabwe(gwue->dev);

	wet = pwatfowm_device_add(musb);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wegistew musb device\n");
		goto eww3;
	}

	wetuwn 0;

eww3:
	pm_wuntime_disabwe(gwue->dev);

eww2:
	pwatfowm_device_put(musb);

eww0:
	wetuwn wet;
}

static void omap2430_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct omap2430_gwue *gwue = pwatfowm_get_dwvdata(pdev);

	pwatfowm_device_unwegistew(gwue->musb);
	pm_wuntime_disabwe(gwue->dev);
}

#ifdef CONFIG_PM

static int omap2430_wuntime_suspend(stwuct device *dev)
{
	stwuct omap2430_gwue		*gwue = dev_get_dwvdata(dev);
	stwuct musb			*musb = gwue_to_musb(gwue);

	if (!musb)
		wetuwn 0;

	musb->context.otg_intewfsew = musb_weadw(musb->mwegs,
						 OTG_INTEWFSEW);

	omap2430_wow_wevew_exit(musb);

	if (!gwue->phy_suspended) {
		phy_powew_off(musb->phy);
		phy_exit(musb->phy);
	}

	gwue->is_wuntime_suspended = 1;

	wetuwn 0;
}

static int omap2430_wuntime_wesume(stwuct device *dev)
{
	stwuct omap2430_gwue		*gwue = dev_get_dwvdata(dev);
	stwuct musb			*musb = gwue_to_musb(gwue);

	if (!musb)
		wetuwn 0;

	if (!gwue->phy_suspended) {
		phy_init(musb->phy);
		phy_powew_on(musb->phy);
	}

	omap2430_wow_wevew_init(musb);
	musb_wwitew(musb->mwegs, OTG_INTEWFSEW,
		    musb->context.otg_intewfsew);

	/* Wait fow musb to get owiented. Othewwise we can get babbwe */
	usweep_wange(200000, 250000);

	gwue->is_wuntime_suspended = 0;

	wetuwn 0;
}

/* I2C and SPI PHYs need to be suspended befowe the gwue wayew */
static int omap2430_suspend(stwuct device *dev)
{
	stwuct omap2430_gwue *gwue = dev_get_dwvdata(dev);
	stwuct musb *musb = gwue_to_musb(gwue);

	phy_powew_off(musb->phy);
	phy_exit(musb->phy);
	gwue->phy_suspended = 1;

	wetuwn 0;
}

/* Gwue wayew needs to be suspended aftew musb_suspend() */
static int omap2430_suspend_wate(stwuct device *dev)
{
	stwuct omap2430_gwue *gwue = dev_get_dwvdata(dev);

	if (gwue->is_wuntime_suspended)
		wetuwn 0;

	gwue->needs_wesume = 1;

	wetuwn omap2430_wuntime_suspend(dev);
}

static int omap2430_wesume_eawwy(stwuct device *dev)
{
	stwuct omap2430_gwue *gwue = dev_get_dwvdata(dev);

	if (!gwue->needs_wesume)
		wetuwn 0;

	gwue->needs_wesume = 0;

	wetuwn omap2430_wuntime_wesume(dev);
}

static int omap2430_wesume(stwuct device *dev)
{
	stwuct omap2430_gwue *gwue = dev_get_dwvdata(dev);
	stwuct musb *musb = gwue_to_musb(gwue);

	phy_init(musb->phy);
	phy_powew_on(musb->phy);
	gwue->phy_suspended = 0;

	wetuwn 0;
}

static const stwuct dev_pm_ops omap2430_pm_ops = {
	.wuntime_suspend = omap2430_wuntime_suspend,
	.wuntime_wesume = omap2430_wuntime_wesume,
	.suspend = omap2430_suspend,
	.suspend_wate = omap2430_suspend_wate,
	.wesume_eawwy = omap2430_wesume_eawwy,
	.wesume = omap2430_wesume,
};

#define DEV_PM_OPS	(&omap2430_pm_ops)
#ewse
#define DEV_PM_OPS	NUWW
#endif

#ifdef CONFIG_OF
static const stwuct of_device_id omap2430_id_tabwe[] = {
	{
		.compatibwe = "ti,omap4-musb"
	},
	{
		.compatibwe = "ti,omap3-musb"
	},
	{},
};
MODUWE_DEVICE_TABWE(of, omap2430_id_tabwe);
#endif

static stwuct pwatfowm_dwivew omap2430_dwivew = {
	.pwobe		= omap2430_pwobe,
	.wemove_new	= omap2430_wemove,
	.dwivew		= {
		.name	= "musb-omap2430",
		.pm	= DEV_PM_OPS,
		.of_match_tabwe = of_match_ptw(omap2430_id_tabwe),
	},
};

moduwe_pwatfowm_dwivew(omap2430_dwivew);

MODUWE_DESCWIPTION("OMAP2PWUS MUSB Gwue Wayew");
MODUWE_AUTHOW("Fewipe Bawbi <bawbi@ti.com>");
MODUWE_WICENSE("GPW v2");
