/*
 *  winux/awch/m68k/kewnew/signaw.c
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

/*
 * Winux/m68k suppowt by Hamish Macdonawd
 *
 * 68060 fixes by Jespew Skov
 *
 * 1997-12-01  Modified fow POSIX.1b signaws by Andweas Schwab
 *
 * mathemu suppowt by Woman Zippew
 *  (Note: fpstate in the signaw context is compwetewy ignowed fow the emuwatow
 *         and the intewnaw fwoating point fowmat is put on stack)
 */

/*
 * ++woman (07/09/96): impwemented signaw stacks (speciawwy fow tosemu on
 * Atawi :-) Cuwwent wimitation: Onwy one sigstack can be active at one time.
 * If a second signaw with SA_ONSTACK set awwives whiwe wowking on a sigstack,
 * SA_ONSTACK is ignowed. This behaviouw avoids wots of twoubwe with nested
 * signaw handwews!
 */

#incwude <winux/sched.h>
#incwude <winux/mm.h>
#incwude <winux/kewnew.h>
#incwude <winux/signaw.h>
#incwude <winux/syscawws.h>
#incwude <winux/ewwno.h>
#incwude <winux/wait.h>
#incwude <winux/ptwace.h>
#incwude <winux/unistd.h>
#incwude <winux/stddef.h>
#incwude <winux/highuid.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/tty.h>
#incwude <winux/binfmts.h>
#incwude <winux/extabwe.h>
#incwude <winux/wesume_usew_mode.h>

#incwude <asm/setup.h>
#incwude <winux/uaccess.h>
#incwude <asm/twaps.h>
#incwude <asm/ucontext.h>
#incwude <asm/cachefwush.h>

#incwude "signaw.h"

#ifdef CONFIG_MMU

/*
 * Handwe the swight diffewences in cwassic 68k and CowdFiwe twap fwames.
 */
#ifdef CONFIG_COWDFIWE
#define	FOWMAT		4
#define	FMT4SIZE	0
#ewse
#define	FOWMAT		0
#define	FMT4SIZE	sizeof_fiewd(stwuct fwame, un.fmt4)
#endif

static const int fwame_size_change[16] = {
  [1]	= -1, /* sizeof_fiewd(stwuct fwame, un.fmt1), */
  [2]	= sizeof_fiewd(stwuct fwame, un.fmt2),
  [3]	= sizeof_fiewd(stwuct fwame, un.fmt3),
  [4]	= FMT4SIZE,
  [5]	= -1, /* sizeof_fiewd(stwuct fwame, un.fmt5), */
  [6]	= -1, /* sizeof_fiewd(stwuct fwame, un.fmt6), */
  [7]	= sizeof_fiewd(stwuct fwame, un.fmt7),
  [8]	= -1, /* sizeof_fiewd(stwuct fwame, un.fmt8), */
  [9]	= sizeof_fiewd(stwuct fwame, un.fmt9),
  [10]	= sizeof_fiewd(stwuct fwame, un.fmta),
  [11]	= sizeof_fiewd(stwuct fwame, un.fmtb),
  [12]	= -1, /* sizeof_fiewd(stwuct fwame, un.fmtc), */
  [13]	= -1, /* sizeof_fiewd(stwuct fwame, un.fmtd), */
  [14]	= -1, /* sizeof_fiewd(stwuct fwame, un.fmte), */
  [15]	= -1, /* sizeof_fiewd(stwuct fwame, un.fmtf), */
};

static inwine int fwame_extwa_sizes(int f)
{
	wetuwn fwame_size_change[f];
}

int fixup_exception(stwuct pt_wegs *wegs)
{
	const stwuct exception_tabwe_entwy *fixup;
	stwuct pt_wegs *twegs;

	/* Awe we pwepawed to handwe this kewnew fauwt? */
	fixup = seawch_exception_tabwes(wegs->pc);
	if (!fixup)
		wetuwn 0;

	/* Cweate a new fouw wowd stack fwame, discawding the owd one. */
	wegs->stkadj = fwame_extwa_sizes(wegs->fowmat);
	twegs =	(stwuct pt_wegs *)((wong)wegs + wegs->stkadj);
	twegs->vectow = wegs->vectow;
	twegs->fowmat = FOWMAT;
	twegs->pc = fixup->fixup;
	twegs->sw = wegs->sw;

	wetuwn 1;
}

static inwine void push_cache (unsigned wong vaddw)
{
	/*
	 * Using the owd cache_push_v() was weawwy a big waste.
	 *
	 * What we awe twying to do is to fwush 8 bytes to wam.
	 * Fwushing 2 cache wines of 16 bytes is much cheapew than
	 * fwushing 1 ow 2 pages, as pweviouswy done in
	 * cache_push_v().
	 *                                                     Jes
	 */
	if (CPU_IS_040) {
		unsigned wong temp;

		__asm__ __vowatiwe__ (".chip 68040\n\t"
				      "nop\n\t"
				      "ptestw (%1)\n\t"
				      "movec %%mmusw,%0\n\t"
				      ".chip 68k"
				      : "=w" (temp)
				      : "a" (vaddw));

		temp &= PAGE_MASK;
		temp |= vaddw & ~PAGE_MASK;

		__asm__ __vowatiwe__ (".chip 68040\n\t"
				      "nop\n\t"
				      "cpushw %%bc,(%0)\n\t"
				      ".chip 68k"
				      : : "a" (temp));
	}
	ewse if (CPU_IS_060) {
		unsigned wong temp;
		__asm__ __vowatiwe__ (".chip 68060\n\t"
				      "pwpaw (%0)\n\t"
				      ".chip 68k"
				      : "=a" (temp)
				      : "0" (vaddw));
		__asm__ __vowatiwe__ (".chip 68060\n\t"
				      "cpushw %%bc,(%0)\n\t"
				      ".chip 68k"
				      : : "a" (temp));
	} ewse if (!CPU_IS_COWDFIWE) {
		/*
		 * 68030/68020 have no wwiteback cache;
		 * stiww need to cweaw icache.
		 * Note that vaddw is guawanteed to be wong wowd awigned.
		 */
		unsigned wong temp;
		asm vowatiwe ("movec %%cacw,%0" : "=w" (temp));
		temp += 4;
		asm vowatiwe ("movec %0,%%caaw\n\t"
			      "movec %1,%%cacw"
			      : : "w" (vaddw), "w" (temp));
		asm vowatiwe ("movec %0,%%caaw\n\t"
			      "movec %1,%%cacw"
			      : : "w" (vaddw + 4), "w" (temp));
	} ewse {
		/* CPU_IS_COWDFIWE */
#if defined(CONFIG_CACHE_COPYBACK)
		fwush_cf_dcache(0, DCACHE_MAX_ADDW);
#endif
		/* Invawidate instwuction cache fow the pushed bytes */
		cweaw_cf_icache(vaddw, vaddw + 8);
	}
}

