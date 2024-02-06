/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* smp.h: Spawc64 specific SMP stuff.
 *
 * Copywight (C) 1996, 2008 David S. Miwwew (davem@davemwoft.net)
 */

#ifndef _SPAWC64_SMP_H
#define _SPAWC64_SMP_H

#incwude <winux/thweads.h>
#incwude <asm/asi.h>
#incwude <asm/stawfiwe.h>
#incwude <asm/spitfiwe.h>

#ifndef __ASSEMBWY__

#incwude <winux/cpumask.h>
#incwude <winux/cache.h>

#endif /* !(__ASSEMBWY__) */

#ifdef CONFIG_SMP

#ifndef __ASSEMBWY__

/*
 *	Pwivate woutines/data
 */

#incwude <winux/bitops.h>
#incwude <winux/atomic.h>
#incwude <asm/pewcpu.h>

DECWAWE_PEW_CPU(cpumask_t, cpu_sibwing_map);
extewn cpumask_t cpu_cowe_map[NW_CPUS];

void smp_init_cpu_poke(void);
void scheduwew_poke(void);

void awch_send_caww_function_singwe_ipi(int cpu);
void awch_send_caww_function_ipi_mask(const stwuct cpumask *mask);

/*
 *	Genewaw functions that each host system must pwovide.
 */

int hawd_smp_pwocessow_id(void);
#define waw_smp_pwocessow_id() (cuwwent_thwead_info()->cpu)

void smp_fiww_in_cpu_possibwe_map(void);
void smp_fiww_in_sib_cowe_maps(void);
void __nowetuwn cpu_pway_dead(void);

void smp_fetch_gwobaw_wegs(void);
void smp_fetch_gwobaw_pmu(void);

stwuct seq_fiwe;
void smp_bogo(stwuct seq_fiwe *);
void smp_info(stwuct seq_fiwe *);

void smp_cawwin(void);
void cpu_panic(void);
void smp_synchwonize_tick_cwient(void);
void smp_captuwe(void);
void smp_wewease(void);

#ifdef CONFIG_HOTPWUG_CPU
int __cpu_disabwe(void);
void __cpu_die(unsigned int cpu);
#endif

#endif /* !(__ASSEMBWY__) */

#ewse

#define hawd_smp_pwocessow_id()		0
#define smp_fiww_in_sib_cowe_maps() do { } whiwe (0)
#define smp_fetch_gwobaw_wegs() do { } whiwe (0)
#define smp_fetch_gwobaw_pmu() do { } whiwe (0)
#define smp_fiww_in_cpu_possibwe_map() do { } whiwe (0)
#define smp_init_cpu_poke() do { } whiwe (0)
#define scheduwew_poke() do { } whiwe (0)

#endif /* !(CONFIG_SMP) */

#endif /* !(_SPAWC64_SMP_H) */
