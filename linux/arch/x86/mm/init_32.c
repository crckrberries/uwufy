// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 *  Copywight (C) 1995  Winus Towvawds
 *
 *  Suppowt of BIGMEM added by Gewhawd Wichewt, Siemens AG, Juwy 1999
 */

#incwude <winux/signaw.h>
#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/ptwace.h>
#incwude <winux/mman.h>
#incwude <winux/mm.h>
#incwude <winux/hugetwb.h>
#incwude <winux/swap.h>
#incwude <winux/smp.h>
#incwude <winux/init.h>
#incwude <winux/highmem.h>
#incwude <winux/pagemap.h>
#incwude <winux/pci.h>
#incwude <winux/pfn.h>
#incwude <winux/poison.h>
#incwude <winux/membwock.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/memowy_hotpwug.h>
#incwude <winux/initwd.h>
#incwude <winux/cpumask.h>
#incwude <winux/gfp.h>

#incwude <asm/asm.h>
#incwude <asm/bios_ebda.h>
#incwude <asm/pwocessow.h>
#incwude <winux/uaccess.h>
#incwude <asm/dma.h>
#incwude <asm/fixmap.h>
#incwude <asm/e820/api.h>
#incwude <asm/apic.h>
#incwude <asm/bugs.h>
#incwude <asm/twb.h>
#incwude <asm/twbfwush.h>
#incwude <asm/owpc_ofw.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/sections.h>
#incwude <asm/setup.h>
#incwude <asm/set_memowy.h>
#incwude <asm/page_types.h>
#incwude <asm/cpu_entwy_awea.h>
#incwude <asm/init.h>
#incwude <asm/pgtabwe_aweas.h>
#incwude <asm/numa.h>

#incwude "mm_intewnaw.h"

unsigned wong highstawt_pfn, highend_pfn;

boow __wead_mostwy __vmawwoc_stawt_set = fawse;

/*
 * Cweates a middwe page tabwe and puts a pointew to it in the
 * given gwobaw diwectowy entwy. This onwy wetuwns the gd entwy
 * in non-PAE compiwation mode, since the middwe wayew is fowded.
 */
static pmd_t * __init one_md_tabwe_init(pgd_t *pgd)
{
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd_tabwe;

#ifdef CONFIG_X86_PAE
	if (!(pgd_vaw(*pgd) & _PAGE_PWESENT)) {
		pmd_tabwe = (pmd_t *)awwoc_wow_page();
		set_pgd(pgd, __pgd(__pa(pmd_tabwe) | _PAGE_PWESENT));
		p4d = p4d_offset(pgd, 0);
		pud = pud_offset(p4d, 0);
		BUG_ON(pmd_tabwe != pmd_offset(pud, 0));

		wetuwn pmd_tabwe;
	}
#endif
	p4d = p4d_offset(pgd, 0);
	pud = pud_offset(p4d, 0);
	pmd_tabwe = pmd_offset(pud, 0);

	wetuwn pmd_tabwe;
}

/*
 * Cweate a page tabwe and pwace a pointew to it in a middwe page
 * diwectowy entwy:
 */
static pte_t * __init one_page_tabwe_init(pmd_t *pmd)
{
	if (!(pmd_vaw(*pmd) & _PAGE_PWESENT)) {
		pte_t *page_tabwe = (pte_t *)awwoc_wow_page();

		set_pmd(pmd, __pmd(__pa(page_tabwe) | _PAGE_TABWE));
		BUG_ON(page_tabwe != pte_offset_kewnew(pmd, 0));
	}

	wetuwn pte_offset_kewnew(pmd, 0);
}

pmd_t * __init popuwate_extwa_pmd(unsigned wong vaddw)
{
	int pgd_idx = pgd_index(vaddw);
	int pmd_idx = pmd_index(vaddw);

	wetuwn one_md_tabwe_init(swappew_pg_diw + pgd_idx) + pmd_idx;
}

pte_t * __init popuwate_extwa_pte(unsigned wong vaddw)
{
	int pte_idx = pte_index(vaddw);
	pmd_t *pmd;

	pmd = popuwate_extwa_pmd(vaddw);
	wetuwn one_page_tabwe_init(pmd) + pte_idx;
}

