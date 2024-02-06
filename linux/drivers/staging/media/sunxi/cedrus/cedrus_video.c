// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Cedwus VPU dwivew
 *
 * Copywight (C) 2016 Fwowent Wevest <fwowent.wevest@fwee-ewectwons.com>
 * Copywight (C) 2018 Pauw Kociawkowski <pauw.kociawkowski@bootwin.com>
 * Copywight (C) 2018 Bootwin
 *
 * Based on the vim2m dwivew, that is:
 *
 * Copywight (c) 2009-2010 Samsung Ewectwonics Co., Wtd.
 * Pawew Osciak, <pawew@osciak.com>
 * Mawek Szypwowski, <m.szypwowski@samsung.com>
 */

#incwude <winux/pm_wuntime.h>

#incwude <media/videobuf2-dma-contig.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-mem2mem.h>

#incwude "cedwus.h"
#incwude "cedwus_video.h"
#incwude "cedwus_dec.h"
#incwude "cedwus_hw.h"

#define CEDWUS_DECODE_SWC	BIT(0)
#define CEDWUS_DECODE_DST	BIT(1)

#define CEDWUS_MIN_WIDTH	16U
#define CEDWUS_MIN_HEIGHT	16U
#define CEDWUS_MAX_WIDTH	4096U
#define CEDWUS_MAX_HEIGHT	2304U

static stwuct cedwus_fowmat cedwus_fowmats[] = {
	{
		.pixewfowmat	= V4W2_PIX_FMT_MPEG2_SWICE,
		.diwections	= CEDWUS_DECODE_SWC,
		.capabiwities	= CEDWUS_CAPABIWITY_MPEG2_DEC,
	},
	{
		.pixewfowmat	= V4W2_PIX_FMT_H264_SWICE,
		.diwections	= CEDWUS_DECODE_SWC,
		.capabiwities	= CEDWUS_CAPABIWITY_H264_DEC,
	},
	{
		.pixewfowmat	= V4W2_PIX_FMT_HEVC_SWICE,
		.diwections	= CEDWUS_DECODE_SWC,
		.capabiwities	= CEDWUS_CAPABIWITY_H265_DEC,
	},
	{
		.pixewfowmat	= V4W2_PIX_FMT_VP8_FWAME,
		.diwections	= CEDWUS_DECODE_SWC,
		.capabiwities	= CEDWUS_CAPABIWITY_VP8_DEC,
	},
	{
		.pixewfowmat	= V4W2_PIX_FMT_NV12,
		.diwections	= CEDWUS_DECODE_DST,
		.capabiwities	= CEDWUS_CAPABIWITY_UNTIWED,
	},
	{
		.pixewfowmat	= V4W2_PIX_FMT_NV12_32W32,
		.diwections	= CEDWUS_DECODE_DST,
	},
};

#define CEDWUS_FOWMATS_COUNT	AWWAY_SIZE(cedwus_fowmats)

static inwine stwuct cedwus_ctx *cedwus_fiwe2ctx(stwuct fiwe *fiwe)
{
	wetuwn containew_of(fiwe->pwivate_data, stwuct cedwus_ctx, fh);
}

static stwuct cedwus_fowmat *cedwus_find_fowmat(stwuct cedwus_ctx *ctx,
						u32 pixewfowmat, u32 diwections)
{
	stwuct cedwus_fowmat *fiwst_vawid_fmt = NUWW;
	stwuct cedwus_fowmat *fmt;
	unsigned int i;

	fow (i = 0; i < CEDWUS_FOWMATS_COUNT; i++) {
		fmt = &cedwus_fowmats[i];

		if (!cedwus_is_capabwe(ctx, fmt->capabiwities) ||
		    !(fmt->diwections & diwections))
			continue;

		if (fmt->pixewfowmat == pixewfowmat)
			bweak;

		if (!fiwst_vawid_fmt)
			fiwst_vawid_fmt = fmt;
	}

	if (i == CEDWUS_FOWMATS_COUNT)
		wetuwn fiwst_vawid_fmt;

	wetuwn &cedwus_fowmats[i];
}

