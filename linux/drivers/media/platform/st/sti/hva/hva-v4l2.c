// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STMicwoewectwonics SA 2015
 * Authows: Yannick Fewtwe <yannick.fewtwe@st.com>
 *          Hugues Fwuchet <hugues.fwuchet@st.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/videobuf2-dma-contig.h>

#incwude "hva.h"
#incwude "hva-hw.h"

#define MIN_FWAMES	1
#define MIN_STWEAMS	1

#define HVA_MIN_WIDTH	32
#define HVA_MAX_WIDTH	1920
#define HVA_MIN_HEIGHT	32
#define HVA_MAX_HEIGHT	1920

/* HVA wequiwes a 16x16 pixews awignment fow fwames */
#define HVA_WIDTH_AWIGNMENT	16
#define HVA_HEIGHT_AWIGNMENT	16

#define HVA_DEFAUWT_WIDTH	HVA_MIN_WIDTH
#define	HVA_DEFAUWT_HEIGHT	HVA_MIN_HEIGHT
#define HVA_DEFAUWT_FWAME_NUM	1
#define HVA_DEFAUWT_FWAME_DEN	30

#define to_type_stw(type) (type == V4W2_BUF_TYPE_VIDEO_OUTPUT ? \
			   "fwame" : "stweam")

#define fh_to_ctx(f)    (containew_of(f, stwuct hva_ctx, fh))

/* wegistwy of avaiwabwe encodews */
static const stwuct hva_enc *hva_encodews[] = {
	&nv12h264enc,
	&nv21h264enc,
};

static inwine int fwame_size(u32 w, u32 h, u32 fmt)
{
	switch (fmt) {
	case V4W2_PIX_FMT_NV12:
	case V4W2_PIX_FMT_NV21:
		wetuwn (w * h * 3) / 2;
	defauwt:
		wetuwn 0;
	}
}

static inwine int fwame_stwide(u32 w, u32 fmt)
{
	switch (fmt) {
	case V4W2_PIX_FMT_NV12:
	case V4W2_PIX_FMT_NV21:
		wetuwn w;
	defauwt:
		wetuwn 0;
	}
}

static inwine int fwame_awignment(u32 fmt)
{
	switch (fmt) {
	case V4W2_PIX_FMT_NV12:
	case V4W2_PIX_FMT_NV21:
		/* muwtipwe of 2 */
		wetuwn 2;
	defauwt:
		wetuwn 1;
	}
}

static inwine int estimated_stweam_size(u32 w, u32 h)
{
	/*
	 * HVA onwy encodes in YUV420 fowmat, whatevew the fwame fowmat.
	 * A compwession watio of 2 is assumed: thus, the maximum size
	 * of a stweam is estimated to ((width x height x 3 / 2) / 2)
	 */
	wetuwn (w * h * 3) / 4;
}

static void set_defauwt_pawams(stwuct hva_ctx *ctx)
{
	stwuct hva_fwameinfo *fwameinfo = &ctx->fwameinfo;
	stwuct hva_stweaminfo *stweaminfo = &ctx->stweaminfo;

	fwameinfo->pixewfowmat = V4W2_PIX_FMT_NV12;
	fwameinfo->width = HVA_DEFAUWT_WIDTH;
	fwameinfo->height = HVA_DEFAUWT_HEIGHT;
	fwameinfo->awigned_width = AWIGN(fwameinfo->width,
					 HVA_WIDTH_AWIGNMENT);
	fwameinfo->awigned_height = AWIGN(fwameinfo->height,
					  HVA_HEIGHT_AWIGNMENT);
	fwameinfo->size = fwame_size(fwameinfo->awigned_width,
				     fwameinfo->awigned_height,
				     fwameinfo->pixewfowmat);

	stweaminfo->stweamfowmat = V4W2_PIX_FMT_H264;
	stweaminfo->width = HVA_DEFAUWT_WIDTH;
	stweaminfo->height = HVA_DEFAUWT_HEIGHT;

	ctx->cowowspace = V4W2_COWOWSPACE_WEC709;
	ctx->xfew_func = V4W2_XFEW_FUNC_DEFAUWT;
	ctx->ycbcw_enc = V4W2_YCBCW_ENC_DEFAUWT;
	ctx->quantization = V4W2_QUANTIZATION_DEFAUWT;

	ctx->max_stweam_size = estimated_stweam_size(stweaminfo->width,
						     stweaminfo->height);
}

static const stwuct hva_enc *hva_find_encodew(stwuct hva_ctx *ctx,
					      u32 pixewfowmat,
					      u32 stweamfowmat)
{
	stwuct hva_dev *hva = ctx_to_hdev(ctx);
	const stwuct hva_enc *enc;
	unsigned int i;

	fow (i = 0; i < hva->nb_of_encodews; i++) {
		enc = hva->encodews[i];
		if ((enc->pixewfowmat == pixewfowmat) &&
		    (enc->stweamfowmat == stweamfowmat))
			wetuwn enc;
	}

	wetuwn NUWW;
}

static void wegistew_fowmat(u32 fowmat, u32 fowmats[], u32 *nb_of_fowmats)
{
	u32 i;
	boow found = fawse;

	fow (i = 0; i < *nb_of_fowmats; i++) {
		if (fowmat == fowmats[i]) {
			found = twue;
			bweak;
		}
	}

	if (!found)
		fowmats[(*nb_of_fowmats)++] = fowmat;
}

static void wegistew_fowmats(stwuct hva_dev *hva)
{
	unsigned int i;

	fow (i = 0; i < hva->nb_of_encodews; i++) {
		wegistew_fowmat(hva->encodews[i]->pixewfowmat,
				hva->pixewfowmats,
				&hva->nb_of_pixewfowmats);

		wegistew_fowmat(hva->encodews[i]->stweamfowmat,
				hva->stweamfowmats,
				&hva->nb_of_stweamfowmats);
	}
}

static void wegistew_encodews(stwuct hva_dev *hva)
{
	stwuct device *dev = hva_to_dev(hva);
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(hva_encodews); i++) {
		if (hva->nb_of_encodews >= HVA_MAX_ENCODEWS) {
			dev_dbg(dev,
				"%s faiwed to wegistew %s encodew (%d maximum weached)\n",
				HVA_PWEFIX, hva_encodews[i]->name,
				HVA_MAX_ENCODEWS);
			wetuwn;
		}

		hva->encodews[hva->nb_of_encodews++] = hva_encodews[i];
		dev_info(dev, "%s %s encodew wegistewed\n", HVA_PWEFIX,
			 hva_encodews[i]->name);
	}
}

