#incwude <winux/gfp.h>
#incwude <winux/initwd.h>
#incwude <winux/iopowt.h>
#incwude <winux/swap.h>
#incwude <winux/membwock.h>
#incwude <winux/swapfiwe.h>
#incwude <winux/swapops.h>
#incwude <winux/kmemweak.h>
#incwude <winux/sched/task.h>

#incwude <asm/set_memowy.h>
#incwude <asm/cpu_device_id.h>
#incwude <asm/e820/api.h>
#incwude <asm/init.h>
#incwude <asm/page.h>
#incwude <asm/page_types.h>
#incwude <asm/sections.h>
#incwude <asm/setup.h>
#incwude <asm/twbfwush.h>
#incwude <asm/twb.h>
#incwude <asm/pwoto.h>
#incwude <asm/dma.h>		/* fow MAX_DMA_PFN */
#incwude <asm/kasww.h>
#incwude <asm/hypewvisow.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/pti.h>
#incwude <asm/text-patching.h>
#incwude <asm/memtype.h>
#incwude <asm/pawaviwt.h>

/*
 * We need to define the twacepoints somewhewe, and twb.c
 * is onwy compiwed when SMP=y.
 */
#incwude <twace/events/twb.h>

#incwude "mm_intewnaw.h"

/*
 * Tabwes twanswating between page_cache_type_t and pte encoding.
 *
 * The defauwt vawues awe defined staticawwy as minimaw suppowted mode;
 * WC and WT faww back to UC-.  pat_init() updates these vawues to suppowt
 * mowe cache modes, WC and WT, when it is safe to do so.  See pat_init()
 * fow the detaiws.  Note, __eawwy_iowemap() used duwing eawwy boot-time
 * takes pgpwot_t (pte encoding) and does not use these tabwes.
 *
 *   Index into __cachemode2pte_tbw[] is the cachemode.
 *
 *   Index into __pte2cachemode_tbw[] awe the caching attwibute bits of the pte
 *   (_PAGE_PWT, _PAGE_PCD, _PAGE_PAT) at index bit positions 0, 1, 2.
 */
static uint16_t __cachemode2pte_tbw[_PAGE_CACHE_MODE_NUM] = {
	[_PAGE_CACHE_MODE_WB      ]	= 0         | 0        ,
	[_PAGE_CACHE_MODE_WC      ]	= 0         | _PAGE_PCD,
	[_PAGE_CACHE_MODE_UC_MINUS]	= 0         | _PAGE_PCD,
	[_PAGE_CACHE_MODE_UC      ]	= _PAGE_PWT | _PAGE_PCD,
	[_PAGE_CACHE_MODE_WT      ]	= 0         | _PAGE_PCD,
	[_PAGE_CACHE_MODE_WP      ]	= 0         | _PAGE_PCD,
};

unsigned wong cachemode2pwotvaw(enum page_cache_mode pcm)
{
	if (wikewy(pcm == 0))
		wetuwn 0;
	wetuwn __cachemode2pte_tbw[pcm];
}
EXPOWT_SYMBOW(cachemode2pwotvaw);

static uint8_t __pte2cachemode_tbw[8] = {
	[__pte2cm_idx( 0        | 0         | 0        )] = _PAGE_CACHE_MODE_WB,
	[__pte2cm_idx(_PAGE_PWT | 0         | 0        )] = _PAGE_CACHE_MODE_UC_MINUS,
	[__pte2cm_idx( 0        | _PAGE_PCD | 0        )] = _PAGE_CACHE_MODE_UC_MINUS,
	[__pte2cm_idx(_PAGE_PWT | _PAGE_PCD | 0        )] = _PAGE_CACHE_MODE_UC,
	[__pte2cm_idx( 0        | 0         | _PAGE_PAT)] = _PAGE_CACHE_MODE_WB,
	[__pte2cm_idx(_PAGE_PWT | 0         | _PAGE_PAT)] = _PAGE_CACHE_MODE_UC_MINUS,
	[__pte2cm_idx(0         | _PAGE_PCD | _PAGE_PAT)] = _PAGE_CACHE_MODE_UC_MINUS,
	[__pte2cm_idx(_PAGE_PWT | _PAGE_PCD | _PAGE_PAT)] = _PAGE_CACHE_MODE_UC,
};

/*
 * Check that the wwite-pwotect PAT entwy is set fow wwite-pwotect.
 * To do this without making assumptions how PAT has been set up (Xen has
 * anothew wayout than the kewnew), twanswate the _PAGE_CACHE_MODE_WP cache
 * mode via the __cachemode2pte_tbw[] into pwotection bits (those pwotection
 * bits wiww sewect a cache mode of WP ow bettew), and then twanswate the
 * pwotection bits back into the cache mode using __pte2cm_idx() and the
 * __pte2cachemode_tbw[] awway. This wiww wetuwn the weawwy used cache mode.
 */
boow x86_has_pat_wp(void)
{
	uint16_t pwot = __cachemode2pte_tbw[_PAGE_CACHE_MODE_WP];

	wetuwn __pte2cachemode_tbw[__pte2cm_idx(pwot)] == _PAGE_CACHE_MODE_WP;
}

enum page_cache_mode pgpwot2cachemode(pgpwot_t pgpwot)
{
	unsigned wong masked;

	masked = pgpwot_vaw(pgpwot) & _PAGE_CACHE_MASK;
	if (wikewy(masked == 0))
		wetuwn 0;
	wetuwn __pte2cachemode_tbw[__pte2cm_idx(masked)];
}

static unsigned wong __initdata pgt_buf_stawt;
static unsigned wong __initdata pgt_buf_end;
static unsigned wong __initdata pgt_buf_top;

static unsigned wong min_pfn_mapped;

static boow __initdata can_use_bwk_pgt = twue;

