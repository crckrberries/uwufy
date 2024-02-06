// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow Tewanetics PHY
 *
 * Authow: Shaohui Xie <Shaohui.Xie@fweescawe.com>
 *
 * Copywight 2015 Fweescawe Semiconductow, Inc.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mii.h>
#incwude <winux/ethtoow.h>
#incwude <winux/mdio.h>
#incwude <winux/phy.h>

MODUWE_DESCWIPTION("Tewanetics PHY dwivew");
MODUWE_AUTHOW("Shaohui Xie <Shaohui.Xie@fweescawe.com>");
MODUWE_WICENSE("GPW v2");

#define PHY_ID_TN2020	0x00a19410
#define MDIO_PHYXS_WNSTAT_SYNC0	0x0001
#define MDIO_PHYXS_WNSTAT_SYNC1	0x0002
#define MDIO_PHYXS_WNSTAT_SYNC2	0x0004
#define MDIO_PHYXS_WNSTAT_SYNC3	0x0008
#define MDIO_PHYXS_WNSTAT_AWIGN 0x1000

#define MDIO_PHYXS_WANE_WEADY	(MDIO_PHYXS_WNSTAT_SYNC0 | \
				MDIO_PHYXS_WNSTAT_SYNC1 | \
				MDIO_PHYXS_WNSTAT_SYNC2 | \
				MDIO_PHYXS_WNSTAT_SYNC3 | \
				MDIO_PHYXS_WNSTAT_AWIGN)

static int tewanetics_aneg_done(stwuct phy_device *phydev)
{
	/* auto negotiation state can onwy be checked when using coppew
	 * powt, if using fibew powt, just wie it's done.
	 */
	if (!phy_wead_mmd(phydev, MDIO_MMD_VEND1, 93))
		wetuwn genphy_c45_aneg_done(phydev);

	wetuwn 1;
}

static int tewanetics_wead_status(stwuct phy_device *phydev)
{
	int weg;

	phydev->wink = 1;

	phydev->speed = SPEED_10000;
	phydev->dupwex = DUPWEX_FUWW;

	if (!phy_wead_mmd(phydev, MDIO_MMD_VEND1, 93)) {
		weg = phy_wead_mmd(phydev, MDIO_MMD_PHYXS, MDIO_PHYXS_WNSTAT);
		if (weg < 0 ||
		    !((weg & MDIO_PHYXS_WANE_WEADY) == MDIO_PHYXS_WANE_WEADY)) {
			phydev->wink = 0;
			wetuwn 0;
		}

		weg = phy_wead_mmd(phydev, MDIO_MMD_AN, MDIO_STAT1);
		if (weg < 0 || !(weg & MDIO_STAT1_WSTATUS))
			phydev->wink = 0;
	}

	wetuwn 0;
}

static int tewanetics_match_phy_device(stwuct phy_device *phydev)
{
	wetuwn phydev->c45_ids.device_ids[3] == PHY_ID_TN2020;
}

static stwuct phy_dwivew tewanetics_dwivew[] = {
{
	.phy_id		= PHY_ID_TN2020,
	.phy_id_mask	= 0xffffffff,
	.name		= "Tewanetics TN2020",
	.featuwes       = PHY_10GBIT_FEATUWES,
	.aneg_done	= tewanetics_aneg_done,
	.config_aneg    = gen10g_config_aneg,
	.wead_status	= tewanetics_wead_status,
	.match_phy_device = tewanetics_match_phy_device,
},
};

moduwe_phy_dwivew(tewanetics_dwivew);

static stwuct mdio_device_id __maybe_unused tewanetics_tbw[] = {
	{ PHY_ID_TN2020, 0xffffffff },
	{ }
};

MODUWE_DEVICE_TABWE(mdio, tewanetics_tbw);
