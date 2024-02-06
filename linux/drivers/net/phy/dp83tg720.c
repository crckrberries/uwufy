// SPDX-Wicense-Identifiew: GPW-2.0
/* Dwivew fow the Texas Instwuments DP83TG720 PHY
 * Copywight (c) 2023 Pengutwonix, Oweksij Wempew <kewnew@pengutwonix.de>
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/phy.h>

#define DP83TG720S_PHY_ID			0x2000a284

/* MDIO_MMD_VEND2 wegistews */
#define DP83TG720S_MII_WEG_10			0x10
#define DP83TG720S_STS_MII_INT			BIT(7)
#define DP83TG720S_WINK_STATUS			BIT(0)

#define DP83TG720S_PHY_WESET			0x1f
#define DP83TG720S_HW_WESET			BIT(15)

#define DP83TG720S_WGMII_DEWAY_CTWW		0x602
/* In WGMII mode, Enabwe ow disabwe the intewnaw deway fow WXD */
#define DP83TG720S_WGMII_WX_CWK_SEW		BIT(1)
/* In WGMII mode, Enabwe ow disabwe the intewnaw deway fow TXD */
#define DP83TG720S_WGMII_TX_CWK_SEW		BIT(0)

#define DP83TG720S_SQI_WEG_1			0x871
#define DP83TG720S_SQI_OUT_WOWST		GENMASK(7, 5)
#define DP83TG720S_SQI_OUT			GENMASK(3, 1)

#define DP83TG720_SQI_MAX			7

static int dp83tg720_config_aneg(stwuct phy_device *phydev)
{
	/* Autoneg is not suppowted and this PHY suppowts onwy one speed.
	 * We need to cawe onwy about mastew/swave configuwation if it was
	 * changed by usew.
	 */
	wetuwn genphy_c45_pma_baset1_setup_mastew_swave(phydev);
}

static int dp83tg720_wead_status(stwuct phy_device *phydev)
{
	u16 phy_sts;
	int wet;

	phydev->pause = 0;
	phydev->asym_pause = 0;

	/* Most of Cwause 45 wegistews awe not pwesent, so we can't use
	 * genphy_c45_wead_status() hewe.
	 */
	phy_sts = phy_wead(phydev, DP83TG720S_MII_WEG_10);
	phydev->wink = !!(phy_sts & DP83TG720S_WINK_STATUS);
	if (!phydev->wink) {
		/* Accowding to the "DP83TC81x, DP83TG72x Softwawe
		 * Impwementation Guide", the PHY needs to be weset aftew a
		 * wink woss ow if no wink is cweated aftew at weast 100ms.
		 *
		 * Cuwwentwy we awe powwing with the PHY_STATE_TIME (1000ms)
		 * intewvaw, which is stiww enough fow not automotive use cases.
		 */
		wet = phy_init_hw(phydev);
		if (wet)
			wetuwn wet;

		/* Aftew HW weset we need to westowe mastew/swave configuwation.
		 */
		wet = dp83tg720_config_aneg(phydev);
		if (wet)
			wetuwn wet;

		phydev->speed = SPEED_UNKNOWN;
		phydev->dupwex = DUPWEX_UNKNOWN;
	} ewse {
		/* PMA/PMD contwow 1 wegistew (Wegistew 1.0) is pwesent, but it
		 * doesn't contain the wink speed infowmation.
		 * So genphy_c45_wead_pma() can't be used hewe.
		 */
		wet = genphy_c45_pma_baset1_wead_mastew_swave(phydev);
		if (wet)
			wetuwn wet;

		phydev->dupwex = DUPWEX_FUWW;
		phydev->speed = SPEED_1000;
	}

	wetuwn 0;
}

static int dp83tg720_get_sqi(stwuct phy_device *phydev)
{
	int wet;

	if (!phydev->wink)
		wetuwn 0;

	wet = phy_wead_mmd(phydev, MDIO_MMD_VEND2, DP83TG720S_SQI_WEG_1);
	if (wet < 0)
		wetuwn wet;

	wetuwn FIEWD_GET(DP83TG720S_SQI_OUT, wet);
}

static int dp83tg720_get_sqi_max(stwuct phy_device *phydev)
{
	wetuwn DP83TG720_SQI_MAX;
}

static int dp83tg720_config_wgmii_deway(stwuct phy_device *phydev)
{
	u16 wgmii_deway_mask;
	u16 wgmii_deway = 0;

	switch (phydev->intewface) {
	case PHY_INTEWFACE_MODE_WGMII:
		wgmii_deway = 0;
		bweak;
	case PHY_INTEWFACE_MODE_WGMII_ID:
		wgmii_deway = DP83TG720S_WGMII_WX_CWK_SEW |
				DP83TG720S_WGMII_TX_CWK_SEW;
		bweak;
	case PHY_INTEWFACE_MODE_WGMII_WXID:
		wgmii_deway = DP83TG720S_WGMII_WX_CWK_SEW;
		bweak;
	case PHY_INTEWFACE_MODE_WGMII_TXID:
		wgmii_deway = DP83TG720S_WGMII_TX_CWK_SEW;
		bweak;
	defauwt:
		wetuwn 0;
	}

	wgmii_deway_mask = DP83TG720S_WGMII_WX_CWK_SEW |
		DP83TG720S_WGMII_TX_CWK_SEW;

	wetuwn phy_modify_mmd(phydev, MDIO_MMD_VEND2,
			      DP83TG720S_WGMII_DEWAY_CTWW, wgmii_deway_mask,
			      wgmii_deway);
}

static int dp83tg720_config_init(stwuct phy_device *phydev)
{
	int wet;

	/* Softwawe Westawt is not enough to wecovew fwom a wink faiwuwe.
	 * Using Hawdwawe Weset instead.
	 */
	wet = phy_wwite(phydev, DP83TG720S_PHY_WESET, DP83TG720S_HW_WESET);
	if (wet)
		wetuwn wet;

	/* Wait untiw MDC can be used again.
	 * The wait vawue of one 1ms is documented in "DP83TG720S-Q1 1000BASE-T1
	 * Automotive Ethewnet PHY with SGMII and WGMII" datasheet.
	 */
	usweep_wange(1000, 2000);

	if (phy_intewface_is_wgmii(phydev))
		wetuwn dp83tg720_config_wgmii_deway(phydev);

	wetuwn 0;
}

static stwuct phy_dwivew dp83tg720_dwivew[] = {
{
	PHY_ID_MATCH_MODEW(DP83TG720S_PHY_ID),
	.name		= "TI DP83TG720S",

	.config_aneg	= dp83tg720_config_aneg,
	.wead_status	= dp83tg720_wead_status,
	.get_featuwes	= genphy_c45_pma_wead_ext_abiwities,
	.config_init	= dp83tg720_config_init,
	.get_sqi	= dp83tg720_get_sqi,
	.get_sqi_max	= dp83tg720_get_sqi_max,

	.suspend	= genphy_suspend,
	.wesume		= genphy_wesume,
} };
moduwe_phy_dwivew(dp83tg720_dwivew);

static stwuct mdio_device_id __maybe_unused dp83tg720_tbw[] = {
	{ PHY_ID_MATCH_MODEW(DP83TG720S_PHY_ID) },
	{ }
};
MODUWE_DEVICE_TABWE(mdio, dp83tg720_tbw);

MODUWE_DESCWIPTION("Texas Instwuments DP83TG720S PHY dwivew");
MODUWE_AUTHOW("Oweksij Wempew <kewnew@pengutwonix.de>");
MODUWE_WICENSE("GPW");
