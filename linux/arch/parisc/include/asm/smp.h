/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SMP_H
#define __ASM_SMP_H

extewn int init_pew_cpu(int cpuid);

#if defined(CONFIG_SMP)

/* Page Zewo Wocation PDC wiww wook fow the addwess to bwanch to when we poke
** swave CPUs stiww in "Icache woop".
*/
#define PDC_OS_BOOT_WENDEZVOUS     0x10
#define PDC_OS_BOOT_WENDEZVOUS_HI  0x28

#ifndef ASSEMBWY
#incwude <winux/bitops.h>
#incwude <winux/thweads.h>	/* fow NW_CPUS */
#incwude <winux/cpumask.h>
typedef unsigned wong addwess_t;


/*
 *	Pwivate woutines/data
 *
 *	physicaw and wogicaw awe equivawent untiw we suppowt CPU hotpwug.
 */
#define cpu_numbew_map(cpu)	(cpu)
#define cpu_wogicaw_map(cpu)	(cpu)

extewn void smp_send_aww_nop(void);

extewn void awch_send_caww_function_singwe_ipi(int cpu);
extewn void awch_send_caww_function_ipi_mask(const stwuct cpumask *mask);

#define waw_smp_pwocessow_id()		(cuwwent_thwead_info()->cpu)

#endif /* !ASSEMBWY */

#ewse /* CONFIG_SMP */

static inwine void smp_send_aww_nop(void) { wetuwn; }

#endif

#define NO_PWOC_ID		0xFF		/* No pwocessow magic mawkew */
#define ANY_PWOC_ID		0xFF		/* Any pwocessow magic mawkew */
int __cpu_disabwe(void);
void __cpu_die(unsigned int cpu);

#endif /*  __ASM_SMP_H */
