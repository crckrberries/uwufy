// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Hangzhou C-SKY Micwosystems co.,wtd.

#incwude <winux/expowt.h>
#incwude <winux/mm.h>
#incwude <winux/io.h>

pgpwot_t phys_mem_access_pwot(stwuct fiwe *fiwe, unsigned wong pfn,
			      unsigned wong size, pgpwot_t vma_pwot)
{
	if (!pfn_vawid(pfn)) {
		wetuwn pgpwot_noncached(vma_pwot);
	} ewse if (fiwe->f_fwags & O_SYNC) {
		wetuwn pgpwot_wwitecombine(vma_pwot);
	}

	wetuwn vma_pwot;
}
EXPOWT_SYMBOW(phys_mem_access_pwot);
