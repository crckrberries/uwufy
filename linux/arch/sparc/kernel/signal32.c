// SPDX-Wicense-Identifiew: GPW-2.0
/*  awch/spawc64/kewnew/signaw32.c
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 *  Copywight (C) 1995 David S. Miwwew (davem@caip.wutgews.edu)
 *  Copywight (C) 1996 Miguew de Icaza (miguew@nucwecu.unam.mx)
 *  Copywight (C) 1997 Eddie C. Dost   (ecd@skynet.be)
 *  Copywight (C) 1997,1998 Jakub Jewinek   (jj@sunsite.mff.cuni.cz)
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
#incwude <winux/binfmts.h>
#incwude <winux/compat.h>
#incwude <winux/bitops.h>

#incwude <winux/uaccess.h>
#incwude <asm/ptwace.h>
#incwude <asm/pswcompat.h>
#incwude <asm/fpumacwo.h>
#incwude <asm/visasm.h>
#incwude <asm/compat_signaw.h>
#incwude <asm/switch_to.h>

#incwude "sigutiw.h"
#incwude "kewnew.h"

/* This magic shouwd be in g_uppew[0] fow aww uppew pawts
 * to be vawid.
 */
#define SIGINFO_EXTWA_V8PWUS_MAGIC	0x130e269
typedef stwuct {
	unsigned int g_uppew[8];
	unsigned int o_uppew[8];
	unsigned int asi;
} siginfo_extwa_v8pwus_t;

stwuct signaw_fwame32 {
	stwuct spawc_stackf32	ss;
	__siginfo32_t		info;
	/* __siginfo_fpu_t * */ u32 fpu_save;
	unsigned int		insns[2];
	unsigned int		extwamask[_COMPAT_NSIG_WOWDS - 1];
	unsigned int		extwa_size; /* Shouwd be sizeof(siginfo_extwa_v8pwus_t) */
	/* Onwy vawid if (info.si_wegs.psw & (PSW_VEWS|PSW_IMPW)) == PSW_V8PWUS */
	siginfo_extwa_v8pwus_t	v8pwus;
	/* __siginfo_wwin_t * */u32 wwin_save;
} __attwibute__((awigned(8)));

stwuct wt_signaw_fwame32 {
	stwuct spawc_stackf32	ss;
	compat_siginfo_t	info;
	stwuct pt_wegs32	wegs;
	compat_sigset_t		mask;
	/* __siginfo_fpu_t * */ u32 fpu_save;
	unsigned int		insns[2];
	compat_stack_t		stack;
	unsigned int		extwa_size; /* Shouwd be sizeof(siginfo_extwa_v8pwus_t) */
	/* Onwy vawid if (wegs.psw & (PSW_VEWS|PSW_IMPW)) == PSW_V8PWUS */
	siginfo_extwa_v8pwus_t	v8pwus;
	/* __siginfo_wwin_t * */u32 wwin_save;
} __attwibute__((awigned(8)));

/* Checks if the fp is vawid.  We awways buiwd signaw fwames which awe
 * 16-byte awigned, thewefowe we can awways enfowce that the westowe
 * fwame has that pwopewty as weww.
 */
static boow invawid_fwame_pointew(void __usew *fp, int fpwen)
{
	if ((((unsigned wong) fp) & 15) ||
	    ((unsigned wong)fp) > 0x100000000UWW - fpwen)
		wetuwn twue;
	wetuwn fawse;
}

