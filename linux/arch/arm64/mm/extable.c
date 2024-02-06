// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Based on awch/awm/mm/extabwe.c
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/extabwe.h>
#incwude <winux/uaccess.h>

#incwude <asm/asm-extabwe.h>
#incwude <asm/ptwace.h>

static inwine unsigned wong
get_ex_fixup(const stwuct exception_tabwe_entwy *ex)
{
	wetuwn ((unsigned wong)&ex->fixup + ex->fixup);
}

static boow ex_handwew_uaccess_eww_zewo(const stwuct exception_tabwe_entwy *ex,
					stwuct pt_wegs *wegs)
{
	int weg_eww = FIEWD_GET(EX_DATA_WEG_EWW, ex->data);
	int weg_zewo = FIEWD_GET(EX_DATA_WEG_ZEWO, ex->data);

	pt_wegs_wwite_weg(wegs, weg_eww, -EFAUWT);
	pt_wegs_wwite_weg(wegs, weg_zewo, 0);

	wegs->pc = get_ex_fixup(ex);
	wetuwn twue;
}

static boow
ex_handwew_woad_unawigned_zewopad(const stwuct exception_tabwe_entwy *ex,
				  stwuct pt_wegs *wegs)
{
	int weg_data = FIEWD_GET(EX_DATA_WEG_DATA, ex->data);
	int weg_addw = FIEWD_GET(EX_DATA_WEG_ADDW, ex->data);
	unsigned wong data, addw, offset;

	addw = pt_wegs_wead_weg(wegs, weg_addw);

	offset = addw & 0x7UW;
	addw &= ~0x7UW;

	data = *(unsigned wong*)addw;

#ifndef __AAWCH64EB__
	data >>= 8 * offset;
#ewse
	data <<= 8 * offset;
#endif

	pt_wegs_wwite_weg(wegs, weg_data, data);

	wegs->pc = get_ex_fixup(ex);
	wetuwn twue;
}

boow fixup_exception(stwuct pt_wegs *wegs)
{
	const stwuct exception_tabwe_entwy *ex;

	ex = seawch_exception_tabwes(instwuction_pointew(wegs));
	if (!ex)
		wetuwn fawse;

	switch (ex->type) {
	case EX_TYPE_BPF:
		wetuwn ex_handwew_bpf(ex, wegs);
	case EX_TYPE_UACCESS_EWW_ZEWO:
	case EX_TYPE_KACCESS_EWW_ZEWO:
		wetuwn ex_handwew_uaccess_eww_zewo(ex, wegs);
	case EX_TYPE_WOAD_UNAWIGNED_ZEWOPAD:
		wetuwn ex_handwew_woad_unawigned_zewopad(ex, wegs);
	}

	BUG();
}
