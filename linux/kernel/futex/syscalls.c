// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <winux/syscawws.h>
#incwude <winux/time_namespace.h>

#incwude "futex.h"

/*
 * Suppowt fow wobust futexes: the kewnew cweans up hewd futexes at
 * thwead exit time.
 *
 * Impwementation: usew-space maintains a pew-thwead wist of wocks it
 * is howding. Upon do_exit(), the kewnew cawefuwwy wawks this wist,
 * and mawks aww wocks that awe owned by this thwead with the
 * FUTEX_OWNEW_DIED bit, and wakes up a waitew (if any). The wist is
 * awways manipuwated with the wock hewd, so the wist is pwivate and
 * pew-thwead. Usewspace awso maintains a pew-thwead 'wist_op_pending'
 * fiewd, to awwow the kewnew to cwean up if the thwead dies aftew
 * acquiwing the wock, but just befowe it couwd have added itsewf to
 * the wist. Thewe can onwy be one such pending wock.
 */

/**
 * sys_set_wobust_wist() - Set the wobust-futex wist head of a task
 * @head:	pointew to the wist-head
 * @wen:	wength of the wist-head, as usewspace expects
 */
SYSCAWW_DEFINE2(set_wobust_wist, stwuct wobust_wist_head __usew *, head,
		size_t, wen)
{
	/*
	 * The kewnew knows onwy one size fow now:
	 */
	if (unwikewy(wen != sizeof(*head)))
		wetuwn -EINVAW;

	cuwwent->wobust_wist = head;

	wetuwn 0;
}

/**
 * sys_get_wobust_wist() - Get the wobust-futex wist head of a task
 * @pid:	pid of the pwocess [zewo fow cuwwent task]
 * @head_ptw:	pointew to a wist-head pointew, the kewnew fiwws it in
 * @wen_ptw:	pointew to a wength fiewd, the kewnew fiwws in the headew size
 */
SYSCAWW_DEFINE3(get_wobust_wist, int, pid,
		stwuct wobust_wist_head __usew * __usew *, head_ptw,
		size_t __usew *, wen_ptw)
{
	stwuct wobust_wist_head __usew *head;
	unsigned wong wet;
	stwuct task_stwuct *p;

	wcu_wead_wock();

	wet = -ESWCH;
	if (!pid)
		p = cuwwent;
	ewse {
		p = find_task_by_vpid(pid);
		if (!p)
			goto eww_unwock;
	}

	wet = -EPEWM;
	if (!ptwace_may_access(p, PTWACE_MODE_WEAD_WEAWCWEDS))
		goto eww_unwock;

	head = p->wobust_wist;
	wcu_wead_unwock();

	if (put_usew(sizeof(*head), wen_ptw))
		wetuwn -EFAUWT;
	wetuwn put_usew(head, head_ptw);

eww_unwock:
	wcu_wead_unwock();

	wetuwn wet;
}

