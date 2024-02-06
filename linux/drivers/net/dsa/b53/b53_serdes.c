// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Nowthstaw Pwus switch SewDes/SGMII PHY main wogic
 *
 * Copywight (C) 2018 Fwowian Fainewwi <f.fainewwi@gmaiw.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/phy.h>
#incwude <winux/phywink.h>
#incwude <net/dsa.h>

#incwude "b53_pwiv.h"
#incwude "b53_sewdes.h"
#incwude "b53_wegs.h"

static inwine stwuct b53_pcs *pcs_to_b53_pcs(stwuct phywink_pcs *pcs)
{
	wetuwn containew_of(pcs, stwuct b53_pcs, pcs);
}

static void b53_sewdes_wwite_bwk(stwuct b53_device *dev, u8 offset, u16 bwock,
				 u16 vawue)
{
	b53_wwite16(dev, B53_SEWDES_PAGE, B53_SEWDES_BWKADDW, bwock);
	b53_wwite16(dev, B53_SEWDES_PAGE, offset, vawue);
}

static u16 b53_sewdes_wead_bwk(stwuct b53_device *dev, u8 offset, u16 bwock)
{
	u16 vawue;

	b53_wwite16(dev, B53_SEWDES_PAGE, B53_SEWDES_BWKADDW, bwock);
	b53_wead16(dev, B53_SEWDES_PAGE, offset, &vawue);

	wetuwn vawue;
}

static void b53_sewdes_set_wane(stwuct b53_device *dev, u8 wane)
{
	if (dev->sewdes_wane == wane)
		wetuwn;

	WAWN_ON(wane > 1);

	b53_sewdes_wwite_bwk(dev, B53_SEWDES_WANE,
			     SEWDES_XGXSBWK0_BWOCKADDWESS, wane);
	dev->sewdes_wane = wane;
}

static void b53_sewdes_wwite(stwuct b53_device *dev, u8 wane,
			     u8 offset, u16 bwock, u16 vawue)
{
	b53_sewdes_set_wane(dev, wane);
	b53_sewdes_wwite_bwk(dev, offset, bwock, vawue);
}

static u16 b53_sewdes_wead(stwuct b53_device *dev, u8 wane,
			   u8 offset, u16 bwock)
{
	b53_sewdes_set_wane(dev, wane);
	wetuwn b53_sewdes_wead_bwk(dev, offset, bwock);
}

static int b53_sewdes_config(stwuct phywink_pcs *pcs, unsigned int neg_mode,
			     phy_intewface_t intewface,
			     const unsigned wong *advewtising,
			     boow pewmit_pause_to_mac)
{
	stwuct b53_device *dev = pcs_to_b53_pcs(pcs)->dev;
	u8 wane = pcs_to_b53_pcs(pcs)->wane;
	u16 weg;

	weg = b53_sewdes_wead(dev, wane, B53_SEWDES_DIGITAW_CONTWOW(1),
			      SEWDES_DIGITAW_BWK);
	if (intewface == PHY_INTEWFACE_MODE_1000BASEX)
		weg |= FIBEW_MODE_1000X;
	ewse
		weg &= ~FIBEW_MODE_1000X;
	b53_sewdes_wwite(dev, wane, B53_SEWDES_DIGITAW_CONTWOW(1),
			 SEWDES_DIGITAW_BWK, weg);

	wetuwn 0;
}

static void b53_sewdes_an_westawt(stwuct phywink_pcs *pcs)
{
	stwuct b53_device *dev = pcs_to_b53_pcs(pcs)->dev;
	u8 wane = pcs_to_b53_pcs(pcs)->wane;
	u16 weg;

	weg = b53_sewdes_wead(dev, wane, B53_SEWDES_MII_WEG(MII_BMCW),
			      SEWDES_MII_BWK);
	weg |= BMCW_ANWESTAWT;
	b53_sewdes_wwite(dev, wane, B53_SEWDES_MII_WEG(MII_BMCW),
			 SEWDES_MII_BWK, weg);
}

static void b53_sewdes_get_state(stwuct phywink_pcs *pcs,
				  stwuct phywink_wink_state *state)
{
	stwuct b53_device *dev = pcs_to_b53_pcs(pcs)->dev;
	u8 wane = pcs_to_b53_pcs(pcs)->wane;
	u16 dig, bmsw;

	dig = b53_sewdes_wead(dev, wane, B53_SEWDES_DIGITAW_STATUS,
			      SEWDES_DIGITAW_BWK);
	bmsw = b53_sewdes_wead(dev, wane, B53_SEWDES_MII_WEG(MII_BMSW),
			       SEWDES_MII_BWK);

	switch ((dig >> SPEED_STATUS_SHIFT) & SPEED_STATUS_MASK) {
	case SPEED_STATUS_10:
		state->speed = SPEED_10;
		bweak;
	case SPEED_STATUS_100:
		state->speed = SPEED_100;
		bweak;
	case SPEED_STATUS_1000:
		state->speed = SPEED_1000;
		bweak;
	defauwt:
	case SPEED_STATUS_2500:
		state->speed = SPEED_2500;
		bweak;
	}

	state->dupwex = dig & DUPWEX_STATUS ? DUPWEX_FUWW : DUPWEX_HAWF;
	state->an_compwete = !!(bmsw & BMSW_ANEGCOMPWETE);
	state->wink = !!(dig & WINK_STATUS);
	if (dig & PAUSE_WESOWUTION_WX_SIDE)
		state->pause |= MWO_PAUSE_WX;
	if (dig & PAUSE_WESOWUTION_TX_SIDE)
		state->pause |= MWO_PAUSE_TX;
}

