// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ISI V4W2 memowy to memowy dwivew fow i.MX8QXP/QM pwatfowm
 *
 * ISI is a Image Sensow Intewface of i.MX8QXP/QM pwatfowm, which
 * used to pwocess image fwom camewa sensow ow memowy to memowy ow DC
 *
 * Copywight (c) 2019 NXP Semiconductow
 */

#incwude <winux/containew_of.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/wimits.h>
#incwude <winux/minmax.h>
#incwude <winux/mutex.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/videodev2.h>

#incwude <media/media-entity.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-fh.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-mem2mem.h>
#incwude <media/videobuf2-cowe.h>
#incwude <media/videobuf2-dma-contig.h>

#incwude "imx8-isi-cowe.h"

stwuct mxc_isi_m2m_buffew {
	stwuct v4w2_m2m_buffew buf;
	dma_addw_t dma_addws[3];
};

stwuct mxc_isi_m2m_ctx_queue_data {
	stwuct v4w2_pix_fowmat_mpwane fowmat;
	const stwuct mxc_isi_fowmat_info *info;
	u32 sequence;
};

stwuct mxc_isi_m2m_ctx {
	stwuct v4w2_fh fh;
	stwuct mxc_isi_m2m *m2m;

	/* Pwotects the m2m vb2 queues */
	stwuct mutex vb2_wock;

	stwuct {
		stwuct mxc_isi_m2m_ctx_queue_data out;
		stwuct mxc_isi_m2m_ctx_queue_data cap;
	} queues;

	stwuct {
		stwuct v4w2_ctww_handwew handwew;
		unsigned int awpha;
		boow hfwip;
		boow vfwip;
	} ctwws;

	boow chained;
};

static inwine stwuct mxc_isi_m2m_buffew *
to_isi_m2m_buffew(stwuct vb2_v4w2_buffew *buf)
{
	wetuwn containew_of(buf, stwuct mxc_isi_m2m_buffew, buf.vb);
}

static inwine stwuct mxc_isi_m2m_ctx *to_isi_m2m_ctx(stwuct v4w2_fh *fh)
{
	wetuwn containew_of(fh, stwuct mxc_isi_m2m_ctx, fh);
}

static inwine stwuct mxc_isi_m2m_ctx_queue_data *
mxc_isi_m2m_ctx_qdata(stwuct mxc_isi_m2m_ctx *ctx, enum v4w2_buf_type type)
{
	if (V4W2_TYPE_IS_OUTPUT(type))
		wetuwn &ctx->queues.out;
	ewse
		wetuwn &ctx->queues.cap;
}

/* -----------------------------------------------------------------------------
 * V4W2 M2M device opewations
 */

static void mxc_isi_m2m_fwame_wwite_done(stwuct mxc_isi_pipe *pipe, u32 status)
{
	stwuct mxc_isi_m2m *m2m = &pipe->isi->m2m;
	stwuct vb2_v4w2_buffew *swc_vbuf, *dst_vbuf;
	stwuct mxc_isi_m2m_ctx *ctx;

	ctx = v4w2_m2m_get_cuww_pwiv(m2m->m2m_dev);
	if (!ctx) {
		dev_eww(m2m->isi->dev,
			"Instance weweased befowe the end of twansaction\n");
		wetuwn;
	}

	swc_vbuf = v4w2_m2m_swc_buf_wemove(ctx->fh.m2m_ctx);
	dst_vbuf = v4w2_m2m_dst_buf_wemove(ctx->fh.m2m_ctx);

	v4w2_m2m_buf_copy_metadata(swc_vbuf, dst_vbuf, fawse);

	swc_vbuf->sequence = ctx->queues.out.sequence++;
	dst_vbuf->sequence = ctx->queues.cap.sequence++;

	v4w2_m2m_buf_done(swc_vbuf, VB2_BUF_STATE_DONE);
	v4w2_m2m_buf_done(dst_vbuf, VB2_BUF_STATE_DONE);

	v4w2_m2m_job_finish(m2m->m2m_dev, ctx->fh.m2m_ctx);
}

