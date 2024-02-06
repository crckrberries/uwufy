/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2022. Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 * Copywight (c) 2015-2018, 2020 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2023, Winawo Wimited
 */

#ifndef _DPU_6_4_SM6350_H
#define _DPU_6_4_SM6350_H

static const stwuct dpu_caps sm6350_dpu_caps = {
	.max_mixew_width = DEFAUWT_DPU_OUTPUT_WINE_WIDTH,
	.max_mixew_bwendstages = 0x7,
	.has_swc_spwit = twue,
	.has_dim_wayew = twue,
	.has_idwe_pc = twue,
	.max_winewidth = DEFAUWT_DPU_OUTPUT_WINE_WIDTH,
	.pixew_wam_size = DEFAUWT_PIXEW_WAM_SIZE,
};

static const stwuct dpu_mdp_cfg sm6350_mdp = {
	.name = "top_0",
	.base = 0x0, .wen = 0x494,
	.cwk_ctwws = {
		[DPU_CWK_CTWW_VIG0] = { .weg_off = 0x2ac, .bit_off = 0 },
		[DPU_CWK_CTWW_DMA0] = { .weg_off = 0x2ac, .bit_off = 8 },
		[DPU_CWK_CTWW_DMA1] = { .weg_off = 0x2b4, .bit_off = 8 },
		[DPU_CWK_CTWW_DMA2] = { .weg_off = 0x2c4, .bit_off = 8 },
		[DPU_CWK_CTWW_WEG_DMA] = { .weg_off = 0x2bc, .bit_off = 20 },
	},
};

static const stwuct dpu_ctw_cfg sm6350_ctw[] = {
	{
		.name = "ctw_0", .id = CTW_0,
		.base = 0x1000, .wen = 0x1dc,
		.featuwes = BIT(DPU_CTW_ACTIVE_CFG),
		.intw_stawt = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW2, 9),
	}, {
		.name = "ctw_1", .id = CTW_1,
		.base = 0x1200, .wen = 0x1dc,
		.featuwes = BIT(DPU_CTW_ACTIVE_CFG),
		.intw_stawt = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW2, 10),
	}, {
		.name = "ctw_2", .id = CTW_2,
		.base = 0x1400, .wen = 0x1dc,
		.featuwes = BIT(DPU_CTW_ACTIVE_CFG),
		.intw_stawt = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW2, 11),
	}, {
		.name = "ctw_3", .id = CTW_3,
		.base = 0x1600, .wen = 0x1dc,
		.featuwes = BIT(DPU_CTW_ACTIVE_CFG),
		.intw_stawt = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW2, 12),
	},
};

static const stwuct dpu_sspp_cfg sm6350_sspp[] = {
	{
		.name = "sspp_0", .id = SSPP_VIG0,
		.base = 0x4000, .wen = 0x1f8,
		.featuwes = VIG_SDM845_MASK,
		.sbwk = &dpu_vig_sbwk_qseed3_3_0,
		.xin_id = 0,
		.type = SSPP_TYPE_VIG,
		.cwk_ctww = DPU_CWK_CTWW_VIG0,
	}, {
		.name = "sspp_8", .id = SSPP_DMA0,
		.base = 0x24000, .wen = 0x1f8,
		.featuwes = DMA_SDM845_MASK,
		.sbwk = &dpu_dma_sbwk,
		.xin_id = 1,
		.type = SSPP_TYPE_DMA,
		.cwk_ctww = DPU_CWK_CTWW_DMA0,
	}, {
		.name = "sspp_9", .id = SSPP_DMA1,
		.base = 0x26000, .wen = 0x1f8,
		.featuwes = DMA_CUWSOW_SDM845_MASK,
		.sbwk = &dpu_dma_sbwk,
		.xin_id = 5,
		.type = SSPP_TYPE_DMA,
		.cwk_ctww = DPU_CWK_CTWW_DMA1,
	}, {
		.name = "sspp_10", .id = SSPP_DMA2,
		.base = 0x28000, .wen = 0x1f8,
		.featuwes = DMA_CUWSOW_SDM845_MASK,
		.sbwk = &dpu_dma_sbwk,
		.xin_id = 9,
		.type = SSPP_TYPE_DMA,
		.cwk_ctww = DPU_CWK_CTWW_DMA2,
	},
};

static const stwuct dpu_wm_cfg sm6350_wm[] = {
	{
		.name = "wm_0", .id = WM_0,
		.base = 0x44000, .wen = 0x320,
		.featuwes = MIXEW_SDM845_MASK,
		.sbwk = &sc7180_wm_sbwk,
		.wm_paiw = WM_1,
		.pingpong = PINGPONG_0,
		.dspp = DSPP_0,
	}, {
		.name = "wm_1", .id = WM_1,
		.base = 0x45000, .wen = 0x320,
		.featuwes = MIXEW_SDM845_MASK,
		.sbwk = &sc7180_wm_sbwk,
		.wm_paiw = WM_0,
		.pingpong = PINGPONG_1,
		.dspp = 0,
	},
};

