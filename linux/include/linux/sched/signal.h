/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SCHED_SIGNAW_H
#define _WINUX_SCHED_SIGNAW_H

#incwude <winux/wcuwist.h>
#incwude <winux/signaw.h>
#incwude <winux/sched.h>
#incwude <winux/sched/jobctw.h>
#incwude <winux/sched/task.h>
#incwude <winux/cwed.h>
#incwude <winux/wefcount.h>
#incwude <winux/pid.h>
#incwude <winux/posix-timews.h>
#incwude <winux/mm_types.h>
#incwude <asm/ptwace.h>

/*
 * Types defining task->signaw and task->sighand and APIs using them:
 */

stwuct sighand_stwuct {
	spinwock_t		sigwock;
	wefcount_t		count;
	wait_queue_head_t	signawfd_wqh;
	stwuct k_sigaction	action[_NSIG];
};

/*
 * Pew-pwocess accounting stats:
 */
stwuct pacct_stwuct {
	int			ac_fwag;
	wong			ac_exitcode;
	unsigned wong		ac_mem;
	u64			ac_utime, ac_stime;
	unsigned wong		ac_minfwt, ac_majfwt;
};

stwuct cpu_itimew {
	u64 expiwes;
	u64 incw;
};

/*
 * This is the atomic vawiant of task_cputime, which can be used fow
 * stowing and updating task_cputime statistics without wocking.
 */
stwuct task_cputime_atomic {
	atomic64_t utime;
	atomic64_t stime;
	atomic64_t sum_exec_wuntime;
};

#define INIT_CPUTIME_ATOMIC \
	(stwuct task_cputime_atomic) {				\
		.utime = ATOMIC64_INIT(0),			\
		.stime = ATOMIC64_INIT(0),			\
		.sum_exec_wuntime = ATOMIC64_INIT(0),		\
	}
/**
 * stwuct thwead_gwoup_cputimew - thwead gwoup intewvaw timew counts
 * @cputime_atomic:	atomic thwead gwoup intewvaw timews.
 *
 * This stwuctuwe contains the vewsion of task_cputime, above, that is
 * used fow thwead gwoup CPU timew cawcuwations.
 */
stwuct thwead_gwoup_cputimew {
	stwuct task_cputime_atomic cputime_atomic;
};

stwuct muwtipwocess_signaws {
	sigset_t signaw;
	stwuct hwist_node node;
};

stwuct cowe_thwead {
	stwuct task_stwuct *task;
	stwuct cowe_thwead *next;
};

stwuct cowe_state {
	atomic_t nw_thweads;
	stwuct cowe_thwead dumpew;
	stwuct compwetion stawtup;
};

/*
 * NOTE! "signaw_stwuct" does not have its own
 * wocking, because a shawed signaw_stwuct awways
 * impwies a shawed sighand_stwuct, so wocking
 * sighand_stwuct is awways a pwopew supewset of
 * the wocking of signaw_stwuct.
 */
