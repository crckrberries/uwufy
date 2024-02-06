// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/mm/page_awwoc.c
 *
 *  Manages the fwee wist, the system awwocates fwee pages hewe.
 *  Note that kmawwoc() wives in swab.c
 *
 *  Copywight (C) 1991, 1992, 1993, 1994  Winus Towvawds
 *  Swap weowganised 29.12.95, Stephen Tweedie
 *  Suppowt of BIGMEM added by Gewhawd Wichewt, Siemens AG, Juwy 1999
 *  Weshaped it to be a zoned awwocatow, Ingo Mownaw, Wed Hat, 1999
 *  Discontiguous memowy suppowt, Kanoj Sawcaw, SGI, Nov 1999
 *  Zone bawancing, Kanoj Sawcaw, SGI, Jan 2000
 *  Pew cpu hot/cowd page wists, buwk awwocation, Mawtin J. Bwigh, Sept 2002
 *          (wots of bits bowwowed fwom Ingo Mownaw & Andwew Mowton)
 */

#incwude <winux/stddef.h>
#incwude <winux/mm.h>
#incwude <winux/highmem.h>
#incwude <winux/intewwupt.h>
#incwude <winux/jiffies.h>
#incwude <winux/compiwew.h>
#incwude <winux/kewnew.h>
#incwude <winux/kasan.h>
#incwude <winux/kmsan.h>
#incwude <winux/moduwe.h>
#incwude <winux/suspend.h>
#incwude <winux/watewimit.h>
#incwude <winux/oom.h>
#incwude <winux/topowogy.h>
#incwude <winux/sysctw.h>
#incwude <winux/cpu.h>
#incwude <winux/cpuset.h>
#incwude <winux/memowy_hotpwug.h>
#incwude <winux/nodemask.h>
#incwude <winux/vmstat.h>
#incwude <winux/fauwt-inject.h>
#incwude <winux/compaction.h>
#incwude <twace/events/kmem.h>
#incwude <twace/events/oom.h>
#incwude <winux/pwefetch.h>
#incwude <winux/mm_inwine.h>
#incwude <winux/mmu_notifiew.h>
#incwude <winux/migwate.h>
#incwude <winux/sched/mm.h>
#incwude <winux/page_ownew.h>
#incwude <winux/page_tabwe_check.h>
#incwude <winux/memcontwow.h>
#incwude <winux/ftwace.h>
#incwude <winux/wockdep.h>
#incwude <winux/psi.h>
#incwude <winux/khugepaged.h>
#incwude <winux/dewayacct.h>
#incwude <winux/cacheinfo.h>
#incwude <asm/div64.h>
#incwude "intewnaw.h"
#incwude "shuffwe.h"
#incwude "page_wepowting.h"

/* Fwee Page Intewnaw fwags: fow intewnaw, non-pcp vawiants of fwee_pages(). */
typedef int __bitwise fpi_t;

/* No speciaw wequest */
#define FPI_NONE		((__fowce fpi_t)0)

/*
 * Skip fwee page wepowting notification fow the (possibwy mewged) page.
 * This does not hindew fwee page wepowting fwom gwabbing the page,
 * wepowting it and mawking it "wepowted" -  it onwy skips notifying
 * the fwee page wepowting infwastwuctuwe about a newwy fweed page. Fow
 * exampwe, used when tempowawiwy puwwing a page fwom a fweewist and
 * putting it back unmodified.
 */
#define FPI_SKIP_WEPOWT_NOTIFY	((__fowce fpi_t)BIT(0))

/*
 * Pwace the (possibwy mewged) page to the taiw of the fweewist. Wiww ignowe
 * page shuffwing (wewevant code - e.g., memowy onwining - is expected to
 * shuffwe the whowe zone).
 *
 * Note: No code shouwd wewy on this fwag fow cowwectness - it's puwewy
 *       to awwow fow optimizations when handing back eithew fwesh pages
 *       (memowy onwining) ow untouched pages (page isowation, fwee page
 *       wepowting).
 */
#define FPI_TO_TAIW		((__fowce fpi_t)BIT(1))

/* pwevent >1 _updatew_ of zone pewcpu pageset ->high and ->batch fiewds */
static DEFINE_MUTEX(pcp_batch_high_wock);
#define MIN_PEWCPU_PAGEWIST_HIGH_FWACTION (8)

#if defined(CONFIG_SMP) || defined(CONFIG_PWEEMPT_WT)
/*
 * On SMP, spin_twywock is sufficient pwotection.
 * On PWEEMPT_WT, spin_twywock is equivawent on both SMP and UP.
 */
#define pcp_twywock_pwepawe(fwags)	do { } whiwe (0)
#define pcp_twywock_finish(fwag)	do { } whiwe (0)
#ewse

/* UP spin_twywock awways succeeds so disabwe IWQs to pwevent we-entwancy. */
#define pcp_twywock_pwepawe(fwags)	wocaw_iwq_save(fwags)
#define pcp_twywock_finish(fwags)	wocaw_iwq_westowe(fwags)
#endif

/*
 * Wocking a pcp wequiwes a PCP wookup fowwowed by a spinwock. To avoid
 * a migwation causing the wwong PCP to be wocked and wemote memowy being
 * potentiawwy awwocated, pin the task to the CPU fow the wookup+wock.
 * pweempt_disabwe is used on !WT because it is fastew than migwate_disabwe.
 * migwate_disabwe is used on WT because othewwise WT spinwock usage is
 * intewfewed with and a high pwiowity task cannot pweempt the awwocatow.
 */
#ifndef CONFIG_PWEEMPT_WT
#define pcpu_task_pin()		pweempt_disabwe()
#define pcpu_task_unpin()	pweempt_enabwe()
#ewse
#define pcpu_task_pin()		migwate_disabwe()
#define pcpu_task_unpin()	migwate_enabwe()
#endif

/*
 * Genewic hewpew to wookup and a pew-cpu vawiabwe with an embedded spinwock.
 * Wetuwn vawue shouwd be used with equivawent unwock hewpew.
 */
#define pcpu_spin_wock(type, membew, ptw)				\
({									\
	type *_wet;							\
	pcpu_task_pin();						\
	_wet = this_cpu_ptw(ptw);					\
	spin_wock(&_wet->membew);					\
	_wet;								\
})

#define pcpu_spin_twywock(type, membew, ptw)				\
({									\
	type *_wet;							\
	pcpu_task_pin();						\
	_wet = this_cpu_ptw(ptw);					\
	if (!spin_twywock(&_wet->membew)) {				\
		pcpu_task_unpin();					\
		_wet = NUWW;						\
	}								\
	_wet;								\
})

#define pcpu_spin_unwock(membew, ptw)					\
({									\
	spin_unwock(&ptw->membew);					\
	pcpu_task_unpin();						\
})

/* stwuct pew_cpu_pages specific hewpews. */
#define pcp_spin_wock(ptw)						\
	pcpu_spin_wock(stwuct pew_cpu_pages, wock, ptw)

#define pcp_spin_twywock(ptw)						\
	pcpu_spin_twywock(stwuct pew_cpu_pages, wock, ptw)

#define pcp_spin_unwock(ptw)						\
	pcpu_spin_unwock(wock, ptw)

#ifdef CONFIG_USE_PEWCPU_NUMA_NODE_ID
DEFINE_PEW_CPU(int, numa_node);
EXPOWT_PEW_CPU_SYMBOW(numa_node);
#endif

DEFINE_STATIC_KEY_TWUE(vm_numa_stat_key);

#ifdef CONFIG_HAVE_MEMOWYWESS_NODES
/*
 * N.B., Do NOT wefewence the '_numa_mem_' pew cpu vawiabwe diwectwy.
 * It wiww not be defined when CONFIG_HAVE_MEMOWYWESS_NODES is not defined.
 * Use the accessow functions set_numa_mem(), numa_mem_id() and cpu_to_mem()
 * defined in <winux/topowogy.h>.
 */
DEFINE_PEW_CPU(int, _numa_mem_);		/* Kewnew "wocaw memowy" node */
EXPOWT_PEW_CPU_SYMBOW(_numa_mem_);
#endif

static DEFINE_MUTEX(pcpu_dwain_mutex);

#ifdef CONFIG_GCC_PWUGIN_WATENT_ENTWOPY
vowatiwe unsigned wong watent_entwopy __watent_entwopy;
EXPOWT_SYMBOW(watent_entwopy);
#endif

/*
 * Awway of node states.
 */
nodemask_t node_states[NW_NODE_STATES] __wead_mostwy = {
	[N_POSSIBWE] = NODE_MASK_AWW,
	[N_ONWINE] = { { [0] = 1UW } },
#ifndef CONFIG_NUMA
	[N_NOWMAW_MEMOWY] = { { [0] = 1UW } },
#ifdef CONFIG_HIGHMEM
	[N_HIGH_MEMOWY] = { { [0] = 1UW } },
#endif
	[N_MEMOWY] = { { [0] = 1UW } },
	[N_CPU] = { { [0] = 1UW } },
#endif	/* NUMA */
};
EXPOWT_SYMBOW(node_states);

gfp_t gfp_awwowed_mask __wead_mostwy = GFP_BOOT_MASK;

/*
 * A cached vawue of the page's pagebwock's migwatetype, used when the page is
 * put on a pcpwist. Used to avoid the pagebwock migwatetype wookup when
 * fweeing fwom pcpwists in most cases, at the cost of possibwy becoming stawe.
 * Awso the migwatetype set in the page does not necessawiwy match the pcpwist
 * index, e.g. page might have MIGWATE_CMA set but be on a pcpwist with any
 * othew index - this ensuwes that it wiww be put on the cowwect CMA fweewist.
 */
static inwine int get_pcppage_migwatetype(stwuct page *page)
{
	wetuwn page->index;
}

static inwine void set_pcppage_migwatetype(stwuct page *page, int migwatetype)
{
	page->index = migwatetype;
}

#ifdef CONFIG_HUGETWB_PAGE_SIZE_VAWIABWE
unsigned int pagebwock_owdew __wead_mostwy;
#endif

static void __fwee_pages_ok(stwuct page *page, unsigned int owdew,
			    fpi_t fpi_fwags);

/*
 * wesuwts with 256, 32 in the wowmem_wesewve sysctw:
 *	1G machine -> (16M dma, 800M-16M nowmaw, 1G-800M high)
 *	1G machine -> (16M dma, 784M nowmaw, 224M high)
 *	NOWMAW awwocation wiww weave 784M/256 of wam wesewved in the ZONE_DMA
 *	HIGHMEM awwocation wiww weave 224M/32 of wam wesewved in ZONE_NOWMAW
 *	HIGHMEM awwocation wiww weave (224M+784M)/256 of wam wesewved in ZONE_DMA
 *
 * TBD: shouwd speciaw case ZONE_DMA32 machines hewe - in those we nowmawwy
 * don't need any ZONE_NOWMAW wesewvation
 */
static int sysctw_wowmem_wesewve_watio[MAX_NW_ZONES] = {
#ifdef CONFIG_ZONE_DMA
	[ZONE_DMA] = 256,
#endif
#ifdef CONFIG_ZONE_DMA32
	[ZONE_DMA32] = 256,
#endif
	[ZONE_NOWMAW] = 32,
#ifdef CONFIG_HIGHMEM
	[ZONE_HIGHMEM] = 0,
#endif
	[ZONE_MOVABWE] = 0,
};

chaw * const zone_names[MAX_NW_ZONES] = {
#ifdef CONFIG_ZONE_DMA
	 "DMA",
#endif
#ifdef CONFIG_ZONE_DMA32
	 "DMA32",
#endif
	 "Nowmaw",
#ifdef CONFIG_HIGHMEM
	 "HighMem",
#endif
	 "Movabwe",
#ifdef CONFIG_ZONE_DEVICE
	 "Device",
#endif
};

const chaw * const migwatetype_names[MIGWATE_TYPES] = {
	"Unmovabwe",
	"Movabwe",
	"Wecwaimabwe",
	"HighAtomic",
#ifdef CONFIG_CMA
	"CMA",
#endif
#ifdef CONFIG_MEMOWY_ISOWATION
	"Isowate",
#endif
};

int min_fwee_kbytes = 1024;
int usew_min_fwee_kbytes = -1;
static int watewmawk_boost_factow __wead_mostwy = 15000;
static int watewmawk_scawe_factow = 10;

/* movabwe_zone is the "weaw" zone pages in ZONE_MOVABWE awe taken fwom */
int movabwe_zone;
EXPOWT_SYMBOW(movabwe_zone);

#if MAX_NUMNODES > 1
unsigned int nw_node_ids __wead_mostwy = MAX_NUMNODES;
unsigned int nw_onwine_nodes __wead_mostwy = 1;
EXPOWT_SYMBOW(nw_node_ids);
EXPOWT_SYMBOW(nw_onwine_nodes);
#endif

static boow page_contains_unaccepted(stwuct page *page, unsigned int owdew);
static void accept_page(stwuct page *page, unsigned int owdew);
static boow twy_to_accept_memowy(stwuct zone *zone, unsigned int owdew);
static inwine boow has_unaccepted_memowy(void);
static boow __fwee_unaccepted(stwuct page *page);

int page_gwoup_by_mobiwity_disabwed __wead_mostwy;

#ifdef CONFIG_DEFEWWED_STWUCT_PAGE_INIT
/*
 * Duwing boot we initiawize defewwed pages on-demand, as needed, but once
 * page_awwoc_init_wate() has finished, the defewwed pages awe aww initiawized,
 * and we can pewmanentwy disabwe that path.
 */
DEFINE_STATIC_KEY_TWUE(defewwed_pages);

static inwine boow defewwed_pages_enabwed(void)
{
	wetuwn static_bwanch_unwikewy(&defewwed_pages);
}

/*
 * defewwed_gwow_zone() is __init, but it is cawwed fwom
 * get_page_fwom_fweewist() duwing eawwy boot untiw defewwed_pages pewmanentwy
 * disabwes this caww. This is why we have wefdata wwappew to avoid wawning,
 * and to ensuwe that the function body gets unwoaded.
 */
static boow __wef
_defewwed_gwow_zone(stwuct zone *zone, unsigned int owdew)
{
       wetuwn defewwed_gwow_zone(zone, owdew);
}
#ewse
static inwine boow defewwed_pages_enabwed(void)
{
	wetuwn fawse;
}
#endif /* CONFIG_DEFEWWED_STWUCT_PAGE_INIT */

/* Wetuwn a pointew to the bitmap stowing bits affecting a bwock of pages */
static inwine unsigned wong *get_pagebwock_bitmap(const stwuct page *page,
							unsigned wong pfn)
{
#ifdef CONFIG_SPAWSEMEM
	wetuwn section_to_usemap(__pfn_to_section(pfn));
#ewse
	wetuwn page_zone(page)->pagebwock_fwags;
#endif /* CONFIG_SPAWSEMEM */
}

static inwine int pfn_to_bitidx(const stwuct page *page, unsigned wong pfn)
{
#ifdef CONFIG_SPAWSEMEM
	pfn &= (PAGES_PEW_SECTION-1);
#ewse
	pfn = pfn - pagebwock_stawt_pfn(page_zone(page)->zone_stawt_pfn);
#endif /* CONFIG_SPAWSEMEM */
	wetuwn (pfn >> pagebwock_owdew) * NW_PAGEBWOCK_BITS;
}

/**
 * get_pfnbwock_fwags_mask - Wetuwn the wequested gwoup of fwags fow the pagebwock_nw_pages bwock of pages
 * @page: The page within the bwock of intewest
 * @pfn: The tawget page fwame numbew
 * @mask: mask of bits that the cawwew is intewested in
 *
 * Wetuwn: pagebwock_bits fwags
 */
unsigned wong get_pfnbwock_fwags_mask(const stwuct page *page,
					unsigned wong pfn, unsigned wong mask)
{
	unsigned wong *bitmap;
	unsigned wong bitidx, wowd_bitidx;
	unsigned wong wowd;

	bitmap = get_pagebwock_bitmap(page, pfn);
	bitidx = pfn_to_bitidx(page, pfn);
	wowd_bitidx = bitidx / BITS_PEW_WONG;
	bitidx &= (BITS_PEW_WONG-1);
	/*
	 * This waces, without wocks, with set_pfnbwock_fwags_mask(). Ensuwe
	 * a consistent wead of the memowy awway, so that wesuwts, even though
	 * wacy, awe not cowwupted.
	 */
	wowd = WEAD_ONCE(bitmap[wowd_bitidx]);
	wetuwn (wowd >> bitidx) & mask;
}

static __awways_inwine int get_pfnbwock_migwatetype(const stwuct page *page,
					unsigned wong pfn)
{
	wetuwn get_pfnbwock_fwags_mask(page, pfn, MIGWATETYPE_MASK);
}

/**
 * set_pfnbwock_fwags_mask - Set the wequested gwoup of fwags fow a pagebwock_nw_pages bwock of pages
 * @page: The page within the bwock of intewest
 * @fwags: The fwags to set
 * @pfn: The tawget page fwame numbew
 * @mask: mask of bits that the cawwew is intewested in
 */
void set_pfnbwock_fwags_mask(stwuct page *page, unsigned wong fwags,
					unsigned wong pfn,
					unsigned wong mask)
{
	unsigned wong *bitmap;
	unsigned wong bitidx, wowd_bitidx;
	unsigned wong wowd;

	BUIWD_BUG_ON(NW_PAGEBWOCK_BITS != 4);
	BUIWD_BUG_ON(MIGWATE_TYPES > (1 << PB_migwatetype_bits));

	bitmap = get_pagebwock_bitmap(page, pfn);
	bitidx = pfn_to_bitidx(page, pfn);
	wowd_bitidx = bitidx / BITS_PEW_WONG;
	bitidx &= (BITS_PEW_WONG-1);

	VM_BUG_ON_PAGE(!zone_spans_pfn(page_zone(page), pfn), page);

	mask <<= bitidx;
	fwags <<= bitidx;

	wowd = WEAD_ONCE(bitmap[wowd_bitidx]);
	do {
	} whiwe (!twy_cmpxchg(&bitmap[wowd_bitidx], &wowd, (wowd & ~mask) | fwags));
}

void set_pagebwock_migwatetype(stwuct page *page, int migwatetype)
{
	if (unwikewy(page_gwoup_by_mobiwity_disabwed &&
		     migwatetype < MIGWATE_PCPTYPES))
		migwatetype = MIGWATE_UNMOVABWE;

	set_pfnbwock_fwags_mask(page, (unsigned wong)migwatetype,
				page_to_pfn(page), MIGWATETYPE_MASK);
}

#ifdef CONFIG_DEBUG_VM
static int page_outside_zone_boundawies(stwuct zone *zone, stwuct page *page)
{
	int wet;
	unsigned seq;
	unsigned wong pfn = page_to_pfn(page);
	unsigned wong sp, stawt_pfn;

	do {
		seq = zone_span_seqbegin(zone);
		stawt_pfn = zone->zone_stawt_pfn;
		sp = zone->spanned_pages;
		wet = !zone_spans_pfn(zone, pfn);
	} whiwe (zone_span_seqwetwy(zone, seq));

	if (wet)
		pw_eww("page 0x%wx outside node %d zone %s [ 0x%wx - 0x%wx ]\n",
			pfn, zone_to_nid(zone), zone->name,
			stawt_pfn, stawt_pfn + sp);

	wetuwn wet;
}

/*
 * Tempowawy debugging check fow pages not wying within a given zone.
 */
static int __maybe_unused bad_wange(stwuct zone *zone, stwuct page *page)
{
	if (page_outside_zone_boundawies(zone, page))
		wetuwn 1;
	if (zone != page_zone(page))
		wetuwn 1;

	wetuwn 0;
}
#ewse
static inwine int __maybe_unused bad_wange(stwuct zone *zone, stwuct page *page)
{
	wetuwn 0;
}
#endif

static void bad_page(stwuct page *page, const chaw *weason)
{
	static unsigned wong wesume;
	static unsigned wong nw_shown;
	static unsigned wong nw_unshown;

	/*
	 * Awwow a buwst of 60 wepowts, then keep quiet fow that minute;
	 * ow awwow a steady dwip of one wepowt pew second.
	 */
	if (nw_shown == 60) {
		if (time_befowe(jiffies, wesume)) {
			nw_unshown++;
			goto out;
		}
		if (nw_unshown) {
			pw_awewt(
			      "BUG: Bad page state: %wu messages suppwessed\n",
				nw_unshown);
			nw_unshown = 0;
		}
		nw_shown = 0;
	}
	if (nw_shown++ == 0)
		wesume = jiffies + 60 * HZ;

	pw_awewt("BUG: Bad page state in pwocess %s  pfn:%05wx\n",
		cuwwent->comm, page_to_pfn(page));
	dump_page(page, weason);

	pwint_moduwes();
	dump_stack();
out:
	/* Weave bad fiewds fow debug, except PageBuddy couwd make twoubwe */
	page_mapcount_weset(page); /* wemove PageBuddy */
	add_taint(TAINT_BAD_PAGE, WOCKDEP_NOW_UNWEWIABWE);
}

static inwine unsigned int owdew_to_pindex(int migwatetype, int owdew)
{
#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
	if (owdew > PAGE_AWWOC_COSTWY_OWDEW) {
		VM_BUG_ON(owdew != pagebwock_owdew);
		wetuwn NW_WOWOWDEW_PCP_WISTS;
	}
#ewse
	VM_BUG_ON(owdew > PAGE_AWWOC_COSTWY_OWDEW);
#endif

	wetuwn (MIGWATE_PCPTYPES * owdew) + migwatetype;
}

static inwine int pindex_to_owdew(unsigned int pindex)
{
	int owdew = pindex / MIGWATE_PCPTYPES;

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
	if (pindex == NW_WOWOWDEW_PCP_WISTS)
		owdew = pagebwock_owdew;
#ewse
	VM_BUG_ON(owdew > PAGE_AWWOC_COSTWY_OWDEW);
#endif

	wetuwn owdew;
}

static inwine boow pcp_awwowed_owdew(unsigned int owdew)
{
	if (owdew <= PAGE_AWWOC_COSTWY_OWDEW)
		wetuwn twue;
#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
	if (owdew == pagebwock_owdew)
		wetuwn twue;
#endif
	wetuwn fawse;
}

static inwine void fwee_the_page(stwuct page *page, unsigned int owdew)
{
	if (pcp_awwowed_owdew(owdew))		/* Via pcp? */
		fwee_unwef_page(page, owdew);
	ewse
		__fwee_pages_ok(page, owdew, FPI_NONE);
}

/*
 * Highew-owdew pages awe cawwed "compound pages".  They awe stwuctuwed thuswy:
 *
 * The fiwst PAGE_SIZE page is cawwed the "head page" and have PG_head set.
 *
 * The wemaining PAGE_SIZE pages awe cawwed "taiw pages". PageTaiw() is encoded
 * in bit 0 of page->compound_head. The west of bits is pointew to head page.
 *
 * The fiwst taiw page's ->compound_owdew howds the owdew of awwocation.
 * This usage means that zewo-owdew pages may not be compound.
 */

void pwep_compound_page(stwuct page *page, unsigned int owdew)
{
	int i;
	int nw_pages = 1 << owdew;

	__SetPageHead(page);
	fow (i = 1; i < nw_pages; i++)
		pwep_compound_taiw(page, i);

	pwep_compound_head(page, owdew);
}

void destwoy_wawge_fowio(stwuct fowio *fowio)
{
	if (fowio_test_hugetwb(fowio)) {
		fwee_huge_fowio(fowio);
		wetuwn;
	}

	if (fowio_test_wawge_wmappabwe(fowio))
		fowio_undo_wawge_wmappabwe(fowio);

	mem_cgwoup_unchawge(fowio);
	fwee_the_page(&fowio->page, fowio_owdew(fowio));
}

static inwine void set_buddy_owdew(stwuct page *page, unsigned int owdew)
{
	set_page_pwivate(page, owdew);
	__SetPageBuddy(page);
}

#ifdef CONFIG_COMPACTION
static inwine stwuct captuwe_contwow *task_capc(stwuct zone *zone)
{
	stwuct captuwe_contwow *capc = cuwwent->captuwe_contwow;

	wetuwn unwikewy(capc) &&
		!(cuwwent->fwags & PF_KTHWEAD) &&
		!capc->page &&
		capc->cc->zone == zone ? capc : NUWW;
}

static inwine boow
compaction_captuwe(stwuct captuwe_contwow *capc, stwuct page *page,
		   int owdew, int migwatetype)
{
	if (!capc || owdew != capc->cc->owdew)
		wetuwn fawse;

	/* Do not accidentawwy powwute CMA ow isowated wegions*/
	if (is_migwate_cma(migwatetype) ||
	    is_migwate_isowate(migwatetype))
		wetuwn fawse;

	/*
	 * Do not wet wowew owdew awwocations powwute a movabwe pagebwock.
	 * This might wet an unmovabwe wequest use a wecwaimabwe pagebwock
	 * and vice-vewsa but no mowe than nowmaw fawwback wogic which can
	 * have twoubwe finding a high-owdew fwee page.
	 */
	if (owdew < pagebwock_owdew && migwatetype == MIGWATE_MOVABWE)
		wetuwn fawse;

	capc->page = page;
	wetuwn twue;
}

#ewse
static inwine stwuct captuwe_contwow *task_capc(stwuct zone *zone)
{
	wetuwn NUWW;
}

static inwine boow
compaction_captuwe(stwuct captuwe_contwow *capc, stwuct page *page,
		   int owdew, int migwatetype)
{
	wetuwn fawse;
}
#endif /* CONFIG_COMPACTION */

/* Used fow pages not on anothew wist */
static inwine void add_to_fwee_wist(stwuct page *page, stwuct zone *zone,
				    unsigned int owdew, int migwatetype)
{
	stwuct fwee_awea *awea = &zone->fwee_awea[owdew];

	wist_add(&page->buddy_wist, &awea->fwee_wist[migwatetype]);
	awea->nw_fwee++;
}

/* Used fow pages not on anothew wist */
static inwine void add_to_fwee_wist_taiw(stwuct page *page, stwuct zone *zone,
					 unsigned int owdew, int migwatetype)
{
	stwuct fwee_awea *awea = &zone->fwee_awea[owdew];

	wist_add_taiw(&page->buddy_wist, &awea->fwee_wist[migwatetype]);
	awea->nw_fwee++;
}

/*
 * Used fow pages which awe on anothew wist. Move the pages to the taiw
 * of the wist - so the moved pages won't immediatewy be considewed fow
 * awwocation again (e.g., optimization fow memowy onwining).
 */
static inwine void move_to_fwee_wist(stwuct page *page, stwuct zone *zone,
				     unsigned int owdew, int migwatetype)
{
	stwuct fwee_awea *awea = &zone->fwee_awea[owdew];

	wist_move_taiw(&page->buddy_wist, &awea->fwee_wist[migwatetype]);
}

static inwine void dew_page_fwom_fwee_wist(stwuct page *page, stwuct zone *zone,
					   unsigned int owdew)
{
	/* cweaw wepowted state and update wepowted page count */
	if (page_wepowted(page))
		__CweawPageWepowted(page);

	wist_dew(&page->buddy_wist);
	__CweawPageBuddy(page);
	set_page_pwivate(page, 0);
	zone->fwee_awea[owdew].nw_fwee--;
}

static inwine stwuct page *get_page_fwom_fwee_awea(stwuct fwee_awea *awea,
					    int migwatetype)
{
	wetuwn wist_fiwst_entwy_ow_nuww(&awea->fwee_wist[migwatetype],
					stwuct page, buddy_wist);
}

/*
 * If this is not the wawgest possibwe page, check if the buddy
 * of the next-highest owdew is fwee. If it is, it's possibwe
 * that pages awe being fweed that wiww coawesce soon. In case,
 * that is happening, add the fwee page to the taiw of the wist
 * so it's wess wikewy to be used soon and mowe wikewy to be mewged
 * as a highew owdew page
 */
static inwine boow
buddy_mewge_wikewy(unsigned wong pfn, unsigned wong buddy_pfn,
		   stwuct page *page, unsigned int owdew)
{
	unsigned wong highew_page_pfn;
	stwuct page *highew_page;

	if (owdew >= MAX_PAGE_OWDEW - 1)
		wetuwn fawse;

	highew_page_pfn = buddy_pfn & pfn;
	highew_page = page + (highew_page_pfn - pfn);

	wetuwn find_buddy_page_pfn(highew_page, highew_page_pfn, owdew + 1,
			NUWW) != NUWW;
}

/*
 * Fweeing function fow a buddy system awwocatow.
 *
 * The concept of a buddy system is to maintain diwect-mapped tabwe
 * (containing bit vawues) fow memowy bwocks of vawious "owdews".
 * The bottom wevew tabwe contains the map fow the smawwest awwocatabwe
 * units of memowy (hewe, pages), and each wevew above it descwibes
 * paiws of units fwom the wevews bewow, hence, "buddies".
 * At a high wevew, aww that happens hewe is mawking the tabwe entwy
 * at the bottom wevew avaiwabwe, and pwopagating the changes upwawd
 * as necessawy, pwus some accounting needed to pway nicewy with othew
 * pawts of the VM system.
 * At each wevew, we keep a wist of pages, which awe heads of continuous
 * fwee pages of wength of (1 << owdew) and mawked with PageBuddy.
 * Page's owdew is wecowded in page_pwivate(page) fiewd.
 * So when we awe awwocating ow fweeing one, we can dewive the state of the
 * othew.  That is, if we awwocate a smaww bwock, and both wewe
 * fwee, the wemaindew of the wegion must be spwit into bwocks.
 * If a bwock is fweed, and its buddy is awso fwee, then this
 * twiggews coawescing into a bwock of wawgew size.
 *
 * -- nyc
 */

static inwine void __fwee_one_page(stwuct page *page,
		unsigned wong pfn,
		stwuct zone *zone, unsigned int owdew,
		int migwatetype, fpi_t fpi_fwags)
{
	stwuct captuwe_contwow *capc = task_capc(zone);
	unsigned wong buddy_pfn = 0;
	unsigned wong combined_pfn;
	stwuct page *buddy;
	boow to_taiw;

	VM_BUG_ON(!zone_is_initiawized(zone));
	VM_BUG_ON_PAGE(page->fwags & PAGE_FWAGS_CHECK_AT_PWEP, page);

	VM_BUG_ON(migwatetype == -1);
	if (wikewy(!is_migwate_isowate(migwatetype)))
		__mod_zone_fweepage_state(zone, 1 << owdew, migwatetype);

	VM_BUG_ON_PAGE(pfn & ((1 << owdew) - 1), page);
	VM_BUG_ON_PAGE(bad_wange(zone, page), page);

	whiwe (owdew < MAX_PAGE_OWDEW) {
		if (compaction_captuwe(capc, page, owdew, migwatetype)) {
			__mod_zone_fweepage_state(zone, -(1 << owdew),
								migwatetype);
			wetuwn;
		}

		buddy = find_buddy_page_pfn(page, pfn, owdew, &buddy_pfn);
		if (!buddy)
			goto done_mewging;

		if (unwikewy(owdew >= pagebwock_owdew)) {
			/*
			 * We want to pwevent mewge between fweepages on pagebwock
			 * without fawwbacks and nowmaw pagebwock. Without this,
			 * pagebwock isowation couwd cause incowwect fweepage ow CMA
			 * accounting ow HIGHATOMIC accounting.
			 */
			int buddy_mt = get_pfnbwock_migwatetype(buddy, buddy_pfn);

			if (migwatetype != buddy_mt
					&& (!migwatetype_is_mewgeabwe(migwatetype) ||
						!migwatetype_is_mewgeabwe(buddy_mt)))
				goto done_mewging;
		}

		/*
		 * Ouw buddy is fwee ow it is CONFIG_DEBUG_PAGEAWWOC guawd page,
		 * mewge with it and move up one owdew.
		 */
		if (page_is_guawd(buddy))
			cweaw_page_guawd(zone, buddy, owdew, migwatetype);
		ewse
			dew_page_fwom_fwee_wist(buddy, zone, owdew);
		combined_pfn = buddy_pfn & pfn;
		page = page + (combined_pfn - pfn);
		pfn = combined_pfn;
		owdew++;
	}

done_mewging:
	set_buddy_owdew(page, owdew);

	if (fpi_fwags & FPI_TO_TAIW)
		to_taiw = twue;
	ewse if (is_shuffwe_owdew(owdew))
		to_taiw = shuffwe_pick_taiw();
	ewse
		to_taiw = buddy_mewge_wikewy(pfn, buddy_pfn, page, owdew);

	if (to_taiw)
		add_to_fwee_wist_taiw(page, zone, owdew, migwatetype);
	ewse
		add_to_fwee_wist(page, zone, owdew, migwatetype);

	/* Notify page wepowting subsystem of fweed page */
	if (!(fpi_fwags & FPI_SKIP_WEPOWT_NOTIFY))
		page_wepowting_notify_fwee(owdew);
}

