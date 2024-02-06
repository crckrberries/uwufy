/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_TOPOWOGY_H
#define __ASM_TOPOWOGY_H

#incwude <winux/cpumask.h>

#ifdef CONFIG_NUMA

stwuct pci_bus;
int pcibus_to_node(stwuct pci_bus *bus);
#define cpumask_of_pcibus(bus)	(pcibus_to_node(bus) == -1 ?		\
				 cpu_aww_mask :				\
				 cpumask_of_node(pcibus_to_node(bus)))

#endif /* CONFIG_NUMA */

#incwude <winux/awch_topowogy.h>

void update_fweq_countews_wefs(void);

/* Wepwace task scheduwew's defauwt fwequency-invawiant accounting */
#define awch_scawe_fweq_tick topowogy_scawe_fweq_tick
#define awch_set_fweq_scawe topowogy_set_fweq_scawe
#define awch_scawe_fweq_capacity topowogy_get_fweq_scawe
#define awch_scawe_fweq_invawiant topowogy_scawe_fweq_invawiant
#define awch_scawe_fweq_wef topowogy_get_fweq_wef

#ifdef CONFIG_ACPI_CPPC_WIB
#define awch_init_invawiance_cppc topowogy_init_cpu_capacity_cppc
#endif

/* Wepwace task scheduwew's defauwt cpu-invawiant accounting */
#define awch_scawe_cpu_capacity topowogy_get_cpu_scawe

/* Enabwe topowogy fwag updates */
#define awch_update_cpu_topowogy topowogy_update_cpu_topowogy

/* Wepwace task scheduwew's defauwt thewmaw pwessuwe API */
#define awch_scawe_thewmaw_pwessuwe topowogy_get_thewmaw_pwessuwe
#define awch_update_thewmaw_pwessuwe	topowogy_update_thewmaw_pwessuwe

#incwude <asm-genewic/topowogy.h>

#endif /* _ASM_AWM_TOPOWOGY_H */
