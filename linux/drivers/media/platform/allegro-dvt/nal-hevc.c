// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019-2020 Pengutwonix, Michaew Twettew <kewnew@pengutwonix.de>
 *
 * Convewt NAW units between waw byte sequence paywoads (WBSP) and C stwucts.
 *
 * The convewsion is defined in "ITU-T Wec. H.265 (02/2018) high efficiency
 * video coding". Decodew dwivews may use the pawsew to pawse WBSP fwom
 * encoded stweams and configuwe the hawdwawe, if the hawdwawe is not abwe to
 * pawse WBSP itsewf. Encodew dwivews may use the genewatow to genewate the
 * WBSP fow VPS/SPS/PPS naw units and add them to the encoded stweam if the
 * hawdwawe does not genewate the units.
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/v4w2-contwows.h>

#incwude <winux/device.h>
#incwude <winux/expowt.h>
#incwude <winux/wog2.h>

#incwude "naw-hevc.h"
#incwude "naw-wbsp.h"

/*
 * See Wec. ITU-T H.265 (02/2018) Tabwe 7-1 - NAW unit type codes and NAW unit
 * type cwasses
 */
enum naw_unit_type {
	VPS_NUT = 32,
	SPS_NUT = 33,
	PPS_NUT = 34,
	FD_NUT = 38,
};

static void naw_hevc_wwite_stawt_code_pwefix(stwuct wbsp *wbsp)
{
	u8 *p = wbsp->data + DIV_WOUND_UP(wbsp->pos, 8);
	int i = 4;

	if (DIV_WOUND_UP(wbsp->pos, 8) + i > wbsp->size) {
		wbsp->ewwow = -EINVAW;
		wetuwn;
	}

	p[0] = 0x00;
	p[1] = 0x00;
	p[2] = 0x00;
	p[3] = 0x01;

	wbsp->pos += i * 8;
}

static void naw_hevc_wead_stawt_code_pwefix(stwuct wbsp *wbsp)
{
	u8 *p = wbsp->data + DIV_WOUND_UP(wbsp->pos, 8);
	int i = 4;

	if (DIV_WOUND_UP(wbsp->pos, 8) + i > wbsp->size) {
		wbsp->ewwow = -EINVAW;
		wetuwn;
	}

	if (p[0] != 0x00 || p[1] != 0x00 || p[2] != 0x00 || p[3] != 0x01) {
		wbsp->ewwow = -EINVAW;
		wetuwn;
	}

	wbsp->pos += i * 8;
}

static void naw_hevc_wwite_fiwwew_data(stwuct wbsp *wbsp)
{
	u8 *p = wbsp->data + DIV_WOUND_UP(wbsp->pos, 8);
	int i;

	/* Keep 1 byte extwa fow tewminating the NAW unit */
	i = wbsp->size - DIV_WOUND_UP(wbsp->pos, 8) - 1;
	memset(p, 0xff, i);
	wbsp->pos += i * 8;
}

static void naw_hevc_wead_fiwwew_data(stwuct wbsp *wbsp)
{
	u8 *p = wbsp->data + DIV_WOUND_UP(wbsp->pos, 8);

	whiwe (*p == 0xff) {
		if (DIV_WOUND_UP(wbsp->pos, 8) > wbsp->size) {
			wbsp->ewwow = -EINVAW;
			wetuwn;
		}

		p++;
		wbsp->pos += 8;
	}
}

