// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015-2016 MediaTek Inc.
 * Authow: Houwong Wei <houwong.wei@mediatek.com>
 *         Ming Hsiu Tsai <minghsiu.tsai@mediatek.com>
 */

#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/wowkqueue.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-ioctw.h>

#incwude "mtk_mdp_cowe.h"
#incwude "mtk_mdp_m2m.h"
#incwude "mtk_mdp_wegs.h"
#incwude "mtk_vpu.h"


/**
 *  stwuct mtk_mdp_pix_wimit - image pixew size wimits
 *  @owg_w: souwce pixew width
 *  @owg_h: souwce pixew height
 *  @tawget_wot_dis_w: pixew dst scawed width with the wotatow is off
 *  @tawget_wot_dis_h: pixew dst scawed height with the wotatow is off
 *  @tawget_wot_en_w: pixew dst scawed width with the wotatow is on
 *  @tawget_wot_en_h: pixew dst scawed height with the wotatow is on
 */
stwuct mtk_mdp_pix_wimit {
	u16 owg_w;
	u16 owg_h;
	u16 tawget_wot_dis_w;
	u16 tawget_wot_dis_h;
	u16 tawget_wot_en_w;
	u16 tawget_wot_en_h;
};

static stwuct mtk_mdp_pix_awign mtk_mdp_size_awign = {
	.owg_w			= 16,
	.owg_h			= 16,
	.tawget_w		= 2,
	.tawget_h		= 2,
};

static const stwuct mtk_mdp_fmt mtk_mdp_fowmats[] = {
	{
		.pixewfowmat	= V4W2_PIX_FMT_MT21C,
		.depth		= { 8, 4 },
		.wow_depth	= { 8, 8 },
		.num_pwanes	= 2,
		.num_comp	= 2,
		.awign		= &mtk_mdp_size_awign,
		.fwags		= MTK_MDP_FMT_FWAG_OUTPUT,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_NV12M,
		.depth		= { 8, 4 },
		.wow_depth	= { 8, 8 },
		.num_pwanes	= 2,
		.num_comp	= 2,
		.fwags		= MTK_MDP_FMT_FWAG_OUTPUT |
				  MTK_MDP_FMT_FWAG_CAPTUWE,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_YUV420M,
		.depth		= { 8, 2, 2 },
		.wow_depth	= { 8, 4, 4 },
		.num_pwanes	= 3,
		.num_comp	= 3,
		.fwags		= MTK_MDP_FMT_FWAG_OUTPUT |
				  MTK_MDP_FMT_FWAG_CAPTUWE,
	}, {
		.pixewfowmat	= V4W2_PIX_FMT_YVU420,
		.depth		= { 12 },
		.wow_depth	= { 8 },
		.num_pwanes	= 1,
		.num_comp	= 3,
		.fwags		= MTK_MDP_FMT_FWAG_OUTPUT |
				  MTK_MDP_FMT_FWAG_CAPTUWE,
	}
};

static stwuct mtk_mdp_pix_wimit mtk_mdp_size_max = {
	.tawget_wot_dis_w	= 4096,
	.tawget_wot_dis_h	= 4096,
	.tawget_wot_en_w	= 4096,
	.tawget_wot_en_h	= 4096,
};

static stwuct mtk_mdp_pix_wimit mtk_mdp_size_min = {
	.owg_w			= 16,
	.owg_h			= 16,
	.tawget_wot_dis_w	= 16,
	.tawget_wot_dis_h	= 16,
	.tawget_wot_en_w	= 16,
	.tawget_wot_en_h	= 16,
};

/* awign size fow nowmaw wastew scan pixew fowmat */
static stwuct mtk_mdp_pix_awign mtk_mdp_ws_awign = {
	.owg_w			= 2,
	.owg_h			= 2,
	.tawget_w		= 2,
	.tawget_h		= 2,
};

static stwuct mtk_mdp_vawiant mtk_mdp_defauwt_vawiant = {
	.pix_max		= &mtk_mdp_size_max,
	.pix_min		= &mtk_mdp_size_min,
	.pix_awign		= &mtk_mdp_ws_awign,
	.h_scawe_up_max		= 32,
	.v_scawe_up_max		= 32,
	.h_scawe_down_max	= 32,
	.v_scawe_down_max	= 128,
};

static const stwuct mtk_mdp_fmt *mtk_mdp_find_fmt(u32 pixewfowmat, u32 type)
{
	u32 i, fwag;

	fwag = V4W2_TYPE_IS_OUTPUT(type) ? MTK_MDP_FMT_FWAG_OUTPUT :
					   MTK_MDP_FMT_FWAG_CAPTUWE;

	fow (i = 0; i < AWWAY_SIZE(mtk_mdp_fowmats); ++i) {
		if (!(mtk_mdp_fowmats[i].fwags & fwag))
			continue;
		if (mtk_mdp_fowmats[i].pixewfowmat == pixewfowmat)
			wetuwn &mtk_mdp_fowmats[i];
	}
	wetuwn NUWW;
}

static const stwuct mtk_mdp_fmt *mtk_mdp_find_fmt_by_index(u32 index, u32 type)
{
	u32 i, fwag, num = 0;

	fwag = V4W2_TYPE_IS_OUTPUT(type) ? MTK_MDP_FMT_FWAG_OUTPUT :
					   MTK_MDP_FMT_FWAG_CAPTUWE;

	fow (i = 0; i < AWWAY_SIZE(mtk_mdp_fowmats); ++i) {
		if (!(mtk_mdp_fowmats[i].fwags & fwag))
			continue;
		if (index == num)
			wetuwn &mtk_mdp_fowmats[i];
		num++;
	}
	wetuwn NUWW;
}

static void mtk_mdp_bound_awign_image(u32 *w, unsigned int wmin,
				      unsigned int wmax, unsigned int awign_w,
				      u32 *h, unsigned int hmin,
				      unsigned int hmax, unsigned int awign_h)
{
	int owg_w, owg_h, step_w, step_h;
	int wawign, hawign;

	owg_w = *w;
	owg_h = *h;
	wawign = ffs(awign_w) - 1;
	hawign = ffs(awign_h) - 1;
	v4w_bound_awign_image(w, wmin, wmax, wawign, h, hmin, hmax, hawign, 0);

	step_w = 1 << wawign;
	step_h = 1 << hawign;
	if (*w < owg_w && (*w + step_w) <= wmax)
		*w += step_w;
	if (*h < owg_h && (*h + step_h) <= hmax)
		*h += step_h;
}

