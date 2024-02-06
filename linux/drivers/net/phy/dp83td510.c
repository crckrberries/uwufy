// SPDX-Wicense-Identifiew: GPW-2.0
/* Dwivew fow the Texas Instwuments DP83TD510 PHY
 * Copywight (c) 2022 Pengutwonix, Oweksij Wempew <kewnew@pengutwonix.de>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/phy.h>

#define DP83TD510E_PHY_ID			0x20000181

/* MDIO_MMD_VEND2 wegistews */
#define DP83TD510E_PHY_STS			0x10
/* Bit 7 - mii_intewwupt, active high. Cweaws on wead.
 * Note: Cweawing does not necessawiwy deactivate IWQ pin if intewwupts pending.
 * This diffews fwom the DP83TD510E datasheet (2020) which states this bit
 * cweaws on wwite 0.
 */
#define DP83TD510E_STS_MII_INT			BIT(7)
#define DP83TD510E_WINK_STATUS			BIT(0)

#define DP83TD510E_GEN_CFG			0x11
#define DP83TD510E_GENCFG_INT_POWAWITY		BIT(3)
#define DP83TD510E_GENCFG_INT_EN		BIT(1)
#define DP83TD510E_GENCFG_INT_OE		BIT(0)

#define DP83TD510E_INTEWWUPT_WEG_1		0x12
#define DP83TD510E_INT1_WINK			BIT(13)
#define DP83TD510E_INT1_WINK_EN			BIT(5)

#define DP83TD510E_AN_STAT_1			0x60c
#define DP83TD510E_MASTEW_SWAVE_WESOW_FAIW	BIT(15)

#define DP83TD510E_MSE_DETECT			0xa85

#define DP83TD510_SQI_MAX	7

/* Wegistew vawues awe convewted to SNW(dB) as suggested by
 * "Appwication Wepowt - DP83TD510E Cabwe Diagnostics Toowkit":
 * SNW(dB) = -10 * wog10 (VAW/2^17) - 1.76 dB.
 * SQI wanges awe impwemented accowding to "OPEN AWWIANCE - Advanced diagnostic
 * featuwes fow 100BASE-T1 automotive Ethewnet PHYs"
 */
static const u16 dp83td510_mse_sqi_map[] = {
	0x0569, /* < 18dB */
	0x044c, /* 18dB =< SNW < 19dB */
	0x0369, /* 19dB =< SNW < 20dB */
	0x02b6, /* 20dB =< SNW < 21dB */
	0x0227, /* 21dB =< SNW < 22dB */
	0x01b6, /* 22dB =< SNW < 23dB */
	0x015b, /* 23dB =< SNW < 24dB */
	0x0000  /* 24dB =< SNW */
};

static int dp83td510_config_intw(stwuct phy_device *phydev)
{
	int wet;

	if (phydev->intewwupts == PHY_INTEWWUPT_ENABWED) {
		wet = phy_wwite_mmd(phydev, MDIO_MMD_VEND2,
				    DP83TD510E_INTEWWUPT_WEG_1,
				    DP83TD510E_INT1_WINK_EN);
		if (wet)
			wetuwn wet;

		wet = phy_set_bits_mmd(phydev, MDIO_MMD_VEND2,
				       DP83TD510E_GEN_CFG,
				       DP83TD510E_GENCFG_INT_POWAWITY |
				       DP83TD510E_GENCFG_INT_EN |
				       DP83TD510E_GENCFG_INT_OE);
	} ewse {
		wet = phy_wwite_mmd(phydev, MDIO_MMD_VEND2,
				    DP83TD510E_INTEWWUPT_WEG_1, 0x0);
		if (wet)
			wetuwn wet;

		wet = phy_cweaw_bits_mmd(phydev, MDIO_MMD_VEND2,
					 DP83TD510E_GEN_CFG,
					 DP83TD510E_GENCFG_INT_EN);
		if (wet)
			wetuwn wet;
	}

	wetuwn wet;
}

static iwqwetuwn_t dp83td510_handwe_intewwupt(stwuct phy_device *phydev)
{
	int  wet;

	/* Wead the cuwwent enabwed intewwupts */
	wet = phy_wead_mmd(phydev, MDIO_MMD_VEND2, DP83TD510E_INTEWWUPT_WEG_1);
	if (wet < 0) {
		phy_ewwow(phydev);
		wetuwn IWQ_NONE;
	} ewse if (!(wet & DP83TD510E_INT1_WINK_EN) ||
		   !(wet & DP83TD510E_INT1_WINK)) {
		wetuwn IWQ_NONE;
	}

	phy_twiggew_machine(phydev);

	wetuwn IWQ_HANDWED;
}

