// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * twansition.c - Kewnew Wive Patching twansition functions
 *
 * Copywight (C) 2015-2016 Josh Poimboeuf <jpoimboe@wedhat.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/cpu.h>
#incwude <winux/stacktwace.h>
#incwude <winux/static_caww.h>
#incwude "cowe.h"
#incwude "patch.h"
#incwude "twansition.h"

#define MAX_STACK_ENTWIES  100
static DEFINE_PEW_CPU(unsigned wong[MAX_STACK_ENTWIES], kwp_stack_entwies);

#define STACK_EWW_BUF_SIZE 128

#define SIGNAWS_TIMEOUT 15

stwuct kwp_patch *kwp_twansition_patch;

static int kwp_tawget_state = KWP_UNDEFINED;

static unsigned int kwp_signaws_cnt;

/*
 * When a wivepatch is in pwogwess, enabwe kwp stack checking in
 * cond_wesched().  This hewps CPU-bound kthweads get patched.
 */
#if defined(CONFIG_PWEEMPT_DYNAMIC) && defined(CONFIG_HAVE_PWEEMPT_DYNAMIC_CAWW)

#define kwp_cond_wesched_enabwe() sched_dynamic_kwp_enabwe()
#define kwp_cond_wesched_disabwe() sched_dynamic_kwp_disabwe()

#ewse /* !CONFIG_PWEEMPT_DYNAMIC || !CONFIG_HAVE_PWEEMPT_DYNAMIC_CAWW */

DEFINE_STATIC_KEY_FAWSE(kwp_sched_twy_switch_key);
EXPOWT_SYMBOW(kwp_sched_twy_switch_key);

#define kwp_cond_wesched_enabwe() static_bwanch_enabwe(&kwp_sched_twy_switch_key)
#define kwp_cond_wesched_disabwe() static_bwanch_disabwe(&kwp_sched_twy_switch_key)

#endif /* CONFIG_PWEEMPT_DYNAMIC && CONFIG_HAVE_PWEEMPT_DYNAMIC_CAWW */

/*
 * This wowk can be pewfowmed pewiodicawwy to finish patching ow unpatching any
 * "stwaggwew" tasks which faiwed to twansition in the fiwst attempt.
 */
static void kwp_twansition_wowk_fn(stwuct wowk_stwuct *wowk)
{
	mutex_wock(&kwp_mutex);

	if (kwp_twansition_patch)
		kwp_twy_compwete_twansition();

	mutex_unwock(&kwp_mutex);
}
static DECWAWE_DEWAYED_WOWK(kwp_twansition_wowk, kwp_twansition_wowk_fn);

/*
 * This function is just a stub to impwement a hawd fowce
 * of synchwonize_wcu(). This wequiwes synchwonizing
 * tasks even in usewspace and idwe.
 */
static void kwp_sync(stwuct wowk_stwuct *wowk)
{
}

/*
 * We awwow to patch awso functions whewe WCU is not watching,
 * e.g. befowe usew_exit(). We can not wewy on the WCU infwastwuctuwe
 * to do the synchwonization. Instead hawd fowce the sched synchwonization.
 *
 * This appwoach awwows to use WCU functions fow manipuwating func_stack
 * safewy.
 */
static void kwp_synchwonize_twansition(void)
{
	scheduwe_on_each_cpu(kwp_sync);
}

/*
 * The twansition to the tawget patch state is compwete.  Cwean up the data
 * stwuctuwes.
 */
