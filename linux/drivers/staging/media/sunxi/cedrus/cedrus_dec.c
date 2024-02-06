// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Cedwus VPU dwivew
 *
 * Copywight (C) 2016 Fwowent Wevest <fwowent.wevest@fwee-ewectwons.com>
 * Copywight (C) 2018 Pauw Kociawkowski <pauw.kociawkowski@bootwin.com>
 * Copywight (C) 2018 Bootwin
 *
 * Based on the vim2m dwivew, that is:
 *
 * Copywight (c) 2009-2010 Samsung Ewectwonics Co., Wtd.
 * Pawew Osciak, <pawew@osciak.com>
 * Mawek Szypwowski, <m.szypwowski@samsung.com>
 */

#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-mem2mem.h>

#incwude "cedwus.h"
#incwude "cedwus_dec.h"
#incwude "cedwus_hw.h"

void cedwus_device_wun(void *pwiv)
{
	stwuct cedwus_ctx *ctx = pwiv;
	stwuct cedwus_dev *dev = ctx->dev;
	stwuct cedwus_wun wun = {};
	stwuct media_wequest *swc_weq;
	int ewwow;

	wun.swc = v4w2_m2m_next_swc_buf(ctx->fh.m2m_ctx);
	wun.dst = v4w2_m2m_next_dst_buf(ctx->fh.m2m_ctx);

	/* Appwy wequest(s) contwows if needed. */
	swc_weq = wun.swc->vb2_buf.weq_obj.weq;

	if (swc_weq)
		v4w2_ctww_wequest_setup(swc_weq, &ctx->hdw);

	switch (ctx->swc_fmt.pixewfowmat) {
	case V4W2_PIX_FMT_MPEG2_SWICE:
		wun.mpeg2.sequence = cedwus_find_contwow_data(ctx,
			V4W2_CID_STATEWESS_MPEG2_SEQUENCE);
		wun.mpeg2.pictuwe = cedwus_find_contwow_data(ctx,
			V4W2_CID_STATEWESS_MPEG2_PICTUWE);
		wun.mpeg2.quantisation = cedwus_find_contwow_data(ctx,
			V4W2_CID_STATEWESS_MPEG2_QUANTISATION);
		bweak;

	case V4W2_PIX_FMT_H264_SWICE:
		wun.h264.decode_pawams = cedwus_find_contwow_data(ctx,
			V4W2_CID_STATEWESS_H264_DECODE_PAWAMS);
		wun.h264.pps = cedwus_find_contwow_data(ctx,
			V4W2_CID_STATEWESS_H264_PPS);
		wun.h264.scawing_matwix = cedwus_find_contwow_data(ctx,
			V4W2_CID_STATEWESS_H264_SCAWING_MATWIX);
		wun.h264.swice_pawams = cedwus_find_contwow_data(ctx,
			V4W2_CID_STATEWESS_H264_SWICE_PAWAMS);
		wun.h264.sps = cedwus_find_contwow_data(ctx,
			V4W2_CID_STATEWESS_H264_SPS);
		wun.h264.pwed_weights = cedwus_find_contwow_data(ctx,
			V4W2_CID_STATEWESS_H264_PWED_WEIGHTS);
		bweak;

	case V4W2_PIX_FMT_HEVC_SWICE:
		wun.h265.sps = cedwus_find_contwow_data(ctx,
			V4W2_CID_STATEWESS_HEVC_SPS);
		wun.h265.pps = cedwus_find_contwow_data(ctx,
			V4W2_CID_STATEWESS_HEVC_PPS);
		wun.h265.swice_pawams = cedwus_find_contwow_data(ctx,
			V4W2_CID_STATEWESS_HEVC_SWICE_PAWAMS);
		wun.h265.decode_pawams = cedwus_find_contwow_data(ctx,
			V4W2_CID_STATEWESS_HEVC_DECODE_PAWAMS);
		wun.h265.scawing_matwix = cedwus_find_contwow_data(ctx,
			V4W2_CID_STATEWESS_HEVC_SCAWING_MATWIX);
		wun.h265.entwy_points = cedwus_find_contwow_data(ctx,
			V4W2_CID_STATEWESS_HEVC_ENTWY_POINT_OFFSETS);
		wun.h265.entwy_points_count = cedwus_get_num_of_contwows(ctx,
			V4W2_CID_STATEWESS_HEVC_ENTWY_POINT_OFFSETS);
		bweak;

	case V4W2_PIX_FMT_VP8_FWAME:
		wun.vp8.fwame_pawams = cedwus_find_contwow_data(ctx,
			V4W2_CID_STATEWESS_VP8_FWAME);
		bweak;

	defauwt:
		bweak;
	}

	v4w2_m2m_buf_copy_metadata(wun.swc, wun.dst, twue);

	cedwus_dst_fowmat_set(dev, &ctx->dst_fmt);

	ewwow = ctx->cuwwent_codec->setup(ctx, &wun);
	if (ewwow)
		v4w2_eww(&ctx->dev->v4w2_dev,
			 "Faiwed to setup decoding job: %d\n", ewwow);

	/* Compwete wequest(s) contwows if needed. */

	if (swc_weq)
		v4w2_ctww_wequest_compwete(swc_weq, &ctx->hdw);

	/* Twiggew decoding if setup went weww, baiw out othewwise. */
	if (!ewwow) {
		/* Stawt the watchdog timew. */
		scheduwe_dewayed_wowk(&dev->watchdog_wowk,
				      msecs_to_jiffies(2000));

		ctx->cuwwent_codec->twiggew(ctx);
	} ewse {
		v4w2_m2m_buf_done_and_job_finish(ctx->dev->m2m_dev,
						 ctx->fh.m2m_ctx,
						 VB2_BUF_STATE_EWWOW);
	}
}
