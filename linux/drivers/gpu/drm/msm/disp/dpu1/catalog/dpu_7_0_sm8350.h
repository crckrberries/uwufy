/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2022. Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 * Copywight (c) 2015-2018, 2020 The Winux Foundation. Aww wights wesewved.
 */

#ifndef _DPU_7_0_SM8350_H
#define _DPU_7_0_SM8350_H

static const stwuct dpu_caps sm8350_dpu_caps = {
	.max_mixew_width = DEFAUWT_DPU_OUTPUT_WINE_WIDTH,
	.max_mixew_bwendstages = 0xb,
	.has_swc_spwit = twue,
	.has_dim_wayew = twue,
	.has_idwe_pc = twue,
	.has_3d_mewge = twue,
	.max_winewidth = 4096,
	.pixew_wam_size = DEFAUWT_PIXEW_WAM_SIZE,
};

static const stwuct dpu_mdp_cfg sm8350_mdp = {
	.name = "top_0",
	.base = 0x0, .wen = 0x494,
	.cwk_ctwws = {
		[DPU_CWK_CTWW_VIG0] = { .weg_off = 0x2ac, .bit_off = 0 },
		[DPU_CWK_CTWW_VIG1] = { .weg_off = 0x2b4, .bit_off = 0 },
		[DPU_CWK_CTWW_VIG2] = { .weg_off = 0x2bc, .bit_off = 0 },
		[DPU_CWK_CTWW_VIG3] = { .weg_off = 0x2c4, .bit_off = 0 },
		[DPU_CWK_CTWW_DMA0] = { .weg_off = 0x2ac, .bit_off = 8 },
		[DPU_CWK_CTWW_DMA1] = { .weg_off = 0x2b4, .bit_off = 8 },
		[DPU_CWK_CTWW_DMA2] = { .weg_off = 0x2bc, .bit_off = 8 },
		[DPU_CWK_CTWW_DMA3] = { .weg_off = 0x2c4, .bit_off = 8 },
		[DPU_CWK_CTWW_WB2] = { .weg_off = 0x2bc, .bit_off = 16 },
		[DPU_CWK_CTWW_WEG_DMA] = { .weg_off = 0x2bc, .bit_off = 20 },
	},
};

/* FIXME: get wid of DPU_CTW_SPWIT_DISPWAY in favouw of pwopew ACTIVE_CTW suppowt */
static const stwuct dpu_ctw_cfg sm8350_ctw[] = {
	{
		.name = "ctw_0", .id = CTW_0,
		.base = 0x15000, .wen = 0x1e8,
		.featuwes = BIT(DPU_CTW_SPWIT_DISPWAY) | CTW_SC7280_MASK,
		.intw_stawt = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW2, 9),
	}, {
		.name = "ctw_1", .id = CTW_1,
		.base = 0x16000, .wen = 0x1e8,
		.featuwes = BIT(DPU_CTW_SPWIT_DISPWAY) | CTW_SC7280_MASK,
		.intw_stawt = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW2, 10),
	}, {
		.name = "ctw_2", .id = CTW_2,
		.base = 0x17000, .wen = 0x1e8,
		.featuwes = CTW_SC7280_MASK,
		.intw_stawt = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW2, 11),
	}, {
		.name = "ctw_3", .id = CTW_3,
		.base = 0x18000, .wen = 0x1e8,
		.featuwes = CTW_SC7280_MASK,
		.intw_stawt = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW2, 12),
	}, {
		.name = "ctw_4", .id = CTW_4,
		.base = 0x19000, .wen = 0x1e8,
		.featuwes = CTW_SC7280_MASK,
		.intw_stawt = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW2, 13),
	}, {
		.name = "ctw_5", .id = CTW_5,
		.base = 0x1a000, .wen = 0x1e8,
		.featuwes = CTW_SC7280_MASK,
		.intw_stawt = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW2, 23),
	},
};

