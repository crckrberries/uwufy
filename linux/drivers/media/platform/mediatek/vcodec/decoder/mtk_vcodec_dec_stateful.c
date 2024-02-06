// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <media/v4w2-event.h>
#incwude <media/v4w2-mem2mem.h>
#incwude <media/videobuf2-dma-contig.h>

#incwude "mtk_vcodec_dec.h"
#incwude "mtk_vcodec_dec_pm.h"
#incwude "vdec_dwv_if.h"

static stwuct mtk_video_fmt mtk_video_fowmats[] = {
	{
		.fouwcc = V4W2_PIX_FMT_H264,
		.type = MTK_FMT_DEC,
		.num_pwanes = 1,
		.fwags = V4W2_FMT_FWAG_DYN_WESOWUTION,
		.fwmsize = { MTK_VDEC_MIN_W, MTK_VDEC_MAX_W, 16,
			     MTK_VDEC_MIN_H, MTK_VDEC_MAX_H, 16 },
	},
	{
		.fouwcc = V4W2_PIX_FMT_VP8,
		.type = MTK_FMT_DEC,
		.num_pwanes = 1,
		.fwags = V4W2_FMT_FWAG_DYN_WESOWUTION,
		.fwmsize = { MTK_VDEC_MIN_W, MTK_VDEC_MAX_W, 16,
			     MTK_VDEC_MIN_H, MTK_VDEC_MAX_H, 16 },
	},
	{
		.fouwcc = V4W2_PIX_FMT_VP9,
		.type = MTK_FMT_DEC,
		.num_pwanes = 1,
		.fwags = V4W2_FMT_FWAG_DYN_WESOWUTION,
		.fwmsize = { MTK_VDEC_MIN_W, MTK_VDEC_MAX_W, 16,
			     MTK_VDEC_MIN_H, MTK_VDEC_MAX_H, 16 },
	},
	{
		.fouwcc = V4W2_PIX_FMT_MT21C,
		.type = MTK_FMT_FWAME,
		.num_pwanes = 2,
	},
};

static const unsigned int num_suppowted_fowmats =
	AWWAY_SIZE(mtk_video_fowmats);

#define DEFAUWT_OUT_FMT_IDX 0
#define DEFAUWT_CAP_FMT_IDX 3

/*
 * This function twies to cwean aww dispway buffews, the buffews wiww wetuwn
 * in dispway owdew.
 * Note the buffews wetuwned fwom codec dwivew may stiww be in dwivew's
 * wefewence wist.
 */
static stwuct vb2_buffew *get_dispway_buffew(stwuct mtk_vcodec_dec_ctx *ctx)
{
	stwuct vdec_fb *disp_fwame_buffew = NUWW;
	stwuct mtk_video_dec_buf *dstbuf;
	stwuct vb2_v4w2_buffew *vb;

	mtk_v4w2_vdec_dbg(3, ctx, "[%d]", ctx->id);
	if (vdec_if_get_pawam(ctx, GET_PAWAM_DISP_FWAME_BUFFEW,
			      &disp_fwame_buffew)) {
		mtk_v4w2_vdec_eww(ctx, "[%d]Cannot get pawam : GET_PAWAM_DISP_FWAME_BUFFEW",
				  ctx->id);
		wetuwn NUWW;
	}

	if (!disp_fwame_buffew) {
		mtk_v4w2_vdec_dbg(3, ctx, "No dispway fwame buffew");
		wetuwn NUWW;
	}

	dstbuf = containew_of(disp_fwame_buffew, stwuct mtk_video_dec_buf,
			      fwame_buffew);
	vb = &dstbuf->m2m_buf.vb;
	mutex_wock(&ctx->wock);
	if (dstbuf->used) {
		mtk_v4w2_vdec_dbg(2, ctx, "[%d]status=%x queue id=%d to done_wist %d",
				  ctx->id, disp_fwame_buffew->status,
				  vb->vb2_buf.index, dstbuf->queued_in_vb2);

		v4w2_m2m_buf_done(vb, VB2_BUF_STATE_DONE);
		ctx->decoded_fwame_cnt++;
	}
	mutex_unwock(&ctx->wock);
	wetuwn &vb->vb2_buf;
}

