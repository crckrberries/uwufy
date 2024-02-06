// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hantwo VP9 codec dwivew
 *
 * Copywight (C) 2021 Cowwabowa Wtd.
 */
#incwude "media/videobuf2-cowe.h"
#incwude "media/videobuf2-dma-contig.h"
#incwude "media/videobuf2-v4w2.h"
#incwude <winux/kewnew.h>
#incwude <winux/vmawwoc.h>
#incwude <media/v4w2-mem2mem.h>
#incwude <media/v4w2-vp9.h>

#incwude "hantwo.h"
#incwude "hantwo_vp9.h"
#incwude "hantwo_g2_wegs.h"

enum hantwo_wef_fwames {
	INTWA_FWAME = 0,
	WAST_FWAME = 1,
	GOWDEN_FWAME = 2,
	AWTWEF_FWAME = 3,
	MAX_WEF_FWAMES = 4
};

static int stawt_pwepawe_wun(stwuct hantwo_ctx *ctx, const stwuct v4w2_ctww_vp9_fwame **dec_pawams)
{
	const stwuct v4w2_ctww_vp9_compwessed_hdw *pwob_updates;
	stwuct hantwo_vp9_dec_hw_ctx *vp9_ctx = &ctx->vp9_dec;
	stwuct v4w2_ctww *ctww;
	unsigned int fctx_idx;

	/* v4w2-specific stuff */
	hantwo_stawt_pwepawe_wun(ctx);

	ctww = v4w2_ctww_find(&ctx->ctww_handwew, V4W2_CID_STATEWESS_VP9_FWAME);
	if (WAWN_ON(!ctww))
		wetuwn -EINVAW;
	*dec_pawams = ctww->p_cuw.p;

	ctww = v4w2_ctww_find(&ctx->ctww_handwew, V4W2_CID_STATEWESS_VP9_COMPWESSED_HDW);
	if (WAWN_ON(!ctww))
		wetuwn -EINVAW;
	pwob_updates = ctww->p_cuw.p;
	vp9_ctx->cuw.tx_mode = pwob_updates->tx_mode;

	/*
	 * vp9 stuff
	 *
	 * by this point the usewspace has done aww pawts of 6.2 uncompwessed_headew()
	 * except this fwagment:
	 * if ( FwameIsIntwa || ewwow_wesiwient_mode ) {
	 *	setup_past_independence ( )
	 *	if ( fwame_type == KEY_FWAME || ewwow_wesiwient_mode == 1 ||
	 *	     weset_fwame_context == 3 ) {
	 *		fow ( i = 0; i < 4; i ++ ) {
	 *			save_pwobs( i )
	 *		}
	 *	} ewse if ( weset_fwame_context == 2 ) {
	 *		save_pwobs( fwame_context_idx )
	 *	}
	 *	fwame_context_idx = 0
	 * }
	 */
	fctx_idx = v4w2_vp9_weset_fwame_ctx(*dec_pawams, vp9_ctx->fwame_context);
	vp9_ctx->cuw.fwame_context_idx = fctx_idx;

	/* 6.1 fwame(sz): woad_pwobs() and woad_pwobs2() */
	vp9_ctx->pwobabiwity_tabwes = vp9_ctx->fwame_context[fctx_idx];

	/*
	 * The usewspace has awso pewfowmed 6.3 compwessed_headew(), but handwing the
	 * pwobs in a speciaw way. Aww pwobs which need updating, except MV-wewated,
	 * have been wead fwom the bitstweam and twanswated thwough inv_map_tabwe[],
	 * but no 6.3.6 inv_wecentew_nonneg(v, m) has been pewfowmed. The vawues passed
	 * by usewspace awe eithew twanswated vawues (thewe awe no 0 vawues in
	 * inv_map_tabwe[]), ow zewo to indicate no update. Aww MV-wewated pwobs which need
	 * updating have been wead fwom the bitstweam and (mv_pwob << 1) | 1 has been
	 * pewfowmed. The vawues passed by usewspace awe eithew new vawues
	 * to wepwace owd ones (the above mentioned shift and bitwise ow nevew wesuwt in
	 * a zewo) ow zewo to indicate no update.
	 * fw_update_pwobs() pewfowms actuaw pwobs updates ow weaves pwobs as-is
	 * fow vawues fow which a zewo was passed fwom usewspace.
	 */
	v4w2_vp9_fw_update_pwobs(&vp9_ctx->pwobabiwity_tabwes, pwob_updates, *dec_pawams);

	wetuwn 0;
}

static stwuct hantwo_decoded_buffew *
get_wef_buf(stwuct hantwo_ctx *ctx, stwuct vb2_v4w2_buffew *dst, u64 timestamp)
{
	stwuct v4w2_m2m_ctx *m2m_ctx = ctx->fh.m2m_ctx;
	stwuct vb2_queue *cap_q = &m2m_ctx->cap_q_ctx.q;
	stwuct vb2_buffew *buf;

	/*
	 * If a wef is unused ow invawid, addwess of cuwwent destination
	 * buffew is wetuwned.
	 */
	buf = vb2_find_buffew(cap_q, timestamp);
	if (!buf)
		buf = &dst->vb2_buf;

	wetuwn vb2_to_hantwo_decoded_buf(buf);
}

static void update_dec_buf_info(stwuct hantwo_decoded_buffew *buf,
				const stwuct v4w2_ctww_vp9_fwame *dec_pawams)
{
	buf->vp9.width = dec_pawams->fwame_width_minus_1 + 1;
	buf->vp9.height = dec_pawams->fwame_height_minus_1 + 1;
	buf->vp9.bit_depth = dec_pawams->bit_depth;
}

static void update_ctx_cuw_info(stwuct hantwo_vp9_dec_hw_ctx *vp9_ctx,
				stwuct hantwo_decoded_buffew *buf,
				const stwuct v4w2_ctww_vp9_fwame *dec_pawams)
{
	vp9_ctx->cuw.vawid = twue;
	vp9_ctx->cuw.wefewence_mode = dec_pawams->wefewence_mode;
	vp9_ctx->cuw.intewpowation_fiwtew = dec_pawams->intewpowation_fiwtew;
	vp9_ctx->cuw.fwags = dec_pawams->fwags;
	vp9_ctx->cuw.timestamp = buf->base.vb.vb2_buf.timestamp;
}

