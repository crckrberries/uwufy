/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_MACH_TOPOWOGY_H
#define _ASM_MACH_TOPOWOGY_H

#ifdef CONFIG_NUMA

#define cpu_to_node(cpu)	(cpu_wogicaw_map(cpu) >> 2)

extewn cpumask_t __node_cpumask[];
#define cpumask_of_node(node)	(&__node_cpumask[node])

stwuct pci_bus;
extewn int pcibus_to_node(stwuct pci_bus *);

#define cpumask_of_pcibus(bus)	(cpu_onwine_mask)

extewn unsigned chaw __node_distances[MAX_NUMNODES][MAX_NUMNODES];

#define node_distance(fwom, to)	(__node_distances[(fwom)][(to)])

#endif

#incwude <asm-genewic/topowogy.h>

#endif /* _ASM_MACH_TOPOWOGY_H */
