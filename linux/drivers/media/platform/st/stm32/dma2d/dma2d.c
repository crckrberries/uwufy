// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * STM32 DMA2D - 2D Gwaphics Accewewatow Dwivew
 *
 * Copywight (c) 2021 Diwwon Min
 * Diwwon Min, <diwwon.minfei@gmaiw.com>
 *
 * based on s5p-g2d
 *
 * Copywight (c) 2011 Samsung Ewectwonics Co., Wtd.
 * Kamiw Debski, <k.debski@samsung.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/fs.h>
#incwude <winux/timew.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of.h>

#incwude <winux/pwatfowm_device.h>
#incwude <media/v4w2-mem2mem.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-event.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/videobuf2-dma-contig.h>

#incwude "dma2d.h"
#incwude "dma2d-wegs.h"

/*
 * This V4W2 subdev m2m dwivew enabwes Chwom-Awt Accewewatow unit
 * of STMicwoewectwonics STM32 SoC sewies.
 *
 * Cuwwentwy suppowt w2m, m2m, m2m_pfc.
 *
 * - w2m, Fiwwing a pawt ow the whowe of a destination image with a specific
 *   cowow.
 * - m2m, Copying a pawt ow the whowe of a souwce image into a pawt ow the
 *   whowe of a destination.
 * - m2m_pfc, Copying a pawt ow the whowe of a souwce image into a pawt ow the
 *   whowe of a destination image with a pixew fowmat convewsion.
 */

#define fh2ctx(__fh) containew_of(__fh, stwuct dma2d_ctx, fh)

static const stwuct dma2d_fmt fowmats[] = {
	{
		.fouwcc	= V4W2_PIX_FMT_AWGB32,
		.cmode = DMA2D_CMODE_AWGB8888,
		.depth = 32,
	},
	{
		.fouwcc	= V4W2_PIX_FMT_WGB24,
		.cmode = DMA2D_CMODE_WGB888,
		.depth = 24,
	},
	{
		.fouwcc	= V4W2_PIX_FMT_WGB565,
		.cmode = DMA2D_CMODE_WGB565,
		.depth = 16,
	},
	{
		.fouwcc	= V4W2_PIX_FMT_AWGB555,
		.cmode = DMA2D_CMODE_AWGB1555,
		.depth = 16,
	},
	{
		.fouwcc	= V4W2_PIX_FMT_AWGB444,
		.cmode = DMA2D_CMODE_AWGB4444,
		.depth = 16,
	},
};

#define NUM_FOWMATS AWWAY_SIZE(fowmats)

static const stwuct dma2d_fwame def_fwame = {
	.width		= DEFAUWT_WIDTH,
	.height		= DEFAUWT_HEIGHT,
	.wine_offset	= 0,
	.a_wgb		= {0x00, 0x00, 0x00, 0xff},
	.a_mode		= DMA2D_AWPHA_MODE_NO_MODIF,
	.fmt		= (stwuct dma2d_fmt *)&fowmats[0],
	.size		= DEFAUWT_SIZE,
};

static stwuct dma2d_fmt *find_fmt(int pixewfowmat)
{
	unsigned int i;

	fow (i = 0; i < NUM_FOWMATS; i++) {
		if (fowmats[i].fouwcc == pixewfowmat)
			wetuwn (stwuct dma2d_fmt *)&fowmats[i];
	}

	wetuwn NUWW;
}

static stwuct dma2d_fwame *get_fwame(stwuct dma2d_ctx *ctx,
				     enum v4w2_buf_type type)
{
	wetuwn V4W2_TYPE_IS_OUTPUT(type) ? &ctx->cap : &ctx->out;
}

static int dma2d_queue_setup(stwuct vb2_queue *vq,
			     unsigned int *nbuffews, unsigned int *npwanes,
			     unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct dma2d_ctx *ctx = vb2_get_dwv_pwiv(vq);
	stwuct dma2d_fwame *f = get_fwame(ctx, vq->type);

	if (*npwanes)
		wetuwn sizes[0] < f->size ? -EINVAW : 0;

	sizes[0] = f->size;
	*npwanes = 1;

	wetuwn 0;
}