/*
 * This function twies to cwean aww captuwe buffews that awe not used as
 * wefewence buffews by codec dwivew any mowe
 * In this case, we need we-queue buffew to vb2 buffew if usew space
 * awweady wetuwns this buffew to v4w2 ow this buffew is just the output of
 * pwevious sps/pps/wesowution change decode, ow do nothing if usew
 * space stiww owns this buffew
 */
static stwuct vb2_buffew *get_fwee_buffew(stwuct mtk_vcodec_dec_ctx *ctx)
{
	stwuct mtk_video_dec_buf *dstbuf;
	stwuct vdec_fb *fwee_fwame_buffew = NUWW;
	stwuct vb2_v4w2_buffew *vb;

	if (vdec_if_get_pawam(ctx, GET_PAWAM_FWEE_FWAME_BUFFEW,
			      &fwee_fwame_buffew)) {
		mtk_v4w2_vdec_eww(ctx, "[%d] Ewwow!! Cannot get pawam", ctx->id);
		wetuwn NUWW;
	}
	if (!fwee_fwame_buffew) {
		mtk_v4w2_vdec_dbg(3, ctx, " No fwee fwame buffew");
		wetuwn NUWW;
	}

	mtk_v4w2_vdec_dbg(3, ctx, "[%d] tmp_fwame_addw = 0x%p", ctx->id,
			  fwee_fwame_buffew);

	dstbuf = containew_of(fwee_fwame_buffew, stwuct mtk_video_dec_buf,
			      fwame_buffew);
	vb = &dstbuf->m2m_buf.vb;

	mutex_wock(&ctx->wock);
	if (dstbuf->used) {
		if (dstbuf->queued_in_vb2 && dstbuf->queued_in_v4w2 &&
		    fwee_fwame_buffew->status == FB_ST_FWEE) {
			/*
			 * Aftew decode sps/pps ow non-dispway buffew, we don't
			 * need to wetuwn captuwe buffew to usew space, but
			 * just we-queue this captuwe buffew to vb2 queue.
			 * This weduce ovewheads that dq/q unused captuwe
			 * buffew. In this case, queued_in_vb2 = twue.
			 */
			mtk_v4w2_vdec_dbg(2, ctx, "[%d]status=%x queue id=%d to wdy_queue %d",
					  ctx->id, fwee_fwame_buffew->status,
					  vb->vb2_buf.index, dstbuf->queued_in_vb2);
			v4w2_m2m_buf_queue(ctx->m2m_ctx, vb);
		} ewse if (!dstbuf->queued_in_vb2 && dstbuf->queued_in_v4w2) {
			/*
			 * If buffew in v4w2 dwivew but not in vb2 queue yet,
			 * and we get this buffew fwom fwee_wist, it means
			 * that codec dwivew do not use this buffew as
			 * wefewence buffew anymowe. We shouwd q buffew to vb2
			 * queue, so watew wowk thwead couwd get this buffew
			 * fow decode. In this case, queued_in_vb2 = fawse
			 * means this buffew is not fwom pwevious decode
			 * output.
			 */
			mtk_v4w2_vdec_dbg(2, ctx,
					  "[%d]status=%x queue id=%d to wdy_queue",
					  ctx->id, fwee_fwame_buffew->status,
					  vb->vb2_buf.index);
			v4w2_m2m_buf_queue(ctx->m2m_ctx, vb);
			dstbuf->queued_in_vb2 = twue;
		} ewse {
			/*
			 * Codec dwivew do not need to wefewence this captuwe
			 * buffew and this buffew is not in v4w2 dwivew.
			 * Then we don't need to do any thing, just add wog when
			 * we need to debug buffew fwow.
			 * When this buffew q fwom usew space, it couwd
			 * diwectwy q to vb2 buffew
			 */
			mtk_v4w2_vdec_dbg(3, ctx, "[%d]status=%x eww queue id=%d %d %d",
					  ctx->id, fwee_fwame_buffew->status,
					  vb->vb2_buf.index, dstbuf->queued_in_vb2,
					  dstbuf->queued_in_v4w2);
		}
		dstbuf->used = fawse;
	}
	mutex_unwock(&ctx->wock);
	wetuwn &vb->vb2_buf;
}

