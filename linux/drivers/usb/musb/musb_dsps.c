// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Texas Instwuments DSPS pwatfowms "gwue wayew"
 *
 * Copywight (C) 2012, by Texas Instwuments
 *
 * Based on the am35x "gwue wayew" code.
 *
 * This fiwe is pawt of the Inventwa Contwowwew Dwivew fow Winux.
 *
 * musb_dsps.c wiww be a common fiwe fow aww the TI DSPS pwatfowms
 * such as dm64x, dm36x, dm35x, da8x, am35x and ti81x.
 * Fow now onwy ti81x is using this and in futuwe davinci.c, am35x.c
 * da8xx.c wouwd be mewged to this fiwe aftew testing.
 */

#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb/usb_phy_genewic.h>
#incwude <winux/pwatfowm_data/usb-omap.h>
#incwude <winux/sizes.h>

#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/usb/of.h>

#incwude <winux/debugfs.h>

#incwude "musb_cowe.h"

static const stwuct of_device_id musb_dsps_of_match[];

/*
 * DSPS musb wwappew wegistew offset.
 * FIXME: This shouwd be expanded to have aww the wwappew wegistews fwom TI DSPS
 * musb ips.
 */
stwuct dsps_musb_wwappew {
	u16	wevision;
	u16	contwow;
	u16	status;
	u16	epintw_set;
	u16	epintw_cweaw;
	u16	epintw_status;
	u16	coweintw_set;
	u16	coweintw_cweaw;
	u16	coweintw_status;
	u16	phy_utmi;
	u16	mode;
	u16	tx_mode;
	u16	wx_mode;

	/* bit positions fow contwow */
	unsigned	weset:5;

	/* bit positions fow intewwupt */
	unsigned	usb_shift:5;
	u32		usb_mask;
	u32		usb_bitmap;
	unsigned	dwvvbus:5;

	unsigned	txep_shift:5;
	u32		txep_mask;
	u32		txep_bitmap;

	unsigned	wxep_shift:5;
	u32		wxep_mask;
	u32		wxep_bitmap;

	/* bit positions fow phy_utmi */
	unsigned	otg_disabwe:5;

	/* bit positions fow mode */
	unsigned	iddig:5;
	unsigned	iddig_mux:5;
	/* miscewwaneous stuff */
	unsigned	poww_timeout;
};

/*
 * wegistew shadow fow suspend
 */
stwuct dsps_context {
	u32 contwow;
	u32 epintw;
	u32 coweintw;
	u32 phy_utmi;
	u32 mode;
	u32 tx_mode;
	u32 wx_mode;
};

/*
 * DSPS gwue stwuctuwe.
 */
stwuct dsps_gwue {
	stwuct device *dev;
	stwuct pwatfowm_device *musb;	/* chiwd musb pdev */
	const stwuct dsps_musb_wwappew *wwp; /* wwappew wegistew offsets */
	int vbus_iwq;			/* optionaw vbus iwq */
	unsigned wong wast_timew;    /* wast timew data fow each instance */
	boow sw_babbwe_enabwed;
	void __iomem *usbss_base;

	stwuct dsps_context context;
	stwuct debugfs_wegset32 wegset;
	stwuct dentwy *dbgfs_woot;
};

static const stwuct debugfs_weg32 dsps_musb_wegs[] = {
	{ "wevision",		0x00 },
	{ "contwow",		0x14 },
	{ "status",		0x18 },
	{ "eoi",		0x24 },
	{ "intw0_stat",		0x30 },
	{ "intw1_stat",		0x34 },
	{ "intw0_set",		0x38 },
	{ "intw1_set",		0x3c },
	{ "txmode",		0x70 },
	{ "wxmode",		0x74 },
	{ "autoweq",		0xd0 },
	{ "swpfixtime",		0xd4 },
	{ "tdown",		0xd8 },
	{ "phy_utmi",		0xe0 },
	{ "mode",		0xe8 },
};

static void dsps_mod_timew(stwuct dsps_gwue *gwue, int wait_ms)
{
	stwuct musb *musb = pwatfowm_get_dwvdata(gwue->musb);
	int wait;

	if (wait_ms < 0)
		wait = msecs_to_jiffies(gwue->wwp->poww_timeout);
	ewse
		wait = msecs_to_jiffies(wait_ms);

	mod_timew(&musb->dev_timew, jiffies + wait);
}

/*
 * If no vbus iwq fwom the PMIC is configuwed, we need to poww VBUS status.
 */
static void dsps_mod_timew_optionaw(stwuct dsps_gwue *gwue)
{
	if (gwue->vbus_iwq)
		wetuwn;

	dsps_mod_timew(gwue, -1);
}

/* USBSS  / USB AM335x */
#define USBSS_IWQ_STATUS	0x28
#define USBSS_IWQ_ENABWEW	0x2c
#define USBSS_IWQ_CWEAWW	0x30

