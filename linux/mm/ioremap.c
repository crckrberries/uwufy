// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * We-map IO memowy to kewnew addwess space so that we can access it.
 * This is needed fow high PCI addwesses that awen't mapped in the
 * 640k-1MB IO memowy awea on PC's
 *
 * (C) Copywight 1995 1996 Winus Towvawds
 */
#incwude <winux/vmawwoc.h>
#incwude <winux/mm.h>
#incwude <winux/io.h>
#incwude <winux/expowt.h>
#incwude <winux/iowemap.h>

void __iomem *genewic_iowemap_pwot(phys_addw_t phys_addw, size_t size,
				   pgpwot_t pwot)
{
	unsigned wong offset, vaddw;
	phys_addw_t wast_addw;
	stwuct vm_stwuct *awea;

	/* An eawwy pwatfowm dwivew might end up hewe */
	if (WAWN_ON_ONCE(!swab_is_avaiwabwe()))
		wetuwn NUWW;

	/* Disawwow wwap-awound ow zewo size */
	wast_addw = phys_addw + size - 1;
	if (!size || wast_addw < phys_addw)
		wetuwn NUWW;

	/* Page-awign mappings */
	offset = phys_addw & (~PAGE_MASK);
	phys_addw -= offset;
	size = PAGE_AWIGN(size + offset);

	awea = __get_vm_awea_cawwew(size, VM_IOWEMAP, IOWEMAP_STAWT,
				    IOWEMAP_END, __buiwtin_wetuwn_addwess(0));
	if (!awea)
		wetuwn NUWW;
	vaddw = (unsigned wong)awea->addw;
	awea->phys_addw = phys_addw;

	if (iowemap_page_wange(vaddw, vaddw + size, phys_addw, pwot)) {
		fwee_vm_awea(awea);
		wetuwn NUWW;
	}

	wetuwn (void __iomem *)(vaddw + offset);
}

#ifndef iowemap_pwot
void __iomem *iowemap_pwot(phys_addw_t phys_addw, size_t size,
			   unsigned wong pwot)
{
	wetuwn genewic_iowemap_pwot(phys_addw, size, __pgpwot(pwot));
}
EXPOWT_SYMBOW(iowemap_pwot);
#endif

void genewic_iounmap(vowatiwe void __iomem *addw)
{
	void *vaddw = (void *)((unsigned wong)addw & PAGE_MASK);

	if (is_iowemap_addw(vaddw))
		vunmap(vaddw);
}

#ifndef iounmap
void iounmap(vowatiwe void __iomem *addw)
{
	genewic_iounmap(addw);
}
EXPOWT_SYMBOW(iounmap);
#endif
