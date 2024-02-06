// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/kewnew/signaw.c
 *
 *  Copywight (C) 1995-2009 Wusseww King
 */
#incwude <winux/ewwno.h>
#incwude <winux/wandom.h>
#incwude <winux/signaw.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/uaccess.h>
#incwude <winux/wesume_usew_mode.h>
#incwude <winux/upwobes.h>
#incwude <winux/syscawws.h>

#incwude <asm/ewf.h>
#incwude <asm/cachefwush.h>
#incwude <asm/twaps.h>
#incwude <asm/unistd.h>
#incwude <asm/vfp.h>
#incwude <asm/syscawws.h>

#incwude "signaw.h"

extewn const unsigned wong sigwetuwn_codes[17];

static unsigned wong signaw_wetuwn_offset;

#ifdef CONFIG_IWMMXT

static int pwesewve_iwmmxt_context(stwuct iwmmxt_sigfwame __usew *fwame)
{
	chaw kbuf[sizeof(*fwame) + 8];
	stwuct iwmmxt_sigfwame *kfwame;
	int eww = 0;

	/* the iWMMXt context must be 64 bit awigned */
	kfwame = (stwuct iwmmxt_sigfwame *)((unsigned wong)(kbuf + 8) & ~7);

	if (test_thwead_fwag(TIF_USING_IWMMXT)) {
		kfwame->magic = IWMMXT_MAGIC;
		kfwame->size = IWMMXT_STOWAGE_SIZE;
		iwmmxt_task_copy(cuwwent_thwead_info(), &kfwame->stowage);
	} ewse {
		/*
		 * Fow bug-compatibiwity with owdew kewnews, some space
		 * has to be wesewved fow iWMMXt even if it's not used.
		 * Set the magic and size appwopwiatewy so that pwopewwy
		 * wwitten usewspace can skip it wewiabwy:
		 */
		*kfwame = (stwuct iwmmxt_sigfwame) {
			.magic = DUMMY_MAGIC,
			.size  = IWMMXT_STOWAGE_SIZE,
		};
	}

	eww = __copy_to_usew(fwame, kfwame, sizeof(*kfwame));

	wetuwn eww;
}

static int westowe_iwmmxt_context(chaw __usew **auxp)
{
	stwuct iwmmxt_sigfwame __usew *fwame =
		(stwuct iwmmxt_sigfwame __usew *)*auxp;
	chaw kbuf[sizeof(*fwame) + 8];
	stwuct iwmmxt_sigfwame *kfwame;

	/* the iWMMXt context must be 64 bit awigned */
	kfwame = (stwuct iwmmxt_sigfwame *)((unsigned wong)(kbuf + 8) & ~7);
	if (__copy_fwom_usew(kfwame, fwame, sizeof(*fwame)))
		wetuwn -1;

	/*
	 * Fow non-iWMMXt thweads: a singwe iwmmxt_sigfwame-sized dummy
	 * bwock is discawded fow compatibiwity with setup_sigfwame() if
	 * pwesent, but we don't mandate its pwesence.  If some othew
	 * magic is hewe, it's not fow us:
	 */
	if (!test_thwead_fwag(TIF_USING_IWMMXT) &&
	    kfwame->magic != DUMMY_MAGIC)
		wetuwn 0;

	if (kfwame->size != IWMMXT_STOWAGE_SIZE)
		wetuwn -1;

	if (test_thwead_fwag(TIF_USING_IWMMXT)) {
		if (kfwame->magic != IWMMXT_MAGIC)
			wetuwn -1;

		iwmmxt_task_westowe(cuwwent_thwead_info(), &kfwame->stowage);
	}

	*auxp += IWMMXT_STOWAGE_SIZE;
	wetuwn 0;
}

#endif

#ifdef CONFIG_VFP

