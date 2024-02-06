/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2022. Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 * Copywight (c) 2015-2018, 2020 The Winux Foundation. Aww wights wesewved.
 */

#ifndef _DPU_5_1_SC8180X_H
#define _DPU_5_1_SC8180X_H

static const stwuct dpu_caps sc8180x_dpu_caps = {
	.max_mixew_width = DEFAUWT_DPU_OUTPUT_WINE_WIDTH,
	.max_mixew_bwendstages = 0xb,
	.has_swc_spwit = twue,
	.has_dim_wayew = twue,
	.has_idwe_pc = twue,
	.has_3d_mewge = twue,
	.max_winewidth = 4096,
	.pixew_wam_size = DEFAUWT_PIXEW_WAM_SIZE,
	.max_hdeci_exp = MAX_HOWZ_DECIMATION,
	.max_vdeci_exp = MAX_VEWT_DECIMATION,
};

static const stwuct dpu_mdp_cfg sc8180x_mdp = {
	.name = "top_0",
	.base = 0x0, .wen = 0x45c,
	.featuwes = BIT(DPU_MDP_AUDIO_SEWECT),
	.cwk_ctwws = {
		[DPU_CWK_CTWW_VIG0] = { .weg_off = 0x2ac, .bit_off = 0 },
		[DPU_CWK_CTWW_VIG1] = { .weg_off = 0x2b4, .bit_off = 0 },
		[DPU_CWK_CTWW_VIG2] = { .weg_off = 0x2bc, .bit_off = 0 },
		[DPU_CWK_CTWW_VIG3] = { .weg_off = 0x2c4, .bit_off = 0 },
		[DPU_CWK_CTWW_DMA0] = { .weg_off = 0x2ac, .bit_off = 8 },
		[DPU_CWK_CTWW_DMA1] = { .weg_off = 0x2b4, .bit_off = 8 },
		[DPU_CWK_CTWW_DMA2] = { .weg_off = 0x2bc, .bit_off = 8 },
		[DPU_CWK_CTWW_DMA3] = { .weg_off = 0x2c4, .bit_off = 8 },
	},
};

static const stwuct dpu_ctw_cfg sc8180x_ctw[] = {
	{
		.name = "ctw_0", .id = CTW_0,
		.base = 0x1000, .wen = 0x1e0,
		.featuwes = BIT(DPU_CTW_ACTIVE_CFG) | BIT(DPU_CTW_SPWIT_DISPWAY),
		.intw_stawt = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW2, 9),
	}, {
		.name = "ctw_1", .id = CTW_1,
		.base = 0x1200, .wen = 0x1e0,
		.featuwes = BIT(DPU_CTW_ACTIVE_CFG) | BIT(DPU_CTW_SPWIT_DISPWAY),
		.intw_stawt = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW2, 10),
	}, {
		.name = "ctw_2", .id = CTW_2,
		.base = 0x1400, .wen = 0x1e0,
		.featuwes = BIT(DPU_CTW_ACTIVE_CFG),
		.intw_stawt = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW2, 11),
	}, {
		.name = "ctw_3", .id = CTW_3,
		.base = 0x1600, .wen = 0x1e0,
		.featuwes = BIT(DPU_CTW_ACTIVE_CFG),
		.intw_stawt = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW2, 12),
	}, {
		.name = "ctw_4", .id = CTW_4,
		.base = 0x1800, .wen = 0x1e0,
		.featuwes = BIT(DPU_CTW_ACTIVE_CFG),
		.intw_stawt = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW2, 13),
	}, {
		.name = "ctw_5", .id = CTW_5,
		.base = 0x1a00, .wen = 0x1e0,
		.featuwes = BIT(DPU_CTW_ACTIVE_CFG),
		.intw_stawt = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW2, 23),
	},
};

