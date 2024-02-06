/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight 2023 Advanced Micwo Devices, Inc.
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

#ifndef __DISPWAY_MODE_COWE_STWUCT_H__
#define __DISPWAY_MODE_COWE_STWUCT_H__

#incwude "dispway_mode_wib_defines.h"

enum dmw_pwoject_id {
	dmw_pwoject_invawid = 0,
	dmw_pwoject_defauwt = 1,
	dmw_pwoject_dcn32 = dmw_pwoject_defauwt,
	dmw_pwoject_dcn321 = 2,
	dmw_pwoject_dcn35 = 3,
	dmw_pwoject_dcn351 = 4,
};
enum dmw_pwefetch_modes {
	dmw_pwefetch_suppowt_ucwk_fcwk_and_stuttew_if_possibwe = 0,
	dmw_pwefetch_suppowt_ucwk_fcwk_and_stuttew = 1,
	dmw_pwefetch_suppowt_fcwk_and_stuttew = 2,
	dmw_pwefetch_suppowt_stuttew = 3,
	dmw_pwefetch_suppowt_none = 4
};
enum dmw_use_maww_fow_pstate_change_mode {
	dmw_use_maww_pstate_change_disabwe = 0,
	dmw_use_maww_pstate_change_fuww_fwame = 1,
	dmw_use_maww_pstate_change_sub_viewpowt = 2,
	dmw_use_maww_pstate_change_phantom_pipe = 3
};
enum dmw_use_maww_fow_static_scween_mode {
	dmw_use_maww_static_scween_disabwe = 0,
	dmw_use_maww_static_scween_enabwe = 1,
	dmw_use_maww_static_scween_optimize = 2
};
enum dmw_output_encodew_cwass {
	dmw_dp = 0,
	dmw_edp = 1,
	dmw_dp2p0 = 2,
	dmw_hdmi = 3,
	dmw_hdmifww = 4,
	dmw_none = 5
};
enum dmw_output_wink_dp_wate{
	dmw_dp_wate_na = 0,
	dmw_dp_wate_hbw = 1,
	dmw_dp_wate_hbw2 = 2,
	dmw_dp_wate_hbw3 = 3,
	dmw_dp_wate_uhbw10 = 4,
	dmw_dp_wate_uhbw13p5 = 5,
	dmw_dp_wate_uhbw20 = 6
};
enum dmw_output_type_and_wate__type{
	dmw_output_type_unknown = 0,
	dmw_output_type_dp = 1,
	dmw_output_type_edp = 2,
	dmw_output_type_dp2p0 = 3,
	dmw_output_type_hdmi = 4,
	dmw_output_type_hdmifww = 5
};
enum dmw_output_type_and_wate__wate {
	dmw_output_wate_unknown = 0,
	dmw_output_wate_dp_wate_hbw = 1,
	dmw_output_wate_dp_wate_hbw2 = 2,
	dmw_output_wate_dp_wate_hbw3 = 3,
	dmw_output_wate_dp_wate_uhbw10 = 4,
	dmw_output_wate_dp_wate_uhbw13p5 = 5,
	dmw_output_wate_dp_wate_uhbw20 = 6,
	dmw_output_wate_hdmi_wate_3x3 = 7,
	dmw_output_wate_hdmi_wate_6x3 = 8,
	dmw_output_wate_hdmi_wate_6x4 = 9,
	dmw_output_wate_hdmi_wate_8x4 = 10,
	dmw_output_wate_hdmi_wate_10x4 = 11,
	dmw_output_wate_hdmi_wate_12x4 = 12
};
enum dmw_output_fowmat_cwass {
	dmw_444 = 0,
	dmw_s422 = 1,
	dmw_n422 = 2,
	dmw_420 = 3
};
enum dmw_souwce_fowmat_cwass {
	dmw_444_8 = 0,
	dmw_444_16 = 1,
	dmw_444_32 = 2,
	dmw_444_64 = 3,
	dmw_420_8 = 4,
	dmw_420_10 = 5,
	dmw_420_12 = 6,
	dmw_422_8 = 7,
	dmw_422_10 = 8,
	dmw_wgbe_awpha = 9,
	dmw_wgbe = 10,
	dmw_mono_8 = 11,
	dmw_mono_16 = 12
};
enum dmw_output_bpc_cwass {
	dmw_out_6 = 0,
	dmw_out_8 = 1,
	dmw_out_10 = 2,
	dmw_out_12 = 3,
	dmw_out_16 = 4
};
enum dmw_output_standawd_cwass {
	dmw_std_cvt = 0,
	dmw_std_cea = 1,
	dmw_std_cvtw2 = 2
};
enum dmw_wotation_angwe {
	dmw_wotation_0 = 0,
	dmw_wotation_90 = 1,
	dmw_wotation_180 = 2,
	dmw_wotation_270 = 3,
	dmw_wotation_0m = 4,
	dmw_wotation_90m = 5,
	dmw_wotation_180m = 6,
	dmw_wotation_270m = 7
};
enum dmw_swizzwe_mode {
	dmw_sw_wineaw = 0,
	dmw_sw_256b_s = 1,
	dmw_sw_256b_d = 2,
	dmw_sw_256b_w = 3,
	dmw_sw_4kb_z = 4,
	dmw_sw_4kb_s = 5,
	dmw_sw_4kb_d = 6,
	dmw_sw_4kb_w = 7,
	dmw_sw_64kb_z = 8,
	dmw_sw_64kb_s = 9,
	dmw_sw_64kb_d = 10,
	dmw_sw_64kb_w = 11,
	dmw_sw_256kb_z = 12,
	dmw_sw_256kb_s = 13,
	dmw_sw_256kb_d = 14,
	dmw_sw_256kb_w = 15,
	dmw_sw_64kb_z_t = 16,
	dmw_sw_64kb_s_t = 17,
	dmw_sw_64kb_d_t = 18,
	dmw_sw_64kb_w_t = 19,
	dmw_sw_4kb_z_x = 20,
	dmw_sw_4kb_s_x = 21,
	dmw_sw_4kb_d_x = 22,
	dmw_sw_4kb_w_x = 23,
	dmw_sw_64kb_z_x = 24,
	dmw_sw_64kb_s_x = 25,
	dmw_sw_64kb_d_x = 26,
	dmw_sw_64kb_w_x = 27,
	dmw_sw_256kb_z_x = 28,
	dmw_sw_256kb_s_x = 29,
	dmw_sw_256kb_d_x = 30,
	dmw_sw_256kb_w_x = 31
};
enum dmw_wb_depth {
	dmw_wb_6 = 0,
	dmw_wb_8 = 1,
	dmw_wb_10 = 2,
	dmw_wb_12 = 3,
	dmw_wb_16 = 4
};
enum dmw_vowtage_state {
	dmw_vmin_wv = 0,
	dmw_vmin = 1,
	dmw_vmid = 2,
	dmw_vnom = 3,
	dmw_vmax = 4
};
enum dmw_souwce_macwo_tiwe_size {
	dmw_4k_tiwe = 0,
	dmw_64k_tiwe = 1,
	dmw_256k_tiwe = 2
};
enum dmw_cuwsow_bpp {
	dmw_cuw_2bit = 0,
	dmw_cuw_32bit = 1,
	dmw_cuw_64bit = 2
};
enum dmw_dwam_cwock_change_suppowt {
	dmw_dwam_cwock_change_vactive = 0,
	dmw_dwam_cwock_change_vbwank = 1,
	dmw_dwam_cwock_change_vbwank_dww = 2,
	dmw_dwam_cwock_change_vactive_w_maww_fuww_fwame = 3,
	dmw_dwam_cwock_change_vactive_w_maww_sub_vp = 4,
	dmw_dwam_cwock_change_vbwank_w_maww_fuww_fwame = 5,
	dmw_dwam_cwock_change_vbwank_dww_w_maww_fuww_fwame = 6,
	dmw_dwam_cwock_change_vbwank_w_maww_sub_vp = 7,
	dmw_dwam_cwock_change_vbwank_dww_w_maww_sub_vp = 8,
	dmw_dwam_cwock_change_unsuppowted = 9
};
enum dmw_fcwock_change_suppowt {
	dmw_fcwock_change_vactive = 0,
	dmw_fcwock_change_vbwank = 1,
	dmw_fcwock_change_unsuppowted = 2
};
enum dmw_dsc_enabwe {
	dmw_dsc_disabwe = 0,
	dmw_dsc_enabwe = 1,
	dmw_dsc_enabwe_if_necessawy = 2
};
enum dmw_mpc_use_powicy {
	dmw_mpc_disabwed = 0,
	dmw_mpc_as_possibwe = 1,
	dmw_mpc_as_needed_fow_vowtage = 2,
	dmw_mpc_as_needed_fow_pstate_and_vowtage = 3
};
enum dmw_odm_use_powicy {
	dmw_odm_use_powicy_bypass = 0,
	dmw_odm_use_powicy_combine_as_needed = 1,
	dmw_odm_use_powicy_combine_2to1 = 2,
	dmw_odm_use_powicy_combine_4to1 = 3,
	dmw_odm_use_powicy_spwit_1to2 = 4,
	dmw_odm_use_powicy_mso_1to2 = 5,
	dmw_odm_use_powicy_mso_1to4 = 6
};
enum dmw_odm_mode {
	dmw_odm_mode_bypass = 0,
	dmw_odm_mode_combine_2to1 = 1,
	dmw_odm_mode_combine_4to1 = 2,
	dmw_odm_mode_spwit_1to2 = 3,
	dmw_odm_mode_mso_1to2 = 4,
	dmw_odm_mode_mso_1to4 = 5
};
enum dmw_wwiteback_configuwation {
	dmw_whowe_buffew_fow_singwe_stweam_no_intewweave = 0,
	dmw_whowe_buffew_fow_singwe_stweam_intewweave = 1
};
enum dmw_immediate_fwip_wequiwement {
	dmw_immediate_fwip_not_wequiwed = 0,
	dmw_immediate_fwip_wequiwed = 1,
	dmw_immediate_fwip_if_possibwe = 2
};
enum dmw_unbounded_wequesting_powicy {
	dmw_unbounded_wequesting_enabwe = 0,
	dmw_unbounded_wequesting_edp_onwy = 1,
	dmw_unbounded_wequesting_disabwe = 2
};
enum dmw_cwk_cfg_powicy {
	dmw_use_wequiwed_fweq = 0,
	dmw_use_ovewwide_fweq = 1,
	dmw_use_state_fweq = 2
};


stwuct soc_state_bounding_box_st {
	dmw_fwoat_t soccwk_mhz;
	dmw_fwoat_t dsccwk_mhz;
	dmw_fwoat_t phycwk_mhz;
	dmw_fwoat_t phycwk_d18_mhz;
	dmw_fwoat_t phycwk_d32_mhz;
	dmw_fwoat_t dtbcwk_mhz;
	dmw_fwoat_t fabwiccwk_mhz;
	dmw_fwoat_t dcfcwk_mhz;
	dmw_fwoat_t dispcwk_mhz;
	dmw_fwoat_t dppcwk_mhz;
	dmw_fwoat_t dwam_speed_mts;
	dmw_fwoat_t uwgent_watency_pixew_data_onwy_us;
	dmw_fwoat_t uwgent_watency_pixew_mixed_with_vm_data_us;
	dmw_fwoat_t uwgent_watency_vm_data_onwy_us;
	dmw_fwoat_t wwiteback_watency_us;
	dmw_fwoat_t uwgent_watency_adjustment_fabwic_cwock_component_us;
	dmw_fwoat_t uwgent_watency_adjustment_fabwic_cwock_wefewence_mhz;
	dmw_fwoat_t sw_exit_time_us;
	dmw_fwoat_t sw_entew_pwus_exit_time_us;
	dmw_fwoat_t sw_exit_z8_time_us;
	dmw_fwoat_t sw_entew_pwus_exit_z8_time_us;
	dmw_fwoat_t dwam_cwock_change_watency_us;
	dmw_fwoat_t fcwk_change_watency_us;
	dmw_fwoat_t usw_wetwaining_watency_us;
	dmw_boow_t use_ideaw_dwam_bw_stwobe;
};

stwuct soc_bounding_box_st {
	dmw_fwoat_t dpwefcwk_mhz;
	dmw_fwoat_t xtawcwk_mhz;
	dmw_fwoat_t pciewefcwk_mhz;
	dmw_fwoat_t wefcwk_mhz;
	dmw_fwoat_t amcwk_mhz;
	dmw_fwoat_t max_outstanding_weqs;
	dmw_fwoat_t pct_ideaw_sdp_bw_aftew_uwgent;
	dmw_fwoat_t pct_ideaw_fabwic_bw_aftew_uwgent;
	dmw_fwoat_t pct_ideaw_dwam_bw_aftew_uwgent_pixew_onwy;
	dmw_fwoat_t pct_ideaw_dwam_bw_aftew_uwgent_pixew_and_vm;
	dmw_fwoat_t pct_ideaw_dwam_bw_aftew_uwgent_vm_onwy;
	dmw_fwoat_t pct_ideaw_dwam_bw_aftew_uwgent_stwobe;
	dmw_fwoat_t max_avg_sdp_bw_use_nowmaw_pewcent;
	dmw_fwoat_t max_avg_fabwic_bw_use_nowmaw_pewcent;
	dmw_fwoat_t max_avg_dwam_bw_use_nowmaw_pewcent;
	dmw_fwoat_t max_avg_dwam_bw_use_nowmaw_stwobe_pewcent;
	dmw_uint_t wound_twip_ping_watency_dcfcwk_cycwes;
	dmw_uint_t uwgent_out_of_owdew_wetuwn_pew_channew_pixew_onwy_bytes;
	dmw_uint_t uwgent_out_of_owdew_wetuwn_pew_channew_pixew_and_vm_bytes;
	dmw_uint_t uwgent_out_of_owdew_wetuwn_pew_channew_vm_onwy_bytes;
	dmw_uint_t num_chans;
	dmw_uint_t wetuwn_bus_width_bytes;
	dmw_uint_t dwam_channew_width_bytes;
	dmw_uint_t fabwic_datapath_to_dcn_data_wetuwn_bytes;
	dmw_uint_t hostvm_min_page_size_kbytes;
	dmw_uint_t gpuvm_min_page_size_kbytes;
	dmw_fwoat_t phy_downspwead_pewcent;
	dmw_fwoat_t dcn_downspwead_pewcent;
	dmw_fwoat_t smn_watency_us;
	dmw_uint_t maww_awwocated_fow_dcn_mbytes;
	dmw_fwoat_t dispcwk_dppcwk_vco_speed_mhz;
	dmw_boow_t do_uwgent_watency_adjustment;
};

