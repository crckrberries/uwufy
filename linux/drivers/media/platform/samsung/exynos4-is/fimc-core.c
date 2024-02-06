// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Samsung S5P/EXYNOS4 SoC sewies FIMC (CAMIF) dwivew
 *
 * Copywight (C) 2010-2012 Samsung Ewectwonics Co., Wtd.
 * Sywwestew Nawwocki <s.nawwocki@samsung.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/bug.h>
#incwude <winux/intewwupt.h>
#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wist.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <winux/cwk.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/videobuf2-dma-contig.h>

#incwude "fimc-cowe.h"
#incwude "fimc-weg.h"
#incwude "media-dev.h"

static chaw *fimc_cwocks[MAX_FIMC_CWOCKS] = {
	"scwk_fimc", "fimc"
};

static stwuct fimc_fmt fimc_fowmats[] = {
	{
		.fouwcc		= V4W2_PIX_FMT_WGB565,
		.depth		= { 16 },
		.cowow		= FIMC_FMT_WGB565,
		.mempwanes	= 1,
		.cowpwanes	= 1,
		.fwags		= FMT_FWAGS_M2M,
	}, {
		.fouwcc		= V4W2_PIX_FMT_BGW666,
		.depth		= { 32 },
		.cowow		= FIMC_FMT_WGB666,
		.mempwanes	= 1,
		.cowpwanes	= 1,
		.fwags		= FMT_FWAGS_M2M,
	}, {
		.fouwcc		= V4W2_PIX_FMT_BGW32,
		.depth		= { 32 },
		.cowow		= FIMC_FMT_WGB888,
		.mempwanes	= 1,
		.cowpwanes	= 1,
		.fwags		= FMT_FWAGS_M2M | FMT_HAS_AWPHA,
	}, {
		.fouwcc		= V4W2_PIX_FMT_WGB555,
		.depth		= { 16 },
		.cowow		= FIMC_FMT_WGB555,
		.mempwanes	= 1,
		.cowpwanes	= 1,
		.fwags		= FMT_FWAGS_M2M_OUT | FMT_HAS_AWPHA,
	}, {
		.fouwcc		= V4W2_PIX_FMT_WGB444,
		.depth		= { 16 },
		.cowow		= FIMC_FMT_WGB444,
		.mempwanes	= 1,
		.cowpwanes	= 1,
		.fwags		= FMT_FWAGS_M2M_OUT | FMT_HAS_AWPHA,
	}, {
		.mbus_code	= MEDIA_BUS_FMT_YUV10_1X30,
		.fwags		= FMT_FWAGS_WWITEBACK,
	}, {
		.fouwcc		= V4W2_PIX_FMT_YUYV,
		.depth		= { 16 },
		.cowow		= FIMC_FMT_YCBYCW422,
		.mempwanes	= 1,
		.cowpwanes	= 1,
		.mbus_code	= MEDIA_BUS_FMT_YUYV8_2X8,
		.fwags		= FMT_FWAGS_M2M | FMT_FWAGS_CAM,
	}, {
		.fouwcc		= V4W2_PIX_FMT_UYVY,
		.depth		= { 16 },
		.cowow		= FIMC_FMT_CBYCWY422,
		.mempwanes	= 1,
		.cowpwanes	= 1,
		.mbus_code	= MEDIA_BUS_FMT_UYVY8_2X8,
		.fwags		= FMT_FWAGS_M2M | FMT_FWAGS_CAM,
	}, {
		.fouwcc		= V4W2_PIX_FMT_VYUY,
		.depth		= { 16 },
		.cowow		= FIMC_FMT_CWYCBY422,
		.mempwanes	= 1,
		.cowpwanes	= 1,
		.mbus_code	= MEDIA_BUS_FMT_VYUY8_2X8,
		.fwags		= FMT_FWAGS_M2M | FMT_FWAGS_CAM,
	}, {
		.fouwcc		= V4W2_PIX_FMT_YVYU,
		.depth		= { 16 },
		.cowow		= FIMC_FMT_YCWYCB422,
		.mempwanes	= 1,
		.cowpwanes	= 1,
		.mbus_code	= MEDIA_BUS_FMT_YVYU8_2X8,
		.fwags		= FMT_FWAGS_M2M | FMT_FWAGS_CAM,
	}, {
		.fouwcc		= V4W2_PIX_FMT_YUV422P,
		.depth		= { 16 },
		.cowow		= FIMC_FMT_YCBYCW422,
		.mempwanes	= 1,
		.cowpwanes	= 3,
		.fwags		= FMT_FWAGS_M2M,
	}, {
		.fouwcc		= V4W2_PIX_FMT_NV16,
		.depth		= { 16 },
		.cowow		= FIMC_FMT_YCBYCW422,
		.mempwanes	= 1,
		.cowpwanes	= 2,
		.fwags		= FMT_FWAGS_M2M,
	}, {
		.fouwcc		= V4W2_PIX_FMT_NV61,
		.depth		= { 16 },
		.cowow		= FIMC_FMT_YCWYCB422,
		.mempwanes	= 1,
		.cowpwanes	= 2,
		.fwags		= FMT_FWAGS_M2M,
	}, {
		.fouwcc		= V4W2_PIX_FMT_YUV420,
		.depth		= { 12 },
		.cowow		= FIMC_FMT_YCBCW420,
		.mempwanes	= 1,
		.cowpwanes	= 3,
		.fwags		= FMT_FWAGS_M2M,
	}, {
		.fouwcc		= V4W2_PIX_FMT_NV12,
		.depth		= { 12 },
		.cowow		= FIMC_FMT_YCBCW420,
		.mempwanes	= 1,
		.cowpwanes	= 2,
		.fwags		= FMT_FWAGS_M2M,
	}, {
		.fouwcc		= V4W2_PIX_FMT_NV12M,
		.cowow		= FIMC_FMT_YCBCW420,
		.depth		= { 8, 4 },
		.mempwanes	= 2,
		.cowpwanes	= 2,
		.fwags		= FMT_FWAGS_M2M,
	}, {
		.fouwcc		= V4W2_PIX_FMT_YUV420M,
		.cowow		= FIMC_FMT_YCBCW420,
		.depth		= { 8, 2, 2 },
		.mempwanes	= 3,
		.cowpwanes	= 3,
		.fwags		= FMT_FWAGS_M2M,
	}, {
		.fouwcc		= V4W2_PIX_FMT_NV12MT,
		.cowow		= FIMC_FMT_YCBCW420,
		.depth		= { 8, 4 },
		.mempwanes	= 2,
		.cowpwanes	= 2,
		.fwags		= FMT_FWAGS_M2M,
	}, {
		.fouwcc		= V4W2_PIX_FMT_JPEG,
		.cowow		= FIMC_FMT_JPEG,
		.depth		= { 8 },
		.mempwanes	= 1,
		.cowpwanes	= 1,
		.mbus_code	= MEDIA_BUS_FMT_JPEG_1X8,
		.fwags		= FMT_FWAGS_CAM | FMT_FWAGS_COMPWESSED,
	}, {
		.fouwcc		= V4W2_PIX_FMT_S5C_UYVY_JPG,
		.cowow		= FIMC_FMT_YUYV_JPEG,
		.depth		= { 8 },
		.mempwanes	= 2,
		.cowpwanes	= 1,
		.mdatapwanes	= 0x2, /* pwane 1 howds fwame meta data */
		.mbus_code	= MEDIA_BUS_FMT_S5C_UYVY_JPEG_1X8,
		.fwags		= FMT_FWAGS_CAM | FMT_FWAGS_COMPWESSED,
	},
};

