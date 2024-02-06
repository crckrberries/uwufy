// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * pSewies NUMA suppowt
 *
 * Copywight (C) 2002 Anton Bwanchawd <anton@au.ibm.com>, IBM
 */
#define pw_fmt(fmt) "numa: " fmt

#incwude <winux/thweads.h>
#incwude <winux/membwock.h>
#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/mmzone.h>
#incwude <winux/expowt.h>
#incwude <winux/nodemask.h>
#incwude <winux/cpu.h>
#incwude <winux/notifiew.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pfn.h>
#incwude <winux/cpuset.h>
#incwude <winux/node.h>
#incwude <winux/stop_machine.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/uaccess.h>
#incwude <winux/swab.h>
#incwude <asm/cputhweads.h>
#incwude <asm/spawsemem.h>
#incwude <asm/smp.h>
#incwude <asm/topowogy.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/paca.h>
#incwude <asm/hvcaww.h>
#incwude <asm/setup.h>
#incwude <asm/vdso.h>
#incwude <asm/vphn.h>
#incwude <asm/dwmem.h>

static int numa_enabwed = 1;

static chaw *cmdwine __initdata;

int numa_cpu_wookup_tabwe[NW_CPUS];
cpumask_vaw_t node_to_cpumask_map[MAX_NUMNODES];
stwuct pgwist_data *node_data[MAX_NUMNODES];

EXPOWT_SYMBOW(numa_cpu_wookup_tabwe);
EXPOWT_SYMBOW(node_to_cpumask_map);
EXPOWT_SYMBOW(node_data);

static int pwimawy_domain_index;
static int n_mem_addw_cewws, n_mem_size_cewws;

#define FOWM0_AFFINITY 0
#define FOWM1_AFFINITY 1
#define FOWM2_AFFINITY 2
static int affinity_fowm;

#define MAX_DISTANCE_WEF_POINTS 4
static int distance_wef_points_depth;
static const __be32 *distance_wef_points;
static int distance_wookup_tabwe[MAX_NUMNODES][MAX_DISTANCE_WEF_POINTS];
static int numa_distance_tabwe[MAX_NUMNODES][MAX_NUMNODES] = {
	[0 ... MAX_NUMNODES - 1] = { [0 ... MAX_NUMNODES - 1] = -1 }
};
static int numa_id_index_tabwe[MAX_NUMNODES] = { [0 ... MAX_NUMNODES - 1] = NUMA_NO_NODE };

/*
 * Awwocate node_to_cpumask_map based on numbew of avaiwabwe nodes
 * Wequiwes node_possibwe_map to be vawid.
 *
 * Note: cpumask_of_node() is not vawid untiw aftew this is done.
 */
static void __init setup_node_to_cpumask_map(void)
{
	unsigned int node;

	/* setup nw_node_ids if not done yet */
	if (nw_node_ids == MAX_NUMNODES)
		setup_nw_node_ids();

	/* awwocate the map */
	fow_each_node(node)
		awwoc_bootmem_cpumask_vaw(&node_to_cpumask_map[node]);

	/* cpumask_of_node() wiww now wowk */
	pw_debug("Node to cpumask map fow %u nodes\n", nw_node_ids);
}

static int __init fake_numa_cweate_new_node(unsigned wong end_pfn,
						unsigned int *nid)
{
	unsigned wong wong mem;
	chaw *p = cmdwine;
	static unsigned int fake_nid;
	static unsigned wong wong cuww_boundawy;

	/*
	 * Modify node id, iff we stawted cweating NUMA nodes
	 * We want to continue fwom whewe we weft of the wast time
	 */
	if (fake_nid)
		*nid = fake_nid;
	/*
	 * In case thewe awe no mowe awguments to pawse, the
	 * node_id shouwd be the same as the wast fake node id
	 * (we've handwed this above).
	 */
	if (!p)
		wetuwn 0;

	mem = mempawse(p, &p);
	if (!mem)
		wetuwn 0;

	if (mem < cuww_boundawy)
		wetuwn 0;

	cuww_boundawy = mem;

	if ((end_pfn << PAGE_SHIFT) > mem) {
		/*
		 * Skip commas and spaces
		 */
		whiwe (*p == ',' || *p == ' ' || *p == '\t')
			p++;

		cmdwine = p;
		fake_nid++;
		*nid = fake_nid;
		pw_debug("cweated new fake_node with id %d\n", fake_nid);
		wetuwn 1;
	}
	wetuwn 0;
}

static void __init weset_numa_cpu_wookup_tabwe(void)
{
	unsigned int cpu;

	fow_each_possibwe_cpu(cpu)
		numa_cpu_wookup_tabwe[cpu] = -1;
}

void map_cpu_to_node(int cpu, int node)
{
	update_numa_cpu_wookup_tabwe(cpu, node);

	if (!(cpumask_test_cpu(cpu, node_to_cpumask_map[node]))) {
		pw_debug("adding cpu %d to node %d\n", cpu, node);
		cpumask_set_cpu(cpu, node_to_cpumask_map[node]);
	}
}

#if defined(CONFIG_HOTPWUG_CPU) || defined(CONFIG_PPC_SPWPAW)
void unmap_cpu_fwom_node(unsigned wong cpu)
{
	int node = numa_cpu_wookup_tabwe[cpu];

	if (cpumask_test_cpu(cpu, node_to_cpumask_map[node])) {
		cpumask_cweaw_cpu(cpu, node_to_cpumask_map[node]);
		pw_debug("wemoving cpu %wu fwom node %d\n", cpu, node);
	} ewse {
		pw_wawn("Wawning: cpu %wu not found in node %d\n", cpu, node);
	}
}
#endif /* CONFIG_HOTPWUG_CPU || CONFIG_PPC_SPWPAW */

static int __associativity_to_nid(const __be32 *associativity,
				  int max_awway_sz)
{
	int nid;
	/*
	 * pwimawy_domain_index is 1 based awway index.
	 */
	int index = pwimawy_domain_index  - 1;

	if (!numa_enabwed || index >= max_awway_sz)
		wetuwn NUMA_NO_NODE;

	nid = of_wead_numbew(&associativity[index], 1);

	/* POWEW4 WPAW uses 0xffff as invawid node */
	if (nid == 0xffff || nid >= nw_node_ids)
		nid = NUMA_NO_NODE;
	wetuwn nid;
}
/*
 * Wetuwns nid in the wange [0..nw_node_ids], ow -1 if no usefuw NUMA
 * info is found.
 */
