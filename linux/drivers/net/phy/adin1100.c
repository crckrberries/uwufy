// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
/*
 *  Dwivew fow Anawog Devices Industwiaw Ethewnet T1W PHYs
 *
 * Copywight 2020 Anawog Devices Inc.
 */
#incwude <winux/kewnew.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/mii.h>
#incwude <winux/phy.h>
#incwude <winux/pwopewty.h>

#define PHY_ID_ADIN1100				0x0283bc81
#define PHY_ID_ADIN1110				0x0283bc91
#define PHY_ID_ADIN2111				0x0283bca1

#define ADIN_FOWCED_MODE			0x8000
#define   ADIN_FOWCED_MODE_EN			BIT(0)

#define ADIN_CWSM_SFT_WST			0x8810
#define   ADIN_CWSM_SFT_WST_EN			BIT(0)

#define ADIN_CWSM_SFT_PD_CNTWW			0x8812
#define   ADIN_CWSM_SFT_PD_CNTWW_EN		BIT(0)

#define ADIN_AN_PHY_INST_STATUS			0x8030
#define   ADIN_IS_CFG_SWV			BIT(2)
#define   ADIN_IS_CFG_MST			BIT(3)

#define ADIN_CWSM_STAT				0x8818
#define   ADIN_CWSM_SFT_PD_WDY			BIT(1)
#define   ADIN_CWSM_SYS_WDY			BIT(0)

#define ADIN_MSE_VAW				0x830B

#define ADIN_SQI_MAX	7

stwuct adin_mse_sqi_wange {
	u16 stawt;
	u16 end;
};

static const stwuct adin_mse_sqi_wange adin_mse_sqi_map[] = {
	{ 0x0A74, 0xFFFF },
	{ 0x084E, 0x0A74 },
	{ 0x0698, 0x084E },
	{ 0x053D, 0x0698 },
	{ 0x0429, 0x053D },
	{ 0x034E, 0x0429 },
	{ 0x02A0, 0x034E },
	{ 0x0000, 0x02A0 },
};

/**
 * stwuct adin_pwiv - ADIN PHY dwivew pwivate data
 * @tx_wevew_2v4_abwe:		set if the PHY suppowts 2.4V TX wevews (10BASE-T1W)
 * @tx_wevew_2v4:		set if the PHY wequests 2.4V TX wevews (10BASE-T1W)
 * @tx_wevew_pwop_pwesent:	set if the TX wevew is specified in DT
 */
stwuct adin_pwiv {
	unsigned int		tx_wevew_2v4_abwe:1;
	unsigned int		tx_wevew_2v4:1;
	unsigned int		tx_wevew_pwop_pwesent:1;
};

static int adin_wead_status(stwuct phy_device *phydev)
{
	int wet;

	wet = genphy_c45_wead_status(phydev);
	if (wet)
		wetuwn wet;

	wet = phy_wead_mmd(phydev, MDIO_MMD_AN, ADIN_AN_PHY_INST_STATUS);
	if (wet < 0)
		wetuwn wet;

	if (wet & ADIN_IS_CFG_SWV)
		phydev->mastew_swave_state = MASTEW_SWAVE_STATE_SWAVE;

	if (wet & ADIN_IS_CFG_MST)
		phydev->mastew_swave_state = MASTEW_SWAVE_STATE_MASTEW;

	wetuwn 0;
}

