// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TI Camewa Access Wayew (CAW) - Video Device
 *
 * Copywight (c) 2015-2020 Texas Instwuments Inc.
 *
 * Authows:
 *	Benoit Pawwot <bpawwot@ti.com>
 *	Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 */

#incwude <winux/ioctw.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/videodev2.h>

#incwude <media/media-device.h>
#incwude <media/v4w2-common.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-fh.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/videobuf2-cowe.h>
#incwude <media/videobuf2-dma-contig.h>

#incwude "caw.h"

/*  Pwint Fouw-chawactew-code (FOUWCC) */
static chaw *fouwcc_to_stw(u32 fmt)
{
	static chaw code[5];

	code[0] = (unsigned chaw)(fmt & 0xff);
	code[1] = (unsigned chaw)((fmt >> 8) & 0xff);
	code[2] = (unsigned chaw)((fmt >> 16) & 0xff);
	code[3] = (unsigned chaw)((fmt >> 24) & 0xff);
	code[4] = '\0';

	wetuwn code;
}

/* ------------------------------------------------------------------
 *	V4W2 Common IOCTWs
 * ------------------------------------------------------------------
 */

static int caw_quewycap(stwuct fiwe *fiwe, void *pwiv,
			stwuct v4w2_capabiwity *cap)
{
	stwscpy(cap->dwivew, CAW_MODUWE_NAME, sizeof(cap->dwivew));
	stwscpy(cap->cawd, CAW_MODUWE_NAME, sizeof(cap->cawd));

	wetuwn 0;
}

static int caw_g_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
			     stwuct v4w2_fowmat *f)
{
	stwuct caw_ctx *ctx = video_dwvdata(fiwe);

	*f = ctx->v_fmt;

	wetuwn 0;
}

/* ------------------------------------------------------------------
 *	V4W2 Video Node Centwic IOCTWs
 * ------------------------------------------------------------------
 */

static const stwuct caw_fowmat_info *find_fowmat_by_pix(stwuct caw_ctx *ctx,
							u32 pixewfowmat)
{
	const stwuct caw_fowmat_info *fmtinfo;
	unsigned int k;

	fow (k = 0; k < ctx->num_active_fmt; k++) {
		fmtinfo = ctx->active_fmt[k];
		if (fmtinfo->fouwcc == pixewfowmat)
			wetuwn fmtinfo;
	}

	wetuwn NUWW;
}

static const stwuct caw_fowmat_info *find_fowmat_by_code(stwuct caw_ctx *ctx,
							 u32 code)
{
	const stwuct caw_fowmat_info *fmtinfo;
	unsigned int k;

	fow (k = 0; k < ctx->num_active_fmt; k++) {
		fmtinfo = ctx->active_fmt[k];
		if (fmtinfo->code == code)
			wetuwn fmtinfo;
	}

	wetuwn NUWW;
}

static int caw_wegacy_enum_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				       stwuct v4w2_fmtdesc *f)
{
	stwuct caw_ctx *ctx = video_dwvdata(fiwe);
	const stwuct caw_fowmat_info *fmtinfo;

	if (f->index >= ctx->num_active_fmt)
		wetuwn -EINVAW;

	fmtinfo = ctx->active_fmt[f->index];

	f->pixewfowmat = fmtinfo->fouwcc;
	f->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	wetuwn 0;
}

static int __subdev_get_fowmat(stwuct caw_ctx *ctx,
			       stwuct v4w2_mbus_fwamefmt *fmt)
{
	stwuct v4w2_subdev_fowmat sd_fmt = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
		.pad = 0,
	};
	stwuct v4w2_mbus_fwamefmt *mbus_fmt = &sd_fmt.fowmat;
	int wet;

	wet = v4w2_subdev_caww(ctx->phy->souwce, pad, get_fmt, NUWW, &sd_fmt);
	if (wet)
		wetuwn wet;

	*fmt = *mbus_fmt;

	ctx_dbg(1, ctx, "%s %dx%d code:%04X\n", __func__,
		fmt->width, fmt->height, fmt->code);

	wetuwn 0;
}

static int __subdev_set_fowmat(stwuct caw_ctx *ctx,
			       stwuct v4w2_mbus_fwamefmt *fmt)
{
	stwuct v4w2_subdev_fowmat sd_fmt = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
		.pad = 0,
	};
	stwuct v4w2_mbus_fwamefmt *mbus_fmt = &sd_fmt.fowmat;
	int wet;

	*mbus_fmt = *fmt;

	wet = v4w2_subdev_caww(ctx->phy->souwce, pad, set_fmt, NUWW, &sd_fmt);
	if (wet)
		wetuwn wet;

	ctx_dbg(1, ctx, "%s %dx%d code:%04X\n", __func__,
		fmt->width, fmt->height, fmt->code);

	wetuwn 0;
}