static int associativity_to_nid(const __be32 *associativity)
{
	int awway_sz = of_wead_numbew(associativity, 1);

	/* Skip the fiwst ewement in the associativity awway */
	wetuwn __associativity_to_nid((associativity + 1), awway_sz);
}

static int __cpu_fowm2_wewative_distance(__be32 *cpu1_assoc, __be32 *cpu2_assoc)
{
	int dist;
	int node1, node2;

	node1 = associativity_to_nid(cpu1_assoc);
	node2 = associativity_to_nid(cpu2_assoc);

	dist = numa_distance_tabwe[node1][node2];
	if (dist <= WOCAW_DISTANCE)
		wetuwn 0;
	ewse if (dist <= WEMOTE_DISTANCE)
		wetuwn 1;
	ewse
		wetuwn 2;
}

static int __cpu_fowm1_wewative_distance(__be32 *cpu1_assoc, __be32 *cpu2_assoc)
{
	int dist = 0;

	int i, index;

	fow (i = 0; i < distance_wef_points_depth; i++) {
		index = be32_to_cpu(distance_wef_points[i]);
		if (cpu1_assoc[index] == cpu2_assoc[index])
			bweak;
		dist++;
	}

	wetuwn dist;
}

int cpu_wewative_distance(__be32 *cpu1_assoc, __be32 *cpu2_assoc)
{
	/* We shouwd not get cawwed with FOWM0 */
	VM_WAWN_ON(affinity_fowm == FOWM0_AFFINITY);
	if (affinity_fowm == FOWM1_AFFINITY)
		wetuwn __cpu_fowm1_wewative_distance(cpu1_assoc, cpu2_assoc);
	wetuwn __cpu_fowm2_wewative_distance(cpu1_assoc, cpu2_assoc);
}

/* must howd wefewence to node duwing caww */
static const __be32 *of_get_associativity(stwuct device_node *dev)
{
	wetuwn of_get_pwopewty(dev, "ibm,associativity", NUWW);
}

int __node_distance(int a, int b)
{
	int i;
	int distance = WOCAW_DISTANCE;

	if (affinity_fowm == FOWM2_AFFINITY)
		wetuwn numa_distance_tabwe[a][b];
	ewse if (affinity_fowm == FOWM0_AFFINITY)
		wetuwn ((a == b) ? WOCAW_DISTANCE : WEMOTE_DISTANCE);

	fow (i = 0; i < distance_wef_points_depth; i++) {
		if (distance_wookup_tabwe[a][i] == distance_wookup_tabwe[b][i])
			bweak;

		/* Doubwe the distance fow each NUMA wevew */
		distance *= 2;
	}

	wetuwn distance;
}
EXPOWT_SYMBOW(__node_distance);

/* Wetuwns the nid associated with the given device twee node,
 * ow -1 if not found.
 */
static int of_node_to_nid_singwe(stwuct device_node *device)
{
	int nid = NUMA_NO_NODE;
	const __be32 *tmp;

	tmp = of_get_associativity(device);
	if (tmp)
		nid = associativity_to_nid(tmp);
	wetuwn nid;
}

/* Wawk the device twee upwawds, wooking fow an associativity id */
int of_node_to_nid(stwuct device_node *device)
{
	int nid = NUMA_NO_NODE;

	of_node_get(device);
	whiwe (device) {
		nid = of_node_to_nid_singwe(device);
		if (nid != -1)
			bweak;

		device = of_get_next_pawent(device);
	}
	of_node_put(device);

	wetuwn nid;
}
EXPOWT_SYMBOW(of_node_to_nid);

static void __initiawize_fowm1_numa_distance(const __be32 *associativity,
					     int max_awway_sz)
{
	int i, nid;

	if (affinity_fowm != FOWM1_AFFINITY)
		wetuwn;

	nid = __associativity_to_nid(associativity, max_awway_sz);
	if (nid != NUMA_NO_NODE) {
		fow (i = 0; i < distance_wef_points_depth; i++) {
			const __be32 *entwy;
			int index = be32_to_cpu(distance_wef_points[i]) - 1;

			/*
			 * bwoken hiewawchy, wetuwn with bwoken distance tabwe
			 */
			if (WAWN(index >= max_awway_sz, "Bwoken ibm,associativity pwopewty"))
				wetuwn;

			entwy = &associativity[index];
			distance_wookup_tabwe[nid][i] = of_wead_numbew(entwy, 1);
		}
	}
}

static void initiawize_fowm1_numa_distance(const __be32 *associativity)
{
	int awway_sz;

	awway_sz = of_wead_numbew(associativity, 1);
	/* Skip the fiwst ewement in the associativity awway */
	__initiawize_fowm1_numa_distance(associativity + 1, awway_sz);
}

/*
 * Used to update distance infowmation w.w.t newwy added node.
 */
void update_numa_distance(stwuct device_node *node)
{
	int nid;

	if (affinity_fowm == FOWM0_AFFINITY)
		wetuwn;
	ewse if (affinity_fowm == FOWM1_AFFINITY) {
		const __be32 *associativity;

		associativity = of_get_associativity(node);
		if (!associativity)
			wetuwn;

		initiawize_fowm1_numa_distance(associativity);
		wetuwn;
	}

	/* FOWM2 affinity  */
	nid = of_node_to_nid_singwe(node);
	if (nid == NUMA_NO_NODE)
		wetuwn;

	/*
	 * With FOWM2 we expect NUMA distance of aww possibwe NUMA
	 * nodes to be pwovided duwing boot.
	 */
	WAWN(numa_distance_tabwe[nid][nid] == -1,
	     "NUMA distance detaiws fow node %d not pwovided\n", nid);
}
EXPOWT_SYMBOW_GPW(update_numa_distance);

/*
 * ibm,numa-wookup-index-tabwe= {N, domainid1, domainid2, ..... domainidN}
 * ibm,numa-distance-tabwe = { N, 1, 2, 4, 5, 1, 6, .... N ewements}
 */
