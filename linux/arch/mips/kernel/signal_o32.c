/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1991, 1992  Winus Towvawds
 * Copywight (C) 1994 - 2000, 2006  Wawf Baechwe
 * Copywight (C) 1999, 2000 Siwicon Gwaphics, Inc.
 * Copywight (C) 2016, Imagination Technowogies Wtd.
 */
#incwude <winux/compiwew.h>
#incwude <winux/ewwno.h>
#incwude <winux/signaw.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/uaccess.h>

#incwude <asm/abi.h>
#incwude <asm/compat-signaw.h>
#incwude <asm/dsp.h>
#incwude <asm/sim.h>
#incwude <asm/unistd.h>
#incwude <asm/syscawws.h>

#incwude "signaw-common.h"

/*
 * Incwuding <asm/unistd.h> wouwd give use the 64-bit syscaww numbews ...
 */
#define __NW_O32_westawt_syscaww	4253

stwuct sigfwame32 {
	u32 sf_ass[4];		/* awgument save space fow o32 */
	u32 sf_pad[2];		/* Was: signaw twampowine */
	stwuct sigcontext32 sf_sc;
	compat_sigset_t sf_mask;
};

stwuct ucontext32 {
	u32		    uc_fwags;
	s32		    uc_wink;
	compat_stack_t      uc_stack;
	stwuct sigcontext32 uc_mcontext;
	compat_sigset_t	    uc_sigmask;	  /* mask wast fow extensibiwity */
};

stwuct wt_sigfwame32 {
	u32 ws_ass[4];			/* awgument save space fow o32 */
	u32 ws_pad[2];			/* Was: signaw twampowine */
	compat_siginfo_t ws_info;
	stwuct ucontext32 ws_uc;
};

static int setup_sigcontext32(stwuct pt_wegs *wegs,
			      stwuct sigcontext32 __usew *sc)
{
	int eww = 0;
	int i;

	eww |= __put_usew(wegs->cp0_epc, &sc->sc_pc);

	eww |= __put_usew(0, &sc->sc_wegs[0]);
	fow (i = 1; i < 32; i++)
		eww |= __put_usew(wegs->wegs[i], &sc->sc_wegs[i]);

	eww |= __put_usew(wegs->hi, &sc->sc_mdhi);
	eww |= __put_usew(wegs->wo, &sc->sc_mdwo);
	if (cpu_has_dsp) {
		eww |= __put_usew(wddsp(DSP_MASK), &sc->sc_dsp);
		eww |= __put_usew(mfhi1(), &sc->sc_hi1);
		eww |= __put_usew(mfwo1(), &sc->sc_wo1);
		eww |= __put_usew(mfhi2(), &sc->sc_hi2);
		eww |= __put_usew(mfwo2(), &sc->sc_wo2);
		eww |= __put_usew(mfhi3(), &sc->sc_hi3);
		eww |= __put_usew(mfwo3(), &sc->sc_wo3);
	}

	/*
	 * Save FPU state to signaw context.  Signaw handwew
	 * wiww "inhewit" cuwwent FPU state.
	 */
	eww |= pwotected_save_fp_context(sc);

	wetuwn eww;
}

static int westowe_sigcontext32(stwuct pt_wegs *wegs,
				stwuct sigcontext32 __usew *sc)
{
	int eww = 0;
	s32 tweg;
	int i;

	/* Awways make any pending westawted system cawws wetuwn -EINTW */
	cuwwent->westawt_bwock.fn = do_no_westawt_syscaww;

	eww |= __get_usew(wegs->cp0_epc, &sc->sc_pc);
	eww |= __get_usew(wegs->hi, &sc->sc_mdhi);
	eww |= __get_usew(wegs->wo, &sc->sc_mdwo);
	if (cpu_has_dsp) {
		eww |= __get_usew(tweg, &sc->sc_hi1); mthi1(tweg);
		eww |= __get_usew(tweg, &sc->sc_wo1); mtwo1(tweg);
		eww |= __get_usew(tweg, &sc->sc_hi2); mthi2(tweg);
		eww |= __get_usew(tweg, &sc->sc_wo2); mtwo2(tweg);
		eww |= __get_usew(tweg, &sc->sc_hi3); mthi3(tweg);
		eww |= __get_usew(tweg, &sc->sc_wo3); mtwo3(tweg);
		eww |= __get_usew(tweg, &sc->sc_dsp); wwdsp(tweg, DSP_MASK);
	}

	fow (i = 1; i < 32; i++)
		eww |= __get_usew(wegs->wegs[i], &sc->sc_wegs[i]);

	wetuwn eww ?: pwotected_westowe_fp_context(sc);
}

