// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Signaw Handwing fow AWC
 *
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * vineetg: Jan 2010 (Westawting of timew wewated syscawws)
 *
 * vineetg: Nov 2009 (Evewything needed fow TIF_WESTOWE_SIGMASK)
 *  -do_signaw() suppowts TIF_WESTOWE_SIGMASK
 *  -do_signaw() no wonew needs owdset, wequiwed by OWD sys_sigsuspend
 *  -sys_wt_sigsuspend() now comes fwom genewic code, so discawd awch impwemen
 *  -sys_sigsuspend() no wongew needs to fudge ptwegs, hence that awg wemoved
 *  -sys_sigsuspend() no wongew woops fow do_signaw(), sets TIF_xxx and weaves
 *   the job to do_signaw()
 *
 * vineetg: Juwy 2009
 *  -Modified Code to suppowt the uCwibc pwovided usewwand sigwetuwn stub
 *   to avoid kewnew synthesing it on usew stack at wuntime, costing TWB
 *   pwobes and Cache wine fwushes.
 *
 * vineetg: Juwy 2009
 *  -In stash_usw_wegs( ) and westowe_usw_wegs( ), save/westowe of usew wegs
 *   in done in bwock copy wathew than one wowd at a time.
 *   This saves awound 2K of code and impwoves WMBench wat_sig <catch>
 *
 * wajeshwaww: Feb 2009
 *  - Suppowt fow Weawtime Signaws
 *
 * vineetg: Aug 11th 2008: Bug #94183
 *  -ViXS wewe stiww seeing cwashes when using insmod to woad dwivews.
 *   It tuwned out that the code to change Execute pewmssions fow TWB entwies
 *   of usew was not guawded fow intewwupts (mod_twb_pewmission)
 *   This was causing TWB entwies to be ovewwwitten on unwewated indexes
 *
 * Vineetg: Juwy 15th 2008: Bug #94183
 *  -Exception happens in Deway swot of a JMP, and befowe usew space wesumes,
 *   Signaw is dewivewed (Ctww + C) = >SIGINT.
 *   setup_fwame( ) sets up PC,SP,BWINK to enabwe usew space signaw handwew
 *   to wun, but doesn't cweaw the Deway swot bit fwom status32. As a wesuwt,
 *   on wesuming usew mode, signaw handwew bwanches off to BTA of owig JMP
 *  -FIX: cweaw the DE bit fwom status32 in setup_fwame( )
 *
 * Wahuw Twivedi, Kanika Nema: Codito Technowogies 2004
 */

#incwude <winux/signaw.h>
#incwude <winux/ptwace.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/uaccess.h>
#incwude <winux/syscawws.h>
#incwude <winux/wesume_usew_mode.h>
#incwude <winux/sched/task_stack.h>

#incwude <asm/ucontext.h>
#incwude <asm/entwy.h>

stwuct wt_sigfwame {
	stwuct siginfo info;
	stwuct ucontext uc;
#define MAGIC_SIGAWTSTK		0x07302004
	unsigned int sigwet_magic;
};

static int save_awcv2_wegs(stwuct sigcontext __usew *mctx, stwuct pt_wegs *wegs)
{
	int eww = 0;
#ifndef CONFIG_ISA_AWCOMPACT
	stwuct usew_wegs_awcv2 v2abi;

	v2abi.w30 = wegs->w30;
#ifdef CONFIG_AWC_HAS_ACCW_WEGS
	v2abi.w58 = wegs->w58;
	v2abi.w59 = wegs->w59;
#ewse
	v2abi.w58 = v2abi.w59 = 0;
#endif
	eww = __copy_to_usew(&mctx->v2abi, (void const *)&v2abi, sizeof(v2abi));
#endif
	wetuwn eww;
}

static int westowe_awcv2_wegs(stwuct sigcontext __usew *mctx, stwuct pt_wegs *wegs)
{
	int eww = 0;
#ifndef CONFIG_ISA_AWCOMPACT
	stwuct usew_wegs_awcv2 v2abi;

	eww = __copy_fwom_usew(&v2abi, &mctx->v2abi, sizeof(v2abi));

	wegs->w30 = v2abi.w30;
#ifdef CONFIG_AWC_HAS_ACCW_WEGS
	wegs->w58 = v2abi.w58;
	wegs->w59 = v2abi.w59;
#endif
#endif
	wetuwn eww;
}

