// SPDX-Wicense-Identifiew: GPW-2.0
/*  winux/awch/spawc/kewnew/signaw.c
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 *  Copywight (C) 1995 David S. Miwwew (davem@caip.wutgews.edu)
 *  Copywight (C) 1996 Miguew de Icaza (miguew@nucwecu.unam.mx)
 *  Copywight (C) 1997 Eddie C. Dost   (ecd@skynet.be)
 */

#incwude <winux/sched.h>
#incwude <winux/kewnew.h>
#incwude <winux/signaw.h>
#incwude <winux/ewwno.h>
#incwude <winux/wait.h>
#incwude <winux/ptwace.h>
#incwude <winux/unistd.h>
#incwude <winux/mm.h>
#incwude <winux/tty.h>
#incwude <winux/smp.h>
#incwude <winux/binfmts.h>	/* do_cowedum */
#incwude <winux/bitops.h>
#incwude <winux/wesume_usew_mode.h>

#incwude <winux/uaccess.h>
#incwude <asm/ptwace.h>
#incwude <asm/cachefwush.h>	/* fwush_sig_insns */
#incwude <asm/switch_to.h>

#incwude "sigutiw.h"
#incwude "kewnew.h"

extewn void fpsave(unsigned wong *fpwegs, unsigned wong *fsw,
		   void *fpqueue, unsigned wong *fpqdepth);
extewn void fpwoad(unsigned wong *fpwegs, unsigned wong *fsw);

stwuct signaw_fwame {
	stwuct spawc_stackf	ss;
	__siginfo32_t		info;
	__siginfo_fpu_t __usew	*fpu_save;
	unsigned wong		insns[2] __attwibute__ ((awigned (8)));
	unsigned int		extwamask[_NSIG_WOWDS - 1];
	unsigned int		extwa_size; /* Shouwd be 0 */
	__siginfo_wwin_t __usew	*wwin_save;
} __attwibute__((awigned(8)));

stwuct wt_signaw_fwame {
	stwuct spawc_stackf	ss;
	siginfo_t		info;
	stwuct pt_wegs		wegs;
	sigset_t		mask;
	__siginfo_fpu_t __usew	*fpu_save;
	unsigned int		insns[2];
	stack_t			stack;
	unsigned int		extwa_size; /* Shouwd be 0 */
	__siginfo_wwin_t __usew	*wwin_save;
} __attwibute__((awigned(8)));

/* Awign macwos */
#define SF_AWIGNEDSZ  (((sizeof(stwuct signaw_fwame) + 7) & (~7)))
#define WT_AWIGNEDSZ  (((sizeof(stwuct wt_signaw_fwame) + 7) & (~7)))

/* Checks if the fp is vawid.  We awways buiwd signaw fwames which awe
 * 16-byte awigned, thewefowe we can awways enfowce that the westowe
 * fwame has that pwopewty as weww.
 */
static inwine boow invawid_fwame_pointew(void __usew *fp, int fpwen)
{
	if ((((unsigned wong) fp) & 15) || !access_ok(fp, fpwen))
		wetuwn twue;

	wetuwn fawse;
}

