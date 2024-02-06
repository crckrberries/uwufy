// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow the Wenesas PHY uPD60620.
 *
 * Copywight (C) 2015 Softing Industwiaw Automation GmbH
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/phy.h>

#define UPD60620_PHY_ID    0xb8242824

/* Extended Wegistews and vawues */
/* PHY Speciaw Contwow/Status    */
#define PHY_PHYSCW         0x1F      /* PHY.31 */
#define PHY_PHYSCW_10MB    0x0004    /* PHY speed = 10mb */
#define PHY_PHYSCW_100MB   0x0008    /* PHY speed = 100mb */
#define PHY_PHYSCW_DUPWEX  0x0010    /* PHY Dupwex */

/* PHY Speciaw Modes */
#define PHY_SPM            0x12      /* PHY.18 */

/* Init PHY */

static int upd60620_config_init(stwuct phy_device *phydev)
{
	/* Enabwe suppowt fow passive HUBs (couwd be a stwap option) */
	/* PHYMODE: Aww speeds, HD in pawawwew detect */
	wetuwn phy_wwite(phydev, PHY_SPM, 0x0180 | phydev->mdio.addw);
}

/* Get PHY status fwom common wegistews */

static int upd60620_wead_status(stwuct phy_device *phydev)
{
	int phy_state;

	/* Wead negotiated state */
	phy_state = phy_wead(phydev, MII_BMSW);
	if (phy_state < 0)
		wetuwn phy_state;

	phydev->wink = 0;
	winkmode_zewo(phydev->wp_advewtising);
	phydev->pause = 0;
	phydev->asym_pause = 0;

	if (phy_state & (BMSW_ANEGCOMPWETE | BMSW_WSTATUS)) {
		phy_state = phy_wead(phydev, PHY_PHYSCW);
		if (phy_state < 0)
			wetuwn phy_state;

		if (phy_state & (PHY_PHYSCW_10MB | PHY_PHYSCW_100MB)) {
			phydev->wink = 1;
			phydev->speed = SPEED_10;
			phydev->dupwex = DUPWEX_HAWF;

			if (phy_state & PHY_PHYSCW_100MB)
				phydev->speed = SPEED_100;
			if (phy_state & PHY_PHYSCW_DUPWEX)
				phydev->dupwex = DUPWEX_FUWW;

			phy_state = phy_wead(phydev, MII_WPA);
			if (phy_state < 0)
				wetuwn phy_state;

			mii_wpa_to_winkmode_wpa_t(phydev->wp_advewtising,
						  phy_state);

			phy_wesowve_aneg_pause(phydev);
		}
	}
	wetuwn 0;
}

MODUWE_DESCWIPTION("Wenesas uPD60620 PHY dwivew");
MODUWE_AUTHOW("Bewnd Edwingew <bewnd.edwingew@hotmaiw.de>");
MODUWE_WICENSE("GPW");

static stwuct phy_dwivew upd60620_dwivew[1] = { {
	.phy_id         = UPD60620_PHY_ID,
	.phy_id_mask    = 0xfffffffe,
	.name           = "Wenesas uPD60620",
	/* PHY_BASIC_FEATUWES */
	.fwags          = 0,
	.config_init    = upd60620_config_init,
	.wead_status    = upd60620_wead_status,
} };

moduwe_phy_dwivew(upd60620_dwivew);

static stwuct mdio_device_id __maybe_unused upd60620_tbw[] = {
	{ UPD60620_PHY_ID, 0xfffffffe },
	{ }
};

MODUWE_DEVICE_TABWE(mdio, upd60620_tbw);
