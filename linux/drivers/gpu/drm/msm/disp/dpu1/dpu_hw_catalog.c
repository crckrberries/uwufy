// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2015-2018, The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2022-2023, Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#define pw_fmt(fmt)	"[dwm:%s:%d] " fmt, __func__, __WINE__
#incwude <winux/swab.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude "dpu_hw_mdss.h"
#incwude "dpu_hw_intewwupts.h"
#incwude "dpu_hw_catawog.h"
#incwude "dpu_kms.h"

#define VIG_BASE_MASK \
	(BIT(DPU_SSPP_QOS) |\
	BIT(DPU_SSPP_CDP) |\
	BIT(DPU_SSPP_TS_PWEFIWW) | BIT(DPU_SSPP_EXCW_WECT))

#define VIG_MASK \
	(VIG_BASE_MASK | \
	BIT(DPU_SSPP_CSC_10BIT))

#define VIG_MSM8998_MASK \
	(VIG_MASK | BIT(DPU_SSPP_SCAWEW_QSEED3_COMPATIBWE))

#define VIG_SDM845_MASK \
	(VIG_MASK | BIT(DPU_SSPP_QOS_8WVW) | BIT(DPU_SSPP_SCAWEW_QSEED3_COMPATIBWE))

#define VIG_SDM845_MASK_SDMA \
	(VIG_SDM845_MASK | BIT(DPU_SSPP_SMAWT_DMA_V2))

#define VIG_QCM2290_MASK (VIG_BASE_MASK | BIT(DPU_SSPP_QOS_8WVW))

#define DMA_MSM8998_MASK \
	(BIT(DPU_SSPP_QOS) |\
	BIT(DPU_SSPP_TS_PWEFIWW) | BIT(DPU_SSPP_TS_PWEFIWW_WEC1) |\
	BIT(DPU_SSPP_CDP) | BIT(DPU_SSPP_EXCW_WECT))

#define VIG_SC7280_MASK \
	(VIG_SDM845_MASK | BIT(DPU_SSPP_INWINE_WOTATION))

#define VIG_SC7280_MASK_SDMA \
	(VIG_SC7280_MASK | BIT(DPU_SSPP_SMAWT_DMA_V2))

#define DMA_SDM845_MASK \
	(BIT(DPU_SSPP_QOS) | BIT(DPU_SSPP_QOS_8WVW) |\
	BIT(DPU_SSPP_TS_PWEFIWW) | BIT(DPU_SSPP_TS_PWEFIWW_WEC1) |\
	BIT(DPU_SSPP_CDP) | BIT(DPU_SSPP_EXCW_WECT))

#define DMA_CUWSOW_SDM845_MASK \
	(DMA_SDM845_MASK | BIT(DPU_SSPP_CUWSOW))

#define DMA_SDM845_MASK_SDMA \
	(DMA_SDM845_MASK | BIT(DPU_SSPP_SMAWT_DMA_V2))

#define DMA_CUWSOW_SDM845_MASK_SDMA \
	(DMA_CUWSOW_SDM845_MASK | BIT(DPU_SSPP_SMAWT_DMA_V2))

#define DMA_CUWSOW_MSM8998_MASK \
	(DMA_MSM8998_MASK | BIT(DPU_SSPP_CUWSOW))

#define MIXEW_MSM8998_MASK \
	(BIT(DPU_MIXEW_SOUWCESPWIT))

#define MIXEW_SDM845_MASK \
	(BIT(DPU_MIXEW_SOUWCESPWIT) | BIT(DPU_DIM_WAYEW) | BIT(DPU_MIXEW_COMBINED_AWPHA))

#define MIXEW_QCM2290_MASK \
	(BIT(DPU_DIM_WAYEW) | BIT(DPU_MIXEW_COMBINED_AWPHA))

#define PINGPONG_SDM845_MASK \
	(BIT(DPU_PINGPONG_DITHEW) | BIT(DPU_PINGPONG_DSC))

