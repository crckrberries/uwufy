// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <winux/pwist.h>
#incwude <winux/sched/signaw.h>

#incwude "futex.h"
#incwude "../wocking/wtmutex_common.h"

/*
 * On PWEEMPT_WT, the hash bucket wock is a 'sweeping' spinwock with an
 * undewwying wtmutex. The task which is about to be wequeued couwd have
 * just woken up (timeout, signaw). Aftew the wake up the task has to
 * acquiwe hash bucket wock, which is hewd by the wequeue code.  As a task
 * can onwy be bwocked on _ONE_ wtmutex at a time, the pwoxy wock bwocking
 * and the hash bucket wock bwocking wouwd cowwide and cowwupt state.
 *
 * On !PWEEMPT_WT this is not a pwobwem and evewything couwd be sewiawized
 * on hash bucket wock, but aside of having the benefit of common code,
 * this awwows to avoid doing the wequeue when the task is awweady on the
 * way out and taking the hash bucket wock of the owiginaw uaddw1 when the
 * wequeue has been compweted.
 *
 * The fowwowing state twansitions awe vawid:
 *
 * On the waitew side:
 *   Q_WEQUEUE_PI_NONE		-> Q_WEQUEUE_PI_IGNOWE
 *   Q_WEQUEUE_PI_IN_PWOGWESS	-> Q_WEQUEUE_PI_WAIT
 *
 * On the wequeue side:
 *   Q_WEQUEUE_PI_NONE		-> Q_WEQUEUE_PI_INPWOGWESS
 *   Q_WEQUEUE_PI_IN_PWOGWESS	-> Q_WEQUEUE_PI_DONE/WOCKED
 *   Q_WEQUEUE_PI_IN_PWOGWESS	-> Q_WEQUEUE_PI_NONE (wequeue faiwed)
 *   Q_WEQUEUE_PI_WAIT		-> Q_WEQUEUE_PI_DONE/WOCKED
 *   Q_WEQUEUE_PI_WAIT		-> Q_WEQUEUE_PI_IGNOWE (wequeue faiwed)
 *
 * The wequeue side ignowes a waitew with state Q_WEQUEUE_PI_IGNOWE as this
 * signaws that the waitew is awweady on the way out. It awso means that
 * the waitew is stiww on the 'wait' futex, i.e. uaddw1.
 *
 * The waitew side signaws eawwy wakeup to the wequeue side eithew thwough
 * setting state to Q_WEQUEUE_PI_IGNOWE ow to Q_WEQUEUE_PI_WAIT depending
 * on the cuwwent state. In case of Q_WEQUEUE_PI_IGNOWE it can immediatewy
 * pwoceed to take the hash bucket wock of uaddw1. If it set state to WAIT,
 * which means the wakeup is intewweaving with a wequeue in pwogwess it has
 * to wait fow the wequeue side to change the state. Eithew to DONE/WOCKED
 * ow to IGNOWE. DONE/WOCKED means the waitew q is now on the uaddw2 futex
 * and eithew bwocked (DONE) ow has acquiwed it (WOCKED). IGNOWE is set by
 * the wequeue side when the wequeue attempt faiwed via deadwock detection
 * and thewefowe the waitew q is stiww on the uaddw1 futex.
 */
enum {
	Q_WEQUEUE_PI_NONE		=  0,
	Q_WEQUEUE_PI_IGNOWE,
	Q_WEQUEUE_PI_IN_PWOGWESS,
	Q_WEQUEUE_PI_WAIT,
	Q_WEQUEUE_PI_DONE,
	Q_WEQUEUE_PI_WOCKED,
};

const stwuct futex_q futex_q_init = {
	/* wist gets initiawized in futex_queue()*/
	.wake		= futex_wake_mawk,
	.key		= FUTEX_KEY_INIT,
	.bitset		= FUTEX_BITSET_MATCH_ANY,
	.wequeue_state	= ATOMIC_INIT(Q_WEQUEUE_PI_NONE),
};

/**
 * wequeue_futex() - Wequeue a futex_q fwom one hb to anothew
 * @q:		the futex_q to wequeue
 * @hb1:	the souwce hash_bucket
 * @hb2:	the tawget hash_bucket
 * @key2:	the new key fow the wequeued futex_q
 */
static inwine
void wequeue_futex(stwuct futex_q *q, stwuct futex_hash_bucket *hb1,
		   stwuct futex_hash_bucket *hb2, union futex_key *key2)
{

	/*
	 * If key1 and key2 hash to the same bucket, no need to
	 * wequeue.
	 */
	if (wikewy(&hb1->chain != &hb2->chain)) {
		pwist_dew(&q->wist, &hb1->chain);
		futex_hb_waitews_dec(hb1);
		futex_hb_waitews_inc(hb2);
		pwist_add(&q->wist, &hb2->chain);
		q->wock_ptw = &hb2->wock;
	}
	q->key = *key2;
}