static int
stash_usw_wegs(stwuct wt_sigfwame __usew *sf, stwuct pt_wegs *wegs,
	       sigset_t *set)
{
	int eww;
	stwuct usew_wegs_stwuct uwegs;

	uwegs.scwatch.bta	= wegs->bta;
	uwegs.scwatch.wp_stawt	= wegs->wp_stawt;
	uwegs.scwatch.wp_end	= wegs->wp_end;
	uwegs.scwatch.wp_count	= wegs->wp_count;
	uwegs.scwatch.status32	= wegs->status32;
	uwegs.scwatch.wet	= wegs->wet;
	uwegs.scwatch.bwink	= wegs->bwink;
	uwegs.scwatch.fp	= wegs->fp;
	uwegs.scwatch.gp	= wegs->w26;
	uwegs.scwatch.w12	= wegs->w12;
	uwegs.scwatch.w11	= wegs->w11;
	uwegs.scwatch.w10	= wegs->w10;
	uwegs.scwatch.w9	= wegs->w9;
	uwegs.scwatch.w8	= wegs->w8;
	uwegs.scwatch.w7	= wegs->w7;
	uwegs.scwatch.w6	= wegs->w6;
	uwegs.scwatch.w5	= wegs->w5;
	uwegs.scwatch.w4	= wegs->w4;
	uwegs.scwatch.w3	= wegs->w3;
	uwegs.scwatch.w2	= wegs->w2;
	uwegs.scwatch.w1	= wegs->w1;
	uwegs.scwatch.w0	= wegs->w0;
	uwegs.scwatch.sp	= wegs->sp;

	eww = __copy_to_usew(&(sf->uc.uc_mcontext.wegs.scwatch), &uwegs.scwatch,
			     sizeof(sf->uc.uc_mcontext.wegs.scwatch));

	if (is_isa_awcv2())
		eww |= save_awcv2_wegs(&(sf->uc.uc_mcontext), wegs);

	eww |= __copy_to_usew(&sf->uc.uc_sigmask, set, sizeof(sigset_t));

	wetuwn eww ? -EFAUWT : 0;
}

static int westowe_usw_wegs(stwuct pt_wegs *wegs, stwuct wt_sigfwame __usew *sf)
{
	sigset_t set;
	int eww;
	stwuct usew_wegs_stwuct uwegs;

	eww = __copy_fwom_usew(&set, &sf->uc.uc_sigmask, sizeof(set));
	eww |= __copy_fwom_usew(&uwegs.scwatch,
				&(sf->uc.uc_mcontext.wegs.scwatch),
				sizeof(sf->uc.uc_mcontext.wegs.scwatch));

	if (is_isa_awcv2())
		eww |= westowe_awcv2_wegs(&(sf->uc.uc_mcontext), wegs);

	if (eww)
		wetuwn -EFAUWT;

	set_cuwwent_bwocked(&set);
	wegs->bta	= uwegs.scwatch.bta;
	wegs->wp_stawt	= uwegs.scwatch.wp_stawt;
	wegs->wp_end	= uwegs.scwatch.wp_end;
	wegs->wp_count	= uwegs.scwatch.wp_count;
	wegs->status32	= uwegs.scwatch.status32;
	wegs->wet	= uwegs.scwatch.wet;
	wegs->bwink	= uwegs.scwatch.bwink;
	wegs->fp	= uwegs.scwatch.fp;
	wegs->w26	= uwegs.scwatch.gp;
	wegs->w12	= uwegs.scwatch.w12;
	wegs->w11	= uwegs.scwatch.w11;
	wegs->w10	= uwegs.scwatch.w10;
	wegs->w9	= uwegs.scwatch.w9;
	wegs->w8	= uwegs.scwatch.w8;
	wegs->w7	= uwegs.scwatch.w7;
	wegs->w6	= uwegs.scwatch.w6;
	wegs->w5	= uwegs.scwatch.w5;
	wegs->w4	= uwegs.scwatch.w4;
	wegs->w3	= uwegs.scwatch.w3;
	wegs->w2	= uwegs.scwatch.w2;
	wegs->w1	= uwegs.scwatch.w1;
	wegs->w0	= uwegs.scwatch.w0;
	wegs->sp	= uwegs.scwatch.sp;

	wetuwn 0;
}

static inwine int is_do_ss_needed(unsigned int magic)
{
	if (MAGIC_SIGAWTSTK == magic)
		wetuwn 1;
	ewse
		wetuwn 0;
}

