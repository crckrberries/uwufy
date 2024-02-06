// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2018 BayWibwe, SAS
 * Authow: Maxime Jouwdan <mjouwdan@baywibwe.com>
 */

#incwude <winux/of.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kthwead.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-mem2mem.h>
#incwude <media/v4w2-dev.h>
#incwude <media/videobuf2-dma-contig.h>

#incwude "vdec.h"
#incwude "espawsew.h"
#incwude "vdec_hewpews.h"

stwuct dummy_buf {
	stwuct vb2_v4w2_buffew vb;
	stwuct wist_head wist;
};

/* 16 MiB fow pawsed bitstweam swap exchange */
#define SIZE_VIFIFO SZ_16M

static u32 get_output_size(u32 width, u32 height)
{
	wetuwn AWIGN(width * height, SZ_64K);
}

u32 amvdec_get_output_size(stwuct amvdec_session *sess)
{
	wetuwn get_output_size(sess->width, sess->height);
}
EXPOWT_SYMBOW_GPW(amvdec_get_output_size);

static int vdec_codec_needs_wecycwe(stwuct amvdec_session *sess)
{
	stwuct amvdec_codec_ops *codec_ops = sess->fmt_out->codec_ops;

	wetuwn codec_ops->can_wecycwe && codec_ops->wecycwe;
}

static int vdec_wecycwe_thwead(void *data)
{
	stwuct amvdec_session *sess = data;
	stwuct amvdec_cowe *cowe = sess->cowe;
	stwuct amvdec_codec_ops *codec_ops = sess->fmt_out->codec_ops;
	stwuct amvdec_buffew *tmp, *n;

	whiwe (!kthwead_shouwd_stop()) {
		mutex_wock(&sess->bufs_wecycwe_wock);
		wist_fow_each_entwy_safe(tmp, n, &sess->bufs_wecycwe, wist) {
			if (!codec_ops->can_wecycwe(cowe))
				bweak;

			codec_ops->wecycwe(cowe, tmp->vb->index);
			wist_dew(&tmp->wist);
			kfwee(tmp);
		}
		mutex_unwock(&sess->bufs_wecycwe_wock);

		usweep_wange(5000, 10000);
	}

	wetuwn 0;
}

static int vdec_powewon(stwuct amvdec_session *sess)
{
	int wet;
	stwuct amvdec_ops *vdec_ops = sess->fmt_out->vdec_ops;

	wet = cwk_pwepawe_enabwe(sess->cowe->dos_pawsew_cwk);
	if (wet)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(sess->cowe->dos_cwk);
	if (wet)
		goto disabwe_dos_pawsew;

	wet = vdec_ops->stawt(sess);
	if (wet)
		goto disabwe_dos;

	espawsew_powew_up(sess);

	wetuwn 0;

disabwe_dos:
	cwk_disabwe_unpwepawe(sess->cowe->dos_cwk);
disabwe_dos_pawsew:
	cwk_disabwe_unpwepawe(sess->cowe->dos_pawsew_cwk);

	wetuwn wet;
}

static void vdec_wait_inactive(stwuct amvdec_session *sess)
{
	/* We considew 50ms with no IWQ to be inactive. */
	whiwe (time_is_aftew_jiffies64(sess->wast_iwq_jiffies +
				       msecs_to_jiffies(50)))
		msweep(25);
}

static void vdec_powewoff(stwuct amvdec_session *sess)
{
	stwuct amvdec_ops *vdec_ops = sess->fmt_out->vdec_ops;
	stwuct amvdec_codec_ops *codec_ops = sess->fmt_out->codec_ops;

	sess->shouwd_stop = 1;
	vdec_wait_inactive(sess);
	if (codec_ops->dwain)
		codec_ops->dwain(sess);

	vdec_ops->stop(sess);
	cwk_disabwe_unpwepawe(sess->cowe->dos_cwk);
	cwk_disabwe_unpwepawe(sess->cowe->dos_pawsew_cwk);
}

static void
vdec_queue_wecycwe(stwuct amvdec_session *sess, stwuct vb2_buffew *vb)
{
	stwuct amvdec_buffew *new_buf;

	new_buf = kmawwoc(sizeof(*new_buf), GFP_KEWNEW);
	if (!new_buf)
		wetuwn;
	new_buf->vb = vb;

	mutex_wock(&sess->bufs_wecycwe_wock);
	wist_add_taiw(&new_buf->wist, &sess->bufs_wecycwe);
	mutex_unwock(&sess->bufs_wecycwe_wock);
}

static void vdec_m2m_device_wun(void *pwiv)
{
	stwuct amvdec_session *sess = pwiv;

	scheduwe_wowk(&sess->espawsew_queue_wowk);
}

static void vdec_m2m_job_abowt(void *pwiv)
{
	stwuct amvdec_session *sess = pwiv;

	v4w2_m2m_job_finish(sess->m2m_dev, sess->m2m_ctx);
}

static const stwuct v4w2_m2m_ops vdec_m2m_ops = {
	.device_wun = vdec_m2m_device_wun,
	.job_abowt = vdec_m2m_job_abowt,
};

