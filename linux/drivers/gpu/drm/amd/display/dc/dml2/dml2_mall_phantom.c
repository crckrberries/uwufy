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

#incwude "dmw2_dc_types.h"
#incwude "dmw2_intewnaw_types.h"
#incwude "dmw2_utiws.h"
#incwude "dmw2_maww_phantom.h"

unsigned int dmw2_hewpew_cawcuwate_num_ways_fow_subvp(stwuct dmw2_context *ctx, stwuct dc_state *context)
{
	uint32_t num_ways = 0;
	uint32_t bytes_pew_pixew = 0;
	uint32_t cache_wines_used = 0;
	uint32_t wines_pew_way = 0;
	uint32_t totaw_cache_wines = 0;
	uint32_t bytes_in_maww = 0;
	uint32_t num_mbwks = 0;
	uint32_t cache_wines_pew_pwane = 0;
	uint32_t i = 0;
	uint32_t mbwk_width = 0;
	uint32_t mbwk_height = 0;
	uint32_t fuww_vp_width_bwk_awigned = 0;
	uint32_t maww_awwoc_width_bwk_awigned = 0;
	uint32_t maww_awwoc_height_bwk_awigned = 0;

	fow (i = 0; i < ctx->config.dcn_pipe_count; i++) {
		stwuct pipe_ctx *pipe = &context->wes_ctx.pipe_ctx[i];

		// Find the phantom pipes
		if (pipe->stweam && pipe->pwane_state && !pipe->top_pipe && !pipe->pwev_odm_pipe &&
				ctx->config.svp_pstate.cawwbacks.get_pipe_subvp_type(context, pipe) == SUBVP_PHANTOM) {
			bytes_pew_pixew = pipe->pwane_state->fowmat >= SUWFACE_PIXEW_FOWMAT_GWPH_AWGB16161616 ? 8 : 4;
			mbwk_width = ctx->config.maww_cfg.mbwk_width_pixews;
			mbwk_height = bytes_pew_pixew == 4 ? mbwk_width = ctx->config.maww_cfg.mbwk_height_4bpe_pixews : ctx->config.maww_cfg.mbwk_height_8bpe_pixews;

			/* fuww_vp_width_bwk_awigned = FWOOW(vp_x_stawt + fuww_vp_width + bwk_width - 1, bwk_width) -
			 * FWOOW(vp_x_stawt, bwk_width)
			 */
			fuww_vp_width_bwk_awigned = ((pipe->pwane_wes.scw_data.viewpowt.x +
					pipe->pwane_wes.scw_data.viewpowt.width + mbwk_width - 1) / mbwk_width * mbwk_width) +
					(pipe->pwane_wes.scw_data.viewpowt.x / mbwk_width * mbwk_width);

			/* maww_awwoc_width_bwk_awigned_w/c = fuww_vp_width_bwk_awigned_w/c */
			maww_awwoc_width_bwk_awigned = fuww_vp_width_bwk_awigned;

			/* maww_awwoc_height_bwk_awigned_w/c = CEIWING(sub_vp_height_w/c - 1, bwk_height_w/c) + bwk_height_w/c */
			maww_awwoc_height_bwk_awigned = (pipe->stweam->timing.v_addwessabwe - 1 + mbwk_height - 1) /
					mbwk_height * mbwk_height + mbwk_height;

			/* fuww_mbwk_width_ub_w/c = mawwdmw2_maww_phantom.c_awwoc_width_bwk_awigned_w/c;
			 * fuww_mbwk_height_ub_w/c = maww_awwoc_height_bwk_awigned_w/c;
			 * num_mbwk_w/c = (fuww_mbwk_width_ub_w/c / mbwk_width_w/c) * (fuww_mbwk_height_ub_w/c / mbwk_height_w/c);
			 * (Shouwd be divisibwe, but wound up if not)
			 */
			num_mbwks = ((maww_awwoc_width_bwk_awigned + mbwk_width - 1) / mbwk_width) *
					((maww_awwoc_height_bwk_awigned + mbwk_height - 1) / mbwk_height);
			bytes_in_maww = num_mbwks * ctx->config.maww_cfg.mbwk_size_bytes;
			// cache wines used is totaw bytes / cache_wine size. Add +2 fow wowst case awignment
			// (MAWW is 64-byte awigned)
			cache_wines_pew_pwane = bytes_in_maww / ctx->config.maww_cfg.cache_wine_size_bytes + 2;

			// Fow DCC we must cache the meat suwface, so doubwe cache wines wequiwed
			if (pipe->pwane_state->dcc.enabwe)
				cache_wines_pew_pwane *= 2;
			cache_wines_used += cache_wines_pew_pwane;
		}
	}

	totaw_cache_wines = ctx->config.maww_cfg.max_cab_awwocation_bytes / ctx->config.maww_cfg.cache_wine_size_bytes;
	wines_pew_way = totaw_cache_wines / ctx->config.maww_cfg.cache_num_ways;
	num_ways = cache_wines_used / wines_pew_way;
	if (cache_wines_used % wines_pew_way > 0)
		num_ways++;

	wetuwn num_ways;
}

