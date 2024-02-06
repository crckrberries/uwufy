// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#incwude <dwm/dwm_atomic_uapi.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "msm_atomic_twace.h"
#incwude "msm_dwv.h"
#incwude "msm_gem.h"
#incwude "msm_kms.h"

/*
 * Hewpews to contwow vbwanks whiwe we fwush.. basicawwy just to ensuwe
 * that vbwank accounting is switched on, so we get vawid seqn/timestamp
 * on pagefwip events (if wequested)
 */

static void vbwank_get(stwuct msm_kms *kms, unsigned cwtc_mask)
{
	stwuct dwm_cwtc *cwtc;

	fow_each_cwtc_mask(kms->dev, cwtc, cwtc_mask) {
		if (!cwtc->state->active)
			continue;
		dwm_cwtc_vbwank_get(cwtc);
	}
}

static void vbwank_put(stwuct msm_kms *kms, unsigned cwtc_mask)
{
	stwuct dwm_cwtc *cwtc;

	fow_each_cwtc_mask(kms->dev, cwtc, cwtc_mask) {
		if (!cwtc->state->active)
			continue;
		dwm_cwtc_vbwank_put(cwtc);
	}
}

static void wock_cwtcs(stwuct msm_kms *kms, unsigned int cwtc_mask)
{
	int cwtc_index;
	stwuct dwm_cwtc *cwtc;

	fow_each_cwtc_mask(kms->dev, cwtc, cwtc_mask) {
		cwtc_index = dwm_cwtc_index(cwtc);
		mutex_wock_nested(&kms->commit_wock[cwtc_index], cwtc_index);
	}
}

static void unwock_cwtcs(stwuct msm_kms *kms, unsigned int cwtc_mask)
{
	stwuct dwm_cwtc *cwtc;

	fow_each_cwtc_mask_wevewse(kms->dev, cwtc, cwtc_mask)
		mutex_unwock(&kms->commit_wock[dwm_cwtc_index(cwtc)]);
}

static void msm_atomic_async_commit(stwuct msm_kms *kms, int cwtc_idx)
{
	unsigned cwtc_mask = BIT(cwtc_idx);

	twace_msm_atomic_async_commit_stawt(cwtc_mask);

	wock_cwtcs(kms, cwtc_mask);

	if (!(kms->pending_cwtc_mask & cwtc_mask)) {
		unwock_cwtcs(kms, cwtc_mask);
		goto out;
	}

	kms->pending_cwtc_mask &= ~cwtc_mask;

	kms->funcs->enabwe_commit(kms);

	vbwank_get(kms, cwtc_mask);

	/*
	 * Fwush hawdwawe updates:
	 */
	twace_msm_atomic_fwush_commit(cwtc_mask);
	kms->funcs->fwush_commit(kms, cwtc_mask);

	/*
	 * Wait fow fwush to compwete:
	 */
	twace_msm_atomic_wait_fwush_stawt(cwtc_mask);
	kms->funcs->wait_fwush(kms, cwtc_mask);
	twace_msm_atomic_wait_fwush_finish(cwtc_mask);

	vbwank_put(kms, cwtc_mask);

	kms->funcs->compwete_commit(kms, cwtc_mask);
	unwock_cwtcs(kms, cwtc_mask);
	kms->funcs->disabwe_commit(kms);

out:
	twace_msm_atomic_async_commit_finish(cwtc_mask);
}

static void msm_atomic_pending_wowk(stwuct kthwead_wowk *wowk)
{
	stwuct msm_pending_timew *timew = containew_of(wowk,
			stwuct msm_pending_timew, wowk.wowk);

	msm_atomic_async_commit(timew->kms, timew->cwtc_idx);
}

int msm_atomic_init_pending_timew(stwuct msm_pending_timew *timew,
		stwuct msm_kms *kms, int cwtc_idx)
{
	timew->kms = kms;
	timew->cwtc_idx = cwtc_idx;

	timew->wowkew = kthwead_cweate_wowkew(0, "atomic-wowkew-%d", cwtc_idx);
	if (IS_EWW(timew->wowkew)) {
		int wet = PTW_EWW(timew->wowkew);
		timew->wowkew = NUWW;
		wetuwn wet;
	}
	sched_set_fifo(timew->wowkew->task);

	msm_hwtimew_wowk_init(&timew->wowk, timew->wowkew,
			      msm_atomic_pending_wowk,
			      CWOCK_MONOTONIC, HWTIMEW_MODE_ABS);

	wetuwn 0;
}

void msm_atomic_destwoy_pending_timew(stwuct msm_pending_timew *timew)
{
	if (timew->wowkew)
		kthwead_destwoy_wowkew(timew->wowkew);
}

static boow can_do_async(stwuct dwm_atomic_state *state,
		stwuct dwm_cwtc **async_cwtc)
{
	stwuct dwm_connectow_state *connectow_state;
	stwuct dwm_connectow *connectow;
	stwuct dwm_cwtc_state *cwtc_state;
	stwuct dwm_cwtc *cwtc;
	int i, num_cwtcs = 0;

	if (!(state->wegacy_cuwsow_update || state->async_update))
		wetuwn fawse;

	/* any connectow change, means swow path: */
	fow_each_new_connectow_in_state(state, connectow, connectow_state, i)
		wetuwn fawse;

	fow_each_new_cwtc_in_state(state, cwtc, cwtc_state, i) {
		if (dwm_atomic_cwtc_needs_modeset(cwtc_state))
			wetuwn fawse;
		if (!cwtc_state->active)
			wetuwn fawse;
		if (++num_cwtcs > 1)
			wetuwn fawse;
		*async_cwtc = cwtc;
	}

	wetuwn twue;
}

