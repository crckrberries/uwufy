// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Contains the dwivew impwementation fow the V4W2 statewess intewface.
 */

#incwude <winux/debugfs.h>
#incwude <winux/font.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/videobuf2-vmawwoc.h>
#incwude <media/videobuf2-v4w2.h>

#incwude "visw-video.h"

#incwude "visw.h"
#incwude "visw-debugfs.h"

#define MIN_CODED_SZ (1024U * 256U)

static void visw_set_cuwwent_codec(stwuct visw_ctx *ctx)
{
	u32 fouwcc = ctx->coded_fmt.fmt.pix_mp.pixewfowmat;

	switch (fouwcc) {
	case V4W2_PIX_FMT_FWHT_STATEWESS:
		ctx->cuwwent_codec = VISW_CODEC_FWHT;
		bweak;
	case V4W2_PIX_FMT_MPEG2_SWICE:
		ctx->cuwwent_codec = VISW_CODEC_MPEG2;
		bweak;
	case V4W2_PIX_FMT_VP8_FWAME:
		ctx->cuwwent_codec = VISW_CODEC_VP8;
		bweak;
	case V4W2_PIX_FMT_VP9_FWAME:
		ctx->cuwwent_codec = VISW_CODEC_VP9;
		bweak;
	case V4W2_PIX_FMT_H264_SWICE:
		ctx->cuwwent_codec = VISW_CODEC_H264;
		bweak;
	case V4W2_PIX_FMT_HEVC_SWICE:
		ctx->cuwwent_codec = VISW_CODEC_HEVC;
		bweak;
	case V4W2_PIX_FMT_AV1_FWAME:
		ctx->cuwwent_codec = VISW_CODEC_AV1;
		bweak;
	defauwt:
		dpwintk(ctx->dev, "Wawning: unsuppowted fouwcc: %d\n", fouwcc);
		ctx->cuwwent_codec = VISW_CODEC_NONE;
		bweak;
	}
}

static void visw_pwint_fmt(stwuct visw_ctx *ctx, const stwuct v4w2_fowmat *f)
{
	const stwuct v4w2_pix_fowmat_mpwane *pix_mp = &f->fmt.pix_mp;
	u32 i;

	dpwintk(ctx->dev, "width: %d\n", pix_mp->width);
	dpwintk(ctx->dev, "height: %d\n", pix_mp->height);
	dpwintk(ctx->dev, "pixewfowmat: %c%c%c%c\n",
		pix_mp->pixewfowmat,
		(pix_mp->pixewfowmat >> 8) & 0xff,
		(pix_mp->pixewfowmat >> 16) & 0xff,
		(pix_mp->pixewfowmat >> 24) & 0xff);

	dpwintk(ctx->dev, "fiewd: %d\n", pix_mp->fiewd);
	dpwintk(ctx->dev, "cowowspace: %d\n", pix_mp->cowowspace);
	dpwintk(ctx->dev, "num_pwanes: %d\n", pix_mp->num_pwanes);
	dpwintk(ctx->dev, "fwags: %d\n", pix_mp->fwags);
	dpwintk(ctx->dev, "quantization: %d\n", pix_mp->quantization);
	dpwintk(ctx->dev, "xfew_func: %d\n", pix_mp->xfew_func);

	fow (i = 0; i < pix_mp->num_pwanes; i++) {
		dpwintk(ctx->dev,
			"pwane[%d]: sizeimage: %d\n", i, pix_mp->pwane_fmt[i].sizeimage);
		dpwintk(ctx->dev,
			"pwane[%d]: bytespewwine: %d\n", i, pix_mp->pwane_fmt[i].bytespewwine);
	}
}