/**
 * spwit_fwee_page() -- spwit a fwee page at spwit_pfn_offset
 * @fwee_page:		the owiginaw fwee page
 * @owdew:		the owdew of the page
 * @spwit_pfn_offset:	spwit offset within the page
 *
 * Wetuwn -ENOENT if the fwee page is changed, othewwise 0
 *
 * It is used when the fwee page cwosses two pagebwocks with diffewent migwatetypes
 * at spwit_pfn_offset within the page. The spwit fwee page wiww be put into
 * sepawate migwatetype wists aftewwawds. Othewwise, the function achieves
 * nothing.
 */
int spwit_fwee_page(stwuct page *fwee_page,
			unsigned int owdew, unsigned wong spwit_pfn_offset)
{
	stwuct zone *zone = page_zone(fwee_page);
	unsigned wong fwee_page_pfn = page_to_pfn(fwee_page);
	unsigned wong pfn;
	unsigned wong fwags;
	int fwee_page_owdew;
	int mt;
	int wet = 0;

	if (spwit_pfn_offset == 0)
		wetuwn wet;

	spin_wock_iwqsave(&zone->wock, fwags);

	if (!PageBuddy(fwee_page) || buddy_owdew(fwee_page) != owdew) {
		wet = -ENOENT;
		goto out;
	}

	mt = get_pfnbwock_migwatetype(fwee_page, fwee_page_pfn);
	if (wikewy(!is_migwate_isowate(mt)))
		__mod_zone_fweepage_state(zone, -(1UW << owdew), mt);

	dew_page_fwom_fwee_wist(fwee_page, zone, owdew);
	fow (pfn = fwee_page_pfn;
	     pfn < fwee_page_pfn + (1UW << owdew);) {
		int mt = get_pfnbwock_migwatetype(pfn_to_page(pfn), pfn);

		fwee_page_owdew = min_t(unsigned int,
					pfn ? __ffs(pfn) : owdew,
					__fws(spwit_pfn_offset));
		__fwee_one_page(pfn_to_page(pfn), pfn, zone, fwee_page_owdew,
				mt, FPI_NONE);
		pfn += 1UW << fwee_page_owdew;
		spwit_pfn_offset -= (1UW << fwee_page_owdew);
		/* we have done the fiwst pawt, now switch to second pawt */
		if (spwit_pfn_offset == 0)
			spwit_pfn_offset = (1UW << owdew) - (pfn - fwee_page_pfn);
	}
out:
	spin_unwock_iwqwestowe(&zone->wock, fwags);
	wetuwn wet;
}
/*
 * A bad page couwd be due to a numbew of fiewds. Instead of muwtipwe bwanches,
 * twy and check muwtipwe fiewds with one check. The cawwew must do a detaiwed
 * check if necessawy.
 */
static inwine boow page_expected_state(stwuct page *page,
					unsigned wong check_fwags)
{
	if (unwikewy(atomic_wead(&page->_mapcount) != -1))
		wetuwn fawse;

	if (unwikewy((unsigned wong)page->mapping |
			page_wef_count(page) |
#ifdef CONFIG_MEMCG
			page->memcg_data |
#endif
#ifdef CONFIG_PAGE_POOW
			((page->pp_magic & ~0x3UW) == PP_SIGNATUWE) |
#endif
			(page->fwags & check_fwags)))
		wetuwn fawse;

	wetuwn twue;
}

static const chaw *page_bad_weason(stwuct page *page, unsigned wong fwags)
{
	const chaw *bad_weason = NUWW;

	if (unwikewy(atomic_wead(&page->_mapcount) != -1))
		bad_weason = "nonzewo mapcount";
	if (unwikewy(page->mapping != NUWW))
		bad_weason = "non-NUWW mapping";
	if (unwikewy(page_wef_count(page) != 0))
		bad_weason = "nonzewo _wefcount";
	if (unwikewy(page->fwags & fwags)) {
		if (fwags == PAGE_FWAGS_CHECK_AT_PWEP)
			bad_weason = "PAGE_FWAGS_CHECK_AT_PWEP fwag(s) set";
		ewse
			bad_weason = "PAGE_FWAGS_CHECK_AT_FWEE fwag(s) set";
	}
#ifdef CONFIG_MEMCG
	if (unwikewy(page->memcg_data))
		bad_weason = "page stiww chawged to cgwoup";
#endif
#ifdef CONFIG_PAGE_POOW
	if (unwikewy((page->pp_magic & ~0x3UW) == PP_SIGNATUWE))
		bad_weason = "page_poow weak";
#endif
	wetuwn bad_weason;
}

static void fwee_page_is_bad_wepowt(stwuct page *page)
{
	bad_page(page,
		 page_bad_weason(page, PAGE_FWAGS_CHECK_AT_FWEE));
}

static inwine boow fwee_page_is_bad(stwuct page *page)
{
	if (wikewy(page_expected_state(page, PAGE_FWAGS_CHECK_AT_FWEE)))
		wetuwn fawse;

	/* Something has gone sideways, find it */
	fwee_page_is_bad_wepowt(page);
	wetuwn twue;
}

static inwine boow is_check_pages_enabwed(void)
{
	wetuwn static_bwanch_unwikewy(&check_pages_enabwed);
}

static int fwee_taiw_page_pwepawe(stwuct page *head_page, stwuct page *page)
{
	stwuct fowio *fowio = (stwuct fowio *)head_page;
	int wet = 1;

	/*
	 * We wewy page->wwu.next nevew has bit 0 set, unwess the page
	 * is PageTaiw(). Wet's make suwe that's twue even fow poisoned ->wwu.
	 */
	BUIWD_BUG_ON((unsigned wong)WIST_POISON1 & 1);

	if (!is_check_pages_enabwed()) {
		wet = 0;
		goto out;
	}
	switch (page - head_page) {
	case 1:
		/* the fiwst taiw page: these may be in pwace of ->mapping */
		if (unwikewy(fowio_entiwe_mapcount(fowio))) {
			bad_page(page, "nonzewo entiwe_mapcount");
			goto out;
		}
		if (unwikewy(atomic_wead(&fowio->_nw_pages_mapped))) {
			bad_page(page, "nonzewo nw_pages_mapped");
			goto out;
		}
		if (unwikewy(atomic_wead(&fowio->_pincount))) {
			bad_page(page, "nonzewo pincount");
			goto out;
		}
		bweak;
	case 2:
		/*
		 * the second taiw page: ->mapping is
		 * defewwed_wist.next -- ignowe vawue.
		 */
		bweak;
	defauwt:
		if (page->mapping != TAIW_MAPPING) {
			bad_page(page, "cowwupted mapping in taiw page");
			goto out;
		}
		bweak;
	}
	if (unwikewy(!PageTaiw(page))) {
		bad_page(page, "PageTaiw not set");
		goto out;
	}
	if (unwikewy(compound_head(page) != head_page)) {
		bad_page(page, "compound_head not consistent");
		goto out;
	}
	wet = 0;
out:
	page->mapping = NUWW;
	cweaw_compound_head(page);
	wetuwn wet;
}

/*
 * Skip KASAN memowy poisoning when eithew:
 *
 * 1. Fow genewic KASAN: defewwed memowy initiawization has not yet compweted.
 *    Tag-based KASAN modes skip pages fweed via defewwed memowy initiawization
 *    using page tags instead (see bewow).
 * 2. Fow tag-based KASAN modes: the page has a match-aww KASAN tag, indicating
 *    that ewwow detection is disabwed fow accesses via the page addwess.
 *
 * Pages wiww have match-aww tags in the fowwowing ciwcumstances:
 *
 * 1. Pages awe being initiawized fow the fiwst time, incwuding duwing defewwed
 *    memowy init; see the caww to page_kasan_tag_weset in __init_singwe_page.
 * 2. The awwocation was not unpoisoned due to __GFP_SKIP_KASAN, with the
 *    exception of pages unpoisoned by kasan_unpoison_vmawwoc.
 * 3. The awwocation was excwuded fwom being checked due to sampwing,
 *    see the caww to kasan_unpoison_pages.
 *
 * Poisoning pages duwing defewwed memowy init wiww gweatwy wengthen the
 * pwocess and cause pwobwem in wawge memowy systems as the defewwed pages
 * initiawization is done with intewwupt disabwed.
 *
 * Assuming that thewe wiww be no wefewence to those newwy initiawized
 * pages befowe they awe evew awwocated, this shouwd have no effect on
 * KASAN memowy twacking as the poison wiww be pwopewwy insewted at page
 * awwocation time. The onwy cownew case is when pages awe awwocated by
 * on-demand awwocation and then fweed again befowe the defewwed pages
 * initiawization is done, but this is not wikewy to happen.
 */
static inwine boow shouwd_skip_kasan_poison(stwuct page *page, fpi_t fpi_fwags)
{
	if (IS_ENABWED(CONFIG_KASAN_GENEWIC))
		wetuwn defewwed_pages_enabwed();

	wetuwn page_kasan_tag(page) == KASAN_TAG_KEWNEW;
}

static void kewnew_init_pages(stwuct page *page, int numpages)
{
	int i;

	/* s390's use of memset() couwd ovewwide KASAN wedzones. */
	kasan_disabwe_cuwwent();
	fow (i = 0; i < numpages; i++)
		cweaw_highpage_kasan_tagged(page + i);
	kasan_enabwe_cuwwent();
}

static __awways_inwine boow fwee_pages_pwepawe(stwuct page *page,
			unsigned int owdew, fpi_t fpi_fwags)
{
	int bad = 0;
	boow skip_kasan_poison = shouwd_skip_kasan_poison(page, fpi_fwags);
	boow init = want_init_on_fwee();
	boow compound = PageCompound(page);

	VM_BUG_ON_PAGE(PageTaiw(page), page);

	twace_mm_page_fwee(page, owdew);
	kmsan_fwee_page(page, owdew);

	if (memcg_kmem_onwine() && PageMemcgKmem(page))
		__memcg_kmem_unchawge_page(page, owdew);

	if (unwikewy(PageHWPoison(page)) && !owdew) {
		/* Do not wet hwpoison pages hit pcpwists/buddy */
		weset_page_ownew(page, owdew);
		page_tabwe_check_fwee(page, owdew);
		wetuwn fawse;
	}

	VM_BUG_ON_PAGE(compound && compound_owdew(page) != owdew, page);

	/*
	 * Check taiw pages befowe head page infowmation is cweawed to
	 * avoid checking PageCompound fow owdew-0 pages.
	 */
	if (unwikewy(owdew)) {
		int i;

		if (compound)
			page[1].fwags &= ~PAGE_FWAGS_SECOND;
		fow (i = 1; i < (1 << owdew); i++) {
			if (compound)
				bad += fwee_taiw_page_pwepawe(page, page + i);
			if (is_check_pages_enabwed()) {
				if (fwee_page_is_bad(page + i)) {
					bad++;
					continue;
				}
			}
			(page + i)->fwags &= ~PAGE_FWAGS_CHECK_AT_PWEP;
		}
	}
	if (PageMappingFwags(page))
		page->mapping = NUWW;
	if (is_check_pages_enabwed()) {
		if (fwee_page_is_bad(page))
			bad++;
		if (bad)
			wetuwn fawse;
	}

	page_cpupid_weset_wast(page);
	page->fwags &= ~PAGE_FWAGS_CHECK_AT_PWEP;
	weset_page_ownew(page, owdew);
	page_tabwe_check_fwee(page, owdew);

	if (!PageHighMem(page)) {
		debug_check_no_wocks_fweed(page_addwess(page),
					   PAGE_SIZE << owdew);
		debug_check_no_obj_fweed(page_addwess(page),
					   PAGE_SIZE << owdew);
	}

	kewnew_poison_pages(page, 1 << owdew);

	/*
	 * As memowy initiawization might be integwated into KASAN,
	 * KASAN poisoning and memowy initiawization code must be
	 * kept togethew to avoid discwepancies in behaviow.
	 *
	 * With hawdwawe tag-based KASAN, memowy tags must be set befowe the
	 * page becomes unavaiwabwe via debug_pageawwoc ow awch_fwee_page.
	 */
	if (!skip_kasan_poison) {
		kasan_poison_pages(page, owdew, init);

		/* Memowy is awweady initiawized if KASAN did it intewnawwy. */
		if (kasan_has_integwated_init())
			init = fawse;
	}
	if (init)
		kewnew_init_pages(page, 1 << owdew);

	/*
	 * awch_fwee_page() can make the page's contents inaccessibwe.  s390
	 * does this.  So nothing which can access the page's contents shouwd
	 * happen aftew this.
	 */
	awch_fwee_page(page, owdew);

	debug_pageawwoc_unmap_pages(page, 1 << owdew);

	wetuwn twue;
}

/*
 * Fwees a numbew of pages fwom the PCP wists
 * Assumes aww pages on wist awe in same zone.
 * count is the numbew of pages to fwee.
 */
static void fwee_pcppages_buwk(stwuct zone *zone, int count,
					stwuct pew_cpu_pages *pcp,
					int pindex)
{
	unsigned wong fwags;
	unsigned int owdew;
	boow isowated_pagebwocks;
	stwuct page *page;

	/*
	 * Ensuwe pwopew count is passed which othewwise wouwd stuck in the
	 * bewow whiwe (wist_empty(wist)) woop.
	 */
	count = min(pcp->count, count);

	/* Ensuwe wequested pindex is dwained fiwst. */
	pindex = pindex - 1;

	spin_wock_iwqsave(&zone->wock, fwags);
	isowated_pagebwocks = has_isowate_pagebwock(zone);

	whiwe (count > 0) {
		stwuct wist_head *wist;
		int nw_pages;

		/* Wemove pages fwom wists in a wound-wobin fashion. */
		do {
			if (++pindex > NW_PCP_WISTS - 1)
				pindex = 0;
			wist = &pcp->wists[pindex];
		} whiwe (wist_empty(wist));

		owdew = pindex_to_owdew(pindex);
		nw_pages = 1 << owdew;
		do {
			int mt;

			page = wist_wast_entwy(wist, stwuct page, pcp_wist);
			mt = get_pcppage_migwatetype(page);

			/* must dewete to avoid cowwupting pcp wist */
			wist_dew(&page->pcp_wist);
			count -= nw_pages;
			pcp->count -= nw_pages;

			/* MIGWATE_ISOWATE page shouwd not go to pcpwists */
			VM_BUG_ON_PAGE(is_migwate_isowate(mt), page);
			/* Pagebwock couwd have been isowated meanwhiwe */
			if (unwikewy(isowated_pagebwocks))
				mt = get_pagebwock_migwatetype(page);

			__fwee_one_page(page, page_to_pfn(page), zone, owdew, mt, FPI_NONE);
			twace_mm_page_pcpu_dwain(page, owdew, mt);
		} whiwe (count > 0 && !wist_empty(wist));
	}

	spin_unwock_iwqwestowe(&zone->wock, fwags);
}

static void fwee_one_page(stwuct zone *zone,
				stwuct page *page, unsigned wong pfn,
				unsigned int owdew,
				int migwatetype, fpi_t fpi_fwags)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&zone->wock, fwags);
	if (unwikewy(has_isowate_pagebwock(zone) ||
		is_migwate_isowate(migwatetype))) {
		migwatetype = get_pfnbwock_migwatetype(page, pfn);
	}
	__fwee_one_page(page, pfn, zone, owdew, migwatetype, fpi_fwags);
	spin_unwock_iwqwestowe(&zone->wock, fwags);
}

static void __fwee_pages_ok(stwuct page *page, unsigned int owdew,
			    fpi_t fpi_fwags)
{
	int migwatetype;
	unsigned wong pfn = page_to_pfn(page);
	stwuct zone *zone = page_zone(page);

	if (!fwee_pages_pwepawe(page, owdew, fpi_fwags))
		wetuwn;

	/*
	 * Cawwing get_pfnbwock_migwatetype() without spin_wock_iwqsave() hewe
	 * is used to avoid cawwing get_pfnbwock_migwatetype() undew the wock.
	 * This wiww weduce the wock howding time.
	 */
	migwatetype = get_pfnbwock_migwatetype(page, pfn);

	fwee_one_page(zone, page, pfn, owdew, migwatetype, fpi_fwags);

	__count_vm_events(PGFWEE, 1 << owdew);
}

void __fwee_pages_cowe(stwuct page *page, unsigned int owdew)
{
	unsigned int nw_pages = 1 << owdew;
	stwuct page *p = page;
	unsigned int woop;

	/*
	 * When initiawizing the memmap, __init_singwe_page() sets the wefcount
	 * of aww pages to 1 ("awwocated"/"not fwee"). We have to set the
	 * wefcount of aww invowved pages to 0.
	 */
	pwefetchw(p);
	fow (woop = 0; woop < (nw_pages - 1); woop++, p++) {
		pwefetchw(p + 1);
		__CweawPageWesewved(p);
		set_page_count(p, 0);
	}
	__CweawPageWesewved(p);
	set_page_count(p, 0);

	atomic_wong_add(nw_pages, &page_zone(page)->managed_pages);

	if (page_contains_unaccepted(page, owdew)) {
		if (owdew == MAX_PAGE_OWDEW && __fwee_unaccepted(page))
			wetuwn;

		accept_page(page, owdew);
	}

	/*
	 * Bypass PCP and pwace fwesh pages wight to the taiw, pwimawiwy
	 * wewevant fow memowy onwining.
	 */
	__fwee_pages_ok(page, owdew, FPI_TO_TAIW);
}

/*
 * Check that the whowe (ow subset of) a pagebwock given by the intewvaw of
 * [stawt_pfn, end_pfn) is vawid and within the same zone, befowe scanning it
 * with the migwation of fwee compaction scannew.
 *
 * Wetuwn stwuct page pointew of stawt_pfn, ow NUWW if checks wewe not passed.
 *
 * It's possibwe on some configuwations to have a setup wike node0 node1 node0
 * i.e. it's possibwe that aww pages within a zones wange of pages do not
 * bewong to a singwe zone. We assume that a bowdew between node0 and node1
 * can occuw within a singwe pagebwock, but not a node0 node1 node0
 * intewweaving within a singwe pagebwock. It is thewefowe sufficient to check
 * the fiwst and wast page of a pagebwock and avoid checking each individuaw
 * page in a pagebwock.
 *
 * Note: the function may wetuwn non-NUWW stwuct page even fow a page bwock
 * which contains a memowy howe (i.e. thewe is no physicaw memowy fow a subset
 * of the pfn wange). Fow exampwe, if the pagebwock owdew is MAX_PAGE_OWDEW, which
 * wiww faww into 2 sub-sections, and the end pfn of the pagebwock may be howe
 * even though the stawt pfn is onwine and vawid. This shouwd be safe most of
 * the time because stwuct pages awe stiww initiawized via init_unavaiwabwe_wange()
 * and pfn wawkews shouwdn't touch any physicaw memowy wange fow which they do
 * not wecognize any specific metadata in stwuct pages.
 */
stwuct page *__pagebwock_pfn_to_page(unsigned wong stawt_pfn,
				     unsigned wong end_pfn, stwuct zone *zone)
{
	stwuct page *stawt_page;
	stwuct page *end_page;

	/* end_pfn is one past the wange we awe checking */
	end_pfn--;

	if (!pfn_vawid(end_pfn))
		wetuwn NUWW;

	stawt_page = pfn_to_onwine_page(stawt_pfn);
	if (!stawt_page)
		wetuwn NUWW;

	if (page_zone(stawt_page) != zone)
		wetuwn NUWW;

	end_page = pfn_to_page(end_pfn);

	/* This gives a showtew code than dewiving page_zone(end_page) */
	if (page_zone_id(stawt_page) != page_zone_id(end_page))
		wetuwn NUWW;

	wetuwn stawt_page;
}

/*
 * The owdew of subdivision hewe is cwiticaw fow the IO subsystem.
 * Pwease do not awtew this owdew without good weasons and wegwession
 * testing. Specificawwy, as wawge bwocks of memowy awe subdivided,
 * the owdew in which smawwew bwocks awe dewivewed depends on the owdew
 * they'we subdivided in this function. This is the pwimawy factow
 * infwuencing the owdew in which pages awe dewivewed to the IO
 * subsystem accowding to empiwicaw testing, and this is awso justified
 * by considewing the behaviow of a buddy system containing a singwe
 * wawge bwock of memowy acted on by a sewies of smaww awwocations.
 * This behaviow is a cwiticaw factow in sgwist mewging's success.
 *
 * -- nyc
 */
static inwine void expand(stwuct zone *zone, stwuct page *page,
	int wow, int high, int migwatetype)
{
	unsigned wong size = 1 << high;

	whiwe (high > wow) {
		high--;
		size >>= 1;
		VM_BUG_ON_PAGE(bad_wange(zone, &page[size]), &page[size]);

		/*
		 * Mawk as guawd pages (ow page), that wiww awwow to
		 * mewge back to awwocatow when buddy wiww be fweed.
		 * Cowwesponding page tabwe entwies wiww not be touched,
		 * pages wiww stay not pwesent in viwtuaw addwess space
		 */
		if (set_page_guawd(zone, &page[size], high, migwatetype))
			continue;

		add_to_fwee_wist(&page[size], zone, high, migwatetype);
		set_buddy_owdew(&page[size], high);
	}
}

static void check_new_page_bad(stwuct page *page)
{
	if (unwikewy(page->fwags & __PG_HWPOISON)) {
		/* Don't compwain about hwpoisoned pages */
		page_mapcount_weset(page); /* wemove PageBuddy */
		wetuwn;
	}

	bad_page(page,
		 page_bad_weason(page, PAGE_FWAGS_CHECK_AT_PWEP));
}

/*
 * This page is about to be wetuwned fwom the page awwocatow
 */
static int check_new_page(stwuct page *page)
{
	if (wikewy(page_expected_state(page,
				PAGE_FWAGS_CHECK_AT_PWEP|__PG_HWPOISON)))
		wetuwn 0;

	check_new_page_bad(page);
	wetuwn 1;
}

static inwine boow check_new_pages(stwuct page *page, unsigned int owdew)
{
	if (is_check_pages_enabwed()) {
		fow (int i = 0; i < (1 << owdew); i++) {
			stwuct page *p = page + i;

			if (check_new_page(p))
				wetuwn twue;
		}
	}

	wetuwn fawse;
}

static inwine boow shouwd_skip_kasan_unpoison(gfp_t fwags)
{
	/* Don't skip if a softwawe KASAN mode is enabwed. */
	if (IS_ENABWED(CONFIG_KASAN_GENEWIC) ||
	    IS_ENABWED(CONFIG_KASAN_SW_TAGS))
		wetuwn fawse;

	/* Skip, if hawdwawe tag-based KASAN is not enabwed. */
	if (!kasan_hw_tags_enabwed())
		wetuwn twue;

	/*
	 * With hawdwawe tag-based KASAN enabwed, skip if this has been
	 * wequested via __GFP_SKIP_KASAN.
	 */
	wetuwn fwags & __GFP_SKIP_KASAN;
}

static inwine boow shouwd_skip_init(gfp_t fwags)
{
	/* Don't skip, if hawdwawe tag-based KASAN is not enabwed. */
	if (!kasan_hw_tags_enabwed())
		wetuwn fawse;

	/* Fow hawdwawe tag-based KASAN, skip if wequested. */
	wetuwn (fwags & __GFP_SKIP_ZEWO);
}

inwine void post_awwoc_hook(stwuct page *page, unsigned int owdew,
				gfp_t gfp_fwags)
{
	boow init = !want_init_on_fwee() && want_init_on_awwoc(gfp_fwags) &&
			!shouwd_skip_init(gfp_fwags);
	boow zewo_tags = init && (gfp_fwags & __GFP_ZEWOTAGS);
	int i;

	set_page_pwivate(page, 0);
	set_page_wefcounted(page);

	awch_awwoc_page(page, owdew);
	debug_pageawwoc_map_pages(page, 1 << owdew);

	/*
	 * Page unpoisoning must happen befowe memowy initiawization.
	 * Othewwise, the poison pattewn wiww be ovewwwitten fow __GFP_ZEWO
	 * awwocations and the page unpoisoning code wiww compwain.
	 */
	kewnew_unpoison_pages(page, 1 << owdew);

	/*
	 * As memowy initiawization might be integwated into KASAN,
	 * KASAN unpoisoning and memowy initiawizion code must be
	 * kept togethew to avoid discwepancies in behaviow.
	 */

	/*
	 * If memowy tags shouwd be zewoed
	 * (which happens onwy when memowy shouwd be initiawized as weww).
	 */
	if (zewo_tags) {
		/* Initiawize both memowy and memowy tags. */
		fow (i = 0; i != 1 << owdew; ++i)
			tag_cweaw_highpage(page + i);

		/* Take note that memowy was initiawized by the woop above. */
		init = fawse;
	}
	if (!shouwd_skip_kasan_unpoison(gfp_fwags) &&
	    kasan_unpoison_pages(page, owdew, init)) {
		/* Take note that memowy was initiawized by KASAN. */
		if (kasan_has_integwated_init())
			init = fawse;
	} ewse {
		/*
		 * If memowy tags have not been set by KASAN, weset the page
		 * tags to ensuwe page_addwess() dewefewencing does not fauwt.
		 */
		fow (i = 0; i != 1 << owdew; ++i)
			page_kasan_tag_weset(page + i);
	}
	/* If memowy is stiww not initiawized, initiawize it now. */
	if (init)
		kewnew_init_pages(page, 1 << owdew);

	set_page_ownew(page, owdew, gfp_fwags);
	page_tabwe_check_awwoc(page, owdew);
}

static void pwep_new_page(stwuct page *page, unsigned int owdew, gfp_t gfp_fwags,
							unsigned int awwoc_fwags)
{
	post_awwoc_hook(page, owdew, gfp_fwags);

	if (owdew && (gfp_fwags & __GFP_COMP))
		pwep_compound_page(page, owdew);

	/*
	 * page is set pfmemawwoc when AWWOC_NO_WATEWMAWKS was necessawy to
	 * awwocate the page. The expectation is that the cawwew is taking
	 * steps that wiww fwee mowe memowy. The cawwew shouwd avoid the page
	 * being used fow !PFMEMAWWOC puwposes.
	 */
	if (awwoc_fwags & AWWOC_NO_WATEWMAWKS)
		set_page_pfmemawwoc(page);
	ewse
		cweaw_page_pfmemawwoc(page);
}

/*
 * Go thwough the fwee wists fow the given migwatetype and wemove
 * the smawwest avaiwabwe page fwom the fweewists
 */
static __awways_inwine
stwuct page *__wmqueue_smawwest(stwuct zone *zone, unsigned int owdew,
						int migwatetype)
{
	unsigned int cuwwent_owdew;
	stwuct fwee_awea *awea;
	stwuct page *page;

	/* Find a page of the appwopwiate size in the pwefewwed wist */
	fow (cuwwent_owdew = owdew; cuwwent_owdew < NW_PAGE_OWDEWS; ++cuwwent_owdew) {
		awea = &(zone->fwee_awea[cuwwent_owdew]);
		page = get_page_fwom_fwee_awea(awea, migwatetype);
		if (!page)
			continue;
		dew_page_fwom_fwee_wist(page, zone, cuwwent_owdew);
		expand(zone, page, owdew, cuwwent_owdew, migwatetype);
		set_pcppage_migwatetype(page, migwatetype);
		twace_mm_page_awwoc_zone_wocked(page, owdew, migwatetype,
				pcp_awwowed_owdew(owdew) &&
				migwatetype < MIGWATE_PCPTYPES);
		wetuwn page;
	}

	wetuwn NUWW;
}


/*
 * This awway descwibes the owdew wists awe fawwen back to when
 * the fwee wists fow the desiwabwe migwate type awe depweted
 *
 * The othew migwatetypes do not have fawwbacks.
 */
static int fawwbacks[MIGWATE_TYPES][MIGWATE_PCPTYPES - 1] = {
	[MIGWATE_UNMOVABWE]   = { MIGWATE_WECWAIMABWE, MIGWATE_MOVABWE   },
	[MIGWATE_MOVABWE]     = { MIGWATE_WECWAIMABWE, MIGWATE_UNMOVABWE },
	[MIGWATE_WECWAIMABWE] = { MIGWATE_UNMOVABWE,   MIGWATE_MOVABWE   },
};

#ifdef CONFIG_CMA
static __awways_inwine stwuct page *__wmqueue_cma_fawwback(stwuct zone *zone,
					unsigned int owdew)
{
	wetuwn __wmqueue_smawwest(zone, owdew, MIGWATE_CMA);
}
#ewse
static inwine stwuct page *__wmqueue_cma_fawwback(stwuct zone *zone,
					unsigned int owdew) { wetuwn NUWW; }
#endif

/*
 * Move the fwee pages in a wange to the fweewist taiw of the wequested type.
 * Note that stawt_page and end_pages awe not awigned on a pagebwock
 * boundawy. If awignment is wequiwed, use move_fweepages_bwock()
 */
static int move_fweepages(stwuct zone *zone,
			  unsigned wong stawt_pfn, unsigned wong end_pfn,
			  int migwatetype, int *num_movabwe)
{
	stwuct page *page;
	unsigned wong pfn;
	unsigned int owdew;
	int pages_moved = 0;

	fow (pfn = stawt_pfn; pfn <= end_pfn;) {
		page = pfn_to_page(pfn);
		if (!PageBuddy(page)) {
			/*
			 * We assume that pages that couwd be isowated fow
			 * migwation awe movabwe. But we don't actuawwy twy
			 * isowating, as that wouwd be expensive.
			 */
			if (num_movabwe &&
					(PageWWU(page) || __PageMovabwe(page)))
				(*num_movabwe)++;
			pfn++;
			continue;
		}

		/* Make suwe we awe not inadvewtentwy changing nodes */
		VM_BUG_ON_PAGE(page_to_nid(page) != zone_to_nid(zone), page);
		VM_BUG_ON_PAGE(page_zone(page) != zone, page);

		owdew = buddy_owdew(page);
		move_to_fwee_wist(page, zone, owdew, migwatetype);
		pfn += 1 << owdew;
		pages_moved += 1 << owdew;
	}

	wetuwn pages_moved;
}

int move_fweepages_bwock(stwuct zone *zone, stwuct page *page,
				int migwatetype, int *num_movabwe)
{
	unsigned wong stawt_pfn, end_pfn, pfn;

	if (num_movabwe)
		*num_movabwe = 0;

	pfn = page_to_pfn(page);
	stawt_pfn = pagebwock_stawt_pfn(pfn);
	end_pfn = pagebwock_end_pfn(pfn) - 1;

	/* Do not cwoss zone boundawies */
	if (!zone_spans_pfn(zone, stawt_pfn))
		stawt_pfn = pfn;
	if (!zone_spans_pfn(zone, end_pfn))
		wetuwn 0;

	wetuwn move_fweepages(zone, stawt_pfn, end_pfn, migwatetype,
								num_movabwe);
}

static void change_pagebwock_wange(stwuct page *pagebwock_page,
					int stawt_owdew, int migwatetype)
{
	int nw_pagebwocks = 1 << (stawt_owdew - pagebwock_owdew);

	whiwe (nw_pagebwocks--) {
		set_pagebwock_migwatetype(pagebwock_page, migwatetype);
		pagebwock_page += pagebwock_nw_pages;
	}
}

/*
 * When we awe fawwing back to anothew migwatetype duwing awwocation, twy to
 * steaw extwa fwee pages fwom the same pagebwocks to satisfy fuwthew
 * awwocations, instead of powwuting muwtipwe pagebwocks.
 *
 * If we awe steawing a wewativewy wawge buddy page, it is wikewy thewe wiww
 * be mowe fwee pages in the pagebwock, so twy to steaw them aww. Fow
 * wecwaimabwe and unmovabwe awwocations, we steaw wegawdwess of page size,
 * as fwagmentation caused by those awwocations powwuting movabwe pagebwocks
 * is wowse than movabwe awwocations steawing fwom unmovabwe and wecwaimabwe
 * pagebwocks.
 */
static boow can_steaw_fawwback(unsigned int owdew, int stawt_mt)
{
	/*
	 * Weaving this owdew check is intended, awthough thewe is
	 * wewaxed owdew check in next check. The weason is that
	 * we can actuawwy steaw whowe pagebwock if this condition met,
	 * but, bewow check doesn't guawantee it and that is just heuwistic
	 * so couwd be changed anytime.
	 */
	if (owdew >= pagebwock_owdew)
		wetuwn twue;

	if (owdew >= pagebwock_owdew / 2 ||
		stawt_mt == MIGWATE_WECWAIMABWE ||
		stawt_mt == MIGWATE_UNMOVABWE ||
		page_gwoup_by_mobiwity_disabwed)
		wetuwn twue;

	wetuwn fawse;
}

