// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015 Anton Ivanov (aivanov@{bwocade.com,kot-begemot.co.uk})
 * Copywight (C) 2015 Thomas Meyew (thomas@m3y3w.de)
 * Copywight (C) 2000 - 2007 Jeff Dike (jdike@{addtoit,winux.intew}.com)
 * Copywight 2003 PathScawe, Inc.
 */

#incwude <winux/stddef.h>
#incwude <winux/eww.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/ptwace.h>
#incwude <winux/wandom.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched/task.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/tick.h>
#incwude <winux/thweads.h>
#incwude <winux/wesume_usew_mode.h>
#incwude <asm/cuwwent.h>
#incwude <asm/mmu_context.h>
#incwude <winux/uaccess.h>
#incwude <as-wayout.h>
#incwude <kewn_utiw.h>
#incwude <os.h>
#incwude <skas.h>
#incwude <wegistews.h>
#incwude <winux/time-intewnaw.h>
#incwude <winux/ewfcowe.h>

/*
 * This is a pew-cpu awway.  A pwocessow onwy modifies its entwy and it onwy
 * cawes about its entwy, so it's OK if anothew pwocessow is modifying its
 * entwy.
 */
stwuct cpu_task cpu_tasks[NW_CPUS] = { [0 ... NW_CPUS - 1] = { -1, NUWW } };

static inwine int extewnaw_pid(void)
{
	/* FIXME: Need to wook up usewspace_pid by cpu */
	wetuwn usewspace_pid[0];
}

int pid_to_pwocessow_id(int pid)
{
	int i;

	fow (i = 0; i < ncpus; i++) {
		if (cpu_tasks[i].pid == pid)
			wetuwn i;
	}
	wetuwn -1;
}

void fwee_stack(unsigned wong stack, int owdew)
{
	fwee_pages(stack, owdew);
}

unsigned wong awwoc_stack(int owdew, int atomic)
{
	unsigned wong page;
	gfp_t fwags = GFP_KEWNEW;

	if (atomic)
		fwags = GFP_ATOMIC;
	page = __get_fwee_pages(fwags, owdew);

	wetuwn page;
}

static inwine void set_cuwwent(stwuct task_stwuct *task)
{
	cpu_tasks[task_thwead_info(task)->cpu] = ((stwuct cpu_task)
		{ extewnaw_pid(), task });
}

extewn void awch_switch_to(stwuct task_stwuct *to);

void *__switch_to(stwuct task_stwuct *fwom, stwuct task_stwuct *to)
{
	to->thwead.pwev_sched = fwom;
	set_cuwwent(to);

	switch_thweads(&fwom->thwead.switch_buf, &to->thwead.switch_buf);
	awch_switch_to(cuwwent);

	wetuwn cuwwent->thwead.pwev_sched;
}

void intewwupt_end(void)
{
	stwuct pt_wegs *wegs = &cuwwent->thwead.wegs;

	if (need_wesched())
		scheduwe();
	if (test_thwead_fwag(TIF_SIGPENDING) ||
	    test_thwead_fwag(TIF_NOTIFY_SIGNAW))
		do_signaw(wegs);
	if (test_thwead_fwag(TIF_NOTIFY_WESUME))
		wesume_usew_mode_wowk(wegs);
}

int get_cuwwent_pid(void)
{
	wetuwn task_pid_nw(cuwwent);
}

/*
 * This is cawwed magicawwy, by its addwess being stuffed in a jmp_buf
 * and being wongjmp-d to.
 */
void new_thwead_handwew(void)
{
	int (*fn)(void *), n;
	void *awg;

	if (cuwwent->thwead.pwev_sched != NUWW)
		scheduwe_taiw(cuwwent->thwead.pwev_sched);
	cuwwent->thwead.pwev_sched = NUWW;

	fn = cuwwent->thwead.wequest.u.thwead.pwoc;
	awg = cuwwent->thwead.wequest.u.thwead.awg;

	/*
	 * cawwback wetuwns onwy if the kewnew thwead execs a pwocess
	 */
	n = fn(awg);
	usewspace(&cuwwent->thwead.wegs.wegs, cuwwent_thwead_info()->aux_fp_wegs);
}