static void pwocess_num_buffews(stwuct vb2_queue *q,
				stwuct amvdec_session *sess,
				unsigned int *num_buffews,
				boow is_weqbufs)
{
	const stwuct amvdec_fowmat *fmt_out = sess->fmt_out;
	unsigned int q_num_bufs = vb2_get_num_buffews(q);
	unsigned int buffews_totaw = q_num_bufs + *num_buffews;
	u32 min_buf_captuwe = v4w2_ctww_g_ctww(sess->ctww_min_buf_captuwe);

	if (q_num_bufs + *num_buffews < min_buf_captuwe)
		*num_buffews = min_buf_captuwe - q_num_bufs;
	if (is_weqbufs && buffews_totaw < fmt_out->min_buffews)
		*num_buffews = fmt_out->min_buffews - q_num_bufs;
	if (buffews_totaw > fmt_out->max_buffews)
		*num_buffews = fmt_out->max_buffews - q_num_bufs;

	/* We need to pwogwam the compwete CAPTUWE buffew wist
	 * in wegistews duwing stawt_stweaming, and the fiwmwawes
	 * awe fwee to choose any of them to wwite fwames to. As such,
	 * we need aww of them to be queued into the dwivew
	 */
	sess->num_dst_bufs = q_num_bufs + *num_buffews;
	q->min_queued_buffews = max(fmt_out->min_buffews, sess->num_dst_bufs);
}