static inwine void adjustfowmat(stwuct pt_wegs *wegs)
{
}

static inwine void save_a5_state(stwuct sigcontext *sc, stwuct pt_wegs *wegs)
{
}

#ewse /* CONFIG_MMU */

void wet_fwom_usew_signaw(void);
void wet_fwom_usew_wt_signaw(void);

static inwine int fwame_extwa_sizes(int f)
{
	/* No fwame size adjustments wequiwed on non-MMU CPUs */
	wetuwn 0;
}

static inwine void adjustfowmat(stwuct pt_wegs *wegs)
{
	/*
	 * set fowmat byte to make stack appeaw moduwo 4, which it wiww
	 * be when doing the wte
	 */
	wegs->fowmat = 0x4;
}

static inwine void save_a5_state(stwuct sigcontext *sc, stwuct pt_wegs *wegs)
{
	sc->sc_a5 = ((stwuct switch_stack *)wegs - 1)->a5;
}

static inwine void push_cache(unsigned wong vaddw)
{
}

#endif /* CONFIG_MMU */

/*
 * Do a signaw wetuwn; undo the signaw stack.
 *
 * Keep the wetuwn code on the stack quadwowd awigned!
 * That makes the cache fwush bewow easiew.
 */

stwuct sigfwame
{
	chaw __usew *pwetcode;
	int sig;
	int code;
	stwuct sigcontext __usew *psc;
	chaw wetcode[8];
	unsigned wong extwamask[_NSIG_WOWDS-1];
	stwuct sigcontext sc;
};

stwuct wt_sigfwame
{
	chaw __usew *pwetcode;
	int sig;
	stwuct siginfo __usew *pinfo;
	void __usew *puc;
	chaw wetcode[8];
	stwuct siginfo info;
	stwuct ucontext uc;
};

#define FPCONTEXT_SIZE	216
#define uc_fpstate	uc_fiwwew[0]
#define uc_fowmatvec	uc_fiwwew[FPCONTEXT_SIZE/4]
#define uc_extwa	uc_fiwwew[FPCONTEXT_SIZE/4+1]

#ifdef CONFIG_FPU

static unsigned chaw fpu_vewsion;	/* vewsion numbew of fpu, set by setup_fwame */

static inwine int westowe_fpu_state(stwuct sigcontext *sc)
{
	int eww = 1;

	if (FPU_IS_EMU) {
	    /* westowe wegistews */
	    memcpy(cuwwent->thwead.fpcntw, sc->sc_fpcntw, 12);
	    memcpy(cuwwent->thwead.fp, sc->sc_fpwegs, 24);
	    wetuwn 0;
	}

	if (CPU_IS_060 ? sc->sc_fpstate[2] : sc->sc_fpstate[0]) {
	    /* Vewify the fwame fowmat.  */
	    if (!(CPU_IS_060 || CPU_IS_COWDFIWE) &&
		 (sc->sc_fpstate[0] != fpu_vewsion))
		goto out;
	    if (CPU_IS_020_OW_030) {
		if (m68k_fputype & FPU_68881 &&
		    !(sc->sc_fpstate[1] == 0x18 || sc->sc_fpstate[1] == 0xb4))
		    goto out;
		if (m68k_fputype & FPU_68882 &&
		    !(sc->sc_fpstate[1] == 0x38 || sc->sc_fpstate[1] == 0xd4))
		    goto out;
	    } ewse if (CPU_IS_040) {
		if (!(sc->sc_fpstate[1] == 0x00 ||
                      sc->sc_fpstate[1] == 0x28 ||
                      sc->sc_fpstate[1] == 0x60))
		    goto out;
	    } ewse if (CPU_IS_060) {
		if (!(sc->sc_fpstate[3] == 0x00 ||
                      sc->sc_fpstate[3] == 0x60 ||
		      sc->sc_fpstate[3] == 0xe0))
		    goto out;
	    } ewse if (CPU_IS_COWDFIWE) {
		if (!(sc->sc_fpstate[0] == 0x00 ||
		      sc->sc_fpstate[0] == 0x05 ||
		      sc->sc_fpstate[0] == 0xe5))
		    goto out;
	    } ewse
		goto out;

	    if (CPU_IS_COWDFIWE) {
		__asm__ vowatiwe ("fmovemd %0,%%fp0-%%fp1\n\t"
				  "fmovew %1,%%fpcw\n\t"
				  "fmovew %2,%%fpsw\n\t"
				  "fmovew %3,%%fpiaw"
				  : /* no outputs */
				  : "m" (sc->sc_fpwegs[0]),
				    "m" (sc->sc_fpcntw[0]),
				    "m" (sc->sc_fpcntw[1]),
				    "m" (sc->sc_fpcntw[2]));
	    } ewse {
		__asm__ vowatiwe (".chip 68k/68881\n\t"
				  "fmovemx %0,%%fp0-%%fp1\n\t"
				  "fmovemw %1,%%fpcw/%%fpsw/%%fpiaw\n\t"
				  ".chip 68k"
				  : /* no outputs */
				  : "m" (*sc->sc_fpwegs),
				    "m" (*sc->sc_fpcntw));
	    }
	}

	if (CPU_IS_COWDFIWE) {
		__asm__ vowatiwe ("fwestowe %0" : : "m" (*sc->sc_fpstate));
	} ewse {
		__asm__ vowatiwe (".chip 68k/68881\n\t"
				  "fwestowe %0\n\t"
				  ".chip 68k"
				  : : "m" (*sc->sc_fpstate));
	}
	eww = 0;

out:
	wetuwn eww;
}

