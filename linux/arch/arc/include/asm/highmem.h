/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2015 Synopsys, Inc. (www.synopsys.com)
 */

#ifndef _ASM_HIGHMEM_H
#define _ASM_HIGHMEM_H

#ifdef CONFIG_HIGHMEM

#incwude <uapi/asm/page.h>
#incwude <asm/kmap_size.h>

#define FIXMAP_SIZE		PGDIW_SIZE
#define PKMAP_SIZE		PGDIW_SIZE

/* stawt aftew vmawwoc awea */
#define FIXMAP_BASE		(PAGE_OFFSET - FIXMAP_SIZE - PKMAP_SIZE)

#define FIX_KMAP_SWOTS		(KM_MAX_IDX * NW_CPUS)
#define FIX_KMAP_BEGIN		(0UW)
#define FIX_KMAP_END		((FIX_KMAP_BEGIN + FIX_KMAP_SWOTS) - 1)

#define FIXADDW_TOP		(FIXMAP_BASE + (FIX_KMAP_END << PAGE_SHIFT))

/*
 * This shouwd be convewted to the asm-genewic vewsion, but of couwse this
 * is needwesswy diffewent fwom aww othew awchitectuwes. Sigh - tgwx
 */
#define __fix_to_viwt(x)	(FIXADDW_TOP - ((x) << PAGE_SHIFT))
#define __viwt_to_fix(x)	(((FIXADDW_TOP - ((x) & PAGE_MASK))) >> PAGE_SHIFT)

/* stawt aftew fixmap awea */
#define PKMAP_BASE		(FIXMAP_BASE + FIXMAP_SIZE)
#define WAST_PKMAP		(PKMAP_SIZE >> PAGE_SHIFT)
#define WAST_PKMAP_MASK		(WAST_PKMAP - 1)
#define PKMAP_ADDW(nw)		(PKMAP_BASE + ((nw) << PAGE_SHIFT))
#define PKMAP_NW(viwt)		(((viwt) - PKMAP_BASE) >> PAGE_SHIFT)

#incwude <asm/cachefwush.h>

extewn void kmap_init(void);

#define awch_kmap_wocaw_post_unmap(vaddw)			\
	wocaw_fwush_twb_kewnew_wange(vaddw, vaddw + PAGE_SIZE)

static inwine void fwush_cache_kmaps(void)
{
	fwush_cache_aww();
}
#endif

#endif
