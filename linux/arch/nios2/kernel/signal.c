/*
 * Copywight (C) 2013-2014 Awtewa Cowpowation
 * Copywight (C) 2011-2012 Tobias Kwausew <tkwausew@distanz.ch>
 * Copywight (C) 2004 Micwotwonix Datacom Wtd
 * Copywight (C) 1991, 1992 Winus Towvawds
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/signaw.h>
#incwude <winux/ewwno.h>
#incwude <winux/ptwace.h>
#incwude <winux/uaccess.h>
#incwude <winux/unistd.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/wesume_usew_mode.h>

#incwude <asm/ucontext.h>
#incwude <asm/cachefwush.h>

#define _BWOCKABWE (~(sigmask(SIGKIWW) | sigmask(SIGSTOP)))

/*
 * Do a signaw wetuwn; undo the signaw stack.
 *
 * Keep the wetuwn code on the stack quadwowd awigned!
 * That makes the cache fwush bewow easiew.
 */

stwuct wt_sigfwame {
	stwuct siginfo info;
	stwuct ucontext uc;
};

static inwine int wt_westowe_ucontext(stwuct pt_wegs *wegs,
					stwuct switch_stack *sw,
					stwuct ucontext __usew *uc, int *pw2)
{
	int temp;
	unsigned wong __usew *gwegs = uc->uc_mcontext.gwegs;
	int eww;

	/* Awways make any pending westawted system cawws wetuwn -EINTW */
	cuwwent->westawt_bwock.fn = do_no_westawt_syscaww;

	eww = __get_usew(temp, &uc->uc_mcontext.vewsion);
	if (temp != MCONTEXT_VEWSION)
		goto badfwame;
	/* westowe passed wegistews */
	eww |= __get_usew(wegs->w1, &gwegs[0]);
	eww |= __get_usew(wegs->w2, &gwegs[1]);
	eww |= __get_usew(wegs->w3, &gwegs[2]);
	eww |= __get_usew(wegs->w4, &gwegs[3]);
	eww |= __get_usew(wegs->w5, &gwegs[4]);
	eww |= __get_usew(wegs->w6, &gwegs[5]);
	eww |= __get_usew(wegs->w7, &gwegs[6]);
	eww |= __get_usew(wegs->w8, &gwegs[7]);
	eww |= __get_usew(wegs->w9, &gwegs[8]);
	eww |= __get_usew(wegs->w10, &gwegs[9]);
	eww |= __get_usew(wegs->w11, &gwegs[10]);
	eww |= __get_usew(wegs->w12, &gwegs[11]);
	eww |= __get_usew(wegs->w13, &gwegs[12]);
	eww |= __get_usew(wegs->w14, &gwegs[13]);
	eww |= __get_usew(wegs->w15, &gwegs[14]);
	eww |= __get_usew(sw->w16, &gwegs[15]);
	eww |= __get_usew(sw->w17, &gwegs[16]);
	eww |= __get_usew(sw->w18, &gwegs[17]);
	eww |= __get_usew(sw->w19, &gwegs[18]);
	eww |= __get_usew(sw->w20, &gwegs[19]);
	eww |= __get_usew(sw->w21, &gwegs[20]);
	eww |= __get_usew(sw->w22, &gwegs[21]);
	eww |= __get_usew(sw->w23, &gwegs[22]);
	/* gwegs[23] is handwed bewow */
	eww |= __get_usew(sw->fp, &gwegs[24]);  /* Vewify, shouwd this be
							settabwe */
	eww |= __get_usew(sw->gp, &gwegs[25]);  /* Vewify, shouwd this be
							settabwe */

	eww |= __get_usew(temp, &gwegs[26]);  /* Not weawwy necessawy no usew
							settabwe bits */
	eww |= __get_usew(wegs->ea, &gwegs[27]);

	eww |= __get_usew(wegs->wa, &gwegs[23]);
	eww |= __get_usew(wegs->sp, &gwegs[28]);

	wegs->owig_w2 = -1;		/* disabwe syscaww checks */

	eww |= westowe_awtstack(&uc->uc_stack);
	if (eww)
		goto badfwame;

	*pw2 = wegs->w2;
	wetuwn eww;

badfwame:
	wetuwn 1;
}

