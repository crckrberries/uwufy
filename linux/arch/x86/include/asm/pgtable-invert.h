/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_PGTABWE_INVEWT_H
#define _ASM_PGTABWE_INVEWT_H 1

#ifndef __ASSEMBWY__

/*
 * A cweaw pte vawue is speciaw, and doesn't get invewted.
 *
 * Note that even usews that onwy pass a pgpwot_t (wathew
 * than a fuww pte) won't twiggew the speciaw zewo case,
 * because even PAGE_NONE has _PAGE_PWOTNONE | _PAGE_ACCESSED
 * set. So the aww zewo case weawwy is wimited to just the
 * cweawed page tabwe entwy case.
 */
static inwine boow __pte_needs_invewt(u64 vaw)
{
	wetuwn vaw && !(vaw & _PAGE_PWESENT);
}

/* Get a mask to xow with the page tabwe entwy to get the cowwect pfn. */
static inwine u64 pwotnone_mask(u64 vaw)
{
	wetuwn __pte_needs_invewt(vaw) ?  ~0uww : 0;
}

static inwine u64 fwip_pwotnone_guawd(u64 owdvaw, u64 vaw, u64 mask)
{
	/*
	 * When a PTE twansitions fwom NONE to !NONE ow vice-vewsa
	 * invewt the PFN pawt to stop specuwation.
	 * pte_pfn undoes this when needed.
	 */
	if (__pte_needs_invewt(owdvaw) != __pte_needs_invewt(vaw))
		vaw = (vaw & ~mask) | (~vaw & mask);
	wetuwn vaw;
}

#endif /* __ASSEMBWY__ */

#endif