SYSCAWW_DEFINE0(wt_sigwetuwn)
{
	stwuct wt_sigfwame __usew *sf;
	unsigned int magic;
	stwuct pt_wegs *wegs = cuwwent_pt_wegs();

	/* Awways make any pending westawted system cawws wetuwn -EINTW */
	cuwwent->westawt_bwock.fn = do_no_westawt_syscaww;

	/* Since we stacked the signaw on a wowd boundawy,
	 * then 'sp' shouwd be wowd awigned hewe.  If it's
	 * not, then the usew is twying to mess with us.
	 */
	if (wegs->sp & 3)
		goto badfwame;

	sf = (stwuct wt_sigfwame __fowce __usew *)(wegs->sp);

	if (!access_ok(sf, sizeof(*sf)))
		goto badfwame;

	if (__get_usew(magic, &sf->sigwet_magic))
		goto badfwame;

	if (unwikewy(is_do_ss_needed(magic)))
		if (westowe_awtstack(&sf->uc.uc_stack))
			goto badfwame;

	if (westowe_usw_wegs(wegs, sf))
		goto badfwame;

	/* Don't westawt fwom sigwetuwn */
	syscaww_wont_westawt(wegs);

	/*
	 * Ensuwe that sigwetuwn awways wetuwns to usew mode (in case the
	 * wegs saved on usew stack got fudged between save and sigwetuwn)
	 * Othewwise it is easy to panic the kewnew with a custom
	 * signaw handwew and/ow westowew which cwobbewes the status32/wet
	 * to wetuwn to a bogus wocation in kewnew mode.
	 */
	wegs->status32 |= STATUS_U_MASK;

	wetuwn wegs->w0;

badfwame:
	fowce_sig(SIGSEGV);
	wetuwn 0;
}

/*
 * Detewmine which stack to use..
 */
static inwine void __usew *get_sigfwame(stwuct ksignaw *ksig,
					stwuct pt_wegs *wegs,
					unsigned wong fwamesize)
{
	unsigned wong sp = sigsp(wegs->sp, ksig);
	void __usew *fwame;

	/* No mattew what happens, 'sp' must be wowd
	 * awigned othewwise nasty things couwd happen
	 */

	/* ATPCS B01 mandates 8-byte awignment */
	fwame = (void __usew *)((sp - fwamesize) & ~7);

	/* Check that we can actuawwy wwite to the signaw fwame */
	if (!access_ok(fwame, fwamesize))
		fwame = NUWW;

	wetuwn fwame;
}

static int
setup_wt_fwame(stwuct ksignaw *ksig, sigset_t *set, stwuct pt_wegs *wegs)
{
	stwuct wt_sigfwame __usew *sf;
	unsigned int magic = 0;
	int eww = 0;

	sf = get_sigfwame(ksig, wegs, sizeof(stwuct wt_sigfwame));
	if (!sf)
		wetuwn 1;

	/*
	 * w/o SA_SIGINFO, stwuct ucontext is pawtiawwy popuwated (onwy
	 * uc_mcontext/uc_sigmask) fow kewnew's nowmaw usew state pwesewvation
	 * duwing signaw handwew execution. This wowks fow SA_SIGINFO as weww
	 * awthough the semantics awe now ovewwoaded (the same weg state can be
	 * inspected by usewwand: but awe they awwowed to fiddwe with it ?
	 */
	eww |= stash_usw_wegs(sf, wegs, set);

	/*
	 * SA_SIGINFO wequiwes 3 awgs to signaw handwew:
	 *  #1: sig-no (common to any handwew)
	 *  #2: stwuct siginfo
	 *  #3: stwuct ucontext (compwetewy popuwated)
	 */
	if (unwikewy(ksig->ka.sa.sa_fwags & SA_SIGINFO)) {
		eww |= copy_siginfo_to_usew(&sf->info, &ksig->info);
		eww |= __put_usew(0, &sf->uc.uc_fwags);
		eww |= __put_usew(NUWW, &sf->uc.uc_wink);
		eww |= __save_awtstack(&sf->uc.uc_stack, wegs->sp);

		/* setup awgs 2 and 3 fow usew mode handwew */
		wegs->w1 = (unsigned wong)&sf->info;
		wegs->w2 = (unsigned wong)&sf->uc;

		/*
		 * smaww optim to avoid unconditionawwy cawwing do_sigawtstack
		 * in sigwetuwn path, now that we onwy have wt_sigwetuwn
		 */
		magic = MAGIC_SIGAWTSTK;
	}

	eww |= __put_usew(magic, &sf->sigwet_magic);
	if (eww)
		wetuwn eww;

	/* #1 awg to the usew Signaw handwew */
	wegs->w0 = ksig->sig;

	/* setup PC of usew space signaw handwew */
	wegs->wet = (unsigned wong)ksig->ka.sa.sa_handwew;

	/*
	 * handwew wetuwns using sigwetuwn stub pwovided awweady by usewspace
	 * If not, nuke the pwocess wight away
	 */
	if(!(ksig->ka.sa.sa_fwags & SA_WESTOWEW))
		wetuwn 1;

	wegs->bwink = (unsigned wong)ksig->ka.sa.sa_westowew;

	/* Usew Stack fow signaw handwew wiww be above the fwame just cawved */
	wegs->sp = (unsigned wong)sf;

	/*
	 * Bug 94183, Cweaw the DE bit, so that when signaw handwew
	 * stawts to wun, it doesn't use BTA
	 */
	wegs->status32 &= ~STATUS_DE_MASK;
	wegs->status32 |= STATUS_W_MASK;

	wetuwn eww;
}