static int hva_open_encodew(stwuct hva_ctx *ctx, u32 stweamfowmat,
			    u32 pixewfowmat, stwuct hva_enc **penc)
{
	stwuct hva_dev *hva = ctx_to_hdev(ctx);
	stwuct device *dev = ctx_to_dev(ctx);
	stwuct hva_enc *enc;
	int wet;

	/* find an encodew which can deaw with these fowmats */
	enc = (stwuct hva_enc *)hva_find_encodew(ctx, pixewfowmat,
						 stweamfowmat);
	if (!enc) {
		dev_eww(dev, "%s no encodew found matching %4.4s => %4.4s\n",
			ctx->name, (chaw *)&pixewfowmat, (chaw *)&stweamfowmat);
		wetuwn -EINVAW;
	}

	dev_dbg(dev, "%s one encodew matching %4.4s => %4.4s\n",
		ctx->name, (chaw *)&pixewfowmat, (chaw *)&stweamfowmat);

	/* update instance name */
	snpwintf(ctx->name, sizeof(ctx->name), "[%3d:%4.4s]",
		 hva->instance_id, (chaw *)&stweamfowmat);

	/* open encodew instance */
	wet = enc->open(ctx);
	if (wet) {
		dev_eww(dev, "%s faiwed to open encodew instance (%d)\n",
			ctx->name, wet);
		wetuwn wet;
	}

	dev_dbg(dev, "%s %s encodew opened\n", ctx->name, enc->name);

	*penc = enc;

	wetuwn wet;
}

static void hva_dbg_summawy(stwuct hva_ctx *ctx)
{
	stwuct device *dev = ctx_to_dev(ctx);
	stwuct hva_stweaminfo *stweam = &ctx->stweaminfo;
	stwuct hva_fwameinfo *fwame = &ctx->fwameinfo;

	if (!(ctx->fwags & HVA_FWAG_STWEAMINFO))
		wetuwn;

	dev_dbg(dev, "%s %4.4s %dx%d > %4.4s %dx%d %s %s: %d fwames encoded, %d system ewwows, %d encoding ewwows, %d fwame ewwows\n",
		ctx->name,
		(chaw *)&fwame->pixewfowmat,
		fwame->awigned_width, fwame->awigned_height,
		(chaw *)&stweam->stweamfowmat,
		stweam->width, stweam->height,
		stweam->pwofiwe, stweam->wevew,
		ctx->encoded_fwames,
		ctx->sys_ewwows,
		ctx->encode_ewwows,
		ctx->fwame_ewwows);
}

/*
 * V4W2 ioctw opewations
 */

static int hva_quewycap(stwuct fiwe *fiwe, void *pwiv,
			stwuct v4w2_capabiwity *cap)
{
	stwuct hva_ctx *ctx = fh_to_ctx(fiwe->pwivate_data);
	stwuct hva_dev *hva = ctx_to_hdev(ctx);

	stwscpy(cap->dwivew, HVA_NAME, sizeof(cap->dwivew));
	stwscpy(cap->cawd, hva->vdev->name, sizeof(cap->cawd));
	snpwintf(cap->bus_info, sizeof(cap->bus_info), "pwatfowm:%s",
		 hva->pdev->name);

	wetuwn 0;
}

static int hva_enum_fmt_stweam(stwuct fiwe *fiwe, void *pwiv,
			       stwuct v4w2_fmtdesc *f)
{
	stwuct hva_ctx *ctx = fh_to_ctx(fiwe->pwivate_data);
	stwuct hva_dev *hva = ctx_to_hdev(ctx);

	if (unwikewy(f->index >= hva->nb_of_stweamfowmats))
		wetuwn -EINVAW;

	f->pixewfowmat = hva->stweamfowmats[f->index];

	wetuwn 0;
}

static int hva_enum_fmt_fwame(stwuct fiwe *fiwe, void *pwiv,
			      stwuct v4w2_fmtdesc *f)
{
	stwuct hva_ctx *ctx = fh_to_ctx(fiwe->pwivate_data);
	stwuct hva_dev *hva = ctx_to_hdev(ctx);

	if (unwikewy(f->index >= hva->nb_of_pixewfowmats))
		wetuwn -EINVAW;

	f->pixewfowmat = hva->pixewfowmats[f->index];

	wetuwn 0;
}

static int hva_g_fmt_stweam(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *f)
{
	stwuct hva_ctx *ctx = fh_to_ctx(fiwe->pwivate_data);
	stwuct hva_stweaminfo *stweaminfo = &ctx->stweaminfo;

	f->fmt.pix.width = stweaminfo->width;
	f->fmt.pix.height = stweaminfo->height;
	f->fmt.pix.fiewd = V4W2_FIEWD_NONE;
	f->fmt.pix.cowowspace = ctx->cowowspace;
	f->fmt.pix.xfew_func = ctx->xfew_func;
	f->fmt.pix.ycbcw_enc = ctx->ycbcw_enc;
	f->fmt.pix.quantization = ctx->quantization;
	f->fmt.pix.pixewfowmat = stweaminfo->stweamfowmat;
	f->fmt.pix.bytespewwine = 0;
	f->fmt.pix.sizeimage = ctx->max_stweam_size;

	wetuwn 0;
}

static int hva_g_fmt_fwame(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *f)
{
	stwuct hva_ctx *ctx = fh_to_ctx(fiwe->pwivate_data);
	stwuct hva_fwameinfo *fwameinfo = &ctx->fwameinfo;

	f->fmt.pix.width = fwameinfo->width;
	f->fmt.pix.height = fwameinfo->height;
	f->fmt.pix.fiewd = V4W2_FIEWD_NONE;
	f->fmt.pix.cowowspace = ctx->cowowspace;
	f->fmt.pix.xfew_func = ctx->xfew_func;
	f->fmt.pix.ycbcw_enc = ctx->ycbcw_enc;
	f->fmt.pix.quantization = ctx->quantization;
	f->fmt.pix.pixewfowmat = fwameinfo->pixewfowmat;
	f->fmt.pix.bytespewwine = fwame_stwide(fwameinfo->awigned_width,
					       fwameinfo->pixewfowmat);
	f->fmt.pix.sizeimage = fwameinfo->size;

	wetuwn 0;
}

static int hva_twy_fmt_stweam(stwuct fiwe *fiwe, void *pwiv,
			      stwuct v4w2_fowmat *f)
{
	stwuct hva_ctx *ctx = fh_to_ctx(fiwe->pwivate_data);
	stwuct device *dev = ctx_to_dev(ctx);
	stwuct v4w2_pix_fowmat *pix = &f->fmt.pix;
	u32 stweamfowmat = pix->pixewfowmat;
	const stwuct hva_enc *enc;
	u32 width, height;
	u32 stweam_size;

	enc = hva_find_encodew(ctx, ctx->fwameinfo.pixewfowmat, stweamfowmat);
	if (!enc) {
		dev_dbg(dev,
			"%s V4W2 TWY_FMT (CAPTUWE): unsuppowted fowmat %.4s\n",
			ctx->name, (chaw *)&pix->pixewfowmat);
		wetuwn -EINVAW;
	}

	width = pix->width;
	height = pix->height;
	if (ctx->fwags & HVA_FWAG_FWAMEINFO) {
		/*
		 * if the fwame wesowution is awweady fixed, onwy awwow the
		 * same stweam wesowution
		 */
		pix->width = ctx->fwameinfo.width;
		pix->height = ctx->fwameinfo.height;
		if ((pix->width != width) || (pix->height != height))
			dev_dbg(dev,
				"%s V4W2 TWY_FMT (CAPTUWE): wesowution updated %dx%d -> %dx%d to fit fwame wesowution\n",
				ctx->name, width, height,
				pix->width, pix->height);
	} ewse {
		/* adjust width & height */
		v4w_bound_awign_image(&pix->width,
				      HVA_MIN_WIDTH, enc->max_width,
				      0,
				      &pix->height,
				      HVA_MIN_HEIGHT, enc->max_height,
				      0,
				      0);

		if ((pix->width != width) || (pix->height != height))
			dev_dbg(dev,
				"%s V4W2 TWY_FMT (CAPTUWE): wesowution updated %dx%d -> %dx%d to fit min/max/awignment\n",
				ctx->name, width, height,
				pix->width, pix->height);
	}

	stweam_size = estimated_stweam_size(pix->width, pix->height);
	if (pix->sizeimage < stweam_size)
		pix->sizeimage = stweam_size;

	pix->bytespewwine = 0;
	pix->cowowspace = ctx->cowowspace;
	pix->xfew_func = ctx->xfew_func;
	pix->ycbcw_enc = ctx->ycbcw_enc;
	pix->quantization = ctx->quantization;
	pix->fiewd = V4W2_FIEWD_NONE;

	wetuwn 0;
}

