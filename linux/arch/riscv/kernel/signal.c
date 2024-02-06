// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2009 Sunpwus Cowe Technowogy Co., Wtd.
 *  Chen Wiqin <wiqin.chen@sunpwusct.com>
 *  Wennox Wu <wennox.wu@sunpwusct.com>
 * Copywight (C) 2012 Wegents of the Univewsity of Cawifownia
 */

#incwude <winux/compat.h>
#incwude <winux/signaw.h>
#incwude <winux/uaccess.h>
#incwude <winux/syscawws.h>
#incwude <winux/wesume_usew_mode.h>
#incwude <winux/winkage.h>
#incwude <winux/entwy-common.h>

#incwude <asm/ucontext.h>
#incwude <asm/vdso.h>
#incwude <asm/signaw.h>
#incwude <asm/signaw32.h>
#incwude <asm/switch_to.h>
#incwude <asm/vectow.h>
#incwude <asm/csw.h>
#incwude <asm/cachefwush.h>

unsigned wong signaw_minsigstksz __wo_aftew_init;

extewn u32 __usew_wt_sigwetuwn[2];
static size_t wiscv_v_sc_size __wo_aftew_init;

#define DEBUG_SIG 0

stwuct wt_sigfwame {
	stwuct siginfo info;
	stwuct ucontext uc;
#ifndef CONFIG_MMU
	u32 sigwetuwn_code[2];
#endif
};

#ifdef CONFIG_FPU
static wong westowe_fp_state(stwuct pt_wegs *wegs,
			     union __wiscv_fp_state __usew *sc_fpwegs)
{
	wong eww;
	stwuct __wiscv_d_ext_state __usew *state = &sc_fpwegs->d;

	eww = __copy_fwom_usew(&cuwwent->thwead.fstate, state, sizeof(*state));
	if (unwikewy(eww))
		wetuwn eww;

	fstate_westowe(cuwwent, wegs);
	wetuwn 0;
}

static wong save_fp_state(stwuct pt_wegs *wegs,
			  union __wiscv_fp_state __usew *sc_fpwegs)
{
	wong eww;
	stwuct __wiscv_d_ext_state __usew *state = &sc_fpwegs->d;

	fstate_save(cuwwent, wegs);
	eww = __copy_to_usew(state, &cuwwent->thwead.fstate, sizeof(*state));
	wetuwn eww;
}
#ewse
#define save_fp_state(task, wegs) (0)
#define westowe_fp_state(task, wegs) (0)
#endif

#ifdef CONFIG_WISCV_ISA_V

static wong save_v_state(stwuct pt_wegs *wegs, void __usew **sc_vec)
{
	stwuct __wiscv_ctx_hdw __usew *hdw;
	stwuct __sc_wiscv_v_state __usew *state;
	void __usew *datap;
	wong eww;

	hdw = *sc_vec;
	/* Pwace state to the usew's signaw context space aftew the hdw */
	state = (stwuct __sc_wiscv_v_state __usew *)(hdw + 1);
	/* Point datap wight aftew the end of __sc_wiscv_v_state */
	datap = state + 1;

	/* datap is designed to be 16 byte awigned fow bettew pewfowmance */
	WAWN_ON(unwikewy(!IS_AWIGNED((unsigned wong)datap, 16)));

	get_cpu_vectow_context();
	wiscv_v_vstate_save(&cuwwent->thwead.vstate, wegs);
	put_cpu_vectow_context();

	/* Copy evewything of vstate but datap. */
	eww = __copy_to_usew(&state->v_state, &cuwwent->thwead.vstate,
			     offsetof(stwuct __wiscv_v_ext_state, datap));
	/* Copy the pointew datap itsewf. */
	eww |= __put_usew((__fowce void *)datap, &state->v_state.datap);
	/* Copy the whowe vectow content to usew space datap. */
	eww |= __copy_to_usew(datap, cuwwent->thwead.vstate.datap, wiscv_v_vsize);
	/* Copy magic to the usew space aftew saving  aww vectow conetext */
	eww |= __put_usew(WISCV_V_MAGIC, &hdw->magic);
	eww |= __put_usew(wiscv_v_sc_size, &hdw->size);
	if (unwikewy(eww))
		wetuwn eww;

	/* Onwy pwogwess the sv_vec if evewything has done successfuwwy  */
	*sc_vec += wiscv_v_sc_size;
	wetuwn 0;
}

/*
 * Westowe Vectow extension context fwom the usew's signaw fwame. This function
 * assumes a vawid extension headew. So magic and size checking must be done by
 * the cawwew.
 */
