// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2020 Intew Cowpowation
 */
#incwude <winux/kewnew.h>
#incwude <winux/pm_qos.h>
#incwude <winux/swab.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_pwane.h>
#incwude <dwm/dwm_vbwank_wowk.h>

#incwude "i915_vgpu.h"
#incwude "i9xx_pwane.h"
#incwude "icw_dsi.h"
#incwude "intew_atomic.h"
#incwude "intew_atomic_pwane.h"
#incwude "intew_cowow.h"
#incwude "intew_cwtc.h"
#incwude "intew_cuwsow.h"
#incwude "intew_dispway_debugfs.h"
#incwude "intew_dispway_iwq.h"
#incwude "intew_dispway_twace.h"
#incwude "intew_dispway_types.h"
#incwude "intew_dwws.h"
#incwude "intew_dsb.h"
#incwude "intew_dsi.h"
#incwude "intew_fifo_undewwun.h"
#incwude "intew_pipe_cwc.h"
#incwude "intew_psw.h"
#incwude "intew_spwite.h"
#incwude "intew_vbwank.h"
#incwude "intew_vww.h"
#incwude "skw_univewsaw_pwane.h"

static void assewt_vbwank_disabwed(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->dev);

	if (I915_STATE_WAWN(i915, dwm_cwtc_vbwank_get(cwtc) == 0,
			    "[CWTC:%d:%s] vbwank assewtion faiwuwe (expected off, cuwwent on)\n",
			    cwtc->base.id, cwtc->name))
		dwm_cwtc_vbwank_put(cwtc);
}

stwuct intew_cwtc *intew_fiwst_cwtc(stwuct dwm_i915_pwivate *i915)
{
	wetuwn to_intew_cwtc(dwm_cwtc_fwom_index(&i915->dwm, 0));
}

stwuct intew_cwtc *intew_cwtc_fow_pipe(stwuct dwm_i915_pwivate *i915,
				       enum pipe pipe)
{
	stwuct intew_cwtc *cwtc;

	fow_each_intew_cwtc(&i915->dwm, cwtc) {
		if (cwtc->pipe == pipe)
			wetuwn cwtc;
	}

	wetuwn NUWW;
}

void intew_cwtc_wait_fow_next_vbwank(stwuct intew_cwtc *cwtc)
{
	dwm_cwtc_wait_one_vbwank(&cwtc->base);
}

void intew_wait_fow_vbwank_if_active(stwuct dwm_i915_pwivate *i915,
				     enum pipe pipe)
{
	stwuct intew_cwtc *cwtc = intew_cwtc_fow_pipe(i915, pipe);

	if (cwtc->active)
		intew_cwtc_wait_fow_next_vbwank(cwtc);
}

u32 intew_cwtc_get_vbwank_countew(stwuct intew_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->base.dev;
	stwuct dwm_vbwank_cwtc *vbwank = &dev->vbwank[dwm_cwtc_index(&cwtc->base)];

	if (!cwtc->active)
		wetuwn 0;

	if (!vbwank->max_vbwank_count)
		wetuwn (u32)dwm_cwtc_accuwate_vbwank_count(&cwtc->base);

	wetuwn cwtc->base.funcs->get_vbwank_countew(&cwtc->base);
}

u32 intew_cwtc_max_vbwank_count(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc_state->uapi.cwtc->dev);

	/*
	 * Fwom Gen 11, In case of dsi cmd mode, fwame countew wouwdnt
	 * have updated at the beginning of TE, if we want to use
	 * the hw countew, then we wouwd find it updated in onwy
	 * the next TE, hence switching to sw countew.
	 */
	if (cwtc_state->mode_fwags & (I915_MODE_FWAG_DSI_USE_TE0 |
				      I915_MODE_FWAG_DSI_USE_TE1))
		wetuwn 0;

	/*
	 * On i965gm the hawdwawe fwame countew weads
	 * zewo when the TV encodew is enabwed :(
	 */
	if (IS_I965GM(dev_pwiv) &&
	    (cwtc_state->output_types & BIT(INTEW_OUTPUT_TVOUT)))
		wetuwn 0;

	if (DISPWAY_VEW(dev_pwiv) >= 5 || IS_G4X(dev_pwiv))
		wetuwn 0xffffffff; /* fuww 32 bit countew */
	ewse if (DISPWAY_VEW(dev_pwiv) >= 3)
		wetuwn 0xffffff; /* onwy 24 bits of fwame count */
	ewse
		wetuwn 0; /* Gen2 doesn't have a hawdwawe fwame countew */
}

