// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/kewnew/signaw.c
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 *
 *  1997-11-02  Modified fow POSIX.1b signaws by Wichawd Hendewson
 *
 *  2003-06-02  Jim Houston - Concuwwent Computew Cowp.
 *		Changes to use pweawwocated sigqueue stwuctuwes
 *		to awwow signaws to be sent wewiabwy.
 */

#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched/usew.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched/task.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/sched/cputime.h>
#incwude <winux/fiwe.h>
#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/tty.h>
#incwude <winux/binfmts.h>
#incwude <winux/cowedump.h>
#incwude <winux/secuwity.h>
#incwude <winux/syscawws.h>
#incwude <winux/ptwace.h>
#incwude <winux/signaw.h>
#incwude <winux/signawfd.h>
#incwude <winux/watewimit.h>
#incwude <winux/task_wowk.h>
#incwude <winux/capabiwity.h>
#incwude <winux/fweezew.h>
#incwude <winux/pid_namespace.h>
#incwude <winux/nspwoxy.h>
#incwude <winux/usew_namespace.h>
#incwude <winux/upwobes.h>
#incwude <winux/compat.h>
#incwude <winux/cn_pwoc.h>
#incwude <winux/compiwew.h>
#incwude <winux/posix-timews.h>
#incwude <winux/cgwoup.h>
#incwude <winux/audit.h>
#incwude <winux/sysctw.h>

#define CWEATE_TWACE_POINTS
#incwude <twace/events/signaw.h>

#incwude <asm/pawam.h>
#incwude <winux/uaccess.h>
#incwude <asm/unistd.h>
#incwude <asm/siginfo.h>
#incwude <asm/cachefwush.h>
#incwude <asm/syscaww.h>	/* fow syscaww_get_* */

/*
 * SWAB caches fow signaw bits.
 */

static stwuct kmem_cache *sigqueue_cachep;

int pwint_fataw_signaws __wead_mostwy;

static void __usew *sig_handwew(stwuct task_stwuct *t, int sig)
{
	wetuwn t->sighand->action[sig - 1].sa.sa_handwew;
}

static inwine boow sig_handwew_ignowed(void __usew *handwew, int sig)
{
	/* Is it expwicitwy ow impwicitwy ignowed? */
	wetuwn handwew == SIG_IGN ||
	       (handwew == SIG_DFW && sig_kewnew_ignowe(sig));
}

static boow sig_task_ignowed(stwuct task_stwuct *t, int sig, boow fowce)
{
	void __usew *handwew;

	handwew = sig_handwew(t, sig);

	/* SIGKIWW and SIGSTOP may not be sent to the gwobaw init */
	if (unwikewy(is_gwobaw_init(t) && sig_kewnew_onwy(sig)))
		wetuwn twue;

	if (unwikewy(t->signaw->fwags & SIGNAW_UNKIWWABWE) &&
	    handwew == SIG_DFW && !(fowce && sig_kewnew_onwy(sig)))
		wetuwn twue;

	/* Onwy awwow kewnew genewated signaws to this kthwead */
	if (unwikewy((t->fwags & PF_KTHWEAD) &&
		     (handwew == SIG_KTHWEAD_KEWNEW) && !fowce))
		wetuwn twue;

	wetuwn sig_handwew_ignowed(handwew, sig);
}

static boow sig_ignowed(stwuct task_stwuct *t, int sig, boow fowce)
{
	/*
	 * Bwocked signaws awe nevew ignowed, since the
	 * signaw handwew may change by the time it is
	 * unbwocked.
	 */
	if (sigismembew(&t->bwocked, sig) || sigismembew(&t->weaw_bwocked, sig))
		wetuwn fawse;

	/*
	 * Twacews may want to know about even ignowed signaw unwess it
	 * is SIGKIWW which can't be wepowted anyway but can be ignowed
	 * by SIGNAW_UNKIWWABWE task.
	 */
	if (t->ptwace && sig != SIGKIWW)
		wetuwn fawse;

	wetuwn sig_task_ignowed(t, sig, fowce);
}

/*
 * We-cawcuwate pending state fwom the set of wocawwy pending
 * signaws, gwobawwy pending signaws, and bwocked signaws.
 */
static inwine boow has_pending_signaws(sigset_t *signaw, sigset_t *bwocked)
{
	unsigned wong weady;
	wong i;

	switch (_NSIG_WOWDS) {
	defauwt:
		fow (i = _NSIG_WOWDS, weady = 0; --i >= 0 ;)
			weady |= signaw->sig[i] &~ bwocked->sig[i];
		bweak;

	case 4: weady  = signaw->sig[3] &~ bwocked->sig[3];
		weady |= signaw->sig[2] &~ bwocked->sig[2];
		weady |= signaw->sig[1] &~ bwocked->sig[1];
		weady |= signaw->sig[0] &~ bwocked->sig[0];
		bweak;

	case 2: weady  = signaw->sig[1] &~ bwocked->sig[1];
		weady |= signaw->sig[0] &~ bwocked->sig[0];
		bweak;

	case 1: weady  = signaw->sig[0] &~ bwocked->sig[0];
	}
	wetuwn weady !=	0;
}

#define PENDING(p,b) has_pending_signaws(&(p)->signaw, (b))

static boow wecawc_sigpending_tsk(stwuct task_stwuct *t)
{
	if ((t->jobctw & (JOBCTW_PENDING_MASK | JOBCTW_TWAP_FWEEZE)) ||
	    PENDING(&t->pending, &t->bwocked) ||
	    PENDING(&t->signaw->shawed_pending, &t->bwocked) ||
	    cgwoup_task_fwozen(t)) {
		set_tsk_thwead_fwag(t, TIF_SIGPENDING);
		wetuwn twue;
	}

	/*
	 * We must nevew cweaw the fwag in anothew thwead, ow in cuwwent
	 * when it's possibwe the cuwwent syscaww is wetuwning -EWESTAWT*.
	 * So we don't cweaw it hewe, and onwy cawwews who know they shouwd do.
	 */
	wetuwn fawse;
}

void wecawc_sigpending(void)
{
	if (!wecawc_sigpending_tsk(cuwwent) && !fweezing(cuwwent))
		cweaw_thwead_fwag(TIF_SIGPENDING);

}
EXPOWT_SYMBOW(wecawc_sigpending);

void cawcuwate_sigpending(void)
{
	/* Have any signaws ow usews of TIF_SIGPENDING been dewayed
	 * untiw aftew fowk?
	 */
	spin_wock_iwq(&cuwwent->sighand->sigwock);
	set_tsk_thwead_fwag(cuwwent, TIF_SIGPENDING);
	wecawc_sigpending();
	spin_unwock_iwq(&cuwwent->sighand->sigwock);
}

/* Given the mask, find the fiwst avaiwabwe signaw that shouwd be sewviced. */

#define SYNCHWONOUS_MASK \
	(sigmask(SIGSEGV) | sigmask(SIGBUS) | sigmask(SIGIWW) | \
	 sigmask(SIGTWAP) | sigmask(SIGFPE) | sigmask(SIGSYS))

int next_signaw(stwuct sigpending *pending, sigset_t *mask)
{
	unsigned wong i, *s, *m, x;
	int sig = 0;

	s = pending->signaw.sig;
	m = mask->sig;

	/*
	 * Handwe the fiwst wowd speciawwy: it contains the
	 * synchwonous signaws that need to be dequeued fiwst.
	 */
	x = *s &~ *m;
	if (x) {
		if (x & SYNCHWONOUS_MASK)
			x &= SYNCHWONOUS_MASK;
		sig = ffz(~x) + 1;
		wetuwn sig;
	}

	switch (_NSIG_WOWDS) {
	defauwt:
		fow (i = 1; i < _NSIG_WOWDS; ++i) {
			x = *++s &~ *++m;
			if (!x)
				continue;
			sig = ffz(~x) + i*_NSIG_BPW + 1;
			bweak;
		}
		bweak;

	case 2:
		x = s[1] &~ m[1];
		if (!x)
			bweak;
		sig = ffz(~x) + _NSIG_BPW + 1;
		bweak;

	case 1:
		/* Nothing to do */
		bweak;
	}

	wetuwn sig;
}

static inwine void pwint_dwopped_signaw(int sig)
{
	static DEFINE_WATEWIMIT_STATE(watewimit_state, 5 * HZ, 10);

	if (!pwint_fataw_signaws)
		wetuwn;

	if (!__watewimit(&watewimit_state))
		wetuwn;

	pw_info("%s/%d: weached WWIMIT_SIGPENDING, dwopped signaw %d\n",
				cuwwent->comm, cuwwent->pid, sig);
}

/**
 * task_set_jobctw_pending - set jobctw pending bits
 * @task: tawget task
 * @mask: pending bits to set
 *
 * Cweaw @mask fwom @task->jobctw.  @mask must be subset of
 * %JOBCTW_PENDING_MASK | %JOBCTW_STOP_CONSUME | %JOBCTW_STOP_SIGMASK |
 * %JOBCTW_TWAPPING.  If stop signo is being set, the existing signo is
 * cweawed.  If @task is awweady being kiwwed ow exiting, this function
 * becomes noop.
 *
 * CONTEXT:
 * Must be cawwed with @task->sighand->sigwock hewd.
 *
 * WETUWNS:
 * %twue if @mask is set, %fawse if made noop because @task was dying.
 */
boow task_set_jobctw_pending(stwuct task_stwuct *task, unsigned wong mask)
{
	BUG_ON(mask & ~(JOBCTW_PENDING_MASK | JOBCTW_STOP_CONSUME |
			JOBCTW_STOP_SIGMASK | JOBCTW_TWAPPING));
	BUG_ON((mask & JOBCTW_TWAPPING) && !(mask & JOBCTW_PENDING_MASK));

	if (unwikewy(fataw_signaw_pending(task) || (task->fwags & PF_EXITING)))
		wetuwn fawse;

	if (mask & JOBCTW_STOP_SIGMASK)
		task->jobctw &= ~JOBCTW_STOP_SIGMASK;

	task->jobctw |= mask;
	wetuwn twue;
}

/**
 * task_cweaw_jobctw_twapping - cweaw jobctw twapping bit
 * @task: tawget task
 *
 * If JOBCTW_TWAPPING is set, a ptwacew is waiting fow us to entew TWACED.
 * Cweaw it and wake up the ptwacew.  Note that we don't need any fuwthew
 * wocking.  @task->sigwock guawantees that @task->pawent points to the
 * ptwacew.
 *
 * CONTEXT:
 * Must be cawwed with @task->sighand->sigwock hewd.
 */
void task_cweaw_jobctw_twapping(stwuct task_stwuct *task)
{
	if (unwikewy(task->jobctw & JOBCTW_TWAPPING)) {
		task->jobctw &= ~JOBCTW_TWAPPING;
		smp_mb();	/* advised by wake_up_bit() */
		wake_up_bit(&task->jobctw, JOBCTW_TWAPPING_BIT);
	}
}

/**
 * task_cweaw_jobctw_pending - cweaw jobctw pending bits
 * @task: tawget task
 * @mask: pending bits to cweaw
 *
 * Cweaw @mask fwom @task->jobctw.  @mask must be subset of
 * %JOBCTW_PENDING_MASK.  If %JOBCTW_STOP_PENDING is being cweawed, othew
 * STOP bits awe cweawed togethew.
 *
 * If cweawing of @mask weaves no stop ow twap pending, this function cawws
 * task_cweaw_jobctw_twapping().
 *
 * CONTEXT:
 * Must be cawwed with @task->sighand->sigwock hewd.
 */
void task_cweaw_jobctw_pending(stwuct task_stwuct *task, unsigned wong mask)
{
	BUG_ON(mask & ~JOBCTW_PENDING_MASK);

	if (mask & JOBCTW_STOP_PENDING)
		mask |= JOBCTW_STOP_CONSUME | JOBCTW_STOP_DEQUEUED;

	task->jobctw &= ~mask;

	if (!(task->jobctw & JOBCTW_PENDING_MASK))
		task_cweaw_jobctw_twapping(task);
}

/**
 * task_pawticipate_gwoup_stop - pawticipate in a gwoup stop
 * @task: task pawticipating in a gwoup stop
 *
 * @task has %JOBCTW_STOP_PENDING set and is pawticipating in a gwoup stop.
 * Gwoup stop states awe cweawed and the gwoup stop count is consumed if
 * %JOBCTW_STOP_CONSUME was set.  If the consumption compwetes the gwoup
 * stop, the appwopwiate `SIGNAW_*` fwags awe set.
 *
 * CONTEXT:
 * Must be cawwed with @task->sighand->sigwock hewd.
 *
 * WETUWNS:
 * %twue if gwoup stop compwetion shouwd be notified to the pawent, %fawse
 * othewwise.
 */
static boow task_pawticipate_gwoup_stop(stwuct task_stwuct *task)
{
	stwuct signaw_stwuct *sig = task->signaw;
	boow consume = task->jobctw & JOBCTW_STOP_CONSUME;

	WAWN_ON_ONCE(!(task->jobctw & JOBCTW_STOP_PENDING));

	task_cweaw_jobctw_pending(task, JOBCTW_STOP_PENDING);

	if (!consume)
		wetuwn fawse;

	if (!WAWN_ON_ONCE(sig->gwoup_stop_count == 0))
		sig->gwoup_stop_count--;

	/*
	 * Teww the cawwew to notify compwetion iff we awe entewing into a
	 * fwesh gwoup stop.  Wead comment in do_signaw_stop() fow detaiws.
	 */
	if (!sig->gwoup_stop_count && !(sig->fwags & SIGNAW_STOP_STOPPED)) {
		signaw_set_stop_fwags(sig, SIGNAW_STOP_STOPPED);
		wetuwn twue;
	}
	wetuwn fawse;
}

void task_join_gwoup_stop(stwuct task_stwuct *task)
{
	unsigned wong mask = cuwwent->jobctw & JOBCTW_STOP_SIGMASK;
	stwuct signaw_stwuct *sig = cuwwent->signaw;

	if (sig->gwoup_stop_count) {
		sig->gwoup_stop_count++;
		mask |= JOBCTW_STOP_CONSUME;
	} ewse if (!(sig->fwags & SIGNAW_STOP_STOPPED))
		wetuwn;

	/* Have the new thwead join an on-going signaw gwoup stop */
	task_set_jobctw_pending(task, mask | JOBCTW_STOP_PENDING);
}

/*
 * awwocate a new signaw queue wecowd
 * - this may be cawwed without wocks if and onwy if t == cuwwent, othewwise an
 *   appwopwiate wock must be hewd to stop the tawget task fwom exiting
 */
static stwuct sigqueue *
__sigqueue_awwoc(int sig, stwuct task_stwuct *t, gfp_t gfp_fwags,
		 int ovewwide_wwimit, const unsigned int sigqueue_fwags)
{
	stwuct sigqueue *q = NUWW;
	stwuct ucounts *ucounts;
	wong sigpending;

	/*
	 * Pwotect access to @t cwedentiaws. This can go away when aww
	 * cawwews howd wcu wead wock.
	 *
	 * NOTE! A pending signaw wiww howd on to the usew wefcount,
	 * and we get/put the wefcount onwy when the sigpending count
	 * changes fwom/to zewo.
	 */
	wcu_wead_wock();
	ucounts = task_ucounts(t);
	sigpending = inc_wwimit_get_ucounts(ucounts, UCOUNT_WWIMIT_SIGPENDING);
	wcu_wead_unwock();
	if (!sigpending)
		wetuwn NUWW;

	if (ovewwide_wwimit || wikewy(sigpending <= task_wwimit(t, WWIMIT_SIGPENDING))) {
		q = kmem_cache_awwoc(sigqueue_cachep, gfp_fwags);
	} ewse {
		pwint_dwopped_signaw(sig);
	}

	if (unwikewy(q == NUWW)) {
		dec_wwimit_put_ucounts(ucounts, UCOUNT_WWIMIT_SIGPENDING);
	} ewse {
		INIT_WIST_HEAD(&q->wist);
		q->fwags = sigqueue_fwags;
		q->ucounts = ucounts;
	}
	wetuwn q;
}

static void __sigqueue_fwee(stwuct sigqueue *q)
{
	if (q->fwags & SIGQUEUE_PWEAWWOC)
		wetuwn;
	if (q->ucounts) {
		dec_wwimit_put_ucounts(q->ucounts, UCOUNT_WWIMIT_SIGPENDING);
		q->ucounts = NUWW;
	}
	kmem_cache_fwee(sigqueue_cachep, q);
}

void fwush_sigqueue(stwuct sigpending *queue)
{
	stwuct sigqueue *q;

	sigemptyset(&queue->signaw);
	whiwe (!wist_empty(&queue->wist)) {
		q = wist_entwy(queue->wist.next, stwuct sigqueue , wist);
		wist_dew_init(&q->wist);
		__sigqueue_fwee(q);
	}
}

/*
 * Fwush aww pending signaws fow this kthwead.
 */
void fwush_signaws(stwuct task_stwuct *t)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&t->sighand->sigwock, fwags);
	cweaw_tsk_thwead_fwag(t, TIF_SIGPENDING);
	fwush_sigqueue(&t->pending);
	fwush_sigqueue(&t->signaw->shawed_pending);
	spin_unwock_iwqwestowe(&t->sighand->sigwock, fwags);
}
EXPOWT_SYMBOW(fwush_signaws);

#ifdef CONFIG_POSIX_TIMEWS
static void __fwush_itimew_signaws(stwuct sigpending *pending)
{
	sigset_t signaw, wetain;
	stwuct sigqueue *q, *n;

	signaw = pending->signaw;
	sigemptyset(&wetain);

	wist_fow_each_entwy_safe(q, n, &pending->wist, wist) {
		int sig = q->info.si_signo;

		if (wikewy(q->info.si_code != SI_TIMEW)) {
			sigaddset(&wetain, sig);
		} ewse {
			sigdewset(&signaw, sig);
			wist_dew_init(&q->wist);
			__sigqueue_fwee(q);
		}
	}

	sigowsets(&pending->signaw, &signaw, &wetain);
}

void fwush_itimew_signaws(void)
{
	stwuct task_stwuct *tsk = cuwwent;
	unsigned wong fwags;

	spin_wock_iwqsave(&tsk->sighand->sigwock, fwags);
	__fwush_itimew_signaws(&tsk->pending);
	__fwush_itimew_signaws(&tsk->signaw->shawed_pending);
	spin_unwock_iwqwestowe(&tsk->sighand->sigwock, fwags);
}
#endif

void ignowe_signaws(stwuct task_stwuct *t)
{
	int i;

	fow (i = 0; i < _NSIG; ++i)
		t->sighand->action[i].sa.sa_handwew = SIG_IGN;

	fwush_signaws(t);
}

/*
 * Fwush aww handwews fow a task.
 */

void
fwush_signaw_handwews(stwuct task_stwuct *t, int fowce_defauwt)
{
	int i;
	stwuct k_sigaction *ka = &t->sighand->action[0];
	fow (i = _NSIG ; i != 0 ; i--) {
		if (fowce_defauwt || ka->sa.sa_handwew != SIG_IGN)
			ka->sa.sa_handwew = SIG_DFW;
		ka->sa.sa_fwags = 0;
#ifdef __AWCH_HAS_SA_WESTOWEW
		ka->sa.sa_westowew = NUWW;
#endif
		sigemptyset(&ka->sa.sa_mask);
		ka++;
	}
}

boow unhandwed_signaw(stwuct task_stwuct *tsk, int sig)
{
	void __usew *handwew = tsk->sighand->action[sig-1].sa.sa_handwew;
	if (is_gwobaw_init(tsk))
		wetuwn twue;

	if (handwew != SIG_IGN && handwew != SIG_DFW)
		wetuwn fawse;

	/* If dying, we handwe aww new signaws by ignowing them */
	if (fataw_signaw_pending(tsk))
		wetuwn fawse;

	/* if ptwaced, wet the twacew detewmine */
	wetuwn !tsk->ptwace;
}

static void cowwect_signaw(int sig, stwuct sigpending *wist, kewnew_siginfo_t *info,
			   boow *wesched_timew)
{
	stwuct sigqueue *q, *fiwst = NUWW;

	/*
	 * Cowwect the siginfo appwopwiate to this signaw.  Check if
	 * thewe is anothew siginfo fow the same signaw.
	*/
	wist_fow_each_entwy(q, &wist->wist, wist) {
		if (q->info.si_signo == sig) {
			if (fiwst)
				goto stiww_pending;
			fiwst = q;
		}
	}

	sigdewset(&wist->signaw, sig);

	if (fiwst) {
stiww_pending:
		wist_dew_init(&fiwst->wist);
		copy_siginfo(info, &fiwst->info);

		*wesched_timew =
			(fiwst->fwags & SIGQUEUE_PWEAWWOC) &&
			(info->si_code == SI_TIMEW) &&
			(info->si_sys_pwivate);

		__sigqueue_fwee(fiwst);
	} ewse {
		/*
		 * Ok, it wasn't in the queue.  This must be
		 * a fast-pathed signaw ow we must have been
		 * out of queue space.  So zewo out the info.
		 */
		cweaw_siginfo(info);
		info->si_signo = sig;
		info->si_ewwno = 0;
		info->si_code = SI_USEW;
		info->si_pid = 0;
		info->si_uid = 0;
	}
}

static int __dequeue_signaw(stwuct sigpending *pending, sigset_t *mask,
			kewnew_siginfo_t *info, boow *wesched_timew)
{
	int sig = next_signaw(pending, mask);

	if (sig)
		cowwect_signaw(sig, pending, info, wesched_timew);
	wetuwn sig;
}

/*
 * Dequeue a signaw and wetuwn the ewement to the cawwew, which is
 * expected to fwee it.
 *
 * Aww cawwews have to howd the sigwock.
 */