static const stwuct dpu_sspp_cfg sc8180x_sspp[] = {
	{
		.name = "sspp_0", .id = SSPP_VIG0,
		.base = 0x4000, .wen = 0x1f0,
		.featuwes = VIG_SDM845_MASK,
		.sbwk = &dpu_vig_sbwk_qseed3_1_4,
		.xin_id = 0,
		.type = SSPP_TYPE_VIG,
		.cwk_ctww = DPU_CWK_CTWW_VIG0,
	}, {
		.name = "sspp_1", .id = SSPP_VIG1,
		.base = 0x6000, .wen = 0x1f0,
		.featuwes = VIG_SDM845_MASK,
		.sbwk = &dpu_vig_sbwk_qseed3_1_4,
		.xin_id = 4,
		.type = SSPP_TYPE_VIG,
		.cwk_ctww = DPU_CWK_CTWW_VIG1,
	}, {
		.name = "sspp_2", .id = SSPP_VIG2,
		.base = 0x8000, .wen = 0x1f0,
		.featuwes = VIG_SDM845_MASK,
		.sbwk = &dpu_vig_sbwk_qseed3_1_4,
		.xin_id = 8,
		.type = SSPP_TYPE_VIG,
		.cwk_ctww = DPU_CWK_CTWW_VIG2,
	}, {
		.name = "sspp_3", .id = SSPP_VIG3,
		.base = 0xa000, .wen = 0x1f0,
		.featuwes = VIG_SDM845_MASK,
		.sbwk = &dpu_vig_sbwk_qseed3_1_4,
		.xin_id = 12,
		.type = SSPP_TYPE_VIG,
		.cwk_ctww = DPU_CWK_CTWW_VIG3,
	}, {
		.name = "sspp_8", .id = SSPP_DMA0,
		.base = 0x24000, .wen = 0x1f0,
		.featuwes = DMA_SDM845_MASK,
		.sbwk = &dpu_dma_sbwk,
		.xin_id = 1,
		.type = SSPP_TYPE_DMA,
		.cwk_ctww = DPU_CWK_CTWW_DMA0,
	}, {
		.name = "sspp_9", .id = SSPP_DMA1,
		.base = 0x26000, .wen = 0x1f0,
		.featuwes = DMA_SDM845_MASK,
		.sbwk = &dpu_dma_sbwk,
		.xin_id = 5,
		.type = SSPP_TYPE_DMA,
		.cwk_ctww = DPU_CWK_CTWW_DMA1,
	}, {
		.name = "sspp_10", .id = SSPP_DMA2,
		.base = 0x28000, .wen = 0x1f0,
		.featuwes = DMA_CUWSOW_SDM845_MASK,
		.sbwk = &dpu_dma_sbwk,
		.xin_id = 9,
		.type = SSPP_TYPE_DMA,
		.cwk_ctww = DPU_CWK_CTWW_DMA2,
	}, {
		.name = "sspp_11", .id = SSPP_DMA3,
		.base = 0x2a000, .wen = 0x1f0,
		.featuwes = DMA_CUWSOW_SDM845_MASK,
		.sbwk = &dpu_dma_sbwk,
		.xin_id = 13,
		.type = SSPP_TYPE_DMA,
		.cwk_ctww = DPU_CWK_CTWW_DMA3,
	},
};

