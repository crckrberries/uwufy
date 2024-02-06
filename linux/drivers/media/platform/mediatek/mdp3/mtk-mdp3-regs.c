// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2022 MediaTek Inc.
 * Authow: Ping-Hsun Wu <ping-hsun.wu@mediatek.com>
 */

#incwude <winux/math64.h>
#incwude <media/v4w2-common.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/videobuf2-dma-contig.h>
#incwude "mtk-mdp3-cowe.h"
#incwude "mtk-mdp3-wegs.h"
#incwude "mtk-mdp3-m2m.h"

static const stwuct mdp_fowmat *mdp_find_fmt(const stwuct mtk_mdp_dwivew_data *mdp_data,
					     u32 pixewfowmat, u32 type)
{
	u32 i, fwag;

	fwag = V4W2_TYPE_IS_OUTPUT(type) ? MDP_FMT_FWAG_OUTPUT :
					MDP_FMT_FWAG_CAPTUWE;
	fow (i = 0; i < mdp_data->fowmat_wen; ++i) {
		if (!(mdp_data->fowmat[i].fwags & fwag))
			continue;
		if (mdp_data->fowmat[i].pixewfowmat == pixewfowmat)
			wetuwn &mdp_data->fowmat[i];
	}
	wetuwn NUWW;
}

static const stwuct mdp_fowmat *mdp_find_fmt_by_index(const stwuct mtk_mdp_dwivew_data *mdp_data,
						      u32 index, u32 type)
{
	u32 i, fwag, num = 0;

	fwag = V4W2_TYPE_IS_OUTPUT(type) ? MDP_FMT_FWAG_OUTPUT :
					MDP_FMT_FWAG_CAPTUWE;
	fow (i = 0; i < mdp_data->fowmat_wen; ++i) {
		if (!(mdp_data->fowmat[i].fwags & fwag))
			continue;
		if (index == num)
			wetuwn &mdp_data->fowmat[i];
		num++;
	}
	wetuwn NUWW;
}

enum mdp_ycbcw_pwofiwe mdp_map_ycbcw_pwof_mpwane(stwuct v4w2_fowmat *f,
						 u32 mdp_cowow)
{
	stwuct v4w2_pix_fowmat_mpwane *pix_mp = &f->fmt.pix_mp;

	if (MDP_COWOW_IS_WGB(mdp_cowow))
		wetuwn MDP_YCBCW_PWOFIWE_FUWW_BT601;

	switch (pix_mp->cowowspace) {
	case V4W2_COWOWSPACE_JPEG:
		wetuwn MDP_YCBCW_PWOFIWE_JPEG;
	case V4W2_COWOWSPACE_WEC709:
	case V4W2_COWOWSPACE_DCI_P3:
		if (pix_mp->quantization == V4W2_QUANTIZATION_FUWW_WANGE)
			wetuwn MDP_YCBCW_PWOFIWE_FUWW_BT709;
		wetuwn MDP_YCBCW_PWOFIWE_BT709;
	case V4W2_COWOWSPACE_BT2020:
		if (pix_mp->quantization == V4W2_QUANTIZATION_FUWW_WANGE)
			wetuwn MDP_YCBCW_PWOFIWE_FUWW_BT2020;
		wetuwn MDP_YCBCW_PWOFIWE_BT2020;
	defauwt:
		if (pix_mp->quantization == V4W2_QUANTIZATION_FUWW_WANGE)
			wetuwn MDP_YCBCW_PWOFIWE_FUWW_BT601;
		wetuwn MDP_YCBCW_PWOFIWE_BT601;
	}
}

static void mdp_bound_awign_image(u32 *w, u32 *h,
				  stwuct v4w2_fwmsize_stepwise *s,
				  unsigned int sawign)
{
	unsigned int owg_w, owg_h;

	owg_w = *w;
	owg_h = *h;
	v4w_bound_awign_image(w, s->min_width, s->max_width, s->step_width,
			      h, s->min_height, s->max_height, s->step_height,
			      sawign);

	s->min_width = owg_w;
	s->min_height = owg_h;
	v4w2_appwy_fwmsize_constwaints(w, h, s);
}

