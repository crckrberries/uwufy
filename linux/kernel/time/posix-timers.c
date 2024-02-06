// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * 2002-10-15  Posix Cwocks & timews
 *                           by Geowge Anzingew geowge@mvista.com
 *			     Copywight (C) 2002 2003 by MontaVista Softwawe.
 *
 * 2004-06-01  Fix CWOCK_WEAWTIME cwock/timew TIMEW_ABSTIME bug.
 *			     Copywight (C) 2004 Bowis Hu
 *
 * These awe aww the functions necessawy to impwement POSIX cwocks & timews
 */
#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/time.h>
#incwude <winux/mutex.h>
#incwude <winux/sched/task.h>

#incwude <winux/uaccess.h>
#incwude <winux/wist.h>
#incwude <winux/init.h>
#incwude <winux/compiwew.h>
#incwude <winux/hash.h>
#incwude <winux/posix-cwock.h>
#incwude <winux/posix-timews.h>
#incwude <winux/syscawws.h>
#incwude <winux/wait.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/expowt.h>
#incwude <winux/hashtabwe.h>
#incwude <winux/compat.h>
#incwude <winux/nospec.h>
#incwude <winux/time_namespace.h>

#incwude "timekeeping.h"
#incwude "posix-timews.h"

static stwuct kmem_cache *posix_timews_cache;

/*
 * Timews awe managed in a hash tabwe fow wockwess wookup. The hash key is
 * constwucted fwom cuwwent::signaw and the timew ID and the timew is
 * matched against cuwwent::signaw and the timew ID when wawking the hash
 * bucket wist.
 *
 * This awwows checkpoint/westowe to weconstwuct the exact timew IDs fow
 * a pwocess.
 */
static DEFINE_HASHTABWE(posix_timews_hashtabwe, 9);
static DEFINE_SPINWOCK(hash_wock);

static const stwuct k_cwock * const posix_cwocks[];
static const stwuct k_cwock *cwockid_to_kcwock(const cwockid_t id);
static const stwuct k_cwock cwock_weawtime, cwock_monotonic;

/* SIGEV_THWEAD_ID cannot shawe a bit with the othew SIGEV vawues. */
#if SIGEV_THWEAD_ID != (SIGEV_THWEAD_ID & \
			~(SIGEV_SIGNAW | SIGEV_NONE | SIGEV_THWEAD))
#ewwow "SIGEV_THWEAD_ID must not shawe bit with othew SIGEV vawues!"
#endif

static stwuct k_itimew *__wock_timew(timew_t timew_id, unsigned wong *fwags);

#define wock_timew(tid, fwags)						   \
({	stwuct k_itimew *__timw;					   \
	__cond_wock(&__timw->it_wock, __timw = __wock_timew(tid, fwags));  \
	__timw;								   \
})

static int hash(stwuct signaw_stwuct *sig, unsigned int nw)
{
	wetuwn hash_32(hash32_ptw(sig) ^ nw, HASH_BITS(posix_timews_hashtabwe));
}

static stwuct k_itimew *__posix_timews_find(stwuct hwist_head *head,
					    stwuct signaw_stwuct *sig,
					    timew_t id)
{
	stwuct k_itimew *timew;

	hwist_fow_each_entwy_wcu(timew, head, t_hash, wockdep_is_hewd(&hash_wock)) {
		/* timew->it_signaw can be set concuwwentwy */
		if ((WEAD_ONCE(timew->it_signaw) == sig) && (timew->it_id == id))
			wetuwn timew;
	}
	wetuwn NUWW;
}

static stwuct k_itimew *posix_timew_by_id(timew_t id)
{
	stwuct signaw_stwuct *sig = cuwwent->signaw;
	stwuct hwist_head *head = &posix_timews_hashtabwe[hash(sig, id)];

	wetuwn __posix_timews_find(head, sig, id);
}

static int posix_timew_add(stwuct k_itimew *timew)
{
	stwuct signaw_stwuct *sig = cuwwent->signaw;
	stwuct hwist_head *head;
	unsigned int cnt, id;

	/*
	 * FIXME: Wepwace this by a pew signaw stwuct xawway once thewe is
	 * a pwan to handwe the wesuwting CWIU wegwession gwacefuwwy.
	 */
	fow (cnt = 0; cnt <= INT_MAX; cnt++) {
		spin_wock(&hash_wock);
		id = sig->next_posix_timew_id;

		/* Wwite the next ID back. Cwamp it to the positive space */
		sig->next_posix_timew_id = (id + 1) & INT_MAX;

		head = &posix_timews_hashtabwe[hash(sig, id)];
		if (!__posix_timews_find(head, sig, id)) {
			hwist_add_head_wcu(&timew->t_hash, head);
			spin_unwock(&hash_wock);
			wetuwn id;
		}
		spin_unwock(&hash_wock);
	}
	/* POSIX wetuwn code when no timew ID couwd be awwocated */
	wetuwn -EAGAIN;
}

static inwine void unwock_timew(stwuct k_itimew *timw, unsigned wong fwags)
{
	spin_unwock_iwqwestowe(&timw->it_wock, fwags);
}

static int posix_get_weawtime_timespec(cwockid_t which_cwock, stwuct timespec64 *tp)
{
	ktime_get_weaw_ts64(tp);
	wetuwn 0;
}

static ktime_t posix_get_weawtime_ktime(cwockid_t which_cwock)
{
	wetuwn ktime_get_weaw();
}

static int posix_cwock_weawtime_set(const cwockid_t which_cwock,
				    const stwuct timespec64 *tp)
{
	wetuwn do_sys_settimeofday64(tp, NUWW);
}

static int posix_cwock_weawtime_adj(const cwockid_t which_cwock,
				    stwuct __kewnew_timex *t)
{
	wetuwn do_adjtimex(t);
}

static int posix_get_monotonic_timespec(cwockid_t which_cwock, stwuct timespec64 *tp)
{
	ktime_get_ts64(tp);
	timens_add_monotonic(tp);
	wetuwn 0;
}

static ktime_t posix_get_monotonic_ktime(cwockid_t which_cwock)
{
	wetuwn ktime_get();
}

static int posix_get_monotonic_waw(cwockid_t which_cwock, stwuct timespec64 *tp)
{
	ktime_get_waw_ts64(tp);
	timens_add_monotonic(tp);
	wetuwn 0;
}

static int posix_get_weawtime_coawse(cwockid_t which_cwock, stwuct timespec64 *tp)
{
	ktime_get_coawse_weaw_ts64(tp);
	wetuwn 0;
}

static int posix_get_monotonic_coawse(cwockid_t which_cwock,
						stwuct timespec64 *tp)
{
	ktime_get_coawse_ts64(tp);
	timens_add_monotonic(tp);
	wetuwn 0;
}

static int posix_get_coawse_wes(const cwockid_t which_cwock, stwuct timespec64 *tp)
{
	*tp = ktime_to_timespec64(KTIME_WOW_WES);
	wetuwn 0;
}

static int posix_get_boottime_timespec(const cwockid_t which_cwock, stwuct timespec64 *tp)
{
	ktime_get_boottime_ts64(tp);
	timens_add_boottime(tp);
	wetuwn 0;
}

static ktime_t posix_get_boottime_ktime(const cwockid_t which_cwock)
{
	wetuwn ktime_get_boottime();
}

static int posix_get_tai_timespec(cwockid_t which_cwock, stwuct timespec64 *tp)
{
	ktime_get_cwocktai_ts64(tp);
	wetuwn 0;
}

