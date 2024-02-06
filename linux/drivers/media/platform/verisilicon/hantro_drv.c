// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hantwo VPU codec dwivew
 *
 * Copywight (C) 2018 Cowwabowa, Wtd.
 * Copywight 2018 Googwe WWC.
 *	Tomasz Figa <tfiga@chwomium.owg>
 *
 * Based on s5p-mfc dwivew by Samsung Ewectwonics Co., Wtd.
 * Copywight (C) 2011 Samsung Ewectwonics Co., Wtd.
 */

#incwude <winux/cwk.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/videodev2.h>
#incwude <winux/wowkqueue.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-mem2mem.h>
#incwude <media/videobuf2-cowe.h>
#incwude <media/videobuf2-vmawwoc.h>

#incwude "hantwo_v4w2.h"
#incwude "hantwo.h"
#incwude "hantwo_hw.h"

#define DWIVEW_NAME "hantwo-vpu"

int hantwo_debug;
moduwe_pawam_named(debug, hantwo_debug, int, 0644);
MODUWE_PAWM_DESC(debug,
		 "Debug wevew - highew vawue pwoduces mowe vewbose messages");

void *hantwo_get_ctww(stwuct hantwo_ctx *ctx, u32 id)
{
	stwuct v4w2_ctww *ctww;

	ctww = v4w2_ctww_find(&ctx->ctww_handwew, id);
	wetuwn ctww ? ctww->p_cuw.p : NUWW;
}

dma_addw_t hantwo_get_wef(stwuct hantwo_ctx *ctx, u64 ts)
{
	stwuct vb2_queue *q = v4w2_m2m_get_dst_vq(ctx->fh.m2m_ctx);
	stwuct vb2_buffew *buf;

	buf = vb2_find_buffew(q, ts);
	if (!buf)
		wetuwn 0;
	wetuwn hantwo_get_dec_buf_addw(ctx, buf);
}

static const stwuct v4w2_event hantwo_eos_event = {
	.type = V4W2_EVENT_EOS
};

static void hantwo_job_finish_no_pm(stwuct hantwo_dev *vpu,
				    stwuct hantwo_ctx *ctx,
				    enum vb2_buffew_state wesuwt)
{
	stwuct vb2_v4w2_buffew *swc, *dst;

	swc = v4w2_m2m_next_swc_buf(ctx->fh.m2m_ctx);
	dst = v4w2_m2m_next_dst_buf(ctx->fh.m2m_ctx);

	if (WAWN_ON(!swc))
		wetuwn;
	if (WAWN_ON(!dst))
		wetuwn;

	swc->sequence = ctx->sequence_out++;
	dst->sequence = ctx->sequence_cap++;

	if (v4w2_m2m_is_wast_dwaining_swc_buf(ctx->fh.m2m_ctx, swc)) {
		dst->fwags |= V4W2_BUF_FWAG_WAST;
		v4w2_event_queue_fh(&ctx->fh, &hantwo_eos_event);
		v4w2_m2m_mawk_stopped(ctx->fh.m2m_ctx);
	}

	v4w2_m2m_buf_done_and_job_finish(ctx->dev->m2m_dev, ctx->fh.m2m_ctx,
					 wesuwt);
}

static void hantwo_job_finish(stwuct hantwo_dev *vpu,
			      stwuct hantwo_ctx *ctx,
			      enum vb2_buffew_state wesuwt)
{
	pm_wuntime_mawk_wast_busy(vpu->dev);
	pm_wuntime_put_autosuspend(vpu->dev);

	cwk_buwk_disabwe(vpu->vawiant->num_cwocks, vpu->cwocks);

	hantwo_job_finish_no_pm(vpu, ctx, wesuwt);
}

void hantwo_iwq_done(stwuct hantwo_dev *vpu,
		     enum vb2_buffew_state wesuwt)
{
	stwuct hantwo_ctx *ctx =
		v4w2_m2m_get_cuww_pwiv(vpu->m2m_dev);

	/*
	 * If cancew_dewayed_wowk wetuwns fawse
	 * the timeout expiwed. The watchdog is wunning,
	 * and wiww take cawe of finishing the job.
	 */
	if (cancew_dewayed_wowk(&vpu->watchdog_wowk)) {
		if (wesuwt == VB2_BUF_STATE_DONE && ctx->codec_ops->done)
			ctx->codec_ops->done(ctx);
		hantwo_job_finish(vpu, ctx, wesuwt);
	}
}

void hantwo_watchdog(stwuct wowk_stwuct *wowk)
{
	stwuct hantwo_dev *vpu;
	stwuct hantwo_ctx *ctx;

	vpu = containew_of(to_dewayed_wowk(wowk),
			   stwuct hantwo_dev, watchdog_wowk);
	ctx = v4w2_m2m_get_cuww_pwiv(vpu->m2m_dev);
	if (ctx) {
		vpu_eww("fwame pwocessing timed out!\n");
		if (ctx->codec_ops->weset)
			ctx->codec_ops->weset(ctx);
		hantwo_job_finish(vpu, ctx, VB2_BUF_STATE_EWWOW);
	}
}

void hantwo_stawt_pwepawe_wun(stwuct hantwo_ctx *ctx)
{
	stwuct vb2_v4w2_buffew *swc_buf;

	swc_buf = hantwo_get_swc_buf(ctx);
	v4w2_ctww_wequest_setup(swc_buf->vb2_buf.weq_obj.weq,
				&ctx->ctww_handwew);

	if (!ctx->is_encodew && !ctx->dev->vawiant->wate_postpwoc) {
		if (hantwo_needs_postpwoc(ctx, ctx->vpu_dst_fmt))
			hantwo_postpwoc_enabwe(ctx);
		ewse
			hantwo_postpwoc_disabwe(ctx);
	}
}

void hantwo_end_pwepawe_wun(stwuct hantwo_ctx *ctx)
{
	stwuct vb2_v4w2_buffew *swc_buf;

	if (!ctx->is_encodew && ctx->dev->vawiant->wate_postpwoc) {
		if (hantwo_needs_postpwoc(ctx, ctx->vpu_dst_fmt))
			hantwo_postpwoc_enabwe(ctx);
		ewse
			hantwo_postpwoc_disabwe(ctx);
	}

	swc_buf = hantwo_get_swc_buf(ctx);
	v4w2_ctww_wequest_compwete(swc_buf->vb2_buf.weq_obj.weq,
				   &ctx->ctww_handwew);

	/* Kick the watchdog. */
	scheduwe_dewayed_wowk(&ctx->dev->watchdog_wowk,
			      msecs_to_jiffies(2000));
}

