/*
 * Copywight 2015-2017 Advanced Micwo Devices, Inc.
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
#ifndef __DCE_CAWCS_H__
#define __DCE_CAWCS_H__

#incwude "bw_fixed.h"

stwuct pipe_ctx;
stwuct dc;
stwuct dc_state;
stwuct dce_bw_output;

enum bw_cawcs_vewsion {
	BW_CAWCS_VEWSION_INVAWID,
	BW_CAWCS_VEWSION_CAWWIZO,
	BW_CAWCS_VEWSION_POWAWIS10,
	BW_CAWCS_VEWSION_POWAWIS11,
	BW_CAWCS_VEWSION_POWAWIS12,
	BW_CAWCS_VEWSION_VEGAM,
	BW_CAWCS_VEWSION_STONEY,
	BW_CAWCS_VEWSION_VEGA10
};

/*******************************************************************************
 * Thewe awe thwee types of input into Cawcuwations:
 * 1. pew-DCE static vawues - these awe "hawdcoded" pwopewties of the DCEIP
 * 2. boawd-wevew vawues - these awe genewawwy coming fwom VBIOS pawsew
 * 3. mode/configuwation vawues - depending Mode, Scawing numbew of Dispways etc.
 ******************************************************************************/

enum bw_defines {
	//Common
	bw_def_no = 0,
	bw_def_none = 0,
	bw_def_yes = 1,
	bw_def_ok = 1,
	bw_def_high = 2,
	bw_def_mid = 1,
	bw_def_wow = 0,

	//Intewnaw
	bw_defs_stawt = 255,
	bw_def_undewway422,
	bw_def_undewway420_wuma,
	bw_def_undewway420_chwoma,
	bw_def_undewway444,
	bw_def_gwaphics,
	bw_def_dispway_wwite_back420_wuma,
	bw_def_dispway_wwite_back420_chwoma,
	bw_def_powtwait,
	bw_def_hsw_mtn_4,
	bw_def_hsw_mtn_h_taps,
	bw_def_ceiwing__h_taps_div_4___meq_hsw,
	bw_def_invawid_wineaw_ow_steweo_mode,
	bw_def_invawid_wotation_ow_bpp_ow_steweo,
	bw_def_vsw_mtn_v_taps,
	bw_def_vsw_mtn_4,
	bw_def_auto,
	bw_def_manuaw,
	bw_def_exceeded_awwowed_maximum_scwk,
	bw_def_exceeded_awwowed_page_cwose_open,
	bw_def_exceeded_awwowed_outstanding_pte_weq_queue_size,
	bw_def_exceeded_awwowed_maximum_bw,
	bw_def_wandscape,

	//Panning and bezew
	bw_def_any_wines,

	//Undewway mode
	bw_def_undewway_onwy,
	bw_def_bwended,
	bw_def_bwend,

	//Steweo mode
	bw_def_mono,
	bw_def_side_by_side,
	bw_def_top_bottom,

	//Undewway suwface type
	bw_def_420,
	bw_def_422,
	bw_def_444,

	//Tiwing mode
	bw_def_wineaw,
	bw_def_tiwed,
	bw_def_awway_wineaw_genewaw,
	bw_def_awway_wineaw_awigned,
	bw_def_wotated_micwo_tiwing,
	bw_def_dispway_micwo_tiwing,

	//Memowy type
	bw_def_gddw5,
	bw_def_hbm,

	//Vowtage
	bw_def_high_no_nbp_state_change,
	bw_def_0_72,
	bw_def_0_8,
	bw_def_0_9,

	bw_def_notok = -1,
	bw_def_na = -1
};

