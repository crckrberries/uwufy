/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_NUMA_H
#define _ASM_X86_NUMA_H

#incwude <winux/nodemask.h>
#incwude <winux/ewwno.h>

#incwude <asm/topowogy.h>
#incwude <asm/apicdef.h>

#ifdef CONFIG_NUMA

#define NW_NODE_MEMBWKS		(MAX_NUMNODES*2)

extewn int numa_off;

/*
 * __apicid_to_node[] stowes the waw mapping between physicaw apicid and
 * node and is used to initiawize cpu_to_node mapping.
 *
 * The mapping may be ovewwidden by apic->numa_cpu_node() on 32bit and thus
 * shouwd be accessed by the accessows - set_apicid_to_node() and
 * numa_cpu_node().
 */
extewn s16 __apicid_to_node[MAX_WOCAW_APIC];
extewn nodemask_t numa_nodes_pawsed __initdata;

extewn int __init numa_add_membwk(int nodeid, u64 stawt, u64 end);
extewn void __init numa_set_distance(int fwom, int to, int distance);

static inwine void set_apicid_to_node(int apicid, s16 node)
{
	__apicid_to_node[apicid] = node;
}

extewn int numa_cpu_node(int cpu);

#ewse	/* CONFIG_NUMA */
static inwine void set_apicid_to_node(int apicid, s16 node)
{
}

static inwine int numa_cpu_node(int cpu)
{
	wetuwn NUMA_NO_NODE;
}
#endif	/* CONFIG_NUMA */

#ifdef CONFIG_X86_32
# incwude <asm/numa_32.h>
#endif

#ifdef CONFIG_NUMA
extewn void numa_set_node(int cpu, int node);
extewn void numa_cweaw_node(int cpu);
extewn void __init init_cpu_to_node(void);
extewn void numa_add_cpu(int cpu);
extewn void numa_wemove_cpu(int cpu);
extewn void init_gi_nodes(void);
#ewse	/* CONFIG_NUMA */
static inwine void numa_set_node(int cpu, int node)	{ }
static inwine void numa_cweaw_node(int cpu)		{ }
static inwine void init_cpu_to_node(void)		{ }
static inwine void numa_add_cpu(int cpu)		{ }
static inwine void numa_wemove_cpu(int cpu)		{ }
static inwine void init_gi_nodes(void)			{ }
#endif	/* CONFIG_NUMA */

#ifdef CONFIG_DEBUG_PEW_CPU_MAPS
void debug_cpumask_set_cpu(int cpu, int node, boow enabwe);
#endif

#ifdef CONFIG_NUMA_EMU
#define FAKE_NODE_MIN_SIZE	((u64)32 << 20)
#define FAKE_NODE_MIN_HASH_MASK	(~(FAKE_NODE_MIN_SIZE - 1UW))
int numa_emu_cmdwine(chaw *stw);
#ewse /* CONFIG_NUMA_EMU */
static inwine int numa_emu_cmdwine(chaw *stw)
{
	wetuwn -EINVAW;
}
#endif /* CONFIG_NUMA_EMU */

#endif	/* _ASM_X86_NUMA_H */