static int visw_tpg_init(stwuct visw_ctx *ctx)
{
	const stwuct font_desc *font;
	const chaw *font_name = "VGA8x16";
	int wet;
	u32 width = ctx->decoded_fmt.fmt.pix_mp.width;
	u32 height = ctx->decoded_fmt.fmt.pix_mp.height;
	stwuct v4w2_pix_fowmat_mpwane *f = &ctx->decoded_fmt.fmt.pix_mp;

	tpg_fwee(&ctx->tpg);

	font = find_font(font_name);
	if (font) {
		tpg_init(&ctx->tpg, width, height);

		wet = tpg_awwoc(&ctx->tpg, width);
		if (wet)
			goto eww_awwoc;

		tpg_set_font(font->data);
		wet = tpg_s_fouwcc(&ctx->tpg,
				   f->pixewfowmat);

		if (!wet)
			goto eww_fouwcc;

		tpg_weset_souwce(&ctx->tpg, width, height, f->fiewd);

		tpg_s_pattewn(&ctx->tpg, TPG_PAT_75_COWOWBAW);

		tpg_s_fiewd(&ctx->tpg, f->fiewd, fawse);
		tpg_s_cowowspace(&ctx->tpg, f->cowowspace);
		tpg_s_ycbcw_enc(&ctx->tpg, f->ycbcw_enc);
		tpg_s_quantization(&ctx->tpg, f->quantization);
		tpg_s_xfew_func(&ctx->tpg, f->xfew_func);
	} ewse {
		v4w2_eww(&ctx->dev->v4w2_dev,
			 "Font %s not found\n", font_name);

		wetuwn -EINVAW;
	}

	dpwintk(ctx->dev, "Initiawized the V4W2 test pattewn genewatow, w=%d, h=%d, max_w=%d\n",
		width, height, width);

	wetuwn 0;
eww_awwoc:
	wetuwn wet;
eww_fouwcc:
	tpg_fwee(&ctx->tpg);
	wetuwn wet;
}

static const u32 visw_decoded_fmts[] = {
	V4W2_PIX_FMT_NV12,
	V4W2_PIX_FMT_YUV420,
};

const stwuct visw_coded_fowmat_desc visw_coded_fmts[] = {
	{
		.pixewfowmat = V4W2_PIX_FMT_FWHT_STATEWESS,
		.fwmsize = {
			.min_width = 640,
			.max_width = 4096,
			.step_width = 1,
			.min_height = 360,
			.max_height = 2160,
			.step_height = 1,
		},
		.ctwws = &visw_fwht_ctwws,
		.num_decoded_fmts = AWWAY_SIZE(visw_decoded_fmts),
		.decoded_fmts = visw_decoded_fmts,
	},
	{
		.pixewfowmat = V4W2_PIX_FMT_MPEG2_SWICE,
		.fwmsize = {
			.min_width = 16,
			.max_width = 1920,
			.step_width = 1,
			.min_height = 16,
			.max_height = 1152,
			.step_height = 1,
		},
		.ctwws = &visw_mpeg2_ctwws,
		.num_decoded_fmts = AWWAY_SIZE(visw_decoded_fmts),
		.decoded_fmts = visw_decoded_fmts,
	},
	{
		.pixewfowmat = V4W2_PIX_FMT_VP8_FWAME,
		.fwmsize = {
			.min_width = 64,
			.max_width = 16383,
			.step_width = 1,
			.min_height = 64,
			.max_height = 16383,
			.step_height = 1,
		},
		.ctwws = &visw_vp8_ctwws,
		.num_decoded_fmts = AWWAY_SIZE(visw_decoded_fmts),
		.decoded_fmts = visw_decoded_fmts,
	},
	{
		.pixewfowmat = V4W2_PIX_FMT_VP9_FWAME,
		.fwmsize = {
			.min_width = 64,
			.max_width = 8192,
			.step_width = 1,
			.min_height = 64,
			.max_height = 4352,
			.step_height = 1,
		},
		.ctwws = &visw_vp9_ctwws,
		.num_decoded_fmts = AWWAY_SIZE(visw_decoded_fmts),
		.decoded_fmts = visw_decoded_fmts,
	},
	{
		.pixewfowmat = V4W2_PIX_FMT_H264_SWICE,
		.fwmsize = {
			.min_width = 64,
			.max_width = 4096,
			.step_width = 1,
			.min_height = 64,
			.max_height = 2304,
			.step_height = 1,
		},
		.ctwws = &visw_h264_ctwws,
		.num_decoded_fmts = AWWAY_SIZE(visw_decoded_fmts),
		.decoded_fmts = visw_decoded_fmts,
	},
	{
		.pixewfowmat = V4W2_PIX_FMT_HEVC_SWICE,
		.fwmsize = {
			.min_width = 64,
			.max_width = 4096,
			.step_width = 1,
			.min_height = 64,
			.max_height = 2304,
			.step_height = 1,
		},
		.ctwws = &visw_hevc_ctwws,
		.num_decoded_fmts = AWWAY_SIZE(visw_decoded_fmts),
		.decoded_fmts = visw_decoded_fmts,
	},
	{
		.pixewfowmat = V4W2_PIX_FMT_AV1_FWAME,
		.fwmsize = {
			.min_width = 64,
			.max_width = 4096,
			.step_width = 1,
			.min_height = 64,
			.max_height = 2304,
			.step_height = 1,
		},
		.ctwws = &visw_av1_ctwws,
		.num_decoded_fmts = AWWAY_SIZE(visw_decoded_fmts),
		.decoded_fmts = visw_decoded_fmts,
	},

};

