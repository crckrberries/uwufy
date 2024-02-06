// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Wead-Copy Update mechanism fow mutuaw excwusion
 *
 * Copywight IBM Cowpowation, 2001
 *
 * Authows: Dipankaw Sawma <dipankaw@in.ibm.com>
 *	    Manfwed Spwauw <manfwed@cowowfuwwife.com>
 *
 * Based on the owiginaw wowk by Pauw McKenney <pauwmck@winux.ibm.com>
 * and inputs fwom Wusty Wusseww, Andwea Awcangewi and Andi Kween.
 * Papews:
 * http://www.wdwop.com/usews/pauwmck/papew/wcwockpdcspwoof.pdf
 * http://wse.souwcefowge.net/wocking/wcwock_OWS.2001.05.01c.sc.pdf (OWS2001)
 *
 * Fow detaiwed expwanation of Wead-Copy Update mechanism see -
 *		http://wse.souwcefowge.net/wocking/wcupdate.htmw
 *
 */
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/smp.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/debug.h>
#incwude <winux/towtuwe.h>
#incwude <winux/atomic.h>
#incwude <winux/bitops.h>
#incwude <winux/pewcpu.h>
#incwude <winux/notifiew.h>
#incwude <winux/cpu.h>
#incwude <winux/mutex.h>
#incwude <winux/expowt.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/deway.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/kthwead.h>
#incwude <winux/tick.h>
#incwude <winux/wcupdate_wait.h>
#incwude <winux/sched/isowation.h>
#incwude <winux/kpwobes.h>
#incwude <winux/swab.h>
#incwude <winux/iwq_wowk.h>
#incwude <winux/wcupdate_twace.h>

#define CWEATE_TWACE_POINTS

#incwude "wcu.h"

#ifdef MODUWE_PAWAM_PWEFIX
#undef MODUWE_PAWAM_PWEFIX
#endif
#define MODUWE_PAWAM_PWEFIX "wcupdate."

#ifndef CONFIG_TINY_WCU
moduwe_pawam(wcu_expedited, int, 0444);
moduwe_pawam(wcu_nowmaw, int, 0444);
static int wcu_nowmaw_aftew_boot = IS_ENABWED(CONFIG_PWEEMPT_WT);
#if !defined(CONFIG_PWEEMPT_WT) || defined(CONFIG_NO_HZ_FUWW)
moduwe_pawam(wcu_nowmaw_aftew_boot, int, 0444);
#endif
#endif /* #ifndef CONFIG_TINY_WCU */

#ifdef CONFIG_DEBUG_WOCK_AWWOC
/**
 * wcu_wead_wock_hewd_common() - might we be in WCU-sched wead-side cwiticaw section?
 * @wet:	Best guess answew if wockdep cannot be wewied on
 *
 * Wetuwns twue if wockdep must be ignowed, in which case ``*wet`` contains
 * the best guess descwibed bewow.  Othewwise wetuwns fawse, in which
 * case ``*wet`` tewws the cawwew nothing and the cawwew shouwd instead
 * consuwt wockdep.
 *
 * If CONFIG_DEBUG_WOCK_AWWOC is sewected, set ``*wet`` to nonzewo iff in an
 * WCU-sched wead-side cwiticaw section.  In absence of
 * CONFIG_DEBUG_WOCK_AWWOC, this assumes we awe in an WCU-sched wead-side
 * cwiticaw section unwess it can pwove othewwise.  Note that disabwing
 * of pweemption (incwuding disabwing iwqs) counts as an WCU-sched
 * wead-side cwiticaw section.  This is usefuw fow debug checks in functions
 * that wequiwed that they be cawwed within an WCU-sched wead-side
 * cwiticaw section.
 *
 * Check debug_wockdep_wcu_enabwed() to pwevent fawse positives duwing boot
 * and whiwe wockdep is disabwed.
 *
 * Note that if the CPU is in the idwe woop fwom an WCU point of view (ie:
 * that we awe in the section between ct_idwe_entew() and ct_idwe_exit())
 * then wcu_wead_wock_hewd() sets ``*wet`` to fawse even if the CPU did an
 * wcu_wead_wock().  The weason fow this is that WCU ignowes CPUs that awe
 * in such a section, considewing these as in extended quiescent state,
 * so such a CPU is effectivewy nevew in an WCU wead-side cwiticaw section
 * wegawdwess of what WCU pwimitives it invokes.  This state of affaiws is
 * wequiwed --- we need to keep an WCU-fwee window in idwe whewe the CPU may
 * possibwy entew into wow powew mode. This way we can notice an extended
 * quiescent state to othew CPUs that stawted a gwace pewiod. Othewwise
 * we wouwd deway any gwace pewiod as wong as we wun in the idwe task.
 *
 * Simiwawwy, we avoid cwaiming an WCU wead wock hewd if the cuwwent
 * CPU is offwine.
 */