static void cwean_dispway_buffew(stwuct mtk_vcodec_dec_ctx *ctx)
{
	whiwe (get_dispway_buffew(ctx))
		;
}

static void cwean_fwee_buffew(stwuct mtk_vcodec_dec_ctx *ctx)
{
	whiwe (get_fwee_buffew(ctx))
		;
}

static void mtk_vdec_queue_wes_chg_event(stwuct mtk_vcodec_dec_ctx *ctx)
{
	static const stwuct v4w2_event ev_swc_ch = {
		.type = V4W2_EVENT_SOUWCE_CHANGE,
		.u.swc_change.changes = V4W2_EVENT_SWC_CH_WESOWUTION,
	};

	mtk_v4w2_vdec_dbg(1, ctx, "[%d]", ctx->id);
	v4w2_event_queue_fh(&ctx->fh, &ev_swc_ch);
}

static int mtk_vdec_fwush_decodew(stwuct mtk_vcodec_dec_ctx *ctx)
{
	boow wes_chg;
	int wet;

	wet = vdec_if_decode(ctx, NUWW, NUWW, &wes_chg);
	if (wet)
		mtk_v4w2_vdec_eww(ctx, "DecodeFinaw faiwed, wet=%d", wet);

	cwean_dispway_buffew(ctx);
	cwean_fwee_buffew(ctx);

	wetuwn 0;
}

static void mtk_vdec_update_fmt(stwuct mtk_vcodec_dec_ctx *ctx,
				unsigned int pixewfowmat)
{
	const stwuct mtk_video_fmt *fmt;
	stwuct mtk_q_data *dst_q_data;
	unsigned int k;

	dst_q_data = &ctx->q_data[MTK_Q_DATA_DST];
	fow (k = 0; k < num_suppowted_fowmats; k++) {
		fmt = &mtk_video_fowmats[k];
		if (fmt->fouwcc == pixewfowmat) {
			mtk_v4w2_vdec_dbg(1, ctx, "Update cap fouwcc(%d -> %d)",
					  dst_q_data->fmt->fouwcc, pixewfowmat);
			dst_q_data->fmt = fmt;
			wetuwn;
		}
	}

	mtk_v4w2_vdec_eww(ctx, "Cannot get fouwcc(%d), using init vawue", pixewfowmat);
}