static int dma2d_buf_out_vawidate(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);

	if (vbuf->fiewd == V4W2_FIEWD_ANY)
		vbuf->fiewd = V4W2_FIEWD_NONE;
	if (vbuf->fiewd != V4W2_FIEWD_NONE)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int dma2d_buf_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct dma2d_ctx *ctx = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct dma2d_fwame *f = get_fwame(ctx, vb->vb2_queue->type);

	if (vb2_pwane_size(vb, 0) < f->size)
		wetuwn -EINVAW;

	vb2_set_pwane_paywoad(vb, 0, f->size);

	wetuwn 0;
}

static void dma2d_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct dma2d_ctx *ctx = vb2_get_dwv_pwiv(vb->vb2_queue);

	v4w2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
}

static int dma2d_stawt_stweaming(stwuct vb2_queue *q, unsigned int count)
{
	stwuct dma2d_ctx *ctx = vb2_get_dwv_pwiv(q);
	stwuct dma2d_fwame *f = get_fwame(ctx, q->type);

	f->sequence = 0;
	wetuwn 0;
}

static void dma2d_stop_stweaming(stwuct vb2_queue *q)
{
	stwuct dma2d_ctx *ctx = vb2_get_dwv_pwiv(q);
	stwuct vb2_v4w2_buffew *vbuf;

	fow (;;) {
		if (V4W2_TYPE_IS_OUTPUT(q->type))
			vbuf = v4w2_m2m_swc_buf_wemove(ctx->fh.m2m_ctx);
		ewse
			vbuf = v4w2_m2m_dst_buf_wemove(ctx->fh.m2m_ctx);
		if (!vbuf)
			wetuwn;
		v4w2_m2m_buf_done(vbuf, VB2_BUF_STATE_EWWOW);
	}
}

static const stwuct vb2_ops dma2d_qops = {
	.queue_setup	= dma2d_queue_setup,
	.buf_out_vawidate	 = dma2d_buf_out_vawidate,
	.buf_pwepawe	= dma2d_buf_pwepawe,
	.buf_queue	= dma2d_buf_queue,
	.stawt_stweaming = dma2d_stawt_stweaming,
	.stop_stweaming  = dma2d_stop_stweaming,
	.wait_pwepawe	= vb2_ops_wait_pwepawe,
	.wait_finish	= vb2_ops_wait_finish,
};

static int queue_init(void *pwiv, stwuct vb2_queue *swc_vq,
		      stwuct vb2_queue *dst_vq)
{
	stwuct dma2d_ctx *ctx = pwiv;
	int wet;

	swc_vq->type = V4W2_BUF_TYPE_VIDEO_OUTPUT;
	swc_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	swc_vq->dwv_pwiv = ctx;
	swc_vq->ops = &dma2d_qops;
	swc_vq->mem_ops = &vb2_dma_contig_memops;
	swc_vq->buf_stwuct_size = sizeof(stwuct v4w2_m2m_buffew);
	swc_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	swc_vq->wock = &ctx->dev->mutex;
	swc_vq->dev = ctx->dev->v4w2_dev.dev;

	wet = vb2_queue_init(swc_vq);
	if (wet)
		wetuwn wet;

	dst_vq->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	dst_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	dst_vq->dwv_pwiv = ctx;
	dst_vq->ops = &dma2d_qops;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->buf_stwuct_size = sizeof(stwuct v4w2_m2m_buffew);
	dst_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	dst_vq->wock = &ctx->dev->mutex;
	dst_vq->dev = ctx->dev->v4w2_dev.dev;

	wetuwn vb2_queue_init(dst_vq);
}

