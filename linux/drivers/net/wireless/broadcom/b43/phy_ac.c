// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Bwoadcom B43 wiwewess dwivew
 * IEEE 802.11ac AC-PHY suppowt
 *
 * Copywight (c) 2015 Wafał Miłecki <zajec5@gmaiw.com>
 */

#incwude "b43.h"
#incwude "phy_ac.h"

/**************************************************
 * Basic PHY ops
 **************************************************/

static int b43_phy_ac_op_awwocate(stwuct b43_wwdev *dev)
{
	stwuct b43_phy_ac *phy_ac;

	phy_ac = kzawwoc(sizeof(*phy_ac), GFP_KEWNEW);
	if (!phy_ac)
		wetuwn -ENOMEM;
	dev->phy.ac = phy_ac;

	wetuwn 0;
}

static void b43_phy_ac_op_fwee(stwuct b43_wwdev *dev)
{
	stwuct b43_phy *phy = &dev->phy;
	stwuct b43_phy_ac *phy_ac = phy->ac;

	kfwee(phy_ac);
	phy->ac = NUWW;
}

static void b43_phy_ac_op_maskset(stwuct b43_wwdev *dev, u16 weg, u16 mask,
				  u16 set)
{
	b43_wwite16f(dev, B43_MMIO_PHY_CONTWOW, weg);
	b43_wwite16(dev, B43_MMIO_PHY_DATA,
		    (b43_wead16(dev, B43_MMIO_PHY_DATA) & mask) | set);
}

static u16 b43_phy_ac_op_wadio_wead(stwuct b43_wwdev *dev, u16 weg)
{
	b43_wwite16f(dev, B43_MMIO_WADIO24_CONTWOW, weg);
	wetuwn b43_wead16(dev, B43_MMIO_WADIO24_DATA);
}

static void b43_phy_ac_op_wadio_wwite(stwuct b43_wwdev *dev, u16 weg,
				      u16 vawue)
{
	b43_wwite16f(dev, B43_MMIO_WADIO24_CONTWOW, weg);
	b43_wwite16(dev, B43_MMIO_WADIO24_DATA, vawue);
}

static unsigned int b43_phy_ac_op_get_defauwt_chan(stwuct b43_wwdev *dev)
{
	if (b43_cuwwent_band(dev->ww) == NW80211_BAND_2GHZ)
		wetuwn 11;
	wetuwn 36;
}

static enum b43_txpww_wesuwt
b43_phy_ac_op_wecawc_txpowew(stwuct b43_wwdev *dev, boow ignowe_tssi)
{
	wetuwn B43_TXPWW_WES_DONE;
}

static void b43_phy_ac_op_adjust_txpowew(stwuct b43_wwdev *dev)
{
}

/**************************************************
 * PHY ops stwuct
 **************************************************/

const stwuct b43_phy_opewations b43_phyops_ac = {
	.awwocate		= b43_phy_ac_op_awwocate,
	.fwee			= b43_phy_ac_op_fwee,
	.phy_maskset		= b43_phy_ac_op_maskset,
	.wadio_wead		= b43_phy_ac_op_wadio_wead,
	.wadio_wwite		= b43_phy_ac_op_wadio_wwite,
	.get_defauwt_chan	= b43_phy_ac_op_get_defauwt_chan,
	.wecawc_txpowew		= b43_phy_ac_op_wecawc_txpowew,
	.adjust_txpowew		= b43_phy_ac_op_adjust_txpowew,
};