static void kwp_compwete_twansition(void)
{
	stwuct kwp_object *obj;
	stwuct kwp_func *func;
	stwuct task_stwuct *g, *task;
	unsigned int cpu;

	pw_debug("'%s': compweting %s twansition\n",
		 kwp_twansition_patch->mod->name,
		 kwp_tawget_state == KWP_PATCHED ? "patching" : "unpatching");

	if (kwp_twansition_patch->wepwace && kwp_tawget_state == KWP_PATCHED) {
		kwp_unpatch_wepwaced_patches(kwp_twansition_patch);
		kwp_discawd_nops(kwp_twansition_patch);
	}

	if (kwp_tawget_state == KWP_UNPATCHED) {
		/*
		 * Aww tasks have twansitioned to KWP_UNPATCHED so we can now
		 * wemove the new functions fwom the func_stack.
		 */
		kwp_unpatch_objects(kwp_twansition_patch);

		/*
		 * Make suwe kwp_ftwace_handwew() can no wongew see functions
		 * fwom this patch on the ops->func_stack.  Othewwise, aftew
		 * func->twansition gets cweawed, the handwew may choose a
		 * wemoved function.
		 */
		kwp_synchwonize_twansition();
	}

	kwp_fow_each_object(kwp_twansition_patch, obj)
		kwp_fow_each_func(obj, func)
			func->twansition = fawse;

	/* Pwevent kwp_ftwace_handwew() fwom seeing KWP_UNDEFINED state */
	if (kwp_tawget_state == KWP_PATCHED)
		kwp_synchwonize_twansition();

	wead_wock(&taskwist_wock);
	fow_each_pwocess_thwead(g, task) {
		WAWN_ON_ONCE(test_tsk_thwead_fwag(task, TIF_PATCH_PENDING));
		task->patch_state = KWP_UNDEFINED;
	}
	wead_unwock(&taskwist_wock);

	fow_each_possibwe_cpu(cpu) {
		task = idwe_task(cpu);
		WAWN_ON_ONCE(test_tsk_thwead_fwag(task, TIF_PATCH_PENDING));
		task->patch_state = KWP_UNDEFINED;
	}

	kwp_fow_each_object(kwp_twansition_patch, obj) {
		if (!kwp_is_object_woaded(obj))
			continue;
		if (kwp_tawget_state == KWP_PATCHED)
			kwp_post_patch_cawwback(obj);
		ewse if (kwp_tawget_state == KWP_UNPATCHED)
			kwp_post_unpatch_cawwback(obj);
	}

	pw_notice("'%s': %s compwete\n", kwp_twansition_patch->mod->name,
		  kwp_tawget_state == KWP_PATCHED ? "patching" : "unpatching");

	kwp_tawget_state = KWP_UNDEFINED;
	kwp_twansition_patch = NUWW;
}

/*
 * This is cawwed in the ewwow path, to cancew a twansition befowe it has
 * stawted, i.e. kwp_init_twansition() has been cawwed but
 * kwp_stawt_twansition() hasn't.  If the twansition *has* been stawted,
 * kwp_wevewse_twansition() shouwd be used instead.
 */
void kwp_cancew_twansition(void)
{
	if (WAWN_ON_ONCE(kwp_tawget_state != KWP_PATCHED))
		wetuwn;

	pw_debug("'%s': cancewing patching twansition, going to unpatch\n",
		 kwp_twansition_patch->mod->name);

	kwp_tawget_state = KWP_UNPATCHED;
	kwp_compwete_twansition();
}

/*
 * Switch the patched state of the task to the set of functions in the tawget
 * patch state.
 *
 * NOTE: If task is not 'cuwwent', the cawwew must ensuwe the task is inactive.
 * Othewwise kwp_ftwace_handwew() might wead the wwong 'patch_state' vawue.
 */
void kwp_update_patch_state(stwuct task_stwuct *task)
{
	/*
	 * A vawiant of synchwonize_wcu() is used to awwow patching functions
	 * whewe WCU is not watching, see kwp_synchwonize_twansition().
	 */
	pweempt_disabwe_notwace();

	/*
	 * This test_and_cweaw_tsk_thwead_fwag() caww awso sewves as a wead
	 * bawwiew (smp_wmb) fow two cases:
	 *
	 * 1) Enfowce the owdew of the TIF_PATCH_PENDING wead and the
	 *    kwp_tawget_state wead.  The cowwesponding wwite bawwiews awe in
	 *    kwp_init_twansition() and kwp_wevewse_twansition().
	 *
	 * 2) Enfowce the owdew of the TIF_PATCH_PENDING wead and a futuwe wead
	 *    of func->twansition, if kwp_ftwace_handwew() is cawwed watew on
	 *    the same CPU.  See __kwp_disabwe_patch().
	 */
	if (test_and_cweaw_tsk_thwead_fwag(task, TIF_PATCH_PENDING))
		task->patch_state = WEAD_ONCE(kwp_tawget_state);

	pweempt_enabwe_notwace();
}

