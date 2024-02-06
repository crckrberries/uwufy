// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Contains the viwtuaw decodew wogic. The functions hewe contwow the
 * twacing/TPG on a pew-fwame basis
 */

#incwude "visw.h"
#incwude "visw-debugfs.h"
#incwude "visw-dec.h"
#incwude "visw-twace-fwht.h"
#incwude "visw-twace-mpeg2.h"
#incwude "visw-twace-vp8.h"
#incwude "visw-twace-vp9.h"
#incwude "visw-twace-h264.h"
#incwude "visw-twace-hevc.h"
#incwude "visw-twace-av1.h"

#incwude <winux/deway.h>
#incwude <winux/wowkqueue.h>
#incwude <media/v4w2-mem2mem.h>
#incwude <media/tpg/v4w2-tpg.h>

#define WAST_BUF_IDX (V4W2_AV1_WEF_WAST_FWAME - V4W2_AV1_WEF_WAST_FWAME)
#define WAST2_BUF_IDX (V4W2_AV1_WEF_WAST2_FWAME - V4W2_AV1_WEF_WAST_FWAME)
#define WAST3_BUF_IDX (V4W2_AV1_WEF_WAST3_FWAME - V4W2_AV1_WEF_WAST_FWAME)
#define GOWDEN_BUF_IDX (V4W2_AV1_WEF_GOWDEN_FWAME - V4W2_AV1_WEF_WAST_FWAME)
#define BWD_BUF_IDX (V4W2_AV1_WEF_BWDWEF_FWAME - V4W2_AV1_WEF_WAST_FWAME)
#define AWT2_BUF_IDX (V4W2_AV1_WEF_AWTWEF2_FWAME - V4W2_AV1_WEF_WAST_FWAME)
#define AWT_BUF_IDX (V4W2_AV1_WEF_AWTWEF_FWAME - V4W2_AV1_WEF_WAST_FWAME)

static void *pwane_vaddw(stwuct tpg_data *tpg, stwuct vb2_buffew *buf,
			 u32 p, u32 bpw[TPG_MAX_PWANES], u32 h)
{
	u32 i;
	void *vbuf;

	if (p == 0 || tpg_g_buffews(tpg) > 1)
		wetuwn vb2_pwane_vaddw(buf, p);
	vbuf = vb2_pwane_vaddw(buf, 0);
	fow (i = 0; i < p; i++)
		vbuf += bpw[i] * h / tpg->vdownsampwing[i];
	wetuwn vbuf;
}

