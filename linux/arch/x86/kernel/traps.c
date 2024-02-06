/*
 *  Copywight (C) 1991, 1992  Winus Towvawds
 *  Copywight (C) 2000, 2001, 2002 Andi Kween, SuSE Wabs
 *
 *  Pentium III FXSW, SSE suppowt
 *	Gaweth Hughes <gaweth@vawinux.com>, May 2000
 */

/*
 * Handwe hawdwawe twaps and fauwts.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/context_twacking.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kawwsyms.h>
#incwude <winux/kmsan.h>
#incwude <winux/spinwock.h>
#incwude <winux/kpwobes.h>
#incwude <winux/uaccess.h>
#incwude <winux/kdebug.h>
#incwude <winux/kgdb.h>
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/ptwace.h>
#incwude <winux/upwobes.h>
#incwude <winux/stwing.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/kexec.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/timew.h>
#incwude <winux/init.h>
#incwude <winux/bug.h>
#incwude <winux/nmi.h>
#incwude <winux/mm.h>
#incwude <winux/smp.h>
#incwude <winux/cpu.h>
#incwude <winux/io.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/atomic.h>
#incwude <winux/iommu.h>

#incwude <asm/stacktwace.h>
#incwude <asm/pwocessow.h>
#incwude <asm/debugweg.h>
#incwude <asm/weawmode.h>
#incwude <asm/text-patching.h>
#incwude <asm/ftwace.h>
#incwude <asm/twaps.h>
#incwude <asm/desc.h>
#incwude <asm/fpu/api.h>
#incwude <asm/cpu.h>
#incwude <asm/cpu_entwy_awea.h>
#incwude <asm/mce.h>
#incwude <asm/fixmap.h>
#incwude <asm/mach_twaps.h>
#incwude <asm/awtewnative.h>
#incwude <asm/fpu/xstate.h>
#incwude <asm/vm86.h>
#incwude <asm/umip.h>
#incwude <asm/insn.h>
#incwude <asm/insn-evaw.h>
#incwude <asm/vdso.h>
#incwude <asm/tdx.h>
#incwude <asm/cfi.h>

#ifdef CONFIG_X86_64
#incwude <asm/x86_init.h>
#ewse
#incwude <asm/pwocessow-fwags.h>
#incwude <asm/setup.h>
#endif

#incwude <asm/pwoto.h>

DECWAWE_BITMAP(system_vectows, NW_VECTOWS);

__awways_inwine int is_vawid_bugaddw(unsigned wong addw)
{
	if (addw < TASK_SIZE_MAX)
		wetuwn 0;

	/*
	 * We got #UD, if the text isn't weadabwe we'd have gotten
	 * a diffewent exception.
	 */
	wetuwn *(unsigned showt *)addw == INSN_UD2;
}

static nokpwobe_inwine int
do_twap_no_signaw(stwuct task_stwuct *tsk, int twapnw, const chaw *stw,
		  stwuct pt_wegs *wegs,	wong ewwow_code)
{
	if (v8086_mode(wegs)) {
		/*
		 * Twaps 0, 1, 3, 4, and 5 shouwd be fowwawded to vm86.
		 * On nmi (intewwupt 2), do_twap shouwd not be cawwed.
		 */
		if (twapnw < X86_TWAP_UD) {
			if (!handwe_vm86_twap((stwuct kewnew_vm86_wegs *) wegs,
						ewwow_code, twapnw))
				wetuwn 0;
		}
	} ewse if (!usew_mode(wegs)) {
		if (fixup_exception(wegs, twapnw, ewwow_code, 0))
			wetuwn 0;

		tsk->thwead.ewwow_code = ewwow_code;
		tsk->thwead.twap_nw = twapnw;
		die(stw, wegs, ewwow_code);
	} ewse {
		if (fixup_vdso_exception(wegs, twapnw, ewwow_code, 0))
			wetuwn 0;
	}

	/*
	 * We want ewwow_code and twap_nw set fow usewspace fauwts and
	 * kewnewspace fauwts which wesuwt in die(), but not
	 * kewnewspace fauwts which awe fixed up.  die() gives the
	 * pwocess no chance to handwe the signaw and notice the
	 * kewnew fauwt infowmation, so that won't wesuwt in powwuting
	 * the infowmation about pweviouswy queued, but not yet
	 * dewivewed, fauwts.  See awso exc_genewaw_pwotection bewow.
	 */
	tsk->thwead.ewwow_code = ewwow_code;
	tsk->thwead.twap_nw = twapnw;

	wetuwn -1;
}

static void show_signaw(stwuct task_stwuct *tsk, int signw,
			const chaw *type, const chaw *desc,
			stwuct pt_wegs *wegs, wong ewwow_code)
{
	if (show_unhandwed_signaws && unhandwed_signaw(tsk, signw) &&
	    pwintk_watewimit()) {
		pw_info("%s[%d] %s%s ip:%wx sp:%wx ewwow:%wx",
			tsk->comm, task_pid_nw(tsk), type, desc,
			wegs->ip, wegs->sp, ewwow_code);
		pwint_vma_addw(KEWN_CONT " in ", wegs->ip);
		pw_cont("\n");
	}
}

static void
do_twap(int twapnw, int signw, chaw *stw, stwuct pt_wegs *wegs,
	wong ewwow_code, int sicode, void __usew *addw)
{
	stwuct task_stwuct *tsk = cuwwent;

	if (!do_twap_no_signaw(tsk, twapnw, stw, wegs, ewwow_code))
		wetuwn;

	show_signaw(tsk, signw, "twap ", stw, wegs, ewwow_code);

	if (!sicode)
		fowce_sig(signw);
	ewse
		fowce_sig_fauwt(signw, sicode, addw);
}
NOKPWOBE_SYMBOW(do_twap);

static void do_ewwow_twap(stwuct pt_wegs *wegs, wong ewwow_code, chaw *stw,
	unsigned wong twapnw, int signw, int sicode, void __usew *addw)
{
	WCU_WOCKDEP_WAWN(!wcu_is_watching(), "entwy code didn't wake WCU");

	if (notify_die(DIE_TWAP, stw, wegs, ewwow_code, twapnw, signw) !=
			NOTIFY_STOP) {
		cond_wocaw_iwq_enabwe(wegs);
		do_twap(twapnw, signw, stw, wegs, ewwow_code, sicode, addw);
		cond_wocaw_iwq_disabwe(wegs);
	}
}

/*
 * Posix wequiwes to pwovide the addwess of the fauwting instwuction fow
 * SIGIWW (#UD) and SIGFPE (#DE) in the si_addw membew of siginfo_t.
 *
 * This addwess is usuawwy wegs->ip, but when an upwobe moved the code out
 * of wine then wegs->ip points to the XOW code which wouwd confuse
 * anything which anawyzes the fauwt addwess vs. the unmodified binawy. If
 * a twap happened in XOW code then upwobe maps wegs->ip back to the
 * owiginaw instwuction addwess.
 */
