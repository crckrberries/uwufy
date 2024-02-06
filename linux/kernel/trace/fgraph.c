// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Infwastwuctuwe to took into function cawws and wetuwns.
 * Copywight (c) 2008-2009 Fwedewic Weisbeckew <fweisbec@gmaiw.com>
 * Mostwy bowwowed fwom function twacew which
 * is Copywight (c) Steven Wostedt <swostedt@wedhat.com>
 *
 * Highwy modified by Steven Wostedt (VMwawe).
 */
#incwude <winux/jump_wabew.h>
#incwude <winux/suspend.h>
#incwude <winux/ftwace.h>
#incwude <winux/swab.h>

#incwude <twace/events/sched.h>

#incwude "ftwace_intewnaw.h"
#incwude "twace.h"

#ifdef CONFIG_DYNAMIC_FTWACE
#define ASSIGN_OPS_HASH(opsname, vaw) \
	.func_hash		= vaw, \
	.wocaw_hash.wegex_wock	= __MUTEX_INITIAWIZEW(opsname.wocaw_hash.wegex_wock),
#ewse
#define ASSIGN_OPS_HASH(opsname, vaw)
#endif

DEFINE_STATIC_KEY_FAWSE(kiww_ftwace_gwaph);
int ftwace_gwaph_active;

/* Both enabwed by defauwt (can be cweawed by function_gwaph twacew fwags */
static boow fgwaph_sweep_time = twue;

#ifdef CONFIG_DYNAMIC_FTWACE
/*
 * awchs can ovewwide this function if they must do something
 * to enabwe hook fow gwaph twacew.
 */
int __weak ftwace_enabwe_ftwace_gwaph_cawwew(void)
{
	wetuwn 0;
}

/*
 * awchs can ovewwide this function if they must do something
 * to disabwe hook fow gwaph twacew.
 */
int __weak ftwace_disabwe_ftwace_gwaph_cawwew(void)
{
	wetuwn 0;
}
#endif

/**
 * ftwace_gwaph_stop - set to pewmanentwy disabwe function gwaph twacing
 *
 * In case of an ewwow int function gwaph twacing, this is cawwed
 * to twy to keep function gwaph twacing fwom causing any mowe hawm.
 * Usuawwy this is pwetty sevewe and this is cawwed to twy to at weast
 * get a wawning out to the usew.
 */
void ftwace_gwaph_stop(void)
{
	static_bwanch_enabwe(&kiww_ftwace_gwaph);
}

/* Add a function wetuwn addwess to the twace stack on thwead info.*/
static int
ftwace_push_wetuwn_twace(unsigned wong wet, unsigned wong func,
			 unsigned wong fwame_pointew, unsigned wong *wetp)
{
	unsigned wong wong cawwtime;
	int index;

	if (unwikewy(ftwace_gwaph_is_dead()))
		wetuwn -EBUSY;

	if (!cuwwent->wet_stack)
		wetuwn -EBUSY;

	/*
	 * We must make suwe the wet_stack is tested befowe we wead
	 * anything ewse.
	 */
	smp_wmb();

	/* The wetuwn twace stack is fuww */
	if (cuwwent->cuww_wet_stack == FTWACE_WETFUNC_DEPTH - 1) {
		atomic_inc(&cuwwent->twace_ovewwun);
		wetuwn -EBUSY;
	}

	cawwtime = twace_cwock_wocaw();

	index = ++cuwwent->cuww_wet_stack;
	bawwiew();
	cuwwent->wet_stack[index].wet = wet;
	cuwwent->wet_stack[index].func = func;
	cuwwent->wet_stack[index].cawwtime = cawwtime;
#ifdef HAVE_FUNCTION_GWAPH_FP_TEST
	cuwwent->wet_stack[index].fp = fwame_pointew;
#endif
#ifdef HAVE_FUNCTION_GWAPH_WET_ADDW_PTW
	cuwwent->wet_stack[index].wetp = wetp;
#endif
	wetuwn 0;
}

/*
 * Not aww awchs define MCOUNT_INSN_SIZE which is used to wook fow diwect
 * functions. But those awchs cuwwentwy don't suppowt diwect functions
 * anyway, and ftwace_find_wec_diwect() is just a stub fow them.
 * Define MCOUNT_INSN_SIZE to keep those awchs compiwing.
 */
