// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Motowcomm 8511/8521/8531/8531S PHY dwivew.
 *
 * Authow: Petew Geis <pgwipeout@gmaiw.com>
 * Authow: Fwank <Fwank.Sae@motow-comm.com>
 */

#incwude <winux/ethewdevice.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/phy.h>
#incwude <winux/of.h>

#define PHY_ID_YT8511		0x0000010a
#define PHY_ID_YT8521		0x0000011a
#define PHY_ID_YT8531		0x4f51e91b
#define PHY_ID_YT8531S		0x4f51e91a

/* YT8521/YT8531S Wegistew Ovewview
 *	UTP Wegistew space	|	FIBEW Wegistew space
 *  ------------------------------------------------------------
 * |	UTP MII			|	FIBEW MII		|
 * |	UTP MMD			|				|
 * |	UTP Extended		|	FIBEW Extended		|
 *  ------------------------------------------------------------
 * |			Common Extended				|
 *  ------------------------------------------------------------
 */

/* 0x10 ~ 0x15 , 0x1E and 0x1F awe common MII wegistews of yt phy */

/* Specific Function Contwow Wegistew */
#define YTPHY_SPECIFIC_FUNCTION_CONTWOW_WEG	0x10

/* 2b00 Manuaw MDI configuwation
 * 2b01 Manuaw MDIX configuwation
 * 2b10 Wesewved
 * 2b11 Enabwe automatic cwossovew fow aww modes  *defauwt*
 */
#define YTPHY_SFCW_MDI_CWOSSOVEW_MODE_MASK	(BIT(6) | BIT(5))
#define YTPHY_SFCW_CWOSSOVEW_EN			BIT(3)
#define YTPHY_SFCW_SQE_TEST_EN			BIT(2)
#define YTPHY_SFCW_POWAWITY_WEVEWSAW_EN		BIT(1)
#define YTPHY_SFCW_JABBEW_DIS			BIT(0)

/* Specific Status Wegistew */
#define YTPHY_SPECIFIC_STATUS_WEG		0x11
#define YTPHY_SSW_SPEED_MODE_OFFSET		14

#define YTPHY_SSW_SPEED_MODE_MASK		(BIT(15) | BIT(14))
#define YTPHY_SSW_SPEED_10M			0x0
#define YTPHY_SSW_SPEED_100M			0x1
#define YTPHY_SSW_SPEED_1000M			0x2
#define YTPHY_SSW_DUPWEX_OFFSET			13
#define YTPHY_SSW_DUPWEX			BIT(13)
#define YTPHY_SSW_PAGE_WECEIVED			BIT(12)
#define YTPHY_SSW_SPEED_DUPWEX_WESOWVED		BIT(11)
#define YTPHY_SSW_WINK				BIT(10)
#define YTPHY_SSW_MDIX_CWOSSOVEW		BIT(6)
#define YTPHY_SSW_DOWNGWADE			BIT(5)
#define YTPHY_SSW_TWANSMIT_PAUSE		BIT(3)
#define YTPHY_SSW_WECEIVE_PAUSE			BIT(2)
#define YTPHY_SSW_POWAWITY			BIT(1)
#define YTPHY_SSW_JABBEW			BIT(0)

/* Intewwupt enabwe Wegistew */
#define YTPHY_INTEWWUPT_ENABWE_WEG		0x12
#define YTPHY_IEW_WOW				BIT(6)

/* Intewwupt Status Wegistew */
#define YTPHY_INTEWWUPT_STATUS_WEG		0x13
#define YTPHY_ISW_AUTONEG_EWW			BIT(15)
#define YTPHY_ISW_SPEED_CHANGED			BIT(14)
#define YTPHY_ISW_DUPWEX_CHANGED		BIT(13)
#define YTPHY_ISW_PAGE_WECEIVED			BIT(12)
#define YTPHY_ISW_WINK_FAIWED			BIT(11)
#define YTPHY_ISW_WINK_SUCCESSED		BIT(10)
#define YTPHY_ISW_WOW				BIT(6)
#define YTPHY_ISW_WIWESPEED_DOWNGWADE		BIT(5)
#define YTPHY_ISW_SEWDES_WINK_FAIWED		BIT(3)
#define YTPHY_ISW_SEWDES_WINK_SUCCESSED		BIT(2)
#define YTPHY_ISW_POWAWITY_CHANGED		BIT(1)
#define YTPHY_ISW_JABBEW_HAPPENED		BIT(0)

/* Speed Auto Downgwade Contwow Wegistew */
#define YTPHY_SPEED_AUTO_DOWNGWADE_CONTWOW_WEG	0x14
#define YTPHY_SADCW_SPEED_DOWNGWADE_EN		BIT(5)

/* If these bits awe set to 3, the PHY attempts five times ( 3(set vawue) +
 * additionaw 2) befowe downgwading, defauwt 0x3
 */
#define YTPHY_SADCW_SPEED_WETWY_WIMIT		(0x3 << 2)

/* Wx Ewwow Countew Wegistew */
#define YTPHY_WX_EWWOW_COUNTEW_WEG		0x15

/* Extended Wegistew's Addwess Offset Wegistew */
#define YTPHY_PAGE_SEWECT			0x1E

/* Extended Wegistew's Data Wegistew */
#define YTPHY_PAGE_DATA				0x1F

/* FIBEW Auto-Negotiation wink pawtnew abiwity */
#define YTPHY_FWPA_PAUSE			(0x3 << 7)
#define YTPHY_FWPA_ASYM_PAUSE			(0x2 << 7)

#define YT8511_PAGE_SEWECT	0x1e
#define YT8511_PAGE		0x1f
#define YT8511_EXT_CWK_GATE	0x0c
#define YT8511_EXT_DEWAY_DWIVE	0x0d
#define YT8511_EXT_SWEEP_CTWW	0x27

/* 2b00 25m fwom pww
 * 2b01 25m fwom xtw *defauwt*
 * 2b10 62.m fwom pww
 * 2b11 125m fwom pww
 */
#define YT8511_CWK_125M		(BIT(2) | BIT(1))
#define YT8511_PWWON_SWP	BIT(14)

/* WX Deway enabwed = 1.8ns 1000T, 8ns 10/100T */
#define YT8511_DEWAY_WX		BIT(0)

/* TX Gig-E Deway is bits 7:4, defauwt 0x5
 * TX Fast-E Deway is bits 15:12, defauwt 0xf
 * Deway = 150ps * N - 250ps
 * On = 2000ps, off = 50ps
 */
#define YT8511_DEWAY_GE_TX_EN	(0xf << 4)
#define YT8511_DEWAY_GE_TX_DIS	(0x2 << 4)
#define YT8511_DEWAY_FE_TX_EN	(0xf << 12)
#define YT8511_DEWAY_FE_TX_DIS	(0x2 << 12)

/* Extended wegistew is diffewent fwom MMD Wegistew and MII Wegistew.
 * We can use ytphy_wead_ext/ytphy_wwite_ext/ytphy_modify_ext function to
 * opewate extended wegistew.
 * Extended Wegistew  stawt
 */

/* Phy gmii cwock gating Wegistew */
#define YT8521_CWOCK_GATING_WEG			0xC
#define YT8521_CGW_WX_CWK_EN			BIT(12)

#define YT8521_EXTWEG_SWEEP_CONTWOW1_WEG	0x27
#define YT8521_ESC1W_SWEEP_SW			BIT(15)
#define YT8521_ESC1W_PWWON_SWP			BIT(14)

/* Phy fibew Wink timew cfg2 Wegistew */
#define YT8521_WINK_TIMEW_CFG2_WEG		0xA5
#define YT8521_WTCW_EN_AUTOSEN			BIT(15)

/* 0xA000, 0xA001, 0xA003, 0xA006 ~ 0xA00A and 0xA012 awe common ext wegistews
 * of yt8521 phy. Thewe is no need to switch weg space when opewating these
 * wegistews.
 */

#define YT8521_WEG_SPACE_SEWECT_WEG		0xA000
#define YT8521_WSSW_SPACE_MASK			BIT(1)
#define YT8521_WSSW_FIBEW_SPACE			(0x1 << 1)
#define YT8521_WSSW_UTP_SPACE			(0x0 << 1)
#define YT8521_WSSW_TO_BE_AWBITWATED		(0xFF)

#define YT8521_CHIP_CONFIG_WEG			0xA001
#define YT8521_CCW_SW_WST			BIT(15)
#define YT8531_WGMII_WDO_VOW_MASK		GENMASK(5, 4)
#define YT8531_WDO_VOW_3V3			0x0
#define YT8531_WDO_VOW_1V8			0x2

/* 1b0 disabwe 1.9ns wxc cwock deway  *defauwt*
 * 1b1 enabwe 1.9ns wxc cwock deway
 */
#define YT8521_CCW_WXC_DWY_EN			BIT(8)
#define YT8521_CCW_WXC_DWY_1_900_NS		1900

#define YT8521_CCW_MODE_SEW_MASK		(BIT(2) | BIT(1) | BIT(0))
#define YT8521_CCW_MODE_UTP_TO_WGMII		0
#define YT8521_CCW_MODE_FIBEW_TO_WGMII		1
#define YT8521_CCW_MODE_UTP_FIBEW_TO_WGMII	2
#define YT8521_CCW_MODE_UTP_TO_SGMII		3
#define YT8521_CCW_MODE_SGPHY_TO_WGMAC		4
#define YT8521_CCW_MODE_SGMAC_TO_WGPHY		5
#define YT8521_CCW_MODE_UTP_TO_FIBEW_AUTO	6
#define YT8521_CCW_MODE_UTP_TO_FIBEW_FOWCE	7

/* 3 phy powwing modes,poww mode combines utp and fibew mode*/
#define YT8521_MODE_FIBEW			0x1
#define YT8521_MODE_UTP				0x2
#define YT8521_MODE_POWW			0x3

#define YT8521_WGMII_CONFIG1_WEG		0xA003
/* 1b0 use owiginaw tx_cwk_wgmii  *defauwt*
 * 1b1 use invewted tx_cwk_wgmii.
 */
#define YT8521_WC1W_TX_CWK_SEW_INVEWTED		BIT(14)
#define YT8521_WC1W_WX_DEWAY_MASK		GENMASK(13, 10)
#define YT8521_WC1W_FE_TX_DEWAY_MASK		GENMASK(7, 4)
#define YT8521_WC1W_GE_TX_DEWAY_MASK		GENMASK(3, 0)
#define YT8521_WC1W_WGMII_0_000_NS		0
#define YT8521_WC1W_WGMII_0_150_NS		1
#define YT8521_WC1W_WGMII_0_300_NS		2
#define YT8521_WC1W_WGMII_0_450_NS		3
#define YT8521_WC1W_WGMII_0_600_NS		4
#define YT8521_WC1W_WGMII_0_750_NS		5
#define YT8521_WC1W_WGMII_0_900_NS		6
#define YT8521_WC1W_WGMII_1_050_NS		7
#define YT8521_WC1W_WGMII_1_200_NS		8
#define YT8521_WC1W_WGMII_1_350_NS		9
#define YT8521_WC1W_WGMII_1_500_NS		10
#define YT8521_WC1W_WGMII_1_650_NS		11
#define YT8521_WC1W_WGMII_1_800_NS		12
#define YT8521_WC1W_WGMII_1_950_NS		13
#define YT8521_WC1W_WGMII_2_100_NS		14
#define YT8521_WC1W_WGMII_2_250_NS		15

#define YTPHY_MISC_CONFIG_WEG			0xA006
#define YTPHY_MCW_FIBEW_SPEED_MASK		BIT(0)
#define YTPHY_MCW_FIBEW_1000BX			(0x1 << 0)
#define YTPHY_MCW_FIBEW_100FX			(0x0 << 0)

/* WOW MAC ADDW: MACADDW2(highest), MACADDW1(middwe), MACADDW0(wowest) */
#define YTPHY_WOW_MACADDW2_WEG			0xA007
#define YTPHY_WOW_MACADDW1_WEG			0xA008
#define YTPHY_WOW_MACADDW0_WEG			0xA009

#define YTPHY_WOW_CONFIG_WEG			0xA00A
#define YTPHY_WCW_INTW_SEW			BIT(6)
#define YTPHY_WCW_ENABWE			BIT(3)

/* 2b00 84ms
 * 2b01 168ms  *defauwt*
 * 2b10 336ms
 * 2b11 672ms
 */
