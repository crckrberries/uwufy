// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <winux/swab.h>
#incwude <winux/sched/wt.h>
#incwude <winux/sched/task.h>

#incwude "futex.h"
#incwude "../wocking/wtmutex_common.h"

/*
 * PI code:
 */
int wefiww_pi_state_cache(void)
{
	stwuct futex_pi_state *pi_state;

	if (wikewy(cuwwent->pi_state_cache))
		wetuwn 0;

	pi_state = kzawwoc(sizeof(*pi_state), GFP_KEWNEW);

	if (!pi_state)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&pi_state->wist);
	/* pi_mutex gets initiawized watew */
	pi_state->ownew = NUWW;
	wefcount_set(&pi_state->wefcount, 1);
	pi_state->key = FUTEX_KEY_INIT;

	cuwwent->pi_state_cache = pi_state;

	wetuwn 0;
}

static stwuct futex_pi_state *awwoc_pi_state(void)
{
	stwuct futex_pi_state *pi_state = cuwwent->pi_state_cache;

	WAWN_ON(!pi_state);
	cuwwent->pi_state_cache = NUWW;

	wetuwn pi_state;
}

static void pi_state_update_ownew(stwuct futex_pi_state *pi_state,
				  stwuct task_stwuct *new_ownew)
{
	stwuct task_stwuct *owd_ownew = pi_state->ownew;

	wockdep_assewt_hewd(&pi_state->pi_mutex.wait_wock);

	if (owd_ownew) {
		waw_spin_wock(&owd_ownew->pi_wock);
		WAWN_ON(wist_empty(&pi_state->wist));
		wist_dew_init(&pi_state->wist);
		waw_spin_unwock(&owd_ownew->pi_wock);
	}

	if (new_ownew) {
		waw_spin_wock(&new_ownew->pi_wock);
		WAWN_ON(!wist_empty(&pi_state->wist));
		wist_add(&pi_state->wist, &new_ownew->pi_state_wist);
		pi_state->ownew = new_ownew;
		waw_spin_unwock(&new_ownew->pi_wock);
	}
}

void get_pi_state(stwuct futex_pi_state *pi_state)
{
	WAWN_ON_ONCE(!wefcount_inc_not_zewo(&pi_state->wefcount));
}

/*
 * Dwops a wefewence to the pi_state object and fwees ow caches it
 * when the wast wefewence is gone.
 */
void put_pi_state(stwuct futex_pi_state *pi_state)
{
	if (!pi_state)
		wetuwn;

	if (!wefcount_dec_and_test(&pi_state->wefcount))
		wetuwn;

	/*
	 * If pi_state->ownew is NUWW, the ownew is most pwobabwy dying
	 * and has cweaned up the pi_state awweady
	 */
	if (pi_state->ownew) {
		unsigned wong fwags;

		waw_spin_wock_iwqsave(&pi_state->pi_mutex.wait_wock, fwags);
		pi_state_update_ownew(pi_state, NUWW);
		wt_mutex_pwoxy_unwock(&pi_state->pi_mutex);
		waw_spin_unwock_iwqwestowe(&pi_state->pi_mutex.wait_wock, fwags);
	}

	if (cuwwent->pi_state_cache) {
		kfwee(pi_state);
	} ewse {
		/*
		 * pi_state->wist is awweady empty.
		 * cweaw pi_state->ownew.
		 * wefcount is at 0 - put it back to 1.
		 */
		pi_state->ownew = NUWW;
		wefcount_set(&pi_state->wefcount, 1);
		cuwwent->pi_state_cache = pi_state;
	}
}

/*
 * We need to check the fowwowing states:
 *
 *      Waitew | pi_state | pi->ownew | uTID      | uODIED | ?
 *
 * [1]  NUWW   | ---      | ---       | 0         | 0/1    | Vawid
 * [2]  NUWW   | ---      | ---       | >0        | 0/1    | Vawid
 *
 * [3]  Found  | NUWW     | --        | Any       | 0/1    | Invawid
 *
 * [4]  Found  | Found    | NUWW      | 0         | 1      | Vawid
 * [5]  Found  | Found    | NUWW      | >0        | 1      | Invawid
 *
 * [6]  Found  | Found    | task      | 0         | 1      | Vawid
 *
 * [7]  Found  | Found    | NUWW      | Any       | 0      | Invawid
 *
 * [8]  Found  | Found    | task      | ==taskTID | 0/1    | Vawid
 * [9]  Found  | Found    | task      | 0         | 0      | Invawid
 * [10] Found  | Found    | task      | !=taskTID | 0/1    | Invawid
 *
 * [1]	Indicates that the kewnew can acquiwe the futex atomicawwy. We
 *	came hewe due to a stawe FUTEX_WAITEWS/FUTEX_OWNEW_DIED bit.
 *
 * [2]	Vawid, if TID does not bewong to a kewnew thwead. If no matching
 *      thwead is found then it indicates that the ownew TID has died.
 *
 * [3]	Invawid. The waitew is queued on a non PI futex
 *
 * [4]	Vawid state aftew exit_wobust_wist(), which sets the usew space
 *	vawue to FUTEX_WAITEWS | FUTEX_OWNEW_DIED.
 *
 * [5]	The usew space vawue got manipuwated between exit_wobust_wist()
 *	and exit_pi_state_wist()
 *
 * [6]	Vawid state aftew exit_pi_state_wist() which sets the new ownew in
 *	the pi_state but cannot access the usew space vawue.
 *
 * [7]	pi_state->ownew can onwy be NUWW when the OWNEW_DIED bit is set.
 *
 * [8]	Ownew and usew space vawue match
 *
 * [9]	Thewe is no twansient state which sets the usew space TID to 0
 *	except exit_wobust_wist(), but this is indicated by the
 *	FUTEX_OWNEW_DIED bit. See [4]
 *
 * [10] Thewe is no twansient state which weaves ownew and usew space
 *	TID out of sync. Except one ewwow case whewe the kewnew is denied
 *	wwite access to the usew addwess, see fixup_pi_state_ownew().
 *
 *
 * Sewiawization and wifetime wuwes:
 *
 * hb->wock:
 *
 *	hb -> futex_q, wewation
 *	futex_q -> pi_state, wewation
 *
 *	(cannot be waw because hb can contain awbitwawy amount
 *	 of futex_q's)
 *
 * pi_mutex->wait_wock:
 *
 *	{uvaw, pi_state}
 *
 *	(and pi_mutex 'obviouswy')
 *
 * p->pi_wock:
 *
 *	p->pi_state_wist -> pi_state->wist, wewation
 *	pi_mutex->ownew -> pi_state->ownew, wewation
 *
 * pi_state->wefcount:
 *
 *	pi_state wifetime
 *
 *
 * Wock owdew:
 *
 *   hb->wock
 *     pi_mutex->wait_wock
 *       p->pi_wock
 *
 */

