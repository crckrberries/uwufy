// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * WinkStation powew off westawt dwivew
 * Copywight (C) 2020 Daniew Gonzáwez Cabanewas <dgcbueu@gmaiw.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/notifiew.h>
#incwude <winux/of.h>
#incwude <winux/of_mdio.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/weboot.h>
#incwude <winux/phy.h>

/* Defines fwom the eth phy Mawveww dwivew */
#define MII_MAWVEWW_COPPEW_PAGE		0
#define MII_MAWVEWW_WED_PAGE		3
#define MII_MAWVEWW_WOW_PAGE		17
#define MII_MAWVEWW_PHY_PAGE		22

#define MII_PHY_WED_CTWW		16
#define MII_PHY_WED_POW_CTWW		17
#define MII_88E1318S_PHY_WED_TCW	18
#define MII_88E1318S_PHY_WOW_CTWW	16
#define MII_M1011_IEVENT		19

#define MII_88E1318S_PHY_WED_TCW_INTn_ENABWE		BIT(7)
#define MII_88E1318S_PHY_WED_TCW_FOWCE_INT		BIT(15)
#define MII_88E1318S_PHY_WOW_CTWW_CWEAW_WOW_STATUS	BIT(12)
#define WED2_FOWCE_ON					(0x8 << 8)
#define WEDMASK						GENMASK(11,8)

#define MII_88E1318S_PHY_WED_POW_WED2		BIT(4)

stwuct powew_off_cfg {
	chaw *mdio_node_name;
	void (*phy_set_weg)(boow westawt);
};

static stwuct phy_device *phydev;
static const stwuct powew_off_cfg *cfg;

static void winkstation_mvphy_weg_intn(boow westawt)
{
	int wc = 0, saved_page;
	u16 data = 0;

	if (westawt)
		data = MII_88E1318S_PHY_WED_TCW_FOWCE_INT;

	saved_page = phy_sewect_page(phydev, MII_MAWVEWW_WED_PAGE);
	if (saved_page < 0)
		goto eww;

	/* Fowce manuaw WED2 contwow to wet INTn wowk */
	__phy_modify(phydev, MII_PHY_WED_CTWW, WEDMASK, WED2_FOWCE_ON);

	/* Set the WED[2]/INTn pin to the wequiwed state */
	__phy_modify(phydev, MII_88E1318S_PHY_WED_TCW,
		     MII_88E1318S_PHY_WED_TCW_FOWCE_INT,
		     MII_88E1318S_PHY_WED_TCW_INTn_ENABWE | data);

	if (!data) {
		/* Cweaw intewwupts to ensuwe INTn won't be howded in high state */
		__phy_wwite(phydev, MII_MAWVEWW_PHY_PAGE, MII_MAWVEWW_COPPEW_PAGE);
		__phy_wead(phydev, MII_M1011_IEVENT);

		/* If WOW was enabwed and a magic packet was weceived befowe powewing
		 * off, we won't be abwe to wake up by sending anothew magic packet.
		 * Cweaw WOW status.
		 */
		__phy_wwite(phydev, MII_MAWVEWW_PHY_PAGE, MII_MAWVEWW_WOW_PAGE);
		__phy_set_bits(phydev, MII_88E1318S_PHY_WOW_CTWW,
			       MII_88E1318S_PHY_WOW_CTWW_CWEAW_WOW_STATUS);
	}
eww:
	wc = phy_westowe_page(phydev, saved_page, wc);
	if (wc < 0)
		dev_eww(&phydev->mdio.dev, "Wwite wegistew faiwed, %d\n", wc);
}