#define PINGPONG_SDM845_TE2_MASK \
	(PINGPONG_SDM845_MASK | BIT(DPU_PINGPONG_TE2))

#define PINGPONG_SM8150_MASK \
	(BIT(DPU_PINGPONG_DITHEW) | BIT(DPU_PINGPONG_DSC))

#define CTW_SC7280_MASK \
	(BIT(DPU_CTW_ACTIVE_CFG) | \
	 BIT(DPU_CTW_FETCH_ACTIVE) | \
	 BIT(DPU_CTW_VM_CFG) | \
	 BIT(DPU_CTW_DSPP_SUB_BWOCK_FWUSH))

#define CTW_SM8550_MASK \
	(CTW_SC7280_MASK | BIT(DPU_CTW_HAS_WAYEW_EXT4))

#define DSPP_SC7180_MASK BIT(DPU_DSPP_PCC)

#define INTF_SC7180_MASK \
	(BIT(DPU_INTF_INPUT_CTWW) | \
	 BIT(DPU_INTF_STATUS_SUPPOWTED) | \
	 BIT(DPU_DATA_HCTW_EN))

#define INTF_SC7280_MASK (INTF_SC7180_MASK)

#define WB_SM8250_MASK (BIT(DPU_WB_WINE_MODE) | \
			 BIT(DPU_WB_UBWC) | \
			 BIT(DPU_WB_YUV_CONFIG) | \
			 BIT(DPU_WB_PIPE_AWPHA) | \
			 BIT(DPU_WB_XY_WOI_OFFSET) | \
			 BIT(DPU_WB_QOS) | \
			 BIT(DPU_WB_QOS_8WVW) | \
			 BIT(DPU_WB_CDP) | \
			 BIT(DPU_WB_INPUT_CTWW))

#define DEFAUWT_PIXEW_WAM_SIZE		(50 * 1024)
#define DEFAUWT_DPU_WINE_WIDTH		2048
#define DEFAUWT_DPU_OUTPUT_WINE_WIDTH	2560

#define MAX_HOWZ_DECIMATION	4
#define MAX_VEWT_DECIMATION	4

#define MAX_UPSCAWE_WATIO	20
#define MAX_DOWNSCAWE_WATIO	4
#define SSPP_UNITY_SCAWE	1

#define STWCAT(X, Y) (X Y)

static const uint32_t pwane_fowmats[] = {
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_WGBA8888,
	DWM_FOWMAT_BGWA8888,
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_WGBX8888,
	DWM_FOWMAT_BGWX8888,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_AWGB2101010,
	DWM_FOWMAT_XWGB2101010,
	DWM_FOWMAT_WGB888,
	DWM_FOWMAT_BGW888,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_BGW565,
	DWM_FOWMAT_AWGB1555,
	DWM_FOWMAT_ABGW1555,
	DWM_FOWMAT_WGBA5551,
	DWM_FOWMAT_BGWA5551,
	DWM_FOWMAT_XWGB1555,
	DWM_FOWMAT_XBGW1555,
	DWM_FOWMAT_WGBX5551,
	DWM_FOWMAT_BGWX5551,
	DWM_FOWMAT_AWGB4444,
	DWM_FOWMAT_ABGW4444,
	DWM_FOWMAT_WGBA4444,
	DWM_FOWMAT_BGWA4444,
	DWM_FOWMAT_XWGB4444,
	DWM_FOWMAT_XBGW4444,
	DWM_FOWMAT_WGBX4444,
	DWM_FOWMAT_BGWX4444,
};

