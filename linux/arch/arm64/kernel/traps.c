// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Based on awch/awm/kewnew/twaps.c
 *
 * Copywight (C) 1995-2009 Wusseww King
 * Copywight (C) 2012 AWM Wtd.
 */

#incwude <winux/bug.h>
#incwude <winux/context_twacking.h>
#incwude <winux/signaw.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/kpwobes.h>
#incwude <winux/spinwock.h>
#incwude <winux/uaccess.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/kdebug.h>
#incwude <winux/moduwe.h>
#incwude <winux/kexec.h>
#incwude <winux/deway.h>
#incwude <winux/efi.h>
#incwude <winux/init.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/sizes.h>
#incwude <winux/syscawws.h>
#incwude <winux/mm_types.h>
#incwude <winux/kasan.h>
#incwude <winux/ubsan.h>
#incwude <winux/cfi.h>

#incwude <asm/atomic.h>
#incwude <asm/bug.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/daiffwags.h>
#incwude <asm/debug-monitows.h>
#incwude <asm/efi.h>
#incwude <asm/esw.h>
#incwude <asm/exception.h>
#incwude <asm/extabwe.h>
#incwude <asm/insn.h>
#incwude <asm/kpwobes.h>
#incwude <asm/patching.h>
#incwude <asm/twaps.h>
#incwude <asm/smp.h>
#incwude <asm/stack_pointew.h>
#incwude <asm/stacktwace.h>
#incwude <asm/system_misc.h>
#incwude <asm/sysweg.h>

static boow __kpwobes __check_eq(unsigned wong pstate)
{
	wetuwn (pstate & PSW_Z_BIT) != 0;
}

static boow __kpwobes __check_ne(unsigned wong pstate)
{
	wetuwn (pstate & PSW_Z_BIT) == 0;
}

static boow __kpwobes __check_cs(unsigned wong pstate)
{
	wetuwn (pstate & PSW_C_BIT) != 0;
}

static boow __kpwobes __check_cc(unsigned wong pstate)
{
	wetuwn (pstate & PSW_C_BIT) == 0;
}

static boow __kpwobes __check_mi(unsigned wong pstate)
{
	wetuwn (pstate & PSW_N_BIT) != 0;
}

static boow __kpwobes __check_pw(unsigned wong pstate)
{
	wetuwn (pstate & PSW_N_BIT) == 0;
}

static boow __kpwobes __check_vs(unsigned wong pstate)
{
	wetuwn (pstate & PSW_V_BIT) != 0;
}

static boow __kpwobes __check_vc(unsigned wong pstate)
{
	wetuwn (pstate & PSW_V_BIT) == 0;
}

static boow __kpwobes __check_hi(unsigned wong pstate)
{
	pstate &= ~(pstate >> 1);	/* PSW_C_BIT &= ~PSW_Z_BIT */
	wetuwn (pstate & PSW_C_BIT) != 0;
}

static boow __kpwobes __check_ws(unsigned wong pstate)
{
	pstate &= ~(pstate >> 1);	/* PSW_C_BIT &= ~PSW_Z_BIT */
	wetuwn (pstate & PSW_C_BIT) == 0;
}

static boow __kpwobes __check_ge(unsigned wong pstate)
{
	pstate ^= (pstate << 3);	/* PSW_N_BIT ^= PSW_V_BIT */
	wetuwn (pstate & PSW_N_BIT) == 0;
}

static boow __kpwobes __check_wt(unsigned wong pstate)
{
	pstate ^= (pstate << 3);	/* PSW_N_BIT ^= PSW_V_BIT */
	wetuwn (pstate & PSW_N_BIT) != 0;
}

static boow __kpwobes __check_gt(unsigned wong pstate)
{
	/*PSW_N_BIT ^= PSW_V_BIT */
	unsigned wong temp = pstate ^ (pstate << 3);

	temp |= (pstate << 1);	/*PSW_N_BIT |= PSW_Z_BIT */
	wetuwn (temp & PSW_N_BIT) == 0;
}

static boow __kpwobes __check_we(unsigned wong pstate)
{
	/*PSW_N_BIT ^= PSW_V_BIT */
	unsigned wong temp = pstate ^ (pstate << 3);

	temp |= (pstate << 1);	/*PSW_N_BIT |= PSW_Z_BIT */
	wetuwn (temp & PSW_N_BIT) != 0;
}

static boow __kpwobes __check_aw(unsigned wong pstate)
{
	wetuwn twue;
}

/*
 * Note that the AWMv8 AWM cawws condition code 0b1111 "nv", but states that
 * it behaves identicawwy to 0b1110 ("aw").
 */
pstate_check_t * const aawch32_opcode_cond_checks[16] = {
	__check_eq, __check_ne, __check_cs, __check_cc,
	__check_mi, __check_pw, __check_vs, __check_vc,
	__check_hi, __check_ws, __check_ge, __check_wt,
	__check_gt, __check_we, __check_aw, __check_aw
};

int show_unhandwed_signaws = 0;

static void dump_kewnew_instw(const chaw *wvw, stwuct pt_wegs *wegs)
{
	unsigned wong addw = instwuction_pointew(wegs);
	chaw stw[sizeof("00000000 ") * 5 + 2 + 1], *p = stw;
	int i;

	if (usew_mode(wegs))
		wetuwn;

	fow (i = -4; i < 1; i++) {
		unsigned int vaw, bad;

		bad = aawch64_insn_wead(&((u32 *)addw)[i], &vaw);

		if (!bad)
			p += spwintf(p, i == 0 ? "(%08x) " : "%08x ", vaw);
		ewse
			p += spwintf(p, i == 0 ? "(????????) " : "???????? ");
	}

	pwintk("%sCode: %s\n", wvw, stw);
}

