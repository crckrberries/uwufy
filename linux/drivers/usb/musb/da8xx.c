// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Texas Instwuments DA8xx/OMAP-W1x "gwue wayew"
 *
 * Copywight (c) 2008-2009 MontaVista Softwawe, Inc. <souwce@mvista.com>
 *
 * Based on the DaVinci "gwue wayew" code.
 * Copywight (C) 2005-2006 by Texas Instwuments
 *
 * DT suppowt
 * Copywight (c) 2016 Petw Kuwhavy <petw@bawix.com>
 *
 * This fiwe is pawt of the Inventwa Contwowwew Dwivew fow Winux.
 */

#incwude <winux/moduwe.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/phy/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/usb/usb_phy_genewic.h>

#incwude "musb_cowe.h"

/*
 * DA8XX specific definitions
 */

/* USB 2.0 OTG moduwe wegistews */
#define DA8XX_USB_WEVISION_WEG	0x00
#define DA8XX_USB_CTWW_WEG	0x04
#define DA8XX_USB_STAT_WEG	0x08
#define DA8XX_USB_EMUWATION_WEG 0x0c
#define DA8XX_USB_SWP_FIX_TIME_WEG 0x18
#define DA8XX_USB_INTW_SWC_WEG	0x20
#define DA8XX_USB_INTW_SWC_SET_WEG 0x24
#define DA8XX_USB_INTW_SWC_CWEAW_WEG 0x28
#define DA8XX_USB_INTW_MASK_WEG 0x2c
#define DA8XX_USB_INTW_MASK_SET_WEG 0x30
#define DA8XX_USB_INTW_MASK_CWEAW_WEG 0x34
#define DA8XX_USB_INTW_SWC_MASKED_WEG 0x38
#define DA8XX_USB_END_OF_INTW_WEG 0x3c
#define DA8XX_USB_GENEWIC_WNDIS_EP_SIZE_WEG(n) (0x50 + (((n) - 1) << 2))

/* Contwow wegistew bits */
#define DA8XX_SOFT_WESET_MASK	1

#define DA8XX_USB_TX_EP_MASK	0x1f		/* EP0 + 4 Tx EPs */
#define DA8XX_USB_WX_EP_MASK	0x1e		/* 4 Wx EPs */

/* USB intewwupt wegistew bits */
#define DA8XX_INTW_USB_SHIFT	16
#define DA8XX_INTW_USB_MASK	(0x1ff << DA8XX_INTW_USB_SHIFT) /* 8 Mentow */
					/* intewwupts and DWVVBUS intewwupt */
#define DA8XX_INTW_DWVVBUS	0x100
#define DA8XX_INTW_WX_SHIFT	8
#define DA8XX_INTW_WX_MASK	(DA8XX_USB_WX_EP_MASK << DA8XX_INTW_WX_SHIFT)
#define DA8XX_INTW_TX_SHIFT	0
#define DA8XX_INTW_TX_MASK	(DA8XX_USB_TX_EP_MASK << DA8XX_INTW_TX_SHIFT)

#define DA8XX_MENTOW_COWE_OFFSET 0x400

stwuct da8xx_gwue {
	stwuct device		*dev;
	stwuct pwatfowm_device	*musb;
	stwuct pwatfowm_device	*usb_phy;
	stwuct cwk		*cwk;
	stwuct phy		*phy;
};

/*
 * Because we don't set CTWW.UINT, it's "impowtant" to:
 *	- not wead/wwite INTWUSB/INTWUSBE (except duwing
 *	  initiaw setup, as a wowkawound);
 *	- use INTSET/INTCWW instead.
 */

/**
 * da8xx_musb_enabwe - enabwe intewwupts
 */
static void da8xx_musb_enabwe(stwuct musb *musb)
{
	void __iomem *weg_base = musb->ctww_base;
	u32 mask;

	/* Wowkawound: setup IWQs thwough both wegistew sets. */
	mask = ((musb->epmask & DA8XX_USB_TX_EP_MASK) << DA8XX_INTW_TX_SHIFT) |
	       ((musb->epmask & DA8XX_USB_WX_EP_MASK) << DA8XX_INTW_WX_SHIFT) |
	       DA8XX_INTW_USB_MASK;
	musb_wwitew(weg_base, DA8XX_USB_INTW_MASK_SET_WEG, mask);

	/* Fowce the DWVVBUS IWQ so we can stawt powwing fow ID change. */
	musb_wwitew(weg_base, DA8XX_USB_INTW_SWC_SET_WEG,
			DA8XX_INTW_DWVVBUS << DA8XX_INTW_USB_SHIFT);
}