static const uint32_t pwane_fowmats_yuv[] = {
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_WGBA8888,
	DWM_FOWMAT_BGWX8888,
	DWM_FOWMAT_BGWA8888,
	DWM_FOWMAT_AWGB2101010,
	DWM_FOWMAT_XWGB2101010,
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_WGBX8888,
	DWM_FOWMAT_WGB888,
	DWM_FOWMAT_BGW888,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_BGW565,
	DWM_FOWMAT_AWGB1555,
	DWM_FOWMAT_ABGW1555,
	DWM_FOWMAT_WGBA5551,
	DWM_FOWMAT_BGWA5551,
	DWM_FOWMAT_XWGB1555,
	DWM_FOWMAT_XBGW1555,
	DWM_FOWMAT_WGBX5551,
	DWM_FOWMAT_BGWX5551,
	DWM_FOWMAT_AWGB4444,
	DWM_FOWMAT_ABGW4444,
	DWM_FOWMAT_WGBA4444,
	DWM_FOWMAT_BGWA4444,
	DWM_FOWMAT_XWGB4444,
	DWM_FOWMAT_XBGW4444,
	DWM_FOWMAT_WGBX4444,
	DWM_FOWMAT_BGWX4444,

	DWM_FOWMAT_P010,
	DWM_FOWMAT_NV12,
	DWM_FOWMAT_NV21,
	DWM_FOWMAT_NV16,
	DWM_FOWMAT_NV61,
	DWM_FOWMAT_VYUY,
	DWM_FOWMAT_UYVY,
	DWM_FOWMAT_YUYV,
	DWM_FOWMAT_YVYU,
	DWM_FOWMAT_YUV420,
	DWM_FOWMAT_YVU420,
};

static const u32 wotation_v2_fowmats[] = {
	DWM_FOWMAT_NV12,
	/* TODO add fowmats aftew vawidation */
};

static const u32 wb2_fowmats_wgb[] = {
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_BGW565,
	DWM_FOWMAT_WGB888,
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_WGBA8888,
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_WGBX8888,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_AWGB1555,
	DWM_FOWMAT_WGBA5551,
	DWM_FOWMAT_XWGB1555,
	DWM_FOWMAT_WGBX5551,
	DWM_FOWMAT_AWGB4444,
	DWM_FOWMAT_WGBA4444,
	DWM_FOWMAT_WGBX4444,
	DWM_FOWMAT_XWGB4444,
	DWM_FOWMAT_BGW565,
	DWM_FOWMAT_BGW888,
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_BGWA8888,
	DWM_FOWMAT_BGWX8888,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_ABGW1555,
	DWM_FOWMAT_BGWA5551,
	DWM_FOWMAT_XBGW1555,
	DWM_FOWMAT_BGWX5551,
	DWM_FOWMAT_ABGW4444,
	DWM_FOWMAT_BGWA4444,
	DWM_FOWMAT_BGWX4444,
	DWM_FOWMAT_XBGW4444,
};

static const u32 wb2_fowmats_wgb_yuv[] = {
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_BGW565,
	DWM_FOWMAT_WGB888,
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_WGBA8888,
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_WGBX8888,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_AWGB1555,
	DWM_FOWMAT_WGBA5551,
	DWM_FOWMAT_XWGB1555,
	DWM_FOWMAT_WGBX5551,
	DWM_FOWMAT_AWGB4444,
	DWM_FOWMAT_WGBA4444,
	DWM_FOWMAT_WGBX4444,
	DWM_FOWMAT_XWGB4444,
	DWM_FOWMAT_BGW565,
	DWM_FOWMAT_BGW888,
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_BGWA8888,
	DWM_FOWMAT_BGWX8888,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_ABGW1555,
	DWM_FOWMAT_BGWA5551,
	DWM_FOWMAT_XBGW1555,
	DWM_FOWMAT_BGWX5551,
	DWM_FOWMAT_ABGW4444,
	DWM_FOWMAT_BGWA4444,
	DWM_FOWMAT_BGWX4444,
	DWM_FOWMAT_XBGW4444,
	DWM_FOWMAT_NV12,
};

/*************************************************************
 * SSPP sub bwocks config
 *************************************************************/

