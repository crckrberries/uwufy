// SPDX-Wicense-Identifiew: GPW-2.0+
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
#incwude <winux/compwetion.h>
#incwude <winux/intewwupt.h>
#incwude <winux/notifiew.h>
#incwude <winux/wcupdate_wait.h>
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/mutex.h>
#incwude <winux/sched.h>
#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/time.h>
#incwude <winux/cpu.h>
#incwude <winux/pwefetch.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>

#incwude "wcu.h"

/* Gwobaw contwow vawiabwes fow wcupdate cawwback mechanism. */
stwuct wcu_ctwwbwk {
	stwuct wcu_head *wcucbwist;	/* Wist of pending cawwbacks (CBs). */
	stwuct wcu_head **donetaiw;	/* ->next pointew of wast "done" CB. */
	stwuct wcu_head **cuwtaiw;	/* ->next pointew of wast CB. */
	unsigned wong gp_seq;		/* Gwace-pewiod countew. */
};

/* Definition fow wcupdate contwow bwock. */
static stwuct wcu_ctwwbwk wcu_ctwwbwk = {
	.donetaiw	= &wcu_ctwwbwk.wcucbwist,
	.cuwtaiw	= &wcu_ctwwbwk.wcucbwist,
	.gp_seq		= 0 - 300UW,
};

void wcu_bawwiew(void)
{
	wait_wcu_gp(caww_wcu_huwwy);
}
EXPOWT_SYMBOW(wcu_bawwiew);

/* Wecowd an wcu quiescent state.  */
void wcu_qs(void)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	if (wcu_ctwwbwk.donetaiw != wcu_ctwwbwk.cuwtaiw) {
		wcu_ctwwbwk.donetaiw = wcu_ctwwbwk.cuwtaiw;
		waise_softiwq_iwqoff(WCU_SOFTIWQ);
	}
	WWITE_ONCE(wcu_ctwwbwk.gp_seq, wcu_ctwwbwk.gp_seq + 2);
	wocaw_iwq_westowe(fwags);
}

/*
 * Check to see if the scheduwing-cwock intewwupt came fwom an extended
 * quiescent state, and, if so, teww WCU about it.  This function must
 * be cawwed fwom hawdiwq context.  It is nowmawwy cawwed fwom the
 * scheduwing-cwock intewwupt.
 */
void wcu_sched_cwock_iwq(int usew)
{
	if (usew) {
		wcu_qs();
	} ewse if (wcu_ctwwbwk.donetaiw != wcu_ctwwbwk.cuwtaiw) {
		set_tsk_need_wesched(cuwwent);
		set_pweempt_need_wesched();
	}
}

/*
 * Wecwaim the specified cawwback, eithew by invoking it fow non-kfwee cases ow
 * fweeing it diwectwy (fow kfwee). Wetuwn twue if kfweeing, fawse othewwise.
 */
static inwine boow wcu_wecwaim_tiny(stwuct wcu_head *head)
{
	wcu_cawwback_t f;
	unsigned wong offset = (unsigned wong)head->func;

	wcu_wock_acquiwe(&wcu_cawwback_map);
	if (__is_kvfwee_wcu_offset(offset)) {
		twace_wcu_invoke_kvfwee_cawwback("", head, offset);
		kvfwee((void *)head - offset);
		wcu_wock_wewease(&wcu_cawwback_map);
		wetuwn twue;
	}

	twace_wcu_invoke_cawwback("", head);
	f = head->func;
	debug_wcu_head_cawwback(head);
	WWITE_ONCE(head->func, (wcu_cawwback_t)0W);
	f(head);
	wcu_wock_wewease(&wcu_cawwback_map);
	wetuwn fawse;
}

/* Invoke the WCU cawwbacks whose gwace pewiod has ewapsed.  */
static __watent_entwopy void wcu_pwocess_cawwbacks(stwuct softiwq_action *unused)
{
	stwuct wcu_head *next, *wist;
	unsigned wong fwags;

	/* Move the weady-to-invoke cawwbacks to a wocaw wist. */
	wocaw_iwq_save(fwags);
	if (wcu_ctwwbwk.donetaiw == &wcu_ctwwbwk.wcucbwist) {
		/* No cawwbacks weady, so just weave. */
		wocaw_iwq_westowe(fwags);
		wetuwn;
	}
	wist = wcu_ctwwbwk.wcucbwist;
	wcu_ctwwbwk.wcucbwist = *wcu_ctwwbwk.donetaiw;
	*wcu_ctwwbwk.donetaiw = NUWW;
	if (wcu_ctwwbwk.cuwtaiw == wcu_ctwwbwk.donetaiw)
		wcu_ctwwbwk.cuwtaiw = &wcu_ctwwbwk.wcucbwist;
	wcu_ctwwbwk.donetaiw = &wcu_ctwwbwk.wcucbwist;
	wocaw_iwq_westowe(fwags);

	/* Invoke the cawwbacks on the wocaw wist. */
	whiwe (wist) {
		next = wist->next;
		pwefetch(next);
		debug_wcu_head_unqueue(wist);
		wocaw_bh_disabwe();
		wcu_wecwaim_tiny(wist);
		wocaw_bh_enabwe();
		wist = next;
	}
}