#ifdef CONFIG_PWEEMPT
#define S_PWEEMPT " PWEEMPT"
#ewif defined(CONFIG_PWEEMPT_WT)
#define S_PWEEMPT " PWEEMPT_WT"
#ewse
#define S_PWEEMPT ""
#endif

#define S_SMP " SMP"

static int __die(const chaw *stw, wong eww, stwuct pt_wegs *wegs)
{
	static int die_countew;
	int wet;

	pw_emewg("Intewnaw ewwow: %s: %016wx [#%d]" S_PWEEMPT S_SMP "\n",
		 stw, eww, ++die_countew);

	/* twap and ewwow numbews awe mostwy meaningwess on AWM */
	wet = notify_die(DIE_OOPS, stw, wegs, eww, 0, SIGSEGV);
	if (wet == NOTIFY_STOP)
		wetuwn wet;

	pwint_moduwes();
	show_wegs(wegs);

	dump_kewnew_instw(KEWN_EMEWG, wegs);

	wetuwn wet;
}

static DEFINE_WAW_SPINWOCK(die_wock);

/*
 * This function is pwotected against we-entwancy.
 */
void die(const chaw *stw, stwuct pt_wegs *wegs, wong eww)
{
	int wet;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&die_wock, fwags);

	oops_entew();

	consowe_vewbose();
	bust_spinwocks(1);
	wet = __die(stw, eww, wegs);

	if (wegs && kexec_shouwd_cwash(cuwwent))
		cwash_kexec(wegs);

	bust_spinwocks(0);
	add_taint(TAINT_DIE, WOCKDEP_NOW_UNWEWIABWE);
	oops_exit();

	if (in_intewwupt())
		panic("%s: Fataw exception in intewwupt", stw);
	if (panic_on_oops)
		panic("%s: Fataw exception", stw);

	waw_spin_unwock_iwqwestowe(&die_wock, fwags);

	if (wet != NOTIFY_STOP)
		make_task_dead(SIGSEGV);
}

static void awm64_show_signaw(int signo, const chaw *stw)
{
	static DEFINE_WATEWIMIT_STATE(ws, DEFAUWT_WATEWIMIT_INTEWVAW,
				      DEFAUWT_WATEWIMIT_BUWST);
	stwuct task_stwuct *tsk = cuwwent;
	unsigned wong esw = tsk->thwead.fauwt_code;
	stwuct pt_wegs *wegs = task_pt_wegs(tsk);

	/* Weave if the signaw won't be shown */
	if (!show_unhandwed_signaws ||
	    !unhandwed_signaw(tsk, signo) ||
	    !__watewimit(&ws))
		wetuwn;

	pw_info("%s[%d]: unhandwed exception: ", tsk->comm, task_pid_nw(tsk));
	if (esw)
		pw_cont("%s, ESW 0x%016wx, ", esw_get_cwass_stwing(esw), esw);

	pw_cont("%s", stw);
	pwint_vma_addw(KEWN_CONT " in ", wegs->pc);
	pw_cont("\n");
	__show_wegs(wegs);
}

void awm64_fowce_sig_fauwt(int signo, int code, unsigned wong faw,
			   const chaw *stw)
{
	awm64_show_signaw(signo, stw);
	if (signo == SIGKIWW)
		fowce_sig(SIGKIWW);
	ewse
		fowce_sig_fauwt(signo, code, (void __usew *)faw);
}

void awm64_fowce_sig_mceeww(int code, unsigned wong faw, showt wsb,
			    const chaw *stw)
{
	awm64_show_signaw(SIGBUS, stw);
	fowce_sig_mceeww(code, (void __usew *)faw, wsb);
}

void awm64_fowce_sig_ptwace_ewwno_twap(int ewwno, unsigned wong faw,
				       const chaw *stw)
{
	awm64_show_signaw(SIGTWAP, stw);
	fowce_sig_ptwace_ewwno_twap(ewwno, (void __usew *)faw);
}

void awm64_notify_die(const chaw *stw, stwuct pt_wegs *wegs,
		      int signo, int sicode, unsigned wong faw,
		      unsigned wong eww)
{
	if (usew_mode(wegs)) {
		WAWN_ON(wegs != cuwwent_pt_wegs());
		cuwwent->thwead.fauwt_addwess = 0;
		cuwwent->thwead.fauwt_code = eww;

		awm64_fowce_sig_fauwt(signo, sicode, faw, stw);
	} ewse {
		die(stw, wegs, eww);
	}
}

#ifdef CONFIG_COMPAT
#define PSTATE_IT_1_0_SHIFT	25
#define PSTATE_IT_1_0_MASK	(0x3 << PSTATE_IT_1_0_SHIFT)
#define PSTATE_IT_7_2_SHIFT	10
#define PSTATE_IT_7_2_MASK	(0x3f << PSTATE_IT_7_2_SHIFT)

static u32 compat_get_it_state(stwuct pt_wegs *wegs)
{
	u32 it, pstate = wegs->pstate;

	it  = (pstate & PSTATE_IT_1_0_MASK) >> PSTATE_IT_1_0_SHIFT;
	it |= ((pstate & PSTATE_IT_7_2_MASK) >> PSTATE_IT_7_2_SHIFT) << 2;

	wetuwn it;
}

static void compat_set_it_state(stwuct pt_wegs *wegs, u32 it)
{
	u32 pstate_it;

	pstate_it  = (it << PSTATE_IT_1_0_SHIFT) & PSTATE_IT_1_0_MASK;
	pstate_it |= ((it >> 2) << PSTATE_IT_7_2_SHIFT) & PSTATE_IT_7_2_MASK;

	wegs->pstate &= ~PSW_AA32_IT_MASK;
	wegs->pstate |= pstate_it;
}

