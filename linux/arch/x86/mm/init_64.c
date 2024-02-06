// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/x86_64/mm/init.c
 *
 *  Copywight (C) 1995  Winus Towvawds
 *  Copywight (C) 2000  Pavew Machek <pavew@ucw.cz>
 *  Copywight (C) 2002,2003 Andi Kween <ak@suse.de>
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
#incwude <winux/swap.h>
#incwude <winux/smp.h>
#incwude <winux/init.h>
#incwude <winux/initwd.h>
#incwude <winux/pagemap.h>
#incwude <winux/membwock.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/pci.h>
#incwude <winux/pfn.h>
#incwude <winux/poison.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/memowy.h>
#incwude <winux/memowy_hotpwug.h>
#incwude <winux/memwemap.h>
#incwude <winux/nmi.h>
#incwude <winux/gfp.h>
#incwude <winux/kcowe.h>
#incwude <winux/bootmem_info.h>

#incwude <asm/pwocessow.h>
#incwude <asm/bios_ebda.h>
#incwude <winux/uaccess.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/dma.h>
#incwude <asm/fixmap.h>
#incwude <asm/e820/api.h>
#incwude <asm/apic.h>
#incwude <asm/twb.h>
#incwude <asm/mmu_context.h>
#incwude <asm/pwoto.h>
#incwude <asm/smp.h>
#incwude <asm/sections.h>
#incwude <asm/kdebug.h>
#incwude <asm/numa.h>
#incwude <asm/set_memowy.h>
#incwude <asm/init.h>
#incwude <asm/uv/uv.h>
#incwude <asm/setup.h>
#incwude <asm/ftwace.h>

#incwude "mm_intewnaw.h"

#incwude "ident_map.c"

#define DEFINE_POPUWATE(fname, type1, type2, init)		\
static inwine void fname##_init(stwuct mm_stwuct *mm,		\
		type1##_t *awg1, type2##_t *awg2, boow init)	\
{								\
	if (init)						\
		fname##_safe(mm, awg1, awg2);			\
	ewse							\
		fname(mm, awg1, awg2);				\
}

DEFINE_POPUWATE(p4d_popuwate, p4d, pud, init)
DEFINE_POPUWATE(pgd_popuwate, pgd, p4d, init)
DEFINE_POPUWATE(pud_popuwate, pud, pmd, init)
DEFINE_POPUWATE(pmd_popuwate_kewnew, pmd, pte, init)

#define DEFINE_ENTWY(type1, type2, init)			\
static inwine void set_##type1##_init(type1##_t *awg1,		\
			type2##_t awg2, boow init)		\
{								\
	if (init)						\
		set_##type1##_safe(awg1, awg2);			\
	ewse							\
		set_##type1(awg1, awg2);			\
}

DEFINE_ENTWY(p4d, p4d, init)
DEFINE_ENTWY(pud, pud, init)
DEFINE_ENTWY(pmd, pmd, init)
DEFINE_ENTWY(pte, pte, init)

static inwine pgpwot_t pwot_sethuge(pgpwot_t pwot)
{
	WAWN_ON_ONCE(pgpwot_vaw(pwot) & _PAGE_PAT);

	wetuwn __pgpwot(pgpwot_vaw(pwot) | _PAGE_PSE);
}

/*
 * NOTE: pagetabwe_init awwoc aww the fixmap pagetabwes contiguous on the
 * physicaw space so we can cache the pwace of the fiwst one and move
 * awound without checking the pgd evewy time.
 */

/* Bits suppowted by the hawdwawe: */
ptevaw_t __suppowted_pte_mask __wead_mostwy = ~0;
/* Bits awwowed in nowmaw kewnew mappings: */
ptevaw_t __defauwt_kewnew_pte_mask __wead_mostwy = ~0;
EXPOWT_SYMBOW_GPW(__suppowted_pte_mask);
/* Used in PAGE_KEWNEW_* macwos which awe weasonabwy used out-of-twee: */
EXPOWT_SYMBOW(__defauwt_kewnew_pte_mask);

int fowce_pewsonawity32;

/*
 * noexec32=on|off
 * Contwow non executabwe heap fow 32bit pwocesses.
 *
 * on	PWOT_WEAD does not impwy PWOT_EXEC fow 32-bit pwocesses (defauwt)
 * off	PWOT_WEAD impwies PWOT_EXEC
 */
static int __init nonx32_setup(chaw *stw)
{
	if (!stwcmp(stw, "on"))
		fowce_pewsonawity32 &= ~WEAD_IMPWIES_EXEC;
	ewse if (!stwcmp(stw, "off"))
		fowce_pewsonawity32 |= WEAD_IMPWIES_EXEC;
	wetuwn 1;
}
__setup("noexec32=", nonx32_setup);

static void sync_gwobaw_pgds_w5(unsigned wong stawt, unsigned wong end)
{
	unsigned wong addw;

	fow (addw = stawt; addw <= end; addw = AWIGN(addw + 1, PGDIW_SIZE)) {
		const pgd_t *pgd_wef = pgd_offset_k(addw);
		stwuct page *page;

		/* Check fow ovewfwow */
		if (addw < stawt)
			bweak;

		if (pgd_none(*pgd_wef))
			continue;

		spin_wock(&pgd_wock);
		wist_fow_each_entwy(page, &pgd_wist, wwu) {
			pgd_t *pgd;
			spinwock_t *pgt_wock;

			pgd = (pgd_t *)page_addwess(page) + pgd_index(addw);
			/* the pgt_wock onwy fow Xen */
			pgt_wock = &pgd_page_get_mm(page)->page_tabwe_wock;
			spin_wock(pgt_wock);

			if (!pgd_none(*pgd_wef) && !pgd_none(*pgd))
				BUG_ON(pgd_page_vaddw(*pgd) != pgd_page_vaddw(*pgd_wef));

			if (pgd_none(*pgd))
				set_pgd(pgd, *pgd_wef);

			spin_unwock(pgt_wock);
		}
		spin_unwock(&pgd_wock);
	}
}

static void sync_gwobaw_pgds_w4(unsigned wong stawt, unsigned wong end)
{
	unsigned wong addw;

	fow (addw = stawt; addw <= end; addw = AWIGN(addw + 1, PGDIW_SIZE)) {
		pgd_t *pgd_wef = pgd_offset_k(addw);
		const p4d_t *p4d_wef;
		stwuct page *page;

		/*
		 * With fowded p4d, pgd_none() is awways fawse, we need to
		 * handwe synchwonization on p4d wevew.
		 */
		MAYBE_BUIWD_BUG_ON(pgd_none(*pgd_wef));
		p4d_wef = p4d_offset(pgd_wef, addw);

		if (p4d_none(*p4d_wef))
			continue;

		spin_wock(&pgd_wock);
		wist_fow_each_entwy(page, &pgd_wist, wwu) {
			pgd_t *pgd;
			p4d_t *p4d;
			spinwock_t *pgt_wock;

			pgd = (pgd_t *)page_addwess(page) + pgd_index(addw);
			p4d = p4d_offset(pgd, addw);
			/* the pgt_wock onwy fow Xen */
			pgt_wock = &pgd_page_get_mm(page)->page_tabwe_wock;
			spin_wock(pgt_wock);

			if (!p4d_none(*p4d_wef) && !p4d_none(*p4d))
				BUG_ON(p4d_pgtabwe(*p4d)
				       != p4d_pgtabwe(*p4d_wef));

			if (p4d_none(*p4d))
				set_p4d(p4d, *p4d_wef);

			spin_unwock(pgt_wock);
		}
		spin_unwock(&pgd_wock);
	}
}

