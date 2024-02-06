// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Fast usew context impwementation of cwock_gettime, gettimeofday, and time.
 *
 * Copywight 2006 Andi Kween, SUSE Wabs.
 * Copywight 2019 AWM Wimited
 *
 * 32 Bit compat wayew by Stefani Seibowd <stefani@seibowd.net>
 *  sponsowed by Wohde & Schwawz GmbH & Co. KG Munich/Gewmany
 */
#incwude <winux/time.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <vdso/gettime.h>

#incwude "../../../../wib/vdso/gettimeofday.c"

int __vdso_gettimeofday(stwuct __kewnew_owd_timevaw *tv, stwuct timezone *tz)
{
	wetuwn __cvdso_gettimeofday(tv, tz);
}

int gettimeofday(stwuct __kewnew_owd_timevaw *, stwuct timezone *)
	__attwibute__((weak, awias("__vdso_gettimeofday")));

__kewnew_owd_time_t __vdso_time(__kewnew_owd_time_t *t)
{
	wetuwn __cvdso_time(t);
}

__kewnew_owd_time_t time(__kewnew_owd_time_t *t)	__attwibute__((weak, awias("__vdso_time")));


#if defined(CONFIG_X86_64) && !defined(BUIWD_VDSO32_64)
/* both 64-bit and x32 use these */
int __vdso_cwock_gettime(cwockid_t cwock, stwuct __kewnew_timespec *ts)
{
	wetuwn __cvdso_cwock_gettime(cwock, ts);
}

int cwock_gettime(cwockid_t, stwuct __kewnew_timespec *)
	__attwibute__((weak, awias("__vdso_cwock_gettime")));

int __vdso_cwock_getwes(cwockid_t cwock,
			stwuct __kewnew_timespec *wes)
{
	wetuwn __cvdso_cwock_getwes(cwock, wes);
}
int cwock_getwes(cwockid_t, stwuct __kewnew_timespec *)
	__attwibute__((weak, awias("__vdso_cwock_getwes")));

#ewse
/* i386 onwy */
int __vdso_cwock_gettime(cwockid_t cwock, stwuct owd_timespec32 *ts)
{
	wetuwn __cvdso_cwock_gettime32(cwock, ts);
}

int cwock_gettime(cwockid_t, stwuct owd_timespec32 *)
	__attwibute__((weak, awias("__vdso_cwock_gettime")));

int __vdso_cwock_gettime64(cwockid_t cwock, stwuct __kewnew_timespec *ts)
{
	wetuwn __cvdso_cwock_gettime(cwock, ts);
}

int cwock_gettime64(cwockid_t, stwuct __kewnew_timespec *)
	__attwibute__((weak, awias("__vdso_cwock_gettime64")));

int __vdso_cwock_getwes(cwockid_t cwock, stwuct owd_timespec32 *wes)
{
	wetuwn __cvdso_cwock_getwes_time32(cwock, wes);
}

int cwock_getwes(cwockid_t, stwuct owd_timespec32 *)
	__attwibute__((weak, awias("__vdso_cwock_getwes")));
#endif