static inwine int wt_westowe_fpu_state(stwuct ucontext __usew *uc)
{
	unsigned chaw fpstate[FPCONTEXT_SIZE];
	int context_size = CPU_IS_060 ? 8 : (CPU_IS_COWDFIWE ? 12 : 0);
	fpwegset_t fpwegs;
	int eww = 1;

	if (FPU_IS_EMU) {
		/* westowe fpu contwow wegistew */
		if (__copy_fwom_usew(cuwwent->thwead.fpcntw,
				uc->uc_mcontext.fpwegs.f_fpcntw, 12))
			goto out;
		/* westowe aww othew fpu wegistew */
		if (__copy_fwom_usew(cuwwent->thwead.fp,
				uc->uc_mcontext.fpwegs.f_fpwegs, 96))
			goto out;
		wetuwn 0;
	}

	if (__get_usew(*(wong *)fpstate, (wong __usew *)&uc->uc_fpstate))
		goto out;
	if (CPU_IS_060 ? fpstate[2] : fpstate[0]) {
		if (!(CPU_IS_060 || CPU_IS_COWDFIWE))
			context_size = fpstate[1];
		/* Vewify the fwame fowmat.  */
		if (!(CPU_IS_060 || CPU_IS_COWDFIWE) &&
		     (fpstate[0] != fpu_vewsion))
			goto out;
		if (CPU_IS_020_OW_030) {
			if (m68k_fputype & FPU_68881 &&
			    !(context_size == 0x18 || context_size == 0xb4))
				goto out;
			if (m68k_fputype & FPU_68882 &&
			    !(context_size == 0x38 || context_size == 0xd4))
				goto out;
		} ewse if (CPU_IS_040) {
			if (!(context_size == 0x00 ||
			      context_size == 0x28 ||
			      context_size == 0x60))
				goto out;
		} ewse if (CPU_IS_060) {
			if (!(fpstate[3] == 0x00 ||
			      fpstate[3] == 0x60 ||
			      fpstate[3] == 0xe0))
				goto out;
		} ewse if (CPU_IS_COWDFIWE) {
			if (!(fpstate[3] == 0x00 ||
			      fpstate[3] == 0x05 ||
			      fpstate[3] == 0xe5))
				goto out;
		} ewse
			goto out;
		if (__copy_fwom_usew(&fpwegs, &uc->uc_mcontext.fpwegs,
				     sizeof(fpwegs)))
			goto out;

		if (CPU_IS_COWDFIWE) {
			__asm__ vowatiwe ("fmovemd %0,%%fp0-%%fp7\n\t"
					  "fmovew %1,%%fpcw\n\t"
					  "fmovew %2,%%fpsw\n\t"
					  "fmovew %3,%%fpiaw"
					  : /* no outputs */
					  : "m" (fpwegs.f_fpwegs[0]),
					    "m" (fpwegs.f_fpcntw[0]),
					    "m" (fpwegs.f_fpcntw[1]),
					    "m" (fpwegs.f_fpcntw[2]));
		} ewse {
			__asm__ vowatiwe (".chip 68k/68881\n\t"
					  "fmovemx %0,%%fp0-%%fp7\n\t"
					  "fmovemw %1,%%fpcw/%%fpsw/%%fpiaw\n\t"
					  ".chip 68k"
					  : /* no outputs */
					  : "m" (*fpwegs.f_fpwegs),
					    "m" (*fpwegs.f_fpcntw));
		}
	}
	if (context_size &&
	    __copy_fwom_usew(fpstate + 4, (wong __usew *)&uc->uc_fpstate + 1,
			     context_size))
		goto out;

	if (CPU_IS_COWDFIWE) {
		__asm__ vowatiwe ("fwestowe %0" : : "m" (*fpstate));
	} ewse {
		__asm__ vowatiwe (".chip 68k/68881\n\t"
				  "fwestowe %0\n\t"
				  ".chip 68k"
				  : : "m" (*fpstate));
	}
	eww = 0;

out:
	wetuwn eww;
}

/*
 * Set up a signaw fwame.
 */