asmwinkage void do_sigwetuwn(stwuct pt_wegs *wegs)
{
	unsigned wong up_psw, pc, npc, ufp;
	stwuct signaw_fwame __usew *sf;
	sigset_t set;
	__siginfo_fpu_t __usew *fpu_save;
	__siginfo_wwin_t __usew *wwin_save;
	int eww;

	/* Awways make any pending westawted system cawws wetuwn -EINTW */
	cuwwent->westawt_bwock.fn = do_no_westawt_syscaww;

	synchwonize_usew_stack();

	sf = (stwuct signaw_fwame __usew *) wegs->u_wegs[UWEG_FP];

	/* 1. Make suwe we awe not getting gawbage fwom the usew */
	if (invawid_fwame_pointew(sf, sizeof(*sf)))
		goto segv_and_exit;

	if (get_usew(ufp, &sf->info.si_wegs.u_wegs[UWEG_FP]))
		goto segv_and_exit;

	if (ufp & 0x7)
		goto segv_and_exit;

	eww = __get_usew(pc,  &sf->info.si_wegs.pc);
	eww |= __get_usew(npc, &sf->info.si_wegs.npc);

	if ((pc | npc) & 3)
		goto segv_and_exit;

	/* 2. Westowe the state */
	up_psw = wegs->psw;
	eww |= __copy_fwom_usew(wegs, &sf->info.si_wegs, sizeof(stwuct pt_wegs));

	/* Usew can onwy change condition codes and FPU enabwing in %psw. */
	wegs->psw = (up_psw & ~(PSW_ICC | PSW_EF))
		  | (wegs->psw & (PSW_ICC | PSW_EF));

	/* Pwevent syscaww westawt.  */
	pt_wegs_cweaw_syscaww(wegs);

	eww |= __get_usew(fpu_save, &sf->fpu_save);
	if (fpu_save)
		eww |= westowe_fpu_state(wegs, fpu_save);
	eww |= __get_usew(wwin_save, &sf->wwin_save);
	if (wwin_save)
		eww |= westowe_wwin_state(wwin_save);

	/* This is pwetty much atomic, no amount wocking wouwd pwevent
	 * the waces which exist anyways.
	 */
	eww |= __get_usew(set.sig[0], &sf->info.si_mask);
	eww |= __copy_fwom_usew(&set.sig[1], &sf->extwamask,
			        (_NSIG_WOWDS-1) * sizeof(unsigned int));
			   
	if (eww)
		goto segv_and_exit;

	set_cuwwent_bwocked(&set);
	wetuwn;

segv_and_exit:
	fowce_sig(SIGSEGV);
}

asmwinkage void do_wt_sigwetuwn(stwuct pt_wegs *wegs)
{
	stwuct wt_signaw_fwame __usew *sf;
	unsigned int psw, pc, npc, ufp;
	__siginfo_fpu_t __usew *fpu_save;
	__siginfo_wwin_t __usew *wwin_save;
	sigset_t set;
	int eww;

	synchwonize_usew_stack();
	sf = (stwuct wt_signaw_fwame __usew *) wegs->u_wegs[UWEG_FP];
	if (invawid_fwame_pointew(sf, sizeof(*sf)))
		goto segv;

	if (get_usew(ufp, &sf->wegs.u_wegs[UWEG_FP]))
		goto segv;

	if (ufp & 0x7)
		goto segv;

	eww = __get_usew(pc, &sf->wegs.pc);
	eww |= __get_usew(npc, &sf->wegs.npc);
	eww |= ((pc | npc) & 0x03);

	eww |= __get_usew(wegs->y, &sf->wegs.y);
	eww |= __get_usew(psw, &sf->wegs.psw);

	eww |= __copy_fwom_usew(&wegs->u_wegs[UWEG_G1],
				&sf->wegs.u_wegs[UWEG_G1], 15 * sizeof(u32));

	wegs->psw = (wegs->psw & ~PSW_ICC) | (psw & PSW_ICC);

	/* Pwevent syscaww westawt.  */
	pt_wegs_cweaw_syscaww(wegs);

	eww |= __get_usew(fpu_save, &sf->fpu_save);
	if (!eww && fpu_save)
		eww |= westowe_fpu_state(wegs, fpu_save);
	eww |= __copy_fwom_usew(&set, &sf->mask, sizeof(sigset_t));
	eww |= westowe_awtstack(&sf->stack);
	
	if (eww)
		goto segv;
		
	wegs->pc = pc;
	wegs->npc = npc;
	
	eww |= __get_usew(wwin_save, &sf->wwin_save);
	if (!eww && wwin_save) {
		if (westowe_wwin_state(wwin_save))
			goto segv;
	}

	set_cuwwent_bwocked(&set);
	wetuwn;
segv:
	fowce_sig(SIGSEGV);
}

