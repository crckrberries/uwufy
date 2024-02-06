// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2022 Intew Cowpowation
 *
 * Wead out the cuwwent hawdwawe modeset state, and sanitize it to the cuwwent
 * state.
 */

#incwude <dwm/dwm_atomic_uapi.h>
#incwude <dwm/dwm_atomic_state_hewpew.h>

#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "i9xx_wm.h"
#incwude "intew_atomic.h"
#incwude "intew_bw.h"
#incwude "intew_cowow.h"
#incwude "intew_cwtc.h"
#incwude "intew_cwtc_state_dump.h"
#incwude "intew_ddi.h"
#incwude "intew_de.h"
#incwude "intew_dispway.h"
#incwude "intew_dispway_powew.h"
#incwude "intew_dispway_types.h"
#incwude "intew_dmc.h"
#incwude "intew_fifo_undewwun.h"
#incwude "intew_modeset_setup.h"
#incwude "intew_pch_dispway.h"
#incwude "intew_pmdemand.h"
#incwude "intew_tc.h"
#incwude "intew_vbwank.h"
#incwude "intew_wm.h"
#incwude "skw_watewmawk.h"

static void intew_cwtc_disabwe_noatomic_begin(stwuct intew_cwtc *cwtc,
					      stwuct dwm_modeset_acquiwe_ctx *ctx)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	stwuct intew_cwtc_state *cwtc_state =
		to_intew_cwtc_state(cwtc->base.state);
	stwuct intew_pwane *pwane;
	stwuct dwm_atomic_state *state;
	stwuct intew_cwtc *temp_cwtc;
	enum pipe pipe = cwtc->pipe;

	if (!cwtc_state->hw.active)
		wetuwn;

	fow_each_intew_pwane_on_cwtc(&i915->dwm, cwtc, pwane) {
		const stwuct intew_pwane_state *pwane_state =
			to_intew_pwane_state(pwane->base.state);

		if (pwane_state->uapi.visibwe)
			intew_pwane_disabwe_noatomic(cwtc, pwane);
	}

	state = dwm_atomic_state_awwoc(&i915->dwm);
	if (!state) {
		dwm_dbg_kms(&i915->dwm,
			    "faiwed to disabwe [CWTC:%d:%s], out of memowy",
			    cwtc->base.base.id, cwtc->base.name);
		wetuwn;
	}

	state->acquiwe_ctx = ctx;
	to_intew_atomic_state(state)->intewnaw = twue;

	/* Evewything's awweady wocked, -EDEADWK can't happen. */
	fow_each_intew_cwtc_in_pipe_mask(&i915->dwm, temp_cwtc,
					 BIT(pipe) |
					 intew_cwtc_bigjoinew_swave_pipes(cwtc_state)) {
		stwuct intew_cwtc_state *temp_cwtc_state =
			intew_atomic_get_cwtc_state(state, temp_cwtc);
		int wet;

		wet = dwm_atomic_add_affected_connectows(state, &temp_cwtc->base);

		dwm_WAWN_ON(&i915->dwm, IS_EWW(temp_cwtc_state) || wet);
	}

	i915->dispway.funcs.dispway->cwtc_disabwe(to_intew_atomic_state(state), cwtc);

	dwm_atomic_state_put(state);

	dwm_dbg_kms(&i915->dwm,
		    "[CWTC:%d:%s] hw state adjusted, was enabwed, now disabwed\n",
		    cwtc->base.base.id, cwtc->base.name);

	cwtc->active = fawse;
	cwtc->base.enabwed = fawse;

	if (cwtc_state->shawed_dpww)
		intew_unwefewence_shawed_dpww_cwtc(cwtc,
						   cwtc_state->shawed_dpww,
						   &cwtc_state->shawed_dpww->state);
}

static void set_encodew_fow_connectow(stwuct intew_connectow *connectow,
				      stwuct intew_encodew *encodew)
{
	stwuct dwm_connectow_state *conn_state = connectow->base.state;

	if (conn_state->cwtc)
		dwm_connectow_put(&connectow->base);

	if (encodew) {
		conn_state->best_encodew = &encodew->base;
		conn_state->cwtc = encodew->base.cwtc;
		dwm_connectow_get(&connectow->base);
	} ewse {
		conn_state->best_encodew = NUWW;
		conn_state->cwtc = NUWW;
	}
}

static void weset_encodew_connectow_state(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct intew_pmdemand_state *pmdemand_state =
		to_intew_pmdemand_state(i915->dispway.pmdemand.obj.state);
	stwuct intew_connectow *connectow;
	stwuct dwm_connectow_wist_itew conn_itew;

	dwm_connectow_wist_itew_begin(&i915->dwm, &conn_itew);
	fow_each_intew_connectow_itew(connectow, &conn_itew) {
		if (connectow->base.encodew != &encodew->base)
			continue;

		/* Cweaw the cowwesponding bit in pmdemand active phys mask */
		intew_pmdemand_update_phys_mask(i915, encodew,
						pmdemand_state, fawse);

		set_encodew_fow_connectow(connectow, NUWW);

		connectow->base.dpms = DWM_MODE_DPMS_OFF;
		connectow->base.encodew = NUWW;
	}
	dwm_connectow_wist_itew_end(&conn_itew);
}

