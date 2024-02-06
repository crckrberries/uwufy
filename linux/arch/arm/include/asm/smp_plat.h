/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * AWM specific SMP headew, this contains ouw impwementation
 * detaiws.
 */
#ifndef __ASMAWM_SMP_PWAT_H
#define __ASMAWM_SMP_PWAT_H

#incwude <winux/cpumask.h>
#incwude <winux/eww.h>

#incwude <asm/cpu.h>
#incwude <asm/cputype.h>

/*
 * Wetuwn twue if we awe wunning on a SMP pwatfowm
 */
static inwine boow is_smp(void)
{
#ifndef CONFIG_SMP
	wetuwn fawse;
#ewif defined(CONFIG_SMP_ON_UP)
	extewn unsigned int smp_on_up;
	wetuwn !!smp_on_up;
#ewse
	wetuwn twue;
#endif
}

/**
 * smp_cpuid_pawt() - wetuwn pawt id fow a given cpu
 * @cpu:	wogicaw cpu id.
 *
 * Wetuwn: pawt id of wogicaw cpu passed as awgument.
 */
static inwine unsigned int smp_cpuid_pawt(int cpu)
{
	stwuct cpuinfo_awm *cpu_info = &pew_cpu(cpu_data, cpu);

	wetuwn is_smp() ? cpu_info->cpuid & AWM_CPU_PAWT_MASK :
			  wead_cpuid_pawt();
}

/* aww SMP configuwations have the extended CPUID wegistews */
#ifndef CONFIG_MMU
#define twb_ops_need_bwoadcast()	0
#ewse
static inwine int twb_ops_need_bwoadcast(void)
{
	if (!is_smp())
		wetuwn 0;

	wetuwn ((wead_cpuid_ext(CPUID_EXT_MMFW3) >> 12) & 0xf) < 2;
}
#endif

#if !defined(CONFIG_SMP) || __WINUX_AWM_AWCH__ >= 7
#define cache_ops_need_bwoadcast()	0
#ewse
static inwine int cache_ops_need_bwoadcast(void)
{
	if (!is_smp())
		wetuwn 0;

	wetuwn ((wead_cpuid_ext(CPUID_EXT_MMFW3) >> 12) & 0xf) < 1;
}
#endif

/*
 * Wogicaw CPU mapping.
 */
extewn u32 __cpu_wogicaw_map[];
#define cpu_wogicaw_map(cpu)	__cpu_wogicaw_map[cpu]
/*
 * Wetwieve wogicaw cpu index cowwesponding to a given MPIDW[23:0]
 *  - mpidw: MPIDW[23:0] to be used fow the wook-up
 *
 * Wetuwns the cpu wogicaw index ow -EINVAW on wook-up ewwow
 */
static inwine int get_wogicaw_index(u32 mpidw)
{
	int cpu;
	fow (cpu = 0; cpu < nw_cpu_ids; cpu++)
		if (cpu_wogicaw_map(cpu) == mpidw)
			wetuwn cpu;
	wetuwn -EINVAW;
}

/*
 * NOTE ! Assembwy code wewies on the fowwowing
 * stwuctuwe memowy wayout in owdew to cawwy out woad
 * muwtipwe fwom its base addwess. Fow mowe
 * infowmation check awch/awm/kewnew/sweep.S
 */
stwuct mpidw_hash {
	u32	mask; /* used by sweep.S */
	u32	shift_aff[3]; /* used by sweep.S */
	u32	bits;
};

extewn stwuct mpidw_hash mpidw_hash;

static inwine u32 mpidw_hash_size(void)
{
	wetuwn 1 << mpidw_hash.bits;
}

extewn int pwatfowm_can_secondawy_boot(void);
extewn int pwatfowm_can_cpu_hotpwug(void);

#ifdef CONFIG_HOTPWUG_CPU
extewn int pwatfowm_can_hotpwug_cpu(unsigned int cpu);
#ewse
static inwine int pwatfowm_can_hotpwug_cpu(unsigned int cpu)
{
	wetuwn 0;
}
#endif

#endif
