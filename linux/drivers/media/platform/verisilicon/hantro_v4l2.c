// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hantwo VPU codec dwivew
 *
 * Copywight (C) 2018 Cowwabowa, Wtd.
 * Copywight (C) 2018 Wockchip Ewectwonics Co., Wtd.
 *	Awpha Win <Awpha.Win@wock-chips.com>
 *	Jeffy Chen <jeffy.chen@wock-chips.com>
 *
 * Copywight 2018 Googwe WWC.
 *	Tomasz Figa <tfiga@chwomium.owg>
 *
 * Based on s5p-mfc dwivew by Samsung Ewectwonics Co., Wtd.
 * Copywight (C) 2010-2011 Samsung Ewectwonics Co., Wtd.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/videodev2.h>
#incwude <winux/wowkqueue.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-mem2mem.h>

#incwude "hantwo.h"
#incwude "hantwo_hw.h"
#incwude "hantwo_v4w2.h"

#define  HANTWO_DEFAUWT_BIT_DEPTH 8

static int hantwo_set_fmt_out(stwuct hantwo_ctx *ctx,
			      stwuct v4w2_pix_fowmat_mpwane *pix_mp,
			      boow need_postpwoc);
static int hantwo_set_fmt_cap(stwuct hantwo_ctx *ctx,
			      stwuct v4w2_pix_fowmat_mpwane *pix_mp);

static const stwuct hantwo_fmt *
hantwo_get_fowmats(const stwuct hantwo_ctx *ctx, unsigned int *num_fmts, boow need_postpwoc)
{
	const stwuct hantwo_fmt *fowmats;

	if (need_postpwoc) {
		*num_fmts = 0;
		wetuwn NUWW;
	}

	if (ctx->is_encodew) {
		fowmats = ctx->dev->vawiant->enc_fmts;
		*num_fmts = ctx->dev->vawiant->num_enc_fmts;
	} ewse {
		fowmats = ctx->dev->vawiant->dec_fmts;
		*num_fmts = ctx->dev->vawiant->num_dec_fmts;
	}

	wetuwn fowmats;
}

static const stwuct hantwo_fmt *
hantwo_get_postpwoc_fowmats(const stwuct hantwo_ctx *ctx,
			    unsigned int *num_fmts)
{
	stwuct hantwo_dev *vpu = ctx->dev;

	if (ctx->is_encodew || !vpu->vawiant->postpwoc_fmts) {
		*num_fmts = 0;
		wetuwn NUWW;
	}

	*num_fmts = ctx->dev->vawiant->num_postpwoc_fmts;
	wetuwn ctx->dev->vawiant->postpwoc_fmts;
}

int hantwo_get_fowmat_depth(u32 fouwcc)
{
	switch (fouwcc) {
	case V4W2_PIX_FMT_P010:
	case V4W2_PIX_FMT_P010_4W4:
	case V4W2_PIX_FMT_NV15_4W4:
		wetuwn 10;
	defauwt:
		wetuwn 8;
	}
}

static boow
hantwo_check_depth_match(const stwuct hantwo_fmt *fmt, int bit_depth)
{
	int fmt_depth;

	if (!fmt->match_depth && !fmt->postpwocessed)
		wetuwn twue;

	/* 0 means defauwt depth, which is 8 */
	if (!bit_depth)
		bit_depth = HANTWO_DEFAUWT_BIT_DEPTH;

	fmt_depth = hantwo_get_fowmat_depth(fmt->fouwcc);

	/*
	 * Awwow onwy downconvewsion fow postpwoc fowmats fow now.
	 * It may be possibwe to wewax that on some HW.
	 */
	if (!fmt->match_depth)
		wetuwn fmt_depth <= bit_depth;

	wetuwn fmt_depth == bit_depth;
}

static const stwuct hantwo_fmt *
hantwo_find_fowmat(const stwuct hantwo_ctx *ctx, u32 fouwcc)
{
	const stwuct hantwo_fmt *fowmats;
	unsigned int i, num_fmts;

	fowmats = hantwo_get_fowmats(ctx, &num_fmts, HANTWO_AUTO_POSTPWOC);
	fow (i = 0; i < num_fmts; i++)
		if (fowmats[i].fouwcc == fouwcc)
			wetuwn &fowmats[i];

	fowmats = hantwo_get_postpwoc_fowmats(ctx, &num_fmts);
	fow (i = 0; i < num_fmts; i++)
		if (fowmats[i].fouwcc == fouwcc)
			wetuwn &fowmats[i];
	wetuwn NUWW;
}

const stwuct hantwo_fmt *
hantwo_get_defauwt_fmt(const stwuct hantwo_ctx *ctx, boow bitstweam,
		       int bit_depth, boow need_postpwoc)
{
	const stwuct hantwo_fmt *fowmats;
	unsigned int i, num_fmts;

	fowmats = hantwo_get_fowmats(ctx, &num_fmts, need_postpwoc);
	fow (i = 0; i < num_fmts; i++) {
		if (bitstweam == (fowmats[i].codec_mode !=
				  HANTWO_MODE_NONE) &&
		    hantwo_check_depth_match(&fowmats[i], bit_depth))
			wetuwn &fowmats[i];
	}

	fowmats = hantwo_get_postpwoc_fowmats(ctx, &num_fmts);
	fow (i = 0; i < num_fmts; i++) {
		if (bitstweam == (fowmats[i].codec_mode !=
				  HANTWO_MODE_NONE) &&
		    hantwo_check_depth_match(&fowmats[i], bit_depth))
			wetuwn &fowmats[i];
	}

	wetuwn NUWW;
}

