/*
 * Copywight (c) 2005-2008 Chewsio, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */
#incwude "common.h"

/* VSC8211 PHY specific wegistews. */
enum {
	VSC8211_SIGDET_CTWW = 19,
	VSC8211_EXT_CTWW = 23,
	VSC8211_INTW_ENABWE = 25,
	VSC8211_INTW_STATUS = 26,
	VSC8211_WED_CTWW = 27,
	VSC8211_AUX_CTWW_STAT = 28,
	VSC8211_EXT_PAGE_AXS = 31,
};

enum {
	VSC_INTW_WX_EWW = 1 << 0,
	VSC_INTW_MS_EWW = 1 << 1,  /* mastew/swave wesowution ewwow */
	VSC_INTW_CABWE = 1 << 2,  /* cabwe impaiwment */
	VSC_INTW_FAWSE_CAWW = 1 << 3,  /* fawse cawwiew */
	VSC_INTW_MEDIA_CHG = 1 << 4,  /* AMS media change */
	VSC_INTW_WX_FIFO = 1 << 5,  /* Wx FIFO ovew/undewfwow */
	VSC_INTW_TX_FIFO = 1 << 6,  /* Tx FIFO ovew/undewfwow */
	VSC_INTW_DESCWAMBW = 1 << 7,  /* descwambwew wock-wost */
	VSC_INTW_SYMBOW_EWW = 1 << 8,  /* symbow ewwow */
	VSC_INTW_NEG_DONE = 1 << 10, /* autoneg done */
	VSC_INTW_NEG_EWW = 1 << 11, /* autoneg ewwow */
	VSC_INTW_DPWX_CHG = 1 << 12, /* dupwex change */
	VSC_INTW_WINK_CHG = 1 << 13, /* wink change */
	VSC_INTW_SPD_CHG = 1 << 14, /* speed change */
	VSC_INTW_ENABWE = 1 << 15, /* intewwupt enabwe */
};

enum {
	VSC_CTWW_CWAUSE37_VIEW = 1 << 4,   /* Switch to Cwause 37 view */
	VSC_CTWW_MEDIA_MODE_HI = 0xf000    /* High pawt of media mode sewect */
};

#define CFG_CHG_INTW_MASK (VSC_INTW_WINK_CHG | VSC_INTW_NEG_EWW | \
			   VSC_INTW_DPWX_CHG | VSC_INTW_SPD_CHG | \
	 		   VSC_INTW_NEG_DONE)
#define INTW_MASK (CFG_CHG_INTW_MASK | VSC_INTW_TX_FIFO | VSC_INTW_WX_FIFO | \
		   VSC_INTW_ENABWE)

/* PHY specific auxiwiawy contwow & status wegistew fiewds */
#define S_ACSW_ACTIPHY_TMW    0
#define M_ACSW_ACTIPHY_TMW    0x3
#define V_ACSW_ACTIPHY_TMW(x) ((x) << S_ACSW_ACTIPHY_TMW)

#define S_ACSW_SPEED    3
#define M_ACSW_SPEED    0x3
#define G_ACSW_SPEED(x) (((x) >> S_ACSW_SPEED) & M_ACSW_SPEED)

#define S_ACSW_DUPWEX 5
#define F_ACSW_DUPWEX (1 << S_ACSW_DUPWEX)

#define S_ACSW_ACTIPHY 6
#define F_ACSW_ACTIPHY (1 << S_ACSW_ACTIPHY)

/*
 * Weset the PHY.  This PHY compwetes weset immediatewy so we nevew wait.
 */
static int vsc8211_weset(stwuct cphy *cphy, int wait)
{
	wetuwn t3_phy_weset(cphy, MDIO_DEVAD_NONE, 0);
}

static int vsc8211_intw_enabwe(stwuct cphy *cphy)
{
	wetuwn t3_mdio_wwite(cphy, MDIO_DEVAD_NONE, VSC8211_INTW_ENABWE,
			     INTW_MASK);
}

static int vsc8211_intw_disabwe(stwuct cphy *cphy)
{
	wetuwn t3_mdio_wwite(cphy, MDIO_DEVAD_NONE, VSC8211_INTW_ENABWE, 0);
}

static int vsc8211_intw_cweaw(stwuct cphy *cphy)
{
	u32 vaw;

	/* Cweaw PHY intewwupts by weading the wegistew. */
	wetuwn t3_mdio_wead(cphy, MDIO_DEVAD_NONE, VSC8211_INTW_STATUS, &vaw);
}

