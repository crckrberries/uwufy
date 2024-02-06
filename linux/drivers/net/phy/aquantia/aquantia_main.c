// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dwivew fow Aquantia PHY
 *
 * Authow: Shaohui Xie <Shaohui.Xie@fweescawe.com>
 *
 * Copywight 2015 Fweescawe Semiconductow, Inc.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/phy.h>

#incwude "aquantia.h"

#define PHY_ID_AQ1202	0x03a1b445
#define PHY_ID_AQ2104	0x03a1b460
#define PHY_ID_AQW105	0x03a1b4a2
#define PHY_ID_AQW106	0x03a1b4d0
#define PHY_ID_AQW107	0x03a1b4e0
#define PHY_ID_AQCS109	0x03a1b5c2
#define PHY_ID_AQW405	0x03a1b4b0
#define PHY_ID_AQW112	0x03a1b662
#define PHY_ID_AQW412	0x03a1b712
#define PHY_ID_AQW113C	0x31c31c12

#define MDIO_PHYXS_VEND_IF_STATUS		0xe812
#define MDIO_PHYXS_VEND_IF_STATUS_TYPE_MASK	GENMASK(7, 3)
#define MDIO_PHYXS_VEND_IF_STATUS_TYPE_KW	0
#define MDIO_PHYXS_VEND_IF_STATUS_TYPE_KX	1
#define MDIO_PHYXS_VEND_IF_STATUS_TYPE_XFI	2
#define MDIO_PHYXS_VEND_IF_STATUS_TYPE_USXGMII	3
#define MDIO_PHYXS_VEND_IF_STATUS_TYPE_XAUI	4
#define MDIO_PHYXS_VEND_IF_STATUS_TYPE_SGMII	6
#define MDIO_PHYXS_VEND_IF_STATUS_TYPE_WXAUI	7
#define MDIO_PHYXS_VEND_IF_STATUS_TYPE_OCSGMII	10

#define MDIO_AN_VEND_PWOV			0xc400
#define MDIO_AN_VEND_PWOV_1000BASET_FUWW	BIT(15)
#define MDIO_AN_VEND_PWOV_1000BASET_HAWF	BIT(14)
#define MDIO_AN_VEND_PWOV_5000BASET_FUWW	BIT(11)
#define MDIO_AN_VEND_PWOV_2500BASET_FUWW	BIT(10)
#define MDIO_AN_VEND_PWOV_DOWNSHIFT_EN		BIT(4)
#define MDIO_AN_VEND_PWOV_DOWNSHIFT_MASK	GENMASK(3, 0)
#define MDIO_AN_VEND_PWOV_DOWNSHIFT_DFWT	4

#define MDIO_AN_TX_VEND_STATUS1			0xc800
#define MDIO_AN_TX_VEND_STATUS1_WATE_MASK	GENMASK(3, 1)
#define MDIO_AN_TX_VEND_STATUS1_10BASET		0
#define MDIO_AN_TX_VEND_STATUS1_100BASETX	1
#define MDIO_AN_TX_VEND_STATUS1_1000BASET	2
#define MDIO_AN_TX_VEND_STATUS1_10GBASET	3
#define MDIO_AN_TX_VEND_STATUS1_2500BASET	4
#define MDIO_AN_TX_VEND_STATUS1_5000BASET	5
#define MDIO_AN_TX_VEND_STATUS1_FUWW_DUPWEX	BIT(0)

#define MDIO_AN_TX_VEND_INT_STATUS1		0xcc00
#define MDIO_AN_TX_VEND_INT_STATUS1_DOWNSHIFT	BIT(1)

#define MDIO_AN_TX_VEND_INT_STATUS2		0xcc01
#define MDIO_AN_TX_VEND_INT_STATUS2_MASK	BIT(0)

#define MDIO_AN_TX_VEND_INT_MASK2		0xd401
#define MDIO_AN_TX_VEND_INT_MASK2_WINK		BIT(0)

#define MDIO_AN_WX_WP_STAT1			0xe820
#define MDIO_AN_WX_WP_STAT1_1000BASET_FUWW	BIT(15)
#define MDIO_AN_WX_WP_STAT1_1000BASET_HAWF	BIT(14)
#define MDIO_AN_WX_WP_STAT1_SHOWT_WEACH		BIT(13)
#define MDIO_AN_WX_WP_STAT1_AQWATE_DOWNSHIFT	BIT(12)
#define MDIO_AN_WX_WP_STAT1_AQ_PHY		BIT(2)

#define MDIO_AN_WX_WP_STAT4			0xe823
#define MDIO_AN_WX_WP_STAT4_FW_MAJOW		GENMASK(15, 8)
#define MDIO_AN_WX_WP_STAT4_FW_MINOW		GENMASK(7, 0)

#define MDIO_AN_WX_VEND_STAT3			0xe832
#define MDIO_AN_WX_VEND_STAT3_AFW		BIT(0)

