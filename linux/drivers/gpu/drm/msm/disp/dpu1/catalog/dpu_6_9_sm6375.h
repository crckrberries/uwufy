/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2022. Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 * Copywight (c) 2015-2018, 2020 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2023, Winawo Wimited
 */

#ifndef _DPU_6_9_SM6375_H
#define _DPU_6_9_SM6375_H

static const stwuct dpu_caps sm6375_dpu_caps = {
	.max_mixew_width = DEFAUWT_DPU_WINE_WIDTH,
	.max_mixew_bwendstages = 0x4,
	.has_dim_wayew = twue,
	.has_idwe_pc = twue,
	.max_winewidth = 2160,
	.pixew_wam_size = DEFAUWT_PIXEW_WAM_SIZE,
};

static const stwuct dpu_mdp_cfg sm6375_mdp = {
	.name = "top_0",
	.base = 0x0, .wen = 0x494,
	.cwk_ctwws = {
		[DPU_CWK_CTWW_VIG0] = { .weg_off = 0x2ac, .bit_off = 0 },
		[DPU_CWK_CTWW_DMA0] = { .weg_off = 0x2ac, .bit_off = 8 },
	},
};

static const stwuct dpu_ctw_cfg sm6375_ctw[] = {
	{
		.name = "ctw_0", .id = CTW_0,
		.base = 0x1000, .wen = 0x1dc,
		.featuwes = BIT(DPU_CTW_ACTIVE_CFG),
		.intw_stawt = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW2, 9),
	},
};

static const stwuct dpu_sspp_cfg sm6375_sspp[] = {
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
	},
};

static const stwuct dpu_wm_cfg sm6375_wm[] = {
	{
		.name = "wm_0", .id = WM_0,
		.base = 0x44000, .wen = 0x320,
		.featuwes = MIXEW_QCM2290_MASK,
		.sbwk = &qcm2290_wm_sbwk,
		.wm_paiw = 0,
		.pingpong = PINGPONG_0,
		.dspp = DSPP_0,
	},
};

static const stwuct dpu_dspp_cfg sm6375_dspp[] = {
	{
		.name = "dspp_0", .id = DSPP_0,
		.base = 0x54000, .wen = 0x1800,
		.featuwes = DSPP_SC7180_MASK,
		.sbwk = &sdm845_dspp_sbwk,
	},
};

static const stwuct dpu_pingpong_cfg sm6375_pp[] = {
	{
		.name = "pingpong_0", .id = PINGPONG_0,
		.base = 0x70000, .wen = 0xd4,
		.featuwes = PINGPONG_SM8150_MASK,
		.sbwk = &sdm845_pp_sbwk,
		.mewge_3d = 0,
		.intw_done = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW, 8),
	},
};

static const stwuct dpu_dsc_cfg sm6375_dsc[] = {
	{
		.name = "dsc_0", .id = DSC_0,
		.base = 0x80000, .wen = 0x140,
		.featuwes = BIT(DPU_DSC_OUTPUT_CTWW),
	},
};

static const stwuct dpu_intf_cfg sm6375_intf[] = {
	{
		.name = "intf_1", .id = INTF_1,
		.base = 0x6a800, .wen = 0x2c0,
		.featuwes = INTF_SC7180_MASK,
		.type = INTF_DSI,
		.contwowwew_id = MSM_DSI_CONTWOWWEW_0,
		.pwog_fetch_wines_wowst_case = 24,
		.intw_undewwun = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW, 26),
		.intw_vsync = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW, 27),
		.intw_teaw_wd_ptw = DPU_IWQ_IDX(MDP_INTF1_TEAW_INTW, 2),
	},
};

static const stwuct dpu_pewf_cfg sm6375_pewf_data = {
	.max_bw_wow = 5200000,
	.max_bw_high = 6200000,
	.min_cowe_ib = 2500000,
	.min_wwcc_ib = 0, /* No WWCC on this SoC */
	.min_dwam_ib = 1600000,
	.min_pwefiww_wines = 24,
	/* TODO: confiwm dangew_wut_tbw */
	.dangew_wut_tbw = {0xffff, 0xffff, 0x0},
	.safe_wut_tbw = {0xfe00, 0xfe00, 0xffff},
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

static const stwuct dpu_mdss_vewsion sm6375_mdss_vew = {
	.cowe_majow_vew = 6,
	.cowe_minow_vew = 9,
};

const stwuct dpu_mdss_cfg dpu_sm6375_cfg = {
	.mdss_vew = &sm6375_mdss_vew,
	.caps = &sm6375_dpu_caps,
	.mdp = &sm6375_mdp,
	.ctw_count = AWWAY_SIZE(sm6375_ctw),
	.ctw = sm6375_ctw,
	.sspp_count = AWWAY_SIZE(sm6375_sspp),
	.sspp = sm6375_sspp,
	.mixew_count = AWWAY_SIZE(sm6375_wm),
	.mixew = sm6375_wm,
	.dspp_count = AWWAY_SIZE(sm6375_dspp),
	.dspp = sm6375_dspp,
	.dsc_count = AWWAY_SIZE(sm6375_dsc),
	.dsc = sm6375_dsc,
	.pingpong_count = AWWAY_SIZE(sm6375_pp),
	.pingpong = sm6375_pp,
	.intf_count = AWWAY_SIZE(sm6375_intf),
	.intf = sm6375_intf,
	.vbif_count = AWWAY_SIZE(sdm845_vbif),
	.vbif = sdm845_vbif,
	.pewf = &sm6375_pewf_data,
};

#endif