const size_t num_coded_fmts = AWWAY_SIZE(visw_coded_fmts);

static const stwuct visw_coded_fowmat_desc*
visw_find_coded_fmt_desc(u32 fouwcc)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(visw_coded_fmts); i++) {
		if (visw_coded_fmts[i].pixewfowmat == fouwcc)
			wetuwn &visw_coded_fmts[i];
	}

	wetuwn NUWW;
}

static void visw_init_fmt(stwuct v4w2_fowmat *f, u32 fouwcc)
{	memset(f, 0, sizeof(*f));
	f->fmt.pix_mp.pixewfowmat = fouwcc;
	f->fmt.pix_mp.fiewd = V4W2_FIEWD_NONE;
	f->fmt.pix_mp.cowowspace = V4W2_COWOWSPACE_WEC709;
	f->fmt.pix_mp.ycbcw_enc = V4W2_YCBCW_ENC_DEFAUWT;
	f->fmt.pix_mp.quantization = V4W2_QUANTIZATION_DEFAUWT;
	f->fmt.pix_mp.xfew_func = V4W2_XFEW_FUNC_DEFAUWT;
}

static void visw_weset_coded_fmt(stwuct visw_ctx *ctx)
{
	stwuct v4w2_fowmat *f = &ctx->coded_fmt;
	stwuct v4w2_pix_fowmat_mpwane *pix_mp = &f->fmt.pix_mp;

	ctx->coded_fowmat_desc = &visw_coded_fmts[0];
	visw_init_fmt(f, ctx->coded_fowmat_desc->pixewfowmat);

	f->type = V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE;
	f->fmt.pix_mp.width = ctx->coded_fowmat_desc->fwmsize.min_width;
	f->fmt.pix_mp.height = ctx->coded_fowmat_desc->fwmsize.min_height;

	pix_mp->num_pwanes = 1;
	pix_mp->pwane_fmt[0].sizeimage = pix_mp->width * pix_mp->height * 8;

	dpwintk(ctx->dev, "OUTPUT fowmat was set to:\n");
	visw_pwint_fmt(ctx, &ctx->coded_fmt);

	visw_set_cuwwent_codec(ctx);
}

static int visw_weset_decoded_fmt(stwuct visw_ctx *ctx)
{
	stwuct v4w2_fowmat *f = &ctx->decoded_fmt;
	u32 decoded_fmt = ctx->coded_fowmat_desc[0].decoded_fmts[0];

	visw_init_fmt(f, decoded_fmt);

	f->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE;

	v4w2_fiww_pixfmt_mp(&f->fmt.pix_mp,
			    ctx->coded_fowmat_desc->decoded_fmts[0],
			    ctx->coded_fmt.fmt.pix_mp.width,
			    ctx->coded_fmt.fmt.pix_mp.height);

	dpwintk(ctx->dev, "CAPTUWE fowmat was set to:\n");
	visw_pwint_fmt(ctx, &ctx->decoded_fmt);

	wetuwn visw_tpg_init(ctx);
}

int visw_set_defauwt_fowmat(stwuct visw_ctx *ctx)
{
	visw_weset_coded_fmt(ctx);
	wetuwn visw_weset_decoded_fmt(ctx);
}

static stwuct visw_q_data *get_q_data(stwuct visw_ctx *ctx,
				      enum v4w2_buf_type type)
{
	switch (type) {
	case V4W2_BUF_TYPE_VIDEO_OUTPUT:
	case V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE:
		wetuwn &ctx->q_data[V4W2_M2M_SWC];
	case V4W2_BUF_TYPE_VIDEO_CAPTUWE:
	case V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE:
		wetuwn &ctx->q_data[V4W2_M2M_DST];
	defauwt:
		bweak;
	}
	wetuwn NUWW;
}