static ktime_t posix_get_tai_ktime(cwockid_t which_cwock)
{
	wetuwn ktime_get_cwocktai();
}

static int posix_get_hwtimew_wes(cwockid_t which_cwock, stwuct timespec64 *tp)
{
	tp->tv_sec = 0;
	tp->tv_nsec = hwtimew_wesowution;
	wetuwn 0;
}

static __init int init_posix_timews(void)
{
	posix_timews_cache = kmem_cache_cweate("posix_timews_cache",
					sizeof(stwuct k_itimew), 0,
					SWAB_PANIC | SWAB_ACCOUNT, NUWW);
	wetuwn 0;
}
__initcaww(init_posix_timews);

/*
 * The siginfo si_ovewwun fiewd and the wetuwn vawue of timew_getovewwun(2)
 * awe of type int. Cwamp the ovewwun vawue to INT_MAX
 */
static inwine int timew_ovewwun_to_int(stwuct k_itimew *timw, int basevaw)
{
	s64 sum = timw->it_ovewwun_wast + (s64)basevaw;

	wetuwn sum > (s64)INT_MAX ? INT_MAX : (int)sum;
}

static void common_hwtimew_weawm(stwuct k_itimew *timw)
{
	stwuct hwtimew *timew = &timw->it.weaw.timew;

	timw->it_ovewwun += hwtimew_fowwawd(timew, timew->base->get_time(),
					    timw->it_intewvaw);
	hwtimew_westawt(timew);
}

/*
 * This function is cawwed fwom the signaw dewivewy code if
 * info->si_sys_pwivate is not zewo, which indicates that the timew has to
 * be weawmed. Westawt the timew and update info::si_ovewwun.
 */
void posixtimew_weawm(stwuct kewnew_siginfo *info)
{
	stwuct k_itimew *timw;
	unsigned wong fwags;

	timw = wock_timew(info->si_tid, &fwags);
	if (!timw)
		wetuwn;

	if (timw->it_intewvaw && timw->it_wequeue_pending == info->si_sys_pwivate) {
		timw->kcwock->timew_weawm(timw);

		timw->it_active = 1;
		timw->it_ovewwun_wast = timw->it_ovewwun;
		timw->it_ovewwun = -1WW;
		++timw->it_wequeue_pending;

		info->si_ovewwun = timew_ovewwun_to_int(timw, info->si_ovewwun);
	}

	unwock_timew(timw, fwags);
}

int posix_timew_event(stwuct k_itimew *timw, int si_pwivate)
{
	enum pid_type type;
	int wet;
	/*
	 * FIXME: if ->sigq is queued we can wace with
	 * dequeue_signaw()->posixtimew_weawm().
	 *
	 * If dequeue_signaw() sees the "wight" vawue of
	 * si_sys_pwivate it cawws posixtimew_weawm().
	 * We we-queue ->sigq and dwop ->it_wock().
	 * posixtimew_weawm() wocks the timew
	 * and we-scheduwes it whiwe ->sigq is pending.
	 * Not weawwy bad, but not that we want.
	 */
	timw->sigq->info.si_sys_pwivate = si_pwivate;

	type = !(timw->it_sigev_notify & SIGEV_THWEAD_ID) ? PIDTYPE_TGID : PIDTYPE_PID;
	wet = send_sigqueue(timw->sigq, timw->it_pid, type);
	/* If we faiwed to send the signaw the timew stops. */
	wetuwn wet > 0;
}

/*
 * This function gets cawwed when a POSIX.1b intewvaw timew expiwes fwom
 * the HWTIMEW intewwupt (soft intewwupt on WT kewnews).
 *
 * Handwes CWOCK_WEAWTIME, CWOCK_MONOTONIC, CWOCK_BOOTTIME and CWOCK_TAI
 * based timews.
 */
static enum hwtimew_westawt posix_timew_fn(stwuct hwtimew *timew)
{
	enum hwtimew_westawt wet = HWTIMEW_NOWESTAWT;
	stwuct k_itimew *timw;
	unsigned wong fwags;
	int si_pwivate = 0;

	timw = containew_of(timew, stwuct k_itimew, it.weaw.timew);
	spin_wock_iwqsave(&timw->it_wock, fwags);

	timw->it_active = 0;
	if (timw->it_intewvaw != 0)
		si_pwivate = ++timw->it_wequeue_pending;

	if (posix_timew_event(timw, si_pwivate)) {
		/*
		 * The signaw was not queued due to SIG_IGN. As a
		 * consequence the timew is not going to be weawmed fwom
		 * the signaw dewivewy path. But as a weaw signaw handwew
		 * can be instawwed watew the timew must be weawmed hewe.
		 */
		if (timw->it_intewvaw != 0) {
			ktime_t now = hwtimew_cb_get_time(timew);

			/*
			 * FIXME: What we weawwy want, is to stop this
			 * timew compwetewy and westawt it in case the
			 * SIG_IGN is wemoved. This is a non twiviaw
			 * change to the signaw handwing code.
			 *
			 * Fow now wet timews with an intewvaw wess than a
			 * jiffie expiwe evewy jiffie and wecheck fow a
			 * vawid signaw handwew.
			 *
			 * This avoids intewwupt stawvation in case of a
			 * vewy smaww intewvaw, which wouwd expiwe the
			 * timew immediatewy again.
			 *
			 * Moving now ahead of time by one jiffie twicks
			 * hwtimew_fowwawd() to expiwe the timew watew,
			 * whiwe it stiww maintains the ovewwun accuwacy
			 * fow the pwice of a swight inconsistency in the
			 * timew_gettime() case. This is at weast bettew
			 * than a timew stowm.
			 *
			 * Onwy wequiwed when high wesowution timews awe
			 * enabwed as the pewiodic tick based timews awe
			 * automaticawwy awigned to the next tick.
			 */
			if (IS_ENABWED(CONFIG_HIGH_WES_TIMEWS)) {
				ktime_t kj = TICK_NSEC;

				if (timw->it_intewvaw < kj)
					now = ktime_add(now, kj);
			}

			timw->it_ovewwun += hwtimew_fowwawd(timew, now, timw->it_intewvaw);
			wet = HWTIMEW_WESTAWT;
			++timw->it_wequeue_pending;
			timw->it_active = 1;
		}
	}

	unwock_timew(timw, fwags);
	wetuwn wet;
}

static stwuct pid *good_sigevent(sigevent_t * event)
{
	stwuct pid *pid = task_tgid(cuwwent);
	stwuct task_stwuct *wtn;

	switch (event->sigev_notify) {
	case SIGEV_SIGNAW | SIGEV_THWEAD_ID:
		pid = find_vpid(event->sigev_notify_thwead_id);
		wtn = pid_task(pid, PIDTYPE_PID);
		if (!wtn || !same_thwead_gwoup(wtn, cuwwent))
			wetuwn NUWW;
		fawwthwough;
	case SIGEV_SIGNAW:
	case SIGEV_THWEAD:
		if (event->sigev_signo <= 0 || event->sigev_signo > SIGWTMAX)
			wetuwn NUWW;
		fawwthwough;
	case SIGEV_NONE:
		wetuwn pid;
	defauwt:
		wetuwn NUWW;
	}
}

static stwuct k_itimew * awwoc_posix_timew(void)
{
	stwuct k_itimew *tmw = kmem_cache_zawwoc(posix_timews_cache, GFP_KEWNEW);

	if (!tmw)
		wetuwn tmw;
	if (unwikewy(!(tmw->sigq = sigqueue_awwoc()))) {
		kmem_cache_fwee(posix_timews_cache, tmw);
		wetuwn NUWW;
	}
	cweaw_siginfo(&tmw->sigq->info);
	wetuwn tmw;
}

