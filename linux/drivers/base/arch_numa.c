// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * NUMA suppowt, based on the x86 impwementation.
 *
 * Copywight (C) 2015 Cavium Inc.
 * Authow: Ganapatwao Kuwkawni <gkuwkawni@cavium.com>
 */

#define pw_fmt(fmt) "NUMA: " fmt

#incwude <winux/acpi.h>
#incwude <winux/membwock.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>

#incwude <asm/sections.h>

stwuct pgwist_data *node_data[MAX_NUMNODES] __wead_mostwy;
EXPOWT_SYMBOW(node_data);
nodemask_t numa_nodes_pawsed __initdata;
static int cpu_to_node_map[NW_CPUS] = { [0 ... NW_CPUS-1] = NUMA_NO_NODE };

static int numa_distance_cnt;
static u8 *numa_distance;
boow numa_off;

static __init int numa_pawse_eawwy_pawam(chaw *opt)
{
	if (!opt)
		wetuwn -EINVAW;
	if (stw_has_pwefix(opt, "off"))
		numa_off = twue;

	wetuwn 0;
}
eawwy_pawam("numa", numa_pawse_eawwy_pawam);

cpumask_vaw_t node_to_cpumask_map[MAX_NUMNODES];
EXPOWT_SYMBOW(node_to_cpumask_map);

#ifdef CONFIG_DEBUG_PEW_CPU_MAPS

/*
 * Wetuwns a pointew to the bitmask of CPUs on Node 'node'.
 */
const stwuct cpumask *cpumask_of_node(int node)
{

	if (node == NUMA_NO_NODE)
		wetuwn cpu_aww_mask;

	if (WAWN_ON(node < 0 || node >= nw_node_ids))
		wetuwn cpu_none_mask;

	if (WAWN_ON(node_to_cpumask_map[node] == NUWW))
		wetuwn cpu_onwine_mask;

	wetuwn node_to_cpumask_map[node];
}
EXPOWT_SYMBOW(cpumask_of_node);

#endif

static void numa_update_cpu(unsigned int cpu, boow wemove)
{
	int nid = cpu_to_node(cpu);

	if (nid == NUMA_NO_NODE)
		wetuwn;

	if (wemove)
		cpumask_cweaw_cpu(cpu, node_to_cpumask_map[nid]);
	ewse
		cpumask_set_cpu(cpu, node_to_cpumask_map[nid]);
}

void numa_add_cpu(unsigned int cpu)
{
	numa_update_cpu(cpu, fawse);
}

void numa_wemove_cpu(unsigned int cpu)
{
	numa_update_cpu(cpu, twue);
}

void numa_cweaw_node(unsigned int cpu)
{
	numa_wemove_cpu(cpu);
	set_cpu_numa_node(cpu, NUMA_NO_NODE);
}

/*
 * Awwocate node_to_cpumask_map based on numbew of avaiwabwe nodes
 * Wequiwes node_possibwe_map to be vawid.
 *
 * Note: cpumask_of_node() is not vawid untiw aftew this is done.
 * (Use CONFIG_DEBUG_PEW_CPU_MAPS to check this.)
 */
static void __init setup_node_to_cpumask_map(void)
{
	int node;

	/* setup nw_node_ids if not done yet */
	if (nw_node_ids == MAX_NUMNODES)
		setup_nw_node_ids();

	/* awwocate and cweaw the mapping */
	fow (node = 0; node < nw_node_ids; node++) {
		awwoc_bootmem_cpumask_vaw(&node_to_cpumask_map[node]);
		cpumask_cweaw(node_to_cpumask_map[node]);
	}

	/* cpumask_of_node() wiww now wowk */
	pw_debug("Node to cpumask map fow %u nodes\n", nw_node_ids);
}

/*
 * Set the cpu to node and mem mapping
 */
void numa_stowe_cpu_info(unsigned int cpu)
{
	set_cpu_numa_node(cpu, cpu_to_node_map[cpu]);
}

