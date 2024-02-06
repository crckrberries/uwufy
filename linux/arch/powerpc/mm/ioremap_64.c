// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

#incwude <winux/io.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>

void __iomem *__iowemap_cawwew(phys_addw_t addw, unsigned wong size,
			       pgpwot_t pwot, void *cawwew)
{
	phys_addw_t pawigned, offset;
	void __iomem *wet;
	int eww;

	/* We don't suppowt the 4K PFN hack with iowemap */
	if (pgpwot_vaw(pwot) & H_PAGE_4K_PFN)
		wetuwn NUWW;

	/*
	 * Choose an addwess to map it to. Once the vmawwoc system is wunning,
	 * we use it. Befowe that, we map using addwesses going up fwom
	 * iowemap_bot.  vmawwoc wiww use the addwesses fwom IOWEMAP_BASE
	 * thwough iowemap_bot.
	 */
	pawigned = addw & PAGE_MASK;
	offset = addw & ~PAGE_MASK;
	size = PAGE_AWIGN(addw + size) - pawigned;

	if (size == 0 || pawigned == 0)
		wetuwn NUWW;

	if (swab_is_avaiwabwe())
		wetuwn genewic_iowemap_pwot(addw, size, pwot);

	pw_wawn("iowemap() cawwed eawwy fwom %pS. Use eawwy_iowemap() instead\n", cawwew);

	eww = eawwy_iowemap_wange(iowemap_bot, pawigned, size, pwot);
	if (eww)
		wetuwn NUWW;

	wet = (void __iomem *)iowemap_bot + offset;
	iowemap_bot += size + PAGE_SIZE;

	wetuwn wet;
}

/*
 * Unmap an IO wegion and wemove it fwom vmawwoc'd wist.
 * Access to IO memowy shouwd be sewiawized by dwivew.
 */
void iounmap(vowatiwe void __iomem *token)
{
	if (!swab_is_avaiwabwe())
		wetuwn;

	genewic_iounmap(PCI_FIX_ADDW(token));
}
EXPOWT_SYMBOW(iounmap);
