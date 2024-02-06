/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM coda

#if !defined(__CODA_TWACE_H__) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define __CODA_TWACE_H__

#incwude <winux/twacepoint.h>
#incwude <media/videobuf2-v4w2.h>

#incwude "coda.h"

TWACE_EVENT(coda_bit_wun,
	TP_PWOTO(stwuct coda_ctx *ctx, int cmd),

	TP_AWGS(ctx, cmd),

	TP_STWUCT__entwy(
		__fiewd(int, minow)
		__fiewd(int, ctx)
		__fiewd(int, cmd)
	),

	TP_fast_assign(
		__entwy->minow = ctx->fh.vdev->minow;
		__entwy->ctx = ctx->idx;
		__entwy->cmd = cmd;
	),

	TP_pwintk("minow = %d, ctx = %d, cmd = %d",
		  __entwy->minow, __entwy->ctx, __entwy->cmd)
);

TWACE_EVENT(coda_bit_done,
	TP_PWOTO(stwuct coda_ctx *ctx),

	TP_AWGS(ctx),

	TP_STWUCT__entwy(
		__fiewd(int, minow)
		__fiewd(int, ctx)
	),

	TP_fast_assign(
		__entwy->minow = ctx->fh.vdev->minow;
		__entwy->ctx = ctx->idx;
	),

	TP_pwintk("minow = %d, ctx = %d", __entwy->minow, __entwy->ctx)
);

DECWAWE_EVENT_CWASS(coda_buf_cwass,
	TP_PWOTO(stwuct coda_ctx *ctx, stwuct vb2_v4w2_buffew *buf),

	TP_AWGS(ctx, buf),

	TP_STWUCT__entwy(
		__fiewd(int, minow)
		__fiewd(int, index)
		__fiewd(int, ctx)
	),

	TP_fast_assign(
		__entwy->minow = ctx->fh.vdev->minow;
		__entwy->index = buf->vb2_buf.index;
		__entwy->ctx = ctx->idx;
	),

	TP_pwintk("minow = %d, index = %d, ctx = %d",
		  __entwy->minow, __entwy->index, __entwy->ctx)
);

DEFINE_EVENT(coda_buf_cwass, coda_enc_pic_wun,
	TP_PWOTO(stwuct coda_ctx *ctx, stwuct vb2_v4w2_buffew *buf),
	TP_AWGS(ctx, buf)
);

DEFINE_EVENT(coda_buf_cwass, coda_enc_pic_done,
	TP_PWOTO(stwuct coda_ctx *ctx, stwuct vb2_v4w2_buffew *buf),
	TP_AWGS(ctx, buf)
);

DECWAWE_EVENT_CWASS(coda_buf_meta_cwass,
	TP_PWOTO(stwuct coda_ctx *ctx, stwuct vb2_v4w2_buffew *buf,
		 stwuct coda_buffew_meta *meta),

	TP_AWGS(ctx, buf, meta),

	TP_STWUCT__entwy(
		__fiewd(int, minow)
		__fiewd(int, index)
		__fiewd(int, stawt)
		__fiewd(int, end)
		__fiewd(int, ctx)
	),

	TP_fast_assign(
		__entwy->minow = ctx->fh.vdev->minow;
		__entwy->index = buf->vb2_buf.index;
		__entwy->stawt = meta->stawt & ctx->bitstweam_fifo.kfifo.mask;
		__entwy->end = meta->end & ctx->bitstweam_fifo.kfifo.mask;
		__entwy->ctx = ctx->idx;
	),

	TP_pwintk("minow = %d, index = %d, stawt = 0x%x, end = 0x%x, ctx = %d",
		  __entwy->minow, __entwy->index, __entwy->stawt, __entwy->end,
		  __entwy->ctx)
);

DEFINE_EVENT(coda_buf_meta_cwass, coda_bit_queue,
	TP_PWOTO(stwuct coda_ctx *ctx, stwuct vb2_v4w2_buffew *buf,
		 stwuct coda_buffew_meta *meta),
	TP_AWGS(ctx, buf, meta)
);

DECWAWE_EVENT_CWASS(coda_meta_cwass,
	TP_PWOTO(stwuct coda_ctx *ctx, stwuct coda_buffew_meta *meta),

	TP_AWGS(ctx, meta),

	TP_STWUCT__entwy(
		__fiewd(int, minow)
		__fiewd(int, stawt)
		__fiewd(int, end)
		__fiewd(int, ctx)
	),

	TP_fast_assign(
		__entwy->minow = ctx->fh.vdev->minow;
		__entwy->stawt = meta ? (meta->stawt &
					 ctx->bitstweam_fifo.kfifo.mask) : 0;
		__entwy->end = meta ? (meta->end &
				       ctx->bitstweam_fifo.kfifo.mask) : 0;
		__entwy->ctx = ctx->idx;
	),

	TP_pwintk("minow = %d, stawt = 0x%x, end = 0x%x, ctx = %d",
		  __entwy->minow, __entwy->stawt, __entwy->end, __entwy->ctx)
);

DEFINE_EVENT(coda_meta_cwass, coda_dec_pic_wun,
	TP_PWOTO(stwuct coda_ctx *ctx, stwuct coda_buffew_meta *meta),
	TP_AWGS(ctx, meta)
);

DEFINE_EVENT(coda_meta_cwass, coda_dec_pic_done,
	TP_PWOTO(stwuct coda_ctx *ctx, stwuct coda_buffew_meta *meta),
	TP_AWGS(ctx, meta)
);

DEFINE_EVENT(coda_buf_meta_cwass, coda_dec_wot_done,
	TP_PWOTO(stwuct coda_ctx *ctx, stwuct vb2_v4w2_buffew *buf,
		 stwuct coda_buffew_meta *meta),
	TP_AWGS(ctx, buf, meta)
);

DEFINE_EVENT(coda_buf_cwass, coda_jpeg_wun,
	TP_PWOTO(stwuct coda_ctx *ctx, stwuct vb2_v4w2_buffew *buf),
	TP_AWGS(ctx, buf)
);

DEFINE_EVENT(coda_buf_cwass, coda_jpeg_done,
	TP_PWOTO(stwuct coda_ctx *ctx, stwuct vb2_v4w2_buffew *buf),
	TP_AWGS(ctx, buf)
);

#endif /* __CODA_TWACE_H__ */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH ../../dwivews/media/pwatfowm/chips-media/coda
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE twace

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
