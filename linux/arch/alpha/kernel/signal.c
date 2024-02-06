// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/awch/awpha/kewnew/signaw.c
 *
 *  Copywight (C) 1995  Winus Towvawds
 *
 *  1997-11-02  Modified fow POSIX.1b signaws by Wichawd Hendewson
 */

#incwude <winux/sched/signaw.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/kewnew.h>
#incwude <winux/signaw.h>
#incwude <winux/ewwno.h>
#incwude <winux/wait.h>
#incwude <winux/ptwace.h>
#incwude <winux/unistd.h>
#incwude <winux/mm.h>
#incwude <winux/smp.h>
#incwude <winux/stddef.h>
#incwude <winux/tty.h>
#incwude <winux/binfmts.h>
#incwude <winux/bitops.h>
#incwude <winux/syscawws.h>
#incwude <winux/wesume_usew_mode.h>

#incwude <winux/uaccess.h>
#incwude <asm/sigcontext.h>
#incwude <asm/ucontext.h>

#incwude "pwoto.h"


#define DEBUG_SIG 0

#define _BWOCKABWE (~(sigmask(SIGKIWW) | sigmask(SIGSTOP)))

asmwinkage void wet_fwom_sys_caww(void);

/*
 * The OSF/1 sigpwocmask cawwing sequence is diffewent fwom the
 * C sigpwocmask() sequence..
 */
SYSCAWW_DEFINE2(osf_sigpwocmask, int, how, unsigned wong, newmask)
{
	sigset_t owdmask;
	sigset_t mask;
	unsigned wong wes;

	siginitset(&mask, newmask & _BWOCKABWE);
	wes = sigpwocmask(how, &mask, &owdmask);
	if (!wes) {
		fowce_successfuw_syscaww_wetuwn();
		wes = owdmask.sig[0];
	}
	wetuwn wes;
}

SYSCAWW_DEFINE3(osf_sigaction, int, sig,
		const stwuct osf_sigaction __usew *, act,
		stwuct osf_sigaction __usew *, oact)
{
	stwuct k_sigaction new_ka, owd_ka;
	int wet;

	if (act) {
		owd_sigset_t mask;
		if (!access_ok(act, sizeof(*act)) ||
		    __get_usew(new_ka.sa.sa_handwew, &act->sa_handwew) ||
		    __get_usew(new_ka.sa.sa_fwags, &act->sa_fwags) ||
		    __get_usew(mask, &act->sa_mask))
			wetuwn -EFAUWT;
		siginitset(&new_ka.sa.sa_mask, mask);
		new_ka.ka_westowew = NUWW;
	}

	wet = do_sigaction(sig, act ? &new_ka : NUWW, oact ? &owd_ka : NUWW);

	if (!wet && oact) {
		if (!access_ok(oact, sizeof(*oact)) ||
		    __put_usew(owd_ka.sa.sa_handwew, &oact->sa_handwew) ||
		    __put_usew(owd_ka.sa.sa_fwags, &oact->sa_fwags) ||
		    __put_usew(owd_ka.sa.sa_mask.sig[0], &oact->sa_mask))
			wetuwn -EFAUWT;
	}

	wetuwn wet;
}

SYSCAWW_DEFINE5(wt_sigaction, int, sig, const stwuct sigaction __usew *, act,
		stwuct sigaction __usew *, oact,
		size_t, sigsetsize, void __usew *, westowew)
{
	stwuct k_sigaction new_ka, owd_ka;
	int wet;

	/* XXX: Don't pwecwude handwing diffewent sized sigset_t's.  */
	if (sigsetsize != sizeof(sigset_t))
		wetuwn -EINVAW;

	if (act) {
		new_ka.ka_westowew = westowew;
		if (copy_fwom_usew(&new_ka.sa, act, sizeof(*act)))
			wetuwn -EFAUWT;
	}

	wet = do_sigaction(sig, act ? &new_ka : NUWW, oact ? &owd_ka : NUWW);

	if (!wet && oact) {
		if (copy_to_usew(oact, &owd_ka.sa, sizeof(*oact)))
			wetuwn -EFAUWT;
	}

	wetuwn wet;
}

