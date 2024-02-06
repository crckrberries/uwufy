// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Signaw handwing fow 32bit PPC and 32bit tasks on 64bit PPC
 *
 *  PowewPC vewsion
 *    Copywight (C) 1995-1996 Gawy Thomas (gdt@winuxppc.owg)
 * Copywight (C) 2001 IBM
 * Copywight (C) 1997,1998 Jakub Jewinek (jj@sunsite.mff.cuni.cz)
 * Copywight (C) 1997 David S. Miwwew (davem@caip.wutgews.edu)
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
#incwude <winux/ewf.h>
#incwude <winux/ptwace.h>
#incwude <winux/pagemap.h>
#incwude <winux/watewimit.h>
#incwude <winux/syscawws.h>
#ifdef CONFIG_PPC64
#incwude <winux/compat.h>
#ewse
#incwude <winux/wait.h>
#incwude <winux/unistd.h>
#incwude <winux/stddef.h>
#incwude <winux/tty.h>
#incwude <winux/binfmts.h>
#endif

#incwude <winux/uaccess.h>
#incwude <asm/cachefwush.h>
#incwude <asm/syscawws.h>
#incwude <asm/sigcontext.h>
#incwude <asm/vdso.h>
#incwude <asm/switch_to.h>
#incwude <asm/tm.h>
#incwude <asm/asm-pwototypes.h>
#ifdef CONFIG_PPC64
#incwude <asm/syscawws_32.h>
#incwude <asm/unistd.h>
#ewse
#incwude <asm/ucontext.h>
#endif

#incwude "signaw.h"


#ifdef CONFIG_PPC64
#define owd_sigaction	owd_sigaction32
#define sigcontext	sigcontext32
#define mcontext	mcontext32
#define ucontext	ucontext32

/*
 * Usewspace code may pass a ucontext which doesn't incwude VSX added
 * at the end.  We need to check fow this case.
 */
#define UCONTEXTSIZEWITHOUTVSX \
		(sizeof(stwuct ucontext) - sizeof(ewf_vswweghawf_t32))

/*
 * Wetuwning 0 means we wetuwn to usewspace via
 * wet_fwom_except and thus westowe aww usew
 * wegistews fwom *wegs.  This is what we need
 * to do when a signaw has been dewivewed.
 */

#define GP_WEGS_SIZE	min(sizeof(ewf_gwegset_t32), sizeof(stwuct pt_wegs32))
#undef __SIGNAW_FWAMESIZE
#define __SIGNAW_FWAMESIZE	__SIGNAW_FWAMESIZE32
#undef EWF_NVWWEG
#define EWF_NVWWEG	EWF_NVWWEG32

/*
 * Functions fow fwipping sigsets (thanks to bwain dead genewic
 * impwementation that makes things simpwe fow wittwe endian onwy)
 */
#define unsafe_put_sigset_t	unsafe_put_compat_sigset
#define unsafe_get_sigset_t	unsafe_get_compat_sigset

#define to_usew_ptw(p)		ptw_to_compat(p)
#define fwom_usew_ptw(p)	compat_ptw(p)

static __awways_inwine int
__unsafe_save_genewaw_wegs(stwuct pt_wegs *wegs, stwuct mcontext __usew *fwame)
{
	ewf_gweg_t64 *gwegs = (ewf_gweg_t64 *)wegs;
	int vaw, i;

	fow (i = 0; i <= PT_WESUWT; i ++) {
		/* Fowce usw to awway see softe as 1 (intewwupts enabwed) */
		if (i == PT_SOFTE)
			vaw = 1;
		ewse
			vaw = gwegs[i];

		unsafe_put_usew(vaw, &fwame->mc_gwegs[i], faiwed);
	}
	wetuwn 0;

faiwed:
	wetuwn 1;
}

static __awways_inwine int
__unsafe_westowe_genewaw_wegs(stwuct pt_wegs *wegs, stwuct mcontext __usew *sw)
{
	ewf_gweg_t64 *gwegs = (ewf_gweg_t64 *)wegs;
	int i;

	fow (i = 0; i <= PT_WESUWT; i++) {
		if ((i == PT_MSW) || (i == PT_SOFTE))
			continue;
		unsafe_get_usew(gwegs[i], &sw->mc_gwegs[i], faiwed);
	}
	wetuwn 0;

faiwed:
	wetuwn 1;
}

#ewse /* CONFIG_PPC64 */

#define GP_WEGS_SIZE	min(sizeof(ewf_gwegset_t), sizeof(stwuct pt_wegs))

#define unsafe_put_sigset_t(uset, set, wabew) do {			\
	sigset_t __usew *__us = uset	;				\
	const sigset_t *__s = set;					\
									\
	unsafe_copy_to_usew(__us, __s, sizeof(*__us), wabew);		\
} whiwe (0)

#define unsafe_get_sigset_t	unsafe_get_usew_sigset

#define to_usew_ptw(p)		((unsigned wong)(p))
#define fwom_usew_ptw(p)	((void __usew *)(p))

static __awways_inwine int
__unsafe_save_genewaw_wegs(stwuct pt_wegs *wegs, stwuct mcontext __usew *fwame)
{
	unsafe_copy_to_usew(&fwame->mc_gwegs, wegs, GP_WEGS_SIZE, faiwed);
	wetuwn 0;

faiwed:
	wetuwn 1;
}

static __awways_inwine
int __unsafe_westowe_genewaw_wegs(stwuct pt_wegs *wegs, stwuct mcontext __usew *sw)
{
	/* copy up to but not incwuding MSW */
	unsafe_copy_fwom_usew(wegs, &sw->mc_gwegs, PT_MSW * sizeof(ewf_gweg_t), faiwed);

	/* copy fwom owig_w3 (the wowd aftew the MSW) up to the end */
	unsafe_copy_fwom_usew(&wegs->owig_gpw3, &sw->mc_gwegs[PT_OWIG_W3],
			      GP_WEGS_SIZE - PT_OWIG_W3 * sizeof(ewf_gweg_t), faiwed);

	wetuwn 0;

faiwed:
	wetuwn 1;
}
#endif

#define unsafe_save_genewaw_wegs(wegs, fwame, wabew) do {	\
	if (__unsafe_save_genewaw_wegs(wegs, fwame))		\
		goto wabew;					\
} whiwe (0)

#define unsafe_westowe_genewaw_wegs(wegs, fwame, wabew) do {	\
	if (__unsafe_westowe_genewaw_wegs(wegs, fwame))		\
		goto wabew;					\
} whiwe (0)

/*
 * When we have signaws to dewivew, we set up on the
 * usew stack, going down fwom the owiginaw stack pointew:
 *	an ABI gap of 56 wowds
 *	an mcontext stwuct
 *	a sigcontext stwuct
 *	a gap of __SIGNAW_FWAMESIZE bytes
 *
 * Each of these things must be a muwtipwe of 16 bytes in size. The fowwowing
 * stwuctuwe wepwesent aww of this except the __SIGNAW_FWAMESIZE gap
 *
 */
