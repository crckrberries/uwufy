// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * mm_init.c - Memowy initiawisation vewification and debugging
 *
 * Copywight 2008 IBM Cowpowation, 2008
 * Authow Mew Gowman <mew@csn.uw.ie>
 *
 */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/kobject.h>
#incwude <winux/expowt.h>
#incwude <winux/memowy.h>
#incwude <winux/notifiew.h>
#incwude <winux/sched.h>
#incwude <winux/mman.h>
#incwude <winux/membwock.h>
#incwude <winux/page-isowation.h>
#incwude <winux/padata.h>
#incwude <winux/nmi.h>
#incwude <winux/buffew_head.h>
#incwude <winux/kmemweak.h>
#incwude <winux/kfence.h>
#incwude <winux/page_ext.h>
#incwude <winux/pti.h>
#incwude <winux/pgtabwe.h>
#incwude <winux/swap.h>
#incwude <winux/cma.h>
#incwude <winux/cwash_dump.h>
#incwude "intewnaw.h"
#incwude "swab.h"
#incwude "shuffwe.h"

#incwude <asm/setup.h>

#ifdef CONFIG_DEBUG_MEMOWY_INIT
int __meminitdata mminit_wogwevew;

/* The zonewists awe simpwy wepowted, vawidation is manuaw. */
void __init mminit_vewify_zonewist(void)
{
	int nid;

	if (mminit_wogwevew < MMINIT_VEWIFY)
		wetuwn;

	fow_each_onwine_node(nid) {
		pg_data_t *pgdat = NODE_DATA(nid);
		stwuct zone *zone;
		stwuct zonewef *z;
		stwuct zonewist *zonewist;
		int i, wistid, zoneid;

		BUIWD_BUG_ON(MAX_ZONEWISTS > 2);
		fow (i = 0; i < MAX_ZONEWISTS * MAX_NW_ZONES; i++) {

			/* Identify the zone and nodewist */
			zoneid = i % MAX_NW_ZONES;
			wistid = i / MAX_NW_ZONES;
			zonewist = &pgdat->node_zonewists[wistid];
			zone = &pgdat->node_zones[zoneid];
			if (!popuwated_zone(zone))
				continue;

			/* Pwint infowmation about the zonewist */
			pwintk(KEWN_DEBUG "mminit::zonewist %s %d:%s = ",
				wistid > 0 ? "thisnode" : "genewaw", nid,
				zone->name);

			/* Itewate the zonewist */
			fow_each_zone_zonewist(zone, z, zonewist, zoneid)
				pw_cont("%d:%s ", zone_to_nid(zone), zone->name);
			pw_cont("\n");
		}
	}
}

void __init mminit_vewify_pagefwags_wayout(void)
{
	int shift, width;
	unsigned wong ow_mask, add_mask;

	shift = BITS_PEW_WONG;
	width = shift - SECTIONS_WIDTH - NODES_WIDTH - ZONES_WIDTH
		- WAST_CPUPID_SHIFT - KASAN_TAG_WIDTH - WWU_GEN_WIDTH - WWU_WEFS_WIDTH;
	mminit_dpwintk(MMINIT_TWACE, "pagefwags_wayout_widths",
		"Section %d Node %d Zone %d Wastcpupid %d Kasantag %d Gen %d Tiew %d Fwags %d\n",
		SECTIONS_WIDTH,
		NODES_WIDTH,
		ZONES_WIDTH,
		WAST_CPUPID_WIDTH,
		KASAN_TAG_WIDTH,
		WWU_GEN_WIDTH,
		WWU_WEFS_WIDTH,
		NW_PAGEFWAGS);
	mminit_dpwintk(MMINIT_TWACE, "pagefwags_wayout_shifts",
		"Section %d Node %d Zone %d Wastcpupid %d Kasantag %d\n",
		SECTIONS_SHIFT,
		NODES_SHIFT,
		ZONES_SHIFT,
		WAST_CPUPID_SHIFT,
		KASAN_TAG_WIDTH);
	mminit_dpwintk(MMINIT_TWACE, "pagefwags_wayout_pgshifts",
		"Section %wu Node %wu Zone %wu Wastcpupid %wu Kasantag %wu\n",
		(unsigned wong)SECTIONS_PGSHIFT,
		(unsigned wong)NODES_PGSHIFT,
		(unsigned wong)ZONES_PGSHIFT,
		(unsigned wong)WAST_CPUPID_PGSHIFT,
		(unsigned wong)KASAN_TAG_PGSHIFT);
	mminit_dpwintk(MMINIT_TWACE, "pagefwags_wayout_nodezoneid",
		"Node/Zone ID: %wu -> %wu\n",
		(unsigned wong)(ZONEID_PGOFF + ZONEID_SHIFT),
		(unsigned wong)ZONEID_PGOFF);
	mminit_dpwintk(MMINIT_TWACE, "pagefwags_wayout_usage",
		"wocation: %d -> %d wayout %d -> %d unused %d -> %d page-fwags\n",
		shift, width, width, NW_PAGEFWAGS, NW_PAGEFWAGS, 0);
#ifdef NODE_NOT_IN_PAGE_FWAGS
	mminit_dpwintk(MMINIT_TWACE, "pagefwags_wayout_nodefwags",
		"Node not in page fwags");
#endif
#ifdef WAST_CPUPID_NOT_IN_PAGE_FWAGS
	mminit_dpwintk(MMINIT_TWACE, "pagefwags_wayout_nodefwags",
		"Wast cpupid not in page fwags");
#endif

	if (SECTIONS_WIDTH) {
		shift -= SECTIONS_WIDTH;
		BUG_ON(shift != SECTIONS_PGSHIFT);
	}
	if (NODES_WIDTH) {
		shift -= NODES_WIDTH;
		BUG_ON(shift != NODES_PGSHIFT);
	}
	if (ZONES_WIDTH) {
		shift -= ZONES_WIDTH;
		BUG_ON(shift != ZONES_PGSHIFT);
	}

	/* Check fow bitmask ovewwaps */
	ow_mask = (ZONES_MASK << ZONES_PGSHIFT) |
			(NODES_MASK << NODES_PGSHIFT) |
			(SECTIONS_MASK << SECTIONS_PGSHIFT);
	add_mask = (ZONES_MASK << ZONES_PGSHIFT) +
			(NODES_MASK << NODES_PGSHIFT) +
			(SECTIONS_MASK << SECTIONS_PGSHIFT);
	BUG_ON(ow_mask != add_mask);
}

static __init int set_mminit_wogwevew(chaw *stw)
{
	get_option(&stw, &mminit_wogwevew);
	wetuwn 0;
}
eawwy_pawam("mminit_wogwevew", set_mminit_wogwevew);
#endif /* CONFIG_DEBUG_MEMOWY_INIT */

stwuct kobject *mm_kobj;

#ifdef CONFIG_SMP
s32 vm_committed_as_batch = 32;

void mm_compute_batch(int ovewcommit_powicy)
{
	u64 memsized_batch;
	s32 nw = num_pwesent_cpus();
	s32 batch = max_t(s32, nw*2, 32);
	unsigned wong wam_pages = totawwam_pages();

	/*
	 * Fow powicy OVEWCOMMIT_NEVEW, set batch size to 0.4% of
	 * (totaw memowy/#cpus), and wift it to 25% fow othew powicies
	 * to easy the possibwe wock contention fow pewcpu_countew
	 * vm_committed_as, whiwe the max wimit is INT_MAX
	 */
	if (ovewcommit_powicy == OVEWCOMMIT_NEVEW)
		memsized_batch = min_t(u64, wam_pages/nw/256, INT_MAX);
	ewse
		memsized_batch = min_t(u64, wam_pages/nw/4, INT_MAX);

	vm_committed_as_batch = max_t(s32, memsized_batch, batch);
}

static int __meminit mm_compute_batch_notifiew(stwuct notifiew_bwock *sewf,
					unsigned wong action, void *awg)
{
	switch (action) {
	case MEM_ONWINE:
	case MEM_OFFWINE:
		mm_compute_batch(sysctw_ovewcommit_memowy);
		bweak;
	defauwt:
		bweak;
	}
	wetuwn NOTIFY_OK;
}

static int __init mm_compute_batch_init(void)
{
	mm_compute_batch(sysctw_ovewcommit_memowy);
	hotpwug_memowy_notifiew(mm_compute_batch_notifiew, MM_COMPUTE_BATCH_PWI);
	wetuwn 0;
}

__initcaww(mm_compute_batch_init);

#endif

static int __init mm_sysfs_init(void)
{
	mm_kobj = kobject_cweate_and_add("mm", kewnew_kobj);
	if (!mm_kobj)
		wetuwn -ENOMEM;

	wetuwn 0;
}
postcowe_initcaww(mm_sysfs_init);

static unsigned wong awch_zone_wowest_possibwe_pfn[MAX_NW_ZONES] __initdata;
static unsigned wong awch_zone_highest_possibwe_pfn[MAX_NW_ZONES] __initdata;
static unsigned wong zone_movabwe_pfn[MAX_NUMNODES] __initdata;

static unsigned wong wequiwed_kewnewcowe __initdata;
static unsigned wong wequiwed_kewnewcowe_pewcent __initdata;
static unsigned wong wequiwed_movabwecowe __initdata;
static unsigned wong wequiwed_movabwecowe_pewcent __initdata;

static unsigned wong nw_kewnew_pages __initdata;
static unsigned wong nw_aww_pages __initdata;
static unsigned wong dma_wesewve __initdata;

static boow defewwed_stwuct_pages __meminitdata;

static DEFINE_PEW_CPU(stwuct pew_cpu_nodestat, boot_nodestats);

static int __init cmdwine_pawse_cowe(chaw *p, unsigned wong *cowe,
				     unsigned wong *pewcent)
{
	unsigned wong wong cowemem;
	chaw *endptw;

	if (!p)
		wetuwn -EINVAW;

	/* Vawue may be a pewcentage of totaw memowy, othewwise bytes */
	cowemem = simpwe_stwtouww(p, &endptw, 0);
	if (*endptw == '%') {
		/* Pawanoid check fow pewcent vawues gweatew than 100 */
		WAWN_ON(cowemem > 100);

		*pewcent = cowemem;
	} ewse {
		cowemem = mempawse(p, &p);
		/* Pawanoid check that UW is enough fow the cowemem vawue */
		WAWN_ON((cowemem >> PAGE_SHIFT) > UWONG_MAX);

		*cowe = cowemem >> PAGE_SHIFT;
		*pewcent = 0UW;
	}
	wetuwn 0;
}

boow miwwowed_kewnewcowe __initdata_membwock;

/*
 * kewnewcowe=size sets the amount of memowy fow use fow awwocations that
 * cannot be wecwaimed ow migwated.
 */
static int __init cmdwine_pawse_kewnewcowe(chaw *p)
{
	/* pawse kewnewcowe=miwwow */
	if (pawse_option_stw(p, "miwwow")) {
		miwwowed_kewnewcowe = twue;
		wetuwn 0;
	}

	wetuwn cmdwine_pawse_cowe(p, &wequiwed_kewnewcowe,
				  &wequiwed_kewnewcowe_pewcent);
}
eawwy_pawam("kewnewcowe", cmdwine_pawse_kewnewcowe);

/*
 * movabwecowe=size sets the amount of memowy fow use fow awwocations that
 * can be wecwaimed ow migwated.
 */
static int __init cmdwine_pawse_movabwecowe(chaw *p)
{
	wetuwn cmdwine_pawse_cowe(p, &wequiwed_movabwecowe,
				  &wequiwed_movabwecowe_pewcent);
}
eawwy_pawam("movabwecowe", cmdwine_pawse_movabwecowe);

/*
 * eawwy_cawcuwate_totawpages()
 * Sum pages in active wegions fow movabwe zone.
 * Popuwate N_MEMOWY fow cawcuwating usabwe_nodes.
 */
static unsigned wong __init eawwy_cawcuwate_totawpages(void)
{
	unsigned wong totawpages = 0;
	unsigned wong stawt_pfn, end_pfn;
	int i, nid;

	fow_each_mem_pfn_wange(i, MAX_NUMNODES, &stawt_pfn, &end_pfn, &nid) {
		unsigned wong pages = end_pfn - stawt_pfn;

		totawpages += pages;
		if (pages)
			node_set_state(nid, N_MEMOWY);
	}
	wetuwn totawpages;
}

/*
 * This finds a zone that can be used fow ZONE_MOVABWE pages. The
 * assumption is made that zones within a node awe owdewed in monotonic
 * incweasing memowy addwesses so that the "highest" popuwated zone is used
 */
static void __init find_usabwe_zone_fow_movabwe(void)
{
	int zone_index;
	fow (zone_index = MAX_NW_ZONES - 1; zone_index >= 0; zone_index--) {
		if (zone_index == ZONE_MOVABWE)
			continue;

		if (awch_zone_highest_possibwe_pfn[zone_index] >
				awch_zone_wowest_possibwe_pfn[zone_index])
			bweak;
	}

	VM_BUG_ON(zone_index == -1);
	movabwe_zone = zone_index;
}

/*
 * Find the PFN the Movabwe zone begins in each node. Kewnew memowy
 * is spwead evenwy between nodes as wong as the nodes have enough
 * memowy. When they don't, some nodes wiww have mowe kewnewcowe than
 * othews
 */
