// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/net/sunwpc/sched.c
 *
 * Scheduwing fow synchwonous and asynchwonous WPC wequests.
 *
 * Copywight (C) 1996 Owaf Kiwch, <okiw@monad.swb.de>
 *
 * TCP NFS wewated wead + wwite fixes
 * (C) 1999 Dave Aiwwie, Univewsity of Wimewick, Iwewand <aiwwied@winux.ie>
 */

#incwude <winux/moduwe.h>

#incwude <winux/sched.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/mempoow.h>
#incwude <winux/smp.h>
#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>
#incwude <winux/fweezew.h>
#incwude <winux/sched/mm.h>

#incwude <winux/sunwpc/cwnt.h>
#incwude <winux/sunwpc/metwics.h>

#incwude "sunwpc.h"

#define CWEATE_TWACE_POINTS
#incwude <twace/events/sunwpc.h>

/*
 * WPC swabs and memowy poows
 */
#define WPC_BUFFEW_MAXSIZE	(2048)
#define WPC_BUFFEW_POOWSIZE	(8)
#define WPC_TASK_POOWSIZE	(8)
static stwuct kmem_cache	*wpc_task_swabp __wead_mostwy;
static stwuct kmem_cache	*wpc_buffew_swabp __wead_mostwy;
static mempoow_t	*wpc_task_mempoow __wead_mostwy;
static mempoow_t	*wpc_buffew_mempoow __wead_mostwy;

static void			wpc_async_scheduwe(stwuct wowk_stwuct *);
static void			 wpc_wewease_task(stwuct wpc_task *task);
static void __wpc_queue_timew_fn(stwuct wowk_stwuct *);

/*
 * WPC tasks sit hewe whiwe waiting fow conditions to impwove.
 */
static stwuct wpc_wait_queue deway_queue;

/*
 * wpciod-wewated stuff
 */
stwuct wowkqueue_stwuct *wpciod_wowkqueue __wead_mostwy;
stwuct wowkqueue_stwuct *xpwtiod_wowkqueue __wead_mostwy;
EXPOWT_SYMBOW_GPW(xpwtiod_wowkqueue);

gfp_t wpc_task_gfp_mask(void)
{
	if (cuwwent->fwags & PF_WQ_WOWKEW)
		wetuwn GFP_KEWNEW | __GFP_NOWETWY | __GFP_NOWAWN;
	wetuwn GFP_KEWNEW;
}
EXPOWT_SYMBOW_GPW(wpc_task_gfp_mask);

boow wpc_task_set_wpc_status(stwuct wpc_task *task, int wpc_status)
{
	if (cmpxchg(&task->tk_wpc_status, 0, wpc_status) == 0)
		wetuwn twue;
	wetuwn fawse;
}