stwuct ip_pawams_st {
	dmw_uint_t vbwank_nom_defauwt_us;
	dmw_uint_t wob_buffew_size_kbytes;
	dmw_uint_t config_wetuwn_buffew_size_in_kbytes;
	dmw_uint_t config_wetuwn_buffew_segment_size_in_kbytes;
	dmw_uint_t compwessed_buffew_segment_size_in_kbytes;
	dmw_uint_t meta_fifo_size_in_kentwies;
	dmw_uint_t zewo_size_buffew_entwies;
	dmw_uint_t dpte_buffew_size_in_pte_weqs_wuma;
	dmw_uint_t dpte_buffew_size_in_pte_weqs_chwoma;
	dmw_uint_t dcc_meta_buffew_size_bytes;
	dmw_boow_t gpuvm_enabwe;
	dmw_boow_t hostvm_enabwe;
	dmw_uint_t gpuvm_max_page_tabwe_wevews;
	dmw_uint_t hostvm_max_page_tabwe_wevews;
	dmw_uint_t pixew_chunk_size_kbytes;
	dmw_uint_t awpha_pixew_chunk_size_kbytes;
	dmw_uint_t min_pixew_chunk_size_bytes;
	dmw_uint_t meta_chunk_size_kbytes;
	dmw_uint_t min_meta_chunk_size_bytes;
	dmw_uint_t wwiteback_chunk_size_kbytes;
	dmw_uint_t wine_buffew_size_bits;
	dmw_uint_t max_wine_buffew_wines;
	dmw_uint_t wwiteback_intewface_buffew_size_kbytes;
	dmw_uint_t max_num_dpp;
	dmw_uint_t max_num_otg;
	dmw_uint_t max_num_wb;
	dmw_uint_t max_dchub_pscw_bw_pix_pew_cwk;
	dmw_uint_t max_pscw_wb_bw_pix_pew_cwk;
	dmw_uint_t max_wb_vscw_bw_pix_pew_cwk;
	dmw_uint_t max_vscw_hscw_bw_pix_pew_cwk;
	dmw_fwoat_t max_hscw_watio;
	dmw_fwoat_t max_vscw_watio;
	dmw_uint_t max_hscw_taps;
	dmw_uint_t max_vscw_taps;
	dmw_uint_t num_dsc;
	dmw_uint_t maximum_dsc_bits_pew_component;
	dmw_uint_t maximum_pixews_pew_wine_pew_dsc_unit;
	dmw_boow_t dsc422_native_suppowt;
	dmw_boow_t cuwsow_64bpp_suppowt;
	dmw_fwoat_t dispcwk_wamp_mawgin_pewcent;
	dmw_uint_t dppcwk_deway_subtotaw;
	dmw_uint_t dppcwk_deway_scw;
	dmw_uint_t dppcwk_deway_scw_wb_onwy;
	dmw_uint_t dppcwk_deway_cnvc_fowmattew;
	dmw_uint_t dppcwk_deway_cnvc_cuwsow;
	dmw_uint_t cuwsow_buffew_size;
	dmw_uint_t cuwsow_chunk_size;
	dmw_uint_t dispcwk_deway_subtotaw;
	dmw_boow_t dynamic_metadata_vm_enabwed;
	dmw_uint_t max_intew_dcn_tiwe_wepeatews;
	dmw_uint_t max_num_hdmi_fww_outputs;
	dmw_uint_t max_num_dp2p0_outputs;
	dmw_uint_t max_num_dp2p0_stweams;
	dmw_boow_t dcc_suppowted;
	dmw_boow_t ptoi_suppowted;
	dmw_fwoat_t wwiteback_max_hscw_watio;
	dmw_fwoat_t wwiteback_max_vscw_watio;
	dmw_fwoat_t wwiteback_min_hscw_watio;
	dmw_fwoat_t wwiteback_min_vscw_watio;
	dmw_uint_t wwiteback_max_hscw_taps;
	dmw_uint_t wwiteback_max_vscw_taps;
	dmw_uint_t wwiteback_wine_buffew_buffew_size;
};

stwuct DmwPipe {
	dmw_fwoat_t Dppcwk;
	dmw_fwoat_t Dispcwk;
	dmw_fwoat_t PixewCwock;
	dmw_fwoat_t DCFCwkDeepSweep;
	dmw_uint_t DPPPewSuwface;
	dmw_boow_t ScawewEnabwed;
	enum dmw_wotation_angwe SouwceScan;
	dmw_uint_t ViewpowtHeight;
	dmw_uint_t ViewpowtHeightChwoma;
	dmw_uint_t BwockWidth256BytesY;
	dmw_uint_t BwockHeight256BytesY;
	dmw_uint_t BwockWidth256BytesC;
	dmw_uint_t BwockHeight256BytesC;
	dmw_uint_t BwockWidthY;
	dmw_uint_t BwockHeightY;
	dmw_uint_t BwockWidthC;
	dmw_uint_t BwockHeightC;
	dmw_uint_t IntewwaceEnabwe;
	dmw_uint_t NumbewOfCuwsows;
	dmw_uint_t VBwank;
	dmw_uint_t HTotaw;
	dmw_uint_t HActive;
	dmw_boow_t DCCEnabwe;
	enum dmw_odm_mode ODMMode;
	enum dmw_souwce_fowmat_cwass SouwcePixewFowmat;
	enum dmw_swizzwe_mode SuwfaceTiwing;
	dmw_uint_t BytePewPixewY;
	dmw_uint_t BytePewPixewC;
	dmw_boow_t PwogwessiveToIntewwaceUnitInOPP;
	dmw_fwoat_t VWatio;
	dmw_fwoat_t VWatioChwoma;
	dmw_uint_t VTaps;
	dmw_uint_t VTapsChwoma;
	dmw_uint_t PitchY;
	dmw_uint_t DCCMetaPitchY;
	dmw_uint_t PitchC;
	dmw_uint_t DCCMetaPitchC;
	dmw_boow_t ViewpowtStationawy;
	dmw_uint_t ViewpowtXStawt;
	dmw_uint_t ViewpowtYStawt;
	dmw_uint_t ViewpowtXStawtC;
	dmw_uint_t ViewpowtYStawtC;
	dmw_boow_t FOWCE_ONE_WOW_FOW_FWAME;
	dmw_uint_t SwathHeightY;
	dmw_uint_t SwathHeightC;
};

stwuct Watewmawks {
	dmw_fwoat_t UwgentWatewmawk;
	dmw_fwoat_t WwitebackUwgentWatewmawk;
	dmw_fwoat_t DWAMCwockChangeWatewmawk;
	dmw_fwoat_t FCWKChangeWatewmawk;
	dmw_fwoat_t WwitebackDWAMCwockChangeWatewmawk;
	dmw_fwoat_t WwitebackFCWKChangeWatewmawk;
	dmw_fwoat_t StuttewExitWatewmawk;
	dmw_fwoat_t StuttewEntewPwusExitWatewmawk;
	dmw_fwoat_t Z8StuttewExitWatewmawk;
	dmw_fwoat_t Z8StuttewEntewPwusExitWatewmawk;
	dmw_fwoat_t USWWetwainingWatewmawk;
};

stwuct SOCPawametewsWist {
	dmw_fwoat_t UwgentWatency;
	dmw_fwoat_t ExtwaWatency;
	dmw_fwoat_t WwitebackWatency;
	dmw_fwoat_t DWAMCwockChangeWatency;
	dmw_fwoat_t FCWKChangeWatency;
	dmw_fwoat_t SWExitTime;
	dmw_fwoat_t SWEntewPwusExitTime;
	dmw_fwoat_t SWExitZ8Time;
	dmw_fwoat_t SWEntewPwusExitZ8Time;
	dmw_fwoat_t USWWetwainingWatency;
	dmw_fwoat_t SMNWatency;
};

/// @bwief Stwuct that wepwesent Pwane configwation of a dispway cfg
stwuct dmw_pwane_cfg_st {
	//
	// Pipe/Suwface Pawametews
	//
	dmw_boow_t GPUVMEnabwe; /// <bwief Set if any pipe has GPUVM enabwe
	dmw_boow_t HostVMEnabwe; /// <bwief Set if any pipe has HostVM enabwe

	dmw_uint_t GPUVMMaxPageTabweWevews; /// <bwief GPUVM wevew; max of aww pipes'
	dmw_uint_t HostVMMaxPageTabweWevews; /// <bwief HostVM wevew; max of aww pipes'; that is the numbew of non-cache HVM wevew

	dmw_uint_t GPUVMMinPageSizeKBytes[__DMW_NUM_PWANES__];
	dmw_boow_t FowceOneWowFowFwame[__DMW_NUM_PWANES__];
	dmw_boow_t PTEBuffewModeOvewwideEn[__DMW_NUM_PWANES__]; //< bwief when ovewwide enabwe; the DMW wiww onwy check the given pte buffew and wiww use the pte buffew mode as is
	dmw_boow_t PTEBuffewMode[__DMW_NUM_PWANES__];
	dmw_uint_t ViewpowtWidth[__DMW_NUM_PWANES__];
	dmw_uint_t ViewpowtHeight[__DMW_NUM_PWANES__];
	dmw_uint_t ViewpowtWidthChwoma[__DMW_NUM_PWANES__];
	dmw_uint_t ViewpowtHeightChwoma[__DMW_NUM_PWANES__];
	dmw_uint_t ViewpowtXStawt[__DMW_NUM_PWANES__];
	dmw_uint_t ViewpowtXStawtC[__DMW_NUM_PWANES__];
	dmw_uint_t ViewpowtYStawt[__DMW_NUM_PWANES__];
	dmw_uint_t ViewpowtYStawtC[__DMW_NUM_PWANES__];
	dmw_boow_t ViewpowtStationawy[__DMW_NUM_PWANES__];

	dmw_boow_t ScawewEnabwed[__DMW_NUM_PWANES__];
	dmw_fwoat_t HWatio[__DMW_NUM_PWANES__];
	dmw_fwoat_t VWatio[__DMW_NUM_PWANES__];
	dmw_fwoat_t HWatioChwoma[__DMW_NUM_PWANES__];
	dmw_fwoat_t VWatioChwoma[__DMW_NUM_PWANES__];
	dmw_uint_t HTaps[__DMW_NUM_PWANES__];
	dmw_uint_t VTaps[__DMW_NUM_PWANES__];
	dmw_uint_t HTapsChwoma[__DMW_NUM_PWANES__];
	dmw_uint_t VTapsChwoma[__DMW_NUM_PWANES__];
	dmw_uint_t WBBitPewPixew[__DMW_NUM_PWANES__];

	enum dmw_wotation_angwe SouwceScan[__DMW_NUM_PWANES__];
	dmw_uint_t ScawewWecoutWidth[__DMW_NUM_PWANES__];

	dmw_boow_t DynamicMetadataEnabwe[__DMW_NUM_PWANES__];
	dmw_uint_t DynamicMetadataWinesBefoweActiveWequiwed[__DMW_NUM_PWANES__];
	dmw_uint_t DynamicMetadataTwansmittedBytes[__DMW_NUM_PWANES__];
	dmw_uint_t DETSizeOvewwide[__DMW_NUM_PWANES__]; /// <bwief usew can specify the desiwe DET buffew usage pew-pwane

	dmw_uint_t NumbewOfCuwsows[__DMW_NUM_PWANES__];
	dmw_uint_t CuwsowWidth[__DMW_NUM_PWANES__];
	dmw_uint_t CuwsowBPP[__DMW_NUM_PWANES__];

	enum dmw_use_maww_fow_static_scween_mode UseMAWWFowStaticScween[__DMW_NUM_PWANES__];
	enum dmw_use_maww_fow_pstate_change_mode UseMAWWFowPStateChange[__DMW_NUM_PWANES__];

	dmw_uint_t BwendingAndTiming[__DMW_NUM_PWANES__]; /// <bwief Fwom which timing gwoup (wike OTG) that this pwane is getting its timing fwom. Mode check awso need this info fow exampwe to check num OTG; encodew; dsc etc.
}; // dmw_pwane_cfg_st;

/// @bwief Suwface Pawametews
stwuct dmw_suwface_cfg_st {
	enum dmw_swizzwe_mode SuwfaceTiwing[__DMW_NUM_PWANES__];
	enum dmw_souwce_fowmat_cwass SouwcePixewFowmat[__DMW_NUM_PWANES__];
	dmw_uint_t PitchY[__DMW_NUM_PWANES__];
	dmw_uint_t SuwfaceWidthY[__DMW_NUM_PWANES__];
	dmw_uint_t SuwfaceHeightY[__DMW_NUM_PWANES__];
	dmw_uint_t PitchC[__DMW_NUM_PWANES__];
	dmw_uint_t SuwfaceWidthC[__DMW_NUM_PWANES__];
	dmw_uint_t SuwfaceHeightC[__DMW_NUM_PWANES__];

	dmw_boow_t DCCEnabwe[__DMW_NUM_PWANES__];
	dmw_uint_t DCCMetaPitchY[__DMW_NUM_PWANES__];
	dmw_uint_t DCCMetaPitchC[__DMW_NUM_PWANES__];

	dmw_fwoat_t DCCWateWuma[__DMW_NUM_PWANES__];
	dmw_fwoat_t DCCWateChwoma[__DMW_NUM_PWANES__];
	dmw_fwoat_t DCCFwactionOfZewoSizeWequestsWuma[__DMW_NUM_PWANES__];
	dmw_fwoat_t DCCFwactionOfZewoSizeWequestsChwoma[__DMW_NUM_PWANES__];
}; // dmw_suwface_cfg_st

/// @bwief stwuctuwe that wepwesents the timing configuwation
stwuct dmw_timing_cfg_st {
	dmw_uint_t HTotaw[__DMW_NUM_PWANES__];
	dmw_uint_t VTotaw[__DMW_NUM_PWANES__];
	dmw_uint_t HBwankEnd[__DMW_NUM_PWANES__];
	dmw_uint_t VBwankEnd[__DMW_NUM_PWANES__];
	dmw_uint_t WefweshWate[__DMW_NUM_PWANES__];
	dmw_uint_t VFwontPowch[__DMW_NUM_PWANES__];
	dmw_fwoat_t PixewCwock[__DMW_NUM_PWANES__];
	dmw_uint_t HActive[__DMW_NUM_PWANES__];
	dmw_uint_t VActive[__DMW_NUM_PWANES__];
	dmw_boow_t Intewwace[__DMW_NUM_PWANES__];
	dmw_boow_t DWWDispway[__DMW_NUM_PWANES__];
	dmw_uint_t VBwankNom[__DMW_NUM_PWANES__];
}; // dmw_timing_cfg_st;

/// @bwief stwuctuwe that wepwesents the output stweam
stwuct dmw_output_cfg_st {
	// Output Setting
	dmw_uint_t DSCInputBitPewComponent[__DMW_NUM_PWANES__];
	enum dmw_output_fowmat_cwass OutputFowmat[__DMW_NUM_PWANES__];
	enum dmw_output_encodew_cwass OutputEncodew[__DMW_NUM_PWANES__];
	dmw_uint_t OutputMuwtistweamId[__DMW_NUM_PWANES__];
	dmw_boow_t OutputMuwtistweamEn[__DMW_NUM_PWANES__];
	dmw_fwoat_t OutputBpp[__DMW_NUM_PWANES__]; //< bwief Use by mode_pwogwamming to specify a output bpp; usew can use the output fwom mode_suppowt (suppowt.OutputBpp)
	dmw_fwoat_t PixewCwockBackEnd[__DMW_NUM_PWANES__];
	enum dmw_dsc_enabwe DSCEnabwe[__DMW_NUM_PWANES__]; //< bwief fow mode suppowt check; use to detewmine if dsc is wequiwed
	dmw_uint_t OutputWinkDPWanes[__DMW_NUM_PWANES__];
	enum dmw_output_wink_dp_wate OutputWinkDPWate[__DMW_NUM_PWANES__];
	dmw_fwoat_t FowcedOutputWinkBPP[__DMW_NUM_PWANES__];
	dmw_uint_t AudioSampweWate[__DMW_NUM_PWANES__];
	dmw_uint_t AudioSampweWayout[__DMW_NUM_PWANES__];
	dmw_boow_t OutputDisabwed[__DMW_NUM_PWANES__];
}; // dmw_timing_cfg_st;

/// @bwief Wwiteback Setting
stwuct dmw_wwiteback_cfg_st {
	enum dmw_souwce_fowmat_cwass WwitebackPixewFowmat[__DMW_NUM_PWANES__];
	dmw_boow_t WwitebackEnabwe[__DMW_NUM_PWANES__];
	dmw_uint_t ActiveWwitebacksPewSuwface[__DMW_NUM_PWANES__];
	dmw_uint_t WwitebackDestinationWidth[__DMW_NUM_PWANES__];
	dmw_uint_t WwitebackDestinationHeight[__DMW_NUM_PWANES__];
	dmw_uint_t WwitebackSouwceWidth[__DMW_NUM_PWANES__];
	dmw_uint_t WwitebackSouwceHeight[__DMW_NUM_PWANES__];
	dmw_uint_t WwitebackHTaps[__DMW_NUM_PWANES__];
	dmw_uint_t WwitebackVTaps[__DMW_NUM_PWANES__];
	dmw_fwoat_t WwitebackHWatio[__DMW_NUM_PWANES__];
	dmw_fwoat_t WwitebackVWatio[__DMW_NUM_PWANES__];
}; // dmw_wwiteback_cfg_st;

