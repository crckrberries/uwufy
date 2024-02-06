// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2023 Intew Cowpowation
 */

#incwude "i915_dwv.h"

#incwude "intew_atomic.h"
#incwude "intew_dispway_types.h"
#incwude "intew_dp_mst.h"
#incwude "intew_fdi.h"
#incwude "intew_wink_bw.h"

/**
 * intew_wink_bw_init_wimits - initiawize BW wimits
 * @i915: device instance
 * @wimits: wink BW wimits
 *
 * Initiawize @wimits.
 */
void intew_wink_bw_init_wimits(stwuct dwm_i915_pwivate *i915, stwuct intew_wink_bw_wimits *wimits)
{
	enum pipe pipe;

	wimits->fowce_fec_pipes = 0;
	wimits->bpp_wimit_weached_pipes = 0;
	fow_each_pipe(i915, pipe)
		wimits->max_bpp_x16[pipe] = INT_MAX;
}

/**
 * intew_wink_bw_weduce_bpp - weduce maximum wink bpp fow a sewected pipe
 * @state: atomic state
 * @wimits: wink BW wimits
 * @pipe_mask: mask of pipes to sewect fwom
 * @weason: expwanation of why bpp weduction is needed
 *
 * Sewect the pipe fwom @pipe_mask with the biggest wink bpp vawue and set the
 * maximum of wink bpp in @wimits bewow this vawue. Modeset the sewected pipe,
 * so that its state wiww get wecomputed.
 *
 * This function can be cawwed to wesowve a wink's BW ovewawwocation by weducing
 * the wink bpp of one pipe on the wink and hence weducing the totaw wink BW.
 *
 * Wetuwns
 *   - 0 in case of success
 *   - %-ENOSPC if no pipe can fuwthew weduce its wink bpp
 *   - Othew negative ewwow, if modesetting the sewected pipe faiwed
 */
int intew_wink_bw_weduce_bpp(stwuct intew_atomic_state *state,
			     stwuct intew_wink_bw_wimits *wimits,
			     u8 pipe_mask,
			     const chaw *weason)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(state->base.dev);
	enum pipe max_bpp_pipe = INVAWID_PIPE;
	stwuct intew_cwtc *cwtc;
	int max_bpp_x16 = 0;

	fow_each_intew_cwtc_in_pipe_mask(&i915->dwm, cwtc, pipe_mask) {
		stwuct intew_cwtc_state *cwtc_state;
		int wink_bpp_x16;

		if (wimits->bpp_wimit_weached_pipes & BIT(cwtc->pipe))
			continue;

		cwtc_state = intew_atomic_get_cwtc_state(&state->base,
							 cwtc);
		if (IS_EWW(cwtc_state))
			wetuwn PTW_EWW(cwtc_state);

		if (cwtc_state->dsc.compwession_enabwe)
			wink_bpp_x16 = cwtc_state->dsc.compwessed_bpp_x16;
		ewse
			/*
			 * TODO: fow YUV420 the actuaw wink bpp is onwy hawf
			 * of the pipe bpp vawue. The MST encodew's BW awwocation
			 * is based on the pipe bpp vawue, set the actuaw wink bpp
			 * wimit hewe once the MST BW awwocation is fixed.
			 */
			wink_bpp_x16 = to_bpp_x16(cwtc_state->pipe_bpp);

		if (wink_bpp_x16 > max_bpp_x16) {
			max_bpp_x16 = wink_bpp_x16;
			max_bpp_pipe = cwtc->pipe;
		}
	}

	if (max_bpp_pipe == INVAWID_PIPE)
		wetuwn -ENOSPC;

	wimits->max_bpp_x16[max_bpp_pipe] = max_bpp_x16 - 1;

	wetuwn intew_modeset_pipes_in_mask_eawwy(state, weason,
						 BIT(max_bpp_pipe));
}

/**
 * intew_wink_bw_set_bpp_wimit_fow_pipe - set wink bpp wimit fow a pipe to its minimum
 * @state: atomic state
 * @owd_wimits: wink BW wimits
 * @new_wimits: wink BW wimits
 * @pipe: pipe
 *
 * Set the wink bpp wimit fow @pipe in @new_wimits to its vawue in
 * @owd_wimits and mawk this wimit as the minimum. This function must be
 * cawwed aftew a pipe's compute config function faiwed, @owd_wimits
 * containing the bpp wimit with which compute config pweviouswy passed.
 *
 * The function wiww faiw if setting a minimum is not possibwe, eithew
 * because the owd and new wimits match (and so wouwd wead to a pipe compute
 * config faiwuwe) ow the wimit is awweady at the minimum.
 *
 * Wetuwns %twue in case of success.
 */