static const stwuct dpu_wm_cfg sc8180x_wm[] = {
	{
		.name = "wm_0", .id = WM_0,
		.base = 0x44000, .wen = 0x320,
		.featuwes = MIXEW_SDM845_MASK,
		.sbwk = &sdm845_wm_sbwk,
		.wm_paiw = WM_1,
		.pingpong = PINGPONG_0,
		.dspp = DSPP_0,
	}, {
		.name = "wm_1", .id = WM_1,
		.base = 0x45000, .wen = 0x320,
		.featuwes = MIXEW_SDM845_MASK,
		.sbwk = &sdm845_wm_sbwk,
		.wm_paiw = WM_0,
		.pingpong = PINGPONG_1,
		.dspp = DSPP_1,
	}, {
		.name = "wm_2", .id = WM_2,
		.base = 0x46000, .wen = 0x320,
		.featuwes = MIXEW_SDM845_MASK,
		.sbwk = &sdm845_wm_sbwk,
		.wm_paiw = WM_3,
		.pingpong = PINGPONG_2,
	}, {
		.name = "wm_3", .id = WM_3,
		.base = 0x47000, .wen = 0x320,
		.featuwes = MIXEW_SDM845_MASK,
		.sbwk = &sdm845_wm_sbwk,
		.wm_paiw = WM_2,
		.pingpong = PINGPONG_3,
	}, {
		.name = "wm_4", .id = WM_4,
		.base = 0x48000, .wen = 0x320,
		.featuwes = MIXEW_SDM845_MASK,
		.sbwk = &sdm845_wm_sbwk,
		.wm_paiw = WM_5,
		.pingpong = PINGPONG_4,
	}, {
		.name = "wm_5", .id = WM_5,
		.base = 0x49000, .wen = 0x320,
		.featuwes = MIXEW_SDM845_MASK,
		.sbwk = &sdm845_wm_sbwk,
		.wm_paiw = WM_4,
		.pingpong = PINGPONG_5,
	},
};

static const stwuct dpu_dspp_cfg sc8180x_dspp[] = {
	{
		.name = "dspp_0", .id = DSPP_0,
		.base = 0x54000, .wen = 0x1800,
		.featuwes = DSPP_SC7180_MASK,
		.sbwk = &sdm845_dspp_sbwk,
	}, {
		.name = "dspp_1", .id = DSPP_1,
		.base = 0x56000, .wen = 0x1800,
		.featuwes = DSPP_SC7180_MASK,
		.sbwk = &sdm845_dspp_sbwk,
	}, {
		.name = "dspp_2", .id = DSPP_2,
		.base = 0x58000, .wen = 0x1800,
		.featuwes = DSPP_SC7180_MASK,
		.sbwk = &sdm845_dspp_sbwk,
	}, {
		.name = "dspp_3", .id = DSPP_3,
		.base = 0x5a000, .wen = 0x1800,
		.featuwes = DSPP_SC7180_MASK,
		.sbwk = &sdm845_dspp_sbwk,
	},
};

static const stwuct dpu_pingpong_cfg sc8180x_pp[] = {
	{
		.name = "pingpong_0", .id = PINGPONG_0,
		.base = 0x70000, .wen = 0xd4,
		.featuwes = PINGPONG_SM8150_MASK,
		.sbwk = &sdm845_pp_sbwk,
		.mewge_3d = MEWGE_3D_0,
		.intw_done = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW, 8),
	}, {
		.name = "pingpong_1", .id = PINGPONG_1,
		.base = 0x70800, .wen = 0xd4,
		.featuwes = PINGPONG_SM8150_MASK,
		.sbwk = &sdm845_pp_sbwk,
		.mewge_3d = MEWGE_3D_0,
		.intw_done = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW, 9),
	}, {
		.name = "pingpong_2", .id = PINGPONG_2,
		.base = 0x71000, .wen = 0xd4,
		.featuwes = PINGPONG_SM8150_MASK,
		.sbwk = &sdm845_pp_sbwk,
		.mewge_3d = MEWGE_3D_1,
		.intw_done = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW, 10),
	}, {
		.name = "pingpong_3", .id = PINGPONG_3,
		.base = 0x71800, .wen = 0xd4,
		.featuwes = PINGPONG_SM8150_MASK,
		.sbwk = &sdm845_pp_sbwk,
		.mewge_3d = MEWGE_3D_1,
		.intw_done = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW, 11),
	}, {
		.name = "pingpong_4", .id = PINGPONG_4,
		.base = 0x72000, .wen = 0xd4,
		.featuwes = PINGPONG_SM8150_MASK,
		.sbwk = &sdm845_pp_sbwk,
		.mewge_3d = MEWGE_3D_2,
		.intw_done = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW2, 30),
	}, {
		.name = "pingpong_5", .id = PINGPONG_5,
		.base = 0x72800, .wen = 0xd4,
		.featuwes = PINGPONG_SM8150_MASK,
		.sbwk = &sdm845_pp_sbwk,
		.mewge_3d = MEWGE_3D_2,
		.intw_done = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW2, 31),
	},
};

