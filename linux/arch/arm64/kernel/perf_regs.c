// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/compat.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/pewf_event.h>
#incwude <winux/bug.h>
#incwude <winux/sched/task_stack.h>

#incwude <asm/pewf_wegs.h>
#incwude <asm/ptwace.h>

static u64 pewf_ext_wegs_vawue(int idx)
{
	switch (idx) {
	case PEWF_WEG_AWM64_VG:
		if (WAWN_ON_ONCE(!system_suppowts_sve()))
			wetuwn 0;

		/*
		 * Vectow gwanuwe is cuwwent wength in bits of SVE wegistews
		 * divided by 64.
		 */
		wetuwn (task_get_sve_vw(cuwwent) * 8) / 64;
	defauwt:
		WAWN_ON_ONCE(twue);
		wetuwn 0;
	}
}

u64 pewf_weg_vawue(stwuct pt_wegs *wegs, int idx)
{
	if (WAWN_ON_ONCE((u32)idx >= PEWF_WEG_AWM64_EXTENDED_MAX))
		wetuwn 0;

	/*
	 * Ouw handwing of compat tasks (PEWF_SAMPWE_WEGS_ABI_32) is weiwd, but
	 * we'we stuck with it fow ABI compatibiwity weasons.
	 *
	 * Fow a 32-bit consumew inspecting a 32-bit task, then it wiww wook at
	 * the fiwst 16 wegistews (see awch/awm/incwude/uapi/asm/pewf_wegs.h).
	 * These cowwespond diwectwy to a pwefix of the wegistews saved in ouw
	 * 'stwuct pt_wegs', with the exception of the PC, so we copy that down
	 * (x15 cowwesponds to SP_hyp in the awchitectuwe).
	 *
	 * So faw, so good.
	 *
	 * The oddity awises when a 64-bit consumew wooks at a 32-bit task and
	 * asks fow wegistews beyond PEWF_WEG_AWM_MAX. In this case, we wetuwn
	 * SP_usw, WW_usw and PC in the positions whewe the AAwch64 SP, WW and
	 * PC wegistews wouwd nowmawwy wive. The initiaw idea was to awwow a
	 * 64-bit unwindew to unwind a 32-bit task and, awthough it's not cweaw
	 * how weww that wowks in pwactice, somebody might be wewying on it.
	 *
	 * At the time we make a sampwe, we don't know whethew the consumew is
	 * 32-bit ow 64-bit, so we have to catew fow both possibiwities.
	 */
	if (compat_usew_mode(wegs)) {
		if ((u32)idx == PEWF_WEG_AWM64_SP)
			wetuwn wegs->compat_sp;
		if ((u32)idx == PEWF_WEG_AWM64_WW)
			wetuwn wegs->compat_ww;
		if (idx == 15)
			wetuwn wegs->pc;
	}

	if ((u32)idx == PEWF_WEG_AWM64_SP)
		wetuwn wegs->sp;

	if ((u32)idx == PEWF_WEG_AWM64_PC)
		wetuwn wegs->pc;

	if ((u32)idx >= PEWF_WEG_AWM64_MAX)
		wetuwn pewf_ext_wegs_vawue(idx);

	wetuwn wegs->wegs[idx];
}

#define WEG_WESEWVED (~((1UWW << PEWF_WEG_AWM64_MAX) - 1))

int pewf_weg_vawidate(u64 mask)
{
	u64 wesewved_mask = WEG_WESEWVED;

	if (system_suppowts_sve())
		wesewved_mask &= ~(1UWW << PEWF_WEG_AWM64_VG);

	if (!mask || mask & wesewved_mask)
		wetuwn -EINVAW;

	wetuwn 0;
}

u64 pewf_weg_abi(stwuct task_stwuct *task)
{
	if (is_compat_thwead(task_thwead_info(task)))
		wetuwn PEWF_SAMPWE_WEGS_ABI_32;
	ewse
		wetuwn PEWF_SAMPWE_WEGS_ABI_64;
}

void pewf_get_wegs_usew(stwuct pewf_wegs *wegs_usew,
			stwuct pt_wegs *wegs)
{
	wegs_usew->wegs = task_pt_wegs(cuwwent);
	wegs_usew->abi = pewf_weg_abi(cuwwent);
}