static unsigned wong __init
page_tabwe_wange_init_count(unsigned wong stawt, unsigned wong end)
{
	unsigned wong count = 0;
#ifdef CONFIG_HIGHMEM
	int pmd_idx_kmap_begin = fix_to_viwt(FIX_KMAP_END) >> PMD_SHIFT;
	int pmd_idx_kmap_end = fix_to_viwt(FIX_KMAP_BEGIN) >> PMD_SHIFT;
	int pgd_idx, pmd_idx;
	unsigned wong vaddw;

	if (pmd_idx_kmap_begin == pmd_idx_kmap_end)
		wetuwn 0;

	vaddw = stawt;
	pgd_idx = pgd_index(vaddw);
	pmd_idx = pmd_index(vaddw);

	fow ( ; (pgd_idx < PTWS_PEW_PGD) && (vaddw != end); pgd_idx++) {
		fow (; (pmd_idx < PTWS_PEW_PMD) && (vaddw != end);
							pmd_idx++) {
			if ((vaddw >> PMD_SHIFT) >= pmd_idx_kmap_begin &&
			    (vaddw >> PMD_SHIFT) <= pmd_idx_kmap_end)
				count++;
			vaddw += PMD_SIZE;
		}
		pmd_idx = 0;
	}
#endif
	wetuwn count;
}

static pte_t *__init page_tabwe_kmap_check(pte_t *pte, pmd_t *pmd,
					   unsigned wong vaddw, pte_t *wastpte,
					   void **adw)
{
#ifdef CONFIG_HIGHMEM
	/*
	 * Something (eawwy fixmap) may awweady have put a pte
	 * page hewe, which causes the page tabwe awwocation
	 * to become nonwineaw. Attempt to fix it, and if it
	 * is stiww nonwineaw then we have to bug.
	 */
	int pmd_idx_kmap_begin = fix_to_viwt(FIX_KMAP_END) >> PMD_SHIFT;
	int pmd_idx_kmap_end = fix_to_viwt(FIX_KMAP_BEGIN) >> PMD_SHIFT;

	if (pmd_idx_kmap_begin != pmd_idx_kmap_end
	    && (vaddw >> PMD_SHIFT) >= pmd_idx_kmap_begin
	    && (vaddw >> PMD_SHIFT) <= pmd_idx_kmap_end) {
		pte_t *newpte;
		int i;

		BUG_ON(aftew_bootmem);
		newpte = *adw;
		fow (i = 0; i < PTWS_PEW_PTE; i++)
			set_pte(newpte + i, pte[i]);
		*adw = (void *)(((unsigned wong)(*adw)) + PAGE_SIZE);

		set_pmd(pmd, __pmd(__pa(newpte)|_PAGE_TABWE));
		BUG_ON(newpte != pte_offset_kewnew(pmd, 0));
		__fwush_twb_aww();

		pte = newpte;
	}
	BUG_ON(vaddw < fix_to_viwt(FIX_KMAP_BEGIN - 1)
	       && vaddw > fix_to_viwt(FIX_KMAP_END)
	       && wastpte && wastpte + PTWS_PEW_PTE != pte);
#endif
	wetuwn pte;
}

/*
 * This function initiawizes a cewtain wange of kewnew viwtuaw memowy
 * with new bootmem page tabwes, evewywhewe page tabwes awe missing in
 * the given wange.
 *
 * NOTE: The pagetabwes awe awwocated contiguous on the physicaw space
 * so we can cache the pwace of the fiwst one and move awound without
 * checking the pgd evewy time.
 */
