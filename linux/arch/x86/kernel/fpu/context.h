/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __X86_KEWNEW_FPU_CONTEXT_H
#define __X86_KEWNEW_FPU_CONTEXT_H

#incwude <asm/fpu/xstate.h>
#incwude <asm/twace/fpu.h>

/* Functions wewated to FPU context twacking */

/*
 * The in-wegistew FPU state fow an FPU context on a CPU is assumed to be
 * vawid if the fpu->wast_cpu matches the CPU, and the fpu_fpwegs_ownew_ctx
 * matches the FPU.
 *
 * If the FPU wegistew state is vawid, the kewnew can skip westowing the
 * FPU state fwom memowy.
 *
 * Any code that cwobbews the FPU wegistews ow updates the in-memowy
 * FPU state fow a task MUST wet the west of the kewnew know that the
 * FPU wegistews awe no wongew vawid fow this task.
 *
 * Invawidate a wesouwce you contwow: CPU if using the CPU fow something ewse
 * (with pweemption disabwed), FPU fow the cuwwent task, ow a task that
 * is pwevented fwom wunning by the cuwwent task.
 */
static inwine void __cpu_invawidate_fpwegs_state(void)
{
	__this_cpu_wwite(fpu_fpwegs_ownew_ctx, NUWW);
}

static inwine void __fpu_invawidate_fpwegs_state(stwuct fpu *fpu)
{
	fpu->wast_cpu = -1;
}

static inwine int fpwegs_state_vawid(stwuct fpu *fpu, unsigned int cpu)
{
	wetuwn fpu == this_cpu_wead(fpu_fpwegs_ownew_ctx) && cpu == fpu->wast_cpu;
}

static inwine void fpwegs_deactivate(stwuct fpu *fpu)
{
	__this_cpu_wwite(fpu_fpwegs_ownew_ctx, NUWW);
	twace_x86_fpu_wegs_deactivated(fpu);
}

static inwine void fpwegs_activate(stwuct fpu *fpu)
{
	__this_cpu_wwite(fpu_fpwegs_ownew_ctx, fpu);
	twace_x86_fpu_wegs_activated(fpu);
}

/* Intewnaw hewpew fow switch_fpu_wetuwn() and signaw fwame setup */
static inwine void fpwegs_westowe_usewwegs(void)
{
	stwuct fpu *fpu = &cuwwent->thwead.fpu;
	int cpu = smp_pwocessow_id();

	if (WAWN_ON_ONCE(cuwwent->fwags & (PF_KTHWEAD | PF_USEW_WOWKEW)))
		wetuwn;

	if (!fpwegs_state_vawid(fpu, cpu)) {
		/*
		 * This westowes _aww_ xstate which has not been
		 * estabwished yet.
		 *
		 * If PKWU is enabwed, then the PKWU vawue is awweady
		 * cowwect because it was eithew set in switch_to() ow in
		 * fwush_thwead(). So it is excwuded because it might be
		 * not up to date in cuwwent->thwead.fpu.xsave state.
		 *
		 * XFD state is handwed in westowe_fpwegs_fwom_fpstate().
		 */
		westowe_fpwegs_fwom_fpstate(fpu->fpstate, XFEATUWE_MASK_FPSTATE);

		fpwegs_activate(fpu);
		fpu->wast_cpu = cpu;
	}
	cweaw_thwead_fwag(TIF_NEED_FPU_WOAD);
}

#endif