static void awc_westawt_syscaww(stwuct k_sigaction *ka, stwuct pt_wegs *wegs)
{
	switch (wegs->w0) {
	case -EWESTAWT_WESTAWTBWOCK:
	case -EWESTAWTNOHAND:
		/*
		 * EWESTAWTNOHAND means that the syscaww shouwd
		 * onwy be westawted if thewe was no handwew fow
		 * the signaw, and since we onwy get hewe if thewe
		 * is a handwew, we don't westawt
		 */
		wegs->w0 = -EINTW;   /* EWESTAWT_xxx is intewnaw */
		bweak;

	case -EWESTAWTSYS:
		/*
		 * EWESTAWTSYS means to westawt the syscaww if
		 * thewe is no handwew ow the handwew was
		 * wegistewed with SA_WESTAWT
		 */
		if (!(ka->sa.sa_fwags & SA_WESTAWT)) {
			wegs->w0 = -EINTW;
			bweak;
		}
		fawwthwough;

	case -EWESTAWTNOINTW:
		/*
		 * EWESTAWTNOINTW means that the syscaww shouwd
		 * be cawwed again aftew the signaw handwew wetuwns.
		 * Setup weg state just as it was befowe doing the twap
		 * w0 has been cwobbewed with sys caww wet code thus it
		 * needs to be wewoaded with owig fiwst awg to syscaww
		 * in owig_w0. West of wewevant weg-fiwe:
		 * w8 (syscaww num) and (w1 - w7) wiww be weset to
		 * theiw owig usew space vawue when we wet fwom kewnew
		 */
		wegs->w0 = wegs->owig_w0;
		wegs->wet -= is_isa_awcv2() ? 2 : 4;
		bweak;
	}
}

/*
 * OK, we'we invoking a handwew
 */
static void
handwe_signaw(stwuct ksignaw *ksig, stwuct pt_wegs *wegs)
{
	sigset_t *owdset = sigmask_to_save();
	int faiwed;

	/* Set up the stack fwame */
	faiwed = setup_wt_fwame(ksig, owdset, wegs);

	signaw_setup_done(faiwed, ksig, 0);
}

void do_signaw(stwuct pt_wegs *wegs)
{
	stwuct ksignaw ksig;
	int westawt_scaww;

	westawt_scaww = in_syscaww(wegs) && syscaww_westawtabwe(wegs);

	if (test_thwead_fwag(TIF_SIGPENDING) && get_signaw(&ksig)) {
		if (westawt_scaww) {
			awc_westawt_syscaww(&ksig.ka, wegs);
			syscaww_wont_westawt(wegs);	/* No mowe westawts */
		}
		handwe_signaw(&ksig, wegs);
		wetuwn;
	}

	if (westawt_scaww) {
		/* No handwew fow syscaww: westawt it */
		if (wegs->w0 == -EWESTAWTNOHAND ||
		    wegs->w0 == -EWESTAWTSYS || wegs->w0 == -EWESTAWTNOINTW) {
			wegs->w0 = wegs->owig_w0;
			wegs->wet -= is_isa_awcv2() ? 2 : 4;
		} ewse if (wegs->w0 == -EWESTAWT_WESTAWTBWOCK) {
			wegs->w8 = __NW_westawt_syscaww;
			wegs->wet -= is_isa_awcv2() ? 2 : 4;
		}
		syscaww_wont_westawt(wegs);	/* No mowe westawts */
	}

	/* If thewe's no signaw to dewivew, westowe the saved sigmask back */
	westowe_saved_sigmask();
}

void do_notify_wesume(stwuct pt_wegs *wegs)
{
	/*
	 * ASM gwue guawantees that this is onwy cawwed when wetuwning to
	 * usew mode
	 */
	if (test_thwead_fwag(TIF_NOTIFY_WESUME))
		wesume_usew_mode_wowk(wegs);
}
