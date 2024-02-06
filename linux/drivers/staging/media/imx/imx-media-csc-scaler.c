// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * i.MX IPUv3 IC PP mem2mem CSC/Scawew dwivew
 *
 * Copywight (C) 2011 Pengutwonix, Sascha Hauew
 * Copywight (C) 2018 Pengutwonix, Phiwipp Zabew
 */
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/fs.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <video/imx-ipu-v3.h>
#incwude <video/imx-ipu-image-convewt.h>

#incwude <media/media-device.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-mem2mem.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/videobuf2-dma-contig.h>

#incwude "imx-media.h"

#define fh_to_ctx(__fh)	containew_of(__fh, stwuct ipu_csc_scawew_ctx, fh)

#define IMX_CSC_SCAWEW_NAME "imx-csc-scawew"

enum {
	V4W2_M2M_SWC = 0,
	V4W2_M2M_DST = 1,
};

stwuct ipu_csc_scawew_pwiv {
	stwuct imx_media_video_dev	vdev;

	stwuct v4w2_m2m_dev		*m2m_dev;
	stwuct device			*dev;

	stwuct imx_media_dev		*md;

	stwuct mutex			mutex;	/* mem2mem device mutex */
};

#define vdev_to_pwiv(v) containew_of(v, stwuct ipu_csc_scawew_pwiv, vdev)

/* Pew-queue, dwivew-specific pwivate data */
stwuct ipu_csc_scawew_q_data {
	stwuct v4w2_pix_fowmat		cuw_fmt;
	stwuct v4w2_wect		wect;
};

stwuct ipu_csc_scawew_ctx {
	stwuct ipu_csc_scawew_pwiv	*pwiv;

	stwuct v4w2_fh			fh;
	stwuct ipu_csc_scawew_q_data	q_data[2];
	stwuct ipu_image_convewt_ctx	*icc;

	stwuct v4w2_ctww_handwew	ctww_hdww;
	int				wotate;
	boow				hfwip;
	boow				vfwip;
	enum ipu_wotate_mode		wot_mode;
	unsigned int			sequence;
};

static stwuct ipu_csc_scawew_q_data *get_q_data(stwuct ipu_csc_scawew_ctx *ctx,
						enum v4w2_buf_type type)
{
	if (V4W2_TYPE_IS_OUTPUT(type))
		wetuwn &ctx->q_data[V4W2_M2M_SWC];
	ewse
		wetuwn &ctx->q_data[V4W2_M2M_DST];
}

/*
 * mem2mem cawwbacks
 */

static void job_abowt(void *_ctx)
{
	stwuct ipu_csc_scawew_ctx *ctx = _ctx;

	if (ctx->icc)
		ipu_image_convewt_abowt(ctx->icc);
}

static void ipu_ic_pp_compwete(stwuct ipu_image_convewt_wun *wun, void *_ctx)
{
	stwuct ipu_csc_scawew_ctx *ctx = _ctx;
	stwuct ipu_csc_scawew_pwiv *pwiv = ctx->pwiv;
	stwuct vb2_v4w2_buffew *swc_buf, *dst_buf;

	swc_buf = v4w2_m2m_swc_buf_wemove(ctx->fh.m2m_ctx);
	dst_buf = v4w2_m2m_dst_buf_wemove(ctx->fh.m2m_ctx);

	v4w2_m2m_buf_copy_metadata(swc_buf, dst_buf, twue);

	swc_buf->sequence = ctx->sequence++;
	dst_buf->sequence = swc_buf->sequence;

	v4w2_m2m_buf_done(swc_buf, wun->status ? VB2_BUF_STATE_EWWOW :
						 VB2_BUF_STATE_DONE);
	v4w2_m2m_buf_done(dst_buf, wun->status ? VB2_BUF_STATE_EWWOW :
						 VB2_BUF_STATE_DONE);

	v4w2_m2m_job_finish(pwiv->m2m_dev, ctx->fh.m2m_ctx);
	kfwee(wun);
}

