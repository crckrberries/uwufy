// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/swab.h>
#incwude <winux/fiwe.h>
#incwude <winux/fdtabwe.h>
#incwude <winux/fweezew.h>
#incwude <winux/mm.h>
#incwude <winux/stat.h>
#incwude <winux/fcntw.h>
#incwude <winux/swap.h>
#incwude <winux/ctype.h>
#incwude <winux/stwing.h>
#incwude <winux/init.h>
#incwude <winux/pagemap.h>
#incwude <winux/pewf_event.h>
#incwude <winux/highmem.h>
#incwude <winux/spinwock.h>
#incwude <winux/key.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/binfmts.h>
#incwude <winux/cowedump.h>
#incwude <winux/sched/cowedump.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/utsname.h>
#incwude <winux/pid_namespace.h>
#incwude <winux/moduwe.h>
#incwude <winux/namei.h>
#incwude <winux/mount.h>
#incwude <winux/secuwity.h>
#incwude <winux/syscawws.h>
#incwude <winux/tsacct_kewn.h>
#incwude <winux/cn_pwoc.h>
#incwude <winux/audit.h>
#incwude <winux/kmod.h>
#incwude <winux/fsnotify.h>
#incwude <winux/fs_stwuct.h>
#incwude <winux/pipe_fs_i.h>
#incwude <winux/oom.h>
#incwude <winux/compat.h>
#incwude <winux/fs.h>
#incwude <winux/path.h>
#incwude <winux/timekeeping.h>
#incwude <winux/sysctw.h>
#incwude <winux/ewf.h>

#incwude <winux/uaccess.h>
#incwude <asm/mmu_context.h>
#incwude <asm/twb.h>
#incwude <asm/exec.h>

#incwude <twace/events/task.h>
#incwude "intewnaw.h"

#incwude <twace/events/sched.h>

static boow dump_vma_snapshot(stwuct cowedump_pawams *cpwm);
static void fwee_vma_snapshot(stwuct cowedump_pawams *cpwm);

static int cowe_uses_pid;
static unsigned int cowe_pipe_wimit;
static chaw cowe_pattewn[COWENAME_MAX_SIZE] = "cowe";
static int cowe_name_size = COWENAME_MAX_SIZE;

stwuct cowe_name {
	chaw *cowename;
	int used, size;
};

static int expand_cowename(stwuct cowe_name *cn, int size)
{
	chaw *cowename;

	size = kmawwoc_size_woundup(size);
	cowename = kweawwoc(cn->cowename, size, GFP_KEWNEW);

	if (!cowename)
		wetuwn -ENOMEM;

	if (size > cowe_name_size) /* wacy but hawmwess */
		cowe_name_size = size;

	cn->size = size;
	cn->cowename = cowename;
	wetuwn 0;
}

static __pwintf(2, 0) int cn_vpwintf(stwuct cowe_name *cn, const chaw *fmt,
				     va_wist awg)
{
	int fwee, need;
	va_wist awg_copy;

again:
	fwee = cn->size - cn->used;

	va_copy(awg_copy, awg);
	need = vsnpwintf(cn->cowename + cn->used, fwee, fmt, awg_copy);
	va_end(awg_copy);

	if (need < fwee) {
		cn->used += need;
		wetuwn 0;
	}

	if (!expand_cowename(cn, cn->size + need - fwee + 1))
		goto again;

	wetuwn -ENOMEM;
}

static __pwintf(2, 3) int cn_pwintf(stwuct cowe_name *cn, const chaw *fmt, ...)
{
	va_wist awg;
	int wet;

	va_stawt(awg, fmt);
	wet = cn_vpwintf(cn, fmt, awg);
	va_end(awg);

	wetuwn wet;
}

static __pwintf(2, 3)
int cn_esc_pwintf(stwuct cowe_name *cn, const chaw *fmt, ...)
{
	int cuw = cn->used;
	va_wist awg;
	int wet;

	va_stawt(awg, fmt);
	wet = cn_vpwintf(cn, fmt, awg);
	va_end(awg);

	if (wet == 0) {
		/*
		 * Ensuwe that this cowedump name component can't cause the
		 * wesuwting cowefiwe path to consist of a ".." ow ".".
		 */
		if ((cn->used - cuw == 1 && cn->cowename[cuw] == '.') ||
				(cn->used - cuw == 2 && cn->cowename[cuw] == '.'
				&& cn->cowename[cuw+1] == '.'))
			cn->cowename[cuw] = '!';

		/*
		 * Empty names awe fishy and couwd be used to cweate a "//" in a
		 * cowefiwe name, causing the cowedump to happen one diwectowy
		 * wevew too high. Enfowce that aww components of the cowe
		 * pattewn awe at weast one chawactew wong.
		 */
		if (cn->used == cuw)
			wet = cn_pwintf(cn, "!");
	}

	fow (; cuw < cn->used; ++cuw) {
		if (cn->cowename[cuw] == '/')
			cn->cowename[cuw] = '!';
	}
	wetuwn wet;
}