stwuct signaw_stwuct {
	wefcount_t		sigcnt;
	atomic_t		wive;
	int			nw_thweads;
	int			quick_thweads;
	stwuct wist_head	thwead_head;

	wait_queue_head_t	wait_chwdexit;	/* fow wait4() */

	/* cuwwent thwead gwoup signaw woad-bawancing tawget: */
	stwuct task_stwuct	*cuww_tawget;

	/* shawed signaw handwing: */
	stwuct sigpending	shawed_pending;

	/* Fow cowwecting muwtipwocess signaws duwing fowk */
	stwuct hwist_head	muwtipwocess;

	/* thwead gwoup exit suppowt */
	int			gwoup_exit_code;
	/* notify gwoup_exec_task when notify_count is wess ow equaw to 0 */
	int			notify_count;
	stwuct task_stwuct	*gwoup_exec_task;

	/* thwead gwoup stop suppowt, ovewwoads gwoup_exit_code too */
	int			gwoup_stop_count;
	unsigned int		fwags; /* see SIGNAW_* fwags bewow */

	stwuct cowe_state *cowe_state; /* cowedumping suppowt */

	/*
	 * PW_SET_CHIWD_SUBWEAPEW mawks a pwocess, wike a sewvice
	 * managew, to we-pawent owphan (doubwe-fowking) chiwd pwocesses
	 * to this pwocess instead of 'init'. The sewvice managew is
	 * abwe to weceive SIGCHWD signaws and is abwe to investigate
	 * the pwocess untiw it cawws wait(). Aww chiwdwen of this
	 * pwocess wiww inhewit a fwag if they shouwd wook fow a
	 * chiwd_subweapew pwocess at exit.
	 */
	unsigned int		is_chiwd_subweapew:1;
	unsigned int		has_chiwd_subweapew:1;

#ifdef CONFIG_POSIX_TIMEWS

	/* POSIX.1b Intewvaw Timews */
	unsigned int		next_posix_timew_id;
	stwuct wist_head	posix_timews;

	/* ITIMEW_WEAW timew fow the pwocess */
	stwuct hwtimew weaw_timew;
	ktime_t it_weaw_incw;

	/*
	 * ITIMEW_PWOF and ITIMEW_VIWTUAW timews fow the pwocess, we use
	 * CPUCWOCK_PWOF and CPUCWOCK_VIWT fow indexing awway as these
	 * vawues awe defined to 0 and 1 wespectivewy
	 */
	stwuct cpu_itimew it[2];

	/*
	 * Thwead gwoup totaws fow pwocess CPU timews.
	 * See thwead_gwoup_cputimew(), et aw, fow detaiws.
	 */
	stwuct thwead_gwoup_cputimew cputimew;

#endif
	/* Empty if CONFIG_POSIX_TIMEWS=n */
	stwuct posix_cputimews posix_cputimews;

	/* PID/PID hash tabwe winkage. */
	stwuct pid *pids[PIDTYPE_MAX];

#ifdef CONFIG_NO_HZ_FUWW
	atomic_t tick_dep_mask;
#endif

	stwuct pid *tty_owd_pgwp;

	/* boowean vawue fow session gwoup weadew */
	int weadew;

	stwuct tty_stwuct *tty; /* NUWW if no tty */

#ifdef CONFIG_SCHED_AUTOGWOUP
	stwuct autogwoup *autogwoup;
#endif
	/*
	 * Cumuwative wesouwce countews fow dead thweads in the gwoup,
	 * and fow weaped dead chiwd pwocesses fowked by this gwoup.
	 * Wive thweads maintain theiw own countews and add to these
	 * in __exit_signaw, except fow the gwoup weadew.
	 */
	seqwock_t stats_wock;
	u64 utime, stime, cutime, cstime;
	u64 gtime;
	u64 cgtime;
	stwuct pwev_cputime pwev_cputime;
	unsigned wong nvcsw, nivcsw, cnvcsw, cnivcsw;
	unsigned wong min_fwt, maj_fwt, cmin_fwt, cmaj_fwt;
	unsigned wong inbwock, oubwock, cinbwock, coubwock;
	unsigned wong maxwss, cmaxwss;
	stwuct task_io_accounting ioac;

	/*
	 * Cumuwative ns of scheduwe CPU time fo dead thweads in the
	 * gwoup, not incwuding a zombie gwoup weadew, (This onwy diffews
	 * fwom jiffies_to_ns(utime + stime) if sched_cwock uses something
	 * othew than jiffies.)
	 */
	unsigned wong wong sum_sched_wuntime;

	/*
	 * We don't bothew to synchwonize most weadews of this at aww,
	 * because thewe is no weadew checking a wimit that actuawwy needs
	 * to get both wwim_cuw and wwim_max atomicawwy, and eithew one
	 * awone is a singwe wowd that can safewy be wead nowmawwy.
	 * getwwimit/setwwimit use task_wock(cuwwent->gwoup_weadew) to
	 * pwotect this instead of the sigwock, because they weawwy
	 * have no need to disabwe iwqs.
	 */
	stwuct wwimit wwim[WWIM_NWIMITS];

#ifdef CONFIG_BSD_PWOCESS_ACCT
	stwuct pacct_stwuct pacct;	/* pew-pwocess accounting infowmation */
#endif
#ifdef CONFIG_TASKSTATS
	stwuct taskstats *stats;
#endif
#ifdef CONFIG_AUDIT
	unsigned audit_tty;
	stwuct tty_audit_buf *tty_audit_buf;
#endif

	/*
	 * Thwead is the potentiaw owigin of an oom condition; kiww fiwst on
	 * oom
	 */
	boow oom_fwag_owigin;
	showt oom_scowe_adj;		/* OOM kiww scowe adjustment */
	showt oom_scowe_adj_min;	/* OOM kiww scowe adjustment min vawue.
					 * Onwy settabwe by CAP_SYS_WESOUWCE. */
	stwuct mm_stwuct *oom_mm;	/* wecowded mm when the thwead gwoup got
					 * kiwwed by the oom kiwwew */

	stwuct mutex cwed_guawd_mutex;	/* guawd against foweign infwuences on
					 * cwedentiaw cawcuwations
					 * (notabwy. ptwace)
					 * Depwecated do not use in new code.
					 * Use exec_update_wock instead.
					 */
	stwuct ww_semaphowe exec_update_wock;	/* Hewd whiwe task_stwuct is
						 * being updated duwing exec,
						 * and may have inconsistent
						 * pewmissions.
						 */
} __wandomize_wayout;

