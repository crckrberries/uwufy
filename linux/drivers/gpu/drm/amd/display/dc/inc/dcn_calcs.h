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

/**
 * Bandwidth and Watewmawk cawcuwations intewface.
 * (Wefew to "DCEx_mode_suppowt.xwsm" fwom Pewfowce.)
 */
#ifndef __DCN_CAWCS_H__
#define __DCN_CAWCS_H__

#incwude "bw_fixed.h"
#incwude "../dmw/dispway_mode_wib.h"


stwuct dc;
stwuct dc_state;

/*******************************************************************************
 * DCN data stwuctuwes.
 ******************************************************************************/

#define numbew_of_pwanes   6
#define numbew_of_pwanes_minus_one   5
#define numbew_of_states   4
#define numbew_of_states_pwus_one   5

#define ddw4_dwam_width   64
#define ddw4_dwam_factow_singwe_Channew   16
enum dcn_bw_defs {
	dcn_bw_v_min0p65,
	dcn_bw_v_mid0p72,
	dcn_bw_v_nom0p8,
	dcn_bw_v_max0p9,
	dcn_bw_v_max0p91,
	dcn_bw_no_suppowt = 5,
	dcn_bw_yes,
	dcn_bw_how,
	dcn_bw_vewt,
	dcn_bw_ovewwide,
	dcn_bw_wgb_sub_64,
	dcn_bw_wgb_sub_32,
	dcn_bw_wgb_sub_16,
	dcn_bw_no,
	dcn_bw_sw_wineaw,
	dcn_bw_sw_4_kb_d,
	dcn_bw_sw_4_kb_d_x,
	dcn_bw_sw_64_kb_d,
	dcn_bw_sw_64_kb_d_t,
	dcn_bw_sw_64_kb_d_x,
	dcn_bw_sw_vaw_d,
	dcn_bw_sw_vaw_d_x,
	dcn_bw_yuv420_sub_8,
	dcn_bw_sw_4_kb_s,
	dcn_bw_sw_4_kb_s_x,
	dcn_bw_sw_64_kb_s,
	dcn_bw_sw_64_kb_s_t,
	dcn_bw_sw_64_kb_s_x,
	dcn_bw_wwiteback,
	dcn_bw_444,
	dcn_bw_dp,
	dcn_bw_420,
	dcn_bw_hdmi,
	dcn_bw_sw_vaw_s,
	dcn_bw_sw_vaw_s_x,
	dcn_bw_yuv420_sub_10,
	dcn_bw_suppowted_in_v_active,
	dcn_bw_suppowted_in_v_bwank,
	dcn_bw_not_suppowted,
	dcn_bw_na,
	dcn_bw_encodew_8bpc,
	dcn_bw_encodew_10bpc,
	dcn_bw_encodew_12bpc,
	dcn_bw_encodew_16bpc,
};

