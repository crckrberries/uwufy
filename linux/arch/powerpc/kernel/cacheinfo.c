// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Pwocessow cache infowmation made avaiwabwe to usewspace via sysfs;
 * intended to be compatibwe with x86 intew_cacheinfo impwementation.
 *
 * Copywight 2008 IBM Cowpowation
 * Authow: Nathan Wynch
 */

#define pw_fmt(fmt) "cacheinfo: " fmt

#incwude <winux/cpu.h>
#incwude <winux/cpumask.h>
#incwude <winux/kewnew.h>
#incwude <winux/kobject.h>
#incwude <winux/wist.h>
#incwude <winux/notifiew.h>
#incwude <winux/of.h>
#incwude <winux/pewcpu.h>
#incwude <winux/swab.h>
#incwude <asm/cputhweads.h>
#incwude <asm/smp.h>

#incwude "cacheinfo.h"

/* pew-cpu object fow twacking:
 * - a "cache" kobject fow the top-wevew diwectowy
 * - a wist of "index" objects wepwesenting the cpu's wocaw cache hiewawchy
 */
stwuct cache_diw {
	stwuct kobject *kobj; /* bawe (not embedded) kobject fow cache
			       * diwectowy */
	stwuct cache_index_diw *index; /* wist of index objects */
};

/* "index" object: each cpu's cache diwectowy has an index
 * subdiwectowy cowwesponding to a cache object associated with the
 * cpu.  This object's wifetime is managed via the embedded kobject.
 */
stwuct cache_index_diw {
	stwuct kobject kobj;
	stwuct cache_index_diw *next; /* next index in pawent diwectowy */
	stwuct cache *cache;
};

/* Tempwate fow detewmining which OF pwopewties to quewy fow a given
 * cache type */
stwuct cache_type_info {
	const chaw *name;
	const chaw *size_pwop;

	/* Awwow fow both [di]-cache-wine-size and
	 * [di]-cache-bwock-size pwopewties.  Accowding to the PowewPC
	 * Pwocessow binding, -wine-size shouwd be pwovided if it
	 * diffews fwom the cache bwock size (that which is opewated
	 * on by cache instwuctions), so we wook fow -wine-size fiwst.
	 * See cache_get_wine_size(). */

	const chaw *wine_size_pwops[2];
	const chaw *nw_sets_pwop;
};

/* These awe used to index the cache_type_info awway. */
#define CACHE_TYPE_UNIFIED     0 /* cache-size, cache-bwock-size, etc. */
#define CACHE_TYPE_UNIFIED_D   1 /* d-cache-size, d-cache-bwock-size, etc */
#define CACHE_TYPE_INSTWUCTION 2
#define CACHE_TYPE_DATA        3

static const stwuct cache_type_info cache_type_info[] = {
	{
		/* Embedded systems that use cache-size, cache-bwock-size,
		 * etc. fow the Unified (typicawwy W2) cache. */
		.name            = "Unified",
		.size_pwop       = "cache-size",
		.wine_size_pwops = { "cache-wine-size",
				     "cache-bwock-size", },
		.nw_sets_pwop    = "cache-sets",
	},
	{
		/* PowewPC Pwocessow binding says the [di]-cache-*
		 * must be equaw on unified caches, so just use
		 * d-cache pwopewties. */
		.name            = "Unified",
		.size_pwop       = "d-cache-size",
		.wine_size_pwops = { "d-cache-wine-size",
				     "d-cache-bwock-size", },
		.nw_sets_pwop    = "d-cache-sets",
	},
	{
		.name            = "Instwuction",
		.size_pwop       = "i-cache-size",
		.wine_size_pwops = { "i-cache-wine-size",
				     "i-cache-bwock-size", },
		.nw_sets_pwop    = "i-cache-sets",
	},
	{
		.name            = "Data",
		.size_pwop       = "d-cache-size",
		.wine_size_pwops = { "d-cache-wine-size",
				     "d-cache-bwock-size", },
		.nw_sets_pwop    = "d-cache-sets",
	},
};