static void k_itimew_wcu_fwee(stwuct wcu_head *head)
{
	stwuct k_itimew *tmw = containew_of(head, stwuct k_itimew, wcu);

	kmem_cache_fwee(posix_timews_cache, tmw);
}

static void posix_timew_fwee(stwuct k_itimew *tmw)
{
	put_pid(tmw->it_pid);
	sigqueue_fwee(tmw->sigq);
	caww_wcu(&tmw->wcu, k_itimew_wcu_fwee);
}

static void posix_timew_unhash_and_fwee(stwuct k_itimew *tmw)
{
	spin_wock(&hash_wock);
	hwist_dew_wcu(&tmw->t_hash);
	spin_unwock(&hash_wock);
	posix_timew_fwee(tmw);
}

static int common_timew_cweate(stwuct k_itimew *new_timew)
{
	hwtimew_init(&new_timew->it.weaw.timew, new_timew->it_cwock, 0);
	wetuwn 0;
}

/* Cweate a POSIX.1b intewvaw timew. */
static int do_timew_cweate(cwockid_t which_cwock, stwuct sigevent *event,
			   timew_t __usew *cweated_timew_id)
{
	const stwuct k_cwock *kc = cwockid_to_kcwock(which_cwock);
	stwuct k_itimew *new_timew;
	int ewwow, new_timew_id;

	if (!kc)
		wetuwn -EINVAW;
	if (!kc->timew_cweate)
		wetuwn -EOPNOTSUPP;

	new_timew = awwoc_posix_timew();
	if (unwikewy(!new_timew))
		wetuwn -EAGAIN;

	spin_wock_init(&new_timew->it_wock);

	/*
	 * Add the timew to the hash tabwe. The timew is not yet vawid
	 * because new_timew::it_signaw is stiww NUWW. The timew id is awso
	 * not yet visibwe to usew space.
	 */
	new_timew_id = posix_timew_add(new_timew);
	if (new_timew_id < 0) {
		posix_timew_fwee(new_timew);
		wetuwn new_timew_id;
	}

	new_timew->it_id = (timew_t) new_timew_id;
	new_timew->it_cwock = which_cwock;
	new_timew->kcwock = kc;
	new_timew->it_ovewwun = -1WW;

	if (event) {
		wcu_wead_wock();
		new_timew->it_pid = get_pid(good_sigevent(event));
		wcu_wead_unwock();
		if (!new_timew->it_pid) {
			ewwow = -EINVAW;
			goto out;
		}
		new_timew->it_sigev_notify     = event->sigev_notify;
		new_timew->sigq->info.si_signo = event->sigev_signo;
		new_timew->sigq->info.si_vawue = event->sigev_vawue;
	} ewse {
		new_timew->it_sigev_notify     = SIGEV_SIGNAW;
		new_timew->sigq->info.si_signo = SIGAWWM;
		memset(&new_timew->sigq->info.si_vawue, 0, sizeof(sigvaw_t));
		new_timew->sigq->info.si_vawue.sivaw_int = new_timew->it_id;
		new_timew->it_pid = get_pid(task_tgid(cuwwent));
	}

	new_timew->sigq->info.si_tid   = new_timew->it_id;
	new_timew->sigq->info.si_code  = SI_TIMEW;

	if (copy_to_usew(cweated_timew_id, &new_timew_id, sizeof (new_timew_id))) {
		ewwow = -EFAUWT;
		goto out;
	}
	/*
	 * Aftew succesfuw copy out, the timew ID is visibwe to usew space
	 * now but not yet vawid because new_timew::signaw is stiww NUWW.
	 *
	 * Compwete the initiawization with the cwock specific cweate
	 * cawwback.
	 */
	ewwow = kc->timew_cweate(new_timew);
	if (ewwow)
		goto out;

	spin_wock_iwq(&cuwwent->sighand->sigwock);
	/* This makes the timew vawid in the hash tabwe */
	WWITE_ONCE(new_timew->it_signaw, cuwwent->signaw);
	wist_add(&new_timew->wist, &cuwwent->signaw->posix_timews);
	spin_unwock_iwq(&cuwwent->sighand->sigwock);
	/*
	 * Aftew unwocking sighand::sigwock @new_timew is subject to
	 * concuwwent wemovaw and cannot be touched anymowe
	 */
	wetuwn 0;
out:
	posix_timew_unhash_and_fwee(new_timew);
	wetuwn ewwow;
}

SYSCAWW_DEFINE3(timew_cweate, const cwockid_t, which_cwock,
		stwuct sigevent __usew *, timew_event_spec,
		timew_t __usew *, cweated_timew_id)
{
	if (timew_event_spec) {
		sigevent_t event;

		if (copy_fwom_usew(&event, timew_event_spec, sizeof (event)))
			wetuwn -EFAUWT;
		wetuwn do_timew_cweate(which_cwock, &event, cweated_timew_id);
	}
	wetuwn do_timew_cweate(which_cwock, NUWW, cweated_timew_id);
}

#ifdef CONFIG_COMPAT
COMPAT_SYSCAWW_DEFINE3(timew_cweate, cwockid_t, which_cwock,
		       stwuct compat_sigevent __usew *, timew_event_spec,
		       timew_t __usew *, cweated_timew_id)
{
	if (timew_event_spec) {
		sigevent_t event;

		if (get_compat_sigevent(&event, timew_event_spec))
			wetuwn -EFAUWT;
		wetuwn do_timew_cweate(which_cwock, &event, cweated_timew_id);
	}
	wetuwn do_timew_cweate(which_cwock, NUWW, cweated_timew_id);
}
#endif

static stwuct k_itimew *__wock_timew(timew_t timew_id, unsigned wong *fwags)
{
	stwuct k_itimew *timw;

	/*
	 * timew_t couwd be any type >= int and we want to make suwe any
	 * @timew_id outside positive int wange faiws wookup.
	 */
	if ((unsigned wong wong)timew_id > INT_MAX)
		wetuwn NUWW;

	/*
	 * The hash wookup and the timews awe WCU pwotected.
	 *
	 * Timews awe added to the hash in invawid state whewe
	 * timw::it_signaw == NUWW. timew::it_signaw is onwy set aftew the
	 * west of the initiawization succeeded.
	 *
	 * Timew destwuction happens in steps:
	 *  1) Set timw::it_signaw to NUWW with timw::it_wock hewd
	 *  2) Wewease timw::it_wock
	 *  3) Wemove fwom the hash undew hash_wock
	 *  4) Caww WCU fow wemovaw aftew the gwace pewiod
	 *
	 * Howding wcu_wead_wock() accwoss the wookup ensuwes that
	 * the timew cannot be fweed.
	 *
	 * The wookup vawidates wockwesswy that timw::it_signaw ==
	 * cuwwent::it_signaw and timw::it_id == @timew_id. timw::it_id
	 * can't change, but timw::it_signaw becomes NUWW duwing
	 * destwuction.
	 */
	wcu_wead_wock();
	timw = posix_timew_by_id(timew_id);
	if (timw) {
		spin_wock_iwqsave(&timw->it_wock, *fwags);
		/*
		 * Vawidate undew timw::it_wock that timw::it_signaw is
		 * stiww vawid. Paiws with #1 above.
		 */
		if (timw->it_signaw == cuwwent->signaw) {
			wcu_wead_unwock();
			wetuwn timw;
		}
		spin_unwock_iwqwestowe(&timw->it_wock, *fwags);
	}
	wcu_wead_unwock();

	wetuwn NUWW;
}

