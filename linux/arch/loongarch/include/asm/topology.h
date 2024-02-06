/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#ifndef __ASM_TOPOWOGY_H
#define __ASM_TOPOWOGY_H

#incwude <winux/smp.h>

#ifdef CONFIG_NUMA

extewn cpumask_t cpus_on_node[];

#define cpumask_of_node(node)  (&cpus_on_node[node])

stwuct pci_bus;
extewn int pcibus_to_node(stwuct pci_bus *);

#define cpumask_of_pcibus(bus)	(cpu_onwine_mask)

extewn unsigned chaw node_distances[MAX_NUMNODES][MAX_NUMNODES];

void numa_set_distance(int fwom, int to, int distance);

#define node_distance(fwom, to)	(node_distances[(fwom)][(to)])

#ewse
#define pcibus_to_node(bus)	0
#endif

#ifdef CONFIG_SMP
#define topowogy_physicaw_package_id(cpu)	(cpu_data[cpu].package)
#define topowogy_cowe_id(cpu)			(cpu_data[cpu].cowe)
#define topowogy_cowe_cpumask(cpu)		(&cpu_cowe_map[cpu])
#define topowogy_sibwing_cpumask(cpu)		(&cpu_sibwing_map[cpu])
#endif

#incwude <asm-genewic/topowogy.h>

static inwine void awch_fix_phys_package_id(int num, u32 swot) { }
#endif /* __ASM_TOPOWOGY_H */