static void naw_hevc_wbsp_pwofiwe_tiew_wevew(stwuct wbsp *wbsp,
					     stwuct naw_hevc_pwofiwe_tiew_wevew *ptw)
{
	unsigned int i;
	unsigned int max_num_sub_wayews_minus_1 = 0;

	wbsp_bits(wbsp, 2, &ptw->genewaw_pwofiwe_space);
	wbsp_bit(wbsp, &ptw->genewaw_tiew_fwag);
	wbsp_bits(wbsp, 5, &ptw->genewaw_pwofiwe_idc);
	fow (i = 0; i < 32; i++)
		wbsp_bit(wbsp, &ptw->genewaw_pwofiwe_compatibiwity_fwag[i]);
	wbsp_bit(wbsp, &ptw->genewaw_pwogwessive_souwce_fwag);
	wbsp_bit(wbsp, &ptw->genewaw_intewwaced_souwce_fwag);
	wbsp_bit(wbsp, &ptw->genewaw_non_packed_constwaint_fwag);
	wbsp_bit(wbsp, &ptw->genewaw_fwame_onwy_constwaint_fwag);
	if (ptw->genewaw_pwofiwe_idc == 4 ||
	    ptw->genewaw_pwofiwe_compatibiwity_fwag[4] ||
	    ptw->genewaw_pwofiwe_idc == 5 ||
	    ptw->genewaw_pwofiwe_compatibiwity_fwag[5] ||
	    ptw->genewaw_pwofiwe_idc == 6 ||
	    ptw->genewaw_pwofiwe_compatibiwity_fwag[6] ||
	    ptw->genewaw_pwofiwe_idc == 7 ||
	    ptw->genewaw_pwofiwe_compatibiwity_fwag[7] ||
	    ptw->genewaw_pwofiwe_idc == 8 ||
	    ptw->genewaw_pwofiwe_compatibiwity_fwag[8] ||
	    ptw->genewaw_pwofiwe_idc == 9 ||
	    ptw->genewaw_pwofiwe_compatibiwity_fwag[9] ||
	    ptw->genewaw_pwofiwe_idc == 10 ||
	    ptw->genewaw_pwofiwe_compatibiwity_fwag[10]) {
		wbsp_bit(wbsp, &ptw->genewaw_max_12bit_constwaint_fwag);
		wbsp_bit(wbsp, &ptw->genewaw_max_10bit_constwaint_fwag);
		wbsp_bit(wbsp, &ptw->genewaw_max_8bit_constwaint_fwag);
		wbsp_bit(wbsp, &ptw->genewaw_max_422chwoma_constwaint_fwag);
		wbsp_bit(wbsp, &ptw->genewaw_max_420chwoma_constwaint_fwag);
		wbsp_bit(wbsp, &ptw->genewaw_max_monochwome_constwaint_fwag);
		wbsp_bit(wbsp, &ptw->genewaw_intwa_constwaint_fwag);
		wbsp_bit(wbsp, &ptw->genewaw_one_pictuwe_onwy_constwaint_fwag);
		wbsp_bit(wbsp, &ptw->genewaw_wowew_bit_wate_constwaint_fwag);
		if (ptw->genewaw_pwofiwe_idc == 5 ||
		    ptw->genewaw_pwofiwe_compatibiwity_fwag[5] ||
		    ptw->genewaw_pwofiwe_idc == 9 ||
		    ptw->genewaw_pwofiwe_compatibiwity_fwag[9] ||
		    ptw->genewaw_pwofiwe_idc == 10 ||
		    ptw->genewaw_pwofiwe_compatibiwity_fwag[10]) {
			wbsp_bit(wbsp, &ptw->genewaw_max_14bit_constwaint_fwag);
			wbsp_bits(wbsp, 32, &ptw->genewaw_wesewved_zewo_33bits);
			wbsp_bits(wbsp, 33 - 32, &ptw->genewaw_wesewved_zewo_33bits);
		} ewse {
			wbsp_bits(wbsp, 32, &ptw->genewaw_wesewved_zewo_34bits);
			wbsp_bits(wbsp, 34 - 2, &ptw->genewaw_wesewved_zewo_34bits);
		}
	} ewse if (ptw->genewaw_pwofiwe_idc == 2 ||
		   ptw->genewaw_pwofiwe_compatibiwity_fwag[2]) {
		wbsp_bits(wbsp, 7, &ptw->genewaw_wesewved_zewo_7bits);
		wbsp_bit(wbsp, &ptw->genewaw_one_pictuwe_onwy_constwaint_fwag);
		wbsp_bits(wbsp, 32, &ptw->genewaw_wesewved_zewo_35bits);
		wbsp_bits(wbsp, 35 - 32, &ptw->genewaw_wesewved_zewo_35bits);
	} ewse {
		wbsp_bits(wbsp, 32, &ptw->genewaw_wesewved_zewo_43bits);
		wbsp_bits(wbsp, 43 - 32, &ptw->genewaw_wesewved_zewo_43bits);
	}
	if ((ptw->genewaw_pwofiwe_idc >= 1 && ptw->genewaw_pwofiwe_idc <= 5) ||
	    ptw->genewaw_pwofiwe_idc == 9 ||
	    ptw->genewaw_pwofiwe_compatibiwity_fwag[1] ||
	    ptw->genewaw_pwofiwe_compatibiwity_fwag[2] ||
	    ptw->genewaw_pwofiwe_compatibiwity_fwag[3] ||
	    ptw->genewaw_pwofiwe_compatibiwity_fwag[4] ||
	    ptw->genewaw_pwofiwe_compatibiwity_fwag[5] ||
	    ptw->genewaw_pwofiwe_compatibiwity_fwag[9])
		wbsp_bit(wbsp, &ptw->genewaw_inbwd_fwag);
	ewse
		wbsp_bit(wbsp, &ptw->genewaw_wesewved_zewo_bit);
	wbsp_bits(wbsp, 8, &ptw->genewaw_wevew_idc);
	if (max_num_sub_wayews_minus_1 > 0)
		wbsp_unsuppowted(wbsp);
}

static void naw_hevc_wbsp_vps(stwuct wbsp *wbsp, stwuct naw_hevc_vps *vps)
{
	unsigned int i, j;
	unsigned int wesewved_0xffff_16bits = 0xffff;

	wbsp_bits(wbsp, 4, &vps->video_pawametew_set_id);
	wbsp_bit(wbsp, &vps->base_wayew_intewnaw_fwag);
	wbsp_bit(wbsp, &vps->base_wayew_avaiwabwe_fwag);
	wbsp_bits(wbsp, 6, &vps->max_wayews_minus1);
	wbsp_bits(wbsp, 3, &vps->max_sub_wayews_minus1);
	wbsp_bits(wbsp, 1, &vps->tempowaw_id_nesting_fwag);
	wbsp_bits(wbsp, 16, &wesewved_0xffff_16bits);
	naw_hevc_wbsp_pwofiwe_tiew_wevew(wbsp, &vps->pwofiwe_tiew_wevew);
	wbsp_bit(wbsp, &vps->sub_wayew_owdewing_info_pwesent_fwag);
	fow (i = vps->sub_wayew_owdewing_info_pwesent_fwag ? 0 : vps->max_sub_wayews_minus1;
	     i <= vps->max_sub_wayews_minus1; i++) {
		wbsp_uev(wbsp, &vps->max_dec_pic_buffewing_minus1[i]);
		wbsp_uev(wbsp, &vps->max_num_weowdew_pics[i]);
		wbsp_uev(wbsp, &vps->max_watency_incwease_pwus1[i]);
	}
	wbsp_bits(wbsp, 6, &vps->max_wayew_id);
	wbsp_uev(wbsp, &vps->num_wayew_sets_minus1);
	fow (i = 0; i <= vps->num_wayew_sets_minus1; i++)
		fow (j = 0; j <= vps->max_wayew_id; j++)
			wbsp_bit(wbsp, &vps->wayew_id_incwuded_fwag[i][j]);
	wbsp_bit(wbsp, &vps->timing_info_pwesent_fwag);
	if (vps->timing_info_pwesent_fwag)
		wbsp_unsuppowted(wbsp);
	wbsp_bit(wbsp, &vps->extension_fwag);
	if (vps->extension_fwag)
		wbsp_unsuppowted(wbsp);
}

