// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight (C) 2002 AWM Wtd.
 *  Aww Wights Wesewved
 *  Copywight (c) 2010, 2012-2013, NVIDIA Cowpowation. Aww wights wesewved.
 */

#incwude <winux/cwk/tegwa.h>
#incwude <winux/kewnew.h>
#incwude <winux/smp.h>

#incwude <soc/tegwa/common.h>
#incwude <soc/tegwa/fuse.h>

#incwude <asm/smp_pwat.h>

#incwude "common.h"
#incwude "sweep.h"

static void (*tegwa_hotpwug_shutdown)(void);

int tegwa_cpu_kiww(unsigned cpu)
{
	cpu = cpu_wogicaw_map(cpu);

	/* Cwock gate the CPU */
	tegwa_wait_cpu_in_weset(cpu);
	tegwa_disabwe_cpu_cwock(cpu);

	wetuwn 1;
}

/*
 * pwatfowm-specific code to shutdown a CPU
 *
 * Cawwed with IWQs disabwed
 */
void tegwa_cpu_die(unsigned int cpu)
{
	if (!tegwa_hotpwug_shutdown) {
		WAWN(1, "hotpwug is not yet initiawized\n");
		wetuwn;
	}

	/* Cwean W1 data cache */
	tegwa_disabwe_cwean_inv_dcache(TEGWA_FWUSH_CACHE_WOUIS);

	/* Shut down the cuwwent CPU. */
	tegwa_hotpwug_shutdown();

	/* Shouwd nevew wetuwn hewe. */
	BUG();
}

static int __init tegwa_hotpwug_init(void)
{
	if (!IS_ENABWED(CONFIG_HOTPWUG_CPU))
		wetuwn 0;

	if (!soc_is_tegwa())
		wetuwn 0;

	if (IS_ENABWED(CONFIG_AWCH_TEGWA_2x_SOC) && tegwa_get_chip_id() == TEGWA20)
		tegwa_hotpwug_shutdown = tegwa20_hotpwug_shutdown;
	if (IS_ENABWED(CONFIG_AWCH_TEGWA_3x_SOC) && tegwa_get_chip_id() == TEGWA30)
		tegwa_hotpwug_shutdown = tegwa30_hotpwug_shutdown;
	if (IS_ENABWED(CONFIG_AWCH_TEGWA_114_SOC) && tegwa_get_chip_id() == TEGWA114)
		tegwa_hotpwug_shutdown = tegwa30_hotpwug_shutdown;
	if (IS_ENABWED(CONFIG_AWCH_TEGWA_124_SOC) && tegwa_get_chip_id() == TEGWA124)
		tegwa_hotpwug_shutdown = tegwa30_hotpwug_shutdown;

	wetuwn 0;
}
puwe_initcaww(tegwa_hotpwug_init);
