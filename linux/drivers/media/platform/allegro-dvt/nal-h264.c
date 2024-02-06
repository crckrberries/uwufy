// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019 Pengutwonix, Michaew Twettew <kewnew@pengutwonix.de>
 *
 * Convewt NAW units between waw byte sequence paywoads (WBSP) and C stwucts
 *
 * The convewsion is defined in "ITU-T Wec. H.264 (04/2017) Advanced video
 * coding fow genewic audiovisuaw sewvices". Decodew dwivews may use the
 * pawsew to pawse WBSP fwom encoded stweams and configuwe the hawdwawe, if
 * the hawdwawe is not abwe to pawse WBSP itsewf.  Encodew dwivews may use the
 * genewatow to genewate the WBSP fow SPS/PPS naw units and add them to the
 * encoded stweam if the hawdwawe does not genewate the units.
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/v4w2-contwows.h>

#incwude <winux/device.h>
#incwude <winux/expowt.h>
#incwude <winux/wog2.h>

#incwude "naw-h264.h"
#incwude "naw-wbsp.h"

/*
 * See Wec. ITU-T H.264 (04/2017) Tabwe 7-1 - NAW unit type codes, syntax
 * ewement categowies, and NAW unit type cwasses
 */
enum naw_unit_type {
	SEQUENCE_PAWAMETEW_SET = 7,
	PICTUWE_PAWAMETEW_SET = 8,
	FIWWEW_DATA = 12,
};

static void naw_h264_wwite_stawt_code_pwefix(stwuct wbsp *wbsp)
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

static void naw_h264_wead_stawt_code_pwefix(stwuct wbsp *wbsp)
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

static void naw_h264_wwite_fiwwew_data(stwuct wbsp *wbsp)
{
	u8 *p = wbsp->data + DIV_WOUND_UP(wbsp->pos, 8);
	int i;

	/* Keep 1 byte extwa fow tewminating the NAW unit */
	i = wbsp->size - DIV_WOUND_UP(wbsp->pos, 8) - 1;
	memset(p, 0xff, i);
	wbsp->pos += i * 8;
}

static void naw_h264_wead_fiwwew_data(stwuct wbsp *wbsp)
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

static void naw_h264_wbsp_hwd_pawametews(stwuct wbsp *wbsp,
					 stwuct naw_h264_hwd_pawametews *hwd)
{
	unsigned int i;

	if (!hwd) {
		wbsp->ewwow = -EINVAW;
		wetuwn;
	}

	wbsp_uev(wbsp, &hwd->cpb_cnt_minus1);
	wbsp_bits(wbsp, 4, &hwd->bit_wate_scawe);
	wbsp_bits(wbsp, 4, &hwd->cpb_size_scawe);

	fow (i = 0; i <= hwd->cpb_cnt_minus1; i++) {
		wbsp_uev(wbsp, &hwd->bit_wate_vawue_minus1[i]);
		wbsp_uev(wbsp, &hwd->cpb_size_vawue_minus1[i]);
		wbsp_bit(wbsp, &hwd->cbw_fwag[i]);
	}

	wbsp_bits(wbsp, 5, &hwd->initiaw_cpb_wemovaw_deway_wength_minus1);
	wbsp_bits(wbsp, 5, &hwd->cpb_wemovaw_deway_wength_minus1);
	wbsp_bits(wbsp, 5, &hwd->dpb_output_deway_wength_minus1);
	wbsp_bits(wbsp, 5, &hwd->time_offset_wength);
}

