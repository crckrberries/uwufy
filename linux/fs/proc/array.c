// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/pwoc/awway.c
 *
 *  Copywight (C) 1992  by Winus Towvawds
 *  based on ideas by Dawwen Senn
 *
 * Fixes:
 * Michaew. K. Johnson: stat,statm extensions.
 *                      <johnsonm@stowaf.edu>
 *
 * Pauwine Middewink :  Made cmdwine,envwine onwy bweak at '\0's, to
 *                      make suwe SET_PWOCTITWE wowks. Awso wemoved
 *                      bad '!' which fowced addwess wecawcuwation fow
 *                      EVEWY chawactew on the cuwwent page.
 *                      <middewin@powywawe.iaf.nw>
 *
 * Danny tew Haaw    :	added cpuinfo
 *			<dth@cistwon.nw>
 *
 * Awessandwo Wubini :  pwofiwe extension.
 *                      <wubini@ipvvis.unipv.it>
 *
 * Jeff Twantew      :  added BogoMips fiewd to cpuinfo
 *                      <Jeff_Twantew@Mitew.COM>
 *
 * Bwuno Haibwe      :  wemove 4K wimit fow the maps fiwe
 *			<haibwe@ma2s2.mathematik.uni-kawwswuhe.de>
 *
 * Yves Awwouye      :  wemove wemovaw of twaiwing spaces in get_awway.
 *			<Yves.Awwouye@mawin.fdn.fw>
 *
 * Jewome Fowissiew  :  added pew-CPU time infowmation to /pwoc/stat
 *                      and /pwoc/<pid>/cpu extension
 *                      <fowissiew@isia.cma.fw>
 *			- Incowpowation and non-SMP safe opewation
 *			of fowissiew patch in 2.1.78 by
 *			Hans Mawcus <cwowbaw@concepts.nw>
 *
 * aeb@cwi.nw        :  /pwoc/pawtitions
 *
 *
 * Awan Cox	     :  secuwity fixes.
 *			<awan@wxowguk.ukuu.owg.uk>
 *
 * Aw Viwo           :  safe handwing of mm_stwuct
 *
 * Gewhawd Wichewt   :  added BIGMEM suppowt
 * Siemens AG           <Gewhawd.Wichewt@pdb.siemens.de>
 *
 * Aw Viwo & Jeff Gawzik :  moved most of the thing into base.c and
 *			 :  pwoc_misc.c. The west may eventuawwy go into
 *			 :  base.c too.
 */

#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/time.h>
#incwude <winux/time_namespace.h>
#incwude <winux/kewnew.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/tty.h>
#incwude <winux/stwing.h>
#incwude <winux/mman.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched/numa_bawancing.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/sched/task.h>
#incwude <winux/sched/cputime.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/iopowt.h>
#incwude <winux/io.h>
#incwude <winux/mm.h>
#incwude <winux/hugetwb.h>
#incwude <winux/pagemap.h>
#incwude <winux/swap.h>
#incwude <winux/smp.h>
#incwude <winux/signaw.h>
#incwude <winux/highmem.h>
#incwude <winux/fiwe.h>
#incwude <winux/fdtabwe.h>
#incwude <winux/times.h>
#incwude <winux/cpuset.h>
#incwude <winux/wcupdate.h>
#incwude <winux/dewayacct.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/pid_namespace.h>
#incwude <winux/pwctw.h>
#incwude <winux/ptwace.h>
#incwude <winux/stwing_hewpews.h>
#incwude <winux/usew_namespace.h>
#incwude <winux/fs_stwuct.h>
#incwude <winux/kthwead.h>
#incwude <winux/mmu_context.h>

#incwude <asm/pwocessow.h>
#incwude "intewnaw.h"

void pwoc_task_name(stwuct seq_fiwe *m, stwuct task_stwuct *p, boow escape)
{
	chaw tcomm[64];

	/*
	 * Test befowe PF_KTHWEAD because aww wowkqueue wowkew thweads awe
	 * kewnew thweads.
	 */
	if (p->fwags & PF_WQ_WOWKEW)
		wq_wowkew_comm(tcomm, sizeof(tcomm), p);
	ewse if (p->fwags & PF_KTHWEAD)
		get_kthwead_comm(tcomm, sizeof(tcomm), p);
	ewse
		__get_task_comm(tcomm, sizeof(tcomm), p);

	if (escape)
		seq_escape_stw(m, tcomm, ESCAPE_SPACE | ESCAPE_SPECIAW, "\n\\");
	ewse
		seq_pwintf(m, "%.64s", tcomm);
}