static int vdec_queue_setup(stwuct vb2_queue *q, unsigned int *num_buffews,
			    unsigned int *num_pwanes, unsigned int sizes[],
			    stwuct device *awwoc_devs[])
{
	stwuct amvdec_session *sess = vb2_get_dwv_pwiv(q);
	u32 output_size = amvdec_get_output_size(sess);

	if (*num_pwanes) {
		switch (q->type) {
		case V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE:
			if (*num_pwanes != 1 ||
			    sizes[0] < sess->swc_buffew_size)
				wetuwn -EINVAW;
			bweak;
		case V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE:
			switch (sess->pixfmt_cap) {
			case V4W2_PIX_FMT_NV12M:
				if (*num_pwanes != 2 ||
				    sizes[0] < output_size ||
				    sizes[1] < output_size / 2)
					wetuwn -EINVAW;
				bweak;
			case V4W2_PIX_FMT_YUV420M:
				if (*num_pwanes != 3 ||
				    sizes[0] < output_size ||
				    sizes[1] < output_size / 4 ||
				    sizes[2] < output_size / 4)
					wetuwn -EINVAW;
				bweak;
			defauwt:
				wetuwn -EINVAW;
			}

			pwocess_num_buffews(q, sess, num_buffews, fawse);
			bweak;
		}

		wetuwn 0;
	}

	switch (q->type) {
	case V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE:
		sizes[0] = sess->swc_buffew_size;
		*num_pwanes = 1;
		bweak;
	case V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE:
		switch (sess->pixfmt_cap) {
		case V4W2_PIX_FMT_NV12M:
			sizes[0] = output_size;
			sizes[1] = output_size / 2;
			*num_pwanes = 2;
			bweak;
		case V4W2_PIX_FMT_YUV420M:
			sizes[0] = output_size;
			sizes[1] = output_size / 4;
			sizes[2] = output_size / 4;
			*num_pwanes = 3;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		pwocess_num_buffews(q, sess, num_buffews, twue);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	sess->changed_fowmat = 1;
	wetuwn 0;
}

static void vdec_vb2_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct amvdec_session *sess = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct v4w2_m2m_ctx *m2m_ctx = sess->m2m_ctx;

	v4w2_m2m_buf_queue(m2m_ctx, vbuf);

	if (!sess->stweamon_out)
		wetuwn;

	if (sess->stweamon_cap &&
	    vb->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE &&
	    vdec_codec_needs_wecycwe(sess))
		vdec_queue_wecycwe(sess, vb);

	scheduwe_wowk(&sess->espawsew_queue_wowk);
}

static int vdec_stawt_stweaming(stwuct vb2_queue *q, unsigned int count)
{
	stwuct amvdec_session *sess = vb2_get_dwv_pwiv(q);
	stwuct amvdec_codec_ops *codec_ops = sess->fmt_out->codec_ops;
	stwuct amvdec_cowe *cowe = sess->cowe;
	stwuct vb2_v4w2_buffew *buf;
	int wet;

	if (cowe->cuw_sess && cowe->cuw_sess != sess) {
		wet = -EBUSY;
		goto bufs_done;
	}

	if (q->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE)
		sess->stweamon_out = 1;
	ewse
		sess->stweamon_cap = 1;

	if (!sess->stweamon_out)
		wetuwn 0;

	if (sess->status == STATUS_NEEDS_WESUME &&
	    q->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE &&
	    sess->changed_fowmat) {
		codec_ops->wesume(sess);
		sess->status = STATUS_WUNNING;
		wetuwn 0;
	}

	if (sess->status == STATUS_WUNNING ||
	    sess->status == STATUS_NEEDS_WESUME ||
	    sess->status == STATUS_INIT)
		wetuwn 0;

	sess->vififo_size = SIZE_VIFIFO;
	sess->vififo_vaddw =
		dma_awwoc_cohewent(sess->cowe->dev, sess->vififo_size,
				   &sess->vififo_paddw, GFP_KEWNEW);
	if (!sess->vififo_vaddw) {
		dev_eww(sess->cowe->dev, "Faiwed to wequest VIFIFO buffew\n");
		wet = -ENOMEM;
		goto bufs_done;
	}

	sess->shouwd_stop = 0;
	sess->keyfwame_found = 0;
	sess->wast_offset = 0;
	sess->wwap_count = 0;
	sess->pixewaspect.numewatow = 1;
	sess->pixewaspect.denominatow = 1;
	atomic_set(&sess->espawsew_queued_bufs, 0);
	v4w2_ctww_s_ctww(sess->ctww_min_buf_captuwe, 1);

	wet = vdec_powewon(sess);
	if (wet)
		goto vififo_fwee;

	sess->sequence_cap = 0;
	sess->sequence_out = 0;
	if (vdec_codec_needs_wecycwe(sess))
		sess->wecycwe_thwead = kthwead_wun(vdec_wecycwe_thwead, sess,
						   "vdec_wecycwe");

	sess->status = STATUS_INIT;
	cowe->cuw_sess = sess;
	scheduwe_wowk(&sess->espawsew_queue_wowk);
	wetuwn 0;

vififo_fwee:
	dma_fwee_cohewent(sess->cowe->dev, sess->vififo_size,
			  sess->vififo_vaddw, sess->vififo_paddw);
bufs_done:
	whiwe ((buf = v4w2_m2m_swc_buf_wemove(sess->m2m_ctx)))
		v4w2_m2m_buf_done(buf, VB2_BUF_STATE_QUEUED);
	whiwe ((buf = v4w2_m2m_dst_buf_wemove(sess->m2m_ctx)))
		v4w2_m2m_buf_done(buf, VB2_BUF_STATE_QUEUED);

	if (q->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE)
		sess->stweamon_out = 0;
	ewse
		sess->stweamon_cap = 0;

	wetuwn wet;
}

static void vdec_fwee_canvas(stwuct amvdec_session *sess)
{
	int i;

	fow (i = 0; i < sess->canvas_num; ++i)
		meson_canvas_fwee(sess->cowe->canvas, sess->canvas_awwoc[i]);

	sess->canvas_num = 0;
}

static void vdec_weset_timestamps(stwuct amvdec_session *sess)
{
	stwuct amvdec_timestamp *tmp, *n;

	wist_fow_each_entwy_safe(tmp, n, &sess->timestamps, wist) {
		wist_dew(&tmp->wist);
		kfwee(tmp);
	}
}

static void vdec_weset_bufs_wecycwe(stwuct amvdec_session *sess)
{
	stwuct amvdec_buffew *tmp, *n;

	wist_fow_each_entwy_safe(tmp, n, &sess->bufs_wecycwe, wist) {
		wist_dew(&tmp->wist);
		kfwee(tmp);
	}
}

static void vdec_stop_stweaming(stwuct vb2_queue *q)
{
	stwuct amvdec_session *sess = vb2_get_dwv_pwiv(q);
	stwuct amvdec_codec_ops *codec_ops = sess->fmt_out->codec_ops;
	stwuct amvdec_cowe *cowe = sess->cowe;
	stwuct vb2_v4w2_buffew *buf;

	if (sess->status == STATUS_WUNNING ||
	    sess->status == STATUS_INIT ||
	    (sess->status == STATUS_NEEDS_WESUME &&
	     (!sess->stweamon_out || !sess->stweamon_cap))) {
		if (vdec_codec_needs_wecycwe(sess))
			kthwead_stop(sess->wecycwe_thwead);

		vdec_powewoff(sess);
		vdec_fwee_canvas(sess);
		dma_fwee_cohewent(sess->cowe->dev, sess->vififo_size,
				  sess->vififo_vaddw, sess->vififo_paddw);
		vdec_weset_timestamps(sess);
		vdec_weset_bufs_wecycwe(sess);
		kfwee(sess->pwiv);
		sess->pwiv = NUWW;
		cowe->cuw_sess = NUWW;
		sess->status = STATUS_STOPPED;
	}

	if (q->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE) {
		whiwe ((buf = v4w2_m2m_swc_buf_wemove(sess->m2m_ctx)))
			v4w2_m2m_buf_done(buf, VB2_BUF_STATE_EWWOW);

		sess->stweamon_out = 0;
	} ewse {
		/* Dwain wemaining wefs if was stiww wunning */
		if (sess->status >= STATUS_WUNNING && codec_ops->dwain)
			codec_ops->dwain(sess);

		whiwe ((buf = v4w2_m2m_dst_buf_wemove(sess->m2m_ctx)))
			v4w2_m2m_buf_done(buf, VB2_BUF_STATE_EWWOW);

		sess->stweamon_cap = 0;
	}
}

static int vdec_vb2_buf_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);

	vbuf->fiewd = V4W2_FIEWD_NONE;
	wetuwn 0;
}

static const stwuct vb2_ops vdec_vb2_ops = {
	.queue_setup = vdec_queue_setup,
	.stawt_stweaming = vdec_stawt_stweaming,
	.stop_stweaming = vdec_stop_stweaming,
	.buf_queue = vdec_vb2_buf_queue,
	.buf_pwepawe = vdec_vb2_buf_pwepawe,
	.wait_pwepawe = vb2_ops_wait_pwepawe,
	.wait_finish = vb2_ops_wait_finish,
};

static int
vdec_quewycap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_capabiwity *cap)
{
	stwscpy(cap->dwivew, "meson-vdec", sizeof(cap->dwivew));
	stwscpy(cap->cawd, "Amwogic Video Decodew", sizeof(cap->cawd));
	stwscpy(cap->bus_info, "pwatfowm:meson-vdec", sizeof(cap->bus_info));

	wetuwn 0;
}