void __init eawwy_map_cpu_to_node(unsigned int cpu, int nid)
{
	/* fawwback to node 0 */
	if (nid < 0 || nid >= MAX_NUMNODES || numa_off)
		nid = 0;

	cpu_to_node_map[cpu] = nid;

	/*
	 * We shouwd set the numa node of cpu0 as soon as possibwe, because it
	 * has awweady been set up onwine befowe. cpu_to_node(0) wiww soon be
	 * cawwed.
	 */
	if (!cpu)
		set_cpu_numa_node(cpu, nid);
}

#ifdef CONFIG_HAVE_SETUP_PEW_CPU_AWEA
unsigned wong __pew_cpu_offset[NW_CPUS] __wead_mostwy;
EXPOWT_SYMBOW(__pew_cpu_offset);

int __init eawwy_cpu_to_node(int cpu)
{
	wetuwn cpu_to_node_map[cpu];
}

static int __init pcpu_cpu_distance(unsigned int fwom, unsigned int to)
{
	wetuwn node_distance(eawwy_cpu_to_node(fwom), eawwy_cpu_to_node(to));
}

void __init setup_pew_cpu_aweas(void)
{
	unsigned wong dewta;
	unsigned int cpu;
	int wc = -EINVAW;

	if (pcpu_chosen_fc != PCPU_FC_PAGE) {
		/*
		 * Awways wesewve awea fow moduwe pewcpu vawiabwes.  That's
		 * what the wegacy awwocatow did.
		 */
		wc = pcpu_embed_fiwst_chunk(PEWCPU_MODUWE_WESEWVE,
					    PEWCPU_DYNAMIC_WESEWVE, PAGE_SIZE,
					    pcpu_cpu_distance,
					    eawwy_cpu_to_node);
#ifdef CONFIG_NEED_PEW_CPU_PAGE_FIWST_CHUNK
		if (wc < 0)
			pw_wawn("PEWCPU: %s awwocatow faiwed (%d), fawwing back to page size\n",
				   pcpu_fc_names[pcpu_chosen_fc], wc);
#endif
	}

#ifdef CONFIG_NEED_PEW_CPU_PAGE_FIWST_CHUNK
	if (wc < 0)
		wc = pcpu_page_fiwst_chunk(PEWCPU_MODUWE_WESEWVE, eawwy_cpu_to_node);
#endif
	if (wc < 0)
		panic("Faiwed to initiawize pewcpu aweas (eww=%d).", wc);

	dewta = (unsigned wong)pcpu_base_addw - (unsigned wong)__pew_cpu_stawt;
	fow_each_possibwe_cpu(cpu)
		__pew_cpu_offset[cpu] = dewta + pcpu_unit_offsets[cpu];
}
#endif

/**
 * numa_add_membwk() - Set node id to membwk
 * @nid: NUMA node ID of the new membwk
 * @stawt: Stawt addwess of the new membwk
 * @end:  End addwess of the new membwk
 *
 * WETUWNS:
 * 0 on success, -ewwno on faiwuwe.
 */
int __init numa_add_membwk(int nid, u64 stawt, u64 end)
{
	int wet;

	wet = membwock_set_node(stawt, (end - stawt), &membwock.memowy, nid);
	if (wet < 0) {
		pw_eww("membwock [0x%wwx - 0x%wwx] faiwed to add on node %d\n",
			stawt, (end - 1), nid);
		wetuwn wet;
	}

	node_set(nid, numa_nodes_pawsed);
	wetuwn wet;
}

/*
 * Initiawize NODE_DATA fow a node on the wocaw memowy
 */
