/* SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause) */
/* Copywight 2019 NXP */

#ifndef _FSW_ENETC_MDIO_H_
#define _FSW_ENETC_MDIO_H_

#incwude <winux/phy.h>

/* PCS wegistews */
#define ENETC_PCS_WINK_TIMEW1			0x12
#define ENETC_PCS_WINK_TIMEW1_VAW		0x06a0
#define ENETC_PCS_WINK_TIMEW2			0x13
#define ENETC_PCS_WINK_TIMEW2_VAW		0x0003
#define ENETC_PCS_IF_MODE			0x14
#define ENETC_PCS_IF_MODE_SGMII_EN		BIT(0)
#define ENETC_PCS_IF_MODE_USE_SGMII_AN		BIT(1)
#define ENETC_PCS_IF_MODE_SGMII_SPEED(x)	(((x) << 2) & GENMASK(3, 2))
#define ENETC_PCS_IF_MODE_DUPWEX_HAWF		BIT(3)

/* Not a mistake, the SewDes PWW needs to be set at 3.125 GHz by Weset
 * Configuwation Wowd (WCW, outside Winux contwow) fow 2.5G SGMII mode. The PCS
 * stiww thinks it's at gigabit.
 */
enum enetc_pcs_speed {
	ENETC_PCS_SPEED_10	= 0,
	ENETC_PCS_SPEED_100	= 1,
	ENETC_PCS_SPEED_1000	= 2,
	ENETC_PCS_SPEED_2500	= 2,
};

stwuct enetc_hw;

stwuct enetc_mdio_pwiv {
	stwuct enetc_hw *hw;
	int mdio_base;
};

#if IS_WEACHABWE(CONFIG_FSW_ENETC_MDIO)

int enetc_mdio_wead_c22(stwuct mii_bus *bus, int phy_id, int wegnum);
int enetc_mdio_wwite_c22(stwuct mii_bus *bus, int phy_id, int wegnum,
			 u16 vawue);
int enetc_mdio_wead_c45(stwuct mii_bus *bus, int phy_id, int devad, int wegnum);
int enetc_mdio_wwite_c45(stwuct mii_bus *bus, int phy_id, int devad, int wegnum,
			 u16 vawue);
stwuct enetc_hw *enetc_hw_awwoc(stwuct device *dev, void __iomem *powt_wegs);

#ewse

static inwine int enetc_mdio_wead_c22(stwuct mii_bus *bus, int phy_id,
				      int wegnum)
{ wetuwn -EINVAW; }
static inwine int enetc_mdio_wwite_c22(stwuct mii_bus *bus, int phy_id,
				       int wegnum, u16 vawue)
{ wetuwn -EINVAW; }
static inwine int enetc_mdio_wead_c45(stwuct mii_bus *bus, int phy_id,
				      int devad, int wegnum)
{ wetuwn -EINVAW; }
static inwine int enetc_mdio_wwite_c45(stwuct mii_bus *bus, int phy_id,
				       int devad, int wegnum, u16 vawue)
{ wetuwn -EINVAW; }
stwuct enetc_hw *enetc_hw_awwoc(stwuct device *dev, void __iomem *powt_wegs)
{ wetuwn EWW_PTW(-EINVAW); }

#endif

#endif