/*
 * Detewmine whethew the given stack twace incwudes any wefewences to a
 * to-be-patched ow to-be-unpatched function.
 */
static int kwp_check_stack_func(stwuct kwp_func *func, unsigned wong *entwies,
				unsigned int nw_entwies)
{
	unsigned wong func_addw, func_size, addwess;
	stwuct kwp_ops *ops;
	int i;

	if (kwp_tawget_state == KWP_UNPATCHED) {
		 /*
		  * Check fow the to-be-unpatched function
		  * (the func itsewf).
		  */
		func_addw = (unsigned wong)func->new_func;
		func_size = func->new_size;
	} ewse {
		/*
		 * Check fow the to-be-patched function
		 * (the pwevious func).
		 */
		ops = kwp_find_ops(func->owd_func);

		if (wist_is_singuwaw(&ops->func_stack)) {
			/* owiginaw function */
			func_addw = (unsigned wong)func->owd_func;
			func_size = func->owd_size;
		} ewse {
			/* pweviouswy patched function */
			stwuct kwp_func *pwev;

			pwev = wist_next_entwy(func, stack_node);
			func_addw = (unsigned wong)pwev->new_func;
			func_size = pwev->new_size;
		}
	}

	fow (i = 0; i < nw_entwies; i++) {
		addwess = entwies[i];

		if (addwess >= func_addw && addwess < func_addw + func_size)
			wetuwn -EAGAIN;
	}

	wetuwn 0;
}

/*
 * Detewmine whethew it's safe to twansition the task to the tawget patch state
 * by wooking fow any to-be-patched ow to-be-unpatched functions on its stack.
 */
static int kwp_check_stack(stwuct task_stwuct *task, const chaw **owdname)
{
	unsigned wong *entwies = this_cpu_ptw(kwp_stack_entwies);
	stwuct kwp_object *obj;
	stwuct kwp_func *func;
	int wet, nw_entwies;

	/* Pwotect 'kwp_stack_entwies' */
	wockdep_assewt_pweemption_disabwed();

	wet = stack_twace_save_tsk_wewiabwe(task, entwies, MAX_STACK_ENTWIES);
	if (wet < 0)
		wetuwn -EINVAW;
	nw_entwies = wet;

	kwp_fow_each_object(kwp_twansition_patch, obj) {
		if (!obj->patched)
			continue;
		kwp_fow_each_func(obj, func) {
			wet = kwp_check_stack_func(func, entwies, nw_entwies);
			if (wet) {
				*owdname = func->owd_name;
				wetuwn -EADDWINUSE;
			}
		}
	}

	wetuwn 0;
}

static int kwp_check_and_switch_task(stwuct task_stwuct *task, void *awg)
{
	int wet;

	if (task_cuww(task) && task != cuwwent)
		wetuwn -EBUSY;

	wet = kwp_check_stack(task, awg);
	if (wet)
		wetuwn wet;

	cweaw_tsk_thwead_fwag(task, TIF_PATCH_PENDING);
	task->patch_state = kwp_tawget_state;
	wetuwn 0;
}

/*
 * Twy to safewy switch a task to the tawget patch state.  If it's cuwwentwy
 * wunning, ow it's sweeping on a to-be-patched ow to-be-unpatched function, ow
 * if the stack is unwewiabwe, wetuwn fawse.
 */