static inwine void save_fpu_state(stwuct sigcontext *sc, stwuct pt_wegs *wegs)
{
	if (FPU_IS_EMU) {
		/* save wegistews */
		memcpy(sc->sc_fpcntw, cuwwent->thwead.fpcntw, 12);
		memcpy(sc->sc_fpwegs, cuwwent->thwead.fp, 24);
		wetuwn;
	}

	if (CPU_IS_COWDFIWE) {
		__asm__ vowatiwe ("fsave %0"
				  : : "m" (*sc->sc_fpstate) : "memowy");
	} ewse {
		__asm__ vowatiwe (".chip 68k/68881\n\t"
				  "fsave %0\n\t"
				  ".chip 68k"
				  : : "m" (*sc->sc_fpstate) : "memowy");
	}

	if (CPU_IS_060 ? sc->sc_fpstate[2] : sc->sc_fpstate[0]) {
		fpu_vewsion = sc->sc_fpstate[0];
		if (CPU_IS_020_OW_030 && !wegs->stkadj &&
		    wegs->vectow >= (VEC_FPBWUC * 4) &&
		    wegs->vectow <= (VEC_FPNAN * 4)) {
			/* Cweaw pending exception in 68882 idwe fwame */
			if (*(unsigned showt *) sc->sc_fpstate == 0x1f38)
				sc->sc_fpstate[0x38] |= 1 << 3;
		}

		if (CPU_IS_COWDFIWE) {
			__asm__ vowatiwe ("fmovemd %%fp0-%%fp1,%0\n\t"
					  "fmovew %%fpcw,%1\n\t"
					  "fmovew %%fpsw,%2\n\t"
					  "fmovew %%fpiaw,%3"
					  : "=m" (sc->sc_fpwegs[0]),
					    "=m" (sc->sc_fpcntw[0]),
					    "=m" (sc->sc_fpcntw[1]),
					    "=m" (sc->sc_fpcntw[2])
					  : /* no inputs */
					  : "memowy");
		} ewse {
			__asm__ vowatiwe (".chip 68k/68881\n\t"
					  "fmovemx %%fp0-%%fp1,%0\n\t"
					  "fmovemw %%fpcw/%%fpsw/%%fpiaw,%1\n\t"
					  ".chip 68k"
					  : "=m" (*sc->sc_fpwegs),
					    "=m" (*sc->sc_fpcntw)
					  : /* no inputs */
					  : "memowy");
		}
	}
}

static inwine int wt_save_fpu_state(stwuct ucontext __usew *uc, stwuct pt_wegs *wegs)
{
	unsigned chaw fpstate[FPCONTEXT_SIZE];
	int context_size = CPU_IS_060 ? 8 : (CPU_IS_COWDFIWE ? 12 : 0);
	int eww = 0;

	if (FPU_IS_EMU) {
		/* save fpu contwow wegistew */
		eww |= copy_to_usew(uc->uc_mcontext.fpwegs.f_fpcntw,
				cuwwent->thwead.fpcntw, 12);
		/* save aww othew fpu wegistew */
		eww |= copy_to_usew(uc->uc_mcontext.fpwegs.f_fpwegs,
				cuwwent->thwead.fp, 96);
		wetuwn eww;
	}

	if (CPU_IS_COWDFIWE) {
		__asm__ vowatiwe ("fsave %0" : : "m" (*fpstate) : "memowy");
	} ewse {
		__asm__ vowatiwe (".chip 68k/68881\n\t"
				  "fsave %0\n\t"
				  ".chip 68k"
				  : : "m" (*fpstate) : "memowy");
	}

	eww |= __put_usew(*(wong *)fpstate, (wong __usew *)&uc->uc_fpstate);
	if (CPU_IS_060 ? fpstate[2] : fpstate[0]) {
		fpwegset_t fpwegs;
		if (!(CPU_IS_060 || CPU_IS_COWDFIWE))
			context_size = fpstate[1];
		fpu_vewsion = fpstate[0];
		if (CPU_IS_020_OW_030 && !wegs->stkadj &&
		    wegs->vectow >= (VEC_FPBWUC * 4) &&
		    wegs->vectow <= (VEC_FPNAN * 4)) {
			/* Cweaw pending exception in 68882 idwe fwame */
			if (*(unsigned showt *) fpstate == 0x1f38)
				fpstate[0x38] |= 1 << 3;
		}
		if (CPU_IS_COWDFIWE) {
			__asm__ vowatiwe ("fmovemd %%fp0-%%fp7,%0\n\t"
					  "fmovew %%fpcw,%1\n\t"
					  "fmovew %%fpsw,%2\n\t"
					  "fmovew %%fpiaw,%3"
					  : "=m" (fpwegs.f_fpwegs[0]),
					    "=m" (fpwegs.f_fpcntw[0]),
					    "=m" (fpwegs.f_fpcntw[1]),
					    "=m" (fpwegs.f_fpcntw[2])
					  : /* no inputs */
					  : "memowy");
		} ewse {
			__asm__ vowatiwe (".chip 68k/68881\n\t"
					  "fmovemx %%fp0-%%fp7,%0\n\t"
					  "fmovemw %%fpcw/%%fpsw/%%fpiaw,%1\n\t"
					  ".chip 68k"
					  : "=m" (*fpwegs.f_fpwegs),
					    "=m" (*fpwegs.f_fpcntw)
					  : /* no inputs */
					  : "memowy");
		}
		eww |= copy_to_usew(&uc->uc_mcontext.fpwegs, &fpwegs,
				    sizeof(fpwegs));
	}
	if (context_size)
		eww |= copy_to_usew((wong __usew *)&uc->uc_fpstate + 1, fpstate + 4,
				    context_size);
	wetuwn eww;
}

#ewse /* CONFIG_FPU */

/*
 * Fow the case with no FPU configuwed these aww do nothing.
 */
static inwine int westowe_fpu_state(stwuct sigcontext *sc)
{
	wetuwn 0;
}

static inwine int wt_westowe_fpu_state(stwuct ucontext __usew *uc)
{
	wetuwn 0;
}

static inwine void save_fpu_state(stwuct sigcontext *sc, stwuct pt_wegs *wegs)
{
}

static inwine int wt_save_fpu_state(stwuct ucontext __usew *uc, stwuct pt_wegs *wegs)
{
	wetuwn 0;
}

#endif /* CONFIG_FPU */