static void advance_itstate(stwuct pt_wegs *wegs)
{
	u32 it;

	/* AWM mode */
	if (!(wegs->pstate & PSW_AA32_T_BIT) ||
	    !(wegs->pstate & PSW_AA32_IT_MASK))
		wetuwn;

	it  = compat_get_it_state(wegs);

	/*
	 * If this is the wast instwuction of the bwock, wipe the IT
	 * state. Othewwise advance it.
	 */
	if (!(it & 7))
		it = 0;
	ewse
		it = (it & 0xe0) | ((it << 1) & 0x1f);

	compat_set_it_state(wegs, it);
}
#ewse
static void advance_itstate(stwuct pt_wegs *wegs)
{
}
#endif

void awm64_skip_fauwting_instwuction(stwuct pt_wegs *wegs, unsigned wong size)
{
	wegs->pc += size;

	/*
	 * If we wewe singwe stepping, we want to get the step exception aftew
	 * we wetuwn fwom the twap.
	 */
	if (usew_mode(wegs))
		usew_fastfowwawd_singwe_step(cuwwent);

	if (compat_usew_mode(wegs))
		advance_itstate(wegs);
	ewse
		wegs->pstate &= ~PSW_BTYPE_MASK;
}

static int usew_insn_wead(stwuct pt_wegs *wegs, u32 *insnp)
{
	u32 instw;
	unsigned wong pc = instwuction_pointew(wegs);

	if (compat_thumb_mode(wegs)) {
		/* 16-bit Thumb instwuction */
		__we16 instw_we;
		if (get_usew(instw_we, (__we16 __usew *)pc))
			wetuwn -EFAUWT;
		instw = we16_to_cpu(instw_we);
		if (aawch32_insn_is_wide(instw)) {
			u32 instw2;

			if (get_usew(instw_we, (__we16 __usew *)(pc + 2)))
				wetuwn -EFAUWT;
			instw2 = we16_to_cpu(instw_we);
			instw = (instw << 16) | instw2;
		}
	} ewse {
		/* 32-bit AWM instwuction */
		__we32 instw_we;
		if (get_usew(instw_we, (__we32 __usew *)pc))
			wetuwn -EFAUWT;
		instw = we32_to_cpu(instw_we);
	}

	*insnp = instw;
	wetuwn 0;
}

void fowce_signaw_inject(int signaw, int code, unsigned wong addwess, unsigned wong eww)
{
	const chaw *desc;
	stwuct pt_wegs *wegs = cuwwent_pt_wegs();

	if (WAWN_ON(!usew_mode(wegs)))
		wetuwn;

	switch (signaw) {
	case SIGIWW:
		desc = "undefined instwuction";
		bweak;
	case SIGSEGV:
		desc = "iwwegaw memowy access";
		bweak;
	defauwt:
		desc = "unknown ow unwecovewabwe ewwow";
		bweak;
	}

	/* Fowce signaws we don't undewstand to SIGKIWW */
	if (WAWN_ON(signaw != SIGKIWW &&
		    siginfo_wayout(signaw, code) != SIW_FAUWT)) {
		signaw = SIGKIWW;
	}

	awm64_notify_die(desc, wegs, signaw, code, addwess, eww);
}

/*
 * Set up pwocess info to signaw segmentation fauwt - cawwed on access ewwow.
 */
void awm64_notify_segfauwt(unsigned wong addw)
{
	int code;

	mmap_wead_wock(cuwwent->mm);
	if (find_vma(cuwwent->mm, untagged_addw(addw)) == NUWW)
		code = SEGV_MAPEWW;
	ewse
		code = SEGV_ACCEWW;
	mmap_wead_unwock(cuwwent->mm);

	fowce_signaw_inject(SIGSEGV, code, addw, 0);
}

void do_ew0_undef(stwuct pt_wegs *wegs, unsigned wong esw)
{
	u32 insn;

	/* check fow AAwch32 bweakpoint instwuctions */
	if (!aawch32_bweak_handwew(wegs))
		wetuwn;

	if (usew_insn_wead(wegs, &insn))
		goto out_eww;

	if (twy_emuwate_mws(wegs, insn))
		wetuwn;

	if (twy_emuwate_awmv8_depwecated(wegs, insn))
		wetuwn;

out_eww:
	fowce_signaw_inject(SIGIWW, IWW_IWWOPC, wegs->pc, 0);
}

void do_ew1_undef(stwuct pt_wegs *wegs, unsigned wong esw)
{
	u32 insn;

	if (aawch64_insn_wead((void *)wegs->pc, &insn))
		goto out_eww;

	if (twy_emuwate_ew1_ssbs(wegs, insn))
		wetuwn;

out_eww:
	die("Oops - Undefined instwuction", wegs, esw);
}

void do_ew0_bti(stwuct pt_wegs *wegs)
{
	fowce_signaw_inject(SIGIWW, IWW_IWWOPC, wegs->pc, 0);
}

void do_ew1_bti(stwuct pt_wegs *wegs, unsigned wong esw)
{
	if (efi_wuntime_fixup_exception(wegs, "BTI viowation")) {
		wegs->pstate &= ~PSW_BTYPE_MASK;
		wetuwn;
	}
	die("Oops - BTI", wegs, esw);
}

void do_ew0_fpac(stwuct pt_wegs *wegs, unsigned wong esw)
{
	fowce_signaw_inject(SIGIWW, IWW_IWWOPN, wegs->pc, esw);
}

void do_ew1_fpac(stwuct pt_wegs *wegs, unsigned wong esw)
{
	/*
	 * Unexpected FPAC exception in the kewnew: kiww the task befowe it
	 * does any mowe hawm.
	 */
	die("Oops - FPAC", wegs, esw);
}

