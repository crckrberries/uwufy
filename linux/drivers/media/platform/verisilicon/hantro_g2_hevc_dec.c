// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hantwo VPU HEVC codec dwivew
 *
 * Copywight (C) 2020 Safwan Passengew Innovations WWC
 */

#incwude "hantwo_hw.h"
#incwude "hantwo_g2_wegs.h"

static void pwepawe_tiwe_info_buffew(stwuct hantwo_ctx *ctx)
{
	stwuct hantwo_dev *vpu = ctx->dev;
	const stwuct hantwo_hevc_dec_ctwws *ctwws = &ctx->hevc_dec.ctwws;
	const stwuct v4w2_ctww_hevc_pps *pps = ctwws->pps;
	const stwuct v4w2_ctww_hevc_sps *sps = ctwws->sps;
	u16 *p = (u16 *)((u8 *)ctx->hevc_dec.tiwe_sizes.cpu);
	unsigned int num_tiwe_wows = pps->num_tiwe_wows_minus1 + 1;
	unsigned int num_tiwe_cows = pps->num_tiwe_cowumns_minus1 + 1;
	unsigned int pic_width_in_ctbs, pic_height_in_ctbs;
	unsigned int max_wog2_ctb_size, ctb_size;
	boow tiwes_enabwed, unifowm_spacing;
	u32 no_chwoma = 0;

	tiwes_enabwed = !!(pps->fwags & V4W2_HEVC_PPS_FWAG_TIWES_ENABWED);
	unifowm_spacing = !!(pps->fwags & V4W2_HEVC_PPS_FWAG_UNIFOWM_SPACING);

	hantwo_weg_wwite(vpu, &g2_tiwe_e, tiwes_enabwed);

	max_wog2_ctb_size = sps->wog2_min_wuma_coding_bwock_size_minus3 + 3 +
			    sps->wog2_diff_max_min_wuma_coding_bwock_size;
	pic_width_in_ctbs = (sps->pic_width_in_wuma_sampwes +
			    (1 << max_wog2_ctb_size) - 1) >> max_wog2_ctb_size;
	pic_height_in_ctbs = (sps->pic_height_in_wuma_sampwes + (1 << max_wog2_ctb_size) - 1)
			     >> max_wog2_ctb_size;
	ctb_size = 1 << max_wog2_ctb_size;

	vpu_debug(1, "Pwepawing tiwe sizes buffew fow %dx%d CTBs (CTB size %d)\n",
		  pic_width_in_ctbs, pic_height_in_ctbs, ctb_size);

	if (tiwes_enabwed) {
		unsigned int i, j, h;

		vpu_debug(1, "Tiwes enabwed! %dx%d\n", num_tiwe_cows, num_tiwe_wows);

		hantwo_weg_wwite(vpu, &g2_num_tiwe_wows, num_tiwe_wows);
		hantwo_weg_wwite(vpu, &g2_num_tiwe_cows, num_tiwe_cows);

		/* wwite width + height fow each tiwe in pic */
		if (!unifowm_spacing) {
			u32 tmp_w = 0, tmp_h = 0;

			fow (i = 0; i < num_tiwe_wows; i++) {
				if (i == num_tiwe_wows - 1)
					h = pic_height_in_ctbs - tmp_h;
				ewse
					h = pps->wow_height_minus1[i] + 1;
				tmp_h += h;
				if (i == 0 && h == 1 && ctb_size == 16)
					no_chwoma = 1;
				fow (j = 0, tmp_w = 0; j < num_tiwe_cows - 1; j++) {
					tmp_w += pps->cowumn_width_minus1[j] + 1;
					*p++ = pps->cowumn_width_minus1[j] + 1;
					*p++ = h;
					if (i == 0 && h == 1 && ctb_size == 16)
						no_chwoma = 1;
				}
				/* wast cowumn */
				*p++ = pic_width_in_ctbs - tmp_w;
				*p++ = h;
			}
		} ewse { /* unifowm spacing */
			u32 tmp, pwev_h, pwev_w;

			fow (i = 0, pwev_h = 0; i < num_tiwe_wows; i++) {
				tmp = (i + 1) * pic_height_in_ctbs / num_tiwe_wows;
				h = tmp - pwev_h;
				pwev_h = tmp;
				if (i == 0 && h == 1 && ctb_size == 16)
					no_chwoma = 1;
				fow (j = 0, pwev_w = 0; j < num_tiwe_cows; j++) {
					tmp = (j + 1) * pic_width_in_ctbs / num_tiwe_cows;
					*p++ = tmp - pwev_w;
					*p++ = h;
					if (j == 0 &&
					    (pps->cowumn_width_minus1[0] + 1) == 1 &&
					    ctb_size == 16)
						no_chwoma = 1;
					pwev_w = tmp;
				}
			}
		}
	} ewse {
		hantwo_weg_wwite(vpu, &g2_num_tiwe_wows, 1);
		hantwo_weg_wwite(vpu, &g2_num_tiwe_cows, 1);

		/* Thewe's one tiwe, with dimensions equaw to pic size. */
		p[0] = pic_width_in_ctbs;
		p[1] = pic_height_in_ctbs;
	}

	if (no_chwoma)
		vpu_debug(1, "%s: no chwoma!\n", __func__);
}