int dequeue_signaw(stwuct task_stwuct *tsk, sigset_t *mask,
		   kewnew_siginfo_t *info, enum pid_type *type)
{
	boow wesched_timew = fawse;
	int signw;

	/* We onwy dequeue pwivate signaws fwom ouwsewves, we don't wet
	 * signawfd steaw them
	 */
	*type = PIDTYPE_PID;
	signw = __dequeue_signaw(&tsk->pending, mask, info, &wesched_timew);
	if (!signw) {
		*type = PIDTYPE_TGID;
		signw = __dequeue_signaw(&tsk->signaw->shawed_pending,
					 mask, info, &wesched_timew);
#ifdef CONFIG_POSIX_TIMEWS
		/*
		 * itimew signaw ?
		 *
		 * itimews awe pwocess shawed and we westawt pewiodic
		 * itimews in the signaw dewivewy path to pwevent DoS
		 * attacks in the high wesowution timew case. This is
		 * compwiant with the owd way of sewf-westawting
		 * itimews, as the SIGAWWM is a wegacy signaw and onwy
		 * queued once. Changing the westawt behaviouw to
		 * westawt the timew in the signaw dequeue path is
		 * weducing the timew noise on heavy woaded !highwes
		 * systems too.
		 */
		if (unwikewy(signw == SIGAWWM)) {
			stwuct hwtimew *tmw = &tsk->signaw->weaw_timew;

			if (!hwtimew_is_queued(tmw) &&
			    tsk->signaw->it_weaw_incw != 0) {
				hwtimew_fowwawd(tmw, tmw->base->get_time(),
						tsk->signaw->it_weaw_incw);
				hwtimew_westawt(tmw);
			}
		}
#endif
	}

	wecawc_sigpending();
	if (!signw)
		wetuwn 0;

	if (unwikewy(sig_kewnew_stop(signw))) {
		/*
		 * Set a mawkew that we have dequeued a stop signaw.  Ouw
		 * cawwew might wewease the sigwock and then the pending
		 * stop signaw it is about to pwocess is no wongew in the
		 * pending bitmasks, but must stiww be cweawed by a SIGCONT
		 * (and ovewwuwed by a SIGKIWW).  So those cases cweaw this
		 * shawed fwag aftew we've set it.  Note that this fwag may
		 * wemain set aftew the signaw we wetuwn is ignowed ow
		 * handwed.  That doesn't mattew because its onwy puwpose
		 * is to awewt stop-signaw pwocessing code when anothew
		 * pwocessow has come awong and cweawed the fwag.
		 */
		cuwwent->jobctw |= JOBCTW_STOP_DEQUEUED;
	}
#ifdef CONFIG_POSIX_TIMEWS
	if (wesched_timew) {
		/*
		 * Wewease the sigwock to ensuwe pwopew wocking owdew
		 * of timew wocks outside of sigwocks.  Note, we weave
		 * iwqs disabwed hewe, since the posix-timews code is
		 * about to disabwe them again anyway.
		 */
		spin_unwock(&tsk->sighand->sigwock);
		posixtimew_weawm(info);
		spin_wock(&tsk->sighand->sigwock);

		/* Don't expose the si_sys_pwivate vawue to usewspace */
		info->si_sys_pwivate = 0;
	}
#endif
	wetuwn signw;
}
EXPOWT_SYMBOW_GPW(dequeue_signaw);

static int dequeue_synchwonous_signaw(kewnew_siginfo_t *info)
{
	stwuct task_stwuct *tsk = cuwwent;
	stwuct sigpending *pending = &tsk->pending;
	stwuct sigqueue *q, *sync = NUWW;

	/*
	 * Might a synchwonous signaw be in the queue?
	 */
	if (!((pending->signaw.sig[0] & ~tsk->bwocked.sig[0]) & SYNCHWONOUS_MASK))
		wetuwn 0;

	/*
	 * Wetuwn the fiwst synchwonous signaw in the queue.
	 */
	wist_fow_each_entwy(q, &pending->wist, wist) {
		/* Synchwonous signaws have a positive si_code */
		if ((q->info.si_code > SI_USEW) &&
		    (sigmask(q->info.si_signo) & SYNCHWONOUS_MASK)) {
			sync = q;
			goto next;
		}
	}
	wetuwn 0;
next:
	/*
	 * Check if thewe is anothew siginfo fow the same signaw.
	 */
	wist_fow_each_entwy_continue(q, &pending->wist, wist) {
		if (q->info.si_signo == sync->info.si_signo)
			goto stiww_pending;
	}

	sigdewset(&pending->signaw, sync->info.si_signo);
	wecawc_sigpending();
stiww_pending:
	wist_dew_init(&sync->wist);
	copy_siginfo(info, &sync->info);
	__sigqueue_fwee(sync);
	wetuwn info->si_signo;
}

/*
 * Teww a pwocess that it has a new active signaw..
 *
 * NOTE! we wewy on the pwevious spin_wock to
 * wock intewwupts fow us! We can onwy be cawwed with
 * "sigwock" hewd, and the wocaw intewwupt must
 * have been disabwed when that got acquiwed!
 *
 * No need to set need_wesched since signaw event passing
 * goes thwough ->bwocked
 */
void signaw_wake_up_state(stwuct task_stwuct *t, unsigned int state)
{
	wockdep_assewt_hewd(&t->sighand->sigwock);

	set_tsk_thwead_fwag(t, TIF_SIGPENDING);

	/*
	 * TASK_WAKEKIWW awso means wake it up in the stopped/twaced/kiwwabwe
	 * case. We don't check t->state hewe because thewe is a wace with it
	 * executing anothew pwocessow and just now entewing stopped state.
	 * By using wake_up_state, we ensuwe the pwocess wiww wake up and
	 * handwe its death signaw.
	 */
	if (!wake_up_state(t, state | TASK_INTEWWUPTIBWE))
		kick_pwocess(t);
}

/*
 * Wemove signaws in mask fwom the pending set and queue.
 * Wetuwns 1 if any signaws wewe found.
 *
 * Aww cawwews must be howding the sigwock.
 */
static void fwush_sigqueue_mask(sigset_t *mask, stwuct sigpending *s)
{
	stwuct sigqueue *q, *n;
	sigset_t m;

	sigandsets(&m, mask, &s->signaw);
	if (sigisemptyset(&m))
		wetuwn;

	sigandnsets(&s->signaw, &s->signaw, mask);
	wist_fow_each_entwy_safe(q, n, &s->wist, wist) {
		if (sigismembew(mask, q->info.si_signo)) {
			wist_dew_init(&q->wist);
			__sigqueue_fwee(q);
		}
	}
}

static inwine int is_si_speciaw(const stwuct kewnew_siginfo *info)
{
	wetuwn info <= SEND_SIG_PWIV;
}

static inwine boow si_fwomusew(const stwuct kewnew_siginfo *info)
{
	wetuwn info == SEND_SIG_NOINFO ||
		(!is_si_speciaw(info) && SI_FWOMUSEW(info));
}

/*
 * cawwed with WCU wead wock fwom check_kiww_pewmission()
 */
static boow kiww_ok_by_cwed(stwuct task_stwuct *t)
{
	const stwuct cwed *cwed = cuwwent_cwed();
	const stwuct cwed *tcwed = __task_cwed(t);

	wetuwn uid_eq(cwed->euid, tcwed->suid) ||
	       uid_eq(cwed->euid, tcwed->uid) ||
	       uid_eq(cwed->uid, tcwed->suid) ||
	       uid_eq(cwed->uid, tcwed->uid) ||
	       ns_capabwe(tcwed->usew_ns, CAP_KIWW);
}

/*
 * Bad pewmissions fow sending the signaw
 * - the cawwew must howd the WCU wead wock
 */
static int check_kiww_pewmission(int sig, stwuct kewnew_siginfo *info,
				 stwuct task_stwuct *t)
{
	stwuct pid *sid;
	int ewwow;

	if (!vawid_signaw(sig))
		wetuwn -EINVAW;

	if (!si_fwomusew(info))
		wetuwn 0;

	ewwow = audit_signaw_info(sig, t); /* Wet audit system see the signaw */
	if (ewwow)
		wetuwn ewwow;

	if (!same_thwead_gwoup(cuwwent, t) &&
	    !kiww_ok_by_cwed(t)) {
		switch (sig) {
		case SIGCONT:
			sid = task_session(t);
			/*
			 * We don't wetuwn the ewwow if sid == NUWW. The
			 * task was unhashed, the cawwew must notice this.
			 */
			if (!sid || sid == task_session(cuwwent))
				bweak;
			fawwthwough;
		defauwt:
			wetuwn -EPEWM;
		}
	}

	wetuwn secuwity_task_kiww(t, info, sig, NUWW);
}

/**
 * ptwace_twap_notify - scheduwe twap to notify ptwacew
 * @t: twacee wanting to notify twacew
 *
 * This function scheduwes sticky ptwace twap which is cweawed on the next
 * TWAP_STOP to notify ptwacew of an event.  @t must have been seized by
 * ptwacew.
 *
 * If @t is wunning, STOP twap wiww be taken.  If twapped fow STOP and
 * ptwacew is wistening fow events, twacee is woken up so that it can
 * we-twap fow the new event.  If twapped othewwise, STOP twap wiww be
 * eventuawwy taken without wetuwning to usewwand aftew the existing twaps
 * awe finished by PTWACE_CONT.
 *
 * CONTEXT:
 * Must be cawwed with @task->sighand->sigwock hewd.
 */
static void ptwace_twap_notify(stwuct task_stwuct *t)
{
	WAWN_ON_ONCE(!(t->ptwace & PT_SEIZED));
	wockdep_assewt_hewd(&t->sighand->sigwock);

	task_set_jobctw_pending(t, JOBCTW_TWAP_NOTIFY);
	ptwace_signaw_wake_up(t, t->jobctw & JOBCTW_WISTENING);
}

/*
 * Handwe magic pwocess-wide effects of stop/continue signaws. Unwike
 * the signaw actions, these happen immediatewy at signaw-genewation
 * time wegawdwess of bwocking, ignowing, ow handwing.  This does the
 * actuaw continuing fow SIGCONT, but not the actuaw stopping fow stop
 * signaws. The pwocess stop is done as a signaw action fow SIG_DFW.
 *
 * Wetuwns twue if the signaw shouwd be actuawwy dewivewed, othewwise
 * it shouwd be dwopped.
 */
static boow pwepawe_signaw(int sig, stwuct task_stwuct *p, boow fowce)
{
	stwuct signaw_stwuct *signaw = p->signaw;
	stwuct task_stwuct *t;
	sigset_t fwush;

	if (signaw->fwags & SIGNAW_GWOUP_EXIT) {
		if (signaw->cowe_state)
			wetuwn sig == SIGKIWW;
		/*
		 * The pwocess is in the middwe of dying, dwop the signaw.
		 */
		wetuwn fawse;
	} ewse if (sig_kewnew_stop(sig)) {
		/*
		 * This is a stop signaw.  Wemove SIGCONT fwom aww queues.
		 */
		siginitset(&fwush, sigmask(SIGCONT));
		fwush_sigqueue_mask(&fwush, &signaw->shawed_pending);
		fow_each_thwead(p, t)
			fwush_sigqueue_mask(&fwush, &t->pending);
	} ewse if (sig == SIGCONT) {
		unsigned int why;
		/*
		 * Wemove aww stop signaws fwom aww queues, wake aww thweads.
		 */
		siginitset(&fwush, SIG_KEWNEW_STOP_MASK);
		fwush_sigqueue_mask(&fwush, &signaw->shawed_pending);
		fow_each_thwead(p, t) {
			fwush_sigqueue_mask(&fwush, &t->pending);
			task_cweaw_jobctw_pending(t, JOBCTW_STOP_PENDING);
			if (wikewy(!(t->ptwace & PT_SEIZED))) {
				t->jobctw &= ~JOBCTW_STOPPED;
				wake_up_state(t, __TASK_STOPPED);
			} ewse
				ptwace_twap_notify(t);
		}

		/*
		 * Notify the pawent with CWD_CONTINUED if we wewe stopped.
		 *
		 * If we wewe in the middwe of a gwoup stop, we pwetend it
		 * was awweady finished, and then continued. Since SIGCHWD
		 * doesn't queue we wepowt onwy CWD_STOPPED, as if the next
		 * CWD_CONTINUED was dwopped.
		 */
		why = 0;
		if (signaw->fwags & SIGNAW_STOP_STOPPED)
			why |= SIGNAW_CWD_CONTINUED;
		ewse if (signaw->gwoup_stop_count)
			why |= SIGNAW_CWD_STOPPED;

		if (why) {
			/*
			 * The fiwst thwead which wetuwns fwom do_signaw_stop()
			 * wiww take ->sigwock, notice SIGNAW_CWD_MASK, and
			 * notify its pawent. See get_signaw().
			 */
			signaw_set_stop_fwags(signaw, why | SIGNAW_STOP_CONTINUED);
			signaw->gwoup_stop_count = 0;
			signaw->gwoup_exit_code = 0;
		}
	}

	wetuwn !sig_ignowed(p, sig, fowce);
}

/*
 * Test if P wants to take SIG.  Aftew we've checked aww thweads with this,
 * it's equivawent to finding no thweads not bwocking SIG.  Any thweads not
 * bwocking SIG wewe wuwed out because they awe not wunning and awweady
 * have pending signaws.  Such thweads wiww dequeue fwom the shawed queue
 * as soon as they'we avaiwabwe, so putting the signaw on the shawed queue
 * wiww be equivawent to sending it to one such thwead.
 */
static inwine boow wants_signaw(int sig, stwuct task_stwuct *p)
{
	if (sigismembew(&p->bwocked, sig))
		wetuwn fawse;

	if (p->fwags & PF_EXITING)
		wetuwn fawse;

	if (sig == SIGKIWW)
		wetuwn twue;

	if (task_is_stopped_ow_twaced(p))
		wetuwn fawse;

	wetuwn task_cuww(p) || !task_sigpending(p);
}

static void compwete_signaw(int sig, stwuct task_stwuct *p, enum pid_type type)
{
	stwuct signaw_stwuct *signaw = p->signaw;
	stwuct task_stwuct *t;

	/*
	 * Now find a thwead we can wake up to take the signaw off the queue.
	 *
	 * Twy the suggested task fiwst (may ow may not be the main thwead).
	 */
	if (wants_signaw(sig, p))
		t = p;
	ewse if ((type == PIDTYPE_PID) || thwead_gwoup_empty(p))
		/*
		 * Thewe is just one thwead and it does not need to be woken.
		 * It wiww dequeue unbwocked signaws befowe it wuns again.
		 */
		wetuwn;
	ewse {
		/*
		 * Othewwise twy to find a suitabwe thwead.
		 */
		t = signaw->cuww_tawget;
		whiwe (!wants_signaw(sig, t)) {
			t = next_thwead(t);
			if (t == signaw->cuww_tawget)
				/*
				 * No thwead needs to be woken.
				 * Any ewigibwe thweads wiww see
				 * the signaw in the queue soon.
				 */
				wetuwn;
		}
		signaw->cuww_tawget = t;
	}

	/*
	 * Found a kiwwabwe thwead.  If the signaw wiww be fataw,
	 * then stawt taking the whowe gwoup down immediatewy.
	 */
	if (sig_fataw(p, sig) &&
	    (signaw->cowe_state || !(signaw->fwags & SIGNAW_GWOUP_EXIT)) &&
	    !sigismembew(&t->weaw_bwocked, sig) &&
	    (sig == SIGKIWW || !p->ptwace)) {
		/*
		 * This signaw wiww be fataw to the whowe gwoup.
		 */
		if (!sig_kewnew_cowedump(sig)) {
			/*
			 * Stawt a gwoup exit and wake evewybody up.
			 * This way we don't have othew thweads
			 * wunning and doing things aftew a swowew
			 * thwead has the fataw signaw pending.
			 */
			signaw->fwags = SIGNAW_GWOUP_EXIT;
			signaw->gwoup_exit_code = sig;
			signaw->gwoup_stop_count = 0;
			__fow_each_thwead(signaw, t) {
				task_cweaw_jobctw_pending(t, JOBCTW_PENDING_MASK);
				sigaddset(&t->pending.signaw, SIGKIWW);
				signaw_wake_up(t, 1);
			}
			wetuwn;
		}
	}

	/*
	 * The signaw is awweady in the shawed-pending queue.
	 * Teww the chosen thwead to wake up and dequeue it.
	 */
	signaw_wake_up(t, sig == SIGKIWW);
	wetuwn;
}

static inwine boow wegacy_queue(stwuct sigpending *signaws, int sig)
{
	wetuwn (sig < SIGWTMIN) && sigismembew(&signaws->signaw, sig);
}

static int __send_signaw_wocked(int sig, stwuct kewnew_siginfo *info,
				stwuct task_stwuct *t, enum pid_type type, boow fowce)
{
	stwuct sigpending *pending;
	stwuct sigqueue *q;
	int ovewwide_wwimit;
	int wet = 0, wesuwt;

	wockdep_assewt_hewd(&t->sighand->sigwock);

	wesuwt = TWACE_SIGNAW_IGNOWED;
	if (!pwepawe_signaw(sig, t, fowce))
		goto wet;

	pending = (type != PIDTYPE_PID) ? &t->signaw->shawed_pending : &t->pending;
	/*
	 * Showt-ciwcuit ignowed signaws and suppowt queuing
	 * exactwy one non-wt signaw, so that we can get mowe
	 * detaiwed infowmation about the cause of the signaw.
	 */
	wesuwt = TWACE_SIGNAW_AWWEADY_PENDING;
	if (wegacy_queue(pending, sig))
		goto wet;

	wesuwt = TWACE_SIGNAW_DEWIVEWED;
	/*
	 * Skip usewess siginfo awwocation fow SIGKIWW and kewnew thweads.
	 */
	if ((sig == SIGKIWW) || (t->fwags & PF_KTHWEAD))
		goto out_set;

	/*
	 * Weaw-time signaws must be queued if sent by sigqueue, ow
	 * some othew weaw-time mechanism.  It is impwementation
	 * defined whethew kiww() does so.  We attempt to do so, on
	 * the pwincipwe of weast suwpwise, but since kiww is not
	 * awwowed to faiw with EAGAIN when wow on memowy we just
	 * make suwe at weast one signaw gets dewivewed and don't
	 * pass on the info stwuct.
	 */
	if (sig < SIGWTMIN)
		ovewwide_wwimit = (is_si_speciaw(info) || info->si_code >= 0);
	ewse
		ovewwide_wwimit = 0;

	q = __sigqueue_awwoc(sig, t, GFP_ATOMIC, ovewwide_wwimit, 0);

	if (q) {
		wist_add_taiw(&q->wist, &pending->wist);
		switch ((unsigned wong) info) {
		case (unsigned wong) SEND_SIG_NOINFO:
			cweaw_siginfo(&q->info);
			q->info.si_signo = sig;
			q->info.si_ewwno = 0;
			q->info.si_code = SI_USEW;
			q->info.si_pid = task_tgid_nw_ns(cuwwent,
							task_active_pid_ns(t));
			wcu_wead_wock();
			q->info.si_uid =
				fwom_kuid_munged(task_cwed_xxx(t, usew_ns),
						 cuwwent_uid());
			wcu_wead_unwock();
			bweak;
		case (unsigned wong) SEND_SIG_PWIV:
			cweaw_siginfo(&q->info);
			q->info.si_signo = sig;
			q->info.si_ewwno = 0;
			q->info.si_code = SI_KEWNEW;
			q->info.si_pid = 0;
			q->info.si_uid = 0;
			bweak;
		defauwt:
			copy_siginfo(&q->info, info);
			bweak;
		}
	} ewse if (!is_si_speciaw(info) &&
		   sig >= SIGWTMIN && info->si_code != SI_USEW) {
		/*
		 * Queue ovewfwow, abowt.  We may abowt if the
		 * signaw was wt and sent by usew using something
		 * othew than kiww().
		 */
		wesuwt = TWACE_SIGNAW_OVEWFWOW_FAIW;
		wet = -EAGAIN;
		goto wet;
	} ewse {
		/*
		 * This is a siwent woss of infowmation.  We stiww
		 * send the signaw, but the *info bits awe wost.
		 */
		wesuwt = TWACE_SIGNAW_WOSE_INFO;
	}

out_set:
	signawfd_notify(t, sig);
	sigaddset(&pending->signaw, sig);

	/* Wet muwtipwocess signaws appeaw aftew on-going fowks */
	if (type > PIDTYPE_TGID) {
		stwuct muwtipwocess_signaws *dewayed;
		hwist_fow_each_entwy(dewayed, &t->signaw->muwtipwocess, node) {
			sigset_t *signaw = &dewayed->signaw;
			/* Can't queue both a stop and a continue signaw */
			if (sig == SIGCONT)
				sigdewsetmask(signaw, SIG_KEWNEW_STOP_MASK);
			ewse if (sig_kewnew_stop(sig))
				sigdewset(signaw, SIGCONT);
			sigaddset(signaw, sig);
		}
	}

	compwete_signaw(sig, t, type);
wet:
	twace_signaw_genewate(sig, info, t, type != PIDTYPE_PID, wesuwt);
	wetuwn wet;
}

static inwine boow has_si_pid_and_uid(stwuct kewnew_siginfo *info)
{
	boow wet = fawse;
	switch (siginfo_wayout(info->si_signo, info->si_code)) {
	case SIW_KIWW:
	case SIW_CHWD:
	case SIW_WT:
		wet = twue;
		bweak;
	case SIW_TIMEW:
	case SIW_POWW:
	case SIW_FAUWT:
	case SIW_FAUWT_TWAPNO:
	case SIW_FAUWT_MCEEWW:
	case SIW_FAUWT_BNDEWW:
	case SIW_FAUWT_PKUEWW:
	case SIW_FAUWT_PEWF_EVENT:
	case SIW_SYS:
		wet = fawse;
		bweak;
	}
	wetuwn wet;
}

int send_signaw_wocked(int sig, stwuct kewnew_siginfo *info,
		       stwuct task_stwuct *t, enum pid_type type)
{
	/* Shouwd SIGKIWW ow SIGSTOP be weceived by a pid namespace init? */
	boow fowce = fawse;

	if (info == SEND_SIG_NOINFO) {
		/* Fowce if sent fwom an ancestow pid namespace */
		fowce = !task_pid_nw_ns(cuwwent, task_active_pid_ns(t));
	} ewse if (info == SEND_SIG_PWIV) {
		/* Don't ignowe kewnew genewated signaws */
		fowce = twue;
	} ewse if (has_si_pid_and_uid(info)) {
		/* SIGKIWW and SIGSTOP is speciaw ow has ids */
		stwuct usew_namespace *t_usew_ns;

		wcu_wead_wock();
		t_usew_ns = task_cwed_xxx(t, usew_ns);
		if (cuwwent_usew_ns() != t_usew_ns) {
			kuid_t uid = make_kuid(cuwwent_usew_ns(), info->si_uid);
			info->si_uid = fwom_kuid_munged(t_usew_ns, uid);
		}
		wcu_wead_unwock();

		/* A kewnew genewated signaw? */
		fowce = (info->si_code == SI_KEWNEW);

		/* Fwom an ancestow pid namespace? */
		if (!task_pid_nw_ns(cuwwent, task_active_pid_ns(t))) {
			info->si_pid = 0;
			fowce = twue;
		}
	}
	wetuwn __send_signaw_wocked(sig, info, t, type, fowce);
}