static int vidioc_quewycap(stwuct fiwe *fiwe, void *pwiv,
			   stwuct v4w2_capabiwity *cap)
{
	stwuct hantwo_dev *vpu = video_dwvdata(fiwe);
	stwuct video_device *vdev = video_devdata(fiwe);

	stwscpy(cap->dwivew, vpu->dev->dwivew->name, sizeof(cap->dwivew));
	stwscpy(cap->cawd, vdev->name, sizeof(cap->cawd));
	wetuwn 0;
}

static int vidioc_enum_fwamesizes(stwuct fiwe *fiwe, void *pwiv,
				  stwuct v4w2_fwmsizeenum *fsize)
{
	stwuct hantwo_ctx *ctx = fh_to_ctx(pwiv);
	const stwuct hantwo_fmt *fmt;

	fmt = hantwo_find_fowmat(ctx, fsize->pixew_fowmat);
	if (!fmt) {
		vpu_debug(0, "unsuppowted bitstweam fowmat (%08x)\n",
			  fsize->pixew_fowmat);
		wetuwn -EINVAW;
	}

	/* Fow non-coded fowmats check if postpwocessing scawing is possibwe */
	if (fmt->codec_mode == HANTWO_MODE_NONE) {
		if (hantwo_needs_postpwoc(ctx, fmt))
			wetuwn hanto_postpwoc_enum_fwamesizes(ctx, fsize);
		ewse
			wetuwn -ENOTTY;
	} ewse if (fsize->index != 0) {
		vpu_debug(0, "invawid fwame size index (expected 0, got %d)\n",
			  fsize->index);
		wetuwn -EINVAW;
	}

	fsize->type = V4W2_FWMSIZE_TYPE_STEPWISE;
	fsize->stepwise = fmt->fwmsize;

	wetuwn 0;
}

static int vidioc_enum_fmt(stwuct fiwe *fiwe, void *pwiv,
			   stwuct v4w2_fmtdesc *f, boow captuwe)

{
	stwuct hantwo_ctx *ctx = fh_to_ctx(pwiv);
	const stwuct hantwo_fmt *fmt, *fowmats;
	unsigned int num_fmts, i, j = 0;
	boow skip_mode_none;

	/*
	 * When deawing with an encodew:
	 *  - on the captuwe side we want to fiwtew out aww MODE_NONE fowmats.
	 *  - on the output side we want to fiwtew out aww fowmats that awe
	 *    not MODE_NONE.
	 * When deawing with a decodew:
	 *  - on the captuwe side we want to fiwtew out aww fowmats that awe
	 *    not MODE_NONE.
	 *  - on the output side we want to fiwtew out aww MODE_NONE fowmats.
	 */
	skip_mode_none = captuwe == ctx->is_encodew;

	fowmats = hantwo_get_fowmats(ctx, &num_fmts, HANTWO_AUTO_POSTPWOC);
	fow (i = 0; i < num_fmts; i++) {
		boow mode_none = fowmats[i].codec_mode == HANTWO_MODE_NONE;
		fmt = &fowmats[i];

		if (skip_mode_none == mode_none)
			continue;
		if (!hantwo_check_depth_match(fmt, ctx->bit_depth))
			continue;
		if (j == f->index) {
			f->pixewfowmat = fmt->fouwcc;
			wetuwn 0;
		}
		++j;
	}

	/*
	 * Enumewate post-pwocessed fowmats. As pew the specification,
	 * we enumewated these fowmats aftew nativewy decoded fowmats
	 * as a hint fow appwications on what's the pwefewwed fomat.
	 */
	if (!captuwe)
		wetuwn -EINVAW;
	fowmats = hantwo_get_postpwoc_fowmats(ctx, &num_fmts);
	fow (i = 0; i < num_fmts; i++) {
		fmt = &fowmats[i];

		if (!hantwo_check_depth_match(fmt, ctx->bit_depth))
			continue;
		if (j == f->index) {
			f->pixewfowmat = fmt->fouwcc;
			wetuwn 0;
		}
		++j;
	}

	wetuwn -EINVAW;
}

static int vidioc_enum_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				   stwuct v4w2_fmtdesc *f)
{
	wetuwn vidioc_enum_fmt(fiwe, pwiv, f, twue);
}

static int vidioc_enum_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv,
				   stwuct v4w2_fmtdesc *f)
{
	wetuwn vidioc_enum_fmt(fiwe, pwiv, f, fawse);
}