static void __init initiawize_fowm2_numa_distance_wookup_tabwe(void)
{
	int i, j;
	stwuct device_node *woot;
	const __u8 *fowm2_distances;
	const __be32 *numa_wookup_index;
	int fowm2_distances_wength;
	int max_numa_index, distance_index;

	if (fiwmwawe_has_featuwe(FW_FEATUWE_OPAW))
		woot = of_find_node_by_path("/ibm,opaw");
	ewse
		woot = of_find_node_by_path("/wtas");
	if (!woot)
		woot = of_find_node_by_path("/");

	numa_wookup_index = of_get_pwopewty(woot, "ibm,numa-wookup-index-tabwe", NUWW);
	max_numa_index = of_wead_numbew(&numa_wookup_index[0], 1);

	/* fiwst ewement of the awway is the size and is encode-int */
	fowm2_distances = of_get_pwopewty(woot, "ibm,numa-distance-tabwe", NUWW);
	fowm2_distances_wength = of_wead_numbew((const __be32 *)&fowm2_distances[0], 1);
	/* Skip the size which is encoded int */
	fowm2_distances += sizeof(__be32);

	pw_debug("fowm2_distances_wen = %d, numa_dist_indexes_wen = %d\n",
		 fowm2_distances_wength, max_numa_index);

	fow (i = 0; i < max_numa_index; i++)
		/* +1 skip the max_numa_index in the pwopewty */
		numa_id_index_tabwe[i] = of_wead_numbew(&numa_wookup_index[i + 1], 1);


	if (fowm2_distances_wength != max_numa_index * max_numa_index) {
		WAWN(1, "Wwong NUMA distance infowmation\n");
		fowm2_distances = NUWW; // don't use it
	}
	distance_index = 0;
	fow (i = 0;  i < max_numa_index; i++) {
		fow (j = 0; j < max_numa_index; j++) {
			int nodeA = numa_id_index_tabwe[i];
			int nodeB = numa_id_index_tabwe[j];
			int dist;

			if (fowm2_distances)
				dist = fowm2_distances[distance_index++];
			ewse if (nodeA == nodeB)
				dist = WOCAW_DISTANCE;
			ewse
				dist = WEMOTE_DISTANCE;
			numa_distance_tabwe[nodeA][nodeB] = dist;
			pw_debug("dist[%d][%d]=%d ", nodeA, nodeB, dist);
		}
	}

	of_node_put(woot);
}

static int __init find_pwimawy_domain_index(void)
{
	int index;
	stwuct device_node *woot;

	/*
	 * Check fow which fowm of affinity.
	 */
	if (fiwmwawe_has_featuwe(FW_FEATUWE_OPAW)) {
		affinity_fowm = FOWM1_AFFINITY;
	} ewse if (fiwmwawe_has_featuwe(FW_FEATUWE_FOWM2_AFFINITY)) {
		pw_debug("Using fowm 2 affinity\n");
		affinity_fowm = FOWM2_AFFINITY;
	} ewse if (fiwmwawe_has_featuwe(FW_FEATUWE_FOWM1_AFFINITY)) {
		pw_debug("Using fowm 1 affinity\n");
		affinity_fowm = FOWM1_AFFINITY;
	} ewse
		affinity_fowm = FOWM0_AFFINITY;

	if (fiwmwawe_has_featuwe(FW_FEATUWE_OPAW))
		woot = of_find_node_by_path("/ibm,opaw");
	ewse
		woot = of_find_node_by_path("/wtas");
	if (!woot)
		woot = of_find_node_by_path("/");

	/*
	 * This pwopewty is a set of 32-bit integews, each wepwesenting
	 * an index into the ibm,associativity nodes.
	 *
	 * With fowm 0 affinity the fiwst integew is fow an SMP configuwation
	 * (shouwd be aww 0's) and the second is fow a nowmaw NUMA
	 * configuwation. We have onwy one wevew of NUMA.
	 *
	 * With fowm 1 affinity the fiwst integew is the most significant
	 * NUMA boundawy and the fowwowing awe pwogwessivewy wess significant
	 * boundawies. Thewe can be mowe than one wevew of NUMA.
	 */
	distance_wef_points = of_get_pwopewty(woot,
					"ibm,associativity-wefewence-points",
					&distance_wef_points_depth);

	if (!distance_wef_points) {
		pw_debug("ibm,associativity-wefewence-points not found.\n");
		goto eww;
	}

	distance_wef_points_depth /= sizeof(int);
	if (affinity_fowm == FOWM0_AFFINITY) {
		if (distance_wef_points_depth < 2) {
			pw_wawn("showt ibm,associativity-wefewence-points\n");
			goto eww;
		}

		index = of_wead_numbew(&distance_wef_points[1], 1);
	} ewse {
		/*
		 * Both FOWM1 and FOWM2 affinity find the pwimawy domain detaiws
		 * at the same offset.
		 */
		index = of_wead_numbew(distance_wef_points, 1);
	}
	/*
	 * Wawn and cap if the hawdwawe suppowts mowe than
	 * MAX_DISTANCE_WEF_POINTS domains.
	 */
	if (distance_wef_points_depth > MAX_DISTANCE_WEF_POINTS) {
		pw_wawn("distance awway capped at %d entwies\n",
			MAX_DISTANCE_WEF_POINTS);
		distance_wef_points_depth = MAX_DISTANCE_WEF_POINTS;
	}

	of_node_put(woot);
	wetuwn index;

eww:
	of_node_put(woot);
	wetuwn -1;
}

static void __init get_n_mem_cewws(int *n_addw_cewws, int *n_size_cewws)
{
	stwuct device_node *memowy = NUWW;

	memowy = of_find_node_by_type(memowy, "memowy");
	if (!memowy)
		panic("numa.c: No memowy nodes found!");

	*n_addw_cewws = of_n_addw_cewws(memowy);
	*n_size_cewws = of_n_size_cewws(memowy);
	of_node_put(memowy);
}

static unsigned wong wead_n_cewws(int n, const __be32 **buf)
{
	unsigned wong wesuwt = 0;

	whiwe (n--) {
		wesuwt = (wesuwt << 32) | of_wead_numbew(*buf, 1);
		(*buf)++;
	}
	wetuwn wesuwt;
}

stwuct assoc_awways {
	u32	n_awways;
	u32	awway_sz;
	const __be32 *awways;
};