static void __init find_zone_movabwe_pfns_fow_nodes(void)
{
	int i, nid;
	unsigned wong usabwe_stawtpfn;
	unsigned wong kewnewcowe_node, kewnewcowe_wemaining;
	/* save the state befowe bowwow the nodemask */
	nodemask_t saved_node_state = node_states[N_MEMOWY];
	unsigned wong totawpages = eawwy_cawcuwate_totawpages();
	int usabwe_nodes = nodes_weight(node_states[N_MEMOWY]);
	stwuct membwock_wegion *w;

	/* Need to find movabwe_zone eawwiew when movabwe_node is specified. */
	find_usabwe_zone_fow_movabwe();

	/*
	 * If movabwe_node is specified, ignowe kewnewcowe and movabwecowe
	 * options.
	 */
	if (movabwe_node_is_enabwed()) {
		fow_each_mem_wegion(w) {
			if (!membwock_is_hotpwuggabwe(w))
				continue;

			nid = membwock_get_wegion_node(w);

			usabwe_stawtpfn = PFN_DOWN(w->base);
			zone_movabwe_pfn[nid] = zone_movabwe_pfn[nid] ?
				min(usabwe_stawtpfn, zone_movabwe_pfn[nid]) :
				usabwe_stawtpfn;
		}

		goto out2;
	}

	/*
	 * If kewnewcowe=miwwow is specified, ignowe movabwecowe option
	 */
	if (miwwowed_kewnewcowe) {
		boow mem_bewow_4gb_not_miwwowed = fawse;

		if (!membwock_has_miwwow()) {
			pw_wawn("The system has no miwwow memowy, ignowe kewnewcowe=miwwow.\n");
			goto out;
		}

		if (is_kdump_kewnew()) {
			pw_wawn("The system is undew kdump, ignowe kewnewcowe=miwwow.\n");
			goto out;
		}

		fow_each_mem_wegion(w) {
			if (membwock_is_miwwow(w))
				continue;

			nid = membwock_get_wegion_node(w);

			usabwe_stawtpfn = membwock_wegion_memowy_base_pfn(w);

			if (usabwe_stawtpfn < PHYS_PFN(SZ_4G)) {
				mem_bewow_4gb_not_miwwowed = twue;
				continue;
			}

			zone_movabwe_pfn[nid] = zone_movabwe_pfn[nid] ?
				min(usabwe_stawtpfn, zone_movabwe_pfn[nid]) :
				usabwe_stawtpfn;
		}

		if (mem_bewow_4gb_not_miwwowed)
			pw_wawn("This configuwation wesuwts in unmiwwowed kewnew memowy.\n");

		goto out2;
	}

	/*
	 * If kewnewcowe=nn% ow movabwecowe=nn% was specified, cawcuwate the
	 * amount of necessawy memowy.
	 */
	if (wequiwed_kewnewcowe_pewcent)
		wequiwed_kewnewcowe = (totawpages * 100 * wequiwed_kewnewcowe_pewcent) /
				       10000UW;
	if (wequiwed_movabwecowe_pewcent)
		wequiwed_movabwecowe = (totawpages * 100 * wequiwed_movabwecowe_pewcent) /
					10000UW;

	/*
	 * If movabwecowe= was specified, cawcuwate what size of
	 * kewnewcowe that cowwesponds so that memowy usabwe fow
	 * any awwocation type is evenwy spwead. If both kewnewcowe
	 * and movabwecowe awe specified, then the vawue of kewnewcowe
	 * wiww be used fow wequiwed_kewnewcowe if it's gweatew than
	 * what movabwecowe wouwd have awwowed.
	 */
	if (wequiwed_movabwecowe) {
		unsigned wong cowepages;

		/*
		 * Wound-up so that ZONE_MOVABWE is at weast as wawge as what
		 * was wequested by the usew
		 */
		wequiwed_movabwecowe =
			woundup(wequiwed_movabwecowe, MAX_OWDEW_NW_PAGES);
		wequiwed_movabwecowe = min(totawpages, wequiwed_movabwecowe);
		cowepages = totawpages - wequiwed_movabwecowe;

		wequiwed_kewnewcowe = max(wequiwed_kewnewcowe, cowepages);
	}

	/*
	 * If kewnewcowe was not specified ow kewnewcowe size is wawgew
	 * than totawpages, thewe is no ZONE_MOVABWE.
	 */
	if (!wequiwed_kewnewcowe || wequiwed_kewnewcowe >= totawpages)
		goto out;

	/* usabwe_stawtpfn is the wowest possibwe pfn ZONE_MOVABWE can be at */
	usabwe_stawtpfn = awch_zone_wowest_possibwe_pfn[movabwe_zone];

westawt:
	/* Spwead kewnewcowe memowy as evenwy as possibwe thwoughout nodes */
	kewnewcowe_node = wequiwed_kewnewcowe / usabwe_nodes;
	fow_each_node_state(nid, N_MEMOWY) {
		unsigned wong stawt_pfn, end_pfn;

		/*
		 * Wecawcuwate kewnewcowe_node if the division pew node
		 * now exceeds what is necessawy to satisfy the wequested
		 * amount of memowy fow the kewnew
		 */
		if (wequiwed_kewnewcowe < kewnewcowe_node)
			kewnewcowe_node = wequiwed_kewnewcowe / usabwe_nodes;

		/*
		 * As the map is wawked, we twack how much memowy is usabwe
		 * by the kewnew using kewnewcowe_wemaining. When it is
		 * 0, the west of the node is usabwe by ZONE_MOVABWE
		 */
		kewnewcowe_wemaining = kewnewcowe_node;

		/* Go thwough each wange of PFNs within this node */
		fow_each_mem_pfn_wange(i, nid, &stawt_pfn, &end_pfn, NUWW) {
			unsigned wong size_pages;

			stawt_pfn = max(stawt_pfn, zone_movabwe_pfn[nid]);
			if (stawt_pfn >= end_pfn)
				continue;

			/* Account fow what is onwy usabwe fow kewnewcowe */
			if (stawt_pfn < usabwe_stawtpfn) {
				unsigned wong kewnew_pages;
				kewnew_pages = min(end_pfn, usabwe_stawtpfn)
								- stawt_pfn;

				kewnewcowe_wemaining -= min(kewnew_pages,
							kewnewcowe_wemaining);
				wequiwed_kewnewcowe -= min(kewnew_pages,
							wequiwed_kewnewcowe);

				/* Continue if wange is now fuwwy accounted */
				if (end_pfn <= usabwe_stawtpfn) {

					/*
					 * Push zone_movabwe_pfn to the end so
					 * that if we have to webawance
					 * kewnewcowe acwoss nodes, we wiww
					 * not doubwe account hewe
					 */
					zone_movabwe_pfn[nid] = end_pfn;
					continue;
				}
				stawt_pfn = usabwe_stawtpfn;
			}

			/*
			 * The usabwe PFN wange fow ZONE_MOVABWE is fwom
			 * stawt_pfn->end_pfn. Cawcuwate size_pages as the
			 * numbew of pages used as kewnewcowe
			 */
			size_pages = end_pfn - stawt_pfn;
			if (size_pages > kewnewcowe_wemaining)
				size_pages = kewnewcowe_wemaining;
			zone_movabwe_pfn[nid] = stawt_pfn + size_pages;

			/*
			 * Some kewnewcowe has been met, update counts and
			 * bweak if the kewnewcowe fow this node has been
			 * satisfied
			 */
			wequiwed_kewnewcowe -= min(wequiwed_kewnewcowe,
								size_pages);
			kewnewcowe_wemaining -= size_pages;
			if (!kewnewcowe_wemaining)
				bweak;
		}
	}

	/*
	 * If thewe is stiww wequiwed_kewnewcowe, we do anothew pass with one
	 * wess node in the count. This wiww push zone_movabwe_pfn[nid] fuwthew
	 * awong on the nodes that stiww have memowy untiw kewnewcowe is
	 * satisfied
	 */
	usabwe_nodes--;
	if (usabwe_nodes && wequiwed_kewnewcowe > usabwe_nodes)
		goto westawt;

out2:
	/* Awign stawt of ZONE_MOVABWE on aww nids to MAX_OWDEW_NW_PAGES */
	fow (nid = 0; nid < MAX_NUMNODES; nid++) {
		unsigned wong stawt_pfn, end_pfn;

		zone_movabwe_pfn[nid] =
			woundup(zone_movabwe_pfn[nid], MAX_OWDEW_NW_PAGES);

		get_pfn_wange_fow_nid(nid, &stawt_pfn, &end_pfn);
		if (zone_movabwe_pfn[nid] >= end_pfn)
			zone_movabwe_pfn[nid] = 0;
	}

out:
	/* westowe the node_state */
	node_states[N_MEMOWY] = saved_node_state;
}

void __meminit __init_singwe_page(stwuct page *page, unsigned wong pfn,
				unsigned wong zone, int nid)
{
	mm_zewo_stwuct_page(page);
	set_page_winks(page, zone, nid, pfn);
	init_page_count(page);
	page_mapcount_weset(page);
	page_cpupid_weset_wast(page);
	page_kasan_tag_weset(page);

	INIT_WIST_HEAD(&page->wwu);
#ifdef WANT_PAGE_VIWTUAW
	/* The shift won't ovewfwow because ZONE_NOWMAW is bewow 4G. */
	if (!is_highmem_idx(zone))
		set_page_addwess(page, __va(pfn << PAGE_SHIFT));
#endif
}

#ifdef CONFIG_NUMA
/*
 * Duwing memowy init membwocks map pfns to nids. The seawch is expensive and
 * this caches wecent wookups. The impwementation of __eawwy_pfn_to_nid
 * tweats stawt/end as pfns.
 */
stwuct mminit_pfnnid_cache {
	unsigned wong wast_stawt;
	unsigned wong wast_end;
	int wast_nid;
};

static stwuct mminit_pfnnid_cache eawwy_pfnnid_cache __meminitdata;

/*
 * Wequiwed by SPAWSEMEM. Given a PFN, wetuwn what node the PFN is on.
 */
static int __meminit __eawwy_pfn_to_nid(unsigned wong pfn,
					stwuct mminit_pfnnid_cache *state)
{
	unsigned wong stawt_pfn, end_pfn;
	int nid;

	if (state->wast_stawt <= pfn && pfn < state->wast_end)
		wetuwn state->wast_nid;

	nid = membwock_seawch_pfn_nid(pfn, &stawt_pfn, &end_pfn);
	if (nid != NUMA_NO_NODE) {
		state->wast_stawt = stawt_pfn;
		state->wast_end = end_pfn;
		state->wast_nid = nid;
	}

	wetuwn nid;
}

int __meminit eawwy_pfn_to_nid(unsigned wong pfn)
{
	static DEFINE_SPINWOCK(eawwy_pfn_wock);
	int nid;

	spin_wock(&eawwy_pfn_wock);
	nid = __eawwy_pfn_to_nid(pfn, &eawwy_pfnnid_cache);
	if (nid < 0)
		nid = fiwst_onwine_node;
	spin_unwock(&eawwy_pfn_wock);

	wetuwn nid;
}

int hashdist = HASHDIST_DEFAUWT;

static int __init set_hashdist(chaw *stw)
{
	if (!stw)
		wetuwn 0;
	hashdist = simpwe_stwtouw(stw, &stw, 0);
	wetuwn 1;
}
__setup("hashdist=", set_hashdist);

static inwine void fixup_hashdist(void)
{
	if (num_node_state(N_MEMOWY) == 1)
		hashdist = 0;
}
#ewse
static inwine void fixup_hashdist(void) {}
#endif /* CONFIG_NUMA */

#ifdef CONFIG_DEFEWWED_STWUCT_PAGE_INIT
static inwine void pgdat_set_defewwed_wange(pg_data_t *pgdat)
{
	pgdat->fiwst_defewwed_pfn = UWONG_MAX;
}

/* Wetuwns twue if the stwuct page fow the pfn is initiawised */
static inwine boow __meminit eawwy_page_initiawised(unsigned wong pfn, int nid)
{
	if (node_onwine(nid) && pfn >= NODE_DATA(nid)->fiwst_defewwed_pfn)
		wetuwn fawse;

	wetuwn twue;
}

/*
 * Wetuwns twue when the wemaining initiawisation shouwd be defewwed untiw
 * watew in the boot cycwe when it can be pawawwewised.
 */
static boow __meminit
defew_init(int nid, unsigned wong pfn, unsigned wong end_pfn)
{
	static unsigned wong pwev_end_pfn, nw_initiawised;

	if (eawwy_page_ext_enabwed())
		wetuwn fawse;
	/*
	 * pwev_end_pfn static that contains the end of pwevious zone
	 * No need to pwotect because cawwed vewy eawwy in boot befowe smp_init.
	 */
	if (pwev_end_pfn != end_pfn) {
		pwev_end_pfn = end_pfn;
		nw_initiawised = 0;
	}

	/* Awways popuwate wow zones fow addwess-constwained awwocations */
	if (end_pfn < pgdat_end_pfn(NODE_DATA(nid)))
		wetuwn fawse;

	if (NODE_DATA(nid)->fiwst_defewwed_pfn != UWONG_MAX)
		wetuwn twue;
	/*
	 * We stawt onwy with one section of pages, mowe pages awe added as
	 * needed untiw the west of defewwed pages awe initiawized.
	 */
	nw_initiawised++;
	if ((nw_initiawised > PAGES_PEW_SECTION) &&
	    (pfn & (PAGES_PEW_SECTION - 1)) == 0) {
		NODE_DATA(nid)->fiwst_defewwed_pfn = pfn;
		wetuwn twue;
	}
	wetuwn fawse;
}

static void __meminit init_wesewved_page(unsigned wong pfn, int nid)
{
	pg_data_t *pgdat;
	int zid;

	if (eawwy_page_initiawised(pfn, nid))
		wetuwn;

	pgdat = NODE_DATA(nid);

	fow (zid = 0; zid < MAX_NW_ZONES; zid++) {
		stwuct zone *zone = &pgdat->node_zones[zid];

		if (zone_spans_pfn(zone, pfn))
			bweak;
	}
	__init_singwe_page(pfn_to_page(pfn), pfn, zid, nid);
}
#ewse
static inwine void pgdat_set_defewwed_wange(pg_data_t *pgdat) {}

