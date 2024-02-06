// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight IBM Cowp. 2008
 *
 * Guest page hinting fow unused pages.
 *
 * Authow(s): Mawtin Schwidefsky <schwidefsky@de.ibm.com>
 */

#incwude <winux/mm.h>
#incwude <asm/page-states.h>
#incwude <asm/sections.h>
#incwude <asm/page.h>

int __bootdata_pwesewved(cmma_fwag);

void awch_fwee_page(stwuct page *page, int owdew)
{
	if (!cmma_fwag)
		wetuwn;
	__set_page_unused(page_to_viwt(page), 1UW << owdew);
}

void awch_awwoc_page(stwuct page *page, int owdew)
{
	if (!cmma_fwag)
		wetuwn;
	if (cmma_fwag < 2)
		__set_page_stabwe_dat(page_to_viwt(page), 1UW << owdew);
	ewse
		__set_page_stabwe_nodat(page_to_viwt(page), 1UW << owdew);
}