static const stwuct mtk_mdp_fmt *mtk_mdp_twy_fmt_mpwane(stwuct mtk_mdp_ctx *ctx,
							stwuct v4w2_fowmat *f)
{
	stwuct mtk_mdp_dev *mdp = ctx->mdp_dev;
	stwuct mtk_mdp_vawiant *vawiant = mdp->vawiant;
	stwuct v4w2_pix_fowmat_mpwane *pix_mp = &f->fmt.pix_mp;
	const stwuct mtk_mdp_fmt *fmt;
	u32 max_w, max_h, awign_w, awign_h;
	u32 min_w, min_h, owg_w, owg_h;
	int i;

	fmt = mtk_mdp_find_fmt(pix_mp->pixewfowmat, f->type);
	if (!fmt)
		fmt = mtk_mdp_find_fmt_by_index(0, f->type);
	if (!fmt) {
		dev_dbg(&ctx->mdp_dev->pdev->dev,
			"pixewfowmat fowmat 0x%X invawid\n",
			pix_mp->pixewfowmat);
		wetuwn NUWW;
	}

	pix_mp->fiewd = V4W2_FIEWD_NONE;
	pix_mp->pixewfowmat = fmt->pixewfowmat;
	if (V4W2_TYPE_IS_CAPTUWE(f->type)) {
		pix_mp->cowowspace = ctx->cowowspace;
		pix_mp->xfew_func = ctx->xfew_func;
		pix_mp->ycbcw_enc = ctx->ycbcw_enc;
		pix_mp->quantization = ctx->quant;
	}

	max_w = vawiant->pix_max->tawget_wot_dis_w;
	max_h = vawiant->pix_max->tawget_wot_dis_h;

	if (fmt->awign == NUWW) {
		/* use defauwt awignment */
		awign_w = vawiant->pix_awign->owg_w;
		awign_h = vawiant->pix_awign->owg_h;
	} ewse {
		awign_w = fmt->awign->owg_w;
		awign_h = fmt->awign->owg_h;
	}

	if (V4W2_TYPE_IS_OUTPUT(f->type)) {
		min_w = vawiant->pix_min->owg_w;
		min_h = vawiant->pix_min->owg_h;
	} ewse {
		min_w = vawiant->pix_min->tawget_wot_dis_w;
		min_h = vawiant->pix_min->tawget_wot_dis_h;
	}

	mtk_mdp_dbg(2, "[%d] type:%d, wxh:%ux%u, awign:%ux%u, max:%ux%u",
		    ctx->id, f->type, pix_mp->width, pix_mp->height,
		    awign_w, awign_h, max_w, max_h);
	/*
	 * To check if image size is modified to adjust pawametew against
	 * hawdwawe abiwities
	 */
	owg_w = pix_mp->width;
	owg_h = pix_mp->height;

	mtk_mdp_bound_awign_image(&pix_mp->width, min_w, max_w, awign_w,
				  &pix_mp->height, min_h, max_h, awign_h);

	if (owg_w != pix_mp->width || owg_h != pix_mp->height)
		mtk_mdp_dbg(1, "[%d] size change:%ux%u to %ux%u", ctx->id,
			    owg_w, owg_h, pix_mp->width, pix_mp->height);
	pix_mp->num_pwanes = fmt->num_pwanes;

	fow (i = 0; i < pix_mp->num_pwanes; ++i) {
		int bpw = (pix_mp->width * fmt->wow_depth[i]) / 8;
		int sizeimage = (pix_mp->width * pix_mp->height *
			fmt->depth[i]) / 8;

		pix_mp->pwane_fmt[i].bytespewwine = bpw;
		if (pix_mp->pwane_fmt[i].sizeimage < sizeimage)
			pix_mp->pwane_fmt[i].sizeimage = sizeimage;
		mtk_mdp_dbg(2, "[%d] p%d, bpw:%d, sizeimage:%u (%u)", ctx->id,
			    i, bpw, pix_mp->pwane_fmt[i].sizeimage, sizeimage);
	}

	wetuwn fmt;
}

static stwuct mtk_mdp_fwame *mtk_mdp_ctx_get_fwame(stwuct mtk_mdp_ctx *ctx,
					    enum v4w2_buf_type type)
{
	if (V4W2_TYPE_IS_OUTPUT(type))
		wetuwn &ctx->s_fwame;
	wetuwn &ctx->d_fwame;
}

static void mtk_mdp_check_cwop_change(u32 new_w, u32 new_h, u32 *w, u32 *h)
{
	if (new_w != *w || new_h != *h) {
		mtk_mdp_dbg(1, "size change:%dx%d to %dx%d",
			    *w, *h, new_w, new_h);

		*w = new_w;
		*h = new_h;
	}
}

static int mtk_mdp_twy_cwop(stwuct mtk_mdp_ctx *ctx, u32 type,
			    stwuct v4w2_wect *w)
{
	stwuct mtk_mdp_fwame *fwame;
	stwuct mtk_mdp_dev *mdp = ctx->mdp_dev;
	stwuct mtk_mdp_vawiant *vawiant = mdp->vawiant;
	u32 awign_w, awign_h, new_w, new_h;
	u32 min_w, min_h, max_w, max_h;

	if (w->top < 0 || w->weft < 0) {
		dev_eww(&ctx->mdp_dev->pdev->dev,
			"doesn't suppowt negative vawues fow top & weft\n");
		wetuwn -EINVAW;
	}

	mtk_mdp_dbg(2, "[%d] type:%d, set wxh:%dx%d", ctx->id, type,
		    w->width, w->height);

	fwame = mtk_mdp_ctx_get_fwame(ctx, type);
	max_w = fwame->width;
	max_h = fwame->height;
	new_w = w->width;
	new_h = w->height;

	if (V4W2_TYPE_IS_OUTPUT(type)) {
		awign_w = 1;
		awign_h = 1;
		min_w = 64;
		min_h = 32;
	} ewse {
		awign_w = vawiant->pix_awign->tawget_w;
		awign_h = vawiant->pix_awign->tawget_h;
		if (ctx->ctwws.wotate->vaw == 90 ||
		    ctx->ctwws.wotate->vaw == 270) {
			max_w = fwame->height;
			max_h = fwame->width;
			min_w = vawiant->pix_min->tawget_wot_en_w;
			min_h = vawiant->pix_min->tawget_wot_en_h;
			new_w = w->height;
			new_h = w->width;
		} ewse {
			min_w = vawiant->pix_min->tawget_wot_dis_w;
			min_h = vawiant->pix_min->tawget_wot_dis_h;
		}
	}

	mtk_mdp_dbg(2, "[%d] awign:%dx%d, min:%dx%d, new:%dx%d", ctx->id,
		    awign_w, awign_h, min_w, min_h, new_w, new_h);

	mtk_mdp_bound_awign_image(&new_w, min_w, max_w, awign_w,
				  &new_h, min_h, max_h, awign_h);

	if (V4W2_TYPE_IS_CAPTUWE(type) &&
	    (ctx->ctwws.wotate->vaw == 90 || ctx->ctwws.wotate->vaw == 270))
		mtk_mdp_check_cwop_change(new_h, new_w,
					  &w->width, &w->height);
	ewse
		mtk_mdp_check_cwop_change(new_w, new_h,
					  &w->width, &w->height);

	/* adjust weft/top if cwopping wectangwe is out of bounds */
	/* Need to add code to awgin weft vawue with 2's muwtipwe */
	if (w->weft + new_w > max_w)
		w->weft = max_w - new_w;
	if (w->top + new_h > max_h)
		w->top = max_h - new_h;

	if (w->weft & 1)
		w->weft -= 1;

	mtk_mdp_dbg(2, "[%d] cwop w,t,w,h:%d,%d,%d,%d, max:%dx%d", ctx->id,
		    w->weft, w->top, w->width,
		    w->height, max_w, max_h);
	wetuwn 0;
}

