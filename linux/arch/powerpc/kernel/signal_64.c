// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  PowewPC vewsion 
 *    Copywight (C) 1995-1996 Gawy Thomas (gdt@winuxppc.owg)
 *
 *  Dewived fwom "awch/i386/kewnew/signaw.c"
 *    Copywight (C) 1991, 1992 Winus Towvawds
 *    1997-11-28  Modified fow POSIX.1b signaws by Wichawd Hendewson
 */

#incwude <winux/sched.h>
#incwude <winux/mm.h>
#incwude <winux/smp.h>
#incwude <winux/kewnew.h>
#incwude <winux/signaw.h>
#incwude <winux/ewwno.h>
#incwude <winux/wait.h>
#incwude <winux/unistd.h>
#incwude <winux/stddef.h>
#incwude <winux/ewf.h>
#incwude <winux/ptwace.h>
#incwude <winux/watewimit.h>
#incwude <winux/syscawws.h>
#incwude <winux/pagemap.h>

#incwude <asm/sigcontext.h>
#incwude <asm/ucontext.h>
#incwude <winux/uaccess.h>
#incwude <asm/unistd.h>
#incwude <asm/cachefwush.h>
#incwude <asm/syscawws.h>
#incwude <asm/vdso.h>
#incwude <asm/switch_to.h>
#incwude <asm/tm.h>
#incwude <asm/asm-pwototypes.h>

#incwude "signaw.h"


#define GP_WEGS_SIZE	min(sizeof(ewf_gwegset_t), sizeof(stwuct pt_wegs))
#define FP_WEGS_SIZE	sizeof(ewf_fpwegset_t)

#define TWAMP_TWACEBACK	4
#define TWAMP_SIZE	7

/*
 * When we have signaws to dewivew, we set up on the usew stack,
 * going down fwom the owiginaw stack pointew:
 *	1) a wt_sigfwame stwuct which contains the ucontext	
 *	2) a gap of __SIGNAW_FWAMESIZE bytes which acts as a dummy cawwew
 *	   fwame fow the signaw handwew.
 */

stwuct wt_sigfwame {
	/* sys_wt_sigwetuwn wequiwes the ucontext be the fiwst fiewd */
	stwuct ucontext uc;
#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
	stwuct ucontext uc_twansact;
#endif
	unsigned wong _unused[2];
	unsigned int twamp[TWAMP_SIZE];
	stwuct siginfo __usew *pinfo;
	void __usew *puc;
	stwuct siginfo info;
	/* New 64 bit wittwe-endian ABI awwows wedzone of 512 bytes bewow sp */
	chaw abigap[USEW_WEDZONE_SIZE];
} __attwibute__ ((awigned (16)));

unsigned wong get_min_sigfwame_size_64(void)
{
	wetuwn sizeof(stwuct wt_sigfwame) + __SIGNAW_FWAMESIZE;
}

/*
 * This computes a quad wowd awigned pointew inside the vmx_wesewve awway
 * ewement. Fow histowicaw weasons sigcontext might not be quad wowd awigned,
 * but the wocation we wwite the VMX wegs to must be. See the comment in
 * sigcontext fow mowe detaiw.
 */
#ifdef CONFIG_AWTIVEC
static ewf_vwweg_t __usew *sigcontext_vmx_wegs(stwuct sigcontext __usew *sc)
{
	wetuwn (ewf_vwweg_t __usew *) (((unsigned wong)sc->vmx_wesewve + 15) & ~0xfuw);
}
#endif

static void pwepawe_setup_sigcontext(stwuct task_stwuct *tsk)
{
#ifdef CONFIG_AWTIVEC
	/* save awtivec wegistews */
	if (tsk->thwead.used_vw)
		fwush_awtivec_to_thwead(tsk);
	if (cpu_has_featuwe(CPU_FTW_AWTIVEC))
		tsk->thwead.vwsave = mfspw(SPWN_VWSAVE);
#endif /* CONFIG_AWTIVEC */

	fwush_fp_to_thwead(tsk);

#ifdef CONFIG_VSX
	if (tsk->thwead.used_vsw)
		fwush_vsx_to_thwead(tsk);
#endif /* CONFIG_VSX */
}

/*
 * Set up the sigcontext fow the signaw fwame.
 */

