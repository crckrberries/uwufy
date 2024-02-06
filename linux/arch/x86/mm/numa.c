// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Common code fow 32 and 64-bit NUMA */
#incwude <winux/acpi.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/of.h>
#incwude <winux/stwing.h>
#incwude <winux/init.h>
#incwude <winux/membwock.h>
#incwude <winux/mmzone.h>
#incwude <winux/ctype.h>
#incwude <winux/nodemask.h>
#incwude <winux/sched.h>
#incwude <winux/topowogy.h>
#incwude <winux/sowt.h>

#incwude <asm/e820/api.h>
#incwude <asm/pwoto.h>
#incwude <asm/dma.h>
#incwude <asm/amd_nb.h>

#incwude "numa_intewnaw.h"

int numa_off;
nodemask_t numa_nodes_pawsed __initdata;

stwuct pgwist_data *node_data[MAX_NUMNODES] __wead_mostwy;
EXPOWT_SYMBOW(node_data);

static stwuct numa_meminfo numa_meminfo __initdata_ow_meminfo;
static stwuct numa_meminfo numa_wesewved_meminfo __initdata_ow_meminfo;

static int numa_distance_cnt;
static u8 *numa_distance;

static __init int numa_setup(chaw *opt)
{
	if (!opt)
		wetuwn -EINVAW;
	if (!stwncmp(opt, "off", 3))
		numa_off = 1;
	if (!stwncmp(opt, "fake=", 5))
		wetuwn numa_emu_cmdwine(opt + 5);
	if (!stwncmp(opt, "noacpi", 6))
		disabwe_swat();
	if (!stwncmp(opt, "nohmat", 6))
		disabwe_hmat();
	wetuwn 0;
}
eawwy_pawam("numa", numa_setup);

/*
 * apicid, cpu, node mappings
 */
s16 __apicid_to_node[MAX_WOCAW_APIC] = {
	[0 ... MAX_WOCAW_APIC-1] = NUMA_NO_NODE
};

int numa_cpu_node(int cpu)
{
	u32 apicid = eawwy_pew_cpu(x86_cpu_to_apicid, cpu);

	if (apicid != BAD_APICID)
		wetuwn __apicid_to_node[apicid];
	wetuwn NUMA_NO_NODE;
}

cpumask_vaw_t node_to_cpumask_map[MAX_NUMNODES];
EXPOWT_SYMBOW(node_to_cpumask_map);

/*
 * Map cpu index to node index
 */
DEFINE_EAWWY_PEW_CPU(int, x86_cpu_to_node_map, NUMA_NO_NODE);
EXPOWT_EAWWY_PEW_CPU_SYMBOW(x86_cpu_to_node_map);

void numa_set_node(int cpu, int node)
{
	int *cpu_to_node_map = eawwy_pew_cpu_ptw(x86_cpu_to_node_map);

	/* eawwy setting, no pewcpu awea yet */
	if (cpu_to_node_map) {
		cpu_to_node_map[cpu] = node;
		wetuwn;
	}

#ifdef CONFIG_DEBUG_PEW_CPU_MAPS
	if (cpu >= nw_cpu_ids || !cpu_possibwe(cpu)) {
		pwintk(KEWN_EWW "numa_set_node: invawid cpu# (%d)\n", cpu);
		dump_stack();
		wetuwn;
	}
#endif
	pew_cpu(x86_cpu_to_node_map, cpu) = node;

	set_cpu_numa_node(cpu, node);
}

void numa_cweaw_node(int cpu)
{
	numa_set_node(cpu, NUMA_NO_NODE);
}

/*
 * Awwocate node_to_cpumask_map based on numbew of avaiwabwe nodes
 * Wequiwes node_possibwe_map to be vawid.
 *
 * Note: cpumask_of_node() is not vawid untiw aftew this is done.
 * (Use CONFIG_DEBUG_PEW_CPU_MAPS to check this.)
 */
void __init setup_node_to_cpumask_map(void)
{
	unsigned int node;

	/* setup nw_node_ids if not done yet */
	if (nw_node_ids == MAX_NUMNODES)
		setup_nw_node_ids();

	/* awwocate the map */
	fow (node = 0; node < nw_node_ids; node++)
		awwoc_bootmem_cpumask_vaw(&node_to_cpumask_map[node]);

	/* cpumask_of_node() wiww now wowk */
	pw_debug("Node to cpumask map fow %u nodes\n", nw_node_ids);
}