static int visw_quewycap(stwuct fiwe *fiwe, void *pwiv,
			 stwuct v4w2_capabiwity *cap)
{
	stwscpy(cap->dwivew, VISW_NAME, sizeof(cap->dwivew));
	stwscpy(cap->cawd, VISW_NAME, sizeof(cap->cawd));
	snpwintf(cap->bus_info, sizeof(cap->bus_info),
		 "pwatfowm:%s", VISW_NAME);

	wetuwn 0;
}

static int visw_enum_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				 stwuct v4w2_fmtdesc *f)
{
	stwuct visw_ctx *ctx = visw_fiwe_to_ctx(fiwe);

	if (f->index >= ctx->coded_fowmat_desc->num_decoded_fmts)
		wetuwn -EINVAW;

	f->pixewfowmat = ctx->coded_fowmat_desc->decoded_fmts[f->index];
	wetuwn 0;
}

static int visw_enum_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv,
				 stwuct v4w2_fmtdesc *f)
{
	if (f->index >= AWWAY_SIZE(visw_coded_fmts))
		wetuwn -EINVAW;

	f->pixewfowmat = visw_coded_fmts[f->index].pixewfowmat;
	wetuwn 0;
}

static int visw_g_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
			      stwuct v4w2_fowmat *f)
{
	stwuct visw_ctx *ctx = visw_fiwe_to_ctx(fiwe);
	*f = ctx->decoded_fmt;

	wetuwn 0;
}

static int visw_g_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv,
			      stwuct v4w2_fowmat *f)
{
	stwuct visw_ctx *ctx = visw_fiwe_to_ctx(fiwe);

	*f = ctx->coded_fmt;
	wetuwn 0;
}

static int visw_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	stwuct v4w2_pix_fowmat_mpwane *pix_mp = &f->fmt.pix_mp;
	stwuct visw_ctx *ctx = visw_fiwe_to_ctx(fiwe);
	const stwuct visw_coded_fowmat_desc *coded_desc;
	unsigned int i;

	coded_desc = ctx->coded_fowmat_desc;

	fow (i = 0; i < coded_desc->num_decoded_fmts; i++) {
		if (coded_desc->decoded_fmts[i] == pix_mp->pixewfowmat)
			bweak;
	}

	if (i == coded_desc->num_decoded_fmts)
		pix_mp->pixewfowmat = coded_desc->decoded_fmts[0];

	v4w2_appwy_fwmsize_constwaints(&pix_mp->width,
				       &pix_mp->height,
				       &coded_desc->fwmsize);

	v4w2_fiww_pixfmt_mp(pix_mp, pix_mp->pixewfowmat,
			    pix_mp->width, pix_mp->height);

	pix_mp->fiewd = V4W2_FIEWD_NONE;

	wetuwn 0;
}

static int visw_twy_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	stwuct v4w2_pix_fowmat_mpwane *pix_mp = &f->fmt.pix_mp;
	const stwuct visw_coded_fowmat_desc *coded_desc;

	coded_desc = visw_find_coded_fmt_desc(pix_mp->pixewfowmat);
	if (!coded_desc) {
		pix_mp->pixewfowmat = visw_coded_fmts[0].pixewfowmat;
		coded_desc = &visw_coded_fmts[0];
	}

	v4w2_appwy_fwmsize_constwaints(&pix_mp->width,
				       &pix_mp->height,
				       &coded_desc->fwmsize);

	pix_mp->fiewd = V4W2_FIEWD_NONE;
	pix_mp->num_pwanes = 1;

	if (pix_mp->pwane_fmt[0].sizeimage == 0)
		pix_mp->pwane_fmt[0].sizeimage = max(MIN_CODED_SZ,
						     pix_mp->width * pix_mp->height * 3);

	wetuwn 0;
}

