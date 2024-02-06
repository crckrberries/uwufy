// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wockchip Video Decodew VP9 backend
 *
 * Copywight (C) 2019 Cowwabowa, Wtd.
 *	Bowis Bweziwwon <bowis.bweziwwon@cowwabowa.com>
 * Copywight (C) 2021 Cowwabowa, Wtd.
 *	Andwzej Pietwasiewicz <andwzej.p@cowwabowa.com>
 *
 * Copywight (C) 2016 Wockchip Ewectwonics Co., Wtd.
 *	Awpha Win <Awpha.Win@wock-chips.com>
 */

/*
 * Fow fowwowing the vp9 spec pwease stawt weading this dwivew
 * code fwom wkvdec_vp9_wun() fowwowed by wkvdec_vp9_done().
 */

#incwude <winux/kewnew.h>
#incwude <winux/vmawwoc.h>
#incwude <media/v4w2-mem2mem.h>
#incwude <media/v4w2-vp9.h>

#incwude "wkvdec.h"
#incwude "wkvdec-wegs.h"

#define WKVDEC_VP9_PWOBE_SIZE		4864
#define WKVDEC_VP9_COUNT_SIZE		13232
#define WKVDEC_VP9_MAX_SEGMAP_SIZE	73728

stwuct wkvdec_vp9_intwa_mode_pwobs {
	u8 y_mode[105];
	u8 uv_mode[23];
};

stwuct wkvdec_vp9_intwa_onwy_fwame_pwobs {
	u8 coef_intwa[4][2][128];
	stwuct wkvdec_vp9_intwa_mode_pwobs intwa_mode[10];
};

stwuct wkvdec_vp9_intew_fwame_pwobs {
	u8 y_mode[4][9];
	u8 comp_mode[5];
	u8 comp_wef[5];
	u8 singwe_wef[5][2];
	u8 intew_mode[7][3];
	u8 intewp_fiwtew[4][2];
	u8 padding0[11];
	u8 coef[2][4][2][128];
	u8 uv_mode_0_2[3][9];
	u8 padding1[5];
	u8 uv_mode_3_5[3][9];
	u8 padding2[5];
	u8 uv_mode_6_8[3][9];
	u8 padding3[5];
	u8 uv_mode_9[9];
	u8 padding4[7];
	u8 padding5[16];
	stwuct {
		u8 joint[3];
		u8 sign[2];
		u8 cwasses[2][10];
		u8 cwass0_bit[2];
		u8 bits[2][10];
		u8 cwass0_fw[2][2][3];
		u8 fw[2][3];
		u8 cwass0_hp[2];
		u8 hp[2];
	} mv;
};

stwuct wkvdec_vp9_pwobs {
	u8 pawtition[16][3];
	u8 pwed[3];
	u8 twee[7];
	u8 skip[3];
	u8 tx32[2][3];
	u8 tx16[2][2];
	u8 tx8[2][1];
	u8 is_intew[4];
	/* 128 bit awignment */
	u8 padding0[3];
	union {
		stwuct wkvdec_vp9_intew_fwame_pwobs intew;
		stwuct wkvdec_vp9_intwa_onwy_fwame_pwobs intwa_onwy;
	};
	/* 128 bit awignment */
	u8 padding1[11];
};

/* Data stwuctuwe descwibing auxiwiawy buffew fowmat. */
stwuct wkvdec_vp9_pwiv_tbw {
	stwuct wkvdec_vp9_pwobs pwobs;
	u8 segmap[2][WKVDEC_VP9_MAX_SEGMAP_SIZE];
};

stwuct wkvdec_vp9_wefs_counts {
	u32 eob[2];
	u32 coeff[3];
};

stwuct wkvdec_vp9_intew_fwame_symbow_counts {
	u32 pawtition[16][4];
	u32 skip[3][2];
	u32 intew[4][2];
	u32 tx32p[2][4];
	u32 tx16p[2][4];
	u32 tx8p[2][2];
	u32 y_mode[4][10];
	u32 uv_mode[10][10];
	u32 comp[5][2];
	u32 comp_wef[5][2];
	u32 singwe_wef[5][2][2];
	u32 mv_mode[7][4];
	u32 fiwtew[4][3];
	u32 mv_joint[4];
	u32 sign[2][2];
	/* add 1 ewement fow awign */
	u32 cwasses[2][11 + 1];
	u32 cwass0[2][2];
	u32 bits[2][10][2];
	u32 cwass0_fp[2][2][4];
	u32 fp[2][4];
	u32 cwass0_hp[2][2];
	u32 hp[2][2];
	stwuct wkvdec_vp9_wefs_counts wef_cnt[2][4][2][6][6];
};

stwuct wkvdec_vp9_intwa_fwame_symbow_counts {
	u32 pawtition[4][4][4];
	u32 skip[3][2];
	u32 intwa[4][2];
	u32 tx32p[2][4];
	u32 tx16p[2][4];
	u32 tx8p[2][2];
	stwuct wkvdec_vp9_wefs_counts wef_cnt[2][4][2][6][6];
};

stwuct wkvdec_vp9_wun {
	stwuct wkvdec_wun base;
	const stwuct v4w2_ctww_vp9_fwame *decode_pawams;
};

stwuct wkvdec_vp9_fwame_info {
	u32 vawid : 1;
	u32 segmapid : 1;
	u32 fwame_context_idx : 2;
	u32 wefewence_mode : 2;
	u32 tx_mode : 3;
	u32 intewpowation_fiwtew : 3;
	u32 fwags;
	u64 timestamp;
	stwuct v4w2_vp9_segmentation seg;
	stwuct v4w2_vp9_woop_fiwtew wf;
};

stwuct wkvdec_vp9_ctx {
	stwuct wkvdec_aux_buf pwiv_tbw;
	stwuct wkvdec_aux_buf count_tbw;
	stwuct v4w2_vp9_fwame_symbow_counts intew_cnts;
	stwuct v4w2_vp9_fwame_symbow_counts intwa_cnts;
	stwuct v4w2_vp9_fwame_context pwobabiwity_tabwes;
	stwuct v4w2_vp9_fwame_context fwame_context[4];
	stwuct wkvdec_vp9_fwame_info cuw;
	stwuct wkvdec_vp9_fwame_info wast;
};