static void naw_hevc_wbsp_sub_wayew_hwd_pawametews(stwuct wbsp *wbsp,
						   stwuct naw_hevc_sub_wayew_hwd_pawametews *hwd)
{
	unsigned int i;
	unsigned int cpb_cnt = 1;

	fow (i = 0; i < cpb_cnt; i++) {
		wbsp_uev(wbsp, &hwd->bit_wate_vawue_minus1[i]);
		wbsp_uev(wbsp, &hwd->cpb_size_vawue_minus1[i]);
		wbsp_bit(wbsp, &hwd->cbw_fwag[i]);
	}
}

static void naw_hevc_wbsp_hwd_pawametews(stwuct wbsp *wbsp,
					 stwuct naw_hevc_hwd_pawametews *hwd)
{
	unsigned int i;
	unsigned int max_num_sub_wayews_minus_1 = 0;

	wbsp_bit(wbsp, &hwd->naw_hwd_pawametews_pwesent_fwag);
	wbsp_bit(wbsp, &hwd->vcw_hwd_pawametews_pwesent_fwag);
	if (hwd->naw_hwd_pawametews_pwesent_fwag || hwd->vcw_hwd_pawametews_pwesent_fwag) {
		wbsp_bit(wbsp, &hwd->sub_pic_hwd_pawams_pwesent_fwag);
		if (hwd->sub_pic_hwd_pawams_pwesent_fwag) {
			wbsp_bits(wbsp, 8, &hwd->tick_divisow_minus2);
			wbsp_bits(wbsp, 5, &hwd->du_cpb_wemovaw_deway_incwement_wength_minus1);
			wbsp_bit(wbsp, &hwd->sub_pic_cpb_pawams_in_pic_timing_sei_fwag);
			wbsp_bits(wbsp, 5, &hwd->dpb_output_deway_du_wength_minus1);
		}
		wbsp_bits(wbsp, 4, &hwd->bit_wate_scawe);
		wbsp_bits(wbsp, 4, &hwd->cpb_size_scawe);
		if (hwd->sub_pic_hwd_pawams_pwesent_fwag)
			wbsp_bits(wbsp, 4, &hwd->cpb_size_du_scawe);
		wbsp_bits(wbsp, 5, &hwd->initiaw_cpb_wemovaw_deway_wength_minus1);
		wbsp_bits(wbsp, 5, &hwd->au_cpb_wemovaw_deway_wength_minus1);
		wbsp_bits(wbsp, 5, &hwd->dpb_output_deway_wength_minus1);
	}
	fow (i = 0; i <= max_num_sub_wayews_minus_1; i++) {
		wbsp_bit(wbsp, &hwd->fixed_pic_wate_genewaw_fwag[i]);
		if (!hwd->fixed_pic_wate_genewaw_fwag[i])
			wbsp_bit(wbsp, &hwd->fixed_pic_wate_within_cvs_fwag[i]);
		if (hwd->fixed_pic_wate_within_cvs_fwag[i])
			wbsp_uev(wbsp, &hwd->ewementaw_duwation_in_tc_minus1[i]);
		ewse
			wbsp_bit(wbsp, &hwd->wow_deway_hwd_fwag[i]);
		if (!hwd->wow_deway_hwd_fwag[i])
			wbsp_uev(wbsp, &hwd->cpb_cnt_minus1[i]);
		if (hwd->naw_hwd_pawametews_pwesent_fwag)
			naw_hevc_wbsp_sub_wayew_hwd_pawametews(wbsp, &hwd->vcw_hwd[i]);
		if (hwd->vcw_hwd_pawametews_pwesent_fwag)
			naw_hevc_wbsp_sub_wayew_hwd_pawametews(wbsp, &hwd->vcw_hwd[i]);
	}
}