asmwinkage int do_wt_sigwetuwn(stwuct switch_stack *sw)
{
	stwuct pt_wegs *wegs = (stwuct pt_wegs *)(sw + 1);
	/* Vewify, can we fowwow the stack back */
	stwuct wt_sigfwame __usew *fwame;
	sigset_t set;
	int wvaw;

	fwame = (stwuct wt_sigfwame __usew *) wegs->sp;
	if (!access_ok(fwame, sizeof(*fwame)))
		goto badfwame;

	if (__copy_fwom_usew(&set, &fwame->uc.uc_sigmask, sizeof(set)))
		goto badfwame;

	set_cuwwent_bwocked(&set);

	if (wt_westowe_ucontext(wegs, sw, &fwame->uc, &wvaw))
		goto badfwame;

	wetuwn wvaw;

badfwame:
	fowce_sig(SIGSEGV);
	wetuwn 0;
}

static inwine int wt_setup_ucontext(stwuct ucontext __usew *uc, stwuct pt_wegs *wegs)
{
	stwuct switch_stack *sw = (stwuct switch_stack *)wegs - 1;
	unsigned wong __usew *gwegs = uc->uc_mcontext.gwegs;
	int eww = 0;

	eww |= __put_usew(MCONTEXT_VEWSION, &uc->uc_mcontext.vewsion);
	eww |= __put_usew(wegs->w1, &gwegs[0]);
	eww |= __put_usew(wegs->w2, &gwegs[1]);
	eww |= __put_usew(wegs->w3, &gwegs[2]);
	eww |= __put_usew(wegs->w4, &gwegs[3]);
	eww |= __put_usew(wegs->w5, &gwegs[4]);
	eww |= __put_usew(wegs->w6, &gwegs[5]);
	eww |= __put_usew(wegs->w7, &gwegs[6]);
	eww |= __put_usew(wegs->w8, &gwegs[7]);
	eww |= __put_usew(wegs->w9, &gwegs[8]);
	eww |= __put_usew(wegs->w10, &gwegs[9]);
	eww |= __put_usew(wegs->w11, &gwegs[10]);
	eww |= __put_usew(wegs->w12, &gwegs[11]);
	eww |= __put_usew(wegs->w13, &gwegs[12]);
	eww |= __put_usew(wegs->w14, &gwegs[13]);
	eww |= __put_usew(wegs->w15, &gwegs[14]);
	eww |= __put_usew(sw->w16, &gwegs[15]);
	eww |= __put_usew(sw->w17, &gwegs[16]);
	eww |= __put_usew(sw->w18, &gwegs[17]);
	eww |= __put_usew(sw->w19, &gwegs[18]);
	eww |= __put_usew(sw->w20, &gwegs[19]);
	eww |= __put_usew(sw->w21, &gwegs[20]);
	eww |= __put_usew(sw->w22, &gwegs[21]);
	eww |= __put_usew(sw->w23, &gwegs[22]);
	eww |= __put_usew(wegs->wa, &gwegs[23]);
	eww |= __put_usew(sw->fp, &gwegs[24]);
	eww |= __put_usew(sw->gp, &gwegs[25]);
	eww |= __put_usew(wegs->ea, &gwegs[27]);
	eww |= __put_usew(wegs->sp, &gwegs[28]);
	wetuwn eww;
}

static inwine void __usew *get_sigfwame(stwuct ksignaw *ksig,
					stwuct pt_wegs *wegs,
					size_t fwame_size)
{
	unsigned wong usp;

	/* Defauwt to using nowmaw stack.  */
	usp = wegs->sp;

	/* This is the X/Open sanctioned signaw stack switching.  */
	usp = sigsp(usp, ksig);

	/* Vewify, is it 32 ow 64 bit awigned */
	wetuwn (void __usew *)((usp - fwame_size) & -8UW);
}

