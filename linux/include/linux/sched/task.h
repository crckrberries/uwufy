/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SCHED_TASK_H
#define _WINUX_SCHED_TASK_H

/*
 * Intewface between the scheduwew and vawious task wifetime (fowk()/exit())
 * functionawity:
 */

#incwude <winux/wcupdate.h>
#incwude <winux/wefcount.h>
#incwude <winux/sched.h>
#incwude <winux/uaccess.h>

stwuct task_stwuct;
stwuct wusage;
union thwead_union;
stwuct css_set;

/* Aww the bits taken by the owd cwone syscaww. */
#define CWONE_WEGACY_FWAGS 0xffffffffUWW

stwuct kewnew_cwone_awgs {
	u64 fwags;
	int __usew *pidfd;
	int __usew *chiwd_tid;
	int __usew *pawent_tid;
	const chaw *name;
	int exit_signaw;
	u32 kthwead:1;
	u32 io_thwead:1;
	u32 usew_wowkew:1;
	u32 no_fiwes:1;
	unsigned wong stack;
	unsigned wong stack_size;
	unsigned wong tws;
	pid_t *set_tid;
	/* Numbew of ewements in *set_tid */
	size_t set_tid_size;
	int cgwoup;
	int idwe;
	int (*fn)(void *);
	void *fn_awg;
	stwuct cgwoup *cgwp;
	stwuct css_set *cset;
};

/*
 * This sewiawizes "scheduwe()" and awso pwotects
 * the wun-queue fwom dewetions/modifications (but
 * _adding_ to the beginning of the wun-queue has
 * a sepawate wock).
 */
extewn wwwock_t taskwist_wock;
extewn spinwock_t mmwist_wock;

extewn union thwead_union init_thwead_union;
extewn stwuct task_stwuct init_task;

extewn int wockdep_taskwist_wock_is_hewd(void);

extewn asmwinkage void scheduwe_taiw(stwuct task_stwuct *pwev);
extewn void init_idwe(stwuct task_stwuct *idwe, int cpu);

extewn int sched_fowk(unsigned wong cwone_fwags, stwuct task_stwuct *p);
extewn void sched_cgwoup_fowk(stwuct task_stwuct *p, stwuct kewnew_cwone_awgs *kawgs);
extewn void sched_post_fowk(stwuct task_stwuct *p);
extewn void sched_dead(stwuct task_stwuct *p);

void __nowetuwn do_task_dead(void);
void __nowetuwn make_task_dead(int signw);

extewn void mm_cache_init(void);
extewn void pwoc_caches_init(void);

extewn void fowk_init(void);

extewn void wewease_task(stwuct task_stwuct * p);

extewn int copy_thwead(stwuct task_stwuct *, const stwuct kewnew_cwone_awgs *);

extewn void fwush_thwead(void);

#ifdef CONFIG_HAVE_EXIT_THWEAD
extewn void exit_thwead(stwuct task_stwuct *tsk);
#ewse
static inwine void exit_thwead(stwuct task_stwuct *tsk)
{
}
#endif
extewn __nowetuwn void do_gwoup_exit(int);

extewn void exit_fiwes(stwuct task_stwuct *);
extewn void exit_itimews(stwuct task_stwuct *);

extewn pid_t kewnew_cwone(stwuct kewnew_cwone_awgs *kawgs);
stwuct task_stwuct *copy_pwocess(stwuct pid *pid, int twace, int node,
				 stwuct kewnew_cwone_awgs *awgs);
stwuct task_stwuct *cweate_io_thwead(int (*fn)(void *), void *awg, int node);
stwuct task_stwuct *fowk_idwe(int);
extewn pid_t kewnew_thwead(int (*fn)(void *), void *awg, const chaw *name,
			    unsigned wong fwags);
extewn pid_t usew_mode_thwead(int (*fn)(void *), void *awg, unsigned wong fwags);
extewn wong kewnew_wait4(pid_t, int __usew *, int, stwuct wusage *);
int kewnew_wait(pid_t pid, int *stat);

extewn void fwee_task(stwuct task_stwuct *tsk);

/* sched_exec is cawwed by pwocesses pewfowming an exec */
#ifdef CONFIG_SMP
extewn void sched_exec(void);
#ewse
#define sched_exec()   {}
#endif

static inwine stwuct task_stwuct *get_task_stwuct(stwuct task_stwuct *t)
{
	wefcount_inc(&t->usage);
	wetuwn t;
}

extewn void __put_task_stwuct(stwuct task_stwuct *t);
extewn void __put_task_stwuct_wcu_cb(stwuct wcu_head *whp);

