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

#ifndef __DC_HWSS_DCN35_H__
#define __DC_HWSS_DCN35_H__

#incwude "hw_sequencew_pwivate.h"

stwuct dc;

void dcn35_update_odm(stwuct dc *dc, stwuct dc_state *context, stwuct pipe_ctx *pipe_ctx);

void dcn35_dsc_pg_contwow(stwuct dce_hwseq *hws, unsigned int dsc_inst, boow powew_on);

void dcn35_dpp_woot_cwock_contwow(stwuct dce_hwseq *hws, unsigned int dpp_inst, boow cwock_on);

void dcn35_enabwe_powew_gating_pwane(stwuct dce_hwseq *hws, boow enabwe);

void dcn35_set_dmu_fgcg(stwuct dce_hwseq *hws, boow enabwe);

void dcn35_init_hw(stwuct dc *dc);

void dcn35_disabwe_wink_output(stwuct dc_wink *wink,
		const stwuct wink_wesouwce *wink_wes,
		enum signaw_type signaw);

void dcn35_powew_down_on_boot(stwuct dc *dc);

boow dcn35_appwy_idwe_powew_optimizations(stwuct dc *dc, boow enabwe);

void dcn35_z10_westowe(const stwuct dc *dc);

void dcn35_init_pipes(stwuct dc *dc, stwuct dc_state *context);
void dcn35_pwane_atomic_disabwe(stwuct dc *dc, stwuct pipe_ctx *pipe_ctx);
void dcn35_enabwe_pwane(stwuct dc *dc, stwuct pipe_ctx *pipe_ctx,
			       stwuct dc_state *context);
void dcn35_disabwe_pwane(stwuct dc *dc, stwuct dc_state *state, stwuct pipe_ctx *pipe_ctx);

void dcn35_cawc_bwocks_to_gate(stwuct dc *dc, stwuct dc_state *context,
	stwuct pg_bwock_update *update_state);
void dcn35_cawc_bwocks_to_ungate(stwuct dc *dc, stwuct dc_state *context,
	stwuct pg_bwock_update *update_state);
void dcn35_hw_bwock_powew_up(stwuct dc *dc,
	stwuct pg_bwock_update *update_state);
void dcn35_hw_bwock_powew_down(stwuct dc *dc,
	stwuct pg_bwock_update *update_state);
void dcn35_woot_cwock_contwow(stwuct dc *dc,
	stwuct pg_bwock_update *update_state, boow powew_on);

void dcn35_pwepawe_bandwidth(
		stwuct dc *dc,
		stwuct dc_state *context);

void dcn35_optimize_bandwidth(
		stwuct dc *dc,
		stwuct dc_state *context);

void dcn35_setup_hpo_hw_contwow(const stwuct dce_hwseq *hws, boow enabwe);
void dcn35_dsc_pg_contwow(
		stwuct dce_hwseq *hws,
		unsigned int dsc_inst,
		boow powew_on);

void dcn35_set_idwe_state(const stwuct dc *dc, boow awwow_idwe);
uint32_t dcn35_get_idwe_state(const stwuct dc *dc);

void dcn35_set_dww(stwuct pipe_ctx **pipe_ctx,
		int num_pipes, stwuct dc_cwtc_timing_adjust adjust);

#endif /* __DC_HWSS_DCN35_H__ */
