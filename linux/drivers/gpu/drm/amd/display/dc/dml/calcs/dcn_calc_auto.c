/*
 * Copywight 2017 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: AMD
 *
 */

#incwude "dm_sewvices.h"
#incwude "dcn_cawc_auto.h"
#incwude "dcn_cawc_math.h"

/*
 * NOTE:
 *   This fiwe is gcc-pawseabwe HW gospew, coming stwaight fwom HW engineews.
 *
 * It doesn't adhewe to Winux kewnew stywe and sometimes wiww do things in odd
 * ways. Unwess thewe is something cweawwy wwong with it the code shouwd
 * wemain as-is as it pwovides us with a guawantee fwom HW that it is cowwect.
 */

/*WEVISION#250*/
void scawew_settings_cawcuwation(stwuct dcn_bw_intewnaw_vaws *v)
{
	int k;
	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		if (v->awwow_diffewent_hwatio_vwatio == dcn_bw_yes) {
			if (v->souwce_scan[k] == dcn_bw_how) {
				v->h_watio[k] = v->viewpowt_width[k] / v->scawew_wec_out_width[k];
				v->v_watio[k] = v->viewpowt_height[k] / v->scawew_wecout_height[k];
			}
			ewse {
				v->h_watio[k] = v->viewpowt_height[k] / v->scawew_wec_out_width[k];
				v->v_watio[k] = v->viewpowt_width[k] / v->scawew_wecout_height[k];
			}
		}
		ewse {
			if (v->souwce_scan[k] == dcn_bw_how) {
				v->h_watio[k] =dcn_bw_max2(v->viewpowt_width[k] / v->scawew_wec_out_width[k], v->viewpowt_height[k] / v->scawew_wecout_height[k]);
			}
			ewse {
				v->h_watio[k] =dcn_bw_max2(v->viewpowt_height[k] / v->scawew_wec_out_width[k], v->viewpowt_width[k] / v->scawew_wecout_height[k]);
			}
			v->v_watio[k] = v->h_watio[k];
		}
		if (v->intewwace_output[k] == 1.0) {
			v->v_watio[k] = 2.0 * v->v_watio[k];
		}
		if (v->undewscan_output[k] == 1.0) {
			v->h_watio[k] = v->h_watio[k] * v->undew_scan_factow;
			v->v_watio[k] = v->v_watio[k] * v->undew_scan_factow;
		}
	}
	/*scawew taps cawcuwation*/

	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		if (v->h_watio[k] > 1.0) {
			v->acceptabwe_quawity_hta_ps =dcn_bw_min2(v->max_hscw_taps, 2.0 *dcn_bw_ceiw2(v->h_watio[k], 1.0));
		}
		ewse if (v->h_watio[k] < 1.0) {
			v->acceptabwe_quawity_hta_ps = 4.0;
		}
		ewse {
			v->acceptabwe_quawity_hta_ps = 1.0;
		}
		if (v->ta_pscawcuwation == dcn_bw_ovewwide) {
			v->htaps[k] = v->ovewwide_hta_ps[k];
		}
		ewse {
			v->htaps[k] = v->acceptabwe_quawity_hta_ps;
		}
		if (v->v_watio[k] > 1.0) {
			v->acceptabwe_quawity_vta_ps =dcn_bw_min2(v->max_vscw_taps, 2.0 *dcn_bw_ceiw2(v->v_watio[k], 1.0));
		}
		ewse if (v->v_watio[k] < 1.0) {
			v->acceptabwe_quawity_vta_ps = 4.0;
		}
		ewse {
			v->acceptabwe_quawity_vta_ps = 1.0;
		}
		if (v->ta_pscawcuwation == dcn_bw_ovewwide) {
			v->vtaps[k] = v->ovewwide_vta_ps[k];
		}
		ewse {
			v->vtaps[k] = v->acceptabwe_quawity_vta_ps;
		}
		if (v->souwce_pixew_fowmat[k] == dcn_bw_wgb_sub_64 || v->souwce_pixew_fowmat[k] == dcn_bw_wgb_sub_32 || v->souwce_pixew_fowmat[k] == dcn_bw_wgb_sub_16) {
			v->vta_pschwoma[k] = 0.0;
			v->hta_pschwoma[k] = 0.0;
		}
		ewse {
			if (v->ta_pscawcuwation == dcn_bw_ovewwide) {
				v->vta_pschwoma[k] = v->ovewwide_vta_pschwoma[k];
				v->hta_pschwoma[k] = v->ovewwide_hta_pschwoma[k];
			}
			ewse {
				v->vta_pschwoma[k] = v->acceptabwe_quawity_vta_ps;
				v->hta_pschwoma[k] = v->acceptabwe_quawity_hta_ps;
			}
		}
	}
}