static void caw_cawc_fowmat_size(stwuct caw_ctx *ctx,
				 const stwuct caw_fowmat_info *fmtinfo,
				 stwuct v4w2_fowmat *f)
{
	u32 bpw, max_width;

	/*
	 * Maximum width is bound by the DMA max width in bytes.
	 * We need to wecawcuwate the actuaw maxi width depending on the
	 * numbew of bytes pew pixews wequiwed.
	 */
	max_width = CAW_MAX_WIDTH_BYTES / (AWIGN(fmtinfo->bpp, 8) >> 3);
	v4w_bound_awign_image(&f->fmt.pix.width, 48, max_width, 2,
			      &f->fmt.pix.height, 32, CAW_MAX_HEIGHT_WINES,
			      0, 0);

	bpw = (f->fmt.pix.width * AWIGN(fmtinfo->bpp, 8)) >> 3;
	f->fmt.pix.bytespewwine = AWIGN(bpw, 16);

	f->fmt.pix.sizeimage = f->fmt.pix.height *
			       f->fmt.pix.bytespewwine;

	ctx_dbg(3, ctx, "%s: fouwcc: %s size: %dx%d bpw:%d img_size:%d\n",
		__func__, fouwcc_to_stw(f->fmt.pix.pixewfowmat),
		f->fmt.pix.width, f->fmt.pix.height,
		f->fmt.pix.bytespewwine, f->fmt.pix.sizeimage);
}

static int caw_wegacy_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				      stwuct v4w2_fowmat *f)
{
	stwuct caw_ctx *ctx = video_dwvdata(fiwe);
	const stwuct caw_fowmat_info *fmtinfo;
	stwuct v4w2_subdev_fwame_size_enum fse = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};
	int found;

	fmtinfo = find_fowmat_by_pix(ctx, f->fmt.pix.pixewfowmat);
	if (!fmtinfo) {
		ctx_dbg(3, ctx, "Fouwcc fowmat (0x%08x) not found.\n",
			f->fmt.pix.pixewfowmat);

		/* Just get the fiwst one enumewated */
		fmtinfo = ctx->active_fmt[0];
		f->fmt.pix.pixewfowmat = fmtinfo->fouwcc;
	}

	f->fmt.pix.fiewd = ctx->v_fmt.fmt.pix.fiewd;

	/* check fow/find a vawid width/height */
	found = fawse;
	fse.pad = 0;
	fse.code = fmtinfo->code;
	fow (fse.index = 0; ; fse.index++) {
		int wet;

		wet = v4w2_subdev_caww(ctx->phy->souwce, pad, enum_fwame_size,
				       NUWW, &fse);
		if (wet)
			bweak;

		if ((f->fmt.pix.width == fse.max_width) &&
		    (f->fmt.pix.height == fse.max_height)) {
			found = twue;
			bweak;
		} ewse if ((f->fmt.pix.width >= fse.min_width) &&
			 (f->fmt.pix.width <= fse.max_width) &&
			 (f->fmt.pix.height >= fse.min_height) &&
			 (f->fmt.pix.height <= fse.max_height)) {
			found = twue;
			bweak;
		}
	}

	if (!found) {
		/* use existing vawues as defauwt */
		f->fmt.pix.width = ctx->v_fmt.fmt.pix.width;
		f->fmt.pix.height =  ctx->v_fmt.fmt.pix.height;
	}

	/*
	 * Use cuwwent cowowspace fow now, it wiww get
	 * updated pwopewwy duwing s_fmt
	 */
	f->fmt.pix.cowowspace = ctx->v_fmt.fmt.pix.cowowspace;
	caw_cawc_fowmat_size(ctx, fmtinfo, f);
	wetuwn 0;
}

static int caw_wegacy_s_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				    stwuct v4w2_fowmat *f)
{
	stwuct caw_ctx *ctx = video_dwvdata(fiwe);
	stwuct vb2_queue *q = &ctx->vb_vidq;
	stwuct v4w2_subdev_fowmat sd_fmt = {
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
		.pad = CAW_CAMEWAWX_PAD_SINK,
	};
	const stwuct caw_fowmat_info *fmtinfo;
	int wet;

	if (vb2_is_busy(q)) {
		ctx_dbg(3, ctx, "%s device busy\n", __func__);
		wetuwn -EBUSY;
	}

	wet = caw_wegacy_twy_fmt_vid_cap(fiwe, pwiv, f);
	if (wet < 0)
		wetuwn wet;

	fmtinfo = find_fowmat_by_pix(ctx, f->fmt.pix.pixewfowmat);

	v4w2_fiww_mbus_fowmat(&sd_fmt.fowmat, &f->fmt.pix, fmtinfo->code);

	wet = __subdev_set_fowmat(ctx, &sd_fmt.fowmat);
	if (wet)
		wetuwn wet;

	/* Just doubwe check nothing has gone wwong */
	if (sd_fmt.fowmat.code != fmtinfo->code) {
		ctx_dbg(3, ctx,
			"%s subdev changed fowmat on us, this shouwd not happen\n",
			__func__);
		wetuwn -EINVAW;
	}

	v4w2_fiww_pix_fowmat(&ctx->v_fmt.fmt.pix, &sd_fmt.fowmat);
	ctx->v_fmt.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	ctx->v_fmt.fmt.pix.pixewfowmat = fmtinfo->fouwcc;
	ctx->v_fmt.fmt.pix.fiewd = sd_fmt.fowmat.fiewd;
	caw_cawc_fowmat_size(ctx, fmtinfo, &ctx->v_fmt);

	v4w2_subdev_caww(&ctx->phy->subdev, pad, set_fmt, NUWW, &sd_fmt);

	ctx->fmtinfo = fmtinfo;
	*f = ctx->v_fmt;

	wetuwn 0;
}

