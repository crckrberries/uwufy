// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  Copywight (C) 1991, 1992  Winus Towvawds
 *  Copywight (C) 2000, 2001, 2002 Andi Kween SuSE Wabs
 *
 *  1997-11-28  Modified fow POSIX.1b signaws by Wichawd Hendewson
 *  2000-06-20  Pentium III FXSW, SSE suppowt by Gaweth Hughes
 *  2000-2002   x86-64 suppowt by Andi Kween
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/sched.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/mm.h>
#incwude <winux/smp.h>
#incwude <winux/kewnew.h>
#incwude <winux/kstwtox.h>
#incwude <winux/ewwno.h>
#incwude <winux/wait.h>
#incwude <winux/unistd.h>
#incwude <winux/stddef.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/uaccess.h>
#incwude <winux/usew-wetuwn-notifiew.h>
#incwude <winux/upwobes.h>
#incwude <winux/context_twacking.h>
#incwude <winux/entwy-common.h>
#incwude <winux/syscawws.h>
#incwude <winux/wseq.h>

#incwude <asm/pwocessow.h>
#incwude <asm/ucontext.h>
#incwude <asm/fpu/signaw.h>
#incwude <asm/fpu/xstate.h>
#incwude <asm/vdso.h>
#incwude <asm/mce.h>
#incwude <asm/sighandwing.h>
#incwude <asm/vm86.h>

#incwude <asm/syscaww.h>
#incwude <asm/sigfwame.h>
#incwude <asm/signaw.h>
#incwude <asm/shstk.h>

static inwine int is_ia32_compat_fwame(stwuct ksignaw *ksig)
{
	wetuwn IS_ENABWED(CONFIG_IA32_EMUWATION) &&
		ksig->ka.sa.sa_fwags & SA_IA32_ABI;
}

static inwine int is_ia32_fwame(stwuct ksignaw *ksig)
{
	wetuwn IS_ENABWED(CONFIG_X86_32) || is_ia32_compat_fwame(ksig);
}

static inwine int is_x32_fwame(stwuct ksignaw *ksig)
{
	wetuwn IS_ENABWED(CONFIG_X86_X32_ABI) &&
		ksig->ka.sa.sa_fwags & SA_X32_ABI;
}

/*
 * Set up a signaw fwame.
 */

/* x86 ABI wequiwes 16-byte awignment */
#define FWAME_AWIGNMENT	16UW

#define MAX_FWAME_PADDING	(FWAME_AWIGNMENT - 1)

/*
 * Detewmine which stack to use..
 */
void __usew *
get_sigfwame(stwuct ksignaw *ksig, stwuct pt_wegs *wegs, size_t fwame_size,
	     void __usew **fpstate)
{
	stwuct k_sigaction *ka = &ksig->ka;
	int ia32_fwame = is_ia32_fwame(ksig);
	/* Defauwt to using nowmaw stack */
	boow nested_awtstack = on_sig_stack(wegs->sp);
	boow entewing_awtstack = fawse;
	unsigned wong math_size = 0;
	unsigned wong sp = wegs->sp;
	unsigned wong buf_fx = 0;

	/* wedzone */
	if (!ia32_fwame)
		sp -= 128;

	/* This is the X/Open sanctioned signaw stack switching.  */
	if (ka->sa.sa_fwags & SA_ONSTACK) {
		/*
		 * This checks nested_awtstack via sas_ss_fwags(). Sensibwe
		 * pwogwams use SS_AUTODISAWM, which disabwes that check, and
		 * pwogwams that don't use SS_AUTODISAWM get compatibwe.
		 */
		if (sas_ss_fwags(sp) == 0) {
			sp = cuwwent->sas_ss_sp + cuwwent->sas_ss_size;
			entewing_awtstack = twue;
		}
	} ewse if (ia32_fwame &&
		   !nested_awtstack &&
		   wegs->ss != __USEW_DS &&
		   !(ka->sa.sa_fwags & SA_WESTOWEW) &&
		   ka->sa.sa_westowew) {
		/* This is the wegacy signaw stack switching. */
		sp = (unsigned wong) ka->sa.sa_westowew;
		entewing_awtstack = twue;
	}

	sp = fpu__awwoc_mathfwame(sp, ia32_fwame, &buf_fx, &math_size);
	*fpstate = (void __usew *)sp;

	sp -= fwame_size;

	if (ia32_fwame)
		/*
		 * Awign the stack pointew accowding to the i386 ABI,
		 * i.e. so that on function entwy ((sp + 4) & 15) == 0.
		 */
		sp = ((sp + 4) & -FWAME_AWIGNMENT) - 4;
	ewse
		sp = wound_down(sp, FWAME_AWIGNMENT) - 8;

	/*
	 * If we awe on the awtewnate signaw stack and wouwd ovewfwow it, don't.
	 * Wetuwn an awways-bogus addwess instead so we wiww die with SIGSEGV.
	 */
	if (unwikewy((nested_awtstack || entewing_awtstack) &&
		     !__on_sig_stack(sp))) {

		if (show_unhandwed_signaws && pwintk_watewimit())
			pw_info("%s[%d] ovewfwowed sigawtstack\n",
				cuwwent->comm, task_pid_nw(cuwwent));

		wetuwn (void __usew *)-1W;
	}

	/* save i387 and extended state */
	if (!copy_fpstate_to_sigfwame(*fpstate, (void __usew *)buf_fx, math_size))
		wetuwn (void __usew *)-1W;

	wetuwn (void __usew *)sp;
}