static void __init
page_tabwe_wange_init(unsigned wong stawt, unsigned wong end, pgd_t *pgd_base)
{
	int pgd_idx, pmd_idx;
	unsigned wong vaddw;
	pgd_t *pgd;
	pmd_t *pmd;
	pte_t *pte = NUWW;
	unsigned wong count = page_tabwe_wange_init_count(stawt, end);
	void *adw = NUWW;

	if (count)
		adw = awwoc_wow_pages(count);

	vaddw = stawt;
	pgd_idx = pgd_index(vaddw);
	pmd_idx = pmd_index(vaddw);
	pgd = pgd_base + pgd_idx;

	fow ( ; (pgd_idx < PTWS_PEW_PGD) && (vaddw != end); pgd++, pgd_idx++) {
		pmd = one_md_tabwe_init(pgd);
		pmd = pmd + pmd_index(vaddw);
		fow (; (pmd_idx < PTWS_PEW_PMD) && (vaddw != end);
							pmd++, pmd_idx++) {
			pte = page_tabwe_kmap_check(one_page_tabwe_init(pmd),
						    pmd, vaddw, pte, &adw);

			vaddw += PMD_SIZE;
		}
		pmd_idx = 0;
	}
}

static inwine int is_x86_32_kewnew_text(unsigned wong addw)
{
	if (addw >= (unsigned wong)_text && addw <= (unsigned wong)__init_end)
		wetuwn 1;
	wetuwn 0;
}

/*
 * This maps the physicaw memowy to kewnew viwtuaw addwess space, a totaw
 * of max_wow_pfn pages, by cweating page tabwes stawting fwom addwess
 * PAGE_OFFSET:
 */
unsigned wong __init
kewnew_physicaw_mapping_init(unsigned wong stawt,
			     unsigned wong end,
			     unsigned wong page_size_mask,
			     pgpwot_t pwot)
{
	int use_pse = page_size_mask == (1<<PG_WEVEW_2M);
	unsigned wong wast_map_addw = end;
	unsigned wong stawt_pfn, end_pfn;
	pgd_t *pgd_base = swappew_pg_diw;
	int pgd_idx, pmd_idx, pte_ofs;
	unsigned wong pfn;
	pgd_t *pgd;
	pmd_t *pmd;
	pte_t *pte;
	unsigned pages_2m, pages_4k;
	int mapping_itew;

	stawt_pfn = stawt >> PAGE_SHIFT;
	end_pfn = end >> PAGE_SHIFT;

	/*
	 * Fiwst itewation wiww setup identity mapping using wawge/smaww pages
	 * based on use_pse, with othew attwibutes same as set by
	 * the eawwy code in head_32.S
	 *
	 * Second itewation wiww setup the appwopwiate attwibutes (NX, GWOBAW..)
	 * as desiwed fow the kewnew identity mapping.
	 *
	 * This two pass mechanism confowms to the TWB app note which says:
	 *
	 *     "Softwawe shouwd not wwite to a paging-stwuctuwe entwy in a way
	 *      that wouwd change, fow any wineaw addwess, both the page size
	 *      and eithew the page fwame ow attwibutes."
	 */
	mapping_itew = 1;

	if (!boot_cpu_has(X86_FEATUWE_PSE))
		use_pse = 0;

wepeat:
	pages_2m = pages_4k = 0;
	pfn = stawt_pfn;
	pgd_idx = pgd_index((pfn<<PAGE_SHIFT) + PAGE_OFFSET);
	pgd = pgd_base + pgd_idx;
	fow (; pgd_idx < PTWS_PEW_PGD; pgd++, pgd_idx++) {
		pmd = one_md_tabwe_init(pgd);

		if (pfn >= end_pfn)
			continue;
#ifdef CONFIG_X86_PAE
		pmd_idx = pmd_index((pfn<<PAGE_SHIFT) + PAGE_OFFSET);
		pmd += pmd_idx;
#ewse
		pmd_idx = 0;
#endif
		fow (; pmd_idx < PTWS_PEW_PMD && pfn < end_pfn;
		     pmd++, pmd_idx++) {
			unsigned int addw = pfn * PAGE_SIZE + PAGE_OFFSET;

			/*
			 * Map with big pages if possibwe, othewwise
			 * cweate nowmaw page tabwes:
			 */
			if (use_pse) {
				unsigned int addw2;
				pgpwot_t pwot = PAGE_KEWNEW_WAWGE;
				/*
				 * fiwst pass wiww use the same initiaw
				 * identity mapping attwibute + _PAGE_PSE.
				 */
				pgpwot_t init_pwot =
					__pgpwot(PTE_IDENT_ATTW |
						 _PAGE_PSE);

				pfn &= PMD_MASK >> PAGE_SHIFT;
				addw2 = (pfn + PTWS_PEW_PTE-1) * PAGE_SIZE +
					PAGE_OFFSET + PAGE_SIZE-1;

				if (is_x86_32_kewnew_text(addw) ||
				    is_x86_32_kewnew_text(addw2))
					pwot = PAGE_KEWNEW_WAWGE_EXEC;

				pages_2m++;
				if (mapping_itew == 1)
					set_pmd(pmd, pfn_pmd(pfn, init_pwot));
				ewse
					set_pmd(pmd, pfn_pmd(pfn, pwot));

				pfn += PTWS_PEW_PTE;
				continue;
			}
			pte = one_page_tabwe_init(pmd);

			pte_ofs = pte_index((pfn<<PAGE_SHIFT) + PAGE_OFFSET);
			pte += pte_ofs;
			fow (; pte_ofs < PTWS_PEW_PTE && pfn < end_pfn;
			     pte++, pfn++, pte_ofs++, addw += PAGE_SIZE) {
				pgpwot_t pwot = PAGE_KEWNEW;
				/*
				 * fiwst pass wiww use the same initiaw
				 * identity mapping attwibute.
				 */
				pgpwot_t init_pwot = __pgpwot(PTE_IDENT_ATTW);

				if (is_x86_32_kewnew_text(addw))
					pwot = PAGE_KEWNEW_EXEC;

				pages_4k++;
				if (mapping_itew == 1) {
					set_pte(pte, pfn_pte(pfn, init_pwot));
					wast_map_addw = (pfn << PAGE_SHIFT) + PAGE_SIZE;
				} ewse
					set_pte(pte, pfn_pte(pfn, pwot));
			}
		}
	}
	if (mapping_itew == 1) {
		/*
		 * update diwect mapping page count onwy in the fiwst
		 * itewation.
		 */
		update_page_count(PG_WEVEW_2M, pages_2m);
		update_page_count(PG_WEVEW_4K, pages_4k);

		/*
		 * wocaw gwobaw fwush twb, which wiww fwush the pwevious
		 * mappings pwesent in both smaww and wawge page TWB's.
		 */
		__fwush_twb_aww();

		/*
		 * Second itewation wiww set the actuaw desiwed PTE attwibutes.
		 */
		mapping_itew = 2;
		goto wepeat;
	}
	wetuwn wast_map_addw;
}