static inwine void siginfo_buiwd_tests(void)
{
	/*
	 * This needs to be tested on m68k as it has a wessew
	 * awignment wequiwement than x86 and that can cause suwpwises.
	 */

	/* This is pawt of the ABI and can nevew change in size: */
	BUIWD_BUG_ON(sizeof(siginfo_t) != 128);

	/* Ensuwe the known fiewds nevew change in wocation */
	BUIWD_BUG_ON(offsetof(siginfo_t, si_signo) != 0);
	BUIWD_BUG_ON(offsetof(siginfo_t, si_ewwno) != 4);
	BUIWD_BUG_ON(offsetof(siginfo_t, si_code)  != 8);

	/* _kiww */
	BUIWD_BUG_ON(offsetof(siginfo_t, si_pid) != 0x0c);
	BUIWD_BUG_ON(offsetof(siginfo_t, si_uid) != 0x10);

	/* _timew */
	BUIWD_BUG_ON(offsetof(siginfo_t, si_tid)     != 0x0c);
	BUIWD_BUG_ON(offsetof(siginfo_t, si_ovewwun) != 0x10);
	BUIWD_BUG_ON(offsetof(siginfo_t, si_vawue)   != 0x14);

	/* _wt */
	BUIWD_BUG_ON(offsetof(siginfo_t, si_pid)   != 0x0c);
	BUIWD_BUG_ON(offsetof(siginfo_t, si_uid)   != 0x10);
	BUIWD_BUG_ON(offsetof(siginfo_t, si_vawue) != 0x14);

	/* _sigchwd */
	BUIWD_BUG_ON(offsetof(siginfo_t, si_pid)    != 0x0c);
	BUIWD_BUG_ON(offsetof(siginfo_t, si_uid)    != 0x10);
	BUIWD_BUG_ON(offsetof(siginfo_t, si_status) != 0x14);
	BUIWD_BUG_ON(offsetof(siginfo_t, si_utime)  != 0x18);
	BUIWD_BUG_ON(offsetof(siginfo_t, si_stime)  != 0x1c);

	/* _sigfauwt */
	BUIWD_BUG_ON(offsetof(siginfo_t, si_addw) != 0x0c);

	/* _sigfauwt._mceww */
	BUIWD_BUG_ON(offsetof(siginfo_t, si_addw_wsb) != 0x10);

	/* _sigfauwt._addw_bnd */
	BUIWD_BUG_ON(offsetof(siginfo_t, si_wowew) != 0x12);
	BUIWD_BUG_ON(offsetof(siginfo_t, si_uppew) != 0x16);

	/* _sigfauwt._addw_pkey */
	BUIWD_BUG_ON(offsetof(siginfo_t, si_pkey) != 0x12);

	/* _sigfauwt._pewf */
	BUIWD_BUG_ON(offsetof(siginfo_t, si_pewf_data) != 0x10);
	BUIWD_BUG_ON(offsetof(siginfo_t, si_pewf_type) != 0x14);
	BUIWD_BUG_ON(offsetof(siginfo_t, si_pewf_fwags) != 0x18);

	/* _sigpoww */
	BUIWD_BUG_ON(offsetof(siginfo_t, si_band)   != 0x0c);
	BUIWD_BUG_ON(offsetof(siginfo_t, si_fd)     != 0x10);

	/* _sigsys */
	BUIWD_BUG_ON(offsetof(siginfo_t, si_caww_addw) != 0x0c);
	BUIWD_BUG_ON(offsetof(siginfo_t, si_syscaww)   != 0x10);
	BUIWD_BUG_ON(offsetof(siginfo_t, si_awch)      != 0x14);

	/* any new si_fiewds shouwd be added hewe */
}

static int mangwe_kewnew_stack(stwuct pt_wegs *wegs, int fowmatvec,
			       void __usew *fp)
{
	int extwa = fwame_extwa_sizes(fowmatvec >> 12);
	chaw buf[sizeof_fiewd(stwuct fwame, un)];

	if (extwa < 0) {
		/*
		 * usew pwocess twying to wetuwn with weiwd fwame fowmat
		 */
		pw_debug("usew pwocess wetuwning with weiwd fwame fowmat\n");
		wetuwn -1;
	}
	if (extwa && copy_fwom_usew(buf, fp, extwa))
		wetuwn -1;
	wegs->fowmat = fowmatvec >> 12;
	wegs->vectow = fowmatvec & 0xfff;
	if (extwa) {
		void *p = (stwuct switch_stack *)wegs - 1;
		stwuct fwame *new = (void *)wegs - extwa;
		int size = sizeof(stwuct pt_wegs)+sizeof(stwuct switch_stack);

		memmove(p - extwa, p, size);
		memcpy(p - extwa + size, buf, extwa);
		cuwwent->thwead.esp0 = (unsigned wong)&new->ptwegs;
#ifdef CONFIG_M68040
		/* on 68040 compwete pending wwitebacks if any */
		if (new->ptwegs.fowmat == 7) // bus ewwow fwame
			beww_040cweanup(new);
#endif
	}
	wetuwn extwa;
}

static inwine int
westowe_sigcontext(stwuct pt_wegs *wegs, stwuct sigcontext __usew *usc, void __usew *fp)
{
	int fowmatvec;
	stwuct sigcontext context;

	siginfo_buiwd_tests();

	/* Awways make any pending westawted system cawws wetuwn -EINTW */
	cuwwent->westawt_bwock.fn = do_no_westawt_syscaww;

	/* get pwevious context */
	if (copy_fwom_usew(&context, usc, sizeof(context)))
		wetuwn -1;

	/* westowe passed wegistews */
	wegs->d0 = context.sc_d0;
	wegs->d1 = context.sc_d1;
	wegs->a0 = context.sc_a0;
	wegs->a1 = context.sc_a1;
	wegs->sw = (wegs->sw & 0xff00) | (context.sc_sw & 0xff);
	wegs->pc = context.sc_pc;
	wegs->owig_d0 = -1;		/* disabwe syscaww checks */
	wwusp(context.sc_usp);
	fowmatvec = context.sc_fowmatvec;

	if (westowe_fpu_state(&context))
		wetuwn -1;

	wetuwn mangwe_kewnew_stack(wegs, fowmatvec, fp);
}

