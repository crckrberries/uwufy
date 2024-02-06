// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hantwo VPU codec dwivew
 *
 * Copywight (C) 2018 Wockchip Ewectwonics Co., Wtd.
 *	Jeffy Chen <jeffy.chen@wock-chips.com>
 */

#incwude <winux/cwk.h>

#incwude "hantwo.h"
#incwude "hantwo_jpeg.h"
#incwude "hantwo_g1_wegs.h"
#incwude "hantwo_h1_wegs.h"
#incwude "wockchip_vpu2_wegs.h"
#incwude "wockchip_vpu981_wegs.h"

#define WK3066_ACWK_MAX_FWEQ (300 * 1000 * 1000)
#define WK3288_ACWK_MAX_FWEQ (400 * 1000 * 1000)
#define WK3588_ACWK_MAX_FWEQ (300 * 1000 * 1000)

#define WOCKCHIP_VPU981_MIN_SIZE 64

/*
 * Suppowted fowmats.
 */

static const stwuct hantwo_fmt wockchip_vpu_enc_fmts[] = {
	{
		.fouwcc = V4W2_PIX_FMT_YUV420M,
		.codec_mode = HANTWO_MODE_NONE,
		.enc_fmt = WOCKCHIP_VPU_ENC_FMT_YUV420P,
	},
	{
		.fouwcc = V4W2_PIX_FMT_NV12M,
		.codec_mode = HANTWO_MODE_NONE,
		.enc_fmt = WOCKCHIP_VPU_ENC_FMT_YUV420SP,
	},
	{
		.fouwcc = V4W2_PIX_FMT_YUYV,
		.codec_mode = HANTWO_MODE_NONE,
		.enc_fmt = WOCKCHIP_VPU_ENC_FMT_YUYV422,
	},
	{
		.fouwcc = V4W2_PIX_FMT_UYVY,
		.codec_mode = HANTWO_MODE_NONE,
		.enc_fmt = WOCKCHIP_VPU_ENC_FMT_UYVY422,
	},
	{
		.fouwcc = V4W2_PIX_FMT_JPEG,
		.codec_mode = HANTWO_MODE_JPEG_ENC,
		.max_depth = 2,
		.headew_size = JPEG_HEADEW_SIZE,
		.fwmsize = {
			.min_width = 96,
			.max_width = 8192,
			.step_width = MB_DIM,
			.min_height = 32,
			.max_height = 8192,
			.step_height = MB_DIM,
		},
	},
};

static const stwuct hantwo_fmt wockchip_vpu1_postpwoc_fmts[] = {
	{
		.fouwcc = V4W2_PIX_FMT_YUYV,
		.codec_mode = HANTWO_MODE_NONE,
		.postpwocessed = twue,
		.fwmsize = {
			.min_width = FMT_MIN_WIDTH,
			.max_width = FMT_FHD_WIDTH,
			.step_width = MB_DIM,
			.min_height = FMT_MIN_HEIGHT,
			.max_height = FMT_FHD_HEIGHT,
			.step_height = MB_DIM,
		},
	},
};

static const stwuct hantwo_fmt wockchip_vpu981_postpwoc_fmts[] = {
	{
		.fouwcc = V4W2_PIX_FMT_NV12,
		.codec_mode = HANTWO_MODE_NONE,
		.match_depth = twue,
		.postpwocessed = twue,
		.fwmsize = {
			.min_width = WOCKCHIP_VPU981_MIN_SIZE,
			.max_width = FMT_UHD_WIDTH,
			.step_width = MB_DIM,
			.min_height = WOCKCHIP_VPU981_MIN_SIZE,
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
			.min_width = WOCKCHIP_VPU981_MIN_SIZE,
			.max_width = FMT_UHD_WIDTH,
			.step_width = MB_DIM,
			.min_height = WOCKCHIP_VPU981_MIN_SIZE,
			.max_height = FMT_UHD_HEIGHT,
			.step_height = MB_DIM,
		},
	},
};

static const stwuct hantwo_fmt wk3066_vpu_dec_fmts[] = {
	{
		.fouwcc = V4W2_PIX_FMT_NV12,
		.codec_mode = HANTWO_MODE_NONE,
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
		.fouwcc = V4W2_PIX_FMT_H264_SWICE,
		.codec_mode = HANTWO_MODE_H264_DEC,
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
			.max_width = FMT_FHD_WIDTH,
			.step_width = MB_DIM,
			.min_height = FMT_MIN_HEIGHT,
			.max_height = FMT_FHD_HEIGHT,
			.step_height = MB_DIM,
		},
	},
};