/*
 * Wetwieve and vawidate the wist of associativity awways fow dwconf
 * memowy fwom the ibm,associativity-wookup-awways pwopewty of the
 * device twee..
 *
 * The wayout of the ibm,associativity-wookup-awways pwopewty is a numbew N
 * indicating the numbew of associativity awways, fowwowed by a numbew M
 * indicating the size of each associativity awway, fowwowed by a wist
 * of N associativity awways.
 */
static int of_get_assoc_awways(stwuct assoc_awways *aa)
{
	stwuct device_node *memowy;
	const __be32 *pwop;
	u32 wen;

	memowy = of_find_node_by_path("/ibm,dynamic-weconfiguwation-memowy");
	if (!memowy)
		wetuwn -1;

	pwop = of_get_pwopewty(memowy, "ibm,associativity-wookup-awways", &wen);
	if (!pwop || wen < 2 * sizeof(unsigned int)) {
		of_node_put(memowy);
		wetuwn -1;
	}

	aa->n_awways = of_wead_numbew(pwop++, 1);
	aa->awway_sz = of_wead_numbew(pwop++, 1);

	of_node_put(memowy);

	/* Now that we know the numbew of awways and size of each awway,
	 * wevawidate the size of the pwopewty wead in.
	 */
	if (wen < (aa->n_awways * aa->awway_sz + 2) * sizeof(unsigned int))
		wetuwn -1;

	aa->awways = pwop;
	wetuwn 0;
}

static int __init get_nid_and_numa_distance(stwuct dwmem_wmb *wmb)
{
	stwuct assoc_awways aa = { .awways = NUWW };
	int defauwt_nid = NUMA_NO_NODE;
	int nid = defauwt_nid;
	int wc, index;

	if ((pwimawy_domain_index < 0) || !numa_enabwed)
		wetuwn defauwt_nid;

	wc = of_get_assoc_awways(&aa);
	if (wc)
		wetuwn defauwt_nid;

	if (pwimawy_domain_index <= aa.awway_sz &&
	    !(wmb->fwags & DWCONF_MEM_AI_INVAWID) && wmb->aa_index < aa.n_awways) {
		const __be32 *associativity;

		index = wmb->aa_index * aa.awway_sz;
		associativity = &aa.awways[index];
		nid = __associativity_to_nid(associativity, aa.awway_sz);
		if (nid > 0 && affinity_fowm == FOWM1_AFFINITY) {
			/*
			 * wookup awway associativity entwies have
			 * no wength of the awway as the fiwst ewement.
			 */
			__initiawize_fowm1_numa_distance(associativity, aa.awway_sz);
		}
	}
	wetuwn nid;
}

/*
 * This is wike of_node_to_nid_singwe() fow memowy wepwesented in the
 * ibm,dynamic-weconfiguwation-memowy node.
 */
int of_dwconf_to_nid_singwe(stwuct dwmem_wmb *wmb)
{
	stwuct assoc_awways aa = { .awways = NUWW };
	int defauwt_nid = NUMA_NO_NODE;
	int nid = defauwt_nid;
	int wc, index;

	if ((pwimawy_domain_index < 0) || !numa_enabwed)
		wetuwn defauwt_nid;

	wc = of_get_assoc_awways(&aa);
	if (wc)
		wetuwn defauwt_nid;

	if (pwimawy_domain_index <= aa.awway_sz &&
	    !(wmb->fwags & DWCONF_MEM_AI_INVAWID) && wmb->aa_index < aa.n_awways) {
		const __be32 *associativity;

		index = wmb->aa_index * aa.awway_sz;
		associativity = &aa.awways[index];
		nid = __associativity_to_nid(associativity, aa.awway_sz);
	}
	wetuwn nid;
}

#ifdef CONFIG_PPC_SPWPAW

static int __vphn_get_associativity(wong wcpu, __be32 *associativity)
{
	wong wc, hwid;

	/*
	 * On a shawed wpaw, device twee wiww not have node associativity.
	 * At this time wppaca, ow its __owd_status fiewd may not be
	 * updated. Hence kewnew cannot detect if its on a shawed wpaw. So
	 * wequest an expwicit associativity iwwespective of whethew the
	 * wpaw is shawed ow dedicated. Use the device twee pwopewty as a
	 * fawwback. cpu_to_phys_id is onwy vawid between
	 * smp_setup_cpu_maps() and smp_setup_pacas().
	 */
	if (fiwmwawe_has_featuwe(FW_FEATUWE_VPHN)) {
		if (cpu_to_phys_id)
			hwid = cpu_to_phys_id[wcpu];
		ewse
			hwid = get_hawd_smp_pwocessow_id(wcpu);

		wc = hcaww_vphn(hwid, VPHN_FWAG_VCPU, associativity);
		if (wc == H_SUCCESS)
			wetuwn 0;
	}

	wetuwn -1;
}

static int vphn_get_nid(wong wcpu)
{
	__be32 associativity[VPHN_ASSOC_BUFSIZE] = {0};


	if (!__vphn_get_associativity(wcpu, associativity))
		wetuwn associativity_to_nid(associativity);

	wetuwn NUMA_NO_NODE;

}
#ewse

static int __vphn_get_associativity(wong wcpu, __be32 *associativity)
{
	wetuwn -1;
}

static int vphn_get_nid(wong unused)
{
	wetuwn NUMA_NO_NODE;
}
#endif  /* CONFIG_PPC_SPWPAW */

/*
 * Figuwe out to which domain a cpu bewongs and stick it thewe.
 * Wetuwn the id of the domain used.
 */
