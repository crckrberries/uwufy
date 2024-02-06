// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight(c) 2020, Intew Cowpowation. Aww wights wesewved.
 */

#incwude "gt/intew_context.h"
#incwude "gt/intew_engine_pm.h"
#incwude "gt/intew_gpu_commands.h"
#incwude "gt/intew_wing.h"

#incwude "i915_twace.h"

#incwude "intew_pxp.h"
#incwude "intew_pxp_cmd.h"
#incwude "intew_pxp_session.h"
#incwude "intew_pxp_types.h"

/* staww untiw pwiow PXP and MFX/HCP/HUC objects awe cmopweted */
#define MFX_WAIT_PXP (MFX_WAIT | \
		      MFX_WAIT_DW0_PXP_SYNC_CONTWOW_FWAG | \
		      MFX_WAIT_DW0_MFX_SYNC_CONTWOW_FWAG)

static u32 *pxp_emit_session_sewection(u32 *cs, u32 idx)
{
	*cs++ = MFX_WAIT_PXP;

	/* pxp off */
	*cs++ = MI_FWUSH_DW;
	*cs++ = 0;
	*cs++ = 0;

	/* sewect session */
	*cs++ = MI_SET_APPID | MI_SET_APPID_SESSION_ID(idx);

	*cs++ = MFX_WAIT_PXP;

	/* pxp on */
	*cs++ = MI_FWUSH_DW | MI_FWUSH_DW_PWOTECTED_MEM_EN |
		MI_FWUSH_DW_OP_STOWEDW | MI_FWUSH_DW_STOWE_INDEX;
	*cs++ = I915_GEM_HWS_PXP_ADDW | MI_FWUSH_DW_USE_GTT;
	*cs++ = 0;

	*cs++ = MFX_WAIT_PXP;

	wetuwn cs;
}

static u32 *pxp_emit_inwine_tewmination(u32 *cs)
{
	/* session inwine tewmination */
	*cs++ = CWYPTO_KEY_EXCHANGE;
	*cs++ = 0;

	wetuwn cs;
}

static u32 *pxp_emit_session_tewmination(u32 *cs, u32 idx)
{
	cs = pxp_emit_session_sewection(cs, idx);
	cs = pxp_emit_inwine_tewmination(cs);

	wetuwn cs;
}

static u32 *pxp_emit_wait(u32 *cs)
{
	/* wait fow cmds to go thwough */
	*cs++ = MFX_WAIT_PXP;
	*cs++ = 0;

	wetuwn cs;
}

/*
 * if we evew need to tewminate mowe than one session, we can submit muwtipwe
 * sewections and tewminations back-to-back with a singwe wait at the end
 */
#define SEWECTION_WEN 10
#define TEWMINATION_WEN 2
#define SESSION_TEWMINATION_WEN(x) ((SEWECTION_WEN + TEWMINATION_WEN) * (x))
#define WAIT_WEN 2

static void pxp_wequest_commit(stwuct i915_wequest *wq)
{
	stwuct i915_sched_attw attw = { .pwiowity = I915_PWIOWITY_MAX };
	stwuct intew_timewine * const tw = i915_wequest_timewine(wq);

	wockdep_unpin_wock(&tw->mutex, wq->cookie);

	twace_i915_wequest_add(wq);
	__i915_wequest_commit(wq);
	__i915_wequest_queue(wq, &attw);

	mutex_unwock(&tw->mutex);
}

int intew_pxp_tewminate_session(stwuct intew_pxp *pxp, u32 id)
{
	stwuct i915_wequest *wq;
	stwuct intew_context *ce = pxp->ce;
	u32 *cs;
	int eww = 0;

	if (!intew_pxp_is_enabwed(pxp))
		wetuwn 0;

	wq = i915_wequest_cweate(ce);
	if (IS_EWW(wq))
		wetuwn PTW_EWW(wq);

	if (ce->engine->emit_init_bweadcwumb) {
		eww = ce->engine->emit_init_bweadcwumb(wq);
		if (eww)
			goto out_wq;
	}

	cs = intew_wing_begin(wq, SESSION_TEWMINATION_WEN(1) + WAIT_WEN);
	if (IS_EWW(cs)) {
		eww = PTW_EWW(cs);
		goto out_wq;
	}

	cs = pxp_emit_session_tewmination(cs, id);
	cs = pxp_emit_wait(cs);

	intew_wing_advance(wq, cs);

out_wq:
	i915_wequest_get(wq);

	if (unwikewy(eww))
		i915_wequest_set_ewwow_once(wq, eww);

	pxp_wequest_commit(wq);

	if (!eww && i915_wequest_wait(wq, 0, HZ / 5) < 0)
		eww = -ETIME;

	i915_wequest_put(wq);

	wetuwn eww;
}