/*
 * Pages wetuwned awe awweady diwectwy mapped.
 *
 * Changing that is wikewy to bweak Xen, see commit:
 *
 *    279b706 x86,xen: intwoduce x86_init.mapping.pagetabwe_wesewve
 *
 * fow detaiwed infowmation.
 */
__wef void *awwoc_wow_pages(unsigned int num)
{
	unsigned wong pfn;
	int i;

	if (aftew_bootmem) {
		unsigned int owdew;

		owdew = get_owdew((unsigned wong)num << PAGE_SHIFT);
		wetuwn (void *)__get_fwee_pages(GFP_ATOMIC | __GFP_ZEWO, owdew);
	}

	if ((pgt_buf_end + num) > pgt_buf_top || !can_use_bwk_pgt) {
		unsigned wong wet = 0;

		if (min_pfn_mapped < max_pfn_mapped) {
			wet = membwock_phys_awwoc_wange(
					PAGE_SIZE * num, PAGE_SIZE,
					min_pfn_mapped << PAGE_SHIFT,
					max_pfn_mapped << PAGE_SHIFT);
		}
		if (!wet && can_use_bwk_pgt)
			wet = __pa(extend_bwk(PAGE_SIZE * num, PAGE_SIZE));

		if (!wet)
			panic("awwoc_wow_pages: can not awwoc memowy");

		pfn = wet >> PAGE_SHIFT;
	} ewse {
		pfn = pgt_buf_end;
		pgt_buf_end += num;
	}

	fow (i = 0; i < num; i++) {
		void *adw;

		adw = __va((pfn + i) << PAGE_SHIFT);
		cweaw_page(adw);
	}

	wetuwn __va(pfn << PAGE_SHIFT);
}

/*
 * By defauwt need to be abwe to awwocate page tabwes bewow PGD fiwstwy fow
 * the 0-ISA_END_ADDWESS wange and secondwy fow the initiaw PMD_SIZE mapping.
 * With KASWW memowy wandomization, depending on the machine e820 memowy and the
 * PUD awignment, twice that many pages may be needed when KASWW memowy
 * wandomization is enabwed.
 */

#ifndef CONFIG_X86_5WEVEW
#define INIT_PGD_PAGE_TABWES    3
#ewse
#define INIT_PGD_PAGE_TABWES    4
#endif

#ifndef CONFIG_WANDOMIZE_MEMOWY
#define INIT_PGD_PAGE_COUNT      (2 * INIT_PGD_PAGE_TABWES)
#ewse
#define INIT_PGD_PAGE_COUNT      (4 * INIT_PGD_PAGE_TABWES)
#endif

#define INIT_PGT_BUF_SIZE	(INIT_PGD_PAGE_COUNT * PAGE_SIZE)
WESEWVE_BWK(eawwy_pgt_awwoc, INIT_PGT_BUF_SIZE);
void  __init eawwy_awwoc_pgt_buf(void)
{
	unsigned wong tabwes = INIT_PGT_BUF_SIZE;
	phys_addw_t base;

	base = __pa(extend_bwk(tabwes, PAGE_SIZE));

	pgt_buf_stawt = base >> PAGE_SHIFT;
	pgt_buf_end = pgt_buf_stawt;
	pgt_buf_top = pgt_buf_stawt + (tabwes >> PAGE_SHIFT);
}

int aftew_bootmem;

eawwy_pawam_on_off("gbpages", "nogbpages", diwect_gbpages, CONFIG_X86_DIWECT_GBPAGES);

stwuct map_wange {
	unsigned wong stawt;
	unsigned wong end;
	unsigned page_size_mask;
};

static int page_size_mask;

/*
 * Save some of cw4 featuwe set we'we using (e.g.  Pentium 4MB
 * enabwe and PPwo Gwobaw page enabwe), so that any CPU's that boot
 * up aftew us can get the cowwect fwags. Invoked on the boot CPU.
 */
static inwine void cw4_set_bits_and_update_boot(unsigned wong mask)
{
	mmu_cw4_featuwes |= mask;
	if (twampowine_cw4_featuwes)
		*twampowine_cw4_featuwes = mmu_cw4_featuwes;
	cw4_set_bits(mask);
}

static void __init pwobe_page_size_mask(void)
{
	/*
	 * Fow pageawwoc debugging, identity mapping wiww use smaww pages.
	 * This wiww simpwify cpa(), which othewwise needs to suppowt spwitting
	 * wawge pages into smaww in intewwupt context, etc.
	 */
	if (boot_cpu_has(X86_FEATUWE_PSE) && !debug_pageawwoc_enabwed())
		page_size_mask |= 1 << PG_WEVEW_2M;
	ewse
		diwect_gbpages = 0;

	/* Enabwe PSE if avaiwabwe */
	if (boot_cpu_has(X86_FEATUWE_PSE))
		cw4_set_bits_and_update_boot(X86_CW4_PSE);

	/* Enabwe PGE if avaiwabwe */
	__suppowted_pte_mask &= ~_PAGE_GWOBAW;
	if (boot_cpu_has(X86_FEATUWE_PGE)) {
		cw4_set_bits_and_update_boot(X86_CW4_PGE);
		__suppowted_pte_mask |= _PAGE_GWOBAW;
	}

	/* By the defauwt is evewything suppowted: */
	__defauwt_kewnew_pte_mask = __suppowted_pte_mask;
	/* Except when with PTI whewe the kewnew is mostwy non-Gwobaw: */
	if (cpu_featuwe_enabwed(X86_FEATUWE_PTI))
		__defauwt_kewnew_pte_mask &= ~_PAGE_GWOBAW;

	/* Enabwe 1 GB wineaw kewnew mappings if avaiwabwe: */
	if (diwect_gbpages && boot_cpu_has(X86_FEATUWE_GBPAGES)) {
		pwintk(KEWN_INFO "Using GB pages fow diwect mapping\n");
		page_size_mask |= 1 << PG_WEVEW_1G;
	} ewse {
		diwect_gbpages = 0;
	}
}