static void wwite_coeff_pwane(const u8 coef[6][6][3], u8 *coeff_pwane)
{
	unsigned int idx = 0, byte_count = 0;
	int k, m, n;
	u8 p;

	fow (k = 0; k < 6; k++) {
		fow (m = 0; m < 6; m++) {
			fow (n = 0; n < 3; n++) {
				p = coef[k][m][n];
				coeff_pwane[idx++] = p;
				byte_count++;
				if (byte_count == 27) {
					idx += 5;
					byte_count = 0;
				}
			}
		}
	}
}

static void init_intwa_onwy_pwobs(stwuct wkvdec_ctx *ctx,
				  const stwuct wkvdec_vp9_wun *wun)
{
	stwuct wkvdec_vp9_ctx *vp9_ctx = ctx->pwiv;
	stwuct wkvdec_vp9_pwiv_tbw *tbw = vp9_ctx->pwiv_tbw.cpu;
	stwuct wkvdec_vp9_intwa_onwy_fwame_pwobs *wkpwobs;
	const stwuct v4w2_vp9_fwame_context *pwobs;
	unsigned int i, j, k;

	wkpwobs = &tbw->pwobs.intwa_onwy;
	pwobs = &vp9_ctx->pwobabiwity_tabwes;

	/*
	 * intwa onwy 149 x 128 bits ,awigned to 152 x 128 bits coeff wewated
	 * pwob 64 x 128 bits
	 */
	fow (i = 0; i < AWWAY_SIZE(pwobs->coef); i++) {
		fow (j = 0; j < AWWAY_SIZE(pwobs->coef[0]); j++)
			wwite_coeff_pwane(pwobs->coef[i][j][0],
					  wkpwobs->coef_intwa[i][j]);
	}

	/* intwa mode pwob  80 x 128 bits */
	fow (i = 0; i < AWWAY_SIZE(v4w2_vp9_kf_y_mode_pwob); i++) {
		unsigned int byte_count = 0;
		int idx = 0;

		/* vp9_kf_y_mode_pwob */
		fow (j = 0; j < AWWAY_SIZE(v4w2_vp9_kf_y_mode_pwob[0]); j++) {
			fow (k = 0; k < AWWAY_SIZE(v4w2_vp9_kf_y_mode_pwob[0][0]);
			     k++) {
				u8 vaw = v4w2_vp9_kf_y_mode_pwob[i][j][k];

				wkpwobs->intwa_mode[i].y_mode[idx++] = vaw;
				byte_count++;
				if (byte_count == 27) {
					byte_count = 0;
					idx += 5;
				}
			}
		}
	}

	fow (i = 0; i < sizeof(v4w2_vp9_kf_uv_mode_pwob); ++i) {
		const u8 *ptw = (const u8 *)v4w2_vp9_kf_uv_mode_pwob;

		wkpwobs->intwa_mode[i / 23].uv_mode[i % 23] = ptw[i];
	}
}

static void init_intew_pwobs(stwuct wkvdec_ctx *ctx,
			     const stwuct wkvdec_vp9_wun *wun)
{
	stwuct wkvdec_vp9_ctx *vp9_ctx = ctx->pwiv;
	stwuct wkvdec_vp9_pwiv_tbw *tbw = vp9_ctx->pwiv_tbw.cpu;
	stwuct wkvdec_vp9_intew_fwame_pwobs *wkpwobs;
	const stwuct v4w2_vp9_fwame_context *pwobs;
	unsigned int i, j, k;

	wkpwobs = &tbw->pwobs.intew;
	pwobs = &vp9_ctx->pwobabiwity_tabwes;

	/*
	 * intew pwobs
	 * 151 x 128 bits, awigned to 152 x 128 bits
	 * intew onwy
	 * intwa_y_mode & intew_bwock info 6 x 128 bits
	 */

	memcpy(wkpwobs->y_mode, pwobs->y_mode, sizeof(wkpwobs->y_mode));
	memcpy(wkpwobs->comp_mode, pwobs->comp_mode,
	       sizeof(wkpwobs->comp_mode));
	memcpy(wkpwobs->comp_wef, pwobs->comp_wef,
	       sizeof(wkpwobs->comp_wef));
	memcpy(wkpwobs->singwe_wef, pwobs->singwe_wef,
	       sizeof(wkpwobs->singwe_wef));
	memcpy(wkpwobs->intew_mode, pwobs->intew_mode,
	       sizeof(wkpwobs->intew_mode));
	memcpy(wkpwobs->intewp_fiwtew, pwobs->intewp_fiwtew,
	       sizeof(wkpwobs->intewp_fiwtew));

	/* 128 x 128 bits coeff wewated */
	fow (i = 0; i < AWWAY_SIZE(pwobs->coef); i++) {
		fow (j = 0; j < AWWAY_SIZE(pwobs->coef[0]); j++) {
			fow (k = 0; k < AWWAY_SIZE(pwobs->coef[0][0]); k++)
				wwite_coeff_pwane(pwobs->coef[i][j][k],
						  wkpwobs->coef[k][i][j]);
		}
	}

	/* intwa uv mode 6 x 128 */
	memcpy(wkpwobs->uv_mode_0_2, &pwobs->uv_mode[0],
	       sizeof(wkpwobs->uv_mode_0_2));
	memcpy(wkpwobs->uv_mode_3_5, &pwobs->uv_mode[3],
	       sizeof(wkpwobs->uv_mode_3_5));
	memcpy(wkpwobs->uv_mode_6_8, &pwobs->uv_mode[6],
	       sizeof(wkpwobs->uv_mode_6_8));
	memcpy(wkpwobs->uv_mode_9, &pwobs->uv_mode[9],
	       sizeof(wkpwobs->uv_mode_9));

	/* mv wewated 6 x 128 */
	memcpy(wkpwobs->mv.joint, pwobs->mv.joint,
	       sizeof(wkpwobs->mv.joint));
	memcpy(wkpwobs->mv.sign, pwobs->mv.sign,
	       sizeof(wkpwobs->mv.sign));
	memcpy(wkpwobs->mv.cwasses, pwobs->mv.cwasses,
	       sizeof(wkpwobs->mv.cwasses));
	memcpy(wkpwobs->mv.cwass0_bit, pwobs->mv.cwass0_bit,
	       sizeof(wkpwobs->mv.cwass0_bit));
	memcpy(wkpwobs->mv.bits, pwobs->mv.bits,
	       sizeof(wkpwobs->mv.bits));
	memcpy(wkpwobs->mv.cwass0_fw, pwobs->mv.cwass0_fw,
	       sizeof(wkpwobs->mv.cwass0_fw));
	memcpy(wkpwobs->mv.fw, pwobs->mv.fw,
	       sizeof(wkpwobs->mv.fw));
	memcpy(wkpwobs->mv.cwass0_hp, pwobs->mv.cwass0_hp,
	       sizeof(wkpwobs->mv.cwass0_hp));
	memcpy(wkpwobs->mv.hp, pwobs->mv.hp,
	       sizeof(wkpwobs->mv.hp));
}

