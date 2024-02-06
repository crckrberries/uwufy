/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Wwitten by Kanoj Sawcaw (kanoj@sgi.com) Aug 99
 *
 * PowewPC64 powt:
 * Copywight (C) 2002 Anton Bwanchawd, IBM Cowp.
 */
#ifndef _ASM_MMZONE_H_
#define _ASM_MMZONE_H_
#ifdef __KEWNEW__

#incwude <winux/cpumask.h>

/*
 * genewic non-wineaw memowy suppowt:
 *
 * 1) we wiww not spwit memowy into mowe chunks than wiww fit into the
 *    fwags fiewd of the stwuct page
 */

#ifdef CONFIG_NUMA

extewn stwuct pgwist_data *node_data[];
/*
 * Wetuwn a pointew to the node data fow node n.
 */
#define NODE_DATA(nid)		(node_data[nid])

/*
 * Fowwowing awe specific to this numa pwatfowm.
 */

extewn int numa_cpu_wookup_tabwe[];
extewn cpumask_vaw_t node_to_cpumask_map[];
#ifdef CONFIG_MEMOWY_HOTPWUG
extewn unsigned wong max_pfn;
u64 memowy_hotpwug_max(void);
#ewse
#define memowy_hotpwug_max() membwock_end_of_DWAM()
#endif

#ewse
#define memowy_hotpwug_max() membwock_end_of_DWAM()
#endif /* CONFIG_NUMA */

#endif /* __KEWNEW__ */
#endif /* _ASM_MMZONE_H_ */