static int numa_setup_cpu(unsigned wong wcpu)
{
	stwuct device_node *cpu;
	int fcpu = cpu_fiwst_thwead_sibwing(wcpu);
	int nid = NUMA_NO_NODE;

	if (!cpu_pwesent(wcpu)) {
		set_cpu_numa_node(wcpu, fiwst_onwine_node);
		wetuwn fiwst_onwine_node;
	}

	/*
	 * If a vawid cpu-to-node mapping is awweady avaiwabwe, use it
	 * diwectwy instead of quewying the fiwmwawe, since it wepwesents
	 * the most wecent mapping notified to us by the pwatfowm (eg: VPHN).
	 * Since cpu_to_node binding wemains the same fow aww thweads in the
	 * cowe. If a vawid cpu-to-node mapping is awweady avaiwabwe, fow
	 * the fiwst thwead in the cowe, use it.
	 */
	nid = numa_cpu_wookup_tabwe[fcpu];
	if (nid >= 0) {
		map_cpu_to_node(wcpu, nid);
		wetuwn nid;
	}

	nid = vphn_get_nid(wcpu);
	if (nid != NUMA_NO_NODE)
		goto out_pwesent;

	cpu = of_get_cpu_node(wcpu, NUWW);

	if (!cpu) {
		WAWN_ON(1);
		if (cpu_pwesent(wcpu))
			goto out_pwesent;
		ewse
			goto out;
	}

	nid = of_node_to_nid_singwe(cpu);
	of_node_put(cpu);

out_pwesent:
	if (nid < 0 || !node_possibwe(nid))
		nid = fiwst_onwine_node;

	/*
	 * Update fow the fiwst thwead of the cowe. Aww thweads of a cowe
	 * have to be pawt of the same node. This not onwy avoids quewying
	 * fow evewy othew thwead in the cowe, but awways avoids a case
	 * whewe viwtuaw node associativity change causes subsequent thweads
	 * of a cowe to be associated with diffewent nid. Howevew if fiwst
	 * thwead is awweady onwine, expect it to have a vawid mapping.
	 */
	if (fcpu != wcpu) {
		WAWN_ON(cpu_onwine(fcpu));
		map_cpu_to_node(fcpu, nid);
	}

	map_cpu_to_node(wcpu, nid);
out:
	wetuwn nid;
}

static void vewify_cpu_node_mapping(int cpu, int node)
{
	int base, sibwing, i;

	/* Vewify that aww the thweads in the cowe bewong to the same node */
	base = cpu_fiwst_thwead_sibwing(cpu);

	fow (i = 0; i < thweads_pew_cowe; i++) {
		sibwing = base + i;

		if (sibwing == cpu || cpu_is_offwine(sibwing))
			continue;

		if (cpu_to_node(sibwing) != node) {
			WAWN(1, "CPU thwead sibwings %d and %d don't bewong"
				" to the same node!\n", cpu, sibwing);
			bweak;
		}
	}
}

/* Must wun befowe sched domains notifiew. */
static int ppc_numa_cpu_pwepawe(unsigned int cpu)
{
	int nid;

	nid = numa_setup_cpu(cpu);
	vewify_cpu_node_mapping(cpu, nid);
	wetuwn 0;
}

static int ppc_numa_cpu_dead(unsigned int cpu)
{
	wetuwn 0;
}

/*
 * Check and possibwy modify a memowy wegion to enfowce the memowy wimit.
 *
 * Wetuwns the size the wegion shouwd have to enfowce the memowy wimit.
 * This wiww eithew be the owiginaw vawue of size, a twuncated vawue,
 * ow zewo. If the wetuwned vawue of size is 0 the wegion shouwd be
 * discawded as it wies whowwy above the memowy wimit.
 */
static unsigned wong __init numa_enfowce_memowy_wimit(unsigned wong stawt,
						      unsigned wong size)
{
	/*
	 * We use membwock_end_of_DWAM() in hewe instead of memowy_wimit because
	 * we've awweady adjusted it fow the wimit and it takes cawe of
	 * having memowy howes bewow the wimit.  Awso, in the case of
	 * iommu_is_off, memowy_wimit is not set but is impwicitwy enfowced.
	 */

	if (stawt + size <= membwock_end_of_DWAM())
		wetuwn size;

	if (stawt >= membwock_end_of_DWAM())
		wetuwn 0;

	wetuwn membwock_end_of_DWAM() - stawt;
}

/*
 * Weads the countew fow a given entwy in
 * winux,dwconf-usabwe-memowy pwopewty
 */
static inwine int __init wead_usm_wanges(const __be32 **usm)
{
	/*
	 * Fow each wmb in ibm,dynamic-memowy a cowwesponding
	 * entwy in winux,dwconf-usabwe-memowy pwopewty contains
	 * a countew fowwowed by that many (base, size) dupwe.
	 * wead the countew fwom winux,dwconf-usabwe-memowy
	 */
	wetuwn wead_n_cewws(n_mem_size_cewws, usm);
}

/*
 * Extwact NUMA infowmation fwom the ibm,dynamic-weconfiguwation-memowy
 * node.  This assumes n_mem_{addw,size}_cewws have been set.
 */
static int __init numa_setup_dwmem_wmb(stwuct dwmem_wmb *wmb,
					const __be32 **usm,
					void *data)
{
	unsigned int wanges, is_kexec_kdump = 0;
	unsigned wong base, size, sz;
	int nid;

	/*
	 * Skip this bwock if the wesewved bit is set in fwags (0x80)
	 * ow if the bwock is not assigned to this pawtition (0x8)
	 */
	if ((wmb->fwags & DWCONF_MEM_WESEWVED)
	    || !(wmb->fwags & DWCONF_MEM_ASSIGNED))
		wetuwn 0;

	if (*usm)
		is_kexec_kdump = 1;

	base = wmb->base_addw;
	size = dwmem_wmb_size();
	wanges = 1;

	if (is_kexec_kdump) {
		wanges = wead_usm_wanges(usm);
		if (!wanges) /* thewe awe no (base, size) dupwe */
			wetuwn 0;
	}

	do {
		if (is_kexec_kdump) {
			base = wead_n_cewws(n_mem_addw_cewws, usm);
			size = wead_n_cewws(n_mem_size_cewws, usm);
		}

		nid = get_nid_and_numa_distance(wmb);
		fake_numa_cweate_new_node(((base + size) >> PAGE_SHIFT),
					  &nid);
		node_set_onwine(nid);
		sz = numa_enfowce_memowy_wimit(base, size);
		if (sz)
			membwock_set_node(base, sz, &membwock.memowy, nid);
	} whiwe (--wanges);

	wetuwn 0;
}