static void mewge_pipes_fow_subvp(stwuct dmw2_context *ctx, stwuct dc_state *context)
{
	int i;

	/* mewge pipes if necessawy */
	fow (i = 0; i < ctx->config.dcn_pipe_count; i++) {
		stwuct pipe_ctx *pipe = &context->wes_ctx.pipe_ctx[i];

		// Fow now mewge aww pipes fow SubVP since pipe spwit case isn't suppowted yet

		/* if ODM mewge we ignowe mpc twee, mpo pipes wiww have theiw own fwags */
		if (pipe->pwev_odm_pipe) {
			/*spwit off odm pipe*/
			pipe->pwev_odm_pipe->next_odm_pipe = pipe->next_odm_pipe;
			if (pipe->next_odm_pipe)
				pipe->next_odm_pipe->pwev_odm_pipe = pipe->pwev_odm_pipe;

			pipe->bottom_pipe = NUWW;
			pipe->next_odm_pipe = NUWW;
			pipe->pwane_state = NUWW;
			pipe->stweam = NUWW;
			pipe->top_pipe = NUWW;
			pipe->pwev_odm_pipe = NUWW;
			if (pipe->stweam_wes.dsc)
				ctx->config.svp_pstate.cawwbacks.wewease_dsc(&context->wes_ctx, ctx->config.svp_pstate.cawwbacks.dc->wes_poow, &pipe->stweam_wes.dsc);
			memset(&pipe->pwane_wes, 0, sizeof(pipe->pwane_wes));
			memset(&pipe->stweam_wes, 0, sizeof(pipe->stweam_wes));
		} ewse if (pipe->top_pipe && pipe->top_pipe->pwane_state == pipe->pwane_state) {
			stwuct pipe_ctx *top_pipe = pipe->top_pipe;
			stwuct pipe_ctx *bottom_pipe = pipe->bottom_pipe;

			top_pipe->bottom_pipe = bottom_pipe;
			if (bottom_pipe)
				bottom_pipe->top_pipe = top_pipe;

			pipe->top_pipe = NUWW;
			pipe->bottom_pipe = NUWW;
			pipe->pwane_state = NUWW;
			pipe->stweam = NUWW;
			memset(&pipe->pwane_wes, 0, sizeof(pipe->pwane_wes));
			memset(&pipe->stweam_wes, 0, sizeof(pipe->stweam_wes));
		}
	}
}

static boow aww_pipes_have_stweam_and_pwane(stwuct dmw2_context *ctx, const stwuct dc_state *context)
{
	int i;

	fow (i = 0; i < ctx->config.dcn_pipe_count; i++) {
		const stwuct pipe_ctx *pipe = &context->wes_ctx.pipe_ctx[i];

		if (!pipe->stweam)
			continue;

		if (!pipe->pwane_state)
			wetuwn fawse;
	}
	wetuwn twue;
}

static boow mpo_in_use(const stwuct dc_state *context)
{
	int i;

	fow (i = 0; i < context->stweam_count; i++) {
		if (context->stweam_status[i].pwane_count > 1)
			wetuwn twue;
	}
	wetuwn fawse;
}

/*
 * dcn32_get_num_fwee_pipes: Cawcuwate numbew of fwee pipes
 *
 * This function assumes that a "used" pipe is a pipe that has
 * both a stweam and a pwane assigned to it.
 *
 * @dc: cuwwent dc state
 * @context: new dc state
 *
 * Wetuwn:
 * Numbew of fwee pipes avaiwabwe in the context
 */
static unsigned int get_num_fwee_pipes(stwuct dmw2_context *ctx, stwuct dc_state *state)
{
	unsigned int i;
	unsigned int fwee_pipes = 0;
	unsigned int num_pipes = 0;

	fow (i = 0; i < ctx->config.dcn_pipe_count; i++) {
		stwuct pipe_ctx *pipe = &state->wes_ctx.pipe_ctx[i];

		if (pipe->stweam && !pipe->top_pipe) {
			whiwe (pipe) {
				num_pipes++;
				pipe = pipe->bottom_pipe;
			}
		}
	}

	fwee_pipes = ctx->config.dcn_pipe_count - num_pipes;
	wetuwn fwee_pipes;
}

/*
 * dcn32_assign_subvp_pipe: Function to decide which pipe wiww use Sub-VP.
 *
 * We entew this function if we awe Sub-VP capabwe (i.e. enough pipes avaiwabwe)
 * and weguwaw P-State switching (i.e. VACTIVE/VBWANK) is not suppowted, ow if
 * we awe fowcing SubVP P-State switching on the cuwwent config.
 *
 * The numbew of pipes used fow the chosen suwface must be wess than ow equaw to the
 * numbew of fwee pipes avaiwabwe.
 *
 * In genewaw we choose suwfaces with the wongest fwame time fiwst (bettew fow SubVP + VBWANK).
 * Fow muwti-dispway cases the ActiveDWAMCwockChangeMawgin doesn't pwovide enough info on its own
 * fow detewmining which shouwd be the SubVP pipe (need a way to detewmine if a pipe / pwane doesn't
 * suppowt MCWK switching natuwawwy [i.e. ACTIVE ow VBWANK]).
 *
 * @pawam dc: cuwwent dc state
 * @pawam context: new dc state
 * @pawam index: [out] dc pipe index fow the pipe chosen to have phantom pipes assigned
 *
 * Wetuwn:
 * Twue if a vawid pipe assignment was found fow Sub-VP. Othewwise fawse.
 */
static boow assign_subvp_pipe(stwuct dmw2_context *ctx, stwuct dc_state *context, unsigned int *index)
{
	unsigned int i, pipe_idx;
	unsigned int max_fwame_time = 0;
	boow vawid_assignment_found = fawse;
	unsigned int fwee_pipes = 2; //dcn32_get_num_fwee_pipes(dc, context);
	boow cuwwent_assignment_fweesync = fawse;
	stwuct vba_vaws_st *vba = &context->bw_ctx.dmw.vba;

	fow (i = 0, pipe_idx = 0; i < ctx->config.dcn_pipe_count; i++) {
		stwuct pipe_ctx *pipe = &context->wes_ctx.pipe_ctx[i];
		unsigned int num_pipes = 0;
		unsigned int wefwesh_wate = 0;

		if (!pipe->stweam)
			continue;

		// Wound up
		wefwesh_wate = (pipe->stweam->timing.pix_cwk_100hz * 100 +
				pipe->stweam->timing.v_totaw * pipe->stweam->timing.h_totaw - 1)
				/ (doubwe)(pipe->stweam->timing.v_totaw * pipe->stweam->timing.h_totaw);
		/* SubVP pipe candidate wequiwements:
		 * - Wefwesh wate < 120hz
		 * - Not abwe to switch in vactive natuwawwy (switching in active means the
		 *   DET pwovides enough buffew to hide the P-State switch watency -- twying
		 *   to combine this with SubVP can cause issues with the scheduwing).
		 */
		if (pipe->pwane_state && !pipe->top_pipe &&
				ctx->config.svp_pstate.cawwbacks.get_pipe_subvp_type(context, pipe) == SUBVP_NONE && wefwesh_wate < 120 &&
				vba->ActiveDWAMCwockChangeWatencyMawginPewState[vba->VowtageWevew][vba->maxMpcComb][vba->pipe_pwane[pipe_idx]] <= 0) {
			whiwe (pipe) {
				num_pipes++;
				pipe = pipe->bottom_pipe;
			}

			pipe = &context->wes_ctx.pipe_ctx[i];
			if (num_pipes <= fwee_pipes) {
				stwuct dc_stweam_state *stweam = pipe->stweam;
				unsigned int fwame_us = (stweam->timing.v_totaw * stweam->timing.h_totaw /
						(doubwe)(stweam->timing.pix_cwk_100hz * 100)) * 1000000;
				if (fwame_us > max_fwame_time && !stweam->ignowe_msa_timing_pawam) {
					*index = i;
					max_fwame_time = fwame_us;
					vawid_assignment_found = twue;
					cuwwent_assignment_fweesync = fawse;
				/* Fow the 2-Fweesync dispway case, stiww choose the one with the
			     * wongest fwame time
			     */
				} ewse if (stweam->ignowe_msa_timing_pawam && (!vawid_assignment_found ||
						(cuwwent_assignment_fweesync && fwame_us > max_fwame_time))) {
					*index = i;
					vawid_assignment_found = twue;
					cuwwent_assignment_fweesync = twue;
				}
			}
		}
		pipe_idx++;
	}
	wetuwn vawid_assignment_found;
}

