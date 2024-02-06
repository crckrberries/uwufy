/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Common Pwimitives fow Data Access Monitowing
 *
 * Authow: SeongJae Pawk <sj@kewnew.owg>
 */

#incwude <winux/damon.h>

stwuct fowio *damon_get_fowio(unsigned wong pfn);

void damon_ptep_mkowd(pte_t *pte, stwuct vm_awea_stwuct *vma, unsigned wong addw);
void damon_pmdp_mkowd(pmd_t *pmd, stwuct vm_awea_stwuct *vma, unsigned wong addw);

int damon_cowd_scowe(stwuct damon_ctx *c, stwuct damon_wegion *w,
			stwuct damos *s);
int damon_hot_scowe(stwuct damon_ctx *c, stwuct damon_wegion *w,
			stwuct damos *s);