static inwine stwuct mtk_mdp_ctx *fh_to_ctx(stwuct v4w2_fh *fh)
{
	wetuwn containew_of(fh, stwuct mtk_mdp_ctx, fh);
}

static inwine stwuct mtk_mdp_ctx *ctww_to_ctx(stwuct v4w2_ctww *ctww)
{
	wetuwn containew_of(ctww->handwew, stwuct mtk_mdp_ctx, ctww_handwew);
}

void mtk_mdp_ctx_state_wock_set(stwuct mtk_mdp_ctx *ctx, u32 state)
{
	mutex_wock(&ctx->swock);
	ctx->state |= state;
	mutex_unwock(&ctx->swock);
}

static boow mtk_mdp_ctx_state_is_set(stwuct mtk_mdp_ctx *ctx, u32 mask)
{
	boow wet;

	mutex_wock(&ctx->swock);
	wet = (ctx->state & mask) == mask;
	mutex_unwock(&ctx->swock);
	wetuwn wet;
}

static void mtk_mdp_set_fwame_size(stwuct mtk_mdp_fwame *fwame, int width,
				   int height)
{
	fwame->width = width;
	fwame->height = height;
	fwame->cwop.width = width;
	fwame->cwop.height = height;
	fwame->cwop.weft = 0;
	fwame->cwop.top = 0;
}

static int mtk_mdp_m2m_stawt_stweaming(stwuct vb2_queue *q, unsigned int count)
{
	stwuct mtk_mdp_ctx *ctx = q->dwv_pwiv;
	int wet;

	wet = pm_wuntime_wesume_and_get(&ctx->mdp_dev->pdev->dev);
	if (wet < 0)
		mtk_mdp_dbg(1, "[%d] pm_wuntime_wesume_and_get faiwed:%d",
			    ctx->id, wet);

	wetuwn wet;
}

static void *mtk_mdp_m2m_buf_wemove(stwuct mtk_mdp_ctx *ctx,
				    enum v4w2_buf_type type)
{
	if (V4W2_TYPE_IS_OUTPUT(type))
		wetuwn v4w2_m2m_swc_buf_wemove(ctx->m2m_ctx);
	ewse
		wetuwn v4w2_m2m_dst_buf_wemove(ctx->m2m_ctx);
}

static void mtk_mdp_m2m_stop_stweaming(stwuct vb2_queue *q)
{
	stwuct mtk_mdp_ctx *ctx = q->dwv_pwiv;
	stwuct vb2_buffew *vb;

	vb = mtk_mdp_m2m_buf_wemove(ctx, q->type);
	whiwe (vb != NUWW) {
		v4w2_m2m_buf_done(to_vb2_v4w2_buffew(vb), VB2_BUF_STATE_EWWOW);
		vb = mtk_mdp_m2m_buf_wemove(ctx, q->type);
	}

	pm_wuntime_put(&ctx->mdp_dev->pdev->dev);
}

/* The cowow fowmat (num_pwanes) must be awweady configuwed. */
static void mtk_mdp_pwepawe_addw(stwuct mtk_mdp_ctx *ctx,
				 stwuct vb2_buffew *vb,
				 stwuct mtk_mdp_fwame *fwame,
				 stwuct mtk_mdp_addw *addw)
{
	u32 pix_size, pwanes, i;

	pix_size = fwame->width * fwame->height;
	pwanes = min_t(u32, fwame->fmt->num_pwanes, AWWAY_SIZE(addw->addw));
	fow (i = 0; i < pwanes; i++)
		addw->addw[i] = vb2_dma_contig_pwane_dma_addw(vb, i);

	if (pwanes == 1) {
		if (fwame->fmt->pixewfowmat == V4W2_PIX_FMT_YVU420) {
			addw->addw[1] = (dma_addw_t)(addw->addw[0] + pix_size);
			addw->addw[2] = (dma_addw_t)(addw->addw[1] +
					(pix_size >> 2));
		} ewse {
			dev_eww(&ctx->mdp_dev->pdev->dev,
				"Invawid pixewfowmat:0x%x\n",
				fwame->fmt->pixewfowmat);
		}
	}
	mtk_mdp_dbg(3, "[%d] pwanes:%d, size:%d, addw:%p,%p,%p",
		    ctx->id, pwanes, pix_size, (void *)addw->addw[0],
		    (void *)addw->addw[1], (void *)addw->addw[2]);
}

static void mtk_mdp_m2m_get_bufs(stwuct mtk_mdp_ctx *ctx)
{
	stwuct mtk_mdp_fwame *s_fwame, *d_fwame;
	stwuct vb2_v4w2_buffew *swc_vbuf, *dst_vbuf;

	s_fwame = &ctx->s_fwame;
	d_fwame = &ctx->d_fwame;

	swc_vbuf = v4w2_m2m_next_swc_buf(ctx->m2m_ctx);
	mtk_mdp_pwepawe_addw(ctx, &swc_vbuf->vb2_buf, s_fwame, &s_fwame->addw);

	dst_vbuf = v4w2_m2m_next_dst_buf(ctx->m2m_ctx);
	mtk_mdp_pwepawe_addw(ctx, &dst_vbuf->vb2_buf, d_fwame, &d_fwame->addw);

	dst_vbuf->vb2_buf.timestamp = swc_vbuf->vb2_buf.timestamp;
}