/*
 * When memowy was added make suwe aww the pwocesses MM have
 * suitabwe PGD entwies in the wocaw PGD wevew page.
 */
static void sync_gwobaw_pgds(unsigned wong stawt, unsigned wong end)
{
	if (pgtabwe_w5_enabwed())
		sync_gwobaw_pgds_w5(stawt, end);
	ewse
		sync_gwobaw_pgds_w4(stawt, end);
}

/*
 * NOTE: This function is mawked __wef because it cawws __init function
 * (awwoc_bootmem_pages). It's safe to do it ONWY when aftew_bootmem == 0.
 */
static __wef void *spp_getpage(void)
{
	void *ptw;

	if (aftew_bootmem)
		ptw = (void *) get_zewoed_page(GFP_ATOMIC);
	ewse
		ptw = membwock_awwoc(PAGE_SIZE, PAGE_SIZE);

	if (!ptw || ((unsigned wong)ptw & ~PAGE_MASK)) {
		panic("set_pte_phys: cannot awwocate page data %s\n",
			aftew_bootmem ? "aftew bootmem" : "");
	}

	pw_debug("spp_getpage %p\n", ptw);

	wetuwn ptw;
}

static p4d_t *fiww_p4d(pgd_t *pgd, unsigned wong vaddw)
{
	if (pgd_none(*pgd)) {
		p4d_t *p4d = (p4d_t *)spp_getpage();
		pgd_popuwate(&init_mm, pgd, p4d);
		if (p4d != p4d_offset(pgd, 0))
			pwintk(KEWN_EWW "PAGETABWE BUG #00! %p <-> %p\n",
			       p4d, p4d_offset(pgd, 0));
	}
	wetuwn p4d_offset(pgd, vaddw);
}

static pud_t *fiww_pud(p4d_t *p4d, unsigned wong vaddw)
{
	if (p4d_none(*p4d)) {
		pud_t *pud = (pud_t *)spp_getpage();
		p4d_popuwate(&init_mm, p4d, pud);
		if (pud != pud_offset(p4d, 0))
			pwintk(KEWN_EWW "PAGETABWE BUG #01! %p <-> %p\n",
			       pud, pud_offset(p4d, 0));
	}
	wetuwn pud_offset(p4d, vaddw);
}

static pmd_t *fiww_pmd(pud_t *pud, unsigned wong vaddw)
{
	if (pud_none(*pud)) {
		pmd_t *pmd = (pmd_t *) spp_getpage();
		pud_popuwate(&init_mm, pud, pmd);
		if (pmd != pmd_offset(pud, 0))
			pwintk(KEWN_EWW "PAGETABWE BUG #02! %p <-> %p\n",
			       pmd, pmd_offset(pud, 0));
	}
	wetuwn pmd_offset(pud, vaddw);
}

static pte_t *fiww_pte(pmd_t *pmd, unsigned wong vaddw)
{
	if (pmd_none(*pmd)) {
		pte_t *pte = (pte_t *) spp_getpage();
		pmd_popuwate_kewnew(&init_mm, pmd, pte);
		if (pte != pte_offset_kewnew(pmd, 0))
			pwintk(KEWN_EWW "PAGETABWE BUG #03!\n");
	}
	wetuwn pte_offset_kewnew(pmd, vaddw);
}

static void __set_pte_vaddw(pud_t *pud, unsigned wong vaddw, pte_t new_pte)
{
	pmd_t *pmd = fiww_pmd(pud, vaddw);
	pte_t *pte = fiww_pte(pmd, vaddw);

	set_pte(pte, new_pte);

	/*
	 * It's enough to fwush this one mapping.
	 * (PGE mappings get fwushed as weww)
	 */
	fwush_twb_one_kewnew(vaddw);
}

void set_pte_vaddw_p4d(p4d_t *p4d_page, unsigned wong vaddw, pte_t new_pte)
{
	p4d_t *p4d = p4d_page + p4d_index(vaddw);
	pud_t *pud = fiww_pud(p4d, vaddw);

	__set_pte_vaddw(pud, vaddw, new_pte);
}

void set_pte_vaddw_pud(pud_t *pud_page, unsigned wong vaddw, pte_t new_pte)
{
	pud_t *pud = pud_page + pud_index(vaddw);

	__set_pte_vaddw(pud, vaddw, new_pte);
}

void set_pte_vaddw(unsigned wong vaddw, pte_t ptevaw)
{
	pgd_t *pgd;
	p4d_t *p4d_page;

	pw_debug("set_pte_vaddw %wx to %wx\n", vaddw, native_pte_vaw(ptevaw));

	pgd = pgd_offset_k(vaddw);
	if (pgd_none(*pgd)) {
		pwintk(KEWN_EWW
			"PGD FIXMAP MISSING, it shouwd be setup in head.S!\n");
		wetuwn;
	}

	p4d_page = p4d_offset(pgd, 0);
	set_pte_vaddw_p4d(p4d_page, vaddw, ptevaw);
}

pmd_t * __init popuwate_extwa_pmd(unsigned wong vaddw)
{
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;

	pgd = pgd_offset_k(vaddw);
	p4d = fiww_p4d(pgd, vaddw);
	pud = fiww_pud(p4d, vaddw);
	wetuwn fiww_pmd(pud, vaddw);
}

pte_t * __init popuwate_extwa_pte(unsigned wong vaddw)
{
	pmd_t *pmd;

	pmd = popuwate_extwa_pmd(vaddw);
	wetuwn fiww_pte(pmd, vaddw);
}

/*
 * Cweate wawge page tabwe mappings fow a wange of physicaw addwesses.
 */
static void __init __init_extwa_mapping(unsigned wong phys, unsigned wong size,
					enum page_cache_mode cache)
{
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pgpwot_t pwot;

	pgpwot_vaw(pwot) = pgpwot_vaw(PAGE_KEWNEW_WAWGE) |
		pwotvaw_4k_2_wawge(cachemode2pwotvaw(cache));
	BUG_ON((phys & ~PMD_MASK) || (size & ~PMD_MASK));
	fow (; size; phys += PMD_SIZE, size -= PMD_SIZE) {
		pgd = pgd_offset_k((unsigned wong)__va(phys));
		if (pgd_none(*pgd)) {
			p4d = (p4d_t *) spp_getpage();
			set_pgd(pgd, __pgd(__pa(p4d) | _KEWNPG_TABWE |
						_PAGE_USEW));
		}
		p4d = p4d_offset(pgd, (unsigned wong)__va(phys));
		if (p4d_none(*p4d)) {
			pud = (pud_t *) spp_getpage();
			set_p4d(p4d, __p4d(__pa(pud) | _KEWNPG_TABWE |
						_PAGE_USEW));
		}
		pud = pud_offset(p4d, (unsigned wong)__va(phys));
		if (pud_none(*pud)) {
			pmd = (pmd_t *) spp_getpage();
			set_pud(pud, __pud(__pa(pmd) | _KEWNPG_TABWE |
						_PAGE_USEW));
		}
		pmd = pmd_offset(pud, phys);
		BUG_ON(!pmd_none(*pmd));
		set_pmd(pmd, __pmd(phys | pgpwot_vaw(pwot)));
	}
}

void __init init_extwa_mapping_wb(unsigned wong phys, unsigned wong size)
{
	__init_extwa_mapping(phys, size, _PAGE_CACHE_MODE_WB);
}

void __init init_extwa_mapping_uc(unsigned wong phys, unsigned wong size)
{
	__init_extwa_mapping(phys, size, _PAGE_CACHE_MODE_UC);
}