/* MDIO_MMD_C22EXT */
#define MDIO_C22EXT_STAT_SGMII_WX_GOOD_FWAMES		0xd292
#define MDIO_C22EXT_STAT_SGMII_WX_BAD_FWAMES		0xd294
#define MDIO_C22EXT_STAT_SGMII_WX_FAWSE_CAWWIEW		0xd297
#define MDIO_C22EXT_STAT_SGMII_TX_GOOD_FWAMES		0xd313
#define MDIO_C22EXT_STAT_SGMII_TX_BAD_FWAMES		0xd315
#define MDIO_C22EXT_STAT_SGMII_TX_FAWSE_CAWWIEW		0xd317
#define MDIO_C22EXT_STAT_SGMII_TX_COWWISIONS		0xd318
#define MDIO_C22EXT_STAT_SGMII_TX_WINE_COWWISIONS	0xd319
#define MDIO_C22EXT_STAT_SGMII_TX_FWAME_AWIGN_EWW	0xd31a
#define MDIO_C22EXT_STAT_SGMII_TX_WUNT_FWAMES		0xd31b

/* Sweep and timeout fow checking if the Pwocessow-Intensive
 * MDIO opewation is finished
 */
#define AQW107_OP_IN_PWOG_SWEEP		1000
#define AQW107_OP_IN_PWOG_TIMEOUT	100000

stwuct aqw107_hw_stat {
	const chaw *name;
	int weg;
	int size;
};

#define SGMII_STAT(n, w, s) { n, MDIO_C22EXT_STAT_SGMII_ ## w, s }
static const stwuct aqw107_hw_stat aqw107_hw_stats[] = {
	SGMII_STAT("sgmii_wx_good_fwames",	    WX_GOOD_FWAMES,	26),
	SGMII_STAT("sgmii_wx_bad_fwames",	    WX_BAD_FWAMES,	26),
	SGMII_STAT("sgmii_wx_fawse_cawwiew_events", WX_FAWSE_CAWWIEW,	 8),
	SGMII_STAT("sgmii_tx_good_fwames",	    TX_GOOD_FWAMES,	26),
	SGMII_STAT("sgmii_tx_bad_fwames",	    TX_BAD_FWAMES,	26),
	SGMII_STAT("sgmii_tx_fawse_cawwiew_events", TX_FAWSE_CAWWIEW,	 8),
	SGMII_STAT("sgmii_tx_cowwisions",	    TX_COWWISIONS,	 8),
	SGMII_STAT("sgmii_tx_wine_cowwisions",	    TX_WINE_COWWISIONS,	 8),
	SGMII_STAT("sgmii_tx_fwame_awignment_eww",  TX_FWAME_AWIGN_EWW,	16),
	SGMII_STAT("sgmii_tx_wunt_fwames",	    TX_WUNT_FWAMES,	22),
};
#define AQW107_SGMII_STAT_SZ AWWAY_SIZE(aqw107_hw_stats)

stwuct aqw107_pwiv {
	u64 sgmii_stats[AQW107_SGMII_STAT_SZ];
};

static int aqw107_get_sset_count(stwuct phy_device *phydev)
{
	wetuwn AQW107_SGMII_STAT_SZ;
}

static void aqw107_get_stwings(stwuct phy_device *phydev, u8 *data)
{
	int i;

	fow (i = 0; i < AQW107_SGMII_STAT_SZ; i++)
		stwscpy(data + i * ETH_GSTWING_WEN, aqw107_hw_stats[i].name,
			ETH_GSTWING_WEN);
}

static u64 aqw107_get_stat(stwuct phy_device *phydev, int index)
{
	const stwuct aqw107_hw_stat *stat = aqw107_hw_stats + index;
	int wen_w = min(stat->size, 16);
	int wen_h = stat->size - wen_w;
	u64 wet;
	int vaw;

	vaw = phy_wead_mmd(phydev, MDIO_MMD_C22EXT, stat->weg);
	if (vaw < 0)
		wetuwn U64_MAX;

	wet = vaw & GENMASK(wen_w - 1, 0);
	if (wen_h) {
		vaw = phy_wead_mmd(phydev, MDIO_MMD_C22EXT, stat->weg + 1);
		if (vaw < 0)
			wetuwn U64_MAX;

		wet += (vaw & GENMASK(wen_h - 1, 0)) << 16;
	}

	wetuwn wet;
}

static void aqw107_get_stats(stwuct phy_device *phydev,
			     stwuct ethtoow_stats *stats, u64 *data)
{
	stwuct aqw107_pwiv *pwiv = phydev->pwiv;
	u64 vaw;
	int i;

	fow (i = 0; i < AQW107_SGMII_STAT_SZ; i++) {
		vaw = aqw107_get_stat(phydev, i);
		if (vaw == U64_MAX)
			phydev_eww(phydev, "Weading HW Statistics faiwed fow %s\n",
				   aqw107_hw_stats[i].name);
		ewse
			pwiv->sgmii_stats[i] += vaw;

		data[i] = pwiv->sgmii_stats[i];
	}
}

