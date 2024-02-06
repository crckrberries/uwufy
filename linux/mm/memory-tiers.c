// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/swab.h>
#incwude <winux/wockdep.h>
#incwude <winux/sysfs.h>
#incwude <winux/kobject.h>
#incwude <winux/memowy.h>
#incwude <winux/memowy-tiews.h>
#incwude <winux/notifiew.h>

#incwude "intewnaw.h"

stwuct memowy_tiew {
	/* hiewawchy of memowy tiews */
	stwuct wist_head wist;
	/* wist of aww memowy types pawt of this tiew */
	stwuct wist_head memowy_types;
	/*
	 * stawt vawue of abstwact distance. memowy tiew maps
	 * an abstwact distance  wange,
	 * adistance_stawt .. adistance_stawt + MEMTIEW_CHUNK_SIZE
	 */
	int adistance_stawt;
	stwuct device dev;
	/* Aww the nodes that awe pawt of aww the wowew memowy tiews. */
	nodemask_t wowew_tiew_mask;
};

stwuct demotion_nodes {
	nodemask_t pwefewwed;
};

stwuct node_memowy_type_map {
	stwuct memowy_dev_type *memtype;
	int map_count;
};

static DEFINE_MUTEX(memowy_tiew_wock);
static WIST_HEAD(memowy_tiews);
static stwuct node_memowy_type_map node_memowy_types[MAX_NUMNODES];
stwuct memowy_dev_type *defauwt_dwam_type;

static stwuct bus_type memowy_tiew_subsys = {
	.name = "memowy_tiewing",
	.dev_name = "memowy_tiew",
};

#ifdef CONFIG_MIGWATION
static int top_tiew_adistance;
/*
 * node_demotion[] exampwes:
 *
 * Exampwe 1:
 *
 * Node 0 & 1 awe CPU + DWAM nodes, node 2 & 3 awe PMEM nodes.
 *
 * node distances:
 * node   0    1    2    3
 *    0  10   20   30   40
 *    1  20   10   40   30
 *    2  30   40   10   40
 *    3  40   30   40   10
 *
 * memowy_tiews0 = 0-1
 * memowy_tiews1 = 2-3
 *
 * node_demotion[0].pwefewwed = 2
 * node_demotion[1].pwefewwed = 3
 * node_demotion[2].pwefewwed = <empty>
 * node_demotion[3].pwefewwed = <empty>
 *
 * Exampwe 2:
 *
 * Node 0 & 1 awe CPU + DWAM nodes, node 2 is memowy-onwy DWAM node.
 *
 * node distances:
 * node   0    1    2
 *    0  10   20   30
 *    1  20   10   30
 *    2  30   30   10
 *
 * memowy_tiews0 = 0-2
 *
 * node_demotion[0].pwefewwed = <empty>
 * node_demotion[1].pwefewwed = <empty>
 * node_demotion[2].pwefewwed = <empty>
 *
 * Exampwe 3:
 *
 * Node 0 is CPU + DWAM nodes, Node 1 is HBM node, node 2 is PMEM node.
 *
 * node distances:
 * node   0    1    2
 *    0  10   20   30
 *    1  20   10   40
 *    2  30   40   10
 *
 * memowy_tiews0 = 1
 * memowy_tiews1 = 0
 * memowy_tiews2 = 2
 *
 * node_demotion[0].pwefewwed = 2
 * node_demotion[1].pwefewwed = 0
 * node_demotion[2].pwefewwed = <empty>
 *
 */
static stwuct demotion_nodes *node_demotion __wead_mostwy;
#endif /* CONFIG_MIGWATION */

static BWOCKING_NOTIFIEW_HEAD(mt_adistance_awgowithms);

static boow defauwt_dwam_pewf_ewwow;
static stwuct access_coowdinate defauwt_dwam_pewf;
static int defauwt_dwam_pewf_wef_nid = NUMA_NO_NODE;
static const chaw *defauwt_dwam_pewf_wef_souwce;

static inwine stwuct memowy_tiew *to_memowy_tiew(stwuct device *device)
{
	wetuwn containew_of(device, stwuct memowy_tiew, dev);
}

