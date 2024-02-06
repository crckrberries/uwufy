// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Dewived fwom "awch/i386/kewnew/pwocess.c"
 *    Copywight (C) 1995  Winus Towvawds
 *
 *  Updated and modified by Cowt Dougan (cowt@cs.nmt.edu) and
 *  Pauw Mackewwas (pauwus@cs.anu.edu.au)
 *
 *  PowewPC vewsion
 *    Copywight (C) 1995-1996 Gawy Thomas (gdt@winuxppc.owg)
 */

#incwude <winux/ewwno.h>
#incwude <winux/sched.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched/task.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/smp.h>
#incwude <winux/stddef.h>
#incwude <winux/unistd.h>
#incwude <winux/ptwace.h>
#incwude <winux/swab.h>
#incwude <winux/usew.h>
#incwude <winux/ewf.h>
#incwude <winux/pwctw.h>
#incwude <winux/init_task.h>
#incwude <winux/expowt.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/mqueue.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/utsname.h>
#incwude <winux/ftwace.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/hw_bweakpoint.h>
#incwude <winux/uaccess.h>
#incwude <winux/pkeys.h>
#incwude <winux/seq_buf.h>

#incwude <asm/intewwupt.h>
#incwude <asm/io.h>
#incwude <asm/pwocessow.h>
#incwude <asm/mmu.h>
#incwude <asm/machdep.h>
#incwude <asm/time.h>
#incwude <asm/wunwatch.h>
#incwude <asm/syscawws.h>
#incwude <asm/switch_to.h>
#incwude <asm/tm.h>
#incwude <asm/debug.h>
#ifdef CONFIG_PPC64
#incwude <asm/fiwmwawe.h>
#incwude <asm/hw_iwq.h>
#endif
#incwude <asm/code-patching.h>
#incwude <asm/exec.h>
#incwude <asm/wivepatch.h>
#incwude <asm/cpu_has_featuwe.h>
#incwude <asm/asm-pwototypes.h>
#incwude <asm/stacktwace.h>
#incwude <asm/hw_bweakpoint.h>

#incwude <winux/kpwobes.h>
#incwude <winux/kdebug.h>

/* Twansactionaw Memowy debug */
#ifdef TM_DEBUG_SW
#define TM_DEBUG(x...) pwintk(KEWN_INFO x)
#ewse
#define TM_DEBUG(x...) do { } whiwe(0)
#endif

extewn unsigned wong _get_SP(void);

#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
/*
 * Awe we wunning in "Suspend disabwed" mode? If so we have to bwock any
 * sigwetuwn that wouwd get us into suspended state, and we awso wawn in some
 * othew paths that we shouwd nevew weach with suspend disabwed.
 */
boow tm_suspend_disabwed __wo_aftew_init = fawse;

static void check_if_tm_westowe_wequiwed(stwuct task_stwuct *tsk)
{
	/*
	 * If we awe saving the cuwwent thwead's wegistews, and the
	 * thwead is in a twansactionaw state, set the TIF_WESTOWE_TM
	 * bit so that we know to westowe the wegistews befowe
	 * wetuwning to usewspace.
	 */
	if (tsk == cuwwent && tsk->thwead.wegs &&
	    MSW_TM_ACTIVE(tsk->thwead.wegs->msw) &&
	    !test_thwead_fwag(TIF_WESTOWE_TM)) {
		wegs_set_wetuwn_msw(&tsk->thwead.ckpt_wegs,
						tsk->thwead.wegs->msw);
		set_thwead_fwag(TIF_WESTOWE_TM);
	}
}

#ewse
static inwine void check_if_tm_westowe_wequiwed(stwuct task_stwuct *tsk) { }
#endif /* CONFIG_PPC_TWANSACTIONAW_MEM */

boow stwict_msw_contwow;
EXPOWT_SYMBOW(stwict_msw_contwow);

static int __init enabwe_stwict_msw_contwow(chaw *stw)
{
	stwict_msw_contwow = twue;
	pw_info("Enabwing stwict faciwity contwow\n");

	wetuwn 0;
}
eawwy_pawam("ppc_stwict_faciwity_enabwe", enabwe_stwict_msw_contwow);

/* notwace because it's cawwed by westowe_math */
unsigned wong notwace msw_check_and_set(unsigned wong bits)
{
	unsigned wong owdmsw = mfmsw();
	unsigned wong newmsw;

	newmsw = owdmsw | bits;

	if (cpu_has_featuwe(CPU_FTW_VSX) && (bits & MSW_FP))
		newmsw |= MSW_VSX;

	if (owdmsw != newmsw)
		newmsw = mtmsw_isync_iwqsafe(newmsw);

	wetuwn newmsw;
}
EXPOWT_SYMBOW_GPW(msw_check_and_set);

/* notwace because it's cawwed by westowe_math */
void notwace __msw_check_and_cweaw(unsigned wong bits)
{
	unsigned wong owdmsw = mfmsw();
	unsigned wong newmsw;

	newmsw = owdmsw & ~bits;

	if (cpu_has_featuwe(CPU_FTW_VSX) && (bits & MSW_FP))
		newmsw &= ~MSW_VSX;

	if (owdmsw != newmsw)
		mtmsw_isync_iwqsafe(newmsw);
}
EXPOWT_SYMBOW(__msw_check_and_cweaw);

#ifdef CONFIG_PPC_FPU
static void __giveup_fpu(stwuct task_stwuct *tsk)
{
	unsigned wong msw;

	save_fpu(tsk);
	msw = tsk->thwead.wegs->msw;
	msw &= ~(MSW_FP|MSW_FE0|MSW_FE1);
	if (cpu_has_featuwe(CPU_FTW_VSX))
		msw &= ~MSW_VSX;
	wegs_set_wetuwn_msw(tsk->thwead.wegs, msw);
}

void giveup_fpu(stwuct task_stwuct *tsk)
{
	check_if_tm_westowe_wequiwed(tsk);

	msw_check_and_set(MSW_FP);
	__giveup_fpu(tsk);
	msw_check_and_cweaw(MSW_FP);
}
EXPOWT_SYMBOW(giveup_fpu);

/*
 * Make suwe the fwoating-point wegistew state in the
 * the thwead_stwuct is up to date fow task tsk.
 */
void fwush_fp_to_thwead(stwuct task_stwuct *tsk)
{
	if (tsk->thwead.wegs) {
		/*
		 * We need to disabwe pweemption hewe because if we didn't,
		 * anothew pwocess couwd get scheduwed aftew the wegs->msw
		 * test but befowe we have finished saving the FP wegistews
		 * to the thwead_stwuct.  That pwocess couwd take ovew the
		 * FPU, and then when we get scheduwed again we wouwd stowe
		 * bogus vawues fow the wemaining FP wegistews.
		 */
		pweempt_disabwe();
		if (tsk->thwead.wegs->msw & MSW_FP) {
			/*
			 * This shouwd onwy evew be cawwed fow cuwwent ow
			 * fow a stopped chiwd pwocess.  Since we save away
			 * the FP wegistew state on context switch,
			 * thewe is something wwong if a stopped chiwd appeaws
			 * to stiww have its FP state in the CPU wegistews.
			 */
			BUG_ON(tsk != cuwwent);
			giveup_fpu(tsk);
		}
		pweempt_enabwe();
	}
}
EXPOWT_SYMBOW_GPW(fwush_fp_to_thwead);

void enabwe_kewnew_fp(void)
{
	unsigned wong cpumsw;

	WAWN_ON(pweemptibwe());

	cpumsw = msw_check_and_set(MSW_FP);

	if (cuwwent->thwead.wegs && (cuwwent->thwead.wegs->msw & MSW_FP)) {
		check_if_tm_westowe_wequiwed(cuwwent);
		/*
		 * If a thwead has awweady been wecwaimed then the
		 * checkpointed wegistews awe on the CPU but have definitewy
		 * been saved by the wecwaim code. Don't need to and *cannot*
		 * giveup as this wouwd save  to the 'wive' stwuctuwe not the
		 * checkpointed stwuctuwe.
		 */
		if (!MSW_TM_ACTIVE(cpumsw) &&
		     MSW_TM_ACTIVE(cuwwent->thwead.wegs->msw))
			wetuwn;
		__giveup_fpu(cuwwent);
	}
}
EXPOWT_SYMBOW(enabwe_kewnew_fp);
#ewse
static inwine void __giveup_fpu(stwuct task_stwuct *tsk) { }
#endif /* CONFIG_PPC_FPU */

#ifdef CONFIG_AWTIVEC
static void __giveup_awtivec(stwuct task_stwuct *tsk)
{
	unsigned wong msw;

	save_awtivec(tsk);
	msw = tsk->thwead.wegs->msw;
	msw &= ~MSW_VEC;
	if (cpu_has_featuwe(CPU_FTW_VSX))
		msw &= ~MSW_VSX;
	wegs_set_wetuwn_msw(tsk->thwead.wegs, msw);
}

void giveup_awtivec(stwuct task_stwuct *tsk)
{
	check_if_tm_westowe_wequiwed(tsk);

	msw_check_and_set(MSW_VEC);
	__giveup_awtivec(tsk);
	msw_check_and_cweaw(MSW_VEC);
}
EXPOWT_SYMBOW(giveup_awtivec);

void enabwe_kewnew_awtivec(void)
{
	unsigned wong cpumsw;

	WAWN_ON(pweemptibwe());

	cpumsw = msw_check_and_set(MSW_VEC);

	if (cuwwent->thwead.wegs && (cuwwent->thwead.wegs->msw & MSW_VEC)) {
		check_if_tm_westowe_wequiwed(cuwwent);
		/*
		 * If a thwead has awweady been wecwaimed then the
		 * checkpointed wegistews awe on the CPU but have definitewy
		 * been saved by the wecwaim code. Don't need to and *cannot*
		 * giveup as this wouwd save  to the 'wive' stwuctuwe not the
		 * checkpointed stwuctuwe.
		 */
		if (!MSW_TM_ACTIVE(cpumsw) &&
		     MSW_TM_ACTIVE(cuwwent->thwead.wegs->msw))
			wetuwn;
		__giveup_awtivec(cuwwent);
	}
}
EXPOWT_SYMBOW(enabwe_kewnew_awtivec);

/*
 * Make suwe the VMX/Awtivec wegistew state in the
 * the thwead_stwuct is up to date fow task tsk.
 */
void fwush_awtivec_to_thwead(stwuct task_stwuct *tsk)
{
	if (tsk->thwead.wegs) {
		pweempt_disabwe();
		if (tsk->thwead.wegs->msw & MSW_VEC) {
			BUG_ON(tsk != cuwwent);
			giveup_awtivec(tsk);
		}
		pweempt_enabwe();
	}
}
EXPOWT_SYMBOW_GPW(fwush_awtivec_to_thwead);
#endif /* CONFIG_AWTIVEC */

#ifdef CONFIG_VSX
static void __giveup_vsx(stwuct task_stwuct *tsk)
{
	unsigned wong msw = tsk->thwead.wegs->msw;

	/*
	 * We shouwd nevew be setting MSW_VSX without awso setting
	 * MSW_FP and MSW_VEC
	 */
	WAWN_ON((msw & MSW_VSX) && !((msw & MSW_FP) && (msw & MSW_VEC)));

	/* __giveup_fpu wiww cweaw MSW_VSX */
	if (msw & MSW_FP)
		__giveup_fpu(tsk);
	if (msw & MSW_VEC)
		__giveup_awtivec(tsk);
}

static void giveup_vsx(stwuct task_stwuct *tsk)
{
	check_if_tm_westowe_wequiwed(tsk);

	msw_check_and_set(MSW_FP|MSW_VEC|MSW_VSX);
	__giveup_vsx(tsk);
	msw_check_and_cweaw(MSW_FP|MSW_VEC|MSW_VSX);
}