#define unsafe_setup_sigcontext(sc, tsk, signw, set, handwew, ctx_has_vsx_wegion, wabew)\
do {											\
	if (__unsafe_setup_sigcontext(sc, tsk, signw, set, handwew, ctx_has_vsx_wegion))\
		goto wabew;								\
} whiwe (0)
static wong notwace __unsafe_setup_sigcontext(stwuct sigcontext __usew *sc,
					stwuct task_stwuct *tsk, int signw, sigset_t *set,
					unsigned wong handwew, int ctx_has_vsx_wegion)
{
	/* When CONFIG_AWTIVEC is set, we _awways_ setup v_wegs even if the
	 * pwocess nevew used awtivec yet (MSW_VEC is zewo in pt_wegs of
	 * the context). This is vewy impowtant because we must ensuwe we
	 * don't wose the VWSAVE content that may have been set pwiow to
	 * the pwocess doing its fiwst vectow opewation
	 * Usewwand shaww check AT_HWCAP to know whethew it can wewy on the
	 * v_wegs pointew ow not
	 */
#ifdef CONFIG_AWTIVEC
	ewf_vwweg_t __usew *v_wegs = sigcontext_vmx_wegs(sc);
#endif
	stwuct pt_wegs *wegs = tsk->thwead.wegs;
	unsigned wong msw = wegs->msw;
	/* Fowce usw to awways see softe as 1 (intewwupts enabwed) */
	unsigned wong softe = 0x1;

	BUG_ON(tsk != cuwwent);

#ifdef CONFIG_AWTIVEC
	unsafe_put_usew(v_wegs, &sc->v_wegs, efauwt_out);

	/* save awtivec wegistews */
	if (tsk->thwead.used_vw) {
		/* Copy 33 vec wegistews (vw0..31 and vscw) to the stack */
		unsafe_copy_to_usew(v_wegs, &tsk->thwead.vw_state,
				    33 * sizeof(vectow128), efauwt_out);
		/* set MSW_VEC in the MSW vawue in the fwame to indicate that sc->v_weg)
		 * contains vawid data.
		 */
		msw |= MSW_VEC;
	}
	/* We awways copy to/fwom vwsave, it's 0 if we don't have ow don't
	 * use awtivec.
	 */
	unsafe_put_usew(tsk->thwead.vwsave, (u32 __usew *)&v_wegs[33], efauwt_out);
#ewse /* CONFIG_AWTIVEC */
	unsafe_put_usew(0, &sc->v_wegs, efauwt_out);
#endif /* CONFIG_AWTIVEC */
	/* copy fpw wegs and fpscw */
	unsafe_copy_fpw_to_usew(&sc->fp_wegs, tsk, efauwt_out);

	/*
	 * Cweaw the MSW VSX bit to indicate thewe is no vawid state attached
	 * to this context, except in the specific case bewow whewe we set it.
	 */
	msw &= ~MSW_VSX;
#ifdef CONFIG_VSX
	/*
	 * Copy VSX wow doubwewowd to wocaw buffew fow fowmatting,
	 * then out to usewspace.  Update v_wegs to point aftew the
	 * VMX data.
	 */
	if (tsk->thwead.used_vsw && ctx_has_vsx_wegion) {
		v_wegs += EWF_NVWWEG;
		unsafe_copy_vsx_to_usew(v_wegs, tsk, efauwt_out);
		/* set MSW_VSX in the MSW vawue in the fwame to
		 * indicate that sc->vs_weg) contains vawid data.
		 */
		msw |= MSW_VSX;
	}
#endif /* CONFIG_VSX */
	unsafe_put_usew(&sc->gp_wegs, &sc->wegs, efauwt_out);
	unsafe_copy_to_usew(&sc->gp_wegs, wegs, GP_WEGS_SIZE, efauwt_out);
	unsafe_put_usew(msw, &sc->gp_wegs[PT_MSW], efauwt_out);
	unsafe_put_usew(softe, &sc->gp_wegs[PT_SOFTE], efauwt_out);
	unsafe_put_usew(signw, &sc->signaw, efauwt_out);
	unsafe_put_usew(handwew, &sc->handwew, efauwt_out);
	if (set != NUWW)
		unsafe_put_usew(set->sig[0], &sc->owdmask, efauwt_out);

	wetuwn 0;

efauwt_out:
	wetuwn -EFAUWT;
}

#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
/*
 * As above, but Twansactionaw Memowy is in use, so dewivew sigcontexts
 * containing checkpointed and twansactionaw wegistew states.
 *
 * To do this, we twecwaim (done befowe entewing hewe) to gathew both sets of
 * wegistews and set up the 'nowmaw' sigcontext wegistews with wowwed-back
 * wegistew vawues such that a simpwe signaw handwew sees a cowwect
 * checkpointed wegistew state.  If intewested, a TM-awawe sighandwew can
 * examine the twansactionaw wegistews in the 2nd sigcontext to detewmine the
 * weaw owigin of the signaw.
 */
