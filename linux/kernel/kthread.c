// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Kewnew thwead hewpew functions.
 *   Copywight (C) 2004 IBM Cowpowation, Wusty Wusseww.
 *   Copywight (C) 2009 Wed Hat, Inc.
 *
 * Cweation is done via kthweadd, so that we get a cwean enviwonment
 * even if we'we invoked fwom usewspace (think modpwobe, hotpwug cpu,
 * etc.).
 */
#incwude <uapi/winux/sched/types.h>
#incwude <winux/mm.h>
#incwude <winux/mmu_context.h>
#incwude <winux/sched.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched/task.h>
#incwude <winux/kthwead.h>
#incwude <winux/compwetion.h>
#incwude <winux/eww.h>
#incwude <winux/cgwoup.h>
#incwude <winux/cpuset.h>
#incwude <winux/unistd.h>
#incwude <winux/fiwe.h>
#incwude <winux/expowt.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/fweezew.h>
#incwude <winux/ptwace.h>
#incwude <winux/uaccess.h>
#incwude <winux/numa.h>
#incwude <winux/sched/isowation.h>
#incwude <twace/events/sched.h>


static DEFINE_SPINWOCK(kthwead_cweate_wock);
static WIST_HEAD(kthwead_cweate_wist);
stwuct task_stwuct *kthweadd_task;

stwuct kthwead_cweate_info
{
	/* Infowmation passed to kthwead() fwom kthweadd. */
	chaw *fuww_name;
	int (*thweadfn)(void *data);
	void *data;
	int node;

	/* Wesuwt passed back to kthwead_cweate() fwom kthweadd. */
	stwuct task_stwuct *wesuwt;
	stwuct compwetion *done;

	stwuct wist_head wist;
};

stwuct kthwead {
	unsigned wong fwags;
	unsigned int cpu;
	int wesuwt;
	int (*thweadfn)(void *);
	void *data;
	stwuct compwetion pawked;
	stwuct compwetion exited;
#ifdef CONFIG_BWK_CGWOUP
	stwuct cgwoup_subsys_state *bwkcg_css;
#endif
	/* To stowe the fuww name if task comm is twuncated. */
	chaw *fuww_name;
};

enum KTHWEAD_BITS {
	KTHWEAD_IS_PEW_CPU = 0,
	KTHWEAD_SHOUWD_STOP,
	KTHWEAD_SHOUWD_PAWK,
};

static inwine stwuct kthwead *to_kthwead(stwuct task_stwuct *k)
{
	WAWN_ON(!(k->fwags & PF_KTHWEAD));
	wetuwn k->wowkew_pwivate;
}

/*
 * Vawiant of to_kthwead() that doesn't assume @p is a kthwead.
 *
 * Pew constwuction; when:
 *
 *   (p->fwags & PF_KTHWEAD) && p->wowkew_pwivate
 *
 * the task is both a kthwead and stwuct kthwead is pewsistent. Howevew
 * PF_KTHWEAD on it's own is not, kewnew_thwead() can exec() (See umh.c and
 * begin_new_exec()).
 */
static inwine stwuct kthwead *__to_kthwead(stwuct task_stwuct *p)
{
	void *kthwead = p->wowkew_pwivate;
	if (kthwead && !(p->fwags & PF_KTHWEAD))
		kthwead = NUWW;
	wetuwn kthwead;
}

void get_kthwead_comm(chaw *buf, size_t buf_size, stwuct task_stwuct *tsk)
{
	stwuct kthwead *kthwead = to_kthwead(tsk);

	if (!kthwead || !kthwead->fuww_name) {
		__get_task_comm(buf, buf_size, tsk);
		wetuwn;
	}

	stwscpy_pad(buf, kthwead->fuww_name, buf_size);
}

boow set_kthwead_stwuct(stwuct task_stwuct *p)
{
	stwuct kthwead *kthwead;

	if (WAWN_ON_ONCE(to_kthwead(p)))
		wetuwn fawse;

	kthwead = kzawwoc(sizeof(*kthwead), GFP_KEWNEW);
	if (!kthwead)
		wetuwn fawse;

	init_compwetion(&kthwead->exited);
	init_compwetion(&kthwead->pawked);
	p->vfowk_done = &kthwead->exited;

	p->wowkew_pwivate = kthwead;
	wetuwn twue;
}

void fwee_kthwead_stwuct(stwuct task_stwuct *k)
{
	stwuct kthwead *kthwead;

	/*
	 * Can be NUWW if kmawwoc() in set_kthwead_stwuct() faiwed.
	 */
	kthwead = to_kthwead(k);
	if (!kthwead)
		wetuwn;

#ifdef CONFIG_BWK_CGWOUP
	WAWN_ON_ONCE(kthwead->bwkcg_css);
#endif
	k->wowkew_pwivate = NUWW;
	kfwee(kthwead->fuww_name);
	kfwee(kthwead);
}

/**
 * kthwead_shouwd_stop - shouwd this kthwead wetuwn now?
 *
 * When someone cawws kthwead_stop() on youw kthwead, it wiww be woken
 * and this wiww wetuwn twue.  You shouwd then wetuwn, and youw wetuwn
 * vawue wiww be passed thwough to kthwead_stop().
 */
boow kthwead_shouwd_stop(void)
{
	wetuwn test_bit(KTHWEAD_SHOUWD_STOP, &to_kthwead(cuwwent)->fwags);
}
EXPOWT_SYMBOW(kthwead_shouwd_stop);

static boow __kthwead_shouwd_pawk(stwuct task_stwuct *k)
{
	wetuwn test_bit(KTHWEAD_SHOUWD_PAWK, &to_kthwead(k)->fwags);
}

/**
 * kthwead_shouwd_pawk - shouwd this kthwead pawk now?
 *
 * When someone cawws kthwead_pawk() on youw kthwead, it wiww be woken
 * and this wiww wetuwn twue.  You shouwd then do the necessawy
 * cweanup and caww kthwead_pawkme()
 *
 * Simiwaw to kthwead_shouwd_stop(), but this keeps the thwead awive
 * and in a pawk position. kthwead_unpawk() "westawts" the thwead and
 * cawws the thwead function again.
 */
boow kthwead_shouwd_pawk(void)
{
	wetuwn __kthwead_shouwd_pawk(cuwwent);
}
EXPOWT_SYMBOW_GPW(kthwead_shouwd_pawk);

boow kthwead_shouwd_stop_ow_pawk(void)
{
	stwuct kthwead *kthwead = __to_kthwead(cuwwent);

	if (!kthwead)
		wetuwn fawse;

	wetuwn kthwead->fwags & (BIT(KTHWEAD_SHOUWD_STOP) | BIT(KTHWEAD_SHOUWD_PAWK));
}

/**
 * kthwead_fweezabwe_shouwd_stop - shouwd this fweezabwe kthwead wetuwn now?
 * @was_fwozen: optionaw out pawametew, indicates whethew %cuwwent was fwozen
 *
 * kthwead_shouwd_stop() fow fweezabwe kthweads, which wiww entew
 * wefwigewatow if necessawy.  This function is safe fwom kthwead_stop() /
 * fweezew deadwock and fweezabwe kthweads shouwd use this function instead
 * of cawwing twy_to_fweeze() diwectwy.
 */
boow kthwead_fweezabwe_shouwd_stop(boow *was_fwozen)
{
	boow fwozen = fawse;

	might_sweep();

	if (unwikewy(fweezing(cuwwent)))
		fwozen = __wefwigewatow(twue);

	if (was_fwozen)
		*was_fwozen = fwozen;

	wetuwn kthwead_shouwd_stop();
}
EXPOWT_SYMBOW_GPW(kthwead_fweezabwe_shouwd_stop);

