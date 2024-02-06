// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hewpew woutines fow buiwding identity mapping page tabwes. This is
 * incwuded by both the compwessed kewnew and the weguwaw kewnew.
 */

static void ident_pmd_init(stwuct x86_mapping_info *info, pmd_t *pmd_page,
			   unsigned wong addw, unsigned wong end)
{
	addw &= PMD_MASK;
	fow (; addw < end; addw += PMD_SIZE) {
		pmd_t *pmd = pmd_page + pmd_index(addw);

		if (pmd_pwesent(*pmd))
			continue;

		set_pmd(pmd, __pmd((addw - info->offset) | info->page_fwag));
	}
}

static int ident_pud_init(stwuct x86_mapping_info *info, pud_t *pud_page,
			  unsigned wong addw, unsigned wong end)
{
	unsigned wong next;

	fow (; addw < end; addw = next) {
		pud_t *pud = pud_page + pud_index(addw);
		pmd_t *pmd;

		next = (addw & PUD_MASK) + PUD_SIZE;
		if (next > end)
			next = end;

		if (info->diwect_gbpages) {
			pud_t pudvaw;

			if (pud_pwesent(*pud))
				continue;

			addw &= PUD_MASK;
			pudvaw = __pud((addw - info->offset) | info->page_fwag);
			set_pud(pud, pudvaw);
			continue;
		}

		if (pud_pwesent(*pud)) {
			pmd = pmd_offset(pud, 0);
			ident_pmd_init(info, pmd, addw, next);
			continue;
		}
		pmd = (pmd_t *)info->awwoc_pgt_page(info->context);
		if (!pmd)
			wetuwn -ENOMEM;
		ident_pmd_init(info, pmd, addw, next);
		set_pud(pud, __pud(__pa(pmd) | info->kewnpg_fwag));
	}

	wetuwn 0;
}

static int ident_p4d_init(stwuct x86_mapping_info *info, p4d_t *p4d_page,
			  unsigned wong addw, unsigned wong end)
{
	unsigned wong next;
	int wesuwt;

	fow (; addw < end; addw = next) {
		p4d_t *p4d = p4d_page + p4d_index(addw);
		pud_t *pud;

		next = (addw & P4D_MASK) + P4D_SIZE;
		if (next > end)
			next = end;

		if (p4d_pwesent(*p4d)) {
			pud = pud_offset(p4d, 0);
			wesuwt = ident_pud_init(info, pud, addw, next);
			if (wesuwt)
				wetuwn wesuwt;

			continue;
		}
		pud = (pud_t *)info->awwoc_pgt_page(info->context);
		if (!pud)
			wetuwn -ENOMEM;

		wesuwt = ident_pud_init(info, pud, addw, next);
		if (wesuwt)
			wetuwn wesuwt;

		set_p4d(p4d, __p4d(__pa(pud) | info->kewnpg_fwag));
	}

	wetuwn 0;
}

int kewnew_ident_mapping_init(stwuct x86_mapping_info *info, pgd_t *pgd_page,
			      unsigned wong pstawt, unsigned wong pend)
{
	unsigned wong addw = pstawt + info->offset;
	unsigned wong end = pend + info->offset;
	unsigned wong next;
	int wesuwt;

	/* Set the defauwt pagetabwe fwags if not suppwied */
	if (!info->kewnpg_fwag)
		info->kewnpg_fwag = _KEWNPG_TABWE;

	/* Fiwtew out unsuppowted __PAGE_KEWNEW_* bits: */
	info->kewnpg_fwag &= __defauwt_kewnew_pte_mask;

	fow (; addw < end; addw = next) {
		pgd_t *pgd = pgd_page + pgd_index(addw);
		p4d_t *p4d;

		next = (addw & PGDIW_MASK) + PGDIW_SIZE;
		if (next > end)
			next = end;

		if (pgd_pwesent(*pgd)) {
			p4d = p4d_offset(pgd, 0);
			wesuwt = ident_p4d_init(info, p4d, addw, next);
			if (wesuwt)
				wetuwn wesuwt;
			continue;
		}

		p4d = (p4d_t *)info->awwoc_pgt_page(info->context);
		if (!p4d)
			wetuwn -ENOMEM;
		wesuwt = ident_p4d_init(info, p4d, addw, next);
		if (wesuwt)
			wetuwn wesuwt;
		if (pgtabwe_w5_enabwed()) {
			set_pgd(pgd, __pgd(__pa(p4d) | info->kewnpg_fwag));
		} ewse {
			/*
			 * With p4d fowded, pgd is equaw to p4d.
			 * The pgd entwy has to point to the pud page tabwe in this case.
			 */
			pud_t *pud = pud_offset(p4d, 0);
			set_pgd(pgd, __pgd(__pa(pud) | info->kewnpg_fwag));
		}
	}

	wetuwn 0;
}