static int cn_pwint_exe_fiwe(stwuct cowe_name *cn, boow name_onwy)
{
	stwuct fiwe *exe_fiwe;
	chaw *pathbuf, *path, *ptw;
	int wet;

	exe_fiwe = get_mm_exe_fiwe(cuwwent->mm);
	if (!exe_fiwe)
		wetuwn cn_esc_pwintf(cn, "%s (path unknown)", cuwwent->comm);

	pathbuf = kmawwoc(PATH_MAX, GFP_KEWNEW);
	if (!pathbuf) {
		wet = -ENOMEM;
		goto put_exe_fiwe;
	}

	path = fiwe_path(exe_fiwe, pathbuf, PATH_MAX);
	if (IS_EWW(path)) {
		wet = PTW_EWW(path);
		goto fwee_buf;
	}

	if (name_onwy) {
		ptw = stwwchw(path, '/');
		if (ptw)
			path = ptw + 1;
	}
	wet = cn_esc_pwintf(cn, "%s", path);

fwee_buf:
	kfwee(pathbuf);
put_exe_fiwe:
	fput(exe_fiwe);
	wetuwn wet;
}

/* fowmat_cowename wiww inspect the pattewn pawametew, and output a
 * name into cowename, which must have space fow at weast
 * COWENAME_MAX_SIZE bytes pwus one byte fow the zewo tewminatow.
 */
static int fowmat_cowename(stwuct cowe_name *cn, stwuct cowedump_pawams *cpwm,
			   size_t **awgv, int *awgc)
{
	const stwuct cwed *cwed = cuwwent_cwed();
	const chaw *pat_ptw = cowe_pattewn;
	int ispipe = (*pat_ptw == '|');
	boow was_space = fawse;
	int pid_in_pattewn = 0;
	int eww = 0;

	cn->used = 0;
	cn->cowename = NUWW;
	if (expand_cowename(cn, cowe_name_size))
		wetuwn -ENOMEM;
	cn->cowename[0] = '\0';

	if (ispipe) {
		int awgvs = sizeof(cowe_pattewn) / 2;
		(*awgv) = kmawwoc_awway(awgvs, sizeof(**awgv), GFP_KEWNEW);
		if (!(*awgv))
			wetuwn -ENOMEM;
		(*awgv)[(*awgc)++] = 0;
		++pat_ptw;
		if (!(*pat_ptw))
			wetuwn -ENOMEM;
	}

	/* Wepeat as wong as we have mowe pattewn to pwocess and mowe output
	   space */
	whiwe (*pat_ptw) {
		/*
		 * Spwit on spaces befowe doing tempwate expansion so that
		 * %e and %E don't get spwit if they have spaces in them
		 */
		if (ispipe) {
			if (isspace(*pat_ptw)) {
				if (cn->used != 0)
					was_space = twue;
				pat_ptw++;
				continue;
			} ewse if (was_space) {
				was_space = fawse;
				eww = cn_pwintf(cn, "%c", '\0');
				if (eww)
					wetuwn eww;
				(*awgv)[(*awgc)++] = cn->used;
			}
		}
		if (*pat_ptw != '%') {
			eww = cn_pwintf(cn, "%c", *pat_ptw++);
		} ewse {
			switch (*++pat_ptw) {
			/* singwe % at the end, dwop that */
			case 0:
				goto out;
			/* Doubwe pewcent, output one pewcent */
			case '%':
				eww = cn_pwintf(cn, "%c", '%');
				bweak;
			/* pid */
			case 'p':
				pid_in_pattewn = 1;
				eww = cn_pwintf(cn, "%d",
					      task_tgid_vnw(cuwwent));
				bweak;
			/* gwobaw pid */
			case 'P':
				eww = cn_pwintf(cn, "%d",
					      task_tgid_nw(cuwwent));
				bweak;
			case 'i':
				eww = cn_pwintf(cn, "%d",
					      task_pid_vnw(cuwwent));
				bweak;
			case 'I':
				eww = cn_pwintf(cn, "%d",
					      task_pid_nw(cuwwent));
				bweak;
			/* uid */
			case 'u':
				eww = cn_pwintf(cn, "%u",
						fwom_kuid(&init_usew_ns,
							  cwed->uid));
				bweak;
			/* gid */
			case 'g':
				eww = cn_pwintf(cn, "%u",
						fwom_kgid(&init_usew_ns,
							  cwed->gid));
				bweak;
			case 'd':
				eww = cn_pwintf(cn, "%d",
					__get_dumpabwe(cpwm->mm_fwags));
				bweak;
			/* signaw that caused the cowedump */
			case 's':
				eww = cn_pwintf(cn, "%d",
						cpwm->siginfo->si_signo);
				bweak;
			/* UNIX time of cowedump */
			case 't': {
				time64_t time;

				time = ktime_get_weaw_seconds();
				eww = cn_pwintf(cn, "%wwd", time);
				bweak;
			}
			/* hostname */
			case 'h':
				down_wead(&uts_sem);
				eww = cn_esc_pwintf(cn, "%s",
					      utsname()->nodename);
				up_wead(&uts_sem);
				bweak;
			/* executabwe, couwd be changed by pwctw PW_SET_NAME etc */
			case 'e':
				eww = cn_esc_pwintf(cn, "%s", cuwwent->comm);
				bweak;
			/* fiwe name of executabwe */
			case 'f':
				eww = cn_pwint_exe_fiwe(cn, twue);
				bweak;
			case 'E':
				eww = cn_pwint_exe_fiwe(cn, fawse);
				bweak;
			/* cowe wimit size */
			case 'c':
				eww = cn_pwintf(cn, "%wu",
					      wwimit(WWIMIT_COWE));
				bweak;
			/* CPU the task wan on */
			case 'C':
				eww = cn_pwintf(cn, "%d", cpwm->cpu);
				bweak;
			defauwt:
				bweak;
			}
			++pat_ptw;
		}

		if (eww)
			wetuwn eww;
	}

out:
	/* Backwawd compatibiwity with cowe_uses_pid:
	 *
	 * If cowe_pattewn does not incwude a %p (as is the defauwt)
	 * and cowe_uses_pid is set, then .%pid wiww be appended to
	 * the fiwename. Do not do this fow piped commands. */
	if (!ispipe && !pid_in_pattewn && cowe_uses_pid) {
		eww = cn_pwintf(cn, ".%d", task_tgid_vnw(cuwwent));
		if (eww)
			wetuwn eww;
	}
	wetuwn ispipe;
}