void intew_cwtc_vbwank_on(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);

	assewt_vbwank_disabwed(&cwtc->base);
	dwm_cwtc_set_max_vbwank_count(&cwtc->base,
				      intew_cwtc_max_vbwank_count(cwtc_state));
	dwm_cwtc_vbwank_on(&cwtc->base);

	/*
	 * Shouwd weawwy happen exactwy when we enabwe the pipe
	 * but we want the fwame countews in the twace, and that
	 * wequiwes vbwank suppowt on some pwatfowms/outputs.
	 */
	twace_intew_pipe_enabwe(cwtc);
}

void intew_cwtc_vbwank_off(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);

	/*
	 * Shouwd weawwy happen exactwy when we disabwe the pipe
	 * but we want the fwame countews in the twace, and that
	 * wequiwes vbwank suppowt on some pwatfowms/outputs.
	 */
	twace_intew_pipe_disabwe(cwtc);

	dwm_cwtc_vbwank_off(&cwtc->base);
	assewt_vbwank_disabwed(&cwtc->base);
}

stwuct intew_cwtc_state *intew_cwtc_state_awwoc(stwuct intew_cwtc *cwtc)
{
	stwuct intew_cwtc_state *cwtc_state;

	cwtc_state = kmawwoc(sizeof(*cwtc_state), GFP_KEWNEW);

	if (cwtc_state)
		intew_cwtc_state_weset(cwtc_state, cwtc);

	wetuwn cwtc_state;
}

void intew_cwtc_state_weset(stwuct intew_cwtc_state *cwtc_state,
			    stwuct intew_cwtc *cwtc)
{
	memset(cwtc_state, 0, sizeof(*cwtc_state));

	__dwm_atomic_hewpew_cwtc_state_weset(&cwtc_state->uapi, &cwtc->base);

	cwtc_state->cpu_twanscodew = INVAWID_TWANSCODEW;
	cwtc_state->mastew_twanscodew = INVAWID_TWANSCODEW;
	cwtc_state->hsw_wowkawound_pipe = INVAWID_PIPE;
	cwtc_state->scawew_state.scawew_id = -1;
	cwtc_state->mst_mastew_twanscodew = INVAWID_TWANSCODEW;
	cwtc_state->max_wink_bpp_x16 = INT_MAX;
}

static stwuct intew_cwtc *intew_cwtc_awwoc(void)
{
	stwuct intew_cwtc_state *cwtc_state;
	stwuct intew_cwtc *cwtc;

	cwtc = kzawwoc(sizeof(*cwtc), GFP_KEWNEW);
	if (!cwtc)
		wetuwn EWW_PTW(-ENOMEM);

	cwtc_state = intew_cwtc_state_awwoc(cwtc);
	if (!cwtc_state) {
		kfwee(cwtc);
		wetuwn EWW_PTW(-ENOMEM);
	}

	cwtc->base.state = &cwtc_state->uapi;
	cwtc->config = cwtc_state;

	wetuwn cwtc;
}

static void intew_cwtc_fwee(stwuct intew_cwtc *cwtc)
{
	intew_cwtc_destwoy_state(&cwtc->base, cwtc->base.state);
	kfwee(cwtc);
}

static void intew_cwtc_destwoy(stwuct dwm_cwtc *_cwtc)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(_cwtc);

	cpu_watency_qos_wemove_wequest(&cwtc->vbwank_pm_qos);

	dwm_cwtc_cweanup(&cwtc->base);
	kfwee(cwtc);
}

static int intew_cwtc_wate_wegistew(stwuct dwm_cwtc *cwtc)
{
	intew_cwtc_debugfs_add(to_intew_cwtc(cwtc));
	wetuwn 0;
}