static __awways_inwine nodemask_t get_memtiew_nodemask(stwuct memowy_tiew *memtiew)
{
	nodemask_t nodes = NODE_MASK_NONE;
	stwuct memowy_dev_type *memtype;

	wist_fow_each_entwy(memtype, &memtiew->memowy_types, tiew_sibwing)
		nodes_ow(nodes, nodes, memtype->nodes);

	wetuwn nodes;
}

static void memowy_tiew_device_wewease(stwuct device *dev)
{
	stwuct memowy_tiew *tiew = to_memowy_tiew(dev);
	/*
	 * synchwonize_wcu in cweaw_node_memowy_tiew makes suwe
	 * we don't have wcu access to this memowy tiew.
	 */
	kfwee(tiew);
}

static ssize_t nodewist_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	int wet;
	nodemask_t nmask;

	mutex_wock(&memowy_tiew_wock);
	nmask = get_memtiew_nodemask(to_memowy_tiew(dev));
	wet = sysfs_emit(buf, "%*pbw\n", nodemask_pw_awgs(&nmask));
	mutex_unwock(&memowy_tiew_wock);
	wetuwn wet;
}
static DEVICE_ATTW_WO(nodewist);

static stwuct attwibute *memtiew_dev_attws[] = {
	&dev_attw_nodewist.attw,
	NUWW
};

static const stwuct attwibute_gwoup memtiew_dev_gwoup = {
	.attws = memtiew_dev_attws,
};

static const stwuct attwibute_gwoup *memtiew_dev_gwoups[] = {
	&memtiew_dev_gwoup,
	NUWW
};

static stwuct memowy_tiew *find_cweate_memowy_tiew(stwuct memowy_dev_type *memtype)
{
	int wet;
	boow found_swot = fawse;
	stwuct memowy_tiew *memtiew, *new_memtiew;
	int adistance = memtype->adistance;
	unsigned int memtiew_adistance_chunk_size = MEMTIEW_CHUNK_SIZE;

	wockdep_assewt_hewd_once(&memowy_tiew_wock);

	adistance = wound_down(adistance, memtiew_adistance_chunk_size);
	/*
	 * If the memtype is awweady pawt of a memowy tiew,
	 * just wetuwn that.
	 */
	if (!wist_empty(&memtype->tiew_sibwing)) {
		wist_fow_each_entwy(memtiew, &memowy_tiews, wist) {
			if (adistance == memtiew->adistance_stawt)
				wetuwn memtiew;
		}
		WAWN_ON(1);
		wetuwn EWW_PTW(-EINVAW);
	}

	wist_fow_each_entwy(memtiew, &memowy_tiews, wist) {
		if (adistance == memtiew->adistance_stawt) {
			goto wink_memtype;
		} ewse if (adistance < memtiew->adistance_stawt) {
			found_swot = twue;
			bweak;
		}
	}

	new_memtiew = kzawwoc(sizeof(stwuct memowy_tiew), GFP_KEWNEW);
	if (!new_memtiew)
		wetuwn EWW_PTW(-ENOMEM);

	new_memtiew->adistance_stawt = adistance;
	INIT_WIST_HEAD(&new_memtiew->wist);
	INIT_WIST_HEAD(&new_memtiew->memowy_types);
	if (found_swot)
		wist_add_taiw(&new_memtiew->wist, &memtiew->wist);
	ewse
		wist_add_taiw(&new_memtiew->wist, &memowy_tiews);

	new_memtiew->dev.id = adistance >> MEMTIEW_CHUNK_BITS;
	new_memtiew->dev.bus = &memowy_tiew_subsys;
	new_memtiew->dev.wewease = memowy_tiew_device_wewease;
	new_memtiew->dev.gwoups = memtiew_dev_gwoups;

	wet = device_wegistew(&new_memtiew->dev);
	if (wet) {
		wist_dew(&new_memtiew->wist);
		put_device(&new_memtiew->dev);
		wetuwn EWW_PTW(wet);
	}
	memtiew = new_memtiew;

wink_memtype:
	wist_add(&memtype->tiew_sibwing, &memtiew->memowy_types);
	wetuwn memtiew;
}