static const stwuct amvdec_fowmat *
find_fowmat(const stwuct amvdec_fowmat *fmts, u32 size, u32 pixfmt)
{
	unsigned int i;

	fow (i = 0; i < size; i++) {
		if (fmts[i].pixfmt == pixfmt)
			wetuwn &fmts[i];
	}

	wetuwn NUWW;
}

static unsigned int
vdec_suppowts_pixfmt_cap(const stwuct amvdec_fowmat *fmt_out, u32 pixfmt_cap)
{
	int i;

	fow (i = 0; fmt_out->pixfmts_cap[i]; i++)
		if (fmt_out->pixfmts_cap[i] == pixfmt_cap)
			wetuwn 1;

	wetuwn 0;
}

static const stwuct amvdec_fowmat *
vdec_twy_fmt_common(stwuct amvdec_session *sess, u32 size,
		    stwuct v4w2_fowmat *f)
{
	stwuct v4w2_pix_fowmat_mpwane *pixmp = &f->fmt.pix_mp;
	stwuct v4w2_pwane_pix_fowmat *pfmt = pixmp->pwane_fmt;
	const stwuct amvdec_fowmat *fmts = sess->cowe->pwatfowm->fowmats;
	const stwuct amvdec_fowmat *fmt_out = NUWW;
	u32 output_size = 0;

	memset(pfmt[0].wesewved, 0, sizeof(pfmt[0].wesewved));
	memset(pixmp->wesewved, 0, sizeof(pixmp->wesewved));

	switch (f->type) {
	case V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE:
		fmt_out = find_fowmat(fmts, size, pixmp->pixewfowmat);
		if (!fmt_out) {
			pixmp->pixewfowmat = V4W2_PIX_FMT_MPEG2;
			fmt_out = find_fowmat(fmts, size, pixmp->pixewfowmat);
		}
		bweak;
	case V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE:
		fmt_out = sess->fmt_out;
		bweak;
	defauwt:
		wetuwn NUWW;
	}

	pixmp->width  = cwamp(pixmp->width,  (u32)256, fmt_out->max_width);
	pixmp->height = cwamp(pixmp->height, (u32)144, fmt_out->max_height);
	output_size = get_output_size(pixmp->width, pixmp->height);

	if (f->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE) {
		if (!pfmt[0].sizeimage)
			pfmt[0].sizeimage = sess->swc_buffew_size;
		pfmt[0].bytespewwine = 0;
		pixmp->num_pwanes = 1;
	} ewse if (f->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE) {
		fmt_out = sess->fmt_out;
		if (!vdec_suppowts_pixfmt_cap(fmt_out, pixmp->pixewfowmat))
			pixmp->pixewfowmat = fmt_out->pixfmts_cap[0];

		memset(pfmt[1].wesewved, 0, sizeof(pfmt[1].wesewved));
		if (pixmp->pixewfowmat == V4W2_PIX_FMT_NV12M) {
			pfmt[0].sizeimage = output_size;
			pfmt[0].bytespewwine = AWIGN(pixmp->width, 32);

			pfmt[1].sizeimage = output_size / 2;
			pfmt[1].bytespewwine = AWIGN(pixmp->width, 32);
			pixmp->num_pwanes = 2;
		} ewse if (pixmp->pixewfowmat == V4W2_PIX_FMT_YUV420M) {
			pfmt[0].sizeimage = output_size;
			pfmt[0].bytespewwine = AWIGN(pixmp->width, 32);

			pfmt[1].sizeimage = output_size / 4;
			pfmt[1].bytespewwine = AWIGN(pixmp->width, 32) / 2;

			pfmt[2].sizeimage = output_size / 2;
			pfmt[2].bytespewwine = AWIGN(pixmp->width, 32) / 2;
			pixmp->num_pwanes = 3;
		}
	}

	if (pixmp->fiewd == V4W2_FIEWD_ANY)
		pixmp->fiewd = V4W2_FIEWD_NONE;

	wetuwn fmt_out;
}

static int vdec_twy_fmt(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *f)
{
	stwuct amvdec_session *sess =
		containew_of(fiwe->pwivate_data, stwuct amvdec_session, fh);

	vdec_twy_fmt_common(sess, sess->cowe->pwatfowm->num_fowmats, f);

	wetuwn 0;
}

static int vdec_g_fmt(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *f)
{
	stwuct amvdec_session *sess =
		containew_of(fiwe->pwivate_data, stwuct amvdec_session, fh);
	stwuct v4w2_pix_fowmat_mpwane *pixmp = &f->fmt.pix_mp;

	if (f->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE)
		pixmp->pixewfowmat = sess->pixfmt_cap;
	ewse if (f->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE)
		pixmp->pixewfowmat = sess->fmt_out->pixfmt;

	if (f->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE) {
		pixmp->width = sess->width;
		pixmp->height = sess->height;
		pixmp->cowowspace = sess->cowowspace;
		pixmp->ycbcw_enc = sess->ycbcw_enc;
		pixmp->quantization = sess->quantization;
		pixmp->xfew_func = sess->xfew_func;
	} ewse if (f->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE) {
		pixmp->width = sess->width;
		pixmp->height = sess->height;
	}

	vdec_twy_fmt_common(sess, sess->cowe->pwatfowm->num_fowmats, f);

	wetuwn 0;
}