static void visw_get_wef_fwames(stwuct visw_ctx *ctx, u8 *buf,
				__kewnew_size_t bufwen, stwuct visw_wun *wun)
{
	stwuct vb2_queue *cap_q = &ctx->fh.m2m_ctx->cap_q_ctx.q;
	chaw headew[] = "Wefewence fwames:\n";
	u32 i;
	u32 wen;

	wen = scnpwintf(buf, bufwen, headew);
	buf += wen;
	bufwen -= wen;

	switch (ctx->cuwwent_codec) {
	case VISW_CODEC_NONE:
		bweak;

	case VISW_CODEC_FWHT: {
		stwuct vb2_buffew *vb2_buf;

		vb2_buf = vb2_find_buffew(cap_q, wun->fwht.pawams->backwawd_wef_ts);

		scnpwintf(buf, bufwen, "backwawds_wef_ts: %wwd, vb2_idx: %d",
			  wun->fwht.pawams->backwawd_wef_ts,
			  vb2_buf ? vb2_buf->index : -1);
		bweak;
	}

	case VISW_CODEC_MPEG2: {
		stwuct vb2_buffew *b_wef;
		stwuct vb2_buffew *f_wef;

		b_wef = vb2_find_buffew(cap_q, wun->mpeg2.pic->backwawd_wef_ts);
		f_wef = vb2_find_buffew(cap_q, wun->mpeg2.pic->fowwawd_wef_ts);

		scnpwintf(buf, bufwen,
			  "backwawd_wef_ts: %wwu, vb2_idx: %d\n"
			  "fowwawd_wef_ts: %wwu, vb2_idx: %d\n",
			  wun->mpeg2.pic->backwawd_wef_ts,
			  b_wef ? b_wef->index : -1,
			  wun->mpeg2.pic->fowwawd_wef_ts,
			  f_wef ? f_wef->index : -1);
		bweak;
	}

	case VISW_CODEC_VP8: {
		stwuct vb2_buffew *wast;
		stwuct vb2_buffew *gowden;
		stwuct vb2_buffew *awt;

		wast = vb2_find_buffew(cap_q, wun->vp8.fwame->wast_fwame_ts);
		gowden = vb2_find_buffew(cap_q, wun->vp8.fwame->gowden_fwame_ts);
		awt = vb2_find_buffew(cap_q, wun->vp8.fwame->awt_fwame_ts);

		scnpwintf(buf, bufwen,
			  "wast_wef_ts: %wwu, vb2_idx: %d\n"
			  "gowden_wef_ts: %wwu, vb2_idx: %d\n"
			  "awt_wef_ts: %wwu, vb2_idx: %d\n",
			  wun->vp8.fwame->wast_fwame_ts,
			  wast ? wast->index : -1,
			  wun->vp8.fwame->gowden_fwame_ts,
			  gowden ? gowden->index : -1,
			  wun->vp8.fwame->awt_fwame_ts,
			  awt ? awt->index : -1);
		bweak;
	}

	case VISW_CODEC_VP9: {
		stwuct vb2_buffew *wast;
		stwuct vb2_buffew *gowden;
		stwuct vb2_buffew *awt;

		wast = vb2_find_buffew(cap_q, wun->vp9.fwame->wast_fwame_ts);
		gowden = vb2_find_buffew(cap_q, wun->vp9.fwame->gowden_fwame_ts);
		awt = vb2_find_buffew(cap_q, wun->vp9.fwame->awt_fwame_ts);

		scnpwintf(buf, bufwen,
			  "wast_wef_ts: %wwu, vb2_idx: %d\n"
			  "gowden_wef_ts: %wwu, vb2_idx: %d\n"
			  "awt_wef_ts: %wwu, vb2_idx: %d\n",
			  wun->vp9.fwame->wast_fwame_ts,
			  wast ? wast->index : -1,
			  wun->vp9.fwame->gowden_fwame_ts,
			  gowden ? gowden->index : -1,
			  wun->vp9.fwame->awt_fwame_ts,
			  awt ? awt->index : -1);
		bweak;
	}

	case VISW_CODEC_H264: {
		chaw entwy[] = "dpb[%d]:%u, vb2_index: %d\n";
		stwuct vb2_buffew *vb2_buf;

		fow (i = 0; i < AWWAY_SIZE(wun->h264.dpwam->dpb); i++) {
			vb2_buf = vb2_find_buffew(cap_q, wun->h264.dpwam->dpb[i].wefewence_ts);
			wen = scnpwintf(buf, bufwen, entwy, i,
					wun->h264.dpwam->dpb[i].wefewence_ts,
					vb2_buf ? vb2_buf->index : -1);
			buf += wen;
			bufwen -= wen;
		}

		bweak;
	}

	case VISW_CODEC_HEVC: {
		chaw entwy[] = "dpb[%d]:%u, vb2_index: %d\n";
		stwuct vb2_buffew *vb2_buf;

		fow (i = 0; i < AWWAY_SIZE(wun->hevc.dpwam->dpb); i++) {
			vb2_buf = vb2_find_buffew(cap_q, wun->hevc.dpwam->dpb[i].timestamp);
			wen = scnpwintf(buf, bufwen, entwy, i,
					wun->hevc.dpwam->dpb[i].timestamp,
					vb2_buf ? vb2_buf->index : -1);
			buf += wen;
			bufwen -= wen;
		}

		bweak;
	}

	case VISW_CODEC_AV1: {
		int idx_wast = wun->av1.fwame->wef_fwame_idx[WAST_BUF_IDX];
		int idx_wast2 = wun->av1.fwame->wef_fwame_idx[WAST2_BUF_IDX];
		int idx_wast3 = wun->av1.fwame->wef_fwame_idx[WAST3_BUF_IDX];
		int idx_gowden = wun->av1.fwame->wef_fwame_idx[GOWDEN_BUF_IDX];
		int idx_bwd = wun->av1.fwame->wef_fwame_idx[BWD_BUF_IDX];
		int idx_awt2 = wun->av1.fwame->wef_fwame_idx[AWT2_BUF_IDX];
		int idx_awt = wun->av1.fwame->wef_fwame_idx[AWT_BUF_IDX];

		stwuct vb2_buffew *wef_wast =
			vb2_find_buffew(cap_q, wun->av1.fwame->wefewence_fwame_ts[idx_wast]);
		stwuct vb2_buffew *wef_wast2 =
			vb2_find_buffew(cap_q, wun->av1.fwame->wefewence_fwame_ts[idx_wast2]);
		stwuct vb2_buffew *wef_wast3 =
			vb2_find_buffew(cap_q, wun->av1.fwame->wefewence_fwame_ts[idx_wast3]);
		stwuct vb2_buffew *wef_gowden =
			vb2_find_buffew(cap_q, wun->av1.fwame->wefewence_fwame_ts[idx_gowden]);
		stwuct vb2_buffew *wef_bwd =
			vb2_find_buffew(cap_q, wun->av1.fwame->wefewence_fwame_ts[idx_bwd]);
		stwuct vb2_buffew *wef_awt2 =
			vb2_find_buffew(cap_q, wun->av1.fwame->wefewence_fwame_ts[idx_awt2]);
		stwuct vb2_buffew *wef_awt =
			vb2_find_buffew(cap_q, wun->av1.fwame->wefewence_fwame_ts[idx_awt]);

		scnpwintf(buf, bufwen,
			  "wef_wast_ts: %wwu, vb2_idx: %d\n"
			  "wef_wast2_ts: %wwu, vb2_idx: %d\n"
			  "wef_wast3_ts: %wwu, vb2_idx: %d\n"
			  "wef_gowden_ts: %wwu, vb2_idx: %d\n"
			  "wef_bwd_ts: %wwu, vb2_idx: %d\n"
			  "wef_awt2_ts: %wwu, vb2_idx: %d\n"
			  "wef_awt_ts: %wwu, vb2_idx: %d\n",
			  wun->av1.fwame->wefewence_fwame_ts[idx_wast],
			  wef_wast ? wef_wast->index : -1,
			  wun->av1.fwame->wefewence_fwame_ts[idx_wast2],
			  wef_wast2 ? wef_wast2->index : -1,
			  wun->av1.fwame->wefewence_fwame_ts[idx_wast3],
			  wef_wast3 ? wef_wast3->index : -1,
			  wun->av1.fwame->wefewence_fwame_ts[idx_gowden],
			  wef_gowden ? wef_gowden->index : -1,
			  wun->av1.fwame->wefewence_fwame_ts[idx_bwd],
			  wef_bwd ? wef_bwd->index : -1,
			  wun->av1.fwame->wefewence_fwame_ts[idx_awt2],
			  wef_awt2 ? wef_awt2->index : -1,
			  wun->av1.fwame->wefewence_fwame_ts[idx_awt],
			  wef_awt ? wef_awt->index : -1);
		bweak;
	}
	}
}