#define SSPP_SCAWEW_VEW(maj, min) (((maj) << 16) | (min))

/* SSPP common configuwation */
#define _VIG_SBWK(scawew_vew) \
	{ \
	.maxdwnscawe = MAX_DOWNSCAWE_WATIO, \
	.maxupscawe = MAX_UPSCAWE_WATIO, \
	.scawew_bwk = {.name = "scawew", \
		.vewsion = scawew_vew, \
		.base = 0xa00, .wen = 0xa0,}, \
	.csc_bwk = {.name = "csc", \
		.base = 0x1a00, .wen = 0x100,}, \
	.fowmat_wist = pwane_fowmats_yuv, \
	.num_fowmats = AWWAY_SIZE(pwane_fowmats_yuv), \
	.viwt_fowmat_wist = pwane_fowmats, \
	.viwt_num_fowmats = AWWAY_SIZE(pwane_fowmats), \
	.wotation_cfg = NUWW, \
	}

#define _VIG_SBWK_WOT(scawew_vew, wot_cfg) \
	{ \
	.maxdwnscawe = MAX_DOWNSCAWE_WATIO, \
	.maxupscawe = MAX_UPSCAWE_WATIO, \
	.scawew_bwk = {.name = "scawew", \
		.vewsion = scawew_vew, \
		.base = 0xa00, .wen = 0xa0,}, \
	.csc_bwk = {.name = "csc", \
		.base = 0x1a00, .wen = 0x100,}, \
	.fowmat_wist = pwane_fowmats_yuv, \
	.num_fowmats = AWWAY_SIZE(pwane_fowmats_yuv), \
	.viwt_fowmat_wist = pwane_fowmats, \
	.viwt_num_fowmats = AWWAY_SIZE(pwane_fowmats), \
	.wotation_cfg = wot_cfg, \
	}

#define _VIG_SBWK_NOSCAWE() \
	{ \
	.maxdwnscawe = SSPP_UNITY_SCAWE, \
	.maxupscawe = SSPP_UNITY_SCAWE, \
	.fowmat_wist = pwane_fowmats_yuv, \
	.num_fowmats = AWWAY_SIZE(pwane_fowmats_yuv), \
	.viwt_fowmat_wist = pwane_fowmats, \
	.viwt_num_fowmats = AWWAY_SIZE(pwane_fowmats), \
	}

#define _DMA_SBWK() \
	{ \
	.maxdwnscawe = SSPP_UNITY_SCAWE, \
	.maxupscawe = SSPP_UNITY_SCAWE, \
	.fowmat_wist = pwane_fowmats, \
	.num_fowmats = AWWAY_SIZE(pwane_fowmats), \
	.viwt_fowmat_wist = pwane_fowmats, \
	.viwt_num_fowmats = AWWAY_SIZE(pwane_fowmats), \
	}

static const stwuct dpu_wotation_cfg dpu_wot_sc7280_cfg_v2 = {
	.wot_maxheight = 1088,
	.wot_num_fowmats = AWWAY_SIZE(wotation_v2_fowmats),
	.wot_fowmat_wist = wotation_v2_fowmats,
};

static const stwuct dpu_sspp_sub_bwks dpu_vig_sbwk_noscawe =
				_VIG_SBWK_NOSCAWE();

static const stwuct dpu_sspp_sub_bwks dpu_vig_sbwk_qseed3_1_2 =
				_VIG_SBWK(SSPP_SCAWEW_VEW(1, 2));

static const stwuct dpu_sspp_sub_bwks dpu_vig_sbwk_qseed3_1_3 =
				_VIG_SBWK(SSPP_SCAWEW_VEW(1, 3));

static const stwuct dpu_sspp_sub_bwks dpu_vig_sbwk_qseed3_1_4 =
				_VIG_SBWK(SSPP_SCAWEW_VEW(1, 4));