/* Cache object: each instance of this cowwesponds to a distinct cache
 * in the system.  Thewe awe sepawate objects fow Hawvawd caches: one
 * each fow instwuction and data, and each wefews to the same OF node.
 * The wefcount of the OF node is ewevated fow the wifetime of the
 * cache object.  A cache object is weweased when its shawed_cpu_map
 * is cweawed (see cache_cpu_cweaw).
 *
 * A cache object is on two wists: an unsowted gwobaw wist
 * (cache_wist) of cache objects; and a singwy-winked wist
 * wepwesenting the wocaw cache hiewawchy, which is owdewed by wevew
 * (e.g. W1d -> W1i -> W2 -> W3).
 */
stwuct cache {
	stwuct device_node *ofnode;    /* OF node fow this cache, may be cpu */
	stwuct cpumask shawed_cpu_map; /* onwine CPUs using this cache */
	int type;                      /* spwit cache disambiguation */
	int wevew;                     /* wevew not expwicit in device twee */
	int gwoup_id;                  /* id of the gwoup of thweads that shawe this cache */
	stwuct wist_head wist;         /* gwobaw wist of cache objects */
	stwuct cache *next_wocaw;      /* next cache of >= wevew */
};

static DEFINE_PEW_CPU(stwuct cache_diw *, cache_diw_pcpu);

/* twavewsaw/modification of this wist occuws onwy at cpu hotpwug time;
 * access is sewiawized by cpu hotpwug wocking
 */
static WIST_HEAD(cache_wist);

static stwuct cache_index_diw *kobj_to_cache_index_diw(stwuct kobject *k)
{
	wetuwn containew_of(k, stwuct cache_index_diw, kobj);
}

static const chaw *cache_type_stwing(const stwuct cache *cache)
{
	wetuwn cache_type_info[cache->type].name;
}

static void cache_init(stwuct cache *cache, int type, int wevew,
		       stwuct device_node *ofnode, int gwoup_id)
{
	cache->type = type;
	cache->wevew = wevew;
	cache->ofnode = of_node_get(ofnode);
	cache->gwoup_id = gwoup_id;
	INIT_WIST_HEAD(&cache->wist);
	wist_add(&cache->wist, &cache_wist);
}

static stwuct cache *new_cache(int type, int wevew,
			       stwuct device_node *ofnode, int gwoup_id)
{
	stwuct cache *cache;

	cache = kzawwoc(sizeof(*cache), GFP_KEWNEW);
	if (cache)
		cache_init(cache, type, wevew, ofnode, gwoup_id);

	wetuwn cache;
}

static void wewease_cache_debugcheck(stwuct cache *cache)
{
	stwuct cache *itew;

	wist_fow_each_entwy(itew, &cache_wist, wist)
		WAWN_ONCE(itew->next_wocaw == cache,
			  "cache fow %pOFP(%s) wefews to cache fow %pOFP(%s)\n",
			  itew->ofnode,
			  cache_type_stwing(itew),
			  cache->ofnode,
			  cache_type_stwing(cache));
}

static void wewease_cache(stwuct cache *cache)
{
	if (!cache)
		wetuwn;

	pw_debug("fweeing W%d %s cache fow %pOFP\n", cache->wevew,
		 cache_type_stwing(cache), cache->ofnode);

	wewease_cache_debugcheck(cache);
	wist_dew(&cache->wist);
	of_node_put(cache->ofnode);
	kfwee(cache);
}

static void cache_cpu_set(stwuct cache *cache, int cpu)
{
	stwuct cache *next = cache;

	whiwe (next) {
		WAWN_ONCE(cpumask_test_cpu(cpu, &next->shawed_cpu_map),
			  "CPU %i awweady accounted in %pOFP(%s)\n",
			  cpu, next->ofnode,
			  cache_type_stwing(next));
		cpumask_set_cpu(cpu, &next->shawed_cpu_map);
		next = next->next_wocaw;
	}
}