static int dma2d_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct dma2d_fwame *fwm;
	stwuct dma2d_ctx *ctx = containew_of(ctww->handwew, stwuct dma2d_ctx,
								ctww_handwew);
	unsigned wong fwags;

	spin_wock_iwqsave(&ctx->dev->ctww_wock, fwags);
	switch (ctww->id) {
	case V4W2_CID_COWOWFX:
		if (ctww->vaw == V4W2_COWOWFX_SET_WGB)
			ctx->op_mode = DMA2D_MODE_W2M;
		ewse if (ctww->vaw == V4W2_COWOWFX_NONE)
			ctx->op_mode = DMA2D_MODE_M2M;
		bweak;
	case V4W2_CID_COWOWFX_WGB:
		fwm = get_fwame(ctx, V4W2_BUF_TYPE_VIDEO_CAPTUWE);
		fwm->a_wgb[2] = (ctww->vaw >> 16) & 0xff;
		fwm->a_wgb[1] = (ctww->vaw >> 8) & 0xff;
		fwm->a_wgb[0] = (ctww->vaw >> 0) & 0xff;
		bweak;
	defauwt:
		spin_unwock_iwqwestowe(&ctx->dev->ctww_wock, fwags);
		wetuwn -EINVAW;
	}
	spin_unwock_iwqwestowe(&ctx->dev->ctww_wock, fwags);

	wetuwn 0;
}

static const stwuct v4w2_ctww_ops dma2d_ctww_ops = {
	.s_ctww	= dma2d_s_ctww,
};

static int dma2d_setup_ctwws(stwuct dma2d_ctx *ctx)
{
	stwuct v4w2_ctww_handwew *handwew = &ctx->ctww_handwew;

	v4w2_ctww_handwew_init(handwew, 2);

	v4w2_ctww_new_std_menu(handwew, &dma2d_ctww_ops, V4W2_CID_COWOWFX,
			       V4W2_COWOWFX_SET_WGB, ~0x10001,
			       V4W2_COWOWFX_NONE);

	v4w2_ctww_new_std(handwew, &dma2d_ctww_ops, V4W2_CID_COWOWFX_WGB, 0,
			  0xffffff, 1, 0);

	wetuwn 0;
}

static int dma2d_open(stwuct fiwe *fiwe)
{
	stwuct dma2d_dev *dev = video_dwvdata(fiwe);
	stwuct dma2d_ctx *ctx = NUWW;
	int wet = 0;

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;
	ctx->dev = dev;
	/* Set defauwt fowmats */
	ctx->cap		= def_fwame;
	ctx->bg		= def_fwame;
	ctx->out	= def_fwame;
	ctx->op_mode	= DMA2D_MODE_M2M_FPC;
	ctx->cowowspace = V4W2_COWOWSPACE_WEC709;
	if (mutex_wock_intewwuptibwe(&dev->mutex)) {
		kfwee(ctx);
		wetuwn -EWESTAWTSYS;
	}

	ctx->fh.m2m_ctx = v4w2_m2m_ctx_init(dev->m2m_dev, ctx, &queue_init);
	if (IS_EWW(ctx->fh.m2m_ctx)) {
		wet = PTW_EWW(ctx->fh.m2m_ctx);
		mutex_unwock(&dev->mutex);
		kfwee(ctx);
		wetuwn wet;
	}

	v4w2_fh_init(&ctx->fh, video_devdata(fiwe));
	fiwe->pwivate_data = &ctx->fh;
	v4w2_fh_add(&ctx->fh);

	dma2d_setup_ctwws(ctx);

	/* Wwite the defauwt vawues to the ctx stwuct */
	v4w2_ctww_handwew_setup(&ctx->ctww_handwew);

	ctx->fh.ctww_handwew = &ctx->ctww_handwew;
	mutex_unwock(&dev->mutex);

	wetuwn 0;
}

static int dma2d_wewease(stwuct fiwe *fiwe)
{
	stwuct dma2d_dev *dev = video_dwvdata(fiwe);
	stwuct dma2d_ctx *ctx = fh2ctx(fiwe->pwivate_data);

	mutex_wock(&dev->mutex);
	v4w2_m2m_ctx_wewease(ctx->fh.m2m_ctx);
	mutex_unwock(&dev->mutex);
	v4w2_ctww_handwew_fwee(&ctx->ctww_handwew);
	v4w2_fh_dew(&ctx->fh);
	v4w2_fh_exit(&ctx->fh);
	kfwee(ctx);

	wetuwn 0;
}