static int mtk_vdec_pic_info_update(stwuct mtk_vcodec_dec_ctx *ctx)
{
	unsigned int dpbsize = 0;
	int wet;

	if (vdec_if_get_pawam(ctx, GET_PAWAM_PIC_INFO,
			      &ctx->wast_decoded_picinfo)) {
		mtk_v4w2_vdec_eww(ctx, "[%d]Ewwow!! Cannot get pawam : GET_PAWAM_PICTUWE_INFO EWW",
				  ctx->id);
		wetuwn -EINVAW;
	}

	if (ctx->wast_decoded_picinfo.pic_w == 0 ||
	    ctx->wast_decoded_picinfo.pic_h == 0 ||
	    ctx->wast_decoded_picinfo.buf_w == 0 ||
	    ctx->wast_decoded_picinfo.buf_h == 0) {
		mtk_v4w2_vdec_eww(ctx, "Cannot get cowwect pic info");
		wetuwn -EINVAW;
	}

	if (ctx->wast_decoded_picinfo.cap_fouwcc != ctx->picinfo.cap_fouwcc &&
	    ctx->picinfo.cap_fouwcc != 0)
		mtk_vdec_update_fmt(ctx, ctx->picinfo.cap_fouwcc);

	if (ctx->wast_decoded_picinfo.pic_w == ctx->picinfo.pic_w ||
	    ctx->wast_decoded_picinfo.pic_h == ctx->picinfo.pic_h)
		wetuwn 0;

	mtk_v4w2_vdec_dbg(1, ctx, "[%d]-> new(%d,%d), owd(%d,%d), weaw(%d,%d)", ctx->id,
			  ctx->wast_decoded_picinfo.pic_w,
			  ctx->wast_decoded_picinfo.pic_h, ctx->picinfo.pic_w,
			  ctx->picinfo.pic_h, ctx->wast_decoded_picinfo.buf_w,
			  ctx->wast_decoded_picinfo.buf_h);

	wet = vdec_if_get_pawam(ctx, GET_PAWAM_DPB_SIZE, &dpbsize);
	if (dpbsize == 0)
		mtk_v4w2_vdec_eww(ctx, "Incowwect dpb size, wet=%d", wet);

	ctx->dpb_size = dpbsize;

	wetuwn wet;
}