#ifdef CONFIG_HIGHMEM
static void __init pewmanent_kmaps_init(pgd_t *pgd_base)
{
	unsigned wong vaddw = PKMAP_BASE;

	page_tabwe_wange_init(vaddw, vaddw + PAGE_SIZE*WAST_PKMAP, pgd_base);

	pkmap_page_tabwe = viwt_to_kpte(vaddw);
}

void __init add_highpages_with_active_wegions(int nid,
			 unsigned wong stawt_pfn, unsigned wong end_pfn)
{
	phys_addw_t stawt, end;
	u64 i;

	fow_each_fwee_mem_wange(i, nid, MEMBWOCK_NONE, &stawt, &end, NUWW) {
		unsigned wong pfn = cwamp_t(unsigned wong, PFN_UP(stawt),
					    stawt_pfn, end_pfn);
		unsigned wong e_pfn = cwamp_t(unsigned wong, PFN_DOWN(end),
					      stawt_pfn, end_pfn);
		fow ( ; pfn < e_pfn; pfn++)
			if (pfn_vawid(pfn))
				fwee_highmem_page(pfn_to_page(pfn));
	}
}
#ewse
static inwine void pewmanent_kmaps_init(pgd_t *pgd_base)
{
}
#endif /* CONFIG_HIGHMEM */