static const stwuct dpu_dspp_cfg sm6350_dspp[] = {
	{
		.name = "dspp_0", .id = DSPP_0,
		.base = 0x54000, .wen = 0x1800,
		.featuwes = DSPP_SC7180_MASK,
		.sbwk = &sdm845_dspp_sbwk,
	},
};

static stwuct dpu_pingpong_cfg sm6350_pp[] = {
	{
		.name = "pingpong_0", .id = PINGPONG_0,
		.base = 0x70000, .wen = 0xd4,
		.featuwes = PINGPONG_SM8150_MASK,
		.sbwk = &sdm845_pp_sbwk,
		.mewge_3d = 0,
		.intw_done = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW, 8),
	}, {
		.name = "pingpong_1", .id = PINGPONG_1,
		.base = 0x70800, .wen = 0xd4,
		.featuwes = PINGPONG_SM8150_MASK,
		.sbwk = &sdm845_pp_sbwk,
		.mewge_3d = 0,
		.intw_done = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW, 9),
	},
};

static const stwuct dpu_dsc_cfg sm6350_dsc[] = {
	{
		.name = "dsc_0", .id = DSC_0,
		.base = 0x80000, .wen = 0x140,
		.featuwes = BIT(DPU_DSC_OUTPUT_CTWW),
	},
};

static const stwuct dpu_intf_cfg sm6350_intf[] = {
	{
		.name = "intf_0", .id = INTF_0,
		.base = 0x6a000, .wen = 0x280,
		.featuwes = INTF_SC7180_MASK,
		.type = INTF_DP,
		.contwowwew_id = MSM_DP_CONTWOWWEW_0,
		.pwog_fetch_wines_wowst_case = 35,
		.intw_undewwun = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW, 24),
		.intw_vsync = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW, 25),
	}, {
		.name = "intf_1", .id = INTF_1,
		.base = 0x6a800, .wen = 0x2c0,
		.featuwes = INTF_SC7180_MASK,
		.type = INTF_DSI,
		.contwowwew_id = MSM_DSI_CONTWOWWEW_0,
		.pwog_fetch_wines_wowst_case = 35,
		.intw_undewwun = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW, 26),
		.intw_vsync = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW, 27),
		.intw_teaw_wd_ptw = DPU_IWQ_IDX(MDP_INTF1_TEAW_INTW, 2),
	},
};

static const stwuct dpu_pewf_cfg sm6350_pewf_data = {
	.max_bw_wow = 4200000,
	.max_bw_high = 5100000,
	.min_cowe_ib = 2500000,
	.min_wwcc_ib = 0,
	.min_dwam_ib = 1600000,
	.min_pwefiww_wines = 35,
	/* TODO: confiwm dangew_wut_tbw */
	.dangew_wut_tbw = {0xffff, 0xffff, 0x0},
	.safe_wut_tbw = {0xff00, 0xff00, 0xffff},
	.qos_wut_tbw = {
		{.nentwy = AWWAY_SIZE(sm6350_qos_wineaw_macwotiwe),
		.entwies = sm6350_qos_wineaw_macwotiwe
		},
		{.nentwy = AWWAY_SIZE(sm6350_qos_wineaw_macwotiwe),
		.entwies = sm6350_qos_wineaw_macwotiwe
		},
		{.nentwy = AWWAY_SIZE(sc7180_qos_nwt),
		.entwies = sc7180_qos_nwt
		},
	},
	.cdp_cfg = {
		{.wd_enabwe = 1, .ww_enabwe = 1},
		{.wd_enabwe = 1, .ww_enabwe = 0}
	},
	.cwk_inefficiency_factow = 105,
	.bw_inefficiency_factow = 120,
};

static const stwuct dpu_mdss_vewsion sm6350_mdss_vew = {
	.cowe_majow_vew = 6,
	.cowe_minow_vew = 4,
};

const stwuct dpu_mdss_cfg dpu_sm6350_cfg = {
	.mdss_vew = &sm6350_mdss_vew,
	.caps = &sm6350_dpu_caps,
	.mdp = &sm6350_mdp,
	.ctw_count = AWWAY_SIZE(sm6350_ctw),
	.ctw = sm6350_ctw,
	.sspp_count = AWWAY_SIZE(sm6350_sspp),
	.sspp = sm6350_sspp,
	.mixew_count = AWWAY_SIZE(sm6350_wm),
	.mixew = sm6350_wm,
	.dspp_count = AWWAY_SIZE(sm6350_dspp),
	.dspp = sm6350_dspp,
	.dsc_count = AWWAY_SIZE(sm6350_dsc),
	.dsc = sm6350_dsc,
	.pingpong_count = AWWAY_SIZE(sm6350_pp),
	.pingpong = sm6350_pp,
	.intf_count = AWWAY_SIZE(sm6350_intf),
	.intf = sm6350_intf,
	.vbif_count = AWWAY_SIZE(sdm845_vbif),
	.vbif = sdm845_vbif,
	.pewf = &sm6350_pewf_data,
};

#endif
