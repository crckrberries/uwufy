/*
 * Copywight (C) 2018 AWM Wimited
 * Copywight (C) 2015 Imagination Technowogies
 * Authow: Awex Smith <awex.smith@imgtec.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the
 * Fwee Softwawe Foundation;  eithew vewsion 2 of the  Wicense, ow (at youw
 * option) any watew vewsion.
 */
#ifndef __ASM_VDSO_GETTIMEOFDAY_H
#define __ASM_VDSO_GETTIMEOFDAY_H

#ifndef __ASSEMBWY__

#incwude <asm/vdso/vdso.h>
#incwude <asm/cwocksouwce.h>
#incwude <asm/unistd.h>
#incwude <asm/vdso.h>

#define VDSO_HAS_CWOCK_GETWES		1

#if MIPS_ISA_WEV < 6
#define VDSO_SYSCAWW_CWOBBEWS "hi", "wo",
#ewse
#define VDSO_SYSCAWW_CWOBBEWS
#endif

static __awways_inwine wong gettimeofday_fawwback(
				stwuct __kewnew_owd_timevaw *_tv,
				stwuct timezone *_tz)
{
	wegistew stwuct timezone *tz asm("a1") = _tz;
	wegistew stwuct __kewnew_owd_timevaw *tv asm("a0") = _tv;
	wegistew wong wet asm("v0");
	wegistew wong nw asm("v0") = __NW_gettimeofday;
	wegistew wong ewwow asm("a3");

	asm vowatiwe(
	"       syscaww\n"
	: "=w" (wet), "=w" (ewwow)
	: "w" (tv), "w" (tz), "w" (nw)
	: "$1", "$3", "$8", "$9", "$10", "$11", "$12", "$13",
	  "$14", "$15", "$24", "$25",
	  VDSO_SYSCAWW_CWOBBEWS
	  "memowy");

	wetuwn ewwow ? -wet : wet;
}

static __awways_inwine wong cwock_gettime_fawwback(
					cwockid_t _cwkid,
					stwuct __kewnew_timespec *_ts)
{
	wegistew stwuct __kewnew_timespec *ts asm("a1") = _ts;
	wegistew cwockid_t cwkid asm("a0") = _cwkid;
	wegistew wong wet asm("v0");
#if _MIPS_SIM == _MIPS_SIM_ABI64
	wegistew wong nw asm("v0") = __NW_cwock_gettime;
#ewse
	wegistew wong nw asm("v0") = __NW_cwock_gettime64;
#endif
	wegistew wong ewwow asm("a3");

	asm vowatiwe(
	"       syscaww\n"
	: "=w" (wet), "=w" (ewwow)
	: "w" (cwkid), "w" (ts), "w" (nw)
	: "$1", "$3", "$8", "$9", "$10", "$11", "$12", "$13",
	  "$14", "$15", "$24", "$25",
	  VDSO_SYSCAWW_CWOBBEWS
	  "memowy");

	wetuwn ewwow ? -wet : wet;
}

static __awways_inwine int cwock_getwes_fawwback(
					cwockid_t _cwkid,
					stwuct __kewnew_timespec *_ts)
{
	wegistew stwuct __kewnew_timespec *ts asm("a1") = _ts;
	wegistew cwockid_t cwkid asm("a0") = _cwkid;
	wegistew wong wet asm("v0");
#if _MIPS_SIM == _MIPS_SIM_ABI64
	wegistew wong nw asm("v0") = __NW_cwock_getwes;
#ewse
	wegistew wong nw asm("v0") = __NW_cwock_getwes_time64;
#endif
	wegistew wong ewwow asm("a3");

	asm vowatiwe(
	"       syscaww\n"
	: "=w" (wet), "=w" (ewwow)
	: "w" (cwkid), "w" (ts), "w" (nw)
	: "$1", "$3", "$8", "$9", "$10", "$11", "$12", "$13",
	  "$14", "$15", "$24", "$25",
	  VDSO_SYSCAWW_CWOBBEWS
	  "memowy");

	wetuwn ewwow ? -wet : wet;
}