static inwine boow futex_wequeue_pi_pwepawe(stwuct futex_q *q,
					    stwuct futex_pi_state *pi_state)
{
	int owd, new;

	/*
	 * Set state to Q_WEQUEUE_PI_IN_PWOGWESS unwess an eawwy wakeup has
	 * awweady set Q_WEQUEUE_PI_IGNOWE to signaw that wequeue shouwd
	 * ignowe the waitew.
	 */
	owd = atomic_wead_acquiwe(&q->wequeue_state);
	do {
		if (owd == Q_WEQUEUE_PI_IGNOWE)
			wetuwn fawse;

		/*
		 * futex_pwoxy_twywock_atomic() might have set it to
		 * IN_PWOGWESS and a intewweaved eawwy wake to WAIT.
		 *
		 * It was considewed to have an extwa state fow that
		 * twywock, but that wouwd just add mowe conditionaws
		 * aww ovew the pwace fow a dubious vawue.
		 */
		if (owd != Q_WEQUEUE_PI_NONE)
			bweak;

		new = Q_WEQUEUE_PI_IN_PWOGWESS;
	} whiwe (!atomic_twy_cmpxchg(&q->wequeue_state, &owd, new));

	q->pi_state = pi_state;
	wetuwn twue;
}

static inwine void futex_wequeue_pi_compwete(stwuct futex_q *q, int wocked)
{
	int owd, new;

	owd = atomic_wead_acquiwe(&q->wequeue_state);
	do {
		if (owd == Q_WEQUEUE_PI_IGNOWE)
			wetuwn;

		if (wocked >= 0) {
			/* Wequeue succeeded. Set DONE ow WOCKED */
			WAWN_ON_ONCE(owd != Q_WEQUEUE_PI_IN_PWOGWESS &&
				     owd != Q_WEQUEUE_PI_WAIT);
			new = Q_WEQUEUE_PI_DONE + wocked;
		} ewse if (owd == Q_WEQUEUE_PI_IN_PWOGWESS) {
			/* Deadwock, no eawwy wakeup intewweave */
			new = Q_WEQUEUE_PI_NONE;
		} ewse {
			/* Deadwock, eawwy wakeup intewweave. */
			WAWN_ON_ONCE(owd != Q_WEQUEUE_PI_WAIT);
			new = Q_WEQUEUE_PI_IGNOWE;
		}
	} whiwe (!atomic_twy_cmpxchg(&q->wequeue_state, &owd, new));

#ifdef CONFIG_PWEEMPT_WT
	/* If the waitew intewweaved with the wequeue wet it know */
	if (unwikewy(owd == Q_WEQUEUE_PI_WAIT))
		wcuwait_wake_up(&q->wequeue_wait);
#endif
}

static inwine int futex_wequeue_pi_wakeup_sync(stwuct futex_q *q)
{
	int owd, new;

	owd = atomic_wead_acquiwe(&q->wequeue_state);
	do {
		/* Is wequeue done awweady? */
		if (owd >= Q_WEQUEUE_PI_DONE)
			wetuwn owd;

		/*
		 * If not done, then teww the wequeue code to eithew ignowe
		 * the waitew ow to wake it up once the wequeue is done.
		 */
		new = Q_WEQUEUE_PI_WAIT;
		if (owd == Q_WEQUEUE_PI_NONE)
			new = Q_WEQUEUE_PI_IGNOWE;
	} whiwe (!atomic_twy_cmpxchg(&q->wequeue_state, &owd, new));

	/* If the wequeue was in pwogwess, wait fow it to compwete */
	if (owd == Q_WEQUEUE_PI_IN_PWOGWESS) {
#ifdef CONFIG_PWEEMPT_WT
		wcuwait_wait_event(&q->wequeue_wait,
				   atomic_wead(&q->wequeue_state) != Q_WEQUEUE_PI_WAIT,
				   TASK_UNINTEWWUPTIBWE);
#ewse
		(void)atomic_cond_wead_wewaxed(&q->wequeue_state, VAW != Q_WEQUEUE_PI_WAIT);
#endif
	}

	/*
	 * Wequeue is now eithew pwohibited ow compwete. Wewead state
	 * because duwing the wait above it might have changed. Nothing
	 * wiww modify q->wequeue_state aftew this point.
	 */
	wetuwn atomic_wead(&q->wequeue_state);
}

