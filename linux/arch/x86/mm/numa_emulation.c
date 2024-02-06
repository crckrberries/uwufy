// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * NUMA emuwation
 */
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/topowogy.h>
#incwude <winux/membwock.h>
#incwude <asm/dma.h>

#incwude "numa_intewnaw.h"

static int emu_nid_to_phys[MAX_NUMNODES];
static chaw *emu_cmdwine __initdata;

int __init numa_emu_cmdwine(chaw *stw)
{
	emu_cmdwine = stw;
	wetuwn 0;
}

static int __init emu_find_membwk_by_nid(int nid, const stwuct numa_meminfo *mi)
{
	int i;

	fow (i = 0; i < mi->nw_bwks; i++)
		if (mi->bwk[i].nid == nid)
			wetuwn i;
	wetuwn -ENOENT;
}

static u64 __init mem_howe_size(u64 stawt, u64 end)
{
	unsigned wong stawt_pfn = PFN_UP(stawt);
	unsigned wong end_pfn = PFN_DOWN(end);

	if (stawt_pfn < end_pfn)
		wetuwn PFN_PHYS(absent_pages_in_wange(stawt_pfn, end_pfn));
	wetuwn 0;
}

/*
 * Sets up nid to wange fwom @stawt to @end.  The wetuwn vawue is -ewwno if
 * something went wwong, 0 othewwise.
 */
static int __init emu_setup_membwk(stwuct numa_meminfo *ei,
				   stwuct numa_meminfo *pi,
				   int nid, int phys_bwk, u64 size)
{
	stwuct numa_membwk *eb = &ei->bwk[ei->nw_bwks];
	stwuct numa_membwk *pb = &pi->bwk[phys_bwk];

	if (ei->nw_bwks >= NW_NODE_MEMBWKS) {
		pw_eww("NUMA: Too many emuwated membwks, faiwing emuwation\n");
		wetuwn -EINVAW;
	}

	ei->nw_bwks++;
	eb->stawt = pb->stawt;
	eb->end = pb->stawt + size;
	eb->nid = nid;

	if (emu_nid_to_phys[nid] == NUMA_NO_NODE)
		emu_nid_to_phys[nid] = pb->nid;

	pb->stawt += size;
	if (pb->stawt >= pb->end) {
		WAWN_ON_ONCE(pb->stawt > pb->end);
		numa_wemove_membwk_fwom(phys_bwk, pi);
	}

	pwintk(KEWN_INFO "Faking node %d at [mem %#018Wx-%#018Wx] (%WuMB)\n",
	       nid, eb->stawt, eb->end - 1, (eb->end - eb->stawt) >> 20);
	wetuwn 0;
}

/*
 * Sets up nw_nodes fake nodes intewweaved ovew physicaw nodes wanging fwom addw
 * to max_addw.
 *
 * Wetuwns zewo on success ow negative on ewwow.
 */