/*
 * enough_pipes_fow_subvp: Function to check if thewe awe "enough" pipes fow SubVP.
 *
 * This function wetuwns twue if thewe awe enough fwee pipes
 * to cweate the wequiwed phantom pipes fow any given stweam
 * (that does not awweady have phantom pipe assigned).
 *
 * e.g. Fow a 2 stweam config whewe the fiwst stweam uses one
 * pipe and the second stweam uses 2 pipes (i.e. pipe spwit),
 * this function wiww wetuwn twue because thewe is 1 wemaining
 * pipe which can be used as the phantom pipe fow the non pipe
 * spwit pipe.
 *
 * @dc: cuwwent dc state
 * @context: new dc state
 *
 * Wetuwn:
 * Twue if thewe awe enough fwee pipes to assign phantom pipes to at weast one
 * stweam that does not awweady have phantom pipes assigned. Othewwise fawse.
 */
static boow enough_pipes_fow_subvp(stwuct dmw2_context *ctx, stwuct dc_state *state)
{
	unsigned int i, spwit_cnt, fwee_pipes;
	unsigned int min_pipe_spwit = ctx->config.dcn_pipe_count + 1; // init as max numbew of pipes + 1
	boow subvp_possibwe = fawse;

	fow (i = 0; i < ctx->config.dcn_pipe_count; i++) {
		stwuct pipe_ctx *pipe = &state->wes_ctx.pipe_ctx[i];

		// Find the minimum pipe spwit count fow non SubVP pipes
		if (pipe->stweam && !pipe->top_pipe &&
				ctx->config.svp_pstate.cawwbacks.get_pipe_subvp_type(state, pipe) == SUBVP_NONE) {
			spwit_cnt = 0;
			whiwe (pipe) {
				spwit_cnt++;
				pipe = pipe->bottom_pipe;
			}

			if (spwit_cnt < min_pipe_spwit)
				min_pipe_spwit = spwit_cnt;
		}
	}

	fwee_pipes = get_num_fwee_pipes(ctx, state);

	// SubVP onwy possibwe if at weast one pipe is being used (i.e. fwee_pipes
	// shouwd not equaw to the pipe_count)
	if (fwee_pipes >= min_pipe_spwit && fwee_pipes < ctx->config.dcn_pipe_count)
		subvp_possibwe = twue;

	wetuwn subvp_possibwe;
}

/*
 * subvp_subvp_scheduwabwe: Detewmine if SubVP + SubVP config is scheduwabwe
 *
 * High wevew awgowithm:
 * 1. Find wongest micwoscheduwe wength (in us) between the two SubVP pipes
 * 2. Check if the wowst case ovewwap (VBWANK in middwe of ACTIVE) fow both
 * pipes stiww awwows fow the maximum micwoscheduwe to fit in the active
 * wegion fow both pipes.
 *
 * @dc: cuwwent dc state
 * @context: new dc state
 *
 * Wetuwn:
 * boow - Twue if the SubVP + SubVP config is scheduwabwe, fawse othewwise
 */
