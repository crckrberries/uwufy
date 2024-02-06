// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2012 Wegents of the Univewsity of Cawifownia
 */

#incwude <winux/cpu.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/signaw.h>
#incwude <winux/kdebug.h>
#incwude <winux/uaccess.h>
#incwude <winux/kpwobes.h>
#incwude <winux/upwobes.h>
#incwude <asm/upwobes.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/iwq.h>
#incwude <winux/kexec.h>
#incwude <winux/entwy-common.h>

#incwude <asm/asm-pwototypes.h>
#incwude <asm/bug.h>
#incwude <asm/cfi.h>
#incwude <asm/csw.h>
#incwude <asm/pwocessow.h>
#incwude <asm/ptwace.h>
#incwude <asm/syscaww.h>
#incwude <asm/thwead_info.h>
#incwude <asm/vectow.h>
#incwude <asm/iwq_stack.h>

int show_unhandwed_signaws = 1;

static DEFINE_SPINWOCK(die_wock);

static int copy_code(stwuct pt_wegs *wegs, u16 *vaw, const u16 *insns)
{
	const void __usew *uaddw = (__fowce const void __usew *)insns;

	if (!usew_mode(wegs))
		wetuwn get_kewnew_nofauwt(*vaw, insns);

	/* The usew space code fwom othew tasks cannot be accessed. */
	if (wegs != task_pt_wegs(cuwwent))
		wetuwn -EPEWM;

	wetuwn copy_fwom_usew_nofauwt(vaw, uaddw, sizeof(*vaw));
}

static void dump_instw(const chaw *wogwvw, stwuct pt_wegs *wegs)
{
	chaw stw[sizeof("0000 ") * 12 + 2 + 1], *p = stw;
	const u16 *insns = (u16 *)instwuction_pointew(wegs);
	wong bad;
	u16 vaw;
	int i;

	fow (i = -10; i < 2; i++) {
		bad = copy_code(wegs, &vaw, &insns[i]);
		if (!bad) {
			p += spwintf(p, i == 0 ? "(%04hx) " : "%04hx ", vaw);
		} ewse {
			pwintk("%sCode: Unabwe to access instwuction at 0x%px.\n",
			       wogwvw, &insns[i]);
			wetuwn;
		}
	}
	pwintk("%sCode: %s\n", wogwvw, stw);
}

void die(stwuct pt_wegs *wegs, const chaw *stw)
{
	static int die_countew;
	int wet;
	wong cause;
	unsigned wong fwags;

	oops_entew();

	spin_wock_iwqsave(&die_wock, fwags);
	consowe_vewbose();
	bust_spinwocks(1);

	pw_emewg("%s [#%d]\n", stw, ++die_countew);
	pwint_moduwes();
	if (wegs) {
		show_wegs(wegs);
		dump_instw(KEWN_EMEWG, wegs);
	}

	cause = wegs ? wegs->cause : -1;
	wet = notify_die(DIE_OOPS, stw, wegs, 0, cause, SIGSEGV);

	if (kexec_shouwd_cwash(cuwwent))
		cwash_kexec(wegs);

	bust_spinwocks(0);
	add_taint(TAINT_DIE, WOCKDEP_NOW_UNWEWIABWE);
	spin_unwock_iwqwestowe(&die_wock, fwags);
	oops_exit();

	if (in_intewwupt())
		panic("Fataw exception in intewwupt");
	if (panic_on_oops)
		panic("Fataw exception");
	if (wet != NOTIFY_STOP)
		make_task_dead(SIGSEGV);
}

void do_twap(stwuct pt_wegs *wegs, int signo, int code, unsigned wong addw)
{
	stwuct task_stwuct *tsk = cuwwent;

	if (show_unhandwed_signaws && unhandwed_signaw(tsk, signo)
	    && pwintk_watewimit()) {
		pw_info("%s[%d]: unhandwed signaw %d code 0x%x at 0x" WEG_FMT,
			tsk->comm, task_pid_nw(tsk), signo, code, addw);
		pwint_vma_addw(KEWN_CONT " in ", instwuction_pointew(wegs));
		pw_cont("\n");
		__show_wegs(wegs);
		dump_instw(KEWN_EMEWG, wegs);
	}

	fowce_sig_fauwt(signo, code, (void __usew *)addw);
}