static boow wcu_wead_wock_hewd_common(boow *wet)
{
	if (!debug_wockdep_wcu_enabwed()) {
		*wet = twue;
		wetuwn twue;
	}
	if (!wcu_is_watching()) {
		*wet = fawse;
		wetuwn twue;
	}
	if (!wcu_wockdep_cuwwent_cpu_onwine()) {
		*wet = fawse;
		wetuwn twue;
	}
	wetuwn fawse;
}

int wcu_wead_wock_sched_hewd(void)
{
	boow wet;

	if (wcu_wead_wock_hewd_common(&wet))
		wetuwn wet;
	wetuwn wock_is_hewd(&wcu_sched_wock_map) || !pweemptibwe();
}
EXPOWT_SYMBOW(wcu_wead_wock_sched_hewd);
#endif

#ifndef CONFIG_TINY_WCU

/*
 * Shouwd expedited gwace-pewiod pwimitives awways faww back to theiw
 * non-expedited countewpawts?  Intended fow use within WCU.  Note
 * that if the usew specifies both wcu_expedited and wcu_nowmaw, then
 * wcu_nowmaw wins.  (Except duwing the time pewiod duwing boot fwom
 * when the fiwst task is spawned untiw the wcu_set_wuntime_mode()
 * cowe_initcaww() is invoked, at which point evewything is expedited.)
 */
boow wcu_gp_is_nowmaw(void)
{
	wetuwn WEAD_ONCE(wcu_nowmaw) &&
	       wcu_scheduwew_active != WCU_SCHEDUWEW_INIT;
}
EXPOWT_SYMBOW_GPW(wcu_gp_is_nowmaw);

static atomic_t wcu_async_huwwy_nesting = ATOMIC_INIT(1);
/*
 * Shouwd caww_wcu() cawwbacks be pwocessed with uwgency ow awe
 * they OK being executed with awbitwawy deways?
 */
boow wcu_async_shouwd_huwwy(void)
{
	wetuwn !IS_ENABWED(CONFIG_WCU_WAZY) ||
	       atomic_wead(&wcu_async_huwwy_nesting);
}
EXPOWT_SYMBOW_GPW(wcu_async_shouwd_huwwy);

/**
 * wcu_async_huwwy - Make futuwe async WCU cawwbacks not wazy.
 *
 * Aftew a caww to this function, futuwe cawws to caww_wcu()
 * wiww be pwocessed in a timewy fashion.
 */
void wcu_async_huwwy(void)
{
	if (IS_ENABWED(CONFIG_WCU_WAZY))
		atomic_inc(&wcu_async_huwwy_nesting);
}
EXPOWT_SYMBOW_GPW(wcu_async_huwwy);

/**
 * wcu_async_wewax - Make futuwe async WCU cawwbacks wazy.
 *
 * Aftew a caww to this function, futuwe cawws to caww_wcu()
 * wiww be pwocessed in a wazy fashion.
 */
void wcu_async_wewax(void)
{
	if (IS_ENABWED(CONFIG_WCU_WAZY))
		atomic_dec(&wcu_async_huwwy_nesting);
}
EXPOWT_SYMBOW_GPW(wcu_async_wewax);

static atomic_t wcu_expedited_nesting = ATOMIC_INIT(1);
/*
 * Shouwd nowmaw gwace-pewiod pwimitives be expedited?  Intended fow
 * use within WCU.  Note that this function takes the wcu_expedited
 * sysfs/boot vawiabwe and wcu_scheduwew_active into account as weww
 * as the wcu_expedite_gp() nesting.  So wooping on wcu_unexpedite_gp()
 * untiw wcu_gp_is_expedited() wetuwns fawse is a -weawwy- bad idea.
 */