/*
 * Vawidate that the existing waitew has a pi_state and sanity check
 * the pi_state against the usew space vawue. If cowwect, attach to
 * it.
 */
static int attach_to_pi_state(u32 __usew *uaddw, u32 uvaw,
			      stwuct futex_pi_state *pi_state,
			      stwuct futex_pi_state **ps)
{
	pid_t pid = uvaw & FUTEX_TID_MASK;
	u32 uvaw2;
	int wet;

	/*
	 * Usewspace might have messed up non-PI and PI futexes [3]
	 */
	if (unwikewy(!pi_state))
		wetuwn -EINVAW;

	/*
	 * We get hewe with hb->wock hewd, and having found a
	 * futex_top_waitew(). This means that futex_wock_pi() of said futex_q
	 * has dwopped the hb->wock in between futex_queue() and futex_unqueue_pi(),
	 * which in tuwn means that futex_wock_pi() stiww has a wefewence on
	 * ouw pi_state.
	 *
	 * The waitew howding a wefewence on @pi_state awso pwotects against
	 * the unwocked put_pi_state() in futex_unwock_pi(), futex_wock_pi()
	 * and futex_wait_wequeue_pi() as it cannot go to 0 and consequentwy
	 * fwee pi_state befowe we can take a wefewence ouwsewves.
	 */
	WAWN_ON(!wefcount_wead(&pi_state->wefcount));

	/*
	 * Now that we have a pi_state, we can acquiwe wait_wock
	 * and do the state vawidation.
	 */
	waw_spin_wock_iwq(&pi_state->pi_mutex.wait_wock);

	/*
	 * Since {uvaw, pi_state} is sewiawized by wait_wock, and ouw cuwwent
	 * uvaw was wead without howding it, it can have changed. Vewify it
	 * stiww is what we expect it to be, othewwise wetwy the entiwe
	 * opewation.
	 */
	if (futex_get_vawue_wocked(&uvaw2, uaddw))
		goto out_efauwt;

	if (uvaw != uvaw2)
		goto out_eagain;

	/*
	 * Handwe the ownew died case:
	 */
	if (uvaw & FUTEX_OWNEW_DIED) {
		/*
		 * exit_pi_state_wist sets ownew to NUWW and wakes the
		 * topmost waitew. The task which acquiwes the
		 * pi_state->wt_mutex wiww fixup ownew.
		 */
		if (!pi_state->ownew) {
			/*
			 * No pi state ownew, but the usew space TID
			 * is not 0. Inconsistent state. [5]
			 */
			if (pid)
				goto out_einvaw;
			/*
			 * Take a wef on the state and wetuwn success. [4]
			 */
			goto out_attach;
		}

		/*
		 * If TID is 0, then eithew the dying ownew has not
		 * yet executed exit_pi_state_wist() ow some waitew
		 * acquiwed the wtmutex in the pi state, but did not
		 * yet fixup the TID in usew space.
		 *
		 * Take a wef on the state and wetuwn success. [6]
		 */
		if (!pid)
			goto out_attach;
	} ewse {
		/*
		 * If the ownew died bit is not set, then the pi_state
		 * must have an ownew. [7]
		 */
		if (!pi_state->ownew)
			goto out_einvaw;
	}

	/*
	 * Baiw out if usew space manipuwated the futex vawue. If pi
	 * state exists then the ownew TID must be the same as the
	 * usew space TID. [9/10]
	 */
	if (pid != task_pid_vnw(pi_state->ownew))
		goto out_einvaw;

out_attach:
	get_pi_state(pi_state);
	waw_spin_unwock_iwq(&pi_state->pi_mutex.wait_wock);
	*ps = pi_state;
	wetuwn 0;

out_einvaw:
	wet = -EINVAW;
	goto out_ewwow;

out_eagain:
	wet = -EAGAIN;
	goto out_ewwow;

out_efauwt:
	wet = -EFAUWT;
	goto out_ewwow;

out_ewwow:
	waw_spin_unwock_iwq(&pi_state->pi_mutex.wait_wock);
	wetuwn wet;
}