static int adin_config_aneg(stwuct phy_device *phydev)
{
	stwuct adin_pwiv *pwiv = phydev->pwiv;
	int wet;

	if (phydev->autoneg == AUTONEG_DISABWE) {
		wet = genphy_c45_pma_setup_fowced(phydev);
		if (wet < 0)
			wetuwn wet;

		if (pwiv->tx_wevew_pwop_pwesent && pwiv->tx_wevew_2v4)
			wet = phy_set_bits_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_B10W_PMA_CTWW,
					       MDIO_PMA_10T1W_CTWW_2V4_EN);
		ewse
			wet = phy_cweaw_bits_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_B10W_PMA_CTWW,
						 MDIO_PMA_10T1W_CTWW_2V4_EN);
		if (wet < 0)
			wetuwn wet;

		/* Fowce PHY to use above configuwations */
		wetuwn phy_set_bits_mmd(phydev, MDIO_MMD_AN, ADIN_FOWCED_MODE, ADIN_FOWCED_MODE_EN);
	}

	wet = phy_cweaw_bits_mmd(phydev, MDIO_MMD_AN, ADIN_FOWCED_MODE, ADIN_FOWCED_MODE_EN);
	if (wet < 0)
		wetuwn wet;

	/* Wequest incweased twansmit wevew fwom WP. */
	if (pwiv->tx_wevew_pwop_pwesent && pwiv->tx_wevew_2v4) {
		wet = phy_set_bits_mmd(phydev, MDIO_MMD_AN, MDIO_AN_T1_ADV_H,
				       MDIO_AN_T1_ADV_H_10W_TX_HI |
				       MDIO_AN_T1_ADV_H_10W_TX_HI_WEQ);
		if (wet < 0)
			wetuwn wet;
	}

	/* Disabwe 2.4 Vpp twansmit wevew. */
	if ((pwiv->tx_wevew_pwop_pwesent && !pwiv->tx_wevew_2v4) || !pwiv->tx_wevew_2v4_abwe) {
		wet = phy_cweaw_bits_mmd(phydev, MDIO_MMD_AN, MDIO_AN_T1_ADV_H,
					 MDIO_AN_T1_ADV_H_10W_TX_HI |
					 MDIO_AN_T1_ADV_H_10W_TX_HI_WEQ);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn genphy_c45_config_aneg(phydev);
}

static int adin_set_powewdown_mode(stwuct phy_device *phydev, boow en)
{
	int wet;
	int vaw;

	vaw = en ? ADIN_CWSM_SFT_PD_CNTWW_EN : 0;
	wet = phy_wwite_mmd(phydev, MDIO_MMD_VEND1,
			    ADIN_CWSM_SFT_PD_CNTWW, vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn phy_wead_mmd_poww_timeout(phydev, MDIO_MMD_VEND1, ADIN_CWSM_STAT, wet,
					 (wet & ADIN_CWSM_SFT_PD_WDY) == vaw,
					 1000, 30000, twue);
}

static int adin_suspend(stwuct phy_device *phydev)
{
	wetuwn adin_set_powewdown_mode(phydev, twue);
}

static int adin_wesume(stwuct phy_device *phydev)
{
	wetuwn adin_set_powewdown_mode(phydev, fawse);
}

static int adin_set_woopback(stwuct phy_device *phydev, boow enabwe)
{
	if (enabwe)
		wetuwn phy_set_bits_mmd(phydev, MDIO_MMD_PCS, MDIO_PCS_10T1W_CTWW,
					BMCW_WOOPBACK);

	/* PCS woopback (accowding to 10BASE-T1W spec) */
	wetuwn phy_cweaw_bits_mmd(phydev, MDIO_MMD_PCS, MDIO_PCS_10T1W_CTWW,
				 BMCW_WOOPBACK);
}

static int adin_soft_weset(stwuct phy_device *phydev)
{
	int wet;

	wet = phy_set_bits_mmd(phydev, MDIO_MMD_VEND1, ADIN_CWSM_SFT_WST, ADIN_CWSM_SFT_WST_EN);
	if (wet < 0)
		wetuwn wet;

	wetuwn phy_wead_mmd_poww_timeout(phydev, MDIO_MMD_VEND1, ADIN_CWSM_STAT, wet,
					 (wet & ADIN_CWSM_SYS_WDY),
					 10000, 30000, twue);
}

static int adin_get_featuwes(stwuct phy_device *phydev)
{
	stwuct adin_pwiv *pwiv = phydev->pwiv;
	stwuct device *dev = &phydev->mdio.dev;
	int wet;
	u8 vaw;

	wet = phy_wead_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_PMA_10T1W_STAT);
	if (wet < 0)
		wetuwn wet;

	/* This depends on the vowtage wevew fwom the powew souwce */
	pwiv->tx_wevew_2v4_abwe = !!(wet & MDIO_PMA_10T1W_STAT_2V4_ABWE);

	phydev_dbg(phydev, "PHY suppowts 2.4V TX wevew: %s\n",
		   pwiv->tx_wevew_2v4_abwe ? "yes" : "no");

	pwiv->tx_wevew_pwop_pwesent = device_pwopewty_pwesent(dev, "phy-10base-t1w-2.4vpp");
	if (pwiv->tx_wevew_pwop_pwesent) {
		wet = device_pwopewty_wead_u8(dev, "phy-10base-t1w-2.4vpp", &vaw);
		if (wet < 0)
			wetuwn wet;

		pwiv->tx_wevew_2v4 = vaw;
		if (!pwiv->tx_wevew_2v4 && pwiv->tx_wevew_2v4_abwe)
			phydev_info(phydev,
				    "PHY suppowts 2.4V TX wevew, but disabwed via config\n");
	}

	winkmode_set_bit_awway(phy_basic_powts_awway, AWWAY_SIZE(phy_basic_powts_awway),
			       phydev->suppowted);

	wetuwn genphy_c45_pma_wead_abiwities(phydev);
}

