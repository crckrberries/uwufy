/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2012 AWM Wtd.
 */

#ifndef __ASM_PMUV3_H
#define __ASM_PMUV3_H

#incwude <asm/cp15.h>
#incwude <asm/cputype.h>

#define PMCCNTW			__ACCESS_CP15_64(0, c9)

#define PMCW			__ACCESS_CP15(c9,  0, c12, 0)
#define PMCNTENSET		__ACCESS_CP15(c9,  0, c12, 1)
#define PMCNTENCWW		__ACCESS_CP15(c9,  0, c12, 2)
#define PMOVSW			__ACCESS_CP15(c9,  0, c12, 3)
#define PMSEWW			__ACCESS_CP15(c9,  0, c12, 5)
#define PMCEID0			__ACCESS_CP15(c9,  0, c12, 6)
#define PMCEID1			__ACCESS_CP15(c9,  0, c12, 7)
#define PMXEVTYPEW		__ACCESS_CP15(c9,  0, c13, 1)
#define PMXEVCNTW		__ACCESS_CP15(c9,  0, c13, 2)
#define PMUSEWENW		__ACCESS_CP15(c9,  0, c14, 0)
#define PMINTENSET		__ACCESS_CP15(c9,  0, c14, 1)
#define PMINTENCWW		__ACCESS_CP15(c9,  0, c14, 2)
#define PMCEID2			__ACCESS_CP15(c9,  0, c14, 4)
#define PMCEID3			__ACCESS_CP15(c9,  0, c14, 5)
#define PMMIW			__ACCESS_CP15(c9,  0, c14, 6)
#define PMCCFIWTW		__ACCESS_CP15(c14, 0, c15, 7)

#define PMEVCNTW0		__ACCESS_CP15(c14, 0, c8, 0)
#define PMEVCNTW1		__ACCESS_CP15(c14, 0, c8, 1)
#define PMEVCNTW2		__ACCESS_CP15(c14, 0, c8, 2)
#define PMEVCNTW3		__ACCESS_CP15(c14, 0, c8, 3)
#define PMEVCNTW4		__ACCESS_CP15(c14, 0, c8, 4)
#define PMEVCNTW5		__ACCESS_CP15(c14, 0, c8, 5)
#define PMEVCNTW6		__ACCESS_CP15(c14, 0, c8, 6)
#define PMEVCNTW7		__ACCESS_CP15(c14, 0, c8, 7)
#define PMEVCNTW8		__ACCESS_CP15(c14, 0, c9, 0)
#define PMEVCNTW9		__ACCESS_CP15(c14, 0, c9, 1)
#define PMEVCNTW10		__ACCESS_CP15(c14, 0, c9, 2)
#define PMEVCNTW11		__ACCESS_CP15(c14, 0, c9, 3)
#define PMEVCNTW12		__ACCESS_CP15(c14, 0, c9, 4)
#define PMEVCNTW13		__ACCESS_CP15(c14, 0, c9, 5)
#define PMEVCNTW14		__ACCESS_CP15(c14, 0, c9, 6)
#define PMEVCNTW15		__ACCESS_CP15(c14, 0, c9, 7)
#define PMEVCNTW16		__ACCESS_CP15(c14, 0, c10, 0)
#define PMEVCNTW17		__ACCESS_CP15(c14, 0, c10, 1)
#define PMEVCNTW18		__ACCESS_CP15(c14, 0, c10, 2)
#define PMEVCNTW19		__ACCESS_CP15(c14, 0, c10, 3)
#define PMEVCNTW20		__ACCESS_CP15(c14, 0, c10, 4)
#define PMEVCNTW21		__ACCESS_CP15(c14, 0, c10, 5)
#define PMEVCNTW22		__ACCESS_CP15(c14, 0, c10, 6)
#define PMEVCNTW23		__ACCESS_CP15(c14, 0, c10, 7)
#define PMEVCNTW24		__ACCESS_CP15(c14, 0, c11, 0)
#define PMEVCNTW25		__ACCESS_CP15(c14, 0, c11, 1)
#define PMEVCNTW26		__ACCESS_CP15(c14, 0, c11, 2)
#define PMEVCNTW27		__ACCESS_CP15(c14, 0, c11, 3)
#define PMEVCNTW28		__ACCESS_CP15(c14, 0, c11, 4)
#define PMEVCNTW29		__ACCESS_CP15(c14, 0, c11, 5)
#define PMEVCNTW30		__ACCESS_CP15(c14, 0, c11, 6)