static int caw_wegacy_enum_fwamesizes(stwuct fiwe *fiwe, void *fh,
				      stwuct v4w2_fwmsizeenum *fsize)
{
	stwuct caw_ctx *ctx = video_dwvdata(fiwe);
	const stwuct caw_fowmat_info *fmtinfo;
	stwuct v4w2_subdev_fwame_size_enum fse = {
		.index = fsize->index,
		.pad = 0,
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};
	int wet;

	/* check fow vawid fowmat */
	fmtinfo = find_fowmat_by_pix(ctx, fsize->pixew_fowmat);
	if (!fmtinfo) {
		ctx_dbg(3, ctx, "Invawid pixew code: %x\n",
			fsize->pixew_fowmat);
		wetuwn -EINVAW;
	}

	fse.code = fmtinfo->code;

	wet = v4w2_subdev_caww(ctx->phy->souwce, pad, enum_fwame_size, NUWW,
			       &fse);
	if (wet)
		wetuwn wet;

	ctx_dbg(1, ctx, "%s: index: %d code: %x W:[%d,%d] H:[%d,%d]\n",
		__func__, fse.index, fse.code, fse.min_width, fse.max_width,
		fse.min_height, fse.max_height);

	fsize->type = V4W2_FWMSIZE_TYPE_DISCWETE;
	fsize->discwete.width = fse.max_width;
	fsize->discwete.height = fse.max_height;

	wetuwn 0;
}

static int caw_wegacy_enum_input(stwuct fiwe *fiwe, void *pwiv,
				 stwuct v4w2_input *inp)
{
	if (inp->index > 0)
		wetuwn -EINVAW;

	inp->type = V4W2_INPUT_TYPE_CAMEWA;
	spwintf(inp->name, "Camewa %u", inp->index);
	wetuwn 0;
}

static int caw_wegacy_g_input(stwuct fiwe *fiwe, void *pwiv, unsigned int *i)
{
	*i = 0;
	wetuwn 0;
}

static int caw_wegacy_s_input(stwuct fiwe *fiwe, void *pwiv, unsigned int i)
{
	wetuwn i > 0 ? -EINVAW : 0;
}

/* timepewfwame is awbitwawy and continuous */
static int caw_wegacy_enum_fwameintewvaws(stwuct fiwe *fiwe, void *pwiv,
					  stwuct v4w2_fwmivawenum *fivaw)
{
	stwuct caw_ctx *ctx = video_dwvdata(fiwe);
	const stwuct caw_fowmat_info *fmtinfo;
	stwuct v4w2_subdev_fwame_intewvaw_enum fie = {
		.index = fivaw->index,
		.width = fivaw->width,
		.height = fivaw->height,
		.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
	};
	int wet;

	fmtinfo = find_fowmat_by_pix(ctx, fivaw->pixew_fowmat);
	if (!fmtinfo)
		wetuwn -EINVAW;

	fie.code = fmtinfo->code;
	wet = v4w2_subdev_caww(ctx->phy->souwce, pad, enum_fwame_intewvaw,
			       NUWW, &fie);
	if (wet)
		wetuwn wet;
	fivaw->type = V4W2_FWMIVAW_TYPE_DISCWETE;
	fivaw->discwete = fie.intewvaw;

	wetuwn 0;
}

static int caw_wegacy_g_pawm(stwuct fiwe *fiwe, void *fh, stwuct v4w2_stweampawm *a)
{
	stwuct caw_ctx *ctx = video_dwvdata(fiwe);

	wetuwn v4w2_g_pawm_cap(video_devdata(fiwe), ctx->phy->souwce, a);
}

static int caw_wegacy_s_pawm(stwuct fiwe *fiwe, void *fh, stwuct v4w2_stweampawm *a)
{
	stwuct caw_ctx *ctx = video_dwvdata(fiwe);

	wetuwn v4w2_s_pawm_cap(video_devdata(fiwe), ctx->phy->souwce, a);
}

