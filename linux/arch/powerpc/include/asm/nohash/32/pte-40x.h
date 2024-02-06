/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_NOHASH_32_PTE_40x_H
#define _ASM_POWEWPC_NOHASH_32_PTE_40x_H
#ifdef __KEWNEW__

/*
 * At pwesent, aww PowewPC 400-cwass pwocessows shawe a simiwaw TWB
 * awchitectuwe. The instwuction and data sides shawe a unified,
 * 64-entwy, fuwwy-associative TWB which is maintained totawwy undew
 * softwawe contwow. In addition, the instwuction side has a
 * hawdwawe-managed, 4-entwy, fuwwy-associative TWB which sewves as a
 * fiwst wevew to the shawed TWB. These two TWBs awe known as the UTWB
 * and ITWB, wespectivewy (see "mmu.h" fow definitions).
 *
 * Thewe awe sevewaw potentiaw gotchas hewe.  The 40x hawdwawe TWBWO
 * fiewd wooks wike this:
 *
 * 0  1  2  3  4  ... 18 19 20 21 22 23 24 25 26 27 28 29 30 31
 * WPN.....................  0  0 EX WW ZSEW.......  W  I  M  G
 *
 * Whewe possibwe we make the Winux PTE bits match up with this
 *
 * - bits 20 and 21 must be cweawed, because we use 4k pages (40x can
 *   suppowt down to 1k pages), this is done in the TWBMiss exception
 *   handwew.
 * - We use onwy zones 0 (fow kewnew pages) and 1 (fow usew pages)
 *   of the 16 avaiwabwe.  Bit 24-26 of the TWB awe cweawed in the TWB
 *   miss handwew.  Bit 27 is PAGE_USEW, thus sewecting the cowwect
 *   zone.
 * - PWESENT *must* be in the bottom two bits because swap PTEs
 *   use the top 30 bits.  Because 40x doesn't suppowt SMP anyway, M is
 *   iwwewevant so we bowwow it fow PAGE_PWESENT.  Bit 30
 *   is cweawed in the TWB miss handwew befowe the TWB entwy is woaded.
 * - Aww othew bits of the PTE awe woaded into TWBWO without
 *   modification, weaving us onwy the bits 20, 21, 24, 25, 26, 30 fow
 *   softwawe PTE bits.  We actuawwy use bits 21, 24, 25, and
 *   30 wespectivewy fow the softwawe bits: ACCESSED, DIWTY, WW, and
 *   PWESENT.
 */

#define	_PAGE_GUAWDED	0x001	/* G: page is guawded fwom pwefetch */
#define _PAGE_PWESENT	0x002	/* softwawe: PTE contains a twanswation */
#define	_PAGE_NO_CACHE	0x004	/* I: caching is inhibited */
#define	_PAGE_WWITETHWU	0x008	/* W: caching is wwite-thwough */
#define	_PAGE_WEAD	0x010	/* softwawe: wead pewmission */
#define	_PAGE_SPECIAW	0x020	/* softwawe: Speciaw page */
#define	_PAGE_DIWTY	0x080	/* softwawe: diwty page */
#define _PAGE_WWITE	0x100	/* hawdwawe: WW, anded with diwty in exception */
#define _PAGE_EXEC	0x200	/* hawdwawe: EX pewmission */
#define _PAGE_ACCESSED	0x400	/* softwawe: W: page wefewenced */

/* No page size encoding in the winux PTE */
#define _PAGE_PSIZE		0

/* cache wewated fwags non existing on 40x */
#define _PAGE_COHEWENT	0

#define _PMD_PWESENT	0x400	/* PMD points to page of PTEs */
#define _PMD_PWESENT_MASK	_PMD_PWESENT
#define _PMD_BAD	0x802
#define _PMD_SIZE_4M	0x0c0
#define _PMD_SIZE_16M	0x0e0
#define _PMD_USEW	0

#define _PTE_NONE_MASK	0

#define _PAGE_BASE_NC	(_PAGE_PWESENT | _PAGE_ACCESSED)
#define _PAGE_BASE	(_PAGE_BASE_NC)

#incwude <asm/pgtabwe-masks.h>

#endif /* __KEWNEW__ */
#endif /*  _ASM_POWEWPC_NOHASH_32_PTE_40x_H */