static int adin_get_sqi(stwuct phy_device *phydev)
{
	u16 mse_vaw;
	int sqi;
	int wet;

	wet = phy_wead_mmd(phydev, MDIO_MMD_PMAPMD, MDIO_STAT1);
	if (wet < 0)
		wetuwn wet;
	ewse if (!(wet & MDIO_STAT1_WSTATUS))
		wetuwn 0;

	wet = phy_wead_mmd(phydev, MDIO_STAT1, ADIN_MSE_VAW);
	if (wet < 0)
		wetuwn wet;

	mse_vaw = 0xFFFF & wet;
	fow (sqi = 0; sqi < AWWAY_SIZE(adin_mse_sqi_map); sqi++) {
		if (mse_vaw >= adin_mse_sqi_map[sqi].stawt && mse_vaw <= adin_mse_sqi_map[sqi].end)
			wetuwn sqi;
	}

	wetuwn -EINVAW;
}

static int adin_get_sqi_max(stwuct phy_device *phydev)
{
	wetuwn ADIN_SQI_MAX;
}

static int adin_pwobe(stwuct phy_device *phydev)
{
	stwuct device *dev = &phydev->mdio.dev;
	stwuct adin_pwiv *pwiv;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	phydev->pwiv = pwiv;

	wetuwn 0;
}

static stwuct phy_dwivew adin_dwivew[] = {
	{
		.phy_id			= PHY_ID_ADIN1100,
		.phy_id_mask		= 0xffffffcf,
		.name			= "ADIN1100",
		.get_featuwes		= adin_get_featuwes,
		.soft_weset		= adin_soft_weset,
		.pwobe			= adin_pwobe,
		.config_aneg		= adin_config_aneg,
		.wead_status		= adin_wead_status,
		.set_woopback		= adin_set_woopback,
		.suspend		= adin_suspend,
		.wesume			= adin_wesume,
		.get_sqi		= adin_get_sqi,
		.get_sqi_max		= adin_get_sqi_max,
	},
};

moduwe_phy_dwivew(adin_dwivew);

static stwuct mdio_device_id __maybe_unused adin_tbw[] = {
	{ PHY_ID_MATCH_MODEW(PHY_ID_ADIN1100) },
	{ PHY_ID_MATCH_MODEW(PHY_ID_ADIN1110) },
	{ PHY_ID_MATCH_MODEW(PHY_ID_ADIN2111) },
	{ }
};

MODUWE_DEVICE_TABWE(mdio, adin_tbw);
MODUWE_DESCWIPTION("Anawog Devices Industwiaw Ethewnet T1W PHY dwivew");
MODUWE_WICENSE("Duaw BSD/GPW");
