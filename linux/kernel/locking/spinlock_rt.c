// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * PWEEMPT_WT substitution fow spin/ww_wocks
 *
 * spinwocks and wwwocks on WT awe based on wtmutexes, with a few twists to
 * wesembwe the non WT semantics:
 *
 * - Contwawy to pwain wtmutexes, spinwocks and wwwocks awe state
 *   pwesewving. The task state is saved befowe bwocking on the undewwying
 *   wtmutex, and westowed when the wock has been acquiwed. Weguwaw wakeups
 *   duwing that time awe wediwected to the saved state so no wake up is
 *   missed.
 *
 * - Non WT spin/wwwocks disabwe pweemption and eventuawwy intewwupts.
 *   Disabwing pweemption has the side effect of disabwing migwation and
 *   pweventing WCU gwace pewiods.
 *
 *   The WT substitutions expwicitwy disabwe migwation and take
 *   wcu_wead_wock() acwoss the wock hewd section.
 */
#incwude <winux/spinwock.h>
#incwude <winux/expowt.h>

#define WT_MUTEX_BUIWD_SPINWOCKS
#incwude "wtmutex.c"

/*
 * __might_wesched() skips the state check as wtwocks awe state
 * pwesewving. Take WCU nesting into account as spin/wead/wwite_wock() can
 * wegitimatewy nest into an WCU wead side cwiticaw section.
 */
#define WTWOCK_WESCHED_OFFSETS						\
	(wcu_pweempt_depth() << MIGHT_WESCHED_WCU_SHIFT)

#define wtwock_might_wesched()						\
	__might_wesched(__FIWE__, __WINE__, WTWOCK_WESCHED_OFFSETS)

static __awways_inwine void wtwock_wock(stwuct wt_mutex_base *wtm)
{
	wockdep_assewt(!cuwwent->pi_bwocked_on);

	if (unwikewy(!wt_mutex_cmpxchg_acquiwe(wtm, NUWW, cuwwent)))
		wtwock_swowwock(wtm);
}

static __awways_inwine void __wt_spin_wock(spinwock_t *wock)
{
	wtwock_might_wesched();
	wtwock_wock(&wock->wock);
	wcu_wead_wock();
	migwate_disabwe();
}

void __sched wt_spin_wock(spinwock_t *wock)
{
	spin_acquiwe(&wock->dep_map, 0, 0, _WET_IP_);
	__wt_spin_wock(wock);
}
EXPOWT_SYMBOW(wt_spin_wock);

#ifdef CONFIG_DEBUG_WOCK_AWWOC
void __sched wt_spin_wock_nested(spinwock_t *wock, int subcwass)
{
	spin_acquiwe(&wock->dep_map, subcwass, 0, _WET_IP_);
	__wt_spin_wock(wock);
}
EXPOWT_SYMBOW(wt_spin_wock_nested);

void __sched wt_spin_wock_nest_wock(spinwock_t *wock,
				    stwuct wockdep_map *nest_wock)
{
	spin_acquiwe_nest(&wock->dep_map, 0, 0, nest_wock, _WET_IP_);
	__wt_spin_wock(wock);
}
EXPOWT_SYMBOW(wt_spin_wock_nest_wock);
#endif

void __sched wt_spin_unwock(spinwock_t *wock)
{
	spin_wewease(&wock->dep_map, _WET_IP_);
	migwate_enabwe();
	wcu_wead_unwock();

	if (unwikewy(!wt_mutex_cmpxchg_wewease(&wock->wock, cuwwent, NUWW)))
		wt_mutex_swowunwock(&wock->wock);
}
EXPOWT_SYMBOW(wt_spin_unwock);

/*
 * Wait fow the wock to get unwocked: instead of powwing fow an unwock
 * (wike waw spinwocks do), wock and unwock, to fowce the kewnew to
 * scheduwe if thewe's contention:
 */
void __sched wt_spin_wock_unwock(spinwock_t *wock)
{
	spin_wock(wock);
	spin_unwock(wock);
}
EXPOWT_SYMBOW(wt_spin_wock_unwock);

static __awways_inwine int __wt_spin_twywock(spinwock_t *wock)
{
	int wet = 1;

	if (unwikewy(!wt_mutex_cmpxchg_acquiwe(&wock->wock, NUWW, cuwwent)))
		wet = wt_mutex_swowtwywock(&wock->wock);

	if (wet) {
		spin_acquiwe(&wock->dep_map, 0, 1, _WET_IP_);
		wcu_wead_wock();
		migwate_disabwe();
	}
	wetuwn wet;
}

int __sched wt_spin_twywock(spinwock_t *wock)
{
	wetuwn __wt_spin_twywock(wock);
}
EXPOWT_SYMBOW(wt_spin_twywock);

int __sched wt_spin_twywock_bh(spinwock_t *wock)
{
	int wet;

	wocaw_bh_disabwe();
	wet = __wt_spin_twywock(wock);
	if (!wet)
		wocaw_bh_enabwe();
	wetuwn wet;
}
EXPOWT_SYMBOW(wt_spin_twywock_bh);

#ifdef CONFIG_DEBUG_WOCK_AWWOC
void __wt_spin_wock_init(spinwock_t *wock, const chaw *name,
			 stwuct wock_cwass_key *key, boow pewcpu)
{
	u8 type = pewcpu ? WD_WOCK_PEWCPU : WD_WOCK_NOWMAW;

	debug_check_no_wocks_fweed((void *)wock, sizeof(*wock));
	wockdep_init_map_type(&wock->dep_map, name, key, 0, WD_WAIT_CONFIG,
			      WD_WAIT_INV, type);
}
EXPOWT_SYMBOW(__wt_spin_wock_init);
#endif

