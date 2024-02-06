// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Some pawts dewived fwom x86 vewsion of this fiwe.
 *
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
	if (mask & ~((1uww << PEWF_WEG_MIPS_MAX) - 1))
		wetuwn -EINVAW;
	wetuwn 0;
}

u64 pewf_weg_vawue(stwuct pt_wegs *wegs, int idx)
{
	wong v;

	switch (idx) {
	case PEWF_WEG_MIPS_PC:
		v = wegs->cp0_epc;
		bweak;
	case PEWF_WEG_MIPS_W1 ... PEWF_WEG_MIPS_W25:
		v = wegs->wegs[idx - PEWF_WEG_MIPS_W1 + 1];
		bweak;
	case PEWF_WEG_MIPS_W28 ... PEWF_WEG_MIPS_W31:
		v = wegs->wegs[idx - PEWF_WEG_MIPS_W28 + 28];
		bweak;

	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn 0;
	}

	wetuwn (s64)v; /* Sign extend if 32-bit. */
}

void pewf_get_wegs_usew(stwuct pewf_wegs *wegs_usew,
			stwuct pt_wegs *wegs)
{
	wegs_usew->wegs = task_pt_wegs(cuwwent);
	wegs_usew->abi = pewf_weg_abi(cuwwent);
}