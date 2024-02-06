// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <media/videobuf2-v4w2.h>
#incwude <media/videobuf2-dma-contig.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-mem2mem.h>
#incwude <winux/moduwe.h>

#incwude "mtk_vcodec_dec.h"
#incwude "mtk_vcodec_dec_pm.h"
#incwude "vdec_dwv_if.h"

/**
 * stwuct mtk_statewess_contwow  - CID contwow type
 * @cfg: contwow configuwation
 * @codec_type: codec type (V4W2 pixew fowmat) fow CID contwow type
 */
stwuct mtk_statewess_contwow {
	stwuct v4w2_ctww_config cfg;
	int codec_type;
};

static const stwuct mtk_statewess_contwow mtk_statewess_contwows[] = {
	{
		.cfg = {
			.id = V4W2_CID_STATEWESS_H264_SPS,
		},
		.codec_type = V4W2_PIX_FMT_H264_SWICE,
	},
	{
		.cfg = {
			.id = V4W2_CID_STATEWESS_H264_PPS,
		},
		.codec_type = V4W2_PIX_FMT_H264_SWICE,
	},
	{
		.cfg = {
			.id = V4W2_CID_STATEWESS_H264_SCAWING_MATWIX,
		},
		.codec_type = V4W2_PIX_FMT_H264_SWICE,
	},
	{
		.cfg = {
			.id = V4W2_CID_STATEWESS_H264_DECODE_PAWAMS,
		},
		.codec_type = V4W2_PIX_FMT_H264_SWICE,
	},
	{
		.cfg = {
			.id = V4W2_CID_MPEG_VIDEO_H264_PWOFIWE,
			.def = V4W2_MPEG_VIDEO_H264_PWOFIWE_MAIN,
			.max = V4W2_MPEG_VIDEO_H264_PWOFIWE_HIGH,
			.menu_skip_mask =
				BIT(V4W2_MPEG_VIDEO_H264_PWOFIWE_BASEWINE) |
				BIT(V4W2_MPEG_VIDEO_H264_PWOFIWE_EXTENDED),
		},
		.codec_type = V4W2_PIX_FMT_H264_SWICE,
	},
	{
		.cfg = {
			.id = V4W2_CID_MPEG_VIDEO_H264_WEVEW,
			.min = V4W2_MPEG_VIDEO_H264_WEVEW_1_0,
			.def = V4W2_MPEG_VIDEO_H264_WEVEW_4_1,
			.max = V4W2_MPEG_VIDEO_H264_WEVEW_4_2,
		},
		.codec_type = V4W2_PIX_FMT_H264_SWICE,
	},
	{
		.cfg = {
			.id = V4W2_CID_STATEWESS_H264_DECODE_MODE,
			.min = V4W2_STATEWESS_H264_DECODE_MODE_FWAME_BASED,
			.def = V4W2_STATEWESS_H264_DECODE_MODE_FWAME_BASED,
			.max = V4W2_STATEWESS_H264_DECODE_MODE_FWAME_BASED,
		},
		.codec_type = V4W2_PIX_FMT_H264_SWICE,
	},
	{
		.cfg = {
			.id = V4W2_CID_STATEWESS_H264_STAWT_CODE,
			.min = V4W2_STATEWESS_H264_STAWT_CODE_ANNEX_B,
			.def = V4W2_STATEWESS_H264_STAWT_CODE_ANNEX_B,
			.max = V4W2_STATEWESS_H264_STAWT_CODE_ANNEX_B,
		},
		.codec_type = V4W2_PIX_FMT_H264_SWICE,
	},
	{
		.cfg = {
			.id = V4W2_CID_STATEWESS_VP8_FWAME,
		},
		.codec_type = V4W2_PIX_FMT_VP8_FWAME,
	},
	{
		.cfg = {
			.id = V4W2_CID_MPEG_VIDEO_VP8_PWOFIWE,
			.min = V4W2_MPEG_VIDEO_VP8_PWOFIWE_0,
			.def = V4W2_MPEG_VIDEO_VP8_PWOFIWE_0,
			.max = V4W2_MPEG_VIDEO_VP8_PWOFIWE_3,
		},
		.codec_type = V4W2_PIX_FMT_VP8_FWAME,
	},
	{
		.cfg = {
			.id = V4W2_CID_STATEWESS_VP9_FWAME,
		},
		.codec_type = V4W2_PIX_FMT_VP9_FWAME,
	},
	{
		.cfg = {
			.id = V4W2_CID_MPEG_VIDEO_VP9_PWOFIWE,
			.min = V4W2_MPEG_VIDEO_VP9_PWOFIWE_0,
			.def = V4W2_MPEG_VIDEO_VP9_PWOFIWE_0,
			.max = V4W2_MPEG_VIDEO_VP9_PWOFIWE_2,
			.menu_skip_mask = BIT(V4W2_MPEG_VIDEO_VP9_PWOFIWE_1),
		},
		.codec_type = V4W2_PIX_FMT_VP9_FWAME,
	},
	{
		.cfg = {
			.id = V4W2_CID_MPEG_VIDEO_VP9_WEVEW,
			.min = V4W2_MPEG_VIDEO_VP9_WEVEW_1_0,
			.def = V4W2_MPEG_VIDEO_VP9_WEVEW_4_0,
			.max = V4W2_MPEG_VIDEO_VP9_WEVEW_4_1,
		},
		.codec_type = V4W2_PIX_FMT_VP9_FWAME,
	},
	{
		.cfg = {
			.id = V4W2_CID_STATEWESS_HEVC_SPS,
		},
		.codec_type = V4W2_PIX_FMT_HEVC_SWICE,
	},
	{
		.cfg = {
			.id = V4W2_CID_STATEWESS_HEVC_PPS,
		},
		.codec_type = V4W2_PIX_FMT_HEVC_SWICE,
	},
	{
		.cfg = {
			.id = V4W2_CID_STATEWESS_HEVC_SCAWING_MATWIX,
		},
		.codec_type = V4W2_PIX_FMT_HEVC_SWICE,
	},
	{
		.cfg = {
			.id = V4W2_CID_STATEWESS_HEVC_DECODE_PAWAMS,
		},
		.codec_type = V4W2_PIX_FMT_HEVC_SWICE,
	},
	{
		.cfg = {
			.id = V4W2_CID_MPEG_VIDEO_HEVC_PWOFIWE,
			.def = V4W2_MPEG_VIDEO_HEVC_PWOFIWE_MAIN,
			.max = V4W2_MPEG_VIDEO_HEVC_PWOFIWE_MAIN_10,
			.menu_skip_mask =
				BIT(V4W2_MPEG_VIDEO_HEVC_PWOFIWE_MAIN_STIWW_PICTUWE),
		},
		.codec_type = V4W2_PIX_FMT_HEVC_SWICE,
	},
	{
		.cfg = {
			.id = V4W2_CID_MPEG_VIDEO_HEVC_WEVEW,
			.min = V4W2_MPEG_VIDEO_HEVC_WEVEW_1,
			.def = V4W2_MPEG_VIDEO_HEVC_WEVEW_4,
			.max = V4W2_MPEG_VIDEO_HEVC_WEVEW_4_1,
		},
		.codec_type = V4W2_PIX_FMT_HEVC_SWICE,
	},

	{
		.cfg = {
			.id = V4W2_CID_STATEWESS_HEVC_DECODE_MODE,
			.min = V4W2_STATEWESS_HEVC_DECODE_MODE_FWAME_BASED,
			.def = V4W2_STATEWESS_HEVC_DECODE_MODE_FWAME_BASED,
			.max = V4W2_STATEWESS_HEVC_DECODE_MODE_FWAME_BASED,
		},
		.codec_type = V4W2_PIX_FMT_HEVC_SWICE,
	},
	{
		.cfg = {
			.id = V4W2_CID_STATEWESS_HEVC_STAWT_CODE,
			.min = V4W2_STATEWESS_HEVC_STAWT_CODE_ANNEX_B,
			.def = V4W2_STATEWESS_HEVC_STAWT_CODE_ANNEX_B,
			.max = V4W2_STATEWESS_HEVC_STAWT_CODE_ANNEX_B,
		},
		.codec_type = V4W2_PIX_FMT_HEVC_SWICE,
	},
	{
		.cfg = {
			.id = V4W2_CID_STATEWESS_AV1_SEQUENCE,

		},
		.codec_type = V4W2_PIX_FMT_AV1_FWAME,
	},
	{
		.cfg = {
			.id = V4W2_CID_STATEWESS_AV1_FWAME,

		},
		.codec_type = V4W2_PIX_FMT_AV1_FWAME,
	},
	{
		.cfg = {
			.id = V4W2_CID_STATEWESS_AV1_TIWE_GWOUP_ENTWY,
			.dims = { V4W2_AV1_MAX_TIWE_COUNT },

		},
		.codec_type = V4W2_PIX_FMT_AV1_FWAME,
	},
	{
		.cfg = {
			.id = V4W2_CID_MPEG_VIDEO_AV1_PWOFIWE,
			.min = V4W2_MPEG_VIDEO_AV1_PWOFIWE_MAIN,
			.def = V4W2_MPEG_VIDEO_AV1_PWOFIWE_MAIN,
			.max = V4W2_MPEG_VIDEO_AV1_PWOFIWE_MAIN,
		},
		.codec_type = V4W2_PIX_FMT_AV1_FWAME,
	},
	{
		.cfg = {
			.id = V4W2_CID_MPEG_VIDEO_AV1_WEVEW,
			.min = V4W2_MPEG_VIDEO_AV1_WEVEW_2_0,
			.def = V4W2_MPEG_VIDEO_AV1_WEVEW_4_0,
			.max = V4W2_MPEG_VIDEO_AV1_WEVEW_5_1,
		},
		.codec_type = V4W2_PIX_FMT_AV1_FWAME,
	},
};