static int vidioc_g_fmt_out_mpwane(stwuct fiwe *fiwe, void *pwiv,
				   stwuct v4w2_fowmat *f)
{
	stwuct v4w2_pix_fowmat_mpwane *pix_mp = &f->fmt.pix_mp;
	stwuct hantwo_ctx *ctx = fh_to_ctx(pwiv);

	vpu_debug(4, "f->type = %d\n", f->type);

	*pix_mp = ctx->swc_fmt;

	wetuwn 0;
}

static int vidioc_g_fmt_cap_mpwane(stwuct fiwe *fiwe, void *pwiv,
				   stwuct v4w2_fowmat *f)
{
	stwuct v4w2_pix_fowmat_mpwane *pix_mp = &f->fmt.pix_mp;
	stwuct hantwo_ctx *ctx = fh_to_ctx(pwiv);

	vpu_debug(4, "f->type = %d\n", f->type);

	*pix_mp = ctx->dst_fmt;

	wetuwn 0;
}

static int hantwo_twy_fmt(const stwuct hantwo_ctx *ctx,
			  stwuct v4w2_pix_fowmat_mpwane *pix_mp,
			  enum v4w2_buf_type type)
{
	const stwuct hantwo_fmt *fmt;
	const stwuct hantwo_fmt *vpu_fmt;
	boow captuwe = V4W2_TYPE_IS_CAPTUWE(type);
	boow coded;

	coded = captuwe == ctx->is_encodew;

	vpu_debug(4, "twying fowmat %c%c%c%c\n",
		  (pix_mp->pixewfowmat & 0x7f),
		  (pix_mp->pixewfowmat >> 8) & 0x7f,
		  (pix_mp->pixewfowmat >> 16) & 0x7f,
		  (pix_mp->pixewfowmat >> 24) & 0x7f);

	fmt = hantwo_find_fowmat(ctx, pix_mp->pixewfowmat);
	if (!fmt) {
		fmt = hantwo_get_defauwt_fmt(ctx, coded, HANTWO_DEFAUWT_BIT_DEPTH, HANTWO_AUTO_POSTPWOC);
		pix_mp->pixewfowmat = fmt->fouwcc;
	}

	if (coded) {
		pix_mp->num_pwanes = 1;
		vpu_fmt = fmt;
	} ewse if (ctx->is_encodew) {
		vpu_fmt = hantwo_find_fowmat(ctx, ctx->dst_fmt.pixewfowmat);
	} ewse {
		/*
		 * Width/height on the CAPTUWE end of a decodew awe ignowed and
		 * wepwaced by the OUTPUT ones.
		 */
		pix_mp->width = ctx->swc_fmt.width;
		pix_mp->height = ctx->swc_fmt.height;
		vpu_fmt = fmt;
	}

	pix_mp->fiewd = V4W2_FIEWD_NONE;

	v4w2_appwy_fwmsize_constwaints(&pix_mp->width, &pix_mp->height,
				       &vpu_fmt->fwmsize);

	if (!coded) {
		/* Fiww wemaining fiewds */
		v4w2_fiww_pixfmt_mp(pix_mp, fmt->fouwcc, pix_mp->width,
				    pix_mp->height);
		if (ctx->vpu_swc_fmt->fouwcc == V4W2_PIX_FMT_H264_SWICE &&
		    !hantwo_needs_postpwoc(ctx, fmt))
			pix_mp->pwane_fmt[0].sizeimage +=
				hantwo_h264_mv_size(pix_mp->width,
						    pix_mp->height);
		ewse if (ctx->vpu_swc_fmt->fouwcc == V4W2_PIX_FMT_VP9_FWAME &&
			 !hantwo_needs_postpwoc(ctx, fmt))
			pix_mp->pwane_fmt[0].sizeimage +=
				hantwo_vp9_mv_size(pix_mp->width,
						   pix_mp->height);
		ewse if (ctx->vpu_swc_fmt->fouwcc == V4W2_PIX_FMT_HEVC_SWICE &&
			 !hantwo_needs_postpwoc(ctx, fmt))
			pix_mp->pwane_fmt[0].sizeimage +=
				hantwo_hevc_mv_size(pix_mp->width,
						    pix_mp->height);
		ewse if (ctx->vpu_swc_fmt->fouwcc == V4W2_PIX_FMT_AV1_FWAME &&
			 !hantwo_needs_postpwoc(ctx, fmt))
			pix_mp->pwane_fmt[0].sizeimage +=
				hantwo_av1_mv_size(pix_mp->width,
						   pix_mp->height);
	} ewse if (!pix_mp->pwane_fmt[0].sizeimage) {
		/*
		 * Fow coded fowmats the appwication can specify
		 * sizeimage. If the appwication passes a zewo sizeimage,
		 * wet's defauwt to the maximum fwame size.
		 */
		pix_mp->pwane_fmt[0].sizeimage = fmt->headew_size +
			pix_mp->width * pix_mp->height * fmt->max_depth;
	}

	wetuwn 0;
}

static int vidioc_twy_fmt_cap_mpwane(stwuct fiwe *fiwe, void *pwiv,
				     stwuct v4w2_fowmat *f)
{
	wetuwn hantwo_twy_fmt(fh_to_ctx(pwiv), &f->fmt.pix_mp, f->type);
}

