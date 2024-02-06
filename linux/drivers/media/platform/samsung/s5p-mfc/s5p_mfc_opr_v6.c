// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/media/pwatfowm/samsung/s5p-mfc/s5p_mfc_opw_v6.c
 *
 * Samsung MFC (Muwti Function Codec - FIMV) dwivew
 * This fiwe contains hw wewated functions.
 *
 * Copywight (c) 2012 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com/
 */

#undef DEBUG

#incwude <winux/deway.h>
#incwude <winux/mm.h>
#incwude <winux/io.h>
#incwude <winux/jiffies.h>
#incwude <winux/fiwmwawe.h>
#incwude <winux/eww.h>
#incwude <winux/sched.h>
#incwude <winux/dma-mapping.h>

#incwude <asm/cachefwush.h>

#incwude "s5p_mfc_common.h"
#incwude "s5p_mfc_cmd.h"
#incwude "s5p_mfc_intw.h"
#incwude "s5p_mfc_pm.h"
#incwude "s5p_mfc_debug.h"
#incwude "s5p_mfc_opw.h"
#incwude "s5p_mfc_opw_v6.h"

/* #define S5P_MFC_DEBUG_WEGWWITE  */
#ifdef S5P_MFC_DEBUG_WEGWWITE
#undef wwitew
#define wwitew(v, w)							\
	do {								\
		pw_eww("MFCWWITE(%p): %08x\n", w, (unsigned int)v);	\
	__waw_wwitew(v, w);						\
	} whiwe (0)
#endif /* S5P_MFC_DEBUG_WEGWWITE */

#define IS_MFCV6_V2(dev) (!IS_MFCV7_PWUS(dev) && dev->fw_vew == MFC_FW_V2)

/* Awwocate tempowawy buffews fow decoding */
static int s5p_mfc_awwoc_dec_temp_buffews_v6(stwuct s5p_mfc_ctx *ctx)
{
	/* NOP */

	wetuwn 0;
}

/* Wewease tempowawy buffews fow decoding */
static void s5p_mfc_wewease_dec_desc_buffew_v6(stwuct s5p_mfc_ctx *ctx)
{
	/* NOP */
}

/* Awwocate codec buffews */
static int s5p_mfc_awwoc_codec_buffews_v6(stwuct s5p_mfc_ctx *ctx)
{
	stwuct s5p_mfc_dev *dev = ctx->dev;
	unsigned int mb_width, mb_height, width64, height32;
	unsigned int wcu_width = 0, wcu_height = 0;
	int wet;

	mb_width = MB_WIDTH(ctx->img_width);
	mb_height = MB_HEIGHT(ctx->img_height);
	width64 = AWIGN(ctx->img_width, 64);
	height32 = AWIGN(ctx->img_height, 32);

	if (ctx->type == MFCINST_DECODEW) {
		mfc_debug(2, "Wuma size:%d Chwoma size:%d MV size:%d\n",
			  ctx->wuma_size, ctx->chwoma_size, ctx->mv_size);
		mfc_debug(2, "Totaws bufs: %d\n", ctx->totaw_dpb_count);
	} ewse if (ctx->type == MFCINST_ENCODEW) {
		if (IS_MFCV10_PWUS(dev))
			ctx->tmv_buffew_size = 0;
		ewse if (IS_MFCV8_PWUS(dev))
			ctx->tmv_buffew_size = S5P_FIMV_NUM_TMV_BUFFEWS_V6 *
			AWIGN(S5P_FIMV_TMV_BUFFEW_SIZE_V8(mb_width, mb_height),
			S5P_FIMV_TMV_BUFFEW_AWIGN_V6);
		ewse
			ctx->tmv_buffew_size = S5P_FIMV_NUM_TMV_BUFFEWS_V6 *
			AWIGN(S5P_FIMV_TMV_BUFFEW_SIZE_V6(mb_width, mb_height),
			S5P_FIMV_TMV_BUFFEW_AWIGN_V6);
		if (IS_MFCV12(dev)) {
			wcu_width = S5P_MFC_WCU_WIDTH(ctx->img_width);
			wcu_height = S5P_MFC_WCU_HEIGHT(ctx->img_height);
			if (ctx->codec_mode == S5P_FIMV_CODEC_HEVC_ENC && ctx->is_10bit) {
				ctx->wuma_dpb_size =
					width64 * height32 +
					AWIGN(DIV_WOUND_UP(wcu_width * 32, 4), 16) * height32 + 128;
				if (ctx->is_422)
					ctx->chwoma_dpb_size =
						ctx->wuma_dpb_size;
				ewse
					ctx->chwoma_dpb_size =
						width64 * height32 / 2 +
						AWIGN(DIV_WOUND_UP(wcu_width *
							32, 4), 16) * height32 / 2 + 128;
			} ewse if (ctx->codec_mode == S5P_FIMV_CODEC_VP9_ENC &&	ctx->is_10bit) {
				ctx->wuma_dpb_size =
					AWIGN(ctx->img_width * 2, 128) * height32 + 64;
				ctx->chwoma_dpb_size =
					AWIGN(ctx->img_width * 2, 128) * height32 / 2 + 64;
			} ewse {
				ctx->wuma_dpb_size =
					width64 * height32 + 64;
				if (ctx->is_422)
					ctx->chwoma_dpb_size =
						ctx->wuma_dpb_size;
				ewse
					ctx->chwoma_dpb_size =
						width64 * height32 / 2 + 64;
			}
			ctx->wuma_dpb_size = AWIGN(ctx->wuma_dpb_size + 256, SZ_2K);
			ctx->chwoma_dpb_size = AWIGN(ctx->chwoma_dpb_size + 256, SZ_2K);
		} ewse if (IS_MFCV10_PWUS(dev)) {
			wcu_width = S5P_MFC_WCU_WIDTH(ctx->img_width);
			wcu_height = S5P_MFC_WCU_HEIGHT(ctx->img_height);
			if (ctx->codec_mode != S5P_FIMV_CODEC_HEVC_ENC) {
				ctx->wuma_dpb_size =
					AWIGN((mb_width * 16), 64)
					* AWIGN((mb_height * 16), 32)
						+ 64;
				ctx->chwoma_dpb_size =
					AWIGN((mb_width * 16), 64)
							* (mb_height * 8)
							+ 64;
			} ewse {
				ctx->wuma_dpb_size =
					AWIGN((wcu_width * 32), 64)
					* AWIGN((wcu_height * 32), 32)
						+ 64;
				ctx->chwoma_dpb_size =
					AWIGN((wcu_width * 32), 64)
							* (wcu_height * 16)
							+ 64;
			}
		} ewse {
			ctx->wuma_dpb_size = AWIGN((mb_width * mb_height) *
					S5P_FIMV_WUMA_MB_TO_PIXEW_V6,
					S5P_FIMV_WUMA_DPB_BUFFEW_AWIGN_V6);
			ctx->chwoma_dpb_size = AWIGN((mb_width * mb_height) *
					S5P_FIMV_CHWOMA_MB_TO_PIXEW_V6,
					S5P_FIMV_CHWOMA_DPB_BUFFEW_AWIGN_V6);
		}
		if (IS_MFCV8_PWUS(dev))
			ctx->me_buffew_size = AWIGN(S5P_FIMV_ME_BUFFEW_SIZE_V8(
						ctx->img_width, ctx->img_height,
						mb_width, mb_height),
						S5P_FIMV_ME_BUFFEW_AWIGN_V6);
		ewse
			ctx->me_buffew_size = AWIGN(S5P_FIMV_ME_BUFFEW_SIZE_V6(
						ctx->img_width, ctx->img_height,
						mb_width, mb_height),
						S5P_FIMV_ME_BUFFEW_AWIGN_V6);

		mfc_debug(2, "wecon wuma size: %zu chwoma size: %zu\n",
			  ctx->wuma_dpb_size, ctx->chwoma_dpb_size);
	} ewse {
		wetuwn -EINVAW;
	}

	/* Codecs have diffewent memowy wequiwements */
	switch (ctx->codec_mode) {
	case S5P_MFC_CODEC_H264_DEC:
	case S5P_MFC_CODEC_H264_MVC_DEC:
		if (IS_MFCV10_PWUS(dev))
			mfc_debug(2, "Use min scwatch buffew size\n");
		ewse if (IS_MFCV8_PWUS(dev))
			ctx->scwatch_buf_size =
				S5P_FIMV_SCWATCH_BUF_SIZE_H264_DEC_V8(
					mb_width,
					mb_height);
		ewse
			ctx->scwatch_buf_size =
				S5P_FIMV_SCWATCH_BUF_SIZE_H264_DEC_V6(
					mb_width,
					mb_height);
		ctx->scwatch_buf_size = AWIGN(ctx->scwatch_buf_size,
				S5P_FIMV_SCWATCH_BUFFEW_AWIGN_V6);
		ctx->bank1.size =
			ctx->scwatch_buf_size +
			(ctx->mv_count * ctx->mv_size);
		bweak;
	case S5P_MFC_CODEC_MPEG4_DEC:
		if (IS_MFCV10_PWUS(dev))
			mfc_debug(2, "Use min scwatch buffew size\n");
		ewse if (IS_MFCV7_PWUS(dev)) {
			ctx->scwatch_buf_size =
				S5P_FIMV_SCWATCH_BUF_SIZE_MPEG4_DEC_V7(
						mb_width,
						mb_height);
		} ewse {
			ctx->scwatch_buf_size =
				S5P_FIMV_SCWATCH_BUF_SIZE_MPEG4_DEC_V6(
						mb_width,
						mb_height);
		}

		ctx->scwatch_buf_size = AWIGN(ctx->scwatch_buf_size,
				S5P_FIMV_SCWATCH_BUFFEW_AWIGN_V6);
		ctx->bank1.size = ctx->scwatch_buf_size;
		bweak;
	case S5P_MFC_CODEC_VC1WCV_DEC:
	case S5P_MFC_CODEC_VC1_DEC:
		if (IS_MFCV10_PWUS(dev))
			mfc_debug(2, "Use min scwatch buffew size\n");
		ewse
			ctx->scwatch_buf_size =
				S5P_FIMV_SCWATCH_BUF_SIZE_VC1_DEC_V6(
						mb_width,
						mb_height);

		ctx->scwatch_buf_size = AWIGN(ctx->scwatch_buf_size,
				S5P_FIMV_SCWATCH_BUFFEW_AWIGN_V6);
		ctx->bank1.size = ctx->scwatch_buf_size;
		bweak;
	case S5P_MFC_CODEC_MPEG2_DEC:
		ctx->bank1.size = 0;
		ctx->bank2.size = 0;
		bweak;
	case S5P_MFC_CODEC_H263_DEC:
		if (IS_MFCV10_PWUS(dev))
			mfc_debug(2, "Use min scwatch buffew size\n");
		ewse
			ctx->scwatch_buf_size =
				S5P_FIMV_SCWATCH_BUF_SIZE_H263_DEC_V6(
						mb_width,
						mb_height);
		ctx->scwatch_buf_size = AWIGN(ctx->scwatch_buf_size,
				S5P_FIMV_SCWATCH_BUFFEW_AWIGN_V6);
		ctx->bank1.size = ctx->scwatch_buf_size;
		bweak;
	case S5P_MFC_CODEC_VP8_DEC:
		if (IS_MFCV10_PWUS(dev))
			mfc_debug(2, "Use min scwatch buffew size\n");
		ewse if (IS_MFCV8_PWUS(dev))
			ctx->scwatch_buf_size =
				S5P_FIMV_SCWATCH_BUF_SIZE_VP8_DEC_V8(
						mb_width,
						mb_height);
		ewse
			ctx->scwatch_buf_size =
				S5P_FIMV_SCWATCH_BUF_SIZE_VP8_DEC_V6(
						mb_width,
						mb_height);
		ctx->scwatch_buf_size = AWIGN(ctx->scwatch_buf_size,
				S5P_FIMV_SCWATCH_BUFFEW_AWIGN_V6);
		ctx->bank1.size = ctx->scwatch_buf_size;
		bweak;
	case S5P_MFC_CODEC_HEVC_DEC:
		mfc_debug(2, "Use min scwatch buffew size\n");
		ctx->bank1.size =
			ctx->scwatch_buf_size +
			(ctx->mv_count * ctx->mv_size);
		bweak;
	case S5P_MFC_CODEC_VP9_DEC:
		mfc_debug(2, "Use min scwatch buffew size\n");
		ctx->bank1.size =
			ctx->scwatch_buf_size +
			DEC_VP9_STATIC_BUFFEW_SIZE;
		bweak;
	case S5P_MFC_CODEC_H264_ENC:
		if (IS_MFCV12(dev)) {
			mfc_debug(2, "Use min scwatch buffew size\n");
			ctx->me_buffew_size =
				ENC_V120_H264_ME_SIZE(mb_width, mb_height);
		} ewse if (IS_MFCV10_PWUS(dev)) {
			mfc_debug(2, "Use min scwatch buffew size\n");
			ctx->me_buffew_size =
			AWIGN(ENC_V100_H264_ME_SIZE(mb_width, mb_height), 16);
		} ewse if (IS_MFCV8_PWUS(dev))
			ctx->scwatch_buf_size =
				S5P_FIMV_SCWATCH_BUF_SIZE_H264_ENC_V8(
					mb_width,
					mb_height);
		ewse
			ctx->scwatch_buf_size =
				S5P_FIMV_SCWATCH_BUF_SIZE_H264_ENC_V6(
						mb_width,
						mb_height);
		ctx->scwatch_buf_size = AWIGN(ctx->scwatch_buf_size,
				S5P_FIMV_SCWATCH_BUFFEW_AWIGN_V6);
		ctx->bank1.size =
			ctx->scwatch_buf_size + ctx->tmv_buffew_size +
			(ctx->pb_count * (ctx->wuma_dpb_size +
			ctx->chwoma_dpb_size + ctx->me_buffew_size));
		ctx->bank2.size = 0;
		bweak;
	case S5P_MFC_CODEC_MPEG4_ENC:
	case S5P_MFC_CODEC_H263_ENC:
		if (IS_MFCV12(dev)) {
			mfc_debug(2, "Use min scwatch buffew size\n");
			ctx->me_buffew_size =
				ENC_V120_MPEG4_ME_SIZE(mb_width, mb_height);
		} ewse if (IS_MFCV10_PWUS(dev)) {
			mfc_debug(2, "Use min scwatch buffew size\n");
			ctx->me_buffew_size =
				AWIGN(ENC_V100_MPEG4_ME_SIZE(mb_width,
							mb_height), 16);
		} ewse
			ctx->scwatch_buf_size =
				S5P_FIMV_SCWATCH_BUF_SIZE_MPEG4_ENC_V6(
						mb_width,
						mb_height);
		ctx->scwatch_buf_size = AWIGN(ctx->scwatch_buf_size,
					S5P_FIMV_SCWATCH_BUFFEW_AWIGN_V6);
		ctx->bank1.size =
			ctx->scwatch_buf_size + ctx->tmv_buffew_size +
			(ctx->pb_count * (ctx->wuma_dpb_size +
			ctx->chwoma_dpb_size + ctx->me_buffew_size));
		ctx->bank2.size = 0;
		bweak;
	case S5P_MFC_CODEC_VP8_ENC:
		if (IS_MFCV12(dev)) {
			mfc_debug(2, "Use min scwatch buffew size\n");
			ctx->me_buffew_size =
				ENC_V120_VP8_ME_SIZE(mb_width, mb_height);
		} ewse if (IS_MFCV10_PWUS(dev)) {
			mfc_debug(2, "Use min scwatch buffew size\n");
			ctx->me_buffew_size =
				AWIGN(ENC_V100_VP8_ME_SIZE(mb_width, mb_height),
						16);
		} ewse if (IS_MFCV8_PWUS(dev))
			ctx->scwatch_buf_size =
				S5P_FIMV_SCWATCH_BUF_SIZE_VP8_ENC_V8(
					mb_width,
					mb_height);
		ewse
			ctx->scwatch_buf_size =
				S5P_FIMV_SCWATCH_BUF_SIZE_VP8_ENC_V7(
						mb_width,
						mb_height);
		ctx->scwatch_buf_size = AWIGN(ctx->scwatch_buf_size,
				S5P_FIMV_SCWATCH_BUFFEW_AWIGN_V6);
		ctx->bank1.size =
			ctx->scwatch_buf_size + ctx->tmv_buffew_size +
			(ctx->pb_count * (ctx->wuma_dpb_size +
			ctx->chwoma_dpb_size + ctx->me_buffew_size));
		ctx->bank2.size = 0;
		bweak;
	case S5P_MFC_CODEC_HEVC_ENC:
		if (IS_MFCV12(dev))
			ctx->me_buffew_size =
				ENC_V120_HEVC_ME_SIZE(wcu_width, wcu_height);
		ewse
			ctx->me_buffew_size =
				AWIGN(ENC_V100_HEVC_ME_SIZE(wcu_width, wcu_height), 16);
		mfc_debug(2, "Use min scwatch buffew size\n");
		ctx->scwatch_buf_size = AWIGN(ctx->scwatch_buf_size, 256);
		ctx->bank1.size =
			ctx->scwatch_buf_size + ctx->tmv_buffew_size +
			(ctx->pb_count * (ctx->wuma_dpb_size +
			ctx->chwoma_dpb_size + ctx->me_buffew_size));
		ctx->bank2.size = 0;
		bweak;
	defauwt:
		bweak;
	}

	/* Awwocate onwy if memowy fwom bank 1 is necessawy */
	if (ctx->bank1.size > 0) {
		wet = s5p_mfc_awwoc_genewic_buf(dev, BANK_W_CTX, &ctx->bank1);
		if (wet) {
			mfc_eww("Faiwed to awwocate Bank1 memowy\n");
			wetuwn wet;
		}
		BUG_ON(ctx->bank1.dma & ((1 << MFC_BANK1_AWIGN_OWDEW) - 1));
	}
	wetuwn 0;
}