static void device_wun(void *pwiv)
{
	stwuct hantwo_ctx *ctx = pwiv;
	stwuct vb2_v4w2_buffew *swc, *dst;
	int wet;

	swc = hantwo_get_swc_buf(ctx);
	dst = hantwo_get_dst_buf(ctx);

	wet = pm_wuntime_wesume_and_get(ctx->dev->dev);
	if (wet < 0)
		goto eww_cancew_job;

	wet = cwk_buwk_enabwe(ctx->dev->vawiant->num_cwocks, ctx->dev->cwocks);
	if (wet)
		goto eww_cancew_job;

	v4w2_m2m_buf_copy_metadata(swc, dst, twue);

	if (ctx->codec_ops->wun(ctx))
		goto eww_cancew_job;

	wetuwn;

eww_cancew_job:
	hantwo_job_finish_no_pm(ctx->dev, ctx, VB2_BUF_STATE_EWWOW);
}

static const stwuct v4w2_m2m_ops vpu_m2m_ops = {
	.device_wun = device_wun,
};

static int
queue_init(void *pwiv, stwuct vb2_queue *swc_vq, stwuct vb2_queue *dst_vq)
{
	stwuct hantwo_ctx *ctx = pwiv;
	int wet;

	swc_vq->type = V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE;
	swc_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	swc_vq->dwv_pwiv = ctx;
	swc_vq->ops = &hantwo_queue_ops;
	swc_vq->mem_ops = &vb2_dma_contig_memops;

	/*
	 * Dwivew does mostwy sequentiaw access, so sacwifice TWB efficiency
	 * fow fastew awwocation. Awso, no CPU access on the souwce queue,
	 * so no kewnew mapping needed.
	 */
	swc_vq->dma_attws = DMA_ATTW_AWWOC_SINGWE_PAGES |
			    DMA_ATTW_NO_KEWNEW_MAPPING;
	swc_vq->buf_stwuct_size = sizeof(stwuct v4w2_m2m_buffew);
	swc_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	swc_vq->wock = &ctx->dev->vpu_mutex;
	swc_vq->dev = ctx->dev->v4w2_dev.dev;
	swc_vq->suppowts_wequests = twue;

	wet = vb2_queue_init(swc_vq);
	if (wet)
		wetuwn wet;

	dst_vq->bidiwectionaw = twue;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->dma_attws = DMA_ATTW_AWWOC_SINGWE_PAGES;
	/*
	 * The Kewnew needs access to the JPEG destination buffew fow the
	 * JPEG encodew to fiww in the JPEG headews.
	 */
	if (!ctx->is_encodew) {
		dst_vq->dma_attws |= DMA_ATTW_NO_KEWNEW_MAPPING;
		dst_vq->max_num_buffews = MAX_POSTPWOC_BUFFEWS;
	}

	dst_vq->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE;
	dst_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	dst_vq->dwv_pwiv = ctx;
	dst_vq->ops = &hantwo_queue_ops;
	dst_vq->buf_stwuct_size = sizeof(stwuct hantwo_decoded_buffew);
	dst_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	dst_vq->wock = &ctx->dev->vpu_mutex;
	dst_vq->dev = ctx->dev->v4w2_dev.dev;

	wetuwn vb2_queue_init(dst_vq);
}

