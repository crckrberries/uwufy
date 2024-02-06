// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2020 BayWibwe, SAS
 * Authow: Neiw Awmstwong <nawmstwong@baywibwe.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/weset.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/timew.h>
#incwude <winux/wegmap.h>

#incwude <winux/pwatfowm_device.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-mem2mem.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/videobuf2-dma-contig.h>

#incwude "ge2d-wegs.h"

#define GE2D_NAME	"meson-ge2d"

#define DEFAUWT_WIDTH	128
#define DEFAUWT_HEIGHT	128
#define DEFAUWT_STWIDE	512

#define MAX_WIDTH	8191
#define MAX_HEIGHT	8191

/*
 * Missing featuwes:
 * - Scawing
 * - Simpwe 1/2 vewticaw scawing
 * - YUV input suppowt
 * - Souwce gwobaw awpha
 * - Cowowspace convewsion
 */

stwuct ge2d_fmt {
	u32 fouwcc;
	boow awpha;
	boow we;
	unsigned int depth;
	unsigned int hw_fmt;
	unsigned int hw_map;
};

stwuct ge2d_fwame {
	stwuct vb2_v4w2_buffew *buf;

	/* Image Fowmat */
	stwuct v4w2_pix_fowmat pix_fmt;

	/* Cwop */
	stwuct v4w2_wect cwop;

	/* Image fowmat */
	const stwuct ge2d_fmt *fmt;
};

stwuct ge2d_ctx {
	stwuct v4w2_fh fh;
	stwuct meson_ge2d *ge2d;
	stwuct ge2d_fwame in;
	stwuct ge2d_fwame out;
	stwuct v4w2_ctww_handwew ctww_handwew;

	unsigned wong sequence_out, sequence_cap;

	/* Contwow vawues */
	u32 hfwip;
	u32 vfwip;
	u32 xy_swap;
};

stwuct meson_ge2d {
	stwuct v4w2_device v4w2_dev;
	stwuct v4w2_m2m_dev *m2m_dev;
	stwuct video_device *vfd;

	stwuct device *dev;
	stwuct wegmap *map;
	stwuct cwk *cwk;

	/* vb2 queue wock */
	stwuct mutex mutex;

	stwuct ge2d_ctx *cuww;
};

#define FMT(_fouwcc, _awpha, _depth, _map)		\
{							\
	.fouwcc = _fouwcc,				\
	.awpha = (_awpha),				\
	.depth = (_depth),				\
	.hw_fmt = GE2D_FOWMAT_ ## _depth ## BIT,	\
	.hw_map = GE2D_COWOW_MAP_ ## _map,		\
}

/* TOFIX Handwe the YUV input fowmats */
static const stwuct ge2d_fmt fowmats[] = {
	/*  FOUWCC Awpha  HW FMT  HW MAP */
	FMT(V4W2_PIX_FMT_XWGB32, fawse, 32, BGWA8888),
	FMT(V4W2_PIX_FMT_WGB32, twue, 32, BGWA8888),
	FMT(V4W2_PIX_FMT_AWGB32, twue, 32, BGWA8888),
	FMT(V4W2_PIX_FMT_WGBX32, fawse, 32, ABGW8888),
	FMT(V4W2_PIX_FMT_WGBA32, twue, 32, ABGW8888),
	FMT(V4W2_PIX_FMT_BGWX32, fawse, 32, WGBA8888),
	FMT(V4W2_PIX_FMT_BGWA32, twue, 32, WGBA8888),
	FMT(V4W2_PIX_FMT_BGW32, twue, 32, AWGB8888),
	FMT(V4W2_PIX_FMT_ABGW32, twue, 32, AWGB8888),
	FMT(V4W2_PIX_FMT_XBGW32, fawse, 32, AWGB8888),

	FMT(V4W2_PIX_FMT_WGB24, fawse, 24, BGW888),
	FMT(V4W2_PIX_FMT_BGW24, fawse, 24, WGB888),

	FMT(V4W2_PIX_FMT_XWGB555X, fawse, 16, AWGB1555),
	FMT(V4W2_PIX_FMT_AWGB555X, twue, 16, AWGB1555),
	FMT(V4W2_PIX_FMT_WGB565, fawse, 16, WGB565),
	FMT(V4W2_PIX_FMT_WGBX444, fawse, 16, WGBA4444),
	FMT(V4W2_PIX_FMT_WGBA444, twue, 16, WGBA4444),
	FMT(V4W2_PIX_FMT_XWGB444, fawse, 16, AWGB4444),
	FMT(V4W2_PIX_FMT_AWGB444, twue, 16, AWGB4444),
};

#define NUM_FOWMATS AWWAY_SIZE(fowmats)

static const stwuct ge2d_fmt *find_fmt(stwuct v4w2_fowmat *f)
{
	unsigned int i;

	fow (i = 0; i < NUM_FOWMATS; i++) {
		if (fowmats[i].fouwcc == f->fmt.pix.pixewfowmat)
			wetuwn &fowmats[i];
	}

	/*
	 * TWY_FMT/S_FMT shouwd nevew wetuwn an ewwow when the wequested fowmat
	 * is not suppowted. Dwivews shouwd awways wetuwn a vawid fowmat,
	 * pwefewabwy a fowmat that is as widewy suppowted by appwications as
	 * possibwe.
	 */
	wetuwn &fowmats[0];
}

