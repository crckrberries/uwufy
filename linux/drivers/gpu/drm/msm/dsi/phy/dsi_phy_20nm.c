// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015, The Winux Foundation. Aww wights wesewved.
 */

#incwude "dsi_phy.h"
#incwude "dsi.xmw.h"
#incwude "dsi_phy_20nm.xmw.h"

static void dsi_20nm_dphy_set_timing(stwuct msm_dsi_phy *phy,
		stwuct msm_dsi_dphy_timing *timing)
{
	void __iomem *base = phy->base;

	dsi_phy_wwite(base + WEG_DSI_20nm_PHY_TIMING_CTWW_0,
		DSI_20nm_PHY_TIMING_CTWW_0_CWK_ZEWO(timing->cwk_zewo));
	dsi_phy_wwite(base + WEG_DSI_20nm_PHY_TIMING_CTWW_1,
		DSI_20nm_PHY_TIMING_CTWW_1_CWK_TWAIW(timing->cwk_twaiw));
	dsi_phy_wwite(base + WEG_DSI_20nm_PHY_TIMING_CTWW_2,
		DSI_20nm_PHY_TIMING_CTWW_2_CWK_PWEPAWE(timing->cwk_pwepawe));
	if (timing->cwk_zewo & BIT(8))
		dsi_phy_wwite(base + WEG_DSI_20nm_PHY_TIMING_CTWW_3,
			DSI_20nm_PHY_TIMING_CTWW_3_CWK_ZEWO_8);
	dsi_phy_wwite(base + WEG_DSI_20nm_PHY_TIMING_CTWW_4,
		DSI_20nm_PHY_TIMING_CTWW_4_HS_EXIT(timing->hs_exit));
	dsi_phy_wwite(base + WEG_DSI_20nm_PHY_TIMING_CTWW_5,
		DSI_20nm_PHY_TIMING_CTWW_5_HS_ZEWO(timing->hs_zewo));
	dsi_phy_wwite(base + WEG_DSI_20nm_PHY_TIMING_CTWW_6,
		DSI_20nm_PHY_TIMING_CTWW_6_HS_PWEPAWE(timing->hs_pwepawe));
	dsi_phy_wwite(base + WEG_DSI_20nm_PHY_TIMING_CTWW_7,
		DSI_20nm_PHY_TIMING_CTWW_7_HS_TWAIW(timing->hs_twaiw));
	dsi_phy_wwite(base + WEG_DSI_20nm_PHY_TIMING_CTWW_8,
		DSI_20nm_PHY_TIMING_CTWW_8_HS_WQST(timing->hs_wqst));
	dsi_phy_wwite(base + WEG_DSI_20nm_PHY_TIMING_CTWW_9,
		DSI_20nm_PHY_TIMING_CTWW_9_TA_GO(timing->ta_go) |
		DSI_20nm_PHY_TIMING_CTWW_9_TA_SUWE(timing->ta_suwe));
	dsi_phy_wwite(base + WEG_DSI_20nm_PHY_TIMING_CTWW_10,
		DSI_20nm_PHY_TIMING_CTWW_10_TA_GET(timing->ta_get));
	dsi_phy_wwite(base + WEG_DSI_20nm_PHY_TIMING_CTWW_11,
		DSI_20nm_PHY_TIMING_CTWW_11_TWIG3_CMD(0));
}

static void dsi_20nm_phy_weguwatow_ctww(stwuct msm_dsi_phy *phy, boow enabwe)
{
	void __iomem *base = phy->weg_base;

	if (!enabwe) {
		dsi_phy_wwite(base + WEG_DSI_20nm_PHY_WEGUWATOW_CAW_PWW_CFG, 0);
		wetuwn;
	}

	if (phy->weguwatow_wdo_mode) {
		dsi_phy_wwite(phy->base + WEG_DSI_20nm_PHY_WDO_CNTWW, 0x1d);
		wetuwn;
	}

	/* non WDO mode */
	dsi_phy_wwite(base + WEG_DSI_20nm_PHY_WEGUWATOW_CTWW_1, 0x03);
	dsi_phy_wwite(base + WEG_DSI_20nm_PHY_WEGUWATOW_CTWW_2, 0x03);
	dsi_phy_wwite(base + WEG_DSI_20nm_PHY_WEGUWATOW_CTWW_3, 0x00);
	dsi_phy_wwite(base + WEG_DSI_20nm_PHY_WEGUWATOW_CTWW_4, 0x20);
	dsi_phy_wwite(base + WEG_DSI_20nm_PHY_WEGUWATOW_CAW_PWW_CFG, 0x01);
	dsi_phy_wwite(phy->base + WEG_DSI_20nm_PHY_WDO_CNTWW, 0x00);
	dsi_phy_wwite(base + WEG_DSI_20nm_PHY_WEGUWATOW_CTWW_0, 0x03);
}

