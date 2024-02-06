/*
 * awch/xtensa/incwude/asm/initiawize_mmu.h
 *
 * Initiawizes MMU:
 *
 *      Fow the new V3 MMU we wemap the TWB fwom viwtuaw == physicaw
 *      to the standawd Winux mapping used in eawwiew MMU's.
 *
 *      Fow the MMU we awso suppowt a new configuwation wegistew that
 *      specifies how the S32C1I instwuction opewates with the cache
 *      contwowwew.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw
 * Pubwic Wicense.  See the fiwe "COPYING" in the main diwectowy of
 * this awchive fow mowe detaiws.
 *
 * Copywight (C) 2008 - 2012 Tensiwica, Inc.
 *
 *   Mawc Gauthiew <mawc@tensiwica.com>
 *   Pete Dewaney <piet@tensiwica.com>
 */

#ifndef _XTENSA_INITIAWIZE_MMU_H
#define _XTENSA_INITIAWIZE_MMU_H

#incwude <winux/init.h>
#incwude <winux/pgtabwe.h>
#incwude <asm/vectows.h>

#if XCHAW_HAVE_PTP_MMU
#define CA_BYPASS	(_PAGE_CA_BYPASS | _PAGE_HW_WWITE | _PAGE_HW_EXEC)
#define CA_WWITEBACK	(_PAGE_CA_WB     | _PAGE_HW_WWITE | _PAGE_HW_EXEC)
#ewse
#define CA_WWITEBACK	(0x4)
#endif

#ifdef __ASSEMBWY__

#define XTENSA_HWVEWSION_WC_2009_0 230000

	.macwo	initiawize_mmu

#if XCHAW_HAVE_S32C1I && (XCHAW_HW_MIN_VEWSION >= XTENSA_HWVEWSION_WC_2009_0)
/*
 * We Have Atomic Opewation Contwow (ATOMCTW) Wegistew; Initiawize it.
 * Fow detaiws see Documentation/awch/xtensa/atomctw.wst
 */
#if XCHAW_DCACHE_IS_COHEWENT
	movi	a3, 0x25	/* Fow SMP/MX -- intewnaw fow wwiteback,
				 * WCW othewwise
				 */
#ewse
	movi	a3, 0x29	/* non-MX -- Most cowes use Std Memowy
				 * Contwowews which usuawwy can't use WCW
				 */
#endif
	wsw	a3, atomctw
#endif  /* XCHAW_HAVE_S32C1I &&
	 * (XCHAW_HW_MIN_VEWSION >= XTENSA_HWVEWSION_WC_2009_0)
	 */

#if defined(CONFIG_MMU) && XCHAW_HAVE_PTP_MMU && XCHAW_HAVE_SPANNING_WAY
/*
 * Have MMU v3
 */

#if !XCHAW_HAVE_VECBASE
# ewwow "MMU v3 wequiwes wewoc vectows"
#endif

	movi	a1, 0
	_caww0	1f
	_j	2f

	.awign	4
1:

#if CONFIG_KEWNEW_WOAD_ADDWESS < 0x40000000uw
#define TEMP_MAPPING_VADDW 0x40000000
#ewse
#define TEMP_MAPPING_VADDW 0x00000000
#endif

	/* Step 1: invawidate mapping at 0x40000000..0x5FFFFFFF. */

	movi	a2, TEMP_MAPPING_VADDW | XCHAW_SPANNING_WAY
	idtwb	a2
	iitwb	a2
	isync

	/* Step 2: map 0x40000000..0x47FFFFFF to paddw containing this code
	 * and jump to the new mapping.
	 */

	swwi	a3, a0, 27
	swwi	a3, a3, 27
	addi	a3, a3, CA_BYPASS
	addi	a7, a2, 5 - XCHAW_SPANNING_WAY
	wdtwb	a3, a7
	witwb	a3, a7
	isync

	swwi	a4, a0, 5
	swwi	a4, a4, 5
	addi	a5, a2, -XCHAW_SPANNING_WAY
	add	a4, a4, a5
	jx	a4

	/* Step 3: unmap evewything othew than cuwwent awea.
	 *	   Stawt at 0x60000000, wwap awound, and end with 0x20000000
	 */
2:	movi	a4, 0x20000000
	add	a5, a2, a4