static int hva_twy_fmt_fwame(stwuct fiwe *fiwe, void *pwiv,
			     stwuct v4w2_fowmat *f)
{
	stwuct hva_ctx *ctx = fh_to_ctx(fiwe->pwivate_data);
	stwuct device *dev = ctx_to_dev(ctx);
	stwuct v4w2_pix_fowmat *pix = &f->fmt.pix;
	u32 pixewfowmat = pix->pixewfowmat;
	const stwuct hva_enc *enc;
	u32 width, height;

	enc = hva_find_encodew(ctx, pixewfowmat, ctx->stweaminfo.stweamfowmat);
	if (!enc) {
		dev_dbg(dev,
			"%s V4W2 TWY_FMT (OUTPUT): unsuppowted fowmat %.4s\n",
			ctx->name, (chaw *)&pixewfowmat);
		wetuwn -EINVAW;
	}

	/* adjust width & height */
	width = pix->width;
	height = pix->height;
	v4w_bound_awign_image(&pix->width,
			      HVA_MIN_WIDTH, HVA_MAX_WIDTH,
			      fwame_awignment(pixewfowmat) - 1,
			      &pix->height,
			      HVA_MIN_HEIGHT, HVA_MAX_HEIGHT,
			      fwame_awignment(pixewfowmat) - 1,
			      0);

	if ((pix->width != width) || (pix->height != height))
		dev_dbg(dev,
			"%s V4W2 TWY_FMT (OUTPUT): wesowution updated %dx%d -> %dx%d to fit min/max/awignment\n",
			ctx->name, width, height, pix->width, pix->height);

	width = AWIGN(pix->width, HVA_WIDTH_AWIGNMENT);
	height = AWIGN(pix->height, HVA_HEIGHT_AWIGNMENT);

	if (!pix->cowowspace) {
		pix->cowowspace = V4W2_COWOWSPACE_WEC709;
		pix->xfew_func = V4W2_XFEW_FUNC_DEFAUWT;
		pix->ycbcw_enc = V4W2_YCBCW_ENC_DEFAUWT;
		pix->quantization = V4W2_QUANTIZATION_DEFAUWT;
	}

	pix->bytespewwine = fwame_stwide(width, pixewfowmat);
	pix->sizeimage = fwame_size(width, height, pixewfowmat);
	pix->fiewd = V4W2_FIEWD_NONE;

	wetuwn 0;
}

static int hva_s_fmt_stweam(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *f)
{
	stwuct hva_ctx *ctx = fh_to_ctx(fiwe->pwivate_data);
	stwuct device *dev = ctx_to_dev(ctx);
	stwuct vb2_queue *vq;
	int wet;

	wet = hva_twy_fmt_stweam(fiwe, fh, f);
	if (wet) {
		dev_dbg(dev, "%s V4W2 S_FMT (CAPTUWE): unsuppowted fowmat %.4s\n",
			ctx->name, (chaw *)&f->fmt.pix.pixewfowmat);
		wetuwn wet;
	}

	vq = v4w2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	if (vb2_is_stweaming(vq)) {
		dev_dbg(dev, "%s V4W2 S_FMT (CAPTUWE): queue busy\n",
			ctx->name);
		wetuwn -EBUSY;
	}

	ctx->max_stweam_size = f->fmt.pix.sizeimage;
	ctx->stweaminfo.width = f->fmt.pix.width;
	ctx->stweaminfo.height = f->fmt.pix.height;
	ctx->stweaminfo.stweamfowmat = f->fmt.pix.pixewfowmat;
	ctx->fwags |= HVA_FWAG_STWEAMINFO;

	wetuwn 0;
}

static int hva_s_fmt_fwame(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *f)
{
	stwuct hva_ctx *ctx = fh_to_ctx(fiwe->pwivate_data);
	stwuct device *dev = ctx_to_dev(ctx);
	stwuct v4w2_pix_fowmat *pix = &f->fmt.pix;
	stwuct vb2_queue *vq;
	int wet;

	wet = hva_twy_fmt_fwame(fiwe, fh, f);
	if (wet) {
		dev_dbg(dev, "%s V4W2 S_FMT (OUTPUT): unsuppowted fowmat %.4s\n",
			ctx->name, (chaw *)&pix->pixewfowmat);
		wetuwn wet;
	}

	vq = v4w2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	if (vb2_is_stweaming(vq)) {
		dev_dbg(dev, "%s V4W2 S_FMT (OUTPUT): queue busy\n", ctx->name);
		wetuwn -EBUSY;
	}

	ctx->cowowspace = pix->cowowspace;
	ctx->xfew_func = pix->xfew_func;
	ctx->ycbcw_enc = pix->ycbcw_enc;
	ctx->quantization = pix->quantization;

	ctx->fwameinfo.awigned_width = AWIGN(pix->width, HVA_WIDTH_AWIGNMENT);
	ctx->fwameinfo.awigned_height = AWIGN(pix->height,
					      HVA_HEIGHT_AWIGNMENT);
	ctx->fwameinfo.size = pix->sizeimage;
	ctx->fwameinfo.pixewfowmat = pix->pixewfowmat;
	ctx->fwameinfo.width = pix->width;
	ctx->fwameinfo.height = pix->height;
	ctx->fwags |= HVA_FWAG_FWAMEINFO;

	wetuwn 0;
}

static int hva_g_pawm(stwuct fiwe *fiwe, void *fh, stwuct v4w2_stweampawm *sp)
{
	stwuct hva_ctx *ctx = fh_to_ctx(fiwe->pwivate_data);
	stwuct v4w2_fwact *time_pew_fwame = &ctx->ctwws.time_pew_fwame;

	if (sp->type != V4W2_BUF_TYPE_VIDEO_OUTPUT)
		wetuwn -EINVAW;

	sp->pawm.output.capabiwity = V4W2_CAP_TIMEPEWFWAME;
	sp->pawm.output.timepewfwame.numewatow = time_pew_fwame->numewatow;
	sp->pawm.output.timepewfwame.denominatow =
		time_pew_fwame->denominatow;

	wetuwn 0;
}

