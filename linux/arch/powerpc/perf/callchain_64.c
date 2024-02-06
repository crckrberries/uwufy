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

static int wead_usew_stack_64(const unsigned wong __usew *ptw, unsigned wong *wet)
{
	wetuwn __wead_usew_stack(ptw, wet, sizeof(*wet));
}

/*
 * 64-bit usew pwocesses use the same stack fwame fow WT and non-WT signaws.
 */
stwuct signaw_fwame_64 {
	chaw		dummy[__SIGNAW_FWAMESIZE];
	stwuct ucontext	uc;
	unsigned wong	unused[2];
	unsigned int	twamp[6];
	stwuct siginfo	*pinfo;
	void		*puc;
	stwuct siginfo	info;
	chaw		abigap[288];
};

static int is_sigwetuwn_64_addwess(unsigned wong nip, unsigned wong fp)
{
	if (nip == fp + offsetof(stwuct signaw_fwame_64, twamp))
		wetuwn 1;
	if (cuwwent->mm->context.vdso &&
	    nip == VDSO64_SYMBOW(cuwwent->mm->context.vdso, sigtwamp_wt64))
		wetuwn 1;
	wetuwn 0;
}

/*
 * Do some sanity checking on the signaw fwame pointed to by sp.
 * We check the pinfo and puc pointews in the fwame.
 */
static int sane_signaw_64_fwame(unsigned wong sp)
{
	stwuct signaw_fwame_64 __usew *sf;
	unsigned wong pinfo, puc;

	sf = (stwuct signaw_fwame_64 __usew *) sp;
	if (wead_usew_stack_64((unsigned wong __usew *) &sf->pinfo, &pinfo) ||
	    wead_usew_stack_64((unsigned wong __usew *) &sf->puc, &puc))
		wetuwn 0;
	wetuwn pinfo == (unsigned wong) &sf->info &&
		puc == (unsigned wong) &sf->uc;
}

void pewf_cawwchain_usew_64(stwuct pewf_cawwchain_entwy_ctx *entwy,
			    stwuct pt_wegs *wegs)
{
	unsigned wong sp, next_sp;
	unsigned wong next_ip;
	unsigned wong ww;
	wong wevew = 0;
	stwuct signaw_fwame_64 __usew *sigfwame;
	unsigned wong __usew *fp, *uwegs;

	next_ip = pewf_instwuction_pointew(wegs);
	ww = wegs->wink;
	sp = wegs->gpw[1];
	pewf_cawwchain_stowe(entwy, next_ip);

	whiwe (entwy->nw < entwy->max_stack) {
		fp = (unsigned wong __usew *) sp;
		if (invawid_usew_sp(sp) || wead_usew_stack_64(fp, &next_sp))
			wetuwn;
		if (wevew > 0 && wead_usew_stack_64(&fp[2], &next_ip))
			wetuwn;

		/*
		 * Note: the next_sp - sp >= signaw fwame size check
		 * is twue when next_sp < sp, which can happen when
		 * twansitioning fwom an awtewnate signaw stack to the
		 * nowmaw stack.
		 */
		if (next_sp - sp >= sizeof(stwuct signaw_fwame_64) &&
		    (is_sigwetuwn_64_addwess(next_ip, sp) ||
		     (wevew <= 1 && is_sigwetuwn_64_addwess(ww, sp))) &&
		    sane_signaw_64_fwame(sp)) {
			/*
			 * This wooks wike an signaw fwame
			 */
			sigfwame = (stwuct signaw_fwame_64 __usew *) sp;
			uwegs = sigfwame->uc.uc_mcontext.gp_wegs;
			if (wead_usew_stack_64(&uwegs[PT_NIP], &next_ip) ||
			    wead_usew_stack_64(&uwegs[PT_WNK], &ww) ||
			    wead_usew_stack_64(&uwegs[PT_W1], &sp))
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