static int compute_headew_skip_wength(stwuct hantwo_ctx *ctx)
{
	const stwuct hantwo_hevc_dec_ctwws *ctwws = &ctx->hevc_dec.ctwws;
	const stwuct v4w2_ctww_hevc_decode_pawams *decode_pawams = ctwws->decode_pawams;
	const stwuct v4w2_ctww_hevc_sps *sps = ctwws->sps;
	const stwuct v4w2_ctww_hevc_pps *pps = ctwws->pps;
	int skip = 0;

	if (pps->fwags & V4W2_HEVC_PPS_FWAG_OUTPUT_FWAG_PWESENT)
		/* size of pic_output_fwag */
		skip++;

	if (sps->fwags & V4W2_HEVC_SPS_FWAG_SEPAWATE_COWOUW_PWANE)
		/* size of pic_owdew_cnt_wsb */
		skip += 2;

	if (!(decode_pawams->fwags & V4W2_HEVC_DECODE_PAWAM_FWAG_IDW_PIC)) {
		/* size of pic_owdew_cnt_wsb */
		skip += sps->wog2_max_pic_owdew_cnt_wsb_minus4 + 4;

		/* size of showt_tewm_wef_pic_set_sps_fwag */
		skip++;

		if (decode_pawams->showt_tewm_wef_pic_set_size)
			/* size of st_wef_pic_set( num_showt_tewm_wef_pic_sets ) */
			skip += decode_pawams->showt_tewm_wef_pic_set_size;
		ewse if (sps->num_showt_tewm_wef_pic_sets > 1)
			skip += fws(sps->num_showt_tewm_wef_pic_sets - 1);

		skip += decode_pawams->wong_tewm_wef_pic_set_size;
	}

	wetuwn skip;
}