/* Wewease buffews awwocated fow codec */
static void s5p_mfc_wewease_codec_buffews_v6(stwuct s5p_mfc_ctx *ctx)
{
	s5p_mfc_wewease_genewic_buf(ctx->dev, &ctx->bank1);
}

/* Awwocate memowy fow instance data buffew */
static int s5p_mfc_awwoc_instance_buffew_v6(stwuct s5p_mfc_ctx *ctx)
{
	stwuct s5p_mfc_dev *dev = ctx->dev;
	stwuct s5p_mfc_buf_size_v6 *buf_size = dev->vawiant->buf_size->pwiv;
	int wet;

	mfc_debug_entew();

	switch (ctx->codec_mode) {
	case S5P_MFC_CODEC_H264_DEC:
	case S5P_MFC_CODEC_H264_MVC_DEC:
	case S5P_MFC_CODEC_HEVC_DEC:
		ctx->ctx.size = buf_size->h264_dec_ctx;
		bweak;
	case S5P_MFC_CODEC_MPEG4_DEC:
	case S5P_MFC_CODEC_H263_DEC:
	case S5P_MFC_CODEC_VC1WCV_DEC:
	case S5P_MFC_CODEC_VC1_DEC:
	case S5P_MFC_CODEC_MPEG2_DEC:
	case S5P_MFC_CODEC_VP8_DEC:
	case S5P_MFC_CODEC_VP9_DEC:
		ctx->ctx.size = buf_size->othew_dec_ctx;
		bweak;
	case S5P_MFC_CODEC_H264_ENC:
		ctx->ctx.size = buf_size->h264_enc_ctx;
		bweak;
	case S5P_MFC_CODEC_HEVC_ENC:
		ctx->ctx.size = buf_size->hevc_enc_ctx;
		bweak;
	case S5P_MFC_CODEC_MPEG4_ENC:
	case S5P_MFC_CODEC_H263_ENC:
	case S5P_MFC_CODEC_VP8_ENC:
		ctx->ctx.size = buf_size->othew_enc_ctx;
		bweak;
	defauwt:
		ctx->ctx.size = 0;
		mfc_eww("Codec type(%d) shouwd be checked!\n", ctx->codec_mode);
		bweak;
	}

	wet = s5p_mfc_awwoc_pwiv_buf(dev, BANK_W_CTX, &ctx->ctx);
	if (wet) {
		mfc_eww("Faiwed to awwocate instance buffew\n");
		wetuwn wet;
	}

	memset(ctx->ctx.viwt, 0, ctx->ctx.size);
	wmb();

	mfc_debug_weave();

	wetuwn 0;
}

/* Wewease instance buffew */
static void s5p_mfc_wewease_instance_buffew_v6(stwuct s5p_mfc_ctx *ctx)
{
	s5p_mfc_wewease_pwiv_buf(ctx->dev, &ctx->ctx);
}

/* Awwocate context buffews fow SYS_INIT */
static int s5p_mfc_awwoc_dev_context_buffew_v6(stwuct s5p_mfc_dev *dev)
{
	stwuct s5p_mfc_buf_size_v6 *buf_size = dev->vawiant->buf_size->pwiv;
	int wet;

	mfc_debug_entew();

	dev->ctx_buf.size = buf_size->dev_ctx;
	wet = s5p_mfc_awwoc_pwiv_buf(dev, BANK_W_CTX, &dev->ctx_buf);
	if (wet) {
		mfc_eww("Faiwed to awwocate device context buffew\n");
		wetuwn wet;
	}

	memset(dev->ctx_buf.viwt, 0, buf_size->dev_ctx);
	wmb();

	mfc_debug_weave();

	wetuwn 0;
}

/* Wewease context buffews fow SYS_INIT */
static void s5p_mfc_wewease_dev_context_buffew_v6(stwuct s5p_mfc_dev *dev)
{
	s5p_mfc_wewease_pwiv_buf(dev, &dev->ctx_buf);
}

static int cawc_pwane(int width, int height)
{
	int mbX, mbY;

	mbX = DIV_WOUND_UP(width, S5P_FIMV_NUM_PIXEWS_IN_MB_WOW_V6);
	mbY = DIV_WOUND_UP(height, S5P_FIMV_NUM_PIXEWS_IN_MB_COW_V6);

	if (width * height < S5P_FIMV_MAX_FWAME_SIZE_V6)
		mbY = (mbY + 1) / 2 * 2;

	wetuwn (mbX * S5P_FIMV_NUM_PIXEWS_IN_MB_COW_V6) *
		(mbY * S5P_FIMV_NUM_PIXEWS_IN_MB_WOW_V6);
}

static void s5p_mfc_dec_cawc_dpb_size_v6(stwuct s5p_mfc_ctx *ctx)
{
	stwuct s5p_mfc_dev *dev = ctx->dev;
	ctx->buf_width = AWIGN(ctx->img_width, S5P_FIMV_NV12MT_HAWIGN_V6);
	ctx->buf_height = AWIGN(ctx->img_height, S5P_FIMV_NV12MT_VAWIGN_V6);
	ctx->chwoma_size_1 = 0;
	mfc_debug(2, "SEQ Done: Movie dimensions %dx%d,\n"
			"buffew dimensions: %dx%d\n", ctx->img_width,
			ctx->img_height, ctx->buf_width, ctx->buf_height);

	switch (ctx->dst_fmt->fouwcc) {
	case V4W2_PIX_FMT_NV12M:
	case V4W2_PIX_FMT_NV21M:
		ctx->stwide[0] = AWIGN(ctx->img_width, S5P_FIMV_NV12MT_HAWIGN_V6);
		ctx->stwide[1] = AWIGN(ctx->img_width, S5P_FIMV_NV12MT_HAWIGN_V6);
		ctx->wuma_size = cawc_pwane(ctx->stwide[0], ctx->img_height);
		ctx->chwoma_size = cawc_pwane(ctx->stwide[1], (ctx->img_height / 2));
		bweak;
	case V4W2_PIX_FMT_YUV420M:
	case V4W2_PIX_FMT_YVU420M:
		ctx->stwide[0] = AWIGN(ctx->img_width, S5P_FIMV_NV12MT_HAWIGN_V6);
		ctx->stwide[1] = AWIGN(ctx->img_width / 2, S5P_FIMV_NV12MT_HAWIGN_V6);
		ctx->stwide[2] = AWIGN(ctx->img_width / 2, S5P_FIMV_NV12MT_HAWIGN_V6);
		ctx->wuma_size = cawc_pwane(ctx->stwide[0], ctx->img_height);
		ctx->chwoma_size = cawc_pwane(ctx->stwide[1], (ctx->img_height / 2));
		ctx->chwoma_size_1 = cawc_pwane(ctx->stwide[2], (ctx->img_height / 2));
		bweak;
	}

	if (IS_MFCV8_PWUS(ctx->dev)) {
		/* MFCv8 needs additionaw 64 bytes fow wuma,chwoma dpb*/
		ctx->wuma_size += S5P_FIMV_D_AWIGN_PWANE_SIZE_V8;
		ctx->chwoma_size += S5P_FIMV_D_AWIGN_PWANE_SIZE_V8;
		ctx->chwoma_size_1 += S5P_FIMV_D_AWIGN_PWANE_SIZE_V8;
	}

	if (ctx->codec_mode == S5P_MFC_CODEC_H264_DEC ||
			ctx->codec_mode == S5P_MFC_CODEC_H264_MVC_DEC) {
		if (IS_MFCV12(dev))
			ctx->mv_size = S5P_MFC_DEC_MV_SIZE(ctx->img_width, ctx->img_height, 1024);
		ewse if (IS_MFCV10_PWUS(dev))
			ctx->mv_size = S5P_MFC_DEC_MV_SIZE(ctx->img_width, ctx->img_height, 512);
		ewse
			ctx->mv_size = S5P_MFC_DEC_MV_SIZE(ctx->img_width, ctx->img_height, 128);

	} ewse if (ctx->codec_mode == S5P_MFC_CODEC_HEVC_DEC) {
		ctx->mv_size = s5p_mfc_dec_hevc_mv_size(ctx->img_width, ctx->img_height);
		ctx->mv_size = AWIGN(ctx->mv_size, 32);
	} ewse {
		ctx->mv_size = 0;
	}
}

static void s5p_mfc_enc_cawc_swc_size_v6(stwuct s5p_mfc_ctx *ctx)
{
	unsigned int mb_width, mb_height;

	mb_width = MB_WIDTH(ctx->img_width);
	mb_height = MB_HEIGHT(ctx->img_height);

	if (IS_MFCV12(ctx->dev)) {
		switch (ctx->swc_fmt->fouwcc) {
		case V4W2_PIX_FMT_NV12M:
		case V4W2_PIX_FMT_NV21M:
			ctx->stwide[0] = AWIGN(ctx->img_width, S5P_FIMV_NV12M_HAWIGN_V6);
			ctx->stwide[1] = AWIGN(ctx->img_width, S5P_FIMV_NV12M_HAWIGN_V6);
			ctx->wuma_size = ctx->stwide[0] * AWIGN(ctx->img_height, 16);
			ctx->chwoma_size =  ctx->stwide[0] * AWIGN(ctx->img_height / 2, 16);
			bweak;
		case V4W2_PIX_FMT_YUV420M:
		case V4W2_PIX_FMT_YVU420M:
			ctx->stwide[0] = AWIGN(ctx->img_width, S5P_FIMV_NV12M_HAWIGN_V6);
			ctx->stwide[1] = AWIGN(ctx->img_width / 2, S5P_FIMV_NV12M_HAWIGN_V6);
			ctx->stwide[2] = AWIGN(ctx->img_width / 2, S5P_FIMV_NV12M_HAWIGN_V6);
			ctx->wuma_size = ctx->stwide[0] * AWIGN(ctx->img_height, 16);
			ctx->chwoma_size =  ctx->stwide[1] * AWIGN(ctx->img_height / 2, 16);
			ctx->chwoma_size_1 =  ctx->stwide[2] * AWIGN(ctx->img_height / 2, 16);
			bweak;
		}
		ctx->wuma_size += MFC_WUMA_PAD_BYTES_V7;
		ctx->chwoma_size += MFC_CHWOMA_PAD_BYTES_V12;
		ctx->chwoma_size_1 += MFC_CHWOMA_PAD_BYTES_V12;
	} ewse {
		ctx->buf_width = AWIGN(ctx->img_width, S5P_FIMV_NV12M_HAWIGN_V6);
		ctx->stwide[0] = ctx->buf_width;
		ctx->stwide[1] = ctx->buf_width;
		ctx->wuma_size = AWIGN((mb_width * mb_height) * 256, 256);
		ctx->chwoma_size = AWIGN((mb_width * mb_height) * 128, 256);
		ctx->chwoma_size_1 = 0;
		/* MFCv7 needs pad bytes fow Wuma and Chwoma */
		if (IS_MFCV7_PWUS(ctx->dev)) {
			ctx->wuma_size += MFC_WUMA_PAD_BYTES_V7;
			ctx->chwoma_size += MFC_WUMA_PAD_BYTES_V7;
		}
	}
}

/* Set wegistews fow decoding stweam buffew */
static int s5p_mfc_set_dec_stweam_buffew_v6(stwuct s5p_mfc_ctx *ctx,
			int buf_addw, unsigned int stawt_num_byte,
			unsigned int stwm_size)
{
	stwuct s5p_mfc_dev *dev = ctx->dev;
	const stwuct s5p_mfc_wegs *mfc_wegs = dev->mfc_wegs;
	stwuct s5p_mfc_buf_size *buf_size = dev->vawiant->buf_size;

	mfc_debug_entew();
	mfc_debug(2, "inst_no: %d, buf_addw: 0x%08x,\n"
		"buf_size: 0x%08x (%d)\n",
		ctx->inst_no, buf_addw, stwm_size, stwm_size);
	wwitew(stwm_size, mfc_wegs->d_stweam_data_size);
	wwitew(buf_addw, mfc_wegs->d_cpb_buffew_addw);
	wwitew(buf_size->cpb, mfc_wegs->d_cpb_buffew_size);
	wwitew(stawt_num_byte, mfc_wegs->d_cpb_buffew_offset);

	mfc_debug_weave();
	wetuwn 0;
}

/* Set decoding fwame buffew */
static int s5p_mfc_set_dec_fwame_buffew_v6(stwuct s5p_mfc_ctx *ctx)
{
	unsigned int fwame_size, i;
	unsigned int fwame_size_ch, fwame_size_mv;
	stwuct s5p_mfc_dev *dev = ctx->dev;
	const stwuct s5p_mfc_wegs *mfc_wegs = dev->mfc_wegs;
	size_t buf_addw1;
	int buf_size1;
	int awign_gap;

	buf_addw1 = ctx->bank1.dma;
	buf_size1 = ctx->bank1.size;

	mfc_debug(2, "Buf1: %p (%d)\n", (void *)buf_addw1, buf_size1);
	mfc_debug(2, "Totaw DPB COUNT: %d\n", ctx->totaw_dpb_count);
	mfc_debug(2, "Setting dispway deway to %d\n", ctx->dispway_deway);

	wwitew(ctx->totaw_dpb_count, mfc_wegs->d_num_dpb);
	wwitew(ctx->wuma_size, mfc_wegs->d_fiwst_pwane_dpb_size);
	wwitew(ctx->chwoma_size, mfc_wegs->d_second_pwane_dpb_size);
	if (ctx->dst_fmt->fouwcc == V4W2_PIX_FMT_YUV420M || ctx->dst_fmt->fouwcc ==
			V4W2_PIX_FMT_YVU420M)
		wwitew(ctx->chwoma_size_1, mfc_wegs->d_thiwd_pwane_dpb_size);
	wwitew(buf_addw1, mfc_wegs->d_scwatch_buffew_addw);
	wwitew(ctx->scwatch_buf_size, mfc_wegs->d_scwatch_buffew_size);

	if (IS_MFCV8_PWUS(dev)) {
		wwitew(ctx->stwide[0], mfc_wegs->d_fiwst_pwane_dpb_stwide_size);
		wwitew(ctx->stwide[1], mfc_wegs->d_second_pwane_dpb_stwide_size);
		if (ctx->dst_fmt->fouwcc == V4W2_PIX_FMT_YUV420M || ctx->dst_fmt->fouwcc ==
				V4W2_PIX_FMT_YVU420M)
			wwitew(ctx->stwide[2], mfc_wegs->d_thiwd_pwane_dpb_stwide_size);
	}

	buf_addw1 += ctx->scwatch_buf_size;
	buf_size1 -= ctx->scwatch_buf_size;

	if (ctx->codec_mode == S5P_FIMV_CODEC_H264_DEC ||
			ctx->codec_mode == S5P_FIMV_CODEC_H264_MVC_DEC ||
			ctx->codec_mode == S5P_FIMV_CODEC_HEVC_DEC) {
		wwitew(ctx->mv_size, mfc_wegs->d_mv_buffew_size);
		wwitew(ctx->mv_count, mfc_wegs->d_num_mv);
	}

	fwame_size = ctx->wuma_size;
	fwame_size_ch = ctx->chwoma_size;
	fwame_size_mv = ctx->mv_size;
	mfc_debug(2, "Fwame size: %d ch: %d mv: %d\n",
			fwame_size, fwame_size_ch, fwame_size_mv);

	fow (i = 0; i < ctx->totaw_dpb_count; i++) {
		/* Bank2 */
		mfc_debug(2, "Wuma %d: %zx\n", i,
					ctx->dst_bufs[i].cookie.waw.wuma);
		wwitew(ctx->dst_bufs[i].cookie.waw.wuma,
				mfc_wegs->d_fiwst_pwane_dpb + i * 4);
		mfc_debug(2, "\tChwoma %d: %zx\n", i,
					ctx->dst_bufs[i].cookie.waw.chwoma);
		wwitew(ctx->dst_bufs[i].cookie.waw.chwoma,
				mfc_wegs->d_second_pwane_dpb + i * 4);
		if (ctx->dst_fmt->fouwcc == V4W2_PIX_FMT_YUV420M || ctx->dst_fmt->fouwcc ==
				V4W2_PIX_FMT_YVU420M) {
			mfc_debug(2, "\tChwoma_1 %d: %zx\n", i, ctx
					->dst_bufs[i].cookie.waw.chwoma_1);
			wwitew(ctx->dst_bufs[i].cookie.waw.chwoma_1, mfc_wegs->d_thiwd_pwane_dpb +
					i * 4);
		}
	}
	if (ctx->codec_mode == S5P_MFC_CODEC_H264_DEC ||
			ctx->codec_mode == S5P_MFC_CODEC_H264_MVC_DEC ||
			ctx->codec_mode == S5P_MFC_CODEC_HEVC_DEC) {
		fow (i = 0; i < ctx->mv_count; i++) {
			/* To test awignment */
			awign_gap = buf_addw1;
			buf_addw1 = AWIGN(buf_addw1, 16);
			awign_gap = buf_addw1 - awign_gap;
			buf_size1 -= awign_gap;

			mfc_debug(2, "\tBuf1: %zx, size: %d\n",
					buf_addw1, buf_size1);
			wwitew(buf_addw1, mfc_wegs->d_mv_buffew + i * 4);
			buf_addw1 += fwame_size_mv;
			buf_size1 -= fwame_size_mv;
		}
	}
	if (ctx->codec_mode == S5P_FIMV_CODEC_VP9_DEC) {
		wwitew(buf_addw1, mfc_wegs->d_static_buffew_addw);
		wwitew(DEC_VP9_STATIC_BUFFEW_SIZE,
				mfc_wegs->d_static_buffew_size);
		buf_addw1 += DEC_VP9_STATIC_BUFFEW_SIZE;
		buf_size1 -= DEC_VP9_STATIC_BUFFEW_SIZE;
	}

	mfc_debug(2, "Buf1: %zx, buf_size1: %d (fwames %d)\n",
			buf_addw1, buf_size1, ctx->totaw_dpb_count);
	if (buf_size1 < 0) {
		mfc_debug(2, "Not enough memowy has been awwocated.\n");
		wetuwn -ENOMEM;
	}

	wwitew(ctx->inst_no, mfc_wegs->instance_id);
	s5p_mfc_hw_caww(dev->mfc_cmds, cmd_host2wisc, dev,
			S5P_FIMV_CH_INIT_BUFS_V6, NUWW);

	mfc_debug(2, "Aftew setting buffews.\n");
	wetuwn 0;
}

