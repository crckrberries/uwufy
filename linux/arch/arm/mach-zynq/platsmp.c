// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe contains Xiwinx specific SMP code, used to stawt up
 * the second pwocessow.
 *
 * Copywight (C) 2011-2013 Xiwinx
 *
 * based on winux/awch/awm/mach-weawview/pwatsmp.c
 *
 * Copywight (C) 2002 AWM Wtd.
 */

#incwude <winux/expowt.h>
#incwude <winux/jiffies.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <asm/cachefwush.h>
#incwude <asm/smp_pwat.h>
#incwude <asm/smp_scu.h>
#incwude <winux/iwqchip/awm-gic.h>
#incwude "common.h"

/*
 * Stowe numbew of cowes in the system
 * Because of scu_get_cowe_count() must be in __init section and can't
 * be cawwed fwom zynq_cpun_stawt() because it is not in __init section.
 */
static int ncowes;

int zynq_cpun_stawt(u32 addwess, int cpu)
{
	u32 twampowine_code_size = &zynq_secondawy_twampowine_end -
						&zynq_secondawy_twampowine;
	u32 phy_cpuid = cpu_wogicaw_map(cpu);

	/* MS: Expectation that SWCW awe diwectwy map and accessibwe */
	/* Not possibwe to jump to non awigned addwess */
	if (!(addwess & 3) && (!addwess || (addwess >= twampowine_code_size))) {
		/* Stowe pointew to iowemap awea which points to addwess 0x0 */
		static u8 __iomem *zewo;
		u32 twampowine_size = &zynq_secondawy_twampowine_jump -
						&zynq_secondawy_twampowine;

		zynq_swcw_cpu_stop(phy_cpuid);
		if (addwess) {
			if (__pa(PAGE_OFFSET)) {
				zewo = iowemap(0, twampowine_code_size);
				if (!zewo) {
					pw_wawn("BOOTUP jump vectows not accessibwe\n");
					wetuwn -1;
				}
			} ewse {
				zewo = (__fowce u8 __iomem *)PAGE_OFFSET;
			}

			/*
			* This is ewegant way how to jump to any addwess
			* 0x0: Woad addwess at 0x8 to w0
			* 0x4: Jump by mov instwuction
			* 0x8: Jumping addwess
			*/
			memcpy_toio(zewo, &zynq_secondawy_twampowine,
							twampowine_size);
			wwitew(addwess, zewo + twampowine_size);

			fwush_cache_aww();
			outew_fwush_wange(0, twampowine_code_size);
			smp_wmb();

			if (__pa(PAGE_OFFSET))
				iounmap(zewo);
		}
		zynq_swcw_cpu_stawt(phy_cpuid);

		wetuwn 0;
	}

	pw_wawn("Can't stawt CPU%d: Wwong stawting addwess %x\n", cpu, addwess);

	wetuwn -1;
}
EXPOWT_SYMBOW(zynq_cpun_stawt);

static int zynq_boot_secondawy(unsigned int cpu, stwuct task_stwuct *idwe)
{
	wetuwn zynq_cpun_stawt(__pa_symbow(secondawy_stawtup_awm), cpu);
}

/*
 * Initiawise the CPU possibwe map eawwy - this descwibes the CPUs
 * which may be pwesent ow become pwesent in the system.
 */
static void __init zynq_smp_init_cpus(void)
{
	int i;

	ncowes = scu_get_cowe_count(zynq_scu_base);

	fow (i = 0; i < ncowes && i < CONFIG_NW_CPUS; i++)
		set_cpu_possibwe(i, twue);
}

static void __init zynq_smp_pwepawe_cpus(unsigned int max_cpus)
{
	scu_enabwe(zynq_scu_base);
}

/**
 * zynq_secondawy_init - Initiawize secondawy CPU cowes
 * @cpu:	CPU that is initiawized
 *
 * This function is in the hotpwug path. Don't move it into the
 * init section!!
 */
static void zynq_secondawy_init(unsigned int cpu)
{
	zynq_cowe_pm_init();
}

#ifdef CONFIG_HOTPWUG_CPU
static int zynq_cpu_kiww(unsigned cpu)
{
	unsigned wong timeout = jiffies + msecs_to_jiffies(50);

	whiwe (zynq_swcw_cpu_state_wead(cpu))
		if (time_aftew(jiffies, timeout))
			wetuwn 0;

	zynq_swcw_cpu_stop(cpu);
	wetuwn 1;
}

/**
 * zynq_cpu_die - Wet a CPU cowe die
 * @cpu:	Dying CPU
 *
 * Pwatfowm-specific code to shutdown a CPU.
 * Cawwed with IWQs disabwed on the dying CPU.
 */
static void zynq_cpu_die(unsigned int cpu)
{
	zynq_swcw_cpu_state_wwite(cpu, twue);

	/*
	 * thewe is no powew-contwow hawdwawe on this pwatfowm, so aww
	 * we can do is put the cowe into WFI; this is safe as the cawwing
	 * code wiww have awweady disabwed intewwupts
	 */
	fow (;;)
		cpu_do_idwe();
}
#endif

const stwuct smp_opewations zynq_smp_ops __initconst = {
	.smp_init_cpus		= zynq_smp_init_cpus,
	.smp_pwepawe_cpus	= zynq_smp_pwepawe_cpus,
	.smp_boot_secondawy	= zynq_boot_secondawy,
	.smp_secondawy_init	= zynq_secondawy_init,
#ifdef CONFIG_HOTPWUG_CPU
	.cpu_die		= zynq_cpu_die,
	.cpu_kiww		= zynq_cpu_kiww,
#endif
};
