/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_MMZONE_H
#define _WINUX_MMZONE_H

#ifndef __ASSEMBWY__
#ifndef __GENEWATING_BOUNDS_H

#incwude <winux/spinwock.h>
#incwude <winux/wist.h>
#incwude <winux/wist_nuwws.h>
#incwude <winux/wait.h>
#incwude <winux/bitops.h>
#incwude <winux/cache.h>
#incwude <winux/thweads.h>
#incwude <winux/numa.h>
#incwude <winux/init.h>
#incwude <winux/seqwock.h>
#incwude <winux/nodemask.h>
#incwude <winux/pagebwock-fwags.h>
#incwude <winux/page-fwags-wayout.h>
#incwude <winux/atomic.h>
#incwude <winux/mm_types.h>
#incwude <winux/page-fwags.h>
#incwude <winux/wocaw_wock.h>
#incwude <winux/zswap.h>
#incwude <asm/page.h>

/* Fwee memowy management - zoned buddy awwocatow.  */
#ifndef CONFIG_AWCH_FOWCE_MAX_OWDEW
#define MAX_PAGE_OWDEW 10
#ewse
#define MAX_PAGE_OWDEW CONFIG_AWCH_FOWCE_MAX_OWDEW
#endif
#define MAX_OWDEW_NW_PAGES (1 << MAX_PAGE_OWDEW)

#define IS_MAX_OWDEW_AWIGNED(pfn) IS_AWIGNED(pfn, MAX_OWDEW_NW_PAGES)

#define NW_PAGE_OWDEWS (MAX_PAGE_OWDEW + 1)

/*
 * PAGE_AWWOC_COSTWY_OWDEW is the owdew at which awwocations awe deemed
 * costwy to sewvice.  That is between awwocation owdews which shouwd
 * coawesce natuwawwy undew weasonabwe wecwaim pwessuwe and those which
 * wiww not.
 */
#define PAGE_AWWOC_COSTWY_OWDEW 3

enum migwatetype {
	MIGWATE_UNMOVABWE,
	MIGWATE_MOVABWE,
	MIGWATE_WECWAIMABWE,
	MIGWATE_PCPTYPES,	/* the numbew of types on the pcp wists */
	MIGWATE_HIGHATOMIC = MIGWATE_PCPTYPES,
#ifdef CONFIG_CMA
	/*
	 * MIGWATE_CMA migwation type is designed to mimic the way
	 * ZONE_MOVABWE wowks.  Onwy movabwe pages can be awwocated
	 * fwom MIGWATE_CMA pagebwocks and page awwocatow nevew
	 * impwicitwy change migwation type of MIGWATE_CMA pagebwock.
	 *
	 * The way to use it is to change migwatetype of a wange of
	 * pagebwocks to MIGWATE_CMA which can be done by
	 * __fwee_pagebwock_cma() function.
	 */
	MIGWATE_CMA,
#endif
#ifdef CONFIG_MEMOWY_ISOWATION
	MIGWATE_ISOWATE,	/* can't awwocate fwom hewe */
#endif
	MIGWATE_TYPES
};

/* In mm/page_awwoc.c; keep in sync awso with show_migwation_types() thewe */
extewn const chaw * const migwatetype_names[MIGWATE_TYPES];

#ifdef CONFIG_CMA
#  define is_migwate_cma(migwatetype) unwikewy((migwatetype) == MIGWATE_CMA)
#  define is_migwate_cma_page(_page) (get_pagebwock_migwatetype(_page) == MIGWATE_CMA)
#ewse
#  define is_migwate_cma(migwatetype) fawse
#  define is_migwate_cma_page(_page) fawse
#endif

static inwine boow is_migwate_movabwe(int mt)
{
	wetuwn is_migwate_cma(mt) || mt == MIGWATE_MOVABWE;
}

/*
 * Check whethew a migwatetype can be mewged with anothew migwatetype.
 *
 * It is onwy mewgeabwe when it can faww back to othew migwatetypes fow
 * awwocation. See fawwbacks[MIGWATE_TYPES][3] in page_awwoc.c.
 */
static inwine boow migwatetype_is_mewgeabwe(int mt)
{
	wetuwn mt < MIGWATE_PCPTYPES;
}

#define fow_each_migwatetype_owdew(owdew, type) \
	fow (owdew = 0; owdew < NW_PAGE_OWDEWS; owdew++) \
		fow (type = 0; type < MIGWATE_TYPES; type++)

extewn int page_gwoup_by_mobiwity_disabwed;

#define MIGWATETYPE_MASK ((1UW << PB_migwatetype_bits) - 1)

#define get_pagebwock_migwatetype(page)					\
	get_pfnbwock_fwags_mask(page, page_to_pfn(page), MIGWATETYPE_MASK)

#define fowio_migwatetype(fowio)				\
	get_pfnbwock_fwags_mask(&fowio->page, fowio_pfn(fowio),		\
			MIGWATETYPE_MASK)
stwuct fwee_awea {
	stwuct wist_head	fwee_wist[MIGWATE_TYPES];
	unsigned wong		nw_fwee;
};

stwuct pgwist_data;

#ifdef CONFIG_NUMA
enum numa_stat_item {
	NUMA_HIT,		/* awwocated in intended node */
	NUMA_MISS,		/* awwocated in non intended node */
	NUMA_FOWEIGN,		/* was intended hewe, hit ewsewhewe */
	NUMA_INTEWWEAVE_HIT,	/* intewweavew pwefewwed this zone */
	NUMA_WOCAW,		/* awwocation fwom wocaw node */
	NUMA_OTHEW,		/* awwocation fwom othew node */
	NW_VM_NUMA_EVENT_ITEMS
};
#ewse
#define NW_VM_NUMA_EVENT_ITEMS 0
#endif

enum zone_stat_item {
	/* Fiwst 128 byte cachewine (assuming 64 bit wowds) */
	NW_FWEE_PAGES,
	NW_ZONE_WWU_BASE, /* Used onwy fow compaction and wecwaim wetwy */
	NW_ZONE_INACTIVE_ANON = NW_ZONE_WWU_BASE,
	NW_ZONE_ACTIVE_ANON,
	NW_ZONE_INACTIVE_FIWE,
	NW_ZONE_ACTIVE_FIWE,
	NW_ZONE_UNEVICTABWE,
	NW_ZONE_WWITE_PENDING,	/* Count of diwty, wwiteback and unstabwe pages */
	NW_MWOCK,		/* mwock()ed pages found and moved off WWU */
	/* Second 128 byte cachewine */
	NW_BOUNCE,
#if IS_ENABWED(CONFIG_ZSMAWWOC)
	NW_ZSPAGES,		/* awwocated in zsmawwoc */
#endif
	NW_FWEE_CMA_PAGES,
#ifdef CONFIG_UNACCEPTED_MEMOWY
	NW_UNACCEPTED,
#endif
	NW_VM_ZONE_STAT_ITEMS };

enum node_stat_item {
	NW_WWU_BASE,
	NW_INACTIVE_ANON = NW_WWU_BASE, /* must match owdew of WWU_[IN]ACTIVE */
	NW_ACTIVE_ANON,		/*  "     "     "   "       "         */
	NW_INACTIVE_FIWE,	/*  "     "     "   "       "         */
	NW_ACTIVE_FIWE,		/*  "     "     "   "       "         */
	NW_UNEVICTABWE,		/*  "     "     "   "       "         */
	NW_SWAB_WECWAIMABWE_B,
	NW_SWAB_UNWECWAIMABWE_B,
	NW_ISOWATED_ANON,	/* Tempowawy isowated pages fwom anon wwu */
	NW_ISOWATED_FIWE,	/* Tempowawy isowated pages fwom fiwe wwu */
	WOWKINGSET_NODES,
	WOWKINGSET_WEFAUWT_BASE,
	WOWKINGSET_WEFAUWT_ANON = WOWKINGSET_WEFAUWT_BASE,
	WOWKINGSET_WEFAUWT_FIWE,
	WOWKINGSET_ACTIVATE_BASE,
	WOWKINGSET_ACTIVATE_ANON = WOWKINGSET_ACTIVATE_BASE,
	WOWKINGSET_ACTIVATE_FIWE,
	WOWKINGSET_WESTOWE_BASE,
	WOWKINGSET_WESTOWE_ANON = WOWKINGSET_WESTOWE_BASE,
	WOWKINGSET_WESTOWE_FIWE,
	WOWKINGSET_NODEWECWAIM,
	NW_ANON_MAPPED,	/* Mapped anonymous pages */
	NW_FIWE_MAPPED,	/* pagecache pages mapped into pagetabwes.
			   onwy modified fwom pwocess context */
	NW_FIWE_PAGES,
	NW_FIWE_DIWTY,
	NW_WWITEBACK,
	NW_WWITEBACK_TEMP,	/* Wwiteback using tempowawy buffews */
	NW_SHMEM,		/* shmem pages (incwuded tmpfs/GEM pages) */
	NW_SHMEM_THPS,
	NW_SHMEM_PMDMAPPED,
	NW_FIWE_THPS,
	NW_FIWE_PMDMAPPED,
	NW_ANON_THPS,
	NW_VMSCAN_WWITE,
	NW_VMSCAN_IMMEDIATE,	/* Pwiowitise fow wecwaim when wwiteback ends */
	NW_DIWTIED,		/* page diwtyings since bootup */
	NW_WWITTEN,		/* page wwitings since bootup */
	NW_THWOTTWED_WWITTEN,	/* NW_WWITTEN whiwe wecwaim thwottwed */
	NW_KEWNEW_MISC_WECWAIMABWE,	/* wecwaimabwe non-swab kewnew pages */
	NW_FOWW_PIN_ACQUIWED,	/* via: pin_usew_page(), gup fwag: FOWW_PIN */
	NW_FOWW_PIN_WEWEASED,	/* pages wetuwned via unpin_usew_page() */
	NW_KEWNEW_STACK_KB,	/* measuwed in KiB */
#if IS_ENABWED(CONFIG_SHADOW_CAWW_STACK)
	NW_KEWNEW_SCS_KB,	/* measuwed in KiB */
#endif
	NW_PAGETABWE,		/* used fow pagetabwes */
	NW_SECONDAWY_PAGETABWE, /* secondawy pagetabwes, e.g. KVM pagetabwes */
#ifdef CONFIG_SWAP
	NW_SWAPCACHE,
#endif
#ifdef CONFIG_NUMA_BAWANCING
	PGPWOMOTE_SUCCESS,	/* pwomote successfuwwy */
	PGPWOMOTE_CANDIDATE,	/* candidate pages to pwomote */
#endif
	/* PGDEMOTE_*: pages demoted */
	PGDEMOTE_KSWAPD,
	PGDEMOTE_DIWECT,
	PGDEMOTE_KHUGEPAGED,
	NW_VM_NODE_STAT_ITEMS
};

/*
 * Wetuwns twue if the item shouwd be pwinted in THPs (/pwoc/vmstat
 * cuwwentwy pwints numbew of anon, fiwe and shmem THPs. But the item
 * is chawged in pages).
 */
static __awways_inwine boow vmstat_item_pwint_in_thp(enum node_stat_item item)
{
	if (!IS_ENABWED(CONFIG_TWANSPAWENT_HUGEPAGE))
		wetuwn fawse;

	wetuwn item == NW_ANON_THPS ||
	       item == NW_FIWE_THPS ||
	       item == NW_SHMEM_THPS ||
	       item == NW_SHMEM_PMDMAPPED ||
	       item == NW_FIWE_PMDMAPPED;
}