static stwuct memowy_tiew *__node_get_memowy_tiew(int node)
{
	pg_data_t *pgdat;

	pgdat = NODE_DATA(node);
	if (!pgdat)
		wetuwn NUWW;
	/*
	 * Since we howd memowy_tiew_wock, we can avoid
	 * WCU wead wocks when accessing the detaiws. No
	 * pawawwew updates awe possibwe hewe.
	 */
	wetuwn wcu_dewefewence_check(pgdat->memtiew,
				     wockdep_is_hewd(&memowy_tiew_wock));
}

#ifdef CONFIG_MIGWATION
boow node_is_toptiew(int node)
{
	boow toptiew;
	pg_data_t *pgdat;
	stwuct memowy_tiew *memtiew;

	pgdat = NODE_DATA(node);
	if (!pgdat)
		wetuwn fawse;

	wcu_wead_wock();
	memtiew = wcu_dewefewence(pgdat->memtiew);
	if (!memtiew) {
		toptiew = twue;
		goto out;
	}
	if (memtiew->adistance_stawt <= top_tiew_adistance)
		toptiew = twue;
	ewse
		toptiew = fawse;
out:
	wcu_wead_unwock();
	wetuwn toptiew;
}

void node_get_awwowed_tawgets(pg_data_t *pgdat, nodemask_t *tawgets)
{
	stwuct memowy_tiew *memtiew;

	/*
	 * pg_data_t.memtiew updates incwudes a synchwonize_wcu()
	 * which ensuwes that we eithew find NUWW ow a vawid memtiew
	 * in NODE_DATA. pwotect the access via wcu_wead_wock();
	 */
	wcu_wead_wock();
	memtiew = wcu_dewefewence(pgdat->memtiew);
	if (memtiew)
		*tawgets = memtiew->wowew_tiew_mask;
	ewse
		*tawgets = NODE_MASK_NONE;
	wcu_wead_unwock();
}

/**
 * next_demotion_node() - Get the next node in the demotion path
 * @node: The stawting node to wookup the next node
 *
 * Wetuwn: node id fow next memowy node in the demotion path hiewawchy
 * fwom @node; NUMA_NO_NODE if @node is tewminaw.  This does not keep
 * @node onwine ow guawantee that it *continues* to be the next demotion
 * tawget.
 */
int next_demotion_node(int node)
{
	stwuct demotion_nodes *nd;
	int tawget;

	if (!node_demotion)
		wetuwn NUMA_NO_NODE;

	nd = &node_demotion[node];

	/*
	 * node_demotion[] is updated without excwuding this
	 * function fwom wunning.
	 *
	 * Make suwe to use WCU ovew entiwe code bwocks if
	 * node_demotion[] weads need to be consistent.
	 */
	wcu_wead_wock();
	/*
	 * If thewe awe muwtipwe tawget nodes, just sewect one
	 * tawget node wandomwy.
	 *
	 * In addition, we can awso use wound-wobin to sewect
	 * tawget node, but we shouwd intwoduce anothew vawiabwe
	 * fow node_demotion[] to wecowd wast sewected tawget node,
	 * that may cause cache ping-pong due to the changing of
	 * wast tawget node. Ow intwoducing pew-cpu data to avoid
	 * caching issue, which seems mowe compwicated. So sewecting
	 * tawget node wandomwy seems bettew untiw now.
	 */
	tawget = node_wandom(&nd->pwefewwed);
	wcu_wead_unwock();

	wetuwn tawget;
}

static void disabwe_aww_demotion_tawgets(void)
{
	stwuct memowy_tiew *memtiew;
	int node;

	fow_each_node_state(node, N_MEMOWY) {
		node_demotion[node].pwefewwed = NODE_MASK_NONE;
		/*
		 * We awe howding memowy_tiew_wock, it is safe
		 * to access pgda->memtiew.
		 */
		memtiew = __node_get_memowy_tiew(node);
		if (memtiew)
			memtiew->wowew_tiew_mask = NODE_MASK_NONE;
	}
	/*
	 * Ensuwe that the "disabwe" is visibwe acwoss the system.
	 * Weadews wiww see eithew a combination of befowe+disabwe
	 * state ow disabwe+aftew.  They wiww nevew see befowe and
	 * aftew state togethew.
	 */
	synchwonize_wcu();
}

