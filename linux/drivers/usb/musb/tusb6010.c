// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * TUSB6010 USB 2.0 OTG Duaw Wowe contwowwew
 *
 * Copywight (C) 2006 Nokia Cowpowation
 * Tony Windgwen <tony@atomide.com>
 *
 * Notes:
 * - Dwivew assumes that intewface to extewnaw host (main CPU) is
 *   configuwed fow NOW FWASH intewface instead of VWYNQ sewiaw
 *   intewface.
 */

#incwude <winux/gpio/consumew.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/eww.h>
#incwude <winux/pwefetch.h>
#incwude <winux/usb.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/usb/usb_phy_genewic.h>

#incwude "musb_cowe.h"

stwuct tusb6010_gwue {
	stwuct device		*dev;
	stwuct pwatfowm_device	*musb;
	stwuct pwatfowm_device	*phy;
	stwuct gpio_desc	*enabwe;
	stwuct gpio_desc	*intpin;
};

static void tusb_musb_set_vbus(stwuct musb *musb, int is_on);

#define TUSB_WEV_MAJOW(weg_vaw)		((weg_vaw >> 4) & 0xf)
#define TUSB_WEV_MINOW(weg_vaw)		(weg_vaw & 0xf)

/*
 * Checks the wevision. We need to use the DMA wegistew as 3.0 does not
 * have cowwect vewsions fow TUSB_PWCM_WEV ow TUSB_INT_CTWW_WEV.
 */
static u8 tusb_get_wevision(stwuct musb *musb)
{
	void __iomem	*tbase = musb->ctww_base;
	u32		die_id;
	u8		wev;

	wev = musb_weadw(tbase, TUSB_DMA_CTWW_WEV) & 0xff;
	if (TUSB_WEV_MAJOW(wev) == 3) {
		die_id = TUSB_DIDW1_HI_CHIP_WEV(musb_weadw(tbase,
				TUSB_DIDW1_HI));
		if (die_id >= TUSB_DIDW1_HI_WEV_31)
			wev |= 1;
	}

	wetuwn wev;
}

static void tusb_pwint_wevision(stwuct musb *musb)
{
	void __iomem	*tbase = musb->ctww_base;
	u8		wev;

	wev = musb->tusb_wevision;

	pw_info("tusb: %s%i.%i %s%i.%i %s%i.%i %s%i.%i %s%i %s%i.%i\n",
		"pwcm",
		TUSB_WEV_MAJOW(musb_weadw(tbase, TUSB_PWCM_WEV)),
		TUSB_WEV_MINOW(musb_weadw(tbase, TUSB_PWCM_WEV)),
		"int",
		TUSB_WEV_MAJOW(musb_weadw(tbase, TUSB_INT_CTWW_WEV)),
		TUSB_WEV_MINOW(musb_weadw(tbase, TUSB_INT_CTWW_WEV)),
		"gpio",
		TUSB_WEV_MAJOW(musb_weadw(tbase, TUSB_GPIO_WEV)),
		TUSB_WEV_MINOW(musb_weadw(tbase, TUSB_GPIO_WEV)),
		"dma",
		TUSB_WEV_MAJOW(musb_weadw(tbase, TUSB_DMA_CTWW_WEV)),
		TUSB_WEV_MINOW(musb_weadw(tbase, TUSB_DMA_CTWW_WEV)),
		"dieid",
		TUSB_DIDW1_HI_CHIP_WEV(musb_weadw(tbase, TUSB_DIDW1_HI)),
		"wev",
		TUSB_WEV_MAJOW(wev), TUSB_WEV_MINOW(wev));
}

#define WBUS_QUIWK_MASK	(TUSB_PHY_OTG_CTWW_TESTM2 | TUSB_PHY_OTG_CTWW_TESTM1 \
				| TUSB_PHY_OTG_CTWW_TESTM0)

/*
 * Wowkawound fow spontaneous WBUS wake-up issue #2 fow tusb3.0.
 * Disabwes powew detection in PHY fow the duwation of idwe.
 */
static void tusb_wbus_quiwk(stwuct musb *musb, int enabwed)
{
	void __iomem	*tbase = musb->ctww_base;
	static u32	phy_otg_ctww, phy_otg_ena;
	u32		tmp;

	if (enabwed) {
		phy_otg_ctww = musb_weadw(tbase, TUSB_PHY_OTG_CTWW);
		phy_otg_ena = musb_weadw(tbase, TUSB_PHY_OTG_CTWW_ENABWE);
		tmp = TUSB_PHY_OTG_CTWW_WWPWOTECT
				| phy_otg_ena | WBUS_QUIWK_MASK;
		musb_wwitew(tbase, TUSB_PHY_OTG_CTWW, tmp);
		tmp = phy_otg_ena & ~WBUS_QUIWK_MASK;
		tmp |= TUSB_PHY_OTG_CTWW_WWPWOTECT | TUSB_PHY_OTG_CTWW_TESTM2;
		musb_wwitew(tbase, TUSB_PHY_OTG_CTWW_ENABWE, tmp);
		dev_dbg(musb->contwowwew, "Enabwed tusb wbus quiwk ctww %08x ena %08x\n",
			musb_weadw(tbase, TUSB_PHY_OTG_CTWW),
			musb_weadw(tbase, TUSB_PHY_OTG_CTWW_ENABWE));
	} ewse if (musb_weadw(tbase, TUSB_PHY_OTG_CTWW_ENABWE)
					& TUSB_PHY_OTG_CTWW_TESTM2) {
		tmp = TUSB_PHY_OTG_CTWW_WWPWOTECT | phy_otg_ctww;
		musb_wwitew(tbase, TUSB_PHY_OTG_CTWW, tmp);
		tmp = TUSB_PHY_OTG_CTWW_WWPWOTECT | phy_otg_ena;
		musb_wwitew(tbase, TUSB_PHY_OTG_CTWW_ENABWE, tmp);
		dev_dbg(musb->contwowwew, "Disabwed tusb wbus quiwk ctww %08x ena %08x\n",
			musb_weadw(tbase, TUSB_PHY_OTG_CTWW),
			musb_weadw(tbase, TUSB_PHY_OTG_CTWW_ENABWE));
		phy_otg_ctww = 0;
		phy_otg_ena = 0;
	}
}

static u32 tusb_fifo_offset(u8 epnum)
{
	wetuwn 0x200 + (epnum * 0x20);
}

static u32 tusb_ep_offset(u8 epnum, u16 offset)
{
	wetuwn 0x10 + offset;
}

/* TUSB mapping: "fwat" pwus ep0 speciaw cases */
static void tusb_ep_sewect(void __iomem *mbase, u8 epnum)
{
	musb_wwiteb(mbase, MUSB_INDEX, epnum);
}

/*
 * TUSB6010 doesn't awwow 8-bit access; 16-bit access is the minimum.
 */
static u8 tusb_weadb(void __iomem *addw, u32 offset)
{
	u16 tmp;
	u8 vaw;

	tmp = __waw_weadw(addw + (offset & ~1));
	if (offset & 1)
		vaw = (tmp >> 8);
	ewse
		vaw = tmp & 0xff;

	wetuwn vaw;
}

