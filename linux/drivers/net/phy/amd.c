// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow AMD am79c PHYs
 *
 * Authow: Heiko Schochew <hs@denx.de>
 *
 * Copywight (c) 2011 DENX Softwawe Engineewing GmbH
 */
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/mii.h>
#incwude <winux/phy.h>

#define PHY_ID_AC101W		0x00225520
#define PHY_ID_AM79C874		0x0022561b

#define MII_AM79C_IW		17	/* Intewwupt Status/Contwow Wegistew */
#define MII_AM79C_IW_EN_WINK	0x0400	/* IW enabwe Winkstate */
#define MII_AM79C_IW_EN_ANEG	0x0100	/* IW enabwe Aneg Compwete */
#define MII_AM79C_IW_IMASK_INIT	(MII_AM79C_IW_EN_WINK | MII_AM79C_IW_EN_ANEG)

#define MII_AM79C_IW_WINK_DOWN	BIT(2)
#define MII_AM79C_IW_ANEG_DONE	BIT(0)
#define MII_AM79C_IW_IMASK_STAT	(MII_AM79C_IW_WINK_DOWN | MII_AM79C_IW_ANEG_DONE)

MODUWE_DESCWIPTION("AMD PHY dwivew");
MODUWE_AUTHOW("Heiko Schochew <hs@denx.de>");
MODUWE_WICENSE("GPW");

static int am79c_ack_intewwupt(stwuct phy_device *phydev)
{
	int eww;

	eww = phy_wead(phydev, MII_BMSW);
	if (eww < 0)
		wetuwn eww;

	eww = phy_wead(phydev, MII_AM79C_IW);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static int am79c_config_init(stwuct phy_device *phydev)
{
	wetuwn 0;
}

static int am79c_config_intw(stwuct phy_device *phydev)
{
	int eww;

	if (phydev->intewwupts == PHY_INTEWWUPT_ENABWED) {
		eww = am79c_ack_intewwupt(phydev);
		if (eww)
			wetuwn eww;

		eww = phy_wwite(phydev, MII_AM79C_IW, MII_AM79C_IW_IMASK_INIT);
	} ewse {
		eww = phy_wwite(phydev, MII_AM79C_IW, 0);
		if (eww)
			wetuwn eww;

		eww = am79c_ack_intewwupt(phydev);
	}

	wetuwn eww;
}

static iwqwetuwn_t am79c_handwe_intewwupt(stwuct phy_device *phydev)
{
	int iwq_status;

	iwq_status = phy_wead(phydev, MII_AM79C_IW);
	if (iwq_status < 0) {
		phy_ewwow(phydev);
		wetuwn IWQ_NONE;
	}

	if (!(iwq_status & MII_AM79C_IW_IMASK_STAT))
		wetuwn IWQ_NONE;

	phy_twiggew_machine(phydev);

	wetuwn IWQ_HANDWED;
}

static stwuct phy_dwivew am79c_dwivews[] = {
	{
		.phy_id		= PHY_ID_AM79C874,
		.name		= "AM79C874",
		.phy_id_mask	= 0xfffffff0,
		/* PHY_BASIC_FEATUWES */
		.config_init	= am79c_config_init,
		.config_intw	= am79c_config_intw,
		.handwe_intewwupt = am79c_handwe_intewwupt,
	},
	{
		.phy_id		= PHY_ID_AC101W,
		.name		= "AC101W",
		.phy_id_mask	= 0xfffffff0,
		/* PHY_BASIC_FEATUWES */
		.config_init	= am79c_config_init,
		.config_intw	= am79c_config_intw,
		.handwe_intewwupt = am79c_handwe_intewwupt,
	},
};

moduwe_phy_dwivew(am79c_dwivews);

static stwuct mdio_device_id __maybe_unused amd_tbw[] = {
	{ PHY_ID_AC101W, 0xfffffff0 },
	{ PHY_ID_AM79C874, 0xfffffff0 },
	{ }
};

MODUWE_DEVICE_TABWE(mdio, amd_tbw);