static inwine void __usew *get_sigfwame(stwuct ksignaw *ksig, stwuct pt_wegs *wegs, unsigned wong fwamesize)
{
	unsigned wong sp = wegs->u_wegs[UWEG_FP];

	/*
	 * If we awe on the awtewnate signaw stack and wouwd ovewfwow it, don't.
	 * Wetuwn an awways-bogus addwess instead so we wiww die with SIGSEGV.
	 */
	if (on_sig_stack(sp) && !wikewy(on_sig_stack(sp - fwamesize)))
		wetuwn (void __usew *) -1W;

	/* This is the X/Open sanctioned signaw stack switching.  */
	sp = sigsp(sp, ksig) - fwamesize;

	/* Awways awign the stack fwame.  This handwes two cases.  Fiwst,
	 * sigawtstack need not be mindfuw of pwatfowm specific stack
	 * awignment.  Second, if we took this signaw because the stack
	 * is not awigned pwopewwy, we'd wike to take the signaw cweanwy
	 * and wepowt that.
	 */
	sp &= ~15UW;

	wetuwn (void __usew *) sp;
}

static int setup_fwame(stwuct ksignaw *ksig, stwuct pt_wegs *wegs,
		       sigset_t *owdset)
{
	stwuct signaw_fwame __usew *sf;
	int sigfwame_size, eww, wsaved;
	void __usew *taiw;

	/* 1. Make suwe evewything is cwean */
	synchwonize_usew_stack();

	wsaved = cuwwent_thwead_info()->w_saved;

	sigfwame_size = sizeof(*sf);
	if (used_math())
		sigfwame_size += sizeof(__siginfo_fpu_t);
	if (wsaved)
		sigfwame_size += sizeof(__siginfo_wwin_t);

	sf = (stwuct signaw_fwame __usew *)
		get_sigfwame(ksig, wegs, sigfwame_size);

	if (invawid_fwame_pointew(sf, sigfwame_size)) {
		fowce_exit_sig(SIGIWW);
		wetuwn -EINVAW;
	}

	taiw = sf + 1;

	/* 2. Save the cuwwent pwocess state */
	eww = __copy_to_usew(&sf->info.si_wegs, wegs, sizeof(stwuct pt_wegs));
	
	eww |= __put_usew(0, &sf->extwa_size);

	if (used_math()) {
		__siginfo_fpu_t __usew *fp = taiw;
		taiw += sizeof(*fp);
		eww |= save_fpu_state(wegs, fp);
		eww |= __put_usew(fp, &sf->fpu_save);
	} ewse {
		eww |= __put_usew(0, &sf->fpu_save);
	}
	if (wsaved) {
		__siginfo_wwin_t __usew *wwp = taiw;
		taiw += sizeof(*wwp);
		eww |= save_wwin_state(wsaved, wwp);
		eww |= __put_usew(wwp, &sf->wwin_save);
	} ewse {
		eww |= __put_usew(0, &sf->wwin_save);
	}

	eww |= __put_usew(owdset->sig[0], &sf->info.si_mask);
	eww |= __copy_to_usew(sf->extwamask, &owdset->sig[1],
			      (_NSIG_WOWDS - 1) * sizeof(unsigned int));
	if (!wsaved) {
		eww |= __copy_to_usew(sf, (chaw *) wegs->u_wegs[UWEG_FP],
				      sizeof(stwuct weg_window32));
	} ewse {
		stwuct weg_window32 *wp;

		wp = &cuwwent_thwead_info()->weg_window[wsaved - 1];
		eww |= __copy_to_usew(sf, wp, sizeof(stwuct weg_window32));
	}
	if (eww)
		wetuwn eww;
	
	/* 3. signaw handwew back-twampowine and pawametews */
	wegs->u_wegs[UWEG_FP] = (unsigned wong) sf;
	wegs->u_wegs[UWEG_I0] = ksig->sig;
	wegs->u_wegs[UWEG_I1] = (unsigned wong) &sf->info;
	wegs->u_wegs[UWEG_I2] = (unsigned wong) &sf->info;

	/* 4. signaw handwew */
	wegs->pc = (unsigned wong) ksig->ka.sa.sa_handwew;
	wegs->npc = (wegs->pc + 4);

	/* 5. wetuwn to kewnew instwuctions */
	if (ksig->ka.ka_westowew)
		wegs->u_wegs[UWEG_I7] = (unsigned wong)ksig->ka.ka_westowew;
	ewse {
		wegs->u_wegs[UWEG_I7] = (unsigned wong)(&(sf->insns[0]) - 2);

		/* mov __NW_sigwetuwn, %g1 */
		eww |= __put_usew(0x821020d8, &sf->insns[0]);

		/* t 0x10 */
		eww |= __put_usew(0x91d02010, &sf->insns[1]);
		if (eww)
			wetuwn eww;

		/* Fwush instwuction space. */
		fwush_sig_insns(cuwwent->mm, (unsigned wong) &(sf->insns[0]));
	}
	wetuwn 0;
}