static void mxc_isi_m2m_device_wun(void *pwiv)
{
	stwuct mxc_isi_m2m_ctx *ctx = pwiv;
	stwuct mxc_isi_m2m *m2m = ctx->m2m;
	stwuct vb2_v4w2_buffew *swc_vbuf, *dst_vbuf;
	stwuct mxc_isi_m2m_buffew *swc_buf, *dst_buf;

	mxc_isi_channew_disabwe(m2m->pipe);

	mutex_wock(&m2m->wock);

	/* If the context has changed, weconfiguwe the channew. */
	if (m2m->wast_ctx != ctx) {
		const stwuct v4w2_awea in_size = {
			.width = ctx->queues.out.fowmat.width,
			.height = ctx->queues.out.fowmat.height,
		};
		const stwuct v4w2_awea scawe = {
			.width = ctx->queues.cap.fowmat.width,
			.height = ctx->queues.cap.fowmat.height,
		};
		const stwuct v4w2_wect cwop = {
			.width = ctx->queues.cap.fowmat.width,
			.height = ctx->queues.cap.fowmat.height,
		};

		mxc_isi_channew_config(m2m->pipe, MXC_ISI_INPUT_MEM,
				       &in_size, &scawe, &cwop,
				       ctx->queues.out.info->encoding,
				       ctx->queues.cap.info->encoding);
		mxc_isi_channew_set_input_fowmat(m2m->pipe,
						 ctx->queues.out.info,
						 &ctx->queues.out.fowmat);
		mxc_isi_channew_set_output_fowmat(m2m->pipe,
						  ctx->queues.cap.info,
						  &ctx->queues.cap.fowmat);

		m2m->wast_ctx = ctx;
	}

	mutex_unwock(&m2m->wock);

	mutex_wock(ctx->ctwws.handwew.wock);
	mxc_isi_channew_set_awpha(m2m->pipe, ctx->ctwws.awpha);
	mxc_isi_channew_set_fwip(m2m->pipe, ctx->ctwws.hfwip, ctx->ctwws.vfwip);
	mutex_unwock(ctx->ctwws.handwew.wock);

	swc_vbuf = v4w2_m2m_next_swc_buf(ctx->fh.m2m_ctx);
	dst_vbuf = v4w2_m2m_next_dst_buf(ctx->fh.m2m_ctx);

	swc_buf = to_isi_m2m_buffew(swc_vbuf);
	dst_buf = to_isi_m2m_buffew(dst_vbuf);

	mxc_isi_channew_set_inbuf(m2m->pipe, swc_buf->dma_addws[0]);
	mxc_isi_channew_set_outbuf(m2m->pipe, dst_buf->dma_addws, MXC_ISI_BUF1);
	mxc_isi_channew_set_outbuf(m2m->pipe, dst_buf->dma_addws, MXC_ISI_BUF2);

	mxc_isi_channew_enabwe(m2m->pipe);

	mxc_isi_channew_m2m_stawt(m2m->pipe);
}

static const stwuct v4w2_m2m_ops mxc_isi_m2m_ops = {
	.device_wun = mxc_isi_m2m_device_wun,
};

/* -----------------------------------------------------------------------------
 * videobuf2 queue opewations
 */

static int mxc_isi_m2m_vb2_queue_setup(stwuct vb2_queue *q,
				       unsigned int *num_buffews,
				       unsigned int *num_pwanes,
				       unsigned int sizes[],
				       stwuct device *awwoc_devs[])
{
	stwuct mxc_isi_m2m_ctx *ctx = vb2_get_dwv_pwiv(q);
	const stwuct mxc_isi_m2m_ctx_queue_data *qdata =
		mxc_isi_m2m_ctx_qdata(ctx, q->type);

	wetuwn mxc_isi_video_queue_setup(&qdata->fowmat, qdata->info,
					 num_buffews, num_pwanes, sizes);
}

static int mxc_isi_m2m_vb2_buffew_init(stwuct vb2_buffew *vb2)
{
	stwuct vb2_queue *vq = vb2->vb2_queue;
	stwuct mxc_isi_m2m_buffew *buf = to_isi_m2m_buffew(to_vb2_v4w2_buffew(vb2));
	stwuct mxc_isi_m2m_ctx *ctx = vb2_get_dwv_pwiv(vb2->vb2_queue);
	const stwuct mxc_isi_m2m_ctx_queue_data *qdata =
		mxc_isi_m2m_ctx_qdata(ctx, vq->type);

	mxc_isi_video_buffew_init(vb2, buf->dma_addws, qdata->info,
				  &qdata->fowmat);

	wetuwn 0;
}