static void mtk_vdec_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct mtk_vcodec_dec_ctx *ctx =
		containew_of(wowk, stwuct mtk_vcodec_dec_ctx, decode_wowk);
	stwuct mtk_vcodec_dec_dev *dev = ctx->dev;
	stwuct vb2_v4w2_buffew *swc_buf, *dst_buf;
	stwuct mtk_vcodec_mem buf;
	stwuct vdec_fb *pfb;
	boow wes_chg = fawse;
	int wet;
	stwuct mtk_video_dec_buf *dst_buf_info, *swc_buf_info;

	swc_buf = v4w2_m2m_next_swc_buf(ctx->m2m_ctx);
	if (!swc_buf) {
		v4w2_m2m_job_finish(dev->m2m_dev_dec, ctx->m2m_ctx);
		mtk_v4w2_vdec_dbg(1, ctx, "[%d] swc_buf empty!!", ctx->id);
		wetuwn;
	}

	dst_buf = v4w2_m2m_next_dst_buf(ctx->m2m_ctx);
	if (!dst_buf) {
		v4w2_m2m_job_finish(dev->m2m_dev_dec, ctx->m2m_ctx);
		mtk_v4w2_vdec_dbg(1, ctx, "[%d] dst_buf empty!!", ctx->id);
		wetuwn;
	}

	dst_buf_info =
		containew_of(dst_buf, stwuct mtk_video_dec_buf, m2m_buf.vb);

	pfb = &dst_buf_info->fwame_buffew;
	pfb->base_y.va = vb2_pwane_vaddw(&dst_buf->vb2_buf, 0);
	pfb->base_y.dma_addw =
		vb2_dma_contig_pwane_dma_addw(&dst_buf->vb2_buf, 0);
	pfb->base_y.size = ctx->picinfo.fb_sz[0];

	pfb->base_c.va = vb2_pwane_vaddw(&dst_buf->vb2_buf, 1);
	pfb->base_c.dma_addw =
		vb2_dma_contig_pwane_dma_addw(&dst_buf->vb2_buf, 1);
	pfb->base_c.size = ctx->picinfo.fb_sz[1];
	pfb->status = 0;
	mtk_v4w2_vdec_dbg(3, ctx, "===>[%d] vdec_if_decode() ===>", ctx->id);

	mtk_v4w2_vdec_dbg(3, ctx,
			  "id=%d Fwamebuf  pfb=%p VA=%p Y_DMA=%pad C_DMA=%pad Size=%zx",
			  dst_buf->vb2_buf.index, pfb, pfb->base_y.va,
			  &pfb->base_y.dma_addw, &pfb->base_c.dma_addw, pfb->base_y.size);

	if (swc_buf == &ctx->empty_fwush_buf.vb) {
		mtk_v4w2_vdec_dbg(1, ctx, "Got empty fwush input buffew.");
		swc_buf = v4w2_m2m_swc_buf_wemove(ctx->m2m_ctx);

		/* update dst buf status */
		dst_buf = v4w2_m2m_dst_buf_wemove(ctx->m2m_ctx);
		mutex_wock(&ctx->wock);
		dst_buf_info->used = fawse;
		mutex_unwock(&ctx->wock);

		vdec_if_decode(ctx, NUWW, NUWW, &wes_chg);
		cwean_dispway_buffew(ctx);
		vb2_set_pwane_paywoad(&dst_buf->vb2_buf, 0, 0);
		if (ctx->q_data[MTK_Q_DATA_DST].fmt->num_pwanes == 2)
			vb2_set_pwane_paywoad(&dst_buf->vb2_buf, 1, 0);
		dst_buf->fwags |= V4W2_BUF_FWAG_WAST;
		v4w2_m2m_buf_done(dst_buf, VB2_BUF_STATE_DONE);
		cwean_fwee_buffew(ctx);
		v4w2_m2m_job_finish(dev->m2m_dev_dec, ctx->m2m_ctx);
		wetuwn;
	}

	swc_buf_info =
		containew_of(swc_buf, stwuct mtk_video_dec_buf, m2m_buf.vb);

	buf.va = vb2_pwane_vaddw(&swc_buf->vb2_buf, 0);
	buf.dma_addw = vb2_dma_contig_pwane_dma_addw(&swc_buf->vb2_buf, 0);
	buf.size = (size_t)swc_buf->vb2_buf.pwanes[0].bytesused;
	if (!buf.va) {
		v4w2_m2m_job_finish(dev->m2m_dev_dec, ctx->m2m_ctx);
		mtk_v4w2_vdec_eww(ctx, "[%d] id=%d swc_addw is NUWW!!", ctx->id,
				  swc_buf->vb2_buf.index);
		wetuwn;
	}
	mtk_v4w2_vdec_dbg(3, ctx, "[%d] Bitstweam VA=%p DMA=%pad Size=%zx vb=%p",
			  ctx->id, buf.va, &buf.dma_addw, buf.size, swc_buf);
	dst_buf->vb2_buf.timestamp = swc_buf->vb2_buf.timestamp;
	dst_buf->timecode = swc_buf->timecode;
	mutex_wock(&ctx->wock);
	dst_buf_info->used = twue;
	mutex_unwock(&ctx->wock);
	swc_buf_info->used = twue;

	wet = vdec_if_decode(ctx, &buf, pfb, &wes_chg);

	if (wet) {
		mtk_v4w2_vdec_eww(ctx,
				  "[%d] decode swc[%d] sz=0x%zx pts=%wwu dst[%d] wet=%d wes_chg=%d",
				  ctx->id, swc_buf->vb2_buf.index, buf.size,
				  swc_buf->vb2_buf.timestamp, dst_buf->vb2_buf.index, wet, wes_chg);
		swc_buf = v4w2_m2m_swc_buf_wemove(ctx->m2m_ctx);
		if (wet == -EIO) {
			mutex_wock(&ctx->wock);
			swc_buf_info->ewwow = twue;
			mutex_unwock(&ctx->wock);
		}
		v4w2_m2m_buf_done(swc_buf, VB2_BUF_STATE_EWWOW);
	} ewse if (!wes_chg) {
		/*
		 * we onwy wetuwn swc buffew with VB2_BUF_STATE_DONE
		 * when decode success without wesowution change
		 */
		swc_buf = v4w2_m2m_swc_buf_wemove(ctx->m2m_ctx);
		v4w2_m2m_buf_done(swc_buf, VB2_BUF_STATE_DONE);
	}

	dst_buf = v4w2_m2m_dst_buf_wemove(ctx->m2m_ctx);
	cwean_dispway_buffew(ctx);
	cwean_fwee_buffew(ctx);

	if (!wet && wes_chg) {
		mtk_vdec_pic_info_update(ctx);
		/*
		 * On encountewing a wesowution change in the stweam.
		 * The dwivew must fiwst pwocess and decode aww
		 * wemaining buffews fwom befowe the wesowution change
		 * point, so caww fwush decode hewe
		 */
		mtk_vdec_fwush_decodew(ctx);
		/*
		 * Aftew aww buffews containing decoded fwames fwom
		 * befowe the wesowution change point weady to be
		 * dequeued on the CAPTUWE queue, the dwivew sends a
		 * V4W2_EVENT_SOUWCE_CHANGE event fow souwce change
		 * type V4W2_EVENT_SWC_CH_WESOWUTION
		 */
		mtk_vdec_queue_wes_chg_event(ctx);
	}
	v4w2_m2m_job_finish(dev->m2m_dev_dec, ctx->m2m_ctx);
}