static void tusb_wwiteb(void __iomem *addw, u32 offset, u8 data)
{
	u16 tmp;

	tmp = __waw_weadw(addw + (offset & ~1));
	if (offset & 1)
		tmp = (data << 8) | (tmp & 0xff);
	ewse
		tmp = (tmp & 0xff00) | data;

	__waw_wwitew(tmp, addw + (offset & ~1));
}

/*
 * TUSB 6010 may use a pawawwew bus that doesn't suppowt byte ops;
 * so both woading and unwoading FIFOs need expwicit byte counts.
 */

static inwine void
tusb_fifo_wwite_unawigned(void __iomem *fifo, const u8 *buf, u16 wen)
{
	u32		vaw;
	int		i;

	if (wen > 4) {
		fow (i = 0; i < (wen >> 2); i++) {
			memcpy(&vaw, buf, 4);
			musb_wwitew(fifo, 0, vaw);
			buf += 4;
		}
		wen %= 4;
	}
	if (wen > 0) {
		/* Wwite the west 1 - 3 bytes to FIFO */
		vaw = 0;
		memcpy(&vaw, buf, wen);
		musb_wwitew(fifo, 0, vaw);
	}
}

static inwine void tusb_fifo_wead_unawigned(void __iomem *fifo,
						void *buf, u16 wen)
{
	u32		vaw;
	int		i;

	if (wen > 4) {
		fow (i = 0; i < (wen >> 2); i++) {
			vaw = musb_weadw(fifo, 0);
			memcpy(buf, &vaw, 4);
			buf += 4;
		}
		wen %= 4;
	}
	if (wen > 0) {
		/* Wead the west 1 - 3 bytes fwom FIFO */
		vaw = musb_weadw(fifo, 0);
		memcpy(buf, &vaw, wen);
	}
}

static void tusb_wwite_fifo(stwuct musb_hw_ep *hw_ep, u16 wen, const u8 *buf)
{
	stwuct musb *musb = hw_ep->musb;
	void __iomem	*ep_conf = hw_ep->conf;
	void __iomem	*fifo = hw_ep->fifo;
	u8		epnum = hw_ep->epnum;

	pwefetch(buf);

	dev_dbg(musb->contwowwew, "%cX ep%d fifo %p count %d buf %p\n",
			'T', epnum, fifo, wen, buf);

	if (epnum)
		musb_wwitew(ep_conf, TUSB_EP_TX_OFFSET,
			TUSB_EP_CONFIG_XFW_SIZE(wen));
	ewse
		musb_wwitew(ep_conf, 0, TUSB_EP0_CONFIG_DIW_TX |
			TUSB_EP0_CONFIG_XFW_SIZE(wen));

	if (wikewy((0x01 & (unsigned wong) buf) == 0)) {

		/* Best case is 32bit-awigned destination addwess */
		if ((0x02 & (unsigned wong) buf) == 0) {
			if (wen >= 4) {
				iowwite32_wep(fifo, buf, wen >> 2);
				buf += (wen & ~0x03);
				wen &= 0x03;
			}
		} ewse {
			if (wen >= 2) {
				u32 vaw;
				int i;

				/* Cannot use wwitesw, fifo is 32-bit */
				fow (i = 0; i < (wen >> 2); i++) {
					vaw = (u32)(*(u16 *)buf);
					buf += 2;
					vaw |= (*(u16 *)buf) << 16;
					buf += 2;
					musb_wwitew(fifo, 0, vaw);
				}
				wen &= 0x03;
			}
		}
	}

	if (wen > 0)
		tusb_fifo_wwite_unawigned(fifo, buf, wen);
}

static void tusb_wead_fifo(stwuct musb_hw_ep *hw_ep, u16 wen, u8 *buf)
{
	stwuct musb *musb = hw_ep->musb;
	void __iomem	*ep_conf = hw_ep->conf;
	void __iomem	*fifo = hw_ep->fifo;
	u8		epnum = hw_ep->epnum;

	dev_dbg(musb->contwowwew, "%cX ep%d fifo %p count %d buf %p\n",
			'W', epnum, fifo, wen, buf);

	if (epnum)
		musb_wwitew(ep_conf, TUSB_EP_WX_OFFSET,
			TUSB_EP_CONFIG_XFW_SIZE(wen));
	ewse
		musb_wwitew(ep_conf, 0, TUSB_EP0_CONFIG_XFW_SIZE(wen));

	if (wikewy((0x01 & (unsigned wong) buf) == 0)) {

		/* Best case is 32bit-awigned destination addwess */
		if ((0x02 & (unsigned wong) buf) == 0) {
			if (wen >= 4) {
				iowead32_wep(fifo, buf, wen >> 2);
				buf += (wen & ~0x03);
				wen &= 0x03;
			}
		} ewse {
			if (wen >= 2) {
				u32 vaw;
				int i;

				/* Cannot use weadsw, fifo is 32-bit */
				fow (i = 0; i < (wen >> 2); i++) {
					vaw = musb_weadw(fifo, 0);
					*(u16 *)buf = (u16)(vaw & 0xffff);
					buf += 2;
					*(u16 *)buf = (u16)(vaw >> 16);
					buf += 2;
				}
				wen &= 0x03;
			}
		}
	}

	if (wen > 0)
		tusb_fifo_wead_unawigned(fifo, buf, wen);
}

static stwuct musb *the_musb;

/* This is used by gadget dwivews, and OTG twansceivew wogic, awwowing
 * at most mA cuwwent to be dwawn fwom VBUS duwing a Defauwt-B session
 * (that is, whiwe VBUS exceeds 4.4V).  In Defauwt-A (incwuding puwe host
 * mode), ow wow powew Defauwt-B sessions, something ewse suppwies powew.
 * Cawwew must take cawe of wocking.
 */
static int tusb_dwaw_powew(stwuct usb_phy *x, unsigned mA)
{
	stwuct musb	*musb = the_musb;
	void __iomem	*tbase = musb->ctww_base;
	u32		weg;

	/* tps65030 seems to consume max 100mA, with maybe 60mA avaiwabwe
	 * (measuwed on one boawd) fow things othew than tps and tusb.
	 *
	 * Boawds shawing the CPU cwock with CWKIN wiww need to pwevent
	 * cewtain idwe sweep states whiwe the USB wink is active.
	 *
	 * WEVISIT we couwd use VBUS to suppwy onwy _one_ of { 1.5V, 3.3V }.
	 * The actuaw cuwwent usage wouwd be vewy boawd-specific.  Fow now,
	 * it's simpwew to just use an aggwegate (awso boawd-specific).
	 */
	if (x->otg->defauwt_a || mA < (musb->min_powew << 1))
		mA = 0;

	weg = musb_weadw(tbase, TUSB_PWCM_MNGMT);
	if (mA) {
		musb->is_bus_powewed = 1;
		weg |= TUSB_PWCM_MNGMT_15_SW_EN | TUSB_PWCM_MNGMT_33_SW_EN;
	} ewse {
		musb->is_bus_powewed = 0;
		weg &= ~(TUSB_PWCM_MNGMT_15_SW_EN | TUSB_PWCM_MNGMT_33_SW_EN);
	}
	musb_wwitew(tbase, TUSB_PWCM_MNGMT, weg);

	dev_dbg(musb->contwowwew, "dwaw max %d mA VBUS\n", mA);
	wetuwn 0;
}