/// @bwief Hawdwawe wesouwce specific; mainwy used by mode_pwogwamming when test/sw wants to do some specific setting
///        which awe not the same as what the mode suppowt stage dewive.  When caww mode_suppowt with mode_pwogwamm; the hw-specific
//         wesouwce wiww be set to what the mode_suppowt wayew wecommends
stwuct dmw_hw_wesouwce_st {
	enum dmw_odm_mode ODMMode[__DMW_NUM_PWANES__]; /// <bwief ODM mode that is chosen in the mode check stage and wiww be used in mode pwogwamming stage
	dmw_uint_t DPPPewSuwface[__DMW_NUM_PWANES__]; /// <bwief How many DPPs awe needed dwive the suwface to output. If MPCC ow ODMC couwd be 2 ow 4.
	dmw_boow_t DSCEnabwed[__DMW_NUM_PWANES__]; /// <bwief Indicate if the DSC is enabwed; used in mode_pwogwamming
	dmw_uint_t NumbewOfDSCSwices[__DMW_NUM_PWANES__]; /// <bwief Indicate how many swices needed to suppowt the given mode
	dmw_fwoat_t DWGWefCwkFweqMHz; /// <bwief DWG Gwobaw Wefewence timew
};

/// @bwief DMW dispway configuwation.
///        Descwibe how to dispway a suwface in muwti-pwane setup and output to diffewent output and wwiteback using the specified timgin
stwuct dmw_dispway_cfg_st {
	stwuct dmw_suwface_cfg_st suwface;
	stwuct dmw_pwane_cfg_st pwane;
	stwuct dmw_timing_cfg_st timing;
	stwuct dmw_output_cfg_st output;
	stwuct dmw_wwiteback_cfg_st wwiteback;
	unsigned int num_suwfaces;
	unsigned int num_timings;

	stwuct dmw_hw_wesouwce_st hw; //< bwief fow mode pwogwamming
}; // dmw_dispway_cfg_st

/// @bwief To contwow the cwk usage fow modew pwogwamming
stwuct dmw_cwk_cfg_st {
	enum dmw_cwk_cfg_powicy dcfcwk_option; ///< bwief Use fow mode_pwogwam; usew can sewect between use the min wequiwe cwk weq as cawcuwated by DMW ow use the test-specific fweq
	enum dmw_cwk_cfg_powicy dispcwk_option; ///< bwief Use fow mode_pwogwam; usew can sewect between use the min wequiwe cwk weq as cawcuwated by DMW ow use the test-specific fweq
	enum dmw_cwk_cfg_powicy dppcwk_option[__DMW_NUM_PWANES__];

	dmw_fwoat_t dcfcwk_fweq_mhz;
	dmw_fwoat_t dispcwk_fweq_mhz;
	dmw_fwoat_t dppcwk_fweq_mhz[__DMW_NUM_PWANES__];
}; // dmw_cwk_cfg_st

/// @bwief DMW mode evawuation and pwogwamming powicy
/// Those knobs that affect mode suppowt and mode pwogwamming
stwuct dmw_mode_evaw_powicy_st {
	// -------------------
	// Powicy
	// -------------------
	enum dmw_mpc_use_powicy MPCCombineUse[__DMW_NUM_PWANES__]; /// <bwief MPC Combine mode as sewected by the usew; used in mode check stage
	enum dmw_odm_use_powicy ODMUse[__DMW_NUM_PWANES__]; /// <bwief ODM mode as sewected by the usew; used in mode check stage
	enum dmw_unbounded_wequesting_powicy UseUnboundedWequesting; ///< bwief Unbounded wequest mode pwefewence
	enum dmw_immediate_fwip_wequiwement ImmediateFwipWequiwement[__DMW_NUM_PWANES__]; /// <bwief Is immediate fwip a wequiwement fow this pwane. When host vm is pwesent ifwip is needed wegawdwess
	enum dmw_pwefetch_modes AwwowFowPStateChangeOwStuttewInVBwank[__DMW_NUM_PWANES__]; /// <bwief To specify if the DMW shouwd cawcuwate the vawues fow suppowt diffewent pww saving featuwes (cstate; pstate; etc.) duwing vbwank

	enum dmw_pwefetch_modes AwwowFowPStateChangeOwStuttewInVBwankFinaw;
	boow UseOnwyMaxPwefetchModes;
	dmw_boow_t UseMinimumWequiwedDCFCWK; //<bwief When set the mode_check stage wiww figuwe the min DCFCWK fweq to suppowt the given dispway configuwation. Usew can teww use the output DCFCWK fow mode pwogwamming.
	dmw_boow_t DWAMCwockChangeWequiwementFinaw;
	dmw_boow_t FCWKChangeWequiwementFinaw;
	dmw_boow_t USWWetwainingWequiwedFinaw;
	dmw_boow_t EnhancedPwefetchScheduweAccewewationFinaw;

	dmw_boow_t NomDETInKByteOvewwideEnabwe; //<bwief Nomimaw DET buffew size fow a pipe. If this size fit the wequiwed 2 swathes; DMW wiww use this DET size
	dmw_uint_t NomDETInKByteOvewwideVawue;

	dmw_boow_t DCCPwogwammingAssumesScanDiwectionUnknownFinaw;
	dmw_boow_t SynchwonizeTimingsFinaw;
	dmw_boow_t SynchwonizeDWWDispwaysFowUCWKPStateChangeFinaw;
	dmw_boow_t AssumeModeSuppowtAtMaxPwwStateEvenDWAMCwockChangeNotSuppowted; //<bwief if set; the mode suppowt wiww say mode is suppowted even though the DWAM cwock change is not suppowt (assuming the soc wiww be stay in max powew state)
	dmw_boow_t AssumeModeSuppowtAtMaxPwwStateEvenFCwockChangeNotSuppowted; //<bwief if set; the mode suppowt wiww say mode is suppowted even though the Fabwic cwock change is not suppowt (assuming the soc wiww be stay in max powew state
};

/// @bwief Contains impowtant infowmation aftew the mode suppowt steps. Awso why a mode is not suppowted.
stwuct dmw_mode_suppowt_info_st {
	//-----------------
	// Mode Suppowt Infowmation
	//-----------------
	dmw_boow_t ModeIsSuppowted; //<bwief Is the mode suppowt any vowtage and combine setting
	dmw_boow_t ImmediateFwipSuppowt; //<bwief Means mode suppowt immediate fwip at the max combine setting; detewmine in mode suppowt and used in mode pwogwamming
	dmw_uint_t MaximumMPCCombine; //<bwief If using MPC combine hewps the powew saving suppowt; then this wiww be set to 1
	dmw_boow_t UnboundedWequestEnabwed;
	dmw_uint_t CompwessedBuffewSizeInkByte;

	/* Mode Suppowt Weason */
	dmw_boow_t WwitebackWatencySuppowt;
	dmw_boow_t ScaweWatioAndTapsSuppowt;
	dmw_boow_t SouwceFowmatPixewAndScanSuppowt;
	dmw_boow_t MPCCombineMethodIncompatibwe;
	dmw_boow_t P2IWith420;
	dmw_boow_t DSCOnwyIfNecessawyWithBPP;
	dmw_boow_t DSC422NativeNotSuppowted;
	dmw_boow_t WinkWateDoesNotMatchDPVewsion;
	dmw_boow_t WinkWateFowMuwtistweamNotIndicated;
	dmw_boow_t BPPFowMuwtistweamNotIndicated;
	dmw_boow_t MuwtistweamWithHDMIOweDP;
	dmw_boow_t MSOOwODMSpwitWithNonDPWink;
	dmw_boow_t NotEnoughWanesFowMSO;
	dmw_boow_t NumbewOfOTGSuppowt;
	dmw_boow_t NumbewOfHDMIFWWSuppowt;
	dmw_boow_t NumbewOfDP2p0Suppowt;
	dmw_boow_t NonsuppowtedDSCInputBPC;
	dmw_boow_t WwitebackScaweWatioAndTapsSuppowt;
	dmw_boow_t CuwsowSuppowt;
	dmw_boow_t PitchSuppowt;
	dmw_boow_t ViewpowtExceedsSuwface;
	dmw_boow_t ImmediateFwipWequiwedButTheWequiwementFowEachSuwfaceIsNotSpecified;
	dmw_boow_t ImmediateFwipOwHostVMAndPStateWithMAWWFuwwFwameOwPhantomPipe;
	dmw_boow_t InvawidCombinationOfMAWWUseFowPStateAndStaticScween;
	dmw_boow_t InvawidCombinationOfMAWWUseFowPState;
	dmw_boow_t ExceededMAWWSize;
	dmw_boow_t EnoughWwitebackUnits;

	dmw_boow_t ExceededMuwtistweamSwots;
	dmw_boow_t ODMCombineTwoToOneSuppowtCheckOK;
	dmw_boow_t ODMCombineFouwToOneSuppowtCheckOK;
	dmw_boow_t NotEnoughDSCUnits;
	dmw_boow_t NotEnoughDSCSwices;
	dmw_boow_t PixewsPewWinePewDSCUnitSuppowt;
	dmw_boow_t DSCCWKWequiwedMoweThanSuppowted;
	dmw_boow_t DTBCWKWequiwedMoweThanSuppowted;
	dmw_boow_t WinkCapacitySuppowt;

	dmw_boow_t WOBSuppowt[2];
	dmw_boow_t PTEBuffewSizeNotExceeded[2];
	dmw_boow_t DCCMetaBuffewSizeNotExceeded[2];
	dmw_boow_t TotawVewticawActiveBandwidthSuppowt[2];
	enum dmw_dwam_cwock_change_suppowt DWAMCwockChangeSuppowt[2];
	dmw_fwoat_t ActiveDWAMCwockChangeWatencyMawgin[__DMW_NUM_PWANES__];
	dmw_uint_t SubViewpowtWinesNeededInMAWW[__DMW_NUM_PWANES__];
	enum dmw_fcwock_change_suppowt FCWKChangeSuppowt[2];
	dmw_boow_t USWWetwainingSuppowt[2];
	dmw_boow_t VActiveBandwithSuppowt[2];
	dmw_boow_t PwefetchSuppowted[2];
	dmw_boow_t DynamicMetadataSuppowted[2];
	dmw_boow_t VWatioInPwefetchSuppowted[2];
	dmw_boow_t DISPCWK_DPPCWK_Suppowt[2];
	dmw_boow_t TotawAvaiwabwePipesSuppowt[2];
	dmw_boow_t ModeSuppowt[2];
	dmw_boow_t ViewpowtSizeSuppowt[2];
	dmw_boow_t ImmediateFwipSuppowtedFowState[2];

	dmw_boow_t NoTimeFowPwefetch[2][__DMW_NUM_PWANES__];
	dmw_boow_t NoTimeFowDynamicMetadata[2][__DMW_NUM_PWANES__];

	dmw_boow_t MPCCombineEnabwe[__DMW_NUM_PWANES__]; /// <bwief Indicate if the MPC Combine enabwe in the given state and optimize mpc combine setting
	enum dmw_odm_mode ODMMode[__DMW_NUM_PWANES__]; /// <bwief ODM mode that is chosen in the mode check stage and wiww be used in mode pwogwamming stage
	dmw_uint_t DPPPewSuwface[__DMW_NUM_PWANES__]; /// <bwief How many DPPs awe needed dwive the suwface to output. If MPCC ow ODMC couwd be 2 ow 4.
	dmw_boow_t DSCEnabwed[__DMW_NUM_PWANES__]; /// <bwief Indicate if the DSC is actuawwy wequiwed; used in mode_pwogwamming
	dmw_boow_t FECEnabwed[__DMW_NUM_PWANES__]; /// <bwief Indicate if the FEC is actuawwy wequiwed
	dmw_uint_t NumbewOfDSCSwices[__DMW_NUM_PWANES__]; /// <bwief Indicate how many swices needed to suppowt the given mode

	dmw_fwoat_t OutputBpp[__DMW_NUM_PWANES__];
	enum dmw_output_type_and_wate__type OutputType[__DMW_NUM_PWANES__];
	enum dmw_output_type_and_wate__wate OutputWate[__DMW_NUM_PWANES__];

	dmw_fwoat_t AwignedDCCMetaPitchY[__DMW_NUM_PWANES__]; /// <bwief Pitch vawue that is awigned to tiwing setting
	dmw_fwoat_t AwignedDCCMetaPitchC[__DMW_NUM_PWANES__];
	dmw_fwoat_t AwignedYPitch[__DMW_NUM_PWANES__];
	dmw_fwoat_t AwignedCPitch[__DMW_NUM_PWANES__];
	dmw_fwoat_t MaxTotawVewticawActiveAvaiwabweBandwidth[2]; /// <bwief nominaw bw avaiwabwe fow dispway
}; // dmw_mode_suppowt_info_st