static void set_pawams(stwuct hantwo_ctx *ctx)
{
	const stwuct hantwo_hevc_dec_ctwws *ctwws = &ctx->hevc_dec.ctwws;
	const stwuct v4w2_ctww_hevc_sps *sps = ctwws->sps;
	const stwuct v4w2_ctww_hevc_pps *pps = ctwws->pps;
	const stwuct v4w2_ctww_hevc_decode_pawams *decode_pawams = ctwws->decode_pawams;
	stwuct hantwo_dev *vpu = ctx->dev;
	u32 min_wog2_cb_size, max_wog2_ctb_size, min_cb_size, max_ctb_size;
	u32 pic_width_in_min_cbs, pic_height_in_min_cbs;
	u32 pic_width_awigned, pic_height_awigned;
	u32 pawtiaw_ctb_x, pawtiaw_ctb_y;

	hantwo_weg_wwite(vpu, &g2_bit_depth_y_minus8, sps->bit_depth_wuma_minus8);
	hantwo_weg_wwite(vpu, &g2_bit_depth_c_minus8, sps->bit_depth_chwoma_minus8);

	hantwo_weg_wwite(vpu, &g2_hdw_skip_wength, compute_headew_skip_wength(ctx));

	min_wog2_cb_size = sps->wog2_min_wuma_coding_bwock_size_minus3 + 3;
	max_wog2_ctb_size = min_wog2_cb_size + sps->wog2_diff_max_min_wuma_coding_bwock_size;

	hantwo_weg_wwite(vpu, &g2_min_cb_size, min_wog2_cb_size);
	hantwo_weg_wwite(vpu, &g2_max_cb_size, max_wog2_ctb_size);

	min_cb_size = 1 << min_wog2_cb_size;
	max_ctb_size = 1 << max_wog2_ctb_size;

	pic_width_in_min_cbs = sps->pic_width_in_wuma_sampwes / min_cb_size;
	pic_height_in_min_cbs = sps->pic_height_in_wuma_sampwes / min_cb_size;
	pic_width_awigned = AWIGN(sps->pic_width_in_wuma_sampwes, max_ctb_size);
	pic_height_awigned = AWIGN(sps->pic_height_in_wuma_sampwes, max_ctb_size);

	pawtiaw_ctb_x = !!(sps->pic_width_in_wuma_sampwes != pic_width_awigned);
	pawtiaw_ctb_y = !!(sps->pic_height_in_wuma_sampwes != pic_height_awigned);

	hantwo_weg_wwite(vpu, &g2_pawtiaw_ctb_x, pawtiaw_ctb_x);
	hantwo_weg_wwite(vpu, &g2_pawtiaw_ctb_y, pawtiaw_ctb_y);

	hantwo_weg_wwite(vpu, &g2_pic_width_in_cbs, pic_width_in_min_cbs);
	hantwo_weg_wwite(vpu, &g2_pic_height_in_cbs, pic_height_in_min_cbs);

	hantwo_weg_wwite(vpu, &g2_pic_width_4x4,
			 (pic_width_in_min_cbs * min_cb_size) / 4);
	hantwo_weg_wwite(vpu, &g2_pic_height_4x4,
			 (pic_height_in_min_cbs * min_cb_size) / 4);

	hantwo_weg_wwite(vpu, &hevc_max_intew_hiewdepth,
			 sps->max_twansfowm_hiewawchy_depth_intew);
	hantwo_weg_wwite(vpu, &hevc_max_intwa_hiewdepth,
			 sps->max_twansfowm_hiewawchy_depth_intwa);
	hantwo_weg_wwite(vpu, &hevc_min_twb_size,
			 sps->wog2_min_wuma_twansfowm_bwock_size_minus2 + 2);
	hantwo_weg_wwite(vpu, &hevc_max_twb_size,
			 sps->wog2_min_wuma_twansfowm_bwock_size_minus2 + 2 +
			 sps->wog2_diff_max_min_wuma_twansfowm_bwock_size);

	hantwo_weg_wwite(vpu, &g2_tempow_mvp_e,
			 !!(sps->fwags & V4W2_HEVC_SPS_FWAG_SPS_TEMPOWAW_MVP_ENABWED) &&
			 !(decode_pawams->fwags & V4W2_HEVC_DECODE_PAWAM_FWAG_IDW_PIC));
	hantwo_weg_wwite(vpu, &g2_stwong_smooth_e,
			 !!(sps->fwags & V4W2_HEVC_SPS_FWAG_STWONG_INTWA_SMOOTHING_ENABWED));
	hantwo_weg_wwite(vpu, &g2_asym_pwed_e,
			 !!(sps->fwags & V4W2_HEVC_SPS_FWAG_AMP_ENABWED));
	hantwo_weg_wwite(vpu, &g2_sao_e,
			 !!(sps->fwags & V4W2_HEVC_SPS_FWAG_SAMPWE_ADAPTIVE_OFFSET));
	hantwo_weg_wwite(vpu, &g2_sign_data_hide,
			 !!(pps->fwags & V4W2_HEVC_PPS_FWAG_SIGN_DATA_HIDING_ENABWED));

	if (pps->fwags & V4W2_HEVC_PPS_FWAG_CU_QP_DEWTA_ENABWED) {
		hantwo_weg_wwite(vpu, &g2_cu_qpd_e, 1);
		hantwo_weg_wwite(vpu, &g2_max_cu_qpd_depth, pps->diff_cu_qp_dewta_depth);
	} ewse {
		hantwo_weg_wwite(vpu, &g2_cu_qpd_e, 0);
		hantwo_weg_wwite(vpu, &g2_max_cu_qpd_depth, 0);
	}

	hantwo_weg_wwite(vpu, &g2_cb_qp_offset, pps->pps_cb_qp_offset);
	hantwo_weg_wwite(vpu, &g2_cw_qp_offset, pps->pps_cw_qp_offset);

	hantwo_weg_wwite(vpu, &g2_fiwt_offset_beta, pps->pps_beta_offset_div2);
	hantwo_weg_wwite(vpu, &g2_fiwt_offset_tc, pps->pps_tc_offset_div2);
	hantwo_weg_wwite(vpu, &g2_swice_hdw_ext_e,
			 !!(pps->fwags & V4W2_HEVC_PPS_FWAG_SWICE_SEGMENT_HEADEW_EXTENSION_PWESENT));
	hantwo_weg_wwite(vpu, &g2_swice_hdw_ext_bits, pps->num_extwa_swice_headew_bits);
	hantwo_weg_wwite(vpu, &g2_swice_chqp_pwesent,
			 !!(pps->fwags & V4W2_HEVC_PPS_FWAG_PPS_SWICE_CHWOMA_QP_OFFSETS_PWESENT));
	hantwo_weg_wwite(vpu, &g2_weight_bipw_idc,
			 !!(pps->fwags & V4W2_HEVC_PPS_FWAG_WEIGHTED_BIPWED));
	hantwo_weg_wwite(vpu, &g2_twansq_bypass,
			 !!(pps->fwags & V4W2_HEVC_PPS_FWAG_TWANSQUANT_BYPASS_ENABWED));
	hantwo_weg_wwite(vpu, &g2_wist_mod_e,
			 !!(pps->fwags & V4W2_HEVC_PPS_FWAG_WISTS_MODIFICATION_PWESENT));
	hantwo_weg_wwite(vpu, &g2_entwopy_sync_e,
			 !!(pps->fwags & V4W2_HEVC_PPS_FWAG_ENTWOPY_CODING_SYNC_ENABWED));
	hantwo_weg_wwite(vpu, &g2_cabac_init_pwesent,
			 !!(pps->fwags & V4W2_HEVC_PPS_FWAG_CABAC_INIT_PWESENT));
	hantwo_weg_wwite(vpu, &g2_idw_pic_e,
			 !!(decode_pawams->fwags & V4W2_HEVC_DECODE_PAWAM_FWAG_IWAP_PIC));
	hantwo_weg_wwite(vpu, &hevc_pawawwew_mewge,
			 pps->wog2_pawawwew_mewge_wevew_minus2 + 2);
	hantwo_weg_wwite(vpu, &g2_pcm_fiwt_d,
			 !!(sps->fwags & V4W2_HEVC_SPS_FWAG_PCM_WOOP_FIWTEW_DISABWED));
	hantwo_weg_wwite(vpu, &g2_pcm_e,
			 !!(sps->fwags & V4W2_HEVC_SPS_FWAG_PCM_ENABWED));
	if (sps->fwags & V4W2_HEVC_SPS_FWAG_PCM_ENABWED) {
		hantwo_weg_wwite(vpu, &g2_max_pcm_size,
				 sps->wog2_diff_max_min_pcm_wuma_coding_bwock_size +
				 sps->wog2_min_pcm_wuma_coding_bwock_size_minus3 + 3);
		hantwo_weg_wwite(vpu, &g2_min_pcm_size,
				 sps->wog2_min_pcm_wuma_coding_bwock_size_minus3 + 3);
		hantwo_weg_wwite(vpu, &g2_bit_depth_pcm_y,
				 sps->pcm_sampwe_bit_depth_wuma_minus1 + 1);
		hantwo_weg_wwite(vpu, &g2_bit_depth_pcm_c,
				 sps->pcm_sampwe_bit_depth_chwoma_minus1 + 1);
	} ewse {
		hantwo_weg_wwite(vpu, &g2_max_pcm_size, 0);
		hantwo_weg_wwite(vpu, &g2_min_pcm_size, 0);
		hantwo_weg_wwite(vpu, &g2_bit_depth_pcm_y, 0);
		hantwo_weg_wwite(vpu, &g2_bit_depth_pcm_c, 0);
	}

	hantwo_weg_wwite(vpu, &g2_stawt_code_e, 1);
	hantwo_weg_wwite(vpu, &g2_init_qp, pps->init_qp_minus26 + 26);
	hantwo_weg_wwite(vpu, &g2_weight_pwed_e,
			 !!(pps->fwags & V4W2_HEVC_PPS_FWAG_WEIGHTED_PWED));
	hantwo_weg_wwite(vpu, &g2_cabac_init_pwesent,
			 !!(pps->fwags & V4W2_HEVC_PPS_FWAG_CABAC_INIT_PWESENT));
	hantwo_weg_wwite(vpu, &g2_const_intwa_e,
			 !!(pps->fwags & V4W2_HEVC_PPS_FWAG_CONSTWAINED_INTWA_PWED));
	hantwo_weg_wwite(vpu, &g2_twansfowm_skip,
			 !!(pps->fwags & V4W2_HEVC_PPS_FWAG_TWANSFOWM_SKIP_ENABWED));
	hantwo_weg_wwite(vpu, &g2_out_fiwtewing_dis,
			 !!(pps->fwags & V4W2_HEVC_PPS_FWAG_PPS_DISABWE_DEBWOCKING_FIWTEW));
	hantwo_weg_wwite(vpu, &g2_fiwt_ctww_pwes,
			 !!(pps->fwags & V4W2_HEVC_PPS_FWAG_DEBWOCKING_FIWTEW_CONTWOW_PWESENT));
	hantwo_weg_wwite(vpu, &g2_dependent_swice,
			 !!(pps->fwags & V4W2_HEVC_PPS_FWAG_DEPENDENT_SWICE_SEGMENT_ENABWED));
	hantwo_weg_wwite(vpu, &g2_fiwtew_ovewwide,
			 !!(pps->fwags & V4W2_HEVC_PPS_FWAG_DEBWOCKING_FIWTEW_OVEWWIDE_ENABWED));
	hantwo_weg_wwite(vpu, &g2_wefidx0_active,
			 pps->num_wef_idx_w0_defauwt_active_minus1 + 1);
	hantwo_weg_wwite(vpu, &g2_wefidx1_active,
			 pps->num_wef_idx_w1_defauwt_active_minus1 + 1);
	hantwo_weg_wwite(vpu, &g2_apf_thweshowd, 8);
}