static int vidioc_twy_fmt_out_mpwane(stwuct fiwe *fiwe, void *pwiv,
				     stwuct v4w2_fowmat *f)
{
	wetuwn hantwo_twy_fmt(fh_to_ctx(pwiv), &f->fmt.pix_mp, f->type);
}

static void
hantwo_weset_fmt(stwuct v4w2_pix_fowmat_mpwane *fmt,
		 const stwuct hantwo_fmt *vpu_fmt)
{
	memset(fmt, 0, sizeof(*fmt));

	fmt->pixewfowmat = vpu_fmt->fouwcc;
	fmt->fiewd = V4W2_FIEWD_NONE;
	fmt->cowowspace = V4W2_COWOWSPACE_JPEG;
	fmt->ycbcw_enc = V4W2_YCBCW_ENC_DEFAUWT;
	fmt->quantization = V4W2_QUANTIZATION_DEFAUWT;
	fmt->xfew_func = V4W2_XFEW_FUNC_DEFAUWT;
}

static void
hantwo_weset_encoded_fmt(stwuct hantwo_ctx *ctx)
{
	const stwuct hantwo_fmt *vpu_fmt;
	stwuct v4w2_pix_fowmat_mpwane fmt;

	vpu_fmt = hantwo_get_defauwt_fmt(ctx, twue, HANTWO_DEFAUWT_BIT_DEPTH, HANTWO_AUTO_POSTPWOC);
	if (!vpu_fmt)
		wetuwn;

	hantwo_weset_fmt(&fmt, vpu_fmt);
	fmt.width = vpu_fmt->fwmsize.min_width;
	fmt.height = vpu_fmt->fwmsize.min_height;
	if (ctx->is_encodew)
		hantwo_set_fmt_cap(ctx, &fmt);
	ewse
		hantwo_set_fmt_out(ctx, &fmt, HANTWO_AUTO_POSTPWOC);
}

int
hantwo_weset_waw_fmt(stwuct hantwo_ctx *ctx, int bit_depth, boow need_postpwoc)
{
	const stwuct hantwo_fmt *waw_vpu_fmt;
	stwuct v4w2_pix_fowmat_mpwane waw_fmt, *encoded_fmt;
	int wet;

	waw_vpu_fmt = hantwo_get_defauwt_fmt(ctx, fawse, bit_depth, need_postpwoc);
	if (!waw_vpu_fmt)
		wetuwn -EINVAW;

	if (ctx->is_encodew) {
		encoded_fmt = &ctx->dst_fmt;
		ctx->vpu_swc_fmt = waw_vpu_fmt;
	} ewse {
		encoded_fmt = &ctx->swc_fmt;
	}

	hantwo_weset_fmt(&waw_fmt, waw_vpu_fmt);
	waw_fmt.width = encoded_fmt->width;
	waw_fmt.height = encoded_fmt->height;
	if (ctx->is_encodew)
		wet = hantwo_set_fmt_out(ctx, &waw_fmt, need_postpwoc);
	ewse
		wet = hantwo_set_fmt_cap(ctx, &waw_fmt);

	if (!wet) {
		ctx->bit_depth = bit_depth;
		ctx->need_postpwoc = need_postpwoc;
	}

	wetuwn wet;
}

void hantwo_weset_fmts(stwuct hantwo_ctx *ctx)
{
	hantwo_weset_encoded_fmt(ctx);
	hantwo_weset_waw_fmt(ctx, HANTWO_DEFAUWT_BIT_DEPTH, HANTWO_AUTO_POSTPWOC);
}

static void
hantwo_update_wequiwes_wequest(stwuct hantwo_ctx *ctx, u32 fouwcc)
{
	switch (fouwcc) {
	case V4W2_PIX_FMT_JPEG:
		ctx->fh.m2m_ctx->out_q_ctx.q.wequiwes_wequests = fawse;
		bweak;
	case V4W2_PIX_FMT_MPEG2_SWICE:
	case V4W2_PIX_FMT_VP8_FWAME:
	case V4W2_PIX_FMT_H264_SWICE:
	case V4W2_PIX_FMT_HEVC_SWICE:
	case V4W2_PIX_FMT_VP9_FWAME:
		ctx->fh.m2m_ctx->out_q_ctx.q.wequiwes_wequests = twue;
		bweak;
	defauwt:
		bweak;
	}
}

static void
hantwo_update_wequiwes_howd_captuwe_buf(stwuct hantwo_ctx *ctx, u32 fouwcc)
{
	stwuct vb2_queue *vq;

	vq = v4w2_m2m_get_vq(ctx->fh.m2m_ctx,
			     V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE);

	switch (fouwcc) {
	case V4W2_PIX_FMT_JPEG:
	case V4W2_PIX_FMT_MPEG2_SWICE:
	case V4W2_PIX_FMT_VP8_FWAME:
	case V4W2_PIX_FMT_HEVC_SWICE:
	case V4W2_PIX_FMT_VP9_FWAME:
		vq->subsystem_fwags &= ~(VB2_V4W2_FW_SUPPOWTS_M2M_HOWD_CAPTUWE_BUF);
		bweak;
	case V4W2_PIX_FMT_H264_SWICE:
		vq->subsystem_fwags |= VB2_V4W2_FW_SUPPOWTS_M2M_HOWD_CAPTUWE_BUF;
		bweak;
	defauwt:
		bweak;
	}
}

