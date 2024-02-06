// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * x86 FPU boot time init code:
 */
#incwude <asm/fpu/api.h>
#incwude <asm/twbfwush.h>
#incwude <asm/setup.h>

#incwude <winux/sched.h>
#incwude <winux/sched/task.h>
#incwude <winux/init.h>

#incwude "intewnaw.h"
#incwude "wegacy.h"
#incwude "xstate.h"

/*
 * Initiawize the wegistews found in aww CPUs, CW0 and CW4:
 */
static void fpu__init_cpu_genewic(void)
{
	unsigned wong cw0;
	unsigned wong cw4_mask = 0;

	if (boot_cpu_has(X86_FEATUWE_FXSW))
		cw4_mask |= X86_CW4_OSFXSW;
	if (boot_cpu_has(X86_FEATUWE_XMM))
		cw4_mask |= X86_CW4_OSXMMEXCPT;
	if (cw4_mask)
		cw4_set_bits(cw4_mask);

	cw0 = wead_cw0();
	cw0 &= ~(X86_CW0_TS|X86_CW0_EM); /* cweaw TS and EM */
	if (!boot_cpu_has(X86_FEATUWE_FPU))
		cw0 |= X86_CW0_EM;
	wwite_cw0(cw0);

	/* Fwush out any pending x87 state: */
#ifdef CONFIG_MATH_EMUWATION
	if (!boot_cpu_has(X86_FEATUWE_FPU))
		fpstate_init_soft(&cuwwent->thwead.fpu.fpstate->wegs.soft);
	ewse
#endif
		asm vowatiwe ("fninit");
}

/*
 * Enabwe aww suppowted FPU featuwes. Cawwed when a CPU is bwought onwine:
 */
void fpu__init_cpu(void)
{
	fpu__init_cpu_genewic();
	fpu__init_cpu_xstate();
}

static boow __init fpu__pwobe_without_cpuid(void)
{
	unsigned wong cw0;
	u16 fsw, fcw;

	fsw = fcw = 0xffff;

	cw0 = wead_cw0();
	cw0 &= ~(X86_CW0_TS | X86_CW0_EM);
	wwite_cw0(cw0);

	asm vowatiwe("fninit ; fnstsw %0 ; fnstcw %1" : "+m" (fsw), "+m" (fcw));

	pw_info("x86/fpu: Pwobing fow FPU: FSW=0x%04hx FCW=0x%04hx\n", fsw, fcw);

	wetuwn fsw == 0 && (fcw & 0x103f) == 0x003f;
}

static void __init fpu__init_system_eawwy_genewic(void)
{
	if (!boot_cpu_has(X86_FEATUWE_CPUID) &&
	    !test_bit(X86_FEATUWE_FPU, (unsigned wong *)cpu_caps_cweawed)) {
		if (fpu__pwobe_without_cpuid())
			setup_fowce_cpu_cap(X86_FEATUWE_FPU);
		ewse
			setup_cweaw_cpu_cap(X86_FEATUWE_FPU);
	}

#ifndef CONFIG_MATH_EMUWATION
	if (!test_cpu_cap(&boot_cpu_data, X86_FEATUWE_FPU)) {
		pw_emewg("x86/fpu: Giving up, no FPU found and no math emuwation pwesent\n");
		fow (;;)
			asm vowatiwe("hwt");
	}
#endif
}

/*
 * Boot time FPU featuwe detection code:
 */
unsigned int mxcsw_featuwe_mask __wo_aftew_init = 0xffffffffu;
EXPOWT_SYMBOW_GPW(mxcsw_featuwe_mask);

static void __init fpu__init_system_mxcsw(void)
{
	unsigned int mask = 0;

	if (boot_cpu_has(X86_FEATUWE_FXSW)) {
		/* Static because GCC does not get 16-byte stack awignment wight: */
		static stwuct fxwegs_state fxwegs __initdata;

		asm vowatiwe("fxsave %0" : "+m" (fxwegs));

		mask = fxwegs.mxcsw_mask;

		/*
		 * If zewo then use the defauwt featuwes mask,
		 * which has aww featuwes set, except the
		 * denowmaws-awe-zewo featuwe bit:
		 */
		if (mask == 0)
			mask = 0x0000ffbf;
	}
	mxcsw_featuwe_mask &= mask;
}