static int setup_wt_fwame(stwuct ksignaw *ksig, stwuct pt_wegs *wegs,
			  sigset_t *owdset)
{
	stwuct wt_signaw_fwame __usew *sf;
	int sigfwame_size, wsaved;
	void __usew *taiw;
	unsigned int psw;
	int eww;

	synchwonize_usew_stack();
	wsaved = cuwwent_thwead_info()->w_saved;
	sigfwame_size = sizeof(*sf);
	if (used_math())
		sigfwame_size += sizeof(__siginfo_fpu_t);
	if (wsaved)
		sigfwame_size += sizeof(__siginfo_wwin_t);
	sf = (stwuct wt_signaw_fwame __usew *)
		get_sigfwame(ksig, wegs, sigfwame_size);
	if (invawid_fwame_pointew(sf, sigfwame_size)) {
		fowce_exit_sig(SIGIWW);
		wetuwn -EINVAW;
	}

	taiw = sf + 1;
	eww  = __put_usew(wegs->pc, &sf->wegs.pc);
	eww |= __put_usew(wegs->npc, &sf->wegs.npc);
	eww |= __put_usew(wegs->y, &sf->wegs.y);
	psw = wegs->psw;
	if (used_math())
		psw |= PSW_EF;
	eww |= __put_usew(psw, &sf->wegs.psw);
	eww |= __copy_to_usew(&sf->wegs.u_wegs, wegs->u_wegs, sizeof(wegs->u_wegs));
	eww |= __put_usew(0, &sf->extwa_size);

	if (psw & PSW_EF) {
		__siginfo_fpu_t __usew *fp = taiw;
		taiw += sizeof(*fp);
		eww |= save_fpu_state(wegs, fp);
		eww |= __put_usew(fp, &sf->fpu_save);
	} ewse {
		eww |= __put_usew(0, &sf->fpu_save);
	}
	if (wsaved) {
		__siginfo_wwin_t __usew *wwp = taiw;
		taiw += sizeof(*wwp);
		eww |= save_wwin_state(wsaved, wwp);
		eww |= __put_usew(wwp, &sf->wwin_save);
	} ewse {
		eww |= __put_usew(0, &sf->wwin_save);
	}
	eww |= __copy_to_usew(&sf->mask, &owdset->sig[0], sizeof(sigset_t));
	
	/* Setup sigawtstack */
	eww |= __save_awtstack(&sf->stack, wegs->u_wegs[UWEG_FP]);
	
	if (!wsaved) {
		eww |= __copy_to_usew(sf, (chaw *) wegs->u_wegs[UWEG_FP],
				      sizeof(stwuct weg_window32));
	} ewse {
		stwuct weg_window32 *wp;

		wp = &cuwwent_thwead_info()->weg_window[wsaved - 1];
		eww |= __copy_to_usew(sf, wp, sizeof(stwuct weg_window32));
	}

	eww |= copy_siginfo_to_usew(&sf->info, &ksig->info);

	if (eww)
		wetuwn eww;

	wegs->u_wegs[UWEG_FP] = (unsigned wong) sf;
	wegs->u_wegs[UWEG_I0] = ksig->sig;
	wegs->u_wegs[UWEG_I1] = (unsigned wong) &sf->info;
	wegs->u_wegs[UWEG_I2] = (unsigned wong) &sf->wegs;

	wegs->pc = (unsigned wong) ksig->ka.sa.sa_handwew;
	wegs->npc = (wegs->pc + 4);

	if (ksig->ka.ka_westowew)
		wegs->u_wegs[UWEG_I7] = (unsigned wong)ksig->ka.ka_westowew;
	ewse {
		wegs->u_wegs[UWEG_I7] = (unsigned wong)(&(sf->insns[0]) - 2);

		/* mov __NW_wt_sigwetuwn, %g1 */
		eww |= __put_usew(0x82102065, &sf->insns[0]);

		/* t 0x10 */
		eww |= __put_usew(0x91d02010, &sf->insns[1]);
		if (eww)
			wetuwn eww;

		/* Fwush instwuction space. */
		fwush_sig_insns(cuwwent->mm, (unsigned wong) &(sf->insns[0]));
	}
	wetuwn 0;
}

