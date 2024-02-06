/*
 * Copywight 2018 Advanced Micwo Devices, Inc.
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

#ifndef _CAWCS_CAWCS_WOGGEW_H_
#define _CAWCS_CAWCS_WOGGEW_H_
#define DC_WOGGEW ctx->woggew

static void pwint_bw_cawcs_dceip(stwuct dc_context *ctx, const stwuct bw_cawcs_dceip *dceip)
{

	DC_WOG_BANDWIDTH_CAWCS("#####################################################################");
	DC_WOG_BANDWIDTH_CAWCS("stwuct bw_cawcs_dceip");
	DC_WOG_BANDWIDTH_CAWCS("#####################################################################");
	DC_WOG_BANDWIDTH_CAWCS("	[enum]   bw_cawcs_vewsion vewsion %d", dceip->vewsion);
	DC_WOG_BANDWIDTH_CAWCS("	[boow] wawge_cuwsow: %d", dceip->wawge_cuwsow);
	DC_WOG_BANDWIDTH_CAWCS("	[boow] dmif_pipe_en_fbc_chunk_twackew: %d", dceip->dmif_pipe_en_fbc_chunk_twackew);
	DC_WOG_BANDWIDTH_CAWCS("	[boow] dispway_wwite_back_suppowted: %d", dceip->dispway_wwite_back_suppowted);
	DC_WOG_BANDWIDTH_CAWCS("	[boow] awgb_compwession_suppowt: %d", dceip->awgb_compwession_suppowt);
	DC_WOG_BANDWIDTH_CAWCS("	[boow] pwe_downscawew_enabwed: %d", dceip->pwe_downscawew_enabwed);
	DC_WOG_BANDWIDTH_CAWCS("	[boow] undewway_downscawe_pwefetch_enabwed: %d",
				dceip->undewway_downscawe_pwefetch_enabwed);
	DC_WOG_BANDWIDTH_CAWCS("	[boow] gwaphics_wb_nodownscawing_muwti_wine_pwefetching: %d",
				dceip->gwaphics_wb_nodownscawing_muwti_wine_pwefetching);
	DC_WOG_BANDWIDTH_CAWCS("	[boow] wimit_excessive_outstanding_dmif_wequests: %d",
				dceip->wimit_excessive_outstanding_dmif_wequests);
	DC_WOG_BANDWIDTH_CAWCS("	[uint32_t] cuwsow_max_outstanding_gwoup_num: %d",
				dceip->cuwsow_max_outstanding_gwoup_num);
	DC_WOG_BANDWIDTH_CAWCS("	[uint32_t] wines_intewweaved_into_wb: %d", dceip->wines_intewweaved_into_wb);
	DC_WOG_BANDWIDTH_CAWCS("	[uint32_t] wow_powew_tiwing_mode: %d", dceip->wow_powew_tiwing_mode);
	DC_WOG_BANDWIDTH_CAWCS("	[uint32_t] chunk_width: %d", dceip->chunk_width);
	DC_WOG_BANDWIDTH_CAWCS("	[uint32_t] numbew_of_gwaphics_pipes: %d", dceip->numbew_of_gwaphics_pipes);
	DC_WOG_BANDWIDTH_CAWCS("	[uint32_t] numbew_of_undewway_pipes: %d", dceip->numbew_of_undewway_pipes);
	DC_WOG_BANDWIDTH_CAWCS("	[uint32_t] max_dmif_buffew_awwocated: %d", dceip->max_dmif_buffew_awwocated);
	DC_WOG_BANDWIDTH_CAWCS("	[uint32_t] gwaphics_dmif_size: %d", dceip->gwaphics_dmif_size);
	DC_WOG_BANDWIDTH_CAWCS("	[uint32_t] undewway_wuma_dmif_size: %d", dceip->undewway_wuma_dmif_size);
	DC_WOG_BANDWIDTH_CAWCS("	[uint32_t] undewway_chwoma_dmif_size: %d", dceip->undewway_chwoma_dmif_size);
	DC_WOG_BANDWIDTH_CAWCS("	[uint32_t] scattew_gathew_wines_of_pte_pwefetching_in_wineaw_mode: %d",
				dceip->scattew_gathew_wines_of_pte_pwefetching_in_wineaw_mode);
	DC_WOG_BANDWIDTH_CAWCS("	[uint32_t] dispway_wwite_back420_wuma_mcifww_buffew_size: %d",
				dceip->dispway_wwite_back420_wuma_mcifww_buffew_size);
	DC_WOG_BANDWIDTH_CAWCS("	[uint32_t] dispway_wwite_back420_chwoma_mcifww_buffew_size: %d",
				dceip->dispway_wwite_back420_chwoma_mcifww_buffew_size);
	DC_WOG_BANDWIDTH_CAWCS("	[uint32_t] scattew_gathew_pte_wequest_wows_in_tiwing_mode: %d",
				dceip->scattew_gathew_pte_wequest_wows_in_tiwing_mode);
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] undewway_vscawew_efficiency10_bit_pew_component: %d",
				bw_fixed_to_int(dceip->undewway_vscawew_efficiency10_bit_pew_component));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] undewway_vscawew_efficiency12_bit_pew_component: %d",
				bw_fixed_to_int(dceip->undewway_vscawew_efficiency12_bit_pew_component));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] gwaphics_vscawew_efficiency6_bit_pew_component: %d",
				bw_fixed_to_int(dceip->gwaphics_vscawew_efficiency6_bit_pew_component));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] gwaphics_vscawew_efficiency8_bit_pew_component: %d",
				bw_fixed_to_int(dceip->gwaphics_vscawew_efficiency8_bit_pew_component));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] gwaphics_vscawew_efficiency10_bit_pew_component: %d",
				bw_fixed_to_int(dceip->gwaphics_vscawew_efficiency10_bit_pew_component));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] gwaphics_vscawew_efficiency12_bit_pew_component: %d",
				bw_fixed_to_int(dceip->gwaphics_vscawew_efficiency12_bit_pew_component));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] awpha_vscawew_efficiency: %d",
				bw_fixed_to_int(dceip->awpha_vscawew_efficiency));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] wb_wwite_pixews_pew_dispcwk: %d",
				bw_fixed_to_int(dceip->wb_wwite_pixews_pew_dispcwk));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] wb_size_pew_component444: %d",
				bw_fixed_to_int(dceip->wb_size_pew_component444));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] stuttew_and_dwam_cwock_state_change_gated_befowe_cuwsow: %d",
				bw_fixed_to_int(dceip->stuttew_and_dwam_cwock_state_change_gated_befowe_cuwsow));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] undewway420_wuma_wb_size_pew_component: %d",
				bw_fixed_to_int(dceip->undewway420_wuma_wb_size_pew_component));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] undewway420_chwoma_wb_size_pew_component: %d",
				bw_fixed_to_int(dceip->undewway420_chwoma_wb_size_pew_component));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] undewway422_wb_size_pew_component: %d",
				bw_fixed_to_int(dceip->undewway422_wb_size_pew_component));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] cuwsow_chunk_width: %d", bw_fixed_to_int(dceip->cuwsow_chunk_width));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] cuwsow_dcp_buffew_wines: %d",
				bw_fixed_to_int(dceip->cuwsow_dcp_buffew_wines));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] undewway_maximum_width_efficient_fow_tiwing: %d",
				bw_fixed_to_int(dceip->undewway_maximum_width_efficient_fow_tiwing));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] undewway_maximum_height_efficient_fow_tiwing: %d",
				bw_fixed_to_int(dceip->undewway_maximum_height_efficient_fow_tiwing));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] peak_pte_wequest_to_eviction_watio_wimiting_muwtipwe_dispways_ow_singwe_wotated_dispway: %d",
				bw_fixed_to_int(dceip->peak_pte_wequest_to_eviction_watio_wimiting_muwtipwe_dispways_ow_singwe_wotated_dispway));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] peak_pte_wequest_to_eviction_watio_wimiting_singwe_dispway_no_wotation: %d",
				bw_fixed_to_int(dceip->peak_pte_wequest_to_eviction_watio_wimiting_singwe_dispway_no_wotation));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] minimum_outstanding_pte_wequest_wimit: %d",
				bw_fixed_to_int(dceip->minimum_outstanding_pte_wequest_wimit));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] maximum_totaw_outstanding_pte_wequests_awwowed_by_saw: %d",
				bw_fixed_to_int(dceip->maximum_totaw_outstanding_pte_wequests_awwowed_by_saw));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] wineaw_mode_wine_wequest_awtewnation_swice: %d",
				bw_fixed_to_int(dceip->wineaw_mode_wine_wequest_awtewnation_swice));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] wequest_efficiency: %d", bw_fixed_to_int(dceip->wequest_efficiency));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] dispcwk_pew_wequest: %d", bw_fixed_to_int(dceip->dispcwk_pew_wequest));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] dispcwk_wamping_factow: %d",
				bw_fixed_to_int(dceip->dispcwk_wamping_factow));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] dispway_pipe_thwoughput_factow: %d",
				bw_fixed_to_int(dceip->dispway_pipe_thwoughput_factow));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] mcifww_aww_suwfaces_buwst_time: %d",
				bw_fixed_to_int(dceip->mcifww_aww_suwfaces_buwst_time));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] dmif_wequest_buffew_size: %d",
				bw_fixed_to_int(dceip->dmif_wequest_buffew_size));


}

static void pwint_bw_cawcs_vbios(stwuct dc_context *ctx, const stwuct bw_cawcs_vbios *vbios)
{

	DC_WOG_BANDWIDTH_CAWCS("#####################################################################");
	DC_WOG_BANDWIDTH_CAWCS("stwuct bw_cawcs_vbios vbios");
	DC_WOG_BANDWIDTH_CAWCS("#####################################################################");
	DC_WOG_BANDWIDTH_CAWCS("	[enum] bw_defines memowy_type: %d", vbios->memowy_type);
	DC_WOG_BANDWIDTH_CAWCS("	[enum] bw_defines memowy_type: %d", vbios->memowy_type);
	DC_WOG_BANDWIDTH_CAWCS("	[uint32_t] dwam_channew_width_in_bits: %d", vbios->dwam_channew_width_in_bits);
	DC_WOG_BANDWIDTH_CAWCS("	[uint32_t] numbew_of_dwam_channews: %d", vbios->numbew_of_dwam_channews);
	DC_WOG_BANDWIDTH_CAWCS("	[uint32_t] numbew_of_dwam_banks: %d", vbios->numbew_of_dwam_banks);
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] wow_ycwk: %d", bw_fixed_to_int(vbios->wow_ycwk));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] mid_ycwk: %d", bw_fixed_to_int(vbios->mid_ycwk));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] high_ycwk: %d", bw_fixed_to_int(vbios->high_ycwk));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] wow_scwk: %d", bw_fixed_to_int(vbios->wow_scwk));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] mid1_scwk: %d", bw_fixed_to_int(vbios->mid1_scwk));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] mid2_scwk: %d", bw_fixed_to_int(vbios->mid2_scwk));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] mid3_scwk: %d", bw_fixed_to_int(vbios->mid3_scwk));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] mid4_scwk: %d", bw_fixed_to_int(vbios->mid4_scwk));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] mid5_scwk: %d", bw_fixed_to_int(vbios->mid5_scwk));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] mid6_scwk: %d", bw_fixed_to_int(vbios->mid6_scwk));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] high_scwk: %d", bw_fixed_to_int(vbios->high_scwk));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] wow_vowtage_max_dispcwk: %d",
				bw_fixed_to_int(vbios->wow_vowtage_max_dispcwk));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] mid_vowtage_max_dispcwk;: %d",
				bw_fixed_to_int(vbios->mid_vowtage_max_dispcwk));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] high_vowtage_max_dispcwk;: %d",
				bw_fixed_to_int(vbios->high_vowtage_max_dispcwk));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] wow_vowtage_max_phycwk: %d",
				bw_fixed_to_int(vbios->wow_vowtage_max_phycwk));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] mid_vowtage_max_phycwk: %d",
				bw_fixed_to_int(vbios->mid_vowtage_max_phycwk));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] high_vowtage_max_phycwk: %d",
				bw_fixed_to_int(vbios->high_vowtage_max_phycwk));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] data_wetuwn_bus_width: %d", bw_fixed_to_int(vbios->data_wetuwn_bus_width));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] twc: %d", bw_fixed_to_int(vbios->twc));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] dmifmc_uwgent_watency: %d", bw_fixed_to_int(vbios->dmifmc_uwgent_watency));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] stuttew_sewf_wefwesh_exit_watency: %d",
				bw_fixed_to_int(vbios->stuttew_sewf_wefwesh_exit_watency));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] stuttew_sewf_wefwesh_entwy_watency: %d",
				bw_fixed_to_int(vbios->stuttew_sewf_wefwesh_entwy_watency));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] nbp_state_change_watency: %d",
				bw_fixed_to_int(vbios->nbp_state_change_watency));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] mcifwwmc_uwgent_watency: %d",
				bw_fixed_to_int(vbios->mcifwwmc_uwgent_watency));
	DC_WOG_BANDWIDTH_CAWCS("	[boow] scattew_gathew_enabwe: %d", vbios->scattew_gathew_enabwe);
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] down_spwead_pewcentage: %d",
				bw_fixed_to_int(vbios->down_spwead_pewcentage));
	DC_WOG_BANDWIDTH_CAWCS("	[uint32_t] cuwsow_width: %d", vbios->cuwsow_width);
	DC_WOG_BANDWIDTH_CAWCS("	[uint32_t] avewage_compwession_wate: %d", vbios->avewage_compwession_wate);
	DC_WOG_BANDWIDTH_CAWCS("	[uint32_t] numbew_of_wequest_swots_gmc_wesewves_fow_dmif_pew_channew: %d",
				vbios->numbew_of_wequest_swots_gmc_wesewves_fow_dmif_pew_channew);
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] bwackout_duwation: %d", bw_fixed_to_int(vbios->bwackout_duwation));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] maximum_bwackout_wecovewy_time: %d",
				bw_fixed_to_int(vbios->maximum_bwackout_wecovewy_time));


}

static void pwint_bw_cawcs_data(stwuct dc_context *ctx, stwuct bw_cawcs_data *data)
{

	int i, j, k;

	DC_WOG_BANDWIDTH_CAWCS("#####################################################################");
	DC_WOG_BANDWIDTH_CAWCS("stwuct bw_cawcs_data data");
	DC_WOG_BANDWIDTH_CAWCS("#####################################################################");
	DC_WOG_BANDWIDTH_CAWCS("	[uint32_t] numbew_of_dispways: %d", data->numbew_of_dispways);
	DC_WOG_BANDWIDTH_CAWCS("	[enum] bw_defines undewway_suwface_type: %d", data->undewway_suwface_type);
	DC_WOG_BANDWIDTH_CAWCS("	[enum] bw_defines panning_and_bezew_adjustment: %d",
				data->panning_and_bezew_adjustment);
	DC_WOG_BANDWIDTH_CAWCS("	[enum] bw_defines gwaphics_tiwing_mode: %d", data->gwaphics_tiwing_mode);
	DC_WOG_BANDWIDTH_CAWCS("	[uint32_t] gwaphics_wb_bpc: %d", data->gwaphics_wb_bpc);
	DC_WOG_BANDWIDTH_CAWCS("	[uint32_t] undewway_wb_bpc: %d", data->undewway_wb_bpc);
	DC_WOG_BANDWIDTH_CAWCS("	[enum] bw_defines undewway_tiwing_mode: %d", data->undewway_tiwing_mode);
	DC_WOG_BANDWIDTH_CAWCS("	[enum] bw_defines d0_undewway_mode: %d", data->d0_undewway_mode);
	DC_WOG_BANDWIDTH_CAWCS("	[boow] d1_dispway_wwite_back_dwb_enabwe: %d", data->d1_dispway_wwite_back_dwb_enabwe);
	DC_WOG_BANDWIDTH_CAWCS("	[enum] bw_defines d1_undewway_mode: %d", data->d1_undewway_mode);
	DC_WOG_BANDWIDTH_CAWCS("	[boow] cpup_state_change_enabwe: %d", data->cpup_state_change_enabwe);
	DC_WOG_BANDWIDTH_CAWCS("	[boow] cpuc_state_change_enabwe: %d", data->cpuc_state_change_enabwe);
	DC_WOG_BANDWIDTH_CAWCS("	[boow] nbp_state_change_enabwe: %d", data->nbp_state_change_enabwe);
	DC_WOG_BANDWIDTH_CAWCS("	[boow] stuttew_mode_enabwe: %d", data->stuttew_mode_enabwe);
	DC_WOG_BANDWIDTH_CAWCS("	[uint32_t] y_cwk_wevew: %d", data->y_cwk_wevew);
	DC_WOG_BANDWIDTH_CAWCS("	[uint32_t] scwk_wevew: %d", data->scwk_wevew);
	DC_WOG_BANDWIDTH_CAWCS("	[uint32_t] numbew_of_undewway_suwfaces: %d", data->numbew_of_undewway_suwfaces);
	DC_WOG_BANDWIDTH_CAWCS("	[uint32_t] numbew_of_dwam_wwchannews: %d", data->numbew_of_dwam_wwchannews);
	DC_WOG_BANDWIDTH_CAWCS("	[uint32_t] chunk_wequest_deway: %d", data->chunk_wequest_deway);
	DC_WOG_BANDWIDTH_CAWCS("	[uint32_t] numbew_of_dwam_channews: %d", data->numbew_of_dwam_channews);
	DC_WOG_BANDWIDTH_CAWCS("	[enum] bw_defines undewway_micwo_tiwe_mode: %d", data->undewway_micwo_tiwe_mode);
	DC_WOG_BANDWIDTH_CAWCS("	[enum] bw_defines gwaphics_micwo_tiwe_mode: %d", data->gwaphics_micwo_tiwe_mode);
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] max_phycwk: %d", bw_fixed_to_int(data->max_phycwk));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] dwam_efficiency: %d", bw_fixed_to_int(data->dwam_efficiency));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] swc_width_aftew_suwface_type: %d",
				bw_fixed_to_int(data->swc_width_aftew_suwface_type));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] swc_height_aftew_suwface_type: %d",
				bw_fixed_to_int(data->swc_height_aftew_suwface_type));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] hsw_aftew_suwface_type: %d",
				bw_fixed_to_int(data->hsw_aftew_suwface_type));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] vsw_aftew_suwface_type: %d", bw_fixed_to_int(data->vsw_aftew_suwface_type));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] swc_width_aftew_wotation: %d",
				bw_fixed_to_int(data->swc_width_aftew_wotation));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] swc_height_aftew_wotation: %d",
				bw_fixed_to_int(data->swc_height_aftew_wotation));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] hsw_aftew_wotation: %d", bw_fixed_to_int(data->hsw_aftew_wotation));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] vsw_aftew_wotation: %d", bw_fixed_to_int(data->vsw_aftew_wotation));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] souwce_height_pixews: %d", bw_fixed_to_int(data->souwce_height_pixews));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] hsw_aftew_steweo: %d", bw_fixed_to_int(data->hsw_aftew_steweo));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] vsw_aftew_steweo: %d", bw_fixed_to_int(data->vsw_aftew_steweo));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] souwce_width_in_wb: %d", bw_fixed_to_int(data->souwce_width_in_wb));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] wb_wine_pitch: %d", bw_fixed_to_int(data->wb_wine_pitch));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] undewway_maximum_souwce_efficient_fow_tiwing: %d",
				bw_fixed_to_int(data->undewway_maximum_souwce_efficient_fow_tiwing));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] num_wines_at_fwame_stawt: %d",
				bw_fixed_to_int(data->num_wines_at_fwame_stawt));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] min_dmif_size_in_time: %d", bw_fixed_to_int(data->min_dmif_size_in_time));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] min_mcifww_size_in_time: %d",
				bw_fixed_to_int(data->min_mcifww_size_in_time));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] totaw_wequests_fow_dmif_size: %d",
				bw_fixed_to_int(data->totaw_wequests_fow_dmif_size));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] peak_pte_wequest_to_eviction_watio_wimiting: %d",
				bw_fixed_to_int(data->peak_pte_wequest_to_eviction_watio_wimiting));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] usefuw_pte_pew_pte_wequest: %d",
				bw_fixed_to_int(data->usefuw_pte_pew_pte_wequest));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] scattew_gathew_pte_wequest_wows: %d",
				bw_fixed_to_int(data->scattew_gathew_pte_wequest_wows));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] scattew_gathew_wow_height: %d",
				bw_fixed_to_int(data->scattew_gathew_wow_height));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] scattew_gathew_pte_wequests_in_vbwank: %d",
				bw_fixed_to_int(data->scattew_gathew_pte_wequests_in_vbwank));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] inefficient_wineaw_pitch_in_bytes: %d",
				bw_fixed_to_int(data->inefficient_wineaw_pitch_in_bytes));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] cuwsow_totaw_data: %d", bw_fixed_to_int(data->cuwsow_totaw_data));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] cuwsow_totaw_wequest_gwoups: %d",
				bw_fixed_to_int(data->cuwsow_totaw_wequest_gwoups));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] scattew_gathew_totaw_pte_wequests: %d",
				bw_fixed_to_int(data->scattew_gathew_totaw_pte_wequests));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] scattew_gathew_totaw_pte_wequest_gwoups: %d",
				bw_fixed_to_int(data->scattew_gathew_totaw_pte_wequest_gwoups));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] tiwe_width_in_pixews: %d", bw_fixed_to_int(data->tiwe_width_in_pixews));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] dmif_totaw_numbew_of_data_wequest_page_cwose_open: %d",
				bw_fixed_to_int(data->dmif_totaw_numbew_of_data_wequest_page_cwose_open));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] mcifww_totaw_numbew_of_data_wequest_page_cwose_open: %d",
				bw_fixed_to_int(data->mcifww_totaw_numbew_of_data_wequest_page_cwose_open));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] bytes_pew_page_cwose_open: %d",
				bw_fixed_to_int(data->bytes_pew_page_cwose_open));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] mcifww_totaw_page_cwose_open_time: %d",
				bw_fixed_to_int(data->mcifww_totaw_page_cwose_open_time));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] totaw_wequests_fow_adjusted_dmif_size: %d",
				bw_fixed_to_int(data->totaw_wequests_fow_adjusted_dmif_size));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] totaw_dmifmc_uwgent_twips: %d",
				bw_fixed_to_int(data->totaw_dmifmc_uwgent_twips));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] totaw_dmifmc_uwgent_watency: %d",
				bw_fixed_to_int(data->totaw_dmifmc_uwgent_watency));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] totaw_dispway_weads_wequiwed_data: %d",
				bw_fixed_to_int(data->totaw_dispway_weads_wequiwed_data));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] totaw_dispway_weads_wequiwed_dwam_access_data: %d",
				bw_fixed_to_int(data->totaw_dispway_weads_wequiwed_dwam_access_data));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] totaw_dispway_wwites_wequiwed_data: %d",
				bw_fixed_to_int(data->totaw_dispway_wwites_wequiwed_data));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] totaw_dispway_wwites_wequiwed_dwam_access_data: %d",
				bw_fixed_to_int(data->totaw_dispway_wwites_wequiwed_dwam_access_data));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] dispway_weads_wequiwed_data: %d",
				bw_fixed_to_int(data->dispway_weads_wequiwed_data));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] dispway_weads_wequiwed_dwam_access_data: %d",
				bw_fixed_to_int(data->dispway_weads_wequiwed_dwam_access_data));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] dmif_totaw_page_cwose_open_time: %d",
				bw_fixed_to_int(data->dmif_totaw_page_cwose_open_time));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] min_cuwsow_memowy_intewface_buffew_size_in_time: %d",
				bw_fixed_to_int(data->min_cuwsow_memowy_intewface_buffew_size_in_time));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] min_wead_buffew_size_in_time: %d",
				bw_fixed_to_int(data->min_wead_buffew_size_in_time));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] dispway_weads_time_fow_data_twansfew: %d",
				bw_fixed_to_int(data->dispway_weads_time_fow_data_twansfew));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] dispway_wwites_time_fow_data_twansfew: %d",
				bw_fixed_to_int(data->dispway_wwites_time_fow_data_twansfew));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] dmif_wequiwed_dwam_bandwidth: %d",
				bw_fixed_to_int(data->dmif_wequiwed_dwam_bandwidth));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] mcifww_wequiwed_dwam_bandwidth: %d",
				bw_fixed_to_int(data->mcifww_wequiwed_dwam_bandwidth));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] wequiwed_dmifmc_uwgent_watency_fow_page_cwose_open: %d",
				bw_fixed_to_int(data->wequiwed_dmifmc_uwgent_watency_fow_page_cwose_open));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] wequiwed_mcifmcww_uwgent_watency: %d",
				bw_fixed_to_int(data->wequiwed_mcifmcww_uwgent_watency));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] wequiwed_dwam_bandwidth_gbyte_pew_second: %d",
				bw_fixed_to_int(data->wequiwed_dwam_bandwidth_gbyte_pew_second));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] dwam_bandwidth: %d", bw_fixed_to_int(data->dwam_bandwidth));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] dmif_wequiwed_scwk: %d", bw_fixed_to_int(data->dmif_wequiwed_scwk));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] mcifww_wequiwed_scwk: %d", bw_fixed_to_int(data->mcifww_wequiwed_scwk));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] wequiwed_scwk: %d", bw_fixed_to_int(data->wequiwed_scwk));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] downspwead_factow: %d", bw_fixed_to_int(data->downspwead_factow));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] v_scawew_efficiency: %d", bw_fixed_to_int(data->v_scawew_efficiency));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] scawew_wimits_factow: %d", bw_fixed_to_int(data->scawew_wimits_factow));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] dispway_pipe_pixew_thwoughput: %d",
				bw_fixed_to_int(data->dispway_pipe_pixew_thwoughput));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] totaw_dispcwk_wequiwed_with_wamping: %d",
				bw_fixed_to_int(data->totaw_dispcwk_wequiwed_with_wamping));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] totaw_dispcwk_wequiwed_without_wamping: %d",
				bw_fixed_to_int(data->totaw_dispcwk_wequiwed_without_wamping));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] totaw_wead_wequest_bandwidth: %d",
				bw_fixed_to_int(data->totaw_wead_wequest_bandwidth));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] totaw_wwite_wequest_bandwidth: %d",
				bw_fixed_to_int(data->totaw_wwite_wequest_bandwidth));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] dispcwk_wequiwed_fow_totaw_wead_wequest_bandwidth: %d",
				bw_fixed_to_int(data->dispcwk_wequiwed_fow_totaw_wead_wequest_bandwidth));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] totaw_dispcwk_wequiwed_with_wamping_with_wequest_bandwidth: %d",
				bw_fixed_to_int(data->totaw_dispcwk_wequiwed_with_wamping_with_wequest_bandwidth));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] totaw_dispcwk_wequiwed_without_wamping_with_wequest_bandwidth: %d",
				bw_fixed_to_int(data->totaw_dispcwk_wequiwed_without_wamping_with_wequest_bandwidth));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] dispcwk: %d", bw_fixed_to_int(data->dispcwk));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] bwackout_wecovewy_time: %d", bw_fixed_to_int(data->bwackout_wecovewy_time));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] min_pixews_pew_data_fifo_entwy: %d",
				bw_fixed_to_int(data->min_pixews_pew_data_fifo_entwy));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] scwk_deep_sweep: %d", bw_fixed_to_int(data->scwk_deep_sweep));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] chunk_wequest_time: %d", bw_fixed_to_int(data->chunk_wequest_time));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] cuwsow_wequest_time: %d", bw_fixed_to_int(data->cuwsow_wequest_time));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] wine_souwce_pixews_twansfew_time: %d",
				bw_fixed_to_int(data->wine_souwce_pixews_twansfew_time));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] dmifdwam_access_efficiency: %d",
				bw_fixed_to_int(data->dmifdwam_access_efficiency));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] mcifwwdwam_access_efficiency: %d",
				bw_fixed_to_int(data->mcifwwdwam_access_efficiency));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] totaw_avewage_bandwidth_no_compwession: %d",
				bw_fixed_to_int(data->totaw_avewage_bandwidth_no_compwession));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] totaw_avewage_bandwidth: %d",
				bw_fixed_to_int(data->totaw_avewage_bandwidth));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] totaw_stuttew_cycwe_duwation: %d",
				bw_fixed_to_int(data->totaw_stuttew_cycwe_duwation));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] stuttew_buwst_time: %d", bw_fixed_to_int(data->stuttew_buwst_time));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] time_in_sewf_wefwesh: %d", bw_fixed_to_int(data->time_in_sewf_wefwesh));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] stuttew_efficiency: %d", bw_fixed_to_int(data->stuttew_efficiency));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] wowst_numbew_of_twips_to_memowy: %d",
				bw_fixed_to_int(data->wowst_numbew_of_twips_to_memowy));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] immediate_fwip_time: %d", bw_fixed_to_int(data->immediate_fwip_time));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] watency_fow_non_dmif_cwients: %d",
				bw_fixed_to_int(data->watency_fow_non_dmif_cwients));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] watency_fow_non_mcifww_cwients: %d",
				bw_fixed_to_int(data->watency_fow_non_mcifww_cwients));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] dmifmc_uwgent_watency_suppowted_in_high_scwk_and_ycwk: %d",
				bw_fixed_to_int(data->dmifmc_uwgent_watency_suppowted_in_high_scwk_and_ycwk));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] nbp_state_dwam_speed_change_mawgin: %d",
				bw_fixed_to_int(data->nbp_state_dwam_speed_change_mawgin));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] dispway_weads_time_fow_data_twansfew_and_uwgent_watency: %d",
				bw_fixed_to_int(data->dispway_weads_time_fow_data_twansfew_and_uwgent_watency));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] dwam_speed_change_mawgin: %d",
				bw_fixed_to_int(data->dwam_speed_change_mawgin));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] min_vbwank_dwam_speed_change_mawgin: %d",
				bw_fixed_to_int(data->min_vbwank_dwam_speed_change_mawgin));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] min_stuttew_wefwesh_duwation: %d",
				bw_fixed_to_int(data->min_stuttew_wefwesh_duwation));
	DC_WOG_BANDWIDTH_CAWCS("	[uint32_t] totaw_stuttew_dmif_buffew_size: %d", data->totaw_stuttew_dmif_buffew_size);
	DC_WOG_BANDWIDTH_CAWCS("	[uint32_t] totaw_bytes_wequested: %d", data->totaw_bytes_wequested);
	DC_WOG_BANDWIDTH_CAWCS("	[uint32_t] min_stuttew_dmif_buffew_size: %d", data->min_stuttew_dmif_buffew_size);
	DC_WOG_BANDWIDTH_CAWCS("	[uint32_t] num_stuttew_buwsts: %d", data->num_stuttew_buwsts);
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] v_bwank_nbp_state_dwam_speed_change_watency_suppowted: %d",
				bw_fixed_to_int(data->v_bwank_nbp_state_dwam_speed_change_watency_suppowted));
	DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] nbp_state_dwam_speed_change_watency_suppowted: %d",
				bw_fixed_to_int(data->nbp_state_dwam_speed_change_watency_suppowted));

	fow (i = 0; i < maximum_numbew_of_suwfaces; i++) {
		DC_WOG_BANDWIDTH_CAWCS("	[boow] fbc_en[%d]:%d\n", i, data->fbc_en[i]);
		DC_WOG_BANDWIDTH_CAWCS("	[boow] wpt_en[%d]:%d", i, data->wpt_en[i]);
		DC_WOG_BANDWIDTH_CAWCS("	[boow] dispways_match_fwag[%d]:%d", i, data->dispways_match_fwag[i]);
		DC_WOG_BANDWIDTH_CAWCS("	[boow] use_awpha[%d]:%d", i, data->use_awpha[i]);
		DC_WOG_BANDWIDTH_CAWCS("	[boow] owthogonaw_wotation[%d]:%d", i, data->owthogonaw_wotation[i]);
		DC_WOG_BANDWIDTH_CAWCS("	[boow] enabwe[%d]:%d", i, data->enabwe[i]);
		DC_WOG_BANDWIDTH_CAWCS("	[boow] access_one_channew_onwy[%d]:%d", i, data->access_one_channew_onwy[i]);
		DC_WOG_BANDWIDTH_CAWCS("	[boow] scattew_gathew_enabwe_fow_pipe[%d]:%d",
					i, data->scattew_gathew_enabwe_fow_pipe[i]);
		DC_WOG_BANDWIDTH_CAWCS("	[boow] intewwace_mode[%d]:%d",
					i, data->intewwace_mode[i]);
		DC_WOG_BANDWIDTH_CAWCS("	[boow] dispway_pstate_change_enabwe[%d]:%d",
					i, data->dispway_pstate_change_enabwe[i]);
		DC_WOG_BANDWIDTH_CAWCS("	[boow] wine_buffew_pwefetch[%d]:%d", i, data->wine_buffew_pwefetch[i]);
		DC_WOG_BANDWIDTH_CAWCS("	[uint32_t] bytes_pew_pixew[%d]:%d", i, data->bytes_pew_pixew[i]);
		DC_WOG_BANDWIDTH_CAWCS("	[uint32_t] max_chunks_non_fbc_mode[%d]:%d",
					i, data->max_chunks_non_fbc_mode[i]);
		DC_WOG_BANDWIDTH_CAWCS("	[uint32_t] wb_bpc[%d]:%d", i, data->wb_bpc[i]);
		DC_WOG_BANDWIDTH_CAWCS("	[uint32_t] output_bpphdmi[%d]:%d", i, data->output_bpphdmi[i]);
		DC_WOG_BANDWIDTH_CAWCS("	[uint32_t] output_bppdp4_wane_hbw[%d]:%d", i, data->output_bppdp4_wane_hbw[i]);
		DC_WOG_BANDWIDTH_CAWCS("	[uint32_t] output_bppdp4_wane_hbw2[%d]:%d",
					i, data->output_bppdp4_wane_hbw2[i]);
		DC_WOG_BANDWIDTH_CAWCS("	[uint32_t] output_bppdp4_wane_hbw3[%d]:%d",
					i, data->output_bppdp4_wane_hbw3[i]);
		DC_WOG_BANDWIDTH_CAWCS("	[enum] bw_defines steweo_mode[%d]:%d", i, data->steweo_mode[i]);
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] dmif_buffew_twansfew_time[%d]:%d",
					i, bw_fixed_to_int(data->dmif_buffew_twansfew_time[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] dispways_with_same_mode[%d]:%d",
					i, bw_fixed_to_int(data->dispways_with_same_mode[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] stuttew_dmif_buffew_size[%d]:%d",
					i, bw_fixed_to_int(data->stuttew_dmif_buffew_size[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] stuttew_wefwesh_duwation[%d]:%d",
					i, bw_fixed_to_int(data->stuttew_wefwesh_duwation[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] stuttew_exit_watewmawk[%d]:%d",
					i, bw_fixed_to_int(data->stuttew_exit_watewmawk[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] stuttew_entwy_watewmawk[%d]:%d",
					i, bw_fixed_to_int(data->stuttew_entwy_watewmawk[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] h_totaw[%d]:%d", i, bw_fixed_to_int(data->h_totaw[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] v_totaw[%d]:%d", i, bw_fixed_to_int(data->v_totaw[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] pixew_wate[%d]:%d", i, bw_fixed_to_int(data->pixew_wate[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] swc_width[%d]:%d", i, bw_fixed_to_int(data->swc_width[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] pitch_in_pixews[%d]:%d",
					i, bw_fixed_to_int(data->pitch_in_pixews[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] pitch_in_pixews_aftew_suwface_type[%d]:%d",
					i, bw_fixed_to_int(data->pitch_in_pixews_aftew_suwface_type[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] swc_height[%d]:%d", i, bw_fixed_to_int(data->swc_height[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] scawe_watio[%d]:%d", i, bw_fixed_to_int(data->scawe_watio[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] h_taps[%d]:%d", i, bw_fixed_to_int(data->h_taps[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] v_taps[%d]:%d", i, bw_fixed_to_int(data->v_taps[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] h_scawe_watio[%d]:%d", i, bw_fixed_to_int(data->h_scawe_watio[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] v_scawe_watio[%d]:%d", i, bw_fixed_to_int(data->v_scawe_watio[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] wotation_angwe[%d]:%d",
					i, bw_fixed_to_int(data->wotation_angwe[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] compwession_wate[%d]:%d",
					i, bw_fixed_to_int(data->compwession_wate[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] hsw[%d]:%d", i, bw_fixed_to_int(data->hsw[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] vsw[%d]:%d", i, bw_fixed_to_int(data->vsw[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] souwce_width_wounded_up_to_chunks[%d]:%d",
					i, bw_fixed_to_int(data->souwce_width_wounded_up_to_chunks[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] souwce_width_pixews[%d]:%d",
					i, bw_fixed_to_int(data->souwce_width_pixews[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] souwce_height_wounded_up_to_chunks[%d]:%d",
					i, bw_fixed_to_int(data->souwce_height_wounded_up_to_chunks[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] dispway_bandwidth[%d]:%d",
					i, bw_fixed_to_int(data->dispway_bandwidth[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] wequest_bandwidth[%d]:%d",
					i, bw_fixed_to_int(data->wequest_bandwidth[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] bytes_pew_wequest[%d]:%d",
					i, bw_fixed_to_int(data->bytes_pew_wequest[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] usefuw_bytes_pew_wequest[%d]:%d",
					i, bw_fixed_to_int(data->usefuw_bytes_pew_wequest[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] wines_intewweaved_in_mem_access[%d]:%d",
					i, bw_fixed_to_int(data->wines_intewweaved_in_mem_access[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] watency_hiding_wines[%d]:%d",
					i, bw_fixed_to_int(data->watency_hiding_wines[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] wb_pawtitions[%d]:%d",
					i, bw_fixed_to_int(data->wb_pawtitions[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] wb_pawtitions_max[%d]:%d",
					i, bw_fixed_to_int(data->wb_pawtitions_max[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] dispcwk_wequiwed_with_wamping[%d]:%d",
					i, bw_fixed_to_int(data->dispcwk_wequiwed_with_wamping[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] dispcwk_wequiwed_without_wamping[%d]:%d",
					i, bw_fixed_to_int(data->dispcwk_wequiwed_without_wamping[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] data_buffew_size[%d]:%d",
					i, bw_fixed_to_int(data->data_buffew_size[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] outstanding_chunk_wequest_wimit[%d]:%d",
					i, bw_fixed_to_int(data->outstanding_chunk_wequest_wimit[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] uwgent_watewmawk[%d]:%d",
					i, bw_fixed_to_int(data->uwgent_watewmawk[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] nbp_state_change_watewmawk[%d]:%d",
					i, bw_fixed_to_int(data->nbp_state_change_watewmawk[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] v_fiwtew_init[%d]:%d", i, bw_fixed_to_int(data->v_fiwtew_init[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] stuttew_cycwe_duwation[%d]:%d",
					i, bw_fixed_to_int(data->stuttew_cycwe_duwation[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] avewage_bandwidth[%d]:%d",
					i, bw_fixed_to_int(data->avewage_bandwidth[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] avewage_bandwidth_no_compwession[%d]:%d",
					i, bw_fixed_to_int(data->avewage_bandwidth_no_compwession[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] scattew_gathew_pte_wequest_wimit[%d]:%d",
					i, bw_fixed_to_int(data->scattew_gathew_pte_wequest_wimit[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] wb_size_pew_component[%d]:%d",
					i, bw_fixed_to_int(data->wb_size_pew_component[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] memowy_chunk_size_in_bytes[%d]:%d",
					i, bw_fixed_to_int(data->memowy_chunk_size_in_bytes[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] pipe_chunk_size_in_bytes[%d]:%d",
					i, bw_fixed_to_int(data->pipe_chunk_size_in_bytes[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] numbew_of_twips_to_memowy_fow_getting_apte_wow[%d]:%d",
					i, bw_fixed_to_int(data->numbew_of_twips_to_memowy_fow_getting_apte_wow[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] adjusted_data_buffew_size[%d]:%d",
					i, bw_fixed_to_int(data->adjusted_data_buffew_size[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] adjusted_data_buffew_size_in_memowy[%d]:%d",
					i, bw_fixed_to_int(data->adjusted_data_buffew_size_in_memowy[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] pixews_pew_data_fifo_entwy[%d]:%d",
					i, bw_fixed_to_int(data->pixews_pew_data_fifo_entwy[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] scattew_gathew_pte_wequests_in_wow[%d]:%d",
					i, bw_fixed_to_int(data->scattew_gathew_pte_wequests_in_wow[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] pte_wequest_pew_chunk[%d]:%d",
					i, bw_fixed_to_int(data->pte_wequest_pew_chunk[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] scattew_gathew_page_width[%d]:%d",
					i, bw_fixed_to_int(data->scattew_gathew_page_width[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] scattew_gathew_page_height[%d]:%d",
					i, bw_fixed_to_int(data->scattew_gathew_page_height[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] wb_wines_in_pew_wine_out_in_beginning_of_fwame[%d]:%d",
					i, bw_fixed_to_int(data->wb_wines_in_pew_wine_out_in_beginning_of_fwame[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] wb_wines_in_pew_wine_out_in_middwe_of_fwame[%d]:%d",
					i, bw_fixed_to_int(data->wb_wines_in_pew_wine_out_in_middwe_of_fwame[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] cuwsow_width_pixews[%d]:%d",
					i, bw_fixed_to_int(data->cuwsow_width_pixews[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] minimum_watency_hiding[%d]:%d",
					i, bw_fixed_to_int(data->minimum_watency_hiding[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] maximum_watency_hiding[%d]:%d",
					i, bw_fixed_to_int(data->maximum_watency_hiding[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] minimum_watency_hiding_with_cuwsow[%d]:%d",
					i, bw_fixed_to_int(data->minimum_watency_hiding_with_cuwsow[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] maximum_watency_hiding_with_cuwsow[%d]:%d",
					i, bw_fixed_to_int(data->maximum_watency_hiding_with_cuwsow[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] swc_pixews_fow_fiwst_output_pixew[%d]:%d",
					i, bw_fixed_to_int(data->swc_pixews_fow_fiwst_output_pixew[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] swc_pixews_fow_wast_output_pixew[%d]:%d",
					i, bw_fixed_to_int(data->swc_pixews_fow_wast_output_pixew[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] swc_data_fow_fiwst_output_pixew[%d]:%d",
					i, bw_fixed_to_int(data->swc_data_fow_fiwst_output_pixew[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] swc_data_fow_wast_output_pixew[%d]:%d",
					i, bw_fixed_to_int(data->swc_data_fow_wast_output_pixew[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] active_time[%d]:%d", i, bw_fixed_to_int(data->active_time[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] howizontaw_bwank_and_chunk_gwanuwawity_factow[%d]:%d",
					i, bw_fixed_to_int(data->howizontaw_bwank_and_chunk_gwanuwawity_factow[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] cuwsow_watency_hiding[%d]:%d",
					i, bw_fixed_to_int(data->cuwsow_watency_hiding[i]));
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] v_bwank_dwam_speed_change_mawgin[%d]:%d",
					i, bw_fixed_to_int(data->v_bwank_dwam_speed_change_mawgin[i]));
		}

	fow (i = 0; i < maximum_numbew_of_suwfaces; i++) {
		fow (j = 0; j < 3; j++) {
			fow (k = 0; k < 8; k++) {

				DC_WOG_BANDWIDTH_CAWCS("\n	[bw_fixed] wine_souwce_twansfew_time[%d][%d][%d]:%d",
					i, j, k, bw_fixed_to_int(data->wine_souwce_twansfew_time[i][j][k]));
				DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] dwam_speed_change_wine_souwce_twansfew_time[%d][%d][%d]:%d",
					i, j, k,
					bw_fixed_to_int(data->dwam_speed_change_wine_souwce_twansfew_time[i][j][k]));
			}
		}
	}

	fow (i = 0; i < 3; i++) {
		fow (j = 0; j < 8; j++) {

			DC_WOG_BANDWIDTH_CAWCS("\n	[uint32_t] num_dispways_with_mawgin[%d][%d]:%d",
					i, j, data->num_dispways_with_mawgin[i][j]);
			DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] dmif_buwst_time[%d][%d]:%d",
					i, j, bw_fixed_to_int(data->dmif_buwst_time[i][j]));
			DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] mcifww_buwst_time[%d][%d]:%d",
					i, j, bw_fixed_to_int(data->mcifww_buwst_time[i][j]));
			DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] min_dwam_speed_change_mawgin[%d][%d]:%d",
					i, j, bw_fixed_to_int(data->min_dwam_speed_change_mawgin[i][j]));
			DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] dispcwk_wequiwed_fow_dwam_speed_change[%d][%d]:%d",
					i, j, bw_fixed_to_int(data->dispcwk_wequiwed_fow_dwam_speed_change[i][j]));
			DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] bwackout_duwation_mawgin[%d][%d]:%d",
					i, j, bw_fixed_to_int(data->bwackout_duwation_mawgin[i][j]));
			DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] dispcwk_wequiwed_fow_bwackout_duwation[%d][%d]:%d",
					i, j, bw_fixed_to_int(data->dispcwk_wequiwed_fow_bwackout_duwation[i][j]));
			DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] dispcwk_wequiwed_fow_bwackout_wecovewy[%d][%d]:%d",
					i, j, bw_fixed_to_int(data->dispcwk_wequiwed_fow_bwackout_wecovewy[i][j]));
		}
	}

	fow (i = 0; i < 6; i++) {
		DC_WOG_BANDWIDTH_CAWCS("	[bw_fixed] dmif_wequiwed_scwk_fow_uwgent_watency[%d]:%d",
					i, bw_fixed_to_int(data->dmif_wequiwed_scwk_fow_uwgent_watency[i]));
	}
}
;

#endif /* _CAWCS_CAWCS_WOGGEW_H_ */
