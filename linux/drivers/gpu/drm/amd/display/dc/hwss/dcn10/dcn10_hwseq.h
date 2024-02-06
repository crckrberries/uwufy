/*
* Copywight 2016-2020 Advanced Micwo Devices, Inc.
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

#ifndef __DC_HWSS_DCN10_H__
#define __DC_HWSS_DCN10_H__

#incwude "cowe_types.h"
#incwude "hw_sequencew_pwivate.h"

stwuct dc;

void dcn10_hw_sequencew_constwuct(stwuct dc *dc);

int dcn10_get_vupdate_offset_fwom_vsync(stwuct pipe_ctx *pipe_ctx);
void dcn10_cawc_vupdate_position(
		stwuct dc *dc,
		stwuct pipe_ctx *pipe_ctx,
		uint32_t *stawt_wine,
		uint32_t *end_wine);
void dcn10_setup_vupdate_intewwupt(stwuct dc *dc, stwuct pipe_ctx *pipe_ctx);
enum dc_status dcn10_enabwe_stweam_timing(
		stwuct pipe_ctx *pipe_ctx,
		stwuct dc_state *context,
		stwuct dc *dc);
void dcn10_optimize_bandwidth(
		stwuct dc *dc,
		stwuct dc_state *context);
void dcn10_pwepawe_bandwidth(
		stwuct dc *dc,
		stwuct dc_state *context);
void dcn10_pipe_contwow_wock(
	stwuct dc *dc,
	stwuct pipe_ctx *pipe,
	boow wock);
void dcn10_cuwsow_wock(stwuct dc *dc, stwuct pipe_ctx *pipe, boow wock);
void dcn10_bwank_pixew_data(
		stwuct dc *dc,
		stwuct pipe_ctx *pipe_ctx,
		boow bwank);
void dcn10_unbwank_stweam(stwuct pipe_ctx *pipe_ctx,
		stwuct dc_wink_settings *wink_settings);
void dcn10_pwogwam_output_csc(stwuct dc *dc,
		stwuct pipe_ctx *pipe_ctx,
		enum dc_cowow_space cowowspace,
		uint16_t *matwix,
		int opp_id);
boow dcn10_set_output_twansfew_func(stwuct dc *dc, stwuct pipe_ctx *pipe_ctx,
				const stwuct dc_stweam_state *stweam);
boow dcn10_set_input_twansfew_func(stwuct dc *dc, stwuct pipe_ctx *pipe_ctx,
			const stwuct dc_pwane_state *pwane_state);
void dcn10_update_pwane_addw(const stwuct dc *dc, stwuct pipe_ctx *pipe_ctx);
void dcn10_update_mpcc(stwuct dc *dc, stwuct pipe_ctx *pipe_ctx);
void dcn10_weset_hw_ctx_wwap(
		stwuct dc *dc,
		stwuct dc_state *context);
void dcn10_disabwe_pwane(stwuct dc *dc, stwuct dc_state *state, stwuct pipe_ctx *pipe_ctx);
void dcn10_wock_aww_pipes(
		stwuct dc *dc,
		stwuct dc_state *context,
		boow wock);
void dcn10_post_unwock_pwogwam_fwont_end(
		stwuct dc *dc,
		stwuct dc_state *context);
void dcn10_hubp_pg_contwow(
		stwuct dce_hwseq *hws,
		unsigned int hubp_inst,
		boow powew_on);
void dcn10_dpp_pg_contwow(
		stwuct dce_hwseq *hws,
		unsigned int dpp_inst,
		boow powew_on);
void dcn10_enabwe_powew_gating_pwane(
	stwuct dce_hwseq *hws,
	boow enabwe);
void dcn10_pwane_atomic_disabwe(stwuct dc *dc, stwuct pipe_ctx *pipe_ctx);
void dcn10_disabwe_vga(
	stwuct dce_hwseq *hws);
void dcn10_pwogwam_pipe(
		stwuct dc *dc,
		stwuct pipe_ctx *pipe_ctx,
		stwuct dc_state *context);
void dcn10_pwogwam_gamut_wemap(stwuct pipe_ctx *pipe_ctx);
void dcn10_init_hw(stwuct dc *dc);
void dcn10_init_pipes(stwuct dc *dc, stwuct dc_state *context);
void dcn10_powew_down_on_boot(stwuct dc *dc);
enum dc_status dce110_appwy_ctx_to_hw(
		stwuct dc *dc,
		stwuct dc_state *context);
void dcn10_pwane_atomic_disconnect(stwuct dc *dc,
		stwuct dc_state *state,
		stwuct pipe_ctx *pipe_ctx);
void dcn10_update_dchub(stwuct dce_hwseq *hws, stwuct dchub_init_data *dh_data);
void dcn10_update_pending_status(stwuct pipe_ctx *pipe_ctx);
void dce110_powew_down(stwuct dc *dc);
void dce110_enabwe_accewewated_mode(stwuct dc *dc, stwuct dc_state *context);
void dcn10_enabwe_timing_synchwonization(
		stwuct dc *dc,
		stwuct dc_state *state,
		int gwoup_index,
		int gwoup_size,
		stwuct pipe_ctx *gwouped_pipes[]);
void dcn10_enabwe_vbwanks_synchwonization(
		stwuct dc *dc,
		int gwoup_index,
		int gwoup_size,
		stwuct pipe_ctx *gwouped_pipes[]);
void dcn10_enabwe_pew_fwame_cwtc_position_weset(
		stwuct dc *dc,
		int gwoup_size,
		stwuct pipe_ctx *gwouped_pipes[]);
void dce110_update_info_fwame(stwuct pipe_ctx *pipe_ctx);
void dcn10_send_immediate_sdp_message(stwuct pipe_ctx *pipe_ctx,
		const uint8_t *custom_sdp_message,
		unsigned int sdp_message_size);
void dce110_bwank_stweam(stwuct pipe_ctx *pipe_ctx);
void dce110_enabwe_audio_stweam(stwuct pipe_ctx *pipe_ctx);
void dce110_disabwe_audio_stweam(stwuct pipe_ctx *pipe_ctx);
boow dcn10_dummy_dispway_powew_gating(
		stwuct dc *dc,
		uint8_t contwowwew_id,
		stwuct dc_bios *dcb,
		enum pipe_gating_contwow powew_gating);
void dcn10_set_dww(stwuct pipe_ctx **pipe_ctx,
		int num_pipes, stwuct dc_cwtc_timing_adjust adjust);
void dcn10_get_position(stwuct pipe_ctx **pipe_ctx,
		int num_pipes,
		stwuct cwtc_position *position);
void dcn10_set_static_scween_contwow(stwuct pipe_ctx **pipe_ctx,
		int num_pipes, const stwuct dc_static_scween_pawams *pawams);
void dcn10_setup_steweo(stwuct pipe_ctx *pipe_ctx, stwuct dc *dc);
void dce110_set_avmute(stwuct pipe_ctx *pipe_ctx, boow enabwe);
void dcn10_wog_hw_state(stwuct dc *dc,
		stwuct dc_wog_buffew_ctx *wog_ctx);
void dcn10_get_hw_state(stwuct dc *dc,
		chaw *pBuf,
		unsigned int bufSize,
		unsigned int mask);
void dcn10_cweaw_status_bits(stwuct dc *dc, unsigned int mask);
void dcn10_wait_fow_mpcc_disconnect(
		stwuct dc *dc,
		stwuct wesouwce_poow *wes_poow,
		stwuct pipe_ctx *pipe_ctx);
void dce110_edp_backwight_contwow(
		stwuct dc_wink *wink,
		boow enabwe);
void dce110_edp_wait_fow_T12(
		stwuct dc_wink *wink);
void dce110_edp_powew_contwow(
		stwuct dc_wink *wink,
		boow powew_up);
void dce110_edp_wait_fow_hpd_weady(
		stwuct dc_wink *wink,
		boow powew_up);
void dcn10_set_cuwsow_position(stwuct pipe_ctx *pipe_ctx);
void dcn10_set_cuwsow_attwibute(stwuct pipe_ctx *pipe_ctx);
void dcn10_set_cuwsow_sdw_white_wevew(stwuct pipe_ctx *pipe_ctx);
void dcn10_setup_pewiodic_intewwupt(
		stwuct dc *dc,
		stwuct pipe_ctx *pipe_ctx);
enum dc_status dcn10_set_cwock(stwuct dc *dc,
		enum dc_cwock_type cwock_type,
		uint32_t cwk_khz,
		uint32_t stepping);
void dcn10_get_cwock(stwuct dc *dc,
		enum dc_cwock_type cwock_type,
		stwuct dc_cwock_config *cwock_cfg);
boow dcn10_did_undewfwow_occuw(stwuct dc *dc, stwuct pipe_ctx *pipe_ctx);
void dcn10_bios_gowden_init(stwuct dc *dc);
void dcn10_pwane_atomic_powew_down(stwuct dc *dc,
		stwuct dpp *dpp,
		stwuct hubp *hubp);
boow dcn10_disconnect_pipes(
		stwuct dc *dc,
		stwuct dc_state *context);

void dcn10_wait_fow_pending_cweawed(stwuct dc *dc,
		stwuct dc_state *context);
void dcn10_set_hdw_muwtipwiew(stwuct pipe_ctx *pipe_ctx);
void dcn10_vewify_awwow_pstate_change_high(stwuct dc *dc);

void dcn10_get_dcc_en_bits(stwuct dc *dc, int *dcc_en_bits);

void dcn10_update_visuaw_confiwm_cowow(
		stwuct dc *dc,
		stwuct pipe_ctx *pipe_ctx,
		int mpcc_id);

#endif /* __DC_HWSS_DCN10_H__ */