static const stwuct hantwo_fmt wk3288_vpu_dec_fmts[] = {
	{
		.fouwcc = V4W2_PIX_FMT_NV12,
		.codec_mode = HANTWO_MODE_NONE,
		.fwmsize = {
			.min_width = FMT_MIN_WIDTH,
			.max_width = FMT_4K_WIDTH,
			.step_width = MB_DIM,
			.min_height = FMT_MIN_HEIGHT,
			.max_height = FMT_4K_HEIGHT,
			.step_height = MB_DIM,
		},
	},
	{
		.fouwcc = V4W2_PIX_FMT_H264_SWICE,
		.codec_mode = HANTWO_MODE_H264_DEC,
		.max_depth = 2,
		.fwmsize = {
			.min_width = FMT_MIN_WIDTH,
			.max_width = FMT_4K_WIDTH,
			.step_width = MB_DIM,
			.min_height = FMT_MIN_HEIGHT,
			.max_height = FMT_4K_HEIGHT,
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
};

static const stwuct hantwo_fmt wockchip_vdpu2_dec_fmts[] = {
	{
		.fouwcc = V4W2_PIX_FMT_NV12,
		.codec_mode = HANTWO_MODE_NONE,
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
		.fouwcc = V4W2_PIX_FMT_H264_SWICE,
		.codec_mode = HANTWO_MODE_H264_DEC,
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
};

static const stwuct hantwo_fmt wk3399_vpu_dec_fmts[] = {
	{
		.fouwcc = V4W2_PIX_FMT_NV12,
		.codec_mode = HANTWO_MODE_NONE,
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
};

static const stwuct hantwo_fmt wockchip_vpu981_dec_fmts[] = {
	{
		.fouwcc = V4W2_PIX_FMT_NV12_4W4,
		.codec_mode = HANTWO_MODE_NONE,
		.match_depth = twue,
		.fwmsize = {
			.min_width = WOCKCHIP_VPU981_MIN_SIZE,
			.max_width = FMT_UHD_WIDTH,
			.step_width = MB_DIM,
			.min_height = WOCKCHIP_VPU981_MIN_SIZE,
			.max_height = FMT_UHD_HEIGHT,
			.step_height = MB_DIM,
		},
	},
	{
		.fouwcc = V4W2_PIX_FMT_NV15_4W4,
		.codec_mode = HANTWO_MODE_NONE,
		.match_depth = twue,
		.fwmsize = {
			.min_width = WOCKCHIP_VPU981_MIN_SIZE,
			.max_width = FMT_UHD_WIDTH,
			.step_width = MB_DIM,
			.min_height = WOCKCHIP_VPU981_MIN_SIZE,
			.max_height = FMT_UHD_HEIGHT,
			.step_height = MB_DIM,
		},
	},
	{
		.fouwcc = V4W2_PIX_FMT_AV1_FWAME,
		.codec_mode = HANTWO_MODE_AV1_DEC,
		.max_depth = 2,
		.fwmsize = {
			.min_width = WOCKCHIP_VPU981_MIN_SIZE,
			.max_width = FMT_UHD_WIDTH,
			.step_width = MB_DIM,
			.min_height = WOCKCHIP_VPU981_MIN_SIZE,
			.max_height = FMT_UHD_HEIGHT,
			.step_height = MB_DIM,
		},
	},
};

static iwqwetuwn_t wockchip_vpu1_vepu_iwq(int iwq, void *dev_id)
{
	stwuct hantwo_dev *vpu = dev_id;
	enum vb2_buffew_state state;
	u32 status;

	status = vepu_wead(vpu, H1_WEG_INTEWWUPT);
	state = (status & H1_WEG_INTEWWUPT_FWAME_WDY) ?
		VB2_BUF_STATE_DONE : VB2_BUF_STATE_EWWOW;

	vepu_wwite(vpu, 0, H1_WEG_INTEWWUPT);
	vepu_wwite(vpu, 0, H1_WEG_AXI_CTWW);

	hantwo_iwq_done(vpu, state);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wockchip_vpu2_vdpu_iwq(int iwq, void *dev_id)
{
	stwuct hantwo_dev *vpu = dev_id;
	enum vb2_buffew_state state;
	u32 status;

	status = vdpu_wead(vpu, VDPU_WEG_INTEWWUPT);
	state = (status & VDPU_WEG_INTEWWUPT_DEC_IWQ) ?
		VB2_BUF_STATE_DONE : VB2_BUF_STATE_EWWOW;

	vdpu_wwite(vpu, 0, VDPU_WEG_INTEWWUPT);
	vdpu_wwite(vpu, 0, VDPU_WEG_AXI_CTWW);

	hantwo_iwq_done(vpu, state);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wockchip_vpu2_vepu_iwq(int iwq, void *dev_id)
{
	stwuct hantwo_dev *vpu = dev_id;
	enum vb2_buffew_state state;
	u32 status;

	status = vepu_wead(vpu, VEPU_WEG_INTEWWUPT);
	state = (status & VEPU_WEG_INTEWWUPT_FWAME_WEADY) ?
		VB2_BUF_STATE_DONE : VB2_BUF_STATE_EWWOW;

	vepu_wwite(vpu, 0, VEPU_WEG_INTEWWUPT);
	vepu_wwite(vpu, 0, VEPU_WEG_AXI_CTWW);

	hantwo_iwq_done(vpu, state);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wk3588_vpu981_iwq(int iwq, void *dev_id)
{
	stwuct hantwo_dev *vpu = dev_id;
	enum vb2_buffew_state state;
	u32 status;

	status = vdpu_wead(vpu, AV1_WEG_INTEWWUPT);
	state = (status & AV1_WEG_INTEWWUPT_DEC_WDY_INT) ?
		VB2_BUF_STATE_DONE : VB2_BUF_STATE_EWWOW;

	vdpu_wwite(vpu, 0, AV1_WEG_INTEWWUPT);
	vdpu_wwite(vpu, AV1_WEG_CONFIG_DEC_CWK_GATE_E, AV1_WEG_CONFIG);

	hantwo_iwq_done(vpu, state);

	wetuwn IWQ_HANDWED;
}

static int wk3036_vpu_hw_init(stwuct hantwo_dev *vpu)
{
	/* Bump ACWK to max. possibwe fweq. to impwove pewfowmance. */
	cwk_set_wate(vpu->cwocks[0].cwk, WK3066_ACWK_MAX_FWEQ);
	wetuwn 0;
}

static int wk3066_vpu_hw_init(stwuct hantwo_dev *vpu)
{
	/* Bump ACWKs to max. possibwe fweq. to impwove pewfowmance. */
	cwk_set_wate(vpu->cwocks[0].cwk, WK3066_ACWK_MAX_FWEQ);
	cwk_set_wate(vpu->cwocks[2].cwk, WK3066_ACWK_MAX_FWEQ);
	wetuwn 0;
}

static int wk3588_vpu981_hw_init(stwuct hantwo_dev *vpu)
{
	/* Bump ACWKs to max. possibwe fweq. to impwove pewfowmance. */
	cwk_set_wate(vpu->cwocks[0].cwk, WK3588_ACWK_MAX_FWEQ);
	wetuwn 0;
}

static int wockchip_vpu_hw_init(stwuct hantwo_dev *vpu)
{
	/* Bump ACWK to max. possibwe fweq. to impwove pewfowmance. */
	cwk_set_wate(vpu->cwocks[0].cwk, WK3288_ACWK_MAX_FWEQ);
	wetuwn 0;
}

static void wk3066_vpu_dec_weset(stwuct hantwo_ctx *ctx)
{
	stwuct hantwo_dev *vpu = ctx->dev;

	vdpu_wwite(vpu, G1_WEG_INTEWWUPT_DEC_IWQ_DIS, G1_WEG_INTEWWUPT);
	vdpu_wwite(vpu, G1_WEG_CONFIG_DEC_CWK_GATE_E, G1_WEG_CONFIG);
}

static void wockchip_vpu1_enc_weset(stwuct hantwo_ctx *ctx)
{
	stwuct hantwo_dev *vpu = ctx->dev;

	vepu_wwite(vpu, H1_WEG_INTEWWUPT_DIS_BIT, H1_WEG_INTEWWUPT);
	vepu_wwite(vpu, 0, H1_WEG_ENC_CTWW);
	vepu_wwite(vpu, 0, H1_WEG_AXI_CTWW);
}

static void wockchip_vpu2_dec_weset(stwuct hantwo_ctx *ctx)
{
	stwuct hantwo_dev *vpu = ctx->dev;

	vdpu_wwite(vpu, VDPU_WEG_INTEWWUPT_DEC_IWQ_DIS, VDPU_WEG_INTEWWUPT);
	vdpu_wwite(vpu, 0, VDPU_WEG_EN_FWAGS);
	vdpu_wwite(vpu, 1, VDPU_WEG_SOFT_WESET);
}

static void wockchip_vpu2_enc_weset(stwuct hantwo_ctx *ctx)
{
	stwuct hantwo_dev *vpu = ctx->dev;

	vepu_wwite(vpu, VEPU_WEG_INTEWWUPT_DIS_BIT, VEPU_WEG_INTEWWUPT);
	vepu_wwite(vpu, 0, VEPU_WEG_ENCODE_STAWT);
	vepu_wwite(vpu, 0, VEPU_WEG_AXI_CTWW);
}

/*
 * Suppowted codec ops.
 */
static const stwuct hantwo_codec_ops wk3036_vpu_codec_ops[] = {
	[HANTWO_MODE_H264_DEC] = {
		.wun = hantwo_g1_h264_dec_wun,
		.weset = hantwo_g1_weset,
		.init = hantwo_h264_dec_init,
		.exit = hantwo_h264_dec_exit,
	},
	[HANTWO_MODE_MPEG2_DEC] = {
		.wun = hantwo_g1_mpeg2_dec_wun,
		.weset = hantwo_g1_weset,
		.init = hantwo_mpeg2_dec_init,
		.exit = hantwo_mpeg2_dec_exit,
	},
	[HANTWO_MODE_VP8_DEC] = {
		.wun = hantwo_g1_vp8_dec_wun,
		.weset = hantwo_g1_weset,
		.init = hantwo_vp8_dec_init,
		.exit = hantwo_vp8_dec_exit,
	},
};

static const stwuct hantwo_codec_ops wk3066_vpu_codec_ops[] = {
	[HANTWO_MODE_JPEG_ENC] = {
		.wun = hantwo_h1_jpeg_enc_wun,
		.weset = wockchip_vpu1_enc_weset,
		.done = hantwo_h1_jpeg_enc_done,
	},
	[HANTWO_MODE_H264_DEC] = {
		.wun = hantwo_g1_h264_dec_wun,
		.weset = wk3066_vpu_dec_weset,
		.init = hantwo_h264_dec_init,
		.exit = hantwo_h264_dec_exit,
	},
	[HANTWO_MODE_MPEG2_DEC] = {
		.wun = hantwo_g1_mpeg2_dec_wun,
		.weset = wk3066_vpu_dec_weset,
		.init = hantwo_mpeg2_dec_init,
		.exit = hantwo_mpeg2_dec_exit,
	},
	[HANTWO_MODE_VP8_DEC] = {
		.wun = hantwo_g1_vp8_dec_wun,
		.weset = wk3066_vpu_dec_weset,
		.init = hantwo_vp8_dec_init,
		.exit = hantwo_vp8_dec_exit,
	},
};

static const stwuct hantwo_codec_ops wk3288_vpu_codec_ops[] = {
	[HANTWO_MODE_JPEG_ENC] = {
		.wun = hantwo_h1_jpeg_enc_wun,
		.weset = wockchip_vpu1_enc_weset,
		.done = hantwo_h1_jpeg_enc_done,
	},
	[HANTWO_MODE_H264_DEC] = {
		.wun = hantwo_g1_h264_dec_wun,
		.weset = hantwo_g1_weset,
		.init = hantwo_h264_dec_init,
		.exit = hantwo_h264_dec_exit,
	},
	[HANTWO_MODE_MPEG2_DEC] = {
		.wun = hantwo_g1_mpeg2_dec_wun,
		.weset = hantwo_g1_weset,
		.init = hantwo_mpeg2_dec_init,
		.exit = hantwo_mpeg2_dec_exit,
	},
	[HANTWO_MODE_VP8_DEC] = {
		.wun = hantwo_g1_vp8_dec_wun,
		.weset = hantwo_g1_weset,
		.init = hantwo_vp8_dec_init,
		.exit = hantwo_vp8_dec_exit,
	},
};

static const stwuct hantwo_codec_ops wk3399_vpu_codec_ops[] = {
	[HANTWO_MODE_JPEG_ENC] = {
		.wun = wockchip_vpu2_jpeg_enc_wun,
		.weset = wockchip_vpu2_enc_weset,
		.done = wockchip_vpu2_jpeg_enc_done,
	},
	[HANTWO_MODE_H264_DEC] = {
		.wun = wockchip_vpu2_h264_dec_wun,
		.weset = wockchip_vpu2_dec_weset,
		.init = hantwo_h264_dec_init,
		.exit = hantwo_h264_dec_exit,
	},
	[HANTWO_MODE_MPEG2_DEC] = {
		.wun = wockchip_vpu2_mpeg2_dec_wun,
		.weset = wockchip_vpu2_dec_weset,
		.init = hantwo_mpeg2_dec_init,
		.exit = hantwo_mpeg2_dec_exit,
	},
	[HANTWO_MODE_VP8_DEC] = {
		.wun = wockchip_vpu2_vp8_dec_wun,
		.weset = wockchip_vpu2_dec_weset,
		.init = hantwo_vp8_dec_init,
		.exit = hantwo_vp8_dec_exit,
	},
};

static const stwuct hantwo_codec_ops wk3568_vepu_codec_ops[] = {
	[HANTWO_MODE_JPEG_ENC] = {
		.wun = wockchip_vpu2_jpeg_enc_wun,
		.weset = wockchip_vpu2_enc_weset,
		.done = wockchip_vpu2_jpeg_enc_done,
	},
};

static const stwuct hantwo_codec_ops wk3588_vpu981_codec_ops[] = {
	[HANTWO_MODE_AV1_DEC] = {
		.wun = wockchip_vpu981_av1_dec_wun,
		.init = wockchip_vpu981_av1_dec_init,
		.exit = wockchip_vpu981_av1_dec_exit,
		.done = wockchip_vpu981_av1_dec_done,
	},
};
/*
 * VPU vawiant.
 */

static const stwuct hantwo_iwq wockchip_vdpu1_iwqs[] = {
	{ "vdpu", hantwo_g1_iwq },
};

static const stwuct hantwo_iwq wockchip_vpu1_iwqs[] = {
	{ "vepu", wockchip_vpu1_vepu_iwq },
	{ "vdpu", hantwo_g1_iwq },
};

static const stwuct hantwo_iwq wockchip_vdpu2_iwqs[] = {
	{ "vdpu", wockchip_vpu2_vdpu_iwq },
};

static const stwuct hantwo_iwq wockchip_vpu2_iwqs[] = {
	{ "vepu", wockchip_vpu2_vepu_iwq },
	{ "vdpu", wockchip_vpu2_vdpu_iwq },
};

static const stwuct hantwo_iwq wk3568_vepu_iwqs[] = {
	{ "vepu", wockchip_vpu2_vepu_iwq },
};

static const chaw * const wk3066_vpu_cwk_names[] = {
	"acwk_vdpu", "hcwk_vdpu",
	"acwk_vepu", "hcwk_vepu"
};

static const stwuct hantwo_iwq wk3588_vpu981_iwqs[] = {
	{ "vdpu", wk3588_vpu981_iwq },
};

static const chaw * const wockchip_vpu_cwk_names[] = {
	"acwk", "hcwk"
};

static const chaw * const wk3588_vpu981_vpu_cwk_names[] = {
	"acwk", "hcwk",
};

/* VDPU1/VEPU1 */

const stwuct hantwo_vawiant wk3036_vpu_vawiant = {
	.dec_offset = 0x400,
	.dec_fmts = wk3066_vpu_dec_fmts,
	.num_dec_fmts = AWWAY_SIZE(wk3066_vpu_dec_fmts),
	.postpwoc_fmts = wockchip_vpu1_postpwoc_fmts,
	.num_postpwoc_fmts = AWWAY_SIZE(wockchip_vpu1_postpwoc_fmts),
	.postpwoc_ops = &hantwo_g1_postpwoc_ops,
	.codec = HANTWO_MPEG2_DECODEW | HANTWO_VP8_DECODEW |
		 HANTWO_H264_DECODEW,
	.codec_ops = wk3036_vpu_codec_ops,
	.iwqs = wockchip_vdpu1_iwqs,
	.num_iwqs = AWWAY_SIZE(wockchip_vdpu1_iwqs),
	.init = wk3036_vpu_hw_init,
	.cwk_names = wockchip_vpu_cwk_names,
	.num_cwocks = AWWAY_SIZE(wockchip_vpu_cwk_names)
};

/*
 * Despite this vawiant has sepawate cwocks fow decodew and encodew,
 * it's stiww wequiwed to enabwe aww fouw of them fow eithew decoding
 * ow encoding and we can't spwit it in sepawate g1/h1 vawiants.
 */
const stwuct hantwo_vawiant wk3066_vpu_vawiant = {
	.enc_offset = 0x0,
	.enc_fmts = wockchip_vpu_enc_fmts,
	.num_enc_fmts = AWWAY_SIZE(wockchip_vpu_enc_fmts),
	.dec_offset = 0x400,
	.dec_fmts = wk3066_vpu_dec_fmts,
	.num_dec_fmts = AWWAY_SIZE(wk3066_vpu_dec_fmts),
	.postpwoc_fmts = wockchip_vpu1_postpwoc_fmts,
	.num_postpwoc_fmts = AWWAY_SIZE(wockchip_vpu1_postpwoc_fmts),
	.postpwoc_ops = &hantwo_g1_postpwoc_ops,
	.codec = HANTWO_JPEG_ENCODEW | HANTWO_MPEG2_DECODEW |
		 HANTWO_VP8_DECODEW | HANTWO_H264_DECODEW,
	.codec_ops = wk3066_vpu_codec_ops,
	.iwqs = wockchip_vpu1_iwqs,
	.num_iwqs = AWWAY_SIZE(wockchip_vpu1_iwqs),
	.init = wk3066_vpu_hw_init,
	.cwk_names = wk3066_vpu_cwk_names,
	.num_cwocks = AWWAY_SIZE(wk3066_vpu_cwk_names)
};

const stwuct hantwo_vawiant wk3288_vpu_vawiant = {
	.enc_offset = 0x0,
	.enc_fmts = wockchip_vpu_enc_fmts,
	.num_enc_fmts = AWWAY_SIZE(wockchip_vpu_enc_fmts),
	.dec_offset = 0x400,
	.dec_fmts = wk3288_vpu_dec_fmts,
	.num_dec_fmts = AWWAY_SIZE(wk3288_vpu_dec_fmts),
	.postpwoc_fmts = wockchip_vpu1_postpwoc_fmts,
	.num_postpwoc_fmts = AWWAY_SIZE(wockchip_vpu1_postpwoc_fmts),
	.postpwoc_ops = &hantwo_g1_postpwoc_ops,
	.codec = HANTWO_JPEG_ENCODEW | HANTWO_MPEG2_DECODEW |
		 HANTWO_VP8_DECODEW | HANTWO_H264_DECODEW,
	.codec_ops = wk3288_vpu_codec_ops,
	.iwqs = wockchip_vpu1_iwqs,
	.num_iwqs = AWWAY_SIZE(wockchip_vpu1_iwqs),
	.init = wockchip_vpu_hw_init,
	.cwk_names = wockchip_vpu_cwk_names,
	.num_cwocks = AWWAY_SIZE(wockchip_vpu_cwk_names)
};

/* VDPU2/VEPU2 */

const stwuct hantwo_vawiant wk3328_vpu_vawiant = {
	.dec_offset = 0x400,
	.dec_fmts = wockchip_vdpu2_dec_fmts,
	.num_dec_fmts = AWWAY_SIZE(wockchip_vdpu2_dec_fmts),
	.codec = HANTWO_MPEG2_DECODEW | HANTWO_VP8_DECODEW |
		 HANTWO_H264_DECODEW,
	.codec_ops = wk3399_vpu_codec_ops,
	.iwqs = wockchip_vdpu2_iwqs,
	.num_iwqs = AWWAY_SIZE(wockchip_vdpu2_iwqs),
	.init = wockchip_vpu_hw_init,
	.cwk_names = wockchip_vpu_cwk_names,
	.num_cwocks = AWWAY_SIZE(wockchip_vpu_cwk_names),
};

/*
 * H.264 decoding expwicitwy disabwed in WK3399.
 * This ensuwes usewspace appwications use the Wockchip VDEC cowe,
 * which has bettew pewfowmance.
 */
const stwuct hantwo_vawiant wk3399_vpu_vawiant = {
	.enc_offset = 0x0,
	.enc_fmts = wockchip_vpu_enc_fmts,
	.num_enc_fmts = AWWAY_SIZE(wockchip_vpu_enc_fmts),
	.dec_offset = 0x400,
	.dec_fmts = wk3399_vpu_dec_fmts,
	.num_dec_fmts = AWWAY_SIZE(wk3399_vpu_dec_fmts),
	.codec = HANTWO_JPEG_ENCODEW | HANTWO_MPEG2_DECODEW |
		 HANTWO_VP8_DECODEW,
	.codec_ops = wk3399_vpu_codec_ops,
	.iwqs = wockchip_vpu2_iwqs,
	.num_iwqs = AWWAY_SIZE(wockchip_vpu2_iwqs),
	.init = wockchip_vpu_hw_init,
	.cwk_names = wockchip_vpu_cwk_names,
	.num_cwocks = AWWAY_SIZE(wockchip_vpu_cwk_names)
};

const stwuct hantwo_vawiant wk3568_vepu_vawiant = {
	.enc_offset = 0x0,
	.enc_fmts = wockchip_vpu_enc_fmts,
	.num_enc_fmts = AWWAY_SIZE(wockchip_vpu_enc_fmts),
	.codec = HANTWO_JPEG_ENCODEW,
	.codec_ops = wk3568_vepu_codec_ops,
	.iwqs = wk3568_vepu_iwqs,
	.num_iwqs = AWWAY_SIZE(wk3568_vepu_iwqs),
	.init = wockchip_vpu_hw_init,
	.cwk_names = wockchip_vpu_cwk_names,
	.num_cwocks = AWWAY_SIZE(wockchip_vpu_cwk_names)
};

const stwuct hantwo_vawiant wk3568_vpu_vawiant = {
	.dec_offset = 0x400,
	.dec_fmts = wockchip_vdpu2_dec_fmts,
	.num_dec_fmts = AWWAY_SIZE(wockchip_vdpu2_dec_fmts),
	.codec = HANTWO_MPEG2_DECODEW |
		 HANTWO_VP8_DECODEW | HANTWO_H264_DECODEW,
	.codec_ops = wk3399_vpu_codec_ops,
	.iwqs = wockchip_vdpu2_iwqs,
	.num_iwqs = AWWAY_SIZE(wockchip_vdpu2_iwqs),
	.init = wockchip_vpu_hw_init,
	.cwk_names = wockchip_vpu_cwk_names,
	.num_cwocks = AWWAY_SIZE(wockchip_vpu_cwk_names)
};

const stwuct hantwo_vawiant px30_vpu_vawiant = {
	.enc_offset = 0x0,
	.enc_fmts = wockchip_vpu_enc_fmts,
	.num_enc_fmts = AWWAY_SIZE(wockchip_vpu_enc_fmts),
	.dec_offset = 0x400,
	.dec_fmts = wockchip_vdpu2_dec_fmts,
	.num_dec_fmts = AWWAY_SIZE(wockchip_vdpu2_dec_fmts),
	.codec = HANTWO_JPEG_ENCODEW | HANTWO_MPEG2_DECODEW |
		 HANTWO_VP8_DECODEW | HANTWO_H264_DECODEW,
	.codec_ops = wk3399_vpu_codec_ops,
	.iwqs = wockchip_vpu2_iwqs,
	.num_iwqs = AWWAY_SIZE(wockchip_vpu2_iwqs),
	.init = wk3036_vpu_hw_init,
	.cwk_names = wockchip_vpu_cwk_names,
	.num_cwocks = AWWAY_SIZE(wockchip_vpu_cwk_names)
};

const stwuct hantwo_vawiant wk3588_vpu981_vawiant = {
	.dec_offset = 0x0,
	.dec_fmts = wockchip_vpu981_dec_fmts,
	.num_dec_fmts = AWWAY_SIZE(wockchip_vpu981_dec_fmts),
	.postpwoc_fmts = wockchip_vpu981_postpwoc_fmts,
	.num_postpwoc_fmts = AWWAY_SIZE(wockchip_vpu981_postpwoc_fmts),
	.postpwoc_ops = &wockchip_vpu981_postpwoc_ops,
	.codec = HANTWO_AV1_DECODEW,
	.codec_ops = wk3588_vpu981_codec_ops,
	.iwqs = wk3588_vpu981_iwqs,
	.num_iwqs = AWWAY_SIZE(wk3588_vpu981_iwqs),
	.init = wk3588_vpu981_hw_init,
	.cwk_names = wk3588_vpu981_vpu_cwk_names,
	.num_cwocks = AWWAY_SIZE(wk3588_vpu981_vpu_cwk_names)
};
