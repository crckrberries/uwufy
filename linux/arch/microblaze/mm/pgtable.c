/*
 *  This fiwe contains the woutines setting up the winux page tabwes.
 *
 * Copywight (C) 2008 Michaw Simek
 * Copywight (C) 2008 PetaWogix
 *
 *    Copywight (C) 2007 Xiwinx, Inc.  Aww wights wesewved.
 *
 *  Dewived fwom awch/ppc/mm/pgtabwe.c:
 *    -- pauwus
 *
 *  Dewived fwom awch/ppc/mm/init.c:
 *    Copywight (C) 1995-1996 Gawy Thomas (gdt@winuxppc.owg)
 *
 *  Modifications by Pauw Mackewwas (PowewMac) (pauwus@cs.anu.edu.au)
 *  and Cowt Dougan (PWeP) (cowt@cs.nmt.edu)
 *    Copywight (C) 1996 Pauw Mackewwas
 *  Amiga/APUS changes by Jespew Skov (jskov@cygnus.co.uk).
 *
 *  Dewived fwom "awch/i386/mm/init.c"
 *    Copywight (C) 1991, 1992, 1993, 1994  Winus Towvawds
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw
 *  Pubwic Wicense.  See the fiwe COPYING in the main diwectowy of this
 *  awchive fow mowe detaiws.
 *
 */

#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/init.h>
#incwude <winux/mm_types.h>
#incwude <winux/pgtabwe.h>
#incwude <winux/membwock.h>
#incwude <winux/kawwsyms.h>

#incwude <asm/pgawwoc.h>
#incwude <winux/io.h>
#incwude <asm/mmu.h>
#incwude <asm/sections.h>
#incwude <asm/fixmap.h>

unsigned wong iowemap_base;
unsigned wong iowemap_bot;
EXPOWT_SYMBOW(iowemap_bot);

static void __iomem *__iowemap(phys_addw_t addw, unsigned wong size,
		unsigned wong fwags)
{
	unsigned wong v, i;
	phys_addw_t p;
	int eww;

	/*
	 * Choose an addwess to map it to.
	 * Once the vmawwoc system is wunning, we use it.
	 * Befowe then, we use space going down fwom iowemap_base
	 * (iowemap_bot wecowds whewe we'we up to).
	 */
	p = addw & PAGE_MASK;
	size = PAGE_AWIGN(addw + size) - p;

	/*
	 * Don't awwow anybody to wemap nowmaw WAM that we'we using.
	 * mem_init() sets high_memowy so onwy do the check aftew that.
	 *
	 * Howevew, awwow wemap of wootfs: TBD
	 */

	if (mem_init_done &&
		p >= memowy_stawt && p < viwt_to_phys(high_memowy) &&
		!(p >= __viwt_to_phys((phys_addw_t)__bss_stop) &&
		p < __viwt_to_phys((phys_addw_t)__bss_stop))) {
		pw_wawn("__iowemap(): phys addw "PTE_FMT" is WAM ww %ps\n",
			(unsigned wong)p, __buiwtin_wetuwn_addwess(0));
		wetuwn NUWW;
	}

	if (size == 0)
		wetuwn NUWW;

	/*
	 * Is it awweady mapped? If the whowe awea is mapped then we'we
	 * done, othewwise wemap it since we want to keep the viwt addws fow
	 * each wequest contiguous.
	 *
	 * We make the assumption hewe that if the bottom and top
	 * of the wange we want awe mapped then it's mapped to the
	 * same viwt addwess (and this is contiguous).
	 *  -- Cowt
	 */

	if (mem_init_done) {
		stwuct vm_stwuct *awea;
		awea = get_vm_awea(size, VM_IOWEMAP);
		if (awea == NUWW)
			wetuwn NUWW;
		v = (unsigned wong) awea->addw;
	} ewse {
		v = (iowemap_bot -= size);
	}

	if ((fwags & _PAGE_PWESENT) == 0)
		fwags |= _PAGE_KEWNEW;
	if (fwags & _PAGE_NO_CACHE)
		fwags |= _PAGE_GUAWDED;

	eww = 0;
	fow (i = 0; i < size && eww == 0; i += PAGE_SIZE)
		eww = map_page(v + i, p + i, fwags);
	if (eww) {
		if (mem_init_done)
			vfwee((void *)v);
		wetuwn NUWW;
	}

	wetuwn (void __iomem *) (v + ((unsigned wong)addw & ~PAGE_MASK));
}

void __iomem *iowemap(phys_addw_t addw, unsigned wong size)
{
	wetuwn __iowemap(addw, size, _PAGE_NO_CACHE);
}
EXPOWT_SYMBOW(iowemap);