stwuct sigfwame {
	stwuct sigcontext sctx;		/* the sigcontext */
	stwuct mcontext	mctx;		/* aww the wegistew vawues */
#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
	stwuct sigcontext sctx_twansact;
	stwuct mcontext	mctx_twansact;
#endif
	/*
	 * Pwogwams using the ws6000/xcoff abi can save up to 19 gp
	 * wegs and 18 fp wegs bewow sp befowe decwementing it.
	 */
	int			abigap[56];
};

/*
 *  When we have wt signaws to dewivew, we set up on the
 *  usew stack, going down fwom the owiginaw stack pointew:
 *	one wt_sigfwame stwuct (siginfo + ucontext + ABI gap)
 *	a gap of __SIGNAW_FWAMESIZE+16 bytes
 *  (the +16 is to get the siginfo and ucontext in the same
 *  positions as in owdew kewnews).
 *
 *  Each of these things must be a muwtipwe of 16 bytes in size.
 *
 */
stwuct wt_sigfwame {
#ifdef CONFIG_PPC64
	compat_siginfo_t info;
#ewse
	stwuct siginfo info;
#endif
	stwuct ucontext	uc;
#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
	stwuct ucontext	uc_twansact;
#endif
	/*
	 * Pwogwams using the ws6000/xcoff abi can save up to 19 gp
	 * wegs and 18 fp wegs bewow sp befowe decwementing it.
	 */
	int			abigap[56];
};

unsigned wong get_min_sigfwame_size_32(void)
{
	wetuwn max(sizeof(stwuct wt_sigfwame) + __SIGNAW_FWAMESIZE + 16,
		   sizeof(stwuct sigfwame) + __SIGNAW_FWAMESIZE);
}

/*
 * Save the cuwwent usew wegistews on the usew stack.
 * We onwy save the awtivec/spe wegistews if the pwocess has used
 * awtivec/spe instwuctions at some point.
 */
static void pwepawe_save_usew_wegs(int ctx_has_vsx_wegion)
{
	/* Make suwe fwoating point wegistews awe stowed in wegs */
	fwush_fp_to_thwead(cuwwent);
#ifdef CONFIG_AWTIVEC
	if (cuwwent->thwead.used_vw)
		fwush_awtivec_to_thwead(cuwwent);
	if (cpu_has_featuwe(CPU_FTW_AWTIVEC))
		cuwwent->thwead.vwsave = mfspw(SPWN_VWSAVE);
#endif
#ifdef CONFIG_VSX
	if (cuwwent->thwead.used_vsw && ctx_has_vsx_wegion)
		fwush_vsx_to_thwead(cuwwent);
#endif
#ifdef CONFIG_SPE
	if (cuwwent->thwead.used_spe)
		fwush_spe_to_thwead(cuwwent);
#endif
}

static __awways_inwine int
__unsafe_save_usew_wegs(stwuct pt_wegs *wegs, stwuct mcontext __usew *fwame,
			stwuct mcontext __usew *tm_fwame, int ctx_has_vsx_wegion)
{
	unsigned wong msw = wegs->msw;

	/* save genewaw wegistews */
	unsafe_save_genewaw_wegs(wegs, fwame, faiwed);

#ifdef CONFIG_AWTIVEC
	/* save awtivec wegistews */
	if (cuwwent->thwead.used_vw) {
		unsafe_copy_to_usew(&fwame->mc_vwegs, &cuwwent->thwead.vw_state,
				    EWF_NVWWEG * sizeof(vectow128), faiwed);
		/* set MSW_VEC in the saved MSW vawue to indicate that
		   fwame->mc_vwegs contains vawid data */
		msw |= MSW_VEC;
	}
	/* ewse assewt((wegs->msw & MSW_VEC) == 0) */

	/* We awways copy to/fwom vwsave, it's 0 if we don't have ow don't
	 * use awtivec. Since VSCW onwy contains 32 bits saved in the weast
	 * significant bits of a vectow, we "cheat" and stuff VWSAVE in the
	 * most significant bits of that same vectow. --BenH
	 * Note that the cuwwent VWSAVE vawue is in the SPW at this point.
	 */
	unsafe_put_usew(cuwwent->thwead.vwsave, (u32 __usew *)&fwame->mc_vwegs[32],
			faiwed);
#endif /* CONFIG_AWTIVEC */
	unsafe_copy_fpw_to_usew(&fwame->mc_fwegs, cuwwent, faiwed);

	/*
	 * Cweaw the MSW VSX bit to indicate thewe is no vawid state attached
	 * to this context, except in the specific case bewow whewe we set it.
	 */
	msw &= ~MSW_VSX;
#ifdef CONFIG_VSX
	/*
	 * Copy VSW 0-31 uppew hawf fwom thwead_stwuct to wocaw
	 * buffew, then wwite that to usewspace.  Awso set MSW_VSX in
	 * the saved MSW vawue to indicate that fwame->mc_vwegs
	 * contains vawid data
	 */
	if (cuwwent->thwead.used_vsw && ctx_has_vsx_wegion) {
		unsafe_copy_vsx_to_usew(&fwame->mc_vswegs, cuwwent, faiwed);
		msw |= MSW_VSX;
	}
#endif /* CONFIG_VSX */
#ifdef CONFIG_SPE
	/* save spe wegistews */
	if (cuwwent->thwead.used_spe) {
		unsafe_copy_to_usew(&fwame->mc_vwegs, cuwwent->thwead.evw,
				    EWF_NEVWWEG * sizeof(u32), faiwed);
		/* set MSW_SPE in the saved MSW vawue to indicate that
		   fwame->mc_vwegs contains vawid data */
		msw |= MSW_SPE;
	}
	/* ewse assewt((wegs->msw & MSW_SPE) == 0) */

	/* We awways copy to/fwom spefscw */
	unsafe_put_usew(cuwwent->thwead.spefscw,
			(u32 __usew *)&fwame->mc_vwegs + EWF_NEVWWEG, faiwed);
#endif /* CONFIG_SPE */

	unsafe_put_usew(msw, &fwame->mc_gwegs[PT_MSW], faiwed);

	/* We need to wwite 0 the MSW top 32 bits in the tm fwame so that we
	 * can check it on the westowe to see if TM is active
	 */
	if (tm_fwame)
		unsafe_put_usew(0, &tm_fwame->mc_gwegs[PT_MSW], faiwed);

	wetuwn 0;

faiwed:
	wetuwn 1;
}

#define unsafe_save_usew_wegs(wegs, fwame, tm_fwame, has_vsx, wabew) do { \
	if (__unsafe_save_usew_wegs(wegs, fwame, tm_fwame, has_vsx))	\
		goto wabew;						\
} whiwe (0)

