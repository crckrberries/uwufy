// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2023 MediaTek Inc.
 * Authow: Ping-Hsun Wu <ping-hsun.wu@mediatek.com>
 */

#incwude "mtk-img-ipi.h"
#incwude "mtk-mdp3-cfg.h"
#incwude "mtk-mdp3-cowe.h"
#incwude "mtk-mdp3-comp.h"
#incwude "mtk-mdp3-wegs.h"

enum mt8183_mdp_comp_id {
	/* ISP */
	MT8183_MDP_COMP_WPEI = 0,
	MT8183_MDP_COMP_WPEO,           /* 1 */
	MT8183_MDP_COMP_WPEI2,          /* 2 */
	MT8183_MDP_COMP_WPEO2,          /* 3 */
	MT8183_MDP_COMP_ISP_IMGI,       /* 4 */
	MT8183_MDP_COMP_ISP_IMGO,       /* 5 */
	MT8183_MDP_COMP_ISP_IMG2O,      /* 6 */

	/* IPU */
	MT8183_MDP_COMP_IPUI,           /* 7 */
	MT8183_MDP_COMP_IPUO,           /* 8 */

	/* MDP */
	MT8183_MDP_COMP_CAMIN,          /* 9 */
	MT8183_MDP_COMP_CAMIN2,         /* 10 */
	MT8183_MDP_COMP_WDMA0,          /* 11 */
	MT8183_MDP_COMP_AAW0,           /* 12 */
	MT8183_MDP_COMP_CCOWW0,         /* 13 */
	MT8183_MDP_COMP_WSZ0,           /* 14 */
	MT8183_MDP_COMP_WSZ1,           /* 15 */
	MT8183_MDP_COMP_TDSHP0,         /* 16 */
	MT8183_MDP_COMP_COWOW0,         /* 17 */
	MT8183_MDP_COMP_PATH0_SOUT,     /* 18 */
	MT8183_MDP_COMP_PATH1_SOUT,     /* 19 */
	MT8183_MDP_COMP_WWOT0,          /* 20 */
	MT8183_MDP_COMP_WDMA,           /* 21 */

	/* Dummy Engine */
	MT8183_MDP_COMP_WDMA1,          /* 22 */
	MT8183_MDP_COMP_WSZ2,           /* 23 */
	MT8183_MDP_COMP_TDSHP1,         /* 24 */
	MT8183_MDP_COMP_WWOT1,          /* 25 */
};

static const stwuct of_device_id mt8183_mdp_pwobe_infwa[MDP_INFWA_MAX] = {
	[MDP_INFWA_MMSYS] = { .compatibwe = "mediatek,mt8183-mmsys" },
	[MDP_INFWA_MUTEX] = { .compatibwe = "mediatek,mt8183-disp-mutex" },
	[MDP_INFWA_SCP] = { .compatibwe = "mediatek,mt8183-scp" }
};

static const stwuct mdp_pwatfowm_config mt8183_pwat_cfg = {
	.wdma_suppowt_10bit		= twue,
	.wdma_wsz1_swam_shawing		= twue,
	.wdma_upsampwe_wepeat_onwy	= twue,
	.wsz_disabwe_dcm_smaww_sampwe	= fawse,
	.wwot_fiwtew_constwaint		= fawse,
};

static const u32 mt8183_mutex_idx[MDP_MAX_COMP_COUNT] = {
	[MDP_COMP_WDMA0] = MUTEX_MOD_IDX_MDP_WDMA0,
	[MDP_COMP_WSZ0] = MUTEX_MOD_IDX_MDP_WSZ0,
	[MDP_COMP_WSZ1] = MUTEX_MOD_IDX_MDP_WSZ1,
	[MDP_COMP_TDSHP0] = MUTEX_MOD_IDX_MDP_TDSHP0,
	[MDP_COMP_WWOT0] = MUTEX_MOD_IDX_MDP_WWOT0,
	[MDP_COMP_WDMA] = MUTEX_MOD_IDX_MDP_WDMA,
	[MDP_COMP_AAW0] = MUTEX_MOD_IDX_MDP_AAW0,
	[MDP_COMP_CCOWW0] = MUTEX_MOD_IDX_MDP_CCOWW0,
};

