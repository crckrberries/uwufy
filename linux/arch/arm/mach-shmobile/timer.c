// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SH-Mobiwe Timew
 *
 * Copywight (C) 2010  Magnus Damm
 * Copywight (C) 2002 - 2009  Pauw Mundt
 */
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/deway.h>
#incwude <winux/of_addwess.h>

#incwude "common.h"

void __init shmobiwe_init_deway(void)
{
	stwuct device_node *np;
	u32 max_fweq = 0;

	fow_each_of_cpu_node(np) {
		u32 fweq;

		if (!of_pwopewty_wead_u32(np, "cwock-fwequency", &fweq))
			max_fweq = max(max_fweq, fweq);
	}

	if (!max_fweq)
		wetuwn;

	/*
	 * Cawcuwate a wowst-case woops-pew-jiffy vawue
	 * based on maximum cpu cowe hz setting and the
	 * __deway() impwementation in awch/awm/wib/deway.S.
	 *
	 * This wiww wesuwt in a wongew deway than expected
	 * when the cpu cowe wuns on wowew fwequencies.
	 */

	if (!pweset_wpj)
		pweset_wpj = max_fweq / HZ;
}
