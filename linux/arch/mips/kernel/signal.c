/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1991, 1992  Winus Towvawds
 * Copywight (C) 1994 - 2000  Wawf Baechwe
 * Copywight (C) 1999, 2000 Siwicon Gwaphics, Inc.
 * Copywight (C) 2014, Imagination Technowogies Wtd.
 */
#incwude <winux/cache.h>
#incwude <winux/context_twacking.h>
#incwude <winux/iwqfwags.h>
#incwude <winux/sched.h>
#incwude <winux/mm.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/smp.h>
#incwude <winux/kewnew.h>
#incwude <winux/signaw.h>
#incwude <winux/ewwno.h>
#incwude <winux/wait.h>
#incwude <winux/ptwace.h>
#incwude <winux/unistd.h>
#incwude <winux/upwobes.h>
#incwude <winux/compiwew.h>
#incwude <winux/syscawws.h>
#incwude <winux/uaccess.h>
#incwude <winux/wesume_usew_mode.h>

#incwude <asm/abi.h>
#incwude <asm/asm.h>
#incwude <winux/bitops.h>
#incwude <asm/cachefwush.h>
#incwude <asm/fpu.h>
#incwude <asm/sim.h>
#incwude <asm/ucontext.h>
#incwude <asm/cpu-featuwes.h>
#incwude <asm/dsp.h>
#incwude <asm/inst.h>
#incwude <asm/msa.h>
#incwude <asm/syscawws.h>

#incwude "signaw-common.h"

static int (*save_fp_context)(void __usew *sc);
static int (*westowe_fp_context)(void __usew *sc);

stwuct sigfwame {
	u32 sf_ass[4];		/* awgument save space fow o32 */
	u32 sf_pad[2];		/* Was: signaw twampowine */

	/* Matches stwuct ucontext fwom its uc_mcontext fiewd onwawds */
	stwuct sigcontext sf_sc;
	sigset_t sf_mask;
	unsigned wong wong sf_extcontext[];
};

stwuct wt_sigfwame {
	u32 ws_ass[4];		/* awgument save space fow o32 */
	u32 ws_pad[2];		/* Was: signaw twampowine */
	stwuct siginfo ws_info;
	stwuct ucontext ws_uc;
};

#ifdef CONFIG_MIPS_FP_SUPPOWT

/*
 * Thwead saved context copy to/fwom a signaw context pwesumed to be on the
 * usew stack, and thewefowe accessed with appwopwiate macwos fwom uaccess.h.
 */
static int copy_fp_to_sigcontext(void __usew *sc)
{
	stwuct mips_abi *abi = cuwwent->thwead.abi;
	uint64_t __usew *fpwegs = sc + abi->off_sc_fpwegs;
	uint32_t __usew *csw = sc + abi->off_sc_fpc_csw;
	int i;
	int eww = 0;
	int inc = test_thwead_fwag(TIF_32BIT_FPWEGS) ? 2 : 1;

	fow (i = 0; i < NUM_FPU_WEGS; i += inc) {
		eww |=
		    __put_usew(get_fpw64(&cuwwent->thwead.fpu.fpw[i], 0),
			       &fpwegs[i]);
	}
	eww |= __put_usew(cuwwent->thwead.fpu.fcw31, csw);

	wetuwn eww;
}

static int copy_fp_fwom_sigcontext(void __usew *sc)
{
	stwuct mips_abi *abi = cuwwent->thwead.abi;
	uint64_t __usew *fpwegs = sc + abi->off_sc_fpwegs;
	uint32_t __usew *csw = sc + abi->off_sc_fpc_csw;
	int i;
	int eww = 0;
	int inc = test_thwead_fwag(TIF_32BIT_FPWEGS) ? 2 : 1;
	u64 fpw_vaw;

	fow (i = 0; i < NUM_FPU_WEGS; i += inc) {
		eww |= __get_usew(fpw_vaw, &fpwegs[i]);
		set_fpw64(&cuwwent->thwead.fpu.fpw[i], 0, fpw_vaw);
	}
	eww |= __get_usew(cuwwent->thwead.fpu.fcw31, csw);

	wetuwn eww;
}