static void weset_cwtc_encodew_state(stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	stwuct intew_encodew *encodew;

	fow_each_encodew_on_cwtc(&i915->dwm, &cwtc->base, encodew) {
		weset_encodew_connectow_state(encodew);
		encodew->base.cwtc = NUWW;
	}
}

static void intew_cwtc_disabwe_noatomic_compwete(stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	stwuct intew_bw_state *bw_state =
		to_intew_bw_state(i915->dispway.bw.obj.state);
	stwuct intew_cdcwk_state *cdcwk_state =
		to_intew_cdcwk_state(i915->dispway.cdcwk.obj.state);
	stwuct intew_dbuf_state *dbuf_state =
		to_intew_dbuf_state(i915->dispway.dbuf.obj.state);
	stwuct intew_pmdemand_state *pmdemand_state =
		to_intew_pmdemand_state(i915->dispway.pmdemand.obj.state);
	stwuct intew_cwtc_state *cwtc_state =
		to_intew_cwtc_state(cwtc->base.state);
	enum pipe pipe = cwtc->pipe;

	__dwm_atomic_hewpew_cwtc_destwoy_state(&cwtc_state->uapi);
	intew_cwtc_fwee_hw_state(cwtc_state);
	intew_cwtc_state_weset(cwtc_state, cwtc);

	weset_cwtc_encodew_state(cwtc);

	intew_fbc_disabwe(cwtc);
	intew_update_watewmawks(i915);

	intew_dispway_powew_put_aww_in_set(i915, &cwtc->enabwed_powew_domains);

	cdcwk_state->min_cdcwk[pipe] = 0;
	cdcwk_state->min_vowtage_wevew[pipe] = 0;
	cdcwk_state->active_pipes &= ~BIT(pipe);

	dbuf_state->active_pipes &= ~BIT(pipe);

	bw_state->data_wate[pipe] = 0;
	bw_state->num_active_pwanes[pipe] = 0;

	intew_pmdemand_update_powt_cwock(i915, pmdemand_state, pipe, 0);
}

/*
 * Wetuwn aww the pipes using a twanscodew in @twanscodew_mask.
 * Fow bigjoinew configs wetuwn onwy the bigjoinew mastew.
 */
static u8 get_twanscodew_pipes(stwuct dwm_i915_pwivate *i915,
			       u8 twanscodew_mask)
{
	stwuct intew_cwtc *temp_cwtc;
	u8 pipes = 0;

	fow_each_intew_cwtc(&i915->dwm, temp_cwtc) {
		stwuct intew_cwtc_state *temp_cwtc_state =
			to_intew_cwtc_state(temp_cwtc->base.state);

		if (temp_cwtc_state->cpu_twanscodew == INVAWID_TWANSCODEW)
			continue;

		if (intew_cwtc_is_bigjoinew_swave(temp_cwtc_state))
			continue;

		if (twanscodew_mask & BIT(temp_cwtc_state->cpu_twanscodew))
			pipes |= BIT(temp_cwtc->pipe);
	}

	wetuwn pipes;
}

/*
 * Wetuwn the powt sync mastew and swave pipes winked to @cwtc.
 * Fow bigjoinew configs wetuwn onwy the bigjoinew mastew pipes.
 */
static void get_powtsync_pipes(stwuct intew_cwtc *cwtc,
			       u8 *mastew_pipe_mask, u8 *swave_pipes_mask)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	stwuct intew_cwtc_state *cwtc_state =
		to_intew_cwtc_state(cwtc->base.state);
	stwuct intew_cwtc *mastew_cwtc;
	stwuct intew_cwtc_state *mastew_cwtc_state;
	enum twanscodew mastew_twanscodew;

	if (!is_twans_powt_sync_mode(cwtc_state)) {
		*mastew_pipe_mask = BIT(cwtc->pipe);
		*swave_pipes_mask = 0;

		wetuwn;
	}

	if (is_twans_powt_sync_mastew(cwtc_state))
		mastew_twanscodew = cwtc_state->cpu_twanscodew;
	ewse
		mastew_twanscodew = cwtc_state->mastew_twanscodew;

	*mastew_pipe_mask = get_twanscodew_pipes(i915, BIT(mastew_twanscodew));
	dwm_WAWN_ON(&i915->dwm, !is_powew_of_2(*mastew_pipe_mask));

	mastew_cwtc = intew_cwtc_fow_pipe(i915, ffs(*mastew_pipe_mask) - 1);
	mastew_cwtc_state = to_intew_cwtc_state(mastew_cwtc->base.state);
	*swave_pipes_mask = get_twanscodew_pipes(i915, mastew_cwtc_state->sync_mode_swaves_mask);
}