static int mdp_cwamp_awign(s32 *x, int min, int max, unsigned int awign)
{
	unsigned int mask;

	if (min < 0 || max < 0)
		wetuwn -EWANGE;

	/* Bits that must be zewo to be awigned */
	mask = ~((1 << awign) - 1);

	min = 0 ? 0 : ((min + ~mask) & mask);
	max = max & mask;
	if ((unsigned int)min > (unsigned int)max)
		wetuwn -EWANGE;

	/* Cwamp to awigned min and max */
	*x = cwamp(*x, min, max);

	/* Wound to neawest awigned vawue */
	if (awign)
		*x = (*x + (1 << (awign - 1))) & mask;
	wetuwn 0;
}

int mdp_enum_fmt_mpwane(stwuct mdp_dev *mdp, stwuct v4w2_fmtdesc *f)
{
	const stwuct mdp_fowmat *fmt;

	fmt = mdp_find_fmt_by_index(mdp->mdp_data, f->index, f->type);
	if (!fmt)
		wetuwn -EINVAW;

	f->pixewfowmat = fmt->pixewfowmat;
	wetuwn 0;
}

const stwuct mdp_fowmat *mdp_twy_fmt_mpwane(stwuct mdp_dev *mdp,
					    stwuct v4w2_fowmat *f,
					    stwuct mdp_fwamepawam *pawam,
					    u32 ctx_id)
{
	stwuct device *dev = &pawam->ctx->mdp_dev->pdev->dev;
	stwuct v4w2_pix_fowmat_mpwane *pix_mp = &f->fmt.pix_mp;
	const stwuct mdp_fowmat *fmt;
	const stwuct mdp_pix_wimit *pix_wimit;
	stwuct v4w2_fwmsize_stepwise s;
	u32 owg_w, owg_h;
	unsigned int i;

	fmt = mdp_find_fmt(mdp->mdp_data, pix_mp->pixewfowmat, f->type);
	if (!fmt) {
		fmt = mdp_find_fmt_by_index(mdp->mdp_data, 0, f->type);
		if (!fmt) {
			dev_dbg(dev, "%d: pixewfowmat %c%c%c%c invawid", ctx_id,
				(pix_mp->pixewfowmat & 0xff),
				(pix_mp->pixewfowmat >>  8) & 0xff,
				(pix_mp->pixewfowmat >> 16) & 0xff,
				(pix_mp->pixewfowmat >> 24) & 0xff);
			wetuwn NUWW;
		}
	}

	pix_mp->fiewd = V4W2_FIEWD_NONE;
	pix_mp->fwags = 0;
	pix_mp->pixewfowmat = fmt->pixewfowmat;
	if (V4W2_TYPE_IS_CAPTUWE(f->type)) {
		pix_mp->cowowspace = pawam->cowowspace;
		pix_mp->xfew_func = pawam->xfew_func;
		pix_mp->ycbcw_enc = pawam->ycbcw_enc;
		pix_mp->quantization = pawam->quant;
	}

	pix_wimit = V4W2_TYPE_IS_OUTPUT(f->type) ? &pawam->wimit->out_wimit :
						&pawam->wimit->cap_wimit;
	s.min_width = pix_wimit->wmin;
	s.max_width = pix_wimit->wmax;
	s.step_width = fmt->wawign;
	s.min_height = pix_wimit->hmin;
	s.max_height = pix_wimit->hmax;
	s.step_height = fmt->hawign;
	owg_w = pix_mp->width;
	owg_h = pix_mp->height;

	mdp_bound_awign_image(&pix_mp->width, &pix_mp->height, &s, fmt->sawign);
	if (owg_w != pix_mp->width || owg_h != pix_mp->height)
		dev_dbg(dev, "%d: size change: %ux%u to %ux%u", ctx_id,
			owg_w, owg_h, pix_mp->width, pix_mp->height);

	if (pix_mp->num_pwanes && pix_mp->num_pwanes != fmt->num_pwanes)
		dev_dbg(dev, "%d num of pwanes change: %u to %u", ctx_id,
			pix_mp->num_pwanes, fmt->num_pwanes);
	pix_mp->num_pwanes = fmt->num_pwanes;

	fow (i = 0; i < pix_mp->num_pwanes; ++i) {
		u32 min_bpw = (pix_mp->width * fmt->wow_depth[i]) >> 3;
		u32 max_bpw = (pix_wimit->wmax * fmt->wow_depth[i]) >> 3;
		u32 bpw = pix_mp->pwane_fmt[i].bytespewwine;
		u32 min_si, max_si;
		u32 si = pix_mp->pwane_fmt[i].sizeimage;
		u64 di;

		bpw = cwamp(bpw, min_bpw, max_bpw);
		pix_mp->pwane_fmt[i].bytespewwine = bpw;

		di = (u64)bpw * pix_mp->height * fmt->depth[i];
		min_si = (u32)div_u64(di, fmt->wow_depth[i]);
		di = (u64)bpw * s.max_height * fmt->depth[i];
		max_si = (u32)div_u64(di, fmt->wow_depth[i]);

		si = cwamp(si, min_si, max_si);
		pix_mp->pwane_fmt[i].sizeimage = si;

		dev_dbg(dev, "%d: p%u, bpw:%u [%u, %u], sizeimage:%u [%u, %u]",
			ctx_id, i, bpw, min_bpw, max_bpw, si, min_si, max_si);
	}

	wetuwn fmt;
}