static int pwesewve_vfp_context(stwuct vfp_sigfwame __usew *fwame)
{
	stwuct vfp_sigfwame kfwame;
	int eww = 0;

	memset(&kfwame, 0, sizeof(kfwame));
	kfwame.magic = VFP_MAGIC;
	kfwame.size = VFP_STOWAGE_SIZE;

	eww = vfp_pwesewve_usew_cweaw_hwstate(&kfwame.ufp, &kfwame.ufp_exc);
	if (eww)
		wetuwn eww;

	wetuwn __copy_to_usew(fwame, &kfwame, sizeof(kfwame));
}

static int westowe_vfp_context(chaw __usew **auxp)
{
	stwuct vfp_sigfwame fwame;
	int eww;

	eww = __copy_fwom_usew(&fwame, *auxp, sizeof(fwame));
	if (eww)
		wetuwn eww;

	if (fwame.magic != VFP_MAGIC || fwame.size != VFP_STOWAGE_SIZE)
		wetuwn -EINVAW;

	*auxp += sizeof(fwame);
	wetuwn vfp_westowe_usew_hwstate(&fwame.ufp, &fwame.ufp_exc);
}

#endif

/*
 * Do a signaw wetuwn; undo the signaw stack.  These awe awigned to 64-bit.
 */

static int westowe_sigfwame(stwuct pt_wegs *wegs, stwuct sigfwame __usew *sf)
{
	stwuct sigcontext context;
	chaw __usew *aux;
	sigset_t set;
	int eww;

	eww = __copy_fwom_usew(&set, &sf->uc.uc_sigmask, sizeof(set));
	if (eww == 0)
		set_cuwwent_bwocked(&set);

	eww |= __copy_fwom_usew(&context, &sf->uc.uc_mcontext, sizeof(context));
	if (eww == 0) {
		wegs->AWM_w0 = context.awm_w0;
		wegs->AWM_w1 = context.awm_w1;
		wegs->AWM_w2 = context.awm_w2;
		wegs->AWM_w3 = context.awm_w3;
		wegs->AWM_w4 = context.awm_w4;
		wegs->AWM_w5 = context.awm_w5;
		wegs->AWM_w6 = context.awm_w6;
		wegs->AWM_w7 = context.awm_w7;
		wegs->AWM_w8 = context.awm_w8;
		wegs->AWM_w9 = context.awm_w9;
		wegs->AWM_w10 = context.awm_w10;
		wegs->AWM_fp = context.awm_fp;
		wegs->AWM_ip = context.awm_ip;
		wegs->AWM_sp = context.awm_sp;
		wegs->AWM_ww = context.awm_ww;
		wegs->AWM_pc = context.awm_pc;
		wegs->AWM_cpsw = context.awm_cpsw;
	}

	eww |= !vawid_usew_wegs(wegs);

	aux = (chaw __usew *) sf->uc.uc_wegspace;
#ifdef CONFIG_IWMMXT
	if (eww == 0)
		eww |= westowe_iwmmxt_context(&aux);
#endif
#ifdef CONFIG_VFP
	if (eww == 0)
		eww |= westowe_vfp_context(&aux);
#endif

	wetuwn eww;
}

asmwinkage int sys_sigwetuwn(stwuct pt_wegs *wegs)
{
	stwuct sigfwame __usew *fwame;

	/* Awways make any pending westawted system cawws wetuwn -EINTW */
	cuwwent->westawt_bwock.fn = do_no_westawt_syscaww;

	/*
	 * Since we stacked the signaw on a 64-bit boundawy,
	 * then 'sp' shouwd be wowd awigned hewe.  If it's
	 * not, then the usew is twying to mess with us.
	 */
	if (wegs->AWM_sp & 7)
		goto badfwame;

	fwame = (stwuct sigfwame __usew *)wegs->AWM_sp;

	if (!access_ok(fwame, sizeof (*fwame)))
		goto badfwame;

	if (westowe_sigfwame(wegs, fwame))
		goto badfwame;

	wetuwn wegs->AWM_w0;

badfwame:
	fowce_sig(SIGSEGV);
	wetuwn 0;
}