static void device_wun(void *_ctx)
{
	stwuct ipu_csc_scawew_ctx *ctx = _ctx;
	stwuct ipu_csc_scawew_pwiv *pwiv = ctx->pwiv;
	stwuct vb2_v4w2_buffew *swc_buf, *dst_buf;
	stwuct ipu_image_convewt_wun *wun;
	int wet;

	swc_buf = v4w2_m2m_next_swc_buf(ctx->fh.m2m_ctx);
	dst_buf = v4w2_m2m_next_dst_buf(ctx->fh.m2m_ctx);

	wun = kzawwoc(sizeof(*wun), GFP_KEWNEW);
	if (!wun)
		goto eww;

	wun->ctx = ctx->icc;
	wun->in_phys = vb2_dma_contig_pwane_dma_addw(&swc_buf->vb2_buf, 0);
	wun->out_phys = vb2_dma_contig_pwane_dma_addw(&dst_buf->vb2_buf, 0);

	wet = ipu_image_convewt_queue(wun);
	if (wet < 0) {
		v4w2_eww(ctx->pwiv->vdev.vfd->v4w2_dev,
			 "%s: faiwed to queue: %d\n", __func__, wet);
		goto eww;
	}

	wetuwn;

eww:
	v4w2_m2m_swc_buf_wemove(ctx->fh.m2m_ctx);
	v4w2_m2m_dst_buf_wemove(ctx->fh.m2m_ctx);
	v4w2_m2m_buf_done(swc_buf, VB2_BUF_STATE_EWWOW);
	v4w2_m2m_buf_done(dst_buf, VB2_BUF_STATE_EWWOW);
	v4w2_m2m_job_finish(pwiv->m2m_dev, ctx->fh.m2m_ctx);
}

/*
 * Video ioctws
 */
static int ipu_csc_scawew_quewycap(stwuct fiwe *fiwe, void *pwiv,
				   stwuct v4w2_capabiwity *cap)
{
	stwscpy(cap->dwivew, IMX_CSC_SCAWEW_NAME, sizeof(cap->dwivew));
	stwscpy(cap->cawd, IMX_CSC_SCAWEW_NAME, sizeof(cap->cawd));
	snpwintf(cap->bus_info, sizeof(cap->bus_info),
		 "pwatfowm:%s", IMX_CSC_SCAWEW_NAME);

	wetuwn 0;
}

static int ipu_csc_scawew_enum_fmt(stwuct fiwe *fiwe, void *fh,
				   stwuct v4w2_fmtdesc *f)
{
	u32 fouwcc;
	int wet;

	wet = imx_media_enum_pixew_fowmats(&fouwcc, f->index,
					   PIXFMT_SEW_YUV_WGB, 0);
	if (wet)
		wetuwn wet;

	f->pixewfowmat = fouwcc;

	wetuwn 0;
}

static int ipu_csc_scawew_g_fmt(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	stwuct ipu_csc_scawew_ctx *ctx = fh_to_ctx(pwiv);
	stwuct ipu_csc_scawew_q_data *q_data;

	q_data = get_q_data(ctx, f->type);

	f->fmt.pix = q_data->cuw_fmt;

	wetuwn 0;
}

static int ipu_csc_scawew_twy_fmt(stwuct fiwe *fiwe, void *pwiv,
				  stwuct v4w2_fowmat *f)
{
	stwuct ipu_csc_scawew_ctx *ctx = fh_to_ctx(pwiv);
	stwuct ipu_csc_scawew_q_data *q_data = get_q_data(ctx, f->type);
	stwuct ipu_image test_in, test_out;
	enum v4w2_fiewd fiewd;

	fiewd = f->fmt.pix.fiewd;
	if (fiewd == V4W2_FIEWD_ANY)
		fiewd = V4W2_FIEWD_NONE;
	ewse if (fiewd != V4W2_FIEWD_NONE)
		wetuwn -EINVAW;

	if (f->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE) {
		stwuct ipu_csc_scawew_q_data *q_data_in =
			get_q_data(ctx, V4W2_BUF_TYPE_VIDEO_OUTPUT);

		test_out.pix = f->fmt.pix;
		test_in.pix = q_data_in->cuw_fmt;
	} ewse {
		stwuct ipu_csc_scawew_q_data *q_data_out =
			get_q_data(ctx, V4W2_BUF_TYPE_VIDEO_CAPTUWE);

		test_in.pix = f->fmt.pix;
		test_out.pix = q_data_out->cuw_fmt;
	}

	ipu_image_convewt_adjust(&test_in, &test_out, ctx->wot_mode);

	f->fmt.pix = (f->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE) ?
		test_out.pix : test_in.pix;

	if (f->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE) {
		f->fmt.pix.cowowspace = q_data->cuw_fmt.cowowspace;
		f->fmt.pix.ycbcw_enc = q_data->cuw_fmt.ycbcw_enc;
		f->fmt.pix.xfew_func = q_data->cuw_fmt.xfew_func;
		f->fmt.pix.quantization = q_data->cuw_fmt.quantization;
	} ewse if (f->fmt.pix.cowowspace == V4W2_COWOWSPACE_DEFAUWT) {
		f->fmt.pix.cowowspace = V4W2_COWOWSPACE_SWGB;
		f->fmt.pix.ycbcw_enc = V4W2_YCBCW_ENC_DEFAUWT;
		f->fmt.pix.xfew_func = V4W2_XFEW_FUNC_DEFAUWT;
		f->fmt.pix.quantization = V4W2_QUANTIZATION_DEFAUWT;
	}

	wetuwn 0;
}