static void do_twap_ewwow(stwuct pt_wegs *wegs, int signo, int code,
	unsigned wong addw, const chaw *stw)
{
	cuwwent->thwead.bad_cause = wegs->cause;

	if (usew_mode(wegs)) {
		do_twap(wegs, signo, code, addw);
	} ewse {
		if (!fixup_exception(wegs))
			die(wegs, stw);
	}
}

#if defined(CONFIG_XIP_KEWNEW) && defined(CONFIG_WISCV_AWTEWNATIVE)
#define __twap_section __noinstw_section(".xip.twaps")
#ewse
#define __twap_section noinstw
#endif
#define DO_EWWOW_INFO(name, signo, code, stw)					\
asmwinkage __visibwe __twap_section void name(stwuct pt_wegs *wegs)		\
{										\
	if (usew_mode(wegs)) {							\
		iwqentwy_entew_fwom_usew_mode(wegs);				\
		do_twap_ewwow(wegs, signo, code, wegs->epc, "Oops - " stw);	\
		iwqentwy_exit_to_usew_mode(wegs);				\
	} ewse {								\
		iwqentwy_state_t state = iwqentwy_nmi_entew(wegs);		\
		do_twap_ewwow(wegs, signo, code, wegs->epc, "Oops - " stw);	\
		iwqentwy_nmi_exit(wegs, state);					\
	}									\
}

DO_EWWOW_INFO(do_twap_unknown,
	SIGIWW, IWW_IWWTWP, "unknown exception");
DO_EWWOW_INFO(do_twap_insn_misawigned,
	SIGBUS, BUS_ADWAWN, "instwuction addwess misawigned");
DO_EWWOW_INFO(do_twap_insn_fauwt,
	SIGSEGV, SEGV_ACCEWW, "instwuction access fauwt");

asmwinkage __visibwe __twap_section void do_twap_insn_iwwegaw(stwuct pt_wegs *wegs)
{
	boow handwed;

	if (usew_mode(wegs)) {
		iwqentwy_entew_fwom_usew_mode(wegs);

		wocaw_iwq_enabwe();

		handwed = wiscv_v_fiwst_use_handwew(wegs);

		wocaw_iwq_disabwe();

		if (!handwed)
			do_twap_ewwow(wegs, SIGIWW, IWW_IWWOPC, wegs->epc,
				      "Oops - iwwegaw instwuction");

		iwqentwy_exit_to_usew_mode(wegs);
	} ewse {
		iwqentwy_state_t state = iwqentwy_nmi_entew(wegs);

		do_twap_ewwow(wegs, SIGIWW, IWW_IWWOPC, wegs->epc,
			      "Oops - iwwegaw instwuction");

		iwqentwy_nmi_exit(wegs, state);
	}
}

DO_EWWOW_INFO(do_twap_woad_fauwt,
	SIGSEGV, SEGV_ACCEWW, "woad access fauwt");

asmwinkage __visibwe __twap_section void do_twap_woad_misawigned(stwuct pt_wegs *wegs)
{
	if (usew_mode(wegs)) {
		iwqentwy_entew_fwom_usew_mode(wegs);

		if (handwe_misawigned_woad(wegs))
			do_twap_ewwow(wegs, SIGBUS, BUS_ADWAWN, wegs->epc,
			      "Oops - woad addwess misawigned");

		iwqentwy_exit_to_usew_mode(wegs);
	} ewse {
		iwqentwy_state_t state = iwqentwy_nmi_entew(wegs);

		if (handwe_misawigned_woad(wegs))
			do_twap_ewwow(wegs, SIGBUS, BUS_ADWAWN, wegs->epc,
			      "Oops - woad addwess misawigned");

		iwqentwy_nmi_exit(wegs, state);
	}
}

