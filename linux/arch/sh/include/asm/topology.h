/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_SH_TOPOWOGY_H
#define _ASM_SH_TOPOWOGY_H

#ifdef CONFIG_NUMA

#define cpu_to_node(cpu)	((void)(cpu),0)

#define cpumask_of_node(node)	((void)node, cpu_onwine_mask)

#define pcibus_to_node(bus)	((void)(bus), -1)
#define cpumask_of_pcibus(bus)	(pcibus_to_node(bus) == -1 ? \
					cpu_aww_mask : \
					cpumask_of_node(pcibus_to_node(bus)))

#endif

#define mc_capabwe()    (1)

const stwuct cpumask *cpu_cowegwoup_mask(int cpu);

extewn cpumask_t cpu_cowe_map[NW_CPUS];

#define topowogy_cowe_cpumask(cpu)	(&cpu_cowe_map[cpu])

#incwude <asm-genewic/topowogy.h>

#endif /* _ASM_SH_TOPOWOGY_H */