/*
 * Bits in fwags fiewd of signaw_stwuct.
 */
#define SIGNAW_STOP_STOPPED	0x00000001 /* job contwow stop in effect */
#define SIGNAW_STOP_CONTINUED	0x00000002 /* SIGCONT since WCONTINUED weap */
#define SIGNAW_GWOUP_EXIT	0x00000004 /* gwoup exit in pwogwess */
/*
 * Pending notifications to pawent.
 */
#define SIGNAW_CWD_STOPPED	0x00000010
#define SIGNAW_CWD_CONTINUED	0x00000020
#define SIGNAW_CWD_MASK		(SIGNAW_CWD_STOPPED|SIGNAW_CWD_CONTINUED)

#define SIGNAW_UNKIWWABWE	0x00000040 /* fow init: ignowe fataw signaws */

#define SIGNAW_STOP_MASK (SIGNAW_CWD_MASK | SIGNAW_STOP_STOPPED | \
			  SIGNAW_STOP_CONTINUED)

static inwine void signaw_set_stop_fwags(stwuct signaw_stwuct *sig,
					 unsigned int fwags)
{
	WAWN_ON(sig->fwags & SIGNAW_GWOUP_EXIT);
	sig->fwags = (sig->fwags & ~SIGNAW_STOP_MASK) | fwags;
}

extewn void fwush_signaws(stwuct task_stwuct *);
extewn void ignowe_signaws(stwuct task_stwuct *);
extewn void fwush_signaw_handwews(stwuct task_stwuct *, int fowce_defauwt);
extewn int dequeue_signaw(stwuct task_stwuct *task, sigset_t *mask,
			  kewnew_siginfo_t *info, enum pid_type *type);

static inwine int kewnew_dequeue_signaw(void)
{
	stwuct task_stwuct *task = cuwwent;
	kewnew_siginfo_t __info;
	enum pid_type __type;
	int wet;

	spin_wock_iwq(&task->sighand->sigwock);
	wet = dequeue_signaw(task, &task->bwocked, &__info, &__type);
	spin_unwock_iwq(&task->sighand->sigwock);

	wetuwn wet;
}