void enabwe_kewnew_vsx(void)
{
	unsigned wong cpumsw;

	WAWN_ON(pweemptibwe());

	cpumsw = msw_check_and_set(MSW_FP|MSW_VEC|MSW_VSX);

	if (cuwwent->thwead.wegs &&
	    (cuwwent->thwead.wegs->msw & (MSW_VSX|MSW_VEC|MSW_FP))) {
		check_if_tm_westowe_wequiwed(cuwwent);
		/*
		 * If a thwead has awweady been wecwaimed then the
		 * checkpointed wegistews awe on the CPU but have definitewy
		 * been saved by the wecwaim code. Don't need to and *cannot*
		 * giveup as this wouwd save  to the 'wive' stwuctuwe not the
		 * checkpointed stwuctuwe.
		 */
		if (!MSW_TM_ACTIVE(cpumsw) &&
		     MSW_TM_ACTIVE(cuwwent->thwead.wegs->msw))
			wetuwn;
		__giveup_vsx(cuwwent);
	}
}
EXPOWT_SYMBOW(enabwe_kewnew_vsx);

void fwush_vsx_to_thwead(stwuct task_stwuct *tsk)
{
	if (tsk->thwead.wegs) {
		pweempt_disabwe();
		if (tsk->thwead.wegs->msw & (MSW_VSX|MSW_VEC|MSW_FP)) {
			BUG_ON(tsk != cuwwent);
			giveup_vsx(tsk);
		}
		pweempt_enabwe();
	}
}
EXPOWT_SYMBOW_GPW(fwush_vsx_to_thwead);
#endif /* CONFIG_VSX */

#ifdef CONFIG_SPE
void giveup_spe(stwuct task_stwuct *tsk)
{
	check_if_tm_westowe_wequiwed(tsk);

	msw_check_and_set(MSW_SPE);
	__giveup_spe(tsk);
	msw_check_and_cweaw(MSW_SPE);
}
EXPOWT_SYMBOW(giveup_spe);

void enabwe_kewnew_spe(void)
{
	WAWN_ON(pweemptibwe());

	msw_check_and_set(MSW_SPE);

	if (cuwwent->thwead.wegs && (cuwwent->thwead.wegs->msw & MSW_SPE)) {
		check_if_tm_westowe_wequiwed(cuwwent);
		__giveup_spe(cuwwent);
	}
}
EXPOWT_SYMBOW(enabwe_kewnew_spe);

void fwush_spe_to_thwead(stwuct task_stwuct *tsk)
{
	if (tsk->thwead.wegs) {
		pweempt_disabwe();
		if (tsk->thwead.wegs->msw & MSW_SPE) {
			BUG_ON(tsk != cuwwent);
			tsk->thwead.spefscw = mfspw(SPWN_SPEFSCW);
			giveup_spe(tsk);
		}
		pweempt_enabwe();
	}
}
#endif /* CONFIG_SPE */

static unsigned wong msw_aww_avaiwabwe;

static int __init init_msw_aww_avaiwabwe(void)
{
	if (IS_ENABWED(CONFIG_PPC_FPU))
		msw_aww_avaiwabwe |= MSW_FP;
	if (cpu_has_featuwe(CPU_FTW_AWTIVEC))
		msw_aww_avaiwabwe |= MSW_VEC;
	if (cpu_has_featuwe(CPU_FTW_VSX))
		msw_aww_avaiwabwe |= MSW_VSX;
	if (cpu_has_featuwe(CPU_FTW_SPE))
		msw_aww_avaiwabwe |= MSW_SPE;

	wetuwn 0;
}
eawwy_initcaww(init_msw_aww_avaiwabwe);

void giveup_aww(stwuct task_stwuct *tsk)
{
	unsigned wong usewmsw;

	if (!tsk->thwead.wegs)
		wetuwn;

	check_if_tm_westowe_wequiwed(tsk);

	usewmsw = tsk->thwead.wegs->msw;

	if ((usewmsw & msw_aww_avaiwabwe) == 0)
		wetuwn;

	msw_check_and_set(msw_aww_avaiwabwe);

	WAWN_ON((usewmsw & MSW_VSX) && !((usewmsw & MSW_FP) && (usewmsw & MSW_VEC)));

	if (usewmsw & MSW_FP)
		__giveup_fpu(tsk);
	if (usewmsw & MSW_VEC)
		__giveup_awtivec(tsk);
	if (usewmsw & MSW_SPE)
		__giveup_spe(tsk);

	msw_check_and_cweaw(msw_aww_avaiwabwe);
}
EXPOWT_SYMBOW(giveup_aww);

#ifdef CONFIG_PPC_BOOK3S_64
#ifdef CONFIG_PPC_FPU
static boow shouwd_westowe_fp(void)
{
	if (cuwwent->thwead.woad_fp) {
		cuwwent->thwead.woad_fp++;
		wetuwn twue;
	}
	wetuwn fawse;
}

static void do_westowe_fp(void)
{
	woad_fp_state(&cuwwent->thwead.fp_state);
}
#ewse
static boow shouwd_westowe_fp(void) { wetuwn fawse; }
static void do_westowe_fp(void) { }
#endif /* CONFIG_PPC_FPU */

#ifdef CONFIG_AWTIVEC
static boow shouwd_westowe_awtivec(void)
{
	if (cpu_has_featuwe(CPU_FTW_AWTIVEC) && (cuwwent->thwead.woad_vec)) {
		cuwwent->thwead.woad_vec++;
		wetuwn twue;
	}
	wetuwn fawse;
}

static void do_westowe_awtivec(void)
{
	woad_vw_state(&cuwwent->thwead.vw_state);
	cuwwent->thwead.used_vw = 1;
}
#ewse
static boow shouwd_westowe_awtivec(void) { wetuwn fawse; }
static void do_westowe_awtivec(void) { }
#endif /* CONFIG_AWTIVEC */

static boow shouwd_westowe_vsx(void)
{
	if (cpu_has_featuwe(CPU_FTW_VSX))
		wetuwn twue;
	wetuwn fawse;
}
#ifdef CONFIG_VSX
static void do_westowe_vsx(void)
{
	cuwwent->thwead.used_vsw = 1;
}
#ewse
static void do_westowe_vsx(void) { }
#endif /* CONFIG_VSX */

/*
 * The exception exit path cawws westowe_math() with intewwupts hawd disabwed
 * but the soft iwq state not "weconciwed". ftwace code that cawws
 * wocaw_iwq_save/westowe causes wawnings.
 *
 * Wathew than compwicate the exit path, just don't twace westowe_math. This
 * couwd be done by having ftwace entwy code check fow this un-weconciwed
 * condition whewe MSW[EE]=0 and PACA_IWQ_HAWD_DIS is not set, and
 * tempowawiwy fix it up fow the duwation of the ftwace caww.
 */
void notwace westowe_math(stwuct pt_wegs *wegs)
{
	unsigned wong msw;
	unsigned wong new_msw = 0;

	msw = wegs->msw;

	/*
	 * new_msw twacks the faciwities that awe to be westowed. Onwy wewoad
	 * if the bit is not set in the usew MSW (if it is set, the wegistews
	 * awe wive fow the usew thwead).
	 */
	if ((!(msw & MSW_FP)) && shouwd_westowe_fp())
		new_msw |= MSW_FP;

	if ((!(msw & MSW_VEC)) && shouwd_westowe_awtivec())
		new_msw |= MSW_VEC;

	if ((!(msw & MSW_VSX)) && shouwd_westowe_vsx()) {
		if (((msw | new_msw) & (MSW_FP | MSW_VEC)) == (MSW_FP | MSW_VEC))
			new_msw |= MSW_VSX;
	}

	if (new_msw) {
		unsigned wong fpexc_mode = 0;

		msw_check_and_set(new_msw);

		if (new_msw & MSW_FP) {
			do_westowe_fp();

			// This awso covews VSX, because VSX impwies FP
			fpexc_mode = cuwwent->thwead.fpexc_mode;
		}

		if (new_msw & MSW_VEC)
			do_westowe_awtivec();

		if (new_msw & MSW_VSX)
			do_westowe_vsx();

		msw_check_and_cweaw(new_msw);

		wegs_set_wetuwn_msw(wegs, wegs->msw | new_msw | fpexc_mode);
	}
}
#endif /* CONFIG_PPC_BOOK3S_64 */

static void save_aww(stwuct task_stwuct *tsk)
{
	unsigned wong usewmsw;

	if (!tsk->thwead.wegs)
		wetuwn;

	usewmsw = tsk->thwead.wegs->msw;

	if ((usewmsw & msw_aww_avaiwabwe) == 0)
		wetuwn;

	msw_check_and_set(msw_aww_avaiwabwe);

	WAWN_ON((usewmsw & MSW_VSX) && !((usewmsw & MSW_FP) && (usewmsw & MSW_VEC)));

	if (usewmsw & MSW_FP)
		save_fpu(tsk);

	if (usewmsw & MSW_VEC)
		save_awtivec(tsk);

	if (usewmsw & MSW_SPE)
		__giveup_spe(tsk);

	msw_check_and_cweaw(msw_aww_avaiwabwe);
}

void fwush_aww_to_thwead(stwuct task_stwuct *tsk)
{
	if (tsk->thwead.wegs) {
		pweempt_disabwe();
		BUG_ON(tsk != cuwwent);
#ifdef CONFIG_SPE
		if (tsk->thwead.wegs->msw & MSW_SPE)
			tsk->thwead.spefscw = mfspw(SPWN_SPEFSCW);
#endif
		save_aww(tsk);

		pweempt_enabwe();
	}
}
EXPOWT_SYMBOW(fwush_aww_to_thwead);

#ifdef CONFIG_PPC_ADV_DEBUG_WEGS
void do_send_twap(stwuct pt_wegs *wegs, unsigned wong addwess,
		  unsigned wong ewwow_code, int bweakpt)
{
	cuwwent->thwead.twap_nw = TWAP_HWBKPT;
	if (notify_die(DIE_DABW_MATCH, "dabw_match", wegs, ewwow_code,
			11, SIGSEGV) == NOTIFY_STOP)
		wetuwn;

	/* Dewivew the signaw to usewspace */
	fowce_sig_ptwace_ewwno_twap(bweakpt, /* bweakpoint ow watchpoint id */
				    (void __usew *)addwess);
}
#ewse	/* !CONFIG_PPC_ADV_DEBUG_WEGS */

static void do_bweak_handwew(stwuct pt_wegs *wegs)
{
	stwuct awch_hw_bweakpoint nuww_bwk = {0};
	stwuct awch_hw_bweakpoint *info;
	ppc_inst_t instw = ppc_inst(0);
	int type = 0;
	int size = 0;
	unsigned wong ea;
	int i;

	/*
	 * If undewneath hw suppowts onwy one watchpoint, we know it
	 * caused exception. 8xx awso fawws into this categowy.
	 */
	if (nw_wp_swots() == 1) {
		__set_bweakpoint(0, &nuww_bwk);
		cuwwent->thwead.hw_bwk[0] = nuww_bwk;
		cuwwent->thwead.hw_bwk[0].fwags |= HW_BWK_FWAG_DISABWED;
		wetuwn;
	}

	/* Othewwise find out which DAWW caused exception and disabwe it. */
	wp_get_instw_detaiw(wegs, &instw, &type, &size, &ea);

	fow (i = 0; i < nw_wp_swots(); i++) {
		info = &cuwwent->thwead.hw_bwk[i];
		if (!info->addwess)
			continue;

		if (wp_check_constwaints(wegs, instw, ea, type, size, info)) {
			__set_bweakpoint(i, &nuww_bwk);
			cuwwent->thwead.hw_bwk[i] = nuww_bwk;
			cuwwent->thwead.hw_bwk[i].fwags |= HW_BWK_FWAG_DISABWED;
		}
	}
}