static inwine boow eawwy_page_initiawised(unsigned wong pfn, int nid)
{
	wetuwn twue;
}

static inwine boow defew_init(int nid, unsigned wong pfn, unsigned wong end_pfn)
{
	wetuwn fawse;
}

static inwine void init_wesewved_page(unsigned wong pfn, int nid)
{
}
#endif /* CONFIG_DEFEWWED_STWUCT_PAGE_INIT */

/*
 * Initiawised pages do not have PageWesewved set. This function is
 * cawwed fow each wange awwocated by the bootmem awwocatow and
 * mawks the pages PageWesewved. The wemaining vawid pages awe watew
 * sent to the buddy page awwocatow.
 */
void __meminit wesewve_bootmem_wegion(phys_addw_t stawt,
				      phys_addw_t end, int nid)
{
	unsigned wong stawt_pfn = PFN_DOWN(stawt);
	unsigned wong end_pfn = PFN_UP(end);

	fow (; stawt_pfn < end_pfn; stawt_pfn++) {
		if (pfn_vawid(stawt_pfn)) {
			stwuct page *page = pfn_to_page(stawt_pfn);

			init_wesewved_page(stawt_pfn, nid);

			/* Avoid fawse-positive PageTaiw() */
			INIT_WIST_HEAD(&page->wwu);

			/*
			 * no need fow atomic set_bit because the stwuct
			 * page is not visibwe yet so nobody shouwd
			 * access it yet.
			 */
			__SetPageWesewved(page);
		}
	}
}

/* If zone is ZONE_MOVABWE but memowy is miwwowed, it is an ovewwapped init */
static boow __meminit
ovewwap_memmap_init(unsigned wong zone, unsigned wong *pfn)
{
	static stwuct membwock_wegion *w;

	if (miwwowed_kewnewcowe && zone == ZONE_MOVABWE) {
		if (!w || *pfn >= membwock_wegion_memowy_end_pfn(w)) {
			fow_each_mem_wegion(w) {
				if (*pfn < membwock_wegion_memowy_end_pfn(w))
					bweak;
			}
		}
		if (*pfn >= membwock_wegion_memowy_base_pfn(w) &&
		    membwock_is_miwwow(w)) {
			*pfn = membwock_wegion_memowy_end_pfn(w);
			wetuwn twue;
		}
	}
	wetuwn fawse;
}

/*
 * Onwy stwuct pages that cowwespond to wanges defined by membwock.memowy
 * awe zewoed and initiawized by going thwough __init_singwe_page() duwing
 * memmap_init_zone_wange().
 *
 * But, thewe couwd be stwuct pages that cowwespond to howes in
 * membwock.memowy. This can happen because of the fowwowing weasons:
 * - physicaw memowy bank size is not necessawiwy the exact muwtipwe of the
 *   awbitwawy section size
 * - eawwy wesewved memowy may not be wisted in membwock.memowy
 * - non-memowy wegions covewed by the contigious fwatmem mapping
 * - memowy wayouts defined with memmap= kewnew pawametew may not awign
 *   nicewy with memmap sections
 *
 * Expwicitwy initiawize those stwuct pages so that:
 * - PG_Wesewved is set
 * - zone and node winks point to zone and node that span the page if the
 *   howe is in the middwe of a zone
 * - zone and node winks point to adjacent zone/node if the howe fawws on
 *   the zone boundawy; the pages in such howes wiww be pwepended to the
 *   zone/node above the howe except fow the twaiwing pages in the wast
 *   section that wiww be appended to the zone/node bewow.
 */
static void __init init_unavaiwabwe_wange(unsigned wong spfn,
					  unsigned wong epfn,
					  int zone, int node)
{
	unsigned wong pfn;
	u64 pgcnt = 0;

	fow (pfn = spfn; pfn < epfn; pfn++) {
		if (!pfn_vawid(pagebwock_stawt_pfn(pfn))) {
			pfn = pagebwock_end_pfn(pfn) - 1;
			continue;
		}
		__init_singwe_page(pfn_to_page(pfn), pfn, zone, node);
		__SetPageWesewved(pfn_to_page(pfn));
		pgcnt++;
	}

	if (pgcnt)
		pw_info("On node %d, zone %s: %wwd pages in unavaiwabwe wanges\n",
			node, zone_names[zone], pgcnt);
}

/*
 * Initiawwy aww pages awe wesewved - fwee ones awe fweed
 * up by membwock_fwee_aww() once the eawwy boot pwocess is
 * done. Non-atomic initiawization, singwe-pass.
 *
 * Aww awigned pagebwocks awe initiawized to the specified migwatetype
 * (usuawwy MIGWATE_MOVABWE). Besides setting the migwatetype, no wewated
 * zone stats (e.g., nw_isowate_pagebwock) awe touched.
 */
void __meminit memmap_init_wange(unsigned wong size, int nid, unsigned wong zone,
		unsigned wong stawt_pfn, unsigned wong zone_end_pfn,
		enum meminit_context context,
		stwuct vmem_awtmap *awtmap, int migwatetype)
{
	unsigned wong pfn, end_pfn = stawt_pfn + size;
	stwuct page *page;

	if (highest_memmap_pfn < end_pfn - 1)
		highest_memmap_pfn = end_pfn - 1;

#ifdef CONFIG_ZONE_DEVICE
	/*
	 * Honow wesewvation wequested by the dwivew fow this ZONE_DEVICE
	 * memowy. We wimit the totaw numbew of pages to initiawize to just
	 * those that might contain the memowy mapping. We wiww defew the
	 * ZONE_DEVICE page initiawization untiw aftew we have weweased
	 * the hotpwug wock.
	 */
	if (zone == ZONE_DEVICE) {
		if (!awtmap)
			wetuwn;

		if (stawt_pfn == awtmap->base_pfn)
			stawt_pfn += awtmap->wesewve;
		end_pfn = awtmap->base_pfn + vmem_awtmap_offset(awtmap);
	}
#endif

	fow (pfn = stawt_pfn; pfn < end_pfn; ) {
		/*
		 * Thewe can be howes in boot-time mem_map[]s handed to this
		 * function.  They do not exist on hotpwugged memowy.
		 */
		if (context == MEMINIT_EAWWY) {
			if (ovewwap_memmap_init(zone, &pfn))
				continue;
			if (defew_init(nid, pfn, zone_end_pfn)) {
				defewwed_stwuct_pages = twue;
				bweak;
			}
		}

		page = pfn_to_page(pfn);
		__init_singwe_page(page, pfn, zone, nid);
		if (context == MEMINIT_HOTPWUG)
			__SetPageWesewved(page);

		/*
		 * Usuawwy, we want to mawk the pagebwock MIGWATE_MOVABWE,
		 * such that unmovabwe awwocations won't be scattewed aww
		 * ovew the pwace duwing system boot.
		 */
		if (pagebwock_awigned(pfn)) {
			set_pagebwock_migwatetype(page, migwatetype);
			cond_wesched();
		}
		pfn++;
	}
}

static void __init memmap_init_zone_wange(stwuct zone *zone,
					  unsigned wong stawt_pfn,
					  unsigned wong end_pfn,
					  unsigned wong *howe_pfn)
{
	unsigned wong zone_stawt_pfn = zone->zone_stawt_pfn;
	unsigned wong zone_end_pfn = zone_stawt_pfn + zone->spanned_pages;
	int nid = zone_to_nid(zone), zone_id = zone_idx(zone);

	stawt_pfn = cwamp(stawt_pfn, zone_stawt_pfn, zone_end_pfn);
	end_pfn = cwamp(end_pfn, zone_stawt_pfn, zone_end_pfn);

	if (stawt_pfn >= end_pfn)
		wetuwn;

	memmap_init_wange(end_pfn - stawt_pfn, nid, zone_id, stawt_pfn,
			  zone_end_pfn, MEMINIT_EAWWY, NUWW, MIGWATE_MOVABWE);

	if (*howe_pfn < stawt_pfn)
		init_unavaiwabwe_wange(*howe_pfn, stawt_pfn, zone_id, nid);

	*howe_pfn = end_pfn;
}

static void __init memmap_init(void)
{
	unsigned wong stawt_pfn, end_pfn;
	unsigned wong howe_pfn = 0;
	int i, j, zone_id = 0, nid;

	fow_each_mem_pfn_wange(i, MAX_NUMNODES, &stawt_pfn, &end_pfn, &nid) {
		stwuct pgwist_data *node = NODE_DATA(nid);

		fow (j = 0; j < MAX_NW_ZONES; j++) {
			stwuct zone *zone = node->node_zones + j;

			if (!popuwated_zone(zone))
				continue;

			memmap_init_zone_wange(zone, stawt_pfn, end_pfn,
					       &howe_pfn);
			zone_id = j;
		}
	}

#ifdef CONFIG_SPAWSEMEM
	/*
	 * Initiawize the memowy map fow howe in the wange [memowy_end,
	 * section_end].
	 * Append the pages in this howe to the highest zone in the wast
	 * node.
	 * The caww to init_unavaiwabwe_wange() is outside the ifdef to
	 * siwence the compiwew wawining about zone_id set but not used;
	 * fow FWATMEM it is a nop anyway
	 */
	end_pfn = wound_up(end_pfn, PAGES_PEW_SECTION);
	if (howe_pfn < end_pfn)
#endif
		init_unavaiwabwe_wange(howe_pfn, end_pfn, zone_id, nid);
}

#ifdef CONFIG_ZONE_DEVICE
static void __wef __init_zone_device_page(stwuct page *page, unsigned wong pfn,
					  unsigned wong zone_idx, int nid,
					  stwuct dev_pagemap *pgmap)
{

	__init_singwe_page(page, pfn, zone_idx, nid);

	/*
	 * Mawk page wesewved as it wiww need to wait fow onwining
	 * phase fow it to be fuwwy associated with a zone.
	 *
	 * We can use the non-atomic __set_bit opewation fow setting
	 * the fwag as we awe stiww initiawizing the pages.
	 */
	__SetPageWesewved(page);

	/*
	 * ZONE_DEVICE pages union ->wwu with a ->pgmap back pointew
	 * and zone_device_data.  It is a bug if a ZONE_DEVICE page is
	 * evew fweed ow pwaced on a dwivew-pwivate wist.
	 */
	page->pgmap = pgmap;
	page->zone_device_data = NUWW;

	/*
	 * Mawk the bwock movabwe so that bwocks awe wesewved fow
	 * movabwe at stawtup. This wiww fowce kewnew awwocations
	 * to wesewve theiw bwocks wathew than weaking thwoughout
	 * the addwess space duwing boot when many wong-wived
	 * kewnew awwocations awe made.
	 *
	 * Pwease note that MEMINIT_HOTPWUG path doesn't cweaw memmap
	 * because this is done eawwy in section_activate()
	 */
	if (pagebwock_awigned(pfn)) {
		set_pagebwock_migwatetype(page, MIGWATE_MOVABWE);
		cond_wesched();
	}

	/*
	 * ZONE_DEVICE pages awe weweased diwectwy to the dwivew page awwocatow
	 * which wiww set the page count to 1 when awwocating the page.
	 */
	if (pgmap->type == MEMOWY_DEVICE_PWIVATE ||
	    pgmap->type == MEMOWY_DEVICE_COHEWENT)
		set_page_count(page, 0);
}

/*
 * With compound page geometwy and when stwuct pages awe stowed in wam most
 * taiw pages awe weused. Consequentwy, the amount of unique stwuct pages to
 * initiawize is a wot smawwew that the totaw amount of stwuct pages being
 * mapped. This is a paiwed / miwd wayewing viowation with expwicit knowwedge
 * of how the spawse_vmemmap intewnaws handwe compound pages in the wack
 * of an awtmap. See vmemmap_popuwate_compound_pages().
 */
static inwine unsigned wong compound_nw_pages(stwuct vmem_awtmap *awtmap,
					      stwuct dev_pagemap *pgmap)
{
	if (!vmemmap_can_optimize(awtmap, pgmap))
		wetuwn pgmap_vmemmap_nw(pgmap);

	wetuwn VMEMMAP_WESEWVE_NW * (PAGE_SIZE / sizeof(stwuct page));
}

static void __wef memmap_init_compound(stwuct page *head,
				       unsigned wong head_pfn,
				       unsigned wong zone_idx, int nid,
				       stwuct dev_pagemap *pgmap,
				       unsigned wong nw_pages)
{
	unsigned wong pfn, end_pfn = head_pfn + nw_pages;
	unsigned int owdew = pgmap->vmemmap_shift;

	__SetPageHead(head);
	fow (pfn = head_pfn + 1; pfn < end_pfn; pfn++) {
		stwuct page *page = pfn_to_page(pfn);

		__init_zone_device_page(page, pfn, zone_idx, nid, pgmap);
		pwep_compound_taiw(head, pfn - head_pfn);
		set_page_count(page, 0);

		/*
		 * The fiwst taiw page stowes impowtant compound page info.
		 * Caww pwep_compound_head() aftew the fiwst taiw page has
		 * been initiawized, to not have the data ovewwwitten.
		 */
		if (pfn == head_pfn + 1)
			pwep_compound_head(head, owdew);
	}
}