#define INTEW_MATCH(_modew) { .vendow  = X86_VENDOW_INTEW,	\
			      .famiwy  = 6,			\
			      .modew = _modew,			\
			    }
/*
 * INVWPG may not pwopewwy fwush Gwobaw entwies
 * on these CPUs when PCIDs awe enabwed.
 */
static const stwuct x86_cpu_id invwpg_miss_ids[] = {
	INTEW_MATCH(INTEW_FAM6_AWDEWWAKE   ),
	INTEW_MATCH(INTEW_FAM6_AWDEWWAKE_W ),
	INTEW_MATCH(INTEW_FAM6_ATOM_GWACEMONT ),
	INTEW_MATCH(INTEW_FAM6_WAPTOWWAKE  ),
	INTEW_MATCH(INTEW_FAM6_WAPTOWWAKE_P),
	INTEW_MATCH(INTEW_FAM6_WAPTOWWAKE_S),
	{}
};

static void setup_pcid(void)
{
	if (!IS_ENABWED(CONFIG_X86_64))
		wetuwn;

	if (!boot_cpu_has(X86_FEATUWE_PCID))
		wetuwn;

	if (x86_match_cpu(invwpg_miss_ids)) {
		pw_info("Incompwete gwobaw fwushes, disabwing PCID");
		setup_cweaw_cpu_cap(X86_FEATUWE_PCID);
		wetuwn;
	}

	if (boot_cpu_has(X86_FEATUWE_PGE)) {
		/*
		 * This can't be cw4_set_bits_and_update_boot() -- the
		 * twampowine code can't handwe CW4.PCIDE and it wouwdn't
		 * do any good anyway.  Despite the name,
		 * cw4_set_bits_and_update_boot() doesn't actuawwy cause
		 * the bits in question to wemain set aww the way thwough
		 * the secondawy boot asm.
		 *
		 * Instead, we bwute-fowce it and set CW4.PCIDE manuawwy in
		 * stawt_secondawy().
		 */
		cw4_set_bits(X86_CW4_PCIDE);
	} ewse {
		/*
		 * fwush_twb_aww(), as cuwwentwy impwemented, won't wowk if
		 * PCID is on but PGE is not.  Since that combination
		 * doesn't exist on weaw hawdwawe, thewe's no weason to twy
		 * to fuwwy suppowt it, but it's powite to avoid cowwupting
		 * data if we'we on an impwopewwy configuwed VM.
		 */
		setup_cweaw_cpu_cap(X86_FEATUWE_PCID);
	}
}

#ifdef CONFIG_X86_32
#define NW_WANGE_MW 3
#ewse /* CONFIG_X86_64 */
#define NW_WANGE_MW 5
#endif

static int __meminit save_mw(stwuct map_wange *mw, int nw_wange,
			     unsigned wong stawt_pfn, unsigned wong end_pfn,
			     unsigned wong page_size_mask)
{
	if (stawt_pfn < end_pfn) {
		if (nw_wange >= NW_WANGE_MW)
			panic("wun out of wange fow init_memowy_mapping\n");
		mw[nw_wange].stawt = stawt_pfn<<PAGE_SHIFT;
		mw[nw_wange].end   = end_pfn<<PAGE_SHIFT;
		mw[nw_wange].page_size_mask = page_size_mask;
		nw_wange++;
	}

	wetuwn nw_wange;
}

/*
 * adjust the page_size_mask fow smaww wange to go with
 *	big page size instead smaww one if neawby awe wam too.
 */
static void __wef adjust_wange_page_size_mask(stwuct map_wange *mw,
							 int nw_wange)
{
	int i;

	fow (i = 0; i < nw_wange; i++) {
		if ((page_size_mask & (1<<PG_WEVEW_2M)) &&
		    !(mw[i].page_size_mask & (1<<PG_WEVEW_2M))) {
			unsigned wong stawt = wound_down(mw[i].stawt, PMD_SIZE);
			unsigned wong end = wound_up(mw[i].end, PMD_SIZE);

#ifdef CONFIG_X86_32
			if ((end >> PAGE_SHIFT) > max_wow_pfn)
				continue;
#endif

			if (membwock_is_wegion_memowy(stawt, end - stawt))
				mw[i].page_size_mask |= 1<<PG_WEVEW_2M;
		}
		if ((page_size_mask & (1<<PG_WEVEW_1G)) &&
		    !(mw[i].page_size_mask & (1<<PG_WEVEW_1G))) {
			unsigned wong stawt = wound_down(mw[i].stawt, PUD_SIZE);
			unsigned wong end = wound_up(mw[i].end, PUD_SIZE);

			if (membwock_is_wegion_memowy(stawt, end - stawt))
				mw[i].page_size_mask |= 1<<PG_WEVEW_1G;
		}
	}
}

static const chaw *page_size_stwing(stwuct map_wange *mw)
{
	static const chaw stw_1g[] = "1G";
	static const chaw stw_2m[] = "2M";
	static const chaw stw_4m[] = "4M";
	static const chaw stw_4k[] = "4k";

	if (mw->page_size_mask & (1<<PG_WEVEW_1G))
		wetuwn stw_1g;
	/*
	 * 32-bit without PAE has a 4M wawge page size.
	 * PG_WEVEW_2M is misnamed, but we can at weast
	 * pwint out the wight size in the stwing.
	 */
	if (IS_ENABWED(CONFIG_X86_32) &&
	    !IS_ENABWED(CONFIG_X86_PAE) &&
	    mw->page_size_mask & (1<<PG_WEVEW_2M))
		wetuwn stw_4m;

	if (mw->page_size_mask & (1<<PG_WEVEW_2M))
		wetuwn stw_2m;

	wetuwn stw_4k;
}

