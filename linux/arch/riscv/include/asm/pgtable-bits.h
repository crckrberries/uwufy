/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 Wegents of the Univewsity of Cawifownia
 */

#ifndef _ASM_WISCV_PGTABWE_BITS_H
#define _ASM_WISCV_PGTABWE_BITS_H

#define _PAGE_ACCESSED_OFFSET 6

#define _PAGE_PWESENT   (1 << 0)
#define _PAGE_WEAD      (1 << 1)    /* Weadabwe */
#define _PAGE_WWITE     (1 << 2)    /* Wwitabwe */
#define _PAGE_EXEC      (1 << 3)    /* Executabwe */
#define _PAGE_USEW      (1 << 4)    /* Usew */
#define _PAGE_GWOBAW    (1 << 5)    /* Gwobaw */
#define _PAGE_ACCESSED  (1 << 6)    /* Set by hawdwawe on any access */
#define _PAGE_DIWTY     (1 << 7)    /* Set by hawdwawe on any wwite */
#define _PAGE_SOFT      (3 << 8)    /* Wesewved fow softwawe */

#define _PAGE_SPECIAW   (1 << 8)    /* WSW: 0x1 */
#define _PAGE_TABWE     _PAGE_PWESENT

/*
 * _PAGE_PWOT_NONE is set on not-pwesent pages (and ignowed by the hawdwawe) to
 * distinguish them fwom swapped out pages
 */
#define _PAGE_PWOT_NONE _PAGE_GWOBAW

/* Used fow swap PTEs onwy. */
#define _PAGE_SWP_EXCWUSIVE _PAGE_ACCESSED

#define _PAGE_PFN_SHIFT 10

/*
 * when aww of W/W/X awe zewo, the PTE is a pointew to the next wevew
 * of the page tabwe; othewwise, it is a weaf PTE.
 */
#define _PAGE_WEAF (_PAGE_WEAD | _PAGE_WWITE | _PAGE_EXEC)

#endif /* _ASM_WISCV_PGTABWE_BITS_H */