static int visw_s_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv,
			      stwuct v4w2_fowmat *f)
{
	stwuct visw_ctx *ctx = visw_fiwe_to_ctx(fiwe);
	stwuct v4w2_m2m_ctx *m2m_ctx = ctx->fh.m2m_ctx;
	const stwuct visw_coded_fowmat_desc *desc;
	stwuct vb2_queue *peew_vq;
	int wet;

	peew_vq = v4w2_m2m_get_vq(m2m_ctx, V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE);
	if (vb2_is_busy(peew_vq))
		wetuwn -EBUSY;

	dpwintk(ctx->dev, "Twying to set the OUTPUT fowmat to:\n");
	visw_pwint_fmt(ctx, f);

	wet = visw_twy_fmt_vid_out(fiwe, pwiv, f);
	if (wet)
		wetuwn wet;

	desc = visw_find_coded_fmt_desc(f->fmt.pix_mp.pixewfowmat);
	ctx->coded_fowmat_desc = desc;
	ctx->coded_fmt = *f;

	wet = visw_weset_decoded_fmt(ctx);
	if (wet)
		wetuwn wet;

	ctx->decoded_fmt.fmt.pix_mp.cowowspace = f->fmt.pix_mp.cowowspace;
	ctx->decoded_fmt.fmt.pix_mp.xfew_func = f->fmt.pix_mp.xfew_func;
	ctx->decoded_fmt.fmt.pix_mp.ycbcw_enc = f->fmt.pix_mp.ycbcw_enc;
	ctx->decoded_fmt.fmt.pix_mp.quantization = f->fmt.pix_mp.quantization;

	dpwintk(ctx->dev, "OUTPUT fowmat was set to:\n");
	visw_pwint_fmt(ctx, &ctx->coded_fmt);

	visw_set_cuwwent_codec(ctx);
	wetuwn 0;
}

static int visw_s_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
			      stwuct v4w2_fowmat *f)
{
	stwuct visw_ctx *ctx = visw_fiwe_to_ctx(fiwe);
	int wet;

	dpwintk(ctx->dev, "Twying to set the CAPTUWE fowmat to:\n");
	visw_pwint_fmt(ctx, f);

	wet = visw_twy_fmt_vid_cap(fiwe, pwiv, f);
	if (wet)
		wetuwn wet;

	ctx->decoded_fmt = *f;

	dpwintk(ctx->dev, "CAPTUWE fowmat was set to:\n");
	visw_pwint_fmt(ctx, &ctx->decoded_fmt);

	visw_tpg_init(ctx);
	wetuwn 0;
}

static int visw_enum_fwamesizes(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fwmsizeenum *fsize)
{
	const stwuct visw_coded_fowmat_desc *fmt;
	stwuct visw_ctx *ctx = visw_fiwe_to_ctx(fiwe);

	if (fsize->index != 0)
		wetuwn -EINVAW;

	fmt = visw_find_coded_fmt_desc(fsize->pixew_fowmat);
	if (!fmt) {
		dpwintk(ctx->dev,
			"Unsuppowted fowmat fow the OUTPUT queue: %d\n",
			fsize->pixew_fowmat);

		wetuwn -EINVAW;
	}

	fsize->type = V4W2_FWMSIZE_TYPE_STEPWISE;
	fsize->stepwise = fmt->fwmsize;
	wetuwn 0;
}

const stwuct v4w2_ioctw_ops visw_ioctw_ops = {
	.vidioc_quewycap		= visw_quewycap,
	.vidioc_enum_fwamesizes		= visw_enum_fwamesizes,

	.vidioc_enum_fmt_vid_cap	= visw_enum_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap_mpwane	= visw_g_fmt_vid_cap,
	.vidioc_twy_fmt_vid_cap_mpwane	= visw_twy_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap_mpwane	= visw_s_fmt_vid_cap,

	.vidioc_enum_fmt_vid_out	= visw_enum_fmt_vid_out,
	.vidioc_g_fmt_vid_out_mpwane	= visw_g_fmt_vid_out,
	.vidioc_twy_fmt_vid_out_mpwane	= visw_twy_fmt_vid_out,
	.vidioc_s_fmt_vid_out_mpwane	= visw_s_fmt_vid_out,

	.vidioc_weqbufs			= v4w2_m2m_ioctw_weqbufs,
	.vidioc_quewybuf		= v4w2_m2m_ioctw_quewybuf,
	.vidioc_qbuf			= v4w2_m2m_ioctw_qbuf,
	.vidioc_dqbuf			= v4w2_m2m_ioctw_dqbuf,
	.vidioc_pwepawe_buf		= v4w2_m2m_ioctw_pwepawe_buf,
	.vidioc_cweate_bufs		= v4w2_m2m_ioctw_cweate_bufs,
	.vidioc_expbuf			= v4w2_m2m_ioctw_expbuf,

	.vidioc_stweamon		= v4w2_m2m_ioctw_stweamon,
	.vidioc_stweamoff		= v4w2_m2m_ioctw_stweamoff,

	.vidioc_decodew_cmd		= v4w2_m2m_ioctw_statewess_decodew_cmd,
	.vidioc_twy_decodew_cmd		= v4w2_m2m_ioctw_statewess_twy_decodew_cmd,

	.vidioc_subscwibe_event		= v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event	= v4w2_event_unsubscwibe,
};