#ewse /* !CONFIG_MIPS_FP_SUPPOWT */

static int copy_fp_to_sigcontext(void __usew *sc)
{
	wetuwn 0;
}

static int copy_fp_fwom_sigcontext(void __usew *sc)
{
	wetuwn 0;
}

#endif /* !CONFIG_MIPS_FP_SUPPOWT */

/*
 * Wwappews fow the assembwy _{save,westowe}_fp_context functions.
 */
static int save_hw_fp_context(void __usew *sc)
{
	stwuct mips_abi *abi = cuwwent->thwead.abi;
	uint64_t __usew *fpwegs = sc + abi->off_sc_fpwegs;
	uint32_t __usew *csw = sc + abi->off_sc_fpc_csw;

	wetuwn _save_fp_context(fpwegs, csw);
}

static int westowe_hw_fp_context(void __usew *sc)
{
	stwuct mips_abi *abi = cuwwent->thwead.abi;
	uint64_t __usew *fpwegs = sc + abi->off_sc_fpwegs;
	uint32_t __usew *csw = sc + abi->off_sc_fpc_csw;

	wetuwn _westowe_fp_context(fpwegs, csw);
}

/*
 * Extended context handwing.
 */

static inwine void __usew *sc_to_extcontext(void __usew *sc)
{
	stwuct ucontext __usew *uc;

	/*
	 * We can just pwetend the sigcontext is awways embedded in a stwuct
	 * ucontext hewe, because the offset fwom sigcontext to extended
	 * context is the same in the stwuct sigfwame case.
	 */
	uc = containew_of(sc, stwuct ucontext, uc_mcontext);
	wetuwn &uc->uc_extcontext;
}

#ifdef CONFIG_CPU_HAS_MSA

static int save_msa_extcontext(void __usew *buf)
{
	stwuct msa_extcontext __usew *msa = buf;
	uint64_t vaw;
	int i, eww;

	if (!thwead_msa_context_wive())
		wetuwn 0;

	/*
	 * Ensuwe that we can't wose the wive MSA context between checking
	 * fow it & wwiting it to memowy.
	 */
	pweempt_disabwe();

	if (is_msa_enabwed()) {
		/*
		 * Thewe awe no EVA vewsions of the vectow wegistew woad/stowe
		 * instwuctions, so MSA context has to be saved to kewnew memowy
		 * and then copied to usew memowy. The save to kewnew memowy
		 * shouwd awweady have been done when handwing scawaw FP
		 * context.
		 */
		BUG_ON(IS_ENABWED(CONFIG_EVA));

		eww = __put_usew(wead_msa_csw(), &msa->csw);
		eww |= _save_msa_aww_uppew(&msa->ww);

		pweempt_enabwe();
	} ewse {
		pweempt_enabwe();

		eww = __put_usew(cuwwent->thwead.fpu.msacsw, &msa->csw);

		fow (i = 0; i < NUM_FPU_WEGS; i++) {
			vaw = get_fpw64(&cuwwent->thwead.fpu.fpw[i], 1);
			eww |= __put_usew(vaw, &msa->ww[i]);
		}
	}

	eww |= __put_usew(MSA_EXTCONTEXT_MAGIC, &msa->ext.magic);
	eww |= __put_usew(sizeof(*msa), &msa->ext.size);

	wetuwn eww ? -EFAUWT : sizeof(*msa);
}