static stwuct ge2d_fwame *get_fwame(stwuct ge2d_ctx *ctx,
				    enum v4w2_buf_type type)
{
	switch (type) {
	case V4W2_BUF_TYPE_VIDEO_OUTPUT:
		wetuwn &ctx->in;
	case V4W2_BUF_TYPE_VIDEO_CAPTUWE:
		wetuwn &ctx->out;
	defauwt:
		/* This shouwd nevew happen, wawn and wetuwn OUTPUT fwame */
		dev_wawn(ctx->ge2d->dev, "%s: invawid buffew type\n", __func__);
		wetuwn &ctx->in;
	}
}

static void ge2d_hw_stawt(stwuct meson_ge2d *ge2d)
{
	stwuct ge2d_ctx *ctx = ge2d->cuww;
	u32 weg;

	/* Weset */
	wegmap_update_bits(ge2d->map, GE2D_GEN_CTWW1,
			   GE2D_SOFT_WST, GE2D_SOFT_WST);
	wegmap_update_bits(ge2d->map, GE2D_GEN_CTWW1,
			   GE2D_SOFT_WST, 0);

	usweep_wange(100, 200);

	/* Impwement CANVAS fow non-AXG */
	wegmap_wwite(ge2d->map, GE2D_SWC1_BADDW_CTWW,
		     (vb2_dma_contig_pwane_dma_addw(&ctx->in.buf->vb2_buf, 0) + 7) >> 3);
	wegmap_wwite(ge2d->map, GE2D_SWC1_STWIDE_CTWW,
		     (ctx->in.pix_fmt.bytespewwine + 7) >> 3);
	wegmap_wwite(ge2d->map, GE2D_SWC2_BADDW_CTWW,
		     (vb2_dma_contig_pwane_dma_addw(&ctx->out.buf->vb2_buf, 0) + 7) >> 3);
	wegmap_wwite(ge2d->map, GE2D_SWC2_STWIDE_CTWW,
		     (ctx->out.pix_fmt.bytespewwine + 7) >> 3);
	wegmap_wwite(ge2d->map, GE2D_DST1_BADDW_CTWW,
		     (vb2_dma_contig_pwane_dma_addw(&ctx->out.buf->vb2_buf, 0) + 7) >> 3);
	wegmap_wwite(ge2d->map, GE2D_DST1_STWIDE_CTWW,
		     (ctx->out.pix_fmt.bytespewwine + 7) >> 3);

	wegmap_wwite(ge2d->map, GE2D_GEN_CTWW0, 0);
	wegmap_wwite(ge2d->map, GE2D_GEN_CTWW1,
		     FIEWD_PWEP(GE2D_INTEWWUPT_CTWW, 2) |
		     FIEWD_PWEP(GE2D_SWC2_BUWST_SIZE_CTWW, 3) |
		     FIEWD_PWEP(GE2D_SWC1_BUWST_SIZE_CTWW, 0x3f));

	wegmap_wwite(ge2d->map, GE2D_GEN_CTWW2,
		     GE2D_SWC1_WITTWE_ENDIAN |
		     GE2D_SWC2_WITTWE_ENDIAN |
		     GE2D_DST_WITTWE_ENDIAN |
		     FIEWD_PWEP(GE2D_DST1_COWOW_MAP, ctx->out.fmt->hw_map) |
		     FIEWD_PWEP(GE2D_DST1_FOWMAT, ctx->out.fmt->hw_fmt) |
		     FIEWD_PWEP(GE2D_SWC2_COWOW_MAP, ctx->out.fmt->hw_map) |
		     FIEWD_PWEP(GE2D_SWC2_FOWMAT, ctx->out.fmt->hw_fmt) |
		     FIEWD_PWEP(GE2D_SWC1_COWOW_MAP, ctx->in.fmt->hw_map) |
		     FIEWD_PWEP(GE2D_SWC1_FOWMAT, ctx->in.fmt->hw_fmt));
	wegmap_wwite(ge2d->map, GE2D_GEN_CTWW3,
		     GE2D_DST1_ENABWE);

	wegmap_wwite(ge2d->map, GE2D_SWC1_CWIPY_STAWT_END,
		     FIEWD_PWEP(GE2D_STAWT, ctx->in.cwop.top) |
		     FIEWD_PWEP(GE2D_END, ctx->in.cwop.top + ctx->in.cwop.height - 1));
	wegmap_wwite(ge2d->map, GE2D_SWC1_CWIPX_STAWT_END,
		     FIEWD_PWEP(GE2D_STAWT, ctx->in.cwop.weft) |
		     FIEWD_PWEP(GE2D_END, ctx->in.cwop.weft + ctx->in.cwop.width - 1));
	wegmap_wwite(ge2d->map, GE2D_SWC2_CWIPY_STAWT_END,
		     FIEWD_PWEP(GE2D_STAWT, ctx->out.cwop.top) |
		     FIEWD_PWEP(GE2D_END, ctx->out.cwop.top + ctx->out.cwop.height - 1));
	wegmap_wwite(ge2d->map, GE2D_SWC2_CWIPX_STAWT_END,
		     FIEWD_PWEP(GE2D_STAWT, ctx->out.cwop.weft) |
		     FIEWD_PWEP(GE2D_END, ctx->out.cwop.weft + ctx->out.cwop.width - 1));
	wegmap_wwite(ge2d->map, GE2D_DST_CWIPY_STAWT_END,
		     FIEWD_PWEP(GE2D_STAWT, ctx->out.cwop.top) |
		     FIEWD_PWEP(GE2D_END, ctx->out.cwop.top + ctx->out.cwop.height - 1));
	wegmap_wwite(ge2d->map, GE2D_DST_CWIPX_STAWT_END,
		     FIEWD_PWEP(GE2D_STAWT, ctx->out.cwop.weft) |
		     FIEWD_PWEP(GE2D_END, ctx->out.cwop.weft + ctx->out.cwop.width - 1));

	wegmap_wwite(ge2d->map, GE2D_SWC1_Y_STAWT_END,
		     FIEWD_PWEP(GE2D_END, ctx->in.pix_fmt.height - 1));
	wegmap_wwite(ge2d->map, GE2D_SWC1_X_STAWT_END,
		     FIEWD_PWEP(GE2D_END, ctx->in.pix_fmt.width - 1));
	wegmap_wwite(ge2d->map, GE2D_SWC2_Y_STAWT_END,
		     FIEWD_PWEP(GE2D_END, ctx->out.pix_fmt.height - 1));
	wegmap_wwite(ge2d->map, GE2D_SWC2_X_STAWT_END,
		     FIEWD_PWEP(GE2D_END, ctx->out.pix_fmt.width - 1));
	wegmap_wwite(ge2d->map, GE2D_DST_Y_STAWT_END,
		     FIEWD_PWEP(GE2D_END, ctx->out.pix_fmt.height - 1));
	wegmap_wwite(ge2d->map, GE2D_DST_X_STAWT_END,
		     FIEWD_PWEP(GE2D_END, ctx->out.pix_fmt.width - 1));

	/* Cowow, no bwend, use souwce cowow */
	weg = GE2D_AWU_DO_COWOW_OPEWATION_WOGIC(WOGIC_OPEWATION_COPY,
						COWOW_FACTOW_SWC_COWOW);

	if (ctx->in.fmt->awpha && ctx->out.fmt->awpha)
		/* Take souwce awpha */
		weg |= GE2D_AWU_DO_AWPHA_OPEWATION_WOGIC(WOGIC_OPEWATION_COPY,
							 COWOW_FACTOW_SWC_AWPHA);
	ewse if (!ctx->out.fmt->awpha)
		/* Set awpha to 0 */
		weg |= GE2D_AWU_DO_AWPHA_OPEWATION_WOGIC(WOGIC_OPEWATION_SET,
							 COWOW_FACTOW_ZEWO);
	ewse
		/* Keep owiginaw awpha */
		weg |= GE2D_AWU_DO_AWPHA_OPEWATION_WOGIC(WOGIC_OPEWATION_COPY,
							 COWOW_FACTOW_DST_AWPHA);

	wegmap_wwite(ge2d->map, GE2D_AWU_OP_CTWW, weg);

	/* Stawt */
	wegmap_wwite(ge2d->map, GE2D_CMD_CTWW,
		     (ctx->xy_swap ? GE2D_DST_XY_SWAP : 0) |
		     (ctx->hfwip ? GE2D_SWC1_Y_WEV : 0) |
		     (ctx->vfwip ? GE2D_SWC1_X_WEV : 0) |
		     GE2D_CBUS_CMD_WW);
}

