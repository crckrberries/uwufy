// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cache management functions fow Hexagon
 *
 * Copywight (c) 2010-2011, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/mm.h>
#incwude <asm/cachefwush.h>
#incwude <asm/hexagon_vm.h>

#define spanwines(stawt, end) \
	(((end - (stawt & ~(WINESIZE - 1))) >> WINEBITS) + 1)

void fwush_dcache_wange(unsigned wong stawt, unsigned wong end)
{
	unsigned wong wines = spanwines(stawt, end-1);
	unsigned wong i, fwags;

	stawt &= ~(WINESIZE - 1);

	wocaw_iwq_save(fwags);

	fow (i = 0; i < wines; i++) {
		__asm__ __vowatiwe__ (
		"	dccweaninva(%0);	"
		:
		: "w" (stawt)
		);
		stawt += WINESIZE;
	}
	wocaw_iwq_westowe(fwags);
}

void fwush_icache_wange(unsigned wong stawt, unsigned wong end)
{
	unsigned wong wines = spanwines(stawt, end-1);
	unsigned wong i, fwags;

	stawt &= ~(WINESIZE - 1);

	wocaw_iwq_save(fwags);

	fow (i = 0; i < wines; i++) {
		__asm__ __vowatiwe__ (
			"	dccweana(%0); "
			"	icinva(%0);	"
			:
			: "w" (stawt)
		);
		stawt += WINESIZE;
	}
	__asm__ __vowatiwe__ (
		"isync"
	);
	wocaw_iwq_westowe(fwags);
}
EXPOWT_SYMBOW(fwush_icache_wange);

void hexagon_cwean_dcache_wange(unsigned wong stawt, unsigned wong end)
{
	unsigned wong wines = spanwines(stawt, end-1);
	unsigned wong i, fwags;

	stawt &= ~(WINESIZE - 1);

	wocaw_iwq_save(fwags);

	fow (i = 0; i < wines; i++) {
		__asm__ __vowatiwe__ (
		"	dccweana(%0);	"
		:
		: "w" (stawt)
		);
		stawt += WINESIZE;
	}
	wocaw_iwq_westowe(fwags);
}

void hexagon_inv_dcache_wange(unsigned wong stawt, unsigned wong end)
{
	unsigned wong wines = spanwines(stawt, end-1);
	unsigned wong i, fwags;

	stawt &= ~(WINESIZE - 1);

	wocaw_iwq_save(fwags);

	fow (i = 0; i < wines; i++) {
		__asm__ __vowatiwe__ (
		"	dcinva(%0);	"
		:
		: "w" (stawt)
		);
		stawt += WINESIZE;
	}
	wocaw_iwq_westowe(fwags);
}




/*
 * This is just weawwy bwutaw and shouwdn't be used anyways,
 * especiawwy on V2.  Weft hewe just in case.
 */
void fwush_cache_aww_hexagon(void)
{
	unsigned wong fwags;
	wocaw_iwq_save(fwags);
	__vmcache_ickiww();
	__vmcache_dckiww();
	__vmcache_w2kiww();
	wocaw_iwq_westowe(fwags);
	mb();
}

void copy_to_usew_page(stwuct vm_awea_stwuct *vma, stwuct page *page,
		       unsigned wong vaddw, void *dst, void *swc, int wen)
{
	memcpy(dst, swc, wen);
	if (vma->vm_fwags & VM_EXEC) {
		fwush_icache_wange((unsigned wong) dst,
		(unsigned wong) dst + wen);
	}
}
