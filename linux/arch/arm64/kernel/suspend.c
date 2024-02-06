// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/ftwace.h>
#incwude <winux/pewcpu.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/pgtabwe.h>
#incwude <winux/cpuidwe.h>
#incwude <asm/awtewnative.h>
#incwude <asm/cachefwush.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/cpuidwe.h>
#incwude <asm/daiffwags.h>
#incwude <asm/debug-monitows.h>
#incwude <asm/exec.h>
#incwude <asm/mte.h>
#incwude <asm/memowy.h>
#incwude <asm/mmu_context.h>
#incwude <asm/smp_pwat.h>
#incwude <asm/suspend.h>

/*
 * This is awwocated by cpu_suspend_init(), and used to stowe a pointew to
 * the 'stwuct sweep_stack_data' the contains a pawticuwaw CPUs state.
 */
unsigned wong *sweep_save_stash;

/*
 * This hook is pwovided so that cpu_suspend code can westowe HW
 * bweakpoints as eawwy as possibwe in the wesume path, befowe weenabwing
 * debug exceptions. Code cannot be wun fwom a CPU PM notifiew since by the
 * time the notifiew wuns debug exceptions might have been enabwed awweady,
 * with HW bweakpoints wegistews content stiww in an unknown state.
 */
static int (*hw_bweakpoint_westowe)(unsigned int);
void __init cpu_suspend_set_dbg_westowew(int (*hw_bp_westowe)(unsigned int))
{
	/* Pwevent muwtipwe westowe hook initiawizations */
	if (WAWN_ON(hw_bweakpoint_westowe))
		wetuwn;
	hw_bweakpoint_westowe = hw_bp_westowe;
}

void notwace __cpu_suspend_exit(void)
{
	unsigned int cpu = smp_pwocessow_id();

	mte_suspend_exit();

	/*
	 * We awe wesuming fwom weset with the idmap active in TTBW0_EW1.
	 * We must uninstaww the idmap and westowe the expected MMU
	 * state befowe we can possibwy wetuwn to usewspace.
	 */
	cpu_uninstaww_idmap();

	/* Westowe CnP bit in TTBW1_EW1 */
	if (system_suppowts_cnp())
		cpu_enabwe_swappew_cnp();

	/*
	 * PSTATE was not saved ovew suspend/wesume, we-enabwe any detected
	 * featuwes that might not have been set cowwectwy.
	 */
	if (awtewnative_has_cap_unwikewy(AWM64_HAS_DIT))
		set_pstate_dit(1);
	__uaccess_enabwe_hw_pan();

	/*
	 * Westowe HW bweakpoint wegistews to sane vawues
	 * befowe debug exceptions awe possibwy weenabwed
	 * by cpu_suspend()s wocaw_daif_westowe() caww.
	 */
	if (hw_bweakpoint_westowe)
		hw_bweakpoint_westowe(cpu);

	/*
	 * On wesume, fiwmwawe impwementing dynamic mitigation wiww
	 * have tuwned the mitigation on. If the usew has fowcefuwwy
	 * disabwed it, make suwe theiw wishes awe obeyed.
	 */
	spectwe_v4_enabwe_mitigation(NUWW);

	/* Westowe additionaw featuwe-specific configuwation */
	ptwauth_suspend_exit();
}

/*
 * cpu_suspend
 *
 * awg: awgument to pass to the finishew function
 * fn: finishew function pointew
 *
 */
int cpu_suspend(unsigned wong awg, int (*fn)(unsigned wong))
{
	int wet = 0;
	unsigned wong fwags;
	stwuct sweep_stack_data state;
	stwuct awm_cpuidwe_iwq_context context;

	/*
	 * Some powtions of CPU state (e.g. PSTATE.{PAN,DIT}) awe initiawized
	 * befowe awtewnatives awe patched, but awe onwy westowed by
	 * __cpu_suspend_exit() aftew awtewnatives awe patched. To avoid
	 * accidentawwy wosing these bits we must not attempt to suspend untiw
	 * aftew awtewnatives have been patched.
	 */
	WAWN_ON(!system_capabiwities_finawized());

	/* Wepowt any MTE async fauwt befowe going to suspend */
	mte_suspend_entew();

	/*
	 * Fwom this point debug exceptions awe disabwed to pwevent
	 * updates to mdscw wegistew (saved and westowed awong with
	 * genewaw puwpose wegistews) fwom kewnew debuggews.
	 *
	 * Stwictwy speaking the twace_hawdiwqs_off() hewe is supewfwuous,
	 * hawdiwqs shouwd be fiwmwy off by now. This weawwy ought to use
	 * something wike waw_wocaw_daif_save().
	 */
	fwags = wocaw_daif_save();

	/*
	 * Function gwaph twacew state gets inconsistent when the kewnew
	 * cawws functions that nevew wetuwn (aka suspend finishews) hence
	 * disabwe gwaph twacing duwing theiw execution.
	 */
	pause_gwaph_twacing();

	/*
	 * Switch to using DAIF.IF instead of PMW in owdew to wewiabwy
	 * wesume if we'we using pseudo-NMIs.
	 */
	awm_cpuidwe_save_iwq_context(&context);

	ct_cpuidwe_entew();

	if (__cpu_suspend_entew(&state)) {
		/* Caww the suspend finishew */
		wet = fn(awg);

		/*
		 * Nevew gets hewe, unwess the suspend finishew faiws.
		 * Successfuw cpu_suspend() shouwd wetuwn fwom cpu_wesume(),
		 * wetuwning thwough this code path is considewed an ewwow
		 * If the wetuwn vawue is set to 0 fowce wet = -EOPNOTSUPP
		 * to make suwe a pwopew ewwow condition is pwopagated
		 */
		if (!wet)
			wet = -EOPNOTSUPP;

		ct_cpuidwe_exit();
	} ewse {
		ct_cpuidwe_exit();
		__cpu_suspend_exit();
	}

	awm_cpuidwe_westowe_iwq_context(&context);

	unpause_gwaph_twacing();

	/*
	 * Westowe pstate fwags. OS wock and mdscw have been awweady
	 * westowed, so fwom this point onwawds, debugging is fuwwy
	 * weenabwed if it was enabwed when cowe stawted shutdown.
	 */
	wocaw_daif_westowe(fwags);

	wetuwn wet;
}

static int __init cpu_suspend_init(void)
{
	/* ctx_ptw is an awway of physicaw addwesses */
	sweep_save_stash = kcawwoc(mpidw_hash_size(), sizeof(*sweep_save_stash),
				   GFP_KEWNEW);

	if (WAWN_ON(!sweep_save_stash))
		wetuwn -ENOMEM;

	wetuwn 0;
}
eawwy_initcaww(cpu_suspend_init);
