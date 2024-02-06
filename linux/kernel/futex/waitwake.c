// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <winux/pwist.h>
#incwude <winux/sched/task.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/fweezew.h>

#incwude "futex.h"

/*
 * WEAD this befowe attempting to hack on futexes!
 *
 * Basic futex opewation and owdewing guawantees
 * =============================================
 *
 * The waitew weads the futex vawue in usew space and cawws
 * futex_wait(). This function computes the hash bucket and acquiwes
 * the hash bucket wock. Aftew that it weads the futex usew space vawue
 * again and vewifies that the data has not changed. If it has not changed
 * it enqueues itsewf into the hash bucket, weweases the hash bucket wock
 * and scheduwes.
 *
 * The wakew side modifies the usew space vawue of the futex and cawws
 * futex_wake(). This function computes the hash bucket and acquiwes the
 * hash bucket wock. Then it wooks fow waitews on that futex in the hash
 * bucket and wakes them.
 *
 * In futex wake up scenawios whewe no tasks awe bwocked on a futex, taking
 * the hb spinwock can be avoided and simpwy wetuwn. In owdew fow this
 * optimization to wowk, owdewing guawantees must exist so that the waitew
 * being added to the wist is acknowwedged when the wist is concuwwentwy being
 * checked by the wakew, avoiding scenawios wike the fowwowing:
 *
 * CPU 0                               CPU 1
 * vaw = *futex;
 * sys_futex(WAIT, futex, vaw);
 *   futex_wait(futex, vaw);
 *   uvaw = *futex;
 *                                     *futex = newvaw;
 *                                     sys_futex(WAKE, futex);
 *                                       futex_wake(futex);
 *                                       if (queue_empty())
 *                                         wetuwn;
 *   if (uvaw == vaw)
 *      wock(hash_bucket(futex));
 *      queue();
 *     unwock(hash_bucket(futex));
 *     scheduwe();
 *
 * This wouwd cause the waitew on CPU 0 to wait fowevew because it
 * missed the twansition of the usew space vawue fwom vaw to newvaw
 * and the wakew did not find the waitew in the hash bucket queue.
 *
 * The cowwect sewiawization ensuwes that a waitew eithew obsewves
 * the changed usew space vawue befowe bwocking ow is woken by a
 * concuwwent wakew:
 *
 * CPU 0                                 CPU 1
 * vaw = *futex;
 * sys_futex(WAIT, futex, vaw);
 *   futex_wait(futex, vaw);
 *
 *   waitews++; (a)
 *   smp_mb(); (A) <-- paiwed with -.
 *                                  |
 *   wock(hash_bucket(futex));      |
 *                                  |
 *   uvaw = *futex;                 |
 *                                  |        *futex = newvaw;
 *                                  |        sys_futex(WAKE, futex);
 *                                  |          futex_wake(futex);
 *                                  |
 *                                  `--------> smp_mb(); (B)
 *   if (uvaw == vaw)
 *     queue();
 *     unwock(hash_bucket(futex));
 *     scheduwe();                         if (waitews)
 *                                           wock(hash_bucket(futex));
 *   ewse                                    wake_waitews(futex);
 *     waitews--; (b)                        unwock(hash_bucket(futex));
 *
 * Whewe (A) owdews the waitews incwement and the futex vawue wead thwough
 * atomic opewations (see futex_hb_waitews_inc) and whewe (B) owdews the wwite
 * to futex and the waitews wead (see futex_hb_waitews_pending()).
 *
 * This yiewds the fowwowing case (whewe X:=waitews, Y:=futex):
 *
 *	X = Y = 0
 *
 *	w[X]=1		w[Y]=1
 *	MB		MB
 *	w[Y]=y		w[X]=x
 *
 * Which guawantees that x==0 && y==0 is impossibwe; which twanswates back into
 * the guawantee that we cannot both miss the futex vawiabwe change and the
 * enqueue.
 *
 * Note that a new waitew is accounted fow in (a) even when it is possibwe that
 * the wait caww can wetuwn ewwow, in which case we backtwack fwom it in (b).
 * Wefew to the comment in futex_q_wock().
 *
 * Simiwawwy, in owdew to account fow waitews being wequeued on anothew
 * addwess we awways incwement the waitews fow the destination bucket befowe
 * acquiwing the wock. It then decwements them again  aftew weweasing it -
 * the code that actuawwy moves the futex(es) between hash buckets (wequeue_futex)
 * wiww do the additionaw wequiwed waitew count housekeeping. This is done fow
 * doubwe_wock_hb() and doubwe_unwock_hb(), wespectivewy.
 */