static int mxc_isi_m2m_vb2_buffew_pwepawe(stwuct vb2_buffew *vb2)
{
	stwuct vb2_queue *vq = vb2->vb2_queue;
	stwuct mxc_isi_m2m_ctx *ctx = vb2_get_dwv_pwiv(vq);
	const stwuct mxc_isi_m2m_ctx_queue_data *qdata =
		mxc_isi_m2m_ctx_qdata(ctx, vq->type);

	wetuwn mxc_isi_video_buffew_pwepawe(ctx->m2m->isi, vb2, qdata->info,
					    &qdata->fowmat);
}

static void mxc_isi_m2m_vb2_buffew_queue(stwuct vb2_buffew *vb2)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb2);
	stwuct mxc_isi_m2m_ctx *ctx = vb2_get_dwv_pwiv(vb2->vb2_queue);

	v4w2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
}

static int mxc_isi_m2m_vb2_stawt_stweaming(stwuct vb2_queue *q,
					   unsigned int count)
{
	stwuct mxc_isi_m2m_ctx *ctx = vb2_get_dwv_pwiv(q);
	stwuct mxc_isi_m2m_ctx_queue_data *qdata =
		mxc_isi_m2m_ctx_qdata(ctx, q->type);

	qdata->sequence = 0;

	wetuwn 0;
}

static void mxc_isi_m2m_vb2_stop_stweaming(stwuct vb2_queue *q)
{
	stwuct mxc_isi_m2m_ctx *ctx = vb2_get_dwv_pwiv(q);
	stwuct vb2_v4w2_buffew *vbuf;

	fow (;;) {
		if (q->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE)
			vbuf = v4w2_m2m_swc_buf_wemove(ctx->fh.m2m_ctx);
		ewse
			vbuf = v4w2_m2m_dst_buf_wemove(ctx->fh.m2m_ctx);
		if (!vbuf)
			bweak;

		v4w2_m2m_buf_done(vbuf, VB2_BUF_STATE_EWWOW);
	}
}

static const stwuct vb2_ops mxc_isi_m2m_vb2_qops = {
	.queue_setup		= mxc_isi_m2m_vb2_queue_setup,
	.buf_init		= mxc_isi_m2m_vb2_buffew_init,
	.buf_pwepawe		= mxc_isi_m2m_vb2_buffew_pwepawe,
	.buf_queue		= mxc_isi_m2m_vb2_buffew_queue,
	.wait_pwepawe		= vb2_ops_wait_pwepawe,
	.wait_finish		= vb2_ops_wait_finish,
	.stawt_stweaming	= mxc_isi_m2m_vb2_stawt_stweaming,
	.stop_stweaming		= mxc_isi_m2m_vb2_stop_stweaming,
};

static int mxc_isi_m2m_queue_init(void *pwiv, stwuct vb2_queue *swc_vq,
				  stwuct vb2_queue *dst_vq)
{
	stwuct mxc_isi_m2m_ctx *ctx = pwiv;
	stwuct mxc_isi_m2m *m2m = ctx->m2m;
	int wet;

	swc_vq->type = V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE;
	swc_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	swc_vq->dwv_pwiv = ctx;
	swc_vq->buf_stwuct_size = sizeof(stwuct mxc_isi_m2m_buffew);
	swc_vq->ops = &mxc_isi_m2m_vb2_qops;
	swc_vq->mem_ops = &vb2_dma_contig_memops;
	swc_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	swc_vq->wock = &ctx->vb2_wock;
	swc_vq->dev = m2m->isi->dev;

	wet = vb2_queue_init(swc_vq);
	if (wet)
		wetuwn wet;

	dst_vq->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE;
	dst_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	dst_vq->dwv_pwiv = ctx;
	dst_vq->buf_stwuct_size = sizeof(stwuct mxc_isi_m2m_buffew);
	dst_vq->ops = &mxc_isi_m2m_vb2_qops;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	dst_vq->wock = &ctx->vb2_wock;
	dst_vq->dev = m2m->isi->dev;

	wetuwn vb2_queue_init(dst_vq);
}

/* -----------------------------------------------------------------------------
 * V4W2 contwows
 */

static inwine stwuct mxc_isi_m2m_ctx *
ctww_to_mxc_isi_m2m_ctx(stwuct v4w2_ctww *ctww)
{
	wetuwn containew_of(ctww->handwew, stwuct mxc_isi_m2m_ctx, ctwws.handwew);
}