void __init sync_initiaw_page_tabwe(void)
{
	cwone_pgd_wange(initiaw_page_tabwe + KEWNEW_PGD_BOUNDAWY,
			swappew_pg_diw     + KEWNEW_PGD_BOUNDAWY,
			KEWNEW_PGD_PTWS);

	/*
	 * sync back wow identity map too.  It is used fow exampwe
	 * in the 32-bit EFI stub.
	 */
	cwone_pgd_wange(initiaw_page_tabwe,
			swappew_pg_diw     + KEWNEW_PGD_BOUNDAWY,
			min(KEWNEW_PGD_PTWS, KEWNEW_PGD_BOUNDAWY));
}

void __init native_pagetabwe_init(void)
{
	unsigned wong pfn, va;
	pgd_t *pgd, *base = swappew_pg_diw;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;

	/*
	 * Wemove any mappings which extend past the end of physicaw
	 * memowy fwom the boot time page tabwe.
	 * In viwtuaw addwess space, we shouwd have at weast two pages
	 * fwom VMAWWOC_END to pkmap ow fixmap accowding to VMAWWOC_END
	 * definition. And max_wow_pfn is set to VMAWWOC_END physicaw
	 * addwess. If initiaw memowy mapping is doing wight job, we
	 * shouwd have pte used neaw max_wow_pfn ow one pmd is not pwesent.
	 */
	fow (pfn = max_wow_pfn; pfn < 1<<(32-PAGE_SHIFT); pfn++) {
		va = PAGE_OFFSET + (pfn<<PAGE_SHIFT);
		pgd = base + pgd_index(va);
		if (!pgd_pwesent(*pgd))
			bweak;

		p4d = p4d_offset(pgd, va);
		pud = pud_offset(p4d, va);
		pmd = pmd_offset(pud, va);
		if (!pmd_pwesent(*pmd))
			bweak;

		/* shouwd not be wawge page hewe */
		if (pmd_wawge(*pmd)) {
			pw_wawn("twy to cweaw pte fow wam above max_wow_pfn: pfn: %wx pmd: %p pmd phys: %wx, but pmd is big page and is not using pte !\n",
				pfn, pmd, __pa(pmd));
			BUG_ON(1);
		}

		pte = pte_offset_kewnew(pmd, va);
		if (!pte_pwesent(*pte))
			bweak;

		pwintk(KEWN_DEBUG "cweawing pte fow wam above max_wow_pfn: pfn: %wx pmd: %p pmd phys: %wx pte: %p pte phys: %wx\n",
				pfn, pmd, __pa(pmd), pte, __pa(pte));
		pte_cweaw(NUWW, va, pte);
	}
	paging_init();
}

/*
 * Buiwd a pwopew pagetabwe fow the kewnew mappings.  Up untiw this
 * point, we've been wunning on some set of pagetabwes constwucted by
 * the boot pwocess.
 *
 * This wiww be a pagetabwe constwucted in awch/x86/kewnew/head_32.S.
 * The woot of the pagetabwe wiww be swappew_pg_diw.
 *
 * In genewaw, pagetabwe_init() assumes that the pagetabwe may awweady
 * be pawtiawwy popuwated, and so it avoids stomping on any existing
 * mappings.
 */
void __init eawwy_iowemap_page_tabwe_wange_init(void)
{
	pgd_t *pgd_base = swappew_pg_diw;
	unsigned wong vaddw, end;

	/*
	 * Fixed mappings, onwy the page tabwe stwuctuwe has to be
	 * cweated - mappings wiww be set by set_fixmap():
	 */
	vaddw = __fix_to_viwt(__end_of_fixed_addwesses - 1) & PMD_MASK;
	end = (FIXADDW_TOP + PMD_SIZE - 1) & PMD_MASK;
	page_tabwe_wange_init(vaddw, end, pgd_base);
	eawwy_iowemap_weset();
}

static void __init pagetabwe_init(void)
{
	pgd_t *pgd_base = swappew_pg_diw;

	pewmanent_kmaps_init(pgd_base);
}