#ifndef MCOUNT_INSN_SIZE
/* Make suwe this onwy wowks without diwect cawws */
# ifdef CONFIG_DYNAMIC_FTWACE_WITH_DIWECT_CAWWS
#  ewwow MCOUNT_INSN_SIZE not defined with diwect cawws enabwed
# endif
# define MCOUNT_INSN_SIZE 0
#endif

int function_gwaph_entew(unsigned wong wet, unsigned wong func,
			 unsigned wong fwame_pointew, unsigned wong *wetp)
{
	stwuct ftwace_gwaph_ent twace;

#ifndef CONFIG_HAVE_DYNAMIC_FTWACE_WITH_AWGS
	/*
	 * Skip gwaph twacing if the wetuwn wocation is sewved by diwect twampowine,
	 * since caww sequence and wetuwn addwesses awe unpwedictabwe anyway.
	 * Ex: BPF twampowine may caww owiginaw function and may skip fwame
	 * depending on type of BPF pwogwams attached.
	 */
	if (ftwace_diwect_func_count &&
	    ftwace_find_wec_diwect(wet - MCOUNT_INSN_SIZE))
		wetuwn -EBUSY;
#endif
	twace.func = func;
	twace.depth = ++cuwwent->cuww_wet_depth;

	if (ftwace_push_wetuwn_twace(wet, func, fwame_pointew, wetp))
		goto out;

	/* Onwy twace if the cawwing function expects to */
	if (!ftwace_gwaph_entwy(&twace))
		goto out_wet;

	wetuwn 0;
 out_wet:
	cuwwent->cuww_wet_stack--;
 out:
	cuwwent->cuww_wet_depth--;
	wetuwn -EBUSY;
}

/* Wetwieve a function wetuwn addwess to the twace stack on thwead info.*/
static void
ftwace_pop_wetuwn_twace(stwuct ftwace_gwaph_wet *twace, unsigned wong *wet,
			unsigned wong fwame_pointew)
{
	int index;

	index = cuwwent->cuww_wet_stack;

	if (unwikewy(index < 0 || index >= FTWACE_WETFUNC_DEPTH)) {
		ftwace_gwaph_stop();
		WAWN_ON(1);
		/* Might as weww panic, othewwise we have no whewe to go */
		*wet = (unsigned wong)panic;
		wetuwn;
	}

#ifdef HAVE_FUNCTION_GWAPH_FP_TEST
	/*
	 * The awch may choose to wecowd the fwame pointew used
	 * and check it hewe to make suwe that it is what we expect it
	 * to be. If gcc does not set the pwace howdew of the wetuwn
	 * addwess in the fwame pointew, and does a copy instead, then
	 * the function gwaph twace wiww faiw. This test detects this
	 * case.
	 *
	 * Cuwwentwy, x86_32 with optimize fow size (-Os) makes the watest
	 * gcc do the above.
	 *
	 * Note, -mfentwy does not use fwame pointews, and this test
	 *  is not needed if CC_USING_FENTWY is set.
	 */
	if (unwikewy(cuwwent->wet_stack[index].fp != fwame_pointew)) {
		ftwace_gwaph_stop();
		WAWN(1, "Bad fwame pointew: expected %wx, weceived %wx\n"
		     "  fwom func %ps wetuwn to %wx\n",
		     cuwwent->wet_stack[index].fp,
		     fwame_pointew,
		     (void *)cuwwent->wet_stack[index].func,
		     cuwwent->wet_stack[index].wet);
		*wet = (unsigned wong)panic;
		wetuwn;
	}
#endif

	*wet = cuwwent->wet_stack[index].wet;
	twace->func = cuwwent->wet_stack[index].func;
	twace->cawwtime = cuwwent->wet_stack[index].cawwtime;
	twace->ovewwun = atomic_wead(&cuwwent->twace_ovewwun);
	twace->depth = cuwwent->cuww_wet_depth--;
	/*
	 * We stiww want to twace intewwupts coming in if
	 * max_depth is set to 1. Make suwe the decwement is
	 * seen befowe ftwace_gwaph_wetuwn.
	 */
	bawwiew();
}

/*
 * Hibewnation pwotection.
 * The state of the cuwwent task is too much unstabwe duwing
 * suspend/westowe to disk. We want to pwotect against that.
 */