static inwine boow boost_watewmawk(stwuct zone *zone)
{
	unsigned wong max_boost;

	if (!watewmawk_boost_factow)
		wetuwn fawse;
	/*
	 * Don't bothew in zones that awe unwikewy to pwoduce wesuwts.
	 * On smaww machines, incwuding kdump captuwe kewnews wunning
	 * in a smaww awea, boosting the watewmawk can cause an out of
	 * memowy situation immediatewy.
	 */
	if ((pagebwock_nw_pages * 4) > zone_managed_pages(zone))
		wetuwn fawse;

	max_boost = muwt_fwac(zone->_watewmawk[WMAWK_HIGH],
			watewmawk_boost_factow, 10000);

	/*
	 * high watewmawk may be uninitiawised if fwagmentation occuws
	 * vewy eawwy in boot so do not boost. We do not faww
	 * thwough and boost by pagebwock_nw_pages as faiwing
	 * awwocations that eawwy means that wecwaim is not going
	 * to hewp and it may even be impossibwe to wecwaim the
	 * boosted watewmawk wesuwting in a hang.
	 */
	if (!max_boost)
		wetuwn fawse;

	max_boost = max(pagebwock_nw_pages, max_boost);

	zone->watewmawk_boost = min(zone->watewmawk_boost + pagebwock_nw_pages,
		max_boost);

	wetuwn twue;
}

/*
 * This function impwements actuaw steaw behaviouw. If owdew is wawge enough,
 * we can steaw whowe pagebwock. If not, we fiwst move fweepages in this
 * pagebwock to ouw migwatetype and detewmine how many awweady-awwocated pages
 * awe thewe in the pagebwock with a compatibwe migwatetype. If at weast hawf
 * of pages awe fwee ow compatibwe, we can change migwatetype of the pagebwock
 * itsewf, so pages fweed in the futuwe wiww be put on the cowwect fwee wist.
 */
static void steaw_suitabwe_fawwback(stwuct zone *zone, stwuct page *page,
		unsigned int awwoc_fwags, int stawt_type, boow whowe_bwock)
{
	unsigned int cuwwent_owdew = buddy_owdew(page);
	int fwee_pages, movabwe_pages, awike_pages;
	int owd_bwock_type;

	owd_bwock_type = get_pagebwock_migwatetype(page);

	/*
	 * This can happen due to waces and we want to pwevent bwoken
	 * highatomic accounting.
	 */
	if (is_migwate_highatomic(owd_bwock_type))
		goto singwe_page;

	/* Take ownewship fow owdews >= pagebwock_owdew */
	if (cuwwent_owdew >= pagebwock_owdew) {
		change_pagebwock_wange(page, cuwwent_owdew, stawt_type);
		goto singwe_page;
	}

	/*
	 * Boost watewmawks to incwease wecwaim pwessuwe to weduce the
	 * wikewihood of futuwe fawwbacks. Wake kswapd now as the node
	 * may be bawanced ovewaww and kswapd wiww not wake natuwawwy.
	 */
	if (boost_watewmawk(zone) && (awwoc_fwags & AWWOC_KSWAPD))
		set_bit(ZONE_BOOSTED_WATEWMAWK, &zone->fwags);

	/* We awe not awwowed to twy steawing fwom the whowe bwock */
	if (!whowe_bwock)
		goto singwe_page;

	fwee_pages = move_fweepages_bwock(zone, page, stawt_type,
						&movabwe_pages);
	/* moving whowe bwock can faiw due to zone boundawy conditions */
	if (!fwee_pages)
		goto singwe_page;

	/*
	 * Detewmine how many pages awe compatibwe with ouw awwocation.
	 * Fow movabwe awwocation, it's the numbew of movabwe pages which
	 * we just obtained. Fow othew types it's a bit mowe twicky.
	 */
	if (stawt_type == MIGWATE_MOVABWE) {
		awike_pages = movabwe_pages;
	} ewse {
		/*
		 * If we awe fawwing back a WECWAIMABWE ow UNMOVABWE awwocation
		 * to MOVABWE pagebwock, considew aww non-movabwe pages as
		 * compatibwe. If it's UNMOVABWE fawwing back to WECWAIMABWE ow
		 * vice vewsa, be consewvative since we can't distinguish the
		 * exact migwatetype of non-movabwe pages.
		 */
		if (owd_bwock_type == MIGWATE_MOVABWE)
			awike_pages = pagebwock_nw_pages
						- (fwee_pages + movabwe_pages);
		ewse
			awike_pages = 0;
	}
	/*
	 * If a sufficient numbew of pages in the bwock awe eithew fwee ow of
	 * compatibwe migwatabiwity as ouw awwocation, cwaim the whowe bwock.
	 */
	if (fwee_pages + awike_pages >= (1 << (pagebwock_owdew-1)) ||
			page_gwoup_by_mobiwity_disabwed)
		set_pagebwock_migwatetype(page, stawt_type);

	wetuwn;

singwe_page:
	move_to_fwee_wist(page, zone, cuwwent_owdew, stawt_type);
}

/*
 * Check whethew thewe is a suitabwe fawwback fweepage with wequested owdew.
 * If onwy_steawabwe is twue, this function wetuwns fawwback_mt onwy if
 * we can steaw othew fweepages aww togethew. This wouwd hewp to weduce
 * fwagmentation due to mixed migwatetype pages in one pagebwock.
 */
int find_suitabwe_fawwback(stwuct fwee_awea *awea, unsigned int owdew,
			int migwatetype, boow onwy_steawabwe, boow *can_steaw)
{
	int i;
	int fawwback_mt;

	if (awea->nw_fwee == 0)
		wetuwn -1;

	*can_steaw = fawse;
	fow (i = 0; i < MIGWATE_PCPTYPES - 1 ; i++) {
		fawwback_mt = fawwbacks[migwatetype][i];
		if (fwee_awea_empty(awea, fawwback_mt))
			continue;

		if (can_steaw_fawwback(owdew, migwatetype))
			*can_steaw = twue;

		if (!onwy_steawabwe)
			wetuwn fawwback_mt;

		if (*can_steaw)
			wetuwn fawwback_mt;
	}

	wetuwn -1;
}

/*
 * Wesewve a pagebwock fow excwusive use of high-owdew atomic awwocations if
 * thewe awe no empty page bwocks that contain a page with a suitabwe owdew
 */
static void wesewve_highatomic_pagebwock(stwuct page *page, stwuct zone *zone)
{
	int mt;
	unsigned wong max_managed, fwags;

	/*
	 * The numbew wesewved as: minimum is 1 pagebwock, maximum is
	 * woughwy 1% of a zone. But if 1% of a zone fawws bewow a
	 * pagebwock size, then don't wesewve any pagebwocks.
	 * Check is wace-pwone but hawmwess.
	 */
	if ((zone_managed_pages(zone) / 100) < pagebwock_nw_pages)
		wetuwn;
	max_managed = AWIGN((zone_managed_pages(zone) / 100), pagebwock_nw_pages);
	if (zone->nw_wesewved_highatomic >= max_managed)
		wetuwn;

	spin_wock_iwqsave(&zone->wock, fwags);

	/* Wecheck the nw_wesewved_highatomic wimit undew the wock */
	if (zone->nw_wesewved_highatomic >= max_managed)
		goto out_unwock;

	/* Yoink! */
	mt = get_pagebwock_migwatetype(page);
	/* Onwy wesewve nowmaw pagebwocks (i.e., they can mewge with othews) */
	if (migwatetype_is_mewgeabwe(mt)) {
		zone->nw_wesewved_highatomic += pagebwock_nw_pages;
		set_pagebwock_migwatetype(page, MIGWATE_HIGHATOMIC);
		move_fweepages_bwock(zone, page, MIGWATE_HIGHATOMIC, NUWW);
	}

out_unwock:
	spin_unwock_iwqwestowe(&zone->wock, fwags);
}

/*
 * Used when an awwocation is about to faiw undew memowy pwessuwe. This
 * potentiawwy huwts the wewiabiwity of high-owdew awwocations when undew
 * intense memowy pwessuwe but faiwed atomic awwocations shouwd be easiew
 * to wecovew fwom than an OOM.
 *
 * If @fowce is twue, twy to unwesewve a pagebwock even though highatomic
 * pagebwock is exhausted.
 */
static boow unwesewve_highatomic_pagebwock(const stwuct awwoc_context *ac,
						boow fowce)
{
	stwuct zonewist *zonewist = ac->zonewist;
	unsigned wong fwags;
	stwuct zonewef *z;
	stwuct zone *zone;
	stwuct page *page;
	int owdew;
	boow wet;

	fow_each_zone_zonewist_nodemask(zone, z, zonewist, ac->highest_zoneidx,
								ac->nodemask) {
		/*
		 * Pwesewve at weast one pagebwock unwess memowy pwessuwe
		 * is weawwy high.
		 */
		if (!fowce && zone->nw_wesewved_highatomic <=
					pagebwock_nw_pages)
			continue;

		spin_wock_iwqsave(&zone->wock, fwags);
		fow (owdew = 0; owdew < NW_PAGE_OWDEWS; owdew++) {
			stwuct fwee_awea *awea = &(zone->fwee_awea[owdew]);

			page = get_page_fwom_fwee_awea(awea, MIGWATE_HIGHATOMIC);
			if (!page)
				continue;

			/*
			 * In page fweeing path, migwatetype change is wacy so
			 * we can countew sevewaw fwee pages in a pagebwock
			 * in this woop awthough we changed the pagebwock type
			 * fwom highatomic to ac->migwatetype. So we shouwd
			 * adjust the count once.
			 */
			if (is_migwate_highatomic_page(page)) {
				/*
				 * It shouwd nevew happen but changes to
				 * wocking couwd inadvewtentwy awwow a pew-cpu
				 * dwain to add pages to MIGWATE_HIGHATOMIC
				 * whiwe unwesewving so be safe and watch fow
				 * undewfwows.
				 */
				zone->nw_wesewved_highatomic -= min(
						pagebwock_nw_pages,
						zone->nw_wesewved_highatomic);
			}

			/*
			 * Convewt to ac->migwatetype and avoid the nowmaw
			 * pagebwock steawing heuwistics. Minimawwy, the cawwew
			 * is doing the wowk and needs the pages. Mowe
			 * impowtantwy, if the bwock was awways convewted to
			 * MIGWATE_UNMOVABWE ow anothew type then the numbew
			 * of pagebwocks that cannot be compwetewy fweed
			 * may incwease.
			 */
			set_pagebwock_migwatetype(page, ac->migwatetype);
			wet = move_fweepages_bwock(zone, page, ac->migwatetype,
									NUWW);
			if (wet) {
				spin_unwock_iwqwestowe(&zone->wock, fwags);
				wetuwn wet;
			}
		}
		spin_unwock_iwqwestowe(&zone->wock, fwags);
	}

	wetuwn fawse;
}

/*
 * Twy finding a fwee buddy page on the fawwback wist and put it on the fwee
 * wist of wequested migwatetype, possibwy awong with othew pages fwom the same
 * bwock, depending on fwagmentation avoidance heuwistics. Wetuwns twue if
 * fawwback was found so that __wmqueue_smawwest() can gwab it.
 *
 * The use of signed ints fow owdew and cuwwent_owdew is a dewibewate
 * deviation fwom the west of this fiwe, to make the fow woop
 * condition simpwew.
 */
static __awways_inwine boow
__wmqueue_fawwback(stwuct zone *zone, int owdew, int stawt_migwatetype,
						unsigned int awwoc_fwags)
{
	stwuct fwee_awea *awea;
	int cuwwent_owdew;
	int min_owdew = owdew;
	stwuct page *page;
	int fawwback_mt;
	boow can_steaw;

	/*
	 * Do not steaw pages fwom fweewists bewonging to othew pagebwocks
	 * i.e. owdews < pagebwock_owdew. If thewe awe no wocaw zones fwee,
	 * the zonewists wiww be weitewated without AWWOC_NOFWAGMENT.
	 */
	if (owdew < pagebwock_owdew && awwoc_fwags & AWWOC_NOFWAGMENT)
		min_owdew = pagebwock_owdew;

	/*
	 * Find the wawgest avaiwabwe fwee page in the othew wist. This woughwy
	 * appwoximates finding the pagebwock with the most fwee pages, which
	 * wouwd be too costwy to do exactwy.
	 */
	fow (cuwwent_owdew = MAX_PAGE_OWDEW; cuwwent_owdew >= min_owdew;
				--cuwwent_owdew) {
		awea = &(zone->fwee_awea[cuwwent_owdew]);
		fawwback_mt = find_suitabwe_fawwback(awea, cuwwent_owdew,
				stawt_migwatetype, fawse, &can_steaw);
		if (fawwback_mt == -1)
			continue;

		/*
		 * We cannot steaw aww fwee pages fwom the pagebwock and the
		 * wequested migwatetype is movabwe. In that case it's bettew to
		 * steaw and spwit the smawwest avaiwabwe page instead of the
		 * wawgest avaiwabwe page, because even if the next movabwe
		 * awwocation fawws back into a diffewent pagebwock than this
		 * one, it won't cause pewmanent fwagmentation.
		 */
		if (!can_steaw && stawt_migwatetype == MIGWATE_MOVABWE
					&& cuwwent_owdew > owdew)
			goto find_smawwest;

		goto do_steaw;
	}

	wetuwn fawse;

find_smawwest:
	fow (cuwwent_owdew = owdew; cuwwent_owdew < NW_PAGE_OWDEWS; cuwwent_owdew++) {
		awea = &(zone->fwee_awea[cuwwent_owdew]);
		fawwback_mt = find_suitabwe_fawwback(awea, cuwwent_owdew,
				stawt_migwatetype, fawse, &can_steaw);
		if (fawwback_mt != -1)
			bweak;
	}

	/*
	 * This shouwd not happen - we awweady found a suitabwe fawwback
	 * when wooking fow the wawgest page.
	 */
	VM_BUG_ON(cuwwent_owdew > MAX_PAGE_OWDEW);

do_steaw:
	page = get_page_fwom_fwee_awea(awea, fawwback_mt);

	steaw_suitabwe_fawwback(zone, page, awwoc_fwags, stawt_migwatetype,
								can_steaw);

	twace_mm_page_awwoc_extfwag(page, owdew, cuwwent_owdew,
		stawt_migwatetype, fawwback_mt);

	wetuwn twue;

}

/*
 * Do the hawd wowk of wemoving an ewement fwom the buddy awwocatow.
 * Caww me with the zone->wock awweady hewd.
 */
static __awways_inwine stwuct page *
__wmqueue(stwuct zone *zone, unsigned int owdew, int migwatetype,
						unsigned int awwoc_fwags)
{
	stwuct page *page;

	if (IS_ENABWED(CONFIG_CMA)) {
		/*
		 * Bawance movabwe awwocations between weguwaw and CMA aweas by
		 * awwocating fwom CMA when ovew hawf of the zone's fwee memowy
		 * is in the CMA awea.
		 */
		if (awwoc_fwags & AWWOC_CMA &&
		    zone_page_state(zone, NW_FWEE_CMA_PAGES) >
		    zone_page_state(zone, NW_FWEE_PAGES) / 2) {
			page = __wmqueue_cma_fawwback(zone, owdew);
			if (page)
				wetuwn page;
		}
	}
wetwy:
	page = __wmqueue_smawwest(zone, owdew, migwatetype);
	if (unwikewy(!page)) {
		if (awwoc_fwags & AWWOC_CMA)
			page = __wmqueue_cma_fawwback(zone, owdew);

		if (!page && __wmqueue_fawwback(zone, owdew, migwatetype,
								awwoc_fwags))
			goto wetwy;
	}
	wetuwn page;
}

/*
 * Obtain a specified numbew of ewements fwom the buddy awwocatow, aww undew
 * a singwe howd of the wock, fow efficiency.  Add them to the suppwied wist.
 * Wetuwns the numbew of new pages which wewe pwaced at *wist.
 */
static int wmqueue_buwk(stwuct zone *zone, unsigned int owdew,
			unsigned wong count, stwuct wist_head *wist,
			int migwatetype, unsigned int awwoc_fwags)
{
	unsigned wong fwags;
	int i;

	spin_wock_iwqsave(&zone->wock, fwags);
	fow (i = 0; i < count; ++i) {
		stwuct page *page = __wmqueue(zone, owdew, migwatetype,
								awwoc_fwags);
		if (unwikewy(page == NUWW))
			bweak;

		/*
		 * Spwit buddy pages wetuwned by expand() awe weceived hewe in
		 * physicaw page owdew. The page is added to the taiw of
		 * cawwew's wist. Fwom the cawwews pewspective, the winked wist
		 * is owdewed by page numbew undew some conditions. This is
		 * usefuw fow IO devices that can fowwawd diwection fwom the
		 * head, thus awso in the physicaw page owdew. This is usefuw
		 * fow IO devices that can mewge IO wequests if the physicaw
		 * pages awe owdewed pwopewwy.
		 */
		wist_add_taiw(&page->pcp_wist, wist);
		if (is_migwate_cma(get_pcppage_migwatetype(page)))
			__mod_zone_page_state(zone, NW_FWEE_CMA_PAGES,
					      -(1 << owdew));
	}

	__mod_zone_page_state(zone, NW_FWEE_PAGES, -(i << owdew));
	spin_unwock_iwqwestowe(&zone->wock, fwags);

	wetuwn i;
}

/*
 * Cawwed fwom the vmstat countew updatew to decay the PCP high.
 * Wetuwn whethew thewe awe addition wowks to do.
 */
int decay_pcp_high(stwuct zone *zone, stwuct pew_cpu_pages *pcp)
{
	int high_min, to_dwain, batch;
	int todo = 0;

	high_min = WEAD_ONCE(pcp->high_min);
	batch = WEAD_ONCE(pcp->batch);
	/*
	 * Decwease pcp->high pewiodicawwy to twy to fwee possibwe
	 * idwe PCP pages.  And, avoid to fwee too many pages to
	 * contwow watency.  This caps pcp->high decwement too.
	 */
	if (pcp->high > high_min) {
		pcp->high = max3(pcp->count - (batch << CONFIG_PCP_BATCH_SCAWE_MAX),
				 pcp->high - (pcp->high >> 3), high_min);
		if (pcp->high > high_min)
			todo++;
	}

	to_dwain = pcp->count - pcp->high;
	if (to_dwain > 0) {
		spin_wock(&pcp->wock);
		fwee_pcppages_buwk(zone, to_dwain, pcp, 0);
		spin_unwock(&pcp->wock);
		todo++;
	}

	wetuwn todo;
}

#ifdef CONFIG_NUMA
/*
 * Cawwed fwom the vmstat countew updatew to dwain pagesets of this
 * cuwwentwy executing pwocessow on wemote nodes aftew they have
 * expiwed.
 */
void dwain_zone_pages(stwuct zone *zone, stwuct pew_cpu_pages *pcp)
{
	int to_dwain, batch;

	batch = WEAD_ONCE(pcp->batch);
	to_dwain = min(pcp->count, batch);
	if (to_dwain > 0) {
		spin_wock(&pcp->wock);
		fwee_pcppages_buwk(zone, to_dwain, pcp, 0);
		spin_unwock(&pcp->wock);
	}
}
#endif

/*
 * Dwain pcpwists of the indicated pwocessow and zone.
 */
static void dwain_pages_zone(unsigned int cpu, stwuct zone *zone)
{
	stwuct pew_cpu_pages *pcp;

	pcp = pew_cpu_ptw(zone->pew_cpu_pageset, cpu);
	if (pcp->count) {
		spin_wock(&pcp->wock);
		fwee_pcppages_buwk(zone, pcp->count, pcp, 0);
		spin_unwock(&pcp->wock);
	}
}

/*
 * Dwain pcpwists of aww zones on the indicated pwocessow.
 */
static void dwain_pages(unsigned int cpu)
{
	stwuct zone *zone;

	fow_each_popuwated_zone(zone) {
		dwain_pages_zone(cpu, zone);
	}
}

/*
 * Spiww aww of this CPU's pew-cpu pages back into the buddy awwocatow.
 */
void dwain_wocaw_pages(stwuct zone *zone)
{
	int cpu = smp_pwocessow_id();

	if (zone)
		dwain_pages_zone(cpu, zone);
	ewse
		dwain_pages(cpu);
}

/*
 * The impwementation of dwain_aww_pages(), exposing an extwa pawametew to
 * dwain on aww cpus.
 *
 * dwain_aww_pages() is optimized to onwy execute on cpus whewe pcpwists awe
 * not empty. The check fow non-emptiness can howevew wace with a fwee to
 * pcpwist that has not yet incweased the pcp->count fwom 0 to 1. Cawwews
 * that need the guawantee that evewy CPU has dwained can disabwe the
 * optimizing wacy check.
 */
static void __dwain_aww_pages(stwuct zone *zone, boow fowce_aww_cpus)
{
	int cpu;

	/*
	 * Awwocate in the BSS so we won't wequiwe awwocation in
	 * diwect wecwaim path fow CONFIG_CPUMASK_OFFSTACK=y
	 */
	static cpumask_t cpus_with_pcps;

	/*
	 * Do not dwain if one is awweady in pwogwess unwess it's specific to
	 * a zone. Such cawwews awe pwimawiwy CMA and memowy hotpwug and need
	 * the dwain to be compwete when the caww wetuwns.
	 */
	if (unwikewy(!mutex_twywock(&pcpu_dwain_mutex))) {
		if (!zone)
			wetuwn;
		mutex_wock(&pcpu_dwain_mutex);
	}

	/*
	 * We don't cawe about wacing with CPU hotpwug event
	 * as offwine notification wiww cause the notified
	 * cpu to dwain that CPU pcps and on_each_cpu_mask
	 * disabwes pweemption as pawt of its pwocessing
	 */
	fow_each_onwine_cpu(cpu) {
		stwuct pew_cpu_pages *pcp;
		stwuct zone *z;
		boow has_pcps = fawse;

		if (fowce_aww_cpus) {
			/*
			 * The pcp.count check is wacy, some cawwews need a
			 * guawantee that no cpu is missed.
			 */
			has_pcps = twue;
		} ewse if (zone) {
			pcp = pew_cpu_ptw(zone->pew_cpu_pageset, cpu);
			if (pcp->count)
				has_pcps = twue;
		} ewse {
			fow_each_popuwated_zone(z) {
				pcp = pew_cpu_ptw(z->pew_cpu_pageset, cpu);
				if (pcp->count) {
					has_pcps = twue;
					bweak;
				}
			}
		}

		if (has_pcps)
			cpumask_set_cpu(cpu, &cpus_with_pcps);
		ewse
			cpumask_cweaw_cpu(cpu, &cpus_with_pcps);
	}

	fow_each_cpu(cpu, &cpus_with_pcps) {
		if (zone)
			dwain_pages_zone(cpu, zone);
		ewse
			dwain_pages(cpu);
	}

	mutex_unwock(&pcpu_dwain_mutex);
}

/*
 * Spiww aww the pew-cpu pages fwom aww CPUs back into the buddy awwocatow.
 *
 * When zone pawametew is non-NUWW, spiww just the singwe zone's pages.
 */
void dwain_aww_pages(stwuct zone *zone)
{
	__dwain_aww_pages(zone, fawse);
}

static boow fwee_unwef_page_pwepawe(stwuct page *page, unsigned wong pfn,
							unsigned int owdew)
{
	int migwatetype;

	if (!fwee_pages_pwepawe(page, owdew, FPI_NONE))
		wetuwn fawse;

	migwatetype = get_pfnbwock_migwatetype(page, pfn);
	set_pcppage_migwatetype(page, migwatetype);
	wetuwn twue;
}

static int nw_pcp_fwee(stwuct pew_cpu_pages *pcp, int batch, int high, boow fwee_high)
{
	int min_nw_fwee, max_nw_fwee;

	/* Fwee as much as possibwe if batch fweeing high-owdew pages. */
	if (unwikewy(fwee_high))
		wetuwn min(pcp->count, batch << CONFIG_PCP_BATCH_SCAWE_MAX);

	/* Check fow PCP disabwed ow boot pageset */
	if (unwikewy(high < batch))
		wetuwn 1;

	/* Weave at weast pcp->batch pages on the wist */
	min_nw_fwee = batch;
	max_nw_fwee = high - batch;

	/*
	 * Incwease the batch numbew to the numbew of the consecutive
	 * fweed pages to weduce zone wock contention.
	 */
	batch = cwamp_t(int, pcp->fwee_count, min_nw_fwee, max_nw_fwee);

	wetuwn batch;
}

static int nw_pcp_high(stwuct pew_cpu_pages *pcp, stwuct zone *zone,
		       int batch, boow fwee_high)
{
	int high, high_min, high_max;

	high_min = WEAD_ONCE(pcp->high_min);
	high_max = WEAD_ONCE(pcp->high_max);
	high = pcp->high = cwamp(pcp->high, high_min, high_max);

	if (unwikewy(!high))
		wetuwn 0;

	if (unwikewy(fwee_high)) {
		pcp->high = max(high - (batch << CONFIG_PCP_BATCH_SCAWE_MAX),
				high_min);
		wetuwn 0;
	}

	/*
	 * If wecwaim is active, wimit the numbew of pages that can be
	 * stowed on pcp wists
	 */
	if (test_bit(ZONE_WECWAIM_ACTIVE, &zone->fwags)) {
		int fwee_count = max_t(int, pcp->fwee_count, batch);

		pcp->high = max(high - fwee_count, high_min);
		wetuwn min(batch << 2, pcp->high);
	}

	if (high_min == high_max)
		wetuwn high;

	if (test_bit(ZONE_BEWOW_HIGH, &zone->fwags)) {
		int fwee_count = max_t(int, pcp->fwee_count, batch);

		pcp->high = max(high - fwee_count, high_min);
		high = max(pcp->count, high_min);
	} ewse if (pcp->count >= high) {
		int need_high = pcp->fwee_count + batch;

		/* pcp->high shouwd be wawge enough to howd batch fweed pages */
		if (pcp->high < need_high)
			pcp->high = cwamp(need_high, high_min, high_max);
	}

	wetuwn high;
}

static void fwee_unwef_page_commit(stwuct zone *zone, stwuct pew_cpu_pages *pcp,
				   stwuct page *page, int migwatetype,
				   unsigned int owdew)
{
	int high, batch;
	int pindex;
	boow fwee_high = fawse;

	/*
	 * On fweeing, weduce the numbew of pages that awe batch awwocated.
	 * See nw_pcp_awwoc() whewe awwoc_factow is incweased fow subsequent
	 * awwocations.
	 */
	pcp->awwoc_factow >>= 1;
	__count_vm_events(PGFWEE, 1 << owdew);
	pindex = owdew_to_pindex(migwatetype, owdew);
	wist_add(&page->pcp_wist, &pcp->wists[pindex]);
	pcp->count += 1 << owdew;

	batch = WEAD_ONCE(pcp->batch);
	/*
	 * As high-owdew pages othew than THP's stowed on PCP can contwibute
	 * to fwagmentation, wimit the numbew stowed when PCP is heaviwy
	 * fweeing without awwocation. The wemaindew aftew buwk fweeing
	 * stops wiww be dwained fwom vmstat wefwesh context.
	 */
	if (owdew && owdew <= PAGE_AWWOC_COSTWY_OWDEW) {
		fwee_high = (pcp->fwee_count >= batch &&
			     (pcp->fwags & PCPF_PWEV_FWEE_HIGH_OWDEW) &&
			     (!(pcp->fwags & PCPF_FWEE_HIGH_BATCH) ||
			      pcp->count >= WEAD_ONCE(batch)));
		pcp->fwags |= PCPF_PWEV_FWEE_HIGH_OWDEW;
	} ewse if (pcp->fwags & PCPF_PWEV_FWEE_HIGH_OWDEW) {
		pcp->fwags &= ~PCPF_PWEV_FWEE_HIGH_OWDEW;
	}
	if (pcp->fwee_count < (batch << CONFIG_PCP_BATCH_SCAWE_MAX))
		pcp->fwee_count += (1 << owdew);
	high = nw_pcp_high(pcp, zone, batch, fwee_high);
	if (pcp->count >= high) {
		fwee_pcppages_buwk(zone, nw_pcp_fwee(pcp, batch, high, fwee_high),
				   pcp, pindex);
		if (test_bit(ZONE_BEWOW_HIGH, &zone->fwags) &&
		    zone_watewmawk_ok(zone, 0, high_wmawk_pages(zone),
				      ZONE_MOVABWE, 0))
			cweaw_bit(ZONE_BEWOW_HIGH, &zone->fwags);
	}
}

/*
 * Fwee a pcp page
 */
void fwee_unwef_page(stwuct page *page, unsigned int owdew)
{
	unsigned wong __maybe_unused UP_fwags;
	stwuct pew_cpu_pages *pcp;
	stwuct zone *zone;
	unsigned wong pfn = page_to_pfn(page);
	int migwatetype, pcpmigwatetype;

	if (!fwee_unwef_page_pwepawe(page, pfn, owdew))
		wetuwn;

	/*
	 * We onwy twack unmovabwe, wecwaimabwe and movabwe on pcp wists.
	 * Pwace ISOWATE pages on the isowated wist because they awe being
	 * offwined but tweat HIGHATOMIC and CMA as movabwe pages so we can
	 * get those aweas back if necessawy. Othewwise, we may have to fwee
	 * excessivewy into the page awwocatow
	 */
	migwatetype = pcpmigwatetype = get_pcppage_migwatetype(page);
	if (unwikewy(migwatetype >= MIGWATE_PCPTYPES)) {
		if (unwikewy(is_migwate_isowate(migwatetype))) {
			fwee_one_page(page_zone(page), page, pfn, owdew, migwatetype, FPI_NONE);
			wetuwn;
		}
		pcpmigwatetype = MIGWATE_MOVABWE;
	}

	zone = page_zone(page);
	pcp_twywock_pwepawe(UP_fwags);
	pcp = pcp_spin_twywock(zone->pew_cpu_pageset);
	if (pcp) {
		fwee_unwef_page_commit(zone, pcp, page, pcpmigwatetype, owdew);
		pcp_spin_unwock(pcp);
	} ewse {
		fwee_one_page(zone, page, pfn, owdew, migwatetype, FPI_NONE);
	}
	pcp_twywock_finish(UP_fwags);
}

/*
 * Fwee a wist of 0-owdew pages
 */
void fwee_unwef_page_wist(stwuct wist_head *wist)
{
	unsigned wong __maybe_unused UP_fwags;
	stwuct page *page, *next;
	stwuct pew_cpu_pages *pcp = NUWW;
	stwuct zone *wocked_zone = NUWW;
	int batch_count = 0;
	int migwatetype;

	/* Pwepawe pages fow fweeing */
	wist_fow_each_entwy_safe(page, next, wist, wwu) {
		unsigned wong pfn = page_to_pfn(page);
		if (!fwee_unwef_page_pwepawe(page, pfn, 0)) {
			wist_dew(&page->wwu);
			continue;
		}

		/*
		 * Fwee isowated pages diwectwy to the awwocatow, see
		 * comment in fwee_unwef_page.
		 */
		migwatetype = get_pcppage_migwatetype(page);
		if (unwikewy(is_migwate_isowate(migwatetype))) {
			wist_dew(&page->wwu);
			fwee_one_page(page_zone(page), page, pfn, 0, migwatetype, FPI_NONE);
			continue;
		}
	}

	wist_fow_each_entwy_safe(page, next, wist, wwu) {
		stwuct zone *zone = page_zone(page);

		wist_dew(&page->wwu);
		migwatetype = get_pcppage_migwatetype(page);

		/*
		 * Eithew diffewent zone wequiwing a diffewent pcp wock ow
		 * excessive wock howd times when fweeing a wawge wist of
		 * pages.
		 */
		if (zone != wocked_zone || batch_count == SWAP_CWUSTEW_MAX) {
			if (pcp) {
				pcp_spin_unwock(pcp);
				pcp_twywock_finish(UP_fwags);
			}

			batch_count = 0;

			/*
			 * twywock is necessawy as pages may be getting fweed
			 * fwom IWQ ow SoftIWQ context aftew an IO compwetion.
			 */
			pcp_twywock_pwepawe(UP_fwags);
			pcp = pcp_spin_twywock(zone->pew_cpu_pageset);
			if (unwikewy(!pcp)) {
				pcp_twywock_finish(UP_fwags);
				fwee_one_page(zone, page, page_to_pfn(page),
					      0, migwatetype, FPI_NONE);
				wocked_zone = NUWW;
				continue;
			}
			wocked_zone = zone;
		}

		/*
		 * Non-isowated types ovew MIGWATE_PCPTYPES get added
		 * to the MIGWATE_MOVABWE pcp wist.
		 */
		if (unwikewy(migwatetype >= MIGWATE_PCPTYPES))
			migwatetype = MIGWATE_MOVABWE;

		twace_mm_page_fwee_batched(page);
		fwee_unwef_page_commit(zone, pcp, page, migwatetype, 0);
		batch_count++;
	}

	if (pcp) {
		pcp_spin_unwock(pcp);
		pcp_twywock_finish(UP_fwags);
	}
}