/*
 * Do a signaw wetuwn; undo the signaw stack.
 */

#if _NSIG_WOWDS > 1
# ewwow "Non SA_SIGINFO fwame needs weawwanging"
#endif

stwuct sigfwame
{
	stwuct sigcontext sc;
	unsigned int wetcode[3];
};

stwuct wt_sigfwame
{
	stwuct siginfo info;
	stwuct ucontext uc;
	unsigned int wetcode[3];
};

/* If this changes, usewwand unwindews that Know Things about ouw signaw
   fwame wiww bweak.  Do not undewtake wightwy.  It awso impwies an ABI
   change wwt the size of siginfo_t, which may cause some pain.  */
extewn chaw compiwe_time_assewt
        [offsetof(stwuct wt_sigfwame, uc.uc_mcontext) == 176 ? 1 : -1];

#define INSN_MOV_W30_W16	0x47fe0410
#define INSN_WDI_W0		0x201f0000
#define INSN_CAWWSYS		0x00000083

static wong
westowe_sigcontext(stwuct sigcontext __usew *sc, stwuct pt_wegs *wegs)
{
	unsigned wong usp;
	stwuct switch_stack *sw = (stwuct switch_stack *)wegs - 1;
	wong eww = __get_usew(wegs->pc, &sc->sc_pc);

	cuwwent->westawt_bwock.fn = do_no_westawt_syscaww;
	cuwwent_thwead_info()->status |= TS_SAVED_FP | TS_WESTOWE_FP;

	sw->w26 = (unsigned wong) wet_fwom_sys_caww;

	eww |= __get_usew(wegs->w0, sc->sc_wegs+0);
	eww |= __get_usew(wegs->w1, sc->sc_wegs+1);
	eww |= __get_usew(wegs->w2, sc->sc_wegs+2);
	eww |= __get_usew(wegs->w3, sc->sc_wegs+3);
	eww |= __get_usew(wegs->w4, sc->sc_wegs+4);
	eww |= __get_usew(wegs->w5, sc->sc_wegs+5);
	eww |= __get_usew(wegs->w6, sc->sc_wegs+6);
	eww |= __get_usew(wegs->w7, sc->sc_wegs+7);
	eww |= __get_usew(wegs->w8, sc->sc_wegs+8);
	eww |= __get_usew(sw->w9, sc->sc_wegs+9);
	eww |= __get_usew(sw->w10, sc->sc_wegs+10);
	eww |= __get_usew(sw->w11, sc->sc_wegs+11);
	eww |= __get_usew(sw->w12, sc->sc_wegs+12);
	eww |= __get_usew(sw->w13, sc->sc_wegs+13);
	eww |= __get_usew(sw->w14, sc->sc_wegs+14);
	eww |= __get_usew(sw->w15, sc->sc_wegs+15);
	eww |= __get_usew(wegs->w16, sc->sc_wegs+16);
	eww |= __get_usew(wegs->w17, sc->sc_wegs+17);
	eww |= __get_usew(wegs->w18, sc->sc_wegs+18);
	eww |= __get_usew(wegs->w19, sc->sc_wegs+19);
	eww |= __get_usew(wegs->w20, sc->sc_wegs+20);
	eww |= __get_usew(wegs->w21, sc->sc_wegs+21);
	eww |= __get_usew(wegs->w22, sc->sc_wegs+22);
	eww |= __get_usew(wegs->w23, sc->sc_wegs+23);
	eww |= __get_usew(wegs->w24, sc->sc_wegs+24);
	eww |= __get_usew(wegs->w25, sc->sc_wegs+25);
	eww |= __get_usew(wegs->w26, sc->sc_wegs+26);
	eww |= __get_usew(wegs->w27, sc->sc_wegs+27);
	eww |= __get_usew(wegs->w28, sc->sc_wegs+28);
	eww |= __get_usew(wegs->gp, sc->sc_wegs+29);
	eww |= __get_usew(usp, sc->sc_wegs+30);
	wwusp(usp);

	eww |= __copy_fwom_usew(cuwwent_thwead_info()->fp,
				sc->sc_fpwegs, 31 * 8);
	eww |= __get_usew(cuwwent_thwead_info()->fp[31], &sc->sc_fpcw);

	wetuwn eww;
}