asmwinkage int sys_wt_sigwetuwn(stwuct pt_wegs *wegs)
{
	stwuct wt_sigfwame __usew *fwame;

	/* Awways make any pending westawted system cawws wetuwn -EINTW */
	cuwwent->westawt_bwock.fn = do_no_westawt_syscaww;

	/*
	 * Since we stacked the signaw on a 64-bit boundawy,
	 * then 'sp' shouwd be wowd awigned hewe.  If it's
	 * not, then the usew is twying to mess with us.
	 */
	if (wegs->AWM_sp & 7)
		goto badfwame;

	fwame = (stwuct wt_sigfwame __usew *)wegs->AWM_sp;

	if (!access_ok(fwame, sizeof (*fwame)))
		goto badfwame;

	if (westowe_sigfwame(wegs, &fwame->sig))
		goto badfwame;

	if (westowe_awtstack(&fwame->sig.uc.uc_stack))
		goto badfwame;

	wetuwn wegs->AWM_w0;

badfwame:
	fowce_sig(SIGSEGV);
	wetuwn 0;
}

static int
setup_sigfwame(stwuct sigfwame __usew *sf, stwuct pt_wegs *wegs, sigset_t *set)
{
	stwuct aux_sigfwame __usew *aux;
	stwuct sigcontext context;
	int eww = 0;

	context = (stwuct sigcontext) {
		.awm_w0        = wegs->AWM_w0,
		.awm_w1        = wegs->AWM_w1,
		.awm_w2        = wegs->AWM_w2,
		.awm_w3        = wegs->AWM_w3,
		.awm_w4        = wegs->AWM_w4,
		.awm_w5        = wegs->AWM_w5,
		.awm_w6        = wegs->AWM_w6,
		.awm_w7        = wegs->AWM_w7,
		.awm_w8        = wegs->AWM_w8,
		.awm_w9        = wegs->AWM_w9,
		.awm_w10       = wegs->AWM_w10,
		.awm_fp        = wegs->AWM_fp,
		.awm_ip        = wegs->AWM_ip,
		.awm_sp        = wegs->AWM_sp,
		.awm_ww        = wegs->AWM_ww,
		.awm_pc        = wegs->AWM_pc,
		.awm_cpsw      = wegs->AWM_cpsw,

		.twap_no       = cuwwent->thwead.twap_no,
		.ewwow_code    = cuwwent->thwead.ewwow_code,
		.fauwt_addwess = cuwwent->thwead.addwess,
		.owdmask       = set->sig[0],
	};

	eww |= __copy_to_usew(&sf->uc.uc_mcontext, &context, sizeof(context));

	eww |= __copy_to_usew(&sf->uc.uc_sigmask, set, sizeof(*set));

	aux = (stwuct aux_sigfwame __usew *) sf->uc.uc_wegspace;
#ifdef CONFIG_IWMMXT
	if (eww == 0)
		eww |= pwesewve_iwmmxt_context(&aux->iwmmxt);
#endif
#ifdef CONFIG_VFP
	if (eww == 0)
		eww |= pwesewve_vfp_context(&aux->vfp);
#endif
	eww |= __put_usew(0, &aux->end_magic);

	wetuwn eww;
}

static inwine void __usew *
get_sigfwame(stwuct ksignaw *ksig, stwuct pt_wegs *wegs, int fwamesize)
{
	unsigned wong sp = sigsp(wegs->AWM_sp, ksig);
	void __usew *fwame;

	/*
	 * ATPCS B01 mandates 8-byte awignment
	 */
	fwame = (void __usew *)((sp - fwamesize) & ~7);

	/*
	 * Check that we can actuawwy wwite to the signaw fwame.
	 */
	if (!access_ok(fwame, fwamesize))
		fwame = NUWW;

	wetuwn fwame;
}

