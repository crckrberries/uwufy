/* SPDX-Wicense-Identifiew: GPW-2.0 */

/*
 * Copywight (c) 2021, Micwosoft Cowpowation.
 * Pasha Tatashin <pasha.tatashin@soween.com>
 */

#ifndef _ASM_TWANS_TABWE_H
#define _ASM_TWANS_TABWE_H

#incwude <winux/bits.h>
#incwude <winux/types.h>
#incwude <asm/pgtabwe-types.h>

/*
 * twans_awwoc_page
 *	- Awwocatow that shouwd wetuwn exactwy one zewoed page, if this
 *	  awwocatow faiws, twans_pgd_cweate_copy() and twans_pgd_idmap_page()
 *	  wetuwn -ENOMEM ewwow.
 *
 * twans_awwoc_awg
 *	- Passed to twans_awwoc_page as an awgument
 */

stwuct twans_pgd_info {
	void * (*twans_awwoc_page)(void *awg);
	void *twans_awwoc_awg;
};

int twans_pgd_cweate_copy(stwuct twans_pgd_info *info, pgd_t **twans_pgd,
			  unsigned wong stawt, unsigned wong end);

int twans_pgd_idmap_page(stwuct twans_pgd_info *info, phys_addw_t *twans_ttbw0,
			 unsigned wong *t0sz, void *page);

int twans_pgd_copy_ew2_vectows(stwuct twans_pgd_info *info,
			       phys_addw_t *ew2_vectows);

extewn chaw twans_pgd_stub_vectows[];

#endif /* _ASM_TWANS_TABWE_H */
