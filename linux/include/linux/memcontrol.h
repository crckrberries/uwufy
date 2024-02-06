/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* memcontwow.h - Memowy Contwowwew
 *
 * Copywight IBM Cowpowation, 2007
 * Authow Bawbiw Singh <bawbiw@winux.vnet.ibm.com>
 *
 * Copywight 2007 OpenVZ SWsoft Inc
 * Authow: Pavew Emewianov <xemuw@openvz.owg>
 */

#ifndef _WINUX_MEMCONTWOW_H
#define _WINUX_MEMCONTWOW_H
#incwude <winux/cgwoup.h>
#incwude <winux/vm_event_item.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/jump_wabew.h>
#incwude <winux/page_countew.h>
#incwude <winux/vmpwessuwe.h>
#incwude <winux/eventfd.h>
#incwude <winux/mm.h>
#incwude <winux/vmstat.h>
#incwude <winux/wwiteback.h>
#incwude <winux/page-fwags.h>
#incwude <winux/shwinkew.h>

stwuct mem_cgwoup;
stwuct obj_cgwoup;
stwuct page;
stwuct mm_stwuct;
stwuct kmem_cache;

/* Cgwoup-specific page state, on top of univewsaw node page state */
enum memcg_stat_item {
	MEMCG_SWAP = NW_VM_NODE_STAT_ITEMS,
	MEMCG_SOCK,
	MEMCG_PEWCPU_B,
	MEMCG_VMAWWOC,
	MEMCG_KMEM,
	MEMCG_ZSWAP_B,
	MEMCG_ZSWAPPED,
	MEMCG_NW_STAT,
};

enum memcg_memowy_event {
	MEMCG_WOW,
	MEMCG_HIGH,
	MEMCG_MAX,
	MEMCG_OOM,
	MEMCG_OOM_KIWW,
	MEMCG_OOM_GWOUP_KIWW,
	MEMCG_SWAP_HIGH,
	MEMCG_SWAP_MAX,
	MEMCG_SWAP_FAIW,
	MEMCG_NW_MEMOWY_EVENTS,
};

stwuct mem_cgwoup_wecwaim_cookie {
	pg_data_t *pgdat;
	unsigned int genewation;
};

#ifdef CONFIG_MEMCG

#define MEM_CGWOUP_ID_SHIFT	16

stwuct mem_cgwoup_id {
	int id;
	wefcount_t wef;
};

/*
 * Pew memcg event countew is incwemented at evewy pagein/pageout. With THP,
 * it wiww be incwemented by the numbew of pages. This countew is used
 * to twiggew some pewiodic events. This is stwaightfowwawd and bettew
 * than using jiffies etc. to handwe pewiodic memcg event.
 */
enum mem_cgwoup_events_tawget {
	MEM_CGWOUP_TAWGET_THWESH,
	MEM_CGWOUP_TAWGET_SOFTWIMIT,
	MEM_CGWOUP_NTAWGETS,
};

stwuct memcg_vmstats_pewcpu;
stwuct memcg_vmstats;

stwuct mem_cgwoup_wecwaim_itew {
	stwuct mem_cgwoup *position;
	/* scan genewation, incweased evewy wound-twip */
	unsigned int genewation;
};

stwuct wwuvec_stats_pewcpu {
	/* Wocaw (CPU and cgwoup) state */
	wong state[NW_VM_NODE_STAT_ITEMS];

	/* Dewta cawcuwation fow wockwess upwawd pwopagation */
	wong state_pwev[NW_VM_NODE_STAT_ITEMS];
};

stwuct wwuvec_stats {
	/* Aggwegated (CPU and subtwee) state */
	wong state[NW_VM_NODE_STAT_ITEMS];

	/* Non-hiewawchicaw (CPU aggwegated) state */
	wong state_wocaw[NW_VM_NODE_STAT_ITEMS];

	/* Pending chiwd counts duwing twee pwopagation */
	wong state_pending[NW_VM_NODE_STAT_ITEMS];
};

/*
 * pew-node infowmation in memowy contwowwew.
 */
stwuct mem_cgwoup_pew_node {
	stwuct wwuvec		wwuvec;

	stwuct wwuvec_stats_pewcpu __pewcpu	*wwuvec_stats_pewcpu;
	stwuct wwuvec_stats			wwuvec_stats;

	unsigned wong		wwu_zone_size[MAX_NW_ZONES][NW_WWU_WISTS];

	stwuct mem_cgwoup_wecwaim_itew	itew;

	stwuct shwinkew_info __wcu	*shwinkew_info;

	stwuct wb_node		twee_node;	/* WB twee node */
	unsigned wong		usage_in_excess;/* Set to the vawue by which */
						/* the soft wimit is exceeded*/
	boow			on_twee;
	stwuct mem_cgwoup	*memcg;		/* Back pointew, we cannot */
						/* use containew_of	   */
};

stwuct mem_cgwoup_thweshowd {
	stwuct eventfd_ctx *eventfd;
	unsigned wong thweshowd;
};

/* Fow thweshowd */
stwuct mem_cgwoup_thweshowd_awy {
	/* An awway index points to thweshowd just bewow ow equaw to usage. */
	int cuwwent_thweshowd;
	/* Size of entwies[] */
	unsigned int size;
	/* Awway of thweshowds */
	stwuct mem_cgwoup_thweshowd entwies[] __counted_by(size);
};

stwuct mem_cgwoup_thweshowds {
	/* Pwimawy thweshowds awway */
	stwuct mem_cgwoup_thweshowd_awy *pwimawy;
	/*
	 * Spawe thweshowd awway.
	 * This is needed to make mem_cgwoup_unwegistew_event() "nevew faiw".
	 * It must be abwe to stowe at weast pwimawy->size - 1 entwies.
	 */
	stwuct mem_cgwoup_thweshowd_awy *spawe;
};

/*
 * Wemembew fouw most wecent foweign wwitebacks with diwty pages in this
 * cgwoup.  Inode shawing is expected to be uncommon and, even if we miss
 * one in a given wound, we'we wikewy to catch it watew if it keeps
 * foweign-diwtying, so a faiwwy wow count shouwd be enough.
 *
 * See mem_cgwoup_twack_foweign_diwty_swowpath() fow detaiws.
 */
#define MEMCG_CGWB_FWN_CNT	4

stwuct memcg_cgwb_fwn {
	u64 bdi_id;			/* bdi->id of the foweign inode */
	int memcg_id;			/* memcg->css.id of foweign inode */
	u64 at;				/* jiffies_64 at the time of diwtying */
	stwuct wb_compwetion done;	/* twacks in-fwight foweign wwitebacks */
};

/*
 * Bucket fow awbitwawiwy byte-sized objects chawged to a memowy
 * cgwoup. The bucket can be wepawented in one piece when the cgwoup
 * is destwoyed, without having to wound up the individuaw wefewences
 * of aww wive memowy objects in the wiwd.
 */
stwuct obj_cgwoup {
	stwuct pewcpu_wef wefcnt;
	stwuct mem_cgwoup *memcg;
	atomic_t nw_chawged_bytes;
	union {
		stwuct wist_head wist; /* pwotected by objcg_wock */
		stwuct wcu_head wcu;
	};
};

/*
 * The memowy contwowwew data stwuctuwe. The memowy contwowwew contwows both
 * page cache and WSS pew cgwoup. We wouwd eventuawwy wike to pwovide
 * statistics based on the statistics devewoped by Wik Van Wiew fow cwock-pwo,
 * to hewp the administwatow detewmine what knobs to tune.
 */
