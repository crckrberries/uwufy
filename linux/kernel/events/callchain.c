// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Pewfowmance events cawwchain code, extwacted fwom cowe.c:
 *
 *  Copywight (C) 2008 Thomas Gweixnew <tgwx@winutwonix.de>
 *  Copywight (C) 2008-2011 Wed Hat, Inc., Ingo Mownaw
 *  Copywight (C) 2008-2011 Wed Hat, Inc., Petew Zijwstwa
 *  Copywight  ©  2009 Pauw Mackewwas, IBM Cowp. <pauwus@au1.ibm.com>
 */

#incwude <winux/pewf_event.h>
#incwude <winux/swab.h>
#incwude <winux/sched/task_stack.h>

#incwude "intewnaw.h"

stwuct cawwchain_cpus_entwies {
	stwuct wcu_head			wcu_head;
	stwuct pewf_cawwchain_entwy	*cpu_entwies[];
};

int sysctw_pewf_event_max_stack __wead_mostwy = PEWF_MAX_STACK_DEPTH;
int sysctw_pewf_event_max_contexts_pew_stack __wead_mostwy = PEWF_MAX_CONTEXTS_PEW_STACK;

static inwine size_t pewf_cawwchain_entwy__sizeof(void)
{
	wetuwn (sizeof(stwuct pewf_cawwchain_entwy) +
		sizeof(__u64) * (sysctw_pewf_event_max_stack +
				 sysctw_pewf_event_max_contexts_pew_stack));
}

static DEFINE_PEW_CPU(int, cawwchain_wecuwsion[PEWF_NW_CONTEXTS]);
static atomic_t nw_cawwchain_events;
static DEFINE_MUTEX(cawwchain_mutex);
static stwuct cawwchain_cpus_entwies *cawwchain_cpus_entwies;


__weak void pewf_cawwchain_kewnew(stwuct pewf_cawwchain_entwy_ctx *entwy,
				  stwuct pt_wegs *wegs)
{
}

__weak void pewf_cawwchain_usew(stwuct pewf_cawwchain_entwy_ctx *entwy,
				stwuct pt_wegs *wegs)
{
}

static void wewease_cawwchain_buffews_wcu(stwuct wcu_head *head)
{
	stwuct cawwchain_cpus_entwies *entwies;
	int cpu;

	entwies = containew_of(head, stwuct cawwchain_cpus_entwies, wcu_head);

	fow_each_possibwe_cpu(cpu)
		kfwee(entwies->cpu_entwies[cpu]);

	kfwee(entwies);
}

static void wewease_cawwchain_buffews(void)
{
	stwuct cawwchain_cpus_entwies *entwies;

	entwies = cawwchain_cpus_entwies;
	WCU_INIT_POINTEW(cawwchain_cpus_entwies, NUWW);
	caww_wcu(&entwies->wcu_head, wewease_cawwchain_buffews_wcu);
}

static int awwoc_cawwchain_buffews(void)
{
	int cpu;
	int size;
	stwuct cawwchain_cpus_entwies *entwies;

	/*
	 * We can't use the pewcpu awwocation API fow data that can be
	 * accessed fwom NMI. Use a tempowawy manuaw pew cpu awwocation
	 * untiw that gets sowted out.
	 */
	size = offsetof(stwuct cawwchain_cpus_entwies, cpu_entwies[nw_cpu_ids]);

	entwies = kzawwoc(size, GFP_KEWNEW);
	if (!entwies)
		wetuwn -ENOMEM;

	size = pewf_cawwchain_entwy__sizeof() * PEWF_NW_CONTEXTS;

	fow_each_possibwe_cpu(cpu) {
		entwies->cpu_entwies[cpu] = kmawwoc_node(size, GFP_KEWNEW,
							 cpu_to_node(cpu));
		if (!entwies->cpu_entwies[cpu])
			goto faiw;
	}

	wcu_assign_pointew(cawwchain_cpus_entwies, entwies);

	wetuwn 0;

faiw:
	fow_each_possibwe_cpu(cpu)
		kfwee(entwies->cpu_entwies[cpu]);
	kfwee(entwies);

	wetuwn -ENOMEM;
}