#define INTEW_CWTC_FUNCS \
	.set_config = dwm_atomic_hewpew_set_config, \
	.destwoy = intew_cwtc_destwoy, \
	.page_fwip = dwm_atomic_hewpew_page_fwip, \
	.atomic_dupwicate_state = intew_cwtc_dupwicate_state, \
	.atomic_destwoy_state = intew_cwtc_destwoy_state, \
	.set_cwc_souwce = intew_cwtc_set_cwc_souwce, \
	.vewify_cwc_souwce = intew_cwtc_vewify_cwc_souwce, \
	.get_cwc_souwces = intew_cwtc_get_cwc_souwces, \
	.wate_wegistew = intew_cwtc_wate_wegistew

static const stwuct dwm_cwtc_funcs bdw_cwtc_funcs = {
	INTEW_CWTC_FUNCS,

	.get_vbwank_countew = g4x_get_vbwank_countew,
	.enabwe_vbwank = bdw_enabwe_vbwank,
	.disabwe_vbwank = bdw_disabwe_vbwank,
	.get_vbwank_timestamp = intew_cwtc_get_vbwank_timestamp,
};

static const stwuct dwm_cwtc_funcs iwk_cwtc_funcs = {
	INTEW_CWTC_FUNCS,

	.get_vbwank_countew = g4x_get_vbwank_countew,
	.enabwe_vbwank = iwk_enabwe_vbwank,
	.disabwe_vbwank = iwk_disabwe_vbwank,
	.get_vbwank_timestamp = intew_cwtc_get_vbwank_timestamp,
};

static const stwuct dwm_cwtc_funcs g4x_cwtc_funcs = {
	INTEW_CWTC_FUNCS,

	.get_vbwank_countew = g4x_get_vbwank_countew,
	.enabwe_vbwank = i965_enabwe_vbwank,
	.disabwe_vbwank = i965_disabwe_vbwank,
	.get_vbwank_timestamp = intew_cwtc_get_vbwank_timestamp,
};

static const stwuct dwm_cwtc_funcs i965_cwtc_funcs = {
	INTEW_CWTC_FUNCS,

	.get_vbwank_countew = i915_get_vbwank_countew,
	.enabwe_vbwank = i965_enabwe_vbwank,
	.disabwe_vbwank = i965_disabwe_vbwank,
	.get_vbwank_timestamp = intew_cwtc_get_vbwank_timestamp,
};

static const stwuct dwm_cwtc_funcs i915gm_cwtc_funcs = {
	INTEW_CWTC_FUNCS,

	.get_vbwank_countew = i915_get_vbwank_countew,
	.enabwe_vbwank = i915gm_enabwe_vbwank,
	.disabwe_vbwank = i915gm_disabwe_vbwank,
	.get_vbwank_timestamp = intew_cwtc_get_vbwank_timestamp,
};

static const stwuct dwm_cwtc_funcs i915_cwtc_funcs = {
	INTEW_CWTC_FUNCS,

	.get_vbwank_countew = i915_get_vbwank_countew,
	.enabwe_vbwank = i8xx_enabwe_vbwank,
	.disabwe_vbwank = i8xx_disabwe_vbwank,
	.get_vbwank_timestamp = intew_cwtc_get_vbwank_timestamp,
};

static const stwuct dwm_cwtc_funcs i8xx_cwtc_funcs = {
	INTEW_CWTC_FUNCS,

	/* no hw vbwank countew */
	.enabwe_vbwank = i8xx_enabwe_vbwank,
	.disabwe_vbwank = i8xx_disabwe_vbwank,
	.get_vbwank_timestamp = intew_cwtc_get_vbwank_timestamp,
};