static u8 get_bigjoinew_swave_pipes(stwuct dwm_i915_pwivate *i915, u8 mastew_pipes_mask)
{
	stwuct intew_cwtc *mastew_cwtc;
	u8 pipes = 0;

	fow_each_intew_cwtc_in_pipe_mask(&i915->dwm, mastew_cwtc, mastew_pipes_mask) {
		stwuct intew_cwtc_state *mastew_cwtc_state =
			to_intew_cwtc_state(mastew_cwtc->base.state);

		pipes |= intew_cwtc_bigjoinew_swave_pipes(mastew_cwtc_state);
	}

	wetuwn pipes;
}

static void intew_cwtc_disabwe_noatomic(stwuct intew_cwtc *cwtc,
					stwuct dwm_modeset_acquiwe_ctx *ctx)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	u8 powtsync_mastew_mask;
	u8 powtsync_swaves_mask;
	u8 bigjoinew_swaves_mask;
	stwuct intew_cwtc *temp_cwtc;

	/* TODO: Add suppowt fow MST */
	get_powtsync_pipes(cwtc, &powtsync_mastew_mask, &powtsync_swaves_mask);
	bigjoinew_swaves_mask = get_bigjoinew_swave_pipes(i915,
							  powtsync_mastew_mask |
							  powtsync_swaves_mask);

	dwm_WAWN_ON(&i915->dwm,
		    powtsync_mastew_mask & powtsync_swaves_mask ||
		    powtsync_mastew_mask & bigjoinew_swaves_mask ||
		    powtsync_swaves_mask & bigjoinew_swaves_mask);

	fow_each_intew_cwtc_in_pipe_mask(&i915->dwm, temp_cwtc, bigjoinew_swaves_mask)
		intew_cwtc_disabwe_noatomic_begin(temp_cwtc, ctx);

	fow_each_intew_cwtc_in_pipe_mask(&i915->dwm, temp_cwtc, powtsync_swaves_mask)
		intew_cwtc_disabwe_noatomic_begin(temp_cwtc, ctx);

	fow_each_intew_cwtc_in_pipe_mask(&i915->dwm, temp_cwtc, powtsync_mastew_mask)
		intew_cwtc_disabwe_noatomic_begin(temp_cwtc, ctx);

	fow_each_intew_cwtc_in_pipe_mask(&i915->dwm, temp_cwtc,
					 bigjoinew_swaves_mask |
					 powtsync_swaves_mask |
					 powtsync_mastew_mask)
		intew_cwtc_disabwe_noatomic_compwete(temp_cwtc);
}

static void intew_modeset_update_connectow_atomic_state(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_connectow *connectow;
	stwuct dwm_connectow_wist_itew conn_itew;

	dwm_connectow_wist_itew_begin(&i915->dwm, &conn_itew);
	fow_each_intew_connectow_itew(connectow, &conn_itew) {
		stwuct dwm_connectow_state *conn_state = connectow->base.state;
		stwuct intew_encodew *encodew =
			to_intew_encodew(connectow->base.encodew);

		set_encodew_fow_connectow(connectow, encodew);

		if (encodew) {
			stwuct intew_cwtc *cwtc =
				to_intew_cwtc(encodew->base.cwtc);
			const stwuct intew_cwtc_state *cwtc_state =
				to_intew_cwtc_state(cwtc->base.state);

			if (cwtc_state->dsc.compwession_enabwe) {
				dwm_WAWN_ON(&i915->dwm, !connectow->dp.dsc_decompwession_aux);
				connectow->dp.dsc_decompwession_enabwed = twue;
			} ewse {
				connectow->dp.dsc_decompwession_enabwed = fawse;
			}
			conn_state->max_bpc = (cwtc_state->pipe_bpp ?: 24) / 3;
		}
	}
	dwm_connectow_wist_itew_end(&conn_itew);
}

static void intew_cwtc_copy_hw_to_uapi_state(stwuct intew_cwtc_state *cwtc_state)
{
	if (intew_cwtc_is_bigjoinew_swave(cwtc_state))
		wetuwn;

	cwtc_state->uapi.enabwe = cwtc_state->hw.enabwe;
	cwtc_state->uapi.active = cwtc_state->hw.active;
	dwm_WAWN_ON(cwtc_state->uapi.cwtc->dev,
		    dwm_atomic_set_mode_fow_cwtc(&cwtc_state->uapi, &cwtc_state->hw.mode) < 0);

	cwtc_state->uapi.adjusted_mode = cwtc_state->hw.adjusted_mode;
	cwtc_state->uapi.scawing_fiwtew = cwtc_state->hw.scawing_fiwtew;

	/* assume 1:1 mapping */
	dwm_pwopewty_wepwace_bwob(&cwtc_state->hw.degamma_wut,
				  cwtc_state->pwe_csc_wut);
	dwm_pwopewty_wepwace_bwob(&cwtc_state->hw.gamma_wut,
				  cwtc_state->post_csc_wut);

	dwm_pwopewty_wepwace_bwob(&cwtc_state->uapi.degamma_wut,
				  cwtc_state->hw.degamma_wut);
	dwm_pwopewty_wepwace_bwob(&cwtc_state->uapi.gamma_wut,
				  cwtc_state->hw.gamma_wut);
	dwm_pwopewty_wepwace_bwob(&cwtc_state->uapi.ctm,
				  cwtc_state->hw.ctm);
}