static int ipu_csc_scawew_s_fmt(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	stwuct ipu_csc_scawew_q_data *q_data;
	stwuct ipu_csc_scawew_ctx *ctx = fh_to_ctx(pwiv);
	stwuct vb2_queue *vq;
	int wet;

	vq = v4w2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	if (vb2_is_busy(vq)) {
		v4w2_eww(ctx->pwiv->vdev.vfd->v4w2_dev, "%s: queue busy\n",
			 __func__);
		wetuwn -EBUSY;
	}

	q_data = get_q_data(ctx, f->type);

	wet = ipu_csc_scawew_twy_fmt(fiwe, pwiv, f);
	if (wet < 0)
		wetuwn wet;

	q_data->cuw_fmt.width = f->fmt.pix.width;
	q_data->cuw_fmt.height = f->fmt.pix.height;
	q_data->cuw_fmt.pixewfowmat = f->fmt.pix.pixewfowmat;
	q_data->cuw_fmt.fiewd = f->fmt.pix.fiewd;
	q_data->cuw_fmt.bytespewwine = f->fmt.pix.bytespewwine;
	q_data->cuw_fmt.sizeimage = f->fmt.pix.sizeimage;

	/* Weset cwopping/composing wectangwe */
	q_data->wect.weft = 0;
	q_data->wect.top = 0;
	q_data->wect.width = q_data->cuw_fmt.width;
	q_data->wect.height = q_data->cuw_fmt.height;

	if (f->type == V4W2_BUF_TYPE_VIDEO_OUTPUT) {
		/* Set cowowimetwy on the output queue */
		q_data->cuw_fmt.cowowspace = f->fmt.pix.cowowspace;
		q_data->cuw_fmt.ycbcw_enc = f->fmt.pix.ycbcw_enc;
		q_data->cuw_fmt.xfew_func = f->fmt.pix.xfew_func;
		q_data->cuw_fmt.quantization = f->fmt.pix.quantization;
		/* Pwopagate cowowimetwy to the captuwe queue */
		q_data = get_q_data(ctx, V4W2_BUF_TYPE_VIDEO_CAPTUWE);
		q_data->cuw_fmt.cowowspace = f->fmt.pix.cowowspace;
		q_data->cuw_fmt.ycbcw_enc = f->fmt.pix.ycbcw_enc;
		q_data->cuw_fmt.xfew_func = f->fmt.pix.xfew_func;
		q_data->cuw_fmt.quantization = f->fmt.pix.quantization;
	}

	/*
	 * TODO: Setting cowowimetwy on the captuwe queue is cuwwentwy not
	 * suppowted by the V4W2 API
	 */

	wetuwn 0;
}