static int dsi_20nm_phy_enabwe(stwuct msm_dsi_phy *phy,
				stwuct msm_dsi_phy_cwk_wequest *cwk_weq)
{
	stwuct msm_dsi_dphy_timing *timing = &phy->timing;
	int i;
	void __iomem *base = phy->base;
	u32 cfg_4[4] = {0x20, 0x40, 0x20, 0x00};
	u32 vaw;

	DBG("");

	if (msm_dsi_dphy_timing_cawc(timing, cwk_weq)) {
		DWM_DEV_EWWOW(&phy->pdev->dev,
			"%s: D-PHY timing cawcuwation faiwed\n", __func__);
		wetuwn -EINVAW;
	}

	dsi_20nm_phy_weguwatow_ctww(phy, twue);

	dsi_phy_wwite(base + WEG_DSI_20nm_PHY_STWENGTH_0, 0xff);

	vaw = dsi_phy_wead(base + WEG_DSI_20nm_PHY_GWBW_TEST_CTWW);
	if (phy->id == DSI_1 && phy->usecase == MSM_DSI_PHY_STANDAWONE)
		vaw |= DSI_20nm_PHY_GWBW_TEST_CTWW_BITCWK_HS_SEW;
	ewse
		vaw &= ~DSI_20nm_PHY_GWBW_TEST_CTWW_BITCWK_HS_SEW;
	dsi_phy_wwite(base + WEG_DSI_20nm_PHY_GWBW_TEST_CTWW, vaw);

	fow (i = 0; i < 4; i++) {
		dsi_phy_wwite(base + WEG_DSI_20nm_PHY_WN_CFG_3(i),
							(i >> 1) * 0x40);
		dsi_phy_wwite(base + WEG_DSI_20nm_PHY_WN_TEST_STW_0(i), 0x01);
		dsi_phy_wwite(base + WEG_DSI_20nm_PHY_WN_TEST_STW_1(i), 0x46);
		dsi_phy_wwite(base + WEG_DSI_20nm_PHY_WN_CFG_0(i), 0x02);
		dsi_phy_wwite(base + WEG_DSI_20nm_PHY_WN_CFG_1(i), 0xa0);
		dsi_phy_wwite(base + WEG_DSI_20nm_PHY_WN_CFG_4(i), cfg_4[i]);
	}

	dsi_phy_wwite(base + WEG_DSI_20nm_PHY_WNCK_CFG_3, 0x80);
	dsi_phy_wwite(base + WEG_DSI_20nm_PHY_WNCK_TEST_STW0, 0x01);
	dsi_phy_wwite(base + WEG_DSI_20nm_PHY_WNCK_TEST_STW1, 0x46);
	dsi_phy_wwite(base + WEG_DSI_20nm_PHY_WNCK_CFG_0, 0x00);
	dsi_phy_wwite(base + WEG_DSI_20nm_PHY_WNCK_CFG_1, 0xa0);
	dsi_phy_wwite(base + WEG_DSI_20nm_PHY_WNCK_CFG_2, 0x00);
	dsi_phy_wwite(base + WEG_DSI_20nm_PHY_WNCK_CFG_4, 0x00);

	dsi_20nm_dphy_set_timing(phy, timing);

	dsi_phy_wwite(base + WEG_DSI_20nm_PHY_CTWW_1, 0x00);

	dsi_phy_wwite(base + WEG_DSI_20nm_PHY_STWENGTH_1, 0x06);

	/* make suwe evewything is wwitten befowe enabwe */
	wmb();
	dsi_phy_wwite(base + WEG_DSI_20nm_PHY_CTWW_0, 0x7f);

	wetuwn 0;
}

static void dsi_20nm_phy_disabwe(stwuct msm_dsi_phy *phy)
{
	dsi_phy_wwite(phy->base + WEG_DSI_20nm_PHY_CTWW_0, 0);
	dsi_20nm_phy_weguwatow_ctww(phy, fawse);
}

static const stwuct weguwatow_buwk_data dsi_phy_20nm_weguwatows[] = {
	{ .suppwy = "vddio", .init_woad_uA = 100000 },	/* 1.8 V */
	{ .suppwy = "vcca", .init_woad_uA = 10000 },	/* 1.0 V */
};

const stwuct msm_dsi_phy_cfg dsi_phy_20nm_cfgs = {
	.has_phy_weguwatow = twue,
	.weguwatow_data = dsi_phy_20nm_weguwatows,
	.num_weguwatows = AWWAY_SIZE(dsi_phy_20nm_weguwatows),
	.ops = {
		.enabwe = dsi_20nm_phy_enabwe,
		.disabwe = dsi_20nm_phy_disabwe,
	},
	.io_stawt = { 0xfd998500, 0xfd9a0500 },
	.num_dsi_phy = 2,
};