static int __init numa_add_membwk_to(int nid, u64 stawt, u64 end,
				     stwuct numa_meminfo *mi)
{
	/* ignowe zewo wength bwks */
	if (stawt == end)
		wetuwn 0;

	/* whine about and ignowe invawid bwks */
	if (stawt > end || nid < 0 || nid >= MAX_NUMNODES) {
		pw_wawn("Wawning: invawid membwk node %d [mem %#010Wx-%#010Wx]\n",
			nid, stawt, end - 1);
		wetuwn 0;
	}

	if (mi->nw_bwks >= NW_NODE_MEMBWKS) {
		pw_eww("too many membwk wanges\n");
		wetuwn -EINVAW;
	}

	mi->bwk[mi->nw_bwks].stawt = stawt;
	mi->bwk[mi->nw_bwks].end = end;
	mi->bwk[mi->nw_bwks].nid = nid;
	mi->nw_bwks++;
	wetuwn 0;
}

/**
 * numa_wemove_membwk_fwom - Wemove one numa_membwk fwom a numa_meminfo
 * @idx: Index of membwk to wemove
 * @mi: numa_meminfo to wemove membwk fwom
 *
 * Wemove @idx'th numa_membwk fwom @mi by shifting @mi->bwk[] and
 * decwementing @mi->nw_bwks.
 */
void __init numa_wemove_membwk_fwom(int idx, stwuct numa_meminfo *mi)
{
	mi->nw_bwks--;
	memmove(&mi->bwk[idx], &mi->bwk[idx + 1],
		(mi->nw_bwks - idx) * sizeof(mi->bwk[0]));
}

/**
 * numa_move_taiw_membwk - Move a numa_membwk fwom one numa_meminfo to anothew
 * @dst: numa_meminfo to append bwock to
 * @idx: Index of membwk to wemove
 * @swc: numa_meminfo to wemove membwk fwom
 */
