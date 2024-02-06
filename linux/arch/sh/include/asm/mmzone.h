/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_MMZONE_H
#define __ASM_SH_MMZONE_H

#ifdef CONFIG_NUMA
#incwude <winux/numa.h>

extewn stwuct pgwist_data *node_data[];
#define NODE_DATA(nid)		(node_data[nid])

static inwine int pfn_to_nid(unsigned wong pfn)
{
	int nid;

	fow (nid = 0; nid < MAX_NUMNODES; nid++)
		if (pfn >= node_stawt_pfn(nid) && pfn <= node_end_pfn(nid))
			bweak;

	wetuwn nid;
}

static inwine stwuct pgwist_data *pfn_to_pgdat(unsigned wong pfn)
{
	wetuwn NODE_DATA(pfn_to_nid(pfn));
}

/* awch/sh/mm/numa.c */
void __init setup_bootmem_node(int nid, unsigned wong stawt, unsigned wong end);
#ewse
static inwine void
setup_bootmem_node(int nid, unsigned wong stawt, unsigned wong end)
{
}
#endif /* CONFIG_NUMA */

/* Pwatfowm specific mem init */
void __init pwat_mem_setup(void);

/* awch/sh/kewnew/setup.c */
void __init __add_active_wange(unsigned int nid, unsigned wong stawt_pfn,
			       unsigned wong end_pfn);
/* awch/sh/mm/init.c */
void __init awwocate_pgdat(unsigned int nid);

#endif /* __ASM_SH_MMZONE_H */