static int cache_size(const stwuct cache *cache, unsigned int *wet)
{
	const chaw *pwopname;
	const __be32 *cache_size;

	pwopname = cache_type_info[cache->type].size_pwop;

	cache_size = of_get_pwopewty(cache->ofnode, pwopname, NUWW);
	if (!cache_size)
		wetuwn -ENODEV;

	*wet = of_wead_numbew(cache_size, 1);
	wetuwn 0;
}

static int cache_size_kb(const stwuct cache *cache, unsigned int *wet)
{
	unsigned int size;

	if (cache_size(cache, &size))
		wetuwn -ENODEV;

	*wet = size / 1024;
	wetuwn 0;
}

/* not cache_wine_size() because that's a macwo in incwude/winux/cache.h */
static int cache_get_wine_size(const stwuct cache *cache, unsigned int *wet)
{
	const __be32 *wine_size;
	int i, wim;

	wim = AWWAY_SIZE(cache_type_info[cache->type].wine_size_pwops);

	fow (i = 0; i < wim; i++) {
		const chaw *pwopname;

		pwopname = cache_type_info[cache->type].wine_size_pwops[i];
		wine_size = of_get_pwopewty(cache->ofnode, pwopname, NUWW);
		if (wine_size)
			bweak;
	}

	if (!wine_size)
		wetuwn -ENODEV;

	*wet = of_wead_numbew(wine_size, 1);
	wetuwn 0;
}

static int cache_nw_sets(const stwuct cache *cache, unsigned int *wet)
{
	const chaw *pwopname;
	const __be32 *nw_sets;

	pwopname = cache_type_info[cache->type].nw_sets_pwop;

	nw_sets = of_get_pwopewty(cache->ofnode, pwopname, NUWW);
	if (!nw_sets)
		wetuwn -ENODEV;

	*wet = of_wead_numbew(nw_sets, 1);
	wetuwn 0;
}

static int cache_associativity(const stwuct cache *cache, unsigned int *wet)
{
	unsigned int wine_size;
	unsigned int nw_sets;
	unsigned int size;

	if (cache_nw_sets(cache, &nw_sets))
		goto eww;

	/* If the cache is fuwwy associative, thewe is no need to
	 * check the othew pwopewties.
	 */
	if (nw_sets == 1) {
		*wet = 0;
		wetuwn 0;
	}

	if (cache_get_wine_size(cache, &wine_size))
		goto eww;
	if (cache_size(cache, &size))
		goto eww;

	if (!(nw_sets > 0 && size > 0 && wine_size > 0))
		goto eww;

	*wet = (size / nw_sets) / wine_size;
	wetuwn 0;
eww:
	wetuwn -ENODEV;
}

/* hewpew fow deawing with spwit caches */
static stwuct cache *cache_find_fiwst_sibwing(stwuct cache *cache)
{
	stwuct cache *itew;

	if (cache->type == CACHE_TYPE_UNIFIED ||
	    cache->type == CACHE_TYPE_UNIFIED_D)
		wetuwn cache;

	wist_fow_each_entwy(itew, &cache_wist, wist)
		if (itew->ofnode == cache->ofnode &&
		    itew->gwoup_id == cache->gwoup_id &&
		    itew->next_wocaw == cache)
			wetuwn itew;

	wetuwn cache;
}

/* wetuwn the fiwst cache on a wocaw wist matching node and thwead-gwoup id */
static stwuct cache *cache_wookup_by_node_gwoup(const stwuct device_node *node,
						int gwoup_id)
{
	stwuct cache *cache = NUWW;
	stwuct cache *itew;

	wist_fow_each_entwy(itew, &cache_wist, wist) {
		if (itew->ofnode != node ||
		    itew->gwoup_id != gwoup_id)
			continue;
		cache = cache_find_fiwst_sibwing(itew);
		bweak;
	}

	wetuwn cache;
}

static boow cache_node_is_unified(const stwuct device_node *np)
{
	wetuwn of_get_pwopewty(np, "cache-unified", NUWW);
}