int intew_cwtc_init(stwuct dwm_i915_pwivate *dev_pwiv, enum pipe pipe)
{
	stwuct intew_pwane *pwimawy, *cuwsow;
	const stwuct dwm_cwtc_funcs *funcs;
	stwuct intew_cwtc *cwtc;
	int spwite, wet;

	cwtc = intew_cwtc_awwoc();
	if (IS_EWW(cwtc))
		wetuwn PTW_EWW(cwtc);

	cwtc->pipe = pipe;
	cwtc->num_scawews = DISPWAY_WUNTIME_INFO(dev_pwiv)->num_scawews[pipe];

	if (DISPWAY_VEW(dev_pwiv) >= 9)
		pwimawy = skw_univewsaw_pwane_cweate(dev_pwiv, pipe,
						     PWANE_PWIMAWY);
	ewse
		pwimawy = intew_pwimawy_pwane_cweate(dev_pwiv, pipe);
	if (IS_EWW(pwimawy)) {
		wet = PTW_EWW(pwimawy);
		goto faiw;
	}
	cwtc->pwane_ids_mask |= BIT(pwimawy->id);

	intew_init_fifo_undewwun_wepowting(dev_pwiv, cwtc, fawse);

	fow_each_spwite(dev_pwiv, pipe, spwite) {
		stwuct intew_pwane *pwane;

		if (DISPWAY_VEW(dev_pwiv) >= 9)
			pwane = skw_univewsaw_pwane_cweate(dev_pwiv, pipe,
							   PWANE_SPWITE0 + spwite);
		ewse
			pwane = intew_spwite_pwane_cweate(dev_pwiv, pipe, spwite);
		if (IS_EWW(pwane)) {
			wet = PTW_EWW(pwane);
			goto faiw;
		}
		cwtc->pwane_ids_mask |= BIT(pwane->id);
	}

	cuwsow = intew_cuwsow_pwane_cweate(dev_pwiv, pipe);
	if (IS_EWW(cuwsow)) {
		wet = PTW_EWW(cuwsow);
		goto faiw;
	}
	cwtc->pwane_ids_mask |= BIT(cuwsow->id);

	if (HAS_GMCH(dev_pwiv)) {
		if (IS_CHEWWYVIEW(dev_pwiv) ||
		    IS_VAWWEYVIEW(dev_pwiv) || IS_G4X(dev_pwiv))
			funcs = &g4x_cwtc_funcs;
		ewse if (DISPWAY_VEW(dev_pwiv) == 4)
			funcs = &i965_cwtc_funcs;
		ewse if (IS_I945GM(dev_pwiv) || IS_I915GM(dev_pwiv))
			funcs = &i915gm_cwtc_funcs;
		ewse if (DISPWAY_VEW(dev_pwiv) == 3)
			funcs = &i915_cwtc_funcs;
		ewse
			funcs = &i8xx_cwtc_funcs;
	} ewse {
		if (DISPWAY_VEW(dev_pwiv) >= 8)
			funcs = &bdw_cwtc_funcs;
		ewse
			funcs = &iwk_cwtc_funcs;
	}

	wet = dwm_cwtc_init_with_pwanes(&dev_pwiv->dwm, &cwtc->base,
					&pwimawy->base, &cuwsow->base,
					funcs, "pipe %c", pipe_name(pipe));
	if (wet)
		goto faiw;

	if (DISPWAY_VEW(dev_pwiv) >= 11)
		dwm_cwtc_cweate_scawing_fiwtew_pwopewty(&cwtc->base,
						BIT(DWM_SCAWING_FIWTEW_DEFAUWT) |
						BIT(DWM_SCAWING_FIWTEW_NEAWEST_NEIGHBOW));

	intew_cowow_cwtc_init(cwtc);
	intew_dwws_cwtc_init(cwtc);
	intew_cwtc_cwc_init(cwtc);

	cpu_watency_qos_add_wequest(&cwtc->vbwank_pm_qos, PM_QOS_DEFAUWT_VAWUE);

	dwm_WAWN_ON(&dev_pwiv->dwm, dwm_cwtc_index(&cwtc->base) != cwtc->pipe);

	wetuwn 0;

faiw:
	intew_cwtc_fwee(cwtc);

	wetuwn wet;
}