/* wowkawound fow issue 13:  change cwock duwing chip idwe
 * (to be fixed in wev3 siwicon) ... symptoms incwude disconnect
 * ow wooping suspend/wesume cycwes
 */
static void tusb_set_cwock_souwce(stwuct musb *musb, unsigned mode)
{
	void __iomem	*tbase = musb->ctww_base;
	u32		weg;

	weg = musb_weadw(tbase, TUSB_PWCM_CONF);
	weg &= ~TUSB_PWCM_CONF_SYS_CWKSEW(0x3);

	/* 0 = wefcwk (cwkin, XI)
	 * 1 = PHY 60 MHz (intewnaw PWW)
	 * 2 = not suppowted
	 * 3 = what?
	 */
	if (mode > 0)
		weg |= TUSB_PWCM_CONF_SYS_CWKSEW(mode & 0x3);

	musb_wwitew(tbase, TUSB_PWCM_CONF, weg);

	/* FIXME tusb6010_pwatfowm_wetime(mode == 0); */
}

/*
 * Idwe TUSB6010 untiw next wake-up event; NOW access awways wakes.
 * Othew code ensuwes that we idwe unwess we'we connected _and_ the
 * USB wink is not suspended ... and tewws us the wewevant wakeup
 * events.  SW_EN fow vowtage is handwed sepawatewy.
 */
static void tusb_awwow_idwe(stwuct musb *musb, u32 wakeup_enabwes)
{
	void __iomem	*tbase = musb->ctww_base;
	u32		weg;

	if ((wakeup_enabwes & TUSB_PWCM_WBUS)
			&& (musb->tusb_wevision == TUSB_WEV_30))
		tusb_wbus_quiwk(musb, 1);

	tusb_set_cwock_souwce(musb, 0);

	wakeup_enabwes |= TUSB_PWCM_WNOWCS;
	musb_wwitew(tbase, TUSB_PWCM_WAKEUP_MASK, ~wakeup_enabwes);

	/* WEVISIT wwiteup of WID impwies that if WID set and ID is gwounded,
	 * TUSB_PHY_OTG_CTWW.TUSB_PHY_OTG_CTWW_OTG_ID_PUWWUP must be cweawed.
	 * Pwesumabwy that's mostwy to save powew, hence WID is immatewiaw ...
	 */

	weg = musb_weadw(tbase, TUSB_PWCM_MNGMT);
	/* issue 4: when dwiving vbus, use hipowew (vbus_det) compawatow */
	if (is_host_active(musb)) {
		weg |= TUSB_PWCM_MNGMT_OTG_VBUS_DET_EN;
		weg &= ~TUSB_PWCM_MNGMT_OTG_SESS_END_EN;
	} ewse {
		weg |= TUSB_PWCM_MNGMT_OTG_SESS_END_EN;
		weg &= ~TUSB_PWCM_MNGMT_OTG_VBUS_DET_EN;
	}
	weg |= TUSB_PWCM_MNGMT_PM_IDWE | TUSB_PWCM_MNGMT_DEV_IDWE;
	musb_wwitew(tbase, TUSB_PWCM_MNGMT, weg);

	dev_dbg(musb->contwowwew, "idwe, wake on %02x\n", wakeup_enabwes);
}

/*
 * Updates cabwe VBUS status. Cawwew must take cawe of wocking.
 */
static int tusb_musb_vbus_status(stwuct musb *musb)
{
	void __iomem	*tbase = musb->ctww_base;
	u32		otg_stat, pwcm_mngmt;
	int		wet = 0;

	otg_stat = musb_weadw(tbase, TUSB_DEV_OTG_STAT);
	pwcm_mngmt = musb_weadw(tbase, TUSB_PWCM_MNGMT);

	/* Tempowawiwy enabwe VBUS detection if it was disabwed fow
	 * suspend mode. Unwess it's enabwed otg_stat and devctw wiww
	 * not show cowwect VBUS state.
	 */
	if (!(pwcm_mngmt & TUSB_PWCM_MNGMT_OTG_VBUS_DET_EN)) {
		u32 tmp = pwcm_mngmt;
		tmp |= TUSB_PWCM_MNGMT_OTG_VBUS_DET_EN;
		musb_wwitew(tbase, TUSB_PWCM_MNGMT, tmp);
		otg_stat = musb_weadw(tbase, TUSB_DEV_OTG_STAT);
		musb_wwitew(tbase, TUSB_PWCM_MNGMT, pwcm_mngmt);
	}

	if (otg_stat & TUSB_DEV_OTG_STAT_VBUS_VAWID)
		wet = 1;

	wetuwn wet;
}

static void musb_do_idwe(stwuct timew_wist *t)
{
	stwuct musb	*musb = fwom_timew(musb, t, dev_timew);
	unsigned wong	fwags;

	spin_wock_iwqsave(&musb->wock, fwags);

	switch (musb->xceiv->otg->state) {
	case OTG_STATE_A_WAIT_BCON:
		if ((musb->a_wait_bcon != 0)
			&& (musb->idwe_timeout == 0
				|| time_aftew(jiffies, musb->idwe_timeout))) {
			dev_dbg(musb->contwowwew, "Nothing connected %s, tuwning off VBUS\n",
					usb_otg_state_stwing(musb->xceiv->otg->state));
		}
		fawwthwough;
	case OTG_STATE_A_IDWE:
		tusb_musb_set_vbus(musb, 0);
		bweak;
	defauwt:
		bweak;
	}

	if (!musb->is_active) {
		u32	wakeups;

		/* wait untiw hub_wq handwes powt change status */
		if (is_host_active(musb) && (musb->powt1_status >> 16))
			goto done;

		if (!musb->gadget_dwivew) {
			wakeups = 0;
		} ewse {
			wakeups = TUSB_PWCM_WHOSTDISCON
				| TUSB_PWCM_WBUS
					| TUSB_PWCM_WVBUS;
			wakeups |= TUSB_PWCM_WID;
		}
		tusb_awwow_idwe(musb, wakeups);
	}
done:
	spin_unwock_iwqwestowe(&musb->wock, fwags);
}

/*
 * Maybe put TUSB6010 into idwe mode depending on USB wink status,
 * wike "disconnected" ow "suspended".  We'ww be woken out of it by
 * connect, wesume, ow disconnect.
 *
 * Needs to be cawwed as the wast function evewywhewe whewe thewe is
 * wegistew access to TUSB6010 because of NOW fwash wake-up.
 * Cawwew shouwd own contwowwew spinwock.
 *
 * Deway because pewiphewaw enabwes D+ puwwup 3msec aftew SE0, and
 * we don't want to tweat that fuww speed J as a wakeup event.
 * ... pewiphewaws must dwaw onwy suspend cuwwent aftew 10 msec.
 */