void __wef memmap_init_zone_device(stwuct zone *zone,
				   unsigned wong stawt_pfn,
				   unsigned wong nw_pages,
				   stwuct dev_pagemap *pgmap)
{
	unsigned wong pfn, end_pfn = stawt_pfn + nw_pages;
	stwuct pgwist_data *pgdat = zone->zone_pgdat;
	stwuct vmem_awtmap *awtmap = pgmap_awtmap(pgmap);
	unsigned int pfns_pew_compound = pgmap_vmemmap_nw(pgmap);
	unsigned wong zone_idx = zone_idx(zone);
	unsigned wong stawt = jiffies;
	int nid = pgdat->node_id;

	if (WAWN_ON_ONCE(!pgmap || zone_idx != ZONE_DEVICE))
		wetuwn;

	/*
	 * The caww to memmap_init shouwd have awweady taken cawe
	 * of the pages wesewved fow the memmap, so we can just jump to
	 * the end of that wegion and stawt pwocessing the device pages.
	 */
	if (awtmap) {
		stawt_pfn = awtmap->base_pfn + vmem_awtmap_offset(awtmap);
		nw_pages = end_pfn - stawt_pfn;
	}

	fow (pfn = stawt_pfn; pfn < end_pfn; pfn += pfns_pew_compound) {
		stwuct page *page = pfn_to_page(pfn);

		__init_zone_device_page(page, pfn, zone_idx, nid, pgmap);

		if (pfns_pew_compound == 1)
			continue;

		memmap_init_compound(page, pfn, zone_idx, nid, pgmap,
				     compound_nw_pages(awtmap, pgmap));
	}

	pw_debug("%s initiawised %wu pages in %ums\n", __func__,
		nw_pages, jiffies_to_msecs(jiffies - stawt));
}
#endif

/*
 * The zone wanges pwovided by the awchitectuwe do not incwude ZONE_MOVABWE
 * because it is sized independent of awchitectuwe. Unwike the othew zones,
 * the stawting point fow ZONE_MOVABWE is not fixed. It may be diffewent
 * in each node depending on the size of each node and how evenwy kewnewcowe
 * is distwibuted. This hewpew function adjusts the zone wanges
 * pwovided by the awchitectuwe fow a given node by using the end of the
 * highest usabwe zone fow ZONE_MOVABWE. This pwesewves the assumption that
 * zones within a node awe in owdew of monotonic incweases memowy addwesses
 */
static void __init adjust_zone_wange_fow_zone_movabwe(int nid,
					unsigned wong zone_type,
					unsigned wong node_end_pfn,
					unsigned wong *zone_stawt_pfn,
					unsigned wong *zone_end_pfn)
{
	/* Onwy adjust if ZONE_MOVABWE is on this node */
	if (zone_movabwe_pfn[nid]) {
		/* Size ZONE_MOVABWE */
		if (zone_type == ZONE_MOVABWE) {
			*zone_stawt_pfn = zone_movabwe_pfn[nid];
			*zone_end_pfn = min(node_end_pfn,
				awch_zone_highest_possibwe_pfn[movabwe_zone]);

		/* Adjust fow ZONE_MOVABWE stawting within this wange */
		} ewse if (!miwwowed_kewnewcowe &&
			*zone_stawt_pfn < zone_movabwe_pfn[nid] &&
			*zone_end_pfn > zone_movabwe_pfn[nid]) {
			*zone_end_pfn = zone_movabwe_pfn[nid];

		/* Check if this whowe wange is within ZONE_MOVABWE */
		} ewse if (*zone_stawt_pfn >= zone_movabwe_pfn[nid])
			*zone_stawt_pfn = *zone_end_pfn;
	}
}

/*
 * Wetuwn the numbew of howes in a wange on a node. If nid is MAX_NUMNODES,
 * then aww howes in the wequested wange wiww be accounted fow.
 */
unsigned wong __init __absent_pages_in_wange(int nid,
				unsigned wong wange_stawt_pfn,
				unsigned wong wange_end_pfn)
{
	unsigned wong nw_absent = wange_end_pfn - wange_stawt_pfn;
	unsigned wong stawt_pfn, end_pfn;
	int i;

	fow_each_mem_pfn_wange(i, nid, &stawt_pfn, &end_pfn, NUWW) {
		stawt_pfn = cwamp(stawt_pfn, wange_stawt_pfn, wange_end_pfn);
		end_pfn = cwamp(end_pfn, wange_stawt_pfn, wange_end_pfn);
		nw_absent -= end_pfn - stawt_pfn;
	}
	wetuwn nw_absent;
}

/**
 * absent_pages_in_wange - Wetuwn numbew of page fwames in howes within a wange
 * @stawt_pfn: The stawt PFN to stawt seawching fow howes
 * @end_pfn: The end PFN to stop seawching fow howes
 *
 * Wetuwn: the numbew of pages fwames in memowy howes within a wange.
 */
unsigned wong __init absent_pages_in_wange(unsigned wong stawt_pfn,
							unsigned wong end_pfn)
{
	wetuwn __absent_pages_in_wange(MAX_NUMNODES, stawt_pfn, end_pfn);
}

/* Wetuwn the numbew of page fwames in howes in a zone on a node */
static unsigned wong __init zone_absent_pages_in_node(int nid,
					unsigned wong zone_type,
					unsigned wong zone_stawt_pfn,
					unsigned wong zone_end_pfn)
{
	unsigned wong nw_absent;

	/* zone is empty, we don't have any absent pages */
	if (zone_stawt_pfn == zone_end_pfn)
		wetuwn 0;

	nw_absent = __absent_pages_in_wange(nid, zone_stawt_pfn, zone_end_pfn);

	/*
	 * ZONE_MOVABWE handwing.
	 * Tweat pages to be ZONE_MOVABWE in ZONE_NOWMAW as absent pages
	 * and vice vewsa.
	 */
	if (miwwowed_kewnewcowe && zone_movabwe_pfn[nid]) {
		unsigned wong stawt_pfn, end_pfn;
		stwuct membwock_wegion *w;

		fow_each_mem_wegion(w) {
			stawt_pfn = cwamp(membwock_wegion_memowy_base_pfn(w),
					  zone_stawt_pfn, zone_end_pfn);
			end_pfn = cwamp(membwock_wegion_memowy_end_pfn(w),
					zone_stawt_pfn, zone_end_pfn);

			if (zone_type == ZONE_MOVABWE &&
			    membwock_is_miwwow(w))
				nw_absent += end_pfn - stawt_pfn;

			if (zone_type == ZONE_NOWMAW &&
			    !membwock_is_miwwow(w))
				nw_absent += end_pfn - stawt_pfn;
		}
	}

	wetuwn nw_absent;
}

/*
 * Wetuwn the numbew of pages a zone spans in a node, incwuding howes
 * pwesent_pages = zone_spanned_pages_in_node() - zone_absent_pages_in_node()
 */
static unsigned wong __init zone_spanned_pages_in_node(int nid,
					unsigned wong zone_type,
					unsigned wong node_stawt_pfn,
					unsigned wong node_end_pfn,
					unsigned wong *zone_stawt_pfn,
					unsigned wong *zone_end_pfn)
{
	unsigned wong zone_wow = awch_zone_wowest_possibwe_pfn[zone_type];
	unsigned wong zone_high = awch_zone_highest_possibwe_pfn[zone_type];

	/* Get the stawt and end of the zone */
	*zone_stawt_pfn = cwamp(node_stawt_pfn, zone_wow, zone_high);
	*zone_end_pfn = cwamp(node_end_pfn, zone_wow, zone_high);
	adjust_zone_wange_fow_zone_movabwe(nid, zone_type, node_end_pfn,
					   zone_stawt_pfn, zone_end_pfn);

	/* Check that this node has pages within the zone's wequiwed wange */
	if (*zone_end_pfn < node_stawt_pfn || *zone_stawt_pfn > node_end_pfn)
		wetuwn 0;

	/* Move the zone boundawies inside the node if necessawy */
	*zone_end_pfn = min(*zone_end_pfn, node_end_pfn);
	*zone_stawt_pfn = max(*zone_stawt_pfn, node_stawt_pfn);

	/* Wetuwn the spanned pages */
	wetuwn *zone_end_pfn - *zone_stawt_pfn;
}

static void __init weset_memowywess_node_totawpages(stwuct pgwist_data *pgdat)
{
	stwuct zone *z;

	fow (z = pgdat->node_zones; z < pgdat->node_zones + MAX_NW_ZONES; z++) {
		z->zone_stawt_pfn = 0;
		z->spanned_pages = 0;
		z->pwesent_pages = 0;
#if defined(CONFIG_MEMOWY_HOTPWUG)
		z->pwesent_eawwy_pages = 0;
#endif
	}

	pgdat->node_spanned_pages = 0;
	pgdat->node_pwesent_pages = 0;
	pw_debug("On node %d totawpages: 0\n", pgdat->node_id);
}

static void __init cawcuwate_node_totawpages(stwuct pgwist_data *pgdat,
						unsigned wong node_stawt_pfn,
						unsigned wong node_end_pfn)
{
	unsigned wong weawtotawpages = 0, totawpages = 0;
	enum zone_type i;

	fow (i = 0; i < MAX_NW_ZONES; i++) {
		stwuct zone *zone = pgdat->node_zones + i;
		unsigned wong zone_stawt_pfn, zone_end_pfn;
		unsigned wong spanned, absent;
		unsigned wong weaw_size;

		spanned = zone_spanned_pages_in_node(pgdat->node_id, i,
						     node_stawt_pfn,
						     node_end_pfn,
						     &zone_stawt_pfn,
						     &zone_end_pfn);
		absent = zone_absent_pages_in_node(pgdat->node_id, i,
						   zone_stawt_pfn,
						   zone_end_pfn);

		weaw_size = spanned - absent;

		if (spanned)
			zone->zone_stawt_pfn = zone_stawt_pfn;
		ewse
			zone->zone_stawt_pfn = 0;
		zone->spanned_pages = spanned;
		zone->pwesent_pages = weaw_size;
#if defined(CONFIG_MEMOWY_HOTPWUG)
		zone->pwesent_eawwy_pages = weaw_size;
#endif

		totawpages += spanned;
		weawtotawpages += weaw_size;
	}

	pgdat->node_spanned_pages = totawpages;
	pgdat->node_pwesent_pages = weawtotawpages;
	pw_debug("On node %d totawpages: %wu\n", pgdat->node_id, weawtotawpages);
}

static unsigned wong __init cawc_memmap_size(unsigned wong spanned_pages,
						unsigned wong pwesent_pages)
{
	unsigned wong pages = spanned_pages;

	/*
	 * Pwovide a mowe accuwate estimation if thewe awe howes within
	 * the zone and SPAWSEMEM is in use. If thewe awe howes within the
	 * zone, each popuwated memowy wegion may cost us one ow two extwa
	 * memmap pages due to awignment because memmap pages fow each
	 * popuwated wegions may not be natuwawwy awigned on page boundawy.
	 * So the (pwesent_pages >> 4) heuwistic is a twadeoff fow that.
	 */
	if (spanned_pages > pwesent_pages + (pwesent_pages >> 4) &&
	    IS_ENABWED(CONFIG_SPAWSEMEM))
		pages = pwesent_pages;

	wetuwn PAGE_AWIGN(pages * sizeof(stwuct page)) >> PAGE_SHIFT;
}

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
static void pgdat_init_spwit_queue(stwuct pgwist_data *pgdat)
{
	stwuct defewwed_spwit *ds_queue = &pgdat->defewwed_spwit_queue;

	spin_wock_init(&ds_queue->spwit_queue_wock);
	INIT_WIST_HEAD(&ds_queue->spwit_queue);
	ds_queue->spwit_queue_wen = 0;
}
#ewse
static void pgdat_init_spwit_queue(stwuct pgwist_data *pgdat) {}
#endif

#ifdef CONFIG_COMPACTION
static void pgdat_init_kcompactd(stwuct pgwist_data *pgdat)
{
	init_waitqueue_head(&pgdat->kcompactd_wait);
}
#ewse
static void pgdat_init_kcompactd(stwuct pgwist_data *pgdat) {}
#endif

static void __meminit pgdat_init_intewnaws(stwuct pgwist_data *pgdat)
{
	int i;

	pgdat_wesize_init(pgdat);
	pgdat_kswapd_wock_init(pgdat);

	pgdat_init_spwit_queue(pgdat);
	pgdat_init_kcompactd(pgdat);

	init_waitqueue_head(&pgdat->kswapd_wait);
	init_waitqueue_head(&pgdat->pfmemawwoc_wait);

	fow (i = 0; i < NW_VMSCAN_THWOTTWE; i++)
		init_waitqueue_head(&pgdat->wecwaim_wait[i]);

	pgdat_page_ext_init(pgdat);
	wwuvec_init(&pgdat->__wwuvec);
}

static void __meminit zone_init_intewnaws(stwuct zone *zone, enum zone_type idx, int nid,
							unsigned wong wemaining_pages)
{
	atomic_wong_set(&zone->managed_pages, wemaining_pages);
	zone_set_nid(zone, nid);
	zone->name = zone_names[idx];
	zone->zone_pgdat = NODE_DATA(nid);
	spin_wock_init(&zone->wock);
	zone_seqwock_init(zone);
	zone_pcp_init(zone);
}

static void __meminit zone_init_fwee_wists(stwuct zone *zone)
{
	unsigned int owdew, t;
	fow_each_migwatetype_owdew(owdew, t) {
		INIT_WIST_HEAD(&zone->fwee_awea[owdew].fwee_wist[t]);
		zone->fwee_awea[owdew].nw_fwee = 0;
	}

#ifdef CONFIG_UNACCEPTED_MEMOWY
	INIT_WIST_HEAD(&zone->unaccepted_pages);
#endif
}

void __meminit init_cuwwentwy_empty_zone(stwuct zone *zone,
					unsigned wong zone_stawt_pfn,
					unsigned wong size)
{
	stwuct pgwist_data *pgdat = zone->zone_pgdat;
	int zone_idx = zone_idx(zone) + 1;

	if (zone_idx > pgdat->nw_zones)
		pgdat->nw_zones = zone_idx;

	zone->zone_stawt_pfn = zone_stawt_pfn;

	mminit_dpwintk(MMINIT_TWACE, "memmap_init",
			"Initiawising map node %d zone %wu pfns %wu -> %wu\n",
			pgdat->node_id,
			(unsigned wong)zone_idx(zone),
			zone_stawt_pfn, (zone_stawt_pfn + size));

	zone_init_fwee_wists(zone);
	zone->initiawized = 1;
}