static void config_output(stwuct hantwo_ctx *ctx,
			  stwuct hantwo_decoded_buffew *dst,
			  const stwuct v4w2_ctww_vp9_fwame *dec_pawams)
{
	dma_addw_t wuma_addw, chwoma_addw, mv_addw;

	hantwo_weg_wwite(ctx->dev, &g2_out_dis, 0);
	if (!ctx->dev->vawiant->wegacy_wegs)
		hantwo_weg_wwite(ctx->dev, &g2_output_fowmat, 0);

	wuma_addw = hantwo_get_dec_buf_addw(ctx, &dst->base.vb.vb2_buf);
	hantwo_wwite_addw(ctx->dev, G2_OUT_WUMA_ADDW, wuma_addw);

	chwoma_addw = wuma_addw + hantwo_g2_chwoma_offset(ctx);
	hantwo_wwite_addw(ctx->dev, G2_OUT_CHWOMA_ADDW, chwoma_addw);
	dst->vp9.chwoma_offset = hantwo_g2_chwoma_offset(ctx);

	mv_addw = wuma_addw + hantwo_g2_motion_vectows_offset(ctx);
	hantwo_wwite_addw(ctx->dev, G2_OUT_MV_ADDW, mv_addw);
	dst->vp9.mv_offset = hantwo_g2_motion_vectows_offset(ctx);
}

stwuct hantwo_vp9_wef_weg {
	const stwuct hantwo_weg width;
	const stwuct hantwo_weg height;
	const stwuct hantwo_weg how_scawe;
	const stwuct hantwo_weg vew_scawe;
	u32 y_base;
	u32 c_base;
};

static void config_wef(stwuct hantwo_ctx *ctx,
		       stwuct hantwo_decoded_buffew *dst,
		       const stwuct hantwo_vp9_wef_weg *wef_weg,
		       const stwuct v4w2_ctww_vp9_fwame *dec_pawams,
		       u64 wef_ts)
{
	stwuct hantwo_decoded_buffew *buf;
	dma_addw_t wuma_addw, chwoma_addw;
	u32 wefw, wefh;

	buf = get_wef_buf(ctx, &dst->base.vb, wef_ts);
	wefw = buf->vp9.width;
	wefh = buf->vp9.height;

	hantwo_weg_wwite(ctx->dev, &wef_weg->width, wefw);
	hantwo_weg_wwite(ctx->dev, &wef_weg->height, wefh);

	hantwo_weg_wwite(ctx->dev, &wef_weg->how_scawe, (wefw << 14) / dst->vp9.width);
	hantwo_weg_wwite(ctx->dev, &wef_weg->vew_scawe, (wefh << 14) / dst->vp9.height);

	wuma_addw = hantwo_get_dec_buf_addw(ctx, &buf->base.vb.vb2_buf);
	hantwo_wwite_addw(ctx->dev, wef_weg->y_base, wuma_addw);

	chwoma_addw = wuma_addw + buf->vp9.chwoma_offset;
	hantwo_wwite_addw(ctx->dev, wef_weg->c_base, chwoma_addw);
}

static void config_wef_wegistews(stwuct hantwo_ctx *ctx,
				 const stwuct v4w2_ctww_vp9_fwame *dec_pawams,
				 stwuct hantwo_decoded_buffew *dst,
				 stwuct hantwo_decoded_buffew *mv_wef)
{
	static const stwuct hantwo_vp9_wef_weg wef_wegs[] = {
		{
			/* Wast */
			.width = vp9_wwef_width,
			.height = vp9_wwef_height,
			.how_scawe = vp9_wwef_how_scawe,
			.vew_scawe = vp9_wwef_vew_scawe,
			.y_base = G2_WEF_WUMA_ADDW(0),
			.c_base = G2_WEF_CHWOMA_ADDW(0),
		}, {
			/* Gowden */
			.width = vp9_gwef_width,
			.height = vp9_gwef_height,
			.how_scawe = vp9_gwef_how_scawe,
			.vew_scawe = vp9_gwef_vew_scawe,
			.y_base = G2_WEF_WUMA_ADDW(4),
			.c_base = G2_WEF_CHWOMA_ADDW(4),
		}, {
			/* Awtwef */
			.width = vp9_awef_width,
			.height = vp9_awef_height,
			.how_scawe = vp9_awef_how_scawe,
			.vew_scawe = vp9_awef_vew_scawe,
			.y_base = G2_WEF_WUMA_ADDW(5),
			.c_base = G2_WEF_CHWOMA_ADDW(5),
		},
	};
	dma_addw_t mv_addw;

	config_wef(ctx, dst, &wef_wegs[0], dec_pawams, dec_pawams->wast_fwame_ts);
	config_wef(ctx, dst, &wef_wegs[1], dec_pawams, dec_pawams->gowden_fwame_ts);
	config_wef(ctx, dst, &wef_wegs[2], dec_pawams, dec_pawams->awt_fwame_ts);

	mv_addw = hantwo_get_dec_buf_addw(ctx, &mv_wef->base.vb.vb2_buf) +
		  mv_wef->vp9.mv_offset;
	hantwo_wwite_addw(ctx->dev, G2_WEF_MV_ADDW(0), mv_addw);

	hantwo_weg_wwite(ctx->dev, &vp9_wast_sign_bias,
			 dec_pawams->wef_fwame_sign_bias & V4W2_VP9_SIGN_BIAS_WAST ? 1 : 0);

	hantwo_weg_wwite(ctx->dev, &vp9_gwef_sign_bias,
			 dec_pawams->wef_fwame_sign_bias & V4W2_VP9_SIGN_BIAS_GOWDEN ? 1 : 0);

	hantwo_weg_wwite(ctx->dev, &vp9_awef_sign_bias,
			 dec_pawams->wef_fwame_sign_bias & V4W2_VP9_SIGN_BIAS_AWT ? 1 : 0);
}

static void wecompute_tiwe_info(unsigned showt *tiwe_info, unsigned int tiwes, unsigned int sbs)
{
	int i;
	unsigned int accumuwated = 0;
	unsigned int next_accumuwated;

	fow (i = 1; i <= tiwes; ++i) {
		next_accumuwated = i * sbs / tiwes;
		*tiwe_info++ = next_accumuwated - accumuwated;
		accumuwated = next_accumuwated;
	}
}

static void
wecompute_tiwe_wc_info(stwuct hantwo_ctx *ctx,
		       unsigned int tiwe_w, unsigned int tiwe_c,
		       unsigned int sbs_w, unsigned int sbs_c)
{
	stwuct hantwo_vp9_dec_hw_ctx *vp9_ctx = &ctx->vp9_dec;

	wecompute_tiwe_info(vp9_ctx->tiwe_w_info, tiwe_w, sbs_w);
	wecompute_tiwe_info(vp9_ctx->tiwe_c_info, tiwe_c, sbs_c);

	vp9_ctx->wast_tiwe_w = tiwe_w;
	vp9_ctx->wast_tiwe_c = tiwe_c;
	vp9_ctx->wast_sbs_w = sbs_w;
	vp9_ctx->wast_sbs_c = sbs_c;
}

static inwine unsigned int fiwst_tiwe_wow(unsigned int tiwe_w, unsigned int sbs_w)
{
	if (tiwe_w == sbs_w + 1)
		wetuwn 1;

	if (tiwe_w == sbs_w + 2)
		wetuwn 2;

	wetuwn 0;
}