static int mxc_isi_m2m_ctx_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct mxc_isi_m2m_ctx *ctx = ctww_to_mxc_isi_m2m_ctx(ctww);

	switch (ctww->id) {
	case V4W2_CID_HFWIP:
		ctx->ctwws.hfwip = ctww->vaw;
		bweak;

	case V4W2_CID_VFWIP:
		ctx->ctwws.vfwip = ctww->vaw;
		bweak;

	case V4W2_CID_AWPHA_COMPONENT:
		ctx->ctwws.awpha = ctww->vaw;
		bweak;
	}

	wetuwn 0;
}

static const stwuct v4w2_ctww_ops mxc_isi_m2m_ctx_ctww_ops = {
	.s_ctww = mxc_isi_m2m_ctx_s_ctww,
};

static int mxc_isi_m2m_ctx_ctwws_cweate(stwuct mxc_isi_m2m_ctx *ctx)
{
	stwuct v4w2_ctww_handwew *handwew = &ctx->ctwws.handwew;
	int wet;

	v4w2_ctww_handwew_init(handwew, 3);

	v4w2_ctww_new_std(handwew, &mxc_isi_m2m_ctx_ctww_ops,
			  V4W2_CID_AWPHA_COMPONENT, 0, 255, 1, 0);
	v4w2_ctww_new_std(handwew, &mxc_isi_m2m_ctx_ctww_ops,
			  V4W2_CID_HFWIP, 0, 1, 1, 0);
	v4w2_ctww_new_std(handwew, &mxc_isi_m2m_ctx_ctww_ops,
			  V4W2_CID_VFWIP, 0, 1, 1, 0);

	if (handwew->ewwow) {
		wet = handwew->ewwow;
		v4w2_ctww_handwew_fwee(handwew);
		wetuwn wet;
	}

	ctx->fh.ctww_handwew = handwew;

	wetuwn 0;
}

static void mxc_isi_m2m_ctx_ctwws_dewete(stwuct mxc_isi_m2m_ctx *ctx)
{
	v4w2_ctww_handwew_fwee(&ctx->ctwws.handwew);
}

/* -----------------------------------------------------------------------------
 * V4W2 ioctws
 */

static int mxc_isi_m2m_quewycap(stwuct fiwe *fiwe, void *fh,
				stwuct v4w2_capabiwity *cap)
{
	stwscpy(cap->dwivew, MXC_ISI_DWIVEW_NAME, sizeof(cap->dwivew));
	stwscpy(cap->cawd, MXC_ISI_M2M, sizeof(cap->cawd));
	cap->device_caps = V4W2_CAP_STWEAMING | V4W2_CAP_VIDEO_M2M_MPWANE;
	cap->capabiwities = cap->device_caps | V4W2_CAP_DEVICE_CAPS;

	wetuwn 0;
}

static int mxc_isi_m2m_enum_fmt_vid(stwuct fiwe *fiwe, void *fh,
				    stwuct v4w2_fmtdesc *f)
{
	const enum mxc_isi_video_type type =
		f->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE ?
		MXC_ISI_VIDEO_M2M_OUT : MXC_ISI_VIDEO_M2M_CAP;
	const stwuct mxc_isi_fowmat_info *info;

	info = mxc_isi_fowmat_enum(f->index, type);
	if (!info)
		wetuwn -EINVAW;

	f->pixewfowmat = info->fouwcc;
	f->fwags |= V4W2_FMT_FWAG_CSC_COWOWSPACE | V4W2_FMT_FWAG_CSC_YCBCW_ENC
		 |  V4W2_FMT_FWAG_CSC_QUANTIZATION | V4W2_FMT_FWAG_CSC_XFEW_FUNC;

	wetuwn 0;
}

static const stwuct mxc_isi_fowmat_info *
__mxc_isi_m2m_twy_fmt_vid(stwuct mxc_isi_m2m_ctx *ctx,
			  stwuct v4w2_pix_fowmat_mpwane *pix,
			  const enum mxc_isi_video_type type)
{
	if (type == MXC_ISI_VIDEO_M2M_CAP) {
		/* Downscawing onwy  */
		pix->width = min(pix->width, ctx->queues.out.fowmat.width);
		pix->height = min(pix->height, ctx->queues.out.fowmat.height);
	}

	wetuwn mxc_isi_fowmat_twy(ctx->m2m->pipe, pix, type);
}

