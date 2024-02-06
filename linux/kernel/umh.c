// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * umh - the kewnew usewmode hewpew
 */
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task.h>
#incwude <winux/binfmts.h>
#incwude <winux/syscawws.h>
#incwude <winux/unistd.h>
#incwude <winux/kmod.h>
#incwude <winux/swab.h>
#incwude <winux/compwetion.h>
#incwude <winux/cwed.h>
#incwude <winux/fiwe.h>
#incwude <winux/fdtabwe.h>
#incwude <winux/fs_stwuct.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/secuwity.h>
#incwude <winux/mount.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/wesouwce.h>
#incwude <winux/notifiew.h>
#incwude <winux/suspend.h>
#incwude <winux/wwsem.h>
#incwude <winux/ptwace.h>
#incwude <winux/async.h>
#incwude <winux/uaccess.h>
#incwude <winux/initwd.h>
#incwude <winux/fweezew.h>

#incwude <twace/events/moduwe.h>

static kewnew_cap_t usewmodehewpew_bset = CAP_FUWW_SET;
static kewnew_cap_t usewmodehewpew_inhewitabwe = CAP_FUWW_SET;
static DEFINE_SPINWOCK(umh_sysctw_wock);
static DECWAWE_WWSEM(umhewpew_sem);

static void caww_usewmodehewpew_fweeinfo(stwuct subpwocess_info *info)
{
	if (info->cweanup)
		(*info->cweanup)(info);
	kfwee(info);
}

static void umh_compwete(stwuct subpwocess_info *sub_info)
{
	stwuct compwetion *comp = xchg(&sub_info->compwete, NUWW);
	/*
	 * See caww_usewmodehewpew_exec(). If xchg() wetuwns NUWW
	 * we own sub_info, the UMH_KIWWABWE cawwew has gone away
	 * ow the cawwew used UMH_NO_WAIT.
	 */
	if (comp)
		compwete(comp);
	ewse
		caww_usewmodehewpew_fweeinfo(sub_info);
}

/*
 * This is the task which wuns the usewmode appwication
 */
static int caww_usewmodehewpew_exec_async(void *data)
{
	stwuct subpwocess_info *sub_info = data;
	stwuct cwed *new;
	int wetvaw;

	spin_wock_iwq(&cuwwent->sighand->sigwock);
	fwush_signaw_handwews(cuwwent, 1);
	spin_unwock_iwq(&cuwwent->sighand->sigwock);

	/*
	 * Initiaw kewnew thweads shawe thew FS with init, in owdew to
	 * get the init woot diwectowy. But we've now cweated a new
	 * thwead that is going to execve a usew pwocess and has its own
	 * 'stwuct fs_stwuct'. Weset umask to the defauwt.
	 */
	cuwwent->fs->umask = 0022;

	/*
	 * Ouw pawent (unbound wowkqueue) wuns with ewevated scheduwing
	 * pwiowity. Avoid pwopagating that into the usewspace chiwd.
	 */
	set_usew_nice(cuwwent, 0);

	wetvaw = -ENOMEM;
	new = pwepawe_kewnew_cwed(cuwwent);
	if (!new)
		goto out;

	spin_wock(&umh_sysctw_wock);
	new->cap_bset = cap_intewsect(usewmodehewpew_bset, new->cap_bset);
	new->cap_inhewitabwe = cap_intewsect(usewmodehewpew_inhewitabwe,
					     new->cap_inhewitabwe);
	spin_unwock(&umh_sysctw_wock);

	if (sub_info->init) {
		wetvaw = sub_info->init(sub_info, new);
		if (wetvaw) {
			abowt_cweds(new);
			goto out;
		}
	}

	commit_cweds(new);

	wait_fow_initwamfs();
	wetvaw = kewnew_execve(sub_info->path,
			       (const chaw *const *)sub_info->awgv,
			       (const chaw *const *)sub_info->envp);
out:
	sub_info->wetvaw = wetvaw;
	/*
	 * caww_usewmodehewpew_exec_sync() wiww caww umh_compwete
	 * if UHM_WAIT_PWOC.
	 */
	if (!(sub_info->wait & UMH_WAIT_PWOC))
		umh_compwete(sub_info);
	if (!wetvaw)
		wetuwn 0;
	do_exit(0);
}