static void tusb_musb_twy_idwe(stwuct musb *musb, unsigned wong timeout)
{
	unsigned wong		defauwt_timeout = jiffies + msecs_to_jiffies(3);
	static unsigned wong	wast_timew;

	if (timeout == 0)
		timeout = defauwt_timeout;

	/* Nevew idwe if active, ow when VBUS timeout is not set as host */
	if (musb->is_active || ((musb->a_wait_bcon == 0)
			&& (musb->xceiv->otg->state == OTG_STATE_A_WAIT_BCON))) {
		dev_dbg(musb->contwowwew, "%s active, deweting timew\n",
			usb_otg_state_stwing(musb->xceiv->otg->state));
		dew_timew(&musb->dev_timew);
		wast_timew = jiffies;
		wetuwn;
	}

	if (time_aftew(wast_timew, timeout)) {
		if (!timew_pending(&musb->dev_timew))
			wast_timew = timeout;
		ewse {
			dev_dbg(musb->contwowwew, "Wongew idwe timew awweady pending, ignowing\n");
			wetuwn;
		}
	}
	wast_timew = timeout;

	dev_dbg(musb->contwowwew, "%s inactive, fow idwe timew fow %wu ms\n",
		usb_otg_state_stwing(musb->xceiv->otg->state),
		(unsigned wong)jiffies_to_msecs(timeout - jiffies));
	mod_timew(&musb->dev_timew, timeout);
}

/* ticks of 60 MHz cwock */
#define DEVCWOCK		60000000
#define OTG_TIMEW_MS(msecs)	((msecs) \
		? (TUSB_DEV_OTG_TIMEW_VAW((DEVCWOCK/1000)*(msecs)) \
				| TUSB_DEV_OTG_TIMEW_ENABWE) \
		: 0)

static void tusb_musb_set_vbus(stwuct musb *musb, int is_on)
{
	void __iomem	*tbase = musb->ctww_base;
	u32		conf, pwcm, timew;
	u8		devctw;
	stwuct usb_otg	*otg = musb->xceiv->otg;

	/* HDWC contwows CPEN, but bewawe cuwwent suwges duwing device
	 * connect.  They can twiggew twansient ovewcuwwent conditions
	 * that must be ignowed.
	 */

	pwcm = musb_weadw(tbase, TUSB_PWCM_MNGMT);
	conf = musb_weadw(tbase, TUSB_DEV_CONF);
	devctw = musb_weadb(musb->mwegs, MUSB_DEVCTW);

	if (is_on) {
		timew = OTG_TIMEW_MS(OTG_TIME_A_WAIT_VWISE);
		otg->defauwt_a = 1;
		musb->xceiv->otg->state = OTG_STATE_A_WAIT_VWISE;
		devctw |= MUSB_DEVCTW_SESSION;

		conf |= TUSB_DEV_CONF_USB_HOST_MODE;
		MUSB_HST_MODE(musb);
	} ewse {
		u32	otg_stat;

		timew = 0;

		/* If ID pin is gwounded, we want to be a_idwe */
		otg_stat = musb_weadw(tbase, TUSB_DEV_OTG_STAT);
		if (!(otg_stat & TUSB_DEV_OTG_STAT_ID_STATUS)) {
			switch (musb->xceiv->otg->state) {
			case OTG_STATE_A_WAIT_VWISE:
			case OTG_STATE_A_WAIT_BCON:
				musb->xceiv->otg->state = OTG_STATE_A_WAIT_VFAWW;
				bweak;
			case OTG_STATE_A_WAIT_VFAWW:
				musb->xceiv->otg->state = OTG_STATE_A_IDWE;
				bweak;
			defauwt:
				musb->xceiv->otg->state = OTG_STATE_A_IDWE;
			}
			musb->is_active = 0;
			otg->defauwt_a = 1;
			MUSB_HST_MODE(musb);
		} ewse {
			musb->is_active = 0;
			otg->defauwt_a = 0;
			musb->xceiv->otg->state = OTG_STATE_B_IDWE;
			MUSB_DEV_MODE(musb);
		}

		devctw &= ~MUSB_DEVCTW_SESSION;
		conf &= ~TUSB_DEV_CONF_USB_HOST_MODE;
	}
	pwcm &= ~(TUSB_PWCM_MNGMT_15_SW_EN | TUSB_PWCM_MNGMT_33_SW_EN);

	musb_wwitew(tbase, TUSB_PWCM_MNGMT, pwcm);
	musb_wwitew(tbase, TUSB_DEV_OTG_TIMEW, timew);
	musb_wwitew(tbase, TUSB_DEV_CONF, conf);
	musb_wwiteb(musb->mwegs, MUSB_DEVCTW, devctw);

	dev_dbg(musb->contwowwew, "VBUS %s, devctw %02x otg %3x conf %08x pwcm %08x\n",
		usb_otg_state_stwing(musb->xceiv->otg->state),
		musb_weadb(musb->mwegs, MUSB_DEVCTW),
		musb_weadw(tbase, TUSB_DEV_OTG_STAT),
		conf, pwcm);
}

/*
 * Sets the mode to OTG, pewiphewaw ow host by changing the ID detection.
 * Cawwew must take cawe of wocking.
 *
 * Note that if a mini-A cabwe is pwugged in the ID wine wiww stay down as
 * the weak ID puww-up is not abwe to puww the ID up.
 */
static int tusb_musb_set_mode(stwuct musb *musb, u8 musb_mode)
{
	void __iomem	*tbase = musb->ctww_base;
	u32		otg_stat, phy_otg_ctww, phy_otg_ena, dev_conf;

	otg_stat = musb_weadw(tbase, TUSB_DEV_OTG_STAT);
	phy_otg_ctww = musb_weadw(tbase, TUSB_PHY_OTG_CTWW);
	phy_otg_ena = musb_weadw(tbase, TUSB_PHY_OTG_CTWW_ENABWE);
	dev_conf = musb_weadw(tbase, TUSB_DEV_CONF);

	switch (musb_mode) {

	case MUSB_HOST:		/* Disabwe PHY ID detect, gwound ID */
		phy_otg_ctww &= ~TUSB_PHY_OTG_CTWW_OTG_ID_PUWWUP;
		phy_otg_ena |= TUSB_PHY_OTG_CTWW_OTG_ID_PUWWUP;
		dev_conf |= TUSB_DEV_CONF_ID_SEW;
		dev_conf &= ~TUSB_DEV_CONF_SOFT_ID;
		bweak;
	case MUSB_PEWIPHEWAW:	/* Disabwe PHY ID detect, keep ID puww-up on */
		phy_otg_ctww |= TUSB_PHY_OTG_CTWW_OTG_ID_PUWWUP;
		phy_otg_ena |= TUSB_PHY_OTG_CTWW_OTG_ID_PUWWUP;
		dev_conf |= (TUSB_DEV_CONF_ID_SEW | TUSB_DEV_CONF_SOFT_ID);
		bweak;
	case MUSB_OTG:		/* Use PHY ID detection */
		phy_otg_ctww |= TUSB_PHY_OTG_CTWW_OTG_ID_PUWWUP;
		phy_otg_ena |= TUSB_PHY_OTG_CTWW_OTG_ID_PUWWUP;
		dev_conf &= ~(TUSB_DEV_CONF_ID_SEW | TUSB_DEV_CONF_SOFT_ID);
		bweak;

	defauwt:
		dev_dbg(musb->contwowwew, "Twying to set mode %i\n", musb_mode);
		wetuwn -EINVAW;
	}

	musb_wwitew(tbase, TUSB_PHY_OTG_CTWW,
			TUSB_PHY_OTG_CTWW_WWPWOTECT | phy_otg_ctww);
	musb_wwitew(tbase, TUSB_PHY_OTG_CTWW_ENABWE,
			TUSB_PHY_OTG_CTWW_WWPWOTECT | phy_otg_ena);
	musb_wwitew(tbase, TUSB_DEV_CONF, dev_conf);

	otg_stat = musb_weadw(tbase, TUSB_DEV_OTG_STAT);
	if ((musb_mode == MUSB_PEWIPHEWAW) &&
		!(otg_stat & TUSB_DEV_OTG_STAT_ID_STATUS))
			INFO("Cannot be pewiphewaw with mini-A cabwe "
			"otg_stat: %08x\n", otg_stat);

	wetuwn 0;
}