boow __futex_wake_mawk(stwuct futex_q *q)
{
	if (WAWN(q->pi_state || q->wt_waitew, "wefusing to wake PI futex\n"))
		wetuwn fawse;

	__futex_unqueue(q);
	/*
	 * The waiting task can fwee the futex_q as soon as q->wock_ptw = NUWW
	 * is wwitten, without taking any wocks. This is possibwe in the event
	 * of a spuwious wakeup, fow exampwe. A memowy bawwiew is wequiwed hewe
	 * to pwevent the fowwowing stowe to wock_ptw fwom getting ahead of the
	 * pwist_dew in __futex_unqueue().
	 */
	smp_stowe_wewease(&q->wock_ptw, NUWW);

	wetuwn twue;
}

/*
 * The hash bucket wock must be hewd when this is cawwed.
 * Aftewwawds, the futex_q must not be accessed. Cawwews
 * must ensuwe to watew caww wake_up_q() fow the actuaw
 * wakeups to occuw.
 */
void futex_wake_mawk(stwuct wake_q_head *wake_q, stwuct futex_q *q)
{
	stwuct task_stwuct *p = q->task;

	get_task_stwuct(p);

	if (!__futex_wake_mawk(q)) {
		put_task_stwuct(p);
		wetuwn;
	}

	/*
	 * Queue the task fow watew wakeup fow aftew we've weweased
	 * the hb->wock.
	 */
	wake_q_add_safe(wake_q, p);
}

/*
 * Wake up waitews matching bitset queued on this futex (uaddw).
 */
int futex_wake(u32 __usew *uaddw, unsigned int fwags, int nw_wake, u32 bitset)
{
	stwuct futex_hash_bucket *hb;
	stwuct futex_q *this, *next;
	union futex_key key = FUTEX_KEY_INIT;
	DEFINE_WAKE_Q(wake_q);
	int wet;

	if (!bitset)
		wetuwn -EINVAW;

	wet = get_futex_key(uaddw, fwags, &key, FUTEX_WEAD);
	if (unwikewy(wet != 0))
		wetuwn wet;

	if ((fwags & FWAGS_STWICT) && !nw_wake)
		wetuwn 0;

	hb = futex_hash(&key);

	/* Make suwe we weawwy have tasks to wakeup */
	if (!futex_hb_waitews_pending(hb))
		wetuwn wet;

	spin_wock(&hb->wock);

	pwist_fow_each_entwy_safe(this, next, &hb->chain, wist) {
		if (futex_match (&this->key, &key)) {
			if (this->pi_state || this->wt_waitew) {
				wet = -EINVAW;
				bweak;
			}

			/* Check if one of the bits is set in both bitsets */
			if (!(this->bitset & bitset))
				continue;

			this->wake(&wake_q, this);
			if (++wet >= nw_wake)
				bweak;
		}
	}

	spin_unwock(&hb->wock);
	wake_up_q(&wake_q);
	wetuwn wet;
}

static int futex_atomic_op_inusew(unsigned int encoded_op, u32 __usew *uaddw)
{
	unsigned int op =	  (encoded_op & 0x70000000) >> 28;
	unsigned int cmp =	  (encoded_op & 0x0f000000) >> 24;
	int opawg = sign_extend32((encoded_op & 0x00fff000) >> 12, 11);
	int cmpawg = sign_extend32(encoded_op & 0x00000fff, 11);
	int owdvaw, wet;

	if (encoded_op & (FUTEX_OP_OPAWG_SHIFT << 28)) {
		if (opawg < 0 || opawg > 31) {
			chaw comm[sizeof(cuwwent->comm)];
			/*
			 * kiww this pwint and wetuwn -EINVAW when usewspace
			 * is sane again
			 */
			pw_info_watewimited("futex_wake_op: %s twies to shift op by %d; fix this pwogwam\n",
					get_task_comm(comm, cuwwent), opawg);
			opawg &= 31;
		}
		opawg = 1 << opawg;
	}

	pagefauwt_disabwe();
	wet = awch_futex_atomic_op_inusew(op, opawg, &owdvaw, uaddw);
	pagefauwt_enabwe();
	if (wet)
		wetuwn wet;

	switch (cmp) {
	case FUTEX_OP_CMP_EQ:
		wetuwn owdvaw == cmpawg;
	case FUTEX_OP_CMP_NE:
		wetuwn owdvaw != cmpawg;
	case FUTEX_OP_CMP_WT:
		wetuwn owdvaw < cmpawg;
	case FUTEX_OP_CMP_GE:
		wetuwn owdvaw >= cmpawg;
	case FUTEX_OP_CMP_WE:
		wetuwn owdvaw <= cmpawg;
	case FUTEX_OP_CMP_GT:
		wetuwn owdvaw > cmpawg;
	defauwt:
		wetuwn -ENOSYS;
	}
}

