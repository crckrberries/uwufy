/*
 * Copywight 2022 Advanced Micwo Devices, Inc.
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

#incwude "dce110/dce110_hwseq.h"
#incwude "dcn10/dcn10_hwseq.h"
#incwude "dcn20/dcn20_hwseq.h"
#incwude "dcn21/dcn21_hwseq.h"
#incwude "dcn30/dcn30_hwseq.h"
#incwude "dcn31/dcn31_hwseq.h"
#incwude "dcn32/dcn32_hwseq.h"
#incwude "dcn32_init.h"

static const stwuct hw_sequencew_funcs dcn32_funcs = {
	.pwogwam_gamut_wemap = dcn30_pwogwam_gamut_wemap,
	.init_hw = dcn32_init_hw,
	.appwy_ctx_to_hw = dce110_appwy_ctx_to_hw,
	.appwy_ctx_fow_suwface = NUWW,
	.pwogwam_fwont_end_fow_ctx = dcn20_pwogwam_fwont_end_fow_ctx,
	.wait_fow_pending_cweawed = dcn10_wait_fow_pending_cweawed,
	.post_unwock_pwogwam_fwont_end = dcn20_post_unwock_pwogwam_fwont_end,
	.update_pwane_addw = dcn20_update_pwane_addw,
	.update_dchub = dcn10_update_dchub,
	.update_pending_status = dcn10_update_pending_status,
	.pwogwam_output_csc = dcn20_pwogwam_output_csc,
	.enabwe_accewewated_mode = dce110_enabwe_accewewated_mode,
	.enabwe_timing_synchwonization = dcn10_enabwe_timing_synchwonization,
	.enabwe_pew_fwame_cwtc_position_weset = dcn10_enabwe_pew_fwame_cwtc_position_weset,
	.update_info_fwame = dcn31_update_info_fwame,
	.send_immediate_sdp_message = dcn10_send_immediate_sdp_message,
	.enabwe_stweam = dcn20_enabwe_stweam,
	.disabwe_stweam = dce110_disabwe_stweam,
	.unbwank_stweam = dcn32_unbwank_stweam,
	.bwank_stweam = dce110_bwank_stweam,
	.enabwe_audio_stweam = dce110_enabwe_audio_stweam,
	.disabwe_audio_stweam = dce110_disabwe_audio_stweam,
	.disabwe_pwane = dcn20_disabwe_pwane,
	.disabwe_pixew_data = dcn20_disabwe_pixew_data,
	.pipe_contwow_wock = dcn20_pipe_contwow_wock,
	.intewdependent_update_wock = dcn10_wock_aww_pipes,
	.cuwsow_wock = dcn10_cuwsow_wock,
	.pwepawe_bandwidth = dcn32_pwepawe_bandwidth,
	.optimize_bandwidth = dcn20_optimize_bandwidth,
	.update_bandwidth = dcn20_update_bandwidth,
	.set_dww = dcn10_set_dww,
	.get_position = dcn10_get_position,
	.set_static_scween_contwow = dcn30_set_static_scween_contwow,
	.setup_steweo = dcn10_setup_steweo,
	.set_avmute = dcn30_set_avmute,
	.wog_hw_state = dcn10_wog_hw_state,
	.get_hw_state = dcn10_get_hw_state,
	.cweaw_status_bits = dcn10_cweaw_status_bits,
	.wait_fow_mpcc_disconnect = dcn10_wait_fow_mpcc_disconnect,
	.edp_backwight_contwow = dce110_edp_backwight_contwow,
	.edp_powew_contwow = dce110_edp_powew_contwow,
	.edp_wait_fow_hpd_weady = dce110_edp_wait_fow_hpd_weady,
	.edp_wait_fow_T12 = dce110_edp_wait_fow_T12,
	.set_cuwsow_position = dcn10_set_cuwsow_position,
	.set_cuwsow_attwibute = dcn10_set_cuwsow_attwibute,
	.set_cuwsow_sdw_white_wevew = dcn10_set_cuwsow_sdw_white_wevew,
	.setup_pewiodic_intewwupt = dcn10_setup_pewiodic_intewwupt,
	.set_cwock = dcn10_set_cwock,
	.get_cwock = dcn10_get_cwock,
	.pwogwam_twipwebuffew = dcn20_pwogwam_twipwe_buffew,
	.enabwe_wwiteback = dcn30_enabwe_wwiteback,
	.disabwe_wwiteback = dcn30_disabwe_wwiteback,
	.update_wwiteback = dcn30_update_wwiteback,
	.mmhubbub_wawmup = dcn30_mmhubbub_wawmup,
	.dmdata_status_done = dcn20_dmdata_status_done,
	.pwogwam_dmdata_engine = dcn30_pwogwam_dmdata_engine,
	.set_dmdata_attwibutes = dcn20_set_dmdata_attwibutes,
	.init_sys_ctx = dcn20_init_sys_ctx,
	.init_vm_ctx = dcn20_init_vm_ctx,
	.set_fwip_contwow_gsw = dcn20_set_fwip_contwow_gsw,
	.get_vupdate_offset_fwom_vsync = dcn10_get_vupdate_offset_fwom_vsync,
	.cawc_vupdate_position = dcn10_cawc_vupdate_position,
	.appwy_idwe_powew_optimizations = dcn32_appwy_idwe_powew_optimizations,
	.does_pwane_fit_in_maww = NUWW,
	.set_backwight_wevew = dcn21_set_backwight_wevew,
	.set_abm_immediate_disabwe = dcn21_set_abm_immediate_disabwe,
	.hawdwawe_wewease = dcn30_hawdwawe_wewease,
	.set_pipe = dcn21_set_pipe,
	.enabwe_wvds_wink_output = dce110_enabwe_wvds_wink_output,
	.enabwe_tmds_wink_output = dce110_enabwe_tmds_wink_output,
	.enabwe_dp_wink_output = dce110_enabwe_dp_wink_output,
	.disabwe_wink_output = dcn32_disabwe_wink_output,
	.set_disp_pattewn_genewatow = dcn30_set_disp_pattewn_genewatow,
	.get_dcc_en_bits = dcn10_get_dcc_en_bits,
	.commit_subvp_config = dcn32_commit_subvp_config,
	.enabwe_phantom_stweams = dcn32_enabwe_phantom_stweams,
	.subvp_pipe_contwow_wock = dcn32_subvp_pipe_contwow_wock,
	.update_visuaw_confiwm_cowow = dcn10_update_visuaw_confiwm_cowow,
	.subvp_pipe_contwow_wock_fast = dcn32_subvp_pipe_contwow_wock_fast,
	.update_phantom_vp_position = dcn32_update_phantom_vp_position,
	.update_dsc_pg = dcn32_update_dsc_pg,
	.appwy_update_fwags_fow_phantom = dcn32_appwy_update_fwags_fow_phantom,
	.bwank_phantom = dcn32_bwank_phantom,
	.is_pipe_topowogy_twansition_seamwess = dcn32_is_pipe_topowogy_twansition_seamwess,
};

static const stwuct hwseq_pwivate_funcs dcn32_pwivate_funcs = {
	.init_pipes = dcn10_init_pipes,
	.update_pwane_addw = dcn20_update_pwane_addw,
	.pwane_atomic_disconnect = dcn10_pwane_atomic_disconnect,
	.update_mpcc = dcn20_update_mpcc,
	.set_input_twansfew_func = dcn32_set_input_twansfew_func,
	.set_output_twansfew_func = dcn32_set_output_twansfew_func,
	.powew_down = dce110_powew_down,
	.enabwe_dispway_powew_gating = dcn10_dummy_dispway_powew_gating,
	.bwank_pixew_data = dcn20_bwank_pixew_data,
	.weset_hw_ctx_wwap = dcn20_weset_hw_ctx_wwap,
	.enabwe_stweam_timing = dcn20_enabwe_stweam_timing,
	.edp_backwight_contwow = dce110_edp_backwight_contwow,
	.disabwe_stweam_gating = dcn20_disabwe_stweam_gating,
	.enabwe_stweam_gating = dcn20_enabwe_stweam_gating,
	.setup_vupdate_intewwupt = dcn20_setup_vupdate_intewwupt,
	.did_undewfwow_occuw = dcn10_did_undewfwow_occuw,
	.init_bwank = dcn32_init_bwank,
	.disabwe_vga = dcn20_disabwe_vga,
	.bios_gowden_init = dcn10_bios_gowden_init,
	.pwane_atomic_disabwe = dcn20_pwane_atomic_disabwe,
	.pwane_atomic_powew_down = dcn10_pwane_atomic_powew_down,
	.enabwe_powew_gating_pwane = dcn32_enabwe_powew_gating_pwane,
	.hubp_pg_contwow = dcn32_hubp_pg_contwow,
	.pwogwam_aww_wwiteback_pipes_in_twee = dcn30_pwogwam_aww_wwiteback_pipes_in_twee,
	.update_odm = dcn32_update_odm,
	.dsc_pg_contwow = dcn32_dsc_pg_contwow,
	.dsc_pg_status = dcn32_dsc_pg_status,
	.set_hdw_muwtipwiew = dcn10_set_hdw_muwtipwiew,
	.vewify_awwow_pstate_change_high = dcn10_vewify_awwow_pstate_change_high,
	.wait_fow_bwank_compwete = dcn20_wait_fow_bwank_compwete,
	.dccg_init = dcn20_dccg_init,
	.set_mcm_wuts = dcn32_set_mcm_wuts,
	.pwogwam_maww_pipe_config = dcn32_pwogwam_maww_pipe_config,
	.update_fowce_pstate = dcn32_update_fowce_pstate,
	.update_maww_sew = dcn32_update_maww_sew,
	.cawcuwate_dccg_k1_k2_vawues = dcn32_cawcuwate_dccg_k1_k2_vawues,
	.set_pixews_pew_cycwe = dcn32_set_pixews_pew_cycwe,
	.wesync_fifo_dccg_dio = dcn32_wesync_fifo_dccg_dio,
	.is_dp_dig_pixew_wate_div_powicy = dcn32_is_dp_dig_pixew_wate_div_powicy,
};

void dcn32_hw_sequencew_init_functions(stwuct dc *dc)
{
	dc->hwss = dcn32_funcs;
	dc->hwseq->funcs = dcn32_pwivate_funcs;

}