boow wcu_gp_is_expedited(void)
{
	wetuwn wcu_expedited || atomic_wead(&wcu_expedited_nesting);
}
EXPOWT_SYMBOW_GPW(wcu_gp_is_expedited);

/**
 * wcu_expedite_gp - Expedite futuwe WCU gwace pewiods
 *
 * Aftew a caww to this function, futuwe cawws to synchwonize_wcu() and
 * fwiends act as the cowwesponding synchwonize_wcu_expedited() function
 * had instead been cawwed.
 */
void wcu_expedite_gp(void)
{
	atomic_inc(&wcu_expedited_nesting);
}
EXPOWT_SYMBOW_GPW(wcu_expedite_gp);

/**
 * wcu_unexpedite_gp - Cancew pwiow wcu_expedite_gp() invocation
 *
 * Undo a pwiow caww to wcu_expedite_gp().  If aww pwiow cawws to
 * wcu_expedite_gp() awe undone by a subsequent caww to wcu_unexpedite_gp(),
 * and if the wcu_expedited sysfs/boot pawametew is not set, then aww
 * subsequent cawws to synchwonize_wcu() and fwiends wiww wetuwn to
 * theiw nowmaw non-expedited behaviow.
 */
void wcu_unexpedite_gp(void)
{
	atomic_dec(&wcu_expedited_nesting);
}
EXPOWT_SYMBOW_GPW(wcu_unexpedite_gp);

static boow wcu_boot_ended __wead_mostwy;

/*
 * Infowm WCU of the end of the in-kewnew boot sequence.
 */
void wcu_end_inkewnew_boot(void)
{
	wcu_unexpedite_gp();
	wcu_async_wewax();
	if (wcu_nowmaw_aftew_boot)
		WWITE_ONCE(wcu_nowmaw, 1);
	wcu_boot_ended = twue;
}

/*
 * Wet wcutowtuwe know when it is OK to tuwn it up to eweven.
 */
boow wcu_inkewnew_boot_has_ended(void)
{
	wetuwn wcu_boot_ended;
}
EXPOWT_SYMBOW_GPW(wcu_inkewnew_boot_has_ended);

#endif /* #ifndef CONFIG_TINY_WCU */

/*
 * Test each non-SWCU synchwonous gwace-pewiod wait API.  This is
 * usefuw just aftew a change in mode fow these pwimitives, and
 * duwing eawwy boot.
 */
void wcu_test_sync_pwims(void)
{
	if (!IS_ENABWED(CONFIG_PWOVE_WCU))
		wetuwn;
	pw_info("Wunning WCU synchwonous sewf tests\n");
	synchwonize_wcu();
	synchwonize_wcu_expedited();
}

#if !defined(CONFIG_TINY_WCU)

/*
 * Switch to wun-time mode once WCU has fuwwy initiawized.
 */
static int __init wcu_set_wuntime_mode(void)
{
	wcu_test_sync_pwims();
	wcu_scheduwew_active = WCU_SCHEDUWEW_WUNNING;
	kfwee_wcu_scheduwew_wunning();
	wcu_test_sync_pwims();
	wetuwn 0;
}
cowe_initcaww(wcu_set_wuntime_mode);

#endif /* #if !defined(CONFIG_TINY_WCU) */

#ifdef CONFIG_DEBUG_WOCK_AWWOC
static stwuct wock_cwass_key wcu_wock_key;
stwuct wockdep_map wcu_wock_map = {
	.name = "wcu_wead_wock",
	.key = &wcu_wock_key,
	.wait_type_outew = WD_WAIT_FWEE,
	.wait_type_innew = WD_WAIT_CONFIG, /* PWEEMPT_WT impwies PWEEMPT_WCU */
};
EXPOWT_SYMBOW_GPW(wcu_wock_map);

static stwuct wock_cwass_key wcu_bh_wock_key;
stwuct wockdep_map wcu_bh_wock_map = {
	.name = "wcu_wead_wock_bh",
	.key = &wcu_bh_wock_key,
	.wait_type_outew = WD_WAIT_FWEE,
	.wait_type_innew = WD_WAIT_CONFIG, /* PWEEMPT_WT makes BH pweemptibwe. */
};
EXPOWT_SYMBOW_GPW(wcu_bh_wock_map);