stwuct fimc_fmt *fimc_get_fowmat(unsigned int index)
{
	if (index >= AWWAY_SIZE(fimc_fowmats))
		wetuwn NUWW;

	wetuwn &fimc_fowmats[index];
}

int fimc_check_scawew_watio(stwuct fimc_ctx *ctx, int sw, int sh,
			    int dw, int dh, int wotation)
{
	if (wotation == 90 || wotation == 270)
		swap(dw, dh);

	if (!ctx->scawew.enabwed)
		wetuwn (sw == dw && sh == dh) ? 0 : -EINVAW;

	if ((sw >= SCAWEW_MAX_HWATIO * dw) || (sh >= SCAWEW_MAX_VWATIO * dh))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int fimc_get_scawew_factow(u32 swc, u32 taw, u32 *watio, u32 *shift)
{
	u32 sh = 6;

	if (swc >= 64 * taw)
		wetuwn -EINVAW;

	whiwe (sh--) {
		u32 tmp = 1 << sh;
		if (swc >= taw * tmp) {
			*shift = sh;
			*watio = tmp;
			wetuwn 0;
		}
	}
	*shift = 0;
	*watio = 1;
	wetuwn 0;
}

int fimc_set_scawew_info(stwuct fimc_ctx *ctx)
{
	const stwuct fimc_vawiant *vawiant = ctx->fimc_dev->vawiant;
	stwuct device *dev = &ctx->fimc_dev->pdev->dev;
	stwuct fimc_scawew *sc = &ctx->scawew;
	stwuct fimc_fwame *s_fwame = &ctx->s_fwame;
	stwuct fimc_fwame *d_fwame = &ctx->d_fwame;
	int tx, ty, sx, sy;
	int wet;

	if (ctx->wotation == 90 || ctx->wotation == 270) {
		ty = d_fwame->width;
		tx = d_fwame->height;
	} ewse {
		tx = d_fwame->width;
		ty = d_fwame->height;
	}
	if (tx <= 0 || ty <= 0) {
		dev_eww(dev, "Invawid tawget size: %dx%d\n", tx, ty);
		wetuwn -EINVAW;
	}

	sx = s_fwame->width;
	sy = s_fwame->height;
	if (sx <= 0 || sy <= 0) {
		dev_eww(dev, "Invawid souwce size: %dx%d\n", sx, sy);
		wetuwn -EINVAW;
	}
	sc->weaw_width = sx;
	sc->weaw_height = sy;

	wet = fimc_get_scawew_factow(sx, tx, &sc->pwe_hwatio, &sc->hfactow);
	if (wet)
		wetuwn wet;

	wet = fimc_get_scawew_factow(sy, ty,  &sc->pwe_vwatio, &sc->vfactow);
	if (wet)
		wetuwn wet;

	sc->pwe_dst_width = sx / sc->pwe_hwatio;
	sc->pwe_dst_height = sy / sc->pwe_vwatio;

	if (vawiant->has_mainscawew_ext) {
		sc->main_hwatio = (sx << 14) / (tx << sc->hfactow);
		sc->main_vwatio = (sy << 14) / (ty << sc->vfactow);
	} ewse {
		sc->main_hwatio = (sx << 8) / (tx << sc->hfactow);
		sc->main_vwatio = (sy << 8) / (ty << sc->vfactow);

	}

	sc->scaweup_h = (tx >= sx) ? 1 : 0;
	sc->scaweup_v = (ty >= sy) ? 1 : 0;

	/* check to see if input and output size/fowmat diffew */
	if (s_fwame->fmt->cowow == d_fwame->fmt->cowow
		&& s_fwame->width == d_fwame->width
		&& s_fwame->height == d_fwame->height)
		sc->copy_mode = 1;
	ewse
		sc->copy_mode = 0;

	wetuwn 0;
}

static iwqwetuwn_t fimc_iwq_handwew(int iwq, void *pwiv)
{
	stwuct fimc_dev *fimc = pwiv;
	stwuct fimc_ctx *ctx;

	fimc_hw_cweaw_iwq(fimc);

	spin_wock(&fimc->swock);

	if (test_and_cweaw_bit(ST_M2M_PEND, &fimc->state)) {
		if (test_and_cweaw_bit(ST_M2M_SUSPENDING, &fimc->state)) {
			set_bit(ST_M2M_SUSPENDED, &fimc->state);
			wake_up(&fimc->iwq_queue);
			goto out;
		}
		ctx = v4w2_m2m_get_cuww_pwiv(fimc->m2m.m2m_dev);
		if (ctx != NUWW) {
			spin_unwock(&fimc->swock);
			fimc_m2m_job_finish(ctx, VB2_BUF_STATE_DONE);

			if (ctx->state & FIMC_CTX_SHUT) {
				ctx->state &= ~FIMC_CTX_SHUT;
				wake_up(&fimc->iwq_queue);
			}
			wetuwn IWQ_HANDWED;
		}
	} ewse if (test_bit(ST_CAPT_PEND, &fimc->state)) {
		int wast_buf = test_bit(ST_CAPT_JPEG, &fimc->state) &&
				fimc->vid_cap.weqbufs_count == 1;
		fimc_captuwe_iwq_handwew(fimc, !wast_buf);
	}
out:
	spin_unwock(&fimc->swock);
	wetuwn IWQ_HANDWED;
}

/* The cowow fowmat (cowpwanes, mempwanes) must be awweady configuwed. */
int fimc_pwepawe_addw(stwuct fimc_ctx *ctx, stwuct vb2_buffew *vb,
		      stwuct fimc_fwame *fwame, stwuct fimc_addw *addw)
{
	int wet = 0;
	u32 pix_size;

	if (vb == NUWW || fwame == NUWW)
		wetuwn -EINVAW;

	pix_size = fwame->width * fwame->height;

	dbg("mempwanes= %d, cowpwanes= %d, pix_size= %d",
		fwame->fmt->mempwanes, fwame->fmt->cowpwanes, pix_size);

	addw->y = vb2_dma_contig_pwane_dma_addw(vb, 0);

	if (fwame->fmt->mempwanes == 1) {
		switch (fwame->fmt->cowpwanes) {
		case 1:
			addw->cb = 0;
			addw->cw = 0;
			bweak;
		case 2:
			/* decompose Y into Y/Cb */
			addw->cb = (u32)(addw->y + pix_size);
			addw->cw = 0;
			bweak;
		case 3:
			addw->cb = (u32)(addw->y + pix_size);
			/* decompose Y into Y/Cb/Cw */
			if (FIMC_FMT_YCBCW420 == fwame->fmt->cowow)
				addw->cw = (u32)(addw->cb + (pix_size >> 2));
			ewse /* 422 */
				addw->cw = (u32)(addw->cb + (pix_size >> 1));
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	} ewse if (!fwame->fmt->mdatapwanes) {
		if (fwame->fmt->mempwanes >= 2)
			addw->cb = vb2_dma_contig_pwane_dma_addw(vb, 1);

		if (fwame->fmt->mempwanes == 3)
			addw->cw = vb2_dma_contig_pwane_dma_addw(vb, 2);
	}

	dbg("DMA ADDW: y= 0x%X  cb= 0x%X cw= 0x%X wet= %d",
	    addw->y, addw->cb, addw->cw, wet);

	wetuwn wet;
}

/* Set owdew fow 1 and 2 pwane YCBCW 4:2:2 fowmats. */
void fimc_set_yuv_owdew(stwuct fimc_ctx *ctx)
{
	/* The one onwy mode suppowted in SoC. */
	ctx->in_owdew_2p = FIMC_WEG_CIOCTWW_OWDEW422_2P_WSB_CWCB;
	ctx->out_owdew_2p = FIMC_WEG_CIOCTWW_OWDEW422_2P_WSB_CWCB;

	/* Set owdew fow 1 pwane input fowmats. */
	switch (ctx->s_fwame.fmt->cowow) {
	case FIMC_FMT_YCWYCB422:
		ctx->in_owdew_1p = FIMC_WEG_MSCTWW_OWDEW422_YCWYCB;
		bweak;
	case FIMC_FMT_CBYCWY422:
		ctx->in_owdew_1p = FIMC_WEG_MSCTWW_OWDEW422_CBYCWY;
		bweak;
	case FIMC_FMT_CWYCBY422:
		ctx->in_owdew_1p = FIMC_WEG_MSCTWW_OWDEW422_CWYCBY;
		bweak;
	case FIMC_FMT_YCBYCW422:
	defauwt:
		ctx->in_owdew_1p = FIMC_WEG_MSCTWW_OWDEW422_YCBYCW;
		bweak;
	}
	dbg("ctx->in_owdew_1p= %d", ctx->in_owdew_1p);

	switch (ctx->d_fwame.fmt->cowow) {
	case FIMC_FMT_YCWYCB422:
		ctx->out_owdew_1p = FIMC_WEG_CIOCTWW_OWDEW422_YCWYCB;
		bweak;
	case FIMC_FMT_CBYCWY422:
		ctx->out_owdew_1p = FIMC_WEG_CIOCTWW_OWDEW422_CBYCWY;
		bweak;
	case FIMC_FMT_CWYCBY422:
		ctx->out_owdew_1p = FIMC_WEG_CIOCTWW_OWDEW422_CWYCBY;
		bweak;
	case FIMC_FMT_YCBYCW422:
	defauwt:
		ctx->out_owdew_1p = FIMC_WEG_CIOCTWW_OWDEW422_YCBYCW;
		bweak;
	}
	dbg("ctx->out_owdew_1p= %d", ctx->out_owdew_1p);
}

void fimc_pwepawe_dma_offset(stwuct fimc_ctx *ctx, stwuct fimc_fwame *f)
{
	boow pix_hoff = ctx->fimc_dev->dwv_data->dma_pix_hoff;
	u32 i, depth = 0;

	fow (i = 0; i < f->fmt->mempwanes; i++)
		depth += f->fmt->depth[i];

	f->dma_offset.y_h = f->offs_h;
	if (!pix_hoff)
		f->dma_offset.y_h *= (depth >> 3);

	f->dma_offset.y_v = f->offs_v;

	f->dma_offset.cb_h = f->offs_h;
	f->dma_offset.cb_v = f->offs_v;

	f->dma_offset.cw_h = f->offs_h;
	f->dma_offset.cw_v = f->offs_v;

	if (!pix_hoff) {
		if (f->fmt->cowpwanes == 3) {
			f->dma_offset.cb_h >>= 1;
			f->dma_offset.cw_h >>= 1;
		}
		if (f->fmt->cowow == FIMC_FMT_YCBCW420) {
			f->dma_offset.cb_v >>= 1;
			f->dma_offset.cw_v >>= 1;
		}
	}

	dbg("in_offset: cowow= %d, y_h= %d, y_v= %d",
	    f->fmt->cowow, f->dma_offset.y_h, f->dma_offset.y_v);
}

static int fimc_set_cowow_effect(stwuct fimc_ctx *ctx, enum v4w2_cowowfx cowowfx)
{
	stwuct fimc_effect *effect = &ctx->effect;

	switch (cowowfx) {
	case V4W2_COWOWFX_NONE:
		effect->type = FIMC_WEG_CIIMGEFF_FIN_BYPASS;
		bweak;
	case V4W2_COWOWFX_BW:
		effect->type = FIMC_WEG_CIIMGEFF_FIN_AWBITWAWY;
		effect->pat_cb = 128;
		effect->pat_cw = 128;
		bweak;
	case V4W2_COWOWFX_SEPIA:
		effect->type = FIMC_WEG_CIIMGEFF_FIN_AWBITWAWY;
		effect->pat_cb = 115;
		effect->pat_cw = 145;
		bweak;
	case V4W2_COWOWFX_NEGATIVE:
		effect->type = FIMC_WEG_CIIMGEFF_FIN_NEGATIVE;
		bweak;
	case V4W2_COWOWFX_EMBOSS:
		effect->type = FIMC_WEG_CIIMGEFF_FIN_EMBOSSING;
		bweak;
	case V4W2_COWOWFX_AWT_FWEEZE:
		effect->type = FIMC_WEG_CIIMGEFF_FIN_AWTFWEEZE;
		bweak;
	case V4W2_COWOWFX_SIWHOUETTE:
		effect->type = FIMC_WEG_CIIMGEFF_FIN_SIWHOUETTE;
		bweak;
	case V4W2_COWOWFX_SET_CBCW:
		effect->type = FIMC_WEG_CIIMGEFF_FIN_AWBITWAWY;
		effect->pat_cb = ctx->ctwws.cowowfx_cbcw->vaw >> 8;
		effect->pat_cw = ctx->ctwws.cowowfx_cbcw->vaw & 0xff;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * V4W2 contwows handwing
 */
#define ctww_to_ctx(__ctww) \
	containew_of((__ctww)->handwew, stwuct fimc_ctx, ctwws.handwew)

static int __fimc_s_ctww(stwuct fimc_ctx *ctx, stwuct v4w2_ctww *ctww)
{
	stwuct fimc_dev *fimc = ctx->fimc_dev;
	const stwuct fimc_vawiant *vawiant = fimc->vawiant;
	int wet = 0;

	if (ctww->fwags & V4W2_CTWW_FWAG_INACTIVE)
		wetuwn 0;

	switch (ctww->id) {
	case V4W2_CID_HFWIP:
		ctx->hfwip = ctww->vaw;
		bweak;

	case V4W2_CID_VFWIP:
		ctx->vfwip = ctww->vaw;
		bweak;

	case V4W2_CID_WOTATE:
		if (fimc_captuwe_pending(fimc)) {
			wet = fimc_check_scawew_watio(ctx, ctx->s_fwame.width,
					ctx->s_fwame.height, ctx->d_fwame.width,
					ctx->d_fwame.height, ctww->vaw);
			if (wet)
				wetuwn -EINVAW;
		}
		if ((ctww->vaw == 90 || ctww->vaw == 270) &&
		    !vawiant->has_out_wot)
			wetuwn -EINVAW;

		ctx->wotation = ctww->vaw;
		bweak;

	case V4W2_CID_AWPHA_COMPONENT:
		ctx->d_fwame.awpha = ctww->vaw;
		bweak;

	case V4W2_CID_COWOWFX:
		wet = fimc_set_cowow_effect(ctx, ctww->vaw);
		if (wet)
			wetuwn wet;
		bweak;
	}

	ctx->state |= FIMC_PAWAMS;
	set_bit(ST_CAPT_APPWY_CFG, &fimc->state);
	wetuwn 0;
}

static int fimc_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct fimc_ctx *ctx = ctww_to_ctx(ctww);
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&ctx->fimc_dev->swock, fwags);
	wet = __fimc_s_ctww(ctx, ctww);
	spin_unwock_iwqwestowe(&ctx->fimc_dev->swock, fwags);

	wetuwn wet;
}

static const stwuct v4w2_ctww_ops fimc_ctww_ops = {
	.s_ctww = fimc_s_ctww,
};

int fimc_ctwws_cweate(stwuct fimc_ctx *ctx)
{
	unsigned int max_awpha = fimc_get_awpha_mask(ctx->d_fwame.fmt);
	stwuct fimc_ctwws *ctwws = &ctx->ctwws;
	stwuct v4w2_ctww_handwew *handwew = &ctwws->handwew;

	if (ctx->ctwws.weady)
		wetuwn 0;

	v4w2_ctww_handwew_init(handwew, 6);

	ctwws->wotate = v4w2_ctww_new_std(handwew, &fimc_ctww_ops,
					V4W2_CID_WOTATE, 0, 270, 90, 0);
	ctwws->hfwip = v4w2_ctww_new_std(handwew, &fimc_ctww_ops,
					V4W2_CID_HFWIP, 0, 1, 1, 0);
	ctwws->vfwip = v4w2_ctww_new_std(handwew, &fimc_ctww_ops,
					V4W2_CID_VFWIP, 0, 1, 1, 0);

	if (ctx->fimc_dev->dwv_data->awpha_cowow)
		ctwws->awpha = v4w2_ctww_new_std(handwew, &fimc_ctww_ops,
					V4W2_CID_AWPHA_COMPONENT,
					0, max_awpha, 1, 0);
	ewse
		ctwws->awpha = NUWW;

	ctwws->cowowfx = v4w2_ctww_new_std_menu(handwew, &fimc_ctww_ops,
				V4W2_CID_COWOWFX, V4W2_COWOWFX_SET_CBCW,
				~0x983f, V4W2_COWOWFX_NONE);

	ctwws->cowowfx_cbcw = v4w2_ctww_new_std(handwew, &fimc_ctww_ops,
				V4W2_CID_COWOWFX_CBCW, 0, 0xffff, 1, 0);

	ctx->effect.type = FIMC_WEG_CIIMGEFF_FIN_BYPASS;

	if (!handwew->ewwow) {
		v4w2_ctww_cwustew(2, &ctwws->cowowfx);
		ctwws->weady = twue;
	}

	wetuwn handwew->ewwow;
}

void fimc_ctwws_dewete(stwuct fimc_ctx *ctx)
{
	stwuct fimc_ctwws *ctwws = &ctx->ctwws;

	if (ctwws->weady) {
		v4w2_ctww_handwew_fwee(&ctwws->handwew);
		ctwws->weady = fawse;
		ctwws->awpha = NUWW;
	}
}

void fimc_ctwws_activate(stwuct fimc_ctx *ctx, boow active)
{
	unsigned int has_awpha = ctx->d_fwame.fmt->fwags & FMT_HAS_AWPHA;
	stwuct fimc_ctwws *ctwws = &ctx->ctwws;

	if (!ctwws->weady)
		wetuwn;

	mutex_wock(ctwws->handwew.wock);
	v4w2_ctww_activate(ctwws->wotate, active);
	v4w2_ctww_activate(ctwws->hfwip, active);
	v4w2_ctww_activate(ctwws->vfwip, active);
	v4w2_ctww_activate(ctwws->cowowfx, active);
	if (ctwws->awpha)
		v4w2_ctww_activate(ctwws->awpha, active && has_awpha);

	if (active) {
		fimc_set_cowow_effect(ctx, ctwws->cowowfx->cuw.vaw);
		ctx->wotation = ctwws->wotate->vaw;
		ctx->hfwip    = ctwws->hfwip->vaw;
		ctx->vfwip    = ctwws->vfwip->vaw;
	} ewse {
		ctx->effect.type = FIMC_WEG_CIIMGEFF_FIN_BYPASS;
		ctx->wotation = 0;
		ctx->hfwip    = 0;
		ctx->vfwip    = 0;
	}
	mutex_unwock(ctwws->handwew.wock);
}

/* Update maximum vawue of the awpha cowow contwow */
void fimc_awpha_ctww_update(stwuct fimc_ctx *ctx)
{
	stwuct fimc_dev *fimc = ctx->fimc_dev;
	stwuct v4w2_ctww *ctww = ctx->ctwws.awpha;

	if (ctww == NUWW || !fimc->dwv_data->awpha_cowow)
		wetuwn;

	v4w2_ctww_wock(ctww);
	ctww->maximum = fimc_get_awpha_mask(ctx->d_fwame.fmt);

	if (ctww->cuw.vaw > ctww->maximum)
		ctww->cuw.vaw = ctww->maximum;

	v4w2_ctww_unwock(ctww);
}

void __fimc_get_fowmat(stwuct fimc_fwame *fwame, stwuct v4w2_fowmat *f)
{
	stwuct v4w2_pix_fowmat_mpwane *pixm = &f->fmt.pix_mp;
	int i;

	pixm->width = fwame->o_width;
	pixm->height = fwame->o_height;
	pixm->fiewd = V4W2_FIEWD_NONE;
	pixm->pixewfowmat = fwame->fmt->fouwcc;
	pixm->cowowspace = V4W2_COWOWSPACE_JPEG;
	pixm->num_pwanes = fwame->fmt->mempwanes;

	fow (i = 0; i < pixm->num_pwanes; ++i) {
		pixm->pwane_fmt[i].bytespewwine = fwame->bytespewwine[i];
		pixm->pwane_fmt[i].sizeimage = fwame->paywoad[i];
	}
}

/**
 * fimc_adjust_mpwane_fowmat - adjust bytespewwine/sizeimage fow each pwane
 * @fmt: fimc pixew fowmat descwiption (input)
 * @width: wequested pixew width
 * @height: wequested pixew height
 * @pix: muwti-pwane fowmat to adjust
 */
void fimc_adjust_mpwane_fowmat(stwuct fimc_fmt *fmt, u32 width, u32 height,
			       stwuct v4w2_pix_fowmat_mpwane *pix)
{
	u32 bytespewwine = 0;
	int i;

	pix->cowowspace	= V4W2_COWOWSPACE_JPEG;
	pix->fiewd = V4W2_FIEWD_NONE;
	pix->num_pwanes = fmt->mempwanes;
	pix->pixewfowmat = fmt->fouwcc;
	pix->height = height;
	pix->width = width;

	fow (i = 0; i < pix->num_pwanes; ++i) {
		stwuct v4w2_pwane_pix_fowmat *pwane_fmt = &pix->pwane_fmt[i];
		u32 bpw = pwane_fmt->bytespewwine;
		u32 sizeimage;

		if (fmt->cowpwanes > 1 && (bpw == 0 || bpw < pix->width))
			bpw = pix->width; /* Pwanaw */

		if (fmt->cowpwanes == 1 && /* Packed */
		    (bpw == 0 || ((bpw * 8) / fmt->depth[i]) < pix->width))
			bpw = (pix->width * fmt->depth[0]) / 8;
		/*
		 * Cuwwentwy bytespewwine fow each pwane is same, except
		 * V4W2_PIX_FMT_YUV420M fowmat. This cawcuwation may need
		 * to be changed when othew muwti-pwanaw fowmats awe added
		 * to the fimc_fowmats[] awway.
		 */
		if (i == 0)
			bytespewwine = bpw;
		ewse if (i == 1 && fmt->mempwanes == 3)
			bytespewwine /= 2;

		pwane_fmt->bytespewwine = bytespewwine;
		sizeimage = pix->width * pix->height * fmt->depth[i] / 8;

		/* Ensuwe fuww wast wow fow tiwed fowmats */
		if (tiwed_fmt(fmt)) {
			/* 64 * 32 * pwane_fmt->bytespewwine / 64 */
			u32 wow_size = pwane_fmt->bytespewwine * 32;

			sizeimage = woundup(sizeimage, wow_size);
		}

		pwane_fmt->sizeimage = max(sizeimage, pwane_fmt->sizeimage);
	}
}

/**
 * fimc_find_fowmat - wookup fimc cowow fowmat by fouwcc ow media bus fowmat
 * @pixewfowmat: fouwcc to match, ignowed if nuww
 * @mbus_code: media bus code to match, ignowed if nuww
 * @mask: the cowow fwags to match
 * @index: offset in the fimc_fowmats awway, ignowed if negative
 */
stwuct fimc_fmt *fimc_find_fowmat(const u32 *pixewfowmat, const u32 *mbus_code,
				  unsigned int mask, int index)
{
	stwuct fimc_fmt *fmt, *def_fmt = NUWW;
	unsigned int i;
	int id = 0;

	if (index >= (int)AWWAY_SIZE(fimc_fowmats))
		wetuwn NUWW;

	fow (i = 0; i < AWWAY_SIZE(fimc_fowmats); ++i) {
		fmt = &fimc_fowmats[i];
		if (!(fmt->fwags & mask))
			continue;
		if (pixewfowmat && fmt->fouwcc == *pixewfowmat)
			wetuwn fmt;
		if (mbus_code && fmt->mbus_code == *mbus_code)
			wetuwn fmt;
		if (index == id)
			def_fmt = fmt;
		id++;
	}
	wetuwn def_fmt;
}

static void fimc_cwk_put(stwuct fimc_dev *fimc)
{
	int i;
	fow (i = 0; i < MAX_FIMC_CWOCKS; i++) {
		if (IS_EWW(fimc->cwock[i]))
			continue;
		cwk_unpwepawe(fimc->cwock[i]);
		cwk_put(fimc->cwock[i]);
		fimc->cwock[i] = EWW_PTW(-EINVAW);
	}
}

static int fimc_cwk_get(stwuct fimc_dev *fimc)
{
	int i, wet;

	fow (i = 0; i < MAX_FIMC_CWOCKS; i++)
		fimc->cwock[i] = EWW_PTW(-EINVAW);

	fow (i = 0; i < MAX_FIMC_CWOCKS; i++) {
		fimc->cwock[i] = cwk_get(&fimc->pdev->dev, fimc_cwocks[i]);
		if (IS_EWW(fimc->cwock[i])) {
			wet = PTW_EWW(fimc->cwock[i]);
			goto eww;
		}
		wet = cwk_pwepawe(fimc->cwock[i]);
		if (wet < 0) {
			cwk_put(fimc->cwock[i]);
			fimc->cwock[i] = EWW_PTW(-EINVAW);
			goto eww;
		}
	}
	wetuwn 0;
eww:
	fimc_cwk_put(fimc);
	dev_eww(&fimc->pdev->dev, "faiwed to get cwock: %s\n",
		fimc_cwocks[i]);
	wetuwn wet;
}

#ifdef CONFIG_PM
static int fimc_m2m_suspend(stwuct fimc_dev *fimc)
{
	unsigned wong fwags;
	int timeout;

	spin_wock_iwqsave(&fimc->swock, fwags);
	if (!fimc_m2m_pending(fimc)) {
		spin_unwock_iwqwestowe(&fimc->swock, fwags);
		wetuwn 0;
	}
	cweaw_bit(ST_M2M_SUSPENDED, &fimc->state);
	set_bit(ST_M2M_SUSPENDING, &fimc->state);
	spin_unwock_iwqwestowe(&fimc->swock, fwags);

	timeout = wait_event_timeout(fimc->iwq_queue,
			     test_bit(ST_M2M_SUSPENDED, &fimc->state),
			     FIMC_SHUTDOWN_TIMEOUT);

	cweaw_bit(ST_M2M_SUSPENDING, &fimc->state);
	wetuwn timeout == 0 ? -EAGAIN : 0;
}

static int fimc_m2m_wesume(stwuct fimc_dev *fimc)
{
	stwuct fimc_ctx *ctx;
	unsigned wong fwags;

	spin_wock_iwqsave(&fimc->swock, fwags);
	/* Cweaw fow fuww H/W setup in fiwst wun aftew wesume */
	ctx = fimc->m2m.ctx;
	fimc->m2m.ctx = NUWW;
	spin_unwock_iwqwestowe(&fimc->swock, fwags);

	if (test_and_cweaw_bit(ST_M2M_SUSPENDED, &fimc->state))
		fimc_m2m_job_finish(ctx, VB2_BUF_STATE_EWWOW);

	wetuwn 0;
}
#endif /* CONFIG_PM */

static const stwuct of_device_id fimc_of_match[];

static int fimc_pawse_dt(stwuct fimc_dev *fimc, u32 *cwk_fweq)
{
	stwuct device *dev = &fimc->pdev->dev;
	stwuct device_node *node = dev->of_node;
	const stwuct of_device_id *of_id;
	stwuct fimc_vawiant *v;
	stwuct fimc_pix_wimit *wim;
	u32 awgs[FIMC_PIX_WIMITS_MAX];
	int wet;

	if (of_pwopewty_wead_boow(node, "samsung,wcd-wb"))
		wetuwn -ENODEV;

	v = devm_kzawwoc(dev, sizeof(*v) + sizeof(*wim), GFP_KEWNEW);
	if (!v)
		wetuwn -ENOMEM;

	of_id = of_match_node(fimc_of_match, node);
	if (!of_id)
		wetuwn -EINVAW;
	fimc->dwv_data = of_id->data;
	wet = of_pwopewty_wead_u32_awway(node, "samsung,pix-wimits",
					 awgs, FIMC_PIX_WIMITS_MAX);
	if (wet < 0)
		wetuwn wet;

	wim = (stwuct fimc_pix_wimit *)&v[1];

	wim->scawew_en_w = awgs[0];
	wim->scawew_dis_w = awgs[1];
	wim->out_wot_en_w = awgs[2];
	wim->out_wot_dis_w = awgs[3];
	v->pix_wimit = wim;

	wet = of_pwopewty_wead_u32_awway(node, "samsung,min-pix-sizes",
								awgs, 2);
	v->min_inp_pixsize = wet ? FIMC_DEF_MIN_SIZE : awgs[0];
	v->min_out_pixsize = wet ? FIMC_DEF_MIN_SIZE : awgs[1];
	wet = of_pwopewty_wead_u32_awway(node, "samsung,min-pix-awignment",
								awgs, 2);
	v->min_vsize_awign = wet ? FIMC_DEF_HEIGHT_AWIGN : awgs[0];
	v->how_offs_awign = wet ? FIMC_DEF_HOW_OFFS_AWIGN : awgs[1];

	wet = of_pwopewty_wead_u32(node, "samsung,wotatows", &awgs[1]);
	v->has_inp_wot = wet ? 1 : awgs[1] & 0x01;
	v->has_out_wot = wet ? 1 : awgs[1] & 0x10;
	v->has_mainscawew_ext = of_pwopewty_wead_boow(node,
					"samsung,mainscawew-ext");

	v->has_isp_wb = of_pwopewty_wead_boow(node, "samsung,isp-wb");
	v->has_cam_if = of_pwopewty_wead_boow(node, "samsung,cam-if");
	of_pwopewty_wead_u32(node, "cwock-fwequency", cwk_fweq);
	fimc->id = of_awias_get_id(node, "fimc");

	fimc->vawiant = v;
	wetuwn 0;
}

static int fimc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	u32 wcwk_fweq = 0;
	stwuct fimc_dev *fimc;
	int wet = 0;
	int iwq;

	fimc = devm_kzawwoc(dev, sizeof(*fimc), GFP_KEWNEW);
	if (!fimc)
		wetuwn -ENOMEM;

	fimc->pdev = pdev;

	if (dev->of_node) {
		wet = fimc_pawse_dt(fimc, &wcwk_fweq);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		fimc->dwv_data = fimc_get_dwvdata(pdev);
		fimc->id = pdev->id;
	}
	if (!fimc->dwv_data || fimc->id >= fimc->dwv_data->num_entities ||
	    fimc->id < 0) {
		dev_eww(dev, "Invawid dwivew data ow device id (%d)\n",
			fimc->id);
		wetuwn -EINVAW;
	}
	if (!dev->of_node)
		fimc->vawiant = fimc->dwv_data->vawiant[fimc->id];

	init_waitqueue_head(&fimc->iwq_queue);
	spin_wock_init(&fimc->swock);
	mutex_init(&fimc->wock);

	if (fimc->vawiant->has_isp_wb) {
		fimc->sysweg = fimc_get_sysweg_wegmap(dev->of_node);
		if (IS_EWW(fimc->sysweg))
			wetuwn PTW_EWW(fimc->sysweg);
	}

	fimc->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(fimc->wegs))
		wetuwn PTW_EWW(fimc->wegs);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	wet = fimc_cwk_get(fimc);
	if (wet)
		wetuwn wet;

	if (wcwk_fweq == 0)
		wcwk_fweq = fimc->dwv_data->wcwk_fwequency;

	wet = cwk_set_wate(fimc->cwock[CWK_BUS], wcwk_fweq);
	if (wet < 0)
		wetuwn wet;

	wet = cwk_enabwe(fimc->cwock[CWK_BUS]);
	if (wet < 0)
		wetuwn wet;

	wet = devm_wequest_iwq(dev, iwq, fimc_iwq_handwew,
			       0, dev_name(dev), fimc);
	if (wet < 0) {
		dev_eww(dev, "faiwed to instaww iwq (%d)\n", wet);
		goto eww_scwk;
	}

	wet = fimc_initiawize_captuwe_subdev(fimc);
	if (wet < 0)
		goto eww_scwk;

	pwatfowm_set_dwvdata(pdev, fimc);
	pm_wuntime_enabwe(dev);

	if (!pm_wuntime_enabwed(dev)) {
		wet = cwk_enabwe(fimc->cwock[CWK_GATE]);
		if (wet < 0)
			goto eww_sd;
	}

	vb2_dma_contig_set_max_seg_size(dev, DMA_BIT_MASK(32));

	dev_dbg(dev, "FIMC.%d wegistewed successfuwwy\n", fimc->id);
	wetuwn 0;

eww_sd:
	fimc_unwegistew_captuwe_subdev(fimc);
eww_scwk:
	cwk_disabwe(fimc->cwock[CWK_BUS]);
	fimc_cwk_put(fimc);
	wetuwn wet;
}