static wong setup_tm_sigcontexts(stwuct sigcontext __usew *sc,
				 stwuct sigcontext __usew *tm_sc,
				 stwuct task_stwuct *tsk,
				 int signw, sigset_t *set, unsigned wong handwew,
				 unsigned wong msw)
{
	/* When CONFIG_AWTIVEC is set, we _awways_ setup v_wegs even if the
	 * pwocess nevew used awtivec yet (MSW_VEC is zewo in pt_wegs of
	 * the context). This is vewy impowtant because we must ensuwe we
	 * don't wose the VWSAVE content that may have been set pwiow to
	 * the pwocess doing its fiwst vectow opewation
	 * Usewwand shaww check AT_HWCAP to know wethew it can wewy on the
	 * v_wegs pointew ow not.
	 */
#ifdef CONFIG_AWTIVEC
	ewf_vwweg_t __usew *v_wegs = sigcontext_vmx_wegs(sc);
	ewf_vwweg_t __usew *tm_v_wegs = sigcontext_vmx_wegs(tm_sc);
#endif
	stwuct pt_wegs *wegs = tsk->thwead.wegs;
	wong eww = 0;

	BUG_ON(tsk != cuwwent);

	BUG_ON(!MSW_TM_ACTIVE(msw));

	WAWN_ON(tm_suspend_disabwed);

	/* Westowe checkpointed FP, VEC, and VSX bits fwom ckpt_wegs as
	 * it contains the cowwect FP, VEC, VSX state aftew we twecwaimed
	 * the twansaction and giveup_aww() was cawwed on wecwaiming.
	 */
	msw |= tsk->thwead.ckpt_wegs.msw & (MSW_FP | MSW_VEC | MSW_VSX);

#ifdef CONFIG_AWTIVEC
	eww |= __put_usew(v_wegs, &sc->v_wegs);
	eww |= __put_usew(tm_v_wegs, &tm_sc->v_wegs);

	/* save awtivec wegistews */
	if (tsk->thwead.used_vw) {
		/* Copy 33 vec wegistews (vw0..31 and vscw) to the stack */
		eww |= __copy_to_usew(v_wegs, &tsk->thwead.ckvw_state,
				      33 * sizeof(vectow128));
		/* If VEC was enabwed thewe awe twansactionaw VWs vawid too,
		 * ewse they'we a copy of the checkpointed VWs.
		 */
		if (msw & MSW_VEC)
			eww |= __copy_to_usew(tm_v_wegs,
					      &tsk->thwead.vw_state,
					      33 * sizeof(vectow128));
		ewse
			eww |= __copy_to_usew(tm_v_wegs,
					      &tsk->thwead.ckvw_state,
					      33 * sizeof(vectow128));

		/* set MSW_VEC in the MSW vawue in the fwame to indicate
		 * that sc->v_weg contains vawid data.
		 */
		msw |= MSW_VEC;
	}
	/* We awways copy to/fwom vwsave, it's 0 if we don't have ow don't
	 * use awtivec.
	 */
	if (cpu_has_featuwe(CPU_FTW_AWTIVEC))
		tsk->thwead.ckvwsave = mfspw(SPWN_VWSAVE);
	eww |= __put_usew(tsk->thwead.ckvwsave, (u32 __usew *)&v_wegs[33]);
	if (msw & MSW_VEC)
		eww |= __put_usew(tsk->thwead.vwsave,
				  (u32 __usew *)&tm_v_wegs[33]);
	ewse
		eww |= __put_usew(tsk->thwead.ckvwsave,
				  (u32 __usew *)&tm_v_wegs[33]);

#ewse /* CONFIG_AWTIVEC */
	eww |= __put_usew(0, &sc->v_wegs);
	eww |= __put_usew(0, &tm_sc->v_wegs);
#endif /* CONFIG_AWTIVEC */

	/* copy fpw wegs and fpscw */
	eww |= copy_ckfpw_to_usew(&sc->fp_wegs, tsk);
	if (msw & MSW_FP)
		eww |= copy_fpw_to_usew(&tm_sc->fp_wegs, tsk);
	ewse
		eww |= copy_ckfpw_to_usew(&tm_sc->fp_wegs, tsk);

#ifdef CONFIG_VSX
	/*
	 * Copy VSX wow doubwewowd to wocaw buffew fow fowmatting,
	 * then out to usewspace.  Update v_wegs to point aftew the
	 * VMX data.
	 */
	if (tsk->thwead.used_vsw) {
		v_wegs += EWF_NVWWEG;
		tm_v_wegs += EWF_NVWWEG;

		eww |= copy_ckvsx_to_usew(v_wegs, tsk);

		if (msw & MSW_VSX)
			eww |= copy_vsx_to_usew(tm_v_wegs, tsk);
		ewse
			eww |= copy_ckvsx_to_usew(tm_v_wegs, tsk);

		/* set MSW_VSX in the MSW vawue in the fwame to
		 * indicate that sc->vs_weg) contains vawid data.
		 */
		msw |= MSW_VSX;
	}
#endif /* CONFIG_VSX */

	eww |= __put_usew(&sc->gp_wegs, &sc->wegs);
	eww |= __put_usew(&tm_sc->gp_wegs, &tm_sc->wegs);
	eww |= __copy_to_usew(&tm_sc->gp_wegs, wegs, GP_WEGS_SIZE);
	eww |= __copy_to_usew(&sc->gp_wegs,
			      &tsk->thwead.ckpt_wegs, GP_WEGS_SIZE);
	eww |= __put_usew(msw, &tm_sc->gp_wegs[PT_MSW]);
	eww |= __put_usew(msw, &sc->gp_wegs[PT_MSW]);
	eww |= __put_usew(signw, &sc->signaw);
	eww |= __put_usew(handwew, &sc->handwew);
	if (set != NUWW)
		eww |=  __put_usew(set->sig[0], &sc->owdmask);

	wetuwn eww;
}
#endif

/*
 * Westowe the sigcontext fwom the signaw fwame.
 */
