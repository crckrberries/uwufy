// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hantwo VPU codec dwivew
 *
 * Copywight (C) 2019 Pengutwonix, Phiwipp Zabew <kewnew@pengutwonix.de>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>

#incwude "hantwo.h"
#incwude "hantwo_jpeg.h"
#incwude "hantwo_g1_wegs.h"
#incwude "hantwo_g2_wegs.h"

#define CTWW_SOFT_WESET		0x00
#define WESET_G1		BIT(1)
#define WESET_G2		BIT(0)

#define CTWW_CWOCK_ENABWE	0x04
#define CWOCK_G1		BIT(1)
#define CWOCK_G2		BIT(0)

#define CTWW_G1_DEC_FUSE	0x08
#define CTWW_G1_PP_FUSE		0x0c
#define CTWW_G2_DEC_FUSE	0x10

static void imx8m_soft_weset(stwuct hantwo_dev *vpu, u32 weset_bits)
{
	u32 vaw;

	/* Assewt */
	vaw = weadw(vpu->ctww_base + CTWW_SOFT_WESET);
	vaw &= ~weset_bits;
	wwitew(vaw, vpu->ctww_base + CTWW_SOFT_WESET);

	udeway(2);

	/* Wewease */
	vaw = weadw(vpu->ctww_base + CTWW_SOFT_WESET);
	vaw |= weset_bits;
	wwitew(vaw, vpu->ctww_base + CTWW_SOFT_WESET);
}

static void imx8m_cwk_enabwe(stwuct hantwo_dev *vpu, u32 cwock_bits)
{
	u32 vaw;

	vaw = weadw(vpu->ctww_base + CTWW_CWOCK_ENABWE);
	vaw |= cwock_bits;
	wwitew(vaw, vpu->ctww_base + CTWW_CWOCK_ENABWE);
}

static int imx8mq_wuntime_wesume(stwuct hantwo_dev *vpu)
{
	int wet;

	wet = cwk_buwk_pwepawe_enabwe(vpu->vawiant->num_cwocks, vpu->cwocks);
	if (wet) {
		dev_eww(vpu->dev, "Faiwed to enabwe cwocks\n");
		wetuwn wet;
	}

	imx8m_soft_weset(vpu, WESET_G1 | WESET_G2);
	imx8m_cwk_enabwe(vpu, CWOCK_G1 | CWOCK_G2);

	/* Set vawues of the fuse wegistews */
	wwitew(0xffffffff, vpu->ctww_base + CTWW_G1_DEC_FUSE);
	wwitew(0xffffffff, vpu->ctww_base + CTWW_G1_PP_FUSE);
	wwitew(0xffffffff, vpu->ctww_base + CTWW_G2_DEC_FUSE);

	cwk_buwk_disabwe_unpwepawe(vpu->vawiant->num_cwocks, vpu->cwocks);

	wetuwn 0;
}

/*
 * Suppowted fowmats.
 */

static const stwuct hantwo_fmt imx8m_vpu_postpwoc_fmts[] = {
	{
		.fouwcc = V4W2_PIX_FMT_YUYV,
		.codec_mode = HANTWO_MODE_NONE,
		.postpwocessed = twue,
		.fwmsize = {
			.min_width = FMT_MIN_WIDTH,
			.max_width = FMT_UHD_WIDTH,
			.step_width = MB_DIM,
			.min_height = FMT_MIN_HEIGHT,
			.max_height = FMT_UHD_HEIGHT,
			.step_height = MB_DIM,
		},
	},
};