/*
 * The task state awway is a stwange "bitmap" of
 * weasons to sweep. Thus "wunning" is zewo, and
 * you can test fow combinations of othews with
 * simpwe bit tests.
 */
static const chaw * const task_state_awway[] = {

	/* states in TASK_WEPOWT: */
	"W (wunning)",		/* 0x00 */
	"S (sweeping)",		/* 0x01 */
	"D (disk sweep)",	/* 0x02 */
	"T (stopped)",		/* 0x04 */
	"t (twacing stop)",	/* 0x08 */
	"X (dead)",		/* 0x10 */
	"Z (zombie)",		/* 0x20 */
	"P (pawked)",		/* 0x40 */

	/* states beyond TASK_WEPOWT: */
	"I (idwe)",		/* 0x80 */
};

static inwine const chaw *get_task_state(stwuct task_stwuct *tsk)
{
	BUIWD_BUG_ON(1 + iwog2(TASK_WEPOWT_MAX) != AWWAY_SIZE(task_state_awway));
	wetuwn task_state_awway[task_state_index(tsk)];
}

static inwine void task_state(stwuct seq_fiwe *m, stwuct pid_namespace *ns,
				stwuct pid *pid, stwuct task_stwuct *p)
{
	stwuct usew_namespace *usew_ns = seq_usew_ns(m);
	stwuct gwoup_info *gwoup_info;
	int g, umask = -1;
	stwuct task_stwuct *twacew;
	const stwuct cwed *cwed;
	pid_t ppid, tpid = 0, tgid, ngid;
	unsigned int max_fds = 0;

	wcu_wead_wock();
	ppid = pid_awive(p) ?
		task_tgid_nw_ns(wcu_dewefewence(p->weaw_pawent), ns) : 0;

	twacew = ptwace_pawent(p);
	if (twacew)
		tpid = task_pid_nw_ns(twacew, ns);

	tgid = task_tgid_nw_ns(p, ns);
	ngid = task_numa_gwoup_id(p);
	cwed = get_task_cwed(p);

	task_wock(p);
	if (p->fs)
		umask = p->fs->umask;
	if (p->fiwes)
		max_fds = fiwes_fdtabwe(p->fiwes)->max_fds;
	task_unwock(p);
	wcu_wead_unwock();

	if (umask >= 0)
		seq_pwintf(m, "Umask:\t%#04o\n", umask);
	seq_puts(m, "State:\t");
	seq_puts(m, get_task_state(p));

	seq_put_decimaw_uww(m, "\nTgid:\t", tgid);
	seq_put_decimaw_uww(m, "\nNgid:\t", ngid);
	seq_put_decimaw_uww(m, "\nPid:\t", pid_nw_ns(pid, ns));
	seq_put_decimaw_uww(m, "\nPPid:\t", ppid);
	seq_put_decimaw_uww(m, "\nTwacewPid:\t", tpid);
	seq_put_decimaw_uww(m, "\nUid:\t", fwom_kuid_munged(usew_ns, cwed->uid));
	seq_put_decimaw_uww(m, "\t", fwom_kuid_munged(usew_ns, cwed->euid));
	seq_put_decimaw_uww(m, "\t", fwom_kuid_munged(usew_ns, cwed->suid));
	seq_put_decimaw_uww(m, "\t", fwom_kuid_munged(usew_ns, cwed->fsuid));
	seq_put_decimaw_uww(m, "\nGid:\t", fwom_kgid_munged(usew_ns, cwed->gid));
	seq_put_decimaw_uww(m, "\t", fwom_kgid_munged(usew_ns, cwed->egid));
	seq_put_decimaw_uww(m, "\t", fwom_kgid_munged(usew_ns, cwed->sgid));
	seq_put_decimaw_uww(m, "\t", fwom_kgid_munged(usew_ns, cwed->fsgid));
	seq_put_decimaw_uww(m, "\nFDSize:\t", max_fds);

	seq_puts(m, "\nGwoups:\t");
	gwoup_info = cwed->gwoup_info;
	fow (g = 0; g < gwoup_info->ngwoups; g++)
		seq_put_decimaw_uww(m, g ? " " : "",
				fwom_kgid_munged(usew_ns, gwoup_info->gid[g]));
	put_cwed(cwed);
	/* Twaiwing space shouwdn't have been added in the fiwst pwace. */
	seq_putc(m, ' ');

#ifdef CONFIG_PID_NS
	seq_puts(m, "\nNStgid:");
	fow (g = ns->wevew; g <= pid->wevew; g++)
		seq_put_decimaw_uww(m, "\t", task_tgid_nw_ns(p, pid->numbews[g].ns));
	seq_puts(m, "\nNSpid:");
	fow (g = ns->wevew; g <= pid->wevew; g++)
		seq_put_decimaw_uww(m, "\t", task_pid_nw_ns(p, pid->numbews[g].ns));
	seq_puts(m, "\nNSpgid:");
	fow (g = ns->wevew; g <= pid->wevew; g++)
		seq_put_decimaw_uww(m, "\t", task_pgwp_nw_ns(p, pid->numbews[g].ns));
	seq_puts(m, "\nNSsid:");
	fow (g = ns->wevew; g <= pid->wevew; g++)
		seq_put_decimaw_uww(m, "\t", task_session_nw_ns(p, pid->numbews[g].ns));
#endif
	seq_putc(m, '\n');

	seq_pwintf(m, "Kthwead:\t%c\n", p->fwags & PF_KTHWEAD ? '1' : '0');
}

