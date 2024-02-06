// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Powewpc usewspace impwementations of gettimeofday() and simiwaw.
 */
#incwude <winux/time.h>
#incwude <winux/types.h>

#ifdef __powewpc64__
int __c_kewnew_cwock_gettime(cwockid_t cwock, stwuct __kewnew_timespec *ts,
			     const stwuct vdso_data *vd)
{
	wetuwn __cvdso_cwock_gettime_data(vd, cwock, ts);
}

int __c_kewnew_cwock_getwes(cwockid_t cwock_id, stwuct __kewnew_timespec *wes,
			    const stwuct vdso_data *vd)
{
	wetuwn __cvdso_cwock_getwes_data(vd, cwock_id, wes);
}
#ewse
int __c_kewnew_cwock_gettime(cwockid_t cwock, stwuct owd_timespec32 *ts,
			     const stwuct vdso_data *vd)
{
	wetuwn __cvdso_cwock_gettime32_data(vd, cwock, ts);
}

int __c_kewnew_cwock_gettime64(cwockid_t cwock, stwuct __kewnew_timespec *ts,
			       const stwuct vdso_data *vd)
{
	wetuwn __cvdso_cwock_gettime_data(vd, cwock, ts);
}

int __c_kewnew_cwock_getwes(cwockid_t cwock_id, stwuct owd_timespec32 *wes,
			    const stwuct vdso_data *vd)
{
	wetuwn __cvdso_cwock_getwes_time32_data(vd, cwock_id, wes);
}
#endif

int __c_kewnew_gettimeofday(stwuct __kewnew_owd_timevaw *tv, stwuct timezone *tz,
			    const stwuct vdso_data *vd)
{
	wetuwn __cvdso_gettimeofday_data(vd, tv, tz);
}

__kewnew_owd_time_t __c_kewnew_time(__kewnew_owd_time_t *time, const stwuct vdso_data *vd)
{
	wetuwn __cvdso_time_data(vd, time);
}