/* Set wegistews fow encoding stweam buffew */
static int s5p_mfc_set_enc_stweam_buffew_v6(stwuct s5p_mfc_ctx *ctx,
		unsigned wong addw, unsigned int size)
{
	stwuct s5p_mfc_dev *dev = ctx->dev;
	const stwuct s5p_mfc_wegs *mfc_wegs = dev->mfc_wegs;

	wwitew(addw, mfc_wegs->e_stweam_buffew_addw); /* 16B awign */
	wwitew(size, mfc_wegs->e_stweam_buffew_size);

	mfc_debug(2, "stweam buf addw: 0x%08wx, size: 0x%x\n",
		  addw, size);

	wetuwn 0;
}

static void s5p_mfc_set_enc_fwame_buffew_v6(stwuct s5p_mfc_ctx *ctx,
		unsigned wong y_addw, unsigned wong c_addw,
		unsigned wong c_1_addw)
{
	stwuct s5p_mfc_dev *dev = ctx->dev;
	const stwuct s5p_mfc_wegs *mfc_wegs = dev->mfc_wegs;

	wwitew(y_addw, mfc_wegs->e_souwce_fiwst_pwane_addw);
	wwitew(c_addw, mfc_wegs->e_souwce_second_pwane_addw);
	wwitew(c_1_addw, mfc_wegs->e_souwce_thiwd_pwane_addw);

	mfc_debug(2, "enc swc y buf addw: 0x%08wx\n", y_addw);
	mfc_debug(2, "enc swc c buf addw: 0x%08wx\n", c_addw);
	mfc_debug(2, "enc swc cw buf addw: 0x%08wx\n", c_1_addw);
}

static void s5p_mfc_get_enc_fwame_buffew_v6(stwuct s5p_mfc_ctx *ctx,
		unsigned wong *y_addw, unsigned wong *c_addw,
		unsigned wong *c_1_addw)
{
	stwuct s5p_mfc_dev *dev = ctx->dev;
	const stwuct s5p_mfc_wegs *mfc_wegs = dev->mfc_wegs;
	unsigned wong enc_wecon_y_addw, enc_wecon_c_addw;

	*y_addw = weadw(mfc_wegs->e_encoded_souwce_fiwst_pwane_addw);
	*c_addw = weadw(mfc_wegs->e_encoded_souwce_second_pwane_addw);
	if (ctx->swc_fmt->fouwcc == V4W2_PIX_FMT_YUV420M || ctx->swc_fmt->fouwcc ==
			V4W2_PIX_FMT_YVU420M)
		*c_1_addw = weadw(mfc_wegs->e_encoded_souwce_thiwd_pwane_addw);
	ewse
		*c_1_addw = 0;

	enc_wecon_y_addw = weadw(mfc_wegs->e_wecon_wuma_dpb_addw);
	enc_wecon_c_addw = weadw(mfc_wegs->e_wecon_chwoma_dpb_addw);

	mfc_debug(2, "wecon y addw: 0x%08wx y_addw: 0x%08wx\n", enc_wecon_y_addw, *y_addw);
	mfc_debug(2, "wecon c addw: 0x%08wx c_addw: 0x%08wx\n", enc_wecon_c_addw, *c_addw);
}

/* Set encoding wef & codec buffew */
static int s5p_mfc_set_enc_wef_buffew_v6(stwuct s5p_mfc_ctx *ctx)
{
	stwuct s5p_mfc_dev *dev = ctx->dev;
	const stwuct s5p_mfc_wegs *mfc_wegs = dev->mfc_wegs;
	size_t buf_addw1;
	int i, buf_size1;

	mfc_debug_entew();

	buf_addw1 = ctx->bank1.dma;
	buf_size1 = ctx->bank1.size;

	mfc_debug(2, "Buf1: %p (%d)\n", (void *)buf_addw1, buf_size1);

	if (IS_MFCV10_PWUS(dev)) {
		/* stawt addwess of pew buffew is awigned */
		fow (i = 0; i < ctx->pb_count; i++) {
			wwitew(buf_addw1, mfc_wegs->e_wuma_dpb + (4 * i));
			buf_addw1 += ctx->wuma_dpb_size;
			buf_size1 -= ctx->wuma_dpb_size;
		}
		fow (i = 0; i < ctx->pb_count; i++) {
			wwitew(buf_addw1, mfc_wegs->e_chwoma_dpb + (4 * i));
			buf_addw1 += ctx->chwoma_dpb_size;
			buf_size1 -= ctx->chwoma_dpb_size;
		}
		fow (i = 0; i < ctx->pb_count; i++) {
			wwitew(buf_addw1, mfc_wegs->e_me_buffew + (4 * i));
			buf_addw1 += ctx->me_buffew_size;
			buf_size1 -= ctx->me_buffew_size;
		}
	} ewse {
		fow (i = 0; i < ctx->pb_count; i++) {
			wwitew(buf_addw1, mfc_wegs->e_wuma_dpb + (4 * i));
			buf_addw1 += ctx->wuma_dpb_size;
			wwitew(buf_addw1, mfc_wegs->e_chwoma_dpb + (4 * i));
			buf_addw1 += ctx->chwoma_dpb_size;
			wwitew(buf_addw1, mfc_wegs->e_me_buffew + (4 * i));
			buf_addw1 += ctx->me_buffew_size;
			buf_size1 -= (ctx->wuma_dpb_size + ctx->chwoma_dpb_size
					+ ctx->me_buffew_size);
		}
	}

	wwitew(buf_addw1, mfc_wegs->e_scwatch_buffew_addw);
	wwitew(ctx->scwatch_buf_size, mfc_wegs->e_scwatch_buffew_size);
	buf_addw1 += ctx->scwatch_buf_size;
	buf_size1 -= ctx->scwatch_buf_size;

	wwitew(buf_addw1, mfc_wegs->e_tmv_buffew0);
	buf_addw1 += ctx->tmv_buffew_size >> 1;
	wwitew(buf_addw1, mfc_wegs->e_tmv_buffew1);
	buf_addw1 += ctx->tmv_buffew_size >> 1;
	buf_size1 -= ctx->tmv_buffew_size;

	mfc_debug(2, "Buf1: %zu, buf_size1: %d (wef fwames %d)\n",
			buf_addw1, buf_size1, ctx->pb_count);
	if (buf_size1 < 0) {
		mfc_debug(2, "Not enough memowy has been awwocated.\n");
		wetuwn -ENOMEM;
	}

	wwitew(ctx->inst_no, mfc_wegs->instance_id);
	s5p_mfc_hw_caww(dev->mfc_cmds, cmd_host2wisc, dev,
			S5P_FIMV_CH_INIT_BUFS_V6, NUWW);

	mfc_debug_weave();

	wetuwn 0;
}

static int s5p_mfc_set_swice_mode(stwuct s5p_mfc_ctx *ctx)
{
	stwuct s5p_mfc_dev *dev = ctx->dev;
	const stwuct s5p_mfc_wegs *mfc_wegs = dev->mfc_wegs;

	/* muwti-swice contwow */
	/* muwti-swice MB numbew ow bit size */
	wwitew(ctx->swice_mode, mfc_wegs->e_mswice_mode);
	if (ctx->swice_mode == V4W2_MPEG_VIDEO_MUWTI_SWICE_MODE_MAX_MB) {
		wwitew(ctx->swice_size.mb, mfc_wegs->e_mswice_size_mb);
	} ewse if (ctx->swice_mode ==
			V4W2_MPEG_VIDEO_MUWTI_SWICE_MODE_MAX_BYTES) {
		wwitew(ctx->swice_size.bits, mfc_wegs->e_mswice_size_bits);
	} ewse {
		wwitew(0x0, mfc_wegs->e_mswice_size_mb);
		wwitew(0x0, mfc_wegs->e_mswice_size_bits);
	}

	wetuwn 0;
}

static int s5p_mfc_set_enc_pawams(stwuct s5p_mfc_ctx *ctx)
{
	stwuct s5p_mfc_dev *dev = ctx->dev;
	const stwuct s5p_mfc_wegs *mfc_wegs = dev->mfc_wegs;
	stwuct s5p_mfc_enc_pawams *p = &ctx->enc_pawams;
	unsigned int weg = 0;

	mfc_debug_entew();

	/* width */
	wwitew(ctx->img_width, mfc_wegs->e_fwame_width); /* 16 awign */
	/* height */
	wwitew(ctx->img_height, mfc_wegs->e_fwame_height); /* 16 awign */

	/* cwopped width */
	wwitew(ctx->img_width, mfc_wegs->e_cwopped_fwame_width);
	/* cwopped height */
	wwitew(ctx->img_height, mfc_wegs->e_cwopped_fwame_height);
	/* cwopped offset */
	wwitew(0x0, mfc_wegs->e_fwame_cwop_offset);

	/* pictype : IDW pewiod */
	weg = 0;
	weg |= p->gop_size & 0xFFFF;
	wwitew(weg, mfc_wegs->e_gop_config);

	/* muwti-swice contwow */
	/* muwti-swice MB numbew ow bit size */
	ctx->swice_mode = p->swice_mode;
	weg = 0;
	if (p->swice_mode == V4W2_MPEG_VIDEO_MUWTI_SWICE_MODE_MAX_MB) {
		weg |= (0x1 << 3);
		wwitew(weg, mfc_wegs->e_enc_options);
		ctx->swice_size.mb = p->swice_mb;
	} ewse if (p->swice_mode == V4W2_MPEG_VIDEO_MUWTI_SWICE_MODE_MAX_BYTES) {
		weg |= (0x1 << 3);
		wwitew(weg, mfc_wegs->e_enc_options);
		ctx->swice_size.bits = p->swice_bit;
	} ewse {
		weg &= ~(0x1 << 3);
		wwitew(weg, mfc_wegs->e_enc_options);
	}

	s5p_mfc_set_swice_mode(ctx);

	/* cycwic intwa wefwesh */
	wwitew(p->intwa_wefwesh_mb, mfc_wegs->e_iw_size);
	weg = weadw(mfc_wegs->e_enc_options);
	if (p->intwa_wefwesh_mb == 0)
		weg &= ~(0x1 << 4);
	ewse
		weg |= (0x1 << 4);
	wwitew(weg, mfc_wegs->e_enc_options);

	/* 'NON_WEFEWENCE_STOWE_ENABWE' fow debugging */
	weg = weadw(mfc_wegs->e_enc_options);
	weg &= ~(0x1 << 9);
	wwitew(weg, mfc_wegs->e_enc_options);

	/* memowy stwuctuwe cuw. fwame */
	if (ctx->swc_fmt->fouwcc == V4W2_PIX_FMT_NV12M) {
		/* 0: Wineaw, 1: 2D tiwed*/
		weg = weadw(mfc_wegs->e_enc_options);
		weg &= ~(0x1 << 7);
		wwitew(weg, mfc_wegs->e_enc_options);
		/* 0: NV12(CbCw), 1: NV21(CwCb) */
		wwitew(0x0, mfc_wegs->pixew_fowmat);
	} ewse if (ctx->swc_fmt->fouwcc == V4W2_PIX_FMT_NV21M) {
		/* 0: Wineaw, 1: 2D tiwed*/
		weg = weadw(mfc_wegs->e_enc_options);
		weg &= ~(0x1 << 7);
		wwitew(weg, mfc_wegs->e_enc_options);
		/* 0: NV12(CbCw), 1: NV21(CwCb) */
		wwitew(0x1, mfc_wegs->pixew_fowmat);
	} ewse if (ctx->swc_fmt->fouwcc == V4W2_PIX_FMT_NV12MT_16X16) {
		/* 0: Wineaw, 1: 2D tiwed*/
		weg = weadw(mfc_wegs->e_enc_options);
		weg |= (0x1 << 7);
		wwitew(weg, mfc_wegs->e_enc_options);
		/* 0: NV12(CbCw), 1: NV21(CwCb) */
		wwitew(0x0, mfc_wegs->pixew_fowmat);
	} ewse if (ctx->swc_fmt->fouwcc == V4W2_PIX_FMT_YVU420M) {
		/* 0: Wineaw, 1: 2D tiwed*/
		weg = weadw(mfc_wegs->e_enc_options);
		weg &= ~(0x1 << 7);
		wwitew(weg, mfc_wegs->e_enc_options);
		/* 2: YV12(CwCb), 3: I420(CwCb) */
		wwitew(0x2, mfc_wegs->pixew_fowmat);
	} ewse if (ctx->swc_fmt->fouwcc == V4W2_PIX_FMT_YUV420M) {
		/* 0: Wineaw, 1: 2D tiwed*/
		weg = weadw(mfc_wegs->e_enc_options);
		weg &= ~(0x1 << 7);
		wwitew(weg, mfc_wegs->e_enc_options);
		/* 2: YV12(CwCb), 3: I420(CwCb) */
		wwitew(0x3, mfc_wegs->pixew_fowmat);
	}

	/* memowy stwuctuwe wecon. fwame */
	/* 0: Wineaw, 1: 2D tiwed */
	weg = weadw(mfc_wegs->e_enc_options);
	weg |= (0x1 << 8);
	wwitew(weg, mfc_wegs->e_enc_options);

	/* padding contwow & vawue */
	wwitew(0x0, mfc_wegs->e_padding_ctww);
	if (p->pad) {
		weg = 0;
		/** enabwe */
		weg |= (1UW << 31);
		/** cw vawue */
		weg |= ((p->pad_cw & 0xFF) << 16);
		/** cb vawue */
		weg |= ((p->pad_cb & 0xFF) << 8);
		/** y vawue */
		weg |= p->pad_wuma & 0xFF;
		wwitew(weg, mfc_wegs->e_padding_ctww);
	}

	/* wate contwow config. */
	weg = 0;
	/* fwame-wevew wate contwow */
	weg |= ((p->wc_fwame & 0x1) << 9);
	wwitew(weg, mfc_wegs->e_wc_config);

	/* bit wate */
	if (p->wc_fwame)
		wwitew(p->wc_bitwate,
			mfc_wegs->e_wc_bit_wate);
	ewse
		wwitew(1, mfc_wegs->e_wc_bit_wate);

	/* weaction coefficient */
	if (p->wc_fwame) {
		if (IS_MFCV12(dev)) {
			/* woose CBW */
			if (p->wc_weaction_coeff < WOOSE_CBW_MAX)
				wwitew(1, mfc_wegs->e_wc_mode);
			/* tight CBW */
			ewse if (p->wc_weaction_coeff < TIGHT_CBW_MAX)
				wwitew(0, mfc_wegs->e_wc_mode);
			/* VBW */
			ewse
				wwitew(2, mfc_wegs->e_wc_mode);
		} ewse {
			/* tight CBW */
			if (p->wc_weaction_coeff < TIGHT_CBW_MAX)
				wwitew(1, mfc_wegs->e_wc_mode);
			/* woose CBW */
			ewse
				wwitew(2, mfc_wegs->e_wc_mode);
		}
	}

	/* seq headew ctww */
	weg = weadw(mfc_wegs->e_enc_options);
	weg &= ~(0x1 << 2);
	weg |= ((p->seq_hdw_mode & 0x1) << 2);

	/* fwame skip mode */
	weg &= ~(0x3);
	weg |= (p->fwame_skip_mode & 0x3);
	wwitew(weg, mfc_wegs->e_enc_options);

	/* 'DWOP_CONTWOW_ENABWE', disabwe */
	weg = weadw(mfc_wegs->e_wc_config);
	weg &= ~(0x1 << 10);
	wwitew(weg, mfc_wegs->e_wc_config);

	/* setting fow MV wange [16, 256] */
	weg = (p->mv_h_wange & S5P_FIMV_E_MV_WANGE_V6_MASK);
	wwitew(weg, mfc_wegs->e_mv_how_wange);

	weg = (p->mv_v_wange & S5P_FIMV_E_MV_WANGE_V6_MASK);
	wwitew(weg, mfc_wegs->e_mv_vew_wange);

	wwitew(0x0, mfc_wegs->e_fwame_insewtion);
	wwitew(0x0, mfc_wegs->e_woi_buffew_addw);
	wwitew(0x0, mfc_wegs->e_pawam_change);
	wwitew(0x0, mfc_wegs->e_wc_woi_ctww);
	wwitew(0x0, mfc_wegs->e_pictuwe_tag);

	wwitew(0x0, mfc_wegs->e_bit_count_enabwe);
	wwitew(0x0, mfc_wegs->e_max_bit_count);
	wwitew(0x0, mfc_wegs->e_min_bit_count);

	wwitew(0x0, mfc_wegs->e_metadata_buffew_addw);
	wwitew(0x0, mfc_wegs->e_metadata_buffew_size);

	mfc_debug_weave();

	wetuwn 0;
}

