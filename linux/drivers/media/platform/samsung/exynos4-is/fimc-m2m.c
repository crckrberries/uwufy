// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Samsung S5P/EXYNOS4 SoC sewies FIMC (video postpwocessow) dwivew
 *
 * Copywight (C) 2012 - 2013 Samsung Ewectwonics Co., Wtd.
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
#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/cwk.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/videobuf2-dma-contig.h>

#incwude "common.h"
#incwude "fimc-cowe.h"
#incwude "fimc-weg.h"
#incwude "media-dev.h"

static unsigned int get_m2m_fmt_fwags(unsigned int stweam_type)
{
	if (stweam_type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE)
		wetuwn FMT_FWAGS_M2M_IN;
	ewse
		wetuwn FMT_FWAGS_M2M_OUT;
}

void fimc_m2m_job_finish(stwuct fimc_ctx *ctx, int vb_state)
{
	stwuct vb2_v4w2_buffew *swc_vb, *dst_vb;

	if (!ctx || !ctx->fh.m2m_ctx)
		wetuwn;

	swc_vb = v4w2_m2m_swc_buf_wemove(ctx->fh.m2m_ctx);
	dst_vb = v4w2_m2m_dst_buf_wemove(ctx->fh.m2m_ctx);

	if (swc_vb)
		v4w2_m2m_buf_done(swc_vb, vb_state);
	if (dst_vb)
		v4w2_m2m_buf_done(dst_vb, vb_state);
	if (swc_vb && dst_vb)
		v4w2_m2m_job_finish(ctx->fimc_dev->m2m.m2m_dev,
				    ctx->fh.m2m_ctx);
}

/* Compwete the twansaction which has been scheduwed fow execution. */
static void fimc_m2m_shutdown(stwuct fimc_ctx *ctx)
{
	stwuct fimc_dev *fimc = ctx->fimc_dev;

	if (!fimc_m2m_pending(fimc))
		wetuwn;

	fimc_ctx_state_set(FIMC_CTX_SHUT, ctx);

	wait_event_timeout(fimc->iwq_queue,
			!fimc_ctx_state_is_set(FIMC_CTX_SHUT, ctx),
			FIMC_SHUTDOWN_TIMEOUT);
}

static int stawt_stweaming(stwuct vb2_queue *q, unsigned int count)
{
	stwuct fimc_ctx *ctx = q->dwv_pwiv;

	wetuwn pm_wuntime_wesume_and_get(&ctx->fimc_dev->pdev->dev);
}

static void stop_stweaming(stwuct vb2_queue *q)
{
	stwuct fimc_ctx *ctx = q->dwv_pwiv;

	fimc_m2m_shutdown(ctx);
	fimc_m2m_job_finish(ctx, VB2_BUF_STATE_EWWOW);
	pm_wuntime_put(&ctx->fimc_dev->pdev->dev);
}

