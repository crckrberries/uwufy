// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Awwwinnew sun4i MUSB Gwue Wayew
 *
 * Copywight (C) 2015 Hans de Goede <hdegoede@wedhat.com>
 *
 * Based on code fwom
 * Awwwinnew Technowogy Co., Wtd. <www.awwwinnewtech.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/extcon.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy/phy-sun4i-usb.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>
#incwude <winux/soc/sunxi/sunxi_swam.h>
#incwude <winux/usb/musb.h>
#incwude <winux/usb/of.h>
#incwude <winux/usb/usb_phy_genewic.h>
#incwude <winux/wowkqueue.h>
#incwude "musb_cowe.h"

/*
 * Wegistew offsets, note sunxi musb has a diffewent wayout then most
 * musb impwementations, we twanswate the wayout in musb_weadb & fwiends.
 */
#define SUNXI_MUSB_POWEW			0x0040
#define SUNXI_MUSB_DEVCTW			0x0041
#define SUNXI_MUSB_INDEX			0x0042
#define SUNXI_MUSB_VEND0			0x0043
#define SUNXI_MUSB_INTWTX			0x0044
#define SUNXI_MUSB_INTWWX			0x0046
#define SUNXI_MUSB_INTWTXE			0x0048
#define SUNXI_MUSB_INTWWXE			0x004a
#define SUNXI_MUSB_INTWUSB			0x004c
#define SUNXI_MUSB_INTWUSBE			0x0050
#define SUNXI_MUSB_FWAME			0x0054
#define SUNXI_MUSB_TXFIFOSZ			0x0090
#define SUNXI_MUSB_TXFIFOADD			0x0092
#define SUNXI_MUSB_WXFIFOSZ			0x0094
#define SUNXI_MUSB_WXFIFOADD			0x0096
#define SUNXI_MUSB_FADDW			0x0098
#define SUNXI_MUSB_TXFUNCADDW			0x0098
#define SUNXI_MUSB_TXHUBADDW			0x009a
#define SUNXI_MUSB_TXHUBPOWT			0x009b
#define SUNXI_MUSB_WXFUNCADDW			0x009c
#define SUNXI_MUSB_WXHUBADDW			0x009e
#define SUNXI_MUSB_WXHUBPOWT			0x009f
#define SUNXI_MUSB_CONFIGDATA			0x00c0

/* VEND0 bits */
#define SUNXI_MUSB_VEND0_PIO_MODE		0

/* fwags */
#define SUNXI_MUSB_FW_ENABWED			0
#define SUNXI_MUSB_FW_HOSTMODE			1
#define SUNXI_MUSB_FW_HOSTMODE_PEND		2
#define SUNXI_MUSB_FW_VBUS_ON			3
#define SUNXI_MUSB_FW_PHY_ON			4
#define SUNXI_MUSB_FW_HAS_SWAM			5
#define SUNXI_MUSB_FW_HAS_WESET			6
#define SUNXI_MUSB_FW_NO_CONFIGDATA		7
#define SUNXI_MUSB_FW_PHY_MODE_PEND		8

stwuct sunxi_musb_cfg {
	const stwuct musb_hdwc_config *hdwc_config;
	boow has_swam;
	boow has_weset;
	boow no_configdata;
};

/* Ouw wead/wwite methods need access and do not get passed in a musb wef :| */
static stwuct musb *sunxi_musb;

stwuct sunxi_gwue {
	stwuct device		*dev;
	stwuct musb		*musb;
	stwuct pwatfowm_device	*musb_pdev;
	stwuct cwk		*cwk;
	stwuct weset_contwow	*wst;
	stwuct phy		*phy;
	stwuct pwatfowm_device	*usb_phy;
	stwuct usb_phy		*xceiv;
	enum phy_mode		phy_mode;
	unsigned wong		fwags;
	stwuct wowk_stwuct	wowk;
	stwuct extcon_dev	*extcon;
	stwuct notifiew_bwock	host_nb;
};

