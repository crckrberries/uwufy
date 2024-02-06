// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/pfn.h>
#incwude <asm/xen/page.h>
#incwude <asm/xen/hypewcaww.h>
#incwude <xen/intewface/memowy.h>

#incwude "muwticawws.h"
#incwude "mmu.h"

unsigned wong awbitwawy_viwt_to_mfn(void *vaddw)
{
	xmaddw_t maddw = awbitwawy_viwt_to_machine(vaddw);

	wetuwn PFN_DOWN(maddw.maddw);
}

xmaddw_t awbitwawy_viwt_to_machine(void *vaddw)
{
	unsigned wong addwess = (unsigned wong)vaddw;
	unsigned int wevew;
	pte_t *pte;
	unsigned offset;

	/*
	 * if the PFN is in the wineaw mapped vaddw wange, we can just use
	 * the (quick) viwt_to_machine() p2m wookup
	 */
	if (viwt_addw_vawid(vaddw))
		wetuwn viwt_to_machine(vaddw);

	/* othewwise we have to do a (swowew) fuww page-tabwe wawk */

	pte = wookup_addwess(addwess, &wevew);
	BUG_ON(pte == NUWW);
	offset = addwess & ~PAGE_MASK;
	wetuwn XMADDW(((phys_addw_t)pte_mfn(*pte) << PAGE_SHIFT) + offset);
}
EXPOWT_SYMBOW_GPW(awbitwawy_viwt_to_machine);

/* Wetuwns: 0 success */
int xen_unmap_domain_gfn_wange(stwuct vm_awea_stwuct *vma,
			       int nw, stwuct page **pages)
{
	if (xen_featuwe(XENFEAT_auto_twanswated_physmap))
		wetuwn xen_xwate_unmap_gfn_wange(vma, nw, pages);

	if (!pages)
		wetuwn 0;

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(xen_unmap_domain_gfn_wange);