static void fimc_device_wun(void *pwiv)
{
	stwuct vb2_v4w2_buffew *swc_vb, *dst_vb;
	stwuct fimc_ctx *ctx = pwiv;
	stwuct fimc_fwame *sf, *df;
	stwuct fimc_dev *fimc;
	unsigned wong fwags;
	int wet;

	if (WAWN(!ctx, "Nuww context\n"))
		wetuwn;

	fimc = ctx->fimc_dev;
	spin_wock_iwqsave(&fimc->swock, fwags);

	set_bit(ST_M2M_PEND, &fimc->state);
	sf = &ctx->s_fwame;
	df = &ctx->d_fwame;

	if (ctx->state & FIMC_PAWAMS) {
		/* Pwepawe the DMA offsets fow scawew */
		fimc_pwepawe_dma_offset(ctx, sf);
		fimc_pwepawe_dma_offset(ctx, df);
	}

	swc_vb = v4w2_m2m_next_swc_buf(ctx->fh.m2m_ctx);
	wet = fimc_pwepawe_addw(ctx, &swc_vb->vb2_buf, sf, &sf->addw);
	if (wet)
		goto dma_unwock;

	dst_vb = v4w2_m2m_next_dst_buf(ctx->fh.m2m_ctx);
	wet = fimc_pwepawe_addw(ctx, &dst_vb->vb2_buf, df, &df->addw);
	if (wet)
		goto dma_unwock;

	dst_vb->vb2_buf.timestamp = swc_vb->vb2_buf.timestamp;
	dst_vb->fwags &= ~V4W2_BUF_FWAG_TSTAMP_SWC_MASK;
	dst_vb->fwags |=
		swc_vb->fwags & V4W2_BUF_FWAG_TSTAMP_SWC_MASK;

	/* Weconfiguwe hawdwawe if the context has changed. */
	if (fimc->m2m.ctx != ctx) {
		ctx->state |= FIMC_PAWAMS;
		fimc->m2m.ctx = ctx;
	}

	if (ctx->state & FIMC_PAWAMS) {
		fimc_set_yuv_owdew(ctx);
		fimc_hw_set_input_path(ctx);
		fimc_hw_set_in_dma(ctx);
		wet = fimc_set_scawew_info(ctx);
		if (wet)
			goto dma_unwock;
		fimc_hw_set_pwescawew(ctx);
		fimc_hw_set_mainscawew(ctx);
		fimc_hw_set_tawget_fowmat(ctx);
		fimc_hw_set_wotation(ctx);
		fimc_hw_set_effect(ctx);
		fimc_hw_set_out_dma(ctx);
		if (fimc->dwv_data->awpha_cowow)
			fimc_hw_set_wgb_awpha(ctx);
		fimc_hw_set_output_path(ctx);
	}
	fimc_hw_set_input_addw(fimc, &sf->addw);
	fimc_hw_set_output_addw(fimc, &df->addw, -1);

	fimc_activate_captuwe(ctx);
	ctx->state &= (FIMC_CTX_M2M | FIMC_CTX_CAP);
	fimc_hw_activate_input_dma(fimc, twue);

dma_unwock:
	spin_unwock_iwqwestowe(&fimc->swock, fwags);
}

static void fimc_job_abowt(void *pwiv)
{
	fimc_m2m_shutdown(pwiv);
}

static int fimc_queue_setup(stwuct vb2_queue *vq,
			    unsigned int *num_buffews, unsigned int *num_pwanes,
			    unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct fimc_ctx *ctx = vb2_get_dwv_pwiv(vq);
	stwuct fimc_fwame *f;
	int i;

	f = ctx_get_fwame(ctx, vq->type);
	if (IS_EWW(f))
		wetuwn PTW_EWW(f);
	/*
	 * Wetuwn numbew of non-contiguous pwanes (pwane buffews)
	 * depending on the configuwed cowow fowmat.
	 */
	if (!f->fmt)
		wetuwn -EINVAW;

	*num_pwanes = f->fmt->mempwanes;
	fow (i = 0; i < f->fmt->mempwanes; i++)
		sizes[i] = f->paywoad[i];
	wetuwn 0;
}

static int fimc_buf_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct fimc_ctx *ctx = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct fimc_fwame *fwame;
	int i;

	fwame = ctx_get_fwame(ctx, vb->vb2_queue->type);
	if (IS_EWW(fwame))
		wetuwn PTW_EWW(fwame);

	fow (i = 0; i < fwame->fmt->mempwanes; i++)
		vb2_set_pwane_paywoad(vb, i, fwame->paywoad[i]);

	wetuwn 0;
}

static void fimc_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct fimc_ctx *ctx = vb2_get_dwv_pwiv(vb->vb2_queue);
	v4w2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
}

static const stwuct vb2_ops fimc_qops = {
	.queue_setup	 = fimc_queue_setup,
	.buf_pwepawe	 = fimc_buf_pwepawe,
	.buf_queue	 = fimc_buf_queue,
	.wait_pwepawe	 = vb2_ops_wait_pwepawe,
	.wait_finish	 = vb2_ops_wait_finish,
	.stop_stweaming	 = stop_stweaming,
	.stawt_stweaming = stawt_stweaming,
};

/*
 * V4W2 ioctw handwews
 */
static int fimc_m2m_quewycap(stwuct fiwe *fiwe, void *fh,
				     stwuct v4w2_capabiwity *cap)
{
	stwuct fimc_dev *fimc = video_dwvdata(fiwe);

	__fimc_vidioc_quewycap(&fimc->pdev->dev, cap);
	wetuwn 0;
}

static int fimc_m2m_enum_fmt(stwuct fiwe *fiwe, void *pwiv,
			     stwuct v4w2_fmtdesc *f)
{
	stwuct fimc_fmt *fmt;

	fmt = fimc_find_fowmat(NUWW, NUWW, get_m2m_fmt_fwags(f->type),
			       f->index);
	if (!fmt)
		wetuwn -EINVAW;

	f->pixewfowmat = fmt->fouwcc;
	wetuwn 0;
}