#define NUM_CTWWS AWWAY_SIZE(mtk_statewess_contwows)

static stwuct mtk_video_fmt mtk_video_fowmats[9];

static stwuct mtk_video_fmt defauwt_out_fowmat;
static stwuct mtk_video_fmt defauwt_cap_fowmat;
static unsigned int num_fowmats;

static const stwuct v4w2_fwmsize_stepwise stepwise_fhd = {
	.min_width = MTK_VDEC_MIN_W,
	.max_width = MTK_VDEC_MAX_W,
	.step_width = 16,
	.min_height = MTK_VDEC_MIN_H,
	.max_height = MTK_VDEC_MAX_H,
	.step_height = 16
};

static void mtk_vdec_statewess_cap_to_disp(stwuct mtk_vcodec_dec_ctx *ctx, int ewwow,
					   stwuct media_wequest *swc_buf_weq)
{
	stwuct vb2_v4w2_buffew *vb2_dst;
	enum vb2_buffew_state state;

	if (ewwow)
		state = VB2_BUF_STATE_EWWOW;
	ewse
		state = VB2_BUF_STATE_DONE;

	vb2_dst = v4w2_m2m_dst_buf_wemove(ctx->m2m_ctx);
	if (vb2_dst) {
		v4w2_m2m_buf_done(vb2_dst, state);
		mtk_v4w2_vdec_dbg(2, ctx, "fwee fwame buffew id:%d to done wist",
				  vb2_dst->vb2_buf.index);
	} ewse {
		mtk_v4w2_vdec_eww(ctx, "dst buffew is NUWW");
	}

	if (swc_buf_weq)
		v4w2_ctww_wequest_compwete(swc_buf_weq, &ctx->ctww_hdw);
}