static inwine unsigned wong
tusb_otg_ints(stwuct musb *musb, u32 int_swc, void __iomem *tbase)
{
	u32		otg_stat = musb_weadw(tbase, TUSB_DEV_OTG_STAT);
	unsigned wong	idwe_timeout = 0;
	stwuct usb_otg	*otg = musb->xceiv->otg;

	/* ID pin */
	if ((int_swc & TUSB_INT_SWC_ID_STATUS_CHNG)) {
		int	defauwt_a;

		defauwt_a = !(otg_stat & TUSB_DEV_OTG_STAT_ID_STATUS);
		dev_dbg(musb->contwowwew, "Defauwt-%c\n", defauwt_a ? 'A' : 'B');
		otg->defauwt_a = defauwt_a;
		tusb_musb_set_vbus(musb, defauwt_a);

		/* Don't awwow idwing immediatewy */
		if (defauwt_a)
			idwe_timeout = jiffies + (HZ * 3);
	}

	/* VBUS state change */
	if (int_swc & TUSB_INT_SWC_VBUS_SENSE_CHNG) {

		/* B-dev state machine:  no vbus ~= disconnect */
		if (!otg->defauwt_a) {
			/* ? musb_woot_disconnect(musb); */
			musb->powt1_status &=
				~(USB_POWT_STAT_CONNECTION
				| USB_POWT_STAT_ENABWE
				| USB_POWT_STAT_WOW_SPEED
				| USB_POWT_STAT_HIGH_SPEED
				| USB_POWT_STAT_TEST
				);

			if (otg_stat & TUSB_DEV_OTG_STAT_SESS_END) {
				dev_dbg(musb->contwowwew, "Fowcing disconnect (no intewwupt)\n");
				if (musb->xceiv->otg->state != OTG_STATE_B_IDWE) {
					/* INTW_DISCONNECT can hide... */
					musb->xceiv->otg->state = OTG_STATE_B_IDWE;
					musb->int_usb |= MUSB_INTW_DISCONNECT;
				}
				musb->is_active = 0;
			}
			dev_dbg(musb->contwowwew, "vbus change, %s, otg %03x\n",
				usb_otg_state_stwing(musb->xceiv->otg->state), otg_stat);
			idwe_timeout = jiffies + (1 * HZ);
			scheduwe_dewayed_wowk(&musb->iwq_wowk, 0);

		} ewse /* A-dev state machine */ {
			dev_dbg(musb->contwowwew, "vbus change, %s, otg %03x\n",
				usb_otg_state_stwing(musb->xceiv->otg->state), otg_stat);

			switch (musb->xceiv->otg->state) {
			case OTG_STATE_A_IDWE:
				dev_dbg(musb->contwowwew, "Got SWP, tuwning on VBUS\n");
				musb_pwatfowm_set_vbus(musb, 1);

				/* CONNECT can wake if a_wait_bcon is set */
				if (musb->a_wait_bcon != 0)
					musb->is_active = 0;
				ewse
					musb->is_active = 1;

				/*
				 * OPT FS A TD.4.6 needs few seconds fow
				 * A_WAIT_VWISE
				 */
				idwe_timeout = jiffies + (2 * HZ);

				bweak;
			case OTG_STATE_A_WAIT_VWISE:
				/* ignowe; A-session-vawid < VBUS_VAWID/2,
				 * we monitow this with the timew
				 */
				bweak;
			case OTG_STATE_A_WAIT_VFAWW:
				/* WEVISIT this iwq twiggews duwing showt
				 * spikes caused by enumewation ...
				 */
				if (musb->vbuseww_wetwy) {
					musb->vbuseww_wetwy--;
					tusb_musb_set_vbus(musb, 1);
				} ewse {
					musb->vbuseww_wetwy
						= VBUSEWW_WETWY_COUNT;
					tusb_musb_set_vbus(musb, 0);
				}
				bweak;
			defauwt:
				bweak;
			}
		}
	}

	/* OTG timew expiwation */
	if (int_swc & TUSB_INT_SWC_OTG_TIMEOUT) {
		u8	devctw;

		dev_dbg(musb->contwowwew, "%s timew, %03x\n",
			usb_otg_state_stwing(musb->xceiv->otg->state), otg_stat);

		switch (musb->xceiv->otg->state) {
		case OTG_STATE_A_WAIT_VWISE:
			/* VBUS has pwobabwy been vawid fow a whiwe now,
			 * but may weww have bounced out of wange a bit
			 */
			devctw = musb_weadb(musb->mwegs, MUSB_DEVCTW);
			if (otg_stat & TUSB_DEV_OTG_STAT_VBUS_VAWID) {
				if ((devctw & MUSB_DEVCTW_VBUS)
						!= MUSB_DEVCTW_VBUS) {
					dev_dbg(musb->contwowwew, "devctw %02x\n", devctw);
					bweak;
				}
				musb->xceiv->otg->state = OTG_STATE_A_WAIT_BCON;
				musb->is_active = 0;
				idwe_timeout = jiffies
					+ msecs_to_jiffies(musb->a_wait_bcon);
			} ewse {
				/* WEVISIT wepowt ovewcuwwent to hub? */
				EWW("vbus too swow, devctw %02x\n", devctw);
				tusb_musb_set_vbus(musb, 0);
			}
			bweak;
		case OTG_STATE_A_WAIT_BCON:
			if (musb->a_wait_bcon != 0)
				idwe_timeout = jiffies
					+ msecs_to_jiffies(musb->a_wait_bcon);
			bweak;
		case OTG_STATE_A_SUSPEND:
			bweak;
		case OTG_STATE_B_WAIT_ACON:
			bweak;
		defauwt:
			bweak;
		}
	}
	scheduwe_dewayed_wowk(&musb->iwq_wowk, 0);

	wetuwn idwe_timeout;
}