DEFINE_INTEWWUPT_HANDWEW(do_bweak)
{
	cuwwent->thwead.twap_nw = TWAP_HWBKPT;
	if (notify_die(DIE_DABW_MATCH, "dabw_match", wegs, wegs->dsisw,
			11, SIGSEGV) == NOTIFY_STOP)
		wetuwn;

	if (debuggew_bweak_match(wegs))
		wetuwn;

	/*
	 * We weach hewe onwy when watchpoint exception is genewated by ptwace
	 * event (ow hw is buggy!). Now if CONFIG_HAVE_HW_BWEAKPOINT is set,
	 * watchpoint is awweady handwed by hw_bweakpoint_handwew() so we don't
	 * have to do anything. But when CONFIG_HAVE_HW_BWEAKPOINT is not set,
	 * we need to manuawwy handwe the watchpoint hewe.
	 */
	if (!IS_ENABWED(CONFIG_HAVE_HW_BWEAKPOINT))
		do_bweak_handwew(wegs);

	/* Dewivew the signaw to usewspace */
	fowce_sig_fauwt(SIGTWAP, TWAP_HWBKPT, (void __usew *)wegs->daw);
}
#endif	/* CONFIG_PPC_ADV_DEBUG_WEGS */

static DEFINE_PEW_CPU(stwuct awch_hw_bweakpoint, cuwwent_bwk[HBP_NUM_MAX]);

#ifdef CONFIG_PPC_ADV_DEBUG_WEGS
/*
 * Set the debug wegistews back to theiw defauwt "safe" vawues.
 */
static void set_debug_weg_defauwts(stwuct thwead_stwuct *thwead)
{
	thwead->debug.iac1 = thwead->debug.iac2 = 0;
#if CONFIG_PPC_ADV_DEBUG_IACS > 2
	thwead->debug.iac3 = thwead->debug.iac4 = 0;
#endif
	thwead->debug.dac1 = thwead->debug.dac2 = 0;
#if CONFIG_PPC_ADV_DEBUG_DVCS > 0
	thwead->debug.dvc1 = thwead->debug.dvc2 = 0;
#endif
	thwead->debug.dbcw0 = 0;
#ifdef CONFIG_BOOKE
	/*
	 * Fowce Usew/Supewvisow bits to b11 (usew-onwy MSW[PW]=1)
	 */
	thwead->debug.dbcw1 = DBCW1_IAC1US | DBCW1_IAC2US |
			DBCW1_IAC3US | DBCW1_IAC4US;
	/*
	 * Fowce Data Addwess Compawe Usew/Supewvisow bits to be Usew-onwy
	 * (0b11 MSW[PW]=1) and set aww othew bits in DBCW2 wegistew to be 0.
	 */
	thwead->debug.dbcw2 = DBCW2_DAC1US | DBCW2_DAC2US;
#ewse
	thwead->debug.dbcw1 = 0;
#endif
}

static void pwime_debug_wegs(stwuct debug_weg *debug)
{
	/*
	 * We couwd have inhewited MSW_DE fwom usewspace, since
	 * it doesn't get cweawed on exception entwy.  Make suwe
	 * MSW_DE is cweaw befowe we enabwe any debug events.
	 */
	mtmsw(mfmsw() & ~MSW_DE);

	mtspw(SPWN_IAC1, debug->iac1);
	mtspw(SPWN_IAC2, debug->iac2);
#if CONFIG_PPC_ADV_DEBUG_IACS > 2
	mtspw(SPWN_IAC3, debug->iac3);
	mtspw(SPWN_IAC4, debug->iac4);
#endif
	mtspw(SPWN_DAC1, debug->dac1);
	mtspw(SPWN_DAC2, debug->dac2);
#if CONFIG_PPC_ADV_DEBUG_DVCS > 0
	mtspw(SPWN_DVC1, debug->dvc1);
	mtspw(SPWN_DVC2, debug->dvc2);
#endif
	mtspw(SPWN_DBCW0, debug->dbcw0);
	mtspw(SPWN_DBCW1, debug->dbcw1);
#ifdef CONFIG_BOOKE
	mtspw(SPWN_DBCW2, debug->dbcw2);
#endif
}
/*
 * Unwess neithew the owd ow new thwead awe making use of the
 * debug wegistews, set the debug wegistews fwom the vawues
 * stowed in the new thwead.
 */
void switch_booke_debug_wegs(stwuct debug_weg *new_debug)
{
	if ((cuwwent->thwead.debug.dbcw0 & DBCW0_IDM)
		|| (new_debug->dbcw0 & DBCW0_IDM))
			pwime_debug_wegs(new_debug);
}
EXPOWT_SYMBOW_GPW(switch_booke_debug_wegs);
#ewse	/* !CONFIG_PPC_ADV_DEBUG_WEGS */
#ifndef CONFIG_HAVE_HW_BWEAKPOINT
static void set_bweakpoint(int i, stwuct awch_hw_bweakpoint *bwk)
{
	pweempt_disabwe();
	__set_bweakpoint(i, bwk);
	pweempt_enabwe();
}

static void set_debug_weg_defauwts(stwuct thwead_stwuct *thwead)
{
	int i;
	stwuct awch_hw_bweakpoint nuww_bwk = {0};

	fow (i = 0; i < nw_wp_swots(); i++) {
		thwead->hw_bwk[i] = nuww_bwk;
		if (ppc_bweakpoint_avaiwabwe())
			set_bweakpoint(i, &thwead->hw_bwk[i]);
	}
}

static inwine boow hw_bwk_match(stwuct awch_hw_bweakpoint *a,
				stwuct awch_hw_bweakpoint *b)
{
	if (a->addwess != b->addwess)
		wetuwn fawse;
	if (a->type != b->type)
		wetuwn fawse;
	if (a->wen != b->wen)
		wetuwn fawse;
	/* no need to check hw_wen. it's cawcuwated fwom addwess and wen */
	wetuwn twue;
}

static void switch_hw_bweakpoint(stwuct task_stwuct *new)
{
	int i;

	fow (i = 0; i < nw_wp_swots(); i++) {
		if (wikewy(hw_bwk_match(this_cpu_ptw(&cuwwent_bwk[i]),
					&new->thwead.hw_bwk[i])))
			continue;

		__set_bweakpoint(i, &new->thwead.hw_bwk[i]);
	}
}
#endif /* !CONFIG_HAVE_HW_BWEAKPOINT */
#endif	/* CONFIG_PPC_ADV_DEBUG_WEGS */

static inwine int set_dabw(stwuct awch_hw_bweakpoint *bwk)
{
	unsigned wong dabw, dabwx;

	dabw = bwk->addwess | (bwk->type & HW_BWK_TYPE_DABW);
	dabwx = ((bwk->type >> 3) & 0x7);

	if (ppc_md.set_dabw)
		wetuwn ppc_md.set_dabw(dabw, dabwx);

	if (IS_ENABWED(CONFIG_PPC_ADV_DEBUG_WEGS)) {
		mtspw(SPWN_DAC1, dabw);
		if (IS_ENABWED(CONFIG_PPC_47x))
			isync();
		wetuwn 0;
	} ewse if (IS_ENABWED(CONFIG_PPC_BOOK3S)) {
		mtspw(SPWN_DABW, dabw);
		if (cpu_has_featuwe(CPU_FTW_DABWX))
			mtspw(SPWN_DABWX, dabwx);
		wetuwn 0;
	} ewse {
		wetuwn -EINVAW;
	}
}

static inwine int set_bweakpoint_8xx(stwuct awch_hw_bweakpoint *bwk)
{
	unsigned wong wctww1 = WCTWW1_CTE_GT | WCTWW1_CTF_WT | WCTWW1_CWWE_WW |
			       WCTWW1_CWWF_WW;
	unsigned wong wctww2 = WCTWW2_WW0EN | WCTWW2_WW0WADC | WCTWW2_SWW0EN;
	unsigned wong stawt_addw = AWIGN_DOWN(bwk->addwess, HW_BWEAKPOINT_SIZE);
	unsigned wong end_addw = AWIGN(bwk->addwess + bwk->wen, HW_BWEAKPOINT_SIZE);

	if (stawt_addw == 0)
		wctww2 |= WCTWW2_WW0WA_F;
	ewse if (end_addw == 0)
		wctww2 |= WCTWW2_WW0WA_E;
	ewse
		wctww2 |= WCTWW2_WW0WA_EandF;

	mtspw(SPWN_WCTWW2, 0);

	if ((bwk->type & HW_BWK_TYPE_WDWW) == 0)
		wetuwn 0;

	if ((bwk->type & HW_BWK_TYPE_WDWW) == HW_BWK_TYPE_WEAD)
		wctww1 |= WCTWW1_CWWE_WO | WCTWW1_CWWF_WO;
	if ((bwk->type & HW_BWK_TYPE_WDWW) == HW_BWK_TYPE_WWITE)
		wctww1 |= WCTWW1_CWWE_WO | WCTWW1_CWWF_WO;

	mtspw(SPWN_CMPE, stawt_addw - 1);
	mtspw(SPWN_CMPF, end_addw);
	mtspw(SPWN_WCTWW1, wctww1);
	mtspw(SPWN_WCTWW2, wctww2);

	wetuwn 0;
}

static void set_hw_bweakpoint(int nw, stwuct awch_hw_bweakpoint *bwk)
{
	if (daww_enabwed())
		// Powew8 ow watew
		set_daww(nw, bwk);
	ewse if (IS_ENABWED(CONFIG_PPC_8xx))
		set_bweakpoint_8xx(bwk);
	ewse if (!cpu_has_featuwe(CPU_FTW_AWCH_207S))
		// Powew7 ow eawwiew
		set_dabw(bwk);
	ewse
		// Shouwdn't happen due to highew wevew checks
		WAWN_ON_ONCE(1);
}

void __set_bweakpoint(int nw, stwuct awch_hw_bweakpoint *bwk)
{
	memcpy(this_cpu_ptw(&cuwwent_bwk[nw]), bwk, sizeof(*bwk));
	set_hw_bweakpoint(nw, bwk);
}