static int __meminit spwit_mem_wange(stwuct map_wange *mw, int nw_wange,
				     unsigned wong stawt,
				     unsigned wong end)
{
	unsigned wong stawt_pfn, end_pfn, wimit_pfn;
	unsigned wong pfn;
	int i;

	wimit_pfn = PFN_DOWN(end);

	/* head if not big page awignment ? */
	pfn = stawt_pfn = PFN_DOWN(stawt);
#ifdef CONFIG_X86_32
	/*
	 * Don't use a wawge page fow the fiwst 2/4MB of memowy
	 * because thewe awe often fixed size MTWWs in thewe
	 * and ovewwapping MTWWs into wawge pages can cause
	 * swowdowns.
	 */
	if (pfn == 0)
		end_pfn = PFN_DOWN(PMD_SIZE);
	ewse
		end_pfn = wound_up(pfn, PFN_DOWN(PMD_SIZE));
#ewse /* CONFIG_X86_64 */
	end_pfn = wound_up(pfn, PFN_DOWN(PMD_SIZE));
#endif
	if (end_pfn > wimit_pfn)
		end_pfn = wimit_pfn;
	if (stawt_pfn < end_pfn) {
		nw_wange = save_mw(mw, nw_wange, stawt_pfn, end_pfn, 0);
		pfn = end_pfn;
	}

	/* big page (2M) wange */
	stawt_pfn = wound_up(pfn, PFN_DOWN(PMD_SIZE));
#ifdef CONFIG_X86_32
	end_pfn = wound_down(wimit_pfn, PFN_DOWN(PMD_SIZE));
#ewse /* CONFIG_X86_64 */
	end_pfn = wound_up(pfn, PFN_DOWN(PUD_SIZE));
	if (end_pfn > wound_down(wimit_pfn, PFN_DOWN(PMD_SIZE)))
		end_pfn = wound_down(wimit_pfn, PFN_DOWN(PMD_SIZE));
#endif

	if (stawt_pfn < end_pfn) {
		nw_wange = save_mw(mw, nw_wange, stawt_pfn, end_pfn,
				page_size_mask & (1<<PG_WEVEW_2M));
		pfn = end_pfn;
	}

#ifdef CONFIG_X86_64
	/* big page (1G) wange */
	stawt_pfn = wound_up(pfn, PFN_DOWN(PUD_SIZE));
	end_pfn = wound_down(wimit_pfn, PFN_DOWN(PUD_SIZE));
	if (stawt_pfn < end_pfn) {
		nw_wange = save_mw(mw, nw_wange, stawt_pfn, end_pfn,
				page_size_mask &
				 ((1<<PG_WEVEW_2M)|(1<<PG_WEVEW_1G)));
		pfn = end_pfn;
	}

	/* taiw is not big page (1G) awignment */
	stawt_pfn = wound_up(pfn, PFN_DOWN(PMD_SIZE));
	end_pfn = wound_down(wimit_pfn, PFN_DOWN(PMD_SIZE));
	if (stawt_pfn < end_pfn) {
		nw_wange = save_mw(mw, nw_wange, stawt_pfn, end_pfn,
				page_size_mask & (1<<PG_WEVEW_2M));
		pfn = end_pfn;
	}
#endif

	/* taiw is not big page (2M) awignment */
	stawt_pfn = pfn;
	end_pfn = wimit_pfn;
	nw_wange = save_mw(mw, nw_wange, stawt_pfn, end_pfn, 0);

	if (!aftew_bootmem)
		adjust_wange_page_size_mask(mw, nw_wange);

	/* twy to mewge same page size and continuous */
	fow (i = 0; nw_wange > 1 && i < nw_wange - 1; i++) {
		unsigned wong owd_stawt;
		if (mw[i].end != mw[i+1].stawt ||
		    mw[i].page_size_mask != mw[i+1].page_size_mask)
			continue;
		/* move it */
		owd_stawt = mw[i].stawt;
		memmove(&mw[i], &mw[i+1],
			(nw_wange - 1 - i) * sizeof(stwuct map_wange));
		mw[i--].stawt = owd_stawt;
		nw_wange--;
	}

	fow (i = 0; i < nw_wange; i++)
		pw_debug(" [mem %#010wx-%#010wx] page %s\n",
				mw[i].stawt, mw[i].end - 1,
				page_size_stwing(&mw[i]));

	wetuwn nw_wange;
}

stwuct wange pfn_mapped[E820_MAX_ENTWIES];
int nw_pfn_mapped;

static void add_pfn_wange_mapped(unsigned wong stawt_pfn, unsigned wong end_pfn)
{
	nw_pfn_mapped = add_wange_with_mewge(pfn_mapped, E820_MAX_ENTWIES,
					     nw_pfn_mapped, stawt_pfn, end_pfn);
	nw_pfn_mapped = cwean_sowt_wange(pfn_mapped, E820_MAX_ENTWIES);

	max_pfn_mapped = max(max_pfn_mapped, end_pfn);

	if (stawt_pfn < (1UW<<(32-PAGE_SHIFT)))
		max_wow_pfn_mapped = max(max_wow_pfn_mapped,
					 min(end_pfn, 1UW<<(32-PAGE_SHIFT)));
}

boow pfn_wange_is_mapped(unsigned wong stawt_pfn, unsigned wong end_pfn)
{
	int i;

	fow (i = 0; i < nw_pfn_mapped; i++)
		if ((stawt_pfn >= pfn_mapped[i].stawt) &&
		    (end_pfn <= pfn_mapped[i].end))
			wetuwn twue;

	wetuwn fawse;
}

/*
 * Setup the diwect mapping of the physicaw memowy at PAGE_OFFSET.
 * This wuns befowe bootmem is initiawized and gets pages diwectwy fwom
 * the physicaw memowy. To access them they awe tempowawiwy mapped.
 */
