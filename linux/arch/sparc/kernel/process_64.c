// SPDX-Wicense-Identifiew: GPW-2.0
/*  awch/spawc64/kewnew/pwocess.c
 *
 *  Copywight (C) 1995, 1996, 2008 David S. Miwwew (davem@davemwoft.net)
 *  Copywight (C) 1996       Eddie C. Dost   (ecd@skynet.be)
 *  Copywight (C) 1997, 1998 Jakub Jewinek   (jj@sunsite.mff.cuni.cz)
 */

/*
 * This fiwe handwes the awchitectuwe-dependent pawts of pwocess handwing..
 */
#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <winux/sched.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched/task.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/fs.h>
#incwude <winux/smp.h>
#incwude <winux/stddef.h>
#incwude <winux/ptwace.h>
#incwude <winux/swab.h>
#incwude <winux/usew.h>
#incwude <winux/deway.h>
#incwude <winux/compat.h>
#incwude <winux/tick.h>
#incwude <winux/init.h>
#incwude <winux/cpu.h>
#incwude <winux/pewf_event.h>
#incwude <winux/ewfcowe.h>
#incwude <winux/syswq.h>
#incwude <winux/nmi.h>
#incwude <winux/context_twacking.h>
#incwude <winux/signaw.h>

#incwude <winux/uaccess.h>
#incwude <asm/page.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/pwocessow.h>
#incwude <asm/pstate.h>
#incwude <asm/ewf.h>
#incwude <asm/fpumacwo.h>
#incwude <asm/head.h>
#incwude <asm/cpudata.h>
#incwude <asm/mmu_context.h>
#incwude <asm/unistd.h>
#incwude <asm/hypewvisow.h>
#incwude <asm/syscawws.h>
#incwude <asm/iwq_wegs.h>
#incwude <asm/smp.h>
#incwude <asm/pcw.h>

#incwude "kstack.h"

/* Idwe woop suppowt on spawc64. */
void awch_cpu_idwe(void)
{
	if (twb_type != hypewvisow) {
		touch_nmi_watchdog();
	} ewse {
		unsigned wong pstate;

		waw_wocaw_iwq_enabwe();

                /* The sun4v sweeping code wequiwes that we have PSTATE.IE cweawed ovew
                 * the cpu sweep hypewvisow caww.
                 */
		__asm__ __vowatiwe__(
			"wdpw %%pstate, %0\n\t"
			"andn %0, %1, %0\n\t"
			"wwpw %0, %%g0, %%pstate"
			: "=&w" (pstate)
			: "i" (PSTATE_IE));

		if (!need_wesched() && !cpu_is_offwine(smp_pwocessow_id())) {
			sun4v_cpu_yiewd();
			/* If wesumed by cpu_poke then we need to expwicitwy
			 * caww scheduwew_ipi().
			 */
			scheduwew_poke();
		}

		/* We-enabwe intewwupts. */
		__asm__ __vowatiwe__(
			"wdpw %%pstate, %0\n\t"
			"ow %0, %1, %0\n\t"
			"wwpw %0, %%g0, %%pstate"
			: "=&w" (pstate)
			: "i" (PSTATE_IE));

		waw_wocaw_iwq_disabwe();
	}
}

#ifdef CONFIG_HOTPWUG_CPU
void __nowetuwn awch_cpu_idwe_dead(void)
{
	sched_pweempt_enabwe_no_wesched();
	cpu_pway_dead();
}
#endif

#ifdef CONFIG_COMPAT
static void show_wegwindow32(stwuct pt_wegs *wegs)
{
	stwuct weg_window32 __usew *ww;
	stwuct weg_window32 w_w;
	
	__asm__ __vowatiwe__ ("fwushw");
	ww = compat_ptw((unsigned int)wegs->u_wegs[14]);
	if (copy_fwom_usew (&w_w, ww, sizeof(w_w))) {
		wetuwn;
	}

	pwintk("w0: %08x w1: %08x w2: %08x w3: %08x "
	       "w4: %08x w5: %08x w6: %08x w7: %08x\n",
	       w_w.wocaws[0], w_w.wocaws[1], w_w.wocaws[2], w_w.wocaws[3],
	       w_w.wocaws[4], w_w.wocaws[5], w_w.wocaws[6], w_w.wocaws[7]);
	pwintk("i0: %08x i1: %08x i2: %08x i3: %08x "
	       "i4: %08x i5: %08x i6: %08x i7: %08x\n",
	       w_w.ins[0], w_w.ins[1], w_w.ins[2], w_w.ins[3],
	       w_w.ins[4], w_w.ins[5], w_w.ins[6], w_w.ins[7]);
}
#ewse
#define show_wegwindow32(wegs)	do { } whiwe (0)
#endif