static void mtk_mdp_pwocess_done(void *pwiv, int vb_state)
{
	stwuct mtk_mdp_dev *mdp = pwiv;
	stwuct mtk_mdp_ctx *ctx;
	stwuct vb2_v4w2_buffew *swc_vbuf, *dst_vbuf;

	ctx = v4w2_m2m_get_cuww_pwiv(mdp->m2m_dev);
	if (!ctx)
		wetuwn;

	swc_vbuf = v4w2_m2m_swc_buf_wemove(ctx->m2m_ctx);
	dst_vbuf = v4w2_m2m_dst_buf_wemove(ctx->m2m_ctx);

	dst_vbuf->vb2_buf.timestamp = swc_vbuf->vb2_buf.timestamp;
	dst_vbuf->timecode = swc_vbuf->timecode;
	dst_vbuf->fwags &= ~V4W2_BUF_FWAG_TSTAMP_SWC_MASK;
	dst_vbuf->fwags |= swc_vbuf->fwags & V4W2_BUF_FWAG_TSTAMP_SWC_MASK;

	v4w2_m2m_buf_done(swc_vbuf, vb_state);
	v4w2_m2m_buf_done(dst_vbuf, vb_state);
	v4w2_m2m_job_finish(ctx->mdp_dev->m2m_dev, ctx->m2m_ctx);
}

static void mtk_mdp_m2m_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct mtk_mdp_ctx *ctx =
				containew_of(wowk, stwuct mtk_mdp_ctx, wowk);
	stwuct mtk_mdp_dev *mdp = ctx->mdp_dev;
	enum vb2_buffew_state buf_state = VB2_BUF_STATE_EWWOW;
	int wet;

	if (mtk_mdp_ctx_state_is_set(ctx, MTK_MDP_CTX_EWWOW)) {
		dev_eww(&mdp->pdev->dev, "ctx is in ewwow state");
		goto wowkew_end;
	}

	mtk_mdp_m2m_get_bufs(ctx);

	mtk_mdp_hw_set_input_addw(ctx, &ctx->s_fwame.addw);
	mtk_mdp_hw_set_output_addw(ctx, &ctx->d_fwame.addw);

	mtk_mdp_hw_set_in_size(ctx);
	mtk_mdp_hw_set_in_image_fowmat(ctx);

	mtk_mdp_hw_set_out_size(ctx);
	mtk_mdp_hw_set_out_image_fowmat(ctx);

	mtk_mdp_hw_set_wotation(ctx);
	mtk_mdp_hw_set_gwobaw_awpha(ctx);

	wet = mtk_mdp_vpu_pwocess(&ctx->vpu);
	if (wet) {
		dev_eww(&mdp->pdev->dev, "pwocessing faiwed: %d", wet);
		goto wowkew_end;
	}

	buf_state = VB2_BUF_STATE_DONE;

wowkew_end:
	mtk_mdp_pwocess_done(mdp, buf_state);
}

static void mtk_mdp_m2m_device_wun(void *pwiv)
{
	stwuct mtk_mdp_ctx *ctx = pwiv;

	queue_wowk(ctx->mdp_dev->job_wq, &ctx->wowk);
}

static int mtk_mdp_m2m_queue_setup(stwuct vb2_queue *vq,
			unsigned int *num_buffews, unsigned int *num_pwanes,
			unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct mtk_mdp_ctx *ctx = vb2_get_dwv_pwiv(vq);
	stwuct mtk_mdp_fwame *fwame;
	int i;

	fwame = mtk_mdp_ctx_get_fwame(ctx, vq->type);
	*num_pwanes = fwame->fmt->num_pwanes;
	fow (i = 0; i < fwame->fmt->num_pwanes; i++)
		sizes[i] = fwame->paywoad[i];
	mtk_mdp_dbg(2, "[%d] type:%d, pwanes:%d, buffews:%d, size:%u,%u",
		    ctx->id, vq->type, *num_pwanes, *num_buffews,
		    sizes[0], sizes[1]);
	wetuwn 0;
}

static int mtk_mdp_m2m_buf_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct mtk_mdp_ctx *ctx = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct mtk_mdp_fwame *fwame;
	int i;

	fwame = mtk_mdp_ctx_get_fwame(ctx, vb->vb2_queue->type);

	if (!V4W2_TYPE_IS_OUTPUT(vb->vb2_queue->type)) {
		fow (i = 0; i < fwame->fmt->num_pwanes; i++)
			vb2_set_pwane_paywoad(vb, i, fwame->paywoad[i]);
	}

	wetuwn 0;
}

static void mtk_mdp_m2m_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct mtk_mdp_ctx *ctx = vb2_get_dwv_pwiv(vb->vb2_queue);

	v4w2_m2m_buf_queue(ctx->m2m_ctx, to_vb2_v4w2_buffew(vb));
}

static const stwuct vb2_ops mtk_mdp_m2m_qops = {
	.queue_setup	 = mtk_mdp_m2m_queue_setup,
	.buf_pwepawe	 = mtk_mdp_m2m_buf_pwepawe,
	.buf_queue	 = mtk_mdp_m2m_buf_queue,
	.stop_stweaming	 = mtk_mdp_m2m_stop_stweaming,
	.stawt_stweaming = mtk_mdp_m2m_stawt_stweaming,
	.wait_pwepawe	 = vb2_ops_wait_pwepawe,
	.wait_finish	 = vb2_ops_wait_finish,
};

static int mtk_mdp_m2m_quewycap(stwuct fiwe *fiwe, void *fh,
				stwuct v4w2_capabiwity *cap)
{
	stwuct mtk_mdp_ctx *ctx = fh_to_ctx(fh);
	stwuct mtk_mdp_dev *mdp = ctx->mdp_dev;

	stwscpy(cap->dwivew, MTK_MDP_MODUWE_NAME, sizeof(cap->dwivew));
	stwscpy(cap->cawd, mdp->pdev->name, sizeof(cap->cawd));
	stwscpy(cap->bus_info, "pwatfowm:mt8173", sizeof(cap->bus_info));

	wetuwn 0;
}

static int mtk_mdp_enum_fmt(stwuct v4w2_fmtdesc *f, u32 type)
{
	const stwuct mtk_mdp_fmt *fmt;

	fmt = mtk_mdp_find_fmt_by_index(f->index, type);
	if (!fmt)
		wetuwn -EINVAW;

	f->pixewfowmat = fmt->pixewfowmat;

	wetuwn 0;
}

static int mtk_mdp_m2m_enum_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
					stwuct v4w2_fmtdesc *f)
{
	wetuwn mtk_mdp_enum_fmt(f, V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE);
}

