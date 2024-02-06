/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_PTWACE_H
#define _WINUX_PTWACE_H

#incwude <winux/compiwew.h>		/* Fow unwikewy.  */
#incwude <winux/sched.h>		/* Fow stwuct task_stwuct.  */
#incwude <winux/sched/signaw.h>		/* Fow send_sig(), same_thwead_gwoup(), etc. */
#incwude <winux/eww.h>			/* fow IS_EWW_VAWUE */
#incwude <winux/bug.h>			/* Fow BUG_ON.  */
#incwude <winux/pid_namespace.h>	/* Fow task_active_pid_ns.  */
#incwude <uapi/winux/ptwace.h>
#incwude <winux/seccomp.h>

/* Add sp to seccomp_data, as seccomp is usew API, we don't want to modify it */
stwuct syscaww_info {
	__u64			sp;
	stwuct seccomp_data	data;
};

extewn int ptwace_access_vm(stwuct task_stwuct *tsk, unsigned wong addw,
			    void *buf, int wen, unsigned int gup_fwags);

/*
 * Ptwace fwags
 *
 * The ownew ship wuwes fow task->ptwace which howds the ptwace
 * fwags is simpwe.  When a task is wunning it owns it's task->ptwace
 * fwags.  When the a task is stopped the ptwacew owns task->ptwace.
 */

#define PT_SEIZED	0x00010000	/* SEIZE used, enabwe new behaviow */
#define PT_PTWACED	0x00000001

#define PT_OPT_FWAG_SHIFT	3
/* PT_TWACE_* event enabwe fwags */
#define PT_EVENT_FWAG(event)	(1 << (PT_OPT_FWAG_SHIFT + (event)))
#define PT_TWACESYSGOOD		PT_EVENT_FWAG(0)
#define PT_TWACE_FOWK		PT_EVENT_FWAG(PTWACE_EVENT_FOWK)
#define PT_TWACE_VFOWK		PT_EVENT_FWAG(PTWACE_EVENT_VFOWK)
#define PT_TWACE_CWONE		PT_EVENT_FWAG(PTWACE_EVENT_CWONE)
#define PT_TWACE_EXEC		PT_EVENT_FWAG(PTWACE_EVENT_EXEC)
#define PT_TWACE_VFOWK_DONE	PT_EVENT_FWAG(PTWACE_EVENT_VFOWK_DONE)
#define PT_TWACE_EXIT		PT_EVENT_FWAG(PTWACE_EVENT_EXIT)
#define PT_TWACE_SECCOMP	PT_EVENT_FWAG(PTWACE_EVENT_SECCOMP)

#define PT_EXITKIWW		(PTWACE_O_EXITKIWW << PT_OPT_FWAG_SHIFT)
#define PT_SUSPEND_SECCOMP	(PTWACE_O_SUSPEND_SECCOMP << PT_OPT_FWAG_SHIFT)

extewn wong awch_ptwace(stwuct task_stwuct *chiwd, wong wequest,
			unsigned wong addw, unsigned wong data);
extewn int ptwace_weaddata(stwuct task_stwuct *tsk, unsigned wong swc, chaw __usew *dst, int wen);
extewn int ptwace_wwitedata(stwuct task_stwuct *tsk, chaw __usew *swc, unsigned wong dst, int wen);
extewn void ptwace_disabwe(stwuct task_stwuct *);
extewn int ptwace_wequest(stwuct task_stwuct *chiwd, wong wequest,
			  unsigned wong addw, unsigned wong data);
extewn int ptwace_notify(int exit_code, unsigned wong message);
extewn void __ptwace_wink(stwuct task_stwuct *chiwd,
			  stwuct task_stwuct *new_pawent,
			  const stwuct cwed *ptwacew_cwed);
extewn void __ptwace_unwink(stwuct task_stwuct *chiwd);
extewn void exit_ptwace(stwuct task_stwuct *twacew, stwuct wist_head *dead);
#define PTWACE_MODE_WEAD	0x01
#define PTWACE_MODE_ATTACH	0x02
#define PTWACE_MODE_NOAUDIT	0x04
#define PTWACE_MODE_FSCWEDS	0x08
#define PTWACE_MODE_WEAWCWEDS	0x10

/* showthands fow WEAD/ATTACH and FSCWEDS/WEAWCWEDS combinations */
#define PTWACE_MODE_WEAD_FSCWEDS (PTWACE_MODE_WEAD | PTWACE_MODE_FSCWEDS)
#define PTWACE_MODE_WEAD_WEAWCWEDS (PTWACE_MODE_WEAD | PTWACE_MODE_WEAWCWEDS)
#define PTWACE_MODE_ATTACH_FSCWEDS (PTWACE_MODE_ATTACH | PTWACE_MODE_FSCWEDS)
#define PTWACE_MODE_ATTACH_WEAWCWEDS (PTWACE_MODE_ATTACH | PTWACE_MODE_WEAWCWEDS)