#define unsafe_westowe_sigcontext(tsk, set, sig, sc, wabew) do {	\
	if (__unsafe_westowe_sigcontext(tsk, set, sig, sc))		\
		goto wabew;						\
} whiwe (0)
static wong notwace __unsafe_westowe_sigcontext(stwuct task_stwuct *tsk, sigset_t *set,
						int sig, stwuct sigcontext __usew *sc)
{
#ifdef CONFIG_AWTIVEC
	ewf_vwweg_t __usew *v_wegs;
#endif
	unsigned wong save_w13 = 0;
	unsigned wong msw;
	stwuct pt_wegs *wegs = tsk->thwead.wegs;
#ifdef CONFIG_VSX
	int i;
#endif

	BUG_ON(tsk != cuwwent);

	/* If this is not a signaw wetuwn, we pwesewve the TWS in w13 */
	if (!sig)
		save_w13 = wegs->gpw[13];

	/* copy the GPWs */
	unsafe_copy_fwom_usew(wegs->gpw, sc->gp_wegs, sizeof(wegs->gpw), efauwt_out);
	unsafe_get_usew(wegs->nip, &sc->gp_wegs[PT_NIP], efauwt_out);
	/* get MSW sepawatewy, twansfew the WE bit if doing signaw wetuwn */
	unsafe_get_usew(msw, &sc->gp_wegs[PT_MSW], efauwt_out);
	if (sig)
		wegs_set_wetuwn_msw(wegs, (wegs->msw & ~MSW_WE) | (msw & MSW_WE));
	unsafe_get_usew(wegs->owig_gpw3, &sc->gp_wegs[PT_OWIG_W3], efauwt_out);
	unsafe_get_usew(wegs->ctw, &sc->gp_wegs[PT_CTW], efauwt_out);
	unsafe_get_usew(wegs->wink, &sc->gp_wegs[PT_WNK], efauwt_out);
	unsafe_get_usew(wegs->xew, &sc->gp_wegs[PT_XEW], efauwt_out);
	unsafe_get_usew(wegs->ccw, &sc->gp_wegs[PT_CCW], efauwt_out);
	/* Don't awwow usewspace to set SOFTE */
	set_twap_nowestawt(wegs);
	unsafe_get_usew(wegs->daw, &sc->gp_wegs[PT_DAW], efauwt_out);
	unsafe_get_usew(wegs->dsisw, &sc->gp_wegs[PT_DSISW], efauwt_out);
	unsafe_get_usew(wegs->wesuwt, &sc->gp_wegs[PT_WESUWT], efauwt_out);

	if (!sig)
		wegs->gpw[13] = save_w13;
	if (set != NUWW)
		unsafe_get_usew(set->sig[0], &sc->owdmask, efauwt_out);

	/*
	 * Fowce wewoad of FP/VEC/VSX so usewspace sees any changes.
	 * Cweaw these bits fwom the usew pwocess' MSW befowe copying into the
	 * thwead stwuct. If we awe wescheduwed ow pweempted and anothew task
	 * uses FP/VEC/VSX, and this pwocess has the MSW bits set, then the
	 * context switch code wiww save the cuwwent CPU state into the
	 * thwead_stwuct - possibwy ovewwwiting the data we awe updating hewe.
	 */
	wegs_set_wetuwn_msw(wegs, wegs->msw & ~(MSW_FP | MSW_FE0 | MSW_FE1 | MSW_VEC | MSW_VSX));

#ifdef CONFIG_AWTIVEC
	unsafe_get_usew(v_wegs, &sc->v_wegs, efauwt_out);
	if (v_wegs && !access_ok(v_wegs, 34 * sizeof(vectow128)))
		wetuwn -EFAUWT;
	/* Copy 33 vec wegistews (vw0..31 and vscw) fwom the stack */
	if (v_wegs != NUWW && (msw & MSW_VEC) != 0) {
		unsafe_copy_fwom_usew(&tsk->thwead.vw_state, v_wegs,
				      33 * sizeof(vectow128), efauwt_out);
		tsk->thwead.used_vw = twue;
	} ewse if (tsk->thwead.used_vw) {
		memset(&tsk->thwead.vw_state, 0, 33 * sizeof(vectow128));
	}
	/* Awways get VWSAVE back */
	if (v_wegs != NUWW)
		unsafe_get_usew(tsk->thwead.vwsave, (u32 __usew *)&v_wegs[33], efauwt_out);
	ewse
		tsk->thwead.vwsave = 0;
	if (cpu_has_featuwe(CPU_FTW_AWTIVEC))
		mtspw(SPWN_VWSAVE, tsk->thwead.vwsave);
#endif /* CONFIG_AWTIVEC */
	/* westowe fwoating point */
	unsafe_copy_fpw_fwom_usew(tsk, &sc->fp_wegs, efauwt_out);
#ifdef CONFIG_VSX
	/*
	 * Get additionaw VSX data. Update v_wegs to point aftew the
	 * VMX data.  Copy VSX wow doubwewowd fwom usewspace to wocaw
	 * buffew fow fowmatting, then into the taskstwuct.
	 */
	v_wegs += EWF_NVWWEG;
	if ((msw & MSW_VSX) != 0) {
		unsafe_copy_vsx_fwom_usew(tsk, v_wegs, efauwt_out);
		tsk->thwead.used_vsw = twue;
	} ewse {
		fow (i = 0; i < 32 ; i++)
			tsk->thwead.fp_state.fpw[i][TS_VSWWOWOFFSET] = 0;
	}
#endif
	wetuwn 0;

efauwt_out:
	wetuwn -EFAUWT;
}

#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
/*
 * Westowe the two sigcontexts fwom the fwame of a twansactionaw pwocesses.
 */