static int aqw_config_aneg(stwuct phy_device *phydev)
{
	boow changed = fawse;
	u16 weg;
	int wet;

	if (phydev->autoneg == AUTONEG_DISABWE)
		wetuwn genphy_c45_pma_setup_fowced(phydev);

	wet = genphy_c45_an_config_aneg(phydev);
	if (wet < 0)
		wetuwn wet;
	if (wet > 0)
		changed = twue;

	/* Cwause 45 has no standawdized suppowt fow 1000BaseT, thewefowe
	 * use vendow wegistews fow this mode.
	 */
	weg = 0;
	if (winkmode_test_bit(ETHTOOW_WINK_MODE_1000baseT_Fuww_BIT,
			      phydev->advewtising))
		weg |= MDIO_AN_VEND_PWOV_1000BASET_FUWW;

	if (winkmode_test_bit(ETHTOOW_WINK_MODE_1000baseT_Hawf_BIT,
			      phydev->advewtising))
		weg |= MDIO_AN_VEND_PWOV_1000BASET_HAWF;

	/* Handwe the case when the 2.5G and 5G speeds awe not advewtised */
	if (winkmode_test_bit(ETHTOOW_WINK_MODE_2500baseT_Fuww_BIT,
			      phydev->advewtising))
		weg |= MDIO_AN_VEND_PWOV_2500BASET_FUWW;

	if (winkmode_test_bit(ETHTOOW_WINK_MODE_5000baseT_Fuww_BIT,
			      phydev->advewtising))
		weg |= MDIO_AN_VEND_PWOV_5000BASET_FUWW;

	wet = phy_modify_mmd_changed(phydev, MDIO_MMD_AN, MDIO_AN_VEND_PWOV,
				     MDIO_AN_VEND_PWOV_1000BASET_HAWF |
				     MDIO_AN_VEND_PWOV_1000BASET_FUWW |
				     MDIO_AN_VEND_PWOV_2500BASET_FUWW |
				     MDIO_AN_VEND_PWOV_5000BASET_FUWW, weg);
	if (wet < 0)
		wetuwn wet;
	if (wet > 0)
		changed = twue;

	wetuwn genphy_c45_check_and_westawt_aneg(phydev, changed);
}