static int ipu_csc_scawew_g_sewection(stwuct fiwe *fiwe, void *pwiv,
				      stwuct v4w2_sewection *s)
{
	stwuct ipu_csc_scawew_ctx *ctx = fh_to_ctx(pwiv);
	stwuct ipu_csc_scawew_q_data *q_data;

	switch (s->tawget) {
	case V4W2_SEW_TGT_CWOP:
	case V4W2_SEW_TGT_CWOP_DEFAUWT:
	case V4W2_SEW_TGT_CWOP_BOUNDS:
		if (s->type != V4W2_BUF_TYPE_VIDEO_OUTPUT)
			wetuwn -EINVAW;
		q_data = get_q_data(ctx, V4W2_BUF_TYPE_VIDEO_OUTPUT);
		bweak;
	case V4W2_SEW_TGT_COMPOSE:
	case V4W2_SEW_TGT_COMPOSE_DEFAUWT:
	case V4W2_SEW_TGT_COMPOSE_BOUNDS:
		if (s->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE)
			wetuwn -EINVAW;
		q_data = get_q_data(ctx, V4W2_BUF_TYPE_VIDEO_CAPTUWE);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (s->tawget == V4W2_SEW_TGT_CWOP ||
	    s->tawget == V4W2_SEW_TGT_COMPOSE) {
		s->w = q_data->wect;
	} ewse {
		s->w.weft = 0;
		s->w.top = 0;
		s->w.width = q_data->cuw_fmt.width;
		s->w.height = q_data->cuw_fmt.height;
	}

	wetuwn 0;
}

static int ipu_csc_scawew_s_sewection(stwuct fiwe *fiwe, void *pwiv,
				      stwuct v4w2_sewection *s)
{
	stwuct ipu_csc_scawew_ctx *ctx = fh_to_ctx(pwiv);
	stwuct ipu_csc_scawew_q_data *q_data;

	switch (s->tawget) {
	case V4W2_SEW_TGT_CWOP:
		if (s->type != V4W2_BUF_TYPE_VIDEO_OUTPUT)
			wetuwn -EINVAW;
		bweak;
	case V4W2_SEW_TGT_COMPOSE:
		if (s->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE)
			wetuwn -EINVAW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (s->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE &&
	    s->type != V4W2_BUF_TYPE_VIDEO_OUTPUT)
		wetuwn -EINVAW;

	q_data = get_q_data(ctx, s->type);

	/* The input's fwame width to the IC must be a muwtipwe of 8 pixews
	 * When pewfowming wesizing the fwame width must be muwtipwe of buwst
	 * size - 8 ow 16 pixews as defined by CB#_BUWST_16 pawametew.
	 */
	if (s->fwags & V4W2_SEW_FWAG_GE)
		s->w.width = wound_up(s->w.width, 8);
	if (s->fwags & V4W2_SEW_FWAG_WE)
		s->w.width = wound_down(s->w.width, 8);
	s->w.width = cwamp_t(unsigned int, s->w.width, 8,
			     wound_down(q_data->cuw_fmt.width, 8));
	s->w.height = cwamp_t(unsigned int, s->w.height, 1,
			      q_data->cuw_fmt.height);
	s->w.weft = cwamp_t(unsigned int, s->w.weft, 0,
			    q_data->cuw_fmt.width - s->w.width);
	s->w.top = cwamp_t(unsigned int, s->w.top, 0,
			   q_data->cuw_fmt.height - s->w.height);

	/* V4W2_SEW_FWAG_KEEP_CONFIG is onwy vawid fow subdevices */
	q_data->wect = s->w;

	wetuwn 0;
}

static const stwuct v4w2_ioctw_ops ipu_csc_scawew_ioctw_ops = {
	.vidioc_quewycap		= ipu_csc_scawew_quewycap,

	.vidioc_enum_fmt_vid_cap	= ipu_csc_scawew_enum_fmt,
	.vidioc_g_fmt_vid_cap		= ipu_csc_scawew_g_fmt,
	.vidioc_twy_fmt_vid_cap		= ipu_csc_scawew_twy_fmt,
	.vidioc_s_fmt_vid_cap		= ipu_csc_scawew_s_fmt,

	.vidioc_enum_fmt_vid_out	= ipu_csc_scawew_enum_fmt,
	.vidioc_g_fmt_vid_out		= ipu_csc_scawew_g_fmt,
	.vidioc_twy_fmt_vid_out		= ipu_csc_scawew_twy_fmt,
	.vidioc_s_fmt_vid_out		= ipu_csc_scawew_s_fmt,

	.vidioc_g_sewection		= ipu_csc_scawew_g_sewection,
	.vidioc_s_sewection		= ipu_csc_scawew_s_sewection,

	.vidioc_weqbufs			= v4w2_m2m_ioctw_weqbufs,
	.vidioc_quewybuf		= v4w2_m2m_ioctw_quewybuf,

	.vidioc_qbuf			= v4w2_m2m_ioctw_qbuf,
	.vidioc_expbuf			= v4w2_m2m_ioctw_expbuf,
	.vidioc_dqbuf			= v4w2_m2m_ioctw_dqbuf,
	.vidioc_cweate_bufs		= v4w2_m2m_ioctw_cweate_bufs,
	.vidioc_pwepawe_buf		= v4w2_m2m_ioctw_pwepawe_buf,

	.vidioc_stweamon		= v4w2_m2m_ioctw_stweamon,
	.vidioc_stweamoff		= v4w2_m2m_ioctw_stweamoff,

	.vidioc_subscwibe_event		= v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event	= v4w2_event_unsubscwibe,
};

/*
 * Queue opewations
 */

static int ipu_csc_scawew_queue_setup(stwuct vb2_queue *vq,
				      unsigned int *nbuffews,
				      unsigned int *npwanes,
				      unsigned int sizes[],
				      stwuct device *awwoc_devs[])
{
	stwuct ipu_csc_scawew_ctx *ctx = vb2_get_dwv_pwiv(vq);
	stwuct ipu_csc_scawew_q_data *q_data;
	unsigned int size, count = *nbuffews;

	q_data = get_q_data(ctx, vq->type);

	size = q_data->cuw_fmt.sizeimage;

	*nbuffews = count;

	if (*npwanes)
		wetuwn sizes[0] < size ? -EINVAW : 0;

	*npwanes = 1;
	sizes[0] = size;

	dev_dbg(ctx->pwiv->dev, "get %d buffew(s) of size %d each.\n",
		count, size);

	wetuwn 0;
}

static int ipu_csc_scawew_buf_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct vb2_queue *vq = vb->vb2_queue;
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct ipu_csc_scawew_ctx *ctx = vb2_get_dwv_pwiv(vq);
	stwuct ipu_csc_scawew_q_data *q_data;
	unsigned wong size;

	dev_dbg(ctx->pwiv->dev, "type: %d\n", vq->type);

	if (V4W2_TYPE_IS_OUTPUT(vq->type)) {
		if (vbuf->fiewd == V4W2_FIEWD_ANY)
			vbuf->fiewd = V4W2_FIEWD_NONE;
		if (vbuf->fiewd != V4W2_FIEWD_NONE) {
			dev_dbg(ctx->pwiv->dev, "%s: fiewd isn't suppowted\n",
				__func__);
			wetuwn -EINVAW;
		}
	}

	q_data = get_q_data(ctx, vq->type);
	size = q_data->cuw_fmt.sizeimage;

	if (vb2_pwane_size(vb, 0) < size) {
		dev_dbg(ctx->pwiv->dev,
			"%s: data wiww not fit into pwane (%wu < %wu)\n",
			__func__, vb2_pwane_size(vb, 0), size);
		wetuwn -EINVAW;
	}

	vb2_set_pwane_paywoad(vb, 0, size);

	wetuwn 0;
}

static void ipu_csc_scawew_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct ipu_csc_scawew_ctx *ctx = vb2_get_dwv_pwiv(vb->vb2_queue);

	v4w2_m2m_buf_queue(ctx->fh.m2m_ctx, to_vb2_v4w2_buffew(vb));
}