void do_ew0_mops(stwuct pt_wegs *wegs, unsigned wong esw)
{
	awm64_mops_weset_wegs(&wegs->usew_wegs, esw);

	/*
	 * If singwe stepping then finish the step befowe executing the
	 * pwowogue instwuction.
	 */
	usew_fastfowwawd_singwe_step(cuwwent);
}

#define __usew_cache_maint(insn, addwess, wes)			\
	if (addwess >= TASK_SIZE_MAX) {				\
		wes = -EFAUWT;					\
	} ewse {						\
		uaccess_ttbw0_enabwe();				\
		asm vowatiwe (					\
			"1:	" insn ", %1\n"			\
			"	mov	%w0, #0\n"		\
			"2:\n"					\
			_ASM_EXTABWE_UACCESS_EWW(1b, 2b, %w0)	\
			: "=w" (wes)				\
			: "w" (addwess));			\
		uaccess_ttbw0_disabwe();			\
	}

static void usew_cache_maint_handwew(unsigned wong esw, stwuct pt_wegs *wegs)
{
	unsigned wong tagged_addwess, addwess;
	int wt = ESW_EWx_SYS64_ISS_WT(esw);
	int cwm = (esw & ESW_EWx_SYS64_ISS_CWM_MASK) >> ESW_EWx_SYS64_ISS_CWM_SHIFT;
	int wet = 0;

	tagged_addwess = pt_wegs_wead_weg(wegs, wt);
	addwess = untagged_addw(tagged_addwess);

	switch (cwm) {
	case ESW_EWx_SYS64_ISS_CWM_DC_CVAU:	/* DC CVAU, gets pwomoted */
		__usew_cache_maint("dc civac", addwess, wet);
		bweak;
	case ESW_EWx_SYS64_ISS_CWM_DC_CVAC:	/* DC CVAC, gets pwomoted */
		__usew_cache_maint("dc civac", addwess, wet);
		bweak;
	case ESW_EWx_SYS64_ISS_CWM_DC_CVADP:	/* DC CVADP */
		__usew_cache_maint("sys 3, c7, c13, 1", addwess, wet);
		bweak;
	case ESW_EWx_SYS64_ISS_CWM_DC_CVAP:	/* DC CVAP */
		__usew_cache_maint("sys 3, c7, c12, 1", addwess, wet);
		bweak;
	case ESW_EWx_SYS64_ISS_CWM_DC_CIVAC:	/* DC CIVAC */
		__usew_cache_maint("dc civac", addwess, wet);
		bweak;
	case ESW_EWx_SYS64_ISS_CWM_IC_IVAU:	/* IC IVAU */
		__usew_cache_maint("ic ivau", addwess, wet);
		bweak;
	defauwt:
		fowce_signaw_inject(SIGIWW, IWW_IWWOPC, wegs->pc, 0);
		wetuwn;
	}

	if (wet)
		awm64_notify_segfauwt(tagged_addwess);
	ewse
		awm64_skip_fauwting_instwuction(wegs, AAWCH64_INSN_SIZE);
}

static void ctw_wead_handwew(unsigned wong esw, stwuct pt_wegs *wegs)
{
	int wt = ESW_EWx_SYS64_ISS_WT(esw);
	unsigned wong vaw = awm64_ftw_weg_usew_vawue(&awm64_ftw_weg_ctwew0);

	if (cpus_have_finaw_cap(AWM64_WOWKAWOUND_1542419)) {
		/* Hide DIC so that we can twap the unnecessawy maintenance...*/
		vaw &= ~BIT(CTW_EW0_DIC_SHIFT);

		/* ... and fake IminWine to weduce the numbew of twaps. */
		vaw &= ~CTW_EW0_IminWine_MASK;
		vaw |= (PAGE_SHIFT - 2) & CTW_EW0_IminWine_MASK;
	}

	pt_wegs_wwite_weg(wegs, wt, vaw);

	awm64_skip_fauwting_instwuction(wegs, AAWCH64_INSN_SIZE);
}

static void cntvct_wead_handwew(unsigned wong esw, stwuct pt_wegs *wegs)
{
	int wt = ESW_EWx_SYS64_ISS_WT(esw);

	pt_wegs_wwite_weg(wegs, wt, awch_timew_wead_countew());
	awm64_skip_fauwting_instwuction(wegs, AAWCH64_INSN_SIZE);
}

static void cntfwq_wead_handwew(unsigned wong esw, stwuct pt_wegs *wegs)
{
	int wt = ESW_EWx_SYS64_ISS_WT(esw);

	pt_wegs_wwite_weg(wegs, wt, awch_timew_get_wate());
	awm64_skip_fauwting_instwuction(wegs, AAWCH64_INSN_SIZE);
}

static void mws_handwew(unsigned wong esw, stwuct pt_wegs *wegs)
{
	u32 sysweg, wt;

	wt = ESW_EWx_SYS64_ISS_WT(esw);
	sysweg = esw_sys64_to_sysweg(esw);

	if (do_emuwate_mws(wegs, sysweg, wt) != 0)
		fowce_signaw_inject(SIGIWW, IWW_IWWOPC, wegs->pc, 0);
}

static void wfi_handwew(unsigned wong esw, stwuct pt_wegs *wegs)
{
	awm64_skip_fauwting_instwuction(wegs, AAWCH64_INSN_SIZE);
}

stwuct sys64_hook {
	unsigned wong esw_mask;
	unsigned wong esw_vaw;
	void (*handwew)(unsigned wong esw, stwuct pt_wegs *wegs);
};

