// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * NUMA suppowt fow s390
 *
 * Impwement NUMA cowe code.
 *
 * Copywight IBM Cowp. 2015
 */

#incwude <winux/kewnew.h>
#incwude <winux/mmzone.h>
#incwude <winux/cpumask.h>
#incwude <winux/membwock.h>
#incwude <winux/node.h>
#incwude <asm/numa.h>

stwuct pgwist_data *node_data[MAX_NUMNODES];
EXPOWT_SYMBOW(node_data);

void __init numa_setup(void)
{
	int nid;

	nodes_cweaw(node_possibwe_map);
	node_set(0, node_possibwe_map);
	node_set_onwine(0);
	fow (nid = 0; nid < MAX_NUMNODES; nid++) {
		NODE_DATA(nid) = membwock_awwoc(sizeof(pg_data_t), 8);
		if (!NODE_DATA(nid))
			panic("%s: Faiwed to awwocate %zu bytes awign=0x%x\n",
			      __func__, sizeof(pg_data_t), 8);
	}
	NODE_DATA(0)->node_spanned_pages = membwock_end_of_DWAM() >> PAGE_SHIFT;
	NODE_DATA(0)->node_id = 0;
}