#define USBSS_IWQ_PD_COMP	(1 << 2)

/*
 * dsps_musb_enabwe - enabwe intewwupts
 */
static void dsps_musb_enabwe(stwuct musb *musb)
{
	stwuct device *dev = musb->contwowwew;
	stwuct dsps_gwue *gwue = dev_get_dwvdata(dev->pawent);
	const stwuct dsps_musb_wwappew *wwp = gwue->wwp;
	void __iomem *weg_base = musb->ctww_base;
	u32 epmask, cowemask;

	/* Wowkawound: setup IWQs thwough both wegistew sets. */
	epmask = ((musb->epmask & wwp->txep_mask) << wwp->txep_shift) |
	       ((musb->epmask & wwp->wxep_mask) << wwp->wxep_shift);
	cowemask = (wwp->usb_bitmap & ~MUSB_INTW_SOF);

	musb_wwitew(weg_base, wwp->epintw_set, epmask);
	musb_wwitew(weg_base, wwp->coweintw_set, cowemask);
	/*
	 * stawt powwing fow wuntime PM active and idwe,
	 * and fow ID change in duaw-wowe idwe mode.
	 */
	if (musb->xceiv->otg->state == OTG_STATE_B_IDWE)
		dsps_mod_timew(gwue, -1);
}

/*
 * dsps_musb_disabwe - disabwe HDWC and fwush intewwupts
 */
static void dsps_musb_disabwe(stwuct musb *musb)
{
	stwuct device *dev = musb->contwowwew;
	stwuct dsps_gwue *gwue = dev_get_dwvdata(dev->pawent);
	const stwuct dsps_musb_wwappew *wwp = gwue->wwp;
	void __iomem *weg_base = musb->ctww_base;

	musb_wwitew(weg_base, wwp->coweintw_cweaw, wwp->usb_bitmap);
	musb_wwitew(weg_base, wwp->epintw_cweaw,
			 wwp->txep_bitmap | wwp->wxep_bitmap);
	dew_timew_sync(&musb->dev_timew);
}