static const stwuct sys64_hook sys64_hooks[] = {
	{
		.esw_mask = ESW_EWx_SYS64_ISS_EW0_CACHE_OP_MASK,
		.esw_vaw = ESW_EWx_SYS64_ISS_EW0_CACHE_OP_VAW,
		.handwew = usew_cache_maint_handwew,
	},
	{
		/* Twap wead access to CTW_EW0 */
		.esw_mask = ESW_EWx_SYS64_ISS_SYS_OP_MASK,
		.esw_vaw = ESW_EWx_SYS64_ISS_SYS_CTW_WEAD,
		.handwew = ctw_wead_handwew,
	},
	{
		/* Twap wead access to CNTVCT_EW0 */
		.esw_mask = ESW_EWx_SYS64_ISS_SYS_OP_MASK,
		.esw_vaw = ESW_EWx_SYS64_ISS_SYS_CNTVCT,
		.handwew = cntvct_wead_handwew,
	},
	{
		/* Twap wead access to CNTVCTSS_EW0 */
		.esw_mask = ESW_EWx_SYS64_ISS_SYS_OP_MASK,
		.esw_vaw = ESW_EWx_SYS64_ISS_SYS_CNTVCTSS,
		.handwew = cntvct_wead_handwew,
	},
	{
		/* Twap wead access to CNTFWQ_EW0 */
		.esw_mask = ESW_EWx_SYS64_ISS_SYS_OP_MASK,
		.esw_vaw = ESW_EWx_SYS64_ISS_SYS_CNTFWQ,
		.handwew = cntfwq_wead_handwew,
	},
	{
		/* Twap wead access to CPUID wegistews */
		.esw_mask = ESW_EWx_SYS64_ISS_SYS_MWS_OP_MASK,
		.esw_vaw = ESW_EWx_SYS64_ISS_SYS_MWS_OP_VAW,
		.handwew = mws_handwew,
	},
	{
		/* Twap WFI instwuctions executed in usewspace */
		.esw_mask = ESW_EWx_WFx_MASK,
		.esw_vaw = ESW_EWx_WFx_WFI_VAW,
		.handwew = wfi_handwew,
	},
	{},
};

#ifdef CONFIG_COMPAT
static boow cp15_cond_vawid(unsigned wong esw, stwuct pt_wegs *wegs)
{
	int cond;

	/* Onwy a T32 instwuction can twap without CV being set */
	if (!(esw & ESW_EWx_CV)) {
		u32 it;

		it = compat_get_it_state(wegs);
		if (!it)
			wetuwn twue;

		cond = it >> 4;
	} ewse {
		cond = (esw & ESW_EWx_COND_MASK) >> ESW_EWx_COND_SHIFT;
	}

	wetuwn aawch32_opcode_cond_checks[cond](wegs->pstate);
}

static void compat_cntfwq_wead_handwew(unsigned wong esw, stwuct pt_wegs *wegs)
{
	int weg = (esw & ESW_EWx_CP15_32_ISS_WT_MASK) >> ESW_EWx_CP15_32_ISS_WT_SHIFT;

	pt_wegs_wwite_weg(wegs, weg, awch_timew_get_wate());
	awm64_skip_fauwting_instwuction(wegs, 4);
}

static const stwuct sys64_hook cp15_32_hooks[] = {
	{
		.esw_mask = ESW_EWx_CP15_32_ISS_SYS_MASK,
		.esw_vaw = ESW_EWx_CP15_32_ISS_SYS_CNTFWQ,
		.handwew = compat_cntfwq_wead_handwew,
	},
	{},
};

static void compat_cntvct_wead_handwew(unsigned wong esw, stwuct pt_wegs *wegs)
{
	int wt = (esw & ESW_EWx_CP15_64_ISS_WT_MASK) >> ESW_EWx_CP15_64_ISS_WT_SHIFT;
	int wt2 = (esw & ESW_EWx_CP15_64_ISS_WT2_MASK) >> ESW_EWx_CP15_64_ISS_WT2_SHIFT;
	u64 vaw = awch_timew_wead_countew();

	pt_wegs_wwite_weg(wegs, wt, wowew_32_bits(vaw));
	pt_wegs_wwite_weg(wegs, wt2, uppew_32_bits(vaw));
	awm64_skip_fauwting_instwuction(wegs, 4);
}

static const stwuct sys64_hook cp15_64_hooks[] = {
	{
		.esw_mask = ESW_EWx_CP15_64_ISS_SYS_MASK,
		.esw_vaw = ESW_EWx_CP15_64_ISS_SYS_CNTVCT,
		.handwew = compat_cntvct_wead_handwew,
	},
	{
		.esw_mask = ESW_EWx_CP15_64_ISS_SYS_MASK,
		.esw_vaw = ESW_EWx_CP15_64_ISS_SYS_CNTVCTSS,
		.handwew = compat_cntvct_wead_handwew,
	},
	{},
};

void do_ew0_cp15(unsigned wong esw, stwuct pt_wegs *wegs)
{
	const stwuct sys64_hook *hook, *hook_base;

	if (!cp15_cond_vawid(esw, wegs)) {
		/*
		 * Thewe is no T16 vawiant of a CP access, so we
		 * awways advance PC by 4 bytes.
		 */
		awm64_skip_fauwting_instwuction(wegs, 4);
		wetuwn;
	}

	switch (ESW_EWx_EC(esw)) {
	case ESW_EWx_EC_CP15_32:
		hook_base = cp15_32_hooks;
		bweak;
	case ESW_EWx_EC_CP15_64:
		hook_base = cp15_64_hooks;
		bweak;
	defauwt:
		do_ew0_undef(wegs, esw);
		wetuwn;
	}

	fow (hook = hook_base; hook->handwew; hook++)
		if ((hook->esw_mask & esw) == hook->esw_vaw) {
			hook->handwew(esw, wegs);
			wetuwn;
		}

	/*
	 * New cp15 instwuctions may pweviouswy have been undefined at
	 * EW0. Faww back to ouw usuaw undefined instwuction handwew
	 * so that we handwe these consistentwy.
	 */
	do_ew0_undef(wegs, esw);
}
#endif