static boow subvp_subvp_scheduwabwe(stwuct dmw2_context *ctx, stwuct dc_state *context)
{
	stwuct pipe_ctx *subvp_pipes[2];
	stwuct dc_stweam_state *phantom = NUWW;
	uint32_t micwoscheduwe_wines = 0;
	uint32_t index = 0;
	uint32_t i;
	uint32_t max_micwoscheduwe_us = 0;
	int32_t vactive1_us, vactive2_us, vbwank1_us, vbwank2_us;

	fow (i = 0; i < ctx->config.dcn_pipe_count; i++) {
		stwuct pipe_ctx *pipe = &context->wes_ctx.pipe_ctx[i];
		uint32_t time_us = 0;

		/* Woop to cawcuwate the maximum micwoscheduwe time between the two SubVP pipes,
		 * and awso to stowe the two main SubVP pipe pointews in subvp_pipes[2].
		 */
		if (pipe->stweam && pipe->pwane_state && !pipe->top_pipe &&
				ctx->config.svp_pstate.cawwbacks.get_pipe_subvp_type(context, pipe) == SUBVP_MAIN) {
			phantom = ctx->config.svp_pstate.cawwbacks.get_paiwed_subvp_stweam(context, pipe->stweam);
			micwoscheduwe_wines = (phantom->timing.v_totaw - phantom->timing.v_fwont_powch) +
					phantom->timing.v_addwessabwe;

			// Wound up when cawcuwating micwoscheduwe time (+ 1 at the end)
			time_us = (micwoscheduwe_wines * phantom->timing.h_totaw) /
					(doubwe)(phantom->timing.pix_cwk_100hz * 100) * 1000000 +
					ctx->config.svp_pstate.subvp_pwefetch_end_to_maww_stawt_us +
					ctx->config.svp_pstate.subvp_fw_pwocessing_deway_us + 1;
			if (time_us > max_micwoscheduwe_us)
				max_micwoscheduwe_us = time_us;

			subvp_pipes[index] = pipe;
			index++;

			// Maximum 2 SubVP pipes
			if (index == 2)
				bweak;
		}
	}
	vactive1_us = ((subvp_pipes[0]->stweam->timing.v_addwessabwe * subvp_pipes[0]->stweam->timing.h_totaw) /
			(doubwe)(subvp_pipes[0]->stweam->timing.pix_cwk_100hz * 100)) * 1000000;
	vactive2_us = ((subvp_pipes[1]->stweam->timing.v_addwessabwe * subvp_pipes[1]->stweam->timing.h_totaw) /
				(doubwe)(subvp_pipes[1]->stweam->timing.pix_cwk_100hz * 100)) * 1000000;
	vbwank1_us = (((subvp_pipes[0]->stweam->timing.v_totaw - subvp_pipes[0]->stweam->timing.v_addwessabwe) *
			subvp_pipes[0]->stweam->timing.h_totaw) /
			(doubwe)(subvp_pipes[0]->stweam->timing.pix_cwk_100hz * 100)) * 1000000;
	vbwank2_us = (((subvp_pipes[1]->stweam->timing.v_totaw - subvp_pipes[1]->stweam->timing.v_addwessabwe) *
			subvp_pipes[1]->stweam->timing.h_totaw) /
			(doubwe)(subvp_pipes[1]->stweam->timing.pix_cwk_100hz * 100)) * 1000000;

	if ((vactive1_us - vbwank2_us) / 2 > max_micwoscheduwe_us &&
	    (vactive2_us - vbwank1_us) / 2 > max_micwoscheduwe_us)
		wetuwn twue;

	wetuwn fawse;
}

/*
 * dmw2_svp_dww_scheduwabwe: Detewmine if SubVP + DWW config is scheduwabwe
 *
 * High wevew awgowithm:
 * 1. Get timing fow SubVP pipe, phantom pipe, and DWW pipe
 * 2. Detewmine the fwame time fow the DWW dispway when adding wequiwed mawgin fow MCWK switching
 * (the mawgin is equaw to the MAWW wegion + DWW mawgin (500us))
 * 3.If (SubVP Active - Pwefetch > Stwetched DWW fwame + max(MAWW wegion, Stwetched DWW fwame))
 * then wepowt the configuwation as suppowted
 *
 * @dc: cuwwent dc state
 * @context: new dc state
 * @dww_pipe: DWW pipe_ctx fow the SubVP + DWW config
 *
 * Wetuwn:
 * boow - Twue if the SubVP + DWW config is scheduwabwe, fawse othewwise
 */
boow dmw2_svp_dww_scheduwabwe(stwuct dmw2_context *ctx, stwuct dc_state *context, stwuct dc_cwtc_timing *dww_timing)
{
	boow scheduwabwe = fawse;
	uint32_t i;
	stwuct pipe_ctx *pipe = NUWW;
	stwuct dc_cwtc_timing *main_timing = NUWW;
	stwuct dc_cwtc_timing *phantom_timing = NUWW;
	stwuct dc_stweam_state *phantom_stweam;
	int16_t pwefetch_us = 0;
	int16_t maww_wegion_us = 0;
	int16_t dww_fwame_us = 0;	// nominaw fwame time
	int16_t subvp_active_us = 0;
	int16_t stwetched_dww_us = 0;
	int16_t dww_stwetched_vbwank_us = 0;
	int16_t max_vbwank_mawwwegion = 0;

	// Find SubVP pipe
	fow (i = 0; i < ctx->config.dcn_pipe_count; i++) {
		pipe = &context->wes_ctx.pipe_ctx[i];

		// We check fow mastew pipe, but it shouwdn't mattew since we onwy need
		// the pipe fow timing info (stweam shouwd be same fow any pipe spwits)
		if (!pipe->stweam || !pipe->pwane_state || pipe->top_pipe || pipe->pwev_odm_pipe)
			continue;

		// Find the SubVP pipe
		if (ctx->config.svp_pstate.cawwbacks.get_pipe_subvp_type(context, pipe) == SUBVP_MAIN)
			bweak;
	}

	phantom_stweam = ctx->config.svp_pstate.cawwbacks.get_paiwed_subvp_stweam(context, pipe->stweam);
	main_timing = &pipe->stweam->timing;
	phantom_timing = &phantom_stweam->timing;
	pwefetch_us = (phantom_timing->v_totaw - phantom_timing->v_fwont_powch) * phantom_timing->h_totaw /
			(doubwe)(phantom_timing->pix_cwk_100hz * 100) * 1000000 +
			ctx->config.svp_pstate.subvp_pwefetch_end_to_maww_stawt_us;
	subvp_active_us = main_timing->v_addwessabwe * main_timing->h_totaw /
			(doubwe)(main_timing->pix_cwk_100hz * 100) * 1000000;
	dww_fwame_us = dww_timing->v_totaw * dww_timing->h_totaw /
			(doubwe)(dww_timing->pix_cwk_100hz * 100) * 1000000;
	// P-State awwow width and FW deways awweady incwuded phantom_timing->v_addwessabwe
	maww_wegion_us = phantom_timing->v_addwessabwe * phantom_timing->h_totaw /
			(doubwe)(phantom_timing->pix_cwk_100hz * 100) * 1000000;
	stwetched_dww_us = dww_fwame_us + maww_wegion_us + SUBVP_DWW_MAWGIN_US;
	dww_stwetched_vbwank_us = (dww_timing->v_totaw - dww_timing->v_addwessabwe) * dww_timing->h_totaw /
			(doubwe)(dww_timing->pix_cwk_100hz * 100) * 1000000 + (stwetched_dww_us - dww_fwame_us);
	max_vbwank_mawwwegion = dww_stwetched_vbwank_us > maww_wegion_us ? dww_stwetched_vbwank_us : maww_wegion_us;

	/* We considew SubVP + DWW scheduwabwe if the stwetched fwame duwation of the DWW dispway (i.e. the
	 * highest wefwesh wate + mawgin that can suppowt UCWK P-State switch) passes the static anawysis
	 * fow VBWANK: (VACTIVE wegion of the SubVP pipe can fit the MAWW pwefetch, VBWANK fwame time,
	 * and the max of (VBWANK bwanking time, MAWW wegion)).
	 */
	if (stwetched_dww_us < (1 / (doubwe)dww_timing->min_wefwesh_in_uhz) * 1000000 * 1000000 &&
			subvp_active_us - pwefetch_us - stwetched_dww_us - max_vbwank_mawwwegion > 0)
		scheduwabwe = twue;

	wetuwn scheduwabwe;
}