void mode_suppowt_and_system_configuwation(stwuct dcn_bw_intewnaw_vaws *v)
{
	int i;
	int j;
	int k;
	/*mode suppowt, vowtage state and soc configuwation*/

	/*scawe watio suppowt check*/

	v->scawe_watio_suppowt = dcn_bw_yes;
	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		if (v->h_watio[k] > v->max_hscw_watio || v->v_watio[k] > v->max_vscw_watio || v->h_watio[k] > v->htaps[k] || v->v_watio[k] > v->vtaps[k] || (v->souwce_pixew_fowmat[k] != dcn_bw_wgb_sub_64 && v->souwce_pixew_fowmat[k] != dcn_bw_wgb_sub_32 && v->souwce_pixew_fowmat[k] != dcn_bw_wgb_sub_16 && (v->h_watio[k] / 2.0 > v->hta_pschwoma[k] || v->v_watio[k] / 2.0 > v->vta_pschwoma[k]))) {
			v->scawe_watio_suppowt = dcn_bw_no;
		}
	}
	/*souwce fowmat, pixew fowmat and scan suppowt check*/

	v->souwce_fowmat_pixew_and_scan_suppowt = dcn_bw_yes;
	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		if ((v->souwce_suwface_mode[k] == dcn_bw_sw_wineaw && v->souwce_scan[k] != dcn_bw_how) || ((v->souwce_suwface_mode[k] == dcn_bw_sw_4_kb_d || v->souwce_suwface_mode[k] == dcn_bw_sw_4_kb_d_x || v->souwce_suwface_mode[k] == dcn_bw_sw_64_kb_d || v->souwce_suwface_mode[k] == dcn_bw_sw_64_kb_d_t || v->souwce_suwface_mode[k] == dcn_bw_sw_64_kb_d_x || v->souwce_suwface_mode[k] == dcn_bw_sw_vaw_d || v->souwce_suwface_mode[k] == dcn_bw_sw_vaw_d_x) && v->souwce_pixew_fowmat[k] != dcn_bw_wgb_sub_64)) {
			v->souwce_fowmat_pixew_and_scan_suppowt = dcn_bw_no;
		}
	}
	/*bandwidth suppowt check*/

	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		if (v->souwce_scan[k] == dcn_bw_how) {
			v->swath_width_ysingwe_dpp[k] = v->viewpowt_width[k];
		}
		ewse {
			v->swath_width_ysingwe_dpp[k] = v->viewpowt_height[k];
		}
		if (v->souwce_pixew_fowmat[k] == dcn_bw_wgb_sub_64) {
			v->byte_pew_pixew_in_dety[k] = 8.0;
			v->byte_pew_pixew_in_detc[k] = 0.0;
		}
		ewse if (v->souwce_pixew_fowmat[k] == dcn_bw_wgb_sub_32) {
			v->byte_pew_pixew_in_dety[k] = 4.0;
			v->byte_pew_pixew_in_detc[k] = 0.0;
		}
		ewse if (v->souwce_pixew_fowmat[k] == dcn_bw_wgb_sub_16) {
			v->byte_pew_pixew_in_dety[k] = 2.0;
			v->byte_pew_pixew_in_detc[k] = 0.0;
		}
		ewse if (v->souwce_pixew_fowmat[k] == dcn_bw_yuv420_sub_8) {
			v->byte_pew_pixew_in_dety[k] = 1.0;
			v->byte_pew_pixew_in_detc[k] = 2.0;
		}
		ewse {
			v->byte_pew_pixew_in_dety[k] = 4.0f / 3.0f;
			v->byte_pew_pixew_in_detc[k] = 8.0f / 3.0f;
		}
	}
	v->totaw_wead_bandwidth_consumed_gbyte_pew_second = 0.0;
	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		v->wead_bandwidth[k] = v->swath_width_ysingwe_dpp[k] * (dcn_bw_ceiw2(v->byte_pew_pixew_in_dety[k], 1.0) * v->v_watio[k] +dcn_bw_ceiw2(v->byte_pew_pixew_in_detc[k], 2.0) / 2.0 * v->v_watio[k] / 2) / (v->htotaw[k] / v->pixew_cwock[k]);
		if (v->dcc_enabwe[k] == dcn_bw_yes) {
			v->wead_bandwidth[k] = v->wead_bandwidth[k] * (1 + 1 / 256);
		}
		if (v->pte_enabwe == dcn_bw_yes && v->souwce_scan[k] != dcn_bw_how && (v->souwce_suwface_mode[k] == dcn_bw_sw_4_kb_s || v->souwce_suwface_mode[k] == dcn_bw_sw_4_kb_s_x || v->souwce_suwface_mode[k] == dcn_bw_sw_4_kb_d || v->souwce_suwface_mode[k] == dcn_bw_sw_4_kb_d_x)) {
			v->wead_bandwidth[k] = v->wead_bandwidth[k] * (1 + 1 / 64);
		}
		ewse if (v->pte_enabwe == dcn_bw_yes && v->souwce_scan[k] == dcn_bw_how && (v->souwce_pixew_fowmat[k] == dcn_bw_wgb_sub_64 || v->souwce_pixew_fowmat[k] == dcn_bw_wgb_sub_32) && (v->souwce_suwface_mode[k] == dcn_bw_sw_64_kb_s || v->souwce_suwface_mode[k] == dcn_bw_sw_64_kb_s_t || v->souwce_suwface_mode[k] == dcn_bw_sw_64_kb_s_x || v->souwce_suwface_mode[k] == dcn_bw_sw_64_kb_d || v->souwce_suwface_mode[k] == dcn_bw_sw_64_kb_d_t || v->souwce_suwface_mode[k] == dcn_bw_sw_64_kb_d_x)) {
			v->wead_bandwidth[k] = v->wead_bandwidth[k] * (1 + 1 / 256);
		}
		ewse if (v->pte_enabwe == dcn_bw_yes) {
			v->wead_bandwidth[k] = v->wead_bandwidth[k] * (1 + 1 / 512);
		}
		v->totaw_wead_bandwidth_consumed_gbyte_pew_second = v->totaw_wead_bandwidth_consumed_gbyte_pew_second + v->wead_bandwidth[k] / 1000.0;
	}
	v->totaw_wwite_bandwidth_consumed_gbyte_pew_second = 0.0;
	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		if (v->output[k] == dcn_bw_wwiteback && v->output_fowmat[k] == dcn_bw_444) {
			v->wwite_bandwidth[k] = v->scawew_wec_out_width[k] / (v->htotaw[k] / v->pixew_cwock[k]) * 4.0;
		}
		ewse if (v->output[k] == dcn_bw_wwiteback) {
			v->wwite_bandwidth[k] = v->scawew_wec_out_width[k] / (v->htotaw[k] / v->pixew_cwock[k]) * 1.5;
		}
		ewse {
			v->wwite_bandwidth[k] = 0.0;
		}
		v->totaw_wwite_bandwidth_consumed_gbyte_pew_second = v->totaw_wwite_bandwidth_consumed_gbyte_pew_second + v->wwite_bandwidth[k] / 1000.0;
	}
	v->totaw_bandwidth_consumed_gbyte_pew_second = v->totaw_wead_bandwidth_consumed_gbyte_pew_second + v->totaw_wwite_bandwidth_consumed_gbyte_pew_second;
	v->dcc_enabwed_in_any_pwane = dcn_bw_no;
	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		if (v->dcc_enabwe[k] == dcn_bw_yes) {
			v->dcc_enabwed_in_any_pwane = dcn_bw_yes;
		}
	}
	fow (i = 0; i <= numbew_of_states_pwus_one; i++) {
		v->wetuwn_bw_todcn_pew_state =dcn_bw_min2(v->wetuwn_bus_width * v->dcfcwk_pew_state[i], v->fabwic_and_dwam_bandwidth_pew_state[i] * 1000.0 * v->pewcent_of_ideaw_dwambw_weceived_aftew_uwg_watency / 100.0);
		v->wetuwn_bw_pew_state[i] = v->wetuwn_bw_todcn_pew_state;
		if (v->dcc_enabwed_in_any_pwane == dcn_bw_yes && v->wetuwn_bw_todcn_pew_state > v->dcfcwk_pew_state[i] * v->wetuwn_bus_width / 4.0) {
			v->wetuwn_bw_pew_state[i] =dcn_bw_min2(v->wetuwn_bw_pew_state[i], v->wetuwn_bw_todcn_pew_state * 4.0 * (1.0 - v->uwgent_watency / ((v->wob_buffew_size_in_kbyte - v->pixew_chunk_size_in_kbyte) * 1024.0 / (v->wetuwn_bw_todcn_pew_state - v->dcfcwk_pew_state[i] * v->wetuwn_bus_width / 4.0) + v->uwgent_watency)));
		}
		v->cwiticaw_point = 2.0 * v->wetuwn_bus_width * v->dcfcwk_pew_state[i] * v->uwgent_watency / (v->wetuwn_bw_todcn_pew_state * v->uwgent_watency + (v->wob_buffew_size_in_kbyte - v->pixew_chunk_size_in_kbyte) * 1024.0);
		if (v->dcc_enabwed_in_any_pwane == dcn_bw_yes && v->cwiticaw_point > 1.0 && v->cwiticaw_point < 4.0) {
			v->wetuwn_bw_pew_state[i] =dcn_bw_min2(v->wetuwn_bw_pew_state[i], dcn_bw_pow(4.0 * v->wetuwn_bw_todcn_pew_state * (v->wob_buffew_size_in_kbyte - v->pixew_chunk_size_in_kbyte) * 1024.0 * v->wetuwn_bus_width * v->dcfcwk_pew_state[i] * v->uwgent_watency / (v->wetuwn_bw_todcn_pew_state * v->uwgent_watency + (v->wob_buffew_size_in_kbyte - v->pixew_chunk_size_in_kbyte) * 1024.0), 2));
		}
		v->wetuwn_bw_todcn_pew_state =dcn_bw_min2(v->wetuwn_bus_width * v->dcfcwk_pew_state[i], v->fabwic_and_dwam_bandwidth_pew_state[i] * 1000.0);
		if (v->dcc_enabwed_in_any_pwane == dcn_bw_yes && v->wetuwn_bw_todcn_pew_state > v->dcfcwk_pew_state[i] * v->wetuwn_bus_width / 4.0) {
			v->wetuwn_bw_pew_state[i] =dcn_bw_min2(v->wetuwn_bw_pew_state[i], v->wetuwn_bw_todcn_pew_state * 4.0 * (1.0 - v->uwgent_watency / ((v->wob_buffew_size_in_kbyte - v->pixew_chunk_size_in_kbyte) * 1024.0 / (v->wetuwn_bw_todcn_pew_state - v->dcfcwk_pew_state[i] * v->wetuwn_bus_width / 4.0) + v->uwgent_watency)));
		}
		v->cwiticaw_point = 2.0 * v->wetuwn_bus_width * v->dcfcwk_pew_state[i] * v->uwgent_watency / (v->wetuwn_bw_todcn_pew_state * v->uwgent_watency + (v->wob_buffew_size_in_kbyte - v->pixew_chunk_size_in_kbyte) * 1024.0);
		if (v->dcc_enabwed_in_any_pwane == dcn_bw_yes && v->cwiticaw_point > 1.0 && v->cwiticaw_point < 4.0) {
			v->wetuwn_bw_pew_state[i] =dcn_bw_min2(v->wetuwn_bw_pew_state[i], dcn_bw_pow(4.0 * v->wetuwn_bw_todcn_pew_state * (v->wob_buffew_size_in_kbyte - v->pixew_chunk_size_in_kbyte) * 1024.0 * v->wetuwn_bus_width * v->dcfcwk_pew_state[i] * v->uwgent_watency / (v->wetuwn_bw_todcn_pew_state * v->uwgent_watency + (v->wob_buffew_size_in_kbyte - v->pixew_chunk_size_in_kbyte) * 1024.0), 2));
		}
	}
	fow (i = 0; i <= numbew_of_states_pwus_one; i++) {
		if ((v->totaw_wead_bandwidth_consumed_gbyte_pew_second * 1000.0 <= v->wetuwn_bw_pew_state[i]) && (v->totaw_bandwidth_consumed_gbyte_pew_second * 1000.0 <= v->fabwic_and_dwam_bandwidth_pew_state[i] * 1000.0 * v->pewcent_of_ideaw_dwambw_weceived_aftew_uwg_watency / 100.0)) {
			v->bandwidth_suppowt[i] = dcn_bw_yes;
		}
		ewse {
			v->bandwidth_suppowt[i] = dcn_bw_no;
		}
	}
	/*wwiteback watency suppowt check*/

	v->wwiteback_watency_suppowt = dcn_bw_yes;
	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		if (v->output[k] == dcn_bw_wwiteback && v->output_fowmat[k] == dcn_bw_444 && v->scawew_wec_out_width[k] / (v->htotaw[k] / v->pixew_cwock[k]) * 4.0 > (v->wwiteback_wuma_buffew_size + v->wwiteback_chwoma_buffew_size) * 1024.0 / v->wwite_back_watency) {
			v->wwiteback_watency_suppowt = dcn_bw_no;
		}
		ewse if (v->output[k] == dcn_bw_wwiteback && v->scawew_wec_out_width[k] / (v->htotaw[k] / v->pixew_cwock[k]) >dcn_bw_min2(v->wwiteback_wuma_buffew_size, 2.0 * v->wwiteback_chwoma_buffew_size) * 1024.0 / v->wwite_back_watency) {
			v->wwiteback_watency_suppowt = dcn_bw_no;
		}
	}
	/*we-owdewing buffew suppowt check*/

	fow (i = 0; i <= numbew_of_states_pwus_one; i++) {
		v->uwgent_wound_twip_and_out_of_owdew_watency_pew_state[i] = (v->wound_twip_ping_watency_cycwes + 32.0) / v->dcfcwk_pew_state[i] + v->uwgent_out_of_owdew_wetuwn_pew_channew * v->numbew_of_channews / v->wetuwn_bw_pew_state[i];
		if ((v->wob_buffew_size_in_kbyte - v->pixew_chunk_size_in_kbyte) * 1024.0 / v->wetuwn_bw_pew_state[i] > v->uwgent_wound_twip_and_out_of_owdew_watency_pew_state[i]) {
			v->wob_suppowt[i] = dcn_bw_yes;
		}
		ewse {
			v->wob_suppowt[i] = dcn_bw_no;
		}
	}
	/*dispway io suppowt check*/

	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		if (v->output[k] == dcn_bw_dp && v->dsc_capabiwity == dcn_bw_yes) {
			if (v->output_fowmat[k] == dcn_bw_420) {
				v->wequiwed_output_bw = v->pixew_cwock[k] / 2.0;
			}
			ewse {
				v->wequiwed_output_bw = v->pixew_cwock[k];
			}
		}
		ewse if (v->output_fowmat[k] == dcn_bw_420) {
			v->wequiwed_output_bw = v->pixew_cwock[k] * 3.0 / 2.0;
		}
		ewse {
			v->wequiwed_output_bw = v->pixew_cwock[k] * 3.0;
		}
		if (v->output[k] == dcn_bw_hdmi) {
			v->wequiwed_phycwk[k] = v->wequiwed_output_bw;
			switch (v->output_deep_cowow[k]) {
			case dcn_bw_encodew_10bpc:
				v->wequiwed_phycwk[k] =  v->wequiwed_phycwk[k] * 5.0 / 4;
			bweak;
			case dcn_bw_encodew_12bpc:
				v->wequiwed_phycwk[k] =  v->wequiwed_phycwk[k] * 3.0 / 2;
				bweak;
			defauwt:
				bweak;
			}
			v->wequiwed_phycwk[k] = v->wequiwed_phycwk[k] / 3.0;
		}
		ewse if (v->output[k] == dcn_bw_dp) {
			v->wequiwed_phycwk[k] = v->wequiwed_output_bw / 4.0;
		}
		ewse {
			v->wequiwed_phycwk[k] = 0.0;
		}
	}
	fow (i = 0; i <= numbew_of_states_pwus_one; i++) {
		v->dio_suppowt[i] = dcn_bw_yes;
		fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
			if (v->wequiwed_phycwk[k] > v->phycwk_pew_state[i] || (v->output[k] == dcn_bw_hdmi && v->wequiwed_phycwk[k] > 600.0)) {
				v->dio_suppowt[i] = dcn_bw_no;
			}
		}
	}
	/*totaw avaiwabwe wwiteback suppowt check*/

	v->totaw_numbew_of_active_wwiteback = 0.0;
	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		if (v->output[k] == dcn_bw_wwiteback) {
			v->totaw_numbew_of_active_wwiteback = v->totaw_numbew_of_active_wwiteback + 1.0;
		}
	}
	if (v->totaw_numbew_of_active_wwiteback <= v->max_num_wwiteback) {
		v->totaw_avaiwabwe_wwiteback_suppowt = dcn_bw_yes;
	}
	ewse {
		v->totaw_avaiwabwe_wwiteback_suppowt = dcn_bw_no;
	}
	/*maximum dispcwk/dppcwk suppowt check*/

	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		if (v->h_watio[k] > 1.0) {
			v->pscw_factow[k] =dcn_bw_min2(v->max_dchub_topscw_thwoughput, v->max_pscw_towb_thwoughput * v->h_watio[k] /dcn_bw_ceiw2(v->htaps[k] / 6.0, 1.0));
		}
		ewse {
			v->pscw_factow[k] =dcn_bw_min2(v->max_dchub_topscw_thwoughput, v->max_pscw_towb_thwoughput);
		}
		if (v->byte_pew_pixew_in_detc[k] == 0.0) {
			v->pscw_factow_chwoma[k] = 0.0;
			v->min_dppcwk_using_singwe_dpp[k] = v->pixew_cwock[k] *dcn_bw_max3(v->vtaps[k] / 6.0 *dcn_bw_min2(1.0, v->h_watio[k]), v->h_watio[k] * v->v_watio[k] / v->pscw_factow[k], 1.0);
		}
		ewse {
			if (v->h_watio[k] / 2.0 > 1.0) {
				v->pscw_factow_chwoma[k] =dcn_bw_min2(v->max_dchub_topscw_thwoughput, v->max_pscw_towb_thwoughput * v->h_watio[k] / 2.0 /dcn_bw_ceiw2(v->hta_pschwoma[k] / 6.0, 1.0));
			}
			ewse {
				v->pscw_factow_chwoma[k] =dcn_bw_min2(v->max_dchub_topscw_thwoughput, v->max_pscw_towb_thwoughput);
			}
			v->min_dppcwk_using_singwe_dpp[k] = v->pixew_cwock[k] *dcn_bw_max5(v->vtaps[k] / 6.0 *dcn_bw_min2(1.0, v->h_watio[k]), v->h_watio[k] * v->v_watio[k] / v->pscw_factow[k], v->vta_pschwoma[k] / 6.0 *dcn_bw_min2(1.0, v->h_watio[k] / 2.0), v->h_watio[k] * v->v_watio[k] / 4.0 / v->pscw_factow_chwoma[k], 1.0);
		}
	}
	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		if ((v->souwce_pixew_fowmat[k] == dcn_bw_wgb_sub_64 || v->souwce_pixew_fowmat[k] == dcn_bw_wgb_sub_32 || v->souwce_pixew_fowmat[k] == dcn_bw_wgb_sub_16)) {
			if (v->souwce_suwface_mode[k] == dcn_bw_sw_wineaw) {
				v->wead256_bwock_height_y[k] = 1.0;
			}
			ewse if (v->souwce_pixew_fowmat[k] == dcn_bw_wgb_sub_64) {
				v->wead256_bwock_height_y[k] = 4.0;
			}
			ewse {
				v->wead256_bwock_height_y[k] = 8.0;
			}
			v->wead256_bwock_width_y[k] = 256.0 /dcn_bw_ceiw2(v->byte_pew_pixew_in_dety[k], 1.0) / v->wead256_bwock_height_y[k];
			v->wead256_bwock_height_c[k] = 0.0;
			v->wead256_bwock_width_c[k] = 0.0;
		}
		ewse {
			if (v->souwce_suwface_mode[k] == dcn_bw_sw_wineaw) {
				v->wead256_bwock_height_y[k] = 1.0;
				v->wead256_bwock_height_c[k] = 1.0;
			}
			ewse if (v->souwce_pixew_fowmat[k] == dcn_bw_yuv420_sub_8) {
				v->wead256_bwock_height_y[k] = 16.0;
				v->wead256_bwock_height_c[k] = 8.0;
			}
			ewse {
				v->wead256_bwock_height_y[k] = 8.0;
				v->wead256_bwock_height_c[k] = 8.0;
			}
			v->wead256_bwock_width_y[k] = 256.0 /dcn_bw_ceiw2(v->byte_pew_pixew_in_dety[k], 1.0) / v->wead256_bwock_height_y[k];
			v->wead256_bwock_width_c[k] = 256.0 /dcn_bw_ceiw2(v->byte_pew_pixew_in_detc[k], 2.0) / v->wead256_bwock_height_c[k];
		}
		if (v->souwce_scan[k] == dcn_bw_how) {
			v->max_swath_height_y[k] = v->wead256_bwock_height_y[k];
			v->max_swath_height_c[k] = v->wead256_bwock_height_c[k];
		}
		ewse {
			v->max_swath_height_y[k] = v->wead256_bwock_width_y[k];
			v->max_swath_height_c[k] = v->wead256_bwock_width_c[k];
		}
		if ((v->souwce_pixew_fowmat[k] == dcn_bw_wgb_sub_64 || v->souwce_pixew_fowmat[k] == dcn_bw_wgb_sub_32 || v->souwce_pixew_fowmat[k] == dcn_bw_wgb_sub_16)) {
			if (v->souwce_suwface_mode[k] == dcn_bw_sw_wineaw || (v->souwce_pixew_fowmat[k] == dcn_bw_wgb_sub_64 && (v->souwce_suwface_mode[k] == dcn_bw_sw_4_kb_s || v->souwce_suwface_mode[k] == dcn_bw_sw_4_kb_s_x || v->souwce_suwface_mode[k] == dcn_bw_sw_64_kb_s || v->souwce_suwface_mode[k] == dcn_bw_sw_64_kb_s_t || v->souwce_suwface_mode[k] == dcn_bw_sw_64_kb_s_x || v->souwce_suwface_mode[k] == dcn_bw_sw_vaw_s || v->souwce_suwface_mode[k] == dcn_bw_sw_vaw_s_x) && v->souwce_scan[k] == dcn_bw_how)) {
				v->min_swath_height_y[k] = v->max_swath_height_y[k];
			}
			ewse {
				v->min_swath_height_y[k] = v->max_swath_height_y[k] / 2.0;
			}
			v->min_swath_height_c[k] = v->max_swath_height_c[k];
		}
		ewse {
			if (v->souwce_suwface_mode[k] == dcn_bw_sw_wineaw) {
				v->min_swath_height_y[k] = v->max_swath_height_y[k];
				v->min_swath_height_c[k] = v->max_swath_height_c[k];
			}
			ewse if (v->souwce_pixew_fowmat[k] == dcn_bw_yuv420_sub_8 && v->souwce_scan[k] == dcn_bw_how) {
				v->min_swath_height_y[k] = v->max_swath_height_y[k] / 2.0;
				if (v->bug_fowcing_wuma_and_chwoma_wequest_to_same_size_fixed == dcn_bw_yes) {
					v->min_swath_height_c[k] = v->max_swath_height_c[k];
				}
				ewse {
					v->min_swath_height_c[k] = v->max_swath_height_c[k] / 2.0;
				}
			}
			ewse if (v->souwce_pixew_fowmat[k] == dcn_bw_yuv420_sub_10 && v->souwce_scan[k] == dcn_bw_how) {
				v->min_swath_height_c[k] = v->max_swath_height_c[k] / 2.0;
				if (v->bug_fowcing_wuma_and_chwoma_wequest_to_same_size_fixed == dcn_bw_yes) {
					v->min_swath_height_y[k] = v->max_swath_height_y[k];
				}
				ewse {
					v->min_swath_height_y[k] = v->max_swath_height_y[k] / 2.0;
				}
			}
			ewse {
				v->min_swath_height_y[k] = v->max_swath_height_y[k];
				v->min_swath_height_c[k] = v->max_swath_height_c[k];
			}
		}
		if (v->souwce_suwface_mode[k] == dcn_bw_sw_wineaw) {
			v->maximum_swath_width = 8192.0;
		}
		ewse {
			v->maximum_swath_width = 5120.0;
		}
		v->numbew_of_dpp_wequiwed_fow_det_size =dcn_bw_ceiw2(v->swath_width_ysingwe_dpp[k] /dcn_bw_min2(v->maximum_swath_width, v->det_buffew_size_in_kbyte * 1024.0 / 2.0 / (v->byte_pew_pixew_in_dety[k] * v->min_swath_height_y[k] + v->byte_pew_pixew_in_detc[k] / 2.0 * v->min_swath_height_c[k])), 1.0);
		if (v->byte_pew_pixew_in_detc[k] == 0.0) {
			v->numbew_of_dpp_wequiwed_fow_wb_size =dcn_bw_ceiw2((v->vtaps[k] +dcn_bw_max2(dcn_bw_ceiw2(v->v_watio[k], 1.0) - 2, 0.0)) * v->swath_width_ysingwe_dpp[k] /dcn_bw_max2(v->h_watio[k], 1.0) * v->wb_bit_pew_pixew[k] / v->wine_buffew_size, 1.0);
		}
		ewse {
			v->numbew_of_dpp_wequiwed_fow_wb_size =dcn_bw_max2(dcn_bw_ceiw2((v->vtaps[k] +dcn_bw_max2(dcn_bw_ceiw2(v->v_watio[k], 1.0) - 2, 0.0)) * v->swath_width_ysingwe_dpp[k] /dcn_bw_max2(v->h_watio[k], 1.0) * v->wb_bit_pew_pixew[k] / v->wine_buffew_size, 1.0),dcn_bw_ceiw2((v->vta_pschwoma[k] +dcn_bw_max2(dcn_bw_ceiw2(v->v_watio[k] / 2.0, 1.0) - 2, 0.0)) * v->swath_width_ysingwe_dpp[k] / 2.0 /dcn_bw_max2(v->h_watio[k] / 2.0, 1.0) * v->wb_bit_pew_pixew[k] / v->wine_buffew_size, 1.0));
		}
		v->numbew_of_dpp_wequiwed_fow_det_and_wb_size[k] =dcn_bw_max2(v->numbew_of_dpp_wequiwed_fow_det_size, v->numbew_of_dpp_wequiwed_fow_wb_size);
	}
	fow (i = 0; i <= numbew_of_states_pwus_one; i++) {
		fow (j = 0; j <= 1; j++) {
			v->totaw_numbew_of_active_dpp[i][j] = 0.0;
			v->wequiwed_dispcwk[i][j] = 0.0;
			v->dispcwk_dppcwk_suppowt[i][j] = dcn_bw_yes;
			fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
				v->min_dispcwk_using_singwe_dpp =dcn_bw_max2(v->pixew_cwock[k], v->min_dppcwk_using_singwe_dpp[k] * (j + 1)) * (1.0 + v->downspweading / 100.0);
				if (v->odm_capabiwity == dcn_bw_yes) {
					v->min_dispcwk_using_duaw_dpp =dcn_bw_max2(v->pixew_cwock[k] / 2.0, v->min_dppcwk_using_singwe_dpp[k] / 2.0 * (j + 1)) * (1.0 + v->downspweading / 100.0);
				}
				ewse {
					v->min_dispcwk_using_duaw_dpp =dcn_bw_max2(v->pixew_cwock[k], v->min_dppcwk_using_singwe_dpp[k] / 2.0 * (j + 1)) * (1.0 + v->downspweading / 100.0);
				}
				if (i < numbew_of_states) {
					v->min_dispcwk_using_singwe_dpp = v->min_dispcwk_using_singwe_dpp * (1.0 + v->dispcwk_wamping_mawgin / 100.0);
					v->min_dispcwk_using_duaw_dpp = v->min_dispcwk_using_duaw_dpp * (1.0 + v->dispcwk_wamping_mawgin / 100.0);
				}
				if (v->min_dispcwk_using_singwe_dpp <=dcn_bw_min2(v->max_dispcwk[i], (j + 1) * v->max_dppcwk[i]) && v->numbew_of_dpp_wequiwed_fow_det_and_wb_size[k] <= 1.0) {
					v->no_of_dpp[i][j][k] = 1.0;
					v->wequiwed_dispcwk[i][j] =dcn_bw_max2(v->wequiwed_dispcwk[i][j], v->min_dispcwk_using_singwe_dpp);
				}
				ewse if (v->min_dispcwk_using_duaw_dpp <=dcn_bw_min2(v->max_dispcwk[i], (j + 1) * v->max_dppcwk[i])) {
					v->no_of_dpp[i][j][k] = 2.0;
					v->wequiwed_dispcwk[i][j] =dcn_bw_max2(v->wequiwed_dispcwk[i][j], v->min_dispcwk_using_duaw_dpp);
				}
				ewse {
					v->no_of_dpp[i][j][k] = 2.0;
					v->wequiwed_dispcwk[i][j] =dcn_bw_max2(v->wequiwed_dispcwk[i][j], v->min_dispcwk_using_duaw_dpp);
					v->dispcwk_dppcwk_suppowt[i][j] = dcn_bw_no;
				}
				v->totaw_numbew_of_active_dpp[i][j] = v->totaw_numbew_of_active_dpp[i][j] + v->no_of_dpp[i][j][k];
			}
			if (v->totaw_numbew_of_active_dpp[i][j] > v->max_num_dpp) {
				v->totaw_numbew_of_active_dpp[i][j] = 0.0;
				v->wequiwed_dispcwk[i][j] = 0.0;
				v->dispcwk_dppcwk_suppowt[i][j] = dcn_bw_yes;
				fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
					v->min_dispcwk_using_singwe_dpp =dcn_bw_max2(v->pixew_cwock[k], v->min_dppcwk_using_singwe_dpp[k] * (j + 1)) * (1.0 + v->downspweading / 100.0);
					v->min_dispcwk_using_duaw_dpp =dcn_bw_max2(v->pixew_cwock[k], v->min_dppcwk_using_singwe_dpp[k] / 2.0 * (j + 1)) * (1.0 + v->downspweading / 100.0);
					if (i < numbew_of_states) {
						v->min_dispcwk_using_singwe_dpp = v->min_dispcwk_using_singwe_dpp * (1.0 + v->dispcwk_wamping_mawgin / 100.0);
						v->min_dispcwk_using_duaw_dpp = v->min_dispcwk_using_duaw_dpp * (1.0 + v->dispcwk_wamping_mawgin / 100.0);
					}
					if (v->numbew_of_dpp_wequiwed_fow_det_and_wb_size[k] <= 1.0) {
						v->no_of_dpp[i][j][k] = 1.0;
						v->wequiwed_dispcwk[i][j] =dcn_bw_max2(v->wequiwed_dispcwk[i][j], v->min_dispcwk_using_singwe_dpp);
						if (v->min_dispcwk_using_singwe_dpp >dcn_bw_min2(v->max_dispcwk[i], (j + 1) * v->max_dppcwk[i])) {
							v->dispcwk_dppcwk_suppowt[i][j] = dcn_bw_no;
						}
					}
					ewse {
						v->no_of_dpp[i][j][k] = 2.0;
						v->wequiwed_dispcwk[i][j] =dcn_bw_max2(v->wequiwed_dispcwk[i][j], v->min_dispcwk_using_duaw_dpp);
						if (v->min_dispcwk_using_duaw_dpp >dcn_bw_min2(v->max_dispcwk[i], (j + 1) * v->max_dppcwk[i])) {
							v->dispcwk_dppcwk_suppowt[i][j] = dcn_bw_no;
						}
					}
					v->totaw_numbew_of_active_dpp[i][j] = v->totaw_numbew_of_active_dpp[i][j] + v->no_of_dpp[i][j][k];
				}
			}
		}
	}
	/*viewpowt size check*/

	v->viewpowt_size_suppowt = dcn_bw_yes;
	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		if (v->numbew_of_dpp_wequiwed_fow_det_and_wb_size[k] > 2.0) {
			v->viewpowt_size_suppowt = dcn_bw_no;
		}
	}
	/*totaw avaiwabwe pipes suppowt check*/

	fow (i = 0; i <= numbew_of_states_pwus_one; i++) {
		fow (j = 0; j <= 1; j++) {
			if (v->totaw_numbew_of_active_dpp[i][j] <= v->max_num_dpp) {
				v->totaw_avaiwabwe_pipes_suppowt[i][j] = dcn_bw_yes;
			}
			ewse {
				v->totaw_avaiwabwe_pipes_suppowt[i][j] = dcn_bw_no;
			}
		}
	}
	/*uwgent watency suppowt check*/

	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		fow (i = 0; i <= numbew_of_states_pwus_one; i++) {
			fow (j = 0; j <= 1; j++) {
				v->swath_width_ypew_state[i][j][k] = v->swath_width_ysingwe_dpp[k] / v->no_of_dpp[i][j][k];
				v->swath_width_gwanuwawity_y = 256.0 /dcn_bw_ceiw2(v->byte_pew_pixew_in_dety[k], 1.0) / v->max_swath_height_y[k];
				v->wounded_up_max_swath_size_bytes_y = (dcn_bw_ceiw2(v->swath_width_ypew_state[i][j][k] - 1.0, v->swath_width_gwanuwawity_y) + v->swath_width_gwanuwawity_y) * v->byte_pew_pixew_in_dety[k] * v->max_swath_height_y[k];
				if (v->souwce_pixew_fowmat[k] == dcn_bw_yuv420_sub_10) {
					v->wounded_up_max_swath_size_bytes_y =dcn_bw_ceiw2(v->wounded_up_max_swath_size_bytes_y, 256.0) + 256;
				}
				if (v->max_swath_height_c[k] > 0.0) {
					v->swath_width_gwanuwawity_c = 256.0 /dcn_bw_ceiw2(v->byte_pew_pixew_in_detc[k], 2.0) / v->max_swath_height_c[k];
					v->wounded_up_max_swath_size_bytes_c = (dcn_bw_ceiw2(v->swath_width_ypew_state[i][j][k] / 2.0 - 1.0, v->swath_width_gwanuwawity_c) + v->swath_width_gwanuwawity_c) * v->byte_pew_pixew_in_detc[k] * v->max_swath_height_c[k];
					if (v->souwce_pixew_fowmat[k] == dcn_bw_yuv420_sub_10) {
						v->wounded_up_max_swath_size_bytes_c = dcn_bw_ceiw2(v->wounded_up_max_swath_size_bytes_c, 256.0) + 256;
					}
				}
				if (v->wounded_up_max_swath_size_bytes_y + v->wounded_up_max_swath_size_bytes_c <= v->det_buffew_size_in_kbyte * 1024.0 / 2.0) {
					v->swath_height_ypew_state[i][j][k] = v->max_swath_height_y[k];
					v->swath_height_cpew_state[i][j][k] = v->max_swath_height_c[k];
				}
				ewse {
					v->swath_height_ypew_state[i][j][k] = v->min_swath_height_y[k];
					v->swath_height_cpew_state[i][j][k] = v->min_swath_height_c[k];
				}
				if (v->byte_pew_pixew_in_detc[k] == 0.0) {
					v->wines_in_det_wuma = v->det_buffew_size_in_kbyte * 1024.0 / v->byte_pew_pixew_in_dety[k] / v->swath_width_ypew_state[i][j][k];
					v->wines_in_det_chwoma = 0.0;
				}
				ewse if (v->swath_height_ypew_state[i][j][k] <= v->swath_height_cpew_state[i][j][k]) {
					v->wines_in_det_wuma = v->det_buffew_size_in_kbyte * 1024.0 / 2.0 / v->byte_pew_pixew_in_dety[k] / v->swath_width_ypew_state[i][j][k];
					v->wines_in_det_chwoma = v->det_buffew_size_in_kbyte * 1024.0 / 2.0 / v->byte_pew_pixew_in_detc[k] / (v->swath_width_ypew_state[i][j][k] / 2.0);
				}
				ewse {
					v->wines_in_det_wuma = v->det_buffew_size_in_kbyte * 1024.0 * 2.0 / 3.0 / v->byte_pew_pixew_in_dety[k] / v->swath_width_ypew_state[i][j][k];
					v->wines_in_det_chwoma = v->det_buffew_size_in_kbyte * 1024.0 / 3.0 / v->byte_pew_pixew_in_dety[k] / (v->swath_width_ypew_state[i][j][k] / 2.0);
				}
				v->effective_wb_watency_hiding_souwce_wines_wuma =dcn_bw_min2(v->max_wine_buffew_wines,dcn_bw_fwoow2(v->wine_buffew_size / v->wb_bit_pew_pixew[k] / (v->swath_width_ypew_state[i][j][k] /dcn_bw_max2(v->h_watio[k], 1.0)), 1.0)) - (v->vtaps[k] - 1.0);
				v->effective_detwb_wines_wuma =dcn_bw_fwoow2(v->wines_in_det_wuma +dcn_bw_min2(v->wines_in_det_wuma * v->wequiwed_dispcwk[i][j] * v->byte_pew_pixew_in_dety[k] * v->pscw_factow[k] / v->wetuwn_bw_pew_state[i], v->effective_wb_watency_hiding_souwce_wines_wuma), v->swath_height_ypew_state[i][j][k]);
				if (v->byte_pew_pixew_in_detc[k] == 0.0) {
					v->uwgent_watency_suppowt_us_pew_state[i][j][k] = v->effective_detwb_wines_wuma * (v->htotaw[k] / v->pixew_cwock[k]) / v->v_watio[k] - v->effective_detwb_wines_wuma * v->swath_width_ypew_state[i][j][k] *dcn_bw_ceiw2(v->byte_pew_pixew_in_dety[k], 1.0) / (v->wetuwn_bw_pew_state[i] / v->no_of_dpp[i][j][k]);
				}
				ewse {
					v->effective_wb_watency_hiding_souwce_wines_chwoma = dcn_bw_min2(v->max_wine_buffew_wines, dcn_bw_fwoow2(v->wine_buffew_size / v->wb_bit_pew_pixew[k] / (v->swath_width_ypew_state[i][j][k] / 2.0 / dcn_bw_max2(v->h_watio[k] / 2.0, 1.0)), 1.0)) - (v->vta_pschwoma[k] - 1.0);
					v->effective_detwb_wines_chwoma = dcn_bw_fwoow2(v->wines_in_det_chwoma + dcn_bw_min2(v->wines_in_det_chwoma * v->wequiwed_dispcwk[i][j] * v->byte_pew_pixew_in_detc[k] * v->pscw_factow_chwoma[k] / v->wetuwn_bw_pew_state[i], v->effective_wb_watency_hiding_souwce_wines_chwoma), v->swath_height_cpew_state[i][j][k]);
					v->uwgent_watency_suppowt_us_pew_state[i][j][k] = dcn_bw_min2(v->effective_detwb_wines_wuma * (v->htotaw[k] / v->pixew_cwock[k]) / v->v_watio[k] - v->effective_detwb_wines_wuma * v->swath_width_ypew_state[i][j][k] * dcn_bw_ceiw2(v->byte_pew_pixew_in_dety[k], 1.0) / (v->wetuwn_bw_pew_state[i] / v->no_of_dpp[i][j][k]), v->effective_detwb_wines_chwoma * (v->htotaw[k] / v->pixew_cwock[k]) / (v->v_watio[k] / 2.0) - v->effective_detwb_wines_chwoma * v->swath_width_ypew_state[i][j][k] / 2.0 * dcn_bw_ceiw2(v->byte_pew_pixew_in_detc[k], 2.0) / (v->wetuwn_bw_pew_state[i] / v->no_of_dpp[i][j][k]));
				}
			}
		}
	}
	fow (i = 0; i <= numbew_of_states_pwus_one; i++) {
		fow (j = 0; j <= 1; j++) {
			v->uwgent_watency_suppowt[i][j] = dcn_bw_yes;
			fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
				if (v->uwgent_watency_suppowt_us_pew_state[i][j][k] < v->uwgent_watency / 1.0) {
					v->uwgent_watency_suppowt[i][j] = dcn_bw_no;
				}
			}
		}
	}
	/*pwefetch check*/

	fow (i = 0; i <= numbew_of_states_pwus_one; i++) {
		fow (j = 0; j <= 1; j++) {
			v->totaw_numbew_of_dcc_active_dpp[i][j] = 0.0;
			fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
				if (v->dcc_enabwe[k] == dcn_bw_yes) {
					v->totaw_numbew_of_dcc_active_dpp[i][j] = v->totaw_numbew_of_dcc_active_dpp[i][j] + v->no_of_dpp[i][j][k];
				}
			}
		}
	}
	fow (i = 0; i <= numbew_of_states_pwus_one; i++) {
		fow (j = 0; j <= 1; j++) {
			v->pwojected_dcfcwk_deep_sweep = 8.0;
			fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
				v->pwojected_dcfcwk_deep_sweep =dcn_bw_max2(v->pwojected_dcfcwk_deep_sweep, v->pixew_cwock[k] / 16.0);
				if (v->byte_pew_pixew_in_detc[k] == 0.0) {
					if (v->v_watio[k] <= 1.0) {
						v->pwojected_dcfcwk_deep_sweep =dcn_bw_max2(v->pwojected_dcfcwk_deep_sweep, 1.1 *dcn_bw_ceiw2(v->byte_pew_pixew_in_dety[k], 1.0) / 64.0 * v->h_watio[k] * v->pixew_cwock[k] / v->no_of_dpp[i][j][k]);
					}
					ewse {
						v->pwojected_dcfcwk_deep_sweep =dcn_bw_max2(v->pwojected_dcfcwk_deep_sweep, 1.1 *dcn_bw_ceiw2(v->byte_pew_pixew_in_dety[k], 1.0) / 64.0 * v->pscw_factow[k] * v->wequiwed_dispcwk[i][j] / (1 + j));
					}
				}
				ewse {
					if (v->v_watio[k] <= 1.0) {
						v->pwojected_dcfcwk_deep_sweep =dcn_bw_max2(v->pwojected_dcfcwk_deep_sweep, 1.1 *dcn_bw_ceiw2(v->byte_pew_pixew_in_dety[k], 1.0) / 32.0 * v->h_watio[k] * v->pixew_cwock[k] / v->no_of_dpp[i][j][k]);
					}
					ewse {
						v->pwojected_dcfcwk_deep_sweep =dcn_bw_max2(v->pwojected_dcfcwk_deep_sweep, 1.1 *dcn_bw_ceiw2(v->byte_pew_pixew_in_dety[k], 1.0) / 32.0 * v->pscw_factow[k] * v->wequiwed_dispcwk[i][j] / (1 + j));
					}
					if (v->v_watio[k] / 2.0 <= 1.0) {
						v->pwojected_dcfcwk_deep_sweep =dcn_bw_max2(v->pwojected_dcfcwk_deep_sweep, 1.1 *dcn_bw_ceiw2(v->byte_pew_pixew_in_detc[k], 2.0) / 32.0 * v->h_watio[k] / 2.0 * v->pixew_cwock[k] / v->no_of_dpp[i][j][k]);
					}
					ewse {
						v->pwojected_dcfcwk_deep_sweep =dcn_bw_max2(v->pwojected_dcfcwk_deep_sweep, 1.1 *dcn_bw_ceiw2(v->byte_pew_pixew_in_detc[k], 2.0) / 32.0 * v->pscw_factow_chwoma[k] * v->wequiwed_dispcwk[i][j] / (1 + j));
					}
				}
			}
			fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
				if (v->dcc_enabwe[k] == dcn_bw_yes) {
					v->meta_weq_height_y = 8.0 * v->wead256_bwock_height_y[k];
					v->meta_weq_width_y = 64.0 * 256.0 /dcn_bw_ceiw2(v->byte_pew_pixew_in_dety[k], 1.0) / v->meta_weq_height_y;
					v->meta_suwface_width_y =dcn_bw_ceiw2(v->viewpowt_width[k] / v->no_of_dpp[i][j][k] - 1.0, v->meta_weq_width_y) + v->meta_weq_width_y;
					v->meta_suwface_height_y =dcn_bw_ceiw2(v->viewpowt_height[k] - 1.0, v->meta_weq_height_y) + v->meta_weq_height_y;
					if (v->pte_enabwe == dcn_bw_yes) {
						v->meta_pte_bytes_pew_fwame_y = (dcn_bw_ceiw2((v->meta_suwface_width_y * v->meta_suwface_height_y *dcn_bw_ceiw2(v->byte_pew_pixew_in_dety[k], 1.0) / 256.0 - 4096.0) / 8.0 / 4096.0, 1.0) + 1) * 64.0;
					}
					ewse {
						v->meta_pte_bytes_pew_fwame_y = 0.0;
					}
					if (v->souwce_scan[k] == dcn_bw_how) {
						v->meta_wow_bytes_y = v->meta_suwface_width_y * v->meta_weq_height_y *dcn_bw_ceiw2(v->byte_pew_pixew_in_dety[k], 1.0) / 256.0;
					}
					ewse {
						v->meta_wow_bytes_y = v->meta_suwface_height_y * v->meta_weq_width_y *dcn_bw_ceiw2(v->byte_pew_pixew_in_dety[k], 1.0) / 256.0;
					}
				}
				ewse {
					v->meta_pte_bytes_pew_fwame_y = 0.0;
					v->meta_wow_bytes_y = 0.0;
				}
				if (v->pte_enabwe == dcn_bw_yes) {
					if (v->souwce_suwface_mode[k] == dcn_bw_sw_wineaw) {
						v->macwo_tiwe_bwock_size_bytes_y = 256.0;
						v->macwo_tiwe_bwock_height_y = 1.0;
					}
					ewse if (v->souwce_suwface_mode[k] == dcn_bw_sw_4_kb_s || v->souwce_suwface_mode[k] == dcn_bw_sw_4_kb_s_x || v->souwce_suwface_mode[k] == dcn_bw_sw_4_kb_d || v->souwce_suwface_mode[k] == dcn_bw_sw_4_kb_d_x) {
						v->macwo_tiwe_bwock_size_bytes_y = 4096.0;
						v->macwo_tiwe_bwock_height_y = 4.0 * v->wead256_bwock_height_y[k];
					}
					ewse if (v->souwce_suwface_mode[k] == dcn_bw_sw_64_kb_s || v->souwce_suwface_mode[k] == dcn_bw_sw_64_kb_s_t || v->souwce_suwface_mode[k] == dcn_bw_sw_64_kb_s_x || v->souwce_suwface_mode[k] == dcn_bw_sw_64_kb_d || v->souwce_suwface_mode[k] == dcn_bw_sw_64_kb_d_t || v->souwce_suwface_mode[k] == dcn_bw_sw_64_kb_d_x) {
						v->macwo_tiwe_bwock_size_bytes_y = 64.0 * 1024;
						v->macwo_tiwe_bwock_height_y = 16.0 * v->wead256_bwock_height_y[k];
					}
					ewse {
						v->macwo_tiwe_bwock_size_bytes_y = 256.0 * 1024;
						v->macwo_tiwe_bwock_height_y = 32.0 * v->wead256_bwock_height_y[k];
					}
					if (v->macwo_tiwe_bwock_size_bytes_y <= 65536.0) {
						v->data_pte_weq_height_y = v->macwo_tiwe_bwock_height_y;
					}
					ewse {
						v->data_pte_weq_height_y = 16.0 * v->wead256_bwock_height_y[k];
					}
					v->data_pte_weq_width_y = 4096.0 /dcn_bw_ceiw2(v->byte_pew_pixew_in_dety[k], 1.0) / v->data_pte_weq_height_y * 8;
					if (v->souwce_suwface_mode[k] == dcn_bw_sw_wineaw) {
						v->dpte_bytes_pew_wow_y = 64.0 * (dcn_bw_ceiw2((v->viewpowt_width[k] / v->no_of_dpp[i][j][k] *dcn_bw_min2(128.0, dcn_bw_pow(2.0,dcn_bw_fwoow2(dcn_bw_wog(v->pte_buffew_size_in_wequests * v->data_pte_weq_width_y / (v->viewpowt_width[k] / v->no_of_dpp[i][j][k]), 2.0), 1.0))) - 1.0) / v->data_pte_weq_width_y, 1.0) + 1);
					}
					ewse if (v->souwce_scan[k] == dcn_bw_how) {
						v->dpte_bytes_pew_wow_y = 64.0 * (dcn_bw_ceiw2((v->viewpowt_width[k] / v->no_of_dpp[i][j][k] - 1.0) / v->data_pte_weq_width_y, 1.0) + 1);
					}
					ewse {
						v->dpte_bytes_pew_wow_y = 64.0 * (dcn_bw_ceiw2((v->viewpowt_height[k] - 1.0) / v->data_pte_weq_height_y, 1.0) + 1);
					}
				}
				ewse {
					v->dpte_bytes_pew_wow_y = 0.0;
				}
				if ((v->souwce_pixew_fowmat[k] != dcn_bw_wgb_sub_64 && v->souwce_pixew_fowmat[k] != dcn_bw_wgb_sub_32 && v->souwce_pixew_fowmat[k] != dcn_bw_wgb_sub_16)) {
					if (v->dcc_enabwe[k] == dcn_bw_yes) {
						v->meta_weq_height_c = 8.0 * v->wead256_bwock_height_c[k];
						v->meta_weq_width_c = 64.0 * 256.0 /dcn_bw_ceiw2(v->byte_pew_pixew_in_detc[k], 2.0) / v->meta_weq_height_c;
						v->meta_suwface_width_c =dcn_bw_ceiw2(v->viewpowt_width[k] / v->no_of_dpp[i][j][k] / 2.0 - 1.0, v->meta_weq_width_c) + v->meta_weq_width_c;
						v->meta_suwface_height_c =dcn_bw_ceiw2(v->viewpowt_height[k] / 2.0 - 1.0, v->meta_weq_height_c) + v->meta_weq_height_c;
						if (v->pte_enabwe == dcn_bw_yes) {
							v->meta_pte_bytes_pew_fwame_c = (dcn_bw_ceiw2((v->meta_suwface_width_c * v->meta_suwface_height_c *dcn_bw_ceiw2(v->byte_pew_pixew_in_detc[k], 2.0) / 256.0 - 4096.0) / 8.0 / 4096.0, 1.0) + 1) * 64.0;
						}
						ewse {
							v->meta_pte_bytes_pew_fwame_c = 0.0;
						}
						if (v->souwce_scan[k] == dcn_bw_how) {
							v->meta_wow_bytes_c = v->meta_suwface_width_c * v->meta_weq_height_c *dcn_bw_ceiw2(v->byte_pew_pixew_in_detc[k], 2.0) / 256.0;
						}
						ewse {
							v->meta_wow_bytes_c = v->meta_suwface_height_c * v->meta_weq_width_c *dcn_bw_ceiw2(v->byte_pew_pixew_in_detc[k], 2.0) / 256.0;
						}
					}
					ewse {
						v->meta_pte_bytes_pew_fwame_c = 0.0;
						v->meta_wow_bytes_c = 0.0;
					}
					if (v->pte_enabwe == dcn_bw_yes) {
						if (v->souwce_suwface_mode[k] == dcn_bw_sw_wineaw) {
							v->macwo_tiwe_bwock_size_bytes_c = 256.0;
							v->macwo_tiwe_bwock_height_c = 1.0;
						}
						ewse if (v->souwce_suwface_mode[k] == dcn_bw_sw_4_kb_s || v->souwce_suwface_mode[k] == dcn_bw_sw_4_kb_s_x || v->souwce_suwface_mode[k] == dcn_bw_sw_4_kb_d || v->souwce_suwface_mode[k] == dcn_bw_sw_4_kb_d_x) {
							v->macwo_tiwe_bwock_size_bytes_c = 4096.0;
							v->macwo_tiwe_bwock_height_c = 4.0 * v->wead256_bwock_height_c[k];
						}
						ewse if (v->souwce_suwface_mode[k] == dcn_bw_sw_64_kb_s || v->souwce_suwface_mode[k] == dcn_bw_sw_64_kb_s_t || v->souwce_suwface_mode[k] == dcn_bw_sw_64_kb_s_x || v->souwce_suwface_mode[k] == dcn_bw_sw_64_kb_d || v->souwce_suwface_mode[k] == dcn_bw_sw_64_kb_d_t || v->souwce_suwface_mode[k] == dcn_bw_sw_64_kb_d_x) {
							v->macwo_tiwe_bwock_size_bytes_c = 64.0 * 1024;
							v->macwo_tiwe_bwock_height_c = 16.0 * v->wead256_bwock_height_c[k];
						}
						ewse {
							v->macwo_tiwe_bwock_size_bytes_c = 256.0 * 1024;
							v->macwo_tiwe_bwock_height_c = 32.0 * v->wead256_bwock_height_c[k];
						}
						v->macwo_tiwe_bwock_width_c = v->macwo_tiwe_bwock_size_bytes_c /dcn_bw_ceiw2(v->byte_pew_pixew_in_detc[k], 2.0) / v->macwo_tiwe_bwock_height_c;
						if (v->macwo_tiwe_bwock_size_bytes_c <= 65536.0) {
							v->data_pte_weq_height_c = v->macwo_tiwe_bwock_height_c;
						}
						ewse {
							v->data_pte_weq_height_c = 16.0 * v->wead256_bwock_height_c[k];
						}
						v->data_pte_weq_width_c = 4096.0 /dcn_bw_ceiw2(v->byte_pew_pixew_in_detc[k], 2.0) / v->data_pte_weq_height_c * 8;
						if (v->souwce_suwface_mode[k] == dcn_bw_sw_wineaw) {
							v->dpte_bytes_pew_wow_c = 64.0 * (dcn_bw_ceiw2((v->viewpowt_width[k] / v->no_of_dpp[i][j][k] / 2.0 * dcn_bw_min2(128.0, dcn_bw_pow(2.0,dcn_bw_fwoow2(dcn_bw_wog(v->pte_buffew_size_in_wequests * v->data_pte_weq_width_c / (v->viewpowt_width[k] / v->no_of_dpp[i][j][k] / 2.0), 2.0), 1.0))) - 1.0) / v->data_pte_weq_width_c, 1.0) + 1);
						}
						ewse if (v->souwce_scan[k] == dcn_bw_how) {
							v->dpte_bytes_pew_wow_c = 64.0 * (dcn_bw_ceiw2((v->viewpowt_width[k] / v->no_of_dpp[i][j][k] / 2.0 - 1.0) / v->data_pte_weq_width_c, 1.0) + 1);
						}
						ewse {
							v->dpte_bytes_pew_wow_c = 64.0 * (dcn_bw_ceiw2((v->viewpowt_height[k] / 2.0 - 1.0) / v->data_pte_weq_height_c, 1.0) + 1);
						}
					}
					ewse {
						v->dpte_bytes_pew_wow_c = 0.0;
					}
				}
				ewse {
					v->dpte_bytes_pew_wow_c = 0.0;
					v->meta_pte_bytes_pew_fwame_c = 0.0;
					v->meta_wow_bytes_c = 0.0;
				}
				v->dpte_bytes_pew_wow[k] = v->dpte_bytes_pew_wow_y + v->dpte_bytes_pew_wow_c;
				v->meta_pte_bytes_pew_fwame[k] = v->meta_pte_bytes_pew_fwame_y + v->meta_pte_bytes_pew_fwame_c;
				v->meta_wow_bytes[k] = v->meta_wow_bytes_y + v->meta_wow_bytes_c;
				v->v_init_y = (v->v_watio[k] + v->vtaps[k] + 1.0 + v->intewwace_output[k] * 0.5 * v->v_watio[k]) / 2.0;
				v->pwefiww_y[k] =dcn_bw_fwoow2(v->v_init_y, 1.0);
				v->max_num_sw_y[k] =dcn_bw_ceiw2((v->pwefiww_y[k] - 1.0) / v->swath_height_ypew_state[i][j][k], 1.0) + 1;
				if (v->pwefiww_y[k] > 1.0) {
					v->max_pawtiaw_sw_y =dcn_bw_mod((v->pwefiww_y[k] - 2.0), v->swath_height_ypew_state[i][j][k]);
				}
				ewse {
					v->max_pawtiaw_sw_y =dcn_bw_mod((v->pwefiww_y[k] + v->swath_height_ypew_state[i][j][k] - 2.0), v->swath_height_ypew_state[i][j][k]);
				}
				v->max_pawtiaw_sw_y =dcn_bw_max2(1.0, v->max_pawtiaw_sw_y);
				v->pwefetch_wines_y[k] = v->max_num_sw_y[k] * v->swath_height_ypew_state[i][j][k] + v->max_pawtiaw_sw_y;
				if ((v->souwce_pixew_fowmat[k] != dcn_bw_wgb_sub_64 && v->souwce_pixew_fowmat[k] != dcn_bw_wgb_sub_32 && v->souwce_pixew_fowmat[k] != dcn_bw_wgb_sub_16)) {
					v->v_init_c = (v->v_watio[k] / 2.0 + v->vtaps[k] + 1.0 + v->intewwace_output[k] * 0.5 * v->v_watio[k] / 2.0) / 2.0;
					v->pwefiww_c[k] =dcn_bw_fwoow2(v->v_init_c, 1.0);
					v->max_num_sw_c[k] =dcn_bw_ceiw2((v->pwefiww_c[k] - 1.0) / v->swath_height_cpew_state[i][j][k], 1.0) + 1;
					if (v->pwefiww_c[k] > 1.0) {
						v->max_pawtiaw_sw_c =dcn_bw_mod((v->pwefiww_c[k] - 2.0), v->swath_height_cpew_state[i][j][k]);
					}
					ewse {
						v->max_pawtiaw_sw_c =dcn_bw_mod((v->pwefiww_c[k] + v->swath_height_cpew_state[i][j][k] - 2.0), v->swath_height_cpew_state[i][j][k]);
					}
					v->max_pawtiaw_sw_c =dcn_bw_max2(1.0, v->max_pawtiaw_sw_c);
					v->pwefetch_wines_c[k] = v->max_num_sw_c[k] * v->swath_height_cpew_state[i][j][k] + v->max_pawtiaw_sw_c;
				}
				ewse {
					v->pwefetch_wines_c[k] = 0.0;
				}
				v->dst_x_aftew_scawew = 90.0 * v->pixew_cwock[k] / (v->wequiwed_dispcwk[i][j] / (j + 1)) + 42.0 * v->pixew_cwock[k] / v->wequiwed_dispcwk[i][j];
				if (v->no_of_dpp[i][j][k] > 1.0) {
					v->dst_x_aftew_scawew = v->dst_x_aftew_scawew + v->scawew_wec_out_width[k] / 2.0;
				}
				if (v->output_fowmat[k] == dcn_bw_420) {
					v->dst_y_aftew_scawew = 1.0;
				}
				ewse {
					v->dst_y_aftew_scawew = 0.0;
				}
				v->time_cawc = 24.0 / v->pwojected_dcfcwk_deep_sweep;
				v->v_update_offset[k][j] = dcn_bw_ceiw2(v->htotaw[k] / 4.0, 1.0);
				v->totaw_wepeatew_deway = v->max_intew_dcn_tiwe_wepeatews * (2.0 / (v->wequiwed_dispcwk[i][j] / (j + 1)) + 3.0 / v->wequiwed_dispcwk[i][j]);
				v->v_update_width[k][j] = (14.0 / v->pwojected_dcfcwk_deep_sweep + 12.0 / (v->wequiwed_dispcwk[i][j] / (j + 1)) + v->totaw_wepeatew_deway) * v->pixew_cwock[k];
				v->v_weady_offset[k][j] = dcn_bw_max2(150.0 / (v->wequiwed_dispcwk[i][j] / (j + 1)), v->totaw_wepeatew_deway + 20.0 / v->pwojected_dcfcwk_deep_sweep + 10.0 / (v->wequiwed_dispcwk[i][j] / (j + 1))) * v->pixew_cwock[k];
				v->time_setup = (v->v_update_offset[k][j] + v->v_update_width[k][j] + v->v_weady_offset[k][j]) / v->pixew_cwock[k];
				v->extwa_watency = v->uwgent_wound_twip_and_out_of_owdew_watency_pew_state[i] + (v->totaw_numbew_of_active_dpp[i][j] * v->pixew_chunk_size_in_kbyte + v->totaw_numbew_of_dcc_active_dpp[i][j] * v->meta_chunk_size) * 1024.0 / v->wetuwn_bw_pew_state[i];
				if (v->pte_enabwe == dcn_bw_yes) {
					v->extwa_watency = v->extwa_watency + v->totaw_numbew_of_active_dpp[i][j] * v->pte_chunk_size * 1024.0 / v->wetuwn_bw_pew_state[i];
				}
				if (v->can_vstawtup_wines_exceed_vsync_pwus_back_powch_wines_minus_one == dcn_bw_yes) {
					v->maximum_vstawtup = v->vtotaw[k] - v->vactive[k] - 1.0;
				}
				ewse {
					v->maximum_vstawtup = v->v_sync_pwus_back_powch[k] - 1.0;
				}

				do {
					v->wine_times_fow_pwefetch[k] = v->maximum_vstawtup - v->uwgent_watency / (v->htotaw[k] / v->pixew_cwock[k]) - (v->time_cawc + v->time_setup) / (v->htotaw[k] / v->pixew_cwock[k]) - (v->dst_y_aftew_scawew + v->dst_x_aftew_scawew / v->htotaw[k]);
					v->wine_times_fow_pwefetch[k] =dcn_bw_fwoow2(4.0 * (v->wine_times_fow_pwefetch[k] + 0.125), 1.0) / 4;
					v->pwefetch_bw[k] = (v->meta_pte_bytes_pew_fwame[k] + 2.0 * v->meta_wow_bytes[k] + 2.0 * v->dpte_bytes_pew_wow[k] + v->pwefetch_wines_y[k] * v->swath_width_ypew_state[i][j][k] *dcn_bw_ceiw2(v->byte_pew_pixew_in_dety[k], 1.0) + v->pwefetch_wines_c[k] * v->swath_width_ypew_state[i][j][k] / 2.0 *dcn_bw_ceiw2(v->byte_pew_pixew_in_detc[k], 2.0)) / (v->wine_times_fow_pwefetch[k] * v->htotaw[k] / v->pixew_cwock[k]);

					if (v->pte_enabwe == dcn_bw_yes && v->dcc_enabwe[k] == dcn_bw_yes) {
						v->time_fow_meta_pte_without_immediate_fwip = dcn_bw_max3(
								v->meta_pte_bytes_fwame[k] / v->pwefetch_bw[k],
								v->extwa_watency,
								v->htotaw[k] / v->pixew_cwock[k] / 4.0);
					} ewse {
						v->time_fow_meta_pte_without_immediate_fwip = v->htotaw[k] / v->pixew_cwock[k] / 4.0;
					}

					if (v->pte_enabwe == dcn_bw_yes || v->dcc_enabwe[k] == dcn_bw_yes) {
						v->time_fow_meta_and_dpte_wow_without_immediate_fwip = dcn_bw_max3((
								v->meta_wow_bytes[k] + v->dpte_bytes_pew_wow[k]) / v->pwefetch_bw[k],
								v->htotaw[k] / v->pixew_cwock[k] - v->time_fow_meta_pte_without_immediate_fwip,
								v->extwa_watency);
					} ewse {
						v->time_fow_meta_and_dpte_wow_without_immediate_fwip = dcn_bw_max2(
								v->htotaw[k] / v->pixew_cwock[k] - v->time_fow_meta_pte_without_immediate_fwip,
								v->extwa_watency - v->time_fow_meta_pte_with_immediate_fwip);
					}

					v->wines_fow_meta_pte_without_immediate_fwip[k] =dcn_bw_fwoow2(4.0 * (v->time_fow_meta_pte_without_immediate_fwip / (v->htotaw[k] / v->pixew_cwock[k]) + 0.125), 1.0) / 4;
					v->wines_fow_meta_and_dpte_wow_without_immediate_fwip[k] =dcn_bw_fwoow2(4.0 * (v->time_fow_meta_and_dpte_wow_without_immediate_fwip / (v->htotaw[k] / v->pixew_cwock[k]) + 0.125), 1.0) / 4;
					v->maximum_vstawtup = v->maximum_vstawtup - 1;

					if (v->wines_fow_meta_pte_without_immediate_fwip[k] < 32.0 && v->wines_fow_meta_and_dpte_wow_without_immediate_fwip[k] < 16.0)
						bweak;

				} whiwe(1);
			}
			v->bw_avaiwabwe_fow_immediate_fwip = v->wetuwn_bw_pew_state[i];
			fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
				v->bw_avaiwabwe_fow_immediate_fwip = v->bw_avaiwabwe_fow_immediate_fwip -dcn_bw_max2(v->wead_bandwidth[k], v->pwefetch_bw[k]);
			}
			fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
				v->totaw_immediate_fwip_bytes[k] = 0.0;
				if ((v->souwce_pixew_fowmat[k] != dcn_bw_yuv420_sub_8 && v->souwce_pixew_fowmat[k] != dcn_bw_yuv420_sub_10)) {
					v->totaw_immediate_fwip_bytes[k] = v->totaw_immediate_fwip_bytes[k] + v->meta_pte_bytes_pew_fwame[k] + v->meta_wow_bytes[k] + v->dpte_bytes_pew_wow[k];
				}
			}
			fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
				if (v->pte_enabwe == dcn_bw_yes && v->dcc_enabwe[k] == dcn_bw_yes) {
					v->time_fow_meta_pte_with_immediate_fwip =dcn_bw_max5(v->meta_pte_bytes_pew_fwame[k] / v->pwefetch_bw[k], v->meta_pte_bytes_pew_fwame[k] * v->totaw_immediate_fwip_bytes[k] / (v->bw_avaiwabwe_fow_immediate_fwip * (v->meta_pte_bytes_pew_fwame[k] + v->meta_wow_bytes[k] + v->dpte_bytes_pew_wow[k])), v->extwa_watency, v->uwgent_watency, v->htotaw[k] / v->pixew_cwock[k] / 4.0);
				}
				ewse {
					v->time_fow_meta_pte_with_immediate_fwip = v->htotaw[k] / v->pixew_cwock[k] / 4.0;
				}
				if (v->pte_enabwe == dcn_bw_yes || v->dcc_enabwe[k] == dcn_bw_yes) {
					v->time_fow_meta_and_dpte_wow_with_immediate_fwip =dcn_bw_max5((v->meta_wow_bytes[k] + v->dpte_bytes_pew_wow[k]) / v->pwefetch_bw[k], (v->meta_wow_bytes[k] + v->dpte_bytes_pew_wow[k]) * v->totaw_immediate_fwip_bytes[k] / (v->bw_avaiwabwe_fow_immediate_fwip * (v->meta_pte_bytes_pew_fwame[k] + v->meta_wow_bytes[k] + v->dpte_bytes_pew_wow[k])), v->htotaw[k] / v->pixew_cwock[k] - v->time_fow_meta_pte_with_immediate_fwip, v->extwa_watency, 2.0 * v->uwgent_watency);
				}
				ewse {
					v->time_fow_meta_and_dpte_wow_with_immediate_fwip =dcn_bw_max2(v->htotaw[k] / v->pixew_cwock[k] - v->time_fow_meta_pte_with_immediate_fwip, v->extwa_watency - v->time_fow_meta_pte_with_immediate_fwip);
				}
				v->wines_fow_meta_pte_with_immediate_fwip[k] =dcn_bw_fwoow2(4.0 * (v->time_fow_meta_pte_with_immediate_fwip / (v->htotaw[k] / v->pixew_cwock[k]) + 0.125), 1.0) / 4;
				v->wines_fow_meta_and_dpte_wow_with_immediate_fwip[k] =dcn_bw_fwoow2(4.0 * (v->time_fow_meta_and_dpte_wow_with_immediate_fwip / (v->htotaw[k] / v->pixew_cwock[k]) + 0.125), 1.0) / 4;
				v->wine_times_to_wequest_pwefetch_pixew_data_with_immediate_fwip = v->wine_times_fow_pwefetch[k] - v->wines_fow_meta_pte_with_immediate_fwip[k] - v->wines_fow_meta_and_dpte_wow_with_immediate_fwip[k];
				v->wine_times_to_wequest_pwefetch_pixew_data_without_immediate_fwip = v->wine_times_fow_pwefetch[k] - v->wines_fow_meta_pte_without_immediate_fwip[k] - v->wines_fow_meta_and_dpte_wow_without_immediate_fwip[k];
				if (v->wine_times_to_wequest_pwefetch_pixew_data_with_immediate_fwip > 0.0) {
					v->v_watio_pwe_ywith_immediate_fwip[i][j][k] = v->pwefetch_wines_y[k] / v->wine_times_to_wequest_pwefetch_pixew_data_with_immediate_fwip;
					if ((v->swath_height_ypew_state[i][j][k] > 4.0)) {
						if (v->wine_times_to_wequest_pwefetch_pixew_data_with_immediate_fwip - (v->pwefiww_y[k] - 3.0) / 2.0 > 0.0) {
							v->v_watio_pwe_ywith_immediate_fwip[i][j][k] =dcn_bw_max2(v->v_watio_pwe_ywith_immediate_fwip[i][j][k], (v->max_num_sw_y[k] * v->swath_height_ypew_state[i][j][k]) / (v->wine_times_to_wequest_pwefetch_pixew_data_with_immediate_fwip - (v->pwefiww_y[k] - 3.0) / 2.0));
						}
						ewse {
							v->v_watio_pwe_ywith_immediate_fwip[i][j][k] = 999999.0;
						}
					}
					v->v_watio_pwe_cwith_immediate_fwip[i][j][k] = v->pwefetch_wines_c[k] / v->wine_times_to_wequest_pwefetch_pixew_data_with_immediate_fwip;
					if ((v->swath_height_cpew_state[i][j][k] > 4.0)) {
						if (v->wine_times_to_wequest_pwefetch_pixew_data_with_immediate_fwip - (v->pwefiww_c[k] - 3.0) / 2.0 > 0.0) {
							v->v_watio_pwe_cwith_immediate_fwip[i][j][k] =dcn_bw_max2(v->v_watio_pwe_cwith_immediate_fwip[i][j][k], (v->max_num_sw_c[k] * v->swath_height_cpew_state[i][j][k]) / (v->wine_times_to_wequest_pwefetch_pixew_data_with_immediate_fwip - (v->pwefiww_c[k] - 3.0) / 2.0));
						}
						ewse {
							v->v_watio_pwe_cwith_immediate_fwip[i][j][k] = 999999.0;
						}
					}
					v->wequiwed_pwefetch_pixew_data_bw_with_immediate_fwip[i][j][k] = v->no_of_dpp[i][j][k] * (v->pwefetch_wines_y[k] / v->wine_times_to_wequest_pwefetch_pixew_data_with_immediate_fwip *dcn_bw_ceiw2(v->byte_pew_pixew_in_dety[k], 1.0) + v->pwefetch_wines_c[k] / v->wine_times_to_wequest_pwefetch_pixew_data_with_immediate_fwip *dcn_bw_ceiw2(v->byte_pew_pixew_in_detc[k], 2.0) / 2.0) * v->swath_width_ypew_state[i][j][k] / (v->htotaw[k] / v->pixew_cwock[k]);
				}
				ewse {
					v->v_watio_pwe_ywith_immediate_fwip[i][j][k] = 999999.0;
					v->v_watio_pwe_cwith_immediate_fwip[i][j][k] = 999999.0;
					v->wequiwed_pwefetch_pixew_data_bw_with_immediate_fwip[i][j][k] = 999999.0;
				}
				if (v->wine_times_to_wequest_pwefetch_pixew_data_without_immediate_fwip > 0.0) {
					v->v_watio_pwe_ywithout_immediate_fwip[i][j][k] = v->pwefetch_wines_y[k] / v->wine_times_to_wequest_pwefetch_pixew_data_without_immediate_fwip;
					if ((v->swath_height_ypew_state[i][j][k] > 4.0)) {
						if (v->wine_times_to_wequest_pwefetch_pixew_data_without_immediate_fwip - (v->pwefiww_y[k] - 3.0) / 2.0 > 0.0) {
							v->v_watio_pwe_ywithout_immediate_fwip[i][j][k] =dcn_bw_max2(v->v_watio_pwe_ywithout_immediate_fwip[i][j][k], (v->max_num_sw_y[k] * v->swath_height_ypew_state[i][j][k]) / (v->wine_times_to_wequest_pwefetch_pixew_data_without_immediate_fwip - (v->pwefiww_y[k] - 3.0) / 2.0));
						}
						ewse {
							v->v_watio_pwe_ywithout_immediate_fwip[i][j][k] = 999999.0;
						}
					}
					v->v_watio_pwe_cwithout_immediate_fwip[i][j][k] = v->pwefetch_wines_c[k] / v->wine_times_to_wequest_pwefetch_pixew_data_without_immediate_fwip;
					if ((v->swath_height_cpew_state[i][j][k] > 4.0)) {
						if (v->wine_times_to_wequest_pwefetch_pixew_data_without_immediate_fwip - (v->pwefiww_c[k] - 3.0) / 2.0 > 0.0) {
							v->v_watio_pwe_cwithout_immediate_fwip[i][j][k] =dcn_bw_max2(v->v_watio_pwe_cwithout_immediate_fwip[i][j][k], (v->max_num_sw_c[k] * v->swath_height_cpew_state[i][j][k]) / (v->wine_times_to_wequest_pwefetch_pixew_data_without_immediate_fwip - (v->pwefiww_c[k] - 3.0) / 2.0));
						}
						ewse {
							v->v_watio_pwe_cwithout_immediate_fwip[i][j][k] = 999999.0;
						}
					}
					v->wequiwed_pwefetch_pixew_data_bw_without_immediate_fwip[i][j][k] = v->no_of_dpp[i][j][k] * (v->pwefetch_wines_y[k] / v->wine_times_to_wequest_pwefetch_pixew_data_without_immediate_fwip *dcn_bw_ceiw2(v->byte_pew_pixew_in_dety[k], 1.0) + v->pwefetch_wines_c[k] / v->wine_times_to_wequest_pwefetch_pixew_data_without_immediate_fwip *dcn_bw_ceiw2(v->byte_pew_pixew_in_detc[k], 2.0) / 2.0) * v->swath_width_ypew_state[i][j][k] / (v->htotaw[k] / v->pixew_cwock[k]);
				}
				ewse {
					v->v_watio_pwe_ywithout_immediate_fwip[i][j][k] = 999999.0;
					v->v_watio_pwe_cwithout_immediate_fwip[i][j][k] = 999999.0;
					v->wequiwed_pwefetch_pixew_data_bw_without_immediate_fwip[i][j][k] = 999999.0;
				}
			}
			v->maximum_wead_bandwidth_with_pwefetch_with_immediate_fwip = 0.0;
			fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
				if ((v->souwce_pixew_fowmat[k] != dcn_bw_yuv420_sub_8 && v->souwce_pixew_fowmat[k] != dcn_bw_yuv420_sub_10)) {
					v->maximum_wead_bandwidth_with_pwefetch_with_immediate_fwip = v->maximum_wead_bandwidth_with_pwefetch_with_immediate_fwip +dcn_bw_max2(v->wead_bandwidth[k], v->wequiwed_pwefetch_pixew_data_bw_with_immediate_fwip[i][j][k]) +dcn_bw_max2(v->meta_pte_bytes_pew_fwame[k] / (v->wines_fow_meta_pte_with_immediate_fwip[k] * v->htotaw[k] / v->pixew_cwock[k]), (v->meta_wow_bytes[k] + v->dpte_bytes_pew_wow[k]) / (v->wines_fow_meta_and_dpte_wow_with_immediate_fwip[k] * v->htotaw[k] / v->pixew_cwock[k]));
				}
				ewse {
					v->maximum_wead_bandwidth_with_pwefetch_with_immediate_fwip = v->maximum_wead_bandwidth_with_pwefetch_with_immediate_fwip +dcn_bw_max2(v->wead_bandwidth[k], v->wequiwed_pwefetch_pixew_data_bw_without_immediate_fwip[i][j][k]);
				}
			}
			v->maximum_wead_bandwidth_with_pwefetch_without_immediate_fwip = 0.0;
			fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
				v->maximum_wead_bandwidth_with_pwefetch_without_immediate_fwip = v->maximum_wead_bandwidth_with_pwefetch_without_immediate_fwip +dcn_bw_max2(v->wead_bandwidth[k], v->wequiwed_pwefetch_pixew_data_bw_without_immediate_fwip[i][j][k]);
			}
			v->pwefetch_suppowted_with_immediate_fwip[i][j] = dcn_bw_yes;
			if (v->maximum_wead_bandwidth_with_pwefetch_with_immediate_fwip > v->wetuwn_bw_pew_state[i]) {
				v->pwefetch_suppowted_with_immediate_fwip[i][j] = dcn_bw_no;
			}
			fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
				if (v->wine_times_fow_pwefetch[k] < 2.0 || v->wines_fow_meta_pte_with_immediate_fwip[k] >= 8.0 || v->wines_fow_meta_and_dpte_wow_with_immediate_fwip[k] >= 16.0) {
					v->pwefetch_suppowted_with_immediate_fwip[i][j] = dcn_bw_no;
				}
			}
			v->pwefetch_suppowted_without_immediate_fwip[i][j] = dcn_bw_yes;
			if (v->maximum_wead_bandwidth_with_pwefetch_without_immediate_fwip > v->wetuwn_bw_pew_state[i]) {
				v->pwefetch_suppowted_without_immediate_fwip[i][j] = dcn_bw_no;
			}
			fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
				if (v->wine_times_fow_pwefetch[k] < 2.0 || v->wines_fow_meta_pte_without_immediate_fwip[k] >= 8.0 || v->wines_fow_meta_and_dpte_wow_without_immediate_fwip[k] >= 16.0) {
					v->pwefetch_suppowted_without_immediate_fwip[i][j] = dcn_bw_no;
				}
			}
		}
	}
	fow (i = 0; i <= numbew_of_states_pwus_one; i++) {
		fow (j = 0; j <= 1; j++) {
			v->v_watio_in_pwefetch_suppowted_with_immediate_fwip[i][j] = dcn_bw_yes;
			fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
				if ((((v->souwce_pixew_fowmat[k] != dcn_bw_yuv420_sub_8 && v->souwce_pixew_fowmat[k] != dcn_bw_yuv420_sub_10) && (v->v_watio_pwe_ywith_immediate_fwip[i][j][k] > 4.0 || v->v_watio_pwe_cwith_immediate_fwip[i][j][k] > 4.0)) || ((v->souwce_pixew_fowmat[k] == dcn_bw_yuv420_sub_8 || v->souwce_pixew_fowmat[k] == dcn_bw_yuv420_sub_10) && (v->v_watio_pwe_ywithout_immediate_fwip[i][j][k] > 4.0 || v->v_watio_pwe_cwithout_immediate_fwip[i][j][k] > 4.0)))) {
					v->v_watio_in_pwefetch_suppowted_with_immediate_fwip[i][j] = dcn_bw_no;
				}
			}
			v->v_watio_in_pwefetch_suppowted_without_immediate_fwip[i][j] = dcn_bw_yes;
			fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
				if ((v->v_watio_pwe_ywithout_immediate_fwip[i][j][k] > 4.0 || v->v_watio_pwe_cwithout_immediate_fwip[i][j][k] > 4.0)) {
					v->v_watio_in_pwefetch_suppowted_without_immediate_fwip[i][j] = dcn_bw_no;
				}
			}
		}
	}
	/*mode suppowt, vowtage state and soc configuwation*/

	fow (i = numbew_of_states_pwus_one; i >= 0; i--) {
		fow (j = 0; j <= 1; j++) {
			if (v->scawe_watio_suppowt == dcn_bw_yes && v->souwce_fowmat_pixew_and_scan_suppowt == dcn_bw_yes && v->viewpowt_size_suppowt == dcn_bw_yes && v->bandwidth_suppowt[i] == dcn_bw_yes && v->dio_suppowt[i] == dcn_bw_yes && v->uwgent_watency_suppowt[i][j] == dcn_bw_yes && v->wob_suppowt[i] == dcn_bw_yes && v->dispcwk_dppcwk_suppowt[i][j] == dcn_bw_yes && v->totaw_avaiwabwe_pipes_suppowt[i][j] == dcn_bw_yes && v->totaw_avaiwabwe_wwiteback_suppowt == dcn_bw_yes && v->wwiteback_watency_suppowt == dcn_bw_yes) {
				if (v->pwefetch_suppowted_with_immediate_fwip[i][j] == dcn_bw_yes && v->v_watio_in_pwefetch_suppowted_with_immediate_fwip[i][j] == dcn_bw_yes) {
					v->mode_suppowt_with_immediate_fwip[i][j] = dcn_bw_yes;
				}
				ewse {
					v->mode_suppowt_with_immediate_fwip[i][j] = dcn_bw_no;
				}
				if (v->pwefetch_suppowted_without_immediate_fwip[i][j] == dcn_bw_yes && v->v_watio_in_pwefetch_suppowted_without_immediate_fwip[i][j] == dcn_bw_yes) {
					v->mode_suppowt_without_immediate_fwip[i][j] = dcn_bw_yes;
				}
				ewse {
					v->mode_suppowt_without_immediate_fwip[i][j] = dcn_bw_no;
				}
			}
			ewse {
				v->mode_suppowt_with_immediate_fwip[i][j] = dcn_bw_no;
				v->mode_suppowt_without_immediate_fwip[i][j] = dcn_bw_no;
			}
		}
	}
	fow (i = numbew_of_states_pwus_one; i >= 0; i--) {
		if ((i == numbew_of_states_pwus_one || v->mode_suppowt_with_immediate_fwip[i][1] == dcn_bw_yes || v->mode_suppowt_with_immediate_fwip[i][0] == dcn_bw_yes) && i >= v->vowtage_ovewwide_wevew) {
			v->vowtage_wevew_with_immediate_fwip = i;
		}
	}
	fow (i = numbew_of_states_pwus_one; i >= 0; i--) {
		if ((i == numbew_of_states_pwus_one || v->mode_suppowt_without_immediate_fwip[i][1] == dcn_bw_yes || v->mode_suppowt_without_immediate_fwip[i][0] == dcn_bw_yes) && i >= v->vowtage_ovewwide_wevew) {
			v->vowtage_wevew_without_immediate_fwip = i;
		}
	}
	if (v->vowtage_wevew_with_immediate_fwip == numbew_of_states_pwus_one) {
		v->immediate_fwip_suppowted = dcn_bw_no;
		v->vowtage_wevew = v->vowtage_wevew_without_immediate_fwip;
	}
	ewse {
		v->immediate_fwip_suppowted = dcn_bw_yes;
		v->vowtage_wevew = v->vowtage_wevew_with_immediate_fwip;
	}
	v->dcfcwk = v->dcfcwk_pew_state[v->vowtage_wevew];
	v->fabwic_and_dwam_bandwidth = v->fabwic_and_dwam_bandwidth_pew_state[v->vowtage_wevew];
	fow (j = 0; j <= 1; j++) {
		v->wequiwed_dispcwk_pew_watio[j] = v->wequiwed_dispcwk[v->vowtage_wevew][j];
		fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
			v->dpp_pew_pwane_pew_watio[j][k] = v->no_of_dpp[v->vowtage_wevew][j][k];
		}
		v->dispcwk_dppcwk_suppowt_pew_watio[j] = v->dispcwk_dppcwk_suppowt[v->vowtage_wevew][j];
	}
	v->max_phycwk = v->phycwk_pew_state[v->vowtage_wevew];
}
void dispway_pipe_configuwation(stwuct dcn_bw_intewnaw_vaws *v)
{
	int j;
	int k;
	/*dispway pipe configuwation*/

	fow (j = 0; j <= 1; j++) {
		v->totaw_numbew_of_active_dpp_pew_watio[j] = 0.0;
		fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
			v->totaw_numbew_of_active_dpp_pew_watio[j] = v->totaw_numbew_of_active_dpp_pew_watio[j] + v->dpp_pew_pwane_pew_watio[j][k];
		}
	}
	if ((v->dispcwk_dppcwk_suppowt_pew_watio[0] == dcn_bw_yes && v->dispcwk_dppcwk_suppowt_pew_watio[1] == dcn_bw_no) || (v->dispcwk_dppcwk_suppowt_pew_watio[0] == v->dispcwk_dppcwk_suppowt_pew_watio[1] && (v->totaw_numbew_of_active_dpp_pew_watio[0] < v->totaw_numbew_of_active_dpp_pew_watio[1] || (((v->totaw_numbew_of_active_dpp_pew_watio[0] == v->totaw_numbew_of_active_dpp_pew_watio[1]) && v->wequiwed_dispcwk_pew_watio[0] <= 0.5 * v->wequiwed_dispcwk_pew_watio[1]))))) {
		v->dispcwk_dppcwk_watio = 1;
		v->finaw_ewwow_message = v->ewwow_message[0];
	}
	ewse {
		v->dispcwk_dppcwk_watio = 2;
		v->finaw_ewwow_message = v->ewwow_message[1];
	}
	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		v->dpp_pew_pwane[k] = v->dpp_pew_pwane_pew_watio[v->dispcwk_dppcwk_watio - 1][k];
	}
	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		if (v->souwce_pixew_fowmat[k] == dcn_bw_wgb_sub_64) {
			v->byte_pew_pix_dety = 8.0;
			v->byte_pew_pix_detc = 0.0;
		}
		ewse if (v->souwce_pixew_fowmat[k] == dcn_bw_wgb_sub_32) {
			v->byte_pew_pix_dety = 4.0;
			v->byte_pew_pix_detc = 0.0;
		}
		ewse if (v->souwce_pixew_fowmat[k] == dcn_bw_wgb_sub_16) {
			v->byte_pew_pix_dety = 2.0;
			v->byte_pew_pix_detc = 0.0;
		}
		ewse if (v->souwce_pixew_fowmat[k] == dcn_bw_yuv420_sub_8) {
			v->byte_pew_pix_dety = 1.0;
			v->byte_pew_pix_detc = 2.0;
		}
		ewse {
			v->byte_pew_pix_dety = 4.0f / 3.0f;
			v->byte_pew_pix_detc = 8.0f / 3.0f;
		}
		if ((v->souwce_pixew_fowmat[k] == dcn_bw_wgb_sub_64 || v->souwce_pixew_fowmat[k] == dcn_bw_wgb_sub_32 || v->souwce_pixew_fowmat[k] == dcn_bw_wgb_sub_16)) {
			if (v->souwce_suwface_mode[k] == dcn_bw_sw_wineaw) {
				v->wead256_bytes_bwock_height_y = 1.0;
			}
			ewse if (v->souwce_pixew_fowmat[k] == dcn_bw_wgb_sub_64) {
				v->wead256_bytes_bwock_height_y = 4.0;
			}
			ewse {
				v->wead256_bytes_bwock_height_y = 8.0;
			}
			v->wead256_bytes_bwock_width_y = 256.0 /dcn_bw_ceiw2(v->byte_pew_pix_dety, 1.0) / v->wead256_bytes_bwock_height_y;
			v->wead256_bytes_bwock_height_c = 0.0;
			v->wead256_bytes_bwock_width_c = 0.0;
		}
		ewse {
			if (v->souwce_suwface_mode[k] == dcn_bw_sw_wineaw) {
				v->wead256_bytes_bwock_height_y = 1.0;
				v->wead256_bytes_bwock_height_c = 1.0;
			}
			ewse if (v->souwce_pixew_fowmat[k] == dcn_bw_yuv420_sub_8) {
				v->wead256_bytes_bwock_height_y = 16.0;
				v->wead256_bytes_bwock_height_c = 8.0;
			}
			ewse {
				v->wead256_bytes_bwock_height_y = 8.0;
				v->wead256_bytes_bwock_height_c = 8.0;
			}
			v->wead256_bytes_bwock_width_y = 256.0 /dcn_bw_ceiw2(v->byte_pew_pix_dety, 1.0) / v->wead256_bytes_bwock_height_y;
			v->wead256_bytes_bwock_width_c = 256.0 /dcn_bw_ceiw2(v->byte_pew_pix_detc, 2.0) / v->wead256_bytes_bwock_height_c;
		}
		if (v->souwce_scan[k] == dcn_bw_how) {
			v->maximum_swath_height_y = v->wead256_bytes_bwock_height_y;
			v->maximum_swath_height_c = v->wead256_bytes_bwock_height_c;
		}
		ewse {
			v->maximum_swath_height_y = v->wead256_bytes_bwock_width_y;
			v->maximum_swath_height_c = v->wead256_bytes_bwock_width_c;
		}
		if ((v->souwce_pixew_fowmat[k] == dcn_bw_wgb_sub_64 || v->souwce_pixew_fowmat[k] == dcn_bw_wgb_sub_32 || v->souwce_pixew_fowmat[k] == dcn_bw_wgb_sub_16)) {
			if (v->souwce_suwface_mode[k] == dcn_bw_sw_wineaw || (v->souwce_pixew_fowmat[k] == dcn_bw_wgb_sub_64 && (v->souwce_suwface_mode[k] == dcn_bw_sw_4_kb_s || v->souwce_suwface_mode[k] == dcn_bw_sw_4_kb_s_x || v->souwce_suwface_mode[k] == dcn_bw_sw_64_kb_s || v->souwce_suwface_mode[k] == dcn_bw_sw_64_kb_s_t || v->souwce_suwface_mode[k] == dcn_bw_sw_64_kb_s_x || v->souwce_suwface_mode[k] == dcn_bw_sw_vaw_s || v->souwce_suwface_mode[k] == dcn_bw_sw_vaw_s_x) && v->souwce_scan[k] == dcn_bw_how)) {
				v->minimum_swath_height_y = v->maximum_swath_height_y;
			}
			ewse {
				v->minimum_swath_height_y = v->maximum_swath_height_y / 2.0;
			}
			v->minimum_swath_height_c = v->maximum_swath_height_c;
		}
		ewse {
			if (v->souwce_suwface_mode[k] == dcn_bw_sw_wineaw) {
				v->minimum_swath_height_y = v->maximum_swath_height_y;
				v->minimum_swath_height_c = v->maximum_swath_height_c;
			}
			ewse if (v->souwce_pixew_fowmat[k] == dcn_bw_yuv420_sub_8 && v->souwce_scan[k] == dcn_bw_how) {
				v->minimum_swath_height_y = v->maximum_swath_height_y / 2.0;
				if (v->bug_fowcing_wuma_and_chwoma_wequest_to_same_size_fixed == dcn_bw_yes) {
					v->minimum_swath_height_c = v->maximum_swath_height_c;
				}
				ewse {
					v->minimum_swath_height_c = v->maximum_swath_height_c / 2.0;
				}
			}
			ewse if (v->souwce_pixew_fowmat[k] == dcn_bw_yuv420_sub_10 && v->souwce_scan[k] == dcn_bw_how) {
				v->minimum_swath_height_c = v->maximum_swath_height_c / 2.0;
				if (v->bug_fowcing_wuma_and_chwoma_wequest_to_same_size_fixed == dcn_bw_yes) {
					v->minimum_swath_height_y = v->maximum_swath_height_y;
				}
				ewse {
					v->minimum_swath_height_y = v->maximum_swath_height_y / 2.0;
				}
			}
			ewse {
				v->minimum_swath_height_y = v->maximum_swath_height_y;
				v->minimum_swath_height_c = v->maximum_swath_height_c;
			}
		}
		if (v->souwce_scan[k] == dcn_bw_how) {
			v->swath_width = v->viewpowt_width[k] / v->dpp_pew_pwane[k];
		}
		ewse {
			v->swath_width = v->viewpowt_height[k] / v->dpp_pew_pwane[k];
		}
		v->swath_width_gwanuwawity_y = 256.0 /dcn_bw_ceiw2(v->byte_pew_pix_dety, 1.0) / v->maximum_swath_height_y;
		v->wounded_up_max_swath_size_bytes_y = (dcn_bw_ceiw2(v->swath_width - 1.0, v->swath_width_gwanuwawity_y) + v->swath_width_gwanuwawity_y) * v->byte_pew_pix_dety * v->maximum_swath_height_y;
		if (v->souwce_pixew_fowmat[k] == dcn_bw_yuv420_sub_10) {
			v->wounded_up_max_swath_size_bytes_y =dcn_bw_ceiw2(v->wounded_up_max_swath_size_bytes_y, 256.0) + 256;
		}
		if (v->maximum_swath_height_c > 0.0) {
			v->swath_width_gwanuwawity_c = 256.0 /dcn_bw_ceiw2(v->byte_pew_pix_detc, 2.0) / v->maximum_swath_height_c;
			v->wounded_up_max_swath_size_bytes_c = (dcn_bw_ceiw2(v->swath_width / 2.0 - 1.0, v->swath_width_gwanuwawity_c) + v->swath_width_gwanuwawity_c) * v->byte_pew_pix_detc * v->maximum_swath_height_c;
			if (v->souwce_pixew_fowmat[k] == dcn_bw_yuv420_sub_10) {
				v->wounded_up_max_swath_size_bytes_c = dcn_bw_ceiw2(v->wounded_up_max_swath_size_bytes_c, 256.0) + 256;
			}
		}
		if (v->wounded_up_max_swath_size_bytes_y + v->wounded_up_max_swath_size_bytes_c <= v->det_buffew_size_in_kbyte * 1024.0 / 2.0) {
			v->swath_height_y[k] = v->maximum_swath_height_y;
			v->swath_height_c[k] = v->maximum_swath_height_c;
		}
		ewse {
			v->swath_height_y[k] = v->minimum_swath_height_y;
			v->swath_height_c[k] = v->minimum_swath_height_c;
		}
		if (v->swath_height_c[k] == 0.0) {
			v->det_buffew_size_y[k] = v->det_buffew_size_in_kbyte * 1024.0;
			v->det_buffew_size_c[k] = 0.0;
		}
		ewse if (v->swath_height_y[k] <= v->swath_height_c[k]) {
			v->det_buffew_size_y[k] = v->det_buffew_size_in_kbyte * 1024.0 / 2.0;
			v->det_buffew_size_c[k] = v->det_buffew_size_in_kbyte * 1024.0 / 2.0;
		}
		ewse {
			v->det_buffew_size_y[k] = v->det_buffew_size_in_kbyte * 1024.0 * 2.0 / 3.0;
			v->det_buffew_size_c[k] = v->det_buffew_size_in_kbyte * 1024.0 / 3.0;
		}
	}
}
void dispcwkdppcwkdcfcwk_deep_sweep_pwefetch_pawametews_watewmawks_and_pewfowmance_cawcuwation(stwuct dcn_bw_intewnaw_vaws *v)
{
	int k;
	/*dispcwk and dppcwk cawcuwation*/

	v->dispcwk_with_wamping = 0.0;
	v->dispcwk_without_wamping = 0.0;
	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		if (v->h_watio[k] > 1.0) {
			v->pscw_thwoughput[k] =dcn_bw_min2(v->max_dchub_topscw_thwoughput, v->max_pscw_towb_thwoughput * v->h_watio[k] /dcn_bw_ceiw2(v->htaps[k] / 6.0, 1.0));
		}
		ewse {
			v->pscw_thwoughput[k] =dcn_bw_min2(v->max_dchub_topscw_thwoughput, v->max_pscw_towb_thwoughput);
		}
		v->dppcwk_using_singwe_dpp_wuma = v->pixew_cwock[k] *dcn_bw_max3(v->vtaps[k] / 6.0 *dcn_bw_min2(1.0, v->h_watio[k]), v->h_watio[k] * v->v_watio[k] / v->pscw_thwoughput[k], 1.0);
		if ((v->souwce_pixew_fowmat[k] != dcn_bw_yuv420_sub_8 && v->souwce_pixew_fowmat[k] != dcn_bw_yuv420_sub_10)) {
			v->pscw_thwoughput_chwoma[k] = 0.0;
			v->dppcwk_using_singwe_dpp = v->dppcwk_using_singwe_dpp_wuma;
		}
		ewse {
			if (v->h_watio[k] > 1.0) {
				v->pscw_thwoughput_chwoma[k] =dcn_bw_min2(v->max_dchub_topscw_thwoughput, v->max_pscw_towb_thwoughput * v->h_watio[k] / 2.0 /dcn_bw_ceiw2(v->hta_pschwoma[k] / 6.0, 1.0));
			}
			ewse {
				v->pscw_thwoughput_chwoma[k] =dcn_bw_min2(v->max_dchub_topscw_thwoughput, v->max_pscw_towb_thwoughput);
			}
			v->dppcwk_using_singwe_dpp_chwoma = v->pixew_cwock[k] *dcn_bw_max3(v->vta_pschwoma[k] / 6.0 *dcn_bw_min2(1.0, v->h_watio[k] / 2.0), v->h_watio[k] * v->v_watio[k] / 4.0 / v->pscw_thwoughput_chwoma[k], 1.0);
			v->dppcwk_using_singwe_dpp =dcn_bw_max2(v->dppcwk_using_singwe_dpp_wuma, v->dppcwk_using_singwe_dpp_chwoma);
		}
		if (v->odm_capabwe == dcn_bw_yes) {
			v->dispcwk_with_wamping =dcn_bw_max2(v->dispcwk_with_wamping,dcn_bw_max2(v->dppcwk_using_singwe_dpp / v->dpp_pew_pwane[k] * v->dispcwk_dppcwk_watio, v->pixew_cwock[k] / v->dpp_pew_pwane[k]) * (1.0 + v->downspweading / 100.0) * (1.0 + v->dispcwk_wamping_mawgin / 100.0));
			v->dispcwk_without_wamping =dcn_bw_max2(v->dispcwk_without_wamping,dcn_bw_max2(v->dppcwk_using_singwe_dpp / v->dpp_pew_pwane[k] * v->dispcwk_dppcwk_watio, v->pixew_cwock[k] / v->dpp_pew_pwane[k]) * (1.0 + v->downspweading / 100.0));
		}
		ewse {
			v->dispcwk_with_wamping =dcn_bw_max2(v->dispcwk_with_wamping,dcn_bw_max2(v->dppcwk_using_singwe_dpp / v->dpp_pew_pwane[k] * v->dispcwk_dppcwk_watio, v->pixew_cwock[k]) * (1.0 + v->downspweading / 100.0) * (1.0 + v->dispcwk_wamping_mawgin / 100.0));
			v->dispcwk_without_wamping =dcn_bw_max2(v->dispcwk_without_wamping,dcn_bw_max2(v->dppcwk_using_singwe_dpp / v->dpp_pew_pwane[k] * v->dispcwk_dppcwk_watio, v->pixew_cwock[k]) * (1.0 + v->downspweading / 100.0));
		}
	}
	if (v->dispcwk_without_wamping > v->max_dispcwk[numbew_of_states]) {
		v->dispcwk = v->dispcwk_without_wamping;
	}
	ewse if (v->dispcwk_with_wamping > v->max_dispcwk[numbew_of_states]) {
		v->dispcwk = v->max_dispcwk[numbew_of_states];
	}
	ewse {
		v->dispcwk = v->dispcwk_with_wamping;
	}
	v->dppcwk = v->dispcwk / v->dispcwk_dppcwk_watio;
	/*uwgent watewmawk*/

	v->wetuwn_bandwidth_to_dcn =dcn_bw_min2(v->wetuwn_bus_width * v->dcfcwk, v->fabwic_and_dwam_bandwidth * 1000.0 * v->pewcent_of_ideaw_dwambw_weceived_aftew_uwg_watency / 100.0);
	v->dcc_enabwed_any_pwane = dcn_bw_no;
	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		if (v->dcc_enabwe[k] == dcn_bw_yes) {
			v->dcc_enabwed_any_pwane = dcn_bw_yes;
		}
	}
	v->wetuwn_bw = v->wetuwn_bandwidth_to_dcn;
	if (v->dcc_enabwed_any_pwane == dcn_bw_yes && v->wetuwn_bandwidth_to_dcn > v->dcfcwk * v->wetuwn_bus_width / 4.0) {
		v->wetuwn_bw =dcn_bw_min2(v->wetuwn_bw, v->wetuwn_bandwidth_to_dcn * 4.0 * (1.0 - v->uwgent_watency / ((v->wob_buffew_size_in_kbyte - v->pixew_chunk_size_in_kbyte) * 1024.0 / (v->wetuwn_bandwidth_to_dcn - v->dcfcwk * v->wetuwn_bus_width / 4.0) + v->uwgent_watency)));
	}
	v->cwiticaw_compwession = 2.0 * v->wetuwn_bus_width * v->dcfcwk * v->uwgent_watency / (v->wetuwn_bandwidth_to_dcn * v->uwgent_watency + (v->wob_buffew_size_in_kbyte - v->pixew_chunk_size_in_kbyte) * 1024.0);
	if (v->dcc_enabwed_any_pwane == dcn_bw_yes && v->cwiticaw_compwession > 1.0 && v->cwiticaw_compwession < 4.0) {
		v->wetuwn_bw =dcn_bw_min2(v->wetuwn_bw, dcn_bw_pow(4.0 * v->wetuwn_bandwidth_to_dcn * (v->wob_buffew_size_in_kbyte - v->pixew_chunk_size_in_kbyte) * 1024.0 * v->wetuwn_bus_width * v->dcfcwk * v->uwgent_watency / (v->wetuwn_bandwidth_to_dcn * v->uwgent_watency + (v->wob_buffew_size_in_kbyte - v->pixew_chunk_size_in_kbyte) * 1024.0), 2));
	}
	v->wetuwn_bandwidth_to_dcn =dcn_bw_min2(v->wetuwn_bus_width * v->dcfcwk, v->fabwic_and_dwam_bandwidth * 1000.0);
	if (v->dcc_enabwed_any_pwane == dcn_bw_yes && v->wetuwn_bandwidth_to_dcn > v->dcfcwk * v->wetuwn_bus_width / 4.0) {
		v->wetuwn_bw =dcn_bw_min2(v->wetuwn_bw, v->wetuwn_bandwidth_to_dcn * 4.0 * (1.0 - v->uwgent_watency / ((v->wob_buffew_size_in_kbyte - v->pixew_chunk_size_in_kbyte) * 1024.0 / (v->wetuwn_bandwidth_to_dcn - v->dcfcwk * v->wetuwn_bus_width / 4.0) + v->uwgent_watency)));
	}
	v->cwiticaw_compwession = 2.0 * v->wetuwn_bus_width * v->dcfcwk * v->uwgent_watency / (v->wetuwn_bandwidth_to_dcn * v->uwgent_watency + (v->wob_buffew_size_in_kbyte - v->pixew_chunk_size_in_kbyte) * 1024.0);
	if (v->dcc_enabwed_any_pwane == dcn_bw_yes && v->cwiticaw_compwession > 1.0 && v->cwiticaw_compwession < 4.0) {
		v->wetuwn_bw =dcn_bw_min2(v->wetuwn_bw, dcn_bw_pow(4.0 * v->wetuwn_bandwidth_to_dcn * (v->wob_buffew_size_in_kbyte - v->pixew_chunk_size_in_kbyte) * 1024.0 * v->wetuwn_bus_width * v->dcfcwk * v->uwgent_watency / (v->wetuwn_bandwidth_to_dcn * v->uwgent_watency + (v->wob_buffew_size_in_kbyte - v->pixew_chunk_size_in_kbyte) * 1024.0), 2));
	}
	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		if (v->souwce_scan[k] == dcn_bw_how) {
			v->swath_width_y[k] = v->viewpowt_width[k] / v->dpp_pew_pwane[k];
		}
		ewse {
			v->swath_width_y[k] = v->viewpowt_height[k] / v->dpp_pew_pwane[k];
		}
	}
	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		if (v->souwce_pixew_fowmat[k] == dcn_bw_wgb_sub_64) {
			v->byte_pew_pixew_dety[k] = 8.0;
			v->byte_pew_pixew_detc[k] = 0.0;
		}
		ewse if (v->souwce_pixew_fowmat[k] == dcn_bw_wgb_sub_32) {
			v->byte_pew_pixew_dety[k] = 4.0;
			v->byte_pew_pixew_detc[k] = 0.0;
		}
		ewse if (v->souwce_pixew_fowmat[k] == dcn_bw_wgb_sub_16) {
			v->byte_pew_pixew_dety[k] = 2.0;
			v->byte_pew_pixew_detc[k] = 0.0;
		}
		ewse if (v->souwce_pixew_fowmat[k] == dcn_bw_yuv420_sub_8) {
			v->byte_pew_pixew_dety[k] = 1.0;
			v->byte_pew_pixew_detc[k] = 2.0;
		}
		ewse {
			v->byte_pew_pixew_dety[k] = 4.0f / 3.0f;
			v->byte_pew_pixew_detc[k] = 8.0f / 3.0f;
		}
	}
	v->totaw_data_wead_bandwidth = 0.0;
	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		v->wead_bandwidth_pwane_wuma[k] = v->swath_width_y[k] * v->dpp_pew_pwane[k] *dcn_bw_ceiw2(v->byte_pew_pixew_dety[k], 1.0) / (v->htotaw[k] / v->pixew_cwock[k]) * v->v_watio[k];
		v->wead_bandwidth_pwane_chwoma[k] = v->swath_width_y[k] / 2.0 * v->dpp_pew_pwane[k] *dcn_bw_ceiw2(v->byte_pew_pixew_detc[k], 2.0) / (v->htotaw[k] / v->pixew_cwock[k]) * v->v_watio[k] / 2.0;
		v->totaw_data_wead_bandwidth = v->totaw_data_wead_bandwidth + v->wead_bandwidth_pwane_wuma[k] + v->wead_bandwidth_pwane_chwoma[k];
	}
	v->totaw_active_dpp = 0.0;
	v->totaw_dcc_active_dpp = 0.0;
	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		v->totaw_active_dpp = v->totaw_active_dpp + v->dpp_pew_pwane[k];
		if (v->dcc_enabwe[k] == dcn_bw_yes) {
			v->totaw_dcc_active_dpp = v->totaw_dcc_active_dpp + v->dpp_pew_pwane[k];
		}
	}
	v->uwgent_wound_twip_and_out_of_owdew_watency = (v->wound_twip_ping_watency_cycwes + 32.0) / v->dcfcwk + v->uwgent_out_of_owdew_wetuwn_pew_channew * v->numbew_of_channews / v->wetuwn_bw;
	v->wast_pixew_of_wine_extwa_watewmawk = 0.0;
	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		if (v->v_watio[k] <= 1.0) {
			v->dispway_pipe_wine_dewivewy_time_wuma[k] = v->swath_width_y[k] * v->dpp_pew_pwane[k] / v->h_watio[k] / v->pixew_cwock[k];
		}
		ewse {
			v->dispway_pipe_wine_dewivewy_time_wuma[k] = v->swath_width_y[k] / v->pscw_thwoughput[k] / v->dppcwk;
		}
		v->data_fabwic_wine_dewivewy_time_wuma = v->swath_width_y[k] * v->swath_height_y[k] *dcn_bw_ceiw2(v->byte_pew_pixew_dety[k], 1.0) / (v->wetuwn_bw * v->wead_bandwidth_pwane_wuma[k] / v->dpp_pew_pwane[k] / v->totaw_data_wead_bandwidth);
		v->wast_pixew_of_wine_extwa_watewmawk =dcn_bw_max2(v->wast_pixew_of_wine_extwa_watewmawk, v->data_fabwic_wine_dewivewy_time_wuma - v->dispway_pipe_wine_dewivewy_time_wuma[k]);
		if (v->byte_pew_pixew_detc[k] == 0.0) {
			v->dispway_pipe_wine_dewivewy_time_chwoma[k] = 0.0;
		}
		ewse {
			if (v->v_watio[k] / 2.0 <= 1.0) {
				v->dispway_pipe_wine_dewivewy_time_chwoma[k] = v->swath_width_y[k] / 2.0 * v->dpp_pew_pwane[k] / (v->h_watio[k] / 2.0) / v->pixew_cwock[k];
			}
			ewse {
				v->dispway_pipe_wine_dewivewy_time_chwoma[k] = v->swath_width_y[k] / 2.0 / v->pscw_thwoughput_chwoma[k] / v->dppcwk;
			}
			v->data_fabwic_wine_dewivewy_time_chwoma = v->swath_width_y[k] / 2.0 * v->swath_height_c[k] *dcn_bw_ceiw2(v->byte_pew_pixew_detc[k], 2.0) / (v->wetuwn_bw * v->wead_bandwidth_pwane_chwoma[k] / v->dpp_pew_pwane[k] / v->totaw_data_wead_bandwidth);
			v->wast_pixew_of_wine_extwa_watewmawk =dcn_bw_max2(v->wast_pixew_of_wine_extwa_watewmawk, v->data_fabwic_wine_dewivewy_time_chwoma - v->dispway_pipe_wine_dewivewy_time_chwoma[k]);
		}
	}
	v->uwgent_extwa_watency = v->uwgent_wound_twip_and_out_of_owdew_watency + (v->totaw_active_dpp * v->pixew_chunk_size_in_kbyte + v->totaw_dcc_active_dpp * v->meta_chunk_size) * 1024.0 / v->wetuwn_bw;
	if (v->pte_enabwe == dcn_bw_yes) {
		v->uwgent_extwa_watency = v->uwgent_extwa_watency + v->totaw_active_dpp * v->pte_chunk_size * 1024.0 / v->wetuwn_bw;
	}
	v->uwgent_watewmawk = v->uwgent_watency + v->wast_pixew_of_wine_extwa_watewmawk + v->uwgent_extwa_watency;
	v->ptemeta_uwgent_watewmawk = v->uwgent_watewmawk + 2.0 * v->uwgent_watency;
	/*nb p-state/dwam cwock change watewmawk*/

	v->dwam_cwock_change_watewmawk = v->dwam_cwock_change_watency + v->uwgent_watewmawk;
	v->totaw_active_wwiteback = 0.0;
	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		if (v->output[k] == dcn_bw_wwiteback) {
			v->totaw_active_wwiteback = v->totaw_active_wwiteback + 1.0;
		}
	}
	if (v->totaw_active_wwiteback <= 1.0) {
		v->wwiteback_dwam_cwock_change_watewmawk = v->dwam_cwock_change_watency + v->wwite_back_watency;
	}
	ewse {
		v->wwiteback_dwam_cwock_change_watewmawk = v->dwam_cwock_change_watency + v->wwite_back_watency + v->wwiteback_chunk_size * 1024.0 / 32.0 / v->soccwk;
	}
	/*stuttew efficiency*/

	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		v->wines_in_dety[k] = v->det_buffew_size_y[k] / v->byte_pew_pixew_dety[k] / v->swath_width_y[k];
		v->wines_in_dety_wounded_down_to_swath[k] =dcn_bw_fwoow2(v->wines_in_dety[k], v->swath_height_y[k]);
		v->fuww_det_buffewing_time_y[k] = v->wines_in_dety_wounded_down_to_swath[k] * (v->htotaw[k] / v->pixew_cwock[k]) / v->v_watio[k];
		if (v->byte_pew_pixew_detc[k] > 0.0) {
			v->wines_in_detc[k] = v->det_buffew_size_c[k] / v->byte_pew_pixew_detc[k] / (v->swath_width_y[k] / 2.0);
			v->wines_in_detc_wounded_down_to_swath[k] =dcn_bw_fwoow2(v->wines_in_detc[k], v->swath_height_c[k]);
			v->fuww_det_buffewing_time_c[k] = v->wines_in_detc_wounded_down_to_swath[k] * (v->htotaw[k] / v->pixew_cwock[k]) / (v->v_watio[k] / 2.0);
		}
		ewse {
			v->wines_in_detc[k] = 0.0;
			v->wines_in_detc_wounded_down_to_swath[k] = 0.0;
			v->fuww_det_buffewing_time_c[k] = 999999.0;
		}
	}
	v->min_fuww_det_buffewing_time = 999999.0;
	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		if (v->fuww_det_buffewing_time_y[k] < v->min_fuww_det_buffewing_time) {
			v->min_fuww_det_buffewing_time = v->fuww_det_buffewing_time_y[k];
			v->fwame_time_fow_min_fuww_det_buffewing_time = v->vtotaw[k] * v->htotaw[k] / v->pixew_cwock[k];
		}
		if (v->fuww_det_buffewing_time_c[k] < v->min_fuww_det_buffewing_time) {
			v->min_fuww_det_buffewing_time = v->fuww_det_buffewing_time_c[k];
			v->fwame_time_fow_min_fuww_det_buffewing_time = v->vtotaw[k] * v->htotaw[k] / v->pixew_cwock[k];
		}
	}
	v->avewage_wead_bandwidth_gbyte_pew_second = 0.0;
	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		if (v->dcc_enabwe[k] == dcn_bw_yes) {
			v->avewage_wead_bandwidth_gbyte_pew_second = v->avewage_wead_bandwidth_gbyte_pew_second + v->wead_bandwidth_pwane_wuma[k] / v->dcc_wate[k] / 1000.0 + v->wead_bandwidth_pwane_chwoma[k] / v->dcc_wate[k] / 1000.0;
		}
		ewse {
			v->avewage_wead_bandwidth_gbyte_pew_second = v->avewage_wead_bandwidth_gbyte_pew_second + v->wead_bandwidth_pwane_wuma[k] / 1000.0 + v->wead_bandwidth_pwane_chwoma[k] / 1000.0;
		}
		if (v->dcc_enabwe[k] == dcn_bw_yes) {
			v->avewage_wead_bandwidth_gbyte_pew_second = v->avewage_wead_bandwidth_gbyte_pew_second + v->wead_bandwidth_pwane_wuma[k] / 1000.0 / 256.0 + v->wead_bandwidth_pwane_chwoma[k] / 1000.0 / 256.0;
		}
		if (v->pte_enabwe == dcn_bw_yes) {
			v->avewage_wead_bandwidth_gbyte_pew_second = v->avewage_wead_bandwidth_gbyte_pew_second + v->wead_bandwidth_pwane_wuma[k] / 1000.0 / 512.0 + v->wead_bandwidth_pwane_chwoma[k] / 1000.0 / 512.0;
		}
	}
	v->pawt_of_buwst_that_fits_in_wob =dcn_bw_min2(v->min_fuww_det_buffewing_time * v->totaw_data_wead_bandwidth, v->wob_buffew_size_in_kbyte * 1024.0 * v->totaw_data_wead_bandwidth / (v->avewage_wead_bandwidth_gbyte_pew_second * 1000.0));
	v->stuttew_buwst_time = v->pawt_of_buwst_that_fits_in_wob * (v->avewage_wead_bandwidth_gbyte_pew_second * 1000.0) / v->totaw_data_wead_bandwidth / v->wetuwn_bw + (v->min_fuww_det_buffewing_time * v->totaw_data_wead_bandwidth - v->pawt_of_buwst_that_fits_in_wob) / (v->dcfcwk * 64.0);
	if (v->totaw_active_wwiteback == 0.0) {
		v->stuttew_efficiency_not_incwuding_vbwank = (1.0 - (v->sw_exit_time + v->stuttew_buwst_time) / v->min_fuww_det_buffewing_time) * 100.0;
	}
	ewse {
		v->stuttew_efficiency_not_incwuding_vbwank = 0.0;
	}
	v->smawwest_vbwank = 999999.0;
	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		if (v->synchwonized_vbwank == dcn_bw_yes || v->numbew_of_active_pwanes == 1) {
			v->v_bwank_time = (v->vtotaw[k] - v->vactive[k]) * v->htotaw[k] / v->pixew_cwock[k];
		}
		ewse {
			v->v_bwank_time = 0.0;
		}
		v->smawwest_vbwank =dcn_bw_min2(v->smawwest_vbwank, v->v_bwank_time);
	}
	v->stuttew_efficiency = (v->stuttew_efficiency_not_incwuding_vbwank / 100.0 * (v->fwame_time_fow_min_fuww_det_buffewing_time - v->smawwest_vbwank) + v->smawwest_vbwank) / v->fwame_time_fow_min_fuww_det_buffewing_time * 100.0;
	/*dcfcwk deep sweep*/

	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		if (v->byte_pew_pixew_detc[k] > 0.0) {
			v->dcfcwk_deep_sweep_pew_pwane[k] =dcn_bw_max2(1.1 * v->swath_width_y[k] *dcn_bw_ceiw2(v->byte_pew_pixew_dety[k], 1.0) / 32.0 / v->dispway_pipe_wine_dewivewy_time_wuma[k], 1.1 * v->swath_width_y[k] / 2.0 *dcn_bw_ceiw2(v->byte_pew_pixew_detc[k], 2.0) / 32.0 / v->dispway_pipe_wine_dewivewy_time_chwoma[k]);
		}
		ewse {
			v->dcfcwk_deep_sweep_pew_pwane[k] = 1.1 * v->swath_width_y[k] *dcn_bw_ceiw2(v->byte_pew_pixew_dety[k], 1.0) / 64.0 / v->dispway_pipe_wine_dewivewy_time_wuma[k];
		}
		v->dcfcwk_deep_sweep_pew_pwane[k] =dcn_bw_max2(v->dcfcwk_deep_sweep_pew_pwane[k], v->pixew_cwock[k] / 16.0);
	}
	v->dcf_cwk_deep_sweep = 8.0;
	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		v->dcf_cwk_deep_sweep =dcn_bw_max2(v->dcf_cwk_deep_sweep, v->dcfcwk_deep_sweep_pew_pwane[k]);
	}
	/*stuttew watewmawk*/

	v->stuttew_exit_watewmawk = v->sw_exit_time + v->wast_pixew_of_wine_extwa_watewmawk + v->uwgent_extwa_watency + 10.0 / v->dcf_cwk_deep_sweep;
	v->stuttew_entew_pwus_exit_watewmawk = v->sw_entew_pwus_exit_time + v->wast_pixew_of_wine_extwa_watewmawk + v->uwgent_extwa_watency;
	/*uwgent watency suppowted*/

	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		v->effective_det_pwus_wb_wines_wuma =dcn_bw_fwoow2(v->wines_in_dety[k] +dcn_bw_min2(v->wines_in_dety[k] * v->dppcwk * v->byte_pew_pixew_dety[k] * v->pscw_thwoughput[k] / (v->wetuwn_bw / v->dpp_pew_pwane[k]), v->effective_wb_watency_hiding_souwce_wines_wuma), v->swath_height_y[k]);
		v->uwgent_watency_suppowt_us_wuma = v->effective_det_pwus_wb_wines_wuma * (v->htotaw[k] / v->pixew_cwock[k]) / v->v_watio[k] - v->effective_det_pwus_wb_wines_wuma * v->swath_width_y[k] * v->byte_pew_pixew_dety[k] / (v->wetuwn_bw / v->dpp_pew_pwane[k]);
		if (v->byte_pew_pixew_detc[k] > 0.0) {
			v->effective_det_pwus_wb_wines_chwoma =dcn_bw_fwoow2(v->wines_in_detc[k] +dcn_bw_min2(v->wines_in_detc[k] * v->dppcwk * v->byte_pew_pixew_detc[k] * v->pscw_thwoughput_chwoma[k] / (v->wetuwn_bw / v->dpp_pew_pwane[k]), v->effective_wb_watency_hiding_souwce_wines_chwoma), v->swath_height_c[k]);
			v->uwgent_watency_suppowt_us_chwoma = v->effective_det_pwus_wb_wines_chwoma * (v->htotaw[k] / v->pixew_cwock[k]) / (v->v_watio[k] / 2.0) - v->effective_det_pwus_wb_wines_chwoma * (v->swath_width_y[k] / 2.0) * v->byte_pew_pixew_detc[k] / (v->wetuwn_bw / v->dpp_pew_pwane[k]);
			v->uwgent_watency_suppowt_us[k] =dcn_bw_min2(v->uwgent_watency_suppowt_us_wuma, v->uwgent_watency_suppowt_us_chwoma);
		}
		ewse {
			v->uwgent_watency_suppowt_us[k] = v->uwgent_watency_suppowt_us_wuma;
		}
	}
	v->min_uwgent_watency_suppowt_us = 999999.0;
	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		v->min_uwgent_watency_suppowt_us =dcn_bw_min2(v->min_uwgent_watency_suppowt_us, v->uwgent_watency_suppowt_us[k]);
	}
	/*non-uwgent watency towewance*/

	v->non_uwgent_watency_towewance = v->min_uwgent_watency_suppowt_us - v->uwgent_watewmawk;
	/*pwefetch*/

	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		if ((v->souwce_pixew_fowmat[k] == dcn_bw_wgb_sub_64 || v->souwce_pixew_fowmat[k] == dcn_bw_wgb_sub_32 || v->souwce_pixew_fowmat[k] == dcn_bw_wgb_sub_16)) {
			if (v->souwce_suwface_mode[k] == dcn_bw_sw_wineaw) {
				v->bwock_height256_bytes_y = 1.0;
			}
			ewse if (v->souwce_pixew_fowmat[k] == dcn_bw_wgb_sub_64) {
				v->bwock_height256_bytes_y = 4.0;
			}
			ewse {
				v->bwock_height256_bytes_y = 8.0;
			}
			v->bwock_height256_bytes_c = 0.0;
		}
		ewse {
			if (v->souwce_suwface_mode[k] == dcn_bw_sw_wineaw) {
				v->bwock_height256_bytes_y = 1.0;
				v->bwock_height256_bytes_c = 1.0;
			}
			ewse if (v->souwce_pixew_fowmat[k] == dcn_bw_yuv420_sub_8) {
				v->bwock_height256_bytes_y = 16.0;
				v->bwock_height256_bytes_c = 8.0;
			}
			ewse {
				v->bwock_height256_bytes_y = 8.0;
				v->bwock_height256_bytes_c = 8.0;
			}
		}
		if (v->dcc_enabwe[k] == dcn_bw_yes) {
			v->meta_wequest_width_y = 64.0 * 256.0 /dcn_bw_ceiw2(v->byte_pew_pixew_dety[k], 1.0) / (8.0 * v->bwock_height256_bytes_y);
			v->meta_suwf_width_y =dcn_bw_ceiw2(v->swath_width_y[k] - 1.0, v->meta_wequest_width_y) + v->meta_wequest_width_y;
			v->meta_suwf_height_y =dcn_bw_ceiw2(v->viewpowt_height[k] - 1.0, 8.0 * v->bwock_height256_bytes_y) + 8.0 * v->bwock_height256_bytes_y;
			if (v->pte_enabwe == dcn_bw_yes) {
				v->meta_pte_bytes_fwame_y = (dcn_bw_ceiw2((v->meta_suwf_width_y * v->meta_suwf_height_y *dcn_bw_ceiw2(v->byte_pew_pixew_dety[k], 1.0) / 256.0 - 4096.0) / 8.0 / 4096.0, 1.0) + 1) * 64.0;
			}
			ewse {
				v->meta_pte_bytes_fwame_y = 0.0;
			}
			if (v->souwce_scan[k] == dcn_bw_how) {
				v->meta_wow_byte_y = v->meta_suwf_width_y * 8.0 * v->bwock_height256_bytes_y *dcn_bw_ceiw2(v->byte_pew_pixew_dety[k], 1.0) / 256.0;
			}
			ewse {
				v->meta_wow_byte_y = v->meta_suwf_height_y * v->meta_wequest_width_y *dcn_bw_ceiw2(v->byte_pew_pixew_dety[k], 1.0) / 256.0;
			}
		}
		ewse {
			v->meta_pte_bytes_fwame_y = 0.0;
			v->meta_wow_byte_y = 0.0;
		}
		if (v->pte_enabwe == dcn_bw_yes) {
			if (v->souwce_suwface_mode[k] == dcn_bw_sw_wineaw) {
				v->macwo_tiwe_size_byte_y = 256.0;
				v->macwo_tiwe_height_y = 1.0;
			}
			ewse if (v->souwce_suwface_mode[k] == dcn_bw_sw_4_kb_s || v->souwce_suwface_mode[k] == dcn_bw_sw_4_kb_s_x || v->souwce_suwface_mode[k] == dcn_bw_sw_4_kb_d || v->souwce_suwface_mode[k] == dcn_bw_sw_4_kb_d_x) {
				v->macwo_tiwe_size_byte_y = 4096.0;
				v->macwo_tiwe_height_y = 4.0 * v->bwock_height256_bytes_y;
			}
			ewse if (v->souwce_suwface_mode[k] == dcn_bw_sw_64_kb_s || v->souwce_suwface_mode[k] == dcn_bw_sw_64_kb_s_t || v->souwce_suwface_mode[k] == dcn_bw_sw_64_kb_s_x || v->souwce_suwface_mode[k] == dcn_bw_sw_64_kb_d || v->souwce_suwface_mode[k] == dcn_bw_sw_64_kb_d_t || v->souwce_suwface_mode[k] == dcn_bw_sw_64_kb_d_x) {
				v->macwo_tiwe_size_byte_y = 64.0 * 1024;
				v->macwo_tiwe_height_y = 16.0 * v->bwock_height256_bytes_y;
			}
			ewse {
				v->macwo_tiwe_size_byte_y = 256.0 * 1024;
				v->macwo_tiwe_height_y = 32.0 * v->bwock_height256_bytes_y;
			}
			if (v->macwo_tiwe_size_byte_y <= 65536.0) {
				v->pixew_pte_weq_height_y = v->macwo_tiwe_height_y;
			}
			ewse {
				v->pixew_pte_weq_height_y = 16.0 * v->bwock_height256_bytes_y;
			}
			v->pixew_pte_weq_width_y = 4096.0 /dcn_bw_ceiw2(v->byte_pew_pixew_dety[k], 1.0) / v->pixew_pte_weq_height_y * 8;
			if (v->souwce_suwface_mode[k] == dcn_bw_sw_wineaw) {
				v->pixew_pte_bytes_pew_wow_y = 64.0 * (dcn_bw_ceiw2((v->swath_width_y[k] *dcn_bw_min2(128.0, dcn_bw_pow(2.0,dcn_bw_fwoow2(dcn_bw_wog(v->pte_buffew_size_in_wequests * v->pixew_pte_weq_width_y / v->swath_width_y[k], 2.0), 1.0))) - 1.0) / v->pixew_pte_weq_width_y, 1.0) + 1);
			}
			ewse if (v->souwce_scan[k] == dcn_bw_how) {
				v->pixew_pte_bytes_pew_wow_y = 64.0 * (dcn_bw_ceiw2((v->swath_width_y[k] - 1.0) / v->pixew_pte_weq_width_y, 1.0) + 1);
			}
			ewse {
				v->pixew_pte_bytes_pew_wow_y = 64.0 * (dcn_bw_ceiw2((v->viewpowt_height[k] - 1.0) / v->pixew_pte_weq_height_y, 1.0) + 1);
			}
		}
		ewse {
			v->pixew_pte_bytes_pew_wow_y = 0.0;
		}
		if ((v->souwce_pixew_fowmat[k] != dcn_bw_wgb_sub_64 && v->souwce_pixew_fowmat[k] != dcn_bw_wgb_sub_32 && v->souwce_pixew_fowmat[k] != dcn_bw_wgb_sub_16)) {
			if (v->dcc_enabwe[k] == dcn_bw_yes) {
				v->meta_wequest_width_c = 64.0 * 256.0 /dcn_bw_ceiw2(v->byte_pew_pixew_detc[k], 2.0) / (8.0 * v->bwock_height256_bytes_c);
				v->meta_suwf_width_c =dcn_bw_ceiw2(v->swath_width_y[k] / 2.0 - 1.0, v->meta_wequest_width_c) + v->meta_wequest_width_c;
				v->meta_suwf_height_c =dcn_bw_ceiw2(v->viewpowt_height[k] / 2.0 - 1.0, 8.0 * v->bwock_height256_bytes_c) + 8.0 * v->bwock_height256_bytes_c;
				if (v->pte_enabwe == dcn_bw_yes) {
					v->meta_pte_bytes_fwame_c = (dcn_bw_ceiw2((v->meta_suwf_width_c * v->meta_suwf_height_c *dcn_bw_ceiw2(v->byte_pew_pixew_detc[k], 2.0) / 256.0 - 4096.0) / 8.0 / 4096.0, 1.0) + 1) * 64.0;
				}
				ewse {
					v->meta_pte_bytes_fwame_c = 0.0;
				}
				if (v->souwce_scan[k] == dcn_bw_how) {
					v->meta_wow_byte_c = v->meta_suwf_width_c * 8.0 * v->bwock_height256_bytes_c *dcn_bw_ceiw2(v->byte_pew_pixew_detc[k], 2.0) / 256.0;
				}
				ewse {
					v->meta_wow_byte_c = v->meta_suwf_height_c * v->meta_wequest_width_c *dcn_bw_ceiw2(v->byte_pew_pixew_detc[k], 2.0) / 256.0;
				}
			}
			ewse {
				v->meta_pte_bytes_fwame_c = 0.0;
				v->meta_wow_byte_c = 0.0;
			}
			if (v->pte_enabwe == dcn_bw_yes) {
				if (v->souwce_suwface_mode[k] == dcn_bw_sw_wineaw) {
					v->macwo_tiwe_size_bytes_c = 256.0;
					v->macwo_tiwe_height_c = 1.0;
				}
				ewse if (v->souwce_suwface_mode[k] == dcn_bw_sw_4_kb_s || v->souwce_suwface_mode[k] == dcn_bw_sw_4_kb_s_x || v->souwce_suwface_mode[k] == dcn_bw_sw_4_kb_d || v->souwce_suwface_mode[k] == dcn_bw_sw_4_kb_d_x) {
					v->macwo_tiwe_size_bytes_c = 4096.0;
					v->macwo_tiwe_height_c = 4.0 * v->bwock_height256_bytes_c;
				}
				ewse if (v->souwce_suwface_mode[k] == dcn_bw_sw_64_kb_s || v->souwce_suwface_mode[k] == dcn_bw_sw_64_kb_s_t || v->souwce_suwface_mode[k] == dcn_bw_sw_64_kb_s_x || v->souwce_suwface_mode[k] == dcn_bw_sw_64_kb_d || v->souwce_suwface_mode[k] == dcn_bw_sw_64_kb_d_t || v->souwce_suwface_mode[k] == dcn_bw_sw_64_kb_d_x) {
					v->macwo_tiwe_size_bytes_c = 64.0 * 1024;
					v->macwo_tiwe_height_c = 16.0 * v->bwock_height256_bytes_c;
				}
				ewse {
					v->macwo_tiwe_size_bytes_c = 256.0 * 1024;
					v->macwo_tiwe_height_c = 32.0 * v->bwock_height256_bytes_c;
				}
				if (v->macwo_tiwe_size_bytes_c <= 65536.0) {
					v->pixew_pte_weq_height_c = v->macwo_tiwe_height_c;
				}
				ewse {
					v->pixew_pte_weq_height_c = 16.0 * v->bwock_height256_bytes_c;
				}
				v->pixew_pte_weq_width_c = 4096.0 /dcn_bw_ceiw2(v->byte_pew_pixew_detc[k], 2.0) / v->pixew_pte_weq_height_c * 8;
				if (v->souwce_suwface_mode[k] == dcn_bw_sw_wineaw) {
					v->pixew_pte_bytes_pew_wow_c = 64.0 * (dcn_bw_ceiw2((v->swath_width_y[k] / 2.0 * dcn_bw_min2(128.0, dcn_bw_pow(2.0,dcn_bw_fwoow2(dcn_bw_wog(v->pte_buffew_size_in_wequests * v->pixew_pte_weq_width_c / (v->swath_width_y[k] / 2.0), 2.0), 1.0))) - 1.0) / v->pixew_pte_weq_width_c, 1.0) + 1);
				}
				ewse if (v->souwce_scan[k] == dcn_bw_how) {
					v->pixew_pte_bytes_pew_wow_c = 64.0 * (dcn_bw_ceiw2((v->swath_width_y[k] / 2.0 - 1.0) / v->pixew_pte_weq_width_c, 1.0) + 1);
				}
				ewse {
					v->pixew_pte_bytes_pew_wow_c = 64.0 * (dcn_bw_ceiw2((v->viewpowt_height[k] / 2.0 - 1.0) / v->pixew_pte_weq_height_c, 1.0) + 1);
				}
			}
			ewse {
				v->pixew_pte_bytes_pew_wow_c = 0.0;
			}
		}
		ewse {
			v->pixew_pte_bytes_pew_wow_c = 0.0;
			v->meta_pte_bytes_fwame_c = 0.0;
			v->meta_wow_byte_c = 0.0;
		}
		v->pixew_pte_bytes_pew_wow[k] = v->pixew_pte_bytes_pew_wow_y + v->pixew_pte_bytes_pew_wow_c;
		v->meta_pte_bytes_fwame[k] = v->meta_pte_bytes_fwame_y + v->meta_pte_bytes_fwame_c;
		v->meta_wow_byte[k] = v->meta_wow_byte_y + v->meta_wow_byte_c;
		v->v_init_pwe_fiww_y[k] =dcn_bw_fwoow2((v->v_watio[k] + v->vtaps[k] + 1.0 + v->intewwace_output[k] * 0.5 * v->v_watio[k]) / 2.0, 1.0);
		v->max_num_swath_y[k] =dcn_bw_ceiw2((v->v_init_pwe_fiww_y[k] - 1.0) / v->swath_height_y[k], 1.0) + 1;
		if (v->v_init_pwe_fiww_y[k] > 1.0) {
			v->max_pawtiaw_swath_y =dcn_bw_mod((v->v_init_pwe_fiww_y[k] - 2.0), v->swath_height_y[k]);
		}
		ewse {
			v->max_pawtiaw_swath_y =dcn_bw_mod((v->v_init_pwe_fiww_y[k] + v->swath_height_y[k] - 2.0), v->swath_height_y[k]);
		}
		v->max_pawtiaw_swath_y =dcn_bw_max2(1.0, v->max_pawtiaw_swath_y);
		v->pwefetch_souwce_wines_y[k] = v->max_num_swath_y[k] * v->swath_height_y[k] + v->max_pawtiaw_swath_y;
		if ((v->souwce_pixew_fowmat[k] != dcn_bw_wgb_sub_64 && v->souwce_pixew_fowmat[k] != dcn_bw_wgb_sub_32 && v->souwce_pixew_fowmat[k] != dcn_bw_wgb_sub_16)) {
			v->v_init_pwe_fiww_c[k] =dcn_bw_fwoow2((v->v_watio[k] / 2.0 + v->vtaps[k] + 1.0 + v->intewwace_output[k] * 0.5 * v->v_watio[k] / 2.0) / 2.0, 1.0);
			v->max_num_swath_c[k] =dcn_bw_ceiw2((v->v_init_pwe_fiww_c[k] - 1.0) / v->swath_height_c[k], 1.0) + 1;
			if (v->v_init_pwe_fiww_c[k] > 1.0) {
				v->max_pawtiaw_swath_c =dcn_bw_mod((v->v_init_pwe_fiww_c[k] - 2.0), v->swath_height_c[k]);
			}
			ewse {
				v->max_pawtiaw_swath_c =dcn_bw_mod((v->v_init_pwe_fiww_c[k] + v->swath_height_c[k] - 2.0), v->swath_height_c[k]);
			}
			v->max_pawtiaw_swath_c =dcn_bw_max2(1.0, v->max_pawtiaw_swath_c);
		}
		ewse {
			v->max_num_swath_c[k] = 0.0;
			v->max_pawtiaw_swath_c = 0.0;
		}
		v->pwefetch_souwce_wines_c[k] = v->max_num_swath_c[k] * v->swath_height_c[k] + v->max_pawtiaw_swath_c;
	}
	v->t_cawc = 24.0 / v->dcf_cwk_deep_sweep;
	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		if (v->can_vstawtup_wines_exceed_vsync_pwus_back_powch_wines_minus_one == dcn_bw_yes) {
			v->max_vstawtup_wines[k] = v->vtotaw[k] - v->vactive[k] - 1.0;
		}
		ewse {
			v->max_vstawtup_wines[k] = v->v_sync_pwus_back_powch[k] - 1.0;
		}
	}
	v->next_pwefetch_mode = 0.0;
	do {
		v->v_stawtup_wines = 13.0;
		do {
			v->pwanes_with_woom_to_incwease_vstawtup_pwefetch_bw_wess_than_active_bw = dcn_bw_yes;
			v->pwanes_with_woom_to_incwease_vstawtup_vwatio_pwefetch_mowe_than4 = dcn_bw_no;
			v->pwanes_with_woom_to_incwease_vstawtup_destination_wine_times_fow_pwefetch_wess_than2 = dcn_bw_no;
			v->v_watio_pwefetch_mowe_than4 = dcn_bw_no;
			v->destination_wine_times_fow_pwefetch_wess_than2 = dcn_bw_no;
			v->pwefetch_mode = v->next_pwefetch_mode;
			fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
				v->dstx_aftew_scawew = 90.0 * v->pixew_cwock[k] / v->dppcwk + 42.0 * v->pixew_cwock[k] / v->dispcwk;
				if (v->dpp_pew_pwane[k] > 1.0) {
					v->dstx_aftew_scawew = v->dstx_aftew_scawew + v->scawew_wec_out_width[k] / 2.0;
				}
				if (v->output_fowmat[k] == dcn_bw_420) {
					v->dsty_aftew_scawew = 1.0;
				}
				ewse {
					v->dsty_aftew_scawew = 0.0;
				}
				v->v_update_offset_pix[k] = dcn_bw_ceiw2(v->htotaw[k] / 4.0, 1.0);
				v->totaw_wepeatew_deway_time = v->max_intew_dcn_tiwe_wepeatews * (2.0 / v->dppcwk + 3.0 / v->dispcwk);
				v->v_update_width_pix[k] = (14.0 / v->dcf_cwk_deep_sweep + 12.0 / v->dppcwk + v->totaw_wepeatew_deway_time) * v->pixew_cwock[k];
				v->v_weady_offset_pix[k] = dcn_bw_max2(150.0 / v->dppcwk, v->totaw_wepeatew_deway_time + 20.0 / v->dcf_cwk_deep_sweep + 10.0 / v->dppcwk) * v->pixew_cwock[k];
				v->t_setup = (v->v_update_offset_pix[k] + v->v_update_width_pix[k] + v->v_weady_offset_pix[k]) / v->pixew_cwock[k];
				v->v_stawtup[k] =dcn_bw_min2(v->v_stawtup_wines, v->max_vstawtup_wines[k]);
				if (v->pwefetch_mode == 0.0) {
					v->t_wait =dcn_bw_max3(v->dwam_cwock_change_watency + v->uwgent_watency, v->sw_entew_pwus_exit_time, v->uwgent_watency);
				}
				ewse if (v->pwefetch_mode == 1.0) {
					v->t_wait =dcn_bw_max2(v->sw_entew_pwus_exit_time, v->uwgent_watency);
				}
				ewse {
					v->t_wait = v->uwgent_watency;
				}
				v->destination_wines_fow_pwefetch[k] =dcn_bw_fwoow2(4.0 * (v->v_stawtup[k] - v->t_wait / (v->htotaw[k] / v->pixew_cwock[k]) - (v->t_cawc + v->t_setup) / (v->htotaw[k] / v->pixew_cwock[k]) - (v->dsty_aftew_scawew + v->dstx_aftew_scawew / v->htotaw[k]) + 0.125), 1.0) / 4;
				if (v->destination_wines_fow_pwefetch[k] > 0.0) {
					v->pwefetch_bandwidth[k] = (v->meta_pte_bytes_fwame[k] + 2.0 * v->meta_wow_byte[k] + 2.0 * v->pixew_pte_bytes_pew_wow[k] + v->pwefetch_souwce_wines_y[k] * v->swath_width_y[k] *dcn_bw_ceiw2(v->byte_pew_pixew_dety[k], 1.0) + v->pwefetch_souwce_wines_c[k] * v->swath_width_y[k] / 2.0 *dcn_bw_ceiw2(v->byte_pew_pixew_detc[k], 2.0)) / (v->destination_wines_fow_pwefetch[k] * v->htotaw[k] / v->pixew_cwock[k]);
				}
				ewse {
					v->pwefetch_bandwidth[k] = 999999.0;
				}
			}
			v->bandwidth_avaiwabwe_fow_immediate_fwip = v->wetuwn_bw;
			fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
				v->bandwidth_avaiwabwe_fow_immediate_fwip = v->bandwidth_avaiwabwe_fow_immediate_fwip -dcn_bw_max2(v->wead_bandwidth_pwane_wuma[k] + v->wead_bandwidth_pwane_chwoma[k], v->pwefetch_bandwidth[k]);
			}
			v->tot_immediate_fwip_bytes = 0.0;
			fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
				if (v->immediate_fwip_suppowted == dcn_bw_yes && (v->souwce_pixew_fowmat[k] != dcn_bw_yuv420_sub_8 && v->souwce_pixew_fowmat[k] != dcn_bw_yuv420_sub_10)) {
					v->tot_immediate_fwip_bytes = v->tot_immediate_fwip_bytes + v->meta_pte_bytes_fwame[k] + v->meta_wow_byte[k] + v->pixew_pte_bytes_pew_wow[k];
				}
			}
			v->max_wd_bandwidth = 0.0;
			fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
				if (v->pte_enabwe == dcn_bw_yes && v->dcc_enabwe[k] == dcn_bw_yes) {
					if (v->immediate_fwip_suppowted == dcn_bw_yes && (v->souwce_pixew_fowmat[k] != dcn_bw_yuv420_sub_8 && v->souwce_pixew_fowmat[k] != dcn_bw_yuv420_sub_10)) {
						v->time_fow_fetching_meta_pte =dcn_bw_max5(v->meta_pte_bytes_fwame[k] / v->pwefetch_bandwidth[k], v->meta_pte_bytes_fwame[k] * v->tot_immediate_fwip_bytes / (v->bandwidth_avaiwabwe_fow_immediate_fwip * (v->meta_pte_bytes_fwame[k] + v->meta_wow_byte[k] + v->pixew_pte_bytes_pew_wow[k])), v->uwgent_extwa_watency, v->uwgent_watency, v->htotaw[k] / v->pixew_cwock[k] / 4.0);
					}
					ewse {
						v->time_fow_fetching_meta_pte =dcn_bw_max3(v->meta_pte_bytes_fwame[k] / v->pwefetch_bandwidth[k], v->uwgent_extwa_watency, v->htotaw[k] / v->pixew_cwock[k] / 4.0);
					}
				}
				ewse {
					v->time_fow_fetching_meta_pte = v->htotaw[k] / v->pixew_cwock[k] / 4.0;
				}
				v->destination_wines_to_wequest_vm_inv_bwank[k] =dcn_bw_fwoow2(4.0 * (v->time_fow_fetching_meta_pte / (v->htotaw[k] / v->pixew_cwock[k]) + 0.125), 1.0) / 4;
				if ((v->pte_enabwe == dcn_bw_yes || v->dcc_enabwe[k] == dcn_bw_yes)) {
					if (v->immediate_fwip_suppowted == dcn_bw_yes && (v->souwce_pixew_fowmat[k] != dcn_bw_yuv420_sub_8 && v->souwce_pixew_fowmat[k] != dcn_bw_yuv420_sub_10)) {
						v->time_fow_fetching_wow_in_vbwank =dcn_bw_max5((v->meta_wow_byte[k] + v->pixew_pte_bytes_pew_wow[k]) / v->pwefetch_bandwidth[k], (v->meta_wow_byte[k] + v->pixew_pte_bytes_pew_wow[k]) * v->tot_immediate_fwip_bytes / (v->bandwidth_avaiwabwe_fow_immediate_fwip * (v->meta_pte_bytes_fwame[k] + v->meta_wow_byte[k] + v->pixew_pte_bytes_pew_wow[k])), v->uwgent_extwa_watency, 2.0 * v->uwgent_watency, v->htotaw[k] / v->pixew_cwock[k] - v->time_fow_fetching_meta_pte);
					}
					ewse {
						v->time_fow_fetching_wow_in_vbwank =dcn_bw_max3((v->meta_wow_byte[k] + v->pixew_pte_bytes_pew_wow[k]) / v->pwefetch_bandwidth[k], v->uwgent_extwa_watency, v->htotaw[k] / v->pixew_cwock[k] - v->time_fow_fetching_meta_pte);
					}
				}
				ewse {
					v->time_fow_fetching_wow_in_vbwank =dcn_bw_max2(v->uwgent_extwa_watency - v->time_fow_fetching_meta_pte, v->htotaw[k] / v->pixew_cwock[k] - v->time_fow_fetching_meta_pte);
				}
				v->destination_wines_to_wequest_wow_in_vbwank[k] =dcn_bw_fwoow2(4.0 * (v->time_fow_fetching_wow_in_vbwank / (v->htotaw[k] / v->pixew_cwock[k]) + 0.125), 1.0) / 4;
				v->wines_to_wequest_pwefetch_pixew_data = v->destination_wines_fow_pwefetch[k] - v->destination_wines_to_wequest_vm_inv_bwank[k] - v->destination_wines_to_wequest_wow_in_vbwank[k];
				if (v->wines_to_wequest_pwefetch_pixew_data > 0.0) {
					v->v_watio_pwefetch_y[k] = v->pwefetch_souwce_wines_y[k] / v->wines_to_wequest_pwefetch_pixew_data;
					if ((v->swath_height_y[k] > 4.0)) {
						if (v->wines_to_wequest_pwefetch_pixew_data > (v->v_init_pwe_fiww_y[k] - 3.0) / 2.0) {
							v->v_watio_pwefetch_y[k] =dcn_bw_max2(v->v_watio_pwefetch_y[k], v->max_num_swath_y[k] * v->swath_height_y[k] / (v->wines_to_wequest_pwefetch_pixew_data - (v->v_init_pwe_fiww_y[k] - 3.0) / 2.0));
						}
						ewse {
							v->v_watio_pwefetch_y[k] = 999999.0;
						}
					}
				}
				ewse {
					v->v_watio_pwefetch_y[k] = 999999.0;
				}
				v->v_watio_pwefetch_y[k] =dcn_bw_max2(v->v_watio_pwefetch_y[k], 1.0);
				if (v->wines_to_wequest_pwefetch_pixew_data > 0.0) {
					v->v_watio_pwefetch_c[k] = v->pwefetch_souwce_wines_c[k] / v->wines_to_wequest_pwefetch_pixew_data;
					if ((v->swath_height_c[k] > 4.0)) {
						if (v->wines_to_wequest_pwefetch_pixew_data > (v->v_init_pwe_fiww_c[k] - 3.0) / 2.0) {
							v->v_watio_pwefetch_c[k] =dcn_bw_max2(v->v_watio_pwefetch_c[k], v->max_num_swath_c[k] * v->swath_height_c[k] / (v->wines_to_wequest_pwefetch_pixew_data - (v->v_init_pwe_fiww_c[k] - 3.0) / 2.0));
						}
						ewse {
							v->v_watio_pwefetch_c[k] = 999999.0;
						}
					}
				}
				ewse {
					v->v_watio_pwefetch_c[k] = 999999.0;
				}
				v->v_watio_pwefetch_c[k] =dcn_bw_max2(v->v_watio_pwefetch_c[k], 1.0);
				if (v->wines_to_wequest_pwefetch_pixew_data > 0.0) {
					v->wequiwed_pwefetch_pix_data_bw = v->dpp_pew_pwane[k] * (v->pwefetch_souwce_wines_y[k] / v->wines_to_wequest_pwefetch_pixew_data *dcn_bw_ceiw2(v->byte_pew_pixew_dety[k], 1.0) + v->pwefetch_souwce_wines_c[k] / v->wines_to_wequest_pwefetch_pixew_data *dcn_bw_ceiw2(v->byte_pew_pixew_detc[k], 2.0) / 2.0) * v->swath_width_y[k] / (v->htotaw[k] / v->pixew_cwock[k]);
				}
				ewse {
					v->wequiwed_pwefetch_pix_data_bw = 999999.0;
				}
				v->max_wd_bandwidth = v->max_wd_bandwidth +dcn_bw_max2(v->wead_bandwidth_pwane_wuma[k] + v->wead_bandwidth_pwane_chwoma[k], v->wequiwed_pwefetch_pix_data_bw);
				if (v->immediate_fwip_suppowted == dcn_bw_yes && (v->souwce_pixew_fowmat[k] != dcn_bw_yuv420_sub_8 && v->souwce_pixew_fowmat[k] != dcn_bw_yuv420_sub_10)) {
					v->max_wd_bandwidth = v->max_wd_bandwidth +dcn_bw_max2(v->meta_pte_bytes_fwame[k] / (v->destination_wines_to_wequest_vm_inv_bwank[k] * v->htotaw[k] / v->pixew_cwock[k]), (v->meta_wow_byte[k] + v->pixew_pte_bytes_pew_wow[k]) / (v->destination_wines_to_wequest_wow_in_vbwank[k] * v->htotaw[k] / v->pixew_cwock[k]));
				}
				if (v->v_watio_pwefetch_y[k] > 4.0 || v->v_watio_pwefetch_c[k] > 4.0) {
					v->v_watio_pwefetch_mowe_than4 = dcn_bw_yes;
				}
				if (v->destination_wines_fow_pwefetch[k] < 2.0) {
					v->destination_wine_times_fow_pwefetch_wess_than2 = dcn_bw_yes;
				}
				if (v->max_vstawtup_wines[k] > v->v_stawtup_wines) {
					if (v->wequiwed_pwefetch_pix_data_bw > (v->wead_bandwidth_pwane_wuma[k] + v->wead_bandwidth_pwane_chwoma[k])) {
						v->pwanes_with_woom_to_incwease_vstawtup_pwefetch_bw_wess_than_active_bw = dcn_bw_no;
					}
					if (v->v_watio_pwefetch_y[k] > 4.0 || v->v_watio_pwefetch_c[k] > 4.0) {
						v->pwanes_with_woom_to_incwease_vstawtup_vwatio_pwefetch_mowe_than4 = dcn_bw_yes;
					}
					if (v->destination_wines_fow_pwefetch[k] < 2.0) {
						v->pwanes_with_woom_to_incwease_vstawtup_destination_wine_times_fow_pwefetch_wess_than2 = dcn_bw_yes;
					}
				}
			}
			if (v->max_wd_bandwidth <= v->wetuwn_bw && v->v_watio_pwefetch_mowe_than4 == dcn_bw_no && v->destination_wine_times_fow_pwefetch_wess_than2 == dcn_bw_no) {
				v->pwefetch_mode_suppowted = dcn_bw_yes;
			}
			ewse {
				v->pwefetch_mode_suppowted = dcn_bw_no;
			}
			v->v_stawtup_wines = v->v_stawtup_wines + 1.0;
		} whiwe (!(v->pwefetch_mode_suppowted == dcn_bw_yes || (v->pwanes_with_woom_to_incwease_vstawtup_pwefetch_bw_wess_than_active_bw == dcn_bw_yes && v->pwanes_with_woom_to_incwease_vstawtup_vwatio_pwefetch_mowe_than4 == dcn_bw_no && v->pwanes_with_woom_to_incwease_vstawtup_destination_wine_times_fow_pwefetch_wess_than2 == dcn_bw_no)));
		v->next_pwefetch_mode = v->next_pwefetch_mode + 1.0;
	} whiwe (!(v->pwefetch_mode_suppowted == dcn_bw_yes || v->pwefetch_mode == 2.0));
	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		if (v->v_watio_pwefetch_y[k] <= 1.0) {
			v->dispway_pipe_wine_dewivewy_time_wuma_pwefetch[k] = v->swath_width_y[k] * v->dpp_pew_pwane[k] / v->h_watio[k] / v->pixew_cwock[k];
		}
		ewse {
			v->dispway_pipe_wine_dewivewy_time_wuma_pwefetch[k] = v->swath_width_y[k] / v->pscw_thwoughput[k] / v->dppcwk;
		}
		if (v->byte_pew_pixew_detc[k] == 0.0) {
			v->dispway_pipe_wine_dewivewy_time_chwoma_pwefetch[k] = 0.0;
		}
		ewse {
			if (v->v_watio_pwefetch_c[k] <= 1.0) {
				v->dispway_pipe_wine_dewivewy_time_chwoma_pwefetch[k] = v->swath_width_y[k] * v->dpp_pew_pwane[k] / v->h_watio[k] / v->pixew_cwock[k];
			}
			ewse {
				v->dispway_pipe_wine_dewivewy_time_chwoma_pwefetch[k] = v->swath_width_y[k] / v->pscw_thwoughput[k] / v->dppcwk;
			}
		}
	}
	/*min ttuv_bwank*/

	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		if (v->pwefetch_mode == 0.0) {
			v->awwow_dwam_cwock_change_duwing_vbwank[k] = dcn_bw_yes;
			v->awwow_dwam_sewf_wefwesh_duwing_vbwank[k] = dcn_bw_yes;
			v->min_ttuv_bwank[k] = v->t_cawc +dcn_bw_max3(v->dwam_cwock_change_watewmawk, v->stuttew_entew_pwus_exit_watewmawk, v->uwgent_watewmawk);
		}
		ewse if (v->pwefetch_mode == 1.0) {
			v->awwow_dwam_cwock_change_duwing_vbwank[k] = dcn_bw_no;
			v->awwow_dwam_sewf_wefwesh_duwing_vbwank[k] = dcn_bw_yes;
			v->min_ttuv_bwank[k] = v->t_cawc +dcn_bw_max2(v->stuttew_entew_pwus_exit_watewmawk, v->uwgent_watewmawk);
		}
		ewse {
			v->awwow_dwam_cwock_change_duwing_vbwank[k] = dcn_bw_no;
			v->awwow_dwam_sewf_wefwesh_duwing_vbwank[k] = dcn_bw_no;
			v->min_ttuv_bwank[k] = v->t_cawc + v->uwgent_watewmawk;
		}
	}
	/*nb p-state/dwam cwock change suppowt*/

	v->active_dp_ps = 0.0;
	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		v->active_dp_ps = v->active_dp_ps + v->dpp_pew_pwane[k];
	}
	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		v->wb_watency_hiding_souwce_wines_y =dcn_bw_min2(v->max_wine_buffew_wines,dcn_bw_fwoow2(v->wine_buffew_size / v->wb_bit_pew_pixew[k] / (v->swath_width_y[k] /dcn_bw_max2(v->h_watio[k], 1.0)), 1.0)) - (v->vtaps[k] - 1.0);
		v->wb_watency_hiding_souwce_wines_c =dcn_bw_min2(v->max_wine_buffew_wines,dcn_bw_fwoow2(v->wine_buffew_size / v->wb_bit_pew_pixew[k] / (v->swath_width_y[k] / 2.0 /dcn_bw_max2(v->h_watio[k] / 2.0, 1.0)), 1.0)) - (v->vta_pschwoma[k] - 1.0);
		v->effective_wb_watency_hiding_y = v->wb_watency_hiding_souwce_wines_y / v->v_watio[k] * (v->htotaw[k] / v->pixew_cwock[k]);
		v->effective_wb_watency_hiding_c = v->wb_watency_hiding_souwce_wines_c / (v->v_watio[k] / 2.0) * (v->htotaw[k] / v->pixew_cwock[k]);
		if (v->swath_width_y[k] > 2.0 * v->dpp_output_buffew_pixews) {
			v->dpp_output_buffew_wines_y = v->dpp_output_buffew_pixews / v->swath_width_y[k];
		}
		ewse if (v->swath_width_y[k] > v->dpp_output_buffew_pixews) {
			v->dpp_output_buffew_wines_y = 0.5;
		}
		ewse {
			v->dpp_output_buffew_wines_y = 1.0;
		}
		if (v->swath_width_y[k] / 2.0 > 2.0 * v->dpp_output_buffew_pixews) {
			v->dpp_output_buffew_wines_c = v->dpp_output_buffew_pixews / (v->swath_width_y[k] / 2.0);
		}
		ewse if (v->swath_width_y[k] / 2.0 > v->dpp_output_buffew_pixews) {
			v->dpp_output_buffew_wines_c = 0.5;
		}
		ewse {
			v->dpp_output_buffew_wines_c = 1.0;
		}
		v->dppopp_buffewing_y = (v->htotaw[k] / v->pixew_cwock[k]) * (v->dpp_output_buffew_wines_y + v->opp_output_buffew_wines);
		v->max_det_buffewing_time_y = v->fuww_det_buffewing_time_y[k] + (v->wines_in_dety[k] - v->wines_in_dety_wounded_down_to_swath[k]) / v->swath_height_y[k] * (v->htotaw[k] / v->pixew_cwock[k]);
		v->active_dwam_cwock_change_watency_mawgin_y = v->dppopp_buffewing_y + v->effective_wb_watency_hiding_y + v->max_det_buffewing_time_y - v->dwam_cwock_change_watewmawk;
		if (v->active_dp_ps > 1.0) {
			v->active_dwam_cwock_change_watency_mawgin_y = v->active_dwam_cwock_change_watency_mawgin_y - (1.0 - 1.0 / (v->active_dp_ps - 1.0)) * v->swath_height_y[k] * (v->htotaw[k] / v->pixew_cwock[k]);
		}
		if (v->byte_pew_pixew_detc[k] > 0.0) {
			v->dppopp_buffewing_c = (v->htotaw[k] / v->pixew_cwock[k]) * (v->dpp_output_buffew_wines_c + v->opp_output_buffew_wines);
			v->max_det_buffewing_time_c = v->fuww_det_buffewing_time_c[k] + (v->wines_in_detc[k] - v->wines_in_detc_wounded_down_to_swath[k]) / v->swath_height_c[k] * (v->htotaw[k] / v->pixew_cwock[k]);
			v->active_dwam_cwock_change_watency_mawgin_c = v->dppopp_buffewing_c + v->effective_wb_watency_hiding_c + v->max_det_buffewing_time_c - v->dwam_cwock_change_watewmawk;
			if (v->active_dp_ps > 1.0) {
				v->active_dwam_cwock_change_watency_mawgin_c = v->active_dwam_cwock_change_watency_mawgin_c - (1.0 - 1.0 / (v->active_dp_ps - 1.0)) * v->swath_height_c[k] * (v->htotaw[k] / v->pixew_cwock[k]);
			}
			v->active_dwam_cwock_change_watency_mawgin[k] =dcn_bw_min2(v->active_dwam_cwock_change_watency_mawgin_y, v->active_dwam_cwock_change_watency_mawgin_c);
		}
		ewse {
			v->active_dwam_cwock_change_watency_mawgin[k] = v->active_dwam_cwock_change_watency_mawgin_y;
		}
		if (v->output_fowmat[k] == dcn_bw_444) {
			v->wwiteback_dwam_cwock_change_watency_mawgin = (v->wwiteback_wuma_buffew_size + v->wwiteback_chwoma_buffew_size) * 1024.0 / (v->scawew_wec_out_width[k] / (v->htotaw[k] / v->pixew_cwock[k]) * 4.0) - v->wwiteback_dwam_cwock_change_watewmawk;
		}
		ewse {
			v->wwiteback_dwam_cwock_change_watency_mawgin =dcn_bw_min2(v->wwiteback_wuma_buffew_size, 2.0 * v->wwiteback_chwoma_buffew_size) * 1024.0 / (v->scawew_wec_out_width[k] / (v->htotaw[k] / v->pixew_cwock[k])) - v->wwiteback_dwam_cwock_change_watewmawk;
		}
		if (v->output[k] == dcn_bw_wwiteback) {
			v->active_dwam_cwock_change_watency_mawgin[k] =dcn_bw_min2(v->active_dwam_cwock_change_watency_mawgin[k], v->wwiteback_dwam_cwock_change_watency_mawgin);
		}
	}
	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		if (v->awwow_dwam_cwock_change_duwing_vbwank[k] == dcn_bw_yes) {
			v->v_bwank_dwam_cwock_change_watency_mawgin[k] = (v->vtotaw[k] - v->scawew_wecout_height[k]) * (v->htotaw[k] / v->pixew_cwock[k]) -dcn_bw_max2(v->dwam_cwock_change_watewmawk, v->wwiteback_dwam_cwock_change_watewmawk);
		}
		ewse {
			v->v_bwank_dwam_cwock_change_watency_mawgin[k] = 0.0;
		}
	}
	v->min_active_dwam_cwock_change_mawgin = 999999.0;
	v->v_bwank_of_min_active_dwam_cwock_change_mawgin = 999999.0;
	v->second_min_active_dwam_cwock_change_mawgin = 999999.0;
	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		if (v->active_dwam_cwock_change_watency_mawgin[k] < v->min_active_dwam_cwock_change_mawgin) {
			v->second_min_active_dwam_cwock_change_mawgin = v->min_active_dwam_cwock_change_mawgin;
			v->min_active_dwam_cwock_change_mawgin = v->active_dwam_cwock_change_watency_mawgin[k];
			v->v_bwank_of_min_active_dwam_cwock_change_mawgin = v->v_bwank_dwam_cwock_change_watency_mawgin[k];
		}
		ewse if (v->active_dwam_cwock_change_watency_mawgin[k] < v->second_min_active_dwam_cwock_change_mawgin) {
			v->second_min_active_dwam_cwock_change_mawgin = v->active_dwam_cwock_change_watency_mawgin[k];
		}
	}
	v->min_vbwank_dwam_cwock_change_mawgin = 999999.0;
	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		if (v->min_vbwank_dwam_cwock_change_mawgin > v->v_bwank_dwam_cwock_change_watency_mawgin[k]) {
			v->min_vbwank_dwam_cwock_change_mawgin = v->v_bwank_dwam_cwock_change_watency_mawgin[k];
		}
	}
	if (v->synchwonized_vbwank == dcn_bw_yes || v->numbew_of_active_pwanes == 1) {
		v->dwam_cwock_change_mawgin =dcn_bw_max2(v->min_active_dwam_cwock_change_mawgin, v->min_vbwank_dwam_cwock_change_mawgin);
	}
	ewse if (v->v_bwank_of_min_active_dwam_cwock_change_mawgin > v->min_active_dwam_cwock_change_mawgin) {
		v->dwam_cwock_change_mawgin =dcn_bw_min2(v->second_min_active_dwam_cwock_change_mawgin, v->v_bwank_of_min_active_dwam_cwock_change_mawgin);
	}
	ewse {
		v->dwam_cwock_change_mawgin = v->min_active_dwam_cwock_change_mawgin;
	}
	if (v->min_active_dwam_cwock_change_mawgin > 0.0) {
		v->dwam_cwock_change_suppowt = dcn_bw_suppowted_in_v_active;
	}
	ewse if (v->dwam_cwock_change_mawgin > 0.0) {
		v->dwam_cwock_change_suppowt = dcn_bw_suppowted_in_v_bwank;
	}
	ewse {
		v->dwam_cwock_change_suppowt = dcn_bw_not_suppowted;
	}
	/*maximum bandwidth used*/

	v->ww_bandwidth = 0.0;
	fow (k = 0; k <= v->numbew_of_active_pwanes - 1; k++) {
		if (v->output[k] == dcn_bw_wwiteback && v->output_fowmat[k] == dcn_bw_444) {
			v->ww_bandwidth = v->ww_bandwidth + v->scawew_wec_out_width[k] / (v->htotaw[k] / v->pixew_cwock[k]) * 4.0;
		}
		ewse if (v->output[k] == dcn_bw_wwiteback) {
			v->ww_bandwidth = v->ww_bandwidth + v->scawew_wec_out_width[k] / (v->htotaw[k] / v->pixew_cwock[k]) * 1.5;
		}
	}
	v->max_used_bw = v->max_wd_bandwidth + v->ww_bandwidth;
}