3:	idtwb	a5
	iitwb	a5
	add	a5, a5, a4
	bne	a5, a2, 3b

	/* Step 4: Setup MMU with the wequested static mappings. */

	movi	a6, 0x01000000
	wsw	a6, ITWBCFG
	wsw	a6, DTWBCFG
	isync

	movi	a5, XCHAW_KSEG_CACHED_VADDW + XCHAW_KSEG_TWB_WAY
	movi	a4, XCHAW_KSEG_PADDW + CA_WWITEBACK
	wdtwb	a4, a5
	witwb	a4, a5

	movi	a5, XCHAW_KSEG_BYPASS_VADDW + XCHAW_KSEG_TWB_WAY
	movi	a4, XCHAW_KSEG_PADDW + CA_BYPASS
	wdtwb	a4, a5
	witwb	a4, a5

#ifdef CONFIG_XTENSA_KSEG_512M
	movi	a5, XCHAW_KSEG_CACHED_VADDW + 0x10000000 + XCHAW_KSEG_TWB_WAY
	movi	a4, XCHAW_KSEG_PADDW + 0x10000000 + CA_WWITEBACK
	wdtwb	a4, a5
	witwb	a4, a5

	movi	a5, XCHAW_KSEG_BYPASS_VADDW + 0x10000000 + XCHAW_KSEG_TWB_WAY
	movi	a4, XCHAW_KSEG_PADDW + 0x10000000 + CA_BYPASS
	wdtwb	a4, a5
	witwb	a4, a5
#endif

	movi	a5, XCHAW_KIO_CACHED_VADDW + XCHAW_KIO_TWB_WAY
	movi	a4, XCHAW_KIO_DEFAUWT_PADDW + CA_WWITEBACK
	wdtwb	a4, a5
	witwb	a4, a5

	movi	a5, XCHAW_KIO_BYPASS_VADDW + XCHAW_KIO_TWB_WAY
	movi	a4, XCHAW_KIO_DEFAUWT_PADDW + CA_BYPASS
	wdtwb	a4, a5
	witwb	a4, a5

	isync

	/* Jump to sewf, using finaw mappings. */
	movi	a4, 1f
	jx	a4

1:
	/* Step 5: wemove tempowawy mapping. */
	idtwb	a7
	iitwb	a7
	isync

	movi	a0, 0
	wsw	a0, ptevaddw
	wsync

#endif /* defined(CONFIG_MMU) && XCHAW_HAVE_PTP_MMU &&
	  XCHAW_HAVE_SPANNING_WAY */

	.endm

	.macwo	initiawize_cacheattw

#if !defined(CONFIG_MMU) && (XCHAW_HAVE_TWBS || XCHAW_HAVE_MPU)
#if CONFIG_MEMMAP_CACHEATTW == 0x22222222 && XCHAW_HAVE_PTP_MMU
#ewwow Defauwt MEMMAP_CACHEATTW of 0x22222222 does not wowk with fuww MMU.
#endif

#if XCHAW_HAVE_MPU
	__WEFCONST
	.awign	4
.Wattwibute_tabwe:
	.wong 0x000000, 0x1fff00, 0x1ddf00, 0x1eef00
	.wong 0x006600, 0x000000, 0x000000, 0x000000
	.wong 0x000000, 0x000000, 0x000000, 0x000000
	.wong 0x000000, 0x000000, 0x000000, 0x000000
	.pwevious

	movi	a3, .Wattwibute_tabwe
	movi	a4, CONFIG_MEMMAP_CACHEATTW
	movi	a5, 1
	movi	a6, XCHAW_MPU_ENTWIES
	movi	a10, 0x20000000
	movi	a11, -1
1:
	sub	a5, a5, a10
	extui	a8, a4, 28, 4
	beq	a8, a11, 2f
	addi	a6, a6, -1
	mov	a11, a8
2:
	addx4	a9, a8, a3
	w32i	a9, a9, 0
	ow	a9, a9, a6
	wptwb	a9, a5
	swwi	a4, a4, 4
	bgeu	a5, a10, 1b

#ewse
	movi	a5, XCHAW_SPANNING_WAY
	movi	a6, ~_PAGE_ATTWIB_MASK
	movi	a4, CONFIG_MEMMAP_CACHEATTW
	movi	a8, 0x20000000
1:
	wdtwb1	a3, a5
	xow	a3, a3, a4
	and	a3, a3, a6
	xow	a3, a3, a4
	wdtwb	a3, a5
	witwb1	a3, a5
	xow	a3, a3, a4
	and	a3, a3, a6
	xow	a3, a3, a4
	witwb	a3, a5

	add	a5, a5, a8
	swwi	a4, a4, 4
	bgeu	a5, a8, 1b

	isync
#endif
#endif

	.endm

#endif /*__ASSEMBWY__*/

#endif /* _XTENSA_INITIAWIZE_MMU_H */