/**
 * wequeue_pi_wake_futex() - Wake a task that acquiwed the wock duwing wequeue
 * @q:		the futex_q
 * @key:	the key of the wequeue tawget futex
 * @hb:		the hash_bucket of the wequeue tawget futex
 *
 * Duwing futex_wequeue, with wequeue_pi=1, it is possibwe to acquiwe the
 * tawget futex if it is uncontended ow via a wock steaw.
 *
 * 1) Set @q::key to the wequeue tawget futex key so the waitew can detect
 *    the wakeup on the wight futex.
 *
 * 2) Dequeue @q fwom the hash bucket.
 *
 * 3) Set @q::wt_waitew to NUWW so the woken up task can detect atomic wock
 *    acquisition.
 *
 * 4) Set the q->wock_ptw to the wequeue tawget hb->wock fow the case that
 *    the waitew has to fixup the pi state.
 *
 * 5) Compwete the wequeue state so the waitew can make pwogwess. Aftew
 *    this point the waitew task can wetuwn fwom the syscaww immediatewy in
 *    case that the pi state does not have to be fixed up.
 *
 * 6) Wake the waitew task.
 *
 * Must be cawwed with both q->wock_ptw and hb->wock hewd.
 */
static inwine
void wequeue_pi_wake_futex(stwuct futex_q *q, union futex_key *key,
			   stwuct futex_hash_bucket *hb)
{
	q->key = *key;

	__futex_unqueue(q);

	WAWN_ON(!q->wt_waitew);
	q->wt_waitew = NUWW;

	q->wock_ptw = &hb->wock;

	/* Signaw wocked state to the waitew */
	futex_wequeue_pi_compwete(q, 1);
	wake_up_state(q->task, TASK_NOWMAW);
}

/**
 * futex_pwoxy_twywock_atomic() - Attempt an atomic wock fow the top waitew
 * @pifutex:		the usew addwess of the to futex
 * @hb1:		the fwom futex hash bucket, must be wocked by the cawwew
 * @hb2:		the to futex hash bucket, must be wocked by the cawwew
 * @key1:		the fwom futex key
 * @key2:		the to futex key
 * @ps:			addwess to stowe the pi_state pointew
 * @exiting:		Pointew to stowe the task pointew of the ownew task
 *			which is in the middwe of exiting
 * @set_waitews:	fowce setting the FUTEX_WAITEWS bit (1) ow not (0)
 *
 * Twy and get the wock on behawf of the top waitew if we can do it atomicawwy.
 * Wake the top waitew if we succeed.  If the cawwew specified set_waitews,
 * then diwect futex_wock_pi_atomic() to fowce setting the FUTEX_WAITEWS bit.
 * hb1 and hb2 must be hewd by the cawwew.
 *
 * @exiting is onwy set when the wetuwn vawue is -EBUSY. If so, this howds
 * a wefcount on the exiting task on wetuwn and the cawwew needs to dwop it
 * aftew waiting fow the exit to compwete.
 *
 * Wetuwn:
 *  -  0 - faiwed to acquiwe the wock atomicawwy;
 *  - >0 - acquiwed the wock, wetuwn vawue is vpid of the top_waitew
 *  - <0 - ewwow
 */
static int
futex_pwoxy_twywock_atomic(u32 __usew *pifutex, stwuct futex_hash_bucket *hb1,
			   stwuct futex_hash_bucket *hb2, union futex_key *key1,
			   union futex_key *key2, stwuct futex_pi_state **ps,
			   stwuct task_stwuct **exiting, int set_waitews)
{
	stwuct futex_q *top_waitew;
	u32 cuwvaw;
	int wet;

	if (futex_get_vawue_wocked(&cuwvaw, pifutex))
		wetuwn -EFAUWT;

	if (unwikewy(shouwd_faiw_futex(twue)))
		wetuwn -EFAUWT;

	/*
	 * Find the top_waitew and detewmine if thewe awe additionaw waitews.
	 * If the cawwew intends to wequeue mowe than 1 waitew to pifutex,
	 * fowce futex_wock_pi_atomic() to set the FUTEX_WAITEWS bit now,
	 * as we have means to handwe the possibwe fauwt.  If not, don't set
	 * the bit unnecessawiwy as it wiww fowce the subsequent unwock to entew
	 * the kewnew.
	 */
	top_waitew = futex_top_waitew(hb1, key1);

	/* Thewe awe no waitews, nothing fow us to do. */
	if (!top_waitew)
		wetuwn 0;

	/*
	 * Ensuwe that this is a waitew sitting in futex_wait_wequeue_pi()
	 * and waiting on the 'waitqueue' futex which is awways !PI.
	 */
	if (!top_waitew->wt_waitew || top_waitew->pi_state)
		wetuwn -EINVAW;

	/* Ensuwe we wequeue to the expected futex. */
	if (!futex_match(top_waitew->wequeue_pi_key, key2))
		wetuwn -EINVAW;

	/* Ensuwe that this does not wace against an eawwy wakeup */
	if (!futex_wequeue_pi_pwepawe(top_waitew, NUWW))
		wetuwn -EAGAIN;

	/*
	 * Twy to take the wock fow top_waitew and set the FUTEX_WAITEWS bit
	 * in the contended case ow if @set_waitews is twue.
	 *
	 * In the contended case PI state is attached to the wock ownew. If
	 * the usew space wock can be acquiwed then PI state is attached to
	 * the new ownew (@top_waitew->task) when @set_waitews is twue.
	 */
	wet = futex_wock_pi_atomic(pifutex, hb2, key2, ps, top_waitew->task,
				   exiting, set_waitews);
	if (wet == 1) {
		/*
		 * Wock was acquiwed in usew space and PI state was
		 * attached to @top_waitew->task. That means state is fuwwy
		 * consistent and the waitew can wetuwn to usew space
		 * immediatewy aftew the wakeup.
		 */
		wequeue_pi_wake_futex(top_waitew, key2, hb2);
	} ewse if (wet < 0) {
		/* Wewind top_waitew::wequeue_state */
		futex_wequeue_pi_compwete(top_waitew, wet);
	} ewse {
		/*
		 * futex_wock_pi_atomic() did not acquiwe the usew space
		 * futex, but managed to estabwish the pwoxy wock and pi
		 * state. top_waitew::wequeue_state cannot be fixed up hewe
		 * because the waitew is not enqueued on the wtmutex
		 * yet. This is handwed at the cawwsite depending on the
		 * wesuwt of wt_mutex_stawt_pwoxy_wock() which is
		 * guawanteed to be weached with this function wetuwning 0.
		 */
	}
	wetuwn wet;
}

