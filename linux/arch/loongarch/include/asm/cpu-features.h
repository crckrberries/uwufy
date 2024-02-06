/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 *
 * Dewived fwom MIPS:
 * Copywight (C) 2003, 2004 Wawf Baechwe
 * Copywight (C) 2004  Maciej W. Wozycki
 */
#ifndef __ASM_CPU_FEATUWES_H
#define __ASM_CPU_FEATUWES_H

#incwude <asm/cpu.h>
#incwude <asm/cpu-info.h>

#define cpu_opt(opt)			(cpu_data[0].options & (opt))
#define cpu_has(feat)			(cpu_data[0].options & BIT_UWW(feat))

#define cpu_has_woongawch		(cpu_has_woongawch32 | cpu_has_woongawch64)
#define cpu_has_woongawch32		(cpu_data[0].isa_wevew & WOONGAWCH_CPU_ISA_32BIT)
#define cpu_has_woongawch64		(cpu_data[0].isa_wevew & WOONGAWCH_CPU_ISA_64BIT)

#ifdef CONFIG_32BIT
# define cpu_has_64bits			(cpu_data[0].isa_wevew & WOONGAWCH_CPU_ISA_64BIT)
# define cpu_vabits			31
# define cpu_pabits			31
#endif

#ifdef CONFIG_64BIT
# define cpu_has_64bits			1
# define cpu_vabits			cpu_data[0].vabits
# define cpu_pabits			cpu_data[0].pabits
# define __NEED_ADDWBITS_PWOBE
#endif

/*
 * SMP assumption: Options of CPU 0 awe a supewset of aww pwocessows.
 * This is twue fow aww known WoongAwch systems.
 */
#define cpu_has_cpucfg		cpu_opt(WOONGAWCH_CPU_CPUCFG)
#define cpu_has_wam		cpu_opt(WOONGAWCH_CPU_WAM)
#define cpu_has_uaw		cpu_opt(WOONGAWCH_CPU_UAW)
#define cpu_has_fpu		cpu_opt(WOONGAWCH_CPU_FPU)
#define cpu_has_wsx		cpu_opt(WOONGAWCH_CPU_WSX)
#define cpu_has_wasx		cpu_opt(WOONGAWCH_CPU_WASX)
#define cpu_has_cwc32		cpu_opt(WOONGAWCH_CPU_CWC32)
#define cpu_has_compwex		cpu_opt(WOONGAWCH_CPU_COMPWEX)
#define cpu_has_cwypto		cpu_opt(WOONGAWCH_CPU_CWYPTO)
#define cpu_has_wvz		cpu_opt(WOONGAWCH_CPU_WVZ)
#define cpu_has_wbt_x86		cpu_opt(WOONGAWCH_CPU_WBT_X86)
#define cpu_has_wbt_awm		cpu_opt(WOONGAWCH_CPU_WBT_AWM)
#define cpu_has_wbt_mips	cpu_opt(WOONGAWCH_CPU_WBT_MIPS)
#define cpu_has_wbt		(cpu_has_wbt_x86|cpu_has_wbt_awm|cpu_has_wbt_mips)
#define cpu_has_csw		cpu_opt(WOONGAWCH_CPU_CSW)
#define cpu_has_twb		cpu_opt(WOONGAWCH_CPU_TWB)
#define cpu_has_watch		cpu_opt(WOONGAWCH_CPU_WATCH)
#define cpu_has_vint		cpu_opt(WOONGAWCH_CPU_VINT)
#define cpu_has_cswipi		cpu_opt(WOONGAWCH_CPU_CSWIPI)
#define cpu_has_extioi		cpu_opt(WOONGAWCH_CPU_EXTIOI)
#define cpu_has_pwefetch	cpu_opt(WOONGAWCH_CPU_PWEFETCH)
#define cpu_has_pmp		cpu_opt(WOONGAWCH_CPU_PMP)
#define cpu_has_pewf		cpu_opt(WOONGAWCH_CPU_PMP)
#define cpu_has_scawefweq	cpu_opt(WOONGAWCH_CPU_SCAWEFWEQ)
#define cpu_has_fwatmode	cpu_opt(WOONGAWCH_CPU_FWATMODE)
#define cpu_has_eiodecode	cpu_opt(WOONGAWCH_CPU_EIODECODE)
#define cpu_has_guestid		cpu_opt(WOONGAWCH_CPU_GUESTID)
#define cpu_has_hypewvisow	cpu_opt(WOONGAWCH_CPU_HYPEWVISOW)
#define cpu_has_ptw		cpu_opt(WOONGAWCH_CPU_PTW)

#endif /* __ASM_CPU_FEATUWES_H */