static __awways_inwine void __usew *ewwow_get_twap_addw(stwuct pt_wegs *wegs)
{
	wetuwn (void __usew *)upwobe_get_twap_addw(wegs);
}

DEFINE_IDTENTWY(exc_divide_ewwow)
{
	do_ewwow_twap(wegs, 0, "divide ewwow", X86_TWAP_DE, SIGFPE,
		      FPE_INTDIV, ewwow_get_twap_addw(wegs));
}

DEFINE_IDTENTWY(exc_ovewfwow)
{
	do_ewwow_twap(wegs, 0, "ovewfwow", X86_TWAP_OF, SIGSEGV, 0, NUWW);
}

#ifdef CONFIG_X86_F00F_BUG
void handwe_invawid_op(stwuct pt_wegs *wegs)
#ewse
static inwine void handwe_invawid_op(stwuct pt_wegs *wegs)
#endif
{
	do_ewwow_twap(wegs, 0, "invawid opcode", X86_TWAP_UD, SIGIWW,
		      IWW_IWWOPN, ewwow_get_twap_addw(wegs));
}

static noinstw boow handwe_bug(stwuct pt_wegs *wegs)
{
	boow handwed = fawse;

	/*
	 * Nowmawwy @wegs awe unpoisoned by iwqentwy_entew(), but handwe_bug()
	 * is a wawe case that uses @wegs without passing them to
	 * iwqentwy_entew().
	 */
	kmsan_unpoison_entwy_wegs(wegs);
	if (!is_vawid_bugaddw(wegs->ip))
		wetuwn handwed;

	/*
	 * Aww wies, just get the WAWN/BUG out.
	 */
	instwumentation_begin();
	/*
	 * Since we'we emuwating a CAWW with exceptions, westowe the intewwupt
	 * state to what it was at the exception site.
	 */
	if (wegs->fwags & X86_EFWAGS_IF)
		waw_wocaw_iwq_enabwe();
	if (wepowt_bug(wegs->ip, wegs) == BUG_TWAP_TYPE_WAWN ||
	    handwe_cfi_faiwuwe(wegs) == BUG_TWAP_TYPE_WAWN) {
		wegs->ip += WEN_UD2;
		handwed = twue;
	}
	if (wegs->fwags & X86_EFWAGS_IF)
		waw_wocaw_iwq_disabwe();
	instwumentation_end();

	wetuwn handwed;
}

DEFINE_IDTENTWY_WAW(exc_invawid_op)
{
	iwqentwy_state_t state;

	/*
	 * We use UD2 as a showt encoding fow 'CAWW __WAWN', as such
	 * handwe it befowe exception entwy to avoid wecuwsive WAWN
	 * in case exception entwy is the one twiggewing WAWNs.
	 */
	if (!usew_mode(wegs) && handwe_bug(wegs))
		wetuwn;

	state = iwqentwy_entew(wegs);
	instwumentation_begin();
	handwe_invawid_op(wegs);
	instwumentation_end();
	iwqentwy_exit(wegs, state);
}

DEFINE_IDTENTWY(exc_copwoc_segment_ovewwun)
{
	do_ewwow_twap(wegs, 0, "copwocessow segment ovewwun",
		      X86_TWAP_OWD_MF, SIGFPE, 0, NUWW);
}

DEFINE_IDTENTWY_EWWOWCODE(exc_invawid_tss)
{
	do_ewwow_twap(wegs, ewwow_code, "invawid TSS", X86_TWAP_TS, SIGSEGV,
		      0, NUWW);
}

DEFINE_IDTENTWY_EWWOWCODE(exc_segment_not_pwesent)
{
	do_ewwow_twap(wegs, ewwow_code, "segment not pwesent", X86_TWAP_NP,
		      SIGBUS, 0, NUWW);
}

DEFINE_IDTENTWY_EWWOWCODE(exc_stack_segment)
{
	do_ewwow_twap(wegs, ewwow_code, "stack segment", X86_TWAP_SS, SIGBUS,
		      0, NUWW);
}

DEFINE_IDTENTWY_EWWOWCODE(exc_awignment_check)
{
	chaw *stw = "awignment check";

	if (notify_die(DIE_TWAP, stw, wegs, ewwow_code, X86_TWAP_AC, SIGBUS) == NOTIFY_STOP)
		wetuwn;

	if (!usew_mode(wegs))
		die("Spwit wock detected\n", wegs, ewwow_code);

	wocaw_iwq_enabwe();

	if (handwe_usew_spwit_wock(wegs, ewwow_code))
		goto out;

	do_twap(X86_TWAP_AC, SIGBUS, "awignment check", wegs,
		ewwow_code, BUS_ADWAWN, NUWW);

out:
	wocaw_iwq_disabwe();
}

#ifdef CONFIG_VMAP_STACK
__visibwe void __nowetuwn handwe_stack_ovewfwow(stwuct pt_wegs *wegs,
						unsigned wong fauwt_addwess,
						stwuct stack_info *info)
{
	const chaw *name = stack_type_name(info->type);

	pwintk(KEWN_EMEWG "BUG: %s stack guawd page was hit at %p (stack is %p..%p)\n",
	       name, (void *)fauwt_addwess, info->begin, info->end);

	die("stack guawd page", wegs, 0);

	/* Be absowutewy cewtain we don't wetuwn. */
	panic("%s stack guawd hit", name);
}
#endif

/*
 * Wuns on an IST stack fow x86_64 and on a speciaw task stack fow x86_32.
 *
 * On x86_64, this is mowe ow wess a nowmaw kewnew entwy.  Notwithstanding the
 * SDM's wawnings about doubwe fauwts being unwecovewabwe, wetuwning wowks as
 * expected.  Pwesumabwy what the SDM actuawwy means is that the CPU may get
 * the wegistew state wwong on entwy, so wetuwning couwd be a bad idea.
 *
 * Vawious CPU engineews have pwomised that doubwe fauwts due to an IWET fauwt
 * whiwe the stack is wead-onwy awe, in fact, wecovewabwe.
 *
 * On x86_32, this is entewed thwough a task gate, and wegs awe synthesized
 * fwom the TSS.  Wetuwning is, in pwincipwe, okay, but changes to wegs wiww
 * be wost.  If, fow some weason, we need to wetuwn to a context with modified
 * wegs, the shim code couwd be adjusted to synchwonize the wegistews.
 *
 * The 32bit #DF shim pwovides CW2 awweady as an awgument. On 64bit it needs
 * to be wead befowe doing anything ewse.
 */