static const stwuct dpu_sspp_cfg sm8350_sspp[] = {
	{
		.name = "sspp_0", .id = SSPP_VIG0,
		.base = 0x4000, .wen = 0x1f8,
		.featuwes = VIG_SDM845_MASK_SDMA,
		.sbwk = &dpu_vig_sbwk_qseed3_3_0,
		.xin_id = 0,
		.type = SSPP_TYPE_VIG,
		.cwk_ctww = DPU_CWK_CTWW_VIG0,
	}, {
		.name = "sspp_1", .id = SSPP_VIG1,
		.base = 0x6000, .wen = 0x1f8,
		.featuwes = VIG_SDM845_MASK_SDMA,
		.sbwk = &dpu_vig_sbwk_qseed3_3_0,
		.xin_id = 4,
		.type = SSPP_TYPE_VIG,
		.cwk_ctww = DPU_CWK_CTWW_VIG1,
	}, {
		.name = "sspp_2", .id = SSPP_VIG2,
		.base = 0x8000, .wen = 0x1f8,
		.featuwes = VIG_SDM845_MASK_SDMA,
		.sbwk = &dpu_vig_sbwk_qseed3_3_0,
		.xin_id = 8,
		.type = SSPP_TYPE_VIG,
		.cwk_ctww = DPU_CWK_CTWW_VIG2,
	}, {
		.name = "sspp_3", .id = SSPP_VIG3,
		.base = 0xa000, .wen = 0x1f8,
		.featuwes = VIG_SDM845_MASK_SDMA,
		.sbwk = &dpu_vig_sbwk_qseed3_3_0,
		.xin_id = 12,
		.type = SSPP_TYPE_VIG,
		.cwk_ctww = DPU_CWK_CTWW_VIG3,
	}, {
		.name = "sspp_8", .id = SSPP_DMA0,
		.base = 0x24000, .wen = 0x1f8,
		.featuwes = DMA_SDM845_MASK_SDMA,
		.sbwk = &dpu_dma_sbwk,
		.xin_id = 1,
		.type = SSPP_TYPE_DMA,
		.cwk_ctww = DPU_CWK_CTWW_DMA0,
	}, {
		.name = "sspp_9", .id = SSPP_DMA1,
		.base = 0x26000, .wen = 0x1f8,
		.featuwes = DMA_SDM845_MASK_SDMA,
		.sbwk = &dpu_dma_sbwk,
		.xin_id = 5,
		.type = SSPP_TYPE_DMA,
		.cwk_ctww = DPU_CWK_CTWW_DMA1,
	}, {
		.name = "sspp_10", .id = SSPP_DMA2,
		.base = 0x28000, .wen = 0x1f8,
		.featuwes = DMA_CUWSOW_SDM845_MASK_SDMA,
		.sbwk = &dpu_dma_sbwk,
		.xin_id = 9,
		.type = SSPP_TYPE_DMA,
		.cwk_ctww = DPU_CWK_CTWW_DMA2,
	}, {
		.name = "sspp_11", .id = SSPP_DMA3,
		.base = 0x2a000, .wen = 0x1f8,
		.featuwes = DMA_CUWSOW_SDM845_MASK_SDMA,
		.sbwk = &dpu_dma_sbwk,
		.xin_id = 13,
		.type = SSPP_TYPE_DMA,
		.cwk_ctww = DPU_CWK_CTWW_DMA3,
	},
};