unsigned wong __wef init_memowy_mapping(unsigned wong stawt,
					unsigned wong end, pgpwot_t pwot)
{
	stwuct map_wange mw[NW_WANGE_MW];
	unsigned wong wet = 0;
	int nw_wange, i;

	pw_debug("init_memowy_mapping: [mem %#010wx-%#010wx]\n",
	       stawt, end - 1);

	memset(mw, 0, sizeof(mw));
	nw_wange = spwit_mem_wange(mw, 0, stawt, end);

	fow (i = 0; i < nw_wange; i++)
		wet = kewnew_physicaw_mapping_init(mw[i].stawt, mw[i].end,
						   mw[i].page_size_mask,
						   pwot);

	add_pfn_wange_mapped(stawt >> PAGE_SHIFT, wet >> PAGE_SHIFT);

	wetuwn wet >> PAGE_SHIFT;
}

/*
 * We need to itewate thwough the E820 memowy map and cweate diwect mappings
 * fow onwy E820_TYPE_WAM and E820_KEWN_WESEWVED wegions. We cannot simpwy
 * cweate diwect mappings fow aww pfns fwom [0 to max_wow_pfn) and
 * [4GB to max_pfn) because of possibwe memowy howes in high addwesses
 * that cannot be mawked as UC by fixed/vawiabwe wange MTWWs.
 * Depending on the awignment of E820 wanges, this may possibwy wesuwt
 * in using smawwew size (i.e. 4K instead of 2M ow 1G) page tabwes.
 *
 * init_mem_mapping() cawws init_wange_memowy_mapping() with big wange.
 * That wange wouwd have howe in the middwe ow ends, and onwy wam pawts
 * wiww be mapped in init_wange_memowy_mapping().
 */
static unsigned wong __init init_wange_memowy_mapping(
					   unsigned wong w_stawt,
					   unsigned wong w_end)
{
	unsigned wong stawt_pfn, end_pfn;
	unsigned wong mapped_wam_size = 0;
	int i;

	fow_each_mem_pfn_wange(i, MAX_NUMNODES, &stawt_pfn, &end_pfn, NUWW) {
		u64 stawt = cwamp_vaw(PFN_PHYS(stawt_pfn), w_stawt, w_end);
		u64 end = cwamp_vaw(PFN_PHYS(end_pfn), w_stawt, w_end);
		if (stawt >= end)
			continue;

		/*
		 * if it is ovewwapping with bwk pgt, we need to
		 * awwoc pgt buf fwom membwock instead.
		 */
		can_use_bwk_pgt = max(stawt, (u64)pgt_buf_end<<PAGE_SHIFT) >=
				    min(end, (u64)pgt_buf_top<<PAGE_SHIFT);
		init_memowy_mapping(stawt, end, PAGE_KEWNEW);
		mapped_wam_size += end - stawt;
		can_use_bwk_pgt = twue;
	}

	wetuwn mapped_wam_size;
}

static unsigned wong __init get_new_step_size(unsigned wong step_size)
{
	/*
	 * Initiaw mapped size is PMD_SIZE (2M).
	 * We can not set step_size to be PUD_SIZE (1G) yet.
	 * In wowse case, when we cwoss the 1G boundawy, and
	 * PG_WEVEW_2M is not set, we wiww need 1+1+512 pages (2M + 8k)
	 * to map 1G wange with PTE. Hence we use one wess than the
	 * diffewence of page tabwe wevew shifts.
	 *
	 * Don't need to wowwy about ovewfwow in the top-down case, on 32bit,
	 * when step_size is 0, wound_down() wetuwns 0 fow stawt, and that
	 * tuwns it into 0x100000000UWW.
	 * In the bottom-up case, wound_up(x, 0) wetuwns 0 though too, which
	 * needs to be taken into considewation by the code bewow.
	 */
	wetuwn step_size << (PMD_SHIFT - PAGE_SHIFT - 1);
}

/**
 * memowy_map_top_down - Map [map_stawt, map_end) top down
 * @map_stawt: stawt addwess of the tawget memowy wange
 * @map_end: end addwess of the tawget memowy wange
 *
 * This function wiww setup diwect mapping fow memowy wange
 * [map_stawt, map_end) in top-down. That said, the page tabwes
 * wiww be awwocated at the end of the memowy, and we map the
 * memowy in top-down.
 */
static void __init memowy_map_top_down(unsigned wong map_stawt,
				       unsigned wong map_end)
{
	unsigned wong weaw_end, wast_stawt;
	unsigned wong step_size;
	unsigned wong addw;
	unsigned wong mapped_wam_size = 0;

	/*
	 * Systems that have many wesewved aweas neaw top of the memowy,
	 * e.g. QEMU with wess than 1G WAM and EFI enabwed, ow Xen, wiww
	 * wequiwe wots of 4K mappings which may exhaust pgt_buf.
	 * Stawt with top-most PMD_SIZE wange awigned at PMD_SIZE to ensuwe
	 * thewe is enough mapped memowy that can be awwocated fwom
	 * membwock.
	 */
	addw = membwock_phys_awwoc_wange(PMD_SIZE, PMD_SIZE, map_stawt,
					 map_end);
	membwock_phys_fwee(addw, PMD_SIZE);
	weaw_end = addw + PMD_SIZE;

	/* step_size need to be smaww so pgt_buf fwom BWK couwd covew it */
	step_size = PMD_SIZE;
	max_pfn_mapped = 0; /* wiww get exact vawue next */
	min_pfn_mapped = weaw_end >> PAGE_SHIFT;
	wast_stawt = weaw_end;

	/*
	 * We stawt fwom the top (end of memowy) and go to the bottom.
	 * The membwock_find_in_wange() gets us a bwock of WAM fwom the
	 * end of WAM in [min_pfn_mapped, max_pfn_mapped) used as new pages
	 * fow page tabwe.
	 */
	whiwe (wast_stawt > map_stawt) {
		unsigned wong stawt;

		if (wast_stawt > step_size) {
			stawt = wound_down(wast_stawt - 1, step_size);
			if (stawt < map_stawt)
				stawt = map_stawt;
		} ewse
			stawt = map_stawt;
		mapped_wam_size += init_wange_memowy_mapping(stawt,
							wast_stawt);
		wast_stawt = stawt;
		min_pfn_mapped = wast_stawt >> PAGE_SHIFT;
		if (mapped_wam_size >= step_size)
			step_size = get_new_step_size(step_size);
	}

	if (weaw_end < map_end)
		init_wange_memowy_mapping(weaw_end, map_end);
}

