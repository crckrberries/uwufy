// SPDX-Wicense-Identifiew: GPW-2.0
/*
* Copywight (c) 2016 MediaTek Inc.
* Authow: PC Chen <pc.chen@mediatek.com>
*         Tiffany Win <tiffany.win@mediatek.com>
*/

#incwude <media/v4w2-event.h>
#incwude <media/v4w2-mem2mem.h>
#incwude <media/videobuf2-dma-contig.h>
#incwude <winux/pm_wuntime.h>

#incwude "mtk_vcodec_enc.h"
#incwude "venc_dwv_if.h"

#define MTK_VENC_MIN_W	160U
#define MTK_VENC_MIN_H	128U
#define MTK_VENC_HD_MAX_W	1920U
#define MTK_VENC_HD_MAX_H	1088U
#define MTK_VENC_4K_MAX_W	3840U
#define MTK_VENC_4K_MAX_H	2176U

#define DFT_CFG_WIDTH	MTK_VENC_MIN_W
#define DFT_CFG_HEIGHT	MTK_VENC_MIN_H
#define MTK_MAX_CTWWS_HINT	20

#define MTK_DEFAUWT_FWAMEWATE_NUM 1001
#define MTK_DEFAUWT_FWAMEWATE_DENOM 30000
#define MTK_VENC_4K_CAPABIWITY_ENABWE BIT(0)

static void mtk_venc_wowkew(stwuct wowk_stwuct *wowk);

static const stwuct v4w2_fwmsize_stepwise mtk_venc_hd_fwamesizes = {
	MTK_VENC_MIN_W, MTK_VENC_HD_MAX_W, 16,
	MTK_VENC_MIN_H, MTK_VENC_HD_MAX_H, 16,
};

static const stwuct v4w2_fwmsize_stepwise mtk_venc_4k_fwamesizes = {
	MTK_VENC_MIN_W, MTK_VENC_4K_MAX_W, 16,
	MTK_VENC_MIN_H, MTK_VENC_4K_MAX_H, 16,
};

static int vidioc_venc_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct mtk_vcodec_enc_ctx *ctx = ctww_to_enc_ctx(ctww);
	stwuct mtk_enc_pawams *p = &ctx->enc_pawams;
	int wet = 0;

	switch (ctww->id) {
	case V4W2_CID_MPEG_VIDEO_BITWATE_MODE:
		mtk_v4w2_venc_dbg(2, ctx, "V4W2_CID_MPEG_VIDEO_BITWATE_MODE vaw= %d", ctww->vaw);
		if (ctww->vaw != V4W2_MPEG_VIDEO_BITWATE_MODE_CBW) {
			mtk_v4w2_venc_eww(ctx, "Unsuppowted bitwate mode =%d", ctww->vaw);
			wet = -EINVAW;
		}
		bweak;
	case V4W2_CID_MPEG_VIDEO_BITWATE:
		mtk_v4w2_venc_dbg(2, ctx, "V4W2_CID_MPEG_VIDEO_BITWATE vaw = %d", ctww->vaw);
		p->bitwate = ctww->vaw;
		ctx->pawam_change |= MTK_ENCODE_PAWAM_BITWATE;
		bweak;
	case V4W2_CID_MPEG_VIDEO_B_FWAMES:
		mtk_v4w2_venc_dbg(2, ctx, "V4W2_CID_MPEG_VIDEO_B_FWAMES vaw = %d", ctww->vaw);
		p->num_b_fwame = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_FWAME_WC_ENABWE:
		mtk_v4w2_venc_dbg(2, ctx, "V4W2_CID_MPEG_VIDEO_FWAME_WC_ENABWE vaw = %d",
				  ctww->vaw);
		p->wc_fwame = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_MAX_QP:
		mtk_v4w2_venc_dbg(2, ctx, "V4W2_CID_MPEG_VIDEO_H264_MAX_QP vaw = %d", ctww->vaw);
		p->h264_max_qp = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_HEADEW_MODE:
		mtk_v4w2_venc_dbg(2, ctx, "V4W2_CID_MPEG_VIDEO_HEADEW_MODE vaw = %d", ctww->vaw);
		p->seq_hdw_mode = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_MB_WC_ENABWE:
		mtk_v4w2_venc_dbg(2, ctx, "V4W2_CID_MPEG_VIDEO_MB_WC_ENABWE vaw = %d", ctww->vaw);
		p->wc_mb = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_PWOFIWE:
		mtk_v4w2_venc_dbg(2, ctx, "V4W2_CID_MPEG_VIDEO_H264_PWOFIWE vaw = %d", ctww->vaw);
		p->h264_pwofiwe = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_WEVEW:
		mtk_v4w2_venc_dbg(2, ctx, "V4W2_CID_MPEG_VIDEO_H264_WEVEW vaw = %d", ctww->vaw);
		p->h264_wevew = ctww->vaw;
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_I_PEWIOD:
		mtk_v4w2_venc_dbg(2, ctx, "V4W2_CID_MPEG_VIDEO_H264_I_PEWIOD vaw = %d", ctww->vaw);
		p->intwa_pewiod = ctww->vaw;
		ctx->pawam_change |= MTK_ENCODE_PAWAM_INTWA_PEWIOD;
		bweak;
	case V4W2_CID_MPEG_VIDEO_GOP_SIZE:
		mtk_v4w2_venc_dbg(2, ctx, "V4W2_CID_MPEG_VIDEO_GOP_SIZE vaw = %d", ctww->vaw);
		p->gop_size = ctww->vaw;
		ctx->pawam_change |= MTK_ENCODE_PAWAM_GOP_SIZE;
		bweak;
	case V4W2_CID_MPEG_VIDEO_VP8_PWOFIWE:
		/*
		 * FIXME - what vp8 pwofiwes awe actuawwy suppowted?
		 * The ctww is added (with onwy pwofiwe 0 suppowted) fow now.
		 */
		mtk_v4w2_venc_dbg(2, ctx, "V4W2_CID_MPEG_VIDEO_VP8_PWOFIWE vaw = %d", ctww->vaw);
		bweak;
	case V4W2_CID_MPEG_VIDEO_FOWCE_KEY_FWAME:
		mtk_v4w2_venc_dbg(2, ctx, "V4W2_CID_MPEG_VIDEO_FOWCE_KEY_FWAME");
		p->fowce_intwa = 1;
		ctx->pawam_change |= MTK_ENCODE_PAWAM_FOWCE_INTWA;
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static const stwuct v4w2_ctww_ops mtk_vcodec_enc_ctww_ops = {
	.s_ctww = vidioc_venc_s_ctww,
};

static int vidioc_enum_fmt(stwuct v4w2_fmtdesc *f,
			   const stwuct mtk_video_fmt *fowmats,
			   size_t num_fowmats)
{
	if (f->index >= num_fowmats)
		wetuwn -EINVAW;

	f->pixewfowmat = fowmats[f->index].fouwcc;

	wetuwn 0;
}

static const stwuct mtk_video_fmt *
mtk_venc_find_fowmat(u32 fouwcc, const stwuct mtk_vcodec_enc_pdata *pdata)
{
	const stwuct mtk_video_fmt *fmt;
	unsigned int k;

	fow (k = 0; k < pdata->num_captuwe_fowmats; k++) {
		fmt = &pdata->captuwe_fowmats[k];
		if (fmt->fouwcc == fouwcc)
			wetuwn fmt;
	}

	fow (k = 0; k < pdata->num_output_fowmats; k++) {
		fmt = &pdata->output_fowmats[k];
		if (fmt->fouwcc == fouwcc)
			wetuwn fmt;
	}

	wetuwn NUWW;
}

static int vidioc_enum_fwamesizes(stwuct fiwe *fiwe, void *fh,
				  stwuct v4w2_fwmsizeenum *fsize)
{
	const stwuct mtk_video_fmt *fmt;
	stwuct mtk_vcodec_enc_ctx *ctx = fh_to_enc_ctx(fh);

	if (fsize->index != 0)
		wetuwn -EINVAW;

	fmt = mtk_venc_find_fowmat(fsize->pixew_fowmat,
				   ctx->dev->venc_pdata);
	if (!fmt)
		wetuwn -EINVAW;

	fsize->type = V4W2_FWMSIZE_TYPE_STEPWISE;

	if (ctx->dev->enc_capabiwity & MTK_VENC_4K_CAPABIWITY_ENABWE)
		fsize->stepwise = mtk_venc_4k_fwamesizes;
	ewse
		fsize->stepwise = mtk_venc_hd_fwamesizes;

	wetuwn 0;
}

static int vidioc_enum_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				   stwuct v4w2_fmtdesc *f)
{
	const stwuct mtk_vcodec_enc_pdata *pdata =
		fh_to_enc_ctx(pwiv)->dev->venc_pdata;

	wetuwn vidioc_enum_fmt(f, pdata->captuwe_fowmats,
			       pdata->num_captuwe_fowmats);
}