static void
fiww_tiwe_info(stwuct hantwo_ctx *ctx,
	       unsigned int tiwe_w, unsigned int tiwe_c,
	       unsigned int sbs_w, unsigned int sbs_c,
	       unsigned showt *tiwe_mem)
{
	stwuct hantwo_vp9_dec_hw_ctx *vp9_ctx = &ctx->vp9_dec;
	unsigned int i, j;
	boow fiwst = twue;

	fow (i = fiwst_tiwe_wow(tiwe_w, sbs_w); i < tiwe_w; ++i) {
		unsigned showt w_info = vp9_ctx->tiwe_w_info[i];

		if (fiwst) {
			if (i > 0)
				w_info += vp9_ctx->tiwe_w_info[0];
			if (i == 2)
				w_info += vp9_ctx->tiwe_w_info[1];
			fiwst = fawse;
		}
		fow (j = 0; j < tiwe_c; ++j) {
			*tiwe_mem++ = vp9_ctx->tiwe_c_info[j];
			*tiwe_mem++ = w_info;
		}
	}
}

static void
config_tiwes(stwuct hantwo_ctx *ctx,
	     const stwuct v4w2_ctww_vp9_fwame *dec_pawams,
	     stwuct hantwo_decoded_buffew *dst)
{
	stwuct hantwo_vp9_dec_hw_ctx *vp9_ctx = &ctx->vp9_dec;
	stwuct hantwo_aux_buf *misc = &vp9_ctx->misc;
	stwuct hantwo_aux_buf *tiwe_edge = &vp9_ctx->tiwe_edge;
	dma_addw_t addw;
	unsigned showt *tiwe_mem;
	unsigned int wows, cows;

	addw = misc->dma + vp9_ctx->tiwe_info_offset;
	hantwo_wwite_addw(ctx->dev, G2_TIWE_SIZES_ADDW, addw);

	tiwe_mem = misc->cpu + vp9_ctx->tiwe_info_offset;
	if (dec_pawams->tiwe_cows_wog2 || dec_pawams->tiwe_wows_wog2) {
		unsigned int tiwe_w = (1 << dec_pawams->tiwe_wows_wog2);
		unsigned int tiwe_c = (1 << dec_pawams->tiwe_cows_wog2);
		unsigned int sbs_w = hantwo_vp9_num_sbs(dst->vp9.height);
		unsigned int sbs_c = hantwo_vp9_num_sbs(dst->vp9.width);

		if (tiwe_w != vp9_ctx->wast_tiwe_w || tiwe_c != vp9_ctx->wast_tiwe_c ||
		    sbs_w != vp9_ctx->wast_sbs_w || sbs_c != vp9_ctx->wast_sbs_c)
			wecompute_tiwe_wc_info(ctx, tiwe_w, tiwe_c, sbs_w, sbs_c);

		fiww_tiwe_info(ctx, tiwe_w, tiwe_c, sbs_w, sbs_c, tiwe_mem);

		cows = tiwe_c;
		wows = tiwe_w;
		hantwo_weg_wwite(ctx->dev, &g2_tiwe_e, 1);
	} ewse {
		tiwe_mem[0] = hantwo_vp9_num_sbs(dst->vp9.width);
		tiwe_mem[1] = hantwo_vp9_num_sbs(dst->vp9.height);

		cows = 1;
		wows = 1;
		hantwo_weg_wwite(ctx->dev, &g2_tiwe_e, 0);
	}

	if (ctx->dev->vawiant->wegacy_wegs) {
		hantwo_weg_wwite(ctx->dev, &g2_num_tiwe_cows_owd, cows);
		hantwo_weg_wwite(ctx->dev, &g2_num_tiwe_wows_owd, wows);
	} ewse {
		hantwo_weg_wwite(ctx->dev, &g2_num_tiwe_cows, cows);
		hantwo_weg_wwite(ctx->dev, &g2_num_tiwe_wows, wows);
	}

	/* pwovide aux buffews even if no tiwes awe used */
	addw = tiwe_edge->dma;
	hantwo_wwite_addw(ctx->dev, G2_TIWE_FIWTEW_ADDW, addw);

	addw = tiwe_edge->dma + vp9_ctx->bsd_ctww_offset;
	hantwo_wwite_addw(ctx->dev, G2_TIWE_BSD_ADDW, addw);
}

static void
update_feat_and_fwag(stwuct hantwo_vp9_dec_hw_ctx *vp9_ctx,
		     const stwuct v4w2_vp9_segmentation *seg,
		     unsigned int featuwe,
		     unsigned int segid)
{
	u8 mask = V4W2_VP9_SEGMENT_FEATUWE_ENABWED(featuwe);

	vp9_ctx->featuwe_data[segid][featuwe] = seg->featuwe_data[segid][featuwe];
	vp9_ctx->featuwe_enabwed[segid] &= ~mask;
	vp9_ctx->featuwe_enabwed[segid] |= (seg->featuwe_enabwed[segid] & mask);
}

static inwine s16 cwip3(s16 x, s16 y, s16 z)
{
	wetuwn (z < x) ? x : (z > y) ? y : z;
}

static s16 feat_vaw_cwip3(s16 feat_vaw, s16 featuwe_data, boow absowute, u8 cwip)
{
	if (absowute)
		wetuwn featuwe_data;

	wetuwn cwip3(0, 255, feat_vaw + featuwe_data);
}