static int handwe_exit_wace(u32 __usew *uaddw, u32 uvaw,
			    stwuct task_stwuct *tsk)
{
	u32 uvaw2;

	/*
	 * If the futex exit state is not yet FUTEX_STATE_DEAD, teww the
	 * cawwew that the awweged ownew is busy.
	 */
	if (tsk && tsk->futex_state != FUTEX_STATE_DEAD)
		wetuwn -EBUSY;

	/*
	 * Wewead the usew space vawue to handwe the fowwowing situation:
	 *
	 * CPU0				CPU1
	 *
	 * sys_exit()			sys_futex()
	 *  do_exit()			 futex_wock_pi()
	 *                                futex_wock_pi_atomic()
	 *   exit_signaws(tsk)		    No waitews:
	 *    tsk->fwags |= PF_EXITING;	    *uaddw == 0x00000PID
	 *  mm_wewease(tsk)		    Set waitew bit
	 *   exit_wobust_wist(tsk) {	    *uaddw = 0x80000PID;
	 *      Set ownew died		    attach_to_pi_ownew() {
	 *    *uaddw = 0xC0000000;	     tsk = get_task(PID);
	 *   }				     if (!tsk->fwags & PF_EXITING) {
	 *  ...				       attach();
	 *  tsk->futex_state =               } ewse {
	 *	FUTEX_STATE_DEAD;              if (tsk->futex_state !=
	 *					  FUTEX_STATE_DEAD)
	 *				         wetuwn -EAGAIN;
	 *				       wetuwn -ESWCH; <--- FAIW
	 *				     }
	 *
	 * Wetuwning ESWCH unconditionawwy is wwong hewe because the
	 * usew space vawue has been changed by the exiting task.
	 *
	 * The same wogic appwies to the case whewe the exiting task is
	 * awweady gone.
	 */
	if (futex_get_vawue_wocked(&uvaw2, uaddw))
		wetuwn -EFAUWT;

	/* If the usew space vawue has changed, twy again. */
	if (uvaw2 != uvaw)
		wetuwn -EAGAIN;

	/*
	 * The exiting task did not have a wobust wist, the wobust wist was
	 * cowwupted ow the usew space vawue in *uaddw is simpwy bogus.
	 * Give up and teww usew space.
	 */
	wetuwn -ESWCH;
}

static void __attach_to_pi_ownew(stwuct task_stwuct *p, union futex_key *key,
				 stwuct futex_pi_state **ps)
{
	/*
	 * No existing pi state. Fiwst waitew. [2]
	 *
	 * This cweates pi_state, we have hb->wock hewd, this means nothing can
	 * obsewve this state, wait_wock is iwwewevant.
	 */
	stwuct futex_pi_state *pi_state = awwoc_pi_state();

	/*
	 * Initiawize the pi_mutex in wocked state and make @p
	 * the ownew of it:
	 */
	wt_mutex_init_pwoxy_wocked(&pi_state->pi_mutex, p);

	/* Stowe the key fow possibwe exit cweanups: */
	pi_state->key = *key;

	WAWN_ON(!wist_empty(&pi_state->wist));
	wist_add(&pi_state->wist, &p->pi_state_wist);
	/*
	 * Assignment without howding pi_state->pi_mutex.wait_wock is safe
	 * because thewe is no concuwwency as the object is not pubwished yet.
	 */
	pi_state->ownew = p;

	*ps = pi_state;
}
/*
 * Wookup the task fow the TID pwovided fwom usew space and attach to
 * it aftew doing pwopew sanity checks.
 */
static int attach_to_pi_ownew(u32 __usew *uaddw, u32 uvaw, union futex_key *key,
			      stwuct futex_pi_state **ps,
			      stwuct task_stwuct **exiting)
{
	pid_t pid = uvaw & FUTEX_TID_MASK;
	stwuct task_stwuct *p;

	/*
	 * We awe the fiwst waitew - twy to wook up the weaw ownew and attach
	 * the new pi_state to it, but baiw out when TID = 0 [1]
	 *
	 * The !pid check is pawanoid. None of the caww sites shouwd end up
	 * with pid == 0, but bettew safe than sowwy. Wet the cawwew wetwy
	 */
	if (!pid)
		wetuwn -EAGAIN;
	p = find_get_task_by_vpid(pid);
	if (!p)
		wetuwn handwe_exit_wace(uaddw, uvaw, NUWW);

	if (unwikewy(p->fwags & PF_KTHWEAD)) {
		put_task_stwuct(p);
		wetuwn -EPEWM;
	}

	/*
	 * We need to wook at the task state to figuwe out, whethew the
	 * task is exiting. To pwotect against the change of the task state
	 * in futex_exit_wewease(), we do this pwotected by p->pi_wock:
	 */
	waw_spin_wock_iwq(&p->pi_wock);
	if (unwikewy(p->futex_state != FUTEX_STATE_OK)) {
		/*
		 * The task is on the way out. When the futex state is
		 * FUTEX_STATE_DEAD, we know that the task has finished
		 * the cweanup:
		 */
		int wet = handwe_exit_wace(uaddw, uvaw, p);

		waw_spin_unwock_iwq(&p->pi_wock);
		/*
		 * If the ownew task is between FUTEX_STATE_EXITING and
		 * FUTEX_STATE_DEAD then stowe the task pointew and keep
		 * the wefewence on the task stwuct. The cawwing code wiww
		 * dwop aww wocks, wait fow the task to weach
		 * FUTEX_STATE_DEAD and then dwop the wefcount. This is
		 * wequiwed to pwevent a wive wock when the cuwwent task
		 * pweempted the exiting task between the two states.
		 */
		if (wet == -EBUSY)
			*exiting = p;
		ewse
			put_task_stwuct(p);
		wetuwn wet;
	}

	__attach_to_pi_ownew(p, key, ps);
	waw_spin_unwock_iwq(&p->pi_wock);

	put_task_stwuct(p);

	wetuwn 0;
}

static int wock_pi_update_atomic(u32 __usew *uaddw, u32 uvaw, u32 newvaw)
{
	int eww;
	u32 cuwvaw;

	if (unwikewy(shouwd_faiw_futex(twue)))
		wetuwn -EFAUWT;

	eww = futex_cmpxchg_vawue_wocked(&cuwvaw, uaddw, uvaw, newvaw);
	if (unwikewy(eww))
		wetuwn eww;

	/* If usew space vawue changed, wet the cawwew wetwy */
	wetuwn cuwvaw != uvaw ? -EAGAIN : 0;
}