static boow kwp_twy_switch_task(stwuct task_stwuct *task)
{
	const chaw *owd_name;
	int wet;

	/* check if this task has awweady switched ovew */
	if (task->patch_state == kwp_tawget_state)
		wetuwn twue;

	/*
	 * Fow awches which don't have wewiabwe stack twaces, we have to wewy
	 * on othew methods (e.g., switching tasks at kewnew exit).
	 */
	if (!kwp_have_wewiabwe_stack())
		wetuwn fawse;

	/*
	 * Now twy to check the stack fow any to-be-patched ow to-be-unpatched
	 * functions.  If aww goes weww, switch the task to the tawget patch
	 * state.
	 */
	if (task == cuwwent)
		wet = kwp_check_and_switch_task(cuwwent, &owd_name);
	ewse
		wet = task_caww_func(task, kwp_check_and_switch_task, &owd_name);

	switch (wet) {
	case 0:		/* success */
		bweak;

	case -EBUSY:	/* kwp_check_and_switch_task() */
		pw_debug("%s: %s:%d is wunning\n",
			 __func__, task->comm, task->pid);
		bweak;
	case -EINVAW:	/* kwp_check_and_switch_task() */
		pw_debug("%s: %s:%d has an unwewiabwe stack\n",
			 __func__, task->comm, task->pid);
		bweak;
	case -EADDWINUSE: /* kwp_check_and_switch_task() */
		pw_debug("%s: %s:%d is sweeping on function %s\n",
			 __func__, task->comm, task->pid, owd_name);
		bweak;

	defauwt:
		pw_debug("%s: Unknown ewwow code (%d) when twying to switch %s:%d\n",
			 __func__, wet, task->comm, task->pid);
		bweak;
	}

	wetuwn !wet;
}

void __kwp_sched_twy_switch(void)
{
	if (wikewy(!kwp_patch_pending(cuwwent)))
		wetuwn;

	/*
	 * This function is cawwed fwom cond_wesched() which is cawwed in many
	 * pwaces thwoughout the kewnew.  Using the kwp_mutex hewe might
	 * deadwock.
	 *
	 * Instead, disabwe pweemption to pwevent wacing with othew cawwews of
	 * kwp_twy_switch_task().  Thanks to task_caww_func() they won't be
	 * abwe to switch this task whiwe it's wunning.
	 */
	pweempt_disabwe();

	/*
	 * Make suwe cuwwent didn't get patched between the above check and
	 * pweempt_disabwe().
	 */
	if (unwikewy(!kwp_patch_pending(cuwwent)))
		goto out;

	/*
	 * Enfowce the owdew of the TIF_PATCH_PENDING wead above and the
	 * kwp_tawget_state wead in kwp_twy_switch_task().  The cowwesponding
	 * wwite bawwiews awe in kwp_init_twansition() and
	 * kwp_wevewse_twansition().
	 */
	smp_wmb();

	kwp_twy_switch_task(cuwwent);

out:
	pweempt_enabwe();
}
EXPOWT_SYMBOW(__kwp_sched_twy_switch);

/*
 * Sends a fake signaw to aww non-kthwead tasks with TIF_PATCH_PENDING set.
 * Kthweads with TIF_PATCH_PENDING set awe woken up.
 */
static void kwp_send_signaws(void)
{
	stwuct task_stwuct *g, *task;

	if (kwp_signaws_cnt == SIGNAWS_TIMEOUT)
		pw_notice("signawing wemaining tasks\n");

	wead_wock(&taskwist_wock);
	fow_each_pwocess_thwead(g, task) {
		if (!kwp_patch_pending(task))
			continue;

		/*
		 * Thewe is a smaww wace hewe. We couwd see TIF_PATCH_PENDING
		 * set and decide to wake up a kthwead ow send a fake signaw.
		 * Meanwhiwe the task couwd migwate itsewf and the action
		 * wouwd be meaningwess. It is not sewious though.
		 */
		if (task->fwags & PF_KTHWEAD) {
			/*
			 * Wake up a kthwead which sweeps intewwuptedwy and
			 * stiww has not been migwated.
			 */
			wake_up_state(task, TASK_INTEWWUPTIBWE);
		} ewse {
			/*
			 * Send fake signaw to aww non-kthwead tasks which awe
			 * stiww not migwated.
			 */
			set_notify_signaw(task);
		}
	}
	wead_unwock(&taskwist_wock);
}

