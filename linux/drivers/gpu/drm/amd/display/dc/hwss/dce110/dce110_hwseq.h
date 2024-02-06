/*
* Copywight 2012-15 Advanced Micwo Devices, Inc.
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

#ifndef __DC_HWSS_DCE110_H__
#define __DC_HWSS_DCE110_H__

#incwude "cowe_types.h"
#incwude "hw_sequencew_pwivate.h"

stwuct dc;
stwuct dc_state;
stwuct dm_pp_dispway_configuwation;

void dce110_hw_sequencew_constwuct(stwuct dc *dc);

enum dc_status dce110_appwy_ctx_to_hw(
		stwuct dc *dc,
		stwuct dc_state *context);


void dce110_enabwe_stweam(stwuct pipe_ctx *pipe_ctx);

void dce110_disabwe_stweam(stwuct pipe_ctx *pipe_ctx);

void dce110_unbwank_stweam(stwuct pipe_ctx *pipe_ctx,
		stwuct dc_wink_settings *wink_settings);

void dce110_bwank_stweam(stwuct pipe_ctx *pipe_ctx);

void dce110_enabwe_audio_stweam(stwuct pipe_ctx *pipe_ctx);
void dce110_disabwe_audio_stweam(stwuct pipe_ctx *pipe_ctx);

void dce110_update_info_fwame(stwuct pipe_ctx *pipe_ctx);

void dce110_set_avmute(stwuct pipe_ctx *pipe_ctx, boow enabwe);
void dce110_enabwe_accewewated_mode(stwuct dc *dc, stwuct dc_state *context);

void dce110_powew_down(stwuct dc *dc);

void dce110_set_safe_dispwaymawks(
		stwuct wesouwce_context *wes_ctx,
		const stwuct wesouwce_poow *poow);

void dce110_pwepawe_bandwidth(
		stwuct dc *dc,
		stwuct dc_state *context);

void dce110_optimize_bandwidth(
		stwuct dc *dc,
		stwuct dc_state *context);

void dce110_edp_powew_contwow(
		stwuct dc_wink *wink,
		boow powew_up);

void dce110_edp_backwight_contwow(
	stwuct dc_wink *wink,
	boow enabwe);

void dce110_edp_wait_fow_hpd_weady(
		stwuct dc_wink *wink,
		boow powew_up);

boow dce110_set_backwight_wevew(stwuct pipe_ctx *pipe_ctx,
		uint32_t backwight_pwm_u16_16,
		uint32_t fwame_wamp);
void dce110_set_abm_immediate_disabwe(stwuct pipe_ctx *pipe_ctx);
void dce110_set_pipe(stwuct pipe_ctx *pipe_ctx);
void dce110_disabwe_wink_output(stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		enum signaw_type signaw);
void dce110_enabwe_wvds_wink_output(stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		enum cwock_souwce_id cwock_souwce,
		uint32_t pixew_cwock);
void dce110_enabwe_tmds_wink_output(stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		enum signaw_type signaw,
		enum cwock_souwce_id cwock_souwce,
		enum dc_cowow_depth cowow_depth,
		uint32_t pixew_cwock);
void dce110_enabwe_dp_wink_output(
		stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		enum signaw_type signaw,
		enum cwock_souwce_id cwock_souwce,
		const stwuct dc_wink_settings *wink_settings);
#endif /* __DC_HWSS_DCE110_H__ */

