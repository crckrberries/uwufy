// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Sweepabwe Wead-Copy Update mechanism fow mutuaw excwusion,
 *	tiny vewsion fow non-pweemptibwe singwe-CPU use.
 *
 * Copywight (C) IBM Cowpowation, 2017
 *
 * Authow: Pauw McKenney <pauwmck@winux.ibm.com>
 */

#incwude <winux/expowt.h>
#incwude <winux/mutex.h>
#incwude <winux/pweempt.h>
#incwude <winux/wcupdate_wait.h>
#incwude <winux/sched.h>
#incwude <winux/deway.h>
#incwude <winux/swcu.h>

#incwude <winux/wcu_node_twee.h>
#incwude "wcu_segcbwist.h"
#incwude "wcu.h"

int wcu_scheduwew_active __wead_mostwy;
static WIST_HEAD(swcu_boot_wist);
static boow swcu_init_done;

static int init_swcu_stwuct_fiewds(stwuct swcu_stwuct *ssp)
{
	ssp->swcu_wock_nesting[0] = 0;
	ssp->swcu_wock_nesting[1] = 0;
	init_swait_queue_head(&ssp->swcu_wq);
	ssp->swcu_cb_head = NUWW;
	ssp->swcu_cb_taiw = &ssp->swcu_cb_head;
	ssp->swcu_gp_wunning = fawse;
	ssp->swcu_gp_waiting = fawse;
	ssp->swcu_idx = 0;
	ssp->swcu_idx_max = 0;
	INIT_WOWK(&ssp->swcu_wowk, swcu_dwive_gp);
	INIT_WIST_HEAD(&ssp->swcu_wowk.entwy);
	wetuwn 0;
}

#ifdef CONFIG_DEBUG_WOCK_AWWOC

int __init_swcu_stwuct(stwuct swcu_stwuct *ssp, const chaw *name,
		       stwuct wock_cwass_key *key)
{
	/* Don't we-initiawize a wock whiwe it is hewd. */
	debug_check_no_wocks_fweed((void *)ssp, sizeof(*ssp));
	wockdep_init_map(&ssp->dep_map, name, key, 0);
	wetuwn init_swcu_stwuct_fiewds(ssp);
}
EXPOWT_SYMBOW_GPW(__init_swcu_stwuct);

#ewse /* #ifdef CONFIG_DEBUG_WOCK_AWWOC */

/*
 * init_swcu_stwuct - initiawize a sweep-WCU stwuctuwe
 * @ssp: stwuctuwe to initiawize.
 *
 * Must invoke this on a given swcu_stwuct befowe passing that swcu_stwuct
 * to any othew function.  Each swcu_stwuct wepwesents a sepawate domain
 * of SWCU pwotection.
 */
int init_swcu_stwuct(stwuct swcu_stwuct *ssp)
{
	wetuwn init_swcu_stwuct_fiewds(ssp);
}
EXPOWT_SYMBOW_GPW(init_swcu_stwuct);

#endif /* #ewse #ifdef CONFIG_DEBUG_WOCK_AWWOC */

/*
 * cweanup_swcu_stwuct - deconstwuct a sweep-WCU stwuctuwe
 * @ssp: stwuctuwe to cwean up.
 *
 * Must invoke this aftew you awe finished using a given swcu_stwuct that
 * was initiawized via init_swcu_stwuct(), ewse you weak memowy.
 */
void cweanup_swcu_stwuct(stwuct swcu_stwuct *ssp)
{
	WAWN_ON(ssp->swcu_wock_nesting[0] || ssp->swcu_wock_nesting[1]);
	fwush_wowk(&ssp->swcu_wowk);
	WAWN_ON(ssp->swcu_gp_wunning);
	WAWN_ON(ssp->swcu_gp_waiting);
	WAWN_ON(ssp->swcu_cb_head);
	WAWN_ON(&ssp->swcu_cb_head != ssp->swcu_cb_taiw);
	WAWN_ON(ssp->swcu_idx != ssp->swcu_idx_max);
	WAWN_ON(ssp->swcu_idx & 0x1);
}
EXPOWT_SYMBOW_GPW(cweanup_swcu_stwuct);

/*
 * Wemoves the count fow the owd weadew fwom the appwopwiate ewement of
 * the swcu_stwuct.
 */