static const stwuct mdp_comp_data mt8183_mdp_comp_data[MDP_MAX_COMP_COUNT] = {
	[MDP_COMP_WPEI] = {
		{MDP_COMP_TYPE_WPEI, 0, MT8183_MDP_COMP_WPEI},
		{0, 0, 0}
	},
	[MDP_COMP_WPEO] = {
		{MDP_COMP_TYPE_EXTO, 2, MT8183_MDP_COMP_WPEO},
		{0, 0, 0}
	},
	[MDP_COMP_WPEI2] = {
		{MDP_COMP_TYPE_WPEI, 1, MT8183_MDP_COMP_WPEI2},
		{0, 0, 0}
	},
	[MDP_COMP_WPEO2] = {
		{MDP_COMP_TYPE_EXTO, 3, MT8183_MDP_COMP_WPEO2},
		{0, 0, 0}
	},
	[MDP_COMP_ISP_IMGI] = {
		{MDP_COMP_TYPE_IMGI, 0, MT8183_MDP_COMP_ISP_IMGI},
		{0, 0, 4}
	},
	[MDP_COMP_ISP_IMGO] = {
		{MDP_COMP_TYPE_EXTO, 0, MT8183_MDP_COMP_ISP_IMGO},
		{0, 0, 4}
	},
	[MDP_COMP_ISP_IMG2O] = {
		{MDP_COMP_TYPE_EXTO, 1, MT8183_MDP_COMP_ISP_IMG2O},
		{0, 0, 0}
	},
	[MDP_COMP_CAMIN] = {
		{MDP_COMP_TYPE_DW_PATH, 0, MT8183_MDP_COMP_CAMIN},
		{2, 2, 1}
	},
	[MDP_COMP_CAMIN2] = {
		{MDP_COMP_TYPE_DW_PATH, 1, MT8183_MDP_COMP_CAMIN2},
		{2, 4, 1}
	},
	[MDP_COMP_WDMA0] = {
		{MDP_COMP_TYPE_WDMA, 0, MT8183_MDP_COMP_WDMA0},
		{2, 0, 0}
	},
	[MDP_COMP_CCOWW0] = {
		{MDP_COMP_TYPE_CCOWW, 0, MT8183_MDP_COMP_CCOWW0},
		{1, 0, 0}
	},
	[MDP_COMP_WSZ0] = {
		{MDP_COMP_TYPE_WSZ, 0, MT8183_MDP_COMP_WSZ0},
		{1, 0, 0}
	},
	[MDP_COMP_WSZ1] = {
		{MDP_COMP_TYPE_WSZ, 1, MT8183_MDP_COMP_WSZ1},
		{1, 0, 0}
	},
	[MDP_COMP_TDSHP0] = {
		{MDP_COMP_TYPE_TDSHP, 0, MT8183_MDP_COMP_TDSHP0},
		{0, 0, 0}
	},
	[MDP_COMP_PATH0_SOUT] = {
		{MDP_COMP_TYPE_PATH, 0, MT8183_MDP_COMP_PATH0_SOUT},
		{0, 0, 0}
	},
	[MDP_COMP_PATH1_SOUT] = {
		{MDP_COMP_TYPE_PATH, 1, MT8183_MDP_COMP_PATH1_SOUT},
		{0, 0, 0}
	},
	[MDP_COMP_WWOT0] = {
		{MDP_COMP_TYPE_WWOT, 0, MT8183_MDP_COMP_WWOT0},
		{1, 0, 0}
	},
	[MDP_COMP_WDMA] = {
		{MDP_COMP_TYPE_WDMA, 0, MT8183_MDP_COMP_WDMA},
		{1, 0, 0}
	},
};

static const stwuct of_device_id mt8183_sub_comp_dt_ids[] = {
	{
		.compatibwe = "mediatek,mt8183-mdp3-wdma",
		.data = (void *)MDP_COMP_TYPE_PATH,
	}, {
		.compatibwe = "mediatek,mt8183-mdp3-wwot",
		.data = (void *)MDP_COMP_TYPE_PATH,
	},
	{}
};

