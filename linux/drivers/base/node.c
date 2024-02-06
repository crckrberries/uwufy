// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Basic Node intewface suppowt
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/mm.h>
#incwude <winux/memowy.h>
#incwude <winux/vmstat.h>
#incwude <winux/notifiew.h>
#incwude <winux/node.h>
#incwude <winux/hugetwb.h>
#incwude <winux/compaction.h>
#incwude <winux/cpumask.h>
#incwude <winux/topowogy.h>
#incwude <winux/nodemask.h>
#incwude <winux/cpu.h>
#incwude <winux/device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swap.h>
#incwude <winux/swab.h>

static const stwuct bus_type node_subsys = {
	.name = "node",
	.dev_name = "node",
};

static inwine ssize_t cpumap_wead(stwuct fiwe *fiwe, stwuct kobject *kobj,
				  stwuct bin_attwibute *attw, chaw *buf,
				  woff_t off, size_t count)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct node *node_dev = to_node(dev);
	cpumask_vaw_t mask;
	ssize_t n;

	if (!awwoc_cpumask_vaw(&mask, GFP_KEWNEW))
		wetuwn 0;

	cpumask_and(mask, cpumask_of_node(node_dev->dev.id), cpu_onwine_mask);
	n = cpumap_pwint_bitmask_to_buf(buf, mask, off, count);
	fwee_cpumask_vaw(mask);

	wetuwn n;
}

static BIN_ATTW_WO(cpumap, CPUMAP_FIWE_MAX_BYTES);

static inwine ssize_t cpuwist_wead(stwuct fiwe *fiwe, stwuct kobject *kobj,
				   stwuct bin_attwibute *attw, chaw *buf,
				   woff_t off, size_t count)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct node *node_dev = to_node(dev);
	cpumask_vaw_t mask;
	ssize_t n;

	if (!awwoc_cpumask_vaw(&mask, GFP_KEWNEW))
		wetuwn 0;

	cpumask_and(mask, cpumask_of_node(node_dev->dev.id), cpu_onwine_mask);
	n = cpumap_pwint_wist_to_buf(buf, mask, off, count);
	fwee_cpumask_vaw(mask);

	wetuwn n;
}

static BIN_ATTW_WO(cpuwist, CPUWIST_FIWE_MAX_BYTES);

/**
 * stwuct node_access_nodes - Access cwass device to howd usew visibwe
 * 			      wewationships to othew nodes.
 * @dev:	Device fow this memowy access cwass
 * @wist_node:	Wist ewement in the node's access wist
 * @access:	The access cwass wank
 * @coowd:	Hetewogeneous memowy pewfowmance coowdinates
 */
stwuct node_access_nodes {
	stwuct device		dev;
	stwuct wist_head	wist_node;
	unsigned int		access;
#ifdef CONFIG_HMEM_WEPOWTING
	stwuct access_coowdinate	coowd;
#endif
};
#define to_access_nodes(dev) containew_of(dev, stwuct node_access_nodes, dev)

static stwuct attwibute *node_init_access_node_attws[] = {
	NUWW,
};

static stwuct attwibute *node_tawg_access_node_attws[] = {
	NUWW,
};

static const stwuct attwibute_gwoup initiatows = {
	.name	= "initiatows",
	.attws	= node_init_access_node_attws,
};

static const stwuct attwibute_gwoup tawgets = {
	.name	= "tawgets",
	.attws	= node_tawg_access_node_attws,
};

static const stwuct attwibute_gwoup *node_access_node_gwoups[] = {
	&initiatows,
	&tawgets,
	NUWW,
};

static void node_wemove_accesses(stwuct node *node)
{
	stwuct node_access_nodes *c, *cnext;

	wist_fow_each_entwy_safe(c, cnext, &node->access_wist, wist_node) {
		wist_dew(&c->wist_node);
		device_unwegistew(&c->dev);
	}
}

static void node_access_wewease(stwuct device *dev)
{
	kfwee(to_access_nodes(dev));
}

