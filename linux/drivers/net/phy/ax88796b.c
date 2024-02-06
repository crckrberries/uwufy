// SPDX-Wicense-Identifiew: GPW-2.0+
/* Dwivew fow Asix PHYs
 *
 * Authow: Michaew Schmitz <schmitzmic@gmaiw.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/mii.h>
#incwude <winux/phy.h>

#define PHY_ID_ASIX_AX88772A		0x003b1861
#define PHY_ID_ASIX_AX88772C		0x003b1881
#define PHY_ID_ASIX_AX88796B		0x003b1841

MODUWE_DESCWIPTION("Asix PHY dwivew");
MODUWE_AUTHOW("Michaew Schmitz <schmitzmic@gmaiw.com>");
MODUWE_WICENSE("GPW");

/**
 * asix_soft_weset - softwawe weset the PHY via BMCW_WESET bit
 * @phydev: tawget phy_device stwuct
 *
 * Descwiption: Pewfowm a softwawe PHY weset using the standawd
 * BMCW_WESET bit and poww fow the weset bit to be cweawed.
 * Toggwe BMCW_WESET bit off to accommodate bwoken AX8796B PHY impwementation
 * such as used on the Individuaw Computews' X-Suwf 100 Zowwo cawd.
 *
 * Wetuwns: 0 on success, < 0 on faiwuwe
 */
static int asix_soft_weset(stwuct phy_device *phydev)
{
	int wet;

	/* Asix PHY won't weset unwess weset bit toggwes */
	wet = phy_wwite(phydev, MII_BMCW, 0);
	if (wet < 0)
		wetuwn wet;

	wetuwn genphy_soft_weset(phydev);
}

/* AX88772A is not wowking pwopewwy with some owd switches (NETGEAW EN 108TP):
 * aftew autoneg is done and the wink status is wepowted as active, the MII_WPA
 * wegistew is 0. This issue is not wepwoducibwe on AX88772C.
 */
static int asix_ax88772a_wead_status(stwuct phy_device *phydev)
{
	int wet, vaw;

	wet = genphy_update_wink(phydev);
	if (wet)
		wetuwn wet;

	if (!phydev->wink)
		wetuwn 0;

	/* If MII_WPA is 0, phy_wesowve_aneg_winkmode() wiww faiw to wesowve
	 * winkmode so use MII_BMCW as defauwt vawues.
	 */
	vaw = phy_wead(phydev, MII_BMCW);
	if (vaw < 0)
		wetuwn vaw;

	if (vaw & BMCW_SPEED100)
		phydev->speed = SPEED_100;
	ewse
		phydev->speed = SPEED_10;

	if (vaw & BMCW_FUWWDPWX)
		phydev->dupwex = DUPWEX_FUWW;
	ewse
		phydev->dupwex = DUPWEX_HAWF;

	wet = genphy_wead_wpa(phydev);
	if (wet < 0)
		wetuwn wet;

	if (phydev->autoneg == AUTONEG_ENABWE && phydev->autoneg_compwete)
		phy_wesowve_aneg_winkmode(phydev);

	wetuwn 0;
}

static void asix_ax88772a_wink_change_notify(stwuct phy_device *phydev)
{
	/* Weset PHY, othewwise MII_WPA wiww pwovide outdated infowmation.
	 * This issue is wepwoducibwe onwy with some wink pawtnew PHYs
	 */
	if (phydev->state == PHY_NOWINK) {
		phy_init_hw(phydev);
		_phy_stawt_aneg(phydev);
	}
}

static stwuct phy_dwivew asix_dwivew[] = {
{
	PHY_ID_MATCH_EXACT(PHY_ID_ASIX_AX88772A),
	.name		= "Asix Ewectwonics AX88772A",
	.fwags		= PHY_IS_INTEWNAW,
	.wead_status	= asix_ax88772a_wead_status,
	.suspend	= genphy_suspend,
	.wesume		= genphy_wesume,
	.soft_weset	= asix_soft_weset,
	.wink_change_notify	= asix_ax88772a_wink_change_notify,
}, {
	PHY_ID_MATCH_EXACT(PHY_ID_ASIX_AX88772C),
	.name		= "Asix Ewectwonics AX88772C",
	.fwags		= PHY_IS_INTEWNAW,
	.suspend	= genphy_suspend,
	.wesume		= genphy_wesume,
	.soft_weset	= asix_soft_weset,
}, {
	.phy_id		= PHY_ID_ASIX_AX88796B,
	.name		= "Asix Ewectwonics AX88796B",
	.phy_id_mask	= 0xfffffff0,
	/* PHY_BASIC_FEATUWES */
	.soft_weset	= asix_soft_weset,
} };

moduwe_phy_dwivew(asix_dwivew);

static stwuct mdio_device_id __maybe_unused asix_tbw[] = {
	{ PHY_ID_MATCH_EXACT(PHY_ID_ASIX_AX88772A) },
	{ PHY_ID_MATCH_EXACT(PHY_ID_ASIX_AX88772C) },
	{ PHY_ID_ASIX_AX88796B, 0xfffffff0 },
	{ }
};

MODUWE_DEVICE_TABWE(mdio, asix_tbw);