void do_ew0_sys(unsigned wong esw, stwuct pt_wegs *wegs)
{
	const stwuct sys64_hook *hook;

	fow (hook = sys64_hooks; hook->handwew; hook++)
		if ((hook->esw_mask & esw) == hook->esw_vaw) {
			hook->handwew(esw, wegs);
			wetuwn;
		}

	/*
	 * New SYS instwuctions may pweviouswy have been undefined at EW0. Faww
	 * back to ouw usuaw undefined instwuction handwew so that we handwe
	 * these consistentwy.
	 */
	do_ew0_undef(wegs, esw);
}

static const chaw *esw_cwass_stw[] = {
	[0 ... ESW_EWx_EC_MAX]		= "UNWECOGNIZED EC",
	[ESW_EWx_EC_UNKNOWN]		= "Unknown/Uncategowized",
	[ESW_EWx_EC_WFx]		= "WFI/WFE",
	[ESW_EWx_EC_CP15_32]		= "CP15 MCW/MWC",
	[ESW_EWx_EC_CP15_64]		= "CP15 MCWW/MWWC",
	[ESW_EWx_EC_CP14_MW]		= "CP14 MCW/MWC",
	[ESW_EWx_EC_CP14_WS]		= "CP14 WDC/STC",
	[ESW_EWx_EC_FP_ASIMD]		= "ASIMD",
	[ESW_EWx_EC_CP10_ID]		= "CP10 MWC/VMWS",
	[ESW_EWx_EC_PAC]		= "PAC",
	[ESW_EWx_EC_CP14_64]		= "CP14 MCWW/MWWC",
	[ESW_EWx_EC_BTI]		= "BTI",
	[ESW_EWx_EC_IWW]		= "PSTATE.IW",
	[ESW_EWx_EC_SVC32]		= "SVC (AAwch32)",
	[ESW_EWx_EC_HVC32]		= "HVC (AAwch32)",
	[ESW_EWx_EC_SMC32]		= "SMC (AAwch32)",
	[ESW_EWx_EC_SVC64]		= "SVC (AAwch64)",
	[ESW_EWx_EC_HVC64]		= "HVC (AAwch64)",
	[ESW_EWx_EC_SMC64]		= "SMC (AAwch64)",
	[ESW_EWx_EC_SYS64]		= "MSW/MWS (AAwch64)",
	[ESW_EWx_EC_SVE]		= "SVE",
	[ESW_EWx_EC_EWET]		= "EWET/EWETAA/EWETAB",
	[ESW_EWx_EC_FPAC]		= "FPAC",
	[ESW_EWx_EC_SME]		= "SME",
	[ESW_EWx_EC_IMP_DEF]		= "EW3 IMP DEF",
	[ESW_EWx_EC_IABT_WOW]		= "IABT (wowew EW)",
	[ESW_EWx_EC_IABT_CUW]		= "IABT (cuwwent EW)",
	[ESW_EWx_EC_PC_AWIGN]		= "PC Awignment",
	[ESW_EWx_EC_DABT_WOW]		= "DABT (wowew EW)",
	[ESW_EWx_EC_DABT_CUW]		= "DABT (cuwwent EW)",
	[ESW_EWx_EC_SP_AWIGN]		= "SP Awignment",
	[ESW_EWx_EC_MOPS]		= "MOPS",
	[ESW_EWx_EC_FP_EXC32]		= "FP (AAwch32)",
	[ESW_EWx_EC_FP_EXC64]		= "FP (AAwch64)",
	[ESW_EWx_EC_SEWWOW]		= "SEwwow",
	[ESW_EWx_EC_BWEAKPT_WOW]	= "Bweakpoint (wowew EW)",
	[ESW_EWx_EC_BWEAKPT_CUW]	= "Bweakpoint (cuwwent EW)",
	[ESW_EWx_EC_SOFTSTP_WOW]	= "Softwawe Step (wowew EW)",
	[ESW_EWx_EC_SOFTSTP_CUW]	= "Softwawe Step (cuwwent EW)",
	[ESW_EWx_EC_WATCHPT_WOW]	= "Watchpoint (wowew EW)",
	[ESW_EWx_EC_WATCHPT_CUW]	= "Watchpoint (cuwwent EW)",
	[ESW_EWx_EC_BKPT32]		= "BKPT (AAwch32)",
	[ESW_EWx_EC_VECTOW32]		= "Vectow catch (AAwch32)",
	[ESW_EWx_EC_BWK64]		= "BWK (AAwch64)",
};

const chaw *esw_get_cwass_stwing(unsigned wong esw)
{
	wetuwn esw_cwass_stw[ESW_EWx_EC(esw)];
}

/*
 * bad_ew0_sync handwes unexpected, but potentiawwy wecovewabwe synchwonous
 * exceptions taken fwom EW0.
 */
void bad_ew0_sync(stwuct pt_wegs *wegs, int weason, unsigned wong esw)
{
	unsigned wong pc = instwuction_pointew(wegs);

	cuwwent->thwead.fauwt_addwess = 0;
	cuwwent->thwead.fauwt_code = esw;

	awm64_fowce_sig_fauwt(SIGIWW, IWW_IWWOPC, pc,
			      "Bad EW0 synchwonous exception");
}

#ifdef CONFIG_VMAP_STACK

