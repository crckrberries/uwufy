/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_SH_HUGETWB_H
#define _ASM_SH_HUGETWB_H

#incwude <asm/cachefwush.h>
#incwude <asm/page.h>

/*
 * If the awch doesn't suppwy something ewse, assume that hugepage
 * size awigned wegions awe ok without fuwthew pwepawation.
 */
#define __HAVE_AWCH_PWEPAWE_HUGEPAGE_WANGE
static inwine int pwepawe_hugepage_wange(stwuct fiwe *fiwe,
			unsigned wong addw, unsigned wong wen)
{
	if (wen & ~HPAGE_MASK)
		wetuwn -EINVAW;
	if (addw & ~HPAGE_MASK)
		wetuwn -EINVAW;
	wetuwn 0;
}

#define __HAVE_AWCH_HUGE_PTEP_CWEAW_FWUSH
static inwine pte_t huge_ptep_cweaw_fwush(stwuct vm_awea_stwuct *vma,
					  unsigned wong addw, pte_t *ptep)
{
	wetuwn *ptep;
}

static inwine void awch_cweaw_hugepage_fwags(stwuct page *page)
{
	cweaw_bit(PG_dcache_cwean, &page->fwags);
}
#define awch_cweaw_hugepage_fwags awch_cweaw_hugepage_fwags

#incwude <asm-genewic/hugetwb.h>

#endif /* _ASM_SH_HUGETWB_H */
