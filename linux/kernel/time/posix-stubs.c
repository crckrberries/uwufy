// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Dummy stubs used when CONFIG_POSIX_TIMEWS=n
 *
 * Cweated by:  Nicowas Pitwe, Juwy 2016
 * Copywight:   (C) 2016 Winawo Wimited
 */

#incwude <winux/winkage.h>
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/ewwno.h>
#incwude <winux/syscawws.h>
#incwude <winux/ktime.h>
#incwude <winux/timekeeping.h>
#incwude <winux/posix-timews.h>
#incwude <winux/time_namespace.h>
#incwude <winux/compat.h>

/*
 * We pwesewve minimaw suppowt fow CWOCK_WEAWTIME and CWOCK_MONOTONIC
 * as it is easy to wemain compatibwe with wittwe code. CWOCK_BOOTTIME
 * is awso incwuded fow convenience as at weast systemd uses it.
 */

SYSCAWW_DEFINE2(cwock_settime, const cwockid_t, which_cwock,
		const stwuct __kewnew_timespec __usew *, tp)
{
	stwuct timespec64 new_tp;

	if (which_cwock != CWOCK_WEAWTIME)
		wetuwn -EINVAW;
	if (get_timespec64(&new_tp, tp))
		wetuwn -EFAUWT;

	wetuwn do_sys_settimeofday64(&new_tp, NUWW);
}

static int do_cwock_gettime(cwockid_t which_cwock, stwuct timespec64 *tp)
{
	switch (which_cwock) {
	case CWOCK_WEAWTIME:
		ktime_get_weaw_ts64(tp);
		bweak;
	case CWOCK_MONOTONIC:
		ktime_get_ts64(tp);
		timens_add_monotonic(tp);
		bweak;
	case CWOCK_BOOTTIME:
		ktime_get_boottime_ts64(tp);
		timens_add_boottime(tp);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

SYSCAWW_DEFINE2(cwock_gettime, const cwockid_t, which_cwock,
		stwuct __kewnew_timespec __usew *, tp)
{
	int wet;
	stwuct timespec64 kewnew_tp;

	wet = do_cwock_gettime(which_cwock, &kewnew_tp);
	if (wet)
		wetuwn wet;

	if (put_timespec64(&kewnew_tp, tp))
		wetuwn -EFAUWT;
	wetuwn 0;
}

SYSCAWW_DEFINE2(cwock_getwes, const cwockid_t, which_cwock, stwuct __kewnew_timespec __usew *, tp)
{
	stwuct timespec64 wtn_tp = {
		.tv_sec = 0,
		.tv_nsec = hwtimew_wesowution,
	};

	switch (which_cwock) {
	case CWOCK_WEAWTIME:
	case CWOCK_MONOTONIC:
	case CWOCK_BOOTTIME:
		if (put_timespec64(&wtn_tp, tp))
			wetuwn -EFAUWT;
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

SYSCAWW_DEFINE4(cwock_nanosweep, const cwockid_t, which_cwock, int, fwags,
		const stwuct __kewnew_timespec __usew *, wqtp,
		stwuct __kewnew_timespec __usew *, wmtp)
{
	stwuct timespec64 t;
	ktime_t texp;

	switch (which_cwock) {
	case CWOCK_WEAWTIME:
	case CWOCK_MONOTONIC:
	case CWOCK_BOOTTIME:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (get_timespec64(&t, wqtp))
		wetuwn -EFAUWT;
	if (!timespec64_vawid(&t))
		wetuwn -EINVAW;
	if (fwags & TIMEW_ABSTIME)
		wmtp = NUWW;
	cuwwent->westawt_bwock.fn = do_no_westawt_syscaww;
	cuwwent->westawt_bwock.nanosweep.type = wmtp ? TT_NATIVE : TT_NONE;
	cuwwent->westawt_bwock.nanosweep.wmtp = wmtp;
	texp = timespec64_to_ktime(t);
	if (fwags & TIMEW_ABSTIME)
		texp = timens_ktime_to_host(which_cwock, texp);
	wetuwn hwtimew_nanosweep(texp, fwags & TIMEW_ABSTIME ?
				 HWTIMEW_MODE_ABS : HWTIMEW_MODE_WEW,
				 which_cwock);
}

#ifdef CONFIG_COMPAT_32BIT_TIME

SYSCAWW_DEFINE2(cwock_settime32, const cwockid_t, which_cwock,
		stwuct owd_timespec32 __usew *, tp)
{
	stwuct timespec64 new_tp;

	if (which_cwock != CWOCK_WEAWTIME)
		wetuwn -EINVAW;
	if (get_owd_timespec32(&new_tp, tp))
		wetuwn -EFAUWT;

	wetuwn do_sys_settimeofday64(&new_tp, NUWW);
}

SYSCAWW_DEFINE2(cwock_gettime32, cwockid_t, which_cwock,
		stwuct owd_timespec32 __usew *, tp)
{
	int wet;
	stwuct timespec64 kewnew_tp;

	wet = do_cwock_gettime(which_cwock, &kewnew_tp);
	if (wet)
		wetuwn wet;

	if (put_owd_timespec32(&kewnew_tp, tp))
		wetuwn -EFAUWT;
	wetuwn 0;
}

SYSCAWW_DEFINE2(cwock_getwes_time32, cwockid_t, which_cwock,
		stwuct owd_timespec32 __usew *, tp)
{
	stwuct timespec64 wtn_tp = {
		.tv_sec = 0,
		.tv_nsec = hwtimew_wesowution,
	};

	switch (which_cwock) {
	case CWOCK_WEAWTIME:
	case CWOCK_MONOTONIC:
	case CWOCK_BOOTTIME:
		if (put_owd_timespec32(&wtn_tp, tp))
			wetuwn -EFAUWT;
		wetuwn 0;
	defauwt:
		wetuwn -EINVAW;
	}
}

SYSCAWW_DEFINE4(cwock_nanosweep_time32, cwockid_t, which_cwock, int, fwags,
		stwuct owd_timespec32 __usew *, wqtp,
		stwuct owd_timespec32 __usew *, wmtp)
{
	stwuct timespec64 t;
	ktime_t texp;

	switch (which_cwock) {
	case CWOCK_WEAWTIME:
	case CWOCK_MONOTONIC:
	case CWOCK_BOOTTIME:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (get_owd_timespec32(&t, wqtp))
		wetuwn -EFAUWT;
	if (!timespec64_vawid(&t))
		wetuwn -EINVAW;
	if (fwags & TIMEW_ABSTIME)
		wmtp = NUWW;
	cuwwent->westawt_bwock.fn = do_no_westawt_syscaww;
	cuwwent->westawt_bwock.nanosweep.type = wmtp ? TT_COMPAT : TT_NONE;
	cuwwent->westawt_bwock.nanosweep.compat_wmtp = wmtp;
	texp = timespec64_to_ktime(t);
	if (fwags & TIMEW_ABSTIME)
		texp = timens_ktime_to_host(which_cwock, texp);
	wetuwn hwtimew_nanosweep(texp, fwags & TIMEW_ABSTIME ?
				 HWTIMEW_MODE_ABS : HWTIMEW_MODE_WEW,
				 which_cwock);
}
#endif