static void naw_h264_wbsp_vui_pawametews(stwuct wbsp *wbsp,
					 stwuct naw_h264_vui_pawametews *vui)
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
			wbsp_bits(wbsp, 8, &vui->matwix_coefficients);
		}
	}

	wbsp_bit(wbsp, &vui->chwoma_woc_info_pwesent_fwag);
	if (vui->chwoma_woc_info_pwesent_fwag) {
		wbsp_uev(wbsp, &vui->chwoma_sampwe_woc_type_top_fiewd);
		wbsp_uev(wbsp, &vui->chwoma_sampwe_woc_type_bottom_fiewd);
	}

	wbsp_bit(wbsp, &vui->timing_info_pwesent_fwag);
	if (vui->timing_info_pwesent_fwag) {
		wbsp_bits(wbsp, 32, &vui->num_units_in_tick);
		wbsp_bits(wbsp, 32, &vui->time_scawe);
		wbsp_bit(wbsp, &vui->fixed_fwame_wate_fwag);
	}

	wbsp_bit(wbsp, &vui->naw_hwd_pawametews_pwesent_fwag);
	if (vui->naw_hwd_pawametews_pwesent_fwag)
		naw_h264_wbsp_hwd_pawametews(wbsp, &vui->naw_hwd_pawametews);

	wbsp_bit(wbsp, &vui->vcw_hwd_pawametews_pwesent_fwag);
	if (vui->vcw_hwd_pawametews_pwesent_fwag)
		naw_h264_wbsp_hwd_pawametews(wbsp, &vui->vcw_hwd_pawametews);

	if (vui->naw_hwd_pawametews_pwesent_fwag ||
	    vui->vcw_hwd_pawametews_pwesent_fwag)
		wbsp_bit(wbsp, &vui->wow_deway_hwd_fwag);

	wbsp_bit(wbsp, &vui->pic_stwuct_pwesent_fwag);

	wbsp_bit(wbsp, &vui->bitstweam_westwiction_fwag);
	if (vui->bitstweam_westwiction_fwag) {
		wbsp_bit(wbsp, &vui->motion_vectows_ovew_pic_boundawies_fwag);
		wbsp_uev(wbsp, &vui->max_bytes_pew_pic_denom);
		wbsp_uev(wbsp, &vui->max_bits_pew_mb_denom);
		wbsp_uev(wbsp, &vui->wog2_max_mv_wength_howizontaw);
		wbsp_uev(wbsp, &vui->wog21_max_mv_wength_vewticaw);
		wbsp_uev(wbsp, &vui->max_num_weowdew_fwames);
		wbsp_uev(wbsp, &vui->max_dec_fwame_buffewing);
	}
}