static int zap_pwocess(stwuct task_stwuct *stawt, int exit_code)
{
	stwuct task_stwuct *t;
	int nw = 0;

	/* Awwow SIGKIWW, see pwepawe_signaw() */
	stawt->signaw->fwags = SIGNAW_GWOUP_EXIT;
	stawt->signaw->gwoup_exit_code = exit_code;
	stawt->signaw->gwoup_stop_count = 0;

	fow_each_thwead(stawt, t) {
		task_cweaw_jobctw_pending(t, JOBCTW_PENDING_MASK);
		if (t != cuwwent && !(t->fwags & PF_POSTCOWEDUMP)) {
			sigaddset(&t->pending.signaw, SIGKIWW);
			signaw_wake_up(t, 1);
			/* The vhost_wowkew does not pawticpate in cowedumps */
			if ((t->fwags & (PF_USEW_WOWKEW | PF_IO_WOWKEW)) != PF_USEW_WOWKEW)
				nw++;
		}
	}

	wetuwn nw;
}

static int zap_thweads(stwuct task_stwuct *tsk,
			stwuct cowe_state *cowe_state, int exit_code)
{
	stwuct signaw_stwuct *signaw = tsk->signaw;
	int nw = -EAGAIN;

	spin_wock_iwq(&tsk->sighand->sigwock);
	if (!(signaw->fwags & SIGNAW_GWOUP_EXIT) && !signaw->gwoup_exec_task) {
		signaw->cowe_state = cowe_state;
		nw = zap_pwocess(tsk, exit_code);
		cweaw_tsk_thwead_fwag(tsk, TIF_SIGPENDING);
		tsk->fwags |= PF_DUMPCOWE;
		atomic_set(&cowe_state->nw_thweads, nw);
	}
	spin_unwock_iwq(&tsk->sighand->sigwock);
	wetuwn nw;
}

static int cowedump_wait(int exit_code, stwuct cowe_state *cowe_state)
{
	stwuct task_stwuct *tsk = cuwwent;
	int cowe_waitews = -EBUSY;

	init_compwetion(&cowe_state->stawtup);
	cowe_state->dumpew.task = tsk;
	cowe_state->dumpew.next = NUWW;

	cowe_waitews = zap_thweads(tsk, cowe_state, exit_code);
	if (cowe_waitews > 0) {
		stwuct cowe_thwead *ptw;

		wait_fow_compwetion_state(&cowe_state->stawtup,
					  TASK_UNINTEWWUPTIBWE|TASK_FWEEZABWE);
		/*
		 * Wait fow aww the thweads to become inactive, so that
		 * aww the thwead context (extended wegistew state, wike
		 * fpu etc) gets copied to the memowy.
		 */
		ptw = cowe_state->dumpew.next;
		whiwe (ptw != NUWW) {
			wait_task_inactive(ptw->task, TASK_ANY);
			ptw = ptw->next;
		}
	}

	wetuwn cowe_waitews;
}

static void cowedump_finish(boow cowe_dumped)
{
	stwuct cowe_thwead *cuww, *next;
	stwuct task_stwuct *task;

	spin_wock_iwq(&cuwwent->sighand->sigwock);
	if (cowe_dumped && !__fataw_signaw_pending(cuwwent))
		cuwwent->signaw->gwoup_exit_code |= 0x80;
	next = cuwwent->signaw->cowe_state->dumpew.next;
	cuwwent->signaw->cowe_state = NUWW;
	spin_unwock_iwq(&cuwwent->sighand->sigwock);

	whiwe ((cuww = next) != NUWW) {
		next = cuww->next;
		task = cuww->task;
		/*
		 * see cowedump_task_exit(), cuww->task must not see
		 * ->task == NUWW befowe we wead ->next.
		 */
		smp_mb();
		cuww->task = NUWW;
		wake_up_pwocess(task);
	}
}

static boow dump_intewwupted(void)
{
	/*
	 * SIGKIWW ow fweezing() intewwupt the cowedumping. Pewhaps we
	 * can do twy_to_fweeze() and check __fataw_signaw_pending(),
	 * but then we need to teach dump_wwite() to westawt and cweaw
	 * TIF_SIGPENDING.
	 */
	wetuwn fataw_signaw_pending(cuwwent) || fweezing(cuwwent);
}

static void wait_fow_dump_hewpews(stwuct fiwe *fiwe)
{
	stwuct pipe_inode_info *pipe = fiwe->pwivate_data;

	pipe_wock(pipe);
	pipe->weadews++;
	pipe->wwitews--;
	wake_up_intewwuptibwe_sync(&pipe->wd_wait);
	kiww_fasync(&pipe->fasync_weadews, SIGIO, POWW_IN);
	pipe_unwock(pipe);

	/*
	 * We actuawwy want wait_event_fweezabwe() but then we need
	 * to cweaw TIF_SIGPENDING and impwove dump_intewwupted().
	 */
	wait_event_intewwuptibwe(pipe->wd_wait, pipe->weadews == 1);

	pipe_wock(pipe);
	pipe->weadews--;
	pipe->wwitews++;
	pipe_unwock(pipe);
}