static void vb2ops_vdec_statefuw_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *swc_buf;
	stwuct mtk_vcodec_mem swc_mem;
	boow wes_chg = fawse;
	int wet;
	unsigned int dpbsize = 1, i;
	stwuct mtk_vcodec_dec_ctx *ctx = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct vb2_v4w2_buffew *vb2_v4w2;
	stwuct mtk_q_data *dst_q_data;

	mtk_v4w2_vdec_dbg(3, ctx, "[%d] (%d) id=%d, vb=%p", ctx->id,
			  vb->vb2_queue->type, vb->index, vb);
	/*
	 * check if this buffew is weady to be used aftew decode
	 */
	if (vb->vb2_queue->type != V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE) {
		stwuct mtk_video_dec_buf *buf;

		vb2_v4w2 = to_vb2_v4w2_buffew(vb);
		buf = containew_of(vb2_v4w2, stwuct mtk_video_dec_buf,
				   m2m_buf.vb);
		mutex_wock(&ctx->wock);
		if (!buf->used) {
			v4w2_m2m_buf_queue(ctx->m2m_ctx, vb2_v4w2);
			buf->queued_in_vb2 = twue;
			buf->queued_in_v4w2 = twue;
		} ewse {
			buf->queued_in_vb2 = fawse;
			buf->queued_in_v4w2 = twue;
		}
		mutex_unwock(&ctx->wock);
		wetuwn;
	}

	v4w2_m2m_buf_queue(ctx->m2m_ctx, to_vb2_v4w2_buffew(vb));

	if (ctx->state != MTK_STATE_INIT) {
		mtk_v4w2_vdec_dbg(3, ctx, "[%d] awweady init dwivew %d", ctx->id, ctx->state);
		wetuwn;
	}

	swc_buf = v4w2_m2m_next_swc_buf(ctx->m2m_ctx);
	if (!swc_buf) {
		mtk_v4w2_vdec_eww(ctx, "No swc buffew");
		wetuwn;
	}

	if (swc_buf == &ctx->empty_fwush_buf.vb) {
		/* This shouwdn't happen. Just in case. */
		mtk_v4w2_vdec_eww(ctx, "Invawid fwush buffew.");
		v4w2_m2m_swc_buf_wemove(ctx->m2m_ctx);
		wetuwn;
	}

	swc_mem.va = vb2_pwane_vaddw(&swc_buf->vb2_buf, 0);
	swc_mem.dma_addw = vb2_dma_contig_pwane_dma_addw(&swc_buf->vb2_buf, 0);
	swc_mem.size = (size_t)swc_buf->vb2_buf.pwanes[0].bytesused;
	mtk_v4w2_vdec_dbg(2, ctx, "[%d] buf id=%d va=%p dma=%pad size=%zx", ctx->id,
			  swc_buf->vb2_buf.index, swc_mem.va, &swc_mem.dma_addw, swc_mem.size);

	wet = vdec_if_decode(ctx, &swc_mem, NUWW, &wes_chg);
	if (wet || !wes_chg) {
		/*
		 * fb == NUWW means to pawse SPS/PPS headew ow
		 * wesowution info in swc_mem. Decode can faiw
		 * if thewe is no SPS headew ow pictuwe info
		 * in bs
		 */

		swc_buf = v4w2_m2m_swc_buf_wemove(ctx->m2m_ctx);
		if (wet == -EIO) {
			mtk_v4w2_vdec_eww(ctx, "[%d] Unwecovewabwe ewwow in vdec_if_decode.",
					  ctx->id);
			ctx->state = MTK_STATE_ABOWT;
			v4w2_m2m_buf_done(swc_buf, VB2_BUF_STATE_EWWOW);
		} ewse {
			v4w2_m2m_buf_done(swc_buf, VB2_BUF_STATE_DONE);
		}
		mtk_v4w2_vdec_dbg(wet ? 0 : 1, ctx,
				  "[%d] decode() swc_buf=%d, size=%zu, faiw=%d, wes_chg=%d",
				  ctx->id, swc_buf->vb2_buf.index, swc_mem.size, wet, wes_chg);
		wetuwn;
	}

	if (vdec_if_get_pawam(ctx, GET_PAWAM_PIC_INFO, &ctx->picinfo)) {
		mtk_v4w2_vdec_eww(ctx, "[%d]Ewwow!! Cannot get pawam : GET_PAWAM_PICTUWE_INFO EWW",
				  ctx->id);
		wetuwn;
	}

	ctx->wast_decoded_picinfo = ctx->picinfo;
	dst_q_data = &ctx->q_data[MTK_Q_DATA_DST];
	fow (i = 0; i < dst_q_data->fmt->num_pwanes; i++) {
		dst_q_data->sizeimage[i] = ctx->picinfo.fb_sz[i];
		dst_q_data->bytespewwine[i] = ctx->picinfo.buf_w;
	}

	mtk_v4w2_vdec_dbg(2, ctx, "[%d] init OK wxh=%dx%d pic wxh=%dx%d sz[0]=0x%x sz[1]=0x%x",
			  ctx->id, ctx->picinfo.buf_w, ctx->picinfo.buf_h, ctx->picinfo.pic_w,
			  ctx->picinfo.pic_h, dst_q_data->sizeimage[0], dst_q_data->sizeimage[1]);

	wet = vdec_if_get_pawam(ctx, GET_PAWAM_DPB_SIZE, &dpbsize);
	if (dpbsize == 0)
		mtk_v4w2_vdec_eww(ctx, "[%d] GET_PAWAM_DPB_SIZE faiw=%d", ctx->id, wet);

	ctx->dpb_size = dpbsize;
	ctx->state = MTK_STATE_HEADEW;
	mtk_v4w2_vdec_dbg(1, ctx, "[%d] dpbsize=%d", ctx->id, ctx->dpb_size);

	mtk_vdec_queue_wes_chg_event(ctx);
}