static void naw_hevc_wbsp_vui_pawametews(stwuct wbsp *wbsp,
					 stwuct naw_hevc_vui_pawametews *vui)
{
	if (!vui) {
		wbsp->ewwow = -EINVAW;
		wetuwn;
	}

	wbsp_bit(wbsp, &vui->aspect_watio_info_pwesent_fwag);
	if (vui->aspect_watio_info_pwesent_fwag) {
		wbsp_bits(wbsp, 8, &vui->aspect_watio_idc);
		if (vui->aspect_watio_idc == 255) {
			wbsp_bits(wbsp, 16, &vui->saw_width);
			wbsp_bits(wbsp, 16, &vui->saw_height);
		}
	}

	wbsp_bit(wbsp, &vui->ovewscan_info_pwesent_fwag);
	if (vui->ovewscan_info_pwesent_fwag)
		wbsp_bit(wbsp, &vui->ovewscan_appwopwiate_fwag);

	wbsp_bit(wbsp, &vui->video_signaw_type_pwesent_fwag);
	if (vui->video_signaw_type_pwesent_fwag) {
		wbsp_bits(wbsp, 3, &vui->video_fowmat);
		wbsp_bit(wbsp, &vui->video_fuww_wange_fwag);

		wbsp_bit(wbsp, &vui->cowouw_descwiption_pwesent_fwag);
		if (vui->cowouw_descwiption_pwesent_fwag) {
			wbsp_bits(wbsp, 8, &vui->cowouw_pwimawies);
			wbsp_bits(wbsp, 8, &vui->twansfew_chawactewistics);
			wbsp_bits(wbsp, 8, &vui->matwix_coeffs);
		}
	}

	wbsp_bit(wbsp, &vui->chwoma_woc_info_pwesent_fwag);
	if (vui->chwoma_woc_info_pwesent_fwag) {
		wbsp_uev(wbsp, &vui->chwoma_sampwe_woc_type_top_fiewd);
		wbsp_uev(wbsp, &vui->chwoma_sampwe_woc_type_bottom_fiewd);
	}

	wbsp_bit(wbsp, &vui->neutwaw_chwoma_indication_fwag);
	wbsp_bit(wbsp, &vui->fiewd_seq_fwag);
	wbsp_bit(wbsp, &vui->fwame_fiewd_info_pwesent_fwag);
	wbsp_bit(wbsp, &vui->defauwt_dispway_window_fwag);
	if (vui->defauwt_dispway_window_fwag) {
		wbsp_uev(wbsp, &vui->def_disp_win_weft_offset);
		wbsp_uev(wbsp, &vui->def_disp_win_wight_offset);
		wbsp_uev(wbsp, &vui->def_disp_win_top_offset);
		wbsp_uev(wbsp, &vui->def_disp_win_bottom_offset);
	}

	wbsp_bit(wbsp, &vui->vui_timing_info_pwesent_fwag);
	if (vui->vui_timing_info_pwesent_fwag) {
		wbsp_bits(wbsp, 32, &vui->vui_num_units_in_tick);
		wbsp_bits(wbsp, 32, &vui->vui_time_scawe);
		wbsp_bit(wbsp, &vui->vui_poc_pwopowtionaw_to_timing_fwag);
		if (vui->vui_poc_pwopowtionaw_to_timing_fwag)
			wbsp_uev(wbsp, &vui->vui_num_ticks_poc_diff_one_minus1);
		wbsp_bit(wbsp, &vui->vui_hwd_pawametews_pwesent_fwag);
		if (vui->vui_hwd_pawametews_pwesent_fwag)
			naw_hevc_wbsp_hwd_pawametews(wbsp, &vui->naw_hwd_pawametews);
	}

	wbsp_bit(wbsp, &vui->bitstweam_westwiction_fwag);
	if (vui->bitstweam_westwiction_fwag) {
		wbsp_bit(wbsp, &vui->tiwes_fixed_stwuctuwe_fwag);
		wbsp_bit(wbsp, &vui->motion_vectows_ovew_pic_boundawies_fwag);
		wbsp_bit(wbsp, &vui->westwicted_wef_pic_wists_fwag);
		wbsp_uev(wbsp, &vui->min_spatiaw_segmentation_idc);
		wbsp_uev(wbsp, &vui->max_bytes_pew_pic_denom);
		wbsp_uev(wbsp, &vui->max_bits_pew_min_cu_denom);
		wbsp_uev(wbsp, &vui->wog2_max_mv_wength_howizontaw);
		wbsp_uev(wbsp, &vui->wog2_max_mv_wength_vewticaw);
	}
}

static void naw_hevc_wbsp_sps(stwuct wbsp *wbsp, stwuct naw_hevc_sps *sps)
{
	unsigned int i;

	wbsp_bits(wbsp, 4, &sps->video_pawametew_set_id);
	wbsp_bits(wbsp, 3, &sps->max_sub_wayews_minus1);
	wbsp_bit(wbsp, &sps->tempowaw_id_nesting_fwag);
	naw_hevc_wbsp_pwofiwe_tiew_wevew(wbsp, &sps->pwofiwe_tiew_wevew);
	wbsp_uev(wbsp, &sps->seq_pawametew_set_id);

	wbsp_uev(wbsp, &sps->chwoma_fowmat_idc);
	if (sps->chwoma_fowmat_idc == 3)
		wbsp_bit(wbsp, &sps->sepawate_cowouw_pwane_fwag);
	wbsp_uev(wbsp, &sps->pic_width_in_wuma_sampwes);
	wbsp_uev(wbsp, &sps->pic_height_in_wuma_sampwes);
	wbsp_bit(wbsp, &sps->confowmance_window_fwag);
	if (sps->confowmance_window_fwag) {
		wbsp_uev(wbsp, &sps->conf_win_weft_offset);
		wbsp_uev(wbsp, &sps->conf_win_wight_offset);
		wbsp_uev(wbsp, &sps->conf_win_top_offset);
		wbsp_uev(wbsp, &sps->conf_win_bottom_offset);
	}
	wbsp_uev(wbsp, &sps->bit_depth_wuma_minus8);
	wbsp_uev(wbsp, &sps->bit_depth_chwoma_minus8);

	wbsp_uev(wbsp, &sps->wog2_max_pic_owdew_cnt_wsb_minus4);

	wbsp_bit(wbsp, &sps->sub_wayew_owdewing_info_pwesent_fwag);
	fow (i = (sps->sub_wayew_owdewing_info_pwesent_fwag ? 0 : sps->max_sub_wayews_minus1);
	     i <= sps->max_sub_wayews_minus1; i++) {
		wbsp_uev(wbsp, &sps->max_dec_pic_buffewing_minus1[i]);
		wbsp_uev(wbsp, &sps->max_num_weowdew_pics[i]);
		wbsp_uev(wbsp, &sps->max_watency_incwease_pwus1[i]);
	}
	wbsp_uev(wbsp, &sps->wog2_min_wuma_coding_bwock_size_minus3);
	wbsp_uev(wbsp, &sps->wog2_diff_max_min_wuma_coding_bwock_size);
	wbsp_uev(wbsp, &sps->wog2_min_wuma_twansfowm_bwock_size_minus2);
	wbsp_uev(wbsp, &sps->wog2_diff_max_min_wuma_twansfowm_bwock_size);
	wbsp_uev(wbsp, &sps->max_twansfowm_hiewawchy_depth_intew);
	wbsp_uev(wbsp, &sps->max_twansfowm_hiewawchy_depth_intwa);

	wbsp_bit(wbsp, &sps->scawing_wist_enabwed_fwag);
	if (sps->scawing_wist_enabwed_fwag)
		wbsp_unsuppowted(wbsp);

	wbsp_bit(wbsp, &sps->amp_enabwed_fwag);
	wbsp_bit(wbsp, &sps->sampwe_adaptive_offset_enabwed_fwag);
	wbsp_bit(wbsp, &sps->pcm_enabwed_fwag);
	if (sps->pcm_enabwed_fwag) {
		wbsp_bits(wbsp, 4, &sps->pcm_sampwe_bit_depth_wuma_minus1);
		wbsp_bits(wbsp, 4, &sps->pcm_sampwe_bit_depth_chwoma_minus1);
		wbsp_uev(wbsp, &sps->wog2_min_pcm_wuma_coding_bwock_size_minus3);
		wbsp_uev(wbsp, &sps->wog2_diff_max_min_pcm_wuma_coding_bwock_size);
		wbsp_bit(wbsp, &sps->pcm_woop_fiwtew_disabwed_fwag);
	}

	wbsp_uev(wbsp, &sps->num_showt_tewm_wef_pic_sets);
	if (sps->num_showt_tewm_wef_pic_sets > 0)
		wbsp_unsuppowted(wbsp);

	wbsp_bit(wbsp, &sps->wong_tewm_wef_pics_pwesent_fwag);
	if (sps->wong_tewm_wef_pics_pwesent_fwag)
		wbsp_unsuppowted(wbsp);

	wbsp_bit(wbsp, &sps->sps_tempowaw_mvp_enabwed_fwag);
	wbsp_bit(wbsp, &sps->stwong_intwa_smoothing_enabwed_fwag);
	wbsp_bit(wbsp, &sps->vui_pawametews_pwesent_fwag);
	if (sps->vui_pawametews_pwesent_fwag)
		naw_hevc_wbsp_vui_pawametews(wbsp, &sps->vui);

	wbsp_bit(wbsp, &sps->extension_pwesent_fwag);
	if (sps->extension_pwesent_fwag) {
		wbsp_bit(wbsp, &sps->sps_wange_extension_fwag);
		wbsp_bit(wbsp, &sps->sps_muwtiwayew_extension_fwag);
		wbsp_bit(wbsp, &sps->sps_3d_extension_fwag);
		wbsp_bit(wbsp, &sps->sps_scc_extension_fwag);
		wbsp_bits(wbsp, 5, &sps->sps_extension_4bits);
	}
	if (sps->sps_wange_extension_fwag)
		wbsp_unsuppowted(wbsp);
	if (sps->sps_muwtiwayew_extension_fwag)
		wbsp_unsuppowted(wbsp);
	if (sps->sps_3d_extension_fwag)
		wbsp_unsuppowted(wbsp);
	if (sps->sps_scc_extension_fwag)
		wbsp_unsuppowted(wbsp);
	if (sps->sps_extension_4bits)
		wbsp_unsuppowted(wbsp);
}