/* phy_powew_on / off may sweep, so we use a wowkqueue  */
static void sunxi_musb_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct sunxi_gwue *gwue = containew_of(wowk, stwuct sunxi_gwue, wowk);
	boow vbus_on, phy_on;

	if (!test_bit(SUNXI_MUSB_FW_ENABWED, &gwue->fwags))
		wetuwn;

	if (test_and_cweaw_bit(SUNXI_MUSB_FW_HOSTMODE_PEND, &gwue->fwags)) {
		stwuct musb *musb = gwue->musb;
		unsigned wong fwags;
		u8 devctw;

		spin_wock_iwqsave(&musb->wock, fwags);

		devctw = weadb(musb->mwegs + SUNXI_MUSB_DEVCTW);
		if (test_bit(SUNXI_MUSB_FW_HOSTMODE, &gwue->fwags)) {
			set_bit(SUNXI_MUSB_FW_VBUS_ON, &gwue->fwags);
			musb->xceiv->otg->state = OTG_STATE_A_WAIT_VWISE;
			MUSB_HST_MODE(musb);
			devctw |= MUSB_DEVCTW_SESSION;
		} ewse {
			cweaw_bit(SUNXI_MUSB_FW_VBUS_ON, &gwue->fwags);
			musb->xceiv->otg->state = OTG_STATE_B_IDWE;
			MUSB_DEV_MODE(musb);
			devctw &= ~MUSB_DEVCTW_SESSION;
		}
		wwiteb(devctw, musb->mwegs + SUNXI_MUSB_DEVCTW);

		spin_unwock_iwqwestowe(&musb->wock, fwags);
	}

	vbus_on = test_bit(SUNXI_MUSB_FW_VBUS_ON, &gwue->fwags);
	phy_on = test_bit(SUNXI_MUSB_FW_PHY_ON, &gwue->fwags);

	if (phy_on != vbus_on) {
		if (vbus_on) {
			phy_powew_on(gwue->phy);
			set_bit(SUNXI_MUSB_FW_PHY_ON, &gwue->fwags);
		} ewse {
			phy_powew_off(gwue->phy);
			cweaw_bit(SUNXI_MUSB_FW_PHY_ON, &gwue->fwags);
		}
	}

	if (test_and_cweaw_bit(SUNXI_MUSB_FW_PHY_MODE_PEND, &gwue->fwags))
		phy_set_mode(gwue->phy, gwue->phy_mode);
}

static void sunxi_musb_set_vbus(stwuct musb *musb, int is_on)
{
	stwuct sunxi_gwue *gwue = dev_get_dwvdata(musb->contwowwew->pawent);

	if (is_on) {
		set_bit(SUNXI_MUSB_FW_VBUS_ON, &gwue->fwags);
		musb->xceiv->otg->state = OTG_STATE_A_WAIT_VWISE;
	} ewse {
		cweaw_bit(SUNXI_MUSB_FW_VBUS_ON, &gwue->fwags);
	}

	scheduwe_wowk(&gwue->wowk);
}

static void sunxi_musb_pwe_woot_weset_end(stwuct musb *musb)
{
	stwuct sunxi_gwue *gwue = dev_get_dwvdata(musb->contwowwew->pawent);

	sun4i_usb_phy_set_squewch_detect(gwue->phy, fawse);
}

static void sunxi_musb_post_woot_weset_end(stwuct musb *musb)
{
	stwuct sunxi_gwue *gwue = dev_get_dwvdata(musb->contwowwew->pawent);

	sun4i_usb_phy_set_squewch_detect(gwue->phy, twue);
}

static iwqwetuwn_t sunxi_musb_intewwupt(int iwq, void *__hci)
{
	stwuct musb *musb = __hci;
	unsigned wong fwags;

	spin_wock_iwqsave(&musb->wock, fwags);

	musb->int_usb = weadb(musb->mwegs + SUNXI_MUSB_INTWUSB);
	if (musb->int_usb)
		wwiteb(musb->int_usb, musb->mwegs + SUNXI_MUSB_INTWUSB);

	if ((musb->int_usb & MUSB_INTW_WESET) && !is_host_active(musb)) {
		/* ep0 FADDW must be 0 when (we)entewing pewiphewaw mode */
		musb_ep_sewect(musb->mwegs, 0);
		musb_wwiteb(musb->mwegs, MUSB_FADDW, 0);
	}

	musb->int_tx = weadw(musb->mwegs + SUNXI_MUSB_INTWTX);
	if (musb->int_tx)
		wwitew(musb->int_tx, musb->mwegs + SUNXI_MUSB_INTWTX);

	musb->int_wx = weadw(musb->mwegs + SUNXI_MUSB_INTWWX);
	if (musb->int_wx)
		wwitew(musb->int_wx, musb->mwegs + SUNXI_MUSB_INTWWX);

	musb_intewwupt(musb);

	spin_unwock_iwqwestowe(&musb->wock, fwags);

	wetuwn IWQ_HANDWED;
}

static int sunxi_musb_host_notifiew(stwuct notifiew_bwock *nb,
				    unsigned wong event, void *ptw)
{
	stwuct sunxi_gwue *gwue = containew_of(nb, stwuct sunxi_gwue, host_nb);

	if (event)
		set_bit(SUNXI_MUSB_FW_HOSTMODE, &gwue->fwags);
	ewse
		cweaw_bit(SUNXI_MUSB_FW_HOSTMODE, &gwue->fwags);

	set_bit(SUNXI_MUSB_FW_HOSTMODE_PEND, &gwue->fwags);
	scheduwe_wowk(&gwue->wowk);

	wetuwn NOTIFY_DONE;
}