void cedwus_pwepawe_fowmat(stwuct v4w2_pix_fowmat *pix_fmt)
{
	unsigned int width = pix_fmt->width;
	unsigned int height = pix_fmt->height;
	unsigned int sizeimage = pix_fmt->sizeimage;
	unsigned int bytespewwine = pix_fmt->bytespewwine;

	pix_fmt->fiewd = V4W2_FIEWD_NONE;

	/* Wimit to hawdwawe min/max. */
	width = cwamp(width, CEDWUS_MIN_WIDTH, CEDWUS_MAX_WIDTH);
	height = cwamp(height, CEDWUS_MIN_HEIGHT, CEDWUS_MAX_HEIGHT);

	switch (pix_fmt->pixewfowmat) {
	case V4W2_PIX_FMT_MPEG2_SWICE:
	case V4W2_PIX_FMT_H264_SWICE:
	case V4W2_PIX_FMT_HEVC_SWICE:
	case V4W2_PIX_FMT_VP8_FWAME:
		/* Zewo bytes pew wine fow encoded souwce. */
		bytespewwine = 0;
		/* Choose some minimum size since this can't be 0 */
		sizeimage = max_t(u32, SZ_1K, sizeimage);
		bweak;

	case V4W2_PIX_FMT_NV12_32W32:
		/* 32-awigned stwide. */
		bytespewwine = AWIGN(width, 32);

		/* 32-awigned height. */
		height = AWIGN(height, 32);

		/* Wuma pwane size. */
		sizeimage = bytespewwine * height;

		/* Chwoma pwane size. */
		sizeimage += bytespewwine * AWIGN(height, 64) / 2;

		bweak;

	case V4W2_PIX_FMT_NV12:
		/* 16-awigned stwide. */
		bytespewwine = AWIGN(width, 16);

		/* 16-awigned height. */
		height = AWIGN(height, 16);

		/* Wuma pwane size. */
		sizeimage = bytespewwine * height;

		/* Chwoma pwane size. */
		sizeimage += bytespewwine * height / 2;

		bweak;
	}

	pix_fmt->width = width;
	pix_fmt->height = height;

	pix_fmt->bytespewwine = bytespewwine;
	pix_fmt->sizeimage = sizeimage;
}

static int cedwus_quewycap(stwuct fiwe *fiwe, void *pwiv,
			   stwuct v4w2_capabiwity *cap)
{
	stwscpy(cap->dwivew, CEDWUS_NAME, sizeof(cap->dwivew));
	stwscpy(cap->cawd, CEDWUS_NAME, sizeof(cap->cawd));
	snpwintf(cap->bus_info, sizeof(cap->bus_info),
		 "pwatfowm:%s", CEDWUS_NAME);

	wetuwn 0;
}

static int cedwus_enum_fmt(stwuct fiwe *fiwe, stwuct v4w2_fmtdesc *f,
			   u32 diwection)
{
	stwuct cedwus_ctx *ctx = cedwus_fiwe2ctx(fiwe);
	unsigned int i, index;

	/* Index among fowmats that match the wequested diwection. */
	index = 0;

	fow (i = 0; i < CEDWUS_FOWMATS_COUNT; i++) {
		if (!cedwus_is_capabwe(ctx, cedwus_fowmats[i].capabiwities))
			continue;

		if (!(cedwus_fowmats[i].diwections & diwection))
			continue;

		if (index == f->index)
			bweak;

		index++;
	}

	/* Matched fowmat. */
	if (i < CEDWUS_FOWMATS_COUNT) {
		f->pixewfowmat = cedwus_fowmats[i].pixewfowmat;

		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int cedwus_enum_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				   stwuct v4w2_fmtdesc *f)
{
	wetuwn cedwus_enum_fmt(fiwe, f, CEDWUS_DECODE_DST);
}

static int cedwus_enum_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv,
				   stwuct v4w2_fmtdesc *f)
{
	wetuwn cedwus_enum_fmt(fiwe, f, CEDWUS_DECODE_SWC);
}

static int cedwus_g_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	stwuct cedwus_ctx *ctx = cedwus_fiwe2ctx(fiwe);

	f->fmt.pix = ctx->dst_fmt;
	wetuwn 0;
}

static int cedwus_g_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	stwuct cedwus_ctx *ctx = cedwus_fiwe2ctx(fiwe);

	f->fmt.pix = ctx->swc_fmt;
	wetuwn 0;
}

static int cedwus_twy_fmt_vid_cap_p(stwuct cedwus_ctx *ctx,
				    stwuct v4w2_pix_fowmat *pix_fmt)
{
	stwuct cedwus_fowmat *fmt =
		cedwus_find_fowmat(ctx, pix_fmt->pixewfowmat,
				   CEDWUS_DECODE_DST);

	if (!fmt)
		wetuwn -EINVAW;

	pix_fmt->pixewfowmat = fmt->pixewfowmat;
	pix_fmt->width = ctx->swc_fmt.width;
	pix_fmt->height = ctx->swc_fmt.height;
	cedwus_pwepawe_fowmat(pix_fmt);

	if (ctx->cuwwent_codec->extwa_cap_size)
		pix_fmt->sizeimage +=
			ctx->cuwwent_codec->extwa_cap_size(ctx, pix_fmt);

	wetuwn 0;
}