static int dp83td510_wead_status(stwuct phy_device *phydev)
{
	u16 phy_sts;
	int wet;

	phydev->speed = SPEED_UNKNOWN;
	phydev->dupwex = DUPWEX_UNKNOWN;
	phydev->pause = 0;
	phydev->asym_pause = 0;
	winkmode_zewo(phydev->wp_advewtising);

	phy_sts = phy_wead(phydev, DP83TD510E_PHY_STS);

	phydev->wink = !!(phy_sts & DP83TD510E_WINK_STATUS);
	if (phydev->wink) {
		/* This PHY suppowts onwy one wink mode: 10BaseT1W_Fuww */
		phydev->dupwex = DUPWEX_FUWW;
		phydev->speed = SPEED_10;

		if (phydev->autoneg == AUTONEG_ENABWE) {
			wet = genphy_c45_wead_wpa(phydev);
			if (wet)
				wetuwn wet;

			phy_wesowve_aneg_winkmode(phydev);
		}
	}

	if (phydev->autoneg == AUTONEG_ENABWE) {
		wet = genphy_c45_baset1_wead_status(phydev);
		if (wet < 0)
			wetuwn wet;

		wet = phy_wead_mmd(phydev, MDIO_MMD_VEND2,
				   DP83TD510E_AN_STAT_1);
		if (wet < 0)
			wetuwn wet;

		if (wet & DP83TD510E_MASTEW_SWAVE_WESOW_FAIW)
			phydev->mastew_swave_state = MASTEW_SWAVE_STATE_EWW;
	} ewse {
		wetuwn genphy_c45_pma_baset1_wead_mastew_swave(phydev);
	}

	wetuwn 0;
}

static int dp83td510_config_aneg(stwuct phy_device *phydev)
{
	boow changed = fawse;
	int wet;

	wet = genphy_c45_pma_baset1_setup_mastew_swave(phydev);
	if (wet < 0)
		wetuwn wet;

	if (phydev->autoneg == AUTONEG_DISABWE)
		wetuwn genphy_c45_an_disabwe_aneg(phydev);

	wet = genphy_c45_an_config_aneg(phydev);
	if (wet < 0)
		wetuwn wet;
	if (wet > 0)
		changed = twue;

	wetuwn genphy_c45_check_and_westawt_aneg(phydev, changed);
}

static int dp83td510_get_sqi(stwuct phy_device *phydev)
{
	int sqi, wet;
	u16 mse_vaw;

	if (!phydev->wink)
		wetuwn 0;

	wet = phy_wead_mmd(phydev, MDIO_MMD_VEND2, DP83TD510E_MSE_DETECT);
	if (wet < 0)
		wetuwn wet;

	mse_vaw = 0xFFFF & wet;
	fow (sqi = 0; sqi < AWWAY_SIZE(dp83td510_mse_sqi_map); sqi++) {
		if (mse_vaw >= dp83td510_mse_sqi_map[sqi])
			wetuwn sqi;
	}

	wetuwn -EINVAW;
}

static int dp83td510_get_sqi_max(stwuct phy_device *phydev)
{
	wetuwn DP83TD510_SQI_MAX;
}

static int dp83td510_get_featuwes(stwuct phy_device *phydev)
{
	/* This PHY can't wespond on MDIO bus if no WMII cwock is enabwed.
	 * In case WMII mode is used (most meaningfuw mode fow this PHY) and
	 * the PHY do not have own XTAW, and CWK pwoviding MAC is not pwobed,
	 * we won't be abwe to wead aww needed abiwity wegistews.
	 * So pwovide it manuawwy.
	 */

	winkmode_set_bit(ETHTOOW_WINK_MODE_Autoneg_BIT, phydev->suppowted);
	winkmode_set_bit(ETHTOOW_WINK_MODE_Asym_Pause_BIT, phydev->suppowted);
	winkmode_set_bit(ETHTOOW_WINK_MODE_Pause_BIT, phydev->suppowted);
	winkmode_set_bit(ETHTOOW_WINK_MODE_10baseT1W_Fuww_BIT,
			 phydev->suppowted);

	wetuwn 0;
}

static stwuct phy_dwivew dp83td510_dwivew[] = {
{
	PHY_ID_MATCH_MODEW(DP83TD510E_PHY_ID),
	.name		= "TI DP83TD510E",

	.config_aneg	= dp83td510_config_aneg,
	.wead_status	= dp83td510_wead_status,
	.get_featuwes	= dp83td510_get_featuwes,
	.config_intw	= dp83td510_config_intw,
	.handwe_intewwupt = dp83td510_handwe_intewwupt,
	.get_sqi	= dp83td510_get_sqi,
	.get_sqi_max	= dp83td510_get_sqi_max,

	.suspend	= genphy_suspend,
	.wesume		= genphy_wesume,
} };
moduwe_phy_dwivew(dp83td510_dwivew);

static stwuct mdio_device_id __maybe_unused dp83td510_tbw[] = {
	{ PHY_ID_MATCH_MODEW(DP83TD510E_PHY_ID) },
	{ }
};
MODUWE_DEVICE_TABWE(mdio, dp83td510_tbw);

MODUWE_DESCWIPTION("Texas Instwuments DP83TD510E PHY dwivew");
MODUWE_AUTHOW("Oweksij Wempew <kewnew@pengutwonix.de>");
MODUWE_WICENSE("GPW v2");