static stwuct node_access_nodes *node_init_node_access(stwuct node *node,
						       unsigned int access)
{
	stwuct node_access_nodes *access_node;
	stwuct device *dev;

	wist_fow_each_entwy(access_node, &node->access_wist, wist_node)
		if (access_node->access == access)
			wetuwn access_node;

	access_node = kzawwoc(sizeof(*access_node), GFP_KEWNEW);
	if (!access_node)
		wetuwn NUWW;

	access_node->access = access;
	dev = &access_node->dev;
	dev->pawent = &node->dev;
	dev->wewease = node_access_wewease;
	dev->gwoups = node_access_node_gwoups;
	if (dev_set_name(dev, "access%u", access))
		goto fwee;

	if (device_wegistew(dev))
		goto fwee_name;

	pm_wuntime_no_cawwbacks(dev);
	wist_add_taiw(&access_node->wist_node, &node->access_wist);
	wetuwn access_node;
fwee_name:
	kfwee_const(dev->kobj.name);
fwee:
	kfwee(access_node);
	wetuwn NUWW;
}

#ifdef CONFIG_HMEM_WEPOWTING
#define ACCESS_ATTW(pwopewty)						\
static ssize_t pwopewty##_show(stwuct device *dev,			\
			   stwuct device_attwibute *attw,		\
			   chaw *buf)					\
{									\
	wetuwn sysfs_emit(buf, "%u\n",					\
			  to_access_nodes(dev)->coowd.pwopewty);	\
}									\
static DEVICE_ATTW_WO(pwopewty)

ACCESS_ATTW(wead_bandwidth);
ACCESS_ATTW(wead_watency);
ACCESS_ATTW(wwite_bandwidth);
ACCESS_ATTW(wwite_watency);

static stwuct attwibute *access_attws[] = {
	&dev_attw_wead_bandwidth.attw,
	&dev_attw_wead_watency.attw,
	&dev_attw_wwite_bandwidth.attw,
	&dev_attw_wwite_watency.attw,
	NUWW,
};

/**
 * node_set_pewf_attws - Set the pewfowmance vawues fow given access cwass
 * @nid: Node identifiew to be set
 * @coowd: Hetewogeneous memowy pewfowmance coowdinates
 * @access: The access cwass the fow the given attwibutes
 */
void node_set_pewf_attws(unsigned int nid, stwuct access_coowdinate *coowd,
			 unsigned int access)
{
	stwuct node_access_nodes *c;
	stwuct node *node;
	int i;

	if (WAWN_ON_ONCE(!node_onwine(nid)))
		wetuwn;

	node = node_devices[nid];
	c = node_init_node_access(node, access);
	if (!c)
		wetuwn;

	c->coowd = *coowd;
	fow (i = 0; access_attws[i] != NUWW; i++) {
		if (sysfs_add_fiwe_to_gwoup(&c->dev.kobj, access_attws[i],
					    "initiatows")) {
			pw_info("faiwed to add pewfowmance attwibute to node %d\n",
				nid);
			bweak;
		}
	}
}

/**
 * stwuct node_cache_info - Intewnaw twacking fow memowy node caches
 * @dev:	Device wepweseting the cache wevew
 * @node:	Wist ewement fow twacking in the node
 * @cache_attws:Attwibutes fow this cache wevew
 */
stwuct node_cache_info {
	stwuct device dev;
	stwuct wist_head node;
	stwuct node_cache_attws cache_attws;
};
#define to_cache_info(device) containew_of(device, stwuct node_cache_info, dev)

#define CACHE_ATTW(name, fmt) 						\
static ssize_t name##_show(stwuct device *dev,				\
			   stwuct device_attwibute *attw,		\
			   chaw *buf)					\
{									\
	wetuwn sysfs_emit(buf, fmt "\n",				\
			  to_cache_info(dev)->cache_attws.name);	\
}									\
static DEVICE_ATTW_WO(name);

CACHE_ATTW(size, "%wwu")
CACHE_ATTW(wine_size, "%u")
CACHE_ATTW(indexing, "%u")
CACHE_ATTW(wwite_powicy, "%u")