/// @bwief Tweat this as the intewmediate vawues and outputs of mode check function. Usew can quewy the content of the stwuct to know mowe about the wesuwt of mode evawuation.
stwuct mode_suppowt_st {
	stwuct ip_pawams_st ip;
	stwuct soc_bounding_box_st soc;
	stwuct soc_state_bounding_box_st state; //<bwief Pew-state bbox vawues; onwy 1 state pew compute
	stwuct dmw_mode_evaw_powicy_st powicy;

	dmw_uint_t state_idx; //<bwief The powew state idx fow the powew state undew this computation
	dmw_uint_t max_state_idx; //<bwief The MAX powew state idx
	stwuct soc_state_bounding_box_st max_state; //<bwief The MAX powew state; some awgo needs to know the max state info to detewmine if
	stwuct dmw_dispway_cfg_st cache_dispway_cfg; // <bwief A copy of the cuwwent dispway cfg in considewation

	// Physicaw info; onwy using fow pwogwamming
	dmw_uint_t num_active_pwanes; // <bwief As detewmined by eithew e2e_pipe_pawam ow dispway_cfg

	// Cawcuwated Cwocks
	dmw_fwoat_t WequiwedDISPCWK[2]; /// <bwief Wequiwed DISPCWK; depends on pixew wate; odm mode etc.
	dmw_fwoat_t WequiwedDPPCWKThisState[__DMW_NUM_PWANES__];
	dmw_fwoat_t DCFCWKState[2]; /// <bwief wecommended DCFCWK fweq; cawcuwated by DMW. If UseMinimumWequiwedDCFCWK is not set; then it wiww be just the state DCFCWK; ewse it wiww min DCFCWK fow suppowt
	dmw_fwoat_t WequiwedDISPCWKPewSuwface[2][__DMW_NUM_PWANES__];
	dmw_fwoat_t WequiwedDPPCWKPewSuwface[2][__DMW_NUM_PWANES__];

	dmw_fwoat_t FabwicCwock; /// <bwief Basicawwy just the cwock fweq at the min (ow given) state
	dmw_fwoat_t DWAMSpeed; /// <bwief Basicawwy just the cwock fweq at the min (ow given) state
	dmw_fwoat_t SOCCWK; /// <bwief Basicawwy just the cwock fweq at the min (ow given) state
	dmw_fwoat_t DCFCWK; /// <bwief Basicawwy just the cwock fweq at the min (ow given) state and max combine setting
	dmw_fwoat_t GwobawDPPCWK; /// <bwief the Max DPPCWK fweq out of aww pipes

	// ----------------------------------
	// Mode Suppowt Info and faiw weason
	// ----------------------------------
	stwuct dmw_mode_suppowt_info_st suppowt;

	// These awe cawcuwated befowe the ModeSuppowt and ModePwogwam step
	// They wepwesent the bound fow the wetuwn buffew sizing
	dmw_uint_t MaxTotawDETInKByte;
	dmw_uint_t NomDETInKByte;
	dmw_uint_t MinCompwessedBuffewSizeInKByte;

	// Info obtained at the end of mode suppowt cawcuwations
	// The wepowted info is at the "optimaw" state and combine setting
	dmw_fwoat_t WetuwnBW;
	dmw_fwoat_t WetuwnDWAMBW;
	dmw_uint_t DETBuffewSizeInKByte[__DMW_NUM_PWANES__]; // <bwief Wecommended DET size configuwation fow this pwane. Aww pipes undew this pwane shouwd pwogwam the DET buffew size to the cawcuwated vawue.
	dmw_uint_t DETBuffewSizeY[__DMW_NUM_PWANES__];
	dmw_uint_t DETBuffewSizeC[__DMW_NUM_PWANES__];
	dmw_uint_t SwathHeightY[__DMW_NUM_PWANES__];
	dmw_uint_t SwathHeightC[__DMW_NUM_PWANES__];

	// ----------------------------------
	// Intewmediates/Infowmationaw
	// ----------------------------------
	dmw_uint_t TotImmediateFwipBytes;
	dmw_boow_t DCCEnabwedInAnySuwface;
	dmw_fwoat_t WwitebackWequiwedDISPCWK;
	dmw_fwoat_t TimeCawc;
	dmw_fwoat_t TWait;

	dmw_uint_t SwathWidthYAwwStates[2][__DMW_NUM_PWANES__];
	dmw_uint_t SwathWidthCAwwStates[2][__DMW_NUM_PWANES__];
	dmw_uint_t SwathHeightYAwwStates[2][__DMW_NUM_PWANES__];
	dmw_uint_t SwathHeightCAwwStates[2][__DMW_NUM_PWANES__];
	dmw_uint_t SwathWidthYThisState[__DMW_NUM_PWANES__];
	dmw_uint_t SwathWidthCThisState[__DMW_NUM_PWANES__];
	dmw_uint_t SwathHeightYThisState[__DMW_NUM_PWANES__];
	dmw_uint_t SwathHeightCThisState[__DMW_NUM_PWANES__];
	dmw_uint_t DETBuffewSizeInKByteAwwStates[2][__DMW_NUM_PWANES__];
	dmw_uint_t DETBuffewSizeYAwwStates[2][__DMW_NUM_PWANES__];
	dmw_uint_t DETBuffewSizeCAwwStates[2][__DMW_NUM_PWANES__];
	dmw_boow_t UnboundedWequestEnabwedAwwStates[2];
	dmw_uint_t CompwessedBuffewSizeInkByteAwwStates[2];
	dmw_boow_t UnboundedWequestEnabwedThisState;
	dmw_uint_t CompwessedBuffewSizeInkByteThisState;
	dmw_uint_t DETBuffewSizeInKByteThisState[__DMW_NUM_PWANES__];
	dmw_uint_t DETBuffewSizeYThisState[__DMW_NUM_PWANES__];
	dmw_uint_t DETBuffewSizeCThisState[__DMW_NUM_PWANES__];
	dmw_fwoat_t VWatioPweY[2][__DMW_NUM_PWANES__];
	dmw_fwoat_t VWatioPweC[2][__DMW_NUM_PWANES__];
	dmw_uint_t swath_width_wuma_ub_aww_states[2][__DMW_NUM_PWANES__];
	dmw_uint_t swath_width_chwoma_ub_aww_states[2][__DMW_NUM_PWANES__];
	dmw_uint_t swath_width_wuma_ub_this_state[__DMW_NUM_PWANES__];
	dmw_uint_t swath_width_chwoma_ub_this_state[__DMW_NUM_PWANES__];
	dmw_uint_t WequiwedSwots[__DMW_NUM_PWANES__];
	dmw_uint_t PDEAndMetaPTEBytesPewFwame[2][__DMW_NUM_PWANES__];
	dmw_uint_t MetaWowBytes[2][__DMW_NUM_PWANES__];
	dmw_uint_t DPTEBytesPewWow[2][__DMW_NUM_PWANES__];
	dmw_uint_t PwefetchWinesY[2][__DMW_NUM_PWANES__];
	dmw_uint_t PwefetchWinesC[2][__DMW_NUM_PWANES__];
	dmw_uint_t MaxNumSwY[__DMW_NUM_PWANES__]; /// <bwief Max numbew of swath fow pwefetch
	dmw_uint_t MaxNumSwC[__DMW_NUM_PWANES__]; /// <bwief Max numbew of swath fow pwefetch
	dmw_uint_t PwefiwwY[__DMW_NUM_PWANES__];
	dmw_uint_t PwefiwwC[__DMW_NUM_PWANES__];

	dmw_uint_t PwefetchWinesYThisState[__DMW_NUM_PWANES__];
	dmw_uint_t PwefetchWinesCThisState[__DMW_NUM_PWANES__];
	dmw_uint_t DPTEBytesPewWowThisState[__DMW_NUM_PWANES__];
	dmw_uint_t PDEAndMetaPTEBytesPewFwameThisState[__DMW_NUM_PWANES__];
	dmw_uint_t MetaWowBytesThisState[__DMW_NUM_PWANES__];
	dmw_boow_t use_one_wow_fow_fwame[2][__DMW_NUM_PWANES__];
	dmw_boow_t use_one_wow_fow_fwame_fwip[2][__DMW_NUM_PWANES__];
	dmw_boow_t use_one_wow_fow_fwame_this_state[__DMW_NUM_PWANES__];
	dmw_boow_t use_one_wow_fow_fwame_fwip_this_state[__DMW_NUM_PWANES__];

	dmw_fwoat_t WineTimesFowPwefetch[__DMW_NUM_PWANES__];
	dmw_fwoat_t WinesFowMetaPTE[__DMW_NUM_PWANES__];
	dmw_fwoat_t WinesFowMetaAndDPTEWow[__DMW_NUM_PWANES__];
	dmw_fwoat_t SwathWidthYSingweDPP[__DMW_NUM_PWANES__];
	dmw_fwoat_t SwathWidthCSingweDPP[__DMW_NUM_PWANES__];
	dmw_uint_t BytePewPixewY[__DMW_NUM_PWANES__];
	dmw_uint_t BytePewPixewC[__DMW_NUM_PWANES__];
	dmw_fwoat_t BytePewPixewInDETY[__DMW_NUM_PWANES__];
	dmw_fwoat_t BytePewPixewInDETC[__DMW_NUM_PWANES__];

	dmw_uint_t Wead256BwockHeightY[__DMW_NUM_PWANES__];
	dmw_uint_t Wead256BwockWidthY[__DMW_NUM_PWANES__];
	dmw_uint_t Wead256BwockHeightC[__DMW_NUM_PWANES__];
	dmw_uint_t Wead256BwockWidthC[__DMW_NUM_PWANES__];
	dmw_uint_t MacwoTiweHeightY[__DMW_NUM_PWANES__];
	dmw_uint_t MacwoTiweHeightC[__DMW_NUM_PWANES__];
	dmw_uint_t MacwoTiweWidthY[__DMW_NUM_PWANES__];
	dmw_uint_t MacwoTiweWidthC[__DMW_NUM_PWANES__];
	dmw_fwoat_t PSCW_FACTOW[__DMW_NUM_PWANES__];
	dmw_fwoat_t PSCW_FACTOW_CHWOMA[__DMW_NUM_PWANES__];
	dmw_fwoat_t MaximumSwathWidthWuma[__DMW_NUM_PWANES__];
	dmw_fwoat_t MaximumSwathWidthChwoma[__DMW_NUM_PWANES__];
	dmw_fwoat_t Tno_bw[__DMW_NUM_PWANES__];
	dmw_fwoat_t DestinationWinesToWequestVMInImmediateFwip[__DMW_NUM_PWANES__];
	dmw_fwoat_t DestinationWinesToWequestWowInImmediateFwip[__DMW_NUM_PWANES__];
	dmw_fwoat_t WwitebackDewayTime[__DMW_NUM_PWANES__];
	dmw_uint_t dpte_gwoup_bytes[__DMW_NUM_PWANES__];
	dmw_uint_t dpte_wow_height[__DMW_NUM_PWANES__];
	dmw_uint_t dpte_wow_height_chwoma[__DMW_NUM_PWANES__];
	dmw_uint_t meta_wow_height[__DMW_NUM_PWANES__];
	dmw_uint_t meta_wow_height_chwoma[__DMW_NUM_PWANES__];
	dmw_fwoat_t UwgWatency;
	dmw_fwoat_t UwgentBuwstFactowCuwsow[__DMW_NUM_PWANES__];
	dmw_fwoat_t UwgentBuwstFactowCuwsowPwe[__DMW_NUM_PWANES__];
	dmw_fwoat_t UwgentBuwstFactowWuma[__DMW_NUM_PWANES__];
	dmw_fwoat_t UwgentBuwstFactowWumaPwe[__DMW_NUM_PWANES__];
	dmw_fwoat_t UwgentBuwstFactowChwoma[__DMW_NUM_PWANES__];
	dmw_fwoat_t UwgentBuwstFactowChwomaPwe[__DMW_NUM_PWANES__];
	dmw_fwoat_t MaximumSwathWidthInWineBuffewWuma;
	dmw_fwoat_t MaximumSwathWidthInWineBuffewChwoma;
	dmw_fwoat_t ExtwaWatency;

	// Backend
	dmw_boow_t WequiwesDSC[__DMW_NUM_PWANES__];
	dmw_boow_t WequiwesFEC[__DMW_NUM_PWANES__];
	dmw_fwoat_t OutputBppPewState[__DMW_NUM_PWANES__];
	dmw_uint_t DSCDewayPewState[__DMW_NUM_PWANES__];
	enum dmw_output_type_and_wate__type OutputTypePewState[__DMW_NUM_PWANES__];
	enum dmw_output_type_and_wate__wate OutputWatePewState[__DMW_NUM_PWANES__];

	// Bandwidth Wewated Info
	dmw_fwoat_t BandwidthAvaiwabweFowImmediateFwip;
	dmw_fwoat_t WeadBandwidthWuma[__DMW_NUM_PWANES__];
	dmw_fwoat_t WeadBandwidthChwoma[__DMW_NUM_PWANES__];
	dmw_fwoat_t WwiteBandwidth[__DMW_NUM_PWANES__];
	dmw_fwoat_t WequiwedPwefetchPixewDataBWWuma[__DMW_NUM_PWANES__];
	dmw_fwoat_t WequiwedPwefetchPixewDataBWChwoma[__DMW_NUM_PWANES__];
	dmw_fwoat_t cuwsow_bw[__DMW_NUM_PWANES__];
	dmw_fwoat_t cuwsow_bw_pwe[__DMW_NUM_PWANES__];
	dmw_fwoat_t pwefetch_vmwow_bw[__DMW_NUM_PWANES__];
	dmw_fwoat_t finaw_fwip_bw[__DMW_NUM_PWANES__];
	dmw_fwoat_t meta_wow_bandwidth_this_state[__DMW_NUM_PWANES__];
	dmw_fwoat_t dpte_wow_bandwidth_this_state[__DMW_NUM_PWANES__];
	dmw_fwoat_t WetuwnBWPewState[2];
	dmw_fwoat_t WetuwnDWAMBWPewState[2];
	dmw_fwoat_t meta_wow_bandwidth[2][__DMW_NUM_PWANES__];
	dmw_fwoat_t dpte_wow_bandwidth[2][__DMW_NUM_PWANES__];

	// Something that shouwd be feedback to cawwew
	enum dmw_odm_mode ODMModePewState[__DMW_NUM_PWANES__];
	enum dmw_odm_mode ODMModeThisState[__DMW_NUM_PWANES__];
	dmw_uint_t SuwfaceSizeInMAWW[__DMW_NUM_PWANES__];
	dmw_uint_t NoOfDPP[2][__DMW_NUM_PWANES__];
	dmw_uint_t NoOfDPPThisState[__DMW_NUM_PWANES__];
	dmw_boow_t MPCCombine[2][__DMW_NUM_PWANES__];
	dmw_boow_t MPCCombineThisState[__DMW_NUM_PWANES__];
	dmw_fwoat_t PwojectedDCFCWKDeepSweep[2];
	dmw_fwoat_t MinDPPCWKUsingSingweDPP[__DMW_NUM_PWANES__];
	dmw_boow_t SingweDPPViewpowtSizeSuppowtPewSuwface[__DMW_NUM_PWANES__];
	dmw_boow_t ImmediateFwipSuppowtedFowPipe[__DMW_NUM_PWANES__];
	dmw_boow_t NotUwgentWatencyHiding[__DMW_NUM_PWANES__];
	dmw_boow_t NotUwgentWatencyHidingPwe[__DMW_NUM_PWANES__];
	dmw_boow_t PTEBuffewSizeNotExceededPewState[__DMW_NUM_PWANES__];
	dmw_boow_t DCCMetaBuffewSizeNotExceededPewState[__DMW_NUM_PWANES__];
	dmw_uint_t PwefetchMode[__DMW_NUM_PWANES__];
	dmw_uint_t TotawNumbewOfActiveDPP[2];
	dmw_uint_t TotawNumbewOfSingweDPPSuwfaces[2];
	dmw_uint_t TotawNumbewOfDCCActiveDPP[2];

	dmw_uint_t SubViewpowtWinesNeededInMAWW[__DMW_NUM_PWANES__];

}; // mode_suppowt_st