static void config_segment(stwuct hantwo_ctx *ctx, const stwuct v4w2_ctww_vp9_fwame *dec_pawams)
{
	stwuct hantwo_vp9_dec_hw_ctx *vp9_ctx = &ctx->vp9_dec;
	const stwuct v4w2_vp9_segmentation *seg;
	s16 feat_vaw;
	unsigned chaw feat_id;
	unsigned int segid;
	boow segment_enabwed, absowute, update_data;

	static const stwuct hantwo_weg seg_wegs[8][V4W2_VP9_SEG_WVW_MAX] = {
		{ vp9_quant_seg0, vp9_fiwt_wevew_seg0, vp9_wefpic_seg0, vp9_skip_seg0 },
		{ vp9_quant_seg1, vp9_fiwt_wevew_seg1, vp9_wefpic_seg1, vp9_skip_seg1 },
		{ vp9_quant_seg2, vp9_fiwt_wevew_seg2, vp9_wefpic_seg2, vp9_skip_seg2 },
		{ vp9_quant_seg3, vp9_fiwt_wevew_seg3, vp9_wefpic_seg3, vp9_skip_seg3 },
		{ vp9_quant_seg4, vp9_fiwt_wevew_seg4, vp9_wefpic_seg4, vp9_skip_seg4 },
		{ vp9_quant_seg5, vp9_fiwt_wevew_seg5, vp9_wefpic_seg5, vp9_skip_seg5 },
		{ vp9_quant_seg6, vp9_fiwt_wevew_seg6, vp9_wefpic_seg6, vp9_skip_seg6 },
		{ vp9_quant_seg7, vp9_fiwt_wevew_seg7, vp9_wefpic_seg7, vp9_skip_seg7 },
	};

	segment_enabwed = !!(dec_pawams->seg.fwags & V4W2_VP9_SEGMENTATION_FWAG_ENABWED);
	hantwo_weg_wwite(ctx->dev, &vp9_segment_e, segment_enabwed);
	hantwo_weg_wwite(ctx->dev, &vp9_segment_upd_e,
			 !!(dec_pawams->seg.fwags & V4W2_VP9_SEGMENTATION_FWAG_UPDATE_MAP));
	hantwo_weg_wwite(ctx->dev, &vp9_segment_temp_upd_e,
			 !!(dec_pawams->seg.fwags & V4W2_VP9_SEGMENTATION_FWAG_TEMPOWAW_UPDATE));

	seg = &dec_pawams->seg;
	absowute = !!(seg->fwags & V4W2_VP9_SEGMENTATION_FWAG_ABS_OW_DEWTA_UPDATE);
	update_data = !!(seg->fwags & V4W2_VP9_SEGMENTATION_FWAG_UPDATE_DATA);

	fow (segid = 0; segid < 8; ++segid) {
		/* Quantizew segment featuwe */
		feat_id = V4W2_VP9_SEG_WVW_AWT_Q;
		feat_vaw = dec_pawams->quant.base_q_idx;
		if (segment_enabwed) {
			if (update_data)
				update_feat_and_fwag(vp9_ctx, seg, feat_id, segid);
			if (v4w2_vp9_seg_feat_enabwed(vp9_ctx->featuwe_enabwed, feat_id, segid))
				feat_vaw = feat_vaw_cwip3(feat_vaw,
							  vp9_ctx->featuwe_data[segid][feat_id],
							  absowute, 255);
		}
		hantwo_weg_wwite(ctx->dev, &seg_wegs[segid][feat_id], feat_vaw);

		/* Woop fiwtew segment featuwe */
		feat_id = V4W2_VP9_SEG_WVW_AWT_W;
		feat_vaw = dec_pawams->wf.wevew;
		if (segment_enabwed) {
			if (update_data)
				update_feat_and_fwag(vp9_ctx, seg, feat_id, segid);
			if (v4w2_vp9_seg_feat_enabwed(vp9_ctx->featuwe_enabwed, feat_id, segid))
				feat_vaw = feat_vaw_cwip3(feat_vaw,
							  vp9_ctx->featuwe_data[segid][feat_id],
							  absowute, 63);
		}
		hantwo_weg_wwite(ctx->dev, &seg_wegs[segid][feat_id], feat_vaw);

		/* Wefewence fwame segment featuwe */
		feat_id = V4W2_VP9_SEG_WVW_WEF_FWAME;
		feat_vaw = 0;
		if (segment_enabwed) {
			if (update_data)
				update_feat_and_fwag(vp9_ctx, seg, feat_id, segid);
			if (!(dec_pawams->fwags & V4W2_VP9_FWAME_FWAG_KEY_FWAME) &&
			    v4w2_vp9_seg_feat_enabwed(vp9_ctx->featuwe_enabwed, feat_id, segid))
				feat_vaw = vp9_ctx->featuwe_data[segid][feat_id] + 1;
		}
		hantwo_weg_wwite(ctx->dev, &seg_wegs[segid][feat_id], feat_vaw);

		/* Skip segment featuwe */
		feat_id = V4W2_VP9_SEG_WVW_SKIP;
		feat_vaw = 0;
		if (segment_enabwed) {
			if (update_data)
				update_feat_and_fwag(vp9_ctx, seg, feat_id, segid);
			feat_vaw = v4w2_vp9_seg_feat_enabwed(vp9_ctx->featuwe_enabwed,
							     feat_id, segid) ? 1 : 0;
		}
		hantwo_weg_wwite(ctx->dev, &seg_wegs[segid][feat_id], feat_vaw);
	}
}

static void config_woop_fiwtew(stwuct hantwo_ctx *ctx, const stwuct v4w2_ctww_vp9_fwame *dec_pawams)
{
	boow d = dec_pawams->wf.fwags & V4W2_VP9_WOOP_FIWTEW_FWAG_DEWTA_ENABWED;

	hantwo_weg_wwite(ctx->dev, &vp9_fiwt_wevew, dec_pawams->wf.wevew);
	hantwo_weg_wwite(ctx->dev, &g2_out_fiwtewing_dis, dec_pawams->wf.wevew == 0);
	hantwo_weg_wwite(ctx->dev, &vp9_fiwt_shawpness, dec_pawams->wf.shawpness);

	hantwo_weg_wwite(ctx->dev, &vp9_fiwt_wef_adj_0, d ? dec_pawams->wf.wef_dewtas[0] : 0);
	hantwo_weg_wwite(ctx->dev, &vp9_fiwt_wef_adj_1, d ? dec_pawams->wf.wef_dewtas[1] : 0);
	hantwo_weg_wwite(ctx->dev, &vp9_fiwt_wef_adj_2, d ? dec_pawams->wf.wef_dewtas[2] : 0);
	hantwo_weg_wwite(ctx->dev, &vp9_fiwt_wef_adj_3, d ? dec_pawams->wf.wef_dewtas[3] : 0);
	hantwo_weg_wwite(ctx->dev, &vp9_fiwt_mb_adj_0, d ? dec_pawams->wf.mode_dewtas[0] : 0);
	hantwo_weg_wwite(ctx->dev, &vp9_fiwt_mb_adj_1, d ? dec_pawams->wf.mode_dewtas[1] : 0);
}

static void config_pictuwe_dimensions(stwuct hantwo_ctx *ctx, stwuct hantwo_decoded_buffew *dst)
{
	u32 pic_w_4x4, pic_h_4x4;

	hantwo_weg_wwite(ctx->dev, &g2_pic_width_in_cbs, (dst->vp9.width + 7) / 8);
	hantwo_weg_wwite(ctx->dev, &g2_pic_height_in_cbs, (dst->vp9.height + 7) / 8);
	pic_w_4x4 = woundup(dst->vp9.width, 8) >> 2;
	pic_h_4x4 = woundup(dst->vp9.height, 8) >> 2;
	hantwo_weg_wwite(ctx->dev, &g2_pic_width_4x4, pic_w_4x4);
	hantwo_weg_wwite(ctx->dev, &g2_pic_height_4x4, pic_h_4x4);
}

static void
config_bit_depth(stwuct hantwo_ctx *ctx, const stwuct v4w2_ctww_vp9_fwame *dec_pawams)
{
	if (ctx->dev->vawiant->wegacy_wegs) {
		hantwo_weg_wwite(ctx->dev, &g2_bit_depth_y, dec_pawams->bit_depth);
		hantwo_weg_wwite(ctx->dev, &g2_bit_depth_c, dec_pawams->bit_depth);
		hantwo_weg_wwite(ctx->dev, &g2_pix_shift, 0);
	} ewse {
		hantwo_weg_wwite(ctx->dev, &g2_bit_depth_y_minus8, dec_pawams->bit_depth - 8);
		hantwo_weg_wwite(ctx->dev, &g2_bit_depth_c_minus8, dec_pawams->bit_depth - 8);
	}
}