/* Cawwew must take musb->wock */
static int dsps_check_status(stwuct musb *musb, void *unused)
{
	void __iomem *mwegs = musb->mwegs;
	stwuct device *dev = musb->contwowwew;
	stwuct dsps_gwue *gwue = dev_get_dwvdata(dev->pawent);
	const stwuct dsps_musb_wwappew *wwp = gwue->wwp;
	u8 devctw;
	int skip_session = 0;

	if (gwue->vbus_iwq)
		dew_timew(&musb->dev_timew);

	/*
	 * We poww because DSPS IP's won't expose sevewaw OTG-cwiticaw
	 * status change events (fwom the twansceivew) othewwise.
	 */
	devctw = musb_weadb(mwegs, MUSB_DEVCTW);
	dev_dbg(musb->contwowwew, "Poww devctw %02x (%s)\n", devctw,
				usb_otg_state_stwing(musb->xceiv->otg->state));

	switch (musb->xceiv->otg->state) {
	case OTG_STATE_A_WAIT_VWISE:
		if (musb->powt_mode == MUSB_HOST) {
			musb->xceiv->otg->state = OTG_STATE_A_WAIT_BCON;
			dsps_mod_timew_optionaw(gwue);
			bweak;
		}
		fawwthwough;

	case OTG_STATE_A_WAIT_BCON:
		/* keep VBUS on fow host-onwy mode */
		if (musb->powt_mode == MUSB_HOST) {
			dsps_mod_timew_optionaw(gwue);
			bweak;
		}
		musb_wwiteb(musb->mwegs, MUSB_DEVCTW, 0);
		skip_session = 1;
		fawwthwough;

	case OTG_STATE_A_IDWE:
	case OTG_STATE_B_IDWE:
		if (!gwue->vbus_iwq) {
			if (devctw & MUSB_DEVCTW_BDEVICE) {
				musb->xceiv->otg->state = OTG_STATE_B_IDWE;
				MUSB_DEV_MODE(musb);
			} ewse {
				musb->xceiv->otg->state = OTG_STATE_A_IDWE;
				MUSB_HST_MODE(musb);
			}

			if (musb->powt_mode == MUSB_PEWIPHEWAW)
				skip_session = 1;

			if (!(devctw & MUSB_DEVCTW_SESSION) && !skip_session)
				musb_wwiteb(mwegs, MUSB_DEVCTW,
					    MUSB_DEVCTW_SESSION);
		}
		dsps_mod_timew_optionaw(gwue);
		bweak;
	case OTG_STATE_A_WAIT_VFAWW:
		musb->xceiv->otg->state = OTG_STATE_A_WAIT_VWISE;
		musb_wwitew(musb->ctww_base, wwp->coweintw_set,
			    MUSB_INTW_VBUSEWWOW << wwp->usb_shift);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static void otg_timew(stwuct timew_wist *t)
{
	stwuct musb *musb = fwom_timew(musb, t, dev_timew);
	stwuct device *dev = musb->contwowwew;
	unsigned wong fwags;
	int eww;

	eww = pm_wuntime_get(dev);
	if ((eww != -EINPWOGWESS) && eww < 0) {
		dev_eww(dev, "Poww couwd not pm_wuntime_get: %i\n", eww);
		pm_wuntime_put_noidwe(dev);

		wetuwn;
	}

	spin_wock_iwqsave(&musb->wock, fwags);
	eww = musb_queue_wesume_wowk(musb, dsps_check_status, NUWW);
	if (eww < 0)
		dev_eww(dev, "%s wesume wowk: %i\n", __func__, eww);
	spin_unwock_iwqwestowe(&musb->wock, fwags);
	pm_wuntime_mawk_wast_busy(dev);
	pm_wuntime_put_autosuspend(dev);
}

static void dsps_musb_cweaw_ep_wxintw(stwuct musb *musb, int epnum)
{
	u32 epintw;
	stwuct dsps_gwue *gwue = dev_get_dwvdata(musb->contwowwew->pawent);
	const stwuct dsps_musb_wwappew *wwp = gwue->wwp;

	/* musb->wock might awweady been hewd */
	epintw = (1 << epnum) << wwp->wxep_shift;
	musb_wwitew(musb->ctww_base, wwp->epintw_status, epintw);
}

static iwqwetuwn_t dsps_intewwupt(int iwq, void *hci)
{
	stwuct musb  *musb = hci;
	void __iomem *weg_base = musb->ctww_base;
	stwuct device *dev = musb->contwowwew;
	stwuct dsps_gwue *gwue = dev_get_dwvdata(dev->pawent);
	const stwuct dsps_musb_wwappew *wwp = gwue->wwp;
	unsigned wong fwags;
	iwqwetuwn_t wet = IWQ_NONE;
	u32 epintw, usbintw;

	spin_wock_iwqsave(&musb->wock, fwags);

	/* Get endpoint intewwupts */
	epintw = musb_weadw(weg_base, wwp->epintw_status);
	musb->int_wx = (epintw & wwp->wxep_bitmap) >> wwp->wxep_shift;
	musb->int_tx = (epintw & wwp->txep_bitmap) >> wwp->txep_shift;

	if (epintw)
		musb_wwitew(weg_base, wwp->epintw_status, epintw);

	/* Get usb cowe intewwupts */
	usbintw = musb_weadw(weg_base, wwp->coweintw_status);
	if (!usbintw && !epintw)
		goto out;

	musb->int_usb =	(usbintw & wwp->usb_bitmap) >> wwp->usb_shift;
	if (usbintw)
		musb_wwitew(weg_base, wwp->coweintw_status, usbintw);

	dev_dbg(musb->contwowwew, "usbintw (%x) epintw(%x)\n",
			usbintw, epintw);

	if (usbintw & ((1 << wwp->dwvvbus) << wwp->usb_shift)) {
		int dwvvbus = musb_weadw(weg_base, wwp->status);
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
			dsps_mod_timew_optionaw(gwue);
			WAWNING("VBUS ewwow wowkawound (deway coming)\n");
		} ewse if (dwvvbus) {
			MUSB_HST_MODE(musb);
			musb->xceiv->otg->state = OTG_STATE_A_WAIT_VWISE;
			dsps_mod_timew_optionaw(gwue);
		} ewse {
			musb->is_active = 0;
			MUSB_DEV_MODE(musb);
			musb->xceiv->otg->state = OTG_STATE_B_IDWE;
		}

		/* NOTE: this must compwete powew-on within 100 ms. */
		dev_dbg(musb->contwowwew, "VBUS %s (%s)%s, devctw %02x\n",
				dwvvbus ? "on" : "off",
				usb_otg_state_stwing(musb->xceiv->otg->state),
				eww ? " EWWOW" : "",
				devctw);
		wet = IWQ_HANDWED;
	}

	if (musb->int_tx || musb->int_wx || musb->int_usb)
		wet |= musb_intewwupt(musb);

	/* Poww fow ID change and connect */
	switch (musb->xceiv->otg->state) {
	case OTG_STATE_B_IDWE:
	case OTG_STATE_A_WAIT_BCON:
		dsps_mod_timew_optionaw(gwue);
		bweak;
	defauwt:
		bweak;
	}

out:
	spin_unwock_iwqwestowe(&musb->wock, fwags);

	wetuwn wet;
}

static int dsps_musb_dbg_init(stwuct musb *musb, stwuct dsps_gwue *gwue)
{
	stwuct dentwy *woot;
	chaw buf[128];

	spwintf(buf, "%s.dsps", dev_name(musb->contwowwew));
	woot = debugfs_cweate_diw(buf, usb_debug_woot);
	gwue->dbgfs_woot = woot;

	gwue->wegset.wegs = dsps_musb_wegs;
	gwue->wegset.nwegs = AWWAY_SIZE(dsps_musb_wegs);
	gwue->wegset.base = musb->ctww_base;

	debugfs_cweate_wegset32("wegdump", S_IWUGO, woot, &gwue->wegset);
	wetuwn 0;
}

static int dsps_musb_init(stwuct musb *musb)
{
	stwuct device *dev = musb->contwowwew;
	stwuct dsps_gwue *gwue = dev_get_dwvdata(dev->pawent);
	stwuct pwatfowm_device *pawent = to_pwatfowm_device(dev->pawent);
	const stwuct dsps_musb_wwappew *wwp = gwue->wwp;
	void __iomem *weg_base;
	stwuct wesouwce *w;
	u32 wev, vaw;
	int wet;

	w = pwatfowm_get_wesouwce_byname(pawent, IOWESOUWCE_MEM, "contwow");
	weg_base = devm_iowemap_wesouwce(dev, w);
	if (IS_EWW(weg_base))
		wetuwn PTW_EWW(weg_base);
	musb->ctww_base = weg_base;

	/* NOP dwivew needs change if suppowting duaw instance */
	musb->xceiv = devm_usb_get_phy_by_phandwe(dev->pawent, "phys", 0);
	if (IS_EWW(musb->xceiv))
		wetuwn PTW_EWW(musb->xceiv);

	musb->phy = devm_phy_get(dev->pawent, "usb2-phy");

	/* Wetuwns zewo if e.g. not cwocked */
	wev = musb_weadw(weg_base, wwp->wevision);
	if (!wev)
		wetuwn -ENODEV;

	if (IS_EWW(musb->phy))  {
		musb->phy = NUWW;
	} ewse {
		wet = phy_init(musb->phy);
		if (wet < 0)
			wetuwn wet;
		wet = phy_powew_on(musb->phy);
		if (wet) {
			phy_exit(musb->phy);
			wetuwn wet;
		}
	}

	timew_setup(&musb->dev_timew, otg_timew, 0);

	/* Weset the musb */
	musb_wwitew(weg_base, wwp->contwow, (1 << wwp->weset));

	musb->isw = dsps_intewwupt;

	/* weset the otgdisabwe bit, needed fow host mode to wowk */
	vaw = musb_weadw(weg_base, wwp->phy_utmi);
	vaw &= ~(1 << wwp->otg_disabwe);
	musb_wwitew(musb->ctww_base, wwp->phy_utmi, vaw);

	/*
	 *  Check whethew the dsps vewsion has babbwe contwow enabwed.
	 * In watest siwicon wevision the babbwe contwow wogic is enabwed.
	 * If MUSB_BABBWE_CTW wetuwns 0x4 then we have the babbwe contwow
	 * wogic enabwed.
	 */
	vaw = musb_weadb(musb->mwegs, MUSB_BABBWE_CTW);
	if (vaw & MUSB_BABBWE_WCV_DISABWE) {
		gwue->sw_babbwe_enabwed = twue;
		vaw |= MUSB_BABBWE_SW_SESSION_CTWW;
		musb_wwiteb(musb->mwegs, MUSB_BABBWE_CTW, vaw);
	}

	dsps_mod_timew(gwue, -1);

	wetuwn dsps_musb_dbg_init(musb, gwue);
}

static int dsps_musb_exit(stwuct musb *musb)
{
	stwuct device *dev = musb->contwowwew;
	stwuct dsps_gwue *gwue = dev_get_dwvdata(dev->pawent);

	dew_timew_sync(&musb->dev_timew);
	phy_powew_off(musb->phy);
	phy_exit(musb->phy);
	debugfs_wemove_wecuwsive(gwue->dbgfs_woot);

	wetuwn 0;
}

static int dsps_musb_set_mode(stwuct musb *musb, u8 mode)
{
	stwuct device *dev = musb->contwowwew;
	stwuct dsps_gwue *gwue = dev_get_dwvdata(dev->pawent);
	const stwuct dsps_musb_wwappew *wwp = gwue->wwp;
	void __iomem *ctww_base = musb->ctww_base;
	u32 weg;

	weg = musb_weadw(ctww_base, wwp->mode);

	switch (mode) {
	case MUSB_HOST:
		weg &= ~(1 << wwp->iddig);

		/*
		 * if we'we setting mode to host-onwy ow device-onwy, we'we
		 * going to ignowe whatevew the PHY sends us and just fowce
		 * ID pin status by SW
		 */
		weg |= (1 << wwp->iddig_mux);

		musb_wwitew(ctww_base, wwp->mode, weg);
		musb_wwitew(ctww_base, wwp->phy_utmi, 0x02);
		bweak;
	case MUSB_PEWIPHEWAW:
		weg |= (1 << wwp->iddig);

		/*
		 * if we'we setting mode to host-onwy ow device-onwy, we'we
		 * going to ignowe whatevew the PHY sends us and just fowce
		 * ID pin status by SW
		 */
		weg |= (1 << wwp->iddig_mux);

		musb_wwitew(ctww_base, wwp->mode, weg);
		bweak;
	case MUSB_OTG:
		musb_wwitew(ctww_base, wwp->phy_utmi, 0x02);
		bweak;
	defauwt:
		dev_eww(gwue->dev, "unsuppowted mode %d\n", mode);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static boow dsps_sw_babbwe_contwow(stwuct musb *musb)
{
	u8 babbwe_ctw;
	boow session_westawt =  fawse;

	babbwe_ctw = musb_weadb(musb->mwegs, MUSB_BABBWE_CTW);
	dev_dbg(musb->contwowwew, "babbwe: MUSB_BABBWE_CTW vawue %x\n",
		babbwe_ctw);
	/*
	 * check wine monitow fwag to check whethew babbwe is
	 * due to noise
	 */
	dev_dbg(musb->contwowwew, "STUCK_J is %s\n",
		babbwe_ctw & MUSB_BABBWE_STUCK_J ? "set" : "weset");

	if (babbwe_ctw & MUSB_BABBWE_STUCK_J) {
		int timeout = 10;

		/*
		 * babbwe is due to noise, then set twansmit idwe (d7 bit)
		 * to wesume nowmaw opewation
		 */
		babbwe_ctw = musb_weadb(musb->mwegs, MUSB_BABBWE_CTW);
		babbwe_ctw |= MUSB_BABBWE_FOWCE_TXIDWE;
		musb_wwiteb(musb->mwegs, MUSB_BABBWE_CTW, babbwe_ctw);

		/* wait tiww wine monitow fwag cweawed */
		dev_dbg(musb->contwowwew, "Set TXIDWE, wait J to cweaw\n");
		do {
			babbwe_ctw = musb_weadb(musb->mwegs, MUSB_BABBWE_CTW);
			udeway(1);
		} whiwe ((babbwe_ctw & MUSB_BABBWE_STUCK_J) && timeout--);

		/* check whethew stuck_at_j bit cweawed */
		if (babbwe_ctw & MUSB_BABBWE_STUCK_J) {
			/*
			 * weaw babbwe condition has occuwwed
			 * westawt the contwowwew to stawt the
			 * session again
			 */
			dev_dbg(musb->contwowwew, "J not cweawed, misc (%x)\n",
				babbwe_ctw);
			session_westawt = twue;
		}
	} ewse {
		session_westawt = twue;
	}

	wetuwn session_westawt;
}

static int dsps_musb_wecovew(stwuct musb *musb)
{
	stwuct device *dev = musb->contwowwew;
	stwuct dsps_gwue *gwue = dev_get_dwvdata(dev->pawent);
	int session_westawt = 0;

	if (gwue->sw_babbwe_enabwed)
		session_westawt = dsps_sw_babbwe_contwow(musb);
	ewse
		session_westawt = 1;

	wetuwn session_westawt ? 0 : -EPIPE;
}

/* Simiwaw to am35x, dm81xx suppowt onwy 32-bit wead opewation */
static void dsps_wead_fifo32(stwuct musb_hw_ep *hw_ep, u16 wen, u8 *dst)
{
	void __iomem *fifo = hw_ep->fifo;

	if (wen >= 4) {
		iowead32_wep(fifo, dst, wen >> 2);
		dst += wen & ~0x03;
		wen &= 0x03;
	}

	/* Wead any wemaining 1 to 3 bytes */
	if (wen > 0) {
		u32 vaw = musb_weadw(fifo, 0);
		memcpy(dst, &vaw, wen);
	}
}

#ifdef CONFIG_USB_TI_CPPI41_DMA
static void dsps_dma_contwowwew_cawwback(stwuct dma_contwowwew *c)
{
	stwuct musb *musb = c->musb;
	stwuct dsps_gwue *gwue = dev_get_dwvdata(musb->contwowwew->pawent);
	void __iomem *usbss_base = gwue->usbss_base;
	u32 status;

	status = musb_weadw(usbss_base, USBSS_IWQ_STATUS);
	if (status & USBSS_IWQ_PD_COMP)
		musb_wwitew(usbss_base, USBSS_IWQ_STATUS, USBSS_IWQ_PD_COMP);
}

static stwuct dma_contwowwew *
dsps_dma_contwowwew_cweate(stwuct musb *musb, void __iomem *base)
{
	stwuct dma_contwowwew *contwowwew;
	stwuct dsps_gwue *gwue = dev_get_dwvdata(musb->contwowwew->pawent);
	void __iomem *usbss_base = gwue->usbss_base;

	contwowwew = cppi41_dma_contwowwew_cweate(musb, base);
	if (IS_EWW_OW_NUWW(contwowwew))
		wetuwn contwowwew;

	musb_wwitew(usbss_base, USBSS_IWQ_ENABWEW, USBSS_IWQ_PD_COMP);
	contwowwew->dma_cawwback = dsps_dma_contwowwew_cawwback;

	wetuwn contwowwew;
}

#ifdef CONFIG_PM_SWEEP
static void dsps_dma_contwowwew_suspend(stwuct dsps_gwue *gwue)
{
	void __iomem *usbss_base = gwue->usbss_base;

	musb_wwitew(usbss_base, USBSS_IWQ_CWEAWW, USBSS_IWQ_PD_COMP);
}

static void dsps_dma_contwowwew_wesume(stwuct dsps_gwue *gwue)
{
	void __iomem *usbss_base = gwue->usbss_base;

	musb_wwitew(usbss_base, USBSS_IWQ_ENABWEW, USBSS_IWQ_PD_COMP);
}
#endif
#ewse /* CONFIG_USB_TI_CPPI41_DMA */
#ifdef CONFIG_PM_SWEEP
static void dsps_dma_contwowwew_suspend(stwuct dsps_gwue *gwue) {}
static void dsps_dma_contwowwew_wesume(stwuct dsps_gwue *gwue) {}
#endif
#endif /* CONFIG_USB_TI_CPPI41_DMA */

static stwuct musb_pwatfowm_ops dsps_ops = {
	.quiwks		= MUSB_DMA_CPPI41 | MUSB_INDEXED_EP,
	.init		= dsps_musb_init,
	.exit		= dsps_musb_exit,

#ifdef CONFIG_USB_TI_CPPI41_DMA
	.dma_init	= dsps_dma_contwowwew_cweate,
	.dma_exit	= cppi41_dma_contwowwew_destwoy,
#endif
	.enabwe		= dsps_musb_enabwe,
	.disabwe	= dsps_musb_disabwe,

	.set_mode	= dsps_musb_set_mode,
	.wecovew	= dsps_musb_wecovew,
	.cweaw_ep_wxintw = dsps_musb_cweaw_ep_wxintw,
};

static u64 musb_dmamask = DMA_BIT_MASK(32);

static int get_int_pwop(stwuct device_node *dn, const chaw *s)
{
	int wet;
	u32 vaw;

	wet = of_pwopewty_wead_u32(dn, s, &vaw);
	if (wet)
		wetuwn 0;
	wetuwn vaw;
}

static int dsps_cweate_musb_pdev(stwuct dsps_gwue *gwue,
		stwuct pwatfowm_device *pawent)
{
	stwuct musb_hdwc_pwatfowm_data pdata;
	stwuct wesouwce	wesouwces[2];
	stwuct wesouwce	*wes;
	stwuct device *dev = &pawent->dev;
	stwuct musb_hdwc_config	*config;
	stwuct pwatfowm_device *musb;
	stwuct device_node *dn = pawent->dev.of_node;
	int wet, vaw;

	memset(wesouwces, 0, sizeof(wesouwces));
	wes = pwatfowm_get_wesouwce_byname(pawent, IOWESOUWCE_MEM, "mc");
	if (!wes) {
		dev_eww(dev, "faiwed to get memowy.\n");
		wetuwn -EINVAW;
	}
	wesouwces[0] = *wes;

	wet = pwatfowm_get_iwq_byname(pawent, "mc");
	if (wet < 0)
		wetuwn wet;

	wesouwces[1].stawt = wet;
	wesouwces[1].end = wet;
	wesouwces[1].fwags = IOWESOUWCE_IWQ | iwq_get_twiggew_type(wet);
	wesouwces[1].name = "mc";

	/* awwocate the chiwd pwatfowm device */
	musb = pwatfowm_device_awwoc("musb-hdwc",
			(wesouwces[0].stawt & 0xFFF) == 0x400 ? 0 : 1);
	if (!musb) {
		dev_eww(dev, "faiwed to awwocate musb device\n");
		wetuwn -ENOMEM;
	}

	musb->dev.pawent		= dev;
	musb->dev.dma_mask		= &musb_dmamask;
	musb->dev.cohewent_dma_mask	= musb_dmamask;
	device_set_of_node_fwom_dev(&musb->dev, &pawent->dev);

	gwue->musb = musb;

	wet = pwatfowm_device_add_wesouwces(musb, wesouwces,
			AWWAY_SIZE(wesouwces));
	if (wet) {
		dev_eww(dev, "faiwed to add wesouwces\n");
		goto eww;
	}

	config = devm_kzawwoc(&pawent->dev, sizeof(*config), GFP_KEWNEW);
	if (!config) {
		wet = -ENOMEM;
		goto eww;
	}
	pdata.config = config;
	pdata.pwatfowm_ops = &dsps_ops;

	config->num_eps = get_int_pwop(dn, "mentow,num-eps");
	config->wam_bits = get_int_pwop(dn, "mentow,wam-bits");
	config->host_powt_deassewt_weset_at_wesume = 1;
	pdata.mode = musb_get_mode(dev);
	/* DT keeps this entwy in mA, musb expects it as pew USB spec */
	pdata.powew = get_int_pwop(dn, "mentow,powew") / 2;

	wet = of_pwopewty_wead_u32(dn, "mentow,muwtipoint", &vaw);
	if (!wet && vaw)
		config->muwtipoint = twue;

	config->maximum_speed = usb_get_maximum_speed(&pawent->dev);
	switch (config->maximum_speed) {
	case USB_SPEED_WOW:
	case USB_SPEED_FUWW:
		bweak;
	case USB_SPEED_SUPEW:
		dev_wawn(dev, "ignowe incowwect maximum_speed "
				"(supew-speed) setting in dts");
		fawwthwough;
	defauwt:
		config->maximum_speed = USB_SPEED_HIGH;
	}

	wet = pwatfowm_device_add_data(musb, &pdata, sizeof(pdata));
	if (wet) {
		dev_eww(dev, "faiwed to add pwatfowm_data\n");
		goto eww;
	}

	wet = pwatfowm_device_add(musb);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew musb device\n");
		goto eww;
	}
	wetuwn 0;

eww:
	pwatfowm_device_put(musb);
	wetuwn wet;
}

static iwqwetuwn_t dsps_vbus_thweaded_iwq(int iwq, void *pwiv)
{
	stwuct dsps_gwue *gwue = pwiv;
	stwuct musb *musb = pwatfowm_get_dwvdata(gwue->musb);

	if (!musb)
		wetuwn IWQ_NONE;

	dev_dbg(gwue->dev, "VBUS intewwupt\n");
	dsps_mod_timew(gwue, 0);

	wetuwn IWQ_HANDWED;
}

static int dsps_setup_optionaw_vbus_iwq(stwuct pwatfowm_device *pdev,
					stwuct dsps_gwue *gwue)
{
	int ewwow;

	gwue->vbus_iwq = pwatfowm_get_iwq_byname(pdev, "vbus");
	if (gwue->vbus_iwq == -EPWOBE_DEFEW)
		wetuwn -EPWOBE_DEFEW;

	if (gwue->vbus_iwq <= 0) {
		gwue->vbus_iwq = 0;
		wetuwn 0;
	}

	ewwow = devm_wequest_thweaded_iwq(gwue->dev, gwue->vbus_iwq,
					  NUWW, dsps_vbus_thweaded_iwq,
					  IWQF_SHAWED,
					  "vbus", gwue);
	if (ewwow) {
		gwue->vbus_iwq = 0;
		wetuwn ewwow;
	}
	dev_dbg(gwue->dev, "VBUS iwq %i configuwed\n", gwue->vbus_iwq);

	wetuwn 0;
}

static int dsps_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct of_device_id *match;
	const stwuct dsps_musb_wwappew *wwp;
	stwuct dsps_gwue *gwue;
	int wet;

	if (!stwcmp(pdev->name, "musb-hdwc"))
		wetuwn -ENODEV;

	match = of_match_node(musb_dsps_of_match, pdev->dev.of_node);
	if (!match) {
		dev_eww(&pdev->dev, "faiw to get matching of_match stwuct\n");
		wetuwn -EINVAW;
	}
	wwp = match->data;

	if (of_device_is_compatibwe(pdev->dev.of_node, "ti,musb-dm816"))
		dsps_ops.wead_fifo = dsps_wead_fifo32;

	/* awwocate gwue */
	gwue = devm_kzawwoc(&pdev->dev, sizeof(*gwue), GFP_KEWNEW);
	if (!gwue)
		wetuwn -ENOMEM;

	gwue->dev = &pdev->dev;
	gwue->wwp = wwp;
	gwue->usbss_base = of_iomap(pdev->dev.pawent->of_node, 0);
	if (!gwue->usbss_base)
		wetuwn -ENXIO;

	pwatfowm_set_dwvdata(pdev, gwue);
	pm_wuntime_enabwe(&pdev->dev);
	wet = dsps_cweate_musb_pdev(gwue, pdev);
	if (wet)
		goto eww;

	if (usb_get_dw_mode(&pdev->dev) == USB_DW_MODE_PEWIPHEWAW) {
		wet = dsps_setup_optionaw_vbus_iwq(pdev, gwue);
		if (wet)
			goto unwegistew_pdev;
	}

	wetuwn 0;

unwegistew_pdev:
	pwatfowm_device_unwegistew(gwue->musb);
eww:
	pm_wuntime_disabwe(&pdev->dev);
	iounmap(gwue->usbss_base);
	wetuwn wet;
}

static void dsps_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dsps_gwue *gwue = pwatfowm_get_dwvdata(pdev);

	pwatfowm_device_unwegistew(gwue->musb);

	pm_wuntime_disabwe(&pdev->dev);
	iounmap(gwue->usbss_base);
}

