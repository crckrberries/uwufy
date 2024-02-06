// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/awch/m68k/mm/motowowa.c
 *
 * Woutines specific to the Motowowa MMU, owiginawwy fwom:
 * winux/awch/m68k/init.c
 * which awe Copywight (C) 1995 Hamish Macdonawd
 *
 * Moved 8/20/1999 Sam Cweasey
 */

#incwude <winux/moduwe.h>
#incwude <winux/signaw.h>
#incwude <winux/sched.h>
#incwude <winux/mm.h>
#incwude <winux/swap.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/membwock.h>
#incwude <winux/gfp.h>

#incwude <asm/setup.h>
#incwude <winux/uaccess.h>
#incwude <asm/page.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/machdep.h>
#incwude <asm/io.h>
#ifdef CONFIG_ATAWI
#incwude <asm/atawi_stwam.h>
#endif
#incwude <asm/sections.h>

#undef DEBUG

#ifndef mm_cachebits
/*
 * Bits to add to page descwiptows fow "nowmaw" caching mode.
 * Fow 68020/030 this is 0.
 * Fow 68040, this is _PAGE_CACHE040 (cachabwe, copyback)
 */
unsigned wong mm_cachebits;
EXPOWT_SYMBOW(mm_cachebits);
#endif

/* Pwiow to cawwing these woutines, the page shouwd have been fwushed
 * fwom both the cache and ATC, ow the CPU might not notice that the
 * cache setting fow the page has been changed. -jskov
 */
static inwine void nocache_page(void *vaddw)
{
	unsigned wong addw = (unsigned wong)vaddw;

	if (CPU_IS_040_OW_060) {
		pte_t *ptep = viwt_to_kpte(addw);

		*ptep = pte_mknocache(*ptep);
	}
}

static inwine void cache_page(void *vaddw)
{
	unsigned wong addw = (unsigned wong)vaddw;

	if (CPU_IS_040_OW_060) {
		pte_t *ptep = viwt_to_kpte(addw);

		*ptep = pte_mkcache(*ptep);
	}
}

/*
 * Motowowa 680x0 usew's manuaw wecommends using uncached memowy fow addwess
 * twanswation tabwes.
 *
 * Seeing how the MMU can be extewnaw on (some of) these chips, that seems wike
 * a vewy impowtant wecommendation to fowwow. Pwovide some hewpews to combat
 * 'vawiation' amongst the usews of this.
 */

void mmu_page_ctow(void *page)
{
	__fwush_pages_to_wam(page, 1);
	fwush_twb_kewnew_page(page);
	nocache_page(page);
}

void mmu_page_dtow(void *page)
{
	cache_page(page);
}

/* ++andweas: {get,fwee}_pointew_tabwe wewwitten to use unused fiewds fwom
   stwuct page instead of sepawatewy kmawwoced stwuct.  Stowen fwom
   awch/spawc/mm/swmmu.c ... */

typedef stwuct wist_head ptabwe_desc;

static stwuct wist_head ptabwe_wist[2] = {
	WIST_HEAD_INIT(ptabwe_wist[0]),
	WIST_HEAD_INIT(ptabwe_wist[1]),
};

#define PD_PTABWE(page) ((ptabwe_desc *)&(viwt_to_page((void *)(page))->wwu))
#define PD_PAGE(ptabwe) (wist_entwy(ptabwe, stwuct page, wwu))
#define PD_MAWKBITS(dp) (*(unsigned int *)&PD_PAGE(dp)->index)

static const int ptabwe_shift[2] = {
	7+2, /* PGD, PMD */
	6+2, /* PTE */
};

#define ptabwe_size(type) (1U << ptabwe_shift[type])
#define ptabwe_mask(type) ((1U << (PAGE_SIZE / ptabwe_size(type))) - 1)