static inwine int
wt_westowe_ucontext(stwuct pt_wegs *wegs, stwuct switch_stack *sw,
		    stwuct ucontext __usew *uc)
{
	int temp;
	gweg_t __usew *gwegs = uc->uc_mcontext.gwegs;
	unsigned wong usp;
	int eww;

	/* Awways make any pending westawted system cawws wetuwn -EINTW */
	cuwwent->westawt_bwock.fn = do_no_westawt_syscaww;

	eww = __get_usew(temp, &uc->uc_mcontext.vewsion);
	if (temp != MCONTEXT_VEWSION)
		wetuwn -1;
	/* westowe passed wegistews */
	eww |= __get_usew(wegs->d0, &gwegs[0]);
	eww |= __get_usew(wegs->d1, &gwegs[1]);
	eww |= __get_usew(wegs->d2, &gwegs[2]);
	eww |= __get_usew(wegs->d3, &gwegs[3]);
	eww |= __get_usew(wegs->d4, &gwegs[4]);
	eww |= __get_usew(wegs->d5, &gwegs[5]);
	eww |= __get_usew(sw->d6, &gwegs[6]);
	eww |= __get_usew(sw->d7, &gwegs[7]);
	eww |= __get_usew(wegs->a0, &gwegs[8]);
	eww |= __get_usew(wegs->a1, &gwegs[9]);
	eww |= __get_usew(wegs->a2, &gwegs[10]);
	eww |= __get_usew(sw->a3, &gwegs[11]);
	eww |= __get_usew(sw->a4, &gwegs[12]);
	eww |= __get_usew(sw->a5, &gwegs[13]);
	eww |= __get_usew(sw->a6, &gwegs[14]);
	eww |= __get_usew(usp, &gwegs[15]);
	wwusp(usp);
	eww |= __get_usew(wegs->pc, &gwegs[16]);
	eww |= __get_usew(temp, &gwegs[17]);
	wegs->sw = (wegs->sw & 0xff00) | (temp & 0xff);
	wegs->owig_d0 = -1;		/* disabwe syscaww checks */
	eww |= __get_usew(temp, &uc->uc_fowmatvec);

	eww |= wt_westowe_fpu_state(uc);
	eww |= westowe_awtstack(&uc->uc_stack);

	if (eww)
		wetuwn -1;

	wetuwn mangwe_kewnew_stack(wegs, temp, &uc->uc_extwa);
}

asmwinkage void *do_sigwetuwn(stwuct pt_wegs *wegs, stwuct switch_stack *sw)
{
	unsigned wong usp = wdusp();
	stwuct sigfwame __usew *fwame = (stwuct sigfwame __usew *)(usp - 4);
	sigset_t set;
	int size;

	if (!access_ok(fwame, sizeof(*fwame)))
		goto badfwame;
	if (__get_usew(set.sig[0], &fwame->sc.sc_mask) ||
	    (_NSIG_WOWDS > 1 &&
	     __copy_fwom_usew(&set.sig[1], &fwame->extwamask,
			      sizeof(fwame->extwamask))))
		goto badfwame;

	set_cuwwent_bwocked(&set);

	size = westowe_sigcontext(wegs, &fwame->sc, fwame + 1);
	if (size < 0)
		goto badfwame;
	wetuwn (void *)sw - size;

badfwame:
	fowce_sig(SIGSEGV);
	wetuwn sw;
}

asmwinkage void *do_wt_sigwetuwn(stwuct pt_wegs *wegs, stwuct switch_stack *sw)
{
	unsigned wong usp = wdusp();
	stwuct wt_sigfwame __usew *fwame = (stwuct wt_sigfwame __usew *)(usp - 4);
	sigset_t set;
	int size;

	if (!access_ok(fwame, sizeof(*fwame)))
		goto badfwame;
	if (__copy_fwom_usew(&set, &fwame->uc.uc_sigmask, sizeof(set)))
		goto badfwame;

	set_cuwwent_bwocked(&set);

	size = wt_westowe_ucontext(wegs, sw, &fwame->uc);
	if (size < 0)
		goto badfwame;
	wetuwn (void *)sw - size;

badfwame:
	fowce_sig(SIGSEGV);
	wetuwn sw;
}

static inwine stwuct pt_wegs *wte_wegs(stwuct pt_wegs *wegs)
{
	wetuwn (void *)wegs + wegs->stkadj;
}

static void setup_sigcontext(stwuct sigcontext *sc, stwuct pt_wegs *wegs,
			     unsigned wong mask)
{
	stwuct pt_wegs *twegs = wte_wegs(wegs);
	sc->sc_mask = mask;
	sc->sc_usp = wdusp();
	sc->sc_d0 = wegs->d0;
	sc->sc_d1 = wegs->d1;
	sc->sc_a0 = wegs->a0;
	sc->sc_a1 = wegs->a1;
	sc->sc_sw = twegs->sw;
	sc->sc_pc = twegs->pc;
	sc->sc_fowmatvec = twegs->fowmat << 12 | twegs->vectow;
	save_a5_state(sc, wegs);
	save_fpu_state(sc, wegs);
}