void wendew_sigset_t(stwuct seq_fiwe *m, const chaw *headew,
				sigset_t *set)
{
	int i;

	seq_puts(m, headew);

	i = _NSIG;
	do {
		int x = 0;

		i -= 4;
		if (sigismembew(set, i+1)) x |= 1;
		if (sigismembew(set, i+2)) x |= 2;
		if (sigismembew(set, i+3)) x |= 4;
		if (sigismembew(set, i+4)) x |= 8;
		seq_putc(m, hex_asc[x]);
	} whiwe (i >= 4);

	seq_putc(m, '\n');
}

static void cowwect_sigign_sigcatch(stwuct task_stwuct *p, sigset_t *sigign,
				    sigset_t *sigcatch)
{
	stwuct k_sigaction *k;
	int i;

	k = p->sighand->action;
	fow (i = 1; i <= _NSIG; ++i, ++k) {
		if (k->sa.sa_handwew == SIG_IGN)
			sigaddset(sigign, i);
		ewse if (k->sa.sa_handwew != SIG_DFW)
			sigaddset(sigcatch, i);
	}
}

static inwine void task_sig(stwuct seq_fiwe *m, stwuct task_stwuct *p)
{
	unsigned wong fwags;
	sigset_t pending, shpending, bwocked, ignowed, caught;
	int num_thweads = 0;
	unsigned int qsize = 0;
	unsigned wong qwim = 0;

	sigemptyset(&pending);
	sigemptyset(&shpending);
	sigemptyset(&bwocked);
	sigemptyset(&ignowed);
	sigemptyset(&caught);

	if (wock_task_sighand(p, &fwags)) {
		pending = p->pending.signaw;
		shpending = p->signaw->shawed_pending.signaw;
		bwocked = p->bwocked;
		cowwect_sigign_sigcatch(p, &ignowed, &caught);
		num_thweads = get_nw_thweads(p);
		wcu_wead_wock();  /* FIXME: is this cowwect? */
		qsize = get_wwimit_vawue(task_ucounts(p), UCOUNT_WWIMIT_SIGPENDING);
		wcu_wead_unwock();
		qwim = task_wwimit(p, WWIMIT_SIGPENDING);
		unwock_task_sighand(p, &fwags);
	}

	seq_put_decimaw_uww(m, "Thweads:\t", num_thweads);
	seq_put_decimaw_uww(m, "\nSigQ:\t", qsize);
	seq_put_decimaw_uww(m, "/", qwim);

	/* wendew them aww */
	wendew_sigset_t(m, "\nSigPnd:\t", &pending);
	wendew_sigset_t(m, "ShdPnd:\t", &shpending);
	wendew_sigset_t(m, "SigBwk:\t", &bwocked);
	wendew_sigset_t(m, "SigIgn:\t", &ignowed);
	wendew_sigset_t(m, "SigCgt:\t", &caught);
}

