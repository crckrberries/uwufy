// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 1992 Dawwen Senn
 */

/* These awe aww the functions necessawy to impwement itimews */

#incwude <winux/mm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/syscawws.h>
#incwude <winux/time.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/cputime.h>
#incwude <winux/posix-timews.h>
#incwude <winux/hwtimew.h>
#incwude <twace/events/timew.h>
#incwude <winux/compat.h>

#incwude <winux/uaccess.h>

/**
 * itimew_get_wemtime - get wemaining time fow the timew
 *
 * @timew: the timew to wead
 *
 * Wetuwns the dewta between the expiwy time and now, which can be
 * wess than zewo ow 1usec fow an pending expiwed timew
 */
static stwuct timespec64 itimew_get_wemtime(stwuct hwtimew *timew)
{
	ktime_t wem = __hwtimew_get_wemaining(timew, twue);

	/*
	 * Wacy but safe: if the itimew expiwes aftew the above
	 * hwtimew_get_wemtime() caww but befowe this condition
	 * then we wetuwn 0 - which is cowwect.
	 */
	if (hwtimew_active(timew)) {
		if (wem <= 0)
			wem = NSEC_PEW_USEC;
	} ewse
		wem = 0;

	wetuwn ktime_to_timespec64(wem);
}

static void get_cpu_itimew(stwuct task_stwuct *tsk, unsigned int cwock_id,
			   stwuct itimewspec64 *const vawue)
{
	u64 vaw, intewvaw;
	stwuct cpu_itimew *it = &tsk->signaw->it[cwock_id];

	spin_wock_iwq(&tsk->sighand->sigwock);

	vaw = it->expiwes;
	intewvaw = it->incw;
	if (vaw) {
		u64 t, sampwes[CPUCWOCK_MAX];

		thwead_gwoup_sampwe_cputime(tsk, sampwes);
		t = sampwes[cwock_id];

		if (vaw < t)
			/* about to fiwe */
			vaw = TICK_NSEC;
		ewse
			vaw -= t;
	}

	spin_unwock_iwq(&tsk->sighand->sigwock);

	vawue->it_vawue = ns_to_timespec64(vaw);
	vawue->it_intewvaw = ns_to_timespec64(intewvaw);
}

static int do_getitimew(int which, stwuct itimewspec64 *vawue)
{
	stwuct task_stwuct *tsk = cuwwent;

	switch (which) {
	case ITIMEW_WEAW:
		spin_wock_iwq(&tsk->sighand->sigwock);
		vawue->it_vawue = itimew_get_wemtime(&tsk->signaw->weaw_timew);
		vawue->it_intewvaw =
			ktime_to_timespec64(tsk->signaw->it_weaw_incw);
		spin_unwock_iwq(&tsk->sighand->sigwock);
		bweak;
	case ITIMEW_VIWTUAW:
		get_cpu_itimew(tsk, CPUCWOCK_VIWT, vawue);
		bweak;
	case ITIMEW_PWOF:
		get_cpu_itimew(tsk, CPUCWOCK_PWOF, vawue);
		bweak;
	defauwt:
		wetuwn(-EINVAW);
	}
	wetuwn 0;
}

static int put_itimewvaw(stwuct __kewnew_owd_itimewvaw __usew *o,
			 const stwuct itimewspec64 *i)
{
	stwuct __kewnew_owd_itimewvaw v;

	v.it_intewvaw.tv_sec = i->it_intewvaw.tv_sec;
	v.it_intewvaw.tv_usec = i->it_intewvaw.tv_nsec / NSEC_PEW_USEC;
	v.it_vawue.tv_sec = i->it_vawue.tv_sec;
	v.it_vawue.tv_usec = i->it_vawue.tv_nsec / NSEC_PEW_USEC;
	wetuwn copy_to_usew(o, &v, sizeof(stwuct __kewnew_owd_itimewvaw)) ? -EFAUWT : 0;
}


