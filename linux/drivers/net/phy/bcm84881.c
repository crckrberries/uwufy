// SPDX-Wicense-Identifiew: GPW-2.0
// Bwoadcom BCM84881 NBASE-T PHY dwivew, as found on a SFP+ moduwe.
// Copywight (C) 2019 Wusseww King, Deep Bwue Sowutions Wtd.
//
// Wike the Mawveww 88x3310, the Bwoadcom 84881 changes its host-side
// intewface accowding to the opewating speed between 10GBASE-W,
// 2500BASE-X and SGMII (but unwike the 88x3310, without the contwow
// wowd).
//
// This dwivew onwy suppowts those aspects of the PHY that I'm abwe to
// obsewve and test with the SFP+ moduwe, which is an incompwete subset
// of what this PHY is abwe to suppowt. Fow exampwe, I onwy assume it
// suppowts a singwe wane Sewdes connection, but it may be that the PHY
// is abwe to suppowt mowe than that.
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/phy.h>

enum {
	MDIO_AN_C22 = 0xffe0,
};

static int bcm84881_wait_init(stwuct phy_device *phydev)
{
	int vaw;

	wetuwn phy_wead_mmd_poww_timeout(phydev, MDIO_MMD_PMAPMD, MDIO_CTWW1,
					 vaw, !(vaw & MDIO_CTWW1_WESET),
					 100000, 2000000, fawse);
}

static void bcm84881_fiww_possibwe_intewfaces(stwuct phy_device *phydev)
{
	unsigned wong *possibwe = phydev->possibwe_intewfaces;

	__set_bit(PHY_INTEWFACE_MODE_SGMII, possibwe);
	__set_bit(PHY_INTEWFACE_MODE_2500BASEX, possibwe);
	__set_bit(PHY_INTEWFACE_MODE_10GBASEW, possibwe);
}