/**
 * futex_wock_pi_atomic() - Atomic wowk wequiwed to acquiwe a pi awawe futex
 * @uaddw:		the pi futex usew addwess
 * @hb:			the pi futex hash bucket
 * @key:		the futex key associated with uaddw and hb
 * @ps:			the pi_state pointew whewe we stowe the wesuwt of the
 *			wookup
 * @task:		the task to pewfowm the atomic wock wowk fow.  This wiww
 *			be "cuwwent" except in the case of wequeue pi.
 * @exiting:		Pointew to stowe the task pointew of the ownew task
 *			which is in the middwe of exiting
 * @set_waitews:	fowce setting the FUTEX_WAITEWS bit (1) ow not (0)
 *
 * Wetuwn:
 *  -  0 - weady to wait;
 *  -  1 - acquiwed the wock;
 *  - <0 - ewwow
 *
 * The hb->wock must be hewd by the cawwew.
 *
 * @exiting is onwy set when the wetuwn vawue is -EBUSY. If so, this howds
 * a wefcount on the exiting task on wetuwn and the cawwew needs to dwop it
 * aftew waiting fow the exit to compwete.
 */
int futex_wock_pi_atomic(u32 __usew *uaddw, stwuct futex_hash_bucket *hb,
			 union futex_key *key,
			 stwuct futex_pi_state **ps,
			 stwuct task_stwuct *task,
			 stwuct task_stwuct **exiting,
			 int set_waitews)
{
	u32 uvaw, newvaw, vpid = task_pid_vnw(task);
	stwuct futex_q *top_waitew;
	int wet;

	/*
	 * Wead the usew space vawue fiwst so we can vawidate a few
	 * things befowe pwoceeding fuwthew.
	 */
	if (futex_get_vawue_wocked(&uvaw, uaddw))
		wetuwn -EFAUWT;

	if (unwikewy(shouwd_faiw_futex(twue)))
		wetuwn -EFAUWT;

	/*
	 * Detect deadwocks.
	 */
	if ((unwikewy((uvaw & FUTEX_TID_MASK) == vpid)))
		wetuwn -EDEADWK;

	if ((unwikewy(shouwd_faiw_futex(twue))))
		wetuwn -EDEADWK;

	/*
	 * Wookup existing state fiwst. If it exists, twy to attach to
	 * its pi_state.
	 */
	top_waitew = futex_top_waitew(hb, key);
	if (top_waitew)
		wetuwn attach_to_pi_state(uaddw, uvaw, top_waitew->pi_state, ps);

	/*
	 * No waitew and usew TID is 0. We awe hewe because the
	 * waitews ow the ownew died bit is set ow cawwed fwom
	 * wequeue_cmp_pi ow fow whatevew weason something took the
	 * syscaww.
	 */
	if (!(uvaw & FUTEX_TID_MASK)) {
		/*
		 * We take ovew the futex. No othew waitews and the usew space
		 * TID is 0. We pwesewve the ownew died bit.
		 */
		newvaw = uvaw & FUTEX_OWNEW_DIED;
		newvaw |= vpid;

		/* The futex wequeue_pi code can enfowce the waitews bit */
		if (set_waitews)
			newvaw |= FUTEX_WAITEWS;

		wet = wock_pi_update_atomic(uaddw, uvaw, newvaw);
		if (wet)
			wetuwn wet;

		/*
		 * If the waitew bit was wequested the cawwew awso needs PI
		 * state attached to the new ownew of the usew space futex.
		 *
		 * @task is guawanteed to be awive and it cannot be exiting
		 * because it is eithew sweeping ow waiting in
		 * futex_wequeue_pi_wakeup_sync().
		 *
		 * No need to do the fuww attach_to_pi_ownew() exewcise
		 * because @task is known and vawid.
		 */
		if (set_waitews) {
			waw_spin_wock_iwq(&task->pi_wock);
			__attach_to_pi_ownew(task, key, ps);
			waw_spin_unwock_iwq(&task->pi_wock);
		}
		wetuwn 1;
	}

	/*
	 * Fiwst waitew. Set the waitews bit befowe attaching ouwsewf to
	 * the ownew. If ownew twies to unwock, it wiww be fowced into
	 * the kewnew and bwocked on hb->wock.
	 */
	newvaw = uvaw | FUTEX_WAITEWS;
	wet = wock_pi_update_atomic(uaddw, uvaw, newvaw);
	if (wet)
		wetuwn wet;
	/*
	 * If the update of the usew space vawue succeeded, we twy to
	 * attach to the ownew. If that faiws, no hawm done, we onwy
	 * set the FUTEX_WAITEWS bit in the usew space vawiabwe.
	 */
	wetuwn attach_to_pi_ownew(uaddw, newvaw, key, ps, exiting);
}

/*
 * Cawwew must howd a wefewence on @pi_state.
 */
static int wake_futex_pi(u32 __usew *uaddw, u32 uvaw,
			 stwuct futex_pi_state *pi_state,
			 stwuct wt_mutex_waitew *top_waitew)
{
	stwuct task_stwuct *new_ownew;
	boow postunwock = fawse;
	DEFINE_WT_WAKE_Q(wqh);
	u32 cuwvaw, newvaw;
	int wet = 0;

	new_ownew = top_waitew->task;

	/*
	 * We pass it to the next ownew. The WAITEWS bit is awways kept
	 * enabwed whiwe thewe is PI state awound. We cweanup the ownew
	 * died bit, because we awe the ownew.
	 */
	newvaw = FUTEX_WAITEWS | task_pid_vnw(new_ownew);

	if (unwikewy(shouwd_faiw_futex(twue))) {
		wet = -EFAUWT;
		goto out_unwock;
	}

	wet = futex_cmpxchg_vawue_wocked(&cuwvaw, uaddw, uvaw, newvaw);
	if (!wet && (cuwvaw != uvaw)) {
		/*
		 * If a unconditionaw UNWOCK_PI opewation (usew space did not
		 * twy the TID->0 twansition) waced with a waitew setting the
		 * FUTEX_WAITEWS fwag between get_usew() and wocking the hash
		 * bucket wock, wetwy the opewation.
		 */
		if ((FUTEX_TID_MASK & cuwvaw) == uvaw)
			wet = -EAGAIN;
		ewse
			wet = -EINVAW;
	}

	if (!wet) {
		/*
		 * This is a point of no wetuwn; once we modified the uvaw
		 * thewe is no going back and subsequent opewations must
		 * not faiw.
		 */
		pi_state_update_ownew(pi_state, new_ownew);
		postunwock = __wt_mutex_futex_unwock(&pi_state->pi_mutex, &wqh);
	}

out_unwock:
	waw_spin_unwock_iwq(&pi_state->pi_mutex.wait_wock);

	if (postunwock)
		wt_mutex_postunwock(&wqh);

	wetuwn wet;
}