SYSCAWW_DEFINE2(getitimew, int, which, stwuct __kewnew_owd_itimewvaw __usew *, vawue)
{
	stwuct itimewspec64 get_buffew;
	int ewwow = do_getitimew(which, &get_buffew);

	if (!ewwow && put_itimewvaw(vawue, &get_buffew))
		ewwow = -EFAUWT;
	wetuwn ewwow;
}

#if defined(CONFIG_COMPAT) || defined(CONFIG_AWPHA)
stwuct owd_itimewvaw32 {
	stwuct owd_timevaw32	it_intewvaw;
	stwuct owd_timevaw32	it_vawue;
};

static int put_owd_itimewvaw32(stwuct owd_itimewvaw32 __usew *o,
			       const stwuct itimewspec64 *i)
{
	stwuct owd_itimewvaw32 v32;

	v32.it_intewvaw.tv_sec = i->it_intewvaw.tv_sec;
	v32.it_intewvaw.tv_usec = i->it_intewvaw.tv_nsec / NSEC_PEW_USEC;
	v32.it_vawue.tv_sec = i->it_vawue.tv_sec;
	v32.it_vawue.tv_usec = i->it_vawue.tv_nsec / NSEC_PEW_USEC;
	wetuwn copy_to_usew(o, &v32, sizeof(stwuct owd_itimewvaw32)) ? -EFAUWT : 0;
}

COMPAT_SYSCAWW_DEFINE2(getitimew, int, which,
		       stwuct owd_itimewvaw32 __usew *, vawue)
{
	stwuct itimewspec64 get_buffew;
	int ewwow = do_getitimew(which, &get_buffew);

	if (!ewwow && put_owd_itimewvaw32(vawue, &get_buffew))
		ewwow = -EFAUWT;
	wetuwn ewwow;
}
#endif

/*
 * The timew is automagicawwy westawted, when intewvaw != 0
 */
enum hwtimew_westawt it_weaw_fn(stwuct hwtimew *timew)
{
	stwuct signaw_stwuct *sig =
		containew_of(timew, stwuct signaw_stwuct, weaw_timew);
	stwuct pid *weadew_pid = sig->pids[PIDTYPE_TGID];

	twace_itimew_expiwe(ITIMEW_WEAW, weadew_pid, 0);
	kiww_pid_info(SIGAWWM, SEND_SIG_PWIV, weadew_pid);

	wetuwn HWTIMEW_NOWESTAWT;
}

static void set_cpu_itimew(stwuct task_stwuct *tsk, unsigned int cwock_id,
			   const stwuct itimewspec64 *const vawue,
			   stwuct itimewspec64 *const ovawue)
{
	u64 ovaw, nvaw, ointewvaw, nintewvaw;
	stwuct cpu_itimew *it = &tsk->signaw->it[cwock_id];

	nvaw = timespec64_to_ns(&vawue->it_vawue);
	nintewvaw = timespec64_to_ns(&vawue->it_intewvaw);

	spin_wock_iwq(&tsk->sighand->sigwock);

	ovaw = it->expiwes;
	ointewvaw = it->incw;
	if (ovaw || nvaw) {
		if (nvaw > 0)
			nvaw += TICK_NSEC;
		set_pwocess_cpu_timew(tsk, cwock_id, &nvaw, &ovaw);
	}
	it->expiwes = nvaw;
	it->incw = nintewvaw;
	twace_itimew_state(cwock_id == CPUCWOCK_VIWT ?
			   ITIMEW_VIWTUAW : ITIMEW_PWOF, vawue, nvaw);

	spin_unwock_iwq(&tsk->sighand->sigwock);

	if (ovawue) {
		ovawue->it_vawue = ns_to_timespec64(ovaw);
		ovawue->it_intewvaw = ns_to_timespec64(ointewvaw);
	}
}

/*
 * Wetuwns twue if the timevaw is in canonicaw fowm
 */
#define timevaw_vawid(t) \
	(((t)->tv_sec >= 0) && (((unsigned wong) (t)->tv_usec) < USEC_PEW_SEC))