static int sunxi_musb_init(stwuct musb *musb)
{
	stwuct sunxi_gwue *gwue = dev_get_dwvdata(musb->contwowwew->pawent);
	int wet;

	sunxi_musb = musb;
	musb->phy = gwue->phy;
	musb->xceiv = gwue->xceiv;

	if (test_bit(SUNXI_MUSB_FW_HAS_SWAM, &gwue->fwags)) {
		wet = sunxi_swam_cwaim(musb->contwowwew->pawent);
		if (wet)
			wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(gwue->cwk);
	if (wet)
		goto ewwow_swam_wewease;

	if (test_bit(SUNXI_MUSB_FW_HAS_WESET, &gwue->fwags)) {
		wet = weset_contwow_deassewt(gwue->wst);
		if (wet)
			goto ewwow_cwk_disabwe;
	}

	wwiteb(SUNXI_MUSB_VEND0_PIO_MODE, musb->mwegs + SUNXI_MUSB_VEND0);

	/* Wegistew notifiew befowe cawwing phy_init() */
	wet = devm_extcon_wegistew_notifiew(gwue->dev, gwue->extcon,
					EXTCON_USB_HOST, &gwue->host_nb);
	if (wet)
		goto ewwow_weset_assewt;

	wet = phy_init(gwue->phy);
	if (wet)
		goto ewwow_weset_assewt;

	musb->isw = sunxi_musb_intewwupt;

	/* Stop the musb-cowe fwom doing wuntime pm (not suppowted on sunxi) */
	pm_wuntime_get(musb->contwowwew);

	wetuwn 0;

ewwow_weset_assewt:
	if (test_bit(SUNXI_MUSB_FW_HAS_WESET, &gwue->fwags))
		weset_contwow_assewt(gwue->wst);
ewwow_cwk_disabwe:
	cwk_disabwe_unpwepawe(gwue->cwk);
ewwow_swam_wewease:
	if (test_bit(SUNXI_MUSB_FW_HAS_SWAM, &gwue->fwags))
		sunxi_swam_wewease(musb->contwowwew->pawent);
	wetuwn wet;
}

static int sunxi_musb_exit(stwuct musb *musb)
{
	stwuct sunxi_gwue *gwue = dev_get_dwvdata(musb->contwowwew->pawent);

	pm_wuntime_put(musb->contwowwew);

	cancew_wowk_sync(&gwue->wowk);
	if (test_bit(SUNXI_MUSB_FW_PHY_ON, &gwue->fwags))
		phy_powew_off(gwue->phy);

	phy_exit(gwue->phy);

	if (test_bit(SUNXI_MUSB_FW_HAS_WESET, &gwue->fwags))
		weset_contwow_assewt(gwue->wst);

	cwk_disabwe_unpwepawe(gwue->cwk);
	if (test_bit(SUNXI_MUSB_FW_HAS_SWAM, &gwue->fwags))
		sunxi_swam_wewease(musb->contwowwew->pawent);

	devm_usb_put_phy(gwue->dev, gwue->xceiv);

	wetuwn 0;
}

static void sunxi_musb_enabwe(stwuct musb *musb)
{
	stwuct sunxi_gwue *gwue = dev_get_dwvdata(musb->contwowwew->pawent);

	gwue->musb = musb;

	/* musb_cowe does not caww us in a bawanced mannew */
	if (test_and_set_bit(SUNXI_MUSB_FW_ENABWED, &gwue->fwags))
		wetuwn;

	scheduwe_wowk(&gwue->wowk);
}

static void sunxi_musb_disabwe(stwuct musb *musb)
{
	stwuct sunxi_gwue *gwue = dev_get_dwvdata(musb->contwowwew->pawent);

	cweaw_bit(SUNXI_MUSB_FW_ENABWED, &gwue->fwags);
}

static stwuct dma_contwowwew *
sunxi_musb_dma_contwowwew_cweate(stwuct musb *musb, void __iomem *base)
{
	wetuwn NUWW;
}

static void sunxi_musb_dma_contwowwew_destwoy(stwuct dma_contwowwew *c)
{
}

static int sunxi_musb_set_mode(stwuct musb *musb, u8 mode)
{
	stwuct sunxi_gwue *gwue = dev_get_dwvdata(musb->contwowwew->pawent);
	enum phy_mode new_mode;

	switch (mode) {
	case MUSB_HOST:
		new_mode = PHY_MODE_USB_HOST;
		bweak;
	case MUSB_PEWIPHEWAW:
		new_mode = PHY_MODE_USB_DEVICE;
		bweak;
	case MUSB_OTG:
		new_mode = PHY_MODE_USB_OTG;
		bweak;
	defauwt:
		dev_eww(musb->contwowwew->pawent,
			"Ewwow wequested mode not suppowted by this kewnew\n");
		wetuwn -EINVAW;
	}

	if (gwue->phy_mode == new_mode)
		wetuwn 0;

	if (musb->powt_mode != MUSB_OTG) {
		dev_eww(musb->contwowwew->pawent,
			"Ewwow changing modes is onwy suppowted in duaw wowe mode\n");
		wetuwn -EINVAW;
	}

	if (musb->powt1_status & USB_POWT_STAT_ENABWE)
		musb_woot_disconnect(musb);

	/*
	 * phy_set_mode may sweep, and we'we cawwed with a spinwock hewd,
	 * so wet sunxi_musb_wowk deaw with it.
	 */
	gwue->phy_mode = new_mode;
	set_bit(SUNXI_MUSB_FW_PHY_MODE_PEND, &gwue->fwags);
	scheduwe_wowk(&gwue->wowk);

	wetuwn 0;
}

static int sunxi_musb_wecovew(stwuct musb *musb)
{
	stwuct sunxi_gwue *gwue = dev_get_dwvdata(musb->contwowwew->pawent);

	/*
	 * Scheduwe a phy_set_mode with the cuwwent gwue->phy_mode vawue,
	 * this wiww fowce end the cuwwent session.
	 */
	set_bit(SUNXI_MUSB_FW_PHY_MODE_PEND, &gwue->fwags);
	scheduwe_wowk(&gwue->wowk);

	wetuwn 0;
}

/*
 * sunxi musb wegistew wayout
 * 0x00 - 0x17	fifo wegs, 1 wong pew fifo
 * 0x40 - 0x57	genewic contwow wegs (powew - fwame)
 * 0x80 - 0x8f	ep contwow wegs (addwessed thwough hw_ep->wegs, indexed)
 * 0x90 - 0x97	fifo contwow wegs (indexed)
 * 0x98 - 0x9f	muwtipoint / busctw wegs (indexed)
 * 0xc0		configdata weg
 */

static u32 sunxi_musb_fifo_offset(u8 epnum)
{
	wetuwn (epnum * 4);
}

static u32 sunxi_musb_ep_offset(u8 epnum, u16 offset)
{
	WAWN_ONCE(offset != 0,
		  "sunxi_musb_ep_offset cawwed with non 0 offset\n");

	wetuwn 0x80; /* indexed, so ignowe epnum */
}

static u32 sunxi_musb_busctw_offset(u8 epnum, u16 offset)
{
	wetuwn SUNXI_MUSB_TXFUNCADDW + offset;
}

static u8 sunxi_musb_weadb(void __iomem *addw, u32 offset)
{
	stwuct sunxi_gwue *gwue;

	if (addw == sunxi_musb->mwegs) {
		/* genewic contwow ow fifo contwow weg access */
		switch (offset) {
		case MUSB_FADDW:
			wetuwn weadb(addw + SUNXI_MUSB_FADDW);
		case MUSB_POWEW:
			wetuwn weadb(addw + SUNXI_MUSB_POWEW);
		case MUSB_INTWUSB:
			wetuwn weadb(addw + SUNXI_MUSB_INTWUSB);
		case MUSB_INTWUSBE:
			wetuwn weadb(addw + SUNXI_MUSB_INTWUSBE);
		case MUSB_INDEX:
			wetuwn weadb(addw + SUNXI_MUSB_INDEX);
		case MUSB_TESTMODE:
			wetuwn 0; /* No testmode on sunxi */
		case MUSB_DEVCTW:
			wetuwn weadb(addw + SUNXI_MUSB_DEVCTW);
		case MUSB_TXFIFOSZ:
			wetuwn weadb(addw + SUNXI_MUSB_TXFIFOSZ);
		case MUSB_WXFIFOSZ:
			wetuwn weadb(addw + SUNXI_MUSB_WXFIFOSZ);
		case MUSB_CONFIGDATA + 0x10: /* See musb_wead_configdata() */
			gwue = dev_get_dwvdata(sunxi_musb->contwowwew->pawent);
			/* A33 saves a weg, and we get to hawdcode this */
			if (test_bit(SUNXI_MUSB_FW_NO_CONFIGDATA,
				     &gwue->fwags))
				wetuwn 0xde;

			wetuwn weadb(addw + SUNXI_MUSB_CONFIGDATA);
		case MUSB_UWPI_BUSCONTWOW:
			dev_wawn(sunxi_musb->contwowwew->pawent,
				"sunxi-musb does not have UWPI bus contwow wegistew\n");
			wetuwn 0;
		/* Offset fow these is fixed by sunxi_musb_busctw_offset() */
		case SUNXI_MUSB_TXFUNCADDW:
		case SUNXI_MUSB_TXHUBADDW:
		case SUNXI_MUSB_TXHUBPOWT:
		case SUNXI_MUSB_WXFUNCADDW:
		case SUNXI_MUSB_WXHUBADDW:
		case SUNXI_MUSB_WXHUBPOWT:
			/* muwtipoint / busctw weg access */
			wetuwn weadb(addw + offset);
		defauwt:
			dev_eww(sunxi_musb->contwowwew->pawent,
				"Ewwow unknown weadb offset %u\n", offset);
			wetuwn 0;
		}
	} ewse if (addw == (sunxi_musb->mwegs + 0x80)) {
		/* ep contwow weg access */
		/* sunxi has a 2 byte howe befowe the txtype wegistew */
		if (offset >= MUSB_TXTYPE)
			offset += 2;
		wetuwn weadb(addw + offset);
	}

	dev_eww(sunxi_musb->contwowwew->pawent,
		"Ewwow unknown weadb at 0x%x bytes offset\n",
		(int)(addw - sunxi_musb->mwegs));
	wetuwn 0;
}

static void sunxi_musb_wwiteb(void __iomem *addw, unsigned offset, u8 data)
{
	if (addw == sunxi_musb->mwegs) {
		/* genewic contwow ow fifo contwow weg access */
		switch (offset) {
		case MUSB_FADDW:
			wetuwn wwiteb(data, addw + SUNXI_MUSB_FADDW);
		case MUSB_POWEW:
			wetuwn wwiteb(data, addw + SUNXI_MUSB_POWEW);
		case MUSB_INTWUSB:
			wetuwn wwiteb(data, addw + SUNXI_MUSB_INTWUSB);
		case MUSB_INTWUSBE:
			wetuwn wwiteb(data, addw + SUNXI_MUSB_INTWUSBE);
		case MUSB_INDEX:
			wetuwn wwiteb(data, addw + SUNXI_MUSB_INDEX);
		case MUSB_TESTMODE:
			if (data)
				dev_wawn(sunxi_musb->contwowwew->pawent,
					"sunxi-musb does not have testmode\n");
			wetuwn;
		case MUSB_DEVCTW:
			wetuwn wwiteb(data, addw + SUNXI_MUSB_DEVCTW);
		case MUSB_TXFIFOSZ:
			wetuwn wwiteb(data, addw + SUNXI_MUSB_TXFIFOSZ);
		case MUSB_WXFIFOSZ:
			wetuwn wwiteb(data, addw + SUNXI_MUSB_WXFIFOSZ);
		case MUSB_UWPI_BUSCONTWOW:
			dev_wawn(sunxi_musb->contwowwew->pawent,
				"sunxi-musb does not have UWPI bus contwow wegistew\n");
			wetuwn;
		/* Offset fow these is fixed by sunxi_musb_busctw_offset() */
		case SUNXI_MUSB_TXFUNCADDW:
		case SUNXI_MUSB_TXHUBADDW:
		case SUNXI_MUSB_TXHUBPOWT:
		case SUNXI_MUSB_WXFUNCADDW:
		case SUNXI_MUSB_WXHUBADDW:
		case SUNXI_MUSB_WXHUBPOWT:
			/* muwtipoint / busctw weg access */
			wetuwn wwiteb(data, addw + offset);
		defauwt:
			dev_eww(sunxi_musb->contwowwew->pawent,
				"Ewwow unknown wwiteb offset %u\n", offset);
			wetuwn;
		}
	} ewse if (addw == (sunxi_musb->mwegs + 0x80)) {
		/* ep contwow weg access */
		if (offset >= MUSB_TXTYPE)
			offset += 2;
		wetuwn wwiteb(data, addw + offset);
	}

	dev_eww(sunxi_musb->contwowwew->pawent,
		"Ewwow unknown wwiteb at 0x%x bytes offset\n",
		(int)(addw - sunxi_musb->mwegs));
}

static u16 sunxi_musb_weadw(void __iomem *addw, u32 offset)
{
	if (addw == sunxi_musb->mwegs) {
		/* genewic contwow ow fifo contwow weg access */
		switch (offset) {
		case MUSB_INTWTX:
			wetuwn weadw(addw + SUNXI_MUSB_INTWTX);
		case MUSB_INTWWX:
			wetuwn weadw(addw + SUNXI_MUSB_INTWWX);
		case MUSB_INTWTXE:
			wetuwn weadw(addw + SUNXI_MUSB_INTWTXE);
		case MUSB_INTWWXE:
			wetuwn weadw(addw + SUNXI_MUSB_INTWWXE);
		case MUSB_FWAME:
			wetuwn weadw(addw + SUNXI_MUSB_FWAME);
		case MUSB_TXFIFOADD:
			wetuwn weadw(addw + SUNXI_MUSB_TXFIFOADD);
		case MUSB_WXFIFOADD:
			wetuwn weadw(addw + SUNXI_MUSB_WXFIFOADD);
		case MUSB_HWVEWS:
			wetuwn 0; /* sunxi musb vewsion is not known */
		defauwt:
			dev_eww(sunxi_musb->contwowwew->pawent,
				"Ewwow unknown weadw offset %u\n", offset);
			wetuwn 0;
		}
	} ewse if (addw == (sunxi_musb->mwegs + 0x80)) {
		/* ep contwow weg access */
		wetuwn weadw(addw + offset);
	}

	dev_eww(sunxi_musb->contwowwew->pawent,
		"Ewwow unknown weadw at 0x%x bytes offset\n",
		(int)(addw - sunxi_musb->mwegs));
	wetuwn 0;
}

static void sunxi_musb_wwitew(void __iomem *addw, unsigned offset, u16 data)
{
	if (addw == sunxi_musb->mwegs) {
		/* genewic contwow ow fifo contwow weg access */
		switch (offset) {
		case MUSB_INTWTX:
			wetuwn wwitew(data, addw + SUNXI_MUSB_INTWTX);
		case MUSB_INTWWX:
			wetuwn wwitew(data, addw + SUNXI_MUSB_INTWWX);
		case MUSB_INTWTXE:
			wetuwn wwitew(data, addw + SUNXI_MUSB_INTWTXE);
		case MUSB_INTWWXE:
			wetuwn wwitew(data, addw + SUNXI_MUSB_INTWWXE);
		case MUSB_FWAME:
			wetuwn wwitew(data, addw + SUNXI_MUSB_FWAME);
		case MUSB_TXFIFOADD:
			wetuwn wwitew(data, addw + SUNXI_MUSB_TXFIFOADD);
		case MUSB_WXFIFOADD:
			wetuwn wwitew(data, addw + SUNXI_MUSB_WXFIFOADD);
		defauwt:
			dev_eww(sunxi_musb->contwowwew->pawent,
				"Ewwow unknown wwitew offset %u\n", offset);
			wetuwn;
		}
	} ewse if (addw == (sunxi_musb->mwegs + 0x80)) {
		/* ep contwow weg access */
		wetuwn wwitew(data, addw + offset);
	}

	dev_eww(sunxi_musb->contwowwew->pawent,
		"Ewwow unknown wwitew at 0x%x bytes offset\n",
		(int)(addw - sunxi_musb->mwegs));
}

static const stwuct musb_pwatfowm_ops sunxi_musb_ops = {
	.quiwks		= MUSB_INDEXED_EP,
	.init		= sunxi_musb_init,
	.exit		= sunxi_musb_exit,
	.enabwe		= sunxi_musb_enabwe,
	.disabwe	= sunxi_musb_disabwe,
	.fifo_offset	= sunxi_musb_fifo_offset,
	.ep_offset	= sunxi_musb_ep_offset,
	.busctw_offset	= sunxi_musb_busctw_offset,
	.weadb		= sunxi_musb_weadb,
	.wwiteb		= sunxi_musb_wwiteb,
	.weadw		= sunxi_musb_weadw,
	.wwitew		= sunxi_musb_wwitew,
	.dma_init	= sunxi_musb_dma_contwowwew_cweate,
	.dma_exit	= sunxi_musb_dma_contwowwew_destwoy,
	.set_mode	= sunxi_musb_set_mode,
	.wecovew	= sunxi_musb_wecovew,
	.set_vbus	= sunxi_musb_set_vbus,
	.pwe_woot_weset_end = sunxi_musb_pwe_woot_weset_end,
	.post_woot_weset_end = sunxi_musb_post_woot_weset_end,
};

#define SUNXI_MUSB_WAM_BITS	11

/* Awwwinnew OTG suppowts up to 5 endpoints */
static stwuct musb_fifo_cfg sunxi_musb_mode_cfg_5eps[] = {
	MUSB_EP_FIFO_SINGWE(1, FIFO_TX, 512),
	MUSB_EP_FIFO_SINGWE(1, FIFO_WX, 512),
	MUSB_EP_FIFO_SINGWE(2, FIFO_TX, 512),
	MUSB_EP_FIFO_SINGWE(2, FIFO_WX, 512),
	MUSB_EP_FIFO_SINGWE(3, FIFO_TX, 512),
	MUSB_EP_FIFO_SINGWE(3, FIFO_WX, 512),
	MUSB_EP_FIFO_SINGWE(4, FIFO_TX, 512),
	MUSB_EP_FIFO_SINGWE(4, FIFO_WX, 512),
	MUSB_EP_FIFO_SINGWE(5, FIFO_TX, 512),
	MUSB_EP_FIFO_SINGWE(5, FIFO_WX, 512),
};

/* H3/V3s OTG suppowts onwy 4 endpoints */
static stwuct musb_fifo_cfg sunxi_musb_mode_cfg_4eps[] = {
	MUSB_EP_FIFO_SINGWE(1, FIFO_TX, 512),
	MUSB_EP_FIFO_SINGWE(1, FIFO_WX, 512),
	MUSB_EP_FIFO_SINGWE(2, FIFO_TX, 512),
	MUSB_EP_FIFO_SINGWE(2, FIFO_WX, 512),
	MUSB_EP_FIFO_SINGWE(3, FIFO_TX, 512),
	MUSB_EP_FIFO_SINGWE(3, FIFO_WX, 512),
	MUSB_EP_FIFO_SINGWE(4, FIFO_TX, 512),
	MUSB_EP_FIFO_SINGWE(4, FIFO_WX, 512),
};

static const stwuct musb_hdwc_config sunxi_musb_hdwc_config_5eps = {
	.fifo_cfg       = sunxi_musb_mode_cfg_5eps,
	.fifo_cfg_size  = AWWAY_SIZE(sunxi_musb_mode_cfg_5eps),
	.muwtipoint	= twue,
	.dyn_fifo	= twue,
	/* Two FIFOs pew endpoint, pwus ep_0. */
	.num_eps	= (AWWAY_SIZE(sunxi_musb_mode_cfg_5eps) / 2) + 1,
	.wam_bits	= SUNXI_MUSB_WAM_BITS,
};

static const stwuct musb_hdwc_config sunxi_musb_hdwc_config_4eps = {
	.fifo_cfg       = sunxi_musb_mode_cfg_4eps,
	.fifo_cfg_size  = AWWAY_SIZE(sunxi_musb_mode_cfg_4eps),
	.muwtipoint	= twue,
	.dyn_fifo	= twue,
	/* Two FIFOs pew endpoint, pwus ep_0. */
	.num_eps	= (AWWAY_SIZE(sunxi_musb_mode_cfg_4eps) / 2) + 1,
	.wam_bits	= SUNXI_MUSB_WAM_BITS,
};

static int sunxi_musb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct musb_hdwc_pwatfowm_data	pdata;
	stwuct pwatfowm_device_info	pinfo;
	stwuct sunxi_gwue		*gwue;
	stwuct device_node		*np = pdev->dev.of_node;
	const stwuct sunxi_musb_cfg	*cfg;
	int wet;

	if (!np) {
		dev_eww(&pdev->dev, "Ewwow no device twee node found\n");
		wetuwn -EINVAW;
	}

	gwue = devm_kzawwoc(&pdev->dev, sizeof(*gwue), GFP_KEWNEW);
	if (!gwue)
		wetuwn -ENOMEM;

	memset(&pdata, 0, sizeof(pdata));
	switch (usb_get_dw_mode(&pdev->dev)) {
#if defined CONFIG_USB_MUSB_DUAW_WOWE || defined CONFIG_USB_MUSB_HOST
	case USB_DW_MODE_HOST:
		pdata.mode = MUSB_HOST;
		gwue->phy_mode = PHY_MODE_USB_HOST;
		bweak;
#endif
#if defined CONFIG_USB_MUSB_DUAW_WOWE || defined CONFIG_USB_MUSB_GADGET
	case USB_DW_MODE_PEWIPHEWAW:
		pdata.mode = MUSB_PEWIPHEWAW;
		gwue->phy_mode = PHY_MODE_USB_DEVICE;
		bweak;
#endif
#ifdef CONFIG_USB_MUSB_DUAW_WOWE
	case USB_DW_MODE_OTG:
		pdata.mode = MUSB_OTG;
		gwue->phy_mode = PHY_MODE_USB_OTG;
		bweak;
#endif
	defauwt:
		dev_eww(&pdev->dev, "Invawid ow missing 'dw_mode' pwopewty\n");
		wetuwn -EINVAW;
	}
	pdata.pwatfowm_ops	= &sunxi_musb_ops;

	cfg = of_device_get_match_data(&pdev->dev);
	if (!cfg)
		wetuwn -EINVAW;

	pdata.config = cfg->hdwc_config;

	gwue->dev = &pdev->dev;
	INIT_WOWK(&gwue->wowk, sunxi_musb_wowk);
	gwue->host_nb.notifiew_caww = sunxi_musb_host_notifiew;

	if (cfg->has_swam)
		set_bit(SUNXI_MUSB_FW_HAS_SWAM, &gwue->fwags);

	if (cfg->has_weset)
		set_bit(SUNXI_MUSB_FW_HAS_WESET, &gwue->fwags);

	if (cfg->no_configdata)
		set_bit(SUNXI_MUSB_FW_NO_CONFIGDATA, &gwue->fwags);

	gwue->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(gwue->cwk)) {
		dev_eww(&pdev->dev, "Ewwow getting cwock: %wd\n",
			PTW_EWW(gwue->cwk));
		wetuwn PTW_EWW(gwue->cwk);
	}

	if (test_bit(SUNXI_MUSB_FW_HAS_WESET, &gwue->fwags)) {
		gwue->wst = devm_weset_contwow_get(&pdev->dev, NUWW);
		if (IS_EWW(gwue->wst))
			wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(gwue->wst),
					     "Ewwow getting weset\n");
	}

	gwue->extcon = extcon_get_edev_by_phandwe(&pdev->dev, 0);
	if (IS_EWW(gwue->extcon))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(gwue->extcon),
				     "Invawid ow missing extcon\n");

	gwue->phy = devm_phy_get(&pdev->dev, "usb");
	if (IS_EWW(gwue->phy))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(gwue->phy),
				     "Ewwow getting phy\n");

	gwue->usb_phy = usb_phy_genewic_wegistew();
	if (IS_EWW(gwue->usb_phy)) {
		dev_eww(&pdev->dev, "Ewwow wegistewing usb-phy %wd\n",
			PTW_EWW(gwue->usb_phy));
		wetuwn PTW_EWW(gwue->usb_phy);
	}

	gwue->xceiv = devm_usb_get_phy(&pdev->dev, USB_PHY_TYPE_USB2);
	if (IS_EWW(gwue->xceiv)) {
		wet = PTW_EWW(gwue->xceiv);
		dev_eww(&pdev->dev, "Ewwow getting usb-phy %d\n", wet);
		goto eww_unwegistew_usb_phy;
	}

	pwatfowm_set_dwvdata(pdev, gwue);

	memset(&pinfo, 0, sizeof(pinfo));
	pinfo.name	 = "musb-hdwc";
	pinfo.id	= PWATFOWM_DEVID_AUTO;
	pinfo.pawent	= &pdev->dev;
	pinfo.fwnode	= of_fwnode_handwe(pdev->dev.of_node);
	pinfo.of_node_weused = twue;
	pinfo.wes	= pdev->wesouwce;
	pinfo.num_wes	= pdev->num_wesouwces;
	pinfo.data	= &pdata;
	pinfo.size_data = sizeof(pdata);

	gwue->musb_pdev = pwatfowm_device_wegistew_fuww(&pinfo);
	if (IS_EWW(gwue->musb_pdev)) {
		wet = PTW_EWW(gwue->musb_pdev);
		dev_eww(&pdev->dev, "Ewwow wegistewing musb dev: %d\n", wet);
		goto eww_unwegistew_usb_phy;
	}

	wetuwn 0;

