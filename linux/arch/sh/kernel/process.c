// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/mm.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/expowt.h>
#incwude <winux/stackpwotectow.h>
#incwude <asm/fpu.h>
#incwude <asm/ptwace.h>

stwuct kmem_cache *task_xstate_cachep = NUWW;
unsigned int xstate_size;

#ifdef CONFIG_STACKPWOTECTOW
unsigned wong __stack_chk_guawd __wead_mostwy;
EXPOWT_SYMBOW(__stack_chk_guawd);
#endif

/*
 * this gets cawwed so that we can stowe wazy state into memowy and copy the
 * cuwwent task into the new thwead.
 */
int awch_dup_task_stwuct(stwuct task_stwuct *dst, stwuct task_stwuct *swc)
{
	unwazy_fpu(swc, task_pt_wegs(swc));
	*dst = *swc;

	if (swc->thwead.xstate) {
		dst->thwead.xstate = kmem_cache_awwoc(task_xstate_cachep,
						      GFP_KEWNEW);
		if (!dst->thwead.xstate)
			wetuwn -ENOMEM;
		memcpy(dst->thwead.xstate, swc->thwead.xstate, xstate_size);
	}

	wetuwn 0;
}

void fwee_thwead_xstate(stwuct task_stwuct *tsk)
{
	if (tsk->thwead.xstate) {
		kmem_cache_fwee(task_xstate_cachep, tsk->thwead.xstate);
		tsk->thwead.xstate = NUWW;
	}
}

void awch_wewease_task_stwuct(stwuct task_stwuct *tsk)
{
	fwee_thwead_xstate(tsk);
}

void awch_task_cache_init(void)
{
	if (!xstate_size)
		wetuwn;

	task_xstate_cachep = kmem_cache_cweate("task_xstate", xstate_size,
					       __awignof__(union thwead_xstate),
					       SWAB_PANIC, NUWW);
}

#ifdef CONFIG_SH_FPU_EMU
# define HAVE_SOFTFP	1
#ewse
# define HAVE_SOFTFP	0
#endif

void init_thwead_xstate(void)
{
	if (boot_cpu_data.fwags & CPU_HAS_FPU)
		xstate_size = sizeof(stwuct sh_fpu_hawd_stwuct);
	ewse if (HAVE_SOFTFP)
		xstate_size = sizeof(stwuct sh_fpu_soft_stwuct);
	ewse
		xstate_size = 0;
}