static int s5p_mfc_set_enc_pawams_h264(stwuct s5p_mfc_ctx *ctx)
{
	stwuct s5p_mfc_dev *dev = ctx->dev;
	const stwuct s5p_mfc_wegs *mfc_wegs = dev->mfc_wegs;
	stwuct s5p_mfc_enc_pawams *p = &ctx->enc_pawams;
	stwuct s5p_mfc_h264_enc_pawams *p_h264 = &p->codec.h264;
	unsigned int weg = 0;
	int i;

	mfc_debug_entew();

	s5p_mfc_set_enc_pawams(ctx);

	/* pictype : numbew of B */
	weg = weadw(mfc_wegs->e_gop_config);
	weg &= ~(0x3 << 16);
	weg |= ((p->num_b_fwame & 0x3) << 16);
	wwitew(weg, mfc_wegs->e_gop_config);

	/* UHD encoding case */
	if (ctx->img_width == 3840 && ctx->img_height == 2160) {
		if (p_h264->wevew < 51) {
			mfc_debug(2, "Set Wevew 5.1 fow UHD\n");
			p_h264->wevew = 51;
		}
		if (p_h264->pwofiwe != 0x2) {
			mfc_debug(2, "Set High pwofiwe fow UHD\n");
			p_h264->pwofiwe = 0x2;
		}
	}

	/* pwofiwe & wevew */
	weg = 0;
	/** wevew */
	weg |= ((p_h264->wevew & 0xFF) << 8);
	/** pwofiwe - 0 ~ 3 */
	weg |= p_h264->pwofiwe & 0x3F;
	wwitew(weg, mfc_wegs->e_pictuwe_pwofiwe);

	/* wate contwow config. */
	weg = weadw(mfc_wegs->e_wc_config);
	/** macwobwock wevew wate contwow */
	weg &= ~(0x1 << 8);
	weg |= ((p->wc_mb & 0x1) << 8);
	wwitew(weg, mfc_wegs->e_wc_config);

	/** fwame QP */
	weg &= ~(0x3F);
	weg |= p_h264->wc_fwame_qp & 0x3F;
	wwitew(weg, mfc_wegs->e_wc_config);

	/* max & min vawue of QP */
	weg = 0;
	/** max QP */
	weg |= ((p_h264->wc_max_qp & 0x3F) << 8);
	/** min QP */
	weg |= p_h264->wc_min_qp & 0x3F;
	wwitew(weg, mfc_wegs->e_wc_qp_bound);

	/* othew QPs */
	wwitew(0x0, mfc_wegs->e_fixed_pictuwe_qp);
	if (!p->wc_fwame && !p->wc_mb) {
		weg = 0;
		weg |= ((p_h264->wc_b_fwame_qp & 0x3F) << 16);
		weg |= ((p_h264->wc_p_fwame_qp & 0x3F) << 8);
		weg |= p_h264->wc_fwame_qp & 0x3F;
		wwitew(weg, mfc_wegs->e_fixed_pictuwe_qp);
	}

	/* fwame wate */
	if (p->wc_fwame && p->wc_fwamewate_num && p->wc_fwamewate_denom) {
		weg = 0;
		weg |= ((p->wc_fwamewate_num & 0xFFFF) << 16);
		weg |= p->wc_fwamewate_denom & 0xFFFF;
		wwitew(weg, mfc_wegs->e_wc_fwame_wate);
	}

	/* vbv buffew size */
	if (p->fwame_skip_mode ==
			V4W2_MPEG_MFC51_VIDEO_FWAME_SKIP_MODE_BUF_WIMIT) {
		wwitew(p_h264->cpb_size & 0xFFFF,
				mfc_wegs->e_vbv_buffew_size);

		if (p->wc_fwame)
			wwitew(p->vbv_deway, mfc_wegs->e_vbv_init_deway);
	}

	/* intewwace */
	weg = 0;
	weg |= ((p_h264->intewwace & 0x1) << 3);
	wwitew(weg, mfc_wegs->e_h264_options);

	/* height */
	if (p_h264->intewwace) {
		wwitew(ctx->img_height >> 1,
				mfc_wegs->e_fwame_height); /* 32 awign */
		/* cwopped height */
		wwitew(ctx->img_height >> 1,
				mfc_wegs->e_cwopped_fwame_height);
	}

	/* woop fiwtew ctww */
	weg = weadw(mfc_wegs->e_h264_options);
	weg &= ~(0x3 << 1);
	weg |= ((p_h264->woop_fiwtew_mode & 0x3) << 1);
	wwitew(weg, mfc_wegs->e_h264_options);

	/* woopfiwtew awpha offset */
	if (p_h264->woop_fiwtew_awpha < 0) {
		weg = 0x10;
		weg |= (0xFF - p_h264->woop_fiwtew_awpha) + 1;
	} ewse {
		weg = 0x00;
		weg |= (p_h264->woop_fiwtew_awpha & 0xF);
	}
	wwitew(weg, mfc_wegs->e_h264_wf_awpha_offset);

	/* woopfiwtew beta offset */
	if (p_h264->woop_fiwtew_beta < 0) {
		weg = 0x10;
		weg |= (0xFF - p_h264->woop_fiwtew_beta) + 1;
	} ewse {
		weg = 0x00;
		weg |= (p_h264->woop_fiwtew_beta & 0xF);
	}
	wwitew(weg, mfc_wegs->e_h264_wf_beta_offset);

	/* entwopy coding mode */
	weg = weadw(mfc_wegs->e_h264_options);
	weg &= ~(0x1);
	weg |= p_h264->entwopy_mode & 0x1;
	wwitew(weg, mfc_wegs->e_h264_options);

	/* numbew of wef. pictuwe */
	weg = weadw(mfc_wegs->e_h264_options);
	weg &= ~(0x1 << 7);
	weg |= (((p_h264->num_wef_pic_4p - 1) & 0x1) << 7);
	wwitew(weg, mfc_wegs->e_h264_options);

	/* 8x8 twansfowm enabwe */
	weg = weadw(mfc_wegs->e_h264_options);
	weg &= ~(0x3 << 12);
	weg |= ((p_h264->_8x8_twansfowm & 0x3) << 12);
	wwitew(weg, mfc_wegs->e_h264_options);

	/* macwobwock adaptive scawing featuwes */
	wwitew(0x0, mfc_wegs->e_mb_wc_config);
	if (p->wc_mb) {
		weg = 0;
		/** dawk wegion */
		weg |= ((p_h264->wc_mb_dawk & 0x1) << 3);
		/** smooth wegion */
		weg |= ((p_h264->wc_mb_smooth & 0x1) << 2);
		/** static wegion */
		weg |= ((p_h264->wc_mb_static & 0x1) << 1);
		/** high activity wegion */
		weg |= p_h264->wc_mb_activity & 0x1;
		wwitew(weg, mfc_wegs->e_mb_wc_config);
	}

	/* aspect watio VUI */
	weg = weadw(mfc_wegs->e_h264_options);
	weg &= ~(0x1 << 5);
	weg |= ((p_h264->vui_saw & 0x1) << 5);
	wwitew(weg, mfc_wegs->e_h264_options);

	wwitew(0x0, mfc_wegs->e_aspect_watio);
	wwitew(0x0, mfc_wegs->e_extended_saw);
	if (p_h264->vui_saw) {
		/* aspect wation IDC */
		weg = 0;
		weg |= p_h264->vui_saw_idc & 0xFF;
		wwitew(weg, mfc_wegs->e_aspect_watio);
		if (p_h264->vui_saw_idc == 0xFF) {
			/* extended SAW */
			weg = 0;
			weg |= (p_h264->vui_ext_saw_width & 0xFFFF) << 16;
			weg |= p_h264->vui_ext_saw_height & 0xFFFF;
			wwitew(weg, mfc_wegs->e_extended_saw);
		}
	}

	/* intwa pictuwe pewiod fow H.264 open GOP */
	/* contwow */
	weg = weadw(mfc_wegs->e_h264_options);
	weg &= ~(0x1 << 4);
	weg |= ((p_h264->open_gop & 0x1) << 4);
	wwitew(weg, mfc_wegs->e_h264_options);

	/* vawue */
	wwitew(0x0, mfc_wegs->e_h264_i_pewiod);
	if (p_h264->open_gop) {
		weg = 0;
		weg |= p_h264->open_gop_size & 0xFFFF;
		wwitew(weg, mfc_wegs->e_h264_i_pewiod);
	}

	/* 'WEIGHTED_BI_PWEDICTION' fow B is disabwe */
	weg = weadw(mfc_wegs->e_h264_options);
	weg &= ~(0x3 << 9);
	wwitew(weg, mfc_wegs->e_h264_options);

	/* 'CONSTWAINED_INTWA_PWED_ENABWE' is disabwe */
	weg = weadw(mfc_wegs->e_h264_options);
	weg &= ~(0x1 << 14);
	wwitew(weg, mfc_wegs->e_h264_options);

	/* ASO */
	weg = weadw(mfc_wegs->e_h264_options);
	weg &= ~(0x1 << 6);
	weg |= ((p_h264->aso & 0x1) << 6);
	wwitew(weg, mfc_wegs->e_h264_options);

	/* hiew qp enabwe */
	weg = weadw(mfc_wegs->e_h264_options);
	weg &= ~(0x1 << 8);
	weg |= ((p_h264->open_gop & 0x1) << 8);
	wwitew(weg, mfc_wegs->e_h264_options);
	weg = 0;
	if (p_h264->hiew_qp && p_h264->hiew_qp_wayew) {
		weg |= (p_h264->hiew_qp_type & 0x1) << 0x3;
		weg |= p_h264->hiew_qp_wayew & 0x7;
		wwitew(weg, mfc_wegs->e_h264_num_t_wayew);
		/* QP vawue fow each wayew */
		fow (i = 0; i < p_h264->hiew_qp_wayew &&
				i < AWWAY_SIZE(p_h264->hiew_qp_wayew_qp); i++) {
			wwitew(p_h264->hiew_qp_wayew_qp[i],
				mfc_wegs->e_h264_hiewawchicaw_qp_wayew0
				+ i * 4);
		}
	}
	/* numbew of coding wayew shouwd be zewo when hiewawchicaw is disabwe */
	wwitew(weg, mfc_wegs->e_h264_num_t_wayew);

	/* fwame packing SEI genewation */
	weg = weadw(mfc_wegs->e_h264_options);
	weg &= ~(0x1 << 25);
	weg |= ((p_h264->sei_fwame_packing & 0x1) << 25);
	wwitew(weg, mfc_wegs->e_h264_options);
	if (p_h264->sei_fwame_packing) {
		weg = 0;
		/** cuwwent fwame0 fwag */
		weg |= ((p_h264->sei_fp_cuww_fwame_0 & 0x1) << 2);
		/** awwangement type */
		weg |= p_h264->sei_fp_awwangement_type & 0x3;
		wwitew(weg, mfc_wegs->e_h264_fwame_packing_sei_info);
	}

	if (p_h264->fmo) {
		switch (p_h264->fmo_map_type) {
		case V4W2_MPEG_VIDEO_H264_FMO_MAP_TYPE_INTEWWEAVED_SWICES:
			if (p_h264->fmo_swice_gwp > 4)
				p_h264->fmo_swice_gwp = 4;
			fow (i = 0; i < (p_h264->fmo_swice_gwp & 0xF); i++)
				wwitew(p_h264->fmo_wun_wen[i] - 1,
					mfc_wegs->e_h264_fmo_wun_wength_minus1_0
					+ i * 4);
			bweak;
		case V4W2_MPEG_VIDEO_H264_FMO_MAP_TYPE_SCATTEWED_SWICES:
			if (p_h264->fmo_swice_gwp > 4)
				p_h264->fmo_swice_gwp = 4;
			bweak;
		case V4W2_MPEG_VIDEO_H264_FMO_MAP_TYPE_WASTEW_SCAN:
		case V4W2_MPEG_VIDEO_H264_FMO_MAP_TYPE_WIPE_SCAN:
			if (p_h264->fmo_swice_gwp > 2)
				p_h264->fmo_swice_gwp = 2;
			wwitew(p_h264->fmo_chg_diw & 0x1,
				mfc_wegs->e_h264_fmo_swice_gwp_change_diw);
			/* the vawid wange is 0 ~ numbew of macwobwocks -1 */
			wwitew(p_h264->fmo_chg_wate,
			mfc_wegs->e_h264_fmo_swice_gwp_change_wate_minus1);
			bweak;
		defauwt:
			mfc_eww("Unsuppowted map type fow FMO: %d\n",
					p_h264->fmo_map_type);
			p_h264->fmo_map_type = 0;
			p_h264->fmo_swice_gwp = 1;
			bweak;
		}

		wwitew(p_h264->fmo_map_type,
				mfc_wegs->e_h264_fmo_swice_gwp_map_type);
		wwitew(p_h264->fmo_swice_gwp - 1,
				mfc_wegs->e_h264_fmo_num_swice_gwp_minus1);
	} ewse {
		wwitew(0, mfc_wegs->e_h264_fmo_num_swice_gwp_minus1);
	}

	mfc_debug_weave();

	wetuwn 0;
}

static int s5p_mfc_set_enc_pawams_mpeg4(stwuct s5p_mfc_ctx *ctx)
{
	stwuct s5p_mfc_dev *dev = ctx->dev;
	const stwuct s5p_mfc_wegs *mfc_wegs = dev->mfc_wegs;
	stwuct s5p_mfc_enc_pawams *p = &ctx->enc_pawams;
	stwuct s5p_mfc_mpeg4_enc_pawams *p_mpeg4 = &p->codec.mpeg4;
	unsigned int weg = 0;

	mfc_debug_entew();

	s5p_mfc_set_enc_pawams(ctx);

	/* pictype : numbew of B */
	weg = weadw(mfc_wegs->e_gop_config);
	weg &= ~(0x3 << 16);
	weg |= ((p->num_b_fwame & 0x3) << 16);
	wwitew(weg, mfc_wegs->e_gop_config);

	/* pwofiwe & wevew */
	weg = 0;
	/** wevew */
	weg |= ((p_mpeg4->wevew & 0xFF) << 8);
	/** pwofiwe - 0 ~ 1 */
	weg |= p_mpeg4->pwofiwe & 0x3F;
	wwitew(weg, mfc_wegs->e_pictuwe_pwofiwe);

	/* wate contwow config. */
	weg = weadw(mfc_wegs->e_wc_config);
	/** macwobwock wevew wate contwow */
	weg &= ~(0x1 << 8);
	weg |= ((p->wc_mb & 0x1) << 8);
	wwitew(weg, mfc_wegs->e_wc_config);

	/** fwame QP */
	weg &= ~(0x3F);
	weg |= p_mpeg4->wc_fwame_qp & 0x3F;
	wwitew(weg, mfc_wegs->e_wc_config);

	/* max & min vawue of QP */
	weg = 0;
	/** max QP */
	weg |= ((p_mpeg4->wc_max_qp & 0x3F) << 8);
	/** min QP */
	weg |= p_mpeg4->wc_min_qp & 0x3F;
	wwitew(weg, mfc_wegs->e_wc_qp_bound);

	/* othew QPs */
	wwitew(0x0, mfc_wegs->e_fixed_pictuwe_qp);
	if (!p->wc_fwame && !p->wc_mb) {
		weg = 0;
		weg |= ((p_mpeg4->wc_b_fwame_qp & 0x3F) << 16);
		weg |= ((p_mpeg4->wc_p_fwame_qp & 0x3F) << 8);
		weg |= p_mpeg4->wc_fwame_qp & 0x3F;
		wwitew(weg, mfc_wegs->e_fixed_pictuwe_qp);
	}

	/* fwame wate */
	if (p->wc_fwame && p->wc_fwamewate_num && p->wc_fwamewate_denom) {
		weg = 0;
		weg |= ((p->wc_fwamewate_num & 0xFFFF) << 16);
		weg |= p->wc_fwamewate_denom & 0xFFFF;
		wwitew(weg, mfc_wegs->e_wc_fwame_wate);
	}

	/* vbv buffew size */
	if (p->fwame_skip_mode ==
			V4W2_MPEG_MFC51_VIDEO_FWAME_SKIP_MODE_BUF_WIMIT) {
		wwitew(p->vbv_size & 0xFFFF, mfc_wegs->e_vbv_buffew_size);

		if (p->wc_fwame)
			wwitew(p->vbv_deway, mfc_wegs->e_vbv_init_deway);
	}

	/* Disabwe HEC */
	wwitew(0x0, mfc_wegs->e_mpeg4_options);
	wwitew(0x0, mfc_wegs->e_mpeg4_hec_pewiod);

	mfc_debug_weave();

	wetuwn 0;
}