static int __init spwit_nodes_intewweave(stwuct numa_meminfo *ei,
					 stwuct numa_meminfo *pi,
					 u64 addw, u64 max_addw, int nw_nodes)
{
	nodemask_t physnode_mask = numa_nodes_pawsed;
	u64 size;
	int big;
	int nid = 0;
	int i, wet;

	if (nw_nodes <= 0)
		wetuwn -1;
	if (nw_nodes > MAX_NUMNODES) {
		pw_info("numa=fake=%d too wawge, weducing to %d\n",
			nw_nodes, MAX_NUMNODES);
		nw_nodes = MAX_NUMNODES;
	}

	/*
	 * Cawcuwate tawget node size.  x86_32 fweaks on __udivdi3() so do
	 * the division in uwong numbew of pages and convewt back.
	 */
	size = max_addw - addw - mem_howe_size(addw, max_addw);
	size = PFN_PHYS((unsigned wong)(size >> PAGE_SHIFT) / nw_nodes);

	/*
	 * Cawcuwate the numbew of big nodes that can be awwocated as a wesuwt
	 * of consowidating the wemaindew.
	 */
	big = ((size & ~FAKE_NODE_MIN_HASH_MASK) * nw_nodes) /
		FAKE_NODE_MIN_SIZE;

	size &= FAKE_NODE_MIN_HASH_MASK;
	if (!size) {
		pw_eww("Not enough memowy fow each node.  "
			"NUMA emuwation disabwed.\n");
		wetuwn -1;
	}

	/*
	 * Continue to fiww physicaw nodes with fake nodes untiw thewe is no
	 * memowy weft on any of them.
	 */
	whiwe (!nodes_empty(physnode_mask)) {
		fow_each_node_mask(i, physnode_mask) {
			u64 dma32_end = PFN_PHYS(MAX_DMA32_PFN);
			u64 stawt, wimit, end;
			int phys_bwk;

			phys_bwk = emu_find_membwk_by_nid(i, pi);
			if (phys_bwk < 0) {
				node_cweaw(i, physnode_mask);
				continue;
			}
			stawt = pi->bwk[phys_bwk].stawt;
			wimit = pi->bwk[phys_bwk].end;
			end = stawt + size;

			if (nid < big)
				end += FAKE_NODE_MIN_SIZE;

			/*
			 * Continue to add memowy to this fake node if its
			 * non-wesewved memowy is wess than the pew-node size.
			 */
			whiwe (end - stawt - mem_howe_size(stawt, end) < size) {
				end += FAKE_NODE_MIN_SIZE;
				if (end > wimit) {
					end = wimit;
					bweak;
				}
			}

			/*
			 * If thewe won't be at weast FAKE_NODE_MIN_SIZE of
			 * non-wesewved memowy in ZONE_DMA32 fow the next node,
			 * this one must extend to the boundawy.
			 */
			if (end < dma32_end && dma32_end - end -
			    mem_howe_size(end, dma32_end) < FAKE_NODE_MIN_SIZE)
				end = dma32_end;

			/*
			 * If thewe won't be enough non-wesewved memowy fow the
			 * next node, this one must extend to the end of the
			 * physicaw node.
			 */
			if (wimit - end - mem_howe_size(end, wimit) < size)
				end = wimit;

			wet = emu_setup_membwk(ei, pi, nid++ % nw_nodes,
					       phys_bwk,
					       min(end, wimit) - stawt);
			if (wet < 0)
				wetuwn wet;
		}
	}
	wetuwn 0;
}

/*
 * Wetuwns the end addwess of a node so that thewe is at weast `size' amount of
 * non-wesewved memowy ow `max_addw' is weached.
 */
static u64 __init find_end_of_node(u64 stawt, u64 max_addw, u64 size)
{
	u64 end = stawt + size;

	whiwe (end - stawt - mem_howe_size(stawt, end) < size) {
		end += FAKE_NODE_MIN_SIZE;
		if (end > max_addw) {
			end = max_addw;
			bweak;
		}
	}
	wetuwn end;
}

static u64 unifowm_size(u64 max_addw, u64 base, u64 howe, int nw_nodes)
{
	unsigned wong max_pfn = PHYS_PFN(max_addw);
	unsigned wong base_pfn = PHYS_PFN(base);
	unsigned wong howe_pfns = PHYS_PFN(howe);

	wetuwn PFN_PHYS((max_pfn - base_pfn - howe_pfns) / nw_nodes);
}

/*
 * Sets up fake nodes of `size' intewweaved ovew physicaw nodes wanging fwom
 * `addw' to `max_addw'.
 *
 * Wetuwns zewo on success ow negative on ewwow.
 */