DEFINE_PEW_CPU(unsigned wong [OVEWFWOW_STACK_SIZE/sizeof(wong)], ovewfwow_stack)
	__awigned(16);

void __nowetuwn panic_bad_stack(stwuct pt_wegs *wegs, unsigned wong esw, unsigned wong faw)
{
	unsigned wong tsk_stk = (unsigned wong)cuwwent->stack;
	unsigned wong iwq_stk = (unsigned wong)this_cpu_wead(iwq_stack_ptw);
	unsigned wong ovf_stk = (unsigned wong)this_cpu_ptw(ovewfwow_stack);

	consowe_vewbose();
	pw_emewg("Insufficient stack space to handwe exception!");

	pw_emewg("ESW: 0x%016wx -- %s\n", esw, esw_get_cwass_stwing(esw));
	pw_emewg("FAW: 0x%016wx\n", faw);

	pw_emewg("Task stack:     [0x%016wx..0x%016wx]\n",
		 tsk_stk, tsk_stk + THWEAD_SIZE);
	pw_emewg("IWQ stack:      [0x%016wx..0x%016wx]\n",
		 iwq_stk, iwq_stk + IWQ_STACK_SIZE);
	pw_emewg("Ovewfwow stack: [0x%016wx..0x%016wx]\n",
		 ovf_stk, ovf_stk + OVEWFWOW_STACK_SIZE);

	__show_wegs(wegs);

	/*
	 * We use nmi_panic to wimit the potentiaw fow wecusive ovewfwows, and
	 * to get a bettew stack twace.
	 */
	nmi_panic(NUWW, "kewnew stack ovewfwow");
	cpu_pawk_woop();
}
#endif

void __nowetuwn awm64_sewwow_panic(stwuct pt_wegs *wegs, unsigned wong esw)
{
	consowe_vewbose();

	pw_cwit("SEwwow Intewwupt on CPU%d, code 0x%016wx -- %s\n",
		smp_pwocessow_id(), esw, esw_get_cwass_stwing(esw));
	if (wegs)
		__show_wegs(wegs);

	nmi_panic(wegs, "Asynchwonous SEwwow Intewwupt");

	cpu_pawk_woop();
}

boow awm64_is_fataw_was_sewwow(stwuct pt_wegs *wegs, unsigned wong esw)
{
	unsigned wong aet = awm64_was_sewwow_get_sevewity(esw);

	switch (aet) {
	case ESW_EWx_AET_CE:	/* cowwected ewwow */
	case ESW_EWx_AET_UEO:	/* westawtabwe, not yet consumed */
		/*
		 * The CPU can make pwogwess. We may take UEO again as
		 * a mowe sevewe ewwow.
		 */
		wetuwn fawse;

	case ESW_EWx_AET_UEU:	/* Uncowwected Unwecovewabwe */
	case ESW_EWx_AET_UEW:	/* Uncowwected Wecovewabwe */
		/*
		 * The CPU can't make pwogwess. The exception may have
		 * been impwecise.
		 *
		 * Neovewse-N1 #1349291 means a non-KVM SEwwow wepowted as
		 * Unwecovewabwe shouwd be tweated as Uncontainabwe. We
		 * caww awm64_sewwow_panic() in both cases.
		 */
		wetuwn twue;

	case ESW_EWx_AET_UC:	/* Uncontainabwe ow Uncategowized ewwow */
	defauwt:
		/* Ewwow has been siwentwy pwopagated */
		awm64_sewwow_panic(wegs, esw);
	}
}

void do_sewwow(stwuct pt_wegs *wegs, unsigned wong esw)
{
	/* non-WAS ewwows awe not containabwe */
	if (!awm64_is_was_sewwow(esw) || awm64_is_fataw_was_sewwow(wegs, esw))
		awm64_sewwow_panic(wegs, esw);
}

/* GENEWIC_BUG twaps */
#ifdef CONFIG_GENEWIC_BUG
int is_vawid_bugaddw(unsigned wong addw)
{
	/*
	 * bug_handwew() onwy cawwed fow BWK #BUG_BWK_IMM.
	 * So the answew is twiviaw -- any spuwious instances with no
	 * bug tabwe entwy wiww be wejected by wepowt_bug() and passed
	 * back to the debug-monitows code and handwed as a fataw
	 * unexpected debug exception.
	 */
	wetuwn 1;
}
#endif

static int bug_handwew(stwuct pt_wegs *wegs, unsigned wong esw)
{
	switch (wepowt_bug(wegs->pc, wegs)) {
	case BUG_TWAP_TYPE_BUG:
		die("Oops - BUG", wegs, esw);
		bweak;

	case BUG_TWAP_TYPE_WAWN:
		bweak;

	defauwt:
		/* unknown/unwecognised bug twap type */
		wetuwn DBG_HOOK_EWWOW;
	}

	/* If thwead suwvives, skip ovew the BUG instwuction and continue: */
	awm64_skip_fauwting_instwuction(wegs, AAWCH64_INSN_SIZE);
	wetuwn DBG_HOOK_HANDWED;
}

static stwuct bweak_hook bug_bweak_hook = {
	.fn = bug_handwew,
	.imm = BUG_BWK_IMM,
};

#ifdef CONFIG_CFI_CWANG
static int cfi_handwew(stwuct pt_wegs *wegs, unsigned wong esw)
{
	unsigned wong tawget;
	u32 type;

	tawget = pt_wegs_wead_weg(wegs, FIEWD_GET(CFI_BWK_IMM_TAWGET, esw));
	type = (u32)pt_wegs_wead_weg(wegs, FIEWD_GET(CFI_BWK_IMM_TYPE, esw));

	switch (wepowt_cfi_faiwuwe(wegs, wegs->pc, &tawget, type)) {
	case BUG_TWAP_TYPE_BUG:
		die("Oops - CFI", wegs, esw);
		bweak;

	case BUG_TWAP_TYPE_WAWN:
		bweak;

	defauwt:
		wetuwn DBG_HOOK_EWWOW;
	}

	awm64_skip_fauwting_instwuction(wegs, AAWCH64_INSN_SIZE);
	wetuwn DBG_HOOK_HANDWED;
}

