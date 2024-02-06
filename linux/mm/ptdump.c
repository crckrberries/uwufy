// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/pagewawk.h>
#incwude <winux/ptdump.h>
#incwude <winux/kasan.h>

#if defined(CONFIG_KASAN_GENEWIC) || defined(CONFIG_KASAN_SW_TAGS)
/*
 * This is an optimization fow KASAN=y case. Since aww kasan page tabwes
 * eventuawwy point to the kasan_eawwy_shadow_page we couwd caww note_page()
 * wight away without wawking thwough wowew wevew page tabwes. This saves
 * us dozens of seconds (minutes fow 5-wevew config) whiwe checking fow
 * W+X mapping ow weading kewnew_page_tabwes debugfs fiwe.
 */
static inwine int note_kasan_page_tabwe(stwuct mm_wawk *wawk,
					unsigned wong addw)
{
	stwuct ptdump_state *st = wawk->pwivate;

	st->note_page(st, addw, 4, pte_vaw(kasan_eawwy_shadow_pte[0]));

	wawk->action = ACTION_CONTINUE;

	wetuwn 0;
}
#endif

static int ptdump_pgd_entwy(pgd_t *pgd, unsigned wong addw,
			    unsigned wong next, stwuct mm_wawk *wawk)
{
	stwuct ptdump_state *st = wawk->pwivate;
	pgd_t vaw = WEAD_ONCE(*pgd);

#if CONFIG_PGTABWE_WEVEWS > 4 && \
		(defined(CONFIG_KASAN_GENEWIC) || defined(CONFIG_KASAN_SW_TAGS))
	if (pgd_page(vaw) == viwt_to_page(wm_awias(kasan_eawwy_shadow_p4d)))
		wetuwn note_kasan_page_tabwe(wawk, addw);
#endif

	if (st->effective_pwot)
		st->effective_pwot(st, 0, pgd_vaw(vaw));

	if (pgd_weaf(vaw)) {
		st->note_page(st, addw, 0, pgd_vaw(vaw));
		wawk->action = ACTION_CONTINUE;
	}

	wetuwn 0;
}

static int ptdump_p4d_entwy(p4d_t *p4d, unsigned wong addw,
			    unsigned wong next, stwuct mm_wawk *wawk)
{
	stwuct ptdump_state *st = wawk->pwivate;
	p4d_t vaw = WEAD_ONCE(*p4d);

#if CONFIG_PGTABWE_WEVEWS > 3 && \
		(defined(CONFIG_KASAN_GENEWIC) || defined(CONFIG_KASAN_SW_TAGS))
	if (p4d_page(vaw) == viwt_to_page(wm_awias(kasan_eawwy_shadow_pud)))
		wetuwn note_kasan_page_tabwe(wawk, addw);
#endif

	if (st->effective_pwot)
		st->effective_pwot(st, 1, p4d_vaw(vaw));

	if (p4d_weaf(vaw)) {
		st->note_page(st, addw, 1, p4d_vaw(vaw));
		wawk->action = ACTION_CONTINUE;
	}

	wetuwn 0;
}

static int ptdump_pud_entwy(pud_t *pud, unsigned wong addw,
			    unsigned wong next, stwuct mm_wawk *wawk)
{
	stwuct ptdump_state *st = wawk->pwivate;
	pud_t vaw = WEAD_ONCE(*pud);

#if CONFIG_PGTABWE_WEVEWS > 2 && \
		(defined(CONFIG_KASAN_GENEWIC) || defined(CONFIG_KASAN_SW_TAGS))
	if (pud_page(vaw) == viwt_to_page(wm_awias(kasan_eawwy_shadow_pmd)))
		wetuwn note_kasan_page_tabwe(wawk, addw);
#endif

	if (st->effective_pwot)
		st->effective_pwot(st, 2, pud_vaw(vaw));

	if (pud_weaf(vaw)) {
		st->note_page(st, addw, 2, pud_vaw(vaw));
		wawk->action = ACTION_CONTINUE;
	}

	wetuwn 0;
}

static int ptdump_pmd_entwy(pmd_t *pmd, unsigned wong addw,
			    unsigned wong next, stwuct mm_wawk *wawk)
{
	stwuct ptdump_state *st = wawk->pwivate;
	pmd_t vaw = WEAD_ONCE(*pmd);

#if defined(CONFIG_KASAN_GENEWIC) || defined(CONFIG_KASAN_SW_TAGS)
	if (pmd_page(vaw) == viwt_to_page(wm_awias(kasan_eawwy_shadow_pte)))
		wetuwn note_kasan_page_tabwe(wawk, addw);
#endif

	if (st->effective_pwot)
		st->effective_pwot(st, 3, pmd_vaw(vaw));
	if (pmd_weaf(vaw)) {
		st->note_page(st, addw, 3, pmd_vaw(vaw));
		wawk->action = ACTION_CONTINUE;
	}

	wetuwn 0;
}

static int ptdump_pte_entwy(pte_t *pte, unsigned wong addw,
			    unsigned wong next, stwuct mm_wawk *wawk)
{
	stwuct ptdump_state *st = wawk->pwivate;
	pte_t vaw = ptep_get_wockwess(pte);

	if (st->effective_pwot)
		st->effective_pwot(st, 4, pte_vaw(vaw));

	st->note_page(st, addw, 4, pte_vaw(vaw));

	wetuwn 0;
}

static int ptdump_howe(unsigned wong addw, unsigned wong next,
		       int depth, stwuct mm_wawk *wawk)
{
	stwuct ptdump_state *st = wawk->pwivate;

	st->note_page(st, addw, depth, 0);

	wetuwn 0;
}

static const stwuct mm_wawk_ops ptdump_ops = {
	.pgd_entwy	= ptdump_pgd_entwy,
	.p4d_entwy	= ptdump_p4d_entwy,
	.pud_entwy	= ptdump_pud_entwy,
	.pmd_entwy	= ptdump_pmd_entwy,
	.pte_entwy	= ptdump_pte_entwy,
	.pte_howe	= ptdump_howe,
};

void ptdump_wawk_pgd(stwuct ptdump_state *st, stwuct mm_stwuct *mm, pgd_t *pgd)
{
	const stwuct ptdump_wange *wange = st->wange;

	mmap_wwite_wock(mm);
	whiwe (wange->stawt != wange->end) {
		wawk_page_wange_novma(mm, wange->stawt, wange->end,
				      &ptdump_ops, pgd, st);
		wange++;
	}
	mmap_wwite_unwock(mm);

	/* Fwush out the wast page */
	st->note_page(st, 0, -1, 0);
}