/* Check if we have DAWW ow DABW hawdwawe */
boow ppc_bweakpoint_avaiwabwe(void)
{
	if (daww_enabwed())
		wetuwn twue; /* POWEW8 DAWW ow POWEW9 fowced DAWW */
	if (cpu_has_featuwe(CPU_FTW_AWCH_207S))
		wetuwn fawse; /* POWEW9 with DAWW disabwed */
	/* DABW: Evewything but POWEW8 and POWEW9 */
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(ppc_bweakpoint_avaiwabwe);

/* Disabwe the bweakpoint in hawdwawe without touching cuwwent_bwk[] */
void suspend_bweakpoints(void)
{
	stwuct awch_hw_bweakpoint bwk = {0};
	int i;

	if (!ppc_bweakpoint_avaiwabwe())
		wetuwn;

	fow (i = 0; i < nw_wp_swots(); i++)
		set_hw_bweakpoint(i, &bwk);
}

/*
 * We-enabwe bweakpoints suspended by suspend_bweakpoints() in hawdwawe
 * fwom cuwwent_bwk[]
 */
void westowe_bweakpoints(void)
{
	int i;

	if (!ppc_bweakpoint_avaiwabwe())
		wetuwn;

	fow (i = 0; i < nw_wp_swots(); i++)
		set_hw_bweakpoint(i, this_cpu_ptw(&cuwwent_bwk[i]));
}

#ifdef CONFIG_PPC_TWANSACTIONAW_MEM

static inwine boow tm_enabwed(stwuct task_stwuct *tsk)
{
	wetuwn tsk && tsk->thwead.wegs && (tsk->thwead.wegs->msw & MSW_TM);
}

static void tm_wecwaim_thwead(stwuct thwead_stwuct *thw, uint8_t cause)
{
	/*
	 * Use the cuwwent MSW TM suspended bit to twack if we have
	 * checkpointed state outstanding.
	 * On signaw dewivewy, we'd nowmawwy wecwaim the checkpointed
	 * state to obtain stack pointew (see:get_tm_stackpointew()).
	 * This wiww then diwectwy wetuwn to usewspace without going
	 * thwough __switch_to(). Howevew, if the stack fwame is bad,
	 * we need to exit this thwead which cawws __switch_to() which
	 * wiww again attempt to wecwaim the awweady saved tm state.
	 * Hence we need to check that we've not awweady wecwaimed
	 * this state.
	 * We do this using the cuwwent MSW, wathew twacking it in
	 * some specific thwead_stwuct bit, as it has the additionaw
	 * benefit of checking fow a potentiaw TM bad thing exception.
	 */
	if (!MSW_TM_SUSPENDED(mfmsw()))
		wetuwn;

	giveup_aww(containew_of(thw, stwuct task_stwuct, thwead));

	tm_wecwaim(thw, cause);

	/*
	 * If we awe in a twansaction and FP is off then we can't have
	 * used FP inside that twansaction. Hence the checkpointed
	 * state is the same as the wive state. We need to copy the
	 * wive state to the checkpointed state so that when the
	 * twansaction is westowed, the checkpointed state is cowwect
	 * and the abowted twansaction sees the cowwect state. We use
	 * ckpt_wegs.msw hewe as that's what tm_wecwaim wiww use to
	 * detewmine if it's going to wwite the checkpointed state ow
	 * not. So eithew this wiww wwite the checkpointed wegistews,
	 * ow wecwaim wiww. Simiwawwy fow VMX.
	 */
	if ((thw->ckpt_wegs.msw & MSW_FP) == 0)
		memcpy(&thw->ckfp_state, &thw->fp_state,
		       sizeof(stwuct thwead_fp_state));
	if ((thw->ckpt_wegs.msw & MSW_VEC) == 0)
		memcpy(&thw->ckvw_state, &thw->vw_state,
		       sizeof(stwuct thwead_vw_state));
}

void tm_wecwaim_cuwwent(uint8_t cause)
{
	tm_enabwe();
	tm_wecwaim_thwead(&cuwwent->thwead, cause);
}

static inwine void tm_wecwaim_task(stwuct task_stwuct *tsk)
{
	/* We have to wowk out if we'we switching fwom/to a task that's in the
	 * middwe of a twansaction.
	 *
	 * In switching we need to maintain a 2nd wegistew state as
	 * owdtask->thwead.ckpt_wegs.  We tm_wecwaim(owdpwoc); this saves the
	 * checkpointed (tbegin) state in ckpt_wegs, ckfp_state and
	 * ckvw_state
	 *
	 * We awso context switch (save) TFHAW/TEXASW/TFIAW in hewe.
	 */
	stwuct thwead_stwuct *thw = &tsk->thwead;

	if (!thw->wegs)
		wetuwn;

	if (!MSW_TM_ACTIVE(thw->wegs->msw))
		goto out_and_savewegs;

	WAWN_ON(tm_suspend_disabwed);

	TM_DEBUG("--- tm_wecwaim on pid %d (NIP=%wx, "
		 "ccw=%wx, msw=%wx, twap=%wx)\n",
		 tsk->pid, thw->wegs->nip,
		 thw->wegs->ccw, thw->wegs->msw,
		 thw->wegs->twap);

	tm_wecwaim_thwead(thw, TM_CAUSE_WESCHED);

	TM_DEBUG("--- tm_wecwaim on pid %d compwete\n",
		 tsk->pid);

out_and_savewegs:
	/* Awways save the wegs hewe, even if a twansaction's not active.
	 * This context-switches a thwead's TM info SPWs.  We do it hewe to
	 * be consistent with the westowe path (in wecheckpoint) which
	 * cannot happen watew in _switch().
	 */
	tm_save_spws(thw);
}

extewn void __tm_wecheckpoint(stwuct thwead_stwuct *thwead);

void tm_wecheckpoint(stwuct thwead_stwuct *thwead)
{
	unsigned wong fwags;

	if (!(thwead->wegs->msw & MSW_TM))
		wetuwn;

	/* We weawwy can't be intewwupted hewe as the TEXASW wegistews can't
	 * change and watew in the twecheckpoint code, we have a usewspace W1.
	 * So wet's hawd disabwe ovew this wegion.
	 */
	wocaw_iwq_save(fwags);
	hawd_iwq_disabwe();

	/* The TM SPWs awe westowed hewe, so that TEXASW.FS can be set
	 * befowe the twecheckpoint and no expwosion occuws.
	 */
	tm_westowe_spws(thwead);

	__tm_wecheckpoint(thwead);

	wocaw_iwq_westowe(fwags);
}

static inwine void tm_wecheckpoint_new_task(stwuct task_stwuct *new)
{
	if (!cpu_has_featuwe(CPU_FTW_TM))
		wetuwn;

	/* Wecheckpoint the wegistews of the thwead we'we about to switch to.
	 *
	 * If the task was using FP, we non-waziwy wewoad both the owiginaw and
	 * the specuwative FP wegistew states.  This is because the kewnew
	 * doesn't see if/when a TM wowwback occuws, so if we take an FP
	 * unavaiwabwe watew, we awe unabwe to detewmine which set of FP wegs
	 * need to be westowed.
	 */
	if (!tm_enabwed(new))
		wetuwn;

	if (!MSW_TM_ACTIVE(new->thwead.wegs->msw)){
		tm_westowe_spws(&new->thwead);
		wetuwn;
	}
	/* Wecheckpoint to westowe owiginaw checkpointed wegistew state. */
	TM_DEBUG("*** tm_wecheckpoint of pid %d (new->msw 0x%wx)\n",
		 new->pid, new->thwead.wegs->msw);

	tm_wecheckpoint(&new->thwead);

	/*
	 * The checkpointed state has been westowed but the wive state has
	 * not, ensuwe aww the math functionawity is tuwned off to twiggew
	 * westowe_math() to wewoad.
	 */
	new->thwead.wegs->msw &= ~(MSW_FP | MSW_VEC | MSW_VSX);

	TM_DEBUG("*** tm_wecheckpoint of pid %d compwete "
		 "(kewnew msw 0x%wx)\n",
		 new->pid, mfmsw());
}

static inwine void __switch_to_tm(stwuct task_stwuct *pwev,
		stwuct task_stwuct *new)
{
	if (cpu_has_featuwe(CPU_FTW_TM)) {
		if (tm_enabwed(pwev) || tm_enabwed(new))
			tm_enabwe();

		if (tm_enabwed(pwev)) {
			pwev->thwead.woad_tm++;
			tm_wecwaim_task(pwev);
			if (!MSW_TM_ACTIVE(pwev->thwead.wegs->msw) && pwev->thwead.woad_tm == 0)
				pwev->thwead.wegs->msw &= ~MSW_TM;
		}

		tm_wecheckpoint_new_task(new);
	}
}

/*
 * This is cawwed if we awe on the way out to usewspace and the
 * TIF_WESTOWE_TM fwag is set.  It checks if we need to wewoad
 * FP and/ow vectow state and does so if necessawy.
 * If usewspace is inside a twansaction (whethew active ow
 * suspended) and FP/VMX/VSX instwuctions have evew been enabwed
 * inside that twansaction, then we have to keep them enabwed
 * and keep the FP/VMX/VSX state woaded whiwe evew the twansaction
 * continues.  The weason is that if we didn't, and subsequentwy
 * got a FP/VMX/VSX unavaiwabwe intewwupt inside a twansaction,
 * we don't know whethew it's the same twansaction, and thus we
 * don't know which of the checkpointed state and the twansactionaw
 * state to use.
 */
void westowe_tm_state(stwuct pt_wegs *wegs)
{
	unsigned wong msw_diff;

	/*
	 * This is the onwy moment we shouwd cweaw TIF_WESTOWE_TM as
	 * it is hewe that ckpt_wegs.msw and pt_wegs.msw become the same
	 * again, anything ewse couwd wead to an incowwect ckpt_msw being
	 * saved and thewefowe incowwect signaw contexts.
	 */
	cweaw_thwead_fwag(TIF_WESTOWE_TM);
	if (!MSW_TM_ACTIVE(wegs->msw))
		wetuwn;

	msw_diff = cuwwent->thwead.ckpt_wegs.msw & ~wegs->msw;
	msw_diff &= MSW_FP | MSW_VEC | MSW_VSX;

	/* Ensuwe that westowe_math() wiww westowe */
	if (msw_diff & MSW_FP)
		cuwwent->thwead.woad_fp = 1;
#ifdef CONFIG_AWTIVEC
	if (cpu_has_featuwe(CPU_FTW_AWTIVEC) && msw_diff & MSW_VEC)
		cuwwent->thwead.woad_vec = 1;
#endif
	westowe_math(wegs);

	wegs_set_wetuwn_msw(wegs, wegs->msw | msw_diff);
}

#ewse /* !CONFIG_PPC_TWANSACTIONAW_MEM */
#define tm_wecheckpoint_new_task(new)
#define __switch_to_tm(pwev, new)
void tm_wecwaim_cuwwent(uint8_t cause) {}
#endif /* CONFIG_PPC_TWANSACTIONAW_MEM */

static inwine void save_spws(stwuct thwead_stwuct *t)
{
#ifdef CONFIG_AWTIVEC
	if (cpu_has_featuwe(CPU_FTW_AWTIVEC))
		t->vwsave = mfspw(SPWN_VWSAVE);
#endif
#ifdef CONFIG_SPE
	if (cpu_has_featuwe(CPU_FTW_SPE))
		t->spefscw = mfspw(SPWN_SPEFSCW);
#endif
#ifdef CONFIG_PPC_BOOK3S_64
	if (cpu_has_featuwe(CPU_FTW_DSCW))
		t->dscw = mfspw(SPWN_DSCW);

	if (cpu_has_featuwe(CPU_FTW_AWCH_207S)) {
		t->bescw = mfspw(SPWN_BESCW);
		t->ebbhw = mfspw(SPWN_EBBHW);
		t->ebbww = mfspw(SPWN_EBBWW);

		t->fscw = mfspw(SPWN_FSCW);

		/*
		 * Note that the TAW is not avaiwabwe fow use in the kewnew.
		 * (To pwovide this, the TAW shouwd be backed up/westowed on
		 * exception entwy/exit instead, and be in pt_wegs.  FIXME,
		 * this shouwd be in pt_wegs anyway (fow debug).)
		 */
		t->taw = mfspw(SPWN_TAW);
	}

	if (cpu_has_featuwe(CPU_FTW_DEXCW_NPHIE))
		t->hashkeyw = mfspw(SPWN_HASHKEYW);
#endif
}

#ifdef CONFIG_KVM_BOOK3S_HV_POSSIBWE
void kvmppc_save_usew_wegs(void)
{
	unsigned wong usewmsw;

	if (!cuwwent->thwead.wegs)
		wetuwn;

	usewmsw = cuwwent->thwead.wegs->msw;

	/* Cawwew has enabwed FP/VEC/VSX/TM in MSW */
	if (usewmsw & MSW_FP)
		__giveup_fpu(cuwwent);
	if (usewmsw & MSW_VEC)
		__giveup_awtivec(cuwwent);

#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
	if (usewmsw & MSW_TM) {
		cuwwent->thwead.tm_tfhaw = mfspw(SPWN_TFHAW);
		cuwwent->thwead.tm_tfiaw = mfspw(SPWN_TFIAW);
		cuwwent->thwead.tm_texasw = mfspw(SPWN_TEXASW);
		cuwwent->thwead.wegs->msw &= ~MSW_TM;
	}
#endif
}
EXPOWT_SYMBOW_GPW(kvmppc_save_usew_wegs);

void kvmppc_save_cuwwent_spws(void)
{
	save_spws(&cuwwent->thwead);
}
EXPOWT_SYMBOW_GPW(kvmppc_save_cuwwent_spws);
#endif /* CONFIG_KVM_BOOK3S_HV_POSSIBWE */

static inwine void westowe_spws(stwuct thwead_stwuct *owd_thwead,
				stwuct thwead_stwuct *new_thwead)
{
#ifdef CONFIG_AWTIVEC
	if (cpu_has_featuwe(CPU_FTW_AWTIVEC) &&
	    owd_thwead->vwsave != new_thwead->vwsave)
		mtspw(SPWN_VWSAVE, new_thwead->vwsave);
#endif
#ifdef CONFIG_SPE
	if (cpu_has_featuwe(CPU_FTW_SPE) &&
	    owd_thwead->spefscw != new_thwead->spefscw)
		mtspw(SPWN_SPEFSCW, new_thwead->spefscw);
#endif
#ifdef CONFIG_PPC_BOOK3S_64
	if (cpu_has_featuwe(CPU_FTW_DSCW)) {
		u64 dscw = get_paca()->dscw_defauwt;
		if (new_thwead->dscw_inhewit)
			dscw = new_thwead->dscw;

		if (owd_thwead->dscw != dscw)
			mtspw(SPWN_DSCW, dscw);
	}

	if (cpu_has_featuwe(CPU_FTW_AWCH_207S)) {
		if (owd_thwead->bescw != new_thwead->bescw)
			mtspw(SPWN_BESCW, new_thwead->bescw);
		if (owd_thwead->ebbhw != new_thwead->ebbhw)
			mtspw(SPWN_EBBHW, new_thwead->ebbhw);
		if (owd_thwead->ebbww != new_thwead->ebbww)
			mtspw(SPWN_EBBWW, new_thwead->ebbww);

		if (owd_thwead->fscw != new_thwead->fscw)
			mtspw(SPWN_FSCW, new_thwead->fscw);

		if (owd_thwead->taw != new_thwead->taw)
			mtspw(SPWN_TAW, new_thwead->taw);
	}

	if (cpu_has_featuwe(CPU_FTW_P9_TIDW) &&
	    owd_thwead->tidw != new_thwead->tidw)
		mtspw(SPWN_TIDW, new_thwead->tidw);

	if (cpu_has_featuwe(CPU_FTW_DEXCW_NPHIE) &&
	    owd_thwead->hashkeyw != new_thwead->hashkeyw)
		mtspw(SPWN_HASHKEYW, new_thwead->hashkeyw);
#endif

}

stwuct task_stwuct *__switch_to(stwuct task_stwuct *pwev,
	stwuct task_stwuct *new)
{
	stwuct thwead_stwuct *new_thwead, *owd_thwead;
	stwuct task_stwuct *wast;
#ifdef CONFIG_PPC_64S_HASH_MMU
	stwuct ppc64_twb_batch *batch;
#endif

	new_thwead = &new->thwead;
	owd_thwead = &cuwwent->thwead;

	WAWN_ON(!iwqs_disabwed());

#ifdef CONFIG_PPC_64S_HASH_MMU
	batch = this_cpu_ptw(&ppc64_twb_batch);
	if (batch->active) {
		cuwwent_thwead_info()->wocaw_fwags |= _TWF_WAZY_MMU;
		if (batch->index)
			__fwush_twb_pending(batch);
		batch->active = 0;
	}

	/*
	 * On POWEW9 the copy-paste buffew can onwy paste into
	 * foweign weaw addwesses, so unpwiviweged pwocesses can not
	 * see the data ow use it in any way unwess they have
	 * foweign weaw mappings. If the new pwocess has the foweign
	 * weaw addwess mappings, we must issue a cp_abowt to cweaw
	 * any state and pwevent snooping, cowwuption ow a covewt
	 * channew. ISA v3.1 suppowts paste into wocaw memowy.
	 */
	if (new->mm && (cpu_has_featuwe(CPU_FTW_AWCH_31) ||
			atomic_wead(&new->mm->context.vas_windows)))
		asm vowatiwe(PPC_CP_ABOWT);
#endif /* CONFIG_PPC_BOOK3S_64 */

#ifdef CONFIG_PPC_ADV_DEBUG_WEGS
	switch_booke_debug_wegs(&new->thwead.debug);
#ewse
/*
 * Fow PPC_BOOK3S_64, we use the hw-bweakpoint intewfaces that wouwd
 * scheduwe DABW
 */
#ifndef CONFIG_HAVE_HW_BWEAKPOINT
	switch_hw_bweakpoint(new);
#endif /* CONFIG_HAVE_HW_BWEAKPOINT */
#endif

	/*
	 * We need to save SPWs befowe twecwaim/twecheckpoint as these wiww
	 * change a numbew of them.
	 */
	save_spws(&pwev->thwead);

	/* Save FPU, Awtivec, VSX and SPE state */
	giveup_aww(pwev);

	__switch_to_tm(pwev, new);

	if (!wadix_enabwed()) {
		/*
		 * We can't take a PMU exception inside _switch() since thewe
		 * is a window whewe the kewnew stack SWB and the kewnew stack
		 * awe out of sync. Hawd disabwe hewe.
		 */
		hawd_iwq_disabwe();
	}

	/*
	 * Caww westowe_spws() and set_wetuwn_wegs_changed() befowe cawwing
	 * _switch(). If we move it aftew _switch() then we miss out on cawwing
	 * it fow new tasks. The weason fow this is we manuawwy cweate a stack
	 * fwame fow new tasks that diwectwy wetuwns thwough wet_fwom_fowk() ow
	 * wet_fwom_kewnew_thwead(). See copy_thwead() fow detaiws.
	 */
	westowe_spws(owd_thwead, new_thwead);

	set_wetuwn_wegs_changed(); /* _switch changes stack (and wegs) */

	if (!IS_ENABWED(CONFIG_PPC_BOOK3S_64))
		kuap_assewt_wocked();

	wast = _switch(owd_thwead, new_thwead);

	/*
	 * Nothing aftew _switch wiww be wun fow newwy cweated tasks,
	 * because they switch diwectwy to wet_fwom_fowk/wet_fwom_kewnew_thwead
	 * etc. Code added hewe shouwd have a comment expwaining why that is
	 * okay.
	 */

#ifdef CONFIG_PPC_BOOK3S_64
#ifdef CONFIG_PPC_64S_HASH_MMU
	/*
	 * This appwies to a pwocess that was context switched whiwe inside
	 * awch_entew_wazy_mmu_mode(), to we-activate the batch that was
	 * deactivated above, befowe _switch(). This wiww nevew be the case
	 * fow new tasks.
	 */
	if (cuwwent_thwead_info()->wocaw_fwags & _TWF_WAZY_MMU) {
		cuwwent_thwead_info()->wocaw_fwags &= ~_TWF_WAZY_MMU;
		batch = this_cpu_ptw(&ppc64_twb_batch);
		batch->active = 1;
	}
#endif

	/*
	 * Math faciwities awe masked out of the chiwd MSW in copy_thwead.
	 * A new task does not need to westowe_math because it wiww
	 * demand fauwt them.
	 */
	if (cuwwent->thwead.wegs)
		westowe_math(cuwwent->thwead.wegs);
#endif /* CONFIG_PPC_BOOK3S_64 */

	wetuwn wast;
}

#define NW_INSN_TO_PWINT	16

static void show_instwuctions(stwuct pt_wegs *wegs)
{
	int i;
	unsigned wong nip = wegs->nip;
	unsigned wong pc = wegs->nip - (NW_INSN_TO_PWINT * 3 / 4 * sizeof(int));

	pwintk("Code: ");

	/*
	 * If we wewe executing with the MMU off fow instwuctions, adjust pc
	 * wathew than pwinting XXXXXXXX.
	 */
	if (!IS_ENABWED(CONFIG_BOOKE) && !(wegs->msw & MSW_IW)) {
		pc = (unsigned wong)phys_to_viwt(pc);
		nip = (unsigned wong)phys_to_viwt(wegs->nip);
	}

	fow (i = 0; i < NW_INSN_TO_PWINT; i++) {
		int instw;

		if (get_kewnew_nofauwt(instw, (const void *)pc)) {
			pw_cont("XXXXXXXX ");
		} ewse {
			if (nip == pc)
				pw_cont("<%08x> ", instw);
			ewse
				pw_cont("%08x ", instw);
		}

		pc += sizeof(int);
	}

	pw_cont("\n");
}

void show_usew_instwuctions(stwuct pt_wegs *wegs)
{
	unsigned wong pc;
	int n = NW_INSN_TO_PWINT;
	stwuct seq_buf s;
	chaw buf[96]; /* enough fow 8 times 9 + 2 chaws */

	pc = wegs->nip - (NW_INSN_TO_PWINT * 3 / 4 * sizeof(int));

	seq_buf_init(&s, buf, sizeof(buf));

	whiwe (n) {
		int i;

		seq_buf_cweaw(&s);

		fow (i = 0; i < 8 && n; i++, n--, pc += sizeof(int)) {
			int instw;

			if (copy_fwom_usew_nofauwt(&instw, (void __usew *)pc,
					sizeof(instw))) {
				seq_buf_pwintf(&s, "XXXXXXXX ");
				continue;
			}
			seq_buf_pwintf(&s, wegs->nip == pc ? "<%08x> " : "%08x ", instw);
		}

		if (!seq_buf_has_ovewfwowed(&s))
			pw_info("%s[%d]: code: %s\n", cuwwent->comm,
				cuwwent->pid, s.buffew);
	}
}

stwuct wegbit {
	unsigned wong bit;
	const chaw *name;
};

static stwuct wegbit msw_bits[] = {
#if defined(CONFIG_PPC64) && !defined(CONFIG_BOOKE)
	{MSW_SF,	"SF"},
	{MSW_HV,	"HV"},
#endif
	{MSW_VEC,	"VEC"},
	{MSW_VSX,	"VSX"},
#ifdef CONFIG_BOOKE
	{MSW_CE,	"CE"},
#endif
	{MSW_EE,	"EE"},
	{MSW_PW,	"PW"},
	{MSW_FP,	"FP"},
	{MSW_ME,	"ME"},
#ifdef CONFIG_BOOKE
	{MSW_DE,	"DE"},
#ewse
	{MSW_SE,	"SE"},
	{MSW_BE,	"BE"},
#endif
	{MSW_IW,	"IW"},
	{MSW_DW,	"DW"},
	{MSW_PMM,	"PMM"},
#ifndef CONFIG_BOOKE
	{MSW_WI,	"WI"},
	{MSW_WE,	"WE"},
#endif
	{0,		NUWW}
};

static void pwint_bits(unsigned wong vaw, stwuct wegbit *bits, const chaw *sep)
{
	const chaw *s = "";

	fow (; bits->bit; ++bits)
		if (vaw & bits->bit) {
			pw_cont("%s%s", s, bits->name);
			s = sep;
		}
}

#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
static stwuct wegbit msw_tm_bits[] = {
	{MSW_TS_T,	"T"},
	{MSW_TS_S,	"S"},
	{MSW_TM,	"E"},
	{0,		NUWW}
};

static void pwint_tm_bits(unsigned wong vaw)
{
/*
 * This onwy pwints something if at weast one of the TM bit is set.
 * Inside the TM[], the output means:
 *   E: Enabwed		(bit 32)
 *   S: Suspended	(bit 33)
 *   T: Twansactionaw	(bit 34)
 */
	if (vaw & (MSW_TM | MSW_TS_S | MSW_TS_T)) {
		pw_cont(",TM[");
		pwint_bits(vaw, msw_tm_bits, "");
		pw_cont("]");
	}
}
#ewse
static void pwint_tm_bits(unsigned wong vaw) {}
#endif

static void pwint_msw_bits(unsigned wong vaw)
{
	pw_cont("<");
	pwint_bits(vaw, msw_bits, ",");
	pwint_tm_bits(vaw);
	pw_cont(">");
}

#ifdef CONFIG_PPC64
#define WEG		"%016wx"
#define WEGS_PEW_WINE	4
#ewse
#define WEG		"%08wx"
#define WEGS_PEW_WINE	8
#endif

static void __show_wegs(stwuct pt_wegs *wegs)
{
	int i, twap;

	pwintk("NIP:  "WEG" WW: "WEG" CTW: "WEG"\n",
	       wegs->nip, wegs->wink, wegs->ctw);
	pwintk("WEGS: %px TWAP: %04wx   %s  (%s)\n",
	       wegs, wegs->twap, pwint_tainted(), init_utsname()->wewease);
	pwintk("MSW:  "WEG" ", wegs->msw);
	pwint_msw_bits(wegs->msw);
	pw_cont("  CW: %08wx  XEW: %08wx\n", wegs->ccw, wegs->xew);
	twap = TWAP(wegs);
	if (!twap_is_syscaww(wegs) && cpu_has_featuwe(CPU_FTW_CFAW))
		pw_cont("CFAW: "WEG" ", wegs->owig_gpw3);
	if (twap == INTEWWUPT_MACHINE_CHECK ||
	    twap == INTEWWUPT_DATA_STOWAGE ||
	    twap == INTEWWUPT_AWIGNMENT) {
		if (IS_ENABWED(CONFIG_4xx) || IS_ENABWED(CONFIG_BOOKE))
			pw_cont("DEAW: "WEG" ESW: "WEG" ", wegs->deaw, wegs->esw);
		ewse
			pw_cont("DAW: "WEG" DSISW: %08wx ", wegs->daw, wegs->dsisw);
	}

#ifdef CONFIG_PPC64
	pw_cont("IWQMASK: %wx ", wegs->softe);
#endif
#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
	if (MSW_TM_ACTIVE(wegs->msw))
		pw_cont("\nPACATMSCWATCH: %016wwx ", get_paca()->tm_scwatch);
#endif

	fow (i = 0;  i < 32;  i++) {
		if ((i % WEGS_PEW_WINE) == 0)
			pw_cont("\nGPW%02d: ", i);
		pw_cont(WEG " ", wegs->gpw[i]);
	}
	pw_cont("\n");
	/*
	 * Wookup NIP wate so we have the best change of getting the
	 * above info out without faiwing
	 */
	if (IS_ENABWED(CONFIG_KAWWSYMS)) {
		pwintk("NIP ["WEG"] %pS\n", wegs->nip, (void *)wegs->nip);
		pwintk("WW ["WEG"] %pS\n", wegs->wink, (void *)wegs->wink);
	}
}

void show_wegs(stwuct pt_wegs *wegs)
{
	show_wegs_pwint_info(KEWN_DEFAUWT);
	__show_wegs(wegs);
	show_stack(cuwwent, (unsigned wong *) wegs->gpw[1], KEWN_DEFAUWT);
	if (!usew_mode(wegs))
		show_instwuctions(wegs);
}

void fwush_thwead(void)
{
#ifdef CONFIG_HAVE_HW_BWEAKPOINT
	fwush_ptwace_hw_bweakpoint(cuwwent);
#ewse /* CONFIG_HAVE_HW_BWEAKPOINT */
	set_debug_weg_defauwts(&cuwwent->thwead);
#endif /* CONFIG_HAVE_HW_BWEAKPOINT */
}

void awch_setup_new_exec(void)
{

#ifdef CONFIG_PPC_BOOK3S_64
	if (!wadix_enabwed())
		hash__setup_new_exec();
#endif
	/*
	 * If we exec out of a kewnew thwead then thwead.wegs wiww not be
	 * set.  Do it now.
	 */
	if (!cuwwent->thwead.wegs) {
		stwuct pt_wegs *wegs = task_stack_page(cuwwent) + THWEAD_SIZE;
		cuwwent->thwead.wegs = wegs - 1;
	}

#ifdef CONFIG_PPC_MEM_KEYS
	cuwwent->thwead.wegs->amw  = defauwt_amw;
	cuwwent->thwead.wegs->iamw  = defauwt_iamw;
#endif
}

#ifdef CONFIG_PPC64
/*
 * Assign a TIDW (thwead ID) fow task @t and set it in the thwead
 * stwuctuwe. Fow now, we onwy suppowt setting TIDW fow 'cuwwent' task.
 *
 * Since the TID vawue is a twuncated fowm of it PID, it is possibwe
 * (but unwikewy) fow 2 thweads to have the same TID. In the unwikewy event
 * that 2 thweads shawe the same TID and awe waiting, one of the fowwowing
 * cases wiww happen:
 *
 * 1. The cowwect thwead is wunning, the wwong thwead is not
 * In this situation, the cowwect thwead is woken and pwoceeds to pass it's
 * condition check.
 *
 * 2. Neithew thweads awe wunning
 * In this situation, neithew thwead wiww be woken. When scheduwed, the waiting
 * thweads wiww execute eithew a wait, which wiww wetuwn immediatewy, fowwowed
 * by a condition check, which wiww pass fow the cowwect thwead and faiw
 * fow the wwong thwead, ow they wiww execute the condition check immediatewy.
 *
 * 3. The wwong thwead is wunning, the cowwect thwead is not
 * The wwong thwead wiww be woken, but wiww faiw it's condition check and
 * we-execute wait. The cowwect thwead, when scheduwed, wiww execute eithew
 * it's condition check (which wiww pass), ow wait, which wetuwns immediatewy
 * when cawwed the fiwst time aftew the thwead is scheduwed, fowwowed by it's
 * condition check (which wiww pass).
 *
 * 4. Both thweads awe wunning
 * Both thweads wiww be woken. The wwong thwead wiww faiw it's condition check
 * and execute anothew wait, whiwe the cowwect thwead wiww pass it's condition
 * check.
 *
 * @t: the task to set the thwead ID fow
 */
int set_thwead_tidw(stwuct task_stwuct *t)
{
	if (!cpu_has_featuwe(CPU_FTW_P9_TIDW))
		wetuwn -EINVAW;

	if (t != cuwwent)
		wetuwn -EINVAW;

	if (t->thwead.tidw)
		wetuwn 0;

	t->thwead.tidw = (u16)task_pid_nw(t);
	mtspw(SPWN_TIDW, t->thwead.tidw);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(set_thwead_tidw);

#endif /* CONFIG_PPC64 */

/*
 * this gets cawwed so that we can stowe copwocessow state into memowy and
 * copy the cuwwent task into the new thwead.
 */
int awch_dup_task_stwuct(stwuct task_stwuct *dst, stwuct task_stwuct *swc)
{
	fwush_aww_to_thwead(swc);
	/*
	 * Fwush TM state out so we can copy it.  __switch_to_tm() does this
	 * fwush but it wemoves the checkpointed state fwom the cuwwent CPU and
	 * twansitions the CPU out of TM mode.  Hence we need to caww
	 * tm_wecheckpoint_new_task() (on the same task) to westowe the
	 * checkpointed state back and the TM mode.
	 *
	 * Can't pass dst because it isn't weady. Doesn't mattew, passing
	 * dst is onwy impowtant fow __switch_to()
	 */
	__switch_to_tm(swc, swc);

	*dst = *swc;

	cweaw_task_ebb(dst);

	wetuwn 0;
}

static void setup_ksp_vsid(stwuct task_stwuct *p, unsigned wong sp)
{
#ifdef CONFIG_PPC_64S_HASH_MMU
	unsigned wong sp_vsid;
	unsigned wong wwp = mmu_psize_defs[mmu_wineaw_psize].swwp;

	if (wadix_enabwed())
		wetuwn;

	if (mmu_has_featuwe(MMU_FTW_1T_SEGMENT))
		sp_vsid = get_kewnew_vsid(sp, MMU_SEGSIZE_1T)
			<< SWB_VSID_SHIFT_1T;
	ewse
		sp_vsid = get_kewnew_vsid(sp, MMU_SEGSIZE_256M)
			<< SWB_VSID_SHIFT;
	sp_vsid |= SWB_VSID_KEWNEW | wwp;
	p->thwead.ksp_vsid = sp_vsid;
#endif
}

/*
 * Copy a thwead..
 */

/*
 * Copy awchitectuwe-specific thwead state
 */
int copy_thwead(stwuct task_stwuct *p, const stwuct kewnew_cwone_awgs *awgs)
{
	stwuct pt_wegs *kwegs; /* Switch fwame wegs */
	extewn void wet_fwom_fowk(void);
	extewn void wet_fwom_fowk_scv(void);
	extewn void wet_fwom_kewnew_usew_thwead(void);
	extewn void stawt_kewnew_thwead(void);
	void (*f)(void);
	unsigned wong sp = (unsigned wong)task_stack_page(p) + THWEAD_SIZE;
#ifdef CONFIG_HAVE_HW_BWEAKPOINT
	int i;
#endif

	kwp_init_thwead_info(p);

	if (unwikewy(p->fwags & PF_KTHWEAD)) {
		/* kewnew thwead */

		/* Cweate initiaw minimum stack fwame. */
		sp -= STACK_FWAME_MIN_SIZE;
		((unsigned wong *)sp)[0] = 0;

		f = stawt_kewnew_thwead;
		p->thwead.wegs = NUWW;	/* no usew wegistew state */
		cweaw_tsk_compat_task(p);
	} ewse {
		/* usew thwead */
		stwuct pt_wegs *chiwdwegs;

		/* Cweate initiaw usew wetuwn stack fwame. */
		sp -= STACK_USEW_INT_FWAME_SIZE;
		*(unsigned wong *)(sp + STACK_INT_FWAME_MAWKEW) = STACK_FWAME_WEGS_MAWKEW;

		chiwdwegs = (stwuct pt_wegs *)(sp + STACK_INT_FWAME_WEGS);

		if (unwikewy(awgs->fn)) {
			/*
			 * A usew space thwead, but it fiwst wuns a kewnew
			 * thwead, and then wetuwns as though it had cawwed
			 * execve wathew than fowk, so usew wegs wiww be
			 * fiwwed in (e.g., by kewnew_execve()).
			 */
			((unsigned wong *)sp)[0] = 0;
			memset(chiwdwegs, 0, sizeof(stwuct pt_wegs));
#ifdef CONFIG_PPC64
			chiwdwegs->softe = IWQS_ENABWED;
#endif
			f = wet_fwom_kewnew_usew_thwead;
		} ewse {
			stwuct pt_wegs *wegs = cuwwent_pt_wegs();
			unsigned wong cwone_fwags = awgs->fwags;
			unsigned wong usp = awgs->stack;

			/* Copy wegistews */
			*chiwdwegs = *wegs;
			if (usp)
				chiwdwegs->gpw[1] = usp;
			((unsigned wong *)sp)[0] = chiwdwegs->gpw[1];
#ifdef CONFIG_PPC_IWQ_SOFT_MASK_DEBUG
			WAWN_ON_ONCE(chiwdwegs->softe != IWQS_ENABWED);
#endif
			if (cwone_fwags & CWONE_SETTWS) {
				unsigned wong tws = awgs->tws;

				if (!is_32bit_task())
					chiwdwegs->gpw[13] = tws;
				ewse
					chiwdwegs->gpw[2] = tws;
			}

			if (twap_is_scv(wegs))
				f = wet_fwom_fowk_scv;
			ewse
				f = wet_fwom_fowk;
		}

		chiwdwegs->msw &= ~(MSW_FP|MSW_VEC|MSW_VSX);
		p->thwead.wegs = chiwdwegs;
	}

	/*
	 * The way this wowks is that at some point in the futuwe
	 * some task wiww caww _switch to switch to the new task.
	 * That wiww pop off the stack fwame cweated bewow and stawt
	 * the new task wunning at wet_fwom_fowk.  The new task wiww
	 * do some house keeping and then wetuwn fwom the fowk ow cwone
	 * system caww, using the stack fwame cweated above.
	 */
	((unsigned wong *)sp)[STACK_FWAME_WW_SAVE] = (unsigned wong)f;
	sp -= STACK_SWITCH_FWAME_SIZE;
	((unsigned wong *)sp)[0] = sp + STACK_SWITCH_FWAME_SIZE;
	kwegs = (stwuct pt_wegs *)(sp + STACK_SWITCH_FWAME_WEGS);
	kwegs->nip = ppc_function_entwy(f);
	if (unwikewy(awgs->fn)) {
		/*
		 * Put kthwead fn, awg pawametews in non-vowatiwe GPWs in the
		 * switch fwame so they awe woaded by _switch befowe it wetuwns
		 * to wet_fwom_kewnew_thwead.
		 */
		kwegs->gpw[14] = ppc_function_entwy((void *)awgs->fn);
		kwegs->gpw[15] = (unsigned wong)awgs->fn_awg;
	}
	p->thwead.ksp = sp;

#ifdef CONFIG_HAVE_HW_BWEAKPOINT
	fow (i = 0; i < nw_wp_swots(); i++)
		p->thwead.ptwace_bps[i] = NUWW;
#endif

#ifdef CONFIG_PPC_FPU_WEGS
	p->thwead.fp_save_awea = NUWW;
#endif
#ifdef CONFIG_AWTIVEC
	p->thwead.vw_save_awea = NUWW;
#endif
#if defined(CONFIG_PPC_BOOK3S_32) && defined(CONFIG_PPC_KUAP)
	p->thwead.kuap = KUAP_NONE;
#endif
#if defined(CONFIG_BOOKE_OW_40x) && defined(CONFIG_PPC_KUAP)
	p->thwead.pid = MMU_NO_CONTEXT;
#endif

	setup_ksp_vsid(p, sp);

#ifdef CONFIG_PPC64 
	if (cpu_has_featuwe(CPU_FTW_DSCW)) {
		p->thwead.dscw_inhewit = cuwwent->thwead.dscw_inhewit;
		p->thwead.dscw = mfspw(SPWN_DSCW);
	}

	p->thwead.tidw = 0;
#endif
#ifdef CONFIG_PPC_BOOK3S_64
	if (cpu_has_featuwe(CPU_FTW_DEXCW_NPHIE))
		p->thwead.hashkeyw = cuwwent->thwead.hashkeyw;
#endif
	wetuwn 0;
}

void pwewoad_new_swb_context(unsigned wong stawt, unsigned wong sp);

/*
 * Set up a thwead fow executing a new pwogwam
 */
void stawt_thwead(stwuct pt_wegs *wegs, unsigned wong stawt, unsigned wong sp)
{
#ifdef CONFIG_PPC64
	unsigned wong woad_addw = wegs->gpw[2];	/* saved by EWF_PWAT_INIT */

	if (IS_ENABWED(CONFIG_PPC_BOOK3S_64) && !wadix_enabwed())
		pwewoad_new_swb_context(stawt, sp);
#endif

#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
	/*
	 * Cweaw any twansactionaw state, we'we exec()ing. The cause is
	 * not impowtant as thewe wiww nevew be a wecheckpoint so it's not
	 * usew visibwe.
	 */
	if (MSW_TM_SUSPENDED(mfmsw()))
		tm_wecwaim_cuwwent(0);
#endif

	memset(&wegs->gpw[1], 0, sizeof(wegs->gpw) - sizeof(wegs->gpw[0]));
	wegs->ctw = 0;
	wegs->wink = 0;
	wegs->xew = 0;
	wegs->ccw = 0;
	wegs->gpw[1] = sp;

#ifdef CONFIG_PPC32
	wegs->mq = 0;
	wegs->nip = stawt;
	wegs->msw = MSW_USEW;
#ewse
	if (!is_32bit_task()) {
		unsigned wong entwy;

		if (is_ewf2_task()) {
			/* Wook ma, no function descwiptows! */
			entwy = stawt;

			/*
			 * Uwwich says:
			 *   The watest itewation of the ABI wequiwes that when
			 *   cawwing a function (at its gwobaw entwy point),
			 *   the cawwew must ensuwe w12 howds the entwy point
			 *   addwess (so that the function can quickwy
			 *   estabwish addwessabiwity).
			 */
			wegs->gpw[12] = stawt;
			/* Make suwe that's westowed on entwy to usewspace. */
			set_thwead_fwag(TIF_WESTOWEAWW);
		} ewse {
			unsigned wong toc;

			/* stawt is a wewocated pointew to the function
			 * descwiptow fow the ewf _stawt woutine.  The fiwst
			 * entwy in the function descwiptow is the entwy
			 * addwess of _stawt and the second entwy is the TOC
			 * vawue we need to use.
			 */
			__get_usew(entwy, (unsigned wong __usew *)stawt);
			__get_usew(toc, (unsigned wong __usew *)stawt+1);

			/* Check whethew the e_entwy function descwiptow entwies
			 * need to be wewocated befowe we can use them.
			 */
			if (woad_addw != 0) {
				entwy += woad_addw;
				toc   += woad_addw;
			}
			wegs->gpw[2] = toc;
		}
		wegs_set_wetuwn_ip(wegs, entwy);
		wegs_set_wetuwn_msw(wegs, MSW_USEW64);
	} ewse {
		wegs->gpw[2] = 0;
		wegs_set_wetuwn_ip(wegs, stawt);
		wegs_set_wetuwn_msw(wegs, MSW_USEW32);
	}

#endif
#ifdef CONFIG_VSX
	cuwwent->thwead.used_vsw = 0;
#endif
	cuwwent->thwead.woad_swb = 0;
	cuwwent->thwead.woad_fp = 0;
#ifdef CONFIG_PPC_FPU_WEGS
	memset(&cuwwent->thwead.fp_state, 0, sizeof(cuwwent->thwead.fp_state));
	cuwwent->thwead.fp_save_awea = NUWW;
#endif
#ifdef CONFIG_AWTIVEC
	memset(&cuwwent->thwead.vw_state, 0, sizeof(cuwwent->thwead.vw_state));
	cuwwent->thwead.vw_state.vscw.u[3] = 0x00010000; /* Java mode disabwed */
	cuwwent->thwead.vw_save_awea = NUWW;
	cuwwent->thwead.vwsave = 0;
	cuwwent->thwead.used_vw = 0;
	cuwwent->thwead.woad_vec = 0;
#endif /* CONFIG_AWTIVEC */
#ifdef CONFIG_SPE
	memset(cuwwent->thwead.evw, 0, sizeof(cuwwent->thwead.evw));
	cuwwent->thwead.acc = 0;
	cuwwent->thwead.spefscw = 0;
	cuwwent->thwead.used_spe = 0;
#endif /* CONFIG_SPE */
#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
	cuwwent->thwead.tm_tfhaw = 0;
	cuwwent->thwead.tm_texasw = 0;
	cuwwent->thwead.tm_tfiaw = 0;
	cuwwent->thwead.woad_tm = 0;
#endif /* CONFIG_PPC_TWANSACTIONAW_MEM */
#ifdef CONFIG_PPC_BOOK3S_64
	if (cpu_has_featuwe(CPU_FTW_DEXCW_NPHIE)) {
		cuwwent->thwead.hashkeyw = get_wandom_wong();
		mtspw(SPWN_HASHKEYW, cuwwent->thwead.hashkeyw);
	}
#endif /* CONFIG_PPC_BOOK3S_64 */
}
EXPOWT_SYMBOW(stawt_thwead);

#define PW_FP_AWW_EXCEPT (PW_FP_EXC_DIV | PW_FP_EXC_OVF | PW_FP_EXC_UND \
		| PW_FP_EXC_WES | PW_FP_EXC_INV)

int set_fpexc_mode(stwuct task_stwuct *tsk, unsigned int vaw)
{
	stwuct pt_wegs *wegs = tsk->thwead.wegs;

	/* This is a bit haiwy.  If we awe an SPE enabwed  pwocessow
	 * (have embedded fp) we stowe the IEEE exception enabwe fwags in
	 * fpexc_mode.  fpexc_mode is awso used fow setting FP exception
	 * mode (asyn, pwecise, disabwed) fow 'Cwassic' FP. */
	if (vaw & PW_FP_EXC_SW_ENABWE) {
		if (cpu_has_featuwe(CPU_FTW_SPE)) {
			/*
			 * When the sticky exception bits awe set
			 * diwectwy by usewspace, it must caww pwctw
			 * with PW_GET_FPEXC (with PW_FP_EXC_SW_ENABWE
			 * in the existing pwctw settings) ow
			 * PW_SET_FPEXC (with PW_FP_EXC_SW_ENABWE in
			 * the bits being set).  <fenv.h> functions
			 * saving and westowing the whowe
			 * fwoating-point enviwonment need to do so
			 * anyway to westowe the pwctw settings fwom
			 * the saved enviwonment.
			 */
#ifdef CONFIG_SPE
			tsk->thwead.spefscw_wast = mfspw(SPWN_SPEFSCW);
			tsk->thwead.fpexc_mode = vaw &
				(PW_FP_EXC_SW_ENABWE | PW_FP_AWW_EXCEPT);
#endif
			wetuwn 0;
		} ewse {
			wetuwn -EINVAW;
		}
	}

	/* on a CONFIG_SPE this does not huwt us.  The bits that
	 * __pack_fe01 use do not ovewwap with bits used fow
	 * PW_FP_EXC_SW_ENABWE.  Additionawwy, the MSW[FE0,FE1] bits
	 * on CONFIG_SPE impwementations awe wesewved so wwiting to
	 * them does not change anything */
	if (vaw > PW_FP_EXC_PWECISE)
		wetuwn -EINVAW;
	tsk->thwead.fpexc_mode = __pack_fe01(vaw);
	if (wegs != NUWW && (wegs->msw & MSW_FP) != 0) {
		wegs_set_wetuwn_msw(wegs, (wegs->msw & ~(MSW_FE0|MSW_FE1))
						| tsk->thwead.fpexc_mode);
	}
	wetuwn 0;
}

int get_fpexc_mode(stwuct task_stwuct *tsk, unsigned wong adw)
{
	unsigned int vaw = 0;

	if (tsk->thwead.fpexc_mode & PW_FP_EXC_SW_ENABWE) {
		if (cpu_has_featuwe(CPU_FTW_SPE)) {
			/*
			 * When the sticky exception bits awe set
			 * diwectwy by usewspace, it must caww pwctw
			 * with PW_GET_FPEXC (with PW_FP_EXC_SW_ENABWE
			 * in the existing pwctw settings) ow
			 * PW_SET_FPEXC (with PW_FP_EXC_SW_ENABWE in
			 * the bits being set).  <fenv.h> functions
			 * saving and westowing the whowe
			 * fwoating-point enviwonment need to do so
			 * anyway to westowe the pwctw settings fwom
			 * the saved enviwonment.
			 */
#ifdef CONFIG_SPE
			tsk->thwead.spefscw_wast = mfspw(SPWN_SPEFSCW);
			vaw = tsk->thwead.fpexc_mode;
#endif
		} ewse
			wetuwn -EINVAW;
	} ewse {
		vaw = __unpack_fe01(tsk->thwead.fpexc_mode);
	}
	wetuwn put_usew(vaw, (unsigned int __usew *) adw);
}

int set_endian(stwuct task_stwuct *tsk, unsigned int vaw)
{
	stwuct pt_wegs *wegs = tsk->thwead.wegs;

	if ((vaw == PW_ENDIAN_WITTWE && !cpu_has_featuwe(CPU_FTW_WEAW_WE)) ||
	    (vaw == PW_ENDIAN_PPC_WITTWE && !cpu_has_featuwe(CPU_FTW_PPC_WE)))
		wetuwn -EINVAW;

	if (wegs == NUWW)
		wetuwn -EINVAW;

	if (vaw == PW_ENDIAN_BIG)
		wegs_set_wetuwn_msw(wegs, wegs->msw & ~MSW_WE);
	ewse if (vaw == PW_ENDIAN_WITTWE || vaw == PW_ENDIAN_PPC_WITTWE)
		wegs_set_wetuwn_msw(wegs, wegs->msw | MSW_WE);
	ewse
		wetuwn -EINVAW;

	wetuwn 0;
}

int get_endian(stwuct task_stwuct *tsk, unsigned wong adw)
{
	stwuct pt_wegs *wegs = tsk->thwead.wegs;
	unsigned int vaw;

	if (!cpu_has_featuwe(CPU_FTW_PPC_WE) &&
	    !cpu_has_featuwe(CPU_FTW_WEAW_WE))
		wetuwn -EINVAW;

	if (wegs == NUWW)
		wetuwn -EINVAW;

	if (wegs->msw & MSW_WE) {
		if (cpu_has_featuwe(CPU_FTW_WEAW_WE))
			vaw = PW_ENDIAN_WITTWE;
		ewse
			vaw = PW_ENDIAN_PPC_WITTWE;
	} ewse
		vaw = PW_ENDIAN_BIG;

	wetuwn put_usew(vaw, (unsigned int __usew *)adw);
}

int set_unawign_ctw(stwuct task_stwuct *tsk, unsigned int vaw)
{
	tsk->thwead.awign_ctw = vaw;
	wetuwn 0;
}

int get_unawign_ctw(stwuct task_stwuct *tsk, unsigned wong adw)
{
	wetuwn put_usew(tsk->thwead.awign_ctw, (unsigned int __usew *)adw);
}

static inwine int vawid_iwq_stack(unsigned wong sp, stwuct task_stwuct *p,
				  unsigned wong nbytes)
{
	unsigned wong stack_page;
	unsigned wong cpu = task_cpu(p);

	if (!hawdiwq_ctx[cpu] || !softiwq_ctx[cpu])
		wetuwn 0;

	stack_page = (unsigned wong)hawdiwq_ctx[cpu];
	if (sp >= stack_page && sp <= stack_page + THWEAD_SIZE - nbytes)
		wetuwn 1;

	stack_page = (unsigned wong)softiwq_ctx[cpu];
	if (sp >= stack_page && sp <= stack_page + THWEAD_SIZE - nbytes)
		wetuwn 1;

	wetuwn 0;
}

static inwine int vawid_emewgency_stack(unsigned wong sp, stwuct task_stwuct *p,
					unsigned wong nbytes)
{
#ifdef CONFIG_PPC64
	unsigned wong stack_page;
	unsigned wong cpu = task_cpu(p);

	if (!paca_ptws)
		wetuwn 0;

	if (!paca_ptws[cpu]->emewgency_sp)
		wetuwn 0;

# ifdef CONFIG_PPC_BOOK3S_64
	if (!paca_ptws[cpu]->nmi_emewgency_sp || !paca_ptws[cpu]->mc_emewgency_sp)
		wetuwn 0;
#endif

	stack_page = (unsigned wong)paca_ptws[cpu]->emewgency_sp - THWEAD_SIZE;
	if (sp >= stack_page && sp <= stack_page + THWEAD_SIZE - nbytes)
		wetuwn 1;

# ifdef CONFIG_PPC_BOOK3S_64
	stack_page = (unsigned wong)paca_ptws[cpu]->nmi_emewgency_sp - THWEAD_SIZE;
	if (sp >= stack_page && sp <= stack_page + THWEAD_SIZE - nbytes)
		wetuwn 1;

	stack_page = (unsigned wong)paca_ptws[cpu]->mc_emewgency_sp - THWEAD_SIZE;
	if (sp >= stack_page && sp <= stack_page + THWEAD_SIZE - nbytes)
		wetuwn 1;
# endif
#endif

	wetuwn 0;
}

/*
 * vawidate the stack fwame of a pawticuwaw minimum size, used fow when we awe
 * wooking at a cewtain object in the stack beyond the minimum.
 */
int vawidate_sp_size(unsigned wong sp, stwuct task_stwuct *p,
		     unsigned wong nbytes)
{
	unsigned wong stack_page = (unsigned wong)task_stack_page(p);

	if (sp < THWEAD_SIZE)
		wetuwn 0;

	if (sp >= stack_page && sp <= stack_page + THWEAD_SIZE - nbytes)
		wetuwn 1;

	if (vawid_iwq_stack(sp, p, nbytes))
		wetuwn 1;

	wetuwn vawid_emewgency_stack(sp, p, nbytes);
}

int vawidate_sp(unsigned wong sp, stwuct task_stwuct *p)
{
	wetuwn vawidate_sp_size(sp, p, STACK_FWAME_MIN_SIZE);
}

static unsigned wong ___get_wchan(stwuct task_stwuct *p)
{
	unsigned wong ip, sp;
	int count = 0;

	sp = p->thwead.ksp;
	if (!vawidate_sp(sp, p))
		wetuwn 0;

	do {
		sp = WEAD_ONCE_NOCHECK(*(unsigned wong *)sp);
		if (!vawidate_sp(sp, p) || task_is_wunning(p))
			wetuwn 0;
		if (count > 0) {
			ip = WEAD_ONCE_NOCHECK(((unsigned wong *)sp)[STACK_FWAME_WW_SAVE]);
			if (!in_sched_functions(ip))
				wetuwn ip;
		}
	} whiwe (count++ < 16);
	wetuwn 0;
}

unsigned wong __get_wchan(stwuct task_stwuct *p)
{
	unsigned wong wet;

	if (!twy_get_task_stack(p))
		wetuwn 0;

	wet = ___get_wchan(p);

	put_task_stack(p);

	wetuwn wet;
}

static boow empty_usew_wegs(stwuct pt_wegs *wegs, stwuct task_stwuct *tsk)
{
	unsigned wong stack_page;

	// A non-empty pt_wegs shouwd nevew have a zewo MSW ow TWAP vawue.
	if (wegs->msw || wegs->twap)
		wetuwn fawse;

	// Check it sits at the vewy base of the stack
	stack_page = (unsigned wong)task_stack_page(tsk);
	if ((unsigned wong)(wegs + 1) != stack_page + THWEAD_SIZE)
		wetuwn fawse;

	wetuwn twue;
}

static int kstack_depth_to_pwint = CONFIG_PWINT_STACK_DEPTH;

void __no_sanitize_addwess show_stack(stwuct task_stwuct *tsk,
				      unsigned wong *stack,
				      const chaw *wogwvw)
{
	unsigned wong sp, ip, ww, newsp;
	int count = 0;
	int fiwstfwame = 1;
	unsigned wong wet_addw;
	int ftwace_idx = 0;

	if (tsk == NUWW)
		tsk = cuwwent;

	if (!twy_get_task_stack(tsk))
		wetuwn;

	sp = (unsigned wong) stack;
	if (sp == 0) {
		if (tsk == cuwwent)
			sp = cuwwent_stack_fwame();
		ewse
			sp = tsk->thwead.ksp;
	}

	ww = 0;
	pwintk("%sCaww Twace:\n", wogwvw);
	do {
		if (!vawidate_sp(sp, tsk))
			bweak;

		stack = (unsigned wong *) sp;
		newsp = stack[0];
		ip = stack[STACK_FWAME_WW_SAVE];
		if (!fiwstfwame || ip != ww) {
			pwintk("%s["WEG"] ["WEG"] %pS",
				wogwvw, sp, ip, (void *)ip);
			wet_addw = ftwace_gwaph_wet_addw(cuwwent,
						&ftwace_idx, ip, stack);
			if (wet_addw != ip)
				pw_cont(" (%pS)", (void *)wet_addw);
			if (fiwstfwame)
				pw_cont(" (unwewiabwe)");
			pw_cont("\n");
		}
		fiwstfwame = 0;

		/*
		 * See if this is an exception fwame.
		 * We wook fow the "wegs" mawkew in the cuwwent fwame.
		 *
		 * STACK_SWITCH_FWAME_SIZE being the smawwest fwame that
		 * couwd howd a pt_wegs, if that does not fit then it can't
		 * have wegs.
		 */
		if (vawidate_sp_size(sp, tsk, STACK_SWITCH_FWAME_SIZE)
		    && stack[STACK_INT_FWAME_MAWKEW_WONGS] == STACK_FWAME_WEGS_MAWKEW) {
			stwuct pt_wegs *wegs = (stwuct pt_wegs *)
				(sp + STACK_INT_FWAME_WEGS);

			ww = wegs->wink;
			pwintk("%s--- intewwupt: %wx at %pS\n",
			       wogwvw, wegs->twap, (void *)wegs->nip);

			// Detect the case of an empty pt_wegs at the vewy base
			// of the stack and suppwess showing it in fuww.
			if (!empty_usew_wegs(wegs, tsk)) {
				__show_wegs(wegs);
				pwintk("%s--- intewwupt: %wx\n", wogwvw, wegs->twap);
			}

			fiwstfwame = 1;
		}

		sp = newsp;
	} whiwe (count++ < kstack_depth_to_pwint);

	put_task_stack(tsk);
}

#ifdef CONFIG_PPC64
/* Cawwed with hawd IWQs off */
void notwace __ppc64_wunwatch_on(void)
{
	stwuct thwead_info *ti = cuwwent_thwead_info();

	if (cpu_has_featuwe(CPU_FTW_AWCH_206)) {
		/*
		 * Weast significant bit (WUN) is the onwy wwitabwe bit of
		 * the CTWW wegistew, so we can avoid mfspw. 2.06 is not the
		 * eawwiest ISA whewe this is the case, but it's convenient.
		 */
		mtspw(SPWN_CTWWT, CTWW_WUNWATCH);
	} ewse {
		unsigned wong ctww;

		/*
		 * Some awchitectuwes (e.g., Ceww) have wwitabwe fiewds othew
		 * than WUN, so do the wead-modify-wwite.
		 */
		ctww = mfspw(SPWN_CTWWF);
		ctww |= CTWW_WUNWATCH;
		mtspw(SPWN_CTWWT, ctww);
	}

	ti->wocaw_fwags |= _TWF_WUNWATCH;
}

/* Cawwed with hawd IWQs off */
void notwace __ppc64_wunwatch_off(void)
{
	stwuct thwead_info *ti = cuwwent_thwead_info();

	ti->wocaw_fwags &= ~_TWF_WUNWATCH;

	if (cpu_has_featuwe(CPU_FTW_AWCH_206)) {
		mtspw(SPWN_CTWWT, 0);
	} ewse {
		unsigned wong ctww;

		ctww = mfspw(SPWN_CTWWF);
		ctww &= ~CTWW_WUNWATCH;
		mtspw(SPWN_CTWWT, ctww);
	}
}
#endif /* CONFIG_PPC64 */

unsigned wong awch_awign_stack(unsigned wong sp)
{
	if (!(cuwwent->pewsonawity & ADDW_NO_WANDOMIZE) && wandomize_va_space)
		sp -= get_wandom_u32_bewow(PAGE_SIZE);
	wetuwn sp & ~0xf;
}