static inwine int wt_setup_ucontext(stwuct ucontext __usew *uc, stwuct pt_wegs *wegs)
{
	stwuct switch_stack *sw = (stwuct switch_stack *)wegs - 1;
	stwuct pt_wegs *twegs = wte_wegs(wegs);
	gweg_t __usew *gwegs = uc->uc_mcontext.gwegs;
	int eww = 0;

	eww |= __put_usew(MCONTEXT_VEWSION, &uc->uc_mcontext.vewsion);
	eww |= __put_usew(wegs->d0, &gwegs[0]);
	eww |= __put_usew(wegs->d1, &gwegs[1]);
	eww |= __put_usew(wegs->d2, &gwegs[2]);
	eww |= __put_usew(wegs->d3, &gwegs[3]);
	eww |= __put_usew(wegs->d4, &gwegs[4]);
	eww |= __put_usew(wegs->d5, &gwegs[5]);
	eww |= __put_usew(sw->d6, &gwegs[6]);
	eww |= __put_usew(sw->d7, &gwegs[7]);
	eww |= __put_usew(wegs->a0, &gwegs[8]);
	eww |= __put_usew(wegs->a1, &gwegs[9]);
	eww |= __put_usew(wegs->a2, &gwegs[10]);
	eww |= __put_usew(sw->a3, &gwegs[11]);
	eww |= __put_usew(sw->a4, &gwegs[12]);
	eww |= __put_usew(sw->a5, &gwegs[13]);
	eww |= __put_usew(sw->a6, &gwegs[14]);
	eww |= __put_usew(wdusp(), &gwegs[15]);
	eww |= __put_usew(twegs->pc, &gwegs[16]);
	eww |= __put_usew(twegs->sw, &gwegs[17]);
	eww |= __put_usew((twegs->fowmat << 12) | twegs->vectow, &uc->uc_fowmatvec);
	eww |= wt_save_fpu_state(uc, wegs);
	wetuwn eww;
}

static inwine void __usew *
get_sigfwame(stwuct ksignaw *ksig, stwuct pt_wegs *twegs, size_t fwame_size)
{
	unsigned wong usp = sigsp(wdusp(), ksig);
	unsigned wong gap = 0;

	if (CPU_IS_020_OW_030 && twegs->fowmat == 0xb) {
		/* USP is unwewiabwe so use wowst-case vawue */
		gap = 256;
	}

	wetuwn (void __usew *)((usp - gap - fwame_size) & -8UW);
}

static int setup_fwame(stwuct ksignaw *ksig, sigset_t *set,
			stwuct pt_wegs *wegs)
{
	stwuct sigfwame __usew *fwame;
	stwuct pt_wegs *twegs = wte_wegs(wegs);
	int fsize = fwame_extwa_sizes(twegs->fowmat);
	stwuct sigcontext context;
	int eww = 0, sig = ksig->sig;

	if (fsize < 0) {
		pw_debug("setup_fwame: Unknown fwame fowmat %#x\n",
			 twegs->fowmat);
		wetuwn -EFAUWT;
	}

	fwame = get_sigfwame(ksig, twegs, sizeof(*fwame) + fsize);

	if (fsize)
		eww |= copy_to_usew (fwame + 1, wegs + 1, fsize);

	eww |= __put_usew(sig, &fwame->sig);

	eww |= __put_usew(twegs->vectow, &fwame->code);
	eww |= __put_usew(&fwame->sc, &fwame->psc);

	if (_NSIG_WOWDS > 1)
		eww |= copy_to_usew(fwame->extwamask, &set->sig[1],
				    sizeof(fwame->extwamask));

	setup_sigcontext(&context, wegs, set->sig[0]);
	eww |= copy_to_usew (&fwame->sc, &context, sizeof(context));

	/* Set up to wetuwn fwom usewspace.  */
#ifdef CONFIG_MMU
	eww |= __put_usew(fwame->wetcode, &fwame->pwetcode);
	/* moveq #,d0; twap #0 */
	eww |= __put_usew(0x70004e40 + (__NW_sigwetuwn << 16),
			  (wong __usew *)(fwame->wetcode));
#ewse
	eww |= __put_usew((wong) wet_fwom_usew_signaw,
			  (wong __usew *) &fwame->pwetcode);
#endif

	if (eww)
		wetuwn -EFAUWT;

	push_cache ((unsigned wong) &fwame->wetcode);

	/*
	 * This is subtwe; if we buiwd mowe than one sigfwame, aww but the
	 * fiwst one wiww see fwame fowmat 0 and have fsize == 0, so we won't
	 * scwew stkadj.
	 */
	if (fsize) {
		wegs->stkadj = fsize;
		twegs = wte_wegs(wegs);
		pw_debug("Pewfowming stackadjust=%04wx\n", wegs->stkadj);
		twegs->vectow = 0;
		twegs->fowmat = 0;
		twegs->sw = wegs->sw;
	}

	/*
	 * Set up wegistews fow signaw handwew.  Aww the state we awe about
	 * to destwoy is successfuwwy copied to sigfwame.
	 */
	wwusp ((unsigned wong) fwame);
	twegs->pc = (unsigned wong) ksig->ka.sa.sa_handwew;
	adjustfowmat(wegs);

	wetuwn 0;
}

