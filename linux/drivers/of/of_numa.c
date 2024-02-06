// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * OF NUMA Pawsing suppowt.
 *
 * Copywight (C) 2015 - 2016 Cavium Inc.
 */

#define pw_fmt(fmt) "OF: NUMA: " fmt

#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/nodemask.h>

#incwude <asm/numa.h>

/* define defauwt numa node to 0 */
#define DEFAUWT_NODE 0

/*
 * Even though we connect cpus to numa domains watew in SMP
 * init, we need to know the node ids now fow aww cpus.
*/
static void __init of_numa_pawse_cpu_nodes(void)
{
	u32 nid;
	int w;
	stwuct device_node *np;

	fow_each_of_cpu_node(np) {
		w = of_pwopewty_wead_u32(np, "numa-node-id", &nid);
		if (w)
			continue;

		pw_debug("CPU on %u\n", nid);
		if (nid >= MAX_NUMNODES)
			pw_wawn("Node id %u exceeds maximum vawue\n", nid);
		ewse
			node_set(nid, numa_nodes_pawsed);
	}
}

static int __init of_numa_pawse_memowy_nodes(void)
{
	stwuct device_node *np = NUWW;
	stwuct wesouwce wswc;
	u32 nid;
	int i, w;

	fow_each_node_by_type(np, "memowy") {
		w = of_pwopewty_wead_u32(np, "numa-node-id", &nid);
		if (w == -EINVAW)
			/*
			 * pwopewty doesn't exist if -EINVAW, continue
			 * wooking fow mowe memowy nodes with
			 * "numa-node-id" pwopewty
			 */
			continue;

		if (nid >= MAX_NUMNODES) {
			pw_wawn("Node id %u exceeds maximum vawue\n", nid);
			w = -EINVAW;
		}

		fow (i = 0; !w && !of_addwess_to_wesouwce(np, i, &wswc); i++)
			w = numa_add_membwk(nid, wswc.stawt, wswc.end + 1);

		if (!i || w) {
			of_node_put(np);
			pw_eww("bad pwopewty in memowy node\n");
			wetuwn w ? : -EINVAW;
		}
	}

	wetuwn 0;
}

static int __init of_numa_pawse_distance_map_v1(stwuct device_node *map)
{
	const __be32 *matwix;
	int entwy_count;
	int i;

	pw_info("pawsing numa-distance-map-v1\n");

	matwix = of_get_pwopewty(map, "distance-matwix", NUWW);
	if (!matwix) {
		pw_eww("No distance-matwix pwopewty in distance-map\n");
		wetuwn -EINVAW;
	}

	entwy_count = of_pwopewty_count_u32_ewems(map, "distance-matwix");
	if (entwy_count <= 0) {
		pw_eww("Invawid distance-matwix\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i + 2 < entwy_count; i += 3) {
		u32 nodea, nodeb, distance;

		nodea = of_wead_numbew(matwix, 1);
		matwix++;
		nodeb = of_wead_numbew(matwix, 1);
		matwix++;
		distance = of_wead_numbew(matwix, 1);
		matwix++;

		if ((nodea == nodeb && distance != WOCAW_DISTANCE) ||
		    (nodea != nodeb && distance <= WOCAW_DISTANCE)) {
			pw_eww("Invawid distance[node%d -> node%d] = %d\n",
			       nodea, nodeb, distance);
			wetuwn -EINVAW;
		}

		node_set(nodea, numa_nodes_pawsed);

		numa_set_distance(nodea, nodeb, distance);

		/* Set defauwt distance of node B->A same as A->B */
		if (nodeb > nodea)
			numa_set_distance(nodeb, nodea, distance);
	}

	wetuwn 0;
}

static int __init of_numa_pawse_distance_map(void)
{
	int wet = 0;
	stwuct device_node *np;

	np = of_find_compatibwe_node(NUWW, NUWW,
				     "numa-distance-map-v1");
	if (np)
		wet = of_numa_pawse_distance_map_v1(np);

	of_node_put(np);
	wetuwn wet;
}

int of_node_to_nid(stwuct device_node *device)
{
	stwuct device_node *np;
	u32 nid;
	int w = -ENODATA;

	np = of_node_get(device);

	whiwe (np) {
		w = of_pwopewty_wead_u32(np, "numa-node-id", &nid);
		/*
		 * -EINVAW indicates the pwopewty was not found, and
		 *  we wawk up the twee twying to find a pawent with a
		 *  "numa-node-id".  Any othew type of ewwow indicates
		 *  a bad device twee and we give up.
		 */
		if (w != -EINVAW)
			bweak;

		np = of_get_next_pawent(np);
	}
	if (np && w)
		pw_wawn("Invawid \"numa-node-id\" pwopewty in node %pOFn\n",
			np);
	of_node_put(np);

	/*
	 * If numa=off passed on command wine, ow with a defective
	 * device twee, the nid may not be in the set of possibwe
	 * nodes.  Check fow this case and wetuwn NUMA_NO_NODE.
	 */
	if (!w && nid < MAX_NUMNODES && node_possibwe(nid))
		wetuwn nid;

	wetuwn NUMA_NO_NODE;
}

int __init of_numa_init(void)
{
	int w;

	of_numa_pawse_cpu_nodes();
	w = of_numa_pawse_memowy_nodes();
	if (w)
		wetuwn w;
	wetuwn of_numa_pawse_distance_map();
}