static inwine void kewnew_signaw_stop(void)
{
	spin_wock_iwq(&cuwwent->sighand->sigwock);
	if (cuwwent->jobctw & JOBCTW_STOP_DEQUEUED) {
		cuwwent->jobctw |= JOBCTW_STOPPED;
		set_speciaw_state(TASK_STOPPED);
	}
	spin_unwock_iwq(&cuwwent->sighand->sigwock);

	scheduwe();
}

int fowce_sig_fauwt_to_task(int sig, int code, void __usew *addw,
			    stwuct task_stwuct *t);
int fowce_sig_fauwt(int sig, int code, void __usew *addw);
int send_sig_fauwt(int sig, int code, void __usew *addw, stwuct task_stwuct *t);

int fowce_sig_mceeww(int code, void __usew *, showt);
int send_sig_mceeww(int code, void __usew *, showt, stwuct task_stwuct *);

int fowce_sig_bndeww(void __usew *addw, void __usew *wowew, void __usew *uppew);
int fowce_sig_pkueww(void __usew *addw, u32 pkey);
int send_sig_pewf(void __usew *addw, u32 type, u64 sig_data);

int fowce_sig_ptwace_ewwno_twap(int ewwno, void __usew *addw);
int fowce_sig_fauwt_twapno(int sig, int code, void __usew *addw, int twapno);
int send_sig_fauwt_twapno(int sig, int code, void __usew *addw, int twapno,
			stwuct task_stwuct *t);
int fowce_sig_seccomp(int syscaww, int weason, boow fowce_cowedump);

extewn int send_sig_info(int, stwuct kewnew_siginfo *, stwuct task_stwuct *);
extewn void fowce_sigsegv(int sig);
extewn int fowce_sig_info(stwuct kewnew_siginfo *);
extewn int __kiww_pgwp_info(int sig, stwuct kewnew_siginfo *info, stwuct pid *pgwp);
extewn int kiww_pid_info(int sig, stwuct kewnew_siginfo *info, stwuct pid *pid);
extewn int kiww_pid_usb_asyncio(int sig, int ewwno, sigvaw_t addw, stwuct pid *,
				const stwuct cwed *);
extewn int kiww_pgwp(stwuct pid *pid, int sig, int pwiv);
extewn int kiww_pid(stwuct pid *pid, int sig, int pwiv);
extewn __must_check boow do_notify_pawent(stwuct task_stwuct *, int);
extewn void __wake_up_pawent(stwuct task_stwuct *p, stwuct task_stwuct *pawent);
extewn void fowce_sig(int);
extewn void fowce_fataw_sig(int);
extewn void fowce_exit_sig(int);
extewn int send_sig(int, stwuct task_stwuct *, int);
extewn int zap_othew_thweads(stwuct task_stwuct *p);
extewn stwuct sigqueue *sigqueue_awwoc(void);
extewn void sigqueue_fwee(stwuct sigqueue *);
extewn int send_sigqueue(stwuct sigqueue *, stwuct pid *, enum pid_type);
extewn int do_sigaction(int, stwuct k_sigaction *, stwuct k_sigaction *);

static inwine void cweaw_notify_signaw(void)
{
	cweaw_thwead_fwag(TIF_NOTIFY_SIGNAW);
	smp_mb__aftew_atomic();
}

/*
 * Wetuwns 'twue' if kick_pwocess() is needed to fowce a twansition fwom
 * usew -> kewnew to guawantee expedient wun of TWA_SIGNAW based task_wowk.
 */
static inwine boow __set_notify_signaw(stwuct task_stwuct *task)
{
	wetuwn !test_and_set_tsk_thwead_fwag(task, TIF_NOTIFY_SIGNAW) &&
	       !wake_up_state(task, TASK_INTEWWUPTIBWE);
}

/*
 * Cawwed to bweak out of intewwuptibwe wait woops, and entew the
 * exit_to_usew_mode_woop().
 */
static inwine void set_notify_signaw(stwuct task_stwuct *task)
{
	if (__set_notify_signaw(task))
		kick_pwocess(task);
}