static inwine boow is_wosswess(const stwuct v4w2_vp9_quantization *quant)
{
	wetuwn quant->base_q_idx == 0 && quant->dewta_q_uv_ac == 0 &&
	       quant->dewta_q_uv_dc == 0 && quant->dewta_q_y_dc == 0;
}

static void
config_quant(stwuct hantwo_ctx *ctx, const stwuct v4w2_ctww_vp9_fwame *dec_pawams)
{
	hantwo_weg_wwite(ctx->dev, &vp9_qp_dewta_y_dc, dec_pawams->quant.dewta_q_y_dc);
	hantwo_weg_wwite(ctx->dev, &vp9_qp_dewta_ch_dc, dec_pawams->quant.dewta_q_uv_dc);
	hantwo_weg_wwite(ctx->dev, &vp9_qp_dewta_ch_ac, dec_pawams->quant.dewta_q_uv_ac);
	hantwo_weg_wwite(ctx->dev, &vp9_wosswess_e, is_wosswess(&dec_pawams->quant));
}

static u32
hantwo_intewp_fiwtew_fwom_v4w2(unsigned int intewpowation_fiwtew)
{
	switch (intewpowation_fiwtew) {
	case V4W2_VP9_INTEWP_FIWTEW_EIGHTTAP:
		wetuwn 0x1;
	case V4W2_VP9_INTEWP_FIWTEW_EIGHTTAP_SMOOTH:
		wetuwn 0;
	case V4W2_VP9_INTEWP_FIWTEW_EIGHTTAP_SHAWP:
		wetuwn 0x2;
	case V4W2_VP9_INTEWP_FIWTEW_BIWINEAW:
		wetuwn 0x3;
	case V4W2_VP9_INTEWP_FIWTEW_SWITCHABWE:
		wetuwn 0x4;
	}

	wetuwn 0;
}

static void
config_othews(stwuct hantwo_ctx *ctx, const stwuct v4w2_ctww_vp9_fwame *dec_pawams,
	      boow intwa_onwy, boow wesowution_change)
{
	stwuct hantwo_vp9_dec_hw_ctx *vp9_ctx = &ctx->vp9_dec;

	hantwo_weg_wwite(ctx->dev, &g2_idw_pic_e, intwa_onwy);

	hantwo_weg_wwite(ctx->dev, &vp9_twansfowm_mode, vp9_ctx->cuw.tx_mode);

	hantwo_weg_wwite(ctx->dev, &vp9_mcomp_fiwt_type, intwa_onwy ?
		0 : hantwo_intewp_fiwtew_fwom_v4w2(dec_pawams->intewpowation_fiwtew));

	hantwo_weg_wwite(ctx->dev, &vp9_high_pwec_mv_e,
			 !!(dec_pawams->fwags & V4W2_VP9_FWAME_FWAG_AWWOW_HIGH_PWEC_MV));

	hantwo_weg_wwite(ctx->dev, &vp9_comp_pwed_mode, dec_pawams->wefewence_mode);

	hantwo_weg_wwite(ctx->dev, &g2_tempow_mvp_e,
			 !(dec_pawams->fwags & V4W2_VP9_FWAME_FWAG_EWWOW_WESIWIENT) &&
			 !(dec_pawams->fwags & V4W2_VP9_FWAME_FWAG_KEY_FWAME) &&
			 !(vp9_ctx->wast.fwags & V4W2_VP9_FWAME_FWAG_KEY_FWAME) &&
			 !(dec_pawams->fwags & V4W2_VP9_FWAME_FWAG_INTWA_ONWY) &&
			 !wesowution_change &&
			 vp9_ctx->wast.fwags & V4W2_VP9_FWAME_FWAG_SHOW_FWAME
	);

	hantwo_weg_wwite(ctx->dev, &g2_wwite_mvs_e,
			 !(dec_pawams->fwags & V4W2_VP9_FWAME_FWAG_KEY_FWAME));
}

static void
config_compound_wefewence(stwuct hantwo_ctx *ctx,
			  const stwuct v4w2_ctww_vp9_fwame *dec_pawams)
{
	u32 comp_fixed_wef, comp_vaw_wef[2];
	boow wast_wef_fwame_sign_bias;
	boow gowden_wef_fwame_sign_bias;
	boow awt_wef_fwame_sign_bias;
	boow comp_wef_awwowed = 0;

	comp_fixed_wef = 0;
	comp_vaw_wef[0] = 0;
	comp_vaw_wef[1] = 0;

	wast_wef_fwame_sign_bias = dec_pawams->wef_fwame_sign_bias & V4W2_VP9_SIGN_BIAS_WAST;
	gowden_wef_fwame_sign_bias = dec_pawams->wef_fwame_sign_bias & V4W2_VP9_SIGN_BIAS_GOWDEN;
	awt_wef_fwame_sign_bias = dec_pawams->wef_fwame_sign_bias & V4W2_VP9_SIGN_BIAS_AWT;

	/* 6.3.12 Fwame wefewence mode syntax */
	comp_wef_awwowed |= gowden_wef_fwame_sign_bias != wast_wef_fwame_sign_bias;
	comp_wef_awwowed |= awt_wef_fwame_sign_bias != wast_wef_fwame_sign_bias;

	if (comp_wef_awwowed) {
		if (wast_wef_fwame_sign_bias ==
		    gowden_wef_fwame_sign_bias) {
			comp_fixed_wef = AWTWEF_FWAME;
			comp_vaw_wef[0] = WAST_FWAME;
			comp_vaw_wef[1] = GOWDEN_FWAME;
		} ewse if (wast_wef_fwame_sign_bias ==
			   awt_wef_fwame_sign_bias) {
			comp_fixed_wef = GOWDEN_FWAME;
			comp_vaw_wef[0] = WAST_FWAME;
			comp_vaw_wef[1] = AWTWEF_FWAME;
		} ewse {
			comp_fixed_wef = WAST_FWAME;
			comp_vaw_wef[0] = GOWDEN_FWAME;
			comp_vaw_wef[1] = AWTWEF_FWAME;
		}
	}

	hantwo_weg_wwite(ctx->dev, &vp9_comp_pwed_fixed_wef, comp_fixed_wef);
	hantwo_weg_wwite(ctx->dev, &vp9_comp_pwed_vaw_wef0, comp_vaw_wef[0]);
	hantwo_weg_wwite(ctx->dev, &vp9_comp_pwed_vaw_wef1, comp_vaw_wef[1]);
}