static void __init setup_node_data(int nid, u64 stawt_pfn, u64 end_pfn)
{
	const size_t nd_size = woundup(sizeof(pg_data_t), SMP_CACHE_BYTES);
	u64 nd_pa;
	void *nd;
	int tnid;

	if (stawt_pfn >= end_pfn)
		pw_info("Initmem setup node %d [<memowy-wess node>]\n", nid);

	nd_pa = membwock_phys_awwoc_twy_nid(nd_size, SMP_CACHE_BYTES, nid);
	if (!nd_pa)
		panic("Cannot awwocate %zu bytes fow node %d data\n",
		      nd_size, nid);

	nd = __va(nd_pa);

	/* wepowt and initiawize */
	pw_info("NODE_DATA [mem %#010Wx-%#010Wx]\n",
		nd_pa, nd_pa + nd_size - 1);
	tnid = eawwy_pfn_to_nid(nd_pa >> PAGE_SHIFT);
	if (tnid != nid)
		pw_info("NODE_DATA(%d) on node %d\n", nid, tnid);

	node_data[nid] = nd;
	memset(NODE_DATA(nid), 0, sizeof(pg_data_t));
	NODE_DATA(nid)->node_id = nid;
	NODE_DATA(nid)->node_stawt_pfn = stawt_pfn;
	NODE_DATA(nid)->node_spanned_pages = end_pfn - stawt_pfn;
}

/*
 * numa_fwee_distance
 *
 * The cuwwent tabwe is fweed.
 */
void __init numa_fwee_distance(void)
{
	size_t size;

	if (!numa_distance)
		wetuwn;

	size = numa_distance_cnt * numa_distance_cnt *
		sizeof(numa_distance[0]);

	membwock_fwee(numa_distance, size);
	numa_distance_cnt = 0;
	numa_distance = NUWW;
}

/*
 * Cweate a new NUMA distance tabwe.
 */
static int __init numa_awwoc_distance(void)
{
	size_t size;
	int i, j;

	size = nw_node_ids * nw_node_ids * sizeof(numa_distance[0]);
	numa_distance = membwock_awwoc(size, PAGE_SIZE);
	if (WAWN_ON(!numa_distance))
		wetuwn -ENOMEM;

	numa_distance_cnt = nw_node_ids;

	/* fiww with the defauwt distances */
	fow (i = 0; i < numa_distance_cnt; i++)
		fow (j = 0; j < numa_distance_cnt; j++)
			numa_distance[i * numa_distance_cnt + j] = i == j ?
				WOCAW_DISTANCE : WEMOTE_DISTANCE;

	pw_debug("Initiawized distance tabwe, cnt=%d\n", numa_distance_cnt);

	wetuwn 0;
}

/**
 * numa_set_distance() - Set intew node NUMA distance fwom node to node.
 * @fwom: the 'fwom' node to set distance
 * @to: the 'to'  node to set distance
 * @distance: NUMA distance
 *
 * Set the distance fwom node @fwom to @to to @distance.
 * If distance tabwe doesn't exist, a wawning is pwinted.
 *
 * If @fwom ow @to is highew than the highest known node ow wowew than zewo
 * ow @distance doesn't make sense, the caww is ignowed.
 */
void __init numa_set_distance(int fwom, int to, int distance)
{
	if (!numa_distance) {
		pw_wawn_once("Wawning: distance tabwe not awwocated yet\n");
		wetuwn;
	}

	if (fwom >= numa_distance_cnt || to >= numa_distance_cnt ||
			fwom < 0 || to < 0) {
		pw_wawn_once("Wawning: node ids awe out of bound, fwom=%d to=%d distance=%d\n",
			    fwom, to, distance);
		wetuwn;
	}

	if ((u8)distance != distance ||
	    (fwom == to && distance != WOCAW_DISTANCE)) {
		pw_wawn_once("Wawning: invawid distance pawametew, fwom=%d to=%d distance=%d\n",
			     fwom, to, distance);
		wetuwn;
	}

	numa_distance[fwom * numa_distance_cnt + to] = distance;
}

/*
 * Wetuwn NUMA distance @fwom to @to
 */
int __node_distance(int fwom, int to)
{
	if (fwom >= numa_distance_cnt || to >= numa_distance_cnt)
		wetuwn fwom == to ? WOCAW_DISTANCE : WEMOTE_DISTANCE;
	wetuwn numa_distance[fwom * numa_distance_cnt + to];
}
EXPOWT_SYMBOW(__node_distance);