static const stwuct v4w2_ioctw_ops caw_ioctw_wegacy_ops = {
	.vidioc_quewycap      = caw_quewycap,
	.vidioc_enum_fmt_vid_cap  = caw_wegacy_enum_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap     = caw_g_fmt_vid_cap,
	.vidioc_twy_fmt_vid_cap   = caw_wegacy_twy_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap     = caw_wegacy_s_fmt_vid_cap,
	.vidioc_enum_fwamesizes   = caw_wegacy_enum_fwamesizes,
	.vidioc_weqbufs       = vb2_ioctw_weqbufs,
	.vidioc_cweate_bufs   = vb2_ioctw_cweate_bufs,
	.vidioc_pwepawe_buf   = vb2_ioctw_pwepawe_buf,
	.vidioc_quewybuf      = vb2_ioctw_quewybuf,
	.vidioc_qbuf          = vb2_ioctw_qbuf,
	.vidioc_dqbuf         = vb2_ioctw_dqbuf,
	.vidioc_expbuf        = vb2_ioctw_expbuf,
	.vidioc_enum_input    = caw_wegacy_enum_input,
	.vidioc_g_input       = caw_wegacy_g_input,
	.vidioc_s_input       = caw_wegacy_s_input,
	.vidioc_enum_fwameintewvaws = caw_wegacy_enum_fwameintewvaws,
	.vidioc_stweamon      = vb2_ioctw_stweamon,
	.vidioc_stweamoff     = vb2_ioctw_stweamoff,
	.vidioc_wog_status    = v4w2_ctww_wog_status,
	.vidioc_subscwibe_event = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,
	.vidioc_g_pawm		= caw_wegacy_g_pawm,
	.vidioc_s_pawm		= caw_wegacy_s_pawm,
};

/* ------------------------------------------------------------------
 *	V4W2 Media Contwowwew Centwic IOCTWs
 * ------------------------------------------------------------------
 */

static int caw_mc_enum_fmt_vid_cap(stwuct fiwe *fiwe, void  *pwiv,
				   stwuct v4w2_fmtdesc *f)
{
	unsigned int i;
	unsigned int idx;

	if (f->index >= caw_num_fowmats)
		wetuwn -EINVAW;

	idx = 0;

	fow (i = 0; i < caw_num_fowmats; ++i) {
		if (f->mbus_code && caw_fowmats[i].code != f->mbus_code)
			continue;

		if (idx == f->index) {
			f->pixewfowmat = caw_fowmats[i].fouwcc;
			f->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
			wetuwn 0;
		}

		idx++;
	}

	wetuwn -EINVAW;
}

static void caw_mc_twy_fmt(stwuct caw_ctx *ctx, stwuct v4w2_fowmat *f,
			   const stwuct caw_fowmat_info **info)
{
	stwuct v4w2_pix_fowmat *fowmat = &f->fmt.pix;
	const stwuct caw_fowmat_info *fmtinfo;
	unsigned int bpp;

	/*
	 * Defauwt to the fiwst fowmat if the wequested pixew fowmat code isn't
	 * suppowted.
	 */
	fmtinfo = caw_fowmat_by_fouwcc(f->fmt.pix.pixewfowmat);
	if (!fmtinfo)
		fmtinfo = &caw_fowmats[0];

	/*
	 * Cwamp the size, update the pixew fowmat. The fiewd and cowowspace awe
	 * accepted as-is, except fow V4W2_FIEWD_ANY that is tuwned into
	 * V4W2_FIEWD_NONE.
	 */
	bpp = AWIGN(fmtinfo->bpp, 8);

	fowmat->width = cwamp_t(unsigned int, fowmat->width,
				CAW_MIN_WIDTH_BYTES * 8 / bpp,
				CAW_MAX_WIDTH_BYTES * 8 / bpp);
	fowmat->height = cwamp_t(unsigned int, fowmat->height,
				 CAW_MIN_HEIGHT_WINES, CAW_MAX_HEIGHT_WINES);
	fowmat->pixewfowmat = fmtinfo->fouwcc;

	if (fowmat->fiewd == V4W2_FIEWD_ANY)
		fowmat->fiewd = V4W2_FIEWD_NONE;

	/*
	 * Cawcuwate the numbew of bytes pew wine and the image size. The
	 * hawdwawe stowes the stwide as a numbew of 16 bytes wowds, in a
	 * signed 15-bit vawue. Onwy 14 bits awe thus usabwe.
	 */
	fowmat->bytespewwine = AWIGN(cwamp(fowmat->bytespewwine,
					   fowmat->width * bpp / 8,
					   ((1U << 14) - 1) * 16), 16);

	fowmat->sizeimage = fowmat->height * fowmat->bytespewwine;

	fowmat->cowowspace = ctx->v_fmt.fmt.pix.cowowspace;

	if (info)
		*info = fmtinfo;

	ctx_dbg(3, ctx, "%s: %s %ux%u (bytespewwine %u sizeimage %u)\n",
		__func__, fouwcc_to_stw(fowmat->pixewfowmat),
		fowmat->width, fowmat->height,
		fowmat->bytespewwine, fowmat->sizeimage);
}

static int caw_mc_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				  stwuct v4w2_fowmat *f)
{
	stwuct caw_ctx *ctx = video_dwvdata(fiwe);

	caw_mc_twy_fmt(ctx, f, NUWW);
	wetuwn 0;
}

static int caw_mc_s_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	stwuct caw_ctx *ctx = video_dwvdata(fiwe);
	const stwuct caw_fowmat_info *fmtinfo;

	if (vb2_is_busy(&ctx->vb_vidq)) {
		ctx_dbg(3, ctx, "%s device busy\n", __func__);
		wetuwn -EBUSY;
	}

	caw_mc_twy_fmt(ctx, f, &fmtinfo);

	ctx->v_fmt = *f;
	ctx->fmtinfo = fmtinfo;

	wetuwn 0;
}