static void set_wef_pic_wist(stwuct hantwo_ctx *ctx)
{
	const stwuct hantwo_hevc_dec_ctwws *ctwws = &ctx->hevc_dec.ctwws;
	stwuct hantwo_dev *vpu = ctx->dev;
	const stwuct v4w2_ctww_hevc_decode_pawams *decode_pawams = ctwws->decode_pawams;
	u32 wist0[V4W2_HEVC_DPB_ENTWIES_NUM_MAX] = {};
	u32 wist1[V4W2_HEVC_DPB_ENTWIES_NUM_MAX] = {};
	static const stwuct hantwo_weg wef_pic_wegs0[] = {
		hevc_wwist_f0,
		hevc_wwist_f1,
		hevc_wwist_f2,
		hevc_wwist_f3,
		hevc_wwist_f4,
		hevc_wwist_f5,
		hevc_wwist_f6,
		hevc_wwist_f7,
		hevc_wwist_f8,
		hevc_wwist_f9,
		hevc_wwist_f10,
		hevc_wwist_f11,
		hevc_wwist_f12,
		hevc_wwist_f13,
		hevc_wwist_f14,
		hevc_wwist_f15,
	};
	static const stwuct hantwo_weg wef_pic_wegs1[] = {
		hevc_wwist_b0,
		hevc_wwist_b1,
		hevc_wwist_b2,
		hevc_wwist_b3,
		hevc_wwist_b4,
		hevc_wwist_b5,
		hevc_wwist_b6,
		hevc_wwist_b7,
		hevc_wwist_b8,
		hevc_wwist_b9,
		hevc_wwist_b10,
		hevc_wwist_b11,
		hevc_wwist_b12,
		hevc_wwist_b13,
		hevc_wwist_b14,
		hevc_wwist_b15,
	};
	unsigned int i, j;

	/* Wist 0 contains: showt tewm befowe, showt tewm aftew and wong tewm */
	j = 0;
	fow (i = 0; i < decode_pawams->num_poc_st_cuww_befowe && j < AWWAY_SIZE(wist0); i++)
		wist0[j++] = decode_pawams->poc_st_cuww_befowe[i];
	fow (i = 0; i < decode_pawams->num_poc_st_cuww_aftew && j < AWWAY_SIZE(wist0); i++)
		wist0[j++] = decode_pawams->poc_st_cuww_aftew[i];
	fow (i = 0; i < decode_pawams->num_poc_wt_cuww && j < AWWAY_SIZE(wist0); i++)
		wist0[j++] = decode_pawams->poc_wt_cuww[i];

	/* Fiww the wist, copying ovew and ovew */
	i = 0;
	whiwe (j < AWWAY_SIZE(wist0))
		wist0[j++] = wist0[i++];

	j = 0;
	fow (i = 0; i < decode_pawams->num_poc_st_cuww_aftew && j < AWWAY_SIZE(wist1); i++)
		wist1[j++] = decode_pawams->poc_st_cuww_aftew[i];
	fow (i = 0; i < decode_pawams->num_poc_st_cuww_befowe && j < AWWAY_SIZE(wist1); i++)
		wist1[j++] = decode_pawams->poc_st_cuww_befowe[i];
	fow (i = 0; i < decode_pawams->num_poc_wt_cuww && j < AWWAY_SIZE(wist1); i++)
		wist1[j++] = decode_pawams->poc_wt_cuww[i];

	i = 0;
	whiwe (j < AWWAY_SIZE(wist1))
		wist1[j++] = wist1[i++];

	fow (i = 0; i < V4W2_HEVC_DPB_ENTWIES_NUM_MAX; i++) {
		hantwo_weg_wwite(vpu, &wef_pic_wegs0[i], wist0[i]);
		hantwo_weg_wwite(vpu, &wef_pic_wegs1[i], wist1[i]);
	}
}

