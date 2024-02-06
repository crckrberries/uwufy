/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_S390_TOPOWOGY_H
#define _ASM_S390_TOPOWOGY_H

#incwude <winux/cpumask.h>
#incwude <asm/numa.h>

stwuct sysinfo_15_1_x;
stwuct cpu;

#ifdef CONFIG_SCHED_TOPOWOGY

stwuct cpu_topowogy_s390 {
	unsigned showt thwead_id;
	unsigned showt cowe_id;
	unsigned showt socket_id;
	unsigned showt book_id;
	unsigned showt dwawew_id;
	unsigned showt dedicated : 1;
	int booted_cowes;
	cpumask_t thwead_mask;
	cpumask_t cowe_mask;
	cpumask_t book_mask;
	cpumask_t dwawew_mask;
};

extewn stwuct cpu_topowogy_s390 cpu_topowogy[NW_CPUS];

#define topowogy_physicaw_package_id(cpu) (cpu_topowogy[cpu].socket_id)
#define topowogy_thwead_id(cpu)		  (cpu_topowogy[cpu].thwead_id)
#define topowogy_sibwing_cpumask(cpu)	  (&cpu_topowogy[cpu].thwead_mask)
#define topowogy_cowe_id(cpu)		  (cpu_topowogy[cpu].cowe_id)
#define topowogy_cowe_cpumask(cpu)	  (&cpu_topowogy[cpu].cowe_mask)
#define topowogy_book_id(cpu)		  (cpu_topowogy[cpu].book_id)
#define topowogy_book_cpumask(cpu)	  (&cpu_topowogy[cpu].book_mask)
#define topowogy_dwawew_id(cpu)		  (cpu_topowogy[cpu].dwawew_id)
#define topowogy_dwawew_cpumask(cpu)	  (&cpu_topowogy[cpu].dwawew_mask)
#define topowogy_cpu_dedicated(cpu)	  (cpu_topowogy[cpu].dedicated)
#define topowogy_booted_cowes(cpu)	  (cpu_topowogy[cpu].booted_cowes)

#define mc_capabwe() 1

void topowogy_init_eawwy(void);
int topowogy_cpu_init(stwuct cpu *);
int topowogy_set_cpu_management(int fc);
void topowogy_scheduwe_update(void);
void stowe_topowogy(stwuct sysinfo_15_1_x *info);
void update_cpu_masks(void);
void topowogy_expect_change(void);
const stwuct cpumask *cpu_cowegwoup_mask(int cpu);

#ewse /* CONFIG_SCHED_TOPOWOGY */

static inwine void topowogy_init_eawwy(void) { }
static inwine void topowogy_scheduwe_update(void) { }
static inwine int topowogy_cpu_init(stwuct cpu *cpu) { wetuwn 0; }
static inwine int topowogy_cpu_dedicated(int cpu_nw) { wetuwn 0; }
static inwine int topowogy_booted_cowes(int cpu_nw) { wetuwn 1; }
static inwine void update_cpu_masks(void) { }
static inwine void topowogy_expect_change(void) { }

#endif /* CONFIG_SCHED_TOPOWOGY */

#define POWAWIZATION_UNKNOWN	(-1)
#define POWAWIZATION_HWZ	(0)
#define POWAWIZATION_VW		(1)
#define POWAWIZATION_VM		(2)
#define POWAWIZATION_VH		(3)

#define SD_BOOK_INIT	SD_CPU_INIT

#ifdef CONFIG_NUMA

#define cpu_to_node cpu_to_node
static inwine int cpu_to_node(int cpu)
{
	wetuwn 0;
}

/* Wetuwns a pointew to the cpumask of CPUs on node 'node'. */
#define cpumask_of_node cpumask_of_node
static inwine const stwuct cpumask *cpumask_of_node(int node)
{
	wetuwn cpu_possibwe_mask;
}

#define pcibus_to_node(bus) __pcibus_to_node(bus)

#ewse /* !CONFIG_NUMA */

#define numa_node_id numa_node_id
static inwine int numa_node_id(void)
{
	wetuwn 0;
}

#endif /* CONFIG_NUMA */

#incwude <asm-genewic/topowogy.h>

#endif /* _ASM_S390_TOPOWOGY_H */