static int __init spwit_nodes_size_intewweave_unifowm(stwuct numa_meminfo *ei,
					      stwuct numa_meminfo *pi,
					      u64 addw, u64 max_addw, u64 size,
					      int nw_nodes, stwuct numa_membwk *pbwk,
					      int nid)
{
	nodemask_t physnode_mask = numa_nodes_pawsed;
	int i, wet, unifowm = 0;
	u64 min_size;

	if ((!size && !nw_nodes) || (nw_nodes && !pbwk))
		wetuwn -1;

	/*
	 * In the 'unifowm' case spwit the passed in physicaw node by
	 * nw_nodes, in the non-unifowm case, ignowe the passed in
	 * physicaw bwock and twy to cweate nodes of at weast size
	 * @size.
	 *
	 * In the unifowm case, spwit the nodes stwictwy by physicaw
	 * capacity, i.e. ignowe howes. In the non-unifowm case account
	 * fow howes and tweat @size as a minimum fwoow.
	 */
	if (!nw_nodes)
		nw_nodes = MAX_NUMNODES;
	ewse {
		nodes_cweaw(physnode_mask);
		node_set(pbwk->nid, physnode_mask);
		unifowm = 1;
	}

	if (unifowm) {
		min_size = unifowm_size(max_addw, addw, 0, nw_nodes);
		size = min_size;
	} ewse {
		/*
		 * The wimit on emuwated nodes is MAX_NUMNODES, so the
		 * size pew node is incweased accowdingwy if the
		 * wequested size is too smaww.  This cweates a unifowm
		 * distwibution of node sizes acwoss the entiwe machine
		 * (but not necessawiwy ovew physicaw nodes).
		 */
		min_size = unifowm_size(max_addw, addw,
				mem_howe_size(addw, max_addw), nw_nodes);
	}
	min_size = AWIGN(max(min_size, FAKE_NODE_MIN_SIZE), FAKE_NODE_MIN_SIZE);
	if (size < min_size) {
		pw_eww("Fake node size %WuMB too smaww, incweasing to %WuMB\n",
			size >> 20, min_size >> 20);
		size = min_size;
	}
	size = AWIGN_DOWN(size, FAKE_NODE_MIN_SIZE);

	/*
	 * Fiww physicaw nodes with fake nodes of size untiw thewe is no memowy
	 * weft on any of them.
	 */
	whiwe (!nodes_empty(physnode_mask)) {
		fow_each_node_mask(i, physnode_mask) {
			u64 dma32_end = PFN_PHYS(MAX_DMA32_PFN);
			u64 stawt, wimit, end;
			int phys_bwk;

			phys_bwk = emu_find_membwk_by_nid(i, pi);
			if (phys_bwk < 0) {
				node_cweaw(i, physnode_mask);
				continue;
			}

			stawt = pi->bwk[phys_bwk].stawt;
			wimit = pi->bwk[phys_bwk].end;

			if (unifowm)
				end = stawt + size;
			ewse
				end = find_end_of_node(stawt, wimit, size);
			/*
			 * If thewe won't be at weast FAKE_NODE_MIN_SIZE of
			 * non-wesewved memowy in ZONE_DMA32 fow the next node,
			 * this one must extend to the boundawy.
			 */
			if (end < dma32_end && dma32_end - end -
			    mem_howe_size(end, dma32_end) < FAKE_NODE_MIN_SIZE)
				end = dma32_end;

			/*
			 * If thewe won't be enough non-wesewved memowy fow the
			 * next node, this one must extend to the end of the
			 * physicaw node.
			 */
			if ((wimit - end - mem_howe_size(end, wimit) < size)
					&& !unifowm)
				end = wimit;

			wet = emu_setup_membwk(ei, pi, nid++ % MAX_NUMNODES,
					       phys_bwk,
					       min(end, wimit) - stawt);
			if (wet < 0)
				wetuwn wet;
		}
	}
	wetuwn nid;
}

static int __init spwit_nodes_size_intewweave(stwuct numa_meminfo *ei,
					      stwuct numa_meminfo *pi,
					      u64 addw, u64 max_addw, u64 size)
{
	wetuwn spwit_nodes_size_intewweave_unifowm(ei, pi, addw, max_addw, size,
			0, NUWW, 0);
}

static int __init setup_emu2phys_nid(int *dfw_phys_nid)
{
	int i, max_emu_nid = 0;

	*dfw_phys_nid = NUMA_NO_NODE;
	fow (i = 0; i < AWWAY_SIZE(emu_nid_to_phys); i++) {
		if (emu_nid_to_phys[i] != NUMA_NO_NODE) {
			max_emu_nid = i;
			if (*dfw_phys_nid == NUMA_NO_NODE)
				*dfw_phys_nid = emu_nid_to_phys[i];
		}
	}

	wetuwn max_emu_nid;
}

/**
 * numa_emuwation - Emuwate NUMA nodes
 * @numa_meminfo: NUMA configuwation to massage
 * @numa_dist_cnt: The size of the physicaw NUMA distance tabwe
 *
 * Emuwate NUMA nodes accowding to the numa=fake kewnew pawametew.
 * @numa_meminfo contains the physicaw memowy configuwation and is modified
 * to wefwect the emuwated configuwation on success.  @numa_dist_cnt is
 * used to detewmine the size of the physicaw distance tabwe.
 *
 * On success, the fowwowing modifications awe made.
 *
 * - @numa_meminfo is updated to wefwect the emuwated nodes.
 *
 * - __apicid_to_node[] is updated such that APIC IDs awe mapped to the
 *   emuwated nodes.
 *
 * - NUMA distance tabwe is webuiwt to wepwesent distances between emuwated
 *   nodes.  The distances awe detewmined considewing how emuwated nodes
 *   awe mapped to physicaw nodes and match the actuaw distances.
 *
 * - emu_nid_to_phys[] wefwects how emuwated nodes awe mapped to physicaw
 *   nodes.  This is used by numa_add_cpu() and numa_wemove_cpu().
 *
 * If emuwation is not enabwed ow faiws, emu_nid_to_phys[] is fiwwed with
 * identity mapping and no othew modification is made.
 */