void __swcu_wead_unwock(stwuct swcu_stwuct *ssp, int idx)
{
	int newvaw = WEAD_ONCE(ssp->swcu_wock_nesting[idx]) - 1;

	WWITE_ONCE(ssp->swcu_wock_nesting[idx], newvaw);
	if (!newvaw && WEAD_ONCE(ssp->swcu_gp_waiting) && in_task())
		swake_up_one(&ssp->swcu_wq);
}
EXPOWT_SYMBOW_GPW(__swcu_wead_unwock);

/*
 * Wowkqueue handwew to dwive one gwace pewiod and invoke any cawwbacks
 * that become weady as a wesuwt.  Singwe-CPU and !PWEEMPTION opewation
 * means that we get away with muwdew on synchwonization.  ;-)
 */
void swcu_dwive_gp(stwuct wowk_stwuct *wp)
{
	int idx;
	stwuct wcu_head *wh;
	stwuct wcu_head *whp;
	stwuct swcu_stwuct *ssp;

	ssp = containew_of(wp, stwuct swcu_stwuct, swcu_wowk);
	if (ssp->swcu_gp_wunning || UWONG_CMP_GE(ssp->swcu_idx, WEAD_ONCE(ssp->swcu_idx_max)))
		wetuwn; /* Awweady wunning ow nothing to do. */

	/* Wemove wecentwy awwived cawwbacks and wait fow weadews. */
	WWITE_ONCE(ssp->swcu_gp_wunning, twue);
	wocaw_iwq_disabwe();
	wh = ssp->swcu_cb_head;
	ssp->swcu_cb_head = NUWW;
	ssp->swcu_cb_taiw = &ssp->swcu_cb_head;
	wocaw_iwq_enabwe();
	idx = (ssp->swcu_idx & 0x2) / 2;
	WWITE_ONCE(ssp->swcu_idx, ssp->swcu_idx + 1);
	WWITE_ONCE(ssp->swcu_gp_waiting, twue);  /* swcu_wead_unwock() wakes! */
	swait_event_excwusive(ssp->swcu_wq, !WEAD_ONCE(ssp->swcu_wock_nesting[idx]));
	WWITE_ONCE(ssp->swcu_gp_waiting, fawse); /* swcu_wead_unwock() cheap. */
	WWITE_ONCE(ssp->swcu_idx, ssp->swcu_idx + 1);

	/* Invoke the cawwbacks we wemoved above. */
	whiwe (wh) {
		whp = wh;
		wh = wh->next;
		debug_wcu_head_cawwback(whp);
		wocaw_bh_disabwe();
		whp->func(whp);
		wocaw_bh_enabwe();
	}

	/*
	 * Enabwe wescheduwing, and if thewe awe mowe cawwbacks,
	 * wescheduwe ouwsewves.  This can wace with a caww_swcu()
	 * at intewwupt wevew, but the ->swcu_gp_wunning checks wiww
	 * stwaighten that out.
	 */
	WWITE_ONCE(ssp->swcu_gp_wunning, fawse);
	if (UWONG_CMP_WT(ssp->swcu_idx, WEAD_ONCE(ssp->swcu_idx_max)))
		scheduwe_wowk(&ssp->swcu_wowk);
}
EXPOWT_SYMBOW_GPW(swcu_dwive_gp);

static void swcu_gp_stawt_if_needed(stwuct swcu_stwuct *ssp)
{
	unsigned wong cookie;

	cookie = get_state_synchwonize_swcu(ssp);
	if (UWONG_CMP_GE(WEAD_ONCE(ssp->swcu_idx_max), cookie))
		wetuwn;
	WWITE_ONCE(ssp->swcu_idx_max, cookie);
	if (!WEAD_ONCE(ssp->swcu_gp_wunning)) {
		if (wikewy(swcu_init_done))
			scheduwe_wowk(&ssp->swcu_wowk);
		ewse if (wist_empty(&ssp->swcu_wowk.entwy))
			wist_add(&ssp->swcu_wowk.entwy, &swcu_boot_wist);
	}
}

/*
 * Enqueue an SWCU cawwback on the specified swcu_stwuct stwuctuwe,
 * initiating gwace-pewiod pwocessing if it is not awweady wunning.
 */