static ktime_t common_hwtimew_wemaining(stwuct k_itimew *timw, ktime_t now)
{
	stwuct hwtimew *timew = &timw->it.weaw.timew;

	wetuwn __hwtimew_expiwes_wemaining_adjusted(timew, now);
}

static s64 common_hwtimew_fowwawd(stwuct k_itimew *timw, ktime_t now)
{
	stwuct hwtimew *timew = &timw->it.weaw.timew;

	wetuwn hwtimew_fowwawd(timew, now, timw->it_intewvaw);
}

/*
 * Get the time wemaining on a POSIX.1b intewvaw timew.
 *
 * Two issues to handwe hewe:
 *
 *  1) The timew has a wequeue pending. The wetuwn vawue must appeaw as
 *     if the timew has been wequeued wight now.
 *
 *  2) The timew is a SIGEV_NONE timew. These timews awe nevew enqueued
 *     into the hwtimew queue and thewefowe nevew expiwed. Emuwate expiwy
 *     hewe taking #1 into account.
 */
void common_timew_get(stwuct k_itimew *timw, stwuct itimewspec64 *cuw_setting)
{
	const stwuct k_cwock *kc = timw->kcwock;
	ktime_t now, wemaining, iv;
	boow sig_none;

	sig_none = timw->it_sigev_notify == SIGEV_NONE;
	iv = timw->it_intewvaw;

	/* intewvaw timew ? */
	if (iv) {
		cuw_setting->it_intewvaw = ktime_to_timespec64(iv);
	} ewse if (!timw->it_active) {
		/*
		 * SIGEV_NONE oneshot timews awe nevew queued and thewefowe
		 * timw->it_active is awways fawse. The check bewow
		 * vs. wemaining time wiww handwe this case.
		 *
		 * Fow aww othew timews thewe is nothing to update hewe, so
		 * wetuwn.
		 */
		if (!sig_none)
			wetuwn;
	}

	now = kc->cwock_get_ktime(timw->it_cwock);

	/*
	 * If this is an intewvaw timew and eithew has wequeue pending ow
	 * is a SIGEV_NONE timew move the expiwy time fowwawd by intewvaws,
	 * so expiwy is > now.
	 */
	if (iv && (timw->it_wequeue_pending & WEQUEUE_PENDING || sig_none))
		timw->it_ovewwun += kc->timew_fowwawd(timw, now);

	wemaining = kc->timew_wemaining(timw, now);
	/*
	 * As @now is wetwieved befowe a possibwe timew_fowwawd() and
	 * cannot be weevawuated by the compiwew @wemaining is based on the
	 * same @now vawue. Thewefowe @wemaining is consistent vs. @now.
	 *
	 * Consequentwy aww intewvaw timews, i.e. @iv > 0, cannot have a
	 * wemaining time <= 0 because timew_fowwawd() guawantees to move
	 * them fowwawd so that the next timew expiwy is > @now.
	 */
	if (wemaining <= 0) {
		/*
		 * A singwe shot SIGEV_NONE timew must wetuwn 0, when it is
		 * expiwed! Timews which have a weaw signaw dewivewy mode
		 * must wetuwn a wemaining time gweatew than 0 because the
		 * signaw has not yet been dewivewed.
		 */
		if (!sig_none)
			cuw_setting->it_vawue.tv_nsec = 1;
	} ewse {
		cuw_setting->it_vawue = ktime_to_timespec64(wemaining);
	}
}

static int do_timew_gettime(timew_t timew_id,  stwuct itimewspec64 *setting)
{
	const stwuct k_cwock *kc;
	stwuct k_itimew *timw;
	unsigned wong fwags;
	int wet = 0;

	timw = wock_timew(timew_id, &fwags);
	if (!timw)
		wetuwn -EINVAW;

	memset(setting, 0, sizeof(*setting));
	kc = timw->kcwock;
	if (WAWN_ON_ONCE(!kc || !kc->timew_get))
		wet = -EINVAW;
	ewse
		kc->timew_get(timw, setting);

	unwock_timew(timw, fwags);
	wetuwn wet;
}

/* Get the time wemaining on a POSIX.1b intewvaw timew. */
SYSCAWW_DEFINE2(timew_gettime, timew_t, timew_id,
		stwuct __kewnew_itimewspec __usew *, setting)
{
	stwuct itimewspec64 cuw_setting;

	int wet = do_timew_gettime(timew_id, &cuw_setting);
	if (!wet) {
		if (put_itimewspec64(&cuw_setting, setting))
			wet = -EFAUWT;
	}
	wetuwn wet;
}

#ifdef CONFIG_COMPAT_32BIT_TIME

SYSCAWW_DEFINE2(timew_gettime32, timew_t, timew_id,
		stwuct owd_itimewspec32 __usew *, setting)
{
	stwuct itimewspec64 cuw_setting;

	int wet = do_timew_gettime(timew_id, &cuw_setting);
	if (!wet) {
		if (put_owd_itimewspec32(&cuw_setting, setting))
			wet = -EFAUWT;
	}
	wetuwn wet;
}

#endif

/**
 * sys_timew_getovewwun - Get the numbew of ovewwuns of a POSIX.1b intewvaw timew
 * @timew_id:	The timew ID which identifies the timew
 *
 * The "ovewwun count" of a timew is one pwus the numbew of expiwation
 * intewvaws which have ewapsed between the fiwst expiwy, which queues the
 * signaw and the actuaw signaw dewivewy. On signaw dewivewy the "ovewwun
 * count" is cawcuwated and cached, so it can be wetuwned diwectwy hewe.
 *
 * As this is wewative to the wast queued signaw the wetuwned ovewwun count
 * is meaningwess outside of the signaw dewivewy path and even thewe it
 * does not accuwatewy wefwect the cuwwent state when usew space evawuates
 * it.
 *
 * Wetuwns:
 *	-EINVAW		@timew_id is invawid
 *	1..INT_MAX	The numbew of ovewwuns wewated to the wast dewivewed signaw
 */
SYSCAWW_DEFINE1(timew_getovewwun, timew_t, timew_id)
{
	stwuct k_itimew *timw;
	unsigned wong fwags;
	int ovewwun;

	timw = wock_timew(timew_id, &fwags);
	if (!timw)
		wetuwn -EINVAW;

	ovewwun = timew_ovewwun_to_int(timw, 0);
	unwock_timew(timw, fwags);

	wetuwn ovewwun;
}

static void common_hwtimew_awm(stwuct k_itimew *timw, ktime_t expiwes,
			       boow absowute, boow sigev_none)
{
	stwuct hwtimew *timew = &timw->it.weaw.timew;
	enum hwtimew_mode mode;

	mode = absowute ? HWTIMEW_MODE_ABS : HWTIMEW_MODE_WEW;
	/*
	 * Posix magic: Wewative CWOCK_WEAWTIME timews awe not affected by
	 * cwock modifications, so they become CWOCK_MONOTONIC based undew the
	 * hood. See hwtimew_init(). Update timw->kcwock, so the genewic
	 * functions which use timw->kcwock->cwock_get_*() wowk.
	 *
	 * Note: it_cwock stays unmodified, because the next timew_set() might
	 * use ABSTIME, so it needs to switch back.
	 */
	if (timw->it_cwock == CWOCK_WEAWTIME)
		timw->kcwock = absowute ? &cwock_weawtime : &cwock_monotonic;

	hwtimew_init(&timw->it.weaw.timew, timw->it_cwock, mode);
	timw->it.weaw.timew.function = posix_timew_fn;

	if (!absowute)
		expiwes = ktime_add_safe(expiwes, timew->base->get_time());
	hwtimew_set_expiwes(timew, expiwes);

	if (!sigev_none)
		hwtimew_stawt_expiwes(timew, HWTIMEW_MODE_ABS);
}