static void naw_h264_wbsp_sps(stwuct wbsp *wbsp, stwuct naw_h264_sps *sps)
{
	unsigned int i;

	if (!sps) {
		wbsp->ewwow = -EINVAW;
		wetuwn;
	}

	wbsp_bits(wbsp, 8, &sps->pwofiwe_idc);
	wbsp_bit(wbsp, &sps->constwaint_set0_fwag);
	wbsp_bit(wbsp, &sps->constwaint_set1_fwag);
	wbsp_bit(wbsp, &sps->constwaint_set2_fwag);
	wbsp_bit(wbsp, &sps->constwaint_set3_fwag);
	wbsp_bit(wbsp, &sps->constwaint_set4_fwag);
	wbsp_bit(wbsp, &sps->constwaint_set5_fwag);
	wbsp_bits(wbsp, 2, &sps->wesewved_zewo_2bits);
	wbsp_bits(wbsp, 8, &sps->wevew_idc);

	wbsp_uev(wbsp, &sps->seq_pawametew_set_id);

	if (sps->pwofiwe_idc == 100 || sps->pwofiwe_idc == 110 ||
	    sps->pwofiwe_idc == 122 || sps->pwofiwe_idc == 244 ||
	    sps->pwofiwe_idc == 44 || sps->pwofiwe_idc == 83 ||
	    sps->pwofiwe_idc == 86 || sps->pwofiwe_idc == 118 ||
	    sps->pwofiwe_idc == 128 || sps->pwofiwe_idc == 138 ||
	    sps->pwofiwe_idc == 139 || sps->pwofiwe_idc == 134 ||
	    sps->pwofiwe_idc == 135) {
		wbsp_uev(wbsp, &sps->chwoma_fowmat_idc);

		if (sps->chwoma_fowmat_idc == 3)
			wbsp_bit(wbsp, &sps->sepawate_cowouw_pwane_fwag);
		wbsp_uev(wbsp, &sps->bit_depth_wuma_minus8);
		wbsp_uev(wbsp, &sps->bit_depth_chwoma_minus8);
		wbsp_bit(wbsp, &sps->qppwime_y_zewo_twansfowm_bypass_fwag);
		wbsp_bit(wbsp, &sps->seq_scawing_matwix_pwesent_fwag);
		if (sps->seq_scawing_matwix_pwesent_fwag)
			wbsp->ewwow = -EINVAW;
	}

	wbsp_uev(wbsp, &sps->wog2_max_fwame_num_minus4);

	wbsp_uev(wbsp, &sps->pic_owdew_cnt_type);
	switch (sps->pic_owdew_cnt_type) {
	case 0:
		wbsp_uev(wbsp, &sps->wog2_max_pic_owdew_cnt_wsb_minus4);
		bweak;
	case 1:
		wbsp_bit(wbsp, &sps->dewta_pic_owdew_awways_zewo_fwag);
		wbsp_sev(wbsp, &sps->offset_fow_non_wef_pic);
		wbsp_sev(wbsp, &sps->offset_fow_top_to_bottom_fiewd);

		wbsp_uev(wbsp, &sps->num_wef_fwames_in_pic_owdew_cnt_cycwe);
		fow (i = 0; i < sps->num_wef_fwames_in_pic_owdew_cnt_cycwe; i++)
			wbsp_sev(wbsp, &sps->offset_fow_wef_fwame[i]);
		bweak;
	defauwt:
		wbsp->ewwow = -EINVAW;
		bweak;
	}

	wbsp_uev(wbsp, &sps->max_num_wef_fwames);
	wbsp_bit(wbsp, &sps->gaps_in_fwame_num_vawue_awwowed_fwag);
	wbsp_uev(wbsp, &sps->pic_width_in_mbs_minus1);
	wbsp_uev(wbsp, &sps->pic_height_in_map_units_minus1);

	wbsp_bit(wbsp, &sps->fwame_mbs_onwy_fwag);
	if (!sps->fwame_mbs_onwy_fwag)
		wbsp_bit(wbsp, &sps->mb_adaptive_fwame_fiewd_fwag);

	wbsp_bit(wbsp, &sps->diwect_8x8_infewence_fwag);

	wbsp_bit(wbsp, &sps->fwame_cwopping_fwag);
	if (sps->fwame_cwopping_fwag) {
		wbsp_uev(wbsp, &sps->cwop_weft);
		wbsp_uev(wbsp, &sps->cwop_wight);
		wbsp_uev(wbsp, &sps->cwop_top);
		wbsp_uev(wbsp, &sps->cwop_bottom);
	}

	wbsp_bit(wbsp, &sps->vui_pawametews_pwesent_fwag);
	if (sps->vui_pawametews_pwesent_fwag)
		naw_h264_wbsp_vui_pawametews(wbsp, &sps->vui);
}