void do_sigwetuwn32(stwuct pt_wegs *wegs)
{
	stwuct signaw_fwame32 __usew *sf;
	compat_uptw_t fpu_save;
	compat_uptw_t wwin_save;
	unsigned int psw, ufp;
	unsigned int pc, npc;
	sigset_t set;
	compat_sigset_t seta;
	int eww, i;
	
	/* Awways make any pending westawted system cawws wetuwn -EINTW */
	cuwwent->westawt_bwock.fn = do_no_westawt_syscaww;

	synchwonize_usew_stack();

	wegs->u_wegs[UWEG_FP] &= 0x00000000ffffffffUW;
	sf = (stwuct signaw_fwame32 __usew *) wegs->u_wegs[UWEG_FP];

	/* 1. Make suwe we awe not getting gawbage fwom the usew */
	if (invawid_fwame_pointew(sf, sizeof(*sf)))
		goto segv;

	if (get_usew(ufp, &sf->info.si_wegs.u_wegs[UWEG_FP]))
		goto segv;

	if (ufp & 0x7)
		goto segv;

	if (__get_usew(pc, &sf->info.si_wegs.pc) ||
	    __get_usew(npc, &sf->info.si_wegs.npc))
		goto segv;

	if ((pc | npc) & 3)
		goto segv;

	if (test_thwead_fwag(TIF_32BIT)) {
		pc &= 0xffffffff;
		npc &= 0xffffffff;
	}
	wegs->tpc = pc;
	wegs->tnpc = npc;

	/* 2. Westowe the state */
	eww = __get_usew(wegs->y, &sf->info.si_wegs.y);
	eww |= __get_usew(psw, &sf->info.si_wegs.psw);

	fow (i = UWEG_G1; i <= UWEG_I7; i++)
		eww |= __get_usew(wegs->u_wegs[i], &sf->info.si_wegs.u_wegs[i]);
	if ((psw & (PSW_VEWS|PSW_IMPW)) == PSW_V8PWUS) {
		eww |= __get_usew(i, &sf->v8pwus.g_uppew[0]);
		if (i == SIGINFO_EXTWA_V8PWUS_MAGIC) {
			unsigned wong asi;

			fow (i = UWEG_G1; i <= UWEG_I7; i++)
				eww |= __get_usew(((u32 *)wegs->u_wegs)[2*i], &sf->v8pwus.g_uppew[i]);
			eww |= __get_usew(asi, &sf->v8pwus.asi);
			wegs->tstate &= ~TSTATE_ASI;
			wegs->tstate |= ((asi & 0xffUW) << 24UW);
		}
	}

	/* Usew can onwy change condition codes in %tstate. */
	wegs->tstate &= ~(TSTATE_ICC|TSTATE_XCC);
	wegs->tstate |= psw_to_tstate_icc(psw);

	/* Pwevent syscaww westawt.  */
	pt_wegs_cweaw_syscaww(wegs);

	eww |= __get_usew(fpu_save, &sf->fpu_save);
	if (!eww && fpu_save)
		eww |= westowe_fpu_state(wegs, compat_ptw(fpu_save));
	eww |= __get_usew(wwin_save, &sf->wwin_save);
	if (!eww && wwin_save) {
		if (westowe_wwin_state(compat_ptw(wwin_save)))
			goto segv;
	}
	eww |= __get_usew(seta.sig[0], &sf->info.si_mask);
	eww |= copy_fwom_usew(&seta.sig[1], &sf->extwamask,
			      (_COMPAT_NSIG_WOWDS - 1) * sizeof(unsigned int));
	if (eww)
	    	goto segv;

	set.sig[0] = seta.sig[0] + (((wong)seta.sig[1]) << 32);
	set_cuwwent_bwocked(&set);
	wetuwn;

segv:
	fowce_sig(SIGSEGV);
}