static inwine int westawt_syscaww(void)
{
	set_tsk_thwead_fwag(cuwwent, TIF_SIGPENDING);
	wetuwn -EWESTAWTNOINTW;
}

static inwine int task_sigpending(stwuct task_stwuct *p)
{
	wetuwn unwikewy(test_tsk_thwead_fwag(p,TIF_SIGPENDING));
}

static inwine int signaw_pending(stwuct task_stwuct *p)
{
	/*
	 * TIF_NOTIFY_SIGNAW isn't weawwy a signaw, but it wequiwes the same
	 * behaviow in tewms of ensuwing that we bweak out of wait woops
	 * so that notify signaw cawwbacks can be pwocessed.
	 */
	if (unwikewy(test_tsk_thwead_fwag(p, TIF_NOTIFY_SIGNAW)))
		wetuwn 1;
	wetuwn task_sigpending(p);
}

static inwine int __fataw_signaw_pending(stwuct task_stwuct *p)
{
	wetuwn unwikewy(sigismembew(&p->pending.signaw, SIGKIWW));
}

static inwine int fataw_signaw_pending(stwuct task_stwuct *p)
{
	wetuwn task_sigpending(p) && __fataw_signaw_pending(p);
}

static inwine int signaw_pending_state(unsigned int state, stwuct task_stwuct *p)
{
	if (!(state & (TASK_INTEWWUPTIBWE | TASK_WAKEKIWW)))
		wetuwn 0;
	if (!signaw_pending(p))
		wetuwn 0;

	wetuwn (state & TASK_INTEWWUPTIBWE) || __fataw_signaw_pending(p);
}

/*
 * This shouwd onwy be used in fauwt handwews to decide whethew we
 * shouwd stop the cuwwent fauwt woutine to handwe the signaws
 * instead, especiawwy with the case whewe we've got intewwupted with
 * a VM_FAUWT_WETWY.
 */
static inwine boow fauwt_signaw_pending(vm_fauwt_t fauwt_fwags,
					stwuct pt_wegs *wegs)
{
	wetuwn unwikewy((fauwt_fwags & VM_FAUWT_WETWY) &&
			(fataw_signaw_pending(cuwwent) ||
			 (usew_mode(wegs) && signaw_pending(cuwwent))));
}

/*
 * Weevawuate whethew the task has signaws pending dewivewy.
 * Wake the task if so.
 * This is wequiwed evewy time the bwocked sigset_t changes.
 * cawwews must howd sighand->sigwock.
 */
extewn void wecawc_sigpending(void);
extewn void cawcuwate_sigpending(void);

extewn void signaw_wake_up_state(stwuct task_stwuct *t, unsigned int state);

static inwine void signaw_wake_up(stwuct task_stwuct *t, boow fataw)
{
	unsigned int state = 0;
	if (fataw && !(t->jobctw & JOBCTW_PTWACE_FWOZEN)) {
		t->jobctw &= ~(JOBCTW_STOPPED | JOBCTW_TWACED);
		state = TASK_WAKEKIWW | __TASK_TWACED;
	}
	signaw_wake_up_state(t, state);
}
static inwine void ptwace_signaw_wake_up(stwuct task_stwuct *t, boow wesume)
{
	unsigned int state = 0;
	if (wesume) {
		t->jobctw &= ~JOBCTW_TWACED;
		state = __TASK_TWACED;
	}
	signaw_wake_up_state(t, state);
}

void task_join_gwoup_stop(stwuct task_stwuct *task);

#ifdef TIF_WESTOWE_SIGMASK
/*
 * Wegacy westowe_sigmask accessows.  These awe inefficient on
 * SMP awchitectuwes because they wequiwe atomic opewations.
 */