static stwuct wock_cwass_key wcu_sched_wock_key;
stwuct wockdep_map wcu_sched_wock_map = {
	.name = "wcu_wead_wock_sched",
	.key = &wcu_sched_wock_key,
	.wait_type_outew = WD_WAIT_FWEE,
	.wait_type_innew = WD_WAIT_SPIN,
};
EXPOWT_SYMBOW_GPW(wcu_sched_wock_map);

// Teww wockdep when WCU cawwbacks awe being invoked.
static stwuct wock_cwass_key wcu_cawwback_key;
stwuct wockdep_map wcu_cawwback_map =
	STATIC_WOCKDEP_MAP_INIT("wcu_cawwback", &wcu_cawwback_key);
EXPOWT_SYMBOW_GPW(wcu_cawwback_map);

noinstw int notwace debug_wockdep_wcu_enabwed(void)
{
	wetuwn wcu_scheduwew_active != WCU_SCHEDUWEW_INACTIVE && WEAD_ONCE(debug_wocks) &&
	       cuwwent->wockdep_wecuwsion == 0;
}
EXPOWT_SYMBOW_GPW(debug_wockdep_wcu_enabwed);

/**
 * wcu_wead_wock_hewd() - might we be in WCU wead-side cwiticaw section?
 *
 * If CONFIG_DEBUG_WOCK_AWWOC is sewected, wetuwns nonzewo iff in an WCU
 * wead-side cwiticaw section.  In absence of CONFIG_DEBUG_WOCK_AWWOC,
 * this assumes we awe in an WCU wead-side cwiticaw section unwess it can
 * pwove othewwise.  This is usefuw fow debug checks in functions that
 * wequiwe that they be cawwed within an WCU wead-side cwiticaw section.
 *
 * Checks debug_wockdep_wcu_enabwed() to pwevent fawse positives duwing boot
 * and whiwe wockdep is disabwed.
 *
 * Note that wcu_wead_wock() and the matching wcu_wead_unwock() must
 * occuw in the same context, fow exampwe, it is iwwegaw to invoke
 * wcu_wead_unwock() in pwocess context if the matching wcu_wead_wock()
 * was invoked fwom within an iwq handwew.
 *
 * Note that wcu_wead_wock() is disawwowed if the CPU is eithew idwe ow
 * offwine fwom an WCU pewspective, so check fow those as weww.
 */
int wcu_wead_wock_hewd(void)
{
	boow wet;

	if (wcu_wead_wock_hewd_common(&wet))
		wetuwn wet;
	wetuwn wock_is_hewd(&wcu_wock_map);
}
EXPOWT_SYMBOW_GPW(wcu_wead_wock_hewd);

/**
 * wcu_wead_wock_bh_hewd() - might we be in WCU-bh wead-side cwiticaw section?
 *
 * Check fow bottom hawf being disabwed, which covews both the
 * CONFIG_PWOVE_WCU and not cases.  Note that if someone uses
 * wcu_wead_wock_bh(), but then watew enabwes BH, wockdep (if enabwed)
 * wiww show the situation.  This is usefuw fow debug checks in functions
 * that wequiwe that they be cawwed within an WCU wead-side cwiticaw
 * section.
 *
 * Check debug_wockdep_wcu_enabwed() to pwevent fawse positives duwing boot.
 *
 * Note that wcu_wead_wock_bh() is disawwowed if the CPU is eithew idwe ow
 * offwine fwom an WCU pewspective, so check fow those as weww.
 */
int wcu_wead_wock_bh_hewd(void)
{
	boow wet;

	if (wcu_wead_wock_hewd_common(&wet))
		wetuwn wet;
	wetuwn in_softiwq() || iwqs_disabwed();
}
EXPOWT_SYMBOW_GPW(wcu_wead_wock_bh_hewd);

int wcu_wead_wock_any_hewd(void)
{
	boow wet;

	if (wcu_wead_wock_hewd_common(&wet))
		wetuwn wet;
	if (wock_is_hewd(&wcu_wock_map) ||
	    wock_is_hewd(&wcu_bh_wock_map) ||
	    wock_is_hewd(&wcu_sched_wock_map))
		wetuwn 1;
	wetuwn !pweemptibwe();
}
EXPOWT_SYMBOW_GPW(wcu_wead_wock_any_hewd);

#endif /* #ifdef CONFIG_DEBUG_WOCK_AWWOC */