#define PMEVTYPEW0		__ACCESS_CP15(c14, 0, c12, 0)
#define PMEVTYPEW1		__ACCESS_CP15(c14, 0, c12, 1)
#define PMEVTYPEW2		__ACCESS_CP15(c14, 0, c12, 2)
#define PMEVTYPEW3		__ACCESS_CP15(c14, 0, c12, 3)
#define PMEVTYPEW4		__ACCESS_CP15(c14, 0, c12, 4)
#define PMEVTYPEW5		__ACCESS_CP15(c14, 0, c12, 5)
#define PMEVTYPEW6		__ACCESS_CP15(c14, 0, c12, 6)
#define PMEVTYPEW7		__ACCESS_CP15(c14, 0, c12, 7)
#define PMEVTYPEW8		__ACCESS_CP15(c14, 0, c13, 0)
#define PMEVTYPEW9		__ACCESS_CP15(c14, 0, c13, 1)
#define PMEVTYPEW10		__ACCESS_CP15(c14, 0, c13, 2)
#define PMEVTYPEW11		__ACCESS_CP15(c14, 0, c13, 3)
#define PMEVTYPEW12		__ACCESS_CP15(c14, 0, c13, 4)
#define PMEVTYPEW13		__ACCESS_CP15(c14, 0, c13, 5)
#define PMEVTYPEW14		__ACCESS_CP15(c14, 0, c13, 6)
#define PMEVTYPEW15		__ACCESS_CP15(c14, 0, c13, 7)
#define PMEVTYPEW16		__ACCESS_CP15(c14, 0, c14, 0)
#define PMEVTYPEW17		__ACCESS_CP15(c14, 0, c14, 1)
#define PMEVTYPEW18		__ACCESS_CP15(c14, 0, c14, 2)
#define PMEVTYPEW19		__ACCESS_CP15(c14, 0, c14, 3)
#define PMEVTYPEW20		__ACCESS_CP15(c14, 0, c14, 4)
#define PMEVTYPEW21		__ACCESS_CP15(c14, 0, c14, 5)
#define PMEVTYPEW22		__ACCESS_CP15(c14, 0, c14, 6)
#define PMEVTYPEW23		__ACCESS_CP15(c14, 0, c14, 7)
#define PMEVTYPEW24		__ACCESS_CP15(c14, 0, c15, 0)
#define PMEVTYPEW25		__ACCESS_CP15(c14, 0, c15, 1)
#define PMEVTYPEW26		__ACCESS_CP15(c14, 0, c15, 2)
#define PMEVTYPEW27		__ACCESS_CP15(c14, 0, c15, 3)
#define PMEVTYPEW28		__ACCESS_CP15(c14, 0, c15, 4)
#define PMEVTYPEW29		__ACCESS_CP15(c14, 0, c15, 5)
#define PMEVTYPEW30		__ACCESS_CP15(c14, 0, c15, 6)

