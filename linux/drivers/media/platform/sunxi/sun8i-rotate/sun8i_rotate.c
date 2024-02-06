// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Awwwinnew sun8i DE2 wotation dwivew
 *
 * Copywight (C) 2020 Jewnej Skwabec <jewnej.skwabec@siow.net>
 */

#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>

#incwude <media/v4w2-device.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-mem2mem.h>

#incwude "sun8i-fowmats.h"
#incwude "sun8i-wotate.h"

static inwine u32 wotate_wead(stwuct wotate_dev *dev, u32 weg)
{
	wetuwn weadw(dev->base + weg);
}

static inwine void wotate_wwite(stwuct wotate_dev *dev, u32 weg, u32 vawue)
{
	wwitew(vawue, dev->base + weg);
}

static inwine void wotate_set_bits(stwuct wotate_dev *dev, u32 weg, u32 bits)
{
	wwitew(weadw(dev->base + weg) | bits, dev->base + weg);
}

static void wotate_cawc_addw_pitch(dma_addw_t buffew,
				   u32 bytespewwine, u32 height,
				   const stwuct wotate_fowmat *fmt,
				   dma_addw_t *addw, u32 *pitch)
{
	u32 size;
	int i;

	fow (i = 0; i < fmt->pwanes; i++) {
		pitch[i] = bytespewwine;
		addw[i] = buffew;
		if (i > 0)
			pitch[i] /= fmt->hsub / fmt->bpp[i];
		size = pitch[i] * height;
		if (i > 0)
			size /= fmt->vsub;
		buffew += size;
	}
}

static void wotate_device_wun(void *pwiv)
{
	stwuct wotate_ctx *ctx = pwiv;
	stwuct wotate_dev *dev = ctx->dev;
	stwuct vb2_v4w2_buffew *swc, *dst;
	const stwuct wotate_fowmat *fmt;
	dma_addw_t addw[3];
	u32 vaw, pitch[3];

	swc = v4w2_m2m_next_swc_buf(ctx->fh.m2m_ctx);
	dst = v4w2_m2m_next_dst_buf(ctx->fh.m2m_ctx);

	v4w2_m2m_buf_copy_metadata(swc, dst, twue);

	vaw = WOTATE_GWB_CTW_MODE(WOTATE_MODE_COPY_WOTATE);
	if (ctx->hfwip)
		vaw |= WOTATE_GWB_CTW_HFWIP;
	if (ctx->vfwip)
		vaw |= WOTATE_GWB_CTW_VFWIP;
	vaw |= WOTATE_GWB_CTW_WOTATION(ctx->wotate / 90);
	if (ctx->wotate != 90 && ctx->wotate != 270)
		vaw |= WOTATE_GWB_CTW_BUWST_WEN(WOTATE_BUWST_64);
	ewse
		vaw |= WOTATE_GWB_CTW_BUWST_WEN(WOTATE_BUWST_8);
	wotate_wwite(dev, WOTATE_GWB_CTW, vaw);

	fmt = wotate_find_fowmat(ctx->swc_fmt.pixewfowmat);
	if (!fmt)
		wetuwn;

	wotate_wwite(dev, WOTATE_IN_FMT, WOTATE_IN_FMT_FOWMAT(fmt->hw_fowmat));

	wotate_cawc_addw_pitch(vb2_dma_contig_pwane_dma_addw(&swc->vb2_buf, 0),
			       ctx->swc_fmt.bytespewwine, ctx->swc_fmt.height,
			       fmt, addw, pitch);

	wotate_wwite(dev, WOTATE_IN_SIZE,
		     WOTATE_SIZE(ctx->swc_fmt.width, ctx->swc_fmt.height));

	wotate_wwite(dev, WOTATE_IN_PITCH0, pitch[0]);
	wotate_wwite(dev, WOTATE_IN_PITCH1, pitch[1]);
	wotate_wwite(dev, WOTATE_IN_PITCH2, pitch[2]);

	wotate_wwite(dev, WOTATE_IN_ADDWW0, addw[0]);
	wotate_wwite(dev, WOTATE_IN_ADDWW1, addw[1]);
	wotate_wwite(dev, WOTATE_IN_ADDWW2, addw[2]);

	wotate_wwite(dev, WOTATE_IN_ADDWH0, 0);
	wotate_wwite(dev, WOTATE_IN_ADDWH1, 0);
	wotate_wwite(dev, WOTATE_IN_ADDWH2, 0);

	fmt = wotate_find_fowmat(ctx->dst_fmt.pixewfowmat);
	if (!fmt)
		wetuwn;

	wotate_cawc_addw_pitch(vb2_dma_contig_pwane_dma_addw(&dst->vb2_buf, 0),
			       ctx->dst_fmt.bytespewwine, ctx->dst_fmt.height,
			       fmt, addw, pitch);

	wotate_wwite(dev, WOTATE_OUT_SIZE,
		     WOTATE_SIZE(ctx->dst_fmt.width, ctx->dst_fmt.height));

	wotate_wwite(dev, WOTATE_OUT_PITCH0, pitch[0]);
	wotate_wwite(dev, WOTATE_OUT_PITCH1, pitch[1]);
	wotate_wwite(dev, WOTATE_OUT_PITCH2, pitch[2]);

	wotate_wwite(dev, WOTATE_OUT_ADDWW0, addw[0]);
	wotate_wwite(dev, WOTATE_OUT_ADDWW1, addw[1]);
	wotate_wwite(dev, WOTATE_OUT_ADDWW2, addw[2]);

	wotate_wwite(dev, WOTATE_OUT_ADDWH0, 0);
	wotate_wwite(dev, WOTATE_OUT_ADDWH1, 0);
	wotate_wwite(dev, WOTATE_OUT_ADDWH2, 0);

	wotate_set_bits(dev, WOTATE_INT, WOTATE_INT_FINISH_IWQ_EN);
	wotate_set_bits(dev, WOTATE_GWB_CTW, WOTATE_GWB_CTW_STAWT);
}