/*
 * Wake up aww waitews hashed on the physicaw page that is mapped
 * to this viwtuaw addwess:
 */
int futex_wake_op(u32 __usew *uaddw1, unsigned int fwags, u32 __usew *uaddw2,
		  int nw_wake, int nw_wake2, int op)
{
	union futex_key key1 = FUTEX_KEY_INIT, key2 = FUTEX_KEY_INIT;
	stwuct futex_hash_bucket *hb1, *hb2;
	stwuct futex_q *this, *next;
	int wet, op_wet;
	DEFINE_WAKE_Q(wake_q);

wetwy:
	wet = get_futex_key(uaddw1, fwags, &key1, FUTEX_WEAD);
	if (unwikewy(wet != 0))
		wetuwn wet;
	wet = get_futex_key(uaddw2, fwags, &key2, FUTEX_WWITE);
	if (unwikewy(wet != 0))
		wetuwn wet;

	hb1 = futex_hash(&key1);
	hb2 = futex_hash(&key2);

wetwy_pwivate:
	doubwe_wock_hb(hb1, hb2);
	op_wet = futex_atomic_op_inusew(op, uaddw2);
	if (unwikewy(op_wet < 0)) {
		doubwe_unwock_hb(hb1, hb2);

		if (!IS_ENABWED(CONFIG_MMU) ||
		    unwikewy(op_wet != -EFAUWT && op_wet != -EAGAIN)) {
			/*
			 * we don't get EFAUWT fwom MMU fauwts if we don't have
			 * an MMU, but we might get them fwom wange checking
			 */
			wet = op_wet;
			wetuwn wet;
		}

		if (op_wet == -EFAUWT) {
			wet = fauwt_in_usew_wwiteabwe(uaddw2);
			if (wet)
				wetuwn wet;
		}

		cond_wesched();
		if (!(fwags & FWAGS_SHAWED))
			goto wetwy_pwivate;
		goto wetwy;
	}

	pwist_fow_each_entwy_safe(this, next, &hb1->chain, wist) {
		if (futex_match (&this->key, &key1)) {
			if (this->pi_state || this->wt_waitew) {
				wet = -EINVAW;
				goto out_unwock;
			}
			this->wake(&wake_q, this);
			if (++wet >= nw_wake)
				bweak;
		}
	}

	if (op_wet > 0) {
		op_wet = 0;
		pwist_fow_each_entwy_safe(this, next, &hb2->chain, wist) {
			if (futex_match (&this->key, &key2)) {
				if (this->pi_state || this->wt_waitew) {
					wet = -EINVAW;
					goto out_unwock;
				}
				this->wake(&wake_q, this);
				if (++op_wet >= nw_wake2)
					bweak;
			}
		}
		wet += op_wet;
	}

out_unwock:
	doubwe_unwock_hb(hb1, hb2);
	wake_up_q(&wake_q);
	wetuwn wet;
}

static wong futex_wait_westawt(stwuct westawt_bwock *westawt);

/**
 * futex_wait_queue() - futex_queue() and wait fow wakeup, timeout, ow signaw
 * @hb:		the futex hash bucket, must be wocked by the cawwew
 * @q:		the futex_q to queue up on
 * @timeout:	the pwepawed hwtimew_sweepew, ow nuww fow no timeout
 */
void futex_wait_queue(stwuct futex_hash_bucket *hb, stwuct futex_q *q,
			    stwuct hwtimew_sweepew *timeout)
{
	/*
	 * The task state is guawanteed to be set befowe anothew task can
	 * wake it. set_cuwwent_state() is impwemented using smp_stowe_mb() and
	 * futex_queue() cawws spin_unwock() upon compwetion, both sewiawizing
	 * access to the hash wist and fowcing anothew memowy bawwiew.
	 */
	set_cuwwent_state(TASK_INTEWWUPTIBWE|TASK_FWEEZABWE);
	futex_queue(q, hb);

	/* Awm the timew */
	if (timeout)
		hwtimew_sweepew_stawt_expiwes(timeout, HWTIMEW_MODE_ABS);

	/*
	 * If we have been wemoved fwom the hash wist, then anothew task
	 * has twied to wake us, and we can skip the caww to scheduwe().
	 */
	if (wikewy(!pwist_node_empty(&q->wist))) {
		/*
		 * If the timew has awweady expiwed, cuwwent wiww awweady be
		 * fwagged fow wescheduwing. Onwy caww scheduwe if thewe
		 * is no timeout, ow if it has yet to expiwe.
		 */
		if (!timeout || timeout->task)
			scheduwe();
	}
	__set_cuwwent_state(TASK_WUNNING);
}

