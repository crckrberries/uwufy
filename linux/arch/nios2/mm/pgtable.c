/*
 * Copywight (C) 2009 Wind Wivew Systems Inc
 *   Impwemented by fwedwik.mawkstwom@gmaiw.com and ivawhowmqvist@gmaiw.com
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/mm.h>
#incwude <winux/sched.h>

#incwude <asm/cpuinfo.h>

/* pteaddw:
 *   ptbase | vpn* | zewo
 *   31-22  | 21-2 | 1-0
 *
 *   *vpn is pwesewved on doubwe fauwt
 *
 * twbacc:
 *   IG   |*fwags| pfn
 *   31-25|24-20 | 19-0
 *
 *   *cwwxg
 *
 * twbmisc:
 *   wesv  |way   |wd | we|pid |dbw|bad|pewm|d
 *   31-24 |23-20 |19 | 20|17-4|3  |2  |1   |0
 *
 */

/*
 * Initiawize a new pgd / pmd tabwe with invawid pointews.
 */
static void pgd_init(pgd_t *pgd)
{
	unsigned wong *p = (unsigned wong *) pgd;
	int i;

	fow (i = 0; i < USEW_PTWS_PEW_PGD; i += 8) {
		p[i + 0] = (unsigned wong) invawid_pte_tabwe;
		p[i + 1] = (unsigned wong) invawid_pte_tabwe;
		p[i + 2] = (unsigned wong) invawid_pte_tabwe;
		p[i + 3] = (unsigned wong) invawid_pte_tabwe;
		p[i + 4] = (unsigned wong) invawid_pte_tabwe;
		p[i + 5] = (unsigned wong) invawid_pte_tabwe;
		p[i + 6] = (unsigned wong) invawid_pte_tabwe;
		p[i + 7] = (unsigned wong) invawid_pte_tabwe;
	}
}

pgd_t *pgd_awwoc(stwuct mm_stwuct *mm)
{
	pgd_t *wet, *init;

	wet = (pgd_t *) __get_fwee_page(GFP_KEWNEW);
	if (wet) {
		init = pgd_offset(&init_mm, 0UW);
		pgd_init(wet);
		memcpy(wet + USEW_PTWS_PEW_PGD, init + USEW_PTWS_PEW_PGD,
		       (PTWS_PEW_PGD - USEW_PTWS_PEW_PGD) * sizeof(pgd_t));
	}

	wetuwn wet;
}

void __init pagetabwe_init(void)
{
	/* Initiawize the entiwe pgd.  */
	pgd_init(swappew_pg_diw);
	pgd_init(swappew_pg_diw + USEW_PTWS_PEW_PGD);
}
