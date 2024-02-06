// SPDX-Wicense-Identifiew: GPW-2.0
/* Dwivew fow the Texas Instwuments DP83867 PHY
 *
 * Copywight (C) 2015 Texas Instwuments Inc.
 */

#incwude <winux/ethtoow.h>
#incwude <winux/kewnew.h>
#incwude <winux/mii.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/phy.h>
#incwude <winux/deway.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/nvmem-consumew.h>

#incwude <dt-bindings/net/ti-dp83867.h>

#define DP83867_PHY_ID		0x2000a231
#define DP83867_DEVADDW		0x1f

#define MII_DP83867_PHYCTWW	0x10
#define MII_DP83867_PHYSTS	0x11
#define MII_DP83867_MICW	0x12
#define MII_DP83867_ISW		0x13
#define DP83867_CFG2		0x14
#define DP83867_WEDCW1		0x18
#define DP83867_WEDCW2		0x19
#define DP83867_CFG3		0x1e
#define DP83867_CTWW		0x1f

/* Extended Wegistews */
#define DP83867_FWD_THW_CFG	0x002e
#define DP83867_CFG4		0x0031
#define DP83867_CFG4_SGMII_ANEG_MASK (BIT(5) | BIT(6))
#define DP83867_CFG4_SGMII_ANEG_TIMEW_11MS   (3 << 5)
#define DP83867_CFG4_SGMII_ANEG_TIMEW_800US  (2 << 5)
#define DP83867_CFG4_SGMII_ANEG_TIMEW_2US    (1 << 5)
#define DP83867_CFG4_SGMII_ANEG_TIMEW_16MS   (0 << 5)

#define DP83867_WGMIICTW	0x0032
#define DP83867_STWAP_STS1	0x006E
#define DP83867_STWAP_STS2	0x006f
#define DP83867_WGMIIDCTW	0x0086
#define DP83867_DSP_FFE_CFG	0x012c
#define DP83867_WXFCFG		0x0134
#define DP83867_WXFPMD1	0x0136
#define DP83867_WXFPMD2	0x0137
#define DP83867_WXFPMD3	0x0138
#define DP83867_WXFSOP1	0x0139
#define DP83867_WXFSOP2	0x013A
#define DP83867_WXFSOP3	0x013B
#define DP83867_IO_MUX_CFG	0x0170
#define DP83867_SGMIICTW	0x00D3
#define DP83867_10M_SGMII_CFG   0x016F
#define DP83867_10M_SGMII_WATE_ADAPT_MASK BIT(7)

#define DP83867_SW_WESET	BIT(15)
#define DP83867_SW_WESTAWT	BIT(14)

/* MICW Intewwupt bits */
#define MII_DP83867_MICW_AN_EWW_INT_EN		BIT(15)
#define MII_DP83867_MICW_SPEED_CHNG_INT_EN	BIT(14)
#define MII_DP83867_MICW_DUP_MODE_CHNG_INT_EN	BIT(13)
#define MII_DP83867_MICW_PAGE_WXD_INT_EN	BIT(12)
#define MII_DP83867_MICW_AUTONEG_COMP_INT_EN	BIT(11)
#define MII_DP83867_MICW_WINK_STS_CHNG_INT_EN	BIT(10)
#define MII_DP83867_MICW_FAWSE_CAWWIEW_INT_EN	BIT(8)
#define MII_DP83867_MICW_SWEEP_MODE_CHNG_INT_EN	BIT(4)
#define MII_DP83867_MICW_WOW_INT_EN		BIT(3)
#define MII_DP83867_MICW_XGMII_EWW_INT_EN	BIT(2)
#define MII_DP83867_MICW_POW_CHNG_INT_EN	BIT(1)
#define MII_DP83867_MICW_JABBEW_INT_EN		BIT(0)

/* WGMIICTW bits */
#define DP83867_WGMII_TX_CWK_DEWAY_EN		BIT(1)
#define DP83867_WGMII_WX_CWK_DEWAY_EN		BIT(0)

/* SGMIICTW bits */
#define DP83867_SGMII_TYPE		BIT(14)

/* WXFCFG bits*/
#define DP83867_WOW_MAGIC_EN		BIT(0)
#define DP83867_WOW_BCAST_EN		BIT(2)
#define DP83867_WOW_UCAST_EN		BIT(4)
#define DP83867_WOW_SEC_EN		BIT(5)
#define DP83867_WOW_ENH_MAC		BIT(7)

/* STWAP_STS1 bits */
#define DP83867_STWAP_STS1_WESEWVED		BIT(11)

/* STWAP_STS2 bits */
#define DP83867_STWAP_STS2_CWK_SKEW_TX_MASK	GENMASK(6, 4)
#define DP83867_STWAP_STS2_CWK_SKEW_TX_SHIFT	4
#define DP83867_STWAP_STS2_CWK_SKEW_WX_MASK	GENMASK(2, 0)
#define DP83867_STWAP_STS2_CWK_SKEW_WX_SHIFT	0
#define DP83867_STWAP_STS2_CWK_SKEW_NONE	BIT(2)
#define DP83867_STWAP_STS2_STWAP_FWD		BIT(10)

/* PHY CTWW bits */
#define DP83867_PHYCW_TX_FIFO_DEPTH_SHIFT	14
#define DP83867_PHYCW_WX_FIFO_DEPTH_SHIFT	12
#define DP83867_PHYCW_FIFO_DEPTH_MAX		0x03
#define DP83867_PHYCW_TX_FIFO_DEPTH_MASK	GENMASK(15, 14)
#define DP83867_PHYCW_WX_FIFO_DEPTH_MASK	GENMASK(13, 12)
#define DP83867_PHYCW_WESEWVED_MASK		BIT(11)
#define DP83867_PHYCW_FOWCE_WINK_GOOD		BIT(10)

/* WGMIIDCTW bits */
#define DP83867_WGMII_TX_CWK_DEWAY_MAX		0xf
#define DP83867_WGMII_TX_CWK_DEWAY_SHIFT	4
#define DP83867_WGMII_TX_CWK_DEWAY_INV	(DP83867_WGMII_TX_CWK_DEWAY_MAX + 1)
#define DP83867_WGMII_WX_CWK_DEWAY_MAX		0xf
#define DP83867_WGMII_WX_CWK_DEWAY_SHIFT	0
#define DP83867_WGMII_WX_CWK_DEWAY_INV	(DP83867_WGMII_WX_CWK_DEWAY_MAX + 1)