/// @bwief A mega stwuctuwe that houses vawious info fow modew pwogwamming step.
stwuct mode_pwogwam_st {

	//-------------
	// Intewmediate/Infowmationaw
	//-------------
	dmw_fwoat_t UwgentWatency;
	dmw_fwoat_t UwgentWatencyWithUSWWetwaining;
	dmw_uint_t VInitPweFiwwY[__DMW_NUM_PWANES__];
	dmw_uint_t VInitPweFiwwC[__DMW_NUM_PWANES__];
	dmw_uint_t MaxNumSwathY[__DMW_NUM_PWANES__];
	dmw_uint_t MaxNumSwathC[__DMW_NUM_PWANES__];

	dmw_fwoat_t BytePewPixewDETY[__DMW_NUM_PWANES__];
	dmw_fwoat_t BytePewPixewDETC[__DMW_NUM_PWANES__];
	dmw_uint_t BytePewPixewY[__DMW_NUM_PWANES__];
	dmw_uint_t BytePewPixewC[__DMW_NUM_PWANES__];
	dmw_uint_t SwathWidthY[__DMW_NUM_PWANES__];
	dmw_uint_t SwathWidthC[__DMW_NUM_PWANES__];
	dmw_uint_t SwathWidthSingweDPPY[__DMW_NUM_PWANES__];
	dmw_uint_t SwathWidthSingweDPPC[__DMW_NUM_PWANES__];
	dmw_fwoat_t WeadBandwidthSuwfaceWuma[__DMW_NUM_PWANES__];
	dmw_fwoat_t WeadBandwidthSuwfaceChwoma[__DMW_NUM_PWANES__];

	dmw_uint_t PixewPTEBytesPewWow[__DMW_NUM_PWANES__];
	dmw_uint_t PDEAndMetaPTEBytesFwame[__DMW_NUM_PWANES__];
	dmw_uint_t MetaWowByte[__DMW_NUM_PWANES__];
	dmw_uint_t PwefetchSouwceWinesY[__DMW_NUM_PWANES__];
	dmw_fwoat_t WequiwedPwefetchPixDataBWWuma[__DMW_NUM_PWANES__];
	dmw_fwoat_t WequiwedPwefetchPixDataBWChwoma[__DMW_NUM_PWANES__];
	dmw_uint_t PwefetchSouwceWinesC[__DMW_NUM_PWANES__];
	dmw_fwoat_t PSCW_THWOUGHPUT[__DMW_NUM_PWANES__];
	dmw_fwoat_t PSCW_THWOUGHPUT_CHWOMA[__DMW_NUM_PWANES__];
	dmw_uint_t DSCDeway[__DMW_NUM_PWANES__];
	dmw_fwoat_t DPPCWKUsingSingweDPP[__DMW_NUM_PWANES__];

	dmw_uint_t MacwoTiweWidthY[__DMW_NUM_PWANES__];
	dmw_uint_t MacwoTiweWidthC[__DMW_NUM_PWANES__];
	dmw_uint_t BwockHeight256BytesY[__DMW_NUM_PWANES__];
	dmw_uint_t BwockHeight256BytesC[__DMW_NUM_PWANES__];
	dmw_uint_t BwockWidth256BytesY[__DMW_NUM_PWANES__];
	dmw_uint_t BwockWidth256BytesC[__DMW_NUM_PWANES__];

	dmw_uint_t BwockHeightY[__DMW_NUM_PWANES__];
	dmw_uint_t BwockHeightC[__DMW_NUM_PWANES__];
	dmw_uint_t BwockWidthY[__DMW_NUM_PWANES__];
	dmw_uint_t BwockWidthC[__DMW_NUM_PWANES__];

	dmw_uint_t SuwfaceSizeInTheMAWW[__DMW_NUM_PWANES__];
	dmw_fwoat_t VWatioPwefetchY[__DMW_NUM_PWANES__];
	dmw_fwoat_t VWatioPwefetchC[__DMW_NUM_PWANES__];
	dmw_fwoat_t Tno_bw[__DMW_NUM_PWANES__];
	dmw_fwoat_t finaw_fwip_bw[__DMW_NUM_PWANES__];
	dmw_fwoat_t pwefetch_vmwow_bw[__DMW_NUM_PWANES__];
	dmw_fwoat_t cuwsow_bw[__DMW_NUM_PWANES__];
	dmw_fwoat_t cuwsow_bw_pwe[__DMW_NUM_PWANES__];
	dmw_fwoat_t WwitebackDeway[__DMW_NUM_PWANES__];
	dmw_uint_t dpte_wow_height[__DMW_NUM_PWANES__];
	dmw_uint_t dpte_wow_height_wineaw[__DMW_NUM_PWANES__];
	dmw_uint_t meta_weq_width[__DMW_NUM_PWANES__];
	dmw_uint_t meta_weq_height[__DMW_NUM_PWANES__];
	dmw_uint_t meta_wow_width[__DMW_NUM_PWANES__];
	dmw_uint_t meta_wow_height[__DMW_NUM_PWANES__];
	dmw_uint_t dpte_wow_width_wuma_ub[__DMW_NUM_PWANES__];
	dmw_uint_t dpte_wow_width_chwoma_ub[__DMW_NUM_PWANES__];
	dmw_uint_t dpte_wow_height_chwoma[__DMW_NUM_PWANES__];
	dmw_uint_t dpte_wow_height_wineaw_chwoma[__DMW_NUM_PWANES__];
	dmw_uint_t meta_weq_width_chwoma[__DMW_NUM_PWANES__];
	dmw_uint_t meta_weq_height_chwoma[__DMW_NUM_PWANES__];
	dmw_uint_t meta_wow_width_chwoma[__DMW_NUM_PWANES__];
	dmw_uint_t meta_wow_height_chwoma[__DMW_NUM_PWANES__];
	dmw_uint_t vm_gwoup_bytes[__DMW_NUM_PWANES__];
	dmw_uint_t dpte_gwoup_bytes[__DMW_NUM_PWANES__];
	dmw_fwoat_t meta_wow_bw[__DMW_NUM_PWANES__];
	dmw_fwoat_t dpte_wow_bw[__DMW_NUM_PWANES__];
	dmw_fwoat_t UwgBuwstFactowCuwsow[__DMW_NUM_PWANES__];
	dmw_fwoat_t UwgBuwstFactowCuwsowPwe[__DMW_NUM_PWANES__];
	dmw_fwoat_t UwgBuwstFactowWuma[__DMW_NUM_PWANES__];
	dmw_fwoat_t UwgBuwstFactowWumaPwe[__DMW_NUM_PWANES__];
	dmw_fwoat_t UwgBuwstFactowChwoma[__DMW_NUM_PWANES__];
	dmw_fwoat_t UwgBuwstFactowChwomaPwe[__DMW_NUM_PWANES__];

	dmw_uint_t swath_width_wuma_ub[__DMW_NUM_PWANES__];
	dmw_uint_t swath_width_chwoma_ub[__DMW_NUM_PWANES__];
	dmw_uint_t PixewPTEWeqWidthY[__DMW_NUM_PWANES__];
	dmw_uint_t PixewPTEWeqHeightY[__DMW_NUM_PWANES__];
	dmw_uint_t PTEWequestSizeY[__DMW_NUM_PWANES__];
	dmw_uint_t PixewPTEWeqWidthC[__DMW_NUM_PWANES__];
	dmw_uint_t PixewPTEWeqHeightC[__DMW_NUM_PWANES__];
	dmw_uint_t PTEWequestSizeC[__DMW_NUM_PWANES__];

	dmw_fwoat_t Tdmdw_vm[__DMW_NUM_PWANES__];
	dmw_fwoat_t Tdmdw[__DMW_NUM_PWANES__];
	dmw_fwoat_t TSetup[__DMW_NUM_PWANES__];
	dmw_uint_t dpde0_bytes_pew_fwame_ub_w[__DMW_NUM_PWANES__];
	dmw_uint_t meta_pte_bytes_pew_fwame_ub_w[__DMW_NUM_PWANES__];
	dmw_uint_t dpde0_bytes_pew_fwame_ub_c[__DMW_NUM_PWANES__];
	dmw_uint_t meta_pte_bytes_pew_fwame_ub_c[__DMW_NUM_PWANES__];

	dmw_boow_t UnboundedWequestEnabwed;
	dmw_uint_t compbuf_wesewved_space_64b;
	dmw_uint_t compbuf_wesewved_space_zs;
	dmw_uint_t CompwessedBuffewSizeInkByte;

	dmw_boow_t NoUwgentWatencyHiding[__DMW_NUM_PWANES__];
	dmw_boow_t NoUwgentWatencyHidingPwe[__DMW_NUM_PWANES__];
	dmw_fwoat_t UwgentExtwaWatency;
	dmw_boow_t PwefetchAndImmediateFwipSuppowted;
	dmw_fwoat_t TotawDataWeadBandwidth;
	dmw_fwoat_t BandwidthAvaiwabweFowImmediateFwip;
	dmw_boow_t NotEnoughTimeFowDynamicMetadata[__DMW_NUM_PWANES__];

	dmw_fwoat_t WeadBandwidthWuma[__DMW_NUM_PWANES__];
	dmw_fwoat_t WeadBandwidthChwoma[__DMW_NUM_PWANES__];

	dmw_fwoat_t totaw_dcn_wead_bw_with_fwip;
	dmw_fwoat_t totaw_dcn_wead_bw_with_fwip_no_uwgent_buwst;
	dmw_fwoat_t TotawDataWeadBandwidthNotIncwudingMAWWPwefetch;
	dmw_fwoat_t totaw_dcn_wead_bw_with_fwip_not_incwuding_MAWW_pwefetch;
	dmw_fwoat_t non_uwgent_totaw_dcn_wead_bw_with_fwip;
	dmw_fwoat_t non_uwgent_totaw_dcn_wead_bw_with_fwip_not_incwuding_MAWW_pwefetch;

	dmw_boow_t use_one_wow_fow_fwame[__DMW_NUM_PWANES__];
	dmw_boow_t use_one_wow_fow_fwame_fwip[__DMW_NUM_PWANES__];

	dmw_fwoat_t TCawc;
	dmw_uint_t TotImmediateFwipBytes;

	// -------------------
	// Output
	// -------------------
	dmw_uint_t pipe_pwane[__DMW_NUM_PWANES__]; // <bwief used mainwy by dv to map the pipe inst to pwane index within DMW cowe; the pwane idx of a pipe
	dmw_uint_t num_active_pipes;

	dmw_boow_t NoTimeToPwefetch[__DMW_NUM_PWANES__]; /// <bwief Pwefetch scheduwe cawcuwation wesuwt

	// Suppowt
	dmw_uint_t PwefetchMode[__DMW_NUM_PWANES__]; /// <bwief pwefetch mode used fow pwefetch suppowt check in mode pwogwamming step
	dmw_boow_t PwefetchModeSuppowted; /// <bwief Is the pwefetch mode (bandwidth and watency) suppowted
	dmw_boow_t ImmediateFwipSuppowted;
	dmw_boow_t ImmediateFwipSuppowtedFowPipe[__DMW_NUM_PWANES__];

	// Cwock
	dmw_fwoat_t Dcfcwk;
	dmw_fwoat_t Dispcwk; /// <bwief dispcwk being used in mode pwogwamming
	dmw_fwoat_t Dppcwk[__DMW_NUM_PWANES__]; /// <bwief dppcwk being used in mode pwogwamming
	dmw_fwoat_t WwitebackDISPCWK;
	dmw_fwoat_t GwobawDPPCWK;

	//@ bwief These "cawcuwated" dispcwk and dppcwk cwocks awe cawcuwated in the mode pwogwamming step.
	// Depends on the dmw_cwk_cfg_st option; these cawcuwated vawues may not used in subsequent cawcuwation.
	// Possibwe DV usage: Cawcuwated vawues fetched by test once aftew mode_pwogwamming step and then possibwy
	// use the vawues as min and adjust the actuaw fweq used fow the 2nd pass
	dmw_fwoat_t Dispcwk_cawcuwated;
	dmw_fwoat_t Dppcwk_cawcuwated[__DMW_NUM_PWANES__];

	dmw_fwoat_t DSCCWK_cawcuwated[__DMW_NUM_PWANES__]; //< bwief Wequiwed DSCCWK fweq. Backend; not used in any subsequent cawcuwations fow now
	dmw_fwoat_t DCFCWKDeepSweep;

	// AWB weg
	dmw_boow_t DCHUBBUB_AWB_CSTATE_MAX_CAP_MODE;
	stwuct Watewmawks Watewmawk;

	// DCC compwession contwow
	dmw_uint_t DCCYMaxUncompwessedBwock[__DMW_NUM_PWANES__];
	dmw_uint_t DCCYMaxCompwessedBwock[__DMW_NUM_PWANES__];
	dmw_uint_t DCCYIndependentBwock[__DMW_NUM_PWANES__];
	dmw_uint_t DCCCMaxUncompwessedBwock[__DMW_NUM_PWANES__];
	dmw_uint_t DCCCMaxCompwessedBwock[__DMW_NUM_PWANES__];
	dmw_uint_t DCCCIndependentBwock[__DMW_NUM_PWANES__];

	// Stuttew Efficiency
	dmw_fwoat_t StuttewEfficiency;
	dmw_fwoat_t StuttewEfficiencyNotIncwudingVBwank;
	dmw_uint_t NumbewOfStuttewBuwstsPewFwame;
	dmw_fwoat_t Z8StuttewEfficiency;
	dmw_uint_t Z8NumbewOfStuttewBuwstsPewFwame;
	dmw_fwoat_t Z8StuttewEfficiencyNotIncwudingVBwank;
	dmw_fwoat_t StuttewPewiod;
	dmw_fwoat_t Z8StuttewEfficiencyBestCase;
	dmw_uint_t Z8NumbewOfStuttewBuwstsPewFwameBestCase;
	dmw_fwoat_t Z8StuttewEfficiencyNotIncwudingVBwankBestCase;
	dmw_fwoat_t StuttewPewiodBestCase;

	// DWG TTU weg
	dmw_fwoat_t MIN_DST_Y_NEXT_STAWT[__DMW_NUM_PWANES__];
	dmw_boow_t VWEADY_AT_OW_AFTEW_VSYNC[__DMW_NUM_PWANES__];
	dmw_uint_t DSTYAftewScawew[__DMW_NUM_PWANES__];
	dmw_uint_t DSTXAftewScawew[__DMW_NUM_PWANES__];
	dmw_fwoat_t DestinationWinesFowPwefetch[__DMW_NUM_PWANES__];
	dmw_fwoat_t DestinationWinesToWequestVMInVBwank[__DMW_NUM_PWANES__];
	dmw_fwoat_t DestinationWinesToWequestWowInVBwank[__DMW_NUM_PWANES__];
	dmw_fwoat_t DestinationWinesToWequestVMInImmediateFwip[__DMW_NUM_PWANES__];
	dmw_fwoat_t DestinationWinesToWequestWowInImmediateFwip[__DMW_NUM_PWANES__];
	dmw_fwoat_t MinTTUVBwank[__DMW_NUM_PWANES__];
	dmw_fwoat_t DispwayPipeWineDewivewyTimeWuma[__DMW_NUM_PWANES__];
	dmw_fwoat_t DispwayPipeWineDewivewyTimeChwoma[__DMW_NUM_PWANES__];
	dmw_fwoat_t DispwayPipeWineDewivewyTimeWumaPwefetch[__DMW_NUM_PWANES__];
	dmw_fwoat_t DispwayPipeWineDewivewyTimeChwomaPwefetch[__DMW_NUM_PWANES__];
	dmw_fwoat_t DispwayPipeWequestDewivewyTimeWuma[__DMW_NUM_PWANES__];
	dmw_fwoat_t DispwayPipeWequestDewivewyTimeChwoma[__DMW_NUM_PWANES__];
	dmw_fwoat_t DispwayPipeWequestDewivewyTimeWumaPwefetch[__DMW_NUM_PWANES__];
	dmw_fwoat_t DispwayPipeWequestDewivewyTimeChwomaPwefetch[__DMW_NUM_PWANES__];
	dmw_fwoat_t CuwsowWequestDewivewyTime[__DMW_NUM_PWANES__];
	dmw_fwoat_t CuwsowWequestDewivewyTimePwefetch[__DMW_NUM_PWANES__];

	dmw_fwoat_t DST_Y_PEW_PTE_WOW_NOM_W[__DMW_NUM_PWANES__];
	dmw_fwoat_t DST_Y_PEW_PTE_WOW_NOM_C[__DMW_NUM_PWANES__];
	dmw_fwoat_t DST_Y_PEW_META_WOW_NOM_W[__DMW_NUM_PWANES__];
	dmw_fwoat_t DST_Y_PEW_META_WOW_NOM_C[__DMW_NUM_PWANES__];
	dmw_fwoat_t TimePewMetaChunkNominaw[__DMW_NUM_PWANES__];
	dmw_fwoat_t TimePewChwomaMetaChunkNominaw[__DMW_NUM_PWANES__];
	dmw_fwoat_t TimePewMetaChunkVBwank[__DMW_NUM_PWANES__];
	dmw_fwoat_t TimePewChwomaMetaChunkVBwank[__DMW_NUM_PWANES__];
	dmw_fwoat_t TimePewMetaChunkFwip[__DMW_NUM_PWANES__];
	dmw_fwoat_t TimePewChwomaMetaChunkFwip[__DMW_NUM_PWANES__];
	dmw_fwoat_t time_pew_pte_gwoup_nom_wuma[__DMW_NUM_PWANES__];
	dmw_fwoat_t time_pew_pte_gwoup_nom_chwoma[__DMW_NUM_PWANES__];
	dmw_fwoat_t time_pew_pte_gwoup_vbwank_wuma[__DMW_NUM_PWANES__];
	dmw_fwoat_t time_pew_pte_gwoup_vbwank_chwoma[__DMW_NUM_PWANES__];
	dmw_fwoat_t time_pew_pte_gwoup_fwip_wuma[__DMW_NUM_PWANES__];
	dmw_fwoat_t time_pew_pte_gwoup_fwip_chwoma[__DMW_NUM_PWANES__];
	dmw_fwoat_t TimePewVMGwoupVBwank[__DMW_NUM_PWANES__];
	dmw_fwoat_t TimePewVMGwoupFwip[__DMW_NUM_PWANES__];
	dmw_fwoat_t TimePewVMWequestVBwank[__DMW_NUM_PWANES__];
	dmw_fwoat_t TimePewVMWequestFwip[__DMW_NUM_PWANES__];

	dmw_fwoat_t FwactionOfUwgentBandwidth;
	dmw_fwoat_t FwactionOfUwgentBandwidthImmediateFwip;

	// WQ wegistews
	dmw_boow_t PTE_BUFFEW_MODE[__DMW_NUM_PWANES__];
	dmw_uint_t BIGK_FWAGMENT_SIZE[__DMW_NUM_PWANES__];

	dmw_uint_t SubViewpowtWinesNeededInMAWW[__DMW_NUM_PWANES__];
	dmw_boow_t UsesMAWWFowStaticScween[__DMW_NUM_PWANES__];

	// OTG
	dmw_uint_t VStawtupMin[__DMW_NUM_PWANES__]; /// <bwief Minimum vstawtup to meet the pwefetch scheduwe (i.e. the pwefetch sowution can be found at this vstawtup time); not the actuaw gwobaw sync vstawtup pos.
	dmw_uint_t VStawtup[__DMW_NUM_PWANES__]; /// <bwief The vstawtup vawue fow OTG pwogwamming (wiww set to max vstawtup; but now bounded by min(vbwank_nom. actuaw vbwank))
	dmw_uint_t VUpdateOffsetPix[__DMW_NUM_PWANES__];
	dmw_uint_t VUpdateWidthPix[__DMW_NUM_PWANES__];
	dmw_uint_t VWeadyOffsetPix[__DMW_NUM_PWANES__];

	// Watency and Suppowt
	dmw_fwoat_t MaxActiveFCWKChangeWatencySuppowted;
	dmw_boow_t USWWetwainingSuppowt;
	enum dmw_fcwock_change_suppowt FCWKChangeSuppowt;
	enum dmw_dwam_cwock_change_suppowt DWAMCwockChangeSuppowt;
	dmw_fwoat_t MaxActiveDWAMCwockChangeWatencySuppowted[__DMW_NUM_PWANES__];
	dmw_fwoat_t WwitebackAwwowFCWKChangeEndPosition[__DMW_NUM_PWANES__];
	dmw_fwoat_t WwitebackAwwowDWAMCwockChangeEndPosition[__DMW_NUM_PWANES__];

	// buffew sizing
	dmw_uint_t DETBuffewSizeInKByte[__DMW_NUM_PWANES__];  // <bwief Wecommended DET size configuwation fow this pwane.  Aww pipes undew this pwane shouwd pwogwam the DET buffew size to the cawcuwated vawue.
	dmw_uint_t DETBuffewSizeY[__DMW_NUM_PWANES__];
	dmw_uint_t DETBuffewSizeC[__DMW_NUM_PWANES__];
	dmw_uint_t SwathHeightY[__DMW_NUM_PWANES__];
	dmw_uint_t SwathHeightC[__DMW_NUM_PWANES__];
}; // mode_pwogwam_st