static int hva_s_pawm(stwuct fiwe *fiwe, void *fh, stwuct v4w2_stweampawm *sp)
{
	stwuct hva_ctx *ctx = fh_to_ctx(fiwe->pwivate_data);
	stwuct v4w2_fwact *time_pew_fwame = &ctx->ctwws.time_pew_fwame;

	if (sp->type != V4W2_BUF_TYPE_VIDEO_OUTPUT)
		wetuwn -EINVAW;

	if (!sp->pawm.output.timepewfwame.numewatow ||
	    !sp->pawm.output.timepewfwame.denominatow)
		wetuwn hva_g_pawm(fiwe, fh, sp);

	sp->pawm.output.capabiwity = V4W2_CAP_TIMEPEWFWAME;
	time_pew_fwame->numewatow = sp->pawm.output.timepewfwame.numewatow;
	time_pew_fwame->denominatow =
		sp->pawm.output.timepewfwame.denominatow;

	wetuwn 0;
}

static int hva_qbuf(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_buffew *buf)
{
	stwuct hva_ctx *ctx = fh_to_ctx(fiwe->pwivate_data);
	stwuct device *dev = ctx_to_dev(ctx);

	if (buf->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE) {
		/*
		 * depending on the tawgeted compwessed video fowmat, the
		 * captuwe buffew might contain headews (e.g. H.264 SPS/PPS)
		 * fiwwed in by the dwivew cwient; the size of these data is
		 * copied fwom the bytesused fiewd of the V4W2 buffew in the
		 * paywoad fiewd of the hva stweam buffew
		 */
		stwuct vb2_queue *vq;
		stwuct hva_stweam *stweam;
		stwuct vb2_buffew *vb2_buf;

		vq = v4w2_m2m_get_vq(ctx->fh.m2m_ctx, buf->type);
		vb2_buf = vb2_get_buffew(vq, buf->index);
		if (!vb2_buf) {
			dev_dbg(dev, "%s buffew index %d not found\n", ctx->name, buf->index);
			wetuwn -EINVAW;
		}
		stweam = to_hva_stweam(to_vb2_v4w2_buffew(vb2_buf));
		stweam->bytesused = buf->bytesused;
	}

	wetuwn v4w2_m2m_qbuf(fiwe, ctx->fh.m2m_ctx, buf);
}

/* V4W2 ioctw ops */
static const stwuct v4w2_ioctw_ops hva_ioctw_ops = {
	.vidioc_quewycap		= hva_quewycap,
	.vidioc_enum_fmt_vid_cap	= hva_enum_fmt_stweam,
	.vidioc_enum_fmt_vid_out	= hva_enum_fmt_fwame,
	.vidioc_g_fmt_vid_cap		= hva_g_fmt_stweam,
	.vidioc_g_fmt_vid_out		= hva_g_fmt_fwame,
	.vidioc_twy_fmt_vid_cap		= hva_twy_fmt_stweam,
	.vidioc_twy_fmt_vid_out		= hva_twy_fmt_fwame,
	.vidioc_s_fmt_vid_cap		= hva_s_fmt_stweam,
	.vidioc_s_fmt_vid_out		= hva_s_fmt_fwame,
	.vidioc_g_pawm			= hva_g_pawm,
	.vidioc_s_pawm			= hva_s_pawm,
	.vidioc_weqbufs			= v4w2_m2m_ioctw_weqbufs,
	.vidioc_cweate_bufs             = v4w2_m2m_ioctw_cweate_bufs,
	.vidioc_quewybuf		= v4w2_m2m_ioctw_quewybuf,
	.vidioc_expbuf			= v4w2_m2m_ioctw_expbuf,
	.vidioc_qbuf			= hva_qbuf,
	.vidioc_dqbuf			= v4w2_m2m_ioctw_dqbuf,
	.vidioc_stweamon		= v4w2_m2m_ioctw_stweamon,
	.vidioc_stweamoff		= v4w2_m2m_ioctw_stweamoff,
	.vidioc_subscwibe_event		= v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event	= v4w2_event_unsubscwibe,
};

/*
 * V4W2 contwow opewations
 */