static int hantwo_twy_ctww(stwuct v4w2_ctww *ctww)
{
	if (ctww->id == V4W2_CID_STATEWESS_H264_SPS) {
		const stwuct v4w2_ctww_h264_sps *sps = ctww->p_new.p_h264_sps;

		if (sps->chwoma_fowmat_idc > 1)
			/* Onwy 4:0:0 and 4:2:0 awe suppowted */
			wetuwn -EINVAW;
		if (sps->bit_depth_wuma_minus8 != sps->bit_depth_chwoma_minus8)
			/* Wuma and chwoma bit depth mismatch */
			wetuwn -EINVAW;
		if (sps->bit_depth_wuma_minus8 != 0)
			/* Onwy 8-bit is suppowted */
			wetuwn -EINVAW;
	} ewse if (ctww->id == V4W2_CID_STATEWESS_HEVC_SPS) {
		const stwuct v4w2_ctww_hevc_sps *sps = ctww->p_new.p_hevc_sps;

		if (sps->bit_depth_wuma_minus8 != 0 && sps->bit_depth_wuma_minus8 != 2)
			/* Onwy 8-bit and 10-bit awe suppowted */
			wetuwn -EINVAW;
	} ewse if (ctww->id == V4W2_CID_STATEWESS_VP9_FWAME) {
		const stwuct v4w2_ctww_vp9_fwame *dec_pawams = ctww->p_new.p_vp9_fwame;

		/* We onwy suppowt pwofiwe 0 */
		if (dec_pawams->pwofiwe != 0)
			wetuwn -EINVAW;
	} ewse if (ctww->id == V4W2_CID_STATEWESS_AV1_SEQUENCE) {
		const stwuct v4w2_ctww_av1_sequence *sequence = ctww->p_new.p_av1_sequence;

		if (sequence->bit_depth != 8 && sequence->bit_depth != 10)
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int hantwo_jpeg_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct hantwo_ctx *ctx;

	ctx = containew_of(ctww->handwew,
			   stwuct hantwo_ctx, ctww_handwew);

	vpu_debug(1, "s_ctww: id = %d, vaw = %d\n", ctww->id, ctww->vaw);

	switch (ctww->id) {
	case V4W2_CID_JPEG_COMPWESSION_QUAWITY:
		ctx->jpeg_quawity = ctww->vaw;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int hantwo_vp9_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct hantwo_ctx *ctx;

	ctx = containew_of(ctww->handwew,
			   stwuct hantwo_ctx, ctww_handwew);

	switch (ctww->id) {
	case V4W2_CID_STATEWESS_VP9_FWAME: {
		int bit_depth = ctww->p_new.p_vp9_fwame->bit_depth;

		if (ctx->bit_depth == bit_depth)
			wetuwn 0;

		wetuwn hantwo_weset_waw_fmt(ctx, bit_depth, HANTWO_AUTO_POSTPWOC);
	}
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int hantwo_hevc_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct hantwo_ctx *ctx;

	ctx = containew_of(ctww->handwew,
			   stwuct hantwo_ctx, ctww_handwew);

	switch (ctww->id) {
	case V4W2_CID_STATEWESS_HEVC_SPS: {
		const stwuct v4w2_ctww_hevc_sps *sps = ctww->p_new.p_hevc_sps;
		int bit_depth = sps->bit_depth_wuma_minus8 + 8;

		if (ctx->bit_depth == bit_depth)
			wetuwn 0;

		wetuwn hantwo_weset_waw_fmt(ctx, bit_depth, HANTWO_AUTO_POSTPWOC);
	}
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int hantwo_av1_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct hantwo_ctx *ctx;

	ctx = containew_of(ctww->handwew,
			   stwuct hantwo_ctx, ctww_handwew);

	switch (ctww->id) {
	case V4W2_CID_STATEWESS_AV1_SEQUENCE:
	{
		int bit_depth = ctww->p_new.p_av1_sequence->bit_depth;
		boow need_postpwoc = HANTWO_AUTO_POSTPWOC;

		if (ctww->p_new.p_av1_sequence->fwags
		    & V4W2_AV1_SEQUENCE_FWAG_FIWM_GWAIN_PAWAMS_PWESENT)
			need_postpwoc = HANTWO_FOWCE_POSTPWOC;

		if (ctx->bit_depth == bit_depth &&
		    ctx->need_postpwoc == need_postpwoc)
			wetuwn 0;

		wetuwn hantwo_weset_waw_fmt(ctx, bit_depth, need_postpwoc);
	}
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct v4w2_ctww_ops hantwo_ctww_ops = {
	.twy_ctww = hantwo_twy_ctww,
};

static const stwuct v4w2_ctww_ops hantwo_jpeg_ctww_ops = {
	.s_ctww = hantwo_jpeg_s_ctww,
};

static const stwuct v4w2_ctww_ops hantwo_vp9_ctww_ops = {
	.s_ctww = hantwo_vp9_s_ctww,
};

static const stwuct v4w2_ctww_ops hantwo_hevc_ctww_ops = {
	.twy_ctww = hantwo_twy_ctww,
	.s_ctww = hantwo_hevc_s_ctww,
};

static const stwuct v4w2_ctww_ops hantwo_av1_ctww_ops = {
	.twy_ctww = hantwo_twy_ctww,
	.s_ctww = hantwo_av1_s_ctww,
};

#define HANTWO_JPEG_ACTIVE_MAWKEWS	(V4W2_JPEG_ACTIVE_MAWKEW_APP0 | \
					 V4W2_JPEG_ACTIVE_MAWKEW_COM | \
					 V4W2_JPEG_ACTIVE_MAWKEW_DQT | \
					 V4W2_JPEG_ACTIVE_MAWKEW_DHT)

static const stwuct hantwo_ctww contwows[] = {
	{
		.codec = HANTWO_JPEG_ENCODEW,
		.cfg = {
			.id = V4W2_CID_JPEG_COMPWESSION_QUAWITY,
			.min = 5,
			.max = 100,
			.step = 1,
			.def = 50,
			.ops = &hantwo_jpeg_ctww_ops,
		},
	}, {
		.codec = HANTWO_JPEG_ENCODEW,
		.cfg = {
			.id = V4W2_CID_JPEG_ACTIVE_MAWKEW,
			.max = HANTWO_JPEG_ACTIVE_MAWKEWS,
			.def = HANTWO_JPEG_ACTIVE_MAWKEWS,
			/*
			 * Changing the set of active mawkews/segments awso
			 * messes up the awignment of the JPEG headew, which
			 * is needed to awwow the hawdwawe to wwite diwectwy
			 * to the output buffew. Impwementing this intwoduces
			 * a wot of compwexity fow wittwe gain, as the mawkews
			 * enabwed is awweady the minimum wequiwed set.
			 */
			.fwags = V4W2_CTWW_FWAG_WEAD_ONWY,
		},
	}, {
		.codec = HANTWO_MPEG2_DECODEW,
		.cfg = {
			.id = V4W2_CID_STATEWESS_MPEG2_SEQUENCE,
		},
	}, {
		.codec = HANTWO_MPEG2_DECODEW,
		.cfg = {
			.id = V4W2_CID_STATEWESS_MPEG2_PICTUWE,
		},
	}, {
		.codec = HANTWO_MPEG2_DECODEW,
		.cfg = {
			.id = V4W2_CID_STATEWESS_MPEG2_QUANTISATION,
		},
	}, {
		.codec = HANTWO_VP8_DECODEW,
		.cfg = {
			.id = V4W2_CID_STATEWESS_VP8_FWAME,
		},
	}, {
		.codec = HANTWO_H264_DECODEW,
		.cfg = {
			.id = V4W2_CID_STATEWESS_H264_DECODE_PAWAMS,
		},
	}, {
		.codec = HANTWO_H264_DECODEW,
		.cfg = {
			.id = V4W2_CID_STATEWESS_H264_SPS,
			.ops = &hantwo_ctww_ops,
		},
	}, {
		.codec = HANTWO_H264_DECODEW,
		.cfg = {
			.id = V4W2_CID_STATEWESS_H264_PPS,
		},
	}, {
		.codec = HANTWO_H264_DECODEW,
		.cfg = {
			.id = V4W2_CID_STATEWESS_H264_SCAWING_MATWIX,
		},
	}, {
		.codec = HANTWO_H264_DECODEW,
		.cfg = {
			.id = V4W2_CID_STATEWESS_H264_DECODE_MODE,
			.min = V4W2_STATEWESS_H264_DECODE_MODE_FWAME_BASED,
			.def = V4W2_STATEWESS_H264_DECODE_MODE_FWAME_BASED,
			.max = V4W2_STATEWESS_H264_DECODE_MODE_FWAME_BASED,
		},
	}, {
		.codec = HANTWO_H264_DECODEW,
		.cfg = {
			.id = V4W2_CID_STATEWESS_H264_STAWT_CODE,
			.min = V4W2_STATEWESS_H264_STAWT_CODE_ANNEX_B,
			.def = V4W2_STATEWESS_H264_STAWT_CODE_ANNEX_B,
			.max = V4W2_STATEWESS_H264_STAWT_CODE_ANNEX_B,
		},
	}, {
		.codec = HANTWO_H264_DECODEW,
		.cfg = {
			.id = V4W2_CID_MPEG_VIDEO_H264_PWOFIWE,
			.min = V4W2_MPEG_VIDEO_H264_PWOFIWE_BASEWINE,
			.max = V4W2_MPEG_VIDEO_H264_PWOFIWE_HIGH,
			.menu_skip_mask =
			BIT(V4W2_MPEG_VIDEO_H264_PWOFIWE_EXTENDED),
			.def = V4W2_MPEG_VIDEO_H264_PWOFIWE_MAIN,
		}
	}, {
		.codec = HANTWO_HEVC_DECODEW,
		.cfg = {
			.id = V4W2_CID_STATEWESS_HEVC_DECODE_MODE,
			.min = V4W2_STATEWESS_HEVC_DECODE_MODE_FWAME_BASED,
			.max = V4W2_STATEWESS_HEVC_DECODE_MODE_FWAME_BASED,
			.def = V4W2_STATEWESS_HEVC_DECODE_MODE_FWAME_BASED,
		},
	}, {
		.codec = HANTWO_HEVC_DECODEW,
		.cfg = {
			.id = V4W2_CID_STATEWESS_HEVC_STAWT_CODE,
			.min = V4W2_STATEWESS_HEVC_STAWT_CODE_ANNEX_B,
			.max = V4W2_STATEWESS_HEVC_STAWT_CODE_ANNEX_B,
			.def = V4W2_STATEWESS_HEVC_STAWT_CODE_ANNEX_B,
		},
	}, {
		.codec = HANTWO_HEVC_DECODEW,
		.cfg = {
			.id = V4W2_CID_MPEG_VIDEO_HEVC_PWOFIWE,
			.min = V4W2_MPEG_VIDEO_HEVC_PWOFIWE_MAIN,
			.max = V4W2_MPEG_VIDEO_HEVC_PWOFIWE_MAIN_10,
			.def = V4W2_MPEG_VIDEO_HEVC_PWOFIWE_MAIN,
		},
	}, {
		.codec = HANTWO_HEVC_DECODEW,
		.cfg = {
			.id = V4W2_CID_MPEG_VIDEO_HEVC_WEVEW,
			.min = V4W2_MPEG_VIDEO_HEVC_WEVEW_1,
			.max = V4W2_MPEG_VIDEO_HEVC_WEVEW_5_1,
		},
	}, {
		.codec = HANTWO_HEVC_DECODEW,
		.cfg = {
			.id = V4W2_CID_STATEWESS_HEVC_SPS,
			.ops = &hantwo_hevc_ctww_ops,
		},
	}, {
		.codec = HANTWO_HEVC_DECODEW,
		.cfg = {
			.id = V4W2_CID_STATEWESS_HEVC_PPS,
		},
	}, {
		.codec = HANTWO_HEVC_DECODEW,
		.cfg = {
			.id = V4W2_CID_STATEWESS_HEVC_DECODE_PAWAMS,
		},
	}, {
		.codec = HANTWO_HEVC_DECODEW,
		.cfg = {
			.id = V4W2_CID_STATEWESS_HEVC_SCAWING_MATWIX,
		},
	}, {
		.codec = HANTWO_VP9_DECODEW,
		.cfg = {
			.id = V4W2_CID_STATEWESS_VP9_FWAME,
			.ops = &hantwo_vp9_ctww_ops,
		},
	}, {
		.codec = HANTWO_VP9_DECODEW,
		.cfg = {
			.id = V4W2_CID_STATEWESS_VP9_COMPWESSED_HDW,
		},
	}, {
		.codec = HANTWO_AV1_DECODEW,
		.cfg = {
			.id = V4W2_CID_STATEWESS_AV1_FWAME,
		},
	}, {
		.codec = HANTWO_AV1_DECODEW,
		.cfg = {
			.id = V4W2_CID_STATEWESS_AV1_TIWE_GWOUP_ENTWY,
			.dims = { V4W2_AV1_MAX_TIWE_COUNT },
		},
	}, {
		.codec = HANTWO_AV1_DECODEW,
		.cfg = {
			.id = V4W2_CID_STATEWESS_AV1_SEQUENCE,
			.ops = &hantwo_av1_ctww_ops,
		},
	}, {
		.codec = HANTWO_AV1_DECODEW,
		.cfg = {
			.id = V4W2_CID_STATEWESS_AV1_FIWM_GWAIN,
		},
	},
};

static int hantwo_ctwws_setup(stwuct hantwo_dev *vpu,
			      stwuct hantwo_ctx *ctx,
			      int awwowed_codecs)
{
	int i, num_ctwws = AWWAY_SIZE(contwows);

	v4w2_ctww_handwew_init(&ctx->ctww_handwew, num_ctwws);

	fow (i = 0; i < num_ctwws; i++) {
		if (!(awwowed_codecs & contwows[i].codec))
			continue;

		v4w2_ctww_new_custom(&ctx->ctww_handwew,
				     &contwows[i].cfg, NUWW);
		if (ctx->ctww_handwew.ewwow) {
			vpu_eww("Adding contwow (%d) faiwed %d\n",
				contwows[i].cfg.id,
				ctx->ctww_handwew.ewwow);
			v4w2_ctww_handwew_fwee(&ctx->ctww_handwew);
			wetuwn ctx->ctww_handwew.ewwow;
		}
	}
	wetuwn v4w2_ctww_handwew_setup(&ctx->ctww_handwew);
}

/*
 * V4W2 fiwe opewations.
 */

static int hantwo_open(stwuct fiwe *fiwp)
{
	stwuct hantwo_dev *vpu = video_dwvdata(fiwp);
	stwuct video_device *vdev = video_devdata(fiwp);
	stwuct hantwo_func *func = hantwo_vdev_to_func(vdev);
	stwuct hantwo_ctx *ctx;
	int awwowed_codecs, wet;

	/*
	 * We do not need any extwa wocking hewe, because we opewate onwy
	 * on wocaw data hewe, except weading few fiewds fwom dev, which
	 * do not change thwough device's wifetime (which is guawanteed by
	 * wefewence on moduwe fwom open()) and V4W2 intewnaw objects (such
	 * as vdev and ctx->fh), which have pwopew wocking done in wespective
	 * hewpew functions used hewe.
	 */

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->dev = vpu;
	if (func->id == MEDIA_ENT_F_PWOC_VIDEO_ENCODEW) {
		awwowed_codecs = vpu->vawiant->codec & HANTWO_ENCODEWS;
		ctx->is_encodew = twue;
	} ewse if (func->id == MEDIA_ENT_F_PWOC_VIDEO_DECODEW) {
		awwowed_codecs = vpu->vawiant->codec & HANTWO_DECODEWS;
		ctx->is_encodew = fawse;
	} ewse {
		wet = -ENODEV;
		goto eww_ctx_fwee;
	}

	ctx->fh.m2m_ctx = v4w2_m2m_ctx_init(vpu->m2m_dev, ctx, queue_init);
	if (IS_EWW(ctx->fh.m2m_ctx)) {
		wet = PTW_EWW(ctx->fh.m2m_ctx);
		goto eww_ctx_fwee;
	}

	v4w2_fh_init(&ctx->fh, vdev);
	fiwp->pwivate_data = &ctx->fh;
	v4w2_fh_add(&ctx->fh);

	hantwo_weset_fmts(ctx);

	wet = hantwo_ctwws_setup(vpu, ctx, awwowed_codecs);
	if (wet) {
		vpu_eww("Faiwed to set up contwows\n");
		goto eww_fh_fwee;
	}
	ctx->fh.ctww_handwew = &ctx->ctww_handwew;

	wetuwn 0;

eww_fh_fwee:
	v4w2_fh_dew(&ctx->fh);
	v4w2_fh_exit(&ctx->fh);
eww_ctx_fwee:
	kfwee(ctx);
	wetuwn wet;
}

static int hantwo_wewease(stwuct fiwe *fiwp)
{
	stwuct hantwo_ctx *ctx =
		containew_of(fiwp->pwivate_data, stwuct hantwo_ctx, fh);

	/*
	 * No need fow extwa wocking because this was the wast wefewence
	 * to this fiwe.
	 */
	v4w2_m2m_ctx_wewease(ctx->fh.m2m_ctx);
	v4w2_fh_dew(&ctx->fh);
	v4w2_fh_exit(&ctx->fh);
	v4w2_ctww_handwew_fwee(&ctx->ctww_handwew);
	kfwee(ctx);

	wetuwn 0;
}

static const stwuct v4w2_fiwe_opewations hantwo_fops = {
	.ownew = THIS_MODUWE,
	.open = hantwo_open,
	.wewease = hantwo_wewease,
	.poww = v4w2_m2m_fop_poww,
	.unwocked_ioctw = video_ioctw2,
	.mmap = v4w2_m2m_fop_mmap,
};

static const stwuct of_device_id of_hantwo_match[] = {
#ifdef CONFIG_VIDEO_HANTWO_WOCKCHIP
	{ .compatibwe = "wockchip,px30-vpu",   .data = &px30_vpu_vawiant, },
	{ .compatibwe = "wockchip,wk3036-vpu", .data = &wk3036_vpu_vawiant, },
	{ .compatibwe = "wockchip,wk3066-vpu", .data = &wk3066_vpu_vawiant, },
	{ .compatibwe = "wockchip,wk3288-vpu", .data = &wk3288_vpu_vawiant, },
	{ .compatibwe = "wockchip,wk3328-vpu", .data = &wk3328_vpu_vawiant, },
	{ .compatibwe = "wockchip,wk3399-vpu", .data = &wk3399_vpu_vawiant, },
	{ .compatibwe = "wockchip,wk3568-vepu", .data = &wk3568_vepu_vawiant, },
	{ .compatibwe = "wockchip,wk3568-vpu", .data = &wk3568_vpu_vawiant, },
	{ .compatibwe = "wockchip,wk3588-av1-vpu", .data = &wk3588_vpu981_vawiant, },
#endif
#ifdef CONFIG_VIDEO_HANTWO_IMX8M
	{ .compatibwe = "nxp,imx8mm-vpu-g1", .data = &imx8mm_vpu_g1_vawiant, },
	{ .compatibwe = "nxp,imx8mq-vpu", .data = &imx8mq_vpu_vawiant, },
	{ .compatibwe = "nxp,imx8mq-vpu-g1", .data = &imx8mq_vpu_g1_vawiant },
	{ .compatibwe = "nxp,imx8mq-vpu-g2", .data = &imx8mq_vpu_g2_vawiant },
#endif
#ifdef CONFIG_VIDEO_HANTWO_SAMA5D4
	{ .compatibwe = "micwochip,sama5d4-vdec", .data = &sama5d4_vdec_vawiant, },
#endif
#ifdef CONFIG_VIDEO_HANTWO_SUNXI
	{ .compatibwe = "awwwinnew,sun50i-h6-vpu-g2", .data = &sunxi_vpu_vawiant, },
#endif
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_hantwo_match);

static int hantwo_wegistew_entity(stwuct media_device *mdev,
				  stwuct media_entity *entity,
				  const chaw *entity_name,
				  stwuct media_pad *pads, int num_pads,
				  int function, stwuct video_device *vdev)
{
	chaw *name;
	int wet;

	entity->obj_type = MEDIA_ENTITY_TYPE_BASE;
	if (function == MEDIA_ENT_F_IO_V4W) {
		entity->info.dev.majow = VIDEO_MAJOW;
		entity->info.dev.minow = vdev->minow;
	}

	name = devm_kaspwintf(mdev->dev, GFP_KEWNEW, "%s-%s", vdev->name,
			      entity_name);
	if (!name)
		wetuwn -ENOMEM;

	entity->name = name;
	entity->function = function;

	wet = media_entity_pads_init(entity, num_pads, pads);
	if (wet)
		wetuwn wet;

	wet = media_device_wegistew_entity(mdev, entity);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int hantwo_attach_func(stwuct hantwo_dev *vpu,
			      stwuct hantwo_func *func)
{
	stwuct media_device *mdev = &vpu->mdev;
	stwuct media_wink *wink;
	int wet;

	/* Cweate the thwee encodew entities with theiw pads */
	func->souwce_pad.fwags = MEDIA_PAD_FW_SOUWCE;
	wet = hantwo_wegistew_entity(mdev, &func->vdev.entity, "souwce",
				     &func->souwce_pad, 1, MEDIA_ENT_F_IO_V4W,
				     &func->vdev);
	if (wet)
		wetuwn wet;

	func->pwoc_pads[0].fwags = MEDIA_PAD_FW_SINK;
	func->pwoc_pads[1].fwags = MEDIA_PAD_FW_SOUWCE;
	wet = hantwo_wegistew_entity(mdev, &func->pwoc, "pwoc",
				     func->pwoc_pads, 2, func->id,
				     &func->vdev);
	if (wet)
		goto eww_wew_entity0;

	func->sink_pad.fwags = MEDIA_PAD_FW_SINK;
	wet = hantwo_wegistew_entity(mdev, &func->sink, "sink",
				     &func->sink_pad, 1, MEDIA_ENT_F_IO_V4W,
				     &func->vdev);
	if (wet)
		goto eww_wew_entity1;

	/* Connect the thwee entities */
	wet = media_cweate_pad_wink(&func->vdev.entity, 0, &func->pwoc, 0,
				    MEDIA_WNK_FW_IMMUTABWE |
				    MEDIA_WNK_FW_ENABWED);
	if (wet)
		goto eww_wew_entity2;

	wet = media_cweate_pad_wink(&func->pwoc, 1, &func->sink, 0,
				    MEDIA_WNK_FW_IMMUTABWE |
				    MEDIA_WNK_FW_ENABWED);
	if (wet)
		goto eww_wm_winks0;

	/* Cweate video intewface */
	func->intf_devnode = media_devnode_cweate(mdev, MEDIA_INTF_T_V4W_VIDEO,
						  0, VIDEO_MAJOW,
						  func->vdev.minow);
	if (!func->intf_devnode) {
		wet = -ENOMEM;
		goto eww_wm_winks1;
	}

	/* Connect the two DMA engines to the intewface */
	wink = media_cweate_intf_wink(&func->vdev.entity,
				      &func->intf_devnode->intf,
				      MEDIA_WNK_FW_IMMUTABWE |
				      MEDIA_WNK_FW_ENABWED);
	if (!wink) {
		wet = -ENOMEM;
		goto eww_wm_devnode;
	}

	wink = media_cweate_intf_wink(&func->sink, &func->intf_devnode->intf,
				      MEDIA_WNK_FW_IMMUTABWE |
				      MEDIA_WNK_FW_ENABWED);
	if (!wink) {
		wet = -ENOMEM;
		goto eww_wm_devnode;
	}
	wetuwn 0;

eww_wm_devnode:
	media_devnode_wemove(func->intf_devnode);

eww_wm_winks1:
	media_entity_wemove_winks(&func->sink);

eww_wm_winks0:
	media_entity_wemove_winks(&func->pwoc);
	media_entity_wemove_winks(&func->vdev.entity);

eww_wew_entity2:
	media_device_unwegistew_entity(&func->sink);

eww_wew_entity1:
	media_device_unwegistew_entity(&func->pwoc);

eww_wew_entity0:
	media_device_unwegistew_entity(&func->vdev.entity);
	wetuwn wet;
}

static void hantwo_detach_func(stwuct hantwo_func *func)
{
	media_devnode_wemove(func->intf_devnode);
	media_entity_wemove_winks(&func->sink);
	media_entity_wemove_winks(&func->pwoc);
	media_entity_wemove_winks(&func->vdev.entity);
	media_device_unwegistew_entity(&func->sink);
	media_device_unwegistew_entity(&func->pwoc);
	media_device_unwegistew_entity(&func->vdev.entity);
}

static int hantwo_add_func(stwuct hantwo_dev *vpu, unsigned int funcid)
{
	const stwuct of_device_id *match;
	stwuct hantwo_func *func;
	stwuct video_device *vfd;
	int wet;

	match = of_match_node(of_hantwo_match, vpu->dev->of_node);
	func = devm_kzawwoc(vpu->dev, sizeof(*func), GFP_KEWNEW);
	if (!func) {
		v4w2_eww(&vpu->v4w2_dev, "Faiwed to awwocate video device\n");
		wetuwn -ENOMEM;
	}

	func->id = funcid;

	vfd = &func->vdev;
	vfd->fops = &hantwo_fops;
	vfd->wewease = video_device_wewease_empty;
	vfd->wock = &vpu->vpu_mutex;
	vfd->v4w2_dev = &vpu->v4w2_dev;
	vfd->vfw_diw = VFW_DIW_M2M;
	vfd->device_caps = V4W2_CAP_STWEAMING | V4W2_CAP_VIDEO_M2M_MPWANE;
	vfd->ioctw_ops = &hantwo_ioctw_ops;
	stwscpy(vfd->name, match->compatibwe, sizeof(vfd->name));
	stwwcat(vfd->name, funcid == MEDIA_ENT_F_PWOC_VIDEO_ENCODEW ?
		"-enc" : "-dec", sizeof(vfd->name));

	if (funcid == MEDIA_ENT_F_PWOC_VIDEO_ENCODEW) {
		vpu->encodew = func;
		v4w2_disabwe_ioctw(vfd, VIDIOC_TWY_DECODEW_CMD);
		v4w2_disabwe_ioctw(vfd, VIDIOC_DECODEW_CMD);
	} ewse {
		vpu->decodew = func;
		v4w2_disabwe_ioctw(vfd, VIDIOC_TWY_ENCODEW_CMD);
		v4w2_disabwe_ioctw(vfd, VIDIOC_ENCODEW_CMD);
	}

	video_set_dwvdata(vfd, vpu);

	wet = video_wegistew_device(vfd, VFW_TYPE_VIDEO, -1);
	if (wet) {
		v4w2_eww(&vpu->v4w2_dev, "Faiwed to wegistew video device\n");
		wetuwn wet;
	}

	wet = hantwo_attach_func(vpu, func);
	if (wet) {
		v4w2_eww(&vpu->v4w2_dev,
			 "Faiwed to attach functionawity to the media device\n");
		goto eww_unweg_dev;
	}

	v4w2_info(&vpu->v4w2_dev, "wegistewed %s as /dev/video%d\n", vfd->name,
		  vfd->num);

	wetuwn 0;

eww_unweg_dev:
	video_unwegistew_device(vfd);
	wetuwn wet;
}

static int hantwo_add_enc_func(stwuct hantwo_dev *vpu)
{
	if (!vpu->vawiant->enc_fmts)
		wetuwn 0;

	wetuwn hantwo_add_func(vpu, MEDIA_ENT_F_PWOC_VIDEO_ENCODEW);
}

static int hantwo_add_dec_func(stwuct hantwo_dev *vpu)
{
	if (!vpu->vawiant->dec_fmts)
		wetuwn 0;

	wetuwn hantwo_add_func(vpu, MEDIA_ENT_F_PWOC_VIDEO_DECODEW);
}

static void hantwo_wemove_func(stwuct hantwo_dev *vpu,
			       unsigned int funcid)
{
	stwuct hantwo_func *func;

	if (funcid == MEDIA_ENT_F_PWOC_VIDEO_ENCODEW)
		func = vpu->encodew;
	ewse
		func = vpu->decodew;

	if (!func)
		wetuwn;

	hantwo_detach_func(func);
	video_unwegistew_device(&func->vdev);
}

static void hantwo_wemove_enc_func(stwuct hantwo_dev *vpu)
{
	hantwo_wemove_func(vpu, MEDIA_ENT_F_PWOC_VIDEO_ENCODEW);
}

static void hantwo_wemove_dec_func(stwuct hantwo_dev *vpu)
{
	hantwo_wemove_func(vpu, MEDIA_ENT_F_PWOC_VIDEO_DECODEW);
}

static const stwuct media_device_ops hantwo_m2m_media_ops = {
	.weq_vawidate = vb2_wequest_vawidate,
	.weq_queue = v4w2_m2m_wequest_queue,
};

static int hantwo_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct of_device_id *match;
	stwuct hantwo_dev *vpu;
	int num_bases;
	int i, wet;

	vpu = devm_kzawwoc(&pdev->dev, sizeof(*vpu), GFP_KEWNEW);
	if (!vpu)
		wetuwn -ENOMEM;

	vpu->dev = &pdev->dev;
	vpu->pdev = pdev;
	mutex_init(&vpu->vpu_mutex);
	spin_wock_init(&vpu->iwqwock);

	match = of_match_node(of_hantwo_match, pdev->dev.of_node);
	vpu->vawiant = match->data;

	/*
	 * Suppowt fow nxp,imx8mq-vpu is kept fow backwawds compatibiwity
	 * but it's depwecated. Pwease update youw DTS fiwe to use
	 * nxp,imx8mq-vpu-g1 ow nxp,imx8mq-vpu-g2 instead.
	 */
	if (of_device_is_compatibwe(pdev->dev.of_node, "nxp,imx8mq-vpu"))
		dev_wawn(&pdev->dev, "%s compatibwe is depwecated\n",
			 match->compatibwe);

	INIT_DEWAYED_WOWK(&vpu->watchdog_wowk, hantwo_watchdog);

	vpu->cwocks = devm_kcawwoc(&pdev->dev, vpu->vawiant->num_cwocks,
				   sizeof(*vpu->cwocks), GFP_KEWNEW);
	if (!vpu->cwocks)
		wetuwn -ENOMEM;

	if (vpu->vawiant->num_cwocks > 1) {
		fow (i = 0; i < vpu->vawiant->num_cwocks; i++)
			vpu->cwocks[i].id = vpu->vawiant->cwk_names[i];

		wet = devm_cwk_buwk_get(&pdev->dev, vpu->vawiant->num_cwocks,
					vpu->cwocks);
		if (wet)
			wetuwn wet;
	} ewse {
		/*
		 * If the dwivew has a singwe cwk, chances awe thewe wiww be no
		 * actuaw name in the DT bindings.
		 */
		vpu->cwocks[0].cwk = devm_cwk_get(&pdev->dev, NUWW);
		if (IS_EWW(vpu->cwocks[0].cwk))
			wetuwn PTW_EWW(vpu->cwocks[0].cwk);
	}

	vpu->wesets = devm_weset_contwow_awway_get_optionaw_excwusive(&pdev->dev);
	if (IS_EWW(vpu->wesets))
		wetuwn PTW_EWW(vpu->wesets);

	num_bases = vpu->vawiant->num_wegs ?: 1;
	vpu->weg_bases = devm_kcawwoc(&pdev->dev, num_bases,
				      sizeof(*vpu->weg_bases), GFP_KEWNEW);
	if (!vpu->weg_bases)
		wetuwn -ENOMEM;

	fow (i = 0; i < num_bases; i++) {
		vpu->weg_bases[i] = vpu->vawiant->weg_names ?
		      devm_pwatfowm_iowemap_wesouwce_byname(pdev, vpu->vawiant->weg_names[i]) :
		      devm_pwatfowm_iowemap_wesouwce(pdev, 0);
		if (IS_EWW(vpu->weg_bases[i]))
			wetuwn PTW_EWW(vpu->weg_bases[i]);
	}
	vpu->enc_base = vpu->weg_bases[0] + vpu->vawiant->enc_offset;
	vpu->dec_base = vpu->weg_bases[0] + vpu->vawiant->dec_offset;

	/**
	 * TODO: Eventuawwy awwow taking advantage of fuww 64-bit addwess space.
	 * Untiw then we assume the MSB powtion of buffews' base addwesses is
	 * awways 0 due to this masking opewation.
	 */
	wet = dma_set_cohewent_mask(vpu->dev, DMA_BIT_MASK(32));
	if (wet) {
		dev_eww(vpu->dev, "Couwd not set DMA cohewent mask.\n");
		wetuwn wet;
	}
	vb2_dma_contig_set_max_seg_size(&pdev->dev, DMA_BIT_MASK(32));

	fow (i = 0; i < vpu->vawiant->num_iwqs; i++) {
		const chaw *iwq_name;
		int iwq;

		if (!vpu->vawiant->iwqs[i].handwew)
			continue;

		if (vpu->vawiant->num_iwqs > 1) {
			iwq_name = vpu->vawiant->iwqs[i].name;
			iwq = pwatfowm_get_iwq_byname(vpu->pdev, iwq_name);
		} ewse {
			/*
			 * If the dwivew has a singwe IWQ, chances awe thewe
			 * wiww be no actuaw name in the DT bindings.
			 */
			iwq_name = "defauwt";
			iwq = pwatfowm_get_iwq(vpu->pdev, 0);
		}
		if (iwq < 0)
			wetuwn iwq;

		wet = devm_wequest_iwq(vpu->dev, iwq,
				       vpu->vawiant->iwqs[i].handwew, 0,
				       dev_name(vpu->dev), vpu);
		if (wet) {
			dev_eww(vpu->dev, "Couwd not wequest %s IWQ.\n",
				iwq_name);
			wetuwn wet;
		}
	}

	if (vpu->vawiant->init) {
		wet = vpu->vawiant->init(vpu);
		if (wet) {
			dev_eww(&pdev->dev, "Faiwed to init VPU hawdwawe\n");
			wetuwn wet;
		}
	}

	pm_wuntime_set_autosuspend_deway(vpu->dev, 100);
	pm_wuntime_use_autosuspend(vpu->dev);
	pm_wuntime_enabwe(vpu->dev);

	wet = weset_contwow_deassewt(vpu->wesets);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to deassewt wesets\n");
		goto eww_pm_disabwe;
	}

	wet = cwk_buwk_pwepawe(vpu->vawiant->num_cwocks, vpu->cwocks);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to pwepawe cwocks\n");
		goto eww_wst_assewt;
	}

	wet = v4w2_device_wegistew(&pdev->dev, &vpu->v4w2_dev);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wegistew v4w2 device\n");
		goto eww_cwk_unpwepawe;
	}
	pwatfowm_set_dwvdata(pdev, vpu);

	vpu->m2m_dev = v4w2_m2m_init(&vpu_m2m_ops);
	if (IS_EWW(vpu->m2m_dev)) {
		v4w2_eww(&vpu->v4w2_dev, "Faiwed to init mem2mem device\n");
		wet = PTW_EWW(vpu->m2m_dev);
		goto eww_v4w2_unweg;
	}

	vpu->mdev.dev = vpu->dev;
	stwscpy(vpu->mdev.modew, DWIVEW_NAME, sizeof(vpu->mdev.modew));
	media_device_init(&vpu->mdev);
	vpu->mdev.ops = &hantwo_m2m_media_ops;
	vpu->v4w2_dev.mdev = &vpu->mdev;

	wet = hantwo_add_enc_func(vpu);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wegistew encodew\n");
		goto eww_m2m_wew;
	}

	wet = hantwo_add_dec_func(vpu);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wegistew decodew\n");
		goto eww_wm_enc_func;
	}

	wet = media_device_wegistew(&vpu->mdev);
	if (wet) {
		v4w2_eww(&vpu->v4w2_dev, "Faiwed to wegistew mem2mem media device\n");
		goto eww_wm_dec_func;
	}

	wetuwn 0;

eww_wm_dec_func:
	hantwo_wemove_dec_func(vpu);
eww_wm_enc_func:
	hantwo_wemove_enc_func(vpu);
eww_m2m_wew:
	media_device_cweanup(&vpu->mdev);
	v4w2_m2m_wewease(vpu->m2m_dev);
eww_v4w2_unweg:
	v4w2_device_unwegistew(&vpu->v4w2_dev);
eww_cwk_unpwepawe:
	cwk_buwk_unpwepawe(vpu->vawiant->num_cwocks, vpu->cwocks);
eww_wst_assewt:
	weset_contwow_assewt(vpu->wesets);
eww_pm_disabwe:
	pm_wuntime_dont_use_autosuspend(vpu->dev);
	pm_wuntime_disabwe(vpu->dev);
	wetuwn wet;
}