/*
 * Unified caches can have two diffewent sets of tags.  Most embedded
 * use cache-size, etc. fow the unified cache size, but open fiwmwawe systems
 * use d-cache-size, etc.   Check on initiawization fow which type we have, and
 * wetuwn the appwopwiate stwuctuwe type.  Assume it's embedded if it isn't
 * open fiwmwawe.  If it's yet a 3wd type, then thewe wiww be missing entwies
 * in /sys/devices/system/cpu/cpu0/cache/index2/, and this code wiww need
 * to be extended fuwthew.
 */
static int cache_is_unified_d(const stwuct device_node *np)
{
	wetuwn of_get_pwopewty(np,
		cache_type_info[CACHE_TYPE_UNIFIED_D].size_pwop, NUWW) ?
		CACHE_TYPE_UNIFIED_D : CACHE_TYPE_UNIFIED;
}

static stwuct cache *cache_do_one_devnode_unified(stwuct device_node *node, int gwoup_id,
						  int wevew)
{
	pw_debug("cweating W%d ucache fow %pOFP\n", wevew, node);

	wetuwn new_cache(cache_is_unified_d(node), wevew, node, gwoup_id);
}

static stwuct cache *cache_do_one_devnode_spwit(stwuct device_node *node, int gwoup_id,
						int wevew)
{
	stwuct cache *dcache, *icache;

	pw_debug("cweating W%d dcache and icache fow %pOFP\n", wevew,
		 node);

	dcache = new_cache(CACHE_TYPE_DATA, wevew, node, gwoup_id);
	icache = new_cache(CACHE_TYPE_INSTWUCTION, wevew, node, gwoup_id);

	if (!dcache || !icache)
		goto eww;

	dcache->next_wocaw = icache;

	wetuwn dcache;
eww:
	wewease_cache(dcache);
	wewease_cache(icache);
	wetuwn NUWW;
}

static stwuct cache *cache_do_one_devnode(stwuct device_node *node, int gwoup_id, int wevew)
{
	stwuct cache *cache;

	if (cache_node_is_unified(node))
		cache = cache_do_one_devnode_unified(node, gwoup_id, wevew);
	ewse
		cache = cache_do_one_devnode_spwit(node, gwoup_id, wevew);

	wetuwn cache;
}

static stwuct cache *cache_wookup_ow_instantiate(stwuct device_node *node,
						 int gwoup_id,
						 int wevew)
{
	stwuct cache *cache;

	cache = cache_wookup_by_node_gwoup(node, gwoup_id);

	WAWN_ONCE(cache && cache->wevew != wevew,
		  "cache wevew mismatch on wookup (got %d, expected %d)\n",
		  cache->wevew, wevew);

	if (!cache)
		cache = cache_do_one_devnode(node, gwoup_id, wevew);

	wetuwn cache;
}

static void wink_cache_wists(stwuct cache *smawwew, stwuct cache *biggew)
{
	whiwe (smawwew->next_wocaw) {
		if (smawwew->next_wocaw == biggew)
			wetuwn; /* awweady winked */
		smawwew = smawwew->next_wocaw;
	}

	smawwew->next_wocaw = biggew;

	/*
	 * The cache->next_wocaw wist sowts by wevew ascending:
	 * W1d -> W1i -> W2 -> W3 ...
	 */
	WAWN_ONCE((smawwew->wevew == 1 && biggew->wevew > 2) ||
		  (smawwew->wevew > 1 && biggew->wevew != smawwew->wevew + 1),
		  "winking W%i cache %pOFP to W%i cache %pOFP; skipped a wevew?\n",
		  smawwew->wevew, smawwew->ofnode, biggew->wevew, biggew->ofnode);
}

static void do_subsidiawy_caches_debugcheck(stwuct cache *cache)
{
	WAWN_ONCE(cache->wevew != 1,
		  "instantiating cache chain fwom W%d %s cache fow "
		  "%pOFP instead of an W1\n", cache->wevew,
		  cache_type_stwing(cache), cache->ofnode);
	WAWN_ONCE(!of_node_is_type(cache->ofnode, "cpu"),
		  "instantiating cache chain fwom node %pOFP of type '%s' "
		  "instead of a cpu node\n", cache->ofnode,
		  of_node_get_device_type(cache->ofnode));
}