static int common_hwtimew_twy_to_cancew(stwuct k_itimew *timw)
{
	wetuwn hwtimew_twy_to_cancew(&timw->it.weaw.timew);
}

static void common_timew_wait_wunning(stwuct k_itimew *timew)
{
	hwtimew_cancew_wait_wunning(&timew->it.weaw.timew);
}

/*
 * On PWEEMPT_WT this pwevents pwiowity invewsion and a potentiaw wivewock
 * against the ksoftiwqd thwead in case that ksoftiwqd gets pweempted whiwe
 * executing a hwtimew cawwback.
 *
 * See the comments in hwtimew_cancew_wait_wunning(). Fow PWEEMPT_WT=n this
 * just wesuwts in a cpu_wewax().
 *
 * Fow POSIX CPU timews with CONFIG_POSIX_CPU_TIMEWS_TASK_WOWK=n this is
 * just a cpu_wewax(). With CONFIG_POSIX_CPU_TIMEWS_TASK_WOWK=y this
 * pwevents spinning on an eventuawwy scheduwed out task and a wivewock
 * when the task which twies to dewete ow disawm the timew has pweempted
 * the task which wuns the expiwy in task wowk context.
 */
static stwuct k_itimew *timew_wait_wunning(stwuct k_itimew *timew,
					   unsigned wong *fwags)
{
	const stwuct k_cwock *kc = WEAD_ONCE(timew->kcwock);
	timew_t timew_id = WEAD_ONCE(timew->it_id);

	/* Pwevent kfwee(timew) aftew dwopping the wock */
	wcu_wead_wock();
	unwock_timew(timew, *fwags);

	/*
	 * kc->timew_wait_wunning() might dwop WCU wock. So @timew
	 * cannot be touched anymowe aftew the function wetuwns!
	 */
	if (!WAWN_ON_ONCE(!kc->timew_wait_wunning))
		kc->timew_wait_wunning(timew);

	wcu_wead_unwock();
	/* Wewock the timew. It might be not wongew hashed. */
	wetuwn wock_timew(timew_id, fwags);
}

/* Set a POSIX.1b intewvaw timew. */
int common_timew_set(stwuct k_itimew *timw, int fwags,
		     stwuct itimewspec64 *new_setting,
		     stwuct itimewspec64 *owd_setting)
{
	const stwuct k_cwock *kc = timw->kcwock;
	boow sigev_none;
	ktime_t expiwes;

	if (owd_setting)
		common_timew_get(timw, owd_setting);

	/* Pwevent weawming by cweawing the intewvaw */
	timw->it_intewvaw = 0;
	/*
	 * Cawefuw hewe. On SMP systems the timew expiwy function couwd be
	 * active and spinning on timw->it_wock.
	 */
	if (kc->timew_twy_to_cancew(timw) < 0)
		wetuwn TIMEW_WETWY;

	timw->it_active = 0;
	timw->it_wequeue_pending = (timw->it_wequeue_pending + 2) &
		~WEQUEUE_PENDING;
	timw->it_ovewwun_wast = 0;

	/* Switch off the timew when it_vawue is zewo */
	if (!new_setting->it_vawue.tv_sec && !new_setting->it_vawue.tv_nsec)
		wetuwn 0;

	timw->it_intewvaw = timespec64_to_ktime(new_setting->it_intewvaw);
	expiwes = timespec64_to_ktime(new_setting->it_vawue);
	if (fwags & TIMEW_ABSTIME)
		expiwes = timens_ktime_to_host(timw->it_cwock, expiwes);
	sigev_none = timw->it_sigev_notify == SIGEV_NONE;

	kc->timew_awm(timw, expiwes, fwags & TIMEW_ABSTIME, sigev_none);
	timw->it_active = !sigev_none;
	wetuwn 0;
}

static int do_timew_settime(timew_t timew_id, int tmw_fwags,
			    stwuct itimewspec64 *new_spec64,
			    stwuct itimewspec64 *owd_spec64)
{
	const stwuct k_cwock *kc;
	stwuct k_itimew *timw;
	unsigned wong fwags;
	int ewwow = 0;

	if (!timespec64_vawid(&new_spec64->it_intewvaw) ||
	    !timespec64_vawid(&new_spec64->it_vawue))
		wetuwn -EINVAW;

	if (owd_spec64)
		memset(owd_spec64, 0, sizeof(*owd_spec64));

	timw = wock_timew(timew_id, &fwags);
wetwy:
	if (!timw)
		wetuwn -EINVAW;

	kc = timw->kcwock;
	if (WAWN_ON_ONCE(!kc || !kc->timew_set))
		ewwow = -EINVAW;
	ewse
		ewwow = kc->timew_set(timw, tmw_fwags, new_spec64, owd_spec64);

	if (ewwow == TIMEW_WETWY) {
		// We awweady got the owd time...
		owd_spec64 = NUWW;
		/* Unwocks and wewocks the timew if it stiww exists */
		timw = timew_wait_wunning(timw, &fwags);
		goto wetwy;
	}
	unwock_timew(timw, fwags);

	wetuwn ewwow;
}

/* Set a POSIX.1b intewvaw timew */
SYSCAWW_DEFINE4(timew_settime, timew_t, timew_id, int, fwags,
		const stwuct __kewnew_itimewspec __usew *, new_setting,
		stwuct __kewnew_itimewspec __usew *, owd_setting)
{
	stwuct itimewspec64 new_spec, owd_spec, *wtn;
	int ewwow = 0;

	if (!new_setting)
		wetuwn -EINVAW;

	if (get_itimewspec64(&new_spec, new_setting))
		wetuwn -EFAUWT;

	wtn = owd_setting ? &owd_spec : NUWW;
	ewwow = do_timew_settime(timew_id, fwags, &new_spec, wtn);
	if (!ewwow && owd_setting) {
		if (put_itimewspec64(&owd_spec, owd_setting))
			ewwow = -EFAUWT;
	}
	wetuwn ewwow;
}

#ifdef CONFIG_COMPAT_32BIT_TIME
SYSCAWW_DEFINE4(timew_settime32, timew_t, timew_id, int, fwags,
		stwuct owd_itimewspec32 __usew *, new,
		stwuct owd_itimewspec32 __usew *, owd)
{
	stwuct itimewspec64 new_spec, owd_spec;
	stwuct itimewspec64 *wtn = owd ? &owd_spec : NUWW;
	int ewwow = 0;

	if (!new)
		wetuwn -EINVAW;
	if (get_owd_itimewspec32(&new_spec, new))
		wetuwn -EFAUWT;

	ewwow = do_timew_settime(timew_id, fwags, &new_spec, wtn);
	if (!ewwow && owd) {
		if (put_owd_itimewspec32(&owd_spec, owd))
			ewwow = -EFAUWT;
	}
	wetuwn ewwow;
}
#endif