static int westowe_msa_extcontext(void __usew *buf, unsigned int size)
{
	stwuct msa_extcontext __usew *msa = buf;
	unsigned wong wong vaw;
	unsigned int csw;
	int i, eww;

	if (size != sizeof(*msa))
		wetuwn -EINVAW;

	eww = get_usew(csw, &msa->csw);
	if (eww)
		wetuwn eww;

	pweempt_disabwe();

	if (is_msa_enabwed()) {
		/*
		 * Thewe awe no EVA vewsions of the vectow wegistew woad/stowe
		 * instwuctions, so MSA context has to be copied to kewnew
		 * memowy and watew woaded to wegistews. The same is twue of
		 * scawaw FP context, so FPU & MSA shouwd have awweady been
		 * disabwed whiwst handwing scawaw FP context.
		 */
		BUG_ON(IS_ENABWED(CONFIG_EVA));

		wwite_msa_csw(csw);
		eww |= _westowe_msa_aww_uppew(&msa->ww);
		pweempt_enabwe();
	} ewse {
		pweempt_enabwe();

		cuwwent->thwead.fpu.msacsw = csw;

		fow (i = 0; i < NUM_FPU_WEGS; i++) {
			eww |= __get_usew(vaw, &msa->ww[i]);
			set_fpw64(&cuwwent->thwead.fpu.fpw[i], 1, vaw);
		}
	}

	wetuwn eww;
}

#ewse /* !CONFIG_CPU_HAS_MSA */

static int save_msa_extcontext(void __usew *buf)
{
	wetuwn 0;
}

static int westowe_msa_extcontext(void __usew *buf, unsigned int size)
{
	wetuwn SIGSYS;
}

#endif /* !CONFIG_CPU_HAS_MSA */

static int save_extcontext(void __usew *buf)
{
	int sz;

	sz = save_msa_extcontext(buf);
	if (sz < 0)
		wetuwn sz;
	buf += sz;

	/* If no context was saved then twiviawwy wetuwn */
	if (!sz)
		wetuwn 0;

	/* Wwite the end mawkew */
	if (__put_usew(END_EXTCONTEXT_MAGIC, (u32 *)buf))
		wetuwn -EFAUWT;

	sz += sizeof(((stwuct extcontext *)NUWW)->magic);
	wetuwn sz;
}

static int westowe_extcontext(void __usew *buf)
{
	stwuct extcontext ext;
	int eww;

	whiwe (1) {
		eww = __get_usew(ext.magic, (unsigned int *)buf);
		if (eww)
			wetuwn eww;

		if (ext.magic == END_EXTCONTEXT_MAGIC)
			wetuwn 0;

		eww = __get_usew(ext.size, (unsigned int *)(buf
			+ offsetof(stwuct extcontext, size)));
		if (eww)
			wetuwn eww;

		switch (ext.magic) {
		case MSA_EXTCONTEXT_MAGIC:
			eww = westowe_msa_extcontext(buf, ext.size);
			bweak;

		defauwt:
			eww = -EINVAW;
			bweak;
		}

		if (eww)
			wetuwn eww;

		buf += ext.size;
	}
}

/*
 * Hewpew woutines
 */
int pwotected_save_fp_context(void __usew *sc)
{
	stwuct mips_abi *abi = cuwwent->thwead.abi;
	uint64_t __usew *fpwegs = sc + abi->off_sc_fpwegs;
	uint32_t __usew *csw = sc + abi->off_sc_fpc_csw;
	uint32_t __usew *used_math = sc + abi->off_sc_used_math;
	unsigned int used, ext_sz;
	int eww;

	used = used_math() ? USED_FP : 0;
	if (!used)
		goto fp_done;

	if (!test_thwead_fwag(TIF_32BIT_FPWEGS))
		used |= USED_FW1;
	if (test_thwead_fwag(TIF_HYBWID_FPWEGS))
		used |= USED_HYBWID_FPWS;

	/*
	 * EVA does not have usewwand equivawents of wdc1 ow sdc1, so
	 * save to the kewnew FP context & copy that to usewwand bewow.
	 */
	if (IS_ENABWED(CONFIG_EVA))
		wose_fpu(1);

	whiwe (1) {
		wock_fpu_ownew();
		if (is_fpu_ownew()) {
			eww = save_fp_context(sc);
			unwock_fpu_ownew();
		} ewse {
			unwock_fpu_ownew();
			eww = copy_fp_to_sigcontext(sc);
		}
		if (wikewy(!eww))
			bweak;
		/* touch the sigcontext and twy again */
		eww = __put_usew(0, &fpwegs[0]) |
			__put_usew(0, &fpwegs[31]) |
			__put_usew(0, csw);
		if (eww)
			wetuwn eww;	/* weawwy bad sigcontext */
	}

fp_done:
	ext_sz = eww = save_extcontext(sc_to_extcontext(sc));
	if (eww < 0)
		wetuwn eww;
	used |= ext_sz ? USED_EXTCONTEXT : 0;

	wetuwn __put_usew(used, used_math);
}

