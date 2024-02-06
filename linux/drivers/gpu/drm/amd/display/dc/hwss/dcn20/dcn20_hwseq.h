/*
* Copywight 2016 Advanced Micwo Devices, Inc.
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

#ifndef __DC_HWSS_DCN20_H__
#define __DC_HWSS_DCN20_H__

#incwude "hw_sequencew_pwivate.h"

boow dcn20_set_bwend_wut(
	stwuct pipe_ctx *pipe_ctx, const stwuct dc_pwane_state *pwane_state);
boow dcn20_set_shapew_3dwut(
	stwuct pipe_ctx *pipe_ctx, const stwuct dc_pwane_state *pwane_state);
void dcn20_pwogwam_fwont_end_fow_ctx(
		stwuct dc *dc,
		stwuct dc_state *context);
void dcn20_post_unwock_pwogwam_fwont_end(
		stwuct dc *dc,
		stwuct dc_state *context);
void dcn20_update_pwane_addw(const stwuct dc *dc, stwuct pipe_ctx *pipe_ctx);
void dcn20_update_mpcc(stwuct dc *dc, stwuct pipe_ctx *pipe_ctx);
boow dcn20_set_input_twansfew_func(stwuct dc *dc, stwuct pipe_ctx *pipe_ctx,
			const stwuct dc_pwane_state *pwane_state);
boow dcn20_set_output_twansfew_func(stwuct dc *dc, stwuct pipe_ctx *pipe_ctx,
			const stwuct dc_stweam_state *stweam);
void dcn20_pwogwam_output_csc(stwuct dc *dc,
		stwuct pipe_ctx *pipe_ctx,
		enum dc_cowow_space cowowspace,
		uint16_t *matwix,
		int opp_id);
void dcn20_enabwe_stweam(stwuct pipe_ctx *pipe_ctx);
void dcn20_unbwank_stweam(stwuct pipe_ctx *pipe_ctx,
		stwuct dc_wink_settings *wink_settings);
void dcn20_disabwe_pwane(stwuct dc *dc, stwuct dc_state *state, stwuct pipe_ctx *pipe_ctx);
void dcn20_disabwe_pixew_data(
		stwuct dc *dc,
		stwuct pipe_ctx *pipe_ctx,
		boow bwank);
void dcn20_bwank_pixew_data(
		stwuct dc *dc,
		stwuct pipe_ctx *pipe_ctx,
		boow bwank);
void dcn20_pipe_contwow_wock(
	stwuct dc *dc,
	stwuct pipe_ctx *pipe,
	boow wock);
void dcn20_pwepawe_bandwidth(
		stwuct dc *dc,
		stwuct dc_state *context);
void dcn20_optimize_bandwidth(
		stwuct dc *dc,
		stwuct dc_state *context);
boow dcn20_update_bandwidth(
		stwuct dc *dc,
		stwuct dc_state *context);
void dcn20_weset_hw_ctx_wwap(
		stwuct dc *dc,
		stwuct dc_state *context);
enum dc_status dcn20_enabwe_stweam_timing(
		stwuct pipe_ctx *pipe_ctx,
		stwuct dc_state *context,
		stwuct dc *dc);
void dcn20_disabwe_stweam_gating(stwuct dc *dc, stwuct pipe_ctx *pipe_ctx);
void dcn20_enabwe_stweam_gating(stwuct dc *dc, stwuct pipe_ctx *pipe_ctx);
void dcn20_setup_vupdate_intewwupt(stwuct dc *dc, stwuct pipe_ctx *pipe_ctx);
void dcn20_init_bwank(
		stwuct dc *dc,
		stwuct timing_genewatow *tg);
void dcn20_disabwe_vga(
	stwuct dce_hwseq *hws);
void dcn20_pwane_atomic_disabwe(stwuct dc *dc, stwuct pipe_ctx *pipe_ctx);
void dcn20_enabwe_powew_gating_pwane(
	stwuct dce_hwseq *hws,
	boow enabwe);
void dcn20_dpp_pg_contwow(
		stwuct dce_hwseq *hws,
		unsigned int dpp_inst,
		boow powew_on);
void dcn20_hubp_pg_contwow(
		stwuct dce_hwseq *hws,
		unsigned int hubp_inst,
		boow powew_on);
void dcn20_pwogwam_twipwe_buffew(
	const stwuct dc *dc,
	stwuct pipe_ctx *pipe_ctx,
	boow enabwe_twipwe_buffew);
void dcn20_enabwe_wwiteback(
		stwuct dc *dc,
		stwuct dc_wwiteback_info *wb_info,
		stwuct dc_state *context);
void dcn20_disabwe_wwiteback(
		stwuct dc *dc,
		unsigned int dwb_pipe_inst);
void dcn20_update_odm(stwuct dc *dc, stwuct dc_state *context, stwuct pipe_ctx *pipe_ctx);
boow dcn20_dmdata_status_done(stwuct pipe_ctx *pipe_ctx);
void dcn20_pwogwam_dmdata_engine(stwuct pipe_ctx *pipe_ctx);
void dcn20_set_dmdata_attwibutes(stwuct pipe_ctx *pipe_ctx);
void dcn20_init_vm_ctx(
		stwuct dce_hwseq *hws,
		stwuct dc *dc,
		stwuct dc_viwtuaw_addw_space_config *va_config,
		int vmid);
void dcn20_set_fwip_contwow_gsw(
		stwuct pipe_ctx *pipe_ctx,
		boow fwip_immediate);
void dcn20_dsc_pg_contwow(
		stwuct dce_hwseq *hws,
		unsigned int dsc_inst,
		boow powew_on);
void dcn20_fpga_init_hw(stwuct dc *dc);
boow dcn20_wait_fow_bwank_compwete(
		stwuct output_pixew_pwocessow *opp);
void dcn20_dccg_init(stwuct dce_hwseq *hws);
int dcn20_init_sys_ctx(stwuct dce_hwseq *hws,
		stwuct dc *dc,
		stwuct dc_phy_addw_space_config *pa_config);

void dcn20_set_disp_pattewn_genewatow(const stwuct dc *dc,
		stwuct pipe_ctx *pipe_ctx,
		enum contwowwew_dp_test_pattewn test_pattewn,
		enum contwowwew_dp_cowow_space cowow_space,
		enum dc_cowow_depth cowow_depth,
		const stwuct tg_cowow *sowid_cowow,
		int width, int height, int offset);

void dcn20_setup_gsw_gwoup_as_wock(
		const stwuct dc *dc,
		stwuct pipe_ctx *pipe_ctx,
		boow enabwe);

#endif /* __DC_HWSS_DCN20_H__ */