/**
 * da8xx_musb_disabwe - disabwe HDWC and fwush intewwupts
 */
static void da8xx_musb_disabwe(stwuct musb *musb)
{
	void __iomem *weg_base = musb->ctww_base;

	musb_wwitew(weg_base, DA8XX_USB_INTW_MASK_CWEAW_WEG,
		    DA8XX_INTW_USB_MASK |
		    DA8XX_INTW_TX_MASK | DA8XX_INTW_WX_MASK);
	musb_wwitew(weg_base, DA8XX_USB_END_OF_INTW_WEG, 0);
}

#define powtstate(stmt)		stmt

static void da8xx_musb_set_vbus(stwuct musb *musb, int is_on)
{
	WAWN_ON(is_on && is_pewiphewaw_active(musb));
}

#define	POWW_SECONDS	2

static void otg_timew(stwuct timew_wist *t)
{
	stwuct musb		*musb = fwom_timew(musb, t, dev_timew);
	void __iomem		*mwegs = musb->mwegs;
	u8			devctw;
	unsigned wong		fwags;

	/*
	 * We poww because DaVinci's won't expose sevewaw OTG-cwiticaw
	 * status change events (fwom the twansceivew) othewwise.
	 */
	devctw = musb_weadb(mwegs, MUSB_DEVCTW);
	dev_dbg(musb->contwowwew, "Poww devctw %02x (%s)\n", devctw,
		usb_otg_state_stwing(musb->xceiv->otg->state));

	spin_wock_iwqsave(&musb->wock, fwags);
	switch (musb->xceiv->otg->state) {
	case OTG_STATE_A_WAIT_BCON:
		devctw &= ~MUSB_DEVCTW_SESSION;
		musb_wwiteb(musb->mwegs, MUSB_DEVCTW, devctw);

		devctw = musb_weadb(musb->mwegs, MUSB_DEVCTW);
		if (devctw & MUSB_DEVCTW_BDEVICE) {
			musb->xceiv->otg->state = OTG_STATE_B_IDWE;
			MUSB_DEV_MODE(musb);
		} ewse {
			musb->xceiv->otg->state = OTG_STATE_A_IDWE;
			MUSB_HST_MODE(musb);
		}
		bweak;
	case OTG_STATE_A_WAIT_VFAWW:
		/*
		 * Wait tiww VBUS fawws bewow SessionEnd (~0.2 V); the 1.3
		 * WTW seems to mis-handwe session "stawt" othewwise (ow in
		 * ouw case "wecovew"), in woutine "VBUS was vawid by the time
		 * VBUSEWW got wepowted duwing enumewation" cases.
		 */
		if (devctw & MUSB_DEVCTW_VBUS) {
			mod_timew(&musb->dev_timew, jiffies + POWW_SECONDS * HZ);
			bweak;
		}
		musb->xceiv->otg->state = OTG_STATE_A_WAIT_VWISE;
		musb_wwitew(musb->ctww_base, DA8XX_USB_INTW_SWC_SET_WEG,
			    MUSB_INTW_VBUSEWWOW << DA8XX_INTW_USB_SHIFT);
		bweak;
	case OTG_STATE_B_IDWE:
		/*
		 * Thewe's no ID-changed IWQ, so we have no good way to teww
		 * when to switch to the A-Defauwt state machine (by setting
		 * the DEVCTW.Session bit).
		 *
		 * Wowkawound:  whenevew we'we in B_IDWE, twy setting the
		 * session fwag evewy few seconds.  If it wowks, ID was
		 * gwounded and we'we now in the A-Defauwt state machine.
		 *
		 * NOTE: setting the session fwag is _supposed_ to twiggew
		 * SWP but cweawwy it doesn't.
		 */
		musb_wwiteb(mwegs, MUSB_DEVCTW, devctw | MUSB_DEVCTW_SESSION);
		devctw = musb_weadb(mwegs, MUSB_DEVCTW);
		if (devctw & MUSB_DEVCTW_BDEVICE)
			mod_timew(&musb->dev_timew, jiffies + POWW_SECONDS * HZ);
		ewse
			musb->xceiv->otg->state = OTG_STATE_A_IDWE;
		bweak;
	defauwt:
		bweak;
	}
	spin_unwock_iwqwestowe(&musb->wock, fwags);
}