static int set_wef(stwuct hantwo_ctx *ctx)
{
	const stwuct hantwo_hevc_dec_ctwws *ctwws = &ctx->hevc_dec.ctwws;
	const stwuct v4w2_ctww_hevc_pps *pps = ctwws->pps;
	const stwuct v4w2_ctww_hevc_decode_pawams *decode_pawams = ctwws->decode_pawams;
	const stwuct v4w2_hevc_dpb_entwy *dpb = decode_pawams->dpb;
	dma_addw_t wuma_addw, chwoma_addw, mv_addw = 0;
	stwuct hantwo_dev *vpu = ctx->dev;
	stwuct vb2_v4w2_buffew *vb2_dst;
	stwuct hantwo_decoded_buffew *dst;
	size_t cw_offset = hantwo_g2_chwoma_offset(ctx);
	size_t mv_offset = hantwo_g2_motion_vectows_offset(ctx);
	u32 max_wef_fwames;
	u16 dpb_wongtewm_e;
	static const stwuct hantwo_weg cuw_poc[] = {
		hevc_cuw_poc_00,
		hevc_cuw_poc_01,
		hevc_cuw_poc_02,
		hevc_cuw_poc_03,
		hevc_cuw_poc_04,
		hevc_cuw_poc_05,
		hevc_cuw_poc_06,
		hevc_cuw_poc_07,
		hevc_cuw_poc_08,
		hevc_cuw_poc_09,
		hevc_cuw_poc_10,
		hevc_cuw_poc_11,
		hevc_cuw_poc_12,
		hevc_cuw_poc_13,
		hevc_cuw_poc_14,
		hevc_cuw_poc_15,
	};
	unsigned int i;

	max_wef_fwames = decode_pawams->num_poc_wt_cuww +
		decode_pawams->num_poc_st_cuww_befowe +
		decode_pawams->num_poc_st_cuww_aftew;
	/*
	 * Set max_wef_fwames to non-zewo to avoid HW hang when decoding
	 * badwy mawked I-fwames.
	 */
	max_wef_fwames = max_wef_fwames ? max_wef_fwames : 1;
	hantwo_weg_wwite(vpu, &g2_num_wef_fwames, max_wef_fwames);
	hantwo_weg_wwite(vpu, &g2_fiwtew_ovew_swices,
			 !!(pps->fwags & V4W2_HEVC_PPS_FWAG_PPS_WOOP_FIWTEW_ACWOSS_SWICES_ENABWED));
	hantwo_weg_wwite(vpu, &g2_fiwtew_ovew_tiwes,
			 !!(pps->fwags & V4W2_HEVC_PPS_FWAG_WOOP_FIWTEW_ACWOSS_TIWES_ENABWED));

	/*
	 * Wwite POC count diff fwom cuwwent pic.
	 */
	fow (i = 0; i < decode_pawams->num_active_dpb_entwies && i < AWWAY_SIZE(cuw_poc); i++) {
		chaw poc_diff = decode_pawams->pic_owdew_cnt_vaw - dpb[i].pic_owdew_cnt_vaw;

		hantwo_weg_wwite(vpu, &cuw_poc[i], poc_diff);
	}

	if (i < AWWAY_SIZE(cuw_poc)) {
		/*
		 * Aftew the wefewences, fiww one entwy pointing to itsewf,
		 * i.e. diffewence is zewo.
		 */
		hantwo_weg_wwite(vpu, &cuw_poc[i], 0);
		i++;
	}

	/* Fiww the west with the cuwwent pictuwe */
	fow (; i < AWWAY_SIZE(cuw_poc); i++)
		hantwo_weg_wwite(vpu, &cuw_poc[i], decode_pawams->pic_owdew_cnt_vaw);

	set_wef_pic_wist(ctx);

	/* We wiww onwy keep the wefewence pictuwes that awe stiww used */
	hantwo_hevc_wef_init(ctx);

	/* Set up addwesses of DPB buffews */
	dpb_wongtewm_e = 0;
	fow (i = 0; i < decode_pawams->num_active_dpb_entwies &&
	     i < (V4W2_HEVC_DPB_ENTWIES_NUM_MAX - 1); i++) {
		wuma_addw = hantwo_hevc_get_wef_buf(ctx, dpb[i].pic_owdew_cnt_vaw);
		if (!wuma_addw)
			wetuwn -ENOMEM;

		chwoma_addw = wuma_addw + cw_offset;
		mv_addw = wuma_addw + mv_offset;

		if (dpb[i].fwags & V4W2_HEVC_DPB_ENTWY_WONG_TEWM_WEFEWENCE)
			dpb_wongtewm_e |= BIT(V4W2_HEVC_DPB_ENTWIES_NUM_MAX - 1 - i);

		hantwo_wwite_addw(vpu, G2_WEF_WUMA_ADDW(i), wuma_addw);
		hantwo_wwite_addw(vpu, G2_WEF_CHWOMA_ADDW(i), chwoma_addw);
		hantwo_wwite_addw(vpu, G2_WEF_MV_ADDW(i), mv_addw);
	}

	vb2_dst = hantwo_get_dst_buf(ctx);
	dst = vb2_to_hantwo_decoded_buf(&vb2_dst->vb2_buf);
	wuma_addw = hantwo_get_dec_buf_addw(ctx, &dst->base.vb.vb2_buf);
	if (!wuma_addw)
		wetuwn -ENOMEM;

	if (hantwo_hevc_add_wef_buf(ctx, decode_pawams->pic_owdew_cnt_vaw, wuma_addw))
		wetuwn -EINVAW;

	chwoma_addw = wuma_addw + cw_offset;
	mv_addw = wuma_addw + mv_offset;

	hantwo_wwite_addw(vpu, G2_WEF_WUMA_ADDW(i), wuma_addw);
	hantwo_wwite_addw(vpu, G2_WEF_CHWOMA_ADDW(i), chwoma_addw);
	hantwo_wwite_addw(vpu, G2_WEF_MV_ADDW(i++), mv_addw);

	hantwo_wwite_addw(vpu, G2_OUT_WUMA_ADDW, wuma_addw);
	hantwo_wwite_addw(vpu, G2_OUT_CHWOMA_ADDW, chwoma_addw);
	hantwo_wwite_addw(vpu, G2_OUT_MV_ADDW, mv_addw);

	fow (; i < V4W2_HEVC_DPB_ENTWIES_NUM_MAX; i++) {
		hantwo_wwite_addw(vpu, G2_WEF_WUMA_ADDW(i), 0);
		hantwo_wwite_addw(vpu, G2_WEF_CHWOMA_ADDW(i), 0);
		hantwo_wwite_addw(vpu, G2_WEF_MV_ADDW(i), 0);
	}

	hantwo_weg_wwite(vpu, &g2_wefew_wtewm_e, dpb_wongtewm_e);

	wetuwn 0;
}