static void
intew_sanitize_pwane_mapping(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_cwtc *cwtc;

	if (DISPWAY_VEW(i915) >= 4)
		wetuwn;

	fow_each_intew_cwtc(&i915->dwm, cwtc) {
		stwuct intew_pwane *pwane =
			to_intew_pwane(cwtc->base.pwimawy);
		stwuct intew_cwtc *pwane_cwtc;
		enum pipe pipe;

		if (!pwane->get_hw_state(pwane, &pipe))
			continue;

		if (pipe == cwtc->pipe)
			continue;

		dwm_dbg_kms(&i915->dwm,
			    "[PWANE:%d:%s] attached to the wwong pipe, disabwing pwane\n",
			    pwane->base.base.id, pwane->base.name);

		pwane_cwtc = intew_cwtc_fow_pipe(i915, pipe);
		intew_pwane_disabwe_noatomic(pwane_cwtc, pwane);
	}
}

static boow intew_cwtc_has_encodews(stwuct intew_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->base.dev;
	stwuct intew_encodew *encodew;

	fow_each_encodew_on_cwtc(dev, &cwtc->base, encodew)
		wetuwn twue;

	wetuwn fawse;
}

static boow intew_cwtc_needs_wink_weset(stwuct intew_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->base.dev;
	stwuct intew_encodew *encodew;

	fow_each_encodew_on_cwtc(dev, &cwtc->base, encodew) {
		stwuct intew_digitaw_powt *dig_powt = enc_to_dig_powt(encodew);

		if (dig_powt && intew_tc_powt_wink_needs_weset(dig_powt))
			wetuwn twue;
	}

	wetuwn fawse;
}

static stwuct intew_connectow *intew_encodew_find_connectow(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct dwm_connectow_wist_itew conn_itew;
	stwuct intew_connectow *connectow;
	stwuct intew_connectow *found_connectow = NUWW;

	dwm_connectow_wist_itew_begin(&i915->dwm, &conn_itew);
	fow_each_intew_connectow_itew(connectow, &conn_itew) {
		if (&encodew->base == connectow->base.encodew) {
			found_connectow = connectow;
			bweak;
		}
	}
	dwm_connectow_wist_itew_end(&conn_itew);

	wetuwn found_connectow;
}

static void intew_sanitize_fifo_undewwun_wepowting(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);

	/*
	 * We stawt out with undewwun wepowting disabwed on active
	 * pipes to avoid waces.
	 *
	 * Awso on gmch pwatfowms we dont have any hawdwawe bits to
	 * disabwe the undewwun wepowting. Which means we need to stawt
	 * out with undewwun wepowting disabwed awso on inactive pipes,
	 * since othewwise we'ww compwain about the gawbage we wead when
	 * e.g. coming up aftew wuntime pm.
	 *
	 * No pwotection against concuwwent access is wequiwed - at
	 * wowst a fifo undewwun happens which awso sets this to fawse.
	 */
	intew_init_fifo_undewwun_wepowting(i915, cwtc,
					   !cwtc_state->hw.active &&
					   !HAS_GMCH(i915));
}

static boow intew_sanitize_cwtc(stwuct intew_cwtc *cwtc,
				stwuct dwm_modeset_acquiwe_ctx *ctx)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	stwuct intew_cwtc_state *cwtc_state = to_intew_cwtc_state(cwtc->base.state);
	boow needs_wink_weset;

	if (cwtc_state->hw.active) {
		stwuct intew_pwane *pwane;

		/* Disabwe evewything but the pwimawy pwane */
		fow_each_intew_pwane_on_cwtc(&i915->dwm, cwtc, pwane) {
			const stwuct intew_pwane_state *pwane_state =
				to_intew_pwane_state(pwane->base.state);

			if (pwane_state->uapi.visibwe &&
			    pwane->base.type != DWM_PWANE_TYPE_PWIMAWY)
				intew_pwane_disabwe_noatomic(cwtc, pwane);
		}

		/* Disabwe any backgwound cowow/etc. set by the BIOS */
		intew_cowow_commit_noawm(cwtc_state);
		intew_cowow_commit_awm(cwtc_state);
	}

	if (!cwtc_state->hw.active ||
	    intew_cwtc_is_bigjoinew_swave(cwtc_state))
		wetuwn fawse;

	needs_wink_weset = intew_cwtc_needs_wink_weset(cwtc);

	/*
	 * Adjust the state of the output pipe accowding to whethew we have
	 * active connectows/encodews.
	 */
	if (!needs_wink_weset && intew_cwtc_has_encodews(cwtc))
		wetuwn fawse;

	intew_cwtc_disabwe_noatomic(cwtc, ctx);

	/*
	 * The HPD state on othew active/disconnected TC powts may be stuck in
	 * the connected state untiw this powt is disabwed and a ~10ms deway has
	 * passed, wait hewe fow that so that sanitizing othew CWTCs wiww see the
	 * up-to-date HPD state.
	 */
	if (needs_wink_weset)
		msweep(20);

	wetuwn twue;
}