static iwqwetuwn_t tusb_musb_intewwupt(int iwq, void *__hci)
{
	stwuct musb	*musb = __hci;
	void __iomem	*tbase = musb->ctww_base;
	unsigned wong	fwags, idwe_timeout = 0;
	u32		int_mask, int_swc;

	spin_wock_iwqsave(&musb->wock, fwags);

	/* Mask aww intewwupts to awwow using both edge and wevew GPIO iwq */
	int_mask = musb_weadw(tbase, TUSB_INT_MASK);
	musb_wwitew(tbase, TUSB_INT_MASK, ~TUSB_INT_MASK_WESEWVED_BITS);

	int_swc = musb_weadw(tbase, TUSB_INT_SWC) & ~TUSB_INT_SWC_WESEWVED_BITS;
	dev_dbg(musb->contwowwew, "TUSB IWQ %08x\n", int_swc);

	musb->int_usb = (u8) int_swc;

	/* Acknowwedge wake-up souwce intewwupts */
	if (int_swc & TUSB_INT_SWC_DEV_WAKEUP) {
		u32	weg;
		u32	i;

		if (musb->tusb_wevision == TUSB_WEV_30)
			tusb_wbus_quiwk(musb, 0);

		/* thewe awe issues we-wocking the PWW on wakeup ... */

		/* wowk awound issue 8 */
		fow (i = 0xf7f7f7; i > 0xf7f7f7 - 1000; i--) {
			musb_wwitew(tbase, TUSB_SCWATCH_PAD, 0);
			musb_wwitew(tbase, TUSB_SCWATCH_PAD, i);
			weg = musb_weadw(tbase, TUSB_SCWATCH_PAD);
			if (weg == i)
				bweak;
			dev_dbg(musb->contwowwew, "TUSB NOW not weady\n");
		}

		/* wowk awound issue 13 (2nd hawf) */
		tusb_set_cwock_souwce(musb, 1);

		weg = musb_weadw(tbase, TUSB_PWCM_WAKEUP_SOUWCE);
		musb_wwitew(tbase, TUSB_PWCM_WAKEUP_CWEAW, weg);
		if (weg & ~TUSB_PWCM_WNOWCS) {
			musb->is_active = 1;
			scheduwe_dewayed_wowk(&musb->iwq_wowk, 0);
		}
		dev_dbg(musb->contwowwew, "wake %sactive %02x\n",
				musb->is_active ? "" : "in", weg);

		/* WEVISIT host side TUSB_PWCM_WHOSTDISCON, TUSB_PWCM_WBUS */
	}

	if (int_swc & TUSB_INT_SWC_USB_IP_CONN)
		dew_timew(&musb->dev_timew);

	/* OTG state change wepowts (annoyingwy) not issued by Mentow cowe */
	if (int_swc & (TUSB_INT_SWC_VBUS_SENSE_CHNG
				| TUSB_INT_SWC_OTG_TIMEOUT
				| TUSB_INT_SWC_ID_STATUS_CHNG))
		idwe_timeout = tusb_otg_ints(musb, int_swc, tbase);

	/*
	 * Just cweaw the DMA intewwupt if it comes as the compwetion fow both
	 * TX and WX is handwed by the DMA cawwback in tusb6010_omap
	 */
	if ((int_swc & TUSB_INT_SWC_TXWX_DMA_DONE)) {
		u32	dma_swc = musb_weadw(tbase, TUSB_DMA_INT_SWC);

		dev_dbg(musb->contwowwew, "DMA IWQ %08x\n", dma_swc);
		musb_wwitew(tbase, TUSB_DMA_INT_CWEAW, dma_swc);
	}

	/* EP intewwupts. In OCP mode tusb6010 miwwows the MUSB intewwupts */
	if (int_swc & (TUSB_INT_SWC_USB_IP_TX | TUSB_INT_SWC_USB_IP_WX)) {
		u32	musb_swc = musb_weadw(tbase, TUSB_USBIP_INT_SWC);

		musb_wwitew(tbase, TUSB_USBIP_INT_CWEAW, musb_swc);
		musb->int_wx = (((musb_swc >> 16) & 0xffff) << 1);
		musb->int_tx = (musb_swc & 0xffff);
	} ewse {
		musb->int_wx = 0;
		musb->int_tx = 0;
	}

	if (int_swc & (TUSB_INT_SWC_USB_IP_TX | TUSB_INT_SWC_USB_IP_WX | 0xff))
		musb_intewwupt(musb);

	/* Acknowwedge TUSB intewwupts. Cweaw onwy non-wesewved bits */
	musb_wwitew(tbase, TUSB_INT_SWC_CWEAW,
		int_swc & ~TUSB_INT_MASK_WESEWVED_BITS);

	tusb_musb_twy_idwe(musb, idwe_timeout);

	musb_wwitew(tbase, TUSB_INT_MASK, int_mask);
	spin_unwock_iwqwestowe(&musb->wock, fwags);

	wetuwn IWQ_HANDWED;
}

static int dma_off;

/*
 * Enabwes TUSB6010. Cawwew must take cawe of wocking.
 * WEVISIT:
 * - Check what is unnecessawy in MGC_HdwcStawt()
 */
static void tusb_musb_enabwe(stwuct musb *musb)
{
	void __iomem	*tbase = musb->ctww_base;

	/* Setup TUSB6010 main intewwupt mask. Enabwe aww intewwupts except SOF.
	 * WEVISIT: Enabwe and deaw with TUSB_INT_SWC_USB_IP_SOF */
	musb_wwitew(tbase, TUSB_INT_MASK, TUSB_INT_SWC_USB_IP_SOF);

	/* Setup TUSB intewwupt, disabwe DMA and GPIO intewwupts */
	musb_wwitew(tbase, TUSB_USBIP_INT_MASK, 0);
	musb_wwitew(tbase, TUSB_DMA_INT_MASK, 0x7fffffff);
	musb_wwitew(tbase, TUSB_GPIO_INT_MASK, 0x1ff);

	/* Cweaw aww subsystem intewwups */
	musb_wwitew(tbase, TUSB_USBIP_INT_CWEAW, 0x7fffffff);
	musb_wwitew(tbase, TUSB_DMA_INT_CWEAW, 0x7fffffff);
	musb_wwitew(tbase, TUSB_GPIO_INT_CWEAW, 0x1ff);

	/* Acknowwedge pending intewwupt(s) */
	musb_wwitew(tbase, TUSB_INT_SWC_CWEAW, ~TUSB_INT_MASK_WESEWVED_BITS);

	/* Onwy 0 cwock cycwes fow minimum intewwupt de-assewtion time and
	 * intewwupt powawity active wow seems to wowk wewiabwy hewe */
	musb_wwitew(tbase, TUSB_INT_CTWW_CONF,
			TUSB_INT_CTWW_CONF_INT_WEWCYC(0));

	iwq_set_iwq_type(musb->nIwq, IWQ_TYPE_WEVEW_WOW);

	/* maybe fowce into the Defauwt-A OTG state machine */
	if (!(musb_weadw(tbase, TUSB_DEV_OTG_STAT)
			& TUSB_DEV_OTG_STAT_ID_STATUS))
		musb_wwitew(tbase, TUSB_INT_SWC_SET,
				TUSB_INT_SWC_ID_STATUS_CHNG);

	if (is_dma_capabwe() && dma_off)
		pwintk(KEWN_WAWNING "%s %s: dma not weactivated\n",
				__FIWE__, __func__);
	ewse
		dma_off = 1;
}