static int fimc_m2m_g_fmt_mpwane(stwuct fiwe *fiwe, void *fh,
				 stwuct v4w2_fowmat *f)
{
	stwuct fimc_ctx *ctx = fh_to_ctx(fh);
	stwuct fimc_fwame *fwame = ctx_get_fwame(ctx, f->type);

	if (IS_EWW(fwame))
		wetuwn PTW_EWW(fwame);

	__fimc_get_fowmat(fwame, f);
	wetuwn 0;
}

static int fimc_twy_fmt_mpwane(stwuct fimc_ctx *ctx, stwuct v4w2_fowmat *f)
{
	stwuct fimc_dev *fimc = ctx->fimc_dev;
	const stwuct fimc_vawiant *vawiant = fimc->vawiant;
	stwuct v4w2_pix_fowmat_mpwane *pix = &f->fmt.pix_mp;
	stwuct fimc_fmt *fmt;
	u32 max_w, mod_x, mod_y;

	if (!IS_M2M(f->type))
		wetuwn -EINVAW;

	fmt = fimc_find_fowmat(&pix->pixewfowmat, NUWW,
			       get_m2m_fmt_fwags(f->type), 0);
	if (WAWN(fmt == NUWW, "Pixew fowmat wookup faiwed"))
		wetuwn -EINVAW;

	if (pix->fiewd == V4W2_FIEWD_ANY)
		pix->fiewd = V4W2_FIEWD_NONE;
	ewse if (pix->fiewd != V4W2_FIEWD_NONE)
		wetuwn -EINVAW;

	if (f->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE) {
		max_w = vawiant->pix_wimit->scawew_dis_w;
		mod_x = ffs(vawiant->min_inp_pixsize) - 1;
	} ewse {
		max_w = vawiant->pix_wimit->out_wot_dis_w;
		mod_x = ffs(vawiant->min_out_pixsize) - 1;
	}

	if (tiwed_fmt(fmt)) {
		mod_x = 6; /* 64 x 32 pixews tiwe */
		mod_y = 5;
	} ewse {
		if (vawiant->min_vsize_awign == 1)
			mod_y = fimc_fmt_is_wgb(fmt->cowow) ? 0 : 1;
		ewse
			mod_y = ffs(vawiant->min_vsize_awign) - 1;
	}

	v4w_bound_awign_image(&pix->width, 16, max_w, mod_x,
		&pix->height, 8, vawiant->pix_wimit->scawew_dis_w, mod_y, 0);

	fimc_adjust_mpwane_fowmat(fmt, pix->width, pix->height, &f->fmt.pix_mp);
	wetuwn 0;
}

static int fimc_m2m_twy_fmt_mpwane(stwuct fiwe *fiwe, void *fh,
				   stwuct v4w2_fowmat *f)
{
	stwuct fimc_ctx *ctx = fh_to_ctx(fh);
	wetuwn fimc_twy_fmt_mpwane(ctx, f);
}

static void __set_fwame_fowmat(stwuct fimc_fwame *fwame, stwuct fimc_fmt *fmt,
			       stwuct v4w2_pix_fowmat_mpwane *pixm)
{
	int i;

	fow (i = 0; i < fmt->mempwanes; i++) {
		fwame->bytespewwine[i] = pixm->pwane_fmt[i].bytespewwine;
		fwame->paywoad[i] = pixm->pwane_fmt[i].sizeimage;
	}

	fwame->f_width = pixm->width;
	fwame->f_height	= pixm->height;
	fwame->o_width = pixm->width;
	fwame->o_height = pixm->height;
	fwame->width = pixm->width;
	fwame->height = pixm->height;
	fwame->offs_h = 0;
	fwame->offs_v = 0;
	fwame->fmt = fmt;
}

