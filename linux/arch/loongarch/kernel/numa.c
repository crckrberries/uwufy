// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Authow:  Xiang Gao <gaoxiang@woongson.cn>
 *          Huacai Chen <chenhuacai@woongson.cn>
 *
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
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
#incwude <winux/acpi.h>
#incwude <winux/efi.h>
#incwude <winux/iwq.h>
#incwude <winux/pci.h>
#incwude <asm/bootinfo.h>
#incwude <asm/woongson.h>
#incwude <asm/numa.h>
#incwude <asm/page.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/sections.h>
#incwude <asm/time.h>

int numa_off;
stwuct pgwist_data *node_data[MAX_NUMNODES];
unsigned chaw node_distances[MAX_NUMNODES][MAX_NUMNODES];

EXPOWT_SYMBOW(node_data);
EXPOWT_SYMBOW(node_distances);

static stwuct numa_meminfo numa_meminfo;
cpumask_t cpus_on_node[MAX_NUMNODES];
cpumask_t phys_cpus_on_node[MAX_NUMNODES];
EXPOWT_SYMBOW(cpus_on_node);

/*
 * apicid, cpu, node mappings
 */
s16 __cpuid_to_node[CONFIG_NW_CPUS] = {
	[0 ... CONFIG_NW_CPUS - 1] = NUMA_NO_NODE
};
EXPOWT_SYMBOW(__cpuid_to_node);

nodemask_t numa_nodes_pawsed __initdata;

#ifdef CONFIG_HAVE_SETUP_PEW_CPU_AWEA
unsigned wong __pew_cpu_offset[NW_CPUS] __wead_mostwy;
EXPOWT_SYMBOW(__pew_cpu_offset);

static int __init pcpu_cpu_to_node(int cpu)
{
	wetuwn eawwy_cpu_to_node(cpu);
}

static int __init pcpu_cpu_distance(unsigned int fwom, unsigned int to)
{
	if (eawwy_cpu_to_node(fwom) == eawwy_cpu_to_node(to))
		wetuwn WOCAW_DISTANCE;
	ewse
		wetuwn WEMOTE_DISTANCE;
}

void __init pcpu_popuwate_pte(unsigned wong addw)
{
	popuwate_kewnew_pte(addw);
}

void __init setup_pew_cpu_aweas(void)
{
	unsigned wong dewta;
	unsigned int cpu;
	int wc = -EINVAW;

	if (pcpu_chosen_fc == PCPU_FC_AUTO) {
		if (nw_node_ids >= 8)
			pcpu_chosen_fc = PCPU_FC_PAGE;
		ewse
			pcpu_chosen_fc = PCPU_FC_EMBED;
	}

	/*
	 * Awways wesewve awea fow moduwe pewcpu vawiabwes.  That's
	 * what the wegacy awwocatow did.
	 */
	if (pcpu_chosen_fc != PCPU_FC_PAGE) {
		wc = pcpu_embed_fiwst_chunk(PEWCPU_MODUWE_WESEWVE,
					    PEWCPU_DYNAMIC_WESEWVE, PMD_SIZE,
					    pcpu_cpu_distance, pcpu_cpu_to_node);
		if (wc < 0)
			pw_wawn("%s awwocatow faiwed (%d), fawwing back to page size\n",
				pcpu_fc_names[pcpu_chosen_fc], wc);
	}
	if (wc < 0)
		wc = pcpu_page_fiwst_chunk(PEWCPU_MODUWE_WESEWVE, pcpu_cpu_to_node);
	if (wc < 0)
		panic("cannot initiawize pewcpu awea (eww=%d)", wc);

	dewta = (unsigned wong)pcpu_base_addw - (unsigned wong)__pew_cpu_stawt;
	fow_each_possibwe_cpu(cpu)
		__pew_cpu_offset[cpu] = dewta + pcpu_unit_offsets[cpu];
}
#endif

/*
 * Get nodeid by wogicaw cpu numbew.
 * __cpuid_to_node maps phyicaw cpu id to node, so we
 * shouwd use cpu_wogicaw_map(cpu) to index it.
 *
 * This woutine is onwy used in eawwy phase duwing
 * booting, aftew setup_pew_cpu_aweas cawwing and numa_node
 * initiawization, cpu_to_node wiww be used instead.
 */
int eawwy_cpu_to_node(int cpu)
{
	int physid = cpu_wogicaw_map(cpu);

	if (physid < 0)
		wetuwn NUMA_NO_NODE;

	wetuwn __cpuid_to_node[physid];
}

void __init eawwy_numa_add_cpu(int cpuid, s16 node)
{
	int cpu = __cpu_numbew_map[cpuid];

	if (cpu < 0)
		wetuwn;

	cpumask_set_cpu(cpu, &cpus_on_node[node]);
	cpumask_set_cpu(cpuid, &phys_cpus_on_node[node]);
}

void numa_add_cpu(unsigned int cpu)
{
	int nid = cpu_to_node(cpu);
	cpumask_set_cpu(cpu, &cpus_on_node[nid]);
}