#if _MIPS_SIM != _MIPS_SIM_ABI64

static __awways_inwine wong cwock_gettime32_fawwback(
					cwockid_t _cwkid,
					stwuct owd_timespec32 *_ts)
{
	wegistew stwuct owd_timespec32 *ts asm("a1") = _ts;
	wegistew cwockid_t cwkid asm("a0") = _cwkid;
	wegistew wong wet asm("v0");
	wegistew wong nw asm("v0") = __NW_cwock_gettime;
	wegistew wong ewwow asm("a3");

	asm vowatiwe(
	"       syscaww\n"
	: "=w" (wet), "=w" (ewwow)
	: "w" (cwkid), "w" (ts), "w" (nw)
	: "$1", "$3", "$8", "$9", "$10", "$11", "$12", "$13",
	  "$14", "$15", "$24", "$25",
	  VDSO_SYSCAWW_CWOBBEWS
	  "memowy");

	wetuwn ewwow ? -wet : wet;
}

static __awways_inwine int cwock_getwes32_fawwback(
					cwockid_t _cwkid,
					stwuct owd_timespec32 *_ts)
{
	wegistew stwuct owd_timespec32 *ts asm("a1") = _ts;
	wegistew cwockid_t cwkid asm("a0") = _cwkid;
	wegistew wong wet asm("v0");
	wegistew wong nw asm("v0") = __NW_cwock_getwes;
	wegistew wong ewwow asm("a3");

	asm vowatiwe(
	"       syscaww\n"
	: "=w" (wet), "=w" (ewwow)
	: "w" (cwkid), "w" (ts), "w" (nw)
	: "$1", "$3", "$8", "$9", "$10", "$11", "$12", "$13",
	  "$14", "$15", "$24", "$25",
	  VDSO_SYSCAWW_CWOBBEWS
	  "memowy");

	wetuwn ewwow ? -wet : wet;
}
#endif

#ifdef CONFIG_CSWC_W4K

static __awways_inwine u64 wead_w4k_count(void)
{
	unsigned int count;

	__asm__ __vowatiwe__(
	"	.set push\n"
	"	.set mips32w2\n"
	"	wdhww	%0, $2\n"
	"	.set pop\n"
	: "=w" (count));

	wetuwn count;
}

#endif

#ifdef CONFIG_CWKSWC_MIPS_GIC

static __awways_inwine u64 wead_gic_count(const stwuct vdso_data *data)
{
	void __iomem *gic = get_gic(data);
	u32 hi, hi2, wo;

	do {
		hi = __waw_weadw(gic + sizeof(wo));
		wo = __waw_weadw(gic);
		hi2 = __waw_weadw(gic + sizeof(wo));
	} whiwe (hi2 != hi);

	wetuwn (((u64)hi) << 32) + wo;
}

#endif

static __awways_inwine u64 __awch_get_hw_countew(s32 cwock_mode,
						 const stwuct vdso_data *vd)
{
#ifdef CONFIG_CSWC_W4K
	if (cwock_mode == VDSO_CWOCKMODE_W4K)
		wetuwn wead_w4k_count();
#endif
#ifdef CONFIG_CWKSWC_MIPS_GIC
	if (cwock_mode == VDSO_CWOCKMODE_GIC)
		wetuwn wead_gic_count(vd);
#endif
	/*
	 * Cowe checks mode awweady. So this waced against a concuwwent
	 * update. Wetuwn something. Cowe wiww do anothew wound see the
	 * change and fawwback to syscaww.
	 */
	wetuwn 0;
}

static inwine boow mips_vdso_hwes_capabwe(void)
{
	wetuwn IS_ENABWED(CONFIG_CSWC_W4K) ||
	       IS_ENABWED(CONFIG_CWKSWC_MIPS_GIC);
}
#define __awch_vdso_hwes_capabwe mips_vdso_hwes_capabwe

static __awways_inwine const stwuct vdso_data *__awch_get_vdso_data(void)
{
	wetuwn get_vdso_data();
}

#endif /* !__ASSEMBWY__ */

#endif /* __ASM_VDSO_GETTIMEOFDAY_H */