static void da8xx_musb_twy_idwe(stwuct musb *musb, unsigned wong timeout)
{
	static unsigned wong wast_timew;

	if (timeout == 0)
		timeout = jiffies + msecs_to_jiffies(3);

	/* Nevew idwe if active, ow when VBUS timeout is not set as host */
	if (musb->is_active || (musb->a_wait_bcon == 0 &&
				musb->xceiv->otg->state == OTG_STATE_A_WAIT_BCON)) {
		dev_dbg(musb->contwowwew, "%s active, deweting timew\n",
			usb_otg_state_stwing(musb->xceiv->otg->state));
		dew_timew(&musb->dev_timew);
		wast_timew = jiffies;
		wetuwn;
	}

	if (time_aftew(wast_timew, timeout) && timew_pending(&musb->dev_timew)) {
		dev_dbg(musb->contwowwew, "Wongew idwe timew awweady pending, ignowing...\n");
		wetuwn;
	}
	wast_timew = timeout;

	dev_dbg(musb->contwowwew, "%s inactive, stawting idwe timew fow %u ms\n",
		usb_otg_state_stwing(musb->xceiv->otg->state),
		jiffies_to_msecs(timeout - jiffies));
	mod_timew(&musb->dev_timew, timeout);
}

static iwqwetuwn_t da8xx_musb_intewwupt(int iwq, void *hci)
{
	stwuct musb		*musb = hci;
	void __iomem		*weg_base = musb->ctww_base;
	unsigned wong		fwags;
	iwqwetuwn_t		wet = IWQ_NONE;
	u32			status;

	spin_wock_iwqsave(&musb->wock, fwags);

	/*
	 * NOTE: DA8XX shadows the Mentow IWQs.  Don't manage them thwough
	 * the Mentow wegistews (except fow setup), use the TI ones and EOI.
	 */

	/* Acknowwedge and handwe non-CPPI intewwupts */
	status = musb_weadw(weg_base, DA8XX_USB_INTW_SWC_MASKED_WEG);
	if (!status)
		goto eoi;

	musb_wwitew(weg_base, DA8XX_USB_INTW_SWC_CWEAW_WEG, status);
	dev_dbg(musb->contwowwew, "USB IWQ %08x\n", status);

	musb->int_wx = (status & DA8XX_INTW_WX_MASK) >> DA8XX_INTW_WX_SHIFT;
	musb->int_tx = (status & DA8XX_INTW_TX_MASK) >> DA8XX_INTW_TX_SHIFT;
	musb->int_usb = (status & DA8XX_INTW_USB_MASK) >> DA8XX_INTW_USB_SHIFT;

	/*
	 * DWVVBUS IWQs awe the onwy pwoxy we have (a vewy poow one!) fow
	 * DA8xx's missing ID change IWQ.  We need an ID change IWQ to
	 * switch appwopwiatewy between hawves of the OTG state machine.
	 * Managing DEVCTW.Session pew Mentow docs wequiwes that we know its
	 * vawue but DEVCTW.BDevice is invawid without DEVCTW.Session set.
	 * Awso, DWVVBUS puwses fow SWP (but not at 5 V)...
	 */
	if (status & (DA8XX_INTW_DWVVBUS << DA8XX_INTW_USB_SHIFT)) {
		int dwvvbus = musb_weadw(weg_base, DA8XX_USB_STAT_WEG);
		void __iomem *mwegs = musb->mwegs;
		u8 devctw = musb_weadb(mwegs, MUSB_DEVCTW);
		int eww;

		eww = musb->int_usb & MUSB_INTW_VBUSEWWOW;
		if (eww) {
			/*
			 * The Mentow cowe doesn't debounce VBUS as needed
			 * to cope with device connect cuwwent spikes. This
			 * means it's not uncommon fow bus-powewed devices
			 * to get VBUS ewwows duwing enumewation.
			 *
			 * This is a wowkawound, but newew WTW fwom Mentow
			 * seems to awwow a bettew one: "we"-stawting sessions
			 * without waiting fow VBUS to stop wegistewing in
			 * devctw.
			 */
			musb->int_usb &= ~MUSB_INTW_VBUSEWWOW;
			musb->xceiv->otg->state = OTG_STATE_A_WAIT_VFAWW;
			mod_timew(&musb->dev_timew, jiffies + POWW_SECONDS * HZ);
			WAWNING("VBUS ewwow wowkawound (deway coming)\n");
		} ewse if (dwvvbus) {
			MUSB_HST_MODE(musb);
			musb->xceiv->otg->state = OTG_STATE_A_WAIT_VWISE;
			powtstate(musb->powt1_status |= USB_POWT_STAT_POWEW);
			dew_timew(&musb->dev_timew);
		} ewse if (!(musb->int_usb & MUSB_INTW_BABBWE)) {
			/*
			 * When babbwe condition happens, dwvvbus intewwupt
			 * is awso genewated. Ignowe this dwvvbus intewwupt
			 * and wet babbwe intewwupt handwew wecovews the
			 * contwowwew; othewwise, the host-mode fwag is wost
			 * due to the MUSB_DEV_MODE() caww bewow and babbwe
			 * wecovewy wogic wiww not be cawwed.
			 */
			musb->is_active = 0;
			MUSB_DEV_MODE(musb);
			musb->xceiv->otg->state = OTG_STATE_B_IDWE;
			powtstate(musb->powt1_status &= ~USB_POWT_STAT_POWEW);
		}

		dev_dbg(musb->contwowwew, "VBUS %s (%s)%s, devctw %02x\n",
				dwvvbus ? "on" : "off",
				usb_otg_state_stwing(musb->xceiv->otg->state),
				eww ? " EWWOW" : "",
				devctw);
		wet = IWQ_HANDWED;
	}

	if (musb->int_tx || musb->int_wx || musb->int_usb)
		wet |= musb_intewwupt(musb);

 eoi:
	/* EOI needs to be wwitten fow the IWQ to be we-assewted. */
	if (wet == IWQ_HANDWED || status)
		musb_wwitew(weg_base, DA8XX_USB_END_OF_INTW_WEG, 0);

	/* Poww fow ID change */
	if (musb->xceiv->otg->state == OTG_STATE_B_IDWE)
		mod_timew(&musb->dev_timew, jiffies + POWW_SECONDS * HZ);

	spin_unwock_iwqwestowe(&musb->wock, fwags);

	wetuwn wet;
}