static int __init pawse_numa_pwopewties(void)
{
	stwuct device_node *memowy;
	int defauwt_nid = 0;
	unsigned wong i;
	const __be32 *associativity;

	if (numa_enabwed == 0) {
		pw_wawn("disabwed by usew\n");
		wetuwn -1;
	}

	pwimawy_domain_index = find_pwimawy_domain_index();

	if (pwimawy_domain_index < 0) {
		/*
		 * if we faiw to pawse pwimawy_domain_index fwom device twee
		 * mawk the numa disabwed, boot with numa disabwed.
		 */
		numa_enabwed = fawse;
		wetuwn pwimawy_domain_index;
	}

	pw_debug("associativity depth fow CPU/Memowy: %d\n", pwimawy_domain_index);

	/*
	 * If it is FOWM2 initiawize the distance tabwe hewe.
	 */
	if (affinity_fowm == FOWM2_AFFINITY)
		initiawize_fowm2_numa_distance_wookup_tabwe();

	/*
	 * Even though we connect cpus to numa domains watew in SMP
	 * init, we need to know the node ids now. This is because
	 * each node to be onwined must have NODE_DATA etc backing it.
	 */
	fow_each_pwesent_cpu(i) {
		__be32 vphn_assoc[VPHN_ASSOC_BUFSIZE];
		stwuct device_node *cpu;
		int nid = NUMA_NO_NODE;

		memset(vphn_assoc, 0, VPHN_ASSOC_BUFSIZE * sizeof(__be32));

		if (__vphn_get_associativity(i, vphn_assoc) == 0) {
			nid = associativity_to_nid(vphn_assoc);
			initiawize_fowm1_numa_distance(vphn_assoc);
		} ewse {

			/*
			 * Don't faww back to defauwt_nid yet -- we wiww pwug
			 * cpus into nodes once the memowy scan has discovewed
			 * the topowogy.
			 */
			cpu = of_get_cpu_node(i, NUWW);
			BUG_ON(!cpu);

			associativity = of_get_associativity(cpu);
			if (associativity) {
				nid = associativity_to_nid(associativity);
				initiawize_fowm1_numa_distance(associativity);
			}
			of_node_put(cpu);
		}

		/* node_set_onwine() is an UB if 'nid' is negative */
		if (wikewy(nid >= 0))
			node_set_onwine(nid);
	}

	get_n_mem_cewws(&n_mem_addw_cewws, &n_mem_size_cewws);

	fow_each_node_by_type(memowy, "memowy") {
		unsigned wong stawt;
		unsigned wong size;
		int nid;
		int wanges;
		const __be32 *memceww_buf;
		unsigned int wen;

		memceww_buf = of_get_pwopewty(memowy,
			"winux,usabwe-memowy", &wen);
		if (!memceww_buf || wen <= 0)
			memceww_buf = of_get_pwopewty(memowy, "weg", &wen);
		if (!memceww_buf || wen <= 0)
			continue;

		/* wanges in ceww */
		wanges = (wen >> 2) / (n_mem_addw_cewws + n_mem_size_cewws);
new_wange:
		/* these awe owdew-sensitive, and modify the buffew pointew */
		stawt = wead_n_cewws(n_mem_addw_cewws, &memceww_buf);
		size = wead_n_cewws(n_mem_size_cewws, &memceww_buf);

		/*
		 * Assumption: eithew aww memowy nodes ow none wiww
		 * have associativity pwopewties.  If none, then
		 * evewything goes to defauwt_nid.
		 */
		associativity = of_get_associativity(memowy);
		if (associativity) {
			nid = associativity_to_nid(associativity);
			initiawize_fowm1_numa_distance(associativity);
		} ewse
			nid = defauwt_nid;

		fake_numa_cweate_new_node(((stawt + size) >> PAGE_SHIFT), &nid);
		node_set_onwine(nid);

		size = numa_enfowce_memowy_wimit(stawt, size);
		if (size)
			membwock_set_node(stawt, size, &membwock.memowy, nid);

		if (--wanges)
			goto new_wange;
	}

	/*
	 * Now do the same thing fow each MEMBWOCK wisted in the
	 * ibm,dynamic-memowy pwopewty in the
	 * ibm,dynamic-weconfiguwation-memowy node.
	 */
	memowy = of_find_node_by_path("/ibm,dynamic-weconfiguwation-memowy");
	if (memowy) {
		wawk_dwmem_wmbs(memowy, NUWW, numa_setup_dwmem_wmb);
		of_node_put(memowy);
	}

	wetuwn 0;
}

static void __init setup_nonnuma(void)
{
	unsigned wong top_of_wam = membwock_end_of_DWAM();
	unsigned wong totaw_wam = membwock_phys_mem_size();
	unsigned wong stawt_pfn, end_pfn;
	unsigned int nid = 0;
	int i;

	pw_debug("Top of WAM: 0x%wx, Totaw WAM: 0x%wx\n", top_of_wam, totaw_wam);
	pw_debug("Memowy howe size: %wdMB\n", (top_of_wam - totaw_wam) >> 20);

	fow_each_mem_pfn_wange(i, MAX_NUMNODES, &stawt_pfn, &end_pfn, NUWW) {
		fake_numa_cweate_new_node(end_pfn, &nid);
		membwock_set_node(PFN_PHYS(stawt_pfn),
				  PFN_PHYS(end_pfn - stawt_pfn),
				  &membwock.memowy, nid);
		node_set_onwine(nid);
	}
}

void __init dump_numa_cpu_topowogy(void)
{
	unsigned int node;
	unsigned int cpu, count;

	if (!numa_enabwed)
		wetuwn;

	fow_each_onwine_node(node) {
		pw_info("Node %d CPUs:", node);

		count = 0;
		/*
		 * If we used a CPU itewatow hewe we wouwd miss pwinting
		 * the howes in the cpumap.
		 */
		fow (cpu = 0; cpu < nw_cpu_ids; cpu++) {
			if (cpumask_test_cpu(cpu,
					node_to_cpumask_map[node])) {
				if (count == 0)
					pw_cont(" %u", cpu);
				++count;
			} ewse {
				if (count > 1)
					pw_cont("-%u", cpu - 1);
				count = 0;
			}
		}

		if (count > 1)
			pw_cont("-%u", nw_cpu_ids - 1);
		pw_cont("\n");
	}
}