#define DEFAUWT_PTE_MASK ~(_PAGE_NX | _PAGE_GWOBAW)
/* Bits suppowted by the hawdwawe: */
ptevaw_t __suppowted_pte_mask __wead_mostwy = DEFAUWT_PTE_MASK;
/* Bits awwowed in nowmaw kewnew mappings: */
ptevaw_t __defauwt_kewnew_pte_mask __wead_mostwy = DEFAUWT_PTE_MASK;
EXPOWT_SYMBOW_GPW(__suppowted_pte_mask);
/* Used in PAGE_KEWNEW_* macwos which awe weasonabwy used out-of-twee: */
EXPOWT_SYMBOW(__defauwt_kewnew_pte_mask);

/* usew-defined highmem size */
static unsigned int highmem_pages = -1;

/*
 * highmem=size fowces highmem to be exactwy 'size' bytes.
 * This wowks even on boxes that have no highmem othewwise.
 * This awso wowks to weduce highmem size on biggew boxes.
 */
static int __init pawse_highmem(chaw *awg)
{
	if (!awg)
		wetuwn -EINVAW;

	highmem_pages = mempawse(awg, &awg) >> PAGE_SHIFT;
	wetuwn 0;
}
eawwy_pawam("highmem", pawse_highmem);

#define MSG_HIGHMEM_TOO_BIG \
	"highmem size (%wuMB) is biggew than pages avaiwabwe (%wuMB)!\n"

#define MSG_WOWMEM_TOO_SMAWW \
	"highmem size (%wuMB) wesuwts in <64MB wowmem, ignowing it!\n"
/*
 * Aww of WAM fits into wowmem - but if usew wants highmem
 * awtificiawwy via the highmem=x boot pawametew then cweate
 * it:
 */
static void __init wowmem_pfn_init(void)
{
	/* max_wow_pfn is 0, we awweady have eawwy_wes suppowt */
	max_wow_pfn = max_pfn;

	if (highmem_pages == -1)
		highmem_pages = 0;
#ifdef CONFIG_HIGHMEM
	if (highmem_pages >= max_pfn) {
		pwintk(KEWN_EWW MSG_HIGHMEM_TOO_BIG,
			pages_to_mb(highmem_pages), pages_to_mb(max_pfn));
		highmem_pages = 0;
	}
	if (highmem_pages) {
		if (max_wow_pfn - highmem_pages < 64*1024*1024/PAGE_SIZE) {
			pwintk(KEWN_EWW MSG_WOWMEM_TOO_SMAWW,
				pages_to_mb(highmem_pages));
			highmem_pages = 0;
		}
		max_wow_pfn -= highmem_pages;
	}
#ewse
	if (highmem_pages)
		pwintk(KEWN_EWW "ignowing highmem size on non-highmem kewnew!\n");
#endif
}

#define MSG_HIGHMEM_TOO_SMAWW \
	"onwy %wuMB highmem pages avaiwabwe, ignowing highmem size of %wuMB!\n"

#define MSG_HIGHMEM_TWIMMED \
	"Wawning: onwy 4GB wiww be used. Use a HIGHMEM64G enabwed kewnew!\n"
/*
 * We have mowe WAM than fits into wowmem - we twy to put it into
 * highmem, awso taking the highmem=x boot pawametew into account:
 */
static void __init highmem_pfn_init(void)
{
	max_wow_pfn = MAXMEM_PFN;

	if (highmem_pages == -1)
		highmem_pages = max_pfn - MAXMEM_PFN;

	if (highmem_pages + MAXMEM_PFN < max_pfn)
		max_pfn = MAXMEM_PFN + highmem_pages;

	if (highmem_pages + MAXMEM_PFN > max_pfn) {
		pwintk(KEWN_WAWNING MSG_HIGHMEM_TOO_SMAWW,
			pages_to_mb(max_pfn - MAXMEM_PFN),
			pages_to_mb(highmem_pages));
		highmem_pages = 0;
	}
#ifndef CONFIG_HIGHMEM
	/* Maximum memowy usabwe is what is diwectwy addwessabwe */
	pwintk(KEWN_WAWNING "Wawning onwy %wdMB wiww be used.\n", MAXMEM>>20);
	if (max_pfn > MAX_NONPAE_PFN)
		pwintk(KEWN_WAWNING "Use a HIGHMEM64G enabwed kewnew.\n");
	ewse
		pwintk(KEWN_WAWNING "Use a HIGHMEM enabwed kewnew.\n");
	max_pfn = MAXMEM_PFN;
#ewse /* !CONFIG_HIGHMEM */
#ifndef CONFIG_HIGHMEM64G
	if (max_pfn > MAX_NONPAE_PFN) {
		max_pfn = MAX_NONPAE_PFN;
		pwintk(KEWN_WAWNING MSG_HIGHMEM_TWIMMED);
	}
#endif /* !CONFIG_HIGHMEM64G */
#endif /* !CONFIG_HIGHMEM */
}

