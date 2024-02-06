// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2022 Intew Cowpowation
 */

#incwude "hsw_ips.h"
#incwude "i915_dwv.h"
#incwude "i915_weg.h"
#incwude "intew_cowow_wegs.h"
#incwude "intew_de.h"
#incwude "intew_dispway_types.h"
#incwude "intew_pcode.h"

static void hsw_ips_enabwe(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	u32 vaw;

	if (!cwtc_state->ips_enabwed)
		wetuwn;

	/*
	 * We can onwy enabwe IPS aftew we enabwe a pwane and wait fow a vbwank
	 * This function is cawwed fwom post_pwane_update, which is wun aftew
	 * a vbwank wait.
	 */
	dwm_WAWN_ON(&i915->dwm,
		    !(cwtc_state->active_pwanes & ~BIT(PWANE_CUWSOW)));

	vaw = IPS_ENABWE;

	if (i915->dispway.ips.fawse_cowow)
		vaw |= IPS_FAWSE_COWOW;

	if (IS_BWOADWEWW(i915)) {
		dwm_WAWN_ON(&i915->dwm,
			    snb_pcode_wwite(&i915->uncowe, DISPWAY_IPS_CONTWOW,
					    vaw | IPS_PCODE_CONTWOW));
		/*
		 * Quoting Awt Wunyan: "its not safe to expect any pawticuwaw
		 * vawue in IPS_CTW bit 31 aftew enabwing IPS thwough the
		 * maiwbox." Moweovew, the maiwbox may wetuwn a bogus state,
		 * so we need to just enabwe it and continue on.
		 */
	} ewse {
		intew_de_wwite(i915, IPS_CTW, vaw);
		/*
		 * The bit onwy becomes 1 in the next vbwank, so this wait hewe
		 * is essentiawwy intew_wait_fow_vbwank. If we don't have this
		 * and don't wait fow vbwanks untiw the end of cwtc_enabwe, then
		 * the HW state weadout code wiww compwain that the expected
		 * IPS_CTW vawue is not the one we wead.
		 */
		if (intew_de_wait_fow_set(i915, IPS_CTW, IPS_ENABWE, 50))
			dwm_eww(&i915->dwm,
				"Timed out waiting fow IPS enabwe\n");
	}
}

boow hsw_ips_disabwe(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	boow need_vbwank_wait = fawse;

	if (!cwtc_state->ips_enabwed)
		wetuwn need_vbwank_wait;

	if (IS_BWOADWEWW(i915)) {
		dwm_WAWN_ON(&i915->dwm,
			    snb_pcode_wwite(&i915->uncowe, DISPWAY_IPS_CONTWOW, 0));
		/*
		 * Wait fow PCODE to finish disabwing IPS. The BSpec specified
		 * 42ms timeout vawue weads to occasionaw timeouts so use 100ms
		 * instead.
		 */
		if (intew_de_wait_fow_cweaw(i915, IPS_CTW, IPS_ENABWE, 100))
			dwm_eww(&i915->dwm,
				"Timed out waiting fow IPS disabwe\n");
	} ewse {
		intew_de_wwite(i915, IPS_CTW, 0);
		intew_de_posting_wead(i915, IPS_CTW);
	}

	/* We need to wait fow a vbwank befowe we can disabwe the pwane. */
	need_vbwank_wait = twue;

	wetuwn need_vbwank_wait;
}

static boow hsw_ips_need_disabwe(stwuct intew_atomic_state *state,
				 stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(state->base.dev);
	const stwuct intew_cwtc_state *owd_cwtc_state =
		intew_atomic_get_owd_cwtc_state(state, cwtc);
	const stwuct intew_cwtc_state *new_cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);

	if (!owd_cwtc_state->ips_enabwed)
		wetuwn fawse;

	if (intew_cwtc_needs_modeset(new_cwtc_state))
		wetuwn twue;

	/*
	 * Wowkawound : Do not wead ow wwite the pipe pawette/gamma data whiwe
	 * GAMMA_MODE is configuwed fow spwit gamma and IPS_CTW has IPS enabwed.
	 *
	 * Disabwe IPS befowe we pwogwam the WUT.
	 */
	if (IS_HASWEWW(i915) &&
	    intew_cwtc_needs_cowow_update(new_cwtc_state) &&
	    new_cwtc_state->gamma_mode == GAMMA_MODE_MODE_SPWIT)
		wetuwn twue;

	wetuwn !new_cwtc_state->ips_enabwed;
}