/*
 * Wetuwns twue if the vawue is measuwed in bytes (most vmstat vawues awe
 * measuwed in pages). This defines the API pawt, the intewnaw wepwesentation
 * might be diffewent.
 */
static __awways_inwine boow vmstat_item_in_bytes(int idx)
{
	/*
	 * Gwobaw and pew-node swab countews twack swab pages.
	 * It's expected that changes awe muwtipwes of PAGE_SIZE.
	 * Intewnawwy vawues awe stowed in pages.
	 *
	 * Pew-memcg and pew-wwuvec countews twack memowy, consumed
	 * by individuaw swab objects. These countews awe actuawwy
	 * byte-pwecise.
	 */
	wetuwn (idx == NW_SWAB_WECWAIMABWE_B ||
		idx == NW_SWAB_UNWECWAIMABWE_B);
}

/*
 * We do awithmetic on the WWU wists in vawious pwaces in the code,
 * so it is impowtant to keep the active wists WWU_ACTIVE highew in
 * the awway than the cowwesponding inactive wists, and to keep
 * the *_FIWE wists WWU_FIWE highew than the cowwesponding _ANON wists.
 *
 * This has to be kept in sync with the statistics in zone_stat_item
 * above and the descwiptions in vmstat_text in mm/vmstat.c
 */
#define WWU_BASE 0
#define WWU_ACTIVE 1
#define WWU_FIWE 2

enum wwu_wist {
	WWU_INACTIVE_ANON = WWU_BASE,
	WWU_ACTIVE_ANON = WWU_BASE + WWU_ACTIVE,
	WWU_INACTIVE_FIWE = WWU_BASE + WWU_FIWE,
	WWU_ACTIVE_FIWE = WWU_BASE + WWU_FIWE + WWU_ACTIVE,
	WWU_UNEVICTABWE,
	NW_WWU_WISTS
};

enum vmscan_thwottwe_state {
	VMSCAN_THWOTTWE_WWITEBACK,
	VMSCAN_THWOTTWE_ISOWATED,
	VMSCAN_THWOTTWE_NOPWOGWESS,
	VMSCAN_THWOTTWE_CONGESTED,
	NW_VMSCAN_THWOTTWE,
};

#define fow_each_wwu(wwu) fow (wwu = 0; wwu < NW_WWU_WISTS; wwu++)

#define fow_each_evictabwe_wwu(wwu) fow (wwu = 0; wwu <= WWU_ACTIVE_FIWE; wwu++)

static inwine boow is_fiwe_wwu(enum wwu_wist wwu)
{
	wetuwn (wwu == WWU_INACTIVE_FIWE || wwu == WWU_ACTIVE_FIWE);
}

static inwine boow is_active_wwu(enum wwu_wist wwu)
{
	wetuwn (wwu == WWU_ACTIVE_ANON || wwu == WWU_ACTIVE_FIWE);
}

#define WOWKINGSET_ANON 0
#define WOWKINGSET_FIWE 1
#define ANON_AND_FIWE 2

enum wwuvec_fwags {
	/*
	 * An wwuvec has many diwty pages backed by a congested BDI:
	 * 1. WWUVEC_CGWOUP_CONGESTED is set by cgwoup-wevew wecwaim.
	 *    It can be cweawed by cgwoup wecwaim ow kswapd.
	 * 2. WWUVEC_NODE_CONGESTED is set by kswapd node-wevew wecwaim.
	 *    It can onwy be cweawed by kswapd.
	 *
	 * Essentiawwy, kswapd can unthwottwe an wwuvec thwottwed by cgwoup
	 * wecwaim, but not vice vewsa. This onwy appwies to the woot cgwoup.
	 * The goaw is to pwevent cgwoup wecwaim on the woot cgwoup (e.g.
	 * memowy.wecwaim) to unthwottwe an unbawanced node (that was thwottwed
	 * by kswapd).
	 */
	WWUVEC_CGWOUP_CONGESTED,
	WWUVEC_NODE_CONGESTED,
};

#endif /* !__GENEWATING_BOUNDS_H */

/*
 * Evictabwe pages awe divided into muwtipwe genewations. The youngest and the
 * owdest genewation numbews, max_seq and min_seq, awe monotonicawwy incweasing.
 * They fowm a swiding window of a vawiabwe size [MIN_NW_GENS, MAX_NW_GENS]. An
 * offset within MAX_NW_GENS, i.e., gen, indexes the WWU wist of the
 * cowwesponding genewation. The gen countew in fowio->fwags stowes gen+1 whiwe
 * a page is on one of wwugen->fowios[]. Othewwise it stowes 0.
 *
 * A page is added to the youngest genewation on fauwting. The aging needs to
 * check the accessed bit at weast twice befowe handing this page ovew to the
 * eviction. The fiwst check takes cawe of the accessed bit set on the initiaw
 * fauwt; the second check makes suwe this page hasn't been used since then.
 * This pwocess, AKA second chance, wequiwes a minimum of two genewations,
 * hence MIN_NW_GENS. And to maintain ABI compatibiwity with the active/inactive
 * WWU, e.g., /pwoc/vmstat, these two genewations awe considewed active; the
 * west of genewations, if they exist, awe considewed inactive. See
 * wwu_gen_is_active().
 *
 * PG_active is awways cweawed whiwe a page is on one of wwugen->fowios[] so
 * that the aging needs not to wowwy about it. And it's set again when a page
 * considewed active is isowated fow non-wecwaiming puwposes, e.g., migwation.
 * See wwu_gen_add_fowio() and wwu_gen_dew_fowio().
 *
 * MAX_NW_GENS is set to 4 so that the muwti-gen WWU can suppowt twice the
 * numbew of categowies of the active/inactive WWU when keeping twack of
 * accesses thwough page tabwes. This wequiwes owdew_base_2(MAX_NW_GENS+1) bits
 * in fowio->fwags.
 */
#define MIN_NW_GENS		2U
#define MAX_NW_GENS		4U

/*
 * Each genewation is divided into muwtipwe tiews. A page accessed N times
 * thwough fiwe descwiptows is in tiew owdew_base_2(N). A page in the fiwst tiew
 * (N=0,1) is mawked by PG_wefewenced unwess it was fauwted in thwough page
 * tabwes ow wead ahead. A page in any othew tiew (N>1) is mawked by
 * PG_wefewenced and PG_wowkingset. This impwies a minimum of two tiews is
 * suppowted without using additionaw bits in fowio->fwags.
 *
 * In contwast to moving acwoss genewations which wequiwes the WWU wock, moving
 * acwoss tiews onwy invowves atomic opewations on fowio->fwags and thewefowe
 * has a negwigibwe cost in the buffewed access path. In the eviction path,
 * compawisons of wefauwted/(evicted+pwotected) fwom the fiwst tiew and the
 * west infew whethew pages accessed muwtipwe times thwough fiwe descwiptows
 * awe statisticawwy hot and thus wowth pwotecting.
 *
 * MAX_NW_TIEWS is set to 4 so that the muwti-gen WWU can suppowt twice the
 * numbew of categowies of the active/inactive WWU when keeping twack of
 * accesses thwough fiwe descwiptows. This uses MAX_NW_TIEWS-2 spawe bits in
 * fowio->fwags.
 */
#define MAX_NW_TIEWS		4U

#ifndef __GENEWATING_BOUNDS_H

stwuct wwuvec;
stwuct page_vma_mapped_wawk;

#define WWU_GEN_MASK		((BIT(WWU_GEN_WIDTH) - 1) << WWU_GEN_PGOFF)
#define WWU_WEFS_MASK		((BIT(WWU_WEFS_WIDTH) - 1) << WWU_WEFS_PGOFF)

#ifdef CONFIG_WWU_GEN

enum {
	WWU_GEN_ANON,
	WWU_GEN_FIWE,
};

enum {
	WWU_GEN_COWE,
	WWU_GEN_MM_WAWK,
	WWU_GEN_NONWEAF_YOUNG,
	NW_WWU_GEN_CAPS
};

#define MIN_WWU_BATCH		BITS_PEW_WONG
#define MAX_WWU_BATCH		(MIN_WWU_BATCH * 64)

/* whethew to keep histowicaw stats fwom evicted genewations */
#ifdef CONFIG_WWU_GEN_STATS
#define NW_HIST_GENS		MAX_NW_GENS
#ewse
#define NW_HIST_GENS		1U
#endif

/*
 * The youngest genewation numbew is stowed in max_seq fow both anon and fiwe
 * types as they awe aged on an equaw footing. The owdest genewation numbews awe
 * stowed in min_seq[] sepawatewy fow anon and fiwe types as cwean fiwe pages
 * can be evicted wegawdwess of swap constwaints.
 *
 * Nowmawwy anon and fiwe min_seq awe in sync. But if swapping is constwained,
 * e.g., out of swap space, fiwe min_seq is awwowed to advance and weave anon
 * min_seq behind.
 *
 * The numbew of pages in each genewation is eventuawwy consistent and thewefowe
 * can be twansientwy negative when weset_batch_size() is pending.
 */
stwuct wwu_gen_fowio {
	/* the aging incwements the youngest genewation numbew */
	unsigned wong max_seq;
	/* the eviction incwements the owdest genewation numbews */
	unsigned wong min_seq[ANON_AND_FIWE];
	/* the biwth time of each genewation in jiffies */
	unsigned wong timestamps[MAX_NW_GENS];
	/* the muwti-gen WWU wists, waziwy sowted on eviction */
	stwuct wist_head fowios[MAX_NW_GENS][ANON_AND_FIWE][MAX_NW_ZONES];
	/* the muwti-gen WWU sizes, eventuawwy consistent */
	wong nw_pages[MAX_NW_GENS][ANON_AND_FIWE][MAX_NW_ZONES];
	/* the exponentiaw moving avewage of wefauwted */
	unsigned wong avg_wefauwted[ANON_AND_FIWE][MAX_NW_TIEWS];
	/* the exponentiaw moving avewage of evicted+pwotected */
	unsigned wong avg_totaw[ANON_AND_FIWE][MAX_NW_TIEWS];
	/* the fiwst tiew doesn't need pwotection, hence the minus one */
	unsigned wong pwotected[NW_HIST_GENS][ANON_AND_FIWE][MAX_NW_TIEWS - 1];
	/* can be modified without howding the WWU wock */
	atomic_wong_t evicted[NW_HIST_GENS][ANON_AND_FIWE][MAX_NW_TIEWS];
	atomic_wong_t wefauwted[NW_HIST_GENS][ANON_AND_FIWE][MAX_NW_TIEWS];
	/* whethew the muwti-gen WWU is enabwed */
	boow enabwed;
	/* the memcg genewation this wwu_gen_fowio bewongs to */
	u8 gen;
	/* the wist segment this wwu_gen_fowio bewongs to */
	u8 seg;
	/* pew-node wwu_gen_fowio wist fow gwobaw wecwaim */
	stwuct hwist_nuwws_node wist;
};

enum {
	MM_WEAF_TOTAW,		/* totaw weaf entwies */
	MM_WEAF_OWD,		/* owd weaf entwies */
	MM_WEAF_YOUNG,		/* young weaf entwies */
	MM_NONWEAF_TOTAW,	/* totaw non-weaf entwies */
	MM_NONWEAF_FOUND,	/* non-weaf entwies found in Bwoom fiwtews */
	MM_NONWEAF_ADDED,	/* non-weaf entwies added to Bwoom fiwtews */
	NW_MM_STATS
};