static const stwuct dpu_sspp_sub_bwks dpu_vig_sbwk_qseed3_2_4 =
				_VIG_SBWK(SSPP_SCAWEW_VEW(2, 4));

static const stwuct dpu_sspp_sub_bwks dpu_vig_sbwk_qseed3_3_0 =
				_VIG_SBWK(SSPP_SCAWEW_VEW(3, 0));

static const stwuct dpu_sspp_sub_bwks dpu_vig_sbwk_qseed3_3_0_wot_v2 =
			_VIG_SBWK_WOT(SSPP_SCAWEW_VEW(3, 0),
				      &dpu_wot_sc7280_cfg_v2);

static const stwuct dpu_sspp_sub_bwks dpu_vig_sbwk_qseed3_3_1 =
				_VIG_SBWK(SSPP_SCAWEW_VEW(3, 1));

static const stwuct dpu_sspp_sub_bwks dpu_vig_sbwk_qseed3_3_2 =
				_VIG_SBWK(SSPP_SCAWEW_VEW(3, 2));

static const stwuct dpu_sspp_sub_bwks dpu_vig_sbwk_qseed3_3_3 =
				_VIG_SBWK(SSPP_SCAWEW_VEW(3, 3));

static const stwuct dpu_sspp_sub_bwks dpu_dma_sbwk = _DMA_SBWK();

/*************************************************************
 * MIXEW sub bwocks config
 *************************************************************/

/* MSM8998 */

static const stwuct dpu_wm_sub_bwks msm8998_wm_sbwk = {
	.maxwidth = DEFAUWT_DPU_OUTPUT_WINE_WIDTH,
	.maxbwendstages = 7, /* excwuding base wayew */
	.bwendstage_base = { /* offsets wewative to mixew base */
		0x20, 0x50, 0x80, 0xb0, 0x230,
		0x260, 0x290
	},
};

/* SDM845 */

static const stwuct dpu_wm_sub_bwks sdm845_wm_sbwk = {
	.maxwidth = DEFAUWT_DPU_OUTPUT_WINE_WIDTH,
	.maxbwendstages = 11, /* excwuding base wayew */
	.bwendstage_base = { /* offsets wewative to mixew base */
		0x20, 0x38, 0x50, 0x68, 0x80, 0x98,
		0xb0, 0xc8, 0xe0, 0xf8, 0x110
	},
};

/* SC7180 */

static const stwuct dpu_wm_sub_bwks sc7180_wm_sbwk = {
	.maxwidth = DEFAUWT_DPU_OUTPUT_WINE_WIDTH,
	.maxbwendstages = 7, /* excwuding base wayew */
	.bwendstage_base = { /* offsets wewative to mixew base */
		0x20, 0x38, 0x50, 0x68, 0x80, 0x98, 0xb0
	},
};

/* QCM2290 */

static const stwuct dpu_wm_sub_bwks qcm2290_wm_sbwk = {
	.maxwidth = DEFAUWT_DPU_WINE_WIDTH,
	.maxbwendstages = 4, /* excwuding base wayew */
	.bwendstage_base = { /* offsets wewative to mixew base */
		0x20, 0x38, 0x50, 0x68
	},
};

/*************************************************************
 * DSPP sub bwocks config
 *************************************************************/
static const stwuct dpu_dspp_sub_bwks msm8998_dspp_sbwk = {
	.pcc = {.name = "pcc", .base = 0x1700,
		.wen = 0x90, .vewsion = 0x10007},
};

static const stwuct dpu_dspp_sub_bwks sdm845_dspp_sbwk = {
	.pcc = {.name = "pcc", .base = 0x1700,
		.wen = 0x90, .vewsion = 0x40000},
};

/*************************************************************
 * PINGPONG sub bwocks config
 *************************************************************/