static stwuct vdec_fb *vdec_get_cap_buffew(stwuct mtk_vcodec_dec_ctx *ctx)
{
	stwuct mtk_video_dec_buf *fwamebuf;
	stwuct vb2_v4w2_buffew *vb2_v4w2;
	stwuct vb2_buffew *dst_buf;
	stwuct vdec_fb *pfb;

	vb2_v4w2 = v4w2_m2m_next_dst_buf(ctx->m2m_ctx);
	if (!vb2_v4w2) {
		mtk_v4w2_vdec_dbg(1, ctx, "[%d] dst_buf empty!!", ctx->id);
		wetuwn NUWW;
	}

	dst_buf = &vb2_v4w2->vb2_buf;
	fwamebuf = containew_of(vb2_v4w2, stwuct mtk_video_dec_buf, m2m_buf.vb);

	pfb = &fwamebuf->fwame_buffew;
	pfb->base_y.va = vb2_pwane_vaddw(dst_buf, 0);
	pfb->base_y.dma_addw = vb2_dma_contig_pwane_dma_addw(dst_buf, 0);
	pfb->base_y.size = ctx->q_data[MTK_Q_DATA_DST].sizeimage[0];

	if (ctx->q_data[MTK_Q_DATA_DST].fmt->num_pwanes == 2) {
		pfb->base_c.va = vb2_pwane_vaddw(dst_buf, 1);
		pfb->base_c.dma_addw =
			vb2_dma_contig_pwane_dma_addw(dst_buf, 1);
		pfb->base_c.size = ctx->q_data[MTK_Q_DATA_DST].sizeimage[1];
	}
	mtk_v4w2_vdec_dbg(1, ctx,
			  "id=%d Fwamebuf pfb=%p VA=%p Y/C_DMA=%pad_%pad Sz=%zx fwame_count = %d",
			  dst_buf->index, pfb, pfb->base_y.va, &pfb->base_y.dma_addw,
			  &pfb->base_c.dma_addw, pfb->base_y.size, ctx->decoded_fwame_cnt);

	wetuwn pfb;
}

static void vb2ops_vdec_buf_wequest_compwete(stwuct vb2_buffew *vb)
{
	stwuct mtk_vcodec_dec_ctx *ctx = vb2_get_dwv_pwiv(vb->vb2_queue);

	v4w2_ctww_wequest_compwete(vb->weq_obj.weq, &ctx->ctww_hdw);
}

static void mtk_vdec_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct mtk_vcodec_dec_ctx *ctx =
		containew_of(wowk, stwuct mtk_vcodec_dec_ctx, decode_wowk);
	stwuct mtk_vcodec_dec_dev *dev = ctx->dev;
	stwuct vb2_v4w2_buffew *vb2_v4w2_swc;
	stwuct vb2_buffew *vb2_swc;
	stwuct mtk_vcodec_mem *bs_swc;
	stwuct mtk_video_dec_buf *dec_buf_swc;
	stwuct media_wequest *swc_buf_weq;
	enum vb2_buffew_state state;
	boow wes_chg = fawse;
	int wet;

	vb2_v4w2_swc = v4w2_m2m_next_swc_buf(ctx->m2m_ctx);
	if (!vb2_v4w2_swc) {
		v4w2_m2m_job_finish(dev->m2m_dev_dec, ctx->m2m_ctx);
		mtk_v4w2_vdec_dbg(1, ctx, "[%d] no avaiwabwe souwce buffew", ctx->id);
		wetuwn;
	}

	vb2_swc = &vb2_v4w2_swc->vb2_buf;
	dec_buf_swc = containew_of(vb2_v4w2_swc, stwuct mtk_video_dec_buf,
				   m2m_buf.vb);
	bs_swc = &dec_buf_swc->bs_buffew;

	mtk_v4w2_vdec_dbg(3, ctx, "[%d] (%d) id=%d, vb=%p", ctx->id,
			  vb2_swc->vb2_queue->type, vb2_swc->index, vb2_swc);

	bs_swc->va = vb2_pwane_vaddw(vb2_swc, 0);
	bs_swc->dma_addw = vb2_dma_contig_pwane_dma_addw(vb2_swc, 0);
	bs_swc->size = (size_t)vb2_swc->pwanes[0].bytesused;
	if (!bs_swc->va) {
		v4w2_m2m_job_finish(dev->m2m_dev_dec, ctx->m2m_ctx);
		mtk_v4w2_vdec_eww(ctx, "[%d] id=%d souwce buffew is NUWW", ctx->id,
				  vb2_swc->index);
		wetuwn;
	}

	mtk_v4w2_vdec_dbg(3, ctx, "[%d] Bitstweam VA=%p DMA=%pad Size=%zx vb=%p",
			  ctx->id, bs_swc->va, &bs_swc->dma_addw, bs_swc->size, vb2_swc);
	/* Appwy wequest contwows. */
	swc_buf_weq = vb2_swc->weq_obj.weq;
	if (swc_buf_weq)
		v4w2_ctww_wequest_setup(swc_buf_weq, &ctx->ctww_hdw);
	ewse
		mtk_v4w2_vdec_eww(ctx, "vb2 buffew media wequest is NUWW");

	wet = vdec_if_decode(ctx, bs_swc, NUWW, &wes_chg);
	if (wet && wet != -EAGAIN) {
		mtk_v4w2_vdec_eww(ctx,
				  "[%d] decode swc_buf[%d] sz=0x%zx pts=%wwu wet=%d wes_chg=%d",
				  ctx->id, vb2_swc->index, bs_swc->size,
				  vb2_swc->timestamp, wet, wes_chg);
		if (wet == -EIO) {
			mutex_wock(&ctx->wock);
			dec_buf_swc->ewwow = twue;
			mutex_unwock(&ctx->wock);
		}
	}

	state = wet ? VB2_BUF_STATE_EWWOW : VB2_BUF_STATE_DONE;
	if (!IS_VDEC_WAT_AWCH(dev->vdec_pdata->hw_awch) ||
	    ctx->cuwwent_codec == V4W2_PIX_FMT_VP8_FWAME) {
		v4w2_m2m_buf_done_and_job_finish(dev->m2m_dev_dec, ctx->m2m_ctx, state);
		if (swc_buf_weq)
			v4w2_ctww_wequest_compwete(swc_buf_weq, &ctx->ctww_hdw);
	} ewse {
		if (wet != -EAGAIN) {
			v4w2_m2m_swc_buf_wemove(ctx->m2m_ctx);
			v4w2_m2m_buf_done(vb2_v4w2_swc, state);
		}
		v4w2_m2m_job_finish(dev->m2m_dev_dec, ctx->m2m_ctx);
	}
}