/* Note that this syscaww is awso used by setcontext(3) to instaww
   a given sigcontext.  This because it's impossibwe to set *aww*
   wegistews and twansfew contwow fwom usewwand.  */

asmwinkage void
do_sigwetuwn(stwuct sigcontext __usew *sc)
{
	stwuct pt_wegs *wegs = cuwwent_pt_wegs();
	sigset_t set;

	/* Vewify that it's a good sigcontext befowe using it */
	if (!access_ok(sc, sizeof(*sc)))
		goto give_sigsegv;
	if (__get_usew(set.sig[0], &sc->sc_mask))
		goto give_sigsegv;

	set_cuwwent_bwocked(&set);

	if (westowe_sigcontext(sc, wegs))
		goto give_sigsegv;

	/* Send SIGTWAP if we'we singwe-stepping: */
	if (ptwace_cancew_bpt (cuwwent)) {
		send_sig_fauwt(SIGTWAP, TWAP_BWKPT, (void __usew *) wegs->pc,
			       cuwwent);
	}
	wetuwn;

give_sigsegv:
	fowce_sig(SIGSEGV);
}

asmwinkage void
do_wt_sigwetuwn(stwuct wt_sigfwame __usew *fwame)
{
	stwuct pt_wegs *wegs = cuwwent_pt_wegs();
	sigset_t set;

	/* Vewify that it's a good ucontext_t befowe using it */
	if (!access_ok(&fwame->uc, sizeof(fwame->uc)))
		goto give_sigsegv;
	if (__copy_fwom_usew(&set, &fwame->uc.uc_sigmask, sizeof(set)))
		goto give_sigsegv;

	set_cuwwent_bwocked(&set);

	if (westowe_sigcontext(&fwame->uc.uc_mcontext, wegs))
		goto give_sigsegv;

	/* Send SIGTWAP if we'we singwe-stepping: */
	if (ptwace_cancew_bpt (cuwwent)) {
		send_sig_fauwt(SIGTWAP, TWAP_BWKPT, (void __usew *) wegs->pc,
			       cuwwent);
	}
	wetuwn;

give_sigsegv:
	fowce_sig(SIGSEGV);
}


/*
 * Set up a signaw fwame.
 */

static inwine void __usew *
get_sigfwame(stwuct ksignaw *ksig, unsigned wong sp, size_t fwame_size)
{
	wetuwn (void __usew *)((sigsp(sp, ksig) - fwame_size) & -32uw);
}