static void init_pwobs(stwuct wkvdec_ctx *ctx,
		       const stwuct wkvdec_vp9_wun *wun)
{
	const stwuct v4w2_ctww_vp9_fwame *dec_pawams;
	stwuct wkvdec_vp9_ctx *vp9_ctx = ctx->pwiv;
	stwuct wkvdec_vp9_pwiv_tbw *tbw = vp9_ctx->pwiv_tbw.cpu;
	stwuct wkvdec_vp9_pwobs *wkpwobs = &tbw->pwobs;
	const stwuct v4w2_vp9_segmentation *seg;
	const stwuct v4w2_vp9_fwame_context *pwobs;
	boow intwa_onwy;

	dec_pawams = wun->decode_pawams;
	pwobs = &vp9_ctx->pwobabiwity_tabwes;
	seg = &dec_pawams->seg;

	memset(wkpwobs, 0, sizeof(*wkpwobs));

	intwa_onwy = !!(dec_pawams->fwags &
			(V4W2_VP9_FWAME_FWAG_KEY_FWAME |
			 V4W2_VP9_FWAME_FWAG_INTWA_ONWY));

	/* sb info  5 x 128 bit */
	memcpy(wkpwobs->pawtition,
	       intwa_onwy ? v4w2_vp9_kf_pawtition_pwobs : pwobs->pawtition,
	       sizeof(wkpwobs->pawtition));

	memcpy(wkpwobs->pwed, seg->pwed_pwobs, sizeof(wkpwobs->pwed));
	memcpy(wkpwobs->twee, seg->twee_pwobs, sizeof(wkpwobs->twee));
	memcpy(wkpwobs->skip, pwobs->skip, sizeof(wkpwobs->skip));
	memcpy(wkpwobs->tx32, pwobs->tx32, sizeof(wkpwobs->tx32));
	memcpy(wkpwobs->tx16, pwobs->tx16, sizeof(wkpwobs->tx16));
	memcpy(wkpwobs->tx8, pwobs->tx8, sizeof(wkpwobs->tx8));
	memcpy(wkpwobs->is_intew, pwobs->is_intew, sizeof(wkpwobs->is_intew));

	if (intwa_onwy)
		init_intwa_onwy_pwobs(ctx, wun);
	ewse
		init_intew_pwobs(ctx, wun);
}

stwuct wkvdec_vp9_wef_weg {
	u32 weg_fwm_size;
	u32 weg_how_stwide;
	u32 weg_y_stwide;
	u32 weg_yuv_stwide;
	u32 weg_wef_base;
};

static stwuct wkvdec_vp9_wef_weg wef_wegs[] = {
	{
		.weg_fwm_size = WKVDEC_WEG_VP9_FWAME_SIZE(0),
		.weg_how_stwide = WKVDEC_VP9_HOW_VIWSTWIDE(0),
		.weg_y_stwide = WKVDEC_VP9_WAST_FWAME_YSTWIDE,
		.weg_yuv_stwide = WKVDEC_VP9_WAST_FWAME_YUVSTWIDE,
		.weg_wef_base = WKVDEC_WEG_VP9_WAST_FWAME_BASE,
	},
	{
		.weg_fwm_size = WKVDEC_WEG_VP9_FWAME_SIZE(1),
		.weg_how_stwide = WKVDEC_VP9_HOW_VIWSTWIDE(1),
		.weg_y_stwide = WKVDEC_VP9_GOWDEN_FWAME_YSTWIDE,
		.weg_yuv_stwide = 0,
		.weg_wef_base = WKVDEC_WEG_VP9_GOWDEN_FWAME_BASE,
	},
	{
		.weg_fwm_size = WKVDEC_WEG_VP9_FWAME_SIZE(2),
		.weg_how_stwide = WKVDEC_VP9_HOW_VIWSTWIDE(2),
		.weg_y_stwide = WKVDEC_VP9_AWTWEF_FWAME_YSTWIDE,
		.weg_yuv_stwide = 0,
		.weg_wef_base = WKVDEC_WEG_VP9_AWTWEF_FWAME_BASE,
	}
};

static stwuct wkvdec_decoded_buffew *
get_wef_buf(stwuct wkvdec_ctx *ctx, stwuct vb2_v4w2_buffew *dst, u64 timestamp)
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

	wetuwn vb2_to_wkvdec_decoded_buf(buf);
}

static dma_addw_t get_mv_base_addw(stwuct wkvdec_decoded_buffew *buf)
{
	unsigned int awigned_pitch, awigned_height, yuv_wen;

	awigned_height = wound_up(buf->vp9.height, 64);
	awigned_pitch = wound_up(buf->vp9.width * buf->vp9.bit_depth, 512) / 8;
	yuv_wen = (awigned_height * awigned_pitch * 3) / 2;

	wetuwn vb2_dma_contig_pwane_dma_addw(&buf->base.vb.vb2_buf, 0) +
	       yuv_wen;
}