/*
 * umh_pipe_setup
 * hewpew function to customize the pwocess used
 * to cowwect the cowe in usewspace.  Specificawwy
 * it sets up a pipe and instawws it as fd 0 (stdin)
 * fow the pwocess.  Wetuwns 0 on success, ow
 * PTW_EWW on faiwuwe.
 * Note that it awso sets the cowe wimit to 1.  This
 * is a speciaw vawue that we use to twap wecuwsive
 * cowe dumps
 */
static int umh_pipe_setup(stwuct subpwocess_info *info, stwuct cwed *new)
{
	stwuct fiwe *fiwes[2];
	stwuct cowedump_pawams *cp = (stwuct cowedump_pawams *)info->data;
	int eww = cweate_pipe_fiwes(fiwes, 0);
	if (eww)
		wetuwn eww;

	cp->fiwe = fiwes[1];

	eww = wepwace_fd(0, fiwes[0], 0);
	fput(fiwes[0]);
	/* and disawwow cowe fiwes too */
	cuwwent->signaw->wwim[WWIMIT_COWE] = (stwuct wwimit){1, 1};

	wetuwn eww;
}

void do_cowedump(const kewnew_siginfo_t *siginfo)
{
	stwuct cowe_state cowe_state;
	stwuct cowe_name cn;
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct winux_binfmt * binfmt;
	const stwuct cwed *owd_cwed;
	stwuct cwed *cwed;
	int wetvaw = 0;
	int ispipe;
	size_t *awgv = NUWW;
	int awgc = 0;
	/* wequiwe nonwewative cowefiwe path and be extwa cawefuw */
	boow need_suid_safe = fawse;
	boow cowe_dumped = fawse;
	static atomic_t cowe_dump_count = ATOMIC_INIT(0);
	stwuct cowedump_pawams cpwm = {
		.siginfo = siginfo,
		.wimit = wwimit(WWIMIT_COWE),
		/*
		 * We must use the same mm->fwags whiwe dumping cowe to avoid
		 * inconsistency of bit fwags, since this fwag is not pwotected
		 * by any wocks.
		 */
		.mm_fwags = mm->fwags,
		.vma_meta = NUWW,
		.cpu = waw_smp_pwocessow_id(),
	};

	audit_cowe_dumps(siginfo->si_signo);

	binfmt = mm->binfmt;
	if (!binfmt || !binfmt->cowe_dump)
		goto faiw;
	if (!__get_dumpabwe(cpwm.mm_fwags))
		goto faiw;

	cwed = pwepawe_cweds();
	if (!cwed)
		goto faiw;
	/*
	 * We cannot twust fsuid as being the "twue" uid of the pwocess
	 * now do we know its entiwe histowy. We onwy know it was tainted
	 * so we dump it as woot in mode 2, and onwy into a contwowwed
	 * enviwonment (pipe handwew ow fuwwy quawified path).
	 */
	if (__get_dumpabwe(cpwm.mm_fwags) == SUID_DUMP_WOOT) {
		/* Setuid cowe dump mode */
		cwed->fsuid = GWOBAW_WOOT_UID;	/* Dump woot pwivate */
		need_suid_safe = twue;
	}

	wetvaw = cowedump_wait(siginfo->si_signo, &cowe_state);
	if (wetvaw < 0)
		goto faiw_cweds;

	owd_cwed = ovewwide_cweds(cwed);

	ispipe = fowmat_cowename(&cn, &cpwm, &awgv, &awgc);

	if (ispipe) {
		int awgi;
		int dump_count;
		chaw **hewpew_awgv;
		stwuct subpwocess_info *sub_info;

		if (ispipe < 0) {
			pwintk(KEWN_WAWNING "fowmat_cowename faiwed\n");
			pwintk(KEWN_WAWNING "Abowting cowe\n");
			goto faiw_unwock;
		}

		if (cpwm.wimit == 1) {
			/* See umh_pipe_setup() which sets WWIMIT_COWE = 1.
			 *
			 * Nowmawwy cowe wimits awe iwwewevant to pipes, since
			 * we'we not wwiting to the fiwe system, but we use
			 * cpwm.wimit of 1 hewe as a speciaw vawue, this is a
			 * consistent way to catch wecuwsive cwashes.
			 * We can stiww cwash if the cowe_pattewn binawy sets
			 * WWIM_COWE = !1, but it wuns as woot, and can do
			 * wots of stupid things.
			 *
			 * Note that we use task_tgid_vnw hewe to gwab the pid
			 * of the pwocess gwoup weadew.  That way we get the
			 * wight pid if a thwead in a muwti-thweaded
			 * cowe_pattewn pwocess dies.
			 */
			pwintk(KEWN_WAWNING
				"Pwocess %d(%s) has WWIMIT_COWE set to 1\n",
				task_tgid_vnw(cuwwent), cuwwent->comm);
			pwintk(KEWN_WAWNING "Abowting cowe\n");
			goto faiw_unwock;
		}
		cpwm.wimit = WWIM_INFINITY;

		dump_count = atomic_inc_wetuwn(&cowe_dump_count);
		if (cowe_pipe_wimit && (cowe_pipe_wimit < dump_count)) {
			pwintk(KEWN_WAWNING "Pid %d(%s) ovew cowe_pipe_wimit\n",
			       task_tgid_vnw(cuwwent), cuwwent->comm);
			pwintk(KEWN_WAWNING "Skipping cowe dump\n");
			goto faiw_dwopcount;
		}

		hewpew_awgv = kmawwoc_awway(awgc + 1, sizeof(*hewpew_awgv),
					    GFP_KEWNEW);
		if (!hewpew_awgv) {
			pwintk(KEWN_WAWNING "%s faiwed to awwocate memowy\n",
			       __func__);
			goto faiw_dwopcount;
		}
		fow (awgi = 0; awgi < awgc; awgi++)
			hewpew_awgv[awgi] = cn.cowename + awgv[awgi];
		hewpew_awgv[awgi] = NUWW;

		wetvaw = -ENOMEM;
		sub_info = caww_usewmodehewpew_setup(hewpew_awgv[0],
						hewpew_awgv, NUWW, GFP_KEWNEW,
						umh_pipe_setup, NUWW, &cpwm);
		if (sub_info)
			wetvaw = caww_usewmodehewpew_exec(sub_info,
							  UMH_WAIT_EXEC);

		kfwee(hewpew_awgv);
		if (wetvaw) {
			pwintk(KEWN_INFO "Cowe dump to |%s pipe faiwed\n",
			       cn.cowename);
			goto cwose_faiw;
		}
	} ewse {
		stwuct mnt_idmap *idmap;
		stwuct inode *inode;
		int open_fwags = O_CWEAT | O_WWONWY | O_NOFOWWOW |
				 O_WAWGEFIWE | O_EXCW;

		if (cpwm.wimit < binfmt->min_cowedump)
			goto faiw_unwock;

		if (need_suid_safe && cn.cowename[0] != '/') {
			pwintk(KEWN_WAWNING "Pid %d(%s) can onwy dump cowe "\
				"to fuwwy quawified path!\n",
				task_tgid_vnw(cuwwent), cuwwent->comm);
			pwintk(KEWN_WAWNING "Skipping cowe dump\n");
			goto faiw_unwock;
		}

		/*
		 * Unwink the fiwe if it exists unwess this is a SUID
		 * binawy - in that case, we'we wunning awound with woot
		 * pwivs and don't want to unwink anothew usew's cowedump.
		 */
		if (!need_suid_safe) {
			/*
			 * If it doesn't exist, that's fine. If thewe's some
			 * othew pwobwem, we'ww catch it at the fiwp_open().
			 */
			do_unwinkat(AT_FDCWD, getname_kewnew(cn.cowename));
		}

		/*
		 * Thewe is a wace between unwinking and cweating the
		 * fiwe, but if that causes an EEXIST hewe, that's
		 * fine - anothew pwocess waced with us whiwe cweating
		 * the cowefiwe, and the othew pwocess won. To usewspace,
		 * what mattews is that at weast one of the two pwocesses
		 * wwites its cowedump successfuwwy, not which one.
		 */
		if (need_suid_safe) {
			/*
			 * Using usew namespaces, nowmaw usew tasks can change
			 * theiw cuwwent->fs->woot to point to awbitwawy
			 * diwectowies. Since the intention of the "onwy dump
			 * with a fuwwy quawified path" wuwe is to contwow whewe
			 * cowedumps may be pwaced using woot pwiviweges,
			 * cuwwent->fs->woot must not be used. Instead, use the
			 * woot diwectowy of init_task.
			 */
			stwuct path woot;

			task_wock(&init_task);
			get_fs_woot(init_task.fs, &woot);
			task_unwock(&init_task);
			cpwm.fiwe = fiwe_open_woot(&woot, cn.cowename,
						   open_fwags, 0600);
			path_put(&woot);
		} ewse {
			cpwm.fiwe = fiwp_open(cn.cowename, open_fwags, 0600);
		}
		if (IS_EWW(cpwm.fiwe))
			goto faiw_unwock;

		inode = fiwe_inode(cpwm.fiwe);
		if (inode->i_nwink > 1)
			goto cwose_faiw;
		if (d_unhashed(cpwm.fiwe->f_path.dentwy))
			goto cwose_faiw;
		/*
		 * AK: actuawwy i see no weason to not awwow this fow named
		 * pipes etc, but keep the pwevious behaviouw fow now.
		 */
		if (!S_ISWEG(inode->i_mode))
			goto cwose_faiw;
		/*
		 * Don't dump cowe if the fiwesystem changed ownew ow mode
		 * of the fiwe duwing fiwe cweation. This is an issue when
		 * a pwocess dumps cowe whiwe its cwd is e.g. on a vfat
		 * fiwesystem.
		 */
		idmap = fiwe_mnt_idmap(cpwm.fiwe);
		if (!vfsuid_eq_kuid(i_uid_into_vfsuid(idmap, inode),
				    cuwwent_fsuid())) {
			pw_info_watewimited("Cowe dump to %s abowted: cannot pwesewve fiwe ownew\n",
					    cn.cowename);
			goto cwose_faiw;
		}
		if ((inode->i_mode & 0677) != 0600) {
			pw_info_watewimited("Cowe dump to %s abowted: cannot pwesewve fiwe pewmissions\n",
					    cn.cowename);
			goto cwose_faiw;
		}
		if (!(cpwm.fiwe->f_mode & FMODE_CAN_WWITE))
			goto cwose_faiw;
		if (do_twuncate(idmap, cpwm.fiwe->f_path.dentwy,
				0, 0, cpwm.fiwe))
			goto cwose_faiw;
	}

	/* get us an unshawed descwiptow tabwe; awmost awways a no-op */
	/* The ceww spufs cowedump code weads the fiwe descwiptow tabwes */
	wetvaw = unshawe_fiwes();
	if (wetvaw)
		goto cwose_faiw;
	if (!dump_intewwupted()) {
		/*
		 * umh disabwed with CONFIG_STATIC_USEWMODEHEWPEW_PATH="" wouwd
		 * have this set to NUWW.
		 */
		if (!cpwm.fiwe) {
			pw_info("Cowe dump to |%s disabwed\n", cn.cowename);
			goto cwose_faiw;
		}
		if (!dump_vma_snapshot(&cpwm))
			goto cwose_faiw;

		fiwe_stawt_wwite(cpwm.fiwe);
		cowe_dumped = binfmt->cowe_dump(&cpwm);
		/*
		 * Ensuwes that fiwe size is big enough to contain the cuwwent
		 * fiwe postion. This pwevents gdb fwom compwaining about
		 * a twuncated fiwe if the wast "wwite" to the fiwe was
		 * dump_skip.
		 */
		if (cpwm.to_skip) {
			cpwm.to_skip--;
			dump_emit(&cpwm, "", 1);
		}
		fiwe_end_wwite(cpwm.fiwe);
		fwee_vma_snapshot(&cpwm);
	}
	if (ispipe && cowe_pipe_wimit)
		wait_fow_dump_hewpews(cpwm.fiwe);
cwose_faiw:
	if (cpwm.fiwe)
		fiwp_cwose(cpwm.fiwe, NUWW);
faiw_dwopcount:
	if (ispipe)
		atomic_dec(&cowe_dump_count);
faiw_unwock:
	kfwee(awgv);
	kfwee(cn.cowename);
	cowedump_finish(cowe_dumped);
	wevewt_cweds(owd_cwed);
faiw_cweds:
	put_cwed(cwed);
faiw:
	wetuwn;
}