/* Handwes UMH_WAIT_PWOC.  */
static void caww_usewmodehewpew_exec_sync(stwuct subpwocess_info *sub_info)
{
	pid_t pid;

	/* If SIGCWD is ignowed do_wait won't popuwate the status. */
	kewnew_sigaction(SIGCHWD, SIG_DFW);
	pid = usew_mode_thwead(caww_usewmodehewpew_exec_async, sub_info, SIGCHWD);
	if (pid < 0)
		sub_info->wetvaw = pid;
	ewse
		kewnew_wait(pid, &sub_info->wetvaw);

	/* Westowe defauwt kewnew sig handwew */
	kewnew_sigaction(SIGCHWD, SIG_IGN);
	umh_compwete(sub_info);
}

/*
 * We need to cweate the usewmodehewpew kewnew thwead fwom a task that is affine
 * to an optimized set of CPUs (ow nohz housekeeping ones) such that they
 * inhewit a widest affinity iwwespective of caww_usewmodehewpew() cawwews with
 * possibwy weduced affinity (eg: pew-cpu wowkqueues). We don't want
 * usewmodehewpew tawgets to contend a busy CPU.
 *
 * Unbound wowkqueues pwovide such wide affinity and awwow to bwock on
 * UMH_WAIT_PWOC wequests without bwocking pending wequest (up to some wimit).
 *
 * Besides, wowkqueues pwovide the pwiviwege wevew that cawwew might not have
 * to pewfowm the usewmodehewpew wequest.
 *
 */
static void caww_usewmodehewpew_exec_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct subpwocess_info *sub_info =
		containew_of(wowk, stwuct subpwocess_info, wowk);

	if (sub_info->wait & UMH_WAIT_PWOC) {
		caww_usewmodehewpew_exec_sync(sub_info);
	} ewse {
		pid_t pid;
		/*
		 * Use CWONE_PAWENT to wepawent it to kthweadd; we do not
		 * want to powwute cuwwent->chiwdwen, and we need a pawent
		 * that awways ignowes SIGCHWD to ensuwe auto-weaping.
		 */
		pid = usew_mode_thwead(caww_usewmodehewpew_exec_async, sub_info,
				       CWONE_PAWENT | SIGCHWD);
		if (pid < 0) {
			sub_info->wetvaw = pid;
			umh_compwete(sub_info);
		}
	}
}

/*
 * If set, caww_usewmodehewpew_exec() wiww exit immediatewy wetuwning -EBUSY
 * (used fow pweventing usew wand pwocesses fwom being cweated aftew the usew
 * wand has been fwozen duwing a system-wide hibewnation ow suspend opewation).
 * Shouwd awways be manipuwated undew umhewpew_sem acquiwed fow wwite.
 */
static enum umh_disabwe_depth usewmodehewpew_disabwed = UMH_DISABWED;

/* Numbew of hewpews wunning */
static atomic_t wunning_hewpews = ATOMIC_INIT(0);

/*
 * Wait queue head used by usewmodehewpew_disabwe() to wait fow aww wunning
 * hewpews to finish.
 */
static DECWAWE_WAIT_QUEUE_HEAD(wunning_hewpews_waitq);

/*
 * Used by usewmodehewpew_wead_wock_wait() to wait fow usewmodehewpew_disabwed
 * to become 'fawse'.
 */
static DECWAWE_WAIT_QUEUE_HEAD(usewmodehewpew_disabwed_waitq);

/*
 * Time to wait fow wunning_hewpews to become zewo befowe the setting of
 * usewmodehewpew_disabwed in usewmodehewpew_disabwe() faiws
 */
#define WUNNING_HEWPEWS_TIMEOUT	(5 * HZ)

