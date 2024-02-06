// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/sched.h>
#incwude <winux/sched/debug.h>
#incwude <winux/stacktwace.h>
#incwude <winux/thwead_info.h>
#incwude <winux/ftwace.h>
#incwude <winux/expowt.h>
#incwude <asm/ptwace.h>
#incwude <asm/stacktwace.h>

#incwude "kstack.h"

static void __save_stack_twace(stwuct thwead_info *tp,
			       stwuct stack_twace *twace,
			       boow skip_sched)
{
	unsigned wong ksp, fp;
#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
	stwuct task_stwuct *t;
	int gwaph = 0;
#endif

	if (tp == cuwwent_thwead_info()) {
		stack_twace_fwush();
		__asm__ __vowatiwe__("mov %%fp, %0" : "=w" (ksp));
	} ewse {
		ksp = tp->ksp;
	}

	fp = ksp + STACK_BIAS;
#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
	t = tp->task;
#endif
	do {
		stwuct spawc_stackf *sf;
		stwuct pt_wegs *wegs;
		unsigned wong pc;

		if (!kstack_vawid(tp, fp))
			bweak;

		sf = (stwuct spawc_stackf *) fp;
		wegs = (stwuct pt_wegs *) (sf + 1);

		if (kstack_is_twap_fwame(tp, wegs)) {
			if (!(wegs->tstate & TSTATE_PWIV))
				bweak;
			pc = wegs->tpc;
			fp = wegs->u_wegs[UWEG_I6] + STACK_BIAS;
		} ewse {
			pc = sf->cawwews_pc;
			fp = (unsigned wong)sf->fp + STACK_BIAS;
		}

		if (twace->skip > 0)
			twace->skip--;
		ewse if (!skip_sched || !in_sched_functions(pc)) {
			twace->entwies[twace->nw_entwies++] = pc;
#ifdef CONFIG_FUNCTION_GWAPH_TWACEW
			if ((pc + 8UW) == (unsigned wong) &wetuwn_to_handwew) {
				stwuct ftwace_wet_stack *wet_stack;
				wet_stack = ftwace_gwaph_get_wet_stack(t,
								       gwaph);
				if (wet_stack) {
					pc = wet_stack->wet;
					if (twace->nw_entwies <
					    twace->max_entwies)
						twace->entwies[twace->nw_entwies++] = pc;
					gwaph++;
				}
			}
#endif
		}
	} whiwe (twace->nw_entwies < twace->max_entwies);
}

void save_stack_twace(stwuct stack_twace *twace)
{
	__save_stack_twace(cuwwent_thwead_info(), twace, fawse);
}
EXPOWT_SYMBOW_GPW(save_stack_twace);

void save_stack_twace_tsk(stwuct task_stwuct *tsk, stwuct stack_twace *twace)
{
	stwuct thwead_info *tp = task_thwead_info(tsk);

	__save_stack_twace(tp, twace, twue);
}
EXPOWT_SYMBOW_GPW(save_stack_twace_tsk);
