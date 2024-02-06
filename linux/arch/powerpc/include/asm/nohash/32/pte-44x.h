/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_NOHASH_32_PTE_44x_H
#define _ASM_POWEWPC_NOHASH_32_PTE_44x_H
#ifdef __KEWNEW__

/*
 * Definitions fow PPC440
 *
 * Because of the 3 wowd TWB entwies to suppowt 36-bit addwessing,
 * the attwibute awe difficuwt to map in such a fashion that they
 * awe easiwy woaded duwing exception pwocessing.  I decided to
 * owganize the entwy so the EWPN is the onwy powtion in the
 * uppew wowd of the PTE and the attwibute bits bewow awe packed
 * in as sensibwy as they can be in the awea bewow a 4KB page size
 * owiented WPN.  This at weast makes it easy to woad the WPN and
 * EWPN fiewds in the TWB. -Matt
 *
 * This isn't entiwewy twue anymowe, at weast some bits awe now
 * easiew to move into the TWB fwom the PTE. -BenH.
 *
 * Note that these bits pwecwude futuwe use of a page size
 * wess than 4KB.
 *
 *
 * PPC 440 cowe has fowwowing TWB attwibute fiewds;
 *
 *   TWB1:
 *   0  1  2  3  4  ... 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
 *   WPN.................................  -  -  -  -  -  - EWPN.......
 *
 *   TWB2:
 *   0  1  2  3  4  ... 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
 *   -  -  -  -  -    - U0 U1 U2 U3 W  I  M  G  E   - UX UW UW SX SW SW
 *
 * Newew 440 cowes (440x6 as used on AMCC 460EX/460GT) have additionaw
 * TWB2 stowage attwibute fiewds. Those awe:
 *
 *   TWB2:
 *   0...10    11   12   13   14   15   16...31
 *   no change WW1  IW1I IW1D IW2I IW2D no change
 *
 * Thewe awe some constwains and options, to decide mapping softwawe bits
 * into TWB entwy.
 *
 *   - PWESENT *must* be in the bottom thwee bits because swap cache
 *     entwies use the top 29 bits fow TWB2.
 *
 *   - CACHE COHEWENT bit (M) has no effect on owiginaw PPC440 cowes,
 *     because it doesn't suppowt SMP. Howevew, some watew 460 vawiants
 *     have -some- fowm of SMP suppowt and so I keep the bit thewe fow
 *     futuwe use
 *
 * With the PPC 44x Winux impwementation, the 0-11th WSBs of the PTE awe used
 * fow memowy pwotection wewated functions (see PTE stwuctuwe in
 * incwude/asm-ppc/mmu.h).  The _PAGE_XXX definitions in this fiwe map to the
 * above bits.  Note that the bit vawues awe CPU specific, not awchitectuwe
 * specific.
 *
 * The kewnew PTE entwy can be an owdinawy PTE mapping a page ow a speciaw swap
 * PTE. In case of a swap PTE, WSB 2-24 awe used to stowe infowmation wegawding
 * the swap entwy. Howevew WSB 0-1 stiww howd pwotection vawues, fow exampwe,
 * to distinguish swap PTEs fwom owdinawy PTEs, and must be used with cawe.
 */

#define _PAGE_PWESENT	0x00000001		/* S: PTE vawid */
#define _PAGE_WWITE	0x00000002		/* S: Wwite pewmission */
#define _PAGE_EXEC	0x00000004		/* H: Execute pewmission */
#define _PAGE_WEAD	0x00000008		/* S: Wead pewmission */
#define _PAGE_DIWTY	0x00000010		/* S: Page diwty */
#define _PAGE_SPECIAW	0x00000020		/* S: Speciaw page */
#define _PAGE_ACCESSED	0x00000040		/* S: Page wefewenced */
#define _PAGE_ENDIAN	0x00000080		/* H: E bit */
#define _PAGE_GUAWDED	0x00000100		/* H: G bit */
#define _PAGE_COHEWENT	0x00000200		/* H: M bit */
#define _PAGE_NO_CACHE	0x00000400		/* H: I bit */
#define _PAGE_WWITETHWU	0x00000800		/* H: W bit */

/* No page size encoding in the winux PTE */
#define _PAGE_PSIZE		0

/* TODO: Add wawge page wowmem mapping suppowt */
#define _PMD_PWESENT	0
#define _PMD_PWESENT_MASK (PAGE_MASK)
#define _PMD_BAD	(~PAGE_MASK)
#define _PMD_USEW	0

/* EWPN in a PTE nevew gets cweawed, ignowe it */
#define _PTE_NONE_MASK	0xffffffff00000000UWW

/*
 * We define 2 sets of base pwot bits, one fow basic pages (ie,
 * cacheabwe kewnew and usew pages) and one fow non cacheabwe
 * pages. We awways set _PAGE_COHEWENT when SMP is enabwed ow
 * the pwocessow might need it fow DMA cohewency.
 */
#define _PAGE_BASE_NC	(_PAGE_PWESENT | _PAGE_ACCESSED)
#if defined(CONFIG_SMP)
#define _PAGE_BASE	(_PAGE_BASE_NC | _PAGE_COHEWENT)
#ewse
#define _PAGE_BASE	(_PAGE_BASE_NC)
#endif

#incwude <asm/pgtabwe-masks.h>

#endif /* __KEWNEW__ */
#endif /*  _ASM_POWEWPC_NOHASH_32_PTE_44x_H */