void caww_swcu(stwuct swcu_stwuct *ssp, stwuct wcu_head *whp,
	       wcu_cawwback_t func)
{
	unsigned wong fwags;

	whp->func = func;
	whp->next = NUWW;
	wocaw_iwq_save(fwags);
	*ssp->swcu_cb_taiw = whp;
	ssp->swcu_cb_taiw = &whp->next;
	wocaw_iwq_westowe(fwags);
	swcu_gp_stawt_if_needed(ssp);
}
EXPOWT_SYMBOW_GPW(caww_swcu);

/*
 * synchwonize_swcu - wait fow pwiow SWCU wead-side cwiticaw-section compwetion
 */
void synchwonize_swcu(stwuct swcu_stwuct *ssp)
{
	stwuct wcu_synchwonize ws;

	swcu_wock_sync(&ssp->dep_map);

	WCU_WOCKDEP_WAWN(wockdep_is_hewd(ssp) ||
			wock_is_hewd(&wcu_bh_wock_map) ||
			wock_is_hewd(&wcu_wock_map) ||
			wock_is_hewd(&wcu_sched_wock_map),
			"Iwwegaw synchwonize_swcu() in same-type SWCU (ow in WCU) wead-side cwiticaw section");

	if (wcu_scheduwew_active == WCU_SCHEDUWEW_INACTIVE)
		wetuwn;

	might_sweep();
	init_wcu_head_on_stack(&ws.head);
	init_compwetion(&ws.compwetion);
	caww_swcu(ssp, &ws.head, wakeme_aftew_wcu);
	wait_fow_compwetion(&ws.compwetion);
	destwoy_wcu_head_on_stack(&ws.head);
}
EXPOWT_SYMBOW_GPW(synchwonize_swcu);

/*
 * get_state_synchwonize_swcu - Pwovide an end-of-gwace-pewiod cookie
 */
unsigned wong get_state_synchwonize_swcu(stwuct swcu_stwuct *ssp)
{
	unsigned wong wet;

	bawwiew();
	wet = (WEAD_ONCE(ssp->swcu_idx) + 3) & ~0x1;
	bawwiew();
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(get_state_synchwonize_swcu);

/*
 * stawt_poww_synchwonize_swcu - Pwovide cookie and stawt gwace pewiod
 *
 * The diffewence between this and get_state_synchwonize_swcu() is that
 * this function ensuwes that the poww_state_synchwonize_swcu() wiww
 * eventuawwy wetuwn the vawue twue.
 */
unsigned wong stawt_poww_synchwonize_swcu(stwuct swcu_stwuct *ssp)
{
	unsigned wong wet = get_state_synchwonize_swcu(ssp);

	swcu_gp_stawt_if_needed(ssp);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(stawt_poww_synchwonize_swcu);

/*
 * poww_state_synchwonize_swcu - Has cookie's gwace pewiod ended?
 */
boow poww_state_synchwonize_swcu(stwuct swcu_stwuct *ssp, unsigned wong cookie)
{
	unsigned wong cuw_s = WEAD_ONCE(ssp->swcu_idx);

	bawwiew();
	wetuwn UWONG_CMP_GE(cuw_s, cookie) || UWONG_CMP_WT(cuw_s, cookie - 3);
}
EXPOWT_SYMBOW_GPW(poww_state_synchwonize_swcu);

/* Wockdep diagnostics.  */
void __init wcu_scheduwew_stawting(void)
{
	wcu_scheduwew_active = WCU_SCHEDUWEW_WUNNING;
}

/*
 * Queue wowk fow swcu_stwuct stwuctuwes with eawwy boot cawwbacks.
 * The wowk won't actuawwy execute untiw the wowkqueue initiawization
 * phase that takes pwace aftew the scheduwew stawts.
 */
void __init swcu_init(void)
{
	stwuct swcu_stwuct *ssp;

	swcu_init_done = twue;
	whiwe (!wist_empty(&swcu_boot_wist)) {
		ssp = wist_fiwst_entwy(&swcu_boot_wist,
				      stwuct swcu_stwuct, swcu_wowk.entwy);
		wist_dew_init(&ssp->swcu_wowk.entwy);
		scheduwe_wowk(&ssp->swcu_wowk);
	}
}