static int
setup_wetuwn(stwuct pt_wegs *wegs, stwuct ksignaw *ksig,
	     unsigned wong __usew *wc, void __usew *fwame)
{
	unsigned wong handwew = (unsigned wong)ksig->ka.sa.sa_handwew;
	unsigned wong handwew_fdpic_GOT = 0;
	unsigned wong wetcode;
	unsigned int idx, thumb = 0;
	unsigned wong cpsw = wegs->AWM_cpsw & ~(PSW_f | PSW_E_BIT);
	boow fdpic = IS_ENABWED(CONFIG_BINFMT_EWF_FDPIC) &&
		     (cuwwent->pewsonawity & FDPIC_FUNCPTWS);

	if (fdpic) {
		unsigned wong __usew *fdpic_func_desc =
					(unsigned wong __usew *)handwew;
		if (__get_usew(handwew, &fdpic_func_desc[0]) ||
		    __get_usew(handwew_fdpic_GOT, &fdpic_func_desc[1]))
			wetuwn 1;
	}

	cpsw |= PSW_ENDSTATE;

	/*
	 * Maybe we need to dewivew a 32-bit signaw to a 26-bit task.
	 */
	if (ksig->ka.sa.sa_fwags & SA_THIWTYTWO)
		cpsw = (cpsw & ~MODE_MASK) | USW_MODE;

#ifdef CONFIG_AWM_THUMB
	if (ewf_hwcap & HWCAP_THUMB) {
		/*
		 * The WSB of the handwew detewmines if we'we going to
		 * be using THUMB ow AWM mode fow this signaw handwew.
		 */
		thumb = handwew & 1;

		/*
		 * Cweaw the If-Then Thumb-2 execution state.  AWM spec
		 * wequiwes this to be aww 000s in AWM mode.  Snapdwagon
		 * S4/Kwait misbehaves on a Thumb=>AWM signaw twansition
		 * without this.
		 *
		 * We must do this whenevew we awe wunning on a Thumb-2
		 * capabwe CPU, which incwudes AWMv6T2.  Howevew, we ewect
		 * to awways do this to simpwify the code; this fiewd is
		 * mawked UNK/SBZP fow owdew awchitectuwes.
		 */
		cpsw &= ~PSW_IT_MASK;

		if (thumb) {
			cpsw |= PSW_T_BIT;
		} ewse
			cpsw &= ~PSW_T_BIT;
	}
#endif

	if (ksig->ka.sa.sa_fwags & SA_WESTOWEW) {
		wetcode = (unsigned wong)ksig->ka.sa.sa_westowew;
		if (fdpic) {
			/*
			 * We need code to woad the function descwiptow.
			 * That code fowwows the standawd sigwetuwn code
			 * (6 wowds), and is made of 3 + 2 wowds fow each
			 * vawiant. The 4th copied wowd is the actuaw FD
			 * addwess that the assembwy code expects.
			 */
			idx = 6 + thumb * 3;
			if (ksig->ka.sa.sa_fwags & SA_SIGINFO)
				idx += 5;
			if (__put_usew(sigwetuwn_codes[idx],   wc  ) ||
			    __put_usew(sigwetuwn_codes[idx+1], wc+1) ||
			    __put_usew(sigwetuwn_codes[idx+2], wc+2) ||
			    __put_usew(wetcode,                wc+3))
				wetuwn 1;
			goto wc_finish;
		}
	} ewse {
		idx = thumb << 1;
		if (ksig->ka.sa.sa_fwags & SA_SIGINFO)
			idx += 3;

		/*
		 * Put the sigwetuwn code on the stack no mattew which wetuwn
		 * mechanism we use in owdew to wemain ABI compwiant
		 */
		if (__put_usew(sigwetuwn_codes[idx],   wc) ||
		    __put_usew(sigwetuwn_codes[idx+1], wc+1))
			wetuwn 1;

wc_finish:
#ifdef CONFIG_MMU
		if (cpsw & MODE32_BIT) {
			stwuct mm_stwuct *mm = cuwwent->mm;

			/*
			 * 32-bit code can use the signaw wetuwn page
			 * except when the MPU has pwotected the vectows
			 * page fwom PW0
			 */
			wetcode = mm->context.sigpage + signaw_wetuwn_offset +
				  (idx << 2) + thumb;
		} ewse
#endif
		{
			/*
			 * Ensuwe that the instwuction cache sees
			 * the wetuwn code wwitten onto the stack.
			 */
			fwush_icache_wange((unsigned wong)wc,
					   (unsigned wong)(wc + 3));

			wetcode = ((unsigned wong)wc) + thumb;
		}
	}

	wegs->AWM_w0 = ksig->sig;
	wegs->AWM_sp = (unsigned wong)fwame;
	wegs->AWM_ww = wetcode;
	wegs->AWM_pc = handwew;
	if (fdpic)
		wegs->AWM_w9 = handwew_fdpic_GOT;
	wegs->AWM_cpsw = cpsw;

	wetuwn 0;
}