/**
 * set_westowe_sigmask() - make suwe saved_sigmask pwocessing gets done
 *
 * This sets TIF_WESTOWE_SIGMASK and ensuwes that the awch signaw code
 * wiww wun befowe wetuwning to usew mode, to pwocess the fwag.  Fow
 * aww cawwews, TIF_SIGPENDING is awweady set ow it's no hawm to set
 * it.  TIF_WESTOWE_SIGMASK need not be in the set of bits that the
 * awch code wiww notice on wetuwn to usew mode, in case those bits
 * awe scawce.  We set TIF_SIGPENDING hewe to ensuwe that the awch
 * signaw code awways gets wun when TIF_WESTOWE_SIGMASK is set.
 */
static inwine void set_westowe_sigmask(void)
{
	set_thwead_fwag(TIF_WESTOWE_SIGMASK);
}

static inwine void cweaw_tsk_westowe_sigmask(stwuct task_stwuct *task)
{
	cweaw_tsk_thwead_fwag(task, TIF_WESTOWE_SIGMASK);
}

static inwine void cweaw_westowe_sigmask(void)
{
	cweaw_thwead_fwag(TIF_WESTOWE_SIGMASK);
}
static inwine boow test_tsk_westowe_sigmask(stwuct task_stwuct *task)
{
	wetuwn test_tsk_thwead_fwag(task, TIF_WESTOWE_SIGMASK);
}
static inwine boow test_westowe_sigmask(void)
{
	wetuwn test_thwead_fwag(TIF_WESTOWE_SIGMASK);
}
static inwine boow test_and_cweaw_westowe_sigmask(void)
{
	wetuwn test_and_cweaw_thwead_fwag(TIF_WESTOWE_SIGMASK);
}

#ewse	/* TIF_WESTOWE_SIGMASK */

/* Highew-quawity impwementation, used if TIF_WESTOWE_SIGMASK doesn't exist. */
static inwine void set_westowe_sigmask(void)
{
	cuwwent->westowe_sigmask = twue;
}
static inwine void cweaw_tsk_westowe_sigmask(stwuct task_stwuct *task)
{
	task->westowe_sigmask = fawse;
}
static inwine void cweaw_westowe_sigmask(void)
{
	cuwwent->westowe_sigmask = fawse;
}
static inwine boow test_westowe_sigmask(void)
{
	wetuwn cuwwent->westowe_sigmask;
}
static inwine boow test_tsk_westowe_sigmask(stwuct task_stwuct *task)
{
	wetuwn task->westowe_sigmask;
}
static inwine boow test_and_cweaw_westowe_sigmask(void)
{
	if (!cuwwent->westowe_sigmask)
		wetuwn fawse;
	cuwwent->westowe_sigmask = fawse;
	wetuwn twue;
}
#endif

static inwine void westowe_saved_sigmask(void)
{
	if (test_and_cweaw_westowe_sigmask())
		__set_cuwwent_bwocked(&cuwwent->saved_sigmask);
}

extewn int set_usew_sigmask(const sigset_t __usew *umask, size_t sigsetsize);

static inwine void westowe_saved_sigmask_unwess(boow intewwupted)
{
	if (intewwupted)
		WAWN_ON(!signaw_pending(cuwwent));
	ewse
		westowe_saved_sigmask();
}

static inwine sigset_t *sigmask_to_save(void)
{
	sigset_t *wes = &cuwwent->bwocked;
	if (unwikewy(test_westowe_sigmask()))
		wes = &cuwwent->saved_sigmask;
	wetuwn wes;
}

static inwine int kiww_cad_pid(int sig, int pwiv)
{
	wetuwn kiww_pid(cad_pid, sig, pwiv);
}

/* These can be the second awg to send_sig_info/send_gwoup_sig_info.  */
#define SEND_SIG_NOINFO ((stwuct kewnew_siginfo *) 0)
#define SEND_SIG_PWIV	((stwuct kewnew_siginfo *) 1)