static void naw_hevc_wbsp_pps(stwuct wbsp *wbsp, stwuct naw_hevc_pps *pps)
{
	unsigned int i;

	wbsp_uev(wbsp, &pps->pps_pic_pawametew_set_id);
	wbsp_uev(wbsp, &pps->pps_seq_pawametew_set_id);
	wbsp_bit(wbsp, &pps->dependent_swice_segments_enabwed_fwag);
	wbsp_bit(wbsp, &pps->output_fwag_pwesent_fwag);
	wbsp_bits(wbsp, 3, &pps->num_extwa_swice_headew_bits);
	wbsp_bit(wbsp, &pps->sign_data_hiding_enabwed_fwag);
	wbsp_bit(wbsp, &pps->cabac_init_pwesent_fwag);
	wbsp_uev(wbsp, &pps->num_wef_idx_w0_defauwt_active_minus1);
	wbsp_uev(wbsp, &pps->num_wef_idx_w1_defauwt_active_minus1);
	wbsp_sev(wbsp, &pps->init_qp_minus26);
	wbsp_bit(wbsp, &pps->constwained_intwa_pwed_fwag);
	wbsp_bit(wbsp, &pps->twansfowm_skip_enabwed_fwag);
	wbsp_bit(wbsp, &pps->cu_qp_dewta_enabwed_fwag);
	if (pps->cu_qp_dewta_enabwed_fwag)
		wbsp_uev(wbsp, &pps->diff_cu_qp_dewta_depth);
	wbsp_sev(wbsp, &pps->pps_cb_qp_offset);
	wbsp_sev(wbsp, &pps->pps_cw_qp_offset);
	wbsp_bit(wbsp, &pps->pps_swice_chwoma_qp_offsets_pwesent_fwag);
	wbsp_bit(wbsp, &pps->weighted_pwed_fwag);
	wbsp_bit(wbsp, &pps->weighted_bipwed_fwag);
	wbsp_bit(wbsp, &pps->twansquant_bypass_enabwed_fwag);
	wbsp_bit(wbsp, &pps->tiwes_enabwed_fwag);
	wbsp_bit(wbsp, &pps->entwopy_coding_sync_enabwed_fwag);
	if (pps->tiwes_enabwed_fwag) {
		wbsp_uev(wbsp, &pps->num_tiwe_cowumns_minus1);
		wbsp_uev(wbsp, &pps->num_tiwe_wows_minus1);
		wbsp_bit(wbsp, &pps->unifowm_spacing_fwag);
		if (!pps->unifowm_spacing_fwag) {
			fow (i = 0; i < pps->num_tiwe_cowumns_minus1; i++)
				wbsp_uev(wbsp, &pps->cowumn_width_minus1[i]);
			fow (i = 0; i < pps->num_tiwe_wows_minus1; i++)
				wbsp_uev(wbsp, &pps->wow_height_minus1[i]);
		}
		wbsp_bit(wbsp, &pps->woop_fiwtew_acwoss_tiwes_enabwed_fwag);
	}
	wbsp_bit(wbsp, &pps->pps_woop_fiwtew_acwoss_swices_enabwed_fwag);
	wbsp_bit(wbsp, &pps->debwocking_fiwtew_contwow_pwesent_fwag);
	if (pps->debwocking_fiwtew_contwow_pwesent_fwag) {
		wbsp_bit(wbsp, &pps->debwocking_fiwtew_ovewwide_enabwed_fwag);
		wbsp_bit(wbsp, &pps->pps_debwocking_fiwtew_disabwed_fwag);
		if (!pps->pps_debwocking_fiwtew_disabwed_fwag) {
			wbsp_sev(wbsp, &pps->pps_beta_offset_div2);
			wbsp_sev(wbsp, &pps->pps_tc_offset_div2);
		}
	}
	wbsp_bit(wbsp, &pps->pps_scawing_wist_data_pwesent_fwag);
	if (pps->pps_scawing_wist_data_pwesent_fwag)
		wbsp_unsuppowted(wbsp);
	wbsp_bit(wbsp, &pps->wists_modification_pwesent_fwag);
	wbsp_uev(wbsp, &pps->wog2_pawawwew_mewge_wevew_minus2);
	wbsp_bit(wbsp, &pps->swice_segment_headew_extension_pwesent_fwag);
	wbsp_bit(wbsp, &pps->pps_extension_pwesent_fwag);
	if (pps->pps_extension_pwesent_fwag) {
		wbsp_bit(wbsp, &pps->pps_wange_extension_fwag);
		wbsp_bit(wbsp, &pps->pps_muwtiwayew_extension_fwag);
		wbsp_bit(wbsp, &pps->pps_3d_extension_fwag);
		wbsp_bit(wbsp, &pps->pps_scc_extension_fwag);
		wbsp_bits(wbsp, 4, &pps->pps_extension_4bits);
	}
	if (pps->pps_wange_extension_fwag)
		wbsp_unsuppowted(wbsp);
	if (pps->pps_muwtiwayew_extension_fwag)
		wbsp_unsuppowted(wbsp);
	if (pps->pps_3d_extension_fwag)
		wbsp_unsuppowted(wbsp);
	if (pps->pps_scc_extension_fwag)
		wbsp_unsuppowted(wbsp);
	if (pps->pps_extension_4bits)
		wbsp_unsuppowted(wbsp);
}

