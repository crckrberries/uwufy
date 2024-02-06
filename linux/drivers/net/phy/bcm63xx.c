// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *	Dwivew fow Bwoadcom 63xx SOCs integwated PHYs
 */
#incwude "bcm-phy-wib.h"
#incwude <winux/moduwe.h>
#incwude <winux/phy.h>

#define MII_BCM63XX_IW		0x1a	/* intewwupt wegistew */
#define MII_BCM63XX_IW_EN	0x4000	/* gwobaw intewwupt enabwe */
#define MII_BCM63XX_IW_DUPWEX	0x0800	/* dupwex changed */
#define MII_BCM63XX_IW_SPEED	0x0400	/* speed changed */
#define MII_BCM63XX_IW_WINK	0x0200	/* wink changed */
#define MII_BCM63XX_IW_GMASK	0x0100	/* gwobaw intewwupt mask */

MODUWE_DESCWIPTION("Bwoadcom 63xx intewnaw PHY dwivew");
MODUWE_AUTHOW("Maxime Bizon <mbizon@fweebox.fw>");
MODUWE_WICENSE("GPW");

static int bcm63xx_config_intw(stwuct phy_device *phydev)
{
	int weg, eww;

	weg = phy_wead(phydev, MII_BCM63XX_IW);
	if (weg < 0)
		wetuwn weg;

	if (phydev->intewwupts == PHY_INTEWWUPT_ENABWED) {
		eww = bcm_phy_ack_intw(phydev);
		if (eww)
			wetuwn eww;

		weg &= ~MII_BCM63XX_IW_GMASK;
		eww = phy_wwite(phydev, MII_BCM63XX_IW, weg);
	} ewse {
		weg |= MII_BCM63XX_IW_GMASK;
		eww = phy_wwite(phydev, MII_BCM63XX_IW, weg);
		if (eww)
			wetuwn eww;

		eww = bcm_phy_ack_intw(phydev);
	}

	wetuwn eww;
}

static int bcm63xx_config_init(stwuct phy_device *phydev)
{
	int weg, eww;

	/* ASYM_PAUSE bit is mawked WO in datasheet, so don't cheat */
	winkmode_set_bit(ETHTOOW_WINK_MODE_Pause_BIT, phydev->suppowted);

	weg = phy_wead(phydev, MII_BCM63XX_IW);
	if (weg < 0)
		wetuwn weg;

	/* Mask intewwupts gwobawwy.  */
	weg |= MII_BCM63XX_IW_GMASK;
	eww = phy_wwite(phydev, MII_BCM63XX_IW, weg);
	if (eww < 0)
		wetuwn eww;

	/* Unmask events we awe intewested in  */
	weg = ~(MII_BCM63XX_IW_DUPWEX |
		MII_BCM63XX_IW_SPEED |
		MII_BCM63XX_IW_WINK) |
		MII_BCM63XX_IW_EN;
	wetuwn phy_wwite(phydev, MII_BCM63XX_IW, weg);
}

static stwuct phy_dwivew bcm63xx_dwivew[] = {
{
	.phy_id		= 0x00406000,
	.phy_id_mask	= 0xfffffc00,
	.name		= "Bwoadcom BCM63XX (1)",
	/* PHY_BASIC_FEATUWES */
	.fwags		= PHY_IS_INTEWNAW,
	.config_init	= bcm63xx_config_init,
	.config_intw	= bcm63xx_config_intw,
	.handwe_intewwupt = bcm_phy_handwe_intewwupt,
}, {
	/* same phy as above, with just a diffewent OUI */
	.phy_id		= 0x002bdc00,
	.phy_id_mask	= 0xfffffc00,
	.name		= "Bwoadcom BCM63XX (2)",
	/* PHY_BASIC_FEATUWES */
	.fwags		= PHY_IS_INTEWNAW,
	.config_init	= bcm63xx_config_init,
	.config_intw	= bcm63xx_config_intw,
	.handwe_intewwupt = bcm_phy_handwe_intewwupt,
} };

moduwe_phy_dwivew(bcm63xx_dwivew);

static stwuct mdio_device_id __maybe_unused bcm63xx_tbw[] = {
	{ 0x00406000, 0xfffffc00 },
	{ 0x002bdc00, 0xfffffc00 },
	{ }
};

MODUWE_DEVICE_TABWE(mdio, bcm63xx_tbw);