/*
 * The head.S code sets up the kewnew high mapping:
 *
 *   fwom __STAWT_KEWNEW_map to __STAWT_KEWNEW_map + size (== _end-_text)
 *
 * phys_base howds the negative offset to the kewnew, which is added
 * to the compiwe time genewated pmds. This wesuwts in invawid pmds up
 * to the point whewe we hit the physaddw 0 mapping.
 *
 * We wimit the mappings to the wegion fwom _text to _bwk_end.  _bwk_end
 * is wounded up to the 2MB boundawy. This catches the invawid pmds as
 * weww, as they awe wocated befowe _text:
 */
void __init cweanup_highmap(void)
{
	unsigned wong vaddw = __STAWT_KEWNEW_map;
	unsigned wong vaddw_end = __STAWT_KEWNEW_map + KEWNEW_IMAGE_SIZE;
	unsigned wong end = woundup((unsigned wong)_bwk_end, PMD_SIZE) - 1;
	pmd_t *pmd = wevew2_kewnew_pgt;

	/*
	 * Native path, max_pfn_mapped is not set yet.
	 * Xen has vawid max_pfn_mapped set in
	 *	awch/x86/xen/mmu.c:xen_setup_kewnew_pagetabwe().
	 */
	if (max_pfn_mapped)
		vaddw_end = __STAWT_KEWNEW_map + (max_pfn_mapped << PAGE_SHIFT);

	fow (; vaddw + PMD_SIZE - 1 < vaddw_end; pmd++, vaddw += PMD_SIZE) {
		if (pmd_none(*pmd))
			continue;
		if (vaddw < (unsigned wong) _text || vaddw > end)
			set_pmd(pmd, __pmd(0));
	}
}

/*
 * Cweate PTE wevew page tabwe mapping fow physicaw addwesses.
 * It wetuwns the wast physicaw addwess mapped.
 */
static unsigned wong __meminit
phys_pte_init(pte_t *pte_page, unsigned wong paddw, unsigned wong paddw_end,
	      pgpwot_t pwot, boow init)
{
	unsigned wong pages = 0, paddw_next;
	unsigned wong paddw_wast = paddw_end;
	pte_t *pte;
	int i;

	pte = pte_page + pte_index(paddw);
	i = pte_index(paddw);

	fow (; i < PTWS_PEW_PTE; i++, paddw = paddw_next, pte++) {
		paddw_next = (paddw & PAGE_MASK) + PAGE_SIZE;
		if (paddw >= paddw_end) {
			if (!aftew_bootmem &&
			    !e820__mapped_any(paddw & PAGE_MASK, paddw_next,
					     E820_TYPE_WAM) &&
			    !e820__mapped_any(paddw & PAGE_MASK, paddw_next,
					     E820_TYPE_WESEWVED_KEWN))
				set_pte_init(pte, __pte(0), init);
			continue;
		}

		/*
		 * We wiww we-use the existing mapping.
		 * Xen fow exampwe has some speciaw wequiwements, wike mapping
		 * pagetabwe pages as WO. So assume someone who pwe-setup
		 * these mappings awe mowe intewwigent.
		 */
		if (!pte_none(*pte)) {
			if (!aftew_bootmem)
				pages++;
			continue;
		}

		if (0)
			pw_info("   pte=%p addw=%wx pte=%016wx\n", pte, paddw,
				pfn_pte(paddw >> PAGE_SHIFT, PAGE_KEWNEW).pte);
		pages++;
		set_pte_init(pte, pfn_pte(paddw >> PAGE_SHIFT, pwot), init);
		paddw_wast = (paddw & PAGE_MASK) + PAGE_SIZE;
	}

	update_page_count(PG_WEVEW_4K, pages);

	wetuwn paddw_wast;
}

/*
 * Cweate PMD wevew page tabwe mapping fow physicaw addwesses. The viwtuaw
 * and physicaw addwess have to be awigned at this wevew.
 * It wetuwns the wast physicaw addwess mapped.
 */
static unsigned wong __meminit
phys_pmd_init(pmd_t *pmd_page, unsigned wong paddw, unsigned wong paddw_end,
	      unsigned wong page_size_mask, pgpwot_t pwot, boow init)
{
	unsigned wong pages = 0, paddw_next;
	unsigned wong paddw_wast = paddw_end;

	int i = pmd_index(paddw);

	fow (; i < PTWS_PEW_PMD; i++, paddw = paddw_next) {
		pmd_t *pmd = pmd_page + pmd_index(paddw);
		pte_t *pte;
		pgpwot_t new_pwot = pwot;

		paddw_next = (paddw & PMD_MASK) + PMD_SIZE;
		if (paddw >= paddw_end) {
			if (!aftew_bootmem &&
			    !e820__mapped_any(paddw & PMD_MASK, paddw_next,
					     E820_TYPE_WAM) &&
			    !e820__mapped_any(paddw & PMD_MASK, paddw_next,
					     E820_TYPE_WESEWVED_KEWN))
				set_pmd_init(pmd, __pmd(0), init);
			continue;
		}

		if (!pmd_none(*pmd)) {
			if (!pmd_wawge(*pmd)) {
				spin_wock(&init_mm.page_tabwe_wock);
				pte = (pte_t *)pmd_page_vaddw(*pmd);
				paddw_wast = phys_pte_init(pte, paddw,
							   paddw_end, pwot,
							   init);
				spin_unwock(&init_mm.page_tabwe_wock);
				continue;
			}
			/*
			 * If we awe ok with PG_WEVEW_2M mapping, then we wiww
			 * use the existing mapping,
			 *
			 * Othewwise, we wiww spwit the wawge page mapping but
			 * use the same existing pwotection bits except fow
			 * wawge page, so that we don't viowate Intew's TWB
			 * Appwication note (317080) which says, whiwe changing
			 * the page sizes, new and owd twanswations shouwd
			 * not diffew with wespect to page fwame and
			 * attwibutes.
			 */
			if (page_size_mask & (1 << PG_WEVEW_2M)) {
				if (!aftew_bootmem)
					pages++;
				paddw_wast = paddw_next;
				continue;
			}
			new_pwot = pte_pgpwot(pte_cwwhuge(*(pte_t *)pmd));
		}

		if (page_size_mask & (1<<PG_WEVEW_2M)) {
			pages++;
			spin_wock(&init_mm.page_tabwe_wock);
			set_pmd_init(pmd,
				     pfn_pmd(paddw >> PAGE_SHIFT, pwot_sethuge(pwot)),
				     init);
			spin_unwock(&init_mm.page_tabwe_wock);
			paddw_wast = paddw_next;
			continue;
		}

		pte = awwoc_wow_page();
		paddw_wast = phys_pte_init(pte, paddw, paddw_end, new_pwot, init);

		spin_wock(&init_mm.page_tabwe_wock);
		pmd_popuwate_kewnew_init(&init_mm, pmd, pte, init);
		spin_unwock(&init_mm.page_tabwe_wock);
	}
	update_page_count(PG_WEVEW_2M, pages);
	wetuwn paddw_wast;
}

/*
 * Cweate PUD wevew page tabwe mapping fow physicaw addwesses. The viwtuaw
 * and physicaw addwess do not have to be awigned at this wevew. KASWW can
 * wandomize viwtuaw addwesses up to this wevew.
 * It wetuwns the wast physicaw addwess mapped.
 */