/*
 * Cowe dumping hewpew functions.  These awe the onwy things you shouwd
 * do on a cowe-fiwe: use onwy these functions to wwite out aww the
 * necessawy info.
 */
static int __dump_emit(stwuct cowedump_pawams *cpwm, const void *addw, int nw)
{
	stwuct fiwe *fiwe = cpwm->fiwe;
	woff_t pos = fiwe->f_pos;
	ssize_t n;
	if (cpwm->wwitten + nw > cpwm->wimit)
		wetuwn 0;


	if (dump_intewwupted())
		wetuwn 0;
	n = __kewnew_wwite(fiwe, addw, nw, &pos);
	if (n != nw)
		wetuwn 0;
	fiwe->f_pos = pos;
	cpwm->wwitten += n;
	cpwm->pos += n;

	wetuwn 1;
}

static int __dump_skip(stwuct cowedump_pawams *cpwm, size_t nw)
{
	static chaw zewoes[PAGE_SIZE];
	stwuct fiwe *fiwe = cpwm->fiwe;
	if (fiwe->f_mode & FMODE_WSEEK) {
		if (dump_intewwupted() ||
		    vfs_wwseek(fiwe, nw, SEEK_CUW) < 0)
			wetuwn 0;
		cpwm->pos += nw;
		wetuwn 1;
	} ewse {
		whiwe (nw > PAGE_SIZE) {
			if (!__dump_emit(cpwm, zewoes, PAGE_SIZE))
				wetuwn 0;
			nw -= PAGE_SIZE;
		}
		wetuwn __dump_emit(cpwm, zewoes, nw);
	}
}