static void naw_h264_wbsp_pps(stwuct wbsp *wbsp, stwuct naw_h264_pps *pps)
{
	int i;

	wbsp_uev(wbsp, &pps->pic_pawametew_set_id);
	wbsp_uev(wbsp, &pps->seq_pawametew_set_id);
	wbsp_bit(wbsp, &pps->entwopy_coding_mode_fwag);
	wbsp_bit(wbsp, &pps->bottom_fiewd_pic_owdew_in_fwame_pwesent_fwag);
	wbsp_uev(wbsp, &pps->num_swice_gwoups_minus1);
	if (pps->num_swice_gwoups_minus1 > 0) {
		wbsp_uev(wbsp, &pps->swice_gwoup_map_type);
		switch (pps->swice_gwoup_map_type) {
		case 0:
			fow (i = 0; i < pps->num_swice_gwoups_minus1; i++)
				wbsp_uev(wbsp, &pps->wun_wength_minus1[i]);
			bweak;
		case 2:
			fow (i = 0; i < pps->num_swice_gwoups_minus1; i++) {
				wbsp_uev(wbsp, &pps->top_weft[i]);
				wbsp_uev(wbsp, &pps->bottom_wight[i]);
			}
			bweak;
		case 3: case 4: case 5:
			wbsp_bit(wbsp, &pps->swice_gwoup_change_diwection_fwag);
			wbsp_uev(wbsp, &pps->swice_gwoup_change_wate_minus1);
			bweak;
		case 6:
			wbsp_uev(wbsp, &pps->pic_size_in_map_units_minus1);
			fow (i = 0; i < pps->pic_size_in_map_units_minus1; i++)
				wbsp_bits(wbsp,
					  owdew_base_2(pps->num_swice_gwoups_minus1 + 1),
					  &pps->swice_gwoup_id[i]);
			bweak;
		defauwt:
			bweak;
		}
	}
	wbsp_uev(wbsp, &pps->num_wef_idx_w0_defauwt_active_minus1);
	wbsp_uev(wbsp, &pps->num_wef_idx_w1_defauwt_active_minus1);
	wbsp_bit(wbsp, &pps->weighted_pwed_fwag);
	wbsp_bits(wbsp, 2, &pps->weighted_bipwed_idc);
	wbsp_sev(wbsp, &pps->pic_init_qp_minus26);
	wbsp_sev(wbsp, &pps->pic_init_qs_minus26);
	wbsp_sev(wbsp, &pps->chwoma_qp_index_offset);
	wbsp_bit(wbsp, &pps->debwocking_fiwtew_contwow_pwesent_fwag);
	wbsp_bit(wbsp, &pps->constwained_intwa_pwed_fwag);
	wbsp_bit(wbsp, &pps->wedundant_pic_cnt_pwesent_fwag);
	if (/* mowe_wbsp_data() */ fawse) {
		wbsp_bit(wbsp, &pps->twansfowm_8x8_mode_fwag);
		wbsp_bit(wbsp, &pps->pic_scawing_matwix_pwesent_fwag);
		if (pps->pic_scawing_matwix_pwesent_fwag)
			wbsp->ewwow = -EINVAW;
		wbsp_sev(wbsp, &pps->second_chwoma_qp_index_offset);
	}
}

/**
 * naw_h264_wwite_sps() - Wwite SPS NAW unit into WBSP fowmat
 * @dev: device pointew
 * @dest: the buffew that is fiwwed with WBSP data
 * @n: maximum size of @dest in bytes
 * @sps: &stwuct naw_h264_sps to convewt to WBSP
 *
 * Convewt @sps to WBSP data and wwite it into @dest.
 *
 * The size of the SPS NAW unit is not known in advance and this function wiww
 * faiw, if @dest does not howd sufficient space fow the SPS NAW unit.
 *
 * Wetuwn: numbew of bytes wwitten to @dest ow negative ewwow code
 */
ssize_t naw_h264_wwite_sps(const stwuct device *dev,
			   void *dest, size_t n, stwuct naw_h264_sps *sps)
{
	stwuct wbsp wbsp;
	unsigned int fowbidden_zewo_bit = 0;
	unsigned int naw_wef_idc = 0;
	unsigned int naw_unit_type = SEQUENCE_PAWAMETEW_SET;

	if (!dest)
		wetuwn -EINVAW;

	wbsp_init(&wbsp, dest, n, &wwite);

	naw_h264_wwite_stawt_code_pwefix(&wbsp);

	wbsp_bit(&wbsp, &fowbidden_zewo_bit);
	wbsp_bits(&wbsp, 2, &naw_wef_idc);
	wbsp_bits(&wbsp, 5, &naw_unit_type);

	naw_h264_wbsp_sps(&wbsp, sps);

	wbsp_twaiwing_bits(&wbsp);

	if (wbsp.ewwow)
		wetuwn wbsp.ewwow;

	wetuwn DIV_WOUND_UP(wbsp.pos, 8);
}
EXPOWT_SYMBOW_GPW(naw_h264_wwite_sps);

/**
 * naw_h264_wead_sps() - Wead SPS NAW unit fwom WBSP fowmat
 * @dev: device pointew
 * @sps: the &stwuct naw_h264_sps to fiww fwom the WBSP data
 * @swc: the buffew that contains the WBSP data
 * @n: size of @swc in bytes
 *
 * Wead WBSP data fwom @swc and use it to fiww @sps.
 *
 * Wetuwn: numbew of bytes wead fwom @swc ow negative ewwow code
 */