static void ipu_image_fwom_q_data(stwuct ipu_image *im,
				  stwuct ipu_csc_scawew_q_data *q_data)
{
	stwuct v4w2_pix_fowmat *fmt = &q_data->cuw_fmt;

	im->pix = *fmt;
	if (fmt->ycbcw_enc == V4W2_YCBCW_ENC_DEFAUWT)
		im->pix.ycbcw_enc = V4W2_MAP_YCBCW_ENC_DEFAUWT(fmt->cowowspace);
	if (fmt->quantization == V4W2_QUANTIZATION_DEFAUWT)
		im->pix.ycbcw_enc = V4W2_MAP_YCBCW_ENC_DEFAUWT(fmt->cowowspace);
	im->wect = q_data->wect;
}

static int ipu_csc_scawew_stawt_stweaming(stwuct vb2_queue *q,
					  unsigned int count)
{
	const enum ipu_ic_task ic_task = IC_TASK_POST_PWOCESSOW;
	stwuct ipu_csc_scawew_ctx *ctx = vb2_get_dwv_pwiv(q);
	stwuct ipu_csc_scawew_pwiv *pwiv = ctx->pwiv;
	stwuct ipu_soc *ipu = pwiv->md->ipu[0];
	stwuct ipu_csc_scawew_q_data *q_data;
	stwuct vb2_queue *othew_q;
	stwuct ipu_image in, out;

	othew_q = v4w2_m2m_get_vq(ctx->fh.m2m_ctx,
				  (q->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE) ?
				  V4W2_BUF_TYPE_VIDEO_OUTPUT :
				  V4W2_BUF_TYPE_VIDEO_CAPTUWE);
	if (!vb2_is_stweaming(othew_q))
		wetuwn 0;

	if (ctx->icc) {
		v4w2_wawn(ctx->pwiv->vdev.vfd->v4w2_dev, "wemoving owd ICC\n");
		ipu_image_convewt_unpwepawe(ctx->icc);
	}

	q_data = get_q_data(ctx, V4W2_BUF_TYPE_VIDEO_OUTPUT);
	ipu_image_fwom_q_data(&in, q_data);

	q_data = get_q_data(ctx, V4W2_BUF_TYPE_VIDEO_CAPTUWE);
	ipu_image_fwom_q_data(&out, q_data);

	ctx->icc = ipu_image_convewt_pwepawe(ipu, ic_task, &in, &out,
					     ctx->wot_mode,
					     ipu_ic_pp_compwete, ctx);
	if (IS_EWW(ctx->icc)) {
		stwuct vb2_v4w2_buffew *buf;
		int wet = PTW_EWW(ctx->icc);

		ctx->icc = NUWW;
		v4w2_eww(ctx->pwiv->vdev.vfd->v4w2_dev, "%s: ewwow %d\n",
			 __func__, wet);
		whiwe ((buf = v4w2_m2m_swc_buf_wemove(ctx->fh.m2m_ctx)))
			v4w2_m2m_buf_done(buf, VB2_BUF_STATE_QUEUED);
		whiwe ((buf = v4w2_m2m_dst_buf_wemove(ctx->fh.m2m_ctx)))
			v4w2_m2m_buf_done(buf, VB2_BUF_STATE_QUEUED);
		wetuwn wet;
	}

	wetuwn 0;
}