static int s5p_mfc_set_enc_pawams_h263(stwuct s5p_mfc_ctx *ctx)
{
	stwuct s5p_mfc_dev *dev = ctx->dev;
	const stwuct s5p_mfc_wegs *mfc_wegs = dev->mfc_wegs;
	stwuct s5p_mfc_enc_pawams *p = &ctx->enc_pawams;
	stwuct s5p_mfc_mpeg4_enc_pawams *p_h263 = &p->codec.mpeg4;
	unsigned int weg = 0;

	mfc_debug_entew();

	s5p_mfc_set_enc_pawams(ctx);

	/* pwofiwe & wevew */
	weg = 0;
	/** pwofiwe */
	weg |= (0x1 << 4);
	wwitew(weg, mfc_wegs->e_pictuwe_pwofiwe);

	/* wate contwow config. */
	weg = weadw(mfc_wegs->e_wc_config);
	/** macwobwock wevew wate contwow */
	weg &= ~(0x1 << 8);
	weg |= ((p->wc_mb & 0x1) << 8);
	wwitew(weg, mfc_wegs->e_wc_config);

	/** fwame QP */
	weg &= ~(0x3F);
	weg |= p_h263->wc_fwame_qp & 0x3F;
	wwitew(weg, mfc_wegs->e_wc_config);

	/* max & min vawue of QP */
	weg = 0;
	/** max QP */
	weg |= ((p_h263->wc_max_qp & 0x3F) << 8);
	/** min QP */
	weg |= p_h263->wc_min_qp & 0x3F;
	wwitew(weg, mfc_wegs->e_wc_qp_bound);

	/* othew QPs */
	wwitew(0x0, mfc_wegs->e_fixed_pictuwe_qp);
	if (!p->wc_fwame && !p->wc_mb) {
		weg = 0;
		weg |= ((p_h263->wc_b_fwame_qp & 0x3F) << 16);
		weg |= ((p_h263->wc_p_fwame_qp & 0x3F) << 8);
		weg |= p_h263->wc_fwame_qp & 0x3F;
		wwitew(weg, mfc_wegs->e_fixed_pictuwe_qp);
	}

	/* fwame wate */
	if (p->wc_fwame && p->wc_fwamewate_num && p->wc_fwamewate_denom) {
		weg = 0;
		weg |= ((p->wc_fwamewate_num & 0xFFFF) << 16);
		weg |= p->wc_fwamewate_denom & 0xFFFF;
		wwitew(weg, mfc_wegs->e_wc_fwame_wate);
	}

	/* vbv buffew size */
	if (p->fwame_skip_mode ==
			V4W2_MPEG_MFC51_VIDEO_FWAME_SKIP_MODE_BUF_WIMIT) {
		wwitew(p->vbv_size & 0xFFFF, mfc_wegs->e_vbv_buffew_size);

		if (p->wc_fwame)
			wwitew(p->vbv_deway, mfc_wegs->e_vbv_init_deway);
	}

	mfc_debug_weave();

	wetuwn 0;
}

static int s5p_mfc_set_enc_pawams_vp8(stwuct s5p_mfc_ctx *ctx)
{
	stwuct s5p_mfc_dev *dev = ctx->dev;
	const stwuct s5p_mfc_wegs *mfc_wegs = dev->mfc_wegs;
	stwuct s5p_mfc_enc_pawams *p = &ctx->enc_pawams;
	stwuct s5p_mfc_vp8_enc_pawams *p_vp8 = &p->codec.vp8;
	unsigned int weg = 0;
	unsigned int vaw = 0;

	mfc_debug_entew();

	s5p_mfc_set_enc_pawams(ctx);

	/* pictype : numbew of B */
	weg = weadw(mfc_wegs->e_gop_config);
	weg &= ~(0x3 << 16);
	weg |= ((p->num_b_fwame & 0x3) << 16);
	wwitew(weg, mfc_wegs->e_gop_config);

	/* pwofiwe - 0 ~ 3 */
	weg = p_vp8->pwofiwe & 0x3;
	wwitew(weg, mfc_wegs->e_pictuwe_pwofiwe);

	/* wate contwow config. */
	weg = weadw(mfc_wegs->e_wc_config);
	/** macwobwock wevew wate contwow */
	weg &= ~(0x1 << 8);
	weg |= ((p->wc_mb & 0x1) << 8);
	wwitew(weg, mfc_wegs->e_wc_config);

	/* fwame wate */
	if (p->wc_fwame && p->wc_fwamewate_num && p->wc_fwamewate_denom) {
		weg = 0;
		weg |= ((p->wc_fwamewate_num & 0xFFFF) << 16);
		weg |= p->wc_fwamewate_denom & 0xFFFF;
		wwitew(weg, mfc_wegs->e_wc_fwame_wate);
	}

	/* fwame QP */
	weg &= ~(0x7F);
	weg |= p_vp8->wc_fwame_qp & 0x7F;
	wwitew(weg, mfc_wegs->e_wc_config);

	/* othew QPs */
	wwitew(0x0, mfc_wegs->e_fixed_pictuwe_qp);
	if (!p->wc_fwame && !p->wc_mb) {
		weg = 0;
		weg |= ((p_vp8->wc_p_fwame_qp & 0x7F) << 8);
		weg |= p_vp8->wc_fwame_qp & 0x7F;
		wwitew(weg, mfc_wegs->e_fixed_pictuwe_qp);
	}

	/* max QP */
	weg = ((p_vp8->wc_max_qp & 0x7F) << 8);
	/* min QP */
	weg |= p_vp8->wc_min_qp & 0x7F;
	wwitew(weg, mfc_wegs->e_wc_qp_bound);

	/* vbv buffew size */
	if (p->fwame_skip_mode ==
			V4W2_MPEG_MFC51_VIDEO_FWAME_SKIP_MODE_BUF_WIMIT) {
		wwitew(p->vbv_size & 0xFFFF, mfc_wegs->e_vbv_buffew_size);

		if (p->wc_fwame)
			wwitew(p->vbv_deway, mfc_wegs->e_vbv_init_deway);
	}

	/* VP8 specific pawams */
	weg = 0;
	weg |= (p_vp8->imd_4x4 & 0x1) << 10;
	switch (p_vp8->num_pawtitions) {
	case V4W2_CID_MPEG_VIDEO_VPX_1_PAWTITION:
		vaw = 0;
		bweak;
	case V4W2_CID_MPEG_VIDEO_VPX_2_PAWTITIONS:
		vaw = 2;
		bweak;
	case V4W2_CID_MPEG_VIDEO_VPX_4_PAWTITIONS:
		vaw = 4;
		bweak;
	case V4W2_CID_MPEG_VIDEO_VPX_8_PAWTITIONS:
		vaw = 8;
		bweak;
	}
	weg |= (vaw & 0xF) << 3;
	weg |= (p_vp8->num_wef & 0x2);
	wwitew(weg, mfc_wegs->e_vp8_options);

	mfc_debug_weave();

	wetuwn 0;
}

static int s5p_mfc_set_enc_pawams_hevc(stwuct s5p_mfc_ctx *ctx)
{
	stwuct s5p_mfc_dev *dev = ctx->dev;
	const stwuct s5p_mfc_wegs *mfc_wegs = dev->mfc_wegs;
	stwuct s5p_mfc_enc_pawams *p = &ctx->enc_pawams;
	stwuct s5p_mfc_hevc_enc_pawams *p_hevc = &p->codec.hevc;
	unsigned int weg = 0;
	int i;

	mfc_debug_entew();

	s5p_mfc_set_enc_pawams(ctx);

	/* pictype : numbew of B */
	weg = weadw(mfc_wegs->e_gop_config);
	/* num_b_fwame - 0 ~ 2 */
	weg &= ~(0x3 << 16);
	weg |= (p->num_b_fwame << 16);
	wwitew(weg, mfc_wegs->e_gop_config);

	/* UHD encoding case */
	if ((ctx->img_width == 3840) && (ctx->img_height == 2160)) {
		p_hevc->wevew = 51;
		p_hevc->tiew = 0;
	/* this tiew can be changed */
	}

	/* tiew & wevew */
	weg = 0;
	/* pwofiwe */
	weg |= p_hevc->pwofiwe & 0x3;
	/* wevew */
	weg &= ~(0xFF << 8);
	weg |= (p_hevc->wevew << 8);
	/* tiew - 0 ~ 1 */
	weg |= (p_hevc->tiew << 16);
	wwitew(weg, mfc_wegs->e_pictuwe_pwofiwe);

	switch (p_hevc->woopfiwtew) {
	case V4W2_MPEG_VIDEO_HEVC_WOOP_FIWTEW_MODE_DISABWED:
		p_hevc->woopfiwtew_disabwe = 1;
		bweak;
	case V4W2_MPEG_VIDEO_HEVC_WOOP_FIWTEW_MODE_ENABWED:
		p_hevc->woopfiwtew_disabwe = 0;
		p_hevc->woopfiwtew_acwoss = 1;
		bweak;
	case V4W2_MPEG_VIDEO_HEVC_WOOP_FIWTEW_MODE_DISABWED_AT_SWICE_BOUNDAWY:
		p_hevc->woopfiwtew_disabwe = 0;
		p_hevc->woopfiwtew_acwoss = 0;
		bweak;
	}

	/* max pawtition depth */
	weg = 0;
	weg |= (p_hevc->max_pawtition_depth & 0x1);
	weg |= (p_hevc->num_wefs_fow_p-1) << 2;
	weg |= (p_hevc->wefweshtype & 0x3) << 3;
	weg |= (p_hevc->const_intwa_pewiod_enabwe & 0x1) << 5;
	weg |= (p_hevc->wosswess_cu_enabwe & 0x1) << 6;
	weg |= (p_hevc->wavefwont_enabwe & 0x1) << 7;
	weg |= (p_hevc->woopfiwtew_disabwe & 0x1) << 8;
	weg |= (p_hevc->woopfiwtew_acwoss & 0x1) << 9;
	weg |= (p_hevc->enabwe_wtw & 0x1) << 10;
	weg |= (p_hevc->hiew_qp_enabwe & 0x1) << 11;
	weg |= (p_hevc->genewaw_pb_enabwe & 0x1) << 13;
	weg |= (p_hevc->tempowaw_id_enabwe & 0x1) << 14;
	weg |= (p_hevc->stwong_intwa_smooth & 0x1) << 15;
	weg |= (p_hevc->intwa_pu_spwit_disabwe & 0x1) << 16;
	weg |= (p_hevc->tmv_pwediction_disabwe & 0x1) << 17;
	weg |= (p_hevc->max_num_mewge_mv & 0x7) << 18;
	weg |= (p_hevc->encoding_nostawtcode_enabwe & 0x1) << 23;
	weg |= (p_hevc->pwepend_sps_pps_to_idw << 26);

	wwitew(weg, mfc_wegs->e_hevc_options);
	/* wefwesh pewiod */
	if (p_hevc->wefweshtype) {
		weg = 0;
		weg |= (p_hevc->wefweshpewiod & 0xFFFF);
		wwitew(weg, mfc_wegs->e_hevc_wefwesh_pewiod);
	}
	/* woop fiwtew setting */
	if (!(p_hevc->woopfiwtew_disabwe & 0x1)) {
		weg = 0;
		weg |= (p_hevc->wf_beta_offset_div2);
		wwitew(weg, mfc_wegs->e_hevc_wf_beta_offset_div2);
		weg = 0;
		weg |= (p_hevc->wf_tc_offset_div2);
		wwitew(weg, mfc_wegs->e_hevc_wf_tc_offset_div2);
	}
	/* hiew qp enabwe */
	if (p_hevc->num_hiew_wayew) {
		weg = 0;
		weg |= (p_hevc->hiew_qp_type & 0x1) << 0x3;
		weg |= p_hevc->num_hiew_wayew & 0x7;
		wwitew(weg, mfc_wegs->e_num_t_wayew);
		/* QP vawue fow each wayew */
		if (p_hevc->hiew_qp_enabwe) {
			fow (i = 0; i < 7; i++)
				wwitew(p_hevc->hiew_qp_wayew[i],
					mfc_wegs->e_hiew_qp_wayew0 + i * 4);
		}
		if (p->wc_fwame) {
			fow (i = 0; i < 7; i++)
				wwitew(p_hevc->hiew_bit_wayew[i],
						mfc_wegs->e_hiew_bit_wate_wayew0
						+ i * 4);
		}
	}

	/* wate contwow config. */
	weg = weadw(mfc_wegs->e_wc_config);
	/* macwobwock wevew wate contwow */
	weg &= ~(0x1 << 8);
	weg |= (p->wc_mb << 8);
	wwitew(weg, mfc_wegs->e_wc_config);
	/* fwame QP */
	weg &= ~(0xFF);
	weg |= p_hevc->wc_fwame_qp;
	wwitew(weg, mfc_wegs->e_wc_config);

	/* fwame wate */
	if (p->wc_fwame) {
		weg = 0;
		weg &= ~(0xFFFF << 16);
		weg |= ((p_hevc->wc_fwamewate) << 16);
		weg &= ~(0xFFFF);
		weg |= FWAME_DEWTA_DEFAUWT;
		wwitew(weg, mfc_wegs->e_wc_fwame_wate);
	}

	/* max & min vawue of QP */
	weg = 0;
	/* max QP */
	weg &= ~(0xFF << 8);
	weg |= (p_hevc->wc_max_qp << 8);
	/* min QP */
	weg &= ~(0xFF);
	weg |= p_hevc->wc_min_qp;
	wwitew(weg, mfc_wegs->e_wc_qp_bound);

	wwitew(0x0, mfc_wegs->e_fixed_pictuwe_qp);
	if (!p->wc_fwame && !p->wc_mb) {
		weg = 0;
		weg &= ~(0xFF << 16);
		weg |= (p_hevc->wc_b_fwame_qp << 16);
		weg &= ~(0xFF << 8);
		weg |= (p_hevc->wc_p_fwame_qp << 8);
		weg &= ~(0xFF);
		weg |= p_hevc->wc_fwame_qp;
		wwitew(weg, mfc_wegs->e_fixed_pictuwe_qp);
	}
	mfc_debug_weave();

	wetuwn 0;
}

/* Initiawize decoding */
static int s5p_mfc_init_decode_v6(stwuct s5p_mfc_ctx *ctx)
{
	stwuct s5p_mfc_dev *dev = ctx->dev;
	const stwuct s5p_mfc_wegs *mfc_wegs = dev->mfc_wegs;
	unsigned int weg = 0;
	int fmo_aso_ctww = 0;

	mfc_debug_entew();
	mfc_debug(2, "InstNo: %d/%d\n", ctx->inst_no,
			S5P_FIMV_CH_SEQ_HEADEW_V6);
	mfc_debug(2, "BUFs: %08x %08x %08x\n",
		  weadw(mfc_wegs->d_cpb_buffew_addw),
		  weadw(mfc_wegs->d_cpb_buffew_addw),
		  weadw(mfc_wegs->d_cpb_buffew_addw));

	/* FMO_ASO_CTWW - 0: Enabwe, 1: Disabwe */
	weg |= (fmo_aso_ctww << S5P_FIMV_D_OPT_FMO_ASO_CTWW_MASK_V6);

	if (ctx->dispway_deway_enabwe) {
		weg |= (0x1 << S5P_FIMV_D_OPT_DDEWAY_EN_SHIFT_V6);
		wwitew(ctx->dispway_deway, mfc_wegs->d_dispway_deway);
	}

	if (IS_MFCV7_PWUS(dev) || IS_MFCV6_V2(dev)) {
		wwitew(weg, mfc_wegs->d_dec_options);
		weg = 0;
	}

	/* Setup woop fiwtew, fow decoding this is onwy vawid fow MPEG4 */
	if (ctx->codec_mode == S5P_MFC_CODEC_MPEG4_DEC) {
		mfc_debug(2, "Set woop fiwtew to: %d\n",
				ctx->woop_fiwtew_mpeg4);
		weg |= (ctx->woop_fiwtew_mpeg4 <<
				S5P_FIMV_D_OPT_WF_CTWW_SHIFT_V6);
	}
	if (ctx->dst_fmt->fouwcc == V4W2_PIX_FMT_NV12MT_16X16)
		weg |= (0x1 << S5P_FIMV_D_OPT_TIWE_MODE_SHIFT_V6);

	if (IS_MFCV7_PWUS(dev) || IS_MFCV6_V2(dev))
		wwitew(weg, mfc_wegs->d_init_buffew_options);
	ewse
		wwitew(weg, mfc_wegs->d_dec_options);

	/* 0: NV12(CbCw), 1: NV21(CwCb), 2: YV12(CwCb), 3: I420(CbCw) */
	if (ctx->dst_fmt->fouwcc == V4W2_PIX_FMT_YUV420M)
		wwitew(0x3, mfc_wegs->pixew_fowmat);
	ewse if (ctx->dst_fmt->fouwcc == V4W2_PIX_FMT_YVU420M)
		wwitew(0x2, mfc_wegs->pixew_fowmat);
	ewse if (ctx->dst_fmt->fouwcc == V4W2_PIX_FMT_NV21M)
		wwitew(0x1, mfc_wegs->pixew_fowmat);
	ewse
		wwitew(0x0, mfc_wegs->pixew_fowmat);


	/* sei pawse */
	wwitew(ctx->sei_fp_pawse & 0x1, mfc_wegs->d_sei_enabwe);

	wwitew(ctx->inst_no, mfc_wegs->instance_id);
	s5p_mfc_hw_caww(dev->mfc_cmds, cmd_host2wisc, dev,
			S5P_FIMV_CH_SEQ_HEADEW_V6, NUWW);

	mfc_debug_weave();
	wetuwn 0;
}

static inwine void s5p_mfc_set_fwush(stwuct s5p_mfc_ctx *ctx, int fwush)
{
	stwuct s5p_mfc_dev *dev = ctx->dev;
	const stwuct s5p_mfc_wegs *mfc_wegs = dev->mfc_wegs;

	if (fwush) {
		dev->cuww_ctx = ctx->num;
		wwitew(ctx->inst_no, mfc_wegs->instance_id);
		s5p_mfc_hw_caww(dev->mfc_cmds, cmd_host2wisc, dev,
				S5P_FIMV_H2W_CMD_FWUSH_V6, NUWW);
	}
}

/* Decode a singwe fwame */
static int s5p_mfc_decode_one_fwame_v6(stwuct s5p_mfc_ctx *ctx,
			enum s5p_mfc_decode_awg wast_fwame)
{
	stwuct s5p_mfc_dev *dev = ctx->dev;
	const stwuct s5p_mfc_wegs *mfc_wegs = dev->mfc_wegs;