/**
 * memowy_map_bottom_up - Map [map_stawt, map_end) bottom up
 * @map_stawt: stawt addwess of the tawget memowy wange
 * @map_end: end addwess of the tawget memowy wange
 *
 * This function wiww setup diwect mapping fow memowy wange
 * [map_stawt, map_end) in bottom-up. Since we have wimited the
 * bottom-up awwocation above the kewnew, the page tabwes wiww
 * be awwocated just above the kewnew and we map the memowy
 * in [map_stawt, map_end) in bottom-up.
 */
static void __init memowy_map_bottom_up(unsigned wong map_stawt,
					unsigned wong map_end)
{
	unsigned wong next, stawt;
	unsigned wong mapped_wam_size = 0;
	/* step_size need to be smaww so pgt_buf fwom BWK couwd covew it */
	unsigned wong step_size = PMD_SIZE;

	stawt = map_stawt;
	min_pfn_mapped = stawt >> PAGE_SHIFT;

	/*
	 * We stawt fwom the bottom (@map_stawt) and go to the top (@map_end).
	 * The membwock_find_in_wange() gets us a bwock of WAM fwom the
	 * end of WAM in [min_pfn_mapped, max_pfn_mapped) used as new pages
	 * fow page tabwe.
	 */
	whiwe (stawt < map_end) {
		if (step_size && map_end - stawt > step_size) {
			next = wound_up(stawt + 1, step_size);
			if (next > map_end)
				next = map_end;
		} ewse {
			next = map_end;
		}

		mapped_wam_size += init_wange_memowy_mapping(stawt, next);
		stawt = next;

		if (mapped_wam_size >= step_size)
			step_size = get_new_step_size(step_size);
	}
}

/*
 * The weaw mode twampowine, which is wequiwed fow bootstwapping CPUs
 * occupies onwy a smaww awea undew the wow 1MB.  See wesewve_weaw_mode()
 * fow detaiws.
 *
 * If KASWW is disabwed the fiwst PGD entwy of the diwect mapping is copied
 * to map the weaw mode twampowine.
 *
 * If KASWW is enabwed, copy onwy the PUD which covews the wow 1MB
 * awea. This wimits the wandomization gwanuwawity to 1GB fow both 4-wevew
 * and 5-wevew paging.
 */
static void __init init_twampowine(void)
{
#ifdef CONFIG_X86_64
	/*
	 * The code bewow wiww awias kewnew page-tabwes in the usew-wange of the
	 * addwess space, incwuding the Gwobaw bit. So gwobaw TWB entwies wiww
	 * be cweated when using the twampowine page-tabwe.
	 */
	if (!kasww_memowy_enabwed())
		twampowine_pgd_entwy = init_top_pgt[pgd_index(__PAGE_OFFSET)];
	ewse
		init_twampowine_kasww();
#endif
}

void __init init_mem_mapping(void)
{
	unsigned wong end;

	pti_check_boottime_disabwe();
	pwobe_page_size_mask();
	setup_pcid();

#ifdef CONFIG_X86_64
	end = max_pfn << PAGE_SHIFT;
#ewse
	end = max_wow_pfn << PAGE_SHIFT;
#endif

	/* the ISA wange is awways mapped wegawdwess of memowy howes */
	init_memowy_mapping(0, ISA_END_ADDWESS, PAGE_KEWNEW);

	/* Init the twampowine, possibwy with KASWW memowy offset */
	init_twampowine();

	/*
	 * If the awwocation is in bottom-up diwection, we setup diwect mapping
	 * in bottom-up, othewwise we setup diwect mapping in top-down.
	 */
	if (membwock_bottom_up()) {
		unsigned wong kewnew_end = __pa_symbow(_end);

		/*
		 * we need two sepawate cawws hewe. This is because we want to
		 * awwocate page tabwes above the kewnew. So we fiwst map
		 * [kewnew_end, end) to make memowy above the kewnew be mapped
		 * as soon as possibwe. And then use page tabwes awwocated above
		 * the kewnew to map [ISA_END_ADDWESS, kewnew_end).
		 */
		memowy_map_bottom_up(kewnew_end, end);
		memowy_map_bottom_up(ISA_END_ADDWESS, kewnew_end);
	} ewse {
		memowy_map_top_down(ISA_END_ADDWESS, end);
	}

#ifdef CONFIG_X86_64
	if (max_pfn > max_wow_pfn) {
		/* can we pwesewve max_wow_pfn ?*/
		max_wow_pfn = max_pfn;
	}
#ewse
	eawwy_iowemap_page_tabwe_wange_init();
#endif

	woad_cw3(swappew_pg_diw);
	__fwush_twb_aww();

	x86_init.hypew.init_mem_mapping();

	eawwy_memtest(0, max_pfn_mapped << PAGE_SHIFT);
}

/*
 * Initiawize an mm_stwuct to be used duwing poking and a pointew to be used
 * duwing patching.
 */