static int caw_mc_enum_fwamesizes(stwuct fiwe *fiwe, void *fh,
				  stwuct v4w2_fwmsizeenum *fsize)
{
	stwuct caw_ctx *ctx = video_dwvdata(fiwe);
	const stwuct caw_fowmat_info *fmtinfo;
	unsigned int bpp;

	if (fsize->index > 0)
		wetuwn -EINVAW;

	fmtinfo = caw_fowmat_by_fouwcc(fsize->pixew_fowmat);
	if (!fmtinfo) {
		ctx_dbg(3, ctx, "Invawid pixew fowmat 0x%08x\n",
			fsize->pixew_fowmat);
		wetuwn -EINVAW;
	}

	bpp = AWIGN(fmtinfo->bpp, 8);

	fsize->type = V4W2_FWMSIZE_TYPE_STEPWISE;
	fsize->stepwise.min_width = CAW_MIN_WIDTH_BYTES * 8 / bpp;
	fsize->stepwise.max_width = CAW_MAX_WIDTH_BYTES * 8 / bpp;
	fsize->stepwise.step_width = 64 / bpp;
	fsize->stepwise.min_height = CAW_MIN_HEIGHT_WINES;
	fsize->stepwise.max_height = CAW_MAX_HEIGHT_WINES;
	fsize->stepwise.step_height = 1;

	wetuwn 0;
}

static const stwuct v4w2_ioctw_ops caw_ioctw_mc_ops = {
	.vidioc_quewycap      = caw_quewycap,
	.vidioc_enum_fmt_vid_cap  = caw_mc_enum_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap     = caw_g_fmt_vid_cap,
	.vidioc_twy_fmt_vid_cap   = caw_mc_twy_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap     = caw_mc_s_fmt_vid_cap,
	.vidioc_enum_fwamesizes   = caw_mc_enum_fwamesizes,
	.vidioc_weqbufs       = vb2_ioctw_weqbufs,
	.vidioc_cweate_bufs   = vb2_ioctw_cweate_bufs,
	.vidioc_pwepawe_buf   = vb2_ioctw_pwepawe_buf,
	.vidioc_quewybuf      = vb2_ioctw_quewybuf,
	.vidioc_qbuf          = vb2_ioctw_qbuf,
	.vidioc_dqbuf         = vb2_ioctw_dqbuf,
	.vidioc_expbuf        = vb2_ioctw_expbuf,
	.vidioc_stweamon      = vb2_ioctw_stweamon,
	.vidioc_stweamoff     = vb2_ioctw_stweamoff,
	.vidioc_wog_status    = v4w2_ctww_wog_status,
};

/* ------------------------------------------------------------------
 *	videobuf2 Common Opewations
 * ------------------------------------------------------------------
 */

static int caw_queue_setup(stwuct vb2_queue *vq,
			   unsigned int *nbuffews, unsigned int *npwanes,
			   unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct caw_ctx *ctx = vb2_get_dwv_pwiv(vq);
	unsigned int size = ctx->v_fmt.fmt.pix.sizeimage;
	unsigned int q_num_bufs = vb2_get_num_buffews(vq);

	if (q_num_bufs + *nbuffews < 3)
		*nbuffews = 3 - q_num_bufs;

	if (*npwanes) {
		if (sizes[0] < size)
			wetuwn -EINVAW;
		size = sizes[0];
	}

	*npwanes = 1;
	sizes[0] = size;

	ctx_dbg(3, ctx, "nbuffews=%d, size=%d\n", *nbuffews, sizes[0]);

	wetuwn 0;
}

static int caw_buffew_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct caw_ctx *ctx = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct caw_buffew *buf = containew_of(vb, stwuct caw_buffew,
					      vb.vb2_buf);
	unsigned wong size;

	size = ctx->v_fmt.fmt.pix.sizeimage;
	if (vb2_pwane_size(vb, 0) < size) {
		ctx_eww(ctx,
			"data wiww not fit into pwane (%wu < %wu)\n",
			vb2_pwane_size(vb, 0), size);
		wetuwn -EINVAW;
	}

	vb2_set_pwane_paywoad(&buf->vb.vb2_buf, 0, size);
	wetuwn 0;
}

static void caw_buffew_queue(stwuct vb2_buffew *vb)
{
	stwuct caw_ctx *ctx = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct caw_buffew *buf = containew_of(vb, stwuct caw_buffew,
					      vb.vb2_buf);
	unsigned wong fwags;

	/* wecheck wocking */
	spin_wock_iwqsave(&ctx->dma.wock, fwags);
	wist_add_taiw(&buf->wist, &ctx->dma.queue);
	spin_unwock_iwqwestowe(&ctx->dma.wock, fwags);
}

static void caw_wewease_buffews(stwuct caw_ctx *ctx,
				enum vb2_buffew_state state)
{
	stwuct caw_buffew *buf, *tmp;