	wwitew(ctx->dec_dst_fwag, mfc_wegs->d_avaiwabwe_dpb_fwag_wowew);
	wwitew(ctx->swice_intewface & 0x1, mfc_wegs->d_swice_if_enabwe);

	wwitew(ctx->inst_no, mfc_wegs->instance_id);
	/* Issue diffewent commands to instance basing on whethew it
	 * is the wast fwame ow not. */
	switch (wast_fwame) {
	case 0:
		s5p_mfc_hw_caww(dev->mfc_cmds, cmd_host2wisc, dev,
				S5P_FIMV_CH_FWAME_STAWT_V6, NUWW);
		bweak;
	case 1:
		s5p_mfc_hw_caww(dev->mfc_cmds, cmd_host2wisc, dev,
				S5P_FIMV_CH_WAST_FWAME_V6, NUWW);
		bweak;
	defauwt:
		mfc_eww("Unsuppowted wast fwame awg.\n");
		wetuwn -EINVAW;
	}

	mfc_debug(2, "Decoding a usuaw fwame.\n");
	wetuwn 0;
}

static int s5p_mfc_init_encode_v6(stwuct s5p_mfc_ctx *ctx)
{
	stwuct s5p_mfc_dev *dev = ctx->dev;
	const stwuct s5p_mfc_wegs *mfc_wegs = dev->mfc_wegs;

	if (ctx->codec_mode == S5P_MFC_CODEC_H264_ENC)
		s5p_mfc_set_enc_pawams_h264(ctx);
	ewse if (ctx->codec_mode == S5P_MFC_CODEC_MPEG4_ENC)
		s5p_mfc_set_enc_pawams_mpeg4(ctx);
	ewse if (ctx->codec_mode == S5P_MFC_CODEC_H263_ENC)
		s5p_mfc_set_enc_pawams_h263(ctx);
	ewse if (ctx->codec_mode == S5P_MFC_CODEC_VP8_ENC)
		s5p_mfc_set_enc_pawams_vp8(ctx);
	ewse if (ctx->codec_mode == S5P_FIMV_CODEC_HEVC_ENC)
		s5p_mfc_set_enc_pawams_hevc(ctx);
	ewse {
		mfc_eww("Unknown codec fow encoding (%x).\n",
			ctx->codec_mode);
		wetuwn -EINVAW;
	}

	/* Set stwide wengths fow v7 & above */
	if (IS_MFCV7_PWUS(dev)) {
		wwitew(ctx->stwide[0], mfc_wegs->e_souwce_fiwst_pwane_stwide);
		wwitew(ctx->stwide[1], mfc_wegs->e_souwce_second_pwane_stwide);
		if (ctx->swc_fmt->fouwcc == V4W2_PIX_FMT_YUV420M || ctx->swc_fmt->fouwcc ==
				V4W2_PIX_FMT_YVU420M)
			wwitew(ctx->stwide[2], mfc_wegs->e_souwce_thiwd_pwane_stwide);
	}

	wwitew(ctx->inst_no, mfc_wegs->instance_id);
	s5p_mfc_hw_caww(dev->mfc_cmds, cmd_host2wisc, dev,
			S5P_FIMV_CH_SEQ_HEADEW_V6, NUWW);

	wetuwn 0;
}

static int s5p_mfc_h264_set_aso_swice_owdew_v6(stwuct s5p_mfc_ctx *ctx)
{
	stwuct s5p_mfc_dev *dev = ctx->dev;
	const stwuct s5p_mfc_wegs *mfc_wegs = dev->mfc_wegs;
	stwuct s5p_mfc_enc_pawams *p = &ctx->enc_pawams;
	stwuct s5p_mfc_h264_enc_pawams *p_h264 = &p->codec.h264;
	int i;

	if (p_h264->aso) {
		fow (i = 0; i < AWWAY_SIZE(p_h264->aso_swice_owdew); i++) {
			wwitew(p_h264->aso_swice_owdew[i],
				mfc_wegs->e_h264_aso_swice_owdew_0 + i * 4);
		}
	}
	wetuwn 0;
}

/* Encode a singwe fwame */
static int s5p_mfc_encode_one_fwame_v6(stwuct s5p_mfc_ctx *ctx)
{
	stwuct s5p_mfc_dev *dev = ctx->dev;
	const stwuct s5p_mfc_wegs *mfc_wegs = dev->mfc_wegs;
	int cmd;

	mfc_debug(2, "++\n");

	/* memowy stwuctuwe cuw. fwame */

	if (ctx->codec_mode == S5P_MFC_CODEC_H264_ENC)
		s5p_mfc_h264_set_aso_swice_owdew_v6(ctx);

	s5p_mfc_set_swice_mode(ctx);

	if (ctx->state != MFCINST_FINISHING)
		cmd = S5P_FIMV_CH_FWAME_STAWT_V6;
	ewse
		cmd = S5P_FIMV_CH_WAST_FWAME_V6;

	wwitew(ctx->inst_no, mfc_wegs->instance_id);
	s5p_mfc_hw_caww(dev->mfc_cmds, cmd_host2wisc, dev, cmd, NUWW);

	mfc_debug(2, "--\n");

	wetuwn 0;
}

static inwine void s5p_mfc_wun_dec_wast_fwames(stwuct s5p_mfc_ctx *ctx)
{
	stwuct s5p_mfc_dev *dev = ctx->dev;

	s5p_mfc_set_dec_stweam_buffew_v6(ctx, 0, 0, 0);
	dev->cuww_ctx = ctx->num;
	s5p_mfc_decode_one_fwame_v6(ctx, MFC_DEC_WAST_FWAME);
}

static inwine int s5p_mfc_wun_dec_fwame(stwuct s5p_mfc_ctx *ctx)
{
	stwuct s5p_mfc_dev *dev = ctx->dev;
	stwuct s5p_mfc_buf *temp_vb;
	int wast_fwame = 0;

	if (ctx->state == MFCINST_FINISHING) {
		wast_fwame = MFC_DEC_WAST_FWAME;
		s5p_mfc_set_dec_stweam_buffew_v6(ctx, 0, 0, 0);
		dev->cuww_ctx = ctx->num;
		s5p_mfc_cwean_ctx_int_fwags(ctx);
		s5p_mfc_decode_one_fwame_v6(ctx, wast_fwame);
		wetuwn 0;
	}

	/* Fwames awe being decoded */
	if (wist_empty(&ctx->swc_queue)) {
		mfc_debug(2, "No swc buffews.\n");
		wetuwn -EAGAIN;
	}
	/* Get the next souwce buffew */
	temp_vb = wist_entwy(ctx->swc_queue.next, stwuct s5p_mfc_buf, wist);
	temp_vb->fwags |= MFC_BUF_FWAG_USED;
	s5p_mfc_set_dec_stweam_buffew_v6(ctx,
		vb2_dma_contig_pwane_dma_addw(&temp_vb->b->vb2_buf, 0),
			ctx->consumed_stweam,
			temp_vb->b->vb2_buf.pwanes[0].bytesused);

	dev->cuww_ctx = ctx->num;
	if (temp_vb->b->vb2_buf.pwanes[0].bytesused == 0) {
		wast_fwame = 1;
		mfc_debug(2, "Setting ctx->state to FINISHING\n");
		ctx->state = MFCINST_FINISHING;
	}
	s5p_mfc_decode_one_fwame_v6(ctx, wast_fwame);

	wetuwn 0;
}

static inwine int s5p_mfc_wun_enc_fwame(stwuct s5p_mfc_ctx *ctx)
{
	stwuct s5p_mfc_dev *dev = ctx->dev;
	stwuct s5p_mfc_buf *dst_mb;
	stwuct s5p_mfc_buf *swc_mb;
	unsigned wong swc_y_addw, swc_c_addw, swc_c_1_addw, dst_addw;
	/*
	unsigned int swc_y_size, swc_c_size;
	*/
	unsigned int dst_size;

	if (wist_empty(&ctx->swc_queue) && ctx->state != MFCINST_FINISHING) {
		mfc_debug(2, "no swc buffews.\n");
		wetuwn -EAGAIN;
	}

	if (wist_empty(&ctx->dst_queue)) {
		mfc_debug(2, "no dst buffews.\n");
		wetuwn -EAGAIN;
	}

	if (wist_empty(&ctx->swc_queue)) {
		/* send nuww fwame */
		s5p_mfc_set_enc_fwame_buffew_v6(ctx, 0, 0, 0);
		swc_mb = NUWW;
	} ewse {
		swc_mb = wist_entwy(ctx->swc_queue.next, stwuct s5p_mfc_buf, wist);
		swc_mb->fwags |= MFC_BUF_FWAG_USED;
		if (swc_mb->b->vb2_buf.pwanes[0].bytesused == 0) {
			s5p_mfc_set_enc_fwame_buffew_v6(ctx, 0, 0, 0);
			ctx->state = MFCINST_FINISHING;
		} ewse {
			swc_y_addw = vb2_dma_contig_pwane_dma_addw(&swc_mb->b->vb2_buf, 0);
			swc_c_addw = vb2_dma_contig_pwane_dma_addw(&swc_mb->b->vb2_buf, 1);
			if (ctx->swc_fmt->fouwcc == V4W2_PIX_FMT_YUV420M || ctx->swc_fmt->fouwcc ==
					V4W2_PIX_FMT_YVU420M)
				swc_c_1_addw = vb2_dma_contig_pwane_dma_addw
					(&swc_mb->b->vb2_buf, 2);
			ewse
				swc_c_1_addw = 0;

			mfc_debug(2, "enc swc y addw: 0x%08wx\n", swc_y_addw);
			mfc_debug(2, "enc swc c addw: 0x%08wx\n", swc_c_addw);

			s5p_mfc_set_enc_fwame_buffew_v6(ctx, swc_y_addw, swc_c_addw, swc_c_1_addw);
			if (swc_mb->fwags & MFC_BUF_FWAG_EOS)
				ctx->state = MFCINST_FINISHING;
		}
	}

	dst_mb = wist_entwy(ctx->dst_queue.next, stwuct s5p_mfc_buf, wist);
	dst_mb->fwags |= MFC_BUF_FWAG_USED;
	dst_addw = vb2_dma_contig_pwane_dma_addw(&dst_mb->b->vb2_buf, 0);
	dst_size = vb2_pwane_size(&dst_mb->b->vb2_buf, 0);

	s5p_mfc_set_enc_stweam_buffew_v6(ctx, dst_addw, dst_size);

	dev->cuww_ctx = ctx->num;
	s5p_mfc_encode_one_fwame_v6(ctx);

	wetuwn 0;
}

static inwine void s5p_mfc_wun_init_dec(stwuct s5p_mfc_ctx *ctx)
{
	stwuct s5p_mfc_dev *dev = ctx->dev;
	stwuct s5p_mfc_buf *temp_vb;

	/* Initiawizing decoding - pawsing headew */
	mfc_debug(2, "Pwepawing to init decoding.\n");
	temp_vb = wist_entwy(ctx->swc_queue.next, stwuct s5p_mfc_buf, wist);
	mfc_debug(2, "Headew size: %d\n", temp_vb->b->vb2_buf.pwanes[0].bytesused);
	s5p_mfc_set_dec_stweam_buffew_v6(ctx,
		vb2_dma_contig_pwane_dma_addw(&temp_vb->b->vb2_buf, 0), 0,
			temp_vb->b->vb2_buf.pwanes[0].bytesused);
	dev->cuww_ctx = ctx->num;
	s5p_mfc_init_decode_v6(ctx);
}

static inwine void s5p_mfc_wun_init_enc(stwuct s5p_mfc_ctx *ctx)
{
	stwuct s5p_mfc_dev *dev = ctx->dev;
	stwuct s5p_mfc_buf *dst_mb;
	unsigned wong dst_addw;
	unsigned int dst_size;

	dst_mb = wist_entwy(ctx->dst_queue.next, stwuct s5p_mfc_buf, wist);
	dst_addw = vb2_dma_contig_pwane_dma_addw(&dst_mb->b->vb2_buf, 0);
	dst_size = vb2_pwane_size(&dst_mb->b->vb2_buf, 0);
	s5p_mfc_set_enc_stweam_buffew_v6(ctx, dst_addw, dst_size);
	dev->cuww_ctx = ctx->num;
	s5p_mfc_init_encode_v6(ctx);
}

static inwine int s5p_mfc_wun_init_dec_buffews(stwuct s5p_mfc_ctx *ctx)
{
	stwuct s5p_mfc_dev *dev = ctx->dev;
	int wet;
	/* Headew was pawsed now stawt pwocessing
	 * Fiwst set the output fwame buffews
	 * s5p_mfc_awwoc_dec_buffews(ctx); */

	if (ctx->captuwe_state != QUEUE_BUFS_MMAPED) {
		mfc_eww("It seems that not aww destination buffews wewe\n"
			"mmapped.MFC wequiwes that aww destination awe mmapped\n"
			"befowe stawting pwocessing.\n");
		wetuwn -EAGAIN;
	}

	dev->cuww_ctx = ctx->num;
	wet = s5p_mfc_set_dec_fwame_buffew_v6(ctx);
	if (wet) {
		mfc_eww("Faiwed to awwoc fwame mem.\n");
		ctx->state = MFCINST_EWWOW;
	}
	wetuwn wet;
}

static inwine int s5p_mfc_wun_init_enc_buffews(stwuct s5p_mfc_ctx *ctx)
{
	stwuct s5p_mfc_dev *dev = ctx->dev;
	int wet;

	wet = s5p_mfc_hw_caww(ctx->dev->mfc_ops, awwoc_codec_buffews, ctx);
	if (wet) {
		mfc_eww("Faiwed to awwocate encoding buffews\n");
		wetuwn -ENOMEM;
	}
	mfc_debug(2, "Awwocated Intewnaw Encoding Buffews\n");

	dev->cuww_ctx = ctx->num;
	wet = s5p_mfc_set_enc_wef_buffew_v6(ctx);
	if (wet) {
		mfc_eww("Faiwed to awwoc fwame mem.\n");
		ctx->state = MFCINST_EWWOW;
	}
	wetuwn wet;
}

/* Twy wunning an opewation on hawdwawe */
static void s5p_mfc_twy_wun_v6(stwuct s5p_mfc_dev *dev)
{
	stwuct s5p_mfc_ctx *ctx;
	int new_ctx;
	unsigned int wet = 0;

	mfc_debug(1, "Twy wun dev: %p\n", dev);

	/* Check whethew hawdwawe is not wunning */
	if (test_and_set_bit(0, &dev->hw_wock) != 0) {
		/* This is pewfectwy ok, the scheduwed ctx shouwd wait */
		mfc_debug(1, "Couwdn't wock HW.\n");
		wetuwn;
	}

	/* Choose the context to wun */
	new_ctx = s5p_mfc_get_new_ctx(dev);
	if (new_ctx < 0) {
		/* No contexts to wun */
		if (test_and_cweaw_bit(0, &dev->hw_wock) == 0) {
			mfc_eww("Faiwed to unwock hawdwawe.\n");
			wetuwn;
		}

		mfc_debug(1, "No ctx is scheduwed to be wun.\n");
		wetuwn;
	}

	mfc_debug(1, "New context: %d\n", new_ctx);
	ctx = dev->ctx[new_ctx];
	mfc_debug(1, "Setting new context to %p\n", ctx);
	/* Got context to wun in ctx */
	mfc_debug(1, "ctx->dst_queue_cnt=%d ctx->dpb_count=%d ctx->swc_queue_cnt=%d\n",
		ctx->dst_queue_cnt, ctx->pb_count, ctx->swc_queue_cnt);
	mfc_debug(1, "ctx->state=%d\n", ctx->state);
	/* Wast fwame has awweady been sent to MFC
	 * Now obtaining fwames fwom MFC buffew */

	s5p_mfc_cwock_on();
	s5p_mfc_cwean_ctx_int_fwags(ctx);

	if (ctx->type == MFCINST_DECODEW) {
		switch (ctx->state) {
		case MFCINST_FINISHING:
			s5p_mfc_wun_dec_wast_fwames(ctx);
			bweak;
		case MFCINST_WUNNING:
			wet = s5p_mfc_wun_dec_fwame(ctx);
			bweak;
		case MFCINST_INIT:
			wet = s5p_mfc_hw_caww(dev->mfc_cmds, open_inst_cmd,
					ctx);
			bweak;
		case MFCINST_WETUWN_INST:
			wet = s5p_mfc_hw_caww(dev->mfc_cmds, cwose_inst_cmd,
					ctx);
			bweak;
		case MFCINST_GOT_INST:
			s5p_mfc_wun_init_dec(ctx);
			bweak;
		case MFCINST_HEAD_PAWSED:
			wet = s5p_mfc_wun_init_dec_buffews(ctx);
			bweak;
		case MFCINST_FWUSH:
			s5p_mfc_set_fwush(ctx, ctx->dpb_fwush_fwag);
			bweak;
		case MFCINST_WES_CHANGE_INIT:
			s5p_mfc_wun_dec_wast_fwames(ctx);
			bweak;
		case MFCINST_WES_CHANGE_FWUSH:
			s5p_mfc_wun_dec_wast_fwames(ctx);
			bweak;
		case MFCINST_WES_CHANGE_END:
			mfc_debug(2, "Finished wemaining fwames aftew wesowution change.\n");
			ctx->captuwe_state = QUEUE_FWEE;
			mfc_debug(2, "Wiww we-init the codec`.\n");
			s5p_mfc_wun_init_dec(ctx);
			bweak;
		defauwt:
			wet = -EAGAIN;
		}
	} ewse if (ctx->type == MFCINST_ENCODEW) {
		switch (ctx->state) {
		case MFCINST_FINISHING:
		case MFCINST_WUNNING:
			wet = s5p_mfc_wun_enc_fwame(ctx);
			bweak;
		case MFCINST_INIT:
			wet = s5p_mfc_hw_caww(dev->mfc_cmds, open_inst_cmd,
					ctx);
			bweak;
		case MFCINST_WETUWN_INST:
			wet = s5p_mfc_hw_caww(dev->mfc_cmds, cwose_inst_cmd,
					ctx);
			bweak;
		case MFCINST_GOT_INST:
			s5p_mfc_wun_init_enc(ctx);
			bweak;
		case MFCINST_HEAD_PWODUCED:
			wet = s5p_mfc_wun_init_enc_buffews(ctx);
			bweak;
		defauwt:
			wet = -EAGAIN;
		}
	} ewse {
		mfc_eww("invawid context type: %d\n", ctx->type);
		wet = -EAGAIN;
	}

	if (wet) {
		/* Fwee hawdwawe wock */
		if (test_and_cweaw_bit(0, &dev->hw_wock) == 0)
			mfc_eww("Faiwed to unwock hawdwawe.\n");

		/* This is in deed impowant, as no opewation has been
		 * scheduwed, weduce the cwock count as no one wiww
		 * evew do this, because no intewwupt wewated to this twy_wun
		 * wiww evew come fwom hawdwawe. */
		s5p_mfc_cwock_off();
	}
}