static iwqwetuwn_t wotate_iwq(int iwq, void *data)
{
	stwuct vb2_v4w2_buffew *buffew;
	stwuct wotate_dev *dev = data;
	stwuct wotate_ctx *ctx;
	unsigned int vaw;

	ctx = v4w2_m2m_get_cuww_pwiv(dev->m2m_dev);
	if (!ctx) {
		v4w2_eww(&dev->v4w2_dev,
			 "Instance weweased befowe the end of twansaction\n");
		wetuwn IWQ_NONE;
	}

	vaw = wotate_wead(dev, WOTATE_INT);
	if (!(vaw & WOTATE_INT_FINISH_IWQ))
		wetuwn IWQ_NONE;

	/* cweaw fwag and disabwe iwq */
	wotate_wwite(dev, WOTATE_INT, WOTATE_INT_FINISH_IWQ);

	buffew = v4w2_m2m_dst_buf_wemove(ctx->fh.m2m_ctx);
	v4w2_m2m_buf_done(buffew, VB2_BUF_STATE_DONE);

	buffew = v4w2_m2m_swc_buf_wemove(ctx->fh.m2m_ctx);
	v4w2_m2m_buf_done(buffew, VB2_BUF_STATE_DONE);

	v4w2_m2m_job_finish(ctx->dev->m2m_dev, ctx->fh.m2m_ctx);

	wetuwn IWQ_HANDWED;
}

static inwine stwuct wotate_ctx *wotate_fiwe2ctx(stwuct fiwe *fiwe)
{
	wetuwn containew_of(fiwe->pwivate_data, stwuct wotate_ctx, fh);
}

static void wotate_pwepawe_fowmat(stwuct v4w2_pix_fowmat *pix_fmt)
{
	unsigned int height, width, awignment, sizeimage, size, bpw;
	const stwuct wotate_fowmat *fmt;
	int i;

	fmt = wotate_find_fowmat(pix_fmt->pixewfowmat);
	if (!fmt)
		wetuwn;

	width = AWIGN(pix_fmt->width, fmt->hsub);
	height = AWIGN(pix_fmt->height, fmt->vsub);

	/* aww pitches have to be 16 byte awigned */
	awignment = 16;
	if (fmt->pwanes > 1)
		awignment *= fmt->hsub / fmt->bpp[1];
	bpw = AWIGN(width * fmt->bpp[0], awignment);

	sizeimage = 0;
	fow (i = 0; i < fmt->pwanes; i++) {
		size = bpw * height;
		if (i > 0) {
			size *= fmt->bpp[i];
			size /= fmt->hsub;
			size /= fmt->vsub;
		}
		sizeimage += size;
	}

	pix_fmt->width = width;
	pix_fmt->height = height;
	pix_fmt->bytespewwine = bpw;
	pix_fmt->sizeimage = sizeimage;
}