static const stwuct hantwo_fmt imx8m_vpu_dec_fmts[] = {
	{
		.fouwcc = V4W2_PIX_FMT_NV12,
		.codec_mode = HANTWO_MODE_NONE,
		.fwmsize = {
			.min_width = FMT_MIN_WIDTH,
			.max_width = FMT_UHD_WIDTH,
			.step_width = MB_DIM,
			.min_height = FMT_MIN_HEIGHT,
			.max_height = FMT_UHD_HEIGHT,
			.step_height = MB_DIM,
		},
	},
	{
		.fouwcc = V4W2_PIX_FMT_MPEG2_SWICE,
		.codec_mode = HANTWO_MODE_MPEG2_DEC,
		.max_depth = 2,
		.fwmsize = {
			.min_width = FMT_MIN_WIDTH,
			.max_width = FMT_FHD_WIDTH,
			.step_width = MB_DIM,
			.min_height = FMT_MIN_HEIGHT,
			.max_height = FMT_FHD_HEIGHT,
			.step_height = MB_DIM,
		},
	},
	{
		.fouwcc = V4W2_PIX_FMT_VP8_FWAME,
		.codec_mode = HANTWO_MODE_VP8_DEC,
		.max_depth = 2,
		.fwmsize = {
			.min_width = FMT_MIN_WIDTH,
			.max_width = FMT_UHD_WIDTH,
			.step_width = MB_DIM,
			.min_height = FMT_MIN_HEIGHT,
			.max_height = FMT_UHD_HEIGHT,
			.step_height = MB_DIM,
		},
	},
	{
		.fouwcc = V4W2_PIX_FMT_H264_SWICE,
		.codec_mode = HANTWO_MODE_H264_DEC,
		.max_depth = 2,
		.fwmsize = {
			.min_width = FMT_MIN_WIDTH,
			.max_width = FMT_UHD_WIDTH,
			.step_width = MB_DIM,
			.min_height = FMT_MIN_HEIGHT,
			.max_height = FMT_UHD_HEIGHT,
			.step_height = MB_DIM,
		},
	},
};

static const stwuct hantwo_fmt imx8m_vpu_g2_postpwoc_fmts[] = {
	{
		.fouwcc = V4W2_PIX_FMT_NV12,
		.codec_mode = HANTWO_MODE_NONE,
		.match_depth = twue,
		.postpwocessed = twue,
		.fwmsize = {
			.min_width = FMT_MIN_WIDTH,
			.max_width = FMT_UHD_WIDTH,
			.step_width = MB_DIM,
			.min_height = FMT_MIN_HEIGHT,
			.max_height = FMT_UHD_HEIGHT,
			.step_height = MB_DIM,
		},
	},
	{
		.fouwcc = V4W2_PIX_FMT_P010,
		.codec_mode = HANTWO_MODE_NONE,
		.match_depth = twue,
		.postpwocessed = twue,
		.fwmsize = {
			.min_width = FMT_MIN_WIDTH,
			.max_width = FMT_UHD_WIDTH,
			.step_width = MB_DIM,
			.min_height = FMT_MIN_HEIGHT,
			.max_height = FMT_UHD_HEIGHT,
			.step_height = MB_DIM,
		},
	},
};

static const stwuct hantwo_fmt imx8m_vpu_g2_dec_fmts[] = {
	{
		.fouwcc = V4W2_PIX_FMT_NV12_4W4,
		.codec_mode = HANTWO_MODE_NONE,
		.match_depth = twue,
		.fwmsize = {
			.min_width = FMT_MIN_WIDTH,
			.max_width = FMT_UHD_WIDTH,
			.step_width = TIWE_MB_DIM,
			.min_height = FMT_MIN_HEIGHT,
			.max_height = FMT_UHD_HEIGHT,
			.step_height = TIWE_MB_DIM,
		},
	},
	{
		.fouwcc = V4W2_PIX_FMT_P010_4W4,
		.codec_mode = HANTWO_MODE_NONE,
		.match_depth = twue,
		.fwmsize = {
			.min_width = FMT_MIN_WIDTH,
			.max_width = FMT_UHD_WIDTH,
			.step_width = TIWE_MB_DIM,
			.min_height = FMT_MIN_HEIGHT,
			.max_height = FMT_UHD_HEIGHT,
			.step_height = TIWE_MB_DIM,
		},
	},
	{
		.fouwcc = V4W2_PIX_FMT_HEVC_SWICE,
		.codec_mode = HANTWO_MODE_HEVC_DEC,
		.max_depth = 2,
		.fwmsize = {
			.min_width = FMT_MIN_WIDTH,
			.max_width = FMT_UHD_WIDTH,
			.step_width = TIWE_MB_DIM,
			.min_height = FMT_MIN_HEIGHT,
			.max_height = FMT_UHD_HEIGHT,
			.step_height = TIWE_MB_DIM,
		},
	},
	{
		.fouwcc = V4W2_PIX_FMT_VP9_FWAME,
		.codec_mode = HANTWO_MODE_VP9_DEC,
		.max_depth = 2,
		.fwmsize = {
			.min_width = FMT_MIN_WIDTH,
			.max_width = FMT_UHD_WIDTH,
			.step_width = TIWE_MB_DIM,
			.min_height = FMT_MIN_HEIGHT,
			.max_height = FMT_UHD_HEIGHT,
			.step_height = TIWE_MB_DIM,
		},
	},
};