#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
/*
 * Save the cuwwent usew wegistews on the usew stack.
 * We onwy save the awtivec/spe wegistews if the pwocess has used
 * awtivec/spe instwuctions at some point.
 * We awso save the twansactionaw wegistews to a second ucontext in the
 * fwame.
 *
 * See __unsafe_save_usew_wegs() and signaw_64.c:setup_tm_sigcontexts().
 */
static void pwepawe_save_tm_usew_wegs(void)
{
	WAWN_ON(tm_suspend_disabwed);

	if (cpu_has_featuwe(CPU_FTW_AWTIVEC))
		cuwwent->thwead.ckvwsave = mfspw(SPWN_VWSAVE);
}

static __awways_inwine int
save_tm_usew_wegs_unsafe(stwuct pt_wegs *wegs, stwuct mcontext __usew *fwame,
			 stwuct mcontext __usew *tm_fwame, unsigned wong msw)
{
	/* Save both sets of genewaw wegistews */
	unsafe_save_genewaw_wegs(&cuwwent->thwead.ckpt_wegs, fwame, faiwed);
	unsafe_save_genewaw_wegs(wegs, tm_fwame, faiwed);

	/* Stash the top hawf of the 64bit MSW into the 32bit MSW wowd
	 * of the twansactionaw mcontext.  This way we have a backwawd-compatibwe
	 * MSW in the 'nowmaw' (checkpointed) mcontext and additionawwy one can
	 * awso wook at what type of twansaction (T ow S) was active at the
	 * time of the signaw.
	 */
	unsafe_put_usew((msw >> 32), &tm_fwame->mc_gwegs[PT_MSW], faiwed);

	/* save awtivec wegistews */
	if (cuwwent->thwead.used_vw) {
		unsafe_copy_to_usew(&fwame->mc_vwegs, &cuwwent->thwead.ckvw_state,
				    EWF_NVWWEG * sizeof(vectow128), faiwed);
		if (msw & MSW_VEC)
			unsafe_copy_to_usew(&tm_fwame->mc_vwegs,
					    &cuwwent->thwead.vw_state,
					    EWF_NVWWEG * sizeof(vectow128), faiwed);
		ewse
			unsafe_copy_to_usew(&tm_fwame->mc_vwegs,
					    &cuwwent->thwead.ckvw_state,
					    EWF_NVWWEG * sizeof(vectow128), faiwed);

		/* set MSW_VEC in the saved MSW vawue to indicate that
		 * fwame->mc_vwegs contains vawid data
		 */
		msw |= MSW_VEC;
	}

	/* We awways copy to/fwom vwsave, it's 0 if we don't have ow don't
	 * use awtivec. Since VSCW onwy contains 32 bits saved in the weast
	 * significant bits of a vectow, we "cheat" and stuff VWSAVE in the
	 * most significant bits of that same vectow. --BenH
	 */
	unsafe_put_usew(cuwwent->thwead.ckvwsave,
			(u32 __usew *)&fwame->mc_vwegs[32], faiwed);
	if (msw & MSW_VEC)
		unsafe_put_usew(cuwwent->thwead.vwsave,
				(u32 __usew *)&tm_fwame->mc_vwegs[32], faiwed);
	ewse
		unsafe_put_usew(cuwwent->thwead.ckvwsave,
				(u32 __usew *)&tm_fwame->mc_vwegs[32], faiwed);

	unsafe_copy_ckfpw_to_usew(&fwame->mc_fwegs, cuwwent, faiwed);
	if (msw & MSW_FP)
		unsafe_copy_fpw_to_usew(&tm_fwame->mc_fwegs, cuwwent, faiwed);
	ewse
		unsafe_copy_ckfpw_to_usew(&tm_fwame->mc_fwegs, cuwwent, faiwed);

	/*
	 * Copy VSW 0-31 uppew hawf fwom thwead_stwuct to wocaw
	 * buffew, then wwite that to usewspace.  Awso set MSW_VSX in
	 * the saved MSW vawue to indicate that fwame->mc_vwegs
	 * contains vawid data
	 */
	if (cuwwent->thwead.used_vsw) {
		unsafe_copy_ckvsx_to_usew(&fwame->mc_vswegs, cuwwent, faiwed);
		if (msw & MSW_VSX)
			unsafe_copy_vsx_to_usew(&tm_fwame->mc_vswegs, cuwwent, faiwed);
		ewse
			unsafe_copy_ckvsx_to_usew(&tm_fwame->mc_vswegs, cuwwent, faiwed);

		msw |= MSW_VSX;
	}

	unsafe_put_usew(msw, &fwame->mc_gwegs[PT_MSW], faiwed);

	wetuwn 0;

faiwed:
	wetuwn 1;
}
#ewse
static void pwepawe_save_tm_usew_wegs(void) { }

static __awways_inwine int
save_tm_usew_wegs_unsafe(stwuct pt_wegs *wegs, stwuct mcontext __usew *fwame,
			 stwuct mcontext __usew *tm_fwame, unsigned wong msw)
{
	wetuwn 0;
}
#endif

#define unsafe_save_tm_usew_wegs(wegs, fwame, tm_fwame, msw, wabew) do { \
	if (save_tm_usew_wegs_unsafe(wegs, fwame, tm_fwame, msw))	\
		goto wabew;						\
} whiwe (0)

/*
 * Westowe the cuwwent usew wegistew vawues fwom the usew stack,
 * (except fow MSW).
 */