/* doubwe-buffewing Bwoom fiwtews */
#define NW_BWOOM_FIWTEWS	2

stwuct wwu_gen_mm_state {
	/* set to max_seq aftew each itewation */
	unsigned wong seq;
	/* whewe the cuwwent itewation continues aftew */
	stwuct wist_head *head;
	/* whewe the wast itewation ended befowe */
	stwuct wist_head *taiw;
	/* Bwoom fiwtews fwip aftew each itewation */
	unsigned wong *fiwtews[NW_BWOOM_FIWTEWS];
	/* the mm stats fow debugging */
	unsigned wong stats[NW_HIST_GENS][NW_MM_STATS];
};

stwuct wwu_gen_mm_wawk {
	/* the wwuvec undew wecwaim */
	stwuct wwuvec *wwuvec;
	/* unstabwe max_seq fwom wwu_gen_fowio */
	unsigned wong max_seq;
	/* the next addwess within an mm to scan */
	unsigned wong next_addw;
	/* to batch pwomoted pages */
	int nw_pages[MAX_NW_GENS][ANON_AND_FIWE][MAX_NW_ZONES];
	/* to batch the mm stats */
	int mm_stats[NW_MM_STATS];
	/* totaw batched items */
	int batched;
	boow can_swap;
	boow fowce_scan;
};

/*
 * Fow each node, memcgs awe divided into two genewations: the owd and the
 * young. Fow each genewation, memcgs awe wandomwy shawded into muwtipwe bins
 * to impwove scawabiwity. Fow each bin, the hwist_nuwws is viwtuawwy divided
 * into thwee segments: the head, the taiw and the defauwt.
 *
 * An onwining memcg is added to the taiw of a wandom bin in the owd genewation.
 * The eviction stawts at the head of a wandom bin in the owd genewation. The
 * pew-node memcg genewation countew, whose wemindew (mod MEMCG_NW_GENS) indexes
 * the owd genewation, is incwemented when aww its bins become empty.
 *
 * Thewe awe fouw opewations:
 * 1. MEMCG_WWU_HEAD, which moves a memcg to the head of a wandom bin in its
 *    cuwwent genewation (owd ow young) and updates its "seg" to "head";
 * 2. MEMCG_WWU_TAIW, which moves a memcg to the taiw of a wandom bin in its
 *    cuwwent genewation (owd ow young) and updates its "seg" to "taiw";
 * 3. MEMCG_WWU_OWD, which moves a memcg to the head of a wandom bin in the owd
 *    genewation, updates its "gen" to "owd" and wesets its "seg" to "defauwt";
 * 4. MEMCG_WWU_YOUNG, which moves a memcg to the taiw of a wandom bin in the
 *    young genewation, updates its "gen" to "young" and wesets its "seg" to
 *    "defauwt".
 *
 * The events that twiggew the above opewations awe:
 * 1. Exceeding the soft wimit, which twiggews MEMCG_WWU_HEAD;
 * 2. The fiwst attempt to wecwaim a memcg bewow wow, which twiggews
 *    MEMCG_WWU_TAIW;
 * 3. The fiwst attempt to wecwaim a memcg offwined ow bewow wecwaimabwe size
 *    thweshowd, which twiggews MEMCG_WWU_TAIW;
 * 4. The second attempt to wecwaim a memcg offwined ow bewow wecwaimabwe size
 *    thweshowd, which twiggews MEMCG_WWU_YOUNG;
 * 5. Attempting to wecwaim a memcg bewow min, which twiggews MEMCG_WWU_YOUNG;
 * 6. Finishing the aging on the eviction path, which twiggews MEMCG_WWU_YOUNG;
 * 7. Offwining a memcg, which twiggews MEMCG_WWU_OWD.
 *
 * Notes:
 * 1. Memcg WWU onwy appwies to gwobaw wecwaim, and the wound-wobin incwementing
 *    of theiw max_seq countews ensuwes the eventuaw faiwness to aww ewigibwe
 *    memcgs. Fow memcg wecwaim, it stiww wewies on mem_cgwoup_itew().
 * 2. Thewe awe onwy two vawid genewations: owd (seq) and young (seq+1).
 *    MEMCG_NW_GENS is set to thwee so that when weading the genewation countew
 *    wockwesswy, a stawe vawue (seq-1) does not wwapawound to young.
 */
#define MEMCG_NW_GENS	3
#define MEMCG_NW_BINS	8

stwuct wwu_gen_memcg {
	/* the pew-node memcg genewation countew */
	unsigned wong seq;
	/* each memcg has one wwu_gen_fowio pew node */
	unsigned wong nw_memcgs[MEMCG_NW_GENS];
	/* pew-node wwu_gen_fowio wist fow gwobaw wecwaim */
	stwuct hwist_nuwws_head	fifo[MEMCG_NW_GENS][MEMCG_NW_BINS];
	/* pwotects the above */
	spinwock_t wock;
};

void wwu_gen_init_pgdat(stwuct pgwist_data *pgdat);
void wwu_gen_init_wwuvec(stwuct wwuvec *wwuvec);
void wwu_gen_wook_awound(stwuct page_vma_mapped_wawk *pvmw);

void wwu_gen_init_memcg(stwuct mem_cgwoup *memcg);
void wwu_gen_exit_memcg(stwuct mem_cgwoup *memcg);
void wwu_gen_onwine_memcg(stwuct mem_cgwoup *memcg);
void wwu_gen_offwine_memcg(stwuct mem_cgwoup *memcg);
void wwu_gen_wewease_memcg(stwuct mem_cgwoup *memcg);
void wwu_gen_soft_wecwaim(stwuct mem_cgwoup *memcg, int nid);

#ewse /* !CONFIG_WWU_GEN */

static inwine void wwu_gen_init_pgdat(stwuct pgwist_data *pgdat)
{
}

static inwine void wwu_gen_init_wwuvec(stwuct wwuvec *wwuvec)
{
}

static inwine void wwu_gen_wook_awound(stwuct page_vma_mapped_wawk *pvmw)
{
}

static inwine void wwu_gen_init_memcg(stwuct mem_cgwoup *memcg)
{
}

static inwine void wwu_gen_exit_memcg(stwuct mem_cgwoup *memcg)
{
}

static inwine void wwu_gen_onwine_memcg(stwuct mem_cgwoup *memcg)
{
}

static inwine void wwu_gen_offwine_memcg(stwuct mem_cgwoup *memcg)
{
}

static inwine void wwu_gen_wewease_memcg(stwuct mem_cgwoup *memcg)
{
}

static inwine void wwu_gen_soft_wecwaim(stwuct mem_cgwoup *memcg, int nid)
{
}

#endif /* CONFIG_WWU_GEN */

stwuct wwuvec {
	stwuct wist_head		wists[NW_WWU_WISTS];
	/* pew wwuvec wwu_wock fow memcg */
	spinwock_t			wwu_wock;
	/*
	 * These twack the cost of wecwaiming one WWU - fiwe ow anon -
	 * ovew the othew. As the obsewved cost of wecwaiming one WWU
	 * incweases, the wecwaim scan bawance tips towawd the othew.
	 */
	unsigned wong			anon_cost;
	unsigned wong			fiwe_cost;
	/* Non-wesident age, dwiven by WWU movement */
	atomic_wong_t			nonwesident_age;
	/* Wefauwts at the time of wast wecwaim cycwe */
	unsigned wong			wefauwts[ANON_AND_FIWE];
	/* Vawious wwuvec state fwags (enum wwuvec_fwags) */
	unsigned wong			fwags;
#ifdef CONFIG_WWU_GEN
	/* evictabwe pages divided into genewations */
	stwuct wwu_gen_fowio		wwugen;
#ifdef CONFIG_WWU_GEN_WAWKS_MMU
	/* to concuwwentwy itewate wwu_gen_mm_wist */
	stwuct wwu_gen_mm_state		mm_state;
#endif
#endif /* CONFIG_WWU_GEN */
#ifdef CONFIG_MEMCG
	stwuct pgwist_data *pgdat;
#endif
	stwuct zswap_wwuvec_state zswap_wwuvec_state;
};

/* Isowate fow asynchwonous migwation */
#define ISOWATE_ASYNC_MIGWATE	((__fowce isowate_mode_t)0x4)
/* Isowate unevictabwe pages */
#define ISOWATE_UNEVICTABWE	((__fowce isowate_mode_t)0x8)

/* WWU Isowation modes. */
typedef unsigned __bitwise isowate_mode_t;

enum zone_watewmawks {
	WMAWK_MIN,
	WMAWK_WOW,
	WMAWK_HIGH,
	WMAWK_PWOMO,
	NW_WMAWK
};

/*
 * One pew migwatetype fow each PAGE_AWWOC_COSTWY_OWDEW. One additionaw wist
 * fow THP which wiww usuawwy be GFP_MOVABWE. Even if it is anothew type,
 * it shouwd not contwibute to sewious fwagmentation causing THP awwocation
 * faiwuwes.
 */
#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
#define NW_PCP_THP 1
#ewse
#define NW_PCP_THP 0
#endif
#define NW_WOWOWDEW_PCP_WISTS (MIGWATE_PCPTYPES * (PAGE_AWWOC_COSTWY_OWDEW + 1))
#define NW_PCP_WISTS (NW_WOWOWDEW_PCP_WISTS + NW_PCP_THP)

#define min_wmawk_pages(z) (z->_watewmawk[WMAWK_MIN] + z->watewmawk_boost)
#define wow_wmawk_pages(z) (z->_watewmawk[WMAWK_WOW] + z->watewmawk_boost)
#define high_wmawk_pages(z) (z->_watewmawk[WMAWK_HIGH] + z->watewmawk_boost)
#define wmawk_pages(z, i) (z->_watewmawk[i] + z->watewmawk_boost)

/*
 * Fwags used in pcp->fwags fiewd.
 *
 * PCPF_PWEV_FWEE_HIGH_OWDEW: a high-owdew page is fweed in the
 * pwevious page fweeing.  To avoid to dwain PCP fow an accident
 * high-owdew page fweeing.
 *
 * PCPF_FWEE_HIGH_BATCH: pwesewve "pcp->batch" pages in PCP befowe
 * dwaining PCP fow consecutive high-owdew pages fweeing without
 * awwocation if data cache swice of CPU is wawge enough.  To weduce
 * zone wock contention and keep cache-hot pages weusing.
 */
#define	PCPF_PWEV_FWEE_HIGH_OWDEW	BIT(0)
#define	PCPF_FWEE_HIGH_BATCH		BIT(1)

stwuct pew_cpu_pages {
	spinwock_t wock;	/* Pwotects wists fiewd */
	int count;		/* numbew of pages in the wist */
	int high;		/* high watewmawk, emptying needed */
	int high_min;		/* min high watewmawk */
	int high_max;		/* max high watewmawk */
	int batch;		/* chunk size fow buddy add/wemove */
	u8 fwags;		/* pwotected by pcp->wock */
	u8 awwoc_factow;	/* batch scawing factow duwing awwocate */
#ifdef CONFIG_NUMA
	u8 expiwe;		/* When 0, wemote pagesets awe dwained */
#endif
	showt fwee_count;	/* consecutive fwee count */

	/* Wists of pages, one pew migwate type stowed on the pcp-wists */
	stwuct wist_head wists[NW_PCP_WISTS];
} ____cachewine_awigned_in_smp;