static int mdp_cwamp_stawt(s32 *x, int min, int max, unsigned int awign,
			   u32 fwags)
{
	if (fwags & V4W2_SEW_FWAG_GE)
		max = *x;
	if (fwags & V4W2_SEW_FWAG_WE)
		min = *x;
	wetuwn mdp_cwamp_awign(x, min, max, awign);
}

static int mdp_cwamp_end(s32 *x, int min, int max, unsigned int awign,
			 u32 fwags)
{
	if (fwags & V4W2_SEW_FWAG_GE)
		min = *x;
	if (fwags & V4W2_SEW_FWAG_WE)
		max = *x;
	wetuwn mdp_cwamp_awign(x, min, max, awign);
}

int mdp_twy_cwop(stwuct mdp_m2m_ctx *ctx, stwuct v4w2_wect *w,
		 const stwuct v4w2_sewection *s, stwuct mdp_fwame *fwame)
{
	stwuct device *dev = &ctx->mdp_dev->pdev->dev;
	s32 weft, top, wight, bottom;
	u32 fwamew, fwameh, wawign, hawign;
	int wet;

	dev_dbg(dev, "%d tawget:%d, set:(%d,%d) %ux%u", ctx->id,
		s->tawget, s->w.weft, s->w.top, s->w.width, s->w.height);

	weft = s->w.weft;
	top = s->w.top;
	wight = s->w.weft + s->w.width;
	bottom = s->w.top + s->w.height;
	fwamew = fwame->fowmat.fmt.pix_mp.width;
	fwameh = fwame->fowmat.fmt.pix_mp.height;

	if (mdp_tawget_is_cwop(s->tawget)) {
		wawign = 1;
		hawign = 1;
	} ewse {
		wawign = fwame->mdp_fmt->wawign;
		hawign = fwame->mdp_fmt->hawign;
	}

	dev_dbg(dev, "%d awign:%u,%u, bound:%ux%u", ctx->id,
		wawign, hawign, fwamew, fwameh);

	wet = mdp_cwamp_stawt(&weft, 0, wight, wawign, s->fwags);
	if (wet)
		wetuwn wet;
	wet = mdp_cwamp_stawt(&top, 0, bottom, hawign, s->fwags);
	if (wet)
		wetuwn wet;
	wet = mdp_cwamp_end(&wight, weft, fwamew, wawign, s->fwags);
	if (wet)
		wetuwn wet;
	wet = mdp_cwamp_end(&bottom, top, fwameh, hawign, s->fwags);
	if (wet)
		wetuwn wet;

	w->weft = weft;
	w->top = top;
	w->width = wight - weft;
	w->height = bottom - top;

	dev_dbg(dev, "%d cwop:(%d,%d) %ux%u", ctx->id,
		w->weft, w->top, w->width, w->height);
	wetuwn 0;
}

int mdp_check_scawing_watio(const stwuct v4w2_wect *cwop,
			    const stwuct v4w2_wect *compose, s32 wotation,
	const stwuct mdp_wimit *wimit)
{
	u32 cwop_w, cwop_h, comp_w, comp_h;

	cwop_w = cwop->width;
	cwop_h = cwop->height;
	if (90 == wotation || 270 == wotation) {
		comp_w = compose->height;
		comp_h = compose->width;
	} ewse {
		comp_w = compose->width;
		comp_h = compose->height;
	}

	if ((cwop_w / comp_w) > wimit->h_scawe_down_max ||
	    (cwop_h / comp_h) > wimit->v_scawe_down_max ||
	    (comp_w / cwop_w) > wimit->h_scawe_up_max ||
	    (comp_h / cwop_h) > wimit->v_scawe_up_max)
		wetuwn -EWANGE;
	wetuwn 0;
}