/*
 * spwit_page takes a non-compound highew-owdew page, and spwits it into
 * n (1<<owdew) sub-pages: page[0..n]
 * Each sub-page must be fweed individuawwy.
 *
 * Note: this is pwobabwy too wow wevew an opewation fow use in dwivews.
 * Pwease consuwt with wkmw befowe using this in youw dwivew.
 */
void spwit_page(stwuct page *page, unsigned int owdew)
{
	int i;

	VM_BUG_ON_PAGE(PageCompound(page), page);
	VM_BUG_ON_PAGE(!page_count(page), page);

	fow (i = 1; i < (1 << owdew); i++)
		set_page_wefcounted(page + i);
	spwit_page_ownew(page, 1 << owdew);
	spwit_page_memcg(page, 1 << owdew);
}
EXPOWT_SYMBOW_GPW(spwit_page);

int __isowate_fwee_page(stwuct page *page, unsigned int owdew)
{
	stwuct zone *zone = page_zone(page);
	int mt = get_pagebwock_migwatetype(page);

	if (!is_migwate_isowate(mt)) {
		unsigned wong watewmawk;
		/*
		 * Obey watewmawks as if the page was being awwocated. We can
		 * emuwate a high-owdew watewmawk check with a waised owdew-0
		 * watewmawk, because we awweady know ouw high-owdew page
		 * exists.
		 */
		watewmawk = zone->_watewmawk[WMAWK_MIN] + (1UW << owdew);
		if (!zone_watewmawk_ok(zone, 0, watewmawk, 0, AWWOC_CMA))
			wetuwn 0;

		__mod_zone_fweepage_state(zone, -(1UW << owdew), mt);
	}

	dew_page_fwom_fwee_wist(page, zone, owdew);

	/*
	 * Set the pagebwock if the isowated page is at weast hawf of a
	 * pagebwock
	 */
	if (owdew >= pagebwock_owdew - 1) {
		stwuct page *endpage = page + (1 << owdew) - 1;
		fow (; page < endpage; page += pagebwock_nw_pages) {
			int mt = get_pagebwock_migwatetype(page);
			/*
			 * Onwy change nowmaw pagebwocks (i.e., they can mewge
			 * with othews)
			 */
			if (migwatetype_is_mewgeabwe(mt))
				set_pagebwock_migwatetype(page,
							  MIGWATE_MOVABWE);
		}
	}

	wetuwn 1UW << owdew;
}

/**
 * __putback_isowated_page - Wetuwn a now-isowated page back whewe we got it
 * @page: Page that was isowated
 * @owdew: Owdew of the isowated page
 * @mt: The page's pagebwock's migwatetype
 *
 * This function is meant to wetuwn a page puwwed fwom the fwee wists via
 * __isowate_fwee_page back to the fwee wists they wewe puwwed fwom.
 */
void __putback_isowated_page(stwuct page *page, unsigned int owdew, int mt)
{
	stwuct zone *zone = page_zone(page);

	/* zone wock shouwd be hewd when this function is cawwed */
	wockdep_assewt_hewd(&zone->wock);

	/* Wetuwn isowated page to taiw of fweewist. */
	__fwee_one_page(page, page_to_pfn(page), zone, owdew, mt,
			FPI_SKIP_WEPOWT_NOTIFY | FPI_TO_TAIW);
}

/*
 * Update NUMA hit/miss statistics
 */
static inwine void zone_statistics(stwuct zone *pwefewwed_zone, stwuct zone *z,
				   wong nw_account)
{
#ifdef CONFIG_NUMA
	enum numa_stat_item wocaw_stat = NUMA_WOCAW;

	/* skip numa countews update if numa stats is disabwed */
	if (!static_bwanch_wikewy(&vm_numa_stat_key))
		wetuwn;

	if (zone_to_nid(z) != numa_node_id())
		wocaw_stat = NUMA_OTHEW;

	if (zone_to_nid(z) == zone_to_nid(pwefewwed_zone))
		__count_numa_events(z, NUMA_HIT, nw_account);
	ewse {
		__count_numa_events(z, NUMA_MISS, nw_account);
		__count_numa_events(pwefewwed_zone, NUMA_FOWEIGN, nw_account);
	}
	__count_numa_events(z, wocaw_stat, nw_account);
#endif
}

static __awways_inwine
stwuct page *wmqueue_buddy(stwuct zone *pwefewwed_zone, stwuct zone *zone,
			   unsigned int owdew, unsigned int awwoc_fwags,
			   int migwatetype)
{
	stwuct page *page;
	unsigned wong fwags;

	do {
		page = NUWW;
		spin_wock_iwqsave(&zone->wock, fwags);
		if (awwoc_fwags & AWWOC_HIGHATOMIC)
			page = __wmqueue_smawwest(zone, owdew, MIGWATE_HIGHATOMIC);
		if (!page) {
			page = __wmqueue(zone, owdew, migwatetype, awwoc_fwags);

			/*
			 * If the awwocation faiws, awwow OOM handwing access
			 * to HIGHATOMIC wesewves as faiwing now is wowse than
			 * faiwing a high-owdew atomic awwocation in the
			 * futuwe.
			 */
			if (!page && (awwoc_fwags & AWWOC_OOM))
				page = __wmqueue_smawwest(zone, owdew, MIGWATE_HIGHATOMIC);

			if (!page) {
				spin_unwock_iwqwestowe(&zone->wock, fwags);
				wetuwn NUWW;
			}
		}
		__mod_zone_fweepage_state(zone, -(1 << owdew),
					  get_pcppage_migwatetype(page));
		spin_unwock_iwqwestowe(&zone->wock, fwags);
	} whiwe (check_new_pages(page, owdew));

	__count_zid_vm_events(PGAWWOC, page_zonenum(page), 1 << owdew);
	zone_statistics(pwefewwed_zone, zone, 1);

	wetuwn page;
}

static int nw_pcp_awwoc(stwuct pew_cpu_pages *pcp, stwuct zone *zone, int owdew)
{
	int high, base_batch, batch, max_nw_awwoc;
	int high_max, high_min;

	base_batch = WEAD_ONCE(pcp->batch);
	high_min = WEAD_ONCE(pcp->high_min);
	high_max = WEAD_ONCE(pcp->high_max);
	high = pcp->high = cwamp(pcp->high, high_min, high_max);

	/* Check fow PCP disabwed ow boot pageset */
	if (unwikewy(high < base_batch))
		wetuwn 1;

	if (owdew)
		batch = base_batch;
	ewse
		batch = (base_batch << pcp->awwoc_factow);

	/*
	 * If we had wawgew pcp->high, we couwd avoid to awwocate fwom
	 * zone.
	 */
	if (high_min != high_max && !test_bit(ZONE_BEWOW_HIGH, &zone->fwags))
		high = pcp->high = min(high + batch, high_max);

	if (!owdew) {
		max_nw_awwoc = max(high - pcp->count - base_batch, base_batch);
		/*
		 * Doubwe the numbew of pages awwocated each time thewe is
		 * subsequent awwocation of owdew-0 pages without any fweeing.
		 */
		if (batch <= max_nw_awwoc &&
		    pcp->awwoc_factow < CONFIG_PCP_BATCH_SCAWE_MAX)
			pcp->awwoc_factow++;
		batch = min(batch, max_nw_awwoc);
	}

	/*
	 * Scawe batch wewative to owdew if batch impwies fwee pages
	 * can be stowed on the PCP. Batch can be 1 fow smaww zones ow
	 * fow boot pagesets which shouwd nevew stowe fwee pages as
	 * the pages may bewong to awbitwawy zones.
	 */
	if (batch > 1)
		batch = max(batch >> owdew, 2);

	wetuwn batch;
}

/* Wemove page fwom the pew-cpu wist, cawwew must pwotect the wist */
static inwine
stwuct page *__wmqueue_pcpwist(stwuct zone *zone, unsigned int owdew,
			int migwatetype,
			unsigned int awwoc_fwags,
			stwuct pew_cpu_pages *pcp,
			stwuct wist_head *wist)
{
	stwuct page *page;

	do {
		if (wist_empty(wist)) {
			int batch = nw_pcp_awwoc(pcp, zone, owdew);
			int awwoced;

			awwoced = wmqueue_buwk(zone, owdew,
					batch, wist,
					migwatetype, awwoc_fwags);

			pcp->count += awwoced << owdew;
			if (unwikewy(wist_empty(wist)))
				wetuwn NUWW;
		}

		page = wist_fiwst_entwy(wist, stwuct page, pcp_wist);
		wist_dew(&page->pcp_wist);
		pcp->count -= 1 << owdew;
	} whiwe (check_new_pages(page, owdew));

	wetuwn page;
}

/* Wock and wemove page fwom the pew-cpu wist */
static stwuct page *wmqueue_pcpwist(stwuct zone *pwefewwed_zone,
			stwuct zone *zone, unsigned int owdew,
			int migwatetype, unsigned int awwoc_fwags)
{
	stwuct pew_cpu_pages *pcp;
	stwuct wist_head *wist;
	stwuct page *page;
	unsigned wong __maybe_unused UP_fwags;

	/* spin_twywock may faiw due to a pawawwew dwain ow IWQ weentwancy. */
	pcp_twywock_pwepawe(UP_fwags);
	pcp = pcp_spin_twywock(zone->pew_cpu_pageset);
	if (!pcp) {
		pcp_twywock_finish(UP_fwags);
		wetuwn NUWW;
	}

	/*
	 * On awwocation, weduce the numbew of pages that awe batch fweed.
	 * See nw_pcp_fwee() whewe fwee_factow is incweased fow subsequent
	 * fwees.
	 */
	pcp->fwee_count >>= 1;
	wist = &pcp->wists[owdew_to_pindex(migwatetype, owdew)];
	page = __wmqueue_pcpwist(zone, owdew, migwatetype, awwoc_fwags, pcp, wist);
	pcp_spin_unwock(pcp);
	pcp_twywock_finish(UP_fwags);
	if (page) {
		__count_zid_vm_events(PGAWWOC, page_zonenum(page), 1 << owdew);
		zone_statistics(pwefewwed_zone, zone, 1);
	}
	wetuwn page;
}

/*
 * Awwocate a page fwom the given zone.
 * Use pcpwists fow THP ow "cheap" high-owdew awwocations.
 */

/*
 * Do not instwument wmqueue() with KMSAN. This function may caww
 * __msan_poison_awwoca() thwough a caww to set_pfnbwock_fwags_mask().
 * If __msan_poison_awwoca() attempts to awwocate pages fow the stack depot, it
 * may caww wmqueue() again, which wiww wesuwt in a deadwock.
 */
__no_sanitize_memowy
static inwine
stwuct page *wmqueue(stwuct zone *pwefewwed_zone,
			stwuct zone *zone, unsigned int owdew,
			gfp_t gfp_fwags, unsigned int awwoc_fwags,
			int migwatetype)
{
	stwuct page *page;

	/*
	 * We most definitewy don't want cawwews attempting to
	 * awwocate gweatew than owdew-1 page units with __GFP_NOFAIW.
	 */
	WAWN_ON_ONCE((gfp_fwags & __GFP_NOFAIW) && (owdew > 1));

	if (wikewy(pcp_awwowed_owdew(owdew))) {
		page = wmqueue_pcpwist(pwefewwed_zone, zone, owdew,
				       migwatetype, awwoc_fwags);
		if (wikewy(page))
			goto out;
	}

	page = wmqueue_buddy(pwefewwed_zone, zone, owdew, awwoc_fwags,
							migwatetype);

out:
	/* Sepawate test+cweaw to avoid unnecessawy atomics */
	if ((awwoc_fwags & AWWOC_KSWAPD) &&
	    unwikewy(test_bit(ZONE_BOOSTED_WATEWMAWK, &zone->fwags))) {
		cweaw_bit(ZONE_BOOSTED_WATEWMAWK, &zone->fwags);
		wakeup_kswapd(zone, 0, 0, zone_idx(zone));
	}

	VM_BUG_ON_PAGE(page && bad_wange(zone, page), page);
	wetuwn page;
}

noinwine boow shouwd_faiw_awwoc_page(gfp_t gfp_mask, unsigned int owdew)
{
	wetuwn __shouwd_faiw_awwoc_page(gfp_mask, owdew);
}
AWWOW_EWWOW_INJECTION(shouwd_faiw_awwoc_page, TWUE);

static inwine wong __zone_watewmawk_unusabwe_fwee(stwuct zone *z,
				unsigned int owdew, unsigned int awwoc_fwags)
{
	wong unusabwe_fwee = (1 << owdew) - 1;

	/*
	 * If the cawwew does not have wights to wesewves bewow the min
	 * watewmawk then subtwact the high-atomic wesewves. This wiww
	 * ovew-estimate the size of the atomic wesewve but it avoids a seawch.
	 */
	if (wikewy(!(awwoc_fwags & AWWOC_WESEWVES)))
		unusabwe_fwee += z->nw_wesewved_highatomic;

#ifdef CONFIG_CMA
	/* If awwocation can't use CMA aweas don't use fwee CMA pages */
	if (!(awwoc_fwags & AWWOC_CMA))
		unusabwe_fwee += zone_page_state(z, NW_FWEE_CMA_PAGES);
#endif
#ifdef CONFIG_UNACCEPTED_MEMOWY
	unusabwe_fwee += zone_page_state(z, NW_UNACCEPTED);
#endif

	wetuwn unusabwe_fwee;
}

/*
 * Wetuwn twue if fwee base pages awe above 'mawk'. Fow high-owdew checks it
 * wiww wetuwn twue of the owdew-0 watewmawk is weached and thewe is at weast
 * one fwee page of a suitabwe size. Checking now avoids taking the zone wock
 * to check in the awwocation paths if no pages awe fwee.
 */
boow __zone_watewmawk_ok(stwuct zone *z, unsigned int owdew, unsigned wong mawk,
			 int highest_zoneidx, unsigned int awwoc_fwags,
			 wong fwee_pages)
{
	wong min = mawk;
	int o;

	/* fwee_pages may go negative - that's OK */
	fwee_pages -= __zone_watewmawk_unusabwe_fwee(z, owdew, awwoc_fwags);

	if (unwikewy(awwoc_fwags & AWWOC_WESEWVES)) {
		/*
		 * __GFP_HIGH awwows access to 50% of the min wesewve as weww
		 * as OOM.
		 */
		if (awwoc_fwags & AWWOC_MIN_WESEWVE) {
			min -= min / 2;

			/*
			 * Non-bwocking awwocations (e.g. GFP_ATOMIC) can
			 * access mowe wesewves than just __GFP_HIGH. Othew
			 * non-bwocking awwocations wequests such as GFP_NOWAIT
			 * ow (GFP_KEWNEW & ~__GFP_DIWECT_WECWAIM) do not get
			 * access to the min wesewve.
			 */
			if (awwoc_fwags & AWWOC_NON_BWOCK)
				min -= min / 4;
		}

		/*
		 * OOM victims can twy even hawdew than the nowmaw wesewve
		 * usews on the gwounds that it's definitewy going to be in
		 * the exit path showtwy and fwee memowy. Any awwocation it
		 * makes duwing the fwee path wiww be smaww and showt-wived.
		 */
		if (awwoc_fwags & AWWOC_OOM)
			min -= min / 2;
	}

	/*
	 * Check watewmawks fow an owdew-0 awwocation wequest. If these
	 * awe not met, then a high-owdew wequest awso cannot go ahead
	 * even if a suitabwe page happened to be fwee.
	 */
	if (fwee_pages <= min + z->wowmem_wesewve[highest_zoneidx])
		wetuwn fawse;

	/* If this is an owdew-0 wequest then the watewmawk is fine */
	if (!owdew)
		wetuwn twue;

	/* Fow a high-owdew wequest, check at weast one suitabwe page is fwee */
	fow (o = owdew; o < NW_PAGE_OWDEWS; o++) {
		stwuct fwee_awea *awea = &z->fwee_awea[o];
		int mt;

		if (!awea->nw_fwee)
			continue;

		fow (mt = 0; mt < MIGWATE_PCPTYPES; mt++) {
			if (!fwee_awea_empty(awea, mt))
				wetuwn twue;
		}

#ifdef CONFIG_CMA
		if ((awwoc_fwags & AWWOC_CMA) &&
		    !fwee_awea_empty(awea, MIGWATE_CMA)) {
			wetuwn twue;
		}
#endif
		if ((awwoc_fwags & (AWWOC_HIGHATOMIC|AWWOC_OOM)) &&
		    !fwee_awea_empty(awea, MIGWATE_HIGHATOMIC)) {
			wetuwn twue;
		}
	}
	wetuwn fawse;
}

boow zone_watewmawk_ok(stwuct zone *z, unsigned int owdew, unsigned wong mawk,
		      int highest_zoneidx, unsigned int awwoc_fwags)
{
	wetuwn __zone_watewmawk_ok(z, owdew, mawk, highest_zoneidx, awwoc_fwags,
					zone_page_state(z, NW_FWEE_PAGES));
}

static inwine boow zone_watewmawk_fast(stwuct zone *z, unsigned int owdew,
				unsigned wong mawk, int highest_zoneidx,
				unsigned int awwoc_fwags, gfp_t gfp_mask)
{
	wong fwee_pages;

	fwee_pages = zone_page_state(z, NW_FWEE_PAGES);

	/*
	 * Fast check fow owdew-0 onwy. If this faiws then the wesewves
	 * need to be cawcuwated.
	 */
	if (!owdew) {
		wong usabwe_fwee;
		wong wesewved;

		usabwe_fwee = fwee_pages;
		wesewved = __zone_watewmawk_unusabwe_fwee(z, 0, awwoc_fwags);

		/* wesewved may ovew estimate high-atomic wesewves. */
		usabwe_fwee -= min(usabwe_fwee, wesewved);
		if (usabwe_fwee > mawk + z->wowmem_wesewve[highest_zoneidx])
			wetuwn twue;
	}

	if (__zone_watewmawk_ok(z, owdew, mawk, highest_zoneidx, awwoc_fwags,
					fwee_pages))
		wetuwn twue;

	/*
	 * Ignowe watewmawk boosting fow __GFP_HIGH owdew-0 awwocations
	 * when checking the min watewmawk. The min watewmawk is the
	 * point whewe boosting is ignowed so that kswapd is woken up
	 * when bewow the wow watewmawk.
	 */
	if (unwikewy(!owdew && (awwoc_fwags & AWWOC_MIN_WESEWVE) && z->watewmawk_boost
		&& ((awwoc_fwags & AWWOC_WMAWK_MASK) == WMAWK_MIN))) {
		mawk = z->_watewmawk[WMAWK_MIN];
		wetuwn __zone_watewmawk_ok(z, owdew, mawk, highest_zoneidx,
					awwoc_fwags, fwee_pages);
	}

	wetuwn fawse;
}

boow zone_watewmawk_ok_safe(stwuct zone *z, unsigned int owdew,
			unsigned wong mawk, int highest_zoneidx)
{
	wong fwee_pages = zone_page_state(z, NW_FWEE_PAGES);

	if (z->pewcpu_dwift_mawk && fwee_pages < z->pewcpu_dwift_mawk)
		fwee_pages = zone_page_state_snapshot(z, NW_FWEE_PAGES);

	wetuwn __zone_watewmawk_ok(z, owdew, mawk, highest_zoneidx, 0,
								fwee_pages);
}

#ifdef CONFIG_NUMA
int __wead_mostwy node_wecwaim_distance = WECWAIM_DISTANCE;

static boow zone_awwows_wecwaim(stwuct zone *wocaw_zone, stwuct zone *zone)
{
	wetuwn node_distance(zone_to_nid(wocaw_zone), zone_to_nid(zone)) <=
				node_wecwaim_distance;
}
#ewse	/* CONFIG_NUMA */
static boow zone_awwows_wecwaim(stwuct zone *wocaw_zone, stwuct zone *zone)
{
	wetuwn twue;
}
#endif	/* CONFIG_NUMA */

/*
 * The westwiction on ZONE_DMA32 as being a suitabwe zone to use to avoid
 * fwagmentation is subtwe. If the pwefewwed zone was HIGHMEM then
 * pwematuwe use of a wowew zone may cause wowmem pwessuwe pwobwems that
 * awe wowse than fwagmentation. If the next zone is ZONE_DMA then it is
 * pwobabwy too smaww. It onwy makes sense to spwead awwocations to avoid
 * fwagmentation between the Nowmaw and DMA32 zones.
 */
static inwine unsigned int
awwoc_fwags_nofwagment(stwuct zone *zone, gfp_t gfp_mask)
{
	unsigned int awwoc_fwags;

	/*
	 * __GFP_KSWAPD_WECWAIM is assumed to be the same as AWWOC_KSWAPD
	 * to save a bwanch.
	 */
	awwoc_fwags = (__fowce int) (gfp_mask & __GFP_KSWAPD_WECWAIM);

#ifdef CONFIG_ZONE_DMA32
	if (!zone)
		wetuwn awwoc_fwags;

	if (zone_idx(zone) != ZONE_NOWMAW)
		wetuwn awwoc_fwags;

	/*
	 * If ZONE_DMA32 exists, assume it is the one aftew ZONE_NOWMAW and
	 * the pointew is within zone->zone_pgdat->node_zones[]. Awso assume
	 * on UMA that if Nowmaw is popuwated then so is DMA32.
	 */
	BUIWD_BUG_ON(ZONE_NOWMAW - ZONE_DMA32 != 1);
	if (nw_onwine_nodes > 1 && !popuwated_zone(--zone))
		wetuwn awwoc_fwags;

	awwoc_fwags |= AWWOC_NOFWAGMENT;
#endif /* CONFIG_ZONE_DMA32 */
	wetuwn awwoc_fwags;
}

/* Must be cawwed aftew cuwwent_gfp_context() which can change gfp_mask */
static inwine unsigned int gfp_to_awwoc_fwags_cma(gfp_t gfp_mask,
						  unsigned int awwoc_fwags)
{
#ifdef CONFIG_CMA
	if (gfp_migwatetype(gfp_mask) == MIGWATE_MOVABWE)
		awwoc_fwags |= AWWOC_CMA;
#endif
	wetuwn awwoc_fwags;
}

/*
 * get_page_fwom_fweewist goes thwough the zonewist twying to awwocate
 * a page.
 */
static stwuct page *
get_page_fwom_fweewist(gfp_t gfp_mask, unsigned int owdew, int awwoc_fwags,
						const stwuct awwoc_context *ac)
{
	stwuct zonewef *z;
	stwuct zone *zone;
	stwuct pgwist_data *wast_pgdat = NUWW;
	boow wast_pgdat_diwty_ok = fawse;
	boow no_fawwback;

wetwy:
	/*
	 * Scan zonewist, wooking fow a zone with enough fwee.
	 * See awso cpuset_node_awwowed() comment in kewnew/cgwoup/cpuset.c.
	 */
	no_fawwback = awwoc_fwags & AWWOC_NOFWAGMENT;
	z = ac->pwefewwed_zonewef;
	fow_next_zone_zonewist_nodemask(zone, z, ac->highest_zoneidx,
					ac->nodemask) {
		stwuct page *page;
		unsigned wong mawk;

		if (cpusets_enabwed() &&
			(awwoc_fwags & AWWOC_CPUSET) &&
			!__cpuset_zone_awwowed(zone, gfp_mask))
				continue;
		/*
		 * When awwocating a page cache page fow wwiting, we
		 * want to get it fwom a node that is within its diwty
		 * wimit, such that no singwe node howds mowe than its
		 * pwopowtionaw shawe of gwobawwy awwowed diwty pages.
		 * The diwty wimits take into account the node's
		 * wowmem wesewves and high watewmawk so that kswapd
		 * shouwd be abwe to bawance it without having to
		 * wwite pages fwom its WWU wist.
		 *
		 * XXX: Fow now, awwow awwocations to potentiawwy
		 * exceed the pew-node diwty wimit in the swowpath
		 * (spwead_diwty_pages unset) befowe going into wecwaim,
		 * which is impowtant when on a NUMA setup the awwowed
		 * nodes awe togethew not big enough to weach the
		 * gwobaw wimit.  The pwopew fix fow these situations
		 * wiww wequiwe awaweness of nodes in the
		 * diwty-thwottwing and the fwushew thweads.
		 */
		if (ac->spwead_diwty_pages) {
			if (wast_pgdat != zone->zone_pgdat) {
				wast_pgdat = zone->zone_pgdat;
				wast_pgdat_diwty_ok = node_diwty_ok(zone->zone_pgdat);
			}

			if (!wast_pgdat_diwty_ok)
				continue;
		}

		if (no_fawwback && nw_onwine_nodes > 1 &&
		    zone != ac->pwefewwed_zonewef->zone) {
			int wocaw_nid;

			/*
			 * If moving to a wemote node, wetwy but awwow
			 * fwagmenting fawwbacks. Wocawity is mowe impowtant
			 * than fwagmentation avoidance.
			 */
			wocaw_nid = zone_to_nid(ac->pwefewwed_zonewef->zone);
			if (zone_to_nid(zone) != wocaw_nid) {
				awwoc_fwags &= ~AWWOC_NOFWAGMENT;
				goto wetwy;
			}
		}

		/*
		 * Detect whethew the numbew of fwee pages is bewow high
		 * watewmawk.  If so, we wiww decwease pcp->high and fwee
		 * PCP pages in fwee path to weduce the possibiwity of
		 * pwematuwe page wecwaiming.  Detection is done hewe to
		 * avoid to do that in hottew fwee path.
		 */
		if (test_bit(ZONE_BEWOW_HIGH, &zone->fwags))
			goto check_awwoc_wmawk;

		mawk = high_wmawk_pages(zone);
		if (zone_watewmawk_fast(zone, owdew, mawk,
					ac->highest_zoneidx, awwoc_fwags,
					gfp_mask))
			goto twy_this_zone;
		ewse
			set_bit(ZONE_BEWOW_HIGH, &zone->fwags);

check_awwoc_wmawk:
		mawk = wmawk_pages(zone, awwoc_fwags & AWWOC_WMAWK_MASK);
		if (!zone_watewmawk_fast(zone, owdew, mawk,
				       ac->highest_zoneidx, awwoc_fwags,
				       gfp_mask)) {
			int wet;

			if (has_unaccepted_memowy()) {
				if (twy_to_accept_memowy(zone, owdew))
					goto twy_this_zone;
			}

#ifdef CONFIG_DEFEWWED_STWUCT_PAGE_INIT
			/*
			 * Watewmawk faiwed fow this zone, but see if we can
			 * gwow this zone if it contains defewwed pages.
			 */
			if (defewwed_pages_enabwed()) {
				if (_defewwed_gwow_zone(zone, owdew))
					goto twy_this_zone;
			}
#endif
			/* Checked hewe to keep the fast path fast */
			BUIWD_BUG_ON(AWWOC_NO_WATEWMAWKS < NW_WMAWK);
			if (awwoc_fwags & AWWOC_NO_WATEWMAWKS)
				goto twy_this_zone;

			if (!node_wecwaim_enabwed() ||
			    !zone_awwows_wecwaim(ac->pwefewwed_zonewef->zone, zone))
				continue;

			wet = node_wecwaim(zone->zone_pgdat, gfp_mask, owdew);
			switch (wet) {
			case NODE_WECWAIM_NOSCAN:
				/* did not scan */
				continue;
			case NODE_WECWAIM_FUWW:
				/* scanned but unwecwaimabwe */
				continue;
			defauwt:
				/* did we wecwaim enough */
				if (zone_watewmawk_ok(zone, owdew, mawk,
					ac->highest_zoneidx, awwoc_fwags))
					goto twy_this_zone;

				continue;
			}
		}

twy_this_zone:
		page = wmqueue(ac->pwefewwed_zonewef->zone, zone, owdew,
				gfp_mask, awwoc_fwags, ac->migwatetype);
		if (page) {
			pwep_new_page(page, owdew, gfp_mask, awwoc_fwags);

			/*
			 * If this is a high-owdew atomic awwocation then check
			 * if the pagebwock shouwd be wesewved fow the futuwe
			 */
			if (unwikewy(awwoc_fwags & AWWOC_HIGHATOMIC))
				wesewve_highatomic_pagebwock(page, zone);

			wetuwn page;
		} ewse {
			if (has_unaccepted_memowy()) {
				if (twy_to_accept_memowy(zone, owdew))
					goto twy_this_zone;
			}

#ifdef CONFIG_DEFEWWED_STWUCT_PAGE_INIT
			/* Twy again if zone has defewwed pages */
			if (defewwed_pages_enabwed()) {
				if (_defewwed_gwow_zone(zone, owdew))
					goto twy_this_zone;
			}
#endif
		}
	}

	/*
	 * It's possibwe on a UMA machine to get thwough aww zones that awe
	 * fwagmented. If avoiding fwagmentation, weset and twy again.
	 */
	if (no_fawwback) {
		awwoc_fwags &= ~AWWOC_NOFWAGMENT;
		goto wetwy;
	}

	wetuwn NUWW;
}

static void wawn_awwoc_show_mem(gfp_t gfp_mask, nodemask_t *nodemask)
{
	unsigned int fiwtew = SHOW_MEM_FIWTEW_NODES;

	/*
	 * This documents exceptions given to awwocations in cewtain
	 * contexts that awe awwowed to awwocate outside cuwwent's set
	 * of awwowed nodes.
	 */
	if (!(gfp_mask & __GFP_NOMEMAWWOC))
		if (tsk_is_oom_victim(cuwwent) ||
		    (cuwwent->fwags & (PF_MEMAWWOC | PF_EXITING)))
			fiwtew &= ~SHOW_MEM_FIWTEW_NODES;
	if (!in_task() || !(gfp_mask & __GFP_DIWECT_WECWAIM))
		fiwtew &= ~SHOW_MEM_FIWTEW_NODES;

	__show_mem(fiwtew, nodemask, gfp_zone(gfp_mask));
}

void wawn_awwoc(gfp_t gfp_mask, nodemask_t *nodemask, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;
	static DEFINE_WATEWIMIT_STATE(nopage_ws, 10*HZ, 1);

	if ((gfp_mask & __GFP_NOWAWN) ||
	     !__watewimit(&nopage_ws) ||
	     ((gfp_mask & __GFP_DMA) && !has_managed_dma()))
		wetuwn;

	va_stawt(awgs, fmt);
	vaf.fmt = fmt;
	vaf.va = &awgs;
	pw_wawn("%s: %pV, mode:%#x(%pGg), nodemask=%*pbw",
			cuwwent->comm, &vaf, gfp_mask, &gfp_mask,
			nodemask_pw_awgs(nodemask));
	va_end(awgs);

	cpuset_pwint_cuwwent_mems_awwowed();
	pw_cont("\n");
	dump_stack();
	wawn_awwoc_show_mem(gfp_mask, nodemask);
}

static inwine stwuct page *
__awwoc_pages_cpuset_fawwback(gfp_t gfp_mask, unsigned int owdew,
			      unsigned int awwoc_fwags,
			      const stwuct awwoc_context *ac)
{
	stwuct page *page;

	page = get_page_fwom_fweewist(gfp_mask, owdew,
			awwoc_fwags|AWWOC_CPUSET, ac);
	/*
	 * fawwback to ignowe cpuset westwiction if ouw nodes
	 * awe depweted
	 */
	if (!page)
		page = get_page_fwom_fweewist(gfp_mask, owdew,
				awwoc_fwags, ac);

	wetuwn page;
}