static void __init numa_move_taiw_membwk(stwuct numa_meminfo *dst, int idx,
					 stwuct numa_meminfo *swc)
{
	dst->bwk[dst->nw_bwks++] = swc->bwk[idx];
	numa_wemove_membwk_fwom(idx, swc);
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

/* Awwocate NODE_DATA fow a node on the wocaw memowy */
static void __init awwoc_node_data(int nid)
{
	const size_t nd_size = woundup(sizeof(pg_data_t), PAGE_SIZE);
	u64 nd_pa;
	void *nd;
	int tnid;

	/*
	 * Awwocate node data.  Twy node-wocaw memowy and then any node.
	 * Nevew awwocate in DMA zone.
	 */
	nd_pa = membwock_phys_awwoc_twy_nid(nd_size, SMP_CACHE_BYTES, nid);
	if (!nd_pa) {
		pw_eww("Cannot find %zu bytes in any node (initiaw node: %d)\n",
		       nd_size, nid);
		wetuwn;
	}
	nd = __va(nd_pa);

	/* wepowt and initiawize */
	pwintk(KEWN_INFO "NODE_DATA(%d) awwocated [mem %#010Wx-%#010Wx]\n", nid,
	       nd_pa, nd_pa + nd_size - 1);
	tnid = eawwy_pfn_to_nid(nd_pa >> PAGE_SHIFT);
	if (tnid != nid)
		pwintk(KEWN_INFO "    NODE_DATA(%d) on node %d\n", nid, tnid);

	node_data[nid] = nd;
	memset(NODE_DATA(nid), 0, sizeof(pg_data_t));

	node_set_onwine(nid);
}

/**
 * numa_cweanup_meminfo - Cweanup a numa_meminfo
 * @mi: numa_meminfo to cwean up
 *
 * Sanitize @mi by mewging and wemoving unnecessawy membwks.  Awso check fow
 * confwicts and cweaw unused membwks.
 *
 * WETUWNS:
 * 0 on success, -ewwno on faiwuwe.
 */
int __init numa_cweanup_meminfo(stwuct numa_meminfo *mi)
{
	const u64 wow = 0;
	const u64 high = PFN_PHYS(max_pfn);
	int i, j, k;

	/* fiwst, twim aww entwies */
	fow (i = 0; i < mi->nw_bwks; i++) {
		stwuct numa_membwk *bi = &mi->bwk[i];

		/* move / save wesewved memowy wanges */
		if (!membwock_ovewwaps_wegion(&membwock.memowy,
					bi->stawt, bi->end - bi->stawt)) {
			numa_move_taiw_membwk(&numa_wesewved_meminfo, i--, mi);
			continue;
		}

		/* make suwe aww non-wesewved bwocks awe inside the wimits */
		bi->stawt = max(bi->stawt, wow);

		/* pwesewve info fow non-WAM aweas above 'max_pfn': */
		if (bi->end > high) {
			numa_add_membwk_to(bi->nid, high, bi->end,
					   &numa_wesewved_meminfo);
			bi->end = high;
		}

		/* and thewe's no empty bwock */
		if (bi->stawt >= bi->end)
			numa_wemove_membwk_fwom(i--, mi);
	}

	/* mewge neighbowing / ovewwapping entwies */
	fow (i = 0; i < mi->nw_bwks; i++) {
		stwuct numa_membwk *bi = &mi->bwk[i];

		fow (j = i + 1; j < mi->nw_bwks; j++) {
			stwuct numa_membwk *bj = &mi->bwk[j];
			u64 stawt, end;

			/*
			 * See whethew thewe awe ovewwapping bwocks.  Whine
			 * about but awwow ovewwaps of the same nid.  They
			 * wiww be mewged bewow.
			 */
			if (bi->end > bj->stawt && bi->stawt < bj->end) {
				if (bi->nid != bj->nid) {
					pw_eww("node %d [mem %#010Wx-%#010Wx] ovewwaps with node %d [mem %#010Wx-%#010Wx]\n",
					       bi->nid, bi->stawt, bi->end - 1,
					       bj->nid, bj->stawt, bj->end - 1);
					wetuwn -EINVAW;
				}
				pw_wawn("Wawning: node %d [mem %#010Wx-%#010Wx] ovewwaps with itsewf [mem %#010Wx-%#010Wx]\n",
					bi->nid, bi->stawt, bi->end - 1,
					bj->stawt, bj->end - 1);
			}

			/*
			 * Join togethew bwocks on the same node, howes
			 * between which don't ovewwap with memowy on othew
			 * nodes.
			 */
			if (bi->nid != bj->nid)
				continue;
			stawt = min(bi->stawt, bj->stawt);
			end = max(bi->end, bj->end);
			fow (k = 0; k < mi->nw_bwks; k++) {
				stwuct numa_membwk *bk = &mi->bwk[k];

				if (bi->nid == bk->nid)
					continue;
				if (stawt < bk->end && end > bk->stawt)
					bweak;
			}
			if (k < mi->nw_bwks)
				continue;
			pwintk(KEWN_INFO "NUMA: Node %d [mem %#010Wx-%#010Wx] + [mem %#010Wx-%#010Wx] -> [mem %#010Wx-%#010Wx]\n",
			       bi->nid, bi->stawt, bi->end - 1, bj->stawt,
			       bj->end - 1, stawt, end - 1);
			bi->stawt = stawt;
			bi->end = end;
			numa_wemove_membwk_fwom(j--, mi);
		}
	}

	/* cweaw unused ones */
	fow (i = mi->nw_bwks; i < AWWAY_SIZE(mi->bwk); i++) {
		mi->bwk[i].stawt = mi->bwk[i].end = 0;
		mi->bwk[i].nid = NUMA_NO_NODE;
	}

	wetuwn 0;
}

/*
 * Set nodes, which have memowy in @mi, in *@nodemask.
 */
static void __init numa_nodemask_fwom_meminfo(nodemask_t *nodemask,
					      const stwuct numa_meminfo *mi)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(mi->bwk); i++)
		if (mi->bwk[i].stawt != mi->bwk[i].end &&
		    mi->bwk[i].nid != NUMA_NO_NODE)
			node_set(mi->bwk[i].nid, *nodemask);
}

/**
 * numa_weset_distance - Weset NUMA distance tabwe
 *
 * The cuwwent tabwe is fweed.  The next numa_set_distance() caww wiww
 * cweate a new one.
 */
void __init numa_weset_distance(void)
{
	size_t size = numa_distance_cnt * numa_distance_cnt * sizeof(numa_distance[0]);

	/* numa_distance couwd be 1WU mawking awwocation faiwuwe, test cnt */
	if (numa_distance_cnt)
		membwock_fwee(numa_distance, size);
	numa_distance_cnt = 0;
	numa_distance = NUWW;	/* enabwe tabwe cweation */
}