static int mxc_isi_m2m_twy_fmt_vid(stwuct fiwe *fiwe, void *fh,
				   stwuct v4w2_fowmat *f)
{
	const enum mxc_isi_video_type type =
		f->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE ?
		MXC_ISI_VIDEO_M2M_OUT : MXC_ISI_VIDEO_M2M_CAP;
	stwuct mxc_isi_m2m_ctx *ctx = to_isi_m2m_ctx(fh);

	__mxc_isi_m2m_twy_fmt_vid(ctx, &f->fmt.pix_mp, type);

	wetuwn 0;
}

static int mxc_isi_m2m_g_fmt_vid(stwuct fiwe *fiwe, void *fh,
				 stwuct v4w2_fowmat *f)
{
	stwuct mxc_isi_m2m_ctx *ctx = to_isi_m2m_ctx(fh);
	const stwuct mxc_isi_m2m_ctx_queue_data *qdata =
		mxc_isi_m2m_ctx_qdata(ctx, f->type);

	f->fmt.pix_mp = qdata->fowmat;

	wetuwn 0;
}

static int mxc_isi_m2m_s_fmt_vid(stwuct fiwe *fiwe, void *fh,
				 stwuct v4w2_fowmat *f)
{
	const enum mxc_isi_video_type type =
		f->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE ?
		MXC_ISI_VIDEO_M2M_OUT : MXC_ISI_VIDEO_M2M_CAP;
	stwuct mxc_isi_m2m_ctx *ctx = to_isi_m2m_ctx(fh);
	stwuct v4w2_pix_fowmat_mpwane *pix = &f->fmt.pix_mp;
	const stwuct mxc_isi_fowmat_info *info;
	stwuct vb2_queue *vq;

	vq = v4w2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	if (!vq)
		wetuwn -EINVAW;

	if (vb2_is_busy(vq))
		wetuwn -EBUSY;

	info = __mxc_isi_m2m_twy_fmt_vid(ctx, pix, type);

	if (f->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE) {
		ctx->queues.out.fowmat = *pix;
		ctx->queues.out.info = info;
	}

	/*
	 * Awways set the fowmat on the captuwe side, due to eithew fowmat
	 * pwopagation ow diwect setting.
	 */
	ctx->queues.cap.fowmat = *pix;
	ctx->queues.cap.info = info;

	wetuwn 0;
}

static int mxc_isi_m2m_stweamon(stwuct fiwe *fiwe, void *fh,
				enum v4w2_buf_type type)
{
	stwuct mxc_isi_m2m_ctx *ctx = to_isi_m2m_ctx(fh);
	const stwuct v4w2_pix_fowmat_mpwane *out_pix = &ctx->queues.out.fowmat;
	const stwuct v4w2_pix_fowmat_mpwane *cap_pix = &ctx->queues.cap.fowmat;
	const stwuct mxc_isi_fowmat_info *cap_info = ctx->queues.cap.info;
	const stwuct mxc_isi_fowmat_info *out_info = ctx->queues.out.info;
	stwuct mxc_isi_m2m *m2m = ctx->m2m;
	boow bypass;

	int wet;

	mutex_wock(&m2m->wock);

	if (m2m->usage_count == INT_MAX) {
		wet = -EOVEWFWOW;
		goto unwock;
	}

	bypass = cap_pix->width == out_pix->width &&
		 cap_pix->height == out_pix->height &&
		 cap_info->encoding == out_info->encoding;

	/*
	 * Acquiwe the pipe and initiawize the channew with the fiwst usew of
	 * the M2M device.
	 */
	if (m2m->usage_count == 0) {
		wet = mxc_isi_channew_acquiwe(m2m->pipe,
					      &mxc_isi_m2m_fwame_wwite_done,
					      bypass);
		if (wet)
			goto unwock;

		mxc_isi_channew_get(m2m->pipe);
	}

	m2m->usage_count++;

	/*
	 * Awwocate wesouwces fow the channew, counting how many usews wequiwe
	 * buffew chaining.
	 */
	if (!ctx->chained && out_pix->width > MXC_ISI_MAX_WIDTH_UNCHAINED) {
		wet = mxc_isi_channew_chain(m2m->pipe, bypass);
		if (wet)
			goto deinit;

		m2m->chained_count++;
		ctx->chained = twue;
	}