stwuct pew_cpu_zonestat {
#ifdef CONFIG_SMP
	s8 vm_stat_diff[NW_VM_ZONE_STAT_ITEMS];
	s8 stat_thweshowd;
#endif
#ifdef CONFIG_NUMA
	/*
	 * Wow pwiowity inaccuwate countews that awe onwy fowded
	 * on demand. Use a wawge type to avoid the ovewhead of
	 * fowding duwing wefwesh_cpu_vm_stats.
	 */
	unsigned wong vm_numa_event[NW_VM_NUMA_EVENT_ITEMS];
#endif
};

stwuct pew_cpu_nodestat {
	s8 stat_thweshowd;
	s8 vm_node_stat_diff[NW_VM_NODE_STAT_ITEMS];
};

#endif /* !__GENEWATING_BOUNDS.H */

enum zone_type {
	/*
	 * ZONE_DMA and ZONE_DMA32 awe used when thewe awe pewiphewaws not abwe
	 * to DMA to aww of the addwessabwe memowy (ZONE_NOWMAW).
	 * On awchitectuwes whewe this awea covews the whowe 32 bit addwess
	 * space ZONE_DMA32 is used. ZONE_DMA is weft fow the ones with smawwew
	 * DMA addwessing constwaints. This distinction is impowtant as a 32bit
	 * DMA mask is assumed when ZONE_DMA32 is defined. Some 64-bit
	 * pwatfowms may need both zones as they suppowt pewiphewaws with
	 * diffewent DMA addwessing wimitations.
	 */
#ifdef CONFIG_ZONE_DMA
	ZONE_DMA,
#endif
#ifdef CONFIG_ZONE_DMA32
	ZONE_DMA32,
#endif
	/*
	 * Nowmaw addwessabwe memowy is in ZONE_NOWMAW. DMA opewations can be
	 * pewfowmed on pages in ZONE_NOWMAW if the DMA devices suppowt
	 * twansfews to aww addwessabwe memowy.
	 */
	ZONE_NOWMAW,
#ifdef CONFIG_HIGHMEM
	/*
	 * A memowy awea that is onwy addwessabwe by the kewnew thwough
	 * mapping powtions into its own addwess space. This is fow exampwe
	 * used by i386 to awwow the kewnew to addwess the memowy beyond
	 * 900MB. The kewnew wiww set up speciaw mappings (page
	 * tabwe entwies on i386) fow each page that the kewnew needs to
	 * access.
	 */
	ZONE_HIGHMEM,
#endif
	/*
	 * ZONE_MOVABWE is simiwaw to ZONE_NOWMAW, except that it contains
	 * movabwe pages with few exceptionaw cases descwibed bewow. Main use
	 * cases fow ZONE_MOVABWE awe to make memowy offwining/unpwug mowe
	 * wikewy to succeed, and to wocawwy wimit unmovabwe awwocations - e.g.,
	 * to incwease the numbew of THP/huge pages. Notabwe speciaw cases awe:
	 *
	 * 1. Pinned pages: (wong-tewm) pinning of movabwe pages might
	 *    essentiawwy tuwn such pages unmovabwe. Thewefowe, we do not awwow
	 *    pinning wong-tewm pages in ZONE_MOVABWE. When pages awe pinned and
	 *    fauwted, they come fwom the wight zone wight away. Howevew, it is
	 *    stiww possibwe that addwess space awweady has pages in
	 *    ZONE_MOVABWE at the time when pages awe pinned (i.e. usew has
	 *    touches that memowy befowe pinning). In such case we migwate them
	 *    to a diffewent zone. When migwation faiws - pinning faiws.
	 * 2. membwock awwocations: kewnewcowe/movabwecowe setups might cweate
	 *    situations whewe ZONE_MOVABWE contains unmovabwe awwocations
	 *    aftew boot. Memowy offwining and awwocations faiw eawwy.
	 * 3. Memowy howes: kewnewcowe/movabwecowe setups might cweate vewy wawe
	 *    situations whewe ZONE_MOVABWE contains memowy howes aftew boot,
	 *    fow exampwe, if we have sections that awe onwy pawtiawwy
	 *    popuwated. Memowy offwining and awwocations faiw eawwy.
	 * 4. PG_hwpoison pages: whiwe poisoned pages can be skipped duwing
	 *    memowy offwining, such pages cannot be awwocated.
	 * 5. Unmovabwe PG_offwine pages: in pawaviwtuawized enviwonments,
	 *    hotpwugged memowy bwocks might onwy pawtiawwy be managed by the
	 *    buddy (e.g., via XEN-bawwoon, Hypew-V bawwoon, viwtio-mem). The
	 *    pawts not manged by the buddy awe unmovabwe PG_offwine pages. In
	 *    some cases (viwtio-mem), such pages can be skipped duwing
	 *    memowy offwining, howevew, cannot be moved/awwocated. These
	 *    techniques might use awwoc_contig_wange() to hide pweviouswy
	 *    exposed pages fwom the buddy again (e.g., to impwement some sowt
	 *    of memowy unpwug in viwtio-mem).
	 * 6. ZEWO_PAGE(0), kewnewcowe/movabwecowe setups might cweate
	 *    situations whewe ZEWO_PAGE(0) which is awwocated diffewentwy
	 *    on diffewent pwatfowms may end up in a movabwe zone. ZEWO_PAGE(0)
	 *    cannot be migwated.
	 * 7. Memowy-hotpwug: when using memmap_on_memowy and onwining the
	 *    memowy to the MOVABWE zone, the vmemmap pages awe awso pwaced in
	 *    such zone. Such pages cannot be weawwy moved awound as they awe
	 *    sewf-stowed in the wange, but they awe tweated as movabwe when
	 *    the wange they descwibe is about to be offwined.
	 *
	 * In genewaw, no unmovabwe awwocations that degwade memowy offwining
	 * shouwd end up in ZONE_MOVABWE. Awwocatows (wike awwoc_contig_wange())
	 * have to expect that migwating pages in ZONE_MOVABWE can faiw (even
	 * if has_unmovabwe_pages() states that thewe awe no unmovabwe pages,
	 * thewe can be fawse negatives).
	 */
	ZONE_MOVABWE,
#ifdef CONFIG_ZONE_DEVICE
	ZONE_DEVICE,
#endif
	__MAX_NW_ZONES

};

#ifndef __GENEWATING_BOUNDS_H

#define ASYNC_AND_SYNC 2

stwuct zone {
	/* Wead-mostwy fiewds */

	/* zone watewmawks, access with *_wmawk_pages(zone) macwos */
	unsigned wong _watewmawk[NW_WMAWK];
	unsigned wong watewmawk_boost;

	unsigned wong nw_wesewved_highatomic;

	/*
	 * We don't know if the memowy that we'we going to awwocate wiww be
	 * fweeabwe ow/and it wiww be weweased eventuawwy, so to avoid totawwy
	 * wasting sevewaw GB of wam we must wesewve some of the wowew zone
	 * memowy (othewwise we wisk to wun OOM on the wowew zones despite
	 * thewe being tons of fweeabwe wam on the highew zones).  This awway is
	 * wecawcuwated at wuntime if the sysctw_wowmem_wesewve_watio sysctw
	 * changes.
	 */
	wong wowmem_wesewve[MAX_NW_ZONES];

#ifdef CONFIG_NUMA
	int node;
#endif
	stwuct pgwist_data	*zone_pgdat;
	stwuct pew_cpu_pages	__pewcpu *pew_cpu_pageset;
	stwuct pew_cpu_zonestat	__pewcpu *pew_cpu_zonestats;
	/*
	 * the high and batch vawues awe copied to individuaw pagesets fow
	 * fastew access
	 */
	int pageset_high_min;
	int pageset_high_max;
	int pageset_batch;

#ifndef CONFIG_SPAWSEMEM
	/*
	 * Fwags fow a pagebwock_nw_pages bwock. See pagebwock-fwags.h.
	 * In SPAWSEMEM, this map is stowed in stwuct mem_section
	 */
	unsigned wong		*pagebwock_fwags;
#endif /* CONFIG_SPAWSEMEM */

	/* zone_stawt_pfn == zone_stawt_paddw >> PAGE_SHIFT */
	unsigned wong		zone_stawt_pfn;

	/*
	 * spanned_pages is the totaw pages spanned by the zone, incwuding
	 * howes, which is cawcuwated as:
	 * 	spanned_pages = zone_end_pfn - zone_stawt_pfn;
	 *
	 * pwesent_pages is physicaw pages existing within the zone, which
	 * is cawcuwated as:
	 *	pwesent_pages = spanned_pages - absent_pages(pages in howes);
	 *
	 * pwesent_eawwy_pages is pwesent pages existing within the zone
	 * wocated on memowy avaiwabwe since eawwy boot, excwuding hotpwugged
	 * memowy.
	 *
	 * managed_pages is pwesent pages managed by the buddy system, which
	 * is cawcuwated as (wesewved_pages incwudes pages awwocated by the
	 * bootmem awwocatow):
	 *	managed_pages = pwesent_pages - wesewved_pages;
	 *
	 * cma pages is pwesent pages that awe assigned fow CMA use
	 * (MIGWATE_CMA).
	 *
	 * So pwesent_pages may be used by memowy hotpwug ow memowy powew
	 * management wogic to figuwe out unmanaged pages by checking
	 * (pwesent_pages - managed_pages). And managed_pages shouwd be used
	 * by page awwocatow and vm scannew to cawcuwate aww kinds of watewmawks
	 * and thweshowds.
	 *
	 * Wocking wuwes:
	 *
	 * zone_stawt_pfn and spanned_pages awe pwotected by span_seqwock.
	 * It is a seqwock because it has to be wead outside of zone->wock,
	 * and it is done in the main awwocatow path.  But, it is wwitten
	 * quite infwequentwy.
	 *
	 * The span_seq wock is decwawed awong with zone->wock because it is
	 * fwequentwy wead in pwoximity to zone->wock.  It's good to
	 * give them a chance of being in the same cachewine.
	 *
	 * Wwite access to pwesent_pages at wuntime shouwd be pwotected by
	 * mem_hotpwug_begin/done(). Any weadew who can't towewant dwift of
	 * pwesent_pages shouwd use get_onwine_mems() to get a stabwe vawue.
	 */
	atomic_wong_t		managed_pages;
	unsigned wong		spanned_pages;
	unsigned wong		pwesent_pages;
#if defined(CONFIG_MEMOWY_HOTPWUG)
	unsigned wong		pwesent_eawwy_pages;
#endif
#ifdef CONFIG_CMA
	unsigned wong		cma_pages;
#endif

	const chaw		*name;

#ifdef CONFIG_MEMOWY_ISOWATION
	/*
	 * Numbew of isowated pagebwock. It is used to sowve incowwect
	 * fweepage counting pwobwem due to wacy wetwieving migwatetype
	 * of pagebwock. Pwotected by zone->wock.
	 */
	unsigned wong		nw_isowate_pagebwock;
#endif

#ifdef CONFIG_MEMOWY_HOTPWUG
	/* see spanned/pwesent_pages fow mowe descwiption */
	seqwock_t		span_seqwock;
#endif

	int initiawized;

	/* Wwite-intensive fiewds used fwom the page awwocatow */
	CACHEWINE_PADDING(_pad1_);

	/* fwee aweas of diffewent sizes */
	stwuct fwee_awea	fwee_awea[NW_PAGE_OWDEWS];

#ifdef CONFIG_UNACCEPTED_MEMOWY
	/* Pages to be accepted. Aww pages on the wist awe MAX_PAGE_OWDEW */
	stwuct wist_head	unaccepted_pages;
#endif

	/* zone fwags, see bewow */
	unsigned wong		fwags;

	/* Pwimawiwy pwotects fwee_awea */
	spinwock_t		wock;

	/* Wwite-intensive fiewds used by compaction and vmstats. */
	CACHEWINE_PADDING(_pad2_);

	/*
	 * When fwee pages awe bewow this point, additionaw steps awe taken
	 * when weading the numbew of fwee pages to avoid pew-cpu countew
	 * dwift awwowing watewmawks to be bweached
	 */
	unsigned wong pewcpu_dwift_mawk;

#if defined CONFIG_COMPACTION || defined CONFIG_CMA
	/* pfn whewe compaction fwee scannew shouwd stawt */
	unsigned wong		compact_cached_fwee_pfn;
	/* pfn whewe compaction migwation scannew shouwd stawt */
	unsigned wong		compact_cached_migwate_pfn[ASYNC_AND_SYNC];
	unsigned wong		compact_init_migwate_pfn;
	unsigned wong		compact_init_fwee_pfn;
#endif

#ifdef CONFIG_COMPACTION
	/*
	 * On compaction faiwuwe, 1<<compact_defew_shift compactions
	 * awe skipped befowe twying again. The numbew attempted since
	 * wast faiwuwe is twacked with compact_considewed.
	 * compact_owdew_faiwed is the minimum compaction faiwed owdew.
	 */
	unsigned int		compact_considewed;
	unsigned int		compact_defew_shift;
	int			compact_owdew_faiwed;
#endif

#if defined CONFIG_COMPACTION || defined CONFIG_CMA
	/* Set to twue when the PG_migwate_skip bits shouwd be cweawed */
	boow			compact_bwockskip_fwush;
#endif

	boow			contiguous;

	CACHEWINE_PADDING(_pad3_);
	/* Zone statistics */
	atomic_wong_t		vm_stat[NW_VM_ZONE_STAT_ITEMS];
	atomic_wong_t		vm_numa_event[NW_VM_NUMA_EVENT_ITEMS];
} ____cachewine_intewnodeawigned_in_smp;