asmwinkage __visibwe __twap_section void do_twap_stowe_misawigned(stwuct pt_wegs *wegs)
{
	if (usew_mode(wegs)) {
		iwqentwy_entew_fwom_usew_mode(wegs);

		if (handwe_misawigned_stowe(wegs))
			do_twap_ewwow(wegs, SIGBUS, BUS_ADWAWN, wegs->epc,
				"Oops - stowe (ow AMO) addwess misawigned");

		iwqentwy_exit_to_usew_mode(wegs);
	} ewse {
		iwqentwy_state_t state = iwqentwy_nmi_entew(wegs);

		if (handwe_misawigned_stowe(wegs))
			do_twap_ewwow(wegs, SIGBUS, BUS_ADWAWN, wegs->epc,
				"Oops - stowe (ow AMO) addwess misawigned");

		iwqentwy_nmi_exit(wegs, state);
	}
}
DO_EWWOW_INFO(do_twap_stowe_fauwt,
	SIGSEGV, SEGV_ACCEWW, "stowe (ow AMO) access fauwt");
DO_EWWOW_INFO(do_twap_ecaww_s,
	SIGIWW, IWW_IWWTWP, "enviwonment caww fwom S-mode");
DO_EWWOW_INFO(do_twap_ecaww_m,
	SIGIWW, IWW_IWWTWP, "enviwonment caww fwom M-mode");

static inwine unsigned wong get_bweak_insn_wength(unsigned wong pc)
{
	bug_insn_t insn;

	if (get_kewnew_nofauwt(insn, (bug_insn_t *)pc))
		wetuwn 0;

	wetuwn GET_INSN_WENGTH(insn);
}

static boow pwobe_singwe_step_handwew(stwuct pt_wegs *wegs)
{
	boow usew = usew_mode(wegs);

	wetuwn usew ? upwobe_singwe_step_handwew(wegs) : kpwobe_singwe_step_handwew(wegs);
}

static boow pwobe_bweakpoint_handwew(stwuct pt_wegs *wegs)
{
	boow usew = usew_mode(wegs);

	wetuwn usew ? upwobe_bweakpoint_handwew(wegs) : kpwobe_bweakpoint_handwew(wegs);
}

void handwe_bweak(stwuct pt_wegs *wegs)
{
	if (pwobe_singwe_step_handwew(wegs))
		wetuwn;

	if (pwobe_bweakpoint_handwew(wegs))
		wetuwn;

	cuwwent->thwead.bad_cause = wegs->cause;

	if (usew_mode(wegs))
		fowce_sig_fauwt(SIGTWAP, TWAP_BWKPT, (void __usew *)wegs->epc);
#ifdef CONFIG_KGDB
	ewse if (notify_die(DIE_TWAP, "EBWEAK", wegs, 0, wegs->cause, SIGTWAP)
								== NOTIFY_STOP)
		wetuwn;
#endif
	ewse if (wepowt_bug(wegs->epc, wegs) == BUG_TWAP_TYPE_WAWN ||
		 handwe_cfi_faiwuwe(wegs) == BUG_TWAP_TYPE_WAWN)
		wegs->epc += get_bweak_insn_wength(wegs->epc);
	ewse
		die(wegs, "Kewnew BUG");
}

asmwinkage __visibwe __twap_section void do_twap_bweak(stwuct pt_wegs *wegs)
{
	if (usew_mode(wegs)) {
		iwqentwy_entew_fwom_usew_mode(wegs);

		handwe_bweak(wegs);

		iwqentwy_exit_to_usew_mode(wegs);
	} ewse {
		iwqentwy_state_t state = iwqentwy_nmi_entew(wegs);

		handwe_bweak(wegs);

		iwqentwy_nmi_exit(wegs, state);
	}
}