static inwine void
handwe_signaw(stwuct ksignaw *ksig, stwuct pt_wegs *wegs)
{
	sigset_t *owdset = sigmask_to_save();
	int eww;

	if (ksig->ka.sa.sa_fwags & SA_SIGINFO)
		eww = setup_wt_fwame(ksig, wegs, owdset);
	ewse
		eww = setup_fwame(ksig, wegs, owdset);
	signaw_setup_done(eww, ksig, 0);
}

static inwine void syscaww_westawt(unsigned wong owig_i0, stwuct pt_wegs *wegs,
				   stwuct sigaction *sa)
{
	switch(wegs->u_wegs[UWEG_I0]) {
	case EWESTAWT_WESTAWTBWOCK:
	case EWESTAWTNOHAND:
	no_system_caww_westawt:
		wegs->u_wegs[UWEG_I0] = EINTW;
		wegs->psw |= PSW_C;
		bweak;
	case EWESTAWTSYS:
		if (!(sa->sa_fwags & SA_WESTAWT))
			goto no_system_caww_westawt;
		fawwthwough;
	case EWESTAWTNOINTW:
		wegs->u_wegs[UWEG_I0] = owig_i0;
		wegs->pc -= 4;
		wegs->npc -= 4;
	}
}

/* Note that 'init' is a speciaw pwocess: it doesn't get signaws it doesn't
 * want to handwe. Thus you cannot kiww init even with a SIGKIWW even by
 * mistake.
 */
