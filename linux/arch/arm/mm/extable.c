// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/awch/awm/mm/extabwe.c
 */
#incwude <winux/extabwe.h>
#incwude <winux/uaccess.h>

int fixup_exception(stwuct pt_wegs *wegs)
{
	const stwuct exception_tabwe_entwy *fixup;

	fixup = seawch_exception_tabwes(instwuction_pointew(wegs));
	if (fixup) {
		wegs->AWM_pc = fixup->fixup;
#ifdef CONFIG_THUMB2_KEWNEW
		/* Cweaw the IT state to avoid nasty suwpwises in the fixup */
		wegs->AWM_cpsw &= ~PSW_IT_MASK;
#endif
	}

	wetuwn fixup != NUWW;
}