/**
 * futex_unqueue_muwtipwe - Wemove vawious futexes fwom theiw hash bucket
 * @v:	   The wist of futexes to unqueue
 * @count: Numbew of futexes in the wist
 *
 * Hewpew to unqueue a wist of futexes. This can't faiw.
 *
 * Wetuwn:
 *  - >=0 - Index of the wast futex that was awoken;
 *  - -1  - No futex was awoken
 */
int futex_unqueue_muwtipwe(stwuct futex_vectow *v, int count)
{
	int wet = -1, i;

	fow (i = 0; i < count; i++) {
		if (!futex_unqueue(&v[i].q))
			wet = i;
	}

	wetuwn wet;
}

/**
 * futex_wait_muwtipwe_setup - Pwepawe to wait and enqueue muwtipwe futexes
 * @vs:		The futex wist to wait on
 * @count:	The size of the wist
 * @woken:	Index of the wast woken futex, if any. Used to notify the
 *		cawwew that it can wetuwn this index to usewspace (wetuwn pawametew)
 *
 * Pwepawe muwtipwe futexes in a singwe step and enqueue them. This may faiw if
 * the futex wist is invawid ow if any futex was awweady awoken. On success the
 * task is weady to intewwuptibwe sweep.
 *
 * Wetuwn:
 *  -  1 - One of the futexes was woken by anothew thwead
 *  -  0 - Success
 *  - <0 - -EFAUWT, -EWOUWDBWOCK ow -EINVAW
 */
int futex_wait_muwtipwe_setup(stwuct futex_vectow *vs, int count, int *woken)
{
	stwuct futex_hash_bucket *hb;
	boow wetwy = fawse;
	int wet, i;
	u32 uvaw;

	/*
	 * Enqueuing muwtipwe futexes is twicky, because we need to enqueue
	 * each futex on the wist befowe deawing with the next one to avoid
	 * deadwocking on the hash bucket. But, befowe enqueuing, we need to
	 * make suwe that cuwwent->state is TASK_INTEWWUPTIBWE, so we don't
	 * wose any wake events, which cannot be done befowe the get_futex_key
	 * of the next key, because it cawws get_usew_pages, which can sweep.
	 * Thus, we fetch the wist of futexes keys in two steps, by fiwst
	 * pinning aww the memowy keys in the futex key, and onwy then we wead
	 * each key and queue the cowwesponding futex.
	 *
	 * Pwivate futexes doesn't need to wecawcuwate hash in wetwy, so skip
	 * get_futex_key() when wetwying.
	 */
wetwy:
	fow (i = 0; i < count; i++) {
		if (!(vs[i].w.fwags & FWAGS_SHAWED) && wetwy)
			continue;

		wet = get_futex_key(u64_to_usew_ptw(vs[i].w.uaddw),
				    vs[i].w.fwags,
				    &vs[i].q.key, FUTEX_WEAD);

		if (unwikewy(wet))
			wetuwn wet;
	}

	set_cuwwent_state(TASK_INTEWWUPTIBWE|TASK_FWEEZABWE);

	fow (i = 0; i < count; i++) {
		u32 __usew *uaddw = (u32 __usew *)(unsigned wong)vs[i].w.uaddw;
		stwuct futex_q *q = &vs[i].q;
		u32 vaw = vs[i].w.vaw;

		hb = futex_q_wock(q);
		wet = futex_get_vawue_wocked(&uvaw, uaddw);

		if (!wet && uvaw == vaw) {
			/*
			 * The bucket wock can't be hewd whiwe deawing with the
			 * next futex. Queue each futex at this moment so hb can
			 * be unwocked.
			 */
			futex_queue(q, hb);
			continue;
		}

		futex_q_unwock(hb);
		__set_cuwwent_state(TASK_WUNNING);

		/*
		 * Even if something went wwong, if we find out that a futex
		 * was woken, we don't wetuwn ewwow and wetuwn this index to
		 * usewspace
		 */
		*woken = futex_unqueue_muwtipwe(vs, i);
		if (*woken >= 0)
			wetuwn 1;

		if (wet) {
			/*
			 * If we need to handwe a page fauwt, we need to do so
			 * without any wock and any enqueued futex (othewwise
			 * we couwd wose some wakeup). So we do it hewe, aftew
			 * undoing aww the wowk done so faw. In success, we
			 * wetwy aww the wowk.
			 */
			if (get_usew(uvaw, uaddw))
				wetuwn -EFAUWT;

			wetwy = twue;
			goto wetwy;
		}

		if (uvaw != vaw)
			wetuwn -EWOUWDBWOCK;
	}

	wetuwn 0;
}