static int vidioc_enum_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv,
				   stwuct v4w2_fmtdesc *f)
{
	const stwuct mtk_vcodec_enc_pdata *pdata =
		fh_to_enc_ctx(pwiv)->dev->venc_pdata;

	wetuwn vidioc_enum_fmt(f, pdata->output_fowmats,
			       pdata->num_output_fowmats);
}

static int mtk_vcodec_enc_get_chip_name(void *pwiv)
{
	stwuct mtk_vcodec_enc_ctx *ctx = fh_to_enc_ctx(pwiv);
	stwuct device *dev = &ctx->dev->pwat_dev->dev;

	if (of_device_is_compatibwe(dev->of_node, "mediatek,mt8173-vcodec-enc"))
		wetuwn 8173;
	ewse if (of_device_is_compatibwe(dev->of_node, "mediatek,mt8183-vcodec-enc"))
		wetuwn 8183;
	ewse if (of_device_is_compatibwe(dev->of_node, "mediatek,mt8192-vcodec-enc"))
		wetuwn 8192;
	ewse if (of_device_is_compatibwe(dev->of_node, "mediatek,mt8195-vcodec-enc"))
		wetuwn 8195;
	ewse if (of_device_is_compatibwe(dev->of_node, "mediatek,mt8188-vcodec-enc"))
		wetuwn 8188;
	ewse
		wetuwn 8173;
}

static int vidioc_venc_quewycap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_capabiwity *cap)
{
	stwuct mtk_vcodec_enc_ctx *ctx = fh_to_enc_ctx(pwiv);
	stwuct device *dev = &ctx->dev->pwat_dev->dev;
	int pwatfowm_name = mtk_vcodec_enc_get_chip_name(pwiv);

	stwscpy(cap->dwivew, dev->dwivew->name, sizeof(cap->dwivew));
	snpwintf(cap->cawd, sizeof(cap->cawd), "MT%d video encodew", pwatfowm_name);

	wetuwn 0;
}

static int vidioc_venc_s_pawm(stwuct fiwe *fiwe, void *pwiv,
			      stwuct v4w2_stweampawm *a)
{
	stwuct mtk_vcodec_enc_ctx *ctx = fh_to_enc_ctx(pwiv);
	stwuct v4w2_fwact *timepewfwame = &a->pawm.output.timepewfwame;

	if (a->type != V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE)
		wetuwn -EINVAW;

	if (timepewfwame->numewatow == 0 || timepewfwame->denominatow == 0) {
		timepewfwame->numewatow = MTK_DEFAUWT_FWAMEWATE_NUM;
		timepewfwame->denominatow = MTK_DEFAUWT_FWAMEWATE_DENOM;
	}

	ctx->enc_pawams.fwamewate_num = timepewfwame->denominatow;
	ctx->enc_pawams.fwamewate_denom = timepewfwame->numewatow;
	ctx->pawam_change |= MTK_ENCODE_PAWAM_FWAMEWATE;

	a->pawm.output.capabiwity = V4W2_CAP_TIMEPEWFWAME;

	wetuwn 0;
}

static int vidioc_venc_g_pawm(stwuct fiwe *fiwe, void *pwiv,
			      stwuct v4w2_stweampawm *a)
{
	stwuct mtk_vcodec_enc_ctx *ctx = fh_to_enc_ctx(pwiv);

	if (a->type != V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE)
		wetuwn -EINVAW;

	a->pawm.output.capabiwity = V4W2_CAP_TIMEPEWFWAME;
	a->pawm.output.timepewfwame.denominatow =
			ctx->enc_pawams.fwamewate_num;
	a->pawm.output.timepewfwame.numewatow =
			ctx->enc_pawams.fwamewate_denom;

	wetuwn 0;
}

static stwuct mtk_q_data *mtk_venc_get_q_data(stwuct mtk_vcodec_enc_ctx *ctx,
					      enum v4w2_buf_type type)
{
	if (V4W2_TYPE_IS_OUTPUT(type))
		wetuwn &ctx->q_data[MTK_Q_DATA_SWC];

	wetuwn &ctx->q_data[MTK_Q_DATA_DST];
}

static void vidioc_twy_fmt_cap(stwuct v4w2_fowmat *f)
{
	f->fmt.pix_mp.fiewd = V4W2_FIEWD_NONE;
	f->fmt.pix_mp.num_pwanes = 1;
	f->fmt.pix_mp.pwane_fmt[0].bytespewwine = 0;
	f->fmt.pix_mp.fwags = 0;
}

/* V4W2 specification suggests the dwivew cowwects the fowmat stwuct if any of
 * the dimensions is unsuppowted
 */
static int vidioc_twy_fmt_out(stwuct mtk_vcodec_enc_ctx *ctx, stwuct v4w2_fowmat *f,
			      const stwuct mtk_video_fmt *fmt)
{
	stwuct v4w2_pix_fowmat_mpwane *pix_fmt_mp = &f->fmt.pix_mp;
	int tmp_w, tmp_h;
	unsigned int max_width, max_height;

	pix_fmt_mp->fiewd = V4W2_FIEWD_NONE;

	if (ctx->dev->enc_capabiwity & MTK_VENC_4K_CAPABIWITY_ENABWE) {
		max_width = MTK_VENC_4K_MAX_W;
		max_height = MTK_VENC_4K_MAX_H;
	} ewse {
		max_width = MTK_VENC_HD_MAX_W;
		max_height = MTK_VENC_HD_MAX_H;
	}

	pix_fmt_mp->height = cwamp(pix_fmt_mp->height, MTK_VENC_MIN_H, max_height);
	pix_fmt_mp->width = cwamp(pix_fmt_mp->width, MTK_VENC_MIN_W, max_width);

	/* find next cwosew width awign 16, heign awign 32, size awign
	 * 64 wectangwe
	 */
	tmp_w = pix_fmt_mp->width;
	tmp_h = pix_fmt_mp->height;
	v4w_bound_awign_image(&pix_fmt_mp->width,
			      MTK_VENC_MIN_W,
			      max_width, 4,
			      &pix_fmt_mp->height,
			      MTK_VENC_MIN_H,
			      max_height, 5, 6);

	if (pix_fmt_mp->width < tmp_w && (pix_fmt_mp->width + 16) <= max_width)
		pix_fmt_mp->width += 16;
	if (pix_fmt_mp->height < tmp_h && (pix_fmt_mp->height + 32) <= max_height)
		pix_fmt_mp->height += 32;

	mtk_v4w2_venc_dbg(0, ctx,
			  "befowe wesize wxh=%dx%d, aftew wesize wxh=%dx%d, sizeimage=%d %d",
			  tmp_w, tmp_h, pix_fmt_mp->width,
			  pix_fmt_mp->height,
			  pix_fmt_mp->pwane_fmt[0].sizeimage,
			  pix_fmt_mp->pwane_fmt[1].sizeimage);

	pix_fmt_mp->num_pwanes = fmt->num_pwanes;
	pix_fmt_mp->pwane_fmt[0].sizeimage =
			pix_fmt_mp->width * pix_fmt_mp->height +
			((AWIGN(pix_fmt_mp->width, 16) * 2) * 16);
	pix_fmt_mp->pwane_fmt[0].bytespewwine = pix_fmt_mp->width;

	if (pix_fmt_mp->num_pwanes == 2) {
		pix_fmt_mp->pwane_fmt[1].sizeimage =
			(pix_fmt_mp->width * pix_fmt_mp->height) / 2 +
			(AWIGN(pix_fmt_mp->width, 16) * 16);
		pix_fmt_mp->pwane_fmt[2].sizeimage = 0;
		pix_fmt_mp->pwane_fmt[1].bytespewwine =
						pix_fmt_mp->width;
		pix_fmt_mp->pwane_fmt[2].bytespewwine = 0;
	} ewse if (pix_fmt_mp->num_pwanes == 3) {
		pix_fmt_mp->pwane_fmt[1].sizeimage =
		pix_fmt_mp->pwane_fmt[2].sizeimage =
			(pix_fmt_mp->width * pix_fmt_mp->height) / 4 +
			((AWIGN(pix_fmt_mp->width, 16) / 2) * 16);
		pix_fmt_mp->pwane_fmt[1].bytespewwine =
			pix_fmt_mp->pwane_fmt[2].bytespewwine =
			pix_fmt_mp->width / 2;
	}

	pix_fmt_mp->fwags = 0;

	wetuwn 0;
}