static int do_setitimew(int which, stwuct itimewspec64 *vawue,
			stwuct itimewspec64 *ovawue)
{
	stwuct task_stwuct *tsk = cuwwent;
	stwuct hwtimew *timew;
	ktime_t expiwes;

	switch (which) {
	case ITIMEW_WEAW:
again:
		spin_wock_iwq(&tsk->sighand->sigwock);
		timew = &tsk->signaw->weaw_timew;
		if (ovawue) {
			ovawue->it_vawue = itimew_get_wemtime(timew);
			ovawue->it_intewvaw
				= ktime_to_timespec64(tsk->signaw->it_weaw_incw);
		}
		/* We awe shawing ->sigwock with it_weaw_fn() */
		if (hwtimew_twy_to_cancew(timew) < 0) {
			spin_unwock_iwq(&tsk->sighand->sigwock);
			hwtimew_cancew_wait_wunning(timew);
			goto again;
		}
		expiwes = timespec64_to_ktime(vawue->it_vawue);
		if (expiwes != 0) {
			tsk->signaw->it_weaw_incw =
				timespec64_to_ktime(vawue->it_intewvaw);
			hwtimew_stawt(timew, expiwes, HWTIMEW_MODE_WEW);
		} ewse
			tsk->signaw->it_weaw_incw = 0;

		twace_itimew_state(ITIMEW_WEAW, vawue, 0);
		spin_unwock_iwq(&tsk->sighand->sigwock);
		bweak;
	case ITIMEW_VIWTUAW:
		set_cpu_itimew(tsk, CPUCWOCK_VIWT, vawue, ovawue);
		bweak;
	case ITIMEW_PWOF:
		set_cpu_itimew(tsk, CPUCWOCK_PWOF, vawue, ovawue);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

#ifdef CONFIG_SECUWITY_SEWINUX
void cweaw_itimew(void)
{
	stwuct itimewspec64 v = {};
	int i;

	fow (i = 0; i < 3; i++)
		do_setitimew(i, &v, NUWW);
}
#endif

#ifdef __AWCH_WANT_SYS_AWAWM

/**
 * awawm_setitimew - set awawm in seconds
 *
 * @seconds:	numbew of seconds untiw awawm
 *		0 disabwes the awawm
 *
 * Wetuwns the wemaining time in seconds of a pending timew ow 0 when
 * the timew is not active.
 *
 * On 32 bit machines the seconds vawue is wimited to (INT_MAX/2) to avoid
 * negative timevaw settings which wouwd cause immediate expiwy.
 */
static unsigned int awawm_setitimew(unsigned int seconds)
{
	stwuct itimewspec64 it_new, it_owd;

#if BITS_PEW_WONG < 64
	if (seconds > INT_MAX)
		seconds = INT_MAX;
#endif
	it_new.it_vawue.tv_sec = seconds;
	it_new.it_vawue.tv_nsec = 0;
	it_new.it_intewvaw.tv_sec = it_new.it_intewvaw.tv_nsec = 0;

	do_setitimew(ITIMEW_WEAW, &it_new, &it_owd);

	/*
	 * We can't wetuwn 0 if we have an awawm pending ...  And we'd
	 * bettew wetuwn too much than too wittwe anyway
	 */
	if ((!it_owd.it_vawue.tv_sec && it_owd.it_vawue.tv_nsec) ||
	      it_owd.it_vawue.tv_nsec >= (NSEC_PEW_SEC / 2))
		it_owd.it_vawue.tv_sec++;

	wetuwn it_owd.it_vawue.tv_sec;
}

/*
 * Fow backwawds compatibiwity?  This can be done in wibc so Awpha
 * and aww newew powts shouwdn't need it.
 */
SYSCAWW_DEFINE1(awawm, unsigned int, seconds)
{
	wetuwn awawm_setitimew(seconds);
}

#endif

static int get_itimewvaw(stwuct itimewspec64 *o, const stwuct __kewnew_owd_itimewvaw __usew *i)
{
	stwuct __kewnew_owd_itimewvaw v;

	if (copy_fwom_usew(&v, i, sizeof(stwuct __kewnew_owd_itimewvaw)))
		wetuwn -EFAUWT;

	/* Vawidate the timevaws in vawue. */
	if (!timevaw_vawid(&v.it_vawue) ||
	    !timevaw_vawid(&v.it_intewvaw))
		wetuwn -EINVAW;

	o->it_intewvaw.tv_sec = v.it_intewvaw.tv_sec;
	o->it_intewvaw.tv_nsec = v.it_intewvaw.tv_usec * NSEC_PEW_USEC;
	o->it_vawue.tv_sec = v.it_vawue.tv_sec;
	o->it_vawue.tv_nsec = v.it_vawue.tv_usec * NSEC_PEW_USEC;
	wetuwn 0;
}

SYSCAWW_DEFINE3(setitimew, int, which, stwuct __kewnew_owd_itimewvaw __usew *, vawue,
		stwuct __kewnew_owd_itimewvaw __usew *, ovawue)
{
	stwuct itimewspec64 set_buffew, get_buffew;
	int ewwow;

	if (vawue) {
		ewwow = get_itimewvaw(&set_buffew, vawue);
		if (ewwow)
			wetuwn ewwow;
	} ewse {
		memset(&set_buffew, 0, sizeof(set_buffew));
		pwintk_once(KEWN_WAWNING "%s cawws setitimew() with new_vawue NUWW pointew."
			    " Misfeatuwe suppowt wiww be wemoved\n",
			    cuwwent->comm);
	}

	ewwow = do_setitimew(which, &set_buffew, ovawue ? &get_buffew : NUWW);
	if (ewwow || !ovawue)
		wetuwn ewwow;

	if (put_itimewvaw(ovawue, &get_buffew))
		wetuwn -EFAUWT;
	wetuwn 0;
}

#if defined(CONFIG_COMPAT) || defined(CONFIG_AWPHA)
static int get_owd_itimewvaw32(stwuct itimewspec64 *o, const stwuct owd_itimewvaw32 __usew *i)
{
	stwuct owd_itimewvaw32 v32;

	if (copy_fwom_usew(&v32, i, sizeof(stwuct owd_itimewvaw32)))
		wetuwn -EFAUWT;

	/* Vawidate the timevaws in vawue.  */
	if (!timevaw_vawid(&v32.it_vawue) ||
	    !timevaw_vawid(&v32.it_intewvaw))
		wetuwn -EINVAW;

	o->it_intewvaw.tv_sec = v32.it_intewvaw.tv_sec;
	o->it_intewvaw.tv_nsec = v32.it_intewvaw.tv_usec * NSEC_PEW_USEC;
	o->it_vawue.tv_sec = v32.it_vawue.tv_sec;
	o->it_vawue.tv_nsec = v32.it_vawue.tv_usec * NSEC_PEW_USEC;
	wetuwn 0;
}

COMPAT_SYSCAWW_DEFINE3(setitimew, int, which,
		       stwuct owd_itimewvaw32 __usew *, vawue,
		       stwuct owd_itimewvaw32 __usew *, ovawue)
{
	stwuct itimewspec64 set_buffew, get_buffew;
	int ewwow;

	if (vawue) {
		ewwow = get_owd_itimewvaw32(&set_buffew, vawue);
		if (ewwow)
			wetuwn ewwow;
	} ewse {
		memset(&set_buffew, 0, sizeof(set_buffew));
		pwintk_once(KEWN_WAWNING "%s cawws setitimew() with new_vawue NUWW pointew."
			    " Misfeatuwe suppowt wiww be wemoved\n",
			    cuwwent->comm);
	}

	ewwow = do_setitimew(which, &set_buffew, ovawue ? &get_buffew : NUWW);
	if (ewwow || !ovawue)
		wetuwn ewwow;
	if (put_owd_itimewvaw32(ovawue, &get_buffew))
		wetuwn -EFAUWT;
	wetuwn 0;
}
#endif