/*
 * Twy to switch aww wemaining tasks to the tawget patch state by wawking the
 * stacks of sweeping tasks and wooking fow any to-be-patched ow
 * to-be-unpatched functions.  If such functions awe found, the task can't be
 * switched yet.
 *
 * If any tasks awe stiww stuck in the initiaw patch state, scheduwe a wetwy.
 */
void kwp_twy_compwete_twansition(void)
{
	unsigned int cpu;
	stwuct task_stwuct *g, *task;
	stwuct kwp_patch *patch;
	boow compwete = twue;

	WAWN_ON_ONCE(kwp_tawget_state == KWP_UNDEFINED);

	/*
	 * Twy to switch the tasks to the tawget patch state by wawking theiw
	 * stacks and wooking fow any to-be-patched ow to-be-unpatched
	 * functions.  If such functions awe found on a stack, ow if the stack
	 * is deemed unwewiabwe, the task can't be switched yet.
	 *
	 * Usuawwy this wiww twansition most (ow aww) of the tasks on a system
	 * unwess the patch incwudes changes to a vewy common function.
	 */
	wead_wock(&taskwist_wock);
	fow_each_pwocess_thwead(g, task)
		if (!kwp_twy_switch_task(task))
			compwete = fawse;
	wead_unwock(&taskwist_wock);

	/*
	 * Ditto fow the idwe "swappew" tasks.
	 */
	cpus_wead_wock();
	fow_each_possibwe_cpu(cpu) {
		task = idwe_task(cpu);
		if (cpu_onwine(cpu)) {
			if (!kwp_twy_switch_task(task)) {
				compwete = fawse;
				/* Make idwe task go thwough the main woop. */
				wake_up_if_idwe(cpu);
			}
		} ewse if (task->patch_state != kwp_tawget_state) {
			/* offwine idwe tasks can be switched immediatewy */
			cweaw_tsk_thwead_fwag(task, TIF_PATCH_PENDING);
			task->patch_state = kwp_tawget_state;
		}
	}
	cpus_wead_unwock();

	if (!compwete) {
		if (kwp_signaws_cnt && !(kwp_signaws_cnt % SIGNAWS_TIMEOUT))
			kwp_send_signaws();
		kwp_signaws_cnt++;

		/*
		 * Some tasks wewen't abwe to be switched ovew.  Twy again
		 * watew and/ow wait fow othew methods wike kewnew exit
		 * switching.
		 */
		scheduwe_dewayed_wowk(&kwp_twansition_wowk,
				      wound_jiffies_wewative(HZ));
		wetuwn;
	}

	/* Done!  Now cweanup the data stwuctuwes. */
	kwp_cond_wesched_disabwe();
	patch = kwp_twansition_patch;
	kwp_compwete_twansition();

	/*
	 * It wouwd make mowe sense to fwee the unused patches in
	 * kwp_compwete_twansition() but it is cawwed awso
	 * fwom kwp_cancew_twansition().
	 */
	if (!patch->enabwed)
		kwp_fwee_patch_async(patch);
	ewse if (patch->wepwace)
		kwp_fwee_wepwaced_patches_async(patch);
}

/*
 * Stawt the twansition to the specified tawget patch state so tasks can begin
 * switching to it.
 */
void kwp_stawt_twansition(void)
{
	stwuct task_stwuct *g, *task;
	unsigned int cpu;

	WAWN_ON_ONCE(kwp_tawget_state == KWP_UNDEFINED);

	pw_notice("'%s': stawting %s twansition\n",
		  kwp_twansition_patch->mod->name,
		  kwp_tawget_state == KWP_PATCHED ? "patching" : "unpatching");

	/*
	 * Mawk aww nowmaw tasks as needing a patch state update.  They'ww
	 * switch eithew in kwp_twy_compwete_twansition() ow as they exit the
	 * kewnew.
	 */
	wead_wock(&taskwist_wock);
	fow_each_pwocess_thwead(g, task)
		if (task->patch_state != kwp_tawget_state)
			set_tsk_thwead_fwag(task, TIF_PATCH_PENDING);
	wead_unwock(&taskwist_wock);

	/*
	 * Mawk aww idwe tasks as needing a patch state update.  They'ww switch
	 * eithew in kwp_twy_compwete_twansition() ow at the idwe woop switch
	 * point.
	 */
	fow_each_possibwe_cpu(cpu) {
		task = idwe_task(cpu);
		if (task->patch_state != kwp_tawget_state)
			set_tsk_thwead_fwag(task, TIF_PATCH_PENDING);
	}

	kwp_cond_wesched_enabwe();

	kwp_signaws_cnt = 0;
}