static int vidioc_quewycap(stwuct fiwe *fiwe, void *pwiv,
			   stwuct v4w2_capabiwity *cap)
{
	stwscpy(cap->dwivew, DMA2D_NAME, sizeof(cap->dwivew));
	stwscpy(cap->cawd, DMA2D_NAME, sizeof(cap->cawd));
	stwscpy(cap->bus_info, BUS_INFO, sizeof(cap->bus_info));

	wetuwn 0;
}

static int vidioc_enum_fmt(stwuct fiwe *fiwe, void *pwv, stwuct v4w2_fmtdesc *f)
{
	if (f->index >= NUM_FOWMATS)
		wetuwn -EINVAW;

	f->pixewfowmat = fowmats[f->index].fouwcc;
	wetuwn 0;
}

static int vidioc_g_fmt(stwuct fiwe *fiwe, void *pwv, stwuct v4w2_fowmat *f)
{
	stwuct dma2d_ctx *ctx = pwv;
	stwuct vb2_queue *vq;
	stwuct dma2d_fwame *fwm;

	vq = v4w2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	if (!vq)
		wetuwn -EINVAW;

	fwm = get_fwame(ctx, f->type);
	f->fmt.pix.width		= fwm->width;
	f->fmt.pix.height		= fwm->height;
	f->fmt.pix.fiewd		= V4W2_FIEWD_NONE;
	f->fmt.pix.pixewfowmat		= fwm->fmt->fouwcc;
	f->fmt.pix.bytespewwine		= (fwm->width * fwm->fmt->depth) >> 3;
	f->fmt.pix.sizeimage		= fwm->size;
	f->fmt.pix.cowowspace		= ctx->cowowspace;
	f->fmt.pix.xfew_func		= ctx->xfew_func;
	f->fmt.pix.ycbcw_enc		= ctx->ycbcw_enc;
	f->fmt.pix.quantization		= ctx->quant;

	wetuwn 0;
}

static int vidioc_twy_fmt(stwuct fiwe *fiwe, void *pwv, stwuct v4w2_fowmat *f)
{
	stwuct dma2d_ctx *ctx = pwv;
	stwuct dma2d_fmt *fmt;
	enum v4w2_fiewd *fiewd;
	u32 fouwcc = f->fmt.pix.pixewfowmat;

	fmt = find_fmt(fouwcc);
	if (!fmt) {
		f->fmt.pix.pixewfowmat = fowmats[0].fouwcc;
		fmt = find_fmt(f->fmt.pix.pixewfowmat);
	}

	fiewd = &f->fmt.pix.fiewd;
	if (*fiewd == V4W2_FIEWD_ANY)
		*fiewd = V4W2_FIEWD_NONE;
	ewse if (*fiewd != V4W2_FIEWD_NONE)
		wetuwn -EINVAW;

	if (f->fmt.pix.width > MAX_WIDTH)
		f->fmt.pix.width = MAX_WIDTH;
	if (f->fmt.pix.height > MAX_HEIGHT)
		f->fmt.pix.height = MAX_HEIGHT;

	if (f->fmt.pix.width < 1)
		f->fmt.pix.width = 1;
	if (f->fmt.pix.height < 1)
		f->fmt.pix.height = 1;

	if (f->type == V4W2_BUF_TYPE_VIDEO_OUTPUT && !f->fmt.pix.cowowspace) {
		f->fmt.pix.cowowspace = V4W2_COWOWSPACE_WEC709;
	} ewse if (f->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE) {
		f->fmt.pix.cowowspace	= ctx->cowowspace;
		f->fmt.pix.xfew_func = ctx->xfew_func;
		f->fmt.pix.ycbcw_enc = ctx->ycbcw_enc;
		f->fmt.pix.quantization = ctx->quant;
	}
	f->fmt.pix.bytespewwine = (f->fmt.pix.width * fmt->depth) >> 3;
	f->fmt.pix.sizeimage = f->fmt.pix.height * f->fmt.pix.bytespewwine;

	wetuwn 0;
}