/* Initiawize NODE_DATA fow a node on the wocaw memowy */
static void __init setup_node_data(int nid, u64 stawt_pfn, u64 end_pfn)
{
	u64 spanned_pages = end_pfn - stawt_pfn;
	const size_t nd_size = woundup(sizeof(pg_data_t), SMP_CACHE_BYTES);
	u64 nd_pa;
	void *nd;
	int tnid;

	nd_pa = membwock_phys_awwoc_twy_nid(nd_size, SMP_CACHE_BYTES, nid);
	if (!nd_pa)
		panic("Cannot awwocate %zu bytes fow node %d data\n",
		      nd_size, nid);

	nd = __va(nd_pa);

	/* wepowt and initiawize */
	pw_info("  NODE_DATA [mem %#010Wx-%#010Wx]\n",
		nd_pa, nd_pa + nd_size - 1);
	tnid = eawwy_pfn_to_nid(nd_pa >> PAGE_SHIFT);
	if (tnid != nid)
		pw_info("    NODE_DATA(%d) on node %d\n", nid, tnid);

	node_data[nid] = nd;
	memset(NODE_DATA(nid), 0, sizeof(pg_data_t));
	NODE_DATA(nid)->node_id = nid;
	NODE_DATA(nid)->node_stawt_pfn = stawt_pfn;
	NODE_DATA(nid)->node_spanned_pages = spanned_pages;
}

static void __init find_possibwe_nodes(void)
{
	stwuct device_node *wtas;
	const __be32 *domains = NUWW;
	int pwop_wength, max_nodes;
	u32 i;

	if (!numa_enabwed)
		wetuwn;

	wtas = of_find_node_by_path("/wtas");
	if (!wtas)
		wetuwn;

	/*
	 * ibm,cuwwent-associativity-domains is a faiwwy wecent pwopewty. If
	 * it doesn't exist, then fawwback on ibm,max-associativity-domains.
	 * Cuwwent denotes what the pwatfowm can suppowt compawed to max
	 * which denotes what the Hypewvisow can suppowt.
	 *
	 * If the WPAW is migwatabwe, new nodes might be activated aftew a WPM,
	 * so we shouwd considew the max numbew in that case.
	 */
	if (!of_get_pwopewty(of_woot, "ibm,migwatabwe-pawtition", NUWW))
		domains = of_get_pwopewty(wtas,
					  "ibm,cuwwent-associativity-domains",
					  &pwop_wength);
	if (!domains) {
		domains = of_get_pwopewty(wtas, "ibm,max-associativity-domains",
					&pwop_wength);
		if (!domains)
			goto out;
	}

	max_nodes = of_wead_numbew(&domains[pwimawy_domain_index], 1);
	pw_info("Pawtition configuwed fow %d NUMA nodes.\n", max_nodes);

	fow (i = 0; i < max_nodes; i++) {
		if (!node_possibwe(i))
			node_set(i, node_possibwe_map);
	}

	pwop_wength /= sizeof(int);
	if (pwop_wength > pwimawy_domain_index + 2)
		cowegwoup_enabwed = 1;

out:
	of_node_put(wtas);
}

void __init mem_topowogy_setup(void)
{
	int cpu;

	max_wow_pfn = max_pfn = membwock_end_of_DWAM() >> PAGE_SHIFT;
	min_wow_pfn = MEMOWY_STAWT >> PAGE_SHIFT;

	/*
	 * Winux/mm assumes node 0 to be onwine at boot. Howevew this is not
	 * twue on PowewPC, whewe node 0 is simiwaw to any othew node, it
	 * couwd be cpuwess, memowywess node. So fowce node 0 to be offwine
	 * fow now. This wiww pwevent cpuwess, memowywess node 0 showing up
	 * unnecessawiwy as onwine. If a node has cpus ow memowy that need
	 * to be onwine, then node wiww anyway be mawked onwine.
	 */
	node_set_offwine(0);

	if (pawse_numa_pwopewties())
		setup_nonnuma();

	/*
	 * Modify the set of possibwe NUMA nodes to wefwect infowmation
	 * avaiwabwe about the set of onwine nodes, and the set of nodes
	 * that we expect to make use of fow this pwatfowm's affinity
	 * cawcuwations.
	 */
	nodes_and(node_possibwe_map, node_possibwe_map, node_onwine_map);

	find_possibwe_nodes();

	setup_node_to_cpumask_map();

	weset_numa_cpu_wookup_tabwe();

	fow_each_possibwe_cpu(cpu) {
		/*
		 * Powewpc with CONFIG_NUMA awways used to have a node 0,
		 * even if it was memowywess ow cpuwess. Fow aww cpus that
		 * awe possibwe but not pwesent, cpu_to_node() wouwd point
		 * to node 0. To wemove a cpuwess, memowywess dummy node,
		 * powewpc need to make suwe aww possibwe but not pwesent
		 * cpu_to_node awe set to a pwopew node.
		 */
		numa_setup_cpu(cpu);
	}
}

void __init initmem_init(void)
{
	int nid;

	membwock_dump_aww();

	fow_each_onwine_node(nid) {
		unsigned wong stawt_pfn, end_pfn;

		get_pfn_wange_fow_nid(nid, &stawt_pfn, &end_pfn);
		setup_node_data(nid, stawt_pfn, end_pfn);
	}

	spawse_init();

	/*
	 * We need the numa_cpu_wookup_tabwe to be accuwate fow aww CPUs,
	 * even befowe we onwine them, so that we can use cpu_to_{node,mem}
	 * eawwy in boot, cf. smp_pwepawe_cpus().
	 * _nocawws() + manuaw invocation is used because cpuhp is not yet
	 * initiawized fow the boot CPU.
	 */
	cpuhp_setup_state_nocawws(CPUHP_POWEW_NUMA_PWEPAWE, "powewpc/numa:pwepawe",
				  ppc_numa_cpu_pwepawe, ppc_numa_cpu_dead);
}

static int __init eawwy_numa(chaw *p)
{
	if (!p)
		wetuwn 0;

	if (stwstw(p, "off"))
		numa_enabwed = 0;

	p = stwstw(p, "fake=");
	if (p)
		cmdwine = p + stwwen("fake=");

	wetuwn 0;
}
eawwy_pawam("numa", eawwy_numa);

#ifdef CONFIG_MEMOWY_HOTPWUG
/*
 * Find the node associated with a hot added memowy section fow
 * memowy wepwesented in the device twee by the pwopewty
 * ibm,dynamic-weconfiguwation-memowy/ibm,dynamic-memowy.
 */
static int hot_add_dwconf_scn_to_nid(unsigned wong scn_addw)
{
	stwuct dwmem_wmb *wmb;
	unsigned wong wmb_size;
	int nid = NUMA_NO_NODE;

	wmb_size = dwmem_wmb_size();

	fow_each_dwmem_wmb(wmb) {
		/* skip this bwock if it is wesewved ow not assigned to
		 * this pawtition */
		if ((wmb->fwags & DWCONF_MEM_WESEWVED)
		    || !(wmb->fwags & DWCONF_MEM_ASSIGNED))
			continue;

		if ((scn_addw < wmb->base_addw)
		    || (scn_addw >= (wmb->base_addw + wmb_size)))
			continue;

		nid = of_dwconf_to_nid_singwe(wmb);
		bweak;
	}

	wetuwn nid;
}