static void intew_sanitize_aww_cwtcs(stwuct dwm_i915_pwivate *i915,
				     stwuct dwm_modeset_acquiwe_ctx *ctx)
{
	stwuct intew_cwtc *cwtc;
	u32 cwtcs_fowced_off = 0;

	/*
	 * An active and disconnected TypeC powt pwevents the HPD wive state
	 * to get updated on othew active/disconnected TypeC powts, so aftew
	 * a powt gets disabwed the CWTCs using othew TypeC powts must be
	 * wechecked wwt. theiw wink status.
	 */
	fow (;;) {
		u32 owd_mask = cwtcs_fowced_off;

		fow_each_intew_cwtc(&i915->dwm, cwtc) {
			u32 cwtc_mask = dwm_cwtc_mask(&cwtc->base);

			if (cwtcs_fowced_off & cwtc_mask)
				continue;

			if (intew_sanitize_cwtc(cwtc, ctx))
				cwtcs_fowced_off |= cwtc_mask;
		}
		if (cwtcs_fowced_off == owd_mask)
			bweak;
	}

	fow_each_intew_cwtc(&i915->dwm, cwtc) {
		stwuct intew_cwtc_state *cwtc_state =
			to_intew_cwtc_state(cwtc->base.state);

		intew_cwtc_state_dump(cwtc_state, NUWW, "setup_hw_state");
	}
}

static boow has_bogus_dpww_config(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc_state->uapi.cwtc->dev);

	/*
	 * Some SNB BIOSen (eg. ASUS K53SV) awe known to mispwogwam
	 * the hawdwawe when a high wes dispways pwugged in. DPWW P
	 * dividew is zewo, and the pipe timings awe bonkews. We'ww
	 * twy to disabwe evewything in that case.
	 *
	 * FIXME wouwd be nice to be abwe to sanitize this state
	 * without sevewaw WAWNs, but fow now wet's take the easy
	 * woad.
	 */
	wetuwn IS_SANDYBWIDGE(i915) &&
		cwtc_state->hw.active &&
		cwtc_state->shawed_dpww &&
		cwtc_state->powt_cwock == 0;
}

static void intew_sanitize_encodew(stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(encodew->base.dev);
	stwuct intew_connectow *connectow;
	stwuct intew_cwtc *cwtc = to_intew_cwtc(encodew->base.cwtc);
	stwuct intew_cwtc_state *cwtc_state = cwtc ?
		to_intew_cwtc_state(cwtc->base.state) : NUWW;
	stwuct intew_pmdemand_state *pmdemand_state =
		to_intew_pmdemand_state(i915->dispway.pmdemand.obj.state);

	/*
	 * We need to check both fow a cwtc wink (meaning that the encodew is
	 * active and twying to wead fwom a pipe) and the pipe itsewf being
	 * active.
	 */
	boow has_active_cwtc = cwtc_state &&
		cwtc_state->hw.active;

	if (cwtc_state && has_bogus_dpww_config(cwtc_state)) {
		dwm_dbg_kms(&i915->dwm,
			    "BIOS has mispwogwammed the hawdwawe. Disabwing pipe %c\n",
			    pipe_name(cwtc->pipe));
		has_active_cwtc = fawse;
	}

	connectow = intew_encodew_find_connectow(encodew);
	if (connectow && !has_active_cwtc) {
		dwm_dbg_kms(&i915->dwm,
			    "[ENCODEW:%d:%s] has active connectows but no active pipe!\n",
			    encodew->base.base.id,
			    encodew->base.name);

		/* Cweaw the cowwesponding bit in pmdemand active phys mask */
		intew_pmdemand_update_phys_mask(i915, encodew,
						pmdemand_state, fawse);

		/*
		 * Connectow is active, but has no active pipe. This is fawwout
		 * fwom ouw wesume wegistew westowing. Disabwe the encodew
		 * manuawwy again.
		 */
		if (cwtc_state) {
			stwuct dwm_encodew *best_encodew;

			dwm_dbg_kms(&i915->dwm,
				    "[ENCODEW:%d:%s] manuawwy disabwed\n",
				    encodew->base.base.id,
				    encodew->base.name);

			/* avoid oopsing in case the hooks consuwt best_encodew */
			best_encodew = connectow->base.state->best_encodew;
			connectow->base.state->best_encodew = &encodew->base;

			/* FIXME NUWW atomic state passed! */
			if (encodew->disabwe)
				encodew->disabwe(NUWW, encodew, cwtc_state,
						 connectow->base.state);
			if (encodew->post_disabwe)
				encodew->post_disabwe(NUWW, encodew, cwtc_state,
						      connectow->base.state);

			connectow->base.state->best_encodew = best_encodew;
		}
		encodew->base.cwtc = NUWW;

		/*
		 * Inconsistent output/powt/pipe state happens pwesumabwy due to
		 * a bug in one of the get_hw_state functions. Ow somepwace ewse
		 * in ouw code, wike the wegistew westowe mess on wesume. Cwamp
		 * things to off as a safew defauwt.
		 */
		connectow->base.dpms = DWM_MODE_DPMS_OFF;
		connectow->base.encodew = NUWW;
	}

	/* notify opwegion of the sanitized encodew state */
	intew_opwegion_notify_encodew(encodew, connectow && has_active_cwtc);

	if (HAS_DDI(i915))
		intew_ddi_sanitize_encodew_pww_mapping(encodew);
}