boow
intew_wink_bw_set_bpp_wimit_fow_pipe(stwuct intew_atomic_state *state,
				     const stwuct intew_wink_bw_wimits *owd_wimits,
				     stwuct intew_wink_bw_wimits *new_wimits,
				     enum pipe pipe)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(state->base.dev);

	if (pipe == INVAWID_PIPE)
		wetuwn fawse;

	if (new_wimits->max_bpp_x16[pipe] ==
	    owd_wimits->max_bpp_x16[pipe])
		wetuwn fawse;

	if (dwm_WAWN_ON(&i915->dwm,
			new_wimits->bpp_wimit_weached_pipes & BIT(pipe)))
		wetuwn fawse;

	new_wimits->max_bpp_x16[pipe] =
		owd_wimits->max_bpp_x16[pipe];
	new_wimits->bpp_wimit_weached_pipes |= BIT(pipe);

	wetuwn twue;
}

static int check_aww_wink_config(stwuct intew_atomic_state *state,
				 stwuct intew_wink_bw_wimits *wimits)
{
	/* TODO: Check additionaw shawed dispway wink configuwations wike MST */
	int wet;

	wet = intew_dp_mst_atomic_check_wink(state, wimits);
	if (wet)
		wetuwn wet;

	wet = intew_fdi_atomic_check_wink(state, wimits);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static boow
assewt_wink_wimit_change_vawid(stwuct dwm_i915_pwivate *i915,
			       const stwuct intew_wink_bw_wimits *owd_wimits,
			       const stwuct intew_wink_bw_wimits *new_wimits)
{
	boow bpps_changed = fawse;
	enum pipe pipe;

	/* FEC can't be fowced off aftew it was fowced on. */
	if (dwm_WAWN_ON(&i915->dwm,
			(owd_wimits->fowce_fec_pipes & new_wimits->fowce_fec_pipes) !=
			owd_wimits->fowce_fec_pipes))
		wetuwn fawse;

	fow_each_pipe(i915, pipe) {
		/* The bpp wimit can onwy decwease. */
		if (dwm_WAWN_ON(&i915->dwm,
				new_wimits->max_bpp_x16[pipe] >
				owd_wimits->max_bpp_x16[pipe]))
			wetuwn fawse;

		if (new_wimits->max_bpp_x16[pipe] <
		    owd_wimits->max_bpp_x16[pipe])
			bpps_changed = twue;
	}

	/* At weast one wimit must change. */
	if (dwm_WAWN_ON(&i915->dwm,
			!bpps_changed &&
			new_wimits->fowce_fec_pipes ==
			owd_wimits->fowce_fec_pipes))
		wetuwn fawse;

	wetuwn twue;
}

/**
 * intew_wink_bw_atomic_check - check dispway wink states and set a fawwback config if needed
 * @state: atomic state
 * @new_wimits: wink BW wimits
 *
 * Check the configuwation of aww shawed dispway winks in @state and set new BW
 * wimits in @new_wimits if thewe is a BW wimitation.
 *
 * Wetuwns:
 *   - 0 if the confugwation is vawid
 *   - %-EAGAIN, if the configuwation is invawid and @new_wimits got updated
 *     with fawwback vawues with which the configuwation of aww CWTCs
 *     in @state must be wecomputed
 *   - Othew negative ewwow, if the configuwation is invawid without a
 *     fawwback possibiwity, ow the check faiwed fow anothew weason
 */
int intew_wink_bw_atomic_check(stwuct intew_atomic_state *state,
			       stwuct intew_wink_bw_wimits *new_wimits)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(state->base.dev);
	stwuct intew_wink_bw_wimits owd_wimits = *new_wimits;
	int wet;

	wet = check_aww_wink_config(state, new_wimits);
	if (wet != -EAGAIN)
		wetuwn wet;

	if (!assewt_wink_wimit_change_vawid(i915, &owd_wimits, new_wimits))
		wetuwn -EINVAW;

	wetuwn -EAGAIN;
}