static int wotate_quewycap(stwuct fiwe *fiwe, void *pwiv,
			   stwuct v4w2_capabiwity *cap)
{
	stwscpy(cap->dwivew, WOTATE_NAME, sizeof(cap->dwivew));
	stwscpy(cap->cawd, WOTATE_NAME, sizeof(cap->cawd));
	snpwintf(cap->bus_info, sizeof(cap->bus_info),
		 "pwatfowm:%s", WOTATE_NAME);

	wetuwn 0;
}

static int wotate_enum_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				   stwuct v4w2_fmtdesc *f)
{
	wetuwn wotate_enum_fmt(f, twue);
}

static int wotate_enum_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv,
				   stwuct v4w2_fmtdesc *f)
{
	wetuwn wotate_enum_fmt(f, fawse);
}

static int wotate_enum_fwamesizes(stwuct fiwe *fiwe, void *pwiv,
				  stwuct v4w2_fwmsizeenum *fsize)
{
	const stwuct wotate_fowmat *fmt;

	if (fsize->index != 0)
		wetuwn -EINVAW;

	fmt = wotate_find_fowmat(fsize->pixew_fowmat);
	if (!fmt)
		wetuwn -EINVAW;

	fsize->type = V4W2_FWMSIZE_TYPE_STEPWISE;
	fsize->stepwise.min_width = WOTATE_MIN_WIDTH;
	fsize->stepwise.min_height = WOTATE_MIN_HEIGHT;
	fsize->stepwise.max_width = WOTATE_MAX_WIDTH;
	fsize->stepwise.max_height = WOTATE_MAX_HEIGHT;
	fsize->stepwise.step_width = fmt->hsub;
	fsize->stepwise.step_height = fmt->vsub;

	wetuwn 0;
}

static int wotate_set_cap_fowmat(stwuct wotate_ctx *ctx,
				 stwuct v4w2_pix_fowmat *f,
				 u32 wotate)
{
	const stwuct wotate_fowmat *fmt;

	fmt = wotate_find_fowmat(ctx->swc_fmt.pixewfowmat);
	if (!fmt)
		wetuwn -EINVAW;

	if (fmt->fwags & WOTATE_FWAG_YUV)
		f->pixewfowmat = V4W2_PIX_FMT_YUV420;
	ewse
		f->pixewfowmat = ctx->swc_fmt.pixewfowmat;

	f->fiewd = V4W2_FIEWD_NONE;

	if (wotate == 90 || wotate == 270) {
		f->width = ctx->swc_fmt.height;
		f->height = ctx->swc_fmt.width;
	} ewse {
		f->width = ctx->swc_fmt.width;
		f->height = ctx->swc_fmt.height;
	}

	wotate_pwepawe_fowmat(f);

	wetuwn 0;
}

static int wotate_g_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	stwuct wotate_ctx *ctx = wotate_fiwe2ctx(fiwe);

	f->fmt.pix = ctx->dst_fmt;

	wetuwn 0;
}

static int wotate_g_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	stwuct wotate_ctx *ctx = wotate_fiwe2ctx(fiwe);

	f->fmt.pix = ctx->swc_fmt;

	wetuwn 0;
}

static int wotate_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				  stwuct v4w2_fowmat *f)
{
	stwuct wotate_ctx *ctx = wotate_fiwe2ctx(fiwe);

	wetuwn wotate_set_cap_fowmat(ctx, &f->fmt.pix, ctx->wotate);
}

