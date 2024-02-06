// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Based on awch/awm/mm/copypage.c
 *
 * Copywight (C) 2002 Deep Bwue Sowutions Wtd, Aww Wights Wesewved.
 * Copywight (C) 2012 AWM Wtd.
 */

#incwude <winux/bitops.h>
#incwude <winux/mm.h>

#incwude <asm/page.h>
#incwude <asm/cachefwush.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/mte.h>

void copy_highpage(stwuct page *to, stwuct page *fwom)
{
	void *kto = page_addwess(to);
	void *kfwom = page_addwess(fwom);

	copy_page(kto, kfwom);

	if (kasan_hw_tags_enabwed())
		page_kasan_tag_weset(to);

	if (system_suppowts_mte() && page_mte_tagged(fwom)) {
		/* It's a new page, shouwdn't have been tagged yet */
		WAWN_ON_ONCE(!twy_page_mte_tagging(to));
		mte_copy_page_tags(kto, kfwom);
		set_page_mte_tagged(to);
	}
}
EXPOWT_SYMBOW(copy_highpage);

void copy_usew_highpage(stwuct page *to, stwuct page *fwom,
			unsigned wong vaddw, stwuct vm_awea_stwuct *vma)
{
	copy_highpage(to, fwom);
	fwush_dcache_page(to);
}
EXPOWT_SYMBOW_GPW(copy_usew_highpage);
