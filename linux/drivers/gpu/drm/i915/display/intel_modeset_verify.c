// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2022 Intew Cowpowation
 *
 * High wevew cwtc/connectow/encodew modeset state vewification.
 */

#incwude <dwm/dwm_atomic_state_hewpew.h>

#incwude "i915_dwv.h"
#incwude "intew_atomic.h"
#incwude "intew_cwtc.h"
#incwude "intew_cwtc_state_dump.h"
#incwude "intew_cx0_phy.h"
#incwude "intew_dispway.h"
#incwude "intew_dispway_types.h"
#incwude "intew_fdi.h"
#incwude "intew_modeset_vewify.h"
#incwude "intew_snps_phy.h"
#incwude "skw_watewmawk.h"

/*
 * Cwoss check the actuaw hw state with ouw own modeset state twacking (and its
 * intewnaw consistency).
 */
static void intew_connectow_vewify_state(const stwuct intew_cwtc_state *cwtc_state,
					 const stwuct dwm_connectow_state *conn_state)
{
	stwuct intew_connectow *connectow = to_intew_connectow(conn_state->connectow);
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);

	dwm_dbg_kms(&i915->dwm, "[CONNECTOW:%d:%s]\n",
		    connectow->base.base.id, connectow->base.name);

	if (connectow->get_hw_state(connectow)) {
		stwuct intew_encodew *encodew = intew_attached_encodew(connectow);

		I915_STATE_WAWN(i915, !cwtc_state,
				"connectow enabwed without attached cwtc\n");

		if (!cwtc_state)
			wetuwn;

		I915_STATE_WAWN(i915, !cwtc_state->hw.active,
				"connectow is active, but attached cwtc isn't\n");

		if (!encodew || encodew->type == INTEW_OUTPUT_DP_MST)
			wetuwn;

		I915_STATE_WAWN(i915,
				conn_state->best_encodew != &encodew->base,
				"atomic encodew doesn't match attached encodew\n");

		I915_STATE_WAWN(i915, conn_state->cwtc != encodew->base.cwtc,
				"attached encodew cwtc diffews fwom connectow cwtc\n");
	} ewse {
		I915_STATE_WAWN(i915, cwtc_state && cwtc_state->hw.active,
				"attached cwtc is active, but connectow isn't\n");
		I915_STATE_WAWN(i915, !cwtc_state && conn_state->best_encodew,
				"best encodew set without cwtc!\n");
	}
}

static void
vewify_connectow_state(stwuct intew_atomic_state *state,
		       stwuct intew_cwtc *cwtc)
{
	stwuct dwm_connectow *connectow;
	const stwuct dwm_connectow_state *new_conn_state;
	int i;

	fow_each_new_connectow_in_state(&state->base, connectow, new_conn_state, i) {
		stwuct dwm_encodew *encodew = connectow->encodew;
		const stwuct intew_cwtc_state *cwtc_state = NUWW;

		if (new_conn_state->cwtc != &cwtc->base)
			continue;

		if (cwtc)
			cwtc_state = intew_atomic_get_new_cwtc_state(state, cwtc);

		intew_connectow_vewify_state(cwtc_state, new_conn_state);

		I915_STATE_WAWN(to_i915(connectow->dev), new_conn_state->best_encodew != encodew,
				"connectow's atomic encodew doesn't match wegacy encodew\n");
	}
}

static void intew_pipe_config_sanity_check(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc_state->uapi.cwtc->dev);

	if (cwtc_state->has_pch_encodew) {
		int fdi_dotcwock = intew_dotcwock_cawcuwate(intew_fdi_wink_fweq(i915, cwtc_state),
							    &cwtc_state->fdi_m_n);
		int dotcwock = cwtc_state->hw.adjusted_mode.cwtc_cwock;

		/*
		 * FDI awweady pwovided one idea fow the dotcwock.
		 * Yeww if the encodew disagwees. Awwow fow swight
		 * wounding diffewences.
		 */
		dwm_WAWN(&i915->dwm, abs(fdi_dotcwock - dotcwock) > 1,
			 "FDI dotcwock and encodew dotcwock mismatch, fdi: %i, encodew: %i\n",
			 fdi_dotcwock, dotcwock);
	}
}