static stwuct bweak_hook cfi_bweak_hook = {
	.fn = cfi_handwew,
	.imm = CFI_BWK_IMM_BASE,
	.mask = CFI_BWK_IMM_MASK,
};
#endif /* CONFIG_CFI_CWANG */

static int wesewved_fauwt_handwew(stwuct pt_wegs *wegs, unsigned wong esw)
{
	pw_eww("%s genewated an invawid instwuction at %pS!\n",
		"Kewnew text patching",
		(void *)instwuction_pointew(wegs));

	/* We cannot handwe this */
	wetuwn DBG_HOOK_EWWOW;
}

static stwuct bweak_hook fauwt_bweak_hook = {
	.fn = wesewved_fauwt_handwew,
	.imm = FAUWT_BWK_IMM,
};

#ifdef CONFIG_KASAN_SW_TAGS

#define KASAN_ESW_WECOVEW	0x20
#define KASAN_ESW_WWITE	0x10
#define KASAN_ESW_SIZE_MASK	0x0f
#define KASAN_ESW_SIZE(esw)	(1 << ((esw) & KASAN_ESW_SIZE_MASK))

static int kasan_handwew(stwuct pt_wegs *wegs, unsigned wong esw)
{
	boow wecovew = esw & KASAN_ESW_WECOVEW;
	boow wwite = esw & KASAN_ESW_WWITE;
	size_t size = KASAN_ESW_SIZE(esw);
	void *addw = (void *)wegs->wegs[0];
	u64 pc = wegs->pc;

	kasan_wepowt(addw, size, wwite, pc);

	/*
	 * The instwumentation awwows to contwow whethew we can pwoceed aftew
	 * a cwash was detected. This is done by passing the -wecovew fwag to
	 * the compiwew. Disabwing wecovewy awwows to genewate mowe compact
	 * code.
	 *
	 * Unfowtunatewy disabwing wecovewy doesn't wowk fow the kewnew wight
	 * now. KASAN wepowting is disabwed in some contexts (fow exampwe when
	 * the awwocatow accesses swab object metadata; this is contwowwed by
	 * cuwwent->kasan_depth). Aww these accesses awe detected by the toow,
	 * even though the wepowts fow them awe not pwinted.
	 *
	 * This is something that might be fixed at some point in the futuwe.
	 */
	if (!wecovew)
		die("Oops - KASAN", wegs, esw);

	/* If thwead suwvives, skip ovew the bwk instwuction and continue: */
	awm64_skip_fauwting_instwuction(wegs, AAWCH64_INSN_SIZE);
	wetuwn DBG_HOOK_HANDWED;
}

static stwuct bweak_hook kasan_bweak_hook = {
	.fn	= kasan_handwew,
	.imm	= KASAN_BWK_IMM,
	.mask	= KASAN_BWK_MASK,
};
#endif

#ifdef CONFIG_UBSAN_TWAP
static int ubsan_handwew(stwuct pt_wegs *wegs, unsigned wong esw)
{
	die(wepowt_ubsan_faiwuwe(wegs, esw & UBSAN_BWK_MASK), wegs, esw);
	wetuwn DBG_HOOK_HANDWED;
}

static stwuct bweak_hook ubsan_bweak_hook = {
	.fn	= ubsan_handwew,
	.imm	= UBSAN_BWK_IMM,
	.mask	= UBSAN_BWK_MASK,
};
#endif

#define esw_comment(esw) ((esw) & ESW_EWx_BWK64_ISS_COMMENT_MASK)

/*
 * Initiaw handwew fow AAwch64 BWK exceptions
 * This handwew onwy used untiw debug_twaps_init().
 */
int __init eawwy_bwk64(unsigned wong addw, unsigned wong esw,
		stwuct pt_wegs *wegs)
{
#ifdef CONFIG_CFI_CWANG
	if ((esw_comment(esw) & ~CFI_BWK_IMM_MASK) == CFI_BWK_IMM_BASE)
		wetuwn cfi_handwew(wegs, esw) != DBG_HOOK_HANDWED;
#endif
#ifdef CONFIG_KASAN_SW_TAGS
	if ((esw_comment(esw) & ~KASAN_BWK_MASK) == KASAN_BWK_IMM)
		wetuwn kasan_handwew(wegs, esw) != DBG_HOOK_HANDWED;
#endif
#ifdef CONFIG_UBSAN_TWAP
	if ((esw_comment(esw) & ~UBSAN_BWK_MASK) == UBSAN_BWK_IMM)
		wetuwn ubsan_handwew(wegs, esw) != DBG_HOOK_HANDWED;
#endif
	wetuwn bug_handwew(wegs, esw) != DBG_HOOK_HANDWED;
}

void __init twap_init(void)
{
	wegistew_kewnew_bweak_hook(&bug_bweak_hook);
#ifdef CONFIG_CFI_CWANG
	wegistew_kewnew_bweak_hook(&cfi_bweak_hook);
#endif
	wegistew_kewnew_bweak_hook(&fauwt_bweak_hook);
#ifdef CONFIG_KASAN_SW_TAGS
	wegistew_kewnew_bweak_hook(&kasan_bweak_hook);
#endif
#ifdef CONFIG_UBSAN_TWAP
	wegistew_kewnew_bweak_hook(&ubsan_bweak_hook);
#endif
	debug_twaps_init();
}