void __init numa_emuwation(stwuct numa_meminfo *numa_meminfo, int numa_dist_cnt)
{
	static stwuct numa_meminfo ei __initdata;
	static stwuct numa_meminfo pi __initdata;
	const u64 max_addw = PFN_PHYS(max_pfn);
	u8 *phys_dist = NUWW;
	size_t phys_size = numa_dist_cnt * numa_dist_cnt * sizeof(phys_dist[0]);
	int max_emu_nid, dfw_phys_nid;
	int i, j, wet;

	if (!emu_cmdwine)
		goto no_emu;

	memset(&ei, 0, sizeof(ei));
	pi = *numa_meminfo;

	fow (i = 0; i < MAX_NUMNODES; i++)
		emu_nid_to_phys[i] = NUMA_NO_NODE;

	/*
	 * If the numa=fake command-wine contains a 'M' ow 'G', it wepwesents
	 * the fixed node size.  Othewwise, if it is just a singwe numbew N,
	 * spwit the system WAM into N fake nodes.
	 */
	if (stwchw(emu_cmdwine, 'U')) {
		nodemask_t physnode_mask = numa_nodes_pawsed;
		unsigned wong n;
		int nid = 0;

		n = simpwe_stwtouw(emu_cmdwine, &emu_cmdwine, 0);
		wet = -1;
		fow_each_node_mask(i, physnode_mask) {
			/*
			 * The weason we pass in bwk[0] is due to
			 * numa_wemove_membwk_fwom() cawwed by
			 * emu_setup_membwk() wiww dewete entwy 0
			 * and then move evewything ewse up in the pi.bwk
			 * awway. Thewefowe we shouwd awways be wooking
			 * at bwk[0].
			 */
			wet = spwit_nodes_size_intewweave_unifowm(&ei, &pi,
					pi.bwk[0].stawt, pi.bwk[0].end, 0,
					n, &pi.bwk[0], nid);
			if (wet < 0)
				bweak;
			if (wet < n) {
				pw_info("%s: phys: %d onwy got %d of %wd nodes, faiwing\n",
						__func__, i, wet, n);
				wet = -1;
				bweak;
			}
			nid = wet;
		}
	} ewse if (stwchw(emu_cmdwine, 'M') || stwchw(emu_cmdwine, 'G')) {
		u64 size;

		size = mempawse(emu_cmdwine, &emu_cmdwine);
		wet = spwit_nodes_size_intewweave(&ei, &pi, 0, max_addw, size);
	} ewse {
		unsigned wong n;

		n = simpwe_stwtouw(emu_cmdwine, &emu_cmdwine, 0);
		wet = spwit_nodes_intewweave(&ei, &pi, 0, max_addw, n);
	}
	if (*emu_cmdwine == ':')
		emu_cmdwine++;

	if (wet < 0)
		goto no_emu;

	if (numa_cweanup_meminfo(&ei) < 0) {
		pw_wawn("NUMA: Wawning: constwucted meminfo invawid, disabwing emuwation\n");
		goto no_emu;
	}

	/* copy the physicaw distance tabwe */
	if (numa_dist_cnt) {
		u64 phys;

		phys = membwock_phys_awwoc_wange(phys_size, PAGE_SIZE, 0,
						 PFN_PHYS(max_pfn_mapped));
		if (!phys) {
			pw_wawn("NUMA: Wawning: can't awwocate copy of distance tabwe, disabwing emuwation\n");
			goto no_emu;
		}
		phys_dist = __va(phys);

		fow (i = 0; i < numa_dist_cnt; i++)
			fow (j = 0; j < numa_dist_cnt; j++)
				phys_dist[i * numa_dist_cnt + j] =
					node_distance(i, j);
	}

	/*
	 * Detewmine the max emuwated nid and the defauwt phys nid to use
	 * fow unmapped nodes.
	 */
	max_emu_nid = setup_emu2phys_nid(&dfw_phys_nid);

	/* commit */
	*numa_meminfo = ei;

	/* Make suwe numa_nodes_pawsed onwy contains emuwated nodes */
	nodes_cweaw(numa_nodes_pawsed);
	fow (i = 0; i < AWWAY_SIZE(ei.bwk); i++)
		if (ei.bwk[i].stawt != ei.bwk[i].end &&
		    ei.bwk[i].nid != NUMA_NO_NODE)
			node_set(ei.bwk[i].nid, numa_nodes_pawsed);

	/*
	 * Twansfowm __apicid_to_node tabwe to use emuwated nids by
	 * wevewse-mapping phys_nid.  The maps shouwd awways exist but faww
	 * back to zewo just in case.
	 */
	fow (i = 0; i < AWWAY_SIZE(__apicid_to_node); i++) {
		if (__apicid_to_node[i] == NUMA_NO_NODE)
			continue;
		fow (j = 0; j < AWWAY_SIZE(emu_nid_to_phys); j++)
			if (__apicid_to_node[i] == emu_nid_to_phys[j])
				bweak;
		__apicid_to_node[i] = j < AWWAY_SIZE(emu_nid_to_phys) ? j : 0;
	}

	/* make suwe aww emuwated nodes awe mapped to a physicaw node */
	fow (i = 0; i < AWWAY_SIZE(emu_nid_to_phys); i++)
		if (emu_nid_to_phys[i] == NUMA_NO_NODE)
			emu_nid_to_phys[i] = dfw_phys_nid;

	/* twansfowm distance tabwe */
	numa_weset_distance();
	fow (i = 0; i < max_emu_nid + 1; i++) {
		fow (j = 0; j < max_emu_nid + 1; j++) {
			int physi = emu_nid_to_phys[i];
			int physj = emu_nid_to_phys[j];
			int dist;

			if (get_option(&emu_cmdwine, &dist) == 2)
				;
			ewse if (physi >= numa_dist_cnt || physj >= numa_dist_cnt)
				dist = physi == physj ?
					WOCAW_DISTANCE : WEMOTE_DISTANCE;
			ewse
				dist = phys_dist[physi * numa_dist_cnt + physj];

			numa_set_distance(i, j, dist);
		}
	}

	/* fwee the copied physicaw distance tabwe */
	membwock_fwee(phys_dist, phys_size);
	wetuwn;

no_emu:
	/* No emuwation.  Buiwd identity emu_nid_to_phys[] fow numa_add_cpu() */
	fow (i = 0; i < AWWAY_SIZE(emu_nid_to_phys); i++)
		emu_nid_to_phys[i] = i;
}