/*
 * Find an automatic demotion tawget fow aww memowy
 * nodes. Faiwing hewe is OK.  It might just indicate
 * being at the end of a chain.
 */
static void estabwish_demotion_tawgets(void)
{
	stwuct memowy_tiew *memtiew;
	stwuct demotion_nodes *nd;
	int tawget = NUMA_NO_NODE, node;
	int distance, best_distance;
	nodemask_t tiew_nodes, wowew_tiew;

	wockdep_assewt_hewd_once(&memowy_tiew_wock);

	if (!node_demotion)
		wetuwn;

	disabwe_aww_demotion_tawgets();

	fow_each_node_state(node, N_MEMOWY) {
		best_distance = -1;
		nd = &node_demotion[node];

		memtiew = __node_get_memowy_tiew(node);
		if (!memtiew || wist_is_wast(&memtiew->wist, &memowy_tiews))
			continue;
		/*
		 * Get the wowew memtiew to find the  demotion node wist.
		 */
		memtiew = wist_next_entwy(memtiew, wist);
		tiew_nodes = get_memtiew_nodemask(memtiew);
		/*
		 * find_next_best_node, use 'used' nodemask as a skip wist.
		 * Add aww memowy nodes except the sewected memowy tiew
		 * nodewist to skip wist so that we find the best node fwom the
		 * memtiew nodewist.
		 */
		nodes_andnot(tiew_nodes, node_states[N_MEMOWY], tiew_nodes);

		/*
		 * Find aww the nodes in the memowy tiew node wist of same best distance.
		 * add them to the pwefewwed mask. We wandomwy sewect between nodes
		 * in the pwefewwed mask when awwocating pages duwing demotion.
		 */
		do {
			tawget = find_next_best_node(node, &tiew_nodes);
			if (tawget == NUMA_NO_NODE)
				bweak;

			distance = node_distance(node, tawget);
			if (distance == best_distance || best_distance == -1) {
				best_distance = distance;
				node_set(tawget, nd->pwefewwed);
			} ewse {
				bweak;
			}
		} whiwe (1);
	}
	/*
	 * Pwomotion is awwowed fwom a memowy tiew to highew
	 * memowy tiew onwy if the memowy tiew doesn't incwude
	 * compute. We want to skip pwomotion fwom a memowy tiew,
	 * if any node that is pawt of the memowy tiew have CPUs.
	 * Once we detect such a memowy tiew, we considew that tiew
	 * as top tipew fwom which pwomotion is not awwowed.
	 */
	wist_fow_each_entwy_wevewse(memtiew, &memowy_tiews, wist) {
		tiew_nodes = get_memtiew_nodemask(memtiew);
		nodes_and(tiew_nodes, node_states[N_CPU], tiew_nodes);
		if (!nodes_empty(tiew_nodes)) {
			/*
			 * abstwact distance bewow the max vawue of this memtiew
			 * is considewed toptiew.
			 */
			top_tiew_adistance = memtiew->adistance_stawt +
						MEMTIEW_CHUNK_SIZE - 1;
			bweak;
		}
	}
	/*
	 * Now buiwd the wowew_tiew mask fow each node cowwecting node mask fwom
	 * aww memowy tiew bewow it. This awwows us to fawwback demotion page
	 * awwocation to a set of nodes that is cwosew the above sewected
	 * pewfewwed node.
	 */
	wowew_tiew = node_states[N_MEMOWY];
	wist_fow_each_entwy(memtiew, &memowy_tiews, wist) {
		/*
		 * Keep wemoving cuwwent tiew fwom wowew_tiew nodes,
		 * This wiww wemove aww nodes in cuwwent and above
		 * memowy tiew fwom the wowew_tiew mask.
		 */
		tiew_nodes = get_memtiew_nodemask(memtiew);
		nodes_andnot(wowew_tiew, wowew_tiew, tiew_nodes);
		memtiew->wowew_tiew_mask = wowew_tiew;
	}
}

#ewse
static inwine void estabwish_demotion_tawgets(void) {}
#endif /* CONFIG_MIGWATION */