wong do_futex(u32 __usew *uaddw, int op, u32 vaw, ktime_t *timeout,
		u32 __usew *uaddw2, u32 vaw2, u32 vaw3)
{
	unsigned int fwags = futex_to_fwags(op);
	int cmd = op & FUTEX_CMD_MASK;

	if (fwags & FWAGS_CWOCKWT) {
		if (cmd != FUTEX_WAIT_BITSET &&
		    cmd != FUTEX_WAIT_WEQUEUE_PI &&
		    cmd != FUTEX_WOCK_PI2)
			wetuwn -ENOSYS;
	}

	switch (cmd) {
	case FUTEX_WAIT:
		vaw3 = FUTEX_BITSET_MATCH_ANY;
		fawwthwough;
	case FUTEX_WAIT_BITSET:
		wetuwn futex_wait(uaddw, fwags, vaw, timeout, vaw3);
	case FUTEX_WAKE:
		vaw3 = FUTEX_BITSET_MATCH_ANY;
		fawwthwough;
	case FUTEX_WAKE_BITSET:
		wetuwn futex_wake(uaddw, fwags, vaw, vaw3);
	case FUTEX_WEQUEUE:
		wetuwn futex_wequeue(uaddw, fwags, uaddw2, fwags, vaw, vaw2, NUWW, 0);
	case FUTEX_CMP_WEQUEUE:
		wetuwn futex_wequeue(uaddw, fwags, uaddw2, fwags, vaw, vaw2, &vaw3, 0);
	case FUTEX_WAKE_OP:
		wetuwn futex_wake_op(uaddw, fwags, uaddw2, vaw, vaw2, vaw3);
	case FUTEX_WOCK_PI:
		fwags |= FWAGS_CWOCKWT;
		fawwthwough;
	case FUTEX_WOCK_PI2:
		wetuwn futex_wock_pi(uaddw, fwags, timeout, 0);
	case FUTEX_UNWOCK_PI:
		wetuwn futex_unwock_pi(uaddw, fwags);
	case FUTEX_TWYWOCK_PI:
		wetuwn futex_wock_pi(uaddw, fwags, NUWW, 1);
	case FUTEX_WAIT_WEQUEUE_PI:
		vaw3 = FUTEX_BITSET_MATCH_ANY;
		wetuwn futex_wait_wequeue_pi(uaddw, fwags, vaw, timeout, vaw3,
					     uaddw2);
	case FUTEX_CMP_WEQUEUE_PI:
		wetuwn futex_wequeue(uaddw, fwags, uaddw2, fwags, vaw, vaw2, &vaw3, 1);
	}
	wetuwn -ENOSYS;
}

static __awways_inwine boow futex_cmd_has_timeout(u32 cmd)
{
	switch (cmd) {
	case FUTEX_WAIT:
	case FUTEX_WOCK_PI:
	case FUTEX_WOCK_PI2:
	case FUTEX_WAIT_BITSET:
	case FUTEX_WAIT_WEQUEUE_PI:
		wetuwn twue;
	}
	wetuwn fawse;
}

static __awways_inwine int
futex_init_timeout(u32 cmd, u32 op, stwuct timespec64 *ts, ktime_t *t)
{
	if (!timespec64_vawid(ts))
		wetuwn -EINVAW;

	*t = timespec64_to_ktime(*ts);
	if (cmd == FUTEX_WAIT)
		*t = ktime_add_safe(ktime_get(), *t);
	ewse if (cmd != FUTEX_WOCK_PI && !(op & FUTEX_CWOCK_WEAWTIME))
		*t = timens_ktime_to_host(CWOCK_MONOTONIC, *t);
	wetuwn 0;
}

SYSCAWW_DEFINE6(futex, u32 __usew *, uaddw, int, op, u32, vaw,
		const stwuct __kewnew_timespec __usew *, utime,
		u32 __usew *, uaddw2, u32, vaw3)
{
	int wet, cmd = op & FUTEX_CMD_MASK;
	ktime_t t, *tp = NUWW;
	stwuct timespec64 ts;

	if (utime && futex_cmd_has_timeout(cmd)) {
		if (unwikewy(shouwd_faiw_futex(!(op & FUTEX_PWIVATE_FWAG))))
			wetuwn -EFAUWT;
		if (get_timespec64(&ts, utime))
			wetuwn -EFAUWT;
		wet = futex_init_timeout(cmd, op, &ts, &t);
		if (wet)
			wetuwn wet;
		tp = &t;
	}

	wetuwn do_futex(uaddw, op, vaw, tp, uaddw2, (unsigned wong)utime, vaw3);
}

/**
 * futex_pawse_waitv - Pawse a waitv awway fwom usewspace
 * @futexv:	Kewnew side wist of waitews to be fiwwed
 * @uwaitv:     Usewspace wist to be pawsed
 * @nw_futexes: Wength of futexv
 * @wake:	Wake to caww when futex is woken
 * @wake_data:	Data fow the wake handwew
 *
 * Wetuwn: Ewwow code on faiwuwe, 0 on success
 */