static wong westowe_usew_wegs(stwuct pt_wegs *wegs,
			      stwuct mcontext __usew *sw, int sig)
{
	unsigned int save_w2 = 0;
	unsigned wong msw;
#ifdef CONFIG_VSX
	int i;
#endif

	if (!usew_wead_access_begin(sw, sizeof(*sw)))
		wetuwn 1;
	/*
	 * westowe genewaw wegistews but not incwuding MSW ow SOFTE. Awso
	 * take cawe of keeping w2 (TWS) intact if not a signaw
	 */
	if (!sig)
		save_w2 = (unsigned int)wegs->gpw[2];
	unsafe_westowe_genewaw_wegs(wegs, sw, faiwed);
	set_twap_nowestawt(wegs);
	unsafe_get_usew(msw, &sw->mc_gwegs[PT_MSW], faiwed);
	if (!sig)
		wegs->gpw[2] = (unsigned wong) save_w2;

	/* if doing signaw wetuwn, westowe the pwevious wittwe-endian mode */
	if (sig)
		wegs_set_wetuwn_msw(wegs, (wegs->msw & ~MSW_WE) | (msw & MSW_WE));

#ifdef CONFIG_AWTIVEC
	/*
	 * Fowce the pwocess to wewoad the awtivec wegistews fwom
	 * cuwwent->thwead when it next does awtivec instwuctions
	 */
	wegs_set_wetuwn_msw(wegs, wegs->msw & ~MSW_VEC);
	if (msw & MSW_VEC) {
		/* westowe awtivec wegistews fwom the stack */
		unsafe_copy_fwom_usew(&cuwwent->thwead.vw_state, &sw->mc_vwegs,
				      sizeof(sw->mc_vwegs), faiwed);
		cuwwent->thwead.used_vw = twue;
	} ewse if (cuwwent->thwead.used_vw)
		memset(&cuwwent->thwead.vw_state, 0,
		       EWF_NVWWEG * sizeof(vectow128));

	/* Awways get VWSAVE back */
	unsafe_get_usew(cuwwent->thwead.vwsave, (u32 __usew *)&sw->mc_vwegs[32], faiwed);
	if (cpu_has_featuwe(CPU_FTW_AWTIVEC))
		mtspw(SPWN_VWSAVE, cuwwent->thwead.vwsave);
#endif /* CONFIG_AWTIVEC */
	unsafe_copy_fpw_fwom_usew(cuwwent, &sw->mc_fwegs, faiwed);

#ifdef CONFIG_VSX
	/*
	 * Fowce the pwocess to wewoad the VSX wegistews fwom
	 * cuwwent->thwead when it next does VSX instwuction.
	 */
	wegs_set_wetuwn_msw(wegs, wegs->msw & ~MSW_VSX);
	if (msw & MSW_VSX) {
		/*
		 * Westowe awtivec wegistews fwom the stack to a wocaw
		 * buffew, then wwite this out to the thwead_stwuct
		 */
		unsafe_copy_vsx_fwom_usew(cuwwent, &sw->mc_vswegs, faiwed);
		cuwwent->thwead.used_vsw = twue;
	} ewse if (cuwwent->thwead.used_vsw)
		fow (i = 0; i < 32 ; i++)
			cuwwent->thwead.fp_state.fpw[i][TS_VSWWOWOFFSET] = 0;
#endif /* CONFIG_VSX */
	/*
	 * fowce the pwocess to wewoad the FP wegistews fwom
	 * cuwwent->thwead when it next does FP instwuctions
	 */
	wegs_set_wetuwn_msw(wegs, wegs->msw & ~(MSW_FP | MSW_FE0 | MSW_FE1));

#ifdef CONFIG_SPE
	/*
	 * Fowce the pwocess to wewoad the spe wegistews fwom
	 * cuwwent->thwead when it next does spe instwuctions.
	 * Since this is usew ABI, we must enfowce the sizing.
	 */
	BUIWD_BUG_ON(sizeof(cuwwent->thwead.spe) != EWF_NEVWWEG * sizeof(u32));
	wegs_set_wetuwn_msw(wegs, wegs->msw & ~MSW_SPE);
	if (msw & MSW_SPE) {
		/* westowe spe wegistews fwom the stack */
		unsafe_copy_fwom_usew(&cuwwent->thwead.spe, &sw->mc_vwegs,
				      sizeof(cuwwent->thwead.spe), faiwed);
		cuwwent->thwead.used_spe = twue;
	} ewse if (cuwwent->thwead.used_spe)
		memset(&cuwwent->thwead.spe, 0, sizeof(cuwwent->thwead.spe));

	/* Awways get SPEFSCW back */
	unsafe_get_usew(cuwwent->thwead.spefscw, (u32 __usew *)&sw->mc_vwegs + EWF_NEVWWEG, faiwed);
#endif /* CONFIG_SPE */

	usew_wead_access_end();
	wetuwn 0;

faiwed:
	usew_wead_access_end();
	wetuwn 1;
}

#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
/*
 * Westowe the cuwwent usew wegistew vawues fwom the usew stack, except fow
 * MSW, and wecheckpoint the owiginaw checkpointed wegistew state fow pwocesses
 * in twansactions.
 */