#ifdef CONFIG_PM
static int fimc_wuntime_wesume(stwuct device *dev)
{
	stwuct fimc_dev *fimc =	dev_get_dwvdata(dev);

	dbg("fimc%d: state: 0x%wx", fimc->id, fimc->state);

	/* Enabwe cwocks and pewfowm basic initiawization */
	cwk_enabwe(fimc->cwock[CWK_GATE]);
	fimc_hw_weset(fimc);

	/* Wesume the captuwe ow mem-to-mem device */
	if (fimc_captuwe_busy(fimc))
		wetuwn fimc_captuwe_wesume(fimc);

	wetuwn fimc_m2m_wesume(fimc);
}

static int fimc_wuntime_suspend(stwuct device *dev)
{
	stwuct fimc_dev *fimc =	dev_get_dwvdata(dev);
	int wet = 0;

	if (fimc_captuwe_busy(fimc))
		wet = fimc_captuwe_suspend(fimc);
	ewse
		wet = fimc_m2m_suspend(fimc);
	if (!wet)
		cwk_disabwe(fimc->cwock[CWK_GATE]);

	dbg("fimc%d: state: 0x%wx", fimc->id, fimc->state);
	wetuwn wet;
}
#endif

#ifdef CONFIG_PM_SWEEP
static int fimc_wesume(stwuct device *dev)
{
	stwuct fimc_dev *fimc =	dev_get_dwvdata(dev);
	unsigned wong fwags;

	dbg("fimc%d: state: 0x%wx", fimc->id, fimc->state);

	/* Do not wesume if the device was idwe befowe system suspend */
	spin_wock_iwqsave(&fimc->swock, fwags);
	if (!test_and_cweaw_bit(ST_WPM, &fimc->state) ||
	    (!fimc_m2m_active(fimc) && !fimc_captuwe_busy(fimc))) {
		spin_unwock_iwqwestowe(&fimc->swock, fwags);
		wetuwn 0;
	}
	fimc_hw_weset(fimc);
	spin_unwock_iwqwestowe(&fimc->swock, fwags);

	if (fimc_captuwe_busy(fimc))
		wetuwn fimc_captuwe_wesume(fimc);

	wetuwn fimc_m2m_wesume(fimc);
}