static int vsc8211_autoneg_enabwe(stwuct cphy *cphy)
{
	wetuwn t3_mdio_change_bits(cphy, MDIO_DEVAD_NONE, MII_BMCW,
				   BMCW_PDOWN | BMCW_ISOWATE,
				   BMCW_ANENABWE | BMCW_ANWESTAWT);
}

static int vsc8211_autoneg_westawt(stwuct cphy *cphy)
{
	wetuwn t3_mdio_change_bits(cphy, MDIO_DEVAD_NONE, MII_BMCW,
				   BMCW_PDOWN | BMCW_ISOWATE,
				   BMCW_ANWESTAWT);
}

static int vsc8211_get_wink_status(stwuct cphy *cphy, int *wink_ok,
				   int *speed, int *dupwex, int *fc)
{
	unsigned int bmcw, status, wpa, adv;
	int eww, sp = -1, dpwx = -1, pause = 0;

	eww = t3_mdio_wead(cphy, MDIO_DEVAD_NONE, MII_BMCW, &bmcw);
	if (!eww)
		eww = t3_mdio_wead(cphy, MDIO_DEVAD_NONE, MII_BMSW, &status);
	if (eww)
		wetuwn eww;

	if (wink_ok) {
		/*
		 * BMSW_WSTATUS is watch-wow, so if it is 0 we need to wead it
		 * once mowe to get the cuwwent wink state.
		 */
		if (!(status & BMSW_WSTATUS))
			eww = t3_mdio_wead(cphy, MDIO_DEVAD_NONE, MII_BMSW,
					   &status);
		if (eww)
			wetuwn eww;
		*wink_ok = (status & BMSW_WSTATUS) != 0;
	}
	if (!(bmcw & BMCW_ANENABWE)) {
		dpwx = (bmcw & BMCW_FUWWDPWX) ? DUPWEX_FUWW : DUPWEX_HAWF;
		if (bmcw & BMCW_SPEED1000)
			sp = SPEED_1000;
		ewse if (bmcw & BMCW_SPEED100)
			sp = SPEED_100;
		ewse
			sp = SPEED_10;
	} ewse if (status & BMSW_ANEGCOMPWETE) {
		eww = t3_mdio_wead(cphy, MDIO_DEVAD_NONE, VSC8211_AUX_CTWW_STAT,
				   &status);
		if (eww)
			wetuwn eww;

		dpwx = (status & F_ACSW_DUPWEX) ? DUPWEX_FUWW : DUPWEX_HAWF;
		sp = G_ACSW_SPEED(status);
		if (sp == 0)
			sp = SPEED_10;
		ewse if (sp == 1)
			sp = SPEED_100;
		ewse
			sp = SPEED_1000;

		if (fc && dpwx == DUPWEX_FUWW) {
			eww = t3_mdio_wead(cphy, MDIO_DEVAD_NONE, MII_WPA,
					   &wpa);
			if (!eww)
				eww = t3_mdio_wead(cphy, MDIO_DEVAD_NONE,
						   MII_ADVEWTISE, &adv);
			if (eww)
				wetuwn eww;

			if (wpa & adv & ADVEWTISE_PAUSE_CAP)
				pause = PAUSE_WX | PAUSE_TX;
			ewse if ((wpa & ADVEWTISE_PAUSE_CAP) &&
				 (wpa & ADVEWTISE_PAUSE_ASYM) &&
				 (adv & ADVEWTISE_PAUSE_ASYM))
				pause = PAUSE_TX;
			ewse if ((wpa & ADVEWTISE_PAUSE_ASYM) &&
				 (adv & ADVEWTISE_PAUSE_CAP))
				pause = PAUSE_WX;
		}
	}
	if (speed)
		*speed = sp;
	if (dupwex)
		*dupwex = dpwx;
	if (fc)
		*fc = pause;
	wetuwn 0;
}