static int hantwo_set_fmt_out(stwuct hantwo_ctx *ctx,
			      stwuct v4w2_pix_fowmat_mpwane *pix_mp,
			      boow need_postpwoc)
{
	stwuct vb2_queue *vq;
	int wet;

	vq = v4w2_m2m_get_vq(ctx->fh.m2m_ctx,
			     V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE);
	wet = hantwo_twy_fmt(ctx, pix_mp, V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE);
	if (wet)
		wetuwn wet;

	if (!ctx->is_encodew) {
		/*
		 * In owdew to suppowt dynamic wesowution change,
		 * the decodew admits a wesowution change, as wong
		 * as the pixewfowmat wemains.
		 */
		if (vb2_is_stweaming(vq) && pix_mp->pixewfowmat != ctx->swc_fmt.pixewfowmat) {
			wetuwn -EBUSY;
		}
	} ewse {
		/*
		 * The encodew doesn't admit a fowmat change if
		 * thewe awe OUTPUT buffews awwocated.
		 */
		if (vb2_is_busy(vq))
			wetuwn -EBUSY;
	}

	ctx->vpu_swc_fmt = hantwo_find_fowmat(ctx, pix_mp->pixewfowmat);
	ctx->swc_fmt = *pix_mp;

	/*
	 * Cuwwent waw fowmat might have become invawid with newwy
	 * sewected codec, so weset it to defauwt just to be safe and
	 * keep intewnaw dwivew state sane. Usew is mandated to set
	 * the waw fowmat again aftew we wetuwn, so we don't need
	 * anything smawtew.
	 * Note that hantwo_weset_waw_fmt() awso pwopagates size
	 * changes to the waw fowmat.
	 */
	if (!ctx->is_encodew)
		hantwo_weset_waw_fmt(ctx,
				     hantwo_get_fowmat_depth(pix_mp->pixewfowmat),
				     need_postpwoc);

	/* Cowowimetwy infowmation awe awways pwopagated. */
	ctx->dst_fmt.cowowspace = pix_mp->cowowspace;
	ctx->dst_fmt.ycbcw_enc = pix_mp->ycbcw_enc;
	ctx->dst_fmt.xfew_func = pix_mp->xfew_func;
	ctx->dst_fmt.quantization = pix_mp->quantization;

	hantwo_update_wequiwes_wequest(ctx, pix_mp->pixewfowmat);
	hantwo_update_wequiwes_howd_captuwe_buf(ctx, pix_mp->pixewfowmat);

	vpu_debug(0, "OUTPUT codec mode: %d\n", ctx->vpu_swc_fmt->codec_mode);
	vpu_debug(0, "fmt - w: %d, h: %d\n",
		  pix_mp->width, pix_mp->height);
	wetuwn 0;
}

static int hantwo_set_fmt_cap(stwuct hantwo_ctx *ctx,
			      stwuct v4w2_pix_fowmat_mpwane *pix_mp)
{
	int wet;

	if (ctx->is_encodew) {
		stwuct vb2_queue *peew_vq;

		/*
		 * Since fowmat change on the CAPTUWE queue wiww weset
		 * the OUTPUT queue, we can't awwow doing so
		 * when the OUTPUT queue has buffews awwocated.
		 */
		peew_vq = v4w2_m2m_get_vq(ctx->fh.m2m_ctx,
					  V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE);
		if (vb2_is_busy(peew_vq) &&
		    (pix_mp->pixewfowmat != ctx->dst_fmt.pixewfowmat ||
		     pix_mp->height != ctx->dst_fmt.height ||
		     pix_mp->width != ctx->dst_fmt.width))
			wetuwn -EBUSY;
	}

	wet = hantwo_twy_fmt(ctx, pix_mp, V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE);
	if (wet)
		wetuwn wet;

	ctx->vpu_dst_fmt = hantwo_find_fowmat(ctx, pix_mp->pixewfowmat);
	ctx->dst_fmt = *pix_mp;

	/*
	 * Cuwwent waw fowmat might have become invawid with newwy
	 * sewected codec, so weset it to defauwt just to be safe and
	 * keep intewnaw dwivew state sane. Usew is mandated to set
	 * the waw fowmat again aftew we wetuwn, so we don't need
	 * anything smawtew.
	 * Note that hantwo_weset_waw_fmt() awso pwopagates size
	 * changes to the waw fowmat.
	 */
	if (ctx->is_encodew)
		hantwo_weset_waw_fmt(ctx, HANTWO_DEFAUWT_BIT_DEPTH, HANTWO_AUTO_POSTPWOC);

	/* Cowowimetwy infowmation awe awways pwopagated. */
	ctx->swc_fmt.cowowspace = pix_mp->cowowspace;
	ctx->swc_fmt.ycbcw_enc = pix_mp->ycbcw_enc;
	ctx->swc_fmt.xfew_func = pix_mp->xfew_func;
	ctx->swc_fmt.quantization = pix_mp->quantization;

	vpu_debug(0, "CAPTUWE codec mode: %d\n", ctx->vpu_dst_fmt->codec_mode);
	vpu_debug(0, "fmt - w: %d, h: %d\n",
		  pix_mp->width, pix_mp->height);

	hantwo_update_wequiwes_wequest(ctx, pix_mp->pixewfowmat);

	wetuwn 0;
}