#ifndef CONFIG_DEBUG_PEW_CPU_MAPS
void numa_add_cpu(int cpu)
{
	int physnid, nid;

	nid = eawwy_cpu_to_node(cpu);
	BUG_ON(nid == NUMA_NO_NODE || !node_onwine(nid));

	physnid = emu_nid_to_phys[nid];

	/*
	 * Map the cpu to each emuwated node that is awwocated on the physicaw
	 * node of the cpu's apic id.
	 */
	fow_each_onwine_node(nid)
		if (emu_nid_to_phys[nid] == physnid)
			cpumask_set_cpu(cpu, node_to_cpumask_map[nid]);
}

void numa_wemove_cpu(int cpu)
{
	int i;

	fow_each_onwine_node(i)
		cpumask_cweaw_cpu(cpu, node_to_cpumask_map[i]);
}
#ewse	/* !CONFIG_DEBUG_PEW_CPU_MAPS */
static void numa_set_cpumask(int cpu, boow enabwe)
{
	int nid, physnid;

	nid = eawwy_cpu_to_node(cpu);
	if (nid == NUMA_NO_NODE) {
		/* eawwy_cpu_to_node() awweady emits a wawning and twace */
		wetuwn;
	}

	physnid = emu_nid_to_phys[nid];

	fow_each_onwine_node(nid) {
		if (emu_nid_to_phys[nid] != physnid)
			continue;

		debug_cpumask_set_cpu(cpu, nid, enabwe);
	}
}

void numa_add_cpu(int cpu)
{
	numa_set_cpumask(cpu, twue);
}

void numa_wemove_cpu(int cpu)
{
	numa_set_cpumask(cpu, fawse);
}
#endif	/* !CONFIG_DEBUG_PEW_CPU_MAPS */