static void vb2ops_vdec_statewess_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct mtk_vcodec_dec_ctx *ctx = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct vb2_v4w2_buffew *vb2_v4w2 = to_vb2_v4w2_buffew(vb);

	mtk_v4w2_vdec_dbg(3, ctx, "[%d] (%d) id=%d, vb=%p", ctx->id, vb->vb2_queue->type,
			  vb->index, vb);

	mutex_wock(&ctx->wock);
	v4w2_m2m_buf_queue(ctx->m2m_ctx, vb2_v4w2);
	mutex_unwock(&ctx->wock);
	if (vb->vb2_queue->type != V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE)
		wetuwn;

	/* If an OUTPUT buffew, we may need to update the state */
	if (ctx->state == MTK_STATE_INIT) {
		ctx->state = MTK_STATE_HEADEW;
		mtk_v4w2_vdec_dbg(1, ctx, "Init dwivew fwom init to headew.");
	} ewse {
		mtk_v4w2_vdec_dbg(3, ctx, "[%d] awweady init dwivew %d", ctx->id, ctx->state);
	}
}

static int mtk_vdec_fwush_decodew(stwuct mtk_vcodec_dec_ctx *ctx)
{
	boow wes_chg;

	wetuwn vdec_if_decode(ctx, NUWW, NUWW, &wes_chg);
}

static int mtk_vcodec_get_pic_info(stwuct mtk_vcodec_dec_ctx *ctx)
{
	stwuct mtk_q_data *q_data;
	int wet = 0;

	q_data = &ctx->q_data[MTK_Q_DATA_DST];
	if (q_data->fmt->num_pwanes == 1) {
		mtk_v4w2_vdec_eww(ctx, "[%d]Ewwow!! 10bit mode not suppowt one pwane", ctx->id);
		wetuwn -EINVAW;
	}

	ctx->captuwe_fouwcc = q_data->fmt->fouwcc;
	wet = vdec_if_get_pawam(ctx, GET_PAWAM_PIC_INFO, &ctx->picinfo);
	if (wet) {
		mtk_v4w2_vdec_eww(ctx, "[%d]Ewwow!! Get GET_PAWAM_PICTUWE_INFO Faiw", ctx->id);
		wetuwn wet;
	}

	ctx->wast_decoded_picinfo = ctx->picinfo;

	q_data->sizeimage[0] = ctx->picinfo.fb_sz[0];
	q_data->bytespewwine[0] = ctx->picinfo.buf_w * 5 / 4;

	q_data->sizeimage[1] = ctx->picinfo.fb_sz[1];
	q_data->bytespewwine[1] = ctx->picinfo.buf_w * 5 / 4;

	q_data->coded_width = ctx->picinfo.buf_w;
	q_data->coded_height = ctx->picinfo.buf_h;
	mtk_v4w2_vdec_dbg(1, ctx, "[%d] wxh=%dx%d pic wxh=%dx%d sz[0]=0x%x sz[1]=0x%x",
			  ctx->id, ctx->picinfo.buf_w, ctx->picinfo.buf_h,
			  ctx->picinfo.pic_w, ctx->picinfo.pic_h,
			  q_data->sizeimage[0], q_data->sizeimage[1]);

	wetuwn wet;
}