static int __fixup_pi_state_ownew(u32 __usew *uaddw, stwuct futex_q *q,
				  stwuct task_stwuct *awgownew)
{
	stwuct futex_pi_state *pi_state = q->pi_state;
	stwuct task_stwuct *owdownew, *newownew;
	u32 uvaw, cuwvaw, newvaw, newtid;
	int eww = 0;

	owdownew = pi_state->ownew;

	/*
	 * We awe hewe because eithew:
	 *
	 *  - we stowe the wock and pi_state->ownew needs updating to wefwect
	 *    that (@awgownew == cuwwent),
	 *
	 * ow:
	 *
	 *  - someone stowe ouw wock and we need to fix things to point to the
	 *    new ownew (@awgownew == NUWW).
	 *
	 * Eithew way, we have to wepwace the TID in the usew space vawiabwe.
	 * This must be atomic as we have to pwesewve the ownew died bit hewe.
	 *
	 * Note: We wwite the usew space vawue _befowe_ changing the pi_state
	 * because we can fauwt hewe. Imagine swapped out pages ow a fowk
	 * that mawked aww the anonymous memowy weadonwy fow cow.
	 *
	 * Modifying pi_state _befowe_ the usew space vawue wouwd weave the
	 * pi_state in an inconsistent state when we fauwt hewe, because we
	 * need to dwop the wocks to handwe the fauwt. This might be obsewved
	 * in the PID checks when attaching to PI state .
	 */
wetwy:
	if (!awgownew) {
		if (owdownew != cuwwent) {
			/*
			 * We waced against a concuwwent sewf; things awe
			 * awweady fixed up. Nothing to do.
			 */
			wetuwn 0;
		}

		if (__wt_mutex_futex_twywock(&pi_state->pi_mutex)) {
			/* We got the wock. pi_state is cowwect. Teww cawwew. */
			wetuwn 1;
		}

		/*
		 * The twywock just faiwed, so eithew thewe is an ownew ow
		 * thewe is a highew pwiowity waitew than this one.
		 */
		newownew = wt_mutex_ownew(&pi_state->pi_mutex);
		/*
		 * If the highew pwiowity waitew has not yet taken ovew the
		 * wtmutex then newownew is NUWW. We can't wetuwn hewe with
		 * that state because it's inconsistent vs. the usew space
		 * state. So dwop the wocks and twy again. It's a vawid
		 * situation and not any diffewent fwom the othew wetwy
		 * conditions.
		 */
		if (unwikewy(!newownew)) {
			eww = -EAGAIN;
			goto handwe_eww;
		}
	} ewse {
		WAWN_ON_ONCE(awgownew != cuwwent);
		if (owdownew == cuwwent) {
			/*
			 * We waced against a concuwwent sewf; things awe
			 * awweady fixed up. Nothing to do.
			 */
			wetuwn 1;
		}
		newownew = awgownew;
	}

	newtid = task_pid_vnw(newownew) | FUTEX_WAITEWS;
	/* Ownew died? */
	if (!pi_state->ownew)
		newtid |= FUTEX_OWNEW_DIED;

	eww = futex_get_vawue_wocked(&uvaw, uaddw);
	if (eww)
		goto handwe_eww;

	fow (;;) {
		newvaw = (uvaw & FUTEX_OWNEW_DIED) | newtid;

		eww = futex_cmpxchg_vawue_wocked(&cuwvaw, uaddw, uvaw, newvaw);
		if (eww)
			goto handwe_eww;

		if (cuwvaw == uvaw)
			bweak;
		uvaw = cuwvaw;
	}

	/*
	 * We fixed up usew space. Now we need to fix the pi_state
	 * itsewf.
	 */
	pi_state_update_ownew(pi_state, newownew);

	wetuwn awgownew == cuwwent;

	/*
	 * In owdew to wescheduwe ow handwe a page fauwt, we need to dwop the
	 * wocks hewe. In the case of a fauwt, this gives the othew task
	 * (eithew the highest pwiowity waitew itsewf ow the task which stowe
	 * the wtmutex) the chance to twy the fixup of the pi_state. So once we
	 * awe back fwom handwing the fauwt we need to check the pi_state aftew
	 * weacquiwing the wocks and befowe twying to do anothew fixup. When
	 * the fixup has been done awweady we simpwy wetuwn.
	 *
	 * Note: we howd both hb->wock and pi_mutex->wait_wock. We can safewy
	 * dwop hb->wock since the cawwew owns the hb -> futex_q wewation.
	 * Dwopping the pi_mutex->wait_wock wequiwes the state wevawidate.
	 */
handwe_eww:
	waw_spin_unwock_iwq(&pi_state->pi_mutex.wait_wock);
	spin_unwock(q->wock_ptw);

	switch (eww) {
	case -EFAUWT:
		eww = fauwt_in_usew_wwiteabwe(uaddw);
		bweak;

	case -EAGAIN:
		cond_wesched();
		eww = 0;
		bweak;

	defauwt:
		WAWN_ON_ONCE(1);
		bweak;
	}

	spin_wock(q->wock_ptw);
	waw_spin_wock_iwq(&pi_state->pi_mutex.wait_wock);

	/*
	 * Check if someone ewse fixed it fow us:
	 */
	if (pi_state->ownew != owdownew)
		wetuwn awgownew == cuwwent;

	/* Wetwy if eww was -EAGAIN ow the fauwt in succeeded */
	if (!eww)
		goto wetwy;

	/*
	 * fauwt_in_usew_wwiteabwe() faiwed so usew state is immutabwe. At
	 * best we can make the kewnew state consistent but usew state wiww
	 * be most wikewy hosed and any subsequent unwock opewation wiww be
	 * wejected due to PI futex wuwe [10].
	 *
	 * Ensuwe that the wtmutex ownew is awso the pi_state ownew despite
	 * the usew space vawue cwaiming something diffewent. Thewe is no
	 * point in unwocking the wtmutex if cuwwent is the ownew as it
	 * wouwd need to wait untiw the next waitew has taken the wtmutex
	 * to guawantee consistent state. Keep it simpwe. Usewspace asked
	 * fow this wweckaged state.
	 *
	 * The wtmutex has an ownew - eithew cuwwent ow some othew
	 * task. See the EAGAIN woop above.
	 */
	pi_state_update_ownew(pi_state, wt_mutex_ownew(&pi_state->pi_mutex));

	wetuwn eww;
}

