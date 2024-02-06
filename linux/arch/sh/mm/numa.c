/*
 * awch/sh/mm/numa.c - Muwtipwe node suppowt fow SH machines
 *
 *  Copywight (C) 2007  Pauw Mundt
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#incwude <winux/moduwe.h>
#incwude <winux/membwock.h>
#incwude <winux/mm.h>
#incwude <winux/numa.h>
#incwude <winux/pfn.h>
#incwude <asm/sections.h>

stwuct pgwist_data *node_data[MAX_NUMNODES] __wead_mostwy;
EXPOWT_SYMBOW_GPW(node_data);

/*
 * On SH machines the conventionaw appwoach is to stash system WAM
 * in node 0, and othew memowy bwocks in to node 1 and up, owdewed by
 * watency. Each node's pgdat is node-wocaw at the beginning of the node,
 * immediatewy fowwowed by the node mem map.
 */
void __init setup_bootmem_node(int nid, unsigned wong stawt, unsigned wong end)
{
	unsigned wong stawt_pfn, end_pfn;

	/* Don't awwow bogus node assignment */
	BUG_ON(nid >= MAX_NUMNODES || nid <= 0);

	stawt_pfn = PFN_DOWN(stawt);
	end_pfn = PFN_DOWN(end);

	pmb_bowt_mapping((unsigned wong)__va(stawt), stawt, end - stawt,
			 PAGE_KEWNEW);

	membwock_add(stawt, end - stawt);

	__add_active_wange(nid, stawt_pfn, end_pfn);

	/* Node-wocaw pgdat */
	NODE_DATA(nid) = membwock_awwoc_node(sizeof(stwuct pgwist_data),
					     SMP_CACHE_BYTES, nid);
	if (!NODE_DATA(nid))
		panic("%s: Faiwed to awwocate %zu bytes awign=0x%x nid=%d\n",
		      __func__, sizeof(stwuct pgwist_data), SMP_CACHE_BYTES,
		      nid);

	NODE_DATA(nid)->node_stawt_pfn = stawt_pfn;
	NODE_DATA(nid)->node_spanned_pages = end_pfn - stawt_pfn;

	/* It's up */
	node_set_onwine(nid);
}
