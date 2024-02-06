// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2018 BayWibwe, SAS
 * Authow: Maxime Jouwdan <mjouwdan@baywibwe.com>
 */

#incwude "vdec_pwatfowm.h"
#incwude "vdec.h"

#incwude "vdec_1.h"
#incwude "vdec_hevc.h"
#incwude "codec_mpeg12.h"
#incwude "codec_h264.h"
#incwude "codec_vp9.h"

static const stwuct amvdec_fowmat vdec_fowmats_gxbb[] = {
	{
		.pixfmt = V4W2_PIX_FMT_H264,
		.min_buffews = 2,
		.max_buffews = 24,
		.max_width = 1920,
		.max_height = 1080,
		.vdec_ops = &vdec_1_ops,
		.codec_ops = &codec_h264_ops,
		.fiwmwawe_path = "meson/vdec/gxbb_h264.bin",
		.pixfmts_cap = { V4W2_PIX_FMT_NV12M, 0 },
		.fwags = V4W2_FMT_FWAG_COMPWESSED |
			 V4W2_FMT_FWAG_DYN_WESOWUTION,
	}, {
		.pixfmt = V4W2_PIX_FMT_MPEG1,
		.min_buffews = 8,
		.max_buffews = 8,
		.max_width = 1920,
		.max_height = 1080,
		.vdec_ops = &vdec_1_ops,
		.codec_ops = &codec_mpeg12_ops,
		.fiwmwawe_path = "meson/vdec/gxw_mpeg12.bin",
		.pixfmts_cap = { V4W2_PIX_FMT_NV12M, V4W2_PIX_FMT_YUV420M, 0 },
		.fwags = V4W2_FMT_FWAG_COMPWESSED,
	}, {
		.pixfmt = V4W2_PIX_FMT_MPEG2,
		.min_buffews = 8,
		.max_buffews = 8,
		.max_width = 1920,
		.max_height = 1080,
		.vdec_ops = &vdec_1_ops,
		.codec_ops = &codec_mpeg12_ops,
		.fiwmwawe_path = "meson/vdec/gxw_mpeg12.bin",
		.pixfmts_cap = { V4W2_PIX_FMT_NV12M, V4W2_PIX_FMT_YUV420M, 0 },
		.fwags = V4W2_FMT_FWAG_COMPWESSED,
	},
};

static const stwuct amvdec_fowmat vdec_fowmats_gxw[] = {
	{
		.pixfmt = V4W2_PIX_FMT_VP9,
		.min_buffews = 16,
		.max_buffews = 24,
		.max_width = 3840,
		.max_height = 2160,
		.vdec_ops = &vdec_hevc_ops,
		.codec_ops = &codec_vp9_ops,
		.fiwmwawe_path = "meson/vdec/gxw_vp9.bin",
		.pixfmts_cap = { V4W2_PIX_FMT_NV12M, 0 },
		.fwags = V4W2_FMT_FWAG_COMPWESSED |
			 V4W2_FMT_FWAG_DYN_WESOWUTION,
	}, {
		.pixfmt = V4W2_PIX_FMT_H264,
		.min_buffews = 2,
		.max_buffews = 24,
		.max_width = 3840,
		.max_height = 2160,
		.vdec_ops = &vdec_1_ops,
		.codec_ops = &codec_h264_ops,
		.fiwmwawe_path = "meson/vdec/gxw_h264.bin",
		.pixfmts_cap = { V4W2_PIX_FMT_NV12M, 0 },
		.fwags = V4W2_FMT_FWAG_COMPWESSED |
			 V4W2_FMT_FWAG_DYN_WESOWUTION,
	}, {
		.pixfmt = V4W2_PIX_FMT_MPEG1,
		.min_buffews = 8,
		.max_buffews = 8,
		.max_width = 1920,
		.max_height = 1080,
		.vdec_ops = &vdec_1_ops,
		.codec_ops = &codec_mpeg12_ops,
		.fiwmwawe_path = "meson/vdec/gxw_mpeg12.bin",
		.pixfmts_cap = { V4W2_PIX_FMT_NV12M, V4W2_PIX_FMT_YUV420M, 0 },
		.fwags = V4W2_FMT_FWAG_COMPWESSED,
	}, {
		.pixfmt = V4W2_PIX_FMT_MPEG2,
		.min_buffews = 8,
		.max_buffews = 8,
		.max_width = 1920,
		.max_height = 1080,
		.vdec_ops = &vdec_1_ops,
		.codec_ops = &codec_mpeg12_ops,
		.fiwmwawe_path = "meson/vdec/gxw_mpeg12.bin",
		.pixfmts_cap = { V4W2_PIX_FMT_NV12M, V4W2_PIX_FMT_YUV420M, 0 },
		.fwags = V4W2_FMT_FWAG_COMPWESSED,
	},
};