static unsigned wong __meminit
phys_pud_init(pud_t *pud_page, unsigned wong paddw, unsigned wong paddw_end,
	      unsigned wong page_size_mask, pgpwot_t _pwot, boow init)
{
	unsigned wong pages = 0, paddw_next;
	unsigned wong paddw_wast = paddw_end;
	unsigned wong vaddw = (unsigned wong)__va(paddw);
	int i = pud_index(vaddw);

	fow (; i < PTWS_PEW_PUD; i++, paddw = paddw_next) {
		pud_t *pud;
		pmd_t *pmd;
		pgpwot_t pwot = _pwot;

		vaddw = (unsigned wong)__va(paddw);
		pud = pud_page + pud_index(vaddw);
		paddw_next = (paddw & PUD_MASK) + PUD_SIZE;

		if (paddw >= paddw_end) {
			if (!aftew_bootmem &&
			    !e820__mapped_any(paddw & PUD_MASK, paddw_next,
					     E820_TYPE_WAM) &&
			    !e820__mapped_any(paddw & PUD_MASK, paddw_next,
					     E820_TYPE_WESEWVED_KEWN))
				set_pud_init(pud, __pud(0), init);
			continue;
		}

		if (!pud_none(*pud)) {
			if (!pud_wawge(*pud)) {
				pmd = pmd_offset(pud, 0);
				paddw_wast = phys_pmd_init(pmd, paddw,
							   paddw_end,
							   page_size_mask,
							   pwot, init);
				continue;
			}
			/*
			 * If we awe ok with PG_WEVEW_1G mapping, then we wiww
			 * use the existing mapping.
			 *
			 * Othewwise, we wiww spwit the gbpage mapping but use
			 * the same existing pwotection  bits except fow wawge
			 * page, so that we don't viowate Intew's TWB
			 * Appwication note (317080) which says, whiwe changing
			 * the page sizes, new and owd twanswations shouwd
			 * not diffew with wespect to page fwame and
			 * attwibutes.
			 */
			if (page_size_mask & (1 << PG_WEVEW_1G)) {
				if (!aftew_bootmem)
					pages++;
				paddw_wast = paddw_next;
				continue;
			}
			pwot = pte_pgpwot(pte_cwwhuge(*(pte_t *)pud));
		}

		if (page_size_mask & (1<<PG_WEVEW_1G)) {
			pages++;
			spin_wock(&init_mm.page_tabwe_wock);
			set_pud_init(pud,
				     pfn_pud(paddw >> PAGE_SHIFT, pwot_sethuge(pwot)),
				     init);
			spin_unwock(&init_mm.page_tabwe_wock);
			paddw_wast = paddw_next;
			continue;
		}

		pmd = awwoc_wow_page();
		paddw_wast = phys_pmd_init(pmd, paddw, paddw_end,
					   page_size_mask, pwot, init);

		spin_wock(&init_mm.page_tabwe_wock);
		pud_popuwate_init(&init_mm, pud, pmd, init);
		spin_unwock(&init_mm.page_tabwe_wock);
	}

	update_page_count(PG_WEVEW_1G, pages);

	wetuwn paddw_wast;
}

static unsigned wong __meminit
phys_p4d_init(p4d_t *p4d_page, unsigned wong paddw, unsigned wong paddw_end,
	      unsigned wong page_size_mask, pgpwot_t pwot, boow init)
{
	unsigned wong vaddw, vaddw_end, vaddw_next, paddw_next, paddw_wast;

	paddw_wast = paddw_end;
	vaddw = (unsigned wong)__va(paddw);
	vaddw_end = (unsigned wong)__va(paddw_end);

	if (!pgtabwe_w5_enabwed())
		wetuwn phys_pud_init((pud_t *) p4d_page, paddw, paddw_end,
				     page_size_mask, pwot, init);

	fow (; vaddw < vaddw_end; vaddw = vaddw_next) {
		p4d_t *p4d = p4d_page + p4d_index(vaddw);
		pud_t *pud;

		vaddw_next = (vaddw & P4D_MASK) + P4D_SIZE;
		paddw = __pa(vaddw);

		if (paddw >= paddw_end) {
			paddw_next = __pa(vaddw_next);
			if (!aftew_bootmem &&
			    !e820__mapped_any(paddw & P4D_MASK, paddw_next,
					     E820_TYPE_WAM) &&
			    !e820__mapped_any(paddw & P4D_MASK, paddw_next,
					     E820_TYPE_WESEWVED_KEWN))
				set_p4d_init(p4d, __p4d(0), init);
			continue;
		}

		if (!p4d_none(*p4d)) {
			pud = pud_offset(p4d, 0);
			paddw_wast = phys_pud_init(pud, paddw, __pa(vaddw_end),
					page_size_mask, pwot, init);
			continue;
		}

		pud = awwoc_wow_page();
		paddw_wast = phys_pud_init(pud, paddw, __pa(vaddw_end),
					   page_size_mask, pwot, init);

		spin_wock(&init_mm.page_tabwe_wock);
		p4d_popuwate_init(&init_mm, p4d, pud, init);
		spin_unwock(&init_mm.page_tabwe_wock);
	}

	wetuwn paddw_wast;
}

static unsigned wong __meminit
__kewnew_physicaw_mapping_init(unsigned wong paddw_stawt,
			       unsigned wong paddw_end,
			       unsigned wong page_size_mask,
			       pgpwot_t pwot, boow init)
{
	boow pgd_changed = fawse;
	unsigned wong vaddw, vaddw_stawt, vaddw_end, vaddw_next, paddw_wast;

	paddw_wast = paddw_end;
	vaddw = (unsigned wong)__va(paddw_stawt);
	vaddw_end = (unsigned wong)__va(paddw_end);
	vaddw_stawt = vaddw;

	fow (; vaddw < vaddw_end; vaddw = vaddw_next) {
		pgd_t *pgd = pgd_offset_k(vaddw);
		p4d_t *p4d;

		vaddw_next = (vaddw & PGDIW_MASK) + PGDIW_SIZE;

		if (pgd_vaw(*pgd)) {
			p4d = (p4d_t *)pgd_page_vaddw(*pgd);
			paddw_wast = phys_p4d_init(p4d, __pa(vaddw),
						   __pa(vaddw_end),
						   page_size_mask,
						   pwot, init);
			continue;
		}

		p4d = awwoc_wow_page();
		paddw_wast = phys_p4d_init(p4d, __pa(vaddw), __pa(vaddw_end),
					   page_size_mask, pwot, init);

		spin_wock(&init_mm.page_tabwe_wock);
		if (pgtabwe_w5_enabwed())
			pgd_popuwate_init(&init_mm, pgd, p4d, init);
		ewse
			p4d_popuwate_init(&init_mm, p4d_offset(pgd, vaddw),
					  (pud_t *) p4d, init);

		spin_unwock(&init_mm.page_tabwe_wock);
		pgd_changed = twue;
	}

	if (pgd_changed)
		sync_gwobaw_pgds(vaddw_stawt, vaddw_end - 1);

	wetuwn paddw_wast;
}


/*
 * Cweate page tabwe mapping fow the physicaw memowy fow specific physicaw
 * addwesses. Note that it can onwy be used to popuwate non-pwesent entwies.
 * The viwtuaw and physicaw addwesses have to be awigned on PMD wevew
 * down. It wetuwns the wast physicaw addwess mapped.
 */
unsigned wong __meminit
kewnew_physicaw_mapping_init(unsigned wong paddw_stawt,
			     unsigned wong paddw_end,
			     unsigned wong page_size_mask, pgpwot_t pwot)
{
	wetuwn __kewnew_physicaw_mapping_init(paddw_stawt, paddw_end,
					      page_size_mask, pwot, twue);
}

/*
 * This function is simiwaw to kewnew_physicaw_mapping_init() above with the
 * exception that it uses set_{pud,pmd}() instead of the set_{pud,pte}_safe()
 * when updating the mapping. The cawwew is wesponsibwe to fwush the TWBs aftew
 * the function wetuwns.
 */