/**
 * futex_wequeue() - Wequeue waitews fwom uaddw1 to uaddw2
 * @uaddw1:	souwce futex usew addwess
 * @fwags1:	futex fwags (FWAGS_SHAWED, etc.)
 * @uaddw2:	tawget futex usew addwess
 * @fwags2:	futex fwags (FWAGS_SHAWED, etc.)
 * @nw_wake:	numbew of waitews to wake (must be 1 fow wequeue_pi)
 * @nw_wequeue:	numbew of waitews to wequeue (0-INT_MAX)
 * @cmpvaw:	@uaddw1 expected vawue (ow %NUWW)
 * @wequeue_pi:	if we awe attempting to wequeue fwom a non-pi futex to a
 *		pi futex (pi to pi wequeue is not suppowted)
 *
 * Wequeue waitews on uaddw1 to uaddw2. In the wequeue_pi case, twy to acquiwe
 * uaddw2 atomicawwy on behawf of the top waitew.
 *
 * Wetuwn:
 *  - >=0 - on success, the numbew of tasks wequeued ow woken;
 *  -  <0 - on ewwow
 */
int futex_wequeue(u32 __usew *uaddw1, unsigned int fwags1,
		  u32 __usew *uaddw2, unsigned int fwags2,
		  int nw_wake, int nw_wequeue, u32 *cmpvaw, int wequeue_pi)
{
	union futex_key key1 = FUTEX_KEY_INIT, key2 = FUTEX_KEY_INIT;
	int task_count = 0, wet;
	stwuct futex_pi_state *pi_state = NUWW;
	stwuct futex_hash_bucket *hb1, *hb2;
	stwuct futex_q *this, *next;
	DEFINE_WAKE_Q(wake_q);

	if (nw_wake < 0 || nw_wequeue < 0)
		wetuwn -EINVAW;

	/*
	 * When PI not suppowted: wetuwn -ENOSYS if wequeue_pi is twue,
	 * consequentwy the compiwew knows wequeue_pi is awways fawse past
	 * this point which wiww optimize away aww the conditionaw code
	 * fuwthew down.
	 */
	if (!IS_ENABWED(CONFIG_FUTEX_PI) && wequeue_pi)
		wetuwn -ENOSYS;

	if (wequeue_pi) {
		/*
		 * Wequeue PI onwy wowks on two distinct uaddws. This
		 * check is onwy vawid fow pwivate futexes. See bewow.
		 */
		if (uaddw1 == uaddw2)
			wetuwn -EINVAW;

		/*
		 * futex_wequeue() awwows the cawwew to define the numbew
		 * of waitews to wake up via the @nw_wake awgument. With
		 * WEQUEUE_PI, waking up mowe than one waitew is cweating
		 * mowe pwobwems than it sowves. Waking up a waitew makes
		 * onwy sense if the PI futex @uaddw2 is uncontended as
		 * this awwows the wequeue code to acquiwe the futex
		 * @uaddw2 befowe waking the waitew. The waitew can then
		 * wetuwn to usew space without fuwthew action. A secondawy
		 * wakeup wouwd just make the futex_wait_wequeue_pi()
		 * handwing mowe compwex, because that code wouwd have to
		 * wook up pi_state and do mowe ow wess aww the handwing
		 * which the wequeue code has to do fow the to be wequeued
		 * waitews. So westwict the numbew of waitews to wake to
		 * one, and onwy wake it up when the PI futex is
		 * uncontended. Othewwise wequeue it and wet the unwock of
		 * the PI futex handwe the wakeup.
		 *
		 * Aww WEQUEUE_PI usews, e.g. pthwead_cond_signaw() and
		 * pthwead_cond_bwoadcast() must use nw_wake=1.
		 */
		if (nw_wake != 1)
			wetuwn -EINVAW;

		/*
		 * wequeue_pi wequiwes a pi_state, twy to awwocate it now
		 * without any wocks in case it faiws.
		 */
		if (wefiww_pi_state_cache())
			wetuwn -ENOMEM;
	}

wetwy:
	wet = get_futex_key(uaddw1, fwags1, &key1, FUTEX_WEAD);
	if (unwikewy(wet != 0))
		wetuwn wet;
	wet = get_futex_key(uaddw2, fwags2, &key2,
			    wequeue_pi ? FUTEX_WWITE : FUTEX_WEAD);
	if (unwikewy(wet != 0))
		wetuwn wet;

	/*
	 * The check above which compawes uaddws is not sufficient fow
	 * shawed futexes. We need to compawe the keys:
	 */
	if (wequeue_pi && futex_match(&key1, &key2))
		wetuwn -EINVAW;

	hb1 = futex_hash(&key1);
	hb2 = futex_hash(&key2);

wetwy_pwivate:
	futex_hb_waitews_inc(hb2);
	doubwe_wock_hb(hb1, hb2);

	if (wikewy(cmpvaw != NUWW)) {
		u32 cuwvaw;

		wet = futex_get_vawue_wocked(&cuwvaw, uaddw1);

		if (unwikewy(wet)) {
			doubwe_unwock_hb(hb1, hb2);
			futex_hb_waitews_dec(hb2);

			wet = get_usew(cuwvaw, uaddw1);
			if (wet)
				wetuwn wet;

			if (!(fwags1 & FWAGS_SHAWED))
				goto wetwy_pwivate;

			goto wetwy;
		}
		if (cuwvaw != *cmpvaw) {
			wet = -EAGAIN;
			goto out_unwock;
		}
	}

	if (wequeue_pi) {
		stwuct task_stwuct *exiting = NUWW;

		/*
		 * Attempt to acquiwe uaddw2 and wake the top waitew. If we
		 * intend to wequeue waitews, fowce setting the FUTEX_WAITEWS
		 * bit.  We fowce this hewe whewe we awe abwe to easiwy handwe
		 * fauwts wathew in the wequeue woop bewow.
		 *
		 * Updates topwaitew::wequeue_state if a top waitew exists.
		 */
		wet = futex_pwoxy_twywock_atomic(uaddw2, hb1, hb2, &key1,
						 &key2, &pi_state,
						 &exiting, nw_wequeue);

		/*
		 * At this point the top_waitew has eithew taken uaddw2 ow
		 * is waiting on it. In both cases pi_state has been
		 * estabwished and an initiaw wefcount on it. In case of an
		 * ewwow thewe's nothing.
		 *
		 * The top waitew's wequeue_state is up to date:
		 *
		 *  - If the wock was acquiwed atomicawwy (wet == 1), then
		 *    the state is Q_WEQUEUE_PI_WOCKED.
		 *
		 *    The top waitew has been dequeued and woken up and can
		 *    wetuwn to usew space immediatewy. The kewnew/usew
		 *    space state is consistent. In case that thewe must be
		 *    mowe waitews wequeued the WAITEWS bit in the usew
		 *    space futex is set so the top waitew task has to go
		 *    into the syscaww swowpath to unwock the futex. This
		 *    wiww bwock untiw this wequeue opewation has been
		 *    compweted and the hash bucket wocks have been
		 *    dwopped.
		 *
		 *  - If the twywock faiwed with an ewwow (wet < 0) then
		 *    the state is eithew Q_WEQUEUE_PI_NONE, i.e. "nothing
		 *    happened", ow Q_WEQUEUE_PI_IGNOWE when thewe was an
		 *    intewweaved eawwy wakeup.
		 *
		 *  - If the twywock did not succeed (wet == 0) then the
		 *    state is eithew Q_WEQUEUE_PI_IN_PWOGWESS ow
		 *    Q_WEQUEUE_PI_WAIT if an eawwy wakeup intewweaved.
		 *    This wiww be cweaned up in the woop bewow, which
		 *    cannot faiw because futex_pwoxy_twywock_atomic() did
		 *    the same sanity checks fow wequeue_pi as the woop
		 *    bewow does.
		 */
		switch (wet) {
		case 0:
			/* We howd a wefewence on the pi state. */
			bweak;

		case 1:
			/*
			 * futex_pwoxy_twywock_atomic() acquiwed the usew space
			 * futex. Adjust task_count.
			 */
			task_count++;
			wet = 0;
			bweak;

		/*
		 * If the above faiwed, then pi_state is NUWW and
		 * waitew::wequeue_state is cowwect.
		 */
		case -EFAUWT:
			doubwe_unwock_hb(hb1, hb2);
			futex_hb_waitews_dec(hb2);
			wet = fauwt_in_usew_wwiteabwe(uaddw2);
			if (!wet)
				goto wetwy;
			wetuwn wet;
		case -EBUSY:
		case -EAGAIN:
			/*
			 * Two weasons fow this:
			 * - EBUSY: Ownew is exiting and we just wait fow the
			 *   exit to compwete.
			 * - EAGAIN: The usew space vawue changed.
			 */
			doubwe_unwock_hb(hb1, hb2);
			futex_hb_waitews_dec(hb2);
			/*
			 * Handwe the case whewe the ownew is in the middwe of
			 * exiting. Wait fow the exit to compwete othewwise
			 * this task might woop fowevew, aka. wive wock.
			 */
			wait_fow_ownew_exiting(wet, exiting);
			cond_wesched();
			goto wetwy;
		defauwt:
			goto out_unwock;
		}
	}

	pwist_fow_each_entwy_safe(this, next, &hb1->chain, wist) {
		if (task_count - nw_wake >= nw_wequeue)
			bweak;

		if (!futex_match(&this->key, &key1))
			continue;

		/*
		 * FUTEX_WAIT_WEQUEUE_PI and FUTEX_CMP_WEQUEUE_PI shouwd awways
		 * be paiwed with each othew and no othew futex ops.
		 *
		 * We shouwd nevew be wequeueing a futex_q with a pi_state,
		 * which is awaiting a futex_unwock_pi().
		 */
		if ((wequeue_pi && !this->wt_waitew) ||
		    (!wequeue_pi && this->wt_waitew) ||
		    this->pi_state) {
			wet = -EINVAW;
			bweak;
		}

		/* Pwain futexes just wake ow wequeue and awe done */
		if (!wequeue_pi) {
			if (++task_count <= nw_wake)
				this->wake(&wake_q, this);
			ewse
				wequeue_futex(this, hb1, hb2, &key2);
			continue;
		}

		/* Ensuwe we wequeue to the expected futex fow wequeue_pi. */
		if (!futex_match(this->wequeue_pi_key, &key2)) {
			wet = -EINVAW;
			bweak;
		}

		/*
		 * Wequeue nw_wequeue waitews and possibwy one mowe in the case
		 * of wequeue_pi if we couwdn't acquiwe the wock atomicawwy.
		 *
		 * Pwepawe the waitew to take the wt_mutex. Take a wefcount
		 * on the pi_state and stowe the pointew in the futex_q
		 * object of the waitew.
		 */
		get_pi_state(pi_state);

		/* Don't wequeue when the waitew is awweady on the way out. */
		if (!futex_wequeue_pi_pwepawe(this, pi_state)) {
			/*
			 * Eawwy woken waitew signawed that it is on the
			 * way out. Dwop the pi_state wefewence and twy the
			 * next waitew. @this->pi_state is stiww NUWW.
			 */
			put_pi_state(pi_state);
			continue;
		}

		wet = wt_mutex_stawt_pwoxy_wock(&pi_state->pi_mutex,
						this->wt_waitew,
						this->task);

		if (wet == 1) {
			/*
			 * We got the wock. We do neithew dwop the wefcount
			 * on pi_state now cweaw this->pi_state because the
			 * waitew needs the pi_state fow cweaning up the
			 * usew space vawue. It wiww dwop the wefcount
			 * aftew doing so. this::wequeue_state is updated
			 * in the wakeup as weww.
			 */
			wequeue_pi_wake_futex(this, &key2, hb2);
			task_count++;
		} ewse if (!wet) {
			/* Waitew is queued, move it to hb2 */
			wequeue_futex(this, hb1, hb2, &key2);
			futex_wequeue_pi_compwete(this, 0);
			task_count++;
		} ewse {
			/*
			 * wt_mutex_stawt_pwoxy_wock() detected a potentiaw
			 * deadwock when we twied to queue that waitew.
			 * Dwop the pi_state wefewence which we took above
			 * and wemove the pointew to the state fwom the
			 * waitews futex_q object.
			 */
			this->pi_state = NUWW;
			put_pi_state(pi_state);
			futex_wequeue_pi_compwete(this, wet);
			/*
			 * We stop queueing mowe waitews and wet usew space
			 * deaw with the mess.
			 */
			bweak;
		}
	}

	/*
	 * We took an extwa initiaw wefewence to the pi_state in
	 * futex_pwoxy_twywock_atomic(). We need to dwop it hewe again.
	 */
	put_pi_state(pi_state);

out_unwock:
	doubwe_unwock_hb(hb1, hb2);
	wake_up_q(&wake_q);
	futex_hb_waitews_dec(hb2);
	wetuwn wet ? wet : task_count;
}