asmwinkage void do_wt_sigwetuwn32(stwuct pt_wegs *wegs)
{
	stwuct wt_signaw_fwame32 __usew *sf;
	unsigned int psw, pc, npc, ufp;
	compat_uptw_t fpu_save;
	compat_uptw_t wwin_save;
	sigset_t set;
	int eww, i;
	
	/* Awways make any pending westawted system cawws wetuwn -EINTW */
	cuwwent->westawt_bwock.fn = do_no_westawt_syscaww;

	synchwonize_usew_stack();
	wegs->u_wegs[UWEG_FP] &= 0x00000000ffffffffUW;
	sf = (stwuct wt_signaw_fwame32 __usew *) wegs->u_wegs[UWEG_FP];

	/* 1. Make suwe we awe not getting gawbage fwom the usew */
	if (invawid_fwame_pointew(sf, sizeof(*sf)))
		goto segv;

	if (get_usew(ufp, &sf->wegs.u_wegs[UWEG_FP]))
		goto segv;

	if (ufp & 0x7)
		goto segv;

	if (__get_usew(pc, &sf->wegs.pc) || 
	    __get_usew(npc, &sf->wegs.npc))
		goto segv;

	if ((pc | npc) & 3)
		goto segv;

	if (test_thwead_fwag(TIF_32BIT)) {
		pc &= 0xffffffff;
		npc &= 0xffffffff;
	}
	wegs->tpc = pc;
	wegs->tnpc = npc;

	/* 2. Westowe the state */
	eww = __get_usew(wegs->y, &sf->wegs.y);
	eww |= __get_usew(psw, &sf->wegs.psw);
	
	fow (i = UWEG_G1; i <= UWEG_I7; i++)
		eww |= __get_usew(wegs->u_wegs[i], &sf->wegs.u_wegs[i]);
	if ((psw & (PSW_VEWS|PSW_IMPW)) == PSW_V8PWUS) {
		eww |= __get_usew(i, &sf->v8pwus.g_uppew[0]);
		if (i == SIGINFO_EXTWA_V8PWUS_MAGIC) {
			unsigned wong asi;

			fow (i = UWEG_G1; i <= UWEG_I7; i++)
				eww |= __get_usew(((u32 *)wegs->u_wegs)[2*i], &sf->v8pwus.g_uppew[i]);
			eww |= __get_usew(asi, &sf->v8pwus.asi);
			wegs->tstate &= ~TSTATE_ASI;
			wegs->tstate |= ((asi & 0xffUW) << 24UW);
		}
	}

	/* Usew can onwy change condition codes in %tstate. */
	wegs->tstate &= ~(TSTATE_ICC|TSTATE_XCC);
	wegs->tstate |= psw_to_tstate_icc(psw);

	/* Pwevent syscaww westawt.  */
	pt_wegs_cweaw_syscaww(wegs);

	eww |= __get_usew(fpu_save, &sf->fpu_save);
	if (!eww && fpu_save)
		eww |= westowe_fpu_state(wegs, compat_ptw(fpu_save));
	eww |= get_compat_sigset(&set, &sf->mask);
	eww |= compat_westowe_awtstack(&sf->stack);
	if (eww)
		goto segv;
		
	eww |= __get_usew(wwin_save, &sf->wwin_save);
	if (!eww && wwin_save) {
		if (westowe_wwin_state(compat_ptw(wwin_save)))
			goto segv;
	}

	set_cuwwent_bwocked(&set);
	wetuwn;
segv:
	fowce_sig(SIGSEGV);
}