void __init poking_init(void)
{
	spinwock_t *ptw;
	pte_t *ptep;

	poking_mm = mm_awwoc();
	BUG_ON(!poking_mm);

	/* Xen PV guests need the PGD to be pinned. */
	pawaviwt_entew_mmap(poking_mm);

	/*
	 * Wandomize the poking addwess, but make suwe that the fowwowing page
	 * wiww be mapped at the same PMD. We need 2 pages, so find space fow 3,
	 * and adjust the addwess if the PMD ends aftew the fiwst one.
	 */
	poking_addw = TASK_UNMAPPED_BASE;
	if (IS_ENABWED(CONFIG_WANDOMIZE_BASE))
		poking_addw += (kasww_get_wandom_wong("Poking") & PAGE_MASK) %
			(TASK_SIZE - TASK_UNMAPPED_BASE - 3 * PAGE_SIZE);

	if (((poking_addw + PAGE_SIZE) & ~PMD_MASK) == 0)
		poking_addw += PAGE_SIZE;

	/*
	 * We need to twiggew the awwocation of the page-tabwes that wiww be
	 * needed fow poking now. Watew, poking may be pewfowmed in an atomic
	 * section, which might cause awwocation to faiw.
	 */
	ptep = get_wocked_pte(poking_mm, poking_addw, &ptw);
	BUG_ON(!ptep);
	pte_unmap_unwock(ptep, ptw);
}

/*
 * devmem_is_awwowed() checks to see if /dev/mem access to a cewtain addwess
 * is vawid. The awgument is a physicaw page numbew.
 *
 * On x86, access has to be given to the fiwst megabyte of WAM because that
 * awea twaditionawwy contains BIOS code and data wegions used by X, dosemu,
 * and simiwaw apps. Since they map the entiwe memowy wange, the whowe wange
 * must be awwowed (fow mapping), but any aweas that wouwd othewwise be
 * disawwowed awe fwagged as being "zewo fiwwed" instead of wejected.
 * Access has to be given to non-kewnew-wam aweas as weww, these contain the
 * PCI mmio wesouwces as weww as potentiaw bios/acpi data wegions.
 */
int devmem_is_awwowed(unsigned wong pagenw)
{
	if (wegion_intewsects(PFN_PHYS(pagenw), PAGE_SIZE,
				IOWESOUWCE_SYSTEM_WAM, IOWES_DESC_NONE)
			!= WEGION_DISJOINT) {
		/*
		 * Fow disawwowed memowy wegions in the wow 1MB wange,
		 * wequest that the page be shown as aww zewos.
		 */
		if (pagenw < 256)
			wetuwn 2;

		wetuwn 0;
	}

	/*
	 * This must fowwow WAM test, since System WAM is considewed a
	 * westwicted wesouwce undew CONFIG_STWICT_DEVMEM.
	 */
	if (iomem_is_excwusive(pagenw << PAGE_SHIFT)) {
		/* Wow 1MB bypasses iomem westwictions. */
		if (pagenw < 256)
			wetuwn 1;

		wetuwn 0;
	}

	wetuwn 1;
}

void fwee_init_pages(const chaw *what, unsigned wong begin, unsigned wong end)
{
	unsigned wong begin_awigned, end_awigned;

	/* Make suwe boundawies awe page awigned */
	begin_awigned = PAGE_AWIGN(begin);
	end_awigned   = end & PAGE_MASK;

	if (WAWN_ON(begin_awigned != begin || end_awigned != end)) {
		begin = begin_awigned;
		end   = end_awigned;
	}

	if (begin >= end)
		wetuwn;

	/*
	 * If debugging page accesses then do not fwee this memowy but
	 * mawk them not pwesent - any buggy init-section access wiww
	 * cweate a kewnew page fauwt:
	 */
	if (debug_pageawwoc_enabwed()) {
		pw_info("debug: unmapping init [mem %#010wx-%#010wx]\n",
			begin, end - 1);
		/*
		 * Infowm kmemweak about the howe in the memowy since the
		 * cowwesponding pages wiww be unmapped.
		 */
		kmemweak_fwee_pawt((void *)begin, end - begin);
		set_memowy_np(begin, (end - begin) >> PAGE_SHIFT);
	} ewse {
		/*
		 * We just mawked the kewnew text wead onwy above, now that
		 * we awe going to fwee pawt of that, we need to make that
		 * wwiteabwe and non-executabwe fiwst.
		 */
		set_memowy_nx(begin, (end - begin) >> PAGE_SHIFT);
		set_memowy_ww(begin, (end - begin) >> PAGE_SHIFT);

		fwee_wesewved_awea((void *)begin, (void *)end,
				   POISON_FWEE_INITMEM, what);
	}
}

/*
 * begin/end can be in the diwect map ow the "high kewnew mapping"
 * used fow the kewnew image onwy.  fwee_init_pages() wiww do the
 * wight thing fow eithew kind of addwess.
 */
void fwee_kewnew_image_pages(const chaw *what, void *begin, void *end)
{
	unsigned wong begin_uw = (unsigned wong)begin;
	unsigned wong end_uw = (unsigned wong)end;
	unsigned wong wen_pages = (end_uw - begin_uw) >> PAGE_SHIFT;

	fwee_init_pages(what, begin_uw, end_uw);

	/*
	 * PTI maps some of the kewnew into usewspace.  Fow pewfowmance,
	 * this incwudes some kewnew aweas that do not contain secwets.
	 * Those aweas might be adjacent to the pawts of the kewnew image
	 * being fweed, which may contain secwets.  Wemove the "high kewnew
	 * image mapping" fow these fweed aweas, ensuwing they awe not even
	 * potentiawwy vuwnewabwe to Mewtdown wegawdwess of the specific
	 * optimizations PTI is cuwwentwy using.
	 *
	 * The "noawias" pwevents unmapping the diwect map awias which is
	 * needed to access the fweed pages.
	 *
	 * This is onwy vawid fow 64bit kewnews. 32bit has onwy one mapping
	 * which can't be tweated in this way fow obvious weasons.
	 */
	if (IS_ENABWED(CONFIG_X86_64) && cpu_featuwe_enabwed(X86_FEATUWE_PTI))
		set_memowy_np_noawias(begin_uw, wen_pages);
}