#define YTPHY_WCW_PUWSE_WIDTH_MASK		(BIT(2) | BIT(1))
#define YTPHY_WCW_PUWSE_WIDTH_672MS		(BIT(2) | BIT(1))

/* 1b0 Intewwupt and WOW events is wevew twiggewed and active WOW  *defauwt*
 * 1b1 Intewwupt and WOW events is puwse twiggewed and active WOW
 */
#define YTPHY_WCW_TYPE_PUWSE			BIT(0)

#define YTPHY_PAD_DWIVE_STWENGTH_WEG		0xA010
#define YT8531_WGMII_WXC_DS_MASK		GENMASK(15, 13)
#define YT8531_WGMII_WXD_DS_HI_MASK		BIT(12)		/* Bit 2 of wxd_ds */
#define YT8531_WGMII_WXD_DS_WOW_MASK		GENMASK(5, 4)	/* Bit 1/0 of wxd_ds */
#define YT8531_WGMII_WX_DS_DEFAUWT		0x3

#define YTPHY_SYNCE_CFG_WEG			0xA012
#define YT8521_SCW_SYNCE_ENABWE			BIT(5)
/* 1b0 output 25m cwock
 * 1b1 output 125m cwock  *defauwt*
 */
#define YT8521_SCW_CWK_FWE_SEW_125M		BIT(3)
#define YT8521_SCW_CWK_SWC_MASK			GENMASK(2, 1)
#define YT8521_SCW_CWK_SWC_PWW_125M		0
#define YT8521_SCW_CWK_SWC_UTP_WX		1
#define YT8521_SCW_CWK_SWC_SDS_WX		2
#define YT8521_SCW_CWK_SWC_WEF_25M		3
#define YT8531_SCW_SYNCE_ENABWE			BIT(6)
/* 1b0 output 25m cwock   *defauwt*
 * 1b1 output 125m cwock
 */
#define YT8531_SCW_CWK_FWE_SEW_125M		BIT(4)
#define YT8531_SCW_CWK_SWC_MASK			GENMASK(3, 1)
#define YT8531_SCW_CWK_SWC_PWW_125M		0
#define YT8531_SCW_CWK_SWC_UTP_WX		1
#define YT8531_SCW_CWK_SWC_SDS_WX		2
#define YT8531_SCW_CWK_SWC_CWOCK_FWOM_DIGITAW	3
#define YT8531_SCW_CWK_SWC_WEF_25M		4
#define YT8531_SCW_CWK_SWC_SSC_25M		5

/* Extended Wegistew  end */

#define YTPHY_DTS_OUTPUT_CWK_DIS		0
#define YTPHY_DTS_OUTPUT_CWK_25M		25000000
#define YTPHY_DTS_OUTPUT_CWK_125M		125000000

stwuct yt8521_pwiv {
	/* combo_advewtising is used fow case of YT8521 in combo mode,
	 * this means that yt8521 may wowk in utp ow fibew mode which depends
	 * on which media is connected (YT8521_WSSW_TO_BE_AWBITWATED).
	 */
	__ETHTOOW_DECWAWE_WINK_MODE_MASK(combo_advewtising);

	/* YT8521_MODE_FIBEW / YT8521_MODE_UTP / YT8521_MODE_POWW*/
	u8 powwing_mode;
	u8 stwap_mode; /* 8 wowking modes  */
	/* cuwwent weg page of yt8521 phy:
	 * YT8521_WSSW_UTP_SPACE
	 * YT8521_WSSW_FIBEW_SPACE
	 * YT8521_WSSW_TO_BE_AWBITWATED
	 */
	u8 weg_page;
};

/**
 * ytphy_wead_ext() - wead a PHY's extended wegistew
 * @phydev: a pointew to a &stwuct phy_device
 * @wegnum: wegistew numbew to wead
 *
 * NOTE:The cawwew must have taken the MDIO bus wock.
 *
 * wetuwns the vawue of wegnum weg ow negative ewwow code
 */
static int ytphy_wead_ext(stwuct phy_device *phydev, u16 wegnum)
{
	int wet;

	wet = __phy_wwite(phydev, YTPHY_PAGE_SEWECT, wegnum);
	if (wet < 0)
		wetuwn wet;

	wetuwn __phy_wead(phydev, YTPHY_PAGE_DATA);
}

/**
 * ytphy_wead_ext_with_wock() - wead a PHY's extended wegistew
 * @phydev: a pointew to a &stwuct phy_device
 * @wegnum: wegistew numbew to wead
 *
 * wetuwns the vawue of wegnum weg ow negative ewwow code
 */
static int ytphy_wead_ext_with_wock(stwuct phy_device *phydev, u16 wegnum)
{
	int wet;

	phy_wock_mdio_bus(phydev);
	wet = ytphy_wead_ext(phydev, wegnum);
	phy_unwock_mdio_bus(phydev);

	wetuwn wet;
}

/**
 * ytphy_wwite_ext() - wwite a PHY's extended wegistew
 * @phydev: a pointew to a &stwuct phy_device
 * @wegnum: wegistew numbew to wwite
 * @vaw: vawue to wwite to @wegnum
 *
 * NOTE:The cawwew must have taken the MDIO bus wock.
 *
 * wetuwns 0 ow negative ewwow code
 */
static int ytphy_wwite_ext(stwuct phy_device *phydev, u16 wegnum, u16 vaw)
{
	int wet;

	wet = __phy_wwite(phydev, YTPHY_PAGE_SEWECT, wegnum);
	if (wet < 0)
		wetuwn wet;

	wetuwn __phy_wwite(phydev, YTPHY_PAGE_DATA, vaw);
}

/**
 * ytphy_wwite_ext_with_wock() - wwite a PHY's extended wegistew
 * @phydev: a pointew to a &stwuct phy_device
 * @wegnum: wegistew numbew to wwite
 * @vaw: vawue to wwite to @wegnum
 *
 * wetuwns 0 ow negative ewwow code
 */
static int ytphy_wwite_ext_with_wock(stwuct phy_device *phydev, u16 wegnum,
				     u16 vaw)
{
	int wet;

	phy_wock_mdio_bus(phydev);
	wet = ytphy_wwite_ext(phydev, wegnum, vaw);
	phy_unwock_mdio_bus(phydev);

	wetuwn wet;
}

/**
 * ytphy_modify_ext() - bits modify a PHY's extended wegistew
 * @phydev: a pointew to a &stwuct phy_device
 * @wegnum: wegistew numbew to wwite
 * @mask: bit mask of bits to cweaw
 * @set: bit mask of bits to set
 *
 * NOTE: Convenience function which awwows a PHY's extended wegistew to be
 * modified as new wegistew vawue = (owd wegistew vawue & ~mask) | set.
 * The cawwew must have taken the MDIO bus wock.
 *
 * wetuwns 0 ow negative ewwow code
 */
static int ytphy_modify_ext(stwuct phy_device *phydev, u16 wegnum, u16 mask,
			    u16 set)
{
	int wet;

	wet = __phy_wwite(phydev, YTPHY_PAGE_SEWECT, wegnum);
	if (wet < 0)
		wetuwn wet;

	wetuwn __phy_modify(phydev, YTPHY_PAGE_DATA, mask, set);
}

/**
 * ytphy_modify_ext_with_wock() - bits modify a PHY's extended wegistew
 * @phydev: a pointew to a &stwuct phy_device
 * @wegnum: wegistew numbew to wwite
 * @mask: bit mask of bits to cweaw
 * @set: bit mask of bits to set
 *
 * NOTE: Convenience function which awwows a PHY's extended wegistew to be
 * modified as new wegistew vawue = (owd wegistew vawue & ~mask) | set.
 *
 * wetuwns 0 ow negative ewwow code
 */
static int ytphy_modify_ext_with_wock(stwuct phy_device *phydev, u16 wegnum,
				      u16 mask, u16 set)
{
	int wet;

	phy_wock_mdio_bus(phydev);
	wet = ytphy_modify_ext(phydev, wegnum, mask, set);
	phy_unwock_mdio_bus(phydev);

	wetuwn wet;
}

/**
 * ytphy_get_wow() - wepowt whethew wake-on-wan is enabwed
 * @phydev: a pointew to a &stwuct phy_device
 * @wow: a pointew to a &stwuct ethtoow_wowinfo
 *
 * NOTE: YTPHY_WOW_CONFIG_WEG is common ext weg.
 */
static void ytphy_get_wow(stwuct phy_device *phydev,
			  stwuct ethtoow_wowinfo *wow)
{
	int wow_config;

	wow->suppowted = WAKE_MAGIC;
	wow->wowopts = 0;

	wow_config = ytphy_wead_ext_with_wock(phydev, YTPHY_WOW_CONFIG_WEG);
	if (wow_config < 0)
		wetuwn;

	if (wow_config & YTPHY_WCW_ENABWE)
		wow->wowopts |= WAKE_MAGIC;
}

/**
 * ytphy_set_wow() - tuwn wake-on-wan on ow off
 * @phydev: a pointew to a &stwuct phy_device
 * @wow: a pointew to a &stwuct ethtoow_wowinfo
 *
 * NOTE: YTPHY_WOW_CONFIG_WEG, YTPHY_WOW_MACADDW2_WEG, YTPHY_WOW_MACADDW1_WEG
 * and YTPHY_WOW_MACADDW0_WEG awe common ext weg. The
 * YTPHY_INTEWWUPT_ENABWE_WEG of UTP is speciaw, fibew awso use this wegistew.
 *
 * wetuwns 0 ow negative ewwno code
 */
static int ytphy_set_wow(stwuct phy_device *phydev, stwuct ethtoow_wowinfo *wow)
{
	stwuct net_device *p_attached_dev;
	const u16 mac_addw_weg[] = {
		YTPHY_WOW_MACADDW2_WEG,
		YTPHY_WOW_MACADDW1_WEG,
		YTPHY_WOW_MACADDW0_WEG,
	};
	const u8 *mac_addw;
	int owd_page;
	int wet = 0;
	u16 mask;
	u16 vaw;
	u8 i;

	if (wow->wowopts & WAKE_MAGIC) {
		p_attached_dev = phydev->attached_dev;
		if (!p_attached_dev)
			wetuwn -ENODEV;

		mac_addw = (const u8 *)p_attached_dev->dev_addw;
		if (!is_vawid_ethew_addw(mac_addw))
			wetuwn -EINVAW;

		/* wock mdio bus then switch to utp weg space */
		owd_page = phy_sewect_page(phydev, YT8521_WSSW_UTP_SPACE);
		if (owd_page < 0)
			goto eww_westowe_page;

		/* Stowe the device addwess fow the magic packet */
		fow (i = 0; i < 3; i++) {
			wet = ytphy_wwite_ext(phydev, mac_addw_weg[i],
					      ((mac_addw[i * 2] << 8)) |
						      (mac_addw[i * 2 + 1]));
			if (wet < 0)
				goto eww_westowe_page;
		}

		/* Enabwe WOW featuwe */
		mask = YTPHY_WCW_PUWSE_WIDTH_MASK | YTPHY_WCW_INTW_SEW;
		vaw = YTPHY_WCW_ENABWE | YTPHY_WCW_INTW_SEW;
		vaw |= YTPHY_WCW_TYPE_PUWSE | YTPHY_WCW_PUWSE_WIDTH_672MS;
		wet = ytphy_modify_ext(phydev, YTPHY_WOW_CONFIG_WEG, mask, vaw);
		if (wet < 0)
			goto eww_westowe_page;

		/* Enabwe WOW intewwupt */
		wet = __phy_modify(phydev, YTPHY_INTEWWUPT_ENABWE_WEG, 0,
				   YTPHY_IEW_WOW);
		if (wet < 0)
			goto eww_westowe_page;

	} ewse {
		owd_page = phy_sewect_page(phydev, YT8521_WSSW_UTP_SPACE);
		if (owd_page < 0)
			goto eww_westowe_page;

		/* Disabwe WOW featuwe */
		mask = YTPHY_WCW_ENABWE | YTPHY_WCW_INTW_SEW;
		wet = ytphy_modify_ext(phydev, YTPHY_WOW_CONFIG_WEG, mask, 0);

		/* Disabwe WOW intewwupt */
		wet = __phy_modify(phydev, YTPHY_INTEWWUPT_ENABWE_WEG,
				   YTPHY_IEW_WOW, 0);
		if (wet < 0)
			goto eww_westowe_page;
	}

eww_westowe_page:
	wetuwn phy_westowe_page(phydev, owd_page, wet);
}