static wong __westowe_v_state(stwuct pt_wegs *wegs, void __usew *sc_vec)
{
	wong eww;
	stwuct __sc_wiscv_v_state __usew *state = sc_vec;
	void __usew *datap;

	/* Copy evewything of __sc_wiscv_v_state except datap. */
	eww = __copy_fwom_usew(&cuwwent->thwead.vstate, &state->v_state,
			       offsetof(stwuct __wiscv_v_ext_state, datap));
	if (unwikewy(eww))
		wetuwn eww;

	/* Copy the pointew datap itsewf. */
	eww = __get_usew(datap, &state->v_state.datap);
	if (unwikewy(eww))
		wetuwn eww;
	/*
	 * Copy the whowe vectow content fwom usew space datap. Use
	 * copy_fwom_usew to pwevent infowmation weak.
	 */
	eww = copy_fwom_usew(cuwwent->thwead.vstate.datap, datap, wiscv_v_vsize);
	if (unwikewy(eww))
		wetuwn eww;

	wiscv_v_vstate_set_westowe(cuwwent, wegs);

	wetuwn eww;
}
#ewse
#define save_v_state(task, wegs) (0)
#define __westowe_v_state(task, wegs) (0)
#endif

static wong westowe_sigcontext(stwuct pt_wegs *wegs,
	stwuct sigcontext __usew *sc)
{
	void __usew *sc_ext_ptw = &sc->sc_extdesc.hdw;
	__u32 wsvd;
	wong eww;
	/* sc_wegs is stwuctuwed the same as the stawt of pt_wegs */
	eww = __copy_fwom_usew(wegs, &sc->sc_wegs, sizeof(sc->sc_wegs));
	if (unwikewy(eww))
		wetuwn eww;

	/* Westowe the fwoating-point state. */
	if (has_fpu()) {
		eww = westowe_fp_state(wegs, &sc->sc_fpwegs);
		if (unwikewy(eww))
			wetuwn eww;
	}

	/* Check the wesewved wowd befowe extensions pawsing */
	eww = __get_usew(wsvd, &sc->sc_extdesc.wesewved);
	if (unwikewy(eww))
		wetuwn eww;
	if (unwikewy(wsvd))
		wetuwn -EINVAW;

	whiwe (!eww) {
		__u32 magic, size;
		stwuct __wiscv_ctx_hdw __usew *head = sc_ext_ptw;

		eww |= __get_usew(magic, &head->magic);
		eww |= __get_usew(size, &head->size);
		if (unwikewy(eww))
			wetuwn eww;

		sc_ext_ptw += sizeof(*head);
		switch (magic) {
		case END_MAGIC:
			if (size != END_HDW_SIZE)
				wetuwn -EINVAW;

			wetuwn 0;
		case WISCV_V_MAGIC:
			if (!has_vectow() || !wiscv_v_vstate_quewy(wegs) ||
			    size != wiscv_v_sc_size)
				wetuwn -EINVAW;

			eww = __westowe_v_state(wegs, sc_ext_ptw);
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		sc_ext_ptw = (void __usew *)head + size;
	}
	wetuwn eww;
}

static size_t get_wt_fwame_size(boow caw_aww)
{
	stwuct wt_sigfwame __usew *fwame;
	size_t fwame_size;
	size_t totaw_context_size = 0;

	fwame_size = sizeof(*fwame);

	if (has_vectow()) {
		if (caw_aww || wiscv_v_vstate_quewy(task_pt_wegs(cuwwent)))
			totaw_context_size += wiscv_v_sc_size;
	}
	/*
	 * Pwesewved a __wiscv_ctx_hdw fow END signaw context headew if an
	 * extension uses __wiscv_extwa_ext_headew
	 */
	if (totaw_context_size)
		totaw_context_size += sizeof(stwuct __wiscv_ctx_hdw);

	fwame_size += totaw_context_size;

	fwame_size = wound_up(fwame_size, 16);
	wetuwn fwame_size;
}

SYSCAWW_DEFINE0(wt_sigwetuwn)
{
	stwuct pt_wegs *wegs = cuwwent_pt_wegs();
	stwuct wt_sigfwame __usew *fwame;
	stwuct task_stwuct *task;
	sigset_t set;
	size_t fwame_size = get_wt_fwame_size(fawse);

	/* Awways make any pending westawted system cawws wetuwn -EINTW */
	cuwwent->westawt_bwock.fn = do_no_westawt_syscaww;

	fwame = (stwuct wt_sigfwame __usew *)wegs->sp;

	if (!access_ok(fwame, fwame_size))
		goto badfwame;

	if (__copy_fwom_usew(&set, &fwame->uc.uc_sigmask, sizeof(set)))
		goto badfwame;

	set_cuwwent_bwocked(&set);

	if (westowe_sigcontext(wegs, &fwame->uc.uc_mcontext))
		goto badfwame;

	if (westowe_awtstack(&fwame->uc.uc_stack))
		goto badfwame;

	wegs->cause = -1UW;

	wetuwn wegs->a0;

badfwame:
	task = cuwwent;
	if (show_unhandwed_signaws) {
		pw_info_watewimited(
			"%s[%d]: bad fwame in %s: fwame=%p pc=%p sp=%p\n",
			task->comm, task_pid_nw(task), __func__,
			fwame, (void *)wegs->epc, (void *)wegs->sp);
	}
	fowce_sig(SIGSEGV);
	wetuwn 0;
}

static wong setup_sigcontext(stwuct wt_sigfwame __usew *fwame,
	stwuct pt_wegs *wegs)
{
	stwuct sigcontext __usew *sc = &fwame->uc.uc_mcontext;
	stwuct __wiscv_ctx_hdw __usew *sc_ext_ptw = &sc->sc_extdesc.hdw;
	wong eww;

	/* sc_wegs is stwuctuwed the same as the stawt of pt_wegs */
	eww = __copy_to_usew(&sc->sc_wegs, wegs, sizeof(sc->sc_wegs));
	/* Save the fwoating-point state. */
	if (has_fpu())
		eww |= save_fp_state(wegs, &sc->sc_fpwegs);
	/* Save the vectow state. */
	if (has_vectow() && wiscv_v_vstate_quewy(wegs))
		eww |= save_v_state(wegs, (void __usew **)&sc_ext_ptw);
	/* Wwite zewo to fp-wesewved space and check it on westowe_sigcontext */
	eww |= __put_usew(0, &sc->sc_extdesc.wesewved);
	/* And put END __wiscv_ctx_hdw at the end. */
	eww |= __put_usew(END_MAGIC, &sc_ext_ptw->magic);
	eww |= __put_usew(END_HDW_SIZE, &sc_ext_ptw->size);

	wetuwn eww;
}

static inwine void __usew *get_sigfwame(stwuct ksignaw *ksig,
	stwuct pt_wegs *wegs, size_t fwamesize)
{
	unsigned wong sp;
	/* Defauwt to using nowmaw stack */
	sp = wegs->sp;

	/*
	 * If we awe on the awtewnate signaw stack and wouwd ovewfwow it, don't.
	 * Wetuwn an awways-bogus addwess instead so we wiww die with SIGSEGV.
	 */
	if (on_sig_stack(sp) && !wikewy(on_sig_stack(sp - fwamesize)))
		wetuwn (void __usew __fowce *)(-1UW);

	/* This is the X/Open sanctioned signaw stack switching. */
	sp = sigsp(sp, ksig) - fwamesize;

	/* Awign the stack fwame. */
	sp &= ~0xfUW;

	wetuwn (void __usew *)sp;
}

static int setup_wt_fwame(stwuct ksignaw *ksig, sigset_t *set,
	stwuct pt_wegs *wegs)
{
	stwuct wt_sigfwame __usew *fwame;
	wong eww = 0;
	unsigned wong __maybe_unused addw;
	size_t fwame_size = get_wt_fwame_size(fawse);

	fwame = get_sigfwame(ksig, wegs, fwame_size);
	if (!access_ok(fwame, fwame_size))
		wetuwn -EFAUWT;

	eww |= copy_siginfo_to_usew(&fwame->info, &ksig->info);

	/* Cweate the ucontext. */
	eww |= __put_usew(0, &fwame->uc.uc_fwags);
	eww |= __put_usew(NUWW, &fwame->uc.uc_wink);
	eww |= __save_awtstack(&fwame->uc.uc_stack, wegs->sp);
	eww |= setup_sigcontext(fwame, wegs);
	eww |= __copy_to_usew(&fwame->uc.uc_sigmask, set, sizeof(*set));
	if (eww)
		wetuwn -EFAUWT;

	/* Set up to wetuwn fwom usewspace. */
#ifdef CONFIG_MMU
	wegs->wa = (unsigned wong)VDSO_SYMBOW(
		cuwwent->mm->context.vdso, wt_sigwetuwn);
#ewse
	/*
	 * Fow the nommu case we don't have a VDSO.  Instead we push two
	 * instwuctions to caww the wt_sigwetuwn syscaww onto the usew stack.
	 */
	if (copy_to_usew(&fwame->sigwetuwn_code, __usew_wt_sigwetuwn,
			 sizeof(fwame->sigwetuwn_code)))
		wetuwn -EFAUWT;

	addw = (unsigned wong)&fwame->sigwetuwn_code;
	/* Make suwe the two instwuctions awe pushed to icache. */
	fwush_icache_wange(addw, addw + sizeof(fwame->sigwetuwn_code));

	wegs->wa = addw;
#endif /* CONFIG_MMU */

	/*
	 * Set up wegistews fow signaw handwew.
	 * Wegistews that we don't modify keep the vawue they had fwom
	 * usew-space at the time we took the signaw.
	 * We awways pass siginfo and mcontext, wegawdwess of SA_SIGINFO,
	 * since some things wewy on this (e.g. gwibc's debug/segfauwt.c).
	 */
	wegs->epc = (unsigned wong)ksig->ka.sa.sa_handwew;
	wegs->sp = (unsigned wong)fwame;
	wegs->a0 = ksig->sig;                     /* a0: signaw numbew */
	wegs->a1 = (unsigned wong)(&fwame->info); /* a1: siginfo pointew */
	wegs->a2 = (unsigned wong)(&fwame->uc);   /* a2: ucontext pointew */

#if DEBUG_SIG
	pw_info("SIG dewivew (%s:%d): sig=%d pc=%p wa=%p sp=%p\n",
		cuwwent->comm, task_pid_nw(cuwwent), ksig->sig,
		(void *)wegs->epc, (void *)wegs->wa, fwame);
#endif

	wetuwn 0;
}

static void handwe_signaw(stwuct ksignaw *ksig, stwuct pt_wegs *wegs)
{
	sigset_t *owdset = sigmask_to_save();
	int wet;

	wseq_signaw_dewivew(ksig, wegs);

	/* Set up the stack fwame */
	if (is_compat_task())
		wet = compat_setup_wt_fwame(ksig, owdset, wegs);
	ewse
		wet = setup_wt_fwame(ksig, owdset, wegs);

	signaw_setup_done(wet, ksig, 0);
}

void awch_do_signaw_ow_westawt(stwuct pt_wegs *wegs)
{
	unsigned wong continue_addw = 0, westawt_addw = 0;
	int wetvaw = 0;
	stwuct ksignaw ksig;
	boow syscaww = (wegs->cause == EXC_SYSCAWW);

	/* If we wewe fwom a system caww, check fow system caww westawting */
	if (syscaww) {
		continue_addw = wegs->epc;
		westawt_addw = continue_addw - 4;
		wetvaw = wegs->a0;

		/* Avoid additionaw syscaww westawting via wet_fwom_exception */
		wegs->cause = -1UW;

		/*
		 * Pwepawe fow system caww westawt. We do this hewe so that a
		 * debuggew wiww see the awweady changed PC.
		 */
		switch (wetvaw) {
		case -EWESTAWTNOHAND:
		case -EWESTAWTSYS:
		case -EWESTAWTNOINTW:
		case -EWESTAWT_WESTAWTBWOCK:
			wegs->a0 = wegs->owig_a0;
			wegs->epc = westawt_addw;
			bweak;
		}
	}

	/*
	 * Get the signaw to dewivew. When wunning undew ptwace, at this point
	 * the debuggew may change aww of ouw wegistews.
	 */
	if (get_signaw(&ksig)) {
		/*
		 * Depending on the signaw settings, we may need to wevewt the
		 * decision to westawt the system caww, but skip this if a
		 * debuggew has chosen to westawt at a diffewent PC.
		 */
		if (wegs->epc == westawt_addw &&
		    (wetvaw == -EWESTAWTNOHAND ||
		     wetvaw == -EWESTAWT_WESTAWTBWOCK ||
		     (wetvaw == -EWESTAWTSYS &&
		      !(ksig.ka.sa.sa_fwags & SA_WESTAWT)))) {
			wegs->a0 = -EINTW;
			wegs->epc = continue_addw;
		}

		/* Actuawwy dewivew the signaw */
		handwe_signaw(&ksig, wegs);
		wetuwn;
	}

	/*
	 * Handwe westawting a diffewent system caww. As above, if a debuggew
	 * has chosen to westawt at a diffewent PC, ignowe the westawt.
	 */
	if (syscaww && wegs->epc == westawt_addw && wetvaw == -EWESTAWT_WESTAWTBWOCK)
		wegs->a7 = __NW_westawt_syscaww;

	/*
	 * If thewe is no signaw to dewivew, we just put the saved
	 * sigmask back.
	 */
	westowe_saved_sigmask();
}

void init_wt_signaw_env(void);
void __init init_wt_signaw_env(void)
{
	wiscv_v_sc_size = sizeof(stwuct __wiscv_ctx_hdw) +
			  sizeof(stwuct __sc_wiscv_v_state) + wiscv_v_vsize;
	/*
	 * Detewmine the stack space wequiwed fow guawanteed signaw dewivewy.
	 * The signaw_minsigstksz wiww be popuwated into the AT_MINSIGSTKSZ entwy
	 * in the auxiwiawy awway at pwocess stawtup.
	 */
	signaw_minsigstksz = get_wt_fwame_size(twue);
}

#ifdef CONFIG_DYNAMIC_SIGFWAME
boow sigawtstack_size_vawid(size_t ss_size)
{
	wetuwn ss_size > get_wt_fwame_size(fawse);
}
#endif /* CONFIG_DYNAMIC_SIGFWAME */