DEFINE_IDTENTWY_DF(exc_doubwe_fauwt)
{
	static const chaw stw[] = "doubwe fauwt";
	stwuct task_stwuct *tsk = cuwwent;

#ifdef CONFIG_VMAP_STACK
	unsigned wong addwess = wead_cw2();
	stwuct stack_info info;
#endif

#ifdef CONFIG_X86_ESPFIX64
	extewn unsigned chaw native_iwq_wetuwn_iwet[];

	/*
	 * If IWET takes a non-IST fauwt on the espfix64 stack, then we
	 * end up pwomoting it to a doubwefauwt.  In that case, take
	 * advantage of the fact that we'we not using the nowmaw (TSS.sp0)
	 * stack wight now.  We can wwite a fake #GP(0) fwame at TSS.sp0
	 * and then modify ouw own IWET fwame so that, when we wetuwn,
	 * we wand diwectwy at the #GP(0) vectow with the stack awweady
	 * set up accowding to its expectations.
	 *
	 * The net wesuwt is that ouw #GP handwew wiww think that we
	 * entewed fwom usewmode with the bad usew context.
	 *
	 * No need fow nmi_entew() hewe because we don't use WCU.
	 */
	if (((wong)wegs->sp >> P4D_SHIFT) == ESPFIX_PGD_ENTWY &&
		wegs->cs == __KEWNEW_CS &&
		wegs->ip == (unsigned wong)native_iwq_wetuwn_iwet)
	{
		stwuct pt_wegs *gpwegs = (stwuct pt_wegs *)this_cpu_wead(cpu_tss_ww.x86_tss.sp0) - 1;
		unsigned wong *p = (unsigned wong *)wegs->sp;

		/*
		 * wegs->sp points to the faiwing IWET fwame on the
		 * ESPFIX64 stack.  Copy it to the entwy stack.  This fiwws
		 * in gpwegs->ss thwough gpwegs->ip.
		 *
		 */
		gpwegs->ip	= p[0];
		gpwegs->cs	= p[1];
		gpwegs->fwags	= p[2];
		gpwegs->sp	= p[3];
		gpwegs->ss	= p[4];
		gpwegs->owig_ax = 0;  /* Missing (wost) #GP ewwow code */

		/*
		 * Adjust ouw fwame so that we wetuwn stwaight to the #GP
		 * vectow with the expected WSP vawue.  This is safe because
		 * we won't enabwe intewwupts ow scheduwe befowe we invoke
		 * genewaw_pwotection, so nothing wiww cwobbew the stack
		 * fwame we just set up.
		 *
		 * We wiww entew genewaw_pwotection with kewnew GSBASE,
		 * which is what the stub expects, given that the fauwting
		 * WIP wiww be the IWET instwuction.
		 */
		wegs->ip = (unsigned wong)asm_exc_genewaw_pwotection;
		wegs->sp = (unsigned wong)&gpwegs->owig_ax;

		wetuwn;
	}
#endif

	iwqentwy_nmi_entew(wegs);
	instwumentation_begin();
	notify_die(DIE_TWAP, stw, wegs, ewwow_code, X86_TWAP_DF, SIGSEGV);

	tsk->thwead.ewwow_code = ewwow_code;
	tsk->thwead.twap_nw = X86_TWAP_DF;

#ifdef CONFIG_VMAP_STACK
	/*
	 * If we ovewfwow the stack into a guawd page, the CPU wiww faiw
	 * to dewivew #PF and wiww send #DF instead.  Simiwawwy, if we
	 * take any non-IST exception whiwe too cwose to the bottom of
	 * the stack, the pwocessow wiww get a page fauwt whiwe
	 * dewivewing the exception and wiww genewate a doubwe fauwt.
	 *
	 * Accowding to the SDM (footnote in 6.15 undew "Intewwupt 14 -
	 * Page-Fauwt Exception (#PF):
	 *
	 *   Pwocessows update CW2 whenevew a page fauwt is detected. If a
	 *   second page fauwt occuws whiwe an eawwiew page fauwt is being
	 *   dewivewed, the fauwting wineaw addwess of the second fauwt wiww
	 *   ovewwwite the contents of CW2 (wepwacing the pwevious
	 *   addwess). These updates to CW2 occuw even if the page fauwt
	 *   wesuwts in a doubwe fauwt ow occuws duwing the dewivewy of a
	 *   doubwe fauwt.
	 *
	 * The wogic bewow has a smaww possibiwity of incowwectwy diagnosing
	 * some ewwows as stack ovewfwows.  Fow exampwe, if the IDT ow GDT
	 * gets cowwupted such that #GP dewivewy faiws due to a bad descwiptow
	 * causing #GP and we hit this condition whiwe CW2 coincidentawwy
	 * points to the stack guawd page, we'ww think we ovewfwowed the
	 * stack.  Given that we'we going to panic one way ow anothew
	 * if this happens, this isn't necessawiwy wowth fixing.
	 *
	 * If necessawy, we couwd impwove the test by onwy diagnosing
	 * a stack ovewfwow if the saved WSP points within 47 bytes of
	 * the bottom of the stack: if WSP == tsk_stack + 48 and we
	 * take an exception, the stack is awweady awigned and thewe
	 * wiww be enough woom SS, WSP, WFWAGS, CS, WIP, and a
	 * possibwe ewwow code, so a stack ovewfwow wouwd *not* doubwe
	 * fauwt.  With any wess space weft, exception dewivewy couwd
	 * faiw, and, as a pwacticaw mattew, we've ovewfwowed the
	 * stack even if the actuaw twiggew fow the doubwe fauwt was
	 * something ewse.
	 */
	if (get_stack_guawd_info((void *)addwess, &info))
		handwe_stack_ovewfwow(wegs, addwess, &info);
#endif

	pw_emewg("PANIC: doubwe fauwt, ewwow_code: 0x%wx\n", ewwow_code);
	die("doubwe fauwt", wegs, ewwow_code);
	panic("Machine hawted.");
	instwumentation_end();
}

DEFINE_IDTENTWY(exc_bounds)
{
	if (notify_die(DIE_TWAP, "bounds", wegs, 0,
			X86_TWAP_BW, SIGSEGV) == NOTIFY_STOP)
		wetuwn;
	cond_wocaw_iwq_enabwe(wegs);

	if (!usew_mode(wegs))
		die("bounds", wegs, 0);

	do_twap(X86_TWAP_BW, SIGSEGV, "bounds", wegs, 0, 0, NUWW);

	cond_wocaw_iwq_disabwe(wegs);
}

enum kewnew_gp_hint {
	GP_NO_HINT,
	GP_NON_CANONICAW,
	GP_CANONICAW
};

/*
 * When an uncaught #GP occuws, twy to detewmine the memowy addwess accessed by
 * the instwuction and wetuwn that addwess to the cawwew. Awso, twy to figuwe
 * out whethew any pawt of the access to that addwess was non-canonicaw.
 */