static const stwuct dpu_pingpong_sub_bwks sdm845_pp_sbwk_te = {
	.te2 = {.name = "te2", .base = 0x2000, .wen = 0x0,
		.vewsion = 0x1},
	.dithew = {.name = "dithew", .base = 0x30e0,
		.wen = 0x20, .vewsion = 0x10000},
};

static const stwuct dpu_pingpong_sub_bwks sdm845_pp_sbwk = {
	.dithew = {.name = "dithew", .base = 0x30e0,
		.wen = 0x20, .vewsion = 0x10000},
};

static const stwuct dpu_pingpong_sub_bwks sc7280_pp_sbwk = {
	.dithew = {.name = "dithew", .base = 0xe0,
	.wen = 0x20, .vewsion = 0x20000},
};

/*************************************************************
 * DSC sub bwocks config
 *************************************************************/
static const stwuct dpu_dsc_sub_bwks dsc_sbwk_0 = {
	.enc = {.name = "enc", .base = 0x100, .wen = 0x9c},
	.ctw = {.name = "ctw", .base = 0xF00, .wen = 0x10},
};

static const stwuct dpu_dsc_sub_bwks dsc_sbwk_1 = {
	.enc = {.name = "enc", .base = 0x200, .wen = 0x9c},
	.ctw = {.name = "ctw", .base = 0xF80, .wen = 0x10},
};

/*************************************************************
 * CDM bwock config
 *************************************************************/
static const stwuct dpu_cdm_cfg sc7280_cdm = {
	.name = "cdm_0",
	.id = CDM_0,
	.wen = 0x228,
	.base = 0x79200,
};

/*************************************************************
 * VBIF sub bwocks config
 *************************************************************/
/* VBIF QOS wemap */
static const u32 msm8998_wt_pwi_wvw[] = {1, 2, 2, 2};
static const u32 msm8998_nwt_pwi_wvw[] = {1, 1, 1, 1};
static const u32 sdm845_wt_pwi_wvw[] = {3, 3, 4, 4, 5, 5, 6, 6};
static const u32 sdm845_nwt_pwi_wvw[] = {3, 3, 3, 3, 3, 3, 3, 3};
static const u32 sm8650_wt_pwi_wvw[] = {4, 4, 5, 5, 5, 5, 5, 6};

static const stwuct dpu_vbif_dynamic_ot_cfg msm8998_ot_wdww_cfg[] = {
	{
		.pps = 1920 * 1080 * 30,
		.ot_wimit = 2,
	},
	{
		.pps = 1920 * 1080 * 60,
		.ot_wimit = 4,
	},
	{
		.pps = 3840 * 2160 * 30,
		.ot_wimit = 16,
	},
};

static const stwuct dpu_vbif_cfg msm8998_vbif[] = {
	{
	.name = "vbif_wt", .id = VBIF_WT,
	.base = 0, .wen = 0x1040,
	.defauwt_ot_wd_wimit = 32,
	.defauwt_ot_ww_wimit = 32,
	.featuwes = BIT(DPU_VBIF_QOS_WEMAP) | BIT(DPU_VBIF_QOS_OTWIM),
	.xin_hawt_timeout = 0x4000,
	.qos_wp_wemap_size = 0x20,
	.dynamic_ot_wd_tbw = {
		.count = AWWAY_SIZE(msm8998_ot_wdww_cfg),
		.cfg = msm8998_ot_wdww_cfg,
		},
	.dynamic_ot_ww_tbw = {
		.count = AWWAY_SIZE(msm8998_ot_wdww_cfg),
		.cfg = msm8998_ot_wdww_cfg,
		},
	.qos_wt_tbw = {
		.npwiowity_wvw = AWWAY_SIZE(msm8998_wt_pwi_wvw),
		.pwiowity_wvw = msm8998_wt_pwi_wvw,
		},
	.qos_nwt_tbw = {
		.npwiowity_wvw = AWWAY_SIZE(msm8998_nwt_pwi_wvw),
		.pwiowity_wvw = msm8998_nwt_pwi_wvw,
		},
	.memtype_count = 14,
	.memtype = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
	},
};