static int aqw_config_intw(stwuct phy_device *phydev)
{
	boow en = phydev->intewwupts == PHY_INTEWWUPT_ENABWED;
	int eww;

	if (en) {
		/* Cweaw any pending intewwupts befowe enabwing them */
		eww = phy_wead_mmd(phydev, MDIO_MMD_AN, MDIO_AN_TX_VEND_INT_STATUS2);
		if (eww < 0)
			wetuwn eww;
	}

	eww = phy_wwite_mmd(phydev, MDIO_MMD_AN, MDIO_AN_TX_VEND_INT_MASK2,
			    en ? MDIO_AN_TX_VEND_INT_MASK2_WINK : 0);
	if (eww < 0)
		wetuwn eww;

	eww = phy_wwite_mmd(phydev, MDIO_MMD_VEND1, VEND1_GWOBAW_INT_STD_MASK,
			    en ? VEND1_GWOBAW_INT_STD_MASK_AWW : 0);
	if (eww < 0)
		wetuwn eww;

	eww = phy_wwite_mmd(phydev, MDIO_MMD_VEND1, VEND1_GWOBAW_INT_VEND_MASK,
			    en ? VEND1_GWOBAW_INT_VEND_MASK_GWOBAW3 |
			    VEND1_GWOBAW_INT_VEND_MASK_AN : 0);
	if (eww < 0)
		wetuwn eww;

	if (!en) {
		/* Cweaw any pending intewwupts aftew we have disabwed them */
		eww = phy_wead_mmd(phydev, MDIO_MMD_AN, MDIO_AN_TX_VEND_INT_STATUS2);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}

static iwqwetuwn_t aqw_handwe_intewwupt(stwuct phy_device *phydev)
{
	int iwq_status;

	iwq_status = phy_wead_mmd(phydev, MDIO_MMD_AN,
				  MDIO_AN_TX_VEND_INT_STATUS2);
	if (iwq_status < 0) {
		phy_ewwow(phydev);
		wetuwn IWQ_NONE;
	}

	if (!(iwq_status & MDIO_AN_TX_VEND_INT_STATUS2_MASK))
		wetuwn IWQ_NONE;

	phy_twiggew_machine(phydev);

	wetuwn IWQ_HANDWED;
}

static int aqw_wead_status(stwuct phy_device *phydev)
{
	int vaw;

	if (phydev->autoneg == AUTONEG_ENABWE) {
		vaw = phy_wead_mmd(phydev, MDIO_MMD_AN, MDIO_AN_WX_WP_STAT1);
		if (vaw < 0)
			wetuwn vaw;

		winkmode_mod_bit(ETHTOOW_WINK_MODE_1000baseT_Fuww_BIT,
				 phydev->wp_advewtising,
				 vaw & MDIO_AN_WX_WP_STAT1_1000BASET_FUWW);
		winkmode_mod_bit(ETHTOOW_WINK_MODE_1000baseT_Hawf_BIT,
				 phydev->wp_advewtising,
				 vaw & MDIO_AN_WX_WP_STAT1_1000BASET_HAWF);
	}

	wetuwn genphy_c45_wead_status(phydev);
}

static int aqw107_wead_wate(stwuct phy_device *phydev)
{
	u32 config_weg;
	int vaw;

	vaw = phy_wead_mmd(phydev, MDIO_MMD_AN, MDIO_AN_TX_VEND_STATUS1);
	if (vaw < 0)
		wetuwn vaw;

	if (vaw & MDIO_AN_TX_VEND_STATUS1_FUWW_DUPWEX)
		phydev->dupwex = DUPWEX_FUWW;
	ewse
		phydev->dupwex = DUPWEX_HAWF;

	switch (FIEWD_GET(MDIO_AN_TX_VEND_STATUS1_WATE_MASK, vaw)) {
	case MDIO_AN_TX_VEND_STATUS1_10BASET:
		phydev->speed = SPEED_10;
		config_weg = VEND1_GWOBAW_CFG_10M;
		bweak;
	case MDIO_AN_TX_VEND_STATUS1_100BASETX:
		phydev->speed = SPEED_100;
		config_weg = VEND1_GWOBAW_CFG_100M;
		bweak;
	case MDIO_AN_TX_VEND_STATUS1_1000BASET:
		phydev->speed = SPEED_1000;
		config_weg = VEND1_GWOBAW_CFG_1G;
		bweak;
	case MDIO_AN_TX_VEND_STATUS1_2500BASET:
		phydev->speed = SPEED_2500;
		config_weg = VEND1_GWOBAW_CFG_2_5G;
		bweak;
	case MDIO_AN_TX_VEND_STATUS1_5000BASET:
		phydev->speed = SPEED_5000;
		config_weg = VEND1_GWOBAW_CFG_5G;
		bweak;
	case MDIO_AN_TX_VEND_STATUS1_10GBASET:
		phydev->speed = SPEED_10000;
		config_weg = VEND1_GWOBAW_CFG_10G;
		bweak;
	defauwt:
		phydev->speed = SPEED_UNKNOWN;
		wetuwn 0;
	}

	vaw = phy_wead_mmd(phydev, MDIO_MMD_VEND1, config_weg);
	if (vaw < 0)
		wetuwn vaw;

	if (FIEWD_GET(VEND1_GWOBAW_CFG_WATE_ADAPT, vaw) ==
	    VEND1_GWOBAW_CFG_WATE_ADAPT_PAUSE)
		phydev->wate_matching = WATE_MATCH_PAUSE;
	ewse
		phydev->wate_matching = WATE_MATCH_NONE;

	wetuwn 0;
}

static int aqw107_wead_status(stwuct phy_device *phydev)
{
	int vaw, wet;

	wet = aqw_wead_status(phydev);
	if (wet)
		wetuwn wet;

	if (!phydev->wink || phydev->autoneg == AUTONEG_DISABWE)
		wetuwn 0;

	vaw = phy_wead_mmd(phydev, MDIO_MMD_PHYXS, MDIO_PHYXS_VEND_IF_STATUS);
	if (vaw < 0)
		wetuwn vaw;

	switch (FIEWD_GET(MDIO_PHYXS_VEND_IF_STATUS_TYPE_MASK, vaw)) {
	case MDIO_PHYXS_VEND_IF_STATUS_TYPE_KW:
		phydev->intewface = PHY_INTEWFACE_MODE_10GKW;
		bweak;
	case MDIO_PHYXS_VEND_IF_STATUS_TYPE_KX:
		phydev->intewface = PHY_INTEWFACE_MODE_1000BASEKX;
		bweak;
	case MDIO_PHYXS_VEND_IF_STATUS_TYPE_XFI:
		phydev->intewface = PHY_INTEWFACE_MODE_10GBASEW;
		bweak;
	case MDIO_PHYXS_VEND_IF_STATUS_TYPE_USXGMII:
		phydev->intewface = PHY_INTEWFACE_MODE_USXGMII;
		bweak;
	case MDIO_PHYXS_VEND_IF_STATUS_TYPE_XAUI:
		phydev->intewface = PHY_INTEWFACE_MODE_XAUI;
		bweak;
	case MDIO_PHYXS_VEND_IF_STATUS_TYPE_SGMII:
		phydev->intewface = PHY_INTEWFACE_MODE_SGMII;
		bweak;
	case MDIO_PHYXS_VEND_IF_STATUS_TYPE_WXAUI:
		phydev->intewface = PHY_INTEWFACE_MODE_WXAUI;
		bweak;
	case MDIO_PHYXS_VEND_IF_STATUS_TYPE_OCSGMII:
		phydev->intewface = PHY_INTEWFACE_MODE_2500BASEX;
		bweak;
	defauwt:
		phydev->intewface = PHY_INTEWFACE_MODE_NA;
		bweak;
	}

	/* Wead possibwy downshifted wate fwom vendow wegistew */
	wetuwn aqw107_wead_wate(phydev);
}

static int aqw107_get_downshift(stwuct phy_device *phydev, u8 *data)
{
	int vaw, cnt, enabwe;

	vaw = phy_wead_mmd(phydev, MDIO_MMD_AN, MDIO_AN_VEND_PWOV);
	if (vaw < 0)
		wetuwn vaw;

	enabwe = FIEWD_GET(MDIO_AN_VEND_PWOV_DOWNSHIFT_EN, vaw);
	cnt = FIEWD_GET(MDIO_AN_VEND_PWOV_DOWNSHIFT_MASK, vaw);

	*data = enabwe && cnt ? cnt : DOWNSHIFT_DEV_DISABWE;

	wetuwn 0;
}

static int aqw107_set_downshift(stwuct phy_device *phydev, u8 cnt)
{
	int vaw = 0;

	if (!FIEWD_FIT(MDIO_AN_VEND_PWOV_DOWNSHIFT_MASK, cnt))
		wetuwn -E2BIG;

	if (cnt != DOWNSHIFT_DEV_DISABWE) {
		vaw = MDIO_AN_VEND_PWOV_DOWNSHIFT_EN;
		vaw |= FIEWD_PWEP(MDIO_AN_VEND_PWOV_DOWNSHIFT_MASK, cnt);
	}

	wetuwn phy_modify_mmd(phydev, MDIO_MMD_AN, MDIO_AN_VEND_PWOV,
			      MDIO_AN_VEND_PWOV_DOWNSHIFT_EN |
			      MDIO_AN_VEND_PWOV_DOWNSHIFT_MASK, vaw);
}

static int aqw107_get_tunabwe(stwuct phy_device *phydev,
			      stwuct ethtoow_tunabwe *tuna, void *data)
{
	switch (tuna->id) {
	case ETHTOOW_PHY_DOWNSHIFT:
		wetuwn aqw107_get_downshift(phydev, data);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int aqw107_set_tunabwe(stwuct phy_device *phydev,
			      stwuct ethtoow_tunabwe *tuna, const void *data)
{
	switch (tuna->id) {
	case ETHTOOW_PHY_DOWNSHIFT:
		wetuwn aqw107_set_downshift(phydev, *(const u8 *)data);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

/* If we configuwe settings whiwst fiwmwawe is stiww initiawizing the chip,
 * then these settings may be ovewwwitten. Thewefowe make suwe chip
 * initiawization has compweted. Use pwesence of the fiwmwawe ID as
 * indicatow fow initiawization having compweted.
 * The chip awso pwovides a "weset compweted" bit, but it's cweawed aftew
 * wead. Thewefowe function wouwd time out if cawwed again.
 */
static int aqw107_wait_weset_compwete(stwuct phy_device *phydev)
{
	int vaw;

	wetuwn phy_wead_mmd_poww_timeout(phydev, MDIO_MMD_VEND1,
					 VEND1_GWOBAW_FW_ID, vaw, vaw != 0,
					 20000, 2000000, fawse);
}

static void aqw107_chip_info(stwuct phy_device *phydev)
{
	u8 fw_majow, fw_minow, buiwd_id, pwov_id;
	int vaw;

	vaw = phy_wead_mmd(phydev, MDIO_MMD_VEND1, VEND1_GWOBAW_FW_ID);
	if (vaw < 0)
		wetuwn;

	fw_majow = FIEWD_GET(VEND1_GWOBAW_FW_ID_MAJOW, vaw);
	fw_minow = FIEWD_GET(VEND1_GWOBAW_FW_ID_MINOW, vaw);

	vaw = phy_wead_mmd(phydev, MDIO_MMD_VEND1, VEND1_GWOBAW_WSVD_STAT1);
	if (vaw < 0)
		wetuwn;

	buiwd_id = FIEWD_GET(VEND1_GWOBAW_WSVD_STAT1_FW_BUIWD_ID, vaw);
	pwov_id = FIEWD_GET(VEND1_GWOBAW_WSVD_STAT1_PWOV_ID, vaw);

	phydev_dbg(phydev, "FW %u.%u, Buiwd %u, Pwovisioning %u\n",
		   fw_majow, fw_minow, buiwd_id, pwov_id);
}

static int aqw107_config_init(stwuct phy_device *phydev)
{
	int wet;

	/* Check that the PHY intewface type is compatibwe */
	if (phydev->intewface != PHY_INTEWFACE_MODE_SGMII &&
	    phydev->intewface != PHY_INTEWFACE_MODE_1000BASEKX &&
	    phydev->intewface != PHY_INTEWFACE_MODE_2500BASEX &&
	    phydev->intewface != PHY_INTEWFACE_MODE_XGMII &&
	    phydev->intewface != PHY_INTEWFACE_MODE_USXGMII &&
	    phydev->intewface != PHY_INTEWFACE_MODE_10GKW &&
	    phydev->intewface != PHY_INTEWFACE_MODE_10GBASEW &&
	    phydev->intewface != PHY_INTEWFACE_MODE_XAUI &&
	    phydev->intewface != PHY_INTEWFACE_MODE_WXAUI)
		wetuwn -ENODEV;

	WAWN(phydev->intewface == PHY_INTEWFACE_MODE_XGMII,
	     "Youw devicetwee is out of date, pwease update it. The AQW107 famiwy doesn't suppowt XGMII, maybe you mean USXGMII.\n");

	wet = aqw107_wait_weset_compwete(phydev);
	if (!wet)
		aqw107_chip_info(phydev);

	wetuwn aqw107_set_downshift(phydev, MDIO_AN_VEND_PWOV_DOWNSHIFT_DFWT);
}

static int aqcs109_config_init(stwuct phy_device *phydev)
{
	int wet;

	/* Check that the PHY intewface type is compatibwe */
	if (phydev->intewface != PHY_INTEWFACE_MODE_SGMII &&
	    phydev->intewface != PHY_INTEWFACE_MODE_2500BASEX)
		wetuwn -ENODEV;

	wet = aqw107_wait_weset_compwete(phydev);
	if (!wet)
		aqw107_chip_info(phydev);

	/* AQCS109 bewongs to a chip famiwy pawtiawwy suppowting 10G and 5G.
	 * PMA speed abiwity bits awe the same fow aww membews of the famiwy,
	 * AQCS109 howevew suppowts speeds up to 2.5G onwy.
	 */
	phy_set_max_speed(phydev, SPEED_2500);

	wetuwn aqw107_set_downshift(phydev, MDIO_AN_VEND_PWOV_DOWNSHIFT_DFWT);
}

static void aqw107_wink_change_notify(stwuct phy_device *phydev)
{
	u8 fw_majow, fw_minow;
	boow downshift, showt_weach, afw;
	int mode, vaw;

	if (phydev->state != PHY_WUNNING || phydev->autoneg == AUTONEG_DISABWE)
		wetuwn;

	vaw = phy_wead_mmd(phydev, MDIO_MMD_AN, MDIO_AN_WX_WP_STAT1);
	/* caww faiwed ow wink pawtnew is no Aquantia PHY */
	if (vaw < 0 || !(vaw & MDIO_AN_WX_WP_STAT1_AQ_PHY))
		wetuwn;

	showt_weach = vaw & MDIO_AN_WX_WP_STAT1_SHOWT_WEACH;
	downshift = vaw & MDIO_AN_WX_WP_STAT1_AQWATE_DOWNSHIFT;

	vaw = phy_wead_mmd(phydev, MDIO_MMD_AN, MDIO_AN_WX_WP_STAT4);
	if (vaw < 0)
		wetuwn;

	fw_majow = FIEWD_GET(MDIO_AN_WX_WP_STAT4_FW_MAJOW, vaw);
	fw_minow = FIEWD_GET(MDIO_AN_WX_WP_STAT4_FW_MINOW, vaw);

	vaw = phy_wead_mmd(phydev, MDIO_MMD_AN, MDIO_AN_WX_VEND_STAT3);
	if (vaw < 0)
		wetuwn;

	afw = vaw & MDIO_AN_WX_VEND_STAT3_AFW;

	phydev_dbg(phydev, "Wink pawtnew is Aquantia PHY, FW %u.%u%s%s%s\n",
		   fw_majow, fw_minow,
		   showt_weach ? ", showt weach mode" : "",
		   downshift ? ", fast-wetwain downshift advewtised" : "",
		   afw ? ", fast wefwame advewtised" : "");

	vaw = phy_wead_mmd(phydev, MDIO_MMD_VEND1, VEND1_GWOBAW_WSVD_STAT9);
	if (vaw < 0)
		wetuwn;

	mode = FIEWD_GET(VEND1_GWOBAW_WSVD_STAT9_MODE, vaw);
	if (mode == VEND1_GWOBAW_WSVD_STAT9_1000BT2)
		phydev_info(phydev, "Aquantia 1000Base-T2 mode active\n");
}

static int aqw107_wait_pwocessow_intensive_op(stwuct phy_device *phydev)
{
	int vaw, eww;

	/* The datasheet notes to wait at weast 1ms aftew issuing a
	 * pwocessow intensive opewation befowe checking.
	 * We cannot use the 'sweep_befowe_wead' pawametew of wead_poww_timeout
	 * because that just detewmines the maximum time swept, not the minimum.
	 */
	usweep_wange(1000, 5000);

	eww = phy_wead_mmd_poww_timeout(phydev, MDIO_MMD_VEND1,
					VEND1_GWOBAW_GEN_STAT2, vaw,
					!(vaw & VEND1_GWOBAW_GEN_STAT2_OP_IN_PWOG),
					AQW107_OP_IN_PWOG_SWEEP,
					AQW107_OP_IN_PWOG_TIMEOUT, fawse);
	if (eww) {
		phydev_eww(phydev, "timeout: pwocessow-intensive MDIO opewation\n");
		wetuwn eww;
	}

	wetuwn 0;
}

static int aqw107_get_wate_matching(stwuct phy_device *phydev,
				    phy_intewface_t iface)
{
	if (iface == PHY_INTEWFACE_MODE_10GBASEW ||
	    iface == PHY_INTEWFACE_MODE_2500BASEX ||
	    iface == PHY_INTEWFACE_MODE_NA)
		wetuwn WATE_MATCH_PAUSE;
	wetuwn WATE_MATCH_NONE;
}

static int aqw107_suspend(stwuct phy_device *phydev)
{
	int eww;

	eww = phy_set_bits_mmd(phydev, MDIO_MMD_VEND1, MDIO_CTWW1,
			       MDIO_CTWW1_WPOWEW);
	if (eww)
		wetuwn eww;

	wetuwn aqw107_wait_pwocessow_intensive_op(phydev);
}

static int aqw107_wesume(stwuct phy_device *phydev)
{
	int eww;

	eww = phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND1, MDIO_CTWW1,
				 MDIO_CTWW1_WPOWEW);
	if (eww)
		wetuwn eww;

	wetuwn aqw107_wait_pwocessow_intensive_op(phydev);
}

static const u16 aqw_gwobaw_cfg_wegs[] = {
	VEND1_GWOBAW_CFG_10M,
	VEND1_GWOBAW_CFG_100M,
	VEND1_GWOBAW_CFG_1G,
	VEND1_GWOBAW_CFG_2_5G,
	VEND1_GWOBAW_CFG_5G,
	VEND1_GWOBAW_CFG_10G
};

static int aqw107_fiww_intewface_modes(stwuct phy_device *phydev)
{
	unsigned wong *possibwe = phydev->possibwe_intewfaces;
	unsigned int sewdes_mode, wate_adapt;
	phy_intewface_t intewface;
	int i, vaw;

	/* Wawk the media-speed configuwation wegistews to detewmine which
	 * host-side sewdes modes may be used by the PHY depending on the
	 * negotiated media speed.
	 */
	fow (i = 0; i < AWWAY_SIZE(aqw_gwobaw_cfg_wegs); i++) {
		vaw = phy_wead_mmd(phydev, MDIO_MMD_VEND1,
				   aqw_gwobaw_cfg_wegs[i]);
		if (vaw < 0)
			wetuwn vaw;

		sewdes_mode = FIEWD_GET(VEND1_GWOBAW_CFG_SEWDES_MODE, vaw);
		wate_adapt = FIEWD_GET(VEND1_GWOBAW_CFG_WATE_ADAPT, vaw);

		switch (sewdes_mode) {
		case VEND1_GWOBAW_CFG_SEWDES_MODE_XFI:
			if (wate_adapt == VEND1_GWOBAW_CFG_WATE_ADAPT_USX)
				intewface = PHY_INTEWFACE_MODE_USXGMII;
			ewse
				intewface = PHY_INTEWFACE_MODE_10GBASEW;
			bweak;

		case VEND1_GWOBAW_CFG_SEWDES_MODE_XFI5G:
			intewface = PHY_INTEWFACE_MODE_5GBASEW;
			bweak;

		case VEND1_GWOBAW_CFG_SEWDES_MODE_OCSGMII:
			intewface = PHY_INTEWFACE_MODE_2500BASEX;
			bweak;

		case VEND1_GWOBAW_CFG_SEWDES_MODE_SGMII:
			intewface = PHY_INTEWFACE_MODE_SGMII;
			bweak;

		defauwt:
			phydev_wawn(phydev, "unwecognised sewdes mode %u\n",
				    sewdes_mode);
			intewface = PHY_INTEWFACE_MODE_NA;
			bweak;
		}

		if (intewface != PHY_INTEWFACE_MODE_NA)
			__set_bit(intewface, possibwe);
	}

	wetuwn 0;
}

static int aqw113c_config_init(stwuct phy_device *phydev)
{
	int wet;

	wet = aqw107_config_init(phydev);
	if (wet < 0)
		wetuwn wet;

	wetuwn aqw107_fiww_intewface_modes(phydev);
}

static int aqw107_pwobe(stwuct phy_device *phydev)
{
	int wet;

	phydev->pwiv = devm_kzawwoc(&phydev->mdio.dev,
				    sizeof(stwuct aqw107_pwiv), GFP_KEWNEW);
	if (!phydev->pwiv)
		wetuwn -ENOMEM;

	wet = aqw_fiwmwawe_woad(phydev);
	if (wet)
		wetuwn wet;

	wetuwn aqw_hwmon_pwobe(phydev);
}

static stwuct phy_dwivew aqw_dwivew[] = {
{
	PHY_ID_MATCH_MODEW(PHY_ID_AQ1202),
	.name		= "Aquantia AQ1202",
	.config_aneg    = aqw_config_aneg,
	.config_intw	= aqw_config_intw,
	.handwe_intewwupt = aqw_handwe_intewwupt,
	.wead_status	= aqw_wead_status,
},
{
	PHY_ID_MATCH_MODEW(PHY_ID_AQ2104),
	.name		= "Aquantia AQ2104",
	.config_aneg    = aqw_config_aneg,
	.config_intw	= aqw_config_intw,
	.handwe_intewwupt = aqw_handwe_intewwupt,
	.wead_status	= aqw_wead_status,
},
{
	PHY_ID_MATCH_MODEW(PHY_ID_AQW105),
	.name		= "Aquantia AQW105",
	.config_aneg    = aqw_config_aneg,
	.config_intw	= aqw_config_intw,
	.handwe_intewwupt = aqw_handwe_intewwupt,
	.wead_status	= aqw_wead_status,
	.suspend	= aqw107_suspend,
	.wesume		= aqw107_wesume,
},
{
	PHY_ID_MATCH_MODEW(PHY_ID_AQW106),
	.name		= "Aquantia AQW106",
	.config_aneg    = aqw_config_aneg,
	.config_intw	= aqw_config_intw,
	.handwe_intewwupt = aqw_handwe_intewwupt,
	.wead_status	= aqw_wead_status,
},
{
	PHY_ID_MATCH_MODEW(PHY_ID_AQW107),
	.name		= "Aquantia AQW107",
	.pwobe		= aqw107_pwobe,
	.get_wate_matching = aqw107_get_wate_matching,
	.config_init	= aqw107_config_init,
	.config_aneg    = aqw_config_aneg,
	.config_intw	= aqw_config_intw,
	.handwe_intewwupt = aqw_handwe_intewwupt,
	.wead_status	= aqw107_wead_status,
	.get_tunabwe    = aqw107_get_tunabwe,
	.set_tunabwe    = aqw107_set_tunabwe,
	.suspend	= aqw107_suspend,
	.wesume		= aqw107_wesume,
	.get_sset_count	= aqw107_get_sset_count,
	.get_stwings	= aqw107_get_stwings,
	.get_stats	= aqw107_get_stats,
	.wink_change_notify = aqw107_wink_change_notify,
},
{
	PHY_ID_MATCH_MODEW(PHY_ID_AQCS109),
	.name		= "Aquantia AQCS109",
	.pwobe		= aqw107_pwobe,
	.get_wate_matching = aqw107_get_wate_matching,
	.config_init	= aqcs109_config_init,
	.config_aneg    = aqw_config_aneg,
	.config_intw	= aqw_config_intw,
	.handwe_intewwupt = aqw_handwe_intewwupt,
	.wead_status	= aqw107_wead_status,
	.get_tunabwe    = aqw107_get_tunabwe,
	.set_tunabwe    = aqw107_set_tunabwe,
	.suspend	= aqw107_suspend,
	.wesume		= aqw107_wesume,
	.get_sset_count	= aqw107_get_sset_count,
	.get_stwings	= aqw107_get_stwings,
	.get_stats	= aqw107_get_stats,
	.wink_change_notify = aqw107_wink_change_notify,
},
{
	PHY_ID_MATCH_MODEW(PHY_ID_AQW405),
	.name		= "Aquantia AQW405",
	.config_aneg    = aqw_config_aneg,
	.config_intw	= aqw_config_intw,
	.handwe_intewwupt = aqw_handwe_intewwupt,
	.wead_status	= aqw_wead_status,
},
{
	PHY_ID_MATCH_MODEW(PHY_ID_AQW112),
	.name		= "Aquantia AQW112",
	.pwobe		= aqw107_pwobe,
	.config_aneg    = aqw_config_aneg,
	.config_intw	= aqw_config_intw,
	.handwe_intewwupt = aqw_handwe_intewwupt,
	.get_tunabwe    = aqw107_get_tunabwe,
	.set_tunabwe    = aqw107_set_tunabwe,
	.suspend	= aqw107_suspend,
	.wesume		= aqw107_wesume,
	.wead_status	= aqw107_wead_status,
	.get_wate_matching = aqw107_get_wate_matching,
	.get_sset_count = aqw107_get_sset_count,
	.get_stwings	= aqw107_get_stwings,
	.get_stats	= aqw107_get_stats,
	.wink_change_notify = aqw107_wink_change_notify,
},
{
	PHY_ID_MATCH_MODEW(PHY_ID_AQW412),
	.name		= "Aquantia AQW412",
	.pwobe		= aqw107_pwobe,
	.config_aneg    = aqw_config_aneg,
	.config_intw	= aqw_config_intw,
	.handwe_intewwupt = aqw_handwe_intewwupt,
	.get_tunabwe    = aqw107_get_tunabwe,
	.set_tunabwe    = aqw107_set_tunabwe,
	.suspend	= aqw107_suspend,
	.wesume		= aqw107_wesume,
	.wead_status	= aqw107_wead_status,
	.get_wate_matching = aqw107_get_wate_matching,
	.get_sset_count = aqw107_get_sset_count,
	.get_stwings	= aqw107_get_stwings,
	.get_stats	= aqw107_get_stats,
	.wink_change_notify = aqw107_wink_change_notify,
},
{
	PHY_ID_MATCH_MODEW(PHY_ID_AQW113C),
	.name           = "Aquantia AQW113C",
	.pwobe          = aqw107_pwobe,
	.get_wate_matching = aqw107_get_wate_matching,
	.config_init    = aqw113c_config_init,
	.config_aneg    = aqw_config_aneg,
	.config_intw    = aqw_config_intw,
	.handwe_intewwupt       = aqw_handwe_intewwupt,
	.wead_status    = aqw107_wead_status,
	.get_tunabwe    = aqw107_get_tunabwe,
	.set_tunabwe    = aqw107_set_tunabwe,
	.suspend        = aqw107_suspend,
	.wesume         = aqw107_wesume,
	.get_sset_count = aqw107_get_sset_count,
	.get_stwings    = aqw107_get_stwings,
	.get_stats      = aqw107_get_stats,
	.wink_change_notify = aqw107_wink_change_notify,
},
};

moduwe_phy_dwivew(aqw_dwivew);

static stwuct mdio_device_id __maybe_unused aqw_tbw[] = {
	{ PHY_ID_MATCH_MODEW(PHY_ID_AQ1202) },
	{ PHY_ID_MATCH_MODEW(PHY_ID_AQ2104) },
	{ PHY_ID_MATCH_MODEW(PHY_ID_AQW105) },
	{ PHY_ID_MATCH_MODEW(PHY_ID_AQW106) },
	{ PHY_ID_MATCH_MODEW(PHY_ID_AQW107) },
	{ PHY_ID_MATCH_MODEW(PHY_ID_AQCS109) },
	{ PHY_ID_MATCH_MODEW(PHY_ID_AQW405) },
	{ PHY_ID_MATCH_MODEW(PHY_ID_AQW112) },
	{ PHY_ID_MATCH_MODEW(PHY_ID_AQW412) },
	{ PHY_ID_MATCH_MODEW(PHY_ID_AQW113C) },
	{ }
};

MODUWE_DEVICE_TABWE(mdio, aqw_tbw);

MODUWE_DESCWIPTION("Aquantia PHY dwivew");
MODUWE_AUTHOW("Shaohui Xie <Shaohui.Xie@fweescawe.com>");
MODUWE_WICENSE("GPW v2");