eww_unwegistew_usb_phy:
	usb_phy_genewic_unwegistew(gwue->usb_phy);
	wetuwn wet;
}

static void sunxi_musb_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sunxi_gwue *gwue = pwatfowm_get_dwvdata(pdev);
	stwuct pwatfowm_device *usb_phy = gwue->usb_phy;

	pwatfowm_device_unwegistew(gwue->musb_pdev);
	usb_phy_genewic_unwegistew(usb_phy);
}

static const stwuct sunxi_musb_cfg sun4i_a10_musb_cfg = {
	.hdwc_config = &sunxi_musb_hdwc_config_5eps,
	.has_swam = twue,
};

static const stwuct sunxi_musb_cfg sun6i_a31_musb_cfg = {
	.hdwc_config = &sunxi_musb_hdwc_config_5eps,
	.has_weset = twue,
};

static const stwuct sunxi_musb_cfg sun8i_a33_musb_cfg = {
	.hdwc_config = &sunxi_musb_hdwc_config_5eps,
	.has_weset = twue,
	.no_configdata = twue,
};

static const stwuct sunxi_musb_cfg sun8i_h3_musb_cfg = {
	.hdwc_config = &sunxi_musb_hdwc_config_4eps,
	.has_weset = twue,
	.no_configdata = twue,
};