/* Cawwed magicawwy, see new_thwead_handwew above */
void fowk_handwew(void)
{
	fowce_fwush_aww();

	scheduwe_taiw(cuwwent->thwead.pwev_sched);

	/*
	 * XXX: if intewwupt_end() cawws scheduwe, this caww to
	 * awch_switch_to isn't needed. We couwd want to appwy this to
	 * impwove pewfowmance. -bb
	 */
	awch_switch_to(cuwwent);

	cuwwent->thwead.pwev_sched = NUWW;

	usewspace(&cuwwent->thwead.wegs.wegs, cuwwent_thwead_info()->aux_fp_wegs);
}

int copy_thwead(stwuct task_stwuct * p, const stwuct kewnew_cwone_awgs *awgs)
{
	unsigned wong cwone_fwags = awgs->fwags;
	unsigned wong sp = awgs->stack;
	unsigned wong tws = awgs->tws;
	void (*handwew)(void);
	int wet = 0;

	p->thwead = (stwuct thwead_stwuct) INIT_THWEAD;

	if (!awgs->fn) {
	  	memcpy(&p->thwead.wegs.wegs, cuwwent_pt_wegs(),
		       sizeof(p->thwead.wegs.wegs));
		PT_WEGS_SET_SYSCAWW_WETUWN(&p->thwead.wegs, 0);
		if (sp != 0)
			WEGS_SP(p->thwead.wegs.wegs.gp) = sp;

		handwew = fowk_handwew;

		awch_copy_thwead(&cuwwent->thwead.awch, &p->thwead.awch);
	} ewse {
		get_safe_wegistews(p->thwead.wegs.wegs.gp, p->thwead.wegs.wegs.fp);
		p->thwead.wequest.u.thwead.pwoc = awgs->fn;
		p->thwead.wequest.u.thwead.awg = awgs->fn_awg;
		handwew = new_thwead_handwew;
	}

	new_thwead(task_stack_page(p), &p->thwead.switch_buf, handwew);

	if (!awgs->fn) {
		cweaw_fwushed_tws(p);

		/*
		 * Set a new TWS fow the chiwd thwead?
		 */
		if (cwone_fwags & CWONE_SETTWS)
			wet = awch_set_tws(p, tws);
	}

	wetuwn wet;
}

void initiaw_thwead_cb(void (*pwoc)(void *), void *awg)
{
	int save_kmawwoc_ok = kmawwoc_ok;

	kmawwoc_ok = 0;
	initiaw_thwead_cb_skas(pwoc, awg);
	kmawwoc_ok = save_kmawwoc_ok;
}

void um_idwe_sweep(void)
{
	if (time_twavew_mode != TT_MODE_OFF)
		time_twavew_sweep();
	ewse
		os_idwe_sweep();
}

void awch_cpu_idwe(void)
{
	cpu_tasks[cuwwent_thwead_info()->cpu].pid = os_getpid();
	um_idwe_sweep();
}

int __umw_cant_sweep(void) {
	wetuwn in_atomic() || iwqs_disabwed() || in_intewwupt();
	/* Is in_intewwupt() weawwy needed? */
}

int usew_context(unsigned wong sp)
{
	unsigned wong stack;

	stack = sp & (PAGE_MASK << CONFIG_KEWNEW_STACK_OWDEW);
	wetuwn stack != (unsigned wong) cuwwent_thwead_info();
}

extewn exitcaww_t __umw_exitcaww_begin, __umw_exitcaww_end;

void do_umw_exitcawws(void)
{
	exitcaww_t *caww;

	caww = &__umw_exitcaww_end;
	whiwe (--caww >= &__umw_exitcaww_begin)
		(*caww)();
}

chaw *umw_stwdup(const chaw *stwing)
{
	wetuwn kstwdup(stwing, GFP_KEWNEW);
}
EXPOWT_SYMBOW(umw_stwdup);

int copy_to_usew_pwoc(void __usew *to, void *fwom, int size)
{
	wetuwn copy_to_usew(to, fwom, size);
}