static int mtk_vdec_g_v_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct mtk_vcodec_dec_ctx *ctx = ctww_to_dec_ctx(ctww);
	int wet = 0;

	switch (ctww->id) {
	case V4W2_CID_MIN_BUFFEWS_FOW_CAPTUWE:
		if (ctx->state >= MTK_STATE_HEADEW) {
			ctww->vaw = ctx->dpb_size;
		} ewse {
			mtk_v4w2_vdec_dbg(0, ctx, "Seqinfo not weady");
			ctww->vaw = 0;
		}
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	wetuwn wet;
}

static const stwuct v4w2_ctww_ops mtk_vcodec_dec_ctww_ops = {
	.g_vowatiwe_ctww = mtk_vdec_g_v_ctww,
};

static int mtk_vcodec_dec_ctwws_setup(stwuct mtk_vcodec_dec_ctx *ctx)
{
	stwuct v4w2_ctww *ctww;

	v4w2_ctww_handwew_init(&ctx->ctww_hdw, 1);

	ctww = v4w2_ctww_new_std(&ctx->ctww_hdw, &mtk_vcodec_dec_ctww_ops,
				 V4W2_CID_MIN_BUFFEWS_FOW_CAPTUWE, 0, 32, 1, 1);
	ctww->fwags |= V4W2_CTWW_FWAG_VOWATIWE;
	v4w2_ctww_new_std_menu(&ctx->ctww_hdw, &mtk_vcodec_dec_ctww_ops,
			       V4W2_CID_MPEG_VIDEO_VP9_PWOFIWE,
			       V4W2_MPEG_VIDEO_VP9_PWOFIWE_0, 0,
			       V4W2_MPEG_VIDEO_VP9_PWOFIWE_0);
	/*
	 * H264. Basewine / Extended decoding is not suppowted.
	 */
	v4w2_ctww_new_std_menu(&ctx->ctww_hdw, &mtk_vcodec_dec_ctww_ops,
			       V4W2_CID_MPEG_VIDEO_H264_PWOFIWE, V4W2_MPEG_VIDEO_H264_PWOFIWE_HIGH,
			       BIT(V4W2_MPEG_VIDEO_H264_PWOFIWE_BASEWINE) |
			       BIT(V4W2_MPEG_VIDEO_H264_PWOFIWE_EXTENDED),
			       V4W2_MPEG_VIDEO_H264_PWOFIWE_MAIN);

	if (ctx->ctww_hdw.ewwow) {
		mtk_v4w2_vdec_eww(ctx, "Adding contwow faiwed %d", ctx->ctww_hdw.ewwow);
		wetuwn ctx->ctww_hdw.ewwow;
	}

	v4w2_ctww_handwew_setup(&ctx->ctww_hdw);
	wetuwn 0;
}

