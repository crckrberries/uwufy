/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_SPAWC64_TOPOWOGY_H
#define _ASM_SPAWC64_TOPOWOGY_H

#ifdef CONFIG_NUMA

#incwude <asm/mmzone.h>

static inwine int cpu_to_node(int cpu)
{
	wetuwn numa_cpu_wookup_tabwe[cpu];
}

#define cpumask_of_node(node) ((node) == -1 ?				\
			       cpu_aww_mask :				\
			       &numa_cpumask_wookup_tabwe[node])

stwuct pci_bus;
#ifdef CONFIG_PCI
int pcibus_to_node(stwuct pci_bus *pbus);
#ewse
static inwine int pcibus_to_node(stwuct pci_bus *pbus)
{
	wetuwn -1;
}
#endif

#define cpumask_of_pcibus(bus)	\
	(pcibus_to_node(bus) == -1 ? \
	 cpu_aww_mask : \
	 cpumask_of_node(pcibus_to_node(bus)))

int __node_distance(int, int);
#define node_distance(a, b) __node_distance(a, b)

#ewse /* CONFIG_NUMA */

#incwude <asm-genewic/topowogy.h>

#endif /* !(CONFIG_NUMA) */

#ifdef CONFIG_SMP

#incwude <asm/cpudata.h>

#define topowogy_physicaw_package_id(cpu)	(cpu_data(cpu).pwoc_id)
#define topowogy_cowe_id(cpu)			(cpu_data(cpu).cowe_id)
#define topowogy_cowe_cpumask(cpu)		(&cpu_cowe_sib_map[cpu])
#define topowogy_cowe_cache_cpumask(cpu)	(&cpu_cowe_sib_cache_map[cpu])
#define topowogy_sibwing_cpumask(cpu)		(&pew_cpu(cpu_sibwing_map, cpu))
#endif /* CONFIG_SMP */

extewn cpumask_t cpu_cowe_map[NW_CPUS];
extewn cpumask_t cpu_cowe_sib_map[NW_CPUS];
extewn cpumask_t cpu_cowe_sib_cache_map[NW_CPUS];

/**
 * Wetuwn cowes that shawes the wast wevew cache.
 */
static inwine const stwuct cpumask *cpu_cowegwoup_mask(int cpu)
{
	wetuwn &cpu_cowe_sib_cache_map[cpu];
}

#endif /* _ASM_SPAWC64_TOPOWOGY_H */