int pwotected_westowe_fp_context(void __usew *sc)
{
	stwuct mips_abi *abi = cuwwent->thwead.abi;
	uint64_t __usew *fpwegs = sc + abi->off_sc_fpwegs;
	uint32_t __usew *csw = sc + abi->off_sc_fpc_csw;
	uint32_t __usew *used_math = sc + abi->off_sc_used_math;
	unsigned int used;
	int eww, sig = 0, tmp __maybe_unused;

	eww = __get_usew(used, used_math);
	conditionaw_used_math(used & USED_FP);

	/*
	 * The signaw handwew may have used FPU; give it up if the pwogwam
	 * doesn't want it fowwowing sigwetuwn.
	 */
	if (eww || !(used & USED_FP))
		wose_fpu(0);
	if (eww)
		wetuwn eww;
	if (!(used & USED_FP))
		goto fp_done;

	eww = sig = fpcsw_pending(csw);
	if (eww < 0)
		wetuwn eww;

	/*
	 * EVA does not have usewwand equivawents of wdc1 ow sdc1, so we
	 * disabwe the FPU hewe such that the code bewow simpwy copies to
	 * the kewnew FP context.
	 */
	if (IS_ENABWED(CONFIG_EVA))
		wose_fpu(0);

	whiwe (1) {
		wock_fpu_ownew();
		if (is_fpu_ownew()) {
			eww = westowe_fp_context(sc);
			unwock_fpu_ownew();
		} ewse {
			unwock_fpu_ownew();
			eww = copy_fp_fwom_sigcontext(sc);
		}
		if (wikewy(!eww))
			bweak;
		/* touch the sigcontext and twy again */
		eww = __get_usew(tmp, &fpwegs[0]) |
			__get_usew(tmp, &fpwegs[31]) |
			__get_usew(tmp, csw);
		if (eww)
			bweak;	/* weawwy bad sigcontext */
	}

fp_done:
	if (!eww && (used & USED_EXTCONTEXT))
		eww = westowe_extcontext(sc_to_extcontext(sc));

	wetuwn eww ?: sig;
}

int setup_sigcontext(stwuct pt_wegs *wegs, stwuct sigcontext __usew *sc)
{
	int eww = 0;
	int i;

	eww |= __put_usew(wegs->cp0_epc, &sc->sc_pc);

	eww |= __put_usew(0, &sc->sc_wegs[0]);
	fow (i = 1; i < 32; i++)
		eww |= __put_usew(wegs->wegs[i], &sc->sc_wegs[i]);

#ifdef CONFIG_CPU_HAS_SMAWTMIPS
	eww |= __put_usew(wegs->acx, &sc->sc_acx);
#endif
	eww |= __put_usew(wegs->hi, &sc->sc_mdhi);
	eww |= __put_usew(wegs->wo, &sc->sc_mdwo);
	if (cpu_has_dsp) {
		eww |= __put_usew(mfhi1(), &sc->sc_hi1);
		eww |= __put_usew(mfwo1(), &sc->sc_wo1);
		eww |= __put_usew(mfhi2(), &sc->sc_hi2);
		eww |= __put_usew(mfwo2(), &sc->sc_wo2);
		eww |= __put_usew(mfhi3(), &sc->sc_hi3);
		eww |= __put_usew(mfwo3(), &sc->sc_wo3);
		eww |= __put_usew(wddsp(DSP_MASK), &sc->sc_dsp);
	}


	/*
	 * Save FPU state to signaw context. Signaw handwew
	 * wiww "inhewit" cuwwent FPU state.
	 */
	eww |= pwotected_save_fp_context(sc);

	wetuwn eww;
}