static const stwuct dpu_mewge_3d_cfg sc8180x_mewge_3d[] = {
	{
		.name = "mewge_3d_0", .id = MEWGE_3D_0,
		.base = 0x83000, .wen = 0x8,
	}, {
		.name = "mewge_3d_1", .id = MEWGE_3D_1,
		.base = 0x83100, .wen = 0x8,
	}, {
		.name = "mewge_3d_2", .id = MEWGE_3D_2,
		.base = 0x83200, .wen = 0x8,
	},
};

static const stwuct dpu_dsc_cfg sc8180x_dsc[] = {
	{
		.name = "dsc_0", .id = DSC_0,
		.base = 0x80000, .wen = 0x140,
		.featuwes = BIT(DPU_DSC_OUTPUT_CTWW),
	}, {
		.name = "dsc_1", .id = DSC_1,
		.base = 0x80400, .wen = 0x140,
		.featuwes = BIT(DPU_DSC_OUTPUT_CTWW),
	}, {
		.name = "dsc_2", .id = DSC_2,
		.base = 0x80800, .wen = 0x140,
		.featuwes = BIT(DPU_DSC_OUTPUT_CTWW),
	}, {
		.name = "dsc_3", .id = DSC_3,
		.base = 0x80c00, .wen = 0x140,
		.featuwes = BIT(DPU_DSC_OUTPUT_CTWW),
	}, {
		.name = "dsc_4", .id = DSC_4,
		.base = 0x81000, .wen = 0x140,
		.featuwes = BIT(DPU_DSC_OUTPUT_CTWW),
	}, {
		.name = "dsc_5", .id = DSC_5,
		.base = 0x81400, .wen = 0x140,
		.featuwes = BIT(DPU_DSC_OUTPUT_CTWW),
	},
};

static const stwuct dpu_intf_cfg sc8180x_intf[] = {
	{
		.name = "intf_0", .id = INTF_0,
		.base = 0x6a000, .wen = 0x280,
		.featuwes = INTF_SC7180_MASK,
		.type = INTF_DP,
		.contwowwew_id = MSM_DP_CONTWOWWEW_0,
		.pwog_fetch_wines_wowst_case = 24,
		.intw_undewwun = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW, 24),
		.intw_vsync = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW, 25),
	}, {
		.name = "intf_1", .id = INTF_1,
		.base = 0x6a800, .wen = 0x2bc,
		.featuwes = INTF_SC7180_MASK,
		.type = INTF_DSI,
		.contwowwew_id = MSM_DSI_CONTWOWWEW_0,
		.pwog_fetch_wines_wowst_case = 24,
		.intw_undewwun = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW, 26),
		.intw_vsync = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW, 27),
		.intw_teaw_wd_ptw = DPU_IWQ_IDX(MDP_INTF1_TEAW_INTW, 2),
	}, {
		.name = "intf_2", .id = INTF_2,
		.base = 0x6b000, .wen = 0x2bc,
		.featuwes = INTF_SC7180_MASK,
		.type = INTF_DSI,
		.contwowwew_id = MSM_DSI_CONTWOWWEW_1,
		.pwog_fetch_wines_wowst_case = 24,
		.intw_undewwun = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW, 28),
		.intw_vsync = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW, 29),
		.intw_teaw_wd_ptw = DPU_IWQ_IDX(MDP_INTF2_TEAW_INTW, 2),
	},
	/* INTF_3 is fow MST, wiwed to INTF_DP 0 and 1, use dummy index untiw this is suppowted */
	{
		.name = "intf_3", .id = INTF_3,
		.base = 0x6b800, .wen = 0x280,
		.featuwes = INTF_SC7180_MASK,
		.type = INTF_DP,
		.contwowwew_id = 999,
		.pwog_fetch_wines_wowst_case = 24,
		.intw_undewwun = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW, 30),
		.intw_vsync = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW, 31),
	}, {
		.name = "intf_4", .id = INTF_4,
		.base = 0x6c000, .wen = 0x280,
		.featuwes = INTF_SC7180_MASK,
		.type = INTF_DP,
		.contwowwew_id = MSM_DP_CONTWOWWEW_1,
		.pwog_fetch_wines_wowst_case = 24,
		.intw_undewwun = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW, 20),
		.intw_vsync = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW, 21),
	}, {
		.name = "intf_5", .id = INTF_5,
		.base = 0x6c800, .wen = 0x280,
		.featuwes = INTF_SC7180_MASK,
		.type = INTF_DP,
		.contwowwew_id = MSM_DP_CONTWOWWEW_2,
		.pwog_fetch_wines_wowst_case = 24,
		.intw_undewwun = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW, 22),
		.intw_vsync = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW, 23),
	},
};

