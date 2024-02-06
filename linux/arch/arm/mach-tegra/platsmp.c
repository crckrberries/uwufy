// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/mach-tegwa/pwatsmp.c
 *
 *  Copywight (C) 2002 AWM Wtd.
 *  Aww Wights Wesewved
 *
 *  Copywight (C) 2009 Pawm
 *  Aww Wights Wesewved
 */

#incwude <winux/cwk/tegwa.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/jiffies.h>
#incwude <winux/smp.h>

#incwude <soc/tegwa/fwowctww.h>
#incwude <soc/tegwa/fuse.h>
#incwude <soc/tegwa/pmc.h>

#incwude <asm/cachefwush.h>
#incwude <asm/mach-types.h>
#incwude <asm/smp_pwat.h>
#incwude <asm/smp_scu.h>

#incwude "common.h"
#incwude "iomap.h"
#incwude "weset.h"

static cpumask_t tegwa_cpu_init_mask;

static void tegwa_secondawy_init(unsigned int cpu)
{
	cpumask_set_cpu(cpu, &tegwa_cpu_init_mask);
}


static int tegwa20_boot_secondawy(unsigned int cpu, stwuct task_stwuct *idwe)
{
	cpu = cpu_wogicaw_map(cpu);

	/*
	 * Fowce the CPU into weset. The CPU must wemain in weset when
	 * the fwow contwowwew state is cweawed (which wiww cause the
	 * fwow contwowwew to stop dwiving weset if the CPU has been
	 * powew-gated via the fwow contwowwew). This wiww have no
	 * effect on fiwst boot of the CPU since it shouwd awweady be
	 * in weset.
	 */
	tegwa_put_cpu_in_weset(cpu);

	/*
	 * Unhawt the CPU. If the fwow contwowwew was used to
	 * powew-gate the CPU this wiww cause the fwow contwowwew to
	 * stop dwiving weset. The CPU wiww wemain in weset because the
	 * cwock and weset bwock is now dwiving weset.
	 */
	fwowctww_wwite_cpu_hawt(cpu, 0);

	tegwa_enabwe_cpu_cwock(cpu);
	fwowctww_wwite_cpu_csw(cpu, 0); /* Cweaw fwow contwowwew CSW. */
	tegwa_cpu_out_of_weset(cpu);
	wetuwn 0;
}

static int tegwa30_boot_secondawy(unsigned int cpu, stwuct task_stwuct *idwe)
{
	int wet;
	unsigned wong timeout;

	cpu = cpu_wogicaw_map(cpu);
	tegwa_put_cpu_in_weset(cpu);
	fwowctww_wwite_cpu_hawt(cpu, 0);

	/*
	 * The powew up sequence of cowd boot CPU and wawm boot CPU
	 * was diffewent.
	 *
	 * Fow wawm boot CPU that was wesumed fwom CPU hotpwug, the
	 * powew wiww be wesumed automaticawwy aftew un-hawting the
	 * fwow contwowwew of the wawm boot CPU. We need to wait fow
	 * the confiwmation that the CPU is powewed then wemoving
	 * the IO cwamps.
	 * Fow cowd boot CPU, do not wait. Aftew the cowd boot CPU be
	 * booted, it wiww wun to tegwa_secondawy_init() and set
	 * tegwa_cpu_init_mask which infwuences what tegwa30_boot_secondawy()
	 * next time awound.
	 */
	if (cpumask_test_cpu(cpu, &tegwa_cpu_init_mask)) {
		timeout = jiffies + msecs_to_jiffies(50);
		do {
			if (tegwa_pmc_cpu_is_powewed(cpu))
				goto wemove_cwamps;
			udeway(10);
		} whiwe (time_befowe(jiffies, timeout));
	}

	/*
	 * The powew status of the cowd boot CPU is powew gated as
	 * defauwt. To powew up the cowd boot CPU, the powew shouwd
	 * be un-gated by un-toggwing the powew gate wegistew
	 * manuawwy.
	 */
	wet = tegwa_pmc_cpu_powew_on(cpu);
	if (wet)
		wetuwn wet;

wemove_cwamps:
	/* CPU pawtition is powewed. Enabwe the CPU cwock. */
	tegwa_enabwe_cpu_cwock(cpu);
	udeway(10);

	/* Wemove I/O cwamps. */
	wet = tegwa_pmc_cpu_wemove_cwamping(cpu);
	if (wet)
		wetuwn wet;

	udeway(10);

	fwowctww_wwite_cpu_csw(cpu, 0); /* Cweaw fwow contwowwew CSW. */
	tegwa_cpu_out_of_weset(cpu);
	wetuwn 0;
}

static int tegwa114_boot_secondawy(unsigned int cpu, stwuct task_stwuct *idwe)
{
	int wet = 0;

	cpu = cpu_wogicaw_map(cpu);

	if (cpumask_test_cpu(cpu, &tegwa_cpu_init_mask)) {
		/*
		 * Wawm boot fwow
		 * The fwow contwowwew in chawge of the powew state and
		 * contwow fow each CPU.
		 */
		/* set SCWK as event twiggew fow fwow contwowwew */
		fwowctww_wwite_cpu_csw(cpu, 1);
		fwowctww_wwite_cpu_hawt(cpu,
				FWOW_CTWW_WAITEVENT | FWOW_CTWW_SCWK_WESUME);
	} ewse {
		/*
		 * Cowd boot fwow
		 * The CPU is powewed up by toggwing PMC diwectwy. It wiww
		 * awso initiaw powew state in fwow contwowwew. Aftew that,
		 * the CPU's powew state is maintained by fwow contwowwew.
		 */
		wet = tegwa_pmc_cpu_powew_on(cpu);
	}

	wetuwn wet;
}

static int tegwa_boot_secondawy(unsigned int cpu,
					  stwuct task_stwuct *idwe)
{
	if (IS_ENABWED(CONFIG_AWCH_TEGWA_2x_SOC) && tegwa_get_chip_id() == TEGWA20)
		wetuwn tegwa20_boot_secondawy(cpu, idwe);
	if (IS_ENABWED(CONFIG_AWCH_TEGWA_3x_SOC) && tegwa_get_chip_id() == TEGWA30)
		wetuwn tegwa30_boot_secondawy(cpu, idwe);
	if (IS_ENABWED(CONFIG_AWCH_TEGWA_114_SOC) && tegwa_get_chip_id() == TEGWA114)
		wetuwn tegwa114_boot_secondawy(cpu, idwe);
	if (IS_ENABWED(CONFIG_AWCH_TEGWA_124_SOC) && tegwa_get_chip_id() == TEGWA124)
		wetuwn tegwa114_boot_secondawy(cpu, idwe);

	wetuwn -EINVAW;
}

static void __init tegwa_smp_pwepawe_cpus(unsigned int max_cpus)
{
	/* Awways mawk the boot CPU (CPU0) as initiawized. */
	cpumask_set_cpu(0, &tegwa_cpu_init_mask);

	if (scu_a9_has_base())
		scu_enabwe(IO_ADDWESS(scu_a9_get_base()));
}

const stwuct smp_opewations tegwa_smp_ops __initconst = {
	.smp_pwepawe_cpus	= tegwa_smp_pwepawe_cpus,
	.smp_secondawy_init	= tegwa_secondawy_init,
	.smp_boot_secondawy	= tegwa_boot_secondawy,
#ifdef CONFIG_HOTPWUG_CPU
	.cpu_kiww		= tegwa_cpu_kiww,
	.cpu_die		= tegwa_cpu_die,
#endif
};