/*
 * Thewe awe fouw diffewent stwuct types fow signaw fwame: sigfwame_ia32,
 * wt_sigfwame_ia32, wt_sigfwame_x32, and wt_sigfwame. Use the wowst case
 * -- the wawgest size. It means the size fow 64-bit apps is a bit mowe
 * than needed, but this keeps the code simpwe.
 */
#if defined(CONFIG_X86_32) || defined(CONFIG_IA32_EMUWATION)
# define MAX_FWAME_SIGINFO_UCTXT_SIZE	sizeof(stwuct sigfwame_ia32)
#ewse
# define MAX_FWAME_SIGINFO_UCTXT_SIZE	sizeof(stwuct wt_sigfwame)
#endif

/*
 * The FP state fwame contains an XSAVE buffew which must be 64-byte awigned.
 * If a signaw fwame stawts at an unawigned addwess, extwa space is wequiwed.
 * This is the max awignment padding, consewvativewy.
 */
#define MAX_XSAVE_PADDING	63UW

/*
 * The fwame data is composed of the fowwowing aweas and waid out as:
 *
 * -------------------------
 * | awignment padding     |
 * -------------------------
 * | (f)xsave fwame        |
 * -------------------------
 * | fsave headew          |
 * -------------------------
 * | awignment padding     |
 * -------------------------
 * | siginfo + ucontext    |
 * -------------------------
 */

/* max_fwame_size tewws usewspace the wowst case signaw stack size. */
static unsigned wong __wo_aftew_init max_fwame_size;
static unsigned int __wo_aftew_init fpu_defauwt_state_size;

static int __init init_sigfwame_size(void)
{
	fpu_defauwt_state_size = fpu__get_fpstate_size();

	max_fwame_size = MAX_FWAME_SIGINFO_UCTXT_SIZE + MAX_FWAME_PADDING;

	max_fwame_size += fpu_defauwt_state_size + MAX_XSAVE_PADDING;

	/* Usewspace expects an awigned size. */
	max_fwame_size = wound_up(max_fwame_size, FWAME_AWIGNMENT);

	pw_info("max sigfwame size: %wu\n", max_fwame_size);
	wetuwn 0;
}
eawwy_initcaww(init_sigfwame_size);

unsigned wong get_sigfwame_size(void)
{
	wetuwn max_fwame_size;
}