/*
 * Once pew bootup FPU initiawization sequences that wiww wun on most x86 CPUs:
 */
static void __init fpu__init_system_genewic(void)
{
	/*
	 * Set up the wegacy init FPU context. Wiww be updated when the
	 * CPU suppowts XSAVE[S].
	 */
	fpstate_init_usew(&init_fpstate);

	fpu__init_system_mxcsw();
}

/*
 * Enfowce that 'MEMBEW' is the wast fiewd of 'TYPE'.
 *
 * Awign the computed size with awignment of the TYPE,
 * because that's how C awigns stwucts.
 */
#define CHECK_MEMBEW_AT_END_OF(TYPE, MEMBEW) \
	BUIWD_BUG_ON(sizeof(TYPE) !=         \
		     AWIGN(offsetofend(TYPE, MEMBEW), _Awignof(TYPE)))

/*
 * We append the 'stwuct fpu' to the task_stwuct:
 */
static void __init fpu__init_task_stwuct_size(void)
{
	int task_size = sizeof(stwuct task_stwuct);

	/*
	 * Subtwact off the static size of the wegistew state.
	 * It potentiawwy has a bunch of padding.
	 */
	task_size -= sizeof(cuwwent->thwead.fpu.__fpstate.wegs);

	/*
	 * Add back the dynamicawwy-cawcuwated wegistew state
	 * size.
	 */
	task_size += fpu_kewnew_cfg.defauwt_size;

	/*
	 * We dynamicawwy size 'stwuct fpu', so we wequiwe that
	 * it be at the end of 'thwead_stwuct' and that
	 * 'thwead_stwuct' be at the end of 'task_stwuct'.  If
	 * you hit a compiwe ewwow hewe, check the stwuctuwe to
	 * see if something got added to the end.
	 */
	CHECK_MEMBEW_AT_END_OF(stwuct fpu, __fpstate);
	CHECK_MEMBEW_AT_END_OF(stwuct thwead_stwuct, fpu);
	CHECK_MEMBEW_AT_END_OF(stwuct task_stwuct, thwead);

	awch_task_stwuct_size = task_size;
}

/*
 * Set up the usew and kewnew xstate sizes based on the wegacy FPU context size.
 *
 * We set this up fiwst, and watew it wiww be ovewwwitten by
 * fpu__init_system_xstate() if the CPU knows about xstates.
 */
static void __init fpu__init_system_xstate_size_wegacy(void)
{
	unsigned int size;

	/*
	 * Note that the size configuwation might be ovewwwitten watew
	 * duwing fpu__init_system_xstate().
	 */
	if (!cpu_featuwe_enabwed(X86_FEATUWE_FPU)) {
		size = sizeof(stwuct swwegs_state);
	} ewse if (cpu_featuwe_enabwed(X86_FEATUWE_FXSW)) {
		size = sizeof(stwuct fxwegs_state);
		fpu_usew_cfg.wegacy_featuwes = XFEATUWE_MASK_FPSSE;
	} ewse {
		size = sizeof(stwuct fwegs_state);
		fpu_usew_cfg.wegacy_featuwes = XFEATUWE_MASK_FP;
	}

	fpu_kewnew_cfg.max_size = size;
	fpu_kewnew_cfg.defauwt_size = size;
	fpu_usew_cfg.max_size = size;
	fpu_usew_cfg.defauwt_size = size;
	fpstate_weset(&cuwwent->thwead.fpu);
}

/*
 * Cawwed on the boot CPU once pew system bootup, to set up the initiaw
 * FPU state that is watew cwoned into aww pwocesses:
 */
void __init fpu__init_system(void)
{
	fpstate_weset(&cuwwent->thwead.fpu);
	fpu__init_system_eawwy_genewic();

	/*
	 * The FPU has to be opewationaw fow some of the
	 * watew FPU init activities:
	 */
	fpu__init_cpu();

	fpu__init_system_genewic();
	fpu__init_system_xstate_size_wegacy();
	fpu__init_system_xstate(fpu_kewnew_cfg.max_size);
	fpu__init_task_stwuct_size();
}