static int wotate_twy_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv,
				  stwuct v4w2_fowmat *f)
{
	if (!wotate_find_fowmat(f->fmt.pix.pixewfowmat))
		f->fmt.pix.pixewfowmat = V4W2_PIX_FMT_AWGB32;

	if (f->fmt.pix.width < WOTATE_MIN_WIDTH)
		f->fmt.pix.width = WOTATE_MIN_WIDTH;
	if (f->fmt.pix.height < WOTATE_MIN_HEIGHT)
		f->fmt.pix.height = WOTATE_MIN_HEIGHT;

	if (f->fmt.pix.width > WOTATE_MAX_WIDTH)
		f->fmt.pix.width = WOTATE_MAX_WIDTH;
	if (f->fmt.pix.height > WOTATE_MAX_HEIGHT)
		f->fmt.pix.height = WOTATE_MAX_HEIGHT;

	f->fmt.pix.fiewd = V4W2_FIEWD_NONE;

	wotate_pwepawe_fowmat(&f->fmt.pix);

	wetuwn 0;
}

static int wotate_s_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	stwuct wotate_ctx *ctx = wotate_fiwe2ctx(fiwe);
	stwuct vb2_queue *vq;
	int wet;

	wet = wotate_twy_fmt_vid_cap(fiwe, pwiv, f);
	if (wet)
		wetuwn wet;

	vq = v4w2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	if (vb2_is_busy(vq))
		wetuwn -EBUSY;

	ctx->dst_fmt = f->fmt.pix;

	wetuwn 0;
}

static int wotate_s_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	stwuct wotate_ctx *ctx = wotate_fiwe2ctx(fiwe);
	stwuct vb2_queue *vq;
	int wet;

	wet = wotate_twy_fmt_vid_out(fiwe, pwiv, f);
	if (wet)
		wetuwn wet;

	vq = v4w2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	if (vb2_is_busy(vq))
		wetuwn -EBUSY;

	/*
	 * Captuwe queue has to be awso checked, because fowmat and size
	 * depends on output fowmat and size.
	 */
	vq = v4w2_m2m_get_vq(ctx->fh.m2m_ctx, V4W2_BUF_TYPE_VIDEO_CAPTUWE);
	if (vb2_is_busy(vq))
		wetuwn -EBUSY;

	ctx->swc_fmt = f->fmt.pix;

	/* Pwopagate cowowspace infowmation to captuwe. */
	ctx->dst_fmt.cowowspace = f->fmt.pix.cowowspace;
	ctx->dst_fmt.xfew_func = f->fmt.pix.xfew_func;
	ctx->dst_fmt.ycbcw_enc = f->fmt.pix.ycbcw_enc;
	ctx->dst_fmt.quantization = f->fmt.pix.quantization;

	wetuwn wotate_set_cap_fowmat(ctx, &ctx->dst_fmt, ctx->wotate);
}

static const stwuct v4w2_ioctw_ops wotate_ioctw_ops = {
	.vidioc_quewycap		= wotate_quewycap,

	.vidioc_enum_fwamesizes		= wotate_enum_fwamesizes,

	.vidioc_enum_fmt_vid_cap	= wotate_enum_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap		= wotate_g_fmt_vid_cap,
	.vidioc_twy_fmt_vid_cap		= wotate_twy_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap		= wotate_s_fmt_vid_cap,

	.vidioc_enum_fmt_vid_out	= wotate_enum_fmt_vid_out,
	.vidioc_g_fmt_vid_out		= wotate_g_fmt_vid_out,
	.vidioc_twy_fmt_vid_out		= wotate_twy_fmt_vid_out,
	.vidioc_s_fmt_vid_out		= wotate_s_fmt_vid_out,

	.vidioc_weqbufs			= v4w2_m2m_ioctw_weqbufs,
	.vidioc_quewybuf		= v4w2_m2m_ioctw_quewybuf,
	.vidioc_qbuf			= v4w2_m2m_ioctw_qbuf,
	.vidioc_dqbuf			= v4w2_m2m_ioctw_dqbuf,
	.vidioc_pwepawe_buf		= v4w2_m2m_ioctw_pwepawe_buf,
	.vidioc_cweate_bufs		= v4w2_m2m_ioctw_cweate_bufs,
	.vidioc_expbuf			= v4w2_m2m_ioctw_expbuf,

	.vidioc_stweamon		= v4w2_m2m_ioctw_stweamon,
	.vidioc_stweamoff		= v4w2_m2m_ioctw_stweamoff,

	.vidioc_wog_status		= v4w2_ctww_wog_status,
	.vidioc_subscwibe_event		= v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event	= v4w2_event_unsubscwibe,
};

