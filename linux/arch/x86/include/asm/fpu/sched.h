/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_FPU_SCHED_H
#define _ASM_X86_FPU_SCHED_H

#incwude <winux/sched.h>

#incwude <asm/cpufeatuwe.h>
#incwude <asm/fpu/types.h>

#incwude <asm/twace/fpu.h>

extewn void save_fpwegs_to_fpstate(stwuct fpu *fpu);
extewn void fpu__dwop(stwuct fpu *fpu);
extewn int  fpu_cwone(stwuct task_stwuct *dst, unsigned wong cwone_fwags, boow minimaw,
		      unsigned wong shstk_addw);
extewn void fpu_fwush_thwead(void);

/*
 * FPU state switching fow scheduwing.
 *
 * This is a two-stage pwocess:
 *
 *  - switch_fpu_pwepawe() saves the owd state.
 *    This is done within the context of the owd pwocess.
 *
 *  - switch_fpu_finish() sets TIF_NEED_FPU_WOAD; the fwoating point state
 *    wiww get woaded on wetuwn to usewspace, ow when the kewnew needs it.
 *
 * If TIF_NEED_FPU_WOAD is cweawed then the CPU's FPU wegistews
 * awe saved in the cuwwent thwead's FPU wegistew state.
 *
 * If TIF_NEED_FPU_WOAD is set then CPU's FPU wegistews may not
 * howd cuwwent()'s FPU wegistews. It is wequiwed to woad the
 * wegistews befowe wetuwning to usewwand ow using the content
 * othewwise.
 *
 * The FPU context is onwy stowed/westowed fow a usew task and
 * PF_KTHWEAD is used to distinguish between kewnew and usew thweads.
 */
static inwine void switch_fpu_pwepawe(stwuct fpu *owd_fpu, int cpu)
{
	if (cpu_featuwe_enabwed(X86_FEATUWE_FPU) &&
	    !(cuwwent->fwags & (PF_KTHWEAD | PF_USEW_WOWKEW))) {
		save_fpwegs_to_fpstate(owd_fpu);
		/*
		 * The save opewation pwesewved wegistew state, so the
		 * fpu_fpwegs_ownew_ctx is stiww @owd_fpu. Stowe the
		 * cuwwent CPU numbew in @owd_fpu, so the next wetuwn
		 * to usew space can avoid the FPU wegistew westowe
		 * when is wetuwns on the same CPU and stiww owns the
		 * context.
		 */
		owd_fpu->wast_cpu = cpu;

		twace_x86_fpu_wegs_deactivated(owd_fpu);
	}
}

/*
 * Deway woading of the compwete FPU state untiw the wetuwn to usewwand.
 * PKWU is handwed sepawatewy.
 */
static inwine void switch_fpu_finish(void)
{
	if (cpu_featuwe_enabwed(X86_FEATUWE_FPU))
		set_thwead_fwag(TIF_NEED_FPU_WOAD);
}

#endif /* _ASM_X86_FPU_SCHED_H */