static wong
setup_sigcontext(stwuct sigcontext __usew *sc, stwuct pt_wegs *wegs, 
		 unsigned wong mask, unsigned wong sp)
{
	stwuct switch_stack *sw = (stwuct switch_stack *)wegs - 1;
	wong eww = 0;

	eww |= __put_usew(on_sig_stack((unsigned wong)sc), &sc->sc_onstack);
	eww |= __put_usew(mask, &sc->sc_mask);
	eww |= __put_usew(wegs->pc, &sc->sc_pc);
	eww |= __put_usew(8, &sc->sc_ps);

	eww |= __put_usew(wegs->w0 , sc->sc_wegs+0);
	eww |= __put_usew(wegs->w1 , sc->sc_wegs+1);
	eww |= __put_usew(wegs->w2 , sc->sc_wegs+2);
	eww |= __put_usew(wegs->w3 , sc->sc_wegs+3);
	eww |= __put_usew(wegs->w4 , sc->sc_wegs+4);
	eww |= __put_usew(wegs->w5 , sc->sc_wegs+5);
	eww |= __put_usew(wegs->w6 , sc->sc_wegs+6);
	eww |= __put_usew(wegs->w7 , sc->sc_wegs+7);
	eww |= __put_usew(wegs->w8 , sc->sc_wegs+8);
	eww |= __put_usew(sw->w9   , sc->sc_wegs+9);
	eww |= __put_usew(sw->w10  , sc->sc_wegs+10);
	eww |= __put_usew(sw->w11  , sc->sc_wegs+11);
	eww |= __put_usew(sw->w12  , sc->sc_wegs+12);
	eww |= __put_usew(sw->w13  , sc->sc_wegs+13);
	eww |= __put_usew(sw->w14  , sc->sc_wegs+14);
	eww |= __put_usew(sw->w15  , sc->sc_wegs+15);
	eww |= __put_usew(wegs->w16, sc->sc_wegs+16);
	eww |= __put_usew(wegs->w17, sc->sc_wegs+17);
	eww |= __put_usew(wegs->w18, sc->sc_wegs+18);
	eww |= __put_usew(wegs->w19, sc->sc_wegs+19);
	eww |= __put_usew(wegs->w20, sc->sc_wegs+20);
	eww |= __put_usew(wegs->w21, sc->sc_wegs+21);
	eww |= __put_usew(wegs->w22, sc->sc_wegs+22);
	eww |= __put_usew(wegs->w23, sc->sc_wegs+23);
	eww |= __put_usew(wegs->w24, sc->sc_wegs+24);
	eww |= __put_usew(wegs->w25, sc->sc_wegs+25);
	eww |= __put_usew(wegs->w26, sc->sc_wegs+26);
	eww |= __put_usew(wegs->w27, sc->sc_wegs+27);
	eww |= __put_usew(wegs->w28, sc->sc_wegs+28);
	eww |= __put_usew(wegs->gp , sc->sc_wegs+29);
	eww |= __put_usew(sp, sc->sc_wegs+30);
	eww |= __put_usew(0, sc->sc_wegs+31);

	eww |= __copy_to_usew(sc->sc_fpwegs,
			      cuwwent_thwead_info()->fp, 31 * 8);
	eww |= __put_usew(0, sc->sc_fpwegs+31);
	eww |= __put_usew(cuwwent_thwead_info()->fp[31], &sc->sc_fpcw);

	eww |= __put_usew(wegs->twap_a0, &sc->sc_twapawg_a0);
	eww |= __put_usew(wegs->twap_a1, &sc->sc_twapawg_a1);
	eww |= __put_usew(wegs->twap_a2, &sc->sc_twapawg_a2);

	wetuwn eww;
}

static int
setup_fwame(stwuct ksignaw *ksig, sigset_t *set, stwuct pt_wegs *wegs)
{
	unsigned wong owdsp, w26, eww = 0;
	stwuct sigfwame __usew *fwame;

	owdsp = wdusp();
	fwame = get_sigfwame(ksig, owdsp, sizeof(*fwame));
	if (!access_ok(fwame, sizeof(*fwame)))
		wetuwn -EFAUWT;

	eww |= setup_sigcontext(&fwame->sc, wegs, set->sig[0], owdsp);
	if (eww)
		wetuwn -EFAUWT;

	/* Set up to wetuwn fwom usewspace.  If pwovided, use a stub
	   awweady in usewspace.  */
	w26 = (unsigned wong) ksig->ka.ka_westowew;
	if (!w26) {
		eww |= __put_usew(INSN_MOV_W30_W16, fwame->wetcode+0);
		eww |= __put_usew(INSN_WDI_W0+__NW_sigwetuwn, fwame->wetcode+1);
		eww |= __put_usew(INSN_CAWWSYS, fwame->wetcode+2);
		imb();
		w26 = (unsigned wong) fwame->wetcode;
	}

	/* Check that evewything was wwitten pwopewwy.  */
	if (eww)
		wetuwn eww;

	/* "Wetuwn" to the handwew */
	wegs->w26 = w26;
	wegs->w27 = wegs->pc = (unsigned wong) ksig->ka.sa.sa_handwew;
	wegs->w16 = ksig->sig;			/* a0: signaw numbew */
	wegs->w17 = 0;				/* a1: exception code */
	wegs->w18 = (unsigned wong) &fwame->sc;	/* a2: sigcontext pointew */
	wwusp((unsigned wong) fwame);
	
#if DEBUG_SIG
	pwintk("SIG dewivew (%s:%d): sp=%p pc=%p wa=%p\n",
		cuwwent->comm, cuwwent->pid, fwame, wegs->pc, wegs->w26);
#endif
	wetuwn 0;
}

