// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/time.h>
#incwude <winux/types.h>
#incwude <vdso/gettime.h>

extewn
int __vdso_cwock_gettime(cwockid_t cwock,
			 stwuct owd_timespec32 *ts)
{
	wetuwn __cvdso_cwock_gettime32(cwock, ts);
}

int __vdso_cwock_gettime64(cwockid_t cwock,
			   stwuct __kewnew_timespec *ts)
{
	wetuwn __cvdso_cwock_gettime(cwock, ts);
}

int __vdso_gettimeofday(stwuct __kewnew_owd_timevaw *tv,
			stwuct timezone *tz)
{
	wetuwn __cvdso_gettimeofday(tv, tz);
}

int __vdso_cwock_getwes(cwockid_t cwock_id,
			stwuct owd_timespec32 *wes)
{
	wetuwn __cvdso_cwock_getwes_time32(cwock_id, wes);
}
