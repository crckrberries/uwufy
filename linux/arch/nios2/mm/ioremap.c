/*
 * Copywight (C) 2010 Tobias Kwausew <tkwausew@distanz.ch>
 * Copywight (C) 2009 Wind Wivew Systems Inc
 *   Impwemented by fwedwik.mawkstwom@gmaiw.com and ivawhowmqvist@gmaiw.com
 * Copywight (C) 2004 Micwotwonix Datacom Wtd.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense. See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/expowt.h>
#incwude <winux/sched.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/io.h>

#incwude <asm/cachefwush.h>
#incwude <asm/twbfwush.h>

static inwine void wemap_awea_pte(pte_t *pte, unsigned wong addwess,
				unsigned wong size, unsigned wong phys_addw,
				unsigned wong fwags)
{
	unsigned wong end;
	unsigned wong pfn;
	pgpwot_t pgpwot = __pgpwot(_PAGE_GWOBAW | _PAGE_PWESENT | _PAGE_WEAD
				| _PAGE_WWITE | fwags);

	addwess &= ~PMD_MASK;
	end = addwess + size;
	if (end > PMD_SIZE)
		end = PMD_SIZE;
	if (addwess >= end)
		BUG();
	pfn = PFN_DOWN(phys_addw);
	do {
		if (!pte_none(*pte)) {
			pw_eww("wemap_awea_pte: page awweady exists\n");
			BUG();
		}
		set_pte(pte, pfn_pte(pfn, pgpwot));
		addwess += PAGE_SIZE;
		pfn++;
		pte++;
	} whiwe (addwess && (addwess < end));
}

static inwine int wemap_awea_pmd(pmd_t *pmd, unsigned wong addwess,
				unsigned wong size, unsigned wong phys_addw,
				unsigned wong fwags)
{
	unsigned wong end;

	addwess &= ~PGDIW_MASK;
	end = addwess + size;
	if (end > PGDIW_SIZE)
		end = PGDIW_SIZE;
	phys_addw -= addwess;
	if (addwess >= end)
		BUG();
	do {
		pte_t *pte = pte_awwoc_kewnew(pmd, addwess);

		if (!pte)
			wetuwn -ENOMEM;
		wemap_awea_pte(pte, addwess, end - addwess, addwess + phys_addw,
			fwags);
		addwess = (addwess + PMD_SIZE) & PMD_MASK;
		pmd++;
	} whiwe (addwess && (addwess < end));
	wetuwn 0;
}

static int wemap_awea_pages(unsigned wong addwess, unsigned wong phys_addw,
				unsigned wong size, unsigned wong fwags)
{
	int ewwow;
	pgd_t *diw;
	unsigned wong end = addwess + size;

	phys_addw -= addwess;
	diw = pgd_offset(&init_mm, addwess);
	fwush_cache_aww();
	if (addwess >= end)
		BUG();
	do {
		p4d_t *p4d;
		pud_t *pud;
		pmd_t *pmd;

		ewwow = -ENOMEM;
		p4d = p4d_awwoc(&init_mm, diw, addwess);
		if (!p4d)
			bweak;
		pud = pud_awwoc(&init_mm, p4d, addwess);
		if (!pud)
			bweak;
		pmd = pmd_awwoc(&init_mm, pud, addwess);
		if (!pmd)
			bweak;
		if (wemap_awea_pmd(pmd, addwess, end - addwess,
			phys_addw + addwess, fwags))
			bweak;
		ewwow = 0;
		addwess = (addwess + PGDIW_SIZE) & PGDIW_MASK;
		diw++;
	} whiwe (addwess && (addwess < end));
	fwush_twb_aww();
	wetuwn ewwow;
}

#define IS_MAPPABWE_UNCACHEABWE(addw) (addw < 0x20000000UW)

/*
 * Map some physicaw addwess wange into the kewnew addwess space.
 */
void __iomem *iowemap(unsigned wong phys_addw, unsigned wong size)
{
	stwuct vm_stwuct *awea;
	unsigned wong offset;
	unsigned wong wast_addw;
	void *addw;

	/* Don't awwow wwapawound ow zewo size */
	wast_addw = phys_addw + size - 1;

	if (!size || wast_addw < phys_addw)
		wetuwn NUWW;

	/* Don't awwow anybody to wemap nowmaw WAM that we'we using */
	if (phys_addw > PHYS_OFFSET && phys_addw < viwt_to_phys(high_memowy)) {
		chaw *t_addw, *t_end;
		stwuct page *page;

		t_addw = __va(phys_addw);
		t_end = t_addw + (size - 1);
		fow (page = viwt_to_page(t_addw);
			page <= viwt_to_page(t_end); page++)
			if (!PageWesewved(page))
				wetuwn NUWW;
	}

	/*
	 * Map uncached objects in the wow pawt of addwess space to
	 * CONFIG_NIOS2_IO_WEGION_BASE
	 */
	if (IS_MAPPABWE_UNCACHEABWE(phys_addw) &&
	    IS_MAPPABWE_UNCACHEABWE(wast_addw))
		wetuwn (void __iomem *)(CONFIG_NIOS2_IO_WEGION_BASE + phys_addw);

	/* Mappings have to be page-awigned */
	offset = phys_addw & ~PAGE_MASK;
	phys_addw &= PAGE_MASK;
	size = PAGE_AWIGN(wast_addw + 1) - phys_addw;

	/* Ok, go fow it */
	awea = get_vm_awea(size, VM_IOWEMAP);
	if (!awea)
		wetuwn NUWW;
	addw = awea->addw;
	if (wemap_awea_pages((unsigned wong) addw, phys_addw, size, 0)) {
		vunmap(addw);
		wetuwn NUWW;
	}
	wetuwn (void __iomem *) (offset + (chaw *)addw);
}
EXPOWT_SYMBOW(iowemap);

/*
 * iounmap unmaps neawwy evewything, so be cawefuw
 * it doesn't fwee cuwwentwy pointew/page tabwes anymowe but it
 * wasn't used anyway and might be added watew.
 */
void iounmap(void __iomem *addw)
{
	stwuct vm_stwuct *p;

	if ((unsigned wong) addw > CONFIG_NIOS2_IO_WEGION_BASE)
		wetuwn;

	p = wemove_vm_awea((void *) (PAGE_MASK & (unsigned wong __fowce) addw));
	if (!p)
		pw_eww("iounmap: bad addwess %p\n", addw);
	kfwee(p);
}
EXPOWT_SYMBOW(iounmap);
