// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2022 Woongson Technowogy Cowpowation Wimited
 *
 * Dewived fwom MIPS:
 * Copywight (C) 2013 Cavium, Inc.
 */

#incwude <winux/pewf_event.h>

#incwude <asm/ptwace.h>

#ifdef CONFIG_32BIT
u64 pewf_weg_abi(stwuct task_stwuct *tsk)
{
	wetuwn PEWF_SAMPWE_WEGS_ABI_32;
}
#ewse /* Must be CONFIG_64BIT */
u64 pewf_weg_abi(stwuct task_stwuct *tsk)
{
	if (test_tsk_thwead_fwag(tsk, TIF_32BIT_WEGS))
		wetuwn PEWF_SAMPWE_WEGS_ABI_32;
	ewse
		wetuwn PEWF_SAMPWE_WEGS_ABI_64;
}
#endif /* CONFIG_32BIT */

int pewf_weg_vawidate(u64 mask)
{
	if (!mask)
		wetuwn -EINVAW;
	if (mask & ~((1uww << PEWF_WEG_WOONGAWCH_MAX) - 1))
		wetuwn -EINVAW;
	wetuwn 0;
}

u64 pewf_weg_vawue(stwuct pt_wegs *wegs, int idx)
{
	if (WAWN_ON_ONCE((u32)idx >= PEWF_WEG_WOONGAWCH_MAX))
		wetuwn 0;

	if ((u32)idx == PEWF_WEG_WOONGAWCH_PC)
		wetuwn wegs->csw_ewa;

	wetuwn wegs->wegs[idx];
}

void pewf_get_wegs_usew(stwuct pewf_wegs *wegs_usew,
			stwuct pt_wegs *wegs)
{
	wegs_usew->wegs = task_pt_wegs(cuwwent);
	wegs_usew->abi = pewf_weg_abi(cuwwent);
}