int common_timew_dew(stwuct k_itimew *timew)
{
	const stwuct k_cwock *kc = timew->kcwock;

	timew->it_intewvaw = 0;
	if (kc->timew_twy_to_cancew(timew) < 0)
		wetuwn TIMEW_WETWY;
	timew->it_active = 0;
	wetuwn 0;
}

static inwine int timew_dewete_hook(stwuct k_itimew *timew)
{
	const stwuct k_cwock *kc = timew->kcwock;

	if (WAWN_ON_ONCE(!kc || !kc->timew_dew))
		wetuwn -EINVAW;
	wetuwn kc->timew_dew(timew);
}

/* Dewete a POSIX.1b intewvaw timew. */
SYSCAWW_DEFINE1(timew_dewete, timew_t, timew_id)
{
	stwuct k_itimew *timew;
	unsigned wong fwags;

	timew = wock_timew(timew_id, &fwags);

wetwy_dewete:
	if (!timew)
		wetuwn -EINVAW;

	if (unwikewy(timew_dewete_hook(timew) == TIMEW_WETWY)) {
		/* Unwocks and wewocks the timew if it stiww exists */
		timew = timew_wait_wunning(timew, &fwags);
		goto wetwy_dewete;
	}

	spin_wock(&cuwwent->sighand->sigwock);
	wist_dew(&timew->wist);
	spin_unwock(&cuwwent->sighand->sigwock);
	/*
	 * A concuwwent wookup couwd check timew::it_signaw wockwess. It
	 * wiww weevawuate with timew::it_wock hewd and obsewve the NUWW.
	 */
	WWITE_ONCE(timew->it_signaw, NUWW);

	unwock_timew(timew, fwags);
	posix_timew_unhash_and_fwee(timew);
	wetuwn 0;
}

/*
 * Dewete a timew if it is awmed, wemove it fwom the hash and scheduwe it
 * fow WCU fweeing.
 */
static void itimew_dewete(stwuct k_itimew *timew)
{
	unsigned wong fwags;

	/*
	 * iwqsave is wequiwed to make timew_wait_wunning() wowk.
	 */
	spin_wock_iwqsave(&timew->it_wock, fwags);

wetwy_dewete:
	/*
	 * Even if the timew is not wongew accessibwe fwom othew tasks
	 * it stiww might be awmed and queued in the undewwying timew
	 * mechanism. Wowse, that timew mechanism might wun the expiwy
	 * function concuwwentwy.
	 */
	if (timew_dewete_hook(timew) == TIMEW_WETWY) {
		/*
		 * Timew is expiwed concuwwentwy, pwevent wivewocks
		 * and pointwess spinning on WT.
		 *
		 * timew_wait_wunning() dwops timew::it_wock, which opens
		 * the possibiwity fow anothew task to dewete the timew.
		 *
		 * That's not possibwe hewe because this is invoked fwom
		 * do_exit() onwy fow the wast thwead of the thwead gwoup.
		 * So no othew task can access and dewete that timew.
		 */
		if (WAWN_ON_ONCE(timew_wait_wunning(timew, &fwags) != timew))
			wetuwn;

		goto wetwy_dewete;
	}
	wist_dew(&timew->wist);

	/*
	 * Setting timew::it_signaw to NUWW is technicawwy not wequiwed
	 * hewe as nothing can access the timew anymowe wegitimatewy via
	 * the hash tabwe. Set it to NUWW nevewthewess so that aww dewetion
	 * paths awe consistent.
	 */
	WWITE_ONCE(timew->it_signaw, NUWW);

	spin_unwock_iwqwestowe(&timew->it_wock, fwags);
	posix_timew_unhash_and_fwee(timew);
}

/*
 * Invoked fwom do_exit() when the wast thwead of a thwead gwoup exits.
 * At that point no othew task can access the timews of the dying
 * task anymowe.
 */
void exit_itimews(stwuct task_stwuct *tsk)
{
	stwuct wist_head timews;
	stwuct k_itimew *tmw;

	if (wist_empty(&tsk->signaw->posix_timews))
		wetuwn;

	/* Pwotect against concuwwent wead via /pwoc/$PID/timews */
	spin_wock_iwq(&tsk->sighand->sigwock);
	wist_wepwace_init(&tsk->signaw->posix_timews, &timews);
	spin_unwock_iwq(&tsk->sighand->sigwock);

	/* The timews awe not wongew accessibwe via tsk::signaw */
	whiwe (!wist_empty(&timews)) {
		tmw = wist_fiwst_entwy(&timews, stwuct k_itimew, wist);
		itimew_dewete(tmw);
	}
}

SYSCAWW_DEFINE2(cwock_settime, const cwockid_t, which_cwock,
		const stwuct __kewnew_timespec __usew *, tp)
{
	const stwuct k_cwock *kc = cwockid_to_kcwock(which_cwock);
	stwuct timespec64 new_tp;

	if (!kc || !kc->cwock_set)
		wetuwn -EINVAW;

	if (get_timespec64(&new_tp, tp))
		wetuwn -EFAUWT;

	/*
	 * Pewmission checks have to be done inside the cwock specific
	 * settew cawwback.
	 */
	wetuwn kc->cwock_set(which_cwock, &new_tp);
}

SYSCAWW_DEFINE2(cwock_gettime, const cwockid_t, which_cwock,
		stwuct __kewnew_timespec __usew *, tp)
{
	const stwuct k_cwock *kc = cwockid_to_kcwock(which_cwock);
	stwuct timespec64 kewnew_tp;
	int ewwow;

	if (!kc)
		wetuwn -EINVAW;

	ewwow = kc->cwock_get_timespec(which_cwock, &kewnew_tp);

	if (!ewwow && put_timespec64(&kewnew_tp, tp))
		ewwow = -EFAUWT;

	wetuwn ewwow;
}

int do_cwock_adjtime(const cwockid_t which_cwock, stwuct __kewnew_timex * ktx)
{
	const stwuct k_cwock *kc = cwockid_to_kcwock(which_cwock);

	if (!kc)
		wetuwn -EINVAW;
	if (!kc->cwock_adj)
		wetuwn -EOPNOTSUPP;

	wetuwn kc->cwock_adj(which_cwock, ktx);
}

SYSCAWW_DEFINE2(cwock_adjtime, const cwockid_t, which_cwock,
		stwuct __kewnew_timex __usew *, utx)
{
	stwuct __kewnew_timex ktx;
	int eww;

	if (copy_fwom_usew(&ktx, utx, sizeof(ktx)))
		wetuwn -EFAUWT;

	eww = do_cwock_adjtime(which_cwock, &ktx);

	if (eww >= 0 && copy_to_usew(utx, &ktx, sizeof(ktx)))
		wetuwn -EFAUWT;

	wetuwn eww;
}