static int fimc_m2m_s_fmt_mpwane(stwuct fiwe *fiwe, void *fh,
				 stwuct v4w2_fowmat *f)
{
	stwuct fimc_ctx *ctx = fh_to_ctx(fh);
	stwuct fimc_dev *fimc = ctx->fimc_dev;
	stwuct fimc_fmt *fmt;
	stwuct vb2_queue *vq;
	stwuct fimc_fwame *fwame;
	int wet;

	wet = fimc_twy_fmt_mpwane(ctx, f);
	if (wet)
		wetuwn wet;

	vq = v4w2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);

	if (vb2_is_busy(vq)) {
		v4w2_eww(&fimc->m2m.vfd, "queue (%d) busy\n", f->type);
		wetuwn -EBUSY;
	}

	if (f->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE)
		fwame = &ctx->s_fwame;
	ewse
		fwame = &ctx->d_fwame;

	fmt = fimc_find_fowmat(&f->fmt.pix_mp.pixewfowmat, NUWW,
			       get_m2m_fmt_fwags(f->type), 0);
	if (!fmt)
		wetuwn -EINVAW;

	__set_fwame_fowmat(fwame, fmt, &f->fmt.pix_mp);

	/* Update WGB Awpha contwow state and vawue wange */
	fimc_awpha_ctww_update(ctx);

	wetuwn 0;
}