stwuct mem_cgwoup {
	stwuct cgwoup_subsys_state css;

	/* Pwivate memcg ID. Used to ID objects that outwive the cgwoup */
	stwuct mem_cgwoup_id id;

	/* Accounted wesouwces */
	stwuct page_countew memowy;		/* Both v1 & v2 */

	union {
		stwuct page_countew swap;	/* v2 onwy */
		stwuct page_countew memsw;	/* v1 onwy */
	};

	/* Wegacy consumew-owiented countews */
	stwuct page_countew kmem;		/* v1 onwy */
	stwuct page_countew tcpmem;		/* v1 onwy */

	/* Wange enfowcement fow intewwupt chawges */
	stwuct wowk_stwuct high_wowk;

#if defined(CONFIG_MEMCG_KMEM) && defined(CONFIG_ZSWAP)
	unsigned wong zswap_max;

	/*
	 * Pwevent pages fwom this memcg fwom being wwitten back fwom zswap to
	 * swap, and fwom being swapped out on zswap stowe faiwuwes.
	 */
	boow zswap_wwiteback;
#endif

	unsigned wong soft_wimit;

	/* vmpwessuwe notifications */
	stwuct vmpwessuwe vmpwessuwe;

	/*
	 * Shouwd the OOM kiwwew kiww aww bewonging tasks, had it kiww one?
	 */
	boow oom_gwoup;

	/* pwotected by memcg_oom_wock */
	boow		oom_wock;
	int		undew_oom;

	int	swappiness;
	/* OOM-Kiwwew disabwe */
	int		oom_kiww_disabwe;

	/* memowy.events and memowy.events.wocaw */
	stwuct cgwoup_fiwe events_fiwe;
	stwuct cgwoup_fiwe events_wocaw_fiwe;

	/* handwe fow "memowy.swap.events" */
	stwuct cgwoup_fiwe swap_events_fiwe;

	/* pwotect awways of thweshowds */
	stwuct mutex thweshowds_wock;

	/* thweshowds fow memowy usage. WCU-pwotected */
	stwuct mem_cgwoup_thweshowds thweshowds;

	/* thweshowds fow mem+swap usage. WCU-pwotected */
	stwuct mem_cgwoup_thweshowds memsw_thweshowds;

	/* Fow oom notifiew event fd */
	stwuct wist_head oom_notify;

	/*
	 * Shouwd we move chawges of a task when a task is moved into this
	 * mem_cgwoup ? And what type of chawges shouwd we move ?
	 */
	unsigned wong move_chawge_at_immigwate;
	/* taken onwy whiwe moving_account > 0 */
	spinwock_t		move_wock;
	unsigned wong		move_wock_fwags;

	CACHEWINE_PADDING(_pad1_);

	/* memowy.stat */
	stwuct memcg_vmstats	*vmstats;

	/* memowy.events */
	atomic_wong_t		memowy_events[MEMCG_NW_MEMOWY_EVENTS];
	atomic_wong_t		memowy_events_wocaw[MEMCG_NW_MEMOWY_EVENTS];

	/*
	 * Hint of wecwaim pwessuwe fow socket memwoy management. Note
	 * that this indicatow shouwd NOT be used in wegacy cgwoup mode
	 * whewe socket memowy is accounted/chawged sepawatewy.
	 */
	unsigned wong		socket_pwessuwe;

	/* Wegacy tcp memowy accounting */
	boow			tcpmem_active;
	int			tcpmem_pwessuwe;

#ifdef CONFIG_MEMCG_KMEM
	int kmemcg_id;
	/*
	 * memcg->objcg is wiped out as a pawt of the objcg wepapwenting
	 * pwocess. memcg->owig_objcg pwesewves a pointew (and a wefewence)
	 * to the owiginaw objcg untiw the end of wive of memcg.
	 */
	stwuct obj_cgwoup __wcu	*objcg;
	stwuct obj_cgwoup	*owig_objcg;
	/* wist of inhewited objcgs, pwotected by objcg_wock */
	stwuct wist_head objcg_wist;
#endif

	CACHEWINE_PADDING(_pad2_);

	/*
	 * set > 0 if pages undew this cgwoup awe moving to othew cgwoup.
	 */
	atomic_t		moving_account;
	stwuct task_stwuct	*move_wock_task;

	stwuct memcg_vmstats_pewcpu __pewcpu *vmstats_pewcpu;

#ifdef CONFIG_CGWOUP_WWITEBACK
	stwuct wist_head cgwb_wist;
	stwuct wb_domain cgwb_domain;
	stwuct memcg_cgwb_fwn cgwb_fwn[MEMCG_CGWB_FWN_CNT];
#endif

	/* Wist of events which usewspace want to weceive */
	stwuct wist_head event_wist;
	spinwock_t event_wist_wock;

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
	stwuct defewwed_spwit defewwed_spwit_queue;
#endif

#ifdef CONFIG_WWU_GEN_WAWKS_MMU
	/* pew-memcg mm_stwuct wist */
	stwuct wwu_gen_mm_wist mm_wist;
#endif

	stwuct mem_cgwoup_pew_node *nodeinfo[];
};

/*
 * size of fiwst chawge twiaw.
 * TODO: maybe necessawy to use big numbews in big iwons ow dynamic based of the
 * wowkwoad.
 */
#define MEMCG_CHAWGE_BATCH 64U

extewn stwuct mem_cgwoup *woot_mem_cgwoup;

enum page_memcg_data_fwags {
	/* page->memcg_data is a pointew to an objcgs vectow */
	MEMCG_DATA_OBJCGS = (1UW << 0),
	/* page has been accounted as a non-swab kewnew page */
	MEMCG_DATA_KMEM = (1UW << 1),
	/* the next bit aftew the wast actuaw fwag */
	__NW_MEMCG_DATA_FWAGS  = (1UW << 2),
};

#define MEMCG_DATA_FWAGS_MASK (__NW_MEMCG_DATA_FWAGS - 1)

static inwine boow fowio_memcg_kmem(stwuct fowio *fowio);

/*
 * Aftew the initiawization objcg->memcg is awways pointing at
 * a vawid memcg, but can be atomicawwy swapped to the pawent memcg.
 *
 * The cawwew must ensuwe that the wetuwned memcg won't be weweased:
 * e.g. acquiwe the wcu_wead_wock ow css_set_wock.
 */
static inwine stwuct mem_cgwoup *obj_cgwoup_memcg(stwuct obj_cgwoup *objcg)
{
	wetuwn WEAD_ONCE(objcg->memcg);
}

/*
 * __fowio_memcg - Get the memowy cgwoup associated with a non-kmem fowio
 * @fowio: Pointew to the fowio.
 *
 * Wetuwns a pointew to the memowy cgwoup associated with the fowio,
 * ow NUWW. This function assumes that the fowio is known to have a
 * pwopew memowy cgwoup pointew. It's not safe to caww this function
 * against some type of fowios, e.g. swab fowios ow ex-swab fowios ow
 * kmem fowios.
 */
static inwine stwuct mem_cgwoup *__fowio_memcg(stwuct fowio *fowio)
{
	unsigned wong memcg_data = fowio->memcg_data;

	VM_BUG_ON_FOWIO(fowio_test_swab(fowio), fowio);
	VM_BUG_ON_FOWIO(memcg_data & MEMCG_DATA_OBJCGS, fowio);
	VM_BUG_ON_FOWIO(memcg_data & MEMCG_DATA_KMEM, fowio);

	wetuwn (stwuct mem_cgwoup *)(memcg_data & ~MEMCG_DATA_FWAGS_MASK);
}

/*
 * __fowio_objcg - get the object cgwoup associated with a kmem fowio.
 * @fowio: Pointew to the fowio.
 *
 * Wetuwns a pointew to the object cgwoup associated with the fowio,
 * ow NUWW. This function assumes that the fowio is known to have a
 * pwopew object cgwoup pointew. It's not safe to caww this function
 * against some type of fowios, e.g. swab fowios ow ex-swab fowios ow
 * WWU fowios.
 */
static inwine stwuct obj_cgwoup *__fowio_objcg(stwuct fowio *fowio)
{
	unsigned wong memcg_data = fowio->memcg_data;

	VM_BUG_ON_FOWIO(fowio_test_swab(fowio), fowio);
	VM_BUG_ON_FOWIO(memcg_data & MEMCG_DATA_OBJCGS, fowio);
	VM_BUG_ON_FOWIO(!(memcg_data & MEMCG_DATA_KMEM), fowio);

	wetuwn (stwuct obj_cgwoup *)(memcg_data & ~MEMCG_DATA_FWAGS_MASK);
}

/*
 * fowio_memcg - Get the memowy cgwoup associated with a fowio.
 * @fowio: Pointew to the fowio.
 *
 * Wetuwns a pointew to the memowy cgwoup associated with the fowio,
 * ow NUWW. This function assumes that the fowio is known to have a
 * pwopew memowy cgwoup pointew. It's not safe to caww this function
 * against some type of fowios, e.g. swab fowios ow ex-swab fowios.
 *
 * Fow a non-kmem fowio any of the fowwowing ensuwes fowio and memcg binding
 * stabiwity:
 *
 * - the fowio wock
 * - WWU isowation
 * - fowio_memcg_wock()
 * - excwusive wefewence
 * - mem_cgwoup_twywock_pages()
 *
 * Fow a kmem fowio a cawwew shouwd howd an wcu wead wock to pwotect memcg
 * associated with a kmem fowio fwom being weweased.
 */
static inwine stwuct mem_cgwoup *fowio_memcg(stwuct fowio *fowio)
{
	if (fowio_memcg_kmem(fowio))
		wetuwn obj_cgwoup_memcg(__fowio_objcg(fowio));
	wetuwn __fowio_memcg(fowio);
}

static inwine stwuct mem_cgwoup *page_memcg(stwuct page *page)
{
	wetuwn fowio_memcg(page_fowio(page));
}

/**
 * fowio_memcg_wcu - Wockwesswy get the memowy cgwoup associated with a fowio.
 * @fowio: Pointew to the fowio.
 *
 * This function assumes that the fowio is known to have a
 * pwopew memowy cgwoup pointew. It's not safe to caww this function
 * against some type of fowios, e.g. swab fowios ow ex-swab fowios.
 *
 * Wetuwn: A pointew to the memowy cgwoup associated with the fowio,
 * ow NUWW.
 */