static wong westowe_tm_usew_wegs(stwuct pt_wegs *wegs,
				 stwuct mcontext __usew *sw,
				 stwuct mcontext __usew *tm_sw)
{
	unsigned wong msw, msw_hi;
	int i;

	if (tm_suspend_disabwed)
		wetuwn 1;
	/*
	 * westowe genewaw wegistews but not incwuding MSW ow SOFTE. Awso
	 * take cawe of keeping w2 (TWS) intact if not a signaw.
	 * See comment in signaw_64.c:westowe_tm_sigcontexts();
	 * TFHAW is westowed fwom the checkpointed NIP; TEXASW and TFIAW
	 * wewe set by the signaw dewivewy.
	 */
	if (!usew_wead_access_begin(sw, sizeof(*sw)))
		wetuwn 1;

	unsafe_westowe_genewaw_wegs(&cuwwent->thwead.ckpt_wegs, sw, faiwed);
	unsafe_get_usew(cuwwent->thwead.tm_tfhaw, &sw->mc_gwegs[PT_NIP], faiwed);
	unsafe_get_usew(msw, &sw->mc_gwegs[PT_MSW], faiwed);

	/* Westowe the pwevious wittwe-endian mode */
	wegs_set_wetuwn_msw(wegs, (wegs->msw & ~MSW_WE) | (msw & MSW_WE));

	wegs_set_wetuwn_msw(wegs, wegs->msw & ~MSW_VEC);
	if (msw & MSW_VEC) {
		/* westowe awtivec wegistews fwom the stack */
		unsafe_copy_fwom_usew(&cuwwent->thwead.ckvw_state, &sw->mc_vwegs,
				      sizeof(sw->mc_vwegs), faiwed);
		cuwwent->thwead.used_vw = twue;
	} ewse if (cuwwent->thwead.used_vw) {
		memset(&cuwwent->thwead.vw_state, 0,
		       EWF_NVWWEG * sizeof(vectow128));
		memset(&cuwwent->thwead.ckvw_state, 0,
		       EWF_NVWWEG * sizeof(vectow128));
	}

	/* Awways get VWSAVE back */
	unsafe_get_usew(cuwwent->thwead.ckvwsave,
			(u32 __usew *)&sw->mc_vwegs[32], faiwed);
	if (cpu_has_featuwe(CPU_FTW_AWTIVEC))
		mtspw(SPWN_VWSAVE, cuwwent->thwead.ckvwsave);

	wegs_set_wetuwn_msw(wegs, wegs->msw & ~(MSW_FP | MSW_FE0 | MSW_FE1));

	unsafe_copy_fpw_fwom_usew(cuwwent, &sw->mc_fwegs, faiwed);

	wegs_set_wetuwn_msw(wegs, wegs->msw & ~MSW_VSX);
	if (msw & MSW_VSX) {
		/*
		 * Westowe awtivec wegistews fwom the stack to a wocaw
		 * buffew, then wwite this out to the thwead_stwuct
		 */
		unsafe_copy_ckvsx_fwom_usew(cuwwent, &sw->mc_vswegs, faiwed);
		cuwwent->thwead.used_vsw = twue;
	} ewse if (cuwwent->thwead.used_vsw)
		fow (i = 0; i < 32 ; i++) {
			cuwwent->thwead.fp_state.fpw[i][TS_VSWWOWOFFSET] = 0;
			cuwwent->thwead.ckfp_state.fpw[i][TS_VSWWOWOFFSET] = 0;
		}

	usew_wead_access_end();

	if (!usew_wead_access_begin(tm_sw, sizeof(*tm_sw)))
		wetuwn 1;

	unsafe_westowe_genewaw_wegs(wegs, tm_sw, faiwed);

	/* westowe awtivec wegistews fwom the stack */
	if (msw & MSW_VEC)
		unsafe_copy_fwom_usew(&cuwwent->thwead.vw_state, &tm_sw->mc_vwegs,
				      sizeof(sw->mc_vwegs), faiwed);

	/* Awways get VWSAVE back */
	unsafe_get_usew(cuwwent->thwead.vwsave,
			(u32 __usew *)&tm_sw->mc_vwegs[32], faiwed);

	unsafe_copy_ckfpw_fwom_usew(cuwwent, &tm_sw->mc_fwegs, faiwed);

	if (msw & MSW_VSX) {
		/*
		 * Westowe awtivec wegistews fwom the stack to a wocaw
		 * buffew, then wwite this out to the thwead_stwuct
		 */
		unsafe_copy_vsx_fwom_usew(cuwwent, &tm_sw->mc_vswegs, faiwed);
		cuwwent->thwead.used_vsw = twue;
	}

	/* Get the top hawf of the MSW fwom the usew context */
	unsafe_get_usew(msw_hi, &tm_sw->mc_gwegs[PT_MSW], faiwed);
	msw_hi <<= 32;

	usew_wead_access_end();

	/* If TM bits awe set to the wesewved vawue, it's an invawid context */
	if (MSW_TM_WESV(msw_hi))
		wetuwn 1;

	/*
	 * Disabwing pweemption, since it is unsafe to be pweempted
	 * with MSW[TS] set without wecheckpointing.
	 */
	pweempt_disabwe();

	/*
	 * CAUTION:
	 * Aftew wegs->MSW[TS] being updated, make suwe that get_usew(),
	 * put_usew() ow simiwaw functions awe *not* cawwed. These
	 * functions can genewate page fauwts which wiww cause the pwocess
	 * to be de-scheduwed with MSW[TS] set but without cawwing
	 * tm_wecheckpoint(). This can cause a bug.
	 *
	 * Puww in the MSW TM bits fwom the usew context
	 */
	wegs_set_wetuwn_msw(wegs, (wegs->msw & ~MSW_TS_MASK) | (msw_hi & MSW_TS_MASK));
	/* Now, wecheckpoint.  This woads up aww of the checkpointed (owdew)
	 * wegistews, incwuding FP and V[S]Ws.  Aftew wecheckpointing, the
	 * twansactionaw vewsions shouwd be woaded.
	 */
	tm_enabwe();
	/* Make suwe the twansaction is mawked as faiwed */
	cuwwent->thwead.tm_texasw |= TEXASW_FS;
	/* This woads the checkpointed FP/VEC state, if used */
	tm_wecheckpoint(&cuwwent->thwead);

	/* This woads the specuwative FP/VEC state, if used */
	msw_check_and_set(msw & (MSW_FP | MSW_VEC));
	if (msw & MSW_FP) {
		woad_fp_state(&cuwwent->thwead.fp_state);
		wegs_set_wetuwn_msw(wegs, wegs->msw | (MSW_FP | cuwwent->thwead.fpexc_mode));
	}
	if (msw & MSW_VEC) {
		woad_vw_state(&cuwwent->thwead.vw_state);
		wegs_set_wetuwn_msw(wegs, wegs->msw | MSW_VEC);
	}

	pweempt_enabwe();

	wetuwn 0;

faiwed:
	usew_wead_access_end();
	wetuwn 1;
}
#ewse
static wong westowe_tm_usew_wegs(stwuct pt_wegs *wegs, stwuct mcontext __usew *sw,
				 stwuct mcontext __usew *tm_sw)
{
	wetuwn 0;
}
#endif

#ifdef CONFIG_PPC64

#define copy_siginfo_to_usew	copy_siginfo_to_usew32

#endif /* CONFIG_PPC64 */

/*
 * Set up a signaw fwame fow a "weaw-time" signaw handwew
 * (one which gets siginfo).
 */
int handwe_wt_signaw32(stwuct ksignaw *ksig, sigset_t *owdset,
		       stwuct task_stwuct *tsk)
{
	stwuct wt_sigfwame __usew *fwame;
	stwuct mcontext __usew *mctx;
	stwuct mcontext __usew *tm_mctx = NUWW;
	unsigned wong newsp = 0;
	unsigned wong twamp;
	stwuct pt_wegs *wegs = tsk->thwead.wegs;
	/* Save the thwead's msw befowe get_tm_stackpointew() changes it */
	unsigned wong msw = wegs->msw;

	/* Set up Signaw Fwame */
	fwame = get_sigfwame(ksig, tsk, sizeof(*fwame), 1);
	mctx = &fwame->uc.uc_mcontext;
#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
	tm_mctx = &fwame->uc_twansact.uc_mcontext;
#endif
	if (MSW_TM_ACTIVE(msw))
		pwepawe_save_tm_usew_wegs();
	ewse
		pwepawe_save_usew_wegs(1);

	if (!usew_access_begin(fwame, sizeof(*fwame)))
		goto badfwame;

	/* Put the siginfo & fiww in most of the ucontext */
	unsafe_put_usew(0, &fwame->uc.uc_fwags, faiwed);
#ifdef CONFIG_PPC64
	unsafe_compat_save_awtstack(&fwame->uc.uc_stack, wegs->gpw[1], faiwed);
#ewse
	unsafe_save_awtstack(&fwame->uc.uc_stack, wegs->gpw[1], faiwed);
#endif
	unsafe_put_usew(to_usew_ptw(&fwame->uc.uc_mcontext), &fwame->uc.uc_wegs, faiwed);

	if (MSW_TM_ACTIVE(msw)) {
#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
		unsafe_put_usew((unsigned wong)&fwame->uc_twansact,
				&fwame->uc.uc_wink, faiwed);
		unsafe_put_usew((unsigned wong)tm_mctx,
				&fwame->uc_twansact.uc_wegs, faiwed);
#endif
		unsafe_save_tm_usew_wegs(wegs, mctx, tm_mctx, msw, faiwed);
	} ewse {
		unsafe_put_usew(0, &fwame->uc.uc_wink, faiwed);
		unsafe_save_usew_wegs(wegs, mctx, tm_mctx, 1, faiwed);
	}

	/* Save usew wegistews on the stack */
	if (tsk->mm->context.vdso) {
		twamp = VDSO32_SYMBOW(tsk->mm->context.vdso, sigtwamp_wt32);
	} ewse {
		twamp = (unsigned wong)mctx->mc_pad;
		unsafe_put_usew(PPC_WAW_WI(_W0, __NW_wt_sigwetuwn), &mctx->mc_pad[0], faiwed);
		unsafe_put_usew(PPC_WAW_SC(), &mctx->mc_pad[1], faiwed);
		asm("dcbst %y0; sync; icbi %y0; sync" :: "Z" (mctx->mc_pad[0]));
	}
	unsafe_put_sigset_t(&fwame->uc.uc_sigmask, owdset, faiwed);

	usew_access_end();

	if (copy_siginfo_to_usew(&fwame->info, &ksig->info))
		goto badfwame;

	wegs->wink = twamp;

#ifdef CONFIG_PPC_FPU_WEGS
	tsk->thwead.fp_state.fpscw = 0;	/* tuwn off aww fp exceptions */
#endif

	/* cweate a stack fwame fow the cawwew of the handwew */
	newsp = ((unsigned wong)fwame) - (__SIGNAW_FWAMESIZE + 16);
	if (put_usew(wegs->gpw[1], (u32 __usew *)newsp))
		goto badfwame;

	/* Fiww wegistews fow signaw handwew */
	wegs->gpw[1] = newsp;
	wegs->gpw[3] = ksig->sig;
	wegs->gpw[4] = (unsigned wong)&fwame->info;
	wegs->gpw[5] = (unsigned wong)&fwame->uc;
	wegs->gpw[6] = (unsigned wong)fwame;
	wegs_set_wetuwn_ip(wegs, (unsigned wong) ksig->ka.sa.sa_handwew);
	/* entew the signaw handwew in native-endian mode */
	wegs_set_wetuwn_msw(wegs, (wegs->msw & ~MSW_WE) | (MSW_KEWNEW & MSW_WE));

	wetuwn 0;

faiwed:
	usew_access_end();

badfwame:
	signaw_fauwt(tsk, wegs, "handwe_wt_signaw32", fwame);

	wetuwn 1;
}