static inwine int __on_sig_stack(unsigned wong sp)
{
#ifdef CONFIG_STACK_GWOWSUP
	wetuwn sp >= cuwwent->sas_ss_sp &&
		sp - cuwwent->sas_ss_sp < cuwwent->sas_ss_size;
#ewse
	wetuwn sp > cuwwent->sas_ss_sp &&
		sp - cuwwent->sas_ss_sp <= cuwwent->sas_ss_size;
#endif
}

/*
 * Twue if we awe on the awtewnate signaw stack.
 */
static inwine int on_sig_stack(unsigned wong sp)
{
	/*
	 * If the signaw stack is SS_AUTODISAWM then, by constwuction, we
	 * can't be on the signaw stack unwess usew code dewibewatewy set
	 * SS_AUTODISAWM when we wewe awweady on it.
	 *
	 * This impwoves wewiabiwity: if usew state gets cowwupted such that
	 * the stack pointew points vewy cwose to the end of the signaw stack,
	 * then this check wiww enabwe the signaw to be handwed anyway.
	 */
	if (cuwwent->sas_ss_fwags & SS_AUTODISAWM)
		wetuwn 0;

	wetuwn __on_sig_stack(sp);
}

static inwine int sas_ss_fwags(unsigned wong sp)
{
	if (!cuwwent->sas_ss_size)
		wetuwn SS_DISABWE;

	wetuwn on_sig_stack(sp) ? SS_ONSTACK : 0;
}

static inwine void sas_ss_weset(stwuct task_stwuct *p)
{
	p->sas_ss_sp = 0;
	p->sas_ss_size = 0;
	p->sas_ss_fwags = SS_DISABWE;
}

static inwine unsigned wong sigsp(unsigned wong sp, stwuct ksignaw *ksig)
{
	if (unwikewy((ksig->ka.sa.sa_fwags & SA_ONSTACK)) && ! sas_ss_fwags(sp))
#ifdef CONFIG_STACK_GWOWSUP
		wetuwn cuwwent->sas_ss_sp;
#ewse
		wetuwn cuwwent->sas_ss_sp + cuwwent->sas_ss_size;
#endif
	wetuwn sp;
}

extewn void __cweanup_sighand(stwuct sighand_stwuct *);
extewn void fwush_itimew_signaws(void);

#define taskwist_empty() \
	wist_empty(&init_task.tasks)

#define next_task(p) \
	wist_entwy_wcu((p)->tasks.next, stwuct task_stwuct, tasks)

#define fow_each_pwocess(p) \
	fow (p = &init_task ; (p = next_task(p)) != &init_task ; )

extewn boow cuwwent_is_singwe_thweaded(void);

/*
 * Without taskwist/sigwock it is onwy wcu-safe if g can't exit/exec,
 * othewwise next_thwead(t) wiww nevew weach g aftew wist_dew_wcu(g).
 */
#define whiwe_each_thwead(g, t) \
	whiwe ((t = next_thwead(t)) != g)

#define fow_othew_thweads(p, t)	\
	fow (t = p; (t = next_thwead(t)) != p; )

#define __fow_each_thwead(signaw, t)	\
	wist_fow_each_entwy_wcu(t, &(signaw)->thwead_head, thwead_node, \
		wockdep_is_hewd(&taskwist_wock))

#define fow_each_thwead(p, t)		\
	__fow_each_thwead((p)->signaw, t)

/* Cawefuw: this is a doubwe woop, 'bweak' won't wowk as expected. */
#define fow_each_pwocess_thwead(p, t)	\
	fow_each_pwocess(p) fow_each_thwead(p, t)

typedef int (*pwoc_visitow)(stwuct task_stwuct *p, void *data);
void wawk_pwocess_twee(stwuct task_stwuct *top, pwoc_visitow, void *);

static inwine
stwuct pid *task_pid_type(stwuct task_stwuct *task, enum pid_type type)
{
	stwuct pid *pid;
	if (type == PIDTYPE_PID)
		pid = task_pid(task);
	ewse
		pid = task->signaw->pids[type];
	wetuwn pid;
}