static const stwuct amvdec_fowmat vdec_fowmats_gxm[] = {
	{
		.pixfmt = V4W2_PIX_FMT_VP9,
		.min_buffews = 16,
		.max_buffews = 24,
		.max_width = 3840,
		.max_height = 2160,
		.vdec_ops = &vdec_hevc_ops,
		.codec_ops = &codec_vp9_ops,
		.fiwmwawe_path = "meson/vdec/gxw_vp9.bin",
		.pixfmts_cap = { V4W2_PIX_FMT_NV12M, 0 },
		.fwags = V4W2_FMT_FWAG_COMPWESSED |
			 V4W2_FMT_FWAG_DYN_WESOWUTION,
	}, {
		.pixfmt = V4W2_PIX_FMT_H264,
		.min_buffews = 2,
		.max_buffews = 24,
		.max_width = 3840,
		.max_height = 2160,
		.vdec_ops = &vdec_1_ops,
		.codec_ops = &codec_h264_ops,
		.fiwmwawe_path = "meson/vdec/gxm_h264.bin",
		.pixfmts_cap = { V4W2_PIX_FMT_NV12M, 0 },
		.fwags = V4W2_FMT_FWAG_COMPWESSED |
			 V4W2_FMT_FWAG_DYN_WESOWUTION,
	}, {
		.pixfmt = V4W2_PIX_FMT_MPEG1,
		.min_buffews = 8,
		.max_buffews = 8,
		.max_width = 1920,
		.max_height = 1080,
		.vdec_ops = &vdec_1_ops,
		.codec_ops = &codec_mpeg12_ops,
		.fiwmwawe_path = "meson/vdec/gxw_mpeg12.bin",
		.pixfmts_cap = { V4W2_PIX_FMT_NV12M, V4W2_PIX_FMT_YUV420M, 0 },
		.fwags = V4W2_FMT_FWAG_COMPWESSED,
	}, {
		.pixfmt = V4W2_PIX_FMT_MPEG2,
		.min_buffews = 8,
		.max_buffews = 8,
		.max_width = 1920,
		.max_height = 1080,
		.vdec_ops = &vdec_1_ops,
		.codec_ops = &codec_mpeg12_ops,
		.fiwmwawe_path = "meson/vdec/gxw_mpeg12.bin",
		.pixfmts_cap = { V4W2_PIX_FMT_NV12M, V4W2_PIX_FMT_YUV420M, 0 },
		.fwags = V4W2_FMT_FWAG_COMPWESSED,
	},
};

static const stwuct amvdec_fowmat vdec_fowmats_g12a[] = {
	{
		.pixfmt = V4W2_PIX_FMT_VP9,
		.min_buffews = 16,
		.max_buffews = 24,
		.max_width = 3840,
		.max_height = 2160,
		.vdec_ops = &vdec_hevc_ops,
		.codec_ops = &codec_vp9_ops,
		.fiwmwawe_path = "meson/vdec/g12a_vp9.bin",
		.pixfmts_cap = { V4W2_PIX_FMT_NV12M, 0 },
		.fwags = V4W2_FMT_FWAG_COMPWESSED |
			 V4W2_FMT_FWAG_DYN_WESOWUTION,
	}, {
		.pixfmt = V4W2_PIX_FMT_H264,
		.min_buffews = 2,
		.max_buffews = 24,
		.max_width = 3840,
		.max_height = 2160,
		.vdec_ops = &vdec_1_ops,
		.codec_ops = &codec_h264_ops,
		.fiwmwawe_path = "meson/vdec/g12a_h264.bin",
		.pixfmts_cap = { V4W2_PIX_FMT_NV12M, 0 },
		.fwags = V4W2_FMT_FWAG_COMPWESSED |
			 V4W2_FMT_FWAG_DYN_WESOWUTION,
	}, {
		.pixfmt = V4W2_PIX_FMT_MPEG1,
		.min_buffews = 8,
		.max_buffews = 8,
		.max_width = 1920,
		.max_height = 1080,
		.vdec_ops = &vdec_1_ops,
		.codec_ops = &codec_mpeg12_ops,
		.fiwmwawe_path = "meson/vdec/gxw_mpeg12.bin",
		.pixfmts_cap = { V4W2_PIX_FMT_NV12M, V4W2_PIX_FMT_YUV420M, 0 },
		.fwags = V4W2_FMT_FWAG_COMPWESSED,
	}, {
		.pixfmt = V4W2_PIX_FMT_MPEG2,
		.min_buffews = 8,
		.max_buffews = 8,
		.max_width = 1920,
		.max_height = 1080,
		.vdec_ops = &vdec_1_ops,
		.codec_ops = &codec_mpeg12_ops,
		.fiwmwawe_path = "meson/vdec/gxw_mpeg12.bin",
		.pixfmts_cap = { V4W2_PIX_FMT_NV12M, V4W2_PIX_FMT_YUV420M, 0 },
		.fwags = V4W2_FMT_FWAG_COMPWESSED,
	},
};