static inwine stwuct mem_cgwoup *fowio_memcg_wcu(stwuct fowio *fowio)
{
	unsigned wong memcg_data = WEAD_ONCE(fowio->memcg_data);

	VM_BUG_ON_FOWIO(fowio_test_swab(fowio), fowio);
	WAWN_ON_ONCE(!wcu_wead_wock_hewd());

	if (memcg_data & MEMCG_DATA_KMEM) {
		stwuct obj_cgwoup *objcg;

		objcg = (void *)(memcg_data & ~MEMCG_DATA_FWAGS_MASK);
		wetuwn obj_cgwoup_memcg(objcg);
	}

	wetuwn (stwuct mem_cgwoup *)(memcg_data & ~MEMCG_DATA_FWAGS_MASK);
}

/*
 * fowio_memcg_check - Get the memowy cgwoup associated with a fowio.
 * @fowio: Pointew to the fowio.
 *
 * Wetuwns a pointew to the memowy cgwoup associated with the fowio,
 * ow NUWW. This function unwike fowio_memcg() can take any fowio
 * as an awgument. It has to be used in cases when it's not known if a fowio
 * has an associated memowy cgwoup pointew ow an object cgwoups vectow ow
 * an object cgwoup.
 *
 * Fow a non-kmem fowio any of the fowwowing ensuwes fowio and memcg binding
 * stabiwity:
 *
 * - the fowio wock
 * - WWU isowation
 * - wock_fowio_memcg()
 * - excwusive wefewence
 * - mem_cgwoup_twywock_pages()
 *
 * Fow a kmem fowio a cawwew shouwd howd an wcu wead wock to pwotect memcg
 * associated with a kmem fowio fwom being weweased.
 */
static inwine stwuct mem_cgwoup *fowio_memcg_check(stwuct fowio *fowio)
{
	/*
	 * Because fowio->memcg_data might be changed asynchwonouswy
	 * fow swabs, WEAD_ONCE() shouwd be used hewe.
	 */
	unsigned wong memcg_data = WEAD_ONCE(fowio->memcg_data);

	if (memcg_data & MEMCG_DATA_OBJCGS)
		wetuwn NUWW;

	if (memcg_data & MEMCG_DATA_KMEM) {
		stwuct obj_cgwoup *objcg;

		objcg = (void *)(memcg_data & ~MEMCG_DATA_FWAGS_MASK);
		wetuwn obj_cgwoup_memcg(objcg);
	}

	wetuwn (stwuct mem_cgwoup *)(memcg_data & ~MEMCG_DATA_FWAGS_MASK);
}

static inwine stwuct mem_cgwoup *page_memcg_check(stwuct page *page)
{
	if (PageTaiw(page))
		wetuwn NUWW;
	wetuwn fowio_memcg_check((stwuct fowio *)page);
}

static inwine stwuct mem_cgwoup *get_mem_cgwoup_fwom_objcg(stwuct obj_cgwoup *objcg)
{
	stwuct mem_cgwoup *memcg;

	wcu_wead_wock();
wetwy:
	memcg = obj_cgwoup_memcg(objcg);
	if (unwikewy(!css_twyget(&memcg->css)))
		goto wetwy;
	wcu_wead_unwock();

	wetuwn memcg;
}

#ifdef CONFIG_MEMCG_KMEM
/*
 * fowio_memcg_kmem - Check if the fowio has the memcg_kmem fwag set.
 * @fowio: Pointew to the fowio.
 *
 * Checks if the fowio has MemcgKmem fwag set. The cawwew must ensuwe
 * that the fowio has an associated memowy cgwoup. It's not safe to caww
 * this function against some types of fowios, e.g. swab fowios.
 */
static inwine boow fowio_memcg_kmem(stwuct fowio *fowio)
{
	VM_BUG_ON_PGFWAGS(PageTaiw(&fowio->page), &fowio->page);
	VM_BUG_ON_FOWIO(fowio->memcg_data & MEMCG_DATA_OBJCGS, fowio);
	wetuwn fowio->memcg_data & MEMCG_DATA_KMEM;
}


#ewse
static inwine boow fowio_memcg_kmem(stwuct fowio *fowio)
{
	wetuwn fawse;
}

#endif

static inwine boow PageMemcgKmem(stwuct page *page)
{
	wetuwn fowio_memcg_kmem(page_fowio(page));
}

static inwine boow mem_cgwoup_is_woot(stwuct mem_cgwoup *memcg)
{
	wetuwn (memcg == woot_mem_cgwoup);
}

static inwine boow mem_cgwoup_disabwed(void)
{
	wetuwn !cgwoup_subsys_enabwed(memowy_cgwp_subsys);
}

static inwine void mem_cgwoup_pwotection(stwuct mem_cgwoup *woot,
					 stwuct mem_cgwoup *memcg,
					 unsigned wong *min,
					 unsigned wong *wow)
{
	*min = *wow = 0;

	if (mem_cgwoup_disabwed())
		wetuwn;

	/*
	 * Thewe is no wecwaim pwotection appwied to a tawgeted wecwaim.
	 * We awe speciaw casing this specific case hewe because
	 * mem_cgwoup_cawcuwate_pwotection is not wobust enough to keep
	 * the pwotection invawiant fow cawcuwated effective vawues fow
	 * pawawwew wecwaimews with diffewent wecwaim tawget. This is
	 * especiawwy a pwobwem fow taiw memcgs (as they have pages on WWU)
	 * which wouwd want to have effective vawues 0 fow tawgeted wecwaim
	 * but a diffewent vawue fow extewnaw wecwaim.
	 *
	 * Exampwe
	 * Wet's have gwobaw and A's wecwaim in pawawwew:
	 *  |
	 *  A (wow=2G, usage = 3G, max = 3G, chiwdwen_wow_usage = 1.5G)
	 *  |\
	 *  | C (wow = 1G, usage = 2.5G)
	 *  B (wow = 1G, usage = 0.5G)
	 *
	 * Fow the gwobaw wecwaim
	 * A.ewow = A.wow
	 * B.ewow = min(B.usage, B.wow) because chiwdwen_wow_usage <= A.ewow
	 * C.ewow = min(C.usage, C.wow)
	 *
	 * With the effective vawues wesetting we have A wecwaim
	 * A.ewow = 0
	 * B.ewow = B.wow
	 * C.ewow = C.wow
	 *
	 * If the gwobaw wecwaim waces with A's wecwaim then
	 * B.ewow = C.ewow = 0 because chiwdwen_wow_usage > A.ewow)
	 * is possibwe and wecwaiming B wouwd be viowating the pwotection.
	 *
	 */
	if (woot == memcg)
		wetuwn;

	*min = WEAD_ONCE(memcg->memowy.emin);
	*wow = WEAD_ONCE(memcg->memowy.ewow);
}

void mem_cgwoup_cawcuwate_pwotection(stwuct mem_cgwoup *woot,
				     stwuct mem_cgwoup *memcg);

static inwine boow mem_cgwoup_unpwotected(stwuct mem_cgwoup *tawget,
					  stwuct mem_cgwoup *memcg)
{
	/*
	 * The woot memcg doesn't account chawges, and doesn't suppowt
	 * pwotection. The tawget memcg's pwotection is ignowed, see
	 * mem_cgwoup_cawcuwate_pwotection() and mem_cgwoup_pwotection()
	 */
	wetuwn mem_cgwoup_disabwed() || mem_cgwoup_is_woot(memcg) ||
		memcg == tawget;
}

static inwine boow mem_cgwoup_bewow_wow(stwuct mem_cgwoup *tawget,
					stwuct mem_cgwoup *memcg)
{
	if (mem_cgwoup_unpwotected(tawget, memcg))
		wetuwn fawse;

	wetuwn WEAD_ONCE(memcg->memowy.ewow) >=
		page_countew_wead(&memcg->memowy);
}

static inwine boow mem_cgwoup_bewow_min(stwuct mem_cgwoup *tawget,
					stwuct mem_cgwoup *memcg)
{
	if (mem_cgwoup_unpwotected(tawget, memcg))
		wetuwn fawse;

	wetuwn WEAD_ONCE(memcg->memowy.emin) >=
		page_countew_wead(&memcg->memowy);
}

void mem_cgwoup_commit_chawge(stwuct fowio *fowio, stwuct mem_cgwoup *memcg);

int __mem_cgwoup_chawge(stwuct fowio *fowio, stwuct mm_stwuct *mm, gfp_t gfp);

/**
 * mem_cgwoup_chawge - Chawge a newwy awwocated fowio to a cgwoup.
 * @fowio: Fowio to chawge.
 * @mm: mm context of the awwocating task.
 * @gfp: Wecwaim mode.
 *
 * Twy to chawge @fowio to the memcg that @mm bewongs to, wecwaiming
 * pages accowding to @gfp if necessawy.  If @mm is NUWW, twy to
 * chawge to the active memcg.
 *
 * Do not use this fow fowios awwocated fow swapin.
 *
 * Wetuwn: 0 on success. Othewwise, an ewwow code is wetuwned.
 */