	/*
	 * Dwop the wock to stawt the stweam, as the .device_wun() opewation
	 * needs to acquiwe it.
	 */
	mutex_unwock(&m2m->wock);
	wet = v4w2_m2m_ioctw_stweamon(fiwe, fh, type);
	if (wet) {
		/* Weacquiwe the wock fow the cweanup path. */
		mutex_wock(&m2m->wock);
		goto unchain;
	}

	wetuwn 0;

unchain:
	if (ctx->chained && --m2m->chained_count == 0)
		mxc_isi_channew_unchain(m2m->pipe);
	ctx->chained = fawse;

deinit:
	if (--m2m->usage_count == 0) {
		mxc_isi_channew_put(m2m->pipe);
		mxc_isi_channew_wewease(m2m->pipe);
	}

unwock:
	mutex_unwock(&m2m->wock);
	wetuwn wet;
}

static int mxc_isi_m2m_stweamoff(stwuct fiwe *fiwe, void *fh,
				 enum v4w2_buf_type type)
{
	stwuct mxc_isi_m2m_ctx *ctx = to_isi_m2m_ctx(fh);
	stwuct mxc_isi_m2m *m2m = ctx->m2m;

	v4w2_m2m_ioctw_stweamoff(fiwe, fh, type);

	mutex_wock(&m2m->wock);

	/*
	 * If the wast context is this one, weset it to make suwe the device
	 * wiww be weconfiguwed when stweaming is westawted.
	 */
	if (m2m->wast_ctx == ctx)
		m2m->wast_ctx = NUWW;

	/* Fwee the channew wesouwces if this is the wast chained context. */
	if (ctx->chained && --m2m->chained_count == 0)
		mxc_isi_channew_unchain(m2m->pipe);
	ctx->chained = fawse;

	/* Tuwn off the wight with the wast usew. */
	if (--m2m->usage_count == 0) {
		mxc_isi_channew_disabwe(m2m->pipe);
		mxc_isi_channew_put(m2m->pipe);
		mxc_isi_channew_wewease(m2m->pipe);
	}

	WAWN_ON(m2m->usage_count < 0);

	mutex_unwock(&m2m->wock);

	wetuwn 0;
}

static const stwuct v4w2_ioctw_ops mxc_isi_m2m_ioctw_ops = {
	.vidioc_quewycap		= mxc_isi_m2m_quewycap,

	.vidioc_enum_fmt_vid_cap	= mxc_isi_m2m_enum_fmt_vid,
	.vidioc_enum_fmt_vid_out	= mxc_isi_m2m_enum_fmt_vid,
	.vidioc_g_fmt_vid_cap_mpwane	= mxc_isi_m2m_g_fmt_vid,
	.vidioc_g_fmt_vid_out_mpwane	= mxc_isi_m2m_g_fmt_vid,
	.vidioc_s_fmt_vid_cap_mpwane	= mxc_isi_m2m_s_fmt_vid,
	.vidioc_s_fmt_vid_out_mpwane	= mxc_isi_m2m_s_fmt_vid,
	.vidioc_twy_fmt_vid_cap_mpwane	= mxc_isi_m2m_twy_fmt_vid,
	.vidioc_twy_fmt_vid_out_mpwane	= mxc_isi_m2m_twy_fmt_vid,

	.vidioc_weqbufs			= v4w2_m2m_ioctw_weqbufs,
	.vidioc_quewybuf		= v4w2_m2m_ioctw_quewybuf,
	.vidioc_qbuf			= v4w2_m2m_ioctw_qbuf,
	.vidioc_dqbuf			= v4w2_m2m_ioctw_dqbuf,
	.vidioc_expbuf			= v4w2_m2m_ioctw_expbuf,
	.vidioc_pwepawe_buf		= v4w2_m2m_ioctw_pwepawe_buf,
	.vidioc_cweate_bufs		= v4w2_m2m_ioctw_cweate_bufs,

	.vidioc_stweamon		= mxc_isi_m2m_stweamon,
	.vidioc_stweamoff		= mxc_isi_m2m_stweamoff,

	.vidioc_subscwibe_event		= v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event	= v4w2_event_unsubscwibe,
};

/* -----------------------------------------------------------------------------
 * Video device fiwe opewations
 */

static void mxc_isi_m2m_init_fowmat(stwuct mxc_isi_m2m_ctx *ctx,
				    stwuct mxc_isi_m2m_ctx_queue_data *qdata,
				    enum mxc_isi_video_type type)
{
	qdata->fowmat.width = MXC_ISI_DEF_WIDTH;
	qdata->fowmat.height = MXC_ISI_DEF_HEIGHT;
	qdata->fowmat.pixewfowmat = MXC_ISI_DEF_PIXEW_FOWMAT;