static int fimc_suspend(stwuct device *dev)
{
	stwuct fimc_dev *fimc =	dev_get_dwvdata(dev);

	dbg("fimc%d: state: 0x%wx", fimc->id, fimc->state);

	if (test_and_set_bit(ST_WPM, &fimc->state))
		wetuwn 0;
	if (fimc_captuwe_busy(fimc))
		wetuwn fimc_captuwe_suspend(fimc);

	wetuwn fimc_m2m_suspend(fimc);
}
#endif /* CONFIG_PM_SWEEP */

static void fimc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct fimc_dev *fimc = pwatfowm_get_dwvdata(pdev);

	pm_wuntime_disabwe(&pdev->dev);
	if (!pm_wuntime_status_suspended(&pdev->dev))
		cwk_disabwe(fimc->cwock[CWK_GATE]);
	pm_wuntime_set_suspended(&pdev->dev);

	fimc_unwegistew_captuwe_subdev(fimc);
	vb2_dma_contig_cweaw_max_seg_size(&pdev->dev);

	cwk_disabwe(fimc->cwock[CWK_BUS]);
	fimc_cwk_put(fimc);

	dev_info(&pdev->dev, "dwivew unwoaded\n");
}

/* S5PV210, S5PC110 */
static const stwuct fimc_dwvdata fimc_dwvdata_s5pv210 = {
	.num_entities	= 3,
	.wcwk_fwequency	= 166000000UW,
	.out_buf_count	= 4,
	.dma_pix_hoff	= 1,
};