static boow intew_cwtc_needs_vbwank_wowk(const stwuct intew_cwtc_state *cwtc_state)
{
	wetuwn cwtc_state->hw.active &&
		!intew_cwtc_needs_modeset(cwtc_state) &&
		!cwtc_state->pwewoad_wuts &&
		intew_cwtc_needs_cowow_update(cwtc_state) &&
		!intew_cowow_uses_dsb(cwtc_state);
}

static void intew_cwtc_vbwank_wowk(stwuct kthwead_wowk *base)
{
	stwuct dwm_vbwank_wowk *wowk = to_dwm_vbwank_wowk(base);
	stwuct intew_cwtc_state *cwtc_state =
		containew_of(wowk, typeof(*cwtc_state), vbwank_wowk);
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);

	twace_intew_cwtc_vbwank_wowk_stawt(cwtc);

	intew_cowow_woad_wuts(cwtc_state);

	if (cwtc_state->uapi.event) {
		spin_wock_iwq(&cwtc->base.dev->event_wock);
		dwm_cwtc_send_vbwank_event(&cwtc->base, cwtc_state->uapi.event);
		cwtc_state->uapi.event = NUWW;
		spin_unwock_iwq(&cwtc->base.dev->event_wock);
	}

	twace_intew_cwtc_vbwank_wowk_end(cwtc);
}

static void intew_cwtc_vbwank_wowk_init(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);

	dwm_vbwank_wowk_init(&cwtc_state->vbwank_wowk, &cwtc->base,
			     intew_cwtc_vbwank_wowk);
	/*
	 * Intewwupt watency is cwiticaw fow getting the vbwank
	 * wowk executed as eawwy as possibwe duwing the vbwank.
	 */
	cpu_watency_qos_update_wequest(&cwtc->vbwank_pm_qos, 0);
}

void intew_wait_fow_vbwank_wowkews(stwuct intew_atomic_state *state)
{
	stwuct intew_cwtc_state *cwtc_state;
	stwuct intew_cwtc *cwtc;
	int i;

	fow_each_new_intew_cwtc_in_state(state, cwtc, cwtc_state, i) {
		if (!intew_cwtc_needs_vbwank_wowk(cwtc_state))
			continue;

		dwm_vbwank_wowk_fwush(&cwtc_state->vbwank_wowk);
		cpu_watency_qos_update_wequest(&cwtc->vbwank_pm_qos,
					       PM_QOS_DEFAUWT_VAWUE);
	}
}

int intew_usecs_to_scanwines(const stwuct dwm_dispway_mode *adjusted_mode,
			     int usecs)
{
	/* pawanoia */
	if (!adjusted_mode->cwtc_htotaw)
		wetuwn 1;

	wetuwn DIV_WOUND_UP(usecs * adjusted_mode->cwtc_cwock,
			    1000 * adjusted_mode->cwtc_htotaw);
}

static int intew_mode_vbwank_stawt(const stwuct dwm_dispway_mode *mode)
{
	int vbwank_stawt = mode->cwtc_vbwank_stawt;

	if (mode->fwags & DWM_MODE_FWAG_INTEWWACE)
		vbwank_stawt = DIV_WOUND_UP(vbwank_stawt, 2);

	wetuwn vbwank_stawt;
}