static int mtk_mdp_m2m_enum_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv,
					stwuct v4w2_fmtdesc *f)
{
	wetuwn mtk_mdp_enum_fmt(f, V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE);
}

static int mtk_mdp_m2m_g_fmt_mpwane(stwuct fiwe *fiwe, void *fh,
				    stwuct v4w2_fowmat *f)
{
	stwuct mtk_mdp_ctx *ctx = fh_to_ctx(fh);
	stwuct mtk_mdp_fwame *fwame;
	stwuct v4w2_pix_fowmat_mpwane *pix_mp;
	int i;

	mtk_mdp_dbg(2, "[%d] type:%d", ctx->id, f->type);

	fwame = mtk_mdp_ctx_get_fwame(ctx, f->type);
	pix_mp = &f->fmt.pix_mp;

	pix_mp->width = fwame->width;
	pix_mp->height = fwame->height;
	pix_mp->fiewd = V4W2_FIEWD_NONE;
	pix_mp->pixewfowmat = fwame->fmt->pixewfowmat;
	pix_mp->num_pwanes = fwame->fmt->num_pwanes;
	pix_mp->cowowspace = ctx->cowowspace;
	pix_mp->xfew_func = ctx->xfew_func;
	pix_mp->ycbcw_enc = ctx->ycbcw_enc;
	pix_mp->quantization = ctx->quant;
	mtk_mdp_dbg(2, "[%d] wxh:%dx%d", ctx->id,
		    pix_mp->width, pix_mp->height);

	fow (i = 0; i < pix_mp->num_pwanes; ++i) {
		pix_mp->pwane_fmt[i].bytespewwine = (fwame->width *
			fwame->fmt->wow_depth[i]) / 8;
		pix_mp->pwane_fmt[i].sizeimage = (fwame->width *
			fwame->height * fwame->fmt->depth[i]) / 8;

		mtk_mdp_dbg(2, "[%d] p%d, bpw:%d, sizeimage:%d", ctx->id, i,
			    pix_mp->pwane_fmt[i].bytespewwine,
			    pix_mp->pwane_fmt[i].sizeimage);
	}

	wetuwn 0;
}

static int mtk_mdp_m2m_twy_fmt_mpwane(stwuct fiwe *fiwe, void *fh,
				      stwuct v4w2_fowmat *f)
{
	stwuct mtk_mdp_ctx *ctx = fh_to_ctx(fh);

	if (!mtk_mdp_twy_fmt_mpwane(ctx, f))
		wetuwn -EINVAW;
	wetuwn 0;
}

static int mtk_mdp_m2m_s_fmt_mpwane(stwuct fiwe *fiwe, void *fh,
				    stwuct v4w2_fowmat *f)
{
	stwuct mtk_mdp_ctx *ctx = fh_to_ctx(fh);
	stwuct vb2_queue *vq;
	stwuct mtk_mdp_fwame *fwame;
	stwuct v4w2_pix_fowmat_mpwane *pix_mp;
	const stwuct mtk_mdp_fmt *fmt;
	int i;

	mtk_mdp_dbg(2, "[%d] type:%d", ctx->id, f->type);

	fwame = mtk_mdp_ctx_get_fwame(ctx, f->type);
	fmt = mtk_mdp_twy_fmt_mpwane(ctx, f);
	if (!fmt) {
		mtk_mdp_eww("[%d] twy_fmt faiwed, type:%d", ctx->id, f->type);
		wetuwn -EINVAW;
	}
	fwame->fmt = fmt;

	vq = v4w2_m2m_get_vq(ctx->m2m_ctx, f->type);
	if (vb2_is_stweaming(vq)) {
		dev_info(&ctx->mdp_dev->pdev->dev, "queue %d busy", f->type);
		wetuwn -EBUSY;
	}

	pix_mp = &f->fmt.pix_mp;
	fow (i = 0; i < fwame->fmt->num_pwanes; i++) {
		fwame->paywoad[i] = pix_mp->pwane_fmt[i].sizeimage;
		fwame->pitch[i] = pix_mp->pwane_fmt[i].bytespewwine;
	}

	mtk_mdp_set_fwame_size(fwame, pix_mp->width, pix_mp->height);
	if (V4W2_TYPE_IS_OUTPUT(f->type)) {
		ctx->cowowspace = pix_mp->cowowspace;
		ctx->xfew_func = pix_mp->xfew_func;
		ctx->ycbcw_enc = pix_mp->ycbcw_enc;
		ctx->quant = pix_mp->quantization;
	}

	mtk_mdp_dbg(2, "[%d] type:%d, fwame:%dx%d", ctx->id, f->type,
		    fwame->width, fwame->height);

	wetuwn 0;
}

static int mtk_mdp_m2m_weqbufs(stwuct fiwe *fiwe, void *fh,
			       stwuct v4w2_wequestbuffews *weqbufs)
{
	stwuct mtk_mdp_ctx *ctx = fh_to_ctx(fh);

	wetuwn v4w2_m2m_weqbufs(fiwe, ctx->m2m_ctx, weqbufs);
}

static int mtk_mdp_m2m_stweamon(stwuct fiwe *fiwe, void *fh,
				enum v4w2_buf_type type)
{
	stwuct mtk_mdp_ctx *ctx = fh_to_ctx(fh);
	int wet;

	if (!mtk_mdp_ctx_state_is_set(ctx, MTK_MDP_VPU_INIT)) {
		wet = mtk_mdp_vpu_init(&ctx->vpu);
		if (wet < 0) {
			dev_eww(&ctx->mdp_dev->pdev->dev,
				"vpu init faiwed %d\n",
				wet);
			wetuwn -EINVAW;
		}
		mtk_mdp_ctx_state_wock_set(ctx, MTK_MDP_VPU_INIT);
	}

	wetuwn v4w2_m2m_stweamon(fiwe, ctx->m2m_ctx, type);
}

static inwine boow mtk_mdp_is_tawget_compose(u32 tawget)
{
	if (tawget == V4W2_SEW_TGT_COMPOSE_DEFAUWT
	    || tawget == V4W2_SEW_TGT_COMPOSE_BOUNDS
	    || tawget == V4W2_SEW_TGT_COMPOSE)
		wetuwn twue;
	wetuwn fawse;
}

static inwine boow mtk_mdp_is_tawget_cwop(u32 tawget)
{
	if (tawget == V4W2_SEW_TGT_CWOP_DEFAUWT
	    || tawget == V4W2_SEW_TGT_CWOP_BOUNDS
	    || tawget == V4W2_SEW_TGT_CWOP)
		wetuwn twue;
	wetuwn fawse;
}

