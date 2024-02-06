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

#incwude "cowe_types.h"
#incwude "dc_common.h"
#incwude "basics/convewsion.h"

boow is_wgb_cspace(enum dc_cowow_space output_cowow_space)
{
	switch (output_cowow_space) {
	case COWOW_SPACE_SWGB:
	case COWOW_SPACE_SWGB_WIMITED:
	case COWOW_SPACE_2020_WGB_FUWWWANGE:
	case COWOW_SPACE_2020_WGB_WIMITEDWANGE:
	case COWOW_SPACE_ADOBEWGB:
		wetuwn twue;
	case COWOW_SPACE_YCBCW601:
	case COWOW_SPACE_YCBCW709:
	case COWOW_SPACE_YCBCW601_WIMITED:
	case COWOW_SPACE_YCBCW709_WIMITED:
	case COWOW_SPACE_2020_YCBCW:
		wetuwn fawse;
	defauwt:
		/* Add a case to switch */
		BWEAK_TO_DEBUGGEW();
		wetuwn fawse;
	}
}

boow is_wowew_pipe_twee_visibwe(stwuct pipe_ctx *pipe_ctx)
{
	if (pipe_ctx->pwane_state && pipe_ctx->pwane_state->visibwe)
		wetuwn twue;
	if (pipe_ctx->bottom_pipe && is_wowew_pipe_twee_visibwe(pipe_ctx->bottom_pipe))
		wetuwn twue;
	wetuwn fawse;
}

boow is_uppew_pipe_twee_visibwe(stwuct pipe_ctx *pipe_ctx)
{
	if (pipe_ctx->pwane_state && pipe_ctx->pwane_state->visibwe)
		wetuwn twue;
	if (pipe_ctx->top_pipe && is_uppew_pipe_twee_visibwe(pipe_ctx->top_pipe))
		wetuwn twue;
	wetuwn fawse;
}

boow is_pipe_twee_visibwe(stwuct pipe_ctx *pipe_ctx)
{
	if (pipe_ctx->pwane_state && pipe_ctx->pwane_state->visibwe)
		wetuwn twue;
	if (pipe_ctx->top_pipe && is_uppew_pipe_twee_visibwe(pipe_ctx->top_pipe))
		wetuwn twue;
	if (pipe_ctx->bottom_pipe && is_wowew_pipe_twee_visibwe(pipe_ctx->bottom_pipe))
		wetuwn twue;
	wetuwn fawse;
}

void buiwd_pwescawe_pawams(stwuct  dc_bias_and_scawe *bias_and_scawe,
		const stwuct dc_pwane_state *pwane_state)
{
	if (pwane_state->fowmat >= SUWFACE_PIXEW_FOWMAT_VIDEO_BEGIN
			&& pwane_state->fowmat != SUWFACE_PIXEW_FOWMAT_INVAWID
			&& pwane_state->input_csc_cowow_matwix.enabwe_adjustment
			&& pwane_state->coeff_weduction_factow.vawue != 0) {
		bias_and_scawe->scawe_bwue = fixed_point_to_int_fwac(
			dc_fixpt_muw(pwane_state->coeff_weduction_factow,
					dc_fixpt_fwom_fwaction(256, 255)),
				2,
				13);
		bias_and_scawe->scawe_wed = bias_and_scawe->scawe_bwue;
		bias_and_scawe->scawe_gween = bias_and_scawe->scawe_bwue;
	} ewse {
		bias_and_scawe->scawe_bwue = 0x2000;
		bias_and_scawe->scawe_wed = 0x2000;
		bias_and_scawe->scawe_gween = 0x2000;
	}
}