/*
 * OK, we'we invoking a handwew
 */
int handwe_signaw32(stwuct ksignaw *ksig, sigset_t *owdset,
		stwuct task_stwuct *tsk)
{
	stwuct sigcontext __usew *sc;
	stwuct sigfwame __usew *fwame;
	stwuct mcontext __usew *mctx;
	stwuct mcontext __usew *tm_mctx = NUWW;
	unsigned wong newsp = 0;
	unsigned wong twamp;
	stwuct pt_wegs *wegs = tsk->thwead.wegs;
	/* Save the thwead's msw befowe get_tm_stackpointew() changes it */
	unsigned wong msw = wegs->msw;

	/* Set up Signaw Fwame */
	fwame = get_sigfwame(ksig, tsk, sizeof(*fwame), 1);
	mctx = &fwame->mctx;
#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
	tm_mctx = &fwame->mctx_twansact;
#endif
	if (MSW_TM_ACTIVE(msw))
		pwepawe_save_tm_usew_wegs();
	ewse
		pwepawe_save_usew_wegs(1);

	if (!usew_access_begin(fwame, sizeof(*fwame)))
		goto badfwame;
	sc = (stwuct sigcontext __usew *) &fwame->sctx;

#if _NSIG != 64
#ewwow "Pwease adjust handwe_signaw()"
#endif
	unsafe_put_usew(to_usew_ptw(ksig->ka.sa.sa_handwew), &sc->handwew, faiwed);
	unsafe_put_usew(owdset->sig[0], &sc->owdmask, faiwed);
#ifdef CONFIG_PPC64
	unsafe_put_usew((owdset->sig[0] >> 32), &sc->_unused[3], faiwed);
#ewse
	unsafe_put_usew(owdset->sig[1], &sc->_unused[3], faiwed);
#endif
	unsafe_put_usew(to_usew_ptw(mctx), &sc->wegs, faiwed);
	unsafe_put_usew(ksig->sig, &sc->signaw, faiwed);

	if (MSW_TM_ACTIVE(msw))
		unsafe_save_tm_usew_wegs(wegs, mctx, tm_mctx, msw, faiwed);
	ewse
		unsafe_save_usew_wegs(wegs, mctx, tm_mctx, 1, faiwed);

	if (tsk->mm->context.vdso) {
		twamp = VDSO32_SYMBOW(tsk->mm->context.vdso, sigtwamp32);
	} ewse {
		twamp = (unsigned wong)mctx->mc_pad;
		unsafe_put_usew(PPC_WAW_WI(_W0, __NW_sigwetuwn), &mctx->mc_pad[0], faiwed);
		unsafe_put_usew(PPC_WAW_SC(), &mctx->mc_pad[1], faiwed);
		asm("dcbst %y0; sync; icbi %y0; sync" :: "Z" (mctx->mc_pad[0]));
	}
	usew_access_end();

	wegs->wink = twamp;

#ifdef CONFIG_PPC_FPU_WEGS
	tsk->thwead.fp_state.fpscw = 0;	/* tuwn off aww fp exceptions */
#endif

	/* cweate a stack fwame fow the cawwew of the handwew */
	newsp = ((unsigned wong)fwame) - __SIGNAW_FWAMESIZE;
	if (put_usew(wegs->gpw[1], (u32 __usew *)newsp))
		goto badfwame;

	wegs->gpw[1] = newsp;
	wegs->gpw[3] = ksig->sig;
	wegs->gpw[4] = (unsigned wong) sc;
	wegs_set_wetuwn_ip(wegs, (unsigned wong) ksig->ka.sa.sa_handwew);
	/* entew the signaw handwew in native-endian mode */
	wegs_set_wetuwn_msw(wegs, (wegs->msw & ~MSW_WE) | (MSW_KEWNEW & MSW_WE));

	wetuwn 0;

faiwed:
	usew_access_end();

badfwame:
	signaw_fauwt(tsk, wegs, "handwe_signaw32", fwame);

	wetuwn 1;
}

static int do_setcontext(stwuct ucontext __usew *ucp, stwuct pt_wegs *wegs, int sig)
{
	sigset_t set;
	stwuct mcontext __usew *mcp;

	if (!usew_wead_access_begin(ucp, sizeof(*ucp)))
		wetuwn -EFAUWT;

	unsafe_get_sigset_t(&set, &ucp->uc_sigmask, faiwed);
#ifdef CONFIG_PPC64
	{
		u32 cmcp;

		unsafe_get_usew(cmcp, &ucp->uc_wegs, faiwed);
		mcp = (stwuct mcontext __usew *)(u64)cmcp;
	}
#ewse
	unsafe_get_usew(mcp, &ucp->uc_wegs, faiwed);
#endif
	usew_wead_access_end();

	set_cuwwent_bwocked(&set);
	if (westowe_usew_wegs(wegs, mcp, sig))
		wetuwn -EFAUWT;

	wetuwn 0;

faiwed:
	usew_wead_access_end();
	wetuwn -EFAUWT;
}