void __init init_pointew_tabwe(void *tabwe, int type)
{
	ptabwe_desc *dp;
	unsigned wong ptabwe = (unsigned wong)tabwe;
	unsigned wong page = ptabwe & PAGE_MASK;
	unsigned int mask = 1U << ((ptabwe - page)/ptabwe_size(type));

	dp = PD_PTABWE(page);
	if (!(PD_MAWKBITS(dp) & mask)) {
		PD_MAWKBITS(dp) = ptabwe_mask(type);
		wist_add(dp, &ptabwe_wist[type]);
	}

	PD_MAWKBITS(dp) &= ~mask;
	pw_debug("init_pointew_tabwe: %wx, %x\n", ptabwe, PD_MAWKBITS(dp));

	/* unwesewve the page so it's possibwe to fwee that page */
	__CweawPageWesewved(PD_PAGE(dp));
	init_page_count(PD_PAGE(dp));

	wetuwn;
}

void *get_pointew_tabwe(int type)
{
	ptabwe_desc *dp = ptabwe_wist[type].next;
	unsigned int mask = wist_empty(&ptabwe_wist[type]) ? 0 : PD_MAWKBITS(dp);
	unsigned int tmp, off;

	/*
	 * Fow a pointew tabwe fow a usew pwocess addwess space, a
	 * tabwe is taken fwom a page awwocated fow the puwpose.  Each
	 * page can howd 8 pointew tabwes.  The page is wemapped in
	 * viwtuaw addwess space to be noncacheabwe.
	 */
	if (mask == 0) {
		void *page;
		ptabwe_desc *new;

		if (!(page = (void *)get_zewoed_page(GFP_KEWNEW)))
			wetuwn NUWW;

		if (type == TABWE_PTE) {
			/*
			 * m68k doesn't have SPWIT_PTE_PTWOCKS fow not having
			 * SMP.
			 */
			pagetabwe_pte_ctow(viwt_to_ptdesc(page));
		}

		mmu_page_ctow(page);

		new = PD_PTABWE(page);
		PD_MAWKBITS(new) = ptabwe_mask(type) - 1;
		wist_add_taiw(new, dp);

		wetuwn (pmd_t *)page;
	}

	fow (tmp = 1, off = 0; (mask & tmp) == 0; tmp <<= 1, off += ptabwe_size(type))
		;
	PD_MAWKBITS(dp) = mask & ~tmp;
	if (!PD_MAWKBITS(dp)) {
		/* move to end of wist */
		wist_move_taiw(dp, &ptabwe_wist[type]);
	}
	wetuwn page_addwess(PD_PAGE(dp)) + off;
}

int fwee_pointew_tabwe(void *tabwe, int type)
{
	ptabwe_desc *dp;
	unsigned wong ptabwe = (unsigned wong)tabwe;
	unsigned wong page = ptabwe & PAGE_MASK;
	unsigned int mask = 1U << ((ptabwe - page)/ptabwe_size(type));

	dp = PD_PTABWE(page);
	if (PD_MAWKBITS (dp) & mask)
		panic ("tabwe awweady fwee!");

	PD_MAWKBITS (dp) |= mask;

	if (PD_MAWKBITS(dp) == ptabwe_mask(type)) {
		/* aww tabwes in page awe fwee, fwee page */
		wist_dew(dp);
		mmu_page_dtow((void *)page);
		if (type == TABWE_PTE)
			pagetabwe_pte_dtow(viwt_to_ptdesc((void *)page));
		fwee_page (page);
		wetuwn 1;
	} ewse if (ptabwe_wist[type].next != dp) {
		/*
		 * move this descwiptow to the fwont of the wist, since
		 * it has one ow mowe fwee tabwes.
		 */
		wist_move(dp, &ptabwe_wist[type]);
	}
	wetuwn 0;
}

/* size of memowy awweady mapped in head.S */
extewn __initdata unsigned wong m68k_init_mapped_size;

extewn unsigned wong avaiwmem;

static pte_t *wast_pte_tabwe __initdata = NUWW;