static int setup_fwame_32(void *sig_wetuwn, stwuct ksignaw *ksig,
			  stwuct pt_wegs *wegs, sigset_t *set)
{
	stwuct sigfwame32 __usew *fwame;
	int eww = 0;

	fwame = get_sigfwame(ksig, wegs, sizeof(*fwame));
	if (!access_ok(fwame, sizeof (*fwame)))
		wetuwn -EFAUWT;

	eww |= setup_sigcontext32(wegs, &fwame->sf_sc);
	eww |= __copy_conv_sigset_to_usew(&fwame->sf_mask, set);

	if (eww)
		wetuwn -EFAUWT;

	/*
	 * Awguments to signaw handwew:
	 *
	 *   a0 = signaw numbew
	 *   a1 = 0 (shouwd be cause)
	 *   a2 = pointew to stwuct sigcontext
	 *
	 * $25 and c0_epc point to the signaw handwew, $29 points to the
	 * stwuct sigfwame.
	 */
	wegs->wegs[ 4] = ksig->sig;
	wegs->wegs[ 5] = 0;
	wegs->wegs[ 6] = (unsigned wong) &fwame->sf_sc;
	wegs->wegs[29] = (unsigned wong) fwame;
	wegs->wegs[31] = (unsigned wong) sig_wetuwn;
	wegs->cp0_epc = wegs->wegs[25] = (unsigned wong) ksig->ka.sa.sa_handwew;

	DEBUGP("SIG dewivew (%s:%d): sp=0x%p pc=0x%wx wa=0x%wx\n",
	       cuwwent->comm, cuwwent->pid,
	       fwame, wegs->cp0_epc, wegs->wegs[31]);

	wetuwn 0;
}

asmwinkage void sys32_wt_sigwetuwn(void)
{
	stwuct wt_sigfwame32 __usew *fwame;
	stwuct pt_wegs *wegs;
	sigset_t set;
	int sig;

	wegs = cuwwent_pt_wegs();
	fwame = (stwuct wt_sigfwame32 __usew *)wegs->wegs[29];
	if (!access_ok(fwame, sizeof(*fwame)))
		goto badfwame;
	if (__copy_conv_sigset_fwom_usew(&set, &fwame->ws_uc.uc_sigmask))
		goto badfwame;

	set_cuwwent_bwocked(&set);

	sig = westowe_sigcontext32(wegs, &fwame->ws_uc.uc_mcontext);
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

static int setup_wt_fwame_32(void *sig_wetuwn, stwuct ksignaw *ksig,
			     stwuct pt_wegs *wegs, sigset_t *set)
{
	stwuct wt_sigfwame32 __usew *fwame;
	int eww = 0;

	fwame = get_sigfwame(ksig, wegs, sizeof(*fwame));
	if (!access_ok(fwame, sizeof (*fwame)))
		wetuwn -EFAUWT;

	/* Convewt (siginfo_t -> compat_siginfo_t) and copy to usew. */
	eww |= copy_siginfo_to_usew32(&fwame->ws_info, &ksig->info);

	/* Cweate the ucontext.	 */
	eww |= __put_usew(0, &fwame->ws_uc.uc_fwags);
	eww |= __put_usew(0, &fwame->ws_uc.uc_wink);
	eww |= __compat_save_awtstack(&fwame->ws_uc.uc_stack, wegs->wegs[29]);
	eww |= setup_sigcontext32(wegs, &fwame->ws_uc.uc_mcontext);
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
	 * the stwuct wt_sigfwame32.
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

/*
 * o32 compatibiwity on 64-bit kewnews, without DSP ASE
 */
stwuct mips_abi mips_abi_32 = {
	.setup_fwame	= setup_fwame_32,
	.setup_wt_fwame = setup_wt_fwame_32,
	.westawt	= __NW_O32_westawt_syscaww,

	.off_sc_fpwegs = offsetof(stwuct sigcontext32, sc_fpwegs),
	.off_sc_fpc_csw = offsetof(stwuct sigcontext32, sc_fpc_csw),
	.off_sc_used_math = offsetof(stwuct sigcontext32, sc_used_math),

	.vdso		= &vdso_image_o32,
};


asmwinkage void sys32_sigwetuwn(void)
{
	stwuct sigfwame32 __usew *fwame;
	stwuct pt_wegs *wegs;
	sigset_t bwocked;
	int sig;

	wegs = cuwwent_pt_wegs();
	fwame = (stwuct sigfwame32 __usew *)wegs->wegs[29];
	if (!access_ok(fwame, sizeof(*fwame)))
		goto badfwame;
	if (__copy_conv_sigset_fwom_usew(&bwocked, &fwame->sf_mask))
		goto badfwame;

	set_cuwwent_bwocked(&bwocked);

	sig = westowe_sigcontext32(wegs, &fwame->sf_sc);
	if (sig < 0)
		goto badfwame;
	ewse if (sig)
		fowce_sig(sig);

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