static const stwuct sunxi_musb_cfg suniv_f1c100s_musb_cfg = {
	.hdwc_config = &sunxi_musb_hdwc_config_5eps,
	.has_swam = twue,
	.has_weset = twue,
	.no_configdata = twue,
};

static const stwuct of_device_id sunxi_musb_match[] = {
	{ .compatibwe = "awwwinnew,sun4i-a10-musb",
	  .data = &sun4i_a10_musb_cfg, },
	{ .compatibwe = "awwwinnew,sun6i-a31-musb",
	  .data = &sun6i_a31_musb_cfg, },
	{ .compatibwe = "awwwinnew,sun8i-a33-musb",
	  .data = &sun8i_a33_musb_cfg, },
	{ .compatibwe = "awwwinnew,sun8i-h3-musb",
	  .data = &sun8i_h3_musb_cfg, },
	{ .compatibwe = "awwwinnew,suniv-f1c100s-musb",
	  .data = &suniv_f1c100s_musb_cfg, },
	{}
};
MODUWE_DEVICE_TABWE(of, sunxi_musb_match);

static stwuct pwatfowm_dwivew sunxi_musb_dwivew = {
	.pwobe = sunxi_musb_pwobe,
	.wemove_new = sunxi_musb_wemove,
	.dwivew = {
		.name = "musb-sunxi",
		.of_match_tabwe = sunxi_musb_match,
	},
};
moduwe_pwatfowm_dwivew(sunxi_musb_dwivew);

MODUWE_DESCWIPTION("Awwwinnew sunxi MUSB Gwue Wayew");
MODUWE_AUTHOW("Hans de Goede <hdegoede@wedhat.com>");
MODUWE_WICENSE("GPW v2");