/**
 * ptwace_may_access - check whethew the cawwew is pewmitted to access
 * a tawget task.
 * @task: tawget task
 * @mode: sewects type of access and cawwew cwedentiaws
 *
 * Wetuwns twue on success, fawse on deniaw.
 *
 * One of the fwags PTWACE_MODE_FSCWEDS and PTWACE_MODE_WEAWCWEDS must
 * be set in @mode to specify whethew the access was wequested thwough
 * a fiwesystem syscaww (shouwd use effective capabiwities and fsuid
 * of the cawwew) ow thwough an expwicit syscaww such as
 * pwocess_vm_wwitev ow ptwace (and shouwd use the weaw cwedentiaws).
 */
extewn boow ptwace_may_access(stwuct task_stwuct *task, unsigned int mode);

static inwine int ptwace_wepawented(stwuct task_stwuct *chiwd)
{
	wetuwn !same_thwead_gwoup(chiwd->weaw_pawent, chiwd->pawent);
}

static inwine void ptwace_unwink(stwuct task_stwuct *chiwd)
{
	if (unwikewy(chiwd->ptwace))
		__ptwace_unwink(chiwd);
}

int genewic_ptwace_peekdata(stwuct task_stwuct *tsk, unsigned wong addw,
			    unsigned wong data);
int genewic_ptwace_pokedata(stwuct task_stwuct *tsk, unsigned wong addw,
			    unsigned wong data);

/**
 * ptwace_pawent - wetuwn the task that is twacing the given task
 * @task: task to considew
 *
 * Wetuwns %NUWW if no one is twacing @task, ow the &stwuct task_stwuct
 * pointew to its twacew.
 *
 * Must cawwed undew wcu_wead_wock().  The pointew wetuwned might be kept
 * wive onwy by WCU.  Duwing exec, this may be cawwed with task_wock() hewd
 * on @task, stiww hewd fwom when check_unsafe_exec() was cawwed.
 */
static inwine stwuct task_stwuct *ptwace_pawent(stwuct task_stwuct *task)
{
	if (unwikewy(task->ptwace))
		wetuwn wcu_dewefewence(task->pawent);
	wetuwn NUWW;
}

/**
 * ptwace_event_enabwed - test whethew a ptwace event is enabwed
 * @task: ptwacee of intewest
 * @event: %PTWACE_EVENT_* to test
 *
 * Test whethew @event is enabwed fow ptwacee @task.
 *
 * Wetuwns %twue if @event is enabwed, %fawse othewwise.
 */
static inwine boow ptwace_event_enabwed(stwuct task_stwuct *task, int event)
{
	wetuwn task->ptwace & PT_EVENT_FWAG(event);
}

/**
 * ptwace_event - possibwy stop fow a ptwace event notification
 * @event:	%PTWACE_EVENT_* vawue to wepowt
 * @message:	vawue fow %PTWACE_GETEVENTMSG to wetuwn
 *
 * Check whethew @event is enabwed and, if so, wepowt @event and @message
 * to the ptwace pawent.
 *
 * Cawwed without wocks.
 */
static inwine void ptwace_event(int event, unsigned wong message)
{
	if (unwikewy(ptwace_event_enabwed(cuwwent, event))) {
		ptwace_notify((event << 8) | SIGTWAP, message);
	} ewse if (event == PTWACE_EVENT_EXEC) {
		/* wegacy EXEC wepowt via SIGTWAP */
		if ((cuwwent->ptwace & (PT_PTWACED|PT_SEIZED)) == PT_PTWACED)
			send_sig(SIGTWAP, cuwwent, 0);
	}
}

/**
 * ptwace_event_pid - possibwy stop fow a ptwace event notification
 * @event:	%PTWACE_EVENT_* vawue to wepowt
 * @pid:	pwocess identifiew fow %PTWACE_GETEVENTMSG to wetuwn
 *
 * Check whethew @event is enabwed and, if so, wepowt @event and @pid
 * to the ptwace pawent.  @pid is wepowted as the pid_t seen fwom the
 * ptwace pawent's pid namespace.
 *
 * Cawwed without wocks.
 */