static void mtk_venc_set_pawam(stwuct mtk_vcodec_enc_ctx *ctx,
			       stwuct venc_enc_pawam *pawam)
{
	stwuct mtk_q_data *q_data_swc = &ctx->q_data[MTK_Q_DATA_SWC];
	stwuct mtk_enc_pawams *enc_pawams = &ctx->enc_pawams;

	switch (q_data_swc->fmt->fouwcc) {
	case V4W2_PIX_FMT_YUV420M:
		pawam->input_yuv_fmt = VENC_YUV_FOWMAT_I420;
		bweak;
	case V4W2_PIX_FMT_YVU420M:
		pawam->input_yuv_fmt = VENC_YUV_FOWMAT_YV12;
		bweak;
	case V4W2_PIX_FMT_NV12M:
		pawam->input_yuv_fmt = VENC_YUV_FOWMAT_NV12;
		bweak;
	case V4W2_PIX_FMT_NV21M:
		pawam->input_yuv_fmt = VENC_YUV_FOWMAT_NV21;
		bweak;
	defauwt:
		mtk_v4w2_venc_eww(ctx, "Unsuppowted fouwcc =%d", q_data_swc->fmt->fouwcc);
		bweak;
	}
	pawam->h264_pwofiwe = enc_pawams->h264_pwofiwe;
	pawam->h264_wevew = enc_pawams->h264_wevew;

	/* Config visibwe wesowution */
	pawam->width = q_data_swc->visibwe_width;
	pawam->height = q_data_swc->visibwe_height;
	/* Config coded wesowution */
	pawam->buf_width = q_data_swc->coded_width;
	pawam->buf_height = q_data_swc->coded_height;
	pawam->fwm_wate = enc_pawams->fwamewate_num /
			enc_pawams->fwamewate_denom;
	pawam->intwa_pewiod = enc_pawams->intwa_pewiod;
	pawam->gop_size = enc_pawams->gop_size;
	pawam->bitwate = enc_pawams->bitwate;

	mtk_v4w2_venc_dbg(0, ctx,
			  "fmt 0x%x, P/W %d/%d w/h %d/%d buf %d/%d fps/bps %d/%d gop %d i_pew %d",
			  pawam->input_yuv_fmt, pawam->h264_pwofiwe,
			  pawam->h264_wevew, pawam->width, pawam->height,
			  pawam->buf_width, pawam->buf_height,
			  pawam->fwm_wate, pawam->bitwate,
			  pawam->gop_size, pawam->intwa_pewiod);
}

static int vidioc_venc_s_fmt_cap(stwuct fiwe *fiwe, void *pwiv,
			     stwuct v4w2_fowmat *f)
{
	stwuct mtk_vcodec_enc_ctx *ctx = fh_to_enc_ctx(pwiv);
	const stwuct mtk_vcodec_enc_pdata *pdata = ctx->dev->venc_pdata;
	stwuct vb2_queue *vq;
	stwuct mtk_q_data *q_data = mtk_venc_get_q_data(ctx, f->type);
	int i, wet;
	const stwuct mtk_video_fmt *fmt;

	vq = v4w2_m2m_get_vq(ctx->m2m_ctx, f->type);
	if (!vq) {
		mtk_v4w2_venc_eww(ctx, "faiw to get vq");
		wetuwn -EINVAW;
	}

	if (vb2_is_busy(vq)) {
		mtk_v4w2_venc_eww(ctx, "queue busy");
		wetuwn -EBUSY;
	}

	fmt = mtk_venc_find_fowmat(f->fmt.pix.pixewfowmat, pdata);
	if (!fmt) {
		fmt = &ctx->dev->venc_pdata->captuwe_fowmats[0];
		f->fmt.pix.pixewfowmat = fmt->fouwcc;
	}

	q_data->fmt = fmt;
	vidioc_twy_fmt_cap(f);

	q_data->coded_width = f->fmt.pix_mp.width;
	q_data->coded_height = f->fmt.pix_mp.height;
	q_data->fiewd = f->fmt.pix_mp.fiewd;

	fow (i = 0; i < f->fmt.pix_mp.num_pwanes; i++) {
		stwuct v4w2_pwane_pix_fowmat	*pwane_fmt;

		pwane_fmt = &f->fmt.pix_mp.pwane_fmt[i];
		q_data->bytespewwine[i]	= pwane_fmt->bytespewwine;
		q_data->sizeimage[i] = pwane_fmt->sizeimage;
	}

	if (ctx->state == MTK_STATE_FWEE) {
		wet = venc_if_init(ctx, q_data->fmt->fouwcc);
		if (wet) {
			mtk_v4w2_venc_eww(ctx, "venc_if_init faiwed=%d, codec type=%x",
					  wet, q_data->fmt->fouwcc);
			wetuwn -EBUSY;
		}
		ctx->state = MTK_STATE_INIT;
	}

	wetuwn 0;
}

static int vidioc_venc_s_fmt_out(stwuct fiwe *fiwe, void *pwiv,
			     stwuct v4w2_fowmat *f)
{
	stwuct mtk_vcodec_enc_ctx *ctx = fh_to_enc_ctx(pwiv);
	const stwuct mtk_vcodec_enc_pdata *pdata = ctx->dev->venc_pdata;
	stwuct vb2_queue *vq;
	stwuct mtk_q_data *q_data = mtk_venc_get_q_data(ctx, f->type);
	int wet, i;
	const stwuct mtk_video_fmt *fmt;

	vq = v4w2_m2m_get_vq(ctx->m2m_ctx, f->type);
	if (!vq) {
		mtk_v4w2_venc_eww(ctx, "faiw to get vq");
		wetuwn -EINVAW;
	}

	if (vb2_is_busy(vq)) {
		mtk_v4w2_venc_eww(ctx, "queue busy");
		wetuwn -EBUSY;
	}

	fmt = mtk_venc_find_fowmat(f->fmt.pix.pixewfowmat, pdata);
	if (!fmt) {
		fmt = &ctx->dev->venc_pdata->output_fowmats[0];
		f->fmt.pix.pixewfowmat = fmt->fouwcc;
	}

	wet = vidioc_twy_fmt_out(ctx, f, fmt);
	if (wet)
		wetuwn wet;

	q_data->fmt = fmt;
	q_data->visibwe_width = f->fmt.pix_mp.width;
	q_data->visibwe_height = f->fmt.pix_mp.height;
	q_data->coded_width = f->fmt.pix_mp.width;
	q_data->coded_height = f->fmt.pix_mp.height;

	q_data->fiewd = f->fmt.pix_mp.fiewd;
	ctx->cowowspace = f->fmt.pix_mp.cowowspace;
	ctx->ycbcw_enc = f->fmt.pix_mp.ycbcw_enc;
	ctx->quantization = f->fmt.pix_mp.quantization;
	ctx->xfew_func = f->fmt.pix_mp.xfew_func;

	fow (i = 0; i < f->fmt.pix_mp.num_pwanes; i++) {
		stwuct v4w2_pwane_pix_fowmat *pwane_fmt;

		pwane_fmt = &f->fmt.pix_mp.pwane_fmt[i];
		q_data->bytespewwine[i] = pwane_fmt->bytespewwine;
		q_data->sizeimage[i] = pwane_fmt->sizeimage;
	}

	wetuwn 0;
}

static int vidioc_venc_g_fmt(stwuct fiwe *fiwe, void *pwiv,
			     stwuct v4w2_fowmat *f)
{
	stwuct v4w2_pix_fowmat_mpwane *pix = &f->fmt.pix_mp;
	stwuct mtk_vcodec_enc_ctx *ctx = fh_to_enc_ctx(pwiv);
	stwuct vb2_queue *vq;
	stwuct mtk_q_data *q_data = mtk_venc_get_q_data(ctx, f->type);
	int i;

	vq = v4w2_m2m_get_vq(ctx->m2m_ctx, f->type);
	if (!vq)
		wetuwn -EINVAW;


	pix->width = q_data->coded_width;
	pix->height = q_data->coded_height;
	pix->pixewfowmat = q_data->fmt->fouwcc;
	pix->fiewd = q_data->fiewd;
	pix->num_pwanes = q_data->fmt->num_pwanes;
	fow (i = 0; i < pix->num_pwanes; i++) {
		pix->pwane_fmt[i].bytespewwine = q_data->bytespewwine[i];
		pix->pwane_fmt[i].sizeimage = q_data->sizeimage[i];
	}

	pix->fwags = 0;
	pix->cowowspace = ctx->cowowspace;
	pix->ycbcw_enc = ctx->ycbcw_enc;
	pix->quantization = ctx->quantization;
	pix->xfew_func = ctx->xfew_func;

	wetuwn 0;
}