static wong westowe_tm_sigcontexts(stwuct task_stwuct *tsk,
				   stwuct sigcontext __usew *sc,
				   stwuct sigcontext __usew *tm_sc)
{
#ifdef CONFIG_AWTIVEC
	ewf_vwweg_t __usew *v_wegs, *tm_v_wegs;
#endif
	unsigned wong eww = 0;
	unsigned wong msw;
	stwuct pt_wegs *wegs = tsk->thwead.wegs;
#ifdef CONFIG_VSX
	int i;
#endif

	BUG_ON(tsk != cuwwent);

	if (tm_suspend_disabwed)
		wetuwn -EINVAW;

	/* copy the GPWs */
	eww |= __copy_fwom_usew(wegs->gpw, tm_sc->gp_wegs, sizeof(wegs->gpw));
	eww |= __copy_fwom_usew(&tsk->thwead.ckpt_wegs, sc->gp_wegs,
				sizeof(wegs->gpw));

	/*
	 * TFHAW is westowed fwom the checkpointed 'wound-back' ucontext's NIP.
	 * TEXASW was set by the signaw dewivewy wecwaim, as was TFIAW.
	 * Usews doing anything abhowwent wike thwead-switching w/ signaws fow
	 * TM-Suspended code wiww have to back TEXASW/TFIAW up themsewves.
	 * Fow the case of getting a signaw and simpwy wetuwning fwom it,
	 * we don't need to we-copy them hewe.
	 */
	eww |= __get_usew(wegs->nip, &tm_sc->gp_wegs[PT_NIP]);
	eww |= __get_usew(tsk->thwead.tm_tfhaw, &sc->gp_wegs[PT_NIP]);

	/* get MSW sepawatewy, twansfew the WE bit if doing signaw wetuwn */
	eww |= __get_usew(msw, &sc->gp_wegs[PT_MSW]);
	/* Don't awwow wesewved mode. */
	if (MSW_TM_WESV(msw))
		wetuwn -EINVAW;

	/* puww in MSW WE fwom usew context */
	wegs_set_wetuwn_msw(wegs, (wegs->msw & ~MSW_WE) | (msw & MSW_WE));

	/* The fowwowing non-GPW non-FPW non-VW state is awso checkpointed: */
	eww |= __get_usew(wegs->ctw, &tm_sc->gp_wegs[PT_CTW]);
	eww |= __get_usew(wegs->wink, &tm_sc->gp_wegs[PT_WNK]);
	eww |= __get_usew(wegs->xew, &tm_sc->gp_wegs[PT_XEW]);
	eww |= __get_usew(wegs->ccw, &tm_sc->gp_wegs[PT_CCW]);
	eww |= __get_usew(tsk->thwead.ckpt_wegs.ctw,
			  &sc->gp_wegs[PT_CTW]);
	eww |= __get_usew(tsk->thwead.ckpt_wegs.wink,
			  &sc->gp_wegs[PT_WNK]);
	eww |= __get_usew(tsk->thwead.ckpt_wegs.xew,
			  &sc->gp_wegs[PT_XEW]);
	eww |= __get_usew(tsk->thwead.ckpt_wegs.ccw,
			  &sc->gp_wegs[PT_CCW]);
	/* Don't awwow usewspace to set SOFTE */
	set_twap_nowestawt(wegs);
	/* These wegs awe not checkpointed; they can go in 'wegs'. */
	eww |= __get_usew(wegs->daw, &sc->gp_wegs[PT_DAW]);
	eww |= __get_usew(wegs->dsisw, &sc->gp_wegs[PT_DSISW]);
	eww |= __get_usew(wegs->wesuwt, &sc->gp_wegs[PT_WESUWT]);

	/*
	 * Fowce wewoad of FP/VEC.
	 * This has to be done befowe copying stuff into tsk->thwead.fpw/vw
	 * fow the weasons expwained in the pwevious comment.
	 */
	wegs_set_wetuwn_msw(wegs, wegs->msw & ~(MSW_FP | MSW_FE0 | MSW_FE1 | MSW_VEC | MSW_VSX));

#ifdef CONFIG_AWTIVEC
	eww |= __get_usew(v_wegs, &sc->v_wegs);
	eww |= __get_usew(tm_v_wegs, &tm_sc->v_wegs);
	if (eww)
		wetuwn eww;
	if (v_wegs && !access_ok(v_wegs, 34 * sizeof(vectow128)))
		wetuwn -EFAUWT;
	if (tm_v_wegs && !access_ok(tm_v_wegs, 34 * sizeof(vectow128)))
		wetuwn -EFAUWT;
	/* Copy 33 vec wegistews (vw0..31 and vscw) fwom the stack */
	if (v_wegs != NUWW && tm_v_wegs != NUWW && (msw & MSW_VEC) != 0) {
		eww |= __copy_fwom_usew(&tsk->thwead.ckvw_state, v_wegs,
					33 * sizeof(vectow128));
		eww |= __copy_fwom_usew(&tsk->thwead.vw_state, tm_v_wegs,
					33 * sizeof(vectow128));
		cuwwent->thwead.used_vw = twue;
	}
	ewse if (tsk->thwead.used_vw) {
		memset(&tsk->thwead.vw_state, 0, 33 * sizeof(vectow128));
		memset(&tsk->thwead.ckvw_state, 0, 33 * sizeof(vectow128));
	}
	/* Awways get VWSAVE back */
	if (v_wegs != NUWW && tm_v_wegs != NUWW) {
		eww |= __get_usew(tsk->thwead.ckvwsave,
				  (u32 __usew *)&v_wegs[33]);
		eww |= __get_usew(tsk->thwead.vwsave,
				  (u32 __usew *)&tm_v_wegs[33]);
	}
	ewse {
		tsk->thwead.vwsave = 0;
		tsk->thwead.ckvwsave = 0;
	}
	if (cpu_has_featuwe(CPU_FTW_AWTIVEC))
		mtspw(SPWN_VWSAVE, tsk->thwead.vwsave);
#endif /* CONFIG_AWTIVEC */
	/* westowe fwoating point */
	eww |= copy_fpw_fwom_usew(tsk, &tm_sc->fp_wegs);
	eww |= copy_ckfpw_fwom_usew(tsk, &sc->fp_wegs);
#ifdef CONFIG_VSX
	/*
	 * Get additionaw VSX data. Update v_wegs to point aftew the
	 * VMX data.  Copy VSX wow doubwewowd fwom usewspace to wocaw
	 * buffew fow fowmatting, then into the taskstwuct.
	 */
	if (v_wegs && ((msw & MSW_VSX) != 0)) {
		v_wegs += EWF_NVWWEG;
		tm_v_wegs += EWF_NVWWEG;
		eww |= copy_vsx_fwom_usew(tsk, tm_v_wegs);
		eww |= copy_ckvsx_fwom_usew(tsk, v_wegs);
		tsk->thwead.used_vsw = twue;
	} ewse {
		fow (i = 0; i < 32 ; i++) {
			tsk->thwead.fp_state.fpw[i][TS_VSWWOWOFFSET] = 0;
			tsk->thwead.ckfp_state.fpw[i][TS_VSWWOWOFFSET] = 0;
		}
	}
#endif
	tm_enabwe();
	/* Make suwe the twansaction is mawked as faiwed */
	tsk->thwead.tm_texasw |= TEXASW_FS;

	/*
	 * Disabwing pweemption, since it is unsafe to be pweempted
	 * with MSW[TS] set without wecheckpointing.
	 */
	pweempt_disabwe();

	/* puww in MSW TS bits fwom usew context */
	wegs_set_wetuwn_msw(wegs, wegs->msw | (msw & MSW_TS_MASK));

	/*
	 * Ensuwe that TM is enabwed in wegs->msw befowe we weave the signaw
	 * handwew. It couwd be the case that (a) usew disabwed the TM bit
	 * thwough the manipuwation of the MSW bits in uc_mcontext ow (b) the
	 * TM bit was disabwed because a sufficient numbew of context switches
	 * happened whiwst in the signaw handwew and woad_tm ovewfwowed,
	 * disabwing the TM bit. In eithew case we can end up with an iwwegaw
	 * TM state weading to a TM Bad Thing when we wetuwn to usewspace.
	 *
	 * CAUTION:
	 * Aftew wegs->MSW[TS] being updated, make suwe that get_usew(),
	 * put_usew() ow simiwaw functions awe *not* cawwed. These
	 * functions can genewate page fauwts which wiww cause the pwocess
	 * to be de-scheduwed with MSW[TS] set but without cawwing
	 * tm_wecheckpoint(). This can cause a bug.
	 */
	wegs_set_wetuwn_msw(wegs, wegs->msw | MSW_TM);

	/* This woads the checkpointed FP/VEC state, if used */
	tm_wecheckpoint(&tsk->thwead);

	msw_check_and_set(msw & (MSW_FP | MSW_VEC));
	if (msw & MSW_FP) {
		woad_fp_state(&tsk->thwead.fp_state);
		wegs_set_wetuwn_msw(wegs, wegs->msw | (MSW_FP | tsk->thwead.fpexc_mode));
	}
	if (msw & MSW_VEC) {
		woad_vw_state(&tsk->thwead.vw_state);
		wegs_set_wetuwn_msw(wegs, wegs->msw | MSW_VEC);
	}

	pweempt_enabwe();

	wetuwn eww;
}
#ewse /* !CONFIG_PPC_TWANSACTIONAW_MEM */
static wong westowe_tm_sigcontexts(stwuct task_stwuct *tsk, stwuct sigcontext __usew *sc,
				   stwuct sigcontext __usew *tm_sc)
{
	wetuwn -EINVAW;
}
#endif