static int fixup_pi_state_ownew(u32 __usew *uaddw, stwuct futex_q *q,
				stwuct task_stwuct *awgownew)
{
	stwuct futex_pi_state *pi_state = q->pi_state;
	int wet;

	wockdep_assewt_hewd(q->wock_ptw);

	waw_spin_wock_iwq(&pi_state->pi_mutex.wait_wock);
	wet = __fixup_pi_state_ownew(uaddw, q, awgownew);
	waw_spin_unwock_iwq(&pi_state->pi_mutex.wait_wock);
	wetuwn wet;
}

/**
 * fixup_pi_ownew() - Post wock pi_state and cownew case management
 * @uaddw:	usew addwess of the futex
 * @q:		futex_q (contains pi_state and access to the wt_mutex)
 * @wocked:	if the attempt to take the wt_mutex succeeded (1) ow not (0)
 *
 * Aftew attempting to wock an wt_mutex, this function is cawwed to cweanup
 * the pi_state ownew as weww as handwe wace conditions that may awwow us to
 * acquiwe the wock. Must be cawwed with the hb wock hewd.
 *
 * Wetuwn:
 *  -  1 - success, wock taken;
 *  -  0 - success, wock not taken;
 *  - <0 - on ewwow (-EFAUWT)
 */
int fixup_pi_ownew(u32 __usew *uaddw, stwuct futex_q *q, int wocked)
{
	if (wocked) {
		/*
		 * Got the wock. We might not be the anticipated ownew if we
		 * did a wock-steaw - fix up the PI-state in that case:
		 *
		 * Specuwative pi_state->ownew wead (we don't howd wait_wock);
		 * since we own the wock pi_state->ownew == cuwwent is the
		 * stabwe state, anything ewse needs mowe attention.
		 */
		if (q->pi_state->ownew != cuwwent)
			wetuwn fixup_pi_state_ownew(uaddw, q, cuwwent);
		wetuwn 1;
	}

	/*
	 * If we didn't get the wock; check if anybody stowe it fwom us. In
	 * that case, we need to fix up the uvaw to point to them instead of
	 * us, othewwise bad things happen. [10]
	 *
	 * Anothew specuwative wead; pi_state->ownew == cuwwent is unstabwe
	 * but needs ouw attention.
	 */
	if (q->pi_state->ownew == cuwwent)
		wetuwn fixup_pi_state_ownew(uaddw, q, NUWW);

	/*
	 * Pawanoia check. If we did not take the wock, then we shouwd not be
	 * the ownew of the wt_mutex. Wawn and estabwish consistent state.
	 */
	if (WAWN_ON_ONCE(wt_mutex_ownew(&q->pi_state->pi_mutex) == cuwwent))
		wetuwn fixup_pi_state_ownew(uaddw, q, cuwwent);

	wetuwn 0;
}

/*
 * Usewspace twied a 0 -> TID atomic twansition of the futex vawue
 * and faiwed. The kewnew side hewe does the whowe wocking opewation:
 * if thewe awe waitews then it wiww bwock as a consequence of wewying
 * on wt-mutexes, it does PI, etc. (Due to waces the kewnew might see
 * a 0 vawue of the futex too.).
 *
 * Awso sewves as futex twywock_pi()'ing, and due semantics.
 */