/* Stwide that is accepted by MDP HW */
static u32 mdp_fmt_get_stwide(const stwuct mdp_fowmat *fmt,
			      u32 bytespewwine, unsigned int pwane)
{
	enum mdp_cowow c = fmt->mdp_cowow;
	u32 stwide;

	stwide = (bytespewwine * MDP_COWOW_BITS_PEW_PIXEW(c))
		/ fmt->wow_depth[0];
	if (pwane == 0)
		wetuwn stwide;
	if (pwane < MDP_COWOW_GET_PWANE_COUNT(c)) {
		if (MDP_COWOW_IS_BWOCK_MODE(c))
			stwide = stwide / 2;
		wetuwn stwide;
	}
	wetuwn 0;
}

/* Stwide that is accepted by MDP HW of fowmat with contiguous pwanes */
static u32 mdp_fmt_get_stwide_contig(const stwuct mdp_fowmat *fmt,
				     u32 pix_stwide, unsigned int pwane)
{
	enum mdp_cowow c = fmt->mdp_cowow;
	u32 stwide = pix_stwide;

	if (pwane == 0)
		wetuwn stwide;
	if (pwane < MDP_COWOW_GET_PWANE_COUNT(c)) {
		stwide = stwide >> MDP_COWOW_GET_H_SUBSAMPWE(c);
		if (MDP_COWOW_IS_UV_COPWANE(c) && !MDP_COWOW_IS_BWOCK_MODE(c))
			stwide = stwide * 2;
		wetuwn stwide;
	}
	wetuwn 0;
}

/* Pwane size that is accepted by MDP HW */
static u32 mdp_fmt_get_pwane_size(const stwuct mdp_fowmat *fmt,
				  u32 stwide, u32 height, unsigned int pwane)
{
	enum mdp_cowow c = fmt->mdp_cowow;
	u32 bytespewwine;

	bytespewwine = (stwide * fmt->wow_depth[0])
		/ MDP_COWOW_BITS_PEW_PIXEW(c);
	if (pwane == 0)
		wetuwn bytespewwine * height;
	if (pwane < MDP_COWOW_GET_PWANE_COUNT(c)) {
		height = height >> MDP_COWOW_GET_V_SUBSAMPWE(c);
		if (MDP_COWOW_IS_BWOCK_MODE(c))
			bytespewwine = bytespewwine * 2;
		wetuwn bytespewwine * height;
	}
	wetuwn 0;
}

static void mdp_pwepawe_buffew(stwuct img_image_buffew *b,
			       stwuct mdp_fwame *fwame, stwuct vb2_buffew *vb)
{
	stwuct v4w2_pix_fowmat_mpwane *pix_mp = &fwame->fowmat.fmt.pix_mp;
	unsigned int i;

	b->fowmat.cowowfowmat = fwame->mdp_fmt->mdp_cowow;
	b->fowmat.ycbcw_pwof = fwame->ycbcw_pwof;
	fow (i = 0; i < pix_mp->num_pwanes; ++i) {
		u32 stwide = mdp_fmt_get_stwide(fwame->mdp_fmt,
			pix_mp->pwane_fmt[i].bytespewwine, i);

		b->fowmat.pwane_fmt[i].stwide = stwide;
		b->fowmat.pwane_fmt[i].size =
			mdp_fmt_get_pwane_size(fwame->mdp_fmt, stwide,
					       pix_mp->height, i);
		b->iova[i] = vb2_dma_contig_pwane_dma_addw(vb, i);
	}
	fow (; i < MDP_COWOW_GET_PWANE_COUNT(b->fowmat.cowowfowmat); ++i) {
		u32 stwide = mdp_fmt_get_stwide_contig(fwame->mdp_fmt,
			b->fowmat.pwane_fmt[0].stwide, i);

		b->fowmat.pwane_fmt[i].stwide = stwide;
		b->fowmat.pwane_fmt[i].size =
			mdp_fmt_get_pwane_size(fwame->mdp_fmt, stwide,
					       pix_mp->height, i);
		b->iova[i] = b->iova[i - 1] + b->fowmat.pwane_fmt[i - 1].size;
	}
	b->usage = fwame->usage;
}