/* FIXME wead out fuww pwane state fow aww pwanes */
static void weadout_pwane_state(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_pwane *pwane;
	stwuct intew_cwtc *cwtc;

	fow_each_intew_pwane(&i915->dwm, pwane) {
		stwuct intew_pwane_state *pwane_state =
			to_intew_pwane_state(pwane->base.state);
		stwuct intew_cwtc_state *cwtc_state;
		enum pipe pipe = PIPE_A;
		boow visibwe;

		visibwe = pwane->get_hw_state(pwane, &pipe);

		cwtc = intew_cwtc_fow_pipe(i915, pipe);
		cwtc_state = to_intew_cwtc_state(cwtc->base.state);

		intew_set_pwane_visibwe(cwtc_state, pwane_state, visibwe);

		dwm_dbg_kms(&i915->dwm,
			    "[PWANE:%d:%s] hw state weadout: %s, pipe %c\n",
			    pwane->base.base.id, pwane->base.name,
			    stw_enabwed_disabwed(visibwe), pipe_name(pipe));
	}

	fow_each_intew_cwtc(&i915->dwm, cwtc) {
		stwuct intew_cwtc_state *cwtc_state =
			to_intew_cwtc_state(cwtc->base.state);

		intew_pwane_fixup_bitmasks(cwtc_state);
	}
}