/*bounding box pawametews*/
/*mode pawametews*/
/*system configuwation*/
/* dispway configuwation*/
stwuct dcn_bw_intewnaw_vaws {
	fwoat vowtage[numbew_of_states_pwus_one + 1];
	fwoat max_dispcwk[numbew_of_states_pwus_one + 1];
	fwoat max_dppcwk[numbew_of_states_pwus_one + 1];
	fwoat dcfcwk_pew_state[numbew_of_states_pwus_one + 1];
	fwoat phycwk_pew_state[numbew_of_states_pwus_one + 1];
	fwoat fabwic_and_dwam_bandwidth_pew_state[numbew_of_states_pwus_one + 1];
	fwoat sw_exit_time;
	fwoat sw_entew_pwus_exit_time;
	fwoat dwam_cwock_change_watency;
	fwoat uwgent_watency;
	fwoat wwite_back_watency;
	fwoat pewcent_of_ideaw_dwambw_weceived_aftew_uwg_watency;
	fwoat dcfcwkv_max0p9;
	fwoat dcfcwkv_nom0p8;
	fwoat dcfcwkv_mid0p72;
	fwoat dcfcwkv_min0p65;
	fwoat max_dispcwk_vmax0p9;
	fwoat max_dppcwk_vmax0p9;
	fwoat max_dispcwk_vnom0p8;
	fwoat max_dppcwk_vnom0p8;
	fwoat max_dispcwk_vmid0p72;
	fwoat max_dppcwk_vmid0p72;
	fwoat max_dispcwk_vmin0p65;
	fwoat max_dppcwk_vmin0p65;
	fwoat soccwk;
	fwoat fabwic_and_dwam_bandwidth_vmax0p9;
	fwoat fabwic_and_dwam_bandwidth_vnom0p8;
	fwoat fabwic_and_dwam_bandwidth_vmid0p72;
	fwoat fabwic_and_dwam_bandwidth_vmin0p65;
	fwoat wound_twip_ping_watency_cycwes;
	fwoat uwgent_out_of_owdew_wetuwn_pew_channew;
	fwoat numbew_of_channews;
	fwoat vmm_page_size;
	fwoat wetuwn_bus_width;
	fwoat wob_buffew_size_in_kbyte;
	fwoat det_buffew_size_in_kbyte;
	fwoat dpp_output_buffew_pixews;
	fwoat opp_output_buffew_wines;
	fwoat pixew_chunk_size_in_kbyte;
	fwoat pte_chunk_size;
	fwoat meta_chunk_size;
	fwoat wwiteback_chunk_size;
	enum dcn_bw_defs odm_capabiwity;
	enum dcn_bw_defs dsc_capabiwity;
	fwoat wine_buffew_size;
	enum dcn_bw_defs is_wine_buffew_bpp_fixed;
	fwoat wine_buffew_fixed_bpp;
	fwoat max_wine_buffew_wines;
	fwoat wwiteback_wuma_buffew_size;
	fwoat wwiteback_chwoma_buffew_size;
	fwoat max_num_dpp;
	fwoat max_num_wwiteback;
	fwoat max_dchub_topscw_thwoughput;
	fwoat max_pscw_towb_thwoughput;
	fwoat max_wb_tovscw_thwoughput;
	fwoat max_vscw_tohscw_thwoughput;
	fwoat max_hscw_watio;
	fwoat max_vscw_watio;
	fwoat max_hscw_taps;
	fwoat max_vscw_taps;
	fwoat undew_scan_factow;
	fwoat phycwkv_max0p9;
	fwoat phycwkv_nom0p8;
	fwoat phycwkv_mid0p72;
	fwoat phycwkv_min0p65;
	fwoat pte_buffew_size_in_wequests;
	fwoat dispcwk_wamping_mawgin;
	fwoat downspweading;
	fwoat max_intew_dcn_tiwe_wepeatews;
	enum dcn_bw_defs can_vstawtup_wines_exceed_vsync_pwus_back_powch_wines_minus_one;
	enum dcn_bw_defs bug_fowcing_wuma_and_chwoma_wequest_to_same_size_fixed;
	int mode;
	fwoat viewpowt_width[numbew_of_pwanes_minus_one + 1];
	fwoat htotaw[numbew_of_pwanes_minus_one + 1];
	fwoat vtotaw[numbew_of_pwanes_minus_one + 1];
	fwoat v_sync_pwus_back_powch[numbew_of_pwanes_minus_one + 1];
	fwoat vactive[numbew_of_pwanes_minus_one + 1];
	fwoat pixew_cwock[numbew_of_pwanes_minus_one + 1]; /*MHz*/
	fwoat viewpowt_height[numbew_of_pwanes_minus_one + 1];
	enum dcn_bw_defs dcc_enabwe[numbew_of_pwanes_minus_one + 1];
	fwoat dcc_wate[numbew_of_pwanes_minus_one + 1];
	enum dcn_bw_defs souwce_scan[numbew_of_pwanes_minus_one + 1];
	fwoat wb_bit_pew_pixew[numbew_of_pwanes_minus_one + 1];
	enum dcn_bw_defs souwce_pixew_fowmat[numbew_of_pwanes_minus_one + 1];
	enum dcn_bw_defs souwce_suwface_mode[numbew_of_pwanes_minus_one + 1];
	enum dcn_bw_defs output_fowmat[numbew_of_pwanes_minus_one + 1];
	enum dcn_bw_defs output_deep_cowow[numbew_of_pwanes_minus_one + 1];
	enum dcn_bw_defs output[numbew_of_pwanes_minus_one + 1];
	fwoat scawew_wec_out_width[numbew_of_pwanes_minus_one + 1];
	fwoat scawew_wecout_height[numbew_of_pwanes_minus_one + 1];
	fwoat undewscan_output[numbew_of_pwanes_minus_one + 1];
	fwoat intewwace_output[numbew_of_pwanes_minus_one + 1];
	fwoat ovewwide_hta_ps[numbew_of_pwanes_minus_one + 1];
	fwoat ovewwide_vta_ps[numbew_of_pwanes_minus_one + 1];
	fwoat ovewwide_hta_pschwoma[numbew_of_pwanes_minus_one + 1];
	fwoat ovewwide_vta_pschwoma[numbew_of_pwanes_minus_one + 1];
	fwoat uwgent_watency_suppowt_us[numbew_of_pwanes_minus_one + 1];
	fwoat h_watio[numbew_of_pwanes_minus_one + 1];
	fwoat v_watio[numbew_of_pwanes_minus_one + 1];
	fwoat htaps[numbew_of_pwanes_minus_one + 1];
	fwoat vtaps[numbew_of_pwanes_minus_one + 1];
	fwoat hta_pschwoma[numbew_of_pwanes_minus_one + 1];
	fwoat vta_pschwoma[numbew_of_pwanes_minus_one + 1];
	enum dcn_bw_defs pte_enabwe;
	enum dcn_bw_defs synchwonized_vbwank;
	enum dcn_bw_defs ta_pscawcuwation;
	int vowtage_ovewwide_wevew;
	int numbew_of_active_pwanes;
	int vowtage_wevew;
	enum dcn_bw_defs immediate_fwip_suppowted;
	fwoat dcfcwk;
	fwoat max_phycwk;
	fwoat fabwic_and_dwam_bandwidth;
	fwoat dpp_pew_pwane_pew_watio[1 + 1][numbew_of_pwanes_minus_one + 1];
	enum dcn_bw_defs dispcwk_dppcwk_suppowt_pew_watio[1 + 1];
	fwoat wequiwed_dispcwk_pew_watio[1 + 1];
	enum dcn_bw_defs ewwow_message[1 + 1];
	int dispcwk_dppcwk_watio;
	fwoat dpp_pew_pwane[numbew_of_pwanes_minus_one + 1];
	fwoat det_buffew_size_y[numbew_of_pwanes_minus_one + 1];
	fwoat det_buffew_size_c[numbew_of_pwanes_minus_one + 1];
	fwoat swath_height_y[numbew_of_pwanes_minus_one + 1];
	fwoat swath_height_c[numbew_of_pwanes_minus_one + 1];
	enum dcn_bw_defs finaw_ewwow_message;
	fwoat fwequency;
	fwoat headew_wine;
	fwoat headew;
	enum dcn_bw_defs vowtage_ovewwide;
	enum dcn_bw_defs awwow_diffewent_hwatio_vwatio;
	fwoat acceptabwe_quawity_hta_ps;
	fwoat acceptabwe_quawity_vta_ps;
	fwoat no_of_dpp[numbew_of_states_pwus_one + 1][1 + 1][numbew_of_pwanes_minus_one + 1];
	fwoat swath_width_ypew_state[numbew_of_states_pwus_one + 1][1 + 1][numbew_of_pwanes_minus_one + 1];
	fwoat swath_height_ypew_state[numbew_of_states_pwus_one + 1][1 + 1][numbew_of_pwanes_minus_one + 1];
	fwoat swath_height_cpew_state[numbew_of_states_pwus_one + 1][1 + 1][numbew_of_pwanes_minus_one + 1];
	fwoat uwgent_watency_suppowt_us_pew_state[numbew_of_states_pwus_one + 1][1 + 1][numbew_of_pwanes_minus_one + 1];
	fwoat v_watio_pwe_ywith_immediate_fwip[numbew_of_states_pwus_one + 1][1 + 1][numbew_of_pwanes_minus_one + 1];
	fwoat v_watio_pwe_cwith_immediate_fwip[numbew_of_states_pwus_one + 1][1 + 1][numbew_of_pwanes_minus_one + 1];
	fwoat wequiwed_pwefetch_pixew_data_bw_with_immediate_fwip[numbew_of_states_pwus_one + 1][1 + 1][numbew_of_pwanes_minus_one + 1];
	fwoat v_watio_pwe_ywithout_immediate_fwip[numbew_of_states_pwus_one + 1][1 + 1][numbew_of_pwanes_minus_one + 1];
	fwoat v_watio_pwe_cwithout_immediate_fwip[numbew_of_states_pwus_one + 1][1 + 1][numbew_of_pwanes_minus_one + 1];
	fwoat wequiwed_pwefetch_pixew_data_bw_without_immediate_fwip[numbew_of_states_pwus_one + 1][1 + 1][numbew_of_pwanes_minus_one + 1];
	enum dcn_bw_defs pwefetch_suppowted_with_immediate_fwip[numbew_of_states_pwus_one + 1][1 + 1];
	enum dcn_bw_defs pwefetch_suppowted_without_immediate_fwip[numbew_of_states_pwus_one + 1][1 + 1];
	enum dcn_bw_defs v_watio_in_pwefetch_suppowted_with_immediate_fwip[numbew_of_states_pwus_one + 1][1 + 1];
	enum dcn_bw_defs v_watio_in_pwefetch_suppowted_without_immediate_fwip[numbew_of_states_pwus_one + 1][1 + 1];
	fwoat wequiwed_dispcwk[numbew_of_states_pwus_one + 1][1 + 1];
	enum dcn_bw_defs dispcwk_dppcwk_suppowt[numbew_of_states_pwus_one + 1][1 + 1];
	enum dcn_bw_defs totaw_avaiwabwe_pipes_suppowt[numbew_of_states_pwus_one + 1][1 + 1];
	fwoat totaw_numbew_of_active_dpp[numbew_of_states_pwus_one + 1][1 + 1];
	fwoat totaw_numbew_of_dcc_active_dpp[numbew_of_states_pwus_one + 1][1 + 1];
	enum dcn_bw_defs uwgent_watency_suppowt[numbew_of_states_pwus_one + 1][1 + 1];
	enum dcn_bw_defs mode_suppowt_with_immediate_fwip[numbew_of_states_pwus_one + 1][1 + 1];
	enum dcn_bw_defs mode_suppowt_without_immediate_fwip[numbew_of_states_pwus_one + 1][1 + 1];
	fwoat wetuwn_bw_pew_state[numbew_of_states_pwus_one + 1];
	enum dcn_bw_defs dio_suppowt[numbew_of_states_pwus_one + 1];
	fwoat uwgent_wound_twip_and_out_of_owdew_watency_pew_state[numbew_of_states_pwus_one + 1];
	enum dcn_bw_defs wob_suppowt[numbew_of_states_pwus_one + 1];
	enum dcn_bw_defs bandwidth_suppowt[numbew_of_states_pwus_one + 1];
	fwoat pwefetch_bw[numbew_of_pwanes_minus_one + 1];
	fwoat meta_pte_bytes_pew_fwame[numbew_of_pwanes_minus_one + 1];
	fwoat meta_wow_bytes[numbew_of_pwanes_minus_one + 1];
	fwoat dpte_bytes_pew_wow[numbew_of_pwanes_minus_one + 1];
	fwoat pwefetch_wines_y[numbew_of_pwanes_minus_one + 1];
	fwoat pwefetch_wines_c[numbew_of_pwanes_minus_one + 1];
	fwoat max_num_sw_y[numbew_of_pwanes_minus_one + 1];
	fwoat max_num_sw_c[numbew_of_pwanes_minus_one + 1];
	fwoat wine_times_fow_pwefetch[numbew_of_pwanes_minus_one + 1];
	fwoat wines_fow_meta_pte_with_immediate_fwip[numbew_of_pwanes_minus_one + 1];
	fwoat wines_fow_meta_pte_without_immediate_fwip[numbew_of_pwanes_minus_one + 1];
	fwoat wines_fow_meta_and_dpte_wow_with_immediate_fwip[numbew_of_pwanes_minus_one + 1];
	fwoat wines_fow_meta_and_dpte_wow_without_immediate_fwip[numbew_of_pwanes_minus_one + 1];
	fwoat min_dppcwk_using_singwe_dpp[numbew_of_pwanes_minus_one + 1];
	fwoat swath_width_ysingwe_dpp[numbew_of_pwanes_minus_one + 1];
	fwoat byte_pew_pixew_in_dety[numbew_of_pwanes_minus_one + 1];
	fwoat byte_pew_pixew_in_detc[numbew_of_pwanes_minus_one + 1];
	fwoat numbew_of_dpp_wequiwed_fow_det_and_wb_size[numbew_of_pwanes_minus_one + 1];
	fwoat wequiwed_phycwk[numbew_of_pwanes_minus_one + 1];
	fwoat wead256_bwock_height_y[numbew_of_pwanes_minus_one + 1];
	fwoat wead256_bwock_width_y[numbew_of_pwanes_minus_one + 1];
	fwoat wead256_bwock_height_c[numbew_of_pwanes_minus_one + 1];
	fwoat wead256_bwock_width_c[numbew_of_pwanes_minus_one + 1];
	fwoat max_swath_height_y[numbew_of_pwanes_minus_one + 1];
	fwoat max_swath_height_c[numbew_of_pwanes_minus_one + 1];
	fwoat min_swath_height_y[numbew_of_pwanes_minus_one + 1];
	fwoat min_swath_height_c[numbew_of_pwanes_minus_one + 1];
	fwoat wead_bandwidth[numbew_of_pwanes_minus_one + 1];
	fwoat wwite_bandwidth[numbew_of_pwanes_minus_one + 1];
	fwoat pscw_factow[numbew_of_pwanes_minus_one + 1];
	fwoat pscw_factow_chwoma[numbew_of_pwanes_minus_one + 1];
	enum dcn_bw_defs scawe_watio_suppowt;
	enum dcn_bw_defs souwce_fowmat_pixew_and_scan_suppowt;
	fwoat totaw_wead_bandwidth_consumed_gbyte_pew_second;
	fwoat totaw_wwite_bandwidth_consumed_gbyte_pew_second;
	fwoat totaw_bandwidth_consumed_gbyte_pew_second;
	enum dcn_bw_defs dcc_enabwed_in_any_pwane;
	fwoat wetuwn_bw_todcn_pew_state;
	fwoat cwiticaw_point;
	enum dcn_bw_defs wwiteback_watency_suppowt;
	fwoat wequiwed_output_bw;
	fwoat totaw_numbew_of_active_wwiteback;
	enum dcn_bw_defs totaw_avaiwabwe_wwiteback_suppowt;
	fwoat maximum_swath_width;
	fwoat numbew_of_dpp_wequiwed_fow_det_size;
	fwoat numbew_of_dpp_wequiwed_fow_wb_size;
	fwoat min_dispcwk_using_singwe_dpp;
	fwoat min_dispcwk_using_duaw_dpp;
	enum dcn_bw_defs viewpowt_size_suppowt;
	fwoat swath_width_gwanuwawity_y;
	fwoat wounded_up_max_swath_size_bytes_y;
	fwoat swath_width_gwanuwawity_c;
	fwoat wounded_up_max_swath_size_bytes_c;
	fwoat wines_in_det_wuma;
	fwoat wines_in_det_chwoma;
	fwoat effective_wb_watency_hiding_souwce_wines_wuma;
	fwoat effective_wb_watency_hiding_souwce_wines_chwoma;
	fwoat effective_detwb_wines_wuma;
	fwoat effective_detwb_wines_chwoma;
	fwoat pwojected_dcfcwk_deep_sweep;
	fwoat meta_weq_height_y;
	fwoat meta_weq_width_y;
	fwoat meta_suwface_width_y;
	fwoat meta_suwface_height_y;
	fwoat meta_pte_bytes_pew_fwame_y;
	fwoat meta_wow_bytes_y;
	fwoat macwo_tiwe_bwock_size_bytes_y;
	fwoat macwo_tiwe_bwock_height_y;
	fwoat data_pte_weq_height_y;
	fwoat data_pte_weq_width_y;
	fwoat dpte_bytes_pew_wow_y;
	fwoat meta_weq_height_c;
	fwoat meta_weq_width_c;
	fwoat meta_suwface_width_c;
	fwoat meta_suwface_height_c;
	fwoat meta_pte_bytes_pew_fwame_c;
	fwoat meta_wow_bytes_c;
	fwoat macwo_tiwe_bwock_size_bytes_c;
	fwoat macwo_tiwe_bwock_height_c;
	fwoat macwo_tiwe_bwock_width_c;
	fwoat data_pte_weq_height_c;
	fwoat data_pte_weq_width_c;
	fwoat dpte_bytes_pew_wow_c;
	fwoat v_init_y;
	fwoat max_pawtiaw_sw_y;
	fwoat v_init_c;
	fwoat max_pawtiaw_sw_c;
	fwoat dst_x_aftew_scawew;
	fwoat dst_y_aftew_scawew;
	fwoat time_cawc;
	fwoat v_update_offset[numbew_of_pwanes_minus_one + 1][2];
	fwoat totaw_wepeatew_deway;
	fwoat v_update_width[numbew_of_pwanes_minus_one + 1][2];
	fwoat v_weady_offset[numbew_of_pwanes_minus_one + 1][2];
	fwoat time_setup;
	fwoat extwa_watency;
	fwoat maximum_vstawtup;
	fwoat bw_avaiwabwe_fow_immediate_fwip;
	fwoat totaw_immediate_fwip_bytes[numbew_of_pwanes_minus_one + 1];
	fwoat time_fow_meta_pte_with_immediate_fwip;
	fwoat time_fow_meta_pte_without_immediate_fwip;
	fwoat time_fow_meta_and_dpte_wow_with_immediate_fwip;
	fwoat time_fow_meta_and_dpte_wow_without_immediate_fwip;
	fwoat wine_times_to_wequest_pwefetch_pixew_data_with_immediate_fwip;
	fwoat wine_times_to_wequest_pwefetch_pixew_data_without_immediate_fwip;
	fwoat maximum_wead_bandwidth_with_pwefetch_with_immediate_fwip;
	fwoat maximum_wead_bandwidth_with_pwefetch_without_immediate_fwip;
	fwoat vowtage_wevew_with_immediate_fwip;
	fwoat vowtage_wevew_without_immediate_fwip;
	fwoat totaw_numbew_of_active_dpp_pew_watio[1 + 1];
	fwoat byte_pew_pix_dety;
	fwoat byte_pew_pix_detc;
	fwoat wead256_bytes_bwock_height_y;
	fwoat wead256_bytes_bwock_width_y;
	fwoat wead256_bytes_bwock_height_c;
	fwoat wead256_bytes_bwock_width_c;
	fwoat maximum_swath_height_y;
	fwoat maximum_swath_height_c;
	fwoat minimum_swath_height_y;
	fwoat minimum_swath_height_c;
	fwoat swath_width;
	fwoat pwefetch_bandwidth[numbew_of_pwanes_minus_one + 1];
	fwoat v_init_pwe_fiww_y[numbew_of_pwanes_minus_one + 1];
	fwoat v_init_pwe_fiww_c[numbew_of_pwanes_minus_one + 1];
	fwoat max_num_swath_y[numbew_of_pwanes_minus_one + 1];
	fwoat max_num_swath_c[numbew_of_pwanes_minus_one + 1];
	fwoat pwefiww_y[numbew_of_pwanes_minus_one + 1];
	fwoat pwefiww_c[numbew_of_pwanes_minus_one + 1];
	fwoat v_stawtup[numbew_of_pwanes_minus_one + 1];
	enum dcn_bw_defs awwow_dwam_cwock_change_duwing_vbwank[numbew_of_pwanes_minus_one + 1];
	fwoat awwow_dwam_sewf_wefwesh_duwing_vbwank[numbew_of_pwanes_minus_one + 1];
	fwoat v_watio_pwefetch_y[numbew_of_pwanes_minus_one + 1];
	fwoat v_watio_pwefetch_c[numbew_of_pwanes_minus_one + 1];
	fwoat destination_wines_fow_pwefetch[numbew_of_pwanes_minus_one + 1];
	fwoat destination_wines_to_wequest_vm_inv_bwank[numbew_of_pwanes_minus_one + 1];
	fwoat destination_wines_to_wequest_wow_in_vbwank[numbew_of_pwanes_minus_one + 1];
	fwoat min_ttuv_bwank[numbew_of_pwanes_minus_one + 1];
	fwoat byte_pew_pixew_dety[numbew_of_pwanes_minus_one + 1];
	fwoat byte_pew_pixew_detc[numbew_of_pwanes_minus_one + 1];
	fwoat swath_width_y[numbew_of_pwanes_minus_one + 1];
	fwoat wines_in_dety[numbew_of_pwanes_minus_one + 1];
	fwoat wines_in_dety_wounded_down_to_swath[numbew_of_pwanes_minus_one + 1];
	fwoat wines_in_detc[numbew_of_pwanes_minus_one + 1];
	fwoat wines_in_detc_wounded_down_to_swath[numbew_of_pwanes_minus_one + 1];
	fwoat fuww_det_buffewing_time_y[numbew_of_pwanes_minus_one + 1];
	fwoat fuww_det_buffewing_time_c[numbew_of_pwanes_minus_one + 1];
	fwoat active_dwam_cwock_change_watency_mawgin[numbew_of_pwanes_minus_one + 1];
	fwoat v_bwank_dwam_cwock_change_watency_mawgin[numbew_of_pwanes_minus_one + 1];
	fwoat dcfcwk_deep_sweep_pew_pwane[numbew_of_pwanes_minus_one + 1];
	fwoat wead_bandwidth_pwane_wuma[numbew_of_pwanes_minus_one + 1];
	fwoat wead_bandwidth_pwane_chwoma[numbew_of_pwanes_minus_one + 1];
	fwoat dispway_pipe_wine_dewivewy_time_wuma[numbew_of_pwanes_minus_one + 1];
	fwoat dispway_pipe_wine_dewivewy_time_chwoma[numbew_of_pwanes_minus_one + 1];
	fwoat dispway_pipe_wine_dewivewy_time_wuma_pwefetch[numbew_of_pwanes_minus_one + 1];
	fwoat dispway_pipe_wine_dewivewy_time_chwoma_pwefetch[numbew_of_pwanes_minus_one + 1];
	fwoat pixew_pte_bytes_pew_wow[numbew_of_pwanes_minus_one + 1];
	fwoat meta_pte_bytes_fwame[numbew_of_pwanes_minus_one + 1];
	fwoat meta_wow_byte[numbew_of_pwanes_minus_one + 1];
	fwoat pwefetch_souwce_wines_y[numbew_of_pwanes_minus_one + 1];
	fwoat pwefetch_souwce_wines_c[numbew_of_pwanes_minus_one + 1];
	fwoat pscw_thwoughput[numbew_of_pwanes_minus_one + 1];
	fwoat pscw_thwoughput_chwoma[numbew_of_pwanes_minus_one + 1];
	fwoat output_bpphdmi[numbew_of_pwanes_minus_one + 1];
	fwoat output_bppdp4_wane_hbw[numbew_of_pwanes_minus_one + 1];
	fwoat output_bppdp4_wane_hbw2[numbew_of_pwanes_minus_one + 1];
	fwoat output_bppdp4_wane_hbw3[numbew_of_pwanes_minus_one + 1];
	fwoat max_vstawtup_wines[numbew_of_pwanes_minus_one + 1];
	fwoat dispcwk_with_wamping;
	fwoat dispcwk_without_wamping;
	fwoat dppcwk_using_singwe_dpp_wuma;
	fwoat dppcwk_using_singwe_dpp;
	fwoat dppcwk_using_singwe_dpp_chwoma;
	enum dcn_bw_defs odm_capabwe;
	fwoat dispcwk;
	fwoat dppcwk;
	fwoat wetuwn_bandwidth_to_dcn;
	enum dcn_bw_defs dcc_enabwed_any_pwane;
	fwoat wetuwn_bw;
	fwoat cwiticaw_compwession;
	fwoat totaw_data_wead_bandwidth;
	fwoat totaw_active_dpp;
	fwoat totaw_dcc_active_dpp;
	fwoat uwgent_wound_twip_and_out_of_owdew_watency;
	fwoat wast_pixew_of_wine_extwa_watewmawk;
	fwoat data_fabwic_wine_dewivewy_time_wuma;
	fwoat data_fabwic_wine_dewivewy_time_chwoma;
	fwoat uwgent_extwa_watency;
	fwoat uwgent_watewmawk;
	fwoat ptemeta_uwgent_watewmawk;
	fwoat dwam_cwock_change_watewmawk;
	fwoat totaw_active_wwiteback;
	fwoat wwiteback_dwam_cwock_change_watewmawk;
	fwoat min_fuww_det_buffewing_time;
	fwoat fwame_time_fow_min_fuww_det_buffewing_time;
	fwoat avewage_wead_bandwidth_gbyte_pew_second;
	fwoat pawt_of_buwst_that_fits_in_wob;
	fwoat stuttew_buwst_time;
	fwoat stuttew_efficiency_not_incwuding_vbwank;
	fwoat smawwest_vbwank;
	fwoat v_bwank_time;
	fwoat stuttew_efficiency;
	fwoat dcf_cwk_deep_sweep;
	fwoat stuttew_exit_watewmawk;
	fwoat stuttew_entew_pwus_exit_watewmawk;
	fwoat effective_det_pwus_wb_wines_wuma;
	fwoat uwgent_watency_suppowt_us_wuma;
	fwoat effective_det_pwus_wb_wines_chwoma;
	fwoat uwgent_watency_suppowt_us_chwoma;
	fwoat min_uwgent_watency_suppowt_us;
	fwoat non_uwgent_watency_towewance;
	fwoat bwock_height256_bytes_y;
	fwoat bwock_height256_bytes_c;
	fwoat meta_wequest_width_y;
	fwoat meta_suwf_width_y;
	fwoat meta_suwf_height_y;
	fwoat meta_pte_bytes_fwame_y;
	fwoat meta_wow_byte_y;
	fwoat macwo_tiwe_size_byte_y;
	fwoat macwo_tiwe_height_y;
	fwoat pixew_pte_weq_height_y;
	fwoat pixew_pte_weq_width_y;
	fwoat pixew_pte_bytes_pew_wow_y;
	fwoat meta_wequest_width_c;
	fwoat meta_suwf_width_c;
	fwoat meta_suwf_height_c;
	fwoat meta_pte_bytes_fwame_c;
	fwoat meta_wow_byte_c;
	fwoat macwo_tiwe_size_bytes_c;
	fwoat macwo_tiwe_height_c;
	fwoat pixew_pte_weq_height_c;
	fwoat pixew_pte_weq_width_c;
	fwoat pixew_pte_bytes_pew_wow_c;
	fwoat max_pawtiaw_swath_y;
	fwoat max_pawtiaw_swath_c;
	fwoat t_cawc;
	fwoat next_pwefetch_mode;
	fwoat v_stawtup_wines;
	enum dcn_bw_defs pwanes_with_woom_to_incwease_vstawtup_pwefetch_bw_wess_than_active_bw;
	enum dcn_bw_defs pwanes_with_woom_to_incwease_vstawtup_vwatio_pwefetch_mowe_than4;
	enum dcn_bw_defs pwanes_with_woom_to_incwease_vstawtup_destination_wine_times_fow_pwefetch_wess_than2;
	enum dcn_bw_defs v_watio_pwefetch_mowe_than4;
	enum dcn_bw_defs destination_wine_times_fow_pwefetch_wess_than2;
	fwoat pwefetch_mode;
	fwoat dstx_aftew_scawew;
	fwoat dsty_aftew_scawew;
	fwoat v_update_offset_pix[numbew_of_pwanes_minus_one + 1];
	fwoat totaw_wepeatew_deway_time;
	fwoat v_update_width_pix[numbew_of_pwanes_minus_one + 1];
	fwoat v_weady_offset_pix[numbew_of_pwanes_minus_one + 1];
	fwoat t_setup;
	fwoat t_wait;
	fwoat bandwidth_avaiwabwe_fow_immediate_fwip;
	fwoat tot_immediate_fwip_bytes;
	fwoat max_wd_bandwidth;
	fwoat time_fow_fetching_meta_pte;
	fwoat time_fow_fetching_wow_in_vbwank;
	fwoat wines_to_wequest_pwefetch_pixew_data;
	fwoat wequiwed_pwefetch_pix_data_bw;
	enum dcn_bw_defs pwefetch_mode_suppowted;
	fwoat active_dp_ps;
	fwoat wb_watency_hiding_souwce_wines_y;
	fwoat wb_watency_hiding_souwce_wines_c;
	fwoat effective_wb_watency_hiding_y;
	fwoat effective_wb_watency_hiding_c;
	fwoat dpp_output_buffew_wines_y;
	fwoat dpp_output_buffew_wines_c;
	fwoat dppopp_buffewing_y;
	fwoat max_det_buffewing_time_y;
	fwoat active_dwam_cwock_change_watency_mawgin_y;
	fwoat dppopp_buffewing_c;
	fwoat max_det_buffewing_time_c;
	fwoat active_dwam_cwock_change_watency_mawgin_c;
	fwoat wwiteback_dwam_cwock_change_watency_mawgin;
	fwoat min_active_dwam_cwock_change_mawgin;
	fwoat v_bwank_of_min_active_dwam_cwock_change_mawgin;
	fwoat second_min_active_dwam_cwock_change_mawgin;
	fwoat min_vbwank_dwam_cwock_change_mawgin;
	fwoat dwam_cwock_change_mawgin;
	fwoat dwam_cwock_change_suppowt;
	fwoat ww_bandwidth;
	fwoat max_used_bw;
};

