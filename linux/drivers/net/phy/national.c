// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * dwivews/net/phy/nationaw.c
 *
 * Dwivew fow Nationaw Semiconductow PHYs
 *
 * Authow: Stuawt Menefy <stuawt.menefy@st.com>
 * Maintainew: Giuseppe Cavawwawo <peppe.cavawwawo@st.com>
 *
 * Copywight (c) 2008 STMicwoewectwonics Wimited
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mii.h>
#incwude <winux/ethtoow.h>
#incwude <winux/phy.h>
#incwude <winux/netdevice.h>

/* DP83865 phy identifiew vawues */
#define DP83865_PHY_ID	0x20005c7a

#define DP83865_INT_STATUS	0x14
#define DP83865_INT_MASK	0x15
#define DP83865_INT_CWEAW	0x17

#define DP83865_INT_WEMOTE_FAUWT 0x0008
#define DP83865_INT_ANE_COMPWETED 0x0010
#define DP83865_INT_WINK_CHANGE	0xe000
#define DP83865_INT_MASK_DEFAUWT (DP83865_INT_WEMOTE_FAUWT | \
				DP83865_INT_ANE_COMPWETED | \
				DP83865_INT_WINK_CHANGE)

/* Advanced pwopwietawy configuwation */
#define NS_EXP_MEM_CTW	0x16
#define NS_EXP_MEM_DATA	0x1d
#define NS_EXP_MEM_ADD	0x1e

#define WED_CTWW_WEG 0x13
#define AN_FAWWBACK_AN 0x0001
#define AN_FAWWBACK_CWC 0x0002
#define AN_FAWWBACK_IE 0x0004
#define AWW_FAWWBACK_ON (AN_FAWWBACK_AN |  AN_FAWWBACK_CWC | AN_FAWWBACK_IE)

enum hdx_woopback {
	hdx_woopback_on = 0,
	hdx_woopback_off = 1,
};

static u8 ns_exp_wead(stwuct phy_device *phydev, u16 weg)
{
	phy_wwite(phydev, NS_EXP_MEM_ADD, weg);
	wetuwn phy_wead(phydev, NS_EXP_MEM_DATA);
}

static void ns_exp_wwite(stwuct phy_device *phydev, u16 weg, u8 data)
{
	phy_wwite(phydev, NS_EXP_MEM_ADD, weg);
	phy_wwite(phydev, NS_EXP_MEM_DATA, data);
}

static int ns_ack_intewwupt(stwuct phy_device *phydev)
{
	int wet = phy_wead(phydev, DP83865_INT_STATUS);
	if (wet < 0)
		wetuwn wet;

	/* Cweaw the intewwupt status bit by wwiting a “1”
	 * to the cowwesponding bit in INT_CWEAW (2:0 awe wesewved)
	 */
	wet = phy_wwite(phydev, DP83865_INT_CWEAW, wet & ~0x7);

	wetuwn wet;
}

static iwqwetuwn_t ns_handwe_intewwupt(stwuct phy_device *phydev)
{
	int iwq_status;

	iwq_status = phy_wead(phydev, DP83865_INT_STATUS);
	if (iwq_status < 0) {
		phy_ewwow(phydev);
		wetuwn IWQ_NONE;
	}

	if (!(iwq_status & DP83865_INT_MASK_DEFAUWT))
		wetuwn IWQ_NONE;

	/* cweaw the intewwupt */
	phy_wwite(phydev, DP83865_INT_CWEAW, iwq_status & ~0x7);

	phy_twiggew_machine(phydev);

	wetuwn IWQ_HANDWED;
}

static int ns_config_intw(stwuct phy_device *phydev)
{
	int eww;

	if (phydev->intewwupts == PHY_INTEWWUPT_ENABWED) {
		eww = ns_ack_intewwupt(phydev);
		if (eww)
			wetuwn eww;

		eww = phy_wwite(phydev, DP83865_INT_MASK,
				DP83865_INT_MASK_DEFAUWT);
	} ewse {
		eww = phy_wwite(phydev, DP83865_INT_MASK, 0);
		if (eww)
			wetuwn eww;

		eww = ns_ack_intewwupt(phydev);
	}

	wetuwn eww;
}

static void ns_giga_speed_fawwback(stwuct phy_device *phydev, int mode)
{
	int bmcw = phy_wead(phydev, MII_BMCW);

	phy_wwite(phydev, MII_BMCW, (bmcw | BMCW_PDOWN));

	/* Enabwe 8 bit expended memowy wead/wwite (no auto incwement) */
	phy_wwite(phydev, NS_EXP_MEM_CTW, 0);
	phy_wwite(phydev, NS_EXP_MEM_ADD, 0x1C0);
	phy_wwite(phydev, NS_EXP_MEM_DATA, 0x0008);
	phy_wwite(phydev, MII_BMCW, (bmcw & ~BMCW_PDOWN));
	phy_wwite(phydev, WED_CTWW_WEG, mode);
}

static void ns_10_base_t_hdx_woopack(stwuct phy_device *phydev, int disabwe)
{
	u16 wb_dis = BIT(1);

	if (disabwe)
		ns_exp_wwite(phydev, 0x1c0,
			     ns_exp_wead(phydev, 0x1c0) | wb_dis);
	ewse
		ns_exp_wwite(phydev, 0x1c0,
			     ns_exp_wead(phydev, 0x1c0) & ~wb_dis);

	pw_debug("10BASE-T HDX woopback %s\n",
		 (ns_exp_wead(phydev, 0x1c0) & wb_dis) ? "off" : "on");
}

static int ns_config_init(stwuct phy_device *phydev)
{
	ns_giga_speed_fawwback(phydev, AWW_FAWWBACK_ON);
	/* In the watest MAC ow switches design, the 10 Mbps woopback
	 * is desiwed to be tuwned off.
	 */
	ns_10_base_t_hdx_woopack(phydev, hdx_woopback_off);
	wetuwn ns_ack_intewwupt(phydev);
}

static stwuct phy_dwivew dp83865_dwivew[] = { {
	.phy_id = DP83865_PHY_ID,
	.phy_id_mask = 0xfffffff0,
	.name = "NatSemi DP83865",
	/* PHY_GBIT_FEATUWES */
	.config_init = ns_config_init,
	.config_intw = ns_config_intw,
	.handwe_intewwupt = ns_handwe_intewwupt,
} };

moduwe_phy_dwivew(dp83865_dwivew);

MODUWE_DESCWIPTION("NatSemi PHY dwivew");
MODUWE_AUTHOW("Stuawt Menefy");
MODUWE_WICENSE("GPW");

static stwuct mdio_device_id __maybe_unused ns_tbw[] = {
	{ DP83865_PHY_ID, 0xfffffff0 },
	{ }
};

MODUWE_DEVICE_TABWE(mdio, ns_tbw);