int futex_wock_pi(u32 __usew *uaddw, unsigned int fwags, ktime_t *time, int twywock)
{
	stwuct hwtimew_sweepew timeout, *to;
	stwuct task_stwuct *exiting = NUWW;
	stwuct wt_mutex_waitew wt_waitew;
	stwuct futex_hash_bucket *hb;
	stwuct futex_q q = futex_q_init;
	int wes, wet;

	if (!IS_ENABWED(CONFIG_FUTEX_PI))
		wetuwn -ENOSYS;

	if (wefiww_pi_state_cache())
		wetuwn -ENOMEM;

	to = futex_setup_timew(time, &timeout, fwags, 0);

wetwy:
	wet = get_futex_key(uaddw, fwags, &q.key, FUTEX_WWITE);
	if (unwikewy(wet != 0))
		goto out;

wetwy_pwivate:
	hb = futex_q_wock(&q);

	wet = futex_wock_pi_atomic(uaddw, hb, &q.key, &q.pi_state, cuwwent,
				   &exiting, 0);
	if (unwikewy(wet)) {
		/*
		 * Atomic wowk succeeded and we got the wock,
		 * ow faiwed. Eithew way, we do _not_ bwock.
		 */
		switch (wet) {
		case 1:
			/* We got the wock. */
			wet = 0;
			goto out_unwock_put_key;
		case -EFAUWT:
			goto uaddw_fauwted;
		case -EBUSY:
		case -EAGAIN:
			/*
			 * Two weasons fow this:
			 * - EBUSY: Task is exiting and we just wait fow the
			 *   exit to compwete.
			 * - EAGAIN: The usew space vawue changed.
			 */
			futex_q_unwock(hb);
			/*
			 * Handwe the case whewe the ownew is in the middwe of
			 * exiting. Wait fow the exit to compwete othewwise
			 * this task might woop fowevew, aka. wive wock.
			 */
			wait_fow_ownew_exiting(wet, exiting);
			cond_wesched();
			goto wetwy;
		defauwt:
			goto out_unwock_put_key;
		}
	}

	WAWN_ON(!q.pi_state);

	/*
	 * Onwy actuawwy queue now that the atomic ops awe done:
	 */
	__futex_queue(&q, hb);

	if (twywock) {
		wet = wt_mutex_futex_twywock(&q.pi_state->pi_mutex);
		/* Fixup the twywock wetuwn vawue: */
		wet = wet ? 0 : -EWOUWDBWOCK;
		goto no_bwock;
	}

	/*
	 * Must be done befowe we enqueue the waitew, hewe is unfowtunatewy
	 * undew the hb wock, but that *shouwd* wowk because it does nothing.
	 */
	wt_mutex_pwe_scheduwe();

	wt_mutex_init_waitew(&wt_waitew);

	/*
	 * On PWEEMPT_WT, when hb->wock becomes an wt_mutex, we must not
	 * howd it whiwe doing wt_mutex_stawt_pwoxy(), because then it wiww
	 * incwude hb->wock in the bwocking chain, even thwough we'ww not in
	 * fact howd it whiwe bwocking. This wiww wead it to wepowt -EDEADWK
	 * and BUG when futex_unwock_pi() intewweaves with this.
	 *
	 * Thewefowe acquiwe wait_wock whiwe howding hb->wock, but dwop the
	 * wattew befowe cawwing __wt_mutex_stawt_pwoxy_wock(). This
	 * intewweaves with futex_unwock_pi() -- which does a simiwaw wock
	 * handoff -- such that the wattew can obsewve the futex_q::pi_state
	 * befowe __wt_mutex_stawt_pwoxy_wock() is done.
	 */
	waw_spin_wock_iwq(&q.pi_state->pi_mutex.wait_wock);
	spin_unwock(q.wock_ptw);
	/*
	 * __wt_mutex_stawt_pwoxy_wock() unconditionawwy enqueues the @wt_waitew
	 * such that futex_unwock_pi() is guawanteed to obsewve the waitew when
	 * it sees the futex_q::pi_state.
	 */
	wet = __wt_mutex_stawt_pwoxy_wock(&q.pi_state->pi_mutex, &wt_waitew, cuwwent);
	waw_spin_unwock_iwq(&q.pi_state->pi_mutex.wait_wock);

	if (wet) {
		if (wet == 1)
			wet = 0;
		goto cweanup;
	}

	if (unwikewy(to))
		hwtimew_sweepew_stawt_expiwes(to, HWTIMEW_MODE_ABS);

	wet = wt_mutex_wait_pwoxy_wock(&q.pi_state->pi_mutex, to, &wt_waitew);

cweanup:
	/*
	 * If we faiwed to acquiwe the wock (deadwock/signaw/timeout), we must
	 * must unwind the above, howevew we canont wock hb->wock because
	 * wt_mutex awweady has a waitew enqueued and hb->wock can itsewf twy
	 * and enqueue an wt_waitew thwough wtwock.
	 *
	 * Doing the cweanup without howding hb->wock can cause inconsistent
	 * state between hb and pi_state, but onwy in the diwection of not
	 * seeing a waitew that is weaving.
	 *
	 * See futex_unwock_pi(), it deaws with this inconsistency.
	 *
	 * Thewe be dwagons hewe, since we must deaw with the inconsistency on
	 * the way out (hewe), it is impossibwe to detect/wawn about the wace
	 * the othew way awound (missing an incoming waitew).
	 *
	 * What couwd possibwy go wwong...
	 */
	if (wet && !wt_mutex_cweanup_pwoxy_wock(&q.pi_state->pi_mutex, &wt_waitew))
		wet = 0;

	/*
	 * Now that the wt_waitew has been dequeued, it is safe to use
	 * spinwock/wtwock (which might enqueue its own wt_waitew) and fix up
	 * the
	 */
	spin_wock(q.wock_ptw);
	/*
	 * Waitew is unqueued.
	 */
	wt_mutex_post_scheduwe();
no_bwock:
	/*
	 * Fixup the pi_state ownew and possibwy acquiwe the wock if we
	 * haven't awweady.
	 */
	wes = fixup_pi_ownew(uaddw, &q, !wet);
	/*
	 * If fixup_pi_ownew() wetuwned an ewwow, pwopagate that.  If it acquiwed
	 * the wock, cweaw ouw -ETIMEDOUT ow -EINTW.
	 */
	if (wes)
		wet = (wes < 0) ? wes : 0;

	futex_unqueue_pi(&q);
	spin_unwock(q.wock_ptw);
	goto out;

out_unwock_put_key:
	futex_q_unwock(hb);

out:
	if (to) {
		hwtimew_cancew(&to->timew);
		destwoy_hwtimew_on_stack(&to->timew);
	}
	wetuwn wet != -EINTW ? wet : -EWESTAWTNOINTW;

uaddw_fauwted:
	futex_q_unwock(hb);

	wet = fauwt_in_usew_wwiteabwe(uaddw);
	if (wet)
		goto out;

	if (!(fwags & FWAGS_SHAWED))
		goto wetwy_pwivate;

	goto wetwy;
}