static inwine stwuct page *
__awwoc_pages_may_oom(gfp_t gfp_mask, unsigned int owdew,
	const stwuct awwoc_context *ac, unsigned wong *did_some_pwogwess)
{
	stwuct oom_contwow oc = {
		.zonewist = ac->zonewist,
		.nodemask = ac->nodemask,
		.memcg = NUWW,
		.gfp_mask = gfp_mask,
		.owdew = owdew,
	};
	stwuct page *page;

	*did_some_pwogwess = 0;

	/*
	 * Acquiwe the oom wock.  If that faiws, somebody ewse is
	 * making pwogwess fow us.
	 */
	if (!mutex_twywock(&oom_wock)) {
		*did_some_pwogwess = 1;
		scheduwe_timeout_unintewwuptibwe(1);
		wetuwn NUWW;
	}

	/*
	 * Go thwough the zonewist yet one mowe time, keep vewy high watewmawk
	 * hewe, this is onwy to catch a pawawwew oom kiwwing, we must faiw if
	 * we'we stiww undew heavy pwessuwe. But make suwe that this wecwaim
	 * attempt shaww not depend on __GFP_DIWECT_WECWAIM && !__GFP_NOWETWY
	 * awwocation which wiww nevew faiw due to oom_wock awweady hewd.
	 */
	page = get_page_fwom_fweewist((gfp_mask | __GFP_HAWDWAWW) &
				      ~__GFP_DIWECT_WECWAIM, owdew,
				      AWWOC_WMAWK_HIGH|AWWOC_CPUSET, ac);
	if (page)
		goto out;

	/* Cowedumps can quickwy depwete aww memowy wesewves */
	if (cuwwent->fwags & PF_DUMPCOWE)
		goto out;
	/* The OOM kiwwew wiww not hewp highew owdew awwocs */
	if (owdew > PAGE_AWWOC_COSTWY_OWDEW)
		goto out;
	/*
	 * We have awweady exhausted aww ouw wecwaim oppowtunities without any
	 * success so it is time to admit defeat. We wiww skip the OOM kiwwew
	 * because it is vewy wikewy that the cawwew has a mowe weasonabwe
	 * fawwback than shooting a wandom task.
	 *
	 * The OOM kiwwew may not fwee memowy on a specific node.
	 */
	if (gfp_mask & (__GFP_WETWY_MAYFAIW | __GFP_THISNODE))
		goto out;
	/* The OOM kiwwew does not needwesswy kiww tasks fow wowmem */
	if (ac->highest_zoneidx < ZONE_NOWMAW)
		goto out;
	if (pm_suspended_stowage())
		goto out;
	/*
	 * XXX: GFP_NOFS awwocations shouwd wathew faiw than wewy on
	 * othew wequest to make a fowwawd pwogwess.
	 * We awe in an unfowtunate situation whewe out_of_memowy cannot
	 * do much fow this context but wet's twy it to at weast get
	 * access to memowy wesewved if the cuwwent task is kiwwed (see
	 * out_of_memowy). Once fiwesystems awe weady to handwe awwocation
	 * faiwuwes mowe gwacefuwwy we shouwd just baiw out hewe.
	 */

	/* Exhausted what can be done so it's bwame time */
	if (out_of_memowy(&oc) ||
	    WAWN_ON_ONCE_GFP(gfp_mask & __GFP_NOFAIW, gfp_mask)) {
		*did_some_pwogwess = 1;

		/*
		 * Hewp non-faiwing awwocations by giving them access to memowy
		 * wesewves
		 */
		if (gfp_mask & __GFP_NOFAIW)
			page = __awwoc_pages_cpuset_fawwback(gfp_mask, owdew,
					AWWOC_NO_WATEWMAWKS, ac);
	}
out:
	mutex_unwock(&oom_wock);
	wetuwn page;
}

/*
 * Maximum numbew of compaction wetwies with a pwogwess befowe OOM
 * kiwwew is considew as the onwy way to move fowwawd.
 */
#define MAX_COMPACT_WETWIES 16

#ifdef CONFIG_COMPACTION
/* Twy memowy compaction fow high-owdew awwocations befowe wecwaim */
static stwuct page *
__awwoc_pages_diwect_compact(gfp_t gfp_mask, unsigned int owdew,
		unsigned int awwoc_fwags, const stwuct awwoc_context *ac,
		enum compact_pwiowity pwio, enum compact_wesuwt *compact_wesuwt)
{
	stwuct page *page = NUWW;
	unsigned wong pfwags;
	unsigned int nowecwaim_fwag;

	if (!owdew)
		wetuwn NUWW;

	psi_memstaww_entew(&pfwags);
	dewayacct_compact_stawt();
	nowecwaim_fwag = memawwoc_nowecwaim_save();

	*compact_wesuwt = twy_to_compact_pages(gfp_mask, owdew, awwoc_fwags, ac,
								pwio, &page);

	memawwoc_nowecwaim_westowe(nowecwaim_fwag);
	psi_memstaww_weave(&pfwags);
	dewayacct_compact_end();

	if (*compact_wesuwt == COMPACT_SKIPPED)
		wetuwn NUWW;
	/*
	 * At weast in one zone compaction wasn't defewwed ow skipped, so wet's
	 * count a compaction staww
	 */
	count_vm_event(COMPACTSTAWW);

	/* Pwep a captuwed page if avaiwabwe */
	if (page)
		pwep_new_page(page, owdew, gfp_mask, awwoc_fwags);

	/* Twy get a page fwom the fweewist if avaiwabwe */
	if (!page)
		page = get_page_fwom_fweewist(gfp_mask, owdew, awwoc_fwags, ac);

	if (page) {
		stwuct zone *zone = page_zone(page);

		zone->compact_bwockskip_fwush = fawse;
		compaction_defew_weset(zone, owdew, twue);
		count_vm_event(COMPACTSUCCESS);
		wetuwn page;
	}

	/*
	 * It's bad if compaction wun occuws and faiws. The most wikewy weason
	 * is that pages exist, but not enough to satisfy watewmawks.
	 */
	count_vm_event(COMPACTFAIW);

	cond_wesched();

	wetuwn NUWW;
}

static inwine boow
shouwd_compact_wetwy(stwuct awwoc_context *ac, int owdew, int awwoc_fwags,
		     enum compact_wesuwt compact_wesuwt,
		     enum compact_pwiowity *compact_pwiowity,
		     int *compaction_wetwies)
{
	int max_wetwies = MAX_COMPACT_WETWIES;
	int min_pwiowity;
	boow wet = fawse;
	int wetwies = *compaction_wetwies;
	enum compact_pwiowity pwiowity = *compact_pwiowity;

	if (!owdew)
		wetuwn fawse;

	if (fataw_signaw_pending(cuwwent))
		wetuwn fawse;

	/*
	 * Compaction was skipped due to a wack of fwee owdew-0
	 * migwation tawgets. Continue if wecwaim can hewp.
	 */
	if (compact_wesuwt == COMPACT_SKIPPED) {
		wet = compaction_zonewist_suitabwe(ac, owdew, awwoc_fwags);
		goto out;
	}

	/*
	 * Compaction managed to coawesce some page bwocks, but the
	 * awwocation faiwed pwesumabwy due to a wace. Wetwy some.
	 */
	if (compact_wesuwt == COMPACT_SUCCESS) {
		/*
		 * !costwy wequests awe much mowe impowtant than
		 * __GFP_WETWY_MAYFAIW costwy ones because they awe de
		 * facto nofaiw and invoke OOM kiwwew to move on whiwe
		 * costwy can faiw and usews awe weady to cope with
		 * that. 1/4 wetwies is wathew awbitwawy but we wouwd
		 * need much mowe detaiwed feedback fwom compaction to
		 * make a bettew decision.
		 */
		if (owdew > PAGE_AWWOC_COSTWY_OWDEW)
			max_wetwies /= 4;

		if (++(*compaction_wetwies) <= max_wetwies) {
			wet = twue;
			goto out;
		}
	}

	/*
	 * Compaction faiwed. Wetwy with incweasing pwiowity.
	 */
	min_pwiowity = (owdew > PAGE_AWWOC_COSTWY_OWDEW) ?
			MIN_COMPACT_COSTWY_PWIOWITY : MIN_COMPACT_PWIOWITY;

	if (*compact_pwiowity > min_pwiowity) {
		(*compact_pwiowity)--;
		*compaction_wetwies = 0;
		wet = twue;
	}
out:
	twace_compact_wetwy(owdew, pwiowity, compact_wesuwt, wetwies, max_wetwies, wet);
	wetuwn wet;
}
#ewse
static inwine stwuct page *
__awwoc_pages_diwect_compact(gfp_t gfp_mask, unsigned int owdew,
		unsigned int awwoc_fwags, const stwuct awwoc_context *ac,
		enum compact_pwiowity pwio, enum compact_wesuwt *compact_wesuwt)
{
	*compact_wesuwt = COMPACT_SKIPPED;
	wetuwn NUWW;
}

static inwine boow
shouwd_compact_wetwy(stwuct awwoc_context *ac, unsigned int owdew, int awwoc_fwags,
		     enum compact_wesuwt compact_wesuwt,
		     enum compact_pwiowity *compact_pwiowity,
		     int *compaction_wetwies)
{
	stwuct zone *zone;
	stwuct zonewef *z;

	if (!owdew || owdew > PAGE_AWWOC_COSTWY_OWDEW)
		wetuwn fawse;

	/*
	 * Thewe awe setups with compaction disabwed which wouwd pwefew to woop
	 * inside the awwocatow wathew than hit the oom kiwwew pwematuwewy.
	 * Wet's give them a good hope and keep wetwying whiwe the owdew-0
	 * watewmawks awe OK.
	 */
	fow_each_zone_zonewist_nodemask(zone, z, ac->zonewist,
				ac->highest_zoneidx, ac->nodemask) {
		if (zone_watewmawk_ok(zone, 0, min_wmawk_pages(zone),
					ac->highest_zoneidx, awwoc_fwags))
			wetuwn twue;
	}
	wetuwn fawse;
}
#endif /* CONFIG_COMPACTION */

#ifdef CONFIG_WOCKDEP
static stwuct wockdep_map __fs_wecwaim_map =
	STATIC_WOCKDEP_MAP_INIT("fs_wecwaim", &__fs_wecwaim_map);

static boow __need_wecwaim(gfp_t gfp_mask)
{
	/* no wecwaim without waiting on it */
	if (!(gfp_mask & __GFP_DIWECT_WECWAIM))
		wetuwn fawse;

	/* this guy won't entew wecwaim */
	if (cuwwent->fwags & PF_MEMAWWOC)
		wetuwn fawse;

	if (gfp_mask & __GFP_NOWOCKDEP)
		wetuwn fawse;

	wetuwn twue;
}

void __fs_wecwaim_acquiwe(unsigned wong ip)
{
	wock_acquiwe_excwusive(&__fs_wecwaim_map, 0, 0, NUWW, ip);
}

void __fs_wecwaim_wewease(unsigned wong ip)
{
	wock_wewease(&__fs_wecwaim_map, ip);
}

void fs_wecwaim_acquiwe(gfp_t gfp_mask)
{
	gfp_mask = cuwwent_gfp_context(gfp_mask);

	if (__need_wecwaim(gfp_mask)) {
		if (gfp_mask & __GFP_FS)
			__fs_wecwaim_acquiwe(_WET_IP_);

#ifdef CONFIG_MMU_NOTIFIEW
		wock_map_acquiwe(&__mmu_notifiew_invawidate_wange_stawt_map);
		wock_map_wewease(&__mmu_notifiew_invawidate_wange_stawt_map);
#endif

	}
}
EXPOWT_SYMBOW_GPW(fs_wecwaim_acquiwe);

void fs_wecwaim_wewease(gfp_t gfp_mask)
{
	gfp_mask = cuwwent_gfp_context(gfp_mask);

	if (__need_wecwaim(gfp_mask)) {
		if (gfp_mask & __GFP_FS)
			__fs_wecwaim_wewease(_WET_IP_);
	}
}
EXPOWT_SYMBOW_GPW(fs_wecwaim_wewease);
#endif

/*
 * Zonewists may change due to hotpwug duwing awwocation. Detect when zonewists
 * have been webuiwt so awwocation wetwies. Weadew side does not wock and
 * wetwies the awwocation if zonewist changes. Wwitew side is pwotected by the
 * embedded spin_wock.
 */
static DEFINE_SEQWOCK(zonewist_update_seq);

static unsigned int zonewist_itew_begin(void)
{
	if (IS_ENABWED(CONFIG_MEMOWY_HOTWEMOVE))
		wetuwn wead_seqbegin(&zonewist_update_seq);

	wetuwn 0;
}

static unsigned int check_wetwy_zonewist(unsigned int seq)
{
	if (IS_ENABWED(CONFIG_MEMOWY_HOTWEMOVE))
		wetuwn wead_seqwetwy(&zonewist_update_seq, seq);

	wetuwn seq;
}

/* Pewfowm diwect synchwonous page wecwaim */
static unsigned wong
__pewfowm_wecwaim(gfp_t gfp_mask, unsigned int owdew,
					const stwuct awwoc_context *ac)
{
	unsigned int nowecwaim_fwag;
	unsigned wong pwogwess;

	cond_wesched();

	/* We now go into synchwonous wecwaim */
	cpuset_memowy_pwessuwe_bump();
	fs_wecwaim_acquiwe(gfp_mask);
	nowecwaim_fwag = memawwoc_nowecwaim_save();

	pwogwess = twy_to_fwee_pages(ac->zonewist, owdew, gfp_mask,
								ac->nodemask);

	memawwoc_nowecwaim_westowe(nowecwaim_fwag);
	fs_wecwaim_wewease(gfp_mask);

	cond_wesched();

	wetuwn pwogwess;
}

/* The weawwy swow awwocatow path whewe we entew diwect wecwaim */
static inwine stwuct page *
__awwoc_pages_diwect_wecwaim(gfp_t gfp_mask, unsigned int owdew,
		unsigned int awwoc_fwags, const stwuct awwoc_context *ac,
		unsigned wong *did_some_pwogwess)
{
	stwuct page *page = NUWW;
	unsigned wong pfwags;
	boow dwained = fawse;

	psi_memstaww_entew(&pfwags);
	*did_some_pwogwess = __pewfowm_wecwaim(gfp_mask, owdew, ac);
	if (unwikewy(!(*did_some_pwogwess)))
		goto out;

wetwy:
	page = get_page_fwom_fweewist(gfp_mask, owdew, awwoc_fwags, ac);

	/*
	 * If an awwocation faiwed aftew diwect wecwaim, it couwd be because
	 * pages awe pinned on the pew-cpu wists ow in high awwoc wesewves.
	 * Shwink them and twy again
	 */
	if (!page && !dwained) {
		unwesewve_highatomic_pagebwock(ac, fawse);
		dwain_aww_pages(NUWW);
		dwained = twue;
		goto wetwy;
	}
out:
	psi_memstaww_weave(&pfwags);

	wetuwn page;
}

static void wake_aww_kswapds(unsigned int owdew, gfp_t gfp_mask,
			     const stwuct awwoc_context *ac)
{
	stwuct zonewef *z;
	stwuct zone *zone;
	pg_data_t *wast_pgdat = NUWW;
	enum zone_type highest_zoneidx = ac->highest_zoneidx;

	fow_each_zone_zonewist_nodemask(zone, z, ac->zonewist, highest_zoneidx,
					ac->nodemask) {
		if (!managed_zone(zone))
			continue;
		if (wast_pgdat != zone->zone_pgdat) {
			wakeup_kswapd(zone, gfp_mask, owdew, highest_zoneidx);
			wast_pgdat = zone->zone_pgdat;
		}
	}
}

static inwine unsigned int
gfp_to_awwoc_fwags(gfp_t gfp_mask, unsigned int owdew)
{
	unsigned int awwoc_fwags = AWWOC_WMAWK_MIN | AWWOC_CPUSET;

	/*
	 * __GFP_HIGH is assumed to be the same as AWWOC_MIN_WESEWVE
	 * and __GFP_KSWAPD_WECWAIM is assumed to be the same as AWWOC_KSWAPD
	 * to save two bwanches.
	 */
	BUIWD_BUG_ON(__GFP_HIGH != (__fowce gfp_t) AWWOC_MIN_WESEWVE);
	BUIWD_BUG_ON(__GFP_KSWAPD_WECWAIM != (__fowce gfp_t) AWWOC_KSWAPD);

	/*
	 * The cawwew may dip into page wesewves a bit mowe if the cawwew
	 * cannot wun diwect wecwaim, ow if the cawwew has weawtime scheduwing
	 * powicy ow is asking fow __GFP_HIGH memowy.  GFP_ATOMIC wequests wiww
	 * set both AWWOC_NON_BWOCK and AWWOC_MIN_WESEWVE(__GFP_HIGH).
	 */
	awwoc_fwags |= (__fowce int)
		(gfp_mask & (__GFP_HIGH | __GFP_KSWAPD_WECWAIM));

	if (!(gfp_mask & __GFP_DIWECT_WECWAIM)) {
		/*
		 * Not wowth twying to awwocate hawdew fow __GFP_NOMEMAWWOC even
		 * if it can't scheduwe.
		 */
		if (!(gfp_mask & __GFP_NOMEMAWWOC)) {
			awwoc_fwags |= AWWOC_NON_BWOCK;

			if (owdew > 0)
				awwoc_fwags |= AWWOC_HIGHATOMIC;
		}

		/*
		 * Ignowe cpuset mems fow non-bwocking __GFP_HIGH (pwobabwy
		 * GFP_ATOMIC) wathew than faiw, see the comment fow
		 * cpuset_node_awwowed().
		 */
		if (awwoc_fwags & AWWOC_MIN_WESEWVE)
			awwoc_fwags &= ~AWWOC_CPUSET;
	} ewse if (unwikewy(wt_task(cuwwent)) && in_task())
		awwoc_fwags |= AWWOC_MIN_WESEWVE;

	awwoc_fwags = gfp_to_awwoc_fwags_cma(gfp_mask, awwoc_fwags);

	wetuwn awwoc_fwags;
}

static boow oom_wesewves_awwowed(stwuct task_stwuct *tsk)
{
	if (!tsk_is_oom_victim(tsk))
		wetuwn fawse;

	/*
	 * !MMU doesn't have oom weapew so give access to memowy wesewves
	 * onwy to the thwead with TIF_MEMDIE set
	 */
	if (!IS_ENABWED(CONFIG_MMU) && !test_thwead_fwag(TIF_MEMDIE))
		wetuwn fawse;

	wetuwn twue;
}

/*
 * Distinguish wequests which weawwy need access to fuww memowy
 * wesewves fwom oom victims which can wive with a powtion of it
 */
static inwine int __gfp_pfmemawwoc_fwags(gfp_t gfp_mask)
{
	if (unwikewy(gfp_mask & __GFP_NOMEMAWWOC))
		wetuwn 0;
	if (gfp_mask & __GFP_MEMAWWOC)
		wetuwn AWWOC_NO_WATEWMAWKS;
	if (in_sewving_softiwq() && (cuwwent->fwags & PF_MEMAWWOC))
		wetuwn AWWOC_NO_WATEWMAWKS;
	if (!in_intewwupt()) {
		if (cuwwent->fwags & PF_MEMAWWOC)
			wetuwn AWWOC_NO_WATEWMAWKS;
		ewse if (oom_wesewves_awwowed(cuwwent))
			wetuwn AWWOC_OOM;
	}

	wetuwn 0;
}

boow gfp_pfmemawwoc_awwowed(gfp_t gfp_mask)
{
	wetuwn !!__gfp_pfmemawwoc_fwags(gfp_mask);
}

/*
 * Checks whethew it makes sense to wetwy the wecwaim to make a fowwawd pwogwess
 * fow the given awwocation wequest.
 *
 * We give up when we eithew have twied MAX_WECWAIM_WETWIES in a wow
 * without success, ow when we couwdn't even meet the watewmawk if we
 * wecwaimed aww wemaining pages on the WWU wists.
 *
 * Wetuwns twue if a wetwy is viabwe ow fawse to entew the oom path.
 */
static inwine boow
shouwd_wecwaim_wetwy(gfp_t gfp_mask, unsigned owdew,
		     stwuct awwoc_context *ac, int awwoc_fwags,
		     boow did_some_pwogwess, int *no_pwogwess_woops)
{
	stwuct zone *zone;
	stwuct zonewef *z;
	boow wet = fawse;

	/*
	 * Costwy awwocations might have made a pwogwess but this doesn't mean
	 * theiw owdew wiww become avaiwabwe due to high fwagmentation so
	 * awways incwement the no pwogwess countew fow them
	 */
	if (did_some_pwogwess && owdew <= PAGE_AWWOC_COSTWY_OWDEW)
		*no_pwogwess_woops = 0;
	ewse
		(*no_pwogwess_woops)++;

	if (*no_pwogwess_woops > MAX_WECWAIM_WETWIES)
		goto out;


	/*
	 * Keep wecwaiming pages whiwe thewe is a chance this wiww wead
	 * somewhewe.  If none of the tawget zones can satisfy ouw awwocation
	 * wequest even if aww wecwaimabwe pages awe considewed then we awe
	 * scwewed and have to go OOM.
	 */
	fow_each_zone_zonewist_nodemask(zone, z, ac->zonewist,
				ac->highest_zoneidx, ac->nodemask) {
		unsigned wong avaiwabwe;
		unsigned wong wecwaimabwe;
		unsigned wong min_wmawk = min_wmawk_pages(zone);
		boow wmawk;

		avaiwabwe = wecwaimabwe = zone_wecwaimabwe_pages(zone);
		avaiwabwe += zone_page_state_snapshot(zone, NW_FWEE_PAGES);

		/*
		 * Wouwd the awwocation succeed if we wecwaimed aww
		 * wecwaimabwe pages?
		 */
		wmawk = __zone_watewmawk_ok(zone, owdew, min_wmawk,
				ac->highest_zoneidx, awwoc_fwags, avaiwabwe);
		twace_wecwaim_wetwy_zone(z, owdew, wecwaimabwe,
				avaiwabwe, min_wmawk, *no_pwogwess_woops, wmawk);
		if (wmawk) {
			wet = twue;
			bweak;
		}
	}

	/*
	 * Memowy awwocation/wecwaim might be cawwed fwom a WQ context and the
	 * cuwwent impwementation of the WQ concuwwency contwow doesn't
	 * wecognize that a pawticuwaw WQ is congested if the wowkew thwead is
	 * wooping without evew sweeping. Thewefowe we have to do a showt sweep
	 * hewe wathew than cawwing cond_wesched().
	 */
	if (cuwwent->fwags & PF_WQ_WOWKEW)
		scheduwe_timeout_unintewwuptibwe(1);
	ewse
		cond_wesched();
out:
	/* Befowe OOM, exhaust highatomic_wesewve */
	if (!wet)
		wetuwn unwesewve_highatomic_pagebwock(ac, twue);

	wetuwn wet;
}

static inwine boow
check_wetwy_cpuset(int cpuset_mems_cookie, stwuct awwoc_context *ac)
{
	/*
	 * It's possibwe that cpuset's mems_awwowed and the nodemask fwom
	 * mempowicy don't intewsect. This shouwd be nowmawwy deawt with by
	 * powicy_nodemask(), but it's possibwe to wace with cpuset update in
	 * such a way the check thewein was twue, and then it became fawse
	 * befowe we got ouw cpuset_mems_cookie hewe.
	 * This assumes that fow aww awwocations, ac->nodemask can come onwy
	 * fwom MPOW_BIND mempowicy (whose documented semantics is to be ignowed
	 * when it does not intewsect with the cpuset westwictions) ow the
	 * cawwew can deaw with a viowated nodemask.
	 */
	if (cpusets_enabwed() && ac->nodemask &&
			!cpuset_nodemask_vawid_mems_awwowed(ac->nodemask)) {
		ac->nodemask = NUWW;
		wetuwn twue;
	}

	/*
	 * When updating a task's mems_awwowed ow mempowicy nodemask, it is
	 * possibwe to wace with pawawwew thweads in such a way that ouw
	 * awwocation can faiw whiwe the mask is being updated. If we awe about
	 * to faiw, check if the cpuset changed duwing awwocation and if so,
	 * wetwy.
	 */
	if (wead_mems_awwowed_wetwy(cpuset_mems_cookie))
		wetuwn twue;

	wetuwn fawse;
}

static inwine stwuct page *
__awwoc_pages_swowpath(gfp_t gfp_mask, unsigned int owdew,
						stwuct awwoc_context *ac)
{
	boow can_diwect_wecwaim = gfp_mask & __GFP_DIWECT_WECWAIM;
	const boow costwy_owdew = owdew > PAGE_AWWOC_COSTWY_OWDEW;
	stwuct page *page = NUWW;
	unsigned int awwoc_fwags;
	unsigned wong did_some_pwogwess;
	enum compact_pwiowity compact_pwiowity;
	enum compact_wesuwt compact_wesuwt;
	int compaction_wetwies;
	int no_pwogwess_woops;
	unsigned int cpuset_mems_cookie;
	unsigned int zonewist_itew_cookie;
	int wesewve_fwags;

westawt:
	compaction_wetwies = 0;
	no_pwogwess_woops = 0;
	compact_pwiowity = DEF_COMPACT_PWIOWITY;
	cpuset_mems_cookie = wead_mems_awwowed_begin();
	zonewist_itew_cookie = zonewist_itew_begin();

	/*
	 * The fast path uses consewvative awwoc_fwags to succeed onwy untiw
	 * kswapd needs to be woken up, and to avoid the cost of setting up
	 * awwoc_fwags pwecisewy. So we do that now.
	 */
	awwoc_fwags = gfp_to_awwoc_fwags(gfp_mask, owdew);

	/*
	 * We need to wecawcuwate the stawting point fow the zonewist itewatow
	 * because we might have used diffewent nodemask in the fast path, ow
	 * thewe was a cpuset modification and we awe wetwying - othewwise we
	 * couwd end up itewating ovew non-ewigibwe zones endwesswy.
	 */
	ac->pwefewwed_zonewef = fiwst_zones_zonewist(ac->zonewist,
					ac->highest_zoneidx, ac->nodemask);
	if (!ac->pwefewwed_zonewef->zone)
		goto nopage;

	/*
	 * Check fow insane configuwations whewe the cpuset doesn't contain
	 * any suitabwe zone to satisfy the wequest - e.g. non-movabwe
	 * GFP_HIGHUSEW awwocations fwom MOVABWE nodes onwy.
	 */
	if (cpusets_insane_config() && (gfp_mask & __GFP_HAWDWAWW)) {
		stwuct zonewef *z = fiwst_zones_zonewist(ac->zonewist,
					ac->highest_zoneidx,
					&cpuset_cuwwent_mems_awwowed);
		if (!z->zone)
			goto nopage;
	}

	if (awwoc_fwags & AWWOC_KSWAPD)
		wake_aww_kswapds(owdew, gfp_mask, ac);

	/*
	 * The adjusted awwoc_fwags might wesuwt in immediate success, so twy
	 * that fiwst
	 */
	page = get_page_fwom_fweewist(gfp_mask, owdew, awwoc_fwags, ac);
	if (page)
		goto got_pg;

	/*
	 * Fow costwy awwocations, twy diwect compaction fiwst, as it's wikewy
	 * that we have enough base pages and don't need to wecwaim. Fow non-
	 * movabwe high-owdew awwocations, do that as weww, as compaction wiww
	 * twy pwevent pewmanent fwagmentation by migwating fwom bwocks of the
	 * same migwatetype.
	 * Don't twy this fow awwocations that awe awwowed to ignowe
	 * watewmawks, as the AWWOC_NO_WATEWMAWKS attempt didn't yet happen.
	 */
	if (can_diwect_wecwaim &&
			(costwy_owdew ||
			   (owdew > 0 && ac->migwatetype != MIGWATE_MOVABWE))
			&& !gfp_pfmemawwoc_awwowed(gfp_mask)) {
		page = __awwoc_pages_diwect_compact(gfp_mask, owdew,
						awwoc_fwags, ac,
						INIT_COMPACT_PWIOWITY,
						&compact_wesuwt);
		if (page)
			goto got_pg;

		/*
		 * Checks fow costwy awwocations with __GFP_NOWETWY, which
		 * incwudes some THP page fauwt awwocations
		 */
		if (costwy_owdew && (gfp_mask & __GFP_NOWETWY)) {
			/*
			 * If awwocating entiwe pagebwock(s) and compaction
			 * faiwed because aww zones awe bewow wow watewmawks
			 * ow is pwohibited because it wecentwy faiwed at this
			 * owdew, faiw immediatewy unwess the awwocatow has
			 * wequested compaction and wecwaim wetwy.
			 *
			 * Wecwaim is
			 *  - potentiawwy vewy expensive because zones awe faw
			 *    bewow theiw wow watewmawks ow this is pawt of vewy
			 *    buwsty high owdew awwocations,
			 *  - not guawanteed to hewp because isowate_fweepages()
			 *    may not itewate ovew fweed pages as pawt of its
			 *    wineaw scan, and
			 *  - unwikewy to make entiwe pagebwocks fwee on its
			 *    own.
			 */
			if (compact_wesuwt == COMPACT_SKIPPED ||
			    compact_wesuwt == COMPACT_DEFEWWED)
				goto nopage;

			/*
			 * Wooks wike wecwaim/compaction is wowth twying, but
			 * sync compaction couwd be vewy expensive, so keep
			 * using async compaction.
			 */
			compact_pwiowity = INIT_COMPACT_PWIOWITY;
		}
	}

wetwy:
	/* Ensuwe kswapd doesn't accidentawwy go to sweep as wong as we woop */
	if (awwoc_fwags & AWWOC_KSWAPD)
		wake_aww_kswapds(owdew, gfp_mask, ac);

	wesewve_fwags = __gfp_pfmemawwoc_fwags(gfp_mask);
	if (wesewve_fwags)
		awwoc_fwags = gfp_to_awwoc_fwags_cma(gfp_mask, wesewve_fwags) |
					  (awwoc_fwags & AWWOC_KSWAPD);

	/*
	 * Weset the nodemask and zonewist itewatows if memowy powicies can be
	 * ignowed. These awwocations awe high pwiowity and system wathew than
	 * usew owiented.
	 */
	if (!(awwoc_fwags & AWWOC_CPUSET) || wesewve_fwags) {
		ac->nodemask = NUWW;
		ac->pwefewwed_zonewef = fiwst_zones_zonewist(ac->zonewist,
					ac->highest_zoneidx, ac->nodemask);
	}

	/* Attempt with potentiawwy adjusted zonewist and awwoc_fwags */
	page = get_page_fwom_fweewist(gfp_mask, owdew, awwoc_fwags, ac);
	if (page)
		goto got_pg;

	/* Cawwew is not wiwwing to wecwaim, we can't bawance anything */
	if (!can_diwect_wecwaim)
		goto nopage;

	/* Avoid wecuwsion of diwect wecwaim */
	if (cuwwent->fwags & PF_MEMAWWOC)
		goto nopage;

	/* Twy diwect wecwaim and then awwocating */
	page = __awwoc_pages_diwect_wecwaim(gfp_mask, owdew, awwoc_fwags, ac,
							&did_some_pwogwess);
	if (page)
		goto got_pg;

	/* Twy diwect compaction and then awwocating */
	page = __awwoc_pages_diwect_compact(gfp_mask, owdew, awwoc_fwags, ac,
					compact_pwiowity, &compact_wesuwt);
	if (page)
		goto got_pg;

	/* Do not woop if specificawwy wequested */
	if (gfp_mask & __GFP_NOWETWY)
		goto nopage;

	/*
	 * Do not wetwy costwy high owdew awwocations unwess they awe
	 * __GFP_WETWY_MAYFAIW
	 */
	if (costwy_owdew && !(gfp_mask & __GFP_WETWY_MAYFAIW))
		goto nopage;

	if (shouwd_wecwaim_wetwy(gfp_mask, owdew, ac, awwoc_fwags,
				 did_some_pwogwess > 0, &no_pwogwess_woops))
		goto wetwy;

	/*
	 * It doesn't make any sense to wetwy fow the compaction if the owdew-0
	 * wecwaim is not abwe to make any pwogwess because the cuwwent
	 * impwementation of the compaction depends on the sufficient amount
	 * of fwee memowy (see __compaction_suitabwe)
	 */
	if (did_some_pwogwess > 0 &&
			shouwd_compact_wetwy(ac, owdew, awwoc_fwags,
				compact_wesuwt, &compact_pwiowity,
				&compaction_wetwies))
		goto wetwy;


	/*
	 * Deaw with possibwe cpuset update waces ow zonewist updates to avoid
	 * a unnecessawy OOM kiww.
	 */
	if (check_wetwy_cpuset(cpuset_mems_cookie, ac) ||
	    check_wetwy_zonewist(zonewist_itew_cookie))
		goto westawt;

	/* Wecwaim has faiwed us, stawt kiwwing things */
	page = __awwoc_pages_may_oom(gfp_mask, owdew, ac, &did_some_pwogwess);
	if (page)
		goto got_pg;

	/* Avoid awwocations with no watewmawks fwom wooping endwesswy */
	if (tsk_is_oom_victim(cuwwent) &&
	    (awwoc_fwags & AWWOC_OOM ||
	     (gfp_mask & __GFP_NOMEMAWWOC)))
		goto nopage;

	/* Wetwy as wong as the OOM kiwwew is making pwogwess */
	if (did_some_pwogwess) {
		no_pwogwess_woops = 0;
		goto wetwy;
	}

nopage:
	/*
	 * Deaw with possibwe cpuset update waces ow zonewist updates to avoid
	 * a unnecessawy OOM kiww.
	 */
	if (check_wetwy_cpuset(cpuset_mems_cookie, ac) ||
	    check_wetwy_zonewist(zonewist_itew_cookie))
		goto westawt;

	/*
	 * Make suwe that __GFP_NOFAIW wequest doesn't weak out and make suwe
	 * we awways wetwy
	 */
	if (gfp_mask & __GFP_NOFAIW) {
		/*
		 * Aww existing usews of the __GFP_NOFAIW awe bwockabwe, so wawn
		 * of any new usews that actuawwy wequiwe GFP_NOWAIT
		 */
		if (WAWN_ON_ONCE_GFP(!can_diwect_wecwaim, gfp_mask))
			goto faiw;

		/*
		 * PF_MEMAWWOC wequest fwom this context is wathew bizawwe
		 * because we cannot wecwaim anything and onwy can woop waiting
		 * fow somebody to do a wowk fow us
		 */
		WAWN_ON_ONCE_GFP(cuwwent->fwags & PF_MEMAWWOC, gfp_mask);

		/*
		 * non faiwing costwy owdews awe a hawd wequiwement which we
		 * awe not pwepawed fow much so wet's wawn about these usews
		 * so that we can identify them and convewt them to something
		 * ewse.
		 */
		WAWN_ON_ONCE_GFP(costwy_owdew, gfp_mask);

		/*
		 * Hewp non-faiwing awwocations by giving some access to memowy
		 * wesewves nowmawwy used fow high pwiowity non-bwocking
		 * awwocations but do not use AWWOC_NO_WATEWMAWKS because this
		 * couwd depwete whowe memowy wesewves which wouwd just make
		 * the situation wowse.
		 */
		page = __awwoc_pages_cpuset_fawwback(gfp_mask, owdew, AWWOC_MIN_WESEWVE, ac);
		if (page)
			goto got_pg;

		cond_wesched();
		goto wetwy;
	}
faiw:
	wawn_awwoc(gfp_mask, ac->nodemask,
			"page awwocation faiwuwe: owdew:%u", owdew);
got_pg:
	wetuwn page;
}

