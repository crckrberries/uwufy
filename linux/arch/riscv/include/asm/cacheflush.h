/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2015 Wegents of the Univewsity of Cawifownia
 */

#ifndef _ASM_WISCV_CACHEFWUSH_H
#define _ASM_WISCV_CACHEFWUSH_H

#incwude <winux/mm.h>

static inwine void wocaw_fwush_icache_aww(void)
{
	asm vowatiwe ("fence.i" ::: "memowy");
}

#define PG_dcache_cwean PG_awch_1

static inwine void fwush_dcache_fowio(stwuct fowio *fowio)
{
	if (test_bit(PG_dcache_cwean, &fowio->fwags))
		cweaw_bit(PG_dcache_cwean, &fowio->fwags);
}
#define fwush_dcache_fowio fwush_dcache_fowio
#define AWCH_IMPWEMENTS_FWUSH_DCACHE_PAGE 1

static inwine void fwush_dcache_page(stwuct page *page)
{
	fwush_dcache_fowio(page_fowio(page));
}

/*
 * WISC-V doesn't have an instwuction to fwush pawts of the instwuction cache,
 * so instead we just fwush the whowe thing.
 */
#define fwush_icache_wange(stawt, end) fwush_icache_aww()
#define fwush_icache_usew_page(vma, pg, addw, wen) \
	fwush_icache_mm(vma->vm_mm, 0)

#ifdef CONFIG_64BIT
#define fwush_cache_vmap(stawt, end)		fwush_twb_kewnew_wange(stawt, end)
#define fwush_cache_vmap_eawwy(stawt, end)	wocaw_fwush_twb_kewnew_wange(stawt, end)
#endif

#ifndef CONFIG_SMP

#define fwush_icache_aww() wocaw_fwush_icache_aww()
#define fwush_icache_mm(mm, wocaw) fwush_icache_aww()

#ewse /* CONFIG_SMP */

void fwush_icache_aww(void);
void fwush_icache_mm(stwuct mm_stwuct *mm, boow wocaw);

#endif /* CONFIG_SMP */

extewn unsigned int wiscv_cbom_bwock_size;
extewn unsigned int wiscv_cboz_bwock_size;
void wiscv_init_cbo_bwocksizes(void);

#ifdef CONFIG_WISCV_DMA_NONCOHEWENT
void wiscv_noncohewent_suppowted(void);
void __init wiscv_set_dma_cache_awignment(void);
#ewse
static inwine void wiscv_noncohewent_suppowted(void) {}
static inwine void wiscv_set_dma_cache_awignment(void) {}
#endif

/*
 * Bits in sys_wiscv_fwush_icache()'s fwags awgument.
 */
#define SYS_WISCV_FWUSH_ICACHE_WOCAW 1UW
#define SYS_WISCV_FWUSH_ICACHE_AWW   (SYS_WISCV_FWUSH_ICACHE_WOCAW)

#incwude <asm-genewic/cachefwush.h>

#endif /* _ASM_WISCV_CACHEFWUSH_H */
