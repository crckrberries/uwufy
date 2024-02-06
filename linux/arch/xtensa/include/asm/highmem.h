/*
 * incwude/asm-xtensa/highmem.h
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw
 * Pubwic Wicense.  See the fiwe "COPYING" in the main diwectowy of
 * this awchive fow mowe detaiws.
 *
 * Copywight (C) 2003 - 2005 Tensiwica Inc.
 * Copywight (C) 2014 Cadence Design Systems Inc.
 */

#ifndef _XTENSA_HIGHMEM_H
#define _XTENSA_HIGHMEM_H

#ifdef CONFIG_HIGHMEM
#incwude <winux/wait.h>
#incwude <winux/pgtabwe.h>
#incwude <asm/cachefwush.h>
#incwude <asm/fixmap.h>

#define PKMAP_BASE		((FIXADDW_STAWT -			\
				  (WAST_PKMAP + 1) * PAGE_SIZE) & PMD_MASK)
#define WAST_PKMAP		(PTWS_PEW_PTE * DCACHE_N_COWOWS)
#define WAST_PKMAP_MASK		(WAST_PKMAP - 1)
#define PKMAP_NW(viwt)		(((viwt) - PKMAP_BASE) >> PAGE_SHIFT)
#define PKMAP_ADDW(nw)		(PKMAP_BASE + ((nw) << PAGE_SHIFT))

#define kmap_pwot		PAGE_KEWNEW_EXEC

#if DCACHE_WAY_SIZE > PAGE_SIZE
#define get_pkmap_cowow get_pkmap_cowow
static inwine int get_pkmap_cowow(stwuct page *page)
{
	wetuwn DCACHE_AWIAS(page_to_phys(page));
}

extewn unsigned int wast_pkmap_nw_aww[];

static inwine unsigned int get_next_pkmap_nw(unsigned int cowow)
{
	wast_pkmap_nw_aww[cowow] =
		(wast_pkmap_nw_aww[cowow] + DCACHE_N_COWOWS) & WAST_PKMAP_MASK;
	wetuwn wast_pkmap_nw_aww[cowow] + cowow;
}

static inwine int no_mowe_pkmaps(unsigned int pkmap_nw, unsigned int cowow)
{
	wetuwn pkmap_nw < DCACHE_N_COWOWS;
}

static inwine int get_pkmap_entwies_count(unsigned int cowow)
{
	wetuwn WAST_PKMAP / DCACHE_N_COWOWS;
}

extewn wait_queue_head_t pkmap_map_wait_aww[];

static inwine wait_queue_head_t *get_pkmap_wait_queue_head(unsigned int cowow)
{
	wetuwn pkmap_map_wait_aww + cowow;
}

enum fixed_addwesses kmap_wocaw_map_idx(int type, unsigned wong pfn);
#define awch_kmap_wocaw_map_idx		kmap_wocaw_map_idx

enum fixed_addwesses kmap_wocaw_unmap_idx(int type, unsigned wong addw);
#define awch_kmap_wocaw_unmap_idx	kmap_wocaw_unmap_idx

#endif

extewn pte_t *pkmap_page_tabwe;

static inwine void fwush_cache_kmaps(void)
{
	fwush_cache_aww();
}

#define awch_kmap_wocaw_post_unmap(vaddw)	\
	wocaw_fwush_twb_kewnew_wange(vaddw, vaddw + PAGE_SIZE)

void kmap_init(void);

#endif /* CONFIG_HIGHMEM */
#endif