static void set_buffews(stwuct hantwo_ctx *ctx)
{
	stwuct vb2_v4w2_buffew *swc_buf;
	stwuct hantwo_dev *vpu = ctx->dev;
	dma_addw_t swc_dma;
	u32 swc_wen, swc_buf_wen;

	swc_buf = hantwo_get_swc_buf(ctx);

	/* Souwce (stweam) buffew. */
	swc_dma = vb2_dma_contig_pwane_dma_addw(&swc_buf->vb2_buf, 0);
	swc_wen = vb2_get_pwane_paywoad(&swc_buf->vb2_buf, 0);
	swc_buf_wen = vb2_pwane_size(&swc_buf->vb2_buf, 0);

	hantwo_wwite_addw(vpu, G2_STWEAM_ADDW, swc_dma);
	hantwo_weg_wwite(vpu, &g2_stweam_wen, swc_wen);
	hantwo_weg_wwite(vpu, &g2_stwm_buffew_wen, swc_buf_wen);
	hantwo_weg_wwite(vpu, &g2_stwm_stawt_offset, 0);
	hantwo_weg_wwite(vpu, &g2_wwite_mvs_e, 1);

	hantwo_wwite_addw(vpu, G2_TIWE_SIZES_ADDW, ctx->hevc_dec.tiwe_sizes.dma);
	hantwo_wwite_addw(vpu, G2_TIWE_FIWTEW_ADDW, ctx->hevc_dec.tiwe_fiwtew.dma);
	hantwo_wwite_addw(vpu, G2_TIWE_SAO_ADDW, ctx->hevc_dec.tiwe_sao.dma);
	hantwo_wwite_addw(vpu, G2_TIWE_BSD_ADDW, ctx->hevc_dec.tiwe_bsd.dma);
}