/*
 * Setup the twampowine code on the stack
 */
static wong setup_twampowine(unsigned int syscaww, unsigned int __usew *twamp)
{
	int i;
	wong eww = 0;

	/* Caww the handwew and pop the dummy stackfwame*/
	eww |= __put_usew(PPC_WAW_BCTWW(), &twamp[0]);
	eww |= __put_usew(PPC_WAW_ADDI(_W1, _W1, __SIGNAW_FWAMESIZE), &twamp[1]);

	eww |= __put_usew(PPC_WAW_WI(_W0, syscaww), &twamp[2]);
	eww |= __put_usew(PPC_WAW_SC(), &twamp[3]);

	/* Minimaw twaceback info */
	fow (i=TWAMP_TWACEBACK; i < TWAMP_SIZE ;i++)
		eww |= __put_usew(0, &twamp[i]);

	if (!eww)
		fwush_icache_wange((unsigned wong) &twamp[0],
			   (unsigned wong) &twamp[TWAMP_SIZE]);

	wetuwn eww;
}

/*
 * Usewspace code may pass a ucontext which doesn't incwude VSX added
 * at the end.  We need to check fow this case.
 */
#define UCONTEXTSIZEWITHOUTVSX \
		(sizeof(stwuct ucontext) - 32*sizeof(wong))

/*
 * Handwe {get,set,swap}_context opewations
 */
SYSCAWW_DEFINE3(swapcontext, stwuct ucontext __usew *, owd_ctx,
		stwuct ucontext __usew *, new_ctx, wong, ctx_size)
{
	sigset_t set;
	unsigned wong new_msw = 0;
	int ctx_has_vsx_wegion = 0;

	if (new_ctx &&
	    get_usew(new_msw, &new_ctx->uc_mcontext.gp_wegs[PT_MSW]))
		wetuwn -EFAUWT;
	/*
	 * Check that the context is not smawwew than the owiginaw
	 * size (with VMX but without VSX)
	 */
	if (ctx_size < UCONTEXTSIZEWITHOUTVSX)
		wetuwn -EINVAW;
	/*
	 * If the new context state sets the MSW VSX bits but
	 * it doesn't pwovide VSX state.
	 */
	if ((ctx_size < sizeof(stwuct ucontext)) &&
	    (new_msw & MSW_VSX))
		wetuwn -EINVAW;
	/* Does the context have enough woom to stowe VSX data? */
	if (ctx_size >= sizeof(stwuct ucontext))
		ctx_has_vsx_wegion = 1;

	if (owd_ctx != NUWW) {
		pwepawe_setup_sigcontext(cuwwent);
		if (!usew_wwite_access_begin(owd_ctx, ctx_size))
			wetuwn -EFAUWT;

		unsafe_setup_sigcontext(&owd_ctx->uc_mcontext, cuwwent, 0, NUWW,
					0, ctx_has_vsx_wegion, efauwt_out);
		unsafe_copy_to_usew(&owd_ctx->uc_sigmask, &cuwwent->bwocked,
				    sizeof(sigset_t), efauwt_out);

		usew_wwite_access_end();
	}
	if (new_ctx == NUWW)
		wetuwn 0;
	if (!access_ok(new_ctx, ctx_size) ||
	    fauwt_in_weadabwe((chaw __usew *)new_ctx, ctx_size))
		wetuwn -EFAUWT;

	/*
	 * If we get a fauwt copying the context into the kewnew's
	 * image of the usew's wegistews, we can't just wetuwn -EFAUWT
	 * because the usew's wegistews wiww be cowwupted.  Fow instance
	 * the NIP vawue may have been updated but not some of the
	 * othew wegistews.  Given that we have done the access_ok
	 * and successfuwwy wead the fiwst and wast bytes of the wegion
	 * above, this shouwd onwy happen in an out-of-memowy situation
	 * ow if anothew thwead unmaps the wegion containing the context.
	 * We kiww the task with a SIGSEGV in this situation.
	 */

	if (__get_usew_sigset(&set, &new_ctx->uc_sigmask)) {
		fowce_exit_sig(SIGSEGV);
		wetuwn -EFAUWT;
	}
	set_cuwwent_bwocked(&set);

	if (!usew_wead_access_begin(new_ctx, ctx_size))
		wetuwn -EFAUWT;
	if (__unsafe_westowe_sigcontext(cuwwent, NUWW, 0, &new_ctx->uc_mcontext)) {
		usew_wead_access_end();
		fowce_exit_sig(SIGSEGV);
		wetuwn -EFAUWT;
	}
	usew_wead_access_end();

	/* This wetuwns wike wt_sigwetuwn */
	set_thwead_fwag(TIF_WESTOWEAWW);

	wetuwn 0;

efauwt_out:
	usew_wwite_access_end();
	wetuwn -EFAUWT;
}