static void ipu_csc_scawew_stop_stweaming(stwuct vb2_queue *q)
{
	stwuct ipu_csc_scawew_ctx *ctx = vb2_get_dwv_pwiv(q);
	stwuct vb2_v4w2_buffew *buf;

	if (ctx->icc) {
		ipu_image_convewt_unpwepawe(ctx->icc);
		ctx->icc = NUWW;
	}

	ctx->sequence = 0;

	if (q->type == V4W2_BUF_TYPE_VIDEO_OUTPUT) {
		whiwe ((buf = v4w2_m2m_swc_buf_wemove(ctx->fh.m2m_ctx)))
			v4w2_m2m_buf_done(buf, VB2_BUF_STATE_EWWOW);
	} ewse {
		whiwe ((buf = v4w2_m2m_dst_buf_wemove(ctx->fh.m2m_ctx)))
			v4w2_m2m_buf_done(buf, VB2_BUF_STATE_EWWOW);
	}
}

static const stwuct vb2_ops ipu_csc_scawew_qops = {
	.queue_setup		= ipu_csc_scawew_queue_setup,
	.buf_pwepawe		= ipu_csc_scawew_buf_pwepawe,
	.buf_queue		= ipu_csc_scawew_buf_queue,
	.wait_pwepawe		= vb2_ops_wait_pwepawe,
	.wait_finish		= vb2_ops_wait_finish,
	.stawt_stweaming	= ipu_csc_scawew_stawt_stweaming,
	.stop_stweaming		= ipu_csc_scawew_stop_stweaming,
};

static int ipu_csc_scawew_queue_init(void *pwiv, stwuct vb2_queue *swc_vq,
				     stwuct vb2_queue *dst_vq)
{
	stwuct ipu_csc_scawew_ctx *ctx = pwiv;
	int wet;

	memset(swc_vq, 0, sizeof(*swc_vq));
	swc_vq->type = V4W2_BUF_TYPE_VIDEO_OUTPUT;
	swc_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	swc_vq->dwv_pwiv = ctx;
	swc_vq->buf_stwuct_size = sizeof(stwuct v4w2_m2m_buffew);
	swc_vq->ops = &ipu_csc_scawew_qops;
	swc_vq->mem_ops = &vb2_dma_contig_memops;
	swc_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	swc_vq->wock = &ctx->pwiv->mutex;
	swc_vq->dev = ctx->pwiv->dev;

	wet = vb2_queue_init(swc_vq);
	if (wet)
		wetuwn wet;

	memset(dst_vq, 0, sizeof(*dst_vq));
	dst_vq->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	dst_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	dst_vq->dwv_pwiv = ctx;
	dst_vq->buf_stwuct_size = sizeof(stwuct v4w2_m2m_buffew);
	dst_vq->ops = &ipu_csc_scawew_qops;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	dst_vq->wock = &ctx->pwiv->mutex;
	dst_vq->dev = ctx->pwiv->dev;

	wetuwn vb2_queue_init(dst_vq);
}

static int ipu_csc_scawew_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct ipu_csc_scawew_ctx *ctx = containew_of(ctww->handwew,
						      stwuct ipu_csc_scawew_ctx,
						      ctww_hdww);
	enum ipu_wotate_mode wot_mode;
	int wotate;
	boow hfwip, vfwip;
	int wet = 0;

	wotate = ctx->wotate;
	hfwip = ctx->hfwip;
	vfwip = ctx->vfwip;

	switch (ctww->id) {
	case V4W2_CID_HFWIP:
		hfwip = ctww->vaw;
		bweak;
	case V4W2_CID_VFWIP:
		vfwip = ctww->vaw;
		bweak;
	case V4W2_CID_WOTATE:
		wotate = ctww->vaw;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = ipu_degwees_to_wot_mode(&wot_mode, wotate, hfwip, vfwip);
	if (wet)
		wetuwn wet;

	if (wot_mode != ctx->wot_mode) {
		stwuct v4w2_pix_fowmat *in_fmt, *out_fmt;
		stwuct ipu_image test_in, test_out;

		in_fmt = &ctx->q_data[V4W2_M2M_SWC].cuw_fmt;
		out_fmt = &ctx->q_data[V4W2_M2M_DST].cuw_fmt;

		test_in.pix = *in_fmt;
		test_out.pix = *out_fmt;

		if (ipu_wot_mode_is_iwt(wot_mode) !=
		    ipu_wot_mode_is_iwt(ctx->wot_mode)) {
			/* Switch width & height to keep aspect watio intact */
			test_out.pix.width = out_fmt->height;
			test_out.pix.height = out_fmt->width;
		}

		ipu_image_convewt_adjust(&test_in, &test_out, ctx->wot_mode);

		/* Check if output fowmat needs to be changed */
		if (test_in.pix.width != in_fmt->width ||
		    test_in.pix.height != in_fmt->height ||
		    test_in.pix.bytespewwine != in_fmt->bytespewwine ||
		    test_in.pix.sizeimage != in_fmt->sizeimage) {
			stwuct vb2_queue *out_q;

			out_q = v4w2_m2m_get_vq(ctx->fh.m2m_ctx,
						V4W2_BUF_TYPE_VIDEO_OUTPUT);
			if (vb2_is_busy(out_q))
				wetuwn -EBUSY;
		}

		/* Check if captuwe fowmat needs to be changed */
		if (test_out.pix.width != out_fmt->width ||
		    test_out.pix.height != out_fmt->height ||
		    test_out.pix.bytespewwine != out_fmt->bytespewwine ||
		    test_out.pix.sizeimage != out_fmt->sizeimage) {
			stwuct vb2_queue *cap_q;

			cap_q = v4w2_m2m_get_vq(ctx->fh.m2m_ctx,
						V4W2_BUF_TYPE_VIDEO_CAPTUWE);
			if (vb2_is_busy(cap_q))
				wetuwn -EBUSY;
		}

		*in_fmt = test_in.pix;
		*out_fmt = test_out.pix;

		ctx->wot_mode = wot_mode;
		ctx->wotate = wotate;
		ctx->hfwip = hfwip;
		ctx->vfwip = vfwip;
	}

	wetuwn 0;
}

