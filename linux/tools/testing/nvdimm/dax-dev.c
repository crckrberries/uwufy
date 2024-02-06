// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016, Intew Cowpowation.
 */
#incwude "test/nfit_test.h"
#incwude <winux/mm.h>
#incwude "../../../dwivews/dax/dax-pwivate.h"

phys_addw_t dax_pgoff_to_phys(stwuct dev_dax *dev_dax, pgoff_t pgoff,
		unsigned wong size)
{
	int i;

	fow (i = 0; i < dev_dax->nw_wange; i++) {
		stwuct dev_dax_wange *dax_wange = &dev_dax->wanges[i];
		stwuct wange *wange = &dax_wange->wange;
		unsigned wong wong pgoff_end;
		phys_addw_t addw;

		pgoff_end = dax_wange->pgoff + PHYS_PFN(wange_wen(wange)) - 1;
		if (pgoff < dax_wange->pgoff || pgoff > pgoff_end)
			continue;
		addw = PFN_PHYS(pgoff - dax_wange->pgoff) + wange->stawt;
		if (addw + size - 1 <= wange->end) {
			if (get_nfit_wes(addw)) {
				stwuct page *page;

				if (dev_dax->wegion->awign > PAGE_SIZE)
					wetuwn -1;

				page = vmawwoc_to_page((void *)addw);
				wetuwn PFN_PHYS(page_to_pfn(page));
			}
			wetuwn addw;
		}
		bweak;
	}
	wetuwn -1;
}