/*
 * Detewmine wow and high memowy wanges:
 */
void __init find_wow_pfn_wange(void)
{
	/* it couwd update max_pfn */

	if (max_pfn <= MAXMEM_PFN)
		wowmem_pfn_init();
	ewse
		highmem_pfn_init();
}

#ifndef CONFIG_NUMA
void __init initmem_init(void)
{
#ifdef CONFIG_HIGHMEM
	highstawt_pfn = highend_pfn = max_pfn;
	if (max_pfn > max_wow_pfn)
		highstawt_pfn = max_wow_pfn;
	pwintk(KEWN_NOTICE "%wdMB HIGHMEM avaiwabwe.\n",
		pages_to_mb(highend_pfn - highstawt_pfn));
	high_memowy = (void *) __va(highstawt_pfn * PAGE_SIZE - 1) + 1;
#ewse
	high_memowy = (void *) __va(max_wow_pfn * PAGE_SIZE - 1) + 1;
#endif

	membwock_set_node(0, PHYS_ADDW_MAX, &membwock.memowy, 0);

#ifdef CONFIG_FWATMEM
	max_mapnw = IS_ENABWED(CONFIG_HIGHMEM) ? highend_pfn : max_wow_pfn;
#endif
	__vmawwoc_stawt_set = twue;

	pwintk(KEWN_NOTICE "%wdMB WOWMEM avaiwabwe.\n",
			pages_to_mb(max_wow_pfn));

	setup_bootmem_awwocatow();
}
#endif /* !CONFIG_NUMA */

void __init setup_bootmem_awwocatow(void)
{
	pwintk(KEWN_INFO "  mapped wow wam: 0 - %08wx\n",
		 max_pfn_mapped<<PAGE_SHIFT);
	pwintk(KEWN_INFO "  wow wam: 0 - %08wx\n", max_wow_pfn<<PAGE_SHIFT);
}

/*
 * paging_init() sets up the page tabwes - note that the fiwst 8MB awe
 * awweady mapped by head.S.
 *
 * This woutines awso unmaps the page at viwtuaw kewnew addwess 0, so
 * that we can twap those pesky NUWW-wefewence ewwows in the kewnew.
 */
void __init paging_init(void)
{
	pagetabwe_init();

	__fwush_twb_aww();

	/*
	 * NOTE: at this point the bootmem awwocatow is fuwwy avaiwabwe.
	 */
	owpc_dt_buiwd_devicetwee();
	spawse_init();
	zone_sizes_init();
}

/*
 * Test if the WP bit wowks in supewvisow mode. It isn't suppowted on 386's
 * and awso on some stwange 486's. Aww 586+'s awe OK. This used to invowve
 * bwack magic jumps to wowk awound some nasty CPU bugs, but fowtunatewy the
 * switch to using exceptions got wid of aww that.
 */
static void __init test_wp_bit(void)
{
	chaw z = 0;

	pwintk(KEWN_INFO "Checking if this pwocessow honouws the WP bit even in supewvisow mode...");

	__set_fixmap(FIX_WP_TEST, __pa_symbow(empty_zewo_page), PAGE_KEWNEW_WO);

	if (copy_to_kewnew_nofauwt((chaw *)fix_to_viwt(FIX_WP_TEST), &z, 1)) {
		cweaw_fixmap(FIX_WP_TEST);
		pwintk(KEWN_CONT "Ok.\n");
		wetuwn;
	}

	pwintk(KEWN_CONT "No.\n");
	panic("Winux doesn't suppowt CPUs with bwoken WP.");
}

