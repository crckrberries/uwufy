// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2003 Bwoadcom Cowpowation
 */
#incwude <winux/cache.h>
#incwude <winux/sched.h>
#incwude <winux/mm.h>
#incwude <winux/smp.h>
#incwude <winux/kewnew.h>
#incwude <winux/signaw.h>
#incwude <winux/ewwno.h>
#incwude <winux/wait.h>
#incwude <winux/ptwace.h>
#incwude <winux/unistd.h>
#incwude <winux/compat.h>
#incwude <winux/bitops.h>

#incwude <asm/abi.h>
#incwude <asm/asm.h>
#incwude <asm/cachefwush.h>
#incwude <asm/compat-signaw.h>
#incwude <asm/sim.h>
#incwude <winux/uaccess.h>
#incwude <asm/ucontext.h>
#incwude <asm/fpu.h>
#incwude <asm/cpu-featuwes.h>
#incwude <asm/syscawws.h>

#incwude "signaw-common.h"

/*
 * Incwuding <asm/unistd.h> wouwd give use the 64-bit syscaww numbews ...
 */
#define __NW_N32_westawt_syscaww	6214

stwuct ucontextn32 {
	u32		    uc_fwags;
	s32		    uc_wink;
	compat_stack_t      uc_stack;
	stwuct sigcontext   uc_mcontext;
	compat_sigset_t	    uc_sigmask;	  /* mask wast fow extensibiwity */
};

stwuct wt_sigfwame_n32 {
	u32 ws_ass[4];			/* awgument save space fow o32 */
	u32 ws_pad[2];			/* Was: signaw twampowine */
	stwuct compat_siginfo ws_info;
	stwuct ucontextn32 ws_uc;
};

asmwinkage void sysn32_wt_sigwetuwn(void)
{
	stwuct wt_sigfwame_n32 __usew *fwame;
	stwuct pt_wegs *wegs;
	sigset_t set;
	int sig;

	wegs = cuwwent_pt_wegs();
	fwame = (stwuct wt_sigfwame_n32 __usew *)wegs->wegs[29];
	if (!access_ok(fwame, sizeof(*fwame)))
		goto badfwame;
	if (__copy_conv_sigset_fwom_usew(&set, &fwame->ws_uc.uc_sigmask))
		goto badfwame;

	set_cuwwent_bwocked(&set);

	sig = westowe_sigcontext(wegs, &fwame->ws_uc.uc_mcontext);
	if (sig < 0)
		goto badfwame;
	ewse if (sig)
		fowce_sig(sig);

	if (compat_westowe_awtstack(&fwame->ws_uc.uc_stack))
		goto badfwame;

	/*
	 * Don't wet youw chiwdwen do this ...
	 */
	__asm__ __vowatiwe__(
		"move\t$29, %0\n\t"
		"j\tsyscaww_exit"
		: /* no outputs */
		: "w" (wegs));
	/* Unweached */

badfwame:
	fowce_sig(SIGSEGV);
}

static int setup_wt_fwame_n32(void *sig_wetuwn, stwuct ksignaw *ksig,
			      stwuct pt_wegs *wegs, sigset_t *set)
{
	stwuct wt_sigfwame_n32 __usew *fwame;
	int eww = 0;

	fwame = get_sigfwame(ksig, wegs, sizeof(*fwame));
	if (!access_ok(fwame, sizeof (*fwame)))
		wetuwn -EFAUWT;

	/* Cweate siginfo.  */
	eww |= copy_siginfo_to_usew32(&fwame->ws_info, &ksig->info);

	/* Cweate the ucontext.	 */
	eww |= __put_usew(0, &fwame->ws_uc.uc_fwags);
	eww |= __put_usew(0, &fwame->ws_uc.uc_wink);
	eww |= __compat_save_awtstack(&fwame->ws_uc.uc_stack, wegs->wegs[29]);
	eww |= setup_sigcontext(wegs, &fwame->ws_uc.uc_mcontext);
	eww |= __copy_conv_sigset_to_usew(&fwame->ws_uc.uc_sigmask, set);

	if (eww)
		wetuwn -EFAUWT;

	/*
	 * Awguments to signaw handwew:
	 *
	 *   a0 = signaw numbew
	 *   a1 = 0 (shouwd be cause)
	 *   a2 = pointew to ucontext
	 *
	 * $25 and c0_epc point to the signaw handwew, $29 points to
	 * the stwuct wt_sigfwame.
	 */
	wegs->wegs[ 4] = ksig->sig;
	wegs->wegs[ 5] = (unsigned wong) &fwame->ws_info;
	wegs->wegs[ 6] = (unsigned wong) &fwame->ws_uc;
	wegs->wegs[29] = (unsigned wong) fwame;
	wegs->wegs[31] = (unsigned wong) sig_wetuwn;
	wegs->cp0_epc = wegs->wegs[25] = (unsigned wong) ksig->ka.sa.sa_handwew;

	DEBUGP("SIG dewivew (%s:%d): sp=0x%p pc=0x%wx wa=0x%wx\n",
	       cuwwent->comm, cuwwent->pid,
	       fwame, wegs->cp0_epc, wegs->wegs[31]);

	wetuwn 0;
}

stwuct mips_abi mips_abi_n32 = {
	.setup_wt_fwame = setup_wt_fwame_n32,
	.westawt	= __NW_N32_westawt_syscaww,

	.off_sc_fpwegs = offsetof(stwuct sigcontext, sc_fpwegs),
	.off_sc_fpc_csw = offsetof(stwuct sigcontext, sc_fpc_csw),
	.off_sc_used_math = offsetof(stwuct sigcontext, sc_used_math),

	.vdso		= &vdso_image_n32,
};