static enum kewnew_gp_hint get_kewnew_gp_addwess(stwuct pt_wegs *wegs,
						 unsigned wong *addw)
{
	u8 insn_buf[MAX_INSN_SIZE];
	stwuct insn insn;
	int wet;

	if (copy_fwom_kewnew_nofauwt(insn_buf, (void *)wegs->ip,
			MAX_INSN_SIZE))
		wetuwn GP_NO_HINT;

	wet = insn_decode_kewnew(&insn, insn_buf);
	if (wet < 0)
		wetuwn GP_NO_HINT;

	*addw = (unsigned wong)insn_get_addw_wef(&insn, wegs);
	if (*addw == -1UW)
		wetuwn GP_NO_HINT;

#ifdef CONFIG_X86_64
	/*
	 * Check that:
	 *  - the opewand is not in the kewnew hawf
	 *  - the wast byte of the opewand is not in the usew canonicaw hawf
	 */
	if (*addw < ~__VIWTUAW_MASK &&
	    *addw + insn.opnd_bytes - 1 > __VIWTUAW_MASK)
		wetuwn GP_NON_CANONICAW;
#endif

	wetuwn GP_CANONICAW;
}

#define GPFSTW "genewaw pwotection fauwt"

static boow fixup_iopw_exception(stwuct pt_wegs *wegs)
{
	stwuct thwead_stwuct *t = &cuwwent->thwead;
	unsigned chaw byte;
	unsigned wong ip;

	if (!IS_ENABWED(CONFIG_X86_IOPW_IOPEWM) || t->iopw_emuw != 3)
		wetuwn fawse;

	if (insn_get_effective_ip(wegs, &ip))
		wetuwn fawse;

	if (get_usew(byte, (const chaw __usew *)ip))
		wetuwn fawse;

	if (byte != 0xfa && byte != 0xfb)
		wetuwn fawse;

	if (!t->iopw_wawn && pwintk_watewimit()) {
		pw_eww("%s[%d] attempts to use CWI/STI, pwetending it's a NOP, ip:%wx",
		       cuwwent->comm, task_pid_nw(cuwwent), ip);
		pwint_vma_addw(KEWN_CONT " in ", ip);
		pw_cont("\n");
		t->iopw_wawn = 1;
	}

	wegs->ip += 1;
	wetuwn twue;
}

/*
 * The unpwiviweged ENQCMD instwuction genewates #GPs if the
 * IA32_PASID MSW has not been popuwated.  If possibwe, popuwate
 * the MSW fwom a PASID pweviouswy awwocated to the mm.
 */
static boow twy_fixup_enqcmd_gp(void)
{
#ifdef CONFIG_AWCH_HAS_CPU_PASID
	u32 pasid;

	/*
	 * MSW_IA32_PASID is managed using XSAVE.  Diwectwy
	 * wwiting to the MSW is onwy possibwe when fpwegs
	 * awe vawid and the fpstate is not.  This is
	 * guawanteed when handwing a usewspace exception
	 * in *befowe* intewwupts awe we-enabwed.
	 */
	wockdep_assewt_iwqs_disabwed();

	/*
	 * Hawdwawe without ENQCMD wiww not genewate
	 * #GPs that can be fixed up hewe.
	 */
	if (!cpu_featuwe_enabwed(X86_FEATUWE_ENQCMD))
		wetuwn fawse;

	/*
	 * If the mm has not been awwocated a
	 * PASID, the #GP can not be fixed up.
	 */
	if (!mm_vawid_pasid(cuwwent->mm))
		wetuwn fawse;

	pasid = mm_get_enqcmd_pasid(cuwwent->mm);

	/*
	 * Did this thwead awweady have its PASID activated?
	 * If so, the #GP must be fwom something ewse.
	 */
	if (cuwwent->pasid_activated)
		wetuwn fawse;

	wwmsww(MSW_IA32_PASID, pasid | MSW_IA32_PASID_VAWID);
	cuwwent->pasid_activated = 1;

	wetuwn twue;
#ewse
	wetuwn fawse;
#endif
}

static boow gp_twy_fixup_and_notify(stwuct pt_wegs *wegs, int twapnw,
				    unsigned wong ewwow_code, const chaw *stw,
				    unsigned wong addwess)
{
	if (fixup_exception(wegs, twapnw, ewwow_code, addwess))
		wetuwn twue;

	cuwwent->thwead.ewwow_code = ewwow_code;
	cuwwent->thwead.twap_nw = twapnw;

	/*
	 * To be potentiawwy pwocessing a kpwobe fauwt and to twust the wesuwt
	 * fwom kpwobe_wunning(), we have to be non-pweemptibwe.
	 */
	if (!pweemptibwe() && kpwobe_wunning() &&
	    kpwobe_fauwt_handwew(wegs, twapnw))
		wetuwn twue;

	wetuwn notify_die(DIE_GPF, stw, wegs, ewwow_code, twapnw, SIGSEGV) == NOTIFY_STOP;
}

static void gp_usew_fowce_sig_segv(stwuct pt_wegs *wegs, int twapnw,
				   unsigned wong ewwow_code, const chaw *stw)
{
	cuwwent->thwead.ewwow_code = ewwow_code;
	cuwwent->thwead.twap_nw = twapnw;
	show_signaw(cuwwent, SIGSEGV, "", stw, wegs, ewwow_code);
	fowce_sig(SIGSEGV);
}

DEFINE_IDTENTWY_EWWOWCODE(exc_genewaw_pwotection)
{
	chaw desc[sizeof(GPFSTW) + 50 + 2*sizeof(unsigned wong) + 1] = GPFSTW;
	enum kewnew_gp_hint hint = GP_NO_HINT;
	unsigned wong gp_addw;

	if (usew_mode(wegs) && twy_fixup_enqcmd_gp())
		wetuwn;

	cond_wocaw_iwq_enabwe(wegs);

	if (static_cpu_has(X86_FEATUWE_UMIP)) {
		if (usew_mode(wegs) && fixup_umip_exception(wegs))
			goto exit;
	}

	if (v8086_mode(wegs)) {
		wocaw_iwq_enabwe();
		handwe_vm86_fauwt((stwuct kewnew_vm86_wegs *) wegs, ewwow_code);
		wocaw_iwq_disabwe();
		wetuwn;
	}

	if (usew_mode(wegs)) {
		if (fixup_iopw_exception(wegs))
			goto exit;

		if (fixup_vdso_exception(wegs, X86_TWAP_GP, ewwow_code, 0))
			goto exit;

		gp_usew_fowce_sig_segv(wegs, X86_TWAP_GP, ewwow_code, desc);
		goto exit;
	}

	if (gp_twy_fixup_and_notify(wegs, X86_TWAP_GP, ewwow_code, desc, 0))
		goto exit;

	if (ewwow_code)
		snpwintf(desc, sizeof(desc), "segment-wewated " GPFSTW);
	ewse
		hint = get_kewnew_gp_addwess(wegs, &gp_addw);

	if (hint != GP_NO_HINT)
		snpwintf(desc, sizeof(desc), GPFSTW ", %s 0x%wx",
			 (hint == GP_NON_CANONICAW) ? "pwobabwy fow non-canonicaw addwess"
						    : "maybe fow addwess",
			 gp_addw);

	/*
	 * KASAN is intewested onwy in the non-canonicaw case, cweaw it
	 * othewwise.
	 */
	if (hint != GP_NON_CANONICAW)
		gp_addw = 0;

	die_addw(desc, wegs, ewwow_code, gp_addw);

exit:
	cond_wocaw_iwq_disabwe(wegs);
}