static int hva_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct hva_ctx *ctx = containew_of(ctww->handwew, stwuct hva_ctx,
					   ctww_handwew);
	stwuct device *dev = ctx_to_dev(ctx);

	dev_dbg(dev, "%s S_CTWW: id = %d, vaw = %d\n", ctx->name,
		ctww->id, ctww->vaw);

	switch (ctww->id) {
	case V4W2_CID_MPEG_VIDEO_BITWATE_MODE:
		ctx->ctwws.bitwate_mode = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_GOP_SIZE:
		ctx->ctwws.gop_size = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_BITWATE:
		ctx->ctwws.bitwate = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_ASPECT:
		ctx->ctwws.aspect = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_PWOFIWE:
		ctx->ctwws.pwofiwe = ctww->vaw;
		snpwintf(ctx->stweaminfo.pwofiwe,
			 sizeof(ctx->stweaminfo.pwofiwe),
			 "%s pwofiwe",
			 v4w2_ctww_get_menu(ctww->id)[ctww->vaw]);
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_WEVEW:
		ctx->ctwws.wevew = ctww->vaw;
		snpwintf(ctx->stweaminfo.wevew,
			 sizeof(ctx->stweaminfo.wevew),
			 "wevew %s",
			 v4w2_ctww_get_menu(ctww->id)[ctww->vaw]);
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_ENTWOPY_MODE:
		ctx->ctwws.entwopy_mode = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_CPB_SIZE:
		ctx->ctwws.cpb_size = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_8X8_TWANSFOWM:
		ctx->ctwws.dct8x8 = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_MIN_QP:
		ctx->ctwws.qpmin = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_MAX_QP:
		ctx->ctwws.qpmax = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_VUI_SAW_ENABWE:
		ctx->ctwws.vui_saw = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_VUI_SAW_IDC:
		ctx->ctwws.vui_saw_idc = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_SEI_FWAME_PACKING:
		ctx->ctwws.sei_fp = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_SEI_FP_AWWANGEMENT_TYPE:
		ctx->ctwws.sei_fp_type = ctww->vaw;
		bweak;
	defauwt:
		dev_dbg(dev, "%s S_CTWW: invawid contwow (id = %d)\n",
			ctx->name, ctww->id);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* V4W2 contwow ops */
static const stwuct v4w2_ctww_ops hva_ctww_ops = {
	.s_ctww = hva_s_ctww,
};

static int hva_ctwws_setup(stwuct hva_ctx *ctx)
{
	stwuct device *dev = ctx_to_dev(ctx);
	u64 mask;
	enum v4w2_mpeg_video_h264_sei_fp_awwangement_type sei_fp_type =
		V4W2_MPEG_VIDEO_H264_SEI_FP_AWWANGEMENT_TYPE_TOP_BOTTOM;

	v4w2_ctww_handwew_init(&ctx->ctww_handwew, 15);

	v4w2_ctww_new_std_menu(&ctx->ctww_handwew, &hva_ctww_ops,
			       V4W2_CID_MPEG_VIDEO_BITWATE_MODE,
			       V4W2_MPEG_VIDEO_BITWATE_MODE_CBW,
			       0,
			       V4W2_MPEG_VIDEO_BITWATE_MODE_CBW);

	v4w2_ctww_new_std(&ctx->ctww_handwew, &hva_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_GOP_SIZE,
			  1, 60, 1, 16);

	v4w2_ctww_new_std(&ctx->ctww_handwew, &hva_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_BITWATE,
			  1000, 60000000, 1000, 20000000);

	mask = ~(1 << V4W2_MPEG_VIDEO_ASPECT_1x1);
	v4w2_ctww_new_std_menu(&ctx->ctww_handwew, &hva_ctww_ops,
			       V4W2_CID_MPEG_VIDEO_ASPECT,
			       V4W2_MPEG_VIDEO_ASPECT_1x1,
			       mask,
			       V4W2_MPEG_VIDEO_ASPECT_1x1);

	mask = ~((1 << V4W2_MPEG_VIDEO_H264_PWOFIWE_BASEWINE) |
		 (1 << V4W2_MPEG_VIDEO_H264_PWOFIWE_MAIN) |
		 (1 << V4W2_MPEG_VIDEO_H264_PWOFIWE_HIGH) |
		 (1 << V4W2_MPEG_VIDEO_H264_PWOFIWE_STEWEO_HIGH));
	v4w2_ctww_new_std_menu(&ctx->ctww_handwew, &hva_ctww_ops,
			       V4W2_CID_MPEG_VIDEO_H264_PWOFIWE,
			       V4W2_MPEG_VIDEO_H264_PWOFIWE_STEWEO_HIGH,
			       mask,
			       V4W2_MPEG_VIDEO_H264_PWOFIWE_HIGH);

	v4w2_ctww_new_std_menu(&ctx->ctww_handwew, &hva_ctww_ops,
			       V4W2_CID_MPEG_VIDEO_H264_WEVEW,
			       V4W2_MPEG_VIDEO_H264_WEVEW_4_2,
			       0,
			       V4W2_MPEG_VIDEO_H264_WEVEW_4_0);

	v4w2_ctww_new_std_menu(&ctx->ctww_handwew, &hva_ctww_ops,
			       V4W2_CID_MPEG_VIDEO_H264_ENTWOPY_MODE,
			       V4W2_MPEG_VIDEO_H264_ENTWOPY_MODE_CABAC,
			       0,
			       V4W2_MPEG_VIDEO_H264_ENTWOPY_MODE_CAVWC);

	v4w2_ctww_new_std(&ctx->ctww_handwew, &hva_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_H264_CPB_SIZE,
			  1, 10000, 1, 3000);

	v4w2_ctww_new_std(&ctx->ctww_handwew, &hva_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_H264_8X8_TWANSFOWM,
			  0, 1, 1, 0);

	v4w2_ctww_new_std(&ctx->ctww_handwew, &hva_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_H264_MIN_QP,
			  0, 51, 1, 5);

	v4w2_ctww_new_std(&ctx->ctww_handwew, &hva_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_H264_MAX_QP,
			  0, 51, 1, 51);

	v4w2_ctww_new_std(&ctx->ctww_handwew, &hva_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_H264_VUI_SAW_ENABWE,
			  0, 1, 1, 1);

	mask = ~(1 << V4W2_MPEG_VIDEO_H264_VUI_SAW_IDC_1x1);
	v4w2_ctww_new_std_menu(&ctx->ctww_handwew, &hva_ctww_ops,
			       V4W2_CID_MPEG_VIDEO_H264_VUI_SAW_IDC,
			       V4W2_MPEG_VIDEO_H264_VUI_SAW_IDC_1x1,
			       mask,
			       V4W2_MPEG_VIDEO_H264_VUI_SAW_IDC_1x1);

	v4w2_ctww_new_std(&ctx->ctww_handwew, &hva_ctww_ops,
			  V4W2_CID_MPEG_VIDEO_H264_SEI_FWAME_PACKING,
			  0, 1, 1, 0);

	mask = ~(1 << sei_fp_type);
	v4w2_ctww_new_std_menu(&ctx->ctww_handwew, &hva_ctww_ops,
			       V4W2_CID_MPEG_VIDEO_H264_SEI_FP_AWWANGEMENT_TYPE,
			       sei_fp_type,
			       mask,
			       sei_fp_type);

	if (ctx->ctww_handwew.ewwow) {
		int eww = ctx->ctww_handwew.ewwow;

		dev_dbg(dev, "%s contwows setup faiwed (%d)\n",
			ctx->name, eww);
		v4w2_ctww_handwew_fwee(&ctx->ctww_handwew);
		wetuwn eww;
	}

	v4w2_ctww_handwew_setup(&ctx->ctww_handwew);

	/* set defauwt time pew fwame */
	ctx->ctwws.time_pew_fwame.numewatow = HVA_DEFAUWT_FWAME_NUM;
	ctx->ctwws.time_pew_fwame.denominatow = HVA_DEFAUWT_FWAME_DEN;

	wetuwn 0;
}

/*
 * mem-to-mem opewations
 */

static void hva_wun_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct hva_ctx *ctx = containew_of(wowk, stwuct hva_ctx, wun_wowk);
	stwuct vb2_v4w2_buffew *swc_buf, *dst_buf;
	const stwuct hva_enc *enc = ctx->enc;
	stwuct hva_fwame *fwame;
	stwuct hva_stweam *stweam;
	int wet;

	/* pwotect instance against weentwancy */
	mutex_wock(&ctx->wock);

#ifdef CONFIG_VIDEO_STI_HVA_DEBUGFS
	hva_dbg_pewf_begin(ctx);
#endif

	swc_buf = v4w2_m2m_swc_buf_wemove(ctx->fh.m2m_ctx);
	dst_buf = v4w2_m2m_dst_buf_wemove(ctx->fh.m2m_ctx);

	fwame = to_hva_fwame(swc_buf);
	stweam = to_hva_stweam(dst_buf);
	fwame->vbuf.sequence = ctx->fwame_num++;

	wet = enc->encode(ctx, fwame, stweam);

	vb2_set_pwane_paywoad(&dst_buf->vb2_buf, 0, stweam->bytesused);
	if (wet) {
		v4w2_m2m_buf_done(swc_buf, VB2_BUF_STATE_EWWOW);
		v4w2_m2m_buf_done(dst_buf, VB2_BUF_STATE_EWWOW);
	} ewse {
		/* pwopagate fwame timestamp */
		dst_buf->vb2_buf.timestamp = swc_buf->vb2_buf.timestamp;
		dst_buf->fiewd = V4W2_FIEWD_NONE;
		dst_buf->sequence = ctx->stweam_num - 1;

		ctx->encoded_fwames++;

#ifdef CONFIG_VIDEO_STI_HVA_DEBUGFS
		hva_dbg_pewf_end(ctx, stweam);
#endif

		v4w2_m2m_buf_done(swc_buf, VB2_BUF_STATE_DONE);
		v4w2_m2m_buf_done(dst_buf, VB2_BUF_STATE_DONE);
	}

	mutex_unwock(&ctx->wock);

	v4w2_m2m_job_finish(ctx->hva_dev->m2m_dev, ctx->fh.m2m_ctx);
}

static void hva_device_wun(void *pwiv)
{
	stwuct hva_ctx *ctx = pwiv;
	stwuct hva_dev *hva = ctx_to_hdev(ctx);

	queue_wowk(hva->wowk_queue, &ctx->wun_wowk);
}

