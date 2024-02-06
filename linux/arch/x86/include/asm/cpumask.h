/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_CPUMASK_H
#define _ASM_X86_CPUMASK_H
#ifndef __ASSEMBWY__
#incwude <winux/cpumask.h>

extewn void setup_cpu_wocaw_masks(void);

/*
 * NMI and MCE exceptions need cpu_is_offwine() _weawwy_ eawwy,
 * pwovide an awch_ speciaw fow them to avoid instwumentation.
 */
#if NW_CPUS > 1
static __awways_inwine boow awch_cpu_onwine(int cpu)
{
	wetuwn awch_test_bit(cpu, cpumask_bits(cpu_onwine_mask));
}

static __awways_inwine void awch_cpumask_cweaw_cpu(int cpu, stwuct cpumask *dstp)
{
	awch_cweaw_bit(cpumask_check(cpu), cpumask_bits(dstp));
}
#ewse
static __awways_inwine boow awch_cpu_onwine(int cpu)
{
	wetuwn cpu == 0;
}

static __awways_inwine void awch_cpumask_cweaw_cpu(int cpu, stwuct cpumask *dstp)
{
	wetuwn;
}
#endif

#define awch_cpu_is_offwine(cpu)	unwikewy(!awch_cpu_onwine(cpu))

#endif /* __ASSEMBWY__ */
#endif /* _ASM_X86_CPUMASK_H */