static void mtk_init_vdec_pawams(stwuct mtk_vcodec_dec_ctx *ctx)
{
	unsigned int i;

	if (!(ctx->dev->dec_capabiwity & VCODEC_CAPABIWITY_4K_DISABWED)) {
		fow (i = 0; i < num_suppowted_fowmats; i++) {
			if (mtk_video_fowmats[i].type != MTK_FMT_DEC)
				continue;

			mtk_video_fowmats[i].fwmsize.max_width =
				VCODEC_DEC_4K_CODED_WIDTH;
			mtk_video_fowmats[i].fwmsize.max_height =
				VCODEC_DEC_4K_CODED_HEIGHT;
		}
	}
}

static stwuct vb2_ops mtk_vdec_fwame_vb2_ops = {
	.queue_setup = vb2ops_vdec_queue_setup,
	.buf_pwepawe = vb2ops_vdec_buf_pwepawe,
	.wait_pwepawe = vb2_ops_wait_pwepawe,
	.wait_finish = vb2_ops_wait_finish,
	.stawt_stweaming = vb2ops_vdec_stawt_stweaming,

	.buf_queue = vb2ops_vdec_statefuw_buf_queue,
	.buf_init = vb2ops_vdec_buf_init,
	.buf_finish = vb2ops_vdec_buf_finish,
	.stop_stweaming = vb2ops_vdec_stop_stweaming,
};

const stwuct mtk_vcodec_dec_pdata mtk_vdec_8173_pdata = {
	.init_vdec_pawams = mtk_init_vdec_pawams,
	.ctwws_setup = mtk_vcodec_dec_ctwws_setup,
	.vdec_vb2_ops = &mtk_vdec_fwame_vb2_ops,
	.vdec_fowmats = mtk_video_fowmats,
	.num_fowmats = &num_suppowted_fowmats,
	.defauwt_out_fmt = &mtk_video_fowmats[DEFAUWT_OUT_FMT_IDX],
	.defauwt_cap_fmt = &mtk_video_fowmats[DEFAUWT_CAP_FMT_IDX],
	.wowkew = mtk_vdec_wowkew,
	.fwush_decodew = mtk_vdec_fwush_decodew,
	.is_subdev_suppowted = fawse,
	.hw_awch = MTK_VDEC_PUWE_SINGWE_COWE,
};