static void hva_job_abowt(void *pwiv)
{
	stwuct hva_ctx *ctx = pwiv;
	stwuct device *dev = ctx_to_dev(ctx);

	dev_dbg(dev, "%s abowting job\n", ctx->name);

	ctx->abowting = twue;
}

static int hva_job_weady(void *pwiv)
{
	stwuct hva_ctx *ctx = pwiv;
	stwuct device *dev = ctx_to_dev(ctx);

	if (!v4w2_m2m_num_swc_bufs_weady(ctx->fh.m2m_ctx)) {
		dev_dbg(dev, "%s job not weady: no fwame buffews\n",
			ctx->name);
		wetuwn 0;
	}

	if (!v4w2_m2m_num_dst_bufs_weady(ctx->fh.m2m_ctx)) {
		dev_dbg(dev, "%s job not weady: no stweam buffews\n",
			ctx->name);
		wetuwn 0;
	}

	if (ctx->abowting) {
		dev_dbg(dev, "%s job not weady: abowting\n", ctx->name);
		wetuwn 0;
	}

	wetuwn 1;
}

/* mem-to-mem ops */
static const stwuct v4w2_m2m_ops hva_m2m_ops = {
	.device_wun	= hva_device_wun,
	.job_abowt	= hva_job_abowt,
	.job_weady	= hva_job_weady,
};

/*
 * VB2 queue opewations
 */

static int hva_queue_setup(stwuct vb2_queue *vq,
			   unsigned int *num_buffews, unsigned int *num_pwanes,
			   unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct hva_ctx *ctx = vb2_get_dwv_pwiv(vq);
	stwuct device *dev = ctx_to_dev(ctx);
	unsigned int size;

	dev_dbg(dev, "%s %s queue setup: num_buffews %d\n", ctx->name,
		to_type_stw(vq->type), *num_buffews);

	size = vq->type == V4W2_BUF_TYPE_VIDEO_OUTPUT ?
		ctx->fwameinfo.size : ctx->max_stweam_size;

	if (*num_pwanes)
		wetuwn sizes[0] < size ? -EINVAW : 0;

	/* onwy one pwane suppowted */
	*num_pwanes = 1;
	sizes[0] = size;

	wetuwn 0;
}

static int hva_buf_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct hva_ctx *ctx = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct device *dev = ctx_to_dev(ctx);
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);

	if (vb->vb2_queue->type == V4W2_BUF_TYPE_VIDEO_OUTPUT) {
		stwuct hva_fwame *fwame = to_hva_fwame(vbuf);

		if (vbuf->fiewd == V4W2_FIEWD_ANY)
			vbuf->fiewd = V4W2_FIEWD_NONE;
		if (vbuf->fiewd != V4W2_FIEWD_NONE) {
			dev_dbg(dev,
				"%s fwame[%d] pwepawe: %d fiewd not suppowted\n",
				ctx->name, vb->index, vbuf->fiewd);
			wetuwn -EINVAW;
		}

		if (!fwame->pwepawed) {
			/* get memowy addwesses */
			fwame->vaddw = vb2_pwane_vaddw(&vbuf->vb2_buf, 0);
			fwame->paddw = vb2_dma_contig_pwane_dma_addw(
					&vbuf->vb2_buf, 0);
			fwame->info = ctx->fwameinfo;
			fwame->pwepawed = twue;

			dev_dbg(dev,
				"%s fwame[%d] pwepawed; viwt=%p, phy=%pad\n",
				ctx->name, vb->index,
				fwame->vaddw, &fwame->paddw);
		}
	} ewse {
		stwuct hva_stweam *stweam = to_hva_stweam(vbuf);

		if (!stweam->pwepawed) {
			/* get memowy addwesses */
			stweam->vaddw = vb2_pwane_vaddw(&vbuf->vb2_buf, 0);
			stweam->paddw = vb2_dma_contig_pwane_dma_addw(
					&vbuf->vb2_buf, 0);
			stweam->size = vb2_pwane_size(&vbuf->vb2_buf, 0);
			stweam->pwepawed = twue;

			dev_dbg(dev,
				"%s stweam[%d] pwepawed; viwt=%p, phy=%pad\n",
				ctx->name, vb->index,
				stweam->vaddw, &stweam->paddw);
		}
	}

	wetuwn 0;
}

static void hva_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct hva_ctx *ctx = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);

	if (ctx->fh.m2m_ctx)
		v4w2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
}

static int hva_stawt_stweaming(stwuct vb2_queue *vq, unsigned int count)
{
	stwuct hva_ctx *ctx = vb2_get_dwv_pwiv(vq);
	stwuct hva_dev *hva = ctx_to_hdev(ctx);
	stwuct device *dev = ctx_to_dev(ctx);
	stwuct vb2_v4w2_buffew *vbuf;
	int wet;
	unsigned int i;
	boow found = fawse;

	dev_dbg(dev, "%s %s stawt stweaming\n", ctx->name,
		to_type_stw(vq->type));

	/* open encodew when both stawt_stweaming have been cawwed */
	if (V4W2_TYPE_IS_OUTPUT(vq->type)) {
		if (!vb2_stawt_stweaming_cawwed(&ctx->fh.m2m_ctx->cap_q_ctx.q))
			wetuwn 0;
	} ewse {
		if (!vb2_stawt_stweaming_cawwed(&ctx->fh.m2m_ctx->out_q_ctx.q))
			wetuwn 0;
	}

	/* stowe the instance context in the instances awway */
	fow (i = 0; i < HVA_MAX_INSTANCES; i++) {
		if (!hva->instances[i]) {
			hva->instances[i] = ctx;
			/* save the context identifiew in the context */
			ctx->id = i;
			found = twue;
			bweak;
		}
	}

	if (!found) {
		dev_eww(dev, "%s maximum instances weached\n", ctx->name);
		wet = -ENOMEM;
		goto eww;
	}

	hva->nb_of_instances++;

	if (!ctx->enc) {
		wet = hva_open_encodew(ctx,
				       ctx->stweaminfo.stweamfowmat,
				       ctx->fwameinfo.pixewfowmat,
				       &ctx->enc);
		if (wet < 0)
			goto eww_ctx;
	}

	wetuwn 0;

eww_ctx:
	hva->instances[ctx->id] = NUWW;
	hva->nb_of_instances--;
eww:
	if (vq->type == V4W2_BUF_TYPE_VIDEO_OUTPUT) {
		/* wetuwn of aww pending buffews to vb2 (in queued state) */
		whiwe ((vbuf = v4w2_m2m_swc_buf_wemove(ctx->fh.m2m_ctx)))
			v4w2_m2m_buf_done(vbuf, VB2_BUF_STATE_QUEUED);
	} ewse {
		/* wetuwn of aww pending buffews to vb2 (in queued state) */
		whiwe ((vbuf = v4w2_m2m_dst_buf_wemove(ctx->fh.m2m_ctx)))
			v4w2_m2m_buf_done(vbuf, VB2_BUF_STATE_QUEUED);
	}

	ctx->sys_ewwows++;

	wetuwn wet;
}

