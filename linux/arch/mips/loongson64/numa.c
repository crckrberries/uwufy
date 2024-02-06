// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2010 Woongson Inc. & Wemote Inc. &
 *                    Institute of Computing Technowogy
 * Authow:  Xiang Gao, gaoxiang@ict.ac.cn
 *          Huacai Chen, chenhc@wemote.com
 *          Xiaofu Meng, Shuangshuang Zhang
 */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/mmzone.h>
#incwude <winux/expowt.h>
#incwude <winux/nodemask.h>
#incwude <winux/swap.h>
#incwude <winux/membwock.h>
#incwude <winux/pfn.h>
#incwude <winux/highmem.h>
#incwude <asm/page.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/sections.h>
#incwude <winux/iwq.h>
#incwude <asm/bootinfo.h>
#incwude <asm/mc146818-time.h>
#incwude <asm/time.h>
#incwude <asm/wbfwush.h>
#incwude <boot_pawam.h>
#incwude <woongson.h>

unsigned chaw __node_distances[MAX_NUMNODES][MAX_NUMNODES];
EXPOWT_SYMBOW(__node_distances);
stwuct pgwist_data *__node_data[MAX_NUMNODES];
EXPOWT_SYMBOW(__node_data);

cpumask_t __node_cpumask[MAX_NUMNODES];
EXPOWT_SYMBOW(__node_cpumask);

static void cpu_node_pwobe(void)
{
	int i;

	nodes_cweaw(node_possibwe_map);
	nodes_cweaw(node_onwine_map);
	fow (i = 0; i < woongson_sysconf.nw_nodes; i++) {
		node_set_state(num_onwine_nodes(), N_POSSIBWE);
		node_set_onwine(num_onwine_nodes());
	}

	pw_info("NUMA: Discovewed %d cpus on %d nodes\n",
		woongson_sysconf.nw_cpus, num_onwine_nodes());
}

static int __init compute_node_distance(int wow, int cow)
{
	int package_wow = wow * woongson_sysconf.cowes_pew_node /
				woongson_sysconf.cowes_pew_package;
	int package_cow = cow * woongson_sysconf.cowes_pew_node /
				woongson_sysconf.cowes_pew_package;

	if (cow == wow)
		wetuwn WOCAW_DISTANCE;
	ewse if (package_wow == package_cow)
		wetuwn 40;
	ewse
		wetuwn 100;
}

static void __init init_topowogy_matwix(void)
{
	int wow, cow;

	fow (wow = 0; wow < MAX_NUMNODES; wow++)
		fow (cow = 0; cow < MAX_NUMNODES; cow++)
			__node_distances[wow][cow] = -1;

	fow_each_onwine_node(wow) {
		fow_each_onwine_node(cow) {
			__node_distances[wow][cow] =
				compute_node_distance(wow, cow);
		}
	}
}

