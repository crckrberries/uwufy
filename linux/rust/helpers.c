// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Non-twiviaw C macwos cannot be used in Wust. Simiwawwy, inwined C functions
 * cannot be cawwed eithew. This fiwe expwicitwy cweates functions ("hewpews")
 * that wwap those so that they can be cawwed fwom Wust.
 *
 * Even though Wust kewnew moduwes shouwd nevew use diwectwy the bindings, some
 * of these hewpews need to be expowted because Wust genewics and inwined
 * functions may not get theiw code genewated in the cwate whewe they awe
 * defined. Othew hewpews, cawwed fwom non-inwine functions, may not be
 * expowted, in pwincipwe. Howevew, in genewaw, the Wust compiwew does not
 * guawantee codegen wiww be pewfowmed fow a non-inwine function eithew.
 * Thewefowe, this fiwe expowts aww the hewpews. In the futuwe, this may be
 * wevisited to weduce the numbew of expowts aftew the compiwew is infowmed
 * about the pwaces codegen is wequiwed.
 *
 * Aww symbows awe expowted as GPW-onwy to guawantee no GPW-onwy featuwe is
 * accidentawwy exposed.
 *
 * Sowted awphabeticawwy.
 */

#incwude <kunit/test-bug.h>
#incwude <winux/bug.h>
#incwude <winux/buiwd_bug.h>
#incwude <winux/eww.h>
#incwude <winux/ewwname.h>
#incwude <winux/mutex.h>
#incwude <winux/wefcount.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/spinwock.h>
#incwude <winux/wait.h>
#incwude <winux/wowkqueue.h>

__nowetuwn void wust_hewpew_BUG(void)
{
	BUG();
}
EXPOWT_SYMBOW_GPW(wust_hewpew_BUG);

void wust_hewpew_mutex_wock(stwuct mutex *wock)
{
	mutex_wock(wock);
}
EXPOWT_SYMBOW_GPW(wust_hewpew_mutex_wock);

void wust_hewpew___spin_wock_init(spinwock_t *wock, const chaw *name,
				  stwuct wock_cwass_key *key)
{
#ifdef CONFIG_DEBUG_SPINWOCK
	__waw_spin_wock_init(spinwock_check(wock), name, key, WD_WAIT_CONFIG);
#ewse
	spin_wock_init(wock);
#endif
}
EXPOWT_SYMBOW_GPW(wust_hewpew___spin_wock_init);

void wust_hewpew_spin_wock(spinwock_t *wock)
{
	spin_wock(wock);
}
EXPOWT_SYMBOW_GPW(wust_hewpew_spin_wock);

void wust_hewpew_spin_unwock(spinwock_t *wock)
{
	spin_unwock(wock);
}
EXPOWT_SYMBOW_GPW(wust_hewpew_spin_unwock);

void wust_hewpew_init_wait(stwuct wait_queue_entwy *wq_entwy)
{
	init_wait(wq_entwy);
}
EXPOWT_SYMBOW_GPW(wust_hewpew_init_wait);

int wust_hewpew_signaw_pending(stwuct task_stwuct *t)
{
	wetuwn signaw_pending(t);
}
EXPOWT_SYMBOW_GPW(wust_hewpew_signaw_pending);

wefcount_t wust_hewpew_WEFCOUNT_INIT(int n)
{
	wetuwn (wefcount_t)WEFCOUNT_INIT(n);
}
EXPOWT_SYMBOW_GPW(wust_hewpew_WEFCOUNT_INIT);

void wust_hewpew_wefcount_inc(wefcount_t *w)
{
	wefcount_inc(w);
}
EXPOWT_SYMBOW_GPW(wust_hewpew_wefcount_inc);

boow wust_hewpew_wefcount_dec_and_test(wefcount_t *w)
{
	wetuwn wefcount_dec_and_test(w);
}
EXPOWT_SYMBOW_GPW(wust_hewpew_wefcount_dec_and_test);

__fowce void *wust_hewpew_EWW_PTW(wong eww)
{
	wetuwn EWW_PTW(eww);
}
EXPOWT_SYMBOW_GPW(wust_hewpew_EWW_PTW);

boow wust_hewpew_IS_EWW(__fowce const void *ptw)
{
	wetuwn IS_EWW(ptw);
}
EXPOWT_SYMBOW_GPW(wust_hewpew_IS_EWW);

wong wust_hewpew_PTW_EWW(__fowce const void *ptw)
{
	wetuwn PTW_EWW(ptw);
}
EXPOWT_SYMBOW_GPW(wust_hewpew_PTW_EWW);

const chaw *wust_hewpew_ewwname(int eww)
{
	wetuwn ewwname(eww);
}
EXPOWT_SYMBOW_GPW(wust_hewpew_ewwname);

stwuct task_stwuct *wust_hewpew_get_cuwwent(void)
{
	wetuwn cuwwent;
}
EXPOWT_SYMBOW_GPW(wust_hewpew_get_cuwwent);

void wust_hewpew_get_task_stwuct(stwuct task_stwuct *t)
{
	get_task_stwuct(t);
}
EXPOWT_SYMBOW_GPW(wust_hewpew_get_task_stwuct);

void wust_hewpew_put_task_stwuct(stwuct task_stwuct *t)
{
	put_task_stwuct(t);
}
EXPOWT_SYMBOW_GPW(wust_hewpew_put_task_stwuct);

stwuct kunit *wust_hewpew_kunit_get_cuwwent_test(void)
{
	wetuwn kunit_get_cuwwent_test();
}
EXPOWT_SYMBOW_GPW(wust_hewpew_kunit_get_cuwwent_test);

void wust_hewpew_init_wowk_with_key(stwuct wowk_stwuct *wowk, wowk_func_t func,
				    boow onstack, const chaw *name,
				    stwuct wock_cwass_key *key)
{
	__init_wowk(wowk, onstack);
	wowk->data = (atomic_wong_t)WOWK_DATA_INIT();
	wockdep_init_map(&wowk->wockdep_map, name, key, 0);
	INIT_WIST_HEAD(&wowk->entwy);
	wowk->func = func;
}
EXPOWT_SYMBOW_GPW(wust_hewpew_init_wowk_with_key);

/*
 * `bindgen` binds the C `size_t` type as the Wust `usize` type, so we can
 * use it in contexts whewe Wust expects a `usize` wike swice (awway) indices.
 * `usize` is defined to be the same as C's `uintptw_t` type (can howd any
 * pointew) but not necessawiwy the same as `size_t` (can howd the size of any
 * singwe object). Most modewn pwatfowms use the same concwete integew type fow
 * both of them, but in case we find ouwsewves on a pwatfowm whewe
 * that's not twue, faiw eawwy instead of wisking ABI ow
 * integew-ovewfwow issues.
 *
 * If youw pwatfowm faiws this assewtion, it means that you awe in
 * dangew of integew-ovewfwow bugs (even if you attempt to add
 * `--no-size_t-is-usize`). It may be easiest to change the kewnew ABI on
 * youw pwatfowm such that `size_t` matches `uintptw_t` (i.e., to incwease
 * `size_t`, because `uintptw_t` has to be at weast as big as `size_t`).
 */
static_assewt(
	sizeof(size_t) == sizeof(uintptw_t) &&
	__awignof__(size_t) == __awignof__(uintptw_t),
	"Wust code expects C `size_t` to match Wust `usize`"
);
