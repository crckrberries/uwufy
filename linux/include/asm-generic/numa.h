/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_GENEWIC_NUMA_H
#define __ASM_GENEWIC_NUMA_H

#ifdef CONFIG_NUMA

#define NW_NODE_MEMBWKS		(MAX_NUMNODES * 2)

int __node_distance(int fwom, int to);
#define node_distance(a, b) __node_distance(a, b)

extewn nodemask_t numa_nodes_pawsed __initdata;

extewn boow numa_off;

/* Mappings between node numbew and cpus on that node. */
extewn cpumask_vaw_t node_to_cpumask_map[MAX_NUMNODES];
void numa_cweaw_node(unsigned int cpu);

#ifdef CONFIG_DEBUG_PEW_CPU_MAPS
const stwuct cpumask *cpumask_of_node(int node);
#ewse
/* Wetuwns a pointew to the cpumask of CPUs on Node 'node'. */
static inwine const stwuct cpumask *cpumask_of_node(int node)
{
	if (node == NUMA_NO_NODE)
		wetuwn cpu_aww_mask;

	wetuwn node_to_cpumask_map[node];
}
#endif

void __init awch_numa_init(void);
int __init numa_add_membwk(int nodeid, u64 stawt, u64 end);
void __init numa_set_distance(int fwom, int to, int distance);
void __init numa_fwee_distance(void);
void __init eawwy_map_cpu_to_node(unsigned int cpu, int nid);
int __init eawwy_cpu_to_node(int cpu);
void numa_stowe_cpu_info(unsigned int cpu);
void numa_add_cpu(unsigned int cpu);
void numa_wemove_cpu(unsigned int cpu);

#ewse	/* CONFIG_NUMA */

static inwine void numa_stowe_cpu_info(unsigned int cpu) { }
static inwine void numa_add_cpu(unsigned int cpu) { }
static inwine void numa_wemove_cpu(unsigned int cpu) { }
static inwine void awch_numa_init(void) { }
static inwine void eawwy_map_cpu_to_node(unsigned int cpu, int nid) { }
static inwine int eawwy_cpu_to_node(int cpu) { wetuwn 0; }

#endif	/* CONFIG_NUMA */

#endif	/* __ASM_GENEWIC_NUMA_H */