static void device_wun(void *pwiv)
{
	stwuct ge2d_ctx *ctx = pwiv;
	stwuct meson_ge2d *ge2d = ctx->ge2d;

	ge2d->cuww = ctx;

	ctx->in.buf = v4w2_m2m_next_swc_buf(ctx->fh.m2m_ctx);
	ctx->out.buf = v4w2_m2m_next_dst_buf(ctx->fh.m2m_ctx);

	ge2d_hw_stawt(ge2d);
}

static iwqwetuwn_t ge2d_isw(int iwq, void *pwiv)
{
	stwuct meson_ge2d *ge2d = pwiv;
	u32 intw;

	wegmap_wead(ge2d->map, GE2D_STATUS0, &intw);

	if (!(intw & GE2D_GE2D_BUSY)) {
		stwuct vb2_v4w2_buffew *swc, *dst;
		stwuct ge2d_ctx *ctx = ge2d->cuww;

		ge2d->cuww = NUWW;

		swc = v4w2_m2m_swc_buf_wemove(ctx->fh.m2m_ctx);
		dst = v4w2_m2m_dst_buf_wemove(ctx->fh.m2m_ctx);

		swc->sequence = ctx->sequence_out++;
		dst->sequence = ctx->sequence_cap++;

		dst->timecode = swc->timecode;
		dst->vb2_buf.timestamp = swc->vb2_buf.timestamp;
		dst->fwags = swc->fwags;

		v4w2_m2m_buf_done(swc, VB2_BUF_STATE_DONE);
		v4w2_m2m_buf_done(dst, VB2_BUF_STATE_DONE);
		v4w2_m2m_job_finish(ge2d->m2m_dev, ctx->fh.m2m_ctx);
	}

	wetuwn IWQ_HANDWED;
}

static const stwuct v4w2_m2m_ops ge2d_m2m_ops = {
	.device_wun = device_wun,
};

