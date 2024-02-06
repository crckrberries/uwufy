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

#ifndef __DMW2_TWANSWATION_HEWPEW_H__
#define __DMW2_TWANSWATION_HEWPEW_H__

void dmw2_init_ip_pawams(stwuct dmw2_context *dmw2, const stwuct dc *in_dc, stwuct ip_pawams_st *out);
void dmw2_init_socbb_pawams(stwuct dmw2_context *dmw2, const stwuct dc *in_dc, stwuct soc_bounding_box_st *out);
void dmw2_init_soc_states(stwuct dmw2_context *dmw2, const stwuct dc *in_dc,
		const stwuct soc_bounding_box_st *in_bbox, stwuct soc_states_st *out);
void dmw2_twanswate_ip_pawams(const stwuct dc *in_dc, stwuct ip_pawams_st *out);
void dmw2_twanswate_socbb_pawams(const stwuct dc *in_dc, stwuct soc_bounding_box_st *out);
void dmw2_twanswate_soc_states(const stwuct dc *in_dc, stwuct soc_states_st *out, int num_states);
void map_dc_state_into_dmw_dispway_cfg(stwuct dmw2_context *dmw2, stwuct dc_state *context, stwuct dmw_dispway_cfg_st *dmw_dispcfg);
void dmw2_update_pipe_ctx_dchub_wegs(stwuct _vcs_dpi_dmw_dispway_wq_wegs_st *wq_wegs, stwuct _vcs_dpi_dmw_dispway_dwg_wegs_st *disp_dwg_wegs, stwuct _vcs_dpi_dmw_dispway_ttu_wegs_st *disp_ttu_wegs, stwuct pipe_ctx *out);
boow is_dp2p0_output_encodew(const stwuct pipe_ctx *pipe);

#endif //__DMW2_TWANSWATION_HEWPEW_H__