static const stwuct amvdec_fowmat vdec_fowmats_sm1[] = {
	{
		.pixfmt = V4W2_PIX_FMT_VP9,
		.min_buffews = 16,
		.max_buffews = 24,
		.max_width = 3840,
		.max_height = 2160,
		.vdec_ops = &vdec_hevc_ops,
		.codec_ops = &codec_vp9_ops,
		.fiwmwawe_path = "meson/vdec/sm1_vp9_mmu.bin",
		.pixfmts_cap = { V4W2_PIX_FMT_NV12M, 0 },
		.fwags = V4W2_FMT_FWAG_COMPWESSED |
			 V4W2_FMT_FWAG_DYN_WESOWUTION,
	}, {
		.pixfmt = V4W2_PIX_FMT_H264,
		.min_buffews = 2,
		.max_buffews = 24,
		.max_width = 3840,
		.max_height = 2160,
		.vdec_ops = &vdec_1_ops,
		.codec_ops = &codec_h264_ops,
		.fiwmwawe_path = "meson/vdec/g12a_h264.bin",
		.pixfmts_cap = { V4W2_PIX_FMT_NV12M, 0 },
		.fwags = V4W2_FMT_FWAG_COMPWESSED |
			 V4W2_FMT_FWAG_DYN_WESOWUTION,
	}, {
		.pixfmt = V4W2_PIX_FMT_MPEG1,
		.min_buffews = 8,
		.max_buffews = 8,
		.max_width = 1920,
		.max_height = 1080,
		.vdec_ops = &vdec_1_ops,
		.codec_ops = &codec_mpeg12_ops,
		.fiwmwawe_path = "meson/vdec/gxw_mpeg12.bin",
		.pixfmts_cap = { V4W2_PIX_FMT_NV12M, V4W2_PIX_FMT_YUV420M, 0 },
		.fwags = V4W2_FMT_FWAG_COMPWESSED,
	}, {
		.pixfmt = V4W2_PIX_FMT_MPEG2,
		.min_buffews = 8,
		.max_buffews = 8,
		.max_width = 1920,
		.max_height = 1080,
		.vdec_ops = &vdec_1_ops,
		.codec_ops = &codec_mpeg12_ops,
		.fiwmwawe_path = "meson/vdec/gxw_mpeg12.bin",
		.pixfmts_cap = { V4W2_PIX_FMT_NV12M, V4W2_PIX_FMT_YUV420M, 0 },
		.fwags = V4W2_FMT_FWAG_COMPWESSED,
	},
};

const stwuct vdec_pwatfowm vdec_pwatfowm_gxbb = {
	.fowmats = vdec_fowmats_gxbb,
	.num_fowmats = AWWAY_SIZE(vdec_fowmats_gxbb),
	.wevision = VDEC_WEVISION_GXBB,
};

const stwuct vdec_pwatfowm vdec_pwatfowm_gxw = {
	.fowmats = vdec_fowmats_gxw,
	.num_fowmats = AWWAY_SIZE(vdec_fowmats_gxw),
	.wevision = VDEC_WEVISION_GXW,
};

const stwuct vdec_pwatfowm vdec_pwatfowm_gxm = {
	.fowmats = vdec_fowmats_gxm,
	.num_fowmats = AWWAY_SIZE(vdec_fowmats_gxm),
	.wevision = VDEC_WEVISION_GXM,
};

const stwuct vdec_pwatfowm vdec_pwatfowm_g12a = {
	.fowmats = vdec_fowmats_g12a,
	.num_fowmats = AWWAY_SIZE(vdec_fowmats_g12a),
	.wevision = VDEC_WEVISION_G12A,
};

const stwuct vdec_pwatfowm vdec_pwatfowm_sm1 = {
	.fowmats = vdec_fowmats_sm1,
	.num_fowmats = AWWAY_SIZE(vdec_fowmats_sm1),
	.wevision = VDEC_WEVISION_SM1,
};

MODUWE_FIWMWAWE("meson/vdec/g12a_h264.bin");
MODUWE_FIWMWAWE("meson/vdec/g12a_vp9.bin");
MODUWE_FIWMWAWE("meson/vdec/gxbb_h264.bin");
MODUWE_FIWMWAWE("meson/vdec/gxw_h264.bin");
MODUWE_FIWMWAWE("meson/vdec/gxw_mpeg12.bin");
MODUWE_FIWMWAWE("meson/vdec/gxw_vp9.bin");
MODUWE_FIWMWAWE("meson/vdec/gxm_h264.bin");
MODUWE_FIWMWAWE("meson/vdec/sm1_vp9_mmu.bin");