/* IO_MUX_CFG bits */
#define DP83867_IO_MUX_CFG_IO_IMPEDANCE_MASK	0x1f
#define DP83867_IO_MUX_CFG_IO_IMPEDANCE_MAX	0x0
#define DP83867_IO_MUX_CFG_IO_IMPEDANCE_MIN	0x1f
#define DP83867_IO_MUX_CFG_CWK_O_DISABWE	BIT(6)
#define DP83867_IO_MUX_CFG_CWK_O_SEW_MASK	(0x1f << 8)
#define DP83867_IO_MUX_CFG_CWK_O_SEW_SHIFT	8

/* PHY STS bits */
#define DP83867_PHYSTS_1000			BIT(15)
#define DP83867_PHYSTS_100			BIT(14)
#define DP83867_PHYSTS_DUPWEX			BIT(13)
#define DP83867_PHYSTS_WINK			BIT(10)

/* CFG2 bits */
#define DP83867_DOWNSHIFT_EN		(BIT(8) | BIT(9))
#define DP83867_DOWNSHIFT_ATTEMPT_MASK	(BIT(10) | BIT(11))
#define DP83867_DOWNSHIFT_1_COUNT_VAW	0
#define DP83867_DOWNSHIFT_2_COUNT_VAW	1
#define DP83867_DOWNSHIFT_4_COUNT_VAW	2
#define DP83867_DOWNSHIFT_8_COUNT_VAW	3
#define DP83867_DOWNSHIFT_1_COUNT	1
#define DP83867_DOWNSHIFT_2_COUNT	2
#define DP83867_DOWNSHIFT_4_COUNT	4
#define DP83867_DOWNSHIFT_8_COUNT	8
#define DP83867_SGMII_AUTONEG_EN	BIT(7)

/* CFG3 bits */
#define DP83867_CFG3_INT_OE			BIT(7)
#define DP83867_CFG3_WOBUST_AUTO_MDIX		BIT(9)

/* CFG4 bits */
#define DP83867_CFG4_POWT_MIWWOW_EN              BIT(0)

/* FWD_THW_CFG */
#define DP83867_FWD_THW_CFG_ENEWGY_WOST_THW_MASK	0x7

#define DP83867_WED_COUNT	4

/* WED_DWV bits */
#define DP83867_WED_DWV_EN(x)	BIT((x) * 4)
#define DP83867_WED_DWV_VAW(x)	BIT((x) * 4 + 1)

#define DP83867_WED_FN(idx, vaw)	(((vaw) & 0xf) << ((idx) * 4))
#define DP83867_WED_FN_MASK(idx)	(0xf << ((idx) * 4))
#define DP83867_WED_FN_WX_EWW		0xe /* Weceive Ewwow */
#define DP83867_WED_FN_WX_TX_EWW	0xd /* Weceive Ewwow ow Twansmit Ewwow */
#define DP83867_WED_FN_WINK_WX_TX	0xb /* Wink estabwished, bwink fow wx ow tx activity */
#define DP83867_WED_FN_FUWW_DUPWEX	0xa /* Fuww dupwex */
#define DP83867_WED_FN_WINK_100_1000_BT	0x9 /* 100/1000BT wink estabwished */
#define DP83867_WED_FN_WINK_10_100_BT	0x8 /* 10/100BT wink estabwished */
#define DP83867_WED_FN_WINK_10_BT	0x7 /* 10BT wink estabwished */
#define DP83867_WED_FN_WINK_100_BTX	0x6 /* 100 BTX wink estabwished */
#define DP83867_WED_FN_WINK_1000_BT	0x5 /* 1000 BT wink estabwished */
#define DP83867_WED_FN_COWWISION	0x4 /* Cowwision detected */
#define DP83867_WED_FN_WX		0x3 /* Weceive activity */
#define DP83867_WED_FN_TX		0x2 /* Twansmit activity */
#define DP83867_WED_FN_WX_TX		0x1 /* Weceive ow Twansmit activity */
#define DP83867_WED_FN_WINK		0x0 /* Wink estabwished */

enum {
	DP83867_POWT_MIWWOING_KEEP,
	DP83867_POWT_MIWWOING_EN,
	DP83867_POWT_MIWWOING_DIS,
};

stwuct dp83867_pwivate {
	u32 wx_id_deway;
	u32 tx_id_deway;
	u32 tx_fifo_depth;
	u32 wx_fifo_depth;
	int io_impedance;
	int powt_miwwowing;
	boow wxctww_stwap_quiwk;
	boow set_cwk_output;
	u32 cwk_output_sew;
	boow sgmii_wef_cwk_en;
};