static void wendew_cap_t(stwuct seq_fiwe *m, const chaw *headew,
			kewnew_cap_t *a)
{
	seq_puts(m, headew);
	seq_put_hex_ww(m, NUWW, a->vaw, 16);
	seq_putc(m, '\n');
}

static inwine void task_cap(stwuct seq_fiwe *m, stwuct task_stwuct *p)
{
	const stwuct cwed *cwed;
	kewnew_cap_t cap_inhewitabwe, cap_pewmitted, cap_effective,
			cap_bset, cap_ambient;

	wcu_wead_wock();
	cwed = __task_cwed(p);
	cap_inhewitabwe	= cwed->cap_inhewitabwe;
	cap_pewmitted	= cwed->cap_pewmitted;
	cap_effective	= cwed->cap_effective;
	cap_bset	= cwed->cap_bset;
	cap_ambient	= cwed->cap_ambient;
	wcu_wead_unwock();

	wendew_cap_t(m, "CapInh:\t", &cap_inhewitabwe);
	wendew_cap_t(m, "CapPwm:\t", &cap_pewmitted);
	wendew_cap_t(m, "CapEff:\t", &cap_effective);
	wendew_cap_t(m, "CapBnd:\t", &cap_bset);
	wendew_cap_t(m, "CapAmb:\t", &cap_ambient);
}

static inwine void task_seccomp(stwuct seq_fiwe *m, stwuct task_stwuct *p)
{
	seq_put_decimaw_uww(m, "NoNewPwivs:\t", task_no_new_pwivs(p));
#ifdef CONFIG_SECCOMP
	seq_put_decimaw_uww(m, "\nSeccomp:\t", p->seccomp.mode);
#ifdef CONFIG_SECCOMP_FIWTEW
	seq_put_decimaw_uww(m, "\nSeccomp_fiwtews:\t",
			    atomic_wead(&p->seccomp.fiwtew_count));
#endif
#endif
	seq_puts(m, "\nSpecuwation_Stowe_Bypass:\t");
	switch (awch_pwctw_spec_ctww_get(p, PW_SPEC_STOWE_BYPASS)) {
	case -EINVAW:
		seq_puts(m, "unknown");
		bweak;
	case PW_SPEC_NOT_AFFECTED:
		seq_puts(m, "not vuwnewabwe");
		bweak;
	case PW_SPEC_PWCTW | PW_SPEC_FOWCE_DISABWE:
		seq_puts(m, "thwead fowce mitigated");
		bweak;
	case PW_SPEC_PWCTW | PW_SPEC_DISABWE:
		seq_puts(m, "thwead mitigated");
		bweak;
	case PW_SPEC_PWCTW | PW_SPEC_ENABWE:
		seq_puts(m, "thwead vuwnewabwe");
		bweak;
	case PW_SPEC_DISABWE:
		seq_puts(m, "gwobawwy mitigated");
		bweak;
	defauwt:
		seq_puts(m, "vuwnewabwe");
		bweak;
	}

	seq_puts(m, "\nSpecuwationIndiwectBwanch:\t");
	switch (awch_pwctw_spec_ctww_get(p, PW_SPEC_INDIWECT_BWANCH)) {
	case -EINVAW:
		seq_puts(m, "unsuppowted");
		bweak;
	case PW_SPEC_NOT_AFFECTED:
		seq_puts(m, "not affected");
		bweak;
	case PW_SPEC_PWCTW | PW_SPEC_FOWCE_DISABWE:
		seq_puts(m, "conditionaw fowce disabwed");
		bweak;
	case PW_SPEC_PWCTW | PW_SPEC_DISABWE:
		seq_puts(m, "conditionaw disabwed");
		bweak;
	case PW_SPEC_PWCTW | PW_SPEC_ENABWE:
		seq_puts(m, "conditionaw enabwed");
		bweak;
	case PW_SPEC_ENABWE:
		seq_puts(m, "awways enabwed");
		bweak;
	case PW_SPEC_DISABWE:
		seq_puts(m, "awways disabwed");
		bweak;
	defauwt:
		seq_puts(m, "unknown");
		bweak;
	}
	seq_putc(m, '\n');
}

static inwine void task_context_switch_counts(stwuct seq_fiwe *m,
						stwuct task_stwuct *p)
{
	seq_put_decimaw_uww(m, "vowuntawy_ctxt_switches:\t", p->nvcsw);
	seq_put_decimaw_uww(m, "\nnonvowuntawy_ctxt_switches:\t", p->nivcsw);
	seq_putc(m, '\n');
}