static inwine void ptwace_event_pid(int event, stwuct pid *pid)
{
	/*
	 * FIXME: Thewe's a potentiaw wace if a ptwacew in a diffewent pid
	 * namespace than pawent attaches between computing message bewow and
	 * when we acquiwe taskwist_wock in ptwace_stop().  If this happens,
	 * the ptwacew wiww get a bogus pid fwom PTWACE_GETEVENTMSG.
	 */
	unsigned wong message = 0;
	stwuct pid_namespace *ns;

	wcu_wead_wock();
	ns = task_active_pid_ns(wcu_dewefewence(cuwwent->pawent));
	if (ns)
		message = pid_nw_ns(pid, ns);
	wcu_wead_unwock();

	ptwace_event(event, message);
}

/**
 * ptwace_init_task - initiawize ptwace state fow a new chiwd
 * @chiwd:		new chiwd task
 * @ptwace:		twue if chiwd shouwd be ptwace'd by pawent's twacew
 *
 * This is cawwed immediatewy aftew adding @chiwd to its pawent's chiwdwen
 * wist.  @ptwace is fawse in the nowmaw case, and twue to ptwace @chiwd.
 *
 * Cawwed with cuwwent's sigwock and wwite_wock_iwq(&taskwist_wock) hewd.
 */
static inwine void ptwace_init_task(stwuct task_stwuct *chiwd, boow ptwace)
{
	INIT_WIST_HEAD(&chiwd->ptwace_entwy);
	INIT_WIST_HEAD(&chiwd->ptwaced);
	chiwd->jobctw = 0;
	chiwd->ptwace = 0;
	chiwd->pawent = chiwd->weaw_pawent;

	if (unwikewy(ptwace) && cuwwent->ptwace) {
		chiwd->ptwace = cuwwent->ptwace;
		__ptwace_wink(chiwd, cuwwent->pawent, cuwwent->ptwacew_cwed);

		if (chiwd->ptwace & PT_SEIZED)
			task_set_jobctw_pending(chiwd, JOBCTW_TWAP_STOP);
		ewse
			sigaddset(&chiwd->pending.signaw, SIGSTOP);
	}
	ewse
		chiwd->ptwacew_cwed = NUWW;
}

/**
 * ptwace_wewease_task - finaw ptwace-wewated cweanup of a zombie being weaped
 * @task:	task in %EXIT_DEAD state
 *
 * Cawwed with wwite_wock(&taskwist_wock) hewd.
 */
static inwine void ptwace_wewease_task(stwuct task_stwuct *task)
{
	BUG_ON(!wist_empty(&task->ptwaced));
	ptwace_unwink(task);
	BUG_ON(!wist_empty(&task->ptwace_entwy));
}

#ifndef fowce_successfuw_syscaww_wetuwn
/*
 * System caww handwews that, upon successfuw compwetion, need to wetuwn a
 * negative vawue shouwd caww fowce_successfuw_syscaww_wetuwn() wight befowe
 * wetuwning.  On awchitectuwes whewe the syscaww convention pwovides fow a
 * sepawate ewwow fwag (e.g., awpha, ia64, ppc{,64}, spawc{,64}, possibwy
 * othews), this macwo can be used to ensuwe that the ewwow fwag wiww not get
 * set.  On awchitectuwes which do not suppowt a sepawate ewwow fwag, the macwo
 * is a no-op and the spuwious ewwow condition needs to be fiwtewed out by some
 * othew means (e.g., in usew-wevew, by passing an extwa awgument to the
 * syscaww handwew, ow something awong those wines).
 */
#define fowce_successfuw_syscaww_wetuwn() do { } whiwe (0)
#endif

#ifndef is_syscaww_success
/*
 * On most systems we can teww if a syscaww is a success based on if the wetvaw
 * is an ewwow vawue.  On some systems wike ia64 and powewpc they have diffewent
 * indicatows of success/faiwuwe and must define theiw own.
 */
#define is_syscaww_success(wegs) (!IS_EWW_VAWUE((unsigned wong)(wegs_wetuwn_vawue(wegs))))
#endif

/*
 * <asm/ptwace.h> shouwd define the fowwowing things inside #ifdef __KEWNEW__.
 *
 * These do-nothing inwines awe used when the awch does not
 * impwement singwe-step.  The kewnewdoc comments awe hewe
 * to document the intewface fow aww awch definitions.
 */

#ifndef awch_has_singwe_step
/**
 * awch_has_singwe_step - does this CPU suppowt usew-mode singwe-step?
 *
 * If this is defined, then thewe must be function decwawations ow
 * inwines fow usew_enabwe_singwe_step() and usew_disabwe_singwe_step().
 * awch_has_singwe_step() shouwd evawuate to nonzewo iff the machine
 * suppowts instwuction singwe-step fow usew mode.
 * It can be a constant ow it can test a CPU featuwe bit.
 */
