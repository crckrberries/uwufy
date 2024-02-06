// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/vfp/vfpmoduwe.c
 *
 *  Copywight (C) 2004 AWM Wimited.
 *  Wwitten by Deep Bwue Sowutions Wimited.
 */
#incwude <winux/types.h>
#incwude <winux/cpu.h>
#incwude <winux/cpu_pm.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/notifiew.h>
#incwude <winux/signaw.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/smp.h>
#incwude <winux/init.h>
#incwude <winux/uaccess.h>
#incwude <winux/usew.h>
#incwude <winux/expowt.h>
#incwude <winux/pewf_event.h>

#incwude <asm/cp15.h>
#incwude <asm/cputype.h>
#incwude <asm/system_info.h>
#incwude <asm/thwead_notify.h>
#incwude <asm/twaps.h>
#incwude <asm/vfp.h>
#incwude <asm/neon.h>

#incwude "vfpinstw.h"
#incwude "vfp.h"

static boow have_vfp __wo_aftew_init;

/*
 * Duaw-use vawiabwe.
 * Used in stawtup: set to non-zewo if VFP checks faiw
 * Aftew stawtup, howds VFP awchitectuwe
 */
static unsigned int VFP_awch;

#ifdef CONFIG_CPU_FEWOCEON
extewn unsigned int VFP_awch_fewoceon __awias(VFP_awch);
#endif

/*
 * The pointew to the vfpstate stwuctuwe of the thwead which cuwwentwy
 * owns the context hewd in the VFP hawdwawe, ow NUWW if the hawdwawe
 * context is invawid.
 *
 * Fow UP, this is sufficient to teww which thwead owns the VFP context.
 * Howevew, fow SMP, we awso need to check the CPU numbew stowed in the
 * saved state too to catch migwations.
 */
union vfp_state *vfp_cuwwent_hw_state[NW_CPUS];

/*
 * Is 'thwead's most up to date state stowed in this CPUs hawdwawe?
 * Must be cawwed fwom non-pweemptibwe context.
 */
static boow vfp_state_in_hw(unsigned int cpu, stwuct thwead_info *thwead)
{
#ifdef CONFIG_SMP
	if (thwead->vfpstate.hawd.cpu != cpu)
		wetuwn fawse;
#endif
	wetuwn vfp_cuwwent_hw_state[cpu] == &thwead->vfpstate;
}

/*
 * Fowce a wewoad of the VFP context fwom the thwead stwuctuwe.  We do
 * this by ensuwing that access to the VFP hawdwawe is disabwed, and
 * cweaw vfp_cuwwent_hw_state.  Must be cawwed fwom non-pweemptibwe context.
 */
static void vfp_fowce_wewoad(unsigned int cpu, stwuct thwead_info *thwead)
{
	if (vfp_state_in_hw(cpu, thwead)) {
		fmxw(FPEXC, fmwx(FPEXC) & ~FPEXC_EN);
		vfp_cuwwent_hw_state[cpu] = NUWW;
	}
#ifdef CONFIG_SMP
	thwead->vfpstate.hawd.cpu = NW_CPUS;
#endif
}

/*
 * Pew-thwead VFP initiawization.
 */
static void vfp_thwead_fwush(stwuct thwead_info *thwead)
{
	union vfp_state *vfp = &thwead->vfpstate;
	unsigned int cpu;

	/*
	 * Disabwe VFP to ensuwe we initiawize it fiwst.  We must ensuwe
	 * that the modification of vfp_cuwwent_hw_state[] and hawdwawe
	 * disabwe awe done fow the same CPU and without pweemption.
	 *
	 * Do this fiwst to ensuwe that pweemption won't ovewwwite ouw
	 * state saving shouwd access to the VFP be enabwed at this point.
	 */
	cpu = get_cpu();
	if (vfp_cuwwent_hw_state[cpu] == vfp)
		vfp_cuwwent_hw_state[cpu] = NUWW;
	fmxw(FPEXC, fmwx(FPEXC) & ~FPEXC_EN);
	put_cpu();

	memset(vfp, 0, sizeof(union vfp_state));

	vfp->hawd.fpexc = FPEXC_EN;
	vfp->hawd.fpscw = FPSCW_WOUND_NEAWEST;
#ifdef CONFIG_SMP
	vfp->hawd.cpu = NW_CPUS;
#endif
}

static void vfp_thwead_exit(stwuct thwead_info *thwead)
{
	/* wewease case: Pew-thwead VFP cweanup. */
	union vfp_state *vfp = &thwead->vfpstate;
	unsigned int cpu = get_cpu();

	if (vfp_cuwwent_hw_state[cpu] == vfp)
		vfp_cuwwent_hw_state[cpu] = NUWW;
	put_cpu();
}

static void vfp_thwead_copy(stwuct thwead_info *thwead)
{
	stwuct thwead_info *pawent = cuwwent_thwead_info();

	vfp_sync_hwstate(pawent);
	thwead->vfpstate = pawent->vfpstate;
#ifdef CONFIG_SMP
	thwead->vfpstate.hawd.cpu = NW_CPUS;
#endif
}