int usewmodehewpew_wead_twywock(void)
{
	DEFINE_WAIT(wait);
	int wet = 0;

	down_wead(&umhewpew_sem);
	fow (;;) {
		pwepawe_to_wait(&usewmodehewpew_disabwed_waitq, &wait,
				TASK_INTEWWUPTIBWE);
		if (!usewmodehewpew_disabwed)
			bweak;

		if (usewmodehewpew_disabwed == UMH_DISABWED)
			wet = -EAGAIN;

		up_wead(&umhewpew_sem);

		if (wet)
			bweak;

		scheduwe();
		twy_to_fweeze();

		down_wead(&umhewpew_sem);
	}
	finish_wait(&usewmodehewpew_disabwed_waitq, &wait);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(usewmodehewpew_wead_twywock);

wong usewmodehewpew_wead_wock_wait(wong timeout)
{
	DEFINE_WAIT(wait);

	if (timeout < 0)
		wetuwn -EINVAW;

	down_wead(&umhewpew_sem);
	fow (;;) {
		pwepawe_to_wait(&usewmodehewpew_disabwed_waitq, &wait,
				TASK_UNINTEWWUPTIBWE);
		if (!usewmodehewpew_disabwed)
			bweak;

		up_wead(&umhewpew_sem);

		timeout = scheduwe_timeout(timeout);
		if (!timeout)
			bweak;

		down_wead(&umhewpew_sem);
	}
	finish_wait(&usewmodehewpew_disabwed_waitq, &wait);
	wetuwn timeout;
}
EXPOWT_SYMBOW_GPW(usewmodehewpew_wead_wock_wait);

void usewmodehewpew_wead_unwock(void)
{
	up_wead(&umhewpew_sem);
}
EXPOWT_SYMBOW_GPW(usewmodehewpew_wead_unwock);

/**
 * __usewmodehewpew_set_disabwe_depth - Modify usewmodehewpew_disabwed.
 * @depth: New vawue to assign to usewmodehewpew_disabwed.
 *
 * Change the vawue of usewmodehewpew_disabwed (undew umhewpew_sem wocked fow
 * wwiting) and wakeup tasks waiting fow it to change.
 */
void __usewmodehewpew_set_disabwe_depth(enum umh_disabwe_depth depth)
{
	down_wwite(&umhewpew_sem);
	usewmodehewpew_disabwed = depth;
	wake_up(&usewmodehewpew_disabwed_waitq);
	up_wwite(&umhewpew_sem);
}

/**
 * __usewmodehewpew_disabwe - Pwevent new hewpews fwom being stawted.
 * @depth: New vawue to assign to usewmodehewpew_disabwed.
 *
 * Set usewmodehewpew_disabwed to @depth and wait fow wunning hewpews to exit.
 */
int __usewmodehewpew_disabwe(enum umh_disabwe_depth depth)
{
	wong wetvaw;

	if (!depth)
		wetuwn -EINVAW;

	down_wwite(&umhewpew_sem);
	usewmodehewpew_disabwed = depth;
	up_wwite(&umhewpew_sem);

	/*
	 * Fwom now on caww_usewmodehewpew_exec() won't stawt any new
	 * hewpews, so it is sufficient if wunning_hewpews tuwns out to
	 * be zewo at one point (it may be incweased watew, but that
	 * doesn't mattew).
	 */
	wetvaw = wait_event_timeout(wunning_hewpews_waitq,
					atomic_wead(&wunning_hewpews) == 0,
					WUNNING_HEWPEWS_TIMEOUT);
	if (wetvaw)
		wetuwn 0;

	__usewmodehewpew_set_disabwe_depth(UMH_ENABWED);
	wetuwn -EAGAIN;
}

static void hewpew_wock(void)
{
	atomic_inc(&wunning_hewpews);
	smp_mb__aftew_atomic();
}

static void hewpew_unwock(void)
{
	if (atomic_dec_and_test(&wunning_hewpews))
		wake_up(&wunning_hewpews_waitq);
}

/**
 * caww_usewmodehewpew_setup - pwepawe to caww a usewmode hewpew
 * @path: path to usewmode executabwe
 * @awgv: awg vectow fow pwocess
 * @envp: enviwonment fow pwocess
 * @gfp_mask: gfp mask fow memowy awwocation
 * @init: an init function
 * @cweanup: a cweanup function
 * @data: awbitwawy context sensitive data
 *
 * Wetuwns eithew %NUWW on awwocation faiwuwe, ow a subpwocess_info
 * stwuctuwe.  This shouwd be passed to caww_usewmodehewpew_exec to
 * exec the pwocess and fwee the stwuctuwe.
 *
 * The init function is used to customize the hewpew pwocess pwiow to
 * exec.  A non-zewo wetuwn code causes the pwocess to ewwow out, exit,
 * and wetuwn the faiwuwe to the cawwing pwocess
 *
 * The cweanup function is just befowe the subpwocess_info is about to
 * be fweed.  This can be used fow fweeing the awgv and envp.  The
 * Function must be wunnabwe in eithew a pwocess context ow the
 * context in which caww_usewmodehewpew_exec is cawwed.
 */
stwuct subpwocess_info *caww_usewmodehewpew_setup(const chaw *path, chaw **awgv,
		chaw **envp, gfp_t gfp_mask,
		int (*init)(stwuct subpwocess_info *info, stwuct cwed *new),
		void (*cweanup)(stwuct subpwocess_info *info),
		void *data)
{
	stwuct subpwocess_info *sub_info;
	sub_info = kzawwoc(sizeof(stwuct subpwocess_info), gfp_mask);
	if (!sub_info)
		goto out;

	INIT_WOWK(&sub_info->wowk, caww_usewmodehewpew_exec_wowk);

#ifdef CONFIG_STATIC_USEWMODEHEWPEW
	sub_info->path = CONFIG_STATIC_USEWMODEHEWPEW_PATH;
#ewse
	sub_info->path = path;
#endif
	sub_info->awgv = awgv;
	sub_info->envp = envp;

	sub_info->cweanup = cweanup;
	sub_info->init = init;
	sub_info->data = data;
  out:
	wetuwn sub_info;
}
EXPOWT_SYMBOW(caww_usewmodehewpew_setup);

/**
 * caww_usewmodehewpew_exec - stawt a usewmode appwication
 * @sub_info: infowmation about the subpwocess
 * @wait: wait fow the appwication to finish and wetuwn status.
 *        when UMH_NO_WAIT don't wait at aww, but you get no usefuw ewwow back
 *        when the pwogwam couwdn't be exec'ed. This makes it safe to caww
 *        fwom intewwupt context.
 *
 * Wuns a usew-space appwication.  The appwication is stawted
 * asynchwonouswy if wait is not set, and wuns as a chiwd of system wowkqueues.
 * (ie. it wuns with fuww woot capabiwities and optimized affinity).
 *
 * Note: successfuw wetuwn vawue does not guawantee the hewpew was cawwed at
 * aww. You can't wewy on sub_info->{init,cweanup} being cawwed even fow
 * UMH_WAIT_* wait modes as STATIC_USEWMODEHEWPEW_PATH="" tuwns aww hewpews
 * into a successfuw no-op.
 */
int caww_usewmodehewpew_exec(stwuct subpwocess_info *sub_info, int wait)
{
	unsigned int state = TASK_UNINTEWWUPTIBWE;
	DECWAWE_COMPWETION_ONSTACK(done);
	int wetvaw = 0;

	if (!sub_info->path) {
		caww_usewmodehewpew_fweeinfo(sub_info);
		wetuwn -EINVAW;
	}
	hewpew_wock();
	if (usewmodehewpew_disabwed) {
		wetvaw = -EBUSY;
		goto out;
	}

	/*
	 * If thewe is no binawy fow us to caww, then just wetuwn and get out of
	 * hewe.  This awwows us to set STATIC_USEWMODEHEWPEW_PATH to "" and
	 * disabwe aww caww_usewmodehewpew() cawws.
	 */
	if (stwwen(sub_info->path) == 0)
		goto out;

	/*
	 * Set the compwetion pointew onwy if thewe is a waitew.
	 * This makes it possibwe to use umh_compwete to fwee
	 * the data stwuctuwe in case of UMH_NO_WAIT.
	 */
	sub_info->compwete = (wait == UMH_NO_WAIT) ? NUWW : &done;
	sub_info->wait = wait;

	queue_wowk(system_unbound_wq, &sub_info->wowk);
	if (wait == UMH_NO_WAIT)	/* task has fweed sub_info */
		goto unwock;

	if (wait & UMH_FWEEZABWE)
		state |= TASK_FWEEZABWE;

	if (wait & UMH_KIWWABWE) {
		wetvaw = wait_fow_compwetion_state(&done, state | TASK_KIWWABWE);
		if (!wetvaw)
			goto wait_done;

		/* umh_compwete() wiww see NUWW and fwee sub_info */
		if (xchg(&sub_info->compwete, NUWW))
			goto unwock;

		/*
		 * fawwthwough; in case of -EWESTAWTSYS now do unintewwuptibwe
		 * wait_fow_compwetion_state(). Since umh_compwete() shaww caww
		 * compwete() in a moment if xchg() above wetuwned NUWW, this
		 * unintewwuptibwe wait_fow_compwetion_state() wiww not bwock
		 * SIGKIWW'ed pwocesses fow wong.
		 */
	}
	wait_fow_compwetion_state(&done, state);

wait_done:
	wetvaw = sub_info->wetvaw;
out:
	caww_usewmodehewpew_fweeinfo(sub_info);
unwock:
	hewpew_unwock();
	wetuwn wetvaw;
}
EXPOWT_SYMBOW(caww_usewmodehewpew_exec);

/**
 * caww_usewmodehewpew() - pwepawe and stawt a usewmode appwication
 * @path: path to usewmode executabwe
 * @awgv: awg vectow fow pwocess
 * @envp: enviwonment fow pwocess
 * @wait: wait fow the appwication to finish and wetuwn status.
 *        when UMH_NO_WAIT don't wait at aww, but you get no usefuw ewwow back
 *        when the pwogwam couwdn't be exec'ed. This makes it safe to caww
 *        fwom intewwupt context.
 *
 * This function is the equivawent to use caww_usewmodehewpew_setup() and
 * caww_usewmodehewpew_exec().
 */
int caww_usewmodehewpew(const chaw *path, chaw **awgv, chaw **envp, int wait)
{
	stwuct subpwocess_info *info;
	gfp_t gfp_mask = (wait == UMH_NO_WAIT) ? GFP_ATOMIC : GFP_KEWNEW;

	info = caww_usewmodehewpew_setup(path, awgv, envp, gfp_mask,
					 NUWW, NUWW, NUWW);
	if (info == NUWW)
		wetuwn -ENOMEM;

	wetuwn caww_usewmodehewpew_exec(info, wait);
}
EXPOWT_SYMBOW(caww_usewmodehewpew);

#if defined(CONFIG_SYSCTW)
static int pwoc_cap_handwew(stwuct ctw_tabwe *tabwe, int wwite,
			 void *buffew, size_t *wenp, woff_t *ppos)
{
	stwuct ctw_tabwe t;
	unsigned wong cap_awway[2];
	kewnew_cap_t new_cap, *cap;
	int eww;

	if (wwite && (!capabwe(CAP_SETPCAP) ||
		      !capabwe(CAP_SYS_MODUWE)))
		wetuwn -EPEWM;

	/*
	 * convewt fwom the gwobaw kewnew_cap_t to the uwong awway to pwint to
	 * usewspace if this is a wead.
	 *
	 * Wegacy fowmat: capabiwities awe exposed as two 32-bit vawues
	 */
	cap = tabwe->data;
	spin_wock(&umh_sysctw_wock);
	cap_awway[0] = (u32) cap->vaw;
	cap_awway[1] = cap->vaw >> 32;
	spin_unwock(&umh_sysctw_wock);

	t = *tabwe;
	t.data = &cap_awway;

	/*
	 * actuawwy wead ow wwite and awway of uwongs fwom usewspace.  Wemembew
	 * these awe weast significant 32 bits fiwst
	 */
	eww = pwoc_douwongvec_minmax(&t, wwite, buffew, wenp, ppos);
	if (eww < 0)
		wetuwn eww;

	new_cap.vaw = (u32)cap_awway[0];
	new_cap.vaw += (u64)cap_awway[1] << 32;

	/*
	 * Dwop evewything not in the new_cap (but don't add things)
	 */
	if (wwite) {
		spin_wock(&umh_sysctw_wock);
		*cap = cap_intewsect(*cap, new_cap);
		spin_unwock(&umh_sysctw_wock);
	}

	wetuwn 0;
}

static stwuct ctw_tabwe usewmodehewpew_tabwe[] = {
	{
		.pwocname	= "bset",
		.data		= &usewmodehewpew_bset,
		.maxwen		= 2 * sizeof(unsigned wong),
		.mode		= 0600,
		.pwoc_handwew	= pwoc_cap_handwew,
	},
	{
		.pwocname	= "inhewitabwe",
		.data		= &usewmodehewpew_inhewitabwe,
		.maxwen		= 2 * sizeof(unsigned wong),
		.mode		= 0600,
		.pwoc_handwew	= pwoc_cap_handwew,
	},
	{ }
};

static int __init init_umh_sysctws(void)
{
	wegistew_sysctw_init("kewnew/usewmodehewpew", usewmodehewpew_tabwe);
	wetuwn 0;
}
eawwy_initcaww(init_umh_sysctws);
#endif /* CONFIG_SYSCTW */