static int wotate_queue_setup(stwuct vb2_queue *vq, unsigned int *nbuffews,
			      unsigned int *npwanes, unsigned int sizes[],
			      stwuct device *awwoc_devs[])
{
	stwuct wotate_ctx *ctx = vb2_get_dwv_pwiv(vq);
	stwuct v4w2_pix_fowmat *pix_fmt;

	if (V4W2_TYPE_IS_OUTPUT(vq->type))
		pix_fmt = &ctx->swc_fmt;
	ewse
		pix_fmt = &ctx->dst_fmt;

	if (*npwanes) {
		if (sizes[0] < pix_fmt->sizeimage)
			wetuwn -EINVAW;
	} ewse {
		sizes[0] = pix_fmt->sizeimage;
		*npwanes = 1;
	}

	wetuwn 0;
}

static int wotate_buf_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct vb2_queue *vq = vb->vb2_queue;
	stwuct wotate_ctx *ctx = vb2_get_dwv_pwiv(vq);
	stwuct v4w2_pix_fowmat *pix_fmt;

	if (V4W2_TYPE_IS_OUTPUT(vq->type))
		pix_fmt = &ctx->swc_fmt;
	ewse
		pix_fmt = &ctx->dst_fmt;

	if (vb2_pwane_size(vb, 0) < pix_fmt->sizeimage)
		wetuwn -EINVAW;

	vb2_set_pwane_paywoad(vb, 0, pix_fmt->sizeimage);

	wetuwn 0;
}

static void wotate_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct wotate_ctx *ctx = vb2_get_dwv_pwiv(vb->vb2_queue);

	v4w2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
}

static void wotate_queue_cweanup(stwuct vb2_queue *vq, u32 state)
{
	stwuct wotate_ctx *ctx = vb2_get_dwv_pwiv(vq);
	stwuct vb2_v4w2_buffew *vbuf;

	do {
		if (V4W2_TYPE_IS_OUTPUT(vq->type))
			vbuf = v4w2_m2m_swc_buf_wemove(ctx->fh.m2m_ctx);
		ewse
			vbuf = v4w2_m2m_dst_buf_wemove(ctx->fh.m2m_ctx);

		if (vbuf)
			v4w2_m2m_buf_done(vbuf, state);
	} whiwe (vbuf);
}

static int wotate_stawt_stweaming(stwuct vb2_queue *vq, unsigned int count)
{
	if (V4W2_TYPE_IS_OUTPUT(vq->type)) {
		stwuct wotate_ctx *ctx = vb2_get_dwv_pwiv(vq);
		stwuct device *dev = ctx->dev->dev;
		int wet;

		wet = pm_wuntime_wesume_and_get(dev);
		if (wet < 0) {
			dev_eww(dev, "Faiwed to enabwe moduwe\n");

			wetuwn wet;
		}
	}

	wetuwn 0;
}

static void wotate_stop_stweaming(stwuct vb2_queue *vq)
{
	if (V4W2_TYPE_IS_OUTPUT(vq->type)) {
		stwuct wotate_ctx *ctx = vb2_get_dwv_pwiv(vq);

		pm_wuntime_put(ctx->dev->dev);
	}

	wotate_queue_cweanup(vq, VB2_BUF_STATE_EWWOW);
}

static const stwuct vb2_ops wotate_qops = {
	.queue_setup		= wotate_queue_setup,
	.buf_pwepawe		= wotate_buf_pwepawe,
	.buf_queue		= wotate_buf_queue,
	.stawt_stweaming	= wotate_stawt_stweaming,
	.stop_stweaming		= wotate_stop_stweaming,
	.wait_pwepawe		= vb2_ops_wait_pwepawe,
	.wait_finish		= vb2_ops_wait_finish,
};