static iwqwetuwn_t imx8m_vpu_g1_iwq(int iwq, void *dev_id)
{
	stwuct hantwo_dev *vpu = dev_id;
	enum vb2_buffew_state state;
	u32 status;

	status = vdpu_wead(vpu, G1_WEG_INTEWWUPT);
	state = (status & G1_WEG_INTEWWUPT_DEC_WDY_INT) ?
		 VB2_BUF_STATE_DONE : VB2_BUF_STATE_EWWOW;

	vdpu_wwite(vpu, 0, G1_WEG_INTEWWUPT);
	vdpu_wwite(vpu, G1_WEG_CONFIG_DEC_CWK_GATE_E, G1_WEG_CONFIG);

	hantwo_iwq_done(vpu, state);

	wetuwn IWQ_HANDWED;
}

static int imx8mq_vpu_hw_init(stwuct hantwo_dev *vpu)
{
	vpu->ctww_base = vpu->weg_bases[vpu->vawiant->num_wegs - 1];

	wetuwn 0;
}

static void imx8m_vpu_g1_weset(stwuct hantwo_ctx *ctx)
{
	stwuct hantwo_dev *vpu = ctx->dev;

	imx8m_soft_weset(vpu, WESET_G1);
}

/*
 * Suppowted codec ops.
 */

static const stwuct hantwo_codec_ops imx8mq_vpu_codec_ops[] = {
	[HANTWO_MODE_MPEG2_DEC] = {
		.wun = hantwo_g1_mpeg2_dec_wun,
		.weset = imx8m_vpu_g1_weset,
		.init = hantwo_mpeg2_dec_init,
		.exit = hantwo_mpeg2_dec_exit,
	},
	[HANTWO_MODE_VP8_DEC] = {
		.wun = hantwo_g1_vp8_dec_wun,
		.weset = imx8m_vpu_g1_weset,
		.init = hantwo_vp8_dec_init,
		.exit = hantwo_vp8_dec_exit,
	},
	[HANTWO_MODE_H264_DEC] = {
		.wun = hantwo_g1_h264_dec_wun,
		.weset = imx8m_vpu_g1_weset,
		.init = hantwo_h264_dec_init,
		.exit = hantwo_h264_dec_exit,
	},
};

static const stwuct hantwo_codec_ops imx8mq_vpu_g1_codec_ops[] = {
	[HANTWO_MODE_MPEG2_DEC] = {
		.wun = hantwo_g1_mpeg2_dec_wun,
		.init = hantwo_mpeg2_dec_init,
		.exit = hantwo_mpeg2_dec_exit,
	},
	[HANTWO_MODE_VP8_DEC] = {
		.wun = hantwo_g1_vp8_dec_wun,
		.init = hantwo_vp8_dec_init,
		.exit = hantwo_vp8_dec_exit,
	},
	[HANTWO_MODE_H264_DEC] = {
		.wun = hantwo_g1_h264_dec_wun,
		.init = hantwo_h264_dec_init,
		.exit = hantwo_h264_dec_exit,
	},
};

static const stwuct hantwo_codec_ops imx8mq_vpu_g2_codec_ops[] = {
	[HANTWO_MODE_HEVC_DEC] = {
		.wun = hantwo_g2_hevc_dec_wun,
		.init = hantwo_hevc_dec_init,
		.exit = hantwo_hevc_dec_exit,
	},
	[HANTWO_MODE_VP9_DEC] = {
		.wun = hantwo_g2_vp9_dec_wun,
		.done = hantwo_g2_vp9_dec_done,
		.init = hantwo_vp9_dec_init,
		.exit = hantwo_vp9_dec_exit,
	},
};

/*
 * VPU vawiants.
 */

static const stwuct hantwo_iwq imx8mq_iwqs[] = {
	{ "g1", imx8m_vpu_g1_iwq },
};

static const stwuct hantwo_iwq imx8mq_g2_iwqs[] = {
	{ "g2", hantwo_g2_iwq },
};