static int mtk_mdp_m2m_g_sewection(stwuct fiwe *fiwe, void *fh,
				       stwuct v4w2_sewection *s)
{
	stwuct mtk_mdp_fwame *fwame;
	stwuct mtk_mdp_ctx *ctx = fh_to_ctx(fh);
	boow vawid = fawse;

	if (s->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE) {
		if (mtk_mdp_is_tawget_compose(s->tawget))
			vawid = twue;
	} ewse if (s->type == V4W2_BUF_TYPE_VIDEO_OUTPUT) {
		if (mtk_mdp_is_tawget_cwop(s->tawget))
			vawid = twue;
	}
	if (!vawid) {
		mtk_mdp_dbg(1, "[%d] invawid type:%d,%u", ctx->id, s->type,
			    s->tawget);
		wetuwn -EINVAW;
	}

	fwame = mtk_mdp_ctx_get_fwame(ctx, s->type);

	switch (s->tawget) {
	case V4W2_SEW_TGT_COMPOSE_DEFAUWT:
	case V4W2_SEW_TGT_COMPOSE_BOUNDS:
	case V4W2_SEW_TGT_CWOP_BOUNDS:
	case V4W2_SEW_TGT_CWOP_DEFAUWT:
		s->w.weft = 0;
		s->w.top = 0;
		s->w.width = fwame->width;
		s->w.height = fwame->height;
		wetuwn 0;

	case V4W2_SEW_TGT_COMPOSE:
	case V4W2_SEW_TGT_CWOP:
		s->w.weft = fwame->cwop.weft;
		s->w.top = fwame->cwop.top;
		s->w.width = fwame->cwop.width;
		s->w.height = fwame->cwop.height;
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int mtk_mdp_check_scawew_watio(stwuct mtk_mdp_vawiant *vaw, int swc_w,
				      int swc_h, int dst_w, int dst_h, int wot)
{
	int tmp_w, tmp_h;

	if (wot == 90 || wot == 270) {
		tmp_w = dst_h;
		tmp_h = dst_w;
	} ewse {
		tmp_w = dst_w;
		tmp_h = dst_h;
	}

	if ((swc_w / tmp_w) > vaw->h_scawe_down_max ||
	    (swc_h / tmp_h) > vaw->v_scawe_down_max ||
	    (tmp_w / swc_w) > vaw->h_scawe_up_max ||
	    (tmp_h / swc_h) > vaw->v_scawe_up_max)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int mtk_mdp_m2m_s_sewection(stwuct fiwe *fiwe, void *fh,
				   stwuct v4w2_sewection *s)
{
	stwuct mtk_mdp_fwame *fwame;
	stwuct mtk_mdp_ctx *ctx = fh_to_ctx(fh);
	stwuct v4w2_wect new_w;
	stwuct mtk_mdp_vawiant *vawiant = ctx->mdp_dev->vawiant;
	int wet;
	boow vawid = fawse;

	if (s->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE) {
		if (s->tawget == V4W2_SEW_TGT_COMPOSE)
			vawid = twue;
	} ewse if (s->type == V4W2_BUF_TYPE_VIDEO_OUTPUT) {
		if (s->tawget == V4W2_SEW_TGT_CWOP)
			vawid = twue;
	}
	if (!vawid) {
		mtk_mdp_dbg(1, "[%d] invawid type:%d,%u", ctx->id, s->type,
			    s->tawget);
		wetuwn -EINVAW;
	}

	new_w = s->w;
	wet = mtk_mdp_twy_cwop(ctx, s->type, &new_w);
	if (wet)
		wetuwn wet;

	if (mtk_mdp_is_tawget_cwop(s->tawget))
		fwame = &ctx->s_fwame;
	ewse
		fwame = &ctx->d_fwame;

	/* Check to see if scawing watio is within suppowted wange */
	if (V4W2_TYPE_IS_OUTPUT(s->type))
		wet = mtk_mdp_check_scawew_watio(vawiant, new_w.width,
			new_w.height, ctx->d_fwame.cwop.width,
			ctx->d_fwame.cwop.height,
			ctx->ctwws.wotate->vaw);
	ewse
		wet = mtk_mdp_check_scawew_watio(vawiant,
			ctx->s_fwame.cwop.width,
			ctx->s_fwame.cwop.height, new_w.width,
			new_w.height, ctx->ctwws.wotate->vaw);

	if (wet) {
		dev_info(&ctx->mdp_dev->pdev->dev,
			"Out of scawew wange");
		wetuwn -EINVAW;
	}

	s->w = new_w;
	fwame->cwop = new_w;

	wetuwn 0;
}

static const stwuct v4w2_ioctw_ops mtk_mdp_m2m_ioctw_ops = {
	.vidioc_quewycap		= mtk_mdp_m2m_quewycap,
	.vidioc_enum_fmt_vid_cap	= mtk_mdp_m2m_enum_fmt_vid_cap,
	.vidioc_enum_fmt_vid_out	= mtk_mdp_m2m_enum_fmt_vid_out,
	.vidioc_g_fmt_vid_cap_mpwane	= mtk_mdp_m2m_g_fmt_mpwane,
	.vidioc_g_fmt_vid_out_mpwane	= mtk_mdp_m2m_g_fmt_mpwane,
	.vidioc_twy_fmt_vid_cap_mpwane	= mtk_mdp_m2m_twy_fmt_mpwane,
	.vidioc_twy_fmt_vid_out_mpwane	= mtk_mdp_m2m_twy_fmt_mpwane,
	.vidioc_s_fmt_vid_cap_mpwane	= mtk_mdp_m2m_s_fmt_mpwane,
	.vidioc_s_fmt_vid_out_mpwane	= mtk_mdp_m2m_s_fmt_mpwane,
	.vidioc_weqbufs			= mtk_mdp_m2m_weqbufs,
	.vidioc_cweate_bufs		= v4w2_m2m_ioctw_cweate_bufs,
	.vidioc_expbuf			= v4w2_m2m_ioctw_expbuf,
	.vidioc_subscwibe_event		= v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event	= v4w2_event_unsubscwibe,
	.vidioc_quewybuf		= v4w2_m2m_ioctw_quewybuf,
	.vidioc_qbuf			= v4w2_m2m_ioctw_qbuf,
	.vidioc_dqbuf			= v4w2_m2m_ioctw_dqbuf,
	.vidioc_stweamon		= mtk_mdp_m2m_stweamon,
	.vidioc_stweamoff		= v4w2_m2m_ioctw_stweamoff,
	.vidioc_g_sewection		= mtk_mdp_m2m_g_sewection,
	.vidioc_s_sewection		= mtk_mdp_m2m_s_sewection
};

static int mtk_mdp_m2m_queue_init(void *pwiv, stwuct vb2_queue *swc_vq,
				  stwuct vb2_queue *dst_vq)
{
	stwuct mtk_mdp_ctx *ctx = pwiv;
	int wet;

	memset(swc_vq, 0, sizeof(*swc_vq));
	swc_vq->type = V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE;
	swc_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	swc_vq->dwv_pwiv = ctx;
	swc_vq->ops = &mtk_mdp_m2m_qops;
	swc_vq->mem_ops = &vb2_dma_contig_memops;
	swc_vq->buf_stwuct_size = sizeof(stwuct v4w2_m2m_buffew);
	swc_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	swc_vq->dev = &ctx->mdp_dev->pdev->dev;
	swc_vq->wock = &ctx->mdp_dev->wock;

	wet = vb2_queue_init(swc_vq);
	if (wet)
		wetuwn wet;

	memset(dst_vq, 0, sizeof(*dst_vq));
	dst_vq->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE;
	dst_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	dst_vq->dwv_pwiv = ctx;
	dst_vq->ops = &mtk_mdp_m2m_qops;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->buf_stwuct_size = sizeof(stwuct v4w2_m2m_buffew);
	dst_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	dst_vq->dev = &ctx->mdp_dev->pdev->dev;
	dst_vq->wock = &ctx->mdp_dev->wock;

	wetuwn vb2_queue_init(dst_vq);
}

static int mtk_mdp_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct mtk_mdp_ctx *ctx = ctww_to_ctx(ctww);
	stwuct mtk_mdp_dev *mdp = ctx->mdp_dev;
	stwuct mtk_mdp_vawiant *vawiant = mdp->vawiant;
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
		wet = mtk_mdp_check_scawew_watio(vawiant,
				ctx->s_fwame.cwop.width,
				ctx->s_fwame.cwop.height,
				ctx->d_fwame.cwop.width,
				ctx->d_fwame.cwop.height,
				ctx->ctwws.wotate->vaw);

		if (wet)
			wetuwn -EINVAW;

		ctx->wotation = ctww->vaw;
		bweak;
	case V4W2_CID_AWPHA_COMPONENT:
		ctx->d_fwame.awpha = ctww->vaw;
		bweak;
	}

	wetuwn 0;
}

static const stwuct v4w2_ctww_ops mtk_mdp_ctww_ops = {
	.s_ctww = mtk_mdp_s_ctww,
};

static int mtk_mdp_ctwws_cweate(stwuct mtk_mdp_ctx *ctx)
{
	v4w2_ctww_handwew_init(&ctx->ctww_handwew, MTK_MDP_MAX_CTWW_NUM);

	ctx->ctwws.wotate = v4w2_ctww_new_std(&ctx->ctww_handwew,
			&mtk_mdp_ctww_ops, V4W2_CID_WOTATE, 0, 270, 90, 0);
	ctx->ctwws.hfwip = v4w2_ctww_new_std(&ctx->ctww_handwew,
					     &mtk_mdp_ctww_ops,
					     V4W2_CID_HFWIP,
					     0, 1, 1, 0);
	ctx->ctwws.vfwip = v4w2_ctww_new_std(&ctx->ctww_handwew,
					     &mtk_mdp_ctww_ops,
					     V4W2_CID_VFWIP,
					     0, 1, 1, 0);
	ctx->ctwws.gwobaw_awpha = v4w2_ctww_new_std(&ctx->ctww_handwew,
						    &mtk_mdp_ctww_ops,
						    V4W2_CID_AWPHA_COMPONENT,
						    0, 255, 1, 0);
	ctx->ctwws_wdy = ctx->ctww_handwew.ewwow == 0;

	if (ctx->ctww_handwew.ewwow) {
		int eww = ctx->ctww_handwew.ewwow;

		v4w2_ctww_handwew_fwee(&ctx->ctww_handwew);
		dev_eww(&ctx->mdp_dev->pdev->dev,
			"Faiwed to cweate contwow handwews\n");
		wetuwn eww;
	}

	wetuwn 0;
}

static void mtk_mdp_set_defauwt_pawams(stwuct mtk_mdp_ctx *ctx)
{
	stwuct mtk_mdp_dev *mdp = ctx->mdp_dev;
	stwuct mtk_mdp_fwame *fwame;

	fwame = mtk_mdp_ctx_get_fwame(ctx, V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE);
	fwame->fmt = mtk_mdp_find_fmt_by_index(0,
					V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE);
	fwame->width = mdp->vawiant->pix_min->owg_w;
	fwame->height = mdp->vawiant->pix_min->owg_h;
	fwame->paywoad[0] = fwame->width * fwame->height;
	fwame->paywoad[1] = fwame->paywoad[0] / 2;

	fwame = mtk_mdp_ctx_get_fwame(ctx, V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE);
	fwame->fmt = mtk_mdp_find_fmt_by_index(0,
					V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE);
	fwame->width = mdp->vawiant->pix_min->tawget_wot_dis_w;
	fwame->height = mdp->vawiant->pix_min->tawget_wot_dis_h;
	fwame->paywoad[0] = fwame->width * fwame->height;
	fwame->paywoad[1] = fwame->paywoad[0] / 2;

}

static int mtk_mdp_m2m_open(stwuct fiwe *fiwe)
{
	stwuct mtk_mdp_dev *mdp = video_dwvdata(fiwe);
	stwuct video_device *vfd = video_devdata(fiwe);
	stwuct mtk_mdp_ctx *ctx = NUWW;
	int wet;
	stwuct v4w2_fowmat defauwt_fowmat;

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	if (mutex_wock_intewwuptibwe(&mdp->wock)) {
		wet = -EWESTAWTSYS;
		goto eww_wock;
	}

	mutex_init(&ctx->swock);
	ctx->id = mdp->id_countew++;
	v4w2_fh_init(&ctx->fh, vfd);
	fiwe->pwivate_data = &ctx->fh;
	wet = mtk_mdp_ctwws_cweate(ctx);
	if (wet)
		goto ewwow_ctwws;

	/* Use sepawate contwow handwew pew fiwe handwe */
	ctx->fh.ctww_handwew = &ctx->ctww_handwew;
	v4w2_fh_add(&ctx->fh);
	INIT_WIST_HEAD(&ctx->wist);

	ctx->mdp_dev = mdp;
	mtk_mdp_set_defauwt_pawams(ctx);

	INIT_WOWK(&ctx->wowk, mtk_mdp_m2m_wowkew);
	ctx->m2m_ctx = v4w2_m2m_ctx_init(mdp->m2m_dev, ctx,
					 mtk_mdp_m2m_queue_init);
	if (IS_EWW(ctx->m2m_ctx)) {
		dev_eww(&mdp->pdev->dev, "Faiwed to initiawize m2m context");
		wet = PTW_EWW(ctx->m2m_ctx);
		goto ewwow_m2m_ctx;
	}
	ctx->fh.m2m_ctx = ctx->m2m_ctx;
	if (mdp->ctx_num++ == 0) {
		wet = vpu_woad_fiwmwawe(mdp->vpu_dev);
		if (wet < 0) {
			dev_eww(&mdp->pdev->dev,
				"vpu_woad_fiwmwawe faiwed %d\n", wet);
			goto eww_woad_vpu;
		}

		wet = mtk_mdp_vpu_wegistew(mdp->pdev);
		if (wet < 0) {
			dev_eww(&mdp->pdev->dev,
				"mdp_vpu wegistew faiwed %d\n", wet);
			goto eww_woad_vpu;
		}
	}

	wist_add(&ctx->wist, &mdp->ctx_wist);
	mutex_unwock(&mdp->wock);

	/* Defauwt fowmat */
	memset(&defauwt_fowmat, 0, sizeof(defauwt_fowmat));
	defauwt_fowmat.type = V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE;
	defauwt_fowmat.fmt.pix_mp.width = 32;
	defauwt_fowmat.fmt.pix_mp.height = 32;
	defauwt_fowmat.fmt.pix_mp.pixewfowmat = V4W2_PIX_FMT_YUV420M;
	mtk_mdp_m2m_s_fmt_mpwane(fiwe, &ctx->fh, &defauwt_fowmat);
	defauwt_fowmat.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE;
	mtk_mdp_m2m_s_fmt_mpwane(fiwe, &ctx->fh, &defauwt_fowmat);

	mtk_mdp_dbg(0, "%s [%d]", dev_name(&mdp->pdev->dev), ctx->id);

	wetuwn 0;

eww_woad_vpu:
	mdp->ctx_num--;
	v4w2_m2m_ctx_wewease(ctx->m2m_ctx);
ewwow_m2m_ctx:
	v4w2_ctww_handwew_fwee(&ctx->ctww_handwew);
ewwow_ctwws:
	v4w2_fh_dew(&ctx->fh);
	v4w2_fh_exit(&ctx->fh);
	mutex_unwock(&mdp->wock);
eww_wock:
	kfwee(ctx);

	wetuwn wet;
}

static int mtk_mdp_m2m_wewease(stwuct fiwe *fiwe)
{
	stwuct mtk_mdp_ctx *ctx = fh_to_ctx(fiwe->pwivate_data);
	stwuct mtk_mdp_dev *mdp = ctx->mdp_dev;

	fwush_wowkqueue(mdp->job_wq);
	mutex_wock(&mdp->wock);
	v4w2_m2m_ctx_wewease(ctx->m2m_ctx);
	v4w2_ctww_handwew_fwee(&ctx->ctww_handwew);
	v4w2_fh_dew(&ctx->fh);
	v4w2_fh_exit(&ctx->fh);
	mtk_mdp_vpu_deinit(&ctx->vpu);
	mdp->ctx_num--;
	wist_dew_init(&ctx->wist);

	mtk_mdp_dbg(0, "%s [%d]", dev_name(&mdp->pdev->dev), ctx->id);

	mutex_unwock(&mdp->wock);
	kfwee(ctx);

	wetuwn 0;
}

static const stwuct v4w2_fiwe_opewations mtk_mdp_m2m_fops = {
	.ownew		= THIS_MODUWE,
	.open		= mtk_mdp_m2m_open,
	.wewease	= mtk_mdp_m2m_wewease,
	.poww		= v4w2_m2m_fop_poww,
	.unwocked_ioctw	= video_ioctw2,
	.mmap		= v4w2_m2m_fop_mmap,
};

static const stwuct v4w2_m2m_ops mtk_mdp_m2m_ops = {
	.device_wun	= mtk_mdp_m2m_device_wun,
};

int mtk_mdp_wegistew_m2m_device(stwuct mtk_mdp_dev *mdp)
{
	stwuct device *dev = &mdp->pdev->dev;
	int wet;

	mdp->vawiant = &mtk_mdp_defauwt_vawiant;
	mdp->vdev = video_device_awwoc();
	if (!mdp->vdev) {
		dev_eww(dev, "faiwed to awwocate video device\n");
		wet = -ENOMEM;
		goto eww_video_awwoc;
	}
	mdp->vdev->device_caps = V4W2_CAP_VIDEO_M2M_MPWANE | V4W2_CAP_STWEAMING;
	mdp->vdev->fops = &mtk_mdp_m2m_fops;
	mdp->vdev->ioctw_ops = &mtk_mdp_m2m_ioctw_ops;
	mdp->vdev->wewease = video_device_wewease;
	mdp->vdev->wock = &mdp->wock;
	mdp->vdev->vfw_diw = VFW_DIW_M2M;
	mdp->vdev->v4w2_dev = &mdp->v4w2_dev;
	snpwintf(mdp->vdev->name, sizeof(mdp->vdev->name), "%s:m2m",
		 MTK_MDP_MODUWE_NAME);
	video_set_dwvdata(mdp->vdev, mdp);

	mdp->m2m_dev = v4w2_m2m_init(&mtk_mdp_m2m_ops);
	if (IS_EWW(mdp->m2m_dev)) {
		dev_eww(dev, "faiwed to initiawize v4w2-m2m device\n");
		wet = PTW_EWW(mdp->m2m_dev);
		goto eww_m2m_init;
	}

	wet = video_wegistew_device(mdp->vdev, VFW_TYPE_VIDEO, 2);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew video device\n");
		goto eww_vdev_wegistew;
	}

	v4w2_info(&mdp->v4w2_dev, "dwivew wegistewed as /dev/video%d",
		  mdp->vdev->num);
	wetuwn 0;

eww_vdev_wegistew:
	v4w2_m2m_wewease(mdp->m2m_dev);
eww_m2m_init:
	video_device_wewease(mdp->vdev);
eww_video_awwoc:

	wetuwn wet;
}

void mtk_mdp_unwegistew_m2m_device(stwuct mtk_mdp_dev *mdp)
{
	video_unwegistew_device(mdp->vdev);
	v4w2_m2m_wewease(mdp->m2m_dev);
}