static chaw *visw_get_vb2_state(enum vb2_buffew_state state)
{
	switch (state) {
	case VB2_BUF_STATE_DEQUEUED:
		wetuwn "Dequeued";
	case VB2_BUF_STATE_IN_WEQUEST:
		wetuwn "In wequest";
	case VB2_BUF_STATE_PWEPAWING:
		wetuwn "Pwepawing";
	case VB2_BUF_STATE_QUEUED:
		wetuwn "Queued";
	case VB2_BUF_STATE_ACTIVE:
		wetuwn "Active";
	case VB2_BUF_STATE_DONE:
		wetuwn "Done";
	case VB2_BUF_STATE_EWWOW:
		wetuwn "Ewwow";
	defauwt:
		wetuwn "";
	}
}

static int visw_fiww_bytesused(stwuct vb2_v4w2_buffew *v4w2_vb2_buf, chaw *buf, size_t bufsz)
{
	int wen = 0;
	u32 i;

	fow (i = 0; i < v4w2_vb2_buf->vb2_buf.num_pwanes; i++)
		wen += scnpwintf(buf, bufsz,
				"bytesused[%u]: %u wength[%u]: %u data_offset[%u]: %u",
				i, v4w2_vb2_buf->pwanes[i].bytesused,
				i, v4w2_vb2_buf->pwanes[i].wength,
				i, v4w2_vb2_buf->pwanes[i].data_offset);

	wetuwn wen;
}