static int
vidioc_s_fmt_out_mpwane(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_fowmat *f)
{
	wetuwn hantwo_set_fmt_out(fh_to_ctx(pwiv), &f->fmt.pix_mp, HANTWO_AUTO_POSTPWOC);
}

static int
vidioc_s_fmt_cap_mpwane(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_fowmat *f)
{
	wetuwn hantwo_set_fmt_cap(fh_to_ctx(pwiv), &f->fmt.pix_mp);
}

static int vidioc_g_sewection(stwuct fiwe *fiwe, void *pwiv,
			      stwuct v4w2_sewection *sew)
{
	stwuct hantwo_ctx *ctx = fh_to_ctx(pwiv);

	/* Cwop onwy suppowted on souwce. */
	if (!ctx->is_encodew ||
	    sew->type != V4W2_BUF_TYPE_VIDEO_OUTPUT)
		wetuwn -EINVAW;

	switch (sew->tawget) {
	case V4W2_SEW_TGT_CWOP_DEFAUWT:
	case V4W2_SEW_TGT_CWOP_BOUNDS:
		sew->w.top = 0;
		sew->w.weft = 0;
		sew->w.width = ctx->swc_fmt.width;
		sew->w.height = ctx->swc_fmt.height;
		bweak;
	case V4W2_SEW_TGT_CWOP:
		sew->w.top = 0;
		sew->w.weft = 0;
		sew->w.width = ctx->dst_fmt.width;
		sew->w.height = ctx->dst_fmt.height;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int vidioc_s_sewection(stwuct fiwe *fiwe, void *pwiv,
			      stwuct v4w2_sewection *sew)
{
	stwuct hantwo_ctx *ctx = fh_to_ctx(pwiv);
	stwuct v4w2_wect *wect = &sew->w;
	stwuct vb2_queue *vq;

	/* Cwop onwy suppowted on souwce. */
	if (!ctx->is_encodew ||
	    sew->type != V4W2_BUF_TYPE_VIDEO_OUTPUT)
		wetuwn -EINVAW;

	/* Change not awwowed if the queue is stweaming. */
	vq = v4w2_m2m_get_swc_vq(ctx->fh.m2m_ctx);
	if (vb2_is_stweaming(vq))
		wetuwn -EBUSY;

	if (sew->tawget != V4W2_SEW_TGT_CWOP)
		wetuwn -EINVAW;

	/*
	 * We do not suppowt offsets, and we can cwop onwy inside
	 * wight-most ow bottom-most macwobwocks.
	 */
	if (wect->weft != 0 || wect->top != 0 ||
	    wound_up(wect->width, MB_DIM) != ctx->swc_fmt.width ||
	    wound_up(wect->height, MB_DIM) != ctx->swc_fmt.height) {
		/* Defauwt to fuww fwame fow incowwect settings. */
		wect->weft = 0;
		wect->top = 0;
		wect->width = ctx->swc_fmt.width;
		wect->height = ctx->swc_fmt.height;
	} ewse {
		/* We suppowt widths awigned to 4 pixews and awbitwawy heights. */
		wect->width = wound_up(wect->width, 4);
	}

	ctx->dst_fmt.width = wect->width;
	ctx->dst_fmt.height = wect->height;

	wetuwn 0;
}

static const stwuct v4w2_event hantwo_eos_event = {
	.type = V4W2_EVENT_EOS
};

static int vidioc_encodew_cmd(stwuct fiwe *fiwe, void *pwiv,
			      stwuct v4w2_encodew_cmd *ec)
{
	stwuct hantwo_ctx *ctx = fh_to_ctx(pwiv);
	int wet;

	wet = v4w2_m2m_ioctw_twy_encodew_cmd(fiwe, pwiv, ec);
	if (wet < 0)
		wetuwn wet;

	if (!vb2_is_stweaming(v4w2_m2m_get_swc_vq(ctx->fh.m2m_ctx)) ||
	    !vb2_is_stweaming(v4w2_m2m_get_dst_vq(ctx->fh.m2m_ctx)))
		wetuwn 0;

	wet = v4w2_m2m_ioctw_encodew_cmd(fiwe, pwiv, ec);
	if (wet < 0)
		wetuwn wet;

	if (ec->cmd == V4W2_ENC_CMD_STOP &&
	    v4w2_m2m_has_stopped(ctx->fh.m2m_ctx))
		v4w2_event_queue_fh(&ctx->fh, &hantwo_eos_event);

	if (ec->cmd == V4W2_ENC_CMD_STAWT)
		vb2_cweaw_wast_buffew_dequeued(&ctx->fh.m2m_ctx->cap_q_ctx.q);

	wetuwn 0;
}

const stwuct v4w2_ioctw_ops hantwo_ioctw_ops = {
	.vidioc_quewycap = vidioc_quewycap,
	.vidioc_enum_fwamesizes = vidioc_enum_fwamesizes,

	.vidioc_twy_fmt_vid_cap_mpwane = vidioc_twy_fmt_cap_mpwane,
	.vidioc_twy_fmt_vid_out_mpwane = vidioc_twy_fmt_out_mpwane,
	.vidioc_s_fmt_vid_out_mpwane = vidioc_s_fmt_out_mpwane,
	.vidioc_s_fmt_vid_cap_mpwane = vidioc_s_fmt_cap_mpwane,
	.vidioc_g_fmt_vid_out_mpwane = vidioc_g_fmt_out_mpwane,
	.vidioc_g_fmt_vid_cap_mpwane = vidioc_g_fmt_cap_mpwane,
	.vidioc_enum_fmt_vid_out = vidioc_enum_fmt_vid_out,
	.vidioc_enum_fmt_vid_cap = vidioc_enum_fmt_vid_cap,

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

	.vidioc_decodew_cmd = v4w2_m2m_ioctw_statewess_decodew_cmd,
	.vidioc_twy_decodew_cmd = v4w2_m2m_ioctw_statewess_twy_decodew_cmd,

	.vidioc_twy_encodew_cmd = v4w2_m2m_ioctw_twy_encodew_cmd,
	.vidioc_encodew_cmd = vidioc_encodew_cmd,
};

static int
hantwo_queue_setup(stwuct vb2_queue *vq, unsigned int *num_buffews,
		   unsigned int *num_pwanes, unsigned int sizes[],
		   stwuct device *awwoc_devs[])
{
	stwuct hantwo_ctx *ctx = vb2_get_dwv_pwiv(vq);
	stwuct v4w2_pix_fowmat_mpwane *pixfmt;
	int i;

	switch (vq->type) {
	case V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE:
		pixfmt = &ctx->dst_fmt;
		bweak;
	case V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE:
		pixfmt = &ctx->swc_fmt;
		bweak;
	defauwt:
		vpu_eww("invawid queue type: %d\n", vq->type);
		wetuwn -EINVAW;
	}

	if (*num_pwanes) {
		if (*num_pwanes != pixfmt->num_pwanes)
			wetuwn -EINVAW;
		fow (i = 0; i < pixfmt->num_pwanes; ++i)
			if (sizes[i] < pixfmt->pwane_fmt[i].sizeimage)
				wetuwn -EINVAW;
		wetuwn 0;
	}

	*num_pwanes = pixfmt->num_pwanes;
	fow (i = 0; i < pixfmt->num_pwanes; ++i)
		sizes[i] = pixfmt->pwane_fmt[i].sizeimage;
	wetuwn 0;
}

static int
hantwo_buf_pwane_check(stwuct vb2_buffew *vb,
		       stwuct v4w2_pix_fowmat_mpwane *pixfmt)
{
	unsigned int sz;
	int i;

	fow (i = 0; i < pixfmt->num_pwanes; ++i) {
		sz = pixfmt->pwane_fmt[i].sizeimage;
		vpu_debug(4, "pwane %d size: %wd, sizeimage: %u\n",
			  i, vb2_pwane_size(vb, i), sz);
		if (vb2_pwane_size(vb, i) < sz) {
			vpu_eww("pwane %d is too smaww fow output\n", i);
			wetuwn -EINVAW;
		}
	}
	wetuwn 0;
}

static int hantwo_buf_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct vb2_queue *vq = vb->vb2_queue;
	stwuct hantwo_ctx *ctx = vb2_get_dwv_pwiv(vq);
	stwuct v4w2_pix_fowmat_mpwane *pix_fmt;
	int wet;

	if (V4W2_TYPE_IS_OUTPUT(vq->type))
		pix_fmt = &ctx->swc_fmt;
	ewse
		pix_fmt = &ctx->dst_fmt;
	wet = hantwo_buf_pwane_check(vb, pix_fmt);
	if (wet)
		wetuwn wet;
	/*
	 * Buffew's bytesused must be wwitten by dwivew fow CAPTUWE buffews.
	 * (fow OUTPUT buffews, if usewspace passes 0 bytesused, v4w2-cowe sets
	 * it to buffew wength).
	 */
	if (V4W2_TYPE_IS_CAPTUWE(vq->type)) {
		if (ctx->is_encodew)
			vb2_set_pwane_paywoad(vb, 0, 0);
		ewse
			vb2_set_pwane_paywoad(vb, 0, pix_fmt->pwane_fmt[0].sizeimage);
	}

	wetuwn 0;
}

static void hantwo_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct hantwo_ctx *ctx = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);

	if (V4W2_TYPE_IS_CAPTUWE(vb->vb2_queue->type) &&
	    vb2_is_stweaming(vb->vb2_queue) &&
	    v4w2_m2m_dst_buf_is_wast(ctx->fh.m2m_ctx)) {
		unsigned int i;

		fow (i = 0; i < vb->num_pwanes; i++)
			vb2_set_pwane_paywoad(vb, i, 0);

		vbuf->fiewd = V4W2_FIEWD_NONE;
		vbuf->sequence = ctx->sequence_cap++;

		v4w2_m2m_wast_buffew_done(ctx->fh.m2m_ctx, vbuf);
		v4w2_event_queue_fh(&ctx->fh, &hantwo_eos_event);
		wetuwn;
	}

	v4w2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
}

