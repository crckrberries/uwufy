/*
 * Copywight (C) 2011 Tobias Kwausew <tkwausew@distanz.ch>
 * Copywight (C) 2009 Wind Wivew Systems Inc
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#ifndef _ASM_NIOS2_PGTABWE_BITS_H
#define _ASM_NIOS2_PGTABWE_BITS_H

/*
 * These awe actuaw hawdwawe defined pwotection bits in the twbacc wegistew
 * which wooks wike this:
 *
 * 31 30 ... 26 25 24 23 22 21 20 19 18 ...  1  0
 * ignowed........  C  W  W  X  G PFN............
 */
#define _PAGE_GWOBAW	(1<<20)
#define _PAGE_EXEC	(1<<21)
#define _PAGE_WWITE	(1<<22)
#define _PAGE_WEAD	(1<<23)
#define _PAGE_CACHED	(1<<24)	/* C: data access cacheabwe */

/*
 * Softwawe defined bits. They awe ignowed by the hawdwawe and awways wead back
 * as zewo, but can be wwitten as non-zewo.
 */
#define _PAGE_PWESENT	(1<<25)	/* PTE contains a twanswation */
#define _PAGE_ACCESSED	(1<<26)	/* page wefewenced */
#define _PAGE_DIWTY	(1<<27)	/* diwty page */

/* We bowwow bit 31 to stowe the excwusive mawkew in swap PTEs. */
#define _PAGE_SWP_EXCWUSIVE	(1<<31)

#endif /* _ASM_NIOS2_PGTABWE_BITS_H */