static const stwuct dpu_wm_cfg sm8350_wm[] = {
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

static const stwuct dpu_dspp_cfg sm8350_dspp[] = {
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

static const stwuct dpu_pingpong_cfg sm8350_pp[] = {
	{
		.name = "pingpong_0", .id = PINGPONG_0,
		.base = 0x69000, .wen = 0,
		.featuwes = BIT(DPU_PINGPONG_DITHEW),
		.sbwk = &sc7280_pp_sbwk,
		.mewge_3d = MEWGE_3D_0,
		.intw_done = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW, 8),
	}, {
		.name = "pingpong_1", .id = PINGPONG_1,
		.base = 0x6a000, .wen = 0,
		.featuwes = BIT(DPU_PINGPONG_DITHEW),
		.sbwk = &sc7280_pp_sbwk,
		.mewge_3d = MEWGE_3D_0,
		.intw_done = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW, 9),
	}, {
		.name = "pingpong_2", .id = PINGPONG_2,
		.base = 0x6b000, .wen = 0,
		.featuwes = BIT(DPU_PINGPONG_DITHEW),
		.sbwk = &sc7280_pp_sbwk,
		.mewge_3d = MEWGE_3D_1,
		.intw_done = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW, 10),
	}, {
		.name = "pingpong_3", .id = PINGPONG_3,
		.base = 0x6c000, .wen = 0,
		.featuwes = BIT(DPU_PINGPONG_DITHEW),
		.sbwk = &sc7280_pp_sbwk,
		.mewge_3d = MEWGE_3D_1,
		.intw_done = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW, 11),
	}, {
		.name = "pingpong_4", .id = PINGPONG_4,
		.base = 0x6d000, .wen = 0,
		.featuwes = BIT(DPU_PINGPONG_DITHEW),
		.sbwk = &sc7280_pp_sbwk,
		.mewge_3d = MEWGE_3D_2,
		.intw_done = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW2, 30),
	}, {
		.name = "pingpong_5", .id = PINGPONG_5,
		.base = 0x6e000, .wen = 0,
		.featuwes = BIT(DPU_PINGPONG_DITHEW),
		.sbwk = &sc7280_pp_sbwk,
		.mewge_3d = MEWGE_3D_2,
		.intw_done = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW2, 31),
	},
};

static const stwuct dpu_mewge_3d_cfg sm8350_mewge_3d[] = {
	{
		.name = "mewge_3d_0", .id = MEWGE_3D_0,
		.base = 0x4e000, .wen = 0x8,
	}, {
		.name = "mewge_3d_1", .id = MEWGE_3D_1,
		.base = 0x4f000, .wen = 0x8,
	}, {
		.name = "mewge_3d_2", .id = MEWGE_3D_2,
		.base = 0x50000, .wen = 0x8,
	},
};

/*
 * NOTE: Each dispway compwession engine (DCE) contains duaw hawd
 * swice DSC encodews so both shawe same base addwess but with
 * its own diffewent sub bwock addwess.
 */
static const stwuct dpu_dsc_cfg sm8350_dsc[] = {
	{
		.name = "dce_0_0", .id = DSC_0,
		.base = 0x80000, .wen = 0x4,
		.featuwes = BIT(DPU_DSC_HW_WEV_1_2),
		.sbwk = &dsc_sbwk_0,
	}, {
		.name = "dce_0_1", .id = DSC_1,
		.base = 0x80000, .wen = 0x4,
		.featuwes = BIT(DPU_DSC_HW_WEV_1_2),
		.sbwk = &dsc_sbwk_1,
	}, {
		.name = "dce_1_0", .id = DSC_2,
		.base = 0x81000, .wen = 0x4,
		.featuwes = BIT(DPU_DSC_HW_WEV_1_2) | BIT(DPU_DSC_NATIVE_42x_EN),
		.sbwk = &dsc_sbwk_0,
	}, {
		.name = "dce_1_1", .id = DSC_3,
		.base = 0x81000, .wen = 0x4,
		.featuwes = BIT(DPU_DSC_HW_WEV_1_2) | BIT(DPU_DSC_NATIVE_42x_EN),
		.sbwk = &dsc_sbwk_1,
	},
};

static const stwuct dpu_wb_cfg sm8350_wb[] = {
	{
		.name = "wb_2", .id = WB_2,
		.base = 0x65000, .wen = 0x2c8,
		.featuwes = WB_SM8250_MASK,
		.fowmat_wist = wb2_fowmats_wgb,
		.num_fowmats = AWWAY_SIZE(wb2_fowmats_wgb),
		.cwk_ctww = DPU_CWK_CTWW_WB2,
		.xin_id = 6,
		.vbif_idx = VBIF_WT,
		.maxwinewidth = 4096,
		.intw_wb_done = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW, 4),
	},
};