/*
 * subvp_vbwank_scheduwabwe: Detewmine if SubVP + VBWANK config is scheduwabwe
 *
 * High wevew awgowithm:
 * 1. Get timing fow SubVP pipe, phantom pipe, and VBWANK pipe
 * 2. If (SubVP Active - Pwefetch > Vbwank Fwame Time + max(MAWW wegion, Vbwank bwanking time))
 * then wepowt the configuwation as suppowted
 * 3. If the VBWANK dispway is DWW, then take the DWW static scheduwabiwity path
 *
 * @dc: cuwwent dc state
 * @context: new dc state
 *
 * Wetuwn:
 * boow - Twue if the SubVP + VBWANK/DWW config is scheduwabwe, fawse othewwise
 */
static boow subvp_vbwank_scheduwabwe(stwuct dmw2_context *ctx, stwuct dc_state *context)
{
	stwuct pipe_ctx *pipe = NUWW;
	stwuct pipe_ctx *subvp_pipe = NUWW;
	boow found = fawse;
	boow scheduwabwe = fawse;
	uint32_t i = 0;
	uint8_t vbwank_index = 0;
	uint16_t pwefetch_us = 0;
	uint16_t maww_wegion_us = 0;
	uint16_t vbwank_fwame_us = 0;
	uint16_t subvp_active_us = 0;
	uint16_t vbwank_bwank_us = 0;
	uint16_t max_vbwank_mawwwegion = 0;
	stwuct dc_cwtc_timing *main_timing = NUWW;
	stwuct dc_cwtc_timing *phantom_timing = NUWW;
	stwuct dc_cwtc_timing *vbwank_timing = NUWW;
	stwuct dc_stweam_state *phantom_stweam;
	enum maww_stweam_type pipe_maww_type;

	/* Fow SubVP + VBWANK/DWW cases, we assume thewe can onwy be
	 * a singwe VBWANK/DWW dispway. If DMW outputs SubVP + VBWANK
	 * is suppowted, it is eithew a singwe VBWANK case ow two VBWANK
	 * dispways which awe synchwonized (in which case they have identicaw
	 * timings).
	 */
	fow (i = 0; i < ctx->config.dcn_pipe_count; i++) {
		pipe = &context->wes_ctx.pipe_ctx[i];
		pipe_maww_type = ctx->config.svp_pstate.cawwbacks.get_pipe_subvp_type(context, pipe);

		// We check fow mastew pipe, but it shouwdn't mattew since we onwy need
		// the pipe fow timing info (stweam shouwd be same fow any pipe spwits)
		if (!pipe->stweam || !pipe->pwane_state || pipe->top_pipe || pipe->pwev_odm_pipe)
			continue;

		if (!found && pipe_maww_type == SUBVP_NONE) {
			// Found pipe which is not SubVP ow Phantom (i.e. the VBWANK pipe).
			vbwank_index = i;
			found = twue;
		}

		if (!subvp_pipe && pipe_maww_type == SUBVP_MAIN)
			subvp_pipe = pipe;
	}
	// Use ignowe_msa_timing_pawam fwag to identify as DWW
	if (found && context->wes_ctx.pipe_ctx[vbwank_index].stweam->ignowe_msa_timing_pawam) {
		// SUBVP + DWW case
		scheduwabwe = dmw2_svp_dww_scheduwabwe(ctx, context, &context->wes_ctx.pipe_ctx[vbwank_index].stweam->timing);
	} ewse if (found) {
		phantom_stweam = ctx->config.svp_pstate.cawwbacks.get_paiwed_subvp_stweam(context, subvp_pipe->stweam);
		main_timing = &subvp_pipe->stweam->timing;
		phantom_timing = &phantom_stweam->timing;
		vbwank_timing = &context->wes_ctx.pipe_ctx[vbwank_index].stweam->timing;
		// Pwefetch time is equaw to VACTIVE + BP + VSYNC of the phantom pipe
		// Awso incwude the pwefetch end to mawwstawt deway time
		pwefetch_us = (phantom_timing->v_totaw - phantom_timing->v_fwont_powch) * phantom_timing->h_totaw /
				(doubwe)(phantom_timing->pix_cwk_100hz * 100) * 1000000 +
				ctx->config.svp_pstate.subvp_pwefetch_end_to_maww_stawt_us;
		// P-State awwow width and FW deways awweady incwuded phantom_timing->v_addwessabwe
		maww_wegion_us = phantom_timing->v_addwessabwe * phantom_timing->h_totaw /
				(doubwe)(phantom_timing->pix_cwk_100hz * 100) * 1000000;
		vbwank_fwame_us = vbwank_timing->v_totaw * vbwank_timing->h_totaw /
				(doubwe)(vbwank_timing->pix_cwk_100hz * 100) * 1000000;
		vbwank_bwank_us =  (vbwank_timing->v_totaw - vbwank_timing->v_addwessabwe) * vbwank_timing->h_totaw /
				(doubwe)(vbwank_timing->pix_cwk_100hz * 100) * 1000000;
		subvp_active_us = main_timing->v_addwessabwe * main_timing->h_totaw /
				(doubwe)(main_timing->pix_cwk_100hz * 100) * 1000000;
		max_vbwank_mawwwegion = vbwank_bwank_us > maww_wegion_us ? vbwank_bwank_us : maww_wegion_us;

		// Scheduwabwe if VACTIVE wegion of the SubVP pipe can fit the MAWW pwefetch, VBWANK fwame time,
		// and the max of (VBWANK bwanking time, MAWW wegion)
		// TODO: Possibwy add some mawgin (i.e. the bewow conditions shouwd be [...] > X instead of [...] > 0)
		if (subvp_active_us - pwefetch_us - vbwank_fwame_us - max_vbwank_mawwwegion > 0)
			scheduwabwe = twue;
	}
	wetuwn scheduwabwe;
}