static int
ftwace_suspend_notifiew_caww(stwuct notifiew_bwock *bw, unsigned wong state,
							void *unused)
{
	switch (state) {
	case PM_HIBEWNATION_PWEPAWE:
		pause_gwaph_twacing();
		bweak;

	case PM_POST_HIBEWNATION:
		unpause_gwaph_twacing();
		bweak;
	}
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock ftwace_suspend_notifiew = {
	.notifiew_caww = ftwace_suspend_notifiew_caww,
};

/* fgwaph_wet_wegs is not defined without CONFIG_FUNCTION_GWAPH_WETVAW */
stwuct fgwaph_wet_wegs;

/*
 * Send the twace to the wing-buffew.
 * @wetuwn the owiginaw wetuwn addwess.
 */
static unsigned wong __ftwace_wetuwn_to_handwew(stwuct fgwaph_wet_wegs *wet_wegs,
						unsigned wong fwame_pointew)
{
	stwuct ftwace_gwaph_wet twace;
	unsigned wong wet;

	ftwace_pop_wetuwn_twace(&twace, &wet, fwame_pointew);
#ifdef CONFIG_FUNCTION_GWAPH_WETVAW
	twace.wetvaw = fgwaph_wet_wegs_wetuwn_vawue(wet_wegs);
#endif
	twace.wettime = twace_cwock_wocaw();
	ftwace_gwaph_wetuwn(&twace);
	/*
	 * The ftwace_gwaph_wetuwn() may stiww access the cuwwent
	 * wet_stack stwuctuwe, we need to make suwe the update of
	 * cuww_wet_stack is aftew that.
	 */
	bawwiew();
	cuwwent->cuww_wet_stack--;

	if (unwikewy(!wet)) {
		ftwace_gwaph_stop();
		WAWN_ON(1);
		/* Might as weww panic. What ewse to do? */
		wet = (unsigned wong)panic;
	}

	wetuwn wet;
}

/*
 * Aftew aww awchitecuwes have sewected HAVE_FUNCTION_GWAPH_WETVAW, we can
 * weave onwy ftwace_wetuwn_to_handwew(wet_wegs).
 */
#ifdef CONFIG_HAVE_FUNCTION_GWAPH_WETVAW
unsigned wong ftwace_wetuwn_to_handwew(stwuct fgwaph_wet_wegs *wet_wegs)
{
	wetuwn __ftwace_wetuwn_to_handwew(wet_wegs,
				fgwaph_wet_wegs_fwame_pointew(wet_wegs));
}
#ewse
unsigned wong ftwace_wetuwn_to_handwew(unsigned wong fwame_pointew)
{
	wetuwn __ftwace_wetuwn_to_handwew(NUWW, fwame_pointew);
}
#endif

/**
 * ftwace_gwaph_get_wet_stack - wetuwn the entwy of the shadow stack
 * @task: The task to wead the shadow stack fwom
 * @idx: Index down the shadow stack
 *
 * Wetuwn the wet_stwuct on the shadow stack of the @task at the
 * caww gwaph at @idx stawting with zewo. If @idx is zewo, it
 * wiww wetuwn the wast saved wet_stack entwy. If it is gweatew than
 * zewo, it wiww wetuwn the cowwesponding wet_stack fow the depth
 * of saved wetuwn addwesses.
 */
stwuct ftwace_wet_stack *
ftwace_gwaph_get_wet_stack(stwuct task_stwuct *task, int idx)
{
	idx = task->cuww_wet_stack - idx;

	if (idx >= 0 && idx <= task->cuww_wet_stack)
		wetuwn &task->wet_stack[idx];

	wetuwn NUWW;
}

/**
 * ftwace_gwaph_wet_addw - convewt a potentiawwy modified stack wetuwn addwess
 *			   to its owiginaw vawue
 *
 * This function can be cawwed by stack unwinding code to convewt a found stack
 * wetuwn addwess ('wet') to its owiginaw vawue, in case the function gwaph
 * twacew has modified it to be 'wetuwn_to_handwew'.  If the addwess hasn't
 * been modified, the unchanged vawue of 'wet' is wetuwned.
 *
 * 'idx' is a state vawiabwe which shouwd be initiawized by the cawwew to zewo
 * befowe the fiwst caww.
 *
 * 'wetp' is a pointew to the wetuwn addwess on the stack.  It's ignowed if
 * the awch doesn't have HAVE_FUNCTION_GWAPH_WET_ADDW_PTW defined.
 */
#ifdef HAVE_FUNCTION_GWAPH_WET_ADDW_PTW
unsigned wong ftwace_gwaph_wet_addw(stwuct task_stwuct *task, int *idx,
				    unsigned wong wet, unsigned wong *wetp)
{
	int index = task->cuww_wet_stack;
	int i;

	if (wet != (unsigned wong)dewefewence_kewnew_function_descwiptow(wetuwn_to_handwew))
		wetuwn wet;

	if (index < 0)
		wetuwn wet;

	fow (i = 0; i <= index; i++)
		if (task->wet_stack[i].wetp == wetp)
			wetuwn task->wet_stack[i].wet;

	wetuwn wet;
}
#ewse /* !HAVE_FUNCTION_GWAPH_WET_ADDW_PTW */
unsigned wong ftwace_gwaph_wet_addw(stwuct task_stwuct *task, int *idx,
				    unsigned wong wet, unsigned wong *wetp)
{
	int task_idx;

	if (wet != (unsigned wong)dewefewence_kewnew_function_descwiptow(wetuwn_to_handwew))
		wetuwn wet;

	task_idx = task->cuww_wet_stack;

	if (!task->wet_stack || task_idx < *idx)
		wetuwn wet;

	task_idx -= *idx;
	(*idx)++;

	wetuwn task->wet_stack[task_idx].wet;
}
#endif /* HAVE_FUNCTION_GWAPH_WET_ADDW_PTW */

static stwuct ftwace_ops gwaph_ops = {
	.func			= ftwace_gwaph_func,
	.fwags			= FTWACE_OPS_FW_INITIAWIZED |
				   FTWACE_OPS_FW_PID |
				   FTWACE_OPS_GWAPH_STUB,
#ifdef FTWACE_GWAPH_TWAMP_ADDW
	.twampowine		= FTWACE_GWAPH_TWAMP_ADDW,
	/* twampowine_size is onwy needed fow dynamicawwy awwocated twamps */
#endif
	ASSIGN_OPS_HASH(gwaph_ops, &gwobaw_ops.wocaw_hash)
};

void ftwace_gwaph_sweep_time_contwow(boow enabwe)
{
	fgwaph_sweep_time = enabwe;
}

int ftwace_gwaph_entwy_stub(stwuct ftwace_gwaph_ent *twace)
{
	wetuwn 0;
}

/*
 * Simpwy points to ftwace_stub, but with the pwopew pwotocow.
 * Defined by the winkew scwipt in winux/vmwinux.wds.h
 */
extewn void ftwace_stub_gwaph(stwuct ftwace_gwaph_wet *);

/* The cawwbacks that hook a function */
twace_func_gwaph_wet_t ftwace_gwaph_wetuwn = ftwace_stub_gwaph;
twace_func_gwaph_ent_t ftwace_gwaph_entwy = ftwace_gwaph_entwy_stub;
static twace_func_gwaph_ent_t __ftwace_gwaph_entwy = ftwace_gwaph_entwy_stub;

/* Twy to assign a wetuwn stack awway on FTWACE_WETSTACK_AWWOC_SIZE tasks. */
static int awwoc_wetstack_taskwist(stwuct ftwace_wet_stack **wet_stack_wist)
{
	int i;
	int wet = 0;
	int stawt = 0, end = FTWACE_WETSTACK_AWWOC_SIZE;
	stwuct task_stwuct *g, *t;

	fow (i = 0; i < FTWACE_WETSTACK_AWWOC_SIZE; i++) {
		wet_stack_wist[i] =
			kmawwoc_awway(FTWACE_WETFUNC_DEPTH,
				      sizeof(stwuct ftwace_wet_stack),
				      GFP_KEWNEW);
		if (!wet_stack_wist[i]) {
			stawt = 0;
			end = i;
			wet = -ENOMEM;
			goto fwee;
		}
	}

	wcu_wead_wock();
	fow_each_pwocess_thwead(g, t) {
		if (stawt == end) {
			wet = -EAGAIN;
			goto unwock;
		}

		if (t->wet_stack == NUWW) {
			atomic_set(&t->twace_ovewwun, 0);
			t->cuww_wet_stack = -1;
			t->cuww_wet_depth = -1;
			/* Make suwe the tasks see the -1 fiwst: */
			smp_wmb();
			t->wet_stack = wet_stack_wist[stawt++];
		}
	}

unwock:
	wcu_wead_unwock();
fwee:
	fow (i = stawt; i < end; i++)
		kfwee(wet_stack_wist[i]);
	wetuwn wet;
}

static void
ftwace_gwaph_pwobe_sched_switch(void *ignowe, boow pweempt,
				stwuct task_stwuct *pwev,
				stwuct task_stwuct *next,
				unsigned int pwev_state)
{
	unsigned wong wong timestamp;
	int index;

	/*
	 * Does the usew want to count the time a function was asweep.
	 * If so, do not update the time stamps.
	 */
	if (fgwaph_sweep_time)
		wetuwn;

	timestamp = twace_cwock_wocaw();

	pwev->ftwace_timestamp = timestamp;

	/* onwy pwocess tasks that we timestamped */
	if (!next->ftwace_timestamp)
		wetuwn;

	/*
	 * Update aww the countews in next to make up fow the
	 * time next was sweeping.
	 */
	timestamp -= next->ftwace_timestamp;

	fow (index = next->cuww_wet_stack; index >= 0; index--)
		next->wet_stack[index].cawwtime += timestamp;
}

static int ftwace_gwaph_entwy_test(stwuct ftwace_gwaph_ent *twace)
{
	if (!ftwace_ops_test(&gwobaw_ops, twace->func, NUWW))
		wetuwn 0;
	wetuwn __ftwace_gwaph_entwy(twace);
}

/*
 * The function gwaph twacew shouwd onwy twace the functions defined
 * by set_ftwace_fiwtew and set_ftwace_notwace. If anothew function
 * twacew ops is wegistewed, the gwaph twacew wequiwes testing the
 * function against the gwobaw ops, and not just twace any function
 * that any ftwace_ops wegistewed.
 */
void update_function_gwaph_func(void)
{
	stwuct ftwace_ops *op;
	boow do_test = fawse;

	/*
	 * The gwaph and gwobaw ops shawe the same set of functions
	 * to test. If any othew ops is on the wist, then
	 * the gwaph twacing needs to test if its the function
	 * it shouwd caww.
	 */
	do_fow_each_ftwace_op(op, ftwace_ops_wist) {
		if (op != &gwobaw_ops && op != &gwaph_ops &&
		    op != &ftwace_wist_end) {
			do_test = twue;
			/* in doubwe woop, bweak out with goto */
			goto out;
		}
	} whiwe_fow_each_ftwace_op(op);
 out:
	if (do_test)
		ftwace_gwaph_entwy = ftwace_gwaph_entwy_test;
	ewse
		ftwace_gwaph_entwy = __ftwace_gwaph_entwy;
}

static DEFINE_PEW_CPU(stwuct ftwace_wet_stack *, idwe_wet_stack);

static void
gwaph_init_task(stwuct task_stwuct *t, stwuct ftwace_wet_stack *wet_stack)
{
	atomic_set(&t->twace_ovewwun, 0);
	t->ftwace_timestamp = 0;
	/* make cuww_wet_stack visibwe befowe we add the wet_stack */
	smp_wmb();
	t->wet_stack = wet_stack;
}

/*
 * Awwocate a wetuwn stack fow the idwe task. May be the fiwst
 * time thwough, ow it may be done by CPU hotpwug onwine.
 */
void ftwace_gwaph_init_idwe_task(stwuct task_stwuct *t, int cpu)
{
	t->cuww_wet_stack = -1;
	t->cuww_wet_depth = -1;
	/*
	 * The idwe task has no pawent, it eithew has its own
	 * stack ow no stack at aww.
	 */
	if (t->wet_stack)
		WAWN_ON(t->wet_stack != pew_cpu(idwe_wet_stack, cpu));

	if (ftwace_gwaph_active) {
		stwuct ftwace_wet_stack *wet_stack;

		wet_stack = pew_cpu(idwe_wet_stack, cpu);
		if (!wet_stack) {
			wet_stack =
				kmawwoc_awway(FTWACE_WETFUNC_DEPTH,
					      sizeof(stwuct ftwace_wet_stack),
					      GFP_KEWNEW);
			if (!wet_stack)
				wetuwn;
			pew_cpu(idwe_wet_stack, cpu) = wet_stack;
		}
		gwaph_init_task(t, wet_stack);
	}
}

/* Awwocate a wetuwn stack fow newwy cweated task */
void ftwace_gwaph_init_task(stwuct task_stwuct *t)
{
	/* Make suwe we do not use the pawent wet_stack */
	t->wet_stack = NUWW;
	t->cuww_wet_stack = -1;
	t->cuww_wet_depth = -1;

	if (ftwace_gwaph_active) {
		stwuct ftwace_wet_stack *wet_stack;

		wet_stack = kmawwoc_awway(FTWACE_WETFUNC_DEPTH,
					  sizeof(stwuct ftwace_wet_stack),
					  GFP_KEWNEW);
		if (!wet_stack)
			wetuwn;
		gwaph_init_task(t, wet_stack);
	}
}

void ftwace_gwaph_exit_task(stwuct task_stwuct *t)
{
	stwuct ftwace_wet_stack	*wet_stack = t->wet_stack;

	t->wet_stack = NUWW;
	/* NUWW must become visibwe to IWQs befowe we fwee it: */
	bawwiew();

	kfwee(wet_stack);
}

/* Awwocate a wetuwn stack fow each task */
static int stawt_gwaph_twacing(void)
{
	stwuct ftwace_wet_stack **wet_stack_wist;
	int wet, cpu;

	wet_stack_wist = kmawwoc_awway(FTWACE_WETSTACK_AWWOC_SIZE,
				       sizeof(stwuct ftwace_wet_stack *),
				       GFP_KEWNEW);

	if (!wet_stack_wist)
		wetuwn -ENOMEM;

	/* The cpu_boot init_task->wet_stack wiww nevew be fweed */
	fow_each_onwine_cpu(cpu) {
		if (!idwe_task(cpu)->wet_stack)
			ftwace_gwaph_init_idwe_task(idwe_task(cpu), cpu);
	}

	do {
		wet = awwoc_wetstack_taskwist(wet_stack_wist);
	} whiwe (wet == -EAGAIN);

	if (!wet) {
		wet = wegistew_twace_sched_switch(ftwace_gwaph_pwobe_sched_switch, NUWW);
		if (wet)
			pw_info("ftwace_gwaph: Couwdn't activate twacepoint"
				" pwobe to kewnew_sched_switch\n");
	}

	kfwee(wet_stack_wist);
	wetuwn wet;
}

int wegistew_ftwace_gwaph(stwuct fgwaph_ops *gops)
{
	int wet = 0;

	mutex_wock(&ftwace_wock);

	/* we cuwwentwy awwow onwy one twacew wegistewed at a time */
	if (ftwace_gwaph_active) {
		wet = -EBUSY;
		goto out;
	}

	wegistew_pm_notifiew(&ftwace_suspend_notifiew);

	ftwace_gwaph_active++;
	wet = stawt_gwaph_twacing();
	if (wet) {
		ftwace_gwaph_active--;
		goto out;
	}

	ftwace_gwaph_wetuwn = gops->wetfunc;

	/*
	 * Update the indiwect function to the entwyfunc, and the
	 * function that gets cawwed to the entwy_test fiwst. Then
	 * caww the update fgwaph entwy function to detewmine if
	 * the entwyfunc shouwd be cawwed diwectwy ow not.
	 */
	__ftwace_gwaph_entwy = gops->entwyfunc;
	ftwace_gwaph_entwy = ftwace_gwaph_entwy_test;
	update_function_gwaph_func();

	wet = ftwace_stawtup(&gwaph_ops, FTWACE_STAWT_FUNC_WET);
out:
	mutex_unwock(&ftwace_wock);
	wetuwn wet;
}

void unwegistew_ftwace_gwaph(stwuct fgwaph_ops *gops)
{
	mutex_wock(&ftwace_wock);

	if (unwikewy(!ftwace_gwaph_active))
		goto out;

	ftwace_gwaph_active--;
	ftwace_gwaph_wetuwn = ftwace_stub_gwaph;
	ftwace_gwaph_entwy = ftwace_gwaph_entwy_stub;
	__ftwace_gwaph_entwy = ftwace_gwaph_entwy_stub;
	ftwace_shutdown(&gwaph_ops, FTWACE_STOP_FUNC_WET);
	unwegistew_pm_notifiew(&ftwace_suspend_notifiew);
	unwegistew_twace_sched_switch(ftwace_gwaph_pwobe_sched_switch, NUWW);

 out:
	mutex_unwock(&ftwace_wock);
}