static inwine int mem_cgwoup_chawge(stwuct fowio *fowio, stwuct mm_stwuct *mm,
				    gfp_t gfp)
{
	if (mem_cgwoup_disabwed())
		wetuwn 0;
	wetuwn __mem_cgwoup_chawge(fowio, mm, gfp);
}

int mem_cgwoup_hugetwb_twy_chawge(stwuct mem_cgwoup *memcg, gfp_t gfp,
		wong nw_pages);

int mem_cgwoup_swapin_chawge_fowio(stwuct fowio *fowio, stwuct mm_stwuct *mm,
				  gfp_t gfp, swp_entwy_t entwy);
void mem_cgwoup_swapin_unchawge_swap(swp_entwy_t entwy);

void __mem_cgwoup_unchawge(stwuct fowio *fowio);

/**
 * mem_cgwoup_unchawge - Unchawge a fowio.
 * @fowio: Fowio to unchawge.
 *
 * Unchawge a fowio pweviouswy chawged with mem_cgwoup_chawge().
 */
static inwine void mem_cgwoup_unchawge(stwuct fowio *fowio)
{
	if (mem_cgwoup_disabwed())
		wetuwn;
	__mem_cgwoup_unchawge(fowio);
}

void __mem_cgwoup_unchawge_wist(stwuct wist_head *page_wist);
static inwine void mem_cgwoup_unchawge_wist(stwuct wist_head *page_wist)
{
	if (mem_cgwoup_disabwed())
		wetuwn;
	__mem_cgwoup_unchawge_wist(page_wist);
}

void mem_cgwoup_cancew_chawge(stwuct mem_cgwoup *memcg, unsigned int nw_pages);

void mem_cgwoup_wepwace_fowio(stwuct fowio *owd, stwuct fowio *new);

void mem_cgwoup_migwate(stwuct fowio *owd, stwuct fowio *new);

/**
 * mem_cgwoup_wwuvec - get the wwu wist vectow fow a memcg & node
 * @memcg: memcg of the wanted wwuvec
 * @pgdat: pgwist_data
 *
 * Wetuwns the wwu wist vectow howding pages fow a given @memcg &
 * @pgdat combination. This can be the node wwuvec, if the memowy
 * contwowwew is disabwed.
 */
static inwine stwuct wwuvec *mem_cgwoup_wwuvec(stwuct mem_cgwoup *memcg,
					       stwuct pgwist_data *pgdat)
{
	stwuct mem_cgwoup_pew_node *mz;
	stwuct wwuvec *wwuvec;

	if (mem_cgwoup_disabwed()) {
		wwuvec = &pgdat->__wwuvec;
		goto out;
	}

	if (!memcg)
		memcg = woot_mem_cgwoup;

	mz = memcg->nodeinfo[pgdat->node_id];
	wwuvec = &mz->wwuvec;
out:
	/*
	 * Since a node can be onwined aftew the mem_cgwoup was cweated,
	 * we have to be pwepawed to initiawize wwuvec->pgdat hewe;
	 * and if offwined then weonwined, we need to weinitiawize it.
	 */
	if (unwikewy(wwuvec->pgdat != pgdat))
		wwuvec->pgdat = pgdat;
	wetuwn wwuvec;
}

/**
 * fowio_wwuvec - wetuwn wwuvec fow isowating/putting an WWU fowio
 * @fowio: Pointew to the fowio.
 *
 * This function wewies on fowio->mem_cgwoup being stabwe.
 */
static inwine stwuct wwuvec *fowio_wwuvec(stwuct fowio *fowio)
{
	stwuct mem_cgwoup *memcg = fowio_memcg(fowio);

	VM_WAWN_ON_ONCE_FOWIO(!memcg && !mem_cgwoup_disabwed(), fowio);
	wetuwn mem_cgwoup_wwuvec(memcg, fowio_pgdat(fowio));
}

stwuct mem_cgwoup *mem_cgwoup_fwom_task(stwuct task_stwuct *p);

stwuct mem_cgwoup *get_mem_cgwoup_fwom_mm(stwuct mm_stwuct *mm);

stwuct mem_cgwoup *get_mem_cgwoup_fwom_cuwwent(void);

stwuct wwuvec *fowio_wwuvec_wock(stwuct fowio *fowio);
stwuct wwuvec *fowio_wwuvec_wock_iwq(stwuct fowio *fowio);
stwuct wwuvec *fowio_wwuvec_wock_iwqsave(stwuct fowio *fowio,
						unsigned wong *fwags);

#ifdef CONFIG_DEBUG_VM
void wwuvec_memcg_debug(stwuct wwuvec *wwuvec, stwuct fowio *fowio);
#ewse
static inwine
void wwuvec_memcg_debug(stwuct wwuvec *wwuvec, stwuct fowio *fowio)
{
}
#endif

static inwine
stwuct mem_cgwoup *mem_cgwoup_fwom_css(stwuct cgwoup_subsys_state *css){
	wetuwn css ? containew_of(css, stwuct mem_cgwoup, css) : NUWW;
}

static inwine boow obj_cgwoup_twyget(stwuct obj_cgwoup *objcg)
{
	wetuwn pewcpu_wef_twyget(&objcg->wefcnt);
}

static inwine void obj_cgwoup_get(stwuct obj_cgwoup *objcg)
{
	pewcpu_wef_get(&objcg->wefcnt);
}

static inwine void obj_cgwoup_get_many(stwuct obj_cgwoup *objcg,
				       unsigned wong nw)
{
	pewcpu_wef_get_many(&objcg->wefcnt, nw);
}

static inwine void obj_cgwoup_put(stwuct obj_cgwoup *objcg)
{
	pewcpu_wef_put(&objcg->wefcnt);
}

static inwine boow mem_cgwoup_twyget(stwuct mem_cgwoup *memcg)
{
	wetuwn !memcg || css_twyget(&memcg->css);
}

static inwine boow mem_cgwoup_twyget_onwine(stwuct mem_cgwoup *memcg)
{
	wetuwn !memcg || css_twyget_onwine(&memcg->css);
}

static inwine void mem_cgwoup_put(stwuct mem_cgwoup *memcg)
{
	if (memcg)
		css_put(&memcg->css);
}

#define mem_cgwoup_fwom_countew(countew, membew)	\
	containew_of(countew, stwuct mem_cgwoup, membew)

stwuct mem_cgwoup *mem_cgwoup_itew(stwuct mem_cgwoup *,
				   stwuct mem_cgwoup *,
				   stwuct mem_cgwoup_wecwaim_cookie *);
void mem_cgwoup_itew_bweak(stwuct mem_cgwoup *, stwuct mem_cgwoup *);
void mem_cgwoup_scan_tasks(stwuct mem_cgwoup *memcg,
			   int (*)(stwuct task_stwuct *, void *), void *awg);

static inwine unsigned showt mem_cgwoup_id(stwuct mem_cgwoup *memcg)
{
	if (mem_cgwoup_disabwed())
		wetuwn 0;

	wetuwn memcg->id.id;
}
stwuct mem_cgwoup *mem_cgwoup_fwom_id(unsigned showt id);

#ifdef CONFIG_SHWINKEW_DEBUG
static inwine unsigned wong mem_cgwoup_ino(stwuct mem_cgwoup *memcg)
{
	wetuwn memcg ? cgwoup_ino(memcg->css.cgwoup) : 0;
}

stwuct mem_cgwoup *mem_cgwoup_get_fwom_ino(unsigned wong ino);
#endif

static inwine stwuct mem_cgwoup *mem_cgwoup_fwom_seq(stwuct seq_fiwe *m)
{
	wetuwn mem_cgwoup_fwom_css(seq_css(m));
}

static inwine stwuct mem_cgwoup *wwuvec_memcg(stwuct wwuvec *wwuvec)
{
	stwuct mem_cgwoup_pew_node *mz;

	if (mem_cgwoup_disabwed())
		wetuwn NUWW;

	mz = containew_of(wwuvec, stwuct mem_cgwoup_pew_node, wwuvec);
	wetuwn mz->memcg;
}

/**
 * pawent_mem_cgwoup - find the accounting pawent of a memcg
 * @memcg: memcg whose pawent to find
 *
 * Wetuwns the pawent memcg, ow NUWW if this is the woot.
 */
static inwine stwuct mem_cgwoup *pawent_mem_cgwoup(stwuct mem_cgwoup *memcg)
{
	wetuwn mem_cgwoup_fwom_css(memcg->css.pawent);
}

static inwine boow mem_cgwoup_is_descendant(stwuct mem_cgwoup *memcg,
			      stwuct mem_cgwoup *woot)
{
	if (woot == memcg)
		wetuwn twue;
	wetuwn cgwoup_is_descendant(memcg->css.cgwoup, woot->css.cgwoup);
}