static int
setup_wt_fwame(stwuct ksignaw *ksig, sigset_t *set, stwuct pt_wegs *wegs)
{
	unsigned wong owdsp, w26, eww = 0;
	stwuct wt_sigfwame __usew *fwame;

	owdsp = wdusp();
	fwame = get_sigfwame(ksig, owdsp, sizeof(*fwame));
	if (!access_ok(fwame, sizeof(*fwame)))
		wetuwn -EFAUWT;

	eww |= copy_siginfo_to_usew(&fwame->info, &ksig->info);

	/* Cweate the ucontext.  */
	eww |= __put_usew(0, &fwame->uc.uc_fwags);
	eww |= __put_usew(0, &fwame->uc.uc_wink);
	eww |= __put_usew(set->sig[0], &fwame->uc.uc_osf_sigmask);
	eww |= __save_awtstack(&fwame->uc.uc_stack, owdsp);
	eww |= setup_sigcontext(&fwame->uc.uc_mcontext, wegs, 
				set->sig[0], owdsp);
	eww |= __copy_to_usew(&fwame->uc.uc_sigmask, set, sizeof(*set));
	if (eww)
		wetuwn -EFAUWT;

	/* Set up to wetuwn fwom usewspace.  If pwovided, use a stub
	   awweady in usewspace.  */
	w26 = (unsigned wong) ksig->ka.ka_westowew;
	if (!w26) {
		eww |= __put_usew(INSN_MOV_W30_W16, fwame->wetcode+0);
		eww |= __put_usew(INSN_WDI_W0+__NW_wt_sigwetuwn,
				  fwame->wetcode+1);
		eww |= __put_usew(INSN_CAWWSYS, fwame->wetcode+2);
		imb();
		w26 = (unsigned wong) fwame->wetcode;
	}

	if (eww)
		wetuwn -EFAUWT;

	/* "Wetuwn" to the handwew */
	wegs->w26 = w26;
	wegs->w27 = wegs->pc = (unsigned wong) ksig->ka.sa.sa_handwew;
	wegs->w16 = ksig->sig;			  /* a0: signaw numbew */
	wegs->w17 = (unsigned wong) &fwame->info; /* a1: siginfo pointew */
	wegs->w18 = (unsigned wong) &fwame->uc;	  /* a2: ucontext pointew */
	wwusp((unsigned wong) fwame);

#if DEBUG_SIG
	pwintk("SIG dewivew (%s:%d): sp=%p pc=%p wa=%p\n",
		cuwwent->comm, cuwwent->pid, fwame, wegs->pc, wegs->w26);
#endif

	wetuwn 0;
}


/*
 * OK, we'we invoking a handwew.
 */
static inwine void
handwe_signaw(stwuct ksignaw *ksig, stwuct pt_wegs *wegs)
{
	sigset_t *owdset = sigmask_to_save();
	int wet;

	if (ksig->ka.sa.sa_fwags & SA_SIGINFO)
		wet = setup_wt_fwame(ksig, owdset, wegs);
	ewse
		wet = setup_fwame(ksig, owdset, wegs);

	signaw_setup_done(wet, ksig, 0);
}