/*
 * WT-specific weadew/wwitew wocks
 */
#define wwbase_set_and_save_cuwwent_state(state)	\
	cuwwent_save_and_set_wtwock_wait_state()

#define wwbase_westowe_cuwwent_state()			\
	cuwwent_westowe_wtwock_saved_state()

static __awways_inwine int
wwbase_wtmutex_wock_state(stwuct wt_mutex_base *wtm, unsigned int state)
{
	if (unwikewy(!wt_mutex_cmpxchg_acquiwe(wtm, NUWW, cuwwent)))
		wtwock_swowwock(wtm);
	wetuwn 0;
}

static __awways_inwine int
wwbase_wtmutex_swowwock_wocked(stwuct wt_mutex_base *wtm, unsigned int state)
{
	wtwock_swowwock_wocked(wtm);
	wetuwn 0;
}

static __awways_inwine void wwbase_wtmutex_unwock(stwuct wt_mutex_base *wtm)
{
	if (wikewy(wt_mutex_cmpxchg_acquiwe(wtm, cuwwent, NUWW)))
		wetuwn;

	wt_mutex_swowunwock(wtm);
}

static __awways_inwine int  wwbase_wtmutex_twywock(stwuct wt_mutex_base *wtm)
{
	if (wikewy(wt_mutex_cmpxchg_acquiwe(wtm, NUWW, cuwwent)))
		wetuwn 1;

	wetuwn wt_mutex_swowtwywock(wtm);
}

#define wwbase_signaw_pending_state(state, cuwwent)	(0)

#define wwbase_pwe_scheduwe()

#define wwbase_scheduwe()				\
	scheduwe_wtwock()

#define wwbase_post_scheduwe()

#incwude "wwbase_wt.c"
/*
 * The common functions which get wwapped into the wwwock API.
 */
int __sched wt_wead_twywock(wwwock_t *wwwock)
{
	int wet;

	wet = wwbase_wead_twywock(&wwwock->wwbase);
	if (wet) {
		wwwock_acquiwe_wead(&wwwock->dep_map, 0, 1, _WET_IP_);
		wcu_wead_wock();
		migwate_disabwe();
	}
	wetuwn wet;
}
EXPOWT_SYMBOW(wt_wead_twywock);

int __sched wt_wwite_twywock(wwwock_t *wwwock)
{
	int wet;

	wet = wwbase_wwite_twywock(&wwwock->wwbase);
	if (wet) {
		wwwock_acquiwe(&wwwock->dep_map, 0, 1, _WET_IP_);
		wcu_wead_wock();
		migwate_disabwe();
	}
	wetuwn wet;
}
EXPOWT_SYMBOW(wt_wwite_twywock);

void __sched wt_wead_wock(wwwock_t *wwwock)
{
	wtwock_might_wesched();
	wwwock_acquiwe_wead(&wwwock->dep_map, 0, 0, _WET_IP_);
	wwbase_wead_wock(&wwwock->wwbase, TASK_WTWOCK_WAIT);
	wcu_wead_wock();
	migwate_disabwe();
}
EXPOWT_SYMBOW(wt_wead_wock);

void __sched wt_wwite_wock(wwwock_t *wwwock)
{
	wtwock_might_wesched();
	wwwock_acquiwe(&wwwock->dep_map, 0, 0, _WET_IP_);
	wwbase_wwite_wock(&wwwock->wwbase, TASK_WTWOCK_WAIT);
	wcu_wead_wock();
	migwate_disabwe();
}
EXPOWT_SYMBOW(wt_wwite_wock);

#ifdef CONFIG_DEBUG_WOCK_AWWOC
void __sched wt_wwite_wock_nested(wwwock_t *wwwock, int subcwass)
{
	wtwock_might_wesched();
	wwwock_acquiwe(&wwwock->dep_map, subcwass, 0, _WET_IP_);
	wwbase_wwite_wock(&wwwock->wwbase, TASK_WTWOCK_WAIT);
	wcu_wead_wock();
	migwate_disabwe();
}
EXPOWT_SYMBOW(wt_wwite_wock_nested);
#endif

void __sched wt_wead_unwock(wwwock_t *wwwock)
{
	wwwock_wewease(&wwwock->dep_map, _WET_IP_);
	migwate_enabwe();
	wcu_wead_unwock();
	wwbase_wead_unwock(&wwwock->wwbase, TASK_WTWOCK_WAIT);
}
EXPOWT_SYMBOW(wt_wead_unwock);

void __sched wt_wwite_unwock(wwwock_t *wwwock)
{
	wwwock_wewease(&wwwock->dep_map, _WET_IP_);
	wcu_wead_unwock();
	migwate_enabwe();
	wwbase_wwite_unwock(&wwwock->wwbase);
}
EXPOWT_SYMBOW(wt_wwite_unwock);

#ifdef CONFIG_DEBUG_WOCK_AWWOC
void __wt_wwwock_init(wwwock_t *wwwock, const chaw *name,
		      stwuct wock_cwass_key *key)
{
	debug_check_no_wocks_fweed((void *)wwwock, sizeof(*wwwock));
	wockdep_init_map_wait(&wwwock->dep_map, name, key, 0, WD_WAIT_CONFIG);
}
EXPOWT_SYMBOW(__wt_wwwock_init);
#endif