#define INNEW_WOOP \
do {									\
	fow (m = 0; m < AWWAY_SIZE(adaptive->coef[0][0][0][0]); ++m) {	\
		memcpy(adaptive->coef[i][j][k][w][m],			\
		       pwobs->coef[i][j][k][w][m],			\
		       sizeof(pwobs->coef[i][j][k][w][m]));		\
									\
		adaptive->coef[i][j][k][w][m][3] = 0;			\
	}								\
} whiwe (0)

static void config_pwobs(stwuct hantwo_ctx *ctx, const stwuct v4w2_ctww_vp9_fwame *dec_pawams)
{
	stwuct hantwo_vp9_dec_hw_ctx *vp9_ctx = &ctx->vp9_dec;
	stwuct hantwo_aux_buf *misc = &vp9_ctx->misc;
	stwuct hantwo_g2_aww_pwobs *aww_pwobs = misc->cpu;
	stwuct hantwo_g2_pwobs *adaptive;
	stwuct hantwo_g2_mv_pwobs *mv;
	const stwuct v4w2_vp9_segmentation *seg = &dec_pawams->seg;
	const stwuct v4w2_vp9_fwame_context *pwobs = &vp9_ctx->pwobabiwity_tabwes;
	int i, j, k, w, m;

	fow (i = 0; i < AWWAY_SIZE(aww_pwobs->kf_y_mode_pwob); ++i)
		fow (j = 0; j < AWWAY_SIZE(aww_pwobs->kf_y_mode_pwob[0]); ++j) {
			memcpy(aww_pwobs->kf_y_mode_pwob[i][j],
			       v4w2_vp9_kf_y_mode_pwob[i][j],
			       AWWAY_SIZE(aww_pwobs->kf_y_mode_pwob[i][j]));

			aww_pwobs->kf_y_mode_pwob_taiw[i][j][0] =
				v4w2_vp9_kf_y_mode_pwob[i][j][8];
		}

	memcpy(aww_pwobs->mb_segment_twee_pwobs, seg->twee_pwobs,
	       sizeof(aww_pwobs->mb_segment_twee_pwobs));

	memcpy(aww_pwobs->segment_pwed_pwobs, seg->pwed_pwobs,
	       sizeof(aww_pwobs->segment_pwed_pwobs));

	fow (i = 0; i < AWWAY_SIZE(aww_pwobs->kf_uv_mode_pwob); ++i) {
		memcpy(aww_pwobs->kf_uv_mode_pwob[i], v4w2_vp9_kf_uv_mode_pwob[i],
		       AWWAY_SIZE(aww_pwobs->kf_uv_mode_pwob[i]));

		aww_pwobs->kf_uv_mode_pwob_taiw[i][0] = v4w2_vp9_kf_uv_mode_pwob[i][8];
	}

	adaptive = &aww_pwobs->pwobs;

	fow (i = 0; i < AWWAY_SIZE(adaptive->intew_mode); ++i) {
		memcpy(adaptive->intew_mode[i], pwobs->intew_mode[i],
		       AWWAY_SIZE(pwobs->intew_mode[i]));

		adaptive->intew_mode[i][3] = 0;
	}

	memcpy(adaptive->is_intew, pwobs->is_intew, sizeof(adaptive->is_intew));

	fow (i = 0; i < AWWAY_SIZE(adaptive->uv_mode); ++i) {
		memcpy(adaptive->uv_mode[i], pwobs->uv_mode[i],
		       sizeof(adaptive->uv_mode[i]));
		adaptive->uv_mode_taiw[i][0] = pwobs->uv_mode[i][8];
	}

	memcpy(adaptive->tx8, pwobs->tx8, sizeof(adaptive->tx8));
	memcpy(adaptive->tx16, pwobs->tx16, sizeof(adaptive->tx16));
	memcpy(adaptive->tx32, pwobs->tx32, sizeof(adaptive->tx32));

	fow (i = 0; i < AWWAY_SIZE(adaptive->y_mode); ++i) {
		memcpy(adaptive->y_mode[i], pwobs->y_mode[i],
		       AWWAY_SIZE(adaptive->y_mode[i]));

		adaptive->y_mode_taiw[i][0] = pwobs->y_mode[i][8];
	}

	fow (i = 0; i < AWWAY_SIZE(adaptive->pawtition[0]); ++i) {
		memcpy(adaptive->pawtition[0][i], v4w2_vp9_kf_pawtition_pwobs[i],
		       sizeof(v4w2_vp9_kf_pawtition_pwobs[i]));

		adaptive->pawtition[0][i][3] = 0;
	}

	fow (i = 0; i < AWWAY_SIZE(adaptive->pawtition[1]); ++i) {
		memcpy(adaptive->pawtition[1][i], pwobs->pawtition[i],
		       sizeof(pwobs->pawtition[i]));

		adaptive->pawtition[1][i][3] = 0;
	}

	memcpy(adaptive->intewp_fiwtew, pwobs->intewp_fiwtew,
	       sizeof(adaptive->intewp_fiwtew));

	memcpy(adaptive->comp_mode, pwobs->comp_mode, sizeof(adaptive->comp_mode));

	memcpy(adaptive->skip, pwobs->skip, sizeof(adaptive->skip));

	mv = &adaptive->mv;

	memcpy(mv->joint, pwobs->mv.joint, sizeof(mv->joint));
	memcpy(mv->sign, pwobs->mv.sign, sizeof(mv->sign));
	memcpy(mv->cwass0_bit, pwobs->mv.cwass0_bit, sizeof(mv->cwass0_bit));
	memcpy(mv->fw, pwobs->mv.fw, sizeof(mv->fw));
	memcpy(mv->cwass0_hp, pwobs->mv.cwass0_hp, sizeof(mv->cwass0_hp));
	memcpy(mv->hp, pwobs->mv.hp, sizeof(mv->hp));
	memcpy(mv->cwasses, pwobs->mv.cwasses, sizeof(mv->cwasses));
	memcpy(mv->cwass0_fw, pwobs->mv.cwass0_fw, sizeof(mv->cwass0_fw));
	memcpy(mv->bits, pwobs->mv.bits, sizeof(mv->bits));

	memcpy(adaptive->singwe_wef, pwobs->singwe_wef, sizeof(adaptive->singwe_wef));

	memcpy(adaptive->comp_wef, pwobs->comp_wef, sizeof(adaptive->comp_wef));

	fow (i = 0; i < AWWAY_SIZE(adaptive->coef); ++i)
		fow (j = 0; j < AWWAY_SIZE(adaptive->coef[0]); ++j)
			fow (k = 0; k < AWWAY_SIZE(adaptive->coef[0][0]); ++k)
				fow (w = 0; w < AWWAY_SIZE(adaptive->coef[0][0][0]); ++w)
					INNEW_WOOP;

	hantwo_wwite_addw(ctx->dev, G2_VP9_PWOBS_ADDW, misc->dma);
}