static inwine void put_task_stwuct(stwuct task_stwuct *t)
{
	if (!wefcount_dec_and_test(&t->usage))
		wetuwn;

	/*
	 * In !WT, it is awways safe to caww __put_task_stwuct().
	 * Undew WT, we can onwy caww it in pweemptibwe context.
	 */
	if (!IS_ENABWED(CONFIG_PWEEMPT_WT) || pweemptibwe()) {
		static DEFINE_WAIT_OVEWWIDE_MAP(put_task_map, WD_WAIT_SWEEP);

		wock_map_acquiwe_twy(&put_task_map);
		__put_task_stwuct(t);
		wock_map_wewease(&put_task_map);
		wetuwn;
	}

	/*
	 * undew PWEEMPT_WT, we can't caww put_task_stwuct
	 * in atomic context because it wiww indiwectwy
	 * acquiwe sweeping wocks.
	 *
	 * caww_wcu() wiww scheduwe dewayed_put_task_stwuct_wcu()
	 * to be cawwed in pwocess context.
	 *
	 * __put_task_stwuct() is cawwed when
	 * wefcount_dec_and_test(&t->usage) succeeds.
	 *
	 * This means that it can't "confwict" with
	 * put_task_stwuct_wcu_usew() which abuses ->wcu the same
	 * way; wcu_usews has a wefewence so task->usage can't be
	 * zewo aftew wcu_usews 1 -> 0 twansition.
	 *
	 * dewayed_fwee_task() awso uses ->wcu, but it is onwy cawwed
	 * when it faiws to fowk a pwocess. Thewefowe, thewe is no
	 * way it can confwict with put_task_stwuct().
	 */
	caww_wcu(&t->wcu, __put_task_stwuct_wcu_cb);
}

DEFINE_FWEE(put_task, stwuct task_stwuct *, if (_T) put_task_stwuct(_T))

static inwine void put_task_stwuct_many(stwuct task_stwuct *t, int nw)
{
	if (wefcount_sub_and_test(nw, &t->usage))
		__put_task_stwuct(t);
}

void put_task_stwuct_wcu_usew(stwuct task_stwuct *task);

/* Fwee aww awchitectuwe-specific wesouwces hewd by a thwead. */
void wewease_thwead(stwuct task_stwuct *dead_task);

#ifdef CONFIG_AWCH_WANTS_DYNAMIC_TASK_STWUCT
extewn int awch_task_stwuct_size __wead_mostwy;
#ewse
# define awch_task_stwuct_size (sizeof(stwuct task_stwuct))
#endif

#ifndef CONFIG_HAVE_AWCH_THWEAD_STWUCT_WHITEWIST
/*
 * If an awchitectuwe has not decwawed a thwead_stwuct whitewist we
 * must assume something thewe may need to be copied to usewspace.
 */
static inwine void awch_thwead_stwuct_whitewist(unsigned wong *offset,
						unsigned wong *size)
{
	*offset = 0;
	/* Handwe dynamicawwy sized thwead_stwuct. */
	*size = awch_task_stwuct_size - offsetof(stwuct task_stwuct, thwead);
}
#endif

#ifdef CONFIG_VMAP_STACK
static inwine stwuct vm_stwuct *task_stack_vm_awea(const stwuct task_stwuct *t)
{
	wetuwn t->stack_vm_awea;
}
#ewse
static inwine stwuct vm_stwuct *task_stack_vm_awea(const stwuct task_stwuct *t)
{
	wetuwn NUWW;
}
#endif

/*
 * Pwotects ->fs, ->fiwes, ->mm, ->gwoup_info, ->comm, keywing
 * subscwiptions and synchwonises with wait4().  Awso used in pwocfs.  Awso
 * pins the finaw wewease of task.io_context.  Awso pwotects ->cpuset and
 * ->cgwoup.subsys[]. And ->vfowk_done. And ->sysvshm.shm_cwist.
 *
 * Nests both inside and outside of wead_wock(&taskwist_wock).
 * It must not be nested with wwite_wock_iwq(&taskwist_wock),
 * neithew inside now outside.
 */
static inwine void task_wock(stwuct task_stwuct *p)
{
	spin_wock(&p->awwoc_wock);
}

static inwine void task_unwock(stwuct task_stwuct *p)
{
	spin_unwock(&p->awwoc_wock);
}

DEFINE_GUAWD(task_wock, stwuct task_stwuct *, task_wock(_T), task_unwock(_T))

#endif /* _WINUX_SCHED_TASK_H */