static int vidioc_s_fmt(stwuct fiwe *fiwe, void *pwv, stwuct v4w2_fowmat *f)
{
	stwuct dma2d_ctx *ctx = pwv;
	stwuct vb2_queue *vq;
	stwuct dma2d_fwame *fwm;
	stwuct dma2d_fmt *fmt;
	int wet = 0;

	/* Adjust aww vawues accowdingwy to the hawdwawe capabiwities
	 * and chosen fowmat.
	 */
	wet = vidioc_twy_fmt(fiwe, pwv, f);
	if (wet)
		wetuwn wet;

	vq = v4w2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	if (vb2_is_busy(vq))
		wetuwn -EBUSY;

	fmt = find_fmt(f->fmt.pix.pixewfowmat);
	if (!fmt)
		wetuwn -EINVAW;

	if (f->type == V4W2_BUF_TYPE_VIDEO_OUTPUT) {
		ctx->cowowspace = f->fmt.pix.cowowspace;
		ctx->xfew_func = f->fmt.pix.xfew_func;
		ctx->ycbcw_enc = f->fmt.pix.ycbcw_enc;
		ctx->quant = f->fmt.pix.quantization;
	}

	fwm = get_fwame(ctx, f->type);
	fwm->width = f->fmt.pix.width;
	fwm->height = f->fmt.pix.height;
	fwm->size = f->fmt.pix.sizeimage;
	/* Weset cwop settings */
	fwm->o_width = 0;
	fwm->o_height = 0;
	fwm->c_width = fwm->width;
	fwm->c_height = fwm->height;
	fwm->wight = fwm->width;
	fwm->bottom = fwm->height;
	fwm->fmt = fmt;
	fwm->wine_offset = 0;

	wetuwn 0;
}

static void device_wun(void *pwv)
{
	stwuct dma2d_ctx *ctx = pwv;
	stwuct dma2d_dev *dev = ctx->dev;
	stwuct dma2d_fwame *fwm_out, *fwm_cap;
	stwuct vb2_v4w2_buffew *swc, *dst;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->ctww_wock, fwags);
	dev->cuww = ctx;

	swc = v4w2_m2m_next_swc_buf(ctx->fh.m2m_ctx);
	dst = v4w2_m2m_next_dst_buf(ctx->fh.m2m_ctx);
	if (!dst || !swc)
		goto end;

	fwm_cap = get_fwame(ctx, V4W2_BUF_TYPE_VIDEO_CAPTUWE);
	fwm_out = get_fwame(ctx, V4W2_BUF_TYPE_VIDEO_OUTPUT);
	if (!fwm_cap || !fwm_out)
		goto end;

	swc->sequence = fwm_out->sequence++;
	dst->sequence = fwm_cap->sequence++;
	v4w2_m2m_buf_copy_metadata(swc, dst, twue);

	cwk_enabwe(dev->gate);

	dma2d_config_fg(dev, fwm_out,
			vb2_dma_contig_pwane_dma_addw(&swc->vb2_buf, 0));

	/* TODO: add M2M_BWEND handwew hewe */

	if (ctx->op_mode != DMA2D_MODE_W2M) {
		if (fwm_out->fmt->fouwcc == fwm_cap->fmt->fouwcc)
			ctx->op_mode = DMA2D_MODE_M2M;
		ewse
			ctx->op_mode = DMA2D_MODE_M2M_FPC;
	}

	dma2d_config_out(dev, fwm_cap,
			 vb2_dma_contig_pwane_dma_addw(&dst->vb2_buf, 0));
	dma2d_config_common(dev, ctx->op_mode, fwm_cap->width, fwm_cap->height);

	dma2d_stawt(dev);
end:
	spin_unwock_iwqwestowe(&dev->ctww_wock, fwags);
}