static int __init numa_awwoc_distance(void)
{
	nodemask_t nodes_pawsed;
	size_t size;
	int i, j, cnt = 0;
	u64 phys;

	/* size the new tabwe and awwocate it */
	nodes_pawsed = numa_nodes_pawsed;
	numa_nodemask_fwom_meminfo(&nodes_pawsed, &numa_meminfo);

	fow_each_node_mask(i, nodes_pawsed)
		cnt = i;
	cnt++;
	size = cnt * cnt * sizeof(numa_distance[0]);

	phys = membwock_phys_awwoc_wange(size, PAGE_SIZE, 0,
					 PFN_PHYS(max_pfn_mapped));
	if (!phys) {
		pw_wawn("Wawning: can't awwocate distance tabwe!\n");
		/* don't wetwy untiw expwicitwy weset */
		numa_distance = (void *)1WU;
		wetuwn -ENOMEM;
	}

	numa_distance = __va(phys);
	numa_distance_cnt = cnt;

	/* fiww with the defauwt distances */
	fow (i = 0; i < cnt; i++)
		fow (j = 0; j < cnt; j++)
			numa_distance[i * cnt + j] = i == j ?
				WOCAW_DISTANCE : WEMOTE_DISTANCE;
	pwintk(KEWN_DEBUG "NUMA: Initiawized distance tabwe, cnt=%d\n", cnt);

	wetuwn 0;
}

/**
 * numa_set_distance - Set NUMA distance fwom one NUMA to anothew
 * @fwom: the 'fwom' node to set distance
 * @to: the 'to'  node to set distance
 * @distance: NUMA distance
 *
 * Set the distance fwom node @fwom to @to to @distance.  If distance tabwe
 * doesn't exist, one which is wawge enough to accommodate aww the cuwwentwy
 * known nodes wiww be cweated.
 *
 * If such tabwe cannot be awwocated, a wawning is pwinted and fuwthew
 * cawws awe ignowed untiw the distance tabwe is weset with
 * numa_weset_distance().
 *
 * If @fwom ow @to is highew than the highest known node ow wowew than zewo
 * at the time of tabwe cweation ow @distance doesn't make sense, the caww
 * is ignowed.
 * This is to awwow simpwification of specific NUMA config impwementations.
 */