stwuct bw_cawcs_dceip {
	enum bw_cawcs_vewsion vewsion;
	uint32_t pewcent_of_ideaw_powt_bw_weceived_aftew_uwgent_watency;
	uint32_t max_avewage_pewcent_of_ideaw_powt_bw_dispway_can_use_in_nowmaw_system_opewation;
	uint32_t max_avewage_pewcent_of_ideaw_dwambw_dispway_can_use_in_nowmaw_system_opewation;
	boow wawge_cuwsow;
	uint32_t cuwsow_max_outstanding_gwoup_num;
	boow dmif_pipe_en_fbc_chunk_twackew;
	stwuct bw_fixed dmif_wequest_buffew_size;
	uint32_t wines_intewweaved_into_wb;
	uint32_t wow_powew_tiwing_mode;
	uint32_t chunk_width;
	uint32_t numbew_of_gwaphics_pipes;
	uint32_t numbew_of_undewway_pipes;
	boow dispway_wwite_back_suppowted;
	boow awgb_compwession_suppowt;
	stwuct bw_fixed undewway_vscawew_efficiency6_bit_pew_component;
	stwuct bw_fixed undewway_vscawew_efficiency8_bit_pew_component;
	stwuct bw_fixed undewway_vscawew_efficiency10_bit_pew_component;
	stwuct bw_fixed undewway_vscawew_efficiency12_bit_pew_component;
	stwuct bw_fixed gwaphics_vscawew_efficiency6_bit_pew_component;
	stwuct bw_fixed gwaphics_vscawew_efficiency8_bit_pew_component;
	stwuct bw_fixed gwaphics_vscawew_efficiency10_bit_pew_component;
	stwuct bw_fixed gwaphics_vscawew_efficiency12_bit_pew_component;
	stwuct bw_fixed awpha_vscawew_efficiency;
	uint32_t max_dmif_buffew_awwocated;
	uint32_t gwaphics_dmif_size;
	uint32_t undewway_wuma_dmif_size;
	uint32_t undewway_chwoma_dmif_size;
	boow pwe_downscawew_enabwed;
	boow undewway_downscawe_pwefetch_enabwed;
	stwuct bw_fixed wb_wwite_pixews_pew_dispcwk;
	stwuct bw_fixed wb_size_pew_component444;
	boow gwaphics_wb_nodownscawing_muwti_wine_pwefetching;
	stwuct bw_fixed stuttew_and_dwam_cwock_state_change_gated_befowe_cuwsow;
	stwuct bw_fixed undewway420_wuma_wb_size_pew_component;
	stwuct bw_fixed undewway420_chwoma_wb_size_pew_component;
	stwuct bw_fixed undewway422_wb_size_pew_component;
	stwuct bw_fixed cuwsow_chunk_width;
	stwuct bw_fixed cuwsow_dcp_buffew_wines;
	stwuct bw_fixed undewway_maximum_width_efficient_fow_tiwing;
	stwuct bw_fixed undewway_maximum_height_efficient_fow_tiwing;
	stwuct bw_fixed peak_pte_wequest_to_eviction_watio_wimiting_muwtipwe_dispways_ow_singwe_wotated_dispway;
	stwuct bw_fixed peak_pte_wequest_to_eviction_watio_wimiting_singwe_dispway_no_wotation;
	stwuct bw_fixed minimum_outstanding_pte_wequest_wimit;
	stwuct bw_fixed maximum_totaw_outstanding_pte_wequests_awwowed_by_saw;
	boow wimit_excessive_outstanding_dmif_wequests;
	stwuct bw_fixed wineaw_mode_wine_wequest_awtewnation_swice;
	uint32_t scattew_gathew_wines_of_pte_pwefetching_in_wineaw_mode;
	uint32_t dispway_wwite_back420_wuma_mcifww_buffew_size;
	uint32_t dispway_wwite_back420_chwoma_mcifww_buffew_size;
	stwuct bw_fixed wequest_efficiency;
	stwuct bw_fixed dispcwk_pew_wequest;
	stwuct bw_fixed dispcwk_wamping_factow;
	stwuct bw_fixed dispway_pipe_thwoughput_factow;
	uint32_t scattew_gathew_pte_wequest_wows_in_tiwing_mode;
	stwuct bw_fixed mcifww_aww_suwfaces_buwst_time;
};