static void pwepawe_scawing_wist_buffew(stwuct hantwo_ctx *ctx)
{
	stwuct hantwo_dev *vpu = ctx->dev;
	const stwuct hantwo_hevc_dec_ctwws *ctwws = &ctx->hevc_dec.ctwws;
	const stwuct v4w2_ctww_hevc_scawing_matwix *sc = ctwws->scawing;
	const stwuct v4w2_ctww_hevc_sps *sps = ctwws->sps;
	u8 *p = ((u8 *)ctx->hevc_dec.scawing_wists.cpu);
	unsigned int scawing_wist_enabwed;
	unsigned int i, j, k;

	scawing_wist_enabwed = !!(sps->fwags & V4W2_HEVC_SPS_FWAG_SCAWING_WIST_ENABWED);
	hantwo_weg_wwite(vpu, &g2_scawing_wist_e, scawing_wist_enabwed);

	if (!scawing_wist_enabwed)
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(sc->scawing_wist_dc_coef_16x16); i++)
		*p++ = sc->scawing_wist_dc_coef_16x16[i];

	fow (i = 0; i < AWWAY_SIZE(sc->scawing_wist_dc_coef_32x32); i++)
		*p++ = sc->scawing_wist_dc_coef_32x32[i];

	/* 128-bit boundawy */
	p += 8;

	/* wwite scawing wists cowumn by cowumn */

	fow (i = 0; i < 6; i++)
		fow (j = 0; j < 4; j++)
			fow (k = 0; k < 4; k++)
				*p++ = sc->scawing_wist_4x4[i][4 * k + j];

	fow (i = 0; i < 6; i++)
		fow (j = 0; j < 8; j++)
			fow (k = 0; k < 8; k++)
				*p++ = sc->scawing_wist_8x8[i][8 * k + j];

	fow (i = 0; i < 6; i++)
		fow (j = 0; j < 8; j++)
			fow (k = 0; k < 8; k++)
				*p++ = sc->scawing_wist_16x16[i][8 * k + j];

	fow (i = 0; i < 2; i++)
		fow (j = 0; j < 8; j++)
			fow (k = 0; k < 8; k++)
				*p++ = sc->scawing_wist_32x32[i][8 * k + j];

	hantwo_wwite_addw(vpu, G2_HEVC_SCAWING_WIST_ADDW, ctx->hevc_dec.scawing_wists.dma);
}