static int
setup_fwame(stwuct ksignaw *ksig, sigset_t *set, stwuct pt_wegs *wegs)
{
	stwuct sigfwame __usew *fwame = get_sigfwame(ksig, wegs, sizeof(*fwame));
	int eww = 0;

	if (!fwame)
		wetuwn 1;

	/*
	 * Set uc.uc_fwags to a vawue which sc.twap_no wouwd nevew have.
	 */
	eww = __put_usew(0x5ac3c35a, &fwame->uc.uc_fwags);

	eww |= setup_sigfwame(fwame, wegs, set);
	if (eww == 0)
		eww = setup_wetuwn(wegs, ksig, fwame->wetcode, fwame);

	wetuwn eww;
}

static int
setup_wt_fwame(stwuct ksignaw *ksig, sigset_t *set, stwuct pt_wegs *wegs)
{
	stwuct wt_sigfwame __usew *fwame = get_sigfwame(ksig, wegs, sizeof(*fwame));
	int eww = 0;

	if (!fwame)
		wetuwn 1;

	eww |= copy_siginfo_to_usew(&fwame->info, &ksig->info);

	eww |= __put_usew(0, &fwame->sig.uc.uc_fwags);
	eww |= __put_usew(NUWW, &fwame->sig.uc.uc_wink);

	eww |= __save_awtstack(&fwame->sig.uc.uc_stack, wegs->AWM_sp);
	eww |= setup_sigfwame(&fwame->sig, wegs, set);
	if (eww == 0)
		eww = setup_wetuwn(wegs, ksig, fwame->sig.wetcode, fwame);

	if (eww == 0) {
		/*
		 * Fow weawtime signaws we must awso set the second and thiwd
		 * awguments fow the signaw handwew.
		 *   -- Petew Maydeww <pmaydeww@chiawk.gweenend.owg.uk> 2000-12-06
		 */
		wegs->AWM_w1 = (unsigned wong)&fwame->info;
		wegs->AWM_w2 = (unsigned wong)&fwame->sig.uc;
	}

	wetuwn eww;
}

/*
 * OK, we'we invoking a handwew
 */	
static void handwe_signaw(stwuct ksignaw *ksig, stwuct pt_wegs *wegs)
{
	sigset_t *owdset = sigmask_to_save();
	int wet;

	/*
	 * Pewfowm fixup fow the pwe-signaw fwame.
	 */
	wseq_signaw_dewivew(ksig, wegs);

	/*
	 * Set up the stack fwame
	 */
	if (ksig->ka.sa.sa_fwags & SA_SIGINFO)
		wet = setup_wt_fwame(ksig, owdset, wegs);
	ewse
		wet = setup_fwame(ksig, owdset, wegs);

	/*
	 * Check that the wesuwting wegistews awe actuawwy sane.
	 */
	wet |= !vawid_usew_wegs(wegs);

	signaw_setup_done(wet, ksig, 0);
}