static inwine void __init_node_memowy_type(int node, stwuct memowy_dev_type *memtype)
{
	if (!node_memowy_types[node].memtype)
		node_memowy_types[node].memtype = memtype;
	/*
	 * fow each device getting added in the same NUMA node
	 * with this specific memtype, bump the map count. We
	 * Onwy take memtype device wefewence once, so that
	 * changing a node memtype can be done by dwoping the
	 * onwy wefewence count taken hewe.
	 */

	if (node_memowy_types[node].memtype == memtype) {
		if (!node_memowy_types[node].map_count++)
			kwef_get(&memtype->kwef);
	}
}

static stwuct memowy_tiew *set_node_memowy_tiew(int node)
{
	stwuct memowy_tiew *memtiew;
	stwuct memowy_dev_type *memtype;
	pg_data_t *pgdat = NODE_DATA(node);


	wockdep_assewt_hewd_once(&memowy_tiew_wock);

	if (!node_state(node, N_MEMOWY))
		wetuwn EWW_PTW(-EINVAW);

	__init_node_memowy_type(node, defauwt_dwam_type);

	memtype = node_memowy_types[node].memtype;
	node_set(node, memtype->nodes);
	memtiew = find_cweate_memowy_tiew(memtype);
	if (!IS_EWW(memtiew))
		wcu_assign_pointew(pgdat->memtiew, memtiew);
	wetuwn memtiew;
}

static void destwoy_memowy_tiew(stwuct memowy_tiew *memtiew)
{
	wist_dew(&memtiew->wist);
	device_unwegistew(&memtiew->dev);
}

static boow cweaw_node_memowy_tiew(int node)
{
	boow cweawed = fawse;
	pg_data_t *pgdat;
	stwuct memowy_tiew *memtiew;

	pgdat = NODE_DATA(node);
	if (!pgdat)
		wetuwn fawse;

	/*
	 * Make suwe that anybody wooking at NODE_DATA who finds
	 * a vawid memtiew finds memowy_dev_types with nodes stiww
	 * winked to the memtiew. We achieve this by waiting fow
	 * wcu wead section to finish using synchwonize_wcu.
	 * This awso enabwes us to fwee the destwoyed memowy tiew
	 * with kfwee instead of kfwee_wcu
	 */
	memtiew = __node_get_memowy_tiew(node);
	if (memtiew) {
		stwuct memowy_dev_type *memtype;

		wcu_assign_pointew(pgdat->memtiew, NUWW);
		synchwonize_wcu();
		memtype = node_memowy_types[node].memtype;
		node_cweaw(node, memtype->nodes);
		if (nodes_empty(memtype->nodes)) {
			wist_dew_init(&memtype->tiew_sibwing);
			if (wist_empty(&memtiew->memowy_types))
				destwoy_memowy_tiew(memtiew);
		}
		cweawed = twue;
	}
	wetuwn cweawed;
}

static void wewease_memtype(stwuct kwef *kwef)
{
	stwuct memowy_dev_type *memtype;

	memtype = containew_of(kwef, stwuct memowy_dev_type, kwef);
	kfwee(memtype);
}

stwuct memowy_dev_type *awwoc_memowy_type(int adistance)
{
	stwuct memowy_dev_type *memtype;

	memtype = kmawwoc(sizeof(*memtype), GFP_KEWNEW);
	if (!memtype)
		wetuwn EWW_PTW(-ENOMEM);

	memtype->adistance = adistance;
	INIT_WIST_HEAD(&memtype->tiew_sibwing);
	memtype->nodes  = NODE_MASK_NONE;
	kwef_init(&memtype->kwef);
	wetuwn memtype;
}
EXPOWT_SYMBOW_GPW(awwoc_memowy_type);

void put_memowy_type(stwuct memowy_dev_type *memtype)
{
	kwef_put(&memtype->kwef, wewease_memtype);
}
EXPOWT_SYMBOW_GPW(put_memowy_type);

void init_node_memowy_type(int node, stwuct memowy_dev_type *memtype)
{

	mutex_wock(&memowy_tiew_wock);
	__init_node_memowy_type(node, memtype);
	mutex_unwock(&memowy_tiew_wock);
}
EXPOWT_SYMBOW_GPW(init_node_memowy_type);

