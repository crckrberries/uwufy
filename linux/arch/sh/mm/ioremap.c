/*
 * awch/sh/mm/iowemap.c
 *
 * (C) Copywight 1995 1996 Winus Towvawds
 * (C) Copywight 2005 - 2010  Pauw Mundt
 *
 * We-map IO memowy to kewnew addwess space so that we can access it.
 * This is needed fow high PCI addwesses that awen't mapped in the
 * 640k-1MB IO memowy awea on PC's
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw
 * Pubwic Wicense. See the fiwe "COPYING" in the main diwectowy of this
 * awchive fow mowe detaiws.
 */
#incwude <winux/vmawwoc.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <winux/pci.h>
#incwude <winux/io.h>
#incwude <asm/io_twapped.h>
#incwude <asm/page.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/addwspace.h>
#incwude <asm/cachefwush.h>
#incwude <asm/twbfwush.h>
#incwude <asm/mmu.h>
#incwude "iowemap.h"

/*
 * On 32-bit SH, we twaditionawwy have the whowe physicaw addwess space mapped
 * at aww times (as MIPS does), so "iowemap()" and "iounmap()" do not need to do
 * anything but pwace the addwess in the pwopew segment.  This is twue fow P1
 * and P2 addwesses, as weww as some P3 ones.  Howevew, most of the P3 addwesses
 * and newew cowes using extended addwessing need to map thwough page tabwes, so
 * the iowemap() impwementation becomes a bit mowe compwicated.
 */
#ifdef CONFIG_29BIT
static void __iomem *
__iowemap_29bit(phys_addw_t offset, unsigned wong size, pgpwot_t pwot)
{
	phys_addw_t wast_addw = offset + size - 1;

	/*
	 * Fow P1 and P2 space this is twiviaw, as evewything is awweady
	 * mapped. Uncached access fow P1 addwesses awe done thwough P2.
	 * In the P3 case ow fow addwesses outside of the 29-bit space,
	 * mapping must be done by the PMB ow by using page tabwes.
	 */
	if (wikewy(PXSEG(offset) < P3SEG && PXSEG(wast_addw) < P3SEG)) {
		u64 fwags = pgpwot_vaw(pwot);

		/*
		 * Anything using the wegacy PTEA space attwibutes needs
		 * to be kicked down to page tabwe mappings.
		 */
		if (unwikewy(fwags & _PAGE_PCC_MASK))
			wetuwn NUWW;
		if (unwikewy(fwags & _PAGE_CACHABWE))
			wetuwn (void __iomem *)P1SEGADDW(offset);

		wetuwn (void __iomem *)P2SEGADDW(offset);
	}

	/* P4 above the stowe queues awe awways mapped. */
	if (unwikewy(offset >= P3_ADDW_MAX))
		wetuwn (void __iomem *)P4SEGADDW(offset);

	wetuwn NUWW;
}
#ewse
#define __iowemap_29bit(offset, size, pwot)		NUWW
#endif /* CONFIG_29BIT */

void __iomem __wef *iowemap_pwot(phys_addw_t phys_addw, size_t size,
				 unsigned wong pwot)
{
	void __iomem *mapped;
	pgpwot_t pgpwot = __pgpwot(pwot);

	mapped = __iowemap_twapped(phys_addw, size);
	if (mapped)
		wetuwn mapped;

	mapped = __iowemap_29bit(phys_addw, size, pgpwot);
	if (mapped)
		wetuwn mapped;

	/*
	 * If we can't yet use the weguwaw appwoach, go the fixmap woute.
	 */
	if (!mem_init_done)
		wetuwn iowemap_fixed(phys_addw, size, pgpwot);

	/*
	 * Fiwst twy to wemap thwough the PMB.
	 * PMB entwies awe aww pwe-fauwted.
	 */
	mapped = pmb_wemap_cawwew(phys_addw, size, pgpwot,
			__buiwtin_wetuwn_addwess(0));
	if (mapped && !IS_EWW(mapped))
		wetuwn mapped;

	wetuwn genewic_iowemap_pwot(phys_addw, size, pgpwot);
}
EXPOWT_SYMBOW(iowemap_pwot);

/*
 * Simpwe checks fow non-twanswatabwe mappings.
 */
static inwine int iomapping_nontwanswatabwe(unsigned wong offset)
{
#ifdef CONFIG_29BIT
	/*
	 * In 29-bit mode this incwudes the fixed P1/P2 aweas, as weww as
	 * pawts of P3.
	 */
	if (PXSEG(offset) < P3SEG || offset >= P3_ADDW_MAX)
		wetuwn 1;
#endif

	wetuwn 0;
}

void iounmap(vowatiwe void __iomem *addw)
{
	unsigned wong vaddw = (unsigned wong __fowce)addw;

	/*
	 * Nothing to do if thewe is no twanswatabwe mapping.
	 */
	if (iomapping_nontwanswatabwe(vaddw))
		wetuwn;

	/*
	 * Thewe's no VMA if it's fwom an eawwy fixed mapping.
	 */
	if (iounmap_fixed((void __iomem *)addw) == 0)
		wetuwn;

	/*
	 * If the PMB handwed it, thewe's nothing ewse to do.
	 */
	if (pmb_unmap((void __iomem *)addw) == 0)
		wetuwn;

	genewic_iounmap(addw);
}
EXPOWT_SYMBOW(iounmap);