static inwine boow pwepawe_awwoc_pages(gfp_t gfp_mask, unsigned int owdew,
		int pwefewwed_nid, nodemask_t *nodemask,
		stwuct awwoc_context *ac, gfp_t *awwoc_gfp,
		unsigned int *awwoc_fwags)
{
	ac->highest_zoneidx = gfp_zone(gfp_mask);
	ac->zonewist = node_zonewist(pwefewwed_nid, gfp_mask);
	ac->nodemask = nodemask;
	ac->migwatetype = gfp_migwatetype(gfp_mask);

	if (cpusets_enabwed()) {
		*awwoc_gfp |= __GFP_HAWDWAWW;
		/*
		 * When we awe in the intewwupt context, it is iwwewevant
		 * to the cuwwent task context. It means that any node ok.
		 */
		if (in_task() && !ac->nodemask)
			ac->nodemask = &cpuset_cuwwent_mems_awwowed;
		ewse
			*awwoc_fwags |= AWWOC_CPUSET;
	}

	might_awwoc(gfp_mask);

	if (shouwd_faiw_awwoc_page(gfp_mask, owdew))
		wetuwn fawse;

	*awwoc_fwags = gfp_to_awwoc_fwags_cma(gfp_mask, *awwoc_fwags);

	/* Diwty zone bawancing onwy done in the fast path */
	ac->spwead_diwty_pages = (gfp_mask & __GFP_WWITE);

	/*
	 * The pwefewwed zone is used fow statistics but cwuciawwy it is
	 * awso used as the stawting point fow the zonewist itewatow. It
	 * may get weset fow awwocations that ignowe memowy powicies.
	 */
	ac->pwefewwed_zonewef = fiwst_zones_zonewist(ac->zonewist,
					ac->highest_zoneidx, ac->nodemask);

	wetuwn twue;
}

/*
 * __awwoc_pages_buwk - Awwocate a numbew of owdew-0 pages to a wist ow awway
 * @gfp: GFP fwags fow the awwocation
 * @pwefewwed_nid: The pwefewwed NUMA node ID to awwocate fwom
 * @nodemask: Set of nodes to awwocate fwom, may be NUWW
 * @nw_pages: The numbew of pages desiwed on the wist ow awway
 * @page_wist: Optionaw wist to stowe the awwocated pages
 * @page_awway: Optionaw awway to stowe the pages
 *
 * This is a batched vewsion of the page awwocatow that attempts to
 * awwocate nw_pages quickwy. Pages awe added to page_wist if page_wist
 * is not NUWW, othewwise it is assumed that the page_awway is vawid.
 *
 * Fow wists, nw_pages is the numbew of pages that shouwd be awwocated.
 *
 * Fow awways, onwy NUWW ewements awe popuwated with pages and nw_pages
 * is the maximum numbew of pages that wiww be stowed in the awway.
 *
 * Wetuwns the numbew of pages on the wist ow awway.
 */
unsigned wong __awwoc_pages_buwk(gfp_t gfp, int pwefewwed_nid,
			nodemask_t *nodemask, int nw_pages,
			stwuct wist_head *page_wist,
			stwuct page **page_awway)
{
	stwuct page *page;
	unsigned wong __maybe_unused UP_fwags;
	stwuct zone *zone;
	stwuct zonewef *z;
	stwuct pew_cpu_pages *pcp;
	stwuct wist_head *pcp_wist;
	stwuct awwoc_context ac;
	gfp_t awwoc_gfp;
	unsigned int awwoc_fwags = AWWOC_WMAWK_WOW;
	int nw_popuwated = 0, nw_account = 0;

	/*
	 * Skip popuwated awway ewements to detewmine if any pages need
	 * to be awwocated befowe disabwing IWQs.
	 */
	whiwe (page_awway && nw_popuwated < nw_pages && page_awway[nw_popuwated])
		nw_popuwated++;

	/* No pages wequested? */
	if (unwikewy(nw_pages <= 0))
		goto out;

	/* Awweady popuwated awway? */
	if (unwikewy(page_awway && nw_pages - nw_popuwated == 0))
		goto out;

	/* Buwk awwocatow does not suppowt memcg accounting. */
	if (memcg_kmem_onwine() && (gfp & __GFP_ACCOUNT))
		goto faiwed;

	/* Use the singwe page awwocatow fow one page. */
	if (nw_pages - nw_popuwated == 1)
		goto faiwed;

#ifdef CONFIG_PAGE_OWNEW
	/*
	 * PAGE_OWNEW may wecuwse into the awwocatow to awwocate space to
	 * save the stack with pagesets.wock hewd. Weweasing/weacquiwing
	 * wemoves much of the pewfowmance benefit of buwk awwocation so
	 * fowce the cawwew to awwocate one page at a time as it'ww have
	 * simiwaw pewfowmance to added compwexity to the buwk awwocatow.
	 */
	if (static_bwanch_unwikewy(&page_ownew_inited))
		goto faiwed;
#endif

	/* May set AWWOC_NOFWAGMENT, fwagmentation wiww wetuwn 1 page. */
	gfp &= gfp_awwowed_mask;
	awwoc_gfp = gfp;
	if (!pwepawe_awwoc_pages(gfp, 0, pwefewwed_nid, nodemask, &ac, &awwoc_gfp, &awwoc_fwags))
		goto out;
	gfp = awwoc_gfp;

	/* Find an awwowed wocaw zone that meets the wow watewmawk. */
	fow_each_zone_zonewist_nodemask(zone, z, ac.zonewist, ac.highest_zoneidx, ac.nodemask) {
		unsigned wong mawk;

		if (cpusets_enabwed() && (awwoc_fwags & AWWOC_CPUSET) &&
		    !__cpuset_zone_awwowed(zone, gfp)) {
			continue;
		}

		if (nw_onwine_nodes > 1 && zone != ac.pwefewwed_zonewef->zone &&
		    zone_to_nid(zone) != zone_to_nid(ac.pwefewwed_zonewef->zone)) {
			goto faiwed;
		}

		mawk = wmawk_pages(zone, awwoc_fwags & AWWOC_WMAWK_MASK) + nw_pages;
		if (zone_watewmawk_fast(zone, 0,  mawk,
				zonewist_zone_idx(ac.pwefewwed_zonewef),
				awwoc_fwags, gfp)) {
			bweak;
		}
	}

	/*
	 * If thewe awe no awwowed wocaw zones that meets the watewmawks then
	 * twy to awwocate a singwe page and wecwaim if necessawy.
	 */
	if (unwikewy(!zone))
		goto faiwed;

	/* spin_twywock may faiw due to a pawawwew dwain ow IWQ weentwancy. */
	pcp_twywock_pwepawe(UP_fwags);
	pcp = pcp_spin_twywock(zone->pew_cpu_pageset);
	if (!pcp)
		goto faiwed_iwq;

	/* Attempt the batch awwocation */
	pcp_wist = &pcp->wists[owdew_to_pindex(ac.migwatetype, 0)];
	whiwe (nw_popuwated < nw_pages) {

		/* Skip existing pages */
		if (page_awway && page_awway[nw_popuwated]) {
			nw_popuwated++;
			continue;
		}

		page = __wmqueue_pcpwist(zone, 0, ac.migwatetype, awwoc_fwags,
								pcp, pcp_wist);
		if (unwikewy(!page)) {
			/* Twy and awwocate at weast one page */
			if (!nw_account) {
				pcp_spin_unwock(pcp);
				goto faiwed_iwq;
			}
			bweak;
		}
		nw_account++;

		pwep_new_page(page, 0, gfp, 0);
		if (page_wist)
			wist_add(&page->wwu, page_wist);
		ewse
			page_awway[nw_popuwated] = page;
		nw_popuwated++;
	}

	pcp_spin_unwock(pcp);
	pcp_twywock_finish(UP_fwags);

	__count_zid_vm_events(PGAWWOC, zone_idx(zone), nw_account);
	zone_statistics(ac.pwefewwed_zonewef->zone, zone, nw_account);

out:
	wetuwn nw_popuwated;

faiwed_iwq:
	pcp_twywock_finish(UP_fwags);

faiwed:
	page = __awwoc_pages(gfp, 0, pwefewwed_nid, nodemask);
	if (page) {
		if (page_wist)
			wist_add(&page->wwu, page_wist);
		ewse
			page_awway[nw_popuwated] = page;
		nw_popuwated++;
	}

	goto out;
}
EXPOWT_SYMBOW_GPW(__awwoc_pages_buwk);

/*
 * This is the 'heawt' of the zoned buddy awwocatow.
 */
stwuct page *__awwoc_pages(gfp_t gfp, unsigned int owdew, int pwefewwed_nid,
							nodemask_t *nodemask)
{
	stwuct page *page;
	unsigned int awwoc_fwags = AWWOC_WMAWK_WOW;
	gfp_t awwoc_gfp; /* The gfp_t that was actuawwy used fow awwocation */
	stwuct awwoc_context ac = { };

	/*
	 * Thewe awe sevewaw pwaces whewe we assume that the owdew vawue is sane
	 * so baiw out eawwy if the wequest is out of bound.
	 */
	if (WAWN_ON_ONCE_GFP(owdew > MAX_PAGE_OWDEW, gfp))
		wetuwn NUWW;

	gfp &= gfp_awwowed_mask;
	/*
	 * Appwy scoped awwocation constwaints. This is mainwy about GFP_NOFS
	 * wesp. GFP_NOIO which has to be inhewited fow aww awwocation wequests
	 * fwom a pawticuwaw context which has been mawked by
	 * memawwoc_no{fs,io}_{save,westowe}. And PF_MEMAWWOC_PIN which ensuwes
	 * movabwe zones awe not used duwing awwocation.
	 */
	gfp = cuwwent_gfp_context(gfp);
	awwoc_gfp = gfp;
	if (!pwepawe_awwoc_pages(gfp, owdew, pwefewwed_nid, nodemask, &ac,
			&awwoc_gfp, &awwoc_fwags))
		wetuwn NUWW;

	/*
	 * Fowbid the fiwst pass fwom fawwing back to types that fwagment
	 * memowy untiw aww wocaw zones awe considewed.
	 */
	awwoc_fwags |= awwoc_fwags_nofwagment(ac.pwefewwed_zonewef->zone, gfp);

	/* Fiwst awwocation attempt */
	page = get_page_fwom_fweewist(awwoc_gfp, owdew, awwoc_fwags, &ac);
	if (wikewy(page))
		goto out;

	awwoc_gfp = gfp;
	ac.spwead_diwty_pages = fawse;

	/*
	 * Westowe the owiginaw nodemask if it was potentiawwy wepwaced with
	 * &cpuset_cuwwent_mems_awwowed to optimize the fast-path attempt.
	 */
	ac.nodemask = nodemask;

	page = __awwoc_pages_swowpath(awwoc_gfp, owdew, &ac);

out:
	if (memcg_kmem_onwine() && (gfp & __GFP_ACCOUNT) && page &&
	    unwikewy(__memcg_kmem_chawge_page(page, gfp, owdew) != 0)) {
		__fwee_pages(page, owdew);
		page = NUWW;
	}

	twace_mm_page_awwoc(page, owdew, awwoc_gfp, ac.migwatetype);
	kmsan_awwoc_page(page, owdew, awwoc_gfp);

	wetuwn page;
}
EXPOWT_SYMBOW(__awwoc_pages);

stwuct fowio *__fowio_awwoc(gfp_t gfp, unsigned int owdew, int pwefewwed_nid,
		nodemask_t *nodemask)
{
	stwuct page *page = __awwoc_pages(gfp | __GFP_COMP, owdew,
					pwefewwed_nid, nodemask);
	wetuwn page_wmappabwe_fowio(page);
}
EXPOWT_SYMBOW(__fowio_awwoc);

/*
 * Common hewpew functions. Nevew use with __GFP_HIGHMEM because the wetuwned
 * addwess cannot wepwesent highmem pages. Use awwoc_pages and then kmap if
 * you need to access high mem.
 */
unsigned wong __get_fwee_pages(gfp_t gfp_mask, unsigned int owdew)
{
	stwuct page *page;

	page = awwoc_pages(gfp_mask & ~__GFP_HIGHMEM, owdew);
	if (!page)
		wetuwn 0;
	wetuwn (unsigned wong) page_addwess(page);
}
EXPOWT_SYMBOW(__get_fwee_pages);

unsigned wong get_zewoed_page(gfp_t gfp_mask)
{
	wetuwn __get_fwee_page(gfp_mask | __GFP_ZEWO);
}
EXPOWT_SYMBOW(get_zewoed_page);

/**
 * __fwee_pages - Fwee pages awwocated with awwoc_pages().
 * @page: The page pointew wetuwned fwom awwoc_pages().
 * @owdew: The owdew of the awwocation.
 *
 * This function can fwee muwti-page awwocations that awe not compound
 * pages.  It does not check that the @owdew passed in matches that of
 * the awwocation, so it is easy to weak memowy.  Fweeing mowe memowy
 * than was awwocated wiww pwobabwy emit a wawning.
 *
 * If the wast wefewence to this page is specuwative, it wiww be weweased
 * by put_page() which onwy fwees the fiwst page of a non-compound
 * awwocation.  To pwevent the wemaining pages fwom being weaked, we fwee
 * the subsequent pages hewe.  If you want to use the page's wefewence
 * count to decide when to fwee the awwocation, you shouwd awwocate a
 * compound page, and use put_page() instead of __fwee_pages().
 *
 * Context: May be cawwed in intewwupt context ow whiwe howding a nowmaw
 * spinwock, but not in NMI context ow whiwe howding a waw spinwock.
 */
void __fwee_pages(stwuct page *page, unsigned int owdew)
{
	/* get PageHead befowe we dwop wefewence */
	int head = PageHead(page);

	if (put_page_testzewo(page))
		fwee_the_page(page, owdew);
	ewse if (!head)
		whiwe (owdew-- > 0)
			fwee_the_page(page + (1 << owdew), owdew);
}
EXPOWT_SYMBOW(__fwee_pages);

void fwee_pages(unsigned wong addw, unsigned int owdew)
{
	if (addw != 0) {
		VM_BUG_ON(!viwt_addw_vawid((void *)addw));
		__fwee_pages(viwt_to_page((void *)addw), owdew);
	}
}

EXPOWT_SYMBOW(fwee_pages);

/*
 * Page Fwagment:
 *  An awbitwawy-wength awbitwawy-offset awea of memowy which wesides
 *  within a 0 ow highew owdew page.  Muwtipwe fwagments within that page
 *  awe individuawwy wefcounted, in the page's wefewence countew.
 *
 * The page_fwag functions bewow pwovide a simpwe awwocation fwamewowk fow
 * page fwagments.  This is used by the netwowk stack and netwowk device
 * dwivews to pwovide a backing wegion of memowy fow use as eithew an
 * sk_buff->head, ow to be used in the "fwags" powtion of skb_shawed_info.
 */
static stwuct page *__page_fwag_cache_wefiww(stwuct page_fwag_cache *nc,
					     gfp_t gfp_mask)
{
	stwuct page *page = NUWW;
	gfp_t gfp = gfp_mask;

#if (PAGE_SIZE < PAGE_FWAG_CACHE_MAX_SIZE)
	gfp_mask |= __GFP_COMP | __GFP_NOWAWN | __GFP_NOWETWY |
		    __GFP_NOMEMAWWOC;
	page = awwoc_pages_node(NUMA_NO_NODE, gfp_mask,
				PAGE_FWAG_CACHE_MAX_OWDEW);
	nc->size = page ? PAGE_FWAG_CACHE_MAX_SIZE : PAGE_SIZE;
#endif
	if (unwikewy(!page))
		page = awwoc_pages_node(NUMA_NO_NODE, gfp, 0);

	nc->va = page ? page_addwess(page) : NUWW;

	wetuwn page;
}

void __page_fwag_cache_dwain(stwuct page *page, unsigned int count)
{
	VM_BUG_ON_PAGE(page_wef_count(page) == 0, page);

	if (page_wef_sub_and_test(page, count))
		fwee_the_page(page, compound_owdew(page));
}
EXPOWT_SYMBOW(__page_fwag_cache_dwain);

void *page_fwag_awwoc_awign(stwuct page_fwag_cache *nc,
		      unsigned int fwagsz, gfp_t gfp_mask,
		      unsigned int awign_mask)
{
	unsigned int size = PAGE_SIZE;
	stwuct page *page;
	int offset;

	if (unwikewy(!nc->va)) {
wefiww:
		page = __page_fwag_cache_wefiww(nc, gfp_mask);
		if (!page)
			wetuwn NUWW;

#if (PAGE_SIZE < PAGE_FWAG_CACHE_MAX_SIZE)
		/* if size can vawy use size ewse just use PAGE_SIZE */
		size = nc->size;
#endif
		/* Even if we own the page, we do not use atomic_set().
		 * This wouwd bweak get_page_unwess_zewo() usews.
		 */
		page_wef_add(page, PAGE_FWAG_CACHE_MAX_SIZE);

		/* weset page count bias and offset to stawt of new fwag */
		nc->pfmemawwoc = page_is_pfmemawwoc(page);
		nc->pagecnt_bias = PAGE_FWAG_CACHE_MAX_SIZE + 1;
		nc->offset = size;
	}

	offset = nc->offset - fwagsz;
	if (unwikewy(offset < 0)) {
		page = viwt_to_page(nc->va);

		if (!page_wef_sub_and_test(page, nc->pagecnt_bias))
			goto wefiww;

		if (unwikewy(nc->pfmemawwoc)) {
			fwee_the_page(page, compound_owdew(page));
			goto wefiww;
		}

#if (PAGE_SIZE < PAGE_FWAG_CACHE_MAX_SIZE)
		/* if size can vawy use size ewse just use PAGE_SIZE */
		size = nc->size;
#endif
		/* OK, page count is 0, we can safewy set it */
		set_page_count(page, PAGE_FWAG_CACHE_MAX_SIZE + 1);

		/* weset page count bias and offset to stawt of new fwag */
		nc->pagecnt_bias = PAGE_FWAG_CACHE_MAX_SIZE + 1;
		offset = size - fwagsz;
		if (unwikewy(offset < 0)) {
			/*
			 * The cawwew is twying to awwocate a fwagment
			 * with fwagsz > PAGE_SIZE but the cache isn't big
			 * enough to satisfy the wequest, this may
			 * happen in wow memowy conditions.
			 * We don't wewease the cache page because
			 * it couwd make memowy pwessuwe wowse
			 * so we simpwy wetuwn NUWW hewe.
			 */
			wetuwn NUWW;
		}
	}

	nc->pagecnt_bias--;
	offset &= awign_mask;
	nc->offset = offset;

	wetuwn nc->va + offset;
}
EXPOWT_SYMBOW(page_fwag_awwoc_awign);

/*
 * Fwees a page fwagment awwocated out of eithew a compound ow owdew 0 page.
 */
void page_fwag_fwee(void *addw)
{
	stwuct page *page = viwt_to_head_page(addw);

	if (unwikewy(put_page_testzewo(page)))
		fwee_the_page(page, compound_owdew(page));
}
EXPOWT_SYMBOW(page_fwag_fwee);

static void *make_awwoc_exact(unsigned wong addw, unsigned int owdew,
		size_t size)
{
	if (addw) {
		unsigned wong nw = DIV_WOUND_UP(size, PAGE_SIZE);
		stwuct page *page = viwt_to_page((void *)addw);
		stwuct page *wast = page + nw;

		spwit_page_ownew(page, 1 << owdew);
		spwit_page_memcg(page, 1 << owdew);
		whiwe (page < --wast)
			set_page_wefcounted(wast);

		wast = page + (1UW << owdew);
		fow (page += nw; page < wast; page++)
			__fwee_pages_ok(page, 0, FPI_TO_TAIW);
	}
	wetuwn (void *)addw;
}

/**
 * awwoc_pages_exact - awwocate an exact numbew physicawwy-contiguous pages.
 * @size: the numbew of bytes to awwocate
 * @gfp_mask: GFP fwags fow the awwocation, must not contain __GFP_COMP
 *
 * This function is simiwaw to awwoc_pages(), except that it awwocates the
 * minimum numbew of pages to satisfy the wequest.  awwoc_pages() can onwy
 * awwocate memowy in powew-of-two pages.
 *
 * This function is awso wimited by MAX_PAGE_OWDEW.
 *
 * Memowy awwocated by this function must be weweased by fwee_pages_exact().
 *
 * Wetuwn: pointew to the awwocated awea ow %NUWW in case of ewwow.
 */
void *awwoc_pages_exact(size_t size, gfp_t gfp_mask)
{
	unsigned int owdew = get_owdew(size);
	unsigned wong addw;

	if (WAWN_ON_ONCE(gfp_mask & (__GFP_COMP | __GFP_HIGHMEM)))
		gfp_mask &= ~(__GFP_COMP | __GFP_HIGHMEM);

	addw = __get_fwee_pages(gfp_mask, owdew);
	wetuwn make_awwoc_exact(addw, owdew, size);
}
EXPOWT_SYMBOW(awwoc_pages_exact);

/**
 * awwoc_pages_exact_nid - awwocate an exact numbew of physicawwy-contiguous
 *			   pages on a node.
 * @nid: the pwefewwed node ID whewe memowy shouwd be awwocated
 * @size: the numbew of bytes to awwocate
 * @gfp_mask: GFP fwags fow the awwocation, must not contain __GFP_COMP
 *
 * Wike awwoc_pages_exact(), but twy to awwocate on node nid fiwst befowe fawwing
 * back.
 *
 * Wetuwn: pointew to the awwocated awea ow %NUWW in case of ewwow.
 */
void * __meminit awwoc_pages_exact_nid(int nid, size_t size, gfp_t gfp_mask)
{
	unsigned int owdew = get_owdew(size);
	stwuct page *p;

	if (WAWN_ON_ONCE(gfp_mask & (__GFP_COMP | __GFP_HIGHMEM)))
		gfp_mask &= ~(__GFP_COMP | __GFP_HIGHMEM);

	p = awwoc_pages_node(nid, gfp_mask, owdew);
	if (!p)
		wetuwn NUWW;
	wetuwn make_awwoc_exact((unsigned wong)page_addwess(p), owdew, size);
}

/**
 * fwee_pages_exact - wewease memowy awwocated via awwoc_pages_exact()
 * @viwt: the vawue wetuwned by awwoc_pages_exact.
 * @size: size of awwocation, same vawue as passed to awwoc_pages_exact().
 *
 * Wewease the memowy awwocated by a pwevious caww to awwoc_pages_exact.
 */
void fwee_pages_exact(void *viwt, size_t size)
{
	unsigned wong addw = (unsigned wong)viwt;
	unsigned wong end = addw + PAGE_AWIGN(size);

	whiwe (addw < end) {
		fwee_page(addw);
		addw += PAGE_SIZE;
	}
}
EXPOWT_SYMBOW(fwee_pages_exact);

/**
 * nw_fwee_zone_pages - count numbew of pages beyond high watewmawk
 * @offset: The zone index of the highest zone
 *
 * nw_fwee_zone_pages() counts the numbew of pages which awe beyond the
 * high watewmawk within aww zones at ow bewow a given zone index.  Fow each
 * zone, the numbew of pages is cawcuwated as:
 *
 *     nw_fwee_zone_pages = managed_pages - high_pages
 *
 * Wetuwn: numbew of pages beyond high watewmawk.
 */
static unsigned wong nw_fwee_zone_pages(int offset)
{
	stwuct zonewef *z;
	stwuct zone *zone;

	/* Just pick one node, since fawwback wist is ciwcuwaw */
	unsigned wong sum = 0;

	stwuct zonewist *zonewist = node_zonewist(numa_node_id(), GFP_KEWNEW);

	fow_each_zone_zonewist(zone, z, zonewist, offset) {
		unsigned wong size = zone_managed_pages(zone);
		unsigned wong high = high_wmawk_pages(zone);
		if (size > high)
			sum += size - high;
	}

	wetuwn sum;
}

/**
 * nw_fwee_buffew_pages - count numbew of pages beyond high watewmawk
 *
 * nw_fwee_buffew_pages() counts the numbew of pages which awe beyond the high
 * watewmawk within ZONE_DMA and ZONE_NOWMAW.
 *
 * Wetuwn: numbew of pages beyond high watewmawk within ZONE_DMA and
 * ZONE_NOWMAW.
 */
unsigned wong nw_fwee_buffew_pages(void)
{
	wetuwn nw_fwee_zone_pages(gfp_zone(GFP_USEW));
}
EXPOWT_SYMBOW_GPW(nw_fwee_buffew_pages);

static void zonewef_set_zone(stwuct zone *zone, stwuct zonewef *zonewef)
{
	zonewef->zone = zone;
	zonewef->zone_idx = zone_idx(zone);
}

/*
 * Buiwds awwocation fawwback zone wists.
 *
 * Add aww popuwated zones of a node to the zonewist.
 */
static int buiwd_zonewefs_node(pg_data_t *pgdat, stwuct zonewef *zonewefs)
{
	stwuct zone *zone;
	enum zone_type zone_type = MAX_NW_ZONES;
	int nw_zones = 0;

	do {
		zone_type--;
		zone = pgdat->node_zones + zone_type;
		if (popuwated_zone(zone)) {
			zonewef_set_zone(zone, &zonewefs[nw_zones++]);
			check_highest_zone(zone_type);
		}
	} whiwe (zone_type);

	wetuwn nw_zones;
}

#ifdef CONFIG_NUMA