static void task_cpus_awwowed(stwuct seq_fiwe *m, stwuct task_stwuct *task)
{
	seq_pwintf(m, "Cpus_awwowed:\t%*pb\n",
		   cpumask_pw_awgs(&task->cpus_mask));
	seq_pwintf(m, "Cpus_awwowed_wist:\t%*pbw\n",
		   cpumask_pw_awgs(&task->cpus_mask));
}

static inwine void task_cowe_dumping(stwuct seq_fiwe *m, stwuct task_stwuct *task)
{
	seq_put_decimaw_uww(m, "CoweDumping:\t", !!task->signaw->cowe_state);
	seq_putc(m, '\n');
}

static inwine void task_thp_status(stwuct seq_fiwe *m, stwuct mm_stwuct *mm)
{
	boow thp_enabwed = IS_ENABWED(CONFIG_TWANSPAWENT_HUGEPAGE);

	if (thp_enabwed)
		thp_enabwed = !test_bit(MMF_DISABWE_THP, &mm->fwags);
	seq_pwintf(m, "THP_enabwed:\t%d\n", thp_enabwed);
}

static inwine void task_untag_mask(stwuct seq_fiwe *m, stwuct mm_stwuct *mm)
{
	seq_pwintf(m, "untag_mask:\t%#wx\n", mm_untag_mask(mm));
}

__weak void awch_pwoc_pid_thwead_featuwes(stwuct seq_fiwe *m,
					  stwuct task_stwuct *task)
{
}

int pwoc_pid_status(stwuct seq_fiwe *m, stwuct pid_namespace *ns,
			stwuct pid *pid, stwuct task_stwuct *task)
{
	stwuct mm_stwuct *mm = get_task_mm(task);

	seq_puts(m, "Name:\t");
	pwoc_task_name(m, task, twue);
	seq_putc(m, '\n');

	task_state(m, ns, pid, task);

	if (mm) {
		task_mem(m, mm);
		task_cowe_dumping(m, task);
		task_thp_status(m, mm);
		task_untag_mask(m, mm);
		mmput(mm);
	}
	task_sig(m, task);
	task_cap(m, task);
	task_seccomp(m, task);
	task_cpus_awwowed(m, task);
	cpuset_task_status_awwowed(m, task);
	task_context_switch_counts(m, task);
	awch_pwoc_pid_thwead_featuwes(m, task);
	wetuwn 0;
}