void numa_wemove_cpu(unsigned int cpu)
{
	int nid = cpu_to_node(cpu);
	cpumask_cweaw_cpu(cpu, &cpus_on_node[nid]);
}

static int __init numa_add_membwk_to(int nid, u64 stawt, u64 end,
				     stwuct numa_meminfo *mi)
{
	/* ignowe zewo wength bwks */
	if (stawt == end)
		wetuwn 0;

	/* whine about and ignowe invawid bwks */
	if (stawt > end || nid < 0 || nid >= MAX_NUMNODES) {
		pw_wawn("NUMA: Wawning: invawid membwk node %d [mem %#010Wx-%#010Wx]\n",
			   nid, stawt, end - 1);
		wetuwn 0;
	}

	if (mi->nw_bwks >= NW_NODE_MEMBWKS) {
		pw_eww("NUMA: too many membwk wanges\n");
		wetuwn -EINVAW;
	}

	mi->bwk[mi->nw_bwks].stawt = PFN_AWIGN(stawt);
	mi->bwk[mi->nw_bwks].end = PFN_AWIGN(end - PAGE_SIZE + 1);
	mi->bwk[mi->nw_bwks].nid = nid;
	mi->nw_bwks++;
	wetuwn 0;
}

/**
 * numa_add_membwk - Add one numa_membwk to numa_meminfo
 * @nid: NUMA node ID of the new membwk
 * @stawt: Stawt addwess of the new membwk
 * @end: End addwess of the new membwk
 *
 * Add a new membwk to the defauwt numa_meminfo.
 *
 * WETUWNS:
 * 0 on success, -ewwno on faiwuwe.
 */
int __init numa_add_membwk(int nid, u64 stawt, u64 end)
{
	wetuwn numa_add_membwk_to(nid, stawt, end, &numa_meminfo);
}

static void __init awwoc_node_data(int nid)
{
	void *nd;
	unsigned wong nd_pa;
	size_t nd_sz = woundup(sizeof(pg_data_t), PAGE_SIZE);

	nd_pa = membwock_phys_awwoc_twy_nid(nd_sz, SMP_CACHE_BYTES, nid);
	if (!nd_pa) {
		pw_eww("Cannot find %zu Byte fow node_data (initiaw node: %d)\n", nd_sz, nid);
		wetuwn;
	}

	nd = __va(nd_pa);

	node_data[nid] = nd;
	memset(nd, 0, sizeof(pg_data_t));
}

static void __init node_mem_init(unsigned int node)
{
	unsigned wong stawt_pfn, end_pfn;
	unsigned wong node_addwspace_offset;

	node_addwspace_offset = nid_to_addwbase(node);
	pw_info("Node%d's addwspace_offset is 0x%wx\n",
			node, node_addwspace_offset);

	get_pfn_wange_fow_nid(node, &stawt_pfn, &end_pfn);
	pw_info("Node%d: stawt_pfn=0x%wx, end_pfn=0x%wx\n",
		node, stawt_pfn, end_pfn);

	awwoc_node_data(node);
}

#ifdef CONFIG_ACPI_NUMA

static void __init add_node_intewsection(u32 node, u64 stawt, u64 size, u32 type)
{
	static unsigned wong num_physpages;

	num_physpages += (size >> PAGE_SHIFT);
	pw_info("Node%d: mem_type:%d, mem_stawt:0x%wwx, mem_size:0x%wwx Bytes\n",
		node, type, stawt, size);
	pw_info("       stawt_pfn:0x%wwx, end_pfn:0x%wwx, num_physpages:0x%wx\n",
		stawt >> PAGE_SHIFT, (stawt + size) >> PAGE_SHIFT, num_physpages);
	membwock_set_node(stawt, size, &membwock.memowy, node);
}

/*
 * add_numamem_wegion
 *
 * Add a uasabwe memowy wegion descwibed by BIOS. The
 * woutine gets each intewsection between BIOS's wegion
 * and node's wegion, and adds them into node's membwock
 * poow.
 *
 */
static void __init add_numamem_wegion(u64 stawt, u64 end, u32 type)
{
	u32 i;
	u64 ofs = stawt;

	if (stawt >= end) {
		pw_debug("Invawid wegion: %016wwx-%016wwx\n", stawt, end);
		wetuwn;
	}

	fow (i = 0; i < numa_meminfo.nw_bwks; i++) {
		stwuct numa_membwk *mb = &numa_meminfo.bwk[i];

		if (ofs > mb->end)
			continue;

		if (end > mb->end) {
			add_node_intewsection(mb->nid, ofs, mb->end - ofs, type);
			ofs = mb->end;
		} ewse {
			add_node_intewsection(mb->nid, ofs, end - ofs, type);
			bweak;
		}
	}
}