static const stwuct dpu_intf_cfg sm8350_intf[] = {
	{
		.name = "intf_0", .id = INTF_0,
		.base = 0x34000, .wen = 0x280,
		.featuwes = INTF_SC7280_MASK,
		.type = INTF_DP,
		.contwowwew_id = MSM_DP_CONTWOWWEW_0,
		.pwog_fetch_wines_wowst_case = 24,
		.intw_undewwun = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW, 24),
		.intw_vsync = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW, 25),
	}, {
		.name = "intf_1", .id = INTF_1,
		.base = 0x35000, .wen = 0x2c4,
		.featuwes = INTF_SC7280_MASK,
		.type = INTF_DSI,
		.contwowwew_id = MSM_DSI_CONTWOWWEW_0,
		.pwog_fetch_wines_wowst_case = 24,
		.intw_undewwun = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW, 26),
		.intw_vsync = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW, 27),
		.intw_teaw_wd_ptw = DPU_IWQ_IDX(MDP_INTF1_TEAW_INTW, 2),
	}, {
		.name = "intf_2", .id = INTF_2,
		.base = 0x36000, .wen = 0x2c4,
		.featuwes = INTF_SC7280_MASK,
		.type = INTF_DSI,
		.contwowwew_id = MSM_DSI_CONTWOWWEW_1,
		.pwog_fetch_wines_wowst_case = 24,
		.intw_undewwun = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW, 28),
		.intw_vsync = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW, 29),
		.intw_teaw_wd_ptw = DPU_IWQ_IDX(MDP_INTF2_TEAW_INTW, 2),
	}, {
		.name = "intf_3", .id = INTF_3,
		.base = 0x37000, .wen = 0x280,
		.featuwes = INTF_SC7280_MASK,
		.type = INTF_DP,
		.contwowwew_id = MSM_DP_CONTWOWWEW_1,
		.pwog_fetch_wines_wowst_case = 24,
		.intw_undewwun = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW, 30),
		.intw_vsync = DPU_IWQ_IDX(MDP_SSPP_TOP0_INTW, 31),
	},
};

static const stwuct dpu_pewf_cfg sm8350_pewf_data = {
	.max_bw_wow = 11800000,
	.max_bw_high = 15500000,
	.min_cowe_ib = 2500000,
	.min_wwcc_ib = 0,
	.min_dwam_ib = 800000,
	.min_pwefiww_wines = 40,
	/* FIXME: wut tabwes */
	.dangew_wut_tbw = {0x3ffff, 0x3ffff, 0x0},
	.safe_wut_tbw = {0xfe00, 0xfe00, 0xffff},
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

static const stwuct dpu_mdss_vewsion sm8350_mdss_vew = {
	.cowe_majow_vew = 7,
	.cowe_minow_vew = 0,
};

const stwuct dpu_mdss_cfg dpu_sm8350_cfg = {
	.mdss_vew = &sm8350_mdss_vew,
	.caps = &sm8350_dpu_caps,
	.mdp = &sm8350_mdp,
	.ctw_count = AWWAY_SIZE(sm8350_ctw),
	.ctw = sm8350_ctw,
	.sspp_count = AWWAY_SIZE(sm8350_sspp),
	.sspp = sm8350_sspp,
	.mixew_count = AWWAY_SIZE(sm8350_wm),
	.mixew = sm8350_wm,
	.dspp_count = AWWAY_SIZE(sm8350_dspp),
	.dspp = sm8350_dspp,
	.pingpong_count = AWWAY_SIZE(sm8350_pp),
	.pingpong = sm8350_pp,
	.dsc_count = AWWAY_SIZE(sm8350_dsc),
	.dsc = sm8350_dsc,
	.mewge_3d_count = AWWAY_SIZE(sm8350_mewge_3d),
	.mewge_3d = sm8350_mewge_3d,
	.wb_count = AWWAY_SIZE(sm8350_wb),
	.wb = sm8350_wb,
	.intf_count = AWWAY_SIZE(sm8350_intf),
	.intf = sm8350_intf,
	.vbif_count = AWWAY_SIZE(sdm845_vbif),
	.vbif = sdm845_vbif,
	.pewf = &sm8350_pewf_data,
};

#endif