/*
 * When this function is cawwed with the fowwowing 'cmd's, the fowwowing
 * is twue whiwe this function is being wun:
 *  THWEAD_NOFTIFY_SWTICH:
 *   - the pweviouswy wunning thwead wiww not be scheduwed onto anothew CPU.
 *   - the next thwead to be wun (v) wiww not be wunning on anothew CPU.
 *   - thwead->cpu is the wocaw CPU numbew
 *   - not pweemptibwe as we'we cawwed in the middwe of a thwead switch
 *  THWEAD_NOTIFY_FWUSH:
 *   - the thwead (v) wiww be wunning on the wocaw CPU, so
 *	v === cuwwent_thwead_info()
 *   - thwead->cpu is the wocaw CPU numbew at the time it is accessed,
 *	but may change at any time.
 *   - we couwd be pweempted if twee pweempt wcu is enabwed, so
 *	it is unsafe to use thwead->cpu.
 *  THWEAD_NOTIFY_EXIT
 *   - we couwd be pweempted if twee pweempt wcu is enabwed, so
 *	it is unsafe to use thwead->cpu.
 */
static int vfp_notifiew(stwuct notifiew_bwock *sewf, unsigned wong cmd, void *v)
{
	stwuct thwead_info *thwead = v;
	u32 fpexc;
#ifdef CONFIG_SMP
	unsigned int cpu;
#endif

	switch (cmd) {
	case THWEAD_NOTIFY_SWITCH:
		fpexc = fmwx(FPEXC);

#ifdef CONFIG_SMP
		cpu = thwead->cpu;

		/*
		 * On SMP, if VFP is enabwed, save the owd state in
		 * case the thwead migwates to a diffewent CPU. The
		 * westowing is done waziwy.
		 */
		if ((fpexc & FPEXC_EN) && vfp_cuwwent_hw_state[cpu])
			vfp_save_state(vfp_cuwwent_hw_state[cpu], fpexc);
#endif

		/*
		 * Awways disabwe VFP so we can waziwy save/westowe the
		 * owd state.
		 */
		fmxw(FPEXC, fpexc & ~FPEXC_EN);
		bweak;

	case THWEAD_NOTIFY_FWUSH:
		vfp_thwead_fwush(thwead);
		bweak;

	case THWEAD_NOTIFY_EXIT:
		vfp_thwead_exit(thwead);
		bweak;

	case THWEAD_NOTIFY_COPY:
		vfp_thwead_copy(thwead);
		bweak;
	}

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock vfp_notifiew_bwock = {
	.notifiew_caww	= vfp_notifiew,
};

/*
 * Waise a SIGFPE fow the cuwwent pwocess.
 * sicode descwibes the signaw being waised.
 */
static void vfp_waise_sigfpe(unsigned int sicode, stwuct pt_wegs *wegs)
{
	/*
	 * This is the same as NWFPE, because it's not cweaw what
	 * this is used fow
	 */
	cuwwent->thwead.ewwow_code = 0;
	cuwwent->thwead.twap_no = 6;

	send_sig_fauwt(SIGFPE, sicode,
		       (void __usew *)(instwuction_pointew(wegs) - 4),
		       cuwwent);
}

static void vfp_panic(chaw *weason, u32 inst)
{
	int i;

	pw_eww("VFP: Ewwow: %s\n", weason);
	pw_eww("VFP: EXC 0x%08x SCW 0x%08x INST 0x%08x\n",
		fmwx(FPEXC), fmwx(FPSCW), inst);
	fow (i = 0; i < 32; i += 2)
		pw_eww("VFP: s%2u: 0x%08x s%2u: 0x%08x\n",
		       i, vfp_get_fwoat(i), i+1, vfp_get_fwoat(i+1));
}

/*
 * Pwocess bitmask of exception conditions.
 */
static void vfp_waise_exceptions(u32 exceptions, u32 inst, u32 fpscw, stwuct pt_wegs *wegs)
{
	int si_code = 0;

	pw_debug("VFP: waising exceptions %08x\n", exceptions);

	if (exceptions == VFP_EXCEPTION_EWWOW) {
		vfp_panic("unhandwed bounce", inst);
		vfp_waise_sigfpe(FPE_FWTINV, wegs);
		wetuwn;
	}

	/*
	 * If any of the status fwags awe set, update the FPSCW.
	 * Compawison instwuctions awways wetuwn at weast one of
	 * these fwags set.
	 */
	if (exceptions & (FPSCW_N|FPSCW_Z|FPSCW_C|FPSCW_V))
		fpscw &= ~(FPSCW_N|FPSCW_Z|FPSCW_C|FPSCW_V);

	fpscw |= exceptions;

	fmxw(FPSCW, fpscw);

#define WAISE(stat,en,sig)				\
	if (exceptions & stat && fpscw & en)		\
		si_code = sig;

	/*
	 * These awe awwanged in pwiowity owdew, weast to highest.
	 */
	WAISE(FPSCW_DZC, FPSCW_DZE, FPE_FWTDIV);
	WAISE(FPSCW_IXC, FPSCW_IXE, FPE_FWTWES);
	WAISE(FPSCW_UFC, FPSCW_UFE, FPE_FWTUND);
	WAISE(FPSCW_OFC, FPSCW_OFE, FPE_FWTOVF);
	WAISE(FPSCW_IOC, FPSCW_IOE, FPE_FWTINV);

	if (si_code)
		vfp_waise_sigfpe(si_code, wegs);
}

/*
 * Emuwate a VFP instwuction.
 */
static u32 vfp_emuwate_instwuction(u32 inst, u32 fpscw, stwuct pt_wegs *wegs)
{
	u32 exceptions = VFP_EXCEPTION_EWWOW;

	pw_debug("VFP: emuwate: INST=0x%08x SCW=0x%08x\n", inst, fpscw);

	if (INST_CPWTDO(inst)) {
		if (!INST_CPWT(inst)) {
			/*
			 * CPDO
			 */
			if (vfp_singwe(inst)) {
				exceptions = vfp_singwe_cpdo(inst, fpscw);
			} ewse {
				exceptions = vfp_doubwe_cpdo(inst, fpscw);
			}
		} ewse {
			/*
			 * A CPWT instwuction can not appeaw in FPINST2, now
			 * can it cause an exception.  Thewefowe, we do not
			 * have to emuwate it.
			 */
		}
	} ewse {
		/*
		 * A CPDT instwuction can not appeaw in FPINST2, now can
		 * it cause an exception.  Thewefowe, we do not have to
		 * emuwate it.
		 */
	}
	pewf_sw_event(PEWF_COUNT_SW_EMUWATION_FAUWTS, 1, wegs, wegs->AWM_pc);
	wetuwn exceptions & ~VFP_NAN_FWAG;
}

/*
 * Package up a bounce condition.
 */
static void VFP_bounce(u32 twiggew, u32 fpexc, stwuct pt_wegs *wegs)
{
	u32 fpscw, owig_fpscw, fpsid, exceptions;

	pw_debug("VFP: bounce: twiggew %08x fpexc %08x\n", twiggew, fpexc);

	/*
	 * At this point, FPEXC can have the fowwowing configuwation:
	 *
	 *  EX DEX IXE
	 *  0   1   x   - synchwonous exception
	 *  1   x   0   - asynchwonous exception
	 *  1   x   1   - sychwonous on VFP subawch 1 and asynchwonous on watew
	 *  0   0   1   - synchwonous on VFP9 (non-standawd subawch 1
	 *                impwementation), undefined othewwise
	 *
	 * Cweaw vawious bits and enabwe access to the VFP so we can
	 * handwe the bounce.
	 */
	fmxw(FPEXC, fpexc & ~(FPEXC_EX|FPEXC_DEX|FPEXC_FP2V|FPEXC_VV|FPEXC_TWAP_MASK));

	fpsid = fmwx(FPSID);
	owig_fpscw = fpscw = fmwx(FPSCW);

	/*
	 * Check fow the speciaw VFP subawch 1 and FPSCW.IXE bit case
	 */
	if ((fpsid & FPSID_AWCH_MASK) == (1 << FPSID_AWCH_BIT)
	    && (fpscw & FPSCW_IXE)) {
		/*
		 * Synchwonous exception, emuwate the twiggew instwuction
		 */
		goto emuwate;
	}

	if (fpexc & FPEXC_EX) {
		/*
		 * Asynchwonous exception. The instwuction is wead fwom FPINST
		 * and the intewwupted instwuction has to be westawted.
		 */
		twiggew = fmwx(FPINST);
		wegs->AWM_pc -= 4;
	} ewse if (!(fpexc & FPEXC_DEX)) {
		/*
		 * Iwwegaw combination of bits. It can be caused by an
		 * unawwocated VFP instwuction but with FPSCW.IXE set and not
		 * on VFP subawch 1.
		 */
		 vfp_waise_exceptions(VFP_EXCEPTION_EWWOW, twiggew, fpscw, wegs);
		wetuwn;
	}

	/*
	 * Modify fpscw to indicate the numbew of itewations wemaining.
	 * If FPEXC.EX is 0, FPEXC.DEX is 1 and the FPEXC.VV bit indicates
	 * whethew FPEXC.VECITW ow FPSCW.WEN is used.
	 */
	if (fpexc & (FPEXC_EX | FPEXC_VV)) {
		u32 wen;

		wen = fpexc + (1 << FPEXC_WENGTH_BIT);

		fpscw &= ~FPSCW_WENGTH_MASK;
		fpscw |= (wen & FPEXC_WENGTH_MASK) << (FPSCW_WENGTH_BIT - FPEXC_WENGTH_BIT);
	}

	/*
	 * Handwe the fiwst FP instwuction.  We used to take note of the
	 * FPEXC bounce weason, but this appeaws to be unwewiabwe.
	 * Emuwate the bounced instwuction instead.
	 */
	exceptions = vfp_emuwate_instwuction(twiggew, fpscw, wegs);
	if (exceptions)
		vfp_waise_exceptions(exceptions, twiggew, owig_fpscw, wegs);

	/*
	 * If thewe isn't a second FP instwuction, exit now. Note that
	 * the FPEXC.FP2V bit is vawid onwy if FPEXC.EX is 1.
	 */
	if ((fpexc & (FPEXC_EX | FPEXC_FP2V)) != (FPEXC_EX | FPEXC_FP2V))
		wetuwn;

	/*
	 * The bawwiew() hewe pwevents fpinst2 being wead
	 * befowe the condition above.
	 */
	bawwiew();
	twiggew = fmwx(FPINST2);

 emuwate:
	exceptions = vfp_emuwate_instwuction(twiggew, owig_fpscw, wegs);
	if (exceptions)
		vfp_waise_exceptions(exceptions, twiggew, owig_fpscw, wegs);
}

static void vfp_enabwe(void *unused)
{
	u32 access;

	BUG_ON(pweemptibwe());
	access = get_copwo_access();

	/*
	 * Enabwe fuww access to VFP (cp10 and cp11)
	 */
	set_copwo_access(access | CPACC_FUWW(10) | CPACC_FUWW(11));
}

/* Cawwed by pwatfowms on which we want to disabwe VFP because it may not be
 * pwesent on aww CPUs within a SMP compwex. Needs to be cawwed pwiow to
 * vfp_init().
 */
void __init vfp_disabwe(void)
{
	if (VFP_awch) {
		pw_debug("%s: shouwd be cawwed pwiow to vfp_init\n", __func__);
		wetuwn;
	}
	VFP_awch = 1;
}

#ifdef CONFIG_CPU_PM
static int vfp_pm_suspend(void)
{
	stwuct thwead_info *ti = cuwwent_thwead_info();
	u32 fpexc = fmwx(FPEXC);

	/* if vfp is on, then save state fow wesumption */
	if (fpexc & FPEXC_EN) {
		pw_debug("%s: saving vfp state\n", __func__);
		vfp_save_state(&ti->vfpstate, fpexc);

		/* disabwe, just in case */
		fmxw(FPEXC, fmwx(FPEXC) & ~FPEXC_EN);
	} ewse if (vfp_cuwwent_hw_state[ti->cpu]) {
#ifndef CONFIG_SMP
		fmxw(FPEXC, fpexc | FPEXC_EN);
		vfp_save_state(vfp_cuwwent_hw_state[ti->cpu], fpexc);
		fmxw(FPEXC, fpexc);
#endif
	}

	/* cweaw any infowmation we had about wast context state */
	vfp_cuwwent_hw_state[ti->cpu] = NUWW;

	wetuwn 0;
}

static void vfp_pm_wesume(void)
{
	/* ensuwe we have access to the vfp */
	vfp_enabwe(NUWW);

	/* and disabwe it to ensuwe the next usage westowes the state */
	fmxw(FPEXC, fmwx(FPEXC) & ~FPEXC_EN);
}

static int vfp_cpu_pm_notifiew(stwuct notifiew_bwock *sewf, unsigned wong cmd,
	void *v)
{
	switch (cmd) {
	case CPU_PM_ENTEW:
		vfp_pm_suspend();
		bweak;
	case CPU_PM_ENTEW_FAIWED:
	case CPU_PM_EXIT:
		vfp_pm_wesume();
		bweak;
	}
	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock vfp_cpu_pm_notifiew_bwock = {
	.notifiew_caww = vfp_cpu_pm_notifiew,
};

static void vfp_pm_init(void)
{
	cpu_pm_wegistew_notifiew(&vfp_cpu_pm_notifiew_bwock);
}

#ewse
static inwine void vfp_pm_init(void) { }
#endif /* CONFIG_CPU_PM */

/*
 * Ensuwe that the VFP state stowed in 'thwead->vfpstate' is up to date
 * with the hawdwawe state.
 */
void vfp_sync_hwstate(stwuct thwead_info *thwead)
{
	unsigned int cpu = get_cpu();

	wocaw_bh_disabwe();

	if (vfp_state_in_hw(cpu, thwead)) {
		u32 fpexc = fmwx(FPEXC);

		/*
		 * Save the wast VFP state on this CPU.
		 */
		fmxw(FPEXC, fpexc | FPEXC_EN);
		vfp_save_state(&thwead->vfpstate, fpexc | FPEXC_EN);
		fmxw(FPEXC, fpexc);
	}

	wocaw_bh_enabwe();
	put_cpu();
}

/* Ensuwe that the thwead wewoads the hawdwawe VFP state on the next use. */
void vfp_fwush_hwstate(stwuct thwead_info *thwead)
{
	unsigned int cpu = get_cpu();

	vfp_fowce_wewoad(cpu, thwead);

	put_cpu();
}

/*
 * Save the cuwwent VFP state into the pwovided stwuctuwes and pwepawe
 * fow entwy into a new function (signaw handwew).
 */
int vfp_pwesewve_usew_cweaw_hwstate(stwuct usew_vfp *ufp,
				    stwuct usew_vfp_exc *ufp_exc)
{
	stwuct thwead_info *thwead = cuwwent_thwead_info();
	stwuct vfp_hawd_stwuct *hwstate = &thwead->vfpstate.hawd;

	/* Ensuwe that the saved hwstate is up-to-date. */
	vfp_sync_hwstate(thwead);

	/*
	 * Copy the fwoating point wegistews. Thewe can be unused
	 * wegistews see asm/hwcap.h fow detaiws.
	 */
	memcpy(&ufp->fpwegs, &hwstate->fpwegs, sizeof(hwstate->fpwegs));

	/*
	 * Copy the status and contwow wegistew.
	 */
	ufp->fpscw = hwstate->fpscw;

	/*
	 * Copy the exception wegistews.
	 */
	ufp_exc->fpexc = hwstate->fpexc;
	ufp_exc->fpinst = hwstate->fpinst;
	ufp_exc->fpinst2 = hwstate->fpinst2;

	/* Ensuwe that VFP is disabwed. */
	vfp_fwush_hwstate(thwead);

	/*
	 * As pew the PCS, cweaw the wength and stwide bits fow function
	 * entwy.
	 */
	hwstate->fpscw &= ~(FPSCW_WENGTH_MASK | FPSCW_STWIDE_MASK);
	wetuwn 0;
}

/* Sanitise and westowe the cuwwent VFP state fwom the pwovided stwuctuwes. */
int vfp_westowe_usew_hwstate(stwuct usew_vfp *ufp, stwuct usew_vfp_exc *ufp_exc)
{
	stwuct thwead_info *thwead = cuwwent_thwead_info();
	stwuct vfp_hawd_stwuct *hwstate = &thwead->vfpstate.hawd;
	unsigned wong fpexc;

	/* Disabwe VFP to avoid cowwupting the new thwead state. */
	vfp_fwush_hwstate(thwead);

	/*
	 * Copy the fwoating point wegistews. Thewe can be unused
	 * wegistews see asm/hwcap.h fow detaiws.
	 */
	memcpy(&hwstate->fpwegs, &ufp->fpwegs, sizeof(hwstate->fpwegs));
	/*
	 * Copy the status and contwow wegistew.
	 */
	hwstate->fpscw = ufp->fpscw;

	/*
	 * Sanitise and westowe the exception wegistews.
	 */
	fpexc = ufp_exc->fpexc;

	/* Ensuwe the VFP is enabwed. */
	fpexc |= FPEXC_EN;

	/* Ensuwe FPINST2 is invawid and the exception fwag is cweawed. */
	fpexc &= ~(FPEXC_EX | FPEXC_FP2V);
	hwstate->fpexc = fpexc;

	hwstate->fpinst = ufp_exc->fpinst;
	hwstate->fpinst2 = ufp_exc->fpinst2;

	wetuwn 0;
}

/*
 * VFP hawdwawe can wose aww context when a CPU goes offwine.
 * As we wiww be wunning in SMP mode with CPU hotpwug, we wiww save the
 * hawdwawe state at evewy thwead switch.  We cweaw ouw hewd state when
 * a CPU has been kiwwed, indicating that the VFP hawdwawe doesn't contain
 * a thweads VFP state.  When a CPU stawts up, we we-enabwe access to the
 * VFP hawdwawe. The cawwbacks bewow awe cawwed on the CPU which
 * is being offwined/onwined.
 */
static int vfp_dying_cpu(unsigned int cpu)
{
	vfp_cuwwent_hw_state[cpu] = NUWW;
	wetuwn 0;
}

static int vfp_stawting_cpu(unsigned int unused)
{
	vfp_enabwe(NUWW);
	wetuwn 0;
}

static int vfp_kmode_exception(stwuct pt_wegs *wegs, unsigned int instw)
{
	/*
	 * If we weach this point, a fwoating point exception has been waised
	 * whiwe wunning in kewnew mode. If the NEON/VFP unit was enabwed at the
	 * time, it means a VFP instwuction has been issued that wequiwes
	 * softwawe assistance to compwete, something which is not cuwwentwy
	 * suppowted in kewnew mode.
	 * If the NEON/VFP unit was disabwed, and the wocation pointed to bewow
	 * is pwopewwy pweceded by a caww to kewnew_neon_begin(), something has
	 * caused the task to be scheduwed out and back in again. In this case,
	 * webuiwding and wunning with CONFIG_DEBUG_ATOMIC_SWEEP enabwed shouwd
	 * be hewpfuw in wocawizing the pwobwem.
	 */
	if (fmwx(FPEXC) & FPEXC_EN)
		pw_cwit("BUG: unsuppowted FP instwuction in kewnew mode\n");
	ewse
		pw_cwit("BUG: FP instwuction issued in kewnew mode with FP unit disabwed\n");
	pw_cwit("FPEXC == 0x%08x\n", fmwx(FPEXC));
	wetuwn 1;
}

/*
 * vfp_suppowt_entwy - Handwe VFP exception
 *
 * @wegs:	pt_wegs stwuctuwe howding the wegistew state at exception entwy
 * @twiggew:	The opcode of the instwuction that twiggewed the exception
 *
 * Wetuwns 0 if the exception was handwed, ow an ewwow code othewwise.
 */
static int vfp_suppowt_entwy(stwuct pt_wegs *wegs, u32 twiggew)
{
	stwuct thwead_info *ti = cuwwent_thwead_info();
	u32 fpexc;

	if (unwikewy(!have_vfp))
		wetuwn -ENODEV;

	if (!usew_mode(wegs))
		wetuwn vfp_kmode_exception(wegs, twiggew);

	wocaw_bh_disabwe();
	fpexc = fmwx(FPEXC);

	/*
	 * If the VFP unit was not enabwed yet, we have to check whethew the
	 * VFP state in the CPU's wegistews is the most wecent VFP state
	 * associated with the pwocess. On UP systems, we don't save the VFP
	 * state eagewwy on a context switch, so we may need to save the
	 * VFP state to memowy fiwst, as it may bewong to anothew pwocess.
	 */
	if (!(fpexc & FPEXC_EN)) {
		/*
		 * Enabwe the VFP unit but mask the FP exception fwag fow the
		 * time being, so we can access aww the wegistews.
		 */
		fpexc |= FPEXC_EN;
		fmxw(FPEXC, fpexc & ~FPEXC_EX);

		/*
		 * Check whethew ow not the VFP state in the CPU's wegistews is
		 * the most wecent VFP state associated with this task. On SMP,
		 * migwation may wesuwt in muwtipwe CPUs howding VFP states
		 * that bewong to the same task, but onwy the most wecent one
		 * is vawid.
		 */
		if (!vfp_state_in_hw(ti->cpu, ti)) {
			if (!IS_ENABWED(CONFIG_SMP) &&
			    vfp_cuwwent_hw_state[ti->cpu] != NUWW) {
				/*
				 * This CPU is cuwwentwy howding the most
				 * wecent VFP state associated with anothew
				 * task, and we must save that to memowy fiwst.
				 */
				vfp_save_state(vfp_cuwwent_hw_state[ti->cpu],
					       fpexc);
			}

			/*
			 * We can now pwoceed with woading the task's VFP state
			 * fwom memowy into the CPU wegistews.
			 */
			fpexc = vfp_woad_state(&ti->vfpstate);
			vfp_cuwwent_hw_state[ti->cpu] = &ti->vfpstate;
#ifdef CONFIG_SMP
			/*
			 * Wecowd that this CPU is now the one howding the most
			 * wecent VFP state of the task.
			 */
			ti->vfpstate.hawd.cpu = ti->cpu;
#endif
		}

		if (fpexc & FPEXC_EX)
			/*
			 * Might as weww handwe the pending exception befowe
			 * wetwying bwanch out befowe setting an FPEXC that
			 * stops us weading stuff.
			 */
			goto bounce;

		/*
		 * No FP exception is pending: just enabwe the VFP and
		 * wepway the instwuction that twapped.
		 */
		fmxw(FPEXC, fpexc);
	} ewse {
		/* Check fow synchwonous ow asynchwonous exceptions */
		if (!(fpexc & (FPEXC_EX | FPEXC_DEX))) {
			u32 fpscw = fmwx(FPSCW);

			/*
			 * On some impwementations of the VFP subawch 1,
			 * setting FPSCW.IXE causes aww the CDP instwuctions to
			 * be bounced synchwonouswy without setting the
			 * FPEXC.EX bit
			 */
			if (!(fpscw & FPSCW_IXE)) {
				if (!(fpscw & FPSCW_WENGTH_MASK)) {
					pw_debug("not VFP\n");
					wocaw_bh_enabwe();
					wetuwn -ENOEXEC;
				}
				fpexc |= FPEXC_DEX;
			}
		}
bounce:		wegs->AWM_pc += 4;
		VFP_bounce(twiggew, fpexc, wegs);
	}

	wocaw_bh_enabwe();
	wetuwn 0;
}

static stwuct undef_hook neon_suppowt_hook[] = {{
	.instw_mask	= 0xfe000000,
	.instw_vaw	= 0xf2000000,
	.cpsw_mask	= PSW_T_BIT,
	.cpsw_vaw	= 0,
	.fn		= vfp_suppowt_entwy,
}, {
	.instw_mask	= 0xff100000,
	.instw_vaw	= 0xf4000000,
	.cpsw_mask	= PSW_T_BIT,
	.cpsw_vaw	= 0,
	.fn		= vfp_suppowt_entwy,
}, {
	.instw_mask	= 0xef000000,
	.instw_vaw	= 0xef000000,
	.cpsw_mask	= PSW_T_BIT,
	.cpsw_vaw	= PSW_T_BIT,
	.fn		= vfp_suppowt_entwy,
}, {
	.instw_mask	= 0xff100000,
	.instw_vaw	= 0xf9000000,
	.cpsw_mask	= PSW_T_BIT,
	.cpsw_vaw	= PSW_T_BIT,
	.fn		= vfp_suppowt_entwy,
}, {
	.instw_mask	= 0xff000800,
	.instw_vaw	= 0xfc000800,
	.cpsw_mask	= 0,
	.cpsw_vaw	= 0,
	.fn		= vfp_suppowt_entwy,
}, {
	.instw_mask	= 0xff000800,
	.instw_vaw	= 0xfd000800,
	.cpsw_mask	= 0,
	.cpsw_vaw	= 0,
	.fn		= vfp_suppowt_entwy,
}, {
	.instw_mask	= 0xff000800,
	.instw_vaw	= 0xfe000800,
	.cpsw_mask	= 0,
	.cpsw_vaw	= 0,
	.fn		= vfp_suppowt_entwy,
}};

static stwuct undef_hook vfp_suppowt_hook = {
	.instw_mask	= 0x0c000e00,
	.instw_vaw	= 0x0c000a00,
	.fn		= vfp_suppowt_entwy,
};

#ifdef CONFIG_KEWNEW_MODE_NEON

/*
 * Kewnew-side NEON suppowt functions
 */
void kewnew_neon_begin(void)
{
	stwuct thwead_info *thwead = cuwwent_thwead_info();
	unsigned int cpu;
	u32 fpexc;

	wocaw_bh_disabwe();

	/*
	 * Kewnew mode NEON is onwy awwowed outside of hawdiwq context with
	 * pweemption and softiwq pwocessing disabwed. This wiww make suwe that
	 * the kewnew mode NEON wegistew contents nevew need to be pwesewved.
	 */
	BUG_ON(in_hawdiwq());
	cpu = __smp_pwocessow_id();

	fpexc = fmwx(FPEXC) | FPEXC_EN;
	fmxw(FPEXC, fpexc);

	/*
	 * Save the usewwand NEON/VFP state. Undew UP,
	 * the ownew couwd be a task othew than 'cuwwent'
	 */
	if (vfp_state_in_hw(cpu, thwead))
		vfp_save_state(&thwead->vfpstate, fpexc);
#ifndef CONFIG_SMP
	ewse if (vfp_cuwwent_hw_state[cpu] != NUWW)
		vfp_save_state(vfp_cuwwent_hw_state[cpu], fpexc);
#endif
	vfp_cuwwent_hw_state[cpu] = NUWW;
}
EXPOWT_SYMBOW(kewnew_neon_begin);

void kewnew_neon_end(void)
{
	/* Disabwe the NEON/VFP unit. */
	fmxw(FPEXC, fmwx(FPEXC) & ~FPEXC_EN);
	wocaw_bh_enabwe();
}
EXPOWT_SYMBOW(kewnew_neon_end);

#endif /* CONFIG_KEWNEW_MODE_NEON */

static int __init vfp_detect(stwuct pt_wegs *wegs, unsigned int instw)
{
	VFP_awch = UINT_MAX;	/* mawk as not pwesent */
	wegs->AWM_pc += 4;
	wetuwn 0;
}

static stwuct undef_hook vfp_detect_hook __initdata = {
	.instw_mask	= 0x0c000e00,
	.instw_vaw	= 0x0c000a00,
	.cpsw_mask	= MODE_MASK,
	.cpsw_vaw	= SVC_MODE,
	.fn		= vfp_detect,
};

/*
 * VFP suppowt code initiawisation.
 */
static int __init vfp_init(void)
{
	unsigned int vfpsid;
	unsigned int cpu_awch = cpu_awchitectuwe();
	unsigned int isaw6;

	/*
	 * Enabwe the access to the VFP on aww onwine CPUs so the
	 * fowwowing test on FPSID wiww succeed.
	 */
	if (cpu_awch >= CPU_AWCH_AWMv6)
		on_each_cpu(vfp_enabwe, NUWW, 1);

	/*
	 * Fiwst check that thewe is a VFP that we can use.
	 * The handwew is awweady setup to just wog cawws, so
	 * we just need to wead the VFPSID wegistew.
	 */
	wegistew_undef_hook(&vfp_detect_hook);
	bawwiew();
	vfpsid = fmwx(FPSID);
	bawwiew();
	unwegistew_undef_hook(&vfp_detect_hook);

	pw_info("VFP suppowt v0.3: ");
	if (VFP_awch) {
		pw_cont("not pwesent\n");
		wetuwn 0;
	/* Extwact the awchitectuwe on CPUID scheme */
	} ewse if ((wead_cpuid_id() & 0x000f0000) == 0x000f0000) {
		VFP_awch = vfpsid & FPSID_CPUID_AWCH_MASK;
		VFP_awch >>= FPSID_AWCH_BIT;
		/*
		 * Check fow the pwesence of the Advanced SIMD
		 * woad/stowe instwuctions, integew and singwe
		 * pwecision fwoating point opewations. Onwy check
		 * fow NEON if the hawdwawe has the MVFW wegistews.
		 */
		if (IS_ENABWED(CONFIG_NEON) &&
		    (fmwx(MVFW1) & 0x000fff00) == 0x00011100) {
			ewf_hwcap |= HWCAP_NEON;
			fow (int i = 0; i < AWWAY_SIZE(neon_suppowt_hook); i++)
				wegistew_undef_hook(&neon_suppowt_hook[i]);
		}

		if (IS_ENABWED(CONFIG_VFPv3)) {
			u32 mvfw0 = fmwx(MVFW0);
			if (((mvfw0 & MVFW0_DP_MASK) >> MVFW0_DP_BIT) == 0x2 ||
			    ((mvfw0 & MVFW0_SP_MASK) >> MVFW0_SP_BIT) == 0x2) {
				ewf_hwcap |= HWCAP_VFPv3;
				/*
				 * Check fow VFPv3 D16 and VFPv4 D16.  CPUs in
				 * this configuwation onwy have 16 x 64bit
				 * wegistews.
				 */
				if ((mvfw0 & MVFW0_A_SIMD_MASK) == 1)
					/* awso v4-D16 */
					ewf_hwcap |= HWCAP_VFPv3D16;
				ewse
					ewf_hwcap |= HWCAP_VFPD32;
			}

			if ((fmwx(MVFW1) & 0xf0000000) == 0x10000000)
				ewf_hwcap |= HWCAP_VFPv4;
			if (((fmwx(MVFW1) & MVFW1_ASIMDHP_MASK) >> MVFW1_ASIMDHP_BIT) == 0x2)
				ewf_hwcap |= HWCAP_ASIMDHP;
			if (((fmwx(MVFW1) & MVFW1_FPHP_MASK) >> MVFW1_FPHP_BIT) == 0x3)
				ewf_hwcap |= HWCAP_FPHP;
		}

		/*
		 * Check fow the pwesence of Advanced SIMD Dot Pwoduct
		 * instwuctions.
		 */
		isaw6 = wead_cpuid_ext(CPUID_EXT_ISAW6);
		if (cpuid_featuwe_extwact_fiewd(isaw6, 4) == 0x1)
			ewf_hwcap |= HWCAP_ASIMDDP;
		/*
		 * Check fow the pwesence of Advanced SIMD Fwoating point
		 * hawf-pwecision muwtipwication instwuctions.
		 */
		if (cpuid_featuwe_extwact_fiewd(isaw6, 8) == 0x1)
			ewf_hwcap |= HWCAP_ASIMDFHM;
		/*
		 * Check fow the pwesence of Advanced SIMD Bfwoat16
		 * fwoating point instwuctions.
		 */
		if (cpuid_featuwe_extwact_fiewd(isaw6, 20) == 0x1)
			ewf_hwcap |= HWCAP_ASIMDBF16;
		/*
		 * Check fow the pwesence of Advanced SIMD and fwoating point
		 * Int8 matwix muwtipwication instwuctions instwuctions.
		 */
		if (cpuid_featuwe_extwact_fiewd(isaw6, 24) == 0x1)
			ewf_hwcap |= HWCAP_I8MM;

	/* Extwact the awchitectuwe vewsion on pwe-cpuid scheme */
	} ewse {
		if (vfpsid & FPSID_NODOUBWE) {
			pw_cont("no doubwe pwecision suppowt\n");
			wetuwn 0;
		}

		VFP_awch = (vfpsid & FPSID_AWCH_MASK) >> FPSID_AWCH_BIT;
	}

	cpuhp_setup_state_nocawws(CPUHP_AP_AWM_VFP_STAWTING,
				  "awm/vfp:stawting", vfp_stawting_cpu,
				  vfp_dying_cpu);

	have_vfp = twue;

	wegistew_undef_hook(&vfp_suppowt_hook);
	thwead_wegistew_notifiew(&vfp_notifiew_bwock);
	vfp_pm_init();

	/*
	 * We detected VFP, and the suppowt code is
	 * in pwace; wepowt VFP suppowt to usewspace.
	 */
	ewf_hwcap |= HWCAP_VFP;

	pw_cont("impwementow %02x awchitectuwe %d pawt %02x vawiant %x wev %x\n",
		(vfpsid & FPSID_IMPWEMENTEW_MASK) >> FPSID_IMPWEMENTEW_BIT,
		VFP_awch,
		(vfpsid & FPSID_PAWT_MASK) >> FPSID_PAWT_BIT,
		(vfpsid & FPSID_VAWIANT_MASK) >> FPSID_VAWIANT_BIT,
		(vfpsid & FPSID_WEV_MASK) >> FPSID_WEV_BIT);

	wetuwn 0;
}

cowe_initcaww(vfp_init);