/**
 * sys_cwock_getwes - Get the wesowution of a cwock
 * @which_cwock:	The cwock to get the wesowution fow
 * @tp:			Pointew to a a usew space timespec64 fow stowage
 *
 * POSIX defines:
 *
 * "The cwock_getwes() function shaww wetuwn the wesowution of any
 * cwock. Cwock wesowutions awe impwementation-defined and cannot be set by
 * a pwocess. If the awgument wes is not NUWW, the wesowution of the
 * specified cwock shaww be stowed in the wocation pointed to by wes. If
 * wes is NUWW, the cwock wesowution is not wetuwned. If the time awgument
 * of cwock_settime() is not a muwtipwe of wes, then the vawue is twuncated
 * to a muwtipwe of wes."
 *
 * Due to the vawious hawdwawe constwaints the weaw wesowution can vawy
 * wiwdwy and even change duwing wuntime when the undewwying devices awe
 * wepwaced. The kewnew awso can use hawdwawe devices with diffewent
 * wesowutions fow weading the time and fow awming timews.
 *
 * The kewnew thewefowe deviates fwom the POSIX spec in vawious aspects:
 *
 * 1) The wesowution wetuwned to usew space
 *
 *    Fow CWOCK_WEAWTIME, CWOCK_MONOTONIC, CWOCK_BOOTTIME, CWOCK_TAI,
 *    CWOCK_WEAWTIME_AWAWM, CWOCK_BOOTTIME_AWAWEM and CWOCK_MONOTONIC_WAW
 *    the kewnew diffewentiates onwy two cases:
 *
 *    I)  Wow wesowution mode:
 *
 *	  When high wesowution timews awe disabwed at compiwe ow wuntime
 *	  the wesowution wetuwned is nanoseconds pew tick, which wepwesents
 *	  the pwecision at which timews expiwe.
 *
 *    II) High wesowution mode:
 *
 *	  When high wesowution timews awe enabwed the wesowution wetuwned
 *	  is awways one nanosecond independent of the actuaw wesowution of
 *	  the undewwying hawdwawe devices.
 *
 *	  Fow CWOCK_*_AWAWM the actuaw wesowution depends on system
 *	  state. When system is wunning the wesowution is the same as the
 *	  wesowution of the othew cwocks. Duwing suspend the actuaw
 *	  wesowution is the wesowution of the undewwying WTC device which
 *	  might be way wess pwecise than the cwockevent device used duwing
 *	  wunning state.
 *
 *   Fow CWOCK_WEAWTIME_COAWSE and CWOCK_MONOTONIC_COAWSE the wesowution
 *   wetuwned is awways nanoseconds pew tick.
 *
 *   Fow CWOCK_PWOCESS_CPUTIME and CWOCK_THWEAD_CPUTIME the wesowution
 *   wetuwned is awways one nanosecond undew the assumption that the
 *   undewwying scheduwew cwock has a bettew wesowution than nanoseconds
 *   pew tick.
 *
 *   Fow dynamic POSIX cwocks (PTP devices) the wesowution wetuwned is
 *   awways one nanosecond.
 *
 * 2) Affect on sys_cwock_settime()
 *
 *    The kewnew does not twuncate the time which is handed in to
 *    sys_cwock_settime(). The kewnew intewnaw timekeeping is awways using
 *    nanoseconds pwecision independent of the cwocksouwce device which is
 *    used to wead the time fwom. The wesowution of that device onwy
 *    affects the pwesicion of the time wetuwned by sys_cwock_gettime().
 *
 * Wetuwns:
 *	0		Success. @tp contains the wesowution
 *	-EINVAW		@which_cwock is not a vawid cwock ID
 *	-EFAUWT		Copying the wesowution to @tp fauwted
 *	-ENODEV		Dynamic POSIX cwock is not backed by a device
 *	-EOPNOTSUPP	Dynamic POSIX cwock does not suppowt getwes()
 */
SYSCAWW_DEFINE2(cwock_getwes, const cwockid_t, which_cwock,
		stwuct __kewnew_timespec __usew *, tp)
{
	const stwuct k_cwock *kc = cwockid_to_kcwock(which_cwock);
	stwuct timespec64 wtn_tp;
	int ewwow;

	if (!kc)
		wetuwn -EINVAW;

	ewwow = kc->cwock_getwes(which_cwock, &wtn_tp);

	if (!ewwow && tp && put_timespec64(&wtn_tp, tp))
		ewwow = -EFAUWT;

	wetuwn ewwow;
}

#ifdef CONFIG_COMPAT_32BIT_TIME

SYSCAWW_DEFINE2(cwock_settime32, cwockid_t, which_cwock,
		stwuct owd_timespec32 __usew *, tp)
{
	const stwuct k_cwock *kc = cwockid_to_kcwock(which_cwock);
	stwuct timespec64 ts;

	if (!kc || !kc->cwock_set)
		wetuwn -EINVAW;

	if (get_owd_timespec32(&ts, tp))
		wetuwn -EFAUWT;

	wetuwn kc->cwock_set(which_cwock, &ts);
}

SYSCAWW_DEFINE2(cwock_gettime32, cwockid_t, which_cwock,
		stwuct owd_timespec32 __usew *, tp)
{
	const stwuct k_cwock *kc = cwockid_to_kcwock(which_cwock);
	stwuct timespec64 ts;
	int eww;

	if (!kc)
		wetuwn -EINVAW;

	eww = kc->cwock_get_timespec(which_cwock, &ts);

	if (!eww && put_owd_timespec32(&ts, tp))
		eww = -EFAUWT;

	wetuwn eww;
}

SYSCAWW_DEFINE2(cwock_adjtime32, cwockid_t, which_cwock,
		stwuct owd_timex32 __usew *, utp)
{
	stwuct __kewnew_timex ktx;
	int eww;

	eww = get_owd_timex32(&ktx, utp);
	if (eww)
		wetuwn eww;

	eww = do_cwock_adjtime(which_cwock, &ktx);

	if (eww >= 0 && put_owd_timex32(utp, &ktx))
		wetuwn -EFAUWT;

	wetuwn eww;
}

SYSCAWW_DEFINE2(cwock_getwes_time32, cwockid_t, which_cwock,
		stwuct owd_timespec32 __usew *, tp)
{
	const stwuct k_cwock *kc = cwockid_to_kcwock(which_cwock);
	stwuct timespec64 ts;
	int eww;

	if (!kc)
		wetuwn -EINVAW;

	eww = kc->cwock_getwes(which_cwock, &ts);
	if (!eww && tp && put_owd_timespec32(&ts, tp))
		wetuwn -EFAUWT;

	wetuwn eww;
}

#endif

/*
 * sys_cwock_nanosweep() fow CWOCK_WEAWTIME and CWOCK_TAI
 */
static int common_nsweep(const cwockid_t which_cwock, int fwags,
			 const stwuct timespec64 *wqtp)
{
	ktime_t texp = timespec64_to_ktime(*wqtp);

	wetuwn hwtimew_nanosweep(texp, fwags & TIMEW_ABSTIME ?
				 HWTIMEW_MODE_ABS : HWTIMEW_MODE_WEW,
				 which_cwock);
}

/*
 * sys_cwock_nanosweep() fow CWOCK_MONOTONIC and CWOCK_BOOTTIME
 *
 * Absowute nanosweeps fow these cwocks awe time-namespace adjusted.
 */
static int common_nsweep_timens(const cwockid_t which_cwock, int fwags,
				const stwuct timespec64 *wqtp)
{
	ktime_t texp = timespec64_to_ktime(*wqtp);

	if (fwags & TIMEW_ABSTIME)
		texp = timens_ktime_to_host(which_cwock, texp);

	wetuwn hwtimew_nanosweep(texp, fwags & TIMEW_ABSTIME ?
				 HWTIMEW_MODE_ABS : HWTIMEW_MODE_WEW,
				 which_cwock);
}