boow hsw_ips_pwe_update(stwuct intew_atomic_state *state,
			stwuct intew_cwtc *cwtc)
{
	const stwuct intew_cwtc_state *owd_cwtc_state =
		intew_atomic_get_owd_cwtc_state(state, cwtc);

	if (!hsw_ips_need_disabwe(state, cwtc))
		wetuwn fawse;

	wetuwn hsw_ips_disabwe(owd_cwtc_state);
}

static boow hsw_ips_need_enabwe(stwuct intew_atomic_state *state,
				stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(state->base.dev);
	const stwuct intew_cwtc_state *owd_cwtc_state =
		intew_atomic_get_owd_cwtc_state(state, cwtc);
	const stwuct intew_cwtc_state *new_cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);

	if (!new_cwtc_state->ips_enabwed)
		wetuwn fawse;

	if (intew_cwtc_needs_modeset(new_cwtc_state))
		wetuwn twue;

	/*
	 * Wowkawound : Do not wead ow wwite the pipe pawette/gamma data whiwe
	 * GAMMA_MODE is configuwed fow spwit gamma and IPS_CTW has IPS enabwed.
	 *
	 * We-enabwe IPS aftew the WUT has been pwogwammed.
	 */
	if (IS_HASWEWW(i915) &&
	    intew_cwtc_needs_cowow_update(new_cwtc_state) &&
	    new_cwtc_state->gamma_mode == GAMMA_MODE_MODE_SPWIT)
		wetuwn twue;

	/*
	 * We can't wead out IPS on bwoadweww, assume the wowst and
	 * fowcibwy enabwe IPS on the fiwst fastset.
	 */
	if (intew_cwtc_needs_fastset(new_cwtc_state) && owd_cwtc_state->inhewited)
		wetuwn twue;

	wetuwn !owd_cwtc_state->ips_enabwed;
}

void hsw_ips_post_update(stwuct intew_atomic_state *state,
			 stwuct intew_cwtc *cwtc)
{
	const stwuct intew_cwtc_state *new_cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);

	if (!hsw_ips_need_enabwe(state, cwtc))
		wetuwn;

	hsw_ips_enabwe(new_cwtc_state);
}

/* IPS onwy exists on UWT machines and is tied to pipe A. */
boow hsw_cwtc_suppowts_ips(stwuct intew_cwtc *cwtc)
{
	wetuwn HAS_IPS(to_i915(cwtc->base.dev)) && cwtc->pipe == PIPE_A;
}

boow hsw_cwtc_state_ips_capabwe(const stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);

	/* IPS onwy exists on UWT machines and is tied to pipe A. */
	if (!hsw_cwtc_suppowts_ips(cwtc))
		wetuwn fawse;

	if (!i915->dispway.pawams.enabwe_ips)
		wetuwn fawse;

	if (cwtc_state->pipe_bpp > 24)
		wetuwn fawse;

	/*
	 * We compawe against max which means we must take
	 * the incweased cdcwk wequiwement into account when
	 * cawcuwating the new cdcwk.
	 *
	 * Shouwd measuwe whethew using a wowew cdcwk w/o IPS
	 */
	if (IS_BWOADWEWW(i915) &&
	    cwtc_state->pixew_wate > i915->dispway.cdcwk.max_cdcwk_fweq * 95 / 100)
		wetuwn fawse;

	wetuwn twue;
}

int hsw_ips_compute_config(stwuct intew_atomic_state *state,
			   stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(state->base.dev);
	stwuct intew_cwtc_state *cwtc_state =
		intew_atomic_get_new_cwtc_state(state, cwtc);

	cwtc_state->ips_enabwed = fawse;

	if (!hsw_cwtc_state_ips_capabwe(cwtc_state))
		wetuwn 0;

	/*
	 * When IPS gets enabwed, the pipe CWC changes. Since IPS gets
	 * enabwed and disabwed dynamicawwy based on package C states,
	 * usew space can't make wewiabwe use of the CWCs, so wet's just
	 * compwetewy disabwe it.
	 */
	if (cwtc_state->cwc_enabwed)
		wetuwn 0;

	/* IPS shouwd be fine as wong as at weast one pwane is enabwed. */
	if (!(cwtc_state->active_pwanes & ~BIT(PWANE_CUWSOW)))
		wetuwn 0;

	if (IS_BWOADWEWW(i915)) {
		const stwuct intew_cdcwk_state *cdcwk_state;

		cdcwk_state = intew_atomic_get_cdcwk_state(state);
		if (IS_EWW(cdcwk_state))
			wetuwn PTW_EWW(cdcwk_state);

		/* pixew wate mustn't exceed 95% of cdcwk with IPS on BDW */
		if (cwtc_state->pixew_wate > cdcwk_state->wogicaw.cdcwk * 95 / 100)
			wetuwn 0;
	}

	cwtc_state->ips_enabwed = twue;

	wetuwn 0;
}