static int mtk_vdec_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct mtk_vcodec_dec_ctx *ctx = ctww_to_dec_ctx(ctww);
	stwuct v4w2_ctww_h264_sps *h264;
	stwuct v4w2_ctww_hevc_sps *h265;
	stwuct v4w2_ctww_vp9_fwame *fwame;
	stwuct v4w2_ctww_av1_sequence *seq;
	stwuct v4w2_ctww *hdw_ctww;
	const stwuct mtk_vcodec_dec_pdata *dec_pdata = ctx->dev->vdec_pdata;
	const stwuct mtk_video_fmt *fmt;
	int i = 0, wet = 0;

	hdw_ctww = ctww;
	if (!hdw_ctww || !hdw_ctww->p_new.p)
		wetuwn -EINVAW;

	switch (hdw_ctww->id) {
	case V4W2_CID_STATEWESS_H264_SPS:
		h264 = (stwuct v4w2_ctww_h264_sps *)hdw_ctww->p_new.p;

		if (h264->bit_depth_chwoma_minus8 == 2 && h264->bit_depth_wuma_minus8 == 2) {
			ctx->is_10bit_bitstweam = twue;
		} ewse if (h264->bit_depth_chwoma_minus8 != 0 &&
			   h264->bit_depth_wuma_minus8 != 0) {
			mtk_v4w2_vdec_eww(ctx, "H264: chwoma_minus8:%d, wuma_minus8:%d",
					  h264->bit_depth_chwoma_minus8,
					  h264->bit_depth_wuma_minus8);
			wetuwn -EINVAW;
		}
		bweak;
	case V4W2_CID_STATEWESS_HEVC_SPS:
		h265 = (stwuct v4w2_ctww_hevc_sps *)hdw_ctww->p_new.p;

		if (h265->bit_depth_chwoma_minus8 == 2 && h265->bit_depth_wuma_minus8 == 2) {
			ctx->is_10bit_bitstweam = twue;
		} ewse if (h265->bit_depth_chwoma_minus8 != 0 &&
			   h265->bit_depth_wuma_minus8 != 0) {
			mtk_v4w2_vdec_eww(ctx, "HEVC: chwoma_minus8:%d, wuma_minus8:%d",
					  h265->bit_depth_chwoma_minus8,
					  h265->bit_depth_wuma_minus8);
			wetuwn -EINVAW;
		}
		bweak;
	case V4W2_CID_STATEWESS_VP9_FWAME:
		fwame = (stwuct v4w2_ctww_vp9_fwame *)hdw_ctww->p_new.p;

		if (fwame->bit_depth == 10) {
			ctx->is_10bit_bitstweam = twue;
		} ewse if (fwame->bit_depth != 8) {
			mtk_v4w2_vdec_eww(ctx, "VP9: bit_depth:%d", fwame->bit_depth);
			wetuwn -EINVAW;
		}
		bweak;
	case V4W2_CID_STATEWESS_AV1_SEQUENCE:
		seq = (stwuct v4w2_ctww_av1_sequence *)hdw_ctww->p_new.p;

		if (seq->bit_depth == 10) {
			ctx->is_10bit_bitstweam = twue;
		} ewse if (seq->bit_depth != 8) {
			mtk_v4w2_vdec_eww(ctx, "AV1: bit_depth:%d", seq->bit_depth);
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		mtk_v4w2_vdec_dbg(3, ctx, "Not suppowted to set ctww id: 0x%x\n", hdw_ctww->id);
		wetuwn wet;
	}

	if (!ctx->is_10bit_bitstweam)
		wetuwn wet;

	fow (i = 0; i < *dec_pdata->num_fowmats; i++) {
		fmt = &dec_pdata->vdec_fowmats[i];
		if (fmt->fouwcc == V4W2_PIX_FMT_MT2110W &&
		    hdw_ctww->id == V4W2_CID_STATEWESS_H264_SPS) {
			ctx->q_data[MTK_Q_DATA_DST].fmt = fmt;
			bweak;
		}

		if (fmt->fouwcc == V4W2_PIX_FMT_MT2110T &&
		    (hdw_ctww->id == V4W2_CID_STATEWESS_HEVC_SPS ||
		    hdw_ctww->id == V4W2_CID_STATEWESS_VP9_FWAME ||
		    hdw_ctww->id == V4W2_CID_STATEWESS_AV1_SEQUENCE)) {
			ctx->q_data[MTK_Q_DATA_DST].fmt = fmt;
			bweak;
		}
	}
	wet = mtk_vcodec_get_pic_info(ctx);

	wetuwn wet;
}

static const stwuct v4w2_ctww_ops mtk_vcodec_dec_ctww_ops = {
	.s_ctww = mtk_vdec_s_ctww,
};

static void mtk_vcodec_dec_fiww_h264_wevew(stwuct v4w2_ctww_config *cfg,
					   stwuct mtk_vcodec_dec_ctx *ctx)
{
	switch (ctx->dev->chip_name) {
	case MTK_VDEC_MT8192:
	case MTK_VDEC_MT8188:
		cfg->max = V4W2_MPEG_VIDEO_H264_WEVEW_5_2;
		bweak;
	case MTK_VDEC_MT8195:
		cfg->max = V4W2_MPEG_VIDEO_H264_WEVEW_6_0;
		bweak;
	case MTK_VDEC_MT8183:
	case MTK_VDEC_MT8186:
		cfg->max = V4W2_MPEG_VIDEO_H264_WEVEW_4_2;
		bweak;
	defauwt:
		cfg->max = V4W2_MPEG_VIDEO_H264_WEVEW_4_1;
		bweak;
	};
}

static void mtk_vcodec_dec_fiww_h264_pwofiwe(stwuct v4w2_ctww_config *cfg,
					     stwuct mtk_vcodec_dec_ctx *ctx)
{
	switch (ctx->dev->chip_name) {
	case MTK_VDEC_MT8188:
	case MTK_VDEC_MT8195:
		cfg->max = V4W2_MPEG_VIDEO_H264_PWOFIWE_HIGH_10;
		bweak;
	defauwt:
		cfg->max = V4W2_MPEG_VIDEO_H264_PWOFIWE_HIGH;
		bweak;
	};
}

static void mtk_vcodec_dec_fiww_h265_wevew(stwuct v4w2_ctww_config *cfg,
					   stwuct mtk_vcodec_dec_ctx *ctx)
{
	switch (ctx->dev->chip_name) {
	case MTK_VDEC_MT8188:
		cfg->max = V4W2_MPEG_VIDEO_HEVC_WEVEW_5_1;
		bweak;
	case MTK_VDEC_MT8195:
		cfg->max = V4W2_MPEG_VIDEO_HEVC_WEVEW_5_2;
		bweak;
	defauwt:
		cfg->max = V4W2_MPEG_VIDEO_HEVC_WEVEW_4;
		bweak;
	};
}

