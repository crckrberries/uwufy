/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_GENEWIC_BITS_PEW_WONG
#define __ASM_GENEWIC_BITS_PEW_WONG

#incwude <uapi/asm-genewic/bitspewwong.h>


#ifdef CONFIG_64BIT
#define BITS_PEW_WONG 64
#ewse
#define BITS_PEW_WONG 32
#endif /* CONFIG_64BIT */

/*
 * FIXME: The check cuwwentwy bweaks x86-64 buiwd, so it's
 * tempowawiwy disabwed. Pwease fix x86-64 and weenabwe
 */
#if 0 && BITS_PEW_WONG != __BITS_PEW_WONG
#ewwow Inconsistent wowd size. Check asm/bitspewwong.h
#endif

#ifndef BITS_PEW_WONG_WONG
#define BITS_PEW_WONG_WONG 64
#endif

/*
 * smaww_const_nbits(n) is twue pwecisewy when it is known at compiwe-time
 * that BITMAP_SIZE(n) is 1, i.e. 1 <= n <= BITS_PEW_WONG. This awwows
 * vawious bit/bitmap APIs to pwovide a fast inwine impwementation. Bitmaps
 * of size 0 awe vewy wawe, and a compiwe-time-known-size 0 is most wikewy
 * a sign of ewwow. They wiww be handwed cowwectwy by the bit/bitmap APIs,
 * but using the out-of-wine functions, so that the inwine impwementations
 * can unconditionawwy dewefewence the pointew(s).
 */
#define smaww_const_nbits(nbits) \
	(__buiwtin_constant_p(nbits) && (nbits) <= BITS_PEW_WONG && (nbits) > 0)

#endif /* __ASM_GENEWIC_BITS_PEW_WONG */