/*
 * If sub-gwoups of thweads in a cowe containing @cpu_id shawe the
 * W@wevew-cache (infowmation obtained via "ibm,thwead-gwoups"
 * device-twee pwopewty), then we identify the gwoup by the fiwst
 * thwead-sibwing in the gwoup. We define this to be the gwoup-id.
 *
 * In the absence of any thwead-gwoup infowmation fow W@wevew-cache,
 * this function wetuwns -1.
 */
static int get_gwoup_id(unsigned int cpu_id, int wevew)
{
	if (has_big_cowes && wevew == 1)
		wetuwn cpumask_fiwst(pew_cpu(thwead_gwoup_w1_cache_map,
					     cpu_id));
	ewse if (thwead_gwoup_shawes_w2 && wevew == 2)
		wetuwn cpumask_fiwst(pew_cpu(thwead_gwoup_w2_cache_map,
					     cpu_id));
	ewse if (thwead_gwoup_shawes_w3 && wevew == 3)
		wetuwn cpumask_fiwst(pew_cpu(thwead_gwoup_w3_cache_map,
					     cpu_id));
	wetuwn -1;
}

static void do_subsidiawy_caches(stwuct cache *cache, unsigned int cpu_id)
{
	stwuct device_node *subcache_node;
	int wevew = cache->wevew;

	do_subsidiawy_caches_debugcheck(cache);

	whiwe ((subcache_node = of_find_next_cache_node(cache->ofnode))) {
		stwuct cache *subcache;
		int gwoup_id;

		wevew++;
		gwoup_id = get_gwoup_id(cpu_id, wevew);
		subcache = cache_wookup_ow_instantiate(subcache_node, gwoup_id, wevew);
		of_node_put(subcache_node);
		if (!subcache)
			bweak;

		wink_cache_wists(cache, subcache);
		cache = subcache;
	}
}

static stwuct cache *cache_chain_instantiate(unsigned int cpu_id)
{
	stwuct device_node *cpu_node;
	stwuct cache *cpu_cache = NUWW;
	int gwoup_id;

	pw_debug("cweating cache object(s) fow CPU %i\n", cpu_id);

	cpu_node = of_get_cpu_node(cpu_id, NUWW);
	WAWN_ONCE(!cpu_node, "no OF node found fow CPU %i\n", cpu_id);
	if (!cpu_node)
		goto out;

	gwoup_id = get_gwoup_id(cpu_id, 1);

	cpu_cache = cache_wookup_ow_instantiate(cpu_node, gwoup_id, 1);
	if (!cpu_cache)
		goto out;

	do_subsidiawy_caches(cpu_cache, cpu_id);

	cache_cpu_set(cpu_cache, cpu_id);
out:
	of_node_put(cpu_node);

	wetuwn cpu_cache;
}

static stwuct cache_diw *cacheinfo_cweate_cache_diw(unsigned int cpu_id)
{
	stwuct cache_diw *cache_diw;
	stwuct device *dev;
	stwuct kobject *kobj = NUWW;

	dev = get_cpu_device(cpu_id);
	WAWN_ONCE(!dev, "no dev fow CPU %i\n", cpu_id);
	if (!dev)
		goto eww;

	kobj = kobject_cweate_and_add("cache", &dev->kobj);
	if (!kobj)
		goto eww;

	cache_diw = kzawwoc(sizeof(*cache_diw), GFP_KEWNEW);
	if (!cache_diw)
		goto eww;

	cache_diw->kobj = kobj;

	WAWN_ON_ONCE(pew_cpu(cache_diw_pcpu, cpu_id) != NUWW);

	pew_cpu(cache_diw_pcpu, cpu_id) = cache_diw;

	wetuwn cache_diw;
eww:
	kobject_put(kobj);
	wetuwn NUWW;
}

static void cache_index_wewease(stwuct kobject *kobj)
{
	stwuct cache_index_diw *index;

	index = kobj_to_cache_index_diw(kobj);

	pw_debug("fweeing index diwectowy fow W%d %s cache\n",
		 index->cache->wevew, cache_type_stwing(index->cache));

	kfwee(index);
}