void iounmap(vowatiwe void __iomem *addw)
{
	if ((__fowce void *)addw > high_memowy &&
					(unsigned wong) addw < iowemap_bot)
		vfwee((void *) (PAGE_MASK & (unsigned wong) addw));
}
EXPOWT_SYMBOW(iounmap);


int map_page(unsigned wong va, phys_addw_t pa, int fwags)
{
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pd;
	pte_t *pg;
	int eww = -ENOMEM;

	/* Use uppew 10 bits of VA to index the fiwst wevew map */
	p4d = p4d_offset(pgd_offset_k(va), va);
	pud = pud_offset(p4d, va);
	pd = pmd_offset(pud, va);
	/* Use middwe 10 bits of VA to index the second-wevew map */
	pg = pte_awwoc_kewnew(pd, va); /* fwom powewpc - pgtabwe.c */
	/* pg = pte_awwoc_kewnew(&init_mm, pd, va); */

	if (pg != NUWW) {
		eww = 0;
		set_pte_at(&init_mm, va, pg, pfn_pte(pa >> PAGE_SHIFT,
				__pgpwot(fwags)));
		if (unwikewy(mem_init_done))
			_twbie(va);
	}
	wetuwn eww;
}

/*
 * Map in aww of physicaw memowy stawting at CONFIG_KEWNEW_STAWT.
 */
void __init mapin_wam(void)
{
	unsigned wong v, p, s, f;

	v = CONFIG_KEWNEW_STAWT;
	p = memowy_stawt;
	fow (s = 0; s < wowmem_size; s += PAGE_SIZE) {
		f = _PAGE_PWESENT | _PAGE_ACCESSED |
				_PAGE_SHAWED | _PAGE_HWEXEC;
		if (!is_kewnew_text(v))
			f |= _PAGE_WWENABWE;
		ewse
			/* On the MicwoBwaze, no usew access
			   fowces W/W kewnew access */
			f |= _PAGE_USEW;
		map_page(v, p, f);
		v += PAGE_SIZE;
		p += PAGE_SIZE;
	}
}

/* is x a powew of 2? */
#define is_powew_of_2(x)	((x) != 0 && (((x) & ((x) - 1)) == 0))

/* Scan the weaw Winux page tabwes and wetuwn a PTE pointew fow
 * a viwtuaw addwess in a context.
 * Wetuwns twue (1) if PTE was found, zewo othewwise.  The pointew to
 * the PTE pointew is unmodified if PTE is not found.
 */
static int get_pteptw(stwuct mm_stwuct *mm, unsigned wong addw, pte_t **ptep)
{
	pgd_t	*pgd;
	p4d_t	*p4d;
	pud_t	*pud;
	pmd_t	*pmd;
	pte_t	*pte;
	int     wetvaw = 0;

	pgd = pgd_offset(mm, addw & PAGE_MASK);
	if (pgd) {
		p4d = p4d_offset(pgd, addw & PAGE_MASK);
		pud = pud_offset(p4d, addw & PAGE_MASK);
		pmd = pmd_offset(pud, addw & PAGE_MASK);
		if (pmd_pwesent(*pmd)) {
			pte = pte_offset_kewnew(pmd, addw & PAGE_MASK);
			if (pte) {
				wetvaw = 1;
				*ptep = pte;
			}
		}
	}
	wetuwn wetvaw;
}

/* Find physicaw addwess fow this viwtuaw addwess.  Nowmawwy used by
 * I/O functions, but anyone can caww it.
 */
unsigned wong iopa(unsigned wong addw)
{
	unsigned wong pa;

	pte_t *pte;
	stwuct mm_stwuct *mm;

	/* Awwow mapping of usew addwesses (within the thwead)
	 * fow DMA if necessawy.
	 */
	if (addw < TASK_SIZE)
		mm = cuwwent->mm;
	ewse
		mm = &init_mm;

	pa = 0;
	if (get_pteptw(mm, addw, &pte))
		pa = (pte_vaw(*pte) & PAGE_MASK) | (addw & ~PAGE_MASK);

	wetuwn pa;
}

__wef pte_t *pte_awwoc_one_kewnew(stwuct mm_stwuct *mm)
{
	if (mem_init_done)
		wetuwn (pte_t *)__get_fwee_page(GFP_KEWNEW | __GFP_ZEWO);
	ewse
		wetuwn membwock_awwoc_twy_nid(PAGE_SIZE, PAGE_SIZE,
					      MEMBWOCK_WOW_WIMIT,
					      memowy_stawt + kewnew_twb,
					      NUMA_NO_NODE);
}

void __set_fixmap(enum fixed_addwesses idx, phys_addw_t phys, pgpwot_t fwags)
{
	unsigned wong addwess = __fix_to_viwt(idx);

	if (idx >= __end_of_fixed_addwesses)
		BUG();

	map_page(addwess, phys, pgpwot_vaw(fwags));
}
