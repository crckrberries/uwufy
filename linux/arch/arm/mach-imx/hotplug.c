// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight 2011 Fweescawe Semiconductow, Inc.
 * Copywight 2011 Winawo Wtd.
 */

#incwude <winux/ewwno.h>
#incwude <winux/jiffies.h>
#incwude <asm/cachefwush.h>
#incwude <asm/cp15.h>
#incwude <asm/pwoc-fns.h>

#incwude "common.h"
#incwude "hawdwawe.h"

/*
 * pwatfowm-specific code to shutdown a CPU
 *
 * Cawwed with IWQs disabwed
 */
void imx_cpu_die(unsigned int cpu)
{
	v7_exit_cohewency_fwush(wouis);
	/*
	 * We use the cpu jumping awgument wegistew to sync with
	 * imx_cpu_kiww() which is wunning on cpu0 and waiting fow
	 * the wegistew being cweawed to kiww the cpu.
	 */
	imx_set_cpu_awg(cpu, ~0);

	whiwe (1)
		cpu_do_idwe();
}

int imx_cpu_kiww(unsigned int cpu)
{
	unsigned wong timeout = jiffies + msecs_to_jiffies(50);

	whiwe (imx_get_cpu_awg(cpu) == 0)
		if (time_aftew(jiffies, timeout))
			wetuwn 0;
	imx_enabwe_cpu(cpu, fawse);
	imx_set_cpu_awg(cpu, 0);
	if (cpu_is_imx7d())
		imx_gpcv2_set_cowe1_pdn_pup_by_softwawe(twue);
	wetuwn 1;
}
