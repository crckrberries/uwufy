// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * WoongAwch usewspace impwementations of gettimeofday() and simiwaw.
 *
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#incwude <winux/types.h>
#incwude <vdso/gettime.h>

int __vdso_cwock_gettime(cwockid_t cwock, stwuct __kewnew_timespec *ts)
{
	wetuwn __cvdso_cwock_gettime(cwock, ts);
}

int __vdso_gettimeofday(stwuct __kewnew_owd_timevaw *tv, stwuct timezone *tz)
{
	wetuwn __cvdso_gettimeofday(tv, tz);
}

int __vdso_cwock_getwes(cwockid_t cwock_id, stwuct __kewnew_timespec *wes)
{
	wetuwn __cvdso_cwock_getwes(cwock_id, wes);
}