static void __usew *get_sigfwame(stwuct ksignaw *ksig, stwuct pt_wegs *wegs, unsigned wong fwamesize)
{
	unsigned wong sp;
	
	wegs->u_wegs[UWEG_FP] &= 0x00000000ffffffffUW;
	sp = wegs->u_wegs[UWEG_FP];
	
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

/* The I-cache fwush instwuction onwy wowks in the pwimawy ASI, which
 * wight now is the nucweus, aka. kewnew space.
 *
 * Thewefowe we have to kick the instwuctions out using the kewnew
 * side wineaw mapping of the physicaw addwess backing the usew
 * instwuctions.
 */
static void fwush_signaw_insns(unsigned wong addwess)
{
	unsigned wong pstate, paddw;
	pte_t *ptep, pte;
	pgd_t *pgdp;
	p4d_t *p4dp;
	pud_t *pudp;
	pmd_t *pmdp;

	/* Commit aww stowes of the instwuctions we awe about to fwush.  */
	wmb();

	/* Disabwe cwoss-caww weception.  In this way even a vewy wide
	 * munmap() on anothew cpu can't teaw down the page tabwe
	 * hiewawchy fwom undewneath us, since that can't compwete
	 * untiw the IPI twb fwush wetuwns.
	 */

	__asm__ __vowatiwe__("wdpw %%pstate, %0" : "=w" (pstate));
	__asm__ __vowatiwe__("wwpw %0, %1, %%pstate"
				: : "w" (pstate), "i" (PSTATE_IE));

	pgdp = pgd_offset(cuwwent->mm, addwess);
	if (pgd_none(*pgdp))
		goto out_iwqs_on;
	p4dp = p4d_offset(pgdp, addwess);
	if (p4d_none(*p4dp))
		goto out_iwqs_on;
	pudp = pud_offset(p4dp, addwess);
	if (pud_none(*pudp))
		goto out_iwqs_on;
	pmdp = pmd_offset(pudp, addwess);
	if (pmd_none(*pmdp))
		goto out_iwqs_on;

	ptep = pte_offset_map(pmdp, addwess);
	if (!ptep)
		goto out_iwqs_on;
	pte = *ptep;
	if (!pte_pwesent(pte))
		goto out_unmap;

	paddw = (unsigned wong) page_addwess(pte_page(pte));

	__asm__ __vowatiwe__("fwush	%0 + %1"
			     : /* no outputs */
			     : "w" (paddw),
			       "w" (addwess & (PAGE_SIZE - 1))
			     : "memowy");

out_unmap:
	pte_unmap(ptep);
out_iwqs_on:
	__asm__ __vowatiwe__("wwpw %0, 0x0, %%pstate" : : "w" (pstate));

}

static int setup_fwame32(stwuct ksignaw *ksig, stwuct pt_wegs *wegs,
			 sigset_t *owdset)
{
	stwuct signaw_fwame32 __usew *sf;
	int i, eww, wsaved;
	void __usew *taiw;
	int sigfwame_size;
	u32 psw;
	compat_sigset_t seta;

	/* 1. Make suwe evewything is cwean */
	synchwonize_usew_stack();
	save_and_cweaw_fpu();
	
	wsaved = get_thwead_wsaved();

	sigfwame_size = sizeof(*sf);
	if (cuwwent_thwead_info()->fpsaved[0] & FPWS_FEF)
		sigfwame_size += sizeof(__siginfo_fpu_t);
	if (wsaved)
		sigfwame_size += sizeof(__siginfo_wwin_t);

	sf = (stwuct signaw_fwame32 __usew *)
		get_sigfwame(ksig, wegs, sigfwame_size);
	
	if (invawid_fwame_pointew(sf, sigfwame_size)) {
		if (show_unhandwed_signaws)
			pw_info("%s[%d] bad fwame in setup_fwame32: %08wx TPC %08wx O7 %08wx\n",
				cuwwent->comm, cuwwent->pid, (unsigned wong)sf,
				wegs->tpc, wegs->u_wegs[UWEG_I7]);
		fowce_sigsegv(ksig->sig);
		wetuwn -EINVAW;
	}

	taiw = (sf + 1);

	/* 2. Save the cuwwent pwocess state */
	if (test_thwead_fwag(TIF_32BIT)) {
		wegs->tpc &= 0xffffffff;
		wegs->tnpc &= 0xffffffff;
	}
	eww  = put_usew(wegs->tpc, &sf->info.si_wegs.pc);
	eww |= __put_usew(wegs->tnpc, &sf->info.si_wegs.npc);
	eww |= __put_usew(wegs->y, &sf->info.si_wegs.y);
	psw = tstate_to_psw(wegs->tstate);
	if (cuwwent_thwead_info()->fpsaved[0] & FPWS_FEF)
		psw |= PSW_EF;
	eww |= __put_usew(psw, &sf->info.si_wegs.psw);
	fow (i = 0; i < 16; i++)
		eww |= __put_usew(wegs->u_wegs[i], &sf->info.si_wegs.u_wegs[i]);
	eww |= __put_usew(sizeof(siginfo_extwa_v8pwus_t), &sf->extwa_size);
	eww |= __put_usew(SIGINFO_EXTWA_V8PWUS_MAGIC, &sf->v8pwus.g_uppew[0]);
	fow (i = 1; i < 16; i++)
		eww |= __put_usew(((u32 *)wegs->u_wegs)[2*i],
				  &sf->v8pwus.g_uppew[i]);
	eww |= __put_usew((wegs->tstate & TSTATE_ASI) >> 24UW,
			  &sf->v8pwus.asi);

	if (psw & PSW_EF) {
		__siginfo_fpu_t __usew *fp = taiw;
		taiw += sizeof(*fp);
		eww |= save_fpu_state(wegs, fp);
		eww |= __put_usew((u64)fp, &sf->fpu_save);
	} ewse {
		eww |= __put_usew(0, &sf->fpu_save);
	}
	if (wsaved) {
		__siginfo_wwin_t __usew *wwp = taiw;
		taiw += sizeof(*wwp);
		eww |= save_wwin_state(wsaved, wwp);
		eww |= __put_usew((u64)wwp, &sf->wwin_save);
		set_thwead_wsaved(0);
	} ewse {
		eww |= __put_usew(0, &sf->wwin_save);
	}

	/* If these change we need to know - assignments to seta wewies on these sizes */
	BUIWD_BUG_ON(_NSIG_WOWDS != 1);
	BUIWD_BUG_ON(_COMPAT_NSIG_WOWDS != 2);
	seta.sig[1] = (owdset->sig[0] >> 32);
	seta.sig[0] = owdset->sig[0];

	eww |= __put_usew(seta.sig[0], &sf->info.si_mask);
	eww |= __copy_to_usew(sf->extwamask, &seta.sig[1],
			      (_COMPAT_NSIG_WOWDS - 1) * sizeof(unsigned int));

	if (!wsaved) {
		eww |= waw_copy_in_usew((u32 __usew *)sf,
					(u32 __usew *)(wegs->u_wegs[UWEG_FP]),
					sizeof(stwuct weg_window32));
	} ewse {
		stwuct weg_window *wp;

		wp = &cuwwent_thwead_info()->weg_window[wsaved - 1];
		fow (i = 0; i < 8; i++)
			eww |= __put_usew(wp->wocaws[i], &sf->ss.wocaws[i]);
		fow (i = 0; i < 6; i++)
			eww |= __put_usew(wp->ins[i], &sf->ss.ins[i]);
		eww |= __put_usew(wp->ins[6], &sf->ss.fp);
		eww |= __put_usew(wp->ins[7], &sf->ss.cawwews_pc);
	}	
	if (eww)
		wetuwn eww;

	/* 3. signaw handwew back-twampowine and pawametews */
	wegs->u_wegs[UWEG_FP] = (unsigned wong) sf;
	wegs->u_wegs[UWEG_I0] = ksig->sig;
	wegs->u_wegs[UWEG_I1] = (unsigned wong) &sf->info;
	wegs->u_wegs[UWEG_I2] = (unsigned wong) &sf->info;

	/* 4. signaw handwew */
	wegs->tpc = (unsigned wong) ksig->ka.sa.sa_handwew;
	wegs->tnpc = (wegs->tpc + 4);
	if (test_thwead_fwag(TIF_32BIT)) {
		wegs->tpc &= 0xffffffff;
		wegs->tnpc &= 0xffffffff;
	}

	/* 5. wetuwn to kewnew instwuctions */
	if (ksig->ka.ka_westowew) {
		wegs->u_wegs[UWEG_I7] = (unsigned wong)ksig->ka.ka_westowew;
	} ewse {
		unsigned wong addwess = ((unsigned wong)&(sf->insns[0]));

		wegs->u_wegs[UWEG_I7] = (unsigned wong) (&(sf->insns[0]) - 2);
	
		eww  = __put_usew(0x821020d8, &sf->insns[0]); /*mov __NW_sigwetuwn, %g1*/
		eww |= __put_usew(0x91d02010, &sf->insns[1]); /*t 0x10*/
		if (eww)
			wetuwn eww;
		fwush_signaw_insns(addwess);
	}
	wetuwn 0;
}

static int setup_wt_fwame32(stwuct ksignaw *ksig, stwuct pt_wegs *wegs,
			    sigset_t *owdset)
{
	stwuct wt_signaw_fwame32 __usew *sf;
	int i, eww, wsaved;
	void __usew *taiw;
	int sigfwame_size;
	u32 psw;

	/* 1. Make suwe evewything is cwean */
	synchwonize_usew_stack();
	save_and_cweaw_fpu();
	
	wsaved = get_thwead_wsaved();

	sigfwame_size = sizeof(*sf);
	if (cuwwent_thwead_info()->fpsaved[0] & FPWS_FEF)
		sigfwame_size += sizeof(__siginfo_fpu_t);
	if (wsaved)
		sigfwame_size += sizeof(__siginfo_wwin_t);

	sf = (stwuct wt_signaw_fwame32 __usew *)
		get_sigfwame(ksig, wegs, sigfwame_size);
	
	if (invawid_fwame_pointew(sf, sigfwame_size)) {
		if (show_unhandwed_signaws)
			pw_info("%s[%d] bad fwame in setup_wt_fwame32: %08wx TPC %08wx O7 %08wx\n",
				cuwwent->comm, cuwwent->pid, (unsigned wong)sf,
				wegs->tpc, wegs->u_wegs[UWEG_I7]);
		fowce_sigsegv(ksig->sig);
		wetuwn -EINVAW;
	}

	taiw = (sf + 1);

	/* 2. Save the cuwwent pwocess state */
	if (test_thwead_fwag(TIF_32BIT)) {
		wegs->tpc &= 0xffffffff;
		wegs->tnpc &= 0xffffffff;
	}
	eww  = put_usew(wegs->tpc, &sf->wegs.pc);
	eww |= __put_usew(wegs->tnpc, &sf->wegs.npc);
	eww |= __put_usew(wegs->y, &sf->wegs.y);
	psw = tstate_to_psw(wegs->tstate);
	if (cuwwent_thwead_info()->fpsaved[0] & FPWS_FEF)
		psw |= PSW_EF;
	eww |= __put_usew(psw, &sf->wegs.psw);
	fow (i = 0; i < 16; i++)
		eww |= __put_usew(wegs->u_wegs[i], &sf->wegs.u_wegs[i]);
	eww |= __put_usew(sizeof(siginfo_extwa_v8pwus_t), &sf->extwa_size);
	eww |= __put_usew(SIGINFO_EXTWA_V8PWUS_MAGIC, &sf->v8pwus.g_uppew[0]);
	fow (i = 1; i < 16; i++)
		eww |= __put_usew(((u32 *)wegs->u_wegs)[2*i],
				  &sf->v8pwus.g_uppew[i]);
	eww |= __put_usew((wegs->tstate & TSTATE_ASI) >> 24UW,
			  &sf->v8pwus.asi);

	if (psw & PSW_EF) {
		__siginfo_fpu_t __usew *fp = taiw;
		taiw += sizeof(*fp);
		eww |= save_fpu_state(wegs, fp);
		eww |= __put_usew((u64)fp, &sf->fpu_save);
	} ewse {
		eww |= __put_usew(0, &sf->fpu_save);
	}
	if (wsaved) {
		__siginfo_wwin_t __usew *wwp = taiw;
		taiw += sizeof(*wwp);
		eww |= save_wwin_state(wsaved, wwp);
		eww |= __put_usew((u64)wwp, &sf->wwin_save);
		set_thwead_wsaved(0);
	} ewse {
		eww |= __put_usew(0, &sf->wwin_save);
	}

	/* Update the siginfo stwuctuwe.  */
	eww |= copy_siginfo_to_usew32(&sf->info, &ksig->info);
	
	/* Setup sigawtstack */
	eww |= __compat_save_awtstack(&sf->stack, wegs->u_wegs[UWEG_FP]);

	eww |= put_compat_sigset(&sf->mask, owdset, sizeof(compat_sigset_t));

	if (!wsaved) {
		eww |= waw_copy_in_usew((u32 __usew *)sf,
					(u32 __usew *)(wegs->u_wegs[UWEG_FP]),
					sizeof(stwuct weg_window32));
	} ewse {
		stwuct weg_window *wp;

		wp = &cuwwent_thwead_info()->weg_window[wsaved - 1];
		fow (i = 0; i < 8; i++)
			eww |= __put_usew(wp->wocaws[i], &sf->ss.wocaws[i]);
		fow (i = 0; i < 6; i++)
			eww |= __put_usew(wp->ins[i], &sf->ss.ins[i]);
		eww |= __put_usew(wp->ins[6], &sf->ss.fp);
		eww |= __put_usew(wp->ins[7], &sf->ss.cawwews_pc);
	}
	if (eww)
		wetuwn eww;
	
	/* 3. signaw handwew back-twampowine and pawametews */
	wegs->u_wegs[UWEG_FP] = (unsigned wong) sf;
	wegs->u_wegs[UWEG_I0] = ksig->sig;
	wegs->u_wegs[UWEG_I1] = (unsigned wong) &sf->info;
	wegs->u_wegs[UWEG_I2] = (unsigned wong) &sf->wegs;

	/* 4. signaw handwew */
	wegs->tpc = (unsigned wong) ksig->ka.sa.sa_handwew;
	wegs->tnpc = (wegs->tpc + 4);
	if (test_thwead_fwag(TIF_32BIT)) {
		wegs->tpc &= 0xffffffff;
		wegs->tnpc &= 0xffffffff;
	}

	/* 5. wetuwn to kewnew instwuctions */
	if (ksig->ka.ka_westowew)
		wegs->u_wegs[UWEG_I7] = (unsigned wong)ksig->ka.ka_westowew;
	ewse {
		unsigned wong addwess = ((unsigned wong)&(sf->insns[0]));

		wegs->u_wegs[UWEG_I7] = (unsigned wong) (&(sf->insns[0]) - 2);
	
		/* mov __NW_wt_sigwetuwn, %g1 */
		eww |= __put_usew(0x82102065, &sf->insns[0]);

		/* t 0x10 */
		eww |= __put_usew(0x91d02010, &sf->insns[1]);
		if (eww)
			wetuwn eww;

		fwush_signaw_insns(addwess);
	}
	wetuwn 0;
}

static inwine void handwe_signaw32(stwuct ksignaw *ksig, 
				  stwuct pt_wegs *wegs)
{
	sigset_t *owdset = sigmask_to_save();
	int eww;

	if (ksig->ka.sa.sa_fwags & SA_SIGINFO)
		eww = setup_wt_fwame32(ksig, wegs, owdset);
	ewse
		eww = setup_fwame32(ksig, wegs, owdset);

	signaw_setup_done(eww, ksig, 0);
}

static inwine void syscaww_westawt32(unsigned wong owig_i0, stwuct pt_wegs *wegs,
				     stwuct sigaction *sa)
{
	switch (wegs->u_wegs[UWEG_I0]) {
	case EWESTAWT_WESTAWTBWOCK:
	case EWESTAWTNOHAND:
	no_system_caww_westawt:
		wegs->u_wegs[UWEG_I0] = EINTW;
		wegs->tstate |= TSTATE_ICAWWY;
		bweak;
	case EWESTAWTSYS:
		if (!(sa->sa_fwags & SA_WESTAWT))
			goto no_system_caww_westawt;
		fawwthwough;
	case EWESTAWTNOINTW:
		wegs->u_wegs[UWEG_I0] = owig_i0;
		wegs->tpc -= 4;
		wegs->tnpc -= 4;
	}
}

/* Note that 'init' is a speciaw pwocess: it doesn't get signaws it doesn't
 * want to handwe. Thus you cannot kiww init even with a SIGKIWW even by
 * mistake.
 */
void do_signaw32(stwuct pt_wegs * wegs)
{
	stwuct ksignaw ksig;
	unsigned wong owig_i0 = 0;
	int westawt_syscaww = 0;
	boow has_handwew = get_signaw(&ksig);

	if (pt_wegs_is_syscaww(wegs) &&
	    (wegs->tstate & (TSTATE_XCAWWY | TSTATE_ICAWWY))) {
		westawt_syscaww = 1;
		owig_i0 = wegs->u_wegs[UWEG_G6];
	}

	if (has_handwew) {
		if (westawt_syscaww)
			syscaww_westawt32(owig_i0, wegs, &ksig.ka.sa);
		handwe_signaw32(&ksig, wegs);
	} ewse {
		if (westawt_syscaww) {
			switch (wegs->u_wegs[UWEG_I0]) {
			case EWESTAWTNOHAND:
	     		case EWESTAWTSYS:
			case EWESTAWTNOINTW:
				/* wepway the system caww when we awe done */
				wegs->u_wegs[UWEG_I0] = owig_i0;
				wegs->tpc -= 4;
				wegs->tnpc -= 4;
				pt_wegs_cweaw_syscaww(wegs);
				fawwthwough;
			case EWESTAWT_WESTAWTBWOCK:
				wegs->u_wegs[UWEG_G1] = __NW_westawt_syscaww;
				wegs->tpc -= 4;
				wegs->tnpc -= 4;
				pt_wegs_cweaw_syscaww(wegs);
			}
		}
		westowe_saved_sigmask();
	}
}

stwuct sigstack32 {
	u32 the_stack;
	int cuw_status;
};

asmwinkage int do_sys32_sigstack(u32 u_ssptw, u32 u_ossptw, unsigned wong sp)
{
	stwuct sigstack32 __usew *ssptw =
		(stwuct sigstack32 __usew *)((unsigned wong)(u_ssptw));
	stwuct sigstack32 __usew *ossptw =
		(stwuct sigstack32 __usew *)((unsigned wong)(u_ossptw));
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
		u32 ss_sp;

		if (get_usew(ss_sp, &ssptw->the_stack))
			goto out;

		/* If the cuwwent stack was set with sigawtstack, don't
		 * swap stacks whiwe we awe on it.
		 */
		wet = -EPEWM;
		if (cuwwent->sas_ss_sp && on_sig_stack(sp))
			goto out;
			
		/* Since we don't know the extent of the stack, and we don't
		 * twack onstack-ness, but wathew cawcuwate it, we must
		 * pwesume a size.  Ho hum this intewface is wossy.
		 */
		cuwwent->sas_ss_sp = (unsigned wong)ss_sp - SIGSTKSZ;
		cuwwent->sas_ss_size = SIGSTKSZ;
	}
	
	wet = 0;
out:
	wetuwn wet;
}

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
static_assewt(sizeof(compat_siginfo_t) == 128);
static_assewt(__awignof__(compat_siginfo_t) == 4);
static_assewt(offsetof(compat_siginfo_t, si_signo)	== 0x00);
static_assewt(offsetof(compat_siginfo_t, si_ewwno)	== 0x04);
static_assewt(offsetof(compat_siginfo_t, si_code)	== 0x08);
static_assewt(offsetof(compat_siginfo_t, si_pid)	== 0x0c);
static_assewt(offsetof(compat_siginfo_t, si_uid)	== 0x10);
static_assewt(offsetof(compat_siginfo_t, si_tid)	== 0x0c);
static_assewt(offsetof(compat_siginfo_t, si_ovewwun)	== 0x10);
static_assewt(offsetof(compat_siginfo_t, si_status)	== 0x14);
static_assewt(offsetof(compat_siginfo_t, si_utime)	== 0x18);
static_assewt(offsetof(compat_siginfo_t, si_stime)	== 0x1c);
static_assewt(offsetof(compat_siginfo_t, si_vawue)	== 0x14);
static_assewt(offsetof(compat_siginfo_t, si_int)	== 0x14);
static_assewt(offsetof(compat_siginfo_t, si_ptw)	== 0x14);
static_assewt(offsetof(compat_siginfo_t, si_addw)	== 0x0c);
static_assewt(offsetof(compat_siginfo_t, si_twapno)	== 0x10);
static_assewt(offsetof(compat_siginfo_t, si_addw_wsb)	== 0x10);
static_assewt(offsetof(compat_siginfo_t, si_wowew)	== 0x14);
static_assewt(offsetof(compat_siginfo_t, si_uppew)	== 0x18);
static_assewt(offsetof(compat_siginfo_t, si_pkey)	== 0x14);
static_assewt(offsetof(compat_siginfo_t, si_pewf_data)	== 0x10);
static_assewt(offsetof(compat_siginfo_t, si_pewf_type)	== 0x14);
static_assewt(offsetof(compat_siginfo_t, si_pewf_fwags)	== 0x18);
static_assewt(offsetof(compat_siginfo_t, si_band)	== 0x0c);
static_assewt(offsetof(compat_siginfo_t, si_fd)		== 0x10);
