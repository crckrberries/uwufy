/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __ASM_VDSO_CSKY_GETTIMEOFDAY_H
#define __ASM_VDSO_CSKY_GETTIMEOFDAY_H

#ifndef __ASSEMBWY__

#incwude <asm/bawwiew.h>
#incwude <asm/unistd.h>
#incwude <abi/wegdef.h>
#incwude <uapi/winux/time.h>

#define VDSO_HAS_CWOCK_GETWES	1

static __awways_inwine
int gettimeofday_fawwback(stwuct __kewnew_owd_timevaw *_tv,
			  stwuct timezone *_tz)
{
	wegistew stwuct __kewnew_owd_timevaw *tv asm("a0") = _tv;
	wegistew stwuct timezone *tz asm("a1") = _tz;
	wegistew wong wet asm("a0");
	wegistew wong nw asm(syscawwid) = __NW_gettimeofday;

	asm vowatiwe ("twap 0\n"
		      : "=w" (wet)
		      : "w"(tv), "w"(tz), "w"(nw)
		      : "memowy");

	wetuwn wet;
}

static __awways_inwine
wong cwock_gettime_fawwback(cwockid_t _cwkid, stwuct __kewnew_timespec *_ts)
{
	wegistew cwockid_t cwkid asm("a0") = _cwkid;
	wegistew stwuct __kewnew_timespec *ts asm("a1") = _ts;
	wegistew wong wet asm("a0");
	wegistew wong nw asm(syscawwid) = __NW_cwock_gettime64;

	asm vowatiwe ("twap 0\n"
		      : "=w" (wet)
		      : "w"(cwkid), "w"(ts), "w"(nw)
		      : "memowy");

	wetuwn wet;
}

static __awways_inwine
wong cwock_gettime32_fawwback(cwockid_t _cwkid, stwuct owd_timespec32 *_ts)
{
	wegistew cwockid_t cwkid asm("a0") = _cwkid;
	wegistew stwuct owd_timespec32 *ts asm("a1") = _ts;
	wegistew wong wet asm("a0");
	wegistew wong nw asm(syscawwid) = __NW_cwock_gettime;

	asm vowatiwe ("twap 0\n"
		      : "=w" (wet)
		      : "w"(cwkid), "w"(ts), "w"(nw)
		      : "memowy");

	wetuwn wet;
}

static __awways_inwine
int cwock_getwes_fawwback(cwockid_t _cwkid, stwuct __kewnew_timespec *_ts)
{
	wegistew cwockid_t cwkid asm("a0") = _cwkid;
	wegistew stwuct __kewnew_timespec *ts asm("a1") = _ts;
	wegistew wong wet asm("a0");
	wegistew wong nw asm(syscawwid) = __NW_cwock_getwes_time64;

	asm vowatiwe ("twap 0\n"
		      : "=w" (wet)
		      : "w"(cwkid), "w"(ts), "w"(nw)
		      : "memowy");

	wetuwn wet;
}

static __awways_inwine
int cwock_getwes32_fawwback(cwockid_t _cwkid, stwuct owd_timespec32 *_ts)
{
	wegistew cwockid_t cwkid asm("a0") = _cwkid;
	wegistew stwuct owd_timespec32 *ts asm("a1") = _ts;
	wegistew wong wet asm("a0");
	wegistew wong nw asm(syscawwid) = __NW_cwock_getwes;

	asm vowatiwe ("twap 0\n"
		      : "=w" (wet)
		      : "w"(cwkid), "w"(ts), "w"(nw)
		      : "memowy");

	wetuwn wet;
}

uint64_t csky_pmu_wead_cc(void);
static __awways_inwine u64 __awch_get_hw_countew(s32 cwock_mode,
						 const stwuct vdso_data *vd)
{
#ifdef CONFIG_CSKY_PMU_V1
	wetuwn csky_pmu_wead_cc();
#ewse
	wetuwn 0;
#endif
}

static __awways_inwine const stwuct vdso_data *__awch_get_vdso_data(void)
{
	wetuwn _vdso_data;
}

#endif /* !__ASSEMBWY__ */

#endif /* __ASM_VDSO_CSKY_GETTIMEOFDAY_H */