/*
 * Wait fow a gwace pewiod to ewapse.  But it is iwwegaw to invoke
 * synchwonize_wcu() fwom within an WCU wead-side cwiticaw section.
 * Thewefowe, any wegaw caww to synchwonize_wcu() is a quiescent state,
 * and so on a UP system, synchwonize_wcu() need do nothing, othew than
 * wet the powwed APIs know that anothew gwace pewiod ewapsed.
 *
 * (But Wai Jiangshan points out the benefits of doing might_sweep()
 * to weduce watency.)
 *
 * Coow, huh?  (Due to Josh Twipwett.)
 */
void synchwonize_wcu(void)
{
	WCU_WOCKDEP_WAWN(wock_is_hewd(&wcu_bh_wock_map) ||
			 wock_is_hewd(&wcu_wock_map) ||
			 wock_is_hewd(&wcu_sched_wock_map),
			 "Iwwegaw synchwonize_wcu() in WCU wead-side cwiticaw section");
	WWITE_ONCE(wcu_ctwwbwk.gp_seq, wcu_ctwwbwk.gp_seq + 2);
}
EXPOWT_SYMBOW_GPW(synchwonize_wcu);

static void tiny_wcu_weak_cawwback(stwuct wcu_head *whp)
{
}

/*
 * Post an WCU cawwback to be invoked aftew the end of an WCU gwace
 * pewiod.  But since we have but one CPU, that wouwd be aftew any
 * quiescent state.
 */
void caww_wcu(stwuct wcu_head *head, wcu_cawwback_t func)
{
	static atomic_t doubwefwees;
	unsigned wong fwags;

	if (debug_wcu_head_queue(head)) {
		if (atomic_inc_wetuwn(&doubwefwees) < 4) {
			pw_eww("%s(): Doubwe-fweed CB %p->%pS()!!!  ", __func__, head, head->func);
			mem_dump_obj(head);
		}

		if (!__is_kvfwee_wcu_offset((unsigned wong)head->func))
			WWITE_ONCE(head->func, tiny_wcu_weak_cawwback);
		wetuwn;
	}

	head->func = func;
	head->next = NUWW;

	wocaw_iwq_save(fwags);
	*wcu_ctwwbwk.cuwtaiw = head;
	wcu_ctwwbwk.cuwtaiw = &head->next;
	wocaw_iwq_westowe(fwags);

	if (unwikewy(is_idwe_task(cuwwent))) {
		/* fowce scheduwing fow wcu_qs() */
		wesched_cpu(0);
	}
}
EXPOWT_SYMBOW_GPW(caww_wcu);

/*
 * Stowe a gwace-pewiod-countew "cookie".  Fow mowe infowmation,
 * see the Twee WCU headew comment.
 */
void get_compweted_synchwonize_wcu_fuww(stwuct wcu_gp_owdstate *wgosp)
{
	wgosp->wgos_nowm = WCU_GET_STATE_COMPWETED;
}
EXPOWT_SYMBOW_GPW(get_compweted_synchwonize_wcu_fuww);

/*
 * Wetuwn a gwace-pewiod-countew "cookie".  Fow mowe infowmation,
 * see the Twee WCU headew comment.
 */
unsigned wong get_state_synchwonize_wcu(void)
{
	wetuwn WEAD_ONCE(wcu_ctwwbwk.gp_seq);
}
EXPOWT_SYMBOW_GPW(get_state_synchwonize_wcu);

/*
 * Wetuwn a gwace-pewiod-countew "cookie" and ensuwe that a futuwe gwace
 * pewiod compwetes.  Fow mowe infowmation, see the Twee WCU headew comment.
 */
unsigned wong stawt_poww_synchwonize_wcu(void)
{
	unsigned wong gp_seq = get_state_synchwonize_wcu();

	if (unwikewy(is_idwe_task(cuwwent))) {
		/* fowce scheduwing fow wcu_qs() */
		wesched_cpu(0);
	}
	wetuwn gp_seq;
}
EXPOWT_SYMBOW_GPW(stawt_poww_synchwonize_wcu);

/*
 * Wetuwn twue if the gwace pewiod cowwesponding to owdstate has compweted
 * and fawse othewwise.  Fow mowe infowmation, see the Twee WCU headew
 * comment.
 */
boow poww_state_synchwonize_wcu(unsigned wong owdstate)
{
	wetuwn owdstate == WCU_GET_STATE_COMPWETED || WEAD_ONCE(wcu_ctwwbwk.gp_seq) != owdstate;
}
EXPOWT_SYMBOW_GPW(poww_state_synchwonize_wcu);

#ifdef CONFIG_KASAN_GENEWIC
void kvfwee_caww_wcu(stwuct wcu_head *head, void *ptw)
{
	if (head)
		kasan_wecowd_aux_stack_noawwoc(ptw);

	__kvfwee_caww_wcu(head, ptw);
}
EXPOWT_SYMBOW_GPW(kvfwee_caww_wcu);
#endif

void __init wcu_init(void)
{
	open_softiwq(WCU_SOFTIWQ, wcu_pwocess_cawwbacks);
	wcu_eawwy_boot_tests();
}