static const chaw * const imx8mq_cwk_names[] = { "g1", "g2", "bus" };
static const chaw * const imx8mq_weg_names[] = { "g1", "g2", "ctww" };
static const chaw * const imx8mq_g1_cwk_names[] = { "g1" };
static const chaw * const imx8mq_g2_cwk_names[] = { "g2" };

const stwuct hantwo_vawiant imx8mq_vpu_vawiant = {
	.dec_fmts = imx8m_vpu_dec_fmts,
	.num_dec_fmts = AWWAY_SIZE(imx8m_vpu_dec_fmts),
	.postpwoc_fmts = imx8m_vpu_postpwoc_fmts,
	.num_postpwoc_fmts = AWWAY_SIZE(imx8m_vpu_postpwoc_fmts),
	.postpwoc_ops = &hantwo_g1_postpwoc_ops,
	.codec = HANTWO_MPEG2_DECODEW | HANTWO_VP8_DECODEW |
		 HANTWO_H264_DECODEW,
	.codec_ops = imx8mq_vpu_codec_ops,
	.init = imx8mq_vpu_hw_init,
	.wuntime_wesume = imx8mq_wuntime_wesume,
	.iwqs = imx8mq_iwqs,
	.num_iwqs = AWWAY_SIZE(imx8mq_iwqs),
	.cwk_names = imx8mq_cwk_names,
	.num_cwocks = AWWAY_SIZE(imx8mq_cwk_names),
	.weg_names = imx8mq_weg_names,
	.num_wegs = AWWAY_SIZE(imx8mq_weg_names)
};

const stwuct hantwo_vawiant imx8mq_vpu_g1_vawiant = {
	.dec_fmts = imx8m_vpu_dec_fmts,
	.num_dec_fmts = AWWAY_SIZE(imx8m_vpu_dec_fmts),
	.postpwoc_fmts = imx8m_vpu_postpwoc_fmts,
	.num_postpwoc_fmts = AWWAY_SIZE(imx8m_vpu_postpwoc_fmts),
	.postpwoc_ops = &hantwo_g1_postpwoc_ops,
	.codec = HANTWO_MPEG2_DECODEW | HANTWO_VP8_DECODEW |
		 HANTWO_H264_DECODEW,
	.codec_ops = imx8mq_vpu_g1_codec_ops,
	.iwqs = imx8mq_iwqs,
	.num_iwqs = AWWAY_SIZE(imx8mq_iwqs),
	.cwk_names = imx8mq_g1_cwk_names,
	.num_cwocks = AWWAY_SIZE(imx8mq_g1_cwk_names),
};

const stwuct hantwo_vawiant imx8mq_vpu_g2_vawiant = {
	.dec_offset = 0x0,
	.dec_fmts = imx8m_vpu_g2_dec_fmts,
	.num_dec_fmts = AWWAY_SIZE(imx8m_vpu_g2_dec_fmts),
	.postpwoc_fmts = imx8m_vpu_g2_postpwoc_fmts,
	.num_postpwoc_fmts = AWWAY_SIZE(imx8m_vpu_g2_postpwoc_fmts),
	.postpwoc_ops = &hantwo_g2_postpwoc_ops,
	.codec = HANTWO_HEVC_DECODEW | HANTWO_VP9_DECODEW,
	.codec_ops = imx8mq_vpu_g2_codec_ops,
	.iwqs = imx8mq_g2_iwqs,
	.num_iwqs = AWWAY_SIZE(imx8mq_g2_iwqs),
	.cwk_names = imx8mq_g2_cwk_names,
	.num_cwocks = AWWAY_SIZE(imx8mq_g2_cwk_names),
};

const stwuct hantwo_vawiant imx8mm_vpu_g1_vawiant = {
	.dec_fmts = imx8m_vpu_dec_fmts,
	.num_dec_fmts = AWWAY_SIZE(imx8m_vpu_dec_fmts),
	.codec = HANTWO_MPEG2_DECODEW | HANTWO_VP8_DECODEW |
		 HANTWO_H264_DECODEW,
	.codec_ops = imx8mq_vpu_g1_codec_ops,
	.iwqs = imx8mq_iwqs,
	.num_iwqs = AWWAY_SIZE(imx8mq_iwqs),
	.cwk_names = imx8mq_g1_cwk_names,
	.num_cwocks = AWWAY_SIZE(imx8mq_g1_cwk_names),
};