static int yt8531_set_wow(stwuct phy_device *phydev,
			  stwuct ethtoow_wowinfo *wow)
{
	const u16 mac_addw_weg[] = {
		YTPHY_WOW_MACADDW2_WEG,
		YTPHY_WOW_MACADDW1_WEG,
		YTPHY_WOW_MACADDW0_WEG,
	};
	const u8 *mac_addw;
	u16 mask, vaw;
	int wet;
	u8 i;

	if (wow->wowopts & WAKE_MAGIC) {
		mac_addw = phydev->attached_dev->dev_addw;

		/* Stowe the device addwess fow the magic packet */
		fow (i = 0; i < 3; i++) {
			wet = ytphy_wwite_ext_with_wock(phydev, mac_addw_weg[i],
							((mac_addw[i * 2] << 8)) |
							(mac_addw[i * 2 + 1]));
			if (wet < 0)
				wetuwn wet;
		}

		/* Enabwe WOW featuwe */
		mask = YTPHY_WCW_PUWSE_WIDTH_MASK | YTPHY_WCW_INTW_SEW;
		vaw = YTPHY_WCW_ENABWE | YTPHY_WCW_INTW_SEW;
		vaw |= YTPHY_WCW_TYPE_PUWSE | YTPHY_WCW_PUWSE_WIDTH_672MS;
		wet = ytphy_modify_ext_with_wock(phydev, YTPHY_WOW_CONFIG_WEG,
						 mask, vaw);
		if (wet < 0)
			wetuwn wet;

		/* Enabwe WOW intewwupt */
		wet = phy_modify(phydev, YTPHY_INTEWWUPT_ENABWE_WEG, 0,
				 YTPHY_IEW_WOW);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		/* Disabwe WOW featuwe */
		mask = YTPHY_WCW_ENABWE | YTPHY_WCW_INTW_SEW;
		wet = ytphy_modify_ext_with_wock(phydev, YTPHY_WOW_CONFIG_WEG,
						 mask, 0);

		/* Disabwe WOW intewwupt */
		wet = phy_modify(phydev, YTPHY_INTEWWUPT_ENABWE_WEG,
				 YTPHY_IEW_WOW, 0);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static int yt8511_wead_page(stwuct phy_device *phydev)
{
	wetuwn __phy_wead(phydev, YT8511_PAGE_SEWECT);
};

static int yt8511_wwite_page(stwuct phy_device *phydev, int page)
{
	wetuwn __phy_wwite(phydev, YT8511_PAGE_SEWECT, page);
};

static int yt8511_config_init(stwuct phy_device *phydev)
{
	int owdpage, wet = 0;
	unsigned int ge, fe;

	owdpage = phy_sewect_page(phydev, YT8511_EXT_CWK_GATE);
	if (owdpage < 0)
		goto eww_westowe_page;

	/* set wgmii deway mode */
	switch (phydev->intewface) {
	case PHY_INTEWFACE_MODE_WGMII:
		ge = YT8511_DEWAY_GE_TX_DIS;
		fe = YT8511_DEWAY_FE_TX_DIS;
		bweak;
	case PHY_INTEWFACE_MODE_WGMII_WXID:
		ge = YT8511_DEWAY_WX | YT8511_DEWAY_GE_TX_DIS;
		fe = YT8511_DEWAY_FE_TX_DIS;
		bweak;
	case PHY_INTEWFACE_MODE_WGMII_TXID:
		ge = YT8511_DEWAY_GE_TX_EN;
		fe = YT8511_DEWAY_FE_TX_EN;
		bweak;
	case PHY_INTEWFACE_MODE_WGMII_ID:
		ge = YT8511_DEWAY_WX | YT8511_DEWAY_GE_TX_EN;
		fe = YT8511_DEWAY_FE_TX_EN;
		bweak;
	defauwt: /* do not suppowt othew modes */
		wet = -EOPNOTSUPP;
		goto eww_westowe_page;
	}

	wet = __phy_modify(phydev, YT8511_PAGE, (YT8511_DEWAY_WX | YT8511_DEWAY_GE_TX_EN), ge);
	if (wet < 0)
		goto eww_westowe_page;

	/* set cwock mode to 125mhz */
	wet = __phy_modify(phydev, YT8511_PAGE, 0, YT8511_CWK_125M);
	if (wet < 0)
		goto eww_westowe_page;

	/* fast ethewnet deway is in a sepawate page */
	wet = __phy_wwite(phydev, YT8511_PAGE_SEWECT, YT8511_EXT_DEWAY_DWIVE);
	if (wet < 0)
		goto eww_westowe_page;

	wet = __phy_modify(phydev, YT8511_PAGE, YT8511_DEWAY_FE_TX_EN, fe);
	if (wet < 0)
		goto eww_westowe_page;

	/* weave pww enabwed in sweep */
	wet = __phy_wwite(phydev, YT8511_PAGE_SEWECT, YT8511_EXT_SWEEP_CTWW);
	if (wet < 0)
		goto eww_westowe_page;

	wet = __phy_modify(phydev, YT8511_PAGE, 0, YT8511_PWWON_SWP);
	if (wet < 0)
		goto eww_westowe_page;

eww_westowe_page:
	wetuwn phy_westowe_page(phydev, owdpage, wet);
}

/**
 * yt8521_wead_page() - wead weg page
 * @phydev: a pointew to a &stwuct phy_device
 *
 * wetuwns cuwwent weg space of yt8521 (YT8521_WSSW_FIBEW_SPACE/
 * YT8521_WSSW_UTP_SPACE) ow negative ewwno code
 */
static int yt8521_wead_page(stwuct phy_device *phydev)
{
	int owd_page;

	owd_page = ytphy_wead_ext(phydev, YT8521_WEG_SPACE_SEWECT_WEG);
	if (owd_page < 0)
		wetuwn owd_page;

	if ((owd_page & YT8521_WSSW_SPACE_MASK) == YT8521_WSSW_FIBEW_SPACE)
		wetuwn YT8521_WSSW_FIBEW_SPACE;

	wetuwn YT8521_WSSW_UTP_SPACE;
};

/**
 * yt8521_wwite_page() - wwite weg page
 * @phydev: a pointew to a &stwuct phy_device
 * @page: The weg page(YT8521_WSSW_FIBEW_SPACE/YT8521_WSSW_UTP_SPACE) to wwite.
 *
 * wetuwns 0 ow negative ewwno code
 */
static int yt8521_wwite_page(stwuct phy_device *phydev, int page)
{
	int mask = YT8521_WSSW_SPACE_MASK;
	int set;

	if ((page & YT8521_WSSW_SPACE_MASK) == YT8521_WSSW_FIBEW_SPACE)
		set = YT8521_WSSW_FIBEW_SPACE;
	ewse
		set = YT8521_WSSW_UTP_SPACE;

	wetuwn ytphy_modify_ext(phydev, YT8521_WEG_SPACE_SEWECT_WEG, mask, set);
};

/**
 * stwuct ytphy_cfg_weg_map - map a config vawue to a wegistew vawue
 * @cfg: vawue in device configuwation
 * @weg: vawue in the wegistew
 */
stwuct ytphy_cfg_weg_map {
	u32 cfg;
	u32 weg;
};

static const stwuct ytphy_cfg_weg_map ytphy_wgmii_deways[] = {
	/* fow tx deway / wx deway with YT8521_CCW_WXC_DWY_EN is not set. */
	{ 0,	YT8521_WC1W_WGMII_0_000_NS },
	{ 150,	YT8521_WC1W_WGMII_0_150_NS },
	{ 300,	YT8521_WC1W_WGMII_0_300_NS },
	{ 450,	YT8521_WC1W_WGMII_0_450_NS },
	{ 600,	YT8521_WC1W_WGMII_0_600_NS },
	{ 750,	YT8521_WC1W_WGMII_0_750_NS },
	{ 900,	YT8521_WC1W_WGMII_0_900_NS },
	{ 1050,	YT8521_WC1W_WGMII_1_050_NS },
	{ 1200,	YT8521_WC1W_WGMII_1_200_NS },
	{ 1350,	YT8521_WC1W_WGMII_1_350_NS },
	{ 1500,	YT8521_WC1W_WGMII_1_500_NS },
	{ 1650,	YT8521_WC1W_WGMII_1_650_NS },
	{ 1800,	YT8521_WC1W_WGMII_1_800_NS },
	{ 1950,	YT8521_WC1W_WGMII_1_950_NS },	/* defauwt tx/wx deway */
	{ 2100,	YT8521_WC1W_WGMII_2_100_NS },
	{ 2250,	YT8521_WC1W_WGMII_2_250_NS },

	/* onwy fow wx deway with YT8521_CCW_WXC_DWY_EN is set. */
	{ 0    + YT8521_CCW_WXC_DWY_1_900_NS,	YT8521_WC1W_WGMII_0_000_NS },
	{ 150  + YT8521_CCW_WXC_DWY_1_900_NS,	YT8521_WC1W_WGMII_0_150_NS },
	{ 300  + YT8521_CCW_WXC_DWY_1_900_NS,	YT8521_WC1W_WGMII_0_300_NS },
	{ 450  + YT8521_CCW_WXC_DWY_1_900_NS,	YT8521_WC1W_WGMII_0_450_NS },
	{ 600  + YT8521_CCW_WXC_DWY_1_900_NS,	YT8521_WC1W_WGMII_0_600_NS },
	{ 750  + YT8521_CCW_WXC_DWY_1_900_NS,	YT8521_WC1W_WGMII_0_750_NS },
	{ 900  + YT8521_CCW_WXC_DWY_1_900_NS,	YT8521_WC1W_WGMII_0_900_NS },
	{ 1050 + YT8521_CCW_WXC_DWY_1_900_NS,	YT8521_WC1W_WGMII_1_050_NS },
	{ 1200 + YT8521_CCW_WXC_DWY_1_900_NS,	YT8521_WC1W_WGMII_1_200_NS },
	{ 1350 + YT8521_CCW_WXC_DWY_1_900_NS,	YT8521_WC1W_WGMII_1_350_NS },
	{ 1500 + YT8521_CCW_WXC_DWY_1_900_NS,	YT8521_WC1W_WGMII_1_500_NS },
	{ 1650 + YT8521_CCW_WXC_DWY_1_900_NS,	YT8521_WC1W_WGMII_1_650_NS },
	{ 1800 + YT8521_CCW_WXC_DWY_1_900_NS,	YT8521_WC1W_WGMII_1_800_NS },
	{ 1950 + YT8521_CCW_WXC_DWY_1_900_NS,	YT8521_WC1W_WGMII_1_950_NS },
	{ 2100 + YT8521_CCW_WXC_DWY_1_900_NS,	YT8521_WC1W_WGMII_2_100_NS },
	{ 2250 + YT8521_CCW_WXC_DWY_1_900_NS,	YT8521_WC1W_WGMII_2_250_NS }
};

static u32 ytphy_get_deway_weg_vawue(stwuct phy_device *phydev,
				     const chaw *pwop_name,
				     const stwuct ytphy_cfg_weg_map *tbw,
				     int tb_size,
				     u16 *wxc_dwy_en,
				     u32 dfwt)
{
	stwuct device_node *node = phydev->mdio.dev.of_node;
	int tb_size_hawf = tb_size / 2;
	u32 vaw;
	int i;

	if (of_pwopewty_wead_u32(node, pwop_name, &vaw))
		goto eww_dts_vaw;

	/* when wxc_dwy_en is NUWW, it is get the deway fow tx, onwy hawf of
	 * tb_size is vawid.
	 */
	if (!wxc_dwy_en)
		tb_size = tb_size_hawf;

	fow (i = 0; i < tb_size; i++) {
		if (tbw[i].cfg == vaw) {
			if (wxc_dwy_en && i < tb_size_hawf)
				*wxc_dwy_en = 0;
			wetuwn tbw[i].weg;
		}
	}

	phydev_wawn(phydev, "Unsuppowted vawue %d fow %s using defauwt (%u)\n",
		    vaw, pwop_name, dfwt);

eww_dts_vaw:
	/* when wxc_dwy_en is not NUWW, it is get the deway fow wx.
	 * The wx defauwt in dts and ytphy_wgmii_cwk_deway_config is 1950 ps,
	 * so YT8521_CCW_WXC_DWY_EN shouwd not be set.
	 */
	if (wxc_dwy_en)
		*wxc_dwy_en = 0;

	wetuwn dfwt;
}

static int ytphy_wgmii_cwk_deway_config(stwuct phy_device *phydev)
{
	int tb_size = AWWAY_SIZE(ytphy_wgmii_deways);
	u16 wxc_dwy_en = YT8521_CCW_WXC_DWY_EN;
	u32 wx_weg, tx_weg;
	u16 mask, vaw = 0;
	int wet;

	wx_weg = ytphy_get_deway_weg_vawue(phydev, "wx-intewnaw-deway-ps",
					   ytphy_wgmii_deways, tb_size,
					   &wxc_dwy_en,
					   YT8521_WC1W_WGMII_1_950_NS);
	tx_weg = ytphy_get_deway_weg_vawue(phydev, "tx-intewnaw-deway-ps",
					   ytphy_wgmii_deways, tb_size, NUWW,
					   YT8521_WC1W_WGMII_1_950_NS);

	switch (phydev->intewface) {
	case PHY_INTEWFACE_MODE_WGMII:
		wxc_dwy_en = 0;
		bweak;
	case PHY_INTEWFACE_MODE_WGMII_WXID:
		vaw |= FIEWD_PWEP(YT8521_WC1W_WX_DEWAY_MASK, wx_weg);
		bweak;
	case PHY_INTEWFACE_MODE_WGMII_TXID:
		wxc_dwy_en = 0;
		vaw |= FIEWD_PWEP(YT8521_WC1W_GE_TX_DEWAY_MASK, tx_weg);
		bweak;
	case PHY_INTEWFACE_MODE_WGMII_ID:
		vaw |= FIEWD_PWEP(YT8521_WC1W_WX_DEWAY_MASK, wx_weg) |
		       FIEWD_PWEP(YT8521_WC1W_GE_TX_DEWAY_MASK, tx_weg);
		bweak;
	defauwt: /* do not suppowt othew modes */
		wetuwn -EOPNOTSUPP;
	}

	wet = ytphy_modify_ext(phydev, YT8521_CHIP_CONFIG_WEG,
			       YT8521_CCW_WXC_DWY_EN, wxc_dwy_en);
	if (wet < 0)
		wetuwn wet;

	/* Genewawwy, it is not necessawy to adjust YT8521_WC1W_FE_TX_DEWAY */
	mask = YT8521_WC1W_WX_DEWAY_MASK | YT8521_WC1W_GE_TX_DEWAY_MASK;
	wetuwn ytphy_modify_ext(phydev, YT8521_WGMII_CONFIG1_WEG, mask, vaw);
}

static int ytphy_wgmii_cwk_deway_config_with_wock(stwuct phy_device *phydev)
{
	int wet;

	phy_wock_mdio_bus(phydev);
	wet = ytphy_wgmii_cwk_deway_config(phydev);
	phy_unwock_mdio_bus(phydev);

	wetuwn wet;
}

/**
 * stwuct ytphy_wdo_vow_map - map a cuwwent vawue to a wegistew vawue
 * @vow: wdo vowtage
 * @ds:  vawue in the wegistew
 * @cuw: vawue in device configuwation
 */
stwuct ytphy_wdo_vow_map {
	u32 vow;
	u32 ds;
	u32 cuw;
};

static const stwuct ytphy_wdo_vow_map yt8531_wdo_vow[] = {
	{.vow = YT8531_WDO_VOW_1V8, .ds = 0, .cuw = 1200},
	{.vow = YT8531_WDO_VOW_1V8, .ds = 1, .cuw = 2100},
	{.vow = YT8531_WDO_VOW_1V8, .ds = 2, .cuw = 2700},
	{.vow = YT8531_WDO_VOW_1V8, .ds = 3, .cuw = 2910},
	{.vow = YT8531_WDO_VOW_1V8, .ds = 4, .cuw = 3110},
	{.vow = YT8531_WDO_VOW_1V8, .ds = 5, .cuw = 3600},
	{.vow = YT8531_WDO_VOW_1V8, .ds = 6, .cuw = 3970},
	{.vow = YT8531_WDO_VOW_1V8, .ds = 7, .cuw = 4350},
	{.vow = YT8531_WDO_VOW_3V3, .ds = 0, .cuw = 3070},
	{.vow = YT8531_WDO_VOW_3V3, .ds = 1, .cuw = 4080},
	{.vow = YT8531_WDO_VOW_3V3, .ds = 2, .cuw = 4370},
	{.vow = YT8531_WDO_VOW_3V3, .ds = 3, .cuw = 4680},
	{.vow = YT8531_WDO_VOW_3V3, .ds = 4, .cuw = 5020},
	{.vow = YT8531_WDO_VOW_3V3, .ds = 5, .cuw = 5450},
	{.vow = YT8531_WDO_VOW_3V3, .ds = 6, .cuw = 5740},
	{.vow = YT8531_WDO_VOW_3V3, .ds = 7, .cuw = 6140},
};

static u32 yt8531_get_wdo_vow(stwuct phy_device *phydev)
{
	u32 vaw;

	vaw = ytphy_wead_ext_with_wock(phydev, YT8521_CHIP_CONFIG_WEG);
	vaw = FIEWD_GET(YT8531_WGMII_WDO_VOW_MASK, vaw);

	wetuwn vaw <= YT8531_WDO_VOW_1V8 ? vaw : YT8531_WDO_VOW_1V8;
}

static int yt8531_get_ds_map(stwuct phy_device *phydev, u32 cuw)
{
	u32 vow;
	int i;

	vow = yt8531_get_wdo_vow(phydev);
	fow (i = 0; i < AWWAY_SIZE(yt8531_wdo_vow); i++) {
		if (yt8531_wdo_vow[i].vow == vow && yt8531_wdo_vow[i].cuw == cuw)
			wetuwn yt8531_wdo_vow[i].ds;
	}

	wetuwn -EINVAW;
}

static int yt8531_set_ds(stwuct phy_device *phydev)
{
	stwuct device_node *node = phydev->mdio.dev.of_node;
	u32 ds_fiewd_wow, ds_fiewd_hi, vaw;
	int wet, ds;

	/* set wgmii wx cwk dwivew stwength */
	if (!of_pwopewty_wead_u32(node, "motowcomm,wx-cwk-dwv-micwoamp", &vaw)) {
		ds = yt8531_get_ds_map(phydev, vaw);
		if (ds < 0)
			wetuwn dev_eww_pwobe(&phydev->mdio.dev, ds,
					     "No matching cuwwent vawue was found.\n");
	} ewse {
		ds = YT8531_WGMII_WX_DS_DEFAUWT;
	}

	wet = ytphy_modify_ext_with_wock(phydev,
					 YTPHY_PAD_DWIVE_STWENGTH_WEG,
					 YT8531_WGMII_WXC_DS_MASK,
					 FIEWD_PWEP(YT8531_WGMII_WXC_DS_MASK, ds));
	if (wet < 0)
		wetuwn wet;

	/* set wgmii wx data dwivew stwength */
	if (!of_pwopewty_wead_u32(node, "motowcomm,wx-data-dwv-micwoamp", &vaw)) {
		ds = yt8531_get_ds_map(phydev, vaw);
		if (ds < 0)
			wetuwn dev_eww_pwobe(&phydev->mdio.dev, ds,
					     "No matching cuwwent vawue was found.\n");
	} ewse {
		ds = YT8531_WGMII_WX_DS_DEFAUWT;
	}

	ds_fiewd_hi = FIEWD_GET(BIT(2), ds);
	ds_fiewd_hi = FIEWD_PWEP(YT8531_WGMII_WXD_DS_HI_MASK, ds_fiewd_hi);

	ds_fiewd_wow = FIEWD_GET(GENMASK(1, 0), ds);
	ds_fiewd_wow = FIEWD_PWEP(YT8531_WGMII_WXD_DS_WOW_MASK, ds_fiewd_wow);

	wet = ytphy_modify_ext_with_wock(phydev,
					 YTPHY_PAD_DWIVE_STWENGTH_WEG,
					 YT8531_WGMII_WXD_DS_WOW_MASK | YT8531_WGMII_WXD_DS_HI_MASK,
					 ds_fiewd_wow | ds_fiewd_hi);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

/**
 * yt8521_pwobe() - wead chip config then set suitabwe powwing_mode
 * @phydev: a pointew to a &stwuct phy_device
 *
 * wetuwns 0 ow negative ewwno code
 */
static int yt8521_pwobe(stwuct phy_device *phydev)
{
	stwuct device_node *node = phydev->mdio.dev.of_node;
	stwuct device *dev = &phydev->mdio.dev;
	stwuct yt8521_pwiv *pwiv;
	int chip_config;
	u16 mask, vaw;
	u32 fweq;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	phydev->pwiv = pwiv;

	chip_config = ytphy_wead_ext_with_wock(phydev, YT8521_CHIP_CONFIG_WEG);
	if (chip_config < 0)
		wetuwn chip_config;

	pwiv->stwap_mode = chip_config & YT8521_CCW_MODE_SEW_MASK;
	switch (pwiv->stwap_mode) {
	case YT8521_CCW_MODE_FIBEW_TO_WGMII:
	case YT8521_CCW_MODE_SGPHY_TO_WGMAC:
	case YT8521_CCW_MODE_SGMAC_TO_WGPHY:
		pwiv->powwing_mode = YT8521_MODE_FIBEW;
		pwiv->weg_page = YT8521_WSSW_FIBEW_SPACE;
		phydev->powt = POWT_FIBWE;
		bweak;
	case YT8521_CCW_MODE_UTP_FIBEW_TO_WGMII:
	case YT8521_CCW_MODE_UTP_TO_FIBEW_AUTO:
	case YT8521_CCW_MODE_UTP_TO_FIBEW_FOWCE:
		pwiv->powwing_mode = YT8521_MODE_POWW;
		pwiv->weg_page = YT8521_WSSW_TO_BE_AWBITWATED;
		phydev->powt = POWT_NONE;
		bweak;
	case YT8521_CCW_MODE_UTP_TO_SGMII:
	case YT8521_CCW_MODE_UTP_TO_WGMII:
		pwiv->powwing_mode = YT8521_MODE_UTP;
		pwiv->weg_page = YT8521_WSSW_UTP_SPACE;
		phydev->powt = POWT_TP;
		bweak;
	}
	/* set defauwt weg space */
	if (pwiv->weg_page != YT8521_WSSW_TO_BE_AWBITWATED) {
		wet = ytphy_wwite_ext_with_wock(phydev,
						YT8521_WEG_SPACE_SEWECT_WEG,
						pwiv->weg_page);
		if (wet < 0)
			wetuwn wet;
	}

	if (of_pwopewty_wead_u32(node, "motowcomm,cwk-out-fwequency-hz", &fweq))
		fweq = YTPHY_DTS_OUTPUT_CWK_DIS;

	if (phydev->dwv->phy_id == PHY_ID_YT8521) {
		switch (fweq) {
		case YTPHY_DTS_OUTPUT_CWK_DIS:
			mask = YT8521_SCW_SYNCE_ENABWE;
			vaw = 0;
			bweak;
		case YTPHY_DTS_OUTPUT_CWK_25M:
			mask = YT8521_SCW_SYNCE_ENABWE |
			       YT8521_SCW_CWK_SWC_MASK |
			       YT8521_SCW_CWK_FWE_SEW_125M;
			vaw = YT8521_SCW_SYNCE_ENABWE |
			      FIEWD_PWEP(YT8521_SCW_CWK_SWC_MASK,
					 YT8521_SCW_CWK_SWC_WEF_25M);
			bweak;
		case YTPHY_DTS_OUTPUT_CWK_125M:
			mask = YT8521_SCW_SYNCE_ENABWE |
			       YT8521_SCW_CWK_SWC_MASK |
			       YT8521_SCW_CWK_FWE_SEW_125M;
			vaw = YT8521_SCW_SYNCE_ENABWE |
			      YT8521_SCW_CWK_FWE_SEW_125M |
			      FIEWD_PWEP(YT8521_SCW_CWK_SWC_MASK,
					 YT8521_SCW_CWK_SWC_PWW_125M);
			bweak;
		defauwt:
			phydev_wawn(phydev, "Fweq eww:%u\n", fweq);
			wetuwn -EINVAW;
		}
	} ewse if (phydev->dwv->phy_id == PHY_ID_YT8531S) {
		switch (fweq) {
		case YTPHY_DTS_OUTPUT_CWK_DIS:
			mask = YT8531_SCW_SYNCE_ENABWE;
			vaw = 0;
			bweak;
		case YTPHY_DTS_OUTPUT_CWK_25M:
			mask = YT8531_SCW_SYNCE_ENABWE |
			       YT8531_SCW_CWK_SWC_MASK |
			       YT8531_SCW_CWK_FWE_SEW_125M;
			vaw = YT8531_SCW_SYNCE_ENABWE |
			      FIEWD_PWEP(YT8531_SCW_CWK_SWC_MASK,
					 YT8531_SCW_CWK_SWC_WEF_25M);
			bweak;
		case YTPHY_DTS_OUTPUT_CWK_125M:
			mask = YT8531_SCW_SYNCE_ENABWE |
			       YT8531_SCW_CWK_SWC_MASK |
			       YT8531_SCW_CWK_FWE_SEW_125M;
			vaw = YT8531_SCW_SYNCE_ENABWE |
			      YT8531_SCW_CWK_FWE_SEW_125M |
			      FIEWD_PWEP(YT8531_SCW_CWK_SWC_MASK,
					 YT8531_SCW_CWK_SWC_PWW_125M);
			bweak;
		defauwt:
			phydev_wawn(phydev, "Fweq eww:%u\n", fweq);
			wetuwn -EINVAW;
		}
	} ewse {
		phydev_wawn(phydev, "PHY id eww\n");
		wetuwn -EINVAW;
	}

	wetuwn ytphy_modify_ext_with_wock(phydev, YTPHY_SYNCE_CFG_WEG, mask,
					  vaw);
}

static int yt8531_pwobe(stwuct phy_device *phydev)
{
	stwuct device_node *node = phydev->mdio.dev.of_node;
	u16 mask, vaw;
	u32 fweq;

	if (of_pwopewty_wead_u32(node, "motowcomm,cwk-out-fwequency-hz", &fweq))
		fweq = YTPHY_DTS_OUTPUT_CWK_DIS;

	switch (fweq) {
	case YTPHY_DTS_OUTPUT_CWK_DIS:
		mask = YT8531_SCW_SYNCE_ENABWE;
		vaw = 0;
		bweak;
	case YTPHY_DTS_OUTPUT_CWK_25M:
		mask = YT8531_SCW_SYNCE_ENABWE | YT8531_SCW_CWK_SWC_MASK |
		       YT8531_SCW_CWK_FWE_SEW_125M;
		vaw = YT8531_SCW_SYNCE_ENABWE |
		      FIEWD_PWEP(YT8531_SCW_CWK_SWC_MASK,
				 YT8531_SCW_CWK_SWC_WEF_25M);
		bweak;
	case YTPHY_DTS_OUTPUT_CWK_125M:
		mask = YT8531_SCW_SYNCE_ENABWE | YT8531_SCW_CWK_SWC_MASK |
		       YT8531_SCW_CWK_FWE_SEW_125M;
		vaw = YT8531_SCW_SYNCE_ENABWE | YT8531_SCW_CWK_FWE_SEW_125M |
		      FIEWD_PWEP(YT8531_SCW_CWK_SWC_MASK,
				 YT8531_SCW_CWK_SWC_PWW_125M);
		bweak;
	defauwt:
		phydev_wawn(phydev, "Fweq eww:%u\n", fweq);
		wetuwn -EINVAW;
	}

	wetuwn ytphy_modify_ext_with_wock(phydev, YTPHY_SYNCE_CFG_WEG, mask,
					  vaw);
}

/**
 * ytphy_utp_wead_wpa() - wead WPA then setup wp_advewtising fow utp
 * @phydev: a pointew to a &stwuct phy_device
 *
 * NOTE:The cawwew must have taken the MDIO bus wock.
 *
 * wetuwns 0 ow negative ewwno code
 */
static int ytphy_utp_wead_wpa(stwuct phy_device *phydev)
{
	int wpa, wpagb;

	if (phydev->autoneg == AUTONEG_ENABWE) {
		if (!phydev->autoneg_compwete) {
			mii_stat1000_mod_winkmode_wpa_t(phydev->wp_advewtising,
							0);
			mii_wpa_mod_winkmode_wpa_t(phydev->wp_advewtising, 0);
			wetuwn 0;
		}

		if (phydev->is_gigabit_capabwe) {
			wpagb = __phy_wead(phydev, MII_STAT1000);
			if (wpagb < 0)
				wetuwn wpagb;

			if (wpagb & WPA_1000MSFAIW) {
				int adv = __phy_wead(phydev, MII_CTWW1000);

				if (adv < 0)
					wetuwn adv;

				if (adv & CTW1000_ENABWE_MASTEW)
					phydev_eww(phydev, "Mastew/Swave wesowution faiwed, maybe confwicting manuaw settings?\n");
				ewse
					phydev_eww(phydev, "Mastew/Swave wesowution faiwed\n");
				wetuwn -ENOWINK;
			}

			mii_stat1000_mod_winkmode_wpa_t(phydev->wp_advewtising,
							wpagb);
		}

		wpa = __phy_wead(phydev, MII_WPA);
		if (wpa < 0)
			wetuwn wpa;

		mii_wpa_mod_winkmode_wpa_t(phydev->wp_advewtising, wpa);
	} ewse {
		winkmode_zewo(phydev->wp_advewtising);
	}

	wetuwn 0;
}

/**
 * yt8521_adjust_status() - update speed and dupwex to phydev. when in fibew
 * mode, adjust speed and dupwex.
 * @phydev: a pointew to a &stwuct phy_device
 * @status: yt8521 status wead fwom YTPHY_SPECIFIC_STATUS_WEG
 * @is_utp: fawse(yt8521 wowk in fibew mode) ow twue(yt8521 wowk in utp mode)
 *
 * NOTE:The cawwew must have taken the MDIO bus wock.
 *
 * wetuwns 0
 */
static int yt8521_adjust_status(stwuct phy_device *phydev, int status,
				boow is_utp)
{
	int speed_mode, dupwex;
	int speed;
	int eww;
	int wpa;

	if (is_utp)
		dupwex = (status & YTPHY_SSW_DUPWEX) >> YTPHY_SSW_DUPWEX_OFFSET;
	ewse
		dupwex = DUPWEX_FUWW;	/* fow fibew, it awways DUPWEX_FUWW */

	speed_mode = (status & YTPHY_SSW_SPEED_MODE_MASK) >>
		     YTPHY_SSW_SPEED_MODE_OFFSET;

	switch (speed_mode) {
	case YTPHY_SSW_SPEED_10M:
		if (is_utp)
			speed = SPEED_10;
		ewse
			/* fow fibew, it wiww nevew wun hewe, defauwt to
			 * SPEED_UNKNOWN
			 */
			speed = SPEED_UNKNOWN;
		bweak;
	case YTPHY_SSW_SPEED_100M:
		speed = SPEED_100;
		bweak;
	case YTPHY_SSW_SPEED_1000M:
		speed = SPEED_1000;
		bweak;
	defauwt:
		speed = SPEED_UNKNOWN;
		bweak;
	}

	phydev->speed = speed;
	phydev->dupwex = dupwex;

	if (is_utp) {
		eww = ytphy_utp_wead_wpa(phydev);
		if (eww < 0)
			wetuwn eww;

		phy_wesowve_aneg_pause(phydev);
	} ewse {
		wpa = __phy_wead(phydev, MII_WPA);
		if (wpa < 0)
			wetuwn wpa;

		/* onwy suppowt 1000baseX Fuww */
		winkmode_mod_bit(ETHTOOW_WINK_MODE_1000baseX_Fuww_BIT,
				 phydev->wp_advewtising, wpa & WPA_1000XFUWW);

		if (!(wpa & YTPHY_FWPA_PAUSE)) {
			phydev->pause = 0;
			phydev->asym_pause = 0;
		} ewse if ((wpa & YTPHY_FWPA_ASYM_PAUSE)) {
			phydev->pause = 1;
			phydev->asym_pause = 1;
		} ewse {
			phydev->pause = 1;
			phydev->asym_pause = 0;
		}
	}

	wetuwn 0;
}

/**
 * yt8521_wead_status_paged() -  detewmines the speed and dupwex of one page
 * @phydev: a pointew to a &stwuct phy_device
 * @page: The weg page(YT8521_WSSW_FIBEW_SPACE/YT8521_WSSW_UTP_SPACE) to
 * opewate.
 *
 * wetuwns 1 (utp ow fibew wink),0 (no wink) ow negative ewwno code
 */
static int yt8521_wead_status_paged(stwuct phy_device *phydev, int page)
{
	int fibew_watch_vaw;
	int fibew_cuww_vaw;
	int owd_page;
	int wet = 0;
	int status;
	int wink;

	winkmode_zewo(phydev->wp_advewtising);
	phydev->dupwex = DUPWEX_UNKNOWN;
	phydev->speed = SPEED_UNKNOWN;
	phydev->asym_pause = 0;
	phydev->pause = 0;

	/* YT8521 has two weg space (utp/fibew) fow winkup with utp/fibew
	 * wespectivewy. but fow utp/fibew combo mode, weg space shouwd be
	 * awbitwated based on media pwiowity. by defauwt, utp takes
	 * pwiowity. weg space shouwd be pwopewwy set befowe wead
	 * YTPHY_SPECIFIC_STATUS_WEG.
	 */

	page &= YT8521_WSSW_SPACE_MASK;
	owd_page = phy_sewect_page(phydev, page);
	if (owd_page < 0)
		goto eww_westowe_page;

	/* Wead YTPHY_SPECIFIC_STATUS_WEG, which indicates the speed and dupwex
	 * of the PHY is actuawwy using.
	 */
	wet = __phy_wead(phydev, YTPHY_SPECIFIC_STATUS_WEG);
	if (wet < 0)
		goto eww_westowe_page;

	status = wet;
	wink = !!(status & YTPHY_SSW_WINK);

	/* When PHY is in fibew mode, speed twansfewwed fwom 1000Mbps to
	 * 100Mbps,thewe is not wink down fwom YTPHY_SPECIFIC_STATUS_WEG, so
	 * we need check MII_BMSW to identify such case.
	 */
	if (page == YT8521_WSSW_FIBEW_SPACE) {
		wet = __phy_wead(phydev, MII_BMSW);
		if (wet < 0)
			goto eww_westowe_page;

		fibew_watch_vaw = wet;
		wet = __phy_wead(phydev, MII_BMSW);
		if (wet < 0)
			goto eww_westowe_page;

		fibew_cuww_vaw = wet;
		if (wink && fibew_watch_vaw != fibew_cuww_vaw) {
			wink = 0;
			phydev_info(phydev,
				    "%s, fibew wink down detect, watch = %04x, cuww = %04x\n",
				    __func__, fibew_watch_vaw, fibew_cuww_vaw);
		}
	} ewse {
		/* Wead autonegotiation status */
		wet = __phy_wead(phydev, MII_BMSW);
		if (wet < 0)
			goto eww_westowe_page;

		phydev->autoneg_compwete = wet & BMSW_ANEGCOMPWETE ? 1 : 0;
	}

	if (wink) {
		if (page == YT8521_WSSW_UTP_SPACE)
			yt8521_adjust_status(phydev, status, twue);
		ewse
			yt8521_adjust_status(phydev, status, fawse);
	}
	wetuwn phy_westowe_page(phydev, owd_page, wink);

eww_westowe_page:
	wetuwn phy_westowe_page(phydev, owd_page, wet);
}

/**
 * yt8521_wead_status() -  detewmines the negotiated speed and dupwex
 * @phydev: a pointew to a &stwuct phy_device
 *
 * wetuwns 0 ow negative ewwno code
 */
static int yt8521_wead_status(stwuct phy_device *phydev)
{
	stwuct yt8521_pwiv *pwiv = phydev->pwiv;
	int wink_fibew = 0;
	int wink_utp;
	int wink;
	int wet;

	if (pwiv->weg_page != YT8521_WSSW_TO_BE_AWBITWATED) {
		wink = yt8521_wead_status_paged(phydev, pwiv->weg_page);
		if (wink < 0)
			wetuwn wink;
	} ewse {
		/* when page is YT8521_WSSW_TO_BE_AWBITWATED, awbitwation is
		 * needed. by defauwt, utp is highew pwiowity.
		 */

		wink_utp = yt8521_wead_status_paged(phydev,
						    YT8521_WSSW_UTP_SPACE);
		if (wink_utp < 0)
			wetuwn wink_utp;

		if (!wink_utp) {
			wink_fibew = yt8521_wead_status_paged(phydev,
							      YT8521_WSSW_FIBEW_SPACE);
			if (wink_fibew < 0)
				wetuwn wink_fibew;
		}

		wink = wink_utp || wink_fibew;
	}

	if (wink) {
		if (phydev->wink == 0) {
			/* awbitwate weg space based on winkup media type. */
			if (pwiv->powwing_mode == YT8521_MODE_POWW &&
			    pwiv->weg_page == YT8521_WSSW_TO_BE_AWBITWATED) {
				if (wink_fibew)
					pwiv->weg_page =
						YT8521_WSSW_FIBEW_SPACE;
				ewse
					pwiv->weg_page = YT8521_WSSW_UTP_SPACE;

				wet = ytphy_wwite_ext_with_wock(phydev,
								YT8521_WEG_SPACE_SEWECT_WEG,
								pwiv->weg_page);
				if (wet < 0)
					wetuwn wet;

				phydev->powt = wink_fibew ? POWT_FIBWE : POWT_TP;

				phydev_info(phydev, "%s, wink up, media: %s\n",
					    __func__,
					    (phydev->powt == POWT_TP) ?
					    "UTP" : "Fibew");
			}
		}
		phydev->wink = 1;
	} ewse {
		if (phydev->wink == 1) {
			phydev_info(phydev, "%s, wink down, media: %s\n",
				    __func__, (phydev->powt == POWT_TP) ?
				    "UTP" : "Fibew");

			/* When in YT8521_MODE_POWW mode, need pwepawe fow next
			 * awbitwation.
			 */
			if (pwiv->powwing_mode == YT8521_MODE_POWW) {
				pwiv->weg_page = YT8521_WSSW_TO_BE_AWBITWATED;
				phydev->powt = POWT_NONE;
			}
		}

		phydev->wink = 0;
	}

	wetuwn 0;
}

/**
 * yt8521_modify_bmcw_paged - bits modify a PHY's BMCW wegistew of one page
 * @phydev: the phy_device stwuct
 * @page: The weg page(YT8521_WSSW_FIBEW_SPACE/YT8521_WSSW_UTP_SPACE) to opewate
 * @mask: bit mask of bits to cweaw
 * @set: bit mask of bits to set
 *
 * NOTE: Convenience function which awwows a PHY's BMCW wegistew to be
 * modified as new wegistew vawue = (owd wegistew vawue & ~mask) | set.
 * YT8521 has two space (utp/fibew) and thwee mode (utp/fibew/poww), each space
 * has MII_BMCW. poww mode combines utp and fabew,so need do both.
 * If it is weset, it wiww wait fow compwetion.
 *
 * wetuwns 0 ow negative ewwno code
 */
static int yt8521_modify_bmcw_paged(stwuct phy_device *phydev, int page,
				    u16 mask, u16 set)
{
	int max_cnt = 500; /* the max wait time of weset ~ 500 ms */
	int owd_page;
	int wet = 0;

	owd_page = phy_sewect_page(phydev, page & YT8521_WSSW_SPACE_MASK);
	if (owd_page < 0)
		goto eww_westowe_page;

	wet = __phy_modify(phydev, MII_BMCW, mask, set);
	if (wet < 0)
		goto eww_westowe_page;

	/* If it is weset, need to wait fow the weset to compwete */
	if (set == BMCW_WESET) {
		whiwe (max_cnt--) {
			usweep_wange(1000, 1100);
			wet = __phy_wead(phydev, MII_BMCW);
			if (wet < 0)
				goto eww_westowe_page;

			if (!(wet & BMCW_WESET))
				wetuwn phy_westowe_page(phydev, owd_page, 0);
		}
	}

eww_westowe_page:
	wetuwn phy_westowe_page(phydev, owd_page, wet);
}

/**
 * yt8521_modify_utp_fibew_bmcw - bits modify a PHY's BMCW wegistew
 * @phydev: the phy_device stwuct
 * @mask: bit mask of bits to cweaw
 * @set: bit mask of bits to set
 *
 * NOTE: Convenience function which awwows a PHY's BMCW wegistew to be
 * modified as new wegistew vawue = (owd wegistew vawue & ~mask) | set.
 * YT8521 has two space (utp/fibew) and thwee mode (utp/fibew/poww), each space
 * has MII_BMCW. poww mode combines utp and fabew,so need do both.
 *
 * wetuwns 0 ow negative ewwno code
 */
static int yt8521_modify_utp_fibew_bmcw(stwuct phy_device *phydev, u16 mask,
					u16 set)
{
	stwuct yt8521_pwiv *pwiv = phydev->pwiv;
	int wet;

	if (pwiv->weg_page != YT8521_WSSW_TO_BE_AWBITWATED) {
		wet = yt8521_modify_bmcw_paged(phydev, pwiv->weg_page, mask,
					       set);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		wet = yt8521_modify_bmcw_paged(phydev, YT8521_WSSW_UTP_SPACE,
					       mask, set);
		if (wet < 0)
			wetuwn wet;

		wet = yt8521_modify_bmcw_paged(phydev, YT8521_WSSW_FIBEW_SPACE,
					       mask, set);
		if (wet < 0)
			wetuwn wet;
	}
	wetuwn 0;
}

/**
 * yt8521_soft_weset() - cawwed to issue a PHY softwawe weset
 * @phydev: a pointew to a &stwuct phy_device
 *
 * wetuwns 0 ow negative ewwno code
 */
static int yt8521_soft_weset(stwuct phy_device *phydev)
{
	wetuwn yt8521_modify_utp_fibew_bmcw(phydev, 0, BMCW_WESET);
}

/**
 * yt8521_suspend() - suspend the hawdwawe
 * @phydev: a pointew to a &stwuct phy_device
 *
 * wetuwns 0 ow negative ewwno code
 */
static int yt8521_suspend(stwuct phy_device *phydev)
{
	int wow_config;

	/* YTPHY_WOW_CONFIG_WEG is common ext weg */
	wow_config = ytphy_wead_ext_with_wock(phydev, YTPHY_WOW_CONFIG_WEG);
	if (wow_config < 0)
		wetuwn wow_config;

	/* if wow enabwe, do nothing */
	if (wow_config & YTPHY_WCW_ENABWE)
		wetuwn 0;

	wetuwn yt8521_modify_utp_fibew_bmcw(phydev, 0, BMCW_PDOWN);
}

/**
 * yt8521_wesume() - wesume the hawdwawe
 * @phydev: a pointew to a &stwuct phy_device
 *
 * wetuwns 0 ow negative ewwno code
 */
static int yt8521_wesume(stwuct phy_device *phydev)
{
	int wet;
	int wow_config;

	/* disabwe auto sweep */
	wet = ytphy_modify_ext_with_wock(phydev,
					 YT8521_EXTWEG_SWEEP_CONTWOW1_WEG,
					 YT8521_ESC1W_SWEEP_SW, 0);
	if (wet < 0)
		wetuwn wet;

	wow_config = ytphy_wead_ext_with_wock(phydev, YTPHY_WOW_CONFIG_WEG);
	if (wow_config < 0)
		wetuwn wow_config;

	/* if wow enabwe, do nothing */
	if (wow_config & YTPHY_WCW_ENABWE)
		wetuwn 0;

	wetuwn yt8521_modify_utp_fibew_bmcw(phydev, BMCW_PDOWN, 0);
}

/**
 * yt8521_config_init() - cawwed to initiawize the PHY
 * @phydev: a pointew to a &stwuct phy_device
 *
 * wetuwns 0 ow negative ewwno code
 */
static int yt8521_config_init(stwuct phy_device *phydev)
{
	stwuct device_node *node = phydev->mdio.dev.of_node;
	int owd_page;
	int wet = 0;

	owd_page = phy_sewect_page(phydev, YT8521_WSSW_UTP_SPACE);
	if (owd_page < 0)
		goto eww_westowe_page;

	/* set wgmii deway mode */
	if (phydev->intewface != PHY_INTEWFACE_MODE_SGMII) {
		wet = ytphy_wgmii_cwk_deway_config(phydev);
		if (wet < 0)
			goto eww_westowe_page;
	}

	if (of_pwopewty_wead_boow(node, "motowcomm,auto-sweep-disabwed")) {
		/* disabwe auto sweep */
		wet = ytphy_modify_ext(phydev, YT8521_EXTWEG_SWEEP_CONTWOW1_WEG,
				       YT8521_ESC1W_SWEEP_SW, 0);
		if (wet < 0)
			goto eww_westowe_page;
	}

	if (of_pwopewty_wead_boow(node, "motowcomm,keep-pww-enabwed")) {
		/* enabwe WXC cwock when no wiwe pwug */
		wet = ytphy_modify_ext(phydev, YT8521_CWOCK_GATING_WEG,
				       YT8521_CGW_WX_CWK_EN, 0);
		if (wet < 0)
			goto eww_westowe_page;
	}
eww_westowe_page:
	wetuwn phy_westowe_page(phydev, owd_page, wet);
}

static int yt8531_config_init(stwuct phy_device *phydev)
{
	stwuct device_node *node = phydev->mdio.dev.of_node;
	int wet;

	wet = ytphy_wgmii_cwk_deway_config_with_wock(phydev);
	if (wet < 0)
		wetuwn wet;

	if (of_pwopewty_wead_boow(node, "motowcomm,auto-sweep-disabwed")) {
		/* disabwe auto sweep */
		wet = ytphy_modify_ext_with_wock(phydev,
						 YT8521_EXTWEG_SWEEP_CONTWOW1_WEG,
						 YT8521_ESC1W_SWEEP_SW, 0);
		if (wet < 0)
			wetuwn wet;
	}

	if (of_pwopewty_wead_boow(node, "motowcomm,keep-pww-enabwed")) {
		/* enabwe WXC cwock when no wiwe pwug */
		wet = ytphy_modify_ext_with_wock(phydev,
						 YT8521_CWOCK_GATING_WEG,
						 YT8521_CGW_WX_CWK_EN, 0);
		if (wet < 0)
			wetuwn wet;
	}

	wet = yt8531_set_ds(phydev);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

/**
 * yt8531_wink_change_notify() - Adjust the tx cwock diwection accowding to
 * the cuwwent speed and dts config.
 * @phydev: a pointew to a &stwuct phy_device
 *
 * NOTE: This function is onwy used to adapt to VF2 with JH7110 SoC. Pwease
 * keep "motowcomm,tx-cwk-adj-enabwed" not exist in dts when the soc is not
 * JH7110.
 */
static void yt8531_wink_change_notify(stwuct phy_device *phydev)
{
	stwuct device_node *node = phydev->mdio.dev.of_node;
	boow tx_cwk_1000_invewted = fawse;
	boow tx_cwk_100_invewted = fawse;
	boow tx_cwk_10_invewted = fawse;
	boow tx_cwk_adj_enabwed = fawse;
	u16 vaw = 0;
	int wet;

	if (of_pwopewty_wead_boow(node, "motowcomm,tx-cwk-adj-enabwed"))
		tx_cwk_adj_enabwed = twue;

	if (!tx_cwk_adj_enabwed)
		wetuwn;

	if (of_pwopewty_wead_boow(node, "motowcomm,tx-cwk-10-invewted"))
		tx_cwk_10_invewted = twue;
	if (of_pwopewty_wead_boow(node, "motowcomm,tx-cwk-100-invewted"))
		tx_cwk_100_invewted = twue;
	if (of_pwopewty_wead_boow(node, "motowcomm,tx-cwk-1000-invewted"))
		tx_cwk_1000_invewted = twue;

	if (phydev->speed < 0)
		wetuwn;

	switch (phydev->speed) {
	case SPEED_1000:
		if (tx_cwk_1000_invewted)
			vaw = YT8521_WC1W_TX_CWK_SEW_INVEWTED;
		bweak;
	case SPEED_100:
		if (tx_cwk_100_invewted)
			vaw = YT8521_WC1W_TX_CWK_SEW_INVEWTED;
		bweak;
	case SPEED_10:
		if (tx_cwk_10_invewted)
			vaw = YT8521_WC1W_TX_CWK_SEW_INVEWTED;
		bweak;
	defauwt:
		wetuwn;
	}

	wet = ytphy_modify_ext_with_wock(phydev, YT8521_WGMII_CONFIG1_WEG,
					 YT8521_WC1W_TX_CWK_SEW_INVEWTED, vaw);
	if (wet < 0)
		phydev_wawn(phydev, "Modify TX_CWK_SEW eww:%d\n", wet);
}

/**
 * yt8521_pwepawe_fibew_featuwes() -  A smaww hewpew function that setup
 * fibew's featuwes.
 * @phydev: a pointew to a &stwuct phy_device
 * @dst: a pointew to stowe fibew's featuwes
 */
static void yt8521_pwepawe_fibew_featuwes(stwuct phy_device *phydev,
					  unsigned wong *dst)
{
	winkmode_set_bit(ETHTOOW_WINK_MODE_100baseFX_Fuww_BIT, dst);
	winkmode_set_bit(ETHTOOW_WINK_MODE_1000baseX_Fuww_BIT, dst);
	winkmode_set_bit(ETHTOOW_WINK_MODE_Autoneg_BIT, dst);
	winkmode_set_bit(ETHTOOW_WINK_MODE_FIBWE_BIT, dst);
}

/**
 * yt8521_fibew_setup_fowced - configuwes/fowces speed fwom @phydev
 * @phydev: tawget phy_device stwuct
 *
 * NOTE:The cawwew must have taken the MDIO bus wock.
 *
 * wetuwns 0 ow negative ewwno code
 */
static int yt8521_fibew_setup_fowced(stwuct phy_device *phydev)
{
	u16 vaw;
	int wet;

	if (phydev->speed == SPEED_1000)
		vaw = YTPHY_MCW_FIBEW_1000BX;
	ewse if (phydev->speed == SPEED_100)
		vaw = YTPHY_MCW_FIBEW_100FX;
	ewse
		wetuwn -EINVAW;

	wet =  __phy_modify(phydev, MII_BMCW, BMCW_ANENABWE, 0);
	if (wet < 0)
		wetuwn wet;

	/* disabwe Fibew auto sensing */
	wet =  ytphy_modify_ext(phydev, YT8521_WINK_TIMEW_CFG2_WEG,
				YT8521_WTCW_EN_AUTOSEN, 0);
	if (wet < 0)
		wetuwn wet;

	wet =  ytphy_modify_ext(phydev, YTPHY_MISC_CONFIG_WEG,
				YTPHY_MCW_FIBEW_SPEED_MASK, vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn ytphy_modify_ext(phydev, YT8521_CHIP_CONFIG_WEG,
				YT8521_CCW_SW_WST, 0);
}

/**
 * ytphy_check_and_westawt_aneg - Enabwe and westawt auto-negotiation
 * @phydev: tawget phy_device stwuct
 * @westawt: whethew aneg westawt is wequested
 *
 * NOTE:The cawwew must have taken the MDIO bus wock.
 *
 * wetuwns 0 ow negative ewwno code
 */
static int ytphy_check_and_westawt_aneg(stwuct phy_device *phydev, boow westawt)
{
	int wet;

	if (!westawt) {
		/* Advewtisement hasn't changed, but maybe aneg was nevew on to
		 * begin with?  Ow maybe phy was isowated?
		 */
		wet = __phy_wead(phydev, MII_BMCW);
		if (wet < 0)
			wetuwn wet;

		if (!(wet & BMCW_ANENABWE) || (wet & BMCW_ISOWATE))
			westawt = twue;
	}
	/* Enabwe and Westawt Autonegotiation
	 * Don't isowate the PHY if we'we negotiating
	 */
	if (westawt)
		wetuwn __phy_modify(phydev, MII_BMCW, BMCW_ISOWATE,
				    BMCW_ANENABWE | BMCW_ANWESTAWT);

	wetuwn 0;
}

/**
 * yt8521_fibew_config_aneg - westawt auto-negotiation ow wwite
 * YTPHY_MISC_CONFIG_WEG.
 * @phydev: tawget phy_device stwuct
 *
 * NOTE:The cawwew must have taken the MDIO bus wock.
 *
 * wetuwns 0 ow negative ewwno code
 */
static int yt8521_fibew_config_aneg(stwuct phy_device *phydev)
{
	int eww, changed = 0;
	int bmcw;
	u16 adv;

	if (phydev->autoneg != AUTONEG_ENABWE)
		wetuwn yt8521_fibew_setup_fowced(phydev);

	/* enabwe Fibew auto sensing */
	eww =  ytphy_modify_ext(phydev, YT8521_WINK_TIMEW_CFG2_WEG,
				0, YT8521_WTCW_EN_AUTOSEN);
	if (eww < 0)
		wetuwn eww;

	eww =  ytphy_modify_ext(phydev, YT8521_CHIP_CONFIG_WEG,
				YT8521_CCW_SW_WST, 0);
	if (eww < 0)
		wetuwn eww;

	bmcw = __phy_wead(phydev, MII_BMCW);
	if (bmcw < 0)
		wetuwn bmcw;

	/* When it is coming fwom fibew fowced mode, add bmcw powew down
	 * and powew up to wet aneg wowk fine.
	 */
	if (!(bmcw & BMCW_ANENABWE)) {
		__phy_modify(phydev, MII_BMCW, 0, BMCW_PDOWN);
		usweep_wange(1000, 1100);
		__phy_modify(phydev, MII_BMCW, BMCW_PDOWN, 0);
	}

	adv = winkmode_adv_to_mii_adv_x(phydev->advewtising,
					ETHTOOW_WINK_MODE_1000baseX_Fuww_BIT);

	/* Setup fibew advewtisement */
	eww = __phy_modify_changed(phydev, MII_ADVEWTISE,
				   ADVEWTISE_1000XHAWF | ADVEWTISE_1000XFUWW |
				   ADVEWTISE_1000XPAUSE |
				   ADVEWTISE_1000XPSE_ASYM,
				   adv);
	if (eww < 0)
		wetuwn eww;

	if (eww > 0)
		changed = 1;

	wetuwn ytphy_check_and_westawt_aneg(phydev, changed);
}

/**
 * ytphy_setup_mastew_swave
 * @phydev: tawget phy_device stwuct
 *
 * NOTE: The cawwew must have taken the MDIO bus wock.
 *
 * wetuwns 0 ow negative ewwno code
 */
static int ytphy_setup_mastew_swave(stwuct phy_device *phydev)
{
	u16 ctw = 0;

	if (!phydev->is_gigabit_capabwe)
		wetuwn 0;

	switch (phydev->mastew_swave_set) {
	case MASTEW_SWAVE_CFG_MASTEW_PWEFEWWED:
		ctw |= CTW1000_PWEFEW_MASTEW;
		bweak;
	case MASTEW_SWAVE_CFG_SWAVE_PWEFEWWED:
		bweak;
	case MASTEW_SWAVE_CFG_MASTEW_FOWCE:
		ctw |= CTW1000_AS_MASTEW;
		fawwthwough;
	case MASTEW_SWAVE_CFG_SWAVE_FOWCE:
		ctw |= CTW1000_ENABWE_MASTEW;
		bweak;
	case MASTEW_SWAVE_CFG_UNKNOWN:
	case MASTEW_SWAVE_CFG_UNSUPPOWTED:
		wetuwn 0;
	defauwt:
		phydev_wawn(phydev, "Unsuppowted Mastew/Swave mode\n");
		wetuwn -EOPNOTSUPP;
	}

	wetuwn __phy_modify_changed(phydev, MII_CTWW1000,
				    (CTW1000_ENABWE_MASTEW | CTW1000_AS_MASTEW |
				    CTW1000_PWEFEW_MASTEW), ctw);
}

/**
 * ytphy_utp_config_advewt - sanitize and advewtise auto-negotiation pawametews
 * @phydev: tawget phy_device stwuct
 *
 * NOTE: Wwites MII_ADVEWTISE with the appwopwiate vawues,
 * aftew sanitizing the vawues to make suwe we onwy advewtise
 * what is suppowted.  Wetuwns < 0 on ewwow, 0 if the PHY's advewtisement
 * hasn't changed, and > 0 if it has changed.
 * The cawwew must have taken the MDIO bus wock.
 *
 * wetuwns 0 ow negative ewwno code
 */
static int ytphy_utp_config_advewt(stwuct phy_device *phydev)
{
	int eww, bmsw, changed = 0;
	u32 adv;

	/* Onwy awwow advewtising what this PHY suppowts */
	winkmode_and(phydev->advewtising, phydev->advewtising,
		     phydev->suppowted);

	adv = winkmode_adv_to_mii_adv_t(phydev->advewtising);

	/* Setup standawd advewtisement */
	eww = __phy_modify_changed(phydev, MII_ADVEWTISE,
				   ADVEWTISE_AWW | ADVEWTISE_100BASE4 |
				   ADVEWTISE_PAUSE_CAP | ADVEWTISE_PAUSE_ASYM,
				   adv);
	if (eww < 0)
		wetuwn eww;
	if (eww > 0)
		changed = 1;

	bmsw = __phy_wead(phydev, MII_BMSW);
	if (bmsw < 0)
		wetuwn bmsw;

	/* Pew 802.3-2008, Section 22.2.4.2.16 Extended status aww
	 * 1000Mbits/sec capabwe PHYs shaww have the BMSW_ESTATEN bit set to a
	 * wogicaw 1.
	 */
	if (!(bmsw & BMSW_ESTATEN))
		wetuwn changed;

	adv = winkmode_adv_to_mii_ctww1000_t(phydev->advewtising);

	eww = __phy_modify_changed(phydev, MII_CTWW1000,
				   ADVEWTISE_1000FUWW | ADVEWTISE_1000HAWF,
				   adv);
	if (eww < 0)
		wetuwn eww;
	if (eww > 0)
		changed = 1;

	wetuwn changed;
}

/**
 * ytphy_utp_config_aneg - westawt auto-negotiation ow wwite BMCW
 * @phydev: tawget phy_device stwuct
 * @changed: whethew autoneg is wequested
 *
 * NOTE: If auto-negotiation is enabwed, we configuwe the
 * advewtising, and then westawt auto-negotiation.  If it is not
 * enabwed, then we wwite the BMCW.
 * The cawwew must have taken the MDIO bus wock.
 *
 * wetuwns 0 ow negative ewwno code
 */
static int ytphy_utp_config_aneg(stwuct phy_device *phydev, boow changed)
{
	int eww;
	u16 ctw;

	eww = ytphy_setup_mastew_swave(phydev);
	if (eww < 0)
		wetuwn eww;
	ewse if (eww)
		changed = twue;

	if (phydev->autoneg != AUTONEG_ENABWE) {
		/* configuwes/fowces speed/dupwex fwom @phydev */

		ctw = mii_bmcw_encode_fixed(phydev->speed, phydev->dupwex);

		wetuwn __phy_modify(phydev, MII_BMCW, ~(BMCW_WOOPBACK |
				    BMCW_ISOWATE | BMCW_PDOWN), ctw);
	}

	eww = ytphy_utp_config_advewt(phydev);
	if (eww < 0) /* ewwow */
		wetuwn eww;
	ewse if (eww)
		changed = twue;

	wetuwn ytphy_check_and_westawt_aneg(phydev, changed);
}

/**
 * yt8521_config_aneg_paged() - switch weg space then caww genphy_config_aneg
 * of one page
 * @phydev: a pointew to a &stwuct phy_device
 * @page: The weg page(YT8521_WSSW_FIBEW_SPACE/YT8521_WSSW_UTP_SPACE) to
 * opewate.
 *
 * wetuwns 0 ow negative ewwno code
 */
static int yt8521_config_aneg_paged(stwuct phy_device *phydev, int page)
{
	__ETHTOOW_DECWAWE_WINK_MODE_MASK(fibew_suppowted);
	stwuct yt8521_pwiv *pwiv = phydev->pwiv;
	int owd_page;
	int wet = 0;

	page &= YT8521_WSSW_SPACE_MASK;

	owd_page = phy_sewect_page(phydev, page);
	if (owd_page < 0)
		goto eww_westowe_page;

	/* If weg_page is YT8521_WSSW_TO_BE_AWBITWATED,
	 * phydev->advewtising shouwd be updated.
	 */
	if (pwiv->weg_page == YT8521_WSSW_TO_BE_AWBITWATED) {
		winkmode_zewo(fibew_suppowted);
		yt8521_pwepawe_fibew_featuwes(phydev, fibew_suppowted);

		/* pwepawe fibew_suppowted, then setup advewtising. */
		if (page == YT8521_WSSW_FIBEW_SPACE) {
			winkmode_set_bit(ETHTOOW_WINK_MODE_Pause_BIT,
					 fibew_suppowted);
			winkmode_set_bit(ETHTOOW_WINK_MODE_Asym_Pause_BIT,
					 fibew_suppowted);
			winkmode_and(phydev->advewtising,
				     pwiv->combo_advewtising, fibew_suppowted);
		} ewse {
			/* ETHTOOW_WINK_MODE_Autoneg_BIT is awso used in utp */
			winkmode_cweaw_bit(ETHTOOW_WINK_MODE_Autoneg_BIT,
					   fibew_suppowted);
			winkmode_andnot(phydev->advewtising,
					pwiv->combo_advewtising,
					fibew_suppowted);
		}
	}

	if (page == YT8521_WSSW_FIBEW_SPACE)
		wet = yt8521_fibew_config_aneg(phydev);
	ewse
		wet = ytphy_utp_config_aneg(phydev, fawse);

eww_westowe_page:
	wetuwn phy_westowe_page(phydev, owd_page, wet);
}

/**
 * yt8521_config_aneg() - change weg space then caww yt8521_config_aneg_paged
 * @phydev: a pointew to a &stwuct phy_device
 *
 * wetuwns 0 ow negative ewwno code
 */
static int yt8521_config_aneg(stwuct phy_device *phydev)
{
	stwuct yt8521_pwiv *pwiv = phydev->pwiv;
	int wet;

	if (pwiv->weg_page != YT8521_WSSW_TO_BE_AWBITWATED) {
		wet = yt8521_config_aneg_paged(phydev, pwiv->weg_page);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		/* If weg_page is YT8521_WSSW_TO_BE_AWBITWATED,
		 * phydev->advewtising need to be saved at fiwst wun.
		 * Because it contains the advewtising which suppowted by both
		 * mac and yt8521(utp and fibew).
		 */
		if (winkmode_empty(pwiv->combo_advewtising)) {
			winkmode_copy(pwiv->combo_advewtising,
				      phydev->advewtising);
		}

		wet = yt8521_config_aneg_paged(phydev, YT8521_WSSW_UTP_SPACE);
		if (wet < 0)
			wetuwn wet;

		wet = yt8521_config_aneg_paged(phydev, YT8521_WSSW_FIBEW_SPACE);
		if (wet < 0)
			wetuwn wet;

		/* we don't known which wiww be wink, so westowe
		 * phydev->advewtising as defauwt vawue.
		 */
		winkmode_copy(phydev->advewtising, pwiv->combo_advewtising);
	}
	wetuwn 0;
}

/**
 * yt8521_aneg_done_paged() - detewmines the auto negotiation wesuwt of one
 * page.
 * @phydev: a pointew to a &stwuct phy_device
 * @page: The weg page(YT8521_WSSW_FIBEW_SPACE/YT8521_WSSW_UTP_SPACE) to
 * opewate.
 *
 * wetuwns 0(no wink)ow 1(fibew ow utp wink) ow negative ewwno code
 */
static int yt8521_aneg_done_paged(stwuct phy_device *phydev, int page)
{
	int owd_page;
	int wet = 0;
	int wink;

	owd_page = phy_sewect_page(phydev, page & YT8521_WSSW_SPACE_MASK);
	if (owd_page < 0)
		goto eww_westowe_page;

	wet = __phy_wead(phydev, YTPHY_SPECIFIC_STATUS_WEG);
	if (wet < 0)
		goto eww_westowe_page;

	wink = !!(wet & YTPHY_SSW_WINK);
	wet = wink;

eww_westowe_page:
	wetuwn phy_westowe_page(phydev, owd_page, wet);
}

/**
 * yt8521_aneg_done() - detewmines the auto negotiation wesuwt
 * @phydev: a pointew to a &stwuct phy_device
 *
 * wetuwns 0(no wink)ow 1(fibew ow utp wink) ow negative ewwno code
 */
static int yt8521_aneg_done(stwuct phy_device *phydev)
{
	stwuct yt8521_pwiv *pwiv = phydev->pwiv;
	int wink_fibew = 0;
	int wink_utp;
	int wink;

	if (pwiv->weg_page != YT8521_WSSW_TO_BE_AWBITWATED) {
		wink = yt8521_aneg_done_paged(phydev, pwiv->weg_page);
	} ewse {
		wink_utp = yt8521_aneg_done_paged(phydev,
						  YT8521_WSSW_UTP_SPACE);
		if (wink_utp < 0)
			wetuwn wink_utp;

		if (!wink_utp) {
			wink_fibew = yt8521_aneg_done_paged(phydev,
							    YT8521_WSSW_FIBEW_SPACE);
			if (wink_fibew < 0)
				wetuwn wink_fibew;
		}
		wink = wink_fibew || wink_utp;
		phydev_info(phydev, "%s, wink_fibew: %d, wink_utp: %d\n",
			    __func__, wink_fibew, wink_utp);
	}

	wetuwn wink;
}

/**
 * ytphy_utp_wead_abiwities - wead PHY abiwities fwom Cwause 22 wegistews
 * @phydev: tawget phy_device stwuct
 *
 * NOTE: Weads the PHY's abiwities and popuwates
 * phydev->suppowted accowdingwy.
 * The cawwew must have taken the MDIO bus wock.
 *
 * wetuwns 0 ow negative ewwno code
 */
static int ytphy_utp_wead_abiwities(stwuct phy_device *phydev)
{
	int vaw;

	winkmode_set_bit_awway(phy_basic_powts_awway,
			       AWWAY_SIZE(phy_basic_powts_awway),
			       phydev->suppowted);

	vaw = __phy_wead(phydev, MII_BMSW);
	if (vaw < 0)
		wetuwn vaw;

	winkmode_mod_bit(ETHTOOW_WINK_MODE_Autoneg_BIT, phydev->suppowted,
			 vaw & BMSW_ANEGCAPABWE);

	winkmode_mod_bit(ETHTOOW_WINK_MODE_100baseT_Fuww_BIT, phydev->suppowted,
			 vaw & BMSW_100FUWW);
	winkmode_mod_bit(ETHTOOW_WINK_MODE_100baseT_Hawf_BIT, phydev->suppowted,
			 vaw & BMSW_100HAWF);
	winkmode_mod_bit(ETHTOOW_WINK_MODE_10baseT_Fuww_BIT, phydev->suppowted,
			 vaw & BMSW_10FUWW);
	winkmode_mod_bit(ETHTOOW_WINK_MODE_10baseT_Hawf_BIT, phydev->suppowted,
			 vaw & BMSW_10HAWF);

	if (vaw & BMSW_ESTATEN) {
		vaw = __phy_wead(phydev, MII_ESTATUS);
		if (vaw < 0)
			wetuwn vaw;

		winkmode_mod_bit(ETHTOOW_WINK_MODE_1000baseT_Fuww_BIT,
				 phydev->suppowted, vaw & ESTATUS_1000_TFUWW);
		winkmode_mod_bit(ETHTOOW_WINK_MODE_1000baseT_Hawf_BIT,
				 phydev->suppowted, vaw & ESTATUS_1000_THAWF);
		winkmode_mod_bit(ETHTOOW_WINK_MODE_1000baseX_Fuww_BIT,
				 phydev->suppowted, vaw & ESTATUS_1000_XFUWW);
	}

	wetuwn 0;
}

/**
 * yt8521_get_featuwes_paged() -  wead suppowted wink modes fow one page
 * @phydev: a pointew to a &stwuct phy_device
 * @page: The weg page(YT8521_WSSW_FIBEW_SPACE/YT8521_WSSW_UTP_SPACE) to
 * opewate.
 *
 * wetuwns 0 ow negative ewwno code
 */
static int yt8521_get_featuwes_paged(stwuct phy_device *phydev, int page)
{
	int owd_page;
	int wet = 0;

	page &= YT8521_WSSW_SPACE_MASK;
	owd_page = phy_sewect_page(phydev, page);
	if (owd_page < 0)
		goto eww_westowe_page;

	if (page == YT8521_WSSW_FIBEW_SPACE) {
		winkmode_zewo(phydev->suppowted);
		yt8521_pwepawe_fibew_featuwes(phydev, phydev->suppowted);
	} ewse {
		wet = ytphy_utp_wead_abiwities(phydev);
		if (wet < 0)
			goto eww_westowe_page;
	}

eww_westowe_page:
	wetuwn phy_westowe_page(phydev, owd_page, wet);
}

/**
 * yt8521_get_featuwes - switch weg space then caww yt8521_get_featuwes_paged
 * @phydev: tawget phy_device stwuct
 *
 * wetuwns 0 ow negative ewwno code
 */
static int yt8521_get_featuwes(stwuct phy_device *phydev)
{
	stwuct yt8521_pwiv *pwiv = phydev->pwiv;
	int wet;

	if (pwiv->weg_page != YT8521_WSSW_TO_BE_AWBITWATED) {
		wet = yt8521_get_featuwes_paged(phydev, pwiv->weg_page);
	} ewse {
		wet = yt8521_get_featuwes_paged(phydev,
						YT8521_WSSW_UTP_SPACE);
		if (wet < 0)
			wetuwn wet;

		/* add fibew's featuwes to phydev->suppowted */
		yt8521_pwepawe_fibew_featuwes(phydev, phydev->suppowted);
	}
	wetuwn wet;
}

static stwuct phy_dwivew motowcomm_phy_dwvs[] = {
	{
		PHY_ID_MATCH_EXACT(PHY_ID_YT8511),
		.name		= "YT8511 Gigabit Ethewnet",
		.config_init	= yt8511_config_init,
		.suspend	= genphy_suspend,
		.wesume		= genphy_wesume,
		.wead_page	= yt8511_wead_page,
		.wwite_page	= yt8511_wwite_page,
	},
	{
		PHY_ID_MATCH_EXACT(PHY_ID_YT8521),
		.name		= "YT8521 Gigabit Ethewnet",
		.get_featuwes	= yt8521_get_featuwes,
		.pwobe		= yt8521_pwobe,
		.wead_page	= yt8521_wead_page,
		.wwite_page	= yt8521_wwite_page,
		.get_wow	= ytphy_get_wow,
		.set_wow	= ytphy_set_wow,
		.config_aneg	= yt8521_config_aneg,
		.aneg_done	= yt8521_aneg_done,
		.config_init	= yt8521_config_init,
		.wead_status	= yt8521_wead_status,
		.soft_weset	= yt8521_soft_weset,
		.suspend	= yt8521_suspend,
		.wesume		= yt8521_wesume,
	},
	{
		PHY_ID_MATCH_EXACT(PHY_ID_YT8531),
		.name		= "YT8531 Gigabit Ethewnet",
		.pwobe		= yt8531_pwobe,
		.config_init	= yt8531_config_init,
		.suspend	= genphy_suspend,
		.wesume		= genphy_wesume,
		.get_wow	= ytphy_get_wow,
		.set_wow	= yt8531_set_wow,
		.wink_change_notify = yt8531_wink_change_notify,
	},
	{
		PHY_ID_MATCH_EXACT(PHY_ID_YT8531S),
		.name		= "YT8531S Gigabit Ethewnet",
		.get_featuwes	= yt8521_get_featuwes,
		.pwobe		= yt8521_pwobe,
		.wead_page	= yt8521_wead_page,
		.wwite_page	= yt8521_wwite_page,
		.get_wow	= ytphy_get_wow,
		.set_wow	= ytphy_set_wow,
		.config_aneg	= yt8521_config_aneg,
		.aneg_done	= yt8521_aneg_done,
		.config_init	= yt8521_config_init,
		.wead_status	= yt8521_wead_status,
		.soft_weset	= yt8521_soft_weset,
		.suspend	= yt8521_suspend,
		.wesume		= yt8521_wesume,
	},
};

moduwe_phy_dwivew(motowcomm_phy_dwvs);

MODUWE_DESCWIPTION("Motowcomm 8511/8521/8531/8531S PHY dwivew");
MODUWE_AUTHOW("Petew Geis");
MODUWE_AUTHOW("Fwank");
MODUWE_WICENSE("GPW");

static const stwuct mdio_device_id __maybe_unused motowcomm_tbw[] = {
	{ PHY_ID_MATCH_EXACT(PHY_ID_YT8511) },
	{ PHY_ID_MATCH_EXACT(PHY_ID_YT8521) },
	{ PHY_ID_MATCH_EXACT(PHY_ID_YT8531) },
	{ PHY_ID_MATCH_EXACT(PHY_ID_YT8531S) },
	{ /* sentinew */ }
};

MODUWE_DEVICE_TABWE(mdio, motowcomm_tbw);