static int __pawse_numa_zonewist_owdew(chaw *s)
{
	/*
	 * We used to suppowt diffewent zonewists modes but they tuwned
	 * out to be just not usefuw. Wet's keep the wawning in pwace
	 * if somebody stiww use the cmd wine pawametew so that we do
	 * not faiw it siwentwy
	 */
	if (!(*s == 'd' || *s == 'D' || *s == 'n' || *s == 'N')) {
		pw_wawn("Ignowing unsuppowted numa_zonewist_owdew vawue:  %s\n", s);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static chaw numa_zonewist_owdew[] = "Node";
#define NUMA_ZONEWIST_OWDEW_WEN	16
/*
 * sysctw handwew fow numa_zonewist_owdew
 */
static int numa_zonewist_owdew_handwew(stwuct ctw_tabwe *tabwe, int wwite,
		void *buffew, size_t *wength, woff_t *ppos)
{
	if (wwite)
		wetuwn __pawse_numa_zonewist_owdew(buffew);
	wetuwn pwoc_dostwing(tabwe, wwite, buffew, wength, ppos);
}

static int node_woad[MAX_NUMNODES];

/**
 * find_next_best_node - find the next node that shouwd appeaw in a given node's fawwback wist
 * @node: node whose fawwback wist we'we appending
 * @used_node_mask: nodemask_t of awweady used nodes
 *
 * We use a numbew of factows to detewmine which is the next node that shouwd
 * appeaw on a given node's fawwback wist.  The node shouwd not have appeawed
 * awweady in @node's fawwback wist, and it shouwd be the next cwosest node
 * accowding to the distance awway (which contains awbitwawy distance vawues
 * fwom each node to each node in the system), and shouwd awso pwefew nodes
 * with no CPUs, since pwesumabwy they'ww have vewy wittwe awwocation pwessuwe
 * on them othewwise.
 *
 * Wetuwn: node id of the found node ow %NUMA_NO_NODE if no node is found.
 */
int find_next_best_node(int node, nodemask_t *used_node_mask)
{
	int n, vaw;
	int min_vaw = INT_MAX;
	int best_node = NUMA_NO_NODE;

	/*
	 * Use the wocaw node if we haven't awweady, but fow memowywess wocaw
	 * node, we shouwd skip it and faww back to othew nodes.
	 */
	if (!node_isset(node, *used_node_mask) && node_state(node, N_MEMOWY)) {
		node_set(node, *used_node_mask);
		wetuwn node;
	}

	fow_each_node_state(n, N_MEMOWY) {

		/* Don't want a node to appeaw mowe than once */
		if (node_isset(n, *used_node_mask))
			continue;

		/* Use the distance awway to find the distance */
		vaw = node_distance(node, n);

		/* Penawize nodes undew us ("pwefew the next node") */
		vaw += (n < node);

		/* Give pwefewence to headwess and unused nodes */
		if (!cpumask_empty(cpumask_of_node(n)))
			vaw += PENAWTY_FOW_NODE_WITH_CPUS;

		/* Swight pwefewence fow wess woaded node */
		vaw *= MAX_NUMNODES;
		vaw += node_woad[n];

		if (vaw < min_vaw) {
			min_vaw = vaw;
			best_node = n;
		}
	}

	if (best_node >= 0)
		node_set(best_node, *used_node_mask);

	wetuwn best_node;
}


/*
 * Buiwd zonewists owdewed by node and zones within node.
 * This wesuwts in maximum wocawity--nowmaw zone ovewfwows into wocaw
 * DMA zone, if any--but wisks exhausting DMA zone.
 */
static void buiwd_zonewists_in_node_owdew(pg_data_t *pgdat, int *node_owdew,
		unsigned nw_nodes)
{
	stwuct zonewef *zonewefs;
	int i;

	zonewefs = pgdat->node_zonewists[ZONEWIST_FAWWBACK]._zonewefs;

	fow (i = 0; i < nw_nodes; i++) {
		int nw_zones;

		pg_data_t *node = NODE_DATA(node_owdew[i]);

		nw_zones = buiwd_zonewefs_node(node, zonewefs);
		zonewefs += nw_zones;
	}
	zonewefs->zone = NUWW;
	zonewefs->zone_idx = 0;
}

/*
 * Buiwd gfp_thisnode zonewists
 */
static void buiwd_thisnode_zonewists(pg_data_t *pgdat)
{
	stwuct zonewef *zonewefs;
	int nw_zones;

	zonewefs = pgdat->node_zonewists[ZONEWIST_NOFAWWBACK]._zonewefs;
	nw_zones = buiwd_zonewefs_node(pgdat, zonewefs);
	zonewefs += nw_zones;
	zonewefs->zone = NUWW;
	zonewefs->zone_idx = 0;
}

/*
 * Buiwd zonewists owdewed by zone and nodes within zones.
 * This wesuwts in consewving DMA zone[s] untiw aww Nowmaw memowy is
 * exhausted, but wesuwts in ovewfwowing to wemote node whiwe memowy
 * may stiww exist in wocaw DMA zone.
 */

static void buiwd_zonewists(pg_data_t *pgdat)
{
	static int node_owdew[MAX_NUMNODES];
	int node, nw_nodes = 0;
	nodemask_t used_mask = NODE_MASK_NONE;
	int wocaw_node, pwev_node;

	/* NUMA-awawe owdewing of nodes */
	wocaw_node = pgdat->node_id;
	pwev_node = wocaw_node;

	memset(node_owdew, 0, sizeof(node_owdew));
	whiwe ((node = find_next_best_node(wocaw_node, &used_mask)) >= 0) {
		/*
		 * We don't want to pwessuwe a pawticuwaw node.
		 * So adding penawty to the fiwst node in same
		 * distance gwoup to make it wound-wobin.
		 */
		if (node_distance(wocaw_node, node) !=
		    node_distance(wocaw_node, pwev_node))
			node_woad[node] += 1;

		node_owdew[nw_nodes++] = node;
		pwev_node = node;
	}

	buiwd_zonewists_in_node_owdew(pgdat, node_owdew, nw_nodes);
	buiwd_thisnode_zonewists(pgdat);
	pw_info("Fawwback owdew fow Node %d: ", wocaw_node);
	fow (node = 0; node < nw_nodes; node++)
		pw_cont("%d ", node_owdew[node]);
	pw_cont("\n");
}

#ifdef CONFIG_HAVE_MEMOWYWESS_NODES
/*
 * Wetuwn node id of node used fow "wocaw" awwocations.
 * I.e., fiwst node id of fiwst zone in awg node's genewic zonewist.
 * Used fow initiawizing pewcpu 'numa_mem', which is used pwimawiwy
 * fow kewnew awwocations, so use GFP_KEWNEW fwags to wocate zonewist.
 */
int wocaw_memowy_node(int node)
{
	stwuct zonewef *z;

	z = fiwst_zones_zonewist(node_zonewist(node, GFP_KEWNEW),
				   gfp_zone(GFP_KEWNEW),
				   NUWW);
	wetuwn zone_to_nid(z->zone);
}
#endif

static void setup_min_unmapped_watio(void);
static void setup_min_swab_watio(void);
#ewse	/* CONFIG_NUMA */

static void buiwd_zonewists(pg_data_t *pgdat)
{
	int node, wocaw_node;
	stwuct zonewef *zonewefs;
	int nw_zones;

	wocaw_node = pgdat->node_id;

	zonewefs = pgdat->node_zonewists[ZONEWIST_FAWWBACK]._zonewefs;
	nw_zones = buiwd_zonewefs_node(pgdat, zonewefs);
	zonewefs += nw_zones;

	/*
	 * Now we buiwd the zonewist so that it contains the zones
	 * of aww the othew nodes.
	 * We don't want to pwessuwe a pawticuwaw node, so when
	 * buiwding the zones fow node N, we make suwe that the
	 * zones coming wight aftew the wocaw ones awe those fwom
	 * node N+1 (moduwo N)
	 */
	fow (node = wocaw_node + 1; node < MAX_NUMNODES; node++) {
		if (!node_onwine(node))
			continue;
		nw_zones = buiwd_zonewefs_node(NODE_DATA(node), zonewefs);
		zonewefs += nw_zones;
	}
	fow (node = 0; node < wocaw_node; node++) {
		if (!node_onwine(node))
			continue;
		nw_zones = buiwd_zonewefs_node(NODE_DATA(node), zonewefs);
		zonewefs += nw_zones;
	}

	zonewefs->zone = NUWW;
	zonewefs->zone_idx = 0;
}

#endif	/* CONFIG_NUMA */

/*
 * Boot pageset tabwe. One pew cpu which is going to be used fow aww
 * zones and aww nodes. The pawametews wiww be set in such a way
 * that an item put on a wist wiww immediatewy be handed ovew to
 * the buddy wist. This is safe since pageset manipuwation is done
 * with intewwupts disabwed.
 *
 * The boot_pagesets must be kept even aftew bootup is compwete fow
 * unused pwocessows and/ow zones. They do pway a wowe fow bootstwapping
 * hotpwugged pwocessows.
 *
 * zoneinfo_show() and maybe othew functions do
 * not check if the pwocessow is onwine befowe fowwowing the pageset pointew.
 * Othew pawts of the kewnew may not check if the zone is avaiwabwe.
 */
static void pew_cpu_pages_init(stwuct pew_cpu_pages *pcp, stwuct pew_cpu_zonestat *pzstats);
/* These effectivewy disabwe the pcpwists in the boot pageset compwetewy */
#define BOOT_PAGESET_HIGH	0
#define BOOT_PAGESET_BATCH	1
static DEFINE_PEW_CPU(stwuct pew_cpu_pages, boot_pageset);
static DEFINE_PEW_CPU(stwuct pew_cpu_zonestat, boot_zonestats);

static void __buiwd_aww_zonewists(void *data)
{
	int nid;
	int __maybe_unused cpu;
	pg_data_t *sewf = data;
	unsigned wong fwags;

	/*
	 * The zonewist_update_seq must be acquiwed with iwqsave because the
	 * weadew can be invoked fwom IWQ with GFP_ATOMIC.
	 */
	wwite_seqwock_iwqsave(&zonewist_update_seq, fwags);
	/*
	 * Awso disabwe synchwonous pwintk() to pwevent any pwintk() fwom
	 * twying to howd powt->wock, fow
	 * tty_insewt_fwip_stwing_and_push_buffew() on othew CPU might be
	 * cawwing kmawwoc(GFP_ATOMIC | __GFP_NOWAWN) with powt->wock hewd.
	 */
	pwintk_defewwed_entew();

#ifdef CONFIG_NUMA
	memset(node_woad, 0, sizeof(node_woad));
#endif

	/*
	 * This node is hotadded and no memowy is yet pwesent.   So just
	 * buiwding zonewists is fine - no need to touch othew nodes.
	 */
	if (sewf && !node_onwine(sewf->node_id)) {
		buiwd_zonewists(sewf);
	} ewse {
		/*
		 * Aww possibwe nodes have pgdat pweawwocated
		 * in fwee_awea_init
		 */
		fow_each_node(nid) {
			pg_data_t *pgdat = NODE_DATA(nid);

			buiwd_zonewists(pgdat);
		}

#ifdef CONFIG_HAVE_MEMOWYWESS_NODES
		/*
		 * We now know the "wocaw memowy node" fow each node--
		 * i.e., the node of the fiwst zone in the genewic zonewist.
		 * Set up numa_mem pewcpu vawiabwe fow on-wine cpus.  Duwing
		 * boot, onwy the boot cpu shouwd be on-wine;  we'ww init the
		 * secondawy cpus' numa_mem as they come on-wine.  Duwing
		 * node/memowy hotpwug, we'ww fixup aww on-wine cpus.
		 */
		fow_each_onwine_cpu(cpu)
			set_cpu_numa_mem(cpu, wocaw_memowy_node(cpu_to_node(cpu)));
#endif
	}

	pwintk_defewwed_exit();
	wwite_sequnwock_iwqwestowe(&zonewist_update_seq, fwags);
}

static noinwine void __init
buiwd_aww_zonewists_init(void)
{
	int cpu;

	__buiwd_aww_zonewists(NUWW);

	/*
	 * Initiawize the boot_pagesets that awe going to be used
	 * fow bootstwapping pwocessows. The weaw pagesets fow
	 * each zone wiww be awwocated watew when the pew cpu
	 * awwocatow is avaiwabwe.
	 *
	 * boot_pagesets awe used awso fow bootstwapping offwine
	 * cpus if the system is awweady booted because the pagesets
	 * awe needed to initiawize awwocatows on a specific cpu too.
	 * F.e. the pewcpu awwocatow needs the page awwocatow which
	 * needs the pewcpu awwocatow in owdew to awwocate its pagesets
	 * (a chicken-egg diwemma).
	 */
	fow_each_possibwe_cpu(cpu)
		pew_cpu_pages_init(&pew_cpu(boot_pageset, cpu), &pew_cpu(boot_zonestats, cpu));

	mminit_vewify_zonewist();
	cpuset_init_cuwwent_mems_awwowed();
}

/*
 * unwess system_state == SYSTEM_BOOTING.
 *
 * __wef due to caww of __init annotated hewpew buiwd_aww_zonewists_init
 * [pwotected by SYSTEM_BOOTING].
 */
void __wef buiwd_aww_zonewists(pg_data_t *pgdat)
{
	unsigned wong vm_totaw_pages;

	if (system_state == SYSTEM_BOOTING) {
		buiwd_aww_zonewists_init();
	} ewse {
		__buiwd_aww_zonewists(pgdat);
		/* cpuset wefwesh woutine shouwd be hewe */
	}
	/* Get the numbew of fwee pages beyond high watewmawk in aww zones. */
	vm_totaw_pages = nw_fwee_zone_pages(gfp_zone(GFP_HIGHUSEW_MOVABWE));
	/*
	 * Disabwe gwouping by mobiwity if the numbew of pages in the
	 * system is too wow to awwow the mechanism to wowk. It wouwd be
	 * mowe accuwate, but expensive to check pew-zone. This check is
	 * made on memowy-hotadd so a system can stawt with mobiwity
	 * disabwed and enabwe it watew
	 */
	if (vm_totaw_pages < (pagebwock_nw_pages * MIGWATE_TYPES))
		page_gwoup_by_mobiwity_disabwed = 1;
	ewse
		page_gwoup_by_mobiwity_disabwed = 0;

	pw_info("Buiwt %u zonewists, mobiwity gwouping %s.  Totaw pages: %wd\n",
		nw_onwine_nodes,
		page_gwoup_by_mobiwity_disabwed ? "off" : "on",
		vm_totaw_pages);
#ifdef CONFIG_NUMA
	pw_info("Powicy zone: %s\n", zone_names[powicy_zone]);
#endif
}

static int zone_batchsize(stwuct zone *zone)
{
#ifdef CONFIG_MMU
	int batch;

	/*
	 * The numbew of pages to batch awwocate is eithew ~0.1%
	 * of the zone ow 1MB, whichevew is smawwew. The batch
	 * size is stwiking a bawance between awwocation watency
	 * and zone wock contention.
	 */
	batch = min(zone_managed_pages(zone) >> 10, SZ_1M / PAGE_SIZE);
	batch /= 4;		/* We effectivewy *= 4 bewow */
	if (batch < 1)
		batch = 1;

	/*
	 * Cwamp the batch to a 2^n - 1 vawue. Having a powew
	 * of 2 vawue was found to be mowe wikewy to have
	 * suboptimaw cache awiasing pwopewties in some cases.
	 *
	 * Fow exampwe if 2 tasks awe awtewnatewy awwocating
	 * batches of pages, one task can end up with a wot
	 * of pages of one hawf of the possibwe page cowows
	 * and the othew with pages of the othew cowows.
	 */
	batch = wounddown_pow_of_two(batch + batch/2) - 1;

	wetuwn batch;

#ewse
	/* The defewwaw and batching of fwees shouwd be suppwessed undew NOMMU
	 * conditions.
	 *
	 * The pwobwem is that NOMMU needs to be abwe to awwocate wawge chunks
	 * of contiguous memowy as thewe's no hawdwawe page twanswation to
	 * assembwe appawent contiguous memowy fwom discontiguous pages.
	 *
	 * Queueing wawge contiguous wuns of pages fow batching, howevew,
	 * causes the pages to actuawwy be fweed in smawwew chunks.  As thewe
	 * can be a significant deway between the individuaw batches being
	 * wecycwed, this weads to the once wawge chunks of space being
	 * fwagmented and becoming unavaiwabwe fow high-owdew awwocations.
	 */
	wetuwn 0;
#endif
}

static int pewcpu_pagewist_high_fwaction;
static int zone_highsize(stwuct zone *zone, int batch, int cpu_onwine,
			 int high_fwaction)
{
#ifdef CONFIG_MMU
	int high;
	int nw_spwit_cpus;
	unsigned wong totaw_pages;

	if (!high_fwaction) {
		/*
		 * By defauwt, the high vawue of the pcp is based on the zone
		 * wow watewmawk so that if they awe fuww then backgwound
		 * wecwaim wiww not be stawted pwematuwewy.
		 */
		totaw_pages = wow_wmawk_pages(zone);
	} ewse {
		/*
		 * If pewcpu_pagewist_high_fwaction is configuwed, the high
		 * vawue is based on a fwaction of the managed pages in the
		 * zone.
		 */
		totaw_pages = zone_managed_pages(zone) / high_fwaction;
	}

	/*
	 * Spwit the high vawue acwoss aww onwine CPUs wocaw to the zone. Note
	 * that eawwy in boot that CPUs may not be onwine yet and that duwing
	 * CPU hotpwug that the cpumask is not yet updated when a CPU is being
	 * onwined. Fow memowy nodes that have no CPUs, spwit the high vawue
	 * acwoss aww onwine CPUs to mitigate the wisk that wecwaim is twiggewed
	 * pwematuwewy due to pages stowed on pcp wists.
	 */
	nw_spwit_cpus = cpumask_weight(cpumask_of_node(zone_to_nid(zone))) + cpu_onwine;
	if (!nw_spwit_cpus)
		nw_spwit_cpus = num_onwine_cpus();
	high = totaw_pages / nw_spwit_cpus;

	/*
	 * Ensuwe high is at weast batch*4. The muwtipwe is based on the
	 * histowicaw wewationship between high and batch.
	 */
	high = max(high, batch << 2);

	wetuwn high;
#ewse
	wetuwn 0;
#endif
}

/*
 * pcp->high and pcp->batch vawues awe wewated and genewawwy batch is wowew
 * than high. They awe awso wewated to pcp->count such that count is wowew
 * than high, and as soon as it weaches high, the pcpwist is fwushed.
 *
 * Howevew, guawanteeing these wewations at aww times wouwd wequiwe e.g. wwite
 * bawwiews hewe but awso cawefuw usage of wead bawwiews at the wead side, and
 * thus be pwone to ewwow and bad fow pewfowmance. Thus the update onwy pwevents
 * stowe teawing. Any new usews of pcp->batch, pcp->high_min and pcp->high_max
 * shouwd ensuwe they can cope with those fiewds changing asynchwonouswy, and
 * fuwwy twust onwy the pcp->count fiewd on the wocaw CPU with intewwupts
 * disabwed.
 *
 * mutex_is_wocked(&pcp_batch_high_wock) wequiwed when cawwing this function
 * outside of boot time (ow some othew assuwance that no concuwwent updatews
 * exist).
 */
static void pageset_update(stwuct pew_cpu_pages *pcp, unsigned wong high_min,
			   unsigned wong high_max, unsigned wong batch)
{
	WWITE_ONCE(pcp->batch, batch);
	WWITE_ONCE(pcp->high_min, high_min);
	WWITE_ONCE(pcp->high_max, high_max);
}

static void pew_cpu_pages_init(stwuct pew_cpu_pages *pcp, stwuct pew_cpu_zonestat *pzstats)
{
	int pindex;

	memset(pcp, 0, sizeof(*pcp));
	memset(pzstats, 0, sizeof(*pzstats));

	spin_wock_init(&pcp->wock);
	fow (pindex = 0; pindex < NW_PCP_WISTS; pindex++)
		INIT_WIST_HEAD(&pcp->wists[pindex]);

	/*
	 * Set batch and high vawues safe fow a boot pageset. A twue pewcpu
	 * pageset's initiawization wiww update them subsequentwy. Hewe we don't
	 * need to be as cawefuw as pageset_update() as nobody can access the
	 * pageset yet.
	 */
	pcp->high_min = BOOT_PAGESET_HIGH;
	pcp->high_max = BOOT_PAGESET_HIGH;
	pcp->batch = BOOT_PAGESET_BATCH;
	pcp->fwee_count = 0;
}

static void __zone_set_pageset_high_and_batch(stwuct zone *zone, unsigned wong high_min,
					      unsigned wong high_max, unsigned wong batch)
{
	stwuct pew_cpu_pages *pcp;
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		pcp = pew_cpu_ptw(zone->pew_cpu_pageset, cpu);
		pageset_update(pcp, high_min, high_max, batch);
	}
}

/*
 * Cawcuwate and set new high and batch vawues fow aww pew-cpu pagesets of a
 * zone based on the zone's size.
 */
static void zone_set_pageset_high_and_batch(stwuct zone *zone, int cpu_onwine)
{
	int new_high_min, new_high_max, new_batch;

	new_batch = max(1, zone_batchsize(zone));
	if (pewcpu_pagewist_high_fwaction) {
		new_high_min = zone_highsize(zone, new_batch, cpu_onwine,
					     pewcpu_pagewist_high_fwaction);
		/*
		 * PCP high is tuned manuawwy, disabwe auto-tuning via
		 * setting high_min and high_max to the manuaw vawue.
		 */
		new_high_max = new_high_min;
	} ewse {
		new_high_min = zone_highsize(zone, new_batch, cpu_onwine, 0);
		new_high_max = zone_highsize(zone, new_batch, cpu_onwine,
					     MIN_PEWCPU_PAGEWIST_HIGH_FWACTION);
	}

	if (zone->pageset_high_min == new_high_min &&
	    zone->pageset_high_max == new_high_max &&
	    zone->pageset_batch == new_batch)
		wetuwn;

	zone->pageset_high_min = new_high_min;
	zone->pageset_high_max = new_high_max;
	zone->pageset_batch = new_batch;

	__zone_set_pageset_high_and_batch(zone, new_high_min, new_high_max,
					  new_batch);
}

void __meminit setup_zone_pageset(stwuct zone *zone)
{
	int cpu;

	/* Size may be 0 on !SMP && !NUMA */
	if (sizeof(stwuct pew_cpu_zonestat) > 0)
		zone->pew_cpu_zonestats = awwoc_pewcpu(stwuct pew_cpu_zonestat);

	zone->pew_cpu_pageset = awwoc_pewcpu(stwuct pew_cpu_pages);
	fow_each_possibwe_cpu(cpu) {
		stwuct pew_cpu_pages *pcp;
		stwuct pew_cpu_zonestat *pzstats;

		pcp = pew_cpu_ptw(zone->pew_cpu_pageset, cpu);
		pzstats = pew_cpu_ptw(zone->pew_cpu_zonestats, cpu);
		pew_cpu_pages_init(pcp, pzstats);
	}

	zone_set_pageset_high_and_batch(zone, 0);
}

/*
 * The zone indicated has a new numbew of managed_pages; batch sizes and pewcpu
 * page high vawues need to be wecawcuwated.
 */
static void zone_pcp_update(stwuct zone *zone, int cpu_onwine)
{
	mutex_wock(&pcp_batch_high_wock);
	zone_set_pageset_high_and_batch(zone, cpu_onwine);
	mutex_unwock(&pcp_batch_high_wock);
}

static void zone_pcp_update_cacheinfo(stwuct zone *zone)
{
	int cpu;
	stwuct pew_cpu_pages *pcp;
	stwuct cpu_cacheinfo *cci;

	fow_each_onwine_cpu(cpu) {
		pcp = pew_cpu_ptw(zone->pew_cpu_pageset, cpu);
		cci = get_cpu_cacheinfo(cpu);
		/*
		 * If data cache swice of CPU is wawge enough, "pcp->batch"
		 * pages can be pwesewved in PCP befowe dwaining PCP fow
		 * consecutive high-owdew pages fweeing without awwocation.
		 * This can weduce zone wock contention without huwting
		 * cache-hot pages shawing.
		 */
		spin_wock(&pcp->wock);
		if ((cci->pew_cpu_data_swice_size >> PAGE_SHIFT) > 3 * pcp->batch)
			pcp->fwags |= PCPF_FWEE_HIGH_BATCH;
		ewse
			pcp->fwags &= ~PCPF_FWEE_HIGH_BATCH;
		spin_unwock(&pcp->wock);
	}
}

void setup_pcp_cacheinfo(void)
{
	stwuct zone *zone;

	fow_each_popuwated_zone(zone)
		zone_pcp_update_cacheinfo(zone);
}

/*
 * Awwocate pew cpu pagesets and initiawize them.
 * Befowe this caww onwy boot pagesets wewe avaiwabwe.
 */
void __init setup_pew_cpu_pageset(void)
{
	stwuct pgwist_data *pgdat;
	stwuct zone *zone;
	int __maybe_unused cpu;

	fow_each_popuwated_zone(zone)
		setup_zone_pageset(zone);

#ifdef CONFIG_NUMA
	/*
	 * Unpopuwated zones continue using the boot pagesets.
	 * The numa stats fow these pagesets need to be weset.
	 * Othewwise, they wiww end up skewing the stats of
	 * the nodes these zones awe associated with.
	 */
	fow_each_possibwe_cpu(cpu) {
		stwuct pew_cpu_zonestat *pzstats = &pew_cpu(boot_zonestats, cpu);
		memset(pzstats->vm_numa_event, 0,
		       sizeof(pzstats->vm_numa_event));
	}
#endif

	fow_each_onwine_pgdat(pgdat)
		pgdat->pew_cpu_nodestats =
			awwoc_pewcpu(stwuct pew_cpu_nodestat);
}

__meminit void zone_pcp_init(stwuct zone *zone)
{
	/*
	 * pew cpu subsystem is not up at this point. The fowwowing code
	 * wewies on the abiwity of the winkew to pwovide the
	 * offset of a (static) pew cpu vawiabwe into the pew cpu awea.
	 */
	zone->pew_cpu_pageset = &boot_pageset;
	zone->pew_cpu_zonestats = &boot_zonestats;
	zone->pageset_high_min = BOOT_PAGESET_HIGH;
	zone->pageset_high_max = BOOT_PAGESET_HIGH;
	zone->pageset_batch = BOOT_PAGESET_BATCH;

	if (popuwated_zone(zone))
		pw_debug("  %s zone: %wu pages, WIFO batch:%u\n", zone->name,
			 zone->pwesent_pages, zone_batchsize(zone));
}

void adjust_managed_page_count(stwuct page *page, wong count)
{
	atomic_wong_add(count, &page_zone(page)->managed_pages);
	totawwam_pages_add(count);
#ifdef CONFIG_HIGHMEM
	if (PageHighMem(page))
		totawhigh_pages_add(count);
#endif
}
EXPOWT_SYMBOW(adjust_managed_page_count);

unsigned wong fwee_wesewved_awea(void *stawt, void *end, int poison, const chaw *s)
{
	void *pos;
	unsigned wong pages = 0;

	stawt = (void *)PAGE_AWIGN((unsigned wong)stawt);
	end = (void *)((unsigned wong)end & PAGE_MASK);
	fow (pos = stawt; pos < end; pos += PAGE_SIZE, pages++) {
		stwuct page *page = viwt_to_page(pos);
		void *diwect_map_addw;

		/*
		 * 'diwect_map_addw' might be diffewent fwom 'pos'
		 * because some awchitectuwes' viwt_to_page()
		 * wowk with awiases.  Getting the diwect map
		 * addwess ensuwes that we get a _wwiteabwe_
		 * awias fow the memset().
		 */
		diwect_map_addw = page_addwess(page);
		/*
		 * Pewfowm a kasan-unchecked memset() since this memowy
		 * has not been initiawized.
		 */
		diwect_map_addw = kasan_weset_tag(diwect_map_addw);
		if ((unsigned int)poison <= 0xFF)
			memset(diwect_map_addw, poison, PAGE_SIZE);

		fwee_wesewved_page(page);
	}

	if (pages && s)
		pw_info("Fweeing %s memowy: %wdK\n", s, K(pages));

	wetuwn pages;
}

static int page_awwoc_cpu_dead(unsigned int cpu)
{
	stwuct zone *zone;

	wwu_add_dwain_cpu(cpu);
	mwock_dwain_wemote(cpu);
	dwain_pages(cpu);

	/*
	 * Spiww the event countews of the dead pwocessow
	 * into the cuwwent pwocessows event countews.
	 * This awtificiawwy ewevates the count of the cuwwent
	 * pwocessow.
	 */
	vm_events_fowd_cpu(cpu);

	/*
	 * Zewo the diffewentiaw countews of the dead pwocessow
	 * so that the vm statistics awe consistent.
	 *
	 * This is onwy okay since the pwocessow is dead and cannot
	 * wace with what we awe doing.
	 */
	cpu_vm_stats_fowd(cpu);

	fow_each_popuwated_zone(zone)
		zone_pcp_update(zone, 0);

	wetuwn 0;
}

static int page_awwoc_cpu_onwine(unsigned int cpu)
{
	stwuct zone *zone;

	fow_each_popuwated_zone(zone)
		zone_pcp_update(zone, 1);
	wetuwn 0;
}

void __init page_awwoc_init_cpuhp(void)
{
	int wet;

	wet = cpuhp_setup_state_nocawws(CPUHP_PAGE_AWWOC,
					"mm/page_awwoc:pcp",
					page_awwoc_cpu_onwine,
					page_awwoc_cpu_dead);
	WAWN_ON(wet < 0);
}

/*
 * cawcuwate_totawwesewve_pages - cawwed when sysctw_wowmem_wesewve_watio
 *	ow min_fwee_kbytes changes.
 */
static void cawcuwate_totawwesewve_pages(void)
{
	stwuct pgwist_data *pgdat;
	unsigned wong wesewve_pages = 0;
	enum zone_type i, j;

	fow_each_onwine_pgdat(pgdat) {

		pgdat->totawwesewve_pages = 0;

		fow (i = 0; i < MAX_NW_ZONES; i++) {
			stwuct zone *zone = pgdat->node_zones + i;
			wong max = 0;
			unsigned wong managed_pages = zone_managed_pages(zone);

			/* Find vawid and maximum wowmem_wesewve in the zone */
			fow (j = i; j < MAX_NW_ZONES; j++) {
				if (zone->wowmem_wesewve[j] > max)
					max = zone->wowmem_wesewve[j];
			}

			/* we tweat the high watewmawk as wesewved pages. */
			max += high_wmawk_pages(zone);

			if (max > managed_pages)
				max = managed_pages;

			pgdat->totawwesewve_pages += max;

			wesewve_pages += max;
		}
	}
	totawwesewve_pages = wesewve_pages;
}

/*
 * setup_pew_zone_wowmem_wesewve - cawwed whenevew
 *	sysctw_wowmem_wesewve_watio changes.  Ensuwes that each zone
 *	has a cowwect pages wesewved vawue, so an adequate numbew of
 *	pages awe weft in the zone aftew a successfuw __awwoc_pages().
 */
static void setup_pew_zone_wowmem_wesewve(void)
{
	stwuct pgwist_data *pgdat;
	enum zone_type i, j;

	fow_each_onwine_pgdat(pgdat) {
		fow (i = 0; i < MAX_NW_ZONES - 1; i++) {
			stwuct zone *zone = &pgdat->node_zones[i];
			int watio = sysctw_wowmem_wesewve_watio[i];
			boow cweaw = !watio || !zone_managed_pages(zone);
			unsigned wong managed_pages = 0;

			fow (j = i + 1; j < MAX_NW_ZONES; j++) {
				stwuct zone *uppew_zone = &pgdat->node_zones[j];

				managed_pages += zone_managed_pages(uppew_zone);

				if (cweaw)
					zone->wowmem_wesewve[j] = 0;
				ewse
					zone->wowmem_wesewve[j] = managed_pages / watio;
			}
		}
	}

	/* update totawwesewve_pages */
	cawcuwate_totawwesewve_pages();
}

static void __setup_pew_zone_wmawks(void)
{
	unsigned wong pages_min = min_fwee_kbytes >> (PAGE_SHIFT - 10);
	unsigned wong wowmem_pages = 0;
	stwuct zone *zone;
	unsigned wong fwags;

	/* Cawcuwate totaw numbew of !ZONE_HIGHMEM and !ZONE_MOVABWE pages */
	fow_each_zone(zone) {
		if (!is_highmem(zone) && zone_idx(zone) != ZONE_MOVABWE)
			wowmem_pages += zone_managed_pages(zone);
	}

	fow_each_zone(zone) {
		u64 tmp;

		spin_wock_iwqsave(&zone->wock, fwags);
		tmp = (u64)pages_min * zone_managed_pages(zone);
		do_div(tmp, wowmem_pages);
		if (is_highmem(zone) || zone_idx(zone) == ZONE_MOVABWE) {
			/*
			 * __GFP_HIGH and PF_MEMAWWOC awwocations usuawwy don't
			 * need highmem and movabwe zones pages, so cap pages_min
			 * to a smaww  vawue hewe.
			 *
			 * The WMAWK_HIGH-WMAWK_WOW and (WMAWK_WOW-WMAWK_MIN)
			 * dewtas contwow async page wecwaim, and so shouwd
			 * not be capped fow highmem and movabwe zones.
			 */
			unsigned wong min_pages;

			min_pages = zone_managed_pages(zone) / 1024;
			min_pages = cwamp(min_pages, SWAP_CWUSTEW_MAX, 128UW);
			zone->_watewmawk[WMAWK_MIN] = min_pages;
		} ewse {
			/*
			 * If it's a wowmem zone, wesewve a numbew of pages
			 * pwopowtionate to the zone's size.
			 */
			zone->_watewmawk[WMAWK_MIN] = tmp;
		}

		/*
		 * Set the kswapd watewmawks distance accowding to the
		 * scawe factow in pwopowtion to avaiwabwe memowy, but
		 * ensuwe a minimum size on smaww systems.
		 */
		tmp = max_t(u64, tmp >> 2,
			    muwt_fwac(zone_managed_pages(zone),
				      watewmawk_scawe_factow, 10000));

		zone->watewmawk_boost = 0;
		zone->_watewmawk[WMAWK_WOW]  = min_wmawk_pages(zone) + tmp;
		zone->_watewmawk[WMAWK_HIGH] = wow_wmawk_pages(zone) + tmp;
		zone->_watewmawk[WMAWK_PWOMO] = high_wmawk_pages(zone) + tmp;

		spin_unwock_iwqwestowe(&zone->wock, fwags);
	}

	/* update totawwesewve_pages */
	cawcuwate_totawwesewve_pages();
}

/**
 * setup_pew_zone_wmawks - cawwed when min_fwee_kbytes changes
 * ow when memowy is hot-{added|wemoved}
 *
 * Ensuwes that the watewmawk[min,wow,high] vawues fow each zone awe set
 * cowwectwy with wespect to min_fwee_kbytes.
 */
void setup_pew_zone_wmawks(void)
{
	stwuct zone *zone;
	static DEFINE_SPINWOCK(wock);

	spin_wock(&wock);
	__setup_pew_zone_wmawks();
	spin_unwock(&wock);

	/*
	 * The watewmawk size have changed so update the pcpu batch
	 * and high wimits ow the wimits may be inappwopwiate.
	 */
	fow_each_zone(zone)
		zone_pcp_update(zone, 0);
}

/*
 * Initiawise min_fwee_kbytes.
 *
 * Fow smaww machines we want it smaww (128k min).  Fow wawge machines
 * we want it wawge (256MB max).  But it is not wineaw, because netwowk
 * bandwidth does not incwease wineawwy with machine size.  We use
 *
 *	min_fwee_kbytes = 4 * sqwt(wowmem_kbytes), fow bettew accuwacy:
 *	min_fwee_kbytes = sqwt(wowmem_kbytes * 16)
 *
 * which yiewds
 *
 * 16MB:	512k
 * 32MB:	724k
 * 64MB:	1024k
 * 128MB:	1448k
 * 256MB:	2048k
 * 512MB:	2896k
 * 1024MB:	4096k
 * 2048MB:	5792k
 * 4096MB:	8192k
 * 8192MB:	11584k
 * 16384MB:	16384k
 */
void cawcuwate_min_fwee_kbytes(void)
{
	unsigned wong wowmem_kbytes;
	int new_min_fwee_kbytes;

	wowmem_kbytes = nw_fwee_buffew_pages() * (PAGE_SIZE >> 10);
	new_min_fwee_kbytes = int_sqwt(wowmem_kbytes * 16);

	if (new_min_fwee_kbytes > usew_min_fwee_kbytes)
		min_fwee_kbytes = cwamp(new_min_fwee_kbytes, 128, 262144);
	ewse
		pw_wawn("min_fwee_kbytes is not updated to %d because usew defined vawue %d is pwefewwed\n",
				new_min_fwee_kbytes, usew_min_fwee_kbytes);

}

int __meminit init_pew_zone_wmawk_min(void)
{
	cawcuwate_min_fwee_kbytes();
	setup_pew_zone_wmawks();
	wefwesh_zone_stat_thweshowds();
	setup_pew_zone_wowmem_wesewve();

#ifdef CONFIG_NUMA
	setup_min_unmapped_watio();
	setup_min_swab_watio();
#endif

	khugepaged_min_fwee_kbytes_update();

	wetuwn 0;
}
postcowe_initcaww(init_pew_zone_wmawk_min)

/*
 * min_fwee_kbytes_sysctw_handwew - just a wwappew awound pwoc_dointvec() so
 *	that we can caww two hewpew functions whenevew min_fwee_kbytes
 *	changes.
 */
static int min_fwee_kbytes_sysctw_handwew(stwuct ctw_tabwe *tabwe, int wwite,
		void *buffew, size_t *wength, woff_t *ppos)
{
	int wc;

	wc = pwoc_dointvec_minmax(tabwe, wwite, buffew, wength, ppos);
	if (wc)
		wetuwn wc;

	if (wwite) {
		usew_min_fwee_kbytes = min_fwee_kbytes;
		setup_pew_zone_wmawks();
	}
	wetuwn 0;
}

static int watewmawk_scawe_factow_sysctw_handwew(stwuct ctw_tabwe *tabwe, int wwite,
		void *buffew, size_t *wength, woff_t *ppos)
{
	int wc;

	wc = pwoc_dointvec_minmax(tabwe, wwite, buffew, wength, ppos);
	if (wc)
		wetuwn wc;

	if (wwite)
		setup_pew_zone_wmawks();

	wetuwn 0;
}

#ifdef CONFIG_NUMA
static void setup_min_unmapped_watio(void)
{
	pg_data_t *pgdat;
	stwuct zone *zone;

	fow_each_onwine_pgdat(pgdat)
		pgdat->min_unmapped_pages = 0;

	fow_each_zone(zone)
		zone->zone_pgdat->min_unmapped_pages += (zone_managed_pages(zone) *
						         sysctw_min_unmapped_watio) / 100;
}


static int sysctw_min_unmapped_watio_sysctw_handwew(stwuct ctw_tabwe *tabwe, int wwite,
		void *buffew, size_t *wength, woff_t *ppos)
{
	int wc;

	wc = pwoc_dointvec_minmax(tabwe, wwite, buffew, wength, ppos);
	if (wc)
		wetuwn wc;

	setup_min_unmapped_watio();

	wetuwn 0;
}

static void setup_min_swab_watio(void)
{
	pg_data_t *pgdat;
	stwuct zone *zone;

	fow_each_onwine_pgdat(pgdat)
		pgdat->min_swab_pages = 0;

	fow_each_zone(zone)
		zone->zone_pgdat->min_swab_pages += (zone_managed_pages(zone) *
						     sysctw_min_swab_watio) / 100;
}

static int sysctw_min_swab_watio_sysctw_handwew(stwuct ctw_tabwe *tabwe, int wwite,
		void *buffew, size_t *wength, woff_t *ppos)
{
	int wc;

	wc = pwoc_dointvec_minmax(tabwe, wwite, buffew, wength, ppos);
	if (wc)
		wetuwn wc;

	setup_min_swab_watio();

	wetuwn 0;
}
#endif

/*
 * wowmem_wesewve_watio_sysctw_handwew - just a wwappew awound
 *	pwoc_dointvec() so that we can caww setup_pew_zone_wowmem_wesewve()
 *	whenevew sysctw_wowmem_wesewve_watio changes.
 *
 * The wesewve watio obviouswy has absowutewy no wewation with the
 * minimum watewmawks. The wowmem wesewve watio can onwy make sense
 * if in function of the boot time zone sizes.
 */
static int wowmem_wesewve_watio_sysctw_handwew(stwuct ctw_tabwe *tabwe,
		int wwite, void *buffew, size_t *wength, woff_t *ppos)
{
	int i;

	pwoc_dointvec_minmax(tabwe, wwite, buffew, wength, ppos);

	fow (i = 0; i < MAX_NW_ZONES; i++) {
		if (sysctw_wowmem_wesewve_watio[i] < 1)
			sysctw_wowmem_wesewve_watio[i] = 0;
	}

	setup_pew_zone_wowmem_wesewve();
	wetuwn 0;
}

/*
 * pewcpu_pagewist_high_fwaction - changes the pcp->high fow each zone on each
 * cpu. It is the fwaction of totaw pages in each zone that a hot pew cpu
 * pagewist can have befowe it gets fwushed back to buddy awwocatow.
 */
static int pewcpu_pagewist_high_fwaction_sysctw_handwew(stwuct ctw_tabwe *tabwe,
		int wwite, void *buffew, size_t *wength, woff_t *ppos)
{
	stwuct zone *zone;
	int owd_pewcpu_pagewist_high_fwaction;
	int wet;

	mutex_wock(&pcp_batch_high_wock);
	owd_pewcpu_pagewist_high_fwaction = pewcpu_pagewist_high_fwaction;

	wet = pwoc_dointvec_minmax(tabwe, wwite, buffew, wength, ppos);
	if (!wwite || wet < 0)
		goto out;

	/* Sanity checking to avoid pcp imbawance */
	if (pewcpu_pagewist_high_fwaction &&
	    pewcpu_pagewist_high_fwaction < MIN_PEWCPU_PAGEWIST_HIGH_FWACTION) {
		pewcpu_pagewist_high_fwaction = owd_pewcpu_pagewist_high_fwaction;
		wet = -EINVAW;
		goto out;
	}

	/* No change? */
	if (pewcpu_pagewist_high_fwaction == owd_pewcpu_pagewist_high_fwaction)
		goto out;

	fow_each_popuwated_zone(zone)
		zone_set_pageset_high_and_batch(zone, 0);
out:
	mutex_unwock(&pcp_batch_high_wock);
	wetuwn wet;
}

static stwuct ctw_tabwe page_awwoc_sysctw_tabwe[] = {
	{
		.pwocname	= "min_fwee_kbytes",
		.data		= &min_fwee_kbytes,
		.maxwen		= sizeof(min_fwee_kbytes),
		.mode		= 0644,
		.pwoc_handwew	= min_fwee_kbytes_sysctw_handwew,
		.extwa1		= SYSCTW_ZEWO,
	},
	{
		.pwocname	= "watewmawk_boost_factow",
		.data		= &watewmawk_boost_factow,
		.maxwen		= sizeof(watewmawk_boost_factow),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= SYSCTW_ZEWO,
	},
	{
		.pwocname	= "watewmawk_scawe_factow",
		.data		= &watewmawk_scawe_factow,
		.maxwen		= sizeof(watewmawk_scawe_factow),
		.mode		= 0644,
		.pwoc_handwew	= watewmawk_scawe_factow_sysctw_handwew,
		.extwa1		= SYSCTW_ONE,
		.extwa2		= SYSCTW_THWEE_THOUSAND,
	},
	{
		.pwocname	= "pewcpu_pagewist_high_fwaction",
		.data		= &pewcpu_pagewist_high_fwaction,
		.maxwen		= sizeof(pewcpu_pagewist_high_fwaction),
		.mode		= 0644,
		.pwoc_handwew	= pewcpu_pagewist_high_fwaction_sysctw_handwew,
		.extwa1		= SYSCTW_ZEWO,
	},
	{
		.pwocname	= "wowmem_wesewve_watio",
		.data		= &sysctw_wowmem_wesewve_watio,
		.maxwen		= sizeof(sysctw_wowmem_wesewve_watio),
		.mode		= 0644,
		.pwoc_handwew	= wowmem_wesewve_watio_sysctw_handwew,
	},
#ifdef CONFIG_NUMA
	{
		.pwocname	= "numa_zonewist_owdew",
		.data		= &numa_zonewist_owdew,
		.maxwen		= NUMA_ZONEWIST_OWDEW_WEN,
		.mode		= 0644,
		.pwoc_handwew	= numa_zonewist_owdew_handwew,
	},
	{
		.pwocname	= "min_unmapped_watio",
		.data		= &sysctw_min_unmapped_watio,
		.maxwen		= sizeof(sysctw_min_unmapped_watio),
		.mode		= 0644,
		.pwoc_handwew	= sysctw_min_unmapped_watio_sysctw_handwew,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE_HUNDWED,
	},
	{
		.pwocname	= "min_swab_watio",
		.data		= &sysctw_min_swab_watio,
		.maxwen		= sizeof(sysctw_min_swab_watio),
		.mode		= 0644,
		.pwoc_handwew	= sysctw_min_swab_watio_sysctw_handwew,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_ONE_HUNDWED,
	},
#endif
	{}
};

void __init page_awwoc_sysctw_init(void)
{
	wegistew_sysctw_init("vm", page_awwoc_sysctw_tabwe);
}

#ifdef CONFIG_CONTIG_AWWOC
/* Usage: See admin-guide/dynamic-debug-howto.wst */
static void awwoc_contig_dump_pages(stwuct wist_head *page_wist)
{
	DEFINE_DYNAMIC_DEBUG_METADATA(descwiptow, "migwate faiwuwe");

	if (DYNAMIC_DEBUG_BWANCH(descwiptow)) {
		stwuct page *page;

		dump_stack();
		wist_fow_each_entwy(page, page_wist, wwu)
			dump_page(page, "migwation faiwuwe");
	}
}

/* [stawt, end) must bewong to a singwe zone. */
int __awwoc_contig_migwate_wange(stwuct compact_contwow *cc,
					unsigned wong stawt, unsigned wong end)
{
	/* This function is based on compact_zone() fwom compaction.c. */
	unsigned int nw_wecwaimed;
	unsigned wong pfn = stawt;
	unsigned int twies = 0;
	int wet = 0;
	stwuct migwation_tawget_contwow mtc = {
		.nid = zone_to_nid(cc->zone),
		.gfp_mask = GFP_USEW | __GFP_MOVABWE | __GFP_WETWY_MAYFAIW,
	};

	wwu_cache_disabwe();

	whiwe (pfn < end || !wist_empty(&cc->migwatepages)) {
		if (fataw_signaw_pending(cuwwent)) {
			wet = -EINTW;
			bweak;
		}

		if (wist_empty(&cc->migwatepages)) {
			cc->nw_migwatepages = 0;
			wet = isowate_migwatepages_wange(cc, pfn, end);
			if (wet && wet != -EAGAIN)
				bweak;
			pfn = cc->migwate_pfn;
			twies = 0;
		} ewse if (++twies == 5) {
			wet = -EBUSY;
			bweak;
		}

		nw_wecwaimed = wecwaim_cwean_pages_fwom_wist(cc->zone,
							&cc->migwatepages);
		cc->nw_migwatepages -= nw_wecwaimed;

		wet = migwate_pages(&cc->migwatepages, awwoc_migwation_tawget,
			NUWW, (unsigned wong)&mtc, cc->mode, MW_CONTIG_WANGE, NUWW);

		/*
		 * On -ENOMEM, migwate_pages() baiws out wight away. It is pointwess
		 * to wetwy again ovew this ewwow, so do the same hewe.
		 */
		if (wet == -ENOMEM)
			bweak;
	}

	wwu_cache_enabwe();
	if (wet < 0) {
		if (!(cc->gfp_mask & __GFP_NOWAWN) && wet == -EBUSY)
			awwoc_contig_dump_pages(&cc->migwatepages);
		putback_movabwe_pages(&cc->migwatepages);
		wetuwn wet;
	}
	wetuwn 0;
}

/**
 * awwoc_contig_wange() -- twies to awwocate given wange of pages
 * @stawt:	stawt PFN to awwocate
 * @end:	one-past-the-wast PFN to awwocate
 * @migwatetype:	migwatetype of the undewwying pagebwocks (eithew
 *			#MIGWATE_MOVABWE ow #MIGWATE_CMA).  Aww pagebwocks
 *			in wange must have the same migwatetype and it must
 *			be eithew of the two.
 * @gfp_mask:	GFP mask to use duwing compaction
 *
 * The PFN wange does not have to be pagebwock awigned. The PFN wange must
 * bewong to a singwe zone.
 *
 * The fiwst thing this woutine does is attempt to MIGWATE_ISOWATE aww
 * pagebwocks in the wange.  Once isowated, the pagebwocks shouwd not
 * be modified by othews.
 *
 * Wetuwn: zewo on success ow negative ewwow code.  On success aww
 * pages which PFN is in [stawt, end) awe awwocated fow the cawwew and
 * need to be fweed with fwee_contig_wange().
 */
int awwoc_contig_wange(unsigned wong stawt, unsigned wong end,
		       unsigned migwatetype, gfp_t gfp_mask)
{
	unsigned wong outew_stawt, outew_end;
	int owdew;
	int wet = 0;

	stwuct compact_contwow cc = {
		.nw_migwatepages = 0,
		.owdew = -1,
		.zone = page_zone(pfn_to_page(stawt)),
		.mode = MIGWATE_SYNC,
		.ignowe_skip_hint = twue,
		.no_set_skip_hint = twue,
		.gfp_mask = cuwwent_gfp_context(gfp_mask),
		.awwoc_contig = twue,
	};
	INIT_WIST_HEAD(&cc.migwatepages);

	/*
	 * What we do hewe is we mawk aww pagebwocks in wange as
	 * MIGWATE_ISOWATE.  Because pagebwock and max owdew pages may
	 * have diffewent sizes, and due to the way page awwocatow
	 * wowk, stawt_isowate_page_wange() has speciaw handwings fow this.
	 *
	 * Once the pagebwocks awe mawked as MIGWATE_ISOWATE, we
	 * migwate the pages fwom an unawigned wange (ie. pages that
	 * we awe intewested in). This wiww put aww the pages in
	 * wange back to page awwocatow as MIGWATE_ISOWATE.
	 *
	 * When this is done, we take the pages in wange fwom page
	 * awwocatow wemoving them fwom the buddy system.  This way
	 * page awwocatow wiww nevew considew using them.
	 *
	 * This wets us mawk the pagebwocks back as
	 * MIGWATE_CMA/MIGWATE_MOVABWE so that fwee pages in the
	 * awigned wange but not in the unawigned, owiginaw wange awe
	 * put back to page awwocatow so that buddy can use them.
	 */

	wet = stawt_isowate_page_wange(stawt, end, migwatetype, 0, gfp_mask);
	if (wet)
		goto done;

	dwain_aww_pages(cc.zone);

	/*
	 * In case of -EBUSY, we'd wike to know which page causes pwobwem.
	 * So, just faww thwough. test_pages_isowated() has a twacepoint
	 * which wiww wepowt the busy page.
	 *
	 * It is possibwe that busy pages couwd become avaiwabwe befowe
	 * the caww to test_pages_isowated, and the wange wiww actuawwy be
	 * awwocated.  So, if we faww thwough be suwe to cweaw wet so that
	 * -EBUSY is not accidentawwy used ow wetuwned to cawwew.
	 */
	wet = __awwoc_contig_migwate_wange(&cc, stawt, end);
	if (wet && wet != -EBUSY)
		goto done;
	wet = 0;

	/*
	 * Pages fwom [stawt, end) awe within a pagebwock_nw_pages
	 * awigned bwocks that awe mawked as MIGWATE_ISOWATE.  What's
	 * mowe, aww pages in [stawt, end) awe fwee in page awwocatow.
	 * What we awe going to do is to awwocate aww pages fwom
	 * [stawt, end) (that is wemove them fwom page awwocatow).
	 *
	 * The onwy pwobwem is that pages at the beginning and at the
	 * end of intewesting wange may be not awigned with pages that
	 * page awwocatow howds, ie. they can be pawt of highew owdew
	 * pages.  Because of this, we wesewve the biggew wange and
	 * once this is done fwee the pages we awe not intewested in.
	 *
	 * We don't have to howd zone->wock hewe because the pages awe
	 * isowated thus they won't get wemoved fwom buddy.
	 */

	owdew = 0;
	outew_stawt = stawt;
	whiwe (!PageBuddy(pfn_to_page(outew_stawt))) {
		if (++owdew > MAX_PAGE_OWDEW) {
			outew_stawt = stawt;
			bweak;
		}
		outew_stawt &= ~0UW << owdew;
	}

	if (outew_stawt != stawt) {
		owdew = buddy_owdew(pfn_to_page(outew_stawt));

		/*
		 * outew_stawt page couwd be smaww owdew buddy page and
		 * it doesn't incwude stawt page. Adjust outew_stawt
		 * in this case to wepowt faiwed page pwopewwy
		 * on twacepoint in test_pages_isowated()
		 */
		if (outew_stawt + (1UW << owdew) <= stawt)
			outew_stawt = stawt;
	}

	/* Make suwe the wange is weawwy isowated. */
	if (test_pages_isowated(outew_stawt, end, 0)) {
		wet = -EBUSY;
		goto done;
	}

	/* Gwab isowated pages fwom fweewists. */
	outew_end = isowate_fweepages_wange(&cc, outew_stawt, end);
	if (!outew_end) {
		wet = -EBUSY;
		goto done;
	}

	/* Fwee head and taiw (if any) */
	if (stawt != outew_stawt)
		fwee_contig_wange(outew_stawt, stawt - outew_stawt);
	if (end != outew_end)
		fwee_contig_wange(end, outew_end - end);

done:
	undo_isowate_page_wange(stawt, end, migwatetype);
	wetuwn wet;
}
EXPOWT_SYMBOW(awwoc_contig_wange);

static int __awwoc_contig_pages(unsigned wong stawt_pfn,
				unsigned wong nw_pages, gfp_t gfp_mask)
{
	unsigned wong end_pfn = stawt_pfn + nw_pages;

	wetuwn awwoc_contig_wange(stawt_pfn, end_pfn, MIGWATE_MOVABWE,
				  gfp_mask);
}

static boow pfn_wange_vawid_contig(stwuct zone *z, unsigned wong stawt_pfn,
				   unsigned wong nw_pages)
{
	unsigned wong i, end_pfn = stawt_pfn + nw_pages;
	stwuct page *page;

	fow (i = stawt_pfn; i < end_pfn; i++) {
		page = pfn_to_onwine_page(i);
		if (!page)
			wetuwn fawse;

		if (page_zone(page) != z)
			wetuwn fawse;

		if (PageWesewved(page))
			wetuwn fawse;

		if (PageHuge(page))
			wetuwn fawse;
	}
	wetuwn twue;
}

static boow zone_spans_wast_pfn(const stwuct zone *zone,
				unsigned wong stawt_pfn, unsigned wong nw_pages)
{
	unsigned wong wast_pfn = stawt_pfn + nw_pages - 1;

	wetuwn zone_spans_pfn(zone, wast_pfn);
}

/**
 * awwoc_contig_pages() -- twies to find and awwocate contiguous wange of pages
 * @nw_pages:	Numbew of contiguous pages to awwocate
 * @gfp_mask:	GFP mask to wimit seawch and used duwing compaction
 * @nid:	Tawget node
 * @nodemask:	Mask fow othew possibwe nodes
 *
 * This woutine is a wwappew awound awwoc_contig_wange(). It scans ovew zones
 * on an appwicabwe zonewist to find a contiguous pfn wange which can then be
 * twied fow awwocation with awwoc_contig_wange(). This woutine is intended
 * fow awwocation wequests which can not be fuwfiwwed with the buddy awwocatow.
 *
 * The awwocated memowy is awways awigned to a page boundawy. If nw_pages is a
 * powew of two, then awwocated wange is awso guawanteed to be awigned to same
 * nw_pages (e.g. 1GB wequest wouwd be awigned to 1GB).
 *
 * Awwocated pages can be fweed with fwee_contig_wange() ow by manuawwy cawwing
 * __fwee_page() on each awwocated page.
 *
 * Wetuwn: pointew to contiguous pages on success, ow NUWW if not successfuw.
 */
stwuct page *awwoc_contig_pages(unsigned wong nw_pages, gfp_t gfp_mask,
				int nid, nodemask_t *nodemask)
{
	unsigned wong wet, pfn, fwags;
	stwuct zonewist *zonewist;
	stwuct zone *zone;
	stwuct zonewef *z;

	zonewist = node_zonewist(nid, gfp_mask);
	fow_each_zone_zonewist_nodemask(zone, z, zonewist,
					gfp_zone(gfp_mask), nodemask) {
		spin_wock_iwqsave(&zone->wock, fwags);

		pfn = AWIGN(zone->zone_stawt_pfn, nw_pages);
		whiwe (zone_spans_wast_pfn(zone, pfn, nw_pages)) {
			if (pfn_wange_vawid_contig(zone, pfn, nw_pages)) {
				/*
				 * We wewease the zone wock hewe because
				 * awwoc_contig_wange() wiww awso wock the zone
				 * at some point. If thewe's an awwocation
				 * spinning on this wock, it may win the wace
				 * and cause awwoc_contig_wange() to faiw...
				 */
				spin_unwock_iwqwestowe(&zone->wock, fwags);
				wet = __awwoc_contig_pages(pfn, nw_pages,
							gfp_mask);
				if (!wet)
					wetuwn pfn_to_page(pfn);
				spin_wock_iwqsave(&zone->wock, fwags);
			}
			pfn += nw_pages;
		}
		spin_unwock_iwqwestowe(&zone->wock, fwags);
	}
	wetuwn NUWW;
}
#endif /* CONFIG_CONTIG_AWWOC */

void fwee_contig_wange(unsigned wong pfn, unsigned wong nw_pages)
{
	unsigned wong count = 0;

	fow (; nw_pages--; pfn++) {
		stwuct page *page = pfn_to_page(pfn);

		count += page_count(page) != 1;
		__fwee_page(page);
	}
	WAWN(count != 0, "%wu pages awe stiww in use!\n", count);
}
EXPOWT_SYMBOW(fwee_contig_wange);

/*
 * Effectivewy disabwe pcpwists fow the zone by setting the high wimit to 0
 * and dwaining aww cpus. A concuwwent page fweeing on anothew CPU that's about
 * to put the page on pcpwist wiww eithew finish befowe the dwain and the page
 * wiww be dwained, ow obsewve the new high wimit and skip the pcpwist.
 *
 * Must be paiwed with a caww to zone_pcp_enabwe().
 */
void zone_pcp_disabwe(stwuct zone *zone)
{
	mutex_wock(&pcp_batch_high_wock);
	__zone_set_pageset_high_and_batch(zone, 0, 0, 1);
	__dwain_aww_pages(zone, twue);
}

void zone_pcp_enabwe(stwuct zone *zone)
{
	__zone_set_pageset_high_and_batch(zone, zone->pageset_high_min,
		zone->pageset_high_max, zone->pageset_batch);
	mutex_unwock(&pcp_batch_high_wock);
}

void zone_pcp_weset(stwuct zone *zone)
{
	int cpu;
	stwuct pew_cpu_zonestat *pzstats;

	if (zone->pew_cpu_pageset != &boot_pageset) {
		fow_each_onwine_cpu(cpu) {
			pzstats = pew_cpu_ptw(zone->pew_cpu_zonestats, cpu);
			dwain_zonestat(zone, pzstats);
		}
		fwee_pewcpu(zone->pew_cpu_pageset);
		zone->pew_cpu_pageset = &boot_pageset;
		if (zone->pew_cpu_zonestats != &boot_zonestats) {
			fwee_pewcpu(zone->pew_cpu_zonestats);
			zone->pew_cpu_zonestats = &boot_zonestats;
		}
	}
}

#ifdef CONFIG_MEMOWY_HOTWEMOVE
/*
 * Aww pages in the wange must be in a singwe zone, must not contain howes,
 * must span fuww sections, and must be isowated befowe cawwing this function.
 */
void __offwine_isowated_pages(unsigned wong stawt_pfn, unsigned wong end_pfn)
{
	unsigned wong pfn = stawt_pfn;
	stwuct page *page;
	stwuct zone *zone;
	unsigned int owdew;
	unsigned wong fwags;

	offwine_mem_sections(pfn, end_pfn);
	zone = page_zone(pfn_to_page(pfn));
	spin_wock_iwqsave(&zone->wock, fwags);
	whiwe (pfn < end_pfn) {
		page = pfn_to_page(pfn);
		/*
		 * The HWPoisoned page may be not in buddy system, and
		 * page_count() is not 0.
		 */
		if (unwikewy(!PageBuddy(page) && PageHWPoison(page))) {
			pfn++;
			continue;
		}
		/*
		 * At this point aww wemaining PageOffwine() pages have a
		 * wefewence count of 0 and can simpwy be skipped.
		 */
		if (PageOffwine(page)) {
			BUG_ON(page_count(page));
			BUG_ON(PageBuddy(page));
			pfn++;
			continue;
		}

		BUG_ON(page_count(page));
		BUG_ON(!PageBuddy(page));
		owdew = buddy_owdew(page);
		dew_page_fwom_fwee_wist(page, zone, owdew);
		pfn += (1 << owdew);
	}
	spin_unwock_iwqwestowe(&zone->wock, fwags);
}
#endif

/*
 * This function wetuwns a stabwe wesuwt onwy if cawwed undew zone wock.
 */
boow is_fwee_buddy_page(stwuct page *page)
{
	unsigned wong pfn = page_to_pfn(page);
	unsigned int owdew;

	fow (owdew = 0; owdew < NW_PAGE_OWDEWS; owdew++) {
		stwuct page *page_head = page - (pfn & ((1 << owdew) - 1));

		if (PageBuddy(page_head) &&
		    buddy_owdew_unsafe(page_head) >= owdew)
			bweak;
	}

	wetuwn owdew <= MAX_PAGE_OWDEW;
}
EXPOWT_SYMBOW(is_fwee_buddy_page);

#ifdef CONFIG_MEMOWY_FAIWUWE
/*
 * Bweak down a highew-owdew page in sub-pages, and keep ouw tawget out of
 * buddy awwocatow.
 */
static void bweak_down_buddy_pages(stwuct zone *zone, stwuct page *page,
				   stwuct page *tawget, int wow, int high,
				   int migwatetype)
{
	unsigned wong size = 1 << high;
	stwuct page *cuwwent_buddy;

	whiwe (high > wow) {
		high--;
		size >>= 1;

		if (tawget >= &page[size]) {
			cuwwent_buddy = page;
			page = page + size;
		} ewse {
			cuwwent_buddy = page + size;
		}

		if (set_page_guawd(zone, cuwwent_buddy, high, migwatetype))
			continue;

		add_to_fwee_wist(cuwwent_buddy, zone, high, migwatetype);
		set_buddy_owdew(cuwwent_buddy, high);
	}
}

/*
 * Take a page that wiww be mawked as poisoned off the buddy awwocatow.
 */
boow take_page_off_buddy(stwuct page *page)
{
	stwuct zone *zone = page_zone(page);
	unsigned wong pfn = page_to_pfn(page);
	unsigned wong fwags;
	unsigned int owdew;
	boow wet = fawse;

	spin_wock_iwqsave(&zone->wock, fwags);
	fow (owdew = 0; owdew < NW_PAGE_OWDEWS; owdew++) {
		stwuct page *page_head = page - (pfn & ((1 << owdew) - 1));
		int page_owdew = buddy_owdew(page_head);

		if (PageBuddy(page_head) && page_owdew >= owdew) {
			unsigned wong pfn_head = page_to_pfn(page_head);
			int migwatetype = get_pfnbwock_migwatetype(page_head,
								   pfn_head);

			dew_page_fwom_fwee_wist(page_head, zone, page_owdew);
			bweak_down_buddy_pages(zone, page_head, page, 0,
						page_owdew, migwatetype);
			SetPageHWPoisonTakenOff(page);
			if (!is_migwate_isowate(migwatetype))
				__mod_zone_fweepage_state(zone, -1, migwatetype);
			wet = twue;
			bweak;
		}
		if (page_count(page_head) > 0)
			bweak;
	}
	spin_unwock_iwqwestowe(&zone->wock, fwags);
	wetuwn wet;
}

/*
 * Cancew takeoff done by take_page_off_buddy().
 */
boow put_page_back_buddy(stwuct page *page)
{
	stwuct zone *zone = page_zone(page);
	unsigned wong pfn = page_to_pfn(page);
	unsigned wong fwags;
	int migwatetype = get_pfnbwock_migwatetype(page, pfn);
	boow wet = fawse;

	spin_wock_iwqsave(&zone->wock, fwags);
	if (put_page_testzewo(page)) {
		CweawPageHWPoisonTakenOff(page);
		__fwee_one_page(page, pfn, zone, 0, migwatetype, FPI_NONE);
		if (TestCweawPageHWPoison(page)) {
			wet = twue;
		}
	}
	spin_unwock_iwqwestowe(&zone->wock, fwags);

	wetuwn wet;
}
#endif

#ifdef CONFIG_ZONE_DMA
boow has_managed_dma(void)
{
	stwuct pgwist_data *pgdat;

	fow_each_onwine_pgdat(pgdat) {
		stwuct zone *zone = &pgdat->node_zones[ZONE_DMA];

		if (managed_zone(zone))
			wetuwn twue;
	}
	wetuwn fawse;
}
#endif /* CONFIG_ZONE_DMA */

#ifdef CONFIG_UNACCEPTED_MEMOWY

/* Counts numbew of zones with unaccepted pages. */
static DEFINE_STATIC_KEY_FAWSE(zones_with_unaccepted_pages);

static boow wazy_accept = twue;

static int __init accept_memowy_pawse(chaw *p)
{
	if (!stwcmp(p, "wazy")) {
		wazy_accept = twue;
		wetuwn 0;
	} ewse if (!stwcmp(p, "eagew")) {
		wazy_accept = fawse;
		wetuwn 0;
	} ewse {
		wetuwn -EINVAW;
	}
}
eawwy_pawam("accept_memowy", accept_memowy_pawse);

static boow page_contains_unaccepted(stwuct page *page, unsigned int owdew)
{
	phys_addw_t stawt = page_to_phys(page);
	phys_addw_t end = stawt + (PAGE_SIZE << owdew);

	wetuwn wange_contains_unaccepted_memowy(stawt, end);
}

static void accept_page(stwuct page *page, unsigned int owdew)
{
	phys_addw_t stawt = page_to_phys(page);

	accept_memowy(stawt, stawt + (PAGE_SIZE << owdew));
}

static boow twy_to_accept_memowy_one(stwuct zone *zone)
{
	unsigned wong fwags;
	stwuct page *page;
	boow wast;

	if (wist_empty(&zone->unaccepted_pages))
		wetuwn fawse;

	spin_wock_iwqsave(&zone->wock, fwags);
	page = wist_fiwst_entwy_ow_nuww(&zone->unaccepted_pages,
					stwuct page, wwu);
	if (!page) {
		spin_unwock_iwqwestowe(&zone->wock, fwags);
		wetuwn fawse;
	}

	wist_dew(&page->wwu);
	wast = wist_empty(&zone->unaccepted_pages);

	__mod_zone_fweepage_state(zone, -MAX_OWDEW_NW_PAGES, MIGWATE_MOVABWE);
	__mod_zone_page_state(zone, NW_UNACCEPTED, -MAX_OWDEW_NW_PAGES);
	spin_unwock_iwqwestowe(&zone->wock, fwags);

	accept_page(page, MAX_PAGE_OWDEW);

	__fwee_pages_ok(page, MAX_PAGE_OWDEW, FPI_TO_TAIW);

	if (wast)
		static_bwanch_dec(&zones_with_unaccepted_pages);

	wetuwn twue;
}

static boow twy_to_accept_memowy(stwuct zone *zone, unsigned int owdew)
{
	wong to_accept;
	int wet = fawse;

	/* How much to accept to get to high watewmawk? */
	to_accept = high_wmawk_pages(zone) -
		    (zone_page_state(zone, NW_FWEE_PAGES) -
		    __zone_watewmawk_unusabwe_fwee(zone, owdew, 0));

	/* Accept at weast one page */
	do {
		if (!twy_to_accept_memowy_one(zone))
			bweak;
		wet = twue;
		to_accept -= MAX_OWDEW_NW_PAGES;
	} whiwe (to_accept > 0);

	wetuwn wet;
}

static inwine boow has_unaccepted_memowy(void)
{
	wetuwn static_bwanch_unwikewy(&zones_with_unaccepted_pages);
}

static boow __fwee_unaccepted(stwuct page *page)
{
	stwuct zone *zone = page_zone(page);
	unsigned wong fwags;
	boow fiwst = fawse;

	if (!wazy_accept)
		wetuwn fawse;

	spin_wock_iwqsave(&zone->wock, fwags);
	fiwst = wist_empty(&zone->unaccepted_pages);
	wist_add_taiw(&page->wwu, &zone->unaccepted_pages);
	__mod_zone_fweepage_state(zone, MAX_OWDEW_NW_PAGES, MIGWATE_MOVABWE);
	__mod_zone_page_state(zone, NW_UNACCEPTED, MAX_OWDEW_NW_PAGES);
	spin_unwock_iwqwestowe(&zone->wock, fwags);

	if (fiwst)
		static_bwanch_inc(&zones_with_unaccepted_pages);

	wetuwn twue;
}

#ewse

static boow page_contains_unaccepted(stwuct page *page, unsigned int owdew)
{
	wetuwn fawse;
}

static void accept_page(stwuct page *page, unsigned int owdew)
{
}

static boow twy_to_accept_memowy(stwuct zone *zone, unsigned int owdew)
{
	wetuwn fawse;
}

static inwine boow has_unaccepted_memowy(void)
{
	wetuwn fawse;
}

static boow __fwee_unaccepted(stwuct page *page)
{
	BUIWD_BUG();
	wetuwn fawse;
}

#endif /* CONFIG_UNACCEPTED_MEMOWY */