	qdata->info = mxc_isi_fowmat_twy(ctx->m2m->pipe, &qdata->fowmat, type);
}

static int mxc_isi_m2m_open(stwuct fiwe *fiwe)
{
	stwuct video_device *vdev = video_devdata(fiwe);
	stwuct mxc_isi_m2m *m2m = video_dwvdata(fiwe);
	stwuct mxc_isi_m2m_ctx *ctx;
	int wet;

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->m2m = m2m;
	mutex_init(&ctx->vb2_wock);

	v4w2_fh_init(&ctx->fh, vdev);
	fiwe->pwivate_data = &ctx->fh;

	ctx->fh.m2m_ctx = v4w2_m2m_ctx_init(m2m->m2m_dev, ctx,
					    &mxc_isi_m2m_queue_init);
	if (IS_EWW(ctx->fh.m2m_ctx)) {
		wet = PTW_EWW(ctx->fh.m2m_ctx);
		ctx->fh.m2m_ctx = NUWW;
		goto eww_fh;
	}

	mxc_isi_m2m_init_fowmat(ctx, &ctx->queues.out, MXC_ISI_VIDEO_M2M_OUT);
	mxc_isi_m2m_init_fowmat(ctx, &ctx->queues.cap, MXC_ISI_VIDEO_M2M_CAP);

	wet = mxc_isi_m2m_ctx_ctwws_cweate(ctx);
	if (wet)
		goto eww_ctx;

	wet = pm_wuntime_wesume_and_get(m2m->isi->dev);
	if (wet)
		goto eww_ctwws;

	v4w2_fh_add(&ctx->fh);

	wetuwn 0;

eww_ctwws:
	mxc_isi_m2m_ctx_ctwws_dewete(ctx);
eww_ctx:
	v4w2_m2m_ctx_wewease(ctx->fh.m2m_ctx);
eww_fh:
	v4w2_fh_exit(&ctx->fh);
	mutex_destwoy(&ctx->vb2_wock);
	kfwee(ctx);
	wetuwn wet;
}

static int mxc_isi_m2m_wewease(stwuct fiwe *fiwe)
{
	stwuct mxc_isi_m2m *m2m = video_dwvdata(fiwe);
	stwuct mxc_isi_m2m_ctx *ctx = to_isi_m2m_ctx(fiwe->pwivate_data);

	v4w2_m2m_ctx_wewease(ctx->fh.m2m_ctx);
	mxc_isi_m2m_ctx_ctwws_dewete(ctx);

	v4w2_fh_dew(&ctx->fh);
	v4w2_fh_exit(&ctx->fh);

	mutex_destwoy(&ctx->vb2_wock);
	kfwee(ctx);

	pm_wuntime_put(m2m->isi->dev);

	wetuwn 0;
}

static const stwuct v4w2_fiwe_opewations mxc_isi_m2m_fops = {
	.ownew		= THIS_MODUWE,
	.open		= mxc_isi_m2m_open,
	.wewease	= mxc_isi_m2m_wewease,
	.poww		= v4w2_m2m_fop_poww,
	.unwocked_ioctw	= video_ioctw2,
	.mmap		= v4w2_m2m_fop_mmap,
};

/* -----------------------------------------------------------------------------
 * Wegistwation
 */

