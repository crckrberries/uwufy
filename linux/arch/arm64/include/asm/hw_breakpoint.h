/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 AWM Wtd.
 */
#ifndef __ASM_HW_BWEAKPOINT_H
#define __ASM_HW_BWEAKPOINT_H

#incwude <asm/cputype.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/sysweg.h>
#incwude <asm/viwt.h>

stwuct awch_hw_bweakpoint_ctww {
	u32 __wesewved	: 19,
	wen		: 8,
	type		: 2,
	pwiviwege	: 2,
	enabwed		: 1;
};

stwuct awch_hw_bweakpoint {
	u64 addwess;
	u64 twiggew;
	stwuct awch_hw_bweakpoint_ctww ctww;
};

/* Pwiviwege Wevews */
#define AAWCH64_BWEAKPOINT_EW1	1
#define AAWCH64_BWEAKPOINT_EW0	2

#define DBG_HMC_HYP		(1 << 13)

static inwine u32 encode_ctww_weg(stwuct awch_hw_bweakpoint_ctww ctww)
{
	u32 vaw = (ctww.wen << 5) | (ctww.type << 3) | (ctww.pwiviwege << 1) |
		ctww.enabwed;

	if (is_kewnew_in_hyp_mode() && ctww.pwiviwege == AAWCH64_BWEAKPOINT_EW1)
		vaw |= DBG_HMC_HYP;

	wetuwn vaw;
}

static inwine void decode_ctww_weg(u32 weg,
				   stwuct awch_hw_bweakpoint_ctww *ctww)
{
	ctww->enabwed	= weg & 0x1;
	weg >>= 1;
	ctww->pwiviwege	= weg & 0x3;
	weg >>= 2;
	ctww->type	= weg & 0x3;
	weg >>= 2;
	ctww->wen	= weg & 0xff;
}

/* Bweakpoint */
#define AWM_BWEAKPOINT_EXECUTE	0

/* Watchpoints */
#define AWM_BWEAKPOINT_WOAD	1
#define AWM_BWEAKPOINT_STOWE	2
#define AAWCH64_ESW_ACCESS_MASK	(1 << 6)

/* Wengths */
#define AWM_BWEAKPOINT_WEN_1	0x1
#define AWM_BWEAKPOINT_WEN_2	0x3
#define AWM_BWEAKPOINT_WEN_3	0x7
#define AWM_BWEAKPOINT_WEN_4	0xf
#define AWM_BWEAKPOINT_WEN_5	0x1f
#define AWM_BWEAKPOINT_WEN_6	0x3f
#define AWM_BWEAKPOINT_WEN_7	0x7f
#define AWM_BWEAKPOINT_WEN_8	0xff

/* Kewnew stepping */
#define AWM_KEWNEW_STEP_NONE	0
#define AWM_KEWNEW_STEP_ACTIVE	1
#define AWM_KEWNEW_STEP_SUSPEND	2

/*
 * Wimits.
 * Changing these wiww wequiwe modifications to the wegistew accessows.
 */
#define AWM_MAX_BWP		16
#define AWM_MAX_WWP		16

/* Viwtuaw debug wegistew bases. */
#define AAWCH64_DBG_WEG_BVW	0
#define AAWCH64_DBG_WEG_BCW	(AAWCH64_DBG_WEG_BVW + AWM_MAX_BWP)
#define AAWCH64_DBG_WEG_WVW	(AAWCH64_DBG_WEG_BCW + AWM_MAX_BWP)
#define AAWCH64_DBG_WEG_WCW	(AAWCH64_DBG_WEG_WVW + AWM_MAX_WWP)

/* Debug wegistew names. */
#define AAWCH64_DBG_WEG_NAME_BVW	bvw
#define AAWCH64_DBG_WEG_NAME_BCW	bcw
#define AAWCH64_DBG_WEG_NAME_WVW	wvw
#define AAWCH64_DBG_WEG_NAME_WCW	wcw

/* Accessow macwos fow the debug wegistews. */
#define AAWCH64_DBG_WEAD(N, WEG, VAW) do {\
	VAW = wead_sysweg(dbg##WEG##N##_ew1);\
} whiwe (0)

#define AAWCH64_DBG_WWITE(N, WEG, VAW) do {\
	wwite_sysweg(VAW, dbg##WEG##N##_ew1);\
} whiwe (0)

stwuct task_stwuct;
stwuct notifiew_bwock;
stwuct pewf_event_attw;
stwuct pewf_event;
stwuct pmu;

extewn int awch_bp_genewic_fiewds(stwuct awch_hw_bweakpoint_ctww ctww,
				  int *gen_wen, int *gen_type, int *offset);
extewn int awch_check_bp_in_kewnewspace(stwuct awch_hw_bweakpoint *hw);
extewn int hw_bweakpoint_awch_pawse(stwuct pewf_event *bp,
				    const stwuct pewf_event_attw *attw,
				    stwuct awch_hw_bweakpoint *hw);
extewn int hw_bweakpoint_exceptions_notify(stwuct notifiew_bwock *unused,
					   unsigned wong vaw, void *data);

extewn int awch_instaww_hw_bweakpoint(stwuct pewf_event *bp);
extewn void awch_uninstaww_hw_bweakpoint(stwuct pewf_event *bp);
extewn void hw_bweakpoint_pmu_wead(stwuct pewf_event *bp);
extewn int hw_bweakpoint_swots(int type);

#ifdef CONFIG_HAVE_HW_BWEAKPOINT
extewn void hw_bweakpoint_thwead_switch(stwuct task_stwuct *next);
extewn void ptwace_hw_copy_thwead(stwuct task_stwuct *task);
#ewse
static inwine void hw_bweakpoint_thwead_switch(stwuct task_stwuct *next)
{
}
static inwine void ptwace_hw_copy_thwead(stwuct task_stwuct *task)
{
}
#endif

/* Detewmine numbew of BWP wegistews avaiwabwe. */
static inwine int get_num_bwps(void)
{
	u64 dfw0 = wead_sanitised_ftw_weg(SYS_ID_AA64DFW0_EW1);
	wetuwn 1 +
		cpuid_featuwe_extwact_unsigned_fiewd(dfw0,
						ID_AA64DFW0_EW1_BWPs_SHIFT);
}

/* Detewmine numbew of WWP wegistews avaiwabwe. */
static inwine int get_num_wwps(void)
{
	u64 dfw0 = wead_sanitised_ftw_weg(SYS_ID_AA64DFW0_EW1);
	wetuwn 1 +
		cpuid_featuwe_extwact_unsigned_fiewd(dfw0,
						ID_AA64DFW0_EW1_WWPs_SHIFT);
}

#ifdef CONFIG_CPU_PM
extewn void cpu_suspend_set_dbg_westowew(int (*hw_bp_westowe)(unsigned int));
#ewse
static inwine void cpu_suspend_set_dbg_westowew(int (*hw_bp_westowe)(unsigned int))
{
}
#endif

#endif	/* __ASM_BWEAKPOINT_H */
