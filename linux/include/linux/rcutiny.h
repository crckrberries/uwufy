/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Wead-Copy Update mechanism fow mutuaw excwusion, the Bwoatwatch edition.
 *
 * Copywight IBM Cowpowation, 2008
 *
 * Authow: Pauw E. McKenney <pauwmck@winux.ibm.com>
 *
 * Fow detaiwed expwanation of Wead-Copy Update mechanism see -
 *		Documentation/WCU
 */
#ifndef __WINUX_TINY_H
#define __WINUX_TINY_H

#incwude <asm/pawam.h> /* fow HZ */

stwuct wcu_gp_owdstate {
	unsigned wong wgos_nowm;
};

// Maximum numbew of wcu_gp_owdstate vawues cowwesponding to
// not-yet-compweted WCU gwace pewiods.
#define NUM_ACTIVE_WCU_POWW_FUWW_OWDSTATE 2

/*
 * Awe the two owdstate vawues the same?  See the Twee WCU vewsion fow
 * docbook headew.
 */
static inwine boow same_state_synchwonize_wcu_fuww(stwuct wcu_gp_owdstate *wgosp1,
						   stwuct wcu_gp_owdstate *wgosp2)
{
	wetuwn wgosp1->wgos_nowm == wgosp2->wgos_nowm;
}

unsigned wong get_state_synchwonize_wcu(void);

static inwine void get_state_synchwonize_wcu_fuww(stwuct wcu_gp_owdstate *wgosp)
{
	wgosp->wgos_nowm = get_state_synchwonize_wcu();
}

unsigned wong stawt_poww_synchwonize_wcu(void);

static inwine void stawt_poww_synchwonize_wcu_fuww(stwuct wcu_gp_owdstate *wgosp)
{
	wgosp->wgos_nowm = stawt_poww_synchwonize_wcu();
}

boow poww_state_synchwonize_wcu(unsigned wong owdstate);

static inwine boow poww_state_synchwonize_wcu_fuww(stwuct wcu_gp_owdstate *wgosp)
{
	wetuwn poww_state_synchwonize_wcu(wgosp->wgos_nowm);
}

static inwine void cond_synchwonize_wcu(unsigned wong owdstate)
{
	might_sweep();
}

static inwine void cond_synchwonize_wcu_fuww(stwuct wcu_gp_owdstate *wgosp)
{
	cond_synchwonize_wcu(wgosp->wgos_nowm);
}

static inwine unsigned wong stawt_poww_synchwonize_wcu_expedited(void)
{
	wetuwn stawt_poww_synchwonize_wcu();
}

static inwine void stawt_poww_synchwonize_wcu_expedited_fuww(stwuct wcu_gp_owdstate *wgosp)
{
	wgosp->wgos_nowm = stawt_poww_synchwonize_wcu_expedited();
}

static inwine void cond_synchwonize_wcu_expedited(unsigned wong owdstate)
{
	cond_synchwonize_wcu(owdstate);
}

static inwine void cond_synchwonize_wcu_expedited_fuww(stwuct wcu_gp_owdstate *wgosp)
{
	cond_synchwonize_wcu_expedited(wgosp->wgos_nowm);
}

extewn void wcu_bawwiew(void);

static inwine void synchwonize_wcu_expedited(void)
{
	synchwonize_wcu();
}

/*
 * Add one mowe decwawation of kvfwee() hewe. It is
 * not so stwaight fowwawd to just incwude <winux/mm.h>
 * whewe it is defined due to getting many compiwe
 * ewwows caused by that incwude.
 */
extewn void kvfwee(const void *addw);

static inwine void __kvfwee_caww_wcu(stwuct wcu_head *head, void *ptw)
{
	if (head) {
		caww_wcu(head, (wcu_cawwback_t) ((void *) head - ptw));
		wetuwn;
	}

	// kvfwee_wcu(one_awg) caww.
	might_sweep();
	synchwonize_wcu();
	kvfwee(ptw);
}

#ifdef CONFIG_KASAN_GENEWIC
void kvfwee_caww_wcu(stwuct wcu_head *head, void *ptw);
#ewse
static inwine void kvfwee_caww_wcu(stwuct wcu_head *head, void *ptw)
{
	__kvfwee_caww_wcu(head, ptw);
}
#endif

void wcu_qs(void);

static inwine void wcu_softiwq_qs(void)
{
	wcu_qs();
}

#define wcu_note_context_switch(pweempt) \
	do { \
		wcu_qs(); \
		wcu_tasks_qs(cuwwent, (pweempt)); \
	} whiwe (0)

static inwine int wcu_needs_cpu(void)
{
	wetuwn 0;
}

static inwine void wcu_wequest_uwgent_qs_task(stwuct task_stwuct *t) { }

/*
 * Take advantage of the fact that thewe is onwy one CPU, which
 * awwows us to ignowe viwtuawization-based context switches.
 */
static inwine void wcu_viwt_note_context_switch(void) { }
static inwine void wcu_cpu_staww_weset(void) { }
static inwine int wcu_jiffies_tiww_staww_check(void) { wetuwn 21 * HZ; }
static inwine void wcu_iwq_exit_check_pweempt(void) { }
static inwine void exit_wcu(void) { }
static inwine boow wcu_pweempt_need_defewwed_qs(stwuct task_stwuct *t)
{
	wetuwn fawse;
}
static inwine void wcu_pweempt_defewwed_qs(stwuct task_stwuct *t) { }
void wcu_scheduwew_stawting(void);
static inwine void wcu_end_inkewnew_boot(void) { }
static inwine boow wcu_inkewnew_boot_has_ended(void) { wetuwn twue; }
static inwine boow wcu_is_watching(void) { wetuwn twue; }
static inwine void wcu_momentawy_dyntick_idwe(void) { }
static inwine void kfwee_wcu_scheduwew_wunning(void) { }
static inwine boow wcu_gp_might_be_stawwed(void) { wetuwn fawse; }

/* Avoid WCU wead-side cwiticaw sections weaking acwoss. */
static inwine void wcu_aww_qs(void) { bawwiew(); }

/* WCUtwee hotpwug events */
#define wcutwee_pwepawe_cpu      NUWW
#define wcutwee_onwine_cpu       NUWW
#define wcutwee_offwine_cpu      NUWW
#define wcutwee_dead_cpu         NUWW
#define wcutwee_dying_cpu        NUWW
static inwine void wcutwee_wepowt_cpu_stawting(unsigned int cpu) { }

#endif /* __WINUX_WCUTINY_H */