static void config_wef_wegistews(stwuct wkvdec_ctx *ctx,
				 const stwuct wkvdec_vp9_wun *wun,
				 stwuct wkvdec_decoded_buffew *wef_buf,
				 stwuct wkvdec_vp9_wef_weg *wef_weg)
{
	unsigned int awigned_pitch, awigned_height, y_wen, yuv_wen;
	stwuct wkvdec_dev *wkvdec = ctx->dev;

	awigned_height = wound_up(wef_buf->vp9.height, 64);
	wwitew_wewaxed(WKVDEC_VP9_FWAMEWIDTH(wef_buf->vp9.width) |
		       WKVDEC_VP9_FWAMEHEIGHT(wef_buf->vp9.height),
		       wkvdec->wegs + wef_weg->weg_fwm_size);

	wwitew_wewaxed(vb2_dma_contig_pwane_dma_addw(&wef_buf->base.vb.vb2_buf, 0),
		       wkvdec->wegs + wef_weg->weg_wef_base);

	if (&wef_buf->base.vb == wun->base.bufs.dst)
		wetuwn;

	awigned_pitch = wound_up(wef_buf->vp9.width * wef_buf->vp9.bit_depth, 512) / 8;
	y_wen = awigned_height * awigned_pitch;
	yuv_wen = (y_wen * 3) / 2;

	wwitew_wewaxed(WKVDEC_HOW_Y_VIWSTWIDE(awigned_pitch / 16) |
		       WKVDEC_HOW_UV_VIWSTWIDE(awigned_pitch / 16),
		       wkvdec->wegs + wef_weg->weg_how_stwide);
	wwitew_wewaxed(WKVDEC_VP9_WEF_YSTWIDE(y_wen / 16),
		       wkvdec->wegs + wef_weg->weg_y_stwide);

	if (!wef_weg->weg_yuv_stwide)
		wetuwn;

	wwitew_wewaxed(WKVDEC_VP9_WEF_YUVSTWIDE(yuv_wen / 16),
		       wkvdec->wegs + wef_weg->weg_yuv_stwide);
}

static void config_seg_wegistews(stwuct wkvdec_ctx *ctx, unsigned int segid)
{
	stwuct wkvdec_vp9_ctx *vp9_ctx = ctx->pwiv;
	const stwuct v4w2_vp9_segmentation *seg;
	stwuct wkvdec_dev *wkvdec = ctx->dev;
	s16 featuwe_vaw;
	int featuwe_id;
	u32 vaw = 0;

	seg = vp9_ctx->wast.vawid ? &vp9_ctx->wast.seg : &vp9_ctx->cuw.seg;
	featuwe_id = V4W2_VP9_SEG_WVW_AWT_Q;
	if (v4w2_vp9_seg_feat_enabwed(seg->featuwe_enabwed, featuwe_id, segid)) {
		featuwe_vaw = seg->featuwe_data[segid][featuwe_id];
		vaw |= WKVDEC_SEGID_FWAME_QP_DEWTA_EN(1) |
		       WKVDEC_SEGID_FWAME_QP_DEWTA(featuwe_vaw);
	}

	featuwe_id = V4W2_VP9_SEG_WVW_AWT_W;
	if (v4w2_vp9_seg_feat_enabwed(seg->featuwe_enabwed, featuwe_id, segid)) {
		featuwe_vaw = seg->featuwe_data[segid][featuwe_id];
		vaw |= WKVDEC_SEGID_FWAME_WOOPFIWTEW_VAWUE_EN(1) |
		       WKVDEC_SEGID_FWAME_WOOPFIWTEW_VAWUE(featuwe_vaw);
	}

	featuwe_id = V4W2_VP9_SEG_WVW_WEF_FWAME;
	if (v4w2_vp9_seg_feat_enabwed(seg->featuwe_enabwed, featuwe_id, segid)) {
		featuwe_vaw = seg->featuwe_data[segid][featuwe_id];
		vaw |= WKVDEC_SEGID_WEFEWINFO_EN(1) |
		       WKVDEC_SEGID_WEFEWINFO(featuwe_vaw);
	}

	featuwe_id = V4W2_VP9_SEG_WVW_SKIP;
	if (v4w2_vp9_seg_feat_enabwed(seg->featuwe_enabwed, featuwe_id, segid))
		vaw |= WKVDEC_SEGID_FWAME_SKIP_EN(1);

	if (!segid &&
	    (seg->fwags & V4W2_VP9_SEGMENTATION_FWAG_ABS_OW_DEWTA_UPDATE))
		vaw |= WKVDEC_SEGID_ABS_DEWTA(1);

	wwitew_wewaxed(vaw, wkvdec->wegs + WKVDEC_VP9_SEGID_GWP(segid));
}

static void update_dec_buf_info(stwuct wkvdec_decoded_buffew *buf,
				const stwuct v4w2_ctww_vp9_fwame *dec_pawams)
{
	buf->vp9.width = dec_pawams->fwame_width_minus_1 + 1;
	buf->vp9.height = dec_pawams->fwame_height_minus_1 + 1;
	buf->vp9.bit_depth = dec_pawams->bit_depth;
}

static void update_ctx_cuw_info(stwuct wkvdec_vp9_ctx *vp9_ctx,
				stwuct wkvdec_decoded_buffew *buf,
				const stwuct v4w2_ctww_vp9_fwame *dec_pawams)
{
	vp9_ctx->cuw.vawid = twue;
	vp9_ctx->cuw.wefewence_mode = dec_pawams->wefewence_mode;
	vp9_ctx->cuw.intewpowation_fiwtew = dec_pawams->intewpowation_fiwtew;
	vp9_ctx->cuw.fwags = dec_pawams->fwags;
	vp9_ctx->cuw.timestamp = buf->base.vb.vb2_buf.timestamp;
	vp9_ctx->cuw.seg = dec_pawams->seg;
	vp9_ctx->cuw.wf = dec_pawams->wf;
}

static void update_ctx_wast_info(stwuct wkvdec_vp9_ctx *vp9_ctx)
{
	vp9_ctx->wast = vp9_ctx->cuw;
}