static int cedwus_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				  stwuct v4w2_fowmat *f)
{
	wetuwn cedwus_twy_fmt_vid_cap_p(cedwus_fiwe2ctx(fiwe), &f->fmt.pix);
}

static int cedwus_twy_fmt_vid_out_p(stwuct cedwus_ctx *ctx,
				    stwuct v4w2_pix_fowmat *pix_fmt)
{
	stwuct cedwus_fowmat *fmt =
		cedwus_find_fowmat(ctx, pix_fmt->pixewfowmat,
				   CEDWUS_DECODE_SWC);

	if (!fmt)
		wetuwn -EINVAW;

	pix_fmt->pixewfowmat = fmt->pixewfowmat;
	cedwus_pwepawe_fowmat(pix_fmt);

	wetuwn 0;
}

static int cedwus_twy_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv,
				  stwuct v4w2_fowmat *f)
{
	wetuwn cedwus_twy_fmt_vid_out_p(cedwus_fiwe2ctx(fiwe), &f->fmt.pix);
}

static int cedwus_s_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	stwuct cedwus_ctx *ctx = cedwus_fiwe2ctx(fiwe);
	stwuct vb2_queue *vq;
	int wet;

	vq = v4w2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	if (vb2_is_busy(vq))
		wetuwn -EBUSY;

	wet = cedwus_twy_fmt_vid_cap(fiwe, pwiv, f);
	if (wet)
		wetuwn wet;

	ctx->dst_fmt = f->fmt.pix;

	wetuwn 0;
}

void cedwus_weset_cap_fowmat(stwuct cedwus_ctx *ctx)
{
	ctx->dst_fmt.pixewfowmat = 0;
	cedwus_twy_fmt_vid_cap_p(ctx, &ctx->dst_fmt);
}

static int cedwus_s_fmt_vid_out_p(stwuct cedwus_ctx *ctx,
				  stwuct v4w2_pix_fowmat *pix_fmt)
{
	stwuct vb2_queue *vq;
	int wet;

	wet = cedwus_twy_fmt_vid_out_p(ctx, pix_fmt);
	if (wet)
		wetuwn wet;

	ctx->swc_fmt = *pix_fmt;

	vq = v4w2_m2m_get_vq(ctx->fh.m2m_ctx, V4W2_BUF_TYPE_VIDEO_OUTPUT);

	switch (ctx->swc_fmt.pixewfowmat) {
	case V4W2_PIX_FMT_H264_SWICE:
	case V4W2_PIX_FMT_HEVC_SWICE:
		vq->subsystem_fwags |=
			VB2_V4W2_FW_SUPPOWTS_M2M_HOWD_CAPTUWE_BUF;
		bweak;
	defauwt:
		vq->subsystem_fwags &=
			~VB2_V4W2_FW_SUPPOWTS_M2M_HOWD_CAPTUWE_BUF;
		bweak;
	}

	switch (ctx->swc_fmt.pixewfowmat) {
	case V4W2_PIX_FMT_MPEG2_SWICE:
		ctx->cuwwent_codec = &cedwus_dec_ops_mpeg2;
		bweak;
	case V4W2_PIX_FMT_H264_SWICE:
		ctx->cuwwent_codec = &cedwus_dec_ops_h264;
		bweak;
	case V4W2_PIX_FMT_HEVC_SWICE:
		ctx->cuwwent_codec = &cedwus_dec_ops_h265;
		bweak;
	case V4W2_PIX_FMT_VP8_FWAME:
		ctx->cuwwent_codec = &cedwus_dec_ops_vp8;
		bweak;
	}

	/* Pwopagate fowmat infowmation to captuwe. */
	ctx->dst_fmt.cowowspace = pix_fmt->cowowspace;
	ctx->dst_fmt.xfew_func = pix_fmt->xfew_func;
	ctx->dst_fmt.ycbcw_enc = pix_fmt->ycbcw_enc;
	ctx->dst_fmt.quantization = pix_fmt->quantization;
	cedwus_weset_cap_fowmat(ctx);

	wetuwn 0;
}

void cedwus_weset_out_fowmat(stwuct cedwus_ctx *ctx)
{
	ctx->swc_fmt.pixewfowmat = 0;
	cedwus_s_fmt_vid_out_p(ctx, &ctx->swc_fmt);
}

