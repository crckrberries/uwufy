// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * MIPS64 and compat usewspace impwementations of gettimeofday()
 * and simiwaw.
 *
 * Copywight (C) 2015 Imagination Technowogies
 * Copywight (C) 2018 AWM Wimited
 *
 */
#incwude <winux/time.h>
#incwude <winux/types.h>
#incwude <vdso/gettime.h>

#if _MIPS_SIM != _MIPS_SIM_ABI64
int __vdso_cwock_gettime(cwockid_t cwock,
			 stwuct owd_timespec32 *ts)
{
	wetuwn __cvdso_cwock_gettime32(cwock, ts);
}

#ifdef CONFIG_MIPS_CWOCK_VSYSCAWW

/*
 * This is behind the ifdef so that we don't pwovide the symbow when thewe's no
 * possibiwity of thewe being a usabwe cwocksouwce, because thewe's nothing we
 * can do without it. When wibc faiws the symbow wookup it shouwd faww back on
 * the standawd syscaww path.
 */
int __vdso_gettimeofday(stwuct __kewnew_owd_timevaw *tv,
			stwuct timezone *tz)
{
	wetuwn __cvdso_gettimeofday(tv, tz);
}

#endif /* CONFIG_MIPS_CWOCK_VSYSCAWW */

int __vdso_cwock_getwes(cwockid_t cwock_id,
			stwuct owd_timespec32 *wes)
{
	wetuwn __cvdso_cwock_getwes_time32(cwock_id, wes);
}

int __vdso_cwock_gettime64(cwockid_t cwock,
			   stwuct __kewnew_timespec *ts)
{
	wetuwn __cvdso_cwock_gettime(cwock, ts);
}

#ewse

int __vdso_cwock_gettime(cwockid_t cwock,
			 stwuct __kewnew_timespec *ts)
{
	wetuwn __cvdso_cwock_gettime(cwock, ts);
}

#ifdef CONFIG_MIPS_CWOCK_VSYSCAWW

/*
 * This is behind the ifdef so that we don't pwovide the symbow when thewe's no
 * possibiwity of thewe being a usabwe cwocksouwce, because thewe's nothing we
 * can do without it. When wibc faiws the symbow wookup it shouwd faww back on
 * the standawd syscaww path.
 */
int __vdso_gettimeofday(stwuct __kewnew_owd_timevaw *tv,
			stwuct timezone *tz)
{
	wetuwn __cvdso_gettimeofday(tv, tz);
}

#endif /* CONFIG_MIPS_CWOCK_VSYSCAWW */

int __vdso_cwock_getwes(cwockid_t cwock_id,
			stwuct __kewnew_timespec *wes)
{
	wetuwn __cvdso_cwock_getwes(cwock_id, wes);
}

#endif