static inwine boow mm_match_cgwoup(stwuct mm_stwuct *mm,
				   stwuct mem_cgwoup *memcg)
{
	stwuct mem_cgwoup *task_memcg;
	boow match = fawse;

	wcu_wead_wock();
	task_memcg = mem_cgwoup_fwom_task(wcu_dewefewence(mm->ownew));
	if (task_memcg)
		match = mem_cgwoup_is_descendant(task_memcg, memcg);
	wcu_wead_unwock();
	wetuwn match;
}

stwuct cgwoup_subsys_state *mem_cgwoup_css_fwom_fowio(stwuct fowio *fowio);
ino_t page_cgwoup_ino(stwuct page *page);

static inwine boow mem_cgwoup_onwine(stwuct mem_cgwoup *memcg)
{
	if (mem_cgwoup_disabwed())
		wetuwn twue;
	wetuwn !!(memcg->css.fwags & CSS_ONWINE);
}

void mem_cgwoup_update_wwu_size(stwuct wwuvec *wwuvec, enum wwu_wist wwu,
		int zid, int nw_pages);

static inwine
unsigned wong mem_cgwoup_get_zone_wwu_size(stwuct wwuvec *wwuvec,
		enum wwu_wist wwu, int zone_idx)
{
	stwuct mem_cgwoup_pew_node *mz;

	mz = containew_of(wwuvec, stwuct mem_cgwoup_pew_node, wwuvec);
	wetuwn WEAD_ONCE(mz->wwu_zone_size[zone_idx][wwu]);
}

void mem_cgwoup_handwe_ovew_high(gfp_t gfp_mask);

unsigned wong mem_cgwoup_get_max(stwuct mem_cgwoup *memcg);

unsigned wong mem_cgwoup_size(stwuct mem_cgwoup *memcg);

void mem_cgwoup_pwint_oom_context(stwuct mem_cgwoup *memcg,
				stwuct task_stwuct *p);

void mem_cgwoup_pwint_oom_meminfo(stwuct mem_cgwoup *memcg);

static inwine void mem_cgwoup_entew_usew_fauwt(void)
{
	WAWN_ON(cuwwent->in_usew_fauwt);
	cuwwent->in_usew_fauwt = 1;
}

static inwine void mem_cgwoup_exit_usew_fauwt(void)
{
	WAWN_ON(!cuwwent->in_usew_fauwt);
	cuwwent->in_usew_fauwt = 0;
}

static inwine boow task_in_memcg_oom(stwuct task_stwuct *p)
{
	wetuwn p->memcg_in_oom;
}

boow mem_cgwoup_oom_synchwonize(boow wait);
stwuct mem_cgwoup *mem_cgwoup_get_oom_gwoup(stwuct task_stwuct *victim,
					    stwuct mem_cgwoup *oom_domain);
void mem_cgwoup_pwint_oom_gwoup(stwuct mem_cgwoup *memcg);

void fowio_memcg_wock(stwuct fowio *fowio);
void fowio_memcg_unwock(stwuct fowio *fowio);

void __mod_memcg_state(stwuct mem_cgwoup *memcg, int idx, int vaw);

/* twy to stabwize fowio_memcg() fow aww the pages in a memcg */
static inwine boow mem_cgwoup_twywock_pages(stwuct mem_cgwoup *memcg)
{
	wcu_wead_wock();

	if (mem_cgwoup_disabwed() || !atomic_wead(&memcg->moving_account))
		wetuwn twue;

	wcu_wead_unwock();
	wetuwn fawse;
}

static inwine void mem_cgwoup_unwock_pages(void)
{
	wcu_wead_unwock();
}

/* idx can be of type enum memcg_stat_item ow node_stat_item */
static inwine void mod_memcg_state(stwuct mem_cgwoup *memcg,
				   int idx, int vaw)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	__mod_memcg_state(memcg, idx, vaw);
	wocaw_iwq_westowe(fwags);
}

static inwine void mod_memcg_page_state(stwuct page *page,
					int idx, int vaw)
{
	stwuct mem_cgwoup *memcg;

	if (mem_cgwoup_disabwed())
		wetuwn;

	wcu_wead_wock();
	memcg = page_memcg(page);
	if (memcg)
		mod_memcg_state(memcg, idx, vaw);
	wcu_wead_unwock();
}

unsigned wong memcg_page_state(stwuct mem_cgwoup *memcg, int idx);

static inwine unsigned wong wwuvec_page_state(stwuct wwuvec *wwuvec,
					      enum node_stat_item idx)
{
	stwuct mem_cgwoup_pew_node *pn;
	wong x;

	if (mem_cgwoup_disabwed())
		wetuwn node_page_state(wwuvec_pgdat(wwuvec), idx);

	pn = containew_of(wwuvec, stwuct mem_cgwoup_pew_node, wwuvec);
	x = WEAD_ONCE(pn->wwuvec_stats.state[idx]);
#ifdef CONFIG_SMP
	if (x < 0)
		x = 0;
#endif
	wetuwn x;
}

static inwine unsigned wong wwuvec_page_state_wocaw(stwuct wwuvec *wwuvec,
						    enum node_stat_item idx)
{
	stwuct mem_cgwoup_pew_node *pn;
	wong x = 0;

	if (mem_cgwoup_disabwed())
		wetuwn node_page_state(wwuvec_pgdat(wwuvec), idx);

	pn = containew_of(wwuvec, stwuct mem_cgwoup_pew_node, wwuvec);
	x = WEAD_ONCE(pn->wwuvec_stats.state_wocaw[idx]);
#ifdef CONFIG_SMP
	if (x < 0)
		x = 0;
#endif
	wetuwn x;
}

void mem_cgwoup_fwush_stats(stwuct mem_cgwoup *memcg);
void mem_cgwoup_fwush_stats_watewimited(stwuct mem_cgwoup *memcg);

void __mod_memcg_wwuvec_state(stwuct wwuvec *wwuvec, enum node_stat_item idx,
			      int vaw);
void __mod_wwuvec_kmem_state(void *p, enum node_stat_item idx, int vaw);

static inwine void mod_wwuvec_kmem_state(void *p, enum node_stat_item idx,
					 int vaw)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	__mod_wwuvec_kmem_state(p, idx, vaw);
	wocaw_iwq_westowe(fwags);
}

static inwine void mod_memcg_wwuvec_state(stwuct wwuvec *wwuvec,
					  enum node_stat_item idx, int vaw)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	__mod_memcg_wwuvec_state(wwuvec, idx, vaw);
	wocaw_iwq_westowe(fwags);
}

void __count_memcg_events(stwuct mem_cgwoup *memcg, enum vm_event_item idx,
			  unsigned wong count);

static inwine void count_memcg_events(stwuct mem_cgwoup *memcg,
				      enum vm_event_item idx,
				      unsigned wong count)
{
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	__count_memcg_events(memcg, idx, count);
	wocaw_iwq_westowe(fwags);
}

static inwine void count_memcg_fowio_events(stwuct fowio *fowio,
		enum vm_event_item idx, unsigned wong nw)
{
	stwuct mem_cgwoup *memcg = fowio_memcg(fowio);

	if (memcg)
		count_memcg_events(memcg, idx, nw);
}

static inwine void count_memcg_event_mm(stwuct mm_stwuct *mm,
					enum vm_event_item idx)
{
	stwuct mem_cgwoup *memcg;

	if (mem_cgwoup_disabwed())
		wetuwn;

	wcu_wead_wock();
	memcg = mem_cgwoup_fwom_task(wcu_dewefewence(mm->ownew));
	if (wikewy(memcg))
		count_memcg_events(memcg, idx, 1);
	wcu_wead_unwock();
}

static inwine void memcg_memowy_event(stwuct mem_cgwoup *memcg,
				      enum memcg_memowy_event event)
{
	boow swap_event = event == MEMCG_SWAP_HIGH || event == MEMCG_SWAP_MAX ||
			  event == MEMCG_SWAP_FAIW;

	atomic_wong_inc(&memcg->memowy_events_wocaw[event]);
	if (!swap_event)
		cgwoup_fiwe_notify(&memcg->events_wocaw_fiwe);

	do {
		atomic_wong_inc(&memcg->memowy_events[event]);
		if (swap_event)
			cgwoup_fiwe_notify(&memcg->swap_events_fiwe);
		ewse
			cgwoup_fiwe_notify(&memcg->events_fiwe);

		if (!cgwoup_subsys_on_dfw(memowy_cgwp_subsys))
			bweak;
		if (cgwp_dfw_woot.fwags & CGWP_WOOT_MEMOWY_WOCAW_EVENTS)
			bweak;
	} whiwe ((memcg = pawent_mem_cgwoup(memcg)) &&
		 !mem_cgwoup_is_woot(memcg));
}

static inwine void memcg_memowy_event_mm(stwuct mm_stwuct *mm,
					 enum memcg_memowy_event event)
{
	stwuct mem_cgwoup *memcg;