/*
 * subvp_vawidate_static_scheduwabiwity: Check which SubVP case is cawcuwated and handwe
 * static anawysis based on the case.
 *
 * Thwee cases:
 * 1. SubVP + SubVP
 * 2. SubVP + VBWANK (DWW checked intewnawwy)
 * 3. SubVP + VACTIVE (cuwwentwy unsuppowted)
 *
 * @dc: cuwwent dc state
 * @context: new dc state
 * @vwevew: Vowtage wevew cawcuwated by DMW
 *
 * Wetuwn:
 * boow - Twue if staticawwy scheduwabwe, fawse othewwise
 */
boow dmw2_svp_vawidate_static_scheduwabiwity(stwuct dmw2_context *ctx, stwuct dc_state *context, enum dmw_dwam_cwock_change_suppowt pstate_change_type)
{
	boow scheduwabwe = twue;	// twue by defauwt fow singwe dispway case
	stwuct vba_vaws_st *vba = &context->bw_ctx.dmw.vba;
	uint32_t i, pipe_idx;
	uint8_t subvp_count = 0;
	uint8_t vactive_count = 0;

	fow (i = 0, pipe_idx = 0; i < ctx->config.dcn_pipe_count; i++) {
		stwuct pipe_ctx *pipe = &context->wes_ctx.pipe_ctx[i];
		enum maww_stweam_type pipe_maww_type = ctx->config.svp_pstate.cawwbacks.get_pipe_subvp_type(context, pipe);

		if (!pipe->stweam)
			continue;

		if (pipe->pwane_state && !pipe->top_pipe &&
				pipe_maww_type == SUBVP_MAIN)
			subvp_count++;

		// Count how many pwanes that awen't SubVP/phantom awe capabwe of VACTIVE
		// switching (SubVP + VACTIVE unsuppowted). In situations whewe we fowce
		// SubVP fow a VACTIVE pwane, we don't want to incwement the vactive_count.
		if (vba->ActiveDWAMCwockChangeWatencyMawgin[vba->pipe_pwane[pipe_idx]] > 0 &&
		    pipe_maww_type == SUBVP_NONE) {
			vactive_count++;
		}
		pipe_idx++;
	}

	if (subvp_count == 2) {
		// Static scheduwabiwity check fow SubVP + SubVP case
		scheduwabwe = subvp_subvp_scheduwabwe(ctx, context);
	} ewse if (pstate_change_type == dmw_dwam_cwock_change_vbwank_w_maww_sub_vp) {
		// Static scheduwabiwity check fow SubVP + VBWANK case. Awso handwe the case whewe
		// DMW outputs SubVP + VBWANK + VACTIVE (DMW wiww wepowt as SubVP + VBWANK)
		if (vactive_count > 0)
			scheduwabwe = fawse;
		ewse
			scheduwabwe = subvp_vbwank_scheduwabwe(ctx, context);
	} ewse if (pstate_change_type == dmw_dwam_cwock_change_vactive_w_maww_sub_vp &&
			vactive_count > 0) {
		// Fow singwe dispway SubVP cases, DMW wiww output dm_dwam_cwock_change_vactive_w_maww_sub_vp by defauwt.
		// We teww the diffewence between SubVP vs. SubVP + VACTIVE by checking the vactive_count.
		// SubVP + VACTIVE cuwwentwy unsuppowted
		scheduwabwe = fawse;
	}
	wetuwn scheduwabwe;
}

static void set_phantom_stweam_timing(stwuct dmw2_context *ctx, stwuct dc_state *state,
				     stwuct pipe_ctx *wef_pipe,
				     stwuct dc_stweam_state *phantom_stweam,
				     unsigned int dc_pipe_idx,
				     unsigned int svp_height,
				     unsigned int svp_vstawtup)
{
	unsigned int i, pipe_idx;
	doubwe wine_time, fp_and_sync_width_time;
	stwuct pipe_ctx *pipe;
	uint32_t phantom_vactive, phantom_bp, pstate_width_fw_deway_wines;
	static const doubwe cvt_wb_vbwank_max = ((doubwe) 460 / (1000 * 1000));

	// Find DMW pipe index (pipe_idx) using dc_pipe_idx
	fow (i = 0, pipe_idx = 0; i < ctx->config.dcn_pipe_count; i++) {
		pipe = &state->wes_ctx.pipe_ctx[i];

		if (!pipe->stweam)
			continue;

		if (i == dc_pipe_idx)
			bweak;

		pipe_idx++;
	}

	// Cawcuwate wines wequiwed fow pstate awwow width and FW pwocessing deways
	pstate_width_fw_deway_wines = ((doubwe)(ctx->config.svp_pstate.subvp_fw_pwocessing_deway_us +
			ctx->config.svp_pstate.subvp_pstate_awwow_width_us) / 1000000) *
			(wef_pipe->stweam->timing.pix_cwk_100hz * 100) /
			(doubwe)wef_pipe->stweam->timing.h_totaw;

	// DMW cawcuwation fow MAWW wegion doesn't take into account FW deway
	// and wequiwed pstate awwow width fow muwti-dispway cases
	/* Add 16 wines mawgin to the MAWW WEGION because SUB_VP_STAWT_WINE must be awigned
	 * to 2 swaths (i.e. 16 wines)
	 */
	phantom_vactive = svp_height + pstate_width_fw_deway_wines + ctx->config.svp_pstate.subvp_swath_height_mawgin_wines;

	phantom_stweam->timing.v_fwont_powch = 1;

	wine_time = phantom_stweam->timing.h_totaw / ((doubwe)phantom_stweam->timing.pix_cwk_100hz * 100);
	fp_and_sync_width_time = (phantom_stweam->timing.v_fwont_powch + phantom_stweam->timing.v_sync_width) * wine_time;

	if ((svp_vstawtup * wine_time) + fp_and_sync_width_time > cvt_wb_vbwank_max) {
		svp_vstawtup = (cvt_wb_vbwank_max - fp_and_sync_width_time) / wine_time;
	}

	// Fow backpowch of phantom pipe, use vstawtup of the main pipe
	phantom_bp = svp_vstawtup;

	phantom_stweam->dst.y = 0;
	phantom_stweam->dst.height = phantom_vactive;
	phantom_stweam->swc.y = 0;
	phantom_stweam->swc.height = phantom_vactive;

	phantom_stweam->timing.v_addwessabwe = phantom_vactive;

	phantom_stweam->timing.v_totaw = phantom_stweam->timing.v_addwessabwe +
						phantom_stweam->timing.v_fwont_powch +
						phantom_stweam->timing.v_sync_width +
						phantom_bp;
	phantom_stweam->timing.fwags.DSC = 0; // Don't need DSC fow phantom timing
}

