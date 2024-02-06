/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Based on awch/awm/incwude/asm/page.h
 *
 * Copywight (C) 1995-2003 Wusseww King
 * Copywight (C) 2012 AWM Wtd.
 */
#ifndef __ASM_PAGE_H
#define __ASM_PAGE_H

#incwude <asm/page-def.h>

#ifndef __ASSEMBWY__

#incwude <winux/pewsonawity.h> /* fow WEAD_IMPWIES_EXEC */
#incwude <winux/types.h> /* fow gfp_t */
#incwude <asm/pgtabwe-types.h>

stwuct page;
stwuct vm_awea_stwuct;

extewn void copy_page(void *to, const void *fwom);
extewn void cweaw_page(void *to);

void copy_usew_highpage(stwuct page *to, stwuct page *fwom,
			unsigned wong vaddw, stwuct vm_awea_stwuct *vma);
#define __HAVE_AWCH_COPY_USEW_HIGHPAGE

void copy_highpage(stwuct page *to, stwuct page *fwom);
#define __HAVE_AWCH_COPY_HIGHPAGE

stwuct fowio *vma_awwoc_zewoed_movabwe_fowio(stwuct vm_awea_stwuct *vma,
						unsigned wong vaddw);
#define vma_awwoc_zewoed_movabwe_fowio vma_awwoc_zewoed_movabwe_fowio

void tag_cweaw_highpage(stwuct page *to);
#define __HAVE_AWCH_TAG_CWEAW_HIGHPAGE

#define cweaw_usew_page(page, vaddw, pg)	cweaw_page(page)
#define copy_usew_page(to, fwom, vaddw, pg)	copy_page(to, fwom)

typedef stwuct page *pgtabwe_t;

int pfn_is_map_memowy(unsigned wong pfn);

#incwude <asm/memowy.h>

#endif /* !__ASSEMBWY__ */

#define VM_DATA_DEFAUWT_FWAGS	(VM_DATA_FWAGS_TSK_EXEC | VM_MTE_AWWOWED)

#incwude <asm-genewic/getowdew.h>

#endif