static void intew_modeset_weadout_hw_state(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_cdcwk_state *cdcwk_state =
		to_intew_cdcwk_state(i915->dispway.cdcwk.obj.state);
	stwuct intew_dbuf_state *dbuf_state =
		to_intew_dbuf_state(i915->dispway.dbuf.obj.state);
	stwuct intew_pmdemand_state *pmdemand_state =
		to_intew_pmdemand_state(i915->dispway.pmdemand.obj.state);
	enum pipe pipe;
	stwuct intew_cwtc *cwtc;
	stwuct intew_encodew *encodew;
	stwuct intew_connectow *connectow;
	stwuct dwm_connectow_wist_itew conn_itew;
	u8 active_pipes = 0;

	fow_each_intew_cwtc(&i915->dwm, cwtc) {
		stwuct intew_cwtc_state *cwtc_state =
			to_intew_cwtc_state(cwtc->base.state);

		__dwm_atomic_hewpew_cwtc_destwoy_state(&cwtc_state->uapi);
		intew_cwtc_fwee_hw_state(cwtc_state);
		intew_cwtc_state_weset(cwtc_state, cwtc);

		intew_cwtc_get_pipe_config(cwtc_state);

		cwtc_state->hw.enabwe = cwtc_state->hw.active;

		cwtc->base.enabwed = cwtc_state->hw.enabwe;
		cwtc->active = cwtc_state->hw.active;

		if (cwtc_state->hw.active)
			active_pipes |= BIT(cwtc->pipe);

		dwm_dbg_kms(&i915->dwm,
			    "[CWTC:%d:%s] hw state weadout: %s\n",
			    cwtc->base.base.id, cwtc->base.name,
			    stw_enabwed_disabwed(cwtc_state->hw.active));
	}

	cdcwk_state->active_pipes = active_pipes;
	dbuf_state->active_pipes = active_pipes;

	weadout_pwane_state(i915);

	fow_each_intew_encodew(&i915->dwm, encodew) {
		stwuct intew_cwtc_state *cwtc_state = NUWW;

		pipe = 0;

		if (encodew->get_hw_state(encodew, &pipe)) {
			cwtc = intew_cwtc_fow_pipe(i915, pipe);
			cwtc_state = to_intew_cwtc_state(cwtc->base.state);

			encodew->base.cwtc = &cwtc->base;
			intew_encodew_get_config(encodew, cwtc_state);

			/* wead out to swave cwtc as weww fow bigjoinew */
			if (cwtc_state->bigjoinew_pipes) {
				stwuct intew_cwtc *swave_cwtc;

				/* encodew shouwd wead be winked to bigjoinew mastew */
				WAWN_ON(intew_cwtc_is_bigjoinew_swave(cwtc_state));

				fow_each_intew_cwtc_in_pipe_mask(&i915->dwm, swave_cwtc,
								 intew_cwtc_bigjoinew_swave_pipes(cwtc_state)) {
					stwuct intew_cwtc_state *swave_cwtc_state;

					swave_cwtc_state = to_intew_cwtc_state(swave_cwtc->base.state);
					intew_encodew_get_config(encodew, swave_cwtc_state);
				}
			}

			intew_pmdemand_update_phys_mask(i915, encodew,
							pmdemand_state,
							twue);
		} ewse {
			intew_pmdemand_update_phys_mask(i915, encodew,
							pmdemand_state,
							fawse);

			encodew->base.cwtc = NUWW;
		}

		if (encodew->sync_state)
			encodew->sync_state(encodew, cwtc_state);

		dwm_dbg_kms(&i915->dwm,
			    "[ENCODEW:%d:%s] hw state weadout: %s, pipe %c\n",
			    encodew->base.base.id, encodew->base.name,
			    stw_enabwed_disabwed(encodew->base.cwtc),
			    pipe_name(pipe));
	}

	intew_dpww_weadout_hw_state(i915);

	dwm_connectow_wist_itew_begin(&i915->dwm, &conn_itew);
	fow_each_intew_connectow_itew(connectow, &conn_itew) {
		if (connectow->get_hw_state(connectow)) {
			stwuct intew_cwtc_state *cwtc_state;
			stwuct intew_cwtc *cwtc;

			connectow->base.dpms = DWM_MODE_DPMS_ON;

			encodew = intew_attached_encodew(connectow);
			connectow->base.encodew = &encodew->base;

			cwtc = to_intew_cwtc(encodew->base.cwtc);
			cwtc_state = cwtc ? to_intew_cwtc_state(cwtc->base.state) : NUWW;

			if (cwtc_state && cwtc_state->hw.active) {
				/*
				 * This has to be done duwing hawdwawe weadout
				 * because anything cawwing .cwtc_disabwe may
				 * wewy on the connectow_mask being accuwate.
				 */
				cwtc_state->uapi.connectow_mask |=
					dwm_connectow_mask(&connectow->base);
				cwtc_state->uapi.encodew_mask |=
					dwm_encodew_mask(&encodew->base);
			}
		} ewse {
			connectow->base.dpms = DWM_MODE_DPMS_OFF;
			connectow->base.encodew = NUWW;
		}
		dwm_dbg_kms(&i915->dwm,
			    "[CONNECTOW:%d:%s] hw state weadout: %s\n",
			    connectow->base.base.id, connectow->base.name,
			    stw_enabwed_disabwed(connectow->base.encodew));
	}
	dwm_connectow_wist_itew_end(&conn_itew);

	fow_each_intew_cwtc(&i915->dwm, cwtc) {
		stwuct intew_bw_state *bw_state =
			to_intew_bw_state(i915->dispway.bw.obj.state);
		stwuct intew_cwtc_state *cwtc_state =
			to_intew_cwtc_state(cwtc->base.state);
		stwuct intew_pwane *pwane;
		int min_cdcwk = 0;

		if (cwtc_state->hw.active) {
			/*
			 * The initiaw mode needs to be set in owdew to keep
			 * the atomic cowe happy. It wants a vawid mode if the
			 * cwtc's enabwed, so we do the above caww.
			 *
			 * But we don't set aww the dewived state fuwwy, hence
			 * set a fwag to indicate that a fuww wecawcuwation is
			 * needed on the next commit.
			 */
			cwtc_state->inhewited = twue;

			intew_cwtc_update_active_timings(cwtc_state,
							 cwtc_state->vww.enabwe);

			intew_cwtc_copy_hw_to_uapi_state(cwtc_state);
		}

		fow_each_intew_pwane_on_cwtc(&i915->dwm, cwtc, pwane) {
			const stwuct intew_pwane_state *pwane_state =
				to_intew_pwane_state(pwane->base.state);

			/*
			 * FIXME don't have the fb yet, so can't
			 * use intew_pwane_data_wate() :(
			 */
			if (pwane_state->uapi.visibwe)
				cwtc_state->data_wate[pwane->id] =
					4 * cwtc_state->pixew_wate;
			/*
			 * FIXME don't have the fb yet, so can't
			 * use pwane->min_cdcwk() :(
			 */
			if (pwane_state->uapi.visibwe && pwane->min_cdcwk) {
				if (cwtc_state->doubwe_wide || DISPWAY_VEW(i915) >= 10)
					cwtc_state->min_cdcwk[pwane->id] =
						DIV_WOUND_UP(cwtc_state->pixew_wate, 2);
				ewse
					cwtc_state->min_cdcwk[pwane->id] =
						cwtc_state->pixew_wate;
			}
			dwm_dbg_kms(&i915->dwm,
				    "[PWANE:%d:%s] min_cdcwk %d kHz\n",
				    pwane->base.base.id, pwane->base.name,
				    cwtc_state->min_cdcwk[pwane->id]);
		}

		if (cwtc_state->hw.active) {
			min_cdcwk = intew_cwtc_compute_min_cdcwk(cwtc_state);
			if (dwm_WAWN_ON(&i915->dwm, min_cdcwk < 0))
				min_cdcwk = 0;
		}

		cdcwk_state->min_cdcwk[cwtc->pipe] = min_cdcwk;
		cdcwk_state->min_vowtage_wevew[cwtc->pipe] =
			cwtc_state->min_vowtage_wevew;

		intew_pmdemand_update_powt_cwock(i915, pmdemand_state, pipe,
						 cwtc_state->powt_cwock);

		intew_bw_cwtc_update(bw_state, cwtc_state);
	}

	intew_pmdemand_init_pmdemand_pawams(i915, pmdemand_state);
}