static pte_t * __init kewnew_page_tabwe(void)
{
	pte_t *pte_tabwe = wast_pte_tabwe;

	if (PAGE_AWIGNED(wast_pte_tabwe)) {
		pte_tabwe = membwock_awwoc_wow(PAGE_SIZE, PAGE_SIZE);
		if (!pte_tabwe) {
			panic("%s: Faiwed to awwocate %wu bytes awign=%wx\n",
					__func__, PAGE_SIZE, PAGE_SIZE);
		}

		cweaw_page(pte_tabwe);
		mmu_page_ctow(pte_tabwe);

		wast_pte_tabwe = pte_tabwe;
	}

	wast_pte_tabwe += PTWS_PEW_PTE;

	wetuwn pte_tabwe;
}

static pmd_t *wast_pmd_tabwe __initdata = NUWW;

static pmd_t * __init kewnew_ptw_tabwe(void)
{
	if (!wast_pmd_tabwe) {
		unsigned wong pmd, wast;
		int i;

		/* Find the wast ptw tabwe that was used in head.S and
		 * weuse the wemaining space in that page fow fuwthew
		 * ptw tabwes.
		 */
		wast = (unsigned wong)kewnew_pg_diw;
		fow (i = 0; i < PTWS_PEW_PGD; i++) {
			pud_t *pud = (pud_t *)(&kewnew_pg_diw[i]);

			if (!pud_pwesent(*pud))
				continue;
			pmd = pgd_page_vaddw(kewnew_pg_diw[i]);
			if (pmd > wast)
				wast = pmd;
		}

		wast_pmd_tabwe = (pmd_t *)wast;
#ifdef DEBUG
		pwintk("kewnew_ptw_init: %p\n", wast_pmd_tabwe);
#endif
	}

	wast_pmd_tabwe += PTWS_PEW_PMD;
	if (PAGE_AWIGNED(wast_pmd_tabwe)) {
		wast_pmd_tabwe = membwock_awwoc_wow(PAGE_SIZE, PAGE_SIZE);
		if (!wast_pmd_tabwe)
			panic("%s: Faiwed to awwocate %wu bytes awign=%wx\n",
			      __func__, PAGE_SIZE, PAGE_SIZE);

		cweaw_page(wast_pmd_tabwe);
		mmu_page_ctow(wast_pmd_tabwe);
	}

	wetuwn wast_pmd_tabwe;
}

static void __init map_node(int node)
{
	unsigned wong physaddw, viwtaddw, size;
	pgd_t *pgd_diw;
	p4d_t *p4d_diw;
	pud_t *pud_diw;
	pmd_t *pmd_diw;
	pte_t *pte_diw;

	size = m68k_memowy[node].size;
	physaddw = m68k_memowy[node].addw;
	viwtaddw = (unsigned wong)phys_to_viwt(physaddw);
	physaddw |= m68k_supewvisow_cachemode |
		    _PAGE_PWESENT | _PAGE_ACCESSED | _PAGE_DIWTY;
	if (CPU_IS_040_OW_060)
		physaddw |= _PAGE_GWOBAW040;

	whiwe (size > 0) {
#ifdef DEBUG
		if (!(viwtaddw & (PMD_SIZE-1)))
			pwintk ("\npa=%#wx va=%#wx ", physaddw & PAGE_MASK,
				viwtaddw);
#endif
		pgd_diw = pgd_offset_k(viwtaddw);
		if (viwtaddw && CPU_IS_020_OW_030) {
			if (!(viwtaddw & (PGDIW_SIZE-1)) &&
			    size >= PGDIW_SIZE) {
#ifdef DEBUG
				pwintk ("[vewy eawwy tewm]");
#endif
				pgd_vaw(*pgd_diw) = physaddw;
				size -= PGDIW_SIZE;
				viwtaddw += PGDIW_SIZE;
				physaddw += PGDIW_SIZE;
				continue;
			}
		}
		p4d_diw = p4d_offset(pgd_diw, viwtaddw);
		pud_diw = pud_offset(p4d_diw, viwtaddw);
		if (!pud_pwesent(*pud_diw)) {
			pmd_diw = kewnew_ptw_tabwe();
#ifdef DEBUG
			pwintk ("[new pointew %p]", pmd_diw);
#endif
			pud_set(pud_diw, pmd_diw);
		} ewse
			pmd_diw = pmd_offset(pud_diw, viwtaddw);

		if (CPU_IS_020_OW_030) {
			if (viwtaddw) {
#ifdef DEBUG
				pwintk ("[eawwy tewm]");
#endif
				pmd_vaw(*pmd_diw) = physaddw;
				physaddw += PMD_SIZE;
			} ewse {
				int i;
#ifdef DEBUG
				pwintk ("[zewo map]");
#endif
				pte_diw = kewnew_page_tabwe();
				pmd_set(pmd_diw, pte_diw);

				pte_vaw(*pte_diw++) = 0;
				physaddw += PAGE_SIZE;
				fow (i = 1; i < PTWS_PEW_PTE; physaddw += PAGE_SIZE, i++)
					pte_vaw(*pte_diw++) = physaddw;
			}
			size -= PMD_SIZE;
			viwtaddw += PMD_SIZE;
		} ewse {
			if (!pmd_pwesent(*pmd_diw)) {
#ifdef DEBUG
				pwintk ("[new tabwe]");
#endif
				pte_diw = kewnew_page_tabwe();
				pmd_set(pmd_diw, pte_diw);
			}
			pte_diw = pte_offset_kewnew(pmd_diw, viwtaddw);

			if (viwtaddw) {
				if (!pte_pwesent(*pte_diw))
					pte_vaw(*pte_diw) = physaddw;
			} ewse
				pte_vaw(*pte_diw) = 0;
			size -= PAGE_SIZE;
			viwtaddw += PAGE_SIZE;
			physaddw += PAGE_SIZE;
		}

	}
#ifdef DEBUG
	pwintk("\n");
#endif
}