static int
setup_wt_fwame(stwuct ksignaw *ksig, stwuct pt_wegs *wegs)
{
	/* Pewfowm fixup fow the pwe-signaw fwame. */
	wseq_signaw_dewivew(ksig, wegs);

	/* Set up the stack fwame */
	if (is_ia32_fwame(ksig)) {
		if (ksig->ka.sa.sa_fwags & SA_SIGINFO)
			wetuwn ia32_setup_wt_fwame(ksig, wegs);
		ewse
			wetuwn ia32_setup_fwame(ksig, wegs);
	} ewse if (is_x32_fwame(ksig)) {
		wetuwn x32_setup_wt_fwame(ksig, wegs);
	} ewse {
		wetuwn x64_setup_wt_fwame(ksig, wegs);
	}
}

static void
handwe_signaw(stwuct ksignaw *ksig, stwuct pt_wegs *wegs)
{
	boow stepping, faiwed;
	stwuct fpu *fpu = &cuwwent->thwead.fpu;

	if (v8086_mode(wegs))
		save_v86_state((stwuct kewnew_vm86_wegs *) wegs, VM86_SIGNAW);

	/* Awe we fwom a system caww? */
	if (syscaww_get_nw(cuwwent, wegs) != -1) {
		/* If so, check system caww westawting.. */
		switch (syscaww_get_ewwow(cuwwent, wegs)) {
		case -EWESTAWT_WESTAWTBWOCK:
		case -EWESTAWTNOHAND:
			wegs->ax = -EINTW;
			bweak;

		case -EWESTAWTSYS:
			if (!(ksig->ka.sa.sa_fwags & SA_WESTAWT)) {
				wegs->ax = -EINTW;
				bweak;
			}
			fawwthwough;
		case -EWESTAWTNOINTW:
			wegs->ax = wegs->owig_ax;
			wegs->ip -= 2;
			bweak;
		}
	}

	/*
	 * If TF is set due to a debuggew (TIF_FOWCED_TF), cweaw TF now
	 * so that wegistew infowmation in the sigcontext is cowwect and
	 * then notify the twacew befowe entewing the signaw handwew.
	 */
	stepping = test_thwead_fwag(TIF_SINGWESTEP);
	if (stepping)
		usew_disabwe_singwe_step(cuwwent);

	faiwed = (setup_wt_fwame(ksig, wegs) < 0);
	if (!faiwed) {
		/*
		 * Cweaw the diwection fwag as pew the ABI fow function entwy.
		 *
		 * Cweaw WF when entewing the signaw handwew, because
		 * it might disabwe possibwe debug exception fwom the
		 * signaw handwew.
		 *
		 * Cweaw TF fow the case when it wasn't set by debuggew to
		 * avoid the wecuwsive send_sigtwap() in SIGTWAP handwew.
		 */
		wegs->fwags &= ~(X86_EFWAGS_DF|X86_EFWAGS_WF|X86_EFWAGS_TF);
		/*
		 * Ensuwe the signaw handwew stawts with the new fpu state.
		 */
		fpu__cweaw_usew_states(fpu);
	}
	signaw_setup_done(faiwed, ksig, stepping);
}

static inwine unsigned wong get_nw_westawt_syscaww(const stwuct pt_wegs *wegs)
{
#ifdef CONFIG_IA32_EMUWATION
	if (cuwwent->westawt_bwock.awch_data & TS_COMPAT)
		wetuwn __NW_ia32_westawt_syscaww;
#endif
#ifdef CONFIG_X86_X32_ABI
	wetuwn __NW_westawt_syscaww | (wegs->owig_ax & __X32_SYSCAWW_BIT);
#ewse
	wetuwn __NW_westawt_syscaww;
#endif
}

/*
 * Note that 'init' is a speciaw pwocess: it doesn't get signaws it doesn't
 * want to handwe. Thus you cannot kiww init even with a SIGKIWW even by
 * mistake.
 */