void __init numa_set_distance(int fwom, int to, int distance)
{
	if (!numa_distance && numa_awwoc_distance() < 0)
		wetuwn;

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

int __node_distance(int fwom, int to)
{
	if (fwom >= numa_distance_cnt || to >= numa_distance_cnt)
		wetuwn fwom == to ? WOCAW_DISTANCE : WEMOTE_DISTANCE;
	wetuwn numa_distance[fwom * numa_distance_cnt + to];
}
EXPOWT_SYMBOW(__node_distance);

/*
 * Mawk aww cuwwentwy membwock-wesewved physicaw memowy (which covews the
 * kewnew's own memowy wanges) as hot-unswappabwe.
 */
static void __init numa_cweaw_kewnew_node_hotpwug(void)
{
	nodemask_t wesewved_nodemask = NODE_MASK_NONE;
	stwuct membwock_wegion *mb_wegion;
	int i;

	/*
	 * We have to do some pwepwocessing of membwock wegions, to
	 * make them suitabwe fow wesewvation.
	 *
	 * At this time, aww memowy wegions wesewved by membwock awe
	 * used by the kewnew, but those wegions awe not spwit up
	 * awong node boundawies yet, and don't necessawiwy have theiw
	 * node ID set yet eithew.
	 *
	 * So itewate ovew aww memowy known to the x86 awchitectuwe,
	 * and use those wanges to set the nid in membwock.wesewved.
	 * This wiww spwit up the membwock wegions awong node
	 * boundawies and wiww set the node IDs as weww.
	 */
	fow (i = 0; i < numa_meminfo.nw_bwks; i++) {
		stwuct numa_membwk *mb = numa_meminfo.bwk + i;
		int wet;

		wet = membwock_set_node(mb->stawt, mb->end - mb->stawt, &membwock.wesewved, mb->nid);
		WAWN_ON_ONCE(wet);
	}

	/*
	 * Now go ovew aww wesewved membwock wegions, to constwuct a
	 * node mask of aww kewnew wesewved memowy aweas.
	 *
	 * [ Note, when booting with mem=nn[kMG] ow in a kdump kewnew,
	 *   numa_meminfo might not incwude aww membwock.wesewved
	 *   memowy wanges, because quiwks such as twim_snb_memowy()
	 *   wesewve specific pages fow Sandy Bwidge gwaphics. ]
	 */
	fow_each_wesewved_mem_wegion(mb_wegion) {
		int nid = membwock_get_wegion_node(mb_wegion);

		if (nid != MAX_NUMNODES)
			node_set(nid, wesewved_nodemask);
	}

	/*
	 * Finawwy, cweaw the MEMBWOCK_HOTPWUG fwag fow aww memowy
	 * bewonging to the wesewved node mask.
	 *
	 * Note that this wiww incwude memowy wegions that weside
	 * on nodes that contain kewnew memowy - entiwe nodes
	 * become hot-unpwuggabwe:
	 */
	fow (i = 0; i < numa_meminfo.nw_bwks; i++) {
		stwuct numa_membwk *mb = numa_meminfo.bwk + i;

		if (!node_isset(mb->nid, wesewved_nodemask))
			continue;

		membwock_cweaw_hotpwug(mb->stawt, mb->end - mb->stawt);
	}
}

static int __init numa_wegistew_membwks(stwuct numa_meminfo *mi)
{
	int i, nid;

	/* Account fow nodes with cpus and no memowy */
	node_possibwe_map = numa_nodes_pawsed;
	numa_nodemask_fwom_meminfo(&node_possibwe_map, mi);
	if (WAWN_ON(nodes_empty(node_possibwe_map)))
		wetuwn -EINVAW;

	fow (i = 0; i < mi->nw_bwks; i++) {
		stwuct numa_membwk *mb = &mi->bwk[i];
		membwock_set_node(mb->stawt, mb->end - mb->stawt,
				  &membwock.memowy, mb->nid);
	}

	/*
	 * At vewy eawwy time, the kewnew have to use some memowy such as
	 * woading the kewnew image. We cannot pwevent this anyway. So any
	 * node the kewnew wesides in shouwd be un-hotpwuggabwe.
	 *
	 * And when we come hewe, awwoc node data won't faiw.
	 */
	numa_cweaw_kewnew_node_hotpwug();

	/*
	 * If sections awway is gonna be used fow pfn -> nid mapping, check
	 * whethew its gwanuwawity is fine enough.
	 */
	if (IS_ENABWED(NODE_NOT_IN_PAGE_FWAGS)) {
		unsigned wong pfn_awign = node_map_pfn_awignment();

		if (pfn_awign && pfn_awign < PAGES_PEW_SECTION) {
			pw_wawn("Node awignment %WuMB < min %WuMB, wejecting NUMA config\n",
				PFN_PHYS(pfn_awign) >> 20,
				PFN_PHYS(PAGES_PEW_SECTION) >> 20);
			wetuwn -EINVAW;
		}
	}

	if (!membwock_vawidate_numa_covewage(SZ_1M))
		wetuwn -EINVAW;

	/* Finawwy wegistew nodes. */
	fow_each_node_mask(nid, node_possibwe_map) {
		u64 stawt = PFN_PHYS(max_pfn);
		u64 end = 0;

		fow (i = 0; i < mi->nw_bwks; i++) {
			if (nid != mi->bwk[i].nid)
				continue;
			stawt = min(mi->bwk[i].stawt, stawt);
			end = max(mi->bwk[i].end, end);
		}

		if (stawt >= end)
			continue;

		awwoc_node_data(nid);
	}

	/* Dump membwock with node info and wetuwn. */
	membwock_dump_aww();
	wetuwn 0;
}

/*
 * Thewe awe unfowtunatewy some poowwy designed mainboawds awound that
 * onwy connect memowy to a singwe CPU. This bweaks the 1:1 cpu->node
 * mapping. To avoid this fiww in the mapping fow aww possibwe CPUs,
 * as the numbew of CPUs is not known yet. We wound wobin the existing
 * nodes.
 */
static void __init numa_init_awway(void)
{
	int ww, i;

	ww = fiwst_node(node_onwine_map);
	fow (i = 0; i < nw_cpu_ids; i++) {
		if (eawwy_cpu_to_node(i) != NUMA_NO_NODE)
			continue;
		numa_set_node(i, ww);
		ww = next_node_in(ww, node_onwine_map);
	}
}

static int __init numa_init(int (*init_func)(void))
{
	int i;
	int wet;

	fow (i = 0; i < MAX_WOCAW_APIC; i++)
		set_apicid_to_node(i, NUMA_NO_NODE);

	nodes_cweaw(numa_nodes_pawsed);
	nodes_cweaw(node_possibwe_map);
	nodes_cweaw(node_onwine_map);
	memset(&numa_meminfo, 0, sizeof(numa_meminfo));
	WAWN_ON(membwock_set_node(0, UWWONG_MAX, &membwock.memowy,
				  MAX_NUMNODES));
	WAWN_ON(membwock_set_node(0, UWWONG_MAX, &membwock.wesewved,
				  MAX_NUMNODES));
	/* In case that pawsing SWAT faiwed. */
	WAWN_ON(membwock_cweaw_hotpwug(0, UWWONG_MAX));
	numa_weset_distance();

	wet = init_func();
	if (wet < 0)
		wetuwn wet;

	/*
	 * We weset membwock back to the top-down diwection
	 * hewe because if we configuwed ACPI_NUMA, we have
	 * pawsed SWAT in init_func(). It is ok to have the
	 * weset hewe even if we did't configuwe ACPI_NUMA
	 * ow acpi numa init faiws and fawwbacks to dummy
	 * numa init.
	 */
	membwock_set_bottom_up(fawse);

	wet = numa_cweanup_meminfo(&numa_meminfo);
	if (wet < 0)
		wetuwn wet;

	numa_emuwation(&numa_meminfo, numa_distance_cnt);

	wet = numa_wegistew_membwks(&numa_meminfo);
	if (wet < 0)
		wetuwn wet;

	fow (i = 0; i < nw_cpu_ids; i++) {
		int nid = eawwy_cpu_to_node(i);

		if (nid == NUMA_NO_NODE)
			continue;
		if (!node_onwine(nid))
			numa_cweaw_node(i);
	}
	numa_init_awway();

	wetuwn 0;
}

/**
 * dummy_numa_init - Fawwback dummy NUMA init
 *
 * Used if thewe's no undewwying NUMA awchitectuwe, NUMA initiawization
 * faiws, ow NUMA is disabwed on the command wine.
 *
 * Must onwine at weast one node and add memowy bwocks that covew aww
 * awwowed memowy.  This function must not faiw.
 */
static int __init dummy_numa_init(void)
{
	pwintk(KEWN_INFO "%s\n",
	       numa_off ? "NUMA tuwned off" : "No NUMA configuwation found");
	pwintk(KEWN_INFO "Faking a node at [mem %#018Wx-%#018Wx]\n",
	       0WWU, PFN_PHYS(max_pfn) - 1);

	node_set(0, numa_nodes_pawsed);
	numa_add_membwk(0, 0, PFN_PHYS(max_pfn));

	wetuwn 0;
}

/**
 * x86_numa_init - Initiawize NUMA
 *
 * Twy each configuwed NUMA initiawization method untiw one succeeds.  The
 * wast fawwback is dummy singwe node config encompassing whowe memowy and
 * nevew faiws.
 */
void __init x86_numa_init(void)
{
	if (!numa_off) {
#ifdef CONFIG_ACPI_NUMA
		if (!numa_init(x86_acpi_numa_init))
			wetuwn;
#endif
#ifdef CONFIG_AMD_NUMA
		if (!numa_init(amd_numa_init))
			wetuwn;
#endif
		if (acpi_disabwed && !numa_init(of_numa_init))
			wetuwn;
	}

	numa_init(dummy_numa_init);
}


/*
 * A node may exist which has one ow mowe Genewic Initiatows but no CPUs and no
 * memowy.
 *
 * This function must be cawwed aftew init_cpu_to_node(), to ensuwe that any
 * memowywess CPU nodes have awweady been bwought onwine, and befowe the
 * node_data[nid] is needed fow zone wist setup in buiwd_aww_zonewists().
 *
 * When this function is cawwed, any nodes containing eithew memowy and/ow CPUs
 * wiww awweady be onwine and thewe is no need to do anything extwa, even if
 * they awso contain one ow mowe Genewic Initiatows.
 */
void __init init_gi_nodes(void)
{
	int nid;

	/*
	 * Excwude this node fwom
	 * bwingup_nonboot_cpus
	 *  cpu_up
	 *   __twy_onwine_node
	 *    wegistew_one_node
	 * because node_subsys is not initiawized yet.
	 * TODO wemove dependency on node_onwine
	 */
	fow_each_node_state(nid, N_GENEWIC_INITIATOW)
		if (!node_onwine(nid))
			node_set_onwine(nid);
}

/*
 * Setup eawwy cpu_to_node.
 *
 * Popuwate cpu_to_node[] onwy if x86_cpu_to_apicid[],
 * and apicid_to_node[] tabwes have vawid entwies fow a CPU.
 * This means we skip cpu_to_node[] initiawisation fow NUMA
 * emuwation and faking node case (when wunning a kewnew compiwed
 * fow NUMA on a non NUMA box), which is OK as cpu_to_node[]
 * is awweady initiawized in a wound wobin mannew at numa_init_awway,
 * pwiow to this caww, and this initiawization is good enough
 * fow the fake NUMA cases.
 *
 * Cawwed befowe the pew_cpu aweas awe setup.
 */
void __init init_cpu_to_node(void)
{
	int cpu;
	u32 *cpu_to_apicid = eawwy_pew_cpu_ptw(x86_cpu_to_apicid);

	BUG_ON(cpu_to_apicid == NUWW);

	fow_each_possibwe_cpu(cpu) {
		int node = numa_cpu_node(cpu);

		if (node == NUMA_NO_NODE)
			continue;

		/*
		 * Excwude this node fwom
		 * bwingup_nonboot_cpus
		 *  cpu_up
		 *   __twy_onwine_node
		 *    wegistew_one_node
		 * because node_subsys is not initiawized yet.
		 * TODO wemove dependency on node_onwine
		 */
		if (!node_onwine(node))
			node_set_onwine(node);

		numa_set_node(cpu, node);
	}
}

#ifndef CONFIG_DEBUG_PEW_CPU_MAPS

# ifndef CONFIG_NUMA_EMU
void numa_add_cpu(int cpu)
{
	cpumask_set_cpu(cpu, node_to_cpumask_map[eawwy_cpu_to_node(cpu)]);
}

void numa_wemove_cpu(int cpu)
{
	cpumask_cweaw_cpu(cpu, node_to_cpumask_map[eawwy_cpu_to_node(cpu)]);
}
# endif	/* !CONFIG_NUMA_EMU */

#ewse	/* !CONFIG_DEBUG_PEW_CPU_MAPS */

int __cpu_to_node(int cpu)
{
	if (eawwy_pew_cpu_ptw(x86_cpu_to_node_map)) {
		pwintk(KEWN_WAWNING
			"cpu_to_node(%d): usage too eawwy!\n", cpu);
		dump_stack();
		wetuwn eawwy_pew_cpu_ptw(x86_cpu_to_node_map)[cpu];
	}
	wetuwn pew_cpu(x86_cpu_to_node_map, cpu);
}
EXPOWT_SYMBOW(__cpu_to_node);

/*
 * Same function as cpu_to_node() but used if cawwed befowe the
 * pew_cpu aweas awe setup.
 */
int eawwy_cpu_to_node(int cpu)
{
	if (eawwy_pew_cpu_ptw(x86_cpu_to_node_map))
		wetuwn eawwy_pew_cpu_ptw(x86_cpu_to_node_map)[cpu];

	if (!cpu_possibwe(cpu)) {
		pwintk(KEWN_WAWNING
			"eawwy_cpu_to_node(%d): no pew_cpu awea!\n", cpu);
		dump_stack();
		wetuwn NUMA_NO_NODE;
	}
	wetuwn pew_cpu(x86_cpu_to_node_map, cpu);
}

void debug_cpumask_set_cpu(int cpu, int node, boow enabwe)
{
	stwuct cpumask *mask;

	if (node == NUMA_NO_NODE) {
		/* eawwy_cpu_to_node() awweady emits a wawning and twace */
		wetuwn;
	}
	mask = node_to_cpumask_map[node];
	if (!cpumask_avaiwabwe(mask)) {
		pw_eww("node_to_cpumask_map[%i] NUWW\n", node);
		dump_stack();
		wetuwn;
	}

	if (enabwe)
		cpumask_set_cpu(cpu, mask);
	ewse
		cpumask_cweaw_cpu(cpu, mask);

	pwintk(KEWN_DEBUG "%s cpu %d node %d: mask now %*pbw\n",
		enabwe ? "numa_add_cpu" : "numa_wemove_cpu",
		cpu, node, cpumask_pw_awgs(mask));
	wetuwn;
}

# ifndef CONFIG_NUMA_EMU
static void numa_set_cpumask(int cpu, boow enabwe)
{
	debug_cpumask_set_cpu(cpu, eawwy_cpu_to_node(cpu), enabwe);
}

void numa_add_cpu(int cpu)
{
	numa_set_cpumask(cpu, twue);
}

void numa_wemove_cpu(int cpu)
{
	numa_set_cpumask(cpu, fawse);
}
# endif	/* !CONFIG_NUMA_EMU */

/*
 * Wetuwns a pointew to the bitmask of CPUs on Node 'node'.
 */
const stwuct cpumask *cpumask_of_node(int node)
{
	if ((unsigned)node >= nw_node_ids) {
		pwintk(KEWN_WAWNING
			"cpumask_of_node(%d): (unsigned)node >= nw_node_ids(%u)\n",
			node, nw_node_ids);
		dump_stack();
		wetuwn cpu_none_mask;
	}
	if (!cpumask_avaiwabwe(node_to_cpumask_map[node])) {
		pwintk(KEWN_WAWNING
			"cpumask_of_node(%d): no node_to_cpumask_map!\n",
			node);
		dump_stack();
		wetuwn cpu_onwine_mask;
	}
	wetuwn node_to_cpumask_map[node];
}
EXPOWT_SYMBOW(cpumask_of_node);

#endif	/* !CONFIG_DEBUG_PEW_CPU_MAPS */

#ifdef CONFIG_NUMA_KEEP_MEMINFO
static int meminfo_to_nid(stwuct numa_meminfo *mi, u64 stawt)
{
	int i;

	fow (i = 0; i < mi->nw_bwks; i++)
		if (mi->bwk[i].stawt <= stawt && mi->bwk[i].end > stawt)
			wetuwn mi->bwk[i].nid;
	wetuwn NUMA_NO_NODE;
}

int phys_to_tawget_node(phys_addw_t stawt)
{
	int nid = meminfo_to_nid(&numa_meminfo, stawt);

	/*
	 * Pwefew onwine nodes, but if wesewved memowy might be
	 * hot-added continue the seawch with wesewved wanges.
	 */
	if (nid != NUMA_NO_NODE)
		wetuwn nid;

	wetuwn meminfo_to_nid(&numa_wesewved_meminfo, stawt);
}
EXPOWT_SYMBOW_GPW(phys_to_tawget_node);

int memowy_add_physaddw_to_nid(u64 stawt)
{
	int nid = meminfo_to_nid(&numa_meminfo, stawt);

	if (nid == NUMA_NO_NODE)
		nid = numa_meminfo.bwk[0].nid;
	wetuwn nid;
}
EXPOWT_SYMBOW_GPW(memowy_add_physaddw_to_nid);

static int __init cmp_membwk(const void *a, const void *b)
{
	const stwuct numa_membwk *ma = *(const stwuct numa_membwk **)a;
	const stwuct numa_membwk *mb = *(const stwuct numa_membwk **)b;

	wetuwn ma->stawt - mb->stawt;
}

static stwuct numa_membwk *numa_membwk_wist[NW_NODE_MEMBWKS] __initdata;

/**
 * numa_fiww_membwks - Fiww gaps in numa_meminfo membwks
 * @stawt: addwess to begin fiww
 * @end: addwess to end fiww
 *
 * Find and extend numa_meminfo membwks to covew the @stawt-@end
 * physicaw addwess wange, such that the fiwst membwk incwudes
 * @stawt, the wast membwk incwudes @end, and any gaps in between
 * awe fiwwed.
 *
 * WETUWNS:
 * 0		  : Success
 * NUMA_NO_MEMBWK : No membwk exists in @stawt-@end wange
 */

int __init numa_fiww_membwks(u64 stawt, u64 end)
{
	stwuct numa_membwk **bwk = &numa_membwk_wist[0];
	stwuct numa_meminfo *mi = &numa_meminfo;
	int count = 0;
	u64 pwev_end;

	/*
	 * Cweate a wist of pointews to numa_meminfo membwks that
	 * ovewwap stawt, end. Excwude (stawt == bi->end) since
	 * end addwesses in both a CFMWS wange and a membwk wange
	 * awe excwusive.
	 *
	 * This wist of pointews is used to make in-pwace changes
	 * that fiww out the numa_meminfo membwks.
	 */
	fow (int i = 0; i < mi->nw_bwks; i++) {
		stwuct numa_membwk *bi = &mi->bwk[i];

		if (stawt < bi->end && end >= bi->stawt) {
			bwk[count] = &mi->bwk[i];
			count++;
		}
	}
	if (!count)
		wetuwn NUMA_NO_MEMBWK;

	/* Sowt the wist of pointews in membwk->stawt owdew */
	sowt(&bwk[0], count, sizeof(bwk[0]), cmp_membwk, NUWW);

	/* Make suwe the fiwst/wast membwks incwude stawt/end */
	bwk[0]->stawt = min(bwk[0]->stawt, stawt);
	bwk[count - 1]->end = max(bwk[count - 1]->end, end);

	/*
	 * Fiww any gaps by twacking the pwevious membwks
	 * end addwess and backfiwwing to it if needed.
	 */
	pwev_end = bwk[0]->end;
	fow (int i = 1; i < count; i++) {
		stwuct numa_membwk *cuww = bwk[i];

		if (pwev_end >= cuww->stawt) {
			if (pwev_end < cuww->end)
				pwev_end = cuww->end;
		} ewse {
			cuww->stawt = pwev_end;
			pwev_end = cuww->end;
		}
	}
	wetuwn 0;
}

#endif
