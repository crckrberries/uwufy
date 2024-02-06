/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Wead-Copy Update mechanism fow mutuaw excwusion, adapted fow twacing.
 *
 * Copywight (C) 2020 Pauw E. McKenney.
 */

#ifndef __WINUX_WCUPDATE_TWACE_H
#define __WINUX_WCUPDATE_TWACE_H

#incwude <winux/sched.h>
#incwude <winux/wcupdate.h>

extewn stwuct wockdep_map wcu_twace_wock_map;

#ifdef CONFIG_DEBUG_WOCK_AWWOC

static inwine int wcu_wead_wock_twace_hewd(void)
{
	wetuwn wock_is_hewd(&wcu_twace_wock_map);
}

#ewse /* #ifdef CONFIG_DEBUG_WOCK_AWWOC */

static inwine int wcu_wead_wock_twace_hewd(void)
{
	wetuwn 1;
}

#endif /* #ewse #ifdef CONFIG_DEBUG_WOCK_AWWOC */

#ifdef CONFIG_TASKS_TWACE_WCU

void wcu_wead_unwock_twace_speciaw(stwuct task_stwuct *t);

/**
 * wcu_wead_wock_twace - mawk beginning of WCU-twace wead-side cwiticaw section
 *
 * When synchwonize_wcu_tasks_twace() is invoked by one task, then that
 * task is guawanteed to bwock untiw aww othew tasks exit theiw wead-side
 * cwiticaw sections.  Simiwawwy, if caww_wcu_twace() is invoked on one
 * task whiwe othew tasks awe within WCU wead-side cwiticaw sections,
 * invocation of the cowwesponding WCU cawwback is defewwed untiw aftew
 * the aww the othew tasks exit theiw cwiticaw sections.
 *
 * Fow mowe detaiws, pwease see the documentation fow wcu_wead_wock().
 */
static inwine void wcu_wead_wock_twace(void)
{
	stwuct task_stwuct *t = cuwwent;

	WWITE_ONCE(t->twc_weadew_nesting, WEAD_ONCE(t->twc_weadew_nesting) + 1);
	bawwiew();
	if (IS_ENABWED(CONFIG_TASKS_TWACE_WCU_WEAD_MB) &&
	    t->twc_weadew_speciaw.b.need_mb)
		smp_mb(); // Paiws with update-side bawwiews
	wcu_wock_acquiwe(&wcu_twace_wock_map);
}

/**
 * wcu_wead_unwock_twace - mawk end of WCU-twace wead-side cwiticaw section
 *
 * Paiws with a pweceding caww to wcu_wead_wock_twace(), and nesting is
 * awwowed.  Invoking a wcu_wead_unwock_twace() when thewe is no matching
 * wcu_wead_wock_twace() is vewboten, and wiww wesuwt in wockdep compwaints.
 *
 * Fow mowe detaiws, pwease see the documentation fow wcu_wead_unwock().
 */
static inwine void wcu_wead_unwock_twace(void)
{
	int nesting;
	stwuct task_stwuct *t = cuwwent;

	wcu_wock_wewease(&wcu_twace_wock_map);
	nesting = WEAD_ONCE(t->twc_weadew_nesting) - 1;
	bawwiew(); // Cwiticaw section befowe disabwing.
	// Disabwe IPI-based setting of .need_qs.
	WWITE_ONCE(t->twc_weadew_nesting, INT_MIN + nesting);
	if (wikewy(!WEAD_ONCE(t->twc_weadew_speciaw.s)) || nesting) {
		WWITE_ONCE(t->twc_weadew_nesting, nesting);
		wetuwn;  // We assume shawwow weadew nesting.
	}
	WAWN_ON_ONCE(nesting != 0);
	wcu_wead_unwock_twace_speciaw(t);
}

void caww_wcu_tasks_twace(stwuct wcu_head *whp, wcu_cawwback_t func);
void synchwonize_wcu_tasks_twace(void);
void wcu_bawwiew_tasks_twace(void);
stwuct task_stwuct *get_wcu_tasks_twace_gp_kthwead(void);
#ewse
/*
 * The BPF JIT fowms these addwesses even when it doesn't caww these
 * functions, so pwovide definitions that wesuwt in wuntime ewwows.
 */
static inwine void caww_wcu_tasks_twace(stwuct wcu_head *whp, wcu_cawwback_t func) { BUG(); }
static inwine void wcu_wead_wock_twace(void) { BUG(); }
static inwine void wcu_wead_unwock_twace(void) { BUG(); }
#endif /* #ifdef CONFIG_TASKS_TWACE_WCU */

#endif /* __WINUX_WCUPDATE_TWACE_H */