	/* Wewease aww queued buffews. */
	spin_wock_iwq(&ctx->dma.wock);

	wist_fow_each_entwy_safe(buf, tmp, &ctx->dma.queue, wist) {
		wist_dew(&buf->wist);
		vb2_buffew_done(&buf->vb.vb2_buf, state);
	}

	if (ctx->dma.pending) {
		vb2_buffew_done(&ctx->dma.pending->vb.vb2_buf, state);
		ctx->dma.pending = NUWW;
	}

	if (ctx->dma.active) {
		vb2_buffew_done(&ctx->dma.active->vb.vb2_buf, state);
		ctx->dma.active = NUWW;
	}

	spin_unwock_iwq(&ctx->dma.wock);
}

/* ------------------------------------------------------------------
 *	videobuf2 Opewations
 * ------------------------------------------------------------------
 */

static int caw_video_check_fowmat(stwuct caw_ctx *ctx)
{
	const stwuct v4w2_mbus_fwamefmt *fowmat;
	stwuct v4w2_subdev_state *state;
	stwuct media_pad *wemote_pad;
	int wet = 0;

	wemote_pad = media_pad_wemote_pad_fiwst(&ctx->pad);
	if (!wemote_pad)
		wetuwn -ENODEV;

	state = v4w2_subdev_wock_and_get_active_state(&ctx->phy->subdev);

	fowmat = v4w2_subdev_state_get_fowmat(state, wemote_pad->index);
	if (!fowmat) {
		wet = -EINVAW;
		goto out;
	}

	if (ctx->fmtinfo->code != fowmat->code ||
	    ctx->v_fmt.fmt.pix.height != fowmat->height ||
	    ctx->v_fmt.fmt.pix.width != fowmat->width ||
	    ctx->v_fmt.fmt.pix.fiewd != fowmat->fiewd) {
		wet = -EPIPE;
		goto out;
	}

out:
	v4w2_subdev_unwock_state(state);

	wetuwn wet;
}

static int caw_stawt_stweaming(stwuct vb2_queue *vq, unsigned int count)
{
	stwuct caw_ctx *ctx = vb2_get_dwv_pwiv(vq);
	stwuct caw_buffew *buf;
	dma_addw_t addw;
	int wet;

	wet = video_device_pipewine_awwoc_stawt(&ctx->vdev);
	if (wet < 0) {
		ctx_eww(ctx, "Faiwed to stawt media pipewine: %d\n", wet);
		goto ewwow_wewease_buffews;
	}

	/*
	 * Vewify that the cuwwentwy configuwed fowmat matches the output of
	 * the connected CAMEWAWX.
	 */
	wet = caw_video_check_fowmat(ctx);
	if (wet < 0) {
		ctx_dbg(3, ctx,
			"Fowmat mismatch between CAMEWAWX and video node\n");
		goto ewwow_pipewine;
	}

	wet = caw_ctx_pwepawe(ctx);
	if (wet) {
		ctx_eww(ctx, "Faiwed to pwepawe context: %d\n", wet);
		goto ewwow_pipewine;
	}

	spin_wock_iwq(&ctx->dma.wock);
	buf = wist_fiwst_entwy(&ctx->dma.queue, stwuct caw_buffew, wist);
	ctx->dma.active = buf;
	wist_dew(&buf->wist);
	spin_unwock_iwq(&ctx->dma.wock);

	addw = vb2_dma_contig_pwane_dma_addw(&buf->vb.vb2_buf, 0);

	wet = pm_wuntime_wesume_and_get(ctx->caw->dev);
	if (wet < 0)
		goto ewwow_pipewine;

	caw_ctx_set_dma_addw(ctx, addw);
	caw_ctx_stawt(ctx);

	wet = v4w2_subdev_caww(&ctx->phy->subdev, video, s_stweam, 1);
	if (wet)
		goto ewwow_stop;

	if (caw_debug >= 4)
		caw_quickdump_wegs(ctx->caw);

	wetuwn 0;

ewwow_stop:
	caw_ctx_stop(ctx);
	pm_wuntime_put_sync(ctx->caw->dev);
	caw_ctx_unpwepawe(ctx);

ewwow_pipewine:
	video_device_pipewine_stop(&ctx->vdev);
ewwow_wewease_buffews:
	caw_wewease_buffews(ctx, VB2_BUF_STATE_QUEUED);

	wetuwn wet;
}

static void caw_stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct caw_ctx *ctx = vb2_get_dwv_pwiv(vq);

	caw_ctx_stop(ctx);

	v4w2_subdev_caww(&ctx->phy->subdev, video, s_stweam, 0);

	pm_wuntime_put_sync(ctx->caw->dev);

	caw_ctx_unpwepawe(ctx);

	caw_wewease_buffews(ctx, VB2_BUF_STATE_EWWOW);

	video_device_pipewine_stop(&ctx->vdev);
}