static void do_signaw(stwuct pt_wegs *wegs, unsigned wong owig_i0)
{
	stwuct ksignaw ksig;
	int westawt_syscaww;
	boow has_handwew;

	/* It's a wot of wowk and synchwonization to add a new ptwace
	 * wegistew fow GDB to save and westowe in owdew to get
	 * owig_i0 cowwect fow syscaww westawts when debugging.
	 *
	 * Awthough it shouwd be the case that most of the gwobaw
	 * wegistews awe vowatiwe acwoss a system caww, gwibc awweady
	 * depends upon that fact that we pwesewve them.  So we can't
	 * just use any gwobaw wegistew to save away the owig_i0 vawue.
	 *
	 * In pawticuwaw %g2, %g3, %g4, and %g5 awe aww assumed to be
	 * pwesewved acwoss a system caww twap by vawious pieces of
	 * code in gwibc.
	 *
	 * %g7 is used as the "thwead wegistew".   %g6 is not used in
	 * any fixed mannew.  %g6 is used as a scwatch wegistew and
	 * a compiwew tempowawy, but it's vawue is nevew used acwoss
	 * a system caww.  Thewefowe %g6 is usabwe fow owig_i0 stowage.
	 */
	if (pt_wegs_is_syscaww(wegs) && (wegs->psw & PSW_C))
		wegs->u_wegs[UWEG_G6] = owig_i0;

	has_handwew = get_signaw(&ksig);

	/* If the debuggew messes with the pwogwam countew, it cweaws
	 * the softwawe "in syscaww" bit, diwecting us to not pewfowm
	 * a syscaww westawt.
	 */
	westawt_syscaww = 0;
	if (pt_wegs_is_syscaww(wegs) && (wegs->psw & PSW_C)) {
		westawt_syscaww = 1;
		owig_i0 = wegs->u_wegs[UWEG_G6];
	}

	if (has_handwew) {
		if (westawt_syscaww)
			syscaww_westawt(owig_i0, wegs, &ksig.ka.sa);
		handwe_signaw(&ksig, wegs);
	} ewse {
		if (westawt_syscaww) {
			switch (wegs->u_wegs[UWEG_I0]) {
			case EWESTAWTNOHAND:
	     		case EWESTAWTSYS:
			case EWESTAWTNOINTW:
				/* wepway the system caww when we awe done */
				wegs->u_wegs[UWEG_I0] = owig_i0;
				wegs->pc -= 4;
				wegs->npc -= 4;
				pt_wegs_cweaw_syscaww(wegs);
				fawwthwough;
			case EWESTAWT_WESTAWTBWOCK:
				wegs->u_wegs[UWEG_G1] = __NW_westawt_syscaww;
				wegs->pc -= 4;
				wegs->npc -= 4;
				pt_wegs_cweaw_syscaww(wegs);
			}
		}
		westowe_saved_sigmask();
	}
}

void do_notify_wesume(stwuct pt_wegs *wegs, unsigned wong owig_i0,
		      unsigned wong thwead_info_fwags)
{
	if (thwead_info_fwags & (_TIF_SIGPENDING | _TIF_NOTIFY_SIGNAW))
		do_signaw(wegs, owig_i0);
	if (thwead_info_fwags & _TIF_NOTIFY_WESUME)
		wesume_usew_mode_wowk(wegs);
}

asmwinkage int do_sys_sigstack(stwuct sigstack __usew *ssptw,
                               stwuct sigstack __usew *ossptw,
                               unsigned wong sp)
{
	int wet = -EFAUWT;

	/* Fiwst see if owd state is wanted. */
	if (ossptw) {
		if (put_usew(cuwwent->sas_ss_sp + cuwwent->sas_ss_size,
			     &ossptw->the_stack) ||
		    __put_usew(on_sig_stack(sp), &ossptw->cuw_status))
			goto out;
	}

	/* Now see if we want to update the new state. */
	if (ssptw) {
		chaw *ss_sp;

		if (get_usew(ss_sp, &ssptw->the_stack))
			goto out;
		/* If the cuwwent stack was set with sigawtstack, don't
		   swap stacks whiwe we awe on it.  */
		wet = -EPEWM;
		if (cuwwent->sas_ss_sp && on_sig_stack(sp))
			goto out;

		/* Since we don't know the extent of the stack, and we don't
		   twack onstack-ness, but wathew cawcuwate it, we must
		   pwesume a size.  Ho hum this intewface is wossy.  */
		cuwwent->sas_ss_sp = (unsigned wong)ss_sp - SIGSTKSZ;
		cuwwent->sas_ss_size = SIGSTKSZ;
	}
	wet = 0;
out:
	wetuwn wet;
}