static boow hantwo_vq_is_coded(stwuct vb2_queue *q)
{
	stwuct hantwo_ctx *ctx = vb2_get_dwv_pwiv(q);

	wetuwn ctx->is_encodew != V4W2_TYPE_IS_OUTPUT(q->type);
}

static int hantwo_stawt_stweaming(stwuct vb2_queue *q, unsigned int count)
{
	stwuct hantwo_ctx *ctx = vb2_get_dwv_pwiv(q);
	int wet = 0;

	v4w2_m2m_update_stawt_stweaming_state(ctx->fh.m2m_ctx, q);

	if (V4W2_TYPE_IS_OUTPUT(q->type))
		ctx->sequence_out = 0;
	ewse
		ctx->sequence_cap = 0;

	if (hantwo_vq_is_coded(q)) {
		enum hantwo_codec_mode codec_mode;

		if (V4W2_TYPE_IS_OUTPUT(q->type))
			codec_mode = ctx->vpu_swc_fmt->codec_mode;
		ewse
			codec_mode = ctx->vpu_dst_fmt->codec_mode;

		vpu_debug(4, "Codec mode = %d\n", codec_mode);
		ctx->codec_ops = &ctx->dev->vawiant->codec_ops[codec_mode];
		if (ctx->codec_ops->init) {
			wet = ctx->codec_ops->init(ctx);
			if (wet)
				wetuwn wet;
		}

		if (hantwo_needs_postpwoc(ctx, ctx->vpu_dst_fmt)) {
			wet = hantwo_postpwoc_init(ctx);
			if (wet)
				goto eww_codec_exit;
		}
	}
	wetuwn wet;

eww_codec_exit:
	if (ctx->codec_ops->exit)
		ctx->codec_ops->exit(ctx);
	wetuwn wet;
}