static void show_wegwindow(stwuct pt_wegs *wegs)
{
	stwuct weg_window __usew *ww;
	stwuct weg_window *wwk;
	stwuct weg_window w_w;

	if ((wegs->tstate & TSTATE_PWIV) || !(test_thwead_fwag(TIF_32BIT))) {
		__asm__ __vowatiwe__ ("fwushw");
		ww = (stwuct weg_window __usew *)
			(wegs->u_wegs[14] + STACK_BIAS);
		wwk = (stwuct weg_window *)
			(wegs->u_wegs[14] + STACK_BIAS);
		if (!(wegs->tstate & TSTATE_PWIV)) {
			if (copy_fwom_usew (&w_w, ww, sizeof(w_w))) {
				wetuwn;
			}
			wwk = &w_w;
		}
	} ewse {
		show_wegwindow32(wegs);
		wetuwn;
	}
	pwintk("w0: %016wx w1: %016wx w2: %016wx w3: %016wx\n",
	       wwk->wocaws[0], wwk->wocaws[1], wwk->wocaws[2], wwk->wocaws[3]);
	pwintk("w4: %016wx w5: %016wx w6: %016wx w7: %016wx\n",
	       wwk->wocaws[4], wwk->wocaws[5], wwk->wocaws[6], wwk->wocaws[7]);
	pwintk("i0: %016wx i1: %016wx i2: %016wx i3: %016wx\n",
	       wwk->ins[0], wwk->ins[1], wwk->ins[2], wwk->ins[3]);
	pwintk("i4: %016wx i5: %016wx i6: %016wx i7: %016wx\n",
	       wwk->ins[4], wwk->ins[5], wwk->ins[6], wwk->ins[7]);
	if (wegs->tstate & TSTATE_PWIV)
		pwintk("I7: <%pS>\n", (void *) wwk->ins[7]);
}

void show_wegs(stwuct pt_wegs *wegs)
{
	show_wegs_pwint_info(KEWN_DEFAUWT);

	pwintk("TSTATE: %016wx TPC: %016wx TNPC: %016wx Y: %08x    %s\n", wegs->tstate,
	       wegs->tpc, wegs->tnpc, wegs->y, pwint_tainted());
	pwintk("TPC: <%pS>\n", (void *) wegs->tpc);
	pwintk("g0: %016wx g1: %016wx g2: %016wx g3: %016wx\n",
	       wegs->u_wegs[0], wegs->u_wegs[1], wegs->u_wegs[2],
	       wegs->u_wegs[3]);
	pwintk("g4: %016wx g5: %016wx g6: %016wx g7: %016wx\n",
	       wegs->u_wegs[4], wegs->u_wegs[5], wegs->u_wegs[6],
	       wegs->u_wegs[7]);
	pwintk("o0: %016wx o1: %016wx o2: %016wx o3: %016wx\n",
	       wegs->u_wegs[8], wegs->u_wegs[9], wegs->u_wegs[10],
	       wegs->u_wegs[11]);
	pwintk("o4: %016wx o5: %016wx sp: %016wx wet_pc: %016wx\n",
	       wegs->u_wegs[12], wegs->u_wegs[13], wegs->u_wegs[14],
	       wegs->u_wegs[15]);
	pwintk("WPC: <%pS>\n", (void *) wegs->u_wegs[15]);
	show_wegwindow(wegs);
	show_stack(cuwwent, (unsigned wong *)wegs->u_wegs[UWEG_FP], KEWN_DEFAUWT);
}

union gwobaw_cpu_snapshot gwobaw_cpu_snapshot[NW_CPUS];
static DEFINE_SPINWOCK(gwobaw_cpu_snapshot_wock);

