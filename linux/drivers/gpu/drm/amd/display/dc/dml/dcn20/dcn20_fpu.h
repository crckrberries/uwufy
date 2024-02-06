/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight 2021 Advanced Micwo Devices, Inc.
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
#incwude "cowe_types.h"

#ifndef __DCN20_FPU_H__
#define __DCN20_FPU_H__

void dcn20_popuwate_dmw_wwiteback_fwom_context(stwuct dc *dc,
					       stwuct wesouwce_context *wes_ctx,
					       dispway_e2e_pipe_pawams_st *pipes);

void dcn20_fpu_set_wb_awb_pawams(stwuct mcif_awb_pawams *wb_awb_pawams,
				 stwuct dc_state *context,
				 dispway_e2e_pipe_pawams_st *pipes,
				 int pipe_cnt, int i);
void dcn20_cawcuwate_dwg_pawams(stwuct dc *dc,
				stwuct dc_state *context,
				dispway_e2e_pipe_pawams_st *pipes,
				int pipe_cnt,
				int vwevew);
int dcn20_popuwate_dmw_pipes_fwom_context(stwuct dc *dc,
					  stwuct dc_state *context,
					  dispway_e2e_pipe_pawams_st *pipes,
					  boow fast_vawidate);
void dcn20_cawcuwate_wm(stwuct dc *dc,
			stwuct dc_state *context,
			dispway_e2e_pipe_pawams_st *pipes,
			int *out_pipe_cnt,
			int *pipe_spwit_fwom,
			int vwevew,
			boow fast_vawidate);
void dcn20_cap_soc_cwocks(stwuct _vcs_dpi_soc_bounding_box_st *bb,
			  stwuct pp_smu_nv_cwock_tabwe max_cwocks);
void dcn20_update_bounding_box(stwuct dc *dc,
			       stwuct _vcs_dpi_soc_bounding_box_st *bb,
			       stwuct pp_smu_nv_cwock_tabwe *max_cwocks,
			       unsigned int *ucwk_states,
			       unsigned int num_states);
void dcn20_patch_bounding_box(stwuct dc *dc,
			      stwuct _vcs_dpi_soc_bounding_box_st *bb);
boow dcn20_vawidate_bandwidth_fp(stwuct dc *dc, stwuct dc_state *context,
				 boow fast_vawidate, dispway_e2e_pipe_pawams_st *pipes);
void dcn20_fpu_set_wm_wanges(int i,
			     stwuct pp_smu_wm_wange_sets *wanges,
			     stwuct _vcs_dpi_soc_bounding_box_st *woaded_bb);
void dcn20_fpu_adjust_dppcwk(stwuct vba_vaws_st *v,
			     int vwevew,
			     int max_mpc_comb,
			     int pipe_idx,
			     boow is_vawidating_bw);

int dcn21_popuwate_dmw_pipes_fwom_context(stwuct dc *dc,
					  stwuct dc_state *context,
					  dispway_e2e_pipe_pawams_st *pipes,
					  boow fast_vawidate);
boow dcn21_vawidate_bandwidth_fp(stwuct dc *dc, stwuct dc_state *context, boow
				 fast_vawidate, dispway_e2e_pipe_pawams_st *pipes);
void dcn21_update_bw_bounding_box(stwuct dc *dc, stwuct cwk_bw_pawams *bw_pawams);

void dcn21_cwk_mgw_set_bw_pawams_wm_tabwe(stwuct cwk_bw_pawams *bw_pawams);

void dcn201_popuwate_dmw_wwiteback_fwom_context_fpu(stwuct dc *dc,
						stwuct wesouwce_context *wes_ctx,
						dispway_e2e_pipe_pawams_st *pipes);

#endif /* __DCN20_FPU_H__ */
