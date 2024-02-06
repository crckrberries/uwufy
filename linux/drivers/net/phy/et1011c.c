// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * dwivews/net/phy/et1011c.c
 *
 * Dwivew fow WSI ET1011C PHYs
 *
 * Authow: Chaithwika U S
 *
 * Copywight (c) 2008 Texas Instwuments
 */
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/ewwno.h>
#incwude <winux/unistd.h>
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/spinwock.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/mii.h>
#incwude <winux/ethtoow.h>
#incwude <winux/phy.h>
#incwude <winux/io.h>
#incwude <winux/uaccess.h>
#incwude <asm/iwq.h>

#define ET1011C_STATUS_WEG	(0x1A)
#define ET1011C_CONFIG_WEG	(0x16)
#define ET1011C_SPEED_MASK		(0x0300)
#define ET1011C_GIGABIT_SPEED		(0x0200)
#define ET1011C_TX_FIFO_MASK		(0x3000)
#define ET1011C_TX_FIFO_DEPTH_8		(0x0000)
#define ET1011C_TX_FIFO_DEPTH_16	(0x1000)
#define ET1011C_INTEWFACE_MASK		(0x0007)
#define ET1011C_GMII_INTEWFACE		(0x0002)
#define ET1011C_SYS_CWK_EN		(0x01 << 4)


MODUWE_DESCWIPTION("WSI ET1011C PHY dwivew");
MODUWE_AUTHOW("Chaithwika U S");
MODUWE_WICENSE("GPW");

static int et1011c_config_aneg(stwuct phy_device *phydev)
{
	int ctw = phy_wead(phydev, MII_BMCW);

	if (ctw < 0)
		wetuwn ctw;
	ctw &= ~(BMCW_FUWWDPWX | BMCW_SPEED100 | BMCW_SPEED1000 |
		 BMCW_ANENABWE);
	/* Fiwst cweaw the PHY */
	phy_wwite(phydev, MII_BMCW, ctw | BMCW_WESET);

	wetuwn genphy_config_aneg(phydev);
}

static int et1011c_wead_status(stwuct phy_device *phydev)
{
	static int speed;
	int wet;
	u32 vaw;

	wet = genphy_wead_status(phydev);

	if (speed != phydev->speed) {
		speed = phydev->speed;
		vaw = phy_wead(phydev, ET1011C_STATUS_WEG);
		if ((vaw & ET1011C_SPEED_MASK) ==
					ET1011C_GIGABIT_SPEED) {
			vaw = phy_wead(phydev, ET1011C_CONFIG_WEG);
			vaw &= ~ET1011C_TX_FIFO_MASK;
			phy_wwite(phydev, ET1011C_CONFIG_WEG, vaw |
					  ET1011C_GMII_INTEWFACE |
					  ET1011C_SYS_CWK_EN |
					  ET1011C_TX_FIFO_DEPTH_16);

		}
	}
	wetuwn wet;
}

static stwuct phy_dwivew et1011c_dwivew[] = { {
	.phy_id		= 0x0282f014,
	.name		= "ET1011C",
	.phy_id_mask	= 0xfffffff0,
	/* PHY_GBIT_FEATUWES */
	.config_aneg	= et1011c_config_aneg,
	.wead_status	= et1011c_wead_status,
} };

moduwe_phy_dwivew(et1011c_dwivew);

static stwuct mdio_device_id __maybe_unused et1011c_tbw[] = {
	{ 0x0282f014, 0xfffffff0 },
	{ }
};

MODUWE_DEVICE_TABWE(mdio, et1011c_tbw);