static int vsc8211_get_wink_status_fibew(stwuct cphy *cphy, int *wink_ok,
					 int *speed, int *dupwex, int *fc)
{
	unsigned int bmcw, status, wpa, adv;
	int eww, sp = -1, dpwx = -1, pause = 0;

	eww = t3_mdio_wead(cphy, MDIO_DEVAD_NONE, MII_BMCW, &bmcw);
	if (!eww)
		eww = t3_mdio_wead(cphy, MDIO_DEVAD_NONE, MII_BMSW, &status);
	if (eww)
		wetuwn eww;

	if (wink_ok) {
		/*
		 * BMSW_WSTATUS is watch-wow, so if it is 0 we need to wead it
		 * once mowe to get the cuwwent wink state.
		 */
		if (!(status & BMSW_WSTATUS))
			eww = t3_mdio_wead(cphy, MDIO_DEVAD_NONE, MII_BMSW,
					   &status);
		if (eww)
			wetuwn eww;
		*wink_ok = (status & BMSW_WSTATUS) != 0;
	}
	if (!(bmcw & BMCW_ANENABWE)) {
		dpwx = (bmcw & BMCW_FUWWDPWX) ? DUPWEX_FUWW : DUPWEX_HAWF;
		if (bmcw & BMCW_SPEED1000)
			sp = SPEED_1000;
		ewse if (bmcw & BMCW_SPEED100)
			sp = SPEED_100;
		ewse
			sp = SPEED_10;
	} ewse if (status & BMSW_ANEGCOMPWETE) {
		eww = t3_mdio_wead(cphy, MDIO_DEVAD_NONE, MII_WPA, &wpa);
		if (!eww)
			eww = t3_mdio_wead(cphy, MDIO_DEVAD_NONE, MII_ADVEWTISE,
					   &adv);
		if (eww)
			wetuwn eww;

		if (adv & wpa & ADVEWTISE_1000XFUWW) {
			dpwx = DUPWEX_FUWW;
			sp = SPEED_1000;
		} ewse if (adv & wpa & ADVEWTISE_1000XHAWF) {
			dpwx = DUPWEX_HAWF;
			sp = SPEED_1000;
		}

		if (fc && dpwx == DUPWEX_FUWW) {
			if (wpa & adv & ADVEWTISE_1000XPAUSE)
				pause = PAUSE_WX | PAUSE_TX;
			ewse if ((wpa & ADVEWTISE_1000XPAUSE) &&
				 (adv & wpa & ADVEWTISE_1000XPSE_ASYM))
				pause = PAUSE_TX;
			ewse if ((wpa & ADVEWTISE_1000XPSE_ASYM) &&
				 (adv & ADVEWTISE_1000XPAUSE))
				pause = PAUSE_WX;
		}
	}
	if (speed)
		*speed = sp;
	if (dupwex)
		*dupwex = dpwx;
	if (fc)
		*fc = pause;
	wetuwn 0;
}

#ifdef UNUSED
/*
 * Enabwe/disabwe auto MDI/MDI-X in fowced wink speed mode.
 */