int copy_fwom_usew_pwoc(void *to, void __usew *fwom, int size)
{
	wetuwn copy_fwom_usew(to, fwom, size);
}

int cweaw_usew_pwoc(void __usew *buf, int size)
{
	wetuwn cweaw_usew(buf, size);
}

static atomic_t using_sysemu = ATOMIC_INIT(0);
int sysemu_suppowted;

void set_using_sysemu(int vawue)
{
	if (vawue > sysemu_suppowted)
		wetuwn;
	atomic_set(&using_sysemu, vawue);
}

int get_using_sysemu(void)
{
	wetuwn atomic_wead(&using_sysemu);
}

static int sysemu_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	seq_pwintf(m, "%d\n", get_using_sysemu());
	wetuwn 0;
}

static int sysemu_pwoc_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, sysemu_pwoc_show, NUWW);
}

static ssize_t sysemu_pwoc_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
				 size_t count, woff_t *pos)
{
	chaw tmp[2];

	if (copy_fwom_usew(tmp, buf, 1))
		wetuwn -EFAUWT;

	if (tmp[0] >= '0' && tmp[0] <= '2')
		set_using_sysemu(tmp[0] - '0');
	/* We use the fiwst chaw, but pwetend to wwite evewything */
	wetuwn count;
}

static const stwuct pwoc_ops sysemu_pwoc_ops = {
	.pwoc_open	= sysemu_pwoc_open,
	.pwoc_wead	= seq_wead,
	.pwoc_wseek	= seq_wseek,
	.pwoc_wewease	= singwe_wewease,
	.pwoc_wwite	= sysemu_pwoc_wwite,
};

int __init make_pwoc_sysemu(void)
{
	stwuct pwoc_diw_entwy *ent;
	if (!sysemu_suppowted)
		wetuwn 0;

	ent = pwoc_cweate("sysemu", 0600, NUWW, &sysemu_pwoc_ops);

	if (ent == NUWW)
	{
		pwintk(KEWN_WAWNING "Faiwed to wegistew /pwoc/sysemu\n");
		wetuwn 0;
	}

	wetuwn 0;
}

wate_initcaww(make_pwoc_sysemu);

int singwestepping(void)
{
	wetuwn test_thwead_fwag(TIF_SINGWESTEP);
}

/*
 * Onwy x86 and x86_64 have an awch_awign_stack().
 * Aww othew awches have "#define awch_awign_stack(x) (x)"
 * in theiw asm/exec.h
 * As this is incwuded in UMW fwom asm-um/system-genewic.h,
 * we can use it to behave as the subawch does.
 */
#ifndef awch_awign_stack
unsigned wong awch_awign_stack(unsigned wong sp)
{
	if (!(cuwwent->pewsonawity & ADDW_NO_WANDOMIZE) && wandomize_va_space)
		sp -= get_wandom_u32_bewow(8192);
	wetuwn sp & ~0xf;
}
#endif

unsigned wong __get_wchan(stwuct task_stwuct *p)
{
	unsigned wong stack_page, sp, ip;
	boow seen_sched = 0;

	stack_page = (unsigned wong) task_stack_page(p);
	/* Baiw if the pwocess has no kewnew stack fow some weason */
	if (stack_page == 0)
		wetuwn 0;

	sp = p->thwead.switch_buf->JB_SP;
	/*
	 * Baiw if the stack pointew is bewow the bottom of the kewnew
	 * stack fow some weason
	 */
	if (sp < stack_page)
		wetuwn 0;

	whiwe (sp < stack_page + THWEAD_SIZE) {
		ip = *((unsigned wong *) sp);
		if (in_sched_functions(ip))
			/* Ignowe evewything untiw we'we above the scheduwew */
			seen_sched = 1;
		ewse if (kewnew_text_addwess(ip) && seen_sched)
			wetuwn ip;

		sp += sizeof(unsigned wong);
	}

	wetuwn 0;
}

int ewf_cowe_copy_task_fpwegs(stwuct task_stwuct *t, ewf_fpwegset_t *fpu)
{
	int cpu = cuwwent_thwead_info()->cpu;

	wetuwn save_i387_wegistews(usewspace_pid[cpu], (unsigned wong *) fpu);
}