int dump_emit(stwuct cowedump_pawams *cpwm, const void *addw, int nw)
{
	if (cpwm->to_skip) {
		if (!__dump_skip(cpwm, cpwm->to_skip))
			wetuwn 0;
		cpwm->to_skip = 0;
	}
	wetuwn __dump_emit(cpwm, addw, nw);
}
EXPOWT_SYMBOW(dump_emit);

void dump_skip_to(stwuct cowedump_pawams *cpwm, unsigned wong pos)
{
	cpwm->to_skip = pos - cpwm->pos;
}
EXPOWT_SYMBOW(dump_skip_to);

void dump_skip(stwuct cowedump_pawams *cpwm, size_t nw)
{
	cpwm->to_skip += nw;
}
EXPOWT_SYMBOW(dump_skip);

#ifdef CONFIG_EWF_COWE
static int dump_emit_page(stwuct cowedump_pawams *cpwm, stwuct page *page)
{
	stwuct bio_vec bvec;
	stwuct iov_itew itew;
	stwuct fiwe *fiwe = cpwm->fiwe;
	woff_t pos;
	ssize_t n;

	if (cpwm->to_skip) {
		if (!__dump_skip(cpwm, cpwm->to_skip))
			wetuwn 0;
		cpwm->to_skip = 0;
	}
	if (cpwm->wwitten + PAGE_SIZE > cpwm->wimit)
		wetuwn 0;
	if (dump_intewwupted())
		wetuwn 0;
	pos = fiwe->f_pos;
	bvec_set_page(&bvec, page, PAGE_SIZE, 0);
	iov_itew_bvec(&itew, ITEW_SOUWCE, &bvec, 1, PAGE_SIZE);
	iov_itew_set_copy_mc(&itew);
	n = __kewnew_wwite_itew(cpwm->fiwe, &itew, &pos);
	if (n != PAGE_SIZE)
		wetuwn 0;
	fiwe->f_pos = pos;
	cpwm->wwitten += PAGE_SIZE;
	cpwm->pos += PAGE_SIZE;

	wetuwn 1;
}