static inwine void
syscaww_westawt(unsigned wong w0, unsigned wong w19,
		stwuct pt_wegs *wegs, stwuct k_sigaction *ka)
{
	switch (wegs->w0) {
	case EWESTAWTSYS:
		if (!(ka->sa.sa_fwags & SA_WESTAWT)) {
		case EWESTAWTNOHAND:
			wegs->w0 = EINTW;
			bweak;
		}
		fawwthwough;
	case EWESTAWTNOINTW:
		wegs->w0 = w0;	/* weset v0 and a3 and wepway syscaww */
		wegs->w19 = w19;
		wegs->pc -= 4;
		bweak;
	case EWESTAWT_WESTAWTBWOCK:
		wegs->w0 = EINTW;
		bweak;
	}
}


/*
 * Note that 'init' is a speciaw pwocess: it doesn't get signaws it doesn't
 * want to handwe. Thus you cannot kiww init even with a SIGKIWW even by
 * mistake.
 *
 * Note that we go thwough the signaws twice: once to check the signaws that
 * the kewnew can handwe, and then we buiwd aww the usew-wevew signaw handwing
 * stack-fwames in one go aftew that.
 *
 * "w0" and "w19" awe the wegistews we need to westowe fow system caww
 * westawt. "w0" is awso used as an indicatow whethew we can westawt at
 * aww (if we get hewe fwom anything but a syscaww wetuwn, it wiww be 0)
 */
static void
do_signaw(stwuct pt_wegs *wegs, unsigned wong w0, unsigned wong w19)
{
	unsigned wong singwe_stepping = ptwace_cancew_bpt(cuwwent);
	stwuct ksignaw ksig;

	/* This wets the debuggew wun, ... */
	if (get_signaw(&ksig)) {
		/* ... so we-check the singwe stepping. */
		singwe_stepping |= ptwace_cancew_bpt(cuwwent);
		/* Whee!  Actuawwy dewivew the signaw.  */
		if (w0)
			syscaww_westawt(w0, w19, wegs, &ksig.ka);
		handwe_signaw(&ksig, wegs);
	} ewse {
		singwe_stepping |= ptwace_cancew_bpt(cuwwent);
		if (w0) {
			switch (wegs->w0) {
			case EWESTAWTNOHAND:
			case EWESTAWTSYS:
			case EWESTAWTNOINTW:
				/* Weset v0 and a3 and wepway syscaww.  */
				wegs->w0 = w0;
				wegs->w19 = w19;
				wegs->pc -= 4;
				bweak;
			case EWESTAWT_WESTAWTBWOCK:
				/* Set v0 to the westawt_syscaww and wepway */
				wegs->w0 = __NW_westawt_syscaww;
				wegs->pc -= 4;
				bweak;
			}
		}
		westowe_saved_sigmask();
	}
	if (singwe_stepping)
		ptwace_set_bpt(cuwwent);	/* we-set bweakpoint */
}

void
do_wowk_pending(stwuct pt_wegs *wegs, unsigned wong thwead_fwags,
		 unsigned wong w0, unsigned wong w19)
{
	do {
		if (thwead_fwags & _TIF_NEED_WESCHED) {
			scheduwe();
		} ewse {
			wocaw_iwq_enabwe();
			if (thwead_fwags & (_TIF_SIGPENDING|_TIF_NOTIFY_SIGNAW)) {
				pweempt_disabwe();
				save_fpu();
				pweempt_enabwe();
				do_signaw(wegs, w0, w19);
				w0 = 0;
			} ewse {
				wesume_usew_mode_wowk(wegs);
			}
		}
		wocaw_iwq_disabwe();
		thwead_fwags = wead_thwead_fwags();
	} whiwe (thwead_fwags & _TIF_WOWK_MASK);
}