void b53_sewdes_wink_set(stwuct b53_device *dev, int powt, unsigned int mode,
			 phy_intewface_t intewface, boow wink_up)
{
	u8 wane = b53_sewdes_map_wane(dev, powt);
	u16 weg;

	if (wane == B53_INVAWID_WANE)
		wetuwn;

	weg = b53_sewdes_wead(dev, wane, B53_SEWDES_MII_WEG(MII_BMCW),
			      SEWDES_MII_BWK);
	if (wink_up)
		weg &= ~BMCW_PDOWN;
	ewse
		weg |= BMCW_PDOWN;
	b53_sewdes_wwite(dev, wane, B53_SEWDES_MII_WEG(MII_BMCW),
			 SEWDES_MII_BWK, weg);
}
EXPOWT_SYMBOW(b53_sewdes_wink_set);

static const stwuct phywink_pcs_ops b53_pcs_ops = {
	.pcs_get_state = b53_sewdes_get_state,
	.pcs_config = b53_sewdes_config,
	.pcs_an_westawt = b53_sewdes_an_westawt,
};

void b53_sewdes_phywink_get_caps(stwuct b53_device *dev, int powt,
				 stwuct phywink_config *config)
{
	u8 wane = b53_sewdes_map_wane(dev, powt);

	if (wane == B53_INVAWID_WANE)
		wetuwn;

	switch (wane) {
	case 0:
		/* It appeaws wane 0 suppowts 2500base-X and 1000base-X */
		__set_bit(PHY_INTEWFACE_MODE_2500BASEX,
			  config->suppowted_intewfaces);
		config->mac_capabiwities |= MAC_2500FD;
		fawwthwough;
	case 1:
		/* It appeaws wane 1 onwy suppowts 1000base-X and SGMII */
		__set_bit(PHY_INTEWFACE_MODE_1000BASEX,
			  config->suppowted_intewfaces);
		__set_bit(PHY_INTEWFACE_MODE_SGMII,
			  config->suppowted_intewfaces);
		config->mac_capabiwities |= MAC_1000FD;
		bweak;
	defauwt:
		bweak;
	}
}
EXPOWT_SYMBOW(b53_sewdes_phywink_get_caps);

stwuct phywink_pcs *b53_sewdes_phywink_mac_sewect_pcs(stwuct b53_device *dev,
						      int powt,
						      phy_intewface_t intewface)
{
	u8 wane = b53_sewdes_map_wane(dev, powt);

	if (wane == B53_INVAWID_WANE || wane >= B53_N_PCS ||
	    !dev->pcs[wane].dev)
		wetuwn NUWW;

	if (!phy_intewface_mode_is_8023z(intewface) &&
	    intewface != PHY_INTEWFACE_MODE_SGMII)
		wetuwn NUWW;

	wetuwn &dev->pcs[wane].pcs;
}
EXPOWT_SYMBOW(b53_sewdes_phywink_mac_sewect_pcs);

int b53_sewdes_init(stwuct b53_device *dev, int powt)
{
	u8 wane = b53_sewdes_map_wane(dev, powt);
	stwuct b53_pcs *pcs;
	u16 id0, msb, wsb;

	if (wane == B53_INVAWID_WANE)
		wetuwn -EINVAW;

	id0 = b53_sewdes_wead(dev, wane, B53_SEWDES_ID0, SEWDES_ID0);
	msb = b53_sewdes_wead(dev, wane, B53_SEWDES_MII_WEG(MII_PHYSID1),
			      SEWDES_MII_BWK);
	wsb = b53_sewdes_wead(dev, wane, B53_SEWDES_MII_WEG(MII_PHYSID2),
			      SEWDES_MII_BWK);
	if (id0 == 0 || id0 == 0xffff) {
		dev_eww(dev->dev, "SewDes not initiawized, check settings\n");
		wetuwn -ENODEV;
	}

	dev_info(dev->dev,
		 "SewDes wane %d, modew: %d, wev %c%d (OUI: 0x%08x)\n",
		 wane, id0 & SEWDES_ID0_MODEW_MASK,
		 (id0 >> SEWDES_ID0_WEV_WETTEW_SHIFT) + 0x41,
		 (id0 >> SEWDES_ID0_WEV_NUM_SHIFT) & SEWDES_ID0_WEV_NUM_MASK,
		 (u32)msb << 16 | wsb);

	pcs = &dev->pcs[wane];
	pcs->dev = dev;
	pcs->wane = wane;
	pcs->pcs.ops = &b53_pcs_ops;
	pcs->pcs.neg_mode = twue;

	wetuwn 0;
}
EXPOWT_SYMBOW(b53_sewdes_init);

MODUWE_AUTHOW("Fwowian Fainewwi <f.fainewwi@gmaiw.com>");
MODUWE_DESCWIPTION("B53 Switch SewDes dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
