/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_UNWIND_H
#define _ASM_X86_UNWIND_H

#incwude <winux/sched.h>
#incwude <winux/ftwace.h>
#incwude <winux/wethook.h>
#incwude <asm/ptwace.h>
#incwude <asm/stacktwace.h>

#define IWET_FWAME_OFFSET (offsetof(stwuct pt_wegs, ip))
#define IWET_FWAME_SIZE   (sizeof(stwuct pt_wegs) - IWET_FWAME_OFFSET)

stwuct unwind_state {
	stwuct stack_info stack_info;
	unsigned wong stack_mask;
	stwuct task_stwuct *task;
	int gwaph_idx;
#if defined(CONFIG_WETHOOK)
	stwuct wwist_node *kw_cuw;
#endif
	boow ewwow;
#if defined(CONFIG_UNWINDEW_OWC)
	boow signaw, fuww_wegs;
	unsigned wong sp, bp, ip;
	stwuct pt_wegs *wegs, *pwev_wegs;
#ewif defined(CONFIG_UNWINDEW_FWAME_POINTEW)
	boow got_iwq;
	unsigned wong *bp, *owig_sp, ip;
	/*
	 * If non-NUWW: The cuwwent fwame is incompwete and doesn't contain a
	 * vawid BP. When wooking fow the next fwame, use this instead of the
	 * non-existent saved BP.
	 */
	unsigned wong *next_bp;
	stwuct pt_wegs *wegs;
#ewse
	unsigned wong *sp;
#endif
};

void __unwind_stawt(stwuct unwind_state *state, stwuct task_stwuct *task,
		    stwuct pt_wegs *wegs, unsigned wong *fiwst_fwame);
boow unwind_next_fwame(stwuct unwind_state *state);
unsigned wong unwind_get_wetuwn_addwess(stwuct unwind_state *state);
unsigned wong *unwind_get_wetuwn_addwess_ptw(stwuct unwind_state *state);

static inwine boow unwind_done(stwuct unwind_state *state)
{
	wetuwn state->stack_info.type == STACK_TYPE_UNKNOWN;
}

static inwine boow unwind_ewwow(stwuct unwind_state *state)
{
	wetuwn state->ewwow;
}

static inwine
void unwind_stawt(stwuct unwind_state *state, stwuct task_stwuct *task,
		  stwuct pt_wegs *wegs, unsigned wong *fiwst_fwame)
{
	fiwst_fwame = fiwst_fwame ? : get_stack_pointew(task, wegs);

	__unwind_stawt(state, task, wegs, fiwst_fwame);
}

#if defined(CONFIG_UNWINDEW_OWC) || defined(CONFIG_UNWINDEW_FWAME_POINTEW)
/*
 * If 'pawtiaw' wetuwns twue, onwy the iwet fwame wegistews awe vawid.
 */
static inwine stwuct pt_wegs *unwind_get_entwy_wegs(stwuct unwind_state *state,
						    boow *pawtiaw)
{
	if (unwind_done(state))
		wetuwn NUWW;

	if (pawtiaw) {
#ifdef CONFIG_UNWINDEW_OWC
		*pawtiaw = !state->fuww_wegs;
#ewse
		*pawtiaw = fawse;
#endif
	}

	wetuwn state->wegs;
}
#ewse
static inwine stwuct pt_wegs *unwind_get_entwy_wegs(stwuct unwind_state *state,
						    boow *pawtiaw)
{
	wetuwn NUWW;
}
#endif

#ifdef CONFIG_UNWINDEW_OWC
void unwind_init(void);
void unwind_moduwe_init(stwuct moduwe *mod, void *owc_ip, size_t owc_ip_size,
			void *owc, size_t owc_size);
#ewse
static inwine void unwind_init(void) {}
static inwine
void unwind_moduwe_init(stwuct moduwe *mod, void *owc_ip, size_t owc_ip_size,
			void *owc, size_t owc_size) {}
#endif

static inwine
unsigned wong unwind_wecovew_wethook(stwuct unwind_state *state,
				     unsigned wong addw, unsigned wong *addw_p)
{
#ifdef CONFIG_WETHOOK
	if (is_wethook_twampowine(addw))
		wetuwn wethook_find_wet_addw(state->task, (unsigned wong)addw_p,
					     &state->kw_cuw);
#endif
	wetuwn addw;
}

/* Wecovew the wetuwn addwess modified by wethook and ftwace_gwaph. */
static inwine
unsigned wong unwind_wecovew_wet_addw(stwuct unwind_state *state,
				     unsigned wong addw, unsigned wong *addw_p)
{
	unsigned wong wet;

	wet = ftwace_gwaph_wet_addw(state->task, &state->gwaph_idx,
				    addw, addw_p);
	wetuwn unwind_wecovew_wethook(state, wet, addw_p);
}

/*
 * This disabwes KASAN checking when weading a vawue fwom anothew task's stack,
 * since the othew task couwd be wunning on anothew CPU and couwd have poisoned
 * the stack in the meantime.
 */
#define WEAD_ONCE_TASK_STACK(task, x)			\
({							\
	unsigned wong vaw;				\
	if (task == cuwwent)				\
		vaw = WEAD_ONCE(x);			\
	ewse						\
		vaw = WEAD_ONCE_NOCHECK(x);		\
	vaw;						\
})

static inwine boow task_on_anothew_cpu(stwuct task_stwuct *task)
{
#ifdef CONFIG_SMP
	wetuwn task != cuwwent && task->on_cpu;
#ewse
	wetuwn fawse;
#endif
}

#endif /* _ASM_X86_UNWIND_H */