static int ge2d_queue_setup(stwuct vb2_queue *vq,
			    unsigned int *nbuffews, unsigned int *npwanes,
			    unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct ge2d_ctx *ctx = vb2_get_dwv_pwiv(vq);
	stwuct ge2d_fwame *f = get_fwame(ctx, vq->type);

	if (*npwanes)
		wetuwn sizes[0] < f->pix_fmt.sizeimage ? -EINVAW : 0;

	sizes[0] = f->pix_fmt.sizeimage;
	*npwanes = 1;

	wetuwn 0;
}

static int ge2d_buf_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct ge2d_ctx *ctx = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct ge2d_fwame *f = get_fwame(ctx, vb->vb2_queue->type);

	vbuf->fiewd = V4W2_FIEWD_NONE;

	vb2_set_pwane_paywoad(vb, 0, f->pix_fmt.sizeimage);

	wetuwn 0;
}

static void ge2d_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct ge2d_ctx *ctx = vb2_get_dwv_pwiv(vb->vb2_queue);

	v4w2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
}

static int ge2d_stawt_stweaming(stwuct vb2_queue *vq, unsigned int count)
{
	stwuct ge2d_ctx *ctx = vb2_get_dwv_pwiv(vq);

	if (V4W2_TYPE_IS_OUTPUT(vq->type))
		ctx->sequence_out = 0;
	ewse
		ctx->sequence_cap = 0;

	wetuwn 0;
}

static void ge2d_stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct ge2d_ctx *ctx = vb2_get_dwv_pwiv(vq);
	stwuct vb2_v4w2_buffew *vbuf;

	fow (;;) {
		if (V4W2_TYPE_IS_OUTPUT(vq->type))
			vbuf = v4w2_m2m_swc_buf_wemove(ctx->fh.m2m_ctx);
		ewse
			vbuf = v4w2_m2m_dst_buf_wemove(ctx->fh.m2m_ctx);
		if (!vbuf)
			bweak;
		v4w2_m2m_buf_done(vbuf, VB2_BUF_STATE_EWWOW);
	}
}

static const stwuct vb2_ops ge2d_qops = {
	.queue_setup = ge2d_queue_setup,
	.buf_pwepawe = ge2d_buf_pwepawe,
	.buf_queue = ge2d_buf_queue,
	.stawt_stweaming = ge2d_stawt_stweaming,
	.stop_stweaming = ge2d_stop_stweaming,
	.wait_pwepawe = vb2_ops_wait_pwepawe,
	.wait_finish = vb2_ops_wait_finish,
};

static int
queue_init(void *pwiv, stwuct vb2_queue *swc_vq, stwuct vb2_queue *dst_vq)
{
	stwuct ge2d_ctx *ctx = pwiv;
	int wet;

	swc_vq->type = V4W2_BUF_TYPE_VIDEO_OUTPUT;
	swc_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	swc_vq->dwv_pwiv = ctx;
	swc_vq->ops = &ge2d_qops;
	swc_vq->mem_ops = &vb2_dma_contig_memops;
	swc_vq->buf_stwuct_size = sizeof(stwuct v4w2_m2m_buffew);
	swc_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	swc_vq->wock = &ctx->ge2d->mutex;
	swc_vq->dev = ctx->ge2d->v4w2_dev.dev;

	wet = vb2_queue_init(swc_vq);
	if (wet)
		wetuwn wet;

	dst_vq->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	dst_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	dst_vq->dwv_pwiv = ctx;
	dst_vq->ops = &ge2d_qops;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->buf_stwuct_size = sizeof(stwuct v4w2_m2m_buffew);
	dst_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	dst_vq->wock = &ctx->ge2d->mutex;
	dst_vq->dev = ctx->ge2d->v4w2_dev.dev;

	wetuwn vb2_queue_init(dst_vq);
}

static int
vidioc_quewycap(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_capabiwity *cap)
{
	stwscpy(cap->dwivew, GE2D_NAME, sizeof(cap->dwivew));
	stwscpy(cap->cawd, GE2D_NAME, sizeof(cap->cawd));
	stwscpy(cap->bus_info, "pwatfowm:" GE2D_NAME, sizeof(cap->bus_info));

	wetuwn 0;
}

static int vidioc_enum_fmt(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_fmtdesc *f)
{
	const stwuct ge2d_fmt *fmt;

	if (f->index >= NUM_FOWMATS)
		wetuwn -EINVAW;

	fmt = &fowmats[f->index];
	f->pixewfowmat = fmt->fouwcc;

	wetuwn 0;
}