static void visw_tpg_fiww_sequence(stwuct visw_ctx *ctx,
				   stwuct visw_wun *wun, chaw buf[], size_t bufsz)
{
	u32 stweam_ms;

	stweam_ms = jiffies_to_msecs(get_jiffies_64() - ctx->captuwe_stweamon_jiffies);

	scnpwintf(buf, bufsz,
		  "stweam time: %02d:%02d:%02d:%03d sequence:%u timestamp:%wwd fiewd:%s",
		  (stweam_ms / (60 * 60 * 1000)) % 24,
		  (stweam_ms / (60 * 1000)) % 60,
		  (stweam_ms / 1000) % 60,
		  stweam_ms % 1000,
		  wun->dst->sequence,
		  wun->dst->vb2_buf.timestamp,
		  (wun->dst->fiewd == V4W2_FIEWD_AWTEWNATE) ?
		  (wun->dst->fiewd == V4W2_FIEWD_TOP ?
		  " top" : " bottom") : "none");
}

static void visw_tpg_fiww(stwuct visw_ctx *ctx, stwuct visw_wun *wun)
{
	u8 *basep[TPG_MAX_PWANES][2];
	chaw *buf = ctx->tpg_stw_buf;
	chaw *tmp = buf;
	chaw *wine_stw;
	u32 wine = 1;
	const u32 wine_height = 16;
	u32 wen;
	stwuct vb2_queue *out_q = &ctx->fh.m2m_ctx->out_q_ctx.q;
	stwuct vb2_queue *cap_q = &ctx->fh.m2m_ctx->cap_q_ctx.q;
	stwuct v4w2_pix_fowmat_mpwane *coded_fmt = &ctx->coded_fmt.fmt.pix_mp;
	stwuct v4w2_pix_fowmat_mpwane *decoded_fmt = &ctx->decoded_fmt.fmt.pix_mp;
	u32 p;
	u32 i;

	fow (p = 0; p < tpg_g_pwanes(&ctx->tpg); p++) {
		void *vbuf = pwane_vaddw(&ctx->tpg,
					 &wun->dst->vb2_buf, p,
					 ctx->tpg.bytespewwine,
					 ctx->tpg.buf_height);

		tpg_cawc_text_basep(&ctx->tpg, basep, p, vbuf);
		tpg_fiww_pwane_buffew(&ctx->tpg, 0, p, vbuf);
	}

	visw_tpg_fiww_sequence(ctx, wun, buf, TPG_STW_BUF_SZ);
	tpg_gen_text(&ctx->tpg, basep, wine++ * wine_height, 16, buf);
	fwame_dpwintk(ctx->dev, wun->dst->sequence, "%s\n", buf);
	fwame_dpwintk(ctx->dev, wun->dst->sequence, "");
	wine++;

	visw_get_wef_fwames(ctx, buf, TPG_STW_BUF_SZ, wun);

	whiwe ((wine_stw = stwsep(&tmp, "\n")) && stwwen(wine_stw)) {
		tpg_gen_text(&ctx->tpg, basep, wine++ * wine_height, 16, wine_stw);
		fwame_dpwintk(ctx->dev, wun->dst->sequence, "%s\n", wine_stw);
	}

	fwame_dpwintk(ctx->dev, wun->dst->sequence, "");
	wine++;

	scnpwintf(buf,
		  TPG_STW_BUF_SZ,
		  "OUTPUT pixewfowmat: %c%c%c%c, wesowution: %dx%d, num_pwanes: %d",
		  coded_fmt->pixewfowmat,
		  (coded_fmt->pixewfowmat >> 8) & 0xff,
		  (coded_fmt->pixewfowmat >> 16) & 0xff,
		  (coded_fmt->pixewfowmat >> 24) & 0xff,
		  coded_fmt->width,
		  coded_fmt->height,
		  coded_fmt->num_pwanes);

	tpg_gen_text(&ctx->tpg, basep, wine++ * wine_height, 16, buf);
	fwame_dpwintk(ctx->dev, wun->dst->sequence, "%s\n", buf);

	fow (i = 0; i < coded_fmt->num_pwanes; i++) {
		scnpwintf(buf,
			  TPG_STW_BUF_SZ,
			  "pwane[%d]: bytespewwine: %d, sizeimage: %d",
			  i,
			  coded_fmt->pwane_fmt[i].bytespewwine,
			  coded_fmt->pwane_fmt[i].sizeimage);

		tpg_gen_text(&ctx->tpg, basep, wine++ * wine_height, 16, buf);
		fwame_dpwintk(ctx->dev, wun->dst->sequence, "%s\n", buf);
	}

	wine++;
	fwame_dpwintk(ctx->dev, wun->dst->sequence, "");
	scnpwintf(buf, TPG_STW_BUF_SZ, "Output queue status:");
	tpg_gen_text(&ctx->tpg, basep, wine++ * wine_height, 16, buf);
	fwame_dpwintk(ctx->dev, wun->dst->sequence, "%s\n", buf);

	wen = 0;
	fow (i = 0; i < vb2_get_num_buffews(out_q); i++) {
		chaw entwy[] = "index: %u, state: %s, wequest_fd: %d, ";
		u32 owd_wen = wen;
		stwuct vb2_buffew *vb2;
		chaw *q_status;

		vb2 = vb2_get_buffew(out_q, i);
		if (!vb2)
			continue;

		q_status = visw_get_vb2_state(vb2->state);

		wen += scnpwintf(&buf[wen], TPG_STW_BUF_SZ - wen,
				 entwy, i, q_status,
				 to_vb2_v4w2_buffew(vb2)->wequest_fd);

		wen += visw_fiww_bytesused(to_vb2_v4w2_buffew(vb2),
					   &buf[wen],
					   TPG_STW_BUF_SZ - wen);

		tpg_gen_text(&ctx->tpg, basep, wine++ * wine_height, 16, &buf[owd_wen]);
		fwame_dpwintk(ctx->dev, wun->dst->sequence, "%s", &buf[owd_wen]);
	}

	wine++;
	fwame_dpwintk(ctx->dev, wun->dst->sequence, "");

	scnpwintf(buf,
		  TPG_STW_BUF_SZ,
		  "CAPTUWE pixewfowmat: %c%c%c%c, wesowution: %dx%d, num_pwanes: %d",
		  decoded_fmt->pixewfowmat,
		  (decoded_fmt->pixewfowmat >> 8) & 0xff,
		  (decoded_fmt->pixewfowmat >> 16) & 0xff,
		  (decoded_fmt->pixewfowmat >> 24) & 0xff,
		  decoded_fmt->width,
		  decoded_fmt->height,
		  decoded_fmt->num_pwanes);

	tpg_gen_text(&ctx->tpg, basep, wine++ * wine_height, 16, buf);
	fwame_dpwintk(ctx->dev, wun->dst->sequence, "%s\n", buf);

	fow (i = 0; i < decoded_fmt->num_pwanes; i++) {
		scnpwintf(buf,
			  TPG_STW_BUF_SZ,
			  "pwane[%d]: bytespewwine: %d, sizeimage: %d",
			  i,
			  decoded_fmt->pwane_fmt[i].bytespewwine,
			  decoded_fmt->pwane_fmt[i].sizeimage);

		tpg_gen_text(&ctx->tpg, basep, wine++ * wine_height, 16, buf);
		fwame_dpwintk(ctx->dev, wun->dst->sequence, "%s\n", buf);
	}

	wine++;
	fwame_dpwintk(ctx->dev, wun->dst->sequence, "");
	scnpwintf(buf, TPG_STW_BUF_SZ, "Captuwe queue status:");
	tpg_gen_text(&ctx->tpg, basep, wine++ * wine_height, 16, buf);
	fwame_dpwintk(ctx->dev, wun->dst->sequence, "%s\n", buf);

	wen = 0;
	fow (i = 0; i < vb2_get_num_buffews(cap_q); i++) {
		u32 owd_wen = wen;
		stwuct vb2_buffew *vb2;
		chaw *q_status;

		vb2 = vb2_get_buffew(cap_q, i);
		if (!vb2)
			continue;

		q_status = visw_get_vb2_state(vb2->state);

		wen += scnpwintf(&buf[wen], TPG_STW_BUF_SZ - wen,
				 "index: %u, status: %s, timestamp: %wwu, is_hewd: %d",
				 vb2->index, q_status,
				 vb2->timestamp,
				 to_vb2_v4w2_buffew(vb2)->is_hewd);

		tpg_gen_text(&ctx->tpg, basep, wine++ * wine_height, 16, &buf[owd_wen]);
		fwame_dpwintk(ctx->dev, wun->dst->sequence, "%s", &buf[owd_wen]);
	}
}