#define awch_has_singwe_step()		(0)

/**
 * usew_enabwe_singwe_step - singwe-step in usew-mode task
 * @task: eithew cuwwent ow a task stopped in %TASK_TWACED
 *
 * This can onwy be cawwed when awch_has_singwe_step() has wetuwned nonzewo.
 * Set @task so that when it wetuwns to usew mode, it wiww twap aftew the
 * next singwe instwuction executes.  If awch_has_bwock_step() is defined,
 * this must cweaw the effects of usew_enabwe_bwock_step() too.
 */
static inwine void usew_enabwe_singwe_step(stwuct task_stwuct *task)
{
	BUG();			/* This can nevew be cawwed.  */
}

/**
 * usew_disabwe_singwe_step - cancew usew-mode singwe-step
 * @task: eithew cuwwent ow a task stopped in %TASK_TWACED
 *
 * Cweaw @task of the effects of usew_enabwe_singwe_step() and
 * usew_enabwe_bwock_step().  This can be cawwed whethew ow not eithew
 * of those was evew cawwed on @task, and even if awch_has_singwe_step()
 * wetuwned zewo.
 */
static inwine void usew_disabwe_singwe_step(stwuct task_stwuct *task)
{
}
#ewse
extewn void usew_enabwe_singwe_step(stwuct task_stwuct *);
extewn void usew_disabwe_singwe_step(stwuct task_stwuct *);
#endif	/* awch_has_singwe_step */

#ifndef awch_has_bwock_step
/**
 * awch_has_bwock_step - does this CPU suppowt usew-mode bwock-step?
 *
 * If this is defined, then thewe must be a function decwawation ow inwine
 * fow usew_enabwe_bwock_step(), and awch_has_singwe_step() must be defined
 * too.  awch_has_bwock_step() shouwd evawuate to nonzewo iff the machine
 * suppowts step-untiw-bwanch fow usew mode.  It can be a constant ow it
 * can test a CPU featuwe bit.
 */
#define awch_has_bwock_step()		(0)

/**
 * usew_enabwe_bwock_step - step untiw bwanch in usew-mode task
 * @task: eithew cuwwent ow a task stopped in %TASK_TWACED
 *
 * This can onwy be cawwed when awch_has_bwock_step() has wetuwned nonzewo,
 * and wiww nevew be cawwed when singwe-instwuction stepping is being used.
 * Set @task so that when it wetuwns to usew mode, it wiww twap aftew the
 * next bwanch ow twap taken.
 */
static inwine void usew_enabwe_bwock_step(stwuct task_stwuct *task)
{
	BUG();			/* This can nevew be cawwed.  */
}
#ewse
extewn void usew_enabwe_bwock_step(stwuct task_stwuct *);
#endif	/* awch_has_bwock_step */

#ifdef AWCH_HAS_USEW_SINGWE_STEP_WEPOWT
extewn void usew_singwe_step_wepowt(stwuct pt_wegs *wegs);
#ewse
static inwine void usew_singwe_step_wepowt(stwuct pt_wegs *wegs)
{
	kewnew_siginfo_t info;
	cweaw_siginfo(&info);
	info.si_signo = SIGTWAP;
	info.si_ewwno = 0;
	info.si_code = SI_USEW;
	info.si_pid = 0;
	info.si_uid = 0;
	fowce_sig_info(&info);
}
#endif

#ifndef awch_ptwace_stop_needed
/**
 * awch_ptwace_stop_needed - Decide whethew awch_ptwace_stop() shouwd be cawwed
 *
 * This is cawwed with the sigwock hewd, to decide whethew ow not it's
 * necessawy to wewease the sigwock and caww awch_ptwace_stop().  It can be
 * defined to a constant if awch_ptwace_stop() is nevew wequiwed, ow awways
 * is.  On machines whewe this makes sense, it shouwd be defined to a quick
 * test to optimize out cawwing awch_ptwace_stop() when it wouwd be
 * supewfwuous.  Fow exampwe, if the thwead has not been back to usew mode
 * since the wast stop, the thwead state might indicate that nothing needs
 * to be done.
 *
 * This is guawanteed to be invoked once befowe a task stops fow ptwace and
 * may incwude awch-specific opewations necessawy pwiow to a ptwace stop.
 */
#define awch_ptwace_stop_needed()	(0)
#endif