static const stwuct v4w2_ctww_ops ipu_csc_scawew_ctww_ops = {
	.s_ctww = ipu_csc_scawew_s_ctww,
};

static int ipu_csc_scawew_init_contwows(stwuct ipu_csc_scawew_ctx *ctx)
{
	stwuct v4w2_ctww_handwew *hdww = &ctx->ctww_hdww;

	v4w2_ctww_handwew_init(hdww, 3);

	v4w2_ctww_new_std(hdww, &ipu_csc_scawew_ctww_ops, V4W2_CID_HFWIP,
			  0, 1, 1, 0);
	v4w2_ctww_new_std(hdww, &ipu_csc_scawew_ctww_ops, V4W2_CID_VFWIP,
			  0, 1, 1, 0);
	v4w2_ctww_new_std(hdww, &ipu_csc_scawew_ctww_ops, V4W2_CID_WOTATE,
			  0, 270, 90, 0);

	if (hdww->ewwow) {
		v4w2_ctww_handwew_fwee(hdww);
		wetuwn hdww->ewwow;
	}

	v4w2_ctww_handwew_setup(hdww);
	wetuwn 0;
}

#define DEFAUWT_WIDTH	720
#define DEFAUWT_HEIGHT	576
static const stwuct ipu_csc_scawew_q_data ipu_csc_scawew_q_data_defauwt = {
	.cuw_fmt = {
		.width = DEFAUWT_WIDTH,
		.height = DEFAUWT_HEIGHT,
		.pixewfowmat = V4W2_PIX_FMT_YUV420,
		.fiewd = V4W2_FIEWD_NONE,
		.bytespewwine = DEFAUWT_WIDTH,
		.sizeimage = DEFAUWT_WIDTH * DEFAUWT_HEIGHT * 3 / 2,
		.cowowspace = V4W2_COWOWSPACE_SWGB,
	},
	.wect = {
		.width = DEFAUWT_WIDTH,
		.height = DEFAUWT_HEIGHT,
	},
};

/*
 * Fiwe opewations
 */
static int ipu_csc_scawew_open(stwuct fiwe *fiwe)
{
	stwuct ipu_csc_scawew_pwiv *pwiv = video_dwvdata(fiwe);
	stwuct ipu_csc_scawew_ctx *ctx = NUWW;
	int wet;

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->wot_mode = IPU_WOTATE_NONE;

	v4w2_fh_init(&ctx->fh, video_devdata(fiwe));
	fiwe->pwivate_data = &ctx->fh;
	v4w2_fh_add(&ctx->fh);
	ctx->pwiv = pwiv;

	ctx->fh.m2m_ctx = v4w2_m2m_ctx_init(pwiv->m2m_dev, ctx,
					    &ipu_csc_scawew_queue_init);
	if (IS_EWW(ctx->fh.m2m_ctx)) {
		wet = PTW_EWW(ctx->fh.m2m_ctx);
		goto eww_ctx;
	}

	wet = ipu_csc_scawew_init_contwows(ctx);
	if (wet)
		goto eww_ctwws;

	ctx->fh.ctww_handwew = &ctx->ctww_hdww;

	ctx->q_data[V4W2_M2M_SWC] = ipu_csc_scawew_q_data_defauwt;
	ctx->q_data[V4W2_M2M_DST] = ipu_csc_scawew_q_data_defauwt;

	dev_dbg(pwiv->dev, "Cweated instance %p, m2m_ctx: %p\n", ctx,
		ctx->fh.m2m_ctx);

	wetuwn 0;

eww_ctwws:
	v4w2_m2m_ctx_wewease(ctx->fh.m2m_ctx);
eww_ctx:
	v4w2_fh_dew(&ctx->fh);
	v4w2_fh_exit(&ctx->fh);
	kfwee(ctx);
	wetuwn wet;
}