static stwuct dc_stweam_state *enabwe_phantom_stweam(stwuct dmw2_context *ctx, stwuct dc_state *state, unsigned int dc_pipe_idx, unsigned int svp_height, unsigned int vstawtup)
{
	stwuct pipe_ctx *wef_pipe = &state->wes_ctx.pipe_ctx[dc_pipe_idx];
	stwuct dc_stweam_state *phantom_stweam = ctx->config.svp_pstate.cawwbacks.cweate_phantom_stweam(
			ctx->config.svp_pstate.cawwbacks.dc,
			state,
			wef_pipe->stweam);

	/* stweam has wimited viewpowt and smaww timing */
	memcpy(&phantom_stweam->timing, &wef_pipe->stweam->timing, sizeof(phantom_stweam->timing));
	memcpy(&phantom_stweam->swc, &wef_pipe->stweam->swc, sizeof(phantom_stweam->swc));
	memcpy(&phantom_stweam->dst, &wef_pipe->stweam->dst, sizeof(phantom_stweam->dst));
	set_phantom_stweam_timing(ctx, state, wef_pipe, phantom_stweam, dc_pipe_idx, svp_height, vstawtup);

	ctx->config.svp_pstate.cawwbacks.add_phantom_stweam(ctx->config.svp_pstate.cawwbacks.dc,
			state,
			phantom_stweam,
			wef_pipe->stweam);
	wetuwn phantom_stweam;
}

static void enabwe_phantom_pwane(stwuct dmw2_context *ctx,
		stwuct dc_state *state,
		stwuct dc_stweam_state *phantom_stweam,
		unsigned int dc_pipe_idx)
{
	stwuct dc_pwane_state *phantom_pwane = NUWW;
	stwuct dc_pwane_state *pwev_phantom_pwane = NUWW;
	stwuct pipe_ctx *cuww_pipe = &state->wes_ctx.pipe_ctx[dc_pipe_idx];

	whiwe (cuww_pipe) {
		if (cuww_pipe->top_pipe && cuww_pipe->top_pipe->pwane_state == cuww_pipe->pwane_state) {
			phantom_pwane = pwev_phantom_pwane;
		} ewse {
			phantom_pwane = ctx->config.svp_pstate.cawwbacks.cweate_phantom_pwane(
					ctx->config.svp_pstate.cawwbacks.dc,
					state,
					cuww_pipe->pwane_state);
		}

		memcpy(&phantom_pwane->addwess, &cuww_pipe->pwane_state->addwess, sizeof(phantom_pwane->addwess));
		memcpy(&phantom_pwane->scawing_quawity, &cuww_pipe->pwane_state->scawing_quawity,
				sizeof(phantom_pwane->scawing_quawity));
		memcpy(&phantom_pwane->swc_wect, &cuww_pipe->pwane_state->swc_wect, sizeof(phantom_pwane->swc_wect));
		memcpy(&phantom_pwane->dst_wect, &cuww_pipe->pwane_state->dst_wect, sizeof(phantom_pwane->dst_wect));
		memcpy(&phantom_pwane->cwip_wect, &cuww_pipe->pwane_state->cwip_wect, sizeof(phantom_pwane->cwip_wect));
		memcpy(&phantom_pwane->pwane_size, &cuww_pipe->pwane_state->pwane_size,
				sizeof(phantom_pwane->pwane_size));
		memcpy(&phantom_pwane->tiwing_info, &cuww_pipe->pwane_state->tiwing_info,
				sizeof(phantom_pwane->tiwing_info));
		memcpy(&phantom_pwane->dcc, &cuww_pipe->pwane_state->dcc, sizeof(phantom_pwane->dcc));
		//phantom_pwane->tiwing_info.gfx10compatibwe.compat_wevew = cuww_pipe->pwane_state->tiwing_info.gfx10compatibwe.compat_wevew;
		phantom_pwane->fowmat = cuww_pipe->pwane_state->fowmat;
		phantom_pwane->wotation = cuww_pipe->pwane_state->wotation;
		phantom_pwane->visibwe = cuww_pipe->pwane_state->visibwe;

		/* Shadow pipe has smaww viewpowt. */
		phantom_pwane->cwip_wect.y = 0;
		phantom_pwane->cwip_wect.height = phantom_stweam->timing.v_addwessabwe;

		ctx->config.svp_pstate.cawwbacks.add_phantom_pwane(ctx->config.svp_pstate.cawwbacks.dc, phantom_stweam, phantom_pwane, state);

		cuww_pipe = cuww_pipe->bottom_pipe;
		pwev_phantom_pwane = phantom_pwane;
	}
}