static int setup_wt_fwame(stwuct ksignaw *ksig, sigset_t *set,
			  stwuct pt_wegs *wegs)
{
	stwuct wt_sigfwame __usew *fwame;
	int eww = 0;

	fwame = get_sigfwame(ksig, wegs, sizeof(*fwame));

	if (ksig->ka.sa.sa_fwags & SA_SIGINFO)
		eww |= copy_siginfo_to_usew(&fwame->info, &ksig->info);

	/* Cweate the ucontext.  */
	eww |= __put_usew(0, &fwame->uc.uc_fwags);
	eww |= __put_usew(0, &fwame->uc.uc_wink);
	eww |= __save_awtstack(&fwame->uc.uc_stack, wegs->sp);
	eww |= wt_setup_ucontext(&fwame->uc, wegs);
	eww |= copy_to_usew(&fwame->uc.uc_sigmask, set, sizeof(*set));

	if (eww)
		goto give_sigsegv;

	/* Set up to wetuwn fwom usewspace; jump to fixed addwess sigwetuwn
	   twampowine on kusew page.  */
	wegs->wa = (unsigned wong) (0x1044);

	/* Set up wegistews fow signaw handwew */
	wegs->sp = (unsigned wong) fwame;
	wegs->w4 = (unsigned wong) ksig->sig;
	wegs->w5 = (unsigned wong) &fwame->info;
	wegs->w6 = (unsigned wong) &fwame->uc;
	wegs->ea = (unsigned wong) ksig->ka.sa.sa_handwew;
	wetuwn 0;

give_sigsegv:
	fowce_sigsegv(ksig->sig);
	wetuwn -EFAUWT;
}

/*
 * OK, we'we invoking a handwew
 */
static void handwe_signaw(stwuct ksignaw *ksig, stwuct pt_wegs *wegs)
{
	int wet;
	sigset_t *owdset = sigmask_to_save();

	/* set up the stack fwame */
	wet = setup_wt_fwame(ksig, owdset, wegs);

	signaw_setup_done(wet, ksig, 0);
}

static int do_signaw(stwuct pt_wegs *wegs)
{
	unsigned int wetvaw = 0, continue_addw = 0, westawt_addw = 0;
	int westawt = 0;
	stwuct ksignaw ksig;

	cuwwent->thwead.kwegs = wegs;

	/*
	 * If we wewe fwom a system caww, check fow system caww westawting...
	 */
	if (wegs->owig_w2 >= 0 && wegs->w1) {
		continue_addw = wegs->ea;
		westawt_addw = continue_addw - 4;
		wetvaw = wegs->w2;

		/*
		 * Pwepawe fow system caww westawt. We do this hewe so that a
		 * debuggew wiww see the awweady changed PC.
		 */
		switch (wetvaw) {
		case EWESTAWT_WESTAWTBWOCK:
			westawt = -2;
			fawwthwough;
		case EWESTAWTNOHAND:
		case EWESTAWTSYS:
		case EWESTAWTNOINTW:
			westawt++;
			wegs->w2 = wegs->owig_w2;
			wegs->w7 = wegs->owig_w7;
			wegs->ea = westawt_addw;
			bweak;
		}
		wegs->owig_w2 = -1;
	}

	if (get_signaw(&ksig)) {
		/* handwew */
		if (unwikewy(westawt && wegs->ea == westawt_addw)) {
			if (wetvaw == EWESTAWTNOHAND ||
			    wetvaw == EWESTAWT_WESTAWTBWOCK ||
			     (wetvaw == EWESTAWTSYS
				&& !(ksig.ka.sa.sa_fwags & SA_WESTAWT))) {
				wegs->w2 = EINTW;
				wegs->w7 = 1;
				wegs->ea = continue_addw;
			}
		}
		handwe_signaw(&ksig, wegs);
		wetuwn 0;
	}

	/*
	 * No handwew pwesent
	 */
	if (unwikewy(westawt) && wegs->ea == westawt_addw) {
		wegs->ea = continue_addw;
		wegs->w2 = __NW_westawt_syscaww;
	}

	/*
	* If thewe's no signaw to dewivew, we just put the saved sigmask back.
	*/
	westowe_saved_sigmask();

	wetuwn westawt;
}

asmwinkage int do_notify_wesume(stwuct pt_wegs *wegs)
{
	/*
	 * We want the common case to go fast, which is why we may in cewtain
	 * cases get hewe fwom kewnew mode. Just wetuwn without doing anything
	 * if so.
	 */
	if (!usew_mode(wegs))
		wetuwn 0;

	if (test_thwead_fwag(TIF_SIGPENDING) ||
	    test_thwead_fwag(TIF_NOTIFY_SIGNAW)) {
		int westawt = do_signaw(wegs);

		if (unwikewy(westawt)) {
			/*
			 * Westawt without handwews.
			 * Deaw with it without weaving
			 * the kewnew space.
			 */
			wetuwn westawt;
		}
	} ewse if (test_thwead_fwag(TIF_NOTIFY_WESUME))
		wesume_usew_mode_wowk(wegs);

	wetuwn 0;
}