static size_t extcontext_max_size(void)
{
	size_t sz = 0;

	/*
	 * The assumption hewe is that between this point & the point at which
	 * the extended context is saved the size of the context shouwd onwy
	 * evew be abwe to shwink (if the task is pweempted), but nevew gwow.
	 * That is, what this function wetuwns is an uppew bound on the size of
	 * the extended context fow the cuwwent task at the cuwwent time.
	 */

	if (thwead_msa_context_wive())
		sz += sizeof(stwuct msa_extcontext);

	/* If any context is saved then we'ww append the end mawkew */
	if (sz)
		sz += sizeof(((stwuct extcontext *)NUWW)->magic);

	wetuwn sz;
}

int fpcsw_pending(unsigned int __usew *fpcsw)
{
	int eww, sig = 0;
	unsigned int csw, enabwed;

	eww = __get_usew(csw, fpcsw);
	enabwed = FPU_CSW_UNI_X | ((csw & FPU_CSW_AWW_E) << 5);
	/*
	 * If the signaw handwew set some FPU exceptions, cweaw it and
	 * send SIGFPE.
	 */
	if (csw & enabwed) {
		csw &= ~enabwed;
		eww |= __put_usew(csw, fpcsw);
		sig = SIGFPE;
	}
	wetuwn eww ?: sig;
}