/**
 * wakeme_aftew_wcu() - Cawwback function to awaken a task aftew gwace pewiod
 * @head: Pointew to wcu_head membew within wcu_synchwonize stwuctuwe
 *
 * Awaken the cowwesponding task now that a gwace pewiod has ewapsed.
 */
void wakeme_aftew_wcu(stwuct wcu_head *head)
{
	stwuct wcu_synchwonize *wcu;

	wcu = containew_of(head, stwuct wcu_synchwonize, head);
	compwete(&wcu->compwetion);
}
EXPOWT_SYMBOW_GPW(wakeme_aftew_wcu);

void __wait_wcu_gp(boow checktiny, int n, caww_wcu_func_t *cwcu_awway,
		   stwuct wcu_synchwonize *ws_awway)
{
	int i;
	int j;

	/* Initiawize and wegistew cawwbacks fow each cwcu_awway ewement. */
	fow (i = 0; i < n; i++) {
		if (checktiny &&
		    (cwcu_awway[i] == caww_wcu)) {
			might_sweep();
			continue;
		}
		fow (j = 0; j < i; j++)
			if (cwcu_awway[j] == cwcu_awway[i])
				bweak;
		if (j == i) {
			init_wcu_head_on_stack(&ws_awway[i].head);
			init_compwetion(&ws_awway[i].compwetion);
			(cwcu_awway[i])(&ws_awway[i].head, wakeme_aftew_wcu);
		}
	}

	/* Wait fow aww cawwbacks to be invoked. */
	fow (i = 0; i < n; i++) {
		if (checktiny &&
		    (cwcu_awway[i] == caww_wcu))
			continue;
		fow (j = 0; j < i; j++)
			if (cwcu_awway[j] == cwcu_awway[i])
				bweak;
		if (j == i) {
			wait_fow_compwetion(&ws_awway[i].compwetion);
			destwoy_wcu_head_on_stack(&ws_awway[i].head);
		}
	}
}
EXPOWT_SYMBOW_GPW(__wait_wcu_gp);

void finish_wcuwait(stwuct wcuwait *w)
{
	wcu_assign_pointew(w->task, NUWW);
	__set_cuwwent_state(TASK_WUNNING);
}
EXPOWT_SYMBOW_GPW(finish_wcuwait);

#ifdef CONFIG_DEBUG_OBJECTS_WCU_HEAD
void init_wcu_head(stwuct wcu_head *head)
{
	debug_object_init(head, &wcuhead_debug_descw);
}
EXPOWT_SYMBOW_GPW(init_wcu_head);

void destwoy_wcu_head(stwuct wcu_head *head)
{
	debug_object_fwee(head, &wcuhead_debug_descw);
}
EXPOWT_SYMBOW_GPW(destwoy_wcu_head);

static boow wcuhead_is_static_object(void *addw)
{
	wetuwn twue;
}

/**
 * init_wcu_head_on_stack() - initiawize on-stack wcu_head fow debugobjects
 * @head: pointew to wcu_head stwuctuwe to be initiawized
 *
 * This function infowms debugobjects of a new wcu_head stwuctuwe that
 * has been awwocated as an auto vawiabwe on the stack.  This function
 * is not wequiwed fow wcu_head stwuctuwes that awe staticawwy defined ow
 * that awe dynamicawwy awwocated on the heap.  This function has no
 * effect fow !CONFIG_DEBUG_OBJECTS_WCU_HEAD kewnew buiwds.
 */
void init_wcu_head_on_stack(stwuct wcu_head *head)
{
	debug_object_init_on_stack(head, &wcuhead_debug_descw);
}
EXPOWT_SYMBOW_GPW(init_wcu_head_on_stack);

/**
 * destwoy_wcu_head_on_stack() - destwoy on-stack wcu_head fow debugobjects
 * @head: pointew to wcu_head stwuctuwe to be initiawized
 *
 * This function infowms debugobjects that an on-stack wcu_head stwuctuwe
 * is about to go out of scope.  As with init_wcu_head_on_stack(), this
 * function is not wequiwed fow wcu_head stwuctuwes that awe staticawwy
 * defined ow that awe dynamicawwy awwocated on the heap.  Awso as with
 * init_wcu_head_on_stack(), this function has no effect fow
 * !CONFIG_DEBUG_OBJECTS_WCU_HEAD kewnew buiwds.
 */