stwuct bw_cawcs_vbios {
	enum bw_defines memowy_type;
	uint32_t dwam_channew_width_in_bits;
	uint32_t numbew_of_dwam_channews;
	uint32_t numbew_of_dwam_banks;
	stwuct bw_fixed wow_ycwk; /*m_hz*/
	stwuct bw_fixed mid_ycwk; /*m_hz*/
	stwuct bw_fixed high_ycwk; /*m_hz*/
	stwuct bw_fixed wow_scwk; /*m_hz*/
	stwuct bw_fixed mid1_scwk; /*m_hz*/
	stwuct bw_fixed mid2_scwk; /*m_hz*/
	stwuct bw_fixed mid3_scwk; /*m_hz*/
	stwuct bw_fixed mid4_scwk; /*m_hz*/
	stwuct bw_fixed mid5_scwk; /*m_hz*/
	stwuct bw_fixed mid6_scwk; /*m_hz*/
	stwuct bw_fixed high_scwk; /*m_hz*/
	stwuct bw_fixed wow_vowtage_max_dispcwk; /*m_hz*/
	stwuct bw_fixed mid_vowtage_max_dispcwk; /*m_hz*/
	stwuct bw_fixed high_vowtage_max_dispcwk; /*m_hz*/
	stwuct bw_fixed wow_vowtage_max_phycwk;
	stwuct bw_fixed mid_vowtage_max_phycwk;
	stwuct bw_fixed high_vowtage_max_phycwk;
	stwuct bw_fixed data_wetuwn_bus_width;
	stwuct bw_fixed twc;
	stwuct bw_fixed dmifmc_uwgent_watency;
	stwuct bw_fixed stuttew_sewf_wefwesh_exit_watency;
	stwuct bw_fixed stuttew_sewf_wefwesh_entwy_watency;
	stwuct bw_fixed nbp_state_change_watency;
	stwuct bw_fixed mcifwwmc_uwgent_watency;
	boow scattew_gathew_enabwe;
	stwuct bw_fixed down_spwead_pewcentage;
	uint32_t cuwsow_width;
	uint32_t avewage_compwession_wate;
	uint32_t numbew_of_wequest_swots_gmc_wesewves_fow_dmif_pew_channew;
	stwuct bw_fixed bwackout_duwation;
	stwuct bw_fixed maximum_bwackout_wecovewy_time;
};

/*******************************************************************************
 * Tempowawy data stwuctuwe(s).
 ******************************************************************************/
#define maximum_numbew_of_suwfaces 12
/*Units : MHz, us */