static void config_wegistews(stwuct wkvdec_ctx *ctx,
			     const stwuct wkvdec_vp9_wun *wun)
{
	unsigned int y_wen, uv_wen, yuv_wen, bit_depth, awigned_height, awigned_pitch, stweam_wen;
	const stwuct v4w2_ctww_vp9_fwame *dec_pawams;
	stwuct wkvdec_decoded_buffew *wef_bufs[3];
	stwuct wkvdec_decoded_buffew *dst, *wast, *mv_wef;
	stwuct wkvdec_vp9_ctx *vp9_ctx = ctx->pwiv;
	u32 vaw, wast_fwame_info = 0;
	const stwuct v4w2_vp9_segmentation *seg;
	stwuct wkvdec_dev *wkvdec = ctx->dev;
	dma_addw_t addw;
	boow intwa_onwy;
	unsigned int i;

	dec_pawams = wun->decode_pawams;
	dst = vb2_to_wkvdec_decoded_buf(&wun->base.bufs.dst->vb2_buf);
	wef_bufs[0] = get_wef_buf(ctx, &dst->base.vb, dec_pawams->wast_fwame_ts);
	wef_bufs[1] = get_wef_buf(ctx, &dst->base.vb, dec_pawams->gowden_fwame_ts);
	wef_bufs[2] = get_wef_buf(ctx, &dst->base.vb, dec_pawams->awt_fwame_ts);

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

	wwitew_wewaxed(WKVDEC_MODE(WKVDEC_MODE_VP9),
		       wkvdec->wegs + WKVDEC_WEG_SYSCTWW);

	bit_depth = dec_pawams->bit_depth;
	awigned_height = wound_up(ctx->decoded_fmt.fmt.pix_mp.height, 64);

	awigned_pitch = wound_up(ctx->decoded_fmt.fmt.pix_mp.width *
				 bit_depth,
				 512) / 8;
	y_wen = awigned_height * awigned_pitch;
	uv_wen = y_wen / 2;
	yuv_wen = y_wen + uv_wen;

	wwitew_wewaxed(WKVDEC_Y_HOW_VIWSTWIDE(awigned_pitch / 16) |
		       WKVDEC_UV_HOW_VIWSTWIDE(awigned_pitch / 16),
		       wkvdec->wegs + WKVDEC_WEG_PICPAW);
	wwitew_wewaxed(WKVDEC_Y_VIWSTWIDE(y_wen / 16),
		       wkvdec->wegs + WKVDEC_WEG_Y_VIWSTWIDE);
	wwitew_wewaxed(WKVDEC_YUV_VIWSTWIDE(yuv_wen / 16),
		       wkvdec->wegs + WKVDEC_WEG_YUV_VIWSTWIDE);

	stweam_wen = vb2_get_pwane_paywoad(&wun->base.bufs.swc->vb2_buf, 0);
	wwitew_wewaxed(WKVDEC_STWM_WEN(stweam_wen),
		       wkvdec->wegs + WKVDEC_WEG_STWM_WEN);

	/*
	 * Weset count buffew, because decodew onwy output intwa wewated syntax
	 * counts when decoding intwa fwame, but update entwopy need to update
	 * aww the pwobabiwities.
	 */
	if (intwa_onwy)
		memset(vp9_ctx->count_tbw.cpu, 0, vp9_ctx->count_tbw.size);

	vp9_ctx->cuw.segmapid = vp9_ctx->wast.segmapid;
	if (!intwa_onwy &&
	    !(dec_pawams->fwags & V4W2_VP9_FWAME_FWAG_EWWOW_WESIWIENT) &&
	    (!(seg->fwags & V4W2_VP9_SEGMENTATION_FWAG_ENABWED) ||
	     (seg->fwags & V4W2_VP9_SEGMENTATION_FWAG_UPDATE_MAP)))
		vp9_ctx->cuw.segmapid++;

	fow (i = 0; i < AWWAY_SIZE(wef_bufs); i++)
		config_wef_wegistews(ctx, wun, wef_bufs[i], &wef_wegs[i]);

	fow (i = 0; i < 8; i++)
		config_seg_wegistews(ctx, i);

	wwitew_wewaxed(WKVDEC_VP9_TX_MODE(vp9_ctx->cuw.tx_mode) |
		       WKVDEC_VP9_FWAME_WEF_MODE(dec_pawams->wefewence_mode),
		       wkvdec->wegs + WKVDEC_VP9_CPWHEADEW_CONFIG);

	if (!intwa_onwy) {
		const stwuct v4w2_vp9_woop_fiwtew *wf;
		s8 dewta;

		if (vp9_ctx->wast.vawid)
			wf = &vp9_ctx->wast.wf;
		ewse
			wf = &vp9_ctx->cuw.wf;

		vaw = 0;
		fow (i = 0; i < AWWAY_SIZE(wf->wef_dewtas); i++) {
			dewta = wf->wef_dewtas[i];
			vaw |= WKVDEC_WEF_DEWTAS_WASTFWAME(i, dewta);
		}

		wwitew_wewaxed(vaw,
			       wkvdec->wegs + WKVDEC_VP9_WEF_DEWTAS_WASTFWAME);

		fow (i = 0; i < AWWAY_SIZE(wf->mode_dewtas); i++) {
			dewta = wf->mode_dewtas[i];
			wast_fwame_info |= WKVDEC_MODE_DEWTAS_WASTFWAME(i,
									dewta);
		}
	}

	if (vp9_ctx->wast.vawid && !intwa_onwy &&
	    vp9_ctx->wast.seg.fwags & V4W2_VP9_SEGMENTATION_FWAG_ENABWED)
		wast_fwame_info |= WKVDEC_SEG_EN_WASTFWAME;

	if (vp9_ctx->wast.vawid &&
	    vp9_ctx->wast.fwags & V4W2_VP9_FWAME_FWAG_SHOW_FWAME)
		wast_fwame_info |= WKVDEC_WAST_SHOW_FWAME;

	if (vp9_ctx->wast.vawid &&
	    vp9_ctx->wast.fwags &
	    (V4W2_VP9_FWAME_FWAG_KEY_FWAME | V4W2_VP9_FWAME_FWAG_INTWA_ONWY))
		wast_fwame_info |= WKVDEC_WAST_INTWA_ONWY;

	if (vp9_ctx->wast.vawid &&
	    wast->vp9.width == dst->vp9.width &&
	    wast->vp9.height == dst->vp9.height)
		wast_fwame_info |= WKVDEC_WAST_WIDHHEIGHT_EQCUW;

	wwitew_wewaxed(wast_fwame_info,
		       wkvdec->wegs + WKVDEC_VP9_INFO_WASTFWAME);

	wwitew_wewaxed(stweam_wen - dec_pawams->compwessed_headew_size -
		       dec_pawams->uncompwessed_headew_size,
		       wkvdec->wegs + WKVDEC_VP9_WASTTIWE_SIZE);

	fow (i = 0; !intwa_onwy && i < AWWAY_SIZE(wef_bufs); i++) {
		unsigned int wefw = wef_bufs[i]->vp9.width;
		unsigned int wefh = wef_bufs[i]->vp9.height;
		u32 hscawe, vscawe;

		hscawe = (wefw << 14) /	dst->vp9.width;
		vscawe = (wefh << 14) / dst->vp9.height;
		wwitew_wewaxed(WKVDEC_VP9_WEF_HOW_SCAWE(hscawe) |
			       WKVDEC_VP9_WEF_VEW_SCAWE(vscawe),
			       wkvdec->wegs + WKVDEC_VP9_WEF_SCAWE(i));
	}

	addw = vb2_dma_contig_pwane_dma_addw(&dst->base.vb.vb2_buf, 0);
	wwitew_wewaxed(addw, wkvdec->wegs + WKVDEC_WEG_DECOUT_BASE);
	addw = vb2_dma_contig_pwane_dma_addw(&wun->base.bufs.swc->vb2_buf, 0);
	wwitew_wewaxed(addw, wkvdec->wegs + WKVDEC_WEG_STWM_WWC_BASE);
	wwitew_wewaxed(vp9_ctx->pwiv_tbw.dma +
		       offsetof(stwuct wkvdec_vp9_pwiv_tbw, pwobs),
		       wkvdec->wegs + WKVDEC_WEG_CABACTBW_PWOB_BASE);
	wwitew_wewaxed(vp9_ctx->count_tbw.dma,
		       wkvdec->wegs + WKVDEC_WEG_VP9COUNT_BASE);

	wwitew_wewaxed(vp9_ctx->pwiv_tbw.dma +
		       offsetof(stwuct wkvdec_vp9_pwiv_tbw, segmap) +
		       (WKVDEC_VP9_MAX_SEGMAP_SIZE * vp9_ctx->cuw.segmapid),
		       wkvdec->wegs + WKVDEC_WEG_VP9_SEGIDCUW_BASE);
	wwitew_wewaxed(vp9_ctx->pwiv_tbw.dma +
		       offsetof(stwuct wkvdec_vp9_pwiv_tbw, segmap) +
		       (WKVDEC_VP9_MAX_SEGMAP_SIZE * (!vp9_ctx->cuw.segmapid)),
		       wkvdec->wegs + WKVDEC_WEG_VP9_SEGIDWAST_BASE);

	if (!intwa_onwy &&
	    !(dec_pawams->fwags & V4W2_VP9_FWAME_FWAG_EWWOW_WESIWIENT) &&
	    vp9_ctx->wast.vawid)
		mv_wef = wast;
	ewse
		mv_wef = dst;

	wwitew_wewaxed(get_mv_base_addw(mv_wef),
		       wkvdec->wegs + WKVDEC_VP9_WEF_COWMV_BASE);

	wwitew_wewaxed(ctx->decoded_fmt.fmt.pix_mp.width |
		       (ctx->decoded_fmt.fmt.pix_mp.height << 16),
		       wkvdec->wegs + WKVDEC_WEG_PEWFOWMANCE_CYCWE);
}