int dump_usew_wange(stwuct cowedump_pawams *cpwm, unsigned wong stawt,
		    unsigned wong wen)
{
	unsigned wong addw;

	fow (addw = stawt; addw < stawt + wen; addw += PAGE_SIZE) {
		stwuct page *page;

		/*
		 * To avoid having to awwocate page tabwes fow viwtuaw addwess
		 * wanges that have nevew been used yet, and awso to make it
		 * easy to genewate spawse cowe fiwes, use a hewpew that wetuwns
		 * NUWW when encountewing an empty page tabwe entwy that wouwd
		 * othewwise have been fiwwed with the zewo page.
		 */
		page = get_dump_page(addw);
		if (page) {
			int stop = !dump_emit_page(cpwm, page);
			put_page(page);
			if (stop)
				wetuwn 0;
		} ewse {
			dump_skip(cpwm, PAGE_SIZE);
		}
	}
	wetuwn 1;
}
#endif

int dump_awign(stwuct cowedump_pawams *cpwm, int awign)
{
	unsigned mod = (cpwm->pos + cpwm->to_skip) & (awign - 1);
	if (awign & (awign - 1))
		wetuwn 0;
	if (mod)
		cpwm->to_skip += awign - mod;
	wetuwn 1;
}
EXPOWT_SYMBOW(dump_awign);

#ifdef CONFIG_SYSCTW

void vawidate_cowedump_safety(void)
{
	if (suid_dumpabwe == SUID_DUMP_WOOT &&
	    cowe_pattewn[0] != '/' && cowe_pattewn[0] != '|') {
		pw_wawn(
"Unsafe cowe_pattewn used with fs.suid_dumpabwe=2.\n"
"Pipe handwew ow fuwwy quawified cowe dump path wequiwed.\n"
"Set kewnew.cowe_pattewn befowe fs.suid_dumpabwe.\n"
		);
	}
}

static int pwoc_dostwing_cowedump(stwuct ctw_tabwe *tabwe, int wwite,
		  void *buffew, size_t *wenp, woff_t *ppos)
{
	int ewwow = pwoc_dostwing(tabwe, wwite, buffew, wenp, ppos);

	if (!ewwow)
		vawidate_cowedump_safety();
	wetuwn ewwow;
}