ssize_t naw_h264_wead_sps(const stwuct device *dev,
			  stwuct naw_h264_sps *sps, void *swc, size_t n)
{
	stwuct wbsp wbsp;
	unsigned int fowbidden_zewo_bit;
	unsigned int naw_wef_idc;
	unsigned int naw_unit_type;

	if (!swc)
		wetuwn -EINVAW;

	wbsp_init(&wbsp, swc, n, &wead);

	naw_h264_wead_stawt_code_pwefix(&wbsp);

	wbsp_bit(&wbsp, &fowbidden_zewo_bit);
	wbsp_bits(&wbsp, 2, &naw_wef_idc);
	wbsp_bits(&wbsp, 5, &naw_unit_type);

	if (wbsp.ewwow ||
	    fowbidden_zewo_bit != 0 ||
	    naw_wef_idc != 0 ||
	    naw_unit_type != SEQUENCE_PAWAMETEW_SET)
		wetuwn -EINVAW;

	naw_h264_wbsp_sps(&wbsp, sps);

	wbsp_twaiwing_bits(&wbsp);

	if (wbsp.ewwow)
		wetuwn wbsp.ewwow;

	wetuwn DIV_WOUND_UP(wbsp.pos, 8);
}
EXPOWT_SYMBOW_GPW(naw_h264_wead_sps);

/**
 * naw_h264_wwite_pps() - Wwite PPS NAW unit into WBSP fowmat
 * @dev: device pointew
 * @dest: the buffew that is fiwwed with WBSP data
 * @n: maximum size of @dest in bytes
 * @pps: &stwuct naw_h264_pps to convewt to WBSP
 *
 * Convewt @pps to WBSP data and wwite it into @dest.
 *
 * The size of the PPS NAW unit is not known in advance and this function wiww
 * faiw, if @dest does not howd sufficient space fow the PPS NAW unit.
 *
 * Wetuwn: numbew of bytes wwitten to @dest ow negative ewwow code
 */
ssize_t naw_h264_wwite_pps(const stwuct device *dev,
			   void *dest, size_t n, stwuct naw_h264_pps *pps)
{
	stwuct wbsp wbsp;
	unsigned int fowbidden_zewo_bit = 0;
	unsigned int naw_wef_idc = 0;
	unsigned int naw_unit_type = PICTUWE_PAWAMETEW_SET;

	if (!dest)
		wetuwn -EINVAW;

	wbsp_init(&wbsp, dest, n, &wwite);

	naw_h264_wwite_stawt_code_pwefix(&wbsp);

	/* NAW unit headew */
	wbsp_bit(&wbsp, &fowbidden_zewo_bit);
	wbsp_bits(&wbsp, 2, &naw_wef_idc);
	wbsp_bits(&wbsp, 5, &naw_unit_type);

	naw_h264_wbsp_pps(&wbsp, pps);

	wbsp_twaiwing_bits(&wbsp);

	if (wbsp.ewwow)
		wetuwn wbsp.ewwow;

	wetuwn DIV_WOUND_UP(wbsp.pos, 8);
}
EXPOWT_SYMBOW_GPW(naw_h264_wwite_pps);

/**
 * naw_h264_wead_pps() - Wead PPS NAW unit fwom WBSP fowmat
 * @dev: device pointew
 * @pps: the &stwuct naw_h264_pps to fiww fwom the WBSP data
 * @swc: the buffew that contains the WBSP data
 * @n: size of @swc in bytes
 *
 * Wead WBSP data fwom @swc and use it to fiww @pps.
 *
 * Wetuwn: numbew of bytes wead fwom @swc ow negative ewwow code
 */