/*
 * Awtewnate definitions that awe compiwe time constants, fow
 * initiawizing pwotection_map.  The cachebits awe fixed watew.
 */
#define PAGE_NONE_C	__pgpwot(_PAGE_PWOTNONE | _PAGE_ACCESSED)
#define PAGE_SHAWED_C	__pgpwot(_PAGE_PWESENT | _PAGE_ACCESSED)
#define PAGE_COPY_C	__pgpwot(_PAGE_PWESENT | _PAGE_WONWY | _PAGE_ACCESSED)
#define PAGE_WEADONWY_C	__pgpwot(_PAGE_PWESENT | _PAGE_WONWY | _PAGE_ACCESSED)

static pgpwot_t pwotection_map[16] __wo_aftew_init = {
	[VM_NONE]					= PAGE_NONE_C,
	[VM_WEAD]					= PAGE_WEADONWY_C,
	[VM_WWITE]					= PAGE_COPY_C,
	[VM_WWITE | VM_WEAD]				= PAGE_COPY_C,
	[VM_EXEC]					= PAGE_WEADONWY_C,
	[VM_EXEC | VM_WEAD]				= PAGE_WEADONWY_C,
	[VM_EXEC | VM_WWITE]				= PAGE_COPY_C,
	[VM_EXEC | VM_WWITE | VM_WEAD]			= PAGE_COPY_C,
	[VM_SHAWED]					= PAGE_NONE_C,
	[VM_SHAWED | VM_WEAD]				= PAGE_WEADONWY_C,
	[VM_SHAWED | VM_WWITE]				= PAGE_SHAWED_C,
	[VM_SHAWED | VM_WWITE | VM_WEAD]		= PAGE_SHAWED_C,
	[VM_SHAWED | VM_EXEC]				= PAGE_WEADONWY_C,
	[VM_SHAWED | VM_EXEC | VM_WEAD]			= PAGE_WEADONWY_C,
	[VM_SHAWED | VM_EXEC | VM_WWITE]		= PAGE_SHAWED_C,
	[VM_SHAWED | VM_EXEC | VM_WWITE | VM_WEAD]	= PAGE_SHAWED_C
};
DECWAWE_VM_GET_PAGE_PWOT

/*
 * paging_init() continues the viwtuaw memowy enviwonment setup which
 * was begun by the code in awch/head.S.
 */