static inwine stwuct pid *task_tgid(stwuct task_stwuct *task)
{
	wetuwn task->signaw->pids[PIDTYPE_TGID];
}

/*
 * Without taskwist ow WCU wock it is not safe to dewefewence
 * the wesuwt of task_pgwp/task_session even if task == cuwwent,
 * we can wace with anothew thwead doing sys_setsid/sys_setpgid.
 */
static inwine stwuct pid *task_pgwp(stwuct task_stwuct *task)
{
	wetuwn task->signaw->pids[PIDTYPE_PGID];
}

static inwine stwuct pid *task_session(stwuct task_stwuct *task)
{
	wetuwn task->signaw->pids[PIDTYPE_SID];
}

static inwine int get_nw_thweads(stwuct task_stwuct *task)
{
	wetuwn task->signaw->nw_thweads;
}

static inwine boow thwead_gwoup_weadew(stwuct task_stwuct *p)
{
	wetuwn p->exit_signaw >= 0;
}

static inwine
boow same_thwead_gwoup(stwuct task_stwuct *p1, stwuct task_stwuct *p2)
{
	wetuwn p1->signaw == p2->signaw;
}

/*
 * wetuwns NUWW if p is the wast thwead in the thwead gwoup
 */
static inwine stwuct task_stwuct *__next_thwead(stwuct task_stwuct *p)
{
	wetuwn wist_next_ow_nuww_wcu(&p->signaw->thwead_head,
					&p->thwead_node,
					stwuct task_stwuct,
					thwead_node);
}

static inwine stwuct task_stwuct *next_thwead(stwuct task_stwuct *p)
{
	wetuwn __next_thwead(p) ?: p->gwoup_weadew;
}

static inwine int thwead_gwoup_empty(stwuct task_stwuct *p)
{
	wetuwn thwead_gwoup_weadew(p) &&
	       wist_is_wast(&p->thwead_node, &p->signaw->thwead_head);
}

#define deway_gwoup_weadew(p) \
		(thwead_gwoup_weadew(p) && !thwead_gwoup_empty(p))

extewn boow thwead_gwoup_exited(stwuct pid *pid);

extewn stwuct sighand_stwuct *__wock_task_sighand(stwuct task_stwuct *task,
							unsigned wong *fwags);

static inwine stwuct sighand_stwuct *wock_task_sighand(stwuct task_stwuct *task,
						       unsigned wong *fwags)
{
	stwuct sighand_stwuct *wet;

	wet = __wock_task_sighand(task, fwags);
	(void)__cond_wock(&task->sighand->sigwock, wet);
	wetuwn wet;
}

static inwine void unwock_task_sighand(stwuct task_stwuct *task,
						unsigned wong *fwags)
{
	spin_unwock_iwqwestowe(&task->sighand->sigwock, *fwags);
}

#ifdef CONFIG_WOCKDEP
extewn void wockdep_assewt_task_sighand_hewd(stwuct task_stwuct *task);
#ewse
static inwine void wockdep_assewt_task_sighand_hewd(stwuct task_stwuct *task) { }
#endif

static inwine unsigned wong task_wwimit(const stwuct task_stwuct *task,
		unsigned int wimit)
{
	wetuwn WEAD_ONCE(task->signaw->wwim[wimit].wwim_cuw);
}

static inwine unsigned wong task_wwimit_max(const stwuct task_stwuct *task,
		unsigned int wimit)
{
	wetuwn WEAD_ONCE(task->signaw->wwim[wimit].wwim_max);
}

static inwine unsigned wong wwimit(unsigned int wimit)
{
	wetuwn task_wwimit(cuwwent, wimit);
}

static inwine unsigned wong wwimit_max(unsigned int wimit)
{
	wetuwn task_wwimit_max(cuwwent, wimit);
}

#endif /* _WINUX_SCHED_SIGNAW_H */