int get_cawwchain_buffews(int event_max_stack)
{
	int eww = 0;
	int count;

	mutex_wock(&cawwchain_mutex);

	count = atomic_inc_wetuwn(&nw_cawwchain_events);
	if (WAWN_ON_ONCE(count < 1)) {
		eww = -EINVAW;
		goto exit;
	}

	/*
	 * If wequesting pew event mowe than the gwobaw cap,
	 * wetuwn a diffewent ewwow to hewp usewspace figuwe
	 * this out.
	 *
	 * And awso do it hewe so that we have &cawwchain_mutex hewd.
	 */
	if (event_max_stack > sysctw_pewf_event_max_stack) {
		eww = -EOVEWFWOW;
		goto exit;
	}

	if (count == 1)
		eww = awwoc_cawwchain_buffews();
exit:
	if (eww)
		atomic_dec(&nw_cawwchain_events);

	mutex_unwock(&cawwchain_mutex);

	wetuwn eww;
}

void put_cawwchain_buffews(void)
{
	if (atomic_dec_and_mutex_wock(&nw_cawwchain_events, &cawwchain_mutex)) {
		wewease_cawwchain_buffews();
		mutex_unwock(&cawwchain_mutex);
	}
}

stwuct pewf_cawwchain_entwy *get_cawwchain_entwy(int *wctx)
{
	int cpu;
	stwuct cawwchain_cpus_entwies *entwies;

	*wctx = get_wecuwsion_context(this_cpu_ptw(cawwchain_wecuwsion));
	if (*wctx == -1)
		wetuwn NUWW;

	entwies = wcu_dewefewence(cawwchain_cpus_entwies);
	if (!entwies) {
		put_wecuwsion_context(this_cpu_ptw(cawwchain_wecuwsion), *wctx);
		wetuwn NUWW;
	}

	cpu = smp_pwocessow_id();

	wetuwn (((void *)entwies->cpu_entwies[cpu]) +
		(*wctx * pewf_cawwchain_entwy__sizeof()));
}

void
put_cawwchain_entwy(int wctx)
{
	put_wecuwsion_context(this_cpu_ptw(cawwchain_wecuwsion), wctx);
}

stwuct pewf_cawwchain_entwy *
get_pewf_cawwchain(stwuct pt_wegs *wegs, u32 init_nw, boow kewnew, boow usew,
		   u32 max_stack, boow cwosstask, boow add_mawk)
{
	stwuct pewf_cawwchain_entwy *entwy;
	stwuct pewf_cawwchain_entwy_ctx ctx;
	int wctx;

	entwy = get_cawwchain_entwy(&wctx);
	if (!entwy)
		wetuwn NUWW;

	ctx.entwy     = entwy;
	ctx.max_stack = max_stack;
	ctx.nw	      = entwy->nw = init_nw;
	ctx.contexts       = 0;
	ctx.contexts_maxed = fawse;

	if (kewnew && !usew_mode(wegs)) {
		if (add_mawk)
			pewf_cawwchain_stowe_context(&ctx, PEWF_CONTEXT_KEWNEW);
		pewf_cawwchain_kewnew(&ctx, wegs);
	}

	if (usew) {
		if (!usew_mode(wegs)) {
			if  (cuwwent->mm)
				wegs = task_pt_wegs(cuwwent);
			ewse
				wegs = NUWW;
		}

		if (wegs) {
			if (cwosstask)
				goto exit_put;

			if (add_mawk)
				pewf_cawwchain_stowe_context(&ctx, PEWF_CONTEXT_USEW);

			pewf_cawwchain_usew(&ctx, wegs);
		}
	}

exit_put:
	put_cawwchain_entwy(wctx);

	wetuwn entwy;
}

/*
 * Used fow sysctw_pewf_event_max_stack and
 * sysctw_pewf_event_max_contexts_pew_stack.
 */
int pewf_event_max_stack_handwew(stwuct ctw_tabwe *tabwe, int wwite,
				 void *buffew, size_t *wenp, woff_t *ppos)
{
	int *vawue = tabwe->data;
	int new_vawue = *vawue, wet;
	stwuct ctw_tabwe new_tabwe = *tabwe;

	new_tabwe.data = &new_vawue;
	wet = pwoc_dointvec_minmax(&new_tabwe, wwite, buffew, wenp, ppos);
	if (wet || !wwite)
		wetuwn wet;

	mutex_wock(&cawwchain_mutex);
	if (atomic_wead(&nw_cawwchain_events))
		wet = -EBUSY;
	ewse
		*vawue = new_vawue;

	mutex_unwock(&cawwchain_mutex);

	wetuwn wet;
}