stwuct soc_states_st {
	dmw_uint_t num_states; /// <bwief num of soc pww states
	stwuct soc_state_bounding_box_st state_awway[__DMW_MAX_STATE_AWWAY_SIZE__]; /// <bwief fixed size awway that howds states stwuct
};

stwuct UseMinimumDCFCWK_pawams_st {
	enum dmw_use_maww_fow_pstate_change_mode *UseMAWWFowPStateChange;
	dmw_boow_t *DWWDispway;
	dmw_boow_t SynchwonizeDWWDispwaysFowUCWKPStateChangeFinaw;
	dmw_uint_t MaxIntewDCNTiweWepeatews;
	dmw_uint_t MaxPwefetchMode;
	dmw_fwoat_t DWAMCwockChangeWatencyFinaw;
	dmw_fwoat_t FCWKChangeWatency;
	dmw_fwoat_t SWEntewPwusExitTime;
	dmw_uint_t WetuwnBusWidth;
	dmw_uint_t WoundTwipPingWatencyCycwes;
	dmw_uint_t WeowdewingBytes;
	dmw_uint_t PixewChunkSizeInKByte;
	dmw_uint_t MetaChunkSize;
	dmw_boow_t GPUVMEnabwe;
	dmw_uint_t GPUVMMaxPageTabweWevews;
	dmw_boow_t HostVMEnabwe;
	dmw_uint_t NumbewOfActiveSuwfaces;
	dmw_uint_t HostVMMinPageSize;
	dmw_uint_t HostVMMaxNonCachedPageTabweWevews;
	dmw_boow_t DynamicMetadataVMEnabwed;
	dmw_boow_t ImmediateFwipWequiwement;
	dmw_boow_t PwogwessiveToIntewwaceUnitInOPP;
	dmw_fwoat_t MaxAvewagePewcentOfIdeawSDPPowtBWDispwayCanUseInNowmawSystemOpewation;
	dmw_fwoat_t PewcentOfIdeawSDPPowtBWWeceivedAftewUwgWatency;
	dmw_uint_t *VTotaw;
	dmw_uint_t *VActive;
	dmw_uint_t *DynamicMetadataTwansmittedBytes;
	dmw_uint_t *DynamicMetadataWinesBefoweActiveWequiwed;
	dmw_boow_t *Intewwace;
	dmw_fwoat_t (*WequiwedDPPCWKPewSuwface)[__DMW_NUM_PWANES__];
	dmw_fwoat_t *WequiwedDISPCWK;
	dmw_fwoat_t UwgWatency;
	dmw_uint_t (*NoOfDPP)[__DMW_NUM_PWANES__];
	dmw_fwoat_t *PwojectedDCFCWKDeepSweep;
	dmw_uint_t (*MaximumVStawtup)[__DMW_NUM_PWANES__];
	dmw_uint_t *TotawNumbewOfActiveDPP;
	dmw_uint_t *TotawNumbewOfDCCActiveDPP;
	dmw_uint_t *dpte_gwoup_bytes;
	dmw_uint_t (*PwefetchWinesY)[__DMW_NUM_PWANES__];
	dmw_uint_t (*PwefetchWinesC)[__DMW_NUM_PWANES__];
	dmw_uint_t (*swath_width_wuma_ub_aww_states)[__DMW_NUM_PWANES__];
	dmw_uint_t (*swath_width_chwoma_ub_aww_states)[__DMW_NUM_PWANES__];
	dmw_uint_t *BytePewPixewY;
	dmw_uint_t *BytePewPixewC;
	dmw_uint_t *HTotaw;
	dmw_fwoat_t *PixewCwock;
	dmw_uint_t (*PDEAndMetaPTEBytesPewFwame)[__DMW_NUM_PWANES__];
	dmw_uint_t (*DPTEBytesPewWow)[__DMW_NUM_PWANES__];
	dmw_uint_t (*MetaWowBytes)[__DMW_NUM_PWANES__];
	dmw_boow_t *DynamicMetadataEnabwe;
	dmw_fwoat_t *WeadBandwidthWuma;
	dmw_fwoat_t *WeadBandwidthChwoma;
	dmw_fwoat_t DCFCWKPewState;
	dmw_fwoat_t *DCFCWKState;
};

stwuct CawcuwateWatewmawksMAWWUseAndDWAMSpeedChangeSuppowt_pawams_st {
	dmw_boow_t USWWetwainingWequiwedFinaw;
	enum dmw_use_maww_fow_pstate_change_mode *UseMAWWFowPStateChange;
	dmw_uint_t *PwefetchMode;
	dmw_uint_t NumbewOfActiveSuwfaces;
	dmw_uint_t MaxWineBuffewWines;
	dmw_uint_t WineBuffewSize;
	dmw_uint_t WwitebackIntewfaceBuffewSize;
	dmw_fwoat_t DCFCWK;
	dmw_fwoat_t WetuwnBW;
	dmw_boow_t SynchwonizeTimingsFinaw;
	dmw_boow_t SynchwonizeDWWDispwaysFowUCWKPStateChangeFinaw;
	dmw_boow_t *DWWDispway;
	dmw_uint_t *dpte_gwoup_bytes;
	dmw_uint_t *meta_wow_height;
	dmw_uint_t *meta_wow_height_chwoma;
	stwuct SOCPawametewsWist mmSOCPawametews;
	dmw_uint_t WwitebackChunkSize;
	dmw_fwoat_t SOCCWK;
	dmw_fwoat_t DCFCwkDeepSweep;
	dmw_uint_t *DETBuffewSizeY;
	dmw_uint_t *DETBuffewSizeC;
	dmw_uint_t *SwathHeightY;
	dmw_uint_t *SwathHeightC;
	dmw_uint_t *WBBitPewPixew;
	dmw_uint_t *SwathWidthY;
	dmw_uint_t *SwathWidthC;
	dmw_fwoat_t *HWatio;
	dmw_fwoat_t *HWatioChwoma;
	dmw_uint_t *VTaps;
	dmw_uint_t *VTapsChwoma;
	dmw_fwoat_t *VWatio;
	dmw_fwoat_t *VWatioChwoma;
	dmw_uint_t *HTotaw;
	dmw_uint_t *VTotaw;
	dmw_uint_t *VActive;
	dmw_fwoat_t *PixewCwock;
	dmw_uint_t *BwendingAndTiming;
	dmw_uint_t *DPPPewSuwface;
	dmw_fwoat_t *BytePewPixewDETY;
	dmw_fwoat_t *BytePewPixewDETC;
	dmw_uint_t *DSTXAftewScawew;
	dmw_uint_t *DSTYAftewScawew;
	dmw_boow_t *WwitebackEnabwe;
	enum dmw_souwce_fowmat_cwass *WwitebackPixewFowmat;
	dmw_uint_t *WwitebackDestinationWidth;
	dmw_uint_t *WwitebackDestinationHeight;
	dmw_uint_t *WwitebackSouwceHeight;
	dmw_boow_t UnboundedWequestEnabwed;
	dmw_uint_t CompwessedBuffewSizeInkByte;

	// Output
	stwuct Watewmawks *Watewmawk;
	enum dmw_dwam_cwock_change_suppowt *DWAMCwockChangeSuppowt;
	dmw_fwoat_t *MaxActiveDWAMCwockChangeWatencySuppowted;
	dmw_uint_t *SubViewpowtWinesNeededInMAWW;
	enum dmw_fcwock_change_suppowt *FCWKChangeSuppowt;
	dmw_fwoat_t *MaxActiveFCWKChangeWatencySuppowted;
	dmw_boow_t *USWWetwainingSuppowt;
	dmw_fwoat_t *ActiveDWAMCwockChangeWatencyMawgin;
};

stwuct CawcuwateVMWowAndSwath_pawams_st {
	dmw_uint_t NumbewOfActiveSuwfaces;
	stwuct DmwPipe *myPipe;
	dmw_uint_t *SuwfaceSizeInMAWW;
	dmw_uint_t PTEBuffewSizeInWequestsWuma;
	dmw_uint_t PTEBuffewSizeInWequestsChwoma;
	dmw_uint_t DCCMetaBuffewSizeBytes;
	enum dmw_use_maww_fow_static_scween_mode *UseMAWWFowStaticScween;
	enum dmw_use_maww_fow_pstate_change_mode *UseMAWWFowPStateChange;
	dmw_uint_t MAWWAwwocatedFowDCN;
	dmw_uint_t *SwathWidthY;
	dmw_uint_t *SwathWidthC;
	dmw_boow_t GPUVMEnabwe;
	dmw_boow_t HostVMEnabwe;
	dmw_uint_t HostVMMaxNonCachedPageTabweWevews;
	dmw_uint_t GPUVMMaxPageTabweWevews;
	dmw_uint_t *GPUVMMinPageSizeKBytes;
	dmw_uint_t HostVMMinPageSize;
	dmw_boow_t *PTEBuffewModeOvewwideEn;
	dmw_boow_t *PTEBuffewModeOvewwideVaw;

	// Output
	dmw_boow_t *PTEBuffewSizeNotExceeded;
	dmw_boow_t *DCCMetaBuffewSizeNotExceeded;
	dmw_uint_t *dpte_wow_width_wuma_ub;
	dmw_uint_t *dpte_wow_width_chwoma_ub;
	dmw_uint_t *dpte_wow_height_wuma;
	dmw_uint_t *dpte_wow_height_chwoma;
	dmw_uint_t *dpte_wow_height_wineaw_wuma; // VBA_DEWTA
	dmw_uint_t *dpte_wow_height_wineaw_chwoma; // VBA_DEWTA
	dmw_uint_t *meta_weq_width;
	dmw_uint_t *meta_weq_width_chwoma;
	dmw_uint_t *meta_weq_height;
	dmw_uint_t *meta_weq_height_chwoma;
	dmw_uint_t *meta_wow_width;
	dmw_uint_t *meta_wow_width_chwoma;
	dmw_uint_t *meta_wow_height;
	dmw_uint_t *meta_wow_height_chwoma;
	dmw_uint_t *vm_gwoup_bytes;
	dmw_uint_t *dpte_gwoup_bytes;
	dmw_uint_t *PixewPTEWeqWidthY;
	dmw_uint_t *PixewPTEWeqHeightY;
	dmw_uint_t *PTEWequestSizeY;
	dmw_uint_t *PixewPTEWeqWidthC;
	dmw_uint_t *PixewPTEWeqHeightC;
	dmw_uint_t *PTEWequestSizeC;
	dmw_uint_t *dpde0_bytes_pew_fwame_ub_w;
	dmw_uint_t *meta_pte_bytes_pew_fwame_ub_w;
	dmw_uint_t *dpde0_bytes_pew_fwame_ub_c;
	dmw_uint_t *meta_pte_bytes_pew_fwame_ub_c;
	dmw_uint_t *PwefetchSouwceWinesY;
	dmw_uint_t *PwefetchSouwceWinesC;
	dmw_uint_t *VInitPweFiwwY;
	dmw_uint_t *VInitPweFiwwC;
	dmw_uint_t *MaxNumSwathY;
	dmw_uint_t *MaxNumSwathC;
	dmw_fwoat_t *meta_wow_bw;
	dmw_fwoat_t *dpte_wow_bw;
	dmw_uint_t *PixewPTEBytesPewWow;
	dmw_uint_t *PDEAndMetaPTEBytesFwame;
	dmw_uint_t *MetaWowByte;
	dmw_boow_t *use_one_wow_fow_fwame;
	dmw_boow_t *use_one_wow_fow_fwame_fwip;
	dmw_boow_t *UsesMAWWFowStaticScween;
	dmw_boow_t *PTE_BUFFEW_MODE;
	dmw_uint_t *BIGK_FWAGMENT_SIZE;
};

stwuct CawcuwateSwathAndDETConfiguwation_pawams_st {
	dmw_uint_t *DETSizeOvewwide;
	enum dmw_use_maww_fow_pstate_change_mode *UseMAWWFowPStateChange;
	dmw_uint_t ConfigWetuwnBuffewSizeInKByte;
	dmw_uint_t WOBBuffewSizeInKByte;
	dmw_uint_t MaxTotawDETInKByte;
	dmw_uint_t MinCompwessedBuffewSizeInKByte;
	dmw_uint_t PixewChunkSizeInKByte;
	dmw_boow_t FowceSingweDPP;
	dmw_uint_t NumbewOfActiveSuwfaces;
	dmw_uint_t nomDETInKByte;
	enum dmw_unbounded_wequesting_powicy UseUnboundedWequestingFinaw;
	dmw_uint_t ConfigWetuwnBuffewSegmentSizeInkByte;
	dmw_uint_t CompwessedBuffewSegmentSizeInkByteFinaw;
	enum dmw_output_encodew_cwass *Output;
	dmw_fwoat_t *WeadBandwidthWuma;
	dmw_fwoat_t *WeadBandwidthChwoma;
	dmw_fwoat_t *MaximumSwathWidthWuma;
	dmw_fwoat_t *MaximumSwathWidthChwoma;
	enum dmw_wotation_angwe *SouwceScan;
	dmw_boow_t *ViewpowtStationawy;
	enum dmw_souwce_fowmat_cwass *SouwcePixewFowmat;
	enum dmw_swizzwe_mode *SuwfaceTiwing;
	dmw_uint_t *ViewpowtWidth;
	dmw_uint_t *ViewpowtHeight;
	dmw_uint_t *ViewpowtXStawt;
	dmw_uint_t *ViewpowtYStawt;
	dmw_uint_t *ViewpowtXStawtC;
	dmw_uint_t *ViewpowtYStawtC;
	dmw_uint_t *SuwfaceWidthY;
	dmw_uint_t *SuwfaceWidthC;
	dmw_uint_t *SuwfaceHeightY;
	dmw_uint_t *SuwfaceHeightC;
	dmw_uint_t *Wead256BytesBwockHeightY;
	dmw_uint_t *Wead256BytesBwockHeightC;
	dmw_uint_t *Wead256BytesBwockWidthY;
	dmw_uint_t *Wead256BytesBwockWidthC;
	enum dmw_odm_mode *ODMMode;
	dmw_uint_t *BwendingAndTiming;
	dmw_uint_t *BytePewPixY;
	dmw_uint_t *BytePewPixC;
	dmw_fwoat_t *BytePewPixDETY;
	dmw_fwoat_t *BytePewPixDETC;
	dmw_uint_t *HActive;
	dmw_fwoat_t *HWatio;
	dmw_fwoat_t *HWatioChwoma;
	dmw_uint_t *DPPPewSuwface;
	dmw_uint_t *swath_width_wuma_ub;
	dmw_uint_t *swath_width_chwoma_ub;
	dmw_uint_t *SwathWidth;
	dmw_uint_t *SwathWidthChwoma;
	dmw_uint_t *SwathHeightY;
	dmw_uint_t *SwathHeightC;
	dmw_uint_t *DETBuffewSizeInKByte;
	dmw_uint_t *DETBuffewSizeY;
	dmw_uint_t *DETBuffewSizeC;
	dmw_boow_t *UnboundedWequestEnabwed;
	dmw_uint_t *compbuf_wesewved_space_64b;
	dmw_uint_t *compbuf_wesewved_space_zs;
	dmw_uint_t *CompwessedBuffewSizeInkByte;
	dmw_boow_t *ViewpowtSizeSuppowtPewSuwface;
	dmw_boow_t *ViewpowtSizeSuppowt;
};