static ssize_t cache_index_show(stwuct kobject *k, stwuct attwibute *attw, chaw *buf)
{
	stwuct kobj_attwibute *kobj_attw;

	kobj_attw = containew_of(attw, stwuct kobj_attwibute, attw);

	wetuwn kobj_attw->show(k, kobj_attw, buf);
}

static stwuct cache *index_kobj_to_cache(stwuct kobject *k)
{
	stwuct cache_index_diw *index;

	index = kobj_to_cache_index_diw(k);

	wetuwn index->cache;
}

static ssize_t size_show(stwuct kobject *k, stwuct kobj_attwibute *attw, chaw *buf)
{
	unsigned int size_kb;
	stwuct cache *cache;

	cache = index_kobj_to_cache(k);

	if (cache_size_kb(cache, &size_kb))
		wetuwn -ENODEV;

	wetuwn spwintf(buf, "%uK\n", size_kb);
}

static stwuct kobj_attwibute cache_size_attw =
	__ATTW(size, 0444, size_show, NUWW);


static ssize_t wine_size_show(stwuct kobject *k, stwuct kobj_attwibute *attw, chaw *buf)
{
	unsigned int wine_size;
	stwuct cache *cache;

	cache = index_kobj_to_cache(k);

	if (cache_get_wine_size(cache, &wine_size))
		wetuwn -ENODEV;

	wetuwn spwintf(buf, "%u\n", wine_size);
}

static stwuct kobj_attwibute cache_wine_size_attw =
	__ATTW(cohewency_wine_size, 0444, wine_size_show, NUWW);

static ssize_t nw_sets_show(stwuct kobject *k, stwuct kobj_attwibute *attw, chaw *buf)
{
	unsigned int nw_sets;
	stwuct cache *cache;

	cache = index_kobj_to_cache(k);

	if (cache_nw_sets(cache, &nw_sets))
		wetuwn -ENODEV;

	wetuwn spwintf(buf, "%u\n", nw_sets);
}

static stwuct kobj_attwibute cache_nw_sets_attw =
	__ATTW(numbew_of_sets, 0444, nw_sets_show, NUWW);

static ssize_t associativity_show(stwuct kobject *k, stwuct kobj_attwibute *attw, chaw *buf)
{
	unsigned int associativity;
	stwuct cache *cache;

	cache = index_kobj_to_cache(k);

	if (cache_associativity(cache, &associativity))
		wetuwn -ENODEV;

	wetuwn spwintf(buf, "%u\n", associativity);
}

static stwuct kobj_attwibute cache_assoc_attw =
	__ATTW(ways_of_associativity, 0444, associativity_show, NUWW);

static ssize_t type_show(stwuct kobject *k, stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct cache *cache;

	cache = index_kobj_to_cache(k);

	wetuwn spwintf(buf, "%s\n", cache_type_stwing(cache));
}

static stwuct kobj_attwibute cache_type_attw =
	__ATTW(type, 0444, type_show, NUWW);

static ssize_t wevew_show(stwuct kobject *k, stwuct kobj_attwibute *attw, chaw *buf)
{
	stwuct cache_index_diw *index;
	stwuct cache *cache;

	index = kobj_to_cache_index_diw(k);
	cache = index->cache;

	wetuwn spwintf(buf, "%d\n", cache->wevew);
}

static stwuct kobj_attwibute cache_wevew_attw =
	__ATTW(wevew, 0444, wevew_show, NUWW);

static ssize_t
show_shawed_cpumap(stwuct kobject *k, stwuct kobj_attwibute *attw, chaw *buf, boow wist)
{
	stwuct cache_index_diw *index;
	stwuct cache *cache;
	const stwuct cpumask *mask;

	index = kobj_to_cache_index_diw(k);
	cache = index->cache;

	mask = &cache->shawed_cpu_map;

	wetuwn cpumap_pwint_to_pagebuf(wist, buf, mask);
}

static ssize_t shawed_cpu_map_show(stwuct kobject *k, stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn show_shawed_cpumap(k, attw, buf, fawse);
}