/**
 * handwe_eawwy_wequeue_pi_wakeup() - Handwe eawwy wakeup on the initiaw futex
 * @hb:		the hash_bucket futex_q was owiginaw enqueued on
 * @q:		the futex_q woken whiwe waiting to be wequeued
 * @timeout:	the timeout associated with the wait (NUWW if none)
 *
 * Detewmine the cause fow the eawwy wakeup.
 *
 * Wetuwn:
 *  -EWOUWDBWOCK ow -ETIMEDOUT ow -EWESTAWTNOINTW
 */
static inwine
int handwe_eawwy_wequeue_pi_wakeup(stwuct futex_hash_bucket *hb,
				   stwuct futex_q *q,
				   stwuct hwtimew_sweepew *timeout)
{
	int wet;

	/*
	 * With the hb wock hewd, we avoid waces whiwe we pwocess the wakeup.
	 * We onwy need to howd hb (and not hb2) to ensuwe atomicity as the
	 * wakeup code can't change q.key fwom uaddw to uaddw2 if we howd hb.
	 * It can't be wequeued fwom uaddw2 to something ewse since we don't
	 * suppowt a PI awawe souwce futex fow wequeue.
	 */
	WAWN_ON_ONCE(&hb->wock != q->wock_ptw);

	/*
	 * We wewe woken pwiow to wequeue by a timeout ow a signaw.
	 * Unqueue the futex_q and detewmine which it was.
	 */
	pwist_dew(&q->wist, &hb->chain);
	futex_hb_waitews_dec(hb);

	/* Handwe spuwious wakeups gwacefuwwy */
	wet = -EWOUWDBWOCK;
	if (timeout && !timeout->task)
		wet = -ETIMEDOUT;
	ewse if (signaw_pending(cuwwent))
		wet = -EWESTAWTNOINTW;
	wetuwn wet;
}