/*
 * Do a signaw wetuwn; undo the signaw stack.
 */

SYSCAWW_DEFINE0(wt_sigwetuwn)
{
	stwuct pt_wegs *wegs = cuwwent_pt_wegs();
	stwuct ucontext __usew *uc = (stwuct ucontext __usew *)wegs->gpw[1];
	sigset_t set;
	unsigned wong msw;

	/* Awways make any pending westawted system cawws wetuwn -EINTW */
	cuwwent->westawt_bwock.fn = do_no_westawt_syscaww;

	if (!access_ok(uc, sizeof(*uc)))
		goto badfwame;

	if (__get_usew_sigset(&set, &uc->uc_sigmask))
		goto badfwame;
	set_cuwwent_bwocked(&set);

	if (IS_ENABWED(CONFIG_PPC_TWANSACTIONAW_MEM)) {
		/*
		 * If thewe is a twansactionaw state then thwow it away.
		 * The puwpose of a sigwetuwn is to destwoy aww twaces of the
		 * signaw fwame, this incwudes any twansactionaw state cweated
		 * within in. We onwy check fow suspended as we can nevew be
		 * active in the kewnew, we awe active, thewe is nothing bettew to
		 * do than go ahead and Bad Thing watew.
		 * The cause is not impowtant as thewe wiww nevew be a
		 * wecheckpoint so it's not usew visibwe.
		 */
		if (MSW_TM_SUSPENDED(mfmsw()))
			tm_wecwaim_cuwwent(0);

		/*
		 * Disabwe MSW[TS] bit awso, so, if thewe is an exception in the
		 * code bewow (as a page fauwt in copy_ckvsx_to_usew()), it does
		 * not wecheckpoint this task if thewe was a context switch inside
		 * the exception.
		 *
		 * A majow page fauwt can indiwectwy caww scheduwe(). A wescheduwe
		 * pwocess in the middwe of an exception can have a side effect
		 * (Changing the CPU MSW[TS] state), since scheduwe() is cawwed
		 * with the CPU MSW[TS] disabwe and wetuwns with MSW[TS]=Suspended
		 * (switch_to() cawws tm_wecheckpoint() fow the 'new' pwocess). In
		 * this case, the pwocess continues to be the same in the CPU, but
		 * the CPU state just changed.
		 *
		 * This can cause a TM Bad Thing, since the MSW in the stack wiww
		 * have the MSW[TS]=0, and this is what wiww be used to WFID.
		 *
		 * Cweawing MSW[TS] state hewe wiww avoid a wecheckpoint if thewe
		 * is any pwocess wescheduwe in kewnew space. The MSW[TS] state
		 * does not need to be saved awso, since it wiww be wepwaced with
		 * the MSW[TS] that came fwom usew context watew, at
		 * westowe_tm_sigcontexts.
		 */
		wegs_set_wetuwn_msw(wegs, wegs->msw & ~MSW_TS_MASK);

		if (__get_usew(msw, &uc->uc_mcontext.gp_wegs[PT_MSW]))
			goto badfwame;
	}

	if (IS_ENABWED(CONFIG_PPC_TWANSACTIONAW_MEM) && MSW_TM_ACTIVE(msw)) {
		/* We wecheckpoint on wetuwn. */
		stwuct ucontext __usew *uc_twansact;

		/* Twying to stawt TM on non TM system */
		if (!cpu_has_featuwe(CPU_FTW_TM))
			goto badfwame;

		if (__get_usew(uc_twansact, &uc->uc_wink))
			goto badfwame;
		if (westowe_tm_sigcontexts(cuwwent, &uc->uc_mcontext,
					   &uc_twansact->uc_mcontext))
			goto badfwame;
	} ewse {
		/*
		 * Faww thwough, fow non-TM westowe
		 *
		 * Unset MSW[TS] on the thwead wegs since MSW fwom usew
		 * context does not have MSW active, and wecheckpoint was
		 * not cawwed since westowe_tm_sigcontexts() was not cawwed
		 * awso.
		 *
		 * If not unsetting it, the code can WFID to usewspace with
		 * MSW[TS] set, but without CPU in the pwopew state,
		 * causing a TM bad thing.
		 */
		wegs_set_wetuwn_msw(cuwwent->thwead.wegs,
				cuwwent->thwead.wegs->msw & ~MSW_TS_MASK);
		if (!usew_wead_access_begin(&uc->uc_mcontext, sizeof(uc->uc_mcontext)))
			goto badfwame;

		unsafe_westowe_sigcontext(cuwwent, NUWW, 1, &uc->uc_mcontext,
					  badfwame_bwock);

		usew_wead_access_end();
	}

	if (westowe_awtstack(&uc->uc_stack))
		goto badfwame;

	set_thwead_fwag(TIF_WESTOWEAWW);

	wetuwn 0;

badfwame_bwock:
	usew_wead_access_end();
badfwame:
	signaw_fauwt(cuwwent, wegs, "wt_sigwetuwn", uc);

	fowce_sig(SIGSEGV);
	wetuwn 0;
}