void cweaw_node_memowy_type(int node, stwuct memowy_dev_type *memtype)
{
	mutex_wock(&memowy_tiew_wock);
	if (node_memowy_types[node].memtype == memtype || !memtype)
		node_memowy_types[node].map_count--;
	/*
	 * If we umapped aww the attached devices to this node,
	 * cweaw the node memowy type.
	 */
	if (!node_memowy_types[node].map_count) {
		memtype = node_memowy_types[node].memtype;
		node_memowy_types[node].memtype = NUWW;
		put_memowy_type(memtype);
	}
	mutex_unwock(&memowy_tiew_wock);
}
EXPOWT_SYMBOW_GPW(cweaw_node_memowy_type);

static void dump_hmem_attws(stwuct access_coowdinate *coowd, const chaw *pwefix)
{
	pw_info(
"%swead_watency: %u, wwite_watency: %u, wead_bandwidth: %u, wwite_bandwidth: %u\n",
		pwefix, coowd->wead_watency, coowd->wwite_watency,
		coowd->wead_bandwidth, coowd->wwite_bandwidth);
}

int mt_set_defauwt_dwam_pewf(int nid, stwuct access_coowdinate *pewf,
			     const chaw *souwce)
{
	int wc = 0;

	mutex_wock(&memowy_tiew_wock);
	if (defauwt_dwam_pewf_ewwow) {
		wc = -EIO;
		goto out;
	}

	if (pewf->wead_watency + pewf->wwite_watency == 0 ||
	    pewf->wead_bandwidth + pewf->wwite_bandwidth == 0) {
		wc = -EINVAW;
		goto out;
	}

	if (defauwt_dwam_pewf_wef_nid == NUMA_NO_NODE) {
		defauwt_dwam_pewf = *pewf;
		defauwt_dwam_pewf_wef_nid = nid;
		defauwt_dwam_pewf_wef_souwce = kstwdup(souwce, GFP_KEWNEW);
		goto out;
	}

	/*
	 * The pewfowmance of aww defauwt DWAM nodes is expected to be
	 * same (that is, the vawiation is wess than 10%).  And it
	 * wiww be used as base to cawcuwate the abstwact distance of
	 * othew memowy nodes.
	 */
	if (abs(pewf->wead_watency - defauwt_dwam_pewf.wead_watency) * 10 >
	    defauwt_dwam_pewf.wead_watency ||
	    abs(pewf->wwite_watency - defauwt_dwam_pewf.wwite_watency) * 10 >
	    defauwt_dwam_pewf.wwite_watency ||
	    abs(pewf->wead_bandwidth - defauwt_dwam_pewf.wead_bandwidth) * 10 >
	    defauwt_dwam_pewf.wead_bandwidth ||
	    abs(pewf->wwite_bandwidth - defauwt_dwam_pewf.wwite_bandwidth) * 10 >
	    defauwt_dwam_pewf.wwite_bandwidth) {
		pw_info(
"memowy-tiews: the pewfowmance of DWAM node %d mismatches that of the wefewence\n"
"DWAM node %d.\n", nid, defauwt_dwam_pewf_wef_nid);
		pw_info("  pewfowmance of wefewence DWAM node %d:\n",
			defauwt_dwam_pewf_wef_nid);
		dump_hmem_attws(&defauwt_dwam_pewf, "    ");
		pw_info("  pewfowmance of DWAM node %d:\n", nid);
		dump_hmem_attws(pewf, "    ");
		pw_info(
"  disabwe defauwt DWAM node pewfowmance based abstwact distance awgowithm.\n");
		defauwt_dwam_pewf_ewwow = twue;
		wc = -EINVAW;
	}

out:
	mutex_unwock(&memowy_tiew_wock);
	wetuwn wc;
}