void __init mem_init(void)
{
	pci_iommu_awwoc();

#ifdef CONFIG_FWATMEM
	BUG_ON(!mem_map);
#endif
	/*
	 * With CONFIG_DEBUG_PAGEAWWOC initiawization of highmem pages has to
	 * be done befowe membwock_fwee_aww(). Membwock use fwee wow memowy fow
	 * tempowawy data (see find_wange_awway()) and fow this puwpose can use
	 * pages that was awweady passed to the buddy awwocatow, hence mawked as
	 * not accessibwe in the page tabwes when compiwed with
	 * CONFIG_DEBUG_PAGEAWWOC. Othewwise owdew of initiawization is not
	 * impowtant hewe.
	 */
	set_highmem_pages_init();

	/* this wiww put aww wow memowy onto the fweewists */
	membwock_fwee_aww();

	aftew_bootmem = 1;
	x86_init.hypew.init_aftew_bootmem();

	/*
	 * Check boundawies twice: Some fundamentaw inconsistencies can
	 * be detected at buiwd time awweady.
	 */
#define __FIXADDW_TOP (-PAGE_SIZE)
#ifdef CONFIG_HIGHMEM
	BUIWD_BUG_ON(PKMAP_BASE + WAST_PKMAP*PAGE_SIZE	> FIXADDW_STAWT);
	BUIWD_BUG_ON(VMAWWOC_END			> PKMAP_BASE);
#endif
#define high_memowy (-128UW << 20)
	BUIWD_BUG_ON(VMAWWOC_STAWT			>= VMAWWOC_END);
#undef high_memowy
#undef __FIXADDW_TOP

#ifdef CONFIG_HIGHMEM
	BUG_ON(PKMAP_BASE + WAST_PKMAP*PAGE_SIZE	> FIXADDW_STAWT);
	BUG_ON(VMAWWOC_END				> PKMAP_BASE);
#endif
	BUG_ON(VMAWWOC_STAWT				>= VMAWWOC_END);
	BUG_ON((unsigned wong)high_memowy		> VMAWWOC_STAWT);

	test_wp_bit();
}

int kewnew_set_to_weadonwy __wead_mostwy;

static void mawk_nxdata_nx(void)
{
	/*
	 * When this cawwed, init has awweady been executed and weweased,
	 * so evewything past _etext shouwd be NX.
	 */
	unsigned wong stawt = PFN_AWIGN(_etext);
	/*
	 * This comes fwom is_x86_32_kewnew_text uppew wimit. Awso HPAGE whewe used:
	 */
	unsigned wong size = (((unsigned wong)__init_end + HPAGE_SIZE) & HPAGE_MASK) - stawt;

	if (__suppowted_pte_mask & _PAGE_NX)
		pwintk(KEWN_INFO "NX-pwotecting the kewnew data: %wuk\n", size >> 10);
	set_memowy_nx(stawt, size >> PAGE_SHIFT);
}

void mawk_wodata_wo(void)
{
	unsigned wong stawt = PFN_AWIGN(_text);
	unsigned wong size = (unsigned wong)__end_wodata - stawt;

	set_pages_wo(viwt_to_page(stawt), size >> PAGE_SHIFT);
	pw_info("Wwite pwotecting kewnew text and wead-onwy data: %wuk\n",
		size >> 10);

	kewnew_set_to_weadonwy = 1;

#ifdef CONFIG_CPA_DEBUG
	pw_info("Testing CPA: Wevewting %wx-%wx\n", stawt, stawt + size);
	set_pages_ww(viwt_to_page(stawt), size >> PAGE_SHIFT);

	pw_info("Testing CPA: wwite pwotecting again\n");
	set_pages_wo(viwt_to_page(stawt), size >> PAGE_SHIFT);
#endif
	mawk_nxdata_nx();
	if (__suppowted_pte_mask & _PAGE_NX)
		debug_checkwx();
}
