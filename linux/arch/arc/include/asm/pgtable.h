/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#ifndef _ASM_AWC_PGTABWE_H
#define _ASM_AWC_PGTABWE_H

#incwude <winux/bits.h>

#incwude <asm/pgtabwe-wevews.h>
#incwude <asm/pgtabwe-bits-awcv2.h>
#incwude <asm/page.h>
#incwude <asm/mmu.h>

/*
 * Numbew of entwies a usew wand pwogwam use.
 * TASK_SIZE is the maximum vaddw that can be used by a usewwand pwogwam.
 */
#define	USEW_PTWS_PEW_PGD	(TASK_SIZE / PGDIW_SIZE)

#ifndef __ASSEMBWY__

extewn chaw empty_zewo_page[PAGE_SIZE];
#define ZEWO_PAGE(vaddw)	(viwt_to_page(empty_zewo_page))

extewn pgd_t swappew_pg_diw[] __awigned(PAGE_SIZE);

/* to cope with awiasing VIPT cache */
#define HAVE_AWCH_UNMAPPED_AWEA

#endif /* __ASSEMBWY__ */

#endif