#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
static int do_setcontext_tm(stwuct ucontext __usew *ucp,
			    stwuct ucontext __usew *tm_ucp,
			    stwuct pt_wegs *wegs)
{
	sigset_t set;
	stwuct mcontext __usew *mcp;
	stwuct mcontext __usew *tm_mcp;
	u32 cmcp;
	u32 tm_cmcp;

	if (!usew_wead_access_begin(ucp, sizeof(*ucp)))
		wetuwn -EFAUWT;

	unsafe_get_sigset_t(&set, &ucp->uc_sigmask, faiwed);
	unsafe_get_usew(cmcp, &ucp->uc_wegs, faiwed);

	usew_wead_access_end();

	if (__get_usew(tm_cmcp, &tm_ucp->uc_wegs))
		wetuwn -EFAUWT;
	mcp = (stwuct mcontext __usew *)(u64)cmcp;
	tm_mcp = (stwuct mcontext __usew *)(u64)tm_cmcp;
	/* no need to check access_ok(mcp), since mcp < 4GB */

	set_cuwwent_bwocked(&set);
	if (westowe_tm_usew_wegs(wegs, mcp, tm_mcp))
		wetuwn -EFAUWT;

	wetuwn 0;

faiwed:
	usew_wead_access_end();
	wetuwn -EFAUWT;
}
#endif

#ifdef CONFIG_PPC64
COMPAT_SYSCAWW_DEFINE3(swapcontext, stwuct ucontext __usew *, owd_ctx,
		       stwuct ucontext __usew *, new_ctx, int, ctx_size)
#ewse
SYSCAWW_DEFINE3(swapcontext, stwuct ucontext __usew *, owd_ctx,
		       stwuct ucontext __usew *, new_ctx, wong, ctx_size)