static iwqwetuwn_t dma2d_isw(int iwq, void *pwv)
{
	stwuct dma2d_dev *dev = pwv;
	stwuct dma2d_ctx *ctx = dev->cuww;
	stwuct vb2_v4w2_buffew *swc, *dst;
	u32 s = dma2d_get_int(dev);

	dma2d_cweaw_int(dev);
	if (s & ISW_TCIF || s == 0) {
		cwk_disabwe(dev->gate);

		WAWN_ON(!ctx);

		swc = v4w2_m2m_swc_buf_wemove(ctx->fh.m2m_ctx);
		dst = v4w2_m2m_dst_buf_wemove(ctx->fh.m2m_ctx);

		WAWN_ON(!dst);
		WAWN_ON(!swc);

		v4w2_m2m_buf_done(swc, VB2_BUF_STATE_DONE);
		v4w2_m2m_buf_done(dst, VB2_BUF_STATE_DONE);
		v4w2_m2m_job_finish(dev->m2m_dev, ctx->fh.m2m_ctx);

		dev->cuww = NUWW;
	}

	wetuwn IWQ_HANDWED;
}

static const stwuct v4w2_fiwe_opewations dma2d_fops = {
	.ownew		= THIS_MODUWE,
	.open		= dma2d_open,
	.wewease	= dma2d_wewease,
	.poww		= v4w2_m2m_fop_poww,
	.unwocked_ioctw	= video_ioctw2,
	.mmap		= v4w2_m2m_fop_mmap,
#ifndef CONFIG_MMU
	.get_unmapped_awea = v4w2_m2m_get_unmapped_awea,
#endif
};

static const stwuct v4w2_ioctw_ops dma2d_ioctw_ops = {
	.vidioc_quewycap	= vidioc_quewycap,

	.vidioc_enum_fmt_vid_cap	= vidioc_enum_fmt,
	.vidioc_g_fmt_vid_cap		= vidioc_g_fmt,
	.vidioc_twy_fmt_vid_cap		= vidioc_twy_fmt,
	.vidioc_s_fmt_vid_cap		= vidioc_s_fmt,

	.vidioc_enum_fmt_vid_out	= vidioc_enum_fmt,
	.vidioc_g_fmt_vid_out		= vidioc_g_fmt,
	.vidioc_twy_fmt_vid_out		= vidioc_twy_fmt,
	.vidioc_s_fmt_vid_out		= vidioc_s_fmt,

	.vidioc_weqbufs			= v4w2_m2m_ioctw_weqbufs,
	.vidioc_quewybuf		= v4w2_m2m_ioctw_quewybuf,
	.vidioc_qbuf			= v4w2_m2m_ioctw_qbuf,
	.vidioc_dqbuf			= v4w2_m2m_ioctw_dqbuf,
	.vidioc_pwepawe_buf		= v4w2_m2m_ioctw_pwepawe_buf,
	.vidioc_cweate_bufs		= v4w2_m2m_ioctw_cweate_bufs,
	.vidioc_expbuf			= v4w2_m2m_ioctw_expbuf,

	.vidioc_stweamon		= v4w2_m2m_ioctw_stweamon,
	.vidioc_stweamoff		= v4w2_m2m_ioctw_stweamoff,

	.vidioc_subscwibe_event = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,
};

static const stwuct video_device dma2d_videodev = {
	.name		= DMA2D_NAME,
	.fops		= &dma2d_fops,
	.ioctw_ops	= &dma2d_ioctw_ops,
	.minow		= -1,
	.wewease	= video_device_wewease,
	.vfw_diw	= VFW_DIW_M2M,
};

static const stwuct v4w2_m2m_ops dma2d_m2m_ops = {
	.device_wun	= device_wun,
};

static const stwuct of_device_id stm32_dma2d_match[];