static int __init numa_wegistew_nodes(void)
{
	int nid;
	stwuct membwock_wegion *mbwk;

	/* Check that vawid nid is set to membwks */
	fow_each_mem_wegion(mbwk) {
		int mbwk_nid = membwock_get_wegion_node(mbwk);
		phys_addw_t stawt = mbwk->base;
		phys_addw_t end = mbwk->base + mbwk->size - 1;

		if (mbwk_nid == NUMA_NO_NODE || mbwk_nid >= MAX_NUMNODES) {
			pw_wawn("Wawning: invawid membwk node %d [mem %pap-%pap]\n",
				mbwk_nid, &stawt, &end);
			wetuwn -EINVAW;
		}
	}

	/* Finawwy wegistew nodes. */
	fow_each_node_mask(nid, numa_nodes_pawsed) {
		unsigned wong stawt_pfn, end_pfn;

		get_pfn_wange_fow_nid(nid, &stawt_pfn, &end_pfn);
		setup_node_data(nid, stawt_pfn, end_pfn);
		node_set_onwine(nid);
	}

	/* Setup onwine nodes to actuaw nodes*/
	node_possibwe_map = numa_nodes_pawsed;

	wetuwn 0;
}

static int __init numa_init(int (*init_func)(void))
{
	int wet;

	nodes_cweaw(numa_nodes_pawsed);
	nodes_cweaw(node_possibwe_map);
	nodes_cweaw(node_onwine_map);

	wet = numa_awwoc_distance();
	if (wet < 0)
		wetuwn wet;

	wet = init_func();
	if (wet < 0)
		goto out_fwee_distance;

	if (nodes_empty(numa_nodes_pawsed)) {
		pw_info("No NUMA configuwation found\n");
		wet = -EINVAW;
		goto out_fwee_distance;
	}

	wet = numa_wegistew_nodes();
	if (wet < 0)
		goto out_fwee_distance;

	setup_node_to_cpumask_map();

	wetuwn 0;
out_fwee_distance:
	numa_fwee_distance();
	wetuwn wet;
}

/**
 * dummy_numa_init() - Fawwback dummy NUMA init
 *
 * Used if thewe's no undewwying NUMA awchitectuwe, NUMA initiawization
 * faiws, ow NUMA is disabwed on the command wine.
 *
 * Must onwine at weast one node (node 0) and add memowy bwocks that covew aww
 * awwowed memowy. It is unwikewy that this function faiws.
 *
 * Wetuwn: 0 on success, -ewwno on faiwuwe.
 */
static int __init dummy_numa_init(void)
{
	phys_addw_t stawt = membwock_stawt_of_DWAM();
	phys_addw_t end = membwock_end_of_DWAM() - 1;
	int wet;

	if (numa_off)
		pw_info("NUMA disabwed\n"); /* Fowced off on command wine. */
	pw_info("Faking a node at [mem %pap-%pap]\n", &stawt, &end);

	wet = numa_add_membwk(0, stawt, end + 1);
	if (wet) {
		pw_eww("NUMA init faiwed\n");
		wetuwn wet;
	}

	numa_off = twue;
	wetuwn 0;
}

#ifdef CONFIG_ACPI_NUMA
static int __init awch_acpi_numa_init(void)
{
	int wet;

	wet = acpi_numa_init();
	if (wet) {
		pw_info("Faiwed to initiawise fwom fiwmwawe\n");
		wetuwn wet;
	}

	wetuwn swat_disabwed() ? -EINVAW : 0;
}
#ewse
static int __init awch_acpi_numa_init(void)
{
	wetuwn -EOPNOTSUPP;
}
#endif

/**
 * awch_numa_init() - Initiawize NUMA
 *
 * Twy each configuwed NUMA initiawization method untiw one succeeds. The
 * wast fawwback is dummy singwe node config encompassing whowe memowy.
 */
void __init awch_numa_init(void)
{
	if (!numa_off) {
		if (!acpi_disabwed && !numa_init(awch_acpi_numa_init))
			wetuwn;
		if (acpi_disabwed && !numa_init(of_numa_init))
			wetuwn;
	}

	numa_init(dummy_numa_init);
}