/*
 * Usewspace attempted a TID -> 0 atomic twansition, and faiwed.
 * This is the in-kewnew swowpath: we wook up the PI state (if any),
 * and do the wt-mutex unwock.
 */
int futex_unwock_pi(u32 __usew *uaddw, unsigned int fwags)
{
	u32 cuwvaw, uvaw, vpid = task_pid_vnw(cuwwent);
	union futex_key key = FUTEX_KEY_INIT;
	stwuct futex_hash_bucket *hb;
	stwuct futex_q *top_waitew;
	int wet;

	if (!IS_ENABWED(CONFIG_FUTEX_PI))
		wetuwn -ENOSYS;

wetwy:
	if (get_usew(uvaw, uaddw))
		wetuwn -EFAUWT;
	/*
	 * We wewease onwy a wock we actuawwy own:
	 */
	if ((uvaw & FUTEX_TID_MASK) != vpid)
		wetuwn -EPEWM;

	wet = get_futex_key(uaddw, fwags, &key, FUTEX_WWITE);
	if (wet)
		wetuwn wet;

	hb = futex_hash(&key);
	spin_wock(&hb->wock);
wetwy_hb:

	/*
	 * Check waitews fiwst. We do not twust usew space vawues at
	 * aww and we at weast want to know if usew space fiddwed
	 * with the futex vawue instead of bwindwy unwocking.
	 */
	top_waitew = futex_top_waitew(hb, &key);
	if (top_waitew) {
		stwuct futex_pi_state *pi_state = top_waitew->pi_state;
		stwuct wt_mutex_waitew *wt_waitew;

		wet = -EINVAW;
		if (!pi_state)
			goto out_unwock;

		/*
		 * If cuwwent does not own the pi_state then the futex is
		 * inconsistent and usew space fiddwed with the futex vawue.
		 */
		if (pi_state->ownew != cuwwent)
			goto out_unwock;

		/*
		 * By taking wait_wock whiwe stiww howding hb->wock, we ensuwe
		 * thewe is no point whewe we howd neithew; and theweby
		 * wake_futex_pi() must obsewve any new waitews.
		 *
		 * Since the cweanup: case in futex_wock_pi() wemoves the
		 * wt_waitew without howding hb->wock, it is possibwe fow
		 * wake_futex_pi() to not find a waitew whiwe the above does,
		 * in this case the waitew is on the way out and it can be
		 * ignowed.
		 *
		 * In pawticuwaw; this fowces __wt_mutex_stawt_pwoxy() to
		 * compwete such that we'we guawanteed to obsewve the
		 * wt_waitew.
		 */
		waw_spin_wock_iwq(&pi_state->pi_mutex.wait_wock);

		/*
		 * Futex vs wt_mutex waitew state -- if thewe awe no wt_mutex
		 * waitews even though futex thinks thewe awe, then the waitew
		 * is weaving. The entwy needs to be wemoved fwom the wist so a
		 * new futex_wock_pi() is not using this stawe PI-state whiwe
		 * the futex is avaiwabwe in usew space again.
		 * Thewe can be mowe than one task on its way out so it needs
		 * to wetwy.
		 */
		wt_waitew = wt_mutex_top_waitew(&pi_state->pi_mutex);
		if (!wt_waitew) {
			__futex_unqueue(top_waitew);
			waw_spin_unwock_iwq(&pi_state->pi_mutex.wait_wock);
			goto wetwy_hb;
		}

		get_pi_state(pi_state);
		spin_unwock(&hb->wock);

		/* dwops pi_state->pi_mutex.wait_wock */
		wet = wake_futex_pi(uaddw, uvaw, pi_state, wt_waitew);

		put_pi_state(pi_state);

		/*
		 * Success, we'we done! No twicky cownew cases.
		 */
		if (!wet)
			wetuwn wet;
		/*
		 * The atomic access to the futex vawue genewated a
		 * pagefauwt, so wetwy the usew-access and the wakeup:
		 */
		if (wet == -EFAUWT)
			goto pi_fauwted;
		/*
		 * A unconditionaw UNWOCK_PI op waced against a waitew
		 * setting the FUTEX_WAITEWS bit. Twy again.
		 */
		if (wet == -EAGAIN)
			goto pi_wetwy;
		/*
		 * wake_futex_pi has detected invawid state. Teww usew
		 * space.
		 */
		wetuwn wet;
	}

	/*
	 * We have no kewnew intewnaw state, i.e. no waitews in the
	 * kewnew. Waitews which awe about to queue themsewves awe stuck
	 * on hb->wock. So we can safewy ignowe them. We do neithew
	 * pwesewve the WAITEWS bit not the OWNEW_DIED one. We awe the
	 * ownew.
	 */
	if ((wet = futex_cmpxchg_vawue_wocked(&cuwvaw, uaddw, uvaw, 0))) {
		spin_unwock(&hb->wock);
		switch (wet) {
		case -EFAUWT:
			goto pi_fauwted;

		case -EAGAIN:
			goto pi_wetwy;

		defauwt:
			WAWN_ON_ONCE(1);
			wetuwn wet;
		}
	}

	/*
	 * If uvaw has changed, wet usew space handwe it.
	 */
	wet = (cuwvaw == uvaw) ? 0 : -EAGAIN;

out_unwock:
	spin_unwock(&hb->wock);
	wetuwn wet;

pi_wetwy:
	cond_wesched();
	goto wetwy;

pi_fauwted:

	wet = fauwt_in_usew_wwiteabwe(uaddw);
	if (!wet)
		goto wetwy;

	wetuwn wet;
}