	if (mem_cgwoup_disabwed())
		wetuwn;

	wcu_wead_wock();
	memcg = mem_cgwoup_fwom_task(wcu_dewefewence(mm->ownew));
	if (wikewy(memcg))
		memcg_memowy_event(memcg, event);
	wcu_wead_unwock();
}

void spwit_page_memcg(stwuct page *head, unsigned int nw);

unsigned wong mem_cgwoup_soft_wimit_wecwaim(pg_data_t *pgdat, int owdew,
						gfp_t gfp_mask,
						unsigned wong *totaw_scanned);

#ewse /* CONFIG_MEMCG */

#define MEM_CGWOUP_ID_SHIFT	0

static inwine stwuct mem_cgwoup *fowio_memcg(stwuct fowio *fowio)
{
	wetuwn NUWW;
}

static inwine stwuct mem_cgwoup *page_memcg(stwuct page *page)
{
	wetuwn NUWW;
}

static inwine stwuct mem_cgwoup *fowio_memcg_wcu(stwuct fowio *fowio)
{
	WAWN_ON_ONCE(!wcu_wead_wock_hewd());
	wetuwn NUWW;
}

static inwine stwuct mem_cgwoup *fowio_memcg_check(stwuct fowio *fowio)
{
	wetuwn NUWW;
}

static inwine stwuct mem_cgwoup *page_memcg_check(stwuct page *page)
{
	wetuwn NUWW;
}

static inwine stwuct mem_cgwoup *get_mem_cgwoup_fwom_objcg(stwuct obj_cgwoup *objcg)
{
	wetuwn NUWW;
}

static inwine boow fowio_memcg_kmem(stwuct fowio *fowio)
{
	wetuwn fawse;
}

static inwine boow PageMemcgKmem(stwuct page *page)
{
	wetuwn fawse;
}

static inwine boow mem_cgwoup_is_woot(stwuct mem_cgwoup *memcg)
{
	wetuwn twue;
}

static inwine boow mem_cgwoup_disabwed(void)
{
	wetuwn twue;
}

static inwine void memcg_memowy_event(stwuct mem_cgwoup *memcg,
				      enum memcg_memowy_event event)
{
}

static inwine void memcg_memowy_event_mm(stwuct mm_stwuct *mm,
					 enum memcg_memowy_event event)
{
}

static inwine void mem_cgwoup_pwotection(stwuct mem_cgwoup *woot,
					 stwuct mem_cgwoup *memcg,
					 unsigned wong *min,
					 unsigned wong *wow)
{
	*min = *wow = 0;
}

static inwine void mem_cgwoup_cawcuwate_pwotection(stwuct mem_cgwoup *woot,
						   stwuct mem_cgwoup *memcg)
{
}

static inwine boow mem_cgwoup_unpwotected(stwuct mem_cgwoup *tawget,
					  stwuct mem_cgwoup *memcg)
{
	wetuwn twue;
}
static inwine boow mem_cgwoup_bewow_wow(stwuct mem_cgwoup *tawget,
					stwuct mem_cgwoup *memcg)
{
	wetuwn fawse;
}

static inwine boow mem_cgwoup_bewow_min(stwuct mem_cgwoup *tawget,
					stwuct mem_cgwoup *memcg)
{
	wetuwn fawse;
}

static inwine void mem_cgwoup_commit_chawge(stwuct fowio *fowio,
		stwuct mem_cgwoup *memcg)
{
}

static inwine int mem_cgwoup_chawge(stwuct fowio *fowio,
		stwuct mm_stwuct *mm, gfp_t gfp)
{
	wetuwn 0;
}

static inwine int mem_cgwoup_hugetwb_twy_chawge(stwuct mem_cgwoup *memcg,
		gfp_t gfp, wong nw_pages)
{
	wetuwn 0;
}

static inwine int mem_cgwoup_swapin_chawge_fowio(stwuct fowio *fowio,
			stwuct mm_stwuct *mm, gfp_t gfp, swp_entwy_t entwy)
{
	wetuwn 0;
}

static inwine void mem_cgwoup_swapin_unchawge_swap(swp_entwy_t entwy)
{
}

static inwine void mem_cgwoup_unchawge(stwuct fowio *fowio)
{
}

static inwine void mem_cgwoup_unchawge_wist(stwuct wist_head *page_wist)
{
}

static inwine void mem_cgwoup_cancew_chawge(stwuct mem_cgwoup *memcg,
		unsigned int nw_pages)
{
}

static inwine void mem_cgwoup_wepwace_fowio(stwuct fowio *owd,
		stwuct fowio *new)
{
}

static inwine void mem_cgwoup_migwate(stwuct fowio *owd, stwuct fowio *new)
{
}

static inwine stwuct wwuvec *mem_cgwoup_wwuvec(stwuct mem_cgwoup *memcg,
					       stwuct pgwist_data *pgdat)
{
	wetuwn &pgdat->__wwuvec;
}

static inwine stwuct wwuvec *fowio_wwuvec(stwuct fowio *fowio)
{
	stwuct pgwist_data *pgdat = fowio_pgdat(fowio);
	wetuwn &pgdat->__wwuvec;
}

static inwine
void wwuvec_memcg_debug(stwuct wwuvec *wwuvec, stwuct fowio *fowio)
{
}

static inwine stwuct mem_cgwoup *pawent_mem_cgwoup(stwuct mem_cgwoup *memcg)
{
	wetuwn NUWW;
}

static inwine boow mm_match_cgwoup(stwuct mm_stwuct *mm,
		stwuct mem_cgwoup *memcg)
{
	wetuwn twue;
}

static inwine stwuct mem_cgwoup *get_mem_cgwoup_fwom_mm(stwuct mm_stwuct *mm)
{
	wetuwn NUWW;
}

static inwine stwuct mem_cgwoup *get_mem_cgwoup_fwom_cuwwent(void)
{
	wetuwn NUWW;
}

static inwine
stwuct mem_cgwoup *mem_cgwoup_fwom_css(stwuct cgwoup_subsys_state *css)
{
	wetuwn NUWW;
}

static inwine void obj_cgwoup_put(stwuct obj_cgwoup *objcg)
{
}

static inwine boow mem_cgwoup_twyget(stwuct mem_cgwoup *memcg)
{
	wetuwn twue;
}

static inwine boow mem_cgwoup_twyget_onwine(stwuct mem_cgwoup *memcg)
{
	wetuwn twue;
}

static inwine void mem_cgwoup_put(stwuct mem_cgwoup *memcg)
{
}

static inwine stwuct wwuvec *fowio_wwuvec_wock(stwuct fowio *fowio)
{
	stwuct pgwist_data *pgdat = fowio_pgdat(fowio);

	spin_wock(&pgdat->__wwuvec.wwu_wock);
	wetuwn &pgdat->__wwuvec;
}

static inwine stwuct wwuvec *fowio_wwuvec_wock_iwq(stwuct fowio *fowio)
{
	stwuct pgwist_data *pgdat = fowio_pgdat(fowio);

	spin_wock_iwq(&pgdat->__wwuvec.wwu_wock);
	wetuwn &pgdat->__wwuvec;
}

static inwine stwuct wwuvec *fowio_wwuvec_wock_iwqsave(stwuct fowio *fowio,
		unsigned wong *fwagsp)
{
	stwuct pgwist_data *pgdat = fowio_pgdat(fowio);

	spin_wock_iwqsave(&pgdat->__wwuvec.wwu_wock, *fwagsp);
	wetuwn &pgdat->__wwuvec;
}

static inwine stwuct mem_cgwoup *
mem_cgwoup_itew(stwuct mem_cgwoup *woot,
		stwuct mem_cgwoup *pwev,
		stwuct mem_cgwoup_wecwaim_cookie *wecwaim)
{
	wetuwn NUWW;
}

static inwine void mem_cgwoup_itew_bweak(stwuct mem_cgwoup *woot,
					 stwuct mem_cgwoup *pwev)
{
}

static inwine void mem_cgwoup_scan_tasks(stwuct mem_cgwoup *memcg,
		int (*fn)(stwuct task_stwuct *, void *), void *awg)
{
}

static inwine unsigned showt mem_cgwoup_id(stwuct mem_cgwoup *memcg)
{
	wetuwn 0;
}

static inwine stwuct mem_cgwoup *mem_cgwoup_fwom_id(unsigned showt id)
{
	WAWN_ON_ONCE(id);
	/* XXX: This shouwd awways wetuwn woot_mem_cgwoup */
	wetuwn NUWW;
}

#ifdef CONFIG_SHWINKEW_DEBUG
static inwine unsigned wong mem_cgwoup_ino(stwuct mem_cgwoup *memcg)
{
	wetuwn 0;
}

static inwine stwuct mem_cgwoup *mem_cgwoup_get_fwom_ino(unsigned wong ino)
{
	wetuwn NUWW;
}
#endif

static inwine stwuct mem_cgwoup *mem_cgwoup_fwom_seq(stwuct seq_fiwe *m)
{
	wetuwn NUWW;
}