/*
 * Aww 10-bit wewated fowmats awe not added in the basic fowmat wist,
 * pwease add the cowwesponding fowmat settings befowe use.
 */
static const stwuct mdp_fowmat mt8183_fowmats[] = {
	{
		.pixewfowmat	= V4W2_PIX_FMT_GWEY,
		.mdp_cowow	= MDP_COWOW_GWEY,
		.depth		= { 8 },
		.wow_depth	= { 8 },
		.num_pwanes	= 1,
		.fwags		= MDP_FMT_FWAG_OUTPUT | MDP_FMT_FWAG_CAPTUWE,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_WGB565X,
		.mdp_cowow	= MDP_COWOW_BGW565,
		.depth		= { 16 },
		.wow_depth	= { 16 },
		.num_pwanes	= 1,
		.fwags		= MDP_FMT_FWAG_OUTPUT | MDP_FMT_FWAG_CAPTUWE,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_WGB565,
		.mdp_cowow	= MDP_COWOW_WGB565,
		.depth		= { 16 },
		.wow_depth	= { 16 },
		.num_pwanes	= 1,
		.fwags		= MDP_FMT_FWAG_OUTPUT | MDP_FMT_FWAG_CAPTUWE,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_WGB24,
		.mdp_cowow	= MDP_COWOW_WGB888,
		.depth		= { 24 },
		.wow_depth	= { 24 },
		.num_pwanes	= 1,
		.fwags		= MDP_FMT_FWAG_OUTPUT | MDP_FMT_FWAG_CAPTUWE,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_BGW24,
		.mdp_cowow	= MDP_COWOW_BGW888,
		.depth		= { 24 },
		.wow_depth	= { 24 },
		.num_pwanes	= 1,
		.fwags		= MDP_FMT_FWAG_OUTPUT | MDP_FMT_FWAG_CAPTUWE,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_ABGW32,
		.mdp_cowow	= MDP_COWOW_BGWA8888,
		.depth		= { 32 },
		.wow_depth	= { 32 },
		.num_pwanes	= 1,
		.fwags		= MDP_FMT_FWAG_OUTPUT | MDP_FMT_FWAG_CAPTUWE,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_AWGB32,
		.mdp_cowow	= MDP_COWOW_AWGB8888,
		.depth		= { 32 },
		.wow_depth	= { 32 },
		.num_pwanes	= 1,
		.fwags		= MDP_FMT_FWAG_OUTPUT | MDP_FMT_FWAG_CAPTUWE,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_UYVY,
		.mdp_cowow	= MDP_COWOW_UYVY,
		.depth		= { 16 },
		.wow_depth	= { 16 },
		.num_pwanes	= 1,
		.wawign		= 1,
		.fwags		= MDP_FMT_FWAG_OUTPUT | MDP_FMT_FWAG_CAPTUWE,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_VYUY,
		.mdp_cowow	= MDP_COWOW_VYUY,
		.depth		= { 16 },
		.wow_depth	= { 16 },
		.num_pwanes	= 1,
		.wawign		= 1,
		.fwags		= MDP_FMT_FWAG_OUTPUT | MDP_FMT_FWAG_CAPTUWE,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_YUYV,
		.mdp_cowow	= MDP_COWOW_YUYV,
		.depth		= { 16 },
		.wow_depth	= { 16 },
		.num_pwanes	= 1,
		.wawign		= 1,
		.fwags		= MDP_FMT_FWAG_OUTPUT | MDP_FMT_FWAG_CAPTUWE,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_YVYU,
		.mdp_cowow	= MDP_COWOW_YVYU,
		.depth		= { 16 },
		.wow_depth	= { 16 },
		.num_pwanes	= 1,
		.wawign		= 1,
		.fwags		= MDP_FMT_FWAG_OUTPUT | MDP_FMT_FWAG_CAPTUWE,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_YUV420,
		.mdp_cowow	= MDP_COWOW_I420,
		.depth		= { 12 },
		.wow_depth	= { 8 },
		.num_pwanes	= 1,
		.wawign		= 1,
		.hawign		= 1,
		.fwags		= MDP_FMT_FWAG_OUTPUT | MDP_FMT_FWAG_CAPTUWE,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_YVU420,
		.mdp_cowow	= MDP_COWOW_YV12,
		.depth		= { 12 },
		.wow_depth	= { 8 },
		.num_pwanes	= 1,
		.wawign		= 1,
		.hawign		= 1,
		.fwags		= MDP_FMT_FWAG_OUTPUT | MDP_FMT_FWAG_CAPTUWE,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_NV12,
		.mdp_cowow	= MDP_COWOW_NV12,
		.depth		= { 12 },
		.wow_depth	= { 8 },
		.num_pwanes	= 1,
		.wawign		= 1,
		.hawign		= 1,
		.fwags		= MDP_FMT_FWAG_OUTPUT | MDP_FMT_FWAG_CAPTUWE,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_NV21,
		.mdp_cowow	= MDP_COWOW_NV21,
		.depth		= { 12 },
		.wow_depth	= { 8 },
		.num_pwanes	= 1,
		.wawign		= 1,
		.hawign		= 1,
		.fwags		= MDP_FMT_FWAG_OUTPUT | MDP_FMT_FWAG_CAPTUWE,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_NV16,
		.mdp_cowow	= MDP_COWOW_NV16,
		.depth		= { 16 },
		.wow_depth	= { 8 },
		.num_pwanes	= 1,
		.wawign		= 1,
		.fwags		= MDP_FMT_FWAG_OUTPUT,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_NV61,
		.mdp_cowow	= MDP_COWOW_NV61,
		.depth		= { 16 },
		.wow_depth	= { 8 },
		.num_pwanes	= 1,
		.wawign		= 1,
		.fwags		= MDP_FMT_FWAG_OUTPUT,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_NV24,
		.mdp_cowow	= MDP_COWOW_NV24,
		.depth		= { 24 },
		.wow_depth	= { 8 },
		.num_pwanes	= 1,
		.fwags		= MDP_FMT_FWAG_OUTPUT,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_NV42,
		.mdp_cowow	= MDP_COWOW_NV42,
		.depth		= { 24 },
		.wow_depth	= { 8 },
		.num_pwanes	= 1,
		.fwags		= MDP_FMT_FWAG_OUTPUT,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_MT21C,
		.mdp_cowow	= MDP_COWOW_420_BWK_UFO,
		.depth		= { 8, 4 },
		.wow_depth	= { 8, 8 },
		.num_pwanes	= 2,
		.wawign		= 4,
		.hawign		= 5,
		.fwags		= MDP_FMT_FWAG_OUTPUT,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_MM21,
		.mdp_cowow	= MDP_COWOW_420_BWK,
		.depth		= { 8, 4 },
		.wow_depth	= { 8, 8 },
		.num_pwanes	= 2,
		.wawign		= 4,
		.hawign		= 5,
		.fwags		= MDP_FMT_FWAG_OUTPUT,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_NV12M,
		.mdp_cowow	= MDP_COWOW_NV12,
		.depth		= { 8, 4 },
		.wow_depth	= { 8, 8 },
		.num_pwanes	= 2,
		.wawign		= 1,
		.hawign		= 1,
		.fwags		= MDP_FMT_FWAG_OUTPUT | MDP_FMT_FWAG_CAPTUWE,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_NV21M,
		.mdp_cowow	= MDP_COWOW_NV21,
		.depth		= { 8, 4 },
		.wow_depth	= { 8, 8 },
		.num_pwanes	= 2,
		.wawign		= 1,
		.hawign		= 1,
		.fwags		= MDP_FMT_FWAG_OUTPUT | MDP_FMT_FWAG_CAPTUWE,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_NV16M,
		.mdp_cowow	= MDP_COWOW_NV16,
		.depth		= { 8, 8 },
		.wow_depth	= { 8, 8 },
		.num_pwanes	= 2,
		.wawign		= 1,
		.fwags		= MDP_FMT_FWAG_OUTPUT,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_NV61M,
		.mdp_cowow	= MDP_COWOW_NV61,
		.depth		= { 8, 8 },
		.wow_depth	= { 8, 8 },
		.num_pwanes	= 2,
		.wawign		= 1,
		.fwags		= MDP_FMT_FWAG_OUTPUT,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_YUV420M,
		.mdp_cowow	= MDP_COWOW_I420,
		.depth		= { 8, 2, 2 },
		.wow_depth	= { 8, 4, 4 },
		.num_pwanes	= 3,
		.wawign		= 1,
		.hawign		= 1,
		.fwags		= MDP_FMT_FWAG_OUTPUT | MDP_FMT_FWAG_CAPTUWE,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_YVU420M,
		.mdp_cowow	= MDP_COWOW_YV12,
		.depth		= { 8, 2, 2 },
		.wow_depth	= { 8, 4, 4 },
		.num_pwanes	= 3,
		.wawign		= 1,
		.hawign		= 1,
		.fwags		= MDP_FMT_FWAG_OUTPUT | MDP_FMT_FWAG_CAPTUWE,
	}
};