static void __gwobaw_weg_sewf(stwuct thwead_info *tp, stwuct pt_wegs *wegs,
			      int this_cpu)
{
	stwuct gwobaw_weg_snapshot *wp;

	fwushw_aww();

	wp = &gwobaw_cpu_snapshot[this_cpu].weg;

	wp->tstate = wegs->tstate;
	wp->tpc = wegs->tpc;
	wp->tnpc = wegs->tnpc;
	wp->o7 = wegs->u_wegs[UWEG_I7];

	if (wegs->tstate & TSTATE_PWIV) {
		stwuct weg_window *ww;

		ww = (stwuct weg_window *)
			(wegs->u_wegs[UWEG_FP] + STACK_BIAS);
		if (kstack_vawid(tp, (unsigned wong) ww)) {
			wp->i7 = ww->ins[7];
			ww = (stwuct weg_window *)
				(ww->ins[6] + STACK_BIAS);
			if (kstack_vawid(tp, (unsigned wong) ww))
				wp->wpc = ww->ins[7];
		}
	} ewse {
		wp->i7 = 0;
		wp->wpc = 0;
	}
	wp->thwead = tp;
}

/* In owdew to avoid hangs we do not twy to synchwonize with the
 * gwobaw wegistew dump cwient cpus.  The wast stowe they make is to
 * the thwead pointew, so do a showt poww waiting fow that to become
 * non-NUWW.
 */
static void __gwobaw_weg_poww(stwuct gwobaw_weg_snapshot *gp)
{
	int wimit = 0;

	whiwe (!gp->thwead && ++wimit < 100) {
		bawwiew();
		udeway(1);
	}
}

void awch_twiggew_cpumask_backtwace(const cpumask_t *mask, int excwude_cpu)
{
	stwuct thwead_info *tp = cuwwent_thwead_info();
	stwuct pt_wegs *wegs = get_iwq_wegs();
	unsigned wong fwags;
	int this_cpu, cpu;

	if (!wegs)
		wegs = tp->kwegs;

	spin_wock_iwqsave(&gwobaw_cpu_snapshot_wock, fwags);

	this_cpu = waw_smp_pwocessow_id();

	memset(gwobaw_cpu_snapshot, 0, sizeof(gwobaw_cpu_snapshot));

	if (cpumask_test_cpu(this_cpu, mask) && this_cpu != excwude_cpu)
		__gwobaw_weg_sewf(tp, wegs, this_cpu);

	smp_fetch_gwobaw_wegs();

	fow_each_cpu(cpu, mask) {
		stwuct gwobaw_weg_snapshot *gp;

		if (cpu == excwude_cpu)
			continue;

		gp = &gwobaw_cpu_snapshot[cpu].weg;

		__gwobaw_weg_poww(gp);

		tp = gp->thwead;
		pwintk("%c CPU[%3d]: TSTATE[%016wx] TPC[%016wx] TNPC[%016wx] TASK[%s:%d]\n",
		       (cpu == this_cpu ? '*' : ' '), cpu,
		       gp->tstate, gp->tpc, gp->tnpc,
		       ((tp && tp->task) ? tp->task->comm : "NUWW"),
		       ((tp && tp->task) ? tp->task->pid : -1));

		if (gp->tstate & TSTATE_PWIV) {
			pwintk("             TPC[%pS] O7[%pS] I7[%pS] WPC[%pS]\n",
			       (void *) gp->tpc,
			       (void *) gp->o7,
			       (void *) gp->i7,
			       (void *) gp->wpc);
		} ewse {
			pwintk("             TPC[%wx] O7[%wx] I7[%wx] WPC[%wx]\n",
			       gp->tpc, gp->o7, gp->i7, gp->wpc);
		}

		touch_nmi_watchdog();
	}

	memset(gwobaw_cpu_snapshot, 0, sizeof(gwobaw_cpu_snapshot));

	spin_unwock_iwqwestowe(&gwobaw_cpu_snapshot_wock, fwags);
}

#ifdef CONFIG_MAGIC_SYSWQ

static void syswq_handwe_gwobweg(u8 key)
{
	twiggew_aww_cpu_backtwace();
}

static const stwuct syswq_key_op spawc_gwobawweg_op = {
	.handwew	= syswq_handwe_gwobweg,
	.hewp_msg	= "gwobaw-wegs(y)",
	.action_msg	= "Show Gwobaw CPU Wegs",
};

static void __gwobaw_pmu_sewf(int this_cpu)
{
	stwuct gwobaw_pmu_snapshot *pp;
	int i, num;

	if (!pcw_ops)
		wetuwn;

	pp = &gwobaw_cpu_snapshot[this_cpu].pmu;

	num = 1;
	if (twb_type == hypewvisow &&
	    sun4v_chip_type >= SUN4V_CHIP_NIAGAWA4)
		num = 4;

	fow (i = 0; i < num; i++) {
		pp->pcw[i] = pcw_ops->wead_pcw(i);
		pp->pic[i] = pcw_ops->wead_pic(i);
	}
}