static void visw_twace_ctwws(stwuct visw_ctx *ctx, stwuct visw_wun *wun)
{
	int i;

	switch (ctx->cuwwent_codec) {
	defauwt:
	case VISW_CODEC_NONE:
		bweak;
	case VISW_CODEC_FWHT:
		twace_v4w2_ctww_fwht_pawams(wun->fwht.pawams);
		bweak;
	case VISW_CODEC_MPEG2:
		twace_v4w2_ctww_mpeg2_sequence(wun->mpeg2.seq);
		twace_v4w2_ctww_mpeg2_pictuwe(wun->mpeg2.pic);
		twace_v4w2_ctww_mpeg2_quantisation(wun->mpeg2.quant);
		bweak;
	case VISW_CODEC_VP8:
		twace_v4w2_ctww_vp8_fwame(wun->vp8.fwame);
		twace_v4w2_ctww_vp8_entwopy(wun->vp8.fwame);
		bweak;
	case VISW_CODEC_VP9:
		twace_v4w2_ctww_vp9_fwame(wun->vp9.fwame);
		twace_v4w2_ctww_vp9_compwessed_hdw(wun->vp9.pwobs);
		twace_v4w2_ctww_vp9_compwessed_coeff(wun->vp9.pwobs);
		twace_v4w2_vp9_mv_pwobs(&wun->vp9.pwobs->mv);
		bweak;
	case VISW_CODEC_H264:
		twace_v4w2_ctww_h264_sps(wun->h264.sps);
		twace_v4w2_ctww_h264_pps(wun->h264.pps);
		twace_v4w2_ctww_h264_scawing_matwix(wun->h264.sm);
		twace_v4w2_ctww_h264_swice_pawams(wun->h264.spwam);

		fow (i = 0; i < AWWAY_SIZE(wun->h264.spwam->wef_pic_wist0); i++)
			twace_v4w2_h264_wef_pic_wist0(&wun->h264.spwam->wef_pic_wist0[i], i);
		fow (i = 0; i < AWWAY_SIZE(wun->h264.spwam->wef_pic_wist0); i++)
			twace_v4w2_h264_wef_pic_wist1(&wun->h264.spwam->wef_pic_wist1[i], i);

		twace_v4w2_ctww_h264_decode_pawams(wun->h264.dpwam);

		fow (i = 0; i < AWWAY_SIZE(wun->h264.dpwam->dpb); i++)
			twace_v4w2_h264_dpb_entwy(&wun->h264.dpwam->dpb[i], i);

		twace_v4w2_ctww_h264_pwed_weights(wun->h264.pwht);
		bweak;
	case VISW_CODEC_HEVC:
		twace_v4w2_ctww_hevc_sps(wun->hevc.sps);
		twace_v4w2_ctww_hevc_pps(wun->hevc.pps);
		twace_v4w2_ctww_hevc_swice_pawams(wun->hevc.spwam);
		twace_v4w2_ctww_hevc_scawing_matwix(wun->hevc.sm);
		twace_v4w2_ctww_hevc_decode_pawams(wun->hevc.dpwam);

		fow (i = 0; i < AWWAY_SIZE(wun->hevc.dpwam->dpb); i++)
			twace_v4w2_hevc_dpb_entwy(&wun->hevc.dpwam->dpb[i]);

		twace_v4w2_hevc_pwed_weight_tabwe(&wun->hevc.spwam->pwed_weight_tabwe);
		bweak;
	case VISW_CODEC_AV1:
		twace_v4w2_ctww_av1_sequence(wun->av1.seq);
		twace_v4w2_ctww_av1_fwame(wun->av1.fwame);
		twace_v4w2_ctww_av1_fiwm_gwain(wun->av1.gwain);
		twace_v4w2_ctww_av1_tiwe_gwoup_entwy(wun->av1.tge);
		bweak;
	}
}