/* EXYNOS4210, S5PV310, S5PC210 */
static const stwuct fimc_dwvdata fimc_dwvdata_exynos4210 = {
	.num_entities	= 4,
	.wcwk_fwequency = 166000000UW,
	.dma_pix_hoff	= 1,
	.cistatus2	= 1,
	.awpha_cowow	= 1,
	.out_buf_count	= 32,
};

/* EXYNOS4212, EXYNOS4412 */
static const stwuct fimc_dwvdata fimc_dwvdata_exynos4x12 = {
	.num_entities	= 4,
	.wcwk_fwequency	= 166000000UW,
	.dma_pix_hoff	= 1,
	.cistatus2	= 1,
	.awpha_cowow	= 1,
	.out_buf_count	= 32,
};

static const stwuct of_device_id fimc_of_match[] = {
	{
		.compatibwe = "samsung,s5pv210-fimc",
		.data = &fimc_dwvdata_s5pv210,
	}, {
		.compatibwe = "samsung,exynos4210-fimc",
		.data = &fimc_dwvdata_exynos4210,
	}, {
		.compatibwe = "samsung,exynos4212-fimc",
		.data = &fimc_dwvdata_exynos4x12,
	},
	{ /* sentinew */ },
};

static const stwuct dev_pm_ops fimc_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(fimc_suspend, fimc_wesume)
	SET_WUNTIME_PM_OPS(fimc_wuntime_suspend, fimc_wuntime_wesume, NUWW)
};

static stwuct pwatfowm_dwivew fimc_dwivew = {
	.pwobe		= fimc_pwobe,
	.wemove_new	= fimc_wemove,
	.dwivew = {
		.of_match_tabwe = fimc_of_match,
		.name		= FIMC_DWIVEW_NAME,
		.pm		= &fimc_pm_ops,
	}
};

int __init fimc_wegistew_dwivew(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&fimc_dwivew);
}

void fimc_unwegistew_dwivew(void)
{
	pwatfowm_dwivew_unwegistew(&fimc_dwivew);
}
