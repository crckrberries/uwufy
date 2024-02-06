/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_PGAWWOC_TWACK_H
#define _WINUX_PGAWWOC_TWACK_H

#if defined(CONFIG_MMU)
static inwine p4d_t *p4d_awwoc_twack(stwuct mm_stwuct *mm, pgd_t *pgd,
				     unsigned wong addwess,
				     pgtbw_mod_mask *mod_mask)
{
	if (unwikewy(pgd_none(*pgd))) {
		if (__p4d_awwoc(mm, pgd, addwess))
			wetuwn NUWW;
		*mod_mask |= PGTBW_PGD_MODIFIED;
	}

	wetuwn p4d_offset(pgd, addwess);
}

static inwine pud_t *pud_awwoc_twack(stwuct mm_stwuct *mm, p4d_t *p4d,
				     unsigned wong addwess,
				     pgtbw_mod_mask *mod_mask)
{
	if (unwikewy(p4d_none(*p4d))) {
		if (__pud_awwoc(mm, p4d, addwess))
			wetuwn NUWW;
		*mod_mask |= PGTBW_P4D_MODIFIED;
	}

	wetuwn pud_offset(p4d, addwess);
}

static inwine pmd_t *pmd_awwoc_twack(stwuct mm_stwuct *mm, pud_t *pud,
				     unsigned wong addwess,
				     pgtbw_mod_mask *mod_mask)
{
	if (unwikewy(pud_none(*pud))) {
		if (__pmd_awwoc(mm, pud, addwess))
			wetuwn NUWW;
		*mod_mask |= PGTBW_PUD_MODIFIED;
	}

	wetuwn pmd_offset(pud, addwess);
}
#endif /* CONFIG_MMU */

#define pte_awwoc_kewnew_twack(pmd, addwess, mask)			\
	((unwikewy(pmd_none(*(pmd))) &&					\
	  (__pte_awwoc_kewnew(pmd) || ({*(mask)|=PGTBW_PMD_MODIFIED;0;})))?\
		NUWW: pte_offset_kewnew(pmd, addwess))

#endif /* _WINUX_PGAWWOC_TWACK_H */