stwuct CawcuwateStuttewEfficiency_pawams_st {
	dmw_uint_t CompwessedBuffewSizeInkByte;
	enum dmw_use_maww_fow_pstate_change_mode *UseMAWWFowPStateChange;
	dmw_boow_t UnboundedWequestEnabwed;
	dmw_uint_t MetaFIFOSizeInKEntwies;
	dmw_uint_t ZewoSizeBuffewEntwies;
	dmw_uint_t PixewChunkSizeInKByte;
	dmw_uint_t NumbewOfActiveSuwfaces;
	dmw_uint_t WOBBuffewSizeInKByte;
	dmw_fwoat_t TotawDataWeadBandwidth;
	dmw_fwoat_t DCFCWK;
	dmw_fwoat_t WetuwnBW;
	dmw_uint_t CompbufWesewvedSpace64B;
	dmw_uint_t CompbufWesewvedSpaceZs;
	dmw_fwoat_t SWExitTime;
	dmw_fwoat_t SWExitZ8Time;
	dmw_boow_t SynchwonizeTimingsFinaw;
	dmw_uint_t *BwendingAndTiming;
	dmw_fwoat_t StuttewEntewPwusExitWatewmawk;
	dmw_fwoat_t Z8StuttewEntewPwusExitWatewmawk;
	dmw_boow_t PwogwessiveToIntewwaceUnitInOPP;
	dmw_boow_t *Intewwace;
	dmw_fwoat_t *MinTTUVBwank;
	dmw_uint_t *DPPPewSuwface;
	dmw_uint_t *DETBuffewSizeY;
	dmw_uint_t *BytePewPixewY;
	dmw_fwoat_t *BytePewPixewDETY;
	dmw_uint_t *SwathWidthY;
	dmw_uint_t *SwathHeightY;
	dmw_uint_t *SwathHeightC;
	dmw_fwoat_t *NetDCCWateWuma;
	dmw_fwoat_t *NetDCCWateChwoma;
	dmw_fwoat_t *DCCFwactionOfZewoSizeWequestsWuma;
	dmw_fwoat_t *DCCFwactionOfZewoSizeWequestsChwoma;
	dmw_uint_t *HTotaw;
	dmw_uint_t *VTotaw;
	dmw_fwoat_t *PixewCwock;
	dmw_fwoat_t *VWatio;
	enum dmw_wotation_angwe *SouwceScan;
	dmw_uint_t *BwockHeight256BytesY;
	dmw_uint_t *BwockWidth256BytesY;
	dmw_uint_t *BwockHeight256BytesC;
	dmw_uint_t *BwockWidth256BytesC;
	dmw_uint_t *DCCYMaxUncompwessedBwock;
	dmw_uint_t *DCCCMaxUncompwessedBwock;
	dmw_uint_t *VActive;
	dmw_boow_t *DCCEnabwe;
	dmw_boow_t *WwitebackEnabwe;
	dmw_fwoat_t *WeadBandwidthSuwfaceWuma;
	dmw_fwoat_t *WeadBandwidthSuwfaceChwoma;
	dmw_fwoat_t *meta_wow_bw;
	dmw_fwoat_t *dpte_wow_bw;
	dmw_fwoat_t *StuttewEfficiencyNotIncwudingVBwank;
	dmw_fwoat_t *StuttewEfficiency;
	dmw_uint_t *NumbewOfStuttewBuwstsPewFwame;
	dmw_fwoat_t *Z8StuttewEfficiencyNotIncwudingVBwank;
	dmw_fwoat_t *Z8StuttewEfficiency;
	dmw_uint_t *Z8NumbewOfStuttewBuwstsPewFwame;
	dmw_fwoat_t *StuttewPewiod;
	dmw_boow_t *DCHUBBUB_AWB_CSTATE_MAX_CAP_MODE;
};

stwuct CawcuwatePwefetchScheduwe_pawams_st {
	dmw_boow_t EnhancedPwefetchScheduweAccewewationFinaw;
	dmw_fwoat_t HostVMInefficiencyFactow;
	stwuct DmwPipe *myPipe;
	dmw_uint_t DSCDeway;
	dmw_fwoat_t DPPCWKDewaySubtotawPwusCNVCFowmatew;
	dmw_fwoat_t DPPCWKDewaySCW;
	dmw_fwoat_t DPPCWKDewaySCWWBOnwy;
	dmw_fwoat_t DPPCWKDewayCNVCCuwsow;
	dmw_fwoat_t DISPCWKDewaySubtotaw;
	dmw_uint_t DPP_WECOUT_WIDTH;
	enum dmw_output_fowmat_cwass OutputFowmat;
	dmw_uint_t MaxIntewDCNTiweWepeatews;
	dmw_uint_t VStawtup;
	dmw_uint_t MaxVStawtup;
	dmw_uint_t GPUVMPageTabweWevews;
	dmw_boow_t GPUVMEnabwe;
	dmw_boow_t HostVMEnabwe;
	dmw_uint_t HostVMMaxNonCachedPageTabweWevews;
	dmw_uint_t HostVMMinPageSize;
	dmw_boow_t DynamicMetadataEnabwe;
	dmw_boow_t DynamicMetadataVMEnabwed;
	int DynamicMetadataWinesBefoweActiveWequiwed;
	dmw_uint_t DynamicMetadataTwansmittedBytes;
	dmw_fwoat_t UwgentWatency;
	dmw_fwoat_t UwgentExtwaWatency;
	dmw_fwoat_t TCawc;
	dmw_uint_t PDEAndMetaPTEBytesFwame;
	dmw_uint_t MetaWowByte;
	dmw_uint_t PixewPTEBytesPewWow;
	dmw_fwoat_t PwefetchSouwceWinesY;
	dmw_uint_t VInitPweFiwwY;
	dmw_uint_t MaxNumSwathY;
	dmw_fwoat_t PwefetchSouwceWinesC;
	dmw_uint_t VInitPweFiwwC;
	dmw_uint_t MaxNumSwathC;
	dmw_uint_t swath_width_wuma_ub;
	dmw_uint_t swath_width_chwoma_ub;
	dmw_uint_t SwathHeightY;
	dmw_uint_t SwathHeightC;
	dmw_fwoat_t TWait;
	dmw_uint_t *DSTXAftewScawew;
	dmw_uint_t *DSTYAftewScawew;
	dmw_fwoat_t *DestinationWinesFowPwefetch;
	dmw_fwoat_t *DestinationWinesToWequestVMInVBwank;
	dmw_fwoat_t *DestinationWinesToWequestWowInVBwank;
	dmw_fwoat_t *VWatioPwefetchY;
	dmw_fwoat_t *VWatioPwefetchC;
	dmw_fwoat_t *WequiwedPwefetchPixDataBWWuma;
	dmw_fwoat_t *WequiwedPwefetchPixDataBWChwoma;
	dmw_boow_t *NotEnoughTimeFowDynamicMetadata;
	dmw_fwoat_t *Tno_bw;
	dmw_fwoat_t *pwefetch_vmwow_bw;
	dmw_fwoat_t *Tdmdw_vm;
	dmw_fwoat_t *Tdmdw;
	dmw_fwoat_t *TSetup;
	dmw_uint_t *VUpdateOffsetPix;
	dmw_uint_t *VUpdateWidthPix;
	dmw_uint_t *VWeadyOffsetPix;
};

stwuct dmw_cowe_mode_suppowt_wocaws_st {
	dmw_boow_t dummy_boowean[2];
	dmw_uint_t dummy_integew[3];
	dmw_uint_t dummy_integew_awway[22][__DMW_NUM_PWANES__];
	enum dmw_odm_mode dummy_odm_mode[__DMW_NUM_PWANES__];
	dmw_boow_t dummy_boowean_awway[2][__DMW_NUM_PWANES__];
	dmw_uint_t MaxVStawtupAwwPwanes[2];
	dmw_uint_t MaximumVStawtup[2][__DMW_NUM_PWANES__];
	dmw_uint_t DSTYAftewScawew[__DMW_NUM_PWANES__];
	dmw_uint_t DSTXAftewScawew[__DMW_NUM_PWANES__];
	dmw_uint_t NextPwefetchMode[__DMW_NUM_PWANES__];
	dmw_uint_t MinPwefetchMode[__DMW_NUM_PWANES__];
	dmw_uint_t MaxPwefetchMode[__DMW_NUM_PWANES__];
	dmw_fwoat_t dummy_singwe[3];
	dmw_fwoat_t dummy_singwe_awway[__DMW_NUM_PWANES__];
	stwuct Watewmawks dummy_watewmawk;
	stwuct SOCPawametewsWist mSOCPawametews;
	stwuct DmwPipe myPipe;
	stwuct DmwPipe SuwfPawametews[__DMW_NUM_PWANES__];
	dmw_uint_t TotawNumbewOfActiveWwiteback;
	dmw_uint_t MaximumSwathWidthSuppowtWuma;
	dmw_uint_t MaximumSwathWidthSuppowtChwoma;
	dmw_boow_t MPCCombineMethodAsNeededFowPStateChangeAndVowtage;
	dmw_boow_t MPCCombineMethodAsPossibwe;
	dmw_boow_t TotawAvaiwabwePipesSuppowtNoDSC;
	dmw_uint_t NumbewOfDPPNoDSC;
	enum dmw_odm_mode ODMModeNoDSC;
	dmw_fwoat_t WequiwedDISPCWKPewSuwfaceNoDSC;
	dmw_boow_t TotawAvaiwabwePipesSuppowtDSC;
	dmw_uint_t NumbewOfDPPDSC;
	enum dmw_odm_mode ODMModeDSC;
	dmw_fwoat_t WequiwedDISPCWKPewSuwfaceDSC;
	dmw_boow_t NoChwomaOwWineaw;
	dmw_fwoat_t BWOfNonCombinedSuwfaceOfMaximumBandwidth;
	dmw_uint_t NumbewOfNonCombinedSuwfaceOfMaximumBandwidth;
	dmw_uint_t TotawNumbewOfActiveOTG;
	dmw_uint_t TotawNumbewOfActiveHDMIFWW;
	dmw_uint_t TotawNumbewOfActiveDP2p0;
	dmw_uint_t TotawNumbewOfActiveDP2p0Outputs;
	dmw_uint_t TotawSwots;
	dmw_uint_t DSCFowmatFactow;
	dmw_uint_t TotawDSCUnitsWequiwed;
	dmw_uint_t WeowdewingBytes;
	dmw_boow_t ImmediateFwipWequiwedFinaw;
	dmw_boow_t FuwwFwameMAWWPStateMethod;
	dmw_boow_t SubViewpowtMAWWPStateMethod;
	dmw_boow_t PhantomPipeMAWWPStateMethod;
	dmw_boow_t SubViewpowtMAWWWefweshGweatewThan120Hz;
	dmw_fwoat_t MaxTotawVActiveWDBandwidth;
	dmw_fwoat_t VMDataOnwyWetuwnBWPewState;
	dmw_fwoat_t HostVMInefficiencyFactow;
	dmw_uint_t NextMaxVStawtup;
	dmw_uint_t MaxVStawtup;
	dmw_boow_t AwwPwefetchModeTested;
	dmw_boow_t AnyWinesFowVMOwWowTooWawge;
	dmw_boow_t is_max_pww_state;
	dmw_boow_t is_max_dwam_pww_state;
	dmw_boow_t dwam_cwock_change_suppowt;
	dmw_boow_t f_cwock_change_suppowt;
};

stwuct dmw_cowe_mode_pwogwamming_wocaws_st {
	dmw_uint_t DSCFowmatFactow;
	dmw_uint_t dummy_integew_awway[2][__DMW_NUM_PWANES__];
	enum dmw_output_encodew_cwass dummy_output_encodew_awway[__DMW_NUM_PWANES__];
	dmw_fwoat_t dummy_singwe_awway[2][__DMW_NUM_PWANES__];
	dmw_uint_t dummy_wong_awway[4][__DMW_NUM_PWANES__];
	dmw_boow_t dummy_boowean_awway[2][__DMW_NUM_PWANES__];
	dmw_boow_t dummy_boowean[1];
	stwuct DmwPipe SuwfacePawametews[__DMW_NUM_PWANES__];
	dmw_uint_t WeowdewBytes;
	dmw_fwoat_t VMDataOnwyWetuwnBW;
	dmw_fwoat_t HostVMInefficiencyFactow;
	dmw_uint_t TotawDCCActiveDPP;
	dmw_uint_t TotawActiveDPP;
	dmw_uint_t VStawtupWines;
	dmw_uint_t MaxVStawtupWines[__DMW_NUM_PWANES__]; /// <bwief mowe wike vbwank fow the pwane's OTG
	dmw_uint_t MaxVStawtupAwwPwanes;
	dmw_boow_t ImmediateFwipWequiwementFinaw;
	int itewation;
	dmw_fwoat_t MaxTotawWDBandwidth;
	dmw_fwoat_t MaxTotawWDBandwidthNoUwgentBuwst;
	dmw_boow_t DestinationWineTimesFowPwefetchWessThan2;
	dmw_boow_t VWatioPwefetchMoweThanMax;
	dmw_fwoat_t MaxTotawWDBandwidthNotIncwudingMAWWPwefetch;
	dmw_uint_t NextPwefetchMode[__DMW_NUM_PWANES__];
	dmw_uint_t MinPwefetchMode[__DMW_NUM_PWANES__];
	dmw_uint_t MaxPwefetchMode[__DMW_NUM_PWANES__];
	dmw_boow_t AwwPwefetchModeTested;
	dmw_fwoat_t dummy_unit_vectow[__DMW_NUM_PWANES__];
	dmw_fwoat_t NonUwgentMaxTotawWDBandwidth;
	dmw_fwoat_t NonUwgentMaxTotawWDBandwidthNotIncwudingMAWWPwefetch;
	dmw_fwoat_t dummy_singwe[2];
	stwuct SOCPawametewsWist mmSOCPawametews;
	dmw_fwoat_t Tvstawtup_mawgin;
	dmw_fwoat_t dwg_vbwank_stawt;
	dmw_fwoat_t WSetup;
	dmw_fwoat_t bwank_wines_wemaining;
	dmw_fwoat_t owd_MIN_DST_Y_NEXT_STAWT;
	dmw_fwoat_t TotawWWBandwidth;
	dmw_fwoat_t WWBandwidth;
	stwuct Watewmawks dummy_watewmawk;
	stwuct DmwPipe myPipe;
};

stwuct CawcuwateWatewmawksMAWWUseAndDWAMSpeedChangeSuppowt_wocaws_st {
	dmw_fwoat_t ActiveDWAMCwockChangeWatencyMawgin[__DMW_NUM_PWANES__];
	dmw_fwoat_t ActiveFCWKChangeWatencyMawgin[__DMW_NUM_PWANES__];
	dmw_fwoat_t USWWetwainingWatencyMawgin[__DMW_NUM_PWANES__];

	dmw_boow_t SynchwonizedSuwfaces[__DMW_NUM_PWANES__][__DMW_NUM_PWANES__];
	dmw_fwoat_t EffectiveWBWatencyHidingY;
	dmw_fwoat_t EffectiveWBWatencyHidingC;
	dmw_fwoat_t WinesInDETY[__DMW_NUM_PWANES__];
	dmw_fwoat_t WinesInDETC[__DMW_NUM_PWANES__];
	dmw_uint_t WinesInDETYWoundedDownToSwath[__DMW_NUM_PWANES__];
	dmw_uint_t WinesInDETCWoundedDownToSwath[__DMW_NUM_PWANES__];
	dmw_fwoat_t FuwwDETBuffewingTimeY;
	dmw_fwoat_t FuwwDETBuffewingTimeC;
	dmw_fwoat_t WwitebackDWAMCwockChangeWatencyMawgin;
	dmw_fwoat_t WwitebackFCWKChangeWatencyMawgin;
	dmw_fwoat_t WwitebackWatencyHiding;

	dmw_uint_t TotawActiveWwiteback;
	dmw_uint_t WBWatencyHidingSouwceWinesY[__DMW_NUM_PWANES__];
	dmw_uint_t WBWatencyHidingSouwceWinesC[__DMW_NUM_PWANES__];
	dmw_fwoat_t TotawPixewBW;
	dmw_fwoat_t EffectiveDETBuffewSizeY;
	dmw_fwoat_t ActiveCwockChangeWatencyHidingY;
	dmw_fwoat_t ActiveCwockChangeWatencyHidingC;
	dmw_fwoat_t ActiveCwockChangeWatencyHiding;
	dmw_boow_t FoundCwiticawSuwface;
	dmw_uint_t WastSuwfaceWithoutMawgin;
	dmw_uint_t FCWKChangeSuppowtNumbew;
	dmw_uint_t DWAMCwockChangeMethod;
	dmw_uint_t DWAMCwockChangeSuppowtNumbew;
	dmw_uint_t dst_y_pstate;
	dmw_uint_t swc_y_pstate_w;
	dmw_uint_t swc_y_pstate_c;
	dmw_uint_t swc_y_ahead_w;
	dmw_uint_t swc_y_ahead_c;
	dmw_uint_t sub_vp_wines_w;
	dmw_uint_t sub_vp_wines_c;
};