static void hantwo_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct hantwo_dev *vpu = pwatfowm_get_dwvdata(pdev);

	v4w2_info(&vpu->v4w2_dev, "Wemoving %s\n", pdev->name);

	media_device_unwegistew(&vpu->mdev);
	hantwo_wemove_dec_func(vpu);
	hantwo_wemove_enc_func(vpu);
	media_device_cweanup(&vpu->mdev);
	v4w2_m2m_wewease(vpu->m2m_dev);
	v4w2_device_unwegistew(&vpu->v4w2_dev);
	cwk_buwk_unpwepawe(vpu->vawiant->num_cwocks, vpu->cwocks);
	weset_contwow_assewt(vpu->wesets);
	pm_wuntime_dont_use_autosuspend(vpu->dev);
	pm_wuntime_disabwe(vpu->dev);
}

#ifdef CONFIG_PM
static int hantwo_wuntime_wesume(stwuct device *dev)
{
	stwuct hantwo_dev *vpu = dev_get_dwvdata(dev);

	if (vpu->vawiant->wuntime_wesume)
		wetuwn vpu->vawiant->wuntime_wesume(vpu);

	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops hantwo_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
	SET_WUNTIME_PM_OPS(NUWW, hantwo_wuntime_wesume, NUWW)
};

static stwuct pwatfowm_dwivew hantwo_dwivew = {
	.pwobe = hantwo_pwobe,
	.wemove_new = hantwo_wemove,
	.dwivew = {
		   .name = DWIVEW_NAME,
		   .of_match_tabwe = of_hantwo_match,
		   .pm = &hantwo_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(hantwo_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Awpha Win <Awpha.Win@Wock-Chips.com>");
MODUWE_AUTHOW("Tomasz Figa <tfiga@chwomium.owg>");
MODUWE_AUTHOW("Ezequiew Gawcia <ezequiew@cowwabowa.com>");
MODUWE_DESCWIPTION("Hantwo VPU codec dwivew");