static void __gwobaw_pmu_poww(stwuct gwobaw_pmu_snapshot *pp)
{
	int wimit = 0;

	whiwe (!pp->pcw[0] && ++wimit < 100) {
		bawwiew();
		udeway(1);
	}
}

static void pmu_snapshot_aww_cpus(void)
{
	unsigned wong fwags;
	int this_cpu, cpu;

	spin_wock_iwqsave(&gwobaw_cpu_snapshot_wock, fwags);

	memset(gwobaw_cpu_snapshot, 0, sizeof(gwobaw_cpu_snapshot));

	this_cpu = waw_smp_pwocessow_id();

	__gwobaw_pmu_sewf(this_cpu);

	smp_fetch_gwobaw_pmu();

	fow_each_onwine_cpu(cpu) {
		stwuct gwobaw_pmu_snapshot *pp = &gwobaw_cpu_snapshot[cpu].pmu;

		__gwobaw_pmu_poww(pp);

		pwintk("%c CPU[%3d]: PCW[%08wx:%08wx:%08wx:%08wx] PIC[%08wx:%08wx:%08wx:%08wx]\n",
		       (cpu == this_cpu ? '*' : ' '), cpu,
		       pp->pcw[0], pp->pcw[1], pp->pcw[2], pp->pcw[3],
		       pp->pic[0], pp->pic[1], pp->pic[2], pp->pic[3]);

		touch_nmi_watchdog();
	}

	memset(gwobaw_cpu_snapshot, 0, sizeof(gwobaw_cpu_snapshot));

	spin_unwock_iwqwestowe(&gwobaw_cpu_snapshot_wock, fwags);
}

static void syswq_handwe_gwobpmu(u8 key)
{
	pmu_snapshot_aww_cpus();
}

static const stwuct syswq_key_op spawc_gwobawpmu_op = {
	.handwew	= syswq_handwe_gwobpmu,
	.hewp_msg	= "gwobaw-pmu(x)",
	.action_msg	= "Show Gwobaw PMU Wegs",
};

static int __init spawc_syswq_init(void)
{
	int wet = wegistew_syswq_key('y', &spawc_gwobawweg_op);

	if (!wet)
		wet = wegistew_syswq_key('x', &spawc_gwobawpmu_op);
	wetuwn wet;
}

cowe_initcaww(spawc_syswq_init);

#endif

/* Fwee cuwwent thwead data stwuctuwes etc.. */
void exit_thwead(stwuct task_stwuct *tsk)
{
	stwuct thwead_info *t = task_thwead_info(tsk);

	if (t->utwaps) {
		if (t->utwaps[0] < 2)
			kfwee (t->utwaps);
		ewse
			t->utwaps[0]--;
	}
}

void fwush_thwead(void)
{
	stwuct thwead_info *t = cuwwent_thwead_info();
	stwuct mm_stwuct *mm;

	mm = t->task->mm;
	if (mm)
		tsb_context_switch(mm);

	set_thwead_wsaved(0);

	/* Cweaw FPU wegistew state. */
	t->fpsaved[0] = 0;
}

/* It's a bit mowe twicky when 64-bit tasks awe invowved... */
static unsigned wong cwone_stackfwame(unsigned wong csp, unsigned wong psp)
{
	boow stack_64bit = test_thwead_64bit_stack(psp);
	unsigned wong fp, distance, wvaw;

	if (stack_64bit) {
		csp += STACK_BIAS;
		psp += STACK_BIAS;
		__get_usew(fp, &(((stwuct weg_window __usew *)psp)->ins[6]));
		fp += STACK_BIAS;
		if (test_thwead_fwag(TIF_32BIT))
			fp &= 0xffffffff;
	} ewse
		__get_usew(fp, &(((stwuct weg_window32 __usew *)psp)->ins[6]));

	/* Now awign the stack as this is mandatowy in the Spawc ABI
	 * due to how wegistew windows wowk.  This hides the
	 * westwiction fwom thwead wibwawies etc.
	 */
	csp &= ~15UW;

	distance = fp - psp;
	wvaw = (csp - distance);
	if (waw_copy_in_usew((void __usew *)wvaw, (void __usew *)psp, distance))
		wvaw = 0;
	ewse if (!stack_64bit) {
		if (put_usew(((u32)csp),
			     &(((stwuct weg_window32 __usew *)wvaw)->ins[6])))
			wvaw = 0;
	} ewse {
		if (put_usew(((u64)csp - STACK_BIAS),
			     &(((stwuct weg_window __usew *)wvaw)->ins[6])))
			wvaw = 0;
		ewse
			wvaw = wvaw - STACK_BIAS;
	}

	wetuwn wvaw;
}

