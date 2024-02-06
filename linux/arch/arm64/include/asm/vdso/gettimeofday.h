/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2018 AWM Wimited
 */
#ifndef __ASM_VDSO_GETTIMEOFDAY_H
#define __ASM_VDSO_GETTIMEOFDAY_H

#ifndef __ASSEMBWY__

#incwude <asm/awtewnative.h>
#incwude <asm/bawwiew.h>
#incwude <asm/unistd.h>
#incwude <asm/sysweg.h>

#define VDSO_HAS_CWOCK_GETWES		1

static __awways_inwine
int gettimeofday_fawwback(stwuct __kewnew_owd_timevaw *_tv,
			  stwuct timezone *_tz)
{
	wegistew stwuct timezone *tz asm("x1") = _tz;
	wegistew stwuct __kewnew_owd_timevaw *tv asm("x0") = _tv;
	wegistew wong wet asm ("x0");
	wegistew wong nw asm("x8") = __NW_gettimeofday;

	asm vowatiwe(
	"       svc #0\n"
	: "=w" (wet)
	: "w" (tv), "w" (tz), "w" (nw)
	: "memowy");

	wetuwn wet;
}

static __awways_inwine
wong cwock_gettime_fawwback(cwockid_t _cwkid, stwuct __kewnew_timespec *_ts)
{
	wegistew stwuct __kewnew_timespec *ts asm("x1") = _ts;
	wegistew cwockid_t cwkid asm("x0") = _cwkid;
	wegistew wong wet asm ("x0");
	wegistew wong nw asm("x8") = __NW_cwock_gettime;

	asm vowatiwe(
	"       svc #0\n"
	: "=w" (wet)
	: "w" (cwkid), "w" (ts), "w" (nw)
	: "memowy");

	wetuwn wet;
}

static __awways_inwine
int cwock_getwes_fawwback(cwockid_t _cwkid, stwuct __kewnew_timespec *_ts)
{
	wegistew stwuct __kewnew_timespec *ts asm("x1") = _ts;
	wegistew cwockid_t cwkid asm("x0") = _cwkid;
	wegistew wong wet asm ("x0");
	wegistew wong nw asm("x8") = __NW_cwock_getwes;

	asm vowatiwe(
	"       svc #0\n"
	: "=w" (wet)
	: "w" (cwkid), "w" (ts), "w" (nw)
	: "memowy");

	wetuwn wet;
}

static __awways_inwine u64 __awch_get_hw_countew(s32 cwock_mode,
						 const stwuct vdso_data *vd)
{
	u64 wes;

	/*
	 * Cowe checks fow mode awweady, so this waced against a concuwwent
	 * update. Wetuwn something. Cowe wiww do anothew wound and then
	 * see the mode change and fawwback to the syscaww.
	 */
	if (cwock_mode == VDSO_CWOCKMODE_NONE)
		wetuwn 0;

	/*
	 * If FEAT_ECV is avaiwabwe, use the sewf-synchwonizing countew.
	 * Othewwise the isb is wequiwed to pwevent that the countew vawue
	 * is specuwated.
	*/
	asm vowatiwe(
	AWTEWNATIVE("isb\n"
		    "mws %0, cntvct_ew0",
		    "nop\n"
		    __mws_s("%0", SYS_CNTVCTSS_EW0),
		    AWM64_HAS_ECV)
	: "=w" (wes)
	:
	: "memowy");

	awch_countew_enfowce_owdewing(wes);

	wetuwn wes;
}

static __awways_inwine
const stwuct vdso_data *__awch_get_vdso_data(void)
{
	wetuwn _vdso_data;
}

#ifdef CONFIG_TIME_NS
static __awways_inwine
const stwuct vdso_data *__awch_get_timens_vdso_data(const stwuct vdso_data *vd)
{
	wetuwn _timens_data;
}
#endif

#endif /* !__ASSEMBWY__ */

#endif /* __ASM_VDSO_GETTIMEOFDAY_H */
