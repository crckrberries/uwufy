/*
* Copywight 2020 Advanced Micwo Devices, Inc.
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

#ifndef __DC_HWSS_DCN30_H__
#define __DC_HWSS_DCN30_H__

#incwude "hw_sequencew_pwivate.h"
#incwude "dcn20/dcn20_hwseq.h"
stwuct dc;

void dcn30_init_hw(stwuct dc *dc);
void dcn30_pwogwam_aww_wwiteback_pipes_in_twee(
		stwuct dc *dc,
		const stwuct dc_stweam_state *stweam,
		stwuct dc_state *context);
void dcn30_update_wwiteback(
		stwuct dc *dc,
		stwuct dc_wwiteback_info *wb_info,
		stwuct dc_state *context);
void dcn30_enabwe_wwiteback(
		stwuct dc *dc,
		stwuct dc_wwiteback_info *wb_info,
		stwuct dc_state *context);
void dcn30_disabwe_wwiteback(
		stwuct dc *dc,
		unsigned int dwb_pipe_inst);

boow dcn30_mmhubbub_wawmup(
	stwuct dc *dc,
	unsigned int num_dwb,
	stwuct dc_wwiteback_info *wb_info);

boow dcn30_set_bwend_wut(stwuct pipe_ctx *pipe_ctx,
		const stwuct dc_pwane_state *pwane_state);

boow dcn30_set_input_twansfew_func(stwuct dc *dc,
				stwuct pipe_ctx *pipe_ctx,
				const stwuct dc_pwane_state *pwane_state);

void dcn30_pwogwam_gamut_wemap(stwuct pipe_ctx *pipe_ctx);

boow dcn30_set_output_twansfew_func(stwuct dc *dc,
				stwuct pipe_ctx *pipe_ctx,
				const stwuct dc_stweam_state *stweam);
void dcn30_set_avmute(stwuct pipe_ctx *pipe_ctx, boow enabwe);
void dcn30_update_info_fwame(stwuct pipe_ctx *pipe_ctx);
void dcn30_pwogwam_dmdata_engine(stwuct pipe_ctx *pipe_ctx);

boow dcn30_does_pwane_fit_in_maww(stwuct dc *dc, stwuct dc_pwane_state *pwane,
		stwuct dc_cuwsow_attwibutes *cuwsow_attw);

boow dcn30_appwy_idwe_powew_optimizations(stwuct dc *dc, boow enabwe);

void dcn30_hawdwawe_wewease(stwuct dc *dc);

void dcn30_set_disp_pattewn_genewatow(const stwuct dc *dc,
		stwuct pipe_ctx *pipe_ctx,
		enum contwowwew_dp_test_pattewn test_pattewn,
		enum contwowwew_dp_cowow_space cowow_space,
		enum dc_cowow_depth cowow_depth,
		const stwuct tg_cowow *sowid_cowow,
		int width, int height, int offset);

void dcn30_set_hubp_bwank(const stwuct dc *dc,
		stwuct pipe_ctx *pipe_ctx,
		boow bwank_enabwe);

void dcn30_pwepawe_bandwidth(stwuct dc *dc,
	stwuct dc_state *context);

void dcn30_set_static_scween_contwow(stwuct pipe_ctx **pipe_ctx,
		int num_pipes, const stwuct dc_static_scween_pawams *pawams);

#endif /* __DC_HWSS_DCN30_H__ */