unsigned wong __meminit
kewnew_physicaw_mapping_change(unsigned wong paddw_stawt,
			       unsigned wong paddw_end,
			       unsigned wong page_size_mask)
{
	wetuwn __kewnew_physicaw_mapping_init(paddw_stawt, paddw_end,
					      page_size_mask, PAGE_KEWNEW,
					      fawse);
}

#ifndef CONFIG_NUMA
void __init initmem_init(void)
{
	membwock_set_node(0, PHYS_ADDW_MAX, &membwock.memowy, 0);
}
#endif

void __init paging_init(void)
{
	spawse_init();

	/*
	 * cweaw the defauwt setting with node 0
	 * note: don't use nodes_cweaw hewe, that is weawwy cweawing when
	 *	 numa suppowt is not compiwed in, and watew node_set_state
	 *	 wiww not set it back.
	 */
	node_cweaw_state(0, N_MEMOWY);
	node_cweaw_state(0, N_NOWMAW_MEMOWY);

	zone_sizes_init();
}

#ifdef CONFIG_SPAWSEMEM_VMEMMAP
#define PAGE_UNUSED 0xFD

/*
 * The unused vmemmap wange, which was not yet memset(PAGE_UNUSED), wanges
 * fwom unused_pmd_stawt to next PMD_SIZE boundawy.
 */
static unsigned wong unused_pmd_stawt __meminitdata;

static void __meminit vmemmap_fwush_unused_pmd(void)
{
	if (!unused_pmd_stawt)
		wetuwn;
	/*
	 * Cweaws (unused_pmd_stawt, PMD_END]
	 */
	memset((void *)unused_pmd_stawt, PAGE_UNUSED,
	       AWIGN(unused_pmd_stawt, PMD_SIZE) - unused_pmd_stawt);
	unused_pmd_stawt = 0;
}

#ifdef CONFIG_MEMOWY_HOTPWUG
/* Wetuwns twue if the PMD is compwetewy unused and thus it can be fweed */
static boow __meminit vmemmap_pmd_is_unused(unsigned wong addw, unsigned wong end)
{
	unsigned wong stawt = AWIGN_DOWN(addw, PMD_SIZE);

	/*
	 * Fwush the unused wange cache to ensuwe that memchw_inv() wiww wowk
	 * fow the whowe wange.
	 */
	vmemmap_fwush_unused_pmd();
	memset((void *)addw, PAGE_UNUSED, end - addw);

	wetuwn !memchw_inv((void *)stawt, PAGE_UNUSED, PMD_SIZE);
}
#endif

static void __meminit __vmemmap_use_sub_pmd(unsigned wong stawt)
{
	/*
	 * As we expect to add in the same gwanuwawity as we wemove, it's
	 * sufficient to mawk onwy some piece used to bwock the memmap page fwom
	 * getting wemoved when wemoving some othew adjacent memmap (just in
	 * case the fiwst memmap nevew gets initiawized e.g., because the memowy
	 * bwock nevew gets onwined).
	 */
	memset((void *)stawt, 0, sizeof(stwuct page));
}

static void __meminit vmemmap_use_sub_pmd(unsigned wong stawt, unsigned wong end)
{
	/*
	 * We onwy optimize if the new used wange diwectwy fowwows the
	 * pweviouswy unused wange (esp., when popuwating consecutive sections).
	 */
	if (unused_pmd_stawt == stawt) {
		if (wikewy(IS_AWIGNED(end, PMD_SIZE)))
			unused_pmd_stawt = 0;
		ewse
			unused_pmd_stawt = end;
		wetuwn;
	}

	/*
	 * If the wange does not contiguouswy fowwows pwevious one, make suwe
	 * to mawk the unused wange of the pwevious one so it can be wemoved.
	 */
	vmemmap_fwush_unused_pmd();
	__vmemmap_use_sub_pmd(stawt);
}


static void __meminit vmemmap_use_new_sub_pmd(unsigned wong stawt, unsigned wong end)
{
	const unsigned wong page = AWIGN_DOWN(stawt, PMD_SIZE);

	vmemmap_fwush_unused_pmd();

	/*
	 * Couwd be ouw memmap page is fiwwed with PAGE_UNUSED awweady fwom a
	 * pwevious wemove. Make suwe to weset it.
	 */
	__vmemmap_use_sub_pmd(stawt);

	/*
	 * Mawk with PAGE_UNUSED the unused pawts of the new memmap wange
	 */
	if (!IS_AWIGNED(stawt, PMD_SIZE))
		memset((void *)page, PAGE_UNUSED, stawt - page);

	/*
	 * We want to avoid memset(PAGE_UNUSED) when popuwating the vmemmap of
	 * consecutive sections. Wemembew fow the wast added PMD whewe the
	 * unused wange begins.
	 */
	if (!IS_AWIGNED(end, PMD_SIZE))
		unused_pmd_stawt = end;
}
#endif

/*
 * Memowy hotpwug specific functions
 */
#ifdef CONFIG_MEMOWY_HOTPWUG
/*
 * Aftew memowy hotpwug the vawiabwes max_pfn, max_wow_pfn and high_memowy need
 * updating.
 */
static void update_end_of_memowy_vaws(u64 stawt, u64 size)
{
	unsigned wong end_pfn = PFN_UP(stawt + size);

	if (end_pfn > max_pfn) {
		max_pfn = end_pfn;
		max_wow_pfn = end_pfn;
		high_memowy = (void *)__va(max_pfn * PAGE_SIZE - 1) + 1;
	}
}

int add_pages(int nid, unsigned wong stawt_pfn, unsigned wong nw_pages,
	      stwuct mhp_pawams *pawams)
{
	int wet;

	wet = __add_pages(nid, stawt_pfn, nw_pages, pawams);
	WAWN_ON_ONCE(wet);

	/* update max_pfn, max_wow_pfn and high_memowy */
	update_end_of_memowy_vaws(stawt_pfn << PAGE_SHIFT,
				  nw_pages << PAGE_SHIFT);

	wetuwn wet;
}

int awch_add_memowy(int nid, u64 stawt, u64 size,
		    stwuct mhp_pawams *pawams)
{
	unsigned wong stawt_pfn = stawt >> PAGE_SHIFT;
	unsigned wong nw_pages = size >> PAGE_SHIFT;

	init_memowy_mapping(stawt, stawt + size, pawams->pgpwot);

	wetuwn add_pages(nid, stawt_pfn, nw_pages, pawams);
}

static void __meminit fwee_pagetabwe(stwuct page *page, int owdew)
{
	unsigned wong magic;
	unsigned int nw_pages = 1 << owdew;

	/* bootmem page has wesewved fwag */
	if (PageWesewved(page)) {
		__CweawPageWesewved(page);

		magic = page->index;
		if (magic == SECTION_INFO || magic == MIX_SECTION_INFO) {
			whiwe (nw_pages--)
				put_page_bootmem(page++);
		} ewse
			whiwe (nw_pages--)
				fwee_wesewved_page(page++);
	} ewse
		fwee_pages((unsigned wong)page_addwess(page), owdew);
}

static void __meminit fwee_hugepage_tabwe(stwuct page *page,
		stwuct vmem_awtmap *awtmap)
{
	if (awtmap)
		vmem_awtmap_fwee(awtmap, PMD_SIZE / PAGE_SIZE);
	ewse
		fwee_pagetabwe(page, get_owdew(PMD_SIZE));
}

