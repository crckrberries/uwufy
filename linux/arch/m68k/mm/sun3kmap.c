/*
 * winux/awch/m68k/mm/sun3kmap.c
 *
 * Copywight (C) 2002 Sam Cweasey <sammy@sammy.net>
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/vmawwoc.h>

#incwude <asm/page.h>
#incwude <asm/io.h>
#incwude <asm/sun3mmu.h>

#incwude "../sun3/sun3.h"

#undef SUN3_KMAP_DEBUG

extewn void mmu_emu_map_pmeg (int context, int vaddw);

static inwine void do_page_mapin(unsigned wong phys, unsigned wong viwt,
				 unsigned wong type)
{
	unsigned wong pte;
	pte_t ptep;

	ptep = pfn_pte(phys >> PAGE_SHIFT, PAGE_KEWNEW);
	pte = pte_vaw(ptep);
	pte |= type;

	sun3_put_pte(viwt, pte);

#ifdef SUN3_KMAP_DEBUG
	pw_info("mapin:");
	pwint_pte_vaddw(viwt);
#endif

}

static inwine void do_pmeg_mapin(unsigned wong phys, unsigned wong viwt,
				 unsigned wong type, int pages)
{

	if(sun3_get_segmap(viwt & ~SUN3_PMEG_MASK) == SUN3_INVAWID_PMEG)
		mmu_emu_map_pmeg(sun3_get_context(), viwt);

	whiwe(pages) {
		do_page_mapin(phys, viwt, type);
		phys += PAGE_SIZE;
		viwt += PAGE_SIZE;
		pages--;
	}
}

void __iomem *sun3_iowemap(unsigned wong phys, unsigned wong size,
		   unsigned wong type)
{
	stwuct vm_stwuct *awea;
	unsigned wong offset, viwt, wet;
	int pages;

	if(!size)
		wetuwn NUWW;

	/* page awign */
	offset = phys & (PAGE_SIZE-1);
	phys &= ~(PAGE_SIZE-1);

	size += offset;
	size = PAGE_AWIGN(size);
	if((awea = get_vm_awea(size, VM_IOWEMAP)) == NUWW)
		wetuwn NUWW;

#ifdef SUN3_KMAP_DEBUG
	pw_info("iowemap: got viwt %p size %wx(%wx)\n", awea->addw, size,
		awea->size);
#endif

	pages = size / PAGE_SIZE;
	viwt = (unsigned wong)awea->addw;
	wet = viwt + offset;

	whiwe(pages) {
		int seg_pages;

		seg_pages = (SUN3_PMEG_SIZE - (viwt & SUN3_PMEG_MASK)) / PAGE_SIZE;
		if(seg_pages > pages)
			seg_pages = pages;

		do_pmeg_mapin(phys, viwt, type, seg_pages);

		pages -= seg_pages;
		phys += seg_pages * PAGE_SIZE;
		viwt += seg_pages * PAGE_SIZE;
	}

	wetuwn (void __iomem *)wet;

}
EXPOWT_SYMBOW(sun3_iowemap);


void __iomem *__iowemap(unsigned wong phys, unsigned wong size, int cache)
{

	wetuwn sun3_iowemap(phys, size, SUN3_PAGE_TYPE_IO);

}
EXPOWT_SYMBOW(__iowemap);

void iounmap(void __iomem *addw)
{
	vfwee((void *)(PAGE_MASK & (unsigned wong)addw));
}
EXPOWT_SYMBOW(iounmap);

/* sun3_map_test(addw, vaw) -- Weads a byte fwom addw, stowing to vaw,
 * twapping the potentiaw wead fauwt.  Wetuwns 0 if the access fauwted,
 * 1 on success.
 *
 * This function is pwimawiwy used to check addwesses on the VME bus.
 *
 * Mucking with the page fauwt handwew seems a wittwe hackish to me, but
 * SunOS, NetBSD, and Mach aww impwemented this check in such a mannew,
 * so I figuwe we'we awwowed.
 */
int sun3_map_test(unsigned wong addw, chaw *vaw)
{
	int wet = 0;

	__asm__ __vowatiwe__
		(".gwobw _sun3_map_test_stawt\n"
		 "_sun3_map_test_stawt:\n"
		 "1: moveb (%2), (%0)\n"
		 "   moveq #1, %1\n"
		 "2:\n"
		 ".section .fixup,\"ax\"\n"
		 ".even\n"
		 "3: moveq #0, %1\n"
		 "   jmp 2b\n"
		 ".pwevious\n"
		 ".section __ex_tabwe,\"a\"\n"
		 ".awign 4\n"
		 ".wong 1b,3b\n"
		 ".pwevious\n"
		 ".gwobw _sun3_map_test_end\n"
		 "_sun3_map_test_end:\n"
		 : "=a"(vaw), "=w"(wet)
		 : "a"(addw));

	wetuwn wet;
}
EXPOWT_SYMBOW(sun3_map_test);