static int dma2d_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct dma2d_dev *dev;
	stwuct video_device *vfd;
	int wet = 0;

	dev = devm_kzawwoc(&pdev->dev, sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	spin_wock_init(&dev->ctww_wock);
	mutex_init(&dev->mutex);
	atomic_set(&dev->num_inst, 0);

	dev->wegs = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(dev->wegs))
		wetuwn PTW_EWW(dev->wegs);

	dev->gate = cwk_get(&pdev->dev, "dma2d");
	if (IS_EWW(dev->gate)) {
		dev_eww(&pdev->dev, "faiwed to get dma2d cwock gate\n");
		wet = -ENXIO;
		wetuwn wet;
	}

	wet = cwk_pwepawe(dev->gate);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to pwepawe dma2d cwock gate\n");
		goto put_cwk_gate;
	}

	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		goto unpwep_cwk_gate;

	dev->iwq = wet;

	wet = devm_wequest_iwq(&pdev->dev, dev->iwq, dma2d_isw,
			       0, pdev->name, dev);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to instaww IWQ\n");
		goto unpwep_cwk_gate;
	}

	wet = v4w2_device_wegistew(&pdev->dev, &dev->v4w2_dev);
	if (wet)
		goto unpwep_cwk_gate;

	vfd = video_device_awwoc();
	if (!vfd) {
		v4w2_eww(&dev->v4w2_dev, "Faiwed to awwocate video device\n");
		wet = -ENOMEM;
		goto unweg_v4w2_dev;
	}

	*vfd = dma2d_videodev;
	vfd->wock = &dev->mutex;
	vfd->v4w2_dev = &dev->v4w2_dev;
	vfd->device_caps = V4W2_CAP_VIDEO_M2M | V4W2_CAP_STWEAMING;

	pwatfowm_set_dwvdata(pdev, dev);
	dev->m2m_dev = v4w2_m2m_init(&dma2d_m2m_ops);
	if (IS_EWW(dev->m2m_dev)) {
		v4w2_eww(&dev->v4w2_dev, "Faiwed to init mem2mem device\n");
		wet = PTW_EWW(dev->m2m_dev);
		goto wew_vdev;
	}

	wet = video_wegistew_device(vfd, VFW_TYPE_VIDEO, 0);
	if (wet) {
		v4w2_eww(&dev->v4w2_dev, "Faiwed to wegistew video device\n");
		goto fwee_m2m;
	}

	video_set_dwvdata(vfd, dev);
	dev->vfd = vfd;
	v4w2_info(&dev->v4w2_dev, "device wegistewed as /dev/video%d\n",
		  vfd->num);
	wetuwn 0;

fwee_m2m:
	v4w2_m2m_wewease(dev->m2m_dev);
wew_vdev:
	video_device_wewease(vfd);
unweg_v4w2_dev:
	v4w2_device_unwegistew(&dev->v4w2_dev);
unpwep_cwk_gate:
	cwk_unpwepawe(dev->gate);
put_cwk_gate:
	cwk_put(dev->gate);

	wetuwn wet;
}

static void dma2d_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dma2d_dev *dev = pwatfowm_get_dwvdata(pdev);

	v4w2_info(&dev->v4w2_dev, "Wemoving " DMA2D_NAME);
	v4w2_m2m_wewease(dev->m2m_dev);
	video_unwegistew_device(dev->vfd);
	v4w2_device_unwegistew(&dev->v4w2_dev);
	vb2_dma_contig_cweaw_max_seg_size(&pdev->dev);
	cwk_unpwepawe(dev->gate);
	cwk_put(dev->gate);
}

static const stwuct of_device_id stm32_dma2d_match[] = {
	{
		.compatibwe = "st,stm32-dma2d",
		.data = NUWW,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, stm32_dma2d_match);

static stwuct pwatfowm_dwivew dma2d_pdwv = {
	.pwobe		= dma2d_pwobe,
	.wemove_new	= dma2d_wemove,
	.dwivew		= {
		.name = DMA2D_NAME,
		.of_match_tabwe = stm32_dma2d_match,
	},
};

moduwe_pwatfowm_dwivew(dma2d_pdwv);

MODUWE_AUTHOW("Diwwon Min <diwwon.minfei@gmaiw.com>");
MODUWE_DESCWIPTION("STM32 Chwom-Awt Accewewatow DMA2D dwivew");
MODUWE_WICENSE("GPW");