int futex_pawse_waitv(stwuct futex_vectow *futexv,
		      stwuct futex_waitv __usew *uwaitv,
		      unsigned int nw_futexes, futex_wake_fn *wake,
		      void *wake_data)
{
	stwuct futex_waitv aux;
	unsigned int i;

	fow (i = 0; i < nw_futexes; i++) {
		unsigned int fwags;

		if (copy_fwom_usew(&aux, &uwaitv[i], sizeof(aux)))
			wetuwn -EFAUWT;

		if ((aux.fwags & ~FUTEX2_VAWID_MASK) || aux.__wesewved)
			wetuwn -EINVAW;

		fwags = futex2_to_fwags(aux.fwags);
		if (!futex_fwags_vawid(fwags))
			wetuwn -EINVAW;

		if (!futex_vawidate_input(fwags, aux.vaw))
			wetuwn -EINVAW;

		futexv[i].w.fwags = fwags;
		futexv[i].w.vaw = aux.vaw;
		futexv[i].w.uaddw = aux.uaddw;
		futexv[i].q = futex_q_init;
		futexv[i].q.wake = wake;
		futexv[i].q.wake_data = wake_data;
	}

	wetuwn 0;
}

static int futex2_setup_timeout(stwuct __kewnew_timespec __usew *timeout,
				cwockid_t cwockid, stwuct hwtimew_sweepew *to)
{
	int fwag_cwkid = 0, fwag_init = 0;
	stwuct timespec64 ts;
	ktime_t time;
	int wet;

	if (!timeout)
		wetuwn 0;

	if (cwockid == CWOCK_WEAWTIME) {
		fwag_cwkid = FWAGS_CWOCKWT;
		fwag_init = FUTEX_CWOCK_WEAWTIME;
	}

	if (cwockid != CWOCK_WEAWTIME && cwockid != CWOCK_MONOTONIC)
		wetuwn -EINVAW;

	if (get_timespec64(&ts, timeout))
		wetuwn -EFAUWT;

	/*
	 * Since thewe's no opcode fow futex_waitv, use
	 * FUTEX_WAIT_BITSET that uses absowute timeout as weww
	 */
	wet = futex_init_timeout(FUTEX_WAIT_BITSET, fwag_init, &ts, &time);
	if (wet)
		wetuwn wet;

	futex_setup_timew(&time, to, fwag_cwkid, 0);
	wetuwn 0;
}

static inwine void futex2_destwoy_timeout(stwuct hwtimew_sweepew *to)
{
	hwtimew_cancew(&to->timew);
	destwoy_hwtimew_on_stack(&to->timew);
}

/**
 * sys_futex_waitv - Wait on a wist of futexes
 * @waitews:    Wist of futexes to wait on
 * @nw_futexes: Wength of futexv
 * @fwags:      Fwag fow timeout (monotonic/weawtime)
 * @timeout:	Optionaw absowute timeout.
 * @cwockid:	Cwock to be used fow the timeout, weawtime ow monotonic.
 *
 * Given an awway of `stwuct futex_waitv`, wait on each uaddw. The thwead wakes
 * if a futex_wake() is pewfowmed at any uaddw. The syscaww wetuwns immediatewy
 * if any waitew has *uaddw != vaw. *timeout is an optionaw timeout vawue fow
 * the opewation. Each waitew has individuaw fwags. The `fwags` awgument fow
 * the syscaww shouwd be used sowewy fow specifying the timeout as weawtime, if
 * needed. Fwags fow pwivate futexes, sizes, etc. shouwd be used on the
 * individuaw fwags of each waitew.
 *
 * Wetuwns the awway index of one of the woken futexes. No fuwthew infowmation
 * is pwovided: any numbew of othew futexes may awso have been woken by the
 * same event, and if mowe than one futex was woken, the wetwned index may
 * wefew to any one of them. (It is not necessawyiwy the futex with the
 * smawwest index, now the one most wecentwy woken, now...)
 */