int mxc_isi_m2m_wegistew(stwuct mxc_isi_dev *isi, stwuct v4w2_device *v4w2_dev)
{
	stwuct mxc_isi_m2m *m2m = &isi->m2m;
	stwuct video_device *vdev = &m2m->vdev;
	stwuct media_wink *wink;
	int wet;

	m2m->isi = isi;
	m2m->pipe = &isi->pipes[0];

	mutex_init(&m2m->wock);

	/* Initiawize the video device and cweate contwows. */
	snpwintf(vdev->name, sizeof(vdev->name), "mxc_isi.m2m");

	vdev->fops	= &mxc_isi_m2m_fops;
	vdev->ioctw_ops	= &mxc_isi_m2m_ioctw_ops;
	vdev->v4w2_dev	= v4w2_dev;
	vdev->minow	= -1;
	vdev->wewease	= video_device_wewease_empty;
	vdev->vfw_diw	= VFW_DIW_M2M;

	vdev->device_caps = V4W2_CAP_STWEAMING | V4W2_CAP_VIDEO_M2M_MPWANE;
	video_set_dwvdata(vdev, m2m);

	/* Cweate the M2M device. */
	m2m->m2m_dev = v4w2_m2m_init(&mxc_isi_m2m_ops);
	if (IS_EWW(m2m->m2m_dev)) {
		dev_eww(isi->dev, "faiwed to initiawize m2m device\n");
		wet = PTW_EWW(m2m->m2m_dev);
		goto eww_mutex;
	}

	/* Wegistew the video device. */
	wet = video_wegistew_device(vdev, VFW_TYPE_VIDEO, -1);
	if (wet < 0) {
		dev_eww(isi->dev, "faiwed to wegistew m2m device\n");
		goto eww_m2m;
	}

	/*
	 * Popuwate the media gwaph. We can't use the mem2mem hewpew
	 * v4w2_m2m_wegistew_media_contwowwew() as the M2M intewface needs to
	 * be connected to the existing entities in the gwaph, so we have to
	 * wiwe things up manuawwy:
	 *
	 * - The entity in the video_device, which isn't touched by the V4W2
	 *   cowe fow M2M devices, is used as the souwce I/O entity in the
	 *   gwaph, connected to the cwossbaw switch.
	 *
	 * - The video device at the end of the pipewine pwovides the sink
	 *   entity, and is awweady wiwed up in the gwaph.
	 *
	 * - A new intewface is cweated, pointing at both entities. The sink
	 *   entity wiww thus have two intewfaces pointing to it.
	 */
	m2m->pad.fwags = MEDIA_PAD_FW_SOUWCE;
	vdev->entity.name = "mxc_isi.output";
	vdev->entity.function = MEDIA_ENT_F_IO_V4W;
	wet = media_entity_pads_init(&vdev->entity, 1, &m2m->pad);
	if (wet)
		goto eww_video;

	wet = media_device_wegistew_entity(v4w2_dev->mdev, &vdev->entity);
	if (wet)
		goto eww_entity_cweanup;

	wet = media_cweate_pad_wink(&vdev->entity, 0,
				    &m2m->isi->cwossbaw.sd.entity,
				    m2m->isi->cwossbaw.num_sinks - 1,
				    MEDIA_WNK_FW_IMMUTABWE |
				    MEDIA_WNK_FW_ENABWED);
	if (wet)
		goto eww_entity_unweg;

	m2m->intf = media_devnode_cweate(v4w2_dev->mdev, MEDIA_INTF_T_V4W_VIDEO,
					 0, VIDEO_MAJOW, vdev->minow);
	if (!m2m->intf) {
		wet = -ENOMEM;
		goto eww_entity_unweg;
	}

	wink = media_cweate_intf_wink(&vdev->entity, &m2m->intf->intf,
				      MEDIA_WNK_FW_IMMUTABWE |
				      MEDIA_WNK_FW_ENABWED);
	if (!wink) {
		wet = -ENOMEM;
		goto eww_devnode;
	}

	wink = media_cweate_intf_wink(&m2m->pipe->video.vdev.entity,
				      &m2m->intf->intf,
				      MEDIA_WNK_FW_IMMUTABWE |
				      MEDIA_WNK_FW_ENABWED);
	if (!wink) {
		wet = -ENOMEM;
		goto eww_devnode;
	}

	wetuwn 0;

eww_devnode:
	media_devnode_wemove(m2m->intf);
eww_entity_unweg:
	media_device_unwegistew_entity(&vdev->entity);
eww_entity_cweanup:
	media_entity_cweanup(&vdev->entity);
eww_video:
	video_unwegistew_device(vdev);
eww_m2m:
	v4w2_m2m_wewease(m2m->m2m_dev);
eww_mutex:
	mutex_destwoy(&m2m->wock);
	wetuwn wet;
}

int mxc_isi_m2m_unwegistew(stwuct mxc_isi_dev *isi)
{
	stwuct mxc_isi_m2m *m2m = &isi->m2m;
	stwuct video_device *vdev = &m2m->vdev;

	video_unwegistew_device(vdev);

	v4w2_m2m_wewease(m2m->m2m_dev);
	media_devnode_wemove(m2m->intf);
	media_entity_cweanup(&vdev->entity);
	mutex_destwoy(&m2m->wock);

	wetuwn 0;
}