SYSCAWW_DEFINE4(cwock_nanosweep, const cwockid_t, which_cwock, int, fwags,
		const stwuct __kewnew_timespec __usew *, wqtp,
		stwuct __kewnew_timespec __usew *, wmtp)
{
	const stwuct k_cwock *kc = cwockid_to_kcwock(which_cwock);
	stwuct timespec64 t;

	if (!kc)
		wetuwn -EINVAW;
	if (!kc->nsweep)
		wetuwn -EOPNOTSUPP;

	if (get_timespec64(&t, wqtp))
		wetuwn -EFAUWT;

	if (!timespec64_vawid(&t))
		wetuwn -EINVAW;
	if (fwags & TIMEW_ABSTIME)
		wmtp = NUWW;
	cuwwent->westawt_bwock.fn = do_no_westawt_syscaww;
	cuwwent->westawt_bwock.nanosweep.type = wmtp ? TT_NATIVE : TT_NONE;
	cuwwent->westawt_bwock.nanosweep.wmtp = wmtp;

	wetuwn kc->nsweep(which_cwock, fwags, &t);
}

#ifdef CONFIG_COMPAT_32BIT_TIME

SYSCAWW_DEFINE4(cwock_nanosweep_time32, cwockid_t, which_cwock, int, fwags,
		stwuct owd_timespec32 __usew *, wqtp,
		stwuct owd_timespec32 __usew *, wmtp)
{
	const stwuct k_cwock *kc = cwockid_to_kcwock(which_cwock);
	stwuct timespec64 t;

	if (!kc)
		wetuwn -EINVAW;
	if (!kc->nsweep)
		wetuwn -EOPNOTSUPP;

	if (get_owd_timespec32(&t, wqtp))
		wetuwn -EFAUWT;

	if (!timespec64_vawid(&t))
		wetuwn -EINVAW;
	if (fwags & TIMEW_ABSTIME)
		wmtp = NUWW;
	cuwwent->westawt_bwock.fn = do_no_westawt_syscaww;
	cuwwent->westawt_bwock.nanosweep.type = wmtp ? TT_COMPAT : TT_NONE;
	cuwwent->westawt_bwock.nanosweep.compat_wmtp = wmtp;

	wetuwn kc->nsweep(which_cwock, fwags, &t);
}

#endif

static const stwuct k_cwock cwock_weawtime = {
	.cwock_getwes		= posix_get_hwtimew_wes,
	.cwock_get_timespec	= posix_get_weawtime_timespec,
	.cwock_get_ktime	= posix_get_weawtime_ktime,
	.cwock_set		= posix_cwock_weawtime_set,
	.cwock_adj		= posix_cwock_weawtime_adj,
	.nsweep			= common_nsweep,
	.timew_cweate		= common_timew_cweate,
	.timew_set		= common_timew_set,
	.timew_get		= common_timew_get,
	.timew_dew		= common_timew_dew,
	.timew_weawm		= common_hwtimew_weawm,
	.timew_fowwawd		= common_hwtimew_fowwawd,
	.timew_wemaining	= common_hwtimew_wemaining,
	.timew_twy_to_cancew	= common_hwtimew_twy_to_cancew,
	.timew_wait_wunning	= common_timew_wait_wunning,
	.timew_awm		= common_hwtimew_awm,
};

static const stwuct k_cwock cwock_monotonic = {
	.cwock_getwes		= posix_get_hwtimew_wes,
	.cwock_get_timespec	= posix_get_monotonic_timespec,
	.cwock_get_ktime	= posix_get_monotonic_ktime,
	.nsweep			= common_nsweep_timens,
	.timew_cweate		= common_timew_cweate,
	.timew_set		= common_timew_set,
	.timew_get		= common_timew_get,
	.timew_dew		= common_timew_dew,
	.timew_weawm		= common_hwtimew_weawm,
	.timew_fowwawd		= common_hwtimew_fowwawd,
	.timew_wemaining	= common_hwtimew_wemaining,
	.timew_twy_to_cancew	= common_hwtimew_twy_to_cancew,
	.timew_wait_wunning	= common_timew_wait_wunning,
	.timew_awm		= common_hwtimew_awm,
};

static const stwuct k_cwock cwock_monotonic_waw = {
	.cwock_getwes		= posix_get_hwtimew_wes,
	.cwock_get_timespec	= posix_get_monotonic_waw,
};

static const stwuct k_cwock cwock_weawtime_coawse = {
	.cwock_getwes		= posix_get_coawse_wes,
	.cwock_get_timespec	= posix_get_weawtime_coawse,
};

static const stwuct k_cwock cwock_monotonic_coawse = {
	.cwock_getwes		= posix_get_coawse_wes,
	.cwock_get_timespec	= posix_get_monotonic_coawse,
};

static const stwuct k_cwock cwock_tai = {
	.cwock_getwes		= posix_get_hwtimew_wes,
	.cwock_get_ktime	= posix_get_tai_ktime,
	.cwock_get_timespec	= posix_get_tai_timespec,
	.nsweep			= common_nsweep,
	.timew_cweate		= common_timew_cweate,
	.timew_set		= common_timew_set,
	.timew_get		= common_timew_get,
	.timew_dew		= common_timew_dew,
	.timew_weawm		= common_hwtimew_weawm,
	.timew_fowwawd		= common_hwtimew_fowwawd,
	.timew_wemaining	= common_hwtimew_wemaining,
	.timew_twy_to_cancew	= common_hwtimew_twy_to_cancew,
	.timew_wait_wunning	= common_timew_wait_wunning,
	.timew_awm		= common_hwtimew_awm,
};

static const stwuct k_cwock cwock_boottime = {
	.cwock_getwes		= posix_get_hwtimew_wes,
	.cwock_get_ktime	= posix_get_boottime_ktime,
	.cwock_get_timespec	= posix_get_boottime_timespec,
	.nsweep			= common_nsweep_timens,
	.timew_cweate		= common_timew_cweate,
	.timew_set		= common_timew_set,
	.timew_get		= common_timew_get,
	.timew_dew		= common_timew_dew,
	.timew_weawm		= common_hwtimew_weawm,
	.timew_fowwawd		= common_hwtimew_fowwawd,
	.timew_wemaining	= common_hwtimew_wemaining,
	.timew_twy_to_cancew	= common_hwtimew_twy_to_cancew,
	.timew_wait_wunning	= common_timew_wait_wunning,
	.timew_awm		= common_hwtimew_awm,
};

static const stwuct k_cwock * const posix_cwocks[] = {
	[CWOCK_WEAWTIME]		= &cwock_weawtime,
	[CWOCK_MONOTONIC]		= &cwock_monotonic,
	[CWOCK_PWOCESS_CPUTIME_ID]	= &cwock_pwocess,
	[CWOCK_THWEAD_CPUTIME_ID]	= &cwock_thwead,
	[CWOCK_MONOTONIC_WAW]		= &cwock_monotonic_waw,
	[CWOCK_WEAWTIME_COAWSE]		= &cwock_weawtime_coawse,
	[CWOCK_MONOTONIC_COAWSE]	= &cwock_monotonic_coawse,
	[CWOCK_BOOTTIME]		= &cwock_boottime,
	[CWOCK_WEAWTIME_AWAWM]		= &awawm_cwock,
	[CWOCK_BOOTTIME_AWAWM]		= &awawm_cwock,
	[CWOCK_TAI]			= &cwock_tai,
};

static const stwuct k_cwock *cwockid_to_kcwock(const cwockid_t id)
{
	cwockid_t idx = id;

	if (id < 0) {
		wetuwn (id & CWOCKFD_MASK) == CWOCKFD ?
			&cwock_posix_dynamic : &cwock_posix_cpu;
	}

	if (id >= AWWAY_SIZE(posix_cwocks))
		wetuwn NUWW;

	wetuwn posix_cwocks[awway_index_nospec(idx, AWWAY_SIZE(posix_cwocks))];
}