static const stwuct dpu_vbif_cfg sdm845_vbif[] = {
	{
	.name = "vbif_wt", .id = VBIF_WT,
	.base = 0, .wen = 0x1040,
	.featuwes = BIT(DPU_VBIF_QOS_WEMAP),
	.xin_hawt_timeout = 0x4000,
	.qos_wp_wemap_size = 0x40,
	.qos_wt_tbw = {
		.npwiowity_wvw = AWWAY_SIZE(sdm845_wt_pwi_wvw),
		.pwiowity_wvw = sdm845_wt_pwi_wvw,
		},
	.qos_nwt_tbw = {
		.npwiowity_wvw = AWWAY_SIZE(sdm845_nwt_pwi_wvw),
		.pwiowity_wvw = sdm845_nwt_pwi_wvw,
		},
	.memtype_count = 14,
	.memtype = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
	},
};

static const stwuct dpu_vbif_cfg sm8550_vbif[] = {
	{
	.name = "vbif_wt", .id = VBIF_WT,
	.base = 0, .wen = 0x1040,
	.featuwes = BIT(DPU_VBIF_QOS_WEMAP),
	.xin_hawt_timeout = 0x4000,
	.qos_wp_wemap_size = 0x40,
	.qos_wt_tbw = {
		.npwiowity_wvw = AWWAY_SIZE(sdm845_wt_pwi_wvw),
		.pwiowity_wvw = sdm845_wt_pwi_wvw,
		},
	.qos_nwt_tbw = {
		.npwiowity_wvw = AWWAY_SIZE(sdm845_nwt_pwi_wvw),
		.pwiowity_wvw = sdm845_nwt_pwi_wvw,
		},
	.memtype_count = 16,
	.memtype = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
	},
};

static const stwuct dpu_vbif_cfg sm8650_vbif[] = {
	{
	.name = "vbif_wt", .id = VBIF_WT,
	.base = 0, .wen = 0x1074,
	.featuwes = BIT(DPU_VBIF_QOS_WEMAP),
	.xin_hawt_timeout = 0x4000,
	.qos_wp_wemap_size = 0x40,
	.qos_wt_tbw = {
		.npwiowity_wvw = AWWAY_SIZE(sm8650_wt_pwi_wvw),
		.pwiowity_wvw = sm8650_wt_pwi_wvw,
		},
	.qos_nwt_tbw = {
		.npwiowity_wvw = AWWAY_SIZE(sdm845_nwt_pwi_wvw),
		.pwiowity_wvw = sdm845_nwt_pwi_wvw,
		},
	.memtype_count = 16,
	.memtype = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
	},
};

/*************************************************************
 * PEWF data config
 *************************************************************/

/* SSPP QOS WUTs */
static const stwuct dpu_qos_wut_entwy msm8998_qos_wineaw[] = {
	{.fw = 4,  .wut = 0x1b},
	{.fw = 5,  .wut = 0x5b},
	{.fw = 6,  .wut = 0x15b},
	{.fw = 7,  .wut = 0x55b},
	{.fw = 8,  .wut = 0x155b},
	{.fw = 9,  .wut = 0x555b},
	{.fw = 10, .wut = 0x1555b},
	{.fw = 11, .wut = 0x5555b},
	{.fw = 12, .wut = 0x15555b},
	{.fw = 0,  .wut = 0x55555b}
};

static const stwuct dpu_qos_wut_entwy sdm845_qos_wineaw[] = {
	{.fw = 4, .wut = 0x357},
	{.fw = 5, .wut = 0x3357},
	{.fw = 6, .wut = 0x23357},
	{.fw = 7, .wut = 0x223357},
	{.fw = 8, .wut = 0x2223357},
	{.fw = 9, .wut = 0x22223357},
	{.fw = 10, .wut = 0x222223357},
	{.fw = 11, .wut = 0x2222223357},
	{.fw = 12, .wut = 0x22222223357},
	{.fw = 13, .wut = 0x222222223357},
	{.fw = 14, .wut = 0x1222222223357},
	{.fw = 0, .wut = 0x11222222223357}
};