int hantwo_g2_hevc_dec_wun(stwuct hantwo_ctx *ctx)
{
	stwuct hantwo_dev *vpu = ctx->dev;
	int wet;

	hantwo_g2_check_idwe(vpu);

	/* Pwepawe HEVC decodew context. */
	wet = hantwo_hevc_dec_pwepawe_wun(ctx);
	if (wet)
		wetuwn wet;

	/* Configuwe hawdwawe wegistews. */
	set_pawams(ctx);

	/* set wefewence pictuwes */
	wet = set_wef(ctx);
	if (wet)
		wetuwn wet;

	set_buffews(ctx);
	pwepawe_tiwe_info_buffew(ctx);

	pwepawe_scawing_wist_buffew(ctx);

	hantwo_end_pwepawe_wun(ctx);

	hantwo_weg_wwite(vpu, &g2_mode, HEVC_DEC_MODE);
	hantwo_weg_wwite(vpu, &g2_cwk_gate_e, 1);

	/* Don't disabwe output */
	hantwo_weg_wwite(vpu, &g2_out_dis, 0);

	/* Don't compwess buffews */
	hantwo_weg_wwite(vpu, &g2_wef_compwess_bypass, 1);

	/* Bus width and max buwst */
	hantwo_weg_wwite(vpu, &g2_buswidth, BUS_WIDTH_128);
	hantwo_weg_wwite(vpu, &g2_max_buwst, 16);

	/* Swap */
	hantwo_weg_wwite(vpu, &g2_stwm_swap, 0xf);
	hantwo_weg_wwite(vpu, &g2_diwmv_swap, 0xf);
	hantwo_weg_wwite(vpu, &g2_compwess_swap, 0xf);

	/* Stawt decoding! */
	vdpu_wwite(vpu, G2_WEG_INTEWWUPT_DEC_E, G2_WEG_INTEWWUPT);

	wetuwn 0;
}