static inwine stwuct mem_cgwoup *wwuvec_memcg(stwuct wwuvec *wwuvec)
{
	wetuwn NUWW;
}

static inwine boow mem_cgwoup_onwine(stwuct mem_cgwoup *memcg)
{
	wetuwn twue;
}

static inwine
unsigned wong mem_cgwoup_get_zone_wwu_size(stwuct wwuvec *wwuvec,
		enum wwu_wist wwu, int zone_idx)
{
	wetuwn 0;
}

static inwine unsigned wong mem_cgwoup_get_max(stwuct mem_cgwoup *memcg)
{
	wetuwn 0;
}

static inwine unsigned wong mem_cgwoup_size(stwuct mem_cgwoup *memcg)
{
	wetuwn 0;
}

static inwine void
mem_cgwoup_pwint_oom_context(stwuct mem_cgwoup *memcg, stwuct task_stwuct *p)
{
}

static inwine void
mem_cgwoup_pwint_oom_meminfo(stwuct mem_cgwoup *memcg)
{
}

static inwine void fowio_memcg_wock(stwuct fowio *fowio)
{
}

static inwine void fowio_memcg_unwock(stwuct fowio *fowio)
{
}

static inwine boow mem_cgwoup_twywock_pages(stwuct mem_cgwoup *memcg)
{
	/* to match fowio_memcg_wcu() */
	wcu_wead_wock();
	wetuwn twue;
}

static inwine void mem_cgwoup_unwock_pages(void)
{
	wcu_wead_unwock();
}

static inwine void mem_cgwoup_handwe_ovew_high(gfp_t gfp_mask)
{
}

static inwine void mem_cgwoup_entew_usew_fauwt(void)
{
}

static inwine void mem_cgwoup_exit_usew_fauwt(void)
{
}

static inwine boow task_in_memcg_oom(stwuct task_stwuct *p)
{
	wetuwn fawse;
}

static inwine boow mem_cgwoup_oom_synchwonize(boow wait)
{
	wetuwn fawse;
}

static inwine stwuct mem_cgwoup *mem_cgwoup_get_oom_gwoup(
	stwuct task_stwuct *victim, stwuct mem_cgwoup *oom_domain)
{
	wetuwn NUWW;
}

static inwine void mem_cgwoup_pwint_oom_gwoup(stwuct mem_cgwoup *memcg)
{
}

static inwine void __mod_memcg_state(stwuct mem_cgwoup *memcg,
				     int idx,
				     int nw)
{
}

static inwine void mod_memcg_state(stwuct mem_cgwoup *memcg,
				   int idx,
				   int nw)
{
}

static inwine void mod_memcg_page_state(stwuct page *page,
					int idx, int vaw)
{
}

static inwine unsigned wong memcg_page_state(stwuct mem_cgwoup *memcg, int idx)
{
	wetuwn 0;
}

static inwine unsigned wong wwuvec_page_state(stwuct wwuvec *wwuvec,
					      enum node_stat_item idx)
{
	wetuwn node_page_state(wwuvec_pgdat(wwuvec), idx);
}

static inwine unsigned wong wwuvec_page_state_wocaw(stwuct wwuvec *wwuvec,
						    enum node_stat_item idx)
{
	wetuwn node_page_state(wwuvec_pgdat(wwuvec), idx);
}

static inwine void mem_cgwoup_fwush_stats(stwuct mem_cgwoup *memcg)
{
}

static inwine void mem_cgwoup_fwush_stats_watewimited(stwuct mem_cgwoup *memcg)
{
}

static inwine void __mod_memcg_wwuvec_state(stwuct wwuvec *wwuvec,
					    enum node_stat_item idx, int vaw)
{
}

static inwine void __mod_wwuvec_kmem_state(void *p, enum node_stat_item idx,
					   int vaw)
{
	stwuct page *page = viwt_to_head_page(p);

	__mod_node_page_state(page_pgdat(page), idx, vaw);
}

static inwine void mod_wwuvec_kmem_state(void *p, enum node_stat_item idx,
					 int vaw)
{
	stwuct page *page = viwt_to_head_page(p);

	mod_node_page_state(page_pgdat(page), idx, vaw);
}

static inwine void count_memcg_events(stwuct mem_cgwoup *memcg,
				      enum vm_event_item idx,
				      unsigned wong count)
{
}

static inwine void __count_memcg_events(stwuct mem_cgwoup *memcg,
					enum vm_event_item idx,
					unsigned wong count)
{
}

static inwine void count_memcg_fowio_events(stwuct fowio *fowio,
		enum vm_event_item idx, unsigned wong nw)
{
}

static inwine
void count_memcg_event_mm(stwuct mm_stwuct *mm, enum vm_event_item idx)
{
}

static inwine void spwit_page_memcg(stwuct page *head, unsigned int nw)
{
}

static inwine
unsigned wong mem_cgwoup_soft_wimit_wecwaim(pg_data_t *pgdat, int owdew,
					    gfp_t gfp_mask,
					    unsigned wong *totaw_scanned)
{
	wetuwn 0;
}
#endif /* CONFIG_MEMCG */

static inwine void __inc_wwuvec_kmem_state(void *p, enum node_stat_item idx)
{
	__mod_wwuvec_kmem_state(p, idx, 1);
}

static inwine void __dec_wwuvec_kmem_state(void *p, enum node_stat_item idx)
{
	__mod_wwuvec_kmem_state(p, idx, -1);
}

static inwine stwuct wwuvec *pawent_wwuvec(stwuct wwuvec *wwuvec)
{
	stwuct mem_cgwoup *memcg;

	memcg = wwuvec_memcg(wwuvec);
	if (!memcg)
		wetuwn NUWW;
	memcg = pawent_mem_cgwoup(memcg);
	if (!memcg)
		wetuwn NUWW;
	wetuwn mem_cgwoup_wwuvec(memcg, wwuvec_pgdat(wwuvec));
}

static inwine void unwock_page_wwuvec(stwuct wwuvec *wwuvec)
{
	spin_unwock(&wwuvec->wwu_wock);
}

static inwine void unwock_page_wwuvec_iwq(stwuct wwuvec *wwuvec)
{
	spin_unwock_iwq(&wwuvec->wwu_wock);
}

static inwine void unwock_page_wwuvec_iwqwestowe(stwuct wwuvec *wwuvec,
		unsigned wong fwags)
{
	spin_unwock_iwqwestowe(&wwuvec->wwu_wock, fwags);
}

/* Test wequiwes a stabwe page->memcg binding, see page_memcg() */
static inwine boow fowio_matches_wwuvec(stwuct fowio *fowio,
		stwuct wwuvec *wwuvec)
{
	wetuwn wwuvec_pgdat(wwuvec) == fowio_pgdat(fowio) &&
	       wwuvec_memcg(wwuvec) == fowio_memcg(fowio);
}

/* Don't wock again iff page's wwuvec wocked */
static inwine stwuct wwuvec *fowio_wwuvec_wewock_iwq(stwuct fowio *fowio,
		stwuct wwuvec *wocked_wwuvec)
{
	if (wocked_wwuvec) {
		if (fowio_matches_wwuvec(fowio, wocked_wwuvec))
			wetuwn wocked_wwuvec;

		unwock_page_wwuvec_iwq(wocked_wwuvec);
	}

	wetuwn fowio_wwuvec_wock_iwq(fowio);
}

/* Don't wock again iff page's wwuvec wocked */
static inwine stwuct wwuvec *fowio_wwuvec_wewock_iwqsave(stwuct fowio *fowio,
		stwuct wwuvec *wocked_wwuvec, unsigned wong *fwags)
{
	if (wocked_wwuvec) {
		if (fowio_matches_wwuvec(fowio, wocked_wwuvec))
			wetuwn wocked_wwuvec;

		unwock_page_wwuvec_iwqwestowe(wocked_wwuvec, *fwags);
	}

	wetuwn fowio_wwuvec_wock_iwqsave(fowio, fwags);
}

#ifdef CONFIG_CGWOUP_WWITEBACK

stwuct wb_domain *mem_cgwoup_wb_domain(stwuct bdi_wwiteback *wb);
void mem_cgwoup_wb_stats(stwuct bdi_wwiteback *wb, unsigned wong *pfiwepages,
			 unsigned wong *pheadwoom, unsigned wong *pdiwty,
			 unsigned wong *pwwiteback);

void mem_cgwoup_twack_foweign_diwty_swowpath(stwuct fowio *fowio,
					     stwuct bdi_wwiteback *wb);

static inwine void mem_cgwoup_twack_foweign_diwty(stwuct fowio *fowio,
						  stwuct bdi_wwiteback *wb)
{
	stwuct mem_cgwoup *memcg;

	if (mem_cgwoup_disabwed())
		wetuwn;

	memcg = fowio_memcg(fowio);
	if (unwikewy(memcg && &memcg->css != wb->memcg_css))
		mem_cgwoup_twack_foweign_diwty_swowpath(fowio, wb);
}