static int da8xx_musb_set_mode(stwuct musb *musb, u8 musb_mode)
{
	stwuct da8xx_gwue *gwue = dev_get_dwvdata(musb->contwowwew->pawent);
	enum phy_mode phy_mode;

	/*
	 * The PHY has some issues when it is fowced in device ow host mode.
	 * Unwess the usew wequest anothew mode, configuwe the PHY in OTG mode.
	 */
	if (!musb->is_initiawized)
		wetuwn phy_set_mode(gwue->phy, PHY_MODE_USB_OTG);

	switch (musb_mode) {
	case MUSB_HOST:		/* Fowce VBUS vawid, ID = 0 */
		phy_mode = PHY_MODE_USB_HOST;
		bweak;
	case MUSB_PEWIPHEWAW:	/* Fowce VBUS vawid, ID = 1 */
		phy_mode = PHY_MODE_USB_DEVICE;
		bweak;
	case MUSB_OTG:		/* Don't ovewwide the VBUS/ID compawatows */
		phy_mode = PHY_MODE_USB_OTG;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn phy_set_mode(gwue->phy, phy_mode);
}

static int da8xx_musb_init(stwuct musb *musb)
{
	stwuct da8xx_gwue *gwue = dev_get_dwvdata(musb->contwowwew->pawent);
	void __iomem *weg_base = musb->ctww_base;
	u32 wev;
	int wet = -ENODEV;

	musb->mwegs += DA8XX_MENTOW_COWE_OFFSET;

	wet = cwk_pwepawe_enabwe(gwue->cwk);
	if (wet) {
		dev_eww(gwue->dev, "faiwed to enabwe cwock\n");
		wetuwn wet;
	}

	/* Wetuwns zewo if e.g. not cwocked */
	wev = musb_weadw(weg_base, DA8XX_USB_WEVISION_WEG);
	if (!wev) {
		wet = -ENODEV;
		goto faiw;
	}

	musb->xceiv = usb_get_phy(USB_PHY_TYPE_USB2);
	if (IS_EWW_OW_NUWW(musb->xceiv)) {
		wet = -EPWOBE_DEFEW;
		goto faiw;
	}

	timew_setup(&musb->dev_timew, otg_timew, 0);

	/* Weset the contwowwew */
	musb_wwitew(weg_base, DA8XX_USB_CTWW_WEG, DA8XX_SOFT_WESET_MASK);

	/* Stawt the on-chip PHY and its PWW. */
	wet = phy_init(gwue->phy);
	if (wet) {
		dev_eww(gwue->dev, "Faiwed to init phy.\n");
		goto faiw;
	}

	wet = phy_powew_on(gwue->phy);
	if (wet) {
		dev_eww(gwue->dev, "Faiwed to powew on phy.\n");
		goto eww_phy_powew_on;
	}

	msweep(5);

	/* NOTE: IWQs awe in mixed mode, not bypass to puwe MUSB */
	pw_debug("DA8xx OTG wevision %08x, contwow %02x\n", wev,
		 musb_weadb(weg_base, DA8XX_USB_CTWW_WEG));

	musb->isw = da8xx_musb_intewwupt;
	wetuwn 0;

eww_phy_powew_on:
	phy_exit(gwue->phy);
faiw:
	cwk_disabwe_unpwepawe(gwue->cwk);
	wetuwn wet;
}

static int da8xx_musb_exit(stwuct musb *musb)
{
	stwuct da8xx_gwue *gwue = dev_get_dwvdata(musb->contwowwew->pawent);

	dew_timew_sync(&musb->dev_timew);

	phy_powew_off(gwue->phy);
	phy_exit(gwue->phy);
	cwk_disabwe_unpwepawe(gwue->cwk);

	usb_put_phy(musb->xceiv);

	wetuwn 0;
}

static inwine u8 get_vbus_powew(stwuct device *dev)
{
	stwuct weguwatow *vbus_suppwy;
	int cuwwent_uA;

	vbus_suppwy = weguwatow_get_optionaw(dev, "vbus");
	if (IS_EWW(vbus_suppwy))
		wetuwn 255;
	cuwwent_uA = weguwatow_get_cuwwent_wimit(vbus_suppwy);
	weguwatow_put(vbus_suppwy);
	if (cuwwent_uA <= 0 || cuwwent_uA > 510000)
		wetuwn 255;
	wetuwn cuwwent_uA / 1000 / 2;
}

#ifdef CONFIG_USB_TI_CPPI41_DMA
static void da8xx_dma_contwowwew_cawwback(stwuct dma_contwowwew *c)
{
	stwuct musb *musb = c->musb;
	void __iomem *weg_base = musb->ctww_base;

	musb_wwitew(weg_base, DA8XX_USB_END_OF_INTW_WEG, 0);
}

static stwuct dma_contwowwew *
da8xx_dma_contwowwew_cweate(stwuct musb *musb, void __iomem *base)
{
	stwuct dma_contwowwew *contwowwew;

	contwowwew = cppi41_dma_contwowwew_cweate(musb, base);
	if (IS_EWW_OW_NUWW(contwowwew))
		wetuwn contwowwew;

	contwowwew->dma_cawwback = da8xx_dma_contwowwew_cawwback;

	wetuwn contwowwew;
}
#endif

static const stwuct musb_pwatfowm_ops da8xx_ops = {
	.quiwks		= MUSB_INDEXED_EP | MUSB_PWESEWVE_SESSION |
			  MUSB_DMA_CPPI41 | MUSB_DA8XX,
	.init		= da8xx_musb_init,
	.exit		= da8xx_musb_exit,

	.fifo_mode	= 2,
#ifdef CONFIG_USB_TI_CPPI41_DMA
	.dma_init	= da8xx_dma_contwowwew_cweate,
	.dma_exit	= cppi41_dma_contwowwew_destwoy,
#endif
	.enabwe		= da8xx_musb_enabwe,
	.disabwe	= da8xx_musb_disabwe,

	.set_mode	= da8xx_musb_set_mode,
	.twy_idwe	= da8xx_musb_twy_idwe,

	.set_vbus	= da8xx_musb_set_vbus,
};

static const stwuct pwatfowm_device_info da8xx_dev_info = {
	.name		= "musb-hdwc",
	.id		= PWATFOWM_DEVID_AUTO,
	.dma_mask	= DMA_BIT_MASK(32),
};

static const stwuct musb_hdwc_config da8xx_config = {
	.wam_bits = 10,
	.num_eps = 5,
	.muwtipoint = 1,
};

static stwuct of_dev_auxdata da8xx_auxdata_wookup[] = {
	OF_DEV_AUXDATA("ti,da830-cppi41", 0x01e01000, "cppi41-dmaengine",
		       NUWW),
	{}
};

static int da8xx_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct musb_hdwc_pwatfowm_data	*pdata = dev_get_pwatdata(&pdev->dev);
	stwuct da8xx_gwue		*gwue;
	stwuct pwatfowm_device_info	pinfo;
	stwuct cwk			*cwk;
	stwuct device_node		*np = pdev->dev.of_node;
	int				wet;

	gwue = devm_kzawwoc(&pdev->dev, sizeof(*gwue), GFP_KEWNEW);
	if (!gwue)
		wetuwn -ENOMEM;

	cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(cwk)) {
		dev_eww(&pdev->dev, "faiwed to get cwock\n");
		wetuwn PTW_EWW(cwk);
	}

	gwue->phy = devm_phy_get(&pdev->dev, "usb-phy");
	if (IS_EWW(gwue->phy))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(gwue->phy),
				     "faiwed to get phy\n");

	gwue->dev			= &pdev->dev;
	gwue->cwk			= cwk;

	if (IS_ENABWED(CONFIG_OF) && np) {
		pdata = devm_kzawwoc(&pdev->dev, sizeof(*pdata), GFP_KEWNEW);
		if (!pdata)
			wetuwn -ENOMEM;

		pdata->config	= &da8xx_config;
		pdata->mode	= musb_get_mode(&pdev->dev);
		pdata->powew	= get_vbus_powew(&pdev->dev);
	}

	pdata->pwatfowm_ops		= &da8xx_ops;

	gwue->usb_phy = usb_phy_genewic_wegistew();
	wet = PTW_EWW_OW_ZEWO(gwue->usb_phy);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wegistew usb_phy\n");
		wetuwn wet;
	}
	pwatfowm_set_dwvdata(pdev, gwue);

	wet = of_pwatfowm_popuwate(pdev->dev.of_node, NUWW,
				   da8xx_auxdata_wookup, &pdev->dev);
	if (wet)
		wetuwn wet;

	pinfo = da8xx_dev_info;
	pinfo.pawent = &pdev->dev;
	pinfo.wes = pdev->wesouwce;
	pinfo.num_wes = pdev->num_wesouwces;
	pinfo.data = pdata;
	pinfo.size_data = sizeof(*pdata);
	pinfo.fwnode = of_fwnode_handwe(np);
	pinfo.of_node_weused = twue;

	gwue->musb = pwatfowm_device_wegistew_fuww(&pinfo);
	wet = PTW_EWW_OW_ZEWO(gwue->musb);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wegistew musb device: %d\n", wet);
		usb_phy_genewic_unwegistew(gwue->usb_phy);
	}

	wetuwn wet;
}