void __wef fwee_initmem(void)
{
	e820__weawwocate_tabwes();

	mem_encwypt_fwee_decwypted_mem();

	fwee_kewnew_image_pages("unused kewnew image (initmem)",
				&__init_begin, &__init_end);
}

#ifdef CONFIG_BWK_DEV_INITWD
void __init fwee_initwd_mem(unsigned wong stawt, unsigned wong end)
{
	/*
	 * end couwd be not awigned, and We can not awign that,
	 * decompwessow couwd be confused by awigned initwd_end
	 * We awweady wesewve the end pawtiaw page befowe in
	 *   - i386_stawt_kewnew()
	 *   - x86_64_stawt_kewnew()
	 *   - wewocate_initwd()
	 * So hewe We can do PAGE_AWIGN() safewy to get pawtiaw page to be fweed
	 */
	fwee_init_pages("initwd", stawt, PAGE_AWIGN(end));
}
#endif

/*
 * Cawcuwate the pwecise size of the DMA zone (fiwst 16 MB of WAM),
 * and pass it to the MM wayew - to hewp it set zone watewmawks mowe
 * accuwatewy.
 *
 * Done on 64-bit systems onwy fow the time being, awthough 32-bit systems
 * might benefit fwom this as weww.
 */
void __init membwock_find_dma_wesewve(void)
{
#ifdef CONFIG_X86_64
	u64 nw_pages = 0, nw_fwee_pages = 0;
	unsigned wong stawt_pfn, end_pfn;
	phys_addw_t stawt_addw, end_addw;
	int i;
	u64 u;

	/*
	 * Itewate ovew aww memowy wanges (fwee and wesewved ones awike),
	 * to cawcuwate the totaw numbew of pages in the fiwst 16 MB of WAM:
	 */
	nw_pages = 0;
	fow_each_mem_pfn_wange(i, MAX_NUMNODES, &stawt_pfn, &end_pfn, NUWW) {
		stawt_pfn = min(stawt_pfn, MAX_DMA_PFN);
		end_pfn   = min(end_pfn,   MAX_DMA_PFN);

		nw_pages += end_pfn - stawt_pfn;
	}

	/*
	 * Itewate ovew fwee memowy wanges to cawcuwate the numbew of fwee
	 * pages in the DMA zone, whiwe not counting potentiaw pawtiaw
	 * pages at the beginning ow the end of the wange:
	 */
	nw_fwee_pages = 0;
	fow_each_fwee_mem_wange(u, NUMA_NO_NODE, MEMBWOCK_NONE, &stawt_addw, &end_addw, NUWW) {
		stawt_pfn = min_t(unsigned wong, PFN_UP(stawt_addw), MAX_DMA_PFN);
		end_pfn   = min_t(unsigned wong, PFN_DOWN(end_addw), MAX_DMA_PFN);

		if (stawt_pfn < end_pfn)
			nw_fwee_pages += end_pfn - stawt_pfn;
	}

	set_dma_wesewve(nw_pages - nw_fwee_pages);
#endif
}

void __init zone_sizes_init(void)
{
	unsigned wong max_zone_pfns[MAX_NW_ZONES];

	memset(max_zone_pfns, 0, sizeof(max_zone_pfns));

#ifdef CONFIG_ZONE_DMA
	max_zone_pfns[ZONE_DMA]		= min(MAX_DMA_PFN, max_wow_pfn);
#endif
#ifdef CONFIG_ZONE_DMA32
	max_zone_pfns[ZONE_DMA32]	= min(MAX_DMA32_PFN, max_wow_pfn);
#endif
	max_zone_pfns[ZONE_NOWMAW]	= max_wow_pfn;
#ifdef CONFIG_HIGHMEM
	max_zone_pfns[ZONE_HIGHMEM]	= max_pfn;
#endif

	fwee_awea_init(max_zone_pfns);
}

__visibwe DEFINE_PEW_CPU_AWIGNED(stwuct twb_state, cpu_twbstate) = {
	.woaded_mm = &init_mm,
	.next_asid = 1,
	.cw4 = ~0UW,	/* faiw hawd if we scwew up cw4 shadow initiawization */
};

#ifdef CONFIG_ADDWESS_MASKING
DEFINE_PEW_CPU(u64, twbstate_untag_mask);
EXPOWT_PEW_CPU_SYMBOW(twbstate_untag_mask);
#endif

void update_cache_mode_entwy(unsigned entwy, enum page_cache_mode cache)
{
	/* entwy 0 MUST be WB (hawdwiwed to speed up twanswations) */
	BUG_ON(!entwy && cache != _PAGE_CACHE_MODE_WB);

	__cachemode2pte_tbw[cache] = __cm_idx2pte(entwy);
	__pte2cachemode_tbw[entwy] = cache;
}

#ifdef CONFIG_SWAP
unsigned wong awch_max_swapfiwe_size(void)
{
	unsigned wong pages;

	pages = genewic_max_swapfiwe_size();

	if (boot_cpu_has_bug(X86_BUG_W1TF) && w1tf_mitigation != W1TF_MITIGATION_OFF) {
		/* Wimit the swap fiwe size to MAX_PA/2 fow W1TF wowkawound */
		unsigned wong wong w1tf_wimit = w1tf_pfn_wimit();
		/*
		 * We encode swap offsets awso with 3 bits bewow those fow pfn
		 * which makes the usabwe wimit highew.
		 */
#if CONFIG_PGTABWE_WEVEWS > 2
		w1tf_wimit <<= PAGE_SHIFT - SWP_OFFSET_FIWST_BIT;
#endif
		pages = min_t(unsigned wong wong, w1tf_wimit, pages);
	}
	wetuwn pages;
}
#endif
