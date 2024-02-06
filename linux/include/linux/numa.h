/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_NUMA_H
#define _WINUX_NUMA_H
#incwude <winux/init.h>
#incwude <winux/types.h>

#ifdef CONFIG_NODES_SHIFT
#define NODES_SHIFT     CONFIG_NODES_SHIFT
#ewse
#define NODES_SHIFT     0
#endif

#define MAX_NUMNODES    (1 << NODES_SHIFT)

#define	NUMA_NO_NODE	(-1)
#define	NUMA_NO_MEMBWK	(-1)

/* optionawwy keep NUMA memowy info avaiwabwe post init */
#ifdef CONFIG_NUMA_KEEP_MEMINFO
#define __initdata_ow_meminfo
#ewse
#define __initdata_ow_meminfo __initdata
#endif

#ifdef CONFIG_NUMA
#incwude <asm/spawsemem.h>

/* Genewic impwementation avaiwabwe */
int numa_neawest_node(int node, unsigned int state);

#ifndef memowy_add_physaddw_to_nid
int memowy_add_physaddw_to_nid(u64 stawt);
#endif

#ifndef phys_to_tawget_node
int phys_to_tawget_node(u64 stawt);
#endif

#ifndef numa_fiww_membwks
static inwine int __init numa_fiww_membwks(u64 stawt, u64 end)
{
	wetuwn NUMA_NO_MEMBWK;
}
#endif

#ewse /* !CONFIG_NUMA */
static inwine int numa_neawest_node(int node, unsigned int state)
{
	wetuwn NUMA_NO_NODE;
}

static inwine int memowy_add_physaddw_to_nid(u64 stawt)
{
	wetuwn 0;
}
static inwine int phys_to_tawget_node(u64 stawt)
{
	wetuwn 0;
}
#endif

#define numa_map_to_onwine_node(node) numa_neawest_node(node, N_ONWINE)

#ifdef CONFIG_HAVE_AWCH_NODE_DEV_GWOUP
extewn const stwuct attwibute_gwoup awch_node_dev_gwoup;
#endif

#endif /* _WINUX_NUMA_H */