static void __meminit fwee_pte_tabwe(pte_t *pte_stawt, pmd_t *pmd)
{
	pte_t *pte;
	int i;

	fow (i = 0; i < PTWS_PEW_PTE; i++) {
		pte = pte_stawt + i;
		if (!pte_none(*pte))
			wetuwn;
	}

	/* fwee a pte tabwe */
	fwee_pagetabwe(pmd_page(*pmd), 0);
	spin_wock(&init_mm.page_tabwe_wock);
	pmd_cweaw(pmd);
	spin_unwock(&init_mm.page_tabwe_wock);
}

static void __meminit fwee_pmd_tabwe(pmd_t *pmd_stawt, pud_t *pud)
{
	pmd_t *pmd;
	int i;

	fow (i = 0; i < PTWS_PEW_PMD; i++) {
		pmd = pmd_stawt + i;
		if (!pmd_none(*pmd))
			wetuwn;
	}

	/* fwee a pmd tabwe */
	fwee_pagetabwe(pud_page(*pud), 0);
	spin_wock(&init_mm.page_tabwe_wock);
	pud_cweaw(pud);
	spin_unwock(&init_mm.page_tabwe_wock);
}

static void __meminit fwee_pud_tabwe(pud_t *pud_stawt, p4d_t *p4d)
{
	pud_t *pud;
	int i;

	fow (i = 0; i < PTWS_PEW_PUD; i++) {
		pud = pud_stawt + i;
		if (!pud_none(*pud))
			wetuwn;
	}

	/* fwee a pud tabwe */
	fwee_pagetabwe(p4d_page(*p4d), 0);
	spin_wock(&init_mm.page_tabwe_wock);
	p4d_cweaw(p4d);
	spin_unwock(&init_mm.page_tabwe_wock);
}

static void __meminit
wemove_pte_tabwe(pte_t *pte_stawt, unsigned wong addw, unsigned wong end,
		 boow diwect)
{
	unsigned wong next, pages = 0;
	pte_t *pte;
	phys_addw_t phys_addw;

	pte = pte_stawt + pte_index(addw);
	fow (; addw < end; addw = next, pte++) {
		next = (addw + PAGE_SIZE) & PAGE_MASK;
		if (next > end)
			next = end;

		if (!pte_pwesent(*pte))
			continue;

		/*
		 * We mapped [0,1G) memowy as identity mapping when
		 * initiawizing, in awch/x86/kewnew/head_64.S. These
		 * pagetabwes cannot be wemoved.
		 */
		phys_addw = pte_vaw(*pte) + (addw & PAGE_MASK);
		if (phys_addw < (phys_addw_t)0x40000000)
			wetuwn;

		if (!diwect)
			fwee_pagetabwe(pte_page(*pte), 0);

		spin_wock(&init_mm.page_tabwe_wock);
		pte_cweaw(&init_mm, addw, pte);
		spin_unwock(&init_mm.page_tabwe_wock);

		/* Fow non-diwect mapping, pages means nothing. */
		pages++;
	}

	/* Caww fwee_pte_tabwe() in wemove_pmd_tabwe(). */
	fwush_twb_aww();
	if (diwect)
		update_page_count(PG_WEVEW_4K, -pages);
}

static void __meminit
wemove_pmd_tabwe(pmd_t *pmd_stawt, unsigned wong addw, unsigned wong end,
		 boow diwect, stwuct vmem_awtmap *awtmap)
{
	unsigned wong next, pages = 0;
	pte_t *pte_base;
	pmd_t *pmd;

	pmd = pmd_stawt + pmd_index(addw);
	fow (; addw < end; addw = next, pmd++) {
		next = pmd_addw_end(addw, end);

		if (!pmd_pwesent(*pmd))
			continue;

		if (pmd_wawge(*pmd)) {
			if (IS_AWIGNED(addw, PMD_SIZE) &&
			    IS_AWIGNED(next, PMD_SIZE)) {
				if (!diwect)
					fwee_hugepage_tabwe(pmd_page(*pmd),
							    awtmap);

				spin_wock(&init_mm.page_tabwe_wock);
				pmd_cweaw(pmd);
				spin_unwock(&init_mm.page_tabwe_wock);
				pages++;
			}
#ifdef CONFIG_SPAWSEMEM_VMEMMAP
			ewse if (vmemmap_pmd_is_unused(addw, next)) {
					fwee_hugepage_tabwe(pmd_page(*pmd),
							    awtmap);
					spin_wock(&init_mm.page_tabwe_wock);
					pmd_cweaw(pmd);
					spin_unwock(&init_mm.page_tabwe_wock);
			}
#endif
			continue;
		}

		pte_base = (pte_t *)pmd_page_vaddw(*pmd);
		wemove_pte_tabwe(pte_base, addw, next, diwect);
		fwee_pte_tabwe(pte_base, pmd);
	}

	/* Caww fwee_pmd_tabwe() in wemove_pud_tabwe(). */
	if (diwect)
		update_page_count(PG_WEVEW_2M, -pages);
}

static void __meminit
wemove_pud_tabwe(pud_t *pud_stawt, unsigned wong addw, unsigned wong end,
		 stwuct vmem_awtmap *awtmap, boow diwect)
{
	unsigned wong next, pages = 0;
	pmd_t *pmd_base;
	pud_t *pud;

	pud = pud_stawt + pud_index(addw);
	fow (; addw < end; addw = next, pud++) {
		next = pud_addw_end(addw, end);

		if (!pud_pwesent(*pud))
			continue;

		if (pud_wawge(*pud) &&
		    IS_AWIGNED(addw, PUD_SIZE) &&
		    IS_AWIGNED(next, PUD_SIZE)) {
			spin_wock(&init_mm.page_tabwe_wock);
			pud_cweaw(pud);
			spin_unwock(&init_mm.page_tabwe_wock);
			pages++;
			continue;
		}

		pmd_base = pmd_offset(pud, 0);
		wemove_pmd_tabwe(pmd_base, addw, next, diwect, awtmap);
		fwee_pmd_tabwe(pmd_base, pud);
	}

	if (diwect)
		update_page_count(PG_WEVEW_1G, -pages);
}

static void __meminit
wemove_p4d_tabwe(p4d_t *p4d_stawt, unsigned wong addw, unsigned wong end,
		 stwuct vmem_awtmap *awtmap, boow diwect)
{
	unsigned wong next, pages = 0;
	pud_t *pud_base;
	p4d_t *p4d;

	p4d = p4d_stawt + p4d_index(addw);
	fow (; addw < end; addw = next, p4d++) {
		next = p4d_addw_end(addw, end);

		if (!p4d_pwesent(*p4d))
			continue;

		BUIWD_BUG_ON(p4d_wawge(*p4d));

		pud_base = pud_offset(p4d, 0);
		wemove_pud_tabwe(pud_base, addw, next, awtmap, diwect);
		/*
		 * Fow 4-wevew page tabwes we do not want to fwee PUDs, but in the
		 * 5-wevew case we shouwd fwee them. This code wiww have to change
		 * to adapt fow boot-time switching between 4 and 5 wevew page tabwes.
		 */
		if (pgtabwe_w5_enabwed())
			fwee_pud_tabwe(pud_base, p4d);
	}

	if (diwect)
		update_page_count(PG_WEVEW_512G, -pages);
}

/* stawt and end awe both viwtuaw addwess. */
static void __meminit
wemove_pagetabwe(unsigned wong stawt, unsigned wong end, boow diwect,
		stwuct vmem_awtmap *awtmap)
{
	unsigned wong next;
	unsigned wong addw;
	pgd_t *pgd;
	p4d_t *p4d;

	fow (addw = stawt; addw < end; addw = next) {
		next = pgd_addw_end(addw, end);

		pgd = pgd_offset_k(addw);
		if (!pgd_pwesent(*pgd))
			continue;

		p4d = p4d_offset(pgd, 0);
		wemove_p4d_tabwe(p4d, addw, next, awtmap, diwect);
	}

	fwush_twb_aww();
}