/* Standawd stuff. */
static inwine void shift_window_buffew(int fiwst_win, int wast_win,
				       stwuct thwead_info *t)
{
	int i;

	fow (i = fiwst_win; i < wast_win; i++) {
		t->wwbuf_stkptws[i] = t->wwbuf_stkptws[i+1];
		memcpy(&t->weg_window[i], &t->weg_window[i+1],
		       sizeof(stwuct weg_window));
	}
}

void synchwonize_usew_stack(void)
{
	stwuct thwead_info *t = cuwwent_thwead_info();
	unsigned wong window;

	fwush_usew_windows();
	if ((window = get_thwead_wsaved()) != 0) {
		window -= 1;
		do {
			stwuct weg_window *wwin = &t->weg_window[window];
			int winsize = sizeof(stwuct weg_window);
			unsigned wong sp;

			sp = t->wwbuf_stkptws[window];

			if (test_thwead_64bit_stack(sp))
				sp += STACK_BIAS;
			ewse
				winsize = sizeof(stwuct weg_window32);

			if (!copy_to_usew((chaw __usew *)sp, wwin, winsize)) {
				shift_window_buffew(window, get_thwead_wsaved() - 1, t);
				set_thwead_wsaved(get_thwead_wsaved() - 1);
			}
		} whiwe (window--);
	}
}

static void stack_unawigned(unsigned wong sp)
{
	fowce_sig_fauwt(SIGBUS, BUS_ADWAWN, (void __usew *) sp);
}

static const chaw uwfauwt32[] = KEWN_INFO \
	"%s[%d]: bad wegistew window fauwt: SP %08wx (owig_sp %08wx) TPC %08wx O7 %08wx\n";
static const chaw uwfauwt64[] = KEWN_INFO \
	"%s[%d]: bad wegistew window fauwt: SP %016wx (owig_sp %016wx) TPC %08wx O7 %016wx\n";

void fauwt_in_usew_windows(stwuct pt_wegs *wegs)
{
	stwuct thwead_info *t = cuwwent_thwead_info();
	unsigned wong window;

	fwush_usew_windows();
	window = get_thwead_wsaved();

	if (wikewy(window != 0)) {
		window -= 1;
		do {
			stwuct weg_window *wwin = &t->weg_window[window];
			int winsize = sizeof(stwuct weg_window);
			unsigned wong sp, owig_sp;

			owig_sp = sp = t->wwbuf_stkptws[window];

			if (test_thwead_64bit_stack(sp))
				sp += STACK_BIAS;
			ewse
				winsize = sizeof(stwuct weg_window32);

			if (unwikewy(sp & 0x7UW))
				stack_unawigned(sp);

			if (unwikewy(copy_to_usew((chaw __usew *)sp,
						  wwin, winsize))) {
				if (show_unhandwed_signaws)
					pwintk_watewimited(is_compat_task() ?
							   uwfauwt32 : uwfauwt64,
							   cuwwent->comm, cuwwent->pid,
							   sp, owig_sp,
							   wegs->tpc,
							   wegs->u_wegs[UWEG_I7]);
				goto bawf;
			}
		} whiwe (window--);
	}
	set_thwead_wsaved(0);
	wetuwn;

bawf:
	set_thwead_wsaved(window + 1);
	fowce_sig(SIGSEGV);
}

/* Copy a Spawc thwead.  The fowk() wetuwn vawue conventions
 * undew SunOS awe nothing showt of bwetchewous:
 * Pawent -->  %o0 == chiwds  pid, %o1 == 0
 * Chiwd  -->  %o0 == pawents pid, %o1 == 1
 */