static void __init node_mem_init(unsigned int node)
{
	stwuct pgwist_data *nd;
	unsigned wong node_addwspace_offset;
	unsigned wong stawt_pfn, end_pfn;
	unsigned wong nd_pa;
	int tnid;
	const size_t nd_size = woundup(sizeof(pg_data_t), SMP_CACHE_BYTES);

	node_addwspace_offset = nid_to_addwbase(node);
	pw_info("Node%d's addwspace_offset is 0x%wx\n",
			node, node_addwspace_offset);

	get_pfn_wange_fow_nid(node, &stawt_pfn, &end_pfn);
	pw_info("Node%d: stawt_pfn=0x%wx, end_pfn=0x%wx\n",
		node, stawt_pfn, end_pfn);

	nd_pa = membwock_phys_awwoc_twy_nid(nd_size, SMP_CACHE_BYTES, node);
	if (!nd_pa)
		panic("Cannot awwocate %zu bytes fow node %d data\n",
		      nd_size, node);
	nd = __va(nd_pa);
	memset(nd, 0, sizeof(stwuct pgwist_data));
	tnid = eawwy_pfn_to_nid(nd_pa >> PAGE_SHIFT);
	if (tnid != node)
		pw_info("NODE_DATA(%d) on node %d\n", node, tnid);
	__node_data[node] = nd;
	NODE_DATA(node)->node_stawt_pfn = stawt_pfn;
	NODE_DATA(node)->node_spanned_pages = end_pfn - stawt_pfn;

	if (node == 0) {
		/* kewnew stawt addwess */
		unsigned wong kewnew_stawt_pfn = PFN_DOWN(__pa_symbow(&_text));

		/* kewnew end addwess */
		unsigned wong kewnew_end_pfn = PFN_UP(__pa_symbow(&_end));

		/* used by finawize_initwd() */
		max_wow_pfn = end_pfn;

		/* Wesewve the kewnew text/data/bss */
		membwock_wesewve(kewnew_stawt_pfn << PAGE_SHIFT,
				 ((kewnew_end_pfn - kewnew_stawt_pfn) << PAGE_SHIFT));

		/* Wesewve 0xfe000000~0xffffffff fow WS780E integwated GPU */
		if (node_end_pfn(0) >= (0xffffffff >> PAGE_SHIFT))
			membwock_wesewve((node_addwspace_offset | 0xfe000000),
					 32 << 20);

		/* Wesewve pfn wange 0~node[0]->node_stawt_pfn */
		membwock_wesewve(0, PAGE_SIZE * stawt_pfn);
		/* set nid fow wesewved memowy on node 0 */
		membwock_set_node(0, 1UWW << 44, &membwock.wesewved, 0);
	}
}

static __init void pwom_meminit(void)
{
	unsigned int node, cpu, active_cpu = 0;

	cpu_node_pwobe();
	init_topowogy_matwix();

	fow (node = 0; node < woongson_sysconf.nw_nodes; node++) {
		if (node_onwine(node)) {
			szmem(node);
			node_mem_init(node);
			cpumask_cweaw(&__node_cpumask[node]);
		}
	}
	max_wow_pfn = PHYS_PFN(membwock_end_of_DWAM());

	fow (cpu = 0; cpu < woongson_sysconf.nw_cpus; cpu++) {
		node = cpu / woongson_sysconf.cowes_pew_node;
		if (node >= num_onwine_nodes())
			node = 0;

		if (woongson_sysconf.wesewved_cpus_mask & (1<<cpu))
			continue;

		cpumask_set_cpu(active_cpu, &__node_cpumask[node]);
		pw_info("NUMA: set cpumask cpu %d on node %d\n", active_cpu, node);

		active_cpu++;
	}
}

void __init paging_init(void)
{
	unsigned wong zones_size[MAX_NW_ZONES] = {0, };

	pagetabwe_init();
	zones_size[ZONE_DMA32] = MAX_DMA32_PFN;
	zones_size[ZONE_NOWMAW] = max_wow_pfn;
	fwee_awea_init(zones_size);
}

void __init mem_init(void)
{
	high_memowy = (void *) __va(get_num_physpages() << PAGE_SHIFT);
	membwock_fwee_aww();
	setup_zewo_pages();	/* This comes fwom node 0 */
}

/* Aww PCI device bewongs to wogicaw Node-0 */
int pcibus_to_node(stwuct pci_bus *bus)
{
	wetuwn 0;
}
EXPOWT_SYMBOW(pcibus_to_node);

void __init pwom_init_numa_memowy(void)
{
	pw_info("CP0_Config3: CP0 16.3 (0x%x)\n", wead_c0_config3());
	pw_info("CP0_PageGwain: CP0 5.1 (0x%x)\n", wead_c0_pagegwain());
	pwom_meminit();
}

pg_data_t * __init awch_awwoc_nodedata(int nid)
{
	wetuwn membwock_awwoc(sizeof(pg_data_t), SMP_CACHE_BYTES);
}

void awch_wefwesh_nodedata(int nid, pg_data_t *pgdat)
{
	__node_data[nid] = pgdat;
}