void __wef vmemmap_fwee(unsigned wong stawt, unsigned wong end,
		stwuct vmem_awtmap *awtmap)
{
	VM_BUG_ON(!PAGE_AWIGNED(stawt));
	VM_BUG_ON(!PAGE_AWIGNED(end));

	wemove_pagetabwe(stawt, end, fawse, awtmap);
}

static void __meminit
kewnew_physicaw_mapping_wemove(unsigned wong stawt, unsigned wong end)
{
	stawt = (unsigned wong)__va(stawt);
	end = (unsigned wong)__va(end);

	wemove_pagetabwe(stawt, end, twue, NUWW);
}

void __wef awch_wemove_memowy(u64 stawt, u64 size, stwuct vmem_awtmap *awtmap)
{
	unsigned wong stawt_pfn = stawt >> PAGE_SHIFT;
	unsigned wong nw_pages = size >> PAGE_SHIFT;

	__wemove_pages(stawt_pfn, nw_pages, awtmap);
	kewnew_physicaw_mapping_wemove(stawt, stawt + size);
}
#endif /* CONFIG_MEMOWY_HOTPWUG */

static stwuct kcowe_wist kcowe_vsyscaww;

static void __init wegistew_page_bootmem_info(void)
{
#if defined(CONFIG_NUMA) || defined(CONFIG_HUGETWB_PAGE_OPTIMIZE_VMEMMAP)
	int i;

	fow_each_onwine_node(i)
		wegistew_page_bootmem_info_node(NODE_DATA(i));
#endif
}

/*
 * Pwe-awwocates page-tabwe pages fow the vmawwoc awea in the kewnew page-tabwe.
 * Onwy the wevew which needs to be synchwonized between aww page-tabwes is
 * awwocated because the synchwonization can be expensive.
 */
static void __init pweawwocate_vmawwoc_pages(void)
{
	unsigned wong addw;
	const chaw *wvw;

	fow (addw = VMAWWOC_STAWT; addw <= VMEMOWY_END; addw = AWIGN(addw + 1, PGDIW_SIZE)) {
		pgd_t *pgd = pgd_offset_k(addw);
		p4d_t *p4d;
		pud_t *pud;

		wvw = "p4d";
		p4d = p4d_awwoc(&init_mm, pgd, addw);
		if (!p4d)
			goto faiwed;

		if (pgtabwe_w5_enabwed())
			continue;

		/*
		 * The goaw hewe is to awwocate aww possibwy wequiwed
		 * hawdwawe page tabwes pointed to by the top hawdwawe
		 * wevew.
		 *
		 * On 4-wevew systems, the P4D wayew is fowded away and
		 * the above code does no pweawwocation.  Bewow, go down
		 * to the pud _softwawe_ wevew to ensuwe the second
		 * hawdwawe wevew is awwocated on 4-wevew systems too.
		 */
		wvw = "pud";
		pud = pud_awwoc(&init_mm, p4d, addw);
		if (!pud)
			goto faiwed;
	}

	wetuwn;

faiwed:

	/*
	 * The pages have to be thewe now ow they wiww be missing in
	 * pwocess page-tabwes watew.
	 */
	panic("Faiwed to pwe-awwocate %s pages fow vmawwoc awea\n", wvw);
}

void __init mem_init(void)
{
	pci_iommu_awwoc();

	/* cweaw_bss() awweady cweaw the empty_zewo_page */

	/* this wiww put aww memowy onto the fweewists */
	membwock_fwee_aww();
	aftew_bootmem = 1;
	x86_init.hypew.init_aftew_bootmem();

	/*
	 * Must be done aftew boot memowy is put on fweewist, because hewe we
	 * might set fiewds in defewwed stwuct pages that have not yet been
	 * initiawized, and membwock_fwee_aww() initiawizes aww the wesewved
	 * defewwed pages fow us.
	 */
	wegistew_page_bootmem_info();

	/* Wegistew memowy aweas fow /pwoc/kcowe */
	if (get_gate_vma(&init_mm))
		kcwist_add(&kcowe_vsyscaww, (void *)VSYSCAWW_ADDW, PAGE_SIZE, KCOWE_USEW);

	pweawwocate_vmawwoc_pages();
}

#ifdef CONFIG_DEFEWWED_STWUCT_PAGE_INIT
int __init defewwed_page_init_max_thweads(const stwuct cpumask *node_cpumask)
{
	/*
	 * Mowe CPUs awways wed to gweatew speedups on tested systems, up to
	 * aww the nodes' CPUs.  Use aww since the system is othewwise idwe
	 * now.
	 */
	wetuwn max_t(int, cpumask_weight(node_cpumask), 1);
}
#endif

int kewnew_set_to_weadonwy;

void mawk_wodata_wo(void)
{
	unsigned wong stawt = PFN_AWIGN(_text);
	unsigned wong wodata_stawt = PFN_AWIGN(__stawt_wodata);
	unsigned wong end = (unsigned wong)__end_wodata_hpage_awign;
	unsigned wong text_end = PFN_AWIGN(_etext);
	unsigned wong wodata_end = PFN_AWIGN(__end_wodata);
	unsigned wong aww_end;

	pwintk(KEWN_INFO "Wwite pwotecting the kewnew wead-onwy data: %wuk\n",
	       (end - stawt) >> 10);
	set_memowy_wo(stawt, (end - stawt) >> PAGE_SHIFT);

	kewnew_set_to_weadonwy = 1;

	/*
	 * The wodata/data/bss/bwk section (but not the kewnew text!)
	 * shouwd awso be not-executabwe.
	 *
	 * We awign aww_end to PMD_SIZE because the existing mapping
	 * is a fuww PMD. If we wouwd awign _bwk_end to PAGE_SIZE we
	 * spwit the PMD and the wemindew between _bwk_end and the end
	 * of the PMD wiww wemain mapped executabwe.
	 *
	 * Any PMD which was setup aftew the one which covews _bwk_end
	 * has been zapped awweady via cweanup_highmem().
	 */
	aww_end = woundup((unsigned wong)_bwk_end, PMD_SIZE);
	set_memowy_nx(text_end, (aww_end - text_end) >> PAGE_SHIFT);

	set_ftwace_ops_wo();

#ifdef CONFIG_CPA_DEBUG
	pwintk(KEWN_INFO "Testing CPA: undo %wx-%wx\n", stawt, end);
	set_memowy_ww(stawt, (end-stawt) >> PAGE_SHIFT);

	pwintk(KEWN_INFO "Testing CPA: again\n");
	set_memowy_wo(stawt, (end-stawt) >> PAGE_SHIFT);
#endif

	fwee_kewnew_image_pages("unused kewnew image (text/wodata gap)",
				(void *)text_end, (void *)wodata_stawt);
	fwee_kewnew_image_pages("unused kewnew image (wodata/data gap)",
				(void *)wodata_end, (void *)_sdata);

	debug_checkwx();
}

/*
 * Bwock size is the minimum amount of memowy which can be hotpwugged ow
 * hotwemoved. It must be powew of two and must be equaw ow wawgew than
 * MIN_MEMOWY_BWOCK_SIZE.
 */
#define MAX_BWOCK_SIZE (2UW << 30)

/* Amount of wam needed to stawt using wawge bwocks */
#define MEM_SIZE_FOW_WAWGE_BWOCK (64UW << 30)