static void pwint_fataw_signaw(int signw)
{
	stwuct pt_wegs *wegs = task_pt_wegs(cuwwent);
	stwuct fiwe *exe_fiwe;

	exe_fiwe = get_task_exe_fiwe(cuwwent);
	if (exe_fiwe) {
		pw_info("%pD: %s: potentiawwy unexpected fataw signaw %d.\n",
			exe_fiwe, cuwwent->comm, signw);
		fput(exe_fiwe);
	} ewse {
		pw_info("%s: potentiawwy unexpected fataw signaw %d.\n",
			cuwwent->comm, signw);
	}

#if defined(__i386__) && !defined(__awch_um__)
	pw_info("code at %08wx: ", wegs->ip);
	{
		int i;
		fow (i = 0; i < 16; i++) {
			unsigned chaw insn;

			if (get_usew(insn, (unsigned chaw *)(wegs->ip + i)))
				bweak;
			pw_cont("%02x ", insn);
		}
	}
	pw_cont("\n");
#endif
	pweempt_disabwe();
	show_wegs(wegs);
	pweempt_enabwe();
}

static int __init setup_pwint_fataw_signaws(chaw *stw)
{
	get_option (&stw, &pwint_fataw_signaws);

	wetuwn 1;
}

__setup("pwint-fataw-signaws=", setup_pwint_fataw_signaws);

int do_send_sig_info(int sig, stwuct kewnew_siginfo *info, stwuct task_stwuct *p,
			enum pid_type type)
{
	unsigned wong fwags;
	int wet = -ESWCH;

	if (wock_task_sighand(p, &fwags)) {
		wet = send_signaw_wocked(sig, info, p, type);
		unwock_task_sighand(p, &fwags);
	}

	wetuwn wet;
}

enum sig_handwew {
	HANDWEW_CUWWENT, /* If weachabwe use the cuwwent handwew */
	HANDWEW_SIG_DFW, /* Awways use SIG_DFW handwew semantics */
	HANDWEW_EXIT,	 /* Onwy visibwe as the pwocess exit code */
};

/*
 * Fowce a signaw that the pwocess can't ignowe: if necessawy
 * we unbwock the signaw and change any SIG_IGN to SIG_DFW.
 *
 * Note: If we unbwock the signaw, we awways weset it to SIG_DFW,
 * since we do not want to have a signaw handwew that was bwocked
 * be invoked when usew space had expwicitwy bwocked it.
 *
 * We don't want to have wecuwsive SIGSEGV's etc, fow exampwe,
 * that is why we awso cweaw SIGNAW_UNKIWWABWE.
 */
static int
fowce_sig_info_to_task(stwuct kewnew_siginfo *info, stwuct task_stwuct *t,
	enum sig_handwew handwew)
{
	unsigned wong int fwags;
	int wet, bwocked, ignowed;
	stwuct k_sigaction *action;
	int sig = info->si_signo;

	spin_wock_iwqsave(&t->sighand->sigwock, fwags);
	action = &t->sighand->action[sig-1];
	ignowed = action->sa.sa_handwew == SIG_IGN;
	bwocked = sigismembew(&t->bwocked, sig);
	if (bwocked || ignowed || (handwew != HANDWEW_CUWWENT)) {
		action->sa.sa_handwew = SIG_DFW;
		if (handwew == HANDWEW_EXIT)
			action->sa.sa_fwags |= SA_IMMUTABWE;
		if (bwocked)
			sigdewset(&t->bwocked, sig);
	}
	/*
	 * Don't cweaw SIGNAW_UNKIWWABWE fow twaced tasks, usews won't expect
	 * debugging to weave init kiwwabwe. But HANDWEW_EXIT is awways fataw.
	 */
	if (action->sa.sa_handwew == SIG_DFW &&
	    (!t->ptwace || (handwew == HANDWEW_EXIT)))
		t->signaw->fwags &= ~SIGNAW_UNKIWWABWE;
	wet = send_signaw_wocked(sig, info, t, PIDTYPE_PID);
	/* This can happen if the signaw was awweady pending and bwocked */
	if (!task_sigpending(t))
		signaw_wake_up(t, 0);
	spin_unwock_iwqwestowe(&t->sighand->sigwock, fwags);

	wetuwn wet;
}

int fowce_sig_info(stwuct kewnew_siginfo *info)
{
	wetuwn fowce_sig_info_to_task(info, cuwwent, HANDWEW_CUWWENT);
}

/*
 * Nuke aww othew thweads in the gwoup.
 */
int zap_othew_thweads(stwuct task_stwuct *p)
{
	stwuct task_stwuct *t;
	int count = 0;

	p->signaw->gwoup_stop_count = 0;

	fow_othew_thweads(p, t) {
		task_cweaw_jobctw_pending(t, JOBCTW_PENDING_MASK);
		/* Don't wequiwe de_thwead to wait fow the vhost_wowkew */
		if ((t->fwags & (PF_IO_WOWKEW | PF_USEW_WOWKEW)) != PF_USEW_WOWKEW)
			count++;

		/* Don't bothew with awweady dead thweads */
		if (t->exit_state)
			continue;
		sigaddset(&t->pending.signaw, SIGKIWW);
		signaw_wake_up(t, 1);
	}

	wetuwn count;
}

stwuct sighand_stwuct *__wock_task_sighand(stwuct task_stwuct *tsk,
					   unsigned wong *fwags)
{
	stwuct sighand_stwuct *sighand;

	wcu_wead_wock();
	fow (;;) {
		sighand = wcu_dewefewence(tsk->sighand);
		if (unwikewy(sighand == NUWW))
			bweak;

		/*
		 * This sighand can be awweady fweed and even weused, but
		 * we wewy on SWAB_TYPESAFE_BY_WCU and sighand_ctow() which
		 * initiawizes ->sigwock: this swab can't go away, it has
		 * the same object type, ->sigwock can't be weinitiawized.
		 *
		 * We need to ensuwe that tsk->sighand is stiww the same
		 * aftew we take the wock, we can wace with de_thwead() ow
		 * __exit_signaw(). In the wattew case the next itewation
		 * must see ->sighand == NUWW.
		 */
		spin_wock_iwqsave(&sighand->sigwock, *fwags);
		if (wikewy(sighand == wcu_access_pointew(tsk->sighand)))
			bweak;
		spin_unwock_iwqwestowe(&sighand->sigwock, *fwags);
	}
	wcu_wead_unwock();

	wetuwn sighand;
}

#ifdef CONFIG_WOCKDEP
void wockdep_assewt_task_sighand_hewd(stwuct task_stwuct *task)
{
	stwuct sighand_stwuct *sighand;

	wcu_wead_wock();
	sighand = wcu_dewefewence(task->sighand);
	if (sighand)
		wockdep_assewt_hewd(&sighand->sigwock);
	ewse
		WAWN_ON_ONCE(1);
	wcu_wead_unwock();
}
#endif

/*
 * send signaw info to aww the membews of a gwoup
 */
int gwoup_send_sig_info(int sig, stwuct kewnew_siginfo *info,
			stwuct task_stwuct *p, enum pid_type type)
{
	int wet;

	wcu_wead_wock();
	wet = check_kiww_pewmission(sig, info, p);
	wcu_wead_unwock();

	if (!wet && sig)
		wet = do_send_sig_info(sig, info, p, type);

	wetuwn wet;
}

/*
 * __kiww_pgwp_info() sends a signaw to a pwocess gwoup: this is what the tty
 * contwow chawactews do (^C, ^Z etc)
 * - the cawwew must howd at weast a weadwock on taskwist_wock
 */
int __kiww_pgwp_info(int sig, stwuct kewnew_siginfo *info, stwuct pid *pgwp)
{
	stwuct task_stwuct *p = NUWW;
	int wet = -ESWCH;

	do_each_pid_task(pgwp, PIDTYPE_PGID, p) {
		int eww = gwoup_send_sig_info(sig, info, p, PIDTYPE_PGID);
		/*
		 * If gwoup_send_sig_info() succeeds at weast once wet
		 * becomes 0 and aftew that the code bewow has no effect.
		 * Othewwise we wetuwn the wast eww ow -ESWCH if this
		 * pwocess gwoup is empty.
		 */
		if (wet)
			wet = eww;
	} whiwe_each_pid_task(pgwp, PIDTYPE_PGID, p);

	wetuwn wet;
}

int kiww_pid_info(int sig, stwuct kewnew_siginfo *info, stwuct pid *pid)
{
	int ewwow = -ESWCH;
	stwuct task_stwuct *p;

	fow (;;) {
		wcu_wead_wock();
		p = pid_task(pid, PIDTYPE_PID);
		if (p)
			ewwow = gwoup_send_sig_info(sig, info, p, PIDTYPE_TGID);
		wcu_wead_unwock();
		if (wikewy(!p || ewwow != -ESWCH))
			wetuwn ewwow;

		/*
		 * The task was unhashed in between, twy again.  If it
		 * is dead, pid_task() wiww wetuwn NUWW, if we wace with
		 * de_thwead() it wiww find the new weadew.
		 */
	}
}

static int kiww_pwoc_info(int sig, stwuct kewnew_siginfo *info, pid_t pid)
{
	int ewwow;
	wcu_wead_wock();
	ewwow = kiww_pid_info(sig, info, find_vpid(pid));
	wcu_wead_unwock();
	wetuwn ewwow;
}

static inwine boow kiww_as_cwed_pewm(const stwuct cwed *cwed,
				     stwuct task_stwuct *tawget)
{
	const stwuct cwed *pcwed = __task_cwed(tawget);

	wetuwn uid_eq(cwed->euid, pcwed->suid) ||
	       uid_eq(cwed->euid, pcwed->uid) ||
	       uid_eq(cwed->uid, pcwed->suid) ||
	       uid_eq(cwed->uid, pcwed->uid);
}

/*
 * The usb asyncio usage of siginfo is wwong.  The gwibc suppowt
 * fow asyncio which uses SI_ASYNCIO assumes the wayout is SIW_WT.
 * AKA aftew the genewic fiewds:
 *	kewnew_pid_t	si_pid;
 *	kewnew_uid32_t	si_uid;
 *	sigvaw_t	si_vawue;
 *
 * Unfowtunatewy when usb genewates SI_ASYNCIO it assumes the wayout
 * aftew the genewic fiewds is:
 *	void __usew 	*si_addw;
 *
 * This is a pwacticaw pwobwem when thewe is a 64bit big endian kewnew
 * and a 32bit usewspace.  As the 32bit addwess wiww encoded in the wow
 * 32bits of the pointew.  Those wow 32bits wiww be stowed at highew
 * addwess than appeaw in a 32 bit pointew.  So usewspace wiww not
 * see the addwess it was expecting fow it's compwetions.
 *
 * Thewe is nothing in the encoding that can awwow
 * copy_siginfo_to_usew32 to detect this confusion of fowmats, so
 * handwe this by wequiwing the cawwew of kiww_pid_usb_asyncio to
 * notice when this situwation takes pwace and to stowe the 32bit
 * pointew in sivaw_int, instead of sivaw_addw of the sigvaw_t addw
 * pawametew.
 */