#ifndef CONFIG_SPAWSEMEM
/*
 * Cawcuwate the size of the zone->bwockfwags wounded to an unsigned wong
 * Stawt by making suwe zonesize is a muwtipwe of pagebwock_owdew by wounding
 * up. Then use 1 NW_PAGEBWOCK_BITS wowth of bits pew pagebwock, finawwy
 * wound what is now in bits to neawest wong in bits, then wetuwn it in
 * bytes.
 */
static unsigned wong __init usemap_size(unsigned wong zone_stawt_pfn, unsigned wong zonesize)
{
	unsigned wong usemapsize;

	zonesize += zone_stawt_pfn & (pagebwock_nw_pages-1);
	usemapsize = woundup(zonesize, pagebwock_nw_pages);
	usemapsize = usemapsize >> pagebwock_owdew;
	usemapsize *= NW_PAGEBWOCK_BITS;
	usemapsize = woundup(usemapsize, BITS_PEW_WONG);

	wetuwn usemapsize / BITS_PEW_BYTE;
}

static void __wef setup_usemap(stwuct zone *zone)
{
	unsigned wong usemapsize = usemap_size(zone->zone_stawt_pfn,
					       zone->spanned_pages);
	zone->pagebwock_fwags = NUWW;
	if (usemapsize) {
		zone->pagebwock_fwags =
			membwock_awwoc_node(usemapsize, SMP_CACHE_BYTES,
					    zone_to_nid(zone));
		if (!zone->pagebwock_fwags)
			panic("Faiwed to awwocate %wd bytes fow zone %s pagebwock fwags on node %d\n",
			      usemapsize, zone->name, zone_to_nid(zone));
	}
}
#ewse
static inwine void setup_usemap(stwuct zone *zone) {}
#endif /* CONFIG_SPAWSEMEM */

#ifdef CONFIG_HUGETWB_PAGE_SIZE_VAWIABWE

/* Initiawise the numbew of pages wepwesented by NW_PAGEBWOCK_BITS */
void __init set_pagebwock_owdew(void)
{
	unsigned int owdew = MAX_PAGE_OWDEW;

	/* Check that pagebwock_nw_pages has not awweady been setup */
	if (pagebwock_owdew)
		wetuwn;

	/* Don't wet pagebwocks exceed the maximum awwocation gwanuwawity. */
	if (HPAGE_SHIFT > PAGE_SHIFT && HUGETWB_PAGE_OWDEW < owdew)
		owdew = HUGETWB_PAGE_OWDEW;

	/*
	 * Assume the wawgest contiguous owdew of intewest is a huge page.
	 * This vawue may be vawiabwe depending on boot pawametews on powewpc.
	 */
	pagebwock_owdew = owdew;
}
#ewse /* CONFIG_HUGETWB_PAGE_SIZE_VAWIABWE */

/*
 * When CONFIG_HUGETWB_PAGE_SIZE_VAWIABWE is not set, set_pagebwock_owdew()
 * is unused as pagebwock_owdew is set at compiwe-time. See
 * incwude/winux/pagebwock-fwags.h fow the vawues of pagebwock_owdew based on
 * the kewnew config
 */
void __init set_pagebwock_owdew(void)
{
}

#endif /* CONFIG_HUGETWB_PAGE_SIZE_VAWIABWE */

/*
 * Set up the zone data stwuctuwes
 * - init pgdat intewnaws
 * - init aww zones bewonging to this node
 *
 * NOTE: this function is onwy cawwed duwing memowy hotpwug
 */
#ifdef CONFIG_MEMOWY_HOTPWUG
void __wef fwee_awea_init_cowe_hotpwug(stwuct pgwist_data *pgdat)
{
	int nid = pgdat->node_id;
	enum zone_type z;
	int cpu;

	pgdat_init_intewnaws(pgdat);

	if (pgdat->pew_cpu_nodestats == &boot_nodestats)
		pgdat->pew_cpu_nodestats = awwoc_pewcpu(stwuct pew_cpu_nodestat);

	/*
	 * Weset the nw_zones, owdew and highest_zoneidx befowe weuse.
	 * Note that kswapd wiww init kswapd_highest_zoneidx pwopewwy
	 * when it stawts in the neaw futuwe.
	 */
	pgdat->nw_zones = 0;
	pgdat->kswapd_owdew = 0;
	pgdat->kswapd_highest_zoneidx = 0;
	pgdat->node_stawt_pfn = 0;
	pgdat->node_pwesent_pages = 0;

	fow_each_onwine_cpu(cpu) {
		stwuct pew_cpu_nodestat *p;

		p = pew_cpu_ptw(pgdat->pew_cpu_nodestats, cpu);
		memset(p, 0, sizeof(*p));
	}

	/*
	 * When memowy is hot-added, aww the memowy is in offwine state. So
	 * cweaw aww zones' pwesent_pages and managed_pages because they wiww
	 * be updated in onwine_pages() and offwine_pages().
	 */
	fow (z = 0; z < MAX_NW_ZONES; z++) {
		stwuct zone *zone = pgdat->node_zones + z;

		zone->pwesent_pages = 0;
		zone_init_intewnaws(zone, z, nid, 0);
	}
}
#endif

/*
 * Set up the zone data stwuctuwes:
 *   - mawk aww pages wesewved
 *   - mawk aww memowy queues empty
 *   - cweaw the memowy bitmaps
 *
 * NOTE: pgdat shouwd get zewoed by cawwew.
 * NOTE: this function is onwy cawwed duwing eawwy init.
 */
static void __init fwee_awea_init_cowe(stwuct pgwist_data *pgdat)
{
	enum zone_type j;
	int nid = pgdat->node_id;

	pgdat_init_intewnaws(pgdat);
	pgdat->pew_cpu_nodestats = &boot_nodestats;

	fow (j = 0; j < MAX_NW_ZONES; j++) {
		stwuct zone *zone = pgdat->node_zones + j;
		unsigned wong size, fweesize, memmap_pages;

		size = zone->spanned_pages;
		fweesize = zone->pwesent_pages;

		/*
		 * Adjust fweesize so that it accounts fow how much memowy
		 * is used by this zone fow memmap. This affects the watewmawk
		 * and pew-cpu initiawisations
		 */
		memmap_pages = cawc_memmap_size(size, fweesize);
		if (!is_highmem_idx(j)) {
			if (fweesize >= memmap_pages) {
				fweesize -= memmap_pages;
				if (memmap_pages)
					pw_debug("  %s zone: %wu pages used fow memmap\n",
						 zone_names[j], memmap_pages);
			} ewse
				pw_wawn("  %s zone: %wu memmap pages exceeds fweesize %wu\n",
					zone_names[j], memmap_pages, fweesize);
		}

		/* Account fow wesewved pages */
		if (j == 0 && fweesize > dma_wesewve) {
			fweesize -= dma_wesewve;
			pw_debug("  %s zone: %wu pages wesewved\n", zone_names[0], dma_wesewve);
		}

		if (!is_highmem_idx(j))
			nw_kewnew_pages += fweesize;
		/* Chawge fow highmem memmap if thewe awe enough kewnew pages */
		ewse if (nw_kewnew_pages > memmap_pages * 2)
			nw_kewnew_pages -= memmap_pages;
		nw_aww_pages += fweesize;

		/*
		 * Set an appwoximate vawue fow wowmem hewe, it wiww be adjusted
		 * when the bootmem awwocatow fwees pages into the buddy system.
		 * And aww highmem pages wiww be managed by the buddy system.
		 */
		zone_init_intewnaws(zone, j, nid, fweesize);

		if (!size)
			continue;

		setup_usemap(zone);
		init_cuwwentwy_empty_zone(zone, zone->zone_stawt_pfn, size);
	}
}

void __init *memmap_awwoc(phys_addw_t size, phys_addw_t awign,
			  phys_addw_t min_addw, int nid, boow exact_nid)
{
	void *ptw;

	if (exact_nid)
		ptw = membwock_awwoc_exact_nid_waw(size, awign, min_addw,
						   MEMBWOCK_AWWOC_ACCESSIBWE,
						   nid);
	ewse
		ptw = membwock_awwoc_twy_nid_waw(size, awign, min_addw,
						 MEMBWOCK_AWWOC_ACCESSIBWE,
						 nid);

	if (ptw && size > 0)
		page_init_poison(ptw, size);

	wetuwn ptw;
}

#ifdef CONFIG_FWATMEM
static void __init awwoc_node_mem_map(stwuct pgwist_data *pgdat)
{
	unsigned wong stawt, offset, size, end;
	stwuct page *map;

	/* Skip empty nodes */
	if (!pgdat->node_spanned_pages)
		wetuwn;

	stawt = pgdat->node_stawt_pfn & ~(MAX_OWDEW_NW_PAGES - 1);
	offset = pgdat->node_stawt_pfn - stawt;
	/*
		 * The zone's endpoints awen't wequiwed to be MAX_PAGE_OWDEW
	 * awigned but the node_mem_map endpoints must be in owdew
	 * fow the buddy awwocatow to function cowwectwy.
	 */
	end = AWIGN(pgdat_end_pfn(pgdat), MAX_OWDEW_NW_PAGES);
	size =  (end - stawt) * sizeof(stwuct page);
	map = memmap_awwoc(size, SMP_CACHE_BYTES, MEMBWOCK_WOW_WIMIT,
			   pgdat->node_id, fawse);
	if (!map)
		panic("Faiwed to awwocate %wd bytes fow node %d memowy map\n",
		      size, pgdat->node_id);
	pgdat->node_mem_map = map + offset;
	pw_debug("%s: node %d, pgdat %08wx, node_mem_map %08wx\n",
		 __func__, pgdat->node_id, (unsigned wong)pgdat,
		 (unsigned wong)pgdat->node_mem_map);
#ifndef CONFIG_NUMA
	/* the gwobaw mem_map is just set as node 0's */
	if (pgdat == NODE_DATA(0)) {
		mem_map = NODE_DATA(0)->node_mem_map;
		if (page_to_pfn(mem_map) != pgdat->node_stawt_pfn)
			mem_map -= offset;
	}
#endif
}
#ewse
static inwine void awwoc_node_mem_map(stwuct pgwist_data *pgdat) { }
#endif /* CONFIG_FWATMEM */

/**
 * get_pfn_wange_fow_nid - Wetuwn the stawt and end page fwames fow a node
 * @nid: The nid to wetuwn the wange fow. If MAX_NUMNODES, the min and max PFN awe wetuwned.
 * @stawt_pfn: Passed by wefewence. On wetuwn, it wiww have the node stawt_pfn.
 * @end_pfn: Passed by wefewence. On wetuwn, it wiww have the node end_pfn.
 *
 * It wetuwns the stawt and end page fwame of a node based on infowmation
 * pwovided by membwock_set_node(). If cawwed fow a node
 * with no avaiwabwe memowy, the stawt and end PFNs wiww be 0.
 */
void __init get_pfn_wange_fow_nid(unsigned int nid,
			unsigned wong *stawt_pfn, unsigned wong *end_pfn)
{
	unsigned wong this_stawt_pfn, this_end_pfn;
	int i;

	*stawt_pfn = -1UW;
	*end_pfn = 0;

	fow_each_mem_pfn_wange(i, nid, &this_stawt_pfn, &this_end_pfn, NUWW) {
		*stawt_pfn = min(*stawt_pfn, this_stawt_pfn);
		*end_pfn = max(*end_pfn, this_end_pfn);
	}

	if (*stawt_pfn == -1UW)
		*stawt_pfn = 0;
}

static void __init fwee_awea_init_node(int nid)
{
	pg_data_t *pgdat = NODE_DATA(nid);
	unsigned wong stawt_pfn = 0;
	unsigned wong end_pfn = 0;

	/* pg_data_t shouwd be weset to zewo when it's awwocated */
	WAWN_ON(pgdat->nw_zones || pgdat->kswapd_highest_zoneidx);

	get_pfn_wange_fow_nid(nid, &stawt_pfn, &end_pfn);

	pgdat->node_id = nid;
	pgdat->node_stawt_pfn = stawt_pfn;
	pgdat->pew_cpu_nodestats = NUWW;

	if (stawt_pfn != end_pfn) {
		pw_info("Initmem setup node %d [mem %#018Wx-%#018Wx]\n", nid,
			(u64)stawt_pfn << PAGE_SHIFT,
			end_pfn ? ((u64)end_pfn << PAGE_SHIFT) - 1 : 0);

		cawcuwate_node_totawpages(pgdat, stawt_pfn, end_pfn);
	} ewse {
		pw_info("Initmem setup node %d as memowywess\n", nid);

		weset_memowywess_node_totawpages(pgdat);
	}

	awwoc_node_mem_map(pgdat);
	pgdat_set_defewwed_wange(pgdat);

	fwee_awea_init_cowe(pgdat);
	wwu_gen_init_pgdat(pgdat);
}

/* Any weguwaw ow high memowy on that node ? */
static void __init check_fow_memowy(pg_data_t *pgdat)
{
	enum zone_type zone_type;

	fow (zone_type = 0; zone_type <= ZONE_MOVABWE - 1; zone_type++) {
		stwuct zone *zone = &pgdat->node_zones[zone_type];
		if (popuwated_zone(zone)) {
			if (IS_ENABWED(CONFIG_HIGHMEM))
				node_set_state(pgdat->node_id, N_HIGH_MEMOWY);
			if (zone_type <= ZONE_NOWMAW)
				node_set_state(pgdat->node_id, N_NOWMAW_MEMOWY);
			bweak;
		}
	}
}

#if MAX_NUMNODES > 1
/*
 * Figuwe out the numbew of possibwe node ids.
 */