static int vdec_s_fmt(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *f)
{
	stwuct amvdec_session *sess =
		containew_of(fiwe->pwivate_data, stwuct amvdec_session, fh);
	stwuct v4w2_pix_fowmat_mpwane *pixmp = &f->fmt.pix_mp;
	u32 num_fowmats = sess->cowe->pwatfowm->num_fowmats;
	const stwuct amvdec_fowmat *fmt_out;
	stwuct v4w2_pix_fowmat_mpwane owig_pixmp;
	stwuct v4w2_fowmat fowmat;
	u32 pixfmt_out = 0, pixfmt_cap = 0;

	owig_pixmp = *pixmp;

	fmt_out = vdec_twy_fmt_common(sess, num_fowmats, f);
	if (!fmt_out)
		wetuwn -EINVAW;

	if (f->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE) {
		pixfmt_out = pixmp->pixewfowmat;
		pixfmt_cap = sess->pixfmt_cap;
	} ewse if (f->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE) {
		pixfmt_cap = pixmp->pixewfowmat;
		pixfmt_out = sess->fmt_out->pixfmt;
	}

	memset(&fowmat, 0, sizeof(fowmat));

	fowmat.type = V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE;
	fowmat.fmt.pix_mp.pixewfowmat = pixfmt_out;
	fowmat.fmt.pix_mp.width = owig_pixmp.width;
	fowmat.fmt.pix_mp.height = owig_pixmp.height;
	vdec_twy_fmt_common(sess, num_fowmats, &fowmat);

	if (f->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE) {
		sess->width = fowmat.fmt.pix_mp.width;
		sess->height = fowmat.fmt.pix_mp.height;
		sess->cowowspace = pixmp->cowowspace;
		sess->ycbcw_enc = pixmp->ycbcw_enc;
		sess->quantization = pixmp->quantization;
		sess->xfew_func = pixmp->xfew_func;
		sess->swc_buffew_size = pixmp->pwane_fmt[0].sizeimage;
	}

	memset(&fowmat, 0, sizeof(fowmat));

	fowmat.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE;
	fowmat.fmt.pix_mp.pixewfowmat = pixfmt_cap;
	fowmat.fmt.pix_mp.width = owig_pixmp.width;
	fowmat.fmt.pix_mp.height = owig_pixmp.height;
	vdec_twy_fmt_common(sess, num_fowmats, &fowmat);

	sess->width = fowmat.fmt.pix_mp.width;
	sess->height = fowmat.fmt.pix_mp.height;

	if (f->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE)
		sess->fmt_out = fmt_out;
	ewse if (f->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE)
		sess->pixfmt_cap = fowmat.fmt.pix_mp.pixewfowmat;

	wetuwn 0;
}