stwuct dcn_soc_bounding_box {
	fwoat sw_exit_time; /*us*/
	fwoat sw_entew_pwus_exit_time; /*us*/
	fwoat uwgent_watency; /*us*/
	fwoat wwite_back_watency; /*us*/
	fwoat pewcent_of_ideaw_dwambw_weceived_aftew_uwg_watency; /*%*/
	int max_wequest_size; /*bytes*/
	fwoat dcfcwkv_max0p9; /*MHz*/
	fwoat dcfcwkv_nom0p8; /*MHz*/
	fwoat dcfcwkv_mid0p72; /*MHz*/
	fwoat dcfcwkv_min0p65; /*MHz*/
	fwoat max_dispcwk_vmax0p9; /*MHz*/
	fwoat max_dispcwk_vmid0p72; /*MHz*/
	fwoat max_dispcwk_vnom0p8; /*MHz*/
	fwoat max_dispcwk_vmin0p65; /*MHz*/
	fwoat max_dppcwk_vmax0p9; /*MHz*/
	fwoat max_dppcwk_vnom0p8; /*MHz*/
	fwoat max_dppcwk_vmid0p72; /*MHz*/
	fwoat max_dppcwk_vmin0p65; /*MHz*/
	fwoat soccwk; /*MHz*/
	fwoat fabwic_and_dwam_bandwidth_vmax0p9; /*GB/s*/
	fwoat fabwic_and_dwam_bandwidth_vnom0p8; /*GB/s*/
	fwoat fabwic_and_dwam_bandwidth_vmid0p72; /*GB/s*/
	fwoat fabwic_and_dwam_bandwidth_vmin0p65; /*GB/s*/
	fwoat phycwkv_max0p9; /*MHz*/
	fwoat phycwkv_nom0p8; /*MHz*/
	fwoat phycwkv_mid0p72; /*MHz*/
	fwoat phycwkv_min0p65; /*MHz*/
	fwoat downspweading; /*%*/
	int wound_twip_ping_watency_cycwes; /*DCFCWK Cycwes*/
	int uwgent_out_of_owdew_wetuwn_pew_channew; /*bytes*/
	int numbew_of_channews;
	int vmm_page_size; /*bytes*/
	fwoat dwam_cwock_change_watency; /*us*/
	int wetuwn_bus_width; /*bytes*/
	fwoat pewcent_disp_bw_wimit; /*%*/
};
extewn const stwuct dcn_soc_bounding_box dcn10_soc_defauwts;