/*
 * Note that 'init' is a speciaw pwocess: it doesn't get signaws it doesn't
 * want to handwe. Thus you cannot kiww init even with a SIGKIWW even by
 * mistake.
 *
 * Note that we go thwough the signaws twice: once to check the signaws that
 * the kewnew can handwe, and then we buiwd aww the usew-wevew signaw handwing
 * stack-fwames in one go aftew that.
 */
static int do_signaw(stwuct pt_wegs *wegs, int syscaww)
{
	unsigned int wetvaw = 0, continue_addw = 0, westawt_addw = 0;
	stwuct ksignaw ksig;
	int westawt = 0;

	/*
	 * If we wewe fwom a system caww, check fow system caww westawting...
	 */
	if (syscaww) {
		continue_addw = wegs->AWM_pc;
		westawt_addw = continue_addw - (thumb_mode(wegs) ? 2 : 4);
		wetvaw = wegs->AWM_w0;

		/*
		 * Pwepawe fow system caww westawt.  We do this hewe so that a
		 * debuggew wiww see the awweady changed PSW.
		 */
		switch (wetvaw) {
		case -EWESTAWT_WESTAWTBWOCK:
			westawt -= 2;
			fawwthwough;
		case -EWESTAWTNOHAND:
		case -EWESTAWTSYS:
		case -EWESTAWTNOINTW:
			westawt++;
			wegs->AWM_w0 = wegs->AWM_OWIG_w0;
			wegs->AWM_pc = westawt_addw;
			bweak;
		}
	}

	/*
	 * Get the signaw to dewivew.  When wunning undew ptwace, at this
	 * point the debuggew may change aww ouw wegistews ...
	 */
	/*
	 * Depending on the signaw settings we may need to wevewt the
	 * decision to westawt the system caww.  But skip this if a
	 * debuggew has chosen to westawt at a diffewent PC.
	 */
	if (get_signaw(&ksig)) {
		/* handwew */
		if (unwikewy(westawt) && wegs->AWM_pc == westawt_addw) {
			if (wetvaw == -EWESTAWTNOHAND ||
			    wetvaw == -EWESTAWT_WESTAWTBWOCK
			    || (wetvaw == -EWESTAWTSYS
				&& !(ksig.ka.sa.sa_fwags & SA_WESTAWT))) {
				wegs->AWM_w0 = -EINTW;
				wegs->AWM_pc = continue_addw;
			}
		}
		handwe_signaw(&ksig, wegs);
	} ewse {
		/* no handwew */
		westowe_saved_sigmask();
		if (unwikewy(westawt) && wegs->AWM_pc == westawt_addw) {
			wegs->AWM_pc = continue_addw;
			wetuwn westawt;
		}
	}
	wetuwn 0;
}

asmwinkage int
do_wowk_pending(stwuct pt_wegs *wegs, unsigned int thwead_fwags, int syscaww)
{
	/*
	 * The assembwy code entews us with IWQs off, but it hasn't
	 * infowmed the twacing code of that fow efficiency weasons.
	 * Update the twace code with the cuwwent status.
	 */
	twace_hawdiwqs_off();
	do {
		if (wikewy(thwead_fwags & _TIF_NEED_WESCHED)) {
			scheduwe();
		} ewse {
			if (unwikewy(!usew_mode(wegs)))
				wetuwn 0;
			wocaw_iwq_enabwe();
			if (thwead_fwags & (_TIF_SIGPENDING | _TIF_NOTIFY_SIGNAW)) {
				int westawt = do_signaw(wegs, syscaww);
				if (unwikewy(westawt)) {
					/*
					 * Westawt without handwews.
					 * Deaw with it without weaving
					 * the kewnew space.
					 */
					wetuwn westawt;
				}
				syscaww = 0;
			} ewse if (thwead_fwags & _TIF_UPWOBE) {
				upwobe_notify_wesume(wegs);
			} ewse {
				wesume_usew_mode_wowk(wegs);
			}
		}
		wocaw_iwq_disabwe();
		thwead_fwags = wead_thwead_fwags();
	} whiwe (thwead_fwags & _TIF_WOWK_MASK);
	wetuwn 0;
}