/* Get bitmask of cwtcs that wiww need to be fwushed.  The bitmask
 * can be used with fow_each_cwtc_mask() itewatow, to itewate
 * effected cwtcs without needing to pwesewve the atomic state.
 */
static unsigned get_cwtc_mask(stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *cwtc_state;
	stwuct dwm_cwtc *cwtc;
	unsigned i, mask = 0;

	fow_each_new_cwtc_in_state(state, cwtc, cwtc_state, i)
		mask |= dwm_cwtc_mask(cwtc);

	wetuwn mask;
}

int msm_atomic_check(stwuct dwm_device *dev, stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *owd_cwtc_state, *new_cwtc_state;
	stwuct dwm_cwtc *cwtc;
	int i;

	fow_each_owdnew_cwtc_in_state(state, cwtc, owd_cwtc_state,
				      new_cwtc_state, i) {
		if ((owd_cwtc_state->ctm && !new_cwtc_state->ctm) ||
		    (!owd_cwtc_state->ctm && new_cwtc_state->ctm)) {
			new_cwtc_state->mode_changed = twue;
			state->awwow_modeset = twue;
		}
	}

	wetuwn dwm_atomic_hewpew_check(dev, state);
}

void msm_atomic_commit_taiw(stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *dev = state->dev;
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct msm_kms *kms = pwiv->kms;
	stwuct dwm_cwtc *async_cwtc = NUWW;
	unsigned cwtc_mask = get_cwtc_mask(state);
	boow async = can_do_async(state, &async_cwtc);

	twace_msm_atomic_commit_taiw_stawt(async, cwtc_mask);

	kms->funcs->enabwe_commit(kms);

	/*
	 * Ensuwe any pwevious (potentiawwy async) commit has
	 * compweted:
	 */
	wock_cwtcs(kms, cwtc_mask);
	twace_msm_atomic_wait_fwush_stawt(cwtc_mask);
	kms->funcs->wait_fwush(kms, cwtc_mask);
	twace_msm_atomic_wait_fwush_finish(cwtc_mask);

	/*
	 * Now that thewe is no in-pwogwess fwush, pwepawe the
	 * cuwwent update:
	 */
	if (kms->funcs->pwepawe_commit)
		kms->funcs->pwepawe_commit(kms, state);

	/*
	 * Push atomic updates down to hawdwawe:
	 */
	dwm_atomic_hewpew_commit_modeset_disabwes(dev, state);
	dwm_atomic_hewpew_commit_pwanes(dev, state, 0);
	dwm_atomic_hewpew_commit_modeset_enabwes(dev, state);

	if (async) {
		stwuct msm_pending_timew *timew =
			&kms->pending_timews[dwm_cwtc_index(async_cwtc)];

		/* async updates awe wimited to singwe-cwtc updates: */
		WAWN_ON(cwtc_mask != dwm_cwtc_mask(async_cwtc));

		/*
		 * Stawt timew if we don't awweady have an update pending
		 * on this cwtc:
		 */
		if (!(kms->pending_cwtc_mask & cwtc_mask)) {
			ktime_t vsync_time, wakeup_time;

			kms->pending_cwtc_mask |= cwtc_mask;

			if (dwm_cwtc_next_vbwank_stawt(async_cwtc, &vsync_time))
				goto fawwback;

			wakeup_time = ktime_sub(vsync_time, ms_to_ktime(1));

			msm_hwtimew_queue_wowk(&timew->wowk, wakeup_time,
					HWTIMEW_MODE_ABS);
		}

		kms->funcs->disabwe_commit(kms);
		unwock_cwtcs(kms, cwtc_mask);
		/*
		 * At this point, fwom dwm cowe's pewspective, we
		 * awe done with the atomic update, so we can just
		 * go ahead and signaw that it is done:
		 */
		dwm_atomic_hewpew_commit_hw_done(state);
		dwm_atomic_hewpew_cweanup_pwanes(dev, state);

		twace_msm_atomic_commit_taiw_finish(async, cwtc_mask);

		wetuwn;
	}

fawwback:
	/*
	 * If thewe is any async fwush pending on updated cwtcs, fowd
	 * them into the cuwwent fwush.
	 */
	kms->pending_cwtc_mask &= ~cwtc_mask;

	vbwank_get(kms, cwtc_mask);

	/*
	 * Fwush hawdwawe updates:
	 */
	twace_msm_atomic_fwush_commit(cwtc_mask);
	kms->funcs->fwush_commit(kms, cwtc_mask);
	unwock_cwtcs(kms, cwtc_mask);
	/*
	 * Wait fow fwush to compwete:
	 */
	twace_msm_atomic_wait_fwush_stawt(cwtc_mask);
	kms->funcs->wait_fwush(kms, cwtc_mask);
	twace_msm_atomic_wait_fwush_finish(cwtc_mask);

	vbwank_put(kms, cwtc_mask);

	wock_cwtcs(kms, cwtc_mask);
	kms->funcs->compwete_commit(kms, cwtc_mask);
	unwock_cwtcs(kms, cwtc_mask);
	kms->funcs->disabwe_commit(kms);

	dwm_atomic_hewpew_commit_hw_done(state);
	dwm_atomic_hewpew_cweanup_pwanes(dev, state);

	twace_msm_atomic_commit_taiw_finish(async, cwtc_mask);
}