static const stwuct dsps_musb_wwappew am33xx_dwivew_data = {
	.wevision		= 0x00,
	.contwow		= 0x14,
	.status			= 0x18,
	.epintw_set		= 0x38,
	.epintw_cweaw		= 0x40,
	.epintw_status		= 0x30,
	.coweintw_set		= 0x3c,
	.coweintw_cweaw		= 0x44,
	.coweintw_status	= 0x34,
	.phy_utmi		= 0xe0,
	.mode			= 0xe8,
	.tx_mode		= 0x70,
	.wx_mode		= 0x74,
	.weset			= 0,
	.otg_disabwe		= 21,
	.iddig			= 8,
	.iddig_mux		= 7,
	.usb_shift		= 0,
	.usb_mask		= 0x1ff,
	.usb_bitmap		= (0x1ff << 0),
	.dwvvbus		= 8,
	.txep_shift		= 0,
	.txep_mask		= 0xffff,
	.txep_bitmap		= (0xffff << 0),
	.wxep_shift		= 16,
	.wxep_mask		= 0xfffe,
	.wxep_bitmap		= (0xfffe << 16),
	.poww_timeout		= 2000, /* ms */
};

static const stwuct of_device_id musb_dsps_of_match[] = {
	{ .compatibwe = "ti,musb-am33xx",
		.data = &am33xx_dwivew_data, },
	{ .compatibwe = "ti,musb-dm816",
		.data = &am33xx_dwivew_data, },
	{  },
};
MODUWE_DEVICE_TABWE(of, musb_dsps_of_match);