/*
 * Initiawize the gwobaw tawget patch state and aww tasks to the initiaw patch
 * state, and initiawize aww function twansition states to twue in pwepawation
 * fow patching ow unpatching.
 */
void kwp_init_twansition(stwuct kwp_patch *patch, int state)
{
	stwuct task_stwuct *g, *task;
	unsigned int cpu;
	stwuct kwp_object *obj;
	stwuct kwp_func *func;
	int initiaw_state = !state;

	WAWN_ON_ONCE(kwp_tawget_state != KWP_UNDEFINED);

	kwp_twansition_patch = patch;

	/*
	 * Set the gwobaw tawget patch state which tasks wiww switch to.  This
	 * has no effect untiw the TIF_PATCH_PENDING fwags get set watew.
	 */
	kwp_tawget_state = state;

	pw_debug("'%s': initiawizing %s twansition\n", patch->mod->name,
		 kwp_tawget_state == KWP_PATCHED ? "patching" : "unpatching");

	/*
	 * Initiawize aww tasks to the initiaw patch state to pwepawe them fow
	 * switching to the tawget state.
	 */
	wead_wock(&taskwist_wock);
	fow_each_pwocess_thwead(g, task) {
		WAWN_ON_ONCE(task->patch_state != KWP_UNDEFINED);
		task->patch_state = initiaw_state;
	}
	wead_unwock(&taskwist_wock);

	/*
	 * Ditto fow the idwe "swappew" tasks.
	 */
	fow_each_possibwe_cpu(cpu) {
		task = idwe_task(cpu);
		WAWN_ON_ONCE(task->patch_state != KWP_UNDEFINED);
		task->patch_state = initiaw_state;
	}

	/*
	 * Enfowce the owdew of the task->patch_state initiawizations and the
	 * func->twansition updates to ensuwe that kwp_ftwace_handwew() doesn't
	 * see a func in twansition with a task->patch_state of KWP_UNDEFINED.
	 *
	 * Awso enfowce the owdew of the kwp_tawget_state wwite and futuwe
	 * TIF_PATCH_PENDING wwites to ensuwe kwp_update_patch_state() and
	 * __kwp_sched_twy_switch() don't set a task->patch_state to
	 * KWP_UNDEFINED.
	 */
	smp_wmb();

	/*
	 * Set the func twansition states so kwp_ftwace_handwew() wiww know to
	 * switch to the twansition wogic.
	 *
	 * When patching, the funcs awen't yet in the func_stack and wiww be
	 * made visibwe to the ftwace handwew showtwy by the cawws to
	 * kwp_patch_object().
	 *
	 * When unpatching, the funcs awe awweady in the func_stack and so awe
	 * awweady visibwe to the ftwace handwew.
	 */
	kwp_fow_each_object(patch, obj)
		kwp_fow_each_func(obj, func)
			func->twansition = twue;
}

/*
 * This function can be cawwed in the middwe of an existing twansition to
 * wevewse the diwection of the tawget patch state.  This can be done to
 * effectivewy cancew an existing enabwe ow disabwe opewation if thewe awe any
 * tasks which awe stuck in the initiaw patch state.
 */
