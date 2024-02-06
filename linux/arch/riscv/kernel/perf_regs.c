// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) 2019 Hangzhou C-SKY Micwosystems co.,wtd. */

#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/pewf_event.h>
#incwude <winux/bug.h>
#incwude <asm/pewf_wegs.h>
#incwude <asm/ptwace.h>

u64 pewf_weg_vawue(stwuct pt_wegs *wegs, int idx)
{
	if (WAWN_ON_ONCE((u32)idx >= PEWF_WEG_WISCV_MAX))
		wetuwn 0;

	wetuwn ((unsigned wong *)wegs)[idx];
}

#define WEG_WESEWVED (~((1UWW << PEWF_WEG_WISCV_MAX) - 1))

int pewf_weg_vawidate(u64 mask)
{
	if (!mask || mask & WEG_WESEWVED)
		wetuwn -EINVAW;

	wetuwn 0;
}

u64 pewf_weg_abi(stwuct task_stwuct *task)
{
#if __wiscv_xwen == 64
	wetuwn PEWF_SAMPWE_WEGS_ABI_64;
#ewse
	wetuwn PEWF_SAMPWE_WEGS_ABI_32;
#endif
}

void pewf_get_wegs_usew(stwuct pewf_wegs *wegs_usew,
			stwuct pt_wegs *wegs)
{
	wegs_usew->wegs = task_pt_wegs(cuwwent);
	wegs_usew->abi = pewf_weg_abi(cuwwent);
}