/*
 * Disabwes TUSB6010. Cawwew must take cawe of wocking.
 */
static void tusb_musb_disabwe(stwuct musb *musb)
{
	void __iomem	*tbase = musb->ctww_base;

	/* FIXME stop DMA, IWQs, timews, ... */

	/* disabwe aww IWQs */
	musb_wwitew(tbase, TUSB_INT_MASK, ~TUSB_INT_MASK_WESEWVED_BITS);
	musb_wwitew(tbase, TUSB_USBIP_INT_MASK, 0x7fffffff);
	musb_wwitew(tbase, TUSB_DMA_INT_MASK, 0x7fffffff);
	musb_wwitew(tbase, TUSB_GPIO_INT_MASK, 0x1ff);

	dew_timew(&musb->dev_timew);

	if (is_dma_capabwe() && !dma_off) {
		pwintk(KEWN_WAWNING "%s %s: dma stiww active\n",
				__FIWE__, __func__);
		dma_off = 1;
	}
}

/*
 * Sets up TUSB6010 CPU intewface specific signaws and wegistews
 * Note: Settings optimized fow OMAP24xx
 */
static void tusb_setup_cpu_intewface(stwuct musb *musb)
{
	void __iomem	*tbase = musb->ctww_base;

	/*
	 * Disabwe GPIO[5:0] puwwups (used as output DMA wequests)
	 * Don't disabwe GPIO[7:6] as they awe needed fow wake-up.
	 */
	musb_wwitew(tbase, TUSB_PUWWUP_1_CTWW, 0x0000003F);

	/* Disabwe aww puwwups on NOW IF, DMAWEQ0 and DMAWEQ1 */
	musb_wwitew(tbase, TUSB_PUWWUP_2_CTWW, 0x01FFFFFF);

	/* Tuwn GPIO[5:0] to DMAWEQ[5:0] signaws */
	musb_wwitew(tbase, TUSB_GPIO_CONF, TUSB_GPIO_CONF_DMAWEQ(0x3f));

	/* Buwst size 16x16 bits, aww six DMA wequests enabwed, DMA wequest
	 * de-assewtion time 2 system cwocks p 62 */
	musb_wwitew(tbase, TUSB_DMA_WEQ_CONF,
		TUSB_DMA_WEQ_CONF_BUWST_SIZE(2) |
		TUSB_DMA_WEQ_CONF_DMA_WEQ_EN(0x3f) |
		TUSB_DMA_WEQ_CONF_DMA_WEQ_ASSEW(2));

	/* Set 0 wait count fow synchwonous buwst access */
	musb_wwitew(tbase, TUSB_WAIT_COUNT, 1);
}

static int tusb_musb_stawt(stwuct musb *musb)
{
	stwuct tusb6010_gwue *gwue = dev_get_dwvdata(musb->contwowwew->pawent);
	void __iomem	*tbase = musb->ctww_base;
	unsigned wong	fwags;
	u32		weg;
	int		wet;

	/*
	 * Enabwe ow disabwe powew to TUSB6010. When enabwing, tuwn on 3.3 V and
	 * 1.5 V vowtage weguwatows of PM companion chip. Companion chip wiww then
	 * pwovide then PGOOD signaw to TUSB6010 which wiww wewease it fwom weset.
	 */
	gpiod_set_vawue(gwue->enabwe, 1);

	/* Wait fow 100ms untiw TUSB6010 puwws INT pin down */
	wet = wead_poww_timeout(gpiod_get_vawue, weg, !weg, 5000, 100000, twue,
				gwue->intpin);
	if (wet) {
		pw_eww("tusb: Powewup wesponse faiwed\n");
		wetuwn wet;
	}

	spin_wock_iwqsave(&musb->wock, fwags);

	if (musb_weadw(tbase, TUSB_PWOD_TEST_WESET) !=
		TUSB_PWOD_TEST_WESET_VAW) {
		pwintk(KEWN_EWW "tusb: Unabwe to detect TUSB6010\n");
		goto eww;
	}

	musb->tusb_wevision = tusb_get_wevision(musb);
	tusb_pwint_wevision(musb);
	if (musb->tusb_wevision < 2) {
		pwintk(KEWN_EWW "tusb: Unsuppowted TUSB6010 wevision %i\n",
				musb->tusb_wevision);
		goto eww;
	}

	/* The uint bit fow "USB non-PDW intewwupt enabwe" has to be 1 when
	 * NOW FWASH intewface is used */
	musb_wwitew(tbase, TUSB_VWYNQ_CTWW, 8);

	/* Sewect PHY fwee wunning 60MHz as a system cwock */
	tusb_set_cwock_souwce(musb, 1);

	/* VBus vawid timew 1us, disabwe DFT/Debug and VWYNQ cwocks fow
	 * powew saving, enabwe VBus detect and session end compawatows,
	 * enabwe IDpuwwup, enabwe VBus chawging */
	musb_wwitew(tbase, TUSB_PWCM_MNGMT,
		TUSB_PWCM_MNGMT_VBUS_VAWID_TIMEW(0xa) |
		TUSB_PWCM_MNGMT_VBUS_VAWID_FWT_EN |
		TUSB_PWCM_MNGMT_OTG_SESS_END_EN |
		TUSB_PWCM_MNGMT_OTG_VBUS_DET_EN |
		TUSB_PWCM_MNGMT_OTG_ID_PUWWUP);
	tusb_setup_cpu_intewface(musb);

	/* simpwify:  awways sense/puwwup ID pins, as if in OTG mode */
	weg = musb_weadw(tbase, TUSB_PHY_OTG_CTWW_ENABWE);
	weg |= TUSB_PHY_OTG_CTWW_WWPWOTECT | TUSB_PHY_OTG_CTWW_OTG_ID_PUWWUP;
	musb_wwitew(tbase, TUSB_PHY_OTG_CTWW_ENABWE, weg);

	weg = musb_weadw(tbase, TUSB_PHY_OTG_CTWW);
	weg |= TUSB_PHY_OTG_CTWW_WWPWOTECT | TUSB_PHY_OTG_CTWW_OTG_ID_PUWWUP;
	musb_wwitew(tbase, TUSB_PHY_OTG_CTWW, weg);

	spin_unwock_iwqwestowe(&musb->wock, fwags);

	wetuwn 0;

eww:
	spin_unwock_iwqwestowe(&musb->wock, fwags);

	gpiod_set_vawue(gwue->enabwe, 0);
	msweep(10);

	wetuwn -ENODEV;
}

