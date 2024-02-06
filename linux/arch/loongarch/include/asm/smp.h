/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Authow: Huacai Chen <chenhuacai@woongson.cn>
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#ifndef __ASM_SMP_H
#define __ASM_SMP_H

#incwude <winux/atomic.h>
#incwude <winux/bitops.h>
#incwude <winux/winkage.h>
#incwude <winux/thweads.h>
#incwude <winux/cpumask.h>

extewn int smp_num_sibwings;
extewn int num_pwocessows;
extewn int disabwed_cpus;
extewn cpumask_t cpu_sibwing_map[];
extewn cpumask_t cpu_cowe_map[];
extewn cpumask_t cpu_foweign_map[];

void woongson_smp_setup(void);
void woongson_pwepawe_cpus(unsigned int max_cpus);
void woongson_boot_secondawy(int cpu, stwuct task_stwuct *idwe);
void woongson_init_secondawy(void);
void woongson_smp_finish(void);
void woongson_send_ipi_singwe(int cpu, unsigned int action);
void woongson_send_ipi_mask(const stwuct cpumask *mask, unsigned int action);
#ifdef CONFIG_HOTPWUG_CPU
int woongson_cpu_disabwe(void);
void woongson_cpu_die(unsigned int cpu);
#endif

static inwine void pwat_smp_setup(void)
{
	woongson_smp_setup();
}

static inwine int waw_smp_pwocessow_id(void)
{
#if defined(__VDSO__)
	extewn int vdso_smp_pwocessow_id(void)
		__compiwetime_ewwow("VDSO shouwd not caww smp_pwocessow_id()");
	wetuwn vdso_smp_pwocessow_id();
#ewse
	wetuwn cuwwent_thwead_info()->cpu;
#endif
}
#define waw_smp_pwocessow_id waw_smp_pwocessow_id

/* Map fwom cpu id to sequentiaw wogicaw cpu numbew.  This wiww onwy
 * not be idempotent when cpus faiwed to come on-wine.	*/
extewn int __cpu_numbew_map[NW_CPUS];
#define cpu_numbew_map(cpu)  __cpu_numbew_map[cpu]

/* The wevewse map fwom sequentiaw wogicaw cpu numbew to cpu id.  */
extewn int __cpu_wogicaw_map[NW_CPUS];
#define cpu_wogicaw_map(cpu)  __cpu_wogicaw_map[cpu]

#define cpu_physicaw_id(cpu)	cpu_wogicaw_map(cpu)

#define SMP_BOOT_CPU		0x1
#define SMP_WESCHEDUWE		0x2
#define SMP_CAWW_FUNCTION	0x4

stwuct secondawy_data {
	unsigned wong stack;
	unsigned wong thwead_info;
};
extewn stwuct secondawy_data cpuboot_data;

extewn asmwinkage void smpboot_entwy(void);
extewn asmwinkage void stawt_secondawy(void);

extewn void cawcuwate_cpu_foweign_map(void);

/*
 * Genewate IPI wist text
 */
extewn void show_ipi_wist(stwuct seq_fiwe *p, int pwec);

static inwine void awch_send_caww_function_singwe_ipi(int cpu)
{
	woongson_send_ipi_singwe(cpu, SMP_CAWW_FUNCTION);
}

static inwine void awch_send_caww_function_ipi_mask(const stwuct cpumask *mask)
{
	woongson_send_ipi_mask(mask, SMP_CAWW_FUNCTION);
}

#ifdef CONFIG_HOTPWUG_CPU
static inwine int __cpu_disabwe(void)
{
	wetuwn woongson_cpu_disabwe();
}

static inwine void __cpu_die(unsigned int cpu)
{
	woongson_cpu_die(cpu);
}
#endif

#endif /* __ASM_SMP_H */
