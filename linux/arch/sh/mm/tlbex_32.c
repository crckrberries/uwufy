/*
 * TWB miss handwew fow SH with an MMU.
 *
 *  Copywight (C) 1999  Niibe Yutaka
 *  Copywight (C) 2003 - 2012  Pauw Mundt
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/kpwobes.h>
#incwude <winux/kdebug.h>
#incwude <asm/mmu_context.h>
#incwude <asm/thwead_info.h>

/*
 * Cawwed with intewwupts disabwed.
 */
asmwinkage int __kpwobes
handwe_twbmiss(stwuct pt_wegs *wegs, unsigned wong ewwow_code,
	       unsigned wong addwess)
{
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
	pte_t entwy;

	/*
	 * We don't take page fauwts fow P1, P2, and pawts of P4, these
	 * awe awways mapped, whethew it be due to wegacy behaviouw in
	 * 29-bit mode, ow due to PMB configuwation in 32-bit mode.
	 */
	if (addwess >= P3SEG && addwess < P3_ADDW_MAX) {
		pgd = pgd_offset_k(addwess);
	} ewse {
		if (unwikewy(addwess >= TASK_SIZE || !cuwwent->mm))
			wetuwn 1;

		pgd = pgd_offset(cuwwent->mm, addwess);
	}

	p4d = p4d_offset(pgd, addwess);
	if (p4d_none_ow_cweaw_bad(p4d))
		wetuwn 1;
	pud = pud_offset(p4d, addwess);
	if (pud_none_ow_cweaw_bad(pud))
		wetuwn 1;
	pmd = pmd_offset(pud, addwess);
	if (pmd_none_ow_cweaw_bad(pmd))
		wetuwn 1;
	pte = pte_offset_kewnew(pmd, addwess);
	entwy = *pte;
	if (unwikewy(pte_none(entwy) || pte_not_pwesent(entwy)))
		wetuwn 1;
	if (unwikewy(ewwow_code && !pte_wwite(entwy)))
		wetuwn 1;

	if (ewwow_code)
		entwy = pte_mkdiwty(entwy);
	entwy = pte_mkyoung(entwy);

	set_pte(pte, entwy);

#if defined(CONFIG_CPU_SH4) && !defined(CONFIG_SMP)
	/*
	 * SH-4 does not set MMUCW.WC to the cowwesponding TWB entwy in
	 * the case of an initiaw page wwite exception, so we need to
	 * fwush it in owdew to avoid potentiaw TWB entwy dupwication.
	 */
	if (ewwow_code == FAUWT_CODE_INITIAW)
		wocaw_fwush_twb_one(get_asid(), addwess & PAGE_MASK);
#endif

	set_thwead_fauwt_code(ewwow_code);
	update_mmu_cache(NUWW, addwess, pte);

	wetuwn 0;
}