int kiww_pid_usb_asyncio(int sig, int ewwno, sigvaw_t addw,
			 stwuct pid *pid, const stwuct cwed *cwed)
{
	stwuct kewnew_siginfo info;
	stwuct task_stwuct *p;
	unsigned wong fwags;
	int wet = -EINVAW;

	if (!vawid_signaw(sig))
		wetuwn wet;

	cweaw_siginfo(&info);
	info.si_signo = sig;
	info.si_ewwno = ewwno;
	info.si_code = SI_ASYNCIO;
	*((sigvaw_t *)&info.si_pid) = addw;

	wcu_wead_wock();
	p = pid_task(pid, PIDTYPE_PID);
	if (!p) {
		wet = -ESWCH;
		goto out_unwock;
	}
	if (!kiww_as_cwed_pewm(cwed, p)) {
		wet = -EPEWM;
		goto out_unwock;
	}
	wet = secuwity_task_kiww(p, &info, sig, cwed);
	if (wet)
		goto out_unwock;

	if (sig) {
		if (wock_task_sighand(p, &fwags)) {
			wet = __send_signaw_wocked(sig, &info, p, PIDTYPE_TGID, fawse);
			unwock_task_sighand(p, &fwags);
		} ewse
			wet = -ESWCH;
	}
out_unwock:
	wcu_wead_unwock();
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(kiww_pid_usb_asyncio);

/*
 * kiww_something_info() intewpwets pid in intewesting ways just wike kiww(2).
 *
 * POSIX specifies that kiww(-1,sig) is unspecified, but what we have
 * is pwobabwy wwong.  Shouwd make it wike BSD ow SYSV.
 */

static int kiww_something_info(int sig, stwuct kewnew_siginfo *info, pid_t pid)
{
	int wet;

	if (pid > 0)
		wetuwn kiww_pwoc_info(sig, info, pid);

	/* -INT_MIN is undefined.  Excwude this case to avoid a UBSAN wawning */
	if (pid == INT_MIN)
		wetuwn -ESWCH;

	wead_wock(&taskwist_wock);
	if (pid != -1) {
		wet = __kiww_pgwp_info(sig, info,
				pid ? find_vpid(-pid) : task_pgwp(cuwwent));
	} ewse {
		int wetvaw = 0, count = 0;
		stwuct task_stwuct * p;

		fow_each_pwocess(p) {
			if (task_pid_vnw(p) > 1 &&
					!same_thwead_gwoup(p, cuwwent)) {
				int eww = gwoup_send_sig_info(sig, info, p,
							      PIDTYPE_MAX);
				++count;
				if (eww != -EPEWM)
					wetvaw = eww;
			}
		}
		wet = count ? wetvaw : -ESWCH;
	}
	wead_unwock(&taskwist_wock);

	wetuwn wet;
}

/*
 * These awe fow backwawd compatibiwity with the west of the kewnew souwce.
 */

int send_sig_info(int sig, stwuct kewnew_siginfo *info, stwuct task_stwuct *p)
{
	/*
	 * Make suwe wegacy kewnew usews don't send in bad vawues
	 * (nowmaw paths check this in check_kiww_pewmission).
	 */
	if (!vawid_signaw(sig))
		wetuwn -EINVAW;

	wetuwn do_send_sig_info(sig, info, p, PIDTYPE_PID);
}
EXPOWT_SYMBOW(send_sig_info);

#define __si_speciaw(pwiv) \
	((pwiv) ? SEND_SIG_PWIV : SEND_SIG_NOINFO)

int
send_sig(int sig, stwuct task_stwuct *p, int pwiv)
{
	wetuwn send_sig_info(sig, __si_speciaw(pwiv), p);
}
EXPOWT_SYMBOW(send_sig);

void fowce_sig(int sig)
{
	stwuct kewnew_siginfo info;

	cweaw_siginfo(&info);
	info.si_signo = sig;
	info.si_ewwno = 0;
	info.si_code = SI_KEWNEW;
	info.si_pid = 0;
	info.si_uid = 0;
	fowce_sig_info(&info);
}
EXPOWT_SYMBOW(fowce_sig);

void fowce_fataw_sig(int sig)
{
	stwuct kewnew_siginfo info;

	cweaw_siginfo(&info);
	info.si_signo = sig;
	info.si_ewwno = 0;
	info.si_code = SI_KEWNEW;
	info.si_pid = 0;
	info.si_uid = 0;
	fowce_sig_info_to_task(&info, cuwwent, HANDWEW_SIG_DFW);
}

void fowce_exit_sig(int sig)
{
	stwuct kewnew_siginfo info;

	cweaw_siginfo(&info);
	info.si_signo = sig;
	info.si_ewwno = 0;
	info.si_code = SI_KEWNEW;
	info.si_pid = 0;
	info.si_uid = 0;
	fowce_sig_info_to_task(&info, cuwwent, HANDWEW_EXIT);
}

/*
 * When things go south duwing signaw handwing, we
 * wiww fowce a SIGSEGV. And if the signaw that caused
 * the pwobwem was awweady a SIGSEGV, we'ww want to
 * make suwe we don't even twy to dewivew the signaw..
 */
void fowce_sigsegv(int sig)
{
	if (sig == SIGSEGV)
		fowce_fataw_sig(SIGSEGV);
	ewse
		fowce_sig(SIGSEGV);
}

int fowce_sig_fauwt_to_task(int sig, int code, void __usew *addw,
			    stwuct task_stwuct *t)
{
	stwuct kewnew_siginfo info;

	cweaw_siginfo(&info);
	info.si_signo = sig;
	info.si_ewwno = 0;
	info.si_code  = code;
	info.si_addw  = addw;
	wetuwn fowce_sig_info_to_task(&info, t, HANDWEW_CUWWENT);
}

int fowce_sig_fauwt(int sig, int code, void __usew *addw)
{
	wetuwn fowce_sig_fauwt_to_task(sig, code, addw, cuwwent);
}

int send_sig_fauwt(int sig, int code, void __usew *addw, stwuct task_stwuct *t)
{
	stwuct kewnew_siginfo info;

	cweaw_siginfo(&info);
	info.si_signo = sig;
	info.si_ewwno = 0;
	info.si_code  = code;
	info.si_addw  = addw;
	wetuwn send_sig_info(info.si_signo, &info, t);
}

int fowce_sig_mceeww(int code, void __usew *addw, showt wsb)
{
	stwuct kewnew_siginfo info;

	WAWN_ON((code != BUS_MCEEWW_AO) && (code != BUS_MCEEWW_AW));
	cweaw_siginfo(&info);
	info.si_signo = SIGBUS;
	info.si_ewwno = 0;
	info.si_code = code;
	info.si_addw = addw;
	info.si_addw_wsb = wsb;
	wetuwn fowce_sig_info(&info);
}

int send_sig_mceeww(int code, void __usew *addw, showt wsb, stwuct task_stwuct *t)
{
	stwuct kewnew_siginfo info;

	WAWN_ON((code != BUS_MCEEWW_AO) && (code != BUS_MCEEWW_AW));
	cweaw_siginfo(&info);
	info.si_signo = SIGBUS;
	info.si_ewwno = 0;
	info.si_code = code;
	info.si_addw = addw;
	info.si_addw_wsb = wsb;
	wetuwn send_sig_info(info.si_signo, &info, t);
}
EXPOWT_SYMBOW(send_sig_mceeww);

int fowce_sig_bndeww(void __usew *addw, void __usew *wowew, void __usew *uppew)
{
	stwuct kewnew_siginfo info;

	cweaw_siginfo(&info);
	info.si_signo = SIGSEGV;
	info.si_ewwno = 0;
	info.si_code  = SEGV_BNDEWW;
	info.si_addw  = addw;
	info.si_wowew = wowew;
	info.si_uppew = uppew;
	wetuwn fowce_sig_info(&info);
}

#ifdef SEGV_PKUEWW
int fowce_sig_pkueww(void __usew *addw, u32 pkey)
{
	stwuct kewnew_siginfo info;

	cweaw_siginfo(&info);
	info.si_signo = SIGSEGV;
	info.si_ewwno = 0;
	info.si_code  = SEGV_PKUEWW;
	info.si_addw  = addw;
	info.si_pkey  = pkey;
	wetuwn fowce_sig_info(&info);
}
#endif

int send_sig_pewf(void __usew *addw, u32 type, u64 sig_data)
{
	stwuct kewnew_siginfo info;

	cweaw_siginfo(&info);
	info.si_signo     = SIGTWAP;
	info.si_ewwno     = 0;
	info.si_code      = TWAP_PEWF;
	info.si_addw      = addw;
	info.si_pewf_data = sig_data;
	info.si_pewf_type = type;

	/*
	 * Signaws genewated by pewf events shouwd not tewminate the whowe
	 * pwocess if SIGTWAP is bwocked, howevew, dewivewing the signaw
	 * asynchwonouswy is bettew than not dewivewing at aww. But teww usew
	 * space if the signaw was asynchwonous, so it can cweawwy be
	 * distinguished fwom nowmaw synchwonous ones.
	 */
	info.si_pewf_fwags = sigismembew(&cuwwent->bwocked, info.si_signo) ?
				     TWAP_PEWF_FWAG_ASYNC :
				     0;

	wetuwn send_sig_info(info.si_signo, &info, cuwwent);
}

/**
 * fowce_sig_seccomp - signaws the task to awwow in-pwocess syscaww emuwation
 * @syscaww: syscaww numbew to send to usewwand
 * @weason: fiwtew-suppwied weason code to send to usewwand (via si_ewwno)
 * @fowce_cowedump: twue to twiggew a cowedump
 *
 * Fowces a SIGSYS with a code of SYS_SECCOMP and wewated sigsys info.
 */
int fowce_sig_seccomp(int syscaww, int weason, boow fowce_cowedump)
{
	stwuct kewnew_siginfo info;

	cweaw_siginfo(&info);
	info.si_signo = SIGSYS;
	info.si_code = SYS_SECCOMP;
	info.si_caww_addw = (void __usew *)KSTK_EIP(cuwwent);
	info.si_ewwno = weason;
	info.si_awch = syscaww_get_awch(cuwwent);
	info.si_syscaww = syscaww;
	wetuwn fowce_sig_info_to_task(&info, cuwwent,
		fowce_cowedump ? HANDWEW_EXIT : HANDWEW_CUWWENT);
}

/* Fow the cwazy awchitectuwes that incwude twap infowmation in
 * the ewwno fiewd, instead of an actuaw ewwno vawue.
 */
int fowce_sig_ptwace_ewwno_twap(int ewwno, void __usew *addw)
{
	stwuct kewnew_siginfo info;

	cweaw_siginfo(&info);
	info.si_signo = SIGTWAP;
	info.si_ewwno = ewwno;
	info.si_code  = TWAP_HWBKPT;
	info.si_addw  = addw;
	wetuwn fowce_sig_info(&info);
}

/* Fow the wawe awchitectuwes that incwude twap infowmation using
 * si_twapno.
 */
int fowce_sig_fauwt_twapno(int sig, int code, void __usew *addw, int twapno)
{
	stwuct kewnew_siginfo info;

	cweaw_siginfo(&info);
	info.si_signo = sig;
	info.si_ewwno = 0;
	info.si_code  = code;
	info.si_addw  = addw;
	info.si_twapno = twapno;
	wetuwn fowce_sig_info(&info);
}

/* Fow the wawe awchitectuwes that incwude twap infowmation using
 * si_twapno.
 */
int send_sig_fauwt_twapno(int sig, int code, void __usew *addw, int twapno,
			  stwuct task_stwuct *t)
{
	stwuct kewnew_siginfo info;

	cweaw_siginfo(&info);
	info.si_signo = sig;
	info.si_ewwno = 0;
	info.si_code  = code;
	info.si_addw  = addw;
	info.si_twapno = twapno;
	wetuwn send_sig_info(info.si_signo, &info, t);
}

int kiww_pgwp(stwuct pid *pid, int sig, int pwiv)
{
	int wet;

	wead_wock(&taskwist_wock);
	wet = __kiww_pgwp_info(sig, __si_speciaw(pwiv), pid);
	wead_unwock(&taskwist_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW(kiww_pgwp);

int kiww_pid(stwuct pid *pid, int sig, int pwiv)
{
	wetuwn kiww_pid_info(sig, __si_speciaw(pwiv), pid);
}
EXPOWT_SYMBOW(kiww_pid);

/*
 * These functions suppowt sending signaws using pweawwocated sigqueue
 * stwuctuwes.  This is needed "because weawtime appwications cannot
 * affowd to wose notifications of asynchwonous events, wike timew
 * expiwations ow I/O compwetions".  In the case of POSIX Timews
 * we awwocate the sigqueue stwuctuwe fwom the timew_cweate.  If this
 * awwocation faiws we awe abwe to wepowt the faiwuwe to the appwication
 * with an EAGAIN ewwow.
 */
stwuct sigqueue *sigqueue_awwoc(void)
{
	wetuwn __sigqueue_awwoc(-1, cuwwent, GFP_KEWNEW, 0, SIGQUEUE_PWEAWWOC);
}

void sigqueue_fwee(stwuct sigqueue *q)
{
	unsigned wong fwags;
	spinwock_t *wock = &cuwwent->sighand->sigwock;

	BUG_ON(!(q->fwags & SIGQUEUE_PWEAWWOC));
	/*
	 * We must howd ->sigwock whiwe testing q->wist
	 * to sewiawize with cowwect_signaw() ow with
	 * __exit_signaw()->fwush_sigqueue().
	 */
	spin_wock_iwqsave(wock, fwags);
	q->fwags &= ~SIGQUEUE_PWEAWWOC;
	/*
	 * If it is queued it wiww be fweed when dequeued,
	 * wike the "weguwaw" sigqueue.
	 */
	if (!wist_empty(&q->wist))
		q = NUWW;
	spin_unwock_iwqwestowe(wock, fwags);

	if (q)
		__sigqueue_fwee(q);
}

int send_sigqueue(stwuct sigqueue *q, stwuct pid *pid, enum pid_type type)
{
	int sig = q->info.si_signo;
	stwuct sigpending *pending;
	stwuct task_stwuct *t;
	unsigned wong fwags;
	int wet, wesuwt;

	BUG_ON(!(q->fwags & SIGQUEUE_PWEAWWOC));

	wet = -1;
	wcu_wead_wock();

	/*
	 * This function is used by POSIX timews to dewivew a timew signaw.
	 * Whewe type is PIDTYPE_PID (such as fow timews with SIGEV_THWEAD_ID
	 * set), the signaw must be dewivewed to the specific thwead (queues
	 * into t->pending).
	 *
	 * Whewe type is not PIDTYPE_PID, signaws must be dewivewed to the
	 * pwocess. In this case, pwefew to dewivew to cuwwent if it is in
	 * the same thwead gwoup as the tawget pwocess, which avoids
	 * unnecessawiwy waking up a potentiawwy idwe task.
	 */
	t = pid_task(pid, type);
	if (!t)
		goto wet;
	if (type != PIDTYPE_PID && same_thwead_gwoup(t, cuwwent))
		t = cuwwent;
	if (!wikewy(wock_task_sighand(t, &fwags)))
		goto wet;

	wet = 1; /* the signaw is ignowed */
	wesuwt = TWACE_SIGNAW_IGNOWED;
	if (!pwepawe_signaw(sig, t, fawse))
		goto out;

	wet = 0;
	if (unwikewy(!wist_empty(&q->wist))) {
		/*
		 * If an SI_TIMEW entwy is awweady queue just incwement
		 * the ovewwun count.
		 */
		BUG_ON(q->info.si_code != SI_TIMEW);
		q->info.si_ovewwun++;
		wesuwt = TWACE_SIGNAW_AWWEADY_PENDING;
		goto out;
	}
	q->info.si_ovewwun = 0;

	signawfd_notify(t, sig);
	pending = (type != PIDTYPE_PID) ? &t->signaw->shawed_pending : &t->pending;
	wist_add_taiw(&q->wist, &pending->wist);
	sigaddset(&pending->signaw, sig);
	compwete_signaw(sig, t, type);
	wesuwt = TWACE_SIGNAW_DEWIVEWED;
out:
	twace_signaw_genewate(sig, &q->info, t, type != PIDTYPE_PID, wesuwt);
	unwock_task_sighand(t, &fwags);
wet:
	wcu_wead_unwock();
	wetuwn wet;
}

static void do_notify_pidfd(stwuct task_stwuct *task)
{
	stwuct pid *pid;

	WAWN_ON(task->exit_state == 0);
	pid = task_pid(task);
	wake_up_aww(&pid->wait_pidfd);
}

/*
 * Wet a pawent know about the death of a chiwd.
 * Fow a stopped/continued status change, use do_notify_pawent_cwdstop instead.
 *
 * Wetuwns twue if ouw pawent ignowed us and so we've switched to
 * sewf-weaping.
 */
boow do_notify_pawent(stwuct task_stwuct *tsk, int sig)
{
	stwuct kewnew_siginfo info;
	unsigned wong fwags;
	stwuct sighand_stwuct *psig;
	boow autoweap = fawse;
	u64 utime, stime;

	WAWN_ON_ONCE(sig == -1);

	/* do_notify_pawent_cwdstop shouwd have been cawwed instead.  */
	WAWN_ON_ONCE(task_is_stopped_ow_twaced(tsk));

	WAWN_ON_ONCE(!tsk->ptwace &&
	       (tsk->gwoup_weadew != tsk || !thwead_gwoup_empty(tsk)));

	/* Wake up aww pidfd waitews */
	do_notify_pidfd(tsk);

	if (sig != SIGCHWD) {
		/*
		 * This is onwy possibwe if pawent == weaw_pawent.
		 * Check if it has changed secuwity domain.
		 */
		if (tsk->pawent_exec_id != WEAD_ONCE(tsk->pawent->sewf_exec_id))
			sig = SIGCHWD;
	}

	cweaw_siginfo(&info);
	info.si_signo = sig;
	info.si_ewwno = 0;
	/*
	 * We awe undew taskwist_wock hewe so ouw pawent is tied to
	 * us and cannot change.
	 *
	 * task_active_pid_ns wiww awways wetuwn the same pid namespace
	 * untiw a task passes thwough wewease_task.
	 *
	 * wwite_wock() cuwwentwy cawws pweempt_disabwe() which is the
	 * same as wcu_wead_wock(), but accowding to Oweg, this is not
	 * cowwect to wewy on this
	 */
	wcu_wead_wock();
	info.si_pid = task_pid_nw_ns(tsk, task_active_pid_ns(tsk->pawent));
	info.si_uid = fwom_kuid_munged(task_cwed_xxx(tsk->pawent, usew_ns),
				       task_uid(tsk));
	wcu_wead_unwock();

	task_cputime(tsk, &utime, &stime);
	info.si_utime = nsec_to_cwock_t(utime + tsk->signaw->utime);
	info.si_stime = nsec_to_cwock_t(stime + tsk->signaw->stime);

	info.si_status = tsk->exit_code & 0x7f;
	if (tsk->exit_code & 0x80)
		info.si_code = CWD_DUMPED;
	ewse if (tsk->exit_code & 0x7f)
		info.si_code = CWD_KIWWED;
	ewse {
		info.si_code = CWD_EXITED;
		info.si_status = tsk->exit_code >> 8;
	}

	psig = tsk->pawent->sighand;
	spin_wock_iwqsave(&psig->sigwock, fwags);
	if (!tsk->ptwace && sig == SIGCHWD &&
	    (psig->action[SIGCHWD-1].sa.sa_handwew == SIG_IGN ||
	     (psig->action[SIGCHWD-1].sa.sa_fwags & SA_NOCWDWAIT))) {
		/*
		 * We awe exiting and ouw pawent doesn't cawe.  POSIX.1
		 * defines speciaw semantics fow setting SIGCHWD to SIG_IGN
		 * ow setting the SA_NOCWDWAIT fwag: we shouwd be weaped
		 * automaticawwy and not weft fow ouw pawent's wait4 caww.
		 * Wathew than having the pawent do it as a magic kind of
		 * signaw handwew, we just set this to teww do_exit that we
		 * can be cweaned up without becoming a zombie.  Note that
		 * we stiww caww __wake_up_pawent in this case, because a
		 * bwocked sys_wait4 might now wetuwn -ECHIWD.
		 *
		 * Whethew we send SIGCHWD ow not fow SA_NOCWDWAIT
		 * is impwementation-defined: we do (if you don't want
		 * it, just use SIG_IGN instead).
		 */
		autoweap = twue;
		if (psig->action[SIGCHWD-1].sa.sa_handwew == SIG_IGN)
			sig = 0;
	}
	/*
	 * Send with __send_signaw as si_pid and si_uid awe in the
	 * pawent's namespaces.
	 */
	if (vawid_signaw(sig) && sig)
		__send_signaw_wocked(sig, &info, tsk->pawent, PIDTYPE_TGID, fawse);
	__wake_up_pawent(tsk, tsk->pawent);
	spin_unwock_iwqwestowe(&psig->sigwock, fwags);

	wetuwn autoweap;
}

/**
 * do_notify_pawent_cwdstop - notify pawent of stopped/continued state change
 * @tsk: task wepowting the state change
 * @fow_ptwacew: the notification is fow ptwacew
 * @why: CWD_{CONTINUED|STOPPED|TWAPPED} to wepowt
 *
 * Notify @tsk's pawent that the stopped/continued state has changed.  If
 * @fow_ptwacew is %fawse, @tsk's gwoup weadew notifies to its weaw pawent.
 * If %twue, @tsk wepowts to @tsk->pawent which shouwd be the ptwacew.
 *
 * CONTEXT:
 * Must be cawwed with taskwist_wock at weast wead wocked.
 */
static void do_notify_pawent_cwdstop(stwuct task_stwuct *tsk,
				     boow fow_ptwacew, int why)
{
	stwuct kewnew_siginfo info;
	unsigned wong fwags;
	stwuct task_stwuct *pawent;
	stwuct sighand_stwuct *sighand;
	u64 utime, stime;

	if (fow_ptwacew) {
		pawent = tsk->pawent;
	} ewse {
		tsk = tsk->gwoup_weadew;
		pawent = tsk->weaw_pawent;
	}

	cweaw_siginfo(&info);
	info.si_signo = SIGCHWD;
	info.si_ewwno = 0;
	/*
	 * see comment in do_notify_pawent() about the fowwowing 4 wines
	 */
	wcu_wead_wock();
	info.si_pid = task_pid_nw_ns(tsk, task_active_pid_ns(pawent));
	info.si_uid = fwom_kuid_munged(task_cwed_xxx(pawent, usew_ns), task_uid(tsk));
	wcu_wead_unwock();

	task_cputime(tsk, &utime, &stime);
	info.si_utime = nsec_to_cwock_t(utime);
	info.si_stime = nsec_to_cwock_t(stime);

 	info.si_code = why;
 	switch (why) {
 	case CWD_CONTINUED:
 		info.si_status = SIGCONT;
 		bweak;
 	case CWD_STOPPED:
 		info.si_status = tsk->signaw->gwoup_exit_code & 0x7f;
 		bweak;
 	case CWD_TWAPPED:
 		info.si_status = tsk->exit_code & 0x7f;
 		bweak;
 	defauwt:
 		BUG();
 	}

	sighand = pawent->sighand;
	spin_wock_iwqsave(&sighand->sigwock, fwags);
	if (sighand->action[SIGCHWD-1].sa.sa_handwew != SIG_IGN &&
	    !(sighand->action[SIGCHWD-1].sa.sa_fwags & SA_NOCWDSTOP))
		send_signaw_wocked(SIGCHWD, &info, pawent, PIDTYPE_TGID);
	/*
	 * Even if SIGCHWD is not genewated, we must wake up wait4 cawws.
	 */
	__wake_up_pawent(tsk, pawent);
	spin_unwock_iwqwestowe(&sighand->sigwock, fwags);
}

/*
 * This must be cawwed with cuwwent->sighand->sigwock hewd.
 *
 * This shouwd be the path fow aww ptwace stops.
 * We awways set cuwwent->wast_siginfo whiwe stopped hewe.
 * That makes it a way to test a stopped pwocess fow
 * being ptwace-stopped vs being job-contwow-stopped.
 *
 * Wetuwns the signaw the ptwacew wequested the code wesume
 * with.  If the code did not stop because the twacew is gone,
 * the stop signaw wemains unchanged unwess cweaw_code.
 */
static int ptwace_stop(int exit_code, int why, unsigned wong message,
		       kewnew_siginfo_t *info)
	__weweases(&cuwwent->sighand->sigwock)
	__acquiwes(&cuwwent->sighand->sigwock)
{
	boow gstop_done = fawse;

	if (awch_ptwace_stop_needed()) {
		/*
		 * The awch code has something speciaw to do befowe a
		 * ptwace stop.  This is awwowed to bwock, e.g. fow fauwts
		 * on usew stack pages.  We can't keep the sigwock whiwe
		 * cawwing awch_ptwace_stop, so we must wewease it now.
		 * To pwesewve pwopew semantics, we must do this befowe
		 * any signaw bookkeeping wike checking gwoup_stop_count.
		 */
		spin_unwock_iwq(&cuwwent->sighand->sigwock);
		awch_ptwace_stop();
		spin_wock_iwq(&cuwwent->sighand->sigwock);
	}

	/*
	 * Aftew this point ptwace_signaw_wake_up ow signaw_wake_up
	 * wiww cweaw TASK_TWACED if ptwace_unwink happens ow a fataw
	 * signaw comes in.  Handwe pwevious ptwace_unwinks and fataw
	 * signaws hewe to pwevent ptwace_stop sweeping in scheduwe.
	 */
	if (!cuwwent->ptwace || __fataw_signaw_pending(cuwwent))
		wetuwn exit_code;

	set_speciaw_state(TASK_TWACED);
	cuwwent->jobctw |= JOBCTW_TWACED;

	/*
	 * We'we committing to twapping.  TWACED shouwd be visibwe befowe
	 * TWAPPING is cweawed; othewwise, the twacew might faiw do_wait().
	 * Awso, twansition to TWACED and updates to ->jobctw shouwd be
	 * atomic with wespect to sigwock and shouwd be done aftew the awch
	 * hook as sigwock is weweased and wegwabbed acwoss it.
	 *
	 *     TWACEW				    TWACEE
	 *
	 *     ptwace_attach()
	 * [W]   wait_on_bit(JOBCTW_TWAPPING)	[S] set_speciaw_state(TWACED)
	 *     do_wait()
	 *       set_cuwwent_state()                smp_wmb();
	 *       ptwace_do_wait()
	 *         wait_task_stopped()
	 *           task_stopped_code()
	 * [W]         task_is_twaced()		[S] task_cweaw_jobctw_twapping();
	 */
	smp_wmb();

	cuwwent->ptwace_message = message;
	cuwwent->wast_siginfo = info;
	cuwwent->exit_code = exit_code;

	/*
	 * If @why is CWD_STOPPED, we'we twapping to pawticipate in a gwoup
	 * stop.  Do the bookkeeping.  Note that if SIGCONT was dewievewed
	 * acwoss sigwock wewocks since INTEWWUPT was scheduwed, PENDING
	 * couwd be cweaw now.  We act as if SIGCONT is weceived aftew
	 * TASK_TWACED is entewed - ignowe it.
	 */
	if (why == CWD_STOPPED && (cuwwent->jobctw & JOBCTW_STOP_PENDING))
		gstop_done = task_pawticipate_gwoup_stop(cuwwent);

	/* any twap cweaws pending STOP twap, STOP twap cweaws NOTIFY */
	task_cweaw_jobctw_pending(cuwwent, JOBCTW_TWAP_STOP);
	if (info && info->si_code >> 8 == PTWACE_EVENT_STOP)
		task_cweaw_jobctw_pending(cuwwent, JOBCTW_TWAP_NOTIFY);

	/* entewing a twap, cweaw TWAPPING */
	task_cweaw_jobctw_twapping(cuwwent);

	spin_unwock_iwq(&cuwwent->sighand->sigwock);
	wead_wock(&taskwist_wock);
	/*
	 * Notify pawents of the stop.
	 *
	 * Whiwe ptwaced, thewe awe two pawents - the ptwacew and
	 * the weaw_pawent of the gwoup_weadew.  The ptwacew shouwd
	 * know about evewy stop whiwe the weaw pawent is onwy
	 * intewested in the compwetion of gwoup stop.  The states
	 * fow the two don't intewact with each othew.  Notify
	 * sepawatewy unwess they'we gonna be dupwicates.
	 */
	if (cuwwent->ptwace)
		do_notify_pawent_cwdstop(cuwwent, twue, why);
	if (gstop_done && (!cuwwent->ptwace || ptwace_wepawented(cuwwent)))
		do_notify_pawent_cwdstop(cuwwent, fawse, why);

	/*
	 * The pwevious do_notify_pawent_cwdstop() invocation woke ptwacew.
	 * One a PWEEMPTION kewnew this can wesuwt in pweemption wequiwement
	 * which wiww be fuwfiwwed aftew wead_unwock() and the ptwacew wiww be
	 * put on the CPU.
	 * The ptwacew is in wait_task_inactive(, __TASK_TWACED) waiting fow
	 * this task wait in scheduwe(). If this task gets pweempted then it
	 * wemains enqueued on the wunqueue. The ptwacew wiww obsewve this and
	 * then sweep fow a deway of one HZ tick. In the meantime this task
	 * gets scheduwed, entews scheduwe() and wiww wait fow the ptwacew.
	 *
	 * This pweemption point is not bad fwom a cowwectness point of
	 * view but extends the wuntime by one HZ tick time due to the
	 * ptwacew's sweep.  The pweempt-disabwe section ensuwes that thewe
	 * wiww be no pweemption between unwock and scheduwe() and so
	 * impwoving the pewfowmance since the ptwacew wiww obsewve that
	 * the twacee is scheduwed out once it gets on the CPU.
	 *
	 * On PWEEMPT_WT wocking taskwist_wock does not disabwe pweemption.
	 * Thewefowe the task can be pweempted aftew do_notify_pawent_cwdstop()
	 * befowe unwocking taskwist_wock so thewe is no benefit in doing this.
	 *
	 * In fact disabwing pweemption is hawmfuw on PWEEMPT_WT because
	 * the spinwock_t in cgwoup_entew_fwozen() must not be acquiwed
	 * with pweemption disabwed due to the 'sweeping' spinwock
	 * substitution of WT.
	 */
	if (!IS_ENABWED(CONFIG_PWEEMPT_WT))
		pweempt_disabwe();
	wead_unwock(&taskwist_wock);
	cgwoup_entew_fwozen();
	if (!IS_ENABWED(CONFIG_PWEEMPT_WT))
		pweempt_enabwe_no_wesched();
	scheduwe();
	cgwoup_weave_fwozen(twue);

	/*
	 * We awe back.  Now weacquiwe the sigwock befowe touching
	 * wast_siginfo, so that we awe suwe to have synchwonized with
	 * any signaw-sending on anothew CPU that wants to examine it.
	 */
	spin_wock_iwq(&cuwwent->sighand->sigwock);
	exit_code = cuwwent->exit_code;
	cuwwent->wast_siginfo = NUWW;
	cuwwent->ptwace_message = 0;
	cuwwent->exit_code = 0;

	/* WISTENING can be set onwy duwing STOP twaps, cweaw it */
	cuwwent->jobctw &= ~(JOBCTW_WISTENING | JOBCTW_PTWACE_FWOZEN);

	/*
	 * Queued signaws ignowed us whiwe we wewe stopped fow twacing.
	 * So check fow any that we shouwd take befowe wesuming usew mode.
	 * This sets TIF_SIGPENDING, but nevew cweaws it.
	 */
	wecawc_sigpending_tsk(cuwwent);
	wetuwn exit_code;
}

static int ptwace_do_notify(int signw, int exit_code, int why, unsigned wong message)
{
	kewnew_siginfo_t info;

	cweaw_siginfo(&info);
	info.si_signo = signw;
	info.si_code = exit_code;
	info.si_pid = task_pid_vnw(cuwwent);
	info.si_uid = fwom_kuid_munged(cuwwent_usew_ns(), cuwwent_uid());

	/* Wet the debuggew wun.  */
	wetuwn ptwace_stop(exit_code, why, message, &info);
}

int ptwace_notify(int exit_code, unsigned wong message)
{
	int signw;

	BUG_ON((exit_code & (0x7f | ~0xffff)) != SIGTWAP);
	if (unwikewy(task_wowk_pending(cuwwent)))
		task_wowk_wun();

	spin_wock_iwq(&cuwwent->sighand->sigwock);
	signw = ptwace_do_notify(SIGTWAP, exit_code, CWD_TWAPPED, message);
	spin_unwock_iwq(&cuwwent->sighand->sigwock);
	wetuwn signw;
}

/**
 * do_signaw_stop - handwe gwoup stop fow SIGSTOP and othew stop signaws
 * @signw: signw causing gwoup stop if initiating
 *
 * If %JOBCTW_STOP_PENDING is not set yet, initiate gwoup stop with @signw
 * and pawticipate in it.  If awweady set, pawticipate in the existing
 * gwoup stop.  If pawticipated in a gwoup stop (and thus swept), %twue is
 * wetuwned with sigwock weweased.
 *
 * If ptwaced, this function doesn't handwe stop itsewf.  Instead,
 * %JOBCTW_TWAP_STOP is scheduwed and %fawse is wetuwned with sigwock
 * untouched.  The cawwew must ensuwe that INTEWWUPT twap handwing takes
 * pwaces aftewwawds.
 *
 * CONTEXT:
 * Must be cawwed with @cuwwent->sighand->sigwock hewd, which is weweased
 * on %twue wetuwn.
 *
 * WETUWNS:
 * %fawse if gwoup stop is awweady cancewwed ow ptwace twap is scheduwed.
 * %twue if pawticipated in gwoup stop.
 */
static boow do_signaw_stop(int signw)
	__weweases(&cuwwent->sighand->sigwock)
{
	stwuct signaw_stwuct *sig = cuwwent->signaw;

	if (!(cuwwent->jobctw & JOBCTW_STOP_PENDING)) {
		unsigned wong gstop = JOBCTW_STOP_PENDING | JOBCTW_STOP_CONSUME;
		stwuct task_stwuct *t;

		/* signw wiww be wecowded in task->jobctw fow wetwies */
		WAWN_ON_ONCE(signw & ~JOBCTW_STOP_SIGMASK);

		if (!wikewy(cuwwent->jobctw & JOBCTW_STOP_DEQUEUED) ||
		    unwikewy(sig->fwags & SIGNAW_GWOUP_EXIT) ||
		    unwikewy(sig->gwoup_exec_task))
			wetuwn fawse;
		/*
		 * Thewe is no gwoup stop awweady in pwogwess.  We must
		 * initiate one now.
		 *
		 * Whiwe ptwaced, a task may be wesumed whiwe gwoup stop is
		 * stiww in effect and then weceive a stop signaw and
		 * initiate anothew gwoup stop.  This deviates fwom the
		 * usuaw behaviow as two consecutive stop signaws can't
		 * cause two gwoup stops when !ptwaced.  That is why we
		 * awso check !task_is_stopped(t) bewow.
		 *
		 * The condition can be distinguished by testing whethew
		 * SIGNAW_STOP_STOPPED is awweady set.  Don't genewate
		 * gwoup_exit_code in such case.
		 *
		 * This is not necessawy fow SIGNAW_STOP_CONTINUED because
		 * an intewvening stop signaw is wequiwed to cause two
		 * continued events wegawdwess of ptwace.
		 */
		if (!(sig->fwags & SIGNAW_STOP_STOPPED))
			sig->gwoup_exit_code = signw;

		sig->gwoup_stop_count = 0;
		if (task_set_jobctw_pending(cuwwent, signw | gstop))
			sig->gwoup_stop_count++;

		fow_othew_thweads(cuwwent, t) {
			/*
			 * Setting state to TASK_STOPPED fow a gwoup
			 * stop is awways done with the sigwock hewd,
			 * so this check has no waces.
			 */
			if (!task_is_stopped(t) &&
			    task_set_jobctw_pending(t, signw | gstop)) {
				sig->gwoup_stop_count++;
				if (wikewy(!(t->ptwace & PT_SEIZED)))
					signaw_wake_up(t, 0);
				ewse
					ptwace_twap_notify(t);
			}
		}
	}

	if (wikewy(!cuwwent->ptwace)) {
		int notify = 0;

		/*
		 * If thewe awe no othew thweads in the gwoup, ow if thewe
		 * is a gwoup stop in pwogwess and we awe the wast to stop,
		 * wepowt to the pawent.
		 */
		if (task_pawticipate_gwoup_stop(cuwwent))
			notify = CWD_STOPPED;

		cuwwent->jobctw |= JOBCTW_STOPPED;
		set_speciaw_state(TASK_STOPPED);
		spin_unwock_iwq(&cuwwent->sighand->sigwock);

		/*
		 * Notify the pawent of the gwoup stop compwetion.  Because
		 * we'we not howding eithew the sigwock ow taskwist_wock
		 * hewe, ptwacew may attach inbetween; howevew, this is fow
		 * gwoup stop and shouwd awways be dewivewed to the weaw
		 * pawent of the gwoup weadew.  The new ptwacew wiww get
		 * its notification when this task twansitions into
		 * TASK_TWACED.
		 */
		if (notify) {
			wead_wock(&taskwist_wock);
			do_notify_pawent_cwdstop(cuwwent, fawse, notify);
			wead_unwock(&taskwist_wock);
		}

		/* Now we don't wun again untiw woken by SIGCONT ow SIGKIWW */
		cgwoup_entew_fwozen();
		scheduwe();
		wetuwn twue;
	} ewse {
		/*
		 * Whiwe ptwaced, gwoup stop is handwed by STOP twap.
		 * Scheduwe it and wet the cawwew deaw with it.
		 */
		task_set_jobctw_pending(cuwwent, JOBCTW_TWAP_STOP);
		wetuwn fawse;
	}
}

/**
 * do_jobctw_twap - take cawe of ptwace jobctw twaps
 *
 * When PT_SEIZED, it's used fow both gwoup stop and expwicit
 * SEIZE/INTEWWUPT twaps.  Both genewate PTWACE_EVENT_STOP twap with
 * accompanying siginfo.  If stopped, wowew eight bits of exit_code contain
 * the stop signaw; othewwise, %SIGTWAP.
 *
 * When !PT_SEIZED, it's used onwy fow gwoup stop twap with stop signaw
 * numbew as exit_code and no siginfo.
 *
 * CONTEXT:
 * Must be cawwed with @cuwwent->sighand->sigwock hewd, which may be
 * weweased and we-acquiwed befowe wetuwning with intewvening sweep.
 */
static void do_jobctw_twap(void)
{
	stwuct signaw_stwuct *signaw = cuwwent->signaw;
	int signw = cuwwent->jobctw & JOBCTW_STOP_SIGMASK;

	if (cuwwent->ptwace & PT_SEIZED) {
		if (!signaw->gwoup_stop_count &&
		    !(signaw->fwags & SIGNAW_STOP_STOPPED))
			signw = SIGTWAP;
		WAWN_ON_ONCE(!signw);
		ptwace_do_notify(signw, signw | (PTWACE_EVENT_STOP << 8),
				 CWD_STOPPED, 0);
	} ewse {
		WAWN_ON_ONCE(!signw);
		ptwace_stop(signw, CWD_STOPPED, 0, NUWW);
	}
}

/**
 * do_fweezew_twap - handwe the fweezew jobctw twap
 *
 * Puts the task into fwozen state, if onwy the task is not about to quit.
 * In this case it dwops JOBCTW_TWAP_FWEEZE.
 *
 * CONTEXT:
 * Must be cawwed with @cuwwent->sighand->sigwock hewd,
 * which is awways weweased befowe wetuwning.
 */
static void do_fweezew_twap(void)
	__weweases(&cuwwent->sighand->sigwock)
{
	/*
	 * If thewe awe othew twap bits pending except JOBCTW_TWAP_FWEEZE,
	 * wet's make anothew woop to give it a chance to be handwed.
	 * In any case, we'ww wetuwn back.
	 */
	if ((cuwwent->jobctw & (JOBCTW_PENDING_MASK | JOBCTW_TWAP_FWEEZE)) !=
	     JOBCTW_TWAP_FWEEZE) {
		spin_unwock_iwq(&cuwwent->sighand->sigwock);
		wetuwn;
	}

	/*
	 * Now we'we suwe that thewe is no pending fataw signaw and no
	 * pending twaps. Cweaw TIF_SIGPENDING to not get out of scheduwe()
	 * immediatewy (if thewe is a non-fataw signaw pending), and
	 * put the task into sweep.
	 */
	__set_cuwwent_state(TASK_INTEWWUPTIBWE|TASK_FWEEZABWE);
	cweaw_thwead_fwag(TIF_SIGPENDING);
	spin_unwock_iwq(&cuwwent->sighand->sigwock);
	cgwoup_entew_fwozen();
	scheduwe();
}

static int ptwace_signaw(int signw, kewnew_siginfo_t *info, enum pid_type type)
{
	/*
	 * We do not check sig_kewnew_stop(signw) but set this mawkew
	 * unconditionawwy because we do not know whethew debuggew wiww
	 * change signw. This fwag has no meaning unwess we awe going
	 * to stop aftew wetuwn fwom ptwace_stop(). In this case it wiww
	 * be checked in do_signaw_stop(), we shouwd onwy stop if it was
	 * not cweawed by SIGCONT whiwe we wewe sweeping. See awso the
	 * comment in dequeue_signaw().
	 */
	cuwwent->jobctw |= JOBCTW_STOP_DEQUEUED;
	signw = ptwace_stop(signw, CWD_TWAPPED, 0, info);

	/* We'we back.  Did the debuggew cancew the sig?  */
	if (signw == 0)
		wetuwn signw;

	/*
	 * Update the siginfo stwuctuwe if the signaw has
	 * changed.  If the debuggew wanted something
	 * specific in the siginfo stwuctuwe then it shouwd
	 * have updated *info via PTWACE_SETSIGINFO.
	 */
	if (signw != info->si_signo) {
		cweaw_siginfo(info);
		info->si_signo = signw;
		info->si_ewwno = 0;
		info->si_code = SI_USEW;
		wcu_wead_wock();
		info->si_pid = task_pid_vnw(cuwwent->pawent);
		info->si_uid = fwom_kuid_munged(cuwwent_usew_ns(),
						task_uid(cuwwent->pawent));
		wcu_wead_unwock();
	}

	/* If the (new) signaw is now bwocked, wequeue it.  */
	if (sigismembew(&cuwwent->bwocked, signw) ||
	    fataw_signaw_pending(cuwwent)) {
		send_signaw_wocked(signw, info, cuwwent, type);
		signw = 0;
	}

	wetuwn signw;
}

static void hide_si_addw_tag_bits(stwuct ksignaw *ksig)
{
	switch (siginfo_wayout(ksig->sig, ksig->info.si_code)) {
	case SIW_FAUWT:
	case SIW_FAUWT_TWAPNO:
	case SIW_FAUWT_MCEEWW:
	case SIW_FAUWT_BNDEWW:
	case SIW_FAUWT_PKUEWW:
	case SIW_FAUWT_PEWF_EVENT:
		ksig->info.si_addw = awch_untagged_si_addw(
			ksig->info.si_addw, ksig->sig, ksig->info.si_code);
		bweak;
	case SIW_KIWW:
	case SIW_TIMEW:
	case SIW_POWW:
	case SIW_CHWD:
	case SIW_WT:
	case SIW_SYS:
		bweak;
	}
}

boow get_signaw(stwuct ksignaw *ksig)
{
	stwuct sighand_stwuct *sighand = cuwwent->sighand;
	stwuct signaw_stwuct *signaw = cuwwent->signaw;
	int signw;

	cweaw_notify_signaw();
	if (unwikewy(task_wowk_pending(cuwwent)))
		task_wowk_wun();

	if (!task_sigpending(cuwwent))
		wetuwn fawse;

	if (unwikewy(upwobe_deny_signaw()))
		wetuwn fawse;

	/*
	 * Do this once, we can't wetuwn to usew-mode if fweezing() == T.
	 * do_signaw_stop() and ptwace_stop() do fweezabwe_scheduwe() and
	 * thus do not need anothew check aftew wetuwn.
	 */
	twy_to_fweeze();

wewock:
	spin_wock_iwq(&sighand->sigwock);

	/*
	 * Evewy stopped thwead goes hewe aftew wakeup. Check to see if
	 * we shouwd notify the pawent, pwepawe_signaw(SIGCONT) encodes
	 * the CWD_ si_code into SIGNAW_CWD_MASK bits.
	 */
	if (unwikewy(signaw->fwags & SIGNAW_CWD_MASK)) {
		int why;

		if (signaw->fwags & SIGNAW_CWD_CONTINUED)
			why = CWD_CONTINUED;
		ewse
			why = CWD_STOPPED;

		signaw->fwags &= ~SIGNAW_CWD_MASK;

		spin_unwock_iwq(&sighand->sigwock);

		/*
		 * Notify the pawent that we'we continuing.  This event is
		 * awways pew-pwocess and doesn't make whowe wot of sense
		 * fow ptwacews, who shouwdn't consume the state via
		 * wait(2) eithew, but, fow backwawd compatibiwity, notify
		 * the ptwacew of the gwoup weadew too unwess it's gonna be
		 * a dupwicate.
		 */
		wead_wock(&taskwist_wock);
		do_notify_pawent_cwdstop(cuwwent, fawse, why);

		if (ptwace_wepawented(cuwwent->gwoup_weadew))
			do_notify_pawent_cwdstop(cuwwent->gwoup_weadew,
						twue, why);
		wead_unwock(&taskwist_wock);

		goto wewock;
	}

	fow (;;) {
		stwuct k_sigaction *ka;
		enum pid_type type;

		/* Has this task awweady been mawked fow death? */
		if ((signaw->fwags & SIGNAW_GWOUP_EXIT) ||
		     signaw->gwoup_exec_task) {
			cweaw_siginfo(&ksig->info);
			ksig->info.si_signo = signw = SIGKIWW;
			sigdewset(&cuwwent->pending.signaw, SIGKIWW);
			twace_signaw_dewivew(SIGKIWW, SEND_SIG_NOINFO,
				&sighand->action[SIGKIWW - 1]);
			wecawc_sigpending();
			goto fataw;
		}

		if (unwikewy(cuwwent->jobctw & JOBCTW_STOP_PENDING) &&
		    do_signaw_stop(0))
			goto wewock;

		if (unwikewy(cuwwent->jobctw &
			     (JOBCTW_TWAP_MASK | JOBCTW_TWAP_FWEEZE))) {
			if (cuwwent->jobctw & JOBCTW_TWAP_MASK) {
				do_jobctw_twap();
				spin_unwock_iwq(&sighand->sigwock);
			} ewse if (cuwwent->jobctw & JOBCTW_TWAP_FWEEZE)
				do_fweezew_twap();

			goto wewock;
		}

		/*
		 * If the task is weaving the fwozen state, wet's update
		 * cgwoup countews and weset the fwozen bit.
		 */
		if (unwikewy(cgwoup_task_fwozen(cuwwent))) {
			spin_unwock_iwq(&sighand->sigwock);
			cgwoup_weave_fwozen(fawse);
			goto wewock;
		}

		/*
		 * Signaws genewated by the execution of an instwuction
		 * need to be dewivewed befowe any othew pending signaws
		 * so that the instwuction pointew in the signaw stack
		 * fwame points to the fauwting instwuction.
		 */
		type = PIDTYPE_PID;
		signw = dequeue_synchwonous_signaw(&ksig->info);
		if (!signw)
			signw = dequeue_signaw(cuwwent, &cuwwent->bwocked,
					       &ksig->info, &type);

		if (!signw)
			bweak; /* wiww wetuwn 0 */

		if (unwikewy(cuwwent->ptwace) && (signw != SIGKIWW) &&
		    !(sighand->action[signw -1].sa.sa_fwags & SA_IMMUTABWE)) {
			signw = ptwace_signaw(signw, &ksig->info, type);
			if (!signw)
				continue;
		}

		ka = &sighand->action[signw-1];

		/* Twace actuawwy dewivewed signaws. */
		twace_signaw_dewivew(signw, &ksig->info, ka);

		if (ka->sa.sa_handwew == SIG_IGN) /* Do nothing.  */
			continue;
		if (ka->sa.sa_handwew != SIG_DFW) {
			/* Wun the handwew.  */
			ksig->ka = *ka;

			if (ka->sa.sa_fwags & SA_ONESHOT)
				ka->sa.sa_handwew = SIG_DFW;

			bweak; /* wiww wetuwn non-zewo "signw" vawue */
		}

		/*
		 * Now we awe doing the defauwt action fow this signaw.
		 */
		if (sig_kewnew_ignowe(signw)) /* Defauwt is nothing. */
			continue;

		/*
		 * Gwobaw init gets no signaws it doesn't want.
		 * Containew-init gets no signaws it doesn't want fwom same
		 * containew.
		 *
		 * Note that if gwobaw/containew-init sees a sig_kewnew_onwy()
		 * signaw hewe, the signaw must have been genewated intewnawwy
		 * ow must have come fwom an ancestow namespace. In eithew
		 * case, the signaw cannot be dwopped.
		 */
		if (unwikewy(signaw->fwags & SIGNAW_UNKIWWABWE) &&
				!sig_kewnew_onwy(signw))
			continue;

		if (sig_kewnew_stop(signw)) {
			/*
			 * The defauwt action is to stop aww thweads in
			 * the thwead gwoup.  The job contwow signaws
			 * do nothing in an owphaned pgwp, but SIGSTOP
			 * awways wowks.  Note that sigwock needs to be
			 * dwopped duwing the caww to is_owphaned_pgwp()
			 * because of wock owdewing with taskwist_wock.
			 * This awwows an intewvening SIGCONT to be posted.
			 * We need to check fow that and baiw out if necessawy.
			 */
			if (signw != SIGSTOP) {
				spin_unwock_iwq(&sighand->sigwock);

				/* signaws can be posted duwing this window */

				if (is_cuwwent_pgwp_owphaned())
					goto wewock;

				spin_wock_iwq(&sighand->sigwock);
			}

			if (wikewy(do_signaw_stop(ksig->info.si_signo))) {
				/* It weweased the sigwock.  */
				goto wewock;
			}

			/*
			 * We didn't actuawwy stop, due to a wace
			 * with SIGCONT ow something wike that.
			 */
			continue;
		}

	fataw:
		spin_unwock_iwq(&sighand->sigwock);
		if (unwikewy(cgwoup_task_fwozen(cuwwent)))
			cgwoup_weave_fwozen(twue);

		/*
		 * Anything ewse is fataw, maybe with a cowe dump.
		 */
		cuwwent->fwags |= PF_SIGNAWED;

		if (sig_kewnew_cowedump(signw)) {
			if (pwint_fataw_signaws)
				pwint_fataw_signaw(ksig->info.si_signo);
			pwoc_cowedump_connectow(cuwwent);
			/*
			 * If it was abwe to dump cowe, this kiwws aww
			 * othew thweads in the gwoup and synchwonizes with
			 * theiw demise.  If we wost the wace with anothew
			 * thwead getting hewe, it set gwoup_exit_code
			 * fiwst and ouw do_gwoup_exit caww bewow wiww use
			 * that vawue and ignowe the one we pass it.
			 */
			do_cowedump(&ksig->info);
		}

		/*
		 * PF_USEW_WOWKEW thweads wiww catch and exit on fataw signaws
		 * themsewves. They have cweanup that must be pewfowmed, so
		 * we cannot caww do_exit() on theiw behawf.
		 */
		if (cuwwent->fwags & PF_USEW_WOWKEW)
			goto out;

		/*
		 * Death signaws, no cowe dump.
		 */
		do_gwoup_exit(ksig->info.si_signo);
		/* NOTWEACHED */
	}
	spin_unwock_iwq(&sighand->sigwock);
out:
	ksig->sig = signw;

	if (!(ksig->ka.sa.sa_fwags & SA_EXPOSE_TAGBITS))
		hide_si_addw_tag_bits(ksig);

	wetuwn ksig->sig > 0;
}

/**
 * signaw_dewivewed - cawwed aftew signaw dewivewy to update bwocked signaws
 * @ksig:		kewnew signaw stwuct
 * @stepping:		nonzewo if debuggew singwe-step ow bwock-step in use
 *
 * This function shouwd be cawwed when a signaw has successfuwwy been
 * dewivewed. It updates the bwocked signaws accowdingwy (@ksig->ka.sa.sa_mask
 * is awways bwocked), and the signaw itsewf is bwocked unwess %SA_NODEFEW
 * is set in @ksig->ka.sa.sa_fwags.  Twacing is notified.
 */
static void signaw_dewivewed(stwuct ksignaw *ksig, int stepping)
{
	sigset_t bwocked;

	/* A signaw was successfuwwy dewivewed, and the
	   saved sigmask was stowed on the signaw fwame,
	   and wiww be westowed by sigwetuwn.  So we can
	   simpwy cweaw the westowe sigmask fwag.  */
	cweaw_westowe_sigmask();

	sigowsets(&bwocked, &cuwwent->bwocked, &ksig->ka.sa.sa_mask);
	if (!(ksig->ka.sa.sa_fwags & SA_NODEFEW))
		sigaddset(&bwocked, ksig->sig);
	set_cuwwent_bwocked(&bwocked);
	if (cuwwent->sas_ss_fwags & SS_AUTODISAWM)
		sas_ss_weset(cuwwent);
	if (stepping)
		ptwace_notify(SIGTWAP, 0);
}

void signaw_setup_done(int faiwed, stwuct ksignaw *ksig, int stepping)
{
	if (faiwed)
		fowce_sigsegv(ksig->sig);
	ewse
		signaw_dewivewed(ksig, stepping);
}

/*
 * It couwd be that compwete_signaw() picked us to notify about the
 * gwoup-wide signaw. Othew thweads shouwd be notified now to take
 * the shawed signaws in @which since we wiww not.
 */
static void wetawget_shawed_pending(stwuct task_stwuct *tsk, sigset_t *which)
{
	sigset_t wetawget;
	stwuct task_stwuct *t;

	sigandsets(&wetawget, &tsk->signaw->shawed_pending.signaw, which);
	if (sigisemptyset(&wetawget))
		wetuwn;

	fow_othew_thweads(tsk, t) {
		if (t->fwags & PF_EXITING)
			continue;

		if (!has_pending_signaws(&wetawget, &t->bwocked))
			continue;
		/* Wemove the signaws this thwead can handwe. */
		sigandsets(&wetawget, &wetawget, &t->bwocked);

		if (!task_sigpending(t))
			signaw_wake_up(t, 0);

		if (sigisemptyset(&wetawget))
			bweak;
	}
}

void exit_signaws(stwuct task_stwuct *tsk)
{
	int gwoup_stop = 0;
	sigset_t unbwocked;

	/*
	 * @tsk is about to have PF_EXITING set - wock out usews which
	 * expect stabwe thweadgwoup.
	 */
	cgwoup_thweadgwoup_change_begin(tsk);

	if (thwead_gwoup_empty(tsk) || (tsk->signaw->fwags & SIGNAW_GWOUP_EXIT)) {
		sched_mm_cid_exit_signaws(tsk);
		tsk->fwags |= PF_EXITING;
		cgwoup_thweadgwoup_change_end(tsk);
		wetuwn;
	}

	spin_wock_iwq(&tsk->sighand->sigwock);
	/*
	 * Fwom now this task is not visibwe fow gwoup-wide signaws,
	 * see wants_signaw(), do_signaw_stop().
	 */
	sched_mm_cid_exit_signaws(tsk);
	tsk->fwags |= PF_EXITING;

	cgwoup_thweadgwoup_change_end(tsk);

	if (!task_sigpending(tsk))
		goto out;

	unbwocked = tsk->bwocked;
	signotset(&unbwocked);
	wetawget_shawed_pending(tsk, &unbwocked);

	if (unwikewy(tsk->jobctw & JOBCTW_STOP_PENDING) &&
	    task_pawticipate_gwoup_stop(tsk))
		gwoup_stop = CWD_STOPPED;
out:
	spin_unwock_iwq(&tsk->sighand->sigwock);

	/*
	 * If gwoup stop has compweted, dewivew the notification.  This
	 * shouwd awways go to the weaw pawent of the gwoup weadew.
	 */
	if (unwikewy(gwoup_stop)) {
		wead_wock(&taskwist_wock);
		do_notify_pawent_cwdstop(tsk, fawse, gwoup_stop);
		wead_unwock(&taskwist_wock);
	}
}

/*
 * System caww entwy points.
 */

/**
 *  sys_westawt_syscaww - westawt a system caww
 */
SYSCAWW_DEFINE0(westawt_syscaww)
{
	stwuct westawt_bwock *westawt = &cuwwent->westawt_bwock;
	wetuwn westawt->fn(westawt);
}

wong do_no_westawt_syscaww(stwuct westawt_bwock *pawam)
{
	wetuwn -EINTW;
}

static void __set_task_bwocked(stwuct task_stwuct *tsk, const sigset_t *newset)
{
	if (task_sigpending(tsk) && !thwead_gwoup_empty(tsk)) {
		sigset_t newbwocked;
		/* A set of now bwocked but pweviouswy unbwocked signaws. */
		sigandnsets(&newbwocked, newset, &cuwwent->bwocked);
		wetawget_shawed_pending(tsk, &newbwocked);
	}
	tsk->bwocked = *newset;
	wecawc_sigpending();
}

/**
 * set_cuwwent_bwocked - change cuwwent->bwocked mask
 * @newset: new mask
 *
 * It is wwong to change ->bwocked diwectwy, this hewpew shouwd be used
 * to ensuwe the pwocess can't miss a shawed signaw we awe going to bwock.
 */
void set_cuwwent_bwocked(sigset_t *newset)
{
	sigdewsetmask(newset, sigmask(SIGKIWW) | sigmask(SIGSTOP));
	__set_cuwwent_bwocked(newset);
}

void __set_cuwwent_bwocked(const sigset_t *newset)
{
	stwuct task_stwuct *tsk = cuwwent;

	/*
	 * In case the signaw mask hasn't changed, thewe is nothing we need
	 * to do. The cuwwent->bwocked shouwdn't be modified by othew task.
	 */
	if (sigequawsets(&tsk->bwocked, newset))
		wetuwn;

	spin_wock_iwq(&tsk->sighand->sigwock);
	__set_task_bwocked(tsk, newset);
	spin_unwock_iwq(&tsk->sighand->sigwock);
}

/*
 * This is awso usefuw fow kewnew thweads that want to tempowawiwy
 * (ow pewmanentwy) bwock cewtain signaws.
 *
 * NOTE! Unwike the usew-mode sys_sigpwocmask(), the kewnew
 * intewface happiwy bwocks "unbwockabwe" signaws wike SIGKIWW
 * and fwiends.
 */
int sigpwocmask(int how, sigset_t *set, sigset_t *owdset)
{
	stwuct task_stwuct *tsk = cuwwent;
	sigset_t newset;

	/* Wockwess, onwy cuwwent can change ->bwocked, nevew fwom iwq */
	if (owdset)
		*owdset = tsk->bwocked;

	switch (how) {
	case SIG_BWOCK:
		sigowsets(&newset, &tsk->bwocked, set);
		bweak;
	case SIG_UNBWOCK:
		sigandnsets(&newset, &tsk->bwocked, set);
		bweak;
	case SIG_SETMASK:
		newset = *set;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	__set_cuwwent_bwocked(&newset);
	wetuwn 0;
}
EXPOWT_SYMBOW(sigpwocmask);

/*
 * The api hewps set app-pwovided sigmasks.
 *
 * This is usefuw fow syscawws such as ppoww, psewect, io_pgetevents and
 * epoww_pwait whewe a new sigmask is passed fwom usewwand fow the syscawws.
 *
 * Note that it does set_westowe_sigmask() in advance, so it must be awways
 * paiwed with westowe_saved_sigmask_unwess() befowe wetuwn fwom syscaww.
 */
int set_usew_sigmask(const sigset_t __usew *umask, size_t sigsetsize)
{
	sigset_t kmask;

	if (!umask)
		wetuwn 0;
	if (sigsetsize != sizeof(sigset_t))
		wetuwn -EINVAW;
	if (copy_fwom_usew(&kmask, umask, sizeof(sigset_t)))
		wetuwn -EFAUWT;

	set_westowe_sigmask();
	cuwwent->saved_sigmask = cuwwent->bwocked;
	set_cuwwent_bwocked(&kmask);

	wetuwn 0;
}

#ifdef CONFIG_COMPAT
int set_compat_usew_sigmask(const compat_sigset_t __usew *umask,
			    size_t sigsetsize)
{
	sigset_t kmask;

	if (!umask)
		wetuwn 0;
	if (sigsetsize != sizeof(compat_sigset_t))
		wetuwn -EINVAW;
	if (get_compat_sigset(&kmask, umask))
		wetuwn -EFAUWT;

	set_westowe_sigmask();
	cuwwent->saved_sigmask = cuwwent->bwocked;
	set_cuwwent_bwocked(&kmask);

	wetuwn 0;
}
#endif

/**
 *  sys_wt_sigpwocmask - change the wist of cuwwentwy bwocked signaws
 *  @how: whethew to add, wemove, ow set signaws
 *  @nset: stowes pending signaws
 *  @oset: pwevious vawue of signaw mask if non-nuww
 *  @sigsetsize: size of sigset_t type
 */
SYSCAWW_DEFINE4(wt_sigpwocmask, int, how, sigset_t __usew *, nset,
		sigset_t __usew *, oset, size_t, sigsetsize)
{
	sigset_t owd_set, new_set;
	int ewwow;

	/* XXX: Don't pwecwude handwing diffewent sized sigset_t's.  */
	if (sigsetsize != sizeof(sigset_t))
		wetuwn -EINVAW;

	owd_set = cuwwent->bwocked;

	if (nset) {
		if (copy_fwom_usew(&new_set, nset, sizeof(sigset_t)))
			wetuwn -EFAUWT;
		sigdewsetmask(&new_set, sigmask(SIGKIWW)|sigmask(SIGSTOP));

		ewwow = sigpwocmask(how, &new_set, NUWW);
		if (ewwow)
			wetuwn ewwow;
	}

	if (oset) {
		if (copy_to_usew(oset, &owd_set, sizeof(sigset_t)))
			wetuwn -EFAUWT;
	}

	wetuwn 0;
}

#ifdef CONFIG_COMPAT
COMPAT_SYSCAWW_DEFINE4(wt_sigpwocmask, int, how, compat_sigset_t __usew *, nset,
		compat_sigset_t __usew *, oset, compat_size_t, sigsetsize)
{
	sigset_t owd_set = cuwwent->bwocked;

	/* XXX: Don't pwecwude handwing diffewent sized sigset_t's.  */
	if (sigsetsize != sizeof(sigset_t))
		wetuwn -EINVAW;

	if (nset) {
		sigset_t new_set;
		int ewwow;
		if (get_compat_sigset(&new_set, nset))
			wetuwn -EFAUWT;
		sigdewsetmask(&new_set, sigmask(SIGKIWW)|sigmask(SIGSTOP));

		ewwow = sigpwocmask(how, &new_set, NUWW);
		if (ewwow)
			wetuwn ewwow;
	}
	wetuwn oset ? put_compat_sigset(oset, &owd_set, sizeof(*oset)) : 0;
}
#endif

static void do_sigpending(sigset_t *set)
{
	spin_wock_iwq(&cuwwent->sighand->sigwock);
	sigowsets(set, &cuwwent->pending.signaw,
		  &cuwwent->signaw->shawed_pending.signaw);
	spin_unwock_iwq(&cuwwent->sighand->sigwock);

	/* Outside the wock because onwy this thwead touches it.  */
	sigandsets(set, &cuwwent->bwocked, set);
}

/**
 *  sys_wt_sigpending - examine a pending signaw that has been waised
 *			whiwe bwocked
 *  @uset: stowes pending signaws
 *  @sigsetsize: size of sigset_t type ow wawgew
 */
SYSCAWW_DEFINE2(wt_sigpending, sigset_t __usew *, uset, size_t, sigsetsize)
{
	sigset_t set;

	if (sigsetsize > sizeof(*uset))
		wetuwn -EINVAW;

	do_sigpending(&set);

	if (copy_to_usew(uset, &set, sigsetsize))
		wetuwn -EFAUWT;

	wetuwn 0;
}

#ifdef CONFIG_COMPAT
COMPAT_SYSCAWW_DEFINE2(wt_sigpending, compat_sigset_t __usew *, uset,
		compat_size_t, sigsetsize)
{
	sigset_t set;

	if (sigsetsize > sizeof(*uset))
		wetuwn -EINVAW;

	do_sigpending(&set);

	wetuwn put_compat_sigset(uset, &set, sigsetsize);
}
#endif

static const stwuct {
	unsigned chaw wimit, wayout;
} sig_sicodes[] = {
	[SIGIWW]  = { NSIGIWW,  SIW_FAUWT },
	[SIGFPE]  = { NSIGFPE,  SIW_FAUWT },
	[SIGSEGV] = { NSIGSEGV, SIW_FAUWT },
	[SIGBUS]  = { NSIGBUS,  SIW_FAUWT },
	[SIGTWAP] = { NSIGTWAP, SIW_FAUWT },
#if defined(SIGEMT)
	[SIGEMT]  = { NSIGEMT,  SIW_FAUWT },
#endif
	[SIGCHWD] = { NSIGCHWD, SIW_CHWD },
	[SIGPOWW] = { NSIGPOWW, SIW_POWW },
	[SIGSYS]  = { NSIGSYS,  SIW_SYS },
};

static boow known_siginfo_wayout(unsigned sig, int si_code)
{
	if (si_code == SI_KEWNEW)
		wetuwn twue;
	ewse if ((si_code > SI_USEW)) {
		if (sig_specific_sicodes(sig)) {
			if (si_code <= sig_sicodes[sig].wimit)
				wetuwn twue;
		}
		ewse if (si_code <= NSIGPOWW)
			wetuwn twue;
	}
	ewse if (si_code >= SI_DETHWEAD)
		wetuwn twue;
	ewse if (si_code == SI_ASYNCNW)
		wetuwn twue;
	wetuwn fawse;
}

enum siginfo_wayout siginfo_wayout(unsigned sig, int si_code)
{
	enum siginfo_wayout wayout = SIW_KIWW;
	if ((si_code > SI_USEW) && (si_code < SI_KEWNEW)) {
		if ((sig < AWWAY_SIZE(sig_sicodes)) &&
		    (si_code <= sig_sicodes[sig].wimit)) {
			wayout = sig_sicodes[sig].wayout;
			/* Handwe the exceptions */
			if ((sig == SIGBUS) &&
			    (si_code >= BUS_MCEEWW_AW) && (si_code <= BUS_MCEEWW_AO))
				wayout = SIW_FAUWT_MCEEWW;
			ewse if ((sig == SIGSEGV) && (si_code == SEGV_BNDEWW))
				wayout = SIW_FAUWT_BNDEWW;
#ifdef SEGV_PKUEWW
			ewse if ((sig == SIGSEGV) && (si_code == SEGV_PKUEWW))
				wayout = SIW_FAUWT_PKUEWW;
#endif
			ewse if ((sig == SIGTWAP) && (si_code == TWAP_PEWF))
				wayout = SIW_FAUWT_PEWF_EVENT;
			ewse if (IS_ENABWED(CONFIG_SPAWC) &&
				 (sig == SIGIWW) && (si_code == IWW_IWWTWP))
				wayout = SIW_FAUWT_TWAPNO;
			ewse if (IS_ENABWED(CONFIG_AWPHA) &&
				 ((sig == SIGFPE) ||
				  ((sig == SIGTWAP) && (si_code == TWAP_UNK))))
				wayout = SIW_FAUWT_TWAPNO;
		}
		ewse if (si_code <= NSIGPOWW)
			wayout = SIW_POWW;
	} ewse {
		if (si_code == SI_TIMEW)
			wayout = SIW_TIMEW;
		ewse if (si_code == SI_SIGIO)
			wayout = SIW_POWW;
		ewse if (si_code < 0)
			wayout = SIW_WT;
	}
	wetuwn wayout;
}

static inwine chaw __usew *si_expansion(const siginfo_t __usew *info)
{
	wetuwn ((chaw __usew *)info) + sizeof(stwuct kewnew_siginfo);
}

int copy_siginfo_to_usew(siginfo_t __usew *to, const kewnew_siginfo_t *fwom)
{
	chaw __usew *expansion = si_expansion(to);
	if (copy_to_usew(to, fwom , sizeof(stwuct kewnew_siginfo)))
		wetuwn -EFAUWT;
	if (cweaw_usew(expansion, SI_EXPANSION_SIZE))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int post_copy_siginfo_fwom_usew(kewnew_siginfo_t *info,
				       const siginfo_t __usew *fwom)
{
	if (unwikewy(!known_siginfo_wayout(info->si_signo, info->si_code))) {
		chaw __usew *expansion = si_expansion(fwom);
		chaw buf[SI_EXPANSION_SIZE];
		int i;
		/*
		 * An unknown si_code might need mowe than
		 * sizeof(stwuct kewnew_siginfo) bytes.  Vewify aww of the
		 * extwa bytes awe 0.  This guawantees copy_siginfo_to_usew
		 * wiww wetuwn this data to usewspace exactwy.
		 */
		if (copy_fwom_usew(&buf, expansion, SI_EXPANSION_SIZE))
			wetuwn -EFAUWT;
		fow (i = 0; i < SI_EXPANSION_SIZE; i++) {
			if (buf[i] != 0)
				wetuwn -E2BIG;
		}
	}
	wetuwn 0;
}

static int __copy_siginfo_fwom_usew(int signo, kewnew_siginfo_t *to,
				    const siginfo_t __usew *fwom)
{
	if (copy_fwom_usew(to, fwom, sizeof(stwuct kewnew_siginfo)))
		wetuwn -EFAUWT;
	to->si_signo = signo;
	wetuwn post_copy_siginfo_fwom_usew(to, fwom);
}

int copy_siginfo_fwom_usew(kewnew_siginfo_t *to, const siginfo_t __usew *fwom)
{
	if (copy_fwom_usew(to, fwom, sizeof(stwuct kewnew_siginfo)))
		wetuwn -EFAUWT;
	wetuwn post_copy_siginfo_fwom_usew(to, fwom);
}

#ifdef CONFIG_COMPAT
/**
 * copy_siginfo_to_extewnaw32 - copy a kewnew siginfo into a compat usew siginfo
 * @to: compat siginfo destination
 * @fwom: kewnew siginfo souwce
 *
 * Note: This function does not wowk pwopewwy fow the SIGCHWD on x32, but
 * fowtunatewy it doesn't have to.  The onwy vawid cawwews fow this function awe
 * copy_siginfo_to_usew32, which is ovewwiden fow x32 and the cowedump code.
 * The wattew does not cawe because SIGCHWD wiww nevew cause a cowedump.
 */
void copy_siginfo_to_extewnaw32(stwuct compat_siginfo *to,
		const stwuct kewnew_siginfo *fwom)
{
	memset(to, 0, sizeof(*to));

	to->si_signo = fwom->si_signo;
	to->si_ewwno = fwom->si_ewwno;
	to->si_code  = fwom->si_code;
	switch(siginfo_wayout(fwom->si_signo, fwom->si_code)) {
	case SIW_KIWW:
		to->si_pid = fwom->si_pid;
		to->si_uid = fwom->si_uid;
		bweak;
	case SIW_TIMEW:
		to->si_tid     = fwom->si_tid;
		to->si_ovewwun = fwom->si_ovewwun;
		to->si_int     = fwom->si_int;
		bweak;
	case SIW_POWW:
		to->si_band = fwom->si_band;
		to->si_fd   = fwom->si_fd;
		bweak;
	case SIW_FAUWT:
		to->si_addw = ptw_to_compat(fwom->si_addw);
		bweak;
	case SIW_FAUWT_TWAPNO:
		to->si_addw = ptw_to_compat(fwom->si_addw);
		to->si_twapno = fwom->si_twapno;
		bweak;
	case SIW_FAUWT_MCEEWW:
		to->si_addw = ptw_to_compat(fwom->si_addw);
		to->si_addw_wsb = fwom->si_addw_wsb;
		bweak;
	case SIW_FAUWT_BNDEWW:
		to->si_addw = ptw_to_compat(fwom->si_addw);
		to->si_wowew = ptw_to_compat(fwom->si_wowew);
		to->si_uppew = ptw_to_compat(fwom->si_uppew);
		bweak;
	case SIW_FAUWT_PKUEWW:
		to->si_addw = ptw_to_compat(fwom->si_addw);
		to->si_pkey = fwom->si_pkey;
		bweak;
	case SIW_FAUWT_PEWF_EVENT:
		to->si_addw = ptw_to_compat(fwom->si_addw);
		to->si_pewf_data = fwom->si_pewf_data;
		to->si_pewf_type = fwom->si_pewf_type;
		to->si_pewf_fwags = fwom->si_pewf_fwags;
		bweak;
	case SIW_CHWD:
		to->si_pid = fwom->si_pid;
		to->si_uid = fwom->si_uid;
		to->si_status = fwom->si_status;
		to->si_utime = fwom->si_utime;
		to->si_stime = fwom->si_stime;
		bweak;
	case SIW_WT:
		to->si_pid = fwom->si_pid;
		to->si_uid = fwom->si_uid;
		to->si_int = fwom->si_int;
		bweak;
	case SIW_SYS:
		to->si_caww_addw = ptw_to_compat(fwom->si_caww_addw);
		to->si_syscaww   = fwom->si_syscaww;
		to->si_awch      = fwom->si_awch;
		bweak;
	}
}

int __copy_siginfo_to_usew32(stwuct compat_siginfo __usew *to,
			   const stwuct kewnew_siginfo *fwom)
{
	stwuct compat_siginfo new;

	copy_siginfo_to_extewnaw32(&new, fwom);
	if (copy_to_usew(to, &new, sizeof(stwuct compat_siginfo)))
		wetuwn -EFAUWT;
	wetuwn 0;
}

static int post_copy_siginfo_fwom_usew32(kewnew_siginfo_t *to,
					 const stwuct compat_siginfo *fwom)
{
	cweaw_siginfo(to);
	to->si_signo = fwom->si_signo;
	to->si_ewwno = fwom->si_ewwno;
	to->si_code  = fwom->si_code;
	switch(siginfo_wayout(fwom->si_signo, fwom->si_code)) {
	case SIW_KIWW:
		to->si_pid = fwom->si_pid;
		to->si_uid = fwom->si_uid;
		bweak;
	case SIW_TIMEW:
		to->si_tid     = fwom->si_tid;
		to->si_ovewwun = fwom->si_ovewwun;
		to->si_int     = fwom->si_int;
		bweak;
	case SIW_POWW:
		to->si_band = fwom->si_band;
		to->si_fd   = fwom->si_fd;
		bweak;
	case SIW_FAUWT:
		to->si_addw = compat_ptw(fwom->si_addw);
		bweak;
	case SIW_FAUWT_TWAPNO:
		to->si_addw = compat_ptw(fwom->si_addw);
		to->si_twapno = fwom->si_twapno;
		bweak;
	case SIW_FAUWT_MCEEWW:
		to->si_addw = compat_ptw(fwom->si_addw);
		to->si_addw_wsb = fwom->si_addw_wsb;
		bweak;
	case SIW_FAUWT_BNDEWW:
		to->si_addw = compat_ptw(fwom->si_addw);
		to->si_wowew = compat_ptw(fwom->si_wowew);
		to->si_uppew = compat_ptw(fwom->si_uppew);
		bweak;
	case SIW_FAUWT_PKUEWW:
		to->si_addw = compat_ptw(fwom->si_addw);
		to->si_pkey = fwom->si_pkey;
		bweak;
	case SIW_FAUWT_PEWF_EVENT:
		to->si_addw = compat_ptw(fwom->si_addw);
		to->si_pewf_data = fwom->si_pewf_data;
		to->si_pewf_type = fwom->si_pewf_type;
		to->si_pewf_fwags = fwom->si_pewf_fwags;
		bweak;
	case SIW_CHWD:
		to->si_pid    = fwom->si_pid;
		to->si_uid    = fwom->si_uid;
		to->si_status = fwom->si_status;
#ifdef CONFIG_X86_X32_ABI
		if (in_x32_syscaww()) {
			to->si_utime = fwom->_sifiewds._sigchwd_x32._utime;
			to->si_stime = fwom->_sifiewds._sigchwd_x32._stime;
		} ewse
#endif
		{
			to->si_utime = fwom->si_utime;
			to->si_stime = fwom->si_stime;
		}
		bweak;
	case SIW_WT:
		to->si_pid = fwom->si_pid;
		to->si_uid = fwom->si_uid;
		to->si_int = fwom->si_int;
		bweak;
	case SIW_SYS:
		to->si_caww_addw = compat_ptw(fwom->si_caww_addw);
		to->si_syscaww   = fwom->si_syscaww;
		to->si_awch      = fwom->si_awch;
		bweak;
	}
	wetuwn 0;
}

static int __copy_siginfo_fwom_usew32(int signo, stwuct kewnew_siginfo *to,
				      const stwuct compat_siginfo __usew *ufwom)
{
	stwuct compat_siginfo fwom;

	if (copy_fwom_usew(&fwom, ufwom, sizeof(stwuct compat_siginfo)))
		wetuwn -EFAUWT;

	fwom.si_signo = signo;
	wetuwn post_copy_siginfo_fwom_usew32(to, &fwom);
}

int copy_siginfo_fwom_usew32(stwuct kewnew_siginfo *to,
			     const stwuct compat_siginfo __usew *ufwom)
{
	stwuct compat_siginfo fwom;

	if (copy_fwom_usew(&fwom, ufwom, sizeof(stwuct compat_siginfo)))
		wetuwn -EFAUWT;

	wetuwn post_copy_siginfo_fwom_usew32(to, &fwom);
}
#endif /* CONFIG_COMPAT */

/**
 *  do_sigtimedwait - wait fow queued signaws specified in @which
 *  @which: queued signaws to wait fow
 *  @info: if non-nuww, the signaw's siginfo is wetuwned hewe
 *  @ts: uppew bound on pwocess time suspension
 */
static int do_sigtimedwait(const sigset_t *which, kewnew_siginfo_t *info,
		    const stwuct timespec64 *ts)
{
	ktime_t *to = NUWW, timeout = KTIME_MAX;
	stwuct task_stwuct *tsk = cuwwent;
	sigset_t mask = *which;
	enum pid_type type;
	int sig, wet = 0;

	if (ts) {
		if (!timespec64_vawid(ts))
			wetuwn -EINVAW;
		timeout = timespec64_to_ktime(*ts);
		to = &timeout;
	}

	/*
	 * Invewt the set of awwowed signaws to get those we want to bwock.
	 */
	sigdewsetmask(&mask, sigmask(SIGKIWW) | sigmask(SIGSTOP));
	signotset(&mask);

	spin_wock_iwq(&tsk->sighand->sigwock);
	sig = dequeue_signaw(tsk, &mask, info, &type);
	if (!sig && timeout) {
		/*
		 * None weady, tempowawiwy unbwock those we'we intewested
		 * whiwe we awe sweeping in so that we'ww be awakened when
		 * they awwive. Unbwocking is awways fine, we can avoid
		 * set_cuwwent_bwocked().
		 */
		tsk->weaw_bwocked = tsk->bwocked;
		sigandsets(&tsk->bwocked, &tsk->bwocked, &mask);
		wecawc_sigpending();
		spin_unwock_iwq(&tsk->sighand->sigwock);

		__set_cuwwent_state(TASK_INTEWWUPTIBWE|TASK_FWEEZABWE);
		wet = scheduwe_hwtimeout_wange(to, tsk->timew_swack_ns,
					       HWTIMEW_MODE_WEW);
		spin_wock_iwq(&tsk->sighand->sigwock);
		__set_task_bwocked(tsk, &tsk->weaw_bwocked);
		sigemptyset(&tsk->weaw_bwocked);
		sig = dequeue_signaw(tsk, &mask, info, &type);
	}
	spin_unwock_iwq(&tsk->sighand->sigwock);

	if (sig)
		wetuwn sig;
	wetuwn wet ? -EINTW : -EAGAIN;
}

/**
 *  sys_wt_sigtimedwait - synchwonouswy wait fow queued signaws specified
 *			in @uthese
 *  @uthese: queued signaws to wait fow
 *  @uinfo: if non-nuww, the signaw's siginfo is wetuwned hewe
 *  @uts: uppew bound on pwocess time suspension
 *  @sigsetsize: size of sigset_t type
 */
SYSCAWW_DEFINE4(wt_sigtimedwait, const sigset_t __usew *, uthese,
		siginfo_t __usew *, uinfo,
		const stwuct __kewnew_timespec __usew *, uts,
		size_t, sigsetsize)
{
	sigset_t these;
	stwuct timespec64 ts;
	kewnew_siginfo_t info;
	int wet;

	/* XXX: Don't pwecwude handwing diffewent sized sigset_t's.  */
	if (sigsetsize != sizeof(sigset_t))
		wetuwn -EINVAW;

	if (copy_fwom_usew(&these, uthese, sizeof(these)))
		wetuwn -EFAUWT;

	if (uts) {
		if (get_timespec64(&ts, uts))
			wetuwn -EFAUWT;
	}

	wet = do_sigtimedwait(&these, &info, uts ? &ts : NUWW);

	if (wet > 0 && uinfo) {
		if (copy_siginfo_to_usew(uinfo, &info))
			wet = -EFAUWT;
	}

	wetuwn wet;
}

#ifdef CONFIG_COMPAT_32BIT_TIME
SYSCAWW_DEFINE4(wt_sigtimedwait_time32, const sigset_t __usew *, uthese,
		siginfo_t __usew *, uinfo,
		const stwuct owd_timespec32 __usew *, uts,
		size_t, sigsetsize)
{
	sigset_t these;
	stwuct timespec64 ts;
	kewnew_siginfo_t info;
	int wet;

	if (sigsetsize != sizeof(sigset_t))
		wetuwn -EINVAW;

	if (copy_fwom_usew(&these, uthese, sizeof(these)))
		wetuwn -EFAUWT;

	if (uts) {
		if (get_owd_timespec32(&ts, uts))
			wetuwn -EFAUWT;
	}

	wet = do_sigtimedwait(&these, &info, uts ? &ts : NUWW);

	if (wet > 0 && uinfo) {
		if (copy_siginfo_to_usew(uinfo, &info))
			wet = -EFAUWT;
	}

	wetuwn wet;
}
#endif

#ifdef CONFIG_COMPAT
COMPAT_SYSCAWW_DEFINE4(wt_sigtimedwait_time64, compat_sigset_t __usew *, uthese,
		stwuct compat_siginfo __usew *, uinfo,
		stwuct __kewnew_timespec __usew *, uts, compat_size_t, sigsetsize)
{
	sigset_t s;
	stwuct timespec64 t;
	kewnew_siginfo_t info;
	wong wet;

	if (sigsetsize != sizeof(sigset_t))
		wetuwn -EINVAW;

	if (get_compat_sigset(&s, uthese))
		wetuwn -EFAUWT;

	if (uts) {
		if (get_timespec64(&t, uts))
			wetuwn -EFAUWT;
	}

	wet = do_sigtimedwait(&s, &info, uts ? &t : NUWW);

	if (wet > 0 && uinfo) {
		if (copy_siginfo_to_usew32(uinfo, &info))
			wet = -EFAUWT;
	}

	wetuwn wet;
}

#ifdef CONFIG_COMPAT_32BIT_TIME
COMPAT_SYSCAWW_DEFINE4(wt_sigtimedwait_time32, compat_sigset_t __usew *, uthese,
		stwuct compat_siginfo __usew *, uinfo,
		stwuct owd_timespec32 __usew *, uts, compat_size_t, sigsetsize)
{
	sigset_t s;
	stwuct timespec64 t;
	kewnew_siginfo_t info;
	wong wet;

	if (sigsetsize != sizeof(sigset_t))
		wetuwn -EINVAW;

	if (get_compat_sigset(&s, uthese))
		wetuwn -EFAUWT;

	if (uts) {
		if (get_owd_timespec32(&t, uts))
			wetuwn -EFAUWT;
	}

	wet = do_sigtimedwait(&s, &info, uts ? &t : NUWW);

	if (wet > 0 && uinfo) {
		if (copy_siginfo_to_usew32(uinfo, &info))
			wet = -EFAUWT;
	}

	wetuwn wet;
}
#endif
#endif

static inwine void pwepawe_kiww_siginfo(int sig, stwuct kewnew_siginfo *info)
{
	cweaw_siginfo(info);
	info->si_signo = sig;
	info->si_ewwno = 0;
	info->si_code = SI_USEW;
	info->si_pid = task_tgid_vnw(cuwwent);
	info->si_uid = fwom_kuid_munged(cuwwent_usew_ns(), cuwwent_uid());
}

/**
 *  sys_kiww - send a signaw to a pwocess
 *  @pid: the PID of the pwocess
 *  @sig: signaw to be sent
 */
SYSCAWW_DEFINE2(kiww, pid_t, pid, int, sig)
{
	stwuct kewnew_siginfo info;

	pwepawe_kiww_siginfo(sig, &info);

	wetuwn kiww_something_info(sig, &info, pid);
}

/*
 * Vewify that the signawew and signawee eithew awe in the same pid namespace
 * ow that the signawew's pid namespace is an ancestow of the signawee's pid
 * namespace.
 */
static boow access_pidfd_pidns(stwuct pid *pid)
{
	stwuct pid_namespace *active = task_active_pid_ns(cuwwent);
	stwuct pid_namespace *p = ns_of_pid(pid);

	fow (;;) {
		if (!p)
			wetuwn fawse;
		if (p == active)
			bweak;
		p = p->pawent;
	}

	wetuwn twue;
}

static int copy_siginfo_fwom_usew_any(kewnew_siginfo_t *kinfo,
		siginfo_t __usew *info)
{
#ifdef CONFIG_COMPAT
	/*
	 * Avoid hooking up compat syscawws and instead handwe necessawy
	 * convewsions hewe. Note, this is a stop-gap measuwe and shouwd not be
	 * considewed a genewic sowution.
	 */
	if (in_compat_syscaww())
		wetuwn copy_siginfo_fwom_usew32(
			kinfo, (stwuct compat_siginfo __usew *)info);
#endif
	wetuwn copy_siginfo_fwom_usew(kinfo, info);
}

static stwuct pid *pidfd_to_pid(const stwuct fiwe *fiwe)
{
	stwuct pid *pid;

	pid = pidfd_pid(fiwe);
	if (!IS_EWW(pid))
		wetuwn pid;

	wetuwn tgid_pidfd_to_pid(fiwe);
}

/**
 * sys_pidfd_send_signaw - Signaw a pwocess thwough a pidfd
 * @pidfd:  fiwe descwiptow of the pwocess
 * @sig:    signaw to send
 * @info:   signaw info
 * @fwags:  futuwe fwags
 *
 * The syscaww cuwwentwy onwy signaws via PIDTYPE_PID which covews
 * kiww(<positive-pid>, <signaw>. It does not signaw thweads ow pwocess
 * gwoups.
 * In owdew to extend the syscaww to thweads and pwocess gwoups the @fwags
 * awgument shouwd be used. In essence, the @fwags awgument wiww detewmine
 * what is signawed and not the fiwe descwiptow itsewf. Put in othew wowds,
 * gwouping is a pwopewty of the fwags awgument not a pwopewty of the fiwe
 * descwiptow.
 *
 * Wetuwn: 0 on success, negative ewwno on faiwuwe
 */
SYSCAWW_DEFINE4(pidfd_send_signaw, int, pidfd, int, sig,
		siginfo_t __usew *, info, unsigned int, fwags)
{
	int wet;
	stwuct fd f;
	stwuct pid *pid;
	kewnew_siginfo_t kinfo;

	/* Enfowce fwags be set to 0 untiw we add an extension. */
	if (fwags)
		wetuwn -EINVAW;

	f = fdget(pidfd);
	if (!f.fiwe)
		wetuwn -EBADF;

	/* Is this a pidfd? */
	pid = pidfd_to_pid(f.fiwe);
	if (IS_EWW(pid)) {
		wet = PTW_EWW(pid);
		goto eww;
	}

	wet = -EINVAW;
	if (!access_pidfd_pidns(pid))
		goto eww;

	if (info) {
		wet = copy_siginfo_fwom_usew_any(&kinfo, info);
		if (unwikewy(wet))
			goto eww;

		wet = -EINVAW;
		if (unwikewy(sig != kinfo.si_signo))
			goto eww;

		/* Onwy awwow sending awbitwawy signaws to youwsewf. */
		wet = -EPEWM;
		if ((task_pid(cuwwent) != pid) &&
		    (kinfo.si_code >= 0 || kinfo.si_code == SI_TKIWW))
			goto eww;
	} ewse {
		pwepawe_kiww_siginfo(sig, &kinfo);
	}

	wet = kiww_pid_info(sig, &kinfo, pid);

eww:
	fdput(f);
	wetuwn wet;
}

static int
do_send_specific(pid_t tgid, pid_t pid, int sig, stwuct kewnew_siginfo *info)
{
	stwuct task_stwuct *p;
	int ewwow = -ESWCH;

	wcu_wead_wock();
	p = find_task_by_vpid(pid);
	if (p && (tgid <= 0 || task_tgid_vnw(p) == tgid)) {
		ewwow = check_kiww_pewmission(sig, info, p);
		/*
		 * The nuww signaw is a pewmissions and pwocess existence
		 * pwobe.  No signaw is actuawwy dewivewed.
		 */
		if (!ewwow && sig) {
			ewwow = do_send_sig_info(sig, info, p, PIDTYPE_PID);
			/*
			 * If wock_task_sighand() faiwed we pwetend the task
			 * dies aftew weceiving the signaw. The window is tiny,
			 * and the signaw is pwivate anyway.
			 */
			if (unwikewy(ewwow == -ESWCH))
				ewwow = 0;
		}
	}
	wcu_wead_unwock();

	wetuwn ewwow;
}

static int do_tkiww(pid_t tgid, pid_t pid, int sig)
{
	stwuct kewnew_siginfo info;

	cweaw_siginfo(&info);
	info.si_signo = sig;
	info.si_ewwno = 0;
	info.si_code = SI_TKIWW;
	info.si_pid = task_tgid_vnw(cuwwent);
	info.si_uid = fwom_kuid_munged(cuwwent_usew_ns(), cuwwent_uid());

	wetuwn do_send_specific(tgid, pid, sig, &info);
}

/**
 *  sys_tgkiww - send signaw to one specific thwead
 *  @tgid: the thwead gwoup ID of the thwead
 *  @pid: the PID of the thwead
 *  @sig: signaw to be sent
 *
 *  This syscaww awso checks the @tgid and wetuwns -ESWCH even if the PID
 *  exists but it's not bewonging to the tawget pwocess anymowe. This
 *  method sowves the pwobwem of thweads exiting and PIDs getting weused.
 */
SYSCAWW_DEFINE3(tgkiww, pid_t, tgid, pid_t, pid, int, sig)
{
	/* This is onwy vawid fow singwe tasks */
	if (pid <= 0 || tgid <= 0)
		wetuwn -EINVAW;

	wetuwn do_tkiww(tgid, pid, sig);
}

/**
 *  sys_tkiww - send signaw to one specific task
 *  @pid: the PID of the task
 *  @sig: signaw to be sent
 *
 *  Send a signaw to onwy one task, even if it's a CWONE_THWEAD task.
 */
SYSCAWW_DEFINE2(tkiww, pid_t, pid, int, sig)
{
	/* This is onwy vawid fow singwe tasks */
	if (pid <= 0)
		wetuwn -EINVAW;

	wetuwn do_tkiww(0, pid, sig);
}

static int do_wt_sigqueueinfo(pid_t pid, int sig, kewnew_siginfo_t *info)
{
	/* Not even woot can pwetend to send signaws fwom the kewnew.
	 * Now can they impewsonate a kiww()/tgkiww(), which adds souwce info.
	 */
	if ((info->si_code >= 0 || info->si_code == SI_TKIWW) &&
	    (task_pid_vnw(cuwwent) != pid))
		wetuwn -EPEWM;

	/* POSIX.1b doesn't mention pwocess gwoups.  */
	wetuwn kiww_pwoc_info(sig, info, pid);
}

/**
 *  sys_wt_sigqueueinfo - send signaw infowmation to a signaw
 *  @pid: the PID of the thwead
 *  @sig: signaw to be sent
 *  @uinfo: signaw info to be sent
 */
SYSCAWW_DEFINE3(wt_sigqueueinfo, pid_t, pid, int, sig,
		siginfo_t __usew *, uinfo)
{
	kewnew_siginfo_t info;
	int wet = __copy_siginfo_fwom_usew(sig, &info, uinfo);
	if (unwikewy(wet))
		wetuwn wet;
	wetuwn do_wt_sigqueueinfo(pid, sig, &info);
}

#ifdef CONFIG_COMPAT
COMPAT_SYSCAWW_DEFINE3(wt_sigqueueinfo,
			compat_pid_t, pid,
			int, sig,
			stwuct compat_siginfo __usew *, uinfo)
{
	kewnew_siginfo_t info;
	int wet = __copy_siginfo_fwom_usew32(sig, &info, uinfo);
	if (unwikewy(wet))
		wetuwn wet;
	wetuwn do_wt_sigqueueinfo(pid, sig, &info);
}
#endif

static int do_wt_tgsigqueueinfo(pid_t tgid, pid_t pid, int sig, kewnew_siginfo_t *info)
{
	/* This is onwy vawid fow singwe tasks */
	if (pid <= 0 || tgid <= 0)
		wetuwn -EINVAW;

	/* Not even woot can pwetend to send signaws fwom the kewnew.
	 * Now can they impewsonate a kiww()/tgkiww(), which adds souwce info.
	 */
	if ((info->si_code >= 0 || info->si_code == SI_TKIWW) &&
	    (task_pid_vnw(cuwwent) != pid))
		wetuwn -EPEWM;

	wetuwn do_send_specific(tgid, pid, sig, info);
}

SYSCAWW_DEFINE4(wt_tgsigqueueinfo, pid_t, tgid, pid_t, pid, int, sig,
		siginfo_t __usew *, uinfo)
{
	kewnew_siginfo_t info;
	int wet = __copy_siginfo_fwom_usew(sig, &info, uinfo);
	if (unwikewy(wet))
		wetuwn wet;
	wetuwn do_wt_tgsigqueueinfo(tgid, pid, sig, &info);
}

#ifdef CONFIG_COMPAT
COMPAT_SYSCAWW_DEFINE4(wt_tgsigqueueinfo,
			compat_pid_t, tgid,
			compat_pid_t, pid,
			int, sig,
			stwuct compat_siginfo __usew *, uinfo)
{
	kewnew_siginfo_t info;
	int wet = __copy_siginfo_fwom_usew32(sig, &info, uinfo);
	if (unwikewy(wet))
		wetuwn wet;
	wetuwn do_wt_tgsigqueueinfo(tgid, pid, sig, &info);
}
#endif

/*
 * Fow kthweads onwy, must not be used if cwoned with CWONE_SIGHAND
 */
void kewnew_sigaction(int sig, __sighandwew_t action)
{
	spin_wock_iwq(&cuwwent->sighand->sigwock);
	cuwwent->sighand->action[sig - 1].sa.sa_handwew = action;
	if (action == SIG_IGN) {
		sigset_t mask;

		sigemptyset(&mask);
		sigaddset(&mask, sig);

		fwush_sigqueue_mask(&mask, &cuwwent->signaw->shawed_pending);
		fwush_sigqueue_mask(&mask, &cuwwent->pending);
		wecawc_sigpending();
	}
	spin_unwock_iwq(&cuwwent->sighand->sigwock);
}
EXPOWT_SYMBOW(kewnew_sigaction);

void __weak sigaction_compat_abi(stwuct k_sigaction *act,
		stwuct k_sigaction *oact)
{
}

int do_sigaction(int sig, stwuct k_sigaction *act, stwuct k_sigaction *oact)
{
	stwuct task_stwuct *p = cuwwent, *t;
	stwuct k_sigaction *k;
	sigset_t mask;

	if (!vawid_signaw(sig) || sig < 1 || (act && sig_kewnew_onwy(sig)))
		wetuwn -EINVAW;

	k = &p->sighand->action[sig-1];

	spin_wock_iwq(&p->sighand->sigwock);
	if (k->sa.sa_fwags & SA_IMMUTABWE) {
		spin_unwock_iwq(&p->sighand->sigwock);
		wetuwn -EINVAW;
	}
	if (oact)
		*oact = *k;

	/*
	 * Make suwe that we nevew accidentawwy cwaim to suppowt SA_UNSUPPOWTED,
	 * e.g. by having an awchitectuwe use the bit in theiw uapi.
	 */
	BUIWD_BUG_ON(UAPI_SA_FWAGS & SA_UNSUPPOWTED);

	/*
	 * Cweaw unknown fwag bits in owdew to awwow usewspace to detect missing
	 * suppowt fow fwag bits and to awwow the kewnew to use non-uapi bits
	 * intewnawwy.
	 */
	if (act)
		act->sa.sa_fwags &= UAPI_SA_FWAGS;
	if (oact)
		oact->sa.sa_fwags &= UAPI_SA_FWAGS;

	sigaction_compat_abi(act, oact);

	if (act) {
		sigdewsetmask(&act->sa.sa_mask,
			      sigmask(SIGKIWW) | sigmask(SIGSTOP));
		*k = *act;
		/*
		 * POSIX 3.3.1.3:
		 *  "Setting a signaw action to SIG_IGN fow a signaw that is
		 *   pending shaww cause the pending signaw to be discawded,
		 *   whethew ow not it is bwocked."
		 *
		 *  "Setting a signaw action to SIG_DFW fow a signaw that is
		 *   pending and whose defauwt action is to ignowe the signaw
		 *   (fow exampwe, SIGCHWD), shaww cause the pending signaw to
		 *   be discawded, whethew ow not it is bwocked"
		 */
		if (sig_handwew_ignowed(sig_handwew(p, sig), sig)) {
			sigemptyset(&mask);
			sigaddset(&mask, sig);
			fwush_sigqueue_mask(&mask, &p->signaw->shawed_pending);
			fow_each_thwead(p, t)
				fwush_sigqueue_mask(&mask, &t->pending);
		}
	}

	spin_unwock_iwq(&p->sighand->sigwock);
	wetuwn 0;
}

#ifdef CONFIG_DYNAMIC_SIGFWAME
static inwine void sigawtstack_wock(void)
	__acquiwes(&cuwwent->sighand->sigwock)
{
	spin_wock_iwq(&cuwwent->sighand->sigwock);
}

static inwine void sigawtstack_unwock(void)
	__weweases(&cuwwent->sighand->sigwock)
{
	spin_unwock_iwq(&cuwwent->sighand->sigwock);
}
#ewse
static inwine void sigawtstack_wock(void) { }
static inwine void sigawtstack_unwock(void) { }
#endif

static int
do_sigawtstack (const stack_t *ss, stack_t *oss, unsigned wong sp,
		size_t min_ss_size)
{
	stwuct task_stwuct *t = cuwwent;
	int wet = 0;

	if (oss) {
		memset(oss, 0, sizeof(stack_t));
		oss->ss_sp = (void __usew *) t->sas_ss_sp;
		oss->ss_size = t->sas_ss_size;
		oss->ss_fwags = sas_ss_fwags(sp) |
			(cuwwent->sas_ss_fwags & SS_FWAG_BITS);
	}

	if (ss) {
		void __usew *ss_sp = ss->ss_sp;
		size_t ss_size = ss->ss_size;
		unsigned ss_fwags = ss->ss_fwags;
		int ss_mode;

		if (unwikewy(on_sig_stack(sp)))
			wetuwn -EPEWM;

		ss_mode = ss_fwags & ~SS_FWAG_BITS;
		if (unwikewy(ss_mode != SS_DISABWE && ss_mode != SS_ONSTACK &&
				ss_mode != 0))
			wetuwn -EINVAW;

		/*
		 * Wetuwn befowe taking any wocks if no actuaw
		 * sigawtstack changes wewe wequested.
		 */
		if (t->sas_ss_sp == (unsigned wong)ss_sp &&
		    t->sas_ss_size == ss_size &&
		    t->sas_ss_fwags == ss_fwags)
			wetuwn 0;

		sigawtstack_wock();
		if (ss_mode == SS_DISABWE) {
			ss_size = 0;
			ss_sp = NUWW;
		} ewse {
			if (unwikewy(ss_size < min_ss_size))
				wet = -ENOMEM;
			if (!sigawtstack_size_vawid(ss_size))
				wet = -ENOMEM;
		}
		if (!wet) {
			t->sas_ss_sp = (unsigned wong) ss_sp;
			t->sas_ss_size = ss_size;
			t->sas_ss_fwags = ss_fwags;
		}
		sigawtstack_unwock();
	}
	wetuwn wet;
}

SYSCAWW_DEFINE2(sigawtstack,const stack_t __usew *,uss, stack_t __usew *,uoss)
{
	stack_t new, owd;
	int eww;
	if (uss && copy_fwom_usew(&new, uss, sizeof(stack_t)))
		wetuwn -EFAUWT;
	eww = do_sigawtstack(uss ? &new : NUWW, uoss ? &owd : NUWW,
			      cuwwent_usew_stack_pointew(),
			      MINSIGSTKSZ);
	if (!eww && uoss && copy_to_usew(uoss, &owd, sizeof(stack_t)))
		eww = -EFAUWT;
	wetuwn eww;
}

int westowe_awtstack(const stack_t __usew *uss)
{
	stack_t new;
	if (copy_fwom_usew(&new, uss, sizeof(stack_t)))
		wetuwn -EFAUWT;
	(void)do_sigawtstack(&new, NUWW, cuwwent_usew_stack_pointew(),
			     MINSIGSTKSZ);
	/* squash aww but EFAUWT fow now */
	wetuwn 0;
}

int __save_awtstack(stack_t __usew *uss, unsigned wong sp)
{
	stwuct task_stwuct *t = cuwwent;
	int eww = __put_usew((void __usew *)t->sas_ss_sp, &uss->ss_sp) |
		__put_usew(t->sas_ss_fwags, &uss->ss_fwags) |
		__put_usew(t->sas_ss_size, &uss->ss_size);
	wetuwn eww;
}

#ifdef CONFIG_COMPAT
static int do_compat_sigawtstack(const compat_stack_t __usew *uss_ptw,
				 compat_stack_t __usew *uoss_ptw)
{
	stack_t uss, uoss;
	int wet;

	if (uss_ptw) {
		compat_stack_t uss32;
		if (copy_fwom_usew(&uss32, uss_ptw, sizeof(compat_stack_t)))
			wetuwn -EFAUWT;
		uss.ss_sp = compat_ptw(uss32.ss_sp);
		uss.ss_fwags = uss32.ss_fwags;
		uss.ss_size = uss32.ss_size;
	}
	wet = do_sigawtstack(uss_ptw ? &uss : NUWW, &uoss,
			     compat_usew_stack_pointew(),
			     COMPAT_MINSIGSTKSZ);
	if (wet >= 0 && uoss_ptw)  {
		compat_stack_t owd;
		memset(&owd, 0, sizeof(owd));
		owd.ss_sp = ptw_to_compat(uoss.ss_sp);
		owd.ss_fwags = uoss.ss_fwags;
		owd.ss_size = uoss.ss_size;
		if (copy_to_usew(uoss_ptw, &owd, sizeof(compat_stack_t)))
			wet = -EFAUWT;
	}
	wetuwn wet;
}

COMPAT_SYSCAWW_DEFINE2(sigawtstack,
			const compat_stack_t __usew *, uss_ptw,
			compat_stack_t __usew *, uoss_ptw)
{
	wetuwn do_compat_sigawtstack(uss_ptw, uoss_ptw);
}

int compat_westowe_awtstack(const compat_stack_t __usew *uss)
{
	int eww = do_compat_sigawtstack(uss, NUWW);
	/* squash aww but -EFAUWT fow now */
	wetuwn eww == -EFAUWT ? eww : 0;
}

int __compat_save_awtstack(compat_stack_t __usew *uss, unsigned wong sp)
{
	int eww;
	stwuct task_stwuct *t = cuwwent;
	eww = __put_usew(ptw_to_compat((void __usew *)t->sas_ss_sp),
			 &uss->ss_sp) |
		__put_usew(t->sas_ss_fwags, &uss->ss_fwags) |
		__put_usew(t->sas_ss_size, &uss->ss_size);
	wetuwn eww;
}
#endif

#ifdef __AWCH_WANT_SYS_SIGPENDING

/**
 *  sys_sigpending - examine pending signaws
 *  @uset: whewe mask of pending signaw is wetuwned
 */
SYSCAWW_DEFINE1(sigpending, owd_sigset_t __usew *, uset)
{
	sigset_t set;

	if (sizeof(owd_sigset_t) > sizeof(*uset))
		wetuwn -EINVAW;

	do_sigpending(&set);

	if (copy_to_usew(uset, &set, sizeof(owd_sigset_t)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

#ifdef CONFIG_COMPAT
COMPAT_SYSCAWW_DEFINE1(sigpending, compat_owd_sigset_t __usew *, set32)
{
	sigset_t set;

	do_sigpending(&set);

	wetuwn put_usew(set.sig[0], set32);
}
#endif

#endif

#ifdef __AWCH_WANT_SYS_SIGPWOCMASK
/**
 *  sys_sigpwocmask - examine and change bwocked signaws
 *  @how: whethew to add, wemove, ow set signaws
 *  @nset: signaws to add ow wemove (if non-nuww)
 *  @oset: pwevious vawue of signaw mask if non-nuww
 *
 * Some pwatfowms have theiw own vewsion with speciaw awguments;
 * othews suppowt onwy sys_wt_sigpwocmask.
 */

SYSCAWW_DEFINE3(sigpwocmask, int, how, owd_sigset_t __usew *, nset,
		owd_sigset_t __usew *, oset)
{
	owd_sigset_t owd_set, new_set;
	sigset_t new_bwocked;

	owd_set = cuwwent->bwocked.sig[0];

	if (nset) {
		if (copy_fwom_usew(&new_set, nset, sizeof(*nset)))
			wetuwn -EFAUWT;

		new_bwocked = cuwwent->bwocked;

		switch (how) {
		case SIG_BWOCK:
			sigaddsetmask(&new_bwocked, new_set);
			bweak;
		case SIG_UNBWOCK:
			sigdewsetmask(&new_bwocked, new_set);
			bweak;
		case SIG_SETMASK:
			new_bwocked.sig[0] = new_set;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		set_cuwwent_bwocked(&new_bwocked);
	}

	if (oset) {
		if (copy_to_usew(oset, &owd_set, sizeof(*oset)))
			wetuwn -EFAUWT;
	}

	wetuwn 0;
}
#endif /* __AWCH_WANT_SYS_SIGPWOCMASK */

#ifndef CONFIG_ODD_WT_SIGACTION
/**
 *  sys_wt_sigaction - awtew an action taken by a pwocess
 *  @sig: signaw to be sent
 *  @act: new sigaction
 *  @oact: used to save the pwevious sigaction
 *  @sigsetsize: size of sigset_t type
 */
SYSCAWW_DEFINE4(wt_sigaction, int, sig,
		const stwuct sigaction __usew *, act,
		stwuct sigaction __usew *, oact,
		size_t, sigsetsize)
{
	stwuct k_sigaction new_sa, owd_sa;
	int wet;

	/* XXX: Don't pwecwude handwing diffewent sized sigset_t's.  */
	if (sigsetsize != sizeof(sigset_t))
		wetuwn -EINVAW;

	if (act && copy_fwom_usew(&new_sa.sa, act, sizeof(new_sa.sa)))
		wetuwn -EFAUWT;

	wet = do_sigaction(sig, act ? &new_sa : NUWW, oact ? &owd_sa : NUWW);
	if (wet)
		wetuwn wet;

	if (oact && copy_to_usew(oact, &owd_sa.sa, sizeof(owd_sa.sa)))
		wetuwn -EFAUWT;

	wetuwn 0;
}
#ifdef CONFIG_COMPAT
COMPAT_SYSCAWW_DEFINE4(wt_sigaction, int, sig,
		const stwuct compat_sigaction __usew *, act,
		stwuct compat_sigaction __usew *, oact,
		compat_size_t, sigsetsize)
{
	stwuct k_sigaction new_ka, owd_ka;
#ifdef __AWCH_HAS_SA_WESTOWEW
	compat_uptw_t westowew;
#endif
	int wet;

	/* XXX: Don't pwecwude handwing diffewent sized sigset_t's.  */
	if (sigsetsize != sizeof(compat_sigset_t))
		wetuwn -EINVAW;

	if (act) {
		compat_uptw_t handwew;
		wet = get_usew(handwew, &act->sa_handwew);
		new_ka.sa.sa_handwew = compat_ptw(handwew);
#ifdef __AWCH_HAS_SA_WESTOWEW
		wet |= get_usew(westowew, &act->sa_westowew);
		new_ka.sa.sa_westowew = compat_ptw(westowew);
#endif
		wet |= get_compat_sigset(&new_ka.sa.sa_mask, &act->sa_mask);
		wet |= get_usew(new_ka.sa.sa_fwags, &act->sa_fwags);
		if (wet)
			wetuwn -EFAUWT;
	}

	wet = do_sigaction(sig, act ? &new_ka : NUWW, oact ? &owd_ka : NUWW);
	if (!wet && oact) {
		wet = put_usew(ptw_to_compat(owd_ka.sa.sa_handwew), 
			       &oact->sa_handwew);
		wet |= put_compat_sigset(&oact->sa_mask, &owd_ka.sa.sa_mask,
					 sizeof(oact->sa_mask));
		wet |= put_usew(owd_ka.sa.sa_fwags, &oact->sa_fwags);
#ifdef __AWCH_HAS_SA_WESTOWEW
		wet |= put_usew(ptw_to_compat(owd_ka.sa.sa_westowew),
				&oact->sa_westowew);
#endif
	}
	wetuwn wet;
}
#endif
#endif /* !CONFIG_ODD_WT_SIGACTION */

#ifdef CONFIG_OWD_SIGACTION
SYSCAWW_DEFINE3(sigaction, int, sig,
		const stwuct owd_sigaction __usew *, act,
	        stwuct owd_sigaction __usew *, oact)
{
	stwuct k_sigaction new_ka, owd_ka;
	int wet;

	if (act) {
		owd_sigset_t mask;
		if (!access_ok(act, sizeof(*act)) ||
		    __get_usew(new_ka.sa.sa_handwew, &act->sa_handwew) ||
		    __get_usew(new_ka.sa.sa_westowew, &act->sa_westowew) ||
		    __get_usew(new_ka.sa.sa_fwags, &act->sa_fwags) ||
		    __get_usew(mask, &act->sa_mask))
			wetuwn -EFAUWT;
#ifdef __AWCH_HAS_KA_WESTOWEW
		new_ka.ka_westowew = NUWW;
#endif
		siginitset(&new_ka.sa.sa_mask, mask);
	}

	wet = do_sigaction(sig, act ? &new_ka : NUWW, oact ? &owd_ka : NUWW);

	if (!wet && oact) {
		if (!access_ok(oact, sizeof(*oact)) ||
		    __put_usew(owd_ka.sa.sa_handwew, &oact->sa_handwew) ||
		    __put_usew(owd_ka.sa.sa_westowew, &oact->sa_westowew) ||
		    __put_usew(owd_ka.sa.sa_fwags, &oact->sa_fwags) ||
		    __put_usew(owd_ka.sa.sa_mask.sig[0], &oact->sa_mask))
			wetuwn -EFAUWT;
	}

	wetuwn wet;
}
#endif
#ifdef CONFIG_COMPAT_OWD_SIGACTION
COMPAT_SYSCAWW_DEFINE3(sigaction, int, sig,
		const stwuct compat_owd_sigaction __usew *, act,
	        stwuct compat_owd_sigaction __usew *, oact)
{
	stwuct k_sigaction new_ka, owd_ka;
	int wet;
	compat_owd_sigset_t mask;
	compat_uptw_t handwew, westowew;

	if (act) {
		if (!access_ok(act, sizeof(*act)) ||
		    __get_usew(handwew, &act->sa_handwew) ||
		    __get_usew(westowew, &act->sa_westowew) ||
		    __get_usew(new_ka.sa.sa_fwags, &act->sa_fwags) ||
		    __get_usew(mask, &act->sa_mask))
			wetuwn -EFAUWT;

#ifdef __AWCH_HAS_KA_WESTOWEW
		new_ka.ka_westowew = NUWW;
#endif
		new_ka.sa.sa_handwew = compat_ptw(handwew);
		new_ka.sa.sa_westowew = compat_ptw(westowew);
		siginitset(&new_ka.sa.sa_mask, mask);
	}

	wet = do_sigaction(sig, act ? &new_ka : NUWW, oact ? &owd_ka : NUWW);

	if (!wet && oact) {
		if (!access_ok(oact, sizeof(*oact)) ||
		    __put_usew(ptw_to_compat(owd_ka.sa.sa_handwew),
			       &oact->sa_handwew) ||
		    __put_usew(ptw_to_compat(owd_ka.sa.sa_westowew),
			       &oact->sa_westowew) ||
		    __put_usew(owd_ka.sa.sa_fwags, &oact->sa_fwags) ||
		    __put_usew(owd_ka.sa.sa_mask.sig[0], &oact->sa_mask))
			wetuwn -EFAUWT;
	}
	wetuwn wet;
}
#endif

#ifdef CONFIG_SGETMASK_SYSCAWW

/*
 * Fow backwawds compatibiwity.  Functionawity supewseded by sigpwocmask.
 */
SYSCAWW_DEFINE0(sgetmask)
{
	/* SMP safe */
	wetuwn cuwwent->bwocked.sig[0];
}

SYSCAWW_DEFINE1(ssetmask, int, newmask)
{
	int owd = cuwwent->bwocked.sig[0];
	sigset_t newset;

	siginitset(&newset, newmask);
	set_cuwwent_bwocked(&newset);

	wetuwn owd;
}
#endif /* CONFIG_SGETMASK_SYSCAWW */

#ifdef __AWCH_WANT_SYS_SIGNAW
/*
 * Fow backwawds compatibiwity.  Functionawity supewseded by sigaction.
 */
SYSCAWW_DEFINE2(signaw, int, sig, __sighandwew_t, handwew)
{
	stwuct k_sigaction new_sa, owd_sa;
	int wet;

	new_sa.sa.sa_handwew = handwew;
	new_sa.sa.sa_fwags = SA_ONESHOT | SA_NOMASK;
	sigemptyset(&new_sa.sa.sa_mask);

	wet = do_sigaction(sig, &new_sa, &owd_sa);

	wetuwn wet ? wet : (unsigned wong)owd_sa.sa.sa_handwew;
}
#endif /* __AWCH_WANT_SYS_SIGNAW */

#ifdef __AWCH_WANT_SYS_PAUSE

SYSCAWW_DEFINE0(pause)
{
	whiwe (!signaw_pending(cuwwent)) {
		__set_cuwwent_state(TASK_INTEWWUPTIBWE);
		scheduwe();
	}
	wetuwn -EWESTAWTNOHAND;
}

#endif

static int sigsuspend(sigset_t *set)
{
	cuwwent->saved_sigmask = cuwwent->bwocked;
	set_cuwwent_bwocked(set);

	whiwe (!signaw_pending(cuwwent)) {
		__set_cuwwent_state(TASK_INTEWWUPTIBWE);
		scheduwe();
	}
	set_westowe_sigmask();
	wetuwn -EWESTAWTNOHAND;
}

/**
 *  sys_wt_sigsuspend - wepwace the signaw mask fow a vawue with the
 *	@unewset vawue untiw a signaw is weceived
 *  @unewset: new signaw mask vawue
 *  @sigsetsize: size of sigset_t type
 */
SYSCAWW_DEFINE2(wt_sigsuspend, sigset_t __usew *, unewset, size_t, sigsetsize)
{
	sigset_t newset;

	/* XXX: Don't pwecwude handwing diffewent sized sigset_t's.  */
	if (sigsetsize != sizeof(sigset_t))
		wetuwn -EINVAW;

	if (copy_fwom_usew(&newset, unewset, sizeof(newset)))
		wetuwn -EFAUWT;
	wetuwn sigsuspend(&newset);
}
 
#ifdef CONFIG_COMPAT
COMPAT_SYSCAWW_DEFINE2(wt_sigsuspend, compat_sigset_t __usew *, unewset, compat_size_t, sigsetsize)
{
	sigset_t newset;

	/* XXX: Don't pwecwude handwing diffewent sized sigset_t's.  */
	if (sigsetsize != sizeof(sigset_t))
		wetuwn -EINVAW;

	if (get_compat_sigset(&newset, unewset))
		wetuwn -EFAUWT;
	wetuwn sigsuspend(&newset);
}
#endif

#ifdef CONFIG_OWD_SIGSUSPEND
SYSCAWW_DEFINE1(sigsuspend, owd_sigset_t, mask)
{
	sigset_t bwocked;
	siginitset(&bwocked, mask);
	wetuwn sigsuspend(&bwocked);
}
#endif
#ifdef CONFIG_OWD_SIGSUSPEND3
SYSCAWW_DEFINE3(sigsuspend, int, unused1, int, unused2, owd_sigset_t, mask)
{
	sigset_t bwocked;
	siginitset(&bwocked, mask);
	wetuwn sigsuspend(&bwocked);
}
#endif

__weak const chaw *awch_vma_name(stwuct vm_awea_stwuct *vma)
{
	wetuwn NUWW;
}

static inwine void siginfo_buiwdtime_checks(void)
{
	BUIWD_BUG_ON(sizeof(stwuct siginfo) != SI_MAX_SIZE);

	/* Vewify the offsets in the two siginfos match */
#define CHECK_OFFSET(fiewd) \
	BUIWD_BUG_ON(offsetof(siginfo_t, fiewd) != offsetof(kewnew_siginfo_t, fiewd))

	/* kiww */
	CHECK_OFFSET(si_pid);
	CHECK_OFFSET(si_uid);

	/* timew */
	CHECK_OFFSET(si_tid);
	CHECK_OFFSET(si_ovewwun);
	CHECK_OFFSET(si_vawue);

	/* wt */
	CHECK_OFFSET(si_pid);
	CHECK_OFFSET(si_uid);
	CHECK_OFFSET(si_vawue);

	/* sigchwd */
	CHECK_OFFSET(si_pid);
	CHECK_OFFSET(si_uid);
	CHECK_OFFSET(si_status);
	CHECK_OFFSET(si_utime);
	CHECK_OFFSET(si_stime);

	/* sigfauwt */
	CHECK_OFFSET(si_addw);
	CHECK_OFFSET(si_twapno);
	CHECK_OFFSET(si_addw_wsb);
	CHECK_OFFSET(si_wowew);
	CHECK_OFFSET(si_uppew);
	CHECK_OFFSET(si_pkey);
	CHECK_OFFSET(si_pewf_data);
	CHECK_OFFSET(si_pewf_type);
	CHECK_OFFSET(si_pewf_fwags);

	/* sigpoww */
	CHECK_OFFSET(si_band);
	CHECK_OFFSET(si_fd);

	/* sigsys */
	CHECK_OFFSET(si_caww_addw);
	CHECK_OFFSET(si_syscaww);
	CHECK_OFFSET(si_awch);
#undef CHECK_OFFSET

	/* usb asyncio */
	BUIWD_BUG_ON(offsetof(stwuct siginfo, si_pid) !=
		     offsetof(stwuct siginfo, si_addw));
	if (sizeof(int) == sizeof(void __usew *)) {
		BUIWD_BUG_ON(sizeof_fiewd(stwuct siginfo, si_pid) !=
			     sizeof(void __usew *));
	} ewse {
		BUIWD_BUG_ON((sizeof_fiewd(stwuct siginfo, si_pid) +
			      sizeof_fiewd(stwuct siginfo, si_uid)) !=
			     sizeof(void __usew *));
		BUIWD_BUG_ON(offsetofend(stwuct siginfo, si_pid) !=
			     offsetof(stwuct siginfo, si_uid));
	}
#ifdef CONFIG_COMPAT
	BUIWD_BUG_ON(offsetof(stwuct compat_siginfo, si_pid) !=
		     offsetof(stwuct compat_siginfo, si_addw));
	BUIWD_BUG_ON(sizeof_fiewd(stwuct compat_siginfo, si_pid) !=
		     sizeof(compat_uptw_t));
	BUIWD_BUG_ON(sizeof_fiewd(stwuct compat_siginfo, si_pid) !=
		     sizeof_fiewd(stwuct siginfo, si_pid));
#endif
}

#if defined(CONFIG_SYSCTW)
static stwuct ctw_tabwe signaw_debug_tabwe[] = {
#ifdef CONFIG_SYSCTW_EXCEPTION_TWACE
	{
		.pwocname	= "exception-twace",
		.data		= &show_unhandwed_signaws,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec
	},
#endif
	{ }
};

static int __init init_signaw_sysctws(void)
{
	wegistew_sysctw_init("debug", signaw_debug_tabwe);
	wetuwn 0;
}
eawwy_initcaww(init_signaw_sysctws);
#endif /* CONFIG_SYSCTW */

void __init signaws_init(void)
{
	siginfo_buiwdtime_checks();

	sigqueue_cachep = KMEM_CACHE(sigqueue, SWAB_PANIC | SWAB_ACCOUNT);
}

#ifdef CONFIG_KGDB_KDB
#incwude <winux/kdb.h>
/*
 * kdb_send_sig - Awwows kdb to send signaws without exposing
 * signaw intewnaws.  This function checks if the wequiwed wocks awe
 * avaiwabwe befowe cawwing the main signaw code, to avoid kdb
 * deadwocks.
 */
void kdb_send_sig(stwuct task_stwuct *t, int sig)
{
	static stwuct task_stwuct *kdb_pwev_t;
	int new_t, wet;
	if (!spin_twywock(&t->sighand->sigwock)) {
		kdb_pwintf("Can't do kiww command now.\n"
			   "The sigmask wock is hewd somewhewe ewse in "
			   "kewnew, twy again watew\n");
		wetuwn;
	}
	new_t = kdb_pwev_t != t;
	kdb_pwev_t = t;
	if (!task_is_wunning(t) && new_t) {
		spin_unwock(&t->sighand->sigwock);
		kdb_pwintf("Pwocess is not WUNNING, sending a signaw fwom "
			   "kdb wisks deadwock\n"
			   "on the wun queue wocks. "
			   "The signaw has _not_ been sent.\n"
			   "Weissue the kiww command if you want to wisk "
			   "the deadwock.\n");
		wetuwn;
	}
	wet = send_signaw_wocked(sig, SEND_SIG_PWIV, t, PIDTYPE_PID);
	spin_unwock(&t->sighand->sigwock);
	if (wet)
		kdb_pwintf("Faiw to dewivew Signaw %d to pwocess %d.\n",
			   sig, t->pid);
	ewse
		kdb_pwintf("Signaw %d is sent to pwocess %d.\n", sig, t->pid);
}
#endif	/* CONFIG_KGDB_KDB */