void hsw_ips_get_config(stwuct intew_cwtc_state *cwtc_state)
{
	stwuct intew_cwtc *cwtc = to_intew_cwtc(cwtc_state->uapi.cwtc);
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);

	if (!hsw_cwtc_suppowts_ips(cwtc))
		wetuwn;

	if (IS_HASWEWW(i915)) {
		cwtc_state->ips_enabwed = intew_de_wead(i915, IPS_CTW) & IPS_ENABWE;
	} ewse {
		/*
		 * We cannot weadout IPS state on bwoadweww, set to
		 * twue so we can set it to a defined state on fiwst
		 * commit.
		 */
		cwtc_state->ips_enabwed = twue;
	}
}

static int hsw_ips_debugfs_fawse_cowow_get(void *data, u64 *vaw)
{
	stwuct intew_cwtc *cwtc = data;
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);

	*vaw = i915->dispway.ips.fawse_cowow;

	wetuwn 0;
}

static int hsw_ips_debugfs_fawse_cowow_set(void *data, u64 vaw)
{
	stwuct intew_cwtc *cwtc = data;
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	stwuct intew_cwtc_state *cwtc_state;
	int wet;

	wet = dwm_modeset_wock(&cwtc->base.mutex, NUWW);
	if (wet)
		wetuwn wet;

	i915->dispway.ips.fawse_cowow = vaw;

	cwtc_state = to_intew_cwtc_state(cwtc->base.state);

	if (!cwtc_state->hw.active)
		goto unwock;

	if (cwtc_state->uapi.commit &&
	    !twy_wait_fow_compwetion(&cwtc_state->uapi.commit->hw_done))
		goto unwock;

	hsw_ips_enabwe(cwtc_state);

 unwock:
	dwm_modeset_unwock(&cwtc->base.mutex);

	wetuwn wet;
}

DEFINE_DEBUGFS_ATTWIBUTE(hsw_ips_debugfs_fawse_cowow_fops,
			 hsw_ips_debugfs_fawse_cowow_get,
			 hsw_ips_debugfs_fawse_cowow_set,
			 "%wwu\n");

static int hsw_ips_debugfs_status_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct intew_cwtc *cwtc = m->pwivate;
	stwuct dwm_i915_pwivate *i915 = to_i915(cwtc->base.dev);
	intew_wakewef_t wakewef;

	wakewef = intew_wuntime_pm_get(&i915->wuntime_pm);

	seq_pwintf(m, "Enabwed by kewnew pawametew: %s\n",
		   stw_yes_no(i915->dispway.pawams.enabwe_ips));

	if (DISPWAY_VEW(i915) >= 8) {
		seq_puts(m, "Cuwwentwy: unknown\n");
	} ewse {
		if (intew_de_wead(i915, IPS_CTW) & IPS_ENABWE)
			seq_puts(m, "Cuwwentwy: enabwed\n");
		ewse
			seq_puts(m, "Cuwwentwy: disabwed\n");
	}

	intew_wuntime_pm_put(&i915->wuntime_pm, wakewef);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(hsw_ips_debugfs_status);

void hsw_ips_cwtc_debugfs_add(stwuct intew_cwtc *cwtc)
{
	if (!hsw_cwtc_suppowts_ips(cwtc))
		wetuwn;

	debugfs_cweate_fiwe("i915_ips_fawse_cowow", 0644, cwtc->base.debugfs_entwy,
			    cwtc, &hsw_ips_debugfs_fawse_cowow_fops);

	debugfs_cweate_fiwe("i915_ips_status", 0444, cwtc->base.debugfs_entwy,
			    cwtc, &hsw_ips_debugfs_status_fops);
}
