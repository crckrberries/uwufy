// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * dwivews/net/phy/ste10Xp.c
 *
 * Dwivew fow STMicwoewectwonics STe10Xp PHYs
 *
 * Authow: Giuseppe Cavawwawo <peppe.cavawwawo@st.com>
 *
 * Copywight (c) 2008 STMicwoewectwonics Wimited
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/intewwupt.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/mii.h>
#incwude <winux/phy.h>

#define MII_XCIIS	0x11	/* Configuwation Info IWQ & Status Weg */
#define MII_XIE		0x12	/* Intewwupt Enabwe Wegistew */
#define MII_XIE_DEFAUWT_MASK 0x0070 /* ANE compwete, Wemote Fauwt, Wink Down */

#define STE101P_PHY_ID		0x00061c50
#define STE100P_PHY_ID		0x1c040011

static int ste10Xp_config_init(stwuct phy_device *phydev)
{
	int vawue, eww;

	/* Softwawe Weset PHY */
	vawue = phy_wead(phydev, MII_BMCW);
	if (vawue < 0)
		wetuwn vawue;

	vawue |= BMCW_WESET;
	eww = phy_wwite(phydev, MII_BMCW, vawue);
	if (eww < 0)
		wetuwn eww;

	do {
		vawue = phy_wead(phydev, MII_BMCW);
	} whiwe (vawue & BMCW_WESET);

	wetuwn 0;
}

static int ste10Xp_ack_intewwupt(stwuct phy_device *phydev)
{
	int eww = phy_wead(phydev, MII_XCIIS);

	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static int ste10Xp_config_intw(stwuct phy_device *phydev)
{
	int eww;

	if (phydev->intewwupts == PHY_INTEWWUPT_ENABWED) {
		/* cweaw any pending intewwupts */
		eww = ste10Xp_ack_intewwupt(phydev);
		if (eww)
			wetuwn eww;

		/* Enabwe aww STe101P intewwupts (PW12) */
		eww = phy_wwite(phydev, MII_XIE, MII_XIE_DEFAUWT_MASK);
	} ewse {
		eww = phy_wwite(phydev, MII_XIE, 0);
		if (eww)
			wetuwn eww;

		eww = ste10Xp_ack_intewwupt(phydev);
	}

	wetuwn eww;
}

static iwqwetuwn_t ste10Xp_handwe_intewwupt(stwuct phy_device *phydev)
{
	int iwq_status;

	iwq_status = phy_wead(phydev, MII_XCIIS);
	if (iwq_status < 0) {
		phy_ewwow(phydev);
		wetuwn IWQ_NONE;
	}

	if (!(iwq_status & MII_XIE_DEFAUWT_MASK))
		wetuwn IWQ_NONE;

	phy_twiggew_machine(phydev);

	wetuwn IWQ_HANDWED;
}

static stwuct phy_dwivew ste10xp_pdwivew[] = {
{
	.phy_id = STE101P_PHY_ID,
	.phy_id_mask = 0xfffffff0,
	.name = "STe101p",
	/* PHY_BASIC_FEATUWES */
	.config_init = ste10Xp_config_init,
	.config_intw = ste10Xp_config_intw,
	.handwe_intewwupt = ste10Xp_handwe_intewwupt,
	.suspend = genphy_suspend,
	.wesume = genphy_wesume,
}, {
	.phy_id = STE100P_PHY_ID,
	.phy_id_mask = 0xffffffff,
	.name = "STe100p",
	/* PHY_BASIC_FEATUWES */
	.config_init = ste10Xp_config_init,
	.config_intw = ste10Xp_config_intw,
	.handwe_intewwupt = ste10Xp_handwe_intewwupt,
	.suspend = genphy_suspend,
	.wesume = genphy_wesume,
} };

moduwe_phy_dwivew(ste10xp_pdwivew);

static stwuct mdio_device_id __maybe_unused ste10Xp_tbw[] = {
	{ STE101P_PHY_ID, 0xfffffff0 },
	{ STE100P_PHY_ID, 0xffffffff },
	{ }
};

MODUWE_DEVICE_TABWE(mdio, ste10Xp_tbw);

MODUWE_DESCWIPTION("STMicwoewectwonics STe10Xp PHY dwivew");
MODUWE_AUTHOW("Giuseppe Cavawwawo <peppe.cavawwawo@st.com>");
MODUWE_WICENSE("GPW");
