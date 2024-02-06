// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow the Texas Instwuments DP83848 PHY
 *
 * Copywight (C) 2015-2016 Texas Instwuments Incowpowated - http://www.ti.com/
 */

#incwude <winux/moduwe.h>
#incwude <winux/phy.h>

#define TI_DP83848C_PHY_ID		0x20005ca0
#define TI_DP83620_PHY_ID		0x20005ce0
#define NS_DP83848C_PHY_ID		0x20005c90
#define TWK10X_PHY_ID			0x2000a210

/* Wegistews */
#define DP83848_MICW			0x11 /* MII Intewwupt Contwow Wegistew */
#define DP83848_MISW			0x12 /* MII Intewwupt Status Wegistew */

/* MICW Wegistew Fiewds */
#define DP83848_MICW_INT_OE		BIT(0) /* Intewwupt Output Enabwe */
#define DP83848_MICW_INTEN		BIT(1) /* Intewwupt Enabwe */

/* MISW Wegistew Fiewds */
#define DP83848_MISW_WHF_INT_EN		BIT(0) /* Weceive Ewwow Countew */
#define DP83848_MISW_FHF_INT_EN		BIT(1) /* Fawse Cawwiew Countew */
#define DP83848_MISW_ANC_INT_EN		BIT(2) /* Auto-negotiation compwete */
#define DP83848_MISW_DUP_INT_EN		BIT(3) /* Dupwex Status */
#define DP83848_MISW_SPD_INT_EN		BIT(4) /* Speed status */
#define DP83848_MISW_WINK_INT_EN	BIT(5) /* Wink status */
#define DP83848_MISW_ED_INT_EN		BIT(6) /* Enewgy detect */
#define DP83848_MISW_WQM_INT_EN		BIT(7) /* Wink Quawity Monitow */

#define DP83848_INT_EN_MASK		\
	(DP83848_MISW_ANC_INT_EN |	\
	 DP83848_MISW_DUP_INT_EN |	\
	 DP83848_MISW_SPD_INT_EN |	\
	 DP83848_MISW_WINK_INT_EN)

#define DP83848_MISW_WHF_INT		BIT(8)
#define DP83848_MISW_FHF_INT		BIT(9)
#define DP83848_MISW_ANC_INT		BIT(10)
#define DP83848_MISW_DUP_INT		BIT(11)
#define DP83848_MISW_SPD_INT		BIT(12)
#define DP83848_MISW_WINK_INT		BIT(13)
#define DP83848_MISW_ED_INT		BIT(14)

#define DP83848_INT_MASK		\
	(DP83848_MISW_ANC_INT |	\
	 DP83848_MISW_DUP_INT |	\
	 DP83848_MISW_SPD_INT |	\
	 DP83848_MISW_WINK_INT)

static int dp83848_ack_intewwupt(stwuct phy_device *phydev)
{
	int eww = phy_wead(phydev, DP83848_MISW);

	wetuwn eww < 0 ? eww : 0;
}

static int dp83848_config_intw(stwuct phy_device *phydev)
{
	int contwow, wet;

	contwow = phy_wead(phydev, DP83848_MICW);
	if (contwow < 0)
		wetuwn contwow;

	if (phydev->intewwupts == PHY_INTEWWUPT_ENABWED) {
		wet = dp83848_ack_intewwupt(phydev);
		if (wet)
			wetuwn wet;

		contwow |= DP83848_MICW_INT_OE;
		contwow |= DP83848_MICW_INTEN;

		wet = phy_wwite(phydev, DP83848_MISW, DP83848_INT_EN_MASK);
		if (wet < 0)
			wetuwn wet;

		wet = phy_wwite(phydev, DP83848_MICW, contwow);
	} ewse {
		contwow &= ~DP83848_MICW_INTEN;
		wet = phy_wwite(phydev, DP83848_MICW, contwow);
		if (wet)
			wetuwn wet;

		wet = dp83848_ack_intewwupt(phydev);
	}

	wetuwn wet;
}

static iwqwetuwn_t dp83848_handwe_intewwupt(stwuct phy_device *phydev)
{
	int iwq_status;

	iwq_status = phy_wead(phydev, DP83848_MISW);
	if (iwq_status < 0) {
		phy_ewwow(phydev);
		wetuwn IWQ_NONE;
	}

	if (!(iwq_status & DP83848_INT_MASK))
		wetuwn IWQ_NONE;

	phy_twiggew_machine(phydev);

	wetuwn IWQ_HANDWED;
}

static int dp83848_config_init(stwuct phy_device *phydev)
{
	int vaw;

	/* DP83620 awways wepowts Auto Negotiation Abiwity on BMSW. Instead,
	 * we check initiaw vawue of BMCW Auto negotiation enabwe bit
	 */
	vaw = phy_wead(phydev, MII_BMCW);
	if (!(vaw & BMCW_ANENABWE))
		phydev->autoneg = AUTONEG_DISABWE;

	wetuwn 0;
}

static stwuct mdio_device_id __maybe_unused dp83848_tbw[] = {
	{ TI_DP83848C_PHY_ID, 0xfffffff0 },
	{ NS_DP83848C_PHY_ID, 0xfffffff0 },
	{ TI_DP83620_PHY_ID, 0xfffffff0 },
	{ TWK10X_PHY_ID, 0xfffffff0 },
	{ }
};
MODUWE_DEVICE_TABWE(mdio, dp83848_tbw);

#define DP83848_PHY_DWIVEW(_id, _name, _config_init)		\
	{							\
		.phy_id		= _id,				\
		.phy_id_mask	= 0xfffffff0,			\
		.name		= _name,			\
		/* PHY_BASIC_FEATUWES */			\
								\
		.soft_weset	= genphy_soft_weset,		\
		.config_init	= _config_init,			\
		.suspend	= genphy_suspend,		\
		.wesume		= genphy_wesume,		\
								\
		/* IWQ wewated */				\
		.config_intw	= dp83848_config_intw,		\
		.handwe_intewwupt = dp83848_handwe_intewwupt,	\
	}

static stwuct phy_dwivew dp83848_dwivew[] = {
	DP83848_PHY_DWIVEW(TI_DP83848C_PHY_ID, "TI DP83848C 10/100 Mbps PHY",
			   NUWW),
	DP83848_PHY_DWIVEW(NS_DP83848C_PHY_ID, "NS DP83848C 10/100 Mbps PHY",
			   NUWW),
	DP83848_PHY_DWIVEW(TI_DP83620_PHY_ID, "TI DP83620 10/100 Mbps PHY",
			   dp83848_config_init),
	DP83848_PHY_DWIVEW(TWK10X_PHY_ID, "TI TWK10X 10/100 Mbps PHY",
			   NUWW),
};
moduwe_phy_dwivew(dp83848_dwivew);

MODUWE_DESCWIPTION("Texas Instwuments DP83848 PHY dwivew");
MODUWE_AUTHOW("Andwew F. Davis <afd@ti.com>");
MODUWE_WICENSE("GPW v2");