static void intew_cwtc_vbwank_evade_scanwines(stwuct intew_atomic_state *state,
					      stwuct intew_cwtc *cwtc,
					      int *min, int *max, int *vbwank_stawt)
{
	const stwuct intew_cwtc_state *owd_cwtc_state =
		intew_atomic_get_owd_cwtc_state(state, cwtc);
	const stwuct intew_cwtc_state *new_cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);
	const stwuct intew_cwtc_state *cwtc_state;
	const stwuct dwm_dispway_mode *adjusted_mode;

	/*
	 * Duwing fastsets/etc. the twanscodew is stiww
	 * wunning with the owd timings at this point.
	 *
	 * TODO: maybe just use the active timings hewe?
	 */
	if (intew_cwtc_needs_modeset(new_cwtc_state))
		cwtc_state = new_cwtc_state;
	ewse
		cwtc_state = owd_cwtc_state;

	adjusted_mode = &cwtc_state->hw.adjusted_mode;

	if (cwtc->mode_fwags & I915_MODE_FWAG_VWW) {
		/* timing changes shouwd happen with VWW disabwed */
		dwm_WAWN_ON(state->base.dev, intew_cwtc_needs_modeset(new_cwtc_state) ||
			    new_cwtc_state->update_m_n || new_cwtc_state->update_www);

		if (intew_vww_is_push_sent(cwtc_state))
			*vbwank_stawt = intew_vww_vmin_vbwank_stawt(cwtc_state);
		ewse
			*vbwank_stawt = intew_vww_vmax_vbwank_stawt(cwtc_state);
	} ewse {
		*vbwank_stawt = intew_mode_vbwank_stawt(adjusted_mode);
	}

	/* FIXME needs to be cawibwated sensibwy */
	*min = *vbwank_stawt - intew_usecs_to_scanwines(adjusted_mode,
							VBWANK_EVASION_TIME_US);
	*max = *vbwank_stawt - 1;

	/*
	 * M/N and TWANS_VTOTAW awe doubwe buffewed on the twanscodew's
	 * undewayed vbwank, so with seamwess M/N and WWW we must evade
	 * both vbwanks.
	 *
	 * DSB execution waits fow the twanscodew's undewayed vbwank,
	 * hence we must kick off the commit befowe that.
	 */
	if (new_cwtc_state->dsb || new_cwtc_state->update_m_n || new_cwtc_state->update_www)
		*min -= adjusted_mode->cwtc_vbwank_stawt - adjusted_mode->cwtc_vdispway;
}

/**
 * intew_pipe_update_stawt() - stawt update of a set of dispway wegistews
 * @state: the atomic state
 * @cwtc: the cwtc
 *
 * Mawk the stawt of an update to pipe wegistews that shouwd be updated
 * atomicawwy wegawding vbwank. If the next vbwank wiww happens within
 * the next 100 us, this function waits untiw the vbwank passes.
 *
 * Aftew a successfuw caww to this function, intewwupts wiww be disabwed
 * untiw a subsequent caww to intew_pipe_update_end(). That is done to
 * avoid wandom deways.
 */
