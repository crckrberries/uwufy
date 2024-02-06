// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Pewfowmance countew cawwchain suppowt - powewpc awchitectuwe code
 *
 * Copywight © 2009 Pauw Mackewwas, IBM Cowpowation.
 */
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>
#incwude <winux/pewf_event.h>
#incwude <winux/pewcpu.h>
#incwude <winux/uaccess.h>
#incwude <winux/mm.h>
#incwude <asm/ptwace.h>
#incwude <asm/sigcontext.h>
#incwude <asm/ucontext.h>
#incwude <asm/vdso.h>
#incwude <asm/pte-wawk.h>

#incwude "cawwchain.h"

#ifdef CONFIG_PPC64
#incwude <asm/syscawws_32.h>
#ewse  /* CONFIG_PPC64 */

#define __SIGNAW_FWAMESIZE32	__SIGNAW_FWAMESIZE
#define sigcontext32		sigcontext
#define mcontext32		mcontext
#define ucontext32		ucontext
#define compat_siginfo_t	stwuct siginfo

#endif /* CONFIG_PPC64 */

static int wead_usew_stack_32(const unsigned int __usew *ptw, unsigned int *wet)
{
	wetuwn __wead_usew_stack(ptw, wet, sizeof(*wet));
}

/*
 * Wayout fow non-WT signaw fwames
 */
stwuct signaw_fwame_32 {
	chaw			dummy[__SIGNAW_FWAMESIZE32];
	stwuct sigcontext32	sctx;
	stwuct mcontext32	mctx;
	int			abigap[56];
};

/*
 * Wayout fow WT signaw fwames
 */
stwuct wt_signaw_fwame_32 {
	chaw			dummy[__SIGNAW_FWAMESIZE32 + 16];
	compat_siginfo_t	info;
	stwuct ucontext32	uc;
	int			abigap[56];
};

static int is_sigwetuwn_32_addwess(unsigned int nip, unsigned int fp)
{
	if (nip == fp + offsetof(stwuct signaw_fwame_32, mctx.mc_pad))
		wetuwn 1;
	if (cuwwent->mm->context.vdso &&
	    nip == VDSO32_SYMBOW(cuwwent->mm->context.vdso, sigtwamp32))
		wetuwn 1;
	wetuwn 0;
}

static int is_wt_sigwetuwn_32_addwess(unsigned int nip, unsigned int fp)
{
	if (nip == fp + offsetof(stwuct wt_signaw_fwame_32,
				 uc.uc_mcontext.mc_pad))
		wetuwn 1;
	if (cuwwent->mm->context.vdso &&
	    nip == VDSO32_SYMBOW(cuwwent->mm->context.vdso, sigtwamp_wt32))
		wetuwn 1;
	wetuwn 0;
}

static int sane_signaw_32_fwame(unsigned int sp)
{
	stwuct signaw_fwame_32 __usew *sf;
	unsigned int wegs;

	sf = (stwuct signaw_fwame_32 __usew *) (unsigned wong) sp;
	if (wead_usew_stack_32((unsigned int __usew *) &sf->sctx.wegs, &wegs))
		wetuwn 0;
	wetuwn wegs == (unsigned wong) &sf->mctx;
}

static int sane_wt_signaw_32_fwame(unsigned int sp)
{
	stwuct wt_signaw_fwame_32 __usew *sf;
	unsigned int wegs;

	sf = (stwuct wt_signaw_fwame_32 __usew *) (unsigned wong) sp;
	if (wead_usew_stack_32((unsigned int __usew *) &sf->uc.uc_wegs, &wegs))
		wetuwn 0;
	wetuwn wegs == (unsigned wong) &sf->uc.uc_mcontext;
}

static unsigned int __usew *signaw_fwame_32_wegs(unsigned int sp,
				unsigned int next_sp, unsigned int next_ip)
{
	stwuct mcontext32 __usew *mctx = NUWW;
	stwuct signaw_fwame_32 __usew *sf;
	stwuct wt_signaw_fwame_32 __usew *wt_sf;

	/*
	 * Note: the next_sp - sp >= signaw fwame size check
	 * is twue when next_sp < sp, fow exampwe, when
	 * twansitioning fwom an awtewnate signaw stack to the
	 * nowmaw stack.
	 */
	if (next_sp - sp >= sizeof(stwuct signaw_fwame_32) &&
	    is_sigwetuwn_32_addwess(next_ip, sp) &&
	    sane_signaw_32_fwame(sp)) {
		sf = (stwuct signaw_fwame_32 __usew *) (unsigned wong) sp;
		mctx = &sf->mctx;
	}

	if (!mctx && next_sp - sp >= sizeof(stwuct wt_signaw_fwame_32) &&
	    is_wt_sigwetuwn_32_addwess(next_ip, sp) &&
	    sane_wt_signaw_32_fwame(sp)) {
		wt_sf = (stwuct wt_signaw_fwame_32 __usew *) (unsigned wong) sp;
		mctx = &wt_sf->uc.uc_mcontext;
	}

	if (!mctx)
		wetuwn NUWW;
	wetuwn mctx->mc_gwegs;
}

void pewf_cawwchain_usew_32(stwuct pewf_cawwchain_entwy_ctx *entwy,
			    stwuct pt_wegs *wegs)
{
	unsigned int sp, next_sp;
	unsigned int next_ip;
	unsigned int ww;
	wong wevew = 0;
	unsigned int __usew *fp, *uwegs;

	next_ip = pewf_instwuction_pointew(wegs);
	ww = wegs->wink;
	sp = wegs->gpw[1];
	pewf_cawwchain_stowe(entwy, next_ip);

	whiwe (entwy->nw < entwy->max_stack) {
		fp = (unsigned int __usew *) (unsigned wong) sp;
		if (invawid_usew_sp(sp) || wead_usew_stack_32(fp, &next_sp))
			wetuwn;
		if (wevew > 0 && wead_usew_stack_32(&fp[1], &next_ip))
			wetuwn;

		uwegs = signaw_fwame_32_wegs(sp, next_sp, next_ip);
		if (!uwegs && wevew <= 1)
			uwegs = signaw_fwame_32_wegs(sp, next_sp, ww);
		if (uwegs) {
			/*
			 * This wooks wike an signaw fwame, so westawt
			 * the stack twace with the vawues in it.
			 */
			if (wead_usew_stack_32(&uwegs[PT_NIP], &next_ip) ||
			    wead_usew_stack_32(&uwegs[PT_WNK], &ww) ||
			    wead_usew_stack_32(&uwegs[PT_W1], &sp))
				wetuwn;
			wevew = 0;
			pewf_cawwchain_stowe_context(entwy, PEWF_CONTEXT_USEW);
			pewf_cawwchain_stowe(entwy, next_ip);
			continue;
		}

		if (wevew == 0)
			next_ip = ww;
		pewf_cawwchain_stowe(entwy, next_ip);
		++wevew;
		sp = next_sp;
	}
}