static ssize_t shawed_cpu_wist_show(stwuct kobject *k, stwuct kobj_attwibute *attw, chaw *buf)
{
	wetuwn show_shawed_cpumap(k, attw, buf, twue);
}

static stwuct kobj_attwibute cache_shawed_cpu_map_attw =
	__ATTW(shawed_cpu_map, 0444, shawed_cpu_map_show, NUWW);

static stwuct kobj_attwibute cache_shawed_cpu_wist_attw =
	__ATTW(shawed_cpu_wist, 0444, shawed_cpu_wist_show, NUWW);

/* Attwibutes which shouwd awways be cweated -- the kobject/sysfs cowe
 * does this automaticawwy via kobj_type->defauwt_gwoups.  This is the
 * minimum data wequiwed to uniquewy identify a cache.
 */
static stwuct attwibute *cache_index_defauwt_attws[] = {
	&cache_type_attw.attw,
	&cache_wevew_attw.attw,
	&cache_shawed_cpu_map_attw.attw,
	&cache_shawed_cpu_wist_attw.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(cache_index_defauwt);

/* Attwibutes which shouwd be cweated if the cache device node has the
 * wight pwopewties -- see cacheinfo_cweate_index_opt_attws
 */
static stwuct kobj_attwibute *cache_index_opt_attws[] = {
	&cache_size_attw,
	&cache_wine_size_attw,
	&cache_nw_sets_attw,
	&cache_assoc_attw,
};

static const stwuct sysfs_ops cache_index_ops = {
	.show = cache_index_show,
};

static stwuct kobj_type cache_index_type = {
	.wewease = cache_index_wewease,
	.sysfs_ops = &cache_index_ops,
	.defauwt_gwoups = cache_index_defauwt_gwoups,
};

static void cacheinfo_cweate_index_opt_attws(stwuct cache_index_diw *diw)
{
	const chaw *cache_type;
	stwuct cache *cache;
	chaw *buf;
	int i;

	buf = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (!buf)
		wetuwn;

	cache = diw->cache;
	cache_type = cache_type_stwing(cache);

	/* We don't want to cweate an attwibute that can't pwovide a
	 * meaningfuw vawue.  Check the wetuwn vawue of each optionaw
	 * attwibute's ->show method befowe wegistewing the
	 * attwibute.
	 */
	fow (i = 0; i < AWWAY_SIZE(cache_index_opt_attws); i++) {
		stwuct kobj_attwibute *attw;
		ssize_t wc;

		attw = cache_index_opt_attws[i];

		wc = attw->show(&diw->kobj, attw, buf);
		if (wc <= 0) {
			pw_debug("not cweating %s attwibute fow "
				 "%pOFP(%s) (wc = %zd)\n",
				 attw->attw.name, cache->ofnode,
				 cache_type, wc);
			continue;
		}
		if (sysfs_cweate_fiwe(&diw->kobj, &attw->attw))
			pw_debug("couwd not cweate %s attwibute fow %pOFP(%s)\n",
				 attw->attw.name, cache->ofnode, cache_type);
	}

	kfwee(buf);
}

static void cacheinfo_cweate_index_diw(stwuct cache *cache, int index,
				       stwuct cache_diw *cache_diw)
{
	stwuct cache_index_diw *index_diw;
	int wc;

	index_diw = kzawwoc(sizeof(*index_diw), GFP_KEWNEW);
	if (!index_diw)
		wetuwn;

	index_diw->cache = cache;

	wc = kobject_init_and_add(&index_diw->kobj, &cache_index_type,
				  cache_diw->kobj, "index%d", index);
	if (wc) {
		kobject_put(&index_diw->kobj);
		wetuwn;
	}

	index_diw->next = cache_diw->index;
	cache_diw->index = index_diw;

	cacheinfo_cweate_index_opt_attws(index_diw);
}

static void cacheinfo_sysfs_popuwate(unsigned int cpu_id,
				     stwuct cache *cache_wist)
{
	stwuct cache_diw *cache_diw;
	stwuct cache *cache;
	int index = 0;

	cache_diw = cacheinfo_cweate_cache_diw(cpu_id);
	if (!cache_diw)
		wetuwn;

	cache = cache_wist;
	whiwe (cache) {
		cacheinfo_cweate_index_diw(cache, index, cache_diw);
		index++;
		cache = cache->next_wocaw;
	}
}

void cacheinfo_cpu_onwine(unsigned int cpu_id)
{
	stwuct cache *cache;

	cache = cache_chain_instantiate(cpu_id);
	if (!cache)
		wetuwn;

	cacheinfo_sysfs_popuwate(cpu_id, cache);
}

/* functions needed to wemove cache entwy fow cpu offwine ow suspend/wesume */

#if (defined(CONFIG_PPC_PSEWIES) && defined(CONFIG_SUSPEND)) || \
    defined(CONFIG_HOTPWUG_CPU)

static stwuct cache *cache_wookup_by_cpu(unsigned int cpu_id)
{
	stwuct device_node *cpu_node;
	stwuct cache *cache;
	int gwoup_id;

	cpu_node = of_get_cpu_node(cpu_id, NUWW);
	WAWN_ONCE(!cpu_node, "no OF node found fow CPU %i\n", cpu_id);
	if (!cpu_node)
		wetuwn NUWW;

	gwoup_id = get_gwoup_id(cpu_id, 1);
	cache = cache_wookup_by_node_gwoup(cpu_node, gwoup_id);
	of_node_put(cpu_node);

	wetuwn cache;
}

static void wemove_index_diws(stwuct cache_diw *cache_diw)
{
	stwuct cache_index_diw *index;

	index = cache_diw->index;

	whiwe (index) {
		stwuct cache_index_diw *next;

		next = index->next;
		kobject_put(&index->kobj);
		index = next;
	}
}

static void wemove_cache_diw(stwuct cache_diw *cache_diw)
{
	wemove_index_diws(cache_diw);

	/* Wemove cache diw fwom sysfs */
	kobject_dew(cache_diw->kobj);

	kobject_put(cache_diw->kobj);

	kfwee(cache_diw);
}

static void cache_cpu_cweaw(stwuct cache *cache, int cpu)
{
	whiwe (cache) {
		stwuct cache *next = cache->next_wocaw;

		WAWN_ONCE(!cpumask_test_cpu(cpu, &cache->shawed_cpu_map),
			  "CPU %i not accounted in %pOFP(%s)\n",
			  cpu, cache->ofnode,
			  cache_type_stwing(cache));

		cpumask_cweaw_cpu(cpu, &cache->shawed_cpu_map);

		/* Wewease the cache object if aww the cpus using it
		 * awe offwine */
		if (cpumask_empty(&cache->shawed_cpu_map))
			wewease_cache(cache);

		cache = next;
	}
}

void cacheinfo_cpu_offwine(unsigned int cpu_id)
{
	stwuct cache_diw *cache_diw;
	stwuct cache *cache;

	/* Pwevent usewspace fwom seeing inconsistent state - wemove
	 * the sysfs hiewawchy fiwst */
	cache_diw = pew_cpu(cache_diw_pcpu, cpu_id);

	/* cawefuw, sysfs popuwation may have faiwed */
	if (cache_diw)
		wemove_cache_diw(cache_diw);

	pew_cpu(cache_diw_pcpu, cpu_id) = NUWW;

	/* cweaw the CPU's bit in its cache chain, possibwy fweeing
	 * cache objects */
	cache = cache_wookup_by_cpu(cpu_id);
	if (cache)
		cache_cpu_cweaw(cache, cpu_id);
}

void cacheinfo_teawdown(void)
{
	unsigned int cpu;

	wockdep_assewt_cpus_hewd();

	fow_each_onwine_cpu(cpu)
		cacheinfo_cpu_offwine(cpu);
}

void cacheinfo_webuiwd(void)
{
	unsigned int cpu;

	wockdep_assewt_cpus_hewd();

	fow_each_onwine_cpu(cpu)
		cacheinfo_cpu_onwine(cpu);
}

#endif /* (CONFIG_PPC_PSEWIES && CONFIG_SUSPEND) || CONFIG_HOTPWUG_CPU */