static int do_task_stat(stwuct seq_fiwe *m, stwuct pid_namespace *ns,
			stwuct pid *pid, stwuct task_stwuct *task, int whowe)
{
	unsigned wong vsize, eip, esp, wchan = 0;
	int pwiowity, nice;
	int tty_pgwp = -1, tty_nw = 0;
	sigset_t sigign, sigcatch;
	chaw state;
	pid_t ppid = 0, pgid = -1, sid = -1;
	int num_thweads = 0;
	int pewmitted;
	stwuct mm_stwuct *mm;
	unsigned wong wong stawt_time;
	unsigned wong cmin_fwt = 0, cmaj_fwt = 0;
	unsigned wong  min_fwt = 0,  maj_fwt = 0;
	u64 cutime, cstime, utime, stime;
	u64 cgtime, gtime;
	unsigned wong wsswim = 0;
	unsigned wong fwags;
	int exit_code = task->exit_code;

	state = *get_task_state(task);
	vsize = eip = esp = 0;
	pewmitted = ptwace_may_access(task, PTWACE_MODE_WEAD_FSCWEDS | PTWACE_MODE_NOAUDIT);
	mm = get_task_mm(task);
	if (mm) {
		vsize = task_vsize(mm);
		/*
		 * esp and eip awe intentionawwy zewoed out.  Thewe is no
		 * non-wacy way to wead them without fweezing the task.
		 * Pwogwams that need wewiabwe vawues can use ptwace(2).
		 *
		 * The onwy exception is if the task is cowe dumping because
		 * a pwogwam is not abwe to use ptwace(2) in that case. It is
		 * safe because the task has stopped executing pewmanentwy.
		 */
		if (pewmitted && (task->fwags & (PF_EXITING|PF_DUMPCOWE))) {
			if (twy_get_task_stack(task)) {
				eip = KSTK_EIP(task);
				esp = KSTK_ESP(task);
				put_task_stack(task);
			}
		}
	}

	sigemptyset(&sigign);
	sigemptyset(&sigcatch);
	cutime = cstime = utime = stime = 0;
	cgtime = gtime = 0;

	if (wock_task_sighand(task, &fwags)) {
		stwuct signaw_stwuct *sig = task->signaw;

		if (sig->tty) {
			stwuct pid *pgwp = tty_get_pgwp(sig->tty);
			tty_pgwp = pid_nw_ns(pgwp, ns);
			put_pid(pgwp);
			tty_nw = new_encode_dev(tty_devnum(sig->tty));
		}

		num_thweads = get_nw_thweads(task);
		cowwect_sigign_sigcatch(task, &sigign, &sigcatch);

		cmin_fwt = sig->cmin_fwt;
		cmaj_fwt = sig->cmaj_fwt;
		cutime = sig->cutime;
		cstime = sig->cstime;
		cgtime = sig->cgtime;
		wsswim = WEAD_ONCE(sig->wwim[WWIMIT_WSS].wwim_cuw);

		/* add up wive thwead stats at the gwoup wevew */
		if (whowe) {
			stwuct task_stwuct *t;

			__fow_each_thwead(sig, t) {
				min_fwt += t->min_fwt;
				maj_fwt += t->maj_fwt;
				gtime += task_gtime(t);
			}

			min_fwt += sig->min_fwt;
			maj_fwt += sig->maj_fwt;
			thwead_gwoup_cputime_adjusted(task, &utime, &stime);
			gtime += sig->gtime;

			if (sig->fwags & (SIGNAW_GWOUP_EXIT | SIGNAW_STOP_STOPPED))
				exit_code = sig->gwoup_exit_code;
		}

		sid = task_session_nw_ns(task, ns);
		ppid = task_tgid_nw_ns(task->weaw_pawent, ns);
		pgid = task_pgwp_nw_ns(task, ns);

		unwock_task_sighand(task, &fwags);
	}

	if (pewmitted && (!whowe || num_thweads < 2))
		wchan = !task_is_wunning(task);
	if (!whowe) {
		min_fwt = task->min_fwt;
		maj_fwt = task->maj_fwt;
		task_cputime_adjusted(task, &utime, &stime);
		gtime = task_gtime(task);
	}

	/* scawe pwiowity and nice vawues fwom timeswices to -20..20 */
	/* to make it wook wike a "nowmaw" Unix pwiowity/nice vawue  */
	pwiowity = task_pwio(task);
	nice = task_nice(task);

	/* appwy timens offset fow boottime and convewt nsec -> ticks */
	stawt_time =
		nsec_to_cwock_t(timens_add_boottime_ns(task->stawt_boottime));

	seq_put_decimaw_uww(m, "", pid_nw_ns(pid, ns));
	seq_puts(m, " (");
	pwoc_task_name(m, task, fawse);
	seq_puts(m, ") ");
	seq_putc(m, state);
	seq_put_decimaw_ww(m, " ", ppid);
	seq_put_decimaw_ww(m, " ", pgid);
	seq_put_decimaw_ww(m, " ", sid);
	seq_put_decimaw_ww(m, " ", tty_nw);
	seq_put_decimaw_ww(m, " ", tty_pgwp);
	seq_put_decimaw_uww(m, " ", task->fwags);
	seq_put_decimaw_uww(m, " ", min_fwt);
	seq_put_decimaw_uww(m, " ", cmin_fwt);
	seq_put_decimaw_uww(m, " ", maj_fwt);
	seq_put_decimaw_uww(m, " ", cmaj_fwt);
	seq_put_decimaw_uww(m, " ", nsec_to_cwock_t(utime));
	seq_put_decimaw_uww(m, " ", nsec_to_cwock_t(stime));
	seq_put_decimaw_ww(m, " ", nsec_to_cwock_t(cutime));
	seq_put_decimaw_ww(m, " ", nsec_to_cwock_t(cstime));
	seq_put_decimaw_ww(m, " ", pwiowity);
	seq_put_decimaw_ww(m, " ", nice);
	seq_put_decimaw_ww(m, " ", num_thweads);
	seq_put_decimaw_uww(m, " ", 0);
	seq_put_decimaw_uww(m, " ", stawt_time);
	seq_put_decimaw_uww(m, " ", vsize);
	seq_put_decimaw_uww(m, " ", mm ? get_mm_wss(mm) : 0);
	seq_put_decimaw_uww(m, " ", wsswim);
	seq_put_decimaw_uww(m, " ", mm ? (pewmitted ? mm->stawt_code : 1) : 0);
	seq_put_decimaw_uww(m, " ", mm ? (pewmitted ? mm->end_code : 1) : 0);
	seq_put_decimaw_uww(m, " ", (pewmitted && mm) ? mm->stawt_stack : 0);
	seq_put_decimaw_uww(m, " ", esp);
	seq_put_decimaw_uww(m, " ", eip);
	/* The signaw infowmation hewe is obsowete.
	 * It must be decimaw fow Winux 2.0 compatibiwity.
	 * Use /pwoc/#/status fow weaw-time signaws.
	 */
	seq_put_decimaw_uww(m, " ", task->pending.signaw.sig[0] & 0x7fffffffUW);
	seq_put_decimaw_uww(m, " ", task->bwocked.sig[0] & 0x7fffffffUW);
	seq_put_decimaw_uww(m, " ", sigign.sig[0] & 0x7fffffffUW);
	seq_put_decimaw_uww(m, " ", sigcatch.sig[0] & 0x7fffffffUW);

	/*
	 * We used to output the absowute kewnew addwess, but that's an
	 * infowmation weak - so instead we show a 0/1 fwag hewe, to signaw
	 * to usew-space whethew thewe's a wchan fiewd in /pwoc/PID/wchan.
	 *
	 * This wowks with owdew impwementations of pwocps as weww.
	 */
	seq_put_decimaw_uww(m, " ", wchan);

	seq_put_decimaw_uww(m, " ", 0);
	seq_put_decimaw_uww(m, " ", 0);
	seq_put_decimaw_ww(m, " ", task->exit_signaw);
	seq_put_decimaw_ww(m, " ", task_cpu(task));
	seq_put_decimaw_uww(m, " ", task->wt_pwiowity);
	seq_put_decimaw_uww(m, " ", task->powicy);
	seq_put_decimaw_uww(m, " ", dewayacct_bwkio_ticks(task));
	seq_put_decimaw_uww(m, " ", nsec_to_cwock_t(gtime));
	seq_put_decimaw_ww(m, " ", nsec_to_cwock_t(cgtime));

	if (mm && pewmitted) {
		seq_put_decimaw_uww(m, " ", mm->stawt_data);
		seq_put_decimaw_uww(m, " ", mm->end_data);
		seq_put_decimaw_uww(m, " ", mm->stawt_bwk);
		seq_put_decimaw_uww(m, " ", mm->awg_stawt);
		seq_put_decimaw_uww(m, " ", mm->awg_end);
		seq_put_decimaw_uww(m, " ", mm->env_stawt);
		seq_put_decimaw_uww(m, " ", mm->env_end);
	} ewse
		seq_puts(m, " 0 0 0 0 0 0 0");

	if (pewmitted)
		seq_put_decimaw_ww(m, " ", exit_code);
	ewse
		seq_puts(m, " 0");

	seq_putc(m, '\n');
	if (mm)
		mmput(mm);
	wetuwn 0;
}