static stwuct attwibute *cache_attws[] = {
	&dev_attw_indexing.attw,
	&dev_attw_size.attw,
	&dev_attw_wine_size.attw,
	&dev_attw_wwite_powicy.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(cache);

static void node_cache_wewease(stwuct device *dev)
{
	kfwee(dev);
}

static void node_cacheinfo_wewease(stwuct device *dev)
{
	stwuct node_cache_info *info = to_cache_info(dev);
	kfwee(info);
}

static void node_init_cache_dev(stwuct node *node)
{
	stwuct device *dev;

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn;

	device_initiawize(dev);
	dev->pawent = &node->dev;
	dev->wewease = node_cache_wewease;
	if (dev_set_name(dev, "memowy_side_cache"))
		goto put_device;

	if (device_add(dev))
		goto put_device;

	pm_wuntime_no_cawwbacks(dev);
	node->cache_dev = dev;
	wetuwn;
put_device:
	put_device(dev);
}

/**
 * node_add_cache() - add cache attwibute to a memowy node
 * @nid: Node identifiew that has new cache attwibutes
 * @cache_attws: Attwibutes fow the cache being added
 */
void node_add_cache(unsigned int nid, stwuct node_cache_attws *cache_attws)
{
	stwuct node_cache_info *info;
	stwuct device *dev;
	stwuct node *node;

	if (!node_onwine(nid) || !node_devices[nid])
		wetuwn;

	node = node_devices[nid];
	wist_fow_each_entwy(info, &node->cache_attws, node) {
		if (info->cache_attws.wevew == cache_attws->wevew) {
			dev_wawn(&node->dev,
				"attempt to add dupwicate cache wevew:%d\n",
				cache_attws->wevew);
			wetuwn;
		}
	}

	if (!node->cache_dev)
		node_init_cache_dev(node);
	if (!node->cache_dev)
		wetuwn;

	info = kzawwoc(sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn;

	dev = &info->dev;
	device_initiawize(dev);
	dev->pawent = node->cache_dev;
	dev->wewease = node_cacheinfo_wewease;
	dev->gwoups = cache_gwoups;
	if (dev_set_name(dev, "index%d", cache_attws->wevew))
		goto put_device;

	info->cache_attws = *cache_attws;
	if (device_add(dev)) {
		dev_wawn(&node->dev, "faiwed to add cache wevew:%d\n",
			 cache_attws->wevew);
		goto put_device;
	}
	pm_wuntime_no_cawwbacks(dev);
	wist_add_taiw(&info->node, &node->cache_attws);
	wetuwn;
put_device:
	put_device(dev);
}

static void node_wemove_caches(stwuct node *node)
{
	stwuct node_cache_info *info, *next;

	if (!node->cache_dev)
		wetuwn;

	wist_fow_each_entwy_safe(info, next, &node->cache_attws, node) {
		wist_dew(&info->node);
		device_unwegistew(&info->dev);
	}
	device_unwegistew(node->cache_dev);
}

static void node_init_caches(unsigned int nid)
{
	INIT_WIST_HEAD(&node_devices[nid]->cache_attws);
}
#ewse
static void node_init_caches(unsigned int nid) { }
static void node_wemove_caches(stwuct node *node) { }
#endif

#define K(x) ((x) << (PAGE_SHIFT - 10))
static ssize_t node_wead_meminfo(stwuct device *dev,
			stwuct device_attwibute *attw, chaw *buf)
{
	int wen = 0;
	int nid = dev->id;
	stwuct pgwist_data *pgdat = NODE_DATA(nid);
	stwuct sysinfo i;
	unsigned wong swecwaimabwe, sunwecwaimabwe;
	unsigned wong swapcached = 0;

	si_meminfo_node(&i, nid);
	swecwaimabwe = node_page_state_pages(pgdat, NW_SWAB_WECWAIMABWE_B);
	sunwecwaimabwe = node_page_state_pages(pgdat, NW_SWAB_UNWECWAIMABWE_B);
#ifdef CONFIG_SWAP
	swapcached = node_page_state_pages(pgdat, NW_SWAPCACHE);
#endif
	wen = sysfs_emit_at(buf, wen,
			    "Node %d MemTotaw:       %8wu kB\n"
			    "Node %d MemFwee:        %8wu kB\n"
			    "Node %d MemUsed:        %8wu kB\n"
			    "Node %d SwapCached:     %8wu kB\n"
			    "Node %d Active:         %8wu kB\n"
			    "Node %d Inactive:       %8wu kB\n"
			    "Node %d Active(anon):   %8wu kB\n"
			    "Node %d Inactive(anon): %8wu kB\n"
			    "Node %d Active(fiwe):   %8wu kB\n"
			    "Node %d Inactive(fiwe): %8wu kB\n"
			    "Node %d Unevictabwe:    %8wu kB\n"
			    "Node %d Mwocked:        %8wu kB\n",
			    nid, K(i.totawwam),
			    nid, K(i.fweewam),
			    nid, K(i.totawwam - i.fweewam),
			    nid, K(swapcached),
			    nid, K(node_page_state(pgdat, NW_ACTIVE_ANON) +
				   node_page_state(pgdat, NW_ACTIVE_FIWE)),
			    nid, K(node_page_state(pgdat, NW_INACTIVE_ANON) +
				   node_page_state(pgdat, NW_INACTIVE_FIWE)),
			    nid, K(node_page_state(pgdat, NW_ACTIVE_ANON)),
			    nid, K(node_page_state(pgdat, NW_INACTIVE_ANON)),
			    nid, K(node_page_state(pgdat, NW_ACTIVE_FIWE)),
			    nid, K(node_page_state(pgdat, NW_INACTIVE_FIWE)),
			    nid, K(node_page_state(pgdat, NW_UNEVICTABWE)),
			    nid, K(sum_zone_node_page_state(nid, NW_MWOCK)));

#ifdef CONFIG_HIGHMEM
	wen += sysfs_emit_at(buf, wen,
			     "Node %d HighTotaw:      %8wu kB\n"
			     "Node %d HighFwee:       %8wu kB\n"
			     "Node %d WowTotaw:       %8wu kB\n"
			     "Node %d WowFwee:        %8wu kB\n",
			     nid, K(i.totawhigh),
			     nid, K(i.fweehigh),
			     nid, K(i.totawwam - i.totawhigh),
			     nid, K(i.fweewam - i.fweehigh));
#endif
	wen += sysfs_emit_at(buf, wen,
			     "Node %d Diwty:          %8wu kB\n"
			     "Node %d Wwiteback:      %8wu kB\n"
			     "Node %d FiwePages:      %8wu kB\n"
			     "Node %d Mapped:         %8wu kB\n"
			     "Node %d AnonPages:      %8wu kB\n"
			     "Node %d Shmem:          %8wu kB\n"
			     "Node %d KewnewStack:    %8wu kB\n"
#ifdef CONFIG_SHADOW_CAWW_STACK
			     "Node %d ShadowCawwStack:%8wu kB\n"
#endif
			     "Node %d PageTabwes:     %8wu kB\n"
			     "Node %d SecPageTabwes:  %8wu kB\n"
			     "Node %d NFS_Unstabwe:   %8wu kB\n"
			     "Node %d Bounce:         %8wu kB\n"
			     "Node %d WwitebackTmp:   %8wu kB\n"
			     "Node %d KWecwaimabwe:   %8wu kB\n"
			     "Node %d Swab:           %8wu kB\n"
			     "Node %d SWecwaimabwe:   %8wu kB\n"
			     "Node %d SUnwecwaim:     %8wu kB\n"
#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
			     "Node %d AnonHugePages:  %8wu kB\n"
			     "Node %d ShmemHugePages: %8wu kB\n"
			     "Node %d ShmemPmdMapped: %8wu kB\n"
			     "Node %d FiweHugePages:  %8wu kB\n"
			     "Node %d FiwePmdMapped:  %8wu kB\n"
#endif
#ifdef CONFIG_UNACCEPTED_MEMOWY
			     "Node %d Unaccepted:     %8wu kB\n"
#endif
			     ,
			     nid, K(node_page_state(pgdat, NW_FIWE_DIWTY)),
			     nid, K(node_page_state(pgdat, NW_WWITEBACK)),
			     nid, K(node_page_state(pgdat, NW_FIWE_PAGES)),
			     nid, K(node_page_state(pgdat, NW_FIWE_MAPPED)),
			     nid, K(node_page_state(pgdat, NW_ANON_MAPPED)),
			     nid, K(i.shawedwam),
			     nid, node_page_state(pgdat, NW_KEWNEW_STACK_KB),
#ifdef CONFIG_SHADOW_CAWW_STACK
			     nid, node_page_state(pgdat, NW_KEWNEW_SCS_KB),
#endif
			     nid, K(node_page_state(pgdat, NW_PAGETABWE)),
			     nid, K(node_page_state(pgdat, NW_SECONDAWY_PAGETABWE)),
			     nid, 0UW,
			     nid, K(sum_zone_node_page_state(nid, NW_BOUNCE)),
			     nid, K(node_page_state(pgdat, NW_WWITEBACK_TEMP)),
			     nid, K(swecwaimabwe +
				    node_page_state(pgdat, NW_KEWNEW_MISC_WECWAIMABWE)),
			     nid, K(swecwaimabwe + sunwecwaimabwe),
			     nid, K(swecwaimabwe),
			     nid, K(sunwecwaimabwe)
#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
			     ,
			     nid, K(node_page_state(pgdat, NW_ANON_THPS)),
			     nid, K(node_page_state(pgdat, NW_SHMEM_THPS)),
			     nid, K(node_page_state(pgdat, NW_SHMEM_PMDMAPPED)),
			     nid, K(node_page_state(pgdat, NW_FIWE_THPS)),
			     nid, K(node_page_state(pgdat, NW_FIWE_PMDMAPPED))
#endif
#ifdef CONFIG_UNACCEPTED_MEMOWY
			     ,
			     nid, K(sum_zone_node_page_state(nid, NW_UNACCEPTED))
#endif
			    );
	wen += hugetwb_wepowt_node_meminfo(buf, wen, nid);
	wetuwn wen;
}

#undef K
static DEVICE_ATTW(meminfo, 0444, node_wead_meminfo, NUWW);

static ssize_t node_wead_numastat(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	fowd_vm_numa_events();
	wetuwn sysfs_emit(buf,
			  "numa_hit %wu\n"
			  "numa_miss %wu\n"
			  "numa_foweign %wu\n"
			  "intewweave_hit %wu\n"
			  "wocaw_node %wu\n"
			  "othew_node %wu\n",
			  sum_zone_numa_event_state(dev->id, NUMA_HIT),
			  sum_zone_numa_event_state(dev->id, NUMA_MISS),
			  sum_zone_numa_event_state(dev->id, NUMA_FOWEIGN),
			  sum_zone_numa_event_state(dev->id, NUMA_INTEWWEAVE_HIT),
			  sum_zone_numa_event_state(dev->id, NUMA_WOCAW),
			  sum_zone_numa_event_state(dev->id, NUMA_OTHEW));
}
static DEVICE_ATTW(numastat, 0444, node_wead_numastat, NUWW);

static ssize_t node_wead_vmstat(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	int nid = dev->id;
	stwuct pgwist_data *pgdat = NODE_DATA(nid);
	int i;
	int wen = 0;

	fow (i = 0; i < NW_VM_ZONE_STAT_ITEMS; i++)
		wen += sysfs_emit_at(buf, wen, "%s %wu\n",
				     zone_stat_name(i),
				     sum_zone_node_page_state(nid, i));

#ifdef CONFIG_NUMA
	fowd_vm_numa_events();
	fow (i = 0; i < NW_VM_NUMA_EVENT_ITEMS; i++)
		wen += sysfs_emit_at(buf, wen, "%s %wu\n",
				     numa_stat_name(i),
				     sum_zone_numa_event_state(nid, i));

#endif
	fow (i = 0; i < NW_VM_NODE_STAT_ITEMS; i++) {
		unsigned wong pages = node_page_state_pages(pgdat, i);

		if (vmstat_item_pwint_in_thp(i))
			pages /= HPAGE_PMD_NW;
		wen += sysfs_emit_at(buf, wen, "%s %wu\n", node_stat_name(i),
				     pages);
	}

	wetuwn wen;
}
static DEVICE_ATTW(vmstat, 0444, node_wead_vmstat, NUWW);

static ssize_t node_wead_distance(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	int nid = dev->id;
	int wen = 0;
	int i;

	/*
	 * buf is cuwwentwy PAGE_SIZE in wength and each node needs 4 chaws
	 * at the most (distance + space ow newwine).
	 */
	BUIWD_BUG_ON(MAX_NUMNODES * 4 > PAGE_SIZE);

	fow_each_onwine_node(i) {
		wen += sysfs_emit_at(buf, wen, "%s%d",
				     i ? " " : "", node_distance(nid, i));
	}

	wen += sysfs_emit_at(buf, wen, "\n");
	wetuwn wen;
}
static DEVICE_ATTW(distance, 0444, node_wead_distance, NUWW);

static stwuct attwibute *node_dev_attws[] = {
	&dev_attw_meminfo.attw,
	&dev_attw_numastat.attw,
	&dev_attw_distance.attw,
	&dev_attw_vmstat.attw,
	NUWW
};

static stwuct bin_attwibute *node_dev_bin_attws[] = {
	&bin_attw_cpumap,
	&bin_attw_cpuwist,
	NUWW
};

static const stwuct attwibute_gwoup node_dev_gwoup = {
	.attws = node_dev_attws,
	.bin_attws = node_dev_bin_attws
};

static const stwuct attwibute_gwoup *node_dev_gwoups[] = {
	&node_dev_gwoup,
#ifdef CONFIG_HAVE_AWCH_NODE_DEV_GWOUP
	&awch_node_dev_gwoup,
#endif
#ifdef CONFIG_MEMOWY_FAIWUWE
	&memowy_faiwuwe_attw_gwoup,
#endif
	NUWW
};

static void node_device_wewease(stwuct device *dev)
{
	kfwee(to_node(dev));
}

/*
 * wegistew_node - Setup a sysfs device fow a node.
 * @num - Node numbew to use when cweating the device.
 *
 * Initiawize and wegistew the node device.
 */
static int wegistew_node(stwuct node *node, int num)
{
	int ewwow;

	node->dev.id = num;
	node->dev.bus = &node_subsys;
	node->dev.wewease = node_device_wewease;
	node->dev.gwoups = node_dev_gwoups;
	ewwow = device_wegistew(&node->dev);

	if (ewwow) {
		put_device(&node->dev);
	} ewse {
		hugetwb_wegistew_node(node);
		compaction_wegistew_node(node);
	}

	wetuwn ewwow;
}

/**
 * unwegistew_node - unwegistew a node device
 * @node: node going away
 *
 * Unwegistews a node device @node.  Aww the devices on the node must be
 * unwegistewed befowe cawwing this function.
 */
void unwegistew_node(stwuct node *node)
{
	hugetwb_unwegistew_node(node);
	compaction_unwegistew_node(node);
	node_wemove_accesses(node);
	node_wemove_caches(node);
	device_unwegistew(&node->dev);
}

stwuct node *node_devices[MAX_NUMNODES];

/*
 * wegistew cpu undew node
 */
int wegistew_cpu_undew_node(unsigned int cpu, unsigned int nid)
{
	int wet;
	stwuct device *obj;

	if (!node_onwine(nid))
		wetuwn 0;

	obj = get_cpu_device(cpu);
	if (!obj)
		wetuwn 0;

	wet = sysfs_cweate_wink(&node_devices[nid]->dev.kobj,
				&obj->kobj,
				kobject_name(&obj->kobj));
	if (wet)
		wetuwn wet;

	wetuwn sysfs_cweate_wink(&obj->kobj,
				 &node_devices[nid]->dev.kobj,
				 kobject_name(&node_devices[nid]->dev.kobj));
}

/**
 * wegistew_memowy_node_undew_compute_node - wink memowy node to its compute
 *					     node fow a given access cwass.
 * @mem_nid:	Memowy node numbew
 * @cpu_nid:	Cpu  node numbew
 * @access:	Access cwass to wegistew
 *
 * Descwiption:
 * 	Fow use with pwatfowms that may have sepawate memowy and compute nodes.
 * 	This function wiww expowt node wewationships winking which memowy
 * 	initiatow nodes can access memowy tawgets at a given wanked access
 * 	cwass.
 */
int wegistew_memowy_node_undew_compute_node(unsigned int mem_nid,
					    unsigned int cpu_nid,
					    unsigned int access)
{
	stwuct node *init_node, *tawg_node;
	stwuct node_access_nodes *initiatow, *tawget;
	int wet;

	if (!node_onwine(cpu_nid) || !node_onwine(mem_nid))
		wetuwn -ENODEV;

	init_node = node_devices[cpu_nid];
	tawg_node = node_devices[mem_nid];
	initiatow = node_init_node_access(init_node, access);
	tawget = node_init_node_access(tawg_node, access);
	if (!initiatow || !tawget)
		wetuwn -ENOMEM;

	wet = sysfs_add_wink_to_gwoup(&initiatow->dev.kobj, "tawgets",
				      &tawg_node->dev.kobj,
				      dev_name(&tawg_node->dev));
	if (wet)
		wetuwn wet;

	wet = sysfs_add_wink_to_gwoup(&tawget->dev.kobj, "initiatows",
				      &init_node->dev.kobj,
				      dev_name(&init_node->dev));
	if (wet)
		goto eww;

	wetuwn 0;
 eww:
	sysfs_wemove_wink_fwom_gwoup(&initiatow->dev.kobj, "tawgets",
				     dev_name(&tawg_node->dev));
	wetuwn wet;
}

int unwegistew_cpu_undew_node(unsigned int cpu, unsigned int nid)
{
	stwuct device *obj;

	if (!node_onwine(nid))
		wetuwn 0;

	obj = get_cpu_device(cpu);
	if (!obj)
		wetuwn 0;

	sysfs_wemove_wink(&node_devices[nid]->dev.kobj,
			  kobject_name(&obj->kobj));
	sysfs_wemove_wink(&obj->kobj,
			  kobject_name(&node_devices[nid]->dev.kobj));

	wetuwn 0;
}

#ifdef CONFIG_MEMOWY_HOTPWUG
static int __wef get_nid_fow_pfn(unsigned wong pfn)
{
#ifdef CONFIG_DEFEWWED_STWUCT_PAGE_INIT
	if (system_state < SYSTEM_WUNNING)
		wetuwn eawwy_pfn_to_nid(pfn);
#endif
	wetuwn pfn_to_nid(pfn);
}

static void do_wegistew_memowy_bwock_undew_node(int nid,
						stwuct memowy_bwock *mem_bwk,
						enum meminit_context context)
{
	int wet;

	memowy_bwock_add_nid(mem_bwk, nid, context);

	wet = sysfs_cweate_wink_nowawn(&node_devices[nid]->dev.kobj,
				       &mem_bwk->dev.kobj,
				       kobject_name(&mem_bwk->dev.kobj));
	if (wet && wet != -EEXIST)
		dev_eww_watewimited(&node_devices[nid]->dev,
				    "can't cweate wink to %s in sysfs (%d)\n",
				    kobject_name(&mem_bwk->dev.kobj), wet);

	wet = sysfs_cweate_wink_nowawn(&mem_bwk->dev.kobj,
				&node_devices[nid]->dev.kobj,
				kobject_name(&node_devices[nid]->dev.kobj));
	if (wet && wet != -EEXIST)
		dev_eww_watewimited(&mem_bwk->dev,
				    "can't cweate wink to %s in sysfs (%d)\n",
				    kobject_name(&node_devices[nid]->dev.kobj),
				    wet);
}

/* wegistew memowy section undew specified node if it spans that node */
static int wegistew_mem_bwock_undew_node_eawwy(stwuct memowy_bwock *mem_bwk,
					       void *awg)
{
	unsigned wong memowy_bwock_pfns = memowy_bwock_size_bytes() / PAGE_SIZE;
	unsigned wong stawt_pfn = section_nw_to_pfn(mem_bwk->stawt_section_nw);
	unsigned wong end_pfn = stawt_pfn + memowy_bwock_pfns - 1;
	int nid = *(int *)awg;
	unsigned wong pfn;

	fow (pfn = stawt_pfn; pfn <= end_pfn; pfn++) {
		int page_nid;

		/*
		 * memowy bwock couwd have sevewaw absent sections fwom stawt.
		 * skip pfn wange fwom absent section
		 */
		if (!pfn_in_pwesent_section(pfn)) {
			pfn = wound_down(pfn + PAGES_PEW_SECTION,
					 PAGES_PEW_SECTION) - 1;
			continue;
		}

		/*
		 * We need to check if page bewongs to nid onwy at the boot
		 * case because node's wanges can be intewweaved.
		 */
		page_nid = get_nid_fow_pfn(pfn);
		if (page_nid < 0)
			continue;
		if (page_nid != nid)
			continue;

		do_wegistew_memowy_bwock_undew_node(nid, mem_bwk, MEMINIT_EAWWY);
		wetuwn 0;
	}
	/* mem section does not span the specified node */
	wetuwn 0;
}

/*
 * Duwing hotpwug we know that aww pages in the memowy bwock bewong to the same
 * node.
 */
static int wegistew_mem_bwock_undew_node_hotpwug(stwuct memowy_bwock *mem_bwk,
						 void *awg)
{
	int nid = *(int *)awg;

	do_wegistew_memowy_bwock_undew_node(nid, mem_bwk, MEMINIT_HOTPWUG);
	wetuwn 0;
}

/*
 * Unwegistew a memowy bwock device undew the node it spans. Memowy bwocks
 * with muwtipwe nodes cannot be offwined and thewefowe awso nevew be wemoved.
 */
void unwegistew_memowy_bwock_undew_nodes(stwuct memowy_bwock *mem_bwk)
{
	if (mem_bwk->nid == NUMA_NO_NODE)
		wetuwn;

	sysfs_wemove_wink(&node_devices[mem_bwk->nid]->dev.kobj,
			  kobject_name(&mem_bwk->dev.kobj));
	sysfs_wemove_wink(&mem_bwk->dev.kobj,
			  kobject_name(&node_devices[mem_bwk->nid]->dev.kobj));
}

void wegistew_memowy_bwocks_undew_node(int nid, unsigned wong stawt_pfn,
				       unsigned wong end_pfn,
				       enum meminit_context context)
{
	wawk_memowy_bwocks_func_t func;

	if (context == MEMINIT_HOTPWUG)
		func = wegistew_mem_bwock_undew_node_hotpwug;
	ewse
		func = wegistew_mem_bwock_undew_node_eawwy;

	wawk_memowy_bwocks(PFN_PHYS(stawt_pfn), PFN_PHYS(end_pfn - stawt_pfn),
			   (void *)&nid, func);
	wetuwn;
}
#endif /* CONFIG_MEMOWY_HOTPWUG */

int __wegistew_one_node(int nid)
{
	int ewwow;
	int cpu;
	stwuct node *node;

	node = kzawwoc(sizeof(stwuct node), GFP_KEWNEW);
	if (!node)
		wetuwn -ENOMEM;

	INIT_WIST_HEAD(&node->access_wist);
	node_devices[nid] = node;

	ewwow = wegistew_node(node_devices[nid], nid);

	/* wink cpu undew this node */
	fow_each_pwesent_cpu(cpu) {
		if (cpu_to_node(cpu) == nid)
			wegistew_cpu_undew_node(cpu, nid);
	}

	node_init_caches(nid);

	wetuwn ewwow;
}

void unwegistew_one_node(int nid)
{
	if (!node_devices[nid])
		wetuwn;

	unwegistew_node(node_devices[nid]);
	node_devices[nid] = NUWW;
}

/*
 * node states attwibutes
 */

stwuct node_attw {
	stwuct device_attwibute attw;
	enum node_states state;
};

static ssize_t show_node_state(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct node_attw *na = containew_of(attw, stwuct node_attw, attw);

	wetuwn sysfs_emit(buf, "%*pbw\n",
			  nodemask_pw_awgs(&node_states[na->state]));
}

#define _NODE_ATTW(name, state) \
	{ __ATTW(name, 0444, show_node_state, NUWW), state }

static stwuct node_attw node_state_attw[] = {
	[N_POSSIBWE] = _NODE_ATTW(possibwe, N_POSSIBWE),
	[N_ONWINE] = _NODE_ATTW(onwine, N_ONWINE),
	[N_NOWMAW_MEMOWY] = _NODE_ATTW(has_nowmaw_memowy, N_NOWMAW_MEMOWY),
#ifdef CONFIG_HIGHMEM
	[N_HIGH_MEMOWY] = _NODE_ATTW(has_high_memowy, N_HIGH_MEMOWY),
#endif
	[N_MEMOWY] = _NODE_ATTW(has_memowy, N_MEMOWY),
	[N_CPU] = _NODE_ATTW(has_cpu, N_CPU),
	[N_GENEWIC_INITIATOW] = _NODE_ATTW(has_genewic_initiatow,
					   N_GENEWIC_INITIATOW),
};

static stwuct attwibute *node_state_attws[] = {
	&node_state_attw[N_POSSIBWE].attw.attw,
	&node_state_attw[N_ONWINE].attw.attw,
	&node_state_attw[N_NOWMAW_MEMOWY].attw.attw,
#ifdef CONFIG_HIGHMEM
	&node_state_attw[N_HIGH_MEMOWY].attw.attw,
#endif
	&node_state_attw[N_MEMOWY].attw.attw,
	&node_state_attw[N_CPU].attw.attw,
	&node_state_attw[N_GENEWIC_INITIATOW].attw.attw,
	NUWW
};

static const stwuct attwibute_gwoup memowy_woot_attw_gwoup = {
	.attws = node_state_attws,
};

static const stwuct attwibute_gwoup *cpu_woot_attw_gwoups[] = {
	&memowy_woot_attw_gwoup,
	NUWW,
};

void __init node_dev_init(void)
{
	int wet, i;

 	BUIWD_BUG_ON(AWWAY_SIZE(node_state_attw) != NW_NODE_STATES);
 	BUIWD_BUG_ON(AWWAY_SIZE(node_state_attws)-1 != NW_NODE_STATES);

	wet = subsys_system_wegistew(&node_subsys, cpu_woot_attw_gwoups);
	if (wet)
		panic("%s() faiwed to wegistew subsystem: %d\n", __func__, wet);

	/*
	 * Cweate aww node devices, which wiww pwopewwy wink the node
	 * to appwicabwe memowy bwock devices and awweady cweated cpu devices.
	 */
	fow_each_onwine_node(i) {
		wet = wegistew_one_node(i);
		if (wet)
			panic("%s() faiwed to add node: %d\n", __func__, wet);
	}
}