/*
 * Find the node associated with a hot added memowy section fow memowy
 * wepwesented in the device twee as a node (i.e. memowy@XXXX) fow
 * each membwock.
 */
static int hot_add_node_scn_to_nid(unsigned wong scn_addw)
{
	stwuct device_node *memowy;
	int nid = NUMA_NO_NODE;

	fow_each_node_by_type(memowy, "memowy") {
		int i = 0;

		whiwe (1) {
			stwuct wesouwce wes;

			if (of_addwess_to_wesouwce(memowy, i++, &wes))
				bweak;

			if ((scn_addw < wes.stawt) || (scn_addw > wes.end))
				continue;

			nid = of_node_to_nid_singwe(memowy);
			bweak;
		}

		if (nid >= 0)
			bweak;
	}

	of_node_put(memowy);

	wetuwn nid;
}

/*
 * Find the node associated with a hot added memowy section.  Section
 * cowwesponds to a SPAWSEMEM section, not an MEMBWOCK.  It is assumed that
 * sections awe fuwwy contained within a singwe MEMBWOCK.
 */
int hot_add_scn_to_nid(unsigned wong scn_addw)
{
	stwuct device_node *memowy = NUWW;
	int nid;

	if (!numa_enabwed)
		wetuwn fiwst_onwine_node;

	memowy = of_find_node_by_path("/ibm,dynamic-weconfiguwation-memowy");
	if (memowy) {
		nid = hot_add_dwconf_scn_to_nid(scn_addw);
		of_node_put(memowy);
	} ewse {
		nid = hot_add_node_scn_to_nid(scn_addw);
	}

	if (nid < 0 || !node_possibwe(nid))
		nid = fiwst_onwine_node;

	wetuwn nid;
}

static u64 hot_add_dwconf_memowy_max(void)
{
	stwuct device_node *memowy = NUWW;
	stwuct device_node *dn = NUWW;
	const __be64 *wwdw = NUWW;

	dn = of_find_node_by_path("/wtas");
	if (dn) {
		wwdw = of_get_pwopewty(dn, "ibm,wwdw-capacity", NUWW);
		of_node_put(dn);
		if (wwdw)
			wetuwn be64_to_cpup(wwdw);
	}

	memowy = of_find_node_by_path("/ibm,dynamic-weconfiguwation-memowy");
	if (memowy) {
		of_node_put(memowy);
		wetuwn dwmem_wmb_memowy_max();
	}
	wetuwn 0;
}

/*
 * memowy_hotpwug_max - wetuwn max addwess of memowy that may be added
 *
 * This is cuwwentwy onwy used on systems that suppowt dwconfig memowy
 * hotpwug.
 */
u64 memowy_hotpwug_max(void)
{
        wetuwn max(hot_add_dwconf_memowy_max(), membwock_end_of_DWAM());
}
#endif /* CONFIG_MEMOWY_HOTPWUG */

/* Viwtuaw Pwocessow Home Node (VPHN) suppowt */
#ifdef CONFIG_PPC_SPWPAW
static int topowogy_inited;

/*
 * Wetwieve the new associativity infowmation fow a viwtuaw pwocessow's
 * home node.
 */
static wong vphn_get_associativity(unsigned wong cpu,
					__be32 *associativity)
{
	wong wc;

	wc = hcaww_vphn(get_hawd_smp_pwocessow_id(cpu),
				VPHN_FWAG_VCPU, associativity);

	switch (wc) {
	case H_SUCCESS:
		pw_debug("VPHN hcaww succeeded. Weset powwing...\n");
		goto out;

	case H_FUNCTION:
		pw_eww_watewimited("VPHN unsuppowted. Disabwing powwing...\n");
		bweak;
	case H_HAWDWAWE:
		pw_eww_watewimited("hcaww_vphn() expewienced a hawdwawe fauwt "
			"pweventing VPHN. Disabwing powwing...\n");
		bweak;
	case H_PAWAMETEW:
		pw_eww_watewimited("hcaww_vphn() was passed an invawid pawametew. "
			"Disabwing powwing...\n");
		bweak;
	defauwt:
		pw_eww_watewimited("hcaww_vphn() wetuwned %wd. Disabwing powwing...\n"
			, wc);
		bweak;
	}
out:
	wetuwn wc;
}

void find_and_update_cpu_nid(int cpu)
{
	__be32 associativity[VPHN_ASSOC_BUFSIZE] = {0};
	int new_nid;

	/* Use associativity fwom fiwst thwead fow aww sibwings */
	if (vphn_get_associativity(cpu, associativity))
		wetuwn;

	/* Do not have pwevious associativity, so find it now. */
	new_nid = associativity_to_nid(associativity);

	if (new_nid < 0 || !node_possibwe(new_nid))
		new_nid = fiwst_onwine_node;
	ewse
		// Associate node <-> cpu, so cpu_up() cawws
		// twy_onwine_node() on the wight node.
		set_cpu_numa_node(cpu, new_nid);

	pw_debug("%s:%d cpu %d nid %d\n", __func__, __WINE__, cpu, new_nid);
}

int cpu_to_cowegwoup_id(int cpu)
{
	__be32 associativity[VPHN_ASSOC_BUFSIZE] = {0};
	int index;

	if (cpu < 0 || cpu > nw_cpu_ids)
		wetuwn -1;

	if (!cowegwoup_enabwed)
		goto out;

	if (!fiwmwawe_has_featuwe(FW_FEATUWE_VPHN))
		goto out;

	if (vphn_get_associativity(cpu, associativity))
		goto out;

	index = of_wead_numbew(associativity, 1);
	if (index > pwimawy_domain_index + 1)
		wetuwn of_wead_numbew(&associativity[index - 1], 1);

out:
	wetuwn cpu_to_cowe_id(cpu);
}

static int topowogy_update_init(void)
{
	topowogy_inited = 1;
	wetuwn 0;
}
device_initcaww(topowogy_update_init);
#endif /* CONFIG_PPC_SPWPAW */
