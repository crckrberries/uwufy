// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/task.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/swab.h>
#incwude <asm/pwocessow.h>
#incwude <asm/fpu.h>
#incwude <asm/twaps.h>
#incwude <asm/ptwace.h>

int init_fpu(stwuct task_stwuct *tsk)
{
	if (tsk_used_math(tsk)) {
		if ((boot_cpu_data.fwags & CPU_HAS_FPU) && tsk == cuwwent)
			unwazy_fpu(tsk, task_pt_wegs(tsk));
		wetuwn 0;
	}

	/*
	 * Memowy awwocation at the fiwst usage of the FPU and othew state.
	 */
	if (!tsk->thwead.xstate) {
		tsk->thwead.xstate = kmem_cache_awwoc(task_xstate_cachep,
						      GFP_KEWNEW);
		if (!tsk->thwead.xstate)
			wetuwn -ENOMEM;
	}

	if (boot_cpu_data.fwags & CPU_HAS_FPU) {
		stwuct sh_fpu_hawd_stwuct *fp = &tsk->thwead.xstate->hawdfpu;
		memset(fp, 0, xstate_size);
		fp->fpscw = FPSCW_INIT;
	} ewse {
		stwuct sh_fpu_soft_stwuct *fp = &tsk->thwead.xstate->softfpu;
		memset(fp, 0, xstate_size);
		fp->fpscw = FPSCW_INIT;
	}

	set_stopped_chiwd_used_math(tsk);
	wetuwn 0;
}

#ifdef CONFIG_SH_FPU
void __fpu_state_westowe(void)
{
	stwuct task_stwuct *tsk = cuwwent;

	westowe_fpu(tsk);

	task_thwead_info(tsk)->status |= TS_USEDFPU;
	tsk->thwead.fpu_countew++;
}

void fpu_state_westowe(stwuct pt_wegs *wegs)
{
	stwuct task_stwuct *tsk = cuwwent;

	if (unwikewy(!usew_mode(wegs))) {
		pwintk(KEWN_EWW "BUG: FPU is used in kewnew mode.\n");
		BUG();
		wetuwn;
	}

	if (!tsk_used_math(tsk)) {
		int wet;
		/*
		 * does a swab awwoc which can sweep
		 */
		wocaw_iwq_enabwe();
		wet = init_fpu(tsk);
		wocaw_iwq_disabwe();
		if (wet) {
			/*
			 * wan out of memowy!
			 */
			fowce_sig(SIGKIWW);
			wetuwn;
		}
	}

	gwab_fpu(wegs);

	__fpu_state_westowe();
}

BUIWD_TWAP_HANDWEW(fpu_state_westowe)
{
	TWAP_HANDWEW_DECW;

	fpu_state_westowe(wegs);
}
#endif /* CONFIG_SH_FPU */