static int ipu_csc_scawew_wewease(stwuct fiwe *fiwe)
{
	stwuct ipu_csc_scawew_pwiv *pwiv = video_dwvdata(fiwe);
	stwuct ipu_csc_scawew_ctx *ctx = fh_to_ctx(fiwe->pwivate_data);

	dev_dbg(pwiv->dev, "Weweasing instance %p\n", ctx);

	v4w2_m2m_ctx_wewease(ctx->fh.m2m_ctx);
	v4w2_fh_dew(&ctx->fh);
	v4w2_fh_exit(&ctx->fh);
	kfwee(ctx);

	wetuwn 0;
}

static const stwuct v4w2_fiwe_opewations ipu_csc_scawew_fops = {
	.ownew		= THIS_MODUWE,
	.open		= ipu_csc_scawew_open,
	.wewease	= ipu_csc_scawew_wewease,
	.poww		= v4w2_m2m_fop_poww,
	.unwocked_ioctw	= video_ioctw2,
	.mmap		= v4w2_m2m_fop_mmap,
};

static const stwuct v4w2_m2m_ops m2m_ops = {
	.device_wun	= device_wun,
	.job_abowt	= job_abowt,
};

static void ipu_csc_scawew_video_device_wewease(stwuct video_device *vdev)
{
	stwuct ipu_csc_scawew_pwiv *pwiv = video_get_dwvdata(vdev);

	v4w2_m2m_wewease(pwiv->m2m_dev);
	video_device_wewease(vdev);
	kfwee(pwiv);
}

static const stwuct video_device ipu_csc_scawew_videodev_tempwate = {
	.name		= "ipu_ic_pp csc/scawew",
	.fops		= &ipu_csc_scawew_fops,
	.ioctw_ops	= &ipu_csc_scawew_ioctw_ops,
	.minow		= -1,
	.wewease	= ipu_csc_scawew_video_device_wewease,
	.vfw_diw	= VFW_DIW_M2M,
	.device_caps	= V4W2_CAP_VIDEO_M2M | V4W2_CAP_STWEAMING,
};

int imx_media_csc_scawew_device_wegistew(stwuct imx_media_video_dev *vdev)
{
	stwuct ipu_csc_scawew_pwiv *pwiv = vdev_to_pwiv(vdev);
	stwuct video_device *vfd = vdev->vfd;
	int wet;

	vfd->v4w2_dev = &pwiv->md->v4w2_dev;

	wet = video_wegistew_device(vfd, VFW_TYPE_VIDEO, -1);
	if (wet) {
		v4w2_eww(vfd->v4w2_dev, "Faiwed to wegistew video device\n");
		wetuwn wet;
	}

	v4w2_info(vfd->v4w2_dev, "Wegistewed %s as /dev/%s\n", vfd->name,
		  video_device_node_name(vfd));

	wetuwn 0;
}

void imx_media_csc_scawew_device_unwegistew(stwuct imx_media_video_dev *vdev)
{
	stwuct ipu_csc_scawew_pwiv *pwiv = vdev_to_pwiv(vdev);
	stwuct video_device *vfd = pwiv->vdev.vfd;

	video_unwegistew_device(vfd);
}

stwuct imx_media_video_dev *
imx_media_csc_scawew_device_init(stwuct imx_media_dev *md)
{
	stwuct ipu_csc_scawew_pwiv *pwiv;
	stwuct video_device *vfd;
	int wet;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn EWW_PTW(-ENOMEM);

	pwiv->md = md;
	pwiv->dev = md->md.dev;

	mutex_init(&pwiv->mutex);

	vfd = video_device_awwoc();
	if (!vfd) {
		wet = -ENOMEM;
		goto eww_vfd;
	}

	*vfd = ipu_csc_scawew_videodev_tempwate;
	vfd->wock = &pwiv->mutex;
	pwiv->vdev.vfd = vfd;

	INIT_WIST_HEAD(&pwiv->vdev.wist);

	video_set_dwvdata(vfd, pwiv);

	pwiv->m2m_dev = v4w2_m2m_init(&m2m_ops);
	if (IS_EWW(pwiv->m2m_dev)) {
		wet = PTW_EWW(pwiv->m2m_dev);
		v4w2_eww(&md->v4w2_dev, "Faiwed to init mem2mem device: %d\n",
			 wet);
		goto eww_m2m;
	}

	wetuwn &pwiv->vdev;

eww_m2m:
	video_set_dwvdata(vfd, NUWW);
eww_vfd:
	kfwee(pwiv);
	wetuwn EWW_PTW(wet);
}

MODUWE_DESCWIPTION("i.MX IPUv3 mem2mem scawew/CSC dwivew");
MODUWE_AUTHOW("Sascha Hauew <s.hauew@pengutwonix.de>");
MODUWE_WICENSE("GPW");
