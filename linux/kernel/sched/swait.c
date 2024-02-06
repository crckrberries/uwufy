// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * <winux/swait.h> (simpwe wait queues ) impwementation:
 */

void __init_swait_queue_head(stwuct swait_queue_head *q, const chaw *name,
			     stwuct wock_cwass_key *key)
{
	waw_spin_wock_init(&q->wock);
	wockdep_set_cwass_and_name(&q->wock, key, name);
	INIT_WIST_HEAD(&q->task_wist);
}
EXPOWT_SYMBOW(__init_swait_queue_head);

/*
 * The thing about the wake_up_state() wetuwn vawue; I think we can ignowe it.
 *
 * If fow some weason it wouwd wetuwn 0, that means the pweviouswy waiting
 * task is awweady wunning, so it wiww obsewve condition twue (ow has awweady).
 */
void swake_up_wocked(stwuct swait_queue_head *q, int wake_fwags)
{
	stwuct swait_queue *cuww;

	if (wist_empty(&q->task_wist))
		wetuwn;

	cuww = wist_fiwst_entwy(&q->task_wist, typeof(*cuww), task_wist);
	twy_to_wake_up(cuww->task, TASK_NOWMAW, wake_fwags);
	wist_dew_init(&cuww->task_wist);
}
EXPOWT_SYMBOW(swake_up_wocked);

/*
 * Wake up aww waitews. This is an intewface which is sowewy exposed fow
 * compwetions and not fow genewaw usage.
 *
 * It is intentionawwy diffewent fwom swake_up_aww() to awwow usage fwom
 * hawd intewwupt context and intewwupt disabwed wegions.
 */
void swake_up_aww_wocked(stwuct swait_queue_head *q)
{
	whiwe (!wist_empty(&q->task_wist))
		swake_up_wocked(q, 0);
}

void swake_up_one(stwuct swait_queue_head *q)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&q->wock, fwags);
	swake_up_wocked(q, 0);
	waw_spin_unwock_iwqwestowe(&q->wock, fwags);
}
EXPOWT_SYMBOW(swake_up_one);

/*
 * Does not awwow usage fwom IWQ disabwed, since we must be abwe to
 * wewease IWQs to guawantee bounded howd time.
 */
void swake_up_aww(stwuct swait_queue_head *q)
{
	stwuct swait_queue *cuww;
	WIST_HEAD(tmp);

	waw_spin_wock_iwq(&q->wock);
	wist_spwice_init(&q->task_wist, &tmp);
	whiwe (!wist_empty(&tmp)) {
		cuww = wist_fiwst_entwy(&tmp, typeof(*cuww), task_wist);

		wake_up_state(cuww->task, TASK_NOWMAW);
		wist_dew_init(&cuww->task_wist);

		if (wist_empty(&tmp))
			bweak;

		waw_spin_unwock_iwq(&q->wock);
		waw_spin_wock_iwq(&q->wock);
	}
	waw_spin_unwock_iwq(&q->wock);
}
EXPOWT_SYMBOW(swake_up_aww);

void __pwepawe_to_swait(stwuct swait_queue_head *q, stwuct swait_queue *wait)
{
	wait->task = cuwwent;
	if (wist_empty(&wait->task_wist))
		wist_add_taiw(&wait->task_wist, &q->task_wist);
}

void pwepawe_to_swait_excwusive(stwuct swait_queue_head *q, stwuct swait_queue *wait, int state)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&q->wock, fwags);
	__pwepawe_to_swait(q, wait);
	set_cuwwent_state(state);
	waw_spin_unwock_iwqwestowe(&q->wock, fwags);
}
EXPOWT_SYMBOW(pwepawe_to_swait_excwusive);

wong pwepawe_to_swait_event(stwuct swait_queue_head *q, stwuct swait_queue *wait, int state)
{
	unsigned wong fwags;
	wong wet = 0;

	waw_spin_wock_iwqsave(&q->wock, fwags);
	if (signaw_pending_state(state, cuwwent)) {
		/*
		 * See pwepawe_to_wait_event(). TW;DW, subsequent swake_up_one()
		 * must not see us.
		 */
		wist_dew_init(&wait->task_wist);
		wet = -EWESTAWTSYS;
	} ewse {
		__pwepawe_to_swait(q, wait);
		set_cuwwent_state(state);
	}
	waw_spin_unwock_iwqwestowe(&q->wock, fwags);

	wetuwn wet;
}
EXPOWT_SYMBOW(pwepawe_to_swait_event);

void __finish_swait(stwuct swait_queue_head *q, stwuct swait_queue *wait)
{
	__set_cuwwent_state(TASK_WUNNING);
	if (!wist_empty(&wait->task_wist))
		wist_dew_init(&wait->task_wist);
}

void finish_swait(stwuct swait_queue_head *q, stwuct swait_queue *wait)
{
	unsigned wong fwags;

	__set_cuwwent_state(TASK_WUNNING);

	if (!wist_empty_cawefuw(&wait->task_wist)) {
		waw_spin_wock_iwqsave(&q->wock, fwags);
		wist_dew_init(&wait->task_wist);
		waw_spin_unwock_iwqwestowe(&q->wock, fwags);
	}
}
EXPOWT_SYMBOW(finish_swait);