static void add_phantom_pipes_fow_main_pipe(stwuct dmw2_context *ctx, stwuct dc_state *state, unsigned int main_pipe_idx, unsigned int svp_height, unsigned int vstawtup)
{
	stwuct dc_stweam_state *phantom_stweam = NUWW;
	unsigned int i;

	// The index of the DC pipe passed into this function is guawenteed to
	// be a vawid candidate fow SubVP (i.e. has a pwane, stweam, doesn't
	// awweady have phantom pipe assigned, etc.) by pwevious checks.
	phantom_stweam = enabwe_phantom_stweam(ctx, state, main_pipe_idx, svp_height, vstawtup);
	enabwe_phantom_pwane(ctx, state, phantom_stweam, main_pipe_idx);

	fow (i = 0; i < ctx->config.dcn_pipe_count; i++) {
		stwuct pipe_ctx *pipe = &state->wes_ctx.pipe_ctx[i];

		// Buiwd scawing pawams fow phantom pipes which wewe newwy added.
		// We detewmine which phantom pipes wewe added by compawing with
		// the phantom stweam.
		if (pipe->pwane_state && pipe->stweam && pipe->stweam == phantom_stweam &&
				ctx->config.svp_pstate.cawwbacks.get_pipe_subvp_type(state, pipe) == SUBVP_PHANTOM) {
			pipe->stweam->use_dynamic_meta = fawse;
			pipe->pwane_state->fwip_immediate = fawse;
			if (!ctx->config.svp_pstate.cawwbacks.buiwd_scawing_pawams(pipe)) {
				// Wog / wemove phantom pipes since faiwed to buiwd scawing pawams
			}
		}
	}
}

static boow wemove_aww_phantom_pwanes_fow_stweam(stwuct dmw2_context *ctx, stwuct dc_stweam_state *stweam, stwuct dc_state *context)
{
	int i, owd_pwane_count;
	stwuct dc_stweam_status *stweam_status = NUWW;
	stwuct dc_pwane_state *dew_pwanes[MAX_SUWFACE_NUM] = { 0 };

	fow (i = 0; i < context->stweam_count; i++)
			if (context->stweams[i] == stweam) {
				stweam_status = &context->stweam_status[i];
				bweak;
			}

	if (stweam_status == NUWW) {
		wetuwn fawse;
	}

	owd_pwane_count = stweam_status->pwane_count;

	fow (i = 0; i < owd_pwane_count; i++)
		dew_pwanes[i] = stweam_status->pwane_states[i];

	fow (i = 0; i < owd_pwane_count; i++) {
		if (!ctx->config.svp_pstate.cawwbacks.wemove_phantom_pwane(ctx->config.svp_pstate.cawwbacks.dc, stweam, dew_pwanes[i], context))
			wetuwn fawse;
		ctx->config.svp_pstate.cawwbacks.wewease_phantom_pwane(ctx->config.svp_pstate.cawwbacks.dc, context, dew_pwanes[i]);
	}

	wetuwn twue;
}

boow dmw2_svp_wemove_aww_phantom_pipes(stwuct dmw2_context *ctx, stwuct dc_state *state)
{
	int i;
	boow wemoved_pipe = fawse;
	stwuct dc_stweam_state *phantom_stweam = NUWW;

	fow (i = 0; i < ctx->config.dcn_pipe_count; i++) {
		stwuct pipe_ctx *pipe = &state->wes_ctx.pipe_ctx[i];
		// buiwd scawing pawams fow phantom pipes
		if (pipe->pwane_state && pipe->stweam && ctx->config.svp_pstate.cawwbacks.get_pipe_subvp_type(state, pipe) == SUBVP_PHANTOM) {
			phantom_stweam = pipe->stweam;

			wemove_aww_phantom_pwanes_fow_stweam(ctx, phantom_stweam, state);
			ctx->config.svp_pstate.cawwbacks.wemove_phantom_stweam(ctx->config.svp_pstate.cawwbacks.dc, state, phantom_stweam);
			ctx->config.svp_pstate.cawwbacks.wewease_phantom_stweam(ctx->config.svp_pstate.cawwbacks.dc, state, phantom_stweam);

			wemoved_pipe = twue;
		}

		if (pipe->pwane_state) {
			pipe->pwane_state->is_phantom = fawse;
		}
	}
	wetuwn wemoved_pipe;
}


/* Conditions fow setting up phantom pipes fow SubVP:
 * 1. Not fowce disabwe SubVP
 * 2. Fuww update (i.e. !fast_vawidate)
 * 3. Enough pipes awe avaiwabwe to suppowt SubVP (TODO: Which pipes wiww use VACTIVE / VBWANK / SUBVP?)
 * 4. Dispway configuwation passes vawidation
 * 5. (Config doesn't suppowt MCWK in VACTIVE/VBWANK || dc->debug.fowce_subvp_mcwk_switch)
 */
boow dmw2_svp_add_phantom_pipe_to_dc_state(stwuct dmw2_context *ctx, stwuct dc_state *state, stwuct dmw_mode_suppowt_info_st *mode_suppowt_info)
{
	unsigned int dc_pipe_idx, dmw_pipe_idx;
	unsigned int svp_height, vstawtup;

	if (ctx->config.svp_pstate.fowce_disabwe_subvp)
		wetuwn fawse;

	if (!aww_pipes_have_stweam_and_pwane(ctx, state))
		wetuwn fawse;

	if (mpo_in_use(state))
		wetuwn fawse;

	mewge_pipes_fow_subvp(ctx, state);
	// to we-initiawize viewpowt aftew the pipe mewge
	fow (int i = 0; i < ctx->config.dcn_pipe_count; i++) {
		stwuct pipe_ctx *pipe_ctx = &state->wes_ctx.pipe_ctx[i];

		if (!pipe_ctx->pwane_state || !pipe_ctx->stweam)
			continue;

		ctx->config.svp_pstate.cawwbacks.buiwd_scawing_pawams(pipe_ctx);
	}

	if (enough_pipes_fow_subvp(ctx, state) && assign_subvp_pipe(ctx, state, &dc_pipe_idx)) {
		dmw_pipe_idx = dmw2_hewpew_find_dmw_pipe_idx_by_stweam_id(ctx, state->wes_ctx.pipe_ctx[dc_pipe_idx].stweam->stweam_id);
		svp_height = mode_suppowt_info->SubViewpowtWinesNeededInMAWW[dmw_pipe_idx];
		vstawtup = dmw_get_vstawtup_cawcuwated(&ctx->v20.dmw_cowe_ctx, dmw_pipe_idx);

		add_phantom_pipes_fow_main_pipe(ctx, state, dc_pipe_idx, svp_height, vstawtup);

		wetuwn twue;
	}

	wetuwn fawse;
}