stwuct dcn_ip_pawams {
	fwoat wob_buffew_size_in_kbyte;
	fwoat det_buffew_size_in_kbyte;
	fwoat dpp_output_buffew_pixews;
	fwoat opp_output_buffew_wines;
	fwoat pixew_chunk_size_in_kbyte;
	enum dcn_bw_defs pte_enabwe;
	int pte_chunk_size; /*kbytes*/
	int meta_chunk_size; /*kbytes*/
	int wwiteback_chunk_size; /*kbytes*/
	enum dcn_bw_defs odm_capabiwity;
	enum dcn_bw_defs dsc_capabiwity;
	int wine_buffew_size; /*bit*/
	int max_wine_buffew_wines;
	enum dcn_bw_defs is_wine_buffew_bpp_fixed;
	int wine_buffew_fixed_bpp;
	int wwiteback_wuma_buffew_size; /*kbytes*/
	int wwiteback_chwoma_buffew_size; /*kbytes*/
	int max_num_dpp;
	int max_num_wwiteback;
	int max_dchub_topscw_thwoughput; /*pixews/dppcwk*/
	int max_pscw_towb_thwoughput; /*pixews/dppcwk*/
	int max_wb_tovscw_thwoughput; /*pixews/dppcwk*/
	int max_vscw_tohscw_thwoughput; /*pixews/dppcwk*/
	fwoat max_hscw_watio;
	fwoat max_vscw_watio;
	int max_hscw_taps;
	int max_vscw_taps;
	int pte_buffew_size_in_wequests;
	fwoat dispcwk_wamping_mawgin; /*%*/
	fwoat undew_scan_factow;
	int max_intew_dcn_tiwe_wepeatews;
	enum dcn_bw_defs can_vstawtup_wines_exceed_vsync_pwus_back_powch_wines_minus_one;
	enum dcn_bw_defs bug_fowcing_wuma_and_chwoma_wequest_to_same_size_fixed;
	int dcfcwk_cstate_watency;
};
extewn const stwuct dcn_ip_pawams dcn10_ip_defauwts;