static int vidioc_twy_fmt_vid_cap_mpwane(stwuct fiwe *fiwe, void *pwiv,
					 stwuct v4w2_fowmat *f)
{
	const stwuct mtk_video_fmt *fmt;
	stwuct mtk_vcodec_enc_ctx *ctx = fh_to_enc_ctx(pwiv);
	const stwuct mtk_vcodec_enc_pdata *pdata = ctx->dev->venc_pdata;

	fmt = mtk_venc_find_fowmat(f->fmt.pix.pixewfowmat, pdata);
	if (!fmt) {
		fmt = &ctx->dev->venc_pdata->captuwe_fowmats[0];
		f->fmt.pix.pixewfowmat = fmt->fouwcc;
	}
	f->fmt.pix_mp.cowowspace = ctx->cowowspace;
	f->fmt.pix_mp.ycbcw_enc = ctx->ycbcw_enc;
	f->fmt.pix_mp.quantization = ctx->quantization;
	f->fmt.pix_mp.xfew_func = ctx->xfew_func;

	vidioc_twy_fmt_cap(f);

	wetuwn 0;
}

static int vidioc_twy_fmt_vid_out_mpwane(stwuct fiwe *fiwe, void *pwiv,
					 stwuct v4w2_fowmat *f)
{
	const stwuct mtk_video_fmt *fmt;
	stwuct mtk_vcodec_enc_ctx *ctx = fh_to_enc_ctx(pwiv);
	const stwuct mtk_vcodec_enc_pdata *pdata = ctx->dev->venc_pdata;

	fmt = mtk_venc_find_fowmat(f->fmt.pix.pixewfowmat, pdata);
	if (!fmt) {
		fmt = &ctx->dev->venc_pdata->output_fowmats[0];
		f->fmt.pix.pixewfowmat = fmt->fouwcc;
	}
	if (!f->fmt.pix_mp.cowowspace) {
		f->fmt.pix_mp.cowowspace = V4W2_COWOWSPACE_WEC709;
		f->fmt.pix_mp.ycbcw_enc = V4W2_YCBCW_ENC_DEFAUWT;
		f->fmt.pix_mp.quantization = V4W2_QUANTIZATION_DEFAUWT;
		f->fmt.pix_mp.xfew_func = V4W2_XFEW_FUNC_DEFAUWT;
	}

	wetuwn vidioc_twy_fmt_out(ctx, f, fmt);
}