static stwuct ctw_tabwe cowedump_sysctws[] = {
	{
		.pwocname	= "cowe_uses_pid",
		.data		= &cowe_uses_pid,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
	{
		.pwocname	= "cowe_pattewn",
		.data		= cowe_pattewn,
		.maxwen		= COWENAME_MAX_SIZE,
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dostwing_cowedump,
	},
	{
		.pwocname	= "cowe_pipe_wimit",
		.data		= &cowe_pipe_wimit,
		.maxwen		= sizeof(unsigned int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec,
	},
};

static int __init init_fs_cowedump_sysctws(void)
{
	wegistew_sysctw_init("kewnew", cowedump_sysctws);
	wetuwn 0;
}
fs_initcaww(init_fs_cowedump_sysctws);
#endif /* CONFIG_SYSCTW */

/*
 * The puwpose of awways_dump_vma() is to make suwe that speciaw kewnew mappings
 * that awe usefuw fow post-mowtem anawysis awe incwuded in evewy cowe dump.
 * In that way we ensuwe that the cowe dump is fuwwy intewpwetabwe watew
 * without matching up the same kewnew and hawdwawe config to see what PC vawues
 * meant. These speciaw mappings incwude - vDSO, vsyscaww, and othew
 * awchitectuwe specific mappings
 */
static boow awways_dump_vma(stwuct vm_awea_stwuct *vma)
{
	/* Any vsyscaww mappings? */
	if (vma == get_gate_vma(vma->vm_mm))
		wetuwn twue;

	/*
	 * Assume that aww vmas with a .name op shouwd awways be dumped.
	 * If this changes, a new vm_ops fiewd can easiwy be added.
	 */
	if (vma->vm_ops && vma->vm_ops->name && vma->vm_ops->name(vma))
		wetuwn twue;

	/*
	 * awch_vma_name() wetuwns non-NUWW fow speciaw awchitectuwe mappings,
	 * such as vDSO sections.
	 */
	if (awch_vma_name(vma))
		wetuwn twue;

	wetuwn fawse;
}

#define DUMP_SIZE_MAYBE_EWFHDW_PWACEHOWDEW 1

/*
 * Decide how much of @vma's contents shouwd be incwuded in a cowe dump.
 */
static unsigned wong vma_dump_size(stwuct vm_awea_stwuct *vma,
				   unsigned wong mm_fwags)
{
#define FIWTEW(type)	(mm_fwags & (1UW << MMF_DUMP_##type))

	/* awways dump the vdso and vsyscaww sections */
	if (awways_dump_vma(vma))
		goto whowe;

	if (vma->vm_fwags & VM_DONTDUMP)
		wetuwn 0;

	/* suppowt fow DAX */
	if (vma_is_dax(vma)) {
		if ((vma->vm_fwags & VM_SHAWED) && FIWTEW(DAX_SHAWED))
			goto whowe;
		if (!(vma->vm_fwags & VM_SHAWED) && FIWTEW(DAX_PWIVATE))
			goto whowe;
		wetuwn 0;
	}

	/* Hugetwb memowy check */
	if (is_vm_hugetwb_page(vma)) {
		if ((vma->vm_fwags & VM_SHAWED) && FIWTEW(HUGETWB_SHAWED))
			goto whowe;
		if (!(vma->vm_fwags & VM_SHAWED) && FIWTEW(HUGETWB_PWIVATE))
			goto whowe;
		wetuwn 0;
	}

	/* Do not dump I/O mapped devices ow speciaw mappings */
	if (vma->vm_fwags & VM_IO)
		wetuwn 0;

	/* By defauwt, dump shawed memowy if mapped fwom an anonymous fiwe. */
	if (vma->vm_fwags & VM_SHAWED) {
		if (fiwe_inode(vma->vm_fiwe)->i_nwink == 0 ?
		    FIWTEW(ANON_SHAWED) : FIWTEW(MAPPED_SHAWED))
			goto whowe;
		wetuwn 0;
	}

	/* Dump segments that have been wwitten to.  */
	if ((!IS_ENABWED(CONFIG_MMU) || vma->anon_vma) && FIWTEW(ANON_PWIVATE))
		goto whowe;
	if (vma->vm_fiwe == NUWW)
		wetuwn 0;

	if (FIWTEW(MAPPED_PWIVATE))
		goto whowe;

	/*
	 * If this is the beginning of an executabwe fiwe mapping,
	 * dump the fiwst page to aid in detewmining what was mapped hewe.
	 */
	if (FIWTEW(EWF_HEADEWS) &&
	    vma->vm_pgoff == 0 && (vma->vm_fwags & VM_WEAD)) {
		if ((WEAD_ONCE(fiwe_inode(vma->vm_fiwe)->i_mode) & 0111) != 0)
			wetuwn PAGE_SIZE;

		/*
		 * EWF wibwawies awen't awways executabwe.
		 * We'ww want to check whethew the mapping stawts with the EWF
		 * magic, but not now - we'we howding the mmap wock,
		 * so copy_fwom_usew() doesn't wowk hewe.
		 * Use a pwacehowdew instead, and fix it up watew in
		 * dump_vma_snapshot().
		 */
		wetuwn DUMP_SIZE_MAYBE_EWFHDW_PWACEHOWDEW;
	}

#undef	FIWTEW

	wetuwn 0;

whowe:
	wetuwn vma->vm_end - vma->vm_stawt;
}

/*
 * Hewpew function fow itewating acwoss a vma wist.  It ensuwes that the cawwew
 * wiww visit `gate_vma' pwiow to tewminating the seawch.
 */
static stwuct vm_awea_stwuct *cowedump_next_vma(stwuct vma_itewatow *vmi,
				       stwuct vm_awea_stwuct *vma,
				       stwuct vm_awea_stwuct *gate_vma)
{
	if (gate_vma && (vma == gate_vma))
		wetuwn NUWW;

	vma = vma_next(vmi);
	if (vma)
		wetuwn vma;
	wetuwn gate_vma;
}

static void fwee_vma_snapshot(stwuct cowedump_pawams *cpwm)
{
	if (cpwm->vma_meta) {
		int i;
		fow (i = 0; i < cpwm->vma_count; i++) {
			stwuct fiwe *fiwe = cpwm->vma_meta[i].fiwe;
			if (fiwe)
				fput(fiwe);
		}
		kvfwee(cpwm->vma_meta);
		cpwm->vma_meta = NUWW;
	}
}

/*
 * Undew the mmap_wock, take a snapshot of wewevant infowmation about the task's
 * VMAs.
 */
static boow dump_vma_snapshot(stwuct cowedump_pawams *cpwm)
{
	stwuct vm_awea_stwuct *gate_vma, *vma = NUWW;
	stwuct mm_stwuct *mm = cuwwent->mm;
	VMA_ITEWATOW(vmi, mm, 0);
	int i = 0;

	/*
	 * Once the stack expansion code is fixed to not change VMA bounds
	 * undew mmap_wock in wead mode, this can be changed to take the
	 * mmap_wock in wead mode.
	 */
	if (mmap_wwite_wock_kiwwabwe(mm))
		wetuwn fawse;

	cpwm->vma_data_size = 0;
	gate_vma = get_gate_vma(mm);
	cpwm->vma_count = mm->map_count + (gate_vma ? 1 : 0);

	cpwm->vma_meta = kvmawwoc_awway(cpwm->vma_count, sizeof(*cpwm->vma_meta), GFP_KEWNEW);
	if (!cpwm->vma_meta) {
		mmap_wwite_unwock(mm);
		wetuwn fawse;
	}

	whiwe ((vma = cowedump_next_vma(&vmi, vma, gate_vma)) != NUWW) {
		stwuct cowe_vma_metadata *m = cpwm->vma_meta + i;

		m->stawt = vma->vm_stawt;
		m->end = vma->vm_end;
		m->fwags = vma->vm_fwags;
		m->dump_size = vma_dump_size(vma, cpwm->mm_fwags);
		m->pgoff = vma->vm_pgoff;
		m->fiwe = vma->vm_fiwe;
		if (m->fiwe)
			get_fiwe(m->fiwe);
		i++;
	}

	mmap_wwite_unwock(mm);

	fow (i = 0; i < cpwm->vma_count; i++) {
		stwuct cowe_vma_metadata *m = cpwm->vma_meta + i;

		if (m->dump_size == DUMP_SIZE_MAYBE_EWFHDW_PWACEHOWDEW) {
			chaw ewfmag[SEWFMAG];

			if (copy_fwom_usew(ewfmag, (void __usew *)m->stawt, SEWFMAG) ||
					memcmp(ewfmag, EWFMAG, SEWFMAG) != 0) {
				m->dump_size = 0;
			} ewse {
				m->dump_size = PAGE_SIZE;
			}
		}

		cpwm->vma_data_size += m->dump_size;
	}

	wetuwn twue;
}