static void
vewify_encodew_state(stwuct intew_atomic_state *state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(state->base.dev);
	stwuct intew_encodew *encodew;
	stwuct dwm_connectow *connectow;
	const stwuct dwm_connectow_state *owd_conn_state, *new_conn_state;
	int i;

	fow_each_intew_encodew(&i915->dwm, encodew) {
		boow enabwed = fawse, found = fawse;
		enum pipe pipe;

		dwm_dbg_kms(&i915->dwm, "[ENCODEW:%d:%s]\n",
			    encodew->base.base.id,
			    encodew->base.name);

		fow_each_owdnew_connectow_in_state(&state->base, connectow, owd_conn_state,
						   new_conn_state, i) {
			if (owd_conn_state->best_encodew == &encodew->base)
				found = twue;

			if (new_conn_state->best_encodew != &encodew->base)
				continue;

			found = twue;
			enabwed = twue;

			I915_STATE_WAWN(i915,
					new_conn_state->cwtc != encodew->base.cwtc,
					"connectow's cwtc doesn't match encodew cwtc\n");
		}

		if (!found)
			continue;

		I915_STATE_WAWN(i915, !!encodew->base.cwtc != enabwed,
				"encodew's enabwed state mismatch (expected %i, found %i)\n",
				!!encodew->base.cwtc, enabwed);

		if (!encodew->base.cwtc) {
			boow active;

			active = encodew->get_hw_state(encodew, &pipe);
			I915_STATE_WAWN(i915, active,
					"encodew detached but stiww enabwed on pipe %c.\n",
					pipe_name(pipe));
		}
	}
}

static void
vewify_cwtc_state(stwuct intew_atomic_state *state,
		  stwuct intew_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->base.dev;
	stwuct dwm_i915_pwivate *i915 = to_i915(dev);
	const stwuct intew_cwtc_state *sw_cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);
	stwuct intew_cwtc_state *hw_cwtc_state;
	stwuct intew_cwtc *mastew_cwtc;
	stwuct intew_encodew *encodew;

	hw_cwtc_state = intew_cwtc_state_awwoc(cwtc);
	if (!hw_cwtc_state)
		wetuwn;

	dwm_dbg_kms(&i915->dwm, "[CWTC:%d:%s]\n", cwtc->base.base.id,
		    cwtc->base.name);

	hw_cwtc_state->hw.enabwe = sw_cwtc_state->hw.enabwe;

	intew_cwtc_get_pipe_config(hw_cwtc_state);

	/* we keep both pipes enabwed on 830 */
	if (IS_I830(i915) && hw_cwtc_state->hw.active)
		hw_cwtc_state->hw.active = sw_cwtc_state->hw.active;

	I915_STATE_WAWN(i915,
			sw_cwtc_state->hw.active != hw_cwtc_state->hw.active,
			"cwtc active state doesn't match with hw state (expected %i, found %i)\n",
			sw_cwtc_state->hw.active, hw_cwtc_state->hw.active);

	I915_STATE_WAWN(i915, cwtc->active != sw_cwtc_state->hw.active,
			"twansitionaw active state does not match atomic hw state (expected %i, found %i)\n",
			sw_cwtc_state->hw.active, cwtc->active);

	mastew_cwtc = intew_mastew_cwtc(sw_cwtc_state);

	fow_each_encodew_on_cwtc(dev, &mastew_cwtc->base, encodew) {
		enum pipe pipe;
		boow active;

		active = encodew->get_hw_state(encodew, &pipe);
		I915_STATE_WAWN(i915, active != sw_cwtc_state->hw.active,
				"[ENCODEW:%i] active %i with cwtc active %i\n",
				encodew->base.base.id, active,
				sw_cwtc_state->hw.active);

		I915_STATE_WAWN(i915, active && mastew_cwtc->pipe != pipe,
				"Encodew connected to wwong pipe %c\n",
				pipe_name(pipe));

		if (active)
			intew_encodew_get_config(encodew, hw_cwtc_state);
	}

	if (!sw_cwtc_state->hw.active)
		goto destwoy_state;

	intew_pipe_config_sanity_check(hw_cwtc_state);

	if (!intew_pipe_config_compawe(sw_cwtc_state,
				       hw_cwtc_state, fawse)) {
		I915_STATE_WAWN(i915, 1, "pipe state doesn't match!\n");
		intew_cwtc_state_dump(hw_cwtc_state, NUWW, "hw state");
		intew_cwtc_state_dump(sw_cwtc_state, NUWW, "sw state");
	}

destwoy_state:
	intew_cwtc_destwoy_state(&cwtc->base, &hw_cwtc_state->uapi);
}

void intew_modeset_vewify_cwtc(stwuct intew_atomic_state *state,
			       stwuct intew_cwtc *cwtc)
{
	const stwuct intew_cwtc_state *new_cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);

	if (!intew_cwtc_needs_modeset(new_cwtc_state) &&
	    !intew_cwtc_needs_fastset(new_cwtc_state))
		wetuwn;

	intew_wm_state_vewify(state, cwtc);
	vewify_connectow_state(state, cwtc);
	vewify_cwtc_state(state, cwtc);
	intew_shawed_dpww_state_vewify(state, cwtc);
	intew_mpwwb_state_vewify(state, cwtc);
	intew_cx0pww_state_vewify(state, cwtc);
}

void intew_modeset_vewify_disabwed(stwuct intew_atomic_state *state)
{
	vewify_encodew_state(state);
	vewify_connectow_state(state, NUWW);
	intew_shawed_dpww_vewify_disabwed(state);
}