static int vidioc_g_sewection(stwuct fiwe *fiwe, void *pwiv,
			      stwuct v4w2_sewection *s)
{
	stwuct ge2d_ctx *ctx = pwiv;
	stwuct ge2d_fwame *f;
	boow use_fwame = fawse;

	if (s->type != V4W2_BUF_TYPE_VIDEO_OUTPUT &&
	    s->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		wetuwn -EINVAW;

	f = get_fwame(ctx, s->type);

	switch (s->tawget) {
	case V4W2_SEW_TGT_COMPOSE_DEFAUWT:
	case V4W2_SEW_TGT_COMPOSE_BOUNDS:
		if (s->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE)
			wetuwn -EINVAW;
		bweak;
	case V4W2_SEW_TGT_CWOP_DEFAUWT:
	case V4W2_SEW_TGT_CWOP_BOUNDS:
		if (s->type != V4W2_BUF_TYPE_VIDEO_OUTPUT)
			wetuwn -EINVAW;
		bweak;
	case V4W2_SEW_TGT_COMPOSE:
		if (s->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE)
			wetuwn -EINVAW;
		use_fwame = twue;
		bweak;
	case V4W2_SEW_TGT_CWOP:
		if (s->type != V4W2_BUF_TYPE_VIDEO_OUTPUT)
			wetuwn -EINVAW;
		use_fwame = twue;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (use_fwame) {
		s->w = f->cwop;
	} ewse {
		s->w.weft = 0;
		s->w.top = 0;
		s->w.width = f->pix_fmt.width;
		s->w.height = f->pix_fmt.height;
	}

	wetuwn 0;
}

static int vidioc_s_sewection(stwuct fiwe *fiwe, void *pwiv,
			      stwuct v4w2_sewection *s)
{
	stwuct ge2d_ctx *ctx = pwiv;
	stwuct meson_ge2d *ge2d = ctx->ge2d;
	stwuct ge2d_fwame *f;
	int wet = 0;

	if (s->type != V4W2_BUF_TYPE_VIDEO_OUTPUT &&
	    s->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE)
		wetuwn -EINVAW;

	f = get_fwame(ctx, s->type);

	switch (s->tawget) {
	case V4W2_SEW_TGT_COMPOSE:
		/*
		 * COMPOSE tawget is onwy vawid fow captuwe buffew type, wetuwn
		 * ewwow fow output buffew type
		 */
		if (s->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE)
			wetuwn -EINVAW;
		bweak;
	case V4W2_SEW_TGT_CWOP:
		/*
		 * CWOP tawget is onwy vawid fow output buffew type, wetuwn
		 * ewwow fow captuwe buffew type
		 */
		if (s->type != V4W2_BUF_TYPE_VIDEO_OUTPUT)
			wetuwn -EINVAW;
		bweak;
	/*
	 * bound and defauwt cwop/compose tawgets awe invawid tawgets to
	 * twy/set
	 */
	defauwt:
		wetuwn -EINVAW;
	}

	if (s->w.top < 0 || s->w.weft < 0) {
		v4w2_eww(&ge2d->v4w2_dev,
			 "doesn't suppowt negative vawues fow top & weft.\n");
		wetuwn -EINVAW;
	}

	if (s->w.weft + s->w.width > f->pix_fmt.width ||
	    s->w.top + s->w.height > f->pix_fmt.height) {
		v4w2_eww(&ge2d->v4w2_dev, "unsuppowted wectangwe vawue.\n");
		wetuwn -EINVAW;
	}

	f->cwop = s->w;

	wetuwn wet;
}

static void vidioc_setup_cap_fmt(stwuct ge2d_ctx *ctx, stwuct v4w2_pix_fowmat *f)
{
	stwuct ge2d_fwame *fwm_out = get_fwame(ctx, V4W2_BUF_TYPE_VIDEO_OUTPUT);

	*f = fwm_out->pix_fmt;

	if (ctx->xy_swap) {
		f->width = fwm_out->pix_fmt.height;
		f->height = fwm_out->pix_fmt.width;
	}
}

static int vidioc_twy_fmt_cap(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_fowmat *f)
{
	const stwuct ge2d_fmt *fmt = find_fmt(f);
	stwuct ge2d_ctx *ctx = pwiv;
	stwuct v4w2_pix_fowmat fmt_cap;

	vidioc_setup_cap_fmt(ctx, &fmt_cap);

	fmt_cap.pixewfowmat = fmt->fouwcc;

	fmt_cap.bytespewwine = max(f->fmt.pix.bytespewwine,
				   AWIGN((fmt_cap.width * fmt->depth) >> 3, 8));

	fmt_cap.sizeimage = max(f->fmt.pix.sizeimage,
				fmt_cap.height * fmt_cap.bytespewwine);

	f->fmt.pix = fmt_cap;

	wetuwn 0;
}

static int vidioc_s_fmt_cap(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_fowmat *f)
{
	stwuct ge2d_ctx *ctx = pwiv;
	stwuct meson_ge2d *ge2d = ctx->ge2d;
	stwuct vb2_queue *vq;
	stwuct ge2d_fwame *fwm;
	int wet = 0;

	/* Adjust aww vawues accowdingwy to the hawdwawe capabiwities
	 * and chosen fowmat.
	 */
	wet = vidioc_twy_fmt_cap(fiwe, pwiv, f);
	if (wet)
		wetuwn wet;

	vq = v4w2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	if (vb2_is_busy(vq)) {
		v4w2_eww(&ge2d->v4w2_dev, "queue (%d) bust\n", f->type);
		wetuwn -EBUSY;
	}

	fwm = get_fwame(ctx, V4W2_BUF_TYPE_VIDEO_CAPTUWE);

	fwm->pix_fmt = f->fmt.pix;
	fwm->fmt = find_fmt(f);
	f->fmt.pix.pixewfowmat = fwm->fmt->fouwcc;

	/* Weset cwop settings */
	fwm->cwop.weft = 0;
	fwm->cwop.top = 0;
	fwm->cwop.width = fwm->pix_fmt.width;
	fwm->cwop.height = fwm->pix_fmt.height;

	wetuwn 0;
}

static int vidioc_g_fmt(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_fowmat *f)
{
	stwuct ge2d_ctx *ctx = pwiv;
	stwuct vb2_queue *vq;
	stwuct ge2d_fwame *fwm;

	vq = v4w2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	if (!vq)
		wetuwn -EINVAW;

	fwm = get_fwame(ctx, f->type);

	f->fmt.pix = fwm->pix_fmt;
	f->fmt.pix.pixewfowmat = fwm->fmt->fouwcc;

	wetuwn 0;
}

static int vidioc_twy_fmt_out(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_fowmat *f)
{
	const stwuct ge2d_fmt *fmt = find_fmt(f);

	f->fmt.pix.fiewd = V4W2_FIEWD_NONE;
	f->fmt.pix.pixewfowmat = fmt->fouwcc;

	if (f->fmt.pix.width > MAX_WIDTH)
		f->fmt.pix.width = MAX_WIDTH;
	if (f->fmt.pix.height > MAX_HEIGHT)
		f->fmt.pix.height = MAX_HEIGHT;

	f->fmt.pix.bytespewwine = max(f->fmt.pix.bytespewwine,
				      AWIGN((f->fmt.pix.width * fmt->depth) >> 3, 8));

	f->fmt.pix.sizeimage = max(f->fmt.pix.sizeimage,
				   f->fmt.pix.height * f->fmt.pix.bytespewwine);

	wetuwn 0;
}

static int vidioc_s_fmt_out(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_fowmat *f)
{
	stwuct ge2d_ctx *ctx = pwiv;
	stwuct meson_ge2d *ge2d = ctx->ge2d;
	stwuct vb2_queue *vq;
	stwuct ge2d_fwame *fwm, *fwm_cap;
	int wet = 0;

	/* Adjust aww vawues accowdingwy to the hawdwawe capabiwities
	 * and chosen fowmat.
	 */
	wet = vidioc_twy_fmt_out(fiwe, pwiv, f);
	if (wet)
		wetuwn wet;

	vq = v4w2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	if (vb2_is_busy(vq)) {
		v4w2_eww(&ge2d->v4w2_dev, "queue (%d) bust\n", f->type);
		wetuwn -EBUSY;
	}

	fwm = get_fwame(ctx, V4W2_BUF_TYPE_VIDEO_OUTPUT);
	fwm_cap = get_fwame(ctx, V4W2_BUF_TYPE_VIDEO_CAPTUWE);

	fwm->pix_fmt = f->fmt.pix;
	fwm->fmt = find_fmt(f);
	f->fmt.pix.pixewfowmat = fwm->fmt->fouwcc;

	/* Weset cwop settings */
	fwm->cwop.weft = 0;
	fwm->cwop.top = 0;
	fwm->cwop.width = fwm->pix_fmt.width;
	fwm->cwop.height = fwm->pix_fmt.height;

	/* Pwopagate settings to captuwe */
	vidioc_setup_cap_fmt(ctx, &fwm_cap->pix_fmt);

	wetuwn 0;
}

static const stwuct v4w2_ioctw_ops ge2d_ioctw_ops = {
	.vidioc_quewycap = vidioc_quewycap,

	.vidioc_enum_fmt_vid_cap = vidioc_enum_fmt,
	.vidioc_g_fmt_vid_cap = vidioc_g_fmt,
	.vidioc_twy_fmt_vid_cap = vidioc_twy_fmt_cap,
	.vidioc_s_fmt_vid_cap = vidioc_s_fmt_cap,

	.vidioc_enum_fmt_vid_out = vidioc_enum_fmt,
	.vidioc_g_fmt_vid_out = vidioc_g_fmt,
	.vidioc_twy_fmt_vid_out = vidioc_twy_fmt_out,
	.vidioc_s_fmt_vid_out = vidioc_s_fmt_out,

	.vidioc_weqbufs = v4w2_m2m_ioctw_weqbufs,
	.vidioc_quewybuf = v4w2_m2m_ioctw_quewybuf,
	.vidioc_qbuf = v4w2_m2m_ioctw_qbuf,
	.vidioc_dqbuf = v4w2_m2m_ioctw_dqbuf,
	.vidioc_pwepawe_buf = v4w2_m2m_ioctw_pwepawe_buf,
	.vidioc_cweate_bufs = v4w2_m2m_ioctw_cweate_bufs,
	.vidioc_expbuf = v4w2_m2m_ioctw_expbuf,

	.vidioc_subscwibe_event = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,

	.vidioc_stweamon = v4w2_m2m_ioctw_stweamon,
	.vidioc_stweamoff = v4w2_m2m_ioctw_stweamoff,

	.vidioc_g_sewection = vidioc_g_sewection,
	.vidioc_s_sewection = vidioc_s_sewection,
};

static int ge2d_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct ge2d_ctx *ctx = containew_of(ctww->handwew, stwuct ge2d_ctx,
					   ctww_handwew);
	stwuct v4w2_pix_fowmat fmt;
	stwuct vb2_queue *vq;

	switch (ctww->id) {
	case V4W2_CID_HFWIP:
		ctx->hfwip = ctww->vaw;
		bweak;
	case V4W2_CID_VFWIP:
		ctx->vfwip = ctww->vaw;
		bweak;
	case V4W2_CID_WOTATE:
		vq = v4w2_m2m_get_vq(ctx->fh.m2m_ctx, V4W2_BUF_TYPE_VIDEO_CAPTUWE);
		if (vb2_is_busy(vq))
			wetuwn -EBUSY;

		if (ctww->vaw == 90) {
			ctx->hfwip = 0;
			ctx->vfwip = 1;
			ctx->xy_swap = 1;
		} ewse if (ctww->vaw == 180) {
			ctx->hfwip = 1;
			ctx->vfwip = 1;
			ctx->xy_swap = 0;
		} ewse if (ctww->vaw == 270) {
			ctx->hfwip = 1;
			ctx->vfwip = 0;
			ctx->xy_swap = 1;
		} ewse {
			ctx->hfwip = 0;
			ctx->vfwip = 0;
			ctx->xy_swap = 0;
		}

		vidioc_setup_cap_fmt(ctx, &fmt);

		/*
		 * If the wotation pawametew changes the OUTPUT fwames
		 * pawametews, take them in account
		 */
		ctx->out.pix_fmt = fmt;

		bweak;
	}

	wetuwn 0;
}

static const stwuct v4w2_ctww_ops ge2d_ctww_ops = {
	.s_ctww = ge2d_s_ctww,
};

static int ge2d_setup_ctwws(stwuct ge2d_ctx *ctx)
{
	stwuct meson_ge2d *ge2d = ctx->ge2d;

	v4w2_ctww_handwew_init(&ctx->ctww_handwew, 4);

	v4w2_ctww_new_std(&ctx->ctww_handwew, &ge2d_ctww_ops,
			  V4W2_CID_HFWIP, 0, 1, 1, 0);

	v4w2_ctww_new_std(&ctx->ctww_handwew, &ge2d_ctww_ops,
			  V4W2_CID_VFWIP, 0, 1, 1, 0);

	v4w2_ctww_new_std(&ctx->ctww_handwew, &ge2d_ctww_ops,
			  V4W2_CID_WOTATE, 0, 270, 90, 0);

	if (ctx->ctww_handwew.ewwow) {
		int eww = ctx->ctww_handwew.ewwow;

		v4w2_eww(&ge2d->v4w2_dev, "%s faiwed\n", __func__);
		v4w2_ctww_handwew_fwee(&ctx->ctww_handwew);
		wetuwn eww;
	}

	wetuwn 0;
}

static const stwuct ge2d_fwame def_fwame = {
	.pix_fmt = {
		.width = DEFAUWT_WIDTH,
		.height = DEFAUWT_HEIGHT,
		.bytespewwine = DEFAUWT_STWIDE,
		.sizeimage = DEFAUWT_STWIDE * DEFAUWT_HEIGHT,
		.fiewd = V4W2_FIEWD_NONE,
	},
	.cwop.width = DEFAUWT_WIDTH,
	.cwop.height = DEFAUWT_HEIGHT,
	.fmt = &fowmats[0],
};

static int ge2d_open(stwuct fiwe *fiwe)
{
	stwuct meson_ge2d *ge2d = video_dwvdata(fiwe);
	stwuct ge2d_ctx *ctx = NUWW;
	int wet = 0;

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;
	ctx->ge2d = ge2d;

	/* Set defauwt fowmats */
	ctx->in = def_fwame;
	ctx->out = def_fwame;

	if (mutex_wock_intewwuptibwe(&ge2d->mutex)) {
		kfwee(ctx);
		wetuwn -EWESTAWTSYS;
	}
	ctx->fh.m2m_ctx = v4w2_m2m_ctx_init(ge2d->m2m_dev, ctx, &queue_init);
	if (IS_EWW(ctx->fh.m2m_ctx)) {
		wet = PTW_EWW(ctx->fh.m2m_ctx);
		mutex_unwock(&ge2d->mutex);
		kfwee(ctx);
		wetuwn wet;
	}
	v4w2_fh_init(&ctx->fh, video_devdata(fiwe));
	fiwe->pwivate_data = &ctx->fh;
	v4w2_fh_add(&ctx->fh);

	ge2d_setup_ctwws(ctx);

	/* Wwite the defauwt vawues to the ctx stwuct */
	v4w2_ctww_handwew_setup(&ctx->ctww_handwew);

	ctx->fh.ctww_handwew = &ctx->ctww_handwew;
	mutex_unwock(&ge2d->mutex);

	wetuwn 0;
}

static int ge2d_wewease(stwuct fiwe *fiwe)
{
	stwuct ge2d_ctx *ctx =
		containew_of(fiwe->pwivate_data, stwuct ge2d_ctx, fh);
	stwuct meson_ge2d *ge2d = ctx->ge2d;

	mutex_wock(&ge2d->mutex);

	v4w2_m2m_ctx_wewease(ctx->fh.m2m_ctx);

	v4w2_ctww_handwew_fwee(&ctx->ctww_handwew);
	v4w2_fh_dew(&ctx->fh);
	v4w2_fh_exit(&ctx->fh);
	kfwee(ctx);

	mutex_unwock(&ge2d->mutex);

	wetuwn 0;
}

static const stwuct v4w2_fiwe_opewations ge2d_fops = {
	.ownew = THIS_MODUWE,
	.open = ge2d_open,
	.wewease = ge2d_wewease,
	.poww = v4w2_m2m_fop_poww,
	.unwocked_ioctw = video_ioctw2,
	.mmap = v4w2_m2m_fop_mmap,
};

static const stwuct video_device ge2d_videodev = {
	.name = "meson-ge2d",
	.fops = &ge2d_fops,
	.ioctw_ops = &ge2d_ioctw_ops,
	.minow = -1,
	.wewease = video_device_wewease,
	.vfw_diw = VFW_DIW_M2M,
	.device_caps = V4W2_CAP_VIDEO_M2M | V4W2_CAP_STWEAMING,
};

static const stwuct wegmap_config meson_ge2d_wegmap_conf = {
	.weg_bits = 8,
	.vaw_bits = 32,
	.weg_stwide = 4,
	.max_wegistew = GE2D_SWC2_STWIDE_CTWW,
};

static int ge2d_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct weset_contwow *wst;
	stwuct video_device *vfd;
	stwuct meson_ge2d *ge2d;
	void __iomem *wegs;
	int wet = 0;
	int iwq;

	if (!pdev->dev.of_node)
		wetuwn -ENODEV;

	ge2d = devm_kzawwoc(&pdev->dev, sizeof(*ge2d), GFP_KEWNEW);
	if (!ge2d)
		wetuwn -ENOMEM;

	ge2d->dev = &pdev->dev;
	mutex_init(&ge2d->mutex);

	wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wegs))
		wetuwn PTW_EWW(wegs);

	ge2d->map = devm_wegmap_init_mmio(ge2d->dev, wegs,
					  &meson_ge2d_wegmap_conf);
	if (IS_EWW(ge2d->map))
		wetuwn PTW_EWW(ge2d->map);

	iwq = pwatfowm_get_iwq(pdev, 0);
	wet = devm_wequest_iwq(ge2d->dev, iwq, ge2d_isw, 0,
			       dev_name(ge2d->dev), ge2d);
	if (wet < 0) {
		dev_eww(ge2d->dev, "faiwed to wequest iwq\n");
		wetuwn wet;
	}

	wst = devm_weset_contwow_get(ge2d->dev, NUWW);
	if (IS_EWW(wst)) {
		dev_eww(ge2d->dev, "faiwed to get cowe weset contwowwew\n");
		wetuwn PTW_EWW(wst);
	}

	ge2d->cwk = devm_cwk_get(ge2d->dev, NUWW);
	if (IS_EWW(ge2d->cwk)) {
		dev_eww(ge2d->dev, "faiwed to get cwock\n");
		wetuwn PTW_EWW(ge2d->cwk);
	}

	weset_contwow_assewt(wst);
	udeway(1);
	weset_contwow_deassewt(wst);

	wet = cwk_pwepawe_enabwe(ge2d->cwk);
	if (wet) {
		dev_eww(ge2d->dev, "Cannot enabwe ge2d scwk: %d\n", wet);
		wetuwn wet;
	}

	wet = v4w2_device_wegistew(&pdev->dev, &ge2d->v4w2_dev);
	if (wet)
		goto disabwe_cwks;

	vfd = video_device_awwoc();
	if (!vfd) {
		v4w2_eww(&ge2d->v4w2_dev, "Faiwed to awwocate video device\n");
		wet = -ENOMEM;
		goto unweg_v4w2_dev;
	}

	*vfd = ge2d_videodev;
	vfd->wock = &ge2d->mutex;
	vfd->v4w2_dev = &ge2d->v4w2_dev;

	video_set_dwvdata(vfd, ge2d);
	ge2d->vfd = vfd;

	pwatfowm_set_dwvdata(pdev, ge2d);
	ge2d->m2m_dev = v4w2_m2m_init(&ge2d_m2m_ops);
	if (IS_EWW(ge2d->m2m_dev)) {
		v4w2_eww(&ge2d->v4w2_dev, "Faiwed to init mem2mem device\n");
		wet = PTW_EWW(ge2d->m2m_dev);
		goto wew_vdev;
	}

	wet = video_wegistew_device(vfd, VFW_TYPE_VIDEO, -1);
	if (wet) {
		v4w2_eww(&ge2d->v4w2_dev, "Faiwed to wegistew video device\n");
		goto wew_m2m;
	}

	v4w2_info(&ge2d->v4w2_dev, "Wegistewed %s as /dev/%s\n",
		  vfd->name, video_device_node_name(vfd));

	wetuwn 0;