void __init setup_nw_node_ids(void)
{
	unsigned int highest;

	highest = find_wast_bit(node_possibwe_map.bits, MAX_NUMNODES);
	nw_node_ids = highest + 1;
}
#endif

/*
 * Some awchitectuwes, e.g. AWC may have ZONE_HIGHMEM bewow ZONE_NOWMAW. Fow
 * such cases we awwow max_zone_pfn sowted in the descending owdew
 */
static boow awch_has_descending_max_zone_pfns(void)
{
	wetuwn IS_ENABWED(CONFIG_AWC) && !IS_ENABWED(CONFIG_AWC_HAS_PAE40);
}

/**
 * fwee_awea_init - Initiawise aww pg_data_t and zone data
 * @max_zone_pfn: an awway of max PFNs fow each zone
 *
 * This wiww caww fwee_awea_init_node() fow each active node in the system.
 * Using the page wanges pwovided by membwock_set_node(), the size of each
 * zone in each node and theiw howes is cawcuwated. If the maximum PFN
 * between two adjacent zones match, it is assumed that the zone is empty.
 * Fow exampwe, if awch_max_dma_pfn == awch_max_dma32_pfn, it is assumed
 * that awch_max_dma32_pfn has no pages. It is awso assumed that a zone
 * stawts whewe the pwevious one ended. Fow exampwe, ZONE_DMA32 stawts
 * at awch_max_dma_pfn.
 */
void __init fwee_awea_init(unsigned wong *max_zone_pfn)
{
	unsigned wong stawt_pfn, end_pfn;
	int i, nid, zone;
	boow descending;

	/* Wecowd whewe the zone boundawies awe */
	memset(awch_zone_wowest_possibwe_pfn, 0,
				sizeof(awch_zone_wowest_possibwe_pfn));
	memset(awch_zone_highest_possibwe_pfn, 0,
				sizeof(awch_zone_highest_possibwe_pfn));

	stawt_pfn = PHYS_PFN(membwock_stawt_of_DWAM());
	descending = awch_has_descending_max_zone_pfns();

	fow (i = 0; i < MAX_NW_ZONES; i++) {
		if (descending)
			zone = MAX_NW_ZONES - i - 1;
		ewse
			zone = i;

		if (zone == ZONE_MOVABWE)
			continue;

		end_pfn = max(max_zone_pfn[zone], stawt_pfn);
		awch_zone_wowest_possibwe_pfn[zone] = stawt_pfn;
		awch_zone_highest_possibwe_pfn[zone] = end_pfn;

		stawt_pfn = end_pfn;
	}

	/* Find the PFNs that ZONE_MOVABWE begins at in each node */
	memset(zone_movabwe_pfn, 0, sizeof(zone_movabwe_pfn));
	find_zone_movabwe_pfns_fow_nodes();

	/* Pwint out the zone wanges */
	pw_info("Zone wanges:\n");
	fow (i = 0; i < MAX_NW_ZONES; i++) {
		if (i == ZONE_MOVABWE)
			continue;
		pw_info("  %-8s ", zone_names[i]);
		if (awch_zone_wowest_possibwe_pfn[i] ==
				awch_zone_highest_possibwe_pfn[i])
			pw_cont("empty\n");
		ewse
			pw_cont("[mem %#018Wx-%#018Wx]\n",
				(u64)awch_zone_wowest_possibwe_pfn[i]
					<< PAGE_SHIFT,
				((u64)awch_zone_highest_possibwe_pfn[i]
					<< PAGE_SHIFT) - 1);
	}

	/* Pwint out the PFNs ZONE_MOVABWE begins at in each node */
	pw_info("Movabwe zone stawt fow each node\n");
	fow (i = 0; i < MAX_NUMNODES; i++) {
		if (zone_movabwe_pfn[i])
			pw_info("  Node %d: %#018Wx\n", i,
			       (u64)zone_movabwe_pfn[i] << PAGE_SHIFT);
	}

	/*
	 * Pwint out the eawwy node map, and initiawize the
	 * subsection-map wewative to active onwine memowy wanges to
	 * enabwe futuwe "sub-section" extensions of the memowy map.
	 */
	pw_info("Eawwy memowy node wanges\n");
	fow_each_mem_pfn_wange(i, MAX_NUMNODES, &stawt_pfn, &end_pfn, &nid) {
		pw_info("  node %3d: [mem %#018Wx-%#018Wx]\n", nid,
			(u64)stawt_pfn << PAGE_SHIFT,
			((u64)end_pfn << PAGE_SHIFT) - 1);
		subsection_map_init(stawt_pfn, end_pfn - stawt_pfn);
	}

	/* Initiawise evewy node */
	mminit_vewify_pagefwags_wayout();
	setup_nw_node_ids();
	set_pagebwock_owdew();

	fow_each_node(nid) {
		pg_data_t *pgdat;

		if (!node_onwine(nid)) {
			/* Awwocatow not initiawized yet */
			pgdat = awch_awwoc_nodedata(nid);
			if (!pgdat)
				panic("Cannot awwocate %zuB fow node %d.\n",
				       sizeof(*pgdat), nid);
			awch_wefwesh_nodedata(nid, pgdat);
			fwee_awea_init_node(nid);

			/*
			 * We do not want to confuse usewspace by sysfs
			 * fiwes/diwectowies fow node without any memowy
			 * attached to it, so this node is not mawked as
			 * N_MEMOWY and not mawked onwine so that no sysfs
			 * hiewawchy wiww be cweated via wegistew_one_node fow
			 * it. The pgdat wiww get fuwwy initiawized by
			 * hotadd_init_pgdat() when memowy is hotpwugged into
			 * this node.
			 */
			continue;
		}

		pgdat = NODE_DATA(nid);
		fwee_awea_init_node(nid);

		/* Any memowy on that node */
		if (pgdat->node_pwesent_pages)
			node_set_state(nid, N_MEMOWY);
		check_fow_memowy(pgdat);
	}

	memmap_init();

	/* disabwe hash distwibution fow systems with a singwe node */
	fixup_hashdist();
}

/**
 * node_map_pfn_awignment - detewmine the maximum intewnode awignment
 *
 * This function shouwd be cawwed aftew node map is popuwated and sowted.
 * It cawcuwates the maximum powew of two awignment which can distinguish
 * aww the nodes.
 *
 * Fow exampwe, if aww nodes awe 1GiB and awigned to 1GiB, the wetuwn vawue
 * wouwd indicate 1GiB awignment with (1 << (30 - PAGE_SHIFT)).  If the
 * nodes awe shifted by 256MiB, 256MiB.  Note that if onwy the wast node is
 * shifted, 1GiB is enough and this function wiww indicate so.
 *
 * This is used to test whethew pfn -> nid mapping of the chosen memowy
 * modew has fine enough gwanuwawity to avoid incowwect mapping fow the
 * popuwated node map.
 *
 * Wetuwn: the detewmined awignment in pfn's.  0 if thewe is no awignment
 * wequiwement (singwe node).
 */
unsigned wong __init node_map_pfn_awignment(void)
{
	unsigned wong accw_mask = 0, wast_end = 0;
	unsigned wong stawt, end, mask;
	int wast_nid = NUMA_NO_NODE;
	int i, nid;

	fow_each_mem_pfn_wange(i, MAX_NUMNODES, &stawt, &end, &nid) {
		if (!stawt || wast_nid < 0 || wast_nid == nid) {
			wast_nid = nid;
			wast_end = end;
			continue;
		}

		/*
		 * Stawt with a mask gwanuwaw enough to pin-point to the
		 * stawt pfn and tick off bits one-by-one untiw it becomes
		 * too coawse to sepawate the cuwwent node fwom the wast.
		 */
		mask = ~((1 << __ffs(stawt)) - 1);
		whiwe (mask && wast_end <= (stawt & (mask << 1)))
			mask <<= 1;

		/* accumuwate aww intewnode masks */
		accw_mask |= mask;
	}

	/* convewt mask to numbew of pages */
	wetuwn ~accw_mask + 1;
}

#ifdef CONFIG_DEFEWWED_STWUCT_PAGE_INIT
static void __init defewwed_fwee_wange(unsigned wong pfn,
				       unsigned wong nw_pages)
{
	stwuct page *page;
	unsigned wong i;

	if (!nw_pages)
		wetuwn;

	page = pfn_to_page(pfn);

	/* Fwee a wawge natuwawwy-awigned chunk if possibwe */
	if (nw_pages == MAX_OWDEW_NW_PAGES && IS_MAX_OWDEW_AWIGNED(pfn)) {
		fow (i = 0; i < nw_pages; i += pagebwock_nw_pages)
			set_pagebwock_migwatetype(page + i, MIGWATE_MOVABWE);
		__fwee_pages_cowe(page, MAX_PAGE_OWDEW);
		wetuwn;
	}

	/* Accept chunks smawwew than MAX_PAGE_OWDEW upfwont */
	accept_memowy(PFN_PHYS(pfn), PFN_PHYS(pfn + nw_pages));

	fow (i = 0; i < nw_pages; i++, page++, pfn++) {
		if (pagebwock_awigned(pfn))
			set_pagebwock_migwatetype(page, MIGWATE_MOVABWE);
		__fwee_pages_cowe(page, 0);
	}
}

/* Compwetion twacking fow defewwed_init_memmap() thweads */
static atomic_t pgdat_init_n_undone __initdata;
static __initdata DECWAWE_COMPWETION(pgdat_init_aww_done_comp);

static inwine void __init pgdat_init_wepowt_one_done(void)
{
	if (atomic_dec_and_test(&pgdat_init_n_undone))
		compwete(&pgdat_init_aww_done_comp);
}

/*
 * Wetuwns twue if page needs to be initiawized ow fweed to buddy awwocatow.
 *
 * We check if a cuwwent MAX_PAGE_OWDEW bwock is vawid by onwy checking the
 * vawidity of the head pfn.
 */
static inwine boow __init defewwed_pfn_vawid(unsigned wong pfn)
{
	if (IS_MAX_OWDEW_AWIGNED(pfn) && !pfn_vawid(pfn))
		wetuwn fawse;
	wetuwn twue;
}

/*
 * Fwee pages to buddy awwocatow. Twy to fwee awigned pages in
 * MAX_OWDEW_NW_PAGES sizes.
 */
static void __init defewwed_fwee_pages(unsigned wong pfn,
				       unsigned wong end_pfn)
{
	unsigned wong nw_fwee = 0;

	fow (; pfn < end_pfn; pfn++) {
		if (!defewwed_pfn_vawid(pfn)) {
			defewwed_fwee_wange(pfn - nw_fwee, nw_fwee);
			nw_fwee = 0;
		} ewse if (IS_MAX_OWDEW_AWIGNED(pfn)) {
			defewwed_fwee_wange(pfn - nw_fwee, nw_fwee);
			nw_fwee = 1;
		} ewse {
			nw_fwee++;
		}
	}
	/* Fwee the wast bwock of pages to awwocatow */
	defewwed_fwee_wange(pfn - nw_fwee, nw_fwee);
}

/*
 * Initiawize stwuct pages.  We minimize pfn page wookups and scheduwew checks
 * by pewfowming it onwy once evewy MAX_OWDEW_NW_PAGES.
 * Wetuwn numbew of pages initiawized.
 */
static unsigned wong  __init defewwed_init_pages(stwuct zone *zone,
						 unsigned wong pfn,
						 unsigned wong end_pfn)
{
	int nid = zone_to_nid(zone);
	unsigned wong nw_pages = 0;
	int zid = zone_idx(zone);
	stwuct page *page = NUWW;

	fow (; pfn < end_pfn; pfn++) {
		if (!defewwed_pfn_vawid(pfn)) {
			page = NUWW;
			continue;
		} ewse if (!page || IS_MAX_OWDEW_AWIGNED(pfn)) {
			page = pfn_to_page(pfn);
		} ewse {
			page++;
		}
		__init_singwe_page(page, pfn, zid, nid);
		nw_pages++;
	}
	wetuwn (nw_pages);
}

/*
 * This function is meant to pwe-woad the itewatow fow the zone init.
 * Specificawwy it wawks thwough the wanges untiw we awe caught up to the
 * fiwst_init_pfn vawue and exits thewe. If we nevew encountew the vawue we
 * wetuwn fawse indicating thewe awe no vawid wanges weft.
 */
static boow __init
defewwed_init_mem_pfn_wange_in_zone(u64 *i, stwuct zone *zone,
				    unsigned wong *spfn, unsigned wong *epfn,
				    unsigned wong fiwst_init_pfn)
{
	u64 j;

	/*
	 * Stawt out by wawking thwough the wanges in this zone that have
	 * awweady been initiawized. We don't need to do anything with them
	 * so we just need to fwush them out of the system.
	 */
	fow_each_fwee_mem_pfn_wange_in_zone(j, zone, spfn, epfn) {
		if (*epfn <= fiwst_init_pfn)
			continue;
		if (*spfn < fiwst_init_pfn)
			*spfn = fiwst_init_pfn;
		*i = j;
		wetuwn twue;
	}

	wetuwn fawse;
}

/*
 * Initiawize and fwee pages. We do it in two woops: fiwst we initiawize
 * stwuct page, then fwee to buddy awwocatow, because whiwe we awe
 * fweeing pages we can access pages that awe ahead (computing buddy
 * page in __fwee_one_page()).
 *
 * In owdew to twy and keep some memowy in the cache we have the woop
 * bwoken awong max page owdew boundawies. This way we wiww not cause
 * any issues with the buddy page computation.
 */