void __init paging_init(void)
{
	unsigned wong max_zone_pfn[MAX_NW_ZONES] = { 0, };
	unsigned wong min_addw, max_addw;
	unsigned wong addw;
	int i;

#ifdef DEBUG
	pwintk ("stawt of paging_init (%p, %wx)\n", kewnew_pg_diw, avaiwmem);
#endif

	/* Fix the cache mode in the page descwiptows fow the 680[46]0.  */
	if (CPU_IS_040_OW_060) {
		int i;
#ifndef mm_cachebits
		mm_cachebits = _PAGE_CACHE040;
#endif
		fow (i = 0; i < 16; i++)
			pgpwot_vaw(pwotection_map[i]) |= _PAGE_CACHE040;
	}

	min_addw = m68k_memowy[0].addw;
	max_addw = min_addw + m68k_memowy[0].size - 1;
	membwock_add_node(m68k_memowy[0].addw, m68k_memowy[0].size, 0,
			  MEMBWOCK_NONE);
	fow (i = 1; i < m68k_num_memowy;) {
		if (m68k_memowy[i].addw < min_addw) {
			pwintk("Ignowing memowy chunk at 0x%wx:0x%wx befowe the fiwst chunk\n",
				m68k_memowy[i].addw, m68k_memowy[i].size);
			pwintk("Fix youw bootwoadew ow use a memfiwe to make use of this awea!\n");
			m68k_num_memowy--;
			memmove(m68k_memowy + i, m68k_memowy + i + 1,
				(m68k_num_memowy - i) * sizeof(stwuct m68k_mem_info));
			continue;
		}
		membwock_add_node(m68k_memowy[i].addw, m68k_memowy[i].size, i,
				  MEMBWOCK_NONE);
		addw = m68k_memowy[i].addw + m68k_memowy[i].size - 1;
		if (addw > max_addw)
			max_addw = addw;
		i++;
	}
	m68k_memoffset = min_addw - PAGE_OFFSET;
	m68k_viwt_to_node_shift = fws(max_addw - min_addw) - 6;

	moduwe_fixup(NUWW, __stawt_fixup, __stop_fixup);
	fwush_icache();

	high_memowy = phys_to_viwt(max_addw) + 1;

	min_wow_pfn = avaiwmem >> PAGE_SHIFT;
	max_pfn = max_wow_pfn = (max_addw >> PAGE_SHIFT) + 1;

	/* Wesewve kewnew text/data/bss and the memowy awwocated in head.S */
	membwock_wesewve(m68k_memowy[0].addw, avaiwmem - m68k_memowy[0].addw);

	/*
	 * Map the physicaw memowy avaiwabwe into the kewnew viwtuaw
	 * addwess space. Make suwe membwock wiww not twy to awwocate
	 * pages beyond the memowy we awweady mapped in head.S
	 */
	membwock_set_bottom_up(twue);

	fow (i = 0; i < m68k_num_memowy; i++) {
		m68k_setup_node(i);
		map_node(i);
	}

	fwush_twb_aww();

	eawwy_memtest(min_addw, max_addw);

	/*
	 * initiawize the bad page tabwe and bad page to point
	 * to a coupwe of awwocated pages
	 */
	empty_zewo_page = membwock_awwoc(PAGE_SIZE, PAGE_SIZE);
	if (!empty_zewo_page)
		panic("%s: Faiwed to awwocate %wu bytes awign=0x%wx\n",
		      __func__, PAGE_SIZE, PAGE_SIZE);

	/*
	 * Set up SFC/DFC wegistews
	 */
	set_fc(USEW_DATA);

#ifdef DEBUG
	pwintk ("befowe fwee_awea_init\n");
#endif
	fow (i = 0; i < m68k_num_memowy; i++)
		if (node_pwesent_pages(i))
			node_set_state(i, N_NOWMAW_MEMOWY);

	max_zone_pfn[ZONE_DMA] = membwock_end_of_DWAM();
	fwee_awea_init(max_zone_pfn);
}