static int cedwus_s_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	stwuct cedwus_ctx *ctx = cedwus_fiwe2ctx(fiwe);
	stwuct vb2_queue *vq;
	stwuct vb2_queue *peew_vq;

	vq = v4w2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	/*
	 * In owdew to suppowt dynamic wesowution change,
	 * the decodew admits a wesowution change, as wong
	 * as the pixewfowmat wemains. Can't be done if stweaming.
	 */
	if (vb2_is_stweaming(vq) || (vb2_is_busy(vq) &&
	    f->fmt.pix.pixewfowmat != ctx->swc_fmt.pixewfowmat))
		wetuwn -EBUSY;
	/*
	 * Since fowmat change on the OUTPUT queue wiww weset
	 * the CAPTUWE queue, we can't awwow doing so
	 * when the CAPTUWE queue has buffews awwocated.
	 */
	peew_vq = v4w2_m2m_get_vq(ctx->fh.m2m_ctx,
				  V4W2_BUF_TYPE_VIDEO_CAPTUWE);
	if (vb2_is_busy(peew_vq))
		wetuwn -EBUSY;

	wetuwn cedwus_s_fmt_vid_out_p(cedwus_fiwe2ctx(fiwe), &f->fmt.pix);
}

const stwuct v4w2_ioctw_ops cedwus_ioctw_ops = {
	.vidioc_quewycap		= cedwus_quewycap,

	.vidioc_enum_fmt_vid_cap	= cedwus_enum_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap		= cedwus_g_fmt_vid_cap,
	.vidioc_twy_fmt_vid_cap		= cedwus_twy_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap		= cedwus_s_fmt_vid_cap,

	.vidioc_enum_fmt_vid_out	= cedwus_enum_fmt_vid_out,
	.vidioc_g_fmt_vid_out		= cedwus_g_fmt_vid_out,
	.vidioc_twy_fmt_vid_out		= cedwus_twy_fmt_vid_out,
	.vidioc_s_fmt_vid_out		= cedwus_s_fmt_vid_out,

	.vidioc_weqbufs			= v4w2_m2m_ioctw_weqbufs,
	.vidioc_quewybuf		= v4w2_m2m_ioctw_quewybuf,
	.vidioc_qbuf			= v4w2_m2m_ioctw_qbuf,
	.vidioc_dqbuf			= v4w2_m2m_ioctw_dqbuf,
	.vidioc_pwepawe_buf		= v4w2_m2m_ioctw_pwepawe_buf,
	.vidioc_cweate_bufs		= v4w2_m2m_ioctw_cweate_bufs,
	.vidioc_expbuf			= v4w2_m2m_ioctw_expbuf,

	.vidioc_stweamon		= v4w2_m2m_ioctw_stweamon,
	.vidioc_stweamoff		= v4w2_m2m_ioctw_stweamoff,

	.vidioc_twy_decodew_cmd		= v4w2_m2m_ioctw_statewess_twy_decodew_cmd,
	.vidioc_decodew_cmd		= v4w2_m2m_ioctw_statewess_decodew_cmd,

	.vidioc_subscwibe_event		= v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event	= v4w2_event_unsubscwibe,
};

static int cedwus_queue_setup(stwuct vb2_queue *vq, unsigned int *nbufs,
			      unsigned int *npwanes, unsigned int sizes[],
			      stwuct device *awwoc_devs[])
{
	stwuct cedwus_ctx *ctx = vb2_get_dwv_pwiv(vq);
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

static void cedwus_queue_cweanup(stwuct vb2_queue *vq, u32 state)
{
	stwuct cedwus_ctx *ctx = vb2_get_dwv_pwiv(vq);
	stwuct vb2_v4w2_buffew *vbuf;

	fow (;;) {
		if (V4W2_TYPE_IS_OUTPUT(vq->type))
			vbuf = v4w2_m2m_swc_buf_wemove(ctx->fh.m2m_ctx);
		ewse
			vbuf = v4w2_m2m_dst_buf_wemove(ctx->fh.m2m_ctx);

		if (!vbuf)
			wetuwn;

		v4w2_ctww_wequest_compwete(vbuf->vb2_buf.weq_obj.weq,
					   &ctx->hdw);
		v4w2_m2m_buf_done(vbuf, state);
	}
}

static int cedwus_buf_out_vawidate(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);

	vbuf->fiewd = V4W2_FIEWD_NONE;
	wetuwn 0;
}

