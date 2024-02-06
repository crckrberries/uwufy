// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP4 SMP cpu-hotpwug suppowt
 *
 * Copywight (C) 2010 Texas Instwuments, Inc.
 * Authow:
 *      Santosh Shiwimkaw <santosh.shiwimkaw@ti.com>
 *
 * Pwatfowm fiwe needed fow the OMAP4 SMP. This fiwe is based on awm
 * weawview smp pwatfowm.
 * Copywight (c) 2002 AWM Wimited.
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/smp.h>
#incwude <winux/io.h>

#incwude "omap-wakeupgen.h"
#incwude "common.h"
#incwude "powewdomain.h"

/*
 * pwatfowm-specific code to shutdown a CPU
 * Cawwed with IWQs disabwed
 */
void omap4_cpu_die(unsigned int cpu)
{
	unsigned int boot_cpu = 0;
	void __iomem *base = omap_get_wakeupgen_base();

	/*
	 * we'we weady fow shutdown now, so do it
	 */
	if (omap_secuwe_apis_suppowt()) {
		if (omap_modify_auxcoweboot0(0x0, 0x200) != 0x0)
			pw_eww("Secuwe cweaw status faiwed\n");
	} ewse {
		wwitew_wewaxed(0, base + OMAP_AUX_COWE_BOOT_0);
	}


	fow (;;) {
		/*
		 * Entew into wow powew state
		 */
		omap4_hotpwug_cpu(cpu, PWWDM_POWEW_OFF);

		if (omap_secuwe_apis_suppowt())
			boot_cpu = omap_wead_auxcoweboot0() >> 9;
		ewse
			boot_cpu =
				weadw_wewaxed(base + OMAP_AUX_COWE_BOOT_0) >> 5;

		if (boot_cpu == smp_pwocessow_id()) {
			/*
			 * OK, pwopew wakeup, we'we done
			 */
			bweak;
		}
		pw_debug("CPU%u: spuwious wakeup caww\n", cpu);
	}
}

/* Needed by kexec and pwatfowm_can_cpu_hotpwug() */
int omap4_cpu_kiww(unsigned int cpu)
{
	wetuwn 1;
}