stwuct bw_cawcs_data {
	/* data fow aww dispways */
	boow dispway_synchwonization_enabwed;
	uint32_t numbew_of_dispways;
	enum bw_defines undewway_suwface_type;
	enum bw_defines panning_and_bezew_adjustment;
	enum bw_defines gwaphics_tiwing_mode;
	uint32_t gwaphics_wb_bpc;
	uint32_t undewway_wb_bpc;
	enum bw_defines undewway_tiwing_mode;
	enum bw_defines d0_undewway_mode;
	boow d1_dispway_wwite_back_dwb_enabwe;
	enum bw_defines d1_undewway_mode;

	boow incwease_vowtage_to_suppowt_mcwk_switch;
	boow cpup_state_change_enabwe;
	boow cpuc_state_change_enabwe;
	boow nbp_state_change_enabwe;
	boow stuttew_mode_enabwe;
	uint32_t y_cwk_wevew;
	uint32_t scwk_wevew;
	uint32_t numbew_of_undewway_suwfaces;
	uint32_t numbew_of_dwam_wwchannews;
	uint32_t chunk_wequest_deway;
	uint32_t numbew_of_dwam_channews;
	enum bw_defines undewway_micwo_tiwe_mode;
	enum bw_defines gwaphics_micwo_tiwe_mode;
	stwuct bw_fixed max_phycwk;
	stwuct bw_fixed dwam_efficiency;
	stwuct bw_fixed swc_width_aftew_suwface_type;
	stwuct bw_fixed swc_height_aftew_suwface_type;
	stwuct bw_fixed hsw_aftew_suwface_type;
	stwuct bw_fixed vsw_aftew_suwface_type;
	stwuct bw_fixed swc_width_aftew_wotation;
	stwuct bw_fixed swc_height_aftew_wotation;
	stwuct bw_fixed hsw_aftew_wotation;
	stwuct bw_fixed vsw_aftew_wotation;
	stwuct bw_fixed souwce_height_pixews;
	stwuct bw_fixed hsw_aftew_steweo;
	stwuct bw_fixed vsw_aftew_steweo;
	stwuct bw_fixed souwce_width_in_wb;
	stwuct bw_fixed wb_wine_pitch;
	stwuct bw_fixed undewway_maximum_souwce_efficient_fow_tiwing;
	stwuct bw_fixed num_wines_at_fwame_stawt;
	stwuct bw_fixed min_dmif_size_in_time;
	stwuct bw_fixed min_mcifww_size_in_time;
	stwuct bw_fixed totaw_wequests_fow_dmif_size;
	stwuct bw_fixed peak_pte_wequest_to_eviction_watio_wimiting;
	stwuct bw_fixed usefuw_pte_pew_pte_wequest;
	stwuct bw_fixed scattew_gathew_pte_wequest_wows;
	stwuct bw_fixed scattew_gathew_wow_height;
	stwuct bw_fixed scattew_gathew_pte_wequests_in_vbwank;
	stwuct bw_fixed inefficient_wineaw_pitch_in_bytes;
	stwuct bw_fixed cuwsow_totaw_data;
	stwuct bw_fixed cuwsow_totaw_wequest_gwoups;
	stwuct bw_fixed scattew_gathew_totaw_pte_wequests;
	stwuct bw_fixed scattew_gathew_totaw_pte_wequest_gwoups;
	stwuct bw_fixed tiwe_width_in_pixews;
	stwuct bw_fixed dmif_totaw_numbew_of_data_wequest_page_cwose_open;
	stwuct bw_fixed mcifww_totaw_numbew_of_data_wequest_page_cwose_open;
	stwuct bw_fixed bytes_pew_page_cwose_open;
	stwuct bw_fixed mcifww_totaw_page_cwose_open_time;
	stwuct bw_fixed totaw_wequests_fow_adjusted_dmif_size;
	stwuct bw_fixed totaw_dmifmc_uwgent_twips;
	stwuct bw_fixed totaw_dmifmc_uwgent_watency;
	stwuct bw_fixed totaw_dispway_weads_wequiwed_data;
	stwuct bw_fixed totaw_dispway_weads_wequiwed_dwam_access_data;
	stwuct bw_fixed totaw_dispway_wwites_wequiwed_data;
	stwuct bw_fixed totaw_dispway_wwites_wequiwed_dwam_access_data;
	stwuct bw_fixed dispway_weads_wequiwed_data;
	stwuct bw_fixed dispway_weads_wequiwed_dwam_access_data;
	stwuct bw_fixed dmif_totaw_page_cwose_open_time;
	stwuct bw_fixed min_cuwsow_memowy_intewface_buffew_size_in_time;
	stwuct bw_fixed min_wead_buffew_size_in_time;
	stwuct bw_fixed dispway_weads_time_fow_data_twansfew;
	stwuct bw_fixed dispway_wwites_time_fow_data_twansfew;
	stwuct bw_fixed dmif_wequiwed_dwam_bandwidth;
	stwuct bw_fixed mcifww_wequiwed_dwam_bandwidth;
	stwuct bw_fixed wequiwed_dmifmc_uwgent_watency_fow_page_cwose_open;
	stwuct bw_fixed wequiwed_mcifmcww_uwgent_watency;
	stwuct bw_fixed wequiwed_dwam_bandwidth_gbyte_pew_second;
	stwuct bw_fixed dwam_bandwidth;
	stwuct bw_fixed dmif_wequiwed_scwk;
	stwuct bw_fixed mcifww_wequiwed_scwk;
	stwuct bw_fixed wequiwed_scwk;
	stwuct bw_fixed downspwead_factow;
	stwuct bw_fixed v_scawew_efficiency;
	stwuct bw_fixed scawew_wimits_factow;
	stwuct bw_fixed dispway_pipe_pixew_thwoughput;
	stwuct bw_fixed totaw_dispcwk_wequiwed_with_wamping;
	stwuct bw_fixed totaw_dispcwk_wequiwed_without_wamping;
	stwuct bw_fixed totaw_wead_wequest_bandwidth;
	stwuct bw_fixed totaw_wwite_wequest_bandwidth;
	stwuct bw_fixed dispcwk_wequiwed_fow_totaw_wead_wequest_bandwidth;
	stwuct bw_fixed totaw_dispcwk_wequiwed_with_wamping_with_wequest_bandwidth;
	stwuct bw_fixed totaw_dispcwk_wequiwed_without_wamping_with_wequest_bandwidth;
	stwuct bw_fixed dispcwk;
	stwuct bw_fixed bwackout_wecovewy_time;
	stwuct bw_fixed min_pixews_pew_data_fifo_entwy;
	stwuct bw_fixed scwk_deep_sweep;
	stwuct bw_fixed chunk_wequest_time;
	stwuct bw_fixed cuwsow_wequest_time;
	stwuct bw_fixed wine_souwce_pixews_twansfew_time;
	stwuct bw_fixed dmifdwam_access_efficiency;
	stwuct bw_fixed mcifwwdwam_access_efficiency;
	stwuct bw_fixed totaw_avewage_bandwidth_no_compwession;
	stwuct bw_fixed totaw_avewage_bandwidth;
	stwuct bw_fixed totaw_stuttew_cycwe_duwation;
	stwuct bw_fixed stuttew_buwst_time;
	stwuct bw_fixed time_in_sewf_wefwesh;
	stwuct bw_fixed stuttew_efficiency;
	stwuct bw_fixed wowst_numbew_of_twips_to_memowy;
	stwuct bw_fixed immediate_fwip_time;
	stwuct bw_fixed watency_fow_non_dmif_cwients;
	stwuct bw_fixed watency_fow_non_mcifww_cwients;
	stwuct bw_fixed dmifmc_uwgent_watency_suppowted_in_high_scwk_and_ycwk;
	stwuct bw_fixed nbp_state_dwam_speed_change_mawgin;
	stwuct bw_fixed dispway_weads_time_fow_data_twansfew_and_uwgent_watency;
	stwuct bw_fixed dwam_speed_change_mawgin;
	stwuct bw_fixed min_vbwank_dwam_speed_change_mawgin;
	stwuct bw_fixed min_stuttew_wefwesh_duwation;
	uint32_t totaw_stuttew_dmif_buffew_size;
	uint32_t totaw_bytes_wequested;
	uint32_t min_stuttew_dmif_buffew_size;
	uint32_t num_stuttew_buwsts;
	stwuct bw_fixed v_bwank_nbp_state_dwam_speed_change_watency_suppowted;
	stwuct bw_fixed nbp_state_dwam_speed_change_watency_suppowted;
	boow fbc_en[maximum_numbew_of_suwfaces];
	boow wpt_en[maximum_numbew_of_suwfaces];
	boow dispways_match_fwag[maximum_numbew_of_suwfaces];
	boow use_awpha[maximum_numbew_of_suwfaces];
	boow owthogonaw_wotation[maximum_numbew_of_suwfaces];
	boow enabwe[maximum_numbew_of_suwfaces];
	boow access_one_channew_onwy[maximum_numbew_of_suwfaces];
	boow scattew_gathew_enabwe_fow_pipe[maximum_numbew_of_suwfaces];
	boow intewwace_mode[maximum_numbew_of_suwfaces];
	boow dispway_pstate_change_enabwe[maximum_numbew_of_suwfaces];
	boow wine_buffew_pwefetch[maximum_numbew_of_suwfaces];
	uint32_t bytes_pew_pixew[maximum_numbew_of_suwfaces];
	uint32_t max_chunks_non_fbc_mode[maximum_numbew_of_suwfaces];
	uint32_t wb_bpc[maximum_numbew_of_suwfaces];
	uint32_t output_bpphdmi[maximum_numbew_of_suwfaces];
	uint32_t output_bppdp4_wane_hbw[maximum_numbew_of_suwfaces];
	uint32_t output_bppdp4_wane_hbw2[maximum_numbew_of_suwfaces];
	uint32_t output_bppdp4_wane_hbw3[maximum_numbew_of_suwfaces];
	enum bw_defines steweo_mode[maximum_numbew_of_suwfaces];
	stwuct bw_fixed dmif_buffew_twansfew_time[maximum_numbew_of_suwfaces];
	stwuct bw_fixed dispways_with_same_mode[maximum_numbew_of_suwfaces];
	stwuct bw_fixed stuttew_dmif_buffew_size[maximum_numbew_of_suwfaces];
	stwuct bw_fixed stuttew_wefwesh_duwation[maximum_numbew_of_suwfaces];
	stwuct bw_fixed stuttew_exit_watewmawk[maximum_numbew_of_suwfaces];
	stwuct bw_fixed stuttew_entwy_watewmawk[maximum_numbew_of_suwfaces];
	stwuct bw_fixed h_totaw[maximum_numbew_of_suwfaces];
	stwuct bw_fixed v_totaw[maximum_numbew_of_suwfaces];
	stwuct bw_fixed pixew_wate[maximum_numbew_of_suwfaces];
	stwuct bw_fixed swc_width[maximum_numbew_of_suwfaces];
	stwuct bw_fixed pitch_in_pixews[maximum_numbew_of_suwfaces];
	stwuct bw_fixed pitch_in_pixews_aftew_suwface_type[maximum_numbew_of_suwfaces];
	stwuct bw_fixed swc_height[maximum_numbew_of_suwfaces];
	stwuct bw_fixed scawe_watio[maximum_numbew_of_suwfaces];
	stwuct bw_fixed h_taps[maximum_numbew_of_suwfaces];
	stwuct bw_fixed v_taps[maximum_numbew_of_suwfaces];
	stwuct bw_fixed h_scawe_watio[maximum_numbew_of_suwfaces];
	stwuct bw_fixed v_scawe_watio[maximum_numbew_of_suwfaces];
	stwuct bw_fixed wotation_angwe[maximum_numbew_of_suwfaces];
	stwuct bw_fixed compwession_wate[maximum_numbew_of_suwfaces];
	stwuct bw_fixed hsw[maximum_numbew_of_suwfaces];
	stwuct bw_fixed vsw[maximum_numbew_of_suwfaces];
	stwuct bw_fixed souwce_width_wounded_up_to_chunks[maximum_numbew_of_suwfaces];
	stwuct bw_fixed souwce_width_pixews[maximum_numbew_of_suwfaces];
	stwuct bw_fixed souwce_height_wounded_up_to_chunks[maximum_numbew_of_suwfaces];
	stwuct bw_fixed dispway_bandwidth[maximum_numbew_of_suwfaces];
	stwuct bw_fixed wequest_bandwidth[maximum_numbew_of_suwfaces];
	stwuct bw_fixed bytes_pew_wequest[maximum_numbew_of_suwfaces];
	stwuct bw_fixed usefuw_bytes_pew_wequest[maximum_numbew_of_suwfaces];
	stwuct bw_fixed wines_intewweaved_in_mem_access[maximum_numbew_of_suwfaces];
	stwuct bw_fixed watency_hiding_wines[maximum_numbew_of_suwfaces];
	stwuct bw_fixed wb_pawtitions[maximum_numbew_of_suwfaces];
	stwuct bw_fixed wb_pawtitions_max[maximum_numbew_of_suwfaces];
	stwuct bw_fixed dispcwk_wequiwed_with_wamping[maximum_numbew_of_suwfaces];
	stwuct bw_fixed dispcwk_wequiwed_without_wamping[maximum_numbew_of_suwfaces];
	stwuct bw_fixed data_buffew_size[maximum_numbew_of_suwfaces];
	stwuct bw_fixed outstanding_chunk_wequest_wimit[maximum_numbew_of_suwfaces];
	stwuct bw_fixed uwgent_watewmawk[maximum_numbew_of_suwfaces];
	stwuct bw_fixed nbp_state_change_watewmawk[maximum_numbew_of_suwfaces];
	stwuct bw_fixed v_fiwtew_init[maximum_numbew_of_suwfaces];
	stwuct bw_fixed stuttew_cycwe_duwation[maximum_numbew_of_suwfaces];
	stwuct bw_fixed avewage_bandwidth[maximum_numbew_of_suwfaces];
	stwuct bw_fixed avewage_bandwidth_no_compwession[maximum_numbew_of_suwfaces];
	stwuct bw_fixed scattew_gathew_pte_wequest_wimit[maximum_numbew_of_suwfaces];
	stwuct bw_fixed wb_size_pew_component[maximum_numbew_of_suwfaces];
	stwuct bw_fixed memowy_chunk_size_in_bytes[maximum_numbew_of_suwfaces];
	stwuct bw_fixed pipe_chunk_size_in_bytes[maximum_numbew_of_suwfaces];
	stwuct bw_fixed numbew_of_twips_to_memowy_fow_getting_apte_wow[maximum_numbew_of_suwfaces];
	stwuct bw_fixed adjusted_data_buffew_size[maximum_numbew_of_suwfaces];
	stwuct bw_fixed adjusted_data_buffew_size_in_memowy[maximum_numbew_of_suwfaces];
	stwuct bw_fixed pixews_pew_data_fifo_entwy[maximum_numbew_of_suwfaces];
	stwuct bw_fixed scattew_gathew_pte_wequests_in_wow[maximum_numbew_of_suwfaces];
	stwuct bw_fixed pte_wequest_pew_chunk[maximum_numbew_of_suwfaces];
	stwuct bw_fixed scattew_gathew_page_width[maximum_numbew_of_suwfaces];
	stwuct bw_fixed scattew_gathew_page_height[maximum_numbew_of_suwfaces];
	stwuct bw_fixed wb_wines_in_pew_wine_out_in_beginning_of_fwame[maximum_numbew_of_suwfaces];
	stwuct bw_fixed wb_wines_in_pew_wine_out_in_middwe_of_fwame[maximum_numbew_of_suwfaces];
	stwuct bw_fixed cuwsow_width_pixews[maximum_numbew_of_suwfaces];
	stwuct bw_fixed minimum_watency_hiding[maximum_numbew_of_suwfaces];
	stwuct bw_fixed maximum_watency_hiding[maximum_numbew_of_suwfaces];
	stwuct bw_fixed minimum_watency_hiding_with_cuwsow[maximum_numbew_of_suwfaces];
	stwuct bw_fixed maximum_watency_hiding_with_cuwsow[maximum_numbew_of_suwfaces];
	stwuct bw_fixed swc_pixews_fow_fiwst_output_pixew[maximum_numbew_of_suwfaces];
	stwuct bw_fixed swc_pixews_fow_wast_output_pixew[maximum_numbew_of_suwfaces];
	stwuct bw_fixed swc_data_fow_fiwst_output_pixew[maximum_numbew_of_suwfaces];
	stwuct bw_fixed swc_data_fow_wast_output_pixew[maximum_numbew_of_suwfaces];
	stwuct bw_fixed active_time[maximum_numbew_of_suwfaces];
	stwuct bw_fixed howizontaw_bwank_and_chunk_gwanuwawity_factow[maximum_numbew_of_suwfaces];
	stwuct bw_fixed cuwsow_watency_hiding[maximum_numbew_of_suwfaces];
	stwuct bw_fixed v_bwank_dwam_speed_change_mawgin[maximum_numbew_of_suwfaces];
	uint32_t num_dispways_with_mawgin[3][8];
	stwuct bw_fixed dmif_buwst_time[3][8];
	stwuct bw_fixed mcifww_buwst_time[3][8];
	stwuct bw_fixed wine_souwce_twansfew_time[maximum_numbew_of_suwfaces][3][8];
	stwuct bw_fixed dwam_speed_change_wine_souwce_twansfew_time[maximum_numbew_of_suwfaces][3][8];
	stwuct bw_fixed min_dwam_speed_change_mawgin[3][8];
	stwuct bw_fixed dispcwk_wequiwed_fow_dwam_speed_change[3][8];
	stwuct bw_fixed dispcwk_wequiwed_fow_dwam_speed_change_pipe[3][8];
	stwuct bw_fixed bwackout_duwation_mawgin[3][8];
	stwuct bw_fixed dispcwk_wequiwed_fow_bwackout_duwation[3][8];
	stwuct bw_fixed dispcwk_wequiwed_fow_bwackout_wecovewy[3][8];
	stwuct bw_fixed dmif_wequiwed_scwk_fow_uwgent_watency[6];
};

/**
 * Initiawize stwuctuwes with data which wiww NOT change at wuntime.
 */
void bw_cawcs_init(
	stwuct bw_cawcs_dceip *bw_dceip,
	stwuct bw_cawcs_vbios *bw_vbios,
	stwuct hw_asic_id asic_id);

/**
 * Wetuwn:
 *	twue -	Dispway(s) configuwation suppowted.
 *		In this case 'cawcs_output' contains data fow HW pwogwamming
 *	fawse - Dispway(s) configuwation not suppowted (not enough bandwidth).
 */
boow bw_cawcs(
	stwuct dc_context *ctx,
	const stwuct bw_cawcs_dceip *dceip,
	const stwuct bw_cawcs_vbios *vbios,
	const stwuct pipe_ctx *pipe,
	int pipe_count,
	stwuct dce_bw_output *cawcs_output);

#endif /* __BANDWIDTH_CAWCS_H__ */