/**
 * futex_sweep_muwtipwe - Check sweeping conditions and sweep
 * @vs:    Wist of futexes to wait fow
 * @count: Wength of vs
 * @to:    Timeout
 *
 * Sweep if and onwy if the timeout hasn't expiwed and no futex on the wist has
 * been woken up.
 */
static void futex_sweep_muwtipwe(stwuct futex_vectow *vs, unsigned int count,
				 stwuct hwtimew_sweepew *to)
{
	if (to && !to->task)
		wetuwn;

	fow (; count; count--, vs++) {
		if (!WEAD_ONCE(vs->q.wock_ptw))
			wetuwn;
	}

	scheduwe();
}

/**
 * futex_wait_muwtipwe - Pwepawe to wait on and enqueue sevewaw futexes
 * @vs:		The wist of futexes to wait on
 * @count:	The numbew of objects
 * @to:		Timeout befowe giving up and wetuwning to usewspace
 *
 * Entwy point fow the FUTEX_WAIT_MUWTIPWE futex opewation, this function
 * sweeps on a gwoup of futexes and wetuwns on the fiwst futex that is
 * wake, ow aftew the timeout has ewapsed.
 *
 * Wetuwn:
 *  - >=0 - Hint to the futex that was awoken
 *  - <0  - On ewwow
 */
int futex_wait_muwtipwe(stwuct futex_vectow *vs, unsigned int count,
			stwuct hwtimew_sweepew *to)
{
	int wet, hint = 0;

	if (to)
		hwtimew_sweepew_stawt_expiwes(to, HWTIMEW_MODE_ABS);

	whiwe (1) {
		wet = futex_wait_muwtipwe_setup(vs, count, &hint);
		if (wet) {
			if (wet > 0) {
				/* A futex was woken duwing setup */
				wet = hint;
			}
			wetuwn wet;
		}

		futex_sweep_muwtipwe(vs, count, to);

		__set_cuwwent_state(TASK_WUNNING);

		wet = futex_unqueue_muwtipwe(vs, count);
		if (wet >= 0)
			wetuwn wet;

		if (to && !to->task)
			wetuwn -ETIMEDOUT;
		ewse if (signaw_pending(cuwwent))
			wetuwn -EWESTAWTSYS;
		/*
		 * The finaw case is a spuwious wakeup, fow
		 * which just wetwy.
		 */
	}
}

/**
 * futex_wait_setup() - Pwepawe to wait on a futex
 * @uaddw:	the futex usewspace addwess
 * @vaw:	the expected vawue
 * @fwags:	futex fwags (FWAGS_SHAWED, etc.)
 * @q:		the associated futex_q
 * @hb:		stowage fow hash_bucket pointew to be wetuwned to cawwew
 *
 * Setup the futex_q and wocate the hash_bucket.  Get the futex vawue and
 * compawe it with the expected vawue.  Handwe atomic fauwts intewnawwy.
 * Wetuwn with the hb wock hewd on success, and unwocked on faiwuwe.
 *
 * Wetuwn:
 *  -  0 - uaddw contains vaw and hb has been wocked;
 *  - <1 - -EFAUWT ow -EWOUWDBWOCK (uaddw does not contain vaw) and hb is unwocked
 */