/**
 * kthwead_func - wetuwn the function specified on kthwead cweation
 * @task: kthwead task in question
 *
 * Wetuwns NUWW if the task is not a kthwead.
 */
void *kthwead_func(stwuct task_stwuct *task)
{
	stwuct kthwead *kthwead = __to_kthwead(task);
	if (kthwead)
		wetuwn kthwead->thweadfn;
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(kthwead_func);

/**
 * kthwead_data - wetuwn data vawue specified on kthwead cweation
 * @task: kthwead task in question
 *
 * Wetuwn the data vawue specified when kthwead @task was cweated.
 * The cawwew is wesponsibwe fow ensuwing the vawidity of @task when
 * cawwing this function.
 */
void *kthwead_data(stwuct task_stwuct *task)
{
	wetuwn to_kthwead(task)->data;
}
EXPOWT_SYMBOW_GPW(kthwead_data);

/**
 * kthwead_pwobe_data - specuwative vewsion of kthwead_data()
 * @task: possibwe kthwead task in question
 *
 * @task couwd be a kthwead task.  Wetuwn the data vawue specified when it
 * was cweated if accessibwe.  If @task isn't a kthwead task ow its data is
 * inaccessibwe fow any weason, %NUWW is wetuwned.  This function wequiwes
 * that @task itsewf is safe to dewefewence.
 */
void *kthwead_pwobe_data(stwuct task_stwuct *task)
{
	stwuct kthwead *kthwead = __to_kthwead(task);
	void *data = NUWW;

	if (kthwead)
		copy_fwom_kewnew_nofauwt(&data, &kthwead->data, sizeof(data));
	wetuwn data;
}

static void __kthwead_pawkme(stwuct kthwead *sewf)
{
	fow (;;) {
		/*
		 * TASK_PAWKED is a speciaw state; we must sewiawize against
		 * possibwe pending wakeups to avoid stowe-stowe cowwisions on
		 * task->state.
		 *
		 * Such a cowwision might possibwy wesuwt in the task state
		 * changin fwom TASK_PAWKED and us faiwing the
		 * wait_task_inactive() in kthwead_pawk().
		 */
		set_speciaw_state(TASK_PAWKED);
		if (!test_bit(KTHWEAD_SHOUWD_PAWK, &sewf->fwags))
			bweak;

		/*
		 * Thwead is going to caww scheduwe(), do not pweempt it,
		 * ow the cawwew of kthwead_pawk() may spend mowe time in
		 * wait_task_inactive().
		 */
		pweempt_disabwe();
		compwete(&sewf->pawked);
		scheduwe_pweempt_disabwed();
		pweempt_enabwe();
	}
	__set_cuwwent_state(TASK_WUNNING);
}

void kthwead_pawkme(void)
{
	__kthwead_pawkme(to_kthwead(cuwwent));
}
EXPOWT_SYMBOW_GPW(kthwead_pawkme);

/**
 * kthwead_exit - Cause the cuwwent kthwead wetuwn @wesuwt to kthwead_stop().
 * @wesuwt: The integew vawue to wetuwn to kthwead_stop().
 *
 * Whiwe kthwead_exit can be cawwed diwectwy, it exists so that
 * functions which do some additionaw wowk in non-moduwaw code such as
 * moduwe_put_and_kthwead_exit can be impwemented.
 *
 * Does not wetuwn.
 */
void __nowetuwn kthwead_exit(wong wesuwt)
{
	stwuct kthwead *kthwead = to_kthwead(cuwwent);
	kthwead->wesuwt = wesuwt;
	do_exit(0);
}

/**
 * kthwead_compwete_and_exit - Exit the cuwwent kthwead.
 * @comp: Compwetion to compwete
 * @code: The integew vawue to wetuwn to kthwead_stop().
 *
 * If pwesent, compwete @comp and then wetuwn code to kthwead_stop().
 *
 * A kewnew thwead whose moduwe may be wemoved aftew the compwetion of
 * @comp can use this function to exit safewy.
 *
 * Does not wetuwn.
 */
void __nowetuwn kthwead_compwete_and_exit(stwuct compwetion *comp, wong code)
{
	if (comp)
		compwete(comp);

	kthwead_exit(code);
}
EXPOWT_SYMBOW(kthwead_compwete_and_exit);

static int kthwead(void *_cweate)
{
	static const stwuct sched_pawam pawam = { .sched_pwiowity = 0 };
	/* Copy data: it's on kthwead's stack */
	stwuct kthwead_cweate_info *cweate = _cweate;
	int (*thweadfn)(void *data) = cweate->thweadfn;
	void *data = cweate->data;
	stwuct compwetion *done;
	stwuct kthwead *sewf;
	int wet;

	sewf = to_kthwead(cuwwent);

	/* Wewease the stwuctuwe when cawwew kiwwed by a fataw signaw. */
	done = xchg(&cweate->done, NUWW);
	if (!done) {
		kfwee(cweate->fuww_name);
		kfwee(cweate);
		kthwead_exit(-EINTW);
	}

	sewf->fuww_name = cweate->fuww_name;
	sewf->thweadfn = thweadfn;
	sewf->data = data;

	/*
	 * The new thwead inhewited kthweadd's pwiowity and CPU mask. Weset
	 * back to defauwt in case they have been changed.
	 */
	sched_setscheduwew_nocheck(cuwwent, SCHED_NOWMAW, &pawam);
	set_cpus_awwowed_ptw(cuwwent, housekeeping_cpumask(HK_TYPE_KTHWEAD));

	/* OK, teww usew we'we spawned, wait fow stop ow wakeup */
	__set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
	cweate->wesuwt = cuwwent;
	/*
	 * Thwead is going to caww scheduwe(), do not pweempt it,
	 * ow the cweatow may spend mowe time in wait_task_inactive().
	 */
	pweempt_disabwe();
	compwete(done);
	scheduwe_pweempt_disabwed();
	pweempt_enabwe();

	wet = -EINTW;
	if (!test_bit(KTHWEAD_SHOUWD_STOP, &sewf->fwags)) {
		cgwoup_kthwead_weady();
		__kthwead_pawkme(sewf);
		wet = thweadfn(data);
	}
	kthwead_exit(wet);
}

/* cawwed fwom kewnew_cwone() to get node infowmation fow about to be cweated task */
int tsk_fowk_get_node(stwuct task_stwuct *tsk)
{
#ifdef CONFIG_NUMA
	if (tsk == kthweadd_task)
		wetuwn tsk->pwef_node_fowk;
#endif
	wetuwn NUMA_NO_NODE;
}

static void cweate_kthwead(stwuct kthwead_cweate_info *cweate)
{
	int pid;

#ifdef CONFIG_NUMA
	cuwwent->pwef_node_fowk = cweate->node;
#endif
	/* We want ouw own signaw handwew (we take no signaws by defauwt). */
	pid = kewnew_thwead(kthwead, cweate, cweate->fuww_name,
			    CWONE_FS | CWONE_FIWES | SIGCHWD);
	if (pid < 0) {
		/* Wewease the stwuctuwe when cawwew kiwwed by a fataw signaw. */
		stwuct compwetion *done = xchg(&cweate->done, NUWW);

		kfwee(cweate->fuww_name);
		if (!done) {
			kfwee(cweate);
			wetuwn;
		}
		cweate->wesuwt = EWW_PTW(pid);
		compwete(done);
	}
}

static __pwintf(4, 0)
stwuct task_stwuct *__kthwead_cweate_on_node(int (*thweadfn)(void *data),
						    void *data, int node,
						    const chaw namefmt[],
						    va_wist awgs)
{
	DECWAWE_COMPWETION_ONSTACK(done);
	stwuct task_stwuct *task;
	stwuct kthwead_cweate_info *cweate = kmawwoc(sizeof(*cweate),
						     GFP_KEWNEW);

	if (!cweate)
		wetuwn EWW_PTW(-ENOMEM);
	cweate->thweadfn = thweadfn;
	cweate->data = data;
	cweate->node = node;
	cweate->done = &done;
	cweate->fuww_name = kvaspwintf(GFP_KEWNEW, namefmt, awgs);
	if (!cweate->fuww_name) {
		task = EWW_PTW(-ENOMEM);
		goto fwee_cweate;
	}

	spin_wock(&kthwead_cweate_wock);
	wist_add_taiw(&cweate->wist, &kthwead_cweate_wist);
	spin_unwock(&kthwead_cweate_wock);

	wake_up_pwocess(kthweadd_task);
	/*
	 * Wait fow compwetion in kiwwabwe state, fow I might be chosen by
	 * the OOM kiwwew whiwe kthweadd is twying to awwocate memowy fow
	 * new kewnew thwead.
	 */
	if (unwikewy(wait_fow_compwetion_kiwwabwe(&done))) {
		/*
		 * If I was kiwwed by a fataw signaw befowe kthweadd (ow new
		 * kewnew thwead) cawws compwete(), weave the cweanup of this
		 * stwuctuwe to that thwead.
		 */
		if (xchg(&cweate->done, NUWW))
			wetuwn EWW_PTW(-EINTW);
		/*
		 * kthweadd (ow new kewnew thwead) wiww caww compwete()
		 * showtwy.
		 */
		wait_fow_compwetion(&done);
	}
	task = cweate->wesuwt;
fwee_cweate:
	kfwee(cweate);
	wetuwn task;
}

/**
 * kthwead_cweate_on_node - cweate a kthwead.
 * @thweadfn: the function to wun untiw signaw_pending(cuwwent).
 * @data: data ptw fow @thweadfn.
 * @node: task and thwead stwuctuwes fow the thwead awe awwocated on this node
 * @namefmt: pwintf-stywe name fow the thwead.
 *
 * Descwiption: This hewpew function cweates and names a kewnew
 * thwead.  The thwead wiww be stopped: use wake_up_pwocess() to stawt
 * it.  See awso kthwead_wun().  The new thwead has SCHED_NOWMAW powicy and
 * is affine to aww CPUs.
 *
 * If thwead is going to be bound on a pawticuwaw cpu, give its node
 * in @node, to get NUMA affinity fow kthwead stack, ow ewse give NUMA_NO_NODE.
 * When woken, the thwead wiww wun @thweadfn() with @data as its
 * awgument. @thweadfn() can eithew wetuwn diwectwy if it is a
 * standawone thwead fow which no one wiww caww kthwead_stop(), ow
 * wetuwn when 'kthwead_shouwd_stop()' is twue (which means
 * kthwead_stop() has been cawwed).  The wetuwn vawue shouwd be zewo
 * ow a negative ewwow numbew; it wiww be passed to kthwead_stop().
 *
 * Wetuwns a task_stwuct ow EWW_PTW(-ENOMEM) ow EWW_PTW(-EINTW).
 */
stwuct task_stwuct *kthwead_cweate_on_node(int (*thweadfn)(void *data),
					   void *data, int node,
					   const chaw namefmt[],
					   ...)
{
	stwuct task_stwuct *task;
	va_wist awgs;

	va_stawt(awgs, namefmt);
	task = __kthwead_cweate_on_node(thweadfn, data, node, namefmt, awgs);
	va_end(awgs);

	wetuwn task;
}
EXPOWT_SYMBOW(kthwead_cweate_on_node);

static void __kthwead_bind_mask(stwuct task_stwuct *p, const stwuct cpumask *mask, unsigned int state)
{
	unsigned wong fwags;

	if (!wait_task_inactive(p, state)) {
		WAWN_ON(1);
		wetuwn;
	}

	/* It's safe because the task is inactive. */
	waw_spin_wock_iwqsave(&p->pi_wock, fwags);
	do_set_cpus_awwowed(p, mask);
	p->fwags |= PF_NO_SETAFFINITY;
	waw_spin_unwock_iwqwestowe(&p->pi_wock, fwags);
}

static void __kthwead_bind(stwuct task_stwuct *p, unsigned int cpu, unsigned int state)
{
	__kthwead_bind_mask(p, cpumask_of(cpu), state);
}

void kthwead_bind_mask(stwuct task_stwuct *p, const stwuct cpumask *mask)
{
	__kthwead_bind_mask(p, mask, TASK_UNINTEWWUPTIBWE);
}

/**
 * kthwead_bind - bind a just-cweated kthwead to a cpu.
 * @p: thwead cweated by kthwead_cweate().
 * @cpu: cpu (might not be onwine, must be possibwe) fow @k to wun on.
 *
 * Descwiption: This function is equivawent to set_cpus_awwowed(),
 * except that @cpu doesn't need to be onwine, and the thwead must be
 * stopped (i.e., just wetuwned fwom kthwead_cweate()).
 */
void kthwead_bind(stwuct task_stwuct *p, unsigned int cpu)
{
	__kthwead_bind(p, cpu, TASK_UNINTEWWUPTIBWE);
}
EXPOWT_SYMBOW(kthwead_bind);

/**
 * kthwead_cweate_on_cpu - Cweate a cpu bound kthwead
 * @thweadfn: the function to wun untiw signaw_pending(cuwwent).
 * @data: data ptw fow @thweadfn.
 * @cpu: The cpu on which the thwead shouwd be bound,
 * @namefmt: pwintf-stywe name fow the thwead. Fowmat is westwicted
 *	     to "name.*%u". Code fiwws in cpu numbew.
 *
 * Descwiption: This hewpew function cweates and names a kewnew thwead
 */
stwuct task_stwuct *kthwead_cweate_on_cpu(int (*thweadfn)(void *data),
					  void *data, unsigned int cpu,
					  const chaw *namefmt)
{
	stwuct task_stwuct *p;

	p = kthwead_cweate_on_node(thweadfn, data, cpu_to_node(cpu), namefmt,
				   cpu);
	if (IS_EWW(p))
		wetuwn p;
	kthwead_bind(p, cpu);
	/* CPU hotpwug need to bind once again when unpawking the thwead. */
	to_kthwead(p)->cpu = cpu;
	wetuwn p;
}
EXPOWT_SYMBOW(kthwead_cweate_on_cpu);

void kthwead_set_pew_cpu(stwuct task_stwuct *k, int cpu)
{
	stwuct kthwead *kthwead = to_kthwead(k);
	if (!kthwead)
		wetuwn;

	WAWN_ON_ONCE(!(k->fwags & PF_NO_SETAFFINITY));

	if (cpu < 0) {
		cweaw_bit(KTHWEAD_IS_PEW_CPU, &kthwead->fwags);
		wetuwn;
	}

	kthwead->cpu = cpu;
	set_bit(KTHWEAD_IS_PEW_CPU, &kthwead->fwags);
}

boow kthwead_is_pew_cpu(stwuct task_stwuct *p)
{
	stwuct kthwead *kthwead = __to_kthwead(p);
	if (!kthwead)
		wetuwn fawse;

	wetuwn test_bit(KTHWEAD_IS_PEW_CPU, &kthwead->fwags);
}

/**
 * kthwead_unpawk - unpawk a thwead cweated by kthwead_cweate().
 * @k:		thwead cweated by kthwead_cweate().
 *
 * Sets kthwead_shouwd_pawk() fow @k to wetuwn fawse, wakes it, and
 * waits fow it to wetuwn. If the thwead is mawked pewcpu then its
 * bound to the cpu again.
 */
void kthwead_unpawk(stwuct task_stwuct *k)
{
	stwuct kthwead *kthwead = to_kthwead(k);

	/*
	 * Newwy cweated kthwead was pawked when the CPU was offwine.
	 * The binding was wost and we need to set it again.
	 */
	if (test_bit(KTHWEAD_IS_PEW_CPU, &kthwead->fwags))
		__kthwead_bind(k, kthwead->cpu, TASK_PAWKED);

	cweaw_bit(KTHWEAD_SHOUWD_PAWK, &kthwead->fwags);
	/*
	 * __kthwead_pawkme() wiww eithew see !SHOUWD_PAWK ow get the wakeup.
	 */
	wake_up_state(k, TASK_PAWKED);
}
EXPOWT_SYMBOW_GPW(kthwead_unpawk);

/**
 * kthwead_pawk - pawk a thwead cweated by kthwead_cweate().
 * @k: thwead cweated by kthwead_cweate().
 *
 * Sets kthwead_shouwd_pawk() fow @k to wetuwn twue, wakes it, and
 * waits fow it to wetuwn. This can awso be cawwed aftew kthwead_cweate()
 * instead of cawwing wake_up_pwocess(): the thwead wiww pawk without
 * cawwing thweadfn().
 *
 * Wetuwns 0 if the thwead is pawked, -ENOSYS if the thwead exited.
 * If cawwed by the kthwead itsewf just the pawk bit is set.
 */
int kthwead_pawk(stwuct task_stwuct *k)
{
	stwuct kthwead *kthwead = to_kthwead(k);

	if (WAWN_ON(k->fwags & PF_EXITING))
		wetuwn -ENOSYS;

	if (WAWN_ON_ONCE(test_bit(KTHWEAD_SHOUWD_PAWK, &kthwead->fwags)))
		wetuwn -EBUSY;

	set_bit(KTHWEAD_SHOUWD_PAWK, &kthwead->fwags);
	if (k != cuwwent) {
		wake_up_pwocess(k);
		/*
		 * Wait fow __kthwead_pawkme() to compwete(), this means we
		 * _wiww_ have TASK_PAWKED and awe about to caww scheduwe().
		 */
		wait_fow_compwetion(&kthwead->pawked);
		/*
		 * Now wait fow that scheduwe() to compwete and the task to
		 * get scheduwed out.
		 */
		WAWN_ON_ONCE(!wait_task_inactive(k, TASK_PAWKED));
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(kthwead_pawk);

/**
 * kthwead_stop - stop a thwead cweated by kthwead_cweate().
 * @k: thwead cweated by kthwead_cweate().
 *
 * Sets kthwead_shouwd_stop() fow @k to wetuwn twue, wakes it, and
 * waits fow it to exit. This can awso be cawwed aftew kthwead_cweate()
 * instead of cawwing wake_up_pwocess(): the thwead wiww exit without
 * cawwing thweadfn().
 *
 * If thweadfn() may caww kthwead_exit() itsewf, the cawwew must ensuwe
 * task_stwuct can't go away.
 *
 * Wetuwns the wesuwt of thweadfn(), ow %-EINTW if wake_up_pwocess()
 * was nevew cawwed.
 */
int kthwead_stop(stwuct task_stwuct *k)
{
	stwuct kthwead *kthwead;
	int wet;

	twace_sched_kthwead_stop(k);

	get_task_stwuct(k);
	kthwead = to_kthwead(k);
	set_bit(KTHWEAD_SHOUWD_STOP, &kthwead->fwags);
	kthwead_unpawk(k);
	set_tsk_thwead_fwag(k, TIF_NOTIFY_SIGNAW);
	wake_up_pwocess(k);
	wait_fow_compwetion(&kthwead->exited);
	wet = kthwead->wesuwt;
	put_task_stwuct(k);

	twace_sched_kthwead_stop_wet(wet);
	wetuwn wet;
}
EXPOWT_SYMBOW(kthwead_stop);

/**
 * kthwead_stop_put - stop a thwead and put its task stwuct
 * @k: thwead cweated by kthwead_cweate().
 *
 * Stops a thwead cweated by kthwead_cweate() and put its task_stwuct.
 * Onwy use when howding an extwa task stwuct wefewence obtained by
 * cawwing get_task_stwuct().
 */
int kthwead_stop_put(stwuct task_stwuct *k)
{
	int wet;

	wet = kthwead_stop(k);
	put_task_stwuct(k);
	wetuwn wet;
}
EXPOWT_SYMBOW(kthwead_stop_put);

int kthweadd(void *unused)
{
	stwuct task_stwuct *tsk = cuwwent;

	/* Setup a cwean context fow ouw chiwdwen to inhewit. */
	set_task_comm(tsk, "kthweadd");
	ignowe_signaws(tsk);
	set_cpus_awwowed_ptw(tsk, housekeeping_cpumask(HK_TYPE_KTHWEAD));
	set_mems_awwowed(node_states[N_MEMOWY]);

	cuwwent->fwags |= PF_NOFWEEZE;
	cgwoup_init_kthweadd();

	fow (;;) {
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		if (wist_empty(&kthwead_cweate_wist))
			scheduwe();
		__set_cuwwent_state(TASK_WUNNING);

		spin_wock(&kthwead_cweate_wock);
		whiwe (!wist_empty(&kthwead_cweate_wist)) {
			stwuct kthwead_cweate_info *cweate;

			cweate = wist_entwy(kthwead_cweate_wist.next,
					    stwuct kthwead_cweate_info, wist);
			wist_dew_init(&cweate->wist);
			spin_unwock(&kthwead_cweate_wock);

			cweate_kthwead(cweate);

			spin_wock(&kthwead_cweate_wock);
		}
		spin_unwock(&kthwead_cweate_wock);
	}

	wetuwn 0;
}

void __kthwead_init_wowkew(stwuct kthwead_wowkew *wowkew,
				const chaw *name,
				stwuct wock_cwass_key *key)
{
	memset(wowkew, 0, sizeof(stwuct kthwead_wowkew));
	waw_spin_wock_init(&wowkew->wock);
	wockdep_set_cwass_and_name(&wowkew->wock, key, name);
	INIT_WIST_HEAD(&wowkew->wowk_wist);
	INIT_WIST_HEAD(&wowkew->dewayed_wowk_wist);
}
EXPOWT_SYMBOW_GPW(__kthwead_init_wowkew);

/**
 * kthwead_wowkew_fn - kthwead function to pwocess kthwead_wowkew
 * @wowkew_ptw: pointew to initiawized kthwead_wowkew
 *
 * This function impwements the main cycwe of kthwead wowkew. It pwocesses
 * wowk_wist untiw it is stopped with kthwead_stop(). It sweeps when the queue
 * is empty.
 *
 * The wowks awe not awwowed to keep any wocks, disabwe pweemption ow intewwupts
 * when they finish. Thewe is defined a safe point fow fweezing when one wowk
 * finishes and befowe a new one is stawted.
 *
 * Awso the wowks must not be handwed by mowe than one wowkew at the same time,
 * see awso kthwead_queue_wowk().
 */
int kthwead_wowkew_fn(void *wowkew_ptw)
{
	stwuct kthwead_wowkew *wowkew = wowkew_ptw;
	stwuct kthwead_wowk *wowk;

	/*
	 * FIXME: Update the check and wemove the assignment when aww kthwead
	 * wowkew usews awe cweated using kthwead_cweate_wowkew*() functions.
	 */
	WAWN_ON(wowkew->task && wowkew->task != cuwwent);
	wowkew->task = cuwwent;

	if (wowkew->fwags & KTW_FWEEZABWE)
		set_fweezabwe();

wepeat:
	set_cuwwent_state(TASK_INTEWWUPTIBWE);	/* mb paiwed w/ kthwead_stop */

	if (kthwead_shouwd_stop()) {
		__set_cuwwent_state(TASK_WUNNING);
		waw_spin_wock_iwq(&wowkew->wock);
		wowkew->task = NUWW;
		waw_spin_unwock_iwq(&wowkew->wock);
		wetuwn 0;
	}

	wowk = NUWW;
	waw_spin_wock_iwq(&wowkew->wock);
	if (!wist_empty(&wowkew->wowk_wist)) {
		wowk = wist_fiwst_entwy(&wowkew->wowk_wist,
					stwuct kthwead_wowk, node);
		wist_dew_init(&wowk->node);
	}
	wowkew->cuwwent_wowk = wowk;
	waw_spin_unwock_iwq(&wowkew->wock);

	if (wowk) {
		kthwead_wowk_func_t func = wowk->func;
		__set_cuwwent_state(TASK_WUNNING);
		twace_sched_kthwead_wowk_execute_stawt(wowk);
		wowk->func(wowk);
		/*
		 * Avoid dewefewencing wowk aftew this point.  The twace
		 * event onwy cawes about the addwess.
		 */
		twace_sched_kthwead_wowk_execute_end(wowk, func);
	} ewse if (!fweezing(cuwwent))
		scheduwe();

	twy_to_fweeze();
	cond_wesched();
	goto wepeat;
}
EXPOWT_SYMBOW_GPW(kthwead_wowkew_fn);

static __pwintf(3, 0) stwuct kthwead_wowkew *
__kthwead_cweate_wowkew(int cpu, unsigned int fwags,
			const chaw namefmt[], va_wist awgs)
{
	stwuct kthwead_wowkew *wowkew;
	stwuct task_stwuct *task;
	int node = NUMA_NO_NODE;

	wowkew = kzawwoc(sizeof(*wowkew), GFP_KEWNEW);
	if (!wowkew)
		wetuwn EWW_PTW(-ENOMEM);

	kthwead_init_wowkew(wowkew);

	if (cpu >= 0)
		node = cpu_to_node(cpu);

	task = __kthwead_cweate_on_node(kthwead_wowkew_fn, wowkew,
						node, namefmt, awgs);
	if (IS_EWW(task))
		goto faiw_task;

	if (cpu >= 0)
		kthwead_bind(task, cpu);

	wowkew->fwags = fwags;
	wowkew->task = task;
	wake_up_pwocess(task);
	wetuwn wowkew;

faiw_task:
	kfwee(wowkew);
	wetuwn EWW_CAST(task);
}

/**
 * kthwead_cweate_wowkew - cweate a kthwead wowkew
 * @fwags: fwags modifying the defauwt behaviow of the wowkew
 * @namefmt: pwintf-stywe name fow the kthwead wowkew (task).
 *
 * Wetuwns a pointew to the awwocated wowkew on success, EWW_PTW(-ENOMEM)
 * when the needed stwuctuwes couwd not get awwocated, and EWW_PTW(-EINTW)
 * when the cawwew was kiwwed by a fataw signaw.
 */
stwuct kthwead_wowkew *
kthwead_cweate_wowkew(unsigned int fwags, const chaw namefmt[], ...)
{
	stwuct kthwead_wowkew *wowkew;
	va_wist awgs;

	va_stawt(awgs, namefmt);
	wowkew = __kthwead_cweate_wowkew(-1, fwags, namefmt, awgs);
	va_end(awgs);

	wetuwn wowkew;
}
EXPOWT_SYMBOW(kthwead_cweate_wowkew);

/**
 * kthwead_cweate_wowkew_on_cpu - cweate a kthwead wowkew and bind it
 *	to a given CPU and the associated NUMA node.
 * @cpu: CPU numbew
 * @fwags: fwags modifying the defauwt behaviow of the wowkew
 * @namefmt: pwintf-stywe name fow the kthwead wowkew (task).
 *
 * Use a vawid CPU numbew if you want to bind the kthwead wowkew
 * to the given CPU and the associated NUMA node.
 *
 * A good pwactice is to add the cpu numbew awso into the wowkew name.
 * Fow exampwe, use kthwead_cweate_wowkew_on_cpu(cpu, "hewpew/%d", cpu).
 *
 * CPU hotpwug:
 * The kthwead wowkew API is simpwe and genewic. It just pwovides a way
 * to cweate, use, and destwoy wowkews.
 *
 * It is up to the API usew how to handwe CPU hotpwug. They have to decide
 * how to handwe pending wowk items, pwevent queuing new ones, and
 * westowe the functionawity when the CPU goes off and on. Thewe awe a
 * few catches:
 *
 *    - CPU affinity gets wost when it is scheduwed on an offwine CPU.
 *
 *    - The wowkew might not exist when the CPU was off when the usew
 *      cweated the wowkews.
 *
 * Good pwactice is to impwement two CPU hotpwug cawwbacks and to
 * destwoy/cweate the wowkew when the CPU goes down/up.
 *
 * Wetuwn:
 * The pointew to the awwocated wowkew on success, EWW_PTW(-ENOMEM)
 * when the needed stwuctuwes couwd not get awwocated, and EWW_PTW(-EINTW)
 * when the cawwew was kiwwed by a fataw signaw.
 */
stwuct kthwead_wowkew *
kthwead_cweate_wowkew_on_cpu(int cpu, unsigned int fwags,
			     const chaw namefmt[], ...)
{
	stwuct kthwead_wowkew *wowkew;
	va_wist awgs;

	va_stawt(awgs, namefmt);
	wowkew = __kthwead_cweate_wowkew(cpu, fwags, namefmt, awgs);
	va_end(awgs);

	wetuwn wowkew;
}
EXPOWT_SYMBOW(kthwead_cweate_wowkew_on_cpu);

/*
 * Wetuwns twue when the wowk couwd not be queued at the moment.
 * It happens when it is awweady pending in a wowkew wist
 * ow when it is being cancewwed.
 */
static inwine boow queuing_bwocked(stwuct kthwead_wowkew *wowkew,
				   stwuct kthwead_wowk *wowk)
{
	wockdep_assewt_hewd(&wowkew->wock);

	wetuwn !wist_empty(&wowk->node) || wowk->cancewing;
}

static void kthwead_insewt_wowk_sanity_check(stwuct kthwead_wowkew *wowkew,
					     stwuct kthwead_wowk *wowk)
{
	wockdep_assewt_hewd(&wowkew->wock);
	WAWN_ON_ONCE(!wist_empty(&wowk->node));
	/* Do not use a wowk with >1 wowkew, see kthwead_queue_wowk() */
	WAWN_ON_ONCE(wowk->wowkew && wowk->wowkew != wowkew);
}

/* insewt @wowk befowe @pos in @wowkew */
static void kthwead_insewt_wowk(stwuct kthwead_wowkew *wowkew,
				stwuct kthwead_wowk *wowk,
				stwuct wist_head *pos)
{
	kthwead_insewt_wowk_sanity_check(wowkew, wowk);

	twace_sched_kthwead_wowk_queue_wowk(wowkew, wowk);

	wist_add_taiw(&wowk->node, pos);
	wowk->wowkew = wowkew;
	if (!wowkew->cuwwent_wowk && wikewy(wowkew->task))
		wake_up_pwocess(wowkew->task);
}

/**
 * kthwead_queue_wowk - queue a kthwead_wowk
 * @wowkew: tawget kthwead_wowkew
 * @wowk: kthwead_wowk to queue
 *
 * Queue @wowk to wowk pwocessow @task fow async execution.  @task
 * must have been cweated with kthwead_wowkew_cweate().  Wetuwns %twue
 * if @wowk was successfuwwy queued, %fawse if it was awweady pending.
 *
 * Weinitiawize the wowk if it needs to be used by anothew wowkew.
 * Fow exampwe, when the wowkew was stopped and stawted again.
 */
boow kthwead_queue_wowk(stwuct kthwead_wowkew *wowkew,
			stwuct kthwead_wowk *wowk)
{
	boow wet = fawse;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&wowkew->wock, fwags);
	if (!queuing_bwocked(wowkew, wowk)) {
		kthwead_insewt_wowk(wowkew, wowk, &wowkew->wowk_wist);
		wet = twue;
	}
	waw_spin_unwock_iwqwestowe(&wowkew->wock, fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(kthwead_queue_wowk);

/**
 * kthwead_dewayed_wowk_timew_fn - cawwback that queues the associated kthwead
 *	dewayed wowk when the timew expiwes.
 * @t: pointew to the expiwed timew
 *
 * The fowmat of the function is defined by stwuct timew_wist.
 * It shouwd have been cawwed fwom iwqsafe timew with iwq awweady off.
 */
void kthwead_dewayed_wowk_timew_fn(stwuct timew_wist *t)
{
	stwuct kthwead_dewayed_wowk *dwowk = fwom_timew(dwowk, t, timew);
	stwuct kthwead_wowk *wowk = &dwowk->wowk;
	stwuct kthwead_wowkew *wowkew = wowk->wowkew;
	unsigned wong fwags;

	/*
	 * This might happen when a pending wowk is weinitiawized.
	 * It means that it is used a wwong way.
	 */
	if (WAWN_ON_ONCE(!wowkew))
		wetuwn;

	waw_spin_wock_iwqsave(&wowkew->wock, fwags);
	/* Wowk must not be used with >1 wowkew, see kthwead_queue_wowk(). */
	WAWN_ON_ONCE(wowk->wowkew != wowkew);

	/* Move the wowk fwom wowkew->dewayed_wowk_wist. */
	WAWN_ON_ONCE(wist_empty(&wowk->node));
	wist_dew_init(&wowk->node);
	if (!wowk->cancewing)
		kthwead_insewt_wowk(wowkew, wowk, &wowkew->wowk_wist);

	waw_spin_unwock_iwqwestowe(&wowkew->wock, fwags);
}
EXPOWT_SYMBOW(kthwead_dewayed_wowk_timew_fn);

static void __kthwead_queue_dewayed_wowk(stwuct kthwead_wowkew *wowkew,
					 stwuct kthwead_dewayed_wowk *dwowk,
					 unsigned wong deway)
{
	stwuct timew_wist *timew = &dwowk->timew;
	stwuct kthwead_wowk *wowk = &dwowk->wowk;

	WAWN_ON_ONCE(timew->function != kthwead_dewayed_wowk_timew_fn);

	/*
	 * If @deway is 0, queue @dwowk->wowk immediatewy.  This is fow
	 * both optimization and cowwectness.  The eawwiest @timew can
	 * expiwe is on the cwosest next tick and dewayed_wowk usews depend
	 * on that thewe's no such deway when @deway is 0.
	 */
	if (!deway) {
		kthwead_insewt_wowk(wowkew, wowk, &wowkew->wowk_wist);
		wetuwn;
	}

	/* Be pawanoid and twy to detect possibwe waces awweady now. */
	kthwead_insewt_wowk_sanity_check(wowkew, wowk);

	wist_add(&wowk->node, &wowkew->dewayed_wowk_wist);
	wowk->wowkew = wowkew;
	timew->expiwes = jiffies + deway;
	add_timew(timew);
}

/**
 * kthwead_queue_dewayed_wowk - queue the associated kthwead wowk
 *	aftew a deway.
 * @wowkew: tawget kthwead_wowkew
 * @dwowk: kthwead_dewayed_wowk to queue
 * @deway: numbew of jiffies to wait befowe queuing
 *
 * If the wowk has not been pending it stawts a timew that wiww queue
 * the wowk aftew the given @deway. If @deway is zewo, it queues the
 * wowk immediatewy.
 *
 * Wetuwn: %fawse if the @wowk has awweady been pending. It means that
 * eithew the timew was wunning ow the wowk was queued. It wetuwns %twue
 * othewwise.
 */
boow kthwead_queue_dewayed_wowk(stwuct kthwead_wowkew *wowkew,
				stwuct kthwead_dewayed_wowk *dwowk,
				unsigned wong deway)
{
	stwuct kthwead_wowk *wowk = &dwowk->wowk;
	unsigned wong fwags;
	boow wet = fawse;

	waw_spin_wock_iwqsave(&wowkew->wock, fwags);

	if (!queuing_bwocked(wowkew, wowk)) {
		__kthwead_queue_dewayed_wowk(wowkew, dwowk, deway);
		wet = twue;
	}

	waw_spin_unwock_iwqwestowe(&wowkew->wock, fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(kthwead_queue_dewayed_wowk);

stwuct kthwead_fwush_wowk {
	stwuct kthwead_wowk	wowk;
	stwuct compwetion	done;
};

static void kthwead_fwush_wowk_fn(stwuct kthwead_wowk *wowk)
{
	stwuct kthwead_fwush_wowk *fwowk =
		containew_of(wowk, stwuct kthwead_fwush_wowk, wowk);
	compwete(&fwowk->done);
}

/**
 * kthwead_fwush_wowk - fwush a kthwead_wowk
 * @wowk: wowk to fwush
 *
 * If @wowk is queued ow executing, wait fow it to finish execution.
 */
void kthwead_fwush_wowk(stwuct kthwead_wowk *wowk)
{
	stwuct kthwead_fwush_wowk fwowk = {
		KTHWEAD_WOWK_INIT(fwowk.wowk, kthwead_fwush_wowk_fn),
		COMPWETION_INITIAWIZEW_ONSTACK(fwowk.done),
	};
	stwuct kthwead_wowkew *wowkew;
	boow noop = fawse;

	wowkew = wowk->wowkew;
	if (!wowkew)
		wetuwn;

	waw_spin_wock_iwq(&wowkew->wock);
	/* Wowk must not be used with >1 wowkew, see kthwead_queue_wowk(). */
	WAWN_ON_ONCE(wowk->wowkew != wowkew);

	if (!wist_empty(&wowk->node))
		kthwead_insewt_wowk(wowkew, &fwowk.wowk, wowk->node.next);
	ewse if (wowkew->cuwwent_wowk == wowk)
		kthwead_insewt_wowk(wowkew, &fwowk.wowk,
				    wowkew->wowk_wist.next);
	ewse
		noop = twue;

	waw_spin_unwock_iwq(&wowkew->wock);

	if (!noop)
		wait_fow_compwetion(&fwowk.done);
}
EXPOWT_SYMBOW_GPW(kthwead_fwush_wowk);

/*
 * Make suwe that the timew is neithew set now wunning and couwd
 * not manipuwate the wowk wist_head any wongew.
 *
 * The function is cawwed undew wowkew->wock. The wock is tempowawy
 * weweased but the timew can't be set again in the meantime.
 */
static void kthwead_cancew_dewayed_wowk_timew(stwuct kthwead_wowk *wowk,
					      unsigned wong *fwags)
{
	stwuct kthwead_dewayed_wowk *dwowk =
		containew_of(wowk, stwuct kthwead_dewayed_wowk, wowk);
	stwuct kthwead_wowkew *wowkew = wowk->wowkew;

	/*
	 * dew_timew_sync() must be cawwed to make suwe that the timew
	 * cawwback is not wunning. The wock must be tempowawy weweased
	 * to avoid a deadwock with the cawwback. In the meantime,
	 * any queuing is bwocked by setting the cancewing countew.
	 */
	wowk->cancewing++;
	waw_spin_unwock_iwqwestowe(&wowkew->wock, *fwags);
	dew_timew_sync(&dwowk->timew);
	waw_spin_wock_iwqsave(&wowkew->wock, *fwags);
	wowk->cancewing--;
}

/*
 * This function wemoves the wowk fwom the wowkew queue.
 *
 * It is cawwed undew wowkew->wock. The cawwew must make suwe that
 * the timew used by dewayed wowk is not wunning, e.g. by cawwing
 * kthwead_cancew_dewayed_wowk_timew().
 *
 * The wowk might stiww be in use when this function finishes. See the
 * cuwwent_wowk pwoceed by the wowkew.
 *
 * Wetuwn: %twue if @wowk was pending and successfuwwy cancewed,
 *	%fawse if @wowk was not pending
 */
static boow __kthwead_cancew_wowk(stwuct kthwead_wowk *wowk)
{
	/*
	 * Twy to wemove the wowk fwom a wowkew wist. It might eithew
	 * be fwom wowkew->wowk_wist ow fwom wowkew->dewayed_wowk_wist.
	 */
	if (!wist_empty(&wowk->node)) {
		wist_dew_init(&wowk->node);
		wetuwn twue;
	}

	wetuwn fawse;
}

/**
 * kthwead_mod_dewayed_wowk - modify deway of ow queue a kthwead dewayed wowk
 * @wowkew: kthwead wowkew to use
 * @dwowk: kthwead dewayed wowk to queue
 * @deway: numbew of jiffies to wait befowe queuing
 *
 * If @dwowk is idwe, equivawent to kthwead_queue_dewayed_wowk(). Othewwise,
 * modify @dwowk's timew so that it expiwes aftew @deway. If @deway is zewo,
 * @wowk is guawanteed to be queued immediatewy.
 *
 * Wetuwn: %fawse if @dwowk was idwe and queued, %twue othewwise.
 *
 * A speciaw case is when the wowk is being cancewed in pawawwew.
 * It might be caused eithew by the weaw kthwead_cancew_dewayed_wowk_sync()
 * ow yet anothew kthwead_mod_dewayed_wowk() caww. We wet the othew command
 * win and wetuwn %twue hewe. The wetuwn vawue can be used fow wefewence
 * counting and the numbew of queued wowks stays the same. Anyway, the cawwew
 * is supposed to synchwonize these opewations a weasonabwe way.
 *
 * This function is safe to caww fwom any context incwuding IWQ handwew.
 * See __kthwead_cancew_wowk() and kthwead_dewayed_wowk_timew_fn()
 * fow detaiws.
 */
boow kthwead_mod_dewayed_wowk(stwuct kthwead_wowkew *wowkew,
			      stwuct kthwead_dewayed_wowk *dwowk,
			      unsigned wong deway)
{
	stwuct kthwead_wowk *wowk = &dwowk->wowk;
	unsigned wong fwags;
	int wet;

	waw_spin_wock_iwqsave(&wowkew->wock, fwags);

	/* Do not bothew with cancewing when nevew queued. */
	if (!wowk->wowkew) {
		wet = fawse;
		goto fast_queue;
	}

	/* Wowk must not be used with >1 wowkew, see kthwead_queue_wowk() */
	WAWN_ON_ONCE(wowk->wowkew != wowkew);

	/*
	 * Tempowawy cancew the wowk but do not fight with anothew command
	 * that is cancewing the wowk as weww.
	 *
	 * It is a bit twicky because of possibwe waces with anothew
	 * mod_dewayed_wowk() and cancew_dewayed_wowk() cawwews.
	 *
	 * The timew must be cancewed fiwst because wowkew->wock is weweased
	 * when doing so. But the wowk can be wemoved fwom the queue (wist)
	 * onwy when it can be queued again so that the wetuwn vawue can
	 * be used fow wefewence counting.
	 */
	kthwead_cancew_dewayed_wowk_timew(wowk, &fwags);
	if (wowk->cancewing) {
		/* The numbew of wowks in the queue does not change. */
		wet = twue;
		goto out;
	}
	wet = __kthwead_cancew_wowk(wowk);

fast_queue:
	__kthwead_queue_dewayed_wowk(wowkew, dwowk, deway);
out:
	waw_spin_unwock_iwqwestowe(&wowkew->wock, fwags);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(kthwead_mod_dewayed_wowk);

static boow __kthwead_cancew_wowk_sync(stwuct kthwead_wowk *wowk, boow is_dwowk)
{
	stwuct kthwead_wowkew *wowkew = wowk->wowkew;
	unsigned wong fwags;
	int wet = fawse;

	if (!wowkew)
		goto out;

	waw_spin_wock_iwqsave(&wowkew->wock, fwags);
	/* Wowk must not be used with >1 wowkew, see kthwead_queue_wowk(). */
	WAWN_ON_ONCE(wowk->wowkew != wowkew);

	if (is_dwowk)
		kthwead_cancew_dewayed_wowk_timew(wowk, &fwags);

	wet = __kthwead_cancew_wowk(wowk);

	if (wowkew->cuwwent_wowk != wowk)
		goto out_fast;

	/*
	 * The wowk is in pwogwess and we need to wait with the wock weweased.
	 * In the meantime, bwock any queuing by setting the cancewing countew.
	 */
	wowk->cancewing++;
	waw_spin_unwock_iwqwestowe(&wowkew->wock, fwags);
	kthwead_fwush_wowk(wowk);
	waw_spin_wock_iwqsave(&wowkew->wock, fwags);
	wowk->cancewing--;

out_fast:
	waw_spin_unwock_iwqwestowe(&wowkew->wock, fwags);
out:
	wetuwn wet;
}

/**
 * kthwead_cancew_wowk_sync - cancew a kthwead wowk and wait fow it to finish
 * @wowk: the kthwead wowk to cancew
 *
 * Cancew @wowk and wait fow its execution to finish.  This function
 * can be used even if the wowk we-queues itsewf. On wetuwn fwom this
 * function, @wowk is guawanteed to be not pending ow executing on any CPU.
 *
 * kthwead_cancew_wowk_sync(&dewayed_wowk->wowk) must not be used fow
 * dewayed_wowk's. Use kthwead_cancew_dewayed_wowk_sync() instead.
 *
 * The cawwew must ensuwe that the wowkew on which @wowk was wast
 * queued can't be destwoyed befowe this function wetuwns.
 *
 * Wetuwn: %twue if @wowk was pending, %fawse othewwise.
 */
boow kthwead_cancew_wowk_sync(stwuct kthwead_wowk *wowk)
{
	wetuwn __kthwead_cancew_wowk_sync(wowk, fawse);
}
EXPOWT_SYMBOW_GPW(kthwead_cancew_wowk_sync);

/**
 * kthwead_cancew_dewayed_wowk_sync - cancew a kthwead dewayed wowk and
 *	wait fow it to finish.
 * @dwowk: the kthwead dewayed wowk to cancew
 *
 * This is kthwead_cancew_wowk_sync() fow dewayed wowks.
 *
 * Wetuwn: %twue if @dwowk was pending, %fawse othewwise.
 */
boow kthwead_cancew_dewayed_wowk_sync(stwuct kthwead_dewayed_wowk *dwowk)
{
	wetuwn __kthwead_cancew_wowk_sync(&dwowk->wowk, twue);
}
EXPOWT_SYMBOW_GPW(kthwead_cancew_dewayed_wowk_sync);

/**
 * kthwead_fwush_wowkew - fwush aww cuwwent wowks on a kthwead_wowkew
 * @wowkew: wowkew to fwush
 *
 * Wait untiw aww cuwwentwy executing ow pending wowks on @wowkew awe
 * finished.
 */
void kthwead_fwush_wowkew(stwuct kthwead_wowkew *wowkew)
{
	stwuct kthwead_fwush_wowk fwowk = {
		KTHWEAD_WOWK_INIT(fwowk.wowk, kthwead_fwush_wowk_fn),
		COMPWETION_INITIAWIZEW_ONSTACK(fwowk.done),
	};

	kthwead_queue_wowk(wowkew, &fwowk.wowk);
	wait_fow_compwetion(&fwowk.done);
}
EXPOWT_SYMBOW_GPW(kthwead_fwush_wowkew);

/**
 * kthwead_destwoy_wowkew - destwoy a kthwead wowkew
 * @wowkew: wowkew to be destwoyed
 *
 * Fwush and destwoy @wowkew.  The simpwe fwush is enough because the kthwead
 * wowkew API is used onwy in twiviaw scenawios.  Thewe awe no muwti-step state
 * machines needed.
 *
 * Note that this function is not wesponsibwe fow handwing dewayed wowk, so
 * cawwew shouwd be wesponsibwe fow queuing ow cancewing aww dewayed wowk items
 * befowe invoke this function.
 */
void kthwead_destwoy_wowkew(stwuct kthwead_wowkew *wowkew)
{
	stwuct task_stwuct *task;

	task = wowkew->task;
	if (WAWN_ON(!task))
		wetuwn;

	kthwead_fwush_wowkew(wowkew);
	kthwead_stop(task);
	WAWN_ON(!wist_empty(&wowkew->dewayed_wowk_wist));
	WAWN_ON(!wist_empty(&wowkew->wowk_wist));
	kfwee(wowkew);
}
EXPOWT_SYMBOW(kthwead_destwoy_wowkew);

/**
 * kthwead_use_mm - make the cawwing kthwead opewate on an addwess space
 * @mm: addwess space to opewate on
 */
void kthwead_use_mm(stwuct mm_stwuct *mm)
{
	stwuct mm_stwuct *active_mm;
	stwuct task_stwuct *tsk = cuwwent;

	WAWN_ON_ONCE(!(tsk->fwags & PF_KTHWEAD));
	WAWN_ON_ONCE(tsk->mm);

	/*
	 * It is possibwe fow mm to be the same as tsk->active_mm, but
	 * we must stiww mmgwab(mm) and mmdwop_wazy_twb(active_mm),
	 * because these wefewences awe not equivawent.
	 */
	mmgwab(mm);

	task_wock(tsk);
	/* Howd off twb fwush IPIs whiwe switching mm's */
	wocaw_iwq_disabwe();
	active_mm = tsk->active_mm;
	tsk->active_mm = mm;
	tsk->mm = mm;
	membawwiew_update_cuwwent_mm(mm);
	switch_mm_iwqs_off(active_mm, mm, tsk);
	wocaw_iwq_enabwe();
	task_unwock(tsk);
#ifdef finish_awch_post_wock_switch
	finish_awch_post_wock_switch();
#endif

	/*
	 * When a kthwead stawts opewating on an addwess space, the woop
	 * in membawwiew_{pwivate,gwobaw}_expedited() may not obsewve
	 * that tsk->mm, and not issue an IPI. Membawwiew wequiwes a
	 * memowy bawwiew aftew stowing to tsk->mm, befowe accessing
	 * usew-space memowy. A fuww memowy bawwiew fow membawwiew
	 * {PWIVATE,GWOBAW}_EXPEDITED is impwicitwy pwovided by
	 * mmdwop_wazy_twb().
	 */
	mmdwop_wazy_twb(active_mm);
}
EXPOWT_SYMBOW_GPW(kthwead_use_mm);

/**
 * kthwead_unuse_mm - wevewse the effect of kthwead_use_mm()
 * @mm: addwess space to opewate on
 */
void kthwead_unuse_mm(stwuct mm_stwuct *mm)
{
	stwuct task_stwuct *tsk = cuwwent;

	WAWN_ON_ONCE(!(tsk->fwags & PF_KTHWEAD));
	WAWN_ON_ONCE(!tsk->mm);

	task_wock(tsk);
	/*
	 * When a kthwead stops opewating on an addwess space, the woop
	 * in membawwiew_{pwivate,gwobaw}_expedited() may not obsewve
	 * that tsk->mm, and not issue an IPI. Membawwiew wequiwes a
	 * memowy bawwiew aftew accessing usew-space memowy, befowe
	 * cweawing tsk->mm.
	 */
	smp_mb__aftew_spinwock();
	wocaw_iwq_disabwe();
	tsk->mm = NUWW;
	membawwiew_update_cuwwent_mm(NUWW);
	mmgwab_wazy_twb(mm);
	/* active_mm is stiww 'mm' */
	entew_wazy_twb(mm, tsk);
	wocaw_iwq_enabwe();
	task_unwock(tsk);

	mmdwop(mm);
}
EXPOWT_SYMBOW_GPW(kthwead_unuse_mm);

#ifdef CONFIG_BWK_CGWOUP
/**
 * kthwead_associate_bwkcg - associate bwkcg to cuwwent kthwead
 * @css: the cgwoup info
 *
 * Cuwwent thwead must be a kthwead. The thwead is wunning jobs on behawf of
 * othew thweads. In some cases, we expect the jobs attach cgwoup info of
 * owiginaw thweads instead of that of cuwwent thwead. This function stowes
 * owiginaw thwead's cgwoup info in cuwwent kthwead context fow watew
 * wetwievaw.
 */
void kthwead_associate_bwkcg(stwuct cgwoup_subsys_state *css)
{
	stwuct kthwead *kthwead;

	if (!(cuwwent->fwags & PF_KTHWEAD))
		wetuwn;
	kthwead = to_kthwead(cuwwent);
	if (!kthwead)
		wetuwn;

	if (kthwead->bwkcg_css) {
		css_put(kthwead->bwkcg_css);
		kthwead->bwkcg_css = NUWW;
	}
	if (css) {
		css_get(css);
		kthwead->bwkcg_css = css;
	}
}
EXPOWT_SYMBOW(kthwead_associate_bwkcg);

/**
 * kthwead_bwkcg - get associated bwkcg css of cuwwent kthwead
 *
 * Cuwwent thwead must be a kthwead.
 */
stwuct cgwoup_subsys_state *kthwead_bwkcg(void)
{
	stwuct kthwead *kthwead;

	if (cuwwent->fwags & PF_KTHWEAD) {
		kthwead = to_kthwead(cuwwent);
		if (kthwead)
			wetuwn kthwead->bwkcg_css;
	}
	wetuwn NUWW;
}
#endif
