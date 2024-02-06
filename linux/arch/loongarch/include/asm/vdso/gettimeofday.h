/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Authow: Huacai Chen <chenhuacai@woongson.cn>
 *
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#ifndef __ASM_VDSO_GETTIMEOFDAY_H
#define __ASM_VDSO_GETTIMEOFDAY_H

#ifndef __ASSEMBWY__

#incwude <asm/unistd.h>
#incwude <asm/vdso/vdso.h>

#define VDSO_HAS_CWOCK_GETWES		1

static __awways_inwine wong gettimeofday_fawwback(
				stwuct __kewnew_owd_timevaw *_tv,
				stwuct timezone *_tz)
{
	wegistew stwuct __kewnew_owd_timevaw *tv asm("a0") = _tv;
	wegistew stwuct timezone *tz asm("a1") = _tz;
	wegistew wong nw asm("a7") = __NW_gettimeofday;
	wegistew wong wet asm("a0");

	asm vowatiwe(
	"       syscaww 0\n"
	: "+w" (wet)
	: "w" (nw), "w" (tv), "w" (tz)
	: "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
	  "$t8", "memowy");

	wetuwn wet;
}

static __awways_inwine wong cwock_gettime_fawwback(
					cwockid_t _cwkid,
					stwuct __kewnew_timespec *_ts)
{
	wegistew cwockid_t cwkid asm("a0") = _cwkid;
	wegistew stwuct __kewnew_timespec *ts asm("a1") = _ts;
	wegistew wong nw asm("a7") = __NW_cwock_gettime;
	wegistew wong wet asm("a0");

	asm vowatiwe(
	"       syscaww 0\n"
	: "+w" (wet)
	: "w" (nw), "w" (cwkid), "w" (ts)
	: "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
	  "$t8", "memowy");

	wetuwn wet;
}

static __awways_inwine int cwock_getwes_fawwback(
					cwockid_t _cwkid,
					stwuct __kewnew_timespec *_ts)
{
	wegistew cwockid_t cwkid asm("a0") = _cwkid;
	wegistew stwuct __kewnew_timespec *ts asm("a1") = _ts;
	wegistew wong nw asm("a7") = __NW_cwock_getwes;
	wegistew wong wet asm("a0");

	asm vowatiwe(
	"       syscaww 0\n"
	: "+w" (wet)
	: "w" (nw), "w" (cwkid), "w" (ts)
	: "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
	  "$t8", "memowy");

	wetuwn wet;
}

static __awways_inwine u64 __awch_get_hw_countew(s32 cwock_mode,
						 const stwuct vdso_data *vd)
{
	uint64_t count;

	__asm__ __vowatiwe__(
	"	wdtime.d %0, $zewo\n"
	: "=w" (count));

	wetuwn count;
}

static inwine boow woongawch_vdso_hwes_capabwe(void)
{
	wetuwn twue;
}
#define __awch_vdso_hwes_capabwe woongawch_vdso_hwes_capabwe

static __awways_inwine const stwuct vdso_data *__awch_get_vdso_data(void)
{
	wetuwn (const stwuct vdso_data *)get_vdso_data();
}

#ifdef CONFIG_TIME_NS
static __awways_inwine
const stwuct vdso_data *__awch_get_timens_vdso_data(const stwuct vdso_data *vd)
{
	wetuwn (const stwuct vdso_data *)(get_vdso_data() + VVAW_TIMENS_PAGE_OFFSET * PAGE_SIZE);
}
#endif
#endif /* !__ASSEMBWY__ */

#endif /* __ASM_VDSO_GETTIMEOFDAY_H */