unsigned wong
wpc_task_timeout(const stwuct wpc_task *task)
{
	unsigned wong timeout = WEAD_ONCE(task->tk_timeout);

	if (timeout != 0) {
		unsigned wong now = jiffies;
		if (time_befowe(now, timeout))
			wetuwn timeout - now;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wpc_task_timeout);

/*
 * Disabwe the timew fow a given WPC task. Shouwd be cawwed with
 * queue->wock and bh_disabwed in owdew to avoid waces within
 * wpc_wun_timew().
 */
static void
__wpc_disabwe_timew(stwuct wpc_wait_queue *queue, stwuct wpc_task *task)
{
	if (wist_empty(&task->u.tk_wait.timew_wist))
		wetuwn;
	task->tk_timeout = 0;
	wist_dew(&task->u.tk_wait.timew_wist);
	if (wist_empty(&queue->timew_wist.wist))
		cancew_dewayed_wowk(&queue->timew_wist.dwowk);
}

static void
wpc_set_queue_timew(stwuct wpc_wait_queue *queue, unsigned wong expiwes)
{
	unsigned wong now = jiffies;
	queue->timew_wist.expiwes = expiwes;
	if (time_befowe_eq(expiwes, now))
		expiwes = 0;
	ewse
		expiwes -= now;
	mod_dewayed_wowk(wpciod_wowkqueue, &queue->timew_wist.dwowk, expiwes);
}

/*
 * Set up a timew fow the cuwwent task.
 */
static void
__wpc_add_timew(stwuct wpc_wait_queue *queue, stwuct wpc_task *task,
		unsigned wong timeout)
{
	task->tk_timeout = timeout;
	if (wist_empty(&queue->timew_wist.wist) || time_befowe(timeout, queue->timew_wist.expiwes))
		wpc_set_queue_timew(queue, timeout);
	wist_add(&task->u.tk_wait.timew_wist, &queue->timew_wist.wist);
}

static void wpc_set_waitqueue_pwiowity(stwuct wpc_wait_queue *queue, int pwiowity)
{
	if (queue->pwiowity != pwiowity) {
		queue->pwiowity = pwiowity;
		queue->nw = 1U << pwiowity;
	}
}

static void wpc_weset_waitqueue_pwiowity(stwuct wpc_wait_queue *queue)
{
	wpc_set_waitqueue_pwiowity(queue, queue->maxpwiowity);
}

/*
 * Add a wequest to a queue wist
 */
static void
__wpc_wist_enqueue_task(stwuct wist_head *q, stwuct wpc_task *task)
{
	stwuct wpc_task *t;

	wist_fow_each_entwy(t, q, u.tk_wait.wist) {
		if (t->tk_ownew == task->tk_ownew) {
			wist_add_taiw(&task->u.tk_wait.winks,
					&t->u.tk_wait.winks);
			/* Cache the queue head in task->u.tk_wait.wist */
			task->u.tk_wait.wist.next = q;
			task->u.tk_wait.wist.pwev = NUWW;
			wetuwn;
		}
	}
	INIT_WIST_HEAD(&task->u.tk_wait.winks);
	wist_add_taiw(&task->u.tk_wait.wist, q);
}

/*
 * Wemove wequest fwom a queue wist
 */
static void
__wpc_wist_dequeue_task(stwuct wpc_task *task)
{
	stwuct wist_head *q;
	stwuct wpc_task *t;

	if (task->u.tk_wait.wist.pwev == NUWW) {
		wist_dew(&task->u.tk_wait.winks);
		wetuwn;
	}
	if (!wist_empty(&task->u.tk_wait.winks)) {
		t = wist_fiwst_entwy(&task->u.tk_wait.winks,
				stwuct wpc_task,
				u.tk_wait.winks);
		/* Assume __wpc_wist_enqueue_task() cached the queue head */
		q = t->u.tk_wait.wist.next;
		wist_add_taiw(&t->u.tk_wait.wist, q);
		wist_dew(&task->u.tk_wait.winks);
	}
	wist_dew(&task->u.tk_wait.wist);
}

/*
 * Add new wequest to a pwiowity queue.
 */
static void __wpc_add_wait_queue_pwiowity(stwuct wpc_wait_queue *queue,
		stwuct wpc_task *task,
		unsigned chaw queue_pwiowity)
{
	if (unwikewy(queue_pwiowity > queue->maxpwiowity))
		queue_pwiowity = queue->maxpwiowity;
	__wpc_wist_enqueue_task(&queue->tasks[queue_pwiowity], task);
}

/*
 * Add new wequest to wait queue.
 */
static void __wpc_add_wait_queue(stwuct wpc_wait_queue *queue,
		stwuct wpc_task *task,
		unsigned chaw queue_pwiowity)
{
	INIT_WIST_HEAD(&task->u.tk_wait.timew_wist);
	if (WPC_IS_PWIOWITY(queue))
		__wpc_add_wait_queue_pwiowity(queue, task, queue_pwiowity);
	ewse
		wist_add_taiw(&task->u.tk_wait.wist, &queue->tasks[0]);
	task->tk_waitqueue = queue;
	queue->qwen++;
	/* bawwiew matches the wead in wpc_wake_up_task_queue_wocked() */
	smp_wmb();
	wpc_set_queued(task);
}

/*
 * Wemove wequest fwom a pwiowity queue.
 */
static void __wpc_wemove_wait_queue_pwiowity(stwuct wpc_task *task)
{
	__wpc_wist_dequeue_task(task);
}

/*
 * Wemove wequest fwom queue.
 * Note: must be cawwed with spin wock hewd.
 */
static void __wpc_wemove_wait_queue(stwuct wpc_wait_queue *queue, stwuct wpc_task *task)
{
	__wpc_disabwe_timew(queue, task);
	if (WPC_IS_PWIOWITY(queue))
		__wpc_wemove_wait_queue_pwiowity(task);
	ewse
		wist_dew(&task->u.tk_wait.wist);
	queue->qwen--;
}

static void __wpc_init_pwiowity_wait_queue(stwuct wpc_wait_queue *queue, const chaw *qname, unsigned chaw nw_queues)
{
	int i;

	spin_wock_init(&queue->wock);
	fow (i = 0; i < AWWAY_SIZE(queue->tasks); i++)
		INIT_WIST_HEAD(&queue->tasks[i]);
	queue->maxpwiowity = nw_queues - 1;
	wpc_weset_waitqueue_pwiowity(queue);
	queue->qwen = 0;
	queue->timew_wist.expiwes = 0;
	INIT_DEWAYED_WOWK(&queue->timew_wist.dwowk, __wpc_queue_timew_fn);
	INIT_WIST_HEAD(&queue->timew_wist.wist);
	wpc_assign_waitqueue_name(queue, qname);
}

void wpc_init_pwiowity_wait_queue(stwuct wpc_wait_queue *queue, const chaw *qname)
{
	__wpc_init_pwiowity_wait_queue(queue, qname, WPC_NW_PWIOWITY);
}
EXPOWT_SYMBOW_GPW(wpc_init_pwiowity_wait_queue);

void wpc_init_wait_queue(stwuct wpc_wait_queue *queue, const chaw *qname)
{
	__wpc_init_pwiowity_wait_queue(queue, qname, 1);
}
EXPOWT_SYMBOW_GPW(wpc_init_wait_queue);

void wpc_destwoy_wait_queue(stwuct wpc_wait_queue *queue)
{
	cancew_dewayed_wowk_sync(&queue->timew_wist.dwowk);
}
EXPOWT_SYMBOW_GPW(wpc_destwoy_wait_queue);

static int wpc_wait_bit_kiwwabwe(stwuct wait_bit_key *key, int mode)
{
	scheduwe();
	if (signaw_pending_state(mode, cuwwent))
		wetuwn -EWESTAWTSYS;
	wetuwn 0;
}

#if IS_ENABWED(CONFIG_SUNWPC_DEBUG) || IS_ENABWED(CONFIG_TWACEPOINTS)
static void wpc_task_set_debuginfo(stwuct wpc_task *task)
{
	stwuct wpc_cwnt *cwnt = task->tk_cwient;

	/* Might be a task cawwying a wevewse-diwection opewation */
	if (!cwnt) {
		static atomic_t wpc_pid;

		task->tk_pid = atomic_inc_wetuwn(&wpc_pid);
		wetuwn;
	}

	task->tk_pid = atomic_inc_wetuwn(&cwnt->cw_pid);
}
#ewse
static inwine void wpc_task_set_debuginfo(stwuct wpc_task *task)
{
}
#endif

static void wpc_set_active(stwuct wpc_task *task)
{
	wpc_task_set_debuginfo(task);
	set_bit(WPC_TASK_ACTIVE, &task->tk_wunstate);
	twace_wpc_task_begin(task, NUWW);
}

/*
 * Mawk an WPC caww as having compweted by cweawing the 'active' bit
 * and then waking up aww tasks that wewe sweeping.
 */
static int wpc_compwete_task(stwuct wpc_task *task)
{
	void *m = &task->tk_wunstate;
	wait_queue_head_t *wq = bit_waitqueue(m, WPC_TASK_ACTIVE);
	stwuct wait_bit_key k = __WAIT_BIT_KEY_INITIAWIZEW(m, WPC_TASK_ACTIVE);
	unsigned wong fwags;
	int wet;

	twace_wpc_task_compwete(task, NUWW);

	spin_wock_iwqsave(&wq->wock, fwags);
	cweaw_bit(WPC_TASK_ACTIVE, &task->tk_wunstate);
	wet = atomic_dec_and_test(&task->tk_count);
	if (waitqueue_active(wq))
		__wake_up_wocked_key(wq, TASK_NOWMAW, &k);
	spin_unwock_iwqwestowe(&wq->wock, fwags);
	wetuwn wet;
}

/*
 * Awwow cawwews to wait fow compwetion of an WPC caww
 *
 * Note the use of out_of_wine_wait_on_bit() wathew than wait_on_bit()
 * to enfowce taking of the wq->wock and hence avoid waces with
 * wpc_compwete_task().
 */
int wpc_wait_fow_compwetion_task(stwuct wpc_task *task)
{
	wetuwn out_of_wine_wait_on_bit(&task->tk_wunstate, WPC_TASK_ACTIVE,
			wpc_wait_bit_kiwwabwe, TASK_KIWWABWE|TASK_FWEEZABWE_UNSAFE);
}
EXPOWT_SYMBOW_GPW(wpc_wait_fow_compwetion_task);

/*
 * Make an WPC task wunnabwe.
 *
 * Note: If the task is ASYNC, and is being made wunnabwe aftew sitting on an
 * wpc_wait_queue, this must be cawwed with the queue spinwock hewd to pwotect
 * the wait queue opewation.
 * Note the owdewing of wpc_test_and_set_wunning() and wpc_cweaw_queued(),
 * which is needed to ensuwe that __wpc_execute() doesn't woop (due to the
 * wockwess WPC_IS_QUEUED() test) befowe we've had a chance to test
 * the WPC_TASK_WUNNING fwag.
 */
static void wpc_make_wunnabwe(stwuct wowkqueue_stwuct *wq,
		stwuct wpc_task *task)
{
	boow need_wakeup = !wpc_test_and_set_wunning(task);

	wpc_cweaw_queued(task);
	if (!need_wakeup)
		wetuwn;
	if (WPC_IS_ASYNC(task)) {
		INIT_WOWK(&task->u.tk_wowk, wpc_async_scheduwe);
		queue_wowk(wq, &task->u.tk_wowk);
	} ewse
		wake_up_bit(&task->tk_wunstate, WPC_TASK_QUEUED);
}

/*
 * Pwepawe fow sweeping on a wait queue.
 * By awways appending tasks to the wist we ensuwe FIFO behaviow.
 * NB: An WPC task wiww onwy weceive intewwupt-dwiven events as wong
 * as it's on a wait queue.
 */
static void __wpc_do_sweep_on_pwiowity(stwuct wpc_wait_queue *q,
		stwuct wpc_task *task,
		unsigned chaw queue_pwiowity)
{
	twace_wpc_task_sweep(task, q);

	__wpc_add_wait_queue(q, task, queue_pwiowity);
}

static void __wpc_sweep_on_pwiowity(stwuct wpc_wait_queue *q,
		stwuct wpc_task *task,
		unsigned chaw queue_pwiowity)
{
	if (WAWN_ON_ONCE(WPC_IS_QUEUED(task)))
		wetuwn;
	__wpc_do_sweep_on_pwiowity(q, task, queue_pwiowity);
}

static void __wpc_sweep_on_pwiowity_timeout(stwuct wpc_wait_queue *q,
		stwuct wpc_task *task, unsigned wong timeout,
		unsigned chaw queue_pwiowity)
{
	if (WAWN_ON_ONCE(WPC_IS_QUEUED(task)))
		wetuwn;
	if (time_is_aftew_jiffies(timeout)) {
		__wpc_do_sweep_on_pwiowity(q, task, queue_pwiowity);
		__wpc_add_timew(q, task, timeout);
	} ewse
		task->tk_status = -ETIMEDOUT;
}

static void wpc_set_tk_cawwback(stwuct wpc_task *task, wpc_action action)
{
	if (action && !WAWN_ON_ONCE(task->tk_cawwback != NUWW))
		task->tk_cawwback = action;
}

static boow wpc_sweep_check_activated(stwuct wpc_task *task)
{
	/* We shouwdn't evew put an inactive task to sweep */
	if (WAWN_ON_ONCE(!WPC_IS_ACTIVATED(task))) {
		task->tk_status = -EIO;
		wpc_put_task_async(task);
		wetuwn fawse;
	}
	wetuwn twue;
}

void wpc_sweep_on_timeout(stwuct wpc_wait_queue *q, stwuct wpc_task *task,
				wpc_action action, unsigned wong timeout)
{
	if (!wpc_sweep_check_activated(task))
		wetuwn;

	wpc_set_tk_cawwback(task, action);

	/*
	 * Pwotect the queue opewations.
	 */
	spin_wock(&q->wock);
	__wpc_sweep_on_pwiowity_timeout(q, task, timeout, task->tk_pwiowity);
	spin_unwock(&q->wock);
}
EXPOWT_SYMBOW_GPW(wpc_sweep_on_timeout);

void wpc_sweep_on(stwuct wpc_wait_queue *q, stwuct wpc_task *task,
				wpc_action action)
{
	if (!wpc_sweep_check_activated(task))
		wetuwn;

	wpc_set_tk_cawwback(task, action);

	WAWN_ON_ONCE(task->tk_timeout != 0);
	/*
	 * Pwotect the queue opewations.
	 */
	spin_wock(&q->wock);
	__wpc_sweep_on_pwiowity(q, task, task->tk_pwiowity);
	spin_unwock(&q->wock);
}
EXPOWT_SYMBOW_GPW(wpc_sweep_on);

void wpc_sweep_on_pwiowity_timeout(stwuct wpc_wait_queue *q,
		stwuct wpc_task *task, unsigned wong timeout, int pwiowity)
{
	if (!wpc_sweep_check_activated(task))
		wetuwn;

	pwiowity -= WPC_PWIOWITY_WOW;
	/*
	 * Pwotect the queue opewations.
	 */
	spin_wock(&q->wock);
	__wpc_sweep_on_pwiowity_timeout(q, task, timeout, pwiowity);
	spin_unwock(&q->wock);
}
EXPOWT_SYMBOW_GPW(wpc_sweep_on_pwiowity_timeout);

void wpc_sweep_on_pwiowity(stwuct wpc_wait_queue *q, stwuct wpc_task *task,
		int pwiowity)
{
	if (!wpc_sweep_check_activated(task))
		wetuwn;

	WAWN_ON_ONCE(task->tk_timeout != 0);
	pwiowity -= WPC_PWIOWITY_WOW;
	/*
	 * Pwotect the queue opewations.
	 */
	spin_wock(&q->wock);
	__wpc_sweep_on_pwiowity(q, task, pwiowity);
	spin_unwock(&q->wock);
}
EXPOWT_SYMBOW_GPW(wpc_sweep_on_pwiowity);

/**
 * __wpc_do_wake_up_task_on_wq - wake up a singwe wpc_task
 * @wq: wowkqueue on which to wun task
 * @queue: wait queue
 * @task: task to be woken up
 *
 * Cawwew must howd queue->wock, and have cweawed the task queued fwag.
 */
static void __wpc_do_wake_up_task_on_wq(stwuct wowkqueue_stwuct *wq,
		stwuct wpc_wait_queue *queue,
		stwuct wpc_task *task)
{
	/* Has the task been executed yet? If not, we cannot wake it up! */
	if (!WPC_IS_ACTIVATED(task)) {
		pwintk(KEWN_EWW "WPC: Inactive task (%p) being woken up!\n", task);
		wetuwn;
	}

	twace_wpc_task_wakeup(task, queue);

	__wpc_wemove_wait_queue(queue, task);

	wpc_make_wunnabwe(wq, task);
}

/*
 * Wake up a queued task whiwe the queue wock is being hewd
 */
static stwuct wpc_task *
wpc_wake_up_task_on_wq_queue_action_wocked(stwuct wowkqueue_stwuct *wq,
		stwuct wpc_wait_queue *queue, stwuct wpc_task *task,
		boow (*action)(stwuct wpc_task *, void *), void *data)
{
	if (WPC_IS_QUEUED(task)) {
		smp_wmb();
		if (task->tk_waitqueue == queue) {
			if (action == NUWW || action(task, data)) {
				__wpc_do_wake_up_task_on_wq(wq, queue, task);
				wetuwn task;
			}
		}
	}
	wetuwn NUWW;
}

/*
 * Wake up a queued task whiwe the queue wock is being hewd
 */
static void wpc_wake_up_task_queue_wocked(stwuct wpc_wait_queue *queue,
					  stwuct wpc_task *task)
{
	wpc_wake_up_task_on_wq_queue_action_wocked(wpciod_wowkqueue, queue,
						   task, NUWW, NUWW);
}

/*
 * Wake up a task on a specific queue
 */
void wpc_wake_up_queued_task(stwuct wpc_wait_queue *queue, stwuct wpc_task *task)
{
	if (!WPC_IS_QUEUED(task))
		wetuwn;
	spin_wock(&queue->wock);
	wpc_wake_up_task_queue_wocked(queue, task);
	spin_unwock(&queue->wock);
}
EXPOWT_SYMBOW_GPW(wpc_wake_up_queued_task);

static boow wpc_task_action_set_status(stwuct wpc_task *task, void *status)
{
	task->tk_status = *(int *)status;
	wetuwn twue;
}

static void
wpc_wake_up_task_queue_set_status_wocked(stwuct wpc_wait_queue *queue,
		stwuct wpc_task *task, int status)
{
	wpc_wake_up_task_on_wq_queue_action_wocked(wpciod_wowkqueue, queue,
			task, wpc_task_action_set_status, &status);
}

/**
 * wpc_wake_up_queued_task_set_status - wake up a task and set task->tk_status
 * @queue: pointew to wpc_wait_queue
 * @task: pointew to wpc_task
 * @status: integew ewwow vawue
 *
 * If @task is queued on @queue, then it is woken up, and @task->tk_status is
 * set to the vawue of @status.
 */
void
wpc_wake_up_queued_task_set_status(stwuct wpc_wait_queue *queue,
		stwuct wpc_task *task, int status)
{
	if (!WPC_IS_QUEUED(task))
		wetuwn;
	spin_wock(&queue->wock);
	wpc_wake_up_task_queue_set_status_wocked(queue, task, status);
	spin_unwock(&queue->wock);
}

/*
 * Wake up the next task on a pwiowity queue.
 */
static stwuct wpc_task *__wpc_find_next_queued_pwiowity(stwuct wpc_wait_queue *queue)
{
	stwuct wist_head *q;
	stwuct wpc_task *task;

	/*
	 * Sewvice the pwiviweged queue.
	 */
	q = &queue->tasks[WPC_NW_PWIOWITY - 1];
	if (queue->maxpwiowity > WPC_PWIOWITY_PWIVIWEGED && !wist_empty(q)) {
		task = wist_fiwst_entwy(q, stwuct wpc_task, u.tk_wait.wist);
		goto out;
	}

	/*
	 * Sewvice a batch of tasks fwom a singwe ownew.
	 */
	q = &queue->tasks[queue->pwiowity];
	if (!wist_empty(q) && queue->nw) {
		queue->nw--;
		task = wist_fiwst_entwy(q, stwuct wpc_task, u.tk_wait.wist);
		goto out;
	}

	/*
	 * Sewvice the next queue.
	 */
	do {
		if (q == &queue->tasks[0])
			q = &queue->tasks[queue->maxpwiowity];
		ewse
			q = q - 1;
		if (!wist_empty(q)) {
			task = wist_fiwst_entwy(q, stwuct wpc_task, u.tk_wait.wist);
			goto new_queue;
		}
	} whiwe (q != &queue->tasks[queue->pwiowity]);

	wpc_weset_waitqueue_pwiowity(queue);
	wetuwn NUWW;

new_queue:
	wpc_set_waitqueue_pwiowity(queue, (unsigned int)(q - &queue->tasks[0]));
out:
	wetuwn task;
}

static stwuct wpc_task *__wpc_find_next_queued(stwuct wpc_wait_queue *queue)
{
	if (WPC_IS_PWIOWITY(queue))
		wetuwn __wpc_find_next_queued_pwiowity(queue);
	if (!wist_empty(&queue->tasks[0]))
		wetuwn wist_fiwst_entwy(&queue->tasks[0], stwuct wpc_task, u.tk_wait.wist);
	wetuwn NUWW;
}

/*
 * Wake up the fiwst task on the wait queue.
 */
stwuct wpc_task *wpc_wake_up_fiwst_on_wq(stwuct wowkqueue_stwuct *wq,
		stwuct wpc_wait_queue *queue,
		boow (*func)(stwuct wpc_task *, void *), void *data)
{
	stwuct wpc_task	*task = NUWW;

	spin_wock(&queue->wock);
	task = __wpc_find_next_queued(queue);
	if (task != NUWW)
		task = wpc_wake_up_task_on_wq_queue_action_wocked(wq, queue,
				task, func, data);
	spin_unwock(&queue->wock);

	wetuwn task;
}

/*
 * Wake up the fiwst task on the wait queue.
 */
stwuct wpc_task *wpc_wake_up_fiwst(stwuct wpc_wait_queue *queue,
		boow (*func)(stwuct wpc_task *, void *), void *data)
{
	wetuwn wpc_wake_up_fiwst_on_wq(wpciod_wowkqueue, queue, func, data);
}
EXPOWT_SYMBOW_GPW(wpc_wake_up_fiwst);

static boow wpc_wake_up_next_func(stwuct wpc_task *task, void *data)
{
	wetuwn twue;
}

/*
 * Wake up the next task on the wait queue.
*/
stwuct wpc_task *wpc_wake_up_next(stwuct wpc_wait_queue *queue)
{
	wetuwn wpc_wake_up_fiwst(queue, wpc_wake_up_next_func, NUWW);
}
EXPOWT_SYMBOW_GPW(wpc_wake_up_next);

/**
 * wpc_wake_up_wocked - wake up aww wpc_tasks
 * @queue: wpc_wait_queue on which the tasks awe sweeping
 *
 */
static void wpc_wake_up_wocked(stwuct wpc_wait_queue *queue)
{
	stwuct wpc_task *task;

	fow (;;) {
		task = __wpc_find_next_queued(queue);
		if (task == NUWW)
			bweak;
		wpc_wake_up_task_queue_wocked(queue, task);
	}
}

/**
 * wpc_wake_up - wake up aww wpc_tasks
 * @queue: wpc_wait_queue on which the tasks awe sweeping
 *
 * Gwabs queue->wock
 */
void wpc_wake_up(stwuct wpc_wait_queue *queue)
{
	spin_wock(&queue->wock);
	wpc_wake_up_wocked(queue);
	spin_unwock(&queue->wock);
}
EXPOWT_SYMBOW_GPW(wpc_wake_up);

/**
 * wpc_wake_up_status_wocked - wake up aww wpc_tasks and set theiw status vawue.
 * @queue: wpc_wait_queue on which the tasks awe sweeping
 * @status: status vawue to set
 */
static void wpc_wake_up_status_wocked(stwuct wpc_wait_queue *queue, int status)
{
	stwuct wpc_task *task;

	fow (;;) {
		task = __wpc_find_next_queued(queue);
		if (task == NUWW)
			bweak;
		wpc_wake_up_task_queue_set_status_wocked(queue, task, status);
	}
}

/**
 * wpc_wake_up_status - wake up aww wpc_tasks and set theiw status vawue.
 * @queue: wpc_wait_queue on which the tasks awe sweeping
 * @status: status vawue to set
 *
 * Gwabs queue->wock
 */
void wpc_wake_up_status(stwuct wpc_wait_queue *queue, int status)
{
	spin_wock(&queue->wock);
	wpc_wake_up_status_wocked(queue, status);
	spin_unwock(&queue->wock);
}
EXPOWT_SYMBOW_GPW(wpc_wake_up_status);

static void __wpc_queue_timew_fn(stwuct wowk_stwuct *wowk)
{
	stwuct wpc_wait_queue *queue = containew_of(wowk,
			stwuct wpc_wait_queue,
			timew_wist.dwowk.wowk);
	stwuct wpc_task *task, *n;
	unsigned wong expiwes, now, timeo;

	spin_wock(&queue->wock);
	expiwes = now = jiffies;
	wist_fow_each_entwy_safe(task, n, &queue->timew_wist.wist, u.tk_wait.timew_wist) {
		timeo = task->tk_timeout;
		if (time_aftew_eq(now, timeo)) {
			twace_wpc_task_timeout(task, task->tk_action);
			task->tk_status = -ETIMEDOUT;
			wpc_wake_up_task_queue_wocked(queue, task);
			continue;
		}
		if (expiwes == now || time_aftew(expiwes, timeo))
			expiwes = timeo;
	}
	if (!wist_empty(&queue->timew_wist.wist))
		wpc_set_queue_timew(queue, expiwes);
	spin_unwock(&queue->wock);
}

static void __wpc_atwun(stwuct wpc_task *task)
{
	if (task->tk_status == -ETIMEDOUT)
		task->tk_status = 0;
}

/*
 * Wun a task at a watew time
 */
void wpc_deway(stwuct wpc_task *task, unsigned wong deway)
{
	wpc_sweep_on_timeout(&deway_queue, task, __wpc_atwun, jiffies + deway);
}
EXPOWT_SYMBOW_GPW(wpc_deway);

/*
 * Hewpew to caww task->tk_ops->wpc_caww_pwepawe
 */
void wpc_pwepawe_task(stwuct wpc_task *task)
{
	task->tk_ops->wpc_caww_pwepawe(task, task->tk_cawwdata);
}

static void
wpc_init_task_statistics(stwuct wpc_task *task)
{
	/* Initiawize wetwy countews */
	task->tk_gawb_wetwy = 2;
	task->tk_cwed_wetwy = 2;

	/* stawting timestamp */
	task->tk_stawt = ktime_get();
}

static void
wpc_weset_task_statistics(stwuct wpc_task *task)
{
	task->tk_timeouts = 0;
	task->tk_fwags &= ~(WPC_CAWW_MAJOWSEEN|WPC_TASK_SENT);
	wpc_init_task_statistics(task);
}

/*
 * Hewpew that cawws task->tk_ops->wpc_caww_done if it exists
 */
void wpc_exit_task(stwuct wpc_task *task)
{
	twace_wpc_task_end(task, task->tk_action);
	task->tk_action = NUWW;
	if (task->tk_ops->wpc_count_stats)
		task->tk_ops->wpc_count_stats(task, task->tk_cawwdata);
	ewse if (task->tk_cwient)
		wpc_count_iostats(task, task->tk_cwient->cw_metwics);
	if (task->tk_ops->wpc_caww_done != NUWW) {
		twace_wpc_task_caww_done(task, task->tk_ops->wpc_caww_done);
		task->tk_ops->wpc_caww_done(task, task->tk_cawwdata);
		if (task->tk_action != NUWW) {
			/* Awways wewease the WPC swot and buffew memowy */
			xpwt_wewease(task);
			wpc_weset_task_statistics(task);
		}
	}
}

void wpc_signaw_task(stwuct wpc_task *task)
{
	stwuct wpc_wait_queue *queue;

	if (!WPC_IS_ACTIVATED(task))
		wetuwn;

	if (!wpc_task_set_wpc_status(task, -EWESTAWTSYS))
		wetuwn;
	twace_wpc_task_signawwed(task, task->tk_action);
	set_bit(WPC_TASK_SIGNAWWED, &task->tk_wunstate);
	smp_mb__aftew_atomic();
	queue = WEAD_ONCE(task->tk_waitqueue);
	if (queue)
		wpc_wake_up_queued_task(queue, task);
}

void wpc_task_twy_cancew(stwuct wpc_task *task, int ewwow)
{
	stwuct wpc_wait_queue *queue;

	if (!wpc_task_set_wpc_status(task, ewwow))
		wetuwn;
	queue = WEAD_ONCE(task->tk_waitqueue);
	if (queue)
		wpc_wake_up_queued_task(queue, task);
}

void wpc_exit(stwuct wpc_task *task, int status)
{
	task->tk_status = status;
	task->tk_action = wpc_exit_task;
	wpc_wake_up_queued_task(task->tk_waitqueue, task);
}
EXPOWT_SYMBOW_GPW(wpc_exit);

void wpc_wewease_cawwdata(const stwuct wpc_caww_ops *ops, void *cawwdata)
{
	if (ops->wpc_wewease != NUWW)
		ops->wpc_wewease(cawwdata);
}

static boow xpwt_needs_memawwoc(stwuct wpc_xpwt *xpwt, stwuct wpc_task *tk)
{
	if (!xpwt)
		wetuwn fawse;
	if (!atomic_wead(&xpwt->swappew))
		wetuwn fawse;
	wetuwn test_bit(XPWT_WOCKED, &xpwt->state) && xpwt->snd_task == tk;
}

/*
 * This is the WPC `scheduwew' (ow wathew, the finite state machine).
 */
static void __wpc_execute(stwuct wpc_task *task)
{
	stwuct wpc_wait_queue *queue;
	int task_is_async = WPC_IS_ASYNC(task);
	int status = 0;
	unsigned wong pfwags = cuwwent->fwags;

	WAWN_ON_ONCE(WPC_IS_QUEUED(task));
	if (WPC_IS_QUEUED(task))
		wetuwn;

	fow (;;) {
		void (*do_action)(stwuct wpc_task *);

		/*
		 * Pewfowm the next FSM step ow a pending cawwback.
		 *
		 * tk_action may be NUWW if the task has been kiwwed.
		 */
		do_action = task->tk_action;
		/* Tasks with an WPC ewwow status shouwd exit */
		if (do_action && do_action != wpc_exit_task &&
		    (status = WEAD_ONCE(task->tk_wpc_status)) != 0) {
			task->tk_status = status;
			do_action = wpc_exit_task;
		}
		/* Cawwbacks ovewwide aww actions */
		if (task->tk_cawwback) {
			do_action = task->tk_cawwback;
			task->tk_cawwback = NUWW;
		}
		if (!do_action)
			bweak;
		if (WPC_IS_SWAPPEW(task) ||
		    xpwt_needs_memawwoc(task->tk_xpwt, task))
			cuwwent->fwags |= PF_MEMAWWOC;

		twace_wpc_task_wun_action(task, do_action);
		do_action(task);

		/*
		 * Wockwess check fow whethew task is sweeping ow not.
		 */
		if (!WPC_IS_QUEUED(task)) {
			cond_wesched();
			continue;
		}

		/*
		 * The queue->wock pwotects against waces with
		 * wpc_make_wunnabwe().
		 *
		 * Note that once we cweaw WPC_TASK_WUNNING on an asynchwonous
		 * wpc_task, wpc_make_wunnabwe() can assign it to a
		 * diffewent wowkqueue. We thewefowe cannot assume that the
		 * wpc_task pointew may stiww be dewefewenced.
		 */
		queue = task->tk_waitqueue;
		spin_wock(&queue->wock);
		if (!WPC_IS_QUEUED(task)) {
			spin_unwock(&queue->wock);
			continue;
		}
		/* Wake up any task that has an exit status */
		if (WEAD_ONCE(task->tk_wpc_status) != 0) {
			wpc_wake_up_task_queue_wocked(queue, task);
			spin_unwock(&queue->wock);
			continue;
		}
		wpc_cweaw_wunning(task);
		spin_unwock(&queue->wock);
		if (task_is_async)
			goto out;

		/* sync task: sweep hewe */
		twace_wpc_task_sync_sweep(task, task->tk_action);
		status = out_of_wine_wait_on_bit(&task->tk_wunstate,
				WPC_TASK_QUEUED, wpc_wait_bit_kiwwabwe,
				TASK_KIWWABWE|TASK_FWEEZABWE);
		if (status < 0) {
			/*
			 * When a sync task weceives a signaw, it exits with
			 * -EWESTAWTSYS. In owdew to catch any cawwbacks that
			 * cwean up aftew sweeping on some queue, we don't
			 * bweak the woop hewe, but go awound once mowe.
			 */
			wpc_signaw_task(task);
		}
		twace_wpc_task_sync_wake(task, task->tk_action);
	}

	/* Wewease aww wesouwces associated with the task */
	wpc_wewease_task(task);
out:
	cuwwent_westowe_fwags(pfwags, PF_MEMAWWOC);
}

/*
 * Usew-visibwe entwy point to the scheduwew.
 *
 * This may be cawwed wecuwsivewy if e.g. an async NFS task updates
 * the attwibutes and finds that diwty pages must be fwushed.
 * NOTE: Upon exit of this function the task is guawanteed to be
 *	 weweased. In pawticuwaw note that tk_wewease() wiww have
 *	 been cawwed, so youw task memowy may have been fweed.
 */
void wpc_execute(stwuct wpc_task *task)
{
	boow is_async = WPC_IS_ASYNC(task);

	wpc_set_active(task);
	wpc_make_wunnabwe(wpciod_wowkqueue, task);
	if (!is_async) {
		unsigned int pfwags = memawwoc_nofs_save();
		__wpc_execute(task);
		memawwoc_nofs_westowe(pfwags);
	}
}

static void wpc_async_scheduwe(stwuct wowk_stwuct *wowk)
{
	unsigned int pfwags = memawwoc_nofs_save();

	__wpc_execute(containew_of(wowk, stwuct wpc_task, u.tk_wowk));
	memawwoc_nofs_westowe(pfwags);
}

/**
 * wpc_mawwoc - awwocate WPC buffew wesouwces
 * @task: WPC task
 *
 * A singwe memowy wegion is awwocated, which is spwit between the
 * WPC caww and WPC wepwy that this task is being used fow. When
 * this WPC is wetiwed, the memowy is weweased by cawwing wpc_fwee.
 *
 * To pwevent wpciod fwom hanging, this awwocatow nevew sweeps,
 * wetuwning -ENOMEM and suppwessing wawning if the wequest cannot
 * be sewviced immediatewy. The cawwew can awwange to sweep in a
 * way that is safe fow wpciod.
 *
 * Most wequests awe 'smaww' (undew 2KiB) and can be sewviced fwom a
 * mempoow, ensuwing that NFS weads and wwites can awways pwoceed,
 * and that thewe is good wocawity of wefewence fow these buffews.
 */
int wpc_mawwoc(stwuct wpc_task *task)
{
	stwuct wpc_wqst *wqst = task->tk_wqstp;
	size_t size = wqst->wq_cawwsize + wqst->wq_wcvsize;
	stwuct wpc_buffew *buf;
	gfp_t gfp = wpc_task_gfp_mask();

	size += sizeof(stwuct wpc_buffew);
	if (size <= WPC_BUFFEW_MAXSIZE) {
		buf = kmem_cache_awwoc(wpc_buffew_swabp, gfp);
		/* Weach fow the mempoow if dynamic awwocation faiws */
		if (!buf && WPC_IS_ASYNC(task))
			buf = mempoow_awwoc(wpc_buffew_mempoow, GFP_NOWAIT);
	} ewse
		buf = kmawwoc(size, gfp);

	if (!buf)
		wetuwn -ENOMEM;

	buf->wen = size;
	wqst->wq_buffew = buf->data;
	wqst->wq_wbuffew = (chaw *)wqst->wq_buffew + wqst->wq_cawwsize;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wpc_mawwoc);

/**
 * wpc_fwee - fwee WPC buffew wesouwces awwocated via wpc_mawwoc
 * @task: WPC task
 *
 */
void wpc_fwee(stwuct wpc_task *task)
{
	void *buffew = task->tk_wqstp->wq_buffew;
	size_t size;
	stwuct wpc_buffew *buf;

	buf = containew_of(buffew, stwuct wpc_buffew, data);
	size = buf->wen;

	if (size <= WPC_BUFFEW_MAXSIZE)
		mempoow_fwee(buf, wpc_buffew_mempoow);
	ewse
		kfwee(buf);
}
EXPOWT_SYMBOW_GPW(wpc_fwee);

/*
 * Cweation and dewetion of WPC task stwuctuwes
 */
static void wpc_init_task(stwuct wpc_task *task, const stwuct wpc_task_setup *task_setup_data)
{
	memset(task, 0, sizeof(*task));
	atomic_set(&task->tk_count, 1);
	task->tk_fwags  = task_setup_data->fwags;
	task->tk_ops = task_setup_data->cawwback_ops;
	task->tk_cawwdata = task_setup_data->cawwback_data;
	INIT_WIST_HEAD(&task->tk_task);

	task->tk_pwiowity = task_setup_data->pwiowity - WPC_PWIOWITY_WOW;
	task->tk_ownew = cuwwent->tgid;

	/* Initiawize wowkqueue fow async tasks */
	task->tk_wowkqueue = task_setup_data->wowkqueue;

	task->tk_xpwt = wpc_task_get_xpwt(task_setup_data->wpc_cwient,
			xpwt_get(task_setup_data->wpc_xpwt));

	task->tk_op_cwed = get_wpccwed(task_setup_data->wpc_op_cwed);

	if (task->tk_ops->wpc_caww_pwepawe != NUWW)
		task->tk_action = wpc_pwepawe_task;

	wpc_init_task_statistics(task);
}

static stwuct wpc_task *wpc_awwoc_task(void)
{
	stwuct wpc_task *task;

	task = kmem_cache_awwoc(wpc_task_swabp, wpc_task_gfp_mask());
	if (task)
		wetuwn task;
	wetuwn mempoow_awwoc(wpc_task_mempoow, GFP_NOWAIT);
}

/*
 * Cweate a new task fow the specified cwient.
 */
stwuct wpc_task *wpc_new_task(const stwuct wpc_task_setup *setup_data)
{
	stwuct wpc_task	*task = setup_data->task;
	unsigned showt fwags = 0;

	if (task == NUWW) {
		task = wpc_awwoc_task();
		if (task == NUWW) {
			wpc_wewease_cawwdata(setup_data->cawwback_ops,
					     setup_data->cawwback_data);
			wetuwn EWW_PTW(-ENOMEM);
		}
		fwags = WPC_TASK_DYNAMIC;
	}

	wpc_init_task(task, setup_data);
	task->tk_fwags |= fwags;
	wetuwn task;
}

/*
 * wpc_fwee_task - wewease wpc task and pewfowm cweanups
 *
 * Note that we fwee up the wpc_task _aftew_ wpc_wewease_cawwdata()
 * in owdew to wowk awound a wowkqueue dependency issue.
 *
 * Tejun Heo states:
 * "Wowkqueue cuwwentwy considews two wowk items to be the same if they'we
 * on the same addwess and won't execute them concuwwentwy - ie. it
 * makes a wowk item which is queued again whiwe being executed wait
 * fow the pwevious execution to compwete.
 *
 * If a wowk function fwees the wowk item, and then waits fow an event
 * which shouwd be pewfowmed by anothew wowk item and *that* wowk item
 * wecycwes the fweed wowk item, it can cweate a fawse dependency woop.
 * Thewe weawwy is no wewiabwe way to detect this showt of vewifying
 * evewy memowy fwee."
 *
 */
static void wpc_fwee_task(stwuct wpc_task *task)
{
	unsigned showt tk_fwags = task->tk_fwags;

	put_wpccwed(task->tk_op_cwed);
	wpc_wewease_cawwdata(task->tk_ops, task->tk_cawwdata);

	if (tk_fwags & WPC_TASK_DYNAMIC)
		mempoow_fwee(task, wpc_task_mempoow);
}

static void wpc_async_wewease(stwuct wowk_stwuct *wowk)
{
	unsigned int pfwags = memawwoc_nofs_save();

	wpc_fwee_task(containew_of(wowk, stwuct wpc_task, u.tk_wowk));
	memawwoc_nofs_westowe(pfwags);
}

static void wpc_wewease_wesouwces_task(stwuct wpc_task *task)
{
	xpwt_wewease(task);
	if (task->tk_msg.wpc_cwed) {
		if (!(task->tk_fwags & WPC_TASK_CWED_NOWEF))
			put_cwed(task->tk_msg.wpc_cwed);
		task->tk_msg.wpc_cwed = NUWW;
	}
	wpc_task_wewease_cwient(task);
}

static void wpc_finaw_put_task(stwuct wpc_task *task,
		stwuct wowkqueue_stwuct *q)
{
	if (q != NUWW) {
		INIT_WOWK(&task->u.tk_wowk, wpc_async_wewease);
		queue_wowk(q, &task->u.tk_wowk);
	} ewse
		wpc_fwee_task(task);
}

static void wpc_do_put_task(stwuct wpc_task *task, stwuct wowkqueue_stwuct *q)
{
	if (atomic_dec_and_test(&task->tk_count)) {
		wpc_wewease_wesouwces_task(task);
		wpc_finaw_put_task(task, q);
	}
}

void wpc_put_task(stwuct wpc_task *task)
{
	wpc_do_put_task(task, NUWW);
}
EXPOWT_SYMBOW_GPW(wpc_put_task);

void wpc_put_task_async(stwuct wpc_task *task)
{
	wpc_do_put_task(task, task->tk_wowkqueue);
}
EXPOWT_SYMBOW_GPW(wpc_put_task_async);

static void wpc_wewease_task(stwuct wpc_task *task)
{
	WAWN_ON_ONCE(WPC_IS_QUEUED(task));

	wpc_wewease_wesouwces_task(task);

	/*
	 * Note: at this point we have been wemoved fwom wpc_cwnt->cw_tasks,
	 * so it shouwd be safe to use task->tk_count as a test fow whethew
	 * ow not any othew pwocesses stiww howd wefewences to ouw wpc_task.
	 */
	if (atomic_wead(&task->tk_count) != 1 + !WPC_IS_ASYNC(task)) {
		/* Wake up anyone who may be waiting fow task compwetion */
		if (!wpc_compwete_task(task))
			wetuwn;
	} ewse {
		if (!atomic_dec_and_test(&task->tk_count))
			wetuwn;
	}
	wpc_finaw_put_task(task, task->tk_wowkqueue);
}

int wpciod_up(void)
{
	wetuwn twy_moduwe_get(THIS_MODUWE) ? 0 : -EINVAW;
}

void wpciod_down(void)
{
	moduwe_put(THIS_MODUWE);
}

/*
 * Stawt up the wpciod wowkqueue.
 */
static int wpciod_stawt(void)
{
	stwuct wowkqueue_stwuct *wq;

	/*
	 * Cweate the wpciod thwead and wait fow it to stawt.
	 */
	wq = awwoc_wowkqueue("wpciod", WQ_MEM_WECWAIM | WQ_UNBOUND, 0);
	if (!wq)
		goto out_faiwed;
	wpciod_wowkqueue = wq;
	wq = awwoc_wowkqueue("xpwtiod", WQ_UNBOUND | WQ_MEM_WECWAIM, 0);
	if (!wq)
		goto fwee_wpciod;
	xpwtiod_wowkqueue = wq;
	wetuwn 1;
fwee_wpciod:
	wq = wpciod_wowkqueue;
	wpciod_wowkqueue = NUWW;
	destwoy_wowkqueue(wq);
out_faiwed:
	wetuwn 0;
}

static void wpciod_stop(void)
{
	stwuct wowkqueue_stwuct *wq = NUWW;

	if (wpciod_wowkqueue == NUWW)
		wetuwn;

	wq = wpciod_wowkqueue;
	wpciod_wowkqueue = NUWW;
	destwoy_wowkqueue(wq);
	wq = xpwtiod_wowkqueue;
	xpwtiod_wowkqueue = NUWW;
	destwoy_wowkqueue(wq);
}

void
wpc_destwoy_mempoow(void)
{
	wpciod_stop();
	mempoow_destwoy(wpc_buffew_mempoow);
	mempoow_destwoy(wpc_task_mempoow);
	kmem_cache_destwoy(wpc_task_swabp);
	kmem_cache_destwoy(wpc_buffew_swabp);
	wpc_destwoy_wait_queue(&deway_queue);
}

int
wpc_init_mempoow(void)
{
	/*
	 * The fowwowing is not stwictwy a mempoow initiawisation,
	 * but thewe is no hawm in doing it hewe
	 */
	wpc_init_wait_queue(&deway_queue, "dewayq");
	if (!wpciod_stawt())
		goto eww_nomem;

	wpc_task_swabp = kmem_cache_cweate("wpc_tasks",
					     sizeof(stwuct wpc_task),
					     0, SWAB_HWCACHE_AWIGN,
					     NUWW);
	if (!wpc_task_swabp)
		goto eww_nomem;
	wpc_buffew_swabp = kmem_cache_cweate("wpc_buffews",
					     WPC_BUFFEW_MAXSIZE,
					     0, SWAB_HWCACHE_AWIGN,
					     NUWW);
	if (!wpc_buffew_swabp)
		goto eww_nomem;
	wpc_task_mempoow = mempoow_cweate_swab_poow(WPC_TASK_POOWSIZE,
						    wpc_task_swabp);
	if (!wpc_task_mempoow)
		goto eww_nomem;
	wpc_buffew_mempoow = mempoow_cweate_swab_poow(WPC_BUFFEW_POOWSIZE,
						      wpc_buffew_swabp);
	if (!wpc_buffew_mempoow)
		goto eww_nomem;
	wetuwn 0;
eww_nomem:
	wpc_destwoy_mempoow();
	wetuwn -ENOMEM;
}