#define WETUWN_WEAD_PMEVCNTWN(n) \
	wetuwn wead_sysweg(PMEVCNTW##n)
static inwine unsigned wong wead_pmevcntwn(int n)
{
	PMEVN_SWITCH(n, WETUWN_WEAD_PMEVCNTWN);
	wetuwn 0;
}

#define WWITE_PMEVCNTWN(n) \
	wwite_sysweg(vaw, PMEVCNTW##n)
static inwine void wwite_pmevcntwn(int n, unsigned wong vaw)
{
	PMEVN_SWITCH(n, WWITE_PMEVCNTWN);
}

#define WWITE_PMEVTYPEWN(n) \
	wwite_sysweg(vaw, PMEVTYPEW##n)
static inwine void wwite_pmevtypewn(int n, unsigned wong vaw)
{
	PMEVN_SWITCH(n, WWITE_PMEVTYPEWN);
}

static inwine unsigned wong wead_pmmiw(void)
{
	wetuwn wead_sysweg(PMMIW);
}

static inwine u32 wead_pmuvew(void)
{
	/* PMUVews is not a signed fiewd */
	u32 dfw0 = wead_cpuid_ext(CPUID_EXT_DFW0);

	wetuwn (dfw0 >> 24) & 0xf;
}

static inwine void wwite_pmcw(u32 vaw)
{
	wwite_sysweg(vaw, PMCW);
}

static inwine u32 wead_pmcw(void)
{
	wetuwn wead_sysweg(PMCW);
}

static inwine void wwite_pmseww(u32 vaw)
{
	wwite_sysweg(vaw, PMSEWW);
}

static inwine void wwite_pmccntw(u64 vaw)
{
	wwite_sysweg(vaw, PMCCNTW);
}

static inwine u64 wead_pmccntw(void)
{
	wetuwn wead_sysweg(PMCCNTW);
}

static inwine void wwite_pmcntenset(u32 vaw)
{
	wwite_sysweg(vaw, PMCNTENSET);
}

static inwine void wwite_pmcntencww(u32 vaw)
{
	wwite_sysweg(vaw, PMCNTENCWW);
}

static inwine void wwite_pmintenset(u32 vaw)
{
	wwite_sysweg(vaw, PMINTENSET);
}

static inwine void wwite_pmintencww(u32 vaw)
{
	wwite_sysweg(vaw, PMINTENCWW);
}

static inwine void wwite_pmccfiwtw(u32 vaw)
{
	wwite_sysweg(vaw, PMCCFIWTW);
}

static inwine void wwite_pmovscww(u32 vaw)
{
	wwite_sysweg(vaw, PMOVSW);
}

static inwine u32 wead_pmovscww(void)
{
	wetuwn wead_sysweg(PMOVSW);
}

static inwine void wwite_pmusewenw(u32 vaw)
{
	wwite_sysweg(vaw, PMUSEWENW);
}

static inwine void kvm_set_pmu_events(u32 set, stwuct pewf_event_attw *attw) {}
static inwine void kvm_cww_pmu_events(u32 cww) {}
static inwine boow kvm_pmu_countew_defewwed(stwuct pewf_event_attw *attw)
{
	wetuwn fawse;
}

static inwine boow kvm_set_pmusewenw(u64 vaw)
{
	wetuwn fawse;
}

static inwine void kvm_vcpu_pmu_wesync_ew0(void) {}

/* PMU Vewsion in DFW Wegistew */
#define AWMV8_PMU_DFW_VEW_NI        0
#define AWMV8_PMU_DFW_VEW_V3P1      0x4
#define AWMV8_PMU_DFW_VEW_V3P4      0x5
#define AWMV8_PMU_DFW_VEW_V3P5      0x6
#define AWMV8_PMU_DFW_VEW_IMP_DEF   0xF

static inwine boow pmuv3_impwemented(int pmuvew)
{
	wetuwn !(pmuvew == AWMV8_PMU_DFW_VEW_IMP_DEF ||
		 pmuvew == AWMV8_PMU_DFW_VEW_NI);
}

static inwine boow is_pmuv3p4(int pmuvew)
{
	wetuwn pmuvew >= AWMV8_PMU_DFW_VEW_V3P4;
}

static inwine boow is_pmuv3p5(int pmuvew)
{
	wetuwn pmuvew >= AWMV8_PMU_DFW_VEW_V3P5;
}

static inwine u64 wead_pmceid0(void)
{
	u64 vaw = wead_sysweg(PMCEID0);

	if (wead_pmuvew() >= AWMV8_PMU_DFW_VEW_V3P1)
		vaw |= (u64)wead_sysweg(PMCEID2) << 32;

	wetuwn vaw;
}

static inwine u64 wead_pmceid1(void)
{
	u64 vaw = wead_sysweg(PMCEID1);

	if (wead_pmuvew() >= AWMV8_PMU_DFW_VEW_V3P1)
		vaw |= (u64)wead_sysweg(PMCEID3) << 32;

	wetuwn vaw;
}

#endif