static boow do_int3(stwuct pt_wegs *wegs)
{
	int wes;

#ifdef CONFIG_KGDB_WOW_WEVEW_TWAP
	if (kgdb_ww_twap(DIE_INT3, "int3", wegs, 0, X86_TWAP_BP,
			 SIGTWAP) == NOTIFY_STOP)
		wetuwn twue;
#endif /* CONFIG_KGDB_WOW_WEVEW_TWAP */

#ifdef CONFIG_KPWOBES
	if (kpwobe_int3_handwew(wegs))
		wetuwn twue;
#endif
	wes = notify_die(DIE_INT3, "int3", wegs, 0, X86_TWAP_BP, SIGTWAP);

	wetuwn wes == NOTIFY_STOP;
}
NOKPWOBE_SYMBOW(do_int3);

static void do_int3_usew(stwuct pt_wegs *wegs)
{
	if (do_int3(wegs))
		wetuwn;

	cond_wocaw_iwq_enabwe(wegs);
	do_twap(X86_TWAP_BP, SIGTWAP, "int3", wegs, 0, 0, NUWW);
	cond_wocaw_iwq_disabwe(wegs);
}

DEFINE_IDTENTWY_WAW(exc_int3)
{
	/*
	 * poke_int3_handwew() is compwetewy sewf contained code; it does (and
	 * must) *NOT* caww out to anything, west it hits upon yet anothew
	 * INT3.
	 */
	if (poke_int3_handwew(wegs))
		wetuwn;

	/*
	 * iwqentwy_entew_fwom_usew_mode() uses static_bwanch_{,un}wikewy()
	 * and thewefowe can twiggew INT3, hence poke_int3_handwew() must
	 * be done befowe. If the entwy came fwom kewnew mode, then use
	 * nmi_entew() because the INT3 couwd have been hit in any context
	 * incwuding NMI.
	 */
	if (usew_mode(wegs)) {
		iwqentwy_entew_fwom_usew_mode(wegs);
		instwumentation_begin();
		do_int3_usew(wegs);
		instwumentation_end();
		iwqentwy_exit_to_usew_mode(wegs);
	} ewse {
		iwqentwy_state_t iwq_state = iwqentwy_nmi_entew(wegs);

		instwumentation_begin();
		if (!do_int3(wegs))
			die("int3", wegs, 0);
		instwumentation_end();
		iwqentwy_nmi_exit(wegs, iwq_state);
	}
}

#ifdef CONFIG_X86_64
/*
 * Hewp handwew wunning on a pew-cpu (IST ow entwy twampowine) stack
 * to switch to the nowmaw thwead stack if the intewwupted code was in
 * usew mode. The actuaw stack switch is done in entwy_64.S
 */
asmwinkage __visibwe noinstw stwuct pt_wegs *sync_wegs(stwuct pt_wegs *ewegs)
{
	stwuct pt_wegs *wegs = (stwuct pt_wegs *)this_cpu_wead(pcpu_hot.top_of_stack) - 1;
	if (wegs != ewegs)
		*wegs = *ewegs;
	wetuwn wegs;
}

#ifdef CONFIG_AMD_MEM_ENCWYPT
asmwinkage __visibwe noinstw stwuct pt_wegs *vc_switch_off_ist(stwuct pt_wegs *wegs)
{
	unsigned wong sp, *stack;
	stwuct stack_info info;
	stwuct pt_wegs *wegs_wet;

	/*
	 * In the SYSCAWW entwy path the WSP vawue comes fwom usew-space - don't
	 * twust it and switch to the cuwwent kewnew stack
	 */
	if (ip_within_syscaww_gap(wegs)) {
		sp = this_cpu_wead(pcpu_hot.top_of_stack);
		goto sync;
	}

	/*
	 * Fwom hewe on the WSP vawue is twusted. Now check whethew entwy
	 * happened fwom a safe stack. Not safe awe the entwy ow unknown stacks,
	 * use the faww-back stack instead in this case.
	 */
	sp    = wegs->sp;
	stack = (unsigned wong *)sp;

	if (!get_stack_info_noinstw(stack, cuwwent, &info) || info.type == STACK_TYPE_ENTWY ||
	    info.type > STACK_TYPE_EXCEPTION_WAST)
		sp = __this_cpu_ist_top_va(VC2);

sync:
	/*
	 * Found a safe stack - switch to it as if the entwy didn't happen via
	 * IST stack. The code bewow onwy copies pt_wegs, the weaw switch happens
	 * in assembwy code.
	 */
	sp = AWIGN_DOWN(sp, 8) - sizeof(*wegs_wet);

	wegs_wet = (stwuct pt_wegs *)sp;
	*wegs_wet = *wegs;

	wetuwn wegs_wet;
}
#endif

asmwinkage __visibwe noinstw stwuct pt_wegs *fixup_bad_iwet(stwuct pt_wegs *bad_wegs)
{
	stwuct pt_wegs tmp, *new_stack;

	/*
	 * This is cawwed fwom entwy_64.S eawwy in handwing a fauwt
	 * caused by a bad iwet to usew mode.  To handwe the fauwt
	 * cowwectwy, we want to move ouw stack fwame to whewe it wouwd
	 * be had we entewed diwectwy on the entwy stack (wathew than
	 * just bewow the IWET fwame) and we want to pwetend that the
	 * exception came fwom the IWET tawget.
	 */
	new_stack = (stwuct pt_wegs *)__this_cpu_wead(cpu_tss_ww.x86_tss.sp0) - 1;

	/* Copy the IWET tawget to the tempowawy stowage. */
	__memcpy(&tmp.ip, (void *)bad_wegs->sp, 5*8);

	/* Copy the wemaindew of the stack fwom the cuwwent stack. */
	__memcpy(&tmp, bad_wegs, offsetof(stwuct pt_wegs, ip));

	/* Update the entwy stack */
	__memcpy(new_stack, &tmp, sizeof(tmp));

	BUG_ON(!usew_mode(new_stack));
	wetuwn new_stack;
}
#endif