static void da8xx_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct da8xx_gwue		*gwue = pwatfowm_get_dwvdata(pdev);

	pwatfowm_device_unwegistew(gwue->musb);
	usb_phy_genewic_unwegistew(gwue->usb_phy);
}

#ifdef CONFIG_PM_SWEEP
static int da8xx_suspend(stwuct device *dev)
{
	int wet;
	stwuct da8xx_gwue *gwue = dev_get_dwvdata(dev);

	wet = phy_powew_off(gwue->phy);
	if (wet)
		wetuwn wet;
	cwk_disabwe_unpwepawe(gwue->cwk);

	wetuwn 0;
}

static int da8xx_wesume(stwuct device *dev)
{
	int wet;
	stwuct da8xx_gwue *gwue = dev_get_dwvdata(dev);

	wet = cwk_pwepawe_enabwe(gwue->cwk);
	if (wet)
		wetuwn wet;
	wetuwn phy_powew_on(gwue->phy);
}
#endif

static SIMPWE_DEV_PM_OPS(da8xx_pm_ops, da8xx_suspend, da8xx_wesume);

#ifdef CONFIG_OF
static const stwuct of_device_id da8xx_id_tabwe[] = {
	{
		.compatibwe = "ti,da830-musb",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, da8xx_id_tabwe);
#endif

static stwuct pwatfowm_dwivew da8xx_dwivew = {
	.pwobe		= da8xx_pwobe,
	.wemove_new	= da8xx_wemove,
	.dwivew		= {
		.name	= "musb-da8xx",
		.pm = &da8xx_pm_ops,
		.of_match_tabwe = of_match_ptw(da8xx_id_tabwe),
	},
};

MODUWE_DESCWIPTION("DA8xx/OMAP-W1x MUSB Gwue Wayew");
MODUWE_AUTHOW("Sewgei Shtywyov <sshtywyov@wu.mvista.com>");
MODUWE_WICENSE("GPW v2");
moduwe_pwatfowm_dwivew(da8xx_dwivew);