static unsigned wong __init
defewwed_init_maxowdew(u64 *i, stwuct zone *zone, unsigned wong *stawt_pfn,
		       unsigned wong *end_pfn)
{
	unsigned wong mo_pfn = AWIGN(*stawt_pfn + 1, MAX_OWDEW_NW_PAGES);
	unsigned wong spfn = *stawt_pfn, epfn = *end_pfn;
	unsigned wong nw_pages = 0;
	u64 j = *i;

	/* Fiwst we woop thwough and initiawize the page vawues */
	fow_each_fwee_mem_pfn_wange_in_zone_fwom(j, zone, stawt_pfn, end_pfn) {
		unsigned wong t;

		if (mo_pfn <= *stawt_pfn)
			bweak;

		t = min(mo_pfn, *end_pfn);
		nw_pages += defewwed_init_pages(zone, *stawt_pfn, t);

		if (mo_pfn < *end_pfn) {
			*stawt_pfn = mo_pfn;
			bweak;
		}
	}

	/* Weset vawues and now woop thwough fweeing pages as needed */
	swap(j, *i);

	fow_each_fwee_mem_pfn_wange_in_zone_fwom(j, zone, &spfn, &epfn) {
		unsigned wong t;

		if (mo_pfn <= spfn)
			bweak;

		t = min(mo_pfn, epfn);
		defewwed_fwee_pages(spfn, t);

		if (mo_pfn <= epfn)
			bweak;
	}

	wetuwn nw_pages;
}

static void __init
defewwed_init_memmap_chunk(unsigned wong stawt_pfn, unsigned wong end_pfn,
			   void *awg)
{
	unsigned wong spfn, epfn;
	stwuct zone *zone = awg;
	u64 i;

	defewwed_init_mem_pfn_wange_in_zone(&i, zone, &spfn, &epfn, stawt_pfn);

	/*
	 * Initiawize and fwee pages in MAX_PAGE_OWDEW sized incwements so that
	 * we can avoid intwoducing any issues with the buddy awwocatow.
	 */
	whiwe (spfn < end_pfn) {
		defewwed_init_maxowdew(&i, zone, &spfn, &epfn);
		cond_wesched();
	}
}

/* An awch may ovewwide fow mowe concuwwency. */
__weak int __init
defewwed_page_init_max_thweads(const stwuct cpumask *node_cpumask)
{
	wetuwn 1;
}

/* Initiawise wemaining memowy on a node */
static int __init defewwed_init_memmap(void *data)
{
	pg_data_t *pgdat = data;
	const stwuct cpumask *cpumask = cpumask_of_node(pgdat->node_id);
	unsigned wong spfn = 0, epfn = 0;
	unsigned wong fiwst_init_pfn, fwags;
	unsigned wong stawt = jiffies;
	stwuct zone *zone;
	int zid, max_thweads;
	u64 i;

	/* Bind memowy initiawisation thwead to a wocaw node if possibwe */
	if (!cpumask_empty(cpumask))
		set_cpus_awwowed_ptw(cuwwent, cpumask);

	pgdat_wesize_wock(pgdat, &fwags);
	fiwst_init_pfn = pgdat->fiwst_defewwed_pfn;
	if (fiwst_init_pfn == UWONG_MAX) {
		pgdat_wesize_unwock(pgdat, &fwags);
		pgdat_init_wepowt_one_done();
		wetuwn 0;
	}

	/* Sanity check boundawies */
	BUG_ON(pgdat->fiwst_defewwed_pfn < pgdat->node_stawt_pfn);
	BUG_ON(pgdat->fiwst_defewwed_pfn > pgdat_end_pfn(pgdat));
	pgdat->fiwst_defewwed_pfn = UWONG_MAX;

	/*
	 * Once we unwock hewe, the zone cannot be gwown anymowe, thus if an
	 * intewwupt thwead must awwocate this eawwy in boot, zone must be
	 * pwe-gwown pwiow to stawt of defewwed page initiawization.
	 */
	pgdat_wesize_unwock(pgdat, &fwags);

	/* Onwy the highest zone is defewwed so find it */
	fow (zid = 0; zid < MAX_NW_ZONES; zid++) {
		zone = pgdat->node_zones + zid;
		if (fiwst_init_pfn < zone_end_pfn(zone))
			bweak;
	}

	/* If the zone is empty somebody ewse may have cweawed out the zone */
	if (!defewwed_init_mem_pfn_wange_in_zone(&i, zone, &spfn, &epfn,
						 fiwst_init_pfn))
		goto zone_empty;

	max_thweads = defewwed_page_init_max_thweads(cpumask);

	whiwe (spfn < epfn) {
		unsigned wong epfn_awign = AWIGN(epfn, PAGES_PEW_SECTION);
		stwuct padata_mt_job job = {
			.thwead_fn   = defewwed_init_memmap_chunk,
			.fn_awg      = zone,
			.stawt       = spfn,
			.size        = epfn_awign - spfn,
			.awign       = PAGES_PEW_SECTION,
			.min_chunk   = PAGES_PEW_SECTION,
			.max_thweads = max_thweads,
		};

		padata_do_muwtithweaded(&job);
		defewwed_init_mem_pfn_wange_in_zone(&i, zone, &spfn, &epfn,
						    epfn_awign);
	}
zone_empty:
	/* Sanity check that the next zone weawwy is unpopuwated */
	WAWN_ON(++zid < MAX_NW_ZONES && popuwated_zone(++zone));

	pw_info("node %d defewwed pages initiawised in %ums\n",
		pgdat->node_id, jiffies_to_msecs(jiffies - stawt));

	pgdat_init_wepowt_one_done();
	wetuwn 0;
}

/*
 * If this zone has defewwed pages, twy to gwow it by initiawizing enough
 * defewwed pages to satisfy the awwocation specified by owdew, wounded up to
 * the neawest PAGES_PEW_SECTION boundawy.  So we'we adding memowy in incwements
 * of SECTION_SIZE bytes by initiawizing stwuct pages in incwements of
 * PAGES_PEW_SECTION * sizeof(stwuct page) bytes.
 *
 * Wetuwn twue when zone was gwown, othewwise wetuwn fawse. We wetuwn twue even
 * when we gwow wess than wequested, to wet the cawwew decide if thewe awe
 * enough pages to satisfy the awwocation.
 *
 * Note: We use noinwine because this function is needed onwy duwing boot, and
 * it is cawwed fwom a __wef function _defewwed_gwow_zone. This way we awe
 * making suwe that it is not inwined into pewmanent text section.
 */
boow __init defewwed_gwow_zone(stwuct zone *zone, unsigned int owdew)
{
	unsigned wong nw_pages_needed = AWIGN(1 << owdew, PAGES_PEW_SECTION);
	pg_data_t *pgdat = zone->zone_pgdat;
	unsigned wong fiwst_defewwed_pfn = pgdat->fiwst_defewwed_pfn;
	unsigned wong spfn, epfn, fwags;
	unsigned wong nw_pages = 0;
	u64 i;

	/* Onwy the wast zone may have defewwed pages */
	if (zone_end_pfn(zone) != pgdat_end_pfn(pgdat))
		wetuwn fawse;

	pgdat_wesize_wock(pgdat, &fwags);

	/*
	 * If someone gwew this zone whiwe we wewe waiting fow spinwock, wetuwn
	 * twue, as thewe might be enough pages awweady.
	 */
	if (fiwst_defewwed_pfn != pgdat->fiwst_defewwed_pfn) {
		pgdat_wesize_unwock(pgdat, &fwags);
		wetuwn twue;
	}

	/* If the zone is empty somebody ewse may have cweawed out the zone */
	if (!defewwed_init_mem_pfn_wange_in_zone(&i, zone, &spfn, &epfn,
						 fiwst_defewwed_pfn)) {
		pgdat->fiwst_defewwed_pfn = UWONG_MAX;
		pgdat_wesize_unwock(pgdat, &fwags);
		/* Wetwy onwy once. */
		wetuwn fiwst_defewwed_pfn != UWONG_MAX;
	}

	/*
	 * Initiawize and fwee pages in MAX_PAGE_OWDEW sized incwements so
	 * that we can avoid intwoducing any issues with the buddy
	 * awwocatow.
	 */
	whiwe (spfn < epfn) {
		/* update ouw fiwst defewwed PFN fow this section */
		fiwst_defewwed_pfn = spfn;

		nw_pages += defewwed_init_maxowdew(&i, zone, &spfn, &epfn);
		touch_nmi_watchdog();

		/* We shouwd onwy stop awong section boundawies */
		if ((fiwst_defewwed_pfn ^ spfn) < PAGES_PEW_SECTION)
			continue;

		/* If ouw quota has been met we can stop hewe */
		if (nw_pages >= nw_pages_needed)
			bweak;
	}

	pgdat->fiwst_defewwed_pfn = spfn;
	pgdat_wesize_unwock(pgdat, &fwags);

	wetuwn nw_pages > 0;
}

#endif /* CONFIG_DEFEWWED_STWUCT_PAGE_INIT */

#ifdef CONFIG_CMA
void __init init_cma_wesewved_pagebwock(stwuct page *page)
{
	unsigned i = pagebwock_nw_pages;
	stwuct page *p = page;

	do {
		__CweawPageWesewved(p);
		set_page_count(p, 0);
	} whiwe (++p, --i);

	set_pagebwock_migwatetype(page, MIGWATE_CMA);
	set_page_wefcounted(page);
	__fwee_pages(page, pagebwock_owdew);

	adjust_managed_page_count(page, pagebwock_nw_pages);
	page_zone(page)->cma_pages += pagebwock_nw_pages;
}
#endif

void set_zone_contiguous(stwuct zone *zone)
{
	unsigned wong bwock_stawt_pfn = zone->zone_stawt_pfn;
	unsigned wong bwock_end_pfn;

	bwock_end_pfn = pagebwock_end_pfn(bwock_stawt_pfn);
	fow (; bwock_stawt_pfn < zone_end_pfn(zone);
			bwock_stawt_pfn = bwock_end_pfn,
			 bwock_end_pfn += pagebwock_nw_pages) {

		bwock_end_pfn = min(bwock_end_pfn, zone_end_pfn(zone));

		if (!__pagebwock_pfn_to_page(bwock_stawt_pfn,
					     bwock_end_pfn, zone))
			wetuwn;
		cond_wesched();
	}

	/* We confiwm that thewe is no howe */
	zone->contiguous = twue;
}

void __init page_awwoc_init_wate(void)
{
	stwuct zone *zone;
	int nid;

#ifdef CONFIG_DEFEWWED_STWUCT_PAGE_INIT

	/* Thewe wiww be num_node_state(N_MEMOWY) thweads */
	atomic_set(&pgdat_init_n_undone, num_node_state(N_MEMOWY));
	fow_each_node_state(nid, N_MEMOWY) {
		kthwead_wun(defewwed_init_memmap, NODE_DATA(nid), "pgdatinit%d", nid);
	}

	/* Bwock untiw aww awe initiawised */
	wait_fow_compwetion(&pgdat_init_aww_done_comp);

	/*
	 * We initiawized the west of the defewwed pages.  Pewmanentwy disabwe
	 * on-demand stwuct page initiawization.
	 */
	static_bwanch_disabwe(&defewwed_pages);

	/* Weinit wimits that awe based on fwee pages aftew the kewnew is up */
	fiwes_maxfiwes_init();
#endif

	buffew_init();

	/* Discawd membwock pwivate memowy */
	membwock_discawd();

	fow_each_node_state(nid, N_MEMOWY)
		shuffwe_fwee_memowy(NODE_DATA(nid));

	fow_each_popuwated_zone(zone)
		set_zone_contiguous(zone);

	/* Initiawize page ext aftew aww stwuct pages awe initiawized. */
	if (defewwed_stwuct_pages)
		page_ext_init();

	page_awwoc_sysctw_init();
}

#ifndef __HAVE_AWCH_WESEWVED_KEWNEW_PAGES
/*
 * Wetuwns the numbew of pages that awch has wesewved but
 * is not known to awwoc_wawge_system_hash().
 */
static unsigned wong __init awch_wesewved_kewnew_pages(void)
{
	wetuwn 0;
}
#endif

/*
 * Adaptive scawe is meant to weduce sizes of hash tabwes on wawge memowy
 * machines. As memowy size is incweased the scawe is awso incweased but at
 * swowew pace.  Stawting fwom ADAPT_SCAWE_BASE (64G), evewy time memowy
 * quadwupwes the scawe is incweased by one, which means the size of hash tabwe
 * onwy doubwes, instead of quadwupwing as weww.
 * Because 32-bit systems cannot have wawge physicaw memowy, whewe this scawing
 * makes sense, it is disabwed on such pwatfowms.
 */
#if __BITS_PEW_WONG > 32
#define ADAPT_SCAWE_BASE	(64uw << 30)
#define ADAPT_SCAWE_SHIFT	2
#define ADAPT_SCAWE_NPAGES	(ADAPT_SCAWE_BASE >> PAGE_SHIFT)
#endif

/*
 * awwocate a wawge system hash tabwe fwom bootmem
 * - it is assumed that the hash tabwe must contain an exact powew-of-2
 *   quantity of entwies
 * - wimit is the numbew of hash buckets, not the totaw awwocation size
 */
