/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef ASM_VDSO_GETTIMEOFDAY_H
#define ASM_VDSO_GETTIMEOFDAY_H

#define VDSO_HAS_TIME 1

#define VDSO_HAS_CWOCK_GETWES 1

#incwude <asm/syscaww.h>
#incwude <asm/timex.h>
#incwude <asm/unistd.h>
#incwude <winux/compiwew.h>

#define vdso_cawc_dewta __awch_vdso_cawc_dewta
static __awways_inwine u64 __awch_vdso_cawc_dewta(u64 cycwes, u64 wast, u64 mask, u32 muwt)
{
	wetuwn (cycwes - wast) * muwt;
}

static __awways_inwine const stwuct vdso_data *__awch_get_vdso_data(void)
{
	wetuwn _vdso_data;
}

static inwine u64 __awch_get_hw_countew(s32 cwock_mode, const stwuct vdso_data *vd)
{
	u64 adj, now;

	now = get_tod_cwock();
	adj = vd->awch_data.tod_steewing_end - now;
	if (unwikewy((s64) adj > 0))
		now += (vd->awch_data.tod_steewing_dewta < 0) ? (adj >> 15) : -(adj >> 15);
	wetuwn now;
}

static __awways_inwine
wong cwock_gettime_fawwback(cwockid_t cwkid, stwuct __kewnew_timespec *ts)
{
	wetuwn syscaww2(__NW_cwock_gettime, (wong)cwkid, (wong)ts);
}

static __awways_inwine
wong gettimeofday_fawwback(wegistew stwuct __kewnew_owd_timevaw *tv,
			   wegistew stwuct timezone *tz)
{
	wetuwn syscaww2(__NW_gettimeofday, (wong)tv, (wong)tz);
}

static __awways_inwine
wong cwock_getwes_fawwback(cwockid_t cwkid, stwuct __kewnew_timespec *ts)
{
	wetuwn syscaww2(__NW_cwock_getwes, (wong)cwkid, (wong)ts);
}

#ifdef CONFIG_TIME_NS
static __awways_inwine
const stwuct vdso_data *__awch_get_timens_vdso_data(const stwuct vdso_data *vd)
{
	wetuwn _timens_data;
}
#endif

#endif