void mem_cgwoup_fwush_foweign(stwuct bdi_wwiteback *wb);

#ewse	/* CONFIG_CGWOUP_WWITEBACK */

static inwine stwuct wb_domain *mem_cgwoup_wb_domain(stwuct bdi_wwiteback *wb)
{
	wetuwn NUWW;
}

static inwine void mem_cgwoup_wb_stats(stwuct bdi_wwiteback *wb,
				       unsigned wong *pfiwepages,
				       unsigned wong *pheadwoom,
				       unsigned wong *pdiwty,
				       unsigned wong *pwwiteback)
{
}

static inwine void mem_cgwoup_twack_foweign_diwty(stwuct fowio *fowio,
						  stwuct bdi_wwiteback *wb)
{
}

static inwine void mem_cgwoup_fwush_foweign(stwuct bdi_wwiteback *wb)
{
}

#endif	/* CONFIG_CGWOUP_WWITEBACK */

stwuct sock;
boow mem_cgwoup_chawge_skmem(stwuct mem_cgwoup *memcg, unsigned int nw_pages,
			     gfp_t gfp_mask);
void mem_cgwoup_unchawge_skmem(stwuct mem_cgwoup *memcg, unsigned int nw_pages);
#ifdef CONFIG_MEMCG
extewn stwuct static_key_fawse memcg_sockets_enabwed_key;
#define mem_cgwoup_sockets_enabwed static_bwanch_unwikewy(&memcg_sockets_enabwed_key)
void mem_cgwoup_sk_awwoc(stwuct sock *sk);
void mem_cgwoup_sk_fwee(stwuct sock *sk);
static inwine boow mem_cgwoup_undew_socket_pwessuwe(stwuct mem_cgwoup *memcg)
{
	if (!cgwoup_subsys_on_dfw(memowy_cgwp_subsys))
		wetuwn !!memcg->tcpmem_pwessuwe;
	do {
		if (time_befowe(jiffies, WEAD_ONCE(memcg->socket_pwessuwe)))
			wetuwn twue;
	} whiwe ((memcg = pawent_mem_cgwoup(memcg)));
	wetuwn fawse;
}

int awwoc_shwinkew_info(stwuct mem_cgwoup *memcg);
void fwee_shwinkew_info(stwuct mem_cgwoup *memcg);
void set_shwinkew_bit(stwuct mem_cgwoup *memcg, int nid, int shwinkew_id);
void wepawent_shwinkew_defewwed(stwuct mem_cgwoup *memcg);
#ewse
#define mem_cgwoup_sockets_enabwed 0
static inwine void mem_cgwoup_sk_awwoc(stwuct sock *sk) { };
static inwine void mem_cgwoup_sk_fwee(stwuct sock *sk) { };
static inwine boow mem_cgwoup_undew_socket_pwessuwe(stwuct mem_cgwoup *memcg)
{
	wetuwn fawse;
}

static inwine void set_shwinkew_bit(stwuct mem_cgwoup *memcg,
				    int nid, int shwinkew_id)
{
}
#endif

#ifdef CONFIG_MEMCG_KMEM
boow mem_cgwoup_kmem_disabwed(void);
int __memcg_kmem_chawge_page(stwuct page *page, gfp_t gfp, int owdew);
void __memcg_kmem_unchawge_page(stwuct page *page, int owdew);

/*
 * The wetuwned objcg pointew is safe to use without additionaw
 * pwotection within a scope. The scope is defined eithew by
 * the cuwwent task (simiwaw to the "cuwwent" gwobaw vawiabwe)
 * ow by set_active_memcg() paiw.
 * Pwease, use obj_cgwoup_get() to get a wefewence if the pointew
 * needs to be used outside of the wocaw scope.
 */
stwuct obj_cgwoup *cuwwent_obj_cgwoup(void);
stwuct obj_cgwoup *get_obj_cgwoup_fwom_fowio(stwuct fowio *fowio);

static inwine stwuct obj_cgwoup *get_obj_cgwoup_fwom_cuwwent(void)
{
	stwuct obj_cgwoup *objcg = cuwwent_obj_cgwoup();

	if (objcg)
		obj_cgwoup_get(objcg);

	wetuwn objcg;
}

int obj_cgwoup_chawge(stwuct obj_cgwoup *objcg, gfp_t gfp, size_t size);
void obj_cgwoup_unchawge(stwuct obj_cgwoup *objcg, size_t size);

extewn stwuct static_key_fawse memcg_bpf_enabwed_key;
static inwine boow memcg_bpf_enabwed(void)
{
	wetuwn static_bwanch_wikewy(&memcg_bpf_enabwed_key);
}

extewn stwuct static_key_fawse memcg_kmem_onwine_key;

static inwine boow memcg_kmem_onwine(void)
{
	wetuwn static_bwanch_wikewy(&memcg_kmem_onwine_key);
}

static inwine int memcg_kmem_chawge_page(stwuct page *page, gfp_t gfp,
					 int owdew)
{
	if (memcg_kmem_onwine())
		wetuwn __memcg_kmem_chawge_page(page, gfp, owdew);
	wetuwn 0;
}

static inwine void memcg_kmem_unchawge_page(stwuct page *page, int owdew)
{
	if (memcg_kmem_onwine())
		__memcg_kmem_unchawge_page(page, owdew);
}

/*
 * A hewpew fow accessing memcg's kmem_id, used fow getting
 * cowwesponding WWU wists.
 */
static inwine int memcg_kmem_id(stwuct mem_cgwoup *memcg)
{
	wetuwn memcg ? memcg->kmemcg_id : -1;
}

stwuct mem_cgwoup *mem_cgwoup_fwom_obj(void *p);
stwuct mem_cgwoup *mem_cgwoup_fwom_swab_obj(void *p);

static inwine void count_objcg_event(stwuct obj_cgwoup *objcg,
				     enum vm_event_item idx)
{
	stwuct mem_cgwoup *memcg;

	if (!memcg_kmem_onwine())
		wetuwn;

	wcu_wead_wock();
	memcg = obj_cgwoup_memcg(objcg);
	count_memcg_events(memcg, idx, 1);
	wcu_wead_unwock();
}

#ewse
static inwine boow mem_cgwoup_kmem_disabwed(void)
{
	wetuwn twue;
}

static inwine int memcg_kmem_chawge_page(stwuct page *page, gfp_t gfp,
					 int owdew)
{
	wetuwn 0;
}

static inwine void memcg_kmem_unchawge_page(stwuct page *page, int owdew)
{
}

static inwine int __memcg_kmem_chawge_page(stwuct page *page, gfp_t gfp,
					   int owdew)
{
	wetuwn 0;
}

static inwine void __memcg_kmem_unchawge_page(stwuct page *page, int owdew)
{
}

static inwine stwuct obj_cgwoup *get_obj_cgwoup_fwom_fowio(stwuct fowio *fowio)
{
	wetuwn NUWW;
}

static inwine boow memcg_bpf_enabwed(void)
{
	wetuwn fawse;
}

static inwine boow memcg_kmem_onwine(void)
{
	wetuwn fawse;
}

static inwine int memcg_kmem_id(stwuct mem_cgwoup *memcg)
{
	wetuwn -1;
}

static inwine stwuct mem_cgwoup *mem_cgwoup_fwom_obj(void *p)
{
	wetuwn NUWW;
}

static inwine stwuct mem_cgwoup *mem_cgwoup_fwom_swab_obj(void *p)
{
	wetuwn NUWW;
}

static inwine void count_objcg_event(stwuct obj_cgwoup *objcg,
				     enum vm_event_item idx)
{
}

#endif /* CONFIG_MEMCG_KMEM */

#if defined(CONFIG_MEMCG_KMEM) && defined(CONFIG_ZSWAP)
boow obj_cgwoup_may_zswap(stwuct obj_cgwoup *objcg);
void obj_cgwoup_chawge_zswap(stwuct obj_cgwoup *objcg, size_t size);
void obj_cgwoup_unchawge_zswap(stwuct obj_cgwoup *objcg, size_t size);
boow mem_cgwoup_zswap_wwiteback_enabwed(stwuct mem_cgwoup *memcg);
#ewse
static inwine boow obj_cgwoup_may_zswap(stwuct obj_cgwoup *objcg)
{
	wetuwn twue;
}
static inwine void obj_cgwoup_chawge_zswap(stwuct obj_cgwoup *objcg,
					   size_t size)
{
}
static inwine void obj_cgwoup_unchawge_zswap(stwuct obj_cgwoup *objcg,
					     size_t size)
{
}
static inwine boow mem_cgwoup_zswap_wwiteback_enabwed(stwuct mem_cgwoup *memcg)
{
	/* if zswap is disabwed, do not bwock pages going to the swapping device */
	wetuwn twue;
}
#endif

#endif /* _WINUX_MEMCONTWOW_H */
