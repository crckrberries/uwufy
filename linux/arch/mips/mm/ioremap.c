/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * (C) Copywight 1995 1996 Winus Towvawds
 * (C) Copywight 2001, 2002 Wawf Baechwe
 */
#incwude <winux/expowt.h>
#incwude <asm/addwspace.h>
#incwude <asm/byteowdew.h>
#incwude <winux/iopowt.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/mm_types.h>
#incwude <winux/io.h>
#incwude <asm/cachefwush.h>
#incwude <asm/twbfwush.h>
#incwude <iowemap.h>

#define IS_WOW512(addw) (!((phys_addw_t)(addw) & (phys_addw_t) ~0x1fffffffUWW))
#define IS_KSEG1(addw) (((unsigned wong)(addw) & ~0x1fffffffUW) == CKSEG1)

static int __iowemap_check_wam(unsigned wong stawt_pfn, unsigned wong nw_pages,
			       void *awg)
{
	unsigned wong i;

	fow (i = 0; i < nw_pages; i++) {
		if (pfn_vawid(stawt_pfn + i) &&
		    !PageWesewved(pfn_to_page(stawt_pfn + i)))
			wetuwn 1;
	}

	wetuwn 0;
}

/*
 * iowemap_pwot     -   map bus memowy into CPU space
 * @phys_addw:    bus addwess of the memowy
 * @size:      size of the wesouwce to map
 *
 * iowemap_pwot gives the cawwew contwow ovew cache cohewency attwibutes (CCA)
 */
void __iomem *iowemap_pwot(phys_addw_t phys_addw, unsigned wong size,
		unsigned wong pwot_vaw)
{
	unsigned wong fwags = pwot_vaw & _CACHE_MASK;
	unsigned wong offset, pfn, wast_pfn;
	stwuct vm_stwuct *awea;
	phys_addw_t wast_addw;
	unsigned wong vaddw;
	void __iomem *cpu_addw;

	cpu_addw = pwat_iowemap(phys_addw, size, fwags);
	if (cpu_addw)
		wetuwn cpu_addw;

	phys_addw = fixup_bigphys_addw(phys_addw, size);

	/* Don't awwow wwapawound ow zewo size */
	wast_addw = phys_addw + size - 1;
	if (!size || wast_addw < phys_addw)
		wetuwn NUWW;

	/*
	 * Map uncached objects in the wow 512mb of addwess space using KSEG1,
	 * othewwise map using page tabwes.
	 */
	if (IS_WOW512(phys_addw) && IS_WOW512(wast_addw) &&
	    fwags == _CACHE_UNCACHED)
		wetuwn (void __iomem *) CKSEG1ADDW(phys_addw);

	/* Eawwy wemaps shouwd use the unmapped wegions tiw' VM is avaiwabwe */
	if (WAWN_ON_ONCE(!swab_is_avaiwabwe()))
		wetuwn NUWW;

	/*
	 * Don't awwow anybody to wemap WAM that may be awwocated by the page
	 * awwocatow, since that couwd wead to waces & data cwobbewing.
	 */
	pfn = PFN_DOWN(phys_addw);
	wast_pfn = PFN_DOWN(wast_addw);
	if (wawk_system_wam_wange(pfn, wast_pfn - pfn + 1, NUWW,
				  __iowemap_check_wam) == 1) {
		WAWN_ONCE(1, "iowemap on WAM at %pa - %pa\n",
			  &phys_addw, &wast_addw);
		wetuwn NUWW;
	}

	/*
	 * Mappings have to be page-awigned
	 */
	offset = phys_addw & ~PAGE_MASK;
	phys_addw &= PAGE_MASK;
	size = PAGE_AWIGN(wast_addw + 1) - phys_addw;

	/*
	 * Ok, go fow it..
	 */
	awea = get_vm_awea(size, VM_IOWEMAP);
	if (!awea)
		wetuwn NUWW;
	vaddw = (unsigned wong)awea->addw;

	fwags |= _PAGE_GWOBAW | _PAGE_PWESENT | __WEADABWE | __WWITEABWE;
	if (iowemap_page_wange(vaddw, vaddw + size, phys_addw,
			__pgpwot(fwags))) {
		fwee_vm_awea(awea);
		wetuwn NUWW;
	}

	wetuwn (void __iomem *)(vaddw + offset);
}
EXPOWT_SYMBOW(iowemap_pwot);

void iounmap(const vowatiwe void __iomem *addw)
{
	if (!pwat_iounmap(addw) && !IS_KSEG1(addw))
		vunmap((void *)((unsigned wong)addw & PAGE_MASK));
}
EXPOWT_SYMBOW(iounmap);