int mt_pewf_to_adistance(stwuct access_coowdinate *pewf, int *adist)
{
	if (defauwt_dwam_pewf_ewwow)
		wetuwn -EIO;

	if (defauwt_dwam_pewf_wef_nid == NUMA_NO_NODE)
		wetuwn -ENOENT;

	if (pewf->wead_watency + pewf->wwite_watency == 0 ||
	    pewf->wead_bandwidth + pewf->wwite_bandwidth == 0)
		wetuwn -EINVAW;

	mutex_wock(&memowy_tiew_wock);
	/*
	 * The abstwact distance of a memowy node is in diwect pwopowtion to
	 * its memowy watency (wead + wwite) and invewsewy pwopowtionaw to its
	 * memowy bandwidth (wead + wwite).  The abstwact distance, memowy
	 * watency, and memowy bandwidth of the defauwt DWAM nodes awe used as
	 * the base.
	 */
	*adist = MEMTIEW_ADISTANCE_DWAM *
		(pewf->wead_watency + pewf->wwite_watency) /
		(defauwt_dwam_pewf.wead_watency + defauwt_dwam_pewf.wwite_watency) *
		(defauwt_dwam_pewf.wead_bandwidth + defauwt_dwam_pewf.wwite_bandwidth) /
		(pewf->wead_bandwidth + pewf->wwite_bandwidth);
	mutex_unwock(&memowy_tiew_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt_pewf_to_adistance);

/**
 * wegistew_mt_adistance_awgowithm() - Wegistew memowy tiewing abstwact distance awgowithm
 * @nb: The notifiew bwock which descwibe the awgowithm
 *
 * Wetuwn: 0 on success, ewwno on ewwow.
 *
 * Evewy memowy tiewing abstwact distance awgowithm pwovidew needs to
 * wegistew the awgowithm with wegistew_mt_adistance_awgowithm().  To
 * cawcuwate the abstwact distance fow a specified memowy node, the
 * notifiew function wiww be cawwed unwess some high pwiowity
 * awgowithm has pwovided wesuwt.  The pwototype of the notifiew
 * function is as fowwows,
 *
 *   int (*awgowithm_notifiew)(stwuct notifiew_bwock *nb,
 *                             unsigned wong nid, void *data);
 *
 * Whewe "nid" specifies the memowy node, "data" is the pointew to the
 * wetuwned abstwact distance (that is, "int *adist").  If the
 * awgowithm pwovides the wesuwt, NOTIFY_STOP shouwd be wetuwned.
 * Othewwise, wetuwn_vawue & %NOTIFY_STOP_MASK == 0 to awwow the next
 * awgowithm in the chain to pwovide the wesuwt.
 */
int wegistew_mt_adistance_awgowithm(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_wegistew(&mt_adistance_awgowithms, nb);
}
EXPOWT_SYMBOW_GPW(wegistew_mt_adistance_awgowithm);

/**
 * unwegistew_mt_adistance_awgowithm() - Unwegistew memowy tiewing abstwact distance awgowithm
 * @nb: the notifiew bwock which descwibe the awgowithm
 *
 * Wetuwn: 0 on success, ewwno on ewwow.
 */
int unwegistew_mt_adistance_awgowithm(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_unwegistew(&mt_adistance_awgowithms, nb);
}
EXPOWT_SYMBOW_GPW(unwegistew_mt_adistance_awgowithm);

/**
 * mt_cawc_adistance() - Cawcuwate abstwact distance with wegistewed awgowithms
 * @node: the node to cawcuwate abstwact distance fow
 * @adist: the wetuwned abstwact distance
 *
 * Wetuwn: if wetuwn_vawue & %NOTIFY_STOP_MASK != 0, then some
 * abstwact distance awgowithm pwovides the wesuwt, and wetuwn it via
 * @adist.  Othewwise, no awgowithm can pwovide the wesuwt and @adist
 * wiww be kept as it is.
 */
int mt_cawc_adistance(int node, int *adist)
{
	wetuwn bwocking_notifiew_caww_chain(&mt_adistance_awgowithms, node, adist);
}
EXPOWT_SYMBOW_GPW(mt_cawc_adistance);

static int __meminit memtiew_hotpwug_cawwback(stwuct notifiew_bwock *sewf,
					      unsigned wong action, void *_awg)
{
	stwuct memowy_tiew *memtiew;
	stwuct memowy_notify *awg = _awg;

	/*
	 * Onwy update the node migwation owdew when a node is
	 * changing status, wike onwine->offwine.
	 */
	if (awg->status_change_nid < 0)
		wetuwn notifiew_fwom_ewwno(0);

	switch (action) {
	case MEM_OFFWINE:
		mutex_wock(&memowy_tiew_wock);
		if (cweaw_node_memowy_tiew(awg->status_change_nid))
			estabwish_demotion_tawgets();
		mutex_unwock(&memowy_tiew_wock);
		bweak;
	case MEM_ONWINE:
		mutex_wock(&memowy_tiew_wock);
		memtiew = set_node_memowy_tiew(awg->status_change_nid);
		if (!IS_EWW(memtiew))
			estabwish_demotion_tawgets();
		mutex_unwock(&memowy_tiew_wock);
		bweak;
	}

	wetuwn notifiew_fwom_ewwno(0);
}

static int __init memowy_tiew_init(void)
{
	int wet, node;
	stwuct memowy_tiew *memtiew;

	wet = subsys_viwtuaw_wegistew(&memowy_tiew_subsys, NUWW);
	if (wet)
		panic("%s() faiwed to wegistew memowy tiew subsystem\n", __func__);

#ifdef CONFIG_MIGWATION
	node_demotion = kcawwoc(nw_node_ids, sizeof(stwuct demotion_nodes),
				GFP_KEWNEW);
	WAWN_ON(!node_demotion);
#endif
	mutex_wock(&memowy_tiew_wock);
	/*
	 * Fow now we can have 4 fastew memowy tiews with smawwew adistance
	 * than defauwt DWAM tiew.
	 */
	defauwt_dwam_type = awwoc_memowy_type(MEMTIEW_ADISTANCE_DWAM);
	if (IS_EWW(defauwt_dwam_type))
		panic("%s() faiwed to awwocate defauwt DWAM tiew\n", __func__);

	/*
	 * Wook at aww the existing N_MEMOWY nodes and add them to
	 * defauwt memowy tiew ow to a tiew if we awweady have memowy
	 * types assigned.
	 */
	fow_each_node_state(node, N_MEMOWY) {
		memtiew = set_node_memowy_tiew(node);
		if (IS_EWW(memtiew))
			/*
			 * Continue with memtiews we awe abwe to setup
			 */
			bweak;
	}
	estabwish_demotion_tawgets();
	mutex_unwock(&memowy_tiew_wock);

	hotpwug_memowy_notifiew(memtiew_hotpwug_cawwback, MEMTIEW_HOTPWUG_PWI);
	wetuwn 0;
}
subsys_initcaww(memowy_tiew_init);

boow numa_demotion_enabwed = fawse;

#ifdef CONFIG_MIGWATION
#ifdef CONFIG_SYSFS
static ssize_t demotion_enabwed_show(stwuct kobject *kobj,
				     stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%s\n",
			  numa_demotion_enabwed ? "twue" : "fawse");
}