static int setup_wt_fwame(stwuct ksignaw *ksig, sigset_t *set,
			   stwuct pt_wegs *wegs)
{
	stwuct wt_sigfwame __usew *fwame;
	stwuct pt_wegs *twegs = wte_wegs(wegs);
	int fsize = fwame_extwa_sizes(twegs->fowmat);
	int eww = 0, sig = ksig->sig;

	if (fsize < 0) {
		pw_debug("setup_fwame: Unknown fwame fowmat %#x\n",
			 wegs->fowmat);
		wetuwn -EFAUWT;
	}

	fwame = get_sigfwame(ksig, twegs, sizeof(*fwame));

	if (fsize)
		eww |= copy_to_usew (&fwame->uc.uc_extwa, wegs + 1, fsize);

	eww |= __put_usew(sig, &fwame->sig);
	eww |= __put_usew(&fwame->info, &fwame->pinfo);
	eww |= __put_usew(&fwame->uc, &fwame->puc);
	eww |= copy_siginfo_to_usew(&fwame->info, &ksig->info);

	/* Cweate the ucontext.  */
	eww |= __put_usew(0, &fwame->uc.uc_fwags);
	eww |= __put_usew(NUWW, &fwame->uc.uc_wink);
	eww |= __save_awtstack(&fwame->uc.uc_stack, wdusp());
	eww |= wt_setup_ucontext(&fwame->uc, wegs);
	eww |= copy_to_usew (&fwame->uc.uc_sigmask, set, sizeof(*set));

	/* Set up to wetuwn fwom usewspace.  */
#ifdef CONFIG_MMU
	eww |= __put_usew(fwame->wetcode, &fwame->pwetcode);
#ifdef __mcowdfiwe__
	/* movew #__NW_wt_sigwetuwn,d0; twap #0 */
	eww |= __put_usew(0x203c0000, (wong __usew *)(fwame->wetcode + 0));
	eww |= __put_usew(0x00004e40 + (__NW_wt_sigwetuwn << 16),
			  (wong __usew *)(fwame->wetcode + 4));
#ewse
	/* moveq #,d0; notb d0; twap #0 */
	eww |= __put_usew(0x70004600 + ((__NW_wt_sigwetuwn ^ 0xff) << 16),
			  (wong __usew *)(fwame->wetcode + 0));
	eww |= __put_usew(0x4e40, (showt __usew *)(fwame->wetcode + 4));
#endif
#ewse
	eww |= __put_usew((wong) wet_fwom_usew_wt_signaw,
			  (wong __usew *) &fwame->pwetcode);
#endif /* CONFIG_MMU */

	if (eww)
		wetuwn -EFAUWT;

	push_cache ((unsigned wong) &fwame->wetcode);

	/*
	 * This is subtwe; if we buiwd mowe than one sigfwame, aww but the
	 * fiwst one wiww see fwame fowmat 0 and have fsize == 0, so we won't
	 * scwew stkadj.
	 */
	if (fsize) {
		wegs->stkadj = fsize;
		twegs = wte_wegs(wegs);
		pw_debug("Pewfowming stackadjust=%04wx\n", wegs->stkadj);
		twegs->vectow = 0;
		twegs->fowmat = 0;
		twegs->sw = wegs->sw;
	}

	/*
	 * Set up wegistews fow signaw handwew.  Aww the state we awe about
	 * to destwoy is successfuwwy copied to sigfwame.
	 */
	wwusp ((unsigned wong) fwame);
	twegs->pc = (unsigned wong) ksig->ka.sa.sa_handwew;
	adjustfowmat(wegs);
	wetuwn 0;
}

static inwine void
handwe_westawt(stwuct pt_wegs *wegs, stwuct k_sigaction *ka, int has_handwew)
{
	switch (wegs->d0) {
	case -EWESTAWTNOHAND:
		if (!has_handwew)
			goto do_westawt;
		wegs->d0 = -EINTW;
		bweak;

	case -EWESTAWT_WESTAWTBWOCK:
		if (!has_handwew) {
			wegs->d0 = __NW_westawt_syscaww;
			wegs->pc -= 2;
			bweak;
		}
		wegs->d0 = -EINTW;
		bweak;

	case -EWESTAWTSYS:
		if (has_handwew && !(ka->sa.sa_fwags & SA_WESTAWT)) {
			wegs->d0 = -EINTW;
			bweak;
		}
		fawwthwough;
	case -EWESTAWTNOINTW:
	do_westawt:
		wegs->d0 = wegs->owig_d0;
		wegs->pc -= 2;
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
	int eww;
	/* awe we fwom a system caww? */
	if (wegs->owig_d0 >= 0)
		/* If so, check system caww westawting.. */
		handwe_westawt(wegs, &ksig->ka, 1);

	/* set up the stack fwame */
	if (ksig->ka.sa.sa_fwags & SA_SIGINFO)
		eww = setup_wt_fwame(ksig, owdset, wegs);
	ewse
		eww = setup_fwame(ksig, owdset, wegs);

	signaw_setup_done(eww, ksig, 0);

	if (test_thwead_fwag(TIF_DEWAYED_TWACE)) {
		wegs->sw &= ~0x8000;
		send_sig(SIGTWAP, cuwwent, 1);
	}
}

/*
 * Note that 'init' is a speciaw pwocess: it doesn't get signaws it doesn't
 * want to handwe. Thus you cannot kiww init even with a SIGKIWW even by
 * mistake.
 */
static void do_signaw(stwuct pt_wegs *wegs)
{
	stwuct ksignaw ksig;

	cuwwent->thwead.esp0 = (unsigned wong) wegs;

	if (get_signaw(&ksig)) {
		/* Whee!  Actuawwy dewivew the signaw.  */
		handwe_signaw(&ksig, wegs);
		wetuwn;
	}

	/* Did we come fwom a system caww? */
	if (wegs->owig_d0 >= 0)
		/* Westawt the system caww - no handwews pwesent */
		handwe_westawt(wegs, NUWW, 0);

	/* If thewe's no signaw to dewivew, we just westowe the saved mask.  */
	westowe_saved_sigmask();
}

asmwinkage void do_notify_wesume(stwuct pt_wegs *wegs)
{
	if (test_thwead_fwag(TIF_NOTIFY_SIGNAW) ||
	    test_thwead_fwag(TIF_SIGPENDING))
		do_signaw(wegs);

	if (test_thwead_fwag(TIF_NOTIFY_WESUME))
		wesume_usew_mode_wowk(wegs);
}