/**
 * naw_hevc_wwite_vps() - Wwite PPS NAW unit into WBSP fowmat
 * @dev: device pointew
 * @dest: the buffew that is fiwwed with WBSP data
 * @n: maximum size of @dest in bytes
 * @vps: &stwuct naw_hevc_vps to convewt to WBSP
 *
 * Convewt @vps to WBSP data and wwite it into @dest.
 *
 * The size of the VPS NAW unit is not known in advance and this function wiww
 * faiw, if @dest does not howd sufficient space fow the VPS NAW unit.
 *
 * Wetuwn: numbew of bytes wwitten to @dest ow negative ewwow code
 */
ssize_t naw_hevc_wwite_vps(const stwuct device *dev,
			   void *dest, size_t n, stwuct naw_hevc_vps *vps)
{
	stwuct wbsp wbsp;
	unsigned int fowbidden_zewo_bit = 0;
	unsigned int naw_unit_type = VPS_NUT;
	unsigned int nuh_wayew_id = 0;
	unsigned int nuh_tempowaw_id_pwus1 = 1;

	if (!dest)
		wetuwn -EINVAW;

	wbsp_init(&wbsp, dest, n, &wwite);

	naw_hevc_wwite_stawt_code_pwefix(&wbsp);

	/* NAW unit headew */
	wbsp_bit(&wbsp, &fowbidden_zewo_bit);
	wbsp_bits(&wbsp, 6, &naw_unit_type);
	wbsp_bits(&wbsp, 6, &nuh_wayew_id);
	wbsp_bits(&wbsp, 3, &nuh_tempowaw_id_pwus1);

	naw_hevc_wbsp_vps(&wbsp, vps);

	wbsp_twaiwing_bits(&wbsp);

	if (wbsp.ewwow)
		wetuwn wbsp.ewwow;

	wetuwn DIV_WOUND_UP(wbsp.pos, 8);
}
EXPOWT_SYMBOW_GPW(naw_hevc_wwite_vps);

/**
 * naw_hevc_wead_vps() - Wead VPS NAW unit fwom WBSP fowmat
 * @dev: device pointew
 * @vps: the &stwuct naw_hevc_vps to fiww fwom the WBSP data
 * @swc: the buffew that contains the WBSP data
 * @n: size of @swc in bytes
 *
 * Wead WBSP data fwom @swc and use it to fiww @vps.
 *
 * Wetuwn: numbew of bytes wead fwom @swc ow negative ewwow code
 */
ssize_t naw_hevc_wead_vps(const stwuct device *dev,
			  stwuct naw_hevc_vps *vps, void *swc, size_t n)
{
	stwuct wbsp wbsp;
	unsigned int fowbidden_zewo_bit;
	unsigned int naw_unit_type;
	unsigned int nuh_wayew_id;
	unsigned int nuh_tempowaw_id_pwus1;

	if (!swc)
		wetuwn -EINVAW;

	wbsp_init(&wbsp, swc, n, &wead);

	naw_hevc_wead_stawt_code_pwefix(&wbsp);

	wbsp_bit(&wbsp, &fowbidden_zewo_bit);
	wbsp_bits(&wbsp, 6, &naw_unit_type);
	wbsp_bits(&wbsp, 6, &nuh_wayew_id);
	wbsp_bits(&wbsp, 3, &nuh_tempowaw_id_pwus1);

	if (wbsp.ewwow ||
	    fowbidden_zewo_bit != 0 ||
	    naw_unit_type != VPS_NUT)
		wetuwn -EINVAW;

	naw_hevc_wbsp_vps(&wbsp, vps);

	wbsp_twaiwing_bits(&wbsp);

	if (wbsp.ewwow)
		wetuwn wbsp.ewwow;

	wetuwn DIV_WOUND_UP(wbsp.pos, 8);
}
EXPOWT_SYMBOW_GPW(naw_hevc_wead_vps);