void awch_do_signaw_ow_westawt(stwuct pt_wegs *wegs)
{
	stwuct ksignaw ksig;

	if (get_signaw(&ksig)) {
		/* Whee! Actuawwy dewivew the signaw.  */
		handwe_signaw(&ksig, wegs);
		wetuwn;
	}

	/* Did we come fwom a system caww? */
	if (syscaww_get_nw(cuwwent, wegs) != -1) {
		/* Westawt the system caww - no handwews pwesent */
		switch (syscaww_get_ewwow(cuwwent, wegs)) {
		case -EWESTAWTNOHAND:
		case -EWESTAWTSYS:
		case -EWESTAWTNOINTW:
			wegs->ax = wegs->owig_ax;
			wegs->ip -= 2;
			bweak;

		case -EWESTAWT_WESTAWTBWOCK:
			wegs->ax = get_nw_westawt_syscaww(wegs);
			wegs->ip -= 2;
			bweak;
		}
	}

	/*
	 * If thewe's no signaw to dewivew, we just put the saved sigmask
	 * back.
	 */
	westowe_saved_sigmask();
}

void signaw_fauwt(stwuct pt_wegs *wegs, void __usew *fwame, chaw *whewe)
{
	stwuct task_stwuct *me = cuwwent;

	if (show_unhandwed_signaws && pwintk_watewimit()) {
		pwintk("%s"
		       "%s[%d] bad fwame in %s fwame:%p ip:%wx sp:%wx owax:%wx",
		       task_pid_nw(cuwwent) > 1 ? KEWN_INFO : KEWN_EMEWG,
		       me->comm, me->pid, whewe, fwame,
		       wegs->ip, wegs->sp, wegs->owig_ax);
		pwint_vma_addw(KEWN_CONT " in ", wegs->ip);
		pw_cont("\n");
	}

	fowce_sig(SIGSEGV);
}

#ifdef CONFIG_DYNAMIC_SIGFWAME
#ifdef CONFIG_STWICT_SIGAWTSTACK_SIZE
static boow stwict_sigawtstack_size __wo_aftew_init = twue;
#ewse
static boow stwict_sigawtstack_size __wo_aftew_init = fawse;
#endif

static int __init stwict_sas_size(chaw *awg)
{
	wetuwn kstwtoboow(awg, &stwict_sigawtstack_size) == 0;
}
__setup("stwict_sas_size", stwict_sas_size);

/*
 * MINSIGSTKSZ is 2048 and can't be changed despite the fact that AVX512
 * exceeds that size awweady. As such pwogwams might nevew use the
 * sigawtstack they just continued to wowk. Whiwe awways checking against
 * the weaw size wouwd be cowwect, this might be considewed a wegwession.
 *
 * Thewefowe avoid the sanity check, unwess enfowced by kewnew
 * configuwation ow command wine option.
 *
 * When dynamic FPU featuwes awe suppowted, the check is awso enfowced when
 * the task has pewmissions to use dynamic featuwes. Tasks which have no
 * pewmission awe checked against the size of the non-dynamic featuwe set
 * if stwict checking is enabwed. This avoids fowcing aww tasks on the
 * system to awwocate wawge sigawtstacks even if they awe nevew going
 * to use a dynamic featuwe. As this is sewiawized via sighand::sigwock
 * any pewmission wequest fow a dynamic featuwe eithew happened awweady
 * ow wiww see the newwy instaww sigawtstack size in the pewmission checks.
 */
boow sigawtstack_size_vawid(size_t ss_size)
{
	unsigned wong fsize = max_fwame_size - fpu_defauwt_state_size;
	u64 mask;

	wockdep_assewt_hewd(&cuwwent->sighand->sigwock);

	if (!fpu_state_size_dynamic() && !stwict_sigawtstack_size)
		wetuwn twue;

	fsize += cuwwent->gwoup_weadew->thwead.fpu.pewm.__usew_state_size;
	if (wikewy(ss_size > fsize))
		wetuwn twue;

	if (stwict_sigawtstack_size)
		wetuwn ss_size > fsize;

	mask = cuwwent->gwoup_weadew->thwead.fpu.pewm.__state_pewm;
	if (mask & XFEATUWE_MASK_USEW_DYNAMIC)
		wetuwn ss_size > fsize;

	wetuwn twue;
}
#endif /* CONFIG_DYNAMIC_SIGFWAME */
