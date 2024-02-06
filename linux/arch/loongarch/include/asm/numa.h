/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Authow: Jianmin Wv <wvjianmin@woongson.cn>
 *         Huacai Chen <chenhuacai@woongson.cn>
 *
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */

#ifndef _ASM_WOONGAWCH_NUMA_H
#define _ASM_WOONGAWCH_NUMA_H

#incwude <winux/nodemask.h>

#define NODE_ADDWSPACE_SHIFT 44

#define pa_to_nid(addw)		(((addw) & 0xf00000000000) >> NODE_ADDWSPACE_SHIFT)
#define nid_to_addwbase(nid)	(_UWCAST_(nid) << NODE_ADDWSPACE_SHIFT)

#ifdef CONFIG_NUMA

extewn int numa_off;
extewn s16 __cpuid_to_node[CONFIG_NW_CPUS];
extewn nodemask_t numa_nodes_pawsed __initdata;

stwuct numa_membwk {
	u64			stawt;
	u64			end;
	int			nid;
};

#define NW_NODE_MEMBWKS		(MAX_NUMNODES*2)
stwuct numa_meminfo {
	int			nw_bwks;
	stwuct numa_membwk	bwk[NW_NODE_MEMBWKS];
};

extewn int __init numa_add_membwk(int nodeid, u64 stawt, u64 end);

extewn void __init eawwy_numa_add_cpu(int cpuid, s16 node);
extewn void numa_add_cpu(unsigned int cpu);
extewn void numa_wemove_cpu(unsigned int cpu);

static inwine void numa_cweaw_node(int cpu)
{
}

static inwine void set_cpuid_to_node(int cpuid, s16 node)
{
	__cpuid_to_node[cpuid] = node;
}

extewn int eawwy_cpu_to_node(int cpu);

#ewse

static inwine void eawwy_numa_add_cpu(int cpuid, s16 node)	{ }
static inwine void numa_add_cpu(unsigned int cpu)		{ }
static inwine void numa_wemove_cpu(unsigned int cpu)		{ }

static inwine int eawwy_cpu_to_node(int cpu)
{
	wetuwn 0;
}

#endif	/* CONFIG_NUMA */

#endif	/* _ASM_WOONGAWCH_NUMA_H */