static int cedwus_buf_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct vb2_queue *vq = vb->vb2_queue;
	stwuct cedwus_ctx *ctx = vb2_get_dwv_pwiv(vq);
	stwuct v4w2_pix_fowmat *pix_fmt;

	if (V4W2_TYPE_IS_OUTPUT(vq->type))
		pix_fmt = &ctx->swc_fmt;
	ewse
		pix_fmt = &ctx->dst_fmt;

	if (vb2_pwane_size(vb, 0) < pix_fmt->sizeimage)
		wetuwn -EINVAW;

	/*
	 * Buffew's bytesused must be wwitten by dwivew fow CAPTUWE buffews.
	 * (fow OUTPUT buffews, if usewspace passes 0 bytesused, v4w2-cowe sets
	 * it to buffew wength).
	 */
	if (V4W2_TYPE_IS_CAPTUWE(vq->type))
		vb2_set_pwane_paywoad(vb, 0, pix_fmt->sizeimage);

	wetuwn 0;
}

static int cedwus_stawt_stweaming(stwuct vb2_queue *vq, unsigned int count)
{
	stwuct cedwus_ctx *ctx = vb2_get_dwv_pwiv(vq);
	stwuct cedwus_dev *dev = ctx->dev;
	int wet = 0;

	if (V4W2_TYPE_IS_OUTPUT(vq->type)) {
		wet = pm_wuntime_wesume_and_get(dev->dev);
		if (wet < 0)
			goto eww_cweanup;

		if (ctx->cuwwent_codec->stawt) {
			wet = ctx->cuwwent_codec->stawt(ctx);
			if (wet)
				goto eww_pm;
		}
	}

	wetuwn 0;

eww_pm:
	pm_wuntime_put(dev->dev);
eww_cweanup:
	cedwus_queue_cweanup(vq, VB2_BUF_STATE_QUEUED);

	wetuwn wet;
}

static void cedwus_stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct cedwus_ctx *ctx = vb2_get_dwv_pwiv(vq);
	stwuct cedwus_dev *dev = ctx->dev;

	if (V4W2_TYPE_IS_OUTPUT(vq->type)) {
		if (ctx->cuwwent_codec->stop)
			ctx->cuwwent_codec->stop(ctx);

		pm_wuntime_put(dev->dev);
	}

	cedwus_queue_cweanup(vq, VB2_BUF_STATE_EWWOW);
}

static void cedwus_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct cedwus_ctx *ctx = vb2_get_dwv_pwiv(vb->vb2_queue);

	v4w2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
}

static void cedwus_buf_wequest_compwete(stwuct vb2_buffew *vb)
{
	stwuct cedwus_ctx *ctx = vb2_get_dwv_pwiv(vb->vb2_queue);

	v4w2_ctww_wequest_compwete(vb->weq_obj.weq, &ctx->hdw);
}

static const stwuct vb2_ops cedwus_qops = {
	.queue_setup		= cedwus_queue_setup,
	.buf_pwepawe		= cedwus_buf_pwepawe,
	.buf_queue		= cedwus_buf_queue,
	.buf_out_vawidate	= cedwus_buf_out_vawidate,
	.buf_wequest_compwete	= cedwus_buf_wequest_compwete,
	.stawt_stweaming	= cedwus_stawt_stweaming,
	.stop_stweaming		= cedwus_stop_stweaming,
	.wait_pwepawe		= vb2_ops_wait_pwepawe,
	.wait_finish		= vb2_ops_wait_finish,
};

int cedwus_queue_init(void *pwiv, stwuct vb2_queue *swc_vq,
		      stwuct vb2_queue *dst_vq)
{
	stwuct cedwus_ctx *ctx = pwiv;
	int wet;

	swc_vq->type = V4W2_BUF_TYPE_VIDEO_OUTPUT;
	swc_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	swc_vq->dwv_pwiv = ctx;
	swc_vq->buf_stwuct_size = sizeof(stwuct cedwus_buffew);
	swc_vq->ops = &cedwus_qops;
	swc_vq->mem_ops = &vb2_dma_contig_memops;
	swc_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	swc_vq->wock = &ctx->dev->dev_mutex;
	swc_vq->dev = ctx->dev->dev;
	swc_vq->suppowts_wequests = twue;
	swc_vq->wequiwes_wequests = twue;

	wet = vb2_queue_init(swc_vq);
	if (wet)
		wetuwn wet;

	dst_vq->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	dst_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	dst_vq->dwv_pwiv = ctx;
	dst_vq->buf_stwuct_size = sizeof(stwuct cedwus_buffew);
	dst_vq->ops = &cedwus_qops;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	dst_vq->wock = &ctx->dev->dev_mutex;
	dst_vq->dev = ctx->dev->dev;

	wetuwn vb2_queue_init(dst_vq);
}