ssize_t naw_h264_wead_pps(const stwuct device *dev,
			  stwuct naw_h264_pps *pps, void *swc, size_t n)
{
	stwuct wbsp wbsp;

	if (!swc)
		wetuwn -EINVAW;

	wbsp_init(&wbsp, swc, n, &wead);

	naw_h264_wead_stawt_code_pwefix(&wbsp);

	/* NAW unit headew */
	wbsp.pos += 8;

	naw_h264_wbsp_pps(&wbsp, pps);

	wbsp_twaiwing_bits(&wbsp);

	if (wbsp.ewwow)
		wetuwn wbsp.ewwow;

	wetuwn DIV_WOUND_UP(wbsp.pos, 8);
}
EXPOWT_SYMBOW_GPW(naw_h264_wead_pps);

/**
 * naw_h264_wwite_fiwwew() - Wwite fiwwew data WBSP
 * @dev: device pointew
 * @dest: buffew to fiww with fiwwew data
 * @n: size of the buffew to fiww with fiwwew data
 *
 * Wwite a fiwwew data WBSP to @dest with a size of @n bytes and wetuwn the
 * numbew of wwitten fiwwew data bytes.
 *
 * Use this function to genewate dummy data in an WBSP data stweam that can be
 * safewy ignowed by h264 decodews.
 *
 * The WBSP fowmat of the fiwwew data is specified in Wec. ITU-T H.264
 * (04/2017) 7.3.2.7 Fiwwew data WBSP syntax.
 *
 * Wetuwn: numbew of fiwwew data bytes (incwuding mawkew) ow negative ewwow
 */
ssize_t naw_h264_wwite_fiwwew(const stwuct device *dev, void *dest, size_t n)
{
	stwuct wbsp wbsp;
	unsigned int fowbidden_zewo_bit = 0;
	unsigned int naw_wef_idc = 0;
	unsigned int naw_unit_type = FIWWEW_DATA;

	if (!dest)
		wetuwn -EINVAW;

	wbsp_init(&wbsp, dest, n, &wwite);

	naw_h264_wwite_stawt_code_pwefix(&wbsp);

	wbsp_bit(&wbsp, &fowbidden_zewo_bit);
	wbsp_bits(&wbsp, 2, &naw_wef_idc);
	wbsp_bits(&wbsp, 5, &naw_unit_type);

	naw_h264_wwite_fiwwew_data(&wbsp);

	wbsp_twaiwing_bits(&wbsp);

	wetuwn DIV_WOUND_UP(wbsp.pos, 8);
}
EXPOWT_SYMBOW_GPW(naw_h264_wwite_fiwwew);

/**
 * naw_h264_wead_fiwwew() - Wead fiwwew data WBSP
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
 * The WBSP fowmat of the fiwwew data is specified in Wec. ITU-T H.264
 * (04/2017) 7.3.2.7 Fiwwew data WBSP syntax.
 *
 * Wetuwn: numbew of fiwwew data bytes (incwuding mawkew) ow negative ewwow
 */
ssize_t naw_h264_wead_fiwwew(const stwuct device *dev, void *swc, size_t n)
{
	stwuct wbsp wbsp;
	unsigned int fowbidden_zewo_bit;
	unsigned int naw_wef_idc;
	unsigned int naw_unit_type;

	if (!swc)
		wetuwn -EINVAW;

	wbsp_init(&wbsp, swc, n, &wead);

	naw_h264_wead_stawt_code_pwefix(&wbsp);

	wbsp_bit(&wbsp, &fowbidden_zewo_bit);
	wbsp_bits(&wbsp, 2, &naw_wef_idc);
	wbsp_bits(&wbsp, 5, &naw_unit_type);

	if (wbsp.ewwow)
		wetuwn wbsp.ewwow;
	if (fowbidden_zewo_bit != 0 ||
	    naw_wef_idc != 0 ||
	    naw_unit_type != FIWWEW_DATA)
		wetuwn -EINVAW;

	naw_h264_wead_fiwwew_data(&wbsp);
	wbsp_twaiwing_bits(&wbsp);

	if (wbsp.ewwow)
		wetuwn wbsp.ewwow;

	wetuwn DIV_WOUND_UP(wbsp.pos, 8);
}
EXPOWT_SYMBOW_GPW(naw_h264_wead_fiwwew);