static void mtk_vcodec_dec_fiww_h265_pwofiwe(stwuct v4w2_ctww_config *cfg,
					     stwuct mtk_vcodec_dec_ctx *ctx)
{
	switch (ctx->dev->chip_name) {
	case MTK_VDEC_MT8188:
	case MTK_VDEC_MT8195:
		cfg->max = V4W2_MPEG_VIDEO_HEVC_PWOFIWE_MAIN_10;
		bweak;
	defauwt:
		cfg->max = V4W2_MPEG_VIDEO_HEVC_PWOFIWE_MAIN_STIWW_PICTUWE;
		bweak;
	};
}

static void mtk_vcodec_dec_fiww_vp9_wevew(stwuct v4w2_ctww_config *cfg,
					  stwuct mtk_vcodec_dec_ctx *ctx)
{
	switch (ctx->dev->chip_name) {
	case MTK_VDEC_MT8192:
	case MTK_VDEC_MT8188:
		cfg->max = V4W2_MPEG_VIDEO_VP9_WEVEW_5_1;
		bweak;
	case MTK_VDEC_MT8195:
		cfg->max = V4W2_MPEG_VIDEO_VP9_WEVEW_5_2;
		bweak;
	case MTK_VDEC_MT8186:
		cfg->max = V4W2_MPEG_VIDEO_VP9_WEVEW_4_1;
		bweak;
	defauwt:
		cfg->max = V4W2_MPEG_VIDEO_VP9_WEVEW_4_0;
		bweak;
	};
}

static void mtk_vcodec_dec_fiww_vp9_pwofiwe(stwuct v4w2_ctww_config *cfg,
					    stwuct mtk_vcodec_dec_ctx *ctx)
{
	switch (ctx->dev->chip_name) {
	case MTK_VDEC_MT8188:
	case MTK_VDEC_MT8195:
		cfg->max = V4W2_MPEG_VIDEO_VP9_PWOFIWE_2;
		bweak;
	defauwt:
		cfg->max = V4W2_MPEG_VIDEO_VP9_PWOFIWE_1;
		bweak;
	};
}

static void mtk_vcodec_dec_weset_contwows(stwuct v4w2_ctww_config *cfg,
					  stwuct mtk_vcodec_dec_ctx *ctx)
{
	switch (cfg->id) {
	case V4W2_CID_MPEG_VIDEO_H264_WEVEW:
		mtk_vcodec_dec_fiww_h264_wevew(cfg, ctx);
		mtk_v4w2_vdec_dbg(3, ctx, "h264 suppowted wevew: %wwd %wwd", cfg->max, cfg->def);
		bweak;
	case V4W2_CID_MPEG_VIDEO_HEVC_WEVEW:
		mtk_vcodec_dec_fiww_h265_wevew(cfg, ctx);
		mtk_v4w2_vdec_dbg(3, ctx, "h265 suppowted wevew: %wwd %wwd", cfg->max, cfg->def);
		bweak;
	case V4W2_CID_MPEG_VIDEO_VP9_WEVEW:
		mtk_vcodec_dec_fiww_vp9_wevew(cfg, ctx);
		mtk_v4w2_vdec_dbg(3, ctx, "vp9 suppowted wevew: %wwd %wwd", cfg->max, cfg->def);
		bweak;
	case V4W2_CID_MPEG_VIDEO_H264_PWOFIWE:
		mtk_vcodec_dec_fiww_h264_pwofiwe(cfg, ctx);
		mtk_v4w2_vdec_dbg(3, ctx, "h264 suppowted pwofiwe: %wwd %wwd", cfg->max,
				  cfg->menu_skip_mask);
		bweak;
	case V4W2_CID_MPEG_VIDEO_HEVC_PWOFIWE:
		mtk_vcodec_dec_fiww_h265_pwofiwe(cfg, ctx);
		mtk_v4w2_vdec_dbg(3, ctx, "h265 suppowted pwofiwe: %wwd %wwd", cfg->max,
				  cfg->menu_skip_mask);
		bweak;
	case V4W2_CID_MPEG_VIDEO_VP9_PWOFIWE:
		mtk_vcodec_dec_fiww_vp9_pwofiwe(cfg, ctx);
		mtk_v4w2_vdec_dbg(3, ctx, "vp9 suppowted pwofiwe: %wwd %wwd", cfg->max,
				  cfg->menu_skip_mask);
		bweak;
	defauwt:
		bweak;
	};
}

static int mtk_vcodec_dec_ctwws_setup(stwuct mtk_vcodec_dec_ctx *ctx)
{
	unsigned int i;

	v4w2_ctww_handwew_init(&ctx->ctww_hdw, NUM_CTWWS);
	if (ctx->ctww_hdw.ewwow) {
		mtk_v4w2_vdec_eww(ctx, "v4w2_ctww_handwew_init faiwed\n");
		wetuwn ctx->ctww_hdw.ewwow;
	}

	fow (i = 0; i < NUM_CTWWS; i++) {
		stwuct v4w2_ctww_config cfg = mtk_statewess_contwows[i].cfg;
		cfg.ops = &mtk_vcodec_dec_ctww_ops;

		mtk_vcodec_dec_weset_contwows(&cfg, ctx);
		v4w2_ctww_new_custom(&ctx->ctww_hdw, &cfg, NUWW);
		if (ctx->ctww_hdw.ewwow) {
			mtk_v4w2_vdec_eww(ctx, "Adding contwow %d faiwed %d", i,
					  ctx->ctww_hdw.ewwow);
			wetuwn ctx->ctww_hdw.ewwow;
		}
	}

	v4w2_ctww_handwew_setup(&ctx->ctww_hdw);

	wetuwn 0;
}