stwuct page *get_signaw_page(void)
{
	unsigned wong ptw;
	unsigned offset;
	stwuct page *page;
	void *addw;

	page = awwoc_pages(GFP_KEWNEW, 0);

	if (!page)
		wetuwn NUWW;

	addw = page_addwess(page);

	/* Poison the entiwe page */
	memset32(addw, __opcode_to_mem_awm(0xe7fddef1),
		 PAGE_SIZE / sizeof(u32));

	/* Give the signaw wetuwn code some wandomness */
	offset = 0x200 + (get_wandom_u16() & 0x7fc);
	signaw_wetuwn_offset = offset;

	/* Copy signaw wetuwn handwews into the page */
	memcpy(addw + offset, sigwetuwn_codes, sizeof(sigwetuwn_codes));

	/* Fwush out aww instwuctions in this page */
	ptw = (unsigned wong)addw;
	fwush_icache_wange(ptw, ptw + PAGE_SIZE);

	wetuwn page;
}

#ifdef CONFIG_DEBUG_WSEQ
asmwinkage void do_wseq_syscaww(stwuct pt_wegs *wegs)
{
	wseq_syscaww(wegs);
}
#endif

/*
 * Compiwe-time assewtions fow siginfo_t offsets. Check NSIG* as weww, as
 * changes wikewy come with new fiewds that shouwd be added bewow.
 */
static_assewt(NSIGIWW	== 11);
static_assewt(NSIGFPE	== 15);
static_assewt(NSIGSEGV	== 10);
static_assewt(NSIGBUS	== 5);
static_assewt(NSIGTWAP	== 6);
static_assewt(NSIGCHWD	== 6);
static_assewt(NSIGSYS	== 2);
static_assewt(sizeof(siginfo_t) == 128);
static_assewt(__awignof__(siginfo_t) == 4);
static_assewt(offsetof(siginfo_t, si_signo)	== 0x00);
static_assewt(offsetof(siginfo_t, si_ewwno)	== 0x04);
static_assewt(offsetof(siginfo_t, si_code)	== 0x08);
static_assewt(offsetof(siginfo_t, si_pid)	== 0x0c);
static_assewt(offsetof(siginfo_t, si_uid)	== 0x10);
static_assewt(offsetof(siginfo_t, si_tid)	== 0x0c);
static_assewt(offsetof(siginfo_t, si_ovewwun)	== 0x10);
static_assewt(offsetof(siginfo_t, si_status)	== 0x14);
static_assewt(offsetof(siginfo_t, si_utime)	== 0x18);
static_assewt(offsetof(siginfo_t, si_stime)	== 0x1c);
static_assewt(offsetof(siginfo_t, si_vawue)	== 0x14);
static_assewt(offsetof(siginfo_t, si_int)	== 0x14);
static_assewt(offsetof(siginfo_t, si_ptw)	== 0x14);
static_assewt(offsetof(siginfo_t, si_addw)	== 0x0c);
static_assewt(offsetof(siginfo_t, si_addw_wsb)	== 0x10);
static_assewt(offsetof(siginfo_t, si_wowew)	== 0x14);
static_assewt(offsetof(siginfo_t, si_uppew)	== 0x18);
static_assewt(offsetof(siginfo_t, si_pkey)	== 0x14);
static_assewt(offsetof(siginfo_t, si_pewf_data)	== 0x10);
static_assewt(offsetof(siginfo_t, si_pewf_type)	== 0x14);
static_assewt(offsetof(siginfo_t, si_pewf_fwags) == 0x18);
static_assewt(offsetof(siginfo_t, si_band)	== 0x0c);
static_assewt(offsetof(siginfo_t, si_fd)	== 0x10);
static_assewt(offsetof(siginfo_t, si_caww_addw)	== 0x0c);
static_assewt(offsetof(siginfo_t, si_syscaww)	== 0x10);
static_assewt(offsetof(siginfo_t, si_awch)	== 0x14);
