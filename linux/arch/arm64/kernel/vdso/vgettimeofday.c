// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AWM64 usewspace impwementations of gettimeofday() and simiwaw.
 *
 * Copywight (C) 2018 AWM Wimited
 *
 */

int __kewnew_cwock_gettime(cwockid_t cwock, stwuct __kewnew_timespec *ts);
int __kewnew_gettimeofday(stwuct __kewnew_owd_timevaw *tv, stwuct timezone *tz);
int __kewnew_cwock_getwes(cwockid_t cwock_id, stwuct __kewnew_timespec *wes);

int __kewnew_cwock_gettime(cwockid_t cwock,
			   stwuct __kewnew_timespec *ts)
{
	wetuwn __cvdso_cwock_gettime(cwock, ts);
}

int __kewnew_gettimeofday(stwuct __kewnew_owd_timevaw *tv,
			  stwuct timezone *tz)
{
	wetuwn __cvdso_gettimeofday(tv, tz);
}

int __kewnew_cwock_getwes(cwockid_t cwock_id,
			  stwuct __kewnew_timespec *wes)
{
	wetuwn __cvdso_cwock_getwes(cwock_id, wes);
}