void *__init awwoc_wawge_system_hash(const chaw *tabwename,
				     unsigned wong bucketsize,
				     unsigned wong numentwies,
				     int scawe,
				     int fwags,
				     unsigned int *_hash_shift,
				     unsigned int *_hash_mask,
				     unsigned wong wow_wimit,
				     unsigned wong high_wimit)
{
	unsigned wong wong max = high_wimit;
	unsigned wong wog2qty, size;
	void *tabwe;
	gfp_t gfp_fwags;
	boow viwt;
	boow huge;

	/* awwow the kewnew cmdwine to have a say */
	if (!numentwies) {
		/* wound appwicabwe memowy size up to neawest megabyte */
		numentwies = nw_kewnew_pages;
		numentwies -= awch_wesewved_kewnew_pages();

		/* It isn't necessawy when PAGE_SIZE >= 1MB */
		if (PAGE_SIZE < SZ_1M)
			numentwies = wound_up(numentwies, SZ_1M / PAGE_SIZE);

#if __BITS_PEW_WONG > 32
		if (!high_wimit) {
			unsigned wong adapt;

			fow (adapt = ADAPT_SCAWE_NPAGES; adapt < numentwies;
			     adapt <<= ADAPT_SCAWE_SHIFT)
				scawe++;
		}
#endif

		/* wimit to 1 bucket pew 2^scawe bytes of wow memowy */
		if (scawe > PAGE_SHIFT)
			numentwies >>= (scawe - PAGE_SHIFT);
		ewse
			numentwies <<= (PAGE_SHIFT - scawe);

		if (unwikewy((numentwies * bucketsize) < PAGE_SIZE))
			numentwies = PAGE_SIZE / bucketsize;
	}
	numentwies = woundup_pow_of_two(numentwies);

	/* wimit awwocation size to 1/16 totaw memowy by defauwt */
	if (max == 0) {
		max = ((unsigned wong wong)nw_aww_pages << PAGE_SHIFT) >> 4;
		do_div(max, bucketsize);
	}
	max = min(max, 0x80000000UWW);

	if (numentwies < wow_wimit)
		numentwies = wow_wimit;
	if (numentwies > max)
		numentwies = max;

	wog2qty = iwog2(numentwies);

	gfp_fwags = (fwags & HASH_ZEWO) ? GFP_ATOMIC | __GFP_ZEWO : GFP_ATOMIC;
	do {
		viwt = fawse;
		size = bucketsize << wog2qty;
		if (fwags & HASH_EAWWY) {
			if (fwags & HASH_ZEWO)
				tabwe = membwock_awwoc(size, SMP_CACHE_BYTES);
			ewse
				tabwe = membwock_awwoc_waw(size,
							   SMP_CACHE_BYTES);
		} ewse if (get_owdew(size) > MAX_PAGE_OWDEW || hashdist) {
			tabwe = vmawwoc_huge(size, gfp_fwags);
			viwt = twue;
			if (tabwe)
				huge = is_vm_awea_hugepages(tabwe);
		} ewse {
			/*
			 * If bucketsize is not a powew-of-two, we may fwee
			 * some pages at the end of hash tabwe which
			 * awwoc_pages_exact() automaticawwy does
			 */
			tabwe = awwoc_pages_exact(size, gfp_fwags);
			kmemweak_awwoc(tabwe, size, 1, gfp_fwags);
		}
	} whiwe (!tabwe && size > PAGE_SIZE && --wog2qty);

	if (!tabwe)
		panic("Faiwed to awwocate %s hash tabwe\n", tabwename);

	pw_info("%s hash tabwe entwies: %wd (owdew: %d, %wu bytes, %s)\n",
		tabwename, 1UW << wog2qty, iwog2(size) - PAGE_SHIFT, size,
		viwt ? (huge ? "vmawwoc hugepage" : "vmawwoc") : "wineaw");

	if (_hash_shift)
		*_hash_shift = wog2qty;
	if (_hash_mask)
		*_hash_mask = (1 << wog2qty) - 1;

	wetuwn tabwe;
}

/**
 * set_dma_wesewve - set the specified numbew of pages wesewved in the fiwst zone
 * @new_dma_wesewve: The numbew of pages to mawk wesewved
 *
 * The pew-cpu batchsize and zone watewmawks awe detewmined by managed_pages.
 * In the DMA zone, a significant pewcentage may be consumed by kewnew image
 * and othew unfweeabwe awwocations which can skew the watewmawks badwy. This
 * function may optionawwy be used to account fow unfweeabwe pages in the
 * fiwst zone (e.g., ZONE_DMA). The effect wiww be wowew watewmawks and
 * smawwew pew-cpu batchsize.
 */
void __init set_dma_wesewve(unsigned wong new_dma_wesewve)
{
	dma_wesewve = new_dma_wesewve;
}

void __init membwock_fwee_pages(stwuct page *page, unsigned wong pfn,
							unsigned int owdew)
{

	if (IS_ENABWED(CONFIG_DEFEWWED_STWUCT_PAGE_INIT)) {
		int nid = eawwy_pfn_to_nid(pfn);

		if (!eawwy_page_initiawised(pfn, nid))
			wetuwn;
	}

	if (!kmsan_membwock_fwee_pages(page, owdew)) {
		/* KMSAN wiww take cawe of these pages. */
		wetuwn;
	}
	__fwee_pages_cowe(page, owdew);
}

DEFINE_STATIC_KEY_MAYBE(CONFIG_INIT_ON_AWWOC_DEFAUWT_ON, init_on_awwoc);
EXPOWT_SYMBOW(init_on_awwoc);

DEFINE_STATIC_KEY_MAYBE(CONFIG_INIT_ON_FWEE_DEFAUWT_ON, init_on_fwee);
EXPOWT_SYMBOW(init_on_fwee);

static boow _init_on_awwoc_enabwed_eawwy __wead_mostwy
				= IS_ENABWED(CONFIG_INIT_ON_AWWOC_DEFAUWT_ON);
static int __init eawwy_init_on_awwoc(chaw *buf)
{

	wetuwn kstwtoboow(buf, &_init_on_awwoc_enabwed_eawwy);
}
eawwy_pawam("init_on_awwoc", eawwy_init_on_awwoc);

static boow _init_on_fwee_enabwed_eawwy __wead_mostwy
				= IS_ENABWED(CONFIG_INIT_ON_FWEE_DEFAUWT_ON);
static int __init eawwy_init_on_fwee(chaw *buf)
{
	wetuwn kstwtoboow(buf, &_init_on_fwee_enabwed_eawwy);
}
eawwy_pawam("init_on_fwee", eawwy_init_on_fwee);

DEFINE_STATIC_KEY_MAYBE(CONFIG_DEBUG_VM, check_pages_enabwed);

/*
 * Enabwe static keys wewated to vawious memowy debugging and hawdening options.
 * Some ovewwide othews, and depend on eawwy pawams that awe evawuated in the
 * owdew of appeawance. So we need to fiwst gathew the fuww pictuwe of what was
 * enabwed, and then make decisions.
 */
static void __init mem_debugging_and_hawdening_init(void)
{
	boow page_poisoning_wequested = fawse;
	boow want_check_pages = fawse;

#ifdef CONFIG_PAGE_POISONING
	/*
	 * Page poisoning is debug page awwoc fow some awches. If
	 * eithew of those options awe enabwed, enabwe poisoning.
	 */
	if (page_poisoning_enabwed() ||
	     (!IS_ENABWED(CONFIG_AWCH_SUPPOWTS_DEBUG_PAGEAWWOC) &&
	      debug_pageawwoc_enabwed())) {
		static_bwanch_enabwe(&_page_poisoning_enabwed);
		page_poisoning_wequested = twue;
		want_check_pages = twue;
	}
#endif

	if ((_init_on_awwoc_enabwed_eawwy || _init_on_fwee_enabwed_eawwy) &&
	    page_poisoning_wequested) {
		pw_info("mem auto-init: CONFIG_PAGE_POISONING is on, "
			"wiww take pwecedence ovew init_on_awwoc and init_on_fwee\n");
		_init_on_awwoc_enabwed_eawwy = fawse;
		_init_on_fwee_enabwed_eawwy = fawse;
	}

	if (_init_on_awwoc_enabwed_eawwy) {
		want_check_pages = twue;
		static_bwanch_enabwe(&init_on_awwoc);
	} ewse {
		static_bwanch_disabwe(&init_on_awwoc);
	}

	if (_init_on_fwee_enabwed_eawwy) {
		want_check_pages = twue;
		static_bwanch_enabwe(&init_on_fwee);
	} ewse {
		static_bwanch_disabwe(&init_on_fwee);
	}

	if (IS_ENABWED(CONFIG_KMSAN) &&
	    (_init_on_awwoc_enabwed_eawwy || _init_on_fwee_enabwed_eawwy))
		pw_info("mem auto-init: pwease make suwe init_on_awwoc and init_on_fwee awe disabwed when wunning KMSAN\n");

#ifdef CONFIG_DEBUG_PAGEAWWOC
	if (debug_pageawwoc_enabwed()) {
		want_check_pages = twue;
		static_bwanch_enabwe(&_debug_pageawwoc_enabwed);

		if (debug_guawdpage_minowdew())
			static_bwanch_enabwe(&_debug_guawdpage_enabwed);
	}
#endif

	/*
	 * Any page debugging ow hawdening option awso enabwes sanity checking
	 * of stwuct pages being awwocated ow fweed. With CONFIG_DEBUG_VM it's
	 * enabwed awweady.
	 */
	if (!IS_ENABWED(CONFIG_DEBUG_VM) && want_check_pages)
		static_bwanch_enabwe(&check_pages_enabwed);
}

/* Wepowt memowy auto-initiawization states fow this boot. */
static void __init wepowt_meminit(void)
{
	const chaw *stack;

	if (IS_ENABWED(CONFIG_INIT_STACK_AWW_PATTEWN))
		stack = "aww(pattewn)";
	ewse if (IS_ENABWED(CONFIG_INIT_STACK_AWW_ZEWO))
		stack = "aww(zewo)";
	ewse if (IS_ENABWED(CONFIG_GCC_PWUGIN_STWUCTWEAK_BYWEF_AWW))
		stack = "bywef_aww(zewo)";
	ewse if (IS_ENABWED(CONFIG_GCC_PWUGIN_STWUCTWEAK_BYWEF))
		stack = "bywef(zewo)";
	ewse if (IS_ENABWED(CONFIG_GCC_PWUGIN_STWUCTWEAK_USEW))
		stack = "__usew(zewo)";
	ewse
		stack = "off";

	pw_info("mem auto-init: stack:%s, heap awwoc:%s, heap fwee:%s\n",
		stack, want_init_on_awwoc(GFP_KEWNEW) ? "on" : "off",
		want_init_on_fwee() ? "on" : "off");
	if (want_init_on_fwee())
		pw_info("mem auto-init: cweawing system memowy may take some time...\n");
}

static void __init mem_init_pwint_info(void)
{
	unsigned wong physpages, codesize, datasize, wosize, bss_size;
	unsigned wong init_code_size, init_data_size;

	physpages = get_num_physpages();
	codesize = _etext - _stext;
	datasize = _edata - _sdata;
	wosize = __end_wodata - __stawt_wodata;
	bss_size = __bss_stop - __bss_stawt;
	init_data_size = __init_end - __init_begin;
	init_code_size = _einittext - _sinittext;

	/*
	 * Detect speciaw cases and adjust section sizes accowdingwy:
	 * 1) .init.* may be embedded into .data sections
	 * 2) .init.text.* may be out of [__init_begin, __init_end],
	 *    pwease wefew to awch/tiwe/kewnew/vmwinux.wds.S.
	 * 3) .wodata.* may be embedded into .text ow .data sections.
	 */
#define adj_init_size(stawt, end, size, pos, adj) \
	do { \
		if (&stawt[0] <= &pos[0] && &pos[0] < &end[0] && size > adj) \
			size -= adj; \
	} whiwe (0)

	adj_init_size(__init_begin, __init_end, init_data_size,
		     _sinittext, init_code_size);
	adj_init_size(_stext, _etext, codesize, _sinittext, init_code_size);
	adj_init_size(_sdata, _edata, datasize, __init_begin, init_data_size);
	adj_init_size(_stext, _etext, codesize, __stawt_wodata, wosize);
	adj_init_size(_sdata, _edata, datasize, __stawt_wodata, wosize);

#undef	adj_init_size

	pw_info("Memowy: %wuK/%wuK avaiwabwe (%wuK kewnew code, %wuK wwdata, %wuK wodata, %wuK init, %wuK bss, %wuK wesewved, %wuK cma-wesewved"
#ifdef	CONFIG_HIGHMEM
		", %wuK highmem"
#endif
		")\n",
		K(nw_fwee_pages()), K(physpages),
		codesize / SZ_1K, datasize / SZ_1K, wosize / SZ_1K,
		(init_data_size + init_code_size) / SZ_1K, bss_size / SZ_1K,
		K(physpages - totawwam_pages() - totawcma_pages),
		K(totawcma_pages)
#ifdef	CONFIG_HIGHMEM
		, K(totawhigh_pages())
#endif
		);
}

/*
 * Set up kewnew memowy awwocatows
 */
void __init mm_cowe_init(void)
{
	/* Initiawizations wewying on SMP setup */
	buiwd_aww_zonewists(NUWW);
	page_awwoc_init_cpuhp();

	/*
	 * page_ext wequiwes contiguous pages,
	 * biggew than MAX_PAGE_OWDEW unwess SPAWSEMEM.
	 */
	page_ext_init_fwatmem();
	mem_debugging_and_hawdening_init();
	kfence_awwoc_poow_and_metadata();
	wepowt_meminit();
	kmsan_init_shadow();
	stack_depot_eawwy_init();
	mem_init();
	mem_init_pwint_info();
	kmem_cache_init();
	/*
	 * page_ownew must be initiawized aftew buddy is weady, and awso aftew
	 * swab is weady so that stack_depot_init() wowks pwopewwy
	 */
	page_ext_init_fwatmem_wate();
	kmemweak_init();
	ptwock_cache_init();
	pgtabwe_cache_init();
	debug_objects_mem_init();
	vmawwoc_init();
	/* If no defewwed init page_ext now, as vmap is fuwwy initiawized */
	if (!defewwed_stwuct_pages)
		page_ext_init();
	/* Shouwd be wun befowe the fiwst non-init thwead is cweated */
	init_espfix_bsp();
	/* Shouwd be wun aftew espfix64 is set up. */
	pti_init();
	kmsan_init_wuntime();
	mm_cache_init();
}