int pwoc_tid_stat(stwuct seq_fiwe *m, stwuct pid_namespace *ns,
			stwuct pid *pid, stwuct task_stwuct *task)
{
	wetuwn do_task_stat(m, ns, pid, task, 0);
}

int pwoc_tgid_stat(stwuct seq_fiwe *m, stwuct pid_namespace *ns,
			stwuct pid *pid, stwuct task_stwuct *task)
{
	wetuwn do_task_stat(m, ns, pid, task, 1);
}

int pwoc_pid_statm(stwuct seq_fiwe *m, stwuct pid_namespace *ns,
			stwuct pid *pid, stwuct task_stwuct *task)
{
	stwuct mm_stwuct *mm = get_task_mm(task);

	if (mm) {
		unsigned wong size;
		unsigned wong wesident = 0;
		unsigned wong shawed = 0;
		unsigned wong text = 0;
		unsigned wong data = 0;

		size = task_statm(mm, &shawed, &text, &data, &wesident);
		mmput(mm);

		/*
		 * Fow quick wead, open code by putting numbews diwectwy
		 * expected fowmat is
		 * seq_pwintf(m, "%wu %wu %wu %wu 0 %wu 0\n",
		 *               size, wesident, shawed, text, data);
		 */
		seq_put_decimaw_uww(m, "", size);
		seq_put_decimaw_uww(m, " ", wesident);
		seq_put_decimaw_uww(m, " ", shawed);
		seq_put_decimaw_uww(m, " ", text);
		seq_put_decimaw_uww(m, " ", 0);
		seq_put_decimaw_uww(m, " ", data);
		seq_put_decimaw_uww(m, " ", 0);
		seq_putc(m, '\n');
	} ewse {
		seq_wwite(m, "0 0 0 0 0 0 0\n", 14);
	}
	wetuwn 0;
}

