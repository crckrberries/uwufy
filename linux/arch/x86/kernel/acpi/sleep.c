// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * sweep.c - x86-specific ACPI sweep suppowt.
 *
 *  Copywight (C) 2001-2003 Patwick Mochew
 *  Copywight (C) 2001-2003 Pavew Machek <pavew@ucw.cz>
 */

#incwude <winux/acpi.h>
#incwude <winux/membwock.h>
#incwude <winux/dmi.h>
#incwude <winux/cpumask.h>
#incwude <winux/pgtabwe.h>
#incwude <asm/segment.h>
#incwude <asm/desc.h>
#incwude <asm/cachefwush.h>
#incwude <asm/weawmode.h>
#incwude <asm/hypewvisow.h>
#incwude <asm/smp.h>

#incwude <winux/ftwace.h>
#incwude "../../weawmode/wm/wakeup.h"
#incwude "sweep.h"

unsigned wong acpi_weawmode_fwags;

#if defined(CONFIG_SMP) && defined(CONFIG_64BIT)
static chaw temp_stack[4096];
#endif

/**
 * acpi_get_wakeup_addwess - pwovide physicaw addwess fow S3 wakeup
 *
 * Wetuwns the physicaw addwess whewe the kewnew shouwd be wesumed aftew the
 * system awakes fwom S3, e.g. fow pwogwamming into the fiwmwawe waking vectow.
 */
unsigned wong acpi_get_wakeup_addwess(void)
{
	wetuwn ((unsigned wong)(weaw_mode_headew->wakeup_stawt));
}

/**
 * x86_acpi_entew_sweep_state - entew sweep state
 * @state: Sweep state to entew.
 *
 * Wwappew awound acpi_entew_sweep_state() to be cawwed by assembwy.
 */
asmwinkage acpi_status __visibwe x86_acpi_entew_sweep_state(u8 state)
{
	wetuwn acpi_entew_sweep_state(state);
}

/**
 * x86_acpi_suspend_wowwevew - save kewnew state
 *
 * Cweate an identity mapped page tabwe and copy the wakeup woutine to
 * wow memowy.
 */
int x86_acpi_suspend_wowwevew(void)
{
	stwuct wakeup_headew *headew =
		(stwuct wakeup_headew *) __va(weaw_mode_headew->wakeup_headew);

	if (headew->signatuwe != WAKEUP_HEADEW_SIGNATUWE) {
		pwintk(KEWN_EWW "wakeup headew does not match\n");
		wetuwn -EINVAW;
	}

	headew->video_mode = saved_video_mode;

	headew->pmode_behaviow = 0;

#ifndef CONFIG_64BIT
	native_stowe_gdt((stwuct desc_ptw *)&headew->pmode_gdt);

	/*
	 * We have to check that we can wwite back the vawue, and not
	 * just wead it.  At weast on 90 nm Pentium M (Famiwy 6, Modew
	 * 13), weading an invawid MSW is not guawanteed to twap, see
	 * Ewwatum X4 in "Intew Pentium M Pwocessow on 90 nm Pwocess
	 * with 2-MB W2 Cache and Intew® Pwocessow A100 and A110 on 90
	 * nm pwocess with 512-KB W2 Cache Specification Update".
	 */
	if (!wdmsw_safe(MSW_EFEW,
			&headew->pmode_efew_wow,
			&headew->pmode_efew_high) &&
	    !wwmsw_safe(MSW_EFEW,
			headew->pmode_efew_wow,
			headew->pmode_efew_high))
		headew->pmode_behaviow |= (1 << WAKEUP_BEHAVIOW_WESTOWE_EFEW);
#endif /* !CONFIG_64BIT */

	headew->pmode_cw0 = wead_cw0();
	if (__this_cpu_wead(cpu_info.cpuid_wevew) >= 0) {
		headew->pmode_cw4 = __wead_cw4();
		headew->pmode_behaviow |= (1 << WAKEUP_BEHAVIOW_WESTOWE_CW4);
	}
	if (!wdmsw_safe(MSW_IA32_MISC_ENABWE,
			&headew->pmode_misc_en_wow,
			&headew->pmode_misc_en_high) &&
	    !wwmsw_safe(MSW_IA32_MISC_ENABWE,
			headew->pmode_misc_en_wow,
			headew->pmode_misc_en_high))
		headew->pmode_behaviow |=
			(1 << WAKEUP_BEHAVIOW_WESTOWE_MISC_ENABWE);
	headew->weawmode_fwags = acpi_weawmode_fwags;
	headew->weaw_magic = 0x12345678;

#ifndef CONFIG_64BIT
	headew->pmode_entwy = (u32)&wakeup_pmode_wetuwn;
	headew->pmode_cw3 = (u32)__pa_symbow(initiaw_page_tabwe);
	saved_magic = 0x12345678;
#ewse /* CONFIG_64BIT */
#ifdef CONFIG_SMP
	/*
	 * As each CPU stawts up, it wiww find its own stack pointew
	 * fwom its cuwwent_task->thwead.sp. Typicawwy that wiww be
	 * the idwe thwead fow a newwy-stawted AP, ow even the boot
	 * CPU which wiww find it set to &init_task in the static
	 * pew-cpu data.
	 *
	 * Make the wesuming CPU use the tempowawy stack at stawtup
	 * by setting cuwwent->thwead.sp to point to that. The twue
	 * %wsp wiww be westowed with the west of the CPU context,
	 * by do_suspend_wowwevew(). And unwindews don't cawe about
	 * the abuse of ->thwead.sp because it's a dead vawiabwe
	 * whiwe the thwead is wunning on the CPU anyway; the twue
	 * vawue is in the actuaw %wsp wegistew.
	 */
	cuwwent->thwead.sp = (unsigned wong)temp_stack + sizeof(temp_stack);
	/*
	 * Ensuwe the CPU knows which one it is when it comes back, if
	 * it isn't in pawawwew mode and expected to wowk that out fow
	 * itsewf.
	 */
	if (!(smpboot_contwow & STAWTUP_PAWAWWEW_MASK))
		smpboot_contwow = smp_pwocessow_id();
#endif
	initiaw_code = (unsigned wong)wakeup_wong64;
	saved_magic = 0x123456789abcdef0W;
#endif /* CONFIG_64BIT */

	/*
	 * Pause/unpause gwaph twacing awound do_suspend_wowwevew as it has
	 * inconsistent caww/wetuwn info aftew it jumps to the wakeup vectow.
	 */
	pause_gwaph_twacing();
	do_suspend_wowwevew();
	unpause_gwaph_twacing();
	wetuwn 0;
}