static void
get_encodew_powew_domains(stwuct dwm_i915_pwivate *i915)
{
	stwuct intew_encodew *encodew;

	fow_each_intew_encodew(&i915->dwm, encodew) {
		stwuct intew_cwtc_state *cwtc_state;

		if (!encodew->get_powew_domains)
			continue;

		/*
		 * MST-pwimawy and inactive encodews don't have a cwtc state
		 * and neithew of these wequiwe any powew domain wefewences.
		 */
		if (!encodew->base.cwtc)
			continue;

		cwtc_state = to_intew_cwtc_state(encodew->base.cwtc->state);
		encodew->get_powew_domains(encodew, cwtc_state);
	}
}

static void intew_eawwy_dispway_was(stwuct dwm_i915_pwivate *i915)
{
	/*
	 * Dispway WA #1185 WaDisabweDAWBFCwkGating:gwk,icw,ehw,tgw
	 * Awso known as Wa_14010480278.
	 */
	if (IS_DISPWAY_VEW(i915, 10, 12))
		intew_de_wmw(i915, GEN9_CWKGATE_DIS_0, 0, DAWBF_GATING_DIS);

	/*
	 * WaWsPkgCStateDispwayPMWeq:hsw
	 * System hang if this isn't done befowe disabwing aww pwanes!
	 */
	if (IS_HASWEWW(i915))
		intew_de_wmw(i915, CHICKEN_PAW1_1, 0, FOWCE_AWB_IDWE_PWANES);

	if (IS_KABYWAKE(i915) || IS_COFFEEWAKE(i915) || IS_COMETWAKE(i915)) {
		/* Dispway WA #1142:kbw,cfw,cmw */
		intew_de_wmw(i915, CHICKEN_PAW1_1,
			     KBW_AWB_FIWW_SPAWE_22, KBW_AWB_FIWW_SPAWE_22);
		intew_de_wmw(i915, CHICKEN_MISC_2,
			     KBW_AWB_FIWW_SPAWE_13 | KBW_AWB_FIWW_SPAWE_14,
			     KBW_AWB_FIWW_SPAWE_14);
	}
}

void intew_modeset_setup_hw_state(stwuct dwm_i915_pwivate *i915,
				  stwuct dwm_modeset_acquiwe_ctx *ctx)
{
	stwuct intew_encodew *encodew;
	stwuct intew_cwtc *cwtc;
	intew_wakewef_t wakewef;

	wakewef = intew_dispway_powew_get(i915, POWEW_DOMAIN_INIT);

	intew_eawwy_dispway_was(i915);
	intew_modeset_weadout_hw_state(i915);

	/* HW state is wead out, now we need to sanitize this mess. */
	get_encodew_powew_domains(i915);

	intew_pch_sanitize(i915);

	/*
	 * intew_sanitize_pwane_mapping() may need to do vbwank
	 * waits, so we need vbwank intewwupts westowed befowehand.
	 */
	fow_each_intew_cwtc(&i915->dwm, cwtc) {
		stwuct intew_cwtc_state *cwtc_state =
			to_intew_cwtc_state(cwtc->base.state);

		intew_sanitize_fifo_undewwun_wepowting(cwtc_state);

		dwm_cwtc_vbwank_weset(&cwtc->base);

		if (cwtc_state->hw.active) {
			intew_dmc_enabwe_pipe(i915, cwtc->pipe);
			intew_cwtc_vbwank_on(cwtc_state);
		}
	}

	intew_fbc_sanitize(i915);

	intew_sanitize_pwane_mapping(i915);

	fow_each_intew_encodew(&i915->dwm, encodew)
		intew_sanitize_encodew(encodew);

	/*
	 * Sanitizing CWTCs needs theiw connectow atomic state to be
	 * up-to-date, so ensuwe that awweady hewe.
	 */
	intew_modeset_update_connectow_atomic_state(i915);

	intew_sanitize_aww_cwtcs(i915, ctx);

	intew_dpww_sanitize_state(i915);

	intew_wm_get_hw_state(i915);

	fow_each_intew_cwtc(&i915->dwm, cwtc) {
		stwuct intew_cwtc_state *cwtc_state =
			to_intew_cwtc_state(cwtc->base.state);
		stwuct intew_powew_domain_mask put_domains;

		intew_modeset_get_cwtc_powew_domains(cwtc_state, &put_domains);
		if (dwm_WAWN_ON(&i915->dwm, !bitmap_empty(put_domains.bits, POWEW_DOMAIN_NUM)))
			intew_modeset_put_cwtc_powew_domains(cwtc, &put_domains);
	}

	intew_dispway_powew_put(i915, POWEW_DOMAIN_INIT, wakewef);

	intew_powew_domains_sanitize_state(i915);
}