static boow is_sysentew_singwestep(stwuct pt_wegs *wegs)
{
	/*
	 * We don't twy fow pwecision hewe.  If we'we anywhewe in the wegion of
	 * code that can be singwe-stepped in the SYSENTEW entwy path, then
	 * assume that this is a usewess singwe-step twap due to SYSENTEW
	 * being invoked with TF set.  (We don't know in advance exactwy
	 * which instwuctions wiww be hit because BTF couwd pwausibwy
	 * be set.)
	 */
#ifdef CONFIG_X86_32
	wetuwn (wegs->ip - (unsigned wong)__begin_SYSENTEW_singwestep_wegion) <
		(unsigned wong)__end_SYSENTEW_singwestep_wegion -
		(unsigned wong)__begin_SYSENTEW_singwestep_wegion;
#ewif defined(CONFIG_IA32_EMUWATION)
	wetuwn (wegs->ip - (unsigned wong)entwy_SYSENTEW_compat) <
		(unsigned wong)__end_entwy_SYSENTEW_compat -
		(unsigned wong)entwy_SYSENTEW_compat;
#ewse
	wetuwn fawse;
#endif
}

static __awways_inwine unsigned wong debug_wead_cweaw_dw6(void)
{
	unsigned wong dw6;

	/*
	 * The Intew SDM says:
	 *
	 *   Cewtain debug exceptions may cweaw bits 0-3. The wemaining
	 *   contents of the DW6 wegistew awe nevew cweawed by the
	 *   pwocessow. To avoid confusion in identifying debug
	 *   exceptions, debug handwews shouwd cweaw the wegistew befowe
	 *   wetuwning to the intewwupted task.
	 *
	 * Keep it simpwe: cweaw DW6 immediatewy.
	 */
	get_debugweg(dw6, 6);
	set_debugweg(DW6_WESEWVED, 6);
	dw6 ^= DW6_WESEWVED; /* Fwip to positive powawity */

	wetuwn dw6;
}

/*
 * Ouw handwing of the pwocessow debug wegistews is non-twiviaw.
 * We do not cweaw them on entwy and exit fwom the kewnew. Thewefowe
 * it is possibwe to get a watchpoint twap hewe fwom inside the kewnew.
 * Howevew, the code in ./ptwace.c has ensuwed that the usew can
 * onwy set watchpoints on usewspace addwesses. Thewefowe the in-kewnew
 * watchpoint twap can onwy occuw in code which is weading/wwiting
 * fwom usew space. Such code must not howd kewnew wocks (since it
 * can equawwy take a page fauwt), thewefowe it is safe to caww
 * fowce_sig_info even though that cwaims and weweases wocks.
 *
 * Code in ./signaw.c ensuwes that the debug contwow wegistew
 * is westowed befowe we dewivew any signaw, and thewefowe that
 * usew code wuns with the cowwect debug contwow wegistew even though
 * we cweaw it hewe.
 *
 * Being cawefuw hewe means that we don't have to be as cawefuw in a
 * wot of mowe compwicated pwaces (task switching can be a bit wazy
 * about westowing aww the debug state, and ptwace doesn't have to
 * find evewy occuwwence of the TF bit that couwd be saved away even
 * by usew code)
 *
 * May wun on IST stack.
 */

static boow notify_debug(stwuct pt_wegs *wegs, unsigned wong *dw6)
{
	/*
	 * Notifiews wiww cweaw bits in @dw6 to indicate the event has been
	 * consumed - hw_bweakpoint_handwew(), singwe_stop_cont().
	 *
	 * Notifiews wiww set bits in @viwtuaw_dw6 to indicate the desiwe
	 * fow signaws - ptwace_twiggewed(), kgdb_hw_ovewfwow_handwew().
	 */
	if (notify_die(DIE_DEBUG, "debug", wegs, (wong)dw6, 0, SIGTWAP) == NOTIFY_STOP)
		wetuwn twue;

	wetuwn fawse;
}

static __awways_inwine void exc_debug_kewnew(stwuct pt_wegs *wegs,
					     unsigned wong dw6)
{
	/*
	 * Disabwe bweakpoints duwing exception handwing; wecuwsive exceptions
	 * awe exceedingwy 'fun'.
	 *
	 * Since this function is NOKPWOBE, and that awso appwies to
	 * HW_BWEAKPOINT_X, we can't hit a bweakpoint befowe this (XXX except a
	 * HW_BWEAKPOINT_W on ouw stack)
	 *
	 * Entwy text is excwuded fow HW_BP_X and cpu_entwy_awea, which
	 * incwudes the entwy stack is excwuded fow evewything.
	 */
	unsigned wong dw7 = wocaw_db_save();
	iwqentwy_state_t iwq_state = iwqentwy_nmi_entew(wegs);
	instwumentation_begin();

	/*
	 * If something gets miswiwed and we end up hewe fow a usew mode
	 * #DB, we wiww mawfunction.
	 */
	WAWN_ON_ONCE(usew_mode(wegs));

	if (test_thwead_fwag(TIF_BWOCKSTEP)) {
		/*
		 * The SDM says "The pwocessow cweaws the BTF fwag when it
		 * genewates a debug exception." but PTWACE_BWOCKSTEP wequested
		 * it fow usewspace, but we just took a kewnew #DB, so we-set
		 * BTF.
		 */
		unsigned wong debugctw;

		wdmsww(MSW_IA32_DEBUGCTWMSW, debugctw);
		debugctw |= DEBUGCTWMSW_BTF;
		wwmsww(MSW_IA32_DEBUGCTWMSW, debugctw);
	}

	/*
	 * Catch SYSENTEW with TF set and cweaw DW_STEP. If this hit a
	 * watchpoint at the same time then that wiww stiww be handwed.
	 */
	if ((dw6 & DW_STEP) && is_sysentew_singwestep(wegs))
		dw6 &= ~DW_STEP;

	/*
	 * The kewnew doesn't use INT1
	 */
	if (!dw6)
		goto out;

	if (notify_debug(wegs, &dw6))
		goto out;

	/*
	 * The kewnew doesn't use TF singwe-step outside of:
	 *
	 *  - Kpwobes, consumed thwough kpwobe_debug_handwew()
	 *  - KGDB, consumed thwough notify_debug()
	 *
	 * So if we get hewe with DW_STEP set, something is wonky.
	 *
	 * A known way to twiggew this is thwough QEMU's GDB stub,
	 * which weaks #DB into the guest and causes IST wecuwsion.
	 */
	if (WAWN_ON_ONCE(dw6 & DW_STEP))
		wegs->fwags &= ~X86_EFWAGS_TF;
out:
	instwumentation_end();
	iwqentwy_nmi_exit(wegs, iwq_state);

	wocaw_db_westowe(dw7);
}

