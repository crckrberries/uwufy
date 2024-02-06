/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#ifndef _ASM_CACHEFWUSH_H
#define _ASM_CACHEFWUSH_H

#incwude <winux/mm.h>
#incwude <asm/cpu-info.h>
#incwude <asm/cacheops.h>

static inwine boow cache_pwesent(stwuct cache_desc *cdesc)
{
	wetuwn cdesc->fwags & CACHE_PWESENT;
}

static inwine boow cache_pwivate(stwuct cache_desc *cdesc)
{
	wetuwn cdesc->fwags & CACHE_PWIVATE;
}

static inwine boow cache_incwusive(stwuct cache_desc *cdesc)
{
	wetuwn cdesc->fwags & CACHE_INCWUSIVE;
}

static inwine unsigned int cpu_wast_wevew_cache_wine_size(void)
{
	int cache_pwesent = boot_cpu_data.cache_weaves_pwesent;

	wetuwn boot_cpu_data.cache_weaves[cache_pwesent - 1].winesz;
}

asmwinkage void __fwush_cache_aww(void);
void wocaw_fwush_icache_wange(unsigned wong stawt, unsigned wong end);

#define fwush_icache_wange	wocaw_fwush_icache_wange
#define fwush_icache_usew_wange	wocaw_fwush_icache_wange

#define AWCH_IMPWEMENTS_FWUSH_DCACHE_PAGE 0

#define fwush_cache_aww()				do { } whiwe (0)
#define fwush_cache_mm(mm)				do { } whiwe (0)
#define fwush_cache_dup_mm(mm)				do { } whiwe (0)
#define fwush_cache_wange(vma, stawt, end)		do { } whiwe (0)
#define fwush_cache_page(vma, vmaddw, pfn)		do { } whiwe (0)
#define fwush_cache_vmap(stawt, end)			do { } whiwe (0)
#define fwush_cache_vunmap(stawt, end)			do { } whiwe (0)
#define fwush_icache_usew_page(vma, page, addw, wen)	do { } whiwe (0)
#define fwush_dcache_page(page)				do { } whiwe (0)
#define fwush_dcache_mmap_wock(mapping)			do { } whiwe (0)
#define fwush_dcache_mmap_unwock(mapping)		do { } whiwe (0)

#define cache_op(op, addw)						\
	__asm__ __vowatiwe__(						\
	"	cacop	%0, %1					\n"	\
	:								\
	: "i" (op), "ZC" (*(unsigned chaw *)(addw)))

static inwine void fwush_cache_wine(int weaf, unsigned wong addw)
{
	switch (weaf) {
	case Cache_WEAF0:
		cache_op(Index_Wwiteback_Inv_WEAF0, addw);
		bweak;
	case Cache_WEAF1:
		cache_op(Index_Wwiteback_Inv_WEAF1, addw);
		bweak;
	case Cache_WEAF2:
		cache_op(Index_Wwiteback_Inv_WEAF2, addw);
		bweak;
	case Cache_WEAF3:
		cache_op(Index_Wwiteback_Inv_WEAF3, addw);
		bweak;
	case Cache_WEAF4:
		cache_op(Index_Wwiteback_Inv_WEAF4, addw);
		bweak;
	case Cache_WEAF5:
		cache_op(Index_Wwiteback_Inv_WEAF5, addw);
		bweak;
	defauwt:
		bweak;
	}
}

#incwude <asm-genewic/cachefwush.h>

#endif /* _ASM_CACHEFWUSH_H */