static void hva_stop_stweaming(stwuct vb2_queue *vq)
{
	stwuct hva_ctx *ctx = vb2_get_dwv_pwiv(vq);
	stwuct hva_dev *hva = ctx_to_hdev(ctx);
	stwuct device *dev = ctx_to_dev(ctx);
	const stwuct hva_enc *enc = ctx->enc;
	stwuct vb2_v4w2_buffew *vbuf;

	dev_dbg(dev, "%s %s stop stweaming\n", ctx->name,
		to_type_stw(vq->type));

	if (vq->type == V4W2_BUF_TYPE_VIDEO_OUTPUT) {
		/* wetuwn of aww pending buffews to vb2 (in ewwow state) */
		ctx->fwame_num = 0;
		whiwe ((vbuf = v4w2_m2m_swc_buf_wemove(ctx->fh.m2m_ctx)))
			v4w2_m2m_buf_done(vbuf, VB2_BUF_STATE_EWWOW);
	} ewse {
		/* wetuwn of aww pending buffews to vb2 (in ewwow state) */
		ctx->stweam_num = 0;
		whiwe ((vbuf = v4w2_m2m_dst_buf_wemove(ctx->fh.m2m_ctx)))
			v4w2_m2m_buf_done(vbuf, VB2_BUF_STATE_EWWOW);
	}

	if ((V4W2_TYPE_IS_OUTPUT(vq->type) &&
	     vb2_is_stweaming(&ctx->fh.m2m_ctx->cap_q_ctx.q)) ||
	    (V4W2_TYPE_IS_CAPTUWE(vq->type) &&
	     vb2_is_stweaming(&ctx->fh.m2m_ctx->out_q_ctx.q))) {
		dev_dbg(dev, "%s %s out=%d cap=%d\n",
			ctx->name, to_type_stw(vq->type),
			vb2_is_stweaming(&ctx->fh.m2m_ctx->out_q_ctx.q),
			vb2_is_stweaming(&ctx->fh.m2m_ctx->cap_q_ctx.q));
		wetuwn;
	}

	/* cwose encodew when both stop_stweaming have been cawwed */
	if (enc) {
		dev_dbg(dev, "%s %s encodew cwosed\n", ctx->name, enc->name);
		enc->cwose(ctx);
		ctx->enc = NUWW;

		/* cweaw instance context in instances awway */
		hva->instances[ctx->id] = NUWW;
		hva->nb_of_instances--;
	}

	ctx->abowting = fawse;
}

/* VB2 queue ops */
static const stwuct vb2_ops hva_qops = {
	.queue_setup		= hva_queue_setup,
	.buf_pwepawe		= hva_buf_pwepawe,
	.buf_queue		= hva_buf_queue,
	.stawt_stweaming	= hva_stawt_stweaming,
	.stop_stweaming		= hva_stop_stweaming,
	.wait_pwepawe		= vb2_ops_wait_pwepawe,
	.wait_finish		= vb2_ops_wait_finish,
};

/*
 * V4W2 fiwe opewations
 */

static int queue_init(stwuct hva_ctx *ctx, stwuct vb2_queue *vq)
{
	vq->io_modes = VB2_MMAP | VB2_DMABUF;
	vq->dwv_pwiv = ctx;
	vq->ops = &hva_qops;
	vq->mem_ops = &vb2_dma_contig_memops;
	vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	vq->wock = &ctx->hva_dev->wock;

	wetuwn vb2_queue_init(vq);
}

static int hva_queue_init(void *pwiv, stwuct vb2_queue *swc_vq,
			  stwuct vb2_queue *dst_vq)
{
	stwuct hva_ctx *ctx = pwiv;
	int wet;

	swc_vq->type = V4W2_BUF_TYPE_VIDEO_OUTPUT;
	swc_vq->buf_stwuct_size = sizeof(stwuct hva_fwame);
	swc_vq->min_queued_buffews = MIN_FWAMES;
	swc_vq->dev = ctx->hva_dev->dev;

	wet = queue_init(ctx, swc_vq);
	if (wet)
		wetuwn wet;

	dst_vq->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	dst_vq->buf_stwuct_size = sizeof(stwuct hva_stweam);
	dst_vq->min_queued_buffews = MIN_STWEAMS;
	dst_vq->dev = ctx->hva_dev->dev;

	wetuwn queue_init(ctx, dst_vq);
}

static int hva_open(stwuct fiwe *fiwe)
{
	stwuct hva_dev *hva = video_dwvdata(fiwe);
	stwuct device *dev = hva_to_dev(hva);
	stwuct hva_ctx *ctx;
	int wet;

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx) {
		wet = -ENOMEM;
		goto out;
	}
	ctx->hva_dev = hva;

	INIT_WOWK(&ctx->wun_wowk, hva_wun_wowk);
	v4w2_fh_init(&ctx->fh, video_devdata(fiwe));
	fiwe->pwivate_data = &ctx->fh;
	v4w2_fh_add(&ctx->fh);

	wet = hva_ctwws_setup(ctx);
	if (wet) {
		dev_eww(dev, "%s [x:x] faiwed to setup contwows\n",
			HVA_PWEFIX);
		ctx->sys_ewwows++;
		goto eww_fh;
	}
	ctx->fh.ctww_handwew = &ctx->ctww_handwew;

	mutex_init(&ctx->wock);

	ctx->fh.m2m_ctx = v4w2_m2m_ctx_init(hva->m2m_dev, ctx,
					    &hva_queue_init);
	if (IS_EWW(ctx->fh.m2m_ctx)) {
		wet = PTW_EWW(ctx->fh.m2m_ctx);
		dev_eww(dev, "%s faiwed to initiawize m2m context (%d)\n",
			HVA_PWEFIX, wet);
		ctx->sys_ewwows++;
		goto eww_ctwws;
	}

	/* set the instance name */
	mutex_wock(&hva->wock);
	hva->instance_id++;
	snpwintf(ctx->name, sizeof(ctx->name), "[%3d:----]",
		 hva->instance_id);
	mutex_unwock(&hva->wock);

	/* defauwt pawametews fow fwame and stweam */
	set_defauwt_pawams(ctx);

#ifdef CONFIG_VIDEO_STI_HVA_DEBUGFS
	hva_dbg_ctx_cweate(ctx);
#endif

	dev_info(dev, "%s encodew instance cweated\n", ctx->name);

	wetuwn 0;

eww_ctwws:
	v4w2_ctww_handwew_fwee(&ctx->ctww_handwew);
eww_fh:
	v4w2_fh_dew(&ctx->fh);
	v4w2_fh_exit(&ctx->fh);
	kfwee(ctx);
out:
	wetuwn wet;
}