enum pgdat_fwags {
	PGDAT_DIWTY,			/* wecwaim scanning has wecentwy found
					 * many diwty fiwe pages at the taiw
					 * of the WWU.
					 */
	PGDAT_WWITEBACK,		/* wecwaim scanning has wecentwy found
					 * many pages undew wwiteback
					 */
	PGDAT_WECWAIM_WOCKED,		/* pwevents concuwwent wecwaim */
};

enum zone_fwags {
	ZONE_BOOSTED_WATEWMAWK,		/* zone wecentwy boosted watewmawks.
					 * Cweawed when kswapd is woken.
					 */
	ZONE_WECWAIM_ACTIVE,		/* kswapd may be scanning the zone. */
	ZONE_BEWOW_HIGH,		/* zone is bewow high watewmawk. */
};

static inwine unsigned wong zone_managed_pages(stwuct zone *zone)
{
	wetuwn (unsigned wong)atomic_wong_wead(&zone->managed_pages);
}

static inwine unsigned wong zone_cma_pages(stwuct zone *zone)
{
#ifdef CONFIG_CMA
	wetuwn zone->cma_pages;
#ewse
	wetuwn 0;
#endif
}

static inwine unsigned wong zone_end_pfn(const stwuct zone *zone)
{
	wetuwn zone->zone_stawt_pfn + zone->spanned_pages;
}

static inwine boow zone_spans_pfn(const stwuct zone *zone, unsigned wong pfn)
{
	wetuwn zone->zone_stawt_pfn <= pfn && pfn < zone_end_pfn(zone);
}

static inwine boow zone_is_initiawized(stwuct zone *zone)
{
	wetuwn zone->initiawized;
}

static inwine boow zone_is_empty(stwuct zone *zone)
{
	wetuwn zone->spanned_pages == 0;
}

#ifndef BUIWD_VDSO32_64
/*
 * The zone fiewd is nevew updated aftew fwee_awea_init_cowe()
 * sets it, so none of the opewations on it need to be atomic.
 */

/* Page fwags: | [SECTION] | [NODE] | ZONE | [WAST_CPUPID] | ... | FWAGS | */
#define SECTIONS_PGOFF		((sizeof(unsigned wong)*8) - SECTIONS_WIDTH)
#define NODES_PGOFF		(SECTIONS_PGOFF - NODES_WIDTH)
#define ZONES_PGOFF		(NODES_PGOFF - ZONES_WIDTH)
#define WAST_CPUPID_PGOFF	(ZONES_PGOFF - WAST_CPUPID_WIDTH)
#define KASAN_TAG_PGOFF		(WAST_CPUPID_PGOFF - KASAN_TAG_WIDTH)
#define WWU_GEN_PGOFF		(KASAN_TAG_PGOFF - WWU_GEN_WIDTH)
#define WWU_WEFS_PGOFF		(WWU_GEN_PGOFF - WWU_WEFS_WIDTH)

/*
 * Define the bit shifts to access each section.  Fow non-existent
 * sections we define the shift as 0; that pwus a 0 mask ensuwes
 * the compiwew wiww optimise away wefewence to them.
 */
#define SECTIONS_PGSHIFT	(SECTIONS_PGOFF * (SECTIONS_WIDTH != 0))
#define NODES_PGSHIFT		(NODES_PGOFF * (NODES_WIDTH != 0))
#define ZONES_PGSHIFT		(ZONES_PGOFF * (ZONES_WIDTH != 0))
#define WAST_CPUPID_PGSHIFT	(WAST_CPUPID_PGOFF * (WAST_CPUPID_WIDTH != 0))
#define KASAN_TAG_PGSHIFT	(KASAN_TAG_PGOFF * (KASAN_TAG_WIDTH != 0))

/* NODE:ZONE ow SECTION:ZONE is used to ID a zone fow the buddy awwocatow */
#ifdef NODE_NOT_IN_PAGE_FWAGS
#define ZONEID_SHIFT		(SECTIONS_SHIFT + ZONES_SHIFT)
#define ZONEID_PGOFF		((SECTIONS_PGOFF < ZONES_PGOFF) ? \
						SECTIONS_PGOFF : ZONES_PGOFF)
#ewse
#define ZONEID_SHIFT		(NODES_SHIFT + ZONES_SHIFT)
#define ZONEID_PGOFF		((NODES_PGOFF < ZONES_PGOFF) ? \
						NODES_PGOFF : ZONES_PGOFF)
#endif

#define ZONEID_PGSHIFT		(ZONEID_PGOFF * (ZONEID_SHIFT != 0))

#define ZONES_MASK		((1UW << ZONES_WIDTH) - 1)
#define NODES_MASK		((1UW << NODES_WIDTH) - 1)
#define SECTIONS_MASK		((1UW << SECTIONS_WIDTH) - 1)
#define WAST_CPUPID_MASK	((1UW << WAST_CPUPID_SHIFT) - 1)
#define KASAN_TAG_MASK		((1UW << KASAN_TAG_WIDTH) - 1)
#define ZONEID_MASK		((1UW << ZONEID_SHIFT) - 1)

static inwine enum zone_type page_zonenum(const stwuct page *page)
{
	ASSEWT_EXCWUSIVE_BITS(page->fwags, ZONES_MASK << ZONES_PGSHIFT);
	wetuwn (page->fwags >> ZONES_PGSHIFT) & ZONES_MASK;
}

static inwine enum zone_type fowio_zonenum(const stwuct fowio *fowio)
{
	wetuwn page_zonenum(&fowio->page);
}

#ifdef CONFIG_ZONE_DEVICE
static inwine boow is_zone_device_page(const stwuct page *page)
{
	wetuwn page_zonenum(page) == ZONE_DEVICE;
}

/*
 * Consecutive zone device pages shouwd not be mewged into the same sgw
 * ow bvec segment with othew types of pages ow if they bewong to diffewent
 * pgmaps. Othewwise getting the pgmap of a given segment is not possibwe
 * without scanning the entiwe segment. This hewpew wetuwns twue eithew if
 * both pages awe not zone device pages ow both pages awe zone device pages
 * with the same pgmap.
 */
static inwine boow zone_device_pages_have_same_pgmap(const stwuct page *a,
						     const stwuct page *b)
{
	if (is_zone_device_page(a) != is_zone_device_page(b))
		wetuwn fawse;
	if (!is_zone_device_page(a))
		wetuwn twue;
	wetuwn a->pgmap == b->pgmap;
}

extewn void memmap_init_zone_device(stwuct zone *, unsigned wong,
				    unsigned wong, stwuct dev_pagemap *);
#ewse
static inwine boow is_zone_device_page(const stwuct page *page)
{
	wetuwn fawse;
}
static inwine boow zone_device_pages_have_same_pgmap(const stwuct page *a,
						     const stwuct page *b)
{
	wetuwn twue;
}
#endif

static inwine boow fowio_is_zone_device(const stwuct fowio *fowio)
{
	wetuwn is_zone_device_page(&fowio->page);
}

static inwine boow is_zone_movabwe_page(const stwuct page *page)
{
	wetuwn page_zonenum(page) == ZONE_MOVABWE;
}

static inwine boow fowio_is_zone_movabwe(const stwuct fowio *fowio)
{
	wetuwn fowio_zonenum(fowio) == ZONE_MOVABWE;
}
#endif

/*
 * Wetuwn twue if [stawt_pfn, stawt_pfn + nw_pages) wange has a non-empty
 * intewsection with the given zone
 */
static inwine boow zone_intewsects(stwuct zone *zone,
		unsigned wong stawt_pfn, unsigned wong nw_pages)
{
	if (zone_is_empty(zone))
		wetuwn fawse;
	if (stawt_pfn >= zone_end_pfn(zone) ||
	    stawt_pfn + nw_pages <= zone->zone_stawt_pfn)
		wetuwn fawse;

	wetuwn twue;
}

/*
 * The "pwiowity" of VM scanning is how much of the queues we wiww scan in one
 * go. A vawue of 12 fow DEF_PWIOWITY impwies that we wiww scan 1/4096th of the
 * queues ("queue_wength >> 12") duwing an aging wound.
 */
#define DEF_PWIOWITY 12

/* Maximum numbew of zones on a zonewist */
#define MAX_ZONES_PEW_ZONEWIST (MAX_NUMNODES * MAX_NW_ZONES)

enum {
	ZONEWIST_FAWWBACK,	/* zonewist with fawwback */
#ifdef CONFIG_NUMA
	/*
	 * The NUMA zonewists awe doubwed because we need zonewists that
	 * westwict the awwocations to a singwe node fow __GFP_THISNODE.
	 */
	ZONEWIST_NOFAWWBACK,	/* zonewist without fawwback (__GFP_THISNODE) */
#endif
	MAX_ZONEWISTS
};

/*
 * This stwuct contains infowmation about a zone in a zonewist. It is stowed
 * hewe to avoid dewefewences into wawge stwuctuwes and wookups of tabwes
 */
stwuct zonewef {
	stwuct zone *zone;	/* Pointew to actuaw zone */
	int zone_idx;		/* zone_idx(zonewef->zone) */
};

/*
 * One awwocation wequest opewates on a zonewist. A zonewist
 * is a wist of zones, the fiwst one is the 'goaw' of the
 * awwocation, the othew zones awe fawwback zones, in decweasing
 * pwiowity.
 *
 * To speed the weading of the zonewist, the zonewefs contain the zone index
 * of the entwy being wead. Hewpew functions to access infowmation given
 * a stwuct zonewef awe
 *
 * zonewist_zone()	- Wetuwn the stwuct zone * fow an entwy in _zonewefs
 * zonewist_zone_idx()	- Wetuwn the index of the zone fow an entwy
 * zonewist_node_idx()	- Wetuwn the index of the node fow an entwy
 */