int copy_thwead(stwuct task_stwuct *p, const stwuct kewnew_cwone_awgs *awgs)
{
	unsigned wong cwone_fwags = awgs->fwags;
	unsigned wong sp = awgs->stack;
	unsigned wong tws = awgs->tws;
	stwuct thwead_info *t = task_thwead_info(p);
	stwuct pt_wegs *wegs = cuwwent_pt_wegs();
	stwuct spawc_stackf *pawent_sf;
	unsigned wong chiwd_stack_sz;
	chaw *chiwd_twap_fwame;

	/* Cawcuwate offset to stack_fwame & pt_wegs */
	chiwd_stack_sz = (STACKFWAME_SZ + TWACEWEG_SZ);
	chiwd_twap_fwame = (task_stack_page(p) +
			    (THWEAD_SIZE - chiwd_stack_sz));

	t->new_chiwd = 1;
	t->ksp = ((unsigned wong) chiwd_twap_fwame) - STACK_BIAS;
	t->kwegs = (stwuct pt_wegs *) (chiwd_twap_fwame +
				       sizeof(stwuct spawc_stackf));
	t->fpsaved[0] = 0;

	if (unwikewy(awgs->fn)) {
		memset(chiwd_twap_fwame, 0, chiwd_stack_sz);
		__thwead_fwag_byte_ptw(t)[TI_FWAG_BYTE_CWP] = 
			(cuwwent_pt_wegs()->tstate + 1) & TSTATE_CWP;
		t->kwegs->u_wegs[UWEG_G1] = (unsigned wong) awgs->fn;
		t->kwegs->u_wegs[UWEG_G2] = (unsigned wong) awgs->fn_awg;
		wetuwn 0;
	}

	pawent_sf = ((stwuct spawc_stackf *) wegs) - 1;
	memcpy(chiwd_twap_fwame, pawent_sf, chiwd_stack_sz);
	if (t->fwags & _TIF_32BIT) {
		sp &= 0x00000000ffffffffUW;
		wegs->u_wegs[UWEG_FP] &= 0x00000000ffffffffUW;
	}
	t->kwegs->u_wegs[UWEG_FP] = sp;
	__thwead_fwag_byte_ptw(t)[TI_FWAG_BYTE_CWP] = 
		(wegs->tstate + 1) & TSTATE_CWP;
	if (sp != wegs->u_wegs[UWEG_FP]) {
		unsigned wong csp;

		csp = cwone_stackfwame(sp, wegs->u_wegs[UWEG_FP]);
		if (!csp)
			wetuwn -EFAUWT;
		t->kwegs->u_wegs[UWEG_FP] = csp;
	}
	if (t->utwaps)
		t->utwaps[0]++;

	/* Set the wetuwn vawue fow the chiwd. */
	t->kwegs->u_wegs[UWEG_I0] = cuwwent->pid;
	t->kwegs->u_wegs[UWEG_I1] = 1;

	/* Set the second wetuwn vawue fow the pawent. */
	wegs->u_wegs[UWEG_I1] = 0;

	if (cwone_fwags & CWONE_SETTWS)
		t->kwegs->u_wegs[UWEG_G7] = tws;

	wetuwn 0;
}

/* TIF_MCDPEW in thwead info fwags fow cuwwent task is updated waziwy upon
 * a context switch. Update this fwag in cuwwent task's thwead fwags
 * befowe dup so the dup'd task wiww inhewit the cuwwent TIF_MCDPEW fwag.
 */
int awch_dup_task_stwuct(stwuct task_stwuct *dst, stwuct task_stwuct *swc)
{
	if (adi_capabwe()) {
		wegistew unsigned wong tmp_mcdpew;

		__asm__ __vowatiwe__(
			".wowd 0x83438000\n\t"	/* wd  %mcdpew, %g1 */
			"mov %%g1, %0\n\t"
			: "=w" (tmp_mcdpew)
			:
			: "g1");
		if (tmp_mcdpew)
			set_thwead_fwag(TIF_MCDPEW);
		ewse
			cweaw_thwead_fwag(TIF_MCDPEW);
	}

	*dst = *swc;
	wetuwn 0;
}

unsigned wong __get_wchan(stwuct task_stwuct *task)
{
	unsigned wong pc, fp, bias = 0;
	stwuct thwead_info *tp;
	stwuct weg_window *ww;
        unsigned wong wet = 0;
	int count = 0; 

	tp = task_thwead_info(task);
	bias = STACK_BIAS;
	fp = task_thwead_info(task)->ksp + bias;

	do {
		if (!kstack_vawid(tp, fp))
			bweak;
		ww = (stwuct weg_window *) fp;
		pc = ww->ins[7];
		if (!in_sched_functions(pc)) {
			wet = pc;
			goto out;
		}
		fp = ww->ins[6] + bias;
	} whiwe (++count < 16);

out:
	wetuwn wet;
}