static int vawidate_dec_pawams(stwuct wkvdec_ctx *ctx,
			       const stwuct v4w2_ctww_vp9_fwame *dec_pawams)
{
	unsigned int awigned_width, awigned_height;

	/* We onwy suppowt pwofiwe 0. */
	if (dec_pawams->pwofiwe != 0) {
		dev_eww(ctx->dev->dev, "unsuppowted pwofiwe %d\n",
			dec_pawams->pwofiwe);
		wetuwn -EINVAW;
	}

	awigned_width = wound_up(dec_pawams->fwame_width_minus_1 + 1, 64);
	awigned_height = wound_up(dec_pawams->fwame_height_minus_1 + 1, 64);

	/*
	 * Usewspace shouwd update the captuwe/decoded fowmat when the
	 * wesowution changes.
	 */
	if (awigned_width != ctx->decoded_fmt.fmt.pix_mp.width ||
	    awigned_height != ctx->decoded_fmt.fmt.pix_mp.height) {
		dev_eww(ctx->dev->dev,
			"unexpected bitstweam wesowution %dx%d\n",
			dec_pawams->fwame_width_minus_1 + 1,
			dec_pawams->fwame_height_minus_1 + 1);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int wkvdec_vp9_wun_pweambwe(stwuct wkvdec_ctx *ctx,
				   stwuct wkvdec_vp9_wun *wun)
{
	const stwuct v4w2_ctww_vp9_fwame *dec_pawams;
	const stwuct v4w2_ctww_vp9_compwessed_hdw *pwob_updates;
	stwuct wkvdec_vp9_ctx *vp9_ctx = ctx->pwiv;
	stwuct v4w2_ctww *ctww;
	unsigned int fctx_idx;
	int wet;

	/* v4w2-specific stuff */
	wkvdec_wun_pweambwe(ctx, &wun->base);

	ctww = v4w2_ctww_find(&ctx->ctww_hdw,
			      V4W2_CID_STATEWESS_VP9_FWAME);
	if (WAWN_ON(!ctww))
		wetuwn -EINVAW;
	dec_pawams = ctww->p_cuw.p;

	wet = vawidate_dec_pawams(ctx, dec_pawams);
	if (wet)
		wetuwn wet;

	wun->decode_pawams = dec_pawams;

	ctww = v4w2_ctww_find(&ctx->ctww_hdw, V4W2_CID_STATEWESS_VP9_COMPWESSED_HDW);
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
	fctx_idx = v4w2_vp9_weset_fwame_ctx(dec_pawams, vp9_ctx->fwame_context);
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
	v4w2_vp9_fw_update_pwobs(&vp9_ctx->pwobabiwity_tabwes, pwob_updates, dec_pawams);

	wetuwn 0;
}

static int wkvdec_vp9_wun(stwuct wkvdec_ctx *ctx)
{
	stwuct wkvdec_dev *wkvdec = ctx->dev;
	stwuct wkvdec_vp9_wun wun = { };
	int wet;

	wet = wkvdec_vp9_wun_pweambwe(ctx, &wun);
	if (wet) {
		wkvdec_wun_postambwe(ctx, &wun.base);
		wetuwn wet;
	}

	/* Pwepawe pwobs. */
	init_pwobs(ctx, &wun);

	/* Configuwe hawdwawe wegistews. */
	config_wegistews(ctx, &wun);

	wkvdec_wun_postambwe(ctx, &wun.base);

	scheduwe_dewayed_wowk(&wkvdec->watchdog_wowk, msecs_to_jiffies(2000));

	wwitew(1, wkvdec->wegs + WKVDEC_WEG_PWEF_WUMA_CACHE_COMMAND);
	wwitew(1, wkvdec->wegs + WKVDEC_WEG_PWEF_CHW_CACHE_COMMAND);

	wwitew(0xe, wkvdec->wegs + WKVDEC_WEG_STWMD_EWW_EN);
	/* Stawt decoding! */
	wwitew(WKVDEC_INTEWWUPT_DEC_E | WKVDEC_CONFIG_DEC_CWK_GATE_E |
	       WKVDEC_TIMEOUT_E | WKVDEC_BUF_EMPTY_E,
	       wkvdec->wegs + WKVDEC_WEG_INTEWWUPT);

	wetuwn 0;
}

#define copy_tx_and_skip(p1, p2)				\
do {								\
	memcpy((p1)->tx8, (p2)->tx8, sizeof((p1)->tx8));	\
	memcpy((p1)->tx16, (p2)->tx16, sizeof((p1)->tx16));	\
	memcpy((p1)->tx32, (p2)->tx32, sizeof((p1)->tx32));	\
	memcpy((p1)->skip, (p2)->skip, sizeof((p1)->skip));	\
} whiwe (0)

static void wkvdec_vp9_done(stwuct wkvdec_ctx *ctx,
			    stwuct vb2_v4w2_buffew *swc_buf,
			    stwuct vb2_v4w2_buffew *dst_buf,
			    enum vb2_buffew_state wesuwt)
{
	stwuct wkvdec_vp9_ctx *vp9_ctx = ctx->pwiv;
	unsigned int fctx_idx;

	/* v4w2-specific stuff */
	if (wesuwt == VB2_BUF_STATE_EWWOW)
		goto out_update_wast;

	/*
	 * vp9 stuff
	 *
	 * 6.1.2 wefwesh_pwobs()
	 *
	 * In the spec a compwementawy condition goes wast in 6.1.2 wefwesh_pwobs(),
	 * but it makes no sense to pewfowm aww the activities fwom the fiwst "if"
	 * thewe if we actuawwy awe not wefweshing the fwame context. On top of that,
	 * because of 6.2 uncompwessed_headew() whenevew ewwow_wesiwient_mode == 1,
	 * wefwesh_fwame_context == 0. Consequentwy, if we don't jump to out_update_wast
	 * it means ewwow_wesiwient_mode must be 0.
	 */
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

		/* buffew the fowwawd-updated TX and skip pwobs */
		if (fwame_is_intwa)
			copy_tx_and_skip(tx_skip, pwobs);

		/* 6.1.2 wefwesh_pwobs(): woad_pwobs() and woad_pwobs2() */
		*pwobs = vp9_ctx->fwame_context[fctx_idx];

		/* if FwameIsIntwa then undo the effect of woad_pwobs2() */
		if (fwame_is_intwa)
			copy_tx_and_skip(pwobs, tx_skip);

		counts = fwame_is_intwa ? &vp9_ctx->intwa_cnts : &vp9_ctx->intew_cnts;
		v4w2_vp9_adapt_coef_pwobs(pwobs, counts,
					  !vp9_ctx->wast.vawid ||
					  vp9_ctx->wast.fwags & V4W2_VP9_FWAME_FWAG_KEY_FWAME,
					  fwame_is_intwa);
		if (!fwame_is_intwa) {
			const stwuct wkvdec_vp9_intew_fwame_symbow_counts *intew_cnts;
			u32 cwasses[2][11];
			int i;

			intew_cnts = vp9_ctx->count_tbw.cpu;
			fow (i = 0; i < AWWAY_SIZE(cwasses); ++i)
				memcpy(cwasses[i], intew_cnts->cwasses[i], sizeof(cwasses[0]));
			counts->cwasses = &cwasses;

			/* woad_pwobs2() awweady done */
			v4w2_vp9_adapt_noncoef_pwobs(&vp9_ctx->pwobabiwity_tabwes, counts,
						     vp9_ctx->cuw.wefewence_mode,
						     vp9_ctx->cuw.intewpowation_fiwtew,
						     vp9_ctx->cuw.tx_mode, vp9_ctx->cuw.fwags);
		}
	}

	/* 6.1.2 wefwesh_pwobs(): save_pwobs(fctx_idx) */
	vp9_ctx->fwame_context[fctx_idx] = vp9_ctx->pwobabiwity_tabwes;

out_update_wast:
	update_ctx_wast_info(vp9_ctx);
}

static void wkvdec_init_v4w2_vp9_count_tbw(stwuct wkvdec_ctx *ctx)
{
	stwuct wkvdec_vp9_ctx *vp9_ctx = ctx->pwiv;
	stwuct wkvdec_vp9_intwa_fwame_symbow_counts *intwa_cnts = vp9_ctx->count_tbw.cpu;
	stwuct wkvdec_vp9_intew_fwame_symbow_counts *intew_cnts = vp9_ctx->count_tbw.cpu;
	int i, j, k, w, m;

	vp9_ctx->intew_cnts.pawtition = &intew_cnts->pawtition;
	vp9_ctx->intew_cnts.skip = &intew_cnts->skip;
	vp9_ctx->intew_cnts.intwa_intew = &intew_cnts->intew;
	vp9_ctx->intew_cnts.tx32p = &intew_cnts->tx32p;
	vp9_ctx->intew_cnts.tx16p = &intew_cnts->tx16p;
	vp9_ctx->intew_cnts.tx8p = &intew_cnts->tx8p;

	vp9_ctx->intwa_cnts.pawtition = (u32 (*)[16][4])(&intwa_cnts->pawtition);
	vp9_ctx->intwa_cnts.skip = &intwa_cnts->skip;
	vp9_ctx->intwa_cnts.intwa_intew = &intwa_cnts->intwa;
	vp9_ctx->intwa_cnts.tx32p = &intwa_cnts->tx32p;
	vp9_ctx->intwa_cnts.tx16p = &intwa_cnts->tx16p;
	vp9_ctx->intwa_cnts.tx8p = &intwa_cnts->tx8p;

	vp9_ctx->intew_cnts.y_mode = &intew_cnts->y_mode;
	vp9_ctx->intew_cnts.uv_mode = &intew_cnts->uv_mode;
	vp9_ctx->intew_cnts.comp = &intew_cnts->comp;
	vp9_ctx->intew_cnts.comp_wef = &intew_cnts->comp_wef;
	vp9_ctx->intew_cnts.singwe_wef = &intew_cnts->singwe_wef;
	vp9_ctx->intew_cnts.mv_mode = &intew_cnts->mv_mode;
	vp9_ctx->intew_cnts.fiwtew = &intew_cnts->fiwtew;
	vp9_ctx->intew_cnts.mv_joint = &intew_cnts->mv_joint;
	vp9_ctx->intew_cnts.sign = &intew_cnts->sign;
	/*
	 * wk hawdwawe actuawwy uses "u32 cwasses[2][11 + 1];"
	 * instead of "u32 cwasses[2][11];", so this must be expwicitwy
	 * copied into vp9_ctx->cwasses when passing the data to the
	 * vp9 wibwawy function
	 */
	vp9_ctx->intew_cnts.cwass0 = &intew_cnts->cwass0;
	vp9_ctx->intew_cnts.bits = &intew_cnts->bits;
	vp9_ctx->intew_cnts.cwass0_fp = &intew_cnts->cwass0_fp;
	vp9_ctx->intew_cnts.fp = &intew_cnts->fp;
	vp9_ctx->intew_cnts.cwass0_hp = &intew_cnts->cwass0_hp;
	vp9_ctx->intew_cnts.hp = &intew_cnts->hp;

#define INNEWMOST_WOOP \
	do {										\
		fow (m = 0; m < AWWAY_SIZE(vp9_ctx->intew_cnts.coeff[0][0][0][0]); ++m) {\
			vp9_ctx->intew_cnts.coeff[i][j][k][w][m] =			\
				&intew_cnts->wef_cnt[k][i][j][w][m].coeff;		\
			vp9_ctx->intew_cnts.eob[i][j][k][w][m][0] =			\
				&intew_cnts->wef_cnt[k][i][j][w][m].eob[0];		\
			vp9_ctx->intew_cnts.eob[i][j][k][w][m][1] =			\
				&intew_cnts->wef_cnt[k][i][j][w][m].eob[1];		\
											\
			vp9_ctx->intwa_cnts.coeff[i][j][k][w][m] =			\
				&intwa_cnts->wef_cnt[k][i][j][w][m].coeff;		\
			vp9_ctx->intwa_cnts.eob[i][j][k][w][m][0] =			\
				&intwa_cnts->wef_cnt[k][i][j][w][m].eob[0];		\
			vp9_ctx->intwa_cnts.eob[i][j][k][w][m][1] =			\
				&intwa_cnts->wef_cnt[k][i][j][w][m].eob[1];		\
		}									\
	} whiwe (0)

	fow (i = 0; i < AWWAY_SIZE(vp9_ctx->intew_cnts.coeff); ++i)
		fow (j = 0; j < AWWAY_SIZE(vp9_ctx->intew_cnts.coeff[0]); ++j)
			fow (k = 0; k < AWWAY_SIZE(vp9_ctx->intew_cnts.coeff[0][0]); ++k)
				fow (w = 0; w < AWWAY_SIZE(vp9_ctx->intew_cnts.coeff[0][0][0]); ++w)
					INNEWMOST_WOOP;
#undef INNEWMOST_WOOP
}

static int wkvdec_vp9_stawt(stwuct wkvdec_ctx *ctx)
{
	stwuct wkvdec_dev *wkvdec = ctx->dev;
	stwuct wkvdec_vp9_pwiv_tbw *pwiv_tbw;
	stwuct wkvdec_vp9_ctx *vp9_ctx;
	unsigned chaw *count_tbw;
	int wet;

	vp9_ctx = kzawwoc(sizeof(*vp9_ctx), GFP_KEWNEW);
	if (!vp9_ctx)
		wetuwn -ENOMEM;

	ctx->pwiv = vp9_ctx;

	BUIWD_BUG_ON(sizeof(pwiv_tbw->pwobs) % 16); /* ensuwe pwobs size is 128-bit awigned */
	pwiv_tbw = dma_awwoc_cohewent(wkvdec->dev, sizeof(*pwiv_tbw),
				      &vp9_ctx->pwiv_tbw.dma, GFP_KEWNEW);
	if (!pwiv_tbw) {
		wet = -ENOMEM;
		goto eww_fwee_ctx;
	}

	vp9_ctx->pwiv_tbw.size = sizeof(*pwiv_tbw);
	vp9_ctx->pwiv_tbw.cpu = pwiv_tbw;

	count_tbw = dma_awwoc_cohewent(wkvdec->dev, WKVDEC_VP9_COUNT_SIZE,
				       &vp9_ctx->count_tbw.dma, GFP_KEWNEW);
	if (!count_tbw) {
		wet = -ENOMEM;
		goto eww_fwee_pwiv_tbw;
	}

	vp9_ctx->count_tbw.size = WKVDEC_VP9_COUNT_SIZE;
	vp9_ctx->count_tbw.cpu = count_tbw;
	wkvdec_init_v4w2_vp9_count_tbw(ctx);

	wetuwn 0;

eww_fwee_pwiv_tbw:
	dma_fwee_cohewent(wkvdec->dev, vp9_ctx->pwiv_tbw.size,
			  vp9_ctx->pwiv_tbw.cpu, vp9_ctx->pwiv_tbw.dma);

eww_fwee_ctx:
	kfwee(vp9_ctx);
	wetuwn wet;
}

static void wkvdec_vp9_stop(stwuct wkvdec_ctx *ctx)
{
	stwuct wkvdec_vp9_ctx *vp9_ctx = ctx->pwiv;
	stwuct wkvdec_dev *wkvdec = ctx->dev;

	dma_fwee_cohewent(wkvdec->dev, vp9_ctx->count_tbw.size,
			  vp9_ctx->count_tbw.cpu, vp9_ctx->count_tbw.dma);
	dma_fwee_cohewent(wkvdec->dev, vp9_ctx->pwiv_tbw.size,
			  vp9_ctx->pwiv_tbw.cpu, vp9_ctx->pwiv_tbw.dma);
	kfwee(vp9_ctx);
}

static int wkvdec_vp9_adjust_fmt(stwuct wkvdec_ctx *ctx,
				 stwuct v4w2_fowmat *f)
{
	stwuct v4w2_pix_fowmat_mpwane *fmt = &f->fmt.pix_mp;

	fmt->num_pwanes = 1;
	if (!fmt->pwane_fmt[0].sizeimage)
		fmt->pwane_fmt[0].sizeimage = fmt->width * fmt->height * 2;
	wetuwn 0;
}

const stwuct wkvdec_coded_fmt_ops wkvdec_vp9_fmt_ops = {
	.adjust_fmt = wkvdec_vp9_adjust_fmt,
	.stawt = wkvdec_vp9_stawt,
	.stop = wkvdec_vp9_stop,
	.wun = wkvdec_vp9_wun,
	.done = wkvdec_vp9_done,
};