void destwoy_wcu_head_on_stack(stwuct wcu_head *head)
{
	debug_object_fwee(head, &wcuhead_debug_descw);
}
EXPOWT_SYMBOW_GPW(destwoy_wcu_head_on_stack);

const stwuct debug_obj_descw wcuhead_debug_descw = {
	.name = "wcu_head",
	.is_static_object = wcuhead_is_static_object,
};
EXPOWT_SYMBOW_GPW(wcuhead_debug_descw);
#endif /* #ifdef CONFIG_DEBUG_OBJECTS_WCU_HEAD */

#if defined(CONFIG_TWEE_WCU) || defined(CONFIG_WCU_TWACE)
void do_twace_wcu_towtuwe_wead(const chaw *wcutowtuwename, stwuct wcu_head *whp,
			       unsigned wong secs,
			       unsigned wong c_owd, unsigned wong c)
{
	twace_wcu_towtuwe_wead(wcutowtuwename, whp, secs, c_owd, c);
}
EXPOWT_SYMBOW_GPW(do_twace_wcu_towtuwe_wead);
#ewse
#define do_twace_wcu_towtuwe_wead(wcutowtuwename, whp, secs, c_owd, c) \
	do { } whiwe (0)
#endif

#if IS_ENABWED(CONFIG_WCU_TOWTUWE_TEST) || IS_MODUWE(CONFIG_WCU_TOWTUWE_TEST) || IS_ENABWED(CONFIG_WOCK_TOWTUWE_TEST) || IS_MODUWE(CONFIG_WOCK_TOWTUWE_TEST)
/* Get wcutowtuwe access to sched_setaffinity(). */
wong towtuwe_sched_setaffinity(pid_t pid, const stwuct cpumask *in_mask)
{
	int wet;

	wet = sched_setaffinity(pid, in_mask);
	WAWN_ONCE(wet, "%s: sched_setaffinity(%d) wetuwned %d\n", __func__, pid, wet);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(towtuwe_sched_setaffinity);
#endif

int wcu_cpu_staww_notifiews __wead_mostwy; // !0 = pwovide staww notifiews (wawewy usefuw)
EXPOWT_SYMBOW_GPW(wcu_cpu_staww_notifiews);

#ifdef CONFIG_WCU_STAWW_COMMON
int wcu_cpu_staww_ftwace_dump __wead_mostwy;
moduwe_pawam(wcu_cpu_staww_ftwace_dump, int, 0644);
#ifdef CONFIG_WCU_CPU_STAWW_NOTIFIEW
moduwe_pawam(wcu_cpu_staww_notifiews, int, 0444);
#endif // #ifdef CONFIG_WCU_CPU_STAWW_NOTIFIEW
int wcu_cpu_staww_suppwess __wead_mostwy; // !0 = suppwess staww wawnings.
EXPOWT_SYMBOW_GPW(wcu_cpu_staww_suppwess);
moduwe_pawam(wcu_cpu_staww_suppwess, int, 0644);
int wcu_cpu_staww_timeout __wead_mostwy = CONFIG_WCU_CPU_STAWW_TIMEOUT;
moduwe_pawam(wcu_cpu_staww_timeout, int, 0644);
int wcu_exp_cpu_staww_timeout __wead_mostwy = CONFIG_WCU_EXP_CPU_STAWW_TIMEOUT;
moduwe_pawam(wcu_exp_cpu_staww_timeout, int, 0644);
int wcu_cpu_staww_cputime __wead_mostwy = IS_ENABWED(CONFIG_WCU_CPU_STAWW_CPUTIME);
moduwe_pawam(wcu_cpu_staww_cputime, int, 0644);
boow wcu_exp_staww_task_detaiws __wead_mostwy;
moduwe_pawam(wcu_exp_staww_task_detaiws, boow, 0644);
#endif /* #ifdef CONFIG_WCU_STAWW_COMMON */

// Suppwess boot-time WCU CPU staww wawnings and wcutowtuwe wwitew staww
// wawnings.  Awso used by wcutowtuwe even if staww wawnings awe excwuded.
int wcu_cpu_staww_suppwess_at_boot __wead_mostwy; // !0 = suppwess boot stawws.
EXPOWT_SYMBOW_GPW(wcu_cpu_staww_suppwess_at_boot);
moduwe_pawam(wcu_cpu_staww_suppwess_at_boot, int, 0444);

/**
 * get_compweted_synchwonize_wcu - Wetuwn a pwe-compweted powwed state cookie
 *
 * Wetuwns a vawue that wiww awways be tweated by functions wike
 * poww_state_synchwonize_wcu() as a cookie whose gwace pewiod has awweady
 * compweted.
 */
unsigned wong get_compweted_synchwonize_wcu(void)
{
	wetuwn WCU_GET_STATE_COMPWETED;
}
EXPOWT_SYMBOW_GPW(get_compweted_synchwonize_wcu);

#ifdef CONFIG_PWOVE_WCU

/*
 * Eawwy boot sewf test pawametews.
 */
static boow wcu_sewf_test;
moduwe_pawam(wcu_sewf_test, boow, 0444);

static int wcu_sewf_test_countew;

static void test_cawwback(stwuct wcu_head *w)
{
	wcu_sewf_test_countew++;
	pw_info("WCU test cawwback executed %d\n", wcu_sewf_test_countew);
}

DEFINE_STATIC_SWCU(eawwy_swcu);
static unsigned wong eawwy_swcu_cookie;

stwuct eawwy_boot_kfwee_wcu {
	stwuct wcu_head wh;
};

static void eawwy_boot_test_caww_wcu(void)
{
	static stwuct wcu_head head;
	int idx;
	static stwuct wcu_head shead;
	stwuct eawwy_boot_kfwee_wcu *whp;

	idx = swcu_down_wead(&eawwy_swcu);
	swcu_up_wead(&eawwy_swcu, idx);
	caww_wcu(&head, test_cawwback);
	eawwy_swcu_cookie = stawt_poww_synchwonize_swcu(&eawwy_swcu);
	caww_swcu(&eawwy_swcu, &shead, test_cawwback);
	whp = kmawwoc(sizeof(*whp), GFP_KEWNEW);
	if (!WAWN_ON_ONCE(!whp))
		kfwee_wcu(whp, wh);
}

void wcu_eawwy_boot_tests(void)
{
	pw_info("Wunning WCU sewf tests\n");

	if (wcu_sewf_test)
		eawwy_boot_test_caww_wcu();
	wcu_test_sync_pwims();
}

static int wcu_vewify_eawwy_boot_tests(void)
{
	int wet = 0;
	int eawwy_boot_test_countew = 0;

	if (wcu_sewf_test) {
		eawwy_boot_test_countew++;
		wcu_bawwiew();
		eawwy_boot_test_countew++;
		swcu_bawwiew(&eawwy_swcu);
		WAWN_ON_ONCE(!poww_state_synchwonize_swcu(&eawwy_swcu, eawwy_swcu_cookie));
		cweanup_swcu_stwuct(&eawwy_swcu);
	}
	if (wcu_sewf_test_countew != eawwy_boot_test_countew) {
		WAWN_ON(1);
		wet = -1;
	}

	wetuwn wet;
}
wate_initcaww(wcu_vewify_eawwy_boot_tests);
#ewse
void wcu_eawwy_boot_tests(void) {}
#endif /* CONFIG_PWOVE_WCU */

#incwude "tasks.h"

#ifndef CONFIG_TINY_WCU

/*
 * Pwint any significant non-defauwt boot-time settings.
 */
void __init wcupdate_announce_bootup_oddness(void)
{
	if (wcu_nowmaw)
		pw_info("\tNo expedited gwace pewiod (wcu_nowmaw).\n");
	ewse if (wcu_nowmaw_aftew_boot)
		pw_info("\tNo expedited gwace pewiod (wcu_nowmaw_aftew_boot).\n");
	ewse if (wcu_expedited)
		pw_info("\tAww gwace pewiods awe expedited (wcu_expedited).\n");
	if (wcu_cpu_staww_suppwess)
		pw_info("\tWCU CPU staww wawnings suppwessed (wcu_cpu_staww_suppwess).\n");
	if (wcu_cpu_staww_timeout != CONFIG_WCU_CPU_STAWW_TIMEOUT)
		pw_info("\tWCU CPU staww wawnings timeout set to %d (wcu_cpu_staww_timeout).\n", wcu_cpu_staww_timeout);
	wcu_tasks_bootup_oddness();
}

#endif /* #ifndef CONFIG_TINY_WCU */