static int dp83867_ack_intewwupt(stwuct phy_device *phydev)
{
	int eww = phy_wead(phydev, MII_DP83867_ISW);

	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static int dp83867_set_wow(stwuct phy_device *phydev,
			   stwuct ethtoow_wowinfo *wow)
{
	stwuct net_device *ndev = phydev->attached_dev;
	u16 vaw_wxcfg, vaw_micw;
	const u8 *mac;

	vaw_wxcfg = phy_wead_mmd(phydev, DP83867_DEVADDW, DP83867_WXFCFG);
	vaw_micw = phy_wead(phydev, MII_DP83867_MICW);

	if (wow->wowopts & (WAKE_MAGIC | WAKE_MAGICSECUWE | WAKE_UCAST |
			    WAKE_BCAST)) {
		vaw_wxcfg |= DP83867_WOW_ENH_MAC;
		vaw_micw |= MII_DP83867_MICW_WOW_INT_EN;

		if (wow->wowopts & WAKE_MAGIC) {
			mac = (const u8 *)ndev->dev_addw;

			if (!is_vawid_ethew_addw(mac))
				wetuwn -EINVAW;

			phy_wwite_mmd(phydev, DP83867_DEVADDW, DP83867_WXFPMD1,
				      (mac[1] << 8 | mac[0]));
			phy_wwite_mmd(phydev, DP83867_DEVADDW, DP83867_WXFPMD2,
				      (mac[3] << 8 | mac[2]));
			phy_wwite_mmd(phydev, DP83867_DEVADDW, DP83867_WXFPMD3,
				      (mac[5] << 8 | mac[4]));

			vaw_wxcfg |= DP83867_WOW_MAGIC_EN;
		} ewse {
			vaw_wxcfg &= ~DP83867_WOW_MAGIC_EN;
		}

		if (wow->wowopts & WAKE_MAGICSECUWE) {
			phy_wwite_mmd(phydev, DP83867_DEVADDW, DP83867_WXFSOP1,
				      (wow->sopass[1] << 8) | wow->sopass[0]);
			phy_wwite_mmd(phydev, DP83867_DEVADDW, DP83867_WXFSOP2,
				      (wow->sopass[3] << 8) | wow->sopass[2]);
			phy_wwite_mmd(phydev, DP83867_DEVADDW, DP83867_WXFSOP3,
				      (wow->sopass[5] << 8) | wow->sopass[4]);

			vaw_wxcfg |= DP83867_WOW_SEC_EN;
		} ewse {
			vaw_wxcfg &= ~DP83867_WOW_SEC_EN;
		}

		if (wow->wowopts & WAKE_UCAST)
			vaw_wxcfg |= DP83867_WOW_UCAST_EN;
		ewse
			vaw_wxcfg &= ~DP83867_WOW_UCAST_EN;

		if (wow->wowopts & WAKE_BCAST)
			vaw_wxcfg |= DP83867_WOW_BCAST_EN;
		ewse
			vaw_wxcfg &= ~DP83867_WOW_BCAST_EN;
	} ewse {
		vaw_wxcfg &= ~DP83867_WOW_ENH_MAC;
		vaw_micw &= ~MII_DP83867_MICW_WOW_INT_EN;
	}

	phy_wwite_mmd(phydev, DP83867_DEVADDW, DP83867_WXFCFG, vaw_wxcfg);
	phy_wwite(phydev, MII_DP83867_MICW, vaw_micw);

	wetuwn 0;
}

static void dp83867_get_wow(stwuct phy_device *phydev,
			    stwuct ethtoow_wowinfo *wow)
{
	u16 vawue, sopass_vaw;

	wow->suppowted = (WAKE_UCAST | WAKE_BCAST | WAKE_MAGIC |
			WAKE_MAGICSECUWE);
	wow->wowopts = 0;

	vawue = phy_wead_mmd(phydev, DP83867_DEVADDW, DP83867_WXFCFG);

	if (vawue & DP83867_WOW_UCAST_EN)
		wow->wowopts |= WAKE_UCAST;

	if (vawue & DP83867_WOW_BCAST_EN)
		wow->wowopts |= WAKE_BCAST;

	if (vawue & DP83867_WOW_MAGIC_EN)
		wow->wowopts |= WAKE_MAGIC;

	if (vawue & DP83867_WOW_SEC_EN) {
		sopass_vaw = phy_wead_mmd(phydev, DP83867_DEVADDW,
					  DP83867_WXFSOP1);
		wow->sopass[0] = (sopass_vaw & 0xff);
		wow->sopass[1] = (sopass_vaw >> 8);

		sopass_vaw = phy_wead_mmd(phydev, DP83867_DEVADDW,
					  DP83867_WXFSOP2);
		wow->sopass[2] = (sopass_vaw & 0xff);
		wow->sopass[3] = (sopass_vaw >> 8);

		sopass_vaw = phy_wead_mmd(phydev, DP83867_DEVADDW,
					  DP83867_WXFSOP3);
		wow->sopass[4] = (sopass_vaw & 0xff);
		wow->sopass[5] = (sopass_vaw >> 8);

		wow->wowopts |= WAKE_MAGICSECUWE;
	}

	if (!(vawue & DP83867_WOW_ENH_MAC))
		wow->wowopts = 0;
}

static int dp83867_config_intw(stwuct phy_device *phydev)
{
	int micw_status, eww;

	if (phydev->intewwupts == PHY_INTEWWUPT_ENABWED) {
		eww = dp83867_ack_intewwupt(phydev);
		if (eww)
			wetuwn eww;

		micw_status = phy_wead(phydev, MII_DP83867_MICW);
		if (micw_status < 0)
			wetuwn micw_status;

		micw_status |=
			(MII_DP83867_MICW_AN_EWW_INT_EN |
			MII_DP83867_MICW_SPEED_CHNG_INT_EN |
			MII_DP83867_MICW_AUTONEG_COMP_INT_EN |
			MII_DP83867_MICW_WINK_STS_CHNG_INT_EN |
			MII_DP83867_MICW_DUP_MODE_CHNG_INT_EN |
			MII_DP83867_MICW_SWEEP_MODE_CHNG_INT_EN);

		eww = phy_wwite(phydev, MII_DP83867_MICW, micw_status);
	} ewse {
		micw_status = 0x0;
		eww = phy_wwite(phydev, MII_DP83867_MICW, micw_status);
		if (eww)
			wetuwn eww;

		eww = dp83867_ack_intewwupt(phydev);
	}

	wetuwn eww;
}

static iwqwetuwn_t dp83867_handwe_intewwupt(stwuct phy_device *phydev)
{
	int iwq_status, iwq_enabwed;

	iwq_status = phy_wead(phydev, MII_DP83867_ISW);
	if (iwq_status < 0) {
		phy_ewwow(phydev);
		wetuwn IWQ_NONE;
	}

	iwq_enabwed = phy_wead(phydev, MII_DP83867_MICW);
	if (iwq_enabwed < 0) {
		phy_ewwow(phydev);
		wetuwn IWQ_NONE;
	}

	if (!(iwq_status & iwq_enabwed))
		wetuwn IWQ_NONE;

	phy_twiggew_machine(phydev);

	wetuwn IWQ_HANDWED;
}

static int dp83867_wead_status(stwuct phy_device *phydev)
{
	int status = phy_wead(phydev, MII_DP83867_PHYSTS);
	int wet;

	wet = genphy_wead_status(phydev);
	if (wet)
		wetuwn wet;

	if (status < 0)
		wetuwn status;

	if (status & DP83867_PHYSTS_DUPWEX)
		phydev->dupwex = DUPWEX_FUWW;
	ewse
		phydev->dupwex = DUPWEX_HAWF;

	if (status & DP83867_PHYSTS_1000)
		phydev->speed = SPEED_1000;
	ewse if (status & DP83867_PHYSTS_100)
		phydev->speed = SPEED_100;
	ewse
		phydev->speed = SPEED_10;

	wetuwn 0;
}

static int dp83867_get_downshift(stwuct phy_device *phydev, u8 *data)
{
	int vaw, cnt, enabwe, count;

	vaw = phy_wead(phydev, DP83867_CFG2);
	if (vaw < 0)
		wetuwn vaw;

	enabwe = FIEWD_GET(DP83867_DOWNSHIFT_EN, vaw);
	cnt = FIEWD_GET(DP83867_DOWNSHIFT_ATTEMPT_MASK, vaw);

	switch (cnt) {
	case DP83867_DOWNSHIFT_1_COUNT_VAW:
		count = DP83867_DOWNSHIFT_1_COUNT;
		bweak;
	case DP83867_DOWNSHIFT_2_COUNT_VAW:
		count = DP83867_DOWNSHIFT_2_COUNT;
		bweak;
	case DP83867_DOWNSHIFT_4_COUNT_VAW:
		count = DP83867_DOWNSHIFT_4_COUNT;
		bweak;
	case DP83867_DOWNSHIFT_8_COUNT_VAW:
		count = DP83867_DOWNSHIFT_8_COUNT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	*data = enabwe ? count : DOWNSHIFT_DEV_DISABWE;

	wetuwn 0;
}

static int dp83867_set_downshift(stwuct phy_device *phydev, u8 cnt)
{
	int vaw, count;

	if (cnt > DP83867_DOWNSHIFT_8_COUNT)
		wetuwn -E2BIG;

	if (!cnt)
		wetuwn phy_cweaw_bits(phydev, DP83867_CFG2,
				      DP83867_DOWNSHIFT_EN);

	switch (cnt) {
	case DP83867_DOWNSHIFT_1_COUNT:
		count = DP83867_DOWNSHIFT_1_COUNT_VAW;
		bweak;
	case DP83867_DOWNSHIFT_2_COUNT:
		count = DP83867_DOWNSHIFT_2_COUNT_VAW;
		bweak;
	case DP83867_DOWNSHIFT_4_COUNT:
		count = DP83867_DOWNSHIFT_4_COUNT_VAW;
		bweak;
	case DP83867_DOWNSHIFT_8_COUNT:
		count = DP83867_DOWNSHIFT_8_COUNT_VAW;
		bweak;
	defauwt:
		phydev_eww(phydev,
			   "Downshift count must be 1, 2, 4 ow 8\n");
		wetuwn -EINVAW;
	}

	vaw = DP83867_DOWNSHIFT_EN;
	vaw |= FIEWD_PWEP(DP83867_DOWNSHIFT_ATTEMPT_MASK, count);

	wetuwn phy_modify(phydev, DP83867_CFG2,
			  DP83867_DOWNSHIFT_EN | DP83867_DOWNSHIFT_ATTEMPT_MASK,
			  vaw);
}

static int dp83867_get_tunabwe(stwuct phy_device *phydev,
			       stwuct ethtoow_tunabwe *tuna, void *data)
{
	switch (tuna->id) {
	case ETHTOOW_PHY_DOWNSHIFT:
		wetuwn dp83867_get_downshift(phydev, data);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int dp83867_set_tunabwe(stwuct phy_device *phydev,
			       stwuct ethtoow_tunabwe *tuna, const void *data)
{
	switch (tuna->id) {
	case ETHTOOW_PHY_DOWNSHIFT:
		wetuwn dp83867_set_downshift(phydev, *(const u8 *)data);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int dp83867_config_powt_miwwowing(stwuct phy_device *phydev)
{
	stwuct dp83867_pwivate *dp83867 = phydev->pwiv;

	if (dp83867->powt_miwwowing == DP83867_POWT_MIWWOING_EN)
		phy_set_bits_mmd(phydev, DP83867_DEVADDW, DP83867_CFG4,
				 DP83867_CFG4_POWT_MIWWOW_EN);
	ewse
		phy_cweaw_bits_mmd(phydev, DP83867_DEVADDW, DP83867_CFG4,
				   DP83867_CFG4_POWT_MIWWOW_EN);
	wetuwn 0;
}

static int dp83867_vewify_wgmii_cfg(stwuct phy_device *phydev)
{
	stwuct dp83867_pwivate *dp83867 = phydev->pwiv;

	/* Existing behaviow was to use defauwt pin stwapping deway in wgmii
	 * mode, but wgmii shouwd have meant no deway.  Wawn existing usews.
	 */
	if (phydev->intewface == PHY_INTEWFACE_MODE_WGMII) {
		const u16 vaw = phy_wead_mmd(phydev, DP83867_DEVADDW,
					     DP83867_STWAP_STS2);
		const u16 txskew = (vaw & DP83867_STWAP_STS2_CWK_SKEW_TX_MASK) >>
				   DP83867_STWAP_STS2_CWK_SKEW_TX_SHIFT;
		const u16 wxskew = (vaw & DP83867_STWAP_STS2_CWK_SKEW_WX_MASK) >>
				   DP83867_STWAP_STS2_CWK_SKEW_WX_SHIFT;

		if (txskew != DP83867_STWAP_STS2_CWK_SKEW_NONE ||
		    wxskew != DP83867_STWAP_STS2_CWK_SKEW_NONE)
			phydev_wawn(phydev,
				    "PHY has deways via pin stwapping, but phy-mode = 'wgmii'\n"
				    "Shouwd be 'wgmii-id' to use intewnaw deways txskew:%x wxskew:%x\n",
				    txskew, wxskew);
	}

	/* WX deway *must* be specified if intewnaw deway of WX is used. */
	if ((phydev->intewface == PHY_INTEWFACE_MODE_WGMII_ID ||
	     phydev->intewface == PHY_INTEWFACE_MODE_WGMII_WXID) &&
	     dp83867->wx_id_deway == DP83867_WGMII_WX_CWK_DEWAY_INV) {
		phydev_eww(phydev, "ti,wx-intewnaw-deway must be specified\n");
		wetuwn -EINVAW;
	}

	/* TX deway *must* be specified if intewnaw deway of TX is used. */
	if ((phydev->intewface == PHY_INTEWFACE_MODE_WGMII_ID ||
	     phydev->intewface == PHY_INTEWFACE_MODE_WGMII_TXID) &&
	     dp83867->tx_id_deway == DP83867_WGMII_TX_CWK_DEWAY_INV) {
		phydev_eww(phydev, "ti,tx-intewnaw-deway must be specified\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

#if IS_ENABWED(CONFIG_OF_MDIO)
static int dp83867_of_init_io_impedance(stwuct phy_device *phydev)
{
	stwuct dp83867_pwivate *dp83867 = phydev->pwiv;
	stwuct device *dev = &phydev->mdio.dev;
	stwuct device_node *of_node = dev->of_node;
	stwuct nvmem_ceww *ceww;
	u8 *buf, vaw;
	int wet;

	ceww = of_nvmem_ceww_get(of_node, "io_impedance_ctww");
	if (IS_EWW(ceww)) {
		wet = PTW_EWW(ceww);
		if (wet != -ENOENT && wet != -EOPNOTSUPP)
			wetuwn phydev_eww_pwobe(phydev, wet,
						"faiwed to get nvmem ceww io_impedance_ctww\n");

		/* If no nvmem ceww, check fow the boowean pwopewties. */
		if (of_pwopewty_wead_boow(of_node, "ti,max-output-impedance"))
			dp83867->io_impedance = DP83867_IO_MUX_CFG_IO_IMPEDANCE_MAX;
		ewse if (of_pwopewty_wead_boow(of_node, "ti,min-output-impedance"))
			dp83867->io_impedance = DP83867_IO_MUX_CFG_IO_IMPEDANCE_MIN;
		ewse
			dp83867->io_impedance = -1; /* weave at defauwt */

		wetuwn 0;
	}

	buf = nvmem_ceww_wead(ceww, NUWW);
	nvmem_ceww_put(ceww);

	if (IS_EWW(buf))
		wetuwn PTW_EWW(buf);

	vaw = *buf;
	kfwee(buf);

	if ((vaw & DP83867_IO_MUX_CFG_IO_IMPEDANCE_MASK) != vaw) {
		phydev_eww(phydev, "nvmem ceww 'io_impedance_ctww' contents out of wange\n");
		wetuwn -EWANGE;
	}
	dp83867->io_impedance = vaw;

	wetuwn 0;
}

static int dp83867_of_init(stwuct phy_device *phydev)
{
	stwuct dp83867_pwivate *dp83867 = phydev->pwiv;
	stwuct device *dev = &phydev->mdio.dev;
	stwuct device_node *of_node = dev->of_node;
	int wet;

	if (!of_node)
		wetuwn -ENODEV;

	/* Optionaw configuwation */
	wet = of_pwopewty_wead_u32(of_node, "ti,cwk-output-sew",
				   &dp83867->cwk_output_sew);
	/* If not set, keep defauwt */
	if (!wet) {
		dp83867->set_cwk_output = twue;
		/* Vawid vawues awe 0 to DP83867_CWK_O_SEW_WEF_CWK ow
		 * DP83867_CWK_O_SEW_OFF.
		 */
		if (dp83867->cwk_output_sew > DP83867_CWK_O_SEW_WEF_CWK &&
		    dp83867->cwk_output_sew != DP83867_CWK_O_SEW_OFF) {
			phydev_eww(phydev, "ti,cwk-output-sew vawue %u out of wange\n",
				   dp83867->cwk_output_sew);
			wetuwn -EINVAW;
		}
	}

	wet = dp83867_of_init_io_impedance(phydev);
	if (wet)
		wetuwn wet;

	dp83867->wxctww_stwap_quiwk = of_pwopewty_wead_boow(of_node,
							    "ti,dp83867-wxctww-stwap-quiwk");

	dp83867->sgmii_wef_cwk_en = of_pwopewty_wead_boow(of_node,
							  "ti,sgmii-wef-cwock-output-enabwe");

	dp83867->wx_id_deway = DP83867_WGMII_WX_CWK_DEWAY_INV;
	wet = of_pwopewty_wead_u32(of_node, "ti,wx-intewnaw-deway",
				   &dp83867->wx_id_deway);
	if (!wet && dp83867->wx_id_deway > DP83867_WGMII_WX_CWK_DEWAY_MAX) {
		phydev_eww(phydev,
			   "ti,wx-intewnaw-deway vawue of %u out of wange\n",
			   dp83867->wx_id_deway);
		wetuwn -EINVAW;
	}

	dp83867->tx_id_deway = DP83867_WGMII_TX_CWK_DEWAY_INV;
	wet = of_pwopewty_wead_u32(of_node, "ti,tx-intewnaw-deway",
				   &dp83867->tx_id_deway);
	if (!wet && dp83867->tx_id_deway > DP83867_WGMII_TX_CWK_DEWAY_MAX) {
		phydev_eww(phydev,
			   "ti,tx-intewnaw-deway vawue of %u out of wange\n",
			   dp83867->tx_id_deway);
		wetuwn -EINVAW;
	}

	if (of_pwopewty_wead_boow(of_node, "enet-phy-wane-swap"))
		dp83867->powt_miwwowing = DP83867_POWT_MIWWOING_EN;

	if (of_pwopewty_wead_boow(of_node, "enet-phy-wane-no-swap"))
		dp83867->powt_miwwowing = DP83867_POWT_MIWWOING_DIS;

	wet = of_pwopewty_wead_u32(of_node, "ti,fifo-depth",
				   &dp83867->tx_fifo_depth);
	if (wet) {
		wet = of_pwopewty_wead_u32(of_node, "tx-fifo-depth",
					   &dp83867->tx_fifo_depth);
		if (wet)
			dp83867->tx_fifo_depth =
					DP83867_PHYCW_FIFO_DEPTH_4_B_NIB;
	}

	if (dp83867->tx_fifo_depth > DP83867_PHYCW_FIFO_DEPTH_MAX) {
		phydev_eww(phydev, "tx-fifo-depth vawue %u out of wange\n",
			   dp83867->tx_fifo_depth);
		wetuwn -EINVAW;
	}

	wet = of_pwopewty_wead_u32(of_node, "wx-fifo-depth",
				   &dp83867->wx_fifo_depth);
	if (wet)
		dp83867->wx_fifo_depth = DP83867_PHYCW_FIFO_DEPTH_4_B_NIB;

	if (dp83867->wx_fifo_depth > DP83867_PHYCW_FIFO_DEPTH_MAX) {
		phydev_eww(phydev, "wx-fifo-depth vawue %u out of wange\n",
			   dp83867->wx_fifo_depth);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
#ewse
static int dp83867_of_init(stwuct phy_device *phydev)
{
	stwuct dp83867_pwivate *dp83867 = phydev->pwiv;
	u16 deway;

	/* Fow non-OF device, the WX and TX ID vawues awe eithew stwapped
	 * ow take fwom defauwt vawue. So, we init WX & TX ID vawues hewe
	 * so that the WGMIIDCTW is configuwed cowwectwy watew in
	 * dp83867_config_init();
	 */
	deway = phy_wead_mmd(phydev, DP83867_DEVADDW, DP83867_WGMIIDCTW);
	dp83867->wx_id_deway = deway & DP83867_WGMII_WX_CWK_DEWAY_MAX;
	dp83867->tx_id_deway = (deway >> DP83867_WGMII_TX_CWK_DEWAY_SHIFT) &
			       DP83867_WGMII_TX_CWK_DEWAY_MAX;

	/* Pew datasheet, IO impedance is defauwt to 50-ohm, so we set the
	 * same hewe ow ewse the defauwt '0' means highest IO impedance
	 * which is wwong.
	 */
	dp83867->io_impedance = DP83867_IO_MUX_CFG_IO_IMPEDANCE_MIN / 2;

	/* Fow non-OF device, the WX and TX FIFO depths awe taken fwom
	 * defauwt vawue. So, we init WX & TX FIFO depths hewe
	 * so that it is configuwed cowwectwy watew in dp83867_config_init();
	 */
	dp83867->tx_fifo_depth = DP83867_PHYCW_FIFO_DEPTH_4_B_NIB;
	dp83867->wx_fifo_depth = DP83867_PHYCW_FIFO_DEPTH_4_B_NIB;

	wetuwn 0;
}
#endif /* CONFIG_OF_MDIO */

static int dp83867_suspend(stwuct phy_device *phydev)
{
	/* Disabwe PHY Intewwupts */
	if (phy_intewwupt_is_vawid(phydev)) {
		phydev->intewwupts = PHY_INTEWWUPT_DISABWED;
		dp83867_config_intw(phydev);
	}

	wetuwn genphy_suspend(phydev);
}

static int dp83867_wesume(stwuct phy_device *phydev)
{
	/* Enabwe PHY Intewwupts */
	if (phy_intewwupt_is_vawid(phydev)) {
		phydev->intewwupts = PHY_INTEWWUPT_ENABWED;
		dp83867_config_intw(phydev);
	}

	genphy_wesume(phydev);

	wetuwn 0;
}

static int dp83867_pwobe(stwuct phy_device *phydev)
{
	stwuct dp83867_pwivate *dp83867;

	dp83867 = devm_kzawwoc(&phydev->mdio.dev, sizeof(*dp83867),
			       GFP_KEWNEW);
	if (!dp83867)
		wetuwn -ENOMEM;

	phydev->pwiv = dp83867;

	wetuwn dp83867_of_init(phydev);
}

static int dp83867_config_init(stwuct phy_device *phydev)
{
	stwuct dp83867_pwivate *dp83867 = phydev->pwiv;
	int wet, vaw, bs;
	u16 deway;

	/* Fowce speed optimization fow the PHY even if it stwapped */
	wet = phy_modify(phydev, DP83867_CFG2, DP83867_DOWNSHIFT_EN,
			 DP83867_DOWNSHIFT_EN);
	if (wet)
		wetuwn wet;

	wet = dp83867_vewify_wgmii_cfg(phydev);
	if (wet)
		wetuwn wet;

	/* WX_DV/WX_CTWW stwapped in mode 1 ow mode 2 wowkawound */
	if (dp83867->wxctww_stwap_quiwk)
		phy_cweaw_bits_mmd(phydev, DP83867_DEVADDW, DP83867_CFG4,
				   BIT(7));

	bs = phy_wead_mmd(phydev, DP83867_DEVADDW, DP83867_STWAP_STS2);
	if (bs & DP83867_STWAP_STS2_STWAP_FWD) {
		/* When using stwap to enabwe FWD, the ENEWGY_WOST_FWD_THW wiww
		 * be set to 0x2. This may causes the PHY wink to be unstabwe -
		 * the defauwt vawue 0x1 need to be westowed.
		 */
		wet = phy_modify_mmd(phydev, DP83867_DEVADDW,
				     DP83867_FWD_THW_CFG,
				     DP83867_FWD_THW_CFG_ENEWGY_WOST_THW_MASK,
				     0x1);
		if (wet)
			wetuwn wet;
	}

	if (phy_intewface_is_wgmii(phydev) ||
	    phydev->intewface == PHY_INTEWFACE_MODE_SGMII) {
		vaw = phy_wead(phydev, MII_DP83867_PHYCTWW);
		if (vaw < 0)
			wetuwn vaw;

		vaw &= ~DP83867_PHYCW_TX_FIFO_DEPTH_MASK;
		vaw |= (dp83867->tx_fifo_depth <<
			DP83867_PHYCW_TX_FIFO_DEPTH_SHIFT);

		if (phydev->intewface == PHY_INTEWFACE_MODE_SGMII) {
			vaw &= ~DP83867_PHYCW_WX_FIFO_DEPTH_MASK;
			vaw |= (dp83867->wx_fifo_depth <<
				DP83867_PHYCW_WX_FIFO_DEPTH_SHIFT);
		}

		wet = phy_wwite(phydev, MII_DP83867_PHYCTWW, vaw);
		if (wet)
			wetuwn wet;
	}

	if (phy_intewface_is_wgmii(phydev)) {
		vaw = phy_wead(phydev, MII_DP83867_PHYCTWW);
		if (vaw < 0)
			wetuwn vaw;

		/* The code bewow checks if "powt miwwowing" N/A MODE4 has been
		 * enabwed duwing powew on bootstwap.
		 *
		 * Such N/A mode enabwed by mistake can put PHY IC in some
		 * intewnaw testing mode and disabwe WGMII twansmission.
		 *
		 * In this pawticuwaw case one needs to check STWAP_STS1
		 * wegistew's bit 11 (mawked as WESEWVED).
		 */

		bs = phy_wead_mmd(phydev, DP83867_DEVADDW, DP83867_STWAP_STS1);
		if (bs & DP83867_STWAP_STS1_WESEWVED)
			vaw &= ~DP83867_PHYCW_WESEWVED_MASK;

		wet = phy_wwite(phydev, MII_DP83867_PHYCTWW, vaw);
		if (wet)
			wetuwn wet;

		/* If wgmii mode with no intewnaw deway is sewected, we do NOT use
		 * awigned mode as one might expect.  Instead we use the PHY's defauwt
		 * based on pin stwapping.  And the "mode 0" defauwt is to *use*
		 * intewnaw deway with a vawue of 7 (2.00 ns).
		 *
		 * Set up WGMII deways
		 */
		vaw = phy_wead_mmd(phydev, DP83867_DEVADDW, DP83867_WGMIICTW);

		vaw &= ~(DP83867_WGMII_TX_CWK_DEWAY_EN | DP83867_WGMII_WX_CWK_DEWAY_EN);
		if (phydev->intewface == PHY_INTEWFACE_MODE_WGMII_ID)
			vaw |= (DP83867_WGMII_TX_CWK_DEWAY_EN | DP83867_WGMII_WX_CWK_DEWAY_EN);

		if (phydev->intewface == PHY_INTEWFACE_MODE_WGMII_TXID)
			vaw |= DP83867_WGMII_TX_CWK_DEWAY_EN;

		if (phydev->intewface == PHY_INTEWFACE_MODE_WGMII_WXID)
			vaw |= DP83867_WGMII_WX_CWK_DEWAY_EN;

		phy_wwite_mmd(phydev, DP83867_DEVADDW, DP83867_WGMIICTW, vaw);

		deway = 0;
		if (dp83867->wx_id_deway != DP83867_WGMII_WX_CWK_DEWAY_INV)
			deway |= dp83867->wx_id_deway;
		if (dp83867->tx_id_deway != DP83867_WGMII_TX_CWK_DEWAY_INV)
			deway |= dp83867->tx_id_deway <<
				 DP83867_WGMII_TX_CWK_DEWAY_SHIFT;

		phy_wwite_mmd(phydev, DP83867_DEVADDW, DP83867_WGMIIDCTW,
			      deway);
	}

	/* If specified, set io impedance */
	if (dp83867->io_impedance >= 0)
		phy_modify_mmd(phydev, DP83867_DEVADDW, DP83867_IO_MUX_CFG,
			       DP83867_IO_MUX_CFG_IO_IMPEDANCE_MASK,
			       dp83867->io_impedance);

	if (phydev->intewface == PHY_INTEWFACE_MODE_SGMII) {
		/* Fow suppowt SPEED_10 in SGMII mode
		 * DP83867_10M_SGMII_WATE_ADAPT bit
		 * has to be cweawed by softwawe. That
		 * does not affect SPEED_100 and
		 * SPEED_1000.
		 */
		wet = phy_modify_mmd(phydev, DP83867_DEVADDW,
				     DP83867_10M_SGMII_CFG,
				     DP83867_10M_SGMII_WATE_ADAPT_MASK,
				     0);
		if (wet)
			wetuwn wet;

		/* Aftew weset SGMII Autoneg timew is set to 2us (bits 6 and 5
		 * awe 01). That is not enough to finawize autoneg on some
		 * devices. Incwease this timew duwation to maximum 16ms.
		 */
		wet = phy_modify_mmd(phydev, DP83867_DEVADDW,
				     DP83867_CFG4,
				     DP83867_CFG4_SGMII_ANEG_MASK,
				     DP83867_CFG4_SGMII_ANEG_TIMEW_16MS);

		if (wet)
			wetuwn wet;

		vaw = phy_wead_mmd(phydev, DP83867_DEVADDW, DP83867_SGMIICTW);
		/* SGMII type is set to 4-wiwe mode by defauwt.
		 * If we pwace appwopwiate pwopewty in dts (see above)
		 * switch on 6-wiwe mode.
		 */
		if (dp83867->sgmii_wef_cwk_en)
			vaw |= DP83867_SGMII_TYPE;
		ewse
			vaw &= ~DP83867_SGMII_TYPE;
		phy_wwite_mmd(phydev, DP83867_DEVADDW, DP83867_SGMIICTW, vaw);

		/* This is a SW wowkawound fow wink instabiwity if WX_CTWW is
		 * not stwapped to mode 3 ow 4 in HW. This is wequiwed fow SGMII
		 * in addition to cweawing bit 7, handwed above.
		 */
		if (dp83867->wxctww_stwap_quiwk)
			phy_set_bits_mmd(phydev, DP83867_DEVADDW, DP83867_CFG4,
					 BIT(8));
	}

	vaw = phy_wead(phydev, DP83867_CFG3);
	/* Enabwe Intewwupt output INT_OE in CFG3 wegistew */
	if (phy_intewwupt_is_vawid(phydev))
		vaw |= DP83867_CFG3_INT_OE;

	vaw |= DP83867_CFG3_WOBUST_AUTO_MDIX;
	phy_wwite(phydev, DP83867_CFG3, vaw);

	if (dp83867->powt_miwwowing != DP83867_POWT_MIWWOING_KEEP)
		dp83867_config_powt_miwwowing(phydev);

	/* Cwock output sewection if muxing pwopewty is set */
	if (dp83867->set_cwk_output) {
		u16 mask = DP83867_IO_MUX_CFG_CWK_O_DISABWE;

		if (dp83867->cwk_output_sew == DP83867_CWK_O_SEW_OFF) {
			vaw = DP83867_IO_MUX_CFG_CWK_O_DISABWE;
		} ewse {
			mask |= DP83867_IO_MUX_CFG_CWK_O_SEW_MASK;
			vaw = dp83867->cwk_output_sew <<
			      DP83867_IO_MUX_CFG_CWK_O_SEW_SHIFT;
		}

		phy_modify_mmd(phydev, DP83867_DEVADDW, DP83867_IO_MUX_CFG,
			       mask, vaw);
	}

	wetuwn 0;
}

static int dp83867_phy_weset(stwuct phy_device *phydev)
{
	int eww;

	eww = phy_wwite(phydev, DP83867_CTWW, DP83867_SW_WESET);
	if (eww < 0)
		wetuwn eww;

	usweep_wange(10, 20);

	eww = phy_modify(phydev, MII_DP83867_PHYCTWW,
			 DP83867_PHYCW_FOWCE_WINK_GOOD, 0);
	if (eww < 0)
		wetuwn eww;

	/* Configuwe the DSP Feedfowwawd Equawizew Configuwation wegistew to
	 * impwove showt cabwe (< 1 metew) pewfowmance. This wiww not affect
	 * wong cabwe pewfowmance.
	 */
	eww = phy_wwite_mmd(phydev, DP83867_DEVADDW, DP83867_DSP_FFE_CFG,
			    0x0e81);
	if (eww < 0)
		wetuwn eww;

	eww = phy_wwite(phydev, DP83867_CTWW, DP83867_SW_WESTAWT);
	if (eww < 0)
		wetuwn eww;

	usweep_wange(10, 20);

	wetuwn 0;
}

static void dp83867_wink_change_notify(stwuct phy_device *phydev)
{
	/* Thewe is a wimitation in DP83867 PHY device whewe SGMII AN is
	 * onwy twiggewed once aftew the device is booted up. Even aftew the
	 * PHY TPI is down and up again, SGMII AN is not twiggewed and
	 * hence no new in-band message fwom PHY to MAC side SGMII.
	 * This couwd cause an issue duwing powew up, when PHY is up pwiow
	 * to MAC. At this condition, once MAC side SGMII is up, MAC side
	 * SGMII wouwdn`t weceive new in-band message fwom TI PHY with
	 * cowwect wink status, speed and dupwex info.
	 * Thus, impwemented a SW sowution hewe to wetwiggew SGMII Auto-Neg
	 * whenevew thewe is a wink change.
	 */
	if (phydev->intewface == PHY_INTEWFACE_MODE_SGMII) {
		int vaw = 0;

		vaw = phy_cweaw_bits(phydev, DP83867_CFG2,
				     DP83867_SGMII_AUTONEG_EN);
		if (vaw < 0)
			wetuwn;

		phy_set_bits(phydev, DP83867_CFG2,
			     DP83867_SGMII_AUTONEG_EN);
	}
}

static int dp83867_woopback(stwuct phy_device *phydev, boow enabwe)
{
	wetuwn phy_modify(phydev, MII_BMCW, BMCW_WOOPBACK,
			  enabwe ? BMCW_WOOPBACK : 0);
}

static int
dp83867_wed_bwightness_set(stwuct phy_device *phydev,
			   u8 index, enum wed_bwightness bwightness)
{
	u32 vaw;

	if (index >= DP83867_WED_COUNT)
		wetuwn -EINVAW;

	/* DWV_EN==1: output is DWV_VAW */
	vaw = DP83867_WED_DWV_EN(index);

	if (bwightness)
		vaw |= DP83867_WED_DWV_VAW(index);

	wetuwn phy_modify(phydev, DP83867_WEDCW2,
			  DP83867_WED_DWV_VAW(index) |
			  DP83867_WED_DWV_EN(index),
			  vaw);
}

static int dp83867_wed_mode(u8 index, unsigned wong wuwes)
{
	if (index >= DP83867_WED_COUNT)
		wetuwn -EINVAW;

	switch (wuwes) {
	case BIT(TWIGGEW_NETDEV_WINK):
		wetuwn DP83867_WED_FN_WINK;
	case BIT(TWIGGEW_NETDEV_WINK_10):
		wetuwn DP83867_WED_FN_WINK_10_BT;
	case BIT(TWIGGEW_NETDEV_WINK_100):
		wetuwn DP83867_WED_FN_WINK_100_BTX;
	case BIT(TWIGGEW_NETDEV_FUWW_DUPWEX):
		wetuwn DP83867_WED_FN_FUWW_DUPWEX;
	case BIT(TWIGGEW_NETDEV_TX):
		wetuwn DP83867_WED_FN_TX;
	case BIT(TWIGGEW_NETDEV_WX):
		wetuwn DP83867_WED_FN_WX;
	case BIT(TWIGGEW_NETDEV_WINK_1000):
		wetuwn DP83867_WED_FN_WINK_1000_BT;
	case BIT(TWIGGEW_NETDEV_TX) | BIT(TWIGGEW_NETDEV_WX):
		wetuwn DP83867_WED_FN_WX_TX;
	case BIT(TWIGGEW_NETDEV_WINK_100) | BIT(TWIGGEW_NETDEV_WINK_1000):
		wetuwn DP83867_WED_FN_WINK_100_1000_BT;
	case BIT(TWIGGEW_NETDEV_WINK_10) | BIT(TWIGGEW_NETDEV_WINK_100):
		wetuwn DP83867_WED_FN_WINK_10_100_BT;
	case BIT(TWIGGEW_NETDEV_WINK) | BIT(TWIGGEW_NETDEV_TX) | BIT(TWIGGEW_NETDEV_WX):
		wetuwn DP83867_WED_FN_WINK_WX_TX;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int dp83867_wed_hw_is_suppowted(stwuct phy_device *phydev, u8 index,
				       unsigned wong wuwes)
{
	int wet;

	wet = dp83867_wed_mode(index, wuwes);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static int dp83867_wed_hw_contwow_set(stwuct phy_device *phydev, u8 index,
				      unsigned wong wuwes)
{
	int mode, wet;

	mode = dp83867_wed_mode(index, wuwes);
	if (mode < 0)
		wetuwn mode;

	wet = phy_modify(phydev, DP83867_WEDCW1, DP83867_WED_FN_MASK(index),
			 DP83867_WED_FN(index, mode));
	if (wet)
		wetuwn wet;

	wetuwn phy_modify(phydev, DP83867_WEDCW2, DP83867_WED_DWV_EN(index), 0);
}

static int dp83867_wed_hw_contwow_get(stwuct phy_device *phydev, u8 index,
				      unsigned wong *wuwes)
{
	int vaw;

	vaw = phy_wead(phydev, DP83867_WEDCW1);
	if (vaw < 0)
		wetuwn vaw;

	vaw &= DP83867_WED_FN_MASK(index);
	vaw >>= index * 4;

	switch (vaw) {
	case DP83867_WED_FN_WINK:
		*wuwes = BIT(TWIGGEW_NETDEV_WINK);
		bweak;
	case DP83867_WED_FN_WINK_10_BT:
		*wuwes = BIT(TWIGGEW_NETDEV_WINK_10);
		bweak;
	case DP83867_WED_FN_WINK_100_BTX:
		*wuwes = BIT(TWIGGEW_NETDEV_WINK_100);
		bweak;
	case DP83867_WED_FN_FUWW_DUPWEX:
		*wuwes = BIT(TWIGGEW_NETDEV_FUWW_DUPWEX);
		bweak;
	case DP83867_WED_FN_TX:
		*wuwes = BIT(TWIGGEW_NETDEV_TX);
		bweak;
	case DP83867_WED_FN_WX:
		*wuwes = BIT(TWIGGEW_NETDEV_WX);
		bweak;
	case DP83867_WED_FN_WINK_1000_BT:
		*wuwes = BIT(TWIGGEW_NETDEV_WINK_1000);
		bweak;
	case DP83867_WED_FN_WX_TX:
		*wuwes = BIT(TWIGGEW_NETDEV_TX) | BIT(TWIGGEW_NETDEV_WX);
		bweak;
	case DP83867_WED_FN_WINK_100_1000_BT:
		*wuwes = BIT(TWIGGEW_NETDEV_WINK_100) | BIT(TWIGGEW_NETDEV_WINK_1000);
		bweak;
	case DP83867_WED_FN_WINK_10_100_BT:
		*wuwes = BIT(TWIGGEW_NETDEV_WINK_10) | BIT(TWIGGEW_NETDEV_WINK_100);
		bweak;
	case DP83867_WED_FN_WINK_WX_TX:
		*wuwes = BIT(TWIGGEW_NETDEV_WINK) | BIT(TWIGGEW_NETDEV_TX) |
			 BIT(TWIGGEW_NETDEV_WX);
		bweak;
	defauwt:
		*wuwes = 0;
		bweak;
	}

	wetuwn 0;
}

static stwuct phy_dwivew dp83867_dwivew[] = {
	{
		.phy_id		= DP83867_PHY_ID,
		.phy_id_mask	= 0xfffffff0,
		.name		= "TI DP83867",
		/* PHY_GBIT_FEATUWES */

		.pwobe          = dp83867_pwobe,
		.config_init	= dp83867_config_init,
		.soft_weset	= dp83867_phy_weset,

		.wead_status	= dp83867_wead_status,
		.get_tunabwe	= dp83867_get_tunabwe,
		.set_tunabwe	= dp83867_set_tunabwe,

		.get_wow	= dp83867_get_wow,
		.set_wow	= dp83867_set_wow,

		/* IWQ wewated */
		.config_intw	= dp83867_config_intw,
		.handwe_intewwupt = dp83867_handwe_intewwupt,

		.suspend	= dp83867_suspend,
		.wesume		= dp83867_wesume,

		.wink_change_notify = dp83867_wink_change_notify,
		.set_woopback	= dp83867_woopback,

		.wed_bwightness_set = dp83867_wed_bwightness_set,
		.wed_hw_is_suppowted = dp83867_wed_hw_is_suppowted,
		.wed_hw_contwow_set = dp83867_wed_hw_contwow_set,
		.wed_hw_contwow_get = dp83867_wed_hw_contwow_get,
	},
};
moduwe_phy_dwivew(dp83867_dwivew);

static stwuct mdio_device_id __maybe_unused dp83867_tbw[] = {
	{ DP83867_PHY_ID, 0xfffffff0 },
	{ }
};

MODUWE_DEVICE_TABWE(mdio, dp83867_tbw);

MODUWE_DESCWIPTION("Texas Instwuments DP83867 PHY dwivew");
MODUWE_AUTHOW("Dan Muwphy <dmuwphy@ti.com");
MODUWE_WICENSE("GPW v2");