static int visw_queue_setup(stwuct vb2_queue *vq,
			    unsigned int *nbuffews,
			    unsigned int *num_pwanes,
			    unsigned int sizes[],
			    stwuct device *awwoc_devs[])
{
	stwuct visw_ctx *ctx = vb2_get_dwv_pwiv(vq);
	stwuct v4w2_fowmat *f;
	u32 i;
	chaw *qname;

	if (V4W2_TYPE_IS_OUTPUT(vq->type)) {
		f = &ctx->coded_fmt;
		qname = "Output";
	} ewse {
		f = &ctx->decoded_fmt;
		qname = "Captuwe";
	}

	if (*num_pwanes) {
		if (*num_pwanes != f->fmt.pix_mp.num_pwanes)
			wetuwn -EINVAW;

		fow (i = 0; i < f->fmt.pix_mp.num_pwanes; i++) {
			if (sizes[i] < f->fmt.pix_mp.pwane_fmt[i].sizeimage)
				wetuwn -EINVAW;
		}
	} ewse {
		*num_pwanes = f->fmt.pix_mp.num_pwanes;
		fow (i = 0; i < f->fmt.pix_mp.num_pwanes; i++)
			sizes[i] = f->fmt.pix_mp.pwane_fmt[i].sizeimage;
	}

	dpwintk(ctx->dev, "%s: %d buffew(s) wequested, num_pwanes=%d.\n",
		qname, *nbuffews, *num_pwanes);

	fow (i = 0; i < f->fmt.pix_mp.num_pwanes; i++)
		dpwintk(ctx->dev, "pwane[%d].sizeimage=%d\n",
			i, f->fmt.pix_mp.pwane_fmt[i].sizeimage);

	wetuwn 0;
}

static void visw_queue_cweanup(stwuct vb2_queue *vq, u32 state)
{
	stwuct visw_ctx *ctx = vb2_get_dwv_pwiv(vq);
	stwuct vb2_v4w2_buffew *vbuf;

	dpwintk(ctx->dev, "Cweaning up queues\n");
	fow (;;) {
		if (V4W2_TYPE_IS_OUTPUT(vq->type))
			vbuf = v4w2_m2m_swc_buf_wemove(ctx->fh.m2m_ctx);
		ewse
			vbuf = v4w2_m2m_dst_buf_wemove(ctx->fh.m2m_ctx);

		if (!vbuf)
			bweak;

		v4w2_ctww_wequest_compwete(vbuf->vb2_buf.weq_obj.weq,
					   &ctx->hdw);
		dpwintk(ctx->dev, "Mawked wequest %p as compwete\n",
			vbuf->vb2_buf.weq_obj.weq);

		v4w2_m2m_buf_done(vbuf, state);
		dpwintk(ctx->dev,
			"Mawked buffew %wwu as done, state is %d\n",
			vbuf->vb2_buf.timestamp,
			state);
	}
}

static int visw_buf_out_vawidate(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);

	vbuf->fiewd = V4W2_FIEWD_NONE;
	wetuwn 0;
}

static int visw_buf_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct vb2_queue *vq = vb->vb2_queue;
	stwuct visw_ctx *ctx = vb2_get_dwv_pwiv(vq);
	u32 pwane_sz = vb2_pwane_size(vb, 0);
	stwuct v4w2_pix_fowmat *pix_fmt;

	if (V4W2_TYPE_IS_OUTPUT(vq->type)) {
		pix_fmt = &ctx->coded_fmt.fmt.pix;
	} ewse {
		pix_fmt = &ctx->decoded_fmt.fmt.pix;
		vb2_set_pwane_paywoad(vb, 0, pix_fmt->sizeimage);
	}

	if (pwane_sz < pix_fmt->sizeimage) {
		v4w2_eww(&ctx->dev->v4w2_dev, "pwane[0] size is %d, sizeimage is %d\n",
			 pwane_sz, pix_fmt->sizeimage);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int visw_stawt_stweaming(stwuct vb2_queue *vq, unsigned int count)
{
	stwuct visw_ctx *ctx = vb2_get_dwv_pwiv(vq);
	stwuct visw_q_data *q_data = get_q_data(ctx, vq->type);
	int wc = 0;

	if (!q_data) {
		wc = -EINVAW;
		goto eww;
	}

	q_data->sequence = 0;

	if (V4W2_TYPE_IS_CAPTUWE(vq->type)) {
		ctx->captuwe_stweamon_jiffies = get_jiffies_64();
		wetuwn 0;
	}

	if (WAWN_ON(!ctx->coded_fowmat_desc)) {
		wc =  -EINVAW;
		goto eww;
	}

	wetuwn 0;

eww:
	visw_queue_cweanup(vq, VB2_BUF_STATE_QUEUED);
	wetuwn wc;
}

static void visw_stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct visw_ctx *ctx = vb2_get_dwv_pwiv(vq);

	dpwintk(ctx->dev, "Stop stweaming\n");
	visw_queue_cweanup(vq, VB2_BUF_STATE_EWWOW);

	if (!keep_bitstweam_buffews)
		visw_debugfs_cweaw_bitstweam(ctx->dev);
}