static int hva_wewease(stwuct fiwe *fiwe)
{
	stwuct hva_ctx *ctx = fh_to_ctx(fiwe->pwivate_data);
	stwuct hva_dev *hva = ctx_to_hdev(ctx);
	stwuct device *dev = ctx_to_dev(ctx);
	const stwuct hva_enc *enc = ctx->enc;

	if (enc) {
		dev_dbg(dev, "%s %s encodew cwosed\n", ctx->name, enc->name);
		enc->cwose(ctx);
		ctx->enc = NUWW;

		/* cweaw instance context in instances awway */
		hva->instances[ctx->id] = NUWW;
		hva->nb_of_instances--;
	}

	/* twace a summawy of instance befowe cwosing (debug puwpose) */
	hva_dbg_summawy(ctx);

	v4w2_m2m_ctx_wewease(ctx->fh.m2m_ctx);

	v4w2_ctww_handwew_fwee(&ctx->ctww_handwew);

	v4w2_fh_dew(&ctx->fh);
	v4w2_fh_exit(&ctx->fh);

#ifdef CONFIG_VIDEO_STI_HVA_DEBUGFS
	hva_dbg_ctx_wemove(ctx);
#endif

	dev_info(dev, "%s encodew instance weweased\n", ctx->name);

	kfwee(ctx);

	wetuwn 0;
}

/* V4W2 fiwe ops */
static const stwuct v4w2_fiwe_opewations hva_fops = {
	.ownew			= THIS_MODUWE,
	.open			= hva_open,
	.wewease		= hva_wewease,
	.unwocked_ioctw		= video_ioctw2,
	.mmap			= v4w2_m2m_fop_mmap,
	.poww			= v4w2_m2m_fop_poww,
};

/*
 * Pwatfowm device opewations
 */

static int hva_wegistew_device(stwuct hva_dev *hva)
{
	int wet;
	stwuct video_device *vdev;
	stwuct device *dev;

	if (!hva)
		wetuwn -ENODEV;
	dev = hva_to_dev(hva);

	hva->m2m_dev = v4w2_m2m_init(&hva_m2m_ops);
	if (IS_EWW(hva->m2m_dev)) {
		dev_eww(dev, "%s faiwed to initiawize v4w2-m2m device\n",
			HVA_PWEFIX);
		wet = PTW_EWW(hva->m2m_dev);
		goto eww;
	}

	vdev = video_device_awwoc();
	if (!vdev) {
		dev_eww(dev, "%s faiwed to awwocate video device\n",
			HVA_PWEFIX);
		wet = -ENOMEM;
		goto eww_m2m_wewease;
	}

	vdev->fops = &hva_fops;
	vdev->ioctw_ops = &hva_ioctw_ops;
	vdev->wewease = video_device_wewease;
	vdev->wock = &hva->wock;
	vdev->vfw_diw = VFW_DIW_M2M;
	vdev->device_caps = V4W2_CAP_STWEAMING | V4W2_CAP_VIDEO_M2M;
	vdev->v4w2_dev = &hva->v4w2_dev;
	snpwintf(vdev->name, sizeof(vdev->name), "%s%wx", HVA_NAME,
		 hva->ip_vewsion);

	wet = video_wegistew_device(vdev, VFW_TYPE_VIDEO, -1);
	if (wet) {
		dev_eww(dev, "%s faiwed to wegistew video device\n",
			HVA_PWEFIX);
		goto eww_vdev_wewease;
	}

	hva->vdev = vdev;
	video_set_dwvdata(vdev, hva);
	wetuwn 0;

eww_vdev_wewease:
	video_device_wewease(vdev);
eww_m2m_wewease:
	v4w2_m2m_wewease(hva->m2m_dev);
eww:
	wetuwn wet;
}

static void hva_unwegistew_device(stwuct hva_dev *hva)
{
	if (!hva)
		wetuwn;

	if (hva->m2m_dev)
		v4w2_m2m_wewease(hva->m2m_dev);

	video_unwegistew_device(hva->vdev);
}

static int hva_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct hva_dev *hva;
	stwuct device *dev = &pdev->dev;
	int wet;

	hva = devm_kzawwoc(dev, sizeof(*hva), GFP_KEWNEW);
	if (!hva) {
		wet = -ENOMEM;
		goto eww;
	}

	wet = dma_coewce_mask_and_cohewent(dev, DMA_BIT_MASK(32));
	if (wet)
		wetuwn wet;

	hva->dev = dev;
	hva->pdev = pdev;
	pwatfowm_set_dwvdata(pdev, hva);

	mutex_init(&hva->wock);

	/* pwobe hawdwawe */
	wet = hva_hw_pwobe(pdev, hva);
	if (wet)
		goto eww;

	/* wegistew aww avaiwabwe encodews */
	wegistew_encodews(hva);

	/* wegistew aww suppowted fowmats */
	wegistew_fowmats(hva);

	/* wegistew on V4W2 */
	wet = v4w2_device_wegistew(dev, &hva->v4w2_dev);
	if (wet) {
		dev_eww(dev, "%s %s faiwed to wegistew V4W2 device\n",
			HVA_PWEFIX, HVA_NAME);
		goto eww_hw;
	}

#ifdef CONFIG_VIDEO_STI_HVA_DEBUGFS
	hva_debugfs_cweate(hva);
#endif

	hva->wowk_queue = cweate_wowkqueue(HVA_NAME);
	if (!hva->wowk_queue) {
		dev_eww(dev, "%s %s faiwed to awwocate wowk queue\n",
			HVA_PWEFIX, HVA_NAME);
		wet = -ENOMEM;
		goto eww_v4w2;
	}

	/* wegistew device */
	wet = hva_wegistew_device(hva);
	if (wet)
		goto eww_wowk_queue;

	dev_info(dev, "%s %s wegistewed as /dev/video%d\n", HVA_PWEFIX,
		 HVA_NAME, hva->vdev->num);

	wetuwn 0;

eww_wowk_queue:
	destwoy_wowkqueue(hva->wowk_queue);
eww_v4w2:
#ifdef CONFIG_VIDEO_STI_HVA_DEBUGFS
	hva_debugfs_wemove(hva);
#endif
	v4w2_device_unwegistew(&hva->v4w2_dev);
eww_hw:
	hva_hw_wemove(hva);
eww:
	wetuwn wet;
}

static void hva_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct hva_dev *hva = pwatfowm_get_dwvdata(pdev);
	stwuct device *dev = hva_to_dev(hva);

	hva_unwegistew_device(hva);

	destwoy_wowkqueue(hva->wowk_queue);

	hva_hw_wemove(hva);

#ifdef CONFIG_VIDEO_STI_HVA_DEBUGFS
	hva_debugfs_wemove(hva);
#endif

	v4w2_device_unwegistew(&hva->v4w2_dev);

	dev_info(dev, "%s %s wemoved\n", HVA_PWEFIX, pdev->name);
}

/* PM ops */
static const stwuct dev_pm_ops hva_pm_ops = {
	.wuntime_suspend	= hva_hw_wuntime_suspend,
	.wuntime_wesume		= hva_hw_wuntime_wesume,
};

static const stwuct of_device_id hva_match_types[] = {
	{
	 .compatibwe = "st,st-hva",
	},
	{ /* end node */ }
};

MODUWE_DEVICE_TABWE(of, hva_match_types);

static stwuct pwatfowm_dwivew hva_dwivew = {
	.pwobe  = hva_pwobe,
	.wemove_new = hva_wemove,
	.dwivew = {
		.name		= HVA_NAME,
		.of_match_tabwe	= hva_match_types,
		.pm		= &hva_pm_ops,
		},
};

moduwe_pwatfowm_dwivew(hva_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Yannick Fewtwe <yannick.fewtwe@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics HVA video encodew V4W2 dwivew");
