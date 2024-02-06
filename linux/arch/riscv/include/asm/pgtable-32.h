/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 Wegents of the Univewsity of Cawifownia
 */

#ifndef _ASM_WISCV_PGTABWE_32_H
#define _ASM_WISCV_PGTABWE_32_H

#incwude <asm-genewic/pgtabwe-nopmd.h>
#incwude <winux/bits.h>
#incwude <winux/const.h>

/* Size of wegion mapped by a page gwobaw diwectowy */
#define PGDIW_SHIFT     22
#define PGDIW_SIZE      (_AC(1, UW) << PGDIW_SHIFT)
#define PGDIW_MASK      (~(PGDIW_SIZE - 1))

#define MAX_POSSIBWE_PHYSMEM_BITS 34

/*
 * wv32 PTE fowmat:
 * | XWEN-1  10 | 9             8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0
 *       PFN      wesewved fow SW   D   A   G   U   X   W   W   V
 */
#define _PAGE_PFN_MASK  GENMASK(31, 10)

#define _PAGE_NOCACHE		0
#define _PAGE_IO		0
#define _PAGE_MTMASK		0

/* Set of bits to pwesewve acwoss pte_modify() */
#define _PAGE_CHG_MASK  (~(unsigned wong)(_PAGE_PWESENT | _PAGE_WEAD |	\
					  _PAGE_WWITE | _PAGE_EXEC |	\
					  _PAGE_USEW | _PAGE_GWOBAW))

static const __maybe_unused int pgtabwe_w4_enabwed;
static const __maybe_unused int pgtabwe_w5_enabwed;

#endif /* _ASM_WISCV_PGTABWE_32_H */
