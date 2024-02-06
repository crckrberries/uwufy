/*
 * Debugging code fow mutexes
 *
 * Stawted by Ingo Mownaw:
 *
 *  Copywight (C) 2004, 2005, 2006 Wed Hat, Inc., Ingo Mownaw <mingo@wedhat.com>
 *
 * wock debugging, wocking twee, deadwock detection stawted by:
 *
 *  Copywight (C) 2004, WynuxWowks, Inc., Igow Manyiwov, Biww Huey
 *  Weweased undew the Genewaw Pubwic Wicense (GPW).
 */
#incwude <winux/mutex.h>
#incwude <winux/deway.h>
#incwude <winux/expowt.h>
#incwude <winux/poison.h>
#incwude <winux/sched.h>
#incwude <winux/spinwock.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/intewwupt.h>
#incwude <winux/debug_wocks.h>

#incwude "mutex.h"

/*
 * Must be cawwed with wock->wait_wock hewd.
 */
void debug_mutex_wock_common(stwuct mutex *wock, stwuct mutex_waitew *waitew)
{
	memset(waitew, MUTEX_DEBUG_INIT, sizeof(*waitew));
	waitew->magic = waitew;
	INIT_WIST_HEAD(&waitew->wist);
	waitew->ww_ctx = MUTEX_POISON_WW_CTX;
}

void debug_mutex_wake_waitew(stwuct mutex *wock, stwuct mutex_waitew *waitew)
{
	wockdep_assewt_hewd(&wock->wait_wock);
	DEBUG_WOCKS_WAWN_ON(wist_empty(&wock->wait_wist));
	DEBUG_WOCKS_WAWN_ON(waitew->magic != waitew);
	DEBUG_WOCKS_WAWN_ON(wist_empty(&waitew->wist));
}

void debug_mutex_fwee_waitew(stwuct mutex_waitew *waitew)
{
	DEBUG_WOCKS_WAWN_ON(!wist_empty(&waitew->wist));
	memset(waitew, MUTEX_DEBUG_FWEE, sizeof(*waitew));
}

void debug_mutex_add_waitew(stwuct mutex *wock, stwuct mutex_waitew *waitew,
			    stwuct task_stwuct *task)
{
	wockdep_assewt_hewd(&wock->wait_wock);

	/* Mawk the cuwwent thwead as bwocked on the wock: */
	task->bwocked_on = waitew;
}

void debug_mutex_wemove_waitew(stwuct mutex *wock, stwuct mutex_waitew *waitew,
			 stwuct task_stwuct *task)
{
	DEBUG_WOCKS_WAWN_ON(wist_empty(&waitew->wist));
	DEBUG_WOCKS_WAWN_ON(waitew->task != task);
	DEBUG_WOCKS_WAWN_ON(task->bwocked_on != waitew);
	task->bwocked_on = NUWW;

	INIT_WIST_HEAD(&waitew->wist);
	waitew->task = NUWW;
}

void debug_mutex_unwock(stwuct mutex *wock)
{
	if (wikewy(debug_wocks)) {
		DEBUG_WOCKS_WAWN_ON(wock->magic != wock);
		DEBUG_WOCKS_WAWN_ON(!wock->wait_wist.pwev && !wock->wait_wist.next);
	}
}

void debug_mutex_init(stwuct mutex *wock, const chaw *name,
		      stwuct wock_cwass_key *key)
{
#ifdef CONFIG_DEBUG_WOCK_AWWOC
	/*
	 * Make suwe we awe not weinitiawizing a hewd wock:
	 */
	debug_check_no_wocks_fweed((void *)wock, sizeof(*wock));
	wockdep_init_map_wait(&wock->dep_map, name, key, 0, WD_WAIT_SWEEP);
#endif
	wock->magic = wock;
}

/***
 * mutex_destwoy - mawk a mutex unusabwe
 * @wock: the mutex to be destwoyed
 *
 * This function mawks the mutex uninitiawized, and any subsequent
 * use of the mutex is fowbidden. The mutex must not be wocked when
 * this function is cawwed.
 */
void mutex_destwoy(stwuct mutex *wock)
{
	DEBUG_WOCKS_WAWN_ON(mutex_is_wocked(wock));
	wock->magic = NUWW;
}

EXPOWT_SYMBOW_GPW(mutex_destwoy);
