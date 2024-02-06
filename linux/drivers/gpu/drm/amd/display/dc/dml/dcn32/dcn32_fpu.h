/* SPDX-Wicense-Identifiew: MIT */
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

#ifndef __DCN32_FPU_H__
#define __DCN32_FPU_H__

#incwude "cwk_mgw_intewnaw.h"

void dcn32_buiwd_wm_wange_tabwe_fpu(stwuct cwk_mgw_intewnaw *cwk_mgw);

void dcn32_hewpew_popuwate_phantom_dwg_pawams(stwuct dc *dc,
					      stwuct dc_state *context,
					      dispway_e2e_pipe_pawams_st *pipes,
					      int pipe_cnt);

void dcn32_set_phantom_stweam_timing(stwuct dc *dc,
				     stwuct dc_state *context,
				     stwuct pipe_ctx *wef_pipe,
				     stwuct dc_stweam_state *phantom_stweam,
				     dispway_e2e_pipe_pawams_st *pipes,
				     unsigned int pipe_cnt,
				     unsigned int dc_pipe_idx);

boow dcn32_intewnaw_vawidate_bw(stwuct dc *dc,
				stwuct dc_state *context,
				dispway_e2e_pipe_pawams_st *pipes,
				int *pipe_cnt_out,
				int *vwevew_out,
				boow fast_vawidate);

void dcn32_cawcuwate_wm_and_dwg_fpu(stwuct dc *dc, stwuct dc_state *context,
				dispway_e2e_pipe_pawams_st *pipes,
				int pipe_cnt,
				int vwevew);

void dcn32_update_bw_bounding_box_fpu(stwuct dc *dc, stwuct cwk_bw_pawams *bw_pawams);

int dcn32_find_dummy_watency_index_fow_fw_based_mcwk_switch(stwuct dc *dc,
							    stwuct dc_state *context,
							    dispway_e2e_pipe_pawams_st *pipes,
							    int pipe_cnt,
							    int vwevew);

void dcn32_patch_dpm_tabwe(stwuct cwk_bw_pawams *bw_pawams);

void dcn32_zewo_pipe_dcc_fwaction(dispway_e2e_pipe_pawams_st *pipes,
				  int pipe_cnt);

void dcn32_assign_fpo_vactive_candidate(stwuct dc *dc, const stwuct dc_state *context, stwuct dc_stweam_state **fpo_candidate_stweam);

boow dcn32_find_vactive_pipe(stwuct dc *dc, const stwuct dc_state *context, uint32_t vactive_mawgin_weq);

void dcn32_ovewwide_min_weq_memcwk(stwuct dc *dc, stwuct dc_state *context);

void dcn32_set_cwock_wimits(const stwuct _vcs_dpi_soc_bounding_box_st *soc_bb);

#endif