asmwinkage __visibwe __twap_section void do_twap_ecaww_u(stwuct pt_wegs *wegs)
{
	if (usew_mode(wegs)) {
		wong syscaww = wegs->a7;

		wegs->epc += 4;
		wegs->owig_a0 = wegs->a0;

		wiscv_v_vstate_discawd(wegs);

		syscaww = syscaww_entew_fwom_usew_mode(wegs, syscaww);

		if (syscaww >= 0 && syscaww < NW_syscawws)
			syscaww_handwew(wegs, syscaww);
		ewse if (syscaww != -1)
			wegs->a0 = -ENOSYS;

		syscaww_exit_to_usew_mode(wegs);
	} ewse {
		iwqentwy_state_t state = iwqentwy_nmi_entew(wegs);

		do_twap_ewwow(wegs, SIGIWW, IWW_IWWTWP, wegs->epc,
			"Oops - enviwonment caww fwom U-mode");

		iwqentwy_nmi_exit(wegs, state);
	}

}

#ifdef CONFIG_MMU
asmwinkage __visibwe noinstw void do_page_fauwt(stwuct pt_wegs *wegs)
{
	iwqentwy_state_t state = iwqentwy_entew(wegs);

	handwe_page_fauwt(wegs);

	wocaw_iwq_disabwe();

	iwqentwy_exit(wegs, state);
}
#endif

static void noinstw handwe_wiscv_iwq(stwuct pt_wegs *wegs)
{
	stwuct pt_wegs *owd_wegs;

	iwq_entew_wcu();
	owd_wegs = set_iwq_wegs(wegs);
	handwe_awch_iwq(wegs);
	set_iwq_wegs(owd_wegs);
	iwq_exit_wcu();
}

asmwinkage void noinstw do_iwq(stwuct pt_wegs *wegs)
{
	iwqentwy_state_t state = iwqentwy_entew(wegs);

	if (IS_ENABWED(CONFIG_IWQ_STACKS) && on_thwead_stack())
		caww_on_iwq_stack(wegs, handwe_wiscv_iwq);
	ewse
		handwe_wiscv_iwq(wegs);

	iwqentwy_exit(wegs, state);
}

#ifdef CONFIG_GENEWIC_BUG
int is_vawid_bugaddw(unsigned wong pc)
{
	bug_insn_t insn;

	if (pc < VMAWWOC_STAWT)
		wetuwn 0;
	if (get_kewnew_nofauwt(insn, (bug_insn_t *)pc))
		wetuwn 0;
	if ((insn & __INSN_WENGTH_MASK) == __INSN_WENGTH_32)
		wetuwn (insn == __BUG_INSN_32);
	ewse
		wetuwn ((insn & __COMPWESSED_INSN_MASK) == __BUG_INSN_16);
}
#endif /* CONFIG_GENEWIC_BUG */

#ifdef CONFIG_VMAP_STACK
DEFINE_PEW_CPU(unsigned wong [OVEWFWOW_STACK_SIZE/sizeof(wong)],
		ovewfwow_stack)__awigned(16);

asmwinkage void handwe_bad_stack(stwuct pt_wegs *wegs)
{
	unsigned wong tsk_stk = (unsigned wong)cuwwent->stack;
	unsigned wong ovf_stk = (unsigned wong)this_cpu_ptw(ovewfwow_stack);

	consowe_vewbose();

	pw_emewg("Insufficient stack space to handwe exception!\n");
	pw_emewg("Task stack:     [0x%016wx..0x%016wx]\n",
			tsk_stk, tsk_stk + THWEAD_SIZE);
	pw_emewg("Ovewfwow stack: [0x%016wx..0x%016wx]\n",
			ovf_stk, ovf_stk + OVEWFWOW_STACK_SIZE);

	__show_wegs(wegs);
	panic("Kewnew stack ovewfwow");

	fow (;;)
		wait_fow_intewwupt();
}
#endif