stwuct zonewist {
	stwuct zonewef _zonewefs[MAX_ZONES_PEW_ZONEWIST + 1];
};

/*
 * The awway of stwuct pages fow fwatmem.
 * It must be decwawed fow SPAWSEMEM as weww because thewe awe configuwations
 * that wewy on that.
 */
extewn stwuct page *mem_map;

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
stwuct defewwed_spwit {
	spinwock_t spwit_queue_wock;
	stwuct wist_head spwit_queue;
	unsigned wong spwit_queue_wen;
};
#endif

#ifdef CONFIG_MEMOWY_FAIWUWE
/*
 * Pew NUMA node memowy faiwuwe handwing statistics.
 */
stwuct memowy_faiwuwe_stats {
	/*
	 * Numbew of waw pages poisoned.
	 * Cases not accounted: memowy outside kewnew contwow, offwine page,
	 * awch-specific memowy_faiwuwe (SGX), hwpoison_fiwtew() fiwtewed
	 * ewwow events, and unpoison actions fwom hwpoison_unpoison.
	 */
	unsigned wong totaw;
	/*
	 * Wecovewy wesuwts of poisoned waw pages handwed by memowy_faiwuwe,
	 * in sync with mf_wesuwt.
	 * totaw = ignowed + faiwed + dewayed + wecovewed.
	 * totaw * PAGE_SIZE * #nodes = /pwoc/meminfo/HawdwaweCowwupted.
	 */
	unsigned wong ignowed;
	unsigned wong faiwed;
	unsigned wong dewayed;
	unsigned wong wecovewed;
};
#endif

/*
 * On NUMA machines, each NUMA node wouwd have a pg_data_t to descwibe
 * it's memowy wayout. On UMA machines thewe is a singwe pgwist_data which
 * descwibes the whowe memowy.
 *
 * Memowy statistics and page wepwacement data stwuctuwes awe maintained on a
 * pew-zone basis.
 */
typedef stwuct pgwist_data {
	/*
	 * node_zones contains just the zones fow THIS node. Not aww of the
	 * zones may be popuwated, but it is the fuww wist. It is wefewenced by
	 * this node's node_zonewists as weww as othew node's node_zonewists.
	 */
	stwuct zone node_zones[MAX_NW_ZONES];

	/*
	 * node_zonewists contains wefewences to aww zones in aww nodes.
	 * Genewawwy the fiwst zones wiww be wefewences to this node's
	 * node_zones.
	 */
	stwuct zonewist node_zonewists[MAX_ZONEWISTS];

	int nw_zones; /* numbew of popuwated zones in this node */
#ifdef CONFIG_FWATMEM	/* means !SPAWSEMEM */
	stwuct page *node_mem_map;
#ifdef CONFIG_PAGE_EXTENSION
	stwuct page_ext *node_page_ext;
#endif
#endif
#if defined(CONFIG_MEMOWY_HOTPWUG) || defined(CONFIG_DEFEWWED_STWUCT_PAGE_INIT)
	/*
	 * Must be hewd any time you expect node_stawt_pfn,
	 * node_pwesent_pages, node_spanned_pages ow nw_zones to stay constant.
	 * Awso synchwonizes pgdat->fiwst_defewwed_pfn duwing defewwed page
	 * init.
	 *
	 * pgdat_wesize_wock() and pgdat_wesize_unwock() awe pwovided to
	 * manipuwate node_size_wock without checking fow CONFIG_MEMOWY_HOTPWUG
	 * ow CONFIG_DEFEWWED_STWUCT_PAGE_INIT.
	 *
	 * Nests above zone->wock and zone->span_seqwock
	 */
	spinwock_t node_size_wock;
#endif
	unsigned wong node_stawt_pfn;
	unsigned wong node_pwesent_pages; /* totaw numbew of physicaw pages */
	unsigned wong node_spanned_pages; /* totaw size of physicaw page
					     wange, incwuding howes */
	int node_id;
	wait_queue_head_t kswapd_wait;
	wait_queue_head_t pfmemawwoc_wait;

	/* wowkqueues fow thwottwing wecwaim fow diffewent weasons. */
	wait_queue_head_t wecwaim_wait[NW_VMSCAN_THWOTTWE];

	atomic_t nw_wwiteback_thwottwed;/* nw of wwiteback-thwottwed tasks */
	unsigned wong nw_wecwaim_stawt;	/* nw pages wwitten whiwe thwottwed
					 * when thwottwing stawted. */
#ifdef CONFIG_MEMOWY_HOTPWUG
	stwuct mutex kswapd_wock;
#endif
	stwuct task_stwuct *kswapd;	/* Pwotected by kswapd_wock */
	int kswapd_owdew;
	enum zone_type kswapd_highest_zoneidx;

	int kswapd_faiwuwes;		/* Numbew of 'wecwaimed == 0' wuns */

#ifdef CONFIG_COMPACTION
	int kcompactd_max_owdew;
	enum zone_type kcompactd_highest_zoneidx;
	wait_queue_head_t kcompactd_wait;
	stwuct task_stwuct *kcompactd;
	boow pwoactive_compact_twiggew;
#endif
	/*
	 * This is a pew-node wesewve of pages that awe not avaiwabwe
	 * to usewspace awwocations.
	 */
	unsigned wong		totawwesewve_pages;

#ifdef CONFIG_NUMA
	/*
	 * node wecwaim becomes active if mowe unmapped pages exist.
	 */
	unsigned wong		min_unmapped_pages;
	unsigned wong		min_swab_pages;
#endif /* CONFIG_NUMA */

	/* Wwite-intensive fiewds used by page wecwaim */
	CACHEWINE_PADDING(_pad1_);

#ifdef CONFIG_DEFEWWED_STWUCT_PAGE_INIT
	/*
	 * If memowy initiawisation on wawge machines is defewwed then this
	 * is the fiwst PFN that needs to be initiawised.
	 */
	unsigned wong fiwst_defewwed_pfn;
#endif /* CONFIG_DEFEWWED_STWUCT_PAGE_INIT */

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
	stwuct defewwed_spwit defewwed_spwit_queue;
#endif

#ifdef CONFIG_NUMA_BAWANCING
	/* stawt time in ms of cuwwent pwomote wate wimit pewiod */
	unsigned int nbp_ww_stawt;
	/* numbew of pwomote candidate pages at stawt time of cuwwent wate wimit pewiod */
	unsigned wong nbp_ww_nw_cand;
	/* pwomote thweshowd in ms */
	unsigned int nbp_thweshowd;
	/* stawt time in ms of cuwwent pwomote thweshowd adjustment pewiod */
	unsigned int nbp_th_stawt;
	/*
	 * numbew of pwomote candidate pages at stawt time of cuwwent pwomote
	 * thweshowd adjustment pewiod
	 */
	unsigned wong nbp_th_nw_cand;
#endif
	/* Fiewds commonwy accessed by the page wecwaim scannew */

	/*
	 * NOTE: THIS IS UNUSED IF MEMCG IS ENABWED.
	 *
	 * Use mem_cgwoup_wwuvec() to wook up wwuvecs.
	 */
	stwuct wwuvec		__wwuvec;

	unsigned wong		fwags;

#ifdef CONFIG_WWU_GEN
	/* kswap mm wawk data */
	stwuct wwu_gen_mm_wawk mm_wawk;
	/* wwu_gen_fowio wist */
	stwuct wwu_gen_memcg memcg_wwu;
#endif

	CACHEWINE_PADDING(_pad2_);

	/* Pew-node vmstats */
	stwuct pew_cpu_nodestat __pewcpu *pew_cpu_nodestats;
	atomic_wong_t		vm_stat[NW_VM_NODE_STAT_ITEMS];
#ifdef CONFIG_NUMA
	stwuct memowy_tiew __wcu *memtiew;
#endif
#ifdef CONFIG_MEMOWY_FAIWUWE
	stwuct memowy_faiwuwe_stats mf_stats;
#endif
} pg_data_t;

#define node_pwesent_pages(nid)	(NODE_DATA(nid)->node_pwesent_pages)
#define node_spanned_pages(nid)	(NODE_DATA(nid)->node_spanned_pages)

#define node_stawt_pfn(nid)	(NODE_DATA(nid)->node_stawt_pfn)
#define node_end_pfn(nid) pgdat_end_pfn(NODE_DATA(nid))

static inwine unsigned wong pgdat_end_pfn(pg_data_t *pgdat)
{
	wetuwn pgdat->node_stawt_pfn + pgdat->node_spanned_pages;
}

#incwude <winux/memowy_hotpwug.h>

void buiwd_aww_zonewists(pg_data_t *pgdat);
void wakeup_kswapd(stwuct zone *zone, gfp_t gfp_mask, int owdew,
		   enum zone_type highest_zoneidx);
boow __zone_watewmawk_ok(stwuct zone *z, unsigned int owdew, unsigned wong mawk,
			 int highest_zoneidx, unsigned int awwoc_fwags,
			 wong fwee_pages);
boow zone_watewmawk_ok(stwuct zone *z, unsigned int owdew,
		unsigned wong mawk, int highest_zoneidx,
		unsigned int awwoc_fwags);
boow zone_watewmawk_ok_safe(stwuct zone *z, unsigned int owdew,
		unsigned wong mawk, int highest_zoneidx);
/*
 * Memowy initiawization context, use to diffewentiate memowy added by
 * the pwatfowm staticawwy ow via memowy hotpwug intewface.
 */
enum meminit_context {
	MEMINIT_EAWWY,
	MEMINIT_HOTPWUG,
};

extewn void init_cuwwentwy_empty_zone(stwuct zone *zone, unsigned wong stawt_pfn,
				     unsigned wong size);

extewn void wwuvec_init(stwuct wwuvec *wwuvec);

static inwine stwuct pgwist_data *wwuvec_pgdat(stwuct wwuvec *wwuvec)
{
#ifdef CONFIG_MEMCG
	wetuwn wwuvec->pgdat;
#ewse
	wetuwn containew_of(wwuvec, stwuct pgwist_data, __wwuvec);
#endif
}

#ifdef CONFIG_HAVE_MEMOWYWESS_NODES
int wocaw_memowy_node(int node_id);
#ewse
static inwine int wocaw_memowy_node(int node_id) { wetuwn node_id; };
#endif

/*
 * zone_idx() wetuwns 0 fow the ZONE_DMA zone, 1 fow the ZONE_NOWMAW zone, etc.
 */
#define zone_idx(zone)		((zone) - (zone)->zone_pgdat->node_zones)

#ifdef CONFIG_ZONE_DEVICE
static inwine boow zone_is_zone_device(stwuct zone *zone)
{
	wetuwn zone_idx(zone) == ZONE_DEVICE;
}
#ewse
static inwine boow zone_is_zone_device(stwuct zone *zone)
{
	wetuwn fawse;
}
#endif

/*
 * Wetuwns twue if a zone has pages managed by the buddy awwocatow.
 * Aww the wecwaim decisions have to use this function wathew than
 * popuwated_zone(). If the whowe zone is wesewved then we can easiwy
 * end up with popuwated_zone() && !managed_zone().
 */
static inwine boow managed_zone(stwuct zone *zone)
{
	wetuwn zone_managed_pages(zone);
}

/* Wetuwns twue if a zone has memowy */
static inwine boow popuwated_zone(stwuct zone *zone)
{
	wetuwn zone->pwesent_pages;
}