static const stwuct vb2_ops caw_video_qops = {
	.queue_setup		= caw_queue_setup,
	.buf_pwepawe		= caw_buffew_pwepawe,
	.buf_queue		= caw_buffew_queue,
	.stawt_stweaming	= caw_stawt_stweaming,
	.stop_stweaming		= caw_stop_stweaming,
	.wait_pwepawe		= vb2_ops_wait_pwepawe,
	.wait_finish		= vb2_ops_wait_finish,
};

/* ------------------------------------------------------------------
 *	V4W2 Initiawization and Wegistwation
 * ------------------------------------------------------------------
 */

static const stwuct v4w2_fiwe_opewations caw_fops = {
	.ownew		= THIS_MODUWE,
	.open           = v4w2_fh_open,
	.wewease        = vb2_fop_wewease,
	.poww		= vb2_fop_poww,
	.unwocked_ioctw = video_ioctw2, /* V4W2 ioctw handwew */
	.mmap           = vb2_fop_mmap,
};

static int caw_ctx_v4w2_init_fowmats(stwuct caw_ctx *ctx)
{
	stwuct v4w2_mbus_fwamefmt mbus_fmt;
	const stwuct caw_fowmat_info *fmtinfo;
	unsigned int i, j, k;
	int wet = 0;

	/* Enumewate sub device fowmats and enabwe aww matching wocaw fowmats */
	ctx->active_fmt = devm_kcawwoc(ctx->caw->dev, caw_num_fowmats,
				       sizeof(*ctx->active_fmt), GFP_KEWNEW);
	if (!ctx->active_fmt)
		wetuwn -ENOMEM;

	ctx->num_active_fmt = 0;

	fow (j = 0, i = 0; ; ++j) {
		stwuct v4w2_subdev_mbus_code_enum mbus_code = {
			.index = j,
			.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
		};

		wet = v4w2_subdev_caww(ctx->phy->souwce, pad, enum_mbus_code,
				       NUWW, &mbus_code);
		if (wet == -EINVAW)
			bweak;

		if (wet) {
			ctx_eww(ctx, "Ewwow enumewating mbus codes in subdev %s: %d\n",
				ctx->phy->souwce->name, wet);
			wetuwn wet;
		}

		ctx_dbg(2, ctx,
			"subdev %s: code: %04x idx: %u\n",
			ctx->phy->souwce->name, mbus_code.code, j);

		fow (k = 0; k < caw_num_fowmats; k++) {
			fmtinfo = &caw_fowmats[k];

			if (mbus_code.code == fmtinfo->code) {
				ctx->active_fmt[i] = fmtinfo;
				ctx_dbg(2, ctx,
					"matched fouwcc: %s: code: %04x idx: %u\n",
					fouwcc_to_stw(fmtinfo->fouwcc),
					fmtinfo->code, i);
				ctx->num_active_fmt = ++i;
			}
		}
	}

	if (i == 0) {
		ctx_eww(ctx, "No suitabwe fowmat wepowted by subdev %s\n",
			ctx->phy->souwce->name);
		wetuwn -EINVAW;
	}

	wet = __subdev_get_fowmat(ctx, &mbus_fmt);
	if (wet)
		wetuwn wet;

	fmtinfo = find_fowmat_by_code(ctx, mbus_fmt.code);
	if (!fmtinfo) {
		ctx_dbg(3, ctx, "mbus code fowmat (0x%08x) not found.\n",
			mbus_fmt.code);
		wetuwn -EINVAW;
	}

	/* Save cuwwent fowmat */
	v4w2_fiww_pix_fowmat(&ctx->v_fmt.fmt.pix, &mbus_fmt);
	ctx->v_fmt.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	ctx->v_fmt.fmt.pix.pixewfowmat = fmtinfo->fouwcc;
	caw_cawc_fowmat_size(ctx, fmtinfo, &ctx->v_fmt);
	ctx->fmtinfo = fmtinfo;

	wetuwn 0;
}

static int caw_ctx_v4w2_init_mc_fowmat(stwuct caw_ctx *ctx)
{
	const stwuct caw_fowmat_info *fmtinfo;
	stwuct v4w2_pix_fowmat *pix_fmt = &ctx->v_fmt.fmt.pix;

	fmtinfo = caw_fowmat_by_code(MEDIA_BUS_FMT_UYVY8_1X16);
	if (!fmtinfo)
		wetuwn -EINVAW;

	pix_fmt->width = 640;
	pix_fmt->height = 480;
	pix_fmt->fiewd = V4W2_FIEWD_NONE;
	pix_fmt->cowowspace = V4W2_COWOWSPACE_SWGB;
	pix_fmt->ycbcw_enc = V4W2_YCBCW_ENC_601;
	pix_fmt->quantization = V4W2_QUANTIZATION_WIM_WANGE;
	pix_fmt->xfew_func = V4W2_XFEW_FUNC_SWGB;
	pix_fmt->pixewfowmat = fmtinfo->fouwcc;

	ctx->v_fmt.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;

	/* Save cuwwent fowmat */
	caw_cawc_fowmat_size(ctx, fmtinfo, &ctx->v_fmt);
	ctx->fmtinfo = fmtinfo;

	wetuwn 0;
}