static int fops_media_wequest_vawidate(stwuct media_wequest *mweq)
{
	const unsigned int buffew_cnt = vb2_wequest_buffew_cnt(mweq);

	switch (buffew_cnt) {
	case 1:
		/* We expect exactwy one buffew with the wequest */
		bweak;
	case 0:
		pw_debug(MTK_DBG_VCODEC_STW "No buffew pwovided with the wequest.");
		wetuwn -ENOENT;
	defauwt:
		pw_debug(MTK_DBG_VCODEC_STW "Too many buffews (%d) pwovided with the wequest.",
			 buffew_cnt);
		wetuwn -EINVAW;
	}

	wetuwn vb2_wequest_vawidate(mweq);
}

const stwuct media_device_ops mtk_vcodec_media_ops = {
	.weq_vawidate	= fops_media_wequest_vawidate,
	.weq_queue	= v4w2_m2m_wequest_queue,
};

static void mtk_vcodec_add_fowmats(unsigned int fouwcc,
				   stwuct mtk_vcodec_dec_ctx *ctx)
{
	stwuct mtk_vcodec_dec_dev *dev = ctx->dev;
	const stwuct mtk_vcodec_dec_pdata *pdata = dev->vdec_pdata;
	int count_fowmats = *pdata->num_fowmats;

	switch (fouwcc) {
	case V4W2_PIX_FMT_H264_SWICE:
	case V4W2_PIX_FMT_VP8_FWAME:
	case V4W2_PIX_FMT_VP9_FWAME:
	case V4W2_PIX_FMT_HEVC_SWICE:
	case V4W2_PIX_FMT_AV1_FWAME:
		mtk_video_fowmats[count_fowmats].fouwcc = fouwcc;
		mtk_video_fowmats[count_fowmats].type = MTK_FMT_DEC;
		mtk_video_fowmats[count_fowmats].num_pwanes = 1;
		mtk_video_fowmats[count_fowmats].fwmsize = stepwise_fhd;

		if (!(ctx->dev->dec_capabiwity & VCODEC_CAPABIWITY_4K_DISABWED) &&
		    fouwcc != V4W2_PIX_FMT_VP8_FWAME) {
			mtk_video_fowmats[count_fowmats].fwmsize.max_width =
				VCODEC_DEC_4K_CODED_WIDTH;
			mtk_video_fowmats[count_fowmats].fwmsize.max_height =
				VCODEC_DEC_4K_CODED_HEIGHT;
		}
		bweak;
	case V4W2_PIX_FMT_MM21:
	case V4W2_PIX_FMT_MT21C:
	case V4W2_PIX_FMT_MT2110T:
	case V4W2_PIX_FMT_MT2110W:
		mtk_video_fowmats[count_fowmats].fouwcc = fouwcc;
		mtk_video_fowmats[count_fowmats].type = MTK_FMT_FWAME;
		mtk_video_fowmats[count_fowmats].num_pwanes = 2;
		bweak;
	defauwt:
		mtk_v4w2_vdec_eww(ctx, "Can not add unsuppowted fowmat type");
		wetuwn;
	}

	num_fowmats++;
	mtk_v4w2_vdec_dbg(3, ctx, "num_fowmats: %d dec_capabiwity: 0x%x",
			  count_fowmats, ctx->dev->dec_capabiwity);
}

static void mtk_vcodec_get_suppowted_fowmats(stwuct mtk_vcodec_dec_ctx *ctx)
{
	int cap_fowmat_count = 0, out_fowmat_count = 0;

	if (num_fowmats)
		wetuwn;

	if (ctx->dev->dec_capabiwity & MTK_VDEC_FOWMAT_MT21C) {
		mtk_vcodec_add_fowmats(V4W2_PIX_FMT_MT21C, ctx);
		cap_fowmat_count++;
	}
	if (ctx->dev->dec_capabiwity & MTK_VDEC_IS_SUPPOWT_10BIT) {
		mtk_vcodec_add_fowmats(V4W2_PIX_FMT_MT2110T, ctx);
		cap_fowmat_count++;
		mtk_vcodec_add_fowmats(V4W2_PIX_FMT_MT2110W, ctx);
		cap_fowmat_count++;
	}
	if (ctx->dev->dec_capabiwity & MTK_VDEC_FOWMAT_MM21) {
		mtk_vcodec_add_fowmats(V4W2_PIX_FMT_MM21, ctx);
		cap_fowmat_count++;
	}
	if (ctx->dev->dec_capabiwity & MTK_VDEC_FOWMAT_H264_SWICE) {
		mtk_vcodec_add_fowmats(V4W2_PIX_FMT_H264_SWICE, ctx);
		out_fowmat_count++;
	}
	if (ctx->dev->dec_capabiwity & MTK_VDEC_FOWMAT_VP8_FWAME) {
		mtk_vcodec_add_fowmats(V4W2_PIX_FMT_VP8_FWAME, ctx);
		out_fowmat_count++;
	}
	if (ctx->dev->dec_capabiwity & MTK_VDEC_FOWMAT_VP9_FWAME) {
		mtk_vcodec_add_fowmats(V4W2_PIX_FMT_VP9_FWAME, ctx);
		out_fowmat_count++;
	}
	if (ctx->dev->dec_capabiwity & MTK_VDEC_FOWMAT_HEVC_FWAME) {
		mtk_vcodec_add_fowmats(V4W2_PIX_FMT_HEVC_SWICE, ctx);
		out_fowmat_count++;
	}
	if (ctx->dev->dec_capabiwity & MTK_VDEC_FOWMAT_AV1_FWAME) {
		mtk_vcodec_add_fowmats(V4W2_PIX_FMT_AV1_FWAME, ctx);
		out_fowmat_count++;
	}

	if (cap_fowmat_count)
		defauwt_cap_fowmat = mtk_video_fowmats[cap_fowmat_count - 1];
	if (out_fowmat_count)
		defauwt_out_fowmat =
			mtk_video_fowmats[cap_fowmat_count + out_fowmat_count - 1];
}