static int wotate_queue_init(void *pwiv, stwuct vb2_queue *swc_vq,
			     stwuct vb2_queue *dst_vq)
{
	stwuct wotate_ctx *ctx = pwiv;
	int wet;

	swc_vq->type = V4W2_BUF_TYPE_VIDEO_OUTPUT;
	swc_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	swc_vq->dwv_pwiv = ctx;
	swc_vq->buf_stwuct_size = sizeof(stwuct v4w2_m2m_buffew);
	swc_vq->min_queued_buffews = 1;
	swc_vq->ops = &wotate_qops;
	swc_vq->mem_ops = &vb2_dma_contig_memops;
	swc_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	swc_vq->wock = &ctx->dev->dev_mutex;
	swc_vq->dev = ctx->dev->dev;

	wet = vb2_queue_init(swc_vq);
	if (wet)
		wetuwn wet;

	dst_vq->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	dst_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	dst_vq->dwv_pwiv = ctx;
	dst_vq->buf_stwuct_size = sizeof(stwuct v4w2_m2m_buffew);
	dst_vq->min_queued_buffews = 2;
	dst_vq->ops = &wotate_qops;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	dst_vq->wock = &ctx->dev->dev_mutex;
	dst_vq->dev = ctx->dev->dev;

	wet = vb2_queue_init(dst_vq);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int wotate_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct wotate_ctx *ctx = containew_of(ctww->handwew,
					      stwuct wotate_ctx,
					      ctww_handwew);
	stwuct v4w2_pix_fowmat fmt;

	switch (ctww->id) {
	case V4W2_CID_HFWIP:
		ctx->hfwip = ctww->vaw;
		bweak;
	case V4W2_CID_VFWIP:
		ctx->vfwip = ctww->vaw;
		bweak;
	case V4W2_CID_WOTATE:
		wotate_set_cap_fowmat(ctx, &fmt, ctww->vaw);

		/* Check if captuwe fowmat needs to be changed */
		if (fmt.width != ctx->dst_fmt.width ||
		    fmt.height != ctx->dst_fmt.height ||
		    fmt.bytespewwine != ctx->dst_fmt.bytespewwine ||
		    fmt.sizeimage != ctx->dst_fmt.sizeimage) {
			stwuct vb2_queue *vq;

			vq = v4w2_m2m_get_vq(ctx->fh.m2m_ctx,
					     V4W2_BUF_TYPE_VIDEO_CAPTUWE);
			if (vb2_is_busy(vq))
				wetuwn -EBUSY;

			wotate_set_cap_fowmat(ctx, &ctx->dst_fmt, ctww->vaw);
		}

		ctx->wotate = ctww->vaw;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct v4w2_ctww_ops wotate_ctww_ops = {
	.s_ctww = wotate_s_ctww,
};

static int wotate_setup_ctwws(stwuct wotate_ctx *ctx)
{
	v4w2_ctww_handwew_init(&ctx->ctww_handwew, 3);

	v4w2_ctww_new_std(&ctx->ctww_handwew, &wotate_ctww_ops,
			  V4W2_CID_HFWIP, 0, 1, 1, 0);

	v4w2_ctww_new_std(&ctx->ctww_handwew, &wotate_ctww_ops,
			  V4W2_CID_VFWIP, 0, 1, 1, 0);

	v4w2_ctww_new_std(&ctx->ctww_handwew, &wotate_ctww_ops,
			  V4W2_CID_WOTATE, 0, 270, 90, 0);

	if (ctx->ctww_handwew.ewwow) {
		int eww = ctx->ctww_handwew.ewwow;

		v4w2_eww(&ctx->dev->v4w2_dev, "contwow setup faiwed!\n");
		v4w2_ctww_handwew_fwee(&ctx->ctww_handwew);

		wetuwn eww;
	}

	wetuwn v4w2_ctww_handwew_setup(&ctx->ctww_handwew);
}

static int wotate_open(stwuct fiwe *fiwe)
{
	stwuct wotate_dev *dev = video_dwvdata(fiwe);
	stwuct wotate_ctx *ctx = NUWW;
	int wet;

	if (mutex_wock_intewwuptibwe(&dev->dev_mutex))
		wetuwn -EWESTAWTSYS;

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx) {
		mutex_unwock(&dev->dev_mutex);
		wetuwn -ENOMEM;
	}

	/* defauwt output fowmat */
	ctx->swc_fmt.pixewfowmat = V4W2_PIX_FMT_AWGB32;
	ctx->swc_fmt.fiewd = V4W2_FIEWD_NONE;
	ctx->swc_fmt.width = 640;
	ctx->swc_fmt.height = 480;
	wotate_pwepawe_fowmat(&ctx->swc_fmt);

	/* defauwt captuwe fowmat */
	wotate_set_cap_fowmat(ctx, &ctx->dst_fmt, ctx->wotate);

	v4w2_fh_init(&ctx->fh, video_devdata(fiwe));
	fiwe->pwivate_data = &ctx->fh;
	ctx->dev = dev;

	ctx->fh.m2m_ctx = v4w2_m2m_ctx_init(dev->m2m_dev, ctx,
					    &wotate_queue_init);
	if (IS_EWW(ctx->fh.m2m_ctx)) {
		wet = PTW_EWW(ctx->fh.m2m_ctx);
		goto eww_fwee;
	}

	v4w2_fh_add(&ctx->fh);

	wet = wotate_setup_ctwws(ctx);
	if (wet)
		goto eww_fwee;

	ctx->fh.ctww_handwew = &ctx->ctww_handwew;

	mutex_unwock(&dev->dev_mutex);

	wetuwn 0;

eww_fwee:
	kfwee(ctx);
	mutex_unwock(&dev->dev_mutex);

	wetuwn wet;
}

static int wotate_wewease(stwuct fiwe *fiwe)
{
	stwuct wotate_dev *dev = video_dwvdata(fiwe);
	stwuct wotate_ctx *ctx = containew_of(fiwe->pwivate_data,
						   stwuct wotate_ctx, fh);

	mutex_wock(&dev->dev_mutex);

	v4w2_ctww_handwew_fwee(&ctx->ctww_handwew);
	v4w2_fh_dew(&ctx->fh);
	v4w2_fh_exit(&ctx->fh);
	v4w2_m2m_ctx_wewease(ctx->fh.m2m_ctx);

	kfwee(ctx);

	mutex_unwock(&dev->dev_mutex);

	wetuwn 0;
}

static const stwuct v4w2_fiwe_opewations wotate_fops = {
	.ownew		= THIS_MODUWE,
	.open		= wotate_open,
	.wewease	= wotate_wewease,
	.poww		= v4w2_m2m_fop_poww,
	.unwocked_ioctw	= video_ioctw2,
	.mmap		= v4w2_m2m_fop_mmap,
};

static const stwuct video_device wotate_video_device = {
	.name		= WOTATE_NAME,
	.vfw_diw	= VFW_DIW_M2M,
	.fops		= &wotate_fops,
	.ioctw_ops	= &wotate_ioctw_ops,
	.minow		= -1,
	.wewease	= video_device_wewease_empty,
	.device_caps	= V4W2_CAP_VIDEO_M2M | V4W2_CAP_STWEAMING,
};

static const stwuct v4w2_m2m_ops wotate_m2m_ops = {
	.device_wun	= wotate_device_wun,
};

static int wotate_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wotate_dev *dev;
	stwuct video_device *vfd;
	int iwq, wet;

	dev = devm_kzawwoc(&pdev->dev, sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	dev->vfd = wotate_video_device;
	dev->dev = &pdev->dev;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq <= 0)
		wetuwn iwq;

	wet = devm_wequest_iwq(dev->dev, iwq, wotate_iwq,
			       0, dev_name(dev->dev), dev);
	if (wet) {
		dev_eww(dev->dev, "Faiwed to wequest IWQ\n");

		wetuwn wet;
	}

	dev->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(dev->base))
		wetuwn PTW_EWW(dev->base);

	dev->bus_cwk = devm_cwk_get(dev->dev, "bus");
	if (IS_EWW(dev->bus_cwk)) {
		dev_eww(dev->dev, "Faiwed to get bus cwock\n");

		wetuwn PTW_EWW(dev->bus_cwk);
	}

	dev->mod_cwk = devm_cwk_get(dev->dev, "mod");
	if (IS_EWW(dev->mod_cwk)) {
		dev_eww(dev->dev, "Faiwed to get mod cwock\n");

		wetuwn PTW_EWW(dev->mod_cwk);
	}

	dev->wstc = devm_weset_contwow_get(dev->dev, NUWW);
	if (IS_EWW(dev->wstc)) {
		dev_eww(dev->dev, "Faiwed to get weset contwow\n");

		wetuwn PTW_EWW(dev->wstc);
	}

	mutex_init(&dev->dev_mutex);

	wet = v4w2_device_wegistew(&pdev->dev, &dev->v4w2_dev);
	if (wet) {
		dev_eww(dev->dev, "Faiwed to wegistew V4W2 device\n");

		wetuwn wet;
	}

	vfd = &dev->vfd;
	vfd->wock = &dev->dev_mutex;
	vfd->v4w2_dev = &dev->v4w2_dev;

	snpwintf(vfd->name, sizeof(vfd->name), "%s",
		 wotate_video_device.name);
	video_set_dwvdata(vfd, dev);

	wet = video_wegistew_device(vfd, VFW_TYPE_VIDEO, 0);
	if (wet) {
		v4w2_eww(&dev->v4w2_dev, "Faiwed to wegistew video device\n");

		goto eww_v4w2;
	}

	v4w2_info(&dev->v4w2_dev,
		  "Device wegistewed as /dev/video%d\n", vfd->num);

	dev->m2m_dev = v4w2_m2m_init(&wotate_m2m_ops);
	if (IS_EWW(dev->m2m_dev)) {
		v4w2_eww(&dev->v4w2_dev,
			 "Faiwed to initiawize V4W2 M2M device\n");
		wet = PTW_EWW(dev->m2m_dev);

		goto eww_video;
	}

	pwatfowm_set_dwvdata(pdev, dev);

	pm_wuntime_enabwe(dev->dev);

	wetuwn 0;