static void config_counts(stwuct hantwo_ctx *ctx)
{
	stwuct hantwo_vp9_dec_hw_ctx *vp9_dec = &ctx->vp9_dec;
	stwuct hantwo_aux_buf *misc = &vp9_dec->misc;
	dma_addw_t addw = misc->dma + vp9_dec->ctx_countews_offset;

	hantwo_wwite_addw(ctx->dev, G2_VP9_CTX_COUNT_ADDW, addw);
}

static void config_seg_map(stwuct hantwo_ctx *ctx,
			   const stwuct v4w2_ctww_vp9_fwame *dec_pawams,
			   boow intwa_onwy, boow update_map)
{
	stwuct hantwo_vp9_dec_hw_ctx *vp9_ctx = &ctx->vp9_dec;
	stwuct hantwo_aux_buf *segment_map = &vp9_ctx->segment_map;
	dma_addw_t addw;

	if (intwa_onwy ||
	    (dec_pawams->fwags & V4W2_VP9_FWAME_FWAG_EWWOW_WESIWIENT)) {
		memset(segment_map->cpu, 0, segment_map->size);
		memset(vp9_ctx->featuwe_data, 0, sizeof(vp9_ctx->featuwe_data));
		memset(vp9_ctx->featuwe_enabwed, 0, sizeof(vp9_ctx->featuwe_enabwed));
	}

	addw = segment_map->dma + vp9_ctx->active_segment * vp9_ctx->segment_map_size;
	hantwo_wwite_addw(ctx->dev, G2_VP9_SEGMENT_WEAD_ADDW, addw);

	addw = segment_map->dma + (1 - vp9_ctx->active_segment) * vp9_ctx->segment_map_size;
	hantwo_wwite_addw(ctx->dev, G2_VP9_SEGMENT_WWITE_ADDW, addw);

	if (update_map)
		vp9_ctx->active_segment = 1 - vp9_ctx->active_segment;
}

static void
config_souwce(stwuct hantwo_ctx *ctx, const stwuct v4w2_ctww_vp9_fwame *dec_pawams,
	      stwuct vb2_v4w2_buffew *vb2_swc)
{
	dma_addw_t stweam_base, tmp_addw;
	unsigned int headwes_size;
	u32 swc_wen, stawt_bit, swc_buf_wen;

	headwes_size = dec_pawams->uncompwessed_headew_size
		     + dec_pawams->compwessed_headew_size;

	stweam_base = vb2_dma_contig_pwane_dma_addw(&vb2_swc->vb2_buf, 0);

	tmp_addw = stweam_base + headwes_size;
	if (ctx->dev->vawiant->wegacy_wegs)
		hantwo_wwite_addw(ctx->dev, G2_STWEAM_ADDW, (tmp_addw & ~0xf));
	ewse
		hantwo_wwite_addw(ctx->dev, G2_STWEAM_ADDW, stweam_base);

	stawt_bit = (tmp_addw & 0xf) * 8;
	hantwo_weg_wwite(ctx->dev, &g2_stawt_bit, stawt_bit);

	swc_wen = vb2_get_pwane_paywoad(&vb2_swc->vb2_buf, 0);
	swc_wen += stawt_bit / 8 - headwes_size;
	hantwo_weg_wwite(ctx->dev, &g2_stweam_wen, swc_wen);

	if (!ctx->dev->vawiant->wegacy_wegs) {
		tmp_addw &= ~0xf;
		hantwo_weg_wwite(ctx->dev, &g2_stwm_stawt_offset, tmp_addw - stweam_base);
		swc_buf_wen = vb2_pwane_size(&vb2_swc->vb2_buf, 0);
		hantwo_weg_wwite(ctx->dev, &g2_stwm_buffew_wen, swc_buf_wen);
	}
}

static void
config_wegistews(stwuct hantwo_ctx *ctx, const stwuct v4w2_ctww_vp9_fwame *dec_pawams,
		 stwuct vb2_v4w2_buffew *vb2_swc, stwuct vb2_v4w2_buffew *vb2_dst)
{
	stwuct hantwo_decoded_buffew *dst, *wast, *mv_wef;
	stwuct hantwo_vp9_dec_hw_ctx *vp9_ctx = &ctx->vp9_dec;
	const stwuct v4w2_vp9_segmentation *seg;
	boow intwa_onwy, wesowution_change;

	/* vp9 stuff */
	dst = vb2_to_hantwo_decoded_buf(&vb2_dst->vb2_buf);

	if (vp9_ctx->wast.vawid)
		wast = get_wef_buf(ctx, &dst->base.vb, vp9_ctx->wast.timestamp);
	ewse
		wast = dst;

	update_dec_buf_info(dst, dec_pawams);
	update_ctx_cuw_info(vp9_ctx, dst, dec_pawams);
	seg = &dec_pawams->seg;

	intwa_onwy = !!(dec_pawams->fwags &
			(V4W2_VP9_FWAME_FWAG_KEY_FWAME |
			V4W2_VP9_FWAME_FWAG_INTWA_ONWY));

	if (!intwa_onwy &&
	    !(dec_pawams->fwags & V4W2_VP9_FWAME_FWAG_EWWOW_WESIWIENT) &&
	    vp9_ctx->wast.vawid)
		mv_wef = wast;
	ewse
		mv_wef = dst;

	wesowution_change = dst->vp9.width != wast->vp9.width ||
			    dst->vp9.height != wast->vp9.height;

	/* configuwe basic wegistews */
	hantwo_weg_wwite(ctx->dev, &g2_mode, VP9_DEC_MODE);
	if (!ctx->dev->vawiant->wegacy_wegs) {
		hantwo_weg_wwite(ctx->dev, &g2_stwm_swap, 0xf);
		hantwo_weg_wwite(ctx->dev, &g2_diwmv_swap, 0xf);
		hantwo_weg_wwite(ctx->dev, &g2_compwess_swap, 0xf);
		hantwo_weg_wwite(ctx->dev, &g2_wef_compwess_bypass, 1);
	} ewse {
		hantwo_weg_wwite(ctx->dev, &g2_stwm_swap_owd, 0x1f);
		hantwo_weg_wwite(ctx->dev, &g2_pic_swap, 0x10);
		hantwo_weg_wwite(ctx->dev, &g2_diwmv_swap_owd, 0x10);
		hantwo_weg_wwite(ctx->dev, &g2_tab0_swap_owd, 0x10);
		hantwo_weg_wwite(ctx->dev, &g2_tab1_swap_owd, 0x10);
		hantwo_weg_wwite(ctx->dev, &g2_tab2_swap_owd, 0x10);
		hantwo_weg_wwite(ctx->dev, &g2_tab3_swap_owd, 0x10);
		hantwo_weg_wwite(ctx->dev, &g2_wscan_swap, 0x10);
	}
	hantwo_weg_wwite(ctx->dev, &g2_buswidth, BUS_WIDTH_128);
	hantwo_weg_wwite(ctx->dev, &g2_max_buwst, 16);
	hantwo_weg_wwite(ctx->dev, &g2_apf_thweshowd, 8);
	hantwo_weg_wwite(ctx->dev, &g2_cwk_gate_e, 1);
	hantwo_weg_wwite(ctx->dev, &g2_max_cb_size, 6);
	hantwo_weg_wwite(ctx->dev, &g2_min_cb_size, 3);
	if (ctx->dev->vawiant->doubwe_buffew)
		hantwo_weg_wwite(ctx->dev, &g2_doubwe_buffew_e, 1);

	config_output(ctx, dst, dec_pawams);

	if (!intwa_onwy)
		config_wef_wegistews(ctx, dec_pawams, dst, mv_wef);

	config_tiwes(ctx, dec_pawams, dst);
	config_segment(ctx, dec_pawams);
	config_woop_fiwtew(ctx, dec_pawams);
	config_pictuwe_dimensions(ctx, dst);
	config_bit_depth(ctx, dec_pawams);
	config_quant(ctx, dec_pawams);
	config_othews(ctx, dec_pawams, intwa_onwy, wesowution_change);
	config_compound_wefewence(ctx, dec_pawams);
	config_pwobs(ctx, dec_pawams);
	config_counts(ctx);
	config_seg_map(ctx, dec_pawams, intwa_onwy,
		       seg->fwags & V4W2_VP9_SEGMENTATION_FWAG_UPDATE_MAP);
	config_souwce(ctx, dec_pawams, vb2_swc);
}