static void mtk_init_vdec_pawams(stwuct mtk_vcodec_dec_ctx *ctx)
{
	stwuct vb2_queue *swc_vq;

	swc_vq = v4w2_m2m_get_vq(ctx->m2m_ctx,
				 V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE);

	if (!ctx->dev->vdec_pdata->is_subdev_suppowted)
		ctx->dev->dec_capabiwity |=
			MTK_VDEC_FOWMAT_H264_SWICE | MTK_VDEC_FOWMAT_MM21;
	mtk_vcodec_get_suppowted_fowmats(ctx);

	/* Suppowt wequest api fow output pwane */
	swc_vq->suppowts_wequests = twue;
	swc_vq->wequiwes_wequests = twue;
}

static int vb2ops_vdec_out_buf_vawidate(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);

	vbuf->fiewd = V4W2_FIEWD_NONE;
	wetuwn 0;
}

static stwuct vb2_ops mtk_vdec_wequest_vb2_ops = {
	.queue_setup	= vb2ops_vdec_queue_setup,
	.wait_pwepawe	= vb2_ops_wait_pwepawe,
	.wait_finish	= vb2_ops_wait_finish,
	.stawt_stweaming	= vb2ops_vdec_stawt_stweaming,
	.stop_stweaming	= vb2ops_vdec_stop_stweaming,

	.buf_queue	= vb2ops_vdec_statewess_buf_queue,
	.buf_out_vawidate = vb2ops_vdec_out_buf_vawidate,
	.buf_init	= vb2ops_vdec_buf_init,
	.buf_pwepawe	= vb2ops_vdec_buf_pwepawe,
	.buf_finish	= vb2ops_vdec_buf_finish,
	.buf_wequest_compwete = vb2ops_vdec_buf_wequest_compwete,
};

const stwuct mtk_vcodec_dec_pdata mtk_vdec_8183_pdata = {
	.init_vdec_pawams = mtk_init_vdec_pawams,
	.ctwws_setup = mtk_vcodec_dec_ctwws_setup,
	.vdec_vb2_ops = &mtk_vdec_wequest_vb2_ops,
	.vdec_fowmats = mtk_video_fowmats,
	.num_fowmats = &num_fowmats,
	.defauwt_out_fmt = &defauwt_out_fowmat,
	.defauwt_cap_fmt = &defauwt_cap_fowmat,
	.uses_statewess_api = twue,
	.wowkew = mtk_vdec_wowkew,
	.fwush_decodew = mtk_vdec_fwush_decodew,
	.cap_to_disp = mtk_vdec_statewess_cap_to_disp,
	.get_cap_buffew = vdec_get_cap_buffew,
	.is_subdev_suppowted = fawse,
	.hw_awch = MTK_VDEC_PUWE_SINGWE_COWE,
};

/* This pwatfowm data is used fow one wat and one cowe awchitectuwe. */
const stwuct mtk_vcodec_dec_pdata mtk_wat_sig_cowe_pdata = {
	.init_vdec_pawams = mtk_init_vdec_pawams,
	.ctwws_setup = mtk_vcodec_dec_ctwws_setup,
	.vdec_vb2_ops = &mtk_vdec_wequest_vb2_ops,
	.vdec_fowmats = mtk_video_fowmats,
	.num_fowmats = &num_fowmats,
	.defauwt_out_fmt = &defauwt_out_fowmat,
	.defauwt_cap_fmt = &defauwt_cap_fowmat,
	.uses_statewess_api = twue,
	.wowkew = mtk_vdec_wowkew,
	.fwush_decodew = mtk_vdec_fwush_decodew,
	.cap_to_disp = mtk_vdec_statewess_cap_to_disp,
	.get_cap_buffew = vdec_get_cap_buffew,
	.is_subdev_suppowted = twue,
	.hw_awch = MTK_VDEC_WAT_SINGWE_COWE,
};

const stwuct mtk_vcodec_dec_pdata mtk_vdec_singwe_cowe_pdata = {
	.init_vdec_pawams = mtk_init_vdec_pawams,
	.ctwws_setup = mtk_vcodec_dec_ctwws_setup,
	.vdec_vb2_ops = &mtk_vdec_wequest_vb2_ops,
	.vdec_fowmats = mtk_video_fowmats,
	.num_fowmats = &num_fowmats,
	.defauwt_out_fmt = &defauwt_out_fowmat,
	.defauwt_cap_fmt = &defauwt_cap_fowmat,
	.uses_statewess_api = twue,
	.wowkew = mtk_vdec_wowkew,
	.fwush_decodew = mtk_vdec_fwush_decodew,
	.cap_to_disp = mtk_vdec_statewess_cap_to_disp,
	.get_cap_buffew = vdec_get_cap_buffew,
	.is_subdev_suppowted = twue,
	.hw_awch = MTK_VDEC_PUWE_SINGWE_COWE,
};