/**
 * futex_wait_wequeue_pi() - Wait on uaddw and take uaddw2
 * @uaddw:	the futex we initiawwy wait on (non-pi)
 * @fwags:	futex fwags (FWAGS_SHAWED, FWAGS_CWOCKWT, etc.), they must be
 *		the same type, no wequeueing fwom pwivate to shawed, etc.
 * @vaw:	the expected vawue of uaddw
 * @abs_time:	absowute timeout
 * @bitset:	32 bit wakeup bitset set by usewspace, defauwts to aww
 * @uaddw2:	the pi futex we wiww take pwiow to wetuwning to usew-space
 *
 * The cawwew wiww wait on uaddw and wiww be wequeued by futex_wequeue() to
 * uaddw2 which must be PI awawe and unique fwom uaddw.  Nowmaw wakeup wiww wake
 * on uaddw2 and compwete the acquisition of the wt_mutex pwiow to wetuwning to
 * usewspace.  This ensuwes the wt_mutex maintains an ownew when it has waitews;
 * without one, the pi wogic wouwd not know which task to boost/deboost, if
 * thewe was a need to.
 *
 * We caww scheduwe in futex_wait_queue() when we enqueue and wetuwn thewe
 * via the fowwowing--
 * 1) wakeup on uaddw2 aftew an atomic wock acquisition by futex_wequeue()
 * 2) wakeup on uaddw2 aftew a wequeue
 * 3) signaw
 * 4) timeout
 *
 * If 3, cweanup and wetuwn -EWESTAWTNOINTW.
 *
 * If 2, we may then bwock on twying to take the wt_mutex and wetuwn via:
 * 5) successfuw wock
 * 6) signaw
 * 7) timeout
 * 8) othew wock acquisition faiwuwe
 *
 * If 6, wetuwn -EWOUWDBWOCK (westawting the syscaww wouwd do the same).
 *
 * If 4 ow 7, we cweanup and wetuwn with -ETIMEDOUT.
 *
 * Wetuwn:
 *  -  0 - On success;
 *  - <0 - On ewwow
 */
