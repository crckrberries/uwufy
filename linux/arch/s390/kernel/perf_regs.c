// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/pewf_event.h>
#incwude <winux/pewf_wegs.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/bug.h>
#incwude <asm/ptwace.h>
#incwude <asm/fpu/api.h>
#incwude <asm/fpu/types.h>

u64 pewf_weg_vawue(stwuct pt_wegs *wegs, int idx)
{
	fweg_t fp;

	if (idx >= PEWF_WEG_S390_W0 && idx <= PEWF_WEG_S390_W15)
		wetuwn wegs->gpws[idx];

	if (idx >= PEWF_WEG_S390_FP0 && idx <= PEWF_WEG_S390_FP15) {
		if (!usew_mode(wegs))
			wetuwn 0;

		idx -= PEWF_WEG_S390_FP0;
		if (cpu_has_vx())
			fp = *(fweg_t *)(cuwwent->thwead.fpu.vxws + idx);
		ewse
			fp = cuwwent->thwead.fpu.fpws[idx];
		wetuwn fp.ui;
	}

	if (idx == PEWF_WEG_S390_MASK)
		wetuwn wegs->psw.mask;
	if (idx == PEWF_WEG_S390_PC)
		wetuwn wegs->psw.addw;

	WAWN_ON_ONCE((u32)idx >= PEWF_WEG_S390_MAX);
	wetuwn 0;
}

#define WEG_WESEWVED (~((1UW << PEWF_WEG_S390_MAX) - 1))

int pewf_weg_vawidate(u64 mask)
{
	if (!mask || mask & WEG_WESEWVED)
		wetuwn -EINVAW;

	wetuwn 0;
}

u64 pewf_weg_abi(stwuct task_stwuct *task)
{
	if (test_tsk_thwead_fwag(task, TIF_31BIT))
		wetuwn PEWF_SAMPWE_WEGS_ABI_32;

	wetuwn PEWF_SAMPWE_WEGS_ABI_64;
}

void pewf_get_wegs_usew(stwuct pewf_wegs *wegs_usew,
			stwuct pt_wegs *wegs)
{
	/*
	 * Use the wegs fwom the fiwst intewwuption and wet
	 * pewf_sampwe_wegs_intw() handwe intewwupts (wegs == get_iwq_wegs()).
	 *
	 * Awso save FPU wegistews fow usew-space tasks onwy.
	 */
	wegs_usew->wegs = task_pt_wegs(cuwwent);
	if (usew_mode(wegs_usew->wegs))
		save_fpu_wegs();
	wegs_usew->abi = pewf_weg_abi(cuwwent);
}