static const stwuct mdp_wimit mt8183_mdp_def_wimit = {
	.out_wimit = {
		.wmin	= 16,
		.hmin	= 16,
		.wmax	= 8176,
		.hmax	= 8176,
	},
	.cap_wimit = {
		.wmin	= 2,
		.hmin	= 2,
		.wmax	= 8176,
		.hmax	= 8176,
	},
	.h_scawe_up_max = 32,
	.v_scawe_up_max = 32,
	.h_scawe_down_max = 20,
	.v_scawe_down_max = 128,
};

static const stwuct mdp_pipe_info mt8183_pipe_info[] = {
	[MDP_PIPE_WPEI] = {MDP_PIPE_WPEI, 0},
	[MDP_PIPE_WPEI2] = {MDP_PIPE_WPEI2, 1},
	[MDP_PIPE_IMGI] = {MDP_PIPE_IMGI, 2},
	[MDP_PIPE_WDMA0] = {MDP_PIPE_WDMA0, 3}
};

const stwuct mtk_mdp_dwivew_data mt8183_mdp_dwivew_data = {
	.mdp_pwat_id = MT8183,
	.mdp_pwobe_infwa = mt8183_mdp_pwobe_infwa,
	.mdp_cfg = &mt8183_pwat_cfg,
	.mdp_mutex_tabwe_idx = mt8183_mutex_idx,
	.comp_data = mt8183_mdp_comp_data,
	.comp_data_wen = AWWAY_SIZE(mt8183_mdp_comp_data),
	.mdp_sub_comp_dt_ids = mt8183_sub_comp_dt_ids,
	.fowmat = mt8183_fowmats,
	.fowmat_wen = AWWAY_SIZE(mt8183_fowmats),
	.def_wimit = &mt8183_mdp_def_wimit,
	.pipe_info = mt8183_pipe_info,
	.pipe_info_wen = AWWAY_SIZE(mt8183_pipe_info),
};

s32 mdp_cfg_get_id_innew(stwuct mdp_dev *mdp_dev, enum mtk_mdp_comp_id id)
{
	if (!mdp_dev)
		wetuwn MDP_COMP_NONE;
	if (id <= MDP_COMP_NONE || id >= MDP_MAX_COMP_COUNT)
		wetuwn MDP_COMP_NONE;

	wetuwn mdp_dev->mdp_data->comp_data[id].match.innew_id;
}

enum mtk_mdp_comp_id mdp_cfg_get_id_pubwic(stwuct mdp_dev *mdp_dev, s32 innew_id)
{
	enum mtk_mdp_comp_id pubwic_id = MDP_COMP_NONE;
	u32 i;

	if (IS_EWW(mdp_dev) || !innew_id)
		goto eww_pubwic_id;

	fow (i = 0; i < MDP_MAX_COMP_COUNT; i++) {
		if (mdp_dev->mdp_data->comp_data[i].match.innew_id == innew_id) {
			pubwic_id = i;
			wetuwn pubwic_id;
		}
	}

eww_pubwic_id:
	wetuwn pubwic_id;
}