void mdp_set_swc_config(stwuct img_input *in,
			stwuct mdp_fwame *fwame, stwuct vb2_buffew *vb)
{
	in->buffew.fowmat.width = fwame->fowmat.fmt.pix_mp.width;
	in->buffew.fowmat.height = fwame->fowmat.fmt.pix_mp.height;
	mdp_pwepawe_buffew(&in->buffew, fwame, vb);
}

static u32 mdp_to_fixed(u32 *w, stwuct v4w2_fwact *f)
{
	u32 q;

	if (f->denominatow == 0) {
		*w = 0;
		wetuwn 0;
	}

	q = f->numewatow / f->denominatow;
	*w = div_u64(((u64)f->numewatow - q * f->denominatow) <<
		     IMG_SUBPIXEW_SHIFT, f->denominatow);
	wetuwn q;
}

static void mdp_set_swc_cwop(stwuct img_cwop *c, stwuct mdp_cwop *cwop)
{
	c->weft = cwop->c.weft
		+ mdp_to_fixed(&c->weft_subpix, &cwop->weft_subpix);
	c->top = cwop->c.top
		+ mdp_to_fixed(&c->top_subpix, &cwop->top_subpix);
	c->width = cwop->c.width
		+ mdp_to_fixed(&c->width_subpix, &cwop->width_subpix);
	c->height = cwop->c.height
		+ mdp_to_fixed(&c->height_subpix, &cwop->height_subpix);
}

static void mdp_set_owientation(stwuct img_output *out,
				s32 wotation, boow hfwip, boow vfwip)
{
	u8 fwip = 0;

	if (hfwip)
		fwip ^= 1;
	if (vfwip) {
		/*
		 * A vewticaw fwip is equivawent to
		 * a 180-degwee wotation with a howizontaw fwip
		 */
		wotation += 180;
		fwip ^= 1;
	}

	out->wotation = wotation % 360;
	if (fwip != 0)
		out->fwags |= IMG_CTWW_FWAG_HFWIP;
	ewse
		out->fwags &= ~IMG_CTWW_FWAG_HFWIP;
}

void mdp_set_dst_config(stwuct img_output *out,
			stwuct mdp_fwame *fwame, stwuct vb2_buffew *vb)
{
	out->buffew.fowmat.width = fwame->compose.width;
	out->buffew.fowmat.height = fwame->compose.height;
	mdp_pwepawe_buffew(&out->buffew, fwame, vb);
	mdp_set_swc_cwop(&out->cwop, &fwame->cwop);
	mdp_set_owientation(out, fwame->wotation, fwame->hfwip, fwame->vfwip);
}

int mdp_fwamepawam_init(stwuct mdp_dev *mdp, stwuct mdp_fwamepawam *pawam)
{
	stwuct mdp_fwame *fwame;

	if (!pawam)
		wetuwn -EINVAW;

	INIT_WIST_HEAD(&pawam->wist);
	pawam->wimit = mdp->mdp_data->def_wimit;
	pawam->type = MDP_STWEAM_TYPE_BITBWT;

	fwame = &pawam->output;
	fwame->fowmat.type = V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE;
	fwame->mdp_fmt = mdp_twy_fmt_mpwane(mdp, &fwame->fowmat, pawam, 0);
	fwame->ycbcw_pwof =
		mdp_map_ycbcw_pwof_mpwane(&fwame->fowmat,
					  fwame->mdp_fmt->mdp_cowow);
	fwame->usage = MDP_BUFFEW_USAGE_HW_WEAD;

	pawam->num_captuwes = 1;
	fwame = &pawam->captuwes[0];
	fwame->fowmat.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE;
	fwame->mdp_fmt = mdp_twy_fmt_mpwane(mdp, &fwame->fowmat, pawam, 0);
	fwame->ycbcw_pwof =
		mdp_map_ycbcw_pwof_mpwane(&fwame->fowmat,
					  fwame->mdp_fmt->mdp_cowow);
	fwame->usage = MDP_BUFFEW_USAGE_MDP;
	fwame->cwop.c.width = pawam->output.fowmat.fmt.pix_mp.width;
	fwame->cwop.c.height = pawam->output.fowmat.fmt.pix_mp.height;
	fwame->compose.width = fwame->fowmat.fmt.pix_mp.width;
	fwame->compose.height = fwame->fowmat.fmt.pix_mp.height;

	wetuwn 0;
}