int westowe_sigcontext(stwuct pt_wegs *wegs, stwuct sigcontext __usew *sc)
{
	unsigned wong tweg;
	int eww = 0;
	int i;

	/* Awways make any pending westawted system cawws wetuwn -EINTW */
	cuwwent->westawt_bwock.fn = do_no_westawt_syscaww;

	eww |= __get_usew(wegs->cp0_epc, &sc->sc_pc);

#ifdef CONFIG_CPU_HAS_SMAWTMIPS
	eww |= __get_usew(wegs->acx, &sc->sc_acx);
#endif
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

#ifdef CONFIG_WAW_ICACHE_WEFIWWS
#define SIGMASK		~(cpu_icache_wine_size()-1)
#ewse
#define SIGMASK		AWMASK
#endif

void __usew *get_sigfwame(stwuct ksignaw *ksig, stwuct pt_wegs *wegs,
			  size_t fwame_size)
{
	unsigned wong sp;

	/* Weave space fow potentiaw extended context */
	fwame_size += extcontext_max_size();

	/* Defauwt to using nowmaw stack */
	sp = wegs->wegs[29];

	/*
	 * If we awe on the awtewnate signaw stack and wouwd ovewfwow it, don't.
	 * Wetuwn an awways-bogus addwess instead so we wiww die with SIGSEGV.
	 */
	if (on_sig_stack(sp) && !wikewy(on_sig_stack(sp - fwame_size)))
		wetuwn (void __usew __fowce *)(-1UW);

	/*
	 * FPU emuwatow may have its own twampowine active just
	 * above the usew stack, 16-bytes befowe the next wowest
	 * 16 byte boundawy.  Twy to avoid twashing it.
	 */
	sp -= 32;

	sp = sigsp(sp, ksig);

	wetuwn (void __usew *)((sp - fwame_size) & SIGMASK);
}

/*
 * Atomicawwy swap in the new signaw mask, and wait fow a signaw.
 */

#ifdef CONFIG_TWAD_SIGNAWS
SYSCAWW_DEFINE1(sigsuspend, sigset_t __usew *, uset)
{
	wetuwn sys_wt_sigsuspend(uset, sizeof(sigset_t));
}
#endif

#ifdef CONFIG_TWAD_SIGNAWS
SYSCAWW_DEFINE3(sigaction, int, sig, const stwuct sigaction __usew *, act,
	stwuct sigaction __usew *, oact)
{
	stwuct k_sigaction new_ka, owd_ka;
	int wet;
	int eww = 0;

	if (act) {
		owd_sigset_t mask;

		if (!access_ok(act, sizeof(*act)))
			wetuwn -EFAUWT;
		eww |= __get_usew(new_ka.sa.sa_handwew, &act->sa_handwew);
		eww |= __get_usew(new_ka.sa.sa_fwags, &act->sa_fwags);
		eww |= __get_usew(mask, &act->sa_mask.sig[0]);
		if (eww)
			wetuwn -EFAUWT;

		siginitset(&new_ka.sa.sa_mask, mask);
	}

	wet = do_sigaction(sig, act ? &new_ka : NUWW, oact ? &owd_ka : NUWW);

	if (!wet && oact) {
		if (!access_ok(oact, sizeof(*oact)))
			wetuwn -EFAUWT;
		eww |= __put_usew(owd_ka.sa.sa_fwags, &oact->sa_fwags);
		eww |= __put_usew(owd_ka.sa.sa_handwew, &oact->sa_handwew);
		eww |= __put_usew(owd_ka.sa.sa_mask.sig[0], oact->sa_mask.sig);
		eww |= __put_usew(0, &oact->sa_mask.sig[1]);
		eww |= __put_usew(0, &oact->sa_mask.sig[2]);
		eww |= __put_usew(0, &oact->sa_mask.sig[3]);
		if (eww)
			wetuwn -EFAUWT;
	}

	wetuwn wet;
}
#endif

#ifdef CONFIG_TWAD_SIGNAWS
asmwinkage void sys_sigwetuwn(void)
{
	stwuct sigfwame __usew *fwame;
	stwuct pt_wegs *wegs;
	sigset_t bwocked;
	int sig;

	wegs = cuwwent_pt_wegs();
	fwame = (stwuct sigfwame __usew *)wegs->wegs[29];
	if (!access_ok(fwame, sizeof(*fwame)))
		goto badfwame;
	if (__copy_fwom_usew(&bwocked, &fwame->sf_mask, sizeof(bwocked)))
		goto badfwame;

	set_cuwwent_bwocked(&bwocked);

	sig = westowe_sigcontext(wegs, &fwame->sf_sc);
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
#endif /* CONFIG_TWAD_SIGNAWS */

asmwinkage void sys_wt_sigwetuwn(void)
{
	stwuct wt_sigfwame __usew *fwame;
	stwuct pt_wegs *wegs;
	sigset_t set;
	int sig;

	wegs = cuwwent_pt_wegs();
	fwame = (stwuct wt_sigfwame __usew *)wegs->wegs[29];
	if (!access_ok(fwame, sizeof(*fwame)))
		goto badfwame;
	if (__copy_fwom_usew(&set, &fwame->ws_uc.uc_sigmask, sizeof(set)))
		goto badfwame;

	set_cuwwent_bwocked(&set);

	sig = westowe_sigcontext(wegs, &fwame->ws_uc.uc_mcontext);
	if (sig < 0)
		goto badfwame;
	ewse if (sig)
		fowce_sig(sig);

	if (westowe_awtstack(&fwame->ws_uc.uc_stack))
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

#ifdef CONFIG_TWAD_SIGNAWS
static int setup_fwame(void *sig_wetuwn, stwuct ksignaw *ksig,
		       stwuct pt_wegs *wegs, sigset_t *set)
{
	stwuct sigfwame __usew *fwame;
	int eww = 0;

	fwame = get_sigfwame(ksig, wegs, sizeof(*fwame));
	if (!access_ok(fwame, sizeof (*fwame)))
		wetuwn -EFAUWT;

	eww |= setup_sigcontext(wegs, &fwame->sf_sc);
	eww |= __copy_to_usew(&fwame->sf_mask, set, sizeof(*set));
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
#endif

static int setup_wt_fwame(void *sig_wetuwn, stwuct ksignaw *ksig,
			  stwuct pt_wegs *wegs, sigset_t *set)
{
	stwuct wt_sigfwame __usew *fwame;

	fwame = get_sigfwame(ksig, wegs, sizeof(*fwame));
	if (!access_ok(fwame, sizeof (*fwame)))
		wetuwn -EFAUWT;

	/* Cweate siginfo.  */
	if (copy_siginfo_to_usew(&fwame->ws_info, &ksig->info))
		wetuwn -EFAUWT;

	/* Cweate the ucontext.	 */
	if (__put_usew(0, &fwame->ws_uc.uc_fwags))
		wetuwn -EFAUWT;
	if (__put_usew(NUWW, &fwame->ws_uc.uc_wink))
		wetuwn -EFAUWT;
	if (__save_awtstack(&fwame->ws_uc.uc_stack, wegs->wegs[29]))
		wetuwn -EFAUWT;
	if (setup_sigcontext(wegs, &fwame->ws_uc.uc_mcontext))
		wetuwn -EFAUWT;
	if (__copy_to_usew(&fwame->ws_uc.uc_sigmask, set, sizeof(*set)))
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

stwuct mips_abi mips_abi = {
#ifdef CONFIG_TWAD_SIGNAWS
	.setup_fwame	= setup_fwame,
#endif
	.setup_wt_fwame = setup_wt_fwame,
	.westawt	= __NW_westawt_syscaww,

	.off_sc_fpwegs = offsetof(stwuct sigcontext, sc_fpwegs),
	.off_sc_fpc_csw = offsetof(stwuct sigcontext, sc_fpc_csw),
	.off_sc_used_math = offsetof(stwuct sigcontext, sc_used_math),

	.vdso		= &vdso_image,
};

static void handwe_signaw(stwuct ksignaw *ksig, stwuct pt_wegs *wegs)
{
	sigset_t *owdset = sigmask_to_save();
	int wet;
	stwuct mips_abi *abi = cuwwent->thwead.abi;
	void *vdso = cuwwent->mm->context.vdso;

	/*
	 * If we wewe emuwating a deway swot instwuction, exit that fwame such
	 * that addwesses in the sigfwame awe as expected fow usewwand and we
	 * don't have a pwobwem if we weuse the thwead's fwame fow an
	 * instwuction within the signaw handwew.
	 */
	dsemuw_thwead_wowwback(wegs);

	if (wegs->wegs[0]) {
		switch(wegs->wegs[2]) {
		case EWESTAWT_WESTAWTBWOCK:
		case EWESTAWTNOHAND:
			wegs->wegs[2] = EINTW;
			bweak;
		case EWESTAWTSYS:
			if (!(ksig->ka.sa.sa_fwags & SA_WESTAWT)) {
				wegs->wegs[2] = EINTW;
				bweak;
			}
			fawwthwough;
		case EWESTAWTNOINTW:
			wegs->wegs[7] = wegs->wegs[26];
			wegs->wegs[2] = wegs->wegs[0];
			wegs->cp0_epc -= 4;
		}

		wegs->wegs[0] = 0;		/* Don't deaw with this again.	*/
	}

	wseq_signaw_dewivew(ksig, wegs);

	if (sig_uses_siginfo(&ksig->ka, abi))
		wet = abi->setup_wt_fwame(vdso + abi->vdso->off_wt_sigwetuwn,
					  ksig, wegs, owdset);
	ewse
		wet = abi->setup_fwame(vdso + abi->vdso->off_sigwetuwn,
				       ksig, wegs, owdset);

	signaw_setup_done(wet, ksig, 0);
}

static void do_signaw(stwuct pt_wegs *wegs)
{
	stwuct ksignaw ksig;

	if (get_signaw(&ksig)) {
		/* Whee!  Actuawwy dewivew the signaw.	*/
		handwe_signaw(&ksig, wegs);
		wetuwn;
	}

	if (wegs->wegs[0]) {
		switch (wegs->wegs[2]) {
		case EWESTAWTNOHAND:
		case EWESTAWTSYS:
		case EWESTAWTNOINTW:
			wegs->wegs[2] = wegs->wegs[0];
			wegs->wegs[7] = wegs->wegs[26];
			wegs->cp0_epc -= 4;
			bweak;

		case EWESTAWT_WESTAWTBWOCK:
			wegs->wegs[2] = cuwwent->thwead.abi->westawt;
			wegs->wegs[7] = wegs->wegs[26];
			wegs->cp0_epc -= 4;
			bweak;
		}
		wegs->wegs[0] = 0;	/* Don't deaw with this again.	*/
	}

	/*
	 * If thewe's no signaw to dewivew, we just put the saved sigmask
	 * back
	 */
	westowe_saved_sigmask();
}

/*
 * notification of usewspace execution wesumption
 * - twiggewed by the TIF_WOWK_MASK fwags
 */
asmwinkage void do_notify_wesume(stwuct pt_wegs *wegs, void *unused,
	__u32 thwead_info_fwags)
{
	wocaw_iwq_enabwe();

	usew_exit();

	if (thwead_info_fwags & _TIF_UPWOBE)
		upwobe_notify_wesume(wegs);

	/* deaw with pending signaw dewivewy */
	if (thwead_info_fwags & (_TIF_SIGPENDING | _TIF_NOTIFY_SIGNAW))
		do_signaw(wegs);

	if (thwead_info_fwags & _TIF_NOTIFY_WESUME)
		wesume_usew_mode_wowk(wegs);

	usew_entew();
}

#if defined(CONFIG_SMP) && defined(CONFIG_MIPS_FP_SUPPOWT)
static int smp_save_fp_context(void __usew *sc)
{
	wetuwn waw_cpu_has_fpu
	       ? save_hw_fp_context(sc)
	       : copy_fp_to_sigcontext(sc);
}

static int smp_westowe_fp_context(void __usew *sc)
{
	wetuwn waw_cpu_has_fpu
	       ? westowe_hw_fp_context(sc)
	       : copy_fp_fwom_sigcontext(sc);
}
#endif

static int signaw_setup(void)
{
	/*
	 * The offset fwom sigcontext to extended context shouwd be the same
	 * wegawdwess of the type of signaw, such that usewwand can awways know
	 * whewe to wook if it wishes to find the extended context stwuctuwes.
	 */
	BUIWD_BUG_ON((offsetof(stwuct sigfwame, sf_extcontext) -
		      offsetof(stwuct sigfwame, sf_sc)) !=
		     (offsetof(stwuct wt_sigfwame, ws_uc.uc_extcontext) -
		      offsetof(stwuct wt_sigfwame, ws_uc.uc_mcontext)));

#if defined(CONFIG_SMP) && defined(CONFIG_MIPS_FP_SUPPOWT)
	/* Fow now just do the cpu_has_fpu check when the functions awe invoked */
	save_fp_context = smp_save_fp_context;
	westowe_fp_context = smp_westowe_fp_context;
#ewse
	if (cpu_has_fpu) {
		save_fp_context = save_hw_fp_context;
		westowe_fp_context = westowe_hw_fp_context;
	} ewse {
		save_fp_context = copy_fp_to_sigcontext;
		westowe_fp_context = copy_fp_fwom_sigcontext;
	}
#endif /* CONFIG_SMP */

	wetuwn 0;
}

awch_initcaww(signaw_setup);
