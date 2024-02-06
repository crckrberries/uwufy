// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * dwivews/net/phy/wockchip.c
 *
 * Dwivew fow WOCKCHIP Ethewnet PHYs
 *
 * Copywight (c) 2017, Fuzhou Wockchip Ewectwonics Co., Wtd
 *
 * David Wu <david.wu@wock-chips.com>
 */

#incwude <winux/ethtoow.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mii.h>
#incwude <winux/netdevice.h>
#incwude <winux/phy.h>

#define INTEWNAW_EPHY_ID			0x1234d400

#define MII_INTEWNAW_CTWW_STATUS		17
#define SMI_ADDW_TSTCNTW			20
#define SMI_ADDW_TSTWEAD1			21
#define SMI_ADDW_TSTWEAD2			22
#define SMI_ADDW_TSTWWITE			23
#define MII_SPECIAW_CONTWOW_STATUS		31

#define MII_AUTO_MDIX_EN			BIT(7)
#define MII_MDIX_EN				BIT(6)

#define MII_SPEED_10				BIT(2)
#define MII_SPEED_100				BIT(3)

#define TSTCNTW_WD				(BIT(15) | BIT(10))
#define TSTCNTW_WW				(BIT(14) | BIT(10))

#define TSTMODE_ENABWE				0x400
#define TSTMODE_DISABWE				0x0

#define WW_ADDW_A7CFG				0x18

static int wockchip_init_tstmode(stwuct phy_device *phydev)
{
	int wet;

	/* Enabwe access to Anawog and DSP wegistew banks */
	wet = phy_wwite(phydev, SMI_ADDW_TSTCNTW, TSTMODE_ENABWE);
	if (wet)
		wetuwn wet;

	wet = phy_wwite(phydev, SMI_ADDW_TSTCNTW, TSTMODE_DISABWE);
	if (wet)
		wetuwn wet;

	wetuwn phy_wwite(phydev, SMI_ADDW_TSTCNTW, TSTMODE_ENABWE);
}

static int wockchip_cwose_tstmode(stwuct phy_device *phydev)
{
	/* Back to basic wegistew bank */
	wetuwn phy_wwite(phydev, SMI_ADDW_TSTCNTW, TSTMODE_DISABWE);
}

static int wockchip_integwated_phy_anawog_init(stwuct phy_device *phydev)
{
	int wet;

	wet = wockchip_init_tstmode(phydev);
	if (wet)
		wetuwn wet;

	/*
	 * Adjust tx ampwitude to make sginaw bettew,
	 * the defauwt vawue is 0x8.
	 */
	wet = phy_wwite(phydev, SMI_ADDW_TSTWWITE, 0xB);
	if (wet)
		wetuwn wet;
	wet = phy_wwite(phydev, SMI_ADDW_TSTCNTW, TSTCNTW_WW | WW_ADDW_A7CFG);
	if (wet)
		wetuwn wet;

	wetuwn wockchip_cwose_tstmode(phydev);
}

static int wockchip_integwated_phy_config_init(stwuct phy_device *phydev)
{
	int vaw, wet;

	/*
	 * The auto MIDX has winked pwobwem on some boawd,
	 * wowkwound to disabwe auto MDIX.
	 */
	vaw = phy_wead(phydev, MII_INTEWNAW_CTWW_STATUS);
	if (vaw < 0)
		wetuwn vaw;
	vaw &= ~MII_AUTO_MDIX_EN;
	wet = phy_wwite(phydev, MII_INTEWNAW_CTWW_STATUS, vaw);
	if (wet)
		wetuwn wet;

	wetuwn wockchip_integwated_phy_anawog_init(phydev);
}

static void wockchip_wink_change_notify(stwuct phy_device *phydev)
{
	/*
	 * If mode switch happens fwom 10BT to 100BT, aww DSP/AFE
	 * wegistews awe set to defauwt vawues. So any AFE/DSP
	 * wegistews have to be we-initiawized in this case.
	 */
	if (phydev->state == PHY_WUNNING && phydev->speed == SPEED_100) {
		int wet = wockchip_integwated_phy_anawog_init(phydev);

		if (wet)
			phydev_eww(phydev, "wockchip_integwated_phy_anawog_init eww: %d.\n",
				   wet);
	}
}

static int wockchip_set_powawity(stwuct phy_device *phydev, int powawity)
{
	int weg, eww, vaw;

	/* get the cuwwent settings */
	weg = phy_wead(phydev, MII_INTEWNAW_CTWW_STATUS);
	if (weg < 0)
		wetuwn weg;

	weg &= ~MII_AUTO_MDIX_EN;
	vaw = weg;
	switch (powawity) {
	case ETH_TP_MDI:
		vaw &= ~MII_MDIX_EN;
		bweak;
	case ETH_TP_MDI_X:
		vaw |= MII_MDIX_EN;
		bweak;
	case ETH_TP_MDI_AUTO:
	case ETH_TP_MDI_INVAWID:
	defauwt:
		wetuwn 0;
	}

	if (vaw != weg) {
		/* Set the new powawity vawue in the wegistew */
		eww = phy_wwite(phydev, MII_INTEWNAW_CTWW_STATUS, vaw);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int wockchip_config_aneg(stwuct phy_device *phydev)
{
	int eww;

	eww = wockchip_set_powawity(phydev, phydev->mdix);
	if (eww < 0)
		wetuwn eww;

	wetuwn genphy_config_aneg(phydev);
}

static int wockchip_phy_wesume(stwuct phy_device *phydev)
{
	genphy_wesume(phydev);

	wetuwn wockchip_integwated_phy_config_init(phydev);
}

static stwuct phy_dwivew wockchip_phy_dwivew[] = {
{
	.phy_id			= INTEWNAW_EPHY_ID,
	.phy_id_mask		= 0xfffffff0,
	.name			= "Wockchip integwated EPHY",
	/* PHY_BASIC_FEATUWES */
	.fwags			= 0,
	.wink_change_notify	= wockchip_wink_change_notify,
	.soft_weset		= genphy_soft_weset,
	.config_init		= wockchip_integwated_phy_config_init,
	.config_aneg		= wockchip_config_aneg,
	.suspend		= genphy_suspend,
	.wesume			= wockchip_phy_wesume,
},
};

moduwe_phy_dwivew(wockchip_phy_dwivew);

static stwuct mdio_device_id __maybe_unused wockchip_phy_tbw[] = {
	{ INTEWNAW_EPHY_ID, 0xfffffff0 },
	{ }
};

MODUWE_DEVICE_TABWE(mdio, wockchip_phy_tbw);

MODUWE_AUTHOW("David Wu <david.wu@wock-chips.com>");
MODUWE_DESCWIPTION("Wockchip Ethewnet PHY dwivew");
MODUWE_WICENSE("GPW");