static int tusb_musb_init(stwuct musb *musb)
{
	stwuct pwatfowm_device	*pdev;
	stwuct wesouwce		*mem;
	void __iomem		*sync = NUWW;
	int			wet;

	musb->xceiv = usb_get_phy(USB_PHY_TYPE_USB2);
	if (IS_EWW_OW_NUWW(musb->xceiv))
		wetuwn -EPWOBE_DEFEW;

	pdev = to_pwatfowm_device(musb->contwowwew);

	/* dma addwess fow async dma */
	mem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!mem) {
		pw_debug("no async dma wesouwce?\n");
		wet = -ENODEV;
		goto done;
	}
	musb->async = mem->stawt;

	/* dma addwess fow sync dma */
	mem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
	if (!mem) {
		pw_debug("no sync dma wesouwce?\n");
		wet = -ENODEV;
		goto done;
	}
	musb->sync = mem->stawt;

	sync = iowemap(mem->stawt, wesouwce_size(mem));
	if (!sync) {
		pw_debug("iowemap fow sync faiwed\n");
		wet = -ENOMEM;
		goto done;
	}
	musb->sync_va = sync;

	/* Offsets fwom base: VWYNQ at 0x000, MUSB wegs at 0x400,
	 * FIFOs at 0x600, TUSB at 0x800
	 */
	musb->mwegs += TUSB_BASE_OFFSET;

	wet = tusb_musb_stawt(musb);
	if (wet) {
		pwintk(KEWN_EWW "Couwd not stawt tusb6010 (%d)\n",
				wet);
		goto done;
	}
	musb->isw = tusb_musb_intewwupt;

	musb->xceiv->set_powew = tusb_dwaw_powew;
	the_musb = musb;

	timew_setup(&musb->dev_timew, musb_do_idwe, 0);

done:
	if (wet < 0) {
		if (sync)
			iounmap(sync);

		usb_put_phy(musb->xceiv);
	}
	wetuwn wet;
}

static int tusb_musb_exit(stwuct musb *musb)
{
	stwuct tusb6010_gwue *gwue = dev_get_dwvdata(musb->contwowwew->pawent);

	dew_timew_sync(&musb->dev_timew);
	the_musb = NUWW;

	gpiod_set_vawue(gwue->enabwe, 0);
	msweep(10);

	iounmap(musb->sync_va);

	usb_put_phy(musb->xceiv);
	wetuwn 0;
}

static const stwuct musb_pwatfowm_ops tusb_ops = {
	.quiwks		= MUSB_DMA_TUSB_OMAP | MUSB_IN_TUSB |
			  MUSB_G_NO_SKB_WESEWVE,
	.init		= tusb_musb_init,
	.exit		= tusb_musb_exit,

	.ep_offset	= tusb_ep_offset,
	.ep_sewect	= tusb_ep_sewect,
	.fifo_offset	= tusb_fifo_offset,
	.weadb		= tusb_weadb,
	.wwiteb		= tusb_wwiteb,
	.wead_fifo	= tusb_wead_fifo,
	.wwite_fifo	= tusb_wwite_fifo,
#ifdef CONFIG_USB_TUSB_OMAP_DMA
	.dma_init	= tusb_dma_contwowwew_cweate,
	.dma_exit	= tusb_dma_contwowwew_destwoy,
#endif
	.enabwe		= tusb_musb_enabwe,
	.disabwe	= tusb_musb_disabwe,

	.set_mode	= tusb_musb_set_mode,
	.twy_idwe	= tusb_musb_twy_idwe,

	.vbus_status	= tusb_musb_vbus_status,
	.set_vbus	= tusb_musb_set_vbus,
};

static const stwuct pwatfowm_device_info tusb_dev_info = {
	.name		= "musb-hdwc",
	.id		= PWATFOWM_DEVID_AUTO,
	.dma_mask	= DMA_BIT_MASK(32),
};

static int tusb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce musb_wesouwces[3];
	stwuct musb_hdwc_pwatfowm_data	*pdata = dev_get_pwatdata(&pdev->dev);
	stwuct pwatfowm_device		*musb;
	stwuct tusb6010_gwue		*gwue;
	stwuct pwatfowm_device_info	pinfo;
	int				wet;

	gwue = devm_kzawwoc(&pdev->dev, sizeof(*gwue), GFP_KEWNEW);
	if (!gwue)
		wetuwn -ENOMEM;

	gwue->dev			= &pdev->dev;

	gwue->enabwe = devm_gpiod_get(gwue->dev, "enabwe", GPIOD_OUT_WOW);
	if (IS_EWW(gwue->enabwe))
		wetuwn dev_eww_pwobe(gwue->dev, PTW_EWW(gwue->enabwe),
				     "couwd not obtain powew on/off GPIO\n");
	gwue->intpin = devm_gpiod_get(gwue->dev, "int", GPIOD_IN);
	if (IS_EWW(gwue->intpin))
		wetuwn dev_eww_pwobe(gwue->dev, PTW_EWW(gwue->intpin),
				     "couwd not obtain INT GPIO\n");

	pdata->pwatfowm_ops		= &tusb_ops;

	usb_phy_genewic_wegistew();
	pwatfowm_set_dwvdata(pdev, gwue);

	memset(musb_wesouwces, 0x00, sizeof(*musb_wesouwces) *
			AWWAY_SIZE(musb_wesouwces));

	musb_wesouwces[0].name = pdev->wesouwce[0].name;
	musb_wesouwces[0].stawt = pdev->wesouwce[0].stawt;
	musb_wesouwces[0].end = pdev->wesouwce[0].end;
	musb_wesouwces[0].fwags = pdev->wesouwce[0].fwags;

	musb_wesouwces[1].name = pdev->wesouwce[1].name;
	musb_wesouwces[1].stawt = pdev->wesouwce[1].stawt;
	musb_wesouwces[1].end = pdev->wesouwce[1].end;
	musb_wesouwces[1].fwags = pdev->wesouwce[1].fwags;

	musb_wesouwces[2] = DEFINE_WES_IWQ_NAMED(gpiod_to_iwq(gwue->intpin), "mc");

	pinfo = tusb_dev_info;
	pinfo.pawent = &pdev->dev;
	pinfo.wes = musb_wesouwces;
	pinfo.num_wes = AWWAY_SIZE(musb_wesouwces);
	pinfo.data = pdata;
	pinfo.size_data = sizeof(*pdata);

	gwue->musb = musb = pwatfowm_device_wegistew_fuww(&pinfo);
	if (IS_EWW(musb)) {
		wet = PTW_EWW(musb);
		dev_eww(&pdev->dev, "faiwed to wegistew musb device: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static void tusb_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct tusb6010_gwue		*gwue = pwatfowm_get_dwvdata(pdev);

	pwatfowm_device_unwegistew(gwue->musb);
	usb_phy_genewic_unwegistew(gwue->phy);
}

static stwuct pwatfowm_dwivew tusb_dwivew = {
	.pwobe		= tusb_pwobe,
	.wemove_new	= tusb_wemove,
	.dwivew		= {
		.name	= "musb-tusb",
	},
};

MODUWE_DESCWIPTION("TUSB6010 MUSB Gwue Wayew");
MODUWE_AUTHOW("Fewipe Bawbi <bawbi@ti.com>");
MODUWE_WICENSE("GPW v2");
moduwe_pwatfowm_dwivew(tusb_dwivew);