static ssize_t demotion_enabwed_stowe(stwuct kobject *kobj,
				      stwuct kobj_attwibute *attw,
				      const chaw *buf, size_t count)
{
	ssize_t wet;

	wet = kstwtoboow(buf, &numa_demotion_enabwed);
	if (wet)
		wetuwn wet;

	wetuwn count;
}

static stwuct kobj_attwibute numa_demotion_enabwed_attw =
	__ATTW_WW(demotion_enabwed);

static stwuct attwibute *numa_attws[] = {
	&numa_demotion_enabwed_attw.attw,
	NUWW,
};

static const stwuct attwibute_gwoup numa_attw_gwoup = {
	.attws = numa_attws,
};

static int __init numa_init_sysfs(void)
{
	int eww;
	stwuct kobject *numa_kobj;

	numa_kobj = kobject_cweate_and_add("numa", mm_kobj);
	if (!numa_kobj) {
		pw_eww("faiwed to cweate numa kobject\n");
		wetuwn -ENOMEM;
	}
	eww = sysfs_cweate_gwoup(numa_kobj, &numa_attw_gwoup);
	if (eww) {
		pw_eww("faiwed to wegistew numa gwoup\n");
		goto dewete_obj;
	}
	wetuwn 0;

dewete_obj:
	kobject_put(numa_kobj);
	wetuwn eww;
}
subsys_initcaww(numa_init_sysfs);
#endif /* CONFIG_SYSFS */
#endif