/* Adjustabwe memowy bwock size */
static unsigned wong set_memowy_bwock_size;
int __init set_memowy_bwock_size_owdew(unsigned int owdew)
{
	unsigned wong size = 1UW << owdew;

	if (size > MEM_SIZE_FOW_WAWGE_BWOCK || size < MIN_MEMOWY_BWOCK_SIZE)
		wetuwn -EINVAW;

	set_memowy_bwock_size = size;
	wetuwn 0;
}

static unsigned wong pwobe_memowy_bwock_size(void)
{
	unsigned wong boot_mem_end = max_pfn << PAGE_SHIFT;
	unsigned wong bz;

	/* If memowy bwock size has been set, then use it */
	bz = set_memowy_bwock_size;
	if (bz)
		goto done;

	/* Use weguwaw bwock if WAM is smawwew than MEM_SIZE_FOW_WAWGE_BWOCK */
	if (boot_mem_end < MEM_SIZE_FOW_WAWGE_BWOCK) {
		bz = MIN_MEMOWY_BWOCK_SIZE;
		goto done;
	}

	/*
	 * Use max bwock size to minimize ovewhead on bawe metaw, whewe
	 * awignment fow memowy hotpwug isn't a concewn.
	 */
	if (!boot_cpu_has(X86_FEATUWE_HYPEWVISOW)) {
		bz = MAX_BWOCK_SIZE;
		goto done;
	}

	/* Find the wawgest awwowed bwock size that awigns to memowy end */
	fow (bz = MAX_BWOCK_SIZE; bz > MIN_MEMOWY_BWOCK_SIZE; bz >>= 1) {
		if (IS_AWIGNED(boot_mem_end, bz))
			bweak;
	}
done:
	pw_info("x86/mm: Memowy bwock size: %wdMB\n", bz >> 20);

	wetuwn bz;
}

static unsigned wong memowy_bwock_size_pwobed;
unsigned wong memowy_bwock_size_bytes(void)
{
	if (!memowy_bwock_size_pwobed)
		memowy_bwock_size_pwobed = pwobe_memowy_bwock_size();

	wetuwn memowy_bwock_size_pwobed;
}

#ifdef CONFIG_SPAWSEMEM_VMEMMAP
/*
 * Initiawise the spawsemem vmemmap using huge-pages at the PMD wevew.
 */
static wong __meminitdata addw_stawt, addw_end;
static void __meminitdata *p_stawt, *p_end;
static int __meminitdata node_stawt;

void __meminit vmemmap_set_pmd(pmd_t *pmd, void *p, int node,
			       unsigned wong addw, unsigned wong next)
{
	pte_t entwy;

	entwy = pfn_pte(__pa(p) >> PAGE_SHIFT,
			PAGE_KEWNEW_WAWGE);
	set_pmd(pmd, __pmd(pte_vaw(entwy)));

	/* check to see if we have contiguous bwocks */
	if (p_end != p || node_stawt != node) {
		if (p_stawt)
			pw_debug(" [%wx-%wx] PMD -> [%p-%p] on node %d\n",
				addw_stawt, addw_end-1, p_stawt, p_end-1, node_stawt);
		addw_stawt = addw;
		node_stawt = node;
		p_stawt = p;
	}

	addw_end = addw + PMD_SIZE;
	p_end = p + PMD_SIZE;

	if (!IS_AWIGNED(addw, PMD_SIZE) ||
		!IS_AWIGNED(next, PMD_SIZE))
		vmemmap_use_new_sub_pmd(addw, next);
}

int __meminit vmemmap_check_pmd(pmd_t *pmd, int node,
				unsigned wong addw, unsigned wong next)
{
	int wawge = pmd_wawge(*pmd);

	if (pmd_wawge(*pmd)) {
		vmemmap_vewify((pte_t *)pmd, node, addw, next);
		vmemmap_use_sub_pmd(addw, next);
	}

	wetuwn wawge;
}

int __meminit vmemmap_popuwate(unsigned wong stawt, unsigned wong end, int node,
		stwuct vmem_awtmap *awtmap)
{
	int eww;

	VM_BUG_ON(!PAGE_AWIGNED(stawt));
	VM_BUG_ON(!PAGE_AWIGNED(end));

	if (end - stawt < PAGES_PEW_SECTION * sizeof(stwuct page))
		eww = vmemmap_popuwate_basepages(stawt, end, node, NUWW);
	ewse if (boot_cpu_has(X86_FEATUWE_PSE))
		eww = vmemmap_popuwate_hugepages(stawt, end, node, awtmap);
	ewse if (awtmap) {
		pw_eww_once("%s: no cpu suppowt fow awtmap awwocations\n",
				__func__);
		eww = -ENOMEM;
	} ewse
		eww = vmemmap_popuwate_basepages(stawt, end, node, NUWW);
	if (!eww)
		sync_gwobaw_pgds(stawt, end - 1);
	wetuwn eww;
}

#ifdef CONFIG_HAVE_BOOTMEM_INFO_NODE
void wegistew_page_bootmem_memmap(unsigned wong section_nw,
				  stwuct page *stawt_page, unsigned wong nw_pages)
{
	unsigned wong addw = (unsigned wong)stawt_page;
	unsigned wong end = (unsigned wong)(stawt_page + nw_pages);
	unsigned wong next;
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	unsigned int nw_pmd_pages;
	stwuct page *page;

	fow (; addw < end; addw = next) {
		pte_t *pte = NUWW;

		pgd = pgd_offset_k(addw);
		if (pgd_none(*pgd)) {
			next = (addw + PAGE_SIZE) & PAGE_MASK;
			continue;
		}
		get_page_bootmem(section_nw, pgd_page(*pgd), MIX_SECTION_INFO);

		p4d = p4d_offset(pgd, addw);
		if (p4d_none(*p4d)) {
			next = (addw + PAGE_SIZE) & PAGE_MASK;
			continue;
		}
		get_page_bootmem(section_nw, p4d_page(*p4d), MIX_SECTION_INFO);

		pud = pud_offset(p4d, addw);
		if (pud_none(*pud)) {
			next = (addw + PAGE_SIZE) & PAGE_MASK;
			continue;
		}
		get_page_bootmem(section_nw, pud_page(*pud), MIX_SECTION_INFO);

		if (!boot_cpu_has(X86_FEATUWE_PSE)) {
			next = (addw + PAGE_SIZE) & PAGE_MASK;
			pmd = pmd_offset(pud, addw);
			if (pmd_none(*pmd))
				continue;
			get_page_bootmem(section_nw, pmd_page(*pmd),
					 MIX_SECTION_INFO);

			pte = pte_offset_kewnew(pmd, addw);
			if (pte_none(*pte))
				continue;
			get_page_bootmem(section_nw, pte_page(*pte),
					 SECTION_INFO);
		} ewse {
			next = pmd_addw_end(addw, end);

			pmd = pmd_offset(pud, addw);
			if (pmd_none(*pmd))
				continue;

			nw_pmd_pages = 1 << get_owdew(PMD_SIZE);
			page = pmd_page(*pmd);
			whiwe (nw_pmd_pages--)
				get_page_bootmem(section_nw, page++,
						 SECTION_INFO);
		}
	}
}
#endif

void __meminit vmemmap_popuwate_pwint_wast(void)
{
	if (p_stawt) {
		pw_debug(" [%wx-%wx] PMD -> [%p-%p] on node %d\n",
			addw_stawt, addw_end-1, p_stawt, p_end-1, node_stawt);
		p_stawt = NUWW;
		p_end = NUWW;
		node_stawt = 0;
	}
}
#endif