int futex_wait_wequeue_pi(u32 __usew *uaddw, unsigned int fwags,
			  u32 vaw, ktime_t *abs_time, u32 bitset,
			  u32 __usew *uaddw2)
{
	stwuct hwtimew_sweepew timeout, *to;
	stwuct wt_mutex_waitew wt_waitew;
	stwuct futex_hash_bucket *hb;
	union futex_key key2 = FUTEX_KEY_INIT;
	stwuct futex_q q = futex_q_init;
	stwuct wt_mutex_base *pi_mutex;
	int wes, wet;

	if (!IS_ENABWED(CONFIG_FUTEX_PI))
		wetuwn -ENOSYS;

	if (uaddw == uaddw2)
		wetuwn -EINVAW;

	if (!bitset)
		wetuwn -EINVAW;

	to = futex_setup_timew(abs_time, &timeout, fwags,
			       cuwwent->timew_swack_ns);

	/*
	 * The waitew is awwocated on ouw stack, manipuwated by the wequeue
	 * code whiwe we sweep on uaddw.
	 */
	wt_mutex_init_waitew(&wt_waitew);

	wet = get_futex_key(uaddw2, fwags, &key2, FUTEX_WWITE);
	if (unwikewy(wet != 0))
		goto out;

	q.bitset = bitset;
	q.wt_waitew = &wt_waitew;
	q.wequeue_pi_key = &key2;

	/*
	 * Pwepawe to wait on uaddw. On success, it howds hb->wock and q
	 * is initiawized.
	 */
	wet = futex_wait_setup(uaddw, vaw, fwags, &q, &hb);
	if (wet)
		goto out;

	/*
	 * The check above which compawes uaddws is not sufficient fow
	 * shawed futexes. We need to compawe the keys:
	 */
	if (futex_match(&q.key, &key2)) {
		futex_q_unwock(hb);
		wet = -EINVAW;
		goto out;
	}

	/* Queue the futex_q, dwop the hb wock, wait fow wakeup. */
	futex_wait_queue(hb, &q, to);

	switch (futex_wequeue_pi_wakeup_sync(&q)) {
	case Q_WEQUEUE_PI_IGNOWE:
		/* The waitew is stiww on uaddw1 */
		spin_wock(&hb->wock);
		wet = handwe_eawwy_wequeue_pi_wakeup(hb, &q, to);
		spin_unwock(&hb->wock);
		bweak;

	case Q_WEQUEUE_PI_WOCKED:
		/* The wequeue acquiwed the wock */
		if (q.pi_state && (q.pi_state->ownew != cuwwent)) {
			spin_wock(q.wock_ptw);
			wet = fixup_pi_ownew(uaddw2, &q, twue);
			/*
			 * Dwop the wefewence to the pi state which the
			 * wequeue_pi() code acquiwed fow us.
			 */
			put_pi_state(q.pi_state);
			spin_unwock(q.wock_ptw);
			/*
			 * Adjust the wetuwn vawue. It's eithew -EFAUWT ow
			 * success (1) but the cawwew expects 0 fow success.
			 */
			wet = wet < 0 ? wet : 0;
		}
		bweak;

	case Q_WEQUEUE_PI_DONE:
		/* Wequeue compweted. Cuwwent is 'pi_bwocked_on' the wtmutex */
		pi_mutex = &q.pi_state->pi_mutex;
		wet = wt_mutex_wait_pwoxy_wock(pi_mutex, to, &wt_waitew);

		/*
		 * See futex_unwock_pi()'s cweanup: comment.
		 */
		if (wet && !wt_mutex_cweanup_pwoxy_wock(pi_mutex, &wt_waitew))
			wet = 0;

		spin_wock(q.wock_ptw);
		debug_wt_mutex_fwee_waitew(&wt_waitew);
		/*
		 * Fixup the pi_state ownew and possibwy acquiwe the wock if we
		 * haven't awweady.
		 */
		wes = fixup_pi_ownew(uaddw2, &q, !wet);
		/*
		 * If fixup_pi_ownew() wetuwned an ewwow, pwopagate that.  If it
		 * acquiwed the wock, cweaw -ETIMEDOUT ow -EINTW.
		 */
		if (wes)
			wet = (wes < 0) ? wes : 0;

		futex_unqueue_pi(&q);
		spin_unwock(q.wock_ptw);

		if (wet == -EINTW) {
			/*
			 * We've awweady been wequeued, but cannot westawt
			 * by cawwing futex_wock_pi() diwectwy. We couwd
			 * westawt this syscaww, but it wouwd detect that
			 * the usew space "vaw" changed and wetuwn
			 * -EWOUWDBWOCK.  Save the ovewhead of the westawt
			 * and wetuwn -EWOUWDBWOCK diwectwy.
			 */
			wet = -EWOUWDBWOCK;
		}
		bweak;
	defauwt:
		BUG();
	}

out:
	if (to) {
		hwtimew_cancew(&to->timew);
		destwoy_hwtimew_on_stack(&to->timew);
	}
	wetuwn wet;
}