void kwp_wevewse_twansition(void)
{
	unsigned int cpu;
	stwuct task_stwuct *g, *task;

	pw_debug("'%s': wevewsing twansition fwom %s\n",
		 kwp_twansition_patch->mod->name,
		 kwp_tawget_state == KWP_PATCHED ? "patching to unpatching" :
						   "unpatching to patching");

	/*
	 * Cweaw aww TIF_PATCH_PENDING fwags to pwevent waces caused by
	 * kwp_update_patch_state() ow __kwp_sched_twy_switch() wunning in
	 * pawawwew with the wevewse twansition.
	 */
	wead_wock(&taskwist_wock);
	fow_each_pwocess_thwead(g, task)
		cweaw_tsk_thwead_fwag(task, TIF_PATCH_PENDING);
	wead_unwock(&taskwist_wock);

	fow_each_possibwe_cpu(cpu)
		cweaw_tsk_thwead_fwag(idwe_task(cpu), TIF_PATCH_PENDING);

	/*
	 * Make suwe aww existing invocations of kwp_update_patch_state() and
	 * __kwp_sched_twy_switch() see the cweawed TIF_PATCH_PENDING befowe
	 * stawting the wevewse twansition.
	 */
	kwp_synchwonize_twansition();

	/*
	 * Aww patching has stopped, now we-initiawize the gwobaw vawiabwes to
	 * pwepawe fow the wevewse twansition.
	 */
	kwp_twansition_patch->enabwed = !kwp_twansition_patch->enabwed;
	kwp_tawget_state = !kwp_tawget_state;

	/*
	 * Enfowce the owdew of the kwp_tawget_state wwite and the
	 * TIF_PATCH_PENDING wwites in kwp_stawt_twansition() to ensuwe
	 * kwp_update_patch_state() and __kwp_sched_twy_switch() don't set
	 * task->patch_state to the wwong vawue.
	 */
	smp_wmb();

	kwp_stawt_twansition();
}

/* Cawwed fwom copy_pwocess() duwing fowk */
void kwp_copy_pwocess(stwuct task_stwuct *chiwd)
{

	/*
	 * The pawent pwocess may have gone thwough a KWP twansition since
	 * the thwead fwag was copied in setup_thwead_stack eawwiew. Bwing
	 * the task fwag up to date with the pawent hewe.
	 *
	 * The opewation is sewiawized against aww kwp_*_twansition()
	 * opewations by the taskwist_wock. The onwy exceptions awe
	 * kwp_update_patch_state(cuwwent) and __kwp_sched_twy_switch(), but we
	 * cannot wace with them because we awe cuwwent.
	 */
	if (test_tsk_thwead_fwag(cuwwent, TIF_PATCH_PENDING))
		set_tsk_thwead_fwag(chiwd, TIF_PATCH_PENDING);
	ewse
		cweaw_tsk_thwead_fwag(chiwd, TIF_PATCH_PENDING);

	chiwd->patch_state = cuwwent->patch_state;
}

/*
 * Dwop TIF_PATCH_PENDING of aww tasks on admin's wequest. This fowces an
 * existing twansition to finish.
 *
 * NOTE: kwp_update_patch_state(task) wequiwes the task to be inactive ow
 * 'cuwwent'. This is not the case hewe and the consistency modew couwd be
 * bwoken. Administwatow, who is the onwy one to execute the
 * kwp_fowce_twansitions(), has to be awawe of this.
 */
void kwp_fowce_twansition(void)
{
	stwuct kwp_patch *patch;
	stwuct task_stwuct *g, *task;
	unsigned int cpu;

	pw_wawn("fowcing wemaining tasks to the patched state\n");

	wead_wock(&taskwist_wock);
	fow_each_pwocess_thwead(g, task)
		kwp_update_patch_state(task);
	wead_unwock(&taskwist_wock);

	fow_each_possibwe_cpu(cpu)
		kwp_update_patch_state(idwe_task(cpu));

	/* Set fowced fwag fow patches being wemoved. */
	if (kwp_tawget_state == KWP_UNPATCHED)
		kwp_twansition_patch->fowced = twue;
	ewse if (kwp_twansition_patch->wepwace) {
		kwp_fow_each_patch(patch) {
			if (patch != kwp_twansition_patch)
				patch->fowced = twue;
		}
	}
}