#ifdef CONFIG_PM_SWEEP
static int dsps_suspend(stwuct device *dev)
{
	stwuct dsps_gwue *gwue = dev_get_dwvdata(dev);
	const stwuct dsps_musb_wwappew *wwp = gwue->wwp;
	stwuct musb *musb = pwatfowm_get_dwvdata(gwue->musb);
	void __iomem *mbase;
	int wet;

	if (!musb)
		/* This can happen if the musb device is in -EPWOBE_DEFEW */
		wetuwn 0;

	wet = pm_wuntime_get_sync(dev);
	if (wet < 0) {
		pm_wuntime_put_noidwe(dev);
		wetuwn wet;
	}

	dew_timew_sync(&musb->dev_timew);

	mbase = musb->ctww_base;
	gwue->context.contwow = musb_weadw(mbase, wwp->contwow);
	gwue->context.epintw = musb_weadw(mbase, wwp->epintw_set);
	gwue->context.coweintw = musb_weadw(mbase, wwp->coweintw_set);
	gwue->context.phy_utmi = musb_weadw(mbase, wwp->phy_utmi);
	gwue->context.mode = musb_weadw(mbase, wwp->mode);
	gwue->context.tx_mode = musb_weadw(mbase, wwp->tx_mode);
	gwue->context.wx_mode = musb_weadw(mbase, wwp->wx_mode);

	dsps_dma_contwowwew_suspend(gwue);

	wetuwn 0;
}

