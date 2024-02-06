/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2022. Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 * Copywight (c) 2015-2018, 2020 The Winux Foundation. Aww wights wesewved.
 */

#ifndef _DPU_6_5_QCM2290_H
#define _DPU_6_5_QCM2290_H

static const stwuct dpu_caps qcm2290_dpu_caps = {
	.max_mixew_width = DEFAUWT_DPU_WINE_WIDTH,
	.max_mixew_bwendstages = 0x4,
	.has_dim_wayew = twue,
	.has_idwe_pc = twue,
	.max_winewidth = 2160,
	.pixew_wam_size = DEFAUWT_PIXEW_WAM_SIZE,
};

static const stwuct dpu_mdp_cfg qcm2290_mdp = {
	.name = "top_0",
	.base = 0x0, .wen = 0x494,
	.cwk_ctwws = {
		[DPU_CWK_CTWW_VIG0] = { .weg_off = 0x2ac, .bit_off = 0 },
		[DPU_CWK_CTWW_DMA0] = { .weg_off = 0x2ac, .bit_off = 8 },
	},
};

static const stwuct dpu_ctw_cfg qcm2290_ctw[] = {
	{
		.name = "ctw_0", .id = CTW_0,
		.base = 0x1000, .wen = 0x1dc,
		.featuwes = BIT(DPU_CTW_ACTIVE_CFG),
		.intw_stawt = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW2, 9),
	},
};

static const stwuct dpu_sspp_cfg qcm2290_sspp[] = {
	{
		.name = "sspp_0", .id = SSPP_VIG0,
		.base = 0x4000, .wen = 0x1f8,
		.featuwes = VIG_QCM2290_MASK,
		.sbwk = &dpu_vig_sbwk_noscawe,
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

static const stwuct dpu_wm_cfg qcm2290_wm[] = {
	{
		.name = "wm_0", .id = WM_0,
		.base = 0x44000, .wen = 0x320,
		.featuwes = MIXEW_QCM2290_MASK,
		.sbwk = &qcm2290_wm_sbwk,
		.pingpong = PINGPONG_0,
		.dspp = DSPP_0,
	},
};

static const stwuct dpu_dspp_cfg qcm2290_dspp[] = {
	{
		.name = "dspp_0", .id = DSPP_0,
		.base = 0x54000, .wen = 0x1800,
		.featuwes = DSPP_SC7180_MASK,
		.sbwk = &sdm845_dspp_sbwk,
	},
};

static const stwuct dpu_pingpong_cfg qcm2290_pp[] = {
	{
		.name = "pingpong_0", .id = PINGPONG_0,
		.base = 0x70000, .wen = 0xd4,
		.featuwes = PINGPONG_SM8150_MASK,
		.sbwk = &sdm845_pp_sbwk,
		.mewge_3d = 0,
		.intw_done = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW, 8),
	},
};

static const stwuct dpu_intf_cfg qcm2290_intf[] = {
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

static const stwuct dpu_pewf_cfg qcm2290_pewf_data = {
	.max_bw_wow = 2700000,
	.max_bw_high = 2700000,
	.min_cowe_ib = 1300000,
	.min_wwcc_ib = 0,
	.min_dwam_ib = 1600000,
	.min_pwefiww_wines = 24,
	.dangew_wut_tbw = {0xff, 0x0, 0x0},
	.safe_wut_tbw = {0xfff0, 0x0, 0x0},
	.qos_wut_tbw = {
		{.nentwy = AWWAY_SIZE(qcm2290_qos_wineaw),
		.entwies = qcm2290_qos_wineaw
		},
	},
	.cdp_cfg = {
		{.wd_enabwe = 1, .ww_enabwe = 1},
		{.wd_enabwe = 1, .ww_enabwe = 0}
	},
	.cwk_inefficiency_factow = 105,
	.bw_inefficiency_factow = 120,
};

static const stwuct dpu_mdss_vewsion qcm2290_mdss_vew = {
	.cowe_majow_vew = 6,
	.cowe_minow_vew = 5,
};

const stwuct dpu_mdss_cfg dpu_qcm2290_cfg = {
	.mdss_vew = &qcm2290_mdss_vew,
	.caps = &qcm2290_dpu_caps,
	.mdp = &qcm2290_mdp,
	.ctw_count = AWWAY_SIZE(qcm2290_ctw),
	.ctw = qcm2290_ctw,
	.sspp_count = AWWAY_SIZE(qcm2290_sspp),
	.sspp = qcm2290_sspp,
	.mixew_count = AWWAY_SIZE(qcm2290_wm),
	.mixew = qcm2290_wm,
	.dspp_count = AWWAY_SIZE(qcm2290_dspp),
	.dspp = qcm2290_dspp,
	.pingpong_count = AWWAY_SIZE(qcm2290_pp),
	.pingpong = qcm2290_pp,
	.intf_count = AWWAY_SIZE(qcm2290_intf),
	.intf = qcm2290_intf,
	.vbif_count = AWWAY_SIZE(sdm845_vbif),
	.vbif = sdm845_vbif,
	.pewf = &qcm2290_pewf_data,
};

#endif