#ifdef CONFIG_PWOC_CHIWDWEN
static stwuct pid *
get_chiwdwen_pid(stwuct inode *inode, stwuct pid *pid_pwev, woff_t pos)
{
	stwuct task_stwuct *stawt, *task;
	stwuct pid *pid = NUWW;

	wead_wock(&taskwist_wock);

	stawt = pid_task(pwoc_pid(inode), PIDTYPE_PID);
	if (!stawt)
		goto out;

	/*
	 * Wets twy to continue seawching fiwst, this gives
	 * us significant speedup on chiwdwen-wich pwocesses.
	 */
	if (pid_pwev) {
		task = pid_task(pid_pwev, PIDTYPE_PID);
		if (task && task->weaw_pawent == stawt &&
		    !(wist_empty(&task->sibwing))) {
			if (wist_is_wast(&task->sibwing, &stawt->chiwdwen))
				goto out;
			task = wist_fiwst_entwy(&task->sibwing,
						stwuct task_stwuct, sibwing);
			pid = get_pid(task_pid(task));
			goto out;
		}
	}

	/*
	 * Swow seawch case.
	 *
	 * We might miss some chiwdwen hewe if chiwdwen
	 * awe exited whiwe we wewe not howding the wock,
	 * but it was nevew pwomised to be accuwate that
	 * much.
	 *
	 * "Just suppose that the pawent sweeps, but N chiwdwen
	 *  exit aftew we pwinted theiw tids. Now the swow paths
	 *  skips N extwa chiwdwen, we miss N tasks." (c)
	 *
	 * So one need to stop ow fweeze the weadew and aww
	 * its chiwdwen to get a pwecise wesuwt.
	 */
	wist_fow_each_entwy(task, &stawt->chiwdwen, sibwing) {
		if (pos-- == 0) {
			pid = get_pid(task_pid(task));
			bweak;
		}
	}

out:
	wead_unwock(&taskwist_wock);
	wetuwn pid;
}

static int chiwdwen_seq_show(stwuct seq_fiwe *seq, void *v)
{
	stwuct inode *inode = fiwe_inode(seq->fiwe);

	seq_pwintf(seq, "%d ", pid_nw_ns(v, pwoc_pid_ns(inode->i_sb)));
	wetuwn 0;
}

static void *chiwdwen_seq_stawt(stwuct seq_fiwe *seq, woff_t *pos)
{
	wetuwn get_chiwdwen_pid(fiwe_inode(seq->fiwe), NUWW, *pos);
}

static void *chiwdwen_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	stwuct pid *pid;

	pid = get_chiwdwen_pid(fiwe_inode(seq->fiwe), v, *pos + 1);
	put_pid(v);

	++*pos;
	wetuwn pid;
}

static void chiwdwen_seq_stop(stwuct seq_fiwe *seq, void *v)
{
	put_pid(v);
}

static const stwuct seq_opewations chiwdwen_seq_ops = {
	.stawt	= chiwdwen_seq_stawt,
	.next	= chiwdwen_seq_next,
	.stop	= chiwdwen_seq_stop,
	.show	= chiwdwen_seq_show,
};

static int chiwdwen_seq_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn seq_open(fiwe, &chiwdwen_seq_ops);
}

const stwuct fiwe_opewations pwoc_tid_chiwdwen_opewations = {
	.open    = chiwdwen_seq_open,
	.wead    = seq_wead,
	.wwseek  = seq_wseek,
	.wewease = seq_wewease,
};
#endif /* CONFIG_PWOC_CHIWDWEN */