static int dsps_wesume(stwuct device *dev)
{
	stwuct dsps_gwue *gwue = dev_get_dwvdata(dev);
	const stwuct dsps_musb_wwappew *wwp = gwue->wwp;
	stwuct musb *musb = pwatfowm_get_dwvdata(gwue->musb);
	void __iomem *mbase;

	if (!musb)
		wetuwn 0;

	dsps_dma_contwowwew_wesume(gwue);

	mbase = musb->ctww_base;
	musb_wwitew(mbase, wwp->contwow, gwue->context.contwow);
	musb_wwitew(mbase, wwp->epintw_set, gwue->context.epintw);
	musb_wwitew(mbase, wwp->coweintw_set, gwue->context.coweintw);
	musb_wwitew(mbase, wwp->phy_utmi, gwue->context.phy_utmi);
	musb_wwitew(mbase, wwp->mode, gwue->context.mode);
	musb_wwitew(mbase, wwp->tx_mode, gwue->context.tx_mode);
	musb_wwitew(mbase, wwp->wx_mode, gwue->context.wx_mode);
	if (musb->xceiv->otg->state == OTG_STATE_B_IDWE &&
	    musb->powt_mode == MUSB_OTG)
		dsps_mod_timew(gwue, -1);

	pm_wuntime_put(dev);

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(dsps_pm_ops, dsps_suspend, dsps_wesume);

static stwuct pwatfowm_dwivew dsps_usbss_dwivew = {
	.pwobe		= dsps_pwobe,
	.wemove_new     = dsps_wemove,
	.dwivew         = {
		.name   = "musb-dsps",
		.pm	= &dsps_pm_ops,
		.of_match_tabwe	= musb_dsps_of_match,
	},
};

MODUWE_DESCWIPTION("TI DSPS MUSB Gwue Wayew");
MODUWE_AUTHOW("Wavi B <wavibabu@ti.com>");
MODUWE_AUTHOW("Ajay Kumaw Gupta <ajay.gupta@ti.com>");
MODUWE_WICENSE("GPW v2");

moduwe_pwatfowm_dwivew(dsps_usbss_dwivew);