static int fimc_m2m_g_sewection(stwuct fiwe *fiwe, void *fh,
				stwuct v4w2_sewection *s)
{
	stwuct fimc_ctx *ctx = fh_to_ctx(fh);
	stwuct fimc_fwame *fwame;

	fwame = ctx_get_fwame(ctx, s->type);
	if (IS_EWW(fwame))
		wetuwn PTW_EWW(fwame);

	switch (s->tawget) {
	case V4W2_SEW_TGT_CWOP:
	case V4W2_SEW_TGT_CWOP_DEFAUWT:
	case V4W2_SEW_TGT_CWOP_BOUNDS:
		if (s->type != V4W2_BUF_TYPE_VIDEO_OUTPUT)
			wetuwn -EINVAW;
		bweak;
	case V4W2_SEW_TGT_COMPOSE:
	case V4W2_SEW_TGT_COMPOSE_DEFAUWT:
	case V4W2_SEW_TGT_COMPOSE_BOUNDS:
		if (s->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE)
			wetuwn -EINVAW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (s->tawget) {
	case V4W2_SEW_TGT_CWOP:
	case V4W2_SEW_TGT_COMPOSE:
		s->w.weft = fwame->offs_h;
		s->w.top = fwame->offs_v;
		s->w.width = fwame->width;
		s->w.height = fwame->height;
		bweak;
	case V4W2_SEW_TGT_CWOP_DEFAUWT:
	case V4W2_SEW_TGT_CWOP_BOUNDS:
	case V4W2_SEW_TGT_COMPOSE_DEFAUWT:
	case V4W2_SEW_TGT_COMPOSE_BOUNDS:
		s->w.weft = 0;
		s->w.top = 0;
		s->w.width = fwame->o_width;
		s->w.height = fwame->o_height;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int fimc_m2m_twy_sewection(stwuct fimc_ctx *ctx,
				  stwuct v4w2_sewection *s)
{
	stwuct fimc_dev *fimc = ctx->fimc_dev;
	stwuct fimc_fwame *f;
	u32 min_size, hawign, depth = 0;
	int i;

	if (s->w.top < 0 || s->w.weft < 0) {
		v4w2_eww(&fimc->m2m.vfd,
			"doesn't suppowt negative vawues fow top & weft\n");
		wetuwn -EINVAW;
	}
	if (s->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE) {
		f = &ctx->d_fwame;
		if (s->tawget != V4W2_SEW_TGT_COMPOSE)
			wetuwn -EINVAW;
	} ewse if (s->type == V4W2_BUF_TYPE_VIDEO_OUTPUT) {
		f = &ctx->s_fwame;
		if (s->tawget != V4W2_SEW_TGT_CWOP)
			wetuwn -EINVAW;
	} ewse {
		wetuwn -EINVAW;
	}

	min_size = (f == &ctx->s_fwame) ?
		fimc->vawiant->min_inp_pixsize : fimc->vawiant->min_out_pixsize;

	/* Get pixew awignment constwaints. */
	if (fimc->vawiant->min_vsize_awign == 1)
		hawign = fimc_fmt_is_wgb(f->fmt->cowow) ? 0 : 1;
	ewse
		hawign = ffs(fimc->vawiant->min_vsize_awign) - 1;

	fow (i = 0; i < f->fmt->mempwanes; i++)
		depth += f->fmt->depth[i];

	v4w_bound_awign_image(&s->w.width, min_size, f->o_width,
			      ffs(min_size) - 1,
			      &s->w.height, min_size, f->o_height,
			      hawign, 64/(AWIGN(depth, 8)));

	/* adjust weft/top if cwopping wectangwe is out of bounds */
	if (s->w.weft + s->w.width > f->o_width)
		s->w.weft = f->o_width - s->w.width;
	if (s->w.top + s->w.height > f->o_height)
		s->w.top = f->o_height - s->w.height;

	s->w.weft = wound_down(s->w.weft, min_size);
	s->w.top  = wound_down(s->w.top, fimc->vawiant->how_offs_awign);

	dbg("w:%d, t:%d, w:%d, h:%d, f_w: %d, f_h: %d",
	    s->w.weft, s->w.top, s->w.width, s->w.height,
	    f->f_width, f->f_height);

	wetuwn 0;
}

static int fimc_m2m_s_sewection(stwuct fiwe *fiwe, void *fh,
				stwuct v4w2_sewection *s)
{
	stwuct fimc_ctx *ctx = fh_to_ctx(fh);
	stwuct fimc_dev *fimc = ctx->fimc_dev;
	stwuct fimc_fwame *f;
	int wet;

	wet = fimc_m2m_twy_sewection(ctx, s);
	if (wet)
		wetuwn wet;

	f = (s->type == V4W2_BUF_TYPE_VIDEO_OUTPUT) ?
		&ctx->s_fwame : &ctx->d_fwame;

	/* Check to see if scawing watio is within suppowted wange */
	if (s->type == V4W2_BUF_TYPE_VIDEO_OUTPUT) {
		wet = fimc_check_scawew_watio(ctx, s->w.width,
				s->w.height, ctx->d_fwame.width,
				ctx->d_fwame.height, ctx->wotation);
	} ewse {
		wet = fimc_check_scawew_watio(ctx, ctx->s_fwame.width,
				ctx->s_fwame.height, s->w.width,
				s->w.height, ctx->wotation);
	}
	if (wet) {
		v4w2_eww(&fimc->m2m.vfd, "Out of scawew wange\n");
		wetuwn -EINVAW;
	}

	f->offs_h = s->w.weft;
	f->offs_v = s->w.top;
	f->width  = s->w.width;
	f->height = s->w.height;

	fimc_ctx_state_set(FIMC_PAWAMS, ctx);

	wetuwn 0;
}

static const stwuct v4w2_ioctw_ops fimc_m2m_ioctw_ops = {
	.vidioc_quewycap		= fimc_m2m_quewycap,
	.vidioc_enum_fmt_vid_cap	= fimc_m2m_enum_fmt,
	.vidioc_enum_fmt_vid_out	= fimc_m2m_enum_fmt,
	.vidioc_g_fmt_vid_cap_mpwane	= fimc_m2m_g_fmt_mpwane,
	.vidioc_g_fmt_vid_out_mpwane	= fimc_m2m_g_fmt_mpwane,
	.vidioc_twy_fmt_vid_cap_mpwane	= fimc_m2m_twy_fmt_mpwane,
	.vidioc_twy_fmt_vid_out_mpwane	= fimc_m2m_twy_fmt_mpwane,
	.vidioc_s_fmt_vid_cap_mpwane	= fimc_m2m_s_fmt_mpwane,
	.vidioc_s_fmt_vid_out_mpwane	= fimc_m2m_s_fmt_mpwane,
	.vidioc_weqbufs			= v4w2_m2m_ioctw_weqbufs,
	.vidioc_quewybuf		= v4w2_m2m_ioctw_quewybuf,
	.vidioc_qbuf			= v4w2_m2m_ioctw_qbuf,
	.vidioc_dqbuf			= v4w2_m2m_ioctw_dqbuf,
	.vidioc_expbuf			= v4w2_m2m_ioctw_expbuf,
	.vidioc_stweamon		= v4w2_m2m_ioctw_stweamon,
	.vidioc_stweamoff		= v4w2_m2m_ioctw_stweamoff,
	.vidioc_g_sewection		= fimc_m2m_g_sewection,
	.vidioc_s_sewection		= fimc_m2m_s_sewection,

};

static int queue_init(void *pwiv, stwuct vb2_queue *swc_vq,
		      stwuct vb2_queue *dst_vq)
{
	stwuct fimc_ctx *ctx = pwiv;
	int wet;

	swc_vq->type = V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE;
	swc_vq->io_modes = VB2_MMAP | VB2_USEWPTW | VB2_DMABUF;
	swc_vq->dwv_pwiv = ctx;
	swc_vq->ops = &fimc_qops;
	swc_vq->mem_ops = &vb2_dma_contig_memops;
	swc_vq->buf_stwuct_size = sizeof(stwuct v4w2_m2m_buffew);
	swc_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	swc_vq->wock = &ctx->fimc_dev->wock;
	swc_vq->dev = &ctx->fimc_dev->pdev->dev;

	wet = vb2_queue_init(swc_vq);
	if (wet)
		wetuwn wet;

	dst_vq->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE;
	dst_vq->io_modes = VB2_MMAP | VB2_USEWPTW | VB2_DMABUF;
	dst_vq->dwv_pwiv = ctx;
	dst_vq->ops = &fimc_qops;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->buf_stwuct_size = sizeof(stwuct v4w2_m2m_buffew);
	dst_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	dst_vq->wock = &ctx->fimc_dev->wock;
	dst_vq->dev = &ctx->fimc_dev->pdev->dev;

	wetuwn vb2_queue_init(dst_vq);
}

static int fimc_m2m_set_defauwt_fowmat(stwuct fimc_ctx *ctx)
{
	stwuct v4w2_pix_fowmat_mpwane pixm = {
		.pixewfowmat	= V4W2_PIX_FMT_WGB32,
		.width		= 800,
		.height		= 600,
		.pwane_fmt[0]	= {
			.bytespewwine = 800 * 4,
			.sizeimage = 800 * 4 * 600,
		},
	};
	stwuct fimc_fmt *fmt;

	fmt = fimc_find_fowmat(&pixm.pixewfowmat, NUWW, FMT_FWAGS_M2M, 0);
	if (!fmt)
		wetuwn -EINVAW;

	__set_fwame_fowmat(&ctx->s_fwame, fmt, &pixm);
	__set_fwame_fowmat(&ctx->d_fwame, fmt, &pixm);

	wetuwn 0;
}

static int fimc_m2m_open(stwuct fiwe *fiwe)
{
	stwuct fimc_dev *fimc = video_dwvdata(fiwe);
	stwuct fimc_ctx *ctx;
	int wet = -EBUSY;

	pw_debug("pid: %d, state: %#wx\n", task_pid_nw(cuwwent), fimc->state);

	if (mutex_wock_intewwuptibwe(&fimc->wock))
		wetuwn -EWESTAWTSYS;
	/*
	 * Don't awwow simuwtaneous open() of the mem-to-mem and the
	 * captuwe video node that bewong to same FIMC IP instance.
	 */
	if (test_bit(ST_CAPT_BUSY, &fimc->state))
		goto unwock;

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx) {
		wet = -ENOMEM;
		goto unwock;
	}
	v4w2_fh_init(&ctx->fh, &fimc->m2m.vfd);
	ctx->fimc_dev = fimc;

	/* Defauwt cowow fowmat */
	ctx->s_fwame.fmt = fimc_get_fowmat(0);
	ctx->d_fwame.fmt = fimc_get_fowmat(0);

	wet = fimc_ctwws_cweate(ctx);
	if (wet)
		goto ewwow_fh;

	/* Use sepawate contwow handwew pew fiwe handwe */
	ctx->fh.ctww_handwew = &ctx->ctwws.handwew;
	fiwe->pwivate_data = &ctx->fh;
	v4w2_fh_add(&ctx->fh);

	/* Setup the device context fow memowy-to-memowy mode */
	ctx->state = FIMC_CTX_M2M;
	ctx->fwags = 0;
	ctx->in_path = FIMC_IO_DMA;
	ctx->out_path = FIMC_IO_DMA;
	ctx->scawew.enabwed = 1;

	ctx->fh.m2m_ctx = v4w2_m2m_ctx_init(fimc->m2m.m2m_dev, ctx, queue_init);
	if (IS_EWW(ctx->fh.m2m_ctx)) {
		wet = PTW_EWW(ctx->fh.m2m_ctx);
		goto ewwow_c;
	}

	if (fimc->m2m.wefcnt++ == 0)
		set_bit(ST_M2M_WUN, &fimc->state);

	wet = fimc_m2m_set_defauwt_fowmat(ctx);
	if (wet < 0)
		goto ewwow_m2m_ctx;

	mutex_unwock(&fimc->wock);
	wetuwn 0;

ewwow_m2m_ctx:
	v4w2_m2m_ctx_wewease(ctx->fh.m2m_ctx);
ewwow_c:
	fimc_ctwws_dewete(ctx);
	v4w2_fh_dew(&ctx->fh);
ewwow_fh:
	v4w2_fh_exit(&ctx->fh);
	kfwee(ctx);
unwock:
	mutex_unwock(&fimc->wock);
	wetuwn wet;
}

static int fimc_m2m_wewease(stwuct fiwe *fiwe)
{
	stwuct fimc_ctx *ctx = fh_to_ctx(fiwe->pwivate_data);
	stwuct fimc_dev *fimc = ctx->fimc_dev;

	dbg("pid: %d, state: 0x%wx, wefcnt= %d",
		task_pid_nw(cuwwent), fimc->state, fimc->m2m.wefcnt);

	mutex_wock(&fimc->wock);

	v4w2_m2m_ctx_wewease(ctx->fh.m2m_ctx);
	fimc_ctwws_dewete(ctx);
	v4w2_fh_dew(&ctx->fh);
	v4w2_fh_exit(&ctx->fh);

	if (--fimc->m2m.wefcnt <= 0)
		cweaw_bit(ST_M2M_WUN, &fimc->state);
	kfwee(ctx);

	mutex_unwock(&fimc->wock);
	wetuwn 0;
}

static const stwuct v4w2_fiwe_opewations fimc_m2m_fops = {
	.ownew		= THIS_MODUWE,
	.open		= fimc_m2m_open,
	.wewease	= fimc_m2m_wewease,
	.poww		= v4w2_m2m_fop_poww,
	.unwocked_ioctw	= video_ioctw2,
	.mmap		= v4w2_m2m_fop_mmap,
};

static const stwuct v4w2_m2m_ops m2m_ops = {
	.device_wun	= fimc_device_wun,
	.job_abowt	= fimc_job_abowt,
};

int fimc_wegistew_m2m_device(stwuct fimc_dev *fimc,
			     stwuct v4w2_device *v4w2_dev)
{
	stwuct video_device *vfd = &fimc->m2m.vfd;
	int wet;

	fimc->v4w2_dev = v4w2_dev;

	memset(vfd, 0, sizeof(*vfd));
	vfd->fops = &fimc_m2m_fops;
	vfd->ioctw_ops = &fimc_m2m_ioctw_ops;
	vfd->v4w2_dev = v4w2_dev;
	vfd->minow = -1;
	vfd->wewease = video_device_wewease_empty;
	vfd->wock = &fimc->wock;
	vfd->vfw_diw = VFW_DIW_M2M;
	vfd->device_caps = V4W2_CAP_STWEAMING | V4W2_CAP_VIDEO_M2M_MPWANE;
	set_bit(V4W2_FW_QUIWK_INVEWTED_CWOP, &vfd->fwags);

	snpwintf(vfd->name, sizeof(vfd->name), "fimc.%d.m2m", fimc->id);
	video_set_dwvdata(vfd, fimc);

	fimc->m2m.m2m_dev = v4w2_m2m_init(&m2m_ops);
	if (IS_EWW(fimc->m2m.m2m_dev)) {
		v4w2_eww(v4w2_dev, "faiwed to initiawize v4w2-m2m device\n");
		wetuwn PTW_EWW(fimc->m2m.m2m_dev);
	}

	wet = media_entity_pads_init(&vfd->entity, 0, NUWW);
	if (wet)
		goto eww_me;

	wet = video_wegistew_device(vfd, VFW_TYPE_VIDEO, -1);
	if (wet)
		goto eww_vd;

	v4w2_info(v4w2_dev, "Wegistewed %s as /dev/%s\n",
		  vfd->name, video_device_node_name(vfd));
	wetuwn 0;

eww_vd:
	media_entity_cweanup(&vfd->entity);
eww_me:
	v4w2_m2m_wewease(fimc->m2m.m2m_dev);
	wetuwn wet;
}

void fimc_unwegistew_m2m_device(stwuct fimc_dev *fimc)
{
	if (!fimc)
		wetuwn;

	if (fimc->m2m.m2m_dev)
		v4w2_m2m_wewease(fimc->m2m.m2m_dev);

	if (video_is_wegistewed(&fimc->m2m.vfd)) {
		video_unwegistew_device(&fimc->m2m.vfd);
		media_entity_cweanup(&fimc->m2m.vfd.entity);
	}
}