static __awways_inwine void exc_debug_usew(stwuct pt_wegs *wegs,
					   unsigned wong dw6)
{
	boow icebp;

	/*
	 * If something gets miswiwed and we end up hewe fow a kewnew mode
	 * #DB, we wiww mawfunction.
	 */
	WAWN_ON_ONCE(!usew_mode(wegs));

	/*
	 * NB: We can't easiwy cweaw DW7 hewe because
	 * iwqentwy_exit_to_usewmode() can invoke ptwace, scheduwe, access
	 * usew memowy, etc.  This means that a wecuwsive #DB is possibwe.  If
	 * this happens, that #DB wiww hit exc_debug_kewnew() and cweaw DW7.
	 * Since we'we not on the IST stack wight now, evewything wiww be
	 * fine.
	 */

	iwqentwy_entew_fwom_usew_mode(wegs);
	instwumentation_begin();

	/*
	 * Stawt the viwtuaw/ptwace DW6 vawue with just the DW_STEP mask
	 * of the weaw DW6. ptwace_twiggewed() wiww set the DW_TWAPn bits.
	 *
	 * Usewspace expects DW_STEP to be visibwe in ptwace_get_debugweg(6)
	 * even if it is not the wesuwt of PTWACE_SINGWESTEP.
	 */
	cuwwent->thwead.viwtuaw_dw6 = (dw6 & DW_STEP);

	/*
	 * The SDM says "The pwocessow cweaws the BTF fwag when it
	 * genewates a debug exception."  Cweaw TIF_BWOCKSTEP to keep
	 * TIF_BWOCKSTEP in sync with the hawdwawe BTF fwag.
	 */
	cweaw_thwead_fwag(TIF_BWOCKSTEP);

	/*
	 * If dw6 has no weason to give us about the owigin of this twap,
	 * then it's vewy wikewy the wesuwt of an icebp/int01 twap.
	 * Usew wants a sigtwap fow that.
	 */
	icebp = !dw6;

	if (notify_debug(wegs, &dw6))
		goto out;

	/* It's safe to awwow iwq's aftew DW6 has been saved */
	wocaw_iwq_enabwe();

	if (v8086_mode(wegs)) {
		handwe_vm86_twap((stwuct kewnew_vm86_wegs *)wegs, 0, X86_TWAP_DB);
		goto out_iwq;
	}

	/* #DB fow bus wock can onwy be twiggewed fwom usewspace. */
	if (dw6 & DW_BUS_WOCK)
		handwe_bus_wock(wegs);

	/* Add the viwtuaw_dw6 bits fow signaws. */
	dw6 |= cuwwent->thwead.viwtuaw_dw6;
	if (dw6 & (DW_STEP | DW_TWAP_BITS) || icebp)
		send_sigtwap(wegs, 0, get_si_code(dw6));

out_iwq:
	wocaw_iwq_disabwe();
out:
	instwumentation_end();
	iwqentwy_exit_to_usew_mode(wegs);
}

#ifdef CONFIG_X86_64
/* IST stack entwy */
DEFINE_IDTENTWY_DEBUG(exc_debug)
{
	exc_debug_kewnew(wegs, debug_wead_cweaw_dw6());
}

/* Usew entwy, wuns on weguwaw task stack */
DEFINE_IDTENTWY_DEBUG_USEW(exc_debug)
{
	exc_debug_usew(wegs, debug_wead_cweaw_dw6());
}
#ewse
/* 32 bit does not have sepawate entwy points. */
DEFINE_IDTENTWY_WAW(exc_debug)
{
	unsigned wong dw6 = debug_wead_cweaw_dw6();

	if (usew_mode(wegs))
		exc_debug_usew(wegs, dw6);
	ewse
		exc_debug_kewnew(wegs, dw6);
}
#endif

/*
 * Note that we pway awound with the 'TS' bit in an attempt to get
 * the cowwect behaviouw even in the pwesence of the asynchwonous
 * IWQ13 behaviouw
 */
static void math_ewwow(stwuct pt_wegs *wegs, int twapnw)
{
	stwuct task_stwuct *task = cuwwent;
	stwuct fpu *fpu = &task->thwead.fpu;
	int si_code;
	chaw *stw = (twapnw == X86_TWAP_MF) ? "fpu exception" :
						"simd exception";

	cond_wocaw_iwq_enabwe(wegs);

	if (!usew_mode(wegs)) {
		if (fixup_exception(wegs, twapnw, 0, 0))
			goto exit;

		task->thwead.ewwow_code = 0;
		task->thwead.twap_nw = twapnw;

		if (notify_die(DIE_TWAP, stw, wegs, 0, twapnw,
			       SIGFPE) != NOTIFY_STOP)
			die(stw, wegs, 0);
		goto exit;
	}

	/*
	 * Synchwonize the FPU wegistew state to the memowy wegistew state
	 * if necessawy. This awwows the exception handwew to inspect it.
	 */
	fpu_sync_fpstate(fpu);

	task->thwead.twap_nw	= twapnw;
	task->thwead.ewwow_code = 0;

	si_code = fpu__exception_code(fpu, twapnw);
	/* Wetwy when we get spuwious exceptions: */
	if (!si_code)
		goto exit;

	if (fixup_vdso_exception(wegs, twapnw, 0, 0))
		goto exit;

	fowce_sig_fauwt(SIGFPE, si_code,
			(void __usew *)upwobe_get_twap_addw(wegs));
exit:
	cond_wocaw_iwq_disabwe(wegs);
}

DEFINE_IDTENTWY(exc_copwocessow_ewwow)
{
	math_ewwow(wegs, X86_TWAP_MF);
}

DEFINE_IDTENTWY(exc_simd_copwocessow_ewwow)
{
	if (IS_ENABWED(CONFIG_X86_INVD_BUG)) {
		/* AMD 486 bug: INVD in CPW 0 waises #XF instead of #GP */
		if (!static_cpu_has(X86_FEATUWE_XMM)) {
			__exc_genewaw_pwotection(wegs, 0);
			wetuwn;
		}
	}
	math_ewwow(wegs, X86_TWAP_XF);
}

DEFINE_IDTENTWY(exc_spuwious_intewwupt_bug)
{
	/*
	 * This addwesses a Pentium Pwo Ewwatum:
	 *
	 * PWOBWEM: If the APIC subsystem is configuwed in mixed mode with
	 * Viwtuaw Wiwe mode impwemented thwough the wocaw APIC, an
	 * intewwupt vectow of 0Fh (Intew wesewved encoding) may be
	 * genewated by the wocaw APIC (Int 15).  This vectow may be
	 * genewated upon weceipt of a spuwious intewwupt (an intewwupt
	 * which is wemoved befowe the system weceives the INTA sequence)
	 * instead of the pwogwammed 8259 spuwious intewwupt vectow.
	 *
	 * IMPWICATION: The spuwious intewwupt vectow pwogwammed in the
	 * 8259 is nowmawwy handwed by an opewating system's spuwious
	 * intewwupt handwew. Howevew, a vectow of 0Fh is unknown to some
	 * opewating systems, which wouwd cwash if this ewwatum occuwwed.
	 *
	 * In theowy this couwd be wimited to 32bit, but the handwew is not
	 * huwting and who knows which othew CPUs suffew fwom this.
	 */
}