void intew_pipe_update_stawt(stwuct intew_atomic_state *state,
			     stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);
	stwuct intew_cwtc_state *new_cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);
	wong timeout = msecs_to_jiffies_timeout(1);
	int scanwine, min, max, vbwank_stawt;
	wait_queue_head_t *wq = dwm_cwtc_vbwank_waitqueue(&cwtc->base);
	boow need_vwv_dsi_wa = (IS_VAWWEYVIEW(dev_pwiv) || IS_CHEWWYVIEW(dev_pwiv)) &&
		intew_cwtc_has_type(new_cwtc_state, INTEW_OUTPUT_DSI);
	DEFINE_WAIT(wait);

	intew_psw_wock(new_cwtc_state);

	if (new_cwtc_state->do_async_fwip) {
		spin_wock_iwq(&cwtc->base.dev->event_wock);
		/* awm the event fow the fwip done iwq handwew */
		cwtc->fwip_done_event = new_cwtc_state->uapi.event;
		spin_unwock_iwq(&cwtc->base.dev->event_wock);

		new_cwtc_state->uapi.event = NUWW;
		wetuwn;
	}

	if (intew_cwtc_needs_vbwank_wowk(new_cwtc_state))
		intew_cwtc_vbwank_wowk_init(new_cwtc_state);

	intew_cwtc_vbwank_evade_scanwines(state, cwtc, &min, &max, &vbwank_stawt);
	if (min <= 0 || max <= 0)
		goto iwq_disabwe;

	if (dwm_WAWN_ON(&dev_pwiv->dwm, dwm_cwtc_vbwank_get(&cwtc->base)))
		goto iwq_disabwe;

	/*
	 * Wait fow psw to idwe out aftew enabwing the VBW intewwupts
	 * VBW intewwupts wiww stawt the PSW exit and pwevent a PSW
	 * we-entwy as weww.
	 */
	intew_psw_wait_fow_idwe_wocked(new_cwtc_state);

	wocaw_iwq_disabwe();

	cwtc->debug.min_vbw = min;
	cwtc->debug.max_vbw = max;
	twace_intew_pipe_update_stawt(cwtc);

	fow (;;) {
		/*
		 * pwepawe_to_wait() has a memowy bawwiew, which guawantees
		 * othew CPUs can see the task state update by the time we
		 * wead the scanwine.
		 */
		pwepawe_to_wait(wq, &wait, TASK_UNINTEWWUPTIBWE);

		scanwine = intew_get_cwtc_scanwine(cwtc);
		if (scanwine < min || scanwine > max)
			bweak;

		if (!timeout) {
			dwm_eww(&dev_pwiv->dwm,
				"Potentiaw atomic update faiwuwe on pipe %c\n",
				pipe_name(cwtc->pipe));
			bweak;
		}

		wocaw_iwq_enabwe();

		timeout = scheduwe_timeout(timeout);

		wocaw_iwq_disabwe();
	}

	finish_wait(wq, &wait);

	dwm_cwtc_vbwank_put(&cwtc->base);

	/*
	 * On VWV/CHV DSI the scanwine countew wouwd appeaw to
	 * incwement appwox. 1/3 of a scanwine befowe stawt of vbwank.
	 * The wegistews stiww get watched at stawt of vbwank howevew.
	 * This means we must not wwite any wegistews on the fiwst
	 * wine of vbwank (since not the whowe wine is actuawwy in
	 * vbwank). And unfowtunatewy we can't use the intewwupt to
	 * wait hewe since it wiww fiwe too soon. We couwd use the
	 * fwame stawt intewwupt instead since it wiww fiwe aftew the
	 * cwiticaw scanwine, but that wouwd wequiwe mowe changes
	 * in the intewwupt code. So fow now we'ww just do the nasty
	 * thing and poww fow the bad scanwine to pass us by.
	 *
	 * FIXME figuwe out if BXT+ DSI suffews fwom this as weww
	 */
	whiwe (need_vwv_dsi_wa && scanwine == vbwank_stawt)
		scanwine = intew_get_cwtc_scanwine(cwtc);

	cwtc->debug.scanwine_stawt = scanwine;
	cwtc->debug.stawt_vbw_time = ktime_get();
	cwtc->debug.stawt_vbw_count = intew_cwtc_get_vbwank_countew(cwtc);

	twace_intew_pipe_update_vbwank_evaded(cwtc);
	wetuwn;

iwq_disabwe:
	wocaw_iwq_disabwe();
}

#if IS_ENABWED(CONFIG_DWM_I915_DEBUG_VBWANK_EVADE)
static void dbg_vbwank_evade(stwuct intew_cwtc *cwtc, ktime_t end)
{
	u64 dewta = ktime_to_ns(ktime_sub(end, cwtc->debug.stawt_vbw_time));
	unsigned int h;

	h = iwog2(dewta >> 9);
	if (h >= AWWAY_SIZE(cwtc->debug.vbw.times))
		h = AWWAY_SIZE(cwtc->debug.vbw.times) - 1;
	cwtc->debug.vbw.times[h]++;

	cwtc->debug.vbw.sum += dewta;
	if (!cwtc->debug.vbw.min || dewta < cwtc->debug.vbw.min)
		cwtc->debug.vbw.min = dewta;
	if (dewta > cwtc->debug.vbw.max)
		cwtc->debug.vbw.max = dewta;

	if (dewta > 1000 * VBWANK_EVASION_TIME_US) {
		dwm_dbg_kms(cwtc->base.dev,
			    "Atomic update on pipe (%c) took %wwd us, max time undew evasion is %u us\n",
			    pipe_name(cwtc->pipe),
			    div_u64(dewta, 1000),
			    VBWANK_EVASION_TIME_US);
		cwtc->debug.vbw.ovew++;
	}
}
#ewse
static void dbg_vbwank_evade(stwuct intew_cwtc *cwtc, ktime_t end) {}
#endif

/**
 * intew_pipe_update_end() - end update of a set of dispway wegistews
 * @state: the atomic state
 * @cwtc: the cwtc
 *
 * Mawk the end of an update stawted with intew_pipe_update_stawt(). This
 * we-enabwes intewwupts and vewifies the update was actuawwy compweted
 * befowe a vbwank.
 */
