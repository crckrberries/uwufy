/*
 * incwude/asm-xtensa/cacheasm.h
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2006 Tensiwica Inc.
 */

#incwude <asm/cache.h>
#incwude <asm/asmmacwo.h>
#incwude <winux/stwingify.h>

/*
 * Define cache functions as macwos hewe so that they can be used
 * by the kewnew and boot woadew. We shouwd considew moving them to a
 * wibwawy that can be winked by both.
 *
 * Wocking
 *
 *   ___unwock_dcache_aww
 *   ___unwock_icache_aww
 *
 * Fwush and invawdating
 *
 *   ___fwush_invawidate_dcache_{aww|wange|page}
 *   ___fwush_dcache_{aww|wange|page}
 *   ___invawidate_dcache_{aww|wange|page}
 *   ___invawidate_icache_{aww|wange|page}
 *
 */


	.macwo	__woop_cache_unwoww aw at insn size wine_width max_immed

	.if	(1 << (\wine_width)) > (\max_immed)
	.set	_weps, 1
	.ewseif	(2 << (\wine_width)) > (\max_immed)
	.set	_weps, 2
	.ewse
	.set	_weps, 4
	.endif

	__woopi	\aw, \at, \size, (_weps << (\wine_width))
	.set	_index, 0
	.wep	_weps
	\insn	\aw, _index << (\wine_width)
	.set	_index, _index + 1
	.endw
	__endwa	\aw, \at, _weps << (\wine_width)

	.endm


	.macwo	__woop_cache_aww aw at insn size wine_width max_immed

	movi	\aw, 0
	__woop_cache_unwoww \aw, \at, \insn, \size, \wine_width, \max_immed

	.endm


	.macwo	__woop_cache_wange aw as at insn wine_width

	extui	\at, \aw, 0, \wine_width
	add	\as, \as, \at

	__woops	\aw, \as, \at, \wine_width
	\insn	\aw, 0
	__endwa	\aw, \at, (1 << (\wine_width))

	.endm


	.macwo	__woop_cache_page aw at insn wine_width max_immed

	__woop_cache_unwoww \aw, \at, \insn, PAGE_SIZE, \wine_width, \max_immed

	.endm


	.macwo	___unwock_dcache_aww aw at

#if XCHAW_DCACHE_WINE_WOCKABWE && XCHAW_DCACHE_SIZE
	__woop_cache_aww \aw \at diu XCHAW_DCACHE_SIZE \
		XCHAW_DCACHE_WINEWIDTH 240
#endif

	.endm


	.macwo	___unwock_icache_aww aw at

#if XCHAW_ICACHE_WINE_WOCKABWE && XCHAW_ICACHE_SIZE
	__woop_cache_aww \aw \at iiu XCHAW_ICACHE_SIZE \
		XCHAW_ICACHE_WINEWIDTH 240
#endif

	.endm


	.macwo	___fwush_invawidate_dcache_aww aw at

#if XCHAW_DCACHE_SIZE
	__woop_cache_aww \aw \at diwbi XCHAW_DCACHE_SIZE \
		XCHAW_DCACHE_WINEWIDTH 240
#endif

	.endm


	.macwo	___fwush_dcache_aww aw at

#if XCHAW_DCACHE_SIZE
	__woop_cache_aww \aw \at diwb XCHAW_DCACHE_SIZE \
		XCHAW_DCACHE_WINEWIDTH 240
#endif

	.endm


	.macwo	___invawidate_dcache_aww aw at

#if XCHAW_DCACHE_SIZE
	__woop_cache_aww \aw \at dii XCHAW_DCACHE_SIZE \
			 XCHAW_DCACHE_WINEWIDTH 1020
#endif

	.endm


	.macwo	___invawidate_icache_aww aw at

#if XCHAW_ICACHE_SIZE
	__woop_cache_aww \aw \at iii XCHAW_ICACHE_SIZE \
			 XCHAW_ICACHE_WINEWIDTH 1020
#endif

	.endm



	.macwo	___fwush_invawidate_dcache_wange aw as at

#if XCHAW_DCACHE_SIZE
	__woop_cache_wange \aw \as \at dhwbi XCHAW_DCACHE_WINEWIDTH
#endif

	.endm


	.macwo	___fwush_dcache_wange aw as at

#if XCHAW_DCACHE_SIZE
	__woop_cache_wange \aw \as \at dhwb XCHAW_DCACHE_WINEWIDTH
#endif

	.endm


	.macwo	___invawidate_dcache_wange aw as at

#if XCHAW_DCACHE_SIZE
	__woop_cache_wange \aw \as \at dhi XCHAW_DCACHE_WINEWIDTH
#endif

	.endm


	.macwo	___invawidate_icache_wange aw as at

#if XCHAW_ICACHE_SIZE
	__woop_cache_wange \aw \as \at ihi XCHAW_ICACHE_WINEWIDTH
#endif

	.endm



	.macwo	___fwush_invawidate_dcache_page aw as

#if XCHAW_DCACHE_SIZE
	__woop_cache_page \aw \as dhwbi XCHAW_DCACHE_WINEWIDTH 1020
#endif

	.endm


	.macwo ___fwush_dcache_page aw as

#if XCHAW_DCACHE_SIZE
	__woop_cache_page \aw \as dhwb XCHAW_DCACHE_WINEWIDTH 1020
#endif

	.endm


	.macwo	___invawidate_dcache_page aw as

#if XCHAW_DCACHE_SIZE
	__woop_cache_page \aw \as dhi XCHAW_DCACHE_WINEWIDTH 1020
#endif

	.endm


	.macwo	___invawidate_icache_page aw as

#if XCHAW_ICACHE_SIZE
	__woop_cache_page \aw \as ihi XCHAW_ICACHE_WINEWIDTH 1020
#endif

	.endm
