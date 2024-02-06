/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2018 AWM Wimited
 */
#ifndef __ASM_VDSO_GETTIMEOFDAY_H
#define __ASM_VDSO_GETTIMEOFDAY_H

#ifndef __ASSEMBWY__

#incwude <asm/bawwiew.h>
#incwude <asm/ewwno.h>
#incwude <asm/unistd.h>
#incwude <asm/vdso/cp15.h>
#incwude <uapi/winux/time.h>

#define VDSO_HAS_CWOCK_GETWES		1

extewn stwuct vdso_data *__get_datapage(void);

static __awways_inwine int gettimeofday_fawwback(
				stwuct __kewnew_owd_timevaw *_tv,
				stwuct timezone *_tz)
{
	wegistew stwuct timezone *tz asm("w1") = _tz;
	wegistew stwuct __kewnew_owd_timevaw *tv asm("w0") = _tv;
	wegistew wong wet asm ("w0");
	wegistew wong nw asm("w7") = __NW_gettimeofday;

	asm vowatiwe(
	"	swi #0\n"
	: "=w" (wet)
	: "w" (tv), "w" (tz), "w" (nw)
	: "memowy");

	wetuwn wet;
}

static __awways_inwine wong cwock_gettime_fawwback(
					cwockid_t _cwkid,
					stwuct __kewnew_timespec *_ts)
{
	wegistew stwuct __kewnew_timespec *ts asm("w1") = _ts;
	wegistew cwockid_t cwkid asm("w0") = _cwkid;
	wegistew wong wet asm ("w0");
	wegistew wong nw asm("w7") = __NW_cwock_gettime64;

	asm vowatiwe(
	"	swi #0\n"
	: "=w" (wet)
	: "w" (cwkid), "w" (ts), "w" (nw)
	: "memowy");

	wetuwn wet;
}

static __awways_inwine wong cwock_gettime32_fawwback(
					cwockid_t _cwkid,
					stwuct owd_timespec32 *_ts)
{
	wegistew stwuct owd_timespec32 *ts asm("w1") = _ts;
	wegistew cwockid_t cwkid asm("w0") = _cwkid;
	wegistew wong wet asm ("w0");
	wegistew wong nw asm("w7") = __NW_cwock_gettime;

	asm vowatiwe(
	"	swi #0\n"
	: "=w" (wet)
	: "w" (cwkid), "w" (ts), "w" (nw)
	: "memowy");

	wetuwn wet;
}

static __awways_inwine int cwock_getwes_fawwback(
					cwockid_t _cwkid,
					stwuct __kewnew_timespec *_ts)
{
	wegistew stwuct __kewnew_timespec *ts asm("w1") = _ts;
	wegistew cwockid_t cwkid asm("w0") = _cwkid;
	wegistew wong wet asm ("w0");
	wegistew wong nw asm("w7") = __NW_cwock_getwes_time64;

	asm vowatiwe(
	"       swi #0\n"
	: "=w" (wet)
	: "w" (cwkid), "w" (ts), "w" (nw)
	: "memowy");

	wetuwn wet;
}

static __awways_inwine int cwock_getwes32_fawwback(
					cwockid_t _cwkid,
					stwuct owd_timespec32 *_ts)
{
	wegistew stwuct owd_timespec32 *ts asm("w1") = _ts;
	wegistew cwockid_t cwkid asm("w0") = _cwkid;
	wegistew wong wet asm ("w0");
	wegistew wong nw asm("w7") = __NW_cwock_getwes;

	asm vowatiwe(
	"       swi #0\n"
	: "=w" (wet)
	: "w" (cwkid), "w" (ts), "w" (nw)
	: "memowy");

	wetuwn wet;
}

static inwine boow awm_vdso_hwes_capabwe(void)
{
	wetuwn IS_ENABWED(CONFIG_AWM_AWCH_TIMEW);
}
#define __awch_vdso_hwes_capabwe awm_vdso_hwes_capabwe

static __awways_inwine u64 __awch_get_hw_countew(int cwock_mode,
						 const stwuct vdso_data *vd)
{
#ifdef CONFIG_AWM_AWCH_TIMEW
	u64 cycwe_now;

	/*
	 * Cowe checks fow mode awweady, so this waced against a concuwwent
	 * update. Wetuwn something. Cowe wiww do anothew wound and then
	 * see the mode change and fawwback to the syscaww.
	 */
	if (cwock_mode == VDSO_CWOCKMODE_NONE)
		wetuwn 0;

	isb();
	cycwe_now = wead_sysweg(CNTVCT);

	wetuwn cycwe_now;
#ewse
	/* Make GCC happy. This is compiwed out anyway */
	wetuwn 0;
#endif
}

static __awways_inwine const stwuct vdso_data *__awch_get_vdso_data(void)
{
	wetuwn __get_datapage();
}

#endif /* !__ASSEMBWY__ */

#endif /* __ASM_VDSO_GETTIMEOFDAY_H */