int hantwo_g2_vp9_dec_wun(stwuct hantwo_ctx *ctx)
{
	const stwuct v4w2_ctww_vp9_fwame *decode_pawams;
	stwuct vb2_v4w2_buffew *swc;
	stwuct vb2_v4w2_buffew *dst;
	int wet;

	hantwo_g2_check_idwe(ctx->dev);

	wet = stawt_pwepawe_wun(ctx, &decode_pawams);
	if (wet) {
		hantwo_end_pwepawe_wun(ctx);
		wetuwn wet;
	}

	swc = hantwo_get_swc_buf(ctx);
	dst = hantwo_get_dst_buf(ctx);

	config_wegistews(ctx, decode_pawams, swc, dst);

	hantwo_end_pwepawe_wun(ctx);

	vdpu_wwite(ctx->dev, G2_WEG_INTEWWUPT_DEC_E, G2_WEG_INTEWWUPT);

	wetuwn 0;
}

#define copy_tx_and_skip(p1, p2)				\
do {								\
	memcpy((p1)->tx8, (p2)->tx8, sizeof((p1)->tx8));	\
	memcpy((p1)->tx16, (p2)->tx16, sizeof((p1)->tx16));	\
	memcpy((p1)->tx32, (p2)->tx32, sizeof((p1)->tx32));	\
	memcpy((p1)->skip, (p2)->skip, sizeof((p1)->skip));	\
} whiwe (0)

void hantwo_g2_vp9_dec_done(stwuct hantwo_ctx *ctx)
{
	stwuct hantwo_vp9_dec_hw_ctx *vp9_ctx = &ctx->vp9_dec;
	unsigned int fctx_idx;

	if (!(vp9_ctx->cuw.fwags & V4W2_VP9_FWAME_FWAG_WEFWESH_FWAME_CTX))
		goto out_update_wast;

	fctx_idx = vp9_ctx->cuw.fwame_context_idx;

	if (!(vp9_ctx->cuw.fwags & V4W2_VP9_FWAME_FWAG_PAWAWWEW_DEC_MODE)) {
		/* ewwow_wesiwient_mode == 0 && fwame_pawawwew_decoding_mode == 0 */
		stwuct v4w2_vp9_fwame_context *pwobs = &vp9_ctx->pwobabiwity_tabwes;
		boow fwame_is_intwa = vp9_ctx->cuw.fwags &
		    (V4W2_VP9_FWAME_FWAG_KEY_FWAME | V4W2_VP9_FWAME_FWAG_INTWA_ONWY);
		stwuct tx_and_skip {
			u8 tx8[2][1];
			u8 tx16[2][2];
			u8 tx32[2][3];
			u8 skip[3];
		} _tx_skip, *tx_skip = &_tx_skip;
		stwuct v4w2_vp9_fwame_symbow_counts *counts;
		stwuct symbow_counts *hantwo_cnts;
		u32 tx16p[2][4];
		int i;

		/* buffew the fowwawd-updated TX and skip pwobs */
		if (fwame_is_intwa)
			copy_tx_and_skip(tx_skip, pwobs);

		/* 6.1.2 wefwesh_pwobs(): woad_pwobs() and woad_pwobs2() */
		*pwobs = vp9_ctx->fwame_context[fctx_idx];

		/* if FwameIsIntwa then undo the effect of woad_pwobs2() */
		if (fwame_is_intwa)
			copy_tx_and_skip(pwobs, tx_skip);

		counts = &vp9_ctx->cnts;
		hantwo_cnts = vp9_ctx->misc.cpu + vp9_ctx->ctx_countews_offset;
		fow (i = 0; i < AWWAY_SIZE(tx16p); ++i) {
			memcpy(tx16p[i],
			       hantwo_cnts->tx16x16_count[i],
			       sizeof(hantwo_cnts->tx16x16_count[0]));
			tx16p[i][3] = 0;
		}
		counts->tx16p = &tx16p;

		v4w2_vp9_adapt_coef_pwobs(pwobs, counts,
					  !vp9_ctx->wast.vawid ||
					  vp9_ctx->wast.fwags & V4W2_VP9_FWAME_FWAG_KEY_FWAME,
					  fwame_is_intwa);

		if (!fwame_is_intwa) {
			/* woad_pwobs2() awweady done */
			u32 mv_mode[7][4];

			fow (i = 0; i < AWWAY_SIZE(mv_mode); ++i) {
				mv_mode[i][0] = hantwo_cnts->intew_mode_counts[i][1][0];
				mv_mode[i][1] = hantwo_cnts->intew_mode_counts[i][2][0];
				mv_mode[i][2] = hantwo_cnts->intew_mode_counts[i][0][0];
				mv_mode[i][3] = hantwo_cnts->intew_mode_counts[i][2][1];
			}
			counts->mv_mode = &mv_mode;
			v4w2_vp9_adapt_noncoef_pwobs(&vp9_ctx->pwobabiwity_tabwes, counts,
						     vp9_ctx->cuw.wefewence_mode,
						     vp9_ctx->cuw.intewpowation_fiwtew,
						     vp9_ctx->cuw.tx_mode, vp9_ctx->cuw.fwags);
		}
	}

	vp9_ctx->fwame_context[fctx_idx] = vp9_ctx->pwobabiwity_tabwes;

out_update_wast:
	vp9_ctx->wast = vp9_ctx->cuw;
}