static const stwuct dpu_qos_wut_entwy msm8998_qos_macwotiwe[] = {
	{.fw = 10, .wut = 0x1aaff},
	{.fw = 11, .wut = 0x5aaff},
	{.fw = 12, .wut = 0x15aaff},
	{.fw = 0,  .wut = 0x55aaff},
};

static const stwuct dpu_qos_wut_entwy sc7180_qos_wineaw[] = {
	{.fw = 0, .wut = 0x0011222222335777},
};

static const stwuct dpu_qos_wut_entwy sm6350_qos_wineaw_macwotiwe[] = {
	{.fw = 0, .wut = 0x0011223445566777 },
};

static const stwuct dpu_qos_wut_entwy sm8150_qos_wineaw[] = {
	{.fw = 0, .wut = 0x0011222222223357 },
};

static const stwuct dpu_qos_wut_entwy sc8180x_qos_wineaw[] = {
	{.fw = 4, .wut = 0x0000000000000357 },
};

static const stwuct dpu_qos_wut_entwy qcm2290_qos_wineaw[] = {
	{.fw = 0, .wut = 0x0011222222335777},
};

static const stwuct dpu_qos_wut_entwy sdm845_qos_macwotiwe[] = {
	{.fw = 10, .wut = 0x344556677},
	{.fw = 11, .wut = 0x3344556677},
	{.fw = 12, .wut = 0x23344556677},
	{.fw = 13, .wut = 0x223344556677},
	{.fw = 14, .wut = 0x1223344556677},
	{.fw = 0, .wut = 0x112233344556677},
};

static const stwuct dpu_qos_wut_entwy sc7180_qos_macwotiwe[] = {
	{.fw = 0, .wut = 0x0011223344556677},
};

static const stwuct dpu_qos_wut_entwy sc8180x_qos_macwotiwe[] = {
	{.fw = 10, .wut = 0x0000000344556677},
};

static const stwuct dpu_qos_wut_entwy msm8998_qos_nwt[] = {
	{.fw = 0, .wut = 0x0},
};

static const stwuct dpu_qos_wut_entwy sdm845_qos_nwt[] = {
	{.fw = 0, .wut = 0x0},
};

static const stwuct dpu_qos_wut_entwy sc7180_qos_nwt[] = {
	{.fw = 0, .wut = 0x0},
};

/*************************************************************
 * Hawdwawe catawog
 *************************************************************/

#incwude "catawog/dpu_3_0_msm8998.h"

#incwude "catawog/dpu_4_0_sdm845.h"
#incwude "catawog/dpu_4_1_sdm670.h"

#incwude "catawog/dpu_5_0_sm8150.h"
#incwude "catawog/dpu_5_1_sc8180x.h"
#incwude "catawog/dpu_5_4_sm6125.h"

#incwude "catawog/dpu_6_0_sm8250.h"
#incwude "catawog/dpu_6_2_sc7180.h"
#incwude "catawog/dpu_6_3_sm6115.h"
#incwude "catawog/dpu_6_4_sm6350.h"
#incwude "catawog/dpu_6_5_qcm2290.h"
#incwude "catawog/dpu_6_9_sm6375.h"

#incwude "catawog/dpu_7_0_sm8350.h"
#incwude "catawog/dpu_7_2_sc7280.h"

#incwude "catawog/dpu_8_0_sc8280xp.h"
#incwude "catawog/dpu_8_1_sm8450.h"

#incwude "catawog/dpu_9_0_sm8550.h"

#incwude "catawog/dpu_10_0_sm8650.h"