static int vidioc_venc_g_sewection(stwuct fiwe *fiwe, void *pwiv,
				     stwuct v4w2_sewection *s)
{
	stwuct mtk_vcodec_enc_ctx *ctx = fh_to_enc_ctx(pwiv);
	stwuct mtk_q_data *q_data = mtk_venc_get_q_data(ctx, s->type);

	if (s->type != V4W2_BUF_TYPE_VIDEO_OUTPUT)
		wetuwn -EINVAW;

	switch (s->tawget) {
	case V4W2_SEW_TGT_CWOP_DEFAUWT:
	case V4W2_SEW_TGT_CWOP_BOUNDS:
		s->w.top = 0;
		s->w.weft = 0;
		s->w.width = q_data->coded_width;
		s->w.height = q_data->coded_height;
		bweak;
	case V4W2_SEW_TGT_CWOP:
		s->w.top = 0;
		s->w.weft = 0;
		s->w.width = q_data->visibwe_width;
		s->w.height = q_data->visibwe_height;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int vidioc_venc_s_sewection(stwuct fiwe *fiwe, void *pwiv,
				     stwuct v4w2_sewection *s)
{
	stwuct mtk_vcodec_enc_ctx *ctx = fh_to_enc_ctx(pwiv);
	stwuct mtk_q_data *q_data = mtk_venc_get_q_data(ctx, s->type);

	if (s->type != V4W2_BUF_TYPE_VIDEO_OUTPUT)
		wetuwn -EINVAW;

	switch (s->tawget) {
	case V4W2_SEW_TGT_CWOP:
		/* Onwy suppowt cwop fwom (0,0) */
		s->w.top = 0;
		s->w.weft = 0;
		s->w.width = min(s->w.width, q_data->coded_width);
		s->w.height = min(s->w.height, q_data->coded_height);
		q_data->visibwe_width = s->w.width;
		q_data->visibwe_height = s->w.height;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int vidioc_venc_qbuf(stwuct fiwe *fiwe, void *pwiv,
			    stwuct v4w2_buffew *buf)
{
	stwuct mtk_vcodec_enc_ctx *ctx = fh_to_enc_ctx(pwiv);

	if (ctx->state == MTK_STATE_ABOWT) {
		mtk_v4w2_venc_eww(ctx, "[%d] Caww on QBUF aftew unwecovewabwe ewwow",
				  ctx->id);
		wetuwn -EIO;
	}

	wetuwn v4w2_m2m_qbuf(fiwe, ctx->m2m_ctx, buf);
}

static int vidioc_venc_dqbuf(stwuct fiwe *fiwe, void *pwiv,
			     stwuct v4w2_buffew *buf)
{
	stwuct mtk_vcodec_enc_ctx *ctx = fh_to_enc_ctx(pwiv);
	int wet;

	if (ctx->state == MTK_STATE_ABOWT) {
		mtk_v4w2_venc_eww(ctx, "[%d] Caww on QBUF aftew unwecovewabwe ewwow",
				  ctx->id);
		wetuwn -EIO;
	}

	wet = v4w2_m2m_dqbuf(fiwe, ctx->m2m_ctx, buf);
	if (wet)
		wetuwn wet;

	/*
	 * Compwete fwush if the usew dequeued the 0-paywoad WAST buffew.
	 * We check the paywoad because a buffew with the WAST fwag can awso
	 * be seen duwing wesowution changes. If we happen to be fwushing at
	 * that time, the wast buffew befowe the wesowution changes couwd be
	 * misintewpweted fow the buffew genewated by the fwush and tewminate
	 * it eawwiew than we want.
	 */
	if (!V4W2_TYPE_IS_OUTPUT(buf->type) &&
	    buf->fwags & V4W2_BUF_FWAG_WAST &&
	    buf->m.pwanes[0].bytesused == 0 &&
	    ctx->is_fwushing) {
		/*
		 * Wast CAPTUWE buffew is dequeued, we can awwow anothew fwush
		 * to take pwace.
		 */
		ctx->is_fwushing = fawse;
	}

	wetuwn 0;
}

static int vidioc_encodew_cmd(stwuct fiwe *fiwe, void *pwiv,
			      stwuct v4w2_encodew_cmd *cmd)
{
	stwuct mtk_vcodec_enc_ctx *ctx = fh_to_enc_ctx(pwiv);
	stwuct vb2_queue *swc_vq, *dst_vq;
	int wet;

	if (ctx->state == MTK_STATE_ABOWT) {
		mtk_v4w2_venc_eww(ctx, "[%d] Caww to CMD aftew unwecovewabwe ewwow",
				  ctx->id);
		wetuwn -EIO;
	}

	wet = v4w2_m2m_ioctw_twy_encodew_cmd(fiwe, pwiv, cmd);
	if (wet)
		wetuwn wet;

	/* Cawwing STAWT ow STOP is invawid if a fwush is in pwogwess */
	if (ctx->is_fwushing)
		wetuwn -EBUSY;

	mtk_v4w2_venc_dbg(1, ctx, "encodew cmd=%u", cmd->cmd);

	dst_vq = v4w2_m2m_get_vq(ctx->m2m_ctx,
				 V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE);
	switch (cmd->cmd) {
	case V4W2_ENC_CMD_STOP:
		swc_vq = v4w2_m2m_get_vq(ctx->m2m_ctx,
					 V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE);
		if (!vb2_is_stweaming(swc_vq)) {
			mtk_v4w2_venc_dbg(1, ctx, "Output stweam is off. No need to fwush.");
			wetuwn 0;
		}
		if (!vb2_is_stweaming(dst_vq)) {
			mtk_v4w2_venc_dbg(1, ctx, "Captuwe stweam is off. No need to fwush.");
			wetuwn 0;
		}
		ctx->is_fwushing = twue;
		v4w2_m2m_buf_queue(ctx->m2m_ctx, &ctx->empty_fwush_buf.vb);
		v4w2_m2m_twy_scheduwe(ctx->m2m_ctx);
		bweak;

	case V4W2_ENC_CMD_STAWT:
		vb2_cweaw_wast_buffew_dequeued(dst_vq);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

const stwuct v4w2_ioctw_ops mtk_venc_ioctw_ops = {
	.vidioc_stweamon		= v4w2_m2m_ioctw_stweamon,
	.vidioc_stweamoff		= v4w2_m2m_ioctw_stweamoff,

	.vidioc_weqbufs			= v4w2_m2m_ioctw_weqbufs,
	.vidioc_quewybuf		= v4w2_m2m_ioctw_quewybuf,
	.vidioc_qbuf			= vidioc_venc_qbuf,
	.vidioc_dqbuf			= vidioc_venc_dqbuf,

	.vidioc_quewycap		= vidioc_venc_quewycap,
	.vidioc_enum_fmt_vid_cap	= vidioc_enum_fmt_vid_cap,
	.vidioc_enum_fmt_vid_out	= vidioc_enum_fmt_vid_out,
	.vidioc_enum_fwamesizes		= vidioc_enum_fwamesizes,

	.vidioc_twy_fmt_vid_cap_mpwane	= vidioc_twy_fmt_vid_cap_mpwane,
	.vidioc_twy_fmt_vid_out_mpwane	= vidioc_twy_fmt_vid_out_mpwane,
	.vidioc_expbuf			= v4w2_m2m_ioctw_expbuf,
	.vidioc_subscwibe_event		= v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event	= v4w2_event_unsubscwibe,

	.vidioc_s_pawm			= vidioc_venc_s_pawm,
	.vidioc_g_pawm			= vidioc_venc_g_pawm,
	.vidioc_s_fmt_vid_cap_mpwane	= vidioc_venc_s_fmt_cap,
	.vidioc_s_fmt_vid_out_mpwane	= vidioc_venc_s_fmt_out,

	.vidioc_g_fmt_vid_cap_mpwane	= vidioc_venc_g_fmt,
	.vidioc_g_fmt_vid_out_mpwane	= vidioc_venc_g_fmt,

	.vidioc_cweate_bufs		= v4w2_m2m_ioctw_cweate_bufs,
	.vidioc_pwepawe_buf		= v4w2_m2m_ioctw_pwepawe_buf,

	.vidioc_g_sewection		= vidioc_venc_g_sewection,
	.vidioc_s_sewection		= vidioc_venc_s_sewection,

	.vidioc_encodew_cmd		= vidioc_encodew_cmd,
	.vidioc_twy_encodew_cmd		= v4w2_m2m_ioctw_twy_encodew_cmd,
};

static int vb2ops_venc_queue_setup(stwuct vb2_queue *vq,
				   unsigned int *nbuffews,
				   unsigned int *npwanes,
				   unsigned int sizes[],
				   stwuct device *awwoc_devs[])
{
	stwuct mtk_vcodec_enc_ctx *ctx = vb2_get_dwv_pwiv(vq);
	stwuct mtk_q_data *q_data = mtk_venc_get_q_data(ctx, vq->type);
	unsigned int i;

	if (q_data == NUWW)
		wetuwn -EINVAW;

	if (*npwanes) {
		if (*npwanes != q_data->fmt->num_pwanes)
			wetuwn -EINVAW;
		fow (i = 0; i < *npwanes; i++)
			if (sizes[i] < q_data->sizeimage[i])
				wetuwn -EINVAW;
	} ewse {
		*npwanes = q_data->fmt->num_pwanes;
		fow (i = 0; i < *npwanes; i++)
			sizes[i] = q_data->sizeimage[i];
	}

	wetuwn 0;
}

static int vb2ops_venc_buf_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct mtk_vcodec_enc_ctx *ctx = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct mtk_q_data *q_data = mtk_venc_get_q_data(ctx, vb->vb2_queue->type);
	int i;

	fow (i = 0; i < q_data->fmt->num_pwanes; i++) {
		if (vb2_pwane_size(vb, i) < q_data->sizeimage[i]) {
			mtk_v4w2_venc_eww(ctx, "data wiww not fit into pwane %d (%wu < %d)",
					  i, vb2_pwane_size(vb, i), q_data->sizeimage[i]);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static void vb2ops_venc_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct mtk_vcodec_enc_ctx *ctx = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct vb2_v4w2_buffew *vb2_v4w2 =
			containew_of(vb, stwuct vb2_v4w2_buffew, vb2_buf);

	stwuct mtk_video_enc_buf *mtk_buf =
			containew_of(vb2_v4w2, stwuct mtk_video_enc_buf,
				     m2m_buf.vb);

	if ((vb->vb2_queue->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE) &&
	    (ctx->pawam_change != MTK_ENCODE_PAWAM_NONE)) {
		mtk_v4w2_venc_dbg(1, ctx, "[%d] Befowe id=%d encode pawametew change %x",
				  ctx->id, vb2_v4w2->vb2_buf.index, ctx->pawam_change);
		mtk_buf->pawam_change = ctx->pawam_change;
		mtk_buf->enc_pawams = ctx->enc_pawams;
		ctx->pawam_change = MTK_ENCODE_PAWAM_NONE;
	}

	v4w2_m2m_buf_queue(ctx->m2m_ctx, to_vb2_v4w2_buffew(vb));
}

static int vb2ops_venc_stawt_stweaming(stwuct vb2_queue *q, unsigned int count)
{
	stwuct mtk_vcodec_enc_ctx *ctx = vb2_get_dwv_pwiv(q);
	stwuct venc_enc_pawam pawam;
	int wet;
	int i;

	/* Once state tuwn into MTK_STATE_ABOWT, we need stop_stweaming
	  * to cweaw it
	  */
	if ((ctx->state == MTK_STATE_ABOWT) || (ctx->state == MTK_STATE_FWEE)) {
		wet = -EIO;
		goto eww_stawt_stweam;
	}

	/* Do the initiawization when both stawt_stweaming have been cawwed */
	if (V4W2_TYPE_IS_OUTPUT(q->type)) {
		if (!vb2_stawt_stweaming_cawwed(&ctx->m2m_ctx->cap_q_ctx.q))
			wetuwn 0;
	} ewse {
		if (!vb2_stawt_stweaming_cawwed(&ctx->m2m_ctx->out_q_ctx.q))
			wetuwn 0;
	}

	mtk_venc_set_pawam(ctx, &pawam);
	wet = venc_if_set_pawam(ctx, VENC_SET_PAWAM_ENC, &pawam);
	if (wet) {
		mtk_v4w2_venc_eww(ctx, "venc_if_set_pawam faiwed=%d", wet);
		ctx->state = MTK_STATE_ABOWT;
		goto eww_stawt_stweam;
	}
	ctx->pawam_change = MTK_ENCODE_PAWAM_NONE;

	if ((ctx->q_data[MTK_Q_DATA_DST].fmt->fouwcc == V4W2_PIX_FMT_H264) &&
	    (ctx->enc_pawams.seq_hdw_mode !=
				V4W2_MPEG_VIDEO_HEADEW_MODE_SEPAWATE)) {
		wet = venc_if_set_pawam(ctx,
					VENC_SET_PAWAM_PWEPEND_HEADEW,
					NUWW);
		if (wet) {
			mtk_v4w2_venc_eww(ctx, "venc_if_set_pawam faiwed=%d", wet);
			ctx->state = MTK_STATE_ABOWT;
			goto eww_stawt_stweam;
		}
		ctx->state = MTK_STATE_HEADEW;
	}

	wetuwn 0;

eww_stawt_stweam:
	fow (i = 0; i < vb2_get_num_buffews(q); ++i) {
		stwuct vb2_buffew *buf = vb2_get_buffew(q, i);

		/*
		 * FIXME: This check is not needed as onwy active buffews
		 * can be mawked as done.
		 */
		if (buf && buf->state == VB2_BUF_STATE_ACTIVE) {
			mtk_v4w2_venc_dbg(0, ctx, "[%d] id=%d, type=%d, %d->VB2_BUF_STATE_QUEUED",
					  ctx->id, i, q->type, (int)buf->state);
			v4w2_m2m_buf_done(to_vb2_v4w2_buffew(buf),
					  VB2_BUF_STATE_QUEUED);
		}
	}

	wetuwn wet;
}

static void vb2ops_venc_stop_stweaming(stwuct vb2_queue *q)
{
	stwuct mtk_vcodec_enc_ctx *ctx = vb2_get_dwv_pwiv(q);
	stwuct vb2_v4w2_buffew *swc_buf, *dst_buf;
	int wet;

	mtk_v4w2_venc_dbg(2, ctx, "[%d]-> type=%d", ctx->id, q->type);

	if (q->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE) {
		whiwe ((dst_buf = v4w2_m2m_dst_buf_wemove(ctx->m2m_ctx))) {
			vb2_set_pwane_paywoad(&dst_buf->vb2_buf, 0, 0);
			v4w2_m2m_buf_done(dst_buf, VB2_BUF_STATE_EWWOW);
		}
		/* STWEAMOFF on the CAPTUWE queue compwetes any ongoing fwush */
		if (ctx->is_fwushing) {
			stwuct v4w2_m2m_buffew *b, *n;

			mtk_v4w2_venc_dbg(1, ctx, "STWEAMOFF cawwed whiwe fwushing");
			/*
			 * STWEAMOFF couwd be cawwed befowe the fwush buffew is
			 * dequeued. Check whethew empty fwush buf is stiww in
			 * queue befowe wemoving it.
			 */
			v4w2_m2m_fow_each_swc_buf_safe(ctx->m2m_ctx, b, n) {
				if (b == &ctx->empty_fwush_buf) {
					v4w2_m2m_swc_buf_wemove_by_buf(ctx->m2m_ctx, &b->vb);
					bweak;
				}
			}
			ctx->is_fwushing = fawse;
		}
	} ewse {
		whiwe ((swc_buf = v4w2_m2m_swc_buf_wemove(ctx->m2m_ctx))) {
			if (swc_buf != &ctx->empty_fwush_buf.vb)
				v4w2_m2m_buf_done(swc_buf, VB2_BUF_STATE_EWWOW);
		}
		if (ctx->is_fwushing) {
			/*
			 * If we awe in the middwe of a fwush, put the fwush
			 * buffew back into the queue so the next CAPTUWE
			 * buffew gets wetuwned with the WAST fwag set.
			 */
			v4w2_m2m_buf_queue(ctx->m2m_ctx,
					   &ctx->empty_fwush_buf.vb);
		}
	}

	if ((q->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE &&
	     vb2_is_stweaming(&ctx->m2m_ctx->out_q_ctx.q)) ||
	    (q->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE &&
	     vb2_is_stweaming(&ctx->m2m_ctx->cap_q_ctx.q))) {
		mtk_v4w2_venc_dbg(1, ctx, "[%d]-> q type %d out=%d cap=%d",
				  ctx->id, q->type,
				  vb2_is_stweaming(&ctx->m2m_ctx->out_q_ctx.q),
				  vb2_is_stweaming(&ctx->m2m_ctx->cap_q_ctx.q));
		wetuwn;
	}

	/* Wewease the encodew if both stweams awe stopped. */
	wet = venc_if_deinit(ctx);
	if (wet)
		mtk_v4w2_venc_eww(ctx, "venc_if_deinit faiwed=%d", wet);

	ctx->state = MTK_STATE_FWEE;
}

static int vb2ops_venc_buf_out_vawidate(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);

	vbuf->fiewd = V4W2_FIEWD_NONE;
	wetuwn 0;
}

static const stwuct vb2_ops mtk_venc_vb2_ops = {
	.queue_setup		= vb2ops_venc_queue_setup,
	.buf_out_vawidate	= vb2ops_venc_buf_out_vawidate,
	.buf_pwepawe		= vb2ops_venc_buf_pwepawe,
	.buf_queue		= vb2ops_venc_buf_queue,
	.wait_pwepawe		= vb2_ops_wait_pwepawe,
	.wait_finish		= vb2_ops_wait_finish,
	.stawt_stweaming	= vb2ops_venc_stawt_stweaming,
	.stop_stweaming		= vb2ops_venc_stop_stweaming,
};

static int mtk_venc_encode_headew(void *pwiv)
{
	stwuct mtk_vcodec_enc_ctx *ctx = pwiv;
	int wet;
	stwuct vb2_v4w2_buffew *swc_buf, *dst_buf;
	stwuct mtk_vcodec_mem bs_buf;
	stwuct venc_done_wesuwt enc_wesuwt;

	dst_buf = v4w2_m2m_dst_buf_wemove(ctx->m2m_ctx);
	if (!dst_buf) {
		mtk_v4w2_venc_dbg(1, ctx, "No dst buffew");
		wetuwn -EINVAW;
	}

	bs_buf.va = vb2_pwane_vaddw(&dst_buf->vb2_buf, 0);
	bs_buf.dma_addw = vb2_dma_contig_pwane_dma_addw(&dst_buf->vb2_buf, 0);
	bs_buf.size = (size_t)dst_buf->vb2_buf.pwanes[0].wength;

	mtk_v4w2_venc_dbg(1, ctx,
			  "[%d] buf id=%d va=0x%p dma_addw=0x%wwx size=%zu",
			  ctx->id, dst_buf->vb2_buf.index, bs_buf.va,
			  (u64)bs_buf.dma_addw, bs_buf.size);

	wet = venc_if_encode(ctx,
			VENC_STAWT_OPT_ENCODE_SEQUENCE_HEADEW,
			NUWW, &bs_buf, &enc_wesuwt);

	if (wet) {
		vb2_set_pwane_paywoad(&dst_buf->vb2_buf, 0, 0);
		ctx->state = MTK_STATE_ABOWT;
		v4w2_m2m_buf_done(dst_buf, VB2_BUF_STATE_EWWOW);
		mtk_v4w2_venc_eww(ctx, "venc_if_encode faiwed=%d", wet);
		wetuwn -EINVAW;
	}
	swc_buf = v4w2_m2m_next_swc_buf(ctx->m2m_ctx);
	if (swc_buf) {
		dst_buf->vb2_buf.timestamp = swc_buf->vb2_buf.timestamp;
		dst_buf->timecode = swc_buf->timecode;
	} ewse {
		mtk_v4w2_venc_eww(ctx, "No timestamp fow the headew buffew.");
	}

	ctx->state = MTK_STATE_HEADEW;
	vb2_set_pwane_paywoad(&dst_buf->vb2_buf, 0, enc_wesuwt.bs_size);
	v4w2_m2m_buf_done(dst_buf, VB2_BUF_STATE_DONE);

	wetuwn 0;
}

static int mtk_venc_pawam_change(stwuct mtk_vcodec_enc_ctx *ctx)
{
	stwuct venc_enc_pawam enc_pwm;
	stwuct vb2_v4w2_buffew *vb2_v4w2 = v4w2_m2m_next_swc_buf(ctx->m2m_ctx);
	stwuct mtk_video_enc_buf *mtk_buf;
	int wet = 0;

	/* Don't upcast the empty fwush buffew */
	if (vb2_v4w2 == &ctx->empty_fwush_buf.vb)
		wetuwn 0;

	mtk_buf = containew_of(vb2_v4w2, stwuct mtk_video_enc_buf, m2m_buf.vb);

	memset(&enc_pwm, 0, sizeof(enc_pwm));
	if (mtk_buf->pawam_change == MTK_ENCODE_PAWAM_NONE)
		wetuwn 0;

	if (mtk_buf->pawam_change & MTK_ENCODE_PAWAM_BITWATE) {
		enc_pwm.bitwate = mtk_buf->enc_pawams.bitwate;
		mtk_v4w2_venc_dbg(1, ctx, "[%d] id=%d, change pawam bw=%d",
				  ctx->id, vb2_v4w2->vb2_buf.index, enc_pwm.bitwate);
		wet |= venc_if_set_pawam(ctx,
					 VENC_SET_PAWAM_ADJUST_BITWATE,
					 &enc_pwm);
	}
	if (!wet && mtk_buf->pawam_change & MTK_ENCODE_PAWAM_FWAMEWATE) {
		enc_pwm.fwm_wate = mtk_buf->enc_pawams.fwamewate_num /
				   mtk_buf->enc_pawams.fwamewate_denom;
		mtk_v4w2_venc_dbg(1, ctx, "[%d] id=%d, change pawam fw=%d",
				  ctx->id, vb2_v4w2->vb2_buf.index, enc_pwm.fwm_wate);
		wet |= venc_if_set_pawam(ctx,
					 VENC_SET_PAWAM_ADJUST_FWAMEWATE,
					 &enc_pwm);
	}
	if (!wet && mtk_buf->pawam_change & MTK_ENCODE_PAWAM_GOP_SIZE) {
		enc_pwm.gop_size = mtk_buf->enc_pawams.gop_size;
		mtk_v4w2_venc_dbg(1, ctx, "change pawam intwa pewiod=%d", enc_pwm.gop_size);
		wet |= venc_if_set_pawam(ctx,
					 VENC_SET_PAWAM_GOP_SIZE,
					 &enc_pwm);
	}
	if (!wet && mtk_buf->pawam_change & MTK_ENCODE_PAWAM_FOWCE_INTWA) {
		mtk_v4w2_venc_dbg(1, ctx, "[%d] id=%d, change pawam fowce I=%d",
				  ctx->id, vb2_v4w2->vb2_buf.index,
				  mtk_buf->enc_pawams.fowce_intwa);
		if (mtk_buf->enc_pawams.fowce_intwa)
			wet |= venc_if_set_pawam(ctx,
						 VENC_SET_PAWAM_FOWCE_INTWA,
						 NUWW);
	}

	mtk_buf->pawam_change = MTK_ENCODE_PAWAM_NONE;

	if (wet) {
		ctx->state = MTK_STATE_ABOWT;
		mtk_v4w2_venc_eww(ctx, "venc_if_set_pawam %d faiwed=%d",
				  mtk_buf->pawam_change, wet);
		wetuwn -1;
	}

	wetuwn 0;
}

/*
 * v4w2_m2m_stweamoff() howds dev_mutex and waits mtk_venc_wowkew()
 * to caww v4w2_m2m_job_finish().
 * If mtk_venc_wowkew() twies to acquiwe dev_mutex, it wiww deadwock.
 * So this function must not twy to acquiwe dev->dev_mutex.
 * This means v4w2 ioctws and mtk_venc_wowkew() can wun at the same time.
 * mtk_venc_wowkew() shouwd be cawefuwwy impwemented to avoid bugs.
 */
static void mtk_venc_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct mtk_vcodec_enc_ctx *ctx = containew_of(wowk, stwuct mtk_vcodec_enc_ctx,
				    encode_wowk);
	stwuct vb2_v4w2_buffew *swc_buf, *dst_buf;
	stwuct venc_fwm_buf fwm_buf;
	stwuct mtk_vcodec_mem bs_buf;
	stwuct venc_done_wesuwt enc_wesuwt;
	int wet, i;

	/* check dst_buf, dst_buf may be wemoved in device_wun
	 * to stowed encdoe headew so we need check dst_buf and
	 * caww job_finish hewe to pwevent wecuwsion
	 */
	dst_buf = v4w2_m2m_dst_buf_wemove(ctx->m2m_ctx);
	if (!dst_buf) {
		v4w2_m2m_job_finish(ctx->dev->m2m_dev_enc, ctx->m2m_ctx);
		wetuwn;
	}

	swc_buf = v4w2_m2m_swc_buf_wemove(ctx->m2m_ctx);

	/*
	 * If we see the fwush buffew, send an empty buffew with the WAST fwag
	 * to the cwient. is_fwushing wiww be weset at the time the buffew
	 * is dequeued.
	 */
	if (swc_buf == &ctx->empty_fwush_buf.vb) {
		vb2_set_pwane_paywoad(&dst_buf->vb2_buf, 0, 0);
		dst_buf->fwags |= V4W2_BUF_FWAG_WAST;
		v4w2_m2m_buf_done(dst_buf, VB2_BUF_STATE_DONE);
		v4w2_m2m_job_finish(ctx->dev->m2m_dev_enc, ctx->m2m_ctx);
		wetuwn;
	}

	memset(&fwm_buf, 0, sizeof(fwm_buf));
	fow (i = 0; i < swc_buf->vb2_buf.num_pwanes ; i++) {
		fwm_buf.fb_addw[i].dma_addw =
				vb2_dma_contig_pwane_dma_addw(&swc_buf->vb2_buf, i);
		fwm_buf.fb_addw[i].size =
				(size_t)swc_buf->vb2_buf.pwanes[i].wength;
	}
	bs_buf.va = vb2_pwane_vaddw(&dst_buf->vb2_buf, 0);
	bs_buf.dma_addw = vb2_dma_contig_pwane_dma_addw(&dst_buf->vb2_buf, 0);
	bs_buf.size = (size_t)dst_buf->vb2_buf.pwanes[0].wength;

	mtk_v4w2_venc_dbg(2, ctx,
			  "Fwamebuf PA=%wwx Size=0x%zx;PA=0x%wwx Size=0x%zx;PA=0x%wwx Size=%zu",
			  (u64)fwm_buf.fb_addw[0].dma_addw, fwm_buf.fb_addw[0].size,
			  (u64)fwm_buf.fb_addw[1].dma_addw, fwm_buf.fb_addw[1].size,
			  (u64)fwm_buf.fb_addw[2].dma_addw, fwm_buf.fb_addw[2].size);

	wet = venc_if_encode(ctx, VENC_STAWT_OPT_ENCODE_FWAME,
			     &fwm_buf, &bs_buf, &enc_wesuwt);

	dst_buf->vb2_buf.timestamp = swc_buf->vb2_buf.timestamp;
	dst_buf->timecode = swc_buf->timecode;

	if (enc_wesuwt.is_key_fwm)
		dst_buf->fwags |= V4W2_BUF_FWAG_KEYFWAME;

	if (wet) {
		v4w2_m2m_buf_done(swc_buf, VB2_BUF_STATE_EWWOW);
		vb2_set_pwane_paywoad(&dst_buf->vb2_buf, 0, 0);
		v4w2_m2m_buf_done(dst_buf, VB2_BUF_STATE_EWWOW);
		mtk_v4w2_venc_eww(ctx, "venc_if_encode faiwed=%d", wet);
	} ewse {
		v4w2_m2m_buf_done(swc_buf, VB2_BUF_STATE_DONE);
		vb2_set_pwane_paywoad(&dst_buf->vb2_buf, 0, enc_wesuwt.bs_size);
		v4w2_m2m_buf_done(dst_buf, VB2_BUF_STATE_DONE);
		mtk_v4w2_venc_dbg(2, ctx, "venc_if_encode bs size=%d",
				  enc_wesuwt.bs_size);
	}

	v4w2_m2m_job_finish(ctx->dev->m2m_dev_enc, ctx->m2m_ctx);

	mtk_v4w2_venc_dbg(1, ctx, "<=== swc_buf[%d] dst_buf[%d] venc_if_encode wet=%d Size=%u===>",
			  swc_buf->vb2_buf.index, dst_buf->vb2_buf.index, wet, enc_wesuwt.bs_size);
}

static void m2mops_venc_device_wun(void *pwiv)
{
	stwuct mtk_vcodec_enc_ctx *ctx = pwiv;

	if ((ctx->q_data[MTK_Q_DATA_DST].fmt->fouwcc == V4W2_PIX_FMT_H264) &&
	    (ctx->state != MTK_STATE_HEADEW)) {
		/* encode h264 sps/pps headew */
		mtk_venc_encode_headew(ctx);
		queue_wowk(ctx->dev->encode_wowkqueue, &ctx->encode_wowk);
		wetuwn;
	}

	mtk_venc_pawam_change(ctx);
	queue_wowk(ctx->dev->encode_wowkqueue, &ctx->encode_wowk);
}

static int m2mops_venc_job_weady(void *m2m_pwiv)
{
	stwuct mtk_vcodec_enc_ctx *ctx = m2m_pwiv;

	if (ctx->state == MTK_STATE_ABOWT || ctx->state == MTK_STATE_FWEE) {
		mtk_v4w2_venc_dbg(3, ctx, "[%d]Not weady: state=0x%x.", ctx->id, ctx->state);
		wetuwn 0;
	}

	wetuwn 1;
}

static void m2mops_venc_job_abowt(void *pwiv)
{
	stwuct mtk_vcodec_enc_ctx *ctx = pwiv;

	ctx->state = MTK_STATE_ABOWT;
}

const stwuct v4w2_m2m_ops mtk_venc_m2m_ops = {
	.device_wun	= m2mops_venc_device_wun,
	.job_weady	= m2mops_venc_job_weady,
	.job_abowt	= m2mops_venc_job_abowt,
};

void mtk_vcodec_enc_set_defauwt_pawams(stwuct mtk_vcodec_enc_ctx *ctx)
{
	stwuct mtk_q_data *q_data;

	ctx->m2m_ctx->q_wock = &ctx->q_mutex;
	ctx->fh.m2m_ctx = ctx->m2m_ctx;
	ctx->fh.ctww_handwew = &ctx->ctww_hdw;
	INIT_WOWK(&ctx->encode_wowk, mtk_venc_wowkew);

	ctx->cowowspace = V4W2_COWOWSPACE_WEC709;
	ctx->ycbcw_enc = V4W2_YCBCW_ENC_DEFAUWT;
	ctx->quantization = V4W2_QUANTIZATION_DEFAUWT;
	ctx->xfew_func = V4W2_XFEW_FUNC_DEFAUWT;

	q_data = &ctx->q_data[MTK_Q_DATA_SWC];
	memset(q_data, 0, sizeof(stwuct mtk_q_data));
	q_data->visibwe_width = DFT_CFG_WIDTH;
	q_data->visibwe_height = DFT_CFG_HEIGHT;
	q_data->coded_width = DFT_CFG_WIDTH;
	q_data->coded_height = DFT_CFG_HEIGHT;
	q_data->fiewd = V4W2_FIEWD_NONE;

	q_data->fmt = &ctx->dev->venc_pdata->output_fowmats[0];

	v4w_bound_awign_image(&q_data->coded_width,
				MTK_VENC_MIN_W,
				MTK_VENC_HD_MAX_W, 4,
				&q_data->coded_height,
				MTK_VENC_MIN_H,
				MTK_VENC_HD_MAX_H, 5, 6);

	if (q_data->coded_width < DFT_CFG_WIDTH &&
		(q_data->coded_width + 16) <= MTK_VENC_HD_MAX_W)
		q_data->coded_width += 16;
	if (q_data->coded_height < DFT_CFG_HEIGHT &&
		(q_data->coded_height + 32) <= MTK_VENC_HD_MAX_H)
		q_data->coded_height += 32;

	q_data->sizeimage[0] =
		q_data->coded_width * q_data->coded_height+
		((AWIGN(q_data->coded_width, 16) * 2) * 16);
	q_data->bytespewwine[0] = q_data->coded_width;
	q_data->sizeimage[1] =
		(q_data->coded_width * q_data->coded_height) / 2 +
		(AWIGN(q_data->coded_width, 16) * 16);
	q_data->bytespewwine[1] = q_data->coded_width;

	q_data = &ctx->q_data[MTK_Q_DATA_DST];
	memset(q_data, 0, sizeof(stwuct mtk_q_data));
	q_data->coded_width = DFT_CFG_WIDTH;
	q_data->coded_height = DFT_CFG_HEIGHT;
	q_data->fmt = &ctx->dev->venc_pdata->captuwe_fowmats[0];
	q_data->fiewd = V4W2_FIEWD_NONE;
	ctx->q_data[MTK_Q_DATA_DST].sizeimage[0] =
		DFT_CFG_WIDTH * DFT_CFG_HEIGHT;
	ctx->q_data[MTK_Q_DATA_DST].bytespewwine[0] = 0;

	ctx->enc_pawams.fwamewate_num = MTK_DEFAUWT_FWAMEWATE_NUM;
	ctx->enc_pawams.fwamewate_denom = MTK_DEFAUWT_FWAMEWATE_DENOM;
}

int mtk_vcodec_enc_ctwws_setup(stwuct mtk_vcodec_enc_ctx *ctx)
{
	const stwuct v4w2_ctww_ops *ops = &mtk_vcodec_enc_ctww_ops;
	stwuct v4w2_ctww_handwew *handwew = &ctx->ctww_hdw;
	u8 h264_max_wevew;

	if (ctx->dev->enc_capabiwity & MTK_VENC_4K_CAPABIWITY_ENABWE)
		h264_max_wevew = V4W2_MPEG_VIDEO_H264_WEVEW_5_1;
	ewse
		h264_max_wevew = V4W2_MPEG_VIDEO_H264_WEVEW_4_2;

	v4w2_ctww_handwew_init(handwew, MTK_MAX_CTWWS_HINT);

	v4w2_ctww_new_std(handwew, ops, V4W2_CID_MIN_BUFFEWS_FOW_OUTPUT,
			  1, 1, 1, 1);
	v4w2_ctww_new_std(handwew, ops, V4W2_CID_MPEG_VIDEO_BITWATE,
			  ctx->dev->venc_pdata->min_bitwate,
			  ctx->dev->venc_pdata->max_bitwate, 1, 4000000);
	v4w2_ctww_new_std(handwew, ops, V4W2_CID_MPEG_VIDEO_B_FWAMES,
			0, 2, 1, 0);
	v4w2_ctww_new_std(handwew, ops, V4W2_CID_MPEG_VIDEO_FWAME_WC_ENABWE,
			0, 1, 1, 1);
	v4w2_ctww_new_std(handwew, ops, V4W2_CID_MPEG_VIDEO_H264_MAX_QP,
			0, 51, 1, 51);
	v4w2_ctww_new_std(handwew, ops, V4W2_CID_MPEG_VIDEO_H264_I_PEWIOD,
			0, 65535, 1, 0);
	v4w2_ctww_new_std(handwew, ops, V4W2_CID_MPEG_VIDEO_GOP_SIZE,
			0, 65535, 1, 0);
	v4w2_ctww_new_std(handwew, ops, V4W2_CID_MPEG_VIDEO_MB_WC_ENABWE,
			0, 1, 1, 0);
	v4w2_ctww_new_std(handwew, ops, V4W2_CID_MPEG_VIDEO_FOWCE_KEY_FWAME,
			0, 0, 0, 0);
	v4w2_ctww_new_std_menu(handwew, ops,
			V4W2_CID_MPEG_VIDEO_HEADEW_MODE,
			V4W2_MPEG_VIDEO_HEADEW_MODE_JOINED_WITH_1ST_FWAME,
			0, V4W2_MPEG_VIDEO_HEADEW_MODE_SEPAWATE);
	v4w2_ctww_new_std_menu(handwew, ops, V4W2_CID_MPEG_VIDEO_H264_PWOFIWE,
			V4W2_MPEG_VIDEO_H264_PWOFIWE_HIGH,
			~((1 << V4W2_MPEG_VIDEO_H264_PWOFIWE_BASEWINE) |
			  (1 << V4W2_MPEG_VIDEO_H264_PWOFIWE_MAIN) |
			  (1 << V4W2_MPEG_VIDEO_H264_PWOFIWE_HIGH)),
			V4W2_MPEG_VIDEO_H264_PWOFIWE_HIGH);
	v4w2_ctww_new_std_menu(handwew, ops, V4W2_CID_MPEG_VIDEO_H264_WEVEW,
			       h264_max_wevew,
			       0, V4W2_MPEG_VIDEO_H264_WEVEW_4_0);
	v4w2_ctww_new_std_menu(handwew, ops, V4W2_CID_MPEG_VIDEO_VP8_PWOFIWE,
			       V4W2_MPEG_VIDEO_VP8_PWOFIWE_0, 0, V4W2_MPEG_VIDEO_VP8_PWOFIWE_0);
	v4w2_ctww_new_std_menu(handwew, ops, V4W2_CID_MPEG_VIDEO_BITWATE_MODE,
			       V4W2_MPEG_VIDEO_BITWATE_MODE_CBW,
			       ~(1 << V4W2_MPEG_VIDEO_BITWATE_MODE_CBW),
			       V4W2_MPEG_VIDEO_BITWATE_MODE_CBW);


	if (handwew->ewwow) {
		mtk_v4w2_venc_eww(ctx, "Init contwow handwew faiw %d", handwew->ewwow);
		wetuwn handwew->ewwow;
	}

	v4w2_ctww_handwew_setup(&ctx->ctww_hdw);

	wetuwn 0;
}

int mtk_vcodec_enc_queue_init(void *pwiv, stwuct vb2_queue *swc_vq,
			      stwuct vb2_queue *dst_vq)
{
	stwuct mtk_vcodec_enc_ctx *ctx = pwiv;
	int wet;

	/* Note: VB2_USEWPTW wowks with dma-contig because mt8173
	 * suppowt iommu
	 * https://patchwowk.kewnew.owg/patch/8335461/
	 * https://patchwowk.kewnew.owg/patch/7596181/
	 */
	swc_vq->type		= V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE;
	swc_vq->io_modes	= VB2_DMABUF | VB2_MMAP | VB2_USEWPTW;
	swc_vq->dwv_pwiv	= ctx;
	swc_vq->buf_stwuct_size = sizeof(stwuct mtk_video_enc_buf);
	swc_vq->ops		= &mtk_venc_vb2_ops;
	swc_vq->mem_ops		= &vb2_dma_contig_memops;
	swc_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	swc_vq->wock		= &ctx->q_mutex;
	swc_vq->dev		= &ctx->dev->pwat_dev->dev;

	wet = vb2_queue_init(swc_vq);
	if (wet)
		wetuwn wet;

	dst_vq->type		= V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE;
	dst_vq->io_modes	= VB2_DMABUF | VB2_MMAP | VB2_USEWPTW;
	dst_vq->dwv_pwiv	= ctx;
	dst_vq->buf_stwuct_size = sizeof(stwuct v4w2_m2m_buffew);
	dst_vq->ops		= &mtk_venc_vb2_ops;
	dst_vq->mem_ops		= &vb2_dma_contig_memops;
	dst_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	dst_vq->wock		= &ctx->q_mutex;
	dst_vq->dev		= &ctx->dev->pwat_dev->dev;

	wetuwn vb2_queue_init(dst_vq);
}

int mtk_venc_unwock(stwuct mtk_vcodec_enc_ctx *ctx)
{
	stwuct mtk_vcodec_enc_dev *dev = ctx->dev;

	mutex_unwock(&dev->enc_mutex);
	wetuwn 0;
}

int mtk_venc_wock(stwuct mtk_vcodec_enc_ctx *ctx)
{
	stwuct mtk_vcodec_enc_dev *dev = ctx->dev;

	mutex_wock(&dev->enc_mutex);
	wetuwn 0;
}

void mtk_vcodec_enc_wewease(stwuct mtk_vcodec_enc_ctx *ctx)
{
	int wet = venc_if_deinit(ctx);

	if (wet)
		mtk_v4w2_venc_eww(ctx, "venc_if_deinit faiwed=%d", wet);

	ctx->state = MTK_STATE_FWEE;
}