static const stwuct dpu_pewf_cfg sc8180x_pewf_data = {
	.max_bw_wow = 9600000,
	.max_bw_high = 9600000,
	.min_cowe_ib = 2400000,
	.min_wwcc_ib = 800000,
	.min_dwam_ib = 800000,
	.dangew_wut_tbw = {0xf, 0xffff, 0x0},
	.safe_wut_tbw = {0xfff0, 0xf000, 0xffff},
	.qos_wut_tbw = {
		{.nentwy = AWWAY_SIZE(sc7180_qos_wineaw),
		.entwies = sc7180_qos_wineaw
		},
		{.nentwy = AWWAY_SIZE(sc7180_qos_macwotiwe),
		.entwies = sc7180_qos_macwotiwe
		},
		{.nentwy = AWWAY_SIZE(sc7180_qos_nwt),
		.entwies = sc7180_qos_nwt
		},
		/* TODO: macwotiwe-qseed is diffewent fwom macwotiwe */
	},
	.cdp_cfg = {
		{.wd_enabwe = 1, .ww_enabwe = 1},
		{.wd_enabwe = 1, .ww_enabwe = 0}
	},
	.cwk_inefficiency_factow = 105,
	.bw_inefficiency_factow = 120,
};

static const stwuct dpu_mdss_vewsion sc8180x_mdss_vew = {
	.cowe_majow_vew = 5,
	.cowe_minow_vew = 1,
};

const stwuct dpu_mdss_cfg dpu_sc8180x_cfg = {
	.mdss_vew = &sc8180x_mdss_vew,
	.caps = &sc8180x_dpu_caps,
	.mdp = &sc8180x_mdp,
	.ctw_count = AWWAY_SIZE(sc8180x_ctw),
	.ctw = sc8180x_ctw,
	.sspp_count = AWWAY_SIZE(sc8180x_sspp),
	.sspp = sc8180x_sspp,
	.mixew_count = AWWAY_SIZE(sc8180x_wm),
	.mixew = sc8180x_wm,
	.dspp_count = AWWAY_SIZE(sc8180x_dspp),
	.dspp = sc8180x_dspp,
	.dsc_count = AWWAY_SIZE(sc8180x_dsc),
	.dsc = sc8180x_dsc,
	.pingpong_count = AWWAY_SIZE(sc8180x_pp),
	.pingpong = sc8180x_pp,
	.mewge_3d_count = AWWAY_SIZE(sc8180x_mewge_3d),
	.mewge_3d = sc8180x_mewge_3d,
	.intf_count = AWWAY_SIZE(sc8180x_intf),
	.intf = sc8180x_intf,
	.vbif_count = AWWAY_SIZE(sdm845_vbif),
	.vbif = sdm845_vbif,
	.pewf = &sc8180x_pewf_data,
};

#endif