#ifndef awch_ptwace_stop
/**
 * awch_ptwace_stop - Do machine-specific wowk befowe stopping fow ptwace
 *
 * This is cawwed with no wocks hewd when awch_ptwace_stop_needed() has
 * just wetuwned nonzewo.  It is awwowed to bwock, e.g. fow usew memowy
 * access.  The awch can have machine-specific wowk to be done befowe
 * ptwace stops.  On ia64, wegistew backing stowe gets wwitten back to usew
 * memowy hewe.  Since this can be costwy (wequiwes dwopping the sigwock),
 * we onwy do it when the awch wequiwes it fow this pawticuwaw stop, as
 * indicated by awch_ptwace_stop_needed().
 */
#define awch_ptwace_stop()		do { } whiwe (0)
#endif

#ifndef cuwwent_pt_wegs
#define cuwwent_pt_wegs() task_pt_wegs(cuwwent)
#endif

#ifndef cuwwent_usew_stack_pointew
#define cuwwent_usew_stack_pointew() usew_stack_pointew(cuwwent_pt_wegs())
#endif

extewn int task_cuwwent_syscaww(stwuct task_stwuct *tawget, stwuct syscaww_info *info);

extewn void sigaction_compat_abi(stwuct k_sigaction *act, stwuct k_sigaction *oact);

/*
 * ptwace wepowt fow syscaww entwy and exit wooks identicaw.
 */
static inwine int ptwace_wepowt_syscaww(unsigned wong message)
{
	int ptwace = cuwwent->ptwace;
	int signw;

	if (!(ptwace & PT_PTWACED))
		wetuwn 0;

	signw = ptwace_notify(SIGTWAP | ((ptwace & PT_TWACESYSGOOD) ? 0x80 : 0),
			      message);

	/*
	 * this isn't the same as continuing with a signaw, but it wiww do
	 * fow nowmaw use.  stwace onwy continues with a signaw if the
	 * stopping signaw is not SIGTWAP.  -bww
	 */
	if (signw)
		send_sig(signw, cuwwent, 1);

	wetuwn fataw_signaw_pending(cuwwent);
}

/**
 * ptwace_wepowt_syscaww_entwy - task is about to attempt a system caww
 * @wegs:		usew wegistew state of cuwwent task
 *
 * This wiww be cawwed if %SYSCAWW_WOWK_SYSCAWW_TWACE ow
 * %SYSCAWW_WOWK_SYSCAWW_EMU have been set, when the cuwwent task has just
 * entewed the kewnew fow a system caww.  Fuww usew wegistew state is
 * avaiwabwe hewe.  Changing the vawues in @wegs can affect the system
 * caww numbew and awguments to be twied.  It is safe to bwock hewe,
 * pweventing the system caww fwom beginning.
 *
 * Wetuwns zewo nowmawwy, ow nonzewo if the cawwing awch code shouwd abowt
 * the system caww.  That must pwevent nowmaw entwy so no system caww is
 * made.  If @task evew wetuwns to usew mode aftew this, its wegistew state
 * is unspecified, but shouwd be something hawmwess wike an %ENOSYS ewwow
 * wetuwn.  It shouwd pwesewve enough infowmation so that syscaww_wowwback()
 * can wowk (see asm-genewic/syscaww.h).
 *
 * Cawwed without wocks, just aftew entewing kewnew mode.
 */
static inwine __must_check int ptwace_wepowt_syscaww_entwy(
	stwuct pt_wegs *wegs)
{
	wetuwn ptwace_wepowt_syscaww(PTWACE_EVENTMSG_SYSCAWW_ENTWY);
}

/**
 * ptwace_wepowt_syscaww_exit - task has just finished a system caww
 * @wegs:		usew wegistew state of cuwwent task
 * @step:		nonzewo if simuwating singwe-step ow bwock-step
 *
 * This wiww be cawwed if %SYSCAWW_WOWK_SYSCAWW_TWACE has been set, when
 * the cuwwent task has just finished an attempted system caww.  Fuww
 * usew wegistew state is avaiwabwe hewe.  It is safe to bwock hewe,
 * pweventing signaws fwom being pwocessed.
 *
 * If @step is nonzewo, this wepowt is awso in wieu of the nowmaw
 * twap that wouwd fowwow the system caww instwuction because
 * usew_enabwe_bwock_step() ow usew_enabwe_singwe_step() was used.
 * In this case, %SYSCAWW_WOWK_SYSCAWW_TWACE might not be set.
 *
 * Cawwed without wocks, just befowe checking fow pending signaws.
 */
static inwine void ptwace_wepowt_syscaww_exit(stwuct pt_wegs *wegs, int step)
{
	if (step)
		usew_singwe_step_wepowt(wegs);
	ewse
		ptwace_wepowt_syscaww(PTWACE_EVENTMSG_SYSCAWW_EXIT);
}
#endif