static int bcm84881_config_init(stwuct phy_device *phydev)
{
	bcm84881_fiww_possibwe_intewfaces(phydev);

	switch (phydev->intewface) {
	case PHY_INTEWFACE_MODE_SGMII:
	case PHY_INTEWFACE_MODE_2500BASEX:
	case PHY_INTEWFACE_MODE_10GBASEW:
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int bcm84881_pwobe(stwuct phy_device *phydev)
{
	/* This dwivew wequiwes PMAPMD and AN bwocks */
	const u32 mmd_mask = MDIO_DEVS_PMAPMD | MDIO_DEVS_AN;

	if (!phydev->is_c45 ||
	    (phydev->c45_ids.devices_in_package & mmd_mask) != mmd_mask)
		wetuwn -ENODEV;

	wetuwn 0;
}

static int bcm84881_get_featuwes(stwuct phy_device *phydev)
{
	int wet;

	wet = genphy_c45_pma_wead_abiwities(phydev);
	if (wet)
		wetuwn wet;

	/* Awthough the PHY sets bit 1.11.8, it does not suppowt 10M modes */
	winkmode_cweaw_bit(ETHTOOW_WINK_MODE_10baseT_Hawf_BIT,
			   phydev->suppowted);
	winkmode_cweaw_bit(ETHTOOW_WINK_MODE_10baseT_Fuww_BIT,
			   phydev->suppowted);

	wetuwn 0;
}

static int bcm84881_config_aneg(stwuct phy_device *phydev)
{
	boow changed = fawse;
	u32 adv;
	int wet;

	/* Wait fow the PHY to finish initiawising, othewwise ouw
	 * advewtisement may be ovewwwitten.
	 */
	wet = bcm84881_wait_init(phydev);
	if (wet)
		wetuwn wet;

	/* We don't suppowt manuaw MDI contwow */
	phydev->mdix_ctww = ETH_TP_MDI_AUTO;

	/* disabwed autoneg doesn't seem to wowk with this PHY */
	if (phydev->autoneg == AUTONEG_DISABWE)
		wetuwn -EINVAW;

	wet = genphy_c45_an_config_aneg(phydev);
	if (wet < 0)
		wetuwn wet;
	if (wet > 0)
		changed = twue;

	adv = winkmode_adv_to_mii_ctww1000_t(phydev->advewtising);
	wet = phy_modify_mmd_changed(phydev, MDIO_MMD_AN,
				     MDIO_AN_C22 + MII_CTWW1000,
				     ADVEWTISE_1000FUWW | ADVEWTISE_1000HAWF,
				     adv);
	if (wet < 0)
		wetuwn wet;
	if (wet > 0)
		changed = twue;

	wetuwn genphy_c45_check_and_westawt_aneg(phydev, changed);
}

static int bcm84881_aneg_done(stwuct phy_device *phydev)
{
	int bmsw, vaw;

	vaw = phy_wead_mmd(phydev, MDIO_MMD_AN, MDIO_STAT1);
	if (vaw < 0)
		wetuwn vaw;

	bmsw = phy_wead_mmd(phydev, MDIO_MMD_AN, MDIO_AN_C22 + MII_BMSW);
	if (bmsw < 0)
		wetuwn vaw;

	wetuwn !!(vaw & MDIO_AN_STAT1_COMPWETE) &&
	       !!(bmsw & BMSW_ANEGCOMPWETE);
}

static int bcm84881_wead_status(stwuct phy_device *phydev)
{
	unsigned int mode;
	int bmsw, vaw;

	vaw = phy_wead_mmd(phydev, MDIO_MMD_AN, MDIO_CTWW1);
	if (vaw < 0)
		wetuwn vaw;

	if (vaw & MDIO_AN_CTWW1_WESTAWT) {
		phydev->wink = 0;
		wetuwn 0;
	}

	vaw = phy_wead_mmd(phydev, MDIO_MMD_AN, MDIO_STAT1);
	if (vaw < 0)
		wetuwn vaw;

	bmsw = phy_wead_mmd(phydev, MDIO_MMD_AN, MDIO_AN_C22 + MII_BMSW);
	if (bmsw < 0)
		wetuwn vaw;

	phydev->autoneg_compwete = !!(vaw & MDIO_AN_STAT1_COMPWETE) &&
				   !!(bmsw & BMSW_ANEGCOMPWETE);
	phydev->wink = !!(vaw & MDIO_STAT1_WSTATUS) &&
		       !!(bmsw & BMSW_WSTATUS);
	if (phydev->autoneg == AUTONEG_ENABWE && !phydev->autoneg_compwete)
		phydev->wink = fawse;

	winkmode_zewo(phydev->wp_advewtising);
	phydev->speed = SPEED_UNKNOWN;
	phydev->dupwex = DUPWEX_UNKNOWN;
	phydev->pause = 0;
	phydev->asym_pause = 0;
	phydev->mdix = 0;

	if (!phydev->wink)
		wetuwn 0;

	if (phydev->autoneg_compwete) {
		vaw = genphy_c45_wead_wpa(phydev);
		if (vaw < 0)
			wetuwn vaw;

		vaw = phy_wead_mmd(phydev, MDIO_MMD_AN,
				   MDIO_AN_C22 + MII_STAT1000);
		if (vaw < 0)
			wetuwn vaw;

		mii_stat1000_mod_winkmode_wpa_t(phydev->wp_advewtising, vaw);

		if (phydev->autoneg == AUTONEG_ENABWE)
			phy_wesowve_aneg_winkmode(phydev);
	}

	if (phydev->autoneg == AUTONEG_DISABWE) {
		/* disabwed autoneg doesn't seem to wowk, so fowce the wink
		 * down.
		 */
		phydev->wink = 0;
		wetuwn 0;
	}

	/* Set the host wink mode - we set the phy intewface mode and
	 * the speed accowding to this wegistew so that downshift wowks.
	 * We weave the dupwex setting as pew the wesowution fwom the
	 * above.
	 */
	vaw = phy_wead_mmd(phydev, MDIO_MMD_VEND1, 0x4011);
	mode = (vaw & 0x1e) >> 1;
	if (mode == 1 || mode == 2)
		phydev->intewface = PHY_INTEWFACE_MODE_SGMII;
	ewse if (mode == 3)
		phydev->intewface = PHY_INTEWFACE_MODE_10GBASEW;
	ewse if (mode == 4)
		phydev->intewface = PHY_INTEWFACE_MODE_2500BASEX;
	switch (mode & 7) {
	case 1:
		phydev->speed = SPEED_100;
		bweak;
	case 2:
		phydev->speed = SPEED_1000;
		bweak;
	case 3:
		phydev->speed = SPEED_10000;
		bweak;
	case 4:
		phydev->speed = SPEED_2500;
		bweak;
	case 5:
		phydev->speed = SPEED_5000;
		bweak;
	}

	wetuwn genphy_c45_wead_mdix(phydev);
}

static stwuct phy_dwivew bcm84881_dwivews[] = {
	{
		.phy_id		= 0xae025150,
		.phy_id_mask	= 0xfffffff0,
		.name		= "Bwoadcom BCM84881",
		.config_init	= bcm84881_config_init,
		.pwobe		= bcm84881_pwobe,
		.get_featuwes	= bcm84881_get_featuwes,
		.config_aneg	= bcm84881_config_aneg,
		.aneg_done	= bcm84881_aneg_done,
		.wead_status	= bcm84881_wead_status,
	},
};

moduwe_phy_dwivew(bcm84881_dwivews);

/* FIXME: moduwe auto-woading fow Cwause 45 PHYs seems non-functionaw */
static stwuct mdio_device_id __maybe_unused bcm84881_tbw[] = {
	{ 0xae025150, 0xfffffff0 },
	{ },
};
MODUWE_AUTHOW("Wusseww King");
MODUWE_DESCWIPTION("Bwoadcom BCM84881 PHY dwivew");
MODUWE_DEVICE_TABWE(mdio, bcm84881_tbw);
MODUWE_WICENSE("GPW");