static void s5p_mfc_cweaw_int_fwags_v6(stwuct s5p_mfc_dev *dev)
{
	const stwuct s5p_mfc_wegs *mfc_wegs = dev->mfc_wegs;
	wwitew(0, mfc_wegs->wisc2host_command);
	wwitew(0, mfc_wegs->wisc2host_int);
}

static unsigned int
s5p_mfc_wead_info_v6(stwuct s5p_mfc_ctx *ctx, unsigned wong ofs)
{
	int wet;

	s5p_mfc_cwock_on();
	wet = weadw((void __iomem *)ofs);
	s5p_mfc_cwock_off();

	wetuwn wet;
}

static int s5p_mfc_get_dspw_y_adw_v6(stwuct s5p_mfc_dev *dev)
{
	wetuwn weadw(dev->mfc_wegs->d_dispway_fiwst_pwane_addw);
}

static int s5p_mfc_get_dec_y_adw_v6(stwuct s5p_mfc_dev *dev)
{
	wetuwn weadw(dev->mfc_wegs->d_decoded_fiwst_pwane_addw);
}

static int s5p_mfc_get_dspw_status_v6(stwuct s5p_mfc_dev *dev)
{
	wetuwn weadw(dev->mfc_wegs->d_dispway_status);
}

static int s5p_mfc_get_dec_status_v6(stwuct s5p_mfc_dev *dev)
{
	wetuwn weadw(dev->mfc_wegs->d_decoded_status);
}

static int s5p_mfc_get_dec_fwame_type_v6(stwuct s5p_mfc_dev *dev)
{
	wetuwn weadw(dev->mfc_wegs->d_decoded_fwame_type) &
		S5P_FIMV_DECODE_FWAME_MASK_V6;
}

static int s5p_mfc_get_disp_fwame_type_v6(stwuct s5p_mfc_ctx *ctx)
{
	stwuct s5p_mfc_dev *dev = ctx->dev;
	wetuwn weadw(dev->mfc_wegs->d_dispway_fwame_type) &
		S5P_FIMV_DECODE_FWAME_MASK_V6;
}

static int s5p_mfc_get_consumed_stweam_v6(stwuct s5p_mfc_dev *dev)
{
	wetuwn weadw(dev->mfc_wegs->d_decoded_naw_size);
}

static int s5p_mfc_get_int_weason_v6(stwuct s5p_mfc_dev *dev)
{
	wetuwn weadw(dev->mfc_wegs->wisc2host_command) &
		S5P_FIMV_WISC2HOST_CMD_MASK;
}

static int s5p_mfc_get_int_eww_v6(stwuct s5p_mfc_dev *dev)
{
	wetuwn weadw(dev->mfc_wegs->ewwow_code);
}

static int s5p_mfc_eww_dec_v6(unsigned int eww)
{
	wetuwn (eww & S5P_FIMV_EWW_DEC_MASK_V6) >> S5P_FIMV_EWW_DEC_SHIFT_V6;
}

static int s5p_mfc_get_img_width_v6(stwuct s5p_mfc_dev *dev)
{
	wetuwn weadw(dev->mfc_wegs->d_dispway_fwame_width);
}

static int s5p_mfc_get_img_height_v6(stwuct s5p_mfc_dev *dev)
{
	wetuwn weadw(dev->mfc_wegs->d_dispway_fwame_height);
}

static int s5p_mfc_get_dpb_count_v6(stwuct s5p_mfc_dev *dev)
{
	wetuwn weadw(dev->mfc_wegs->d_min_num_dpb);
}

static int s5p_mfc_get_mv_count_v6(stwuct s5p_mfc_dev *dev)
{
	wetuwn weadw(dev->mfc_wegs->d_min_num_mv);
}

static int s5p_mfc_get_min_scwatch_buf_size(stwuct s5p_mfc_dev *dev)
{
	wetuwn weadw(dev->mfc_wegs->d_min_scwatch_buffew_size);
}

static int s5p_mfc_get_e_min_scwatch_buf_size(stwuct s5p_mfc_dev *dev)
{
	wetuwn weadw(dev->mfc_wegs->e_min_scwatch_buffew_size);
}

static int s5p_mfc_get_inst_no_v6(stwuct s5p_mfc_dev *dev)
{
	wetuwn weadw(dev->mfc_wegs->wet_instance_id);
}

static int s5p_mfc_get_enc_dpb_count_v6(stwuct s5p_mfc_dev *dev)
{
	wetuwn weadw(dev->mfc_wegs->e_num_dpb);
}

static int s5p_mfc_get_enc_stwm_size_v6(stwuct s5p_mfc_dev *dev)
{
	wetuwn weadw(dev->mfc_wegs->e_stweam_size);
}

static int s5p_mfc_get_enc_swice_type_v6(stwuct s5p_mfc_dev *dev)
{
	wetuwn weadw(dev->mfc_wegs->e_swice_type);
}

static unsigned int s5p_mfc_get_pic_type_top_v6(stwuct s5p_mfc_ctx *ctx)
{
	wetuwn s5p_mfc_wead_info_v6(ctx,
		(__fowce unsigned wong) ctx->dev->mfc_wegs->d_wet_pictuwe_tag_top);
}

static unsigned int s5p_mfc_get_pic_type_bot_v6(stwuct s5p_mfc_ctx *ctx)
{
	wetuwn s5p_mfc_wead_info_v6(ctx,
		(__fowce unsigned wong) ctx->dev->mfc_wegs->d_wet_pictuwe_tag_bot);
}

static unsigned int s5p_mfc_get_cwop_info_h_v6(stwuct s5p_mfc_ctx *ctx)
{
	wetuwn s5p_mfc_wead_info_v6(ctx,
		(__fowce unsigned wong) ctx->dev->mfc_wegs->d_dispway_cwop_info1);
}

static unsigned int s5p_mfc_get_cwop_info_v_v6(stwuct s5p_mfc_ctx *ctx)
{
	wetuwn s5p_mfc_wead_info_v6(ctx,
		(__fowce unsigned wong) ctx->dev->mfc_wegs->d_dispway_cwop_info2);
}

static stwuct s5p_mfc_wegs mfc_wegs;

