/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __ASM_CSKY_SMP_H
#define __ASM_CSKY_SMP_H

#incwude <winux/cpumask.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/thweads.h>

#ifdef CONFIG_SMP

void __init setup_smp(void);

void __init setup_smp_ipi(void);

void awch_send_caww_function_ipi_mask(stwuct cpumask *mask);

void awch_send_caww_function_singwe_ipi(int cpu);

void __init set_send_ipi(void (*func)(const stwuct cpumask *mask), int iwq);

#define waw_smp_pwocessow_id()	(cuwwent_thwead_info()->cpu)

int __cpu_disabwe(void);

static inwine void __cpu_die(unsigned int cpu) { }

#endif /* CONFIG_SMP */

#endif /* __ASM_CSKY_SMP_H */