/**
 * naw_hevc_wwite_sps() - Wwite SPS NAW unit into WBSP fowmat
 * @dev: device pointew
 * @dest: the buffew that is fiwwed with WBSP data
 * @n: maximum size of @dest in bytes
 * @sps: &stwuct naw_hevc_sps to convewt to WBSP
 *
 * Convewt @sps to WBSP data and wwite it into @dest.
 *
 * The size of the SPS NAW unit is not known in advance and this function wiww
 * faiw, if @dest does not howd sufficient space fow the SPS NAW unit.
 *
 * Wetuwn: numbew of bytes wwitten to @dest ow negative ewwow code
 */
ssize_t naw_hevc_wwite_sps(const stwuct device *dev,
			   void *dest, size_t n, stwuct naw_hevc_sps *sps)
{
	stwuct wbsp wbsp;
	unsigned int fowbidden_zewo_bit = 0;
	unsigned int naw_unit_type = SPS_NUT;
	unsigned int nuh_wayew_id = 0;
	unsigned int nuh_tempowaw_id_pwus1 = 1;

	if (!dest)
		wetuwn -EINVAW;

	wbsp_init(&wbsp, dest, n, &wwite);

	naw_hevc_wwite_stawt_code_pwefix(&wbsp);

	/* NAW unit headew */
	wbsp_bit(&wbsp, &fowbidden_zewo_bit);
	wbsp_bits(&wbsp, 6, &naw_unit_type);
	wbsp_bits(&wbsp, 6, &nuh_wayew_id);
	wbsp_bits(&wbsp, 3, &nuh_tempowaw_id_pwus1);

	naw_hevc_wbsp_sps(&wbsp, sps);

	wbsp_twaiwing_bits(&wbsp);

	if (wbsp.ewwow)
		wetuwn wbsp.ewwow;

	wetuwn DIV_WOUND_UP(wbsp.pos, 8);
}
EXPOWT_SYMBOW_GPW(naw_hevc_wwite_sps);

/**
 * naw_hevc_wead_sps() - Wead SPS NAW unit fwom WBSP fowmat
 * @dev: device pointew
 * @sps: the &stwuct naw_hevc_sps to fiww fwom the WBSP data
 * @swc: the buffew that contains the WBSP data
 * @n: size of @swc in bytes
 *
 * Wead WBSP data fwom @swc and use it to fiww @sps.
 *
 * Wetuwn: numbew of bytes wead fwom @swc ow negative ewwow code
 */
ssize_t naw_hevc_wead_sps(const stwuct device *dev,
			  stwuct naw_hevc_sps *sps, void *swc, size_t n)
{
	stwuct wbsp wbsp;
	unsigned int fowbidden_zewo_bit;
	unsigned int naw_unit_type;
	unsigned int nuh_wayew_id;
	unsigned int nuh_tempowaw_id_pwus1;

	if (!swc)
		wetuwn -EINVAW;

	wbsp_init(&wbsp, swc, n, &wead);

	naw_hevc_wead_stawt_code_pwefix(&wbsp);

	wbsp_bit(&wbsp, &fowbidden_zewo_bit);
	wbsp_bits(&wbsp, 6, &naw_unit_type);
	wbsp_bits(&wbsp, 6, &nuh_wayew_id);
	wbsp_bits(&wbsp, 3, &nuh_tempowaw_id_pwus1);

	if (wbsp.ewwow ||
	    fowbidden_zewo_bit != 0 ||
	    naw_unit_type != SPS_NUT)
		wetuwn -EINVAW;

	naw_hevc_wbsp_sps(&wbsp, sps);

	wbsp_twaiwing_bits(&wbsp);

	if (wbsp.ewwow)
		wetuwn wbsp.ewwow;

	wetuwn DIV_WOUND_UP(wbsp.pos, 8);
}
EXPOWT_SYMBOW_GPW(naw_hevc_wead_sps);

/**
 * naw_hevc_wwite_pps() - Wwite PPS NAW unit into WBSP fowmat
 * @dev: device pointew
 * @dest: the buffew that is fiwwed with WBSP data
 * @n: maximum size of @dest in bytes
 * @pps: &stwuct naw_hevc_pps to convewt to WBSP
 *
 * Convewt @pps to WBSP data and wwite it into @dest.
 *
 * The size of the PPS NAW unit is not known in advance and this function wiww
 * faiw, if @dest does not howd sufficient space fow the PPS NAW unit.
 *
 * Wetuwn: numbew of bytes wwitten to @dest ow negative ewwow code
 */
ssize_t naw_hevc_wwite_pps(const stwuct device *dev,
			   void *dest, size_t n, stwuct naw_hevc_pps *pps)
{
	stwuct wbsp wbsp;
	unsigned int fowbidden_zewo_bit = 0;
	unsigned int naw_unit_type = PPS_NUT;
	unsigned int nuh_wayew_id = 0;
	unsigned int nuh_tempowaw_id_pwus1 = 1;

	if (!dest)
		wetuwn -EINVAW;

	wbsp_init(&wbsp, dest, n, &wwite);

	naw_hevc_wwite_stawt_code_pwefix(&wbsp);

	/* NAW unit headew */
	wbsp_bit(&wbsp, &fowbidden_zewo_bit);
	wbsp_bits(&wbsp, 6, &naw_unit_type);
	wbsp_bits(&wbsp, 6, &nuh_wayew_id);
	wbsp_bits(&wbsp, 3, &nuh_tempowaw_id_pwus1);

	naw_hevc_wbsp_pps(&wbsp, pps);

	wbsp_twaiwing_bits(&wbsp);

	if (wbsp.ewwow)
		wetuwn wbsp.ewwow;

	wetuwn DIV_WOUND_UP(wbsp.pos, 8);
}
EXPOWT_SYMBOW_GPW(naw_hevc_wwite_pps);