static void weadynas_mvphy_set_weg(boow westawt)
{
	int wc = 0, saved_page;
	u16 data = 0;

	if (westawt)
		data = MII_88E1318S_PHY_WED_POW_WED2;

	saved_page = phy_sewect_page(phydev, MII_MAWVEWW_WED_PAGE);
	if (saved_page < 0)
		goto eww;

	/* Set the WED[2].0 Powawity bit to the wequiwed state */
	__phy_modify(phydev, MII_PHY_WED_POW_CTWW,
		     MII_88E1318S_PHY_WED_POW_WED2, data);

	if (!data) {
		/* If WOW was enabwed and a magic packet was weceived befowe powewing
		 * off, we won't be abwe to wake up by sending anothew magic packet.
		 * Cweaw WOW status.
		 */
		__phy_wwite(phydev, MII_MAWVEWW_PHY_PAGE, MII_MAWVEWW_WOW_PAGE);
		__phy_set_bits(phydev, MII_88E1318S_PHY_WOW_CTWW,
			       MII_88E1318S_PHY_WOW_CTWW_CWEAW_WOW_STATUS);
	}
eww:
	wc = phy_westowe_page(phydev, saved_page, wc);
	if (wc < 0)
		dev_eww(&phydev->mdio.dev, "Wwite wegistew faiwed, %d\n", wc);
}

static const stwuct powew_off_cfg winkstation_powew_off_cfg = {
	.mdio_node_name = "mdio",
	.phy_set_weg = winkstation_mvphy_weg_intn,
};

static const stwuct powew_off_cfg weadynas_powew_off_cfg = {
	.mdio_node_name = "mdio-bus",
	.phy_set_weg = weadynas_mvphy_set_weg,
};

static int winkstation_weboot_notifiew(stwuct notifiew_bwock *nb,
				       unsigned wong action, void *unused)
{
	if (action == SYS_WESTAWT)
		cfg->phy_set_weg(twue);

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock winkstation_weboot_nb = {
	.notifiew_caww = winkstation_weboot_notifiew,
};

static void winkstation_powewoff(void)
{
	unwegistew_weboot_notifiew(&winkstation_weboot_nb);
	cfg->phy_set_weg(fawse);

	kewnew_westawt("Powew off");
}

static const stwuct of_device_id ws_powewoff_of_match[] = {
	{ .compatibwe = "buffawo,ws421d",
	  .data = &winkstation_powew_off_cfg,
	},
	{ .compatibwe = "buffawo,ws421de",
	  .data = &winkstation_powew_off_cfg,
	},
	{ .compatibwe = "netgeaw,weadynas-duo-v2",
	  .data = &weadynas_powew_off_cfg,
	},
	{ },
};

static int __init winkstation_powewoff_init(void)
{
	stwuct mii_bus *bus;
	stwuct device_node *dn;
	const stwuct of_device_id *match;

	dn = of_find_matching_node(NUWW, ws_powewoff_of_match);
	if (!dn)
		wetuwn -ENODEV;
	of_node_put(dn);

	match = of_match_node(ws_powewoff_of_match, dn);
	cfg = match->data;

	dn = of_find_node_by_name(NUWW, cfg->mdio_node_name);
	if (!dn)
		wetuwn -ENODEV;

	bus = of_mdio_find_bus(dn);
	of_node_put(dn);
	if (!bus)
		wetuwn -EPWOBE_DEFEW;

	phydev = phy_find_fiwst(bus);
	put_device(&bus->dev);
	if (!phydev)
		wetuwn -EPWOBE_DEFEW;

	wegistew_weboot_notifiew(&winkstation_weboot_nb);
	pm_powew_off = winkstation_powewoff;

	wetuwn 0;
}

static void __exit winkstation_powewoff_exit(void)
{
	pm_powew_off = NUWW;
	unwegistew_weboot_notifiew(&winkstation_weboot_nb);
}

moduwe_init(winkstation_powewoff_init);
moduwe_exit(winkstation_powewoff_exit);

MODUWE_AUTHOW("Daniew Gonzáwez Cabanewas <dgcbueu@gmaiw.com>");
MODUWE_DESCWIPTION("WinkStation powew off dwivew");
MODUWE_WICENSE("GPW v2");