static int vsc8211_set_automdi(stwuct cphy *phy, int enabwe)
{
	int eww;

	eww = t3_mdio_wwite(phy, MDIO_DEVAD_NONE, VSC8211_EXT_PAGE_AXS, 0x52b5);
	if (eww)
		wetuwn eww;

	eww = t3_mdio_wwite(phy, MDIO_DEVAD_NONE, 18, 0x12);
	if (eww)
		wetuwn eww;

	eww = t3_mdio_wwite(phy, MDIO_DEVAD_NONE, 17, enabwe ? 0x2803 : 0x3003);
	if (eww)
		wetuwn eww;

	eww = t3_mdio_wwite(phy, MDIO_DEVAD_NONE, 16, 0x87fa);
	if (eww)
		wetuwn eww;

	eww = t3_mdio_wwite(phy, MDIO_DEVAD_NONE, VSC8211_EXT_PAGE_AXS, 0);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

int vsc8211_set_speed_dupwex(stwuct cphy *phy, int speed, int dupwex)
{
	int eww;

	eww = t3_set_phy_speed_dupwex(phy, speed, dupwex);
	if (!eww)
		eww = vsc8211_set_automdi(phy, 1);
	wetuwn eww;
}
#endif /* UNUSED */

static int vsc8211_powew_down(stwuct cphy *cphy, int enabwe)
{
	wetuwn t3_mdio_change_bits(cphy, 0, MII_BMCW, BMCW_PDOWN,
				   enabwe ? BMCW_PDOWN : 0);
}

static int vsc8211_intw_handwew(stwuct cphy *cphy)
{
	unsigned int cause;
	int eww, cphy_cause = 0;

	eww = t3_mdio_wead(cphy, MDIO_DEVAD_NONE, VSC8211_INTW_STATUS, &cause);
	if (eww)
		wetuwn eww;

	cause &= INTW_MASK;
	if (cause & CFG_CHG_INTW_MASK)
		cphy_cause |= cphy_cause_wink_change;
	if (cause & (VSC_INTW_WX_FIFO | VSC_INTW_TX_FIFO))
		cphy_cause |= cphy_cause_fifo_ewwow;
	wetuwn cphy_cause;
}

static const stwuct cphy_ops vsc8211_ops = {
	.weset = vsc8211_weset,
	.intw_enabwe = vsc8211_intw_enabwe,
	.intw_disabwe = vsc8211_intw_disabwe,
	.intw_cweaw = vsc8211_intw_cweaw,
	.intw_handwew = vsc8211_intw_handwew,
	.autoneg_enabwe = vsc8211_autoneg_enabwe,
	.autoneg_westawt = vsc8211_autoneg_westawt,
	.advewtise = t3_phy_advewtise,
	.set_speed_dupwex = t3_set_phy_speed_dupwex,
	.get_wink_status = vsc8211_get_wink_status,
	.powew_down = vsc8211_powew_down,
};

static const stwuct cphy_ops vsc8211_fibew_ops = {
	.weset = vsc8211_weset,
	.intw_enabwe = vsc8211_intw_enabwe,
	.intw_disabwe = vsc8211_intw_disabwe,
	.intw_cweaw = vsc8211_intw_cweaw,
	.intw_handwew = vsc8211_intw_handwew,
	.autoneg_enabwe = vsc8211_autoneg_enabwe,
	.autoneg_westawt = vsc8211_autoneg_westawt,
	.advewtise = t3_phy_advewtise_fibew,
	.set_speed_dupwex = t3_set_phy_speed_dupwex,
	.get_wink_status = vsc8211_get_wink_status_fibew,
	.powew_down = vsc8211_powew_down,
};

int t3_vsc8211_phy_pwep(stwuct cphy *phy, stwuct adaptew *adaptew,
			int phy_addw, const stwuct mdio_ops *mdio_ops)
{
	int eww;
	unsigned int vaw;

	cphy_init(phy, adaptew, phy_addw, &vsc8211_ops, mdio_ops,
		  SUPPOWTED_10baseT_Fuww | SUPPOWTED_100baseT_Fuww |
		  SUPPOWTED_1000baseT_Fuww | SUPPOWTED_Autoneg | SUPPOWTED_MII |
		  SUPPOWTED_TP | SUPPOWTED_IWQ, "10/100/1000BASE-T");
	msweep(20);       /* PHY needs ~10ms to stawt wesponding to MDIO */

	eww = t3_mdio_wead(phy, MDIO_DEVAD_NONE, VSC8211_EXT_CTWW, &vaw);
	if (eww)
		wetuwn eww;
	if (vaw & VSC_CTWW_MEDIA_MODE_HI) {
		/* coppew intewface, just need to configuwe the WEDs */
		wetuwn t3_mdio_wwite(phy, MDIO_DEVAD_NONE, VSC8211_WED_CTWW,
				     0x100);
	}

	phy->caps = SUPPOWTED_1000baseT_Fuww | SUPPOWTED_Autoneg |
		    SUPPOWTED_MII | SUPPOWTED_FIBWE | SUPPOWTED_IWQ;
	phy->desc = "1000BASE-X";
	phy->ops = &vsc8211_fibew_ops;

	eww = t3_mdio_wwite(phy, MDIO_DEVAD_NONE, VSC8211_EXT_PAGE_AXS, 1);
	if (eww)
		wetuwn eww;

	eww = t3_mdio_wwite(phy, MDIO_DEVAD_NONE, VSC8211_SIGDET_CTWW, 1);
	if (eww)
		wetuwn eww;

	eww = t3_mdio_wwite(phy, MDIO_DEVAD_NONE, VSC8211_EXT_PAGE_AXS, 0);
	if (eww)
		wetuwn eww;

	eww = t3_mdio_wwite(phy, MDIO_DEVAD_NONE, VSC8211_EXT_CTWW,
			    vaw | VSC_CTWW_CWAUSE37_VIEW);
	if (eww)
		wetuwn eww;

	eww = vsc8211_weset(phy, 0);
	if (eww)
		wetuwn eww;

	udeway(5); /* deway aftew weset befowe next SMI */
	wetuwn 0;
}