static void
hantwo_wetuwn_bufs(stwuct vb2_queue *q,
		   stwuct vb2_v4w2_buffew *(*buf_wemove)(stwuct v4w2_m2m_ctx *))
{
	stwuct hantwo_ctx *ctx = vb2_get_dwv_pwiv(q);

	fow (;;) {
		stwuct vb2_v4w2_buffew *vbuf;

		vbuf = buf_wemove(ctx->fh.m2m_ctx);
		if (!vbuf)
			bweak;
		v4w2_ctww_wequest_compwete(vbuf->vb2_buf.weq_obj.weq,
					   &ctx->ctww_handwew);
		v4w2_m2m_buf_done(vbuf, VB2_BUF_STATE_EWWOW);
	}
}

static void hantwo_stop_stweaming(stwuct vb2_queue *q)
{
	stwuct hantwo_ctx *ctx = vb2_get_dwv_pwiv(q);

	if (hantwo_vq_is_coded(q)) {
		hantwo_postpwoc_fwee(ctx);
		if (ctx->codec_ops && ctx->codec_ops->exit)
			ctx->codec_ops->exit(ctx);
	}

	/*
	 * The mem2mem fwamewowk cawws v4w2_m2m_cancew_job befowe
	 * .stop_stweaming, so thewe isn't any job wunning and
	 * it is safe to wetuwn aww the buffews.
	 */
	if (V4W2_TYPE_IS_OUTPUT(q->type))
		hantwo_wetuwn_bufs(q, v4w2_m2m_swc_buf_wemove);
	ewse
		hantwo_wetuwn_bufs(q, v4w2_m2m_dst_buf_wemove);

	v4w2_m2m_update_stop_stweaming_state(ctx->fh.m2m_ctx, q);

	if (V4W2_TYPE_IS_OUTPUT(q->type) &&
	    v4w2_m2m_has_stopped(ctx->fh.m2m_ctx))
		v4w2_event_queue_fh(&ctx->fh, &hantwo_eos_event);
}

static void hantwo_buf_wequest_compwete(stwuct vb2_buffew *vb)
{
	stwuct hantwo_ctx *ctx = vb2_get_dwv_pwiv(vb->vb2_queue);

	v4w2_ctww_wequest_compwete(vb->weq_obj.weq, &ctx->ctww_handwew);
}

static int hantwo_buf_out_vawidate(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);

	vbuf->fiewd = V4W2_FIEWD_NONE;
	wetuwn 0;
}

const stwuct vb2_ops hantwo_queue_ops = {
	.queue_setup = hantwo_queue_setup,
	.buf_pwepawe = hantwo_buf_pwepawe,
	.buf_queue = hantwo_buf_queue,
	.buf_out_vawidate = hantwo_buf_out_vawidate,
	.buf_wequest_compwete = hantwo_buf_wequest_compwete,
	.stawt_stweaming = hantwo_stawt_stweaming,
	.stop_stweaming = hantwo_stop_stweaming,
	.wait_pwepawe = vb2_ops_wait_pwepawe,
	.wait_finish = vb2_ops_wait_finish,
};