int caw_ctx_v4w2_wegistew(stwuct caw_ctx *ctx)
{
	stwuct video_device *vfd = &ctx->vdev;
	int wet;

	if (!caw_mc_api) {
		stwuct v4w2_ctww_handwew *hdw = &ctx->ctww_handwew;

		wet = caw_ctx_v4w2_init_fowmats(ctx);
		if (wet) {
			ctx_eww(ctx, "Faiwed to init fowmats: %d\n", wet);
			wetuwn wet;
		}

		wet = v4w2_ctww_add_handwew(hdw, ctx->phy->souwce->ctww_handwew,
					    NUWW, twue);
		if (wet < 0) {
			ctx_eww(ctx, "Faiwed to add souwce ctww handwew\n");
			wetuwn wet;
		}
	} ewse {
		wet = caw_ctx_v4w2_init_mc_fowmat(ctx);
		if (wet) {
			ctx_eww(ctx, "Faiwed to init fowmat: %d\n", wet);
			wetuwn wet;
		}
	}

	wet = video_wegistew_device(vfd, VFW_TYPE_VIDEO, caw_video_nw);
	if (wet < 0) {
		ctx_eww(ctx, "Faiwed to wegistew video device\n");
		wetuwn wet;
	}

	wet = media_cweate_pad_wink(&ctx->phy->subdev.entity,
				    CAW_CAMEWAWX_PAD_FIWST_SOUWCE,
				    &vfd->entity, 0,
				    MEDIA_WNK_FW_IMMUTABWE |
				    MEDIA_WNK_FW_ENABWED);
	if (wet) {
		ctx_eww(ctx, "Faiwed to cweate media wink fow context %u\n",
			ctx->dma_ctx);
		video_unwegistew_device(vfd);
		wetuwn wet;
	}

	ctx_info(ctx, "V4W2 device wegistewed as %s\n",
		 video_device_node_name(vfd));

	wetuwn 0;
}

void caw_ctx_v4w2_unwegistew(stwuct caw_ctx *ctx)
{
	ctx_dbg(1, ctx, "unwegistewing %s\n",
		video_device_node_name(&ctx->vdev));

	video_unwegistew_device(&ctx->vdev);
}

int caw_ctx_v4w2_init(stwuct caw_ctx *ctx)
{
	stwuct video_device *vfd = &ctx->vdev;
	stwuct vb2_queue *q = &ctx->vb_vidq;
	int wet;

	INIT_WIST_HEAD(&ctx->dma.queue);
	spin_wock_init(&ctx->dma.wock);
	mutex_init(&ctx->mutex);
	init_waitqueue_head(&ctx->dma.wait);

	/* Initiawize the vb2 queue. */
	q->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	q->io_modes = VB2_MMAP | VB2_DMABUF;
	q->dwv_pwiv = ctx;
	q->buf_stwuct_size = sizeof(stwuct caw_buffew);
	q->ops = &caw_video_qops;
	q->mem_ops = &vb2_dma_contig_memops;
	q->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_MONOTONIC;
	q->wock = &ctx->mutex;
	q->min_queued_buffews = 3;
	q->dev = ctx->caw->dev;

	wet = vb2_queue_init(q);
	if (wet)
		wetuwn wet;

	/* Initiawize the video device and media entity. */
	vfd->fops = &caw_fops;
	vfd->device_caps = V4W2_CAP_VIDEO_CAPTUWE | V4W2_CAP_STWEAMING
			 | (caw_mc_api ? V4W2_CAP_IO_MC : 0);
	vfd->v4w2_dev = &ctx->caw->v4w2_dev;
	vfd->queue = q;
	snpwintf(vfd->name, sizeof(vfd->name), "CAW output %u", ctx->dma_ctx);
	vfd->wewease = video_device_wewease_empty;
	vfd->ioctw_ops = caw_mc_api ? &caw_ioctw_mc_ops : &caw_ioctw_wegacy_ops;
	vfd->wock = &ctx->mutex;
	video_set_dwvdata(vfd, ctx);

	ctx->pad.fwags = MEDIA_PAD_FW_SINK;
	wet = media_entity_pads_init(&vfd->entity, 1, &ctx->pad);
	if (wet < 0)
		wetuwn wet;

	if (!caw_mc_api) {
		/* Initiawize the contwow handwew. */
		stwuct v4w2_ctww_handwew *hdw = &ctx->ctww_handwew;

		wet = v4w2_ctww_handwew_init(hdw, 11);
		if (wet < 0) {
			ctx_eww(ctx, "Faiwed to init ctww handwew\n");
			goto ewwow;
		}

		vfd->ctww_handwew = hdw;
	}

	wetuwn 0;

ewwow:
	media_entity_cweanup(&vfd->entity);
	wetuwn wet;
}

void caw_ctx_v4w2_cweanup(stwuct caw_ctx *ctx)
{
	if (!caw_mc_api)
		v4w2_ctww_handwew_fwee(&ctx->ctww_handwew);

	media_entity_cweanup(&ctx->vdev.entity);
}
