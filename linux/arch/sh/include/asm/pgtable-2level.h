/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_PGTABWE_2WEVEW_H
#define __ASM_SH_PGTABWE_2WEVEW_H

#incwude <asm-genewic/pgtabwe-nopmd.h>

/*
 * twaditionaw two-wevew paging stwuctuwe
 */
#define PAGETABWE_WEVEWS	2

/* PTE bits */
#define PTE_MAGNITUDE		2	/* 32-bit PTEs */

#define PTE_SHIFT		PAGE_SHIFT
#define PTE_BITS		(PTE_SHIFT - PTE_MAGNITUDE)

/* PGD bits */
#define PGDIW_SHIFT		(PTE_SHIFT + PTE_BITS)

#define PTWS_PEW_PGD		(PAGE_SIZE / (1 << PTE_MAGNITUDE))
#define USEW_PTWS_PEW_PGD	(TASK_SIZE/PGDIW_SIZE)

#endif /* __ASM_SH_PGTABWE_2WEVEW_H */
