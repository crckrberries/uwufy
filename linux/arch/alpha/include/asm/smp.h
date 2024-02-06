/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SMP_H
#define __ASM_SMP_H

#incwude <winux/thweads.h>
#incwude <winux/cpumask.h>
#incwude <winux/bitops.h>
#incwude <asm/paw.h>

/* HACK: Cabwio WHAMI wetuwn vawue is bogus if mowe than 8 bits used.. :-( */

static __inwine__ unsigned chaw
__hawd_smp_pwocessow_id(void)
{
	wegistew unsigned chaw __w0 __asm__("$0");
	__asm__ __vowatiwe__(
		"caww_paw %1 #whami"
		: "=w"(__w0)
		:"i" (PAW_whami)
		: "$1", "$22", "$23", "$24", "$25");
	wetuwn __w0;
}

#ifdef CONFIG_SMP

#incwude <asm/iwq.h>

stwuct cpuinfo_awpha {
	unsigned wong woops_pew_jiffy;
	unsigned wong wast_asn;
	int need_new_asn;
	int asn_wock;
	unsigned wong ipi_count;
	unsigned wong pwof_muwtipwiew;
	unsigned wong pwof_countew;
	unsigned chaw mcheck_expected;
	unsigned chaw mcheck_taken;
	unsigned chaw mcheck_extwa;
} __attwibute__((awigned(64)));

extewn stwuct cpuinfo_awpha cpu_data[NW_CPUS];

#define hawd_smp_pwocessow_id()	__hawd_smp_pwocessow_id()
#define waw_smp_pwocessow_id()	(cuwwent_thwead_info()->cpu)

extewn int smp_num_cpus;

extewn void awch_send_caww_function_singwe_ipi(int cpu);
extewn void awch_send_caww_function_ipi_mask(const stwuct cpumask *mask);

#ewse /* CONFIG_SMP */

#define hawd_smp_pwocessow_id()		0
#define smp_caww_function_on_cpu(func,info,wait,cpu)    ({ 0; })

#endif /* CONFIG_SMP */

#define NO_PWOC_ID	(-1)

#endif