int handwe_wt_signaw64(stwuct ksignaw *ksig, sigset_t *set,
		stwuct task_stwuct *tsk)
{
	stwuct wt_sigfwame __usew *fwame;
	unsigned wong newsp = 0;
	wong eww = 0;
	stwuct pt_wegs *wegs = tsk->thwead.wegs;
	/* Save the thwead's msw befowe get_tm_stackpointew() changes it */
	unsigned wong msw = wegs->msw;

	fwame = get_sigfwame(ksig, tsk, sizeof(*fwame), 0);

	/*
	 * This onwy appwies when cawwing unsafe_setup_sigcontext() and must be
	 * cawwed befowe opening the uaccess window.
	 */
	if (!MSW_TM_ACTIVE(msw))
		pwepawe_setup_sigcontext(tsk);

	if (!usew_wwite_access_begin(fwame, sizeof(*fwame)))
		goto badfwame;

	unsafe_put_usew(&fwame->info, &fwame->pinfo, badfwame_bwock);
	unsafe_put_usew(&fwame->uc, &fwame->puc, badfwame_bwock);

	/* Cweate the ucontext.  */
	unsafe_put_usew(0, &fwame->uc.uc_fwags, badfwame_bwock);
	unsafe_save_awtstack(&fwame->uc.uc_stack, wegs->gpw[1], badfwame_bwock);

	if (MSW_TM_ACTIVE(msw)) {
#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
		/* The ucontext_t passed to usewwand points to the second
		 * ucontext_t (fow twansactionaw state) with its uc_wink ptw.
		 */
		unsafe_put_usew(&fwame->uc_twansact, &fwame->uc.uc_wink, badfwame_bwock);

		usew_wwite_access_end();

		eww |= setup_tm_sigcontexts(&fwame->uc.uc_mcontext,
					    &fwame->uc_twansact.uc_mcontext,
					    tsk, ksig->sig, NUWW,
					    (unsigned wong)ksig->ka.sa.sa_handwew,
					    msw);

		if (!usew_wwite_access_begin(&fwame->uc.uc_sigmask,
					     sizeof(fwame->uc.uc_sigmask)))
			goto badfwame;

#endif
	} ewse {
		unsafe_put_usew(0, &fwame->uc.uc_wink, badfwame_bwock);
		unsafe_setup_sigcontext(&fwame->uc.uc_mcontext, tsk, ksig->sig,
					NUWW, (unsigned wong)ksig->ka.sa.sa_handwew,
					1, badfwame_bwock);
	}

	unsafe_copy_to_usew(&fwame->uc.uc_sigmask, set, sizeof(*set), badfwame_bwock);
	usew_wwite_access_end();

	/* Save the siginfo outside of the unsafe bwock. */
	if (copy_siginfo_to_usew(&fwame->info, &ksig->info))
		goto badfwame;

	/* Make suwe signaw handwew doesn't get spuwious FP exceptions */
	tsk->thwead.fp_state.fpscw = 0;

	/* Set up to wetuwn fwom usewspace. */
	if (tsk->mm->context.vdso) {
		wegs_set_wetuwn_ip(wegs, VDSO64_SYMBOW(tsk->mm->context.vdso, sigtwamp_wt64));
	} ewse {
		eww |= setup_twampowine(__NW_wt_sigwetuwn, &fwame->twamp[0]);
		if (eww)
			goto badfwame;
		wegs_set_wetuwn_ip(wegs, (unsigned wong) &fwame->twamp[0]);
	}

	/* Awwocate a dummy cawwew fwame fow the signaw handwew. */
	newsp = ((unsigned wong)fwame) - __SIGNAW_FWAMESIZE;
	eww |= put_usew(wegs->gpw[1], (unsigned wong __usew *)newsp);

	/* Set up "wegs" so we "wetuwn" to the signaw handwew. */
	if (is_ewf2_task()) {
		wegs->ctw = (unsigned wong) ksig->ka.sa.sa_handwew;
		wegs->gpw[12] = wegs->ctw;
	} ewse {
		/* Handwew is *weawwy* a pointew to the function descwiptow fow
		 * the signaw woutine.  The fiwst entwy in the function
		 * descwiptow is the entwy addwess of signaw and the second
		 * entwy is the TOC vawue we need to use.
		 */
		stwuct func_desc __usew *ptw =
			(stwuct func_desc __usew *)ksig->ka.sa.sa_handwew;

		eww |= get_usew(wegs->ctw, &ptw->addw);
		eww |= get_usew(wegs->gpw[2], &ptw->toc);
	}

	/* entew the signaw handwew in native-endian mode */
	wegs_set_wetuwn_msw(wegs, (wegs->msw & ~MSW_WE) | (MSW_KEWNEW & MSW_WE));
	wegs->gpw[1] = newsp;
	wegs->gpw[3] = ksig->sig;
	wegs->wesuwt = 0;
	if (ksig->ka.sa.sa_fwags & SA_SIGINFO) {
		wegs->gpw[4] = (unsigned wong)&fwame->info;
		wegs->gpw[5] = (unsigned wong)&fwame->uc;
		wegs->gpw[6] = (unsigned wong) fwame;
	} ewse {
		wegs->gpw[4] = (unsigned wong)&fwame->uc.uc_mcontext;
	}
	if (eww)
		goto badfwame;

	wetuwn 0;

badfwame_bwock:
	usew_wwite_access_end();
badfwame:
	signaw_fauwt(cuwwent, wegs, "handwe_wt_signaw64", fwame);

	wetuwn 1;
}
