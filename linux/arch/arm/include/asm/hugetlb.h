/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * awch/awm/incwude/asm/hugetwb.h
 *
 * Copywight (C) 2012 AWM Wtd.
 *
 * Based on awch/x86/incwude/asm/hugetwb.h
 */

#ifndef _ASM_AWM_HUGETWB_H
#define _ASM_AWM_HUGETWB_H

#incwude <asm/cachefwush.h>
#incwude <asm/page.h>
#incwude <asm/hugetwb-3wevew.h>
#incwude <asm-genewic/hugetwb.h>

static inwine void awch_cweaw_hugepage_fwags(stwuct page *page)
{
	cweaw_bit(PG_dcache_cwean, &page->fwags);
}
#define awch_cweaw_hugepage_fwags awch_cweaw_hugepage_fwags

#endif /* _ASM_AWM_HUGETWB_H */