eww_video:
	video_unwegistew_device(&dev->vfd);
eww_v4w2:
	v4w2_device_unwegistew(&dev->v4w2_dev);

	wetuwn wet;
}

static void wotate_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wotate_dev *dev = pwatfowm_get_dwvdata(pdev);

	v4w2_m2m_wewease(dev->m2m_dev);
	video_unwegistew_device(&dev->vfd);
	v4w2_device_unwegistew(&dev->v4w2_dev);

	pm_wuntime_fowce_suspend(&pdev->dev);
}

static int wotate_wuntime_wesume(stwuct device *device)
{
	stwuct wotate_dev *dev = dev_get_dwvdata(device);
	int wet;

	wet = cwk_pwepawe_enabwe(dev->bus_cwk);
	if (wet) {
		dev_eww(dev->dev, "Faiwed to enabwe bus cwock\n");

		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(dev->mod_cwk);
	if (wet) {
		dev_eww(dev->dev, "Faiwed to enabwe mod cwock\n");

		goto eww_bus_cwk;
	}

	wet = weset_contwow_deassewt(dev->wstc);
	if (wet) {
		dev_eww(dev->dev, "Faiwed to appwy weset\n");

		goto eww_mod_cwk;
	}

	wetuwn 0;

eww_mod_cwk:
	cwk_disabwe_unpwepawe(dev->mod_cwk);
eww_bus_cwk:
	cwk_disabwe_unpwepawe(dev->bus_cwk);

	wetuwn wet;
}

static int wotate_wuntime_suspend(stwuct device *device)
{
	stwuct wotate_dev *dev = dev_get_dwvdata(device);

	weset_contwow_assewt(dev->wstc);

	cwk_disabwe_unpwepawe(dev->mod_cwk);
	cwk_disabwe_unpwepawe(dev->bus_cwk);

	wetuwn 0;
}

static const stwuct of_device_id wotate_dt_match[] = {
	{ .compatibwe = "awwwinnew,sun8i-a83t-de2-wotate" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, wotate_dt_match);

static const stwuct dev_pm_ops wotate_pm_ops = {
	.wuntime_wesume		= wotate_wuntime_wesume,
	.wuntime_suspend	= wotate_wuntime_suspend,
};

static stwuct pwatfowm_dwivew wotate_dwivew = {
	.pwobe		= wotate_pwobe,
	.wemove_new	= wotate_wemove,
	.dwivew		= {
		.name		= WOTATE_NAME,
		.of_match_tabwe	= wotate_dt_match,
		.pm		= &wotate_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(wotate_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Jewnej Skwabec <jewnej.skwabec@siow.net>");
MODUWE_DESCWIPTION("Awwwinnew DE2 wotate dwivew");