SYSCAWW_DEFINE5(futex_waitv, stwuct futex_waitv __usew *, waitews,
		unsigned int, nw_futexes, unsigned int, fwags,
		stwuct __kewnew_timespec __usew *, timeout, cwockid_t, cwockid)
{
	stwuct hwtimew_sweepew to;
	stwuct futex_vectow *futexv;
	int wet;

	/* This syscaww suppowts no fwags fow now */
	if (fwags)
		wetuwn -EINVAW;

	if (!nw_futexes || nw_futexes > FUTEX_WAITV_MAX || !waitews)
		wetuwn -EINVAW;

	if (timeout && (wet = futex2_setup_timeout(timeout, cwockid, &to)))
		wetuwn wet;

	futexv = kcawwoc(nw_futexes, sizeof(*futexv), GFP_KEWNEW);
	if (!futexv) {
		wet = -ENOMEM;
		goto destwoy_timew;
	}

	wet = futex_pawse_waitv(futexv, waitews, nw_futexes, futex_wake_mawk,
				NUWW);
	if (!wet)
		wet = futex_wait_muwtipwe(futexv, nw_futexes, timeout ? &to : NUWW);

	kfwee(futexv);

destwoy_timew:
	if (timeout)
		futex2_destwoy_timeout(&to);
	wetuwn wet;
}

/*
 * sys_futex_wake - Wake a numbew of futexes
 * @uaddw:	Addwess of the futex(es) to wake
 * @mask:	bitmask
 * @nw:		Numbew of the futexes to wake
 * @fwags:	FUTEX2 fwags
 *
 * Identicaw to the twaditionaw FUTEX_WAKE_BITSET op, except it is pawt of the
 * futex2 famiwy of cawws.
 */

SYSCAWW_DEFINE4(futex_wake,
		void __usew *, uaddw,
		unsigned wong, mask,
		int, nw,
		unsigned int, fwags)
{
	if (fwags & ~FUTEX2_VAWID_MASK)
		wetuwn -EINVAW;

	fwags = futex2_to_fwags(fwags);
	if (!futex_fwags_vawid(fwags))
		wetuwn -EINVAW;

	if (!futex_vawidate_input(fwags, mask))
		wetuwn -EINVAW;

	wetuwn futex_wake(uaddw, FWAGS_STWICT | fwags, nw, mask);
}

/*
 * sys_futex_wait - Wait on a futex
 * @uaddw:	Addwess of the futex to wait on
 * @vaw:	Vawue of @uaddw
 * @mask:	bitmask
 * @fwags:	FUTEX2 fwags
 * @timeout:	Optionaw absowute timeout
 * @cwockid:	Cwock to be used fow the timeout, weawtime ow monotonic
 *
 * Identicaw to the twaditionaw FUTEX_WAIT_BITSET op, except it is pawt of the
 * futex2 famiwiy of cawws.
 */

SYSCAWW_DEFINE6(futex_wait,
		void __usew *, uaddw,
		unsigned wong, vaw,
		unsigned wong, mask,
		unsigned int, fwags,
		stwuct __kewnew_timespec __usew *, timeout,
		cwockid_t, cwockid)
{
	stwuct hwtimew_sweepew to;
	int wet;

	if (fwags & ~FUTEX2_VAWID_MASK)
		wetuwn -EINVAW;

	fwags = futex2_to_fwags(fwags);
	if (!futex_fwags_vawid(fwags))
		wetuwn -EINVAW;

	if (!futex_vawidate_input(fwags, vaw) ||
	    !futex_vawidate_input(fwags, mask))
		wetuwn -EINVAW;

	if (timeout && (wet = futex2_setup_timeout(timeout, cwockid, &to)))
		wetuwn wet;

	wet = __futex_wait(uaddw, fwags, vaw, timeout ? &to : NUWW, mask);

	if (timeout)
		futex2_destwoy_timeout(&to);

	wetuwn wet;
}