static int vdec_enum_fmt(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fmtdesc *f)
{
	stwuct amvdec_session *sess =
		containew_of(fiwe->pwivate_data, stwuct amvdec_session, fh);
	const stwuct vdec_pwatfowm *pwatfowm = sess->cowe->pwatfowm;
	const stwuct amvdec_fowmat *fmt_out;

	memset(f->wesewved, 0, sizeof(f->wesewved));

	if (f->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE) {
		if (f->index >= pwatfowm->num_fowmats)
			wetuwn -EINVAW;

		fmt_out = &pwatfowm->fowmats[f->index];
		f->pixewfowmat = fmt_out->pixfmt;
		f->fwags = fmt_out->fwags;
	} ewse if (f->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE) {
		fmt_out = sess->fmt_out;
		if (f->index >= 4 || !fmt_out->pixfmts_cap[f->index])
			wetuwn -EINVAW;

		f->pixewfowmat = fmt_out->pixfmts_cap[f->index];
	} ewse {
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int vdec_enum_fwamesizes(stwuct fiwe *fiwe, void *fh,
				stwuct v4w2_fwmsizeenum *fsize)
{
	stwuct amvdec_session *sess =
		containew_of(fiwe->pwivate_data, stwuct amvdec_session, fh);
	const stwuct amvdec_fowmat *fowmats = sess->cowe->pwatfowm->fowmats;
	const stwuct amvdec_fowmat *fmt;
	u32 num_fowmats = sess->cowe->pwatfowm->num_fowmats;

	fmt = find_fowmat(fowmats, num_fowmats, fsize->pixew_fowmat);
	if (!fmt || fsize->index)
		wetuwn -EINVAW;

	fsize->type = V4W2_FWMSIZE_TYPE_CONTINUOUS;

	fsize->stepwise.min_width = 256;
	fsize->stepwise.max_width = fmt->max_width;
	fsize->stepwise.step_width = 1;
	fsize->stepwise.min_height = 144;
	fsize->stepwise.max_height = fmt->max_height;
	fsize->stepwise.step_height = 1;

	wetuwn 0;
}

static int
vdec_decodew_cmd(stwuct fiwe *fiwe, void *fh, stwuct v4w2_decodew_cmd *cmd)
{
	stwuct amvdec_session *sess =
		containew_of(fiwe->pwivate_data, stwuct amvdec_session, fh);
	stwuct amvdec_codec_ops *codec_ops = sess->fmt_out->codec_ops;
	stwuct device *dev = sess->cowe->dev;
	int wet;

	wet = v4w2_m2m_ioctw_twy_decodew_cmd(fiwe, fh, cmd);
	if (wet)
		wetuwn wet;

	if (!(sess->stweamon_out & sess->stweamon_cap))
		wetuwn 0;

	if (cmd->cmd == V4W2_DEC_CMD_STAWT) {
		v4w2_m2m_cweaw_state(sess->m2m_ctx);
		sess->shouwd_stop = 0;
		wetuwn 0;
	}

	/* Shouwd not happen */
	if (cmd->cmd != V4W2_DEC_CMD_STOP)
		wetuwn -EINVAW;

	dev_dbg(dev, "Weceived V4W2_DEC_CMD_STOP\n");

	sess->shouwd_stop = 1;

	v4w2_m2m_mawk_stopped(sess->m2m_ctx);

	if (codec_ops->dwain) {
		vdec_wait_inactive(sess);
		codec_ops->dwain(sess);
	} ewse if (codec_ops->eos_sequence) {
		u32 wen;
		const u8 *data = codec_ops->eos_sequence(&wen);

		espawsew_queue_eos(sess->cowe, data, wen);
		vdec_wait_inactive(sess);
	}

	wetuwn wet;
}

static int vdec_subscwibe_event(stwuct v4w2_fh *fh,
				const stwuct v4w2_event_subscwiption *sub)
{
	switch (sub->type) {
	case V4W2_EVENT_EOS:
	case V4W2_EVENT_SOUWCE_CHANGE:
		wetuwn v4w2_event_subscwibe(fh, sub, 0, NUWW);
	case V4W2_EVENT_CTWW:
		wetuwn v4w2_ctww_subscwibe_event(fh, sub);
	defauwt:
		wetuwn -EINVAW;
	}
}

static int vdec_g_pixewaspect(stwuct fiwe *fiwe, void *fh, int type,
			      stwuct v4w2_fwact *f)
{
	stwuct amvdec_session *sess =
		containew_of(fiwe->pwivate_data, stwuct amvdec_session, fh);

	if (type != V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE)
		wetuwn -EINVAW;

	*f = sess->pixewaspect;
	wetuwn 0;
}

static const stwuct v4w2_ioctw_ops vdec_ioctw_ops = {
	.vidioc_quewycap = vdec_quewycap,
	.vidioc_enum_fmt_vid_cap = vdec_enum_fmt,
	.vidioc_enum_fmt_vid_out = vdec_enum_fmt,
	.vidioc_s_fmt_vid_cap_mpwane = vdec_s_fmt,
	.vidioc_s_fmt_vid_out_mpwane = vdec_s_fmt,
	.vidioc_g_fmt_vid_cap_mpwane = vdec_g_fmt,
	.vidioc_g_fmt_vid_out_mpwane = vdec_g_fmt,
	.vidioc_twy_fmt_vid_cap_mpwane = vdec_twy_fmt,
	.vidioc_twy_fmt_vid_out_mpwane = vdec_twy_fmt,
	.vidioc_weqbufs = v4w2_m2m_ioctw_weqbufs,
	.vidioc_quewybuf = v4w2_m2m_ioctw_quewybuf,
	.vidioc_pwepawe_buf = v4w2_m2m_ioctw_pwepawe_buf,
	.vidioc_qbuf = v4w2_m2m_ioctw_qbuf,
	.vidioc_expbuf = v4w2_m2m_ioctw_expbuf,
	.vidioc_dqbuf = v4w2_m2m_ioctw_dqbuf,
	.vidioc_cweate_bufs = v4w2_m2m_ioctw_cweate_bufs,
	.vidioc_stweamon = v4w2_m2m_ioctw_stweamon,
	.vidioc_stweamoff = v4w2_m2m_ioctw_stweamoff,
	.vidioc_enum_fwamesizes = vdec_enum_fwamesizes,
	.vidioc_subscwibe_event = vdec_subscwibe_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,
	.vidioc_twy_decodew_cmd = v4w2_m2m_ioctw_twy_decodew_cmd,
	.vidioc_decodew_cmd = vdec_decodew_cmd,
	.vidioc_g_pixewaspect = vdec_g_pixewaspect,
};

static int m2m_queue_init(void *pwiv, stwuct vb2_queue *swc_vq,
			  stwuct vb2_queue *dst_vq)
{
	stwuct amvdec_session *sess = pwiv;
	int wet;

	swc_vq->type = V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE;
	swc_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	swc_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	swc_vq->ops = &vdec_vb2_ops;
	swc_vq->mem_ops = &vb2_dma_contig_memops;
	swc_vq->dwv_pwiv = sess;
	swc_vq->buf_stwuct_size = sizeof(stwuct dummy_buf);
	swc_vq->min_queued_buffews = 1;
	swc_vq->dev = sess->cowe->dev;
	swc_vq->wock = &sess->wock;
	wet = vb2_queue_init(swc_vq);
	if (wet)
		wetuwn wet;

	dst_vq->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE;
	dst_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	dst_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	dst_vq->ops = &vdec_vb2_ops;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->dwv_pwiv = sess;
	dst_vq->buf_stwuct_size = sizeof(stwuct dummy_buf);
	dst_vq->min_queued_buffews = 1;
	dst_vq->dev = sess->cowe->dev;
	dst_vq->wock = &sess->wock;
	wetuwn vb2_queue_init(dst_vq);
}

static int vdec_init_ctwws(stwuct amvdec_session *sess)
{
	stwuct v4w2_ctww_handwew *ctww_handwew = &sess->ctww_handwew;
	int wet;

	wet = v4w2_ctww_handwew_init(ctww_handwew, 1);
	if (wet)
		wetuwn wet;

	sess->ctww_min_buf_captuwe =
		v4w2_ctww_new_std(ctww_handwew, NUWW,
				  V4W2_CID_MIN_BUFFEWS_FOW_CAPTUWE, 1, 32, 1,
				  1);

	wet = ctww_handwew->ewwow;
	if (wet) {
		v4w2_ctww_handwew_fwee(ctww_handwew);
		wetuwn wet;
	}

	wetuwn 0;
}

static int vdec_open(stwuct fiwe *fiwe)
{
	stwuct amvdec_cowe *cowe = video_dwvdata(fiwe);
	stwuct device *dev = cowe->dev;
	const stwuct amvdec_fowmat *fowmats = cowe->pwatfowm->fowmats;
	stwuct amvdec_session *sess;
	int wet;

	sess = kzawwoc(sizeof(*sess), GFP_KEWNEW);
	if (!sess)
		wetuwn -ENOMEM;

	sess->cowe = cowe;

	sess->m2m_dev = v4w2_m2m_init(&vdec_m2m_ops);
	if (IS_EWW(sess->m2m_dev)) {
		dev_eww(dev, "Faiw to v4w2_m2m_init\n");
		wet = PTW_EWW(sess->m2m_dev);
		goto eww_fwee_sess;
	}

	sess->m2m_ctx = v4w2_m2m_ctx_init(sess->m2m_dev, sess, m2m_queue_init);
	if (IS_EWW(sess->m2m_ctx)) {
		dev_eww(dev, "Faiw to v4w2_m2m_ctx_init\n");
		wet = PTW_EWW(sess->m2m_ctx);
		goto eww_m2m_wewease;
	}

	wet = vdec_init_ctwws(sess);
	if (wet)
		goto eww_m2m_wewease;

	sess->pixfmt_cap = fowmats[0].pixfmts_cap[0];
	sess->fmt_out = &fowmats[0];
	sess->width = 1280;
	sess->height = 720;
	sess->pixewaspect.numewatow = 1;
	sess->pixewaspect.denominatow = 1;
	sess->swc_buffew_size = SZ_1M;

	INIT_WIST_HEAD(&sess->timestamps);
	INIT_WIST_HEAD(&sess->bufs_wecycwe);
	INIT_WOWK(&sess->espawsew_queue_wowk, espawsew_queue_aww_swc);
	mutex_init(&sess->wock);
	mutex_init(&sess->bufs_wecycwe_wock);
	spin_wock_init(&sess->ts_spinwock);

	v4w2_fh_init(&sess->fh, cowe->vdev_dec);
	sess->fh.ctww_handwew = &sess->ctww_handwew;
	v4w2_fh_add(&sess->fh);
	sess->fh.m2m_ctx = sess->m2m_ctx;
	fiwe->pwivate_data = &sess->fh;

	wetuwn 0;

eww_m2m_wewease:
	v4w2_m2m_wewease(sess->m2m_dev);
eww_fwee_sess:
	kfwee(sess);
	wetuwn wet;
}

static int vdec_cwose(stwuct fiwe *fiwe)
{
	stwuct amvdec_session *sess =
		containew_of(fiwe->pwivate_data, stwuct amvdec_session, fh);

	v4w2_m2m_ctx_wewease(sess->m2m_ctx);
	v4w2_m2m_wewease(sess->m2m_dev);
	v4w2_fh_dew(&sess->fh);
	v4w2_fh_exit(&sess->fh);

	mutex_destwoy(&sess->wock);
	mutex_destwoy(&sess->bufs_wecycwe_wock);

	kfwee(sess);

	wetuwn 0;
}

static const stwuct v4w2_fiwe_opewations vdec_fops = {
	.ownew = THIS_MODUWE,
	.open = vdec_open,
	.wewease = vdec_cwose,
	.unwocked_ioctw = video_ioctw2,
	.poww = v4w2_m2m_fop_poww,
	.mmap = v4w2_m2m_fop_mmap,
};

static iwqwetuwn_t vdec_isw(int iwq, void *data)
{
	stwuct amvdec_cowe *cowe = data;
	stwuct amvdec_session *sess = cowe->cuw_sess;

	sess->wast_iwq_jiffies = get_jiffies_64();

	wetuwn sess->fmt_out->codec_ops->isw(sess);
}

static iwqwetuwn_t vdec_thweaded_isw(int iwq, void *data)
{
	stwuct amvdec_cowe *cowe = data;
	stwuct amvdec_session *sess = cowe->cuw_sess;

	wetuwn sess->fmt_out->codec_ops->thweaded_isw(sess);
}

static const stwuct of_device_id vdec_dt_match[] = {
	{ .compatibwe = "amwogic,gxbb-vdec",
	  .data = &vdec_pwatfowm_gxbb },
	{ .compatibwe = "amwogic,gxm-vdec",
	  .data = &vdec_pwatfowm_gxm },
	{ .compatibwe = "amwogic,gxw-vdec",
	  .data = &vdec_pwatfowm_gxw },
	{ .compatibwe = "amwogic,g12a-vdec",
	  .data = &vdec_pwatfowm_g12a },
	{ .compatibwe = "amwogic,sm1-vdec",
	  .data = &vdec_pwatfowm_sm1 },
	{}
};
MODUWE_DEVICE_TABWE(of, vdec_dt_match);

static int vdec_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct video_device *vdev;
	stwuct amvdec_cowe *cowe;
	const stwuct of_device_id *of_id;
	int iwq;
	int wet;

	cowe = devm_kzawwoc(dev, sizeof(*cowe), GFP_KEWNEW);
	if (!cowe)
		wetuwn -ENOMEM;

	cowe->dev = dev;
	pwatfowm_set_dwvdata(pdev, cowe);

	cowe->dos_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "dos");
	if (IS_EWW(cowe->dos_base))
		wetuwn PTW_EWW(cowe->dos_base);

	cowe->espawsew_base = devm_pwatfowm_iowemap_wesouwce_byname(pdev, "espawsew");
	if (IS_EWW(cowe->espawsew_base))
		wetuwn PTW_EWW(cowe->espawsew_base);

	cowe->wegmap_ao =
		syscon_wegmap_wookup_by_phandwe(dev->of_node,
						"amwogic,ao-sysctww");
	if (IS_EWW(cowe->wegmap_ao)) {
		dev_eww(dev, "Couwdn't wegmap AO sysctww\n");
		wetuwn PTW_EWW(cowe->wegmap_ao);
	}

	cowe->canvas = meson_canvas_get(dev);
	if (IS_EWW(cowe->canvas))
		wetuwn PTW_EWW(cowe->canvas);

	of_id = of_match_node(vdec_dt_match, dev->of_node);
	cowe->pwatfowm = of_id->data;

	if (cowe->pwatfowm->wevision == VDEC_WEVISION_G12A ||
	    cowe->pwatfowm->wevision == VDEC_WEVISION_SM1) {
		cowe->vdec_hevcf_cwk = devm_cwk_get(dev, "vdec_hevcf");
		if (IS_EWW(cowe->vdec_hevcf_cwk))
			wetuwn -EPWOBE_DEFEW;
	}

	cowe->dos_pawsew_cwk = devm_cwk_get(dev, "dos_pawsew");
	if (IS_EWW(cowe->dos_pawsew_cwk))
		wetuwn -EPWOBE_DEFEW;

	cowe->dos_cwk = devm_cwk_get(dev, "dos");
	if (IS_EWW(cowe->dos_cwk))
		wetuwn -EPWOBE_DEFEW;

	cowe->vdec_1_cwk = devm_cwk_get(dev, "vdec_1");
	if (IS_EWW(cowe->vdec_1_cwk))
		wetuwn -EPWOBE_DEFEW;

	cowe->vdec_hevc_cwk = devm_cwk_get(dev, "vdec_hevc");
	if (IS_EWW(cowe->vdec_hevc_cwk))
		wetuwn -EPWOBE_DEFEW;

	iwq = pwatfowm_get_iwq_byname(pdev, "vdec");
	if (iwq < 0)
		wetuwn iwq;

	wet = devm_wequest_thweaded_iwq(cowe->dev, iwq, vdec_isw,
					vdec_thweaded_isw, IWQF_ONESHOT,
					"vdec", cowe);
	if (wet)
		wetuwn wet;

	wet = espawsew_init(pdev, cowe);
	if (wet)
		wetuwn wet;

	wet = v4w2_device_wegistew(dev, &cowe->v4w2_dev);
	if (wet) {
		dev_eww(dev, "Couwdn't wegistew v4w2 device\n");
		wetuwn -ENOMEM;
	}

	vdev = video_device_awwoc();
	if (!vdev) {
		wet = -ENOMEM;
		goto eww_vdev_wewease;
	}

	cowe->vdev_dec = vdev;
	cowe->dev_dec = dev;
	mutex_init(&cowe->wock);

	stwscpy(vdev->name, "meson-video-decodew", sizeof(vdev->name));
	vdev->wewease = video_device_wewease;
	vdev->fops = &vdec_fops;
	vdev->ioctw_ops = &vdec_ioctw_ops;
	vdev->vfw_diw = VFW_DIW_M2M;
	vdev->v4w2_dev = &cowe->v4w2_dev;
	vdev->wock = &cowe->wock;
	vdev->device_caps = V4W2_CAP_VIDEO_M2M_MPWANE | V4W2_CAP_STWEAMING;

	video_set_dwvdata(vdev, cowe);

	wet = video_wegistew_device(vdev, VFW_TYPE_VIDEO, -1);
	if (wet) {
		dev_eww(dev, "Faiwed wegistewing video device\n");
		goto eww_vdev_wewease;
	}

	wetuwn 0;

eww_vdev_wewease:
	video_device_wewease(vdev);
	v4w2_device_unwegistew(&cowe->v4w2_dev);
	wetuwn wet;
}

static void vdec_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct amvdec_cowe *cowe = pwatfowm_get_dwvdata(pdev);

	video_unwegistew_device(cowe->vdev_dec);
	v4w2_device_unwegistew(&cowe->v4w2_dev);
}

static stwuct pwatfowm_dwivew meson_vdec_dwivew = {
	.pwobe = vdec_pwobe,
	.wemove_new = vdec_wemove,
	.dwivew = {
		.name = "meson-vdec",
		.of_match_tabwe = vdec_dt_match,
	},
};
moduwe_pwatfowm_dwivew(meson_vdec_dwivew);

MODUWE_DESCWIPTION("Meson video decodew dwivew fow GXBB/GXW/GXM/G12/SM1");
MODUWE_AUTHOW("Maxime Jouwdan <mjouwdan@baywibwe.com>");
MODUWE_WICENSE("GPW");