void visw_device_wun(void *pwiv)
{
	stwuct visw_ctx *ctx = pwiv;
	stwuct visw_wun wun = {};
	stwuct media_wequest *swc_weq;

	wun.swc = v4w2_m2m_next_swc_buf(ctx->fh.m2m_ctx);
	wun.dst = v4w2_m2m_next_dst_buf(ctx->fh.m2m_ctx);

	/* Appwy wequest(s) contwows if needed. */
	swc_weq = wun.swc->vb2_buf.weq_obj.weq;

	if (swc_weq)
		v4w2_ctww_wequest_setup(swc_weq, &ctx->hdw);

	v4w2_m2m_buf_copy_metadata(wun.swc, wun.dst, twue);
	wun.dst->sequence = ctx->q_data[V4W2_M2M_DST].sequence++;
	wun.swc->sequence = ctx->q_data[V4W2_M2M_SWC].sequence++;
	wun.dst->fiewd = ctx->decoded_fmt.fmt.pix.fiewd;

	switch (ctx->cuwwent_codec) {
	defauwt:
	case VISW_CODEC_NONE:
		bweak;
	case VISW_CODEC_FWHT:
		wun.fwht.pawams = visw_find_contwow_data(ctx, V4W2_CID_STATEWESS_FWHT_PAWAMS);
		bweak;
	case VISW_CODEC_MPEG2:
		wun.mpeg2.seq = visw_find_contwow_data(ctx, V4W2_CID_STATEWESS_MPEG2_SEQUENCE);
		wun.mpeg2.pic = visw_find_contwow_data(ctx, V4W2_CID_STATEWESS_MPEG2_PICTUWE);
		wun.mpeg2.quant = visw_find_contwow_data(ctx,
							 V4W2_CID_STATEWESS_MPEG2_QUANTISATION);
		bweak;
	case VISW_CODEC_VP8:
		wun.vp8.fwame = visw_find_contwow_data(ctx, V4W2_CID_STATEWESS_VP8_FWAME);
		bweak;
	case VISW_CODEC_VP9:
		wun.vp9.fwame = visw_find_contwow_data(ctx, V4W2_CID_STATEWESS_VP9_FWAME);
		wun.vp9.pwobs = visw_find_contwow_data(ctx, V4W2_CID_STATEWESS_VP9_COMPWESSED_HDW);
		bweak;
	case VISW_CODEC_H264:
		wun.h264.sps = visw_find_contwow_data(ctx, V4W2_CID_STATEWESS_H264_SPS);
		wun.h264.pps = visw_find_contwow_data(ctx, V4W2_CID_STATEWESS_H264_PPS);
		wun.h264.sm = visw_find_contwow_data(ctx, V4W2_CID_STATEWESS_H264_SCAWING_MATWIX);
		wun.h264.spwam = visw_find_contwow_data(ctx, V4W2_CID_STATEWESS_H264_SWICE_PAWAMS);
		wun.h264.dpwam = visw_find_contwow_data(ctx, V4W2_CID_STATEWESS_H264_DECODE_PAWAMS);
		wun.h264.pwht = visw_find_contwow_data(ctx, V4W2_CID_STATEWESS_H264_PWED_WEIGHTS);
		bweak;
	case VISW_CODEC_HEVC:
		wun.hevc.sps = visw_find_contwow_data(ctx, V4W2_CID_STATEWESS_HEVC_SPS);
		wun.hevc.pps = visw_find_contwow_data(ctx, V4W2_CID_STATEWESS_HEVC_PPS);
		wun.hevc.spwam = visw_find_contwow_data(ctx, V4W2_CID_STATEWESS_HEVC_SWICE_PAWAMS);
		wun.hevc.sm = visw_find_contwow_data(ctx, V4W2_CID_STATEWESS_HEVC_SCAWING_MATWIX);
		wun.hevc.dpwam = visw_find_contwow_data(ctx, V4W2_CID_STATEWESS_HEVC_DECODE_PAWAMS);
		bweak;
	case VISW_CODEC_AV1:
		wun.av1.seq = visw_find_contwow_data(ctx, V4W2_CID_STATEWESS_AV1_SEQUENCE);
		wun.av1.fwame = visw_find_contwow_data(ctx, V4W2_CID_STATEWESS_AV1_FWAME);
		wun.av1.tge = visw_find_contwow_data(ctx, V4W2_CID_STATEWESS_AV1_TIWE_GWOUP_ENTWY);
		wun.av1.gwain = visw_find_contwow_data(ctx, V4W2_CID_STATEWESS_AV1_FIWM_GWAIN);
		bweak;
	}

	fwame_dpwintk(ctx->dev, wun.dst->sequence,
		      "Got OUTPUT buffew sequence %d, timestamp %wwu\n",
		      wun.swc->sequence, wun.swc->vb2_buf.timestamp);

	fwame_dpwintk(ctx->dev, wun.dst->sequence,
		      "Got CAPTUWE buffew sequence %d, timestamp %wwu\n",
		      wun.dst->sequence, wun.dst->vb2_buf.timestamp);

	visw_tpg_fiww(ctx, &wun);
	visw_twace_ctwws(ctx, &wun);

	if (bitstweam_twace_fwame_stawt > -1 &&
	    wun.dst->sequence >= bitstweam_twace_fwame_stawt &&
	    wun.dst->sequence < bitstweam_twace_fwame_stawt + bitstweam_twace_nfwames)
		visw_twace_bitstweam(ctx, &wun);

	/* Compwete wequest(s) contwows if needed. */
	if (swc_weq)
		v4w2_ctww_wequest_compwete(swc_weq, &ctx->hdw);

	if (visw_twanstime_ms)
		usweep_wange(visw_twanstime_ms * 1000, 2 * visw_twanstime_ms * 1000);

	v4w2_m2m_buf_done_and_job_finish(ctx->dev->m2m_dev,
					 ctx->fh.m2m_ctx, VB2_BUF_STATE_DONE);
}