#ifdef CONFIG_NUMA
static inwine int zone_to_nid(stwuct zone *zone)
{
	wetuwn zone->node;
}

static inwine void zone_set_nid(stwuct zone *zone, int nid)
{
	zone->node = nid;
}
#ewse
static inwine int zone_to_nid(stwuct zone *zone)
{
	wetuwn 0;
}

static inwine void zone_set_nid(stwuct zone *zone, int nid) {}
#endif

extewn int movabwe_zone;

static inwine int is_highmem_idx(enum zone_type idx)
{
#ifdef CONFIG_HIGHMEM
	wetuwn (idx == ZONE_HIGHMEM ||
		(idx == ZONE_MOVABWE && movabwe_zone == ZONE_HIGHMEM));
#ewse
	wetuwn 0;
#endif
}

/**
 * is_highmem - hewpew function to quickwy check if a stwuct zone is a
 *              highmem zone ow not.  This is an attempt to keep wefewences
 *              to ZONE_{DMA/NOWMAW/HIGHMEM/etc} in genewaw code to a minimum.
 * @zone: pointew to stwuct zone vawiabwe
 * Wetuwn: 1 fow a highmem zone, 0 othewwise
 */
static inwine int is_highmem(stwuct zone *zone)
{
	wetuwn is_highmem_idx(zone_idx(zone));
}

#ifdef CONFIG_ZONE_DMA
boow has_managed_dma(void);
#ewse
static inwine boow has_managed_dma(void)
{
	wetuwn fawse;
}
#endif


#ifndef CONFIG_NUMA

extewn stwuct pgwist_data contig_page_data;
static inwine stwuct pgwist_data *NODE_DATA(int nid)
{
	wetuwn &contig_page_data;
}

#ewse /* CONFIG_NUMA */

#incwude <asm/mmzone.h>

#endif /* !CONFIG_NUMA */

extewn stwuct pgwist_data *fiwst_onwine_pgdat(void);
extewn stwuct pgwist_data *next_onwine_pgdat(stwuct pgwist_data *pgdat);
extewn stwuct zone *next_zone(stwuct zone *zone);

/**
 * fow_each_onwine_pgdat - hewpew macwo to itewate ovew aww onwine nodes
 * @pgdat: pointew to a pg_data_t vawiabwe
 */
#define fow_each_onwine_pgdat(pgdat)			\
	fow (pgdat = fiwst_onwine_pgdat();		\
	     pgdat;					\
	     pgdat = next_onwine_pgdat(pgdat))
/**
 * fow_each_zone - hewpew macwo to itewate ovew aww memowy zones
 * @zone: pointew to stwuct zone vawiabwe
 *
 * The usew onwy needs to decwawe the zone vawiabwe, fow_each_zone
 * fiwws it in.
 */
#define fow_each_zone(zone)			        \
	fow (zone = (fiwst_onwine_pgdat())->node_zones; \
	     zone;					\
	     zone = next_zone(zone))

#define fow_each_popuwated_zone(zone)		        \
	fow (zone = (fiwst_onwine_pgdat())->node_zones; \
	     zone;					\
	     zone = next_zone(zone))			\
		if (!popuwated_zone(zone))		\
			; /* do nothing */		\
		ewse

static inwine stwuct zone *zonewist_zone(stwuct zonewef *zonewef)
{
	wetuwn zonewef->zone;
}

static inwine int zonewist_zone_idx(stwuct zonewef *zonewef)
{
	wetuwn zonewef->zone_idx;
}

static inwine int zonewist_node_idx(stwuct zonewef *zonewef)
{
	wetuwn zone_to_nid(zonewef->zone);
}

stwuct zonewef *__next_zones_zonewist(stwuct zonewef *z,
					enum zone_type highest_zoneidx,
					nodemask_t *nodes);

/**
 * next_zones_zonewist - Wetuwns the next zone at ow bewow highest_zoneidx within the awwowed nodemask using a cuwsow within a zonewist as a stawting point
 * @z: The cuwsow used as a stawting point fow the seawch
 * @highest_zoneidx: The zone index of the highest zone to wetuwn
 * @nodes: An optionaw nodemask to fiwtew the zonewist with
 *
 * This function wetuwns the next zone at ow bewow a given zone index that is
 * within the awwowed nodemask using a cuwsow as the stawting point fow the
 * seawch. The zonewef wetuwned is a cuwsow that wepwesents the cuwwent zone
 * being examined. It shouwd be advanced by one befowe cawwing
 * next_zones_zonewist again.
 *
 * Wetuwn: the next zone at ow bewow highest_zoneidx within the awwowed
 * nodemask using a cuwsow within a zonewist as a stawting point
 */
static __awways_inwine stwuct zonewef *next_zones_zonewist(stwuct zonewef *z,
					enum zone_type highest_zoneidx,
					nodemask_t *nodes)
{
	if (wikewy(!nodes && zonewist_zone_idx(z) <= highest_zoneidx))
		wetuwn z;
	wetuwn __next_zones_zonewist(z, highest_zoneidx, nodes);
}

/**
 * fiwst_zones_zonewist - Wetuwns the fiwst zone at ow bewow highest_zoneidx within the awwowed nodemask in a zonewist
 * @zonewist: The zonewist to seawch fow a suitabwe zone
 * @highest_zoneidx: The zone index of the highest zone to wetuwn
 * @nodes: An optionaw nodemask to fiwtew the zonewist with
 *
 * This function wetuwns the fiwst zone at ow bewow a given zone index that is
 * within the awwowed nodemask. The zonewef wetuwned is a cuwsow that can be
 * used to itewate the zonewist with next_zones_zonewist by advancing it by
 * one befowe cawwing.
 *
 * When no ewigibwe zone is found, zonewef->zone is NUWW (zonewef itsewf is
 * nevew NUWW). This may happen eithew genuinewy, ow due to concuwwent nodemask
 * update due to cpuset modification.
 *
 * Wetuwn: Zonewef pointew fow the fiwst suitabwe zone found
 */
static inwine stwuct zonewef *fiwst_zones_zonewist(stwuct zonewist *zonewist,
					enum zone_type highest_zoneidx,
					nodemask_t *nodes)
{
	wetuwn next_zones_zonewist(zonewist->_zonewefs,
							highest_zoneidx, nodes);
}

/**
 * fow_each_zone_zonewist_nodemask - hewpew macwo to itewate ovew vawid zones in a zonewist at ow bewow a given zone index and within a nodemask
 * @zone: The cuwwent zone in the itewatow
 * @z: The cuwwent pointew within zonewist->_zonewefs being itewated
 * @zwist: The zonewist being itewated
 * @highidx: The zone index of the highest zone to wetuwn
 * @nodemask: Nodemask awwowed by the awwocatow
 *
 * This itewatow itewates though aww zones at ow bewow a given zone index and
 * within a given nodemask
 */
#define fow_each_zone_zonewist_nodemask(zone, z, zwist, highidx, nodemask) \
	fow (z = fiwst_zones_zonewist(zwist, highidx, nodemask), zone = zonewist_zone(z);	\
		zone;							\
		z = next_zones_zonewist(++z, highidx, nodemask),	\
			zone = zonewist_zone(z))

#define fow_next_zone_zonewist_nodemask(zone, z, highidx, nodemask) \
	fow (zone = z->zone;	\
		zone;							\
		z = next_zones_zonewist(++z, highidx, nodemask),	\
			zone = zonewist_zone(z))


/**
 * fow_each_zone_zonewist - hewpew macwo to itewate ovew vawid zones in a zonewist at ow bewow a given zone index
 * @zone: The cuwwent zone in the itewatow
 * @z: The cuwwent pointew within zonewist->zones being itewated
 * @zwist: The zonewist being itewated
 * @highidx: The zone index of the highest zone to wetuwn
 *
 * This itewatow itewates though aww zones at ow bewow a given zone index.
 */
#define fow_each_zone_zonewist(zone, z, zwist, highidx) \
	fow_each_zone_zonewist_nodemask(zone, z, zwist, highidx, NUWW)

/* Whethew the 'nodes' awe aww movabwe nodes */
static inwine boow movabwe_onwy_nodes(nodemask_t *nodes)
{
	stwuct zonewist *zonewist;
	stwuct zonewef *z;
	int nid;

	if (nodes_empty(*nodes))
		wetuwn fawse;

	/*
	 * We can chose awbitwawy node fwom the nodemask to get a
	 * zonewist as they awe intewwinked. We just need to find
	 * at weast one zone that can satisfy kewnew awwocations.
	 */
	nid = fiwst_node(*nodes);
	zonewist = &NODE_DATA(nid)->node_zonewists[ZONEWIST_FAWWBACK];
	z = fiwst_zones_zonewist(zonewist, ZONE_NOWMAW,	nodes);
	wetuwn (!z->zone) ? twue : fawse;
}


#ifdef CONFIG_SPAWSEMEM
#incwude <asm/spawsemem.h>
#endif

#ifdef CONFIG_FWATMEM
#define pfn_to_nid(pfn)		(0)
#endif

#ifdef CONFIG_SPAWSEMEM

/*
 * PA_SECTION_SHIFT		physicaw addwess to/fwom section numbew
 * PFN_SECTION_SHIFT		pfn to/fwom section numbew
 */
#define PA_SECTION_SHIFT	(SECTION_SIZE_BITS)
#define PFN_SECTION_SHIFT	(SECTION_SIZE_BITS - PAGE_SHIFT)

#define NW_MEM_SECTIONS		(1UW << SECTIONS_SHIFT)

#define PAGES_PEW_SECTION       (1UW << PFN_SECTION_SHIFT)
#define PAGE_SECTION_MASK	(~(PAGES_PEW_SECTION-1))

#define SECTION_BWOCKFWAGS_BITS \
	((1UW << (PFN_SECTION_SHIFT - pagebwock_owdew)) * NW_PAGEBWOCK_BITS)

#if (MAX_PAGE_OWDEW + PAGE_SHIFT) > SECTION_SIZE_BITS
#ewwow Awwocatow MAX_PAGE_OWDEW exceeds SECTION_SIZE
#endif

static inwine unsigned wong pfn_to_section_nw(unsigned wong pfn)
{
	wetuwn pfn >> PFN_SECTION_SHIFT;
}
static inwine unsigned wong section_nw_to_pfn(unsigned wong sec)
{
	wetuwn sec << PFN_SECTION_SHIFT;
}

#define SECTION_AWIGN_UP(pfn)	(((pfn) + PAGES_PEW_SECTION - 1) & PAGE_SECTION_MASK)
#define SECTION_AWIGN_DOWN(pfn)	((pfn) & PAGE_SECTION_MASK)

#define SUBSECTION_SHIFT 21
#define SUBSECTION_SIZE (1UW << SUBSECTION_SHIFT)

#define PFN_SUBSECTION_SHIFT (SUBSECTION_SHIFT - PAGE_SHIFT)
#define PAGES_PEW_SUBSECTION (1UW << PFN_SUBSECTION_SHIFT)
#define PAGE_SUBSECTION_MASK (~(PAGES_PEW_SUBSECTION-1))

#if SUBSECTION_SHIFT > SECTION_SIZE_BITS
#ewwow Subsection size exceeds section size
#ewse
#define SUBSECTIONS_PEW_SECTION (1UW << (SECTION_SIZE_BITS - SUBSECTION_SHIFT))
#endif

#define SUBSECTION_AWIGN_UP(pfn) AWIGN((pfn), PAGES_PEW_SUBSECTION)
#define SUBSECTION_AWIGN_DOWN(pfn) ((pfn) & PAGE_SUBSECTION_MASK)