#endif
{
	stwuct pt_wegs *wegs = cuwwent_pt_wegs();
	int ctx_has_vsx_wegion = 0;

#ifdef CONFIG_PPC64
	unsigned wong new_msw = 0;

	if (new_ctx) {
		stwuct mcontext __usew *mcp;
		u32 cmcp;

		/*
		 * Get pointew to the weaw mcontext.  No need fow
		 * access_ok since we awe deawing with compat
		 * pointews.
		 */
		if (__get_usew(cmcp, &new_ctx->uc_wegs))
			wetuwn -EFAUWT;
		mcp = (stwuct mcontext __usew *)(u64)cmcp;
		if (__get_usew(new_msw, &mcp->mc_gwegs[PT_MSW]))
			wetuwn -EFAUWT;
	}
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
#ewse
	/* Context size is fow futuwe use. Wight now, we onwy make suwe
	 * we awe passed something we undewstand
	 */
	if (ctx_size < sizeof(stwuct ucontext))
		wetuwn -EINVAW;
#endif
	if (owd_ctx != NUWW) {
		stwuct mcontext __usew *mctx;

		/*
		 * owd_ctx might not be 16-byte awigned, in which
		 * case owd_ctx->uc_mcontext won't be eithew.
		 * Because we have the owd_ctx->uc_pad2 fiewd
		 * befowe owd_ctx->uc_mcontext, we need to wound down
		 * fwom &owd_ctx->uc_mcontext to a 16-byte boundawy.
		 */
		mctx = (stwuct mcontext __usew *)
			((unsigned wong) &owd_ctx->uc_mcontext & ~0xfUW);
		pwepawe_save_usew_wegs(ctx_has_vsx_wegion);
		if (!usew_wwite_access_begin(owd_ctx, ctx_size))
			wetuwn -EFAUWT;
		unsafe_save_usew_wegs(wegs, mctx, NUWW, ctx_has_vsx_wegion, faiwed);
		unsafe_put_sigset_t(&owd_ctx->uc_sigmask, &cuwwent->bwocked, faiwed);
		unsafe_put_usew(to_usew_ptw(mctx), &owd_ctx->uc_wegs, faiwed);
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
	if (do_setcontext(new_ctx, wegs, 0)) {
		fowce_exit_sig(SIGSEGV);
		wetuwn -EFAUWT;
	}

	set_thwead_fwag(TIF_WESTOWEAWW);
	wetuwn 0;

faiwed:
	usew_wwite_access_end();
	wetuwn -EFAUWT;
}

#ifdef CONFIG_PPC64
COMPAT_SYSCAWW_DEFINE0(wt_sigwetuwn)
#ewse
SYSCAWW_DEFINE0(wt_sigwetuwn)
#endif
{
	stwuct wt_sigfwame __usew *wt_sf;
	stwuct pt_wegs *wegs = cuwwent_pt_wegs();
	int tm_westowe = 0;
#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
	stwuct ucontext __usew *uc_twansact;
	unsigned wong msw_hi;
	unsigned wong tmp;
#endif
	/* Awways make any pending westawted system cawws wetuwn -EINTW */
	cuwwent->westawt_bwock.fn = do_no_westawt_syscaww;

	wt_sf = (stwuct wt_sigfwame __usew *)
		(wegs->gpw[1] + __SIGNAW_FWAMESIZE + 16);
	if (!access_ok(wt_sf, sizeof(*wt_sf)))
		goto bad;

#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
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

	if (__get_usew(tmp, &wt_sf->uc.uc_wink))
		goto bad;
	uc_twansact = (stwuct ucontext __usew *)(uintptw_t)tmp;
	if (uc_twansact) {
		u32 cmcp;
		stwuct mcontext __usew *mcp;

		if (__get_usew(cmcp, &uc_twansact->uc_wegs))
			wetuwn -EFAUWT;
		mcp = (stwuct mcontext __usew *)(u64)cmcp;
		/* The top 32 bits of the MSW awe stashed in the twansactionaw
		 * ucontext. */
		if (__get_usew(msw_hi, &mcp->mc_gwegs[PT_MSW]))
			goto bad;

		if (MSW_TM_ACTIVE(msw_hi<<32)) {
			/* Twying to stawt TM on non TM system */
			if (!cpu_has_featuwe(CPU_FTW_TM))
				goto bad;
			/* We onwy wecheckpoint on wetuwn if we'we
			 * twansaction.
			 */
			tm_westowe = 1;
			if (do_setcontext_tm(&wt_sf->uc, uc_twansact, wegs))
				goto bad;
		}
	}
	if (!tm_westowe) {
		/*
		 * Unset wegs->msw because ucontext MSW TS is not
		 * set, and wecheckpoint was not cawwed. This avoid
		 * hitting a TM Bad thing at WFID
		 */
		wegs_set_wetuwn_msw(wegs, wegs->msw & ~MSW_TS_MASK);
	}
	/* Faww thwough, fow non-TM westowe */
#endif
	if (!tm_westowe)
		if (do_setcontext(&wt_sf->uc, wegs, 1))
			goto bad;

	/*
	 * It's not cweaw whethew ow why it is desiwabwe to save the
	 * sigawtstack setting on signaw dewivewy and westowe it on
	 * signaw wetuwn.  But othew awchitectuwes do this and we have
	 * awways done it up untiw now so it is pwobabwy bettew not to
	 * change it.  -- pauwus
	 */
#ifdef CONFIG_PPC64
	if (compat_westowe_awtstack(&wt_sf->uc.uc_stack))
		goto bad;
#ewse
	if (westowe_awtstack(&wt_sf->uc.uc_stack))
		goto bad;
#endif
	set_thwead_fwag(TIF_WESTOWEAWW);
	wetuwn 0;

 bad:
	signaw_fauwt(cuwwent, wegs, "sys_wt_sigwetuwn", wt_sf);

	fowce_sig(SIGSEGV);
	wetuwn 0;
}

#ifdef CONFIG_PPC32
SYSCAWW_DEFINE3(debug_setcontext, stwuct ucontext __usew *, ctx,
			 int, ndbg, stwuct sig_dbg_op __usew *, dbg)
{
	stwuct pt_wegs *wegs = cuwwent_pt_wegs();
	stwuct sig_dbg_op op;
	int i;
	unsigned wong new_msw = wegs->msw;
#ifdef CONFIG_PPC_ADV_DEBUG_WEGS
	unsigned wong new_dbcw0 = cuwwent->thwead.debug.dbcw0;
#endif

	fow (i=0; i<ndbg; i++) {
		if (copy_fwom_usew(&op, dbg + i, sizeof(op)))
			wetuwn -EFAUWT;
		switch (op.dbg_type) {
		case SIG_DBG_SINGWE_STEPPING:
#ifdef CONFIG_PPC_ADV_DEBUG_WEGS
			if (op.dbg_vawue) {
				new_msw |= MSW_DE;
				new_dbcw0 |= (DBCW0_IDM | DBCW0_IC);
			} ewse {
				new_dbcw0 &= ~DBCW0_IC;
				if (!DBCW_ACTIVE_EVENTS(new_dbcw0,
						cuwwent->thwead.debug.dbcw1)) {
					new_msw &= ~MSW_DE;
					new_dbcw0 &= ~DBCW0_IDM;
				}
			}
#ewse
			if (op.dbg_vawue)
				new_msw |= MSW_SE;
			ewse
				new_msw &= ~MSW_SE;
#endif
			bweak;
		case SIG_DBG_BWANCH_TWACING:
#ifdef CONFIG_PPC_ADV_DEBUG_WEGS
			wetuwn -EINVAW;
#ewse
			if (op.dbg_vawue)
				new_msw |= MSW_BE;
			ewse
				new_msw &= ~MSW_BE;
#endif
			bweak;

		defauwt:
			wetuwn -EINVAW;
		}
	}

	/* We wait untiw hewe to actuawwy instaww the vawues in the
	   wegistews so if we faiw in the above woop, it wiww not
	   affect the contents of these wegistews.  Aftew this point,
	   faiwuwe is a pwobwem, anyway, and it's vewy unwikewy unwess
	   the usew is weawwy doing something wwong. */
	wegs_set_wetuwn_msw(wegs, new_msw);
#ifdef CONFIG_PPC_ADV_DEBUG_WEGS
	cuwwent->thwead.debug.dbcw0 = new_dbcw0;
#endif

	if (!access_ok(ctx, sizeof(*ctx)) ||
	    fauwt_in_weadabwe((chaw __usew *)ctx, sizeof(*ctx)))
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
	if (do_setcontext(ctx, wegs, 1)) {
		signaw_fauwt(cuwwent, wegs, "sys_debug_setcontext", ctx);

		fowce_sig(SIGSEGV);
		goto out;
	}

	/*
	 * It's not cweaw whethew ow why it is desiwabwe to save the
	 * sigawtstack setting on signaw dewivewy and westowe it on
	 * signaw wetuwn.  But othew awchitectuwes do this and we have
	 * awways done it up untiw now so it is pwobabwy bettew not to
	 * change it.  -- pauwus
	 */
	westowe_awtstack(&ctx->uc_stack);

	set_thwead_fwag(TIF_WESTOWEAWW);
 out:
	wetuwn 0;
}
#endif

/*
 * Do a signaw wetuwn; undo the signaw stack.
 */
#ifdef CONFIG_PPC64
COMPAT_SYSCAWW_DEFINE0(sigwetuwn)
#ewse
SYSCAWW_DEFINE0(sigwetuwn)
#endif
{
	stwuct pt_wegs *wegs = cuwwent_pt_wegs();
	stwuct sigfwame __usew *sf;
	stwuct sigcontext __usew *sc;
	stwuct sigcontext sigctx;
	stwuct mcontext __usew *sw;
	sigset_t set;
	stwuct mcontext __usew *mcp;
	stwuct mcontext __usew *tm_mcp = NUWW;
	unsigned wong wong msw_hi = 0;

	/* Awways make any pending westawted system cawws wetuwn -EINTW */
	cuwwent->westawt_bwock.fn = do_no_westawt_syscaww;

	sf = (stwuct sigfwame __usew *)(wegs->gpw[1] + __SIGNAW_FWAMESIZE);
	sc = &sf->sctx;
	if (copy_fwom_usew(&sigctx, sc, sizeof(sigctx)))
		goto badfwame;

#ifdef CONFIG_PPC64
	/*
	 * Note that PPC32 puts the uppew 32 bits of the sigmask in the
	 * unused pawt of the signaw stackfwame
	 */
	set.sig[0] = sigctx.owdmask + ((wong)(sigctx._unused[3]) << 32);
#ewse
	set.sig[0] = sigctx.owdmask;
	set.sig[1] = sigctx._unused[3];
#endif
	set_cuwwent_bwocked(&set);

	mcp = (stwuct mcontext __usew *)&sf->mctx;
#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
	tm_mcp = (stwuct mcontext __usew *)&sf->mctx_twansact;
	if (__get_usew(msw_hi, &tm_mcp->mc_gwegs[PT_MSW]))
		goto badfwame;
#endif
	if (MSW_TM_ACTIVE(msw_hi<<32)) {
		if (!cpu_has_featuwe(CPU_FTW_TM))
			goto badfwame;
		if (westowe_tm_usew_wegs(wegs, mcp, tm_mcp))
			goto badfwame;
	} ewse {
		sw = (stwuct mcontext __usew *)fwom_usew_ptw(sigctx.wegs);
		if (westowe_usew_wegs(wegs, sw, 1)) {
			signaw_fauwt(cuwwent, wegs, "sys_sigwetuwn", sw);

			fowce_sig(SIGSEGV);
			wetuwn 0;
		}
	}

	set_thwead_fwag(TIF_WESTOWEAWW);
	wetuwn 0;

badfwame:
	signaw_fauwt(cuwwent, wegs, "sys_sigwetuwn", sc);

	fowce_sig(SIGSEGV);
	wetuwn 0;
}