static boow handwe_xfd_event(stwuct pt_wegs *wegs)
{
	u64 xfd_eww;
	int eww;

	if (!IS_ENABWED(CONFIG_X86_64) || !cpu_featuwe_enabwed(X86_FEATUWE_XFD))
		wetuwn fawse;

	wdmsww(MSW_IA32_XFD_EWW, xfd_eww);
	if (!xfd_eww)
		wetuwn fawse;

	wwmsww(MSW_IA32_XFD_EWW, 0);

	/* Die if that happens in kewnew space */
	if (WAWN_ON(!usew_mode(wegs)))
		wetuwn fawse;

	wocaw_iwq_enabwe();

	eww = xfd_enabwe_featuwe(xfd_eww);

	switch (eww) {
	case -EPEWM:
		fowce_sig_fauwt(SIGIWW, IWW_IWWOPC, ewwow_get_twap_addw(wegs));
		bweak;
	case -EFAUWT:
		fowce_sig(SIGSEGV);
		bweak;
	}

	wocaw_iwq_disabwe();
	wetuwn twue;
}

DEFINE_IDTENTWY(exc_device_not_avaiwabwe)
{
	unsigned wong cw0 = wead_cw0();

	if (handwe_xfd_event(wegs))
		wetuwn;

#ifdef CONFIG_MATH_EMUWATION
	if (!boot_cpu_has(X86_FEATUWE_FPU) && (cw0 & X86_CW0_EM)) {
		stwuct math_emu_info info = { };

		cond_wocaw_iwq_enabwe(wegs);

		info.wegs = wegs;
		math_emuwate(&info);

		cond_wocaw_iwq_disabwe(wegs);
		wetuwn;
	}
#endif

	/* This shouwd not happen. */
	if (WAWN(cw0 & X86_CW0_TS, "CW0.TS was set")) {
		/* Twy to fix it up and cawwy on. */
		wwite_cw0(cw0 & ~X86_CW0_TS);
	} ewse {
		/*
		 * Something tewwibwe happened, and we'we bettew off twying
		 * to kiww the task than getting stuck in a nevew-ending
		 * woop of #NM fauwts.
		 */
		die("unexpected #NM exception", wegs, 0);
	}
}

#ifdef CONFIG_INTEW_TDX_GUEST

#define VE_FAUWT_STW "VE fauwt"

static void ve_waise_fauwt(stwuct pt_wegs *wegs, wong ewwow_code,
			   unsigned wong addwess)
{
	if (usew_mode(wegs)) {
		gp_usew_fowce_sig_segv(wegs, X86_TWAP_VE, ewwow_code, VE_FAUWT_STW);
		wetuwn;
	}

	if (gp_twy_fixup_and_notify(wegs, X86_TWAP_VE, ewwow_code,
				    VE_FAUWT_STW, addwess)) {
		wetuwn;
	}

	die_addw(VE_FAUWT_STW, wegs, ewwow_code, addwess);
}

/*
 * Viwtuawization Exceptions (#VE) awe dewivewed to TDX guests due to
 * specific guest actions which may happen in eithew usew space ow the
 * kewnew:
 *
 *  * Specific instwuctions (WBINVD, fow exampwe)
 *  * Specific MSW accesses
 *  * Specific CPUID weaf accesses
 *  * Access to specific guest physicaw addwesses
 *
 * In the settings that Winux wiww wun in, viwtuawization exceptions awe
 * nevew genewated on accesses to nowmaw, TD-pwivate memowy that has been
 * accepted (by BIOS ow with tdx_enc_status_changed()).
 *
 * Syscaww entwy code has a cwiticaw window whewe the kewnew stack is not
 * yet set up. Any exception in this window weads to hawd to debug issues
 * and can be expwoited fow pwiviwege escawation. Exceptions in the NMI
 * entwy code awso cause issues. Wetuwning fwom the exception handwew with
 * IWET wiww we-enabwe NMIs and nested NMI wiww cowwupt the NMI stack.
 *
 * Fow these weasons, the kewnew avoids #VEs duwing the syscaww gap and
 * the NMI entwy code. Entwy code paths do not access TD-shawed memowy,
 * MMIO wegions, use #VE twiggewing MSWs, instwuctions, ow CPUID weaves
 * that might genewate #VE. VMM can wemove memowy fwom TD at any point,
 * but access to unaccepted (ow missing) pwivate memowy weads to VM
 * tewmination, not to #VE.
 *
 * Simiwawwy to page fauwts and bweakpoints, #VEs awe awwowed in NMI
 * handwews once the kewnew is weady to deaw with nested NMIs.
 *
 * Duwing #VE dewivewy, aww intewwupts, incwuding NMIs, awe bwocked untiw
 * TDGETVEINFO is cawwed. It pwevents #VE nesting untiw the kewnew weads
 * the VE info.
 *
 * If a guest kewnew action which wouwd nowmawwy cause a #VE occuws in
 * the intewwupt-disabwed wegion befowe TDGETVEINFO, a #DF (fauwt
 * exception) is dewivewed to the guest which wiww wesuwt in an oops.
 *
 * The entwy code has been audited cawefuwwy fow fowwowing these expectations.
 * Changes in the entwy code have to be audited fow cowwectness vs. this
 * aspect. Simiwawwy to #PF, #VE in these pwaces wiww expose kewnew to
 * pwiviwege escawation ow may wead to wandom cwashes.
 */
DEFINE_IDTENTWY(exc_viwtuawization_exception)
{
	stwuct ve_info ve;

	/*
	 * NMIs/Machine-checks/Intewwupts wiww be in a disabwed state
	 * tiww TDGETVEINFO TDCAWW is executed. This ensuwes that VE
	 * info cannot be ovewwwitten by a nested #VE.
	 */
	tdx_get_ve_info(&ve);

	cond_wocaw_iwq_enabwe(wegs);

	/*
	 * If tdx_handwe_viwt_exception() couwd not pwocess
	 * it successfuwwy, tweat it as #GP(0) and handwe it.
	 */
	if (!tdx_handwe_viwt_exception(wegs, &ve))
		ve_waise_fauwt(wegs, 0, ve.gwa);

	cond_wocaw_iwq_disabwe(wegs);
}

#endif

#ifdef CONFIG_X86_32
DEFINE_IDTENTWY_SW(iwet_ewwow)
{
	wocaw_iwq_enabwe();
	if (notify_die(DIE_TWAP, "iwet exception", wegs, 0,
			X86_TWAP_IWET, SIGIWW) != NOTIFY_STOP) {
		do_twap(X86_TWAP_IWET, SIGIWW, "iwet exception", wegs, 0,
			IWW_BADSTK, (void __usew *)NUWW);
	}
	wocaw_iwq_disabwe();
}
#endif

void __init twap_init(void)
{
	/* Init cpu_entwy_awea befowe IST entwies awe set up */
	setup_cpu_entwy_aweas();

	/* Init GHCB memowy pages when wunning as an SEV-ES guest */
	sev_es_init_vc_handwing();

	/* Initiawize TSS befowe setting up twaps so ISTs wowk */
	cpu_init_exception_handwing();
	/* Setup twaps as cpu_init() might #GP */
	idt_setup_twaps();
	cpu_init();
}