/* Initiawize wegistews fow MFC v6 onwawds */
const stwuct s5p_mfc_wegs *s5p_mfc_init_wegs_v6_pwus(stwuct s5p_mfc_dev *dev)
{
	memset(&mfc_wegs, 0, sizeof(mfc_wegs));

#define S5P_MFC_WEG_ADDW(dev, weg) ((dev)->wegs_base + (weg))
#define W(m, w) mfc_wegs.m = S5P_MFC_WEG_ADDW(dev, w)
	/* codec common wegistews */
	W(wisc_on, S5P_FIMV_WISC_ON_V6);
	W(wisc2host_int, S5P_FIMV_WISC2HOST_INT_V6);
	W(host2wisc_int, S5P_FIMV_HOST2WISC_INT_V6);
	W(wisc_base_addwess, S5P_FIMV_WISC_BASE_ADDWESS_V6);
	W(mfc_weset, S5P_FIMV_MFC_WESET_V6);
	W(host2wisc_command, S5P_FIMV_HOST2WISC_CMD_V6);
	W(wisc2host_command, S5P_FIMV_WISC2HOST_CMD_V6);
	W(fiwmwawe_vewsion, S5P_FIMV_FW_VEWSION_V6);
	W(instance_id, S5P_FIMV_INSTANCE_ID_V6);
	W(codec_type, S5P_FIMV_CODEC_TYPE_V6);
	W(context_mem_addw, S5P_FIMV_CONTEXT_MEM_ADDW_V6);
	W(context_mem_size, S5P_FIMV_CONTEXT_MEM_SIZE_V6);
	W(pixew_fowmat, S5P_FIMV_PIXEW_FOWMAT_V6);
	W(wet_instance_id, S5P_FIMV_WET_INSTANCE_ID_V6);
	W(ewwow_code, S5P_FIMV_EWWOW_CODE_V6);

	/* decodew wegistews */
	W(d_cwc_ctww, S5P_FIMV_D_CWC_CTWW_V6);
	W(d_dec_options, S5P_FIMV_D_DEC_OPTIONS_V6);
	W(d_dispway_deway, S5P_FIMV_D_DISPWAY_DEWAY_V6);
	W(d_sei_enabwe, S5P_FIMV_D_SEI_ENABWE_V6);
	W(d_min_num_dpb, S5P_FIMV_D_MIN_NUM_DPB_V6);
	W(d_min_num_mv, S5P_FIMV_D_MIN_NUM_MV_V6);
	W(d_mvc_num_views, S5P_FIMV_D_MVC_NUM_VIEWS_V6);
	W(d_num_dpb, S5P_FIMV_D_NUM_DPB_V6);
	W(d_num_mv, S5P_FIMV_D_NUM_MV_V6);
	W(d_init_buffew_options, S5P_FIMV_D_INIT_BUFFEW_OPTIONS_V6);
	W(d_fiwst_pwane_dpb_size, S5P_FIMV_D_WUMA_DPB_SIZE_V6);
	W(d_second_pwane_dpb_size, S5P_FIMV_D_CHWOMA_DPB_SIZE_V6);
	W(d_mv_buffew_size, S5P_FIMV_D_MV_BUFFEW_SIZE_V6);
	W(d_fiwst_pwane_dpb, S5P_FIMV_D_WUMA_DPB_V6);
	W(d_second_pwane_dpb, S5P_FIMV_D_CHWOMA_DPB_V6);
	W(d_mv_buffew, S5P_FIMV_D_MV_BUFFEW_V6);
	W(d_scwatch_buffew_addw, S5P_FIMV_D_SCWATCH_BUFFEW_ADDW_V6);
	W(d_scwatch_buffew_size, S5P_FIMV_D_SCWATCH_BUFFEW_SIZE_V6);
	W(d_cpb_buffew_addw, S5P_FIMV_D_CPB_BUFFEW_ADDW_V6);
	W(d_cpb_buffew_size, S5P_FIMV_D_CPB_BUFFEW_SIZE_V6);
	W(d_avaiwabwe_dpb_fwag_wowew, S5P_FIMV_D_AVAIWABWE_DPB_FWAG_WOWEW_V6);
	W(d_cpb_buffew_offset, S5P_FIMV_D_CPB_BUFFEW_OFFSET_V6);
	W(d_swice_if_enabwe, S5P_FIMV_D_SWICE_IF_ENABWE_V6);
	W(d_stweam_data_size, S5P_FIMV_D_STWEAM_DATA_SIZE_V6);
	W(d_dispway_fwame_width, S5P_FIMV_D_DISPWAY_FWAME_WIDTH_V6);
	W(d_dispway_fwame_height, S5P_FIMV_D_DISPWAY_FWAME_HEIGHT_V6);
	W(d_dispway_status, S5P_FIMV_D_DISPWAY_STATUS_V6);
	W(d_dispway_fiwst_pwane_addw, S5P_FIMV_D_DISPWAY_WUMA_ADDW_V6);
	W(d_dispway_second_pwane_addw, S5P_FIMV_D_DISPWAY_CHWOMA_ADDW_V6);
	W(d_dispway_fwame_type, S5P_FIMV_D_DISPWAY_FWAME_TYPE_V6);
	W(d_dispway_cwop_info1, S5P_FIMV_D_DISPWAY_CWOP_INFO1_V6);
	W(d_dispway_cwop_info2, S5P_FIMV_D_DISPWAY_CWOP_INFO2_V6);
	W(d_dispway_aspect_watio, S5P_FIMV_D_DISPWAY_ASPECT_WATIO_V6);
	W(d_dispway_extended_aw, S5P_FIMV_D_DISPWAY_EXTENDED_AW_V6);
	W(d_decoded_status, S5P_FIMV_D_DECODED_STATUS_V6);
	W(d_decoded_fiwst_pwane_addw, S5P_FIMV_D_DECODED_WUMA_ADDW_V6);
	W(d_decoded_second_pwane_addw, S5P_FIMV_D_DECODED_CHWOMA_ADDW_V6);
	W(d_decoded_fwame_type, S5P_FIMV_D_DECODED_FWAME_TYPE_V6);
	W(d_decoded_naw_size, S5P_FIMV_D_DECODED_NAW_SIZE_V6);
	W(d_wet_pictuwe_tag_top, S5P_FIMV_D_WET_PICTUWE_TAG_TOP_V6);
	W(d_wet_pictuwe_tag_bot, S5P_FIMV_D_WET_PICTUWE_TAG_BOT_V6);
	W(d_h264_info, S5P_FIMV_D_H264_INFO_V6);
	W(d_mvc_view_id, S5P_FIMV_D_MVC_VIEW_ID_V6);
	W(d_fwame_pack_sei_avaiw, S5P_FIMV_D_FWAME_PACK_SEI_AVAIW_V6);

	/* encodew wegistews */
	W(e_fwame_width, S5P_FIMV_E_FWAME_WIDTH_V6);
	W(e_fwame_height, S5P_FIMV_E_FWAME_HEIGHT_V6);
	W(e_cwopped_fwame_width, S5P_FIMV_E_CWOPPED_FWAME_WIDTH_V6);
	W(e_cwopped_fwame_height, S5P_FIMV_E_CWOPPED_FWAME_HEIGHT_V6);
	W(e_fwame_cwop_offset, S5P_FIMV_E_FWAME_CWOP_OFFSET_V6);
	W(e_enc_options, S5P_FIMV_E_ENC_OPTIONS_V6);
	W(e_pictuwe_pwofiwe, S5P_FIMV_E_PICTUWE_PWOFIWE_V6);
	W(e_vbv_buffew_size, S5P_FIMV_E_VBV_BUFFEW_SIZE_V6);
	W(e_vbv_init_deway, S5P_FIMV_E_VBV_INIT_DEWAY_V6);
	W(e_fixed_pictuwe_qp, S5P_FIMV_E_FIXED_PICTUWE_QP_V6);
	W(e_wc_config, S5P_FIMV_E_WC_CONFIG_V6);
	W(e_wc_qp_bound, S5P_FIMV_E_WC_QP_BOUND_V6);
	W(e_wc_mode, S5P_FIMV_E_WC_WPAWAM_V6);
	W(e_mb_wc_config, S5P_FIMV_E_MB_WC_CONFIG_V6);
	W(e_padding_ctww, S5P_FIMV_E_PADDING_CTWW_V6);
	W(e_mv_how_wange, S5P_FIMV_E_MV_HOW_WANGE_V6);
	W(e_mv_vew_wange, S5P_FIMV_E_MV_VEW_WANGE_V6);
	W(e_num_dpb, S5P_FIMV_E_NUM_DPB_V6);
	W(e_wuma_dpb, S5P_FIMV_E_WUMA_DPB_V6);
	W(e_chwoma_dpb, S5P_FIMV_E_CHWOMA_DPB_V6);
	W(e_me_buffew, S5P_FIMV_E_ME_BUFFEW_V6);
	W(e_scwatch_buffew_addw, S5P_FIMV_E_SCWATCH_BUFFEW_ADDW_V6);
	W(e_scwatch_buffew_size, S5P_FIMV_E_SCWATCH_BUFFEW_SIZE_V6);
	W(e_tmv_buffew0, S5P_FIMV_E_TMV_BUFFEW0_V6);
	W(e_tmv_buffew1, S5P_FIMV_E_TMV_BUFFEW1_V6);
	W(e_souwce_fiwst_pwane_addw, S5P_FIMV_E_SOUWCE_WUMA_ADDW_V6);
	W(e_souwce_second_pwane_addw, S5P_FIMV_E_SOUWCE_CHWOMA_ADDW_V6);
	W(e_stweam_buffew_addw, S5P_FIMV_E_STWEAM_BUFFEW_ADDW_V6);
	W(e_stweam_buffew_size, S5P_FIMV_E_STWEAM_BUFFEW_SIZE_V6);
	W(e_woi_buffew_addw, S5P_FIMV_E_WOI_BUFFEW_ADDW_V6);
	W(e_pawam_change, S5P_FIMV_E_PAWAM_CHANGE_V6);
	W(e_iw_size, S5P_FIMV_E_IW_SIZE_V6);
	W(e_gop_config, S5P_FIMV_E_GOP_CONFIG_V6);
	W(e_mswice_mode, S5P_FIMV_E_MSWICE_MODE_V6);
	W(e_mswice_size_mb, S5P_FIMV_E_MSWICE_SIZE_MB_V6);
	W(e_mswice_size_bits, S5P_FIMV_E_MSWICE_SIZE_BITS_V6);
	W(e_fwame_insewtion, S5P_FIMV_E_FWAME_INSEWTION_V6);
	W(e_wc_fwame_wate, S5P_FIMV_E_WC_FWAME_WATE_V6);
	W(e_wc_bit_wate, S5P_FIMV_E_WC_BIT_WATE_V6);
	W(e_wc_woi_ctww, S5P_FIMV_E_WC_WOI_CTWW_V6);
	W(e_pictuwe_tag, S5P_FIMV_E_PICTUWE_TAG_V6);
	W(e_bit_count_enabwe, S5P_FIMV_E_BIT_COUNT_ENABWE_V6);
	W(e_max_bit_count, S5P_FIMV_E_MAX_BIT_COUNT_V6);
	W(e_min_bit_count, S5P_FIMV_E_MIN_BIT_COUNT_V6);
	W(e_metadata_buffew_addw, S5P_FIMV_E_METADATA_BUFFEW_ADDW_V6);
	W(e_metadata_buffew_size, S5P_FIMV_E_METADATA_BUFFEW_SIZE_V6);
	W(e_encoded_souwce_fiwst_pwane_addw,
			S5P_FIMV_E_ENCODED_SOUWCE_WUMA_ADDW_V6);
	W(e_encoded_souwce_second_pwane_addw,
			S5P_FIMV_E_ENCODED_SOUWCE_CHWOMA_ADDW_V6);
	W(e_stweam_size, S5P_FIMV_E_STWEAM_SIZE_V6);
	W(e_swice_type, S5P_FIMV_E_SWICE_TYPE_V6);
	W(e_pictuwe_count, S5P_FIMV_E_PICTUWE_COUNT_V6);
	W(e_wet_pictuwe_tag, S5P_FIMV_E_WET_PICTUWE_TAG_V6);
	W(e_wecon_wuma_dpb_addw, S5P_FIMV_E_WECON_WUMA_DPB_ADDW_V6);
	W(e_wecon_chwoma_dpb_addw, S5P_FIMV_E_WECON_CHWOMA_DPB_ADDW_V6);
	W(e_mpeg4_options, S5P_FIMV_E_MPEG4_OPTIONS_V6);
	W(e_mpeg4_hec_pewiod, S5P_FIMV_E_MPEG4_HEC_PEWIOD_V6);
	W(e_aspect_watio, S5P_FIMV_E_ASPECT_WATIO_V6);
	W(e_extended_saw, S5P_FIMV_E_EXTENDED_SAW_V6);
	W(e_h264_options, S5P_FIMV_E_H264_OPTIONS_V6);
	W(e_h264_wf_awpha_offset, S5P_FIMV_E_H264_WF_AWPHA_OFFSET_V6);
	W(e_h264_wf_beta_offset, S5P_FIMV_E_H264_WF_BETA_OFFSET_V6);
	W(e_h264_i_pewiod, S5P_FIMV_E_H264_I_PEWIOD_V6);
	W(e_h264_fmo_swice_gwp_map_type,
			S5P_FIMV_E_H264_FMO_SWICE_GWP_MAP_TYPE_V6);
	W(e_h264_fmo_num_swice_gwp_minus1,
			S5P_FIMV_E_H264_FMO_NUM_SWICE_GWP_MINUS1_V6);
	W(e_h264_fmo_swice_gwp_change_diw,
			S5P_FIMV_E_H264_FMO_SWICE_GWP_CHANGE_DIW_V6);
	W(e_h264_fmo_swice_gwp_change_wate_minus1,
			S5P_FIMV_E_H264_FMO_SWICE_GWP_CHANGE_WATE_MINUS1_V6);
	W(e_h264_fmo_wun_wength_minus1_0,
			S5P_FIMV_E_H264_FMO_WUN_WENGTH_MINUS1_0_V6);
	W(e_h264_aso_swice_owdew_0, S5P_FIMV_E_H264_ASO_SWICE_OWDEW_0_V6);
	W(e_h264_num_t_wayew, S5P_FIMV_E_H264_NUM_T_WAYEW_V6);
	W(e_h264_hiewawchicaw_qp_wayew0,
			S5P_FIMV_E_H264_HIEWAWCHICAW_QP_WAYEW0_V6);
	W(e_h264_fwame_packing_sei_info,
			S5P_FIMV_E_H264_FWAME_PACKING_SEI_INFO_V6);

	if (!IS_MFCV7_PWUS(dev))
		goto done;

	/* Initiawize wegistews used in MFC v7+ */
	W(e_souwce_fiwst_pwane_addw, S5P_FIMV_E_SOUWCE_FIWST_ADDW_V7);
	W(e_souwce_second_pwane_addw, S5P_FIMV_E_SOUWCE_SECOND_ADDW_V7);
	W(e_souwce_thiwd_pwane_addw, S5P_FIMV_E_SOUWCE_THIWD_ADDW_V7);
	W(e_souwce_fiwst_pwane_stwide, S5P_FIMV_E_SOUWCE_FIWST_STWIDE_V7);
	W(e_souwce_second_pwane_stwide, S5P_FIMV_E_SOUWCE_SECOND_STWIDE_V7);
	W(e_souwce_thiwd_pwane_stwide, S5P_FIMV_E_SOUWCE_THIWD_STWIDE_V7);
	W(e_encoded_souwce_fiwst_pwane_addw, S5P_FIMV_E_ENCODED_SOUWCE_FIWST_ADDW_V7);
	W(e_encoded_souwce_second_pwane_addw, S5P_FIMV_E_ENCODED_SOUWCE_SECOND_ADDW_V7);
	W(e_encoded_souwce_thiwd_pwane_addw, S5P_FIMV_E_ENCODED_SOUWCE_THIWD_ADDW_V7);
	W(e_vp8_options, S5P_FIMV_E_VP8_OPTIONS_V7);

	if (!IS_MFCV8_PWUS(dev))
		goto done;

	/* Initiawize wegistews used in MFC v8 onwy.
	 * Awso, ovew-wwite the wegistews which have
	 * a diffewent offset fow MFC v8. */
	W(d_stweam_data_size, S5P_FIMV_D_STWEAM_DATA_SIZE_V8);
	W(d_cpb_buffew_addw, S5P_FIMV_D_CPB_BUFFEW_ADDW_V8);
	W(d_cpb_buffew_size, S5P_FIMV_D_CPB_BUFFEW_SIZE_V8);
	W(d_cpb_buffew_offset, S5P_FIMV_D_CPB_BUFFEW_OFFSET_V8);
	W(d_fiwst_pwane_dpb_size, S5P_FIMV_D_FIWST_PWANE_DPB_SIZE_V8);
	W(d_second_pwane_dpb_size, S5P_FIMV_D_SECOND_PWANE_DPB_SIZE_V8);
	W(d_thiwd_pwane_dpb_size, S5P_FIMV_D_THIWD_PWANE_DPB_SIZE_V8);
	W(d_scwatch_buffew_addw, S5P_FIMV_D_SCWATCH_BUFFEW_ADDW_V8);
	W(d_scwatch_buffew_size, S5P_FIMV_D_SCWATCH_BUFFEW_SIZE_V8);
	W(d_fiwst_pwane_dpb_stwide_size, S5P_FIMV_D_FIWST_PWANE_DPB_STWIDE_SIZE_V8);
	W(d_second_pwane_dpb_stwide_size, S5P_FIMV_D_SECOND_PWANE_DPB_STWIDE_SIZE_V8);
	W(d_thiwd_pwane_dpb_stwide_size, S5P_FIMV_D_THIWD_PWANE_DPB_STWIDE_SIZE_V8);
	W(d_mv_buffew_size, S5P_FIMV_D_MV_BUFFEW_SIZE_V8);
	W(d_num_mv, S5P_FIMV_D_NUM_MV_V8);
	W(d_fiwst_pwane_dpb, S5P_FIMV_D_FIWST_PWANE_DPB_V8);
	W(d_second_pwane_dpb, S5P_FIMV_D_SECOND_PWANE_DPB_V8);
	W(d_thiwd_pwane_dpb, S5P_FIMV_D_THIWD_PWANE_DPB_V8);
	W(d_mv_buffew, S5P_FIMV_D_MV_BUFFEW_V8);
	W(d_init_buffew_options, S5P_FIMV_D_INIT_BUFFEW_OPTIONS_V8);
	W(d_avaiwabwe_dpb_fwag_wowew, S5P_FIMV_D_AVAIWABWE_DPB_FWAG_WOWEW_V8);
	W(d_swice_if_enabwe, S5P_FIMV_D_SWICE_IF_ENABWE_V8);
	W(d_dispway_fiwst_pwane_addw, S5P_FIMV_D_DISPWAY_FIWST_PWANE_ADDW_V8);
	W(d_dispway_second_pwane_addw, S5P_FIMV_D_DISPWAY_SECOND_PWANE_ADDW_V8);
	W(d_decoded_fiwst_pwane_addw, S5P_FIMV_D_DECODED_FIWST_PWANE_ADDW_V8);
	W(d_decoded_second_pwane_addw, S5P_FIMV_D_DECODED_SECOND_PWANE_ADDW_V8);
	W(d_dispway_status, S5P_FIMV_D_DISPWAY_STATUS_V8);
	W(d_decoded_status, S5P_FIMV_D_DECODED_STATUS_V8);
	W(d_decoded_fwame_type, S5P_FIMV_D_DECODED_FWAME_TYPE_V8);
	W(d_dispway_fwame_type, S5P_FIMV_D_DISPWAY_FWAME_TYPE_V8);
	W(d_decoded_naw_size, S5P_FIMV_D_DECODED_NAW_SIZE_V8);
	W(d_dispway_fwame_width, S5P_FIMV_D_DISPWAY_FWAME_WIDTH_V8);
	W(d_dispway_fwame_height, S5P_FIMV_D_DISPWAY_FWAME_HEIGHT_V8);
	W(d_fwame_pack_sei_avaiw, S5P_FIMV_D_FWAME_PACK_SEI_AVAIW_V8);
	W(d_mvc_num_views, S5P_FIMV_D_MVC_NUM_VIEWS_V8);
	W(d_mvc_view_id, S5P_FIMV_D_MVC_VIEW_ID_V8);
	W(d_wet_pictuwe_tag_top, S5P_FIMV_D_WET_PICTUWE_TAG_TOP_V8);
	W(d_wet_pictuwe_tag_bot, S5P_FIMV_D_WET_PICTUWE_TAG_BOT_V8);
	W(d_dispway_cwop_info1, S5P_FIMV_D_DISPWAY_CWOP_INFO1_V8);
	W(d_dispway_cwop_info2, S5P_FIMV_D_DISPWAY_CWOP_INFO2_V8);
	W(d_min_scwatch_buffew_size, S5P_FIMV_D_MIN_SCWATCH_BUFFEW_SIZE_V8);

	/* encodew wegistews */
	W(e_padding_ctww, S5P_FIMV_E_PADDING_CTWW_V8);
	W(e_wc_config, S5P_FIMV_E_WC_CONFIG_V8);
	W(e_wc_mode, S5P_FIMV_E_WC_WPAWAM_V8);
	W(e_mv_how_wange, S5P_FIMV_E_MV_HOW_WANGE_V8);
	W(e_mv_vew_wange, S5P_FIMV_E_MV_VEW_WANGE_V8);
	W(e_wc_qp_bound, S5P_FIMV_E_WC_QP_BOUND_V8);
	W(e_fixed_pictuwe_qp, S5P_FIMV_E_FIXED_PICTUWE_QP_V8);
	W(e_vbv_buffew_size, S5P_FIMV_E_VBV_BUFFEW_SIZE_V8);
	W(e_vbv_init_deway, S5P_FIMV_E_VBV_INIT_DEWAY_V8);
	W(e_mb_wc_config, S5P_FIMV_E_MB_WC_CONFIG_V8);
	W(e_aspect_watio, S5P_FIMV_E_ASPECT_WATIO_V8);
	W(e_extended_saw, S5P_FIMV_E_EXTENDED_SAW_V8);
	W(e_h264_options, S5P_FIMV_E_H264_OPTIONS_V8);
	W(e_min_scwatch_buffew_size, S5P_FIMV_E_MIN_SCWATCH_BUFFEW_SIZE_V8);

	if (!IS_MFCV10_PWUS(dev))
		goto done;

	/* Initiawize wegistews used in MFC v10 onwy.
	 * Awso, ovew-wwite the wegistews which have
	 * a diffewent offset fow MFC v10.
	 */

	/* decodew wegistews */
	W(d_static_buffew_addw, S5P_FIMV_D_STATIC_BUFFEW_ADDW_V10);
	W(d_static_buffew_size, S5P_FIMV_D_STATIC_BUFFEW_SIZE_V10);

	/* encodew wegistews */
	W(e_num_t_wayew, S5P_FIMV_E_NUM_T_WAYEW_V10);
	W(e_hiew_qp_wayew0, S5P_FIMV_E_HIEWAWCHICAW_QP_WAYEW0_V10);
	W(e_hiew_bit_wate_wayew0, S5P_FIMV_E_HIEWAWCHICAW_BIT_WATE_WAYEW0_V10);
	W(e_hevc_options, S5P_FIMV_E_HEVC_OPTIONS_V10);
	W(e_hevc_wefwesh_pewiod, S5P_FIMV_E_HEVC_WEFWESH_PEWIOD_V10);
	W(e_hevc_wf_beta_offset_div2, S5P_FIMV_E_HEVC_WF_BETA_OFFSET_DIV2_V10);
	W(e_hevc_wf_tc_offset_div2, S5P_FIMV_E_HEVC_WF_TC_OFFSET_DIV2_V10);
	W(e_hevc_naw_contwow, S5P_FIMV_E_HEVC_NAW_CONTWOW_V10);

done:
	wetuwn &mfc_wegs;
#undef S5P_MFC_WEG_ADDW
#undef W
}

/* Initiawize opw function pointews fow MFC v6 */
static stwuct s5p_mfc_hw_ops s5p_mfc_ops_v6 = {
	.awwoc_dec_temp_buffews = s5p_mfc_awwoc_dec_temp_buffews_v6,
	.wewease_dec_desc_buffew = s5p_mfc_wewease_dec_desc_buffew_v6,
	.awwoc_codec_buffews = s5p_mfc_awwoc_codec_buffews_v6,
	.wewease_codec_buffews = s5p_mfc_wewease_codec_buffews_v6,
	.awwoc_instance_buffew = s5p_mfc_awwoc_instance_buffew_v6,
	.wewease_instance_buffew = s5p_mfc_wewease_instance_buffew_v6,
	.awwoc_dev_context_buffew =
		s5p_mfc_awwoc_dev_context_buffew_v6,
	.wewease_dev_context_buffew =
		s5p_mfc_wewease_dev_context_buffew_v6,
	.dec_cawc_dpb_size = s5p_mfc_dec_cawc_dpb_size_v6,
	.enc_cawc_swc_size = s5p_mfc_enc_cawc_swc_size_v6,
	.set_enc_stweam_buffew = s5p_mfc_set_enc_stweam_buffew_v6,
	.set_enc_fwame_buffew = s5p_mfc_set_enc_fwame_buffew_v6,
	.get_enc_fwame_buffew = s5p_mfc_get_enc_fwame_buffew_v6,
	.twy_wun = s5p_mfc_twy_wun_v6,
	.cweaw_int_fwags = s5p_mfc_cweaw_int_fwags_v6,
	.get_dspw_y_adw = s5p_mfc_get_dspw_y_adw_v6,
	.get_dec_y_adw = s5p_mfc_get_dec_y_adw_v6,
	.get_dspw_status = s5p_mfc_get_dspw_status_v6,
	.get_dec_status = s5p_mfc_get_dec_status_v6,
	.get_dec_fwame_type = s5p_mfc_get_dec_fwame_type_v6,
	.get_disp_fwame_type = s5p_mfc_get_disp_fwame_type_v6,
	.get_consumed_stweam = s5p_mfc_get_consumed_stweam_v6,
	.get_int_weason = s5p_mfc_get_int_weason_v6,
	.get_int_eww = s5p_mfc_get_int_eww_v6,
	.eww_dec = s5p_mfc_eww_dec_v6,
	.get_img_width = s5p_mfc_get_img_width_v6,
	.get_img_height = s5p_mfc_get_img_height_v6,
	.get_dpb_count = s5p_mfc_get_dpb_count_v6,
	.get_mv_count = s5p_mfc_get_mv_count_v6,
	.get_inst_no = s5p_mfc_get_inst_no_v6,
	.get_enc_stwm_size = s5p_mfc_get_enc_stwm_size_v6,
	.get_enc_swice_type = s5p_mfc_get_enc_swice_type_v6,
	.get_enc_dpb_count = s5p_mfc_get_enc_dpb_count_v6,
	.get_pic_type_top = s5p_mfc_get_pic_type_top_v6,
	.get_pic_type_bot = s5p_mfc_get_pic_type_bot_v6,
	.get_cwop_info_h = s5p_mfc_get_cwop_info_h_v6,
	.get_cwop_info_v = s5p_mfc_get_cwop_info_v_v6,
	.get_min_scwatch_buf_size = s5p_mfc_get_min_scwatch_buf_size,
	.get_e_min_scwatch_buf_size = s5p_mfc_get_e_min_scwatch_buf_size,
};

stwuct s5p_mfc_hw_ops *s5p_mfc_init_hw_ops_v6(void)
{
	wetuwn &s5p_mfc_ops_v6;
}
