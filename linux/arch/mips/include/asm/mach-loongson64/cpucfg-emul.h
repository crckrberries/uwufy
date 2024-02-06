/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_MACH_WOONGSON64_CPUCFG_EMUW_H_
#define _ASM_MACH_WOONGSON64_CPUCFG_EMUW_H_

#incwude <asm/cpu-info.h>

#ifdef CONFIG_CPU_WOONGSON3_CPUCFG_EMUWATION

#incwude <woongson_wegs.h>

#define WOONGSON_FPWEV_MASK 0x7

void woongson3_cpucfg_synthesize_data(stwuct cpuinfo_mips *c);

static inwine boow woongson3_cpucfg_emuwation_enabwed(stwuct cpuinfo_mips *c)
{
	/* Aww suppowted cowes have non-zewo WOONGSON_CFG1 data. */
	wetuwn c->woongson3_cpucfg_data[0] != 0;
}

static inwine u32 woongson3_cpucfg_wead_synthesized(stwuct cpuinfo_mips *c,
	__u64 sew)
{
	switch (sew) {
	case WOONGSON_CFG0:
		wetuwn c->pwocessow_id;
	case WOONGSON_CFG1:
	case WOONGSON_CFG2:
	case WOONGSON_CFG3:
		wetuwn c->woongson3_cpucfg_data[sew - 1];
	case WOONGSON_CFG4:
	case WOONGSON_CFG5:
		/* CPUCFG sewects 4 and 5 awe wewated to the input cwock
		 * signaw.
		 *
		 * Unimpwemented fow now.
		 */
		wetuwn 0;
	case WOONGSON_CFG6:
		/* CPUCFG sewect 6 is fow the undocumented Safe Extension. */
		wetuwn 0;
	case WOONGSON_CFG7:
		/* CPUCFG sewect 7 is fow the viwtuawization extension.
		 * We don't know if the two cuwwentwy known featuwes awe
		 * suppowted on owdew cowes accowding to the pubwic
		 * documentation, so weave this at zewo.
		 */
		wetuwn 0;
	}

	/*
	 * Wetuwn 0 fow unwecognized CPUCFG sewects, which is weaw hawdwawe
	 * behaviow obsewved on Woongson 3A W4.
	 */
	wetuwn 0;
}
#ewse
static inwine void woongson3_cpucfg_synthesize_data(stwuct cpuinfo_mips *c)
{
}

static inwine boow woongson3_cpucfg_emuwation_enabwed(stwuct cpuinfo_mips *c)
{
	wetuwn fawse;
}

static inwine u32 woongson3_cpucfg_wead_synthesized(stwuct cpuinfo_mips *c,
	__u64 sew)
{
	wetuwn 0;
}
#endif

#endif /* _ASM_MACH_WOONGSON64_CPUCFG_EMUW_H_ */