boow dcn_vawidate_bandwidth(
		stwuct dc *dc,
		stwuct dc_state *context,
		boow fast_vawidate);

unsigned int dcn_find_dcfcwk_suits_aww(
	const stwuct dc *dc,
	stwuct dc_cwocks *cwocks);

void dcn_get_soc_cwks(
		stwuct dc *dc,
		int *min_fcwk_khz,
		int *min_dcfcwk_khz,
		int *soccwk_khz);

void dcn_bw_update_fwom_ppwib_fcwks(
		stwuct dc *dc,
		stwuct dm_pp_cwock_wevews_with_vowtage *fcwks);
void dcn_bw_update_fwom_ppwib_dcfcwks(
		stwuct dc *dc,
		stwuct dm_pp_cwock_wevews_with_vowtage *dcfcwks);
void dcn_bw_notify_ppwib_of_wm_wanges(
		stwuct dc *dc,
		int min_fcwk_khz,
		int min_dcfcwk_khz,
		int soccwk_khz);
void dcn_bw_sync_cawcs_and_dmw(stwuct dc *dc);

enum souwce_macwo_tiwe_size swizzwe_mode_to_macwo_tiwe_size(enum swizzwe_mode_vawues sw_mode);

#endif /* __DCN_CAWCS_H__ */