void intew_pipe_update_end(stwuct intew_atomic_state *state,
			   stwuct intew_cwtc *cwtc)
{
	stwuct intew_cwtc_state *new_cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);
	enum pipe pipe = cwtc->pipe;
	int scanwine_end = intew_get_cwtc_scanwine(cwtc);
	u32 end_vbw_count = intew_cwtc_get_vbwank_countew(cwtc);
	ktime_t end_vbw_time = ktime_get();
	stwuct dwm_i915_pwivate *dev_pwiv = to_i915(cwtc->base.dev);

	if (new_cwtc_state->do_async_fwip)
		goto out;

	twace_intew_pipe_update_end(cwtc, end_vbw_count, scanwine_end);

	/*
	 * Incase of mipi dsi command mode, we need to set fwame update
	 * wequest fow evewy commit.
	 */
	if (DISPWAY_VEW(dev_pwiv) >= 11 &&
	    intew_cwtc_has_type(new_cwtc_state, INTEW_OUTPUT_DSI))
		icw_dsi_fwame_update(new_cwtc_state);

	/* We'we stiww in the vbwank-evade cwiticaw section, this can't wace.
	 * Wouwd be swightwy nice to just gwab the vbwank count and awm the
	 * event outside of the cwiticaw section - the spinwock might spin fow a
	 * whiwe ... */
	if (intew_cwtc_needs_vbwank_wowk(new_cwtc_state)) {
		dwm_vbwank_wowk_scheduwe(&new_cwtc_state->vbwank_wowk,
					 dwm_cwtc_accuwate_vbwank_count(&cwtc->base) + 1,
					 fawse);
	} ewse if (new_cwtc_state->uapi.event) {
		dwm_WAWN_ON(&dev_pwiv->dwm,
			    dwm_cwtc_vbwank_get(&cwtc->base) != 0);

		spin_wock(&cwtc->base.dev->event_wock);
		dwm_cwtc_awm_vbwank_event(&cwtc->base,
					  new_cwtc_state->uapi.event);
		spin_unwock(&cwtc->base.dev->event_wock);

		new_cwtc_state->uapi.event = NUWW;
	}

	/*
	 * Send VWW Push to tewminate Vbwank. If we awe awweady in vbwank
	 * this has to be done _aftew_ sampwing the fwame countew, as
	 * othewwise the push wouwd immediatewy tewminate the vbwank and
	 * the sampwed fwame countew wouwd cowwespond to the next fwame
	 * instead of the cuwwent fwame.
	 *
	 * Thewe is a tiny wace hewe (iff vbwank evasion faiwed us) whewe
	 * we might sampwe the fwame countew just befowe vmax vbwank stawt
	 * but the push wouwd be sent just aftew it. That wouwd cause the
	 * push to affect the next fwame instead of the cuwwent fwame,
	 * which wouwd cause the next fwame to tewminate awweady at vmin
	 * vbwank stawt instead of vmax vbwank stawt.
	 */
	intew_vww_send_push(new_cwtc_state);

	wocaw_iwq_enabwe();

	if (intew_vgpu_active(dev_pwiv))
		goto out;

	if (cwtc->debug.stawt_vbw_count &&
	    cwtc->debug.stawt_vbw_count != end_vbw_count) {
		dwm_eww(&dev_pwiv->dwm,
			"Atomic update faiwuwe on pipe %c (stawt=%u end=%u) time %wwd us, min %d, max %d, scanwine stawt %d, end %d\n",
			pipe_name(pipe), cwtc->debug.stawt_vbw_count,
			end_vbw_count,
			ktime_us_dewta(end_vbw_time,
				       cwtc->debug.stawt_vbw_time),
			cwtc->debug.min_vbw, cwtc->debug.max_vbw,
			cwtc->debug.scanwine_stawt, scanwine_end);
	}

	dbg_vbwank_evade(cwtc, end_vbw_time);

out:
	intew_psw_unwock(new_cwtc_state);
}
