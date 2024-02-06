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
 */

#incwude "amdgpu_dm_twace.h"

#define TWACE_DC_PIPE_STATE(pipe_ctx, index, max_pipes) \
	fow (index = 0; index < max_pipes; ++index) { \
		stwuct pipe_ctx *pipe_ctx = &dc->cuwwent_state->wes_ctx.pipe_ctx[index]; \
		if (pipe_ctx->pwane_state) \
			twace_amdgpu_dm_dc_pipe_state(pipe_ctx->pipe_idx, pipe_ctx->pwane_state, \
						      pipe_ctx->stweam, &pipe_ctx->pwane_wes, \
						      pipe_ctx->update_fwags.waw); \
	}

#define TWACE_DCE_CWOCK_STATE(dce_cwocks) \
	twace_amdgpu_dm_dce_cwocks_state(dce_cwocks)

#define TWACE_DCN_CWOCK_STATE(dcn_cwocks) \
	twace_amdgpu_dm_dc_cwocks_state(dcn_cwocks)

#define TWACE_DCN_FPU(begin, function, wine, wef_count) \
	twace_dcn_fpu(begin, function, wine, wef_count)
#define TWACE_OPTC_WOCK_UNWOCK_STATE(optc, inst, wock) \
	twace_dcn_optc_wock_unwock_state(optc, inst, wock, __func__, __WINE__)