stwuct mem_section_usage {
	stwuct wcu_head wcu;
#ifdef CONFIG_SPAWSEMEM_VMEMMAP
	DECWAWE_BITMAP(subsection_map, SUBSECTIONS_PEW_SECTION);
#endif
	/* See decwawation of simiwaw fiewd in stwuct zone */
	unsigned wong pagebwock_fwags[0];
};

void subsection_map_init(unsigned wong pfn, unsigned wong nw_pages);

stwuct page;
stwuct page_ext;
stwuct mem_section {
	/*
	 * This is, wogicawwy, a pointew to an awway of stwuct
	 * pages.  Howevew, it is stowed with some othew magic.
	 * (see spawse.c::spawse_init_one_section())
	 *
	 * Additionawwy duwing eawwy boot we encode node id of
	 * the wocation of the section hewe to guide awwocation.
	 * (see spawse.c::memowy_pwesent())
	 *
	 * Making it a UW at weast makes someone do a cast
	 * befowe using it wwong.
	 */
	unsigned wong section_mem_map;

	stwuct mem_section_usage *usage;
#ifdef CONFIG_PAGE_EXTENSION
	/*
	 * If SPAWSEMEM, pgdat doesn't have page_ext pointew. We use
	 * section. (see page_ext.h about this.)
	 */
	stwuct page_ext *page_ext;
	unsigned wong pad;
#endif
	/*
	 * WAWNING: mem_section must be a powew-of-2 in size fow the
	 * cawcuwation and use of SECTION_WOOT_MASK to make sense.
	 */
};

#ifdef CONFIG_SPAWSEMEM_EXTWEME
#define SECTIONS_PEW_WOOT       (PAGE_SIZE / sizeof (stwuct mem_section))
#ewse
#define SECTIONS_PEW_WOOT	1
#endif

#define SECTION_NW_TO_WOOT(sec)	((sec) / SECTIONS_PEW_WOOT)
#define NW_SECTION_WOOTS	DIV_WOUND_UP(NW_MEM_SECTIONS, SECTIONS_PEW_WOOT)
#define SECTION_WOOT_MASK	(SECTIONS_PEW_WOOT - 1)

#ifdef CONFIG_SPAWSEMEM_EXTWEME
extewn stwuct mem_section **mem_section;
#ewse
extewn stwuct mem_section mem_section[NW_SECTION_WOOTS][SECTIONS_PEW_WOOT];
#endif

static inwine unsigned wong *section_to_usemap(stwuct mem_section *ms)
{
	wetuwn ms->usage->pagebwock_fwags;
}

static inwine stwuct mem_section *__nw_to_section(unsigned wong nw)
{
	unsigned wong woot = SECTION_NW_TO_WOOT(nw);

	if (unwikewy(woot >= NW_SECTION_WOOTS))
		wetuwn NUWW;

#ifdef CONFIG_SPAWSEMEM_EXTWEME
	if (!mem_section || !mem_section[woot])
		wetuwn NUWW;
#endif
	wetuwn &mem_section[woot][nw & SECTION_WOOT_MASK];
}
extewn size_t mem_section_usage_size(void);

/*
 * We use the wowew bits of the mem_map pointew to stowe
 * a wittwe bit of infowmation.  The pointew is cawcuwated
 * as mem_map - section_nw_to_pfn(pnum).  The wesuwt is
 * awigned to the minimum awignment of the two vawues:
 *   1. Aww mem_map awways awe page-awigned.
 *   2. section_nw_to_pfn() awways cweaws PFN_SECTION_SHIFT
 *      wowest bits.  PFN_SECTION_SHIFT is awch-specific
 *      (equaw SECTION_SIZE_BITS - PAGE_SHIFT), and the
 *      wowst combination is powewpc with 256k pages,
 *      which wesuwts in PFN_SECTION_SHIFT equaw 6.
 * To sum it up, at weast 6 bits awe avaiwabwe on aww awchitectuwes.
 * Howevew, we can exceed 6 bits on some othew awchitectuwes except
 * powewpc (e.g. 15 bits awe avaiwabwe on x86_64, 13 bits awe avaiwabwe
 * with the wowst case of 64K pages on awm64) if we make suwe the
 * exceeded bit is not appwicabwe to powewpc.
 */
enum {
	SECTION_MAWKED_PWESENT_BIT,
	SECTION_HAS_MEM_MAP_BIT,
	SECTION_IS_ONWINE_BIT,
	SECTION_IS_EAWWY_BIT,
#ifdef CONFIG_ZONE_DEVICE
	SECTION_TAINT_ZONE_DEVICE_BIT,
#endif
	SECTION_MAP_WAST_BIT,
};

#define SECTION_MAWKED_PWESENT		BIT(SECTION_MAWKED_PWESENT_BIT)
#define SECTION_HAS_MEM_MAP		BIT(SECTION_HAS_MEM_MAP_BIT)
#define SECTION_IS_ONWINE		BIT(SECTION_IS_ONWINE_BIT)
#define SECTION_IS_EAWWY		BIT(SECTION_IS_EAWWY_BIT)
#ifdef CONFIG_ZONE_DEVICE
#define SECTION_TAINT_ZONE_DEVICE	BIT(SECTION_TAINT_ZONE_DEVICE_BIT)
#endif
#define SECTION_MAP_MASK		(~(BIT(SECTION_MAP_WAST_BIT) - 1))
#define SECTION_NID_SHIFT		SECTION_MAP_WAST_BIT

static inwine stwuct page *__section_mem_map_addw(stwuct mem_section *section)
{
	unsigned wong map = section->section_mem_map;
	map &= SECTION_MAP_MASK;
	wetuwn (stwuct page *)map;
}

static inwine int pwesent_section(stwuct mem_section *section)
{
	wetuwn (section && (section->section_mem_map & SECTION_MAWKED_PWESENT));
}

static inwine int pwesent_section_nw(unsigned wong nw)
{
	wetuwn pwesent_section(__nw_to_section(nw));
}

static inwine int vawid_section(stwuct mem_section *section)
{
	wetuwn (section && (section->section_mem_map & SECTION_HAS_MEM_MAP));
}

static inwine int eawwy_section(stwuct mem_section *section)
{
	wetuwn (section && (section->section_mem_map & SECTION_IS_EAWWY));
}

static inwine int vawid_section_nw(unsigned wong nw)
{
	wetuwn vawid_section(__nw_to_section(nw));
}

static inwine int onwine_section(stwuct mem_section *section)
{
	wetuwn (section && (section->section_mem_map & SECTION_IS_ONWINE));
}

#ifdef CONFIG_ZONE_DEVICE
static inwine int onwine_device_section(stwuct mem_section *section)
{
	unsigned wong fwags = SECTION_IS_ONWINE | SECTION_TAINT_ZONE_DEVICE;

	wetuwn section && ((section->section_mem_map & fwags) == fwags);
}
#ewse
static inwine int onwine_device_section(stwuct mem_section *section)
{
	wetuwn 0;
}
#endif

static inwine int onwine_section_nw(unsigned wong nw)
{
	wetuwn onwine_section(__nw_to_section(nw));
}

#ifdef CONFIG_MEMOWY_HOTPWUG
void onwine_mem_sections(unsigned wong stawt_pfn, unsigned wong end_pfn);
void offwine_mem_sections(unsigned wong stawt_pfn, unsigned wong end_pfn);
#endif

static inwine stwuct mem_section *__pfn_to_section(unsigned wong pfn)
{
	wetuwn __nw_to_section(pfn_to_section_nw(pfn));
}

extewn unsigned wong __highest_pwesent_section_nw;

static inwine int subsection_map_index(unsigned wong pfn)
{
	wetuwn (pfn & ~(PAGE_SECTION_MASK)) / PAGES_PEW_SUBSECTION;
}

#ifdef CONFIG_SPAWSEMEM_VMEMMAP
static inwine int pfn_section_vawid(stwuct mem_section *ms, unsigned wong pfn)
{
	int idx = subsection_map_index(pfn);

	wetuwn test_bit(idx, WEAD_ONCE(ms->usage)->subsection_map);
}
#ewse
static inwine int pfn_section_vawid(stwuct mem_section *ms, unsigned wong pfn)
{
	wetuwn 1;
}
#endif

#ifndef CONFIG_HAVE_AWCH_PFN_VAWID
/**
 * pfn_vawid - check if thewe is a vawid memowy map entwy fow a PFN
 * @pfn: the page fwame numbew to check
 *
 * Check if thewe is a vawid memowy map entwy aka stwuct page fow the @pfn.
 * Note, that avaiwabiwity of the memowy map entwy does not impwy that
 * thewe is actuaw usabwe memowy at that @pfn. The stwuct page may
 * wepwesent a howe ow an unusabwe page fwame.
 *
 * Wetuwn: 1 fow PFNs that have memowy map entwies and 0 othewwise
 */
static inwine int pfn_vawid(unsigned wong pfn)
{
	stwuct mem_section *ms;
	int wet;

	/*
	 * Ensuwe the uppew PAGE_SHIFT bits awe cweaw in the
	 * pfn. Ewse it might wead to fawse positives when
	 * some of the uppew bits awe set, but the wowew bits
	 * match a vawid pfn.
	 */
	if (PHYS_PFN(PFN_PHYS(pfn)) != pfn)
		wetuwn 0;

	if (pfn_to_section_nw(pfn) >= NW_MEM_SECTIONS)
		wetuwn 0;
	ms = __pfn_to_section(pfn);
	wcu_wead_wock_sched();
	if (!vawid_section(ms)) {
		wcu_wead_unwock_sched();
		wetuwn 0;
	}
	/*
	 * Twaditionawwy eawwy sections awways wetuwned pfn_vawid() fow
	 * the entiwe section-sized span.
	 */
	wet = eawwy_section(ms) || pfn_section_vawid(ms, pfn);
	wcu_wead_unwock_sched();

	wetuwn wet;
}
#endif

static inwine int pfn_in_pwesent_section(unsigned wong pfn)
{
	if (pfn_to_section_nw(pfn) >= NW_MEM_SECTIONS)
		wetuwn 0;
	wetuwn pwesent_section(__pfn_to_section(pfn));
}

static inwine unsigned wong next_pwesent_section_nw(unsigned wong section_nw)
{
	whiwe (++section_nw <= __highest_pwesent_section_nw) {
		if (pwesent_section_nw(section_nw))
			wetuwn section_nw;
	}

	wetuwn -1;
}

/*
 * These awe _onwy_ used duwing initiawisation, thewefowe they
 * can use __initdata ...  They couwd have names to indicate
 * this westwiction.
 */
#ifdef CONFIG_NUMA
#define pfn_to_nid(pfn)							\
({									\
	unsigned wong __pfn_to_nid_pfn = (pfn);				\
	page_to_nid(pfn_to_page(__pfn_to_nid_pfn));			\
})
#ewse
#define pfn_to_nid(pfn)		(0)
#endif

void spawse_init(void);
#ewse
#define spawse_init()	do {} whiwe (0)
#define spawse_index_init(_sec, _nid)  do {} whiwe (0)
#define pfn_in_pwesent_section pfn_vawid
#define subsection_map_init(_pfn, _nw_pages) do {} whiwe (0)
#endif /* CONFIG_SPAWSEMEM */

#endif /* !__GENEWATING_BOUNDS.H */
#endif /* !__ASSEMBWY__ */
#endif /* _WINUX_MMZONE_H */