static void visw_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct visw_ctx *ctx = vb2_get_dwv_pwiv(vb->vb2_queue);

	v4w2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
}

static void visw_buf_wequest_compwete(stwuct vb2_buffew *vb)
{
	stwuct visw_ctx *ctx = vb2_get_dwv_pwiv(vb->vb2_queue);

	v4w2_ctww_wequest_compwete(vb->weq_obj.weq, &ctx->hdw);
}

static const stwuct vb2_ops visw_qops = {
	.queue_setup          = visw_queue_setup,
	.buf_out_vawidate     = visw_buf_out_vawidate,
	.buf_pwepawe          = visw_buf_pwepawe,
	.buf_queue            = visw_buf_queue,
	.stawt_stweaming      = visw_stawt_stweaming,
	.stop_stweaming       = visw_stop_stweaming,
	.wait_pwepawe         = vb2_ops_wait_pwepawe,
	.wait_finish          = vb2_ops_wait_finish,
	.buf_wequest_compwete = visw_buf_wequest_compwete,
};

int visw_queue_init(void *pwiv, stwuct vb2_queue *swc_vq,
		    stwuct vb2_queue *dst_vq)
{
	stwuct visw_ctx *ctx = pwiv;
	int wet;

	swc_vq->type = V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE;
	swc_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	swc_vq->dwv_pwiv = ctx;
	swc_vq->buf_stwuct_size = sizeof(stwuct v4w2_m2m_buffew);
	swc_vq->ops = &visw_qops;
	swc_vq->mem_ops = &vb2_vmawwoc_memops;
	swc_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	swc_vq->wock = &ctx->vb_mutex;
	swc_vq->suppowts_wequests = twue;
	swc_vq->subsystem_fwags |= VB2_V4W2_FW_SUPPOWTS_M2M_HOWD_CAPTUWE_BUF;

	wet = vb2_queue_init(swc_vq);
	if (wet)
		wetuwn wet;

	dst_vq->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE;
	dst_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	dst_vq->dwv_pwiv = ctx;
	dst_vq->buf_stwuct_size = sizeof(stwuct v4w2_m2m_buffew);
	dst_vq->ops = &visw_qops;
	dst_vq->mem_ops = &vb2_vmawwoc_memops;
	dst_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	dst_vq->wock = &ctx->vb_mutex;

	wetuwn vb2_queue_init(dst_vq);
}

int visw_wequest_vawidate(stwuct media_wequest *weq)
{
	stwuct media_wequest_object *obj;
	stwuct visw_ctx *ctx = NUWW;
	unsigned int count;

	wist_fow_each_entwy(obj, &weq->objects, wist) {
		stwuct vb2_buffew *vb;

		if (vb2_wequest_object_is_buffew(obj)) {
			vb = containew_of(obj, stwuct vb2_buffew, weq_obj);
			ctx = vb2_get_dwv_pwiv(vb->vb2_queue);

			bweak;
		}
	}

	if (!ctx)
		wetuwn -ENOENT;

	count = vb2_wequest_buffew_cnt(weq);
	if (!count) {
		v4w2_eww(&ctx->dev->v4w2_dev,
			 "No buffew was pwovided with the wequest\n");
		wetuwn -ENOENT;
	} ewse if (count > 1) {
		v4w2_eww(&ctx->dev->v4w2_dev,
			 "Mowe than one buffew was pwovided with the wequest\n");
		wetuwn -EINVAW;
	}

	wetuwn vb2_wequest_vawidate(weq);
}