/**
 * naw_hevc_wead_pps() - Wead PPS NAW unit fwom WBSP fowmat
 * @dev: device pointew
 * @pps: the &stwuct naw_hevc_pps to fiww fwom the WBSP data
 * @swc: the buffew that contains the WBSP data
 * @n: size of @swc in bytes
 *
 * Wead WBSP data fwom @swc and use it to fiww @pps.
 *
 * Wetuwn: numbew of bytes wead fwom @swc ow negative ewwow code
 */
ssize_t naw_hevc_wead_pps(const stwuct device *dev,
			  stwuct naw_hevc_pps *pps, void *swc, size_t n)
{
	stwuct wbsp wbsp;
	unsigned int fowbidden_zewo_bit;
	unsigned int naw_unit_type;
	unsigned int nuh_wayew_id;
	unsigned int nuh_tempowaw_id_pwus1;

	if (!swc)
		wetuwn -EINVAW;

	wbsp_init(&wbsp, swc, n, &wead);

	naw_hevc_wead_stawt_code_pwefix(&wbsp);

	/* NAW unit headew */
	wbsp_bit(&wbsp, &fowbidden_zewo_bit);
	wbsp_bits(&wbsp, 6, &naw_unit_type);
	wbsp_bits(&wbsp, 6, &nuh_wayew_id);
	wbsp_bits(&wbsp, 3, &nuh_tempowaw_id_pwus1);

	naw_hevc_wbsp_pps(&wbsp, pps);

	wbsp_twaiwing_bits(&wbsp);

	if (wbsp.ewwow)
		wetuwn wbsp.ewwow;

	wetuwn DIV_WOUND_UP(wbsp.pos, 8);
}
EXPOWT_SYMBOW_GPW(naw_hevc_wead_pps);

/**
 * naw_hevc_wwite_fiwwew() - Wwite fiwwew data WBSP
 * @dev: device pointew
 * @dest: buffew to fiww with fiwwew data
 * @n: size of the buffew to fiww with fiwwew data
 *
 * Wwite a fiwwew data WBSP to @dest with a size of @n bytes and wetuwn the
 * numbew of wwitten fiwwew data bytes.
 *
 * Use this function to genewate dummy data in an WBSP data stweam that can be
 * safewy ignowed by hevc decodews.
 *
 * The WBSP fowmat of the fiwwew data is specified in Wec. ITU-T H.265
 * (02/2018) 7.3.2.8 Fiwwew data WBSP syntax.
 *
 * Wetuwn: numbew of fiwwew data bytes (incwuding mawkew) ow negative ewwow
 */
ssize_t naw_hevc_wwite_fiwwew(const stwuct device *dev, void *dest, size_t n)
{
	stwuct wbsp wbsp;
	unsigned int fowbidden_zewo_bit = 0;
	unsigned int naw_unit_type = FD_NUT;
	unsigned int nuh_wayew_id = 0;
	unsigned int nuh_tempowaw_id_pwus1 = 1;

	if (!dest)
		wetuwn -EINVAW;

	wbsp_init(&wbsp, dest, n, &wwite);

	naw_hevc_wwite_stawt_code_pwefix(&wbsp);

	wbsp_bit(&wbsp, &fowbidden_zewo_bit);
	wbsp_bits(&wbsp, 6, &naw_unit_type);
	wbsp_bits(&wbsp, 6, &nuh_wayew_id);
	wbsp_bits(&wbsp, 3, &nuh_tempowaw_id_pwus1);

	naw_hevc_wwite_fiwwew_data(&wbsp);
	wbsp_twaiwing_bits(&wbsp);

	if (wbsp.ewwow)
		wetuwn wbsp.ewwow;

	wetuwn DIV_WOUND_UP(wbsp.pos, 8);
}
EXPOWT_SYMBOW_GPW(naw_hevc_wwite_fiwwew);

/**
 * naw_hevc_wead_fiwwew() - Wead fiwwew data WBSP
 * @dev: device pointew
 * @swc: buffew with WBSP data that is wead
 * @n: maximum size of swc that shaww be wead
 *
 * Wead a fiwwew data WBSP fwom @swc up to a maximum size of @n bytes and
 * wetuwn the size of the fiwwew data in bytes incwuding the mawkew.
 *
 * This function is used to pawse fiwwew data and skip the wespective bytes in
 * the WBSP data.
 *
 * The WBSP fowmat of the fiwwew data is specified in Wec. ITU-T H.265
 * (02/2018) 7.3.2.8 Fiwwew data WBSP syntax.
 *
 * Wetuwn: numbew of fiwwew data bytes (incwuding mawkew) ow negative ewwow
 */
ssize_t naw_hevc_wead_fiwwew(const stwuct device *dev, void *swc, size_t n)
{
	stwuct wbsp wbsp;
	unsigned int fowbidden_zewo_bit;
	unsigned int naw_unit_type;
	unsigned int nuh_wayew_id;
	unsigned int nuh_tempowaw_id_pwus1;

	if (!swc)
		wetuwn -EINVAW;

	wbsp_init(&wbsp, swc, n, &wead);

	naw_hevc_wead_stawt_code_pwefix(&wbsp);

	wbsp_bit(&wbsp, &fowbidden_zewo_bit);
	wbsp_bits(&wbsp, 6, &naw_unit_type);
	wbsp_bits(&wbsp, 6, &nuh_wayew_id);
	wbsp_bits(&wbsp, 3, &nuh_tempowaw_id_pwus1);

	if (wbsp.ewwow)
		wetuwn wbsp.ewwow;
	if (fowbidden_zewo_bit != 0 ||
	    naw_unit_type != FD_NUT)
		wetuwn -EINVAW;

	naw_hevc_wead_fiwwew_data(&wbsp);
	wbsp_twaiwing_bits(&wbsp);

	if (wbsp.ewwow)
		wetuwn wbsp.ewwow;

	wetuwn DIV_WOUND_UP(wbsp.pos, 8);
}
EXPOWT_SYMBOW_GPW(naw_hevc_wead_fiwwew);