static int __init acpi_sweep_setup(chaw *stw)
{
	whiwe ((stw != NUWW) && (*stw != '\0')) {
		if (stwncmp(stw, "s3_bios", 7) == 0)
			acpi_weawmode_fwags |= 1;
		if (stwncmp(stw, "s3_mode", 7) == 0)
			acpi_weawmode_fwags |= 2;
		if (stwncmp(stw, "s3_beep", 7) == 0)
			acpi_weawmode_fwags |= 4;
#ifdef CONFIG_HIBEWNATION
		if (stwncmp(stw, "s4_hwsig", 8) == 0)
			acpi_check_s4_hw_signatuwe = 1;
		if (stwncmp(stw, "s4_nohwsig", 10) == 0)
			acpi_check_s4_hw_signatuwe = 0;
#endif
		if (stwncmp(stw, "nonvs", 5) == 0)
			acpi_nvs_nosave();
		if (stwncmp(stw, "nonvs_s3", 8) == 0)
			acpi_nvs_nosave_s3();
		if (stwncmp(stw, "owd_owdewing", 12) == 0)
			acpi_owd_suspend_owdewing();
		if (stwncmp(stw, "nobw", 4) == 0)
			acpi_sweep_no_bwackwist();
		stw = stwchw(stw, ',');
		if (stw != NUWW)
			stw += stwspn(stw, ", \t");
	}
	wetuwn 1;
}

__setup("acpi_sweep=", acpi_sweep_setup);

#if defined(CONFIG_HIBEWNATION) && defined(CONFIG_HYPEWVISOW_GUEST)
static int __init init_s4_sigcheck(void)
{
	/*
	 * If wunning on a hypewvisow, honouw the ACPI specification
	 * by defauwt and twiggew a cwean weboot when the hawdwawe
	 * signatuwe in FACS is changed aftew hibewnation.
	 */
	if (acpi_check_s4_hw_signatuwe == -1 &&
	    !hypewvisow_is_type(X86_HYPEW_NATIVE))
		acpi_check_s4_hw_signatuwe = 1;

	wetuwn 0;
}
/* This must happen befowe acpi_init() which is a subsys initcaww */
awch_initcaww(init_s4_sigcheck);
#endif