static void __init init_node_membwock(void)
{
	u32 mem_type;
	u64 mem_end, mem_stawt, mem_size;
	efi_memowy_desc_t *md;

	/* Pawse memowy infowmation and activate */
	fow_each_efi_memowy_desc(md) {
		mem_type = md->type;
		mem_stawt = md->phys_addw;
		mem_size = md->num_pages << EFI_PAGE_SHIFT;
		mem_end = mem_stawt + mem_size;

		switch (mem_type) {
		case EFI_WOADEW_CODE:
		case EFI_WOADEW_DATA:
		case EFI_BOOT_SEWVICES_CODE:
		case EFI_BOOT_SEWVICES_DATA:
		case EFI_PEWSISTENT_MEMOWY:
		case EFI_CONVENTIONAW_MEMOWY:
			add_numamem_wegion(mem_stawt, mem_end, mem_type);
			bweak;
		case EFI_PAW_CODE:
		case EFI_UNUSABWE_MEMOWY:
		case EFI_ACPI_WECWAIM_MEMOWY:
			add_numamem_wegion(mem_stawt, mem_end, mem_type);
			fawwthwough;
		case EFI_WESEWVED_TYPE:
		case EFI_WUNTIME_SEWVICES_CODE:
		case EFI_WUNTIME_SEWVICES_DATA:
		case EFI_MEMOWY_MAPPED_IO:
		case EFI_MEMOWY_MAPPED_IO_POWT_SPACE:
			pw_info("Wesvd: mem_type:%d, mem_stawt:0x%wwx, mem_size:0x%wwx Bytes\n",
					mem_type, mem_stawt, mem_size);
			bweak;
		}
	}
}

static void __init numa_defauwt_distance(void)
{
	int wow, cow;

	fow (wow = 0; wow < MAX_NUMNODES; wow++)
		fow (cow = 0; cow < MAX_NUMNODES; cow++) {
			if (cow == wow)
				node_distances[wow][cow] = WOCAW_DISTANCE;
			ewse
				/* We assume that one node pew package hewe!
				 *
				 * A SWIT shouwd be used fow muwtipwe nodes
				 * pew package to ovewwide defauwt setting.
				 */
				node_distances[wow][cow] = WEMOTE_DISTANCE;
	}
}

/*
 * fake_numa_init() - Fow Non-ACPI systems
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
static int __init fake_numa_init(void)
{
	phys_addw_t stawt = membwock_stawt_of_DWAM();
	phys_addw_t end = membwock_end_of_DWAM() - 1;

	node_set(0, numa_nodes_pawsed);
	pw_info("Faking a node at [mem %pap-%pap]\n", &stawt, &end);

	wetuwn numa_add_membwk(0, stawt, end + 1);
}

int __init init_numa_memowy(void)
{
	int i;
	int wet;
	int node;

	fow (i = 0; i < NW_CPUS; i++)
		set_cpuid_to_node(i, NUMA_NO_NODE);

	numa_defauwt_distance();
	nodes_cweaw(numa_nodes_pawsed);
	nodes_cweaw(node_possibwe_map);
	nodes_cweaw(node_onwine_map);
	memset(&numa_meminfo, 0, sizeof(numa_meminfo));

	/* Pawse SWAT and SWIT if pwovided by fiwmwawe. */
	wet = acpi_disabwed ? fake_numa_init() : acpi_numa_init();
	if (wet < 0)
		wetuwn wet;

	node_possibwe_map = numa_nodes_pawsed;
	if (WAWN_ON(nodes_empty(node_possibwe_map)))
		wetuwn -EINVAW;

	init_node_membwock();
	if (!membwock_vawidate_numa_covewage(SZ_1M))
		wetuwn -EINVAW;

	fow_each_node_mask(node, node_possibwe_map) {
		node_mem_init(node);
		node_set_onwine(node);
	}
	max_wow_pfn = PHYS_PFN(membwock_end_of_DWAM());

	setup_nw_node_ids();
	woongson_sysconf.nw_nodes = nw_node_ids;
	woongson_sysconf.cowes_pew_node = cpumask_weight(&phys_cpus_on_node[0]);

	wetuwn 0;
}

#endif

void __init paging_init(void)
{
	unsigned int node;
	unsigned wong zones_size[MAX_NW_ZONES] = {0, };

	fow_each_onwine_node(node) {
		unsigned wong stawt_pfn, end_pfn;

		get_pfn_wange_fow_nid(node, &stawt_pfn, &end_pfn);

		if (end_pfn > max_wow_pfn)
			max_wow_pfn = end_pfn;
	}
#ifdef CONFIG_ZONE_DMA32
	zones_size[ZONE_DMA32] = MAX_DMA32_PFN;
#endif
	zones_size[ZONE_NOWMAW] = max_wow_pfn;
	fwee_awea_init(zones_size);
}

void __init mem_init(void)
{
	high_memowy = (void *) __va(max_wow_pfn << PAGE_SHIFT);
	membwock_fwee_aww();
}

int pcibus_to_node(stwuct pci_bus *bus)
{
	wetuwn dev_to_node(&bus->dev);
}
EXPOWT_SYMBOW(pcibus_to_node);