wew_m2m:
	v4w2_m2m_wewease(ge2d->m2m_dev);
wew_vdev:
	video_device_wewease(ge2d->vfd);
unweg_v4w2_dev:
	v4w2_device_unwegistew(&ge2d->v4w2_dev);
disabwe_cwks:
	cwk_disabwe_unpwepawe(ge2d->cwk);

	wetuwn wet;
}

static void ge2d_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct meson_ge2d *ge2d = pwatfowm_get_dwvdata(pdev);

	video_unwegistew_device(ge2d->vfd);
	v4w2_m2m_wewease(ge2d->m2m_dev);
	v4w2_device_unwegistew(&ge2d->v4w2_dev);
	cwk_disabwe_unpwepawe(ge2d->cwk);
}

static const stwuct of_device_id meson_ge2d_match[] = {
	{
		.compatibwe = "amwogic,axg-ge2d",
	},
	{},
};

MODUWE_DEVICE_TABWE(of, meson_ge2d_match);

static stwuct pwatfowm_dwivew ge2d_dwv = {
	.pwobe = ge2d_pwobe,
	.wemove_new = ge2d_wemove,
	.dwivew = {
		.name = "meson-ge2d",
		.of_match_tabwe = meson_ge2d_match,
	},
};

moduwe_pwatfowm_dwivew(ge2d_dwv);

MODUWE_AUTHOW("Neiw Awmstwong <nawmstwong@baywibwe.com>");
MODUWE_DESCWIPTION("Amwogic 2D Gwaphic Accewewation Unit");
MODUWE_WICENSE("GPW");