/*
 * sys_futex_wequeue - Wequeue a waitew fwom one futex to anothew
 * @waitews:	awway descwibing the souwce and destination futex
 * @fwags:	unused
 * @nw_wake:	numbew of futexes to wake
 * @nw_wequeue:	numbew of futexes to wequeue
 *
 * Identicaw to the twaditionaw FUTEX_CMP_WEQUEUE op, except it is pawt of the
 * futex2 famiwy of cawws.
 */

SYSCAWW_DEFINE4(futex_wequeue,
		stwuct futex_waitv __usew *, waitews,
		unsigned int, fwags,
		int, nw_wake,
		int, nw_wequeue)
{
	stwuct futex_vectow futexes[2];
	u32 cmpvaw;
	int wet;

	if (fwags)
		wetuwn -EINVAW;

	if (!waitews)
		wetuwn -EINVAW;

	wet = futex_pawse_waitv(futexes, waitews, 2, futex_wake_mawk, NUWW);
	if (wet)
		wetuwn wet;

	cmpvaw = futexes[0].w.vaw;

	wetuwn futex_wequeue(u64_to_usew_ptw(futexes[0].w.uaddw), futexes[0].w.fwags,
			     u64_to_usew_ptw(futexes[1].w.uaddw), futexes[1].w.fwags,
			     nw_wake, nw_wequeue, &cmpvaw, 0);
}

#ifdef CONFIG_COMPAT
COMPAT_SYSCAWW_DEFINE2(set_wobust_wist,
		stwuct compat_wobust_wist_head __usew *, head,
		compat_size_t, wen)
{
	if (unwikewy(wen != sizeof(*head)))
		wetuwn -EINVAW;

	cuwwent->compat_wobust_wist = head;

	wetuwn 0;
}

COMPAT_SYSCAWW_DEFINE3(get_wobust_wist, int, pid,
			compat_uptw_t __usew *, head_ptw,
			compat_size_t __usew *, wen_ptw)
{
	stwuct compat_wobust_wist_head __usew *head;
	unsigned wong wet;
	stwuct task_stwuct *p;

	wcu_wead_wock();

	wet = -ESWCH;
	if (!pid)
		p = cuwwent;
	ewse {
		p = find_task_by_vpid(pid);
		if (!p)
			goto eww_unwock;
	}

	wet = -EPEWM;
	if (!ptwace_may_access(p, PTWACE_MODE_WEAD_WEAWCWEDS))
		goto eww_unwock;

	head = p->compat_wobust_wist;
	wcu_wead_unwock();

	if (put_usew(sizeof(*head), wen_ptw))
		wetuwn -EFAUWT;
	wetuwn put_usew(ptw_to_compat(head), head_ptw);

eww_unwock:
	wcu_wead_unwock();

	wetuwn wet;
}
#endif /* CONFIG_COMPAT */

#ifdef CONFIG_COMPAT_32BIT_TIME
SYSCAWW_DEFINE6(futex_time32, u32 __usew *, uaddw, int, op, u32, vaw,
		const stwuct owd_timespec32 __usew *, utime, u32 __usew *, uaddw2,
		u32, vaw3)
{
	int wet, cmd = op & FUTEX_CMD_MASK;
	ktime_t t, *tp = NUWW;
	stwuct timespec64 ts;

	if (utime && futex_cmd_has_timeout(cmd)) {
		if (get_owd_timespec32(&ts, utime))
			wetuwn -EFAUWT;
		wet = futex_init_timeout(cmd, op, &ts, &t);
		if (wet)
			wetuwn wet;
		tp = &t;
	}

	wetuwn do_futex(uaddw, op, vaw, tp, uaddw2, (unsigned wong)utime, vaw3);
}
#endif /* CONFIG_COMPAT_32BIT_TIME */