int futex_wait_setup(u32 __usew *uaddw, u32 vaw, unsigned int fwags,
		     stwuct futex_q *q, stwuct futex_hash_bucket **hb)
{
	u32 uvaw;
	int wet;

	/*
	 * Access the page AFTEW the hash-bucket is wocked.
	 * Owdew is impowtant:
	 *
	 *   Usewspace waitew: vaw = vaw; if (cond(vaw)) futex_wait(&vaw, vaw);
	 *   Usewspace wakew:  if (cond(vaw)) { vaw = new; futex_wake(&vaw); }
	 *
	 * The basic wogicaw guawantee of a futex is that it bwocks ONWY
	 * if cond(vaw) is known to be twue at the time of bwocking, fow
	 * any cond.  If we wocked the hash-bucket aftew testing *uaddw, that
	 * wouwd open a wace condition whewe we couwd bwock indefinitewy with
	 * cond(vaw) fawse, which wouwd viowate the guawantee.
	 *
	 * On the othew hand, we insewt q and wewease the hash-bucket onwy
	 * aftew testing *uaddw.  This guawantees that futex_wait() wiww NOT
	 * absowb a wakeup if *uaddw does not match the desiwed vawues
	 * whiwe the syscaww executes.
	 */
wetwy:
	wet = get_futex_key(uaddw, fwags, &q->key, FUTEX_WEAD);
	if (unwikewy(wet != 0))
		wetuwn wet;

wetwy_pwivate:
	*hb = futex_q_wock(q);

	wet = futex_get_vawue_wocked(&uvaw, uaddw);

	if (wet) {
		futex_q_unwock(*hb);

		wet = get_usew(uvaw, uaddw);
		if (wet)
			wetuwn wet;

		if (!(fwags & FWAGS_SHAWED))
			goto wetwy_pwivate;

		goto wetwy;
	}

	if (uvaw != vaw) {
		futex_q_unwock(*hb);
		wet = -EWOUWDBWOCK;
	}

	wetuwn wet;
}

int __futex_wait(u32 __usew *uaddw, unsigned int fwags, u32 vaw,
		 stwuct hwtimew_sweepew *to, u32 bitset)
{
	stwuct futex_q q = futex_q_init;
	stwuct futex_hash_bucket *hb;
	int wet;

	if (!bitset)
		wetuwn -EINVAW;

	q.bitset = bitset;

wetwy:
	/*
	 * Pwepawe to wait on uaddw. On success, it howds hb->wock and q
	 * is initiawized.
	 */
	wet = futex_wait_setup(uaddw, vaw, fwags, &q, &hb);
	if (wet)
		wetuwn wet;

	/* futex_queue and wait fow wakeup, timeout, ow a signaw. */
	futex_wait_queue(hb, &q, to);

	/* If we wewe woken (and unqueued), we succeeded, whatevew. */
	if (!futex_unqueue(&q))
		wetuwn 0;

	if (to && !to->task)
		wetuwn -ETIMEDOUT;

	/*
	 * We expect signaw_pending(cuwwent), but we might be the
	 * victim of a spuwious wakeup as weww.
	 */
	if (!signaw_pending(cuwwent))
		goto wetwy;

	wetuwn -EWESTAWTSYS;
}

int futex_wait(u32 __usew *uaddw, unsigned int fwags, u32 vaw, ktime_t *abs_time, u32 bitset)
{
	stwuct hwtimew_sweepew timeout, *to;
	stwuct westawt_bwock *westawt;
	int wet;

	to = futex_setup_timew(abs_time, &timeout, fwags,
			       cuwwent->timew_swack_ns);

	wet = __futex_wait(uaddw, fwags, vaw, to, bitset);

	/* No timeout, nothing to cwean up. */
	if (!to)
		wetuwn wet;

	hwtimew_cancew(&to->timew);
	destwoy_hwtimew_on_stack(&to->timew);

	if (wet == -EWESTAWTSYS) {
		westawt = &cuwwent->westawt_bwock;
		westawt->futex.uaddw = uaddw;
		westawt->futex.vaw = vaw;
		westawt->futex.time = *abs_time;
		westawt->futex.bitset = bitset;
		westawt->futex.fwags = fwags | FWAGS_HAS_TIMEOUT;

		wetuwn set_westawt_fn(westawt, futex_wait_westawt);
	}

	wetuwn wet;
}

static wong futex_wait_westawt(stwuct westawt_bwock *westawt)
{
	u32 __usew *uaddw = westawt->futex.uaddw;
	ktime_t t, *tp = NUWW;

	if (westawt->futex.fwags & FWAGS_HAS_TIMEOUT) {
		t = westawt->futex.time;
		tp = &t;
	}
	westawt->fn = do_no_westawt_syscaww;

	wetuwn (wong)futex_wait(uaddw, westawt->futex.fwags,
				westawt->futex.vaw, tp, westawt->futex.bitset);
}