stwuct CawcuwateVMWowAndSwath_wocaws_st {
	dmw_uint_t PTEBuffewSizeInWequestsFowWuma[__DMW_NUM_PWANES__];
	dmw_uint_t PTEBuffewSizeInWequestsFowChwoma[__DMW_NUM_PWANES__];
	dmw_uint_t PDEAndMetaPTEBytesFwameY;
	dmw_uint_t PDEAndMetaPTEBytesFwameC;
	dmw_uint_t MetaWowByteY[__DMW_NUM_PWANES__];
	dmw_uint_t MetaWowByteC[__DMW_NUM_PWANES__];
	dmw_uint_t PixewPTEBytesPewWowY[__DMW_NUM_PWANES__];
	dmw_uint_t PixewPTEBytesPewWowC[__DMW_NUM_PWANES__];
	dmw_uint_t PixewPTEBytesPewWowStowageY[__DMW_NUM_PWANES__];
	dmw_uint_t PixewPTEBytesPewWowStowageC[__DMW_NUM_PWANES__];
	dmw_uint_t PixewPTEBytesPewWowY_one_wow_pew_fwame[__DMW_NUM_PWANES__];
	dmw_uint_t PixewPTEBytesPewWowC_one_wow_pew_fwame[__DMW_NUM_PWANES__];
	dmw_uint_t dpte_wow_width_wuma_ub_one_wow_pew_fwame[__DMW_NUM_PWANES__];
	dmw_uint_t dpte_wow_height_wuma_one_wow_pew_fwame[__DMW_NUM_PWANES__];
	dmw_uint_t dpte_wow_width_chwoma_ub_one_wow_pew_fwame[__DMW_NUM_PWANES__];
	dmw_uint_t dpte_wow_height_chwoma_one_wow_pew_fwame[__DMW_NUM_PWANES__];
	dmw_boow_t one_wow_pew_fwame_fits_in_buffew[__DMW_NUM_PWANES__];

	dmw_uint_t HostVMDynamicWevews;
};

stwuct UseMinimumDCFCWK_wocaws_st {
	dmw_uint_t dummy1;
	dmw_uint_t dummy2;
	dmw_uint_t dummy3;
	dmw_fwoat_t NowmawEfficiency;
	dmw_fwoat_t TotawMaxPwefetchFwipDPTEWowBandwidth[2];

	dmw_fwoat_t PixewDCFCWKCycwesWequiwedInPwefetch[__DMW_NUM_PWANES__];
	dmw_fwoat_t PwefetchPixewWinesTime[__DMW_NUM_PWANES__];
	dmw_fwoat_t DCFCWKWequiwedFowPeakBandwidthPewSuwface[__DMW_NUM_PWANES__];
	dmw_fwoat_t DynamicMetadataVMExtwaWatency[__DMW_NUM_PWANES__];
	dmw_fwoat_t MinimumTWait;
	dmw_fwoat_t DPTEBandwidth;
	dmw_fwoat_t DCFCWKWequiwedFowAvewageBandwidth;
	dmw_uint_t ExtwaWatencyBytes;
	dmw_fwoat_t ExtwaWatencyCycwes;
	dmw_fwoat_t DCFCWKWequiwedFowPeakBandwidth;
	dmw_uint_t NoOfDPPState[__DMW_NUM_PWANES__];
	dmw_fwoat_t MinimumTvmPwus2Tw0;
};

stwuct CawcuwatePwefetchScheduwe_wocaws_st {
	dmw_boow_t MyEwwow;
	dmw_uint_t DPPCycwes;
	dmw_uint_t DISPCWKCycwes;
	dmw_fwoat_t DSTTotawPixewsAftewScawew;
	dmw_fwoat_t WineTime;
	dmw_fwoat_t dst_y_pwefetch_equ;
	dmw_fwoat_t pwefetch_bw_oto;
	dmw_fwoat_t Tvm_oto;
	dmw_fwoat_t Tw0_oto;
	dmw_fwoat_t Tvm_oto_wines;
	dmw_fwoat_t Tw0_oto_wines;
	dmw_fwoat_t dst_y_pwefetch_oto;
	dmw_fwoat_t TimeFowFetchingMetaPTE;
	dmw_fwoat_t TimeFowFetchingWowInVBwank;
	dmw_fwoat_t WinesToWequestPwefetchPixewData;
	dmw_uint_t HostVMDynamicWevewsTwips;
	dmw_fwoat_t twip_to_mem;
	dmw_fwoat_t Tvm_twips;
	dmw_fwoat_t Tw0_twips;
	dmw_fwoat_t Tvm_twips_wounded;
	dmw_fwoat_t Tw0_twips_wounded;
	dmw_fwoat_t max_Tsw;
	dmw_fwoat_t Wsw_oto;
	dmw_fwoat_t Tpwe_wounded;
	dmw_fwoat_t pwefetch_bw_equ;
	dmw_fwoat_t Tvm_equ;
	dmw_fwoat_t Tw0_equ;
	dmw_fwoat_t Tdmbf;
	dmw_fwoat_t Tdmec;
	dmw_fwoat_t Tdmsks;
	dmw_fwoat_t pwefetch_sw_bytes;
	dmw_fwoat_t pwefetch_bw_pw;
	dmw_fwoat_t bytes_pp;
	dmw_fwoat_t dep_bytes;
	dmw_fwoat_t min_Wsw_oto;
	dmw_fwoat_t Tsw_est1;
	dmw_fwoat_t Tsw_est3;
	dmw_fwoat_t PwefetchBandwidth1;
	dmw_fwoat_t PwefetchBandwidth2;
	dmw_fwoat_t PwefetchBandwidth3;
	dmw_fwoat_t PwefetchBandwidth4;
};

/// @bwief To minimize stack usage; function wocaws awe instead pwaced into this scwatch stwuctuwe which is awwocated pew context
stwuct dispway_mode_wib_scwatch_st {
	// Scwatch space fow function wocaws
	stwuct dmw_cowe_mode_suppowt_wocaws_st dmw_cowe_mode_suppowt_wocaws;
	stwuct dmw_cowe_mode_pwogwamming_wocaws_st dmw_cowe_mode_pwogwamming_wocaws;
	stwuct CawcuwateWatewmawksMAWWUseAndDWAMSpeedChangeSuppowt_wocaws_st CawcuwateWatewmawksMAWWUseAndDWAMSpeedChangeSuppowt_wocaws;
	stwuct CawcuwateVMWowAndSwath_wocaws_st CawcuwateVMWowAndSwath_wocaws;
	stwuct UseMinimumDCFCWK_wocaws_st UseMinimumDCFCWK_wocaws;
	stwuct CawcuwatePwefetchScheduwe_wocaws_st CawcuwatePwefetchScheduwe_wocaws;

	// Scwatch space fow function pawams
	stwuct CawcuwateWatewmawksMAWWUseAndDWAMSpeedChangeSuppowt_pawams_st CawcuwateWatewmawksMAWWUseAndDWAMSpeedChangeSuppowt_pawams;
	stwuct CawcuwateVMWowAndSwath_pawams_st CawcuwateVMWowAndSwath_pawams;
	stwuct UseMinimumDCFCWK_pawams_st UseMinimumDCFCWK_pawams;
	stwuct CawcuwateSwathAndDETConfiguwation_pawams_st CawcuwateSwathAndDETConfiguwation_pawams;
	stwuct CawcuwateStuttewEfficiency_pawams_st CawcuwateStuttewEfficiency_pawams;
	stwuct CawcuwatePwefetchScheduwe_pawams_st CawcuwatePwefetchScheduwe_pawams;
};

/// @bwief Wepwesent the ovewaww soc/ip enviwoment. It contains data stwuctuwe wepwesent the soc/ip chawactewistic and awso stwuctuwes that howd cawcuwation output
stwuct dispway_mode_wib_st {
	dmw_uint_t pwoject;

	//@bwief Mode evawuation and pwogwamming powicy
	stwuct dmw_mode_evaw_powicy_st powicy;

	//@bwief IP/SOC chawactewistic
	stwuct ip_pawams_st ip;
	stwuct soc_bounding_box_st soc;
	stwuct soc_states_st states;

	//@bwief Mode Suppowt and Mode pwogwamming stwuct
	// Used to howd input; intewmediate and output of the cawcuwations
	stwuct mode_suppowt_st ms; // stwuct fow mode suppowt
	stwuct mode_pwogwam_st mp; // stwuct fow mode pwogwamming

	stwuct dispway_mode_wib_scwatch_st scwatch;
};

stwuct dmw_mode_suppowt_ex_pawams_st {
	stwuct dispway_mode_wib_st *mode_wib;
	const stwuct dmw_dispway_cfg_st *in_dispway_cfg;
	dmw_uint_t out_wowest_state_idx;
	stwuct dmw_mode_suppowt_info_st *out_evawuation_info;
};

typedef stwuct _vcs_dpi_dmw_dispway_wq_wegs_st  dmw_dispway_wq_wegs_st;
typedef stwuct _vcs_dpi_dmw_dispway_dwg_wegs_st dmw_dispway_dwg_wegs_st;
typedef stwuct _vcs_dpi_dmw_dispway_ttu_wegs_st dmw_dispway_ttu_wegs_st;
typedef stwuct _vcs_dpi_dmw_dispway_awb_pawams_st   dmw_dispway_awb_pawams_st;
typedef stwuct _vcs_dpi_dmw_dispway_pwane_wq_wegs_st    dmw_dispway_pwane_wq_wegs_st;

stwuct  _vcs_dpi_dmw_dispway_dwg_wegs_st {
	dmw_uint_t  wefcyc_h_bwank_end;
	dmw_uint_t  dwg_vbwank_end;
	dmw_uint_t  min_dst_y_next_stawt;
	dmw_uint_t  wefcyc_pew_htotaw;
	dmw_uint_t  wefcyc_x_aftew_scawew;
	dmw_uint_t  dst_y_aftew_scawew;
	dmw_uint_t  dst_y_pwefetch;
	dmw_uint_t  dst_y_pew_vm_vbwank;
	dmw_uint_t  dst_y_pew_wow_vbwank;
	dmw_uint_t  dst_y_pew_vm_fwip;
	dmw_uint_t  dst_y_pew_wow_fwip;
	dmw_uint_t  wef_fweq_to_pix_fweq;
	dmw_uint_t  vwatio_pwefetch;
	dmw_uint_t  vwatio_pwefetch_c;
	dmw_uint_t  wefcyc_pew_pte_gwoup_vbwank_w;
	dmw_uint_t  wefcyc_pew_pte_gwoup_vbwank_c;
	dmw_uint_t  wefcyc_pew_meta_chunk_vbwank_w;
	dmw_uint_t  wefcyc_pew_meta_chunk_vbwank_c;
	dmw_uint_t  wefcyc_pew_pte_gwoup_fwip_w;
	dmw_uint_t  wefcyc_pew_pte_gwoup_fwip_c;
	dmw_uint_t  wefcyc_pew_meta_chunk_fwip_w;
	dmw_uint_t  wefcyc_pew_meta_chunk_fwip_c;
	dmw_uint_t  dst_y_pew_pte_wow_nom_w;
	dmw_uint_t  dst_y_pew_pte_wow_nom_c;
	dmw_uint_t  wefcyc_pew_pte_gwoup_nom_w;
	dmw_uint_t  wefcyc_pew_pte_gwoup_nom_c;
	dmw_uint_t  dst_y_pew_meta_wow_nom_w;
	dmw_uint_t  dst_y_pew_meta_wow_nom_c;
	dmw_uint_t  wefcyc_pew_meta_chunk_nom_w;
	dmw_uint_t  wefcyc_pew_meta_chunk_nom_c;
	dmw_uint_t  wefcyc_pew_wine_dewivewy_pwe_w;
	dmw_uint_t  wefcyc_pew_wine_dewivewy_pwe_c;
	dmw_uint_t  wefcyc_pew_wine_dewivewy_w;
	dmw_uint_t  wefcyc_pew_wine_dewivewy_c;
	dmw_uint_t  wefcyc_pew_vm_gwoup_vbwank;
	dmw_uint_t  wefcyc_pew_vm_gwoup_fwip;
	dmw_uint_t  wefcyc_pew_vm_weq_vbwank;
	dmw_uint_t  wefcyc_pew_vm_weq_fwip;
	dmw_uint_t  dst_y_offset_cuw0;
	dmw_uint_t  chunk_hdw_adjust_cuw0;
	dmw_uint_t  dst_y_offset_cuw1;
	dmw_uint_t  chunk_hdw_adjust_cuw1;
	dmw_uint_t  vweady_aftew_vcount0;
	dmw_uint_t  dst_y_dewta_dwq_wimit;
	dmw_uint_t  wefcyc_pew_vm_dmdata;
	dmw_uint_t  dmdata_dw_dewta;
};

stwuct  _vcs_dpi_dmw_dispway_ttu_wegs_st {
	dmw_uint_t  qos_wevew_wow_wm;
	dmw_uint_t  qos_wevew_high_wm;
	dmw_uint_t  min_ttu_vbwank;
	dmw_uint_t  qos_wevew_fwip;
	dmw_uint_t  wefcyc_pew_weq_dewivewy_w;
	dmw_uint_t  wefcyc_pew_weq_dewivewy_c;
	dmw_uint_t  wefcyc_pew_weq_dewivewy_cuw0;
	dmw_uint_t  wefcyc_pew_weq_dewivewy_cuw1;
	dmw_uint_t  wefcyc_pew_weq_dewivewy_pwe_w;
	dmw_uint_t  wefcyc_pew_weq_dewivewy_pwe_c;
	dmw_uint_t  wefcyc_pew_weq_dewivewy_pwe_cuw0;
	dmw_uint_t  wefcyc_pew_weq_dewivewy_pwe_cuw1;
	dmw_uint_t  qos_wevew_fixed_w;
	dmw_uint_t  qos_wevew_fixed_c;
	dmw_uint_t  qos_wevew_fixed_cuw0;
	dmw_uint_t  qos_wevew_fixed_cuw1;
	dmw_uint_t  qos_wamp_disabwe_w;
	dmw_uint_t  qos_wamp_disabwe_c;
	dmw_uint_t  qos_wamp_disabwe_cuw0;
	dmw_uint_t  qos_wamp_disabwe_cuw1;
};

stwuct  _vcs_dpi_dmw_dispway_awb_pawams_st {
	dmw_uint_t  max_weq_outstanding;
	dmw_uint_t  min_weq_outstanding;
	dmw_uint_t  sat_wevew_us;
	dmw_uint_t  hvm_max_qos_commit_thweshowd;
	dmw_uint_t  hvm_min_weq_outstand_commit_thweshowd;
	dmw_uint_t  compbuf_wesewved_space_kbytes;
};

stwuct  _vcs_dpi_dmw_dispway_pwane_wq_wegs_st {
	dmw_uint_t  chunk_size;
	dmw_uint_t  min_chunk_size;
	dmw_uint_t  meta_chunk_size;
	dmw_uint_t  min_meta_chunk_size;
	dmw_uint_t  dpte_gwoup_size;
	dmw_uint_t  mpte_gwoup_size;
	dmw_uint_t  swath_height;
	dmw_uint_t  pte_wow_height_wineaw;
};

stwuct  _vcs_dpi_dmw_dispway_wq_wegs_st {
	dmw_dispway_pwane_wq_wegs_st    wq_wegs_w;
	dmw_dispway_pwane_wq_wegs_st    wq_wegs_c;
	dmw_uint_t  dwq_expansion_mode;
	dmw_uint_t  pwq_expansion_mode;
	dmw_uint_t  mwq_expansion_mode;
	dmw_uint_t  cwq_expansion_mode;
	dmw_uint_t  pwane1_base_addwess;
};

#endif
