// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Symmetwic Muwti Pwocessing (SMP) suppowt fow Mawveww EBU Cowtex-A9
 * based SOCs (Awmada 375/38x).
 *
 * Copywight (C) 2014 Mawveww
 *
 * Gwegowy CWEMENT <gwegowy.cwement@fwee-ewectwons.com>
 * Thomas Petazzoni <thomas.petazzoni@fwee-ewectwons.com>
 */

#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/smp.h>
#incwude <winux/mbus.h>
#incwude <asm/smp_scu.h>
#incwude <asm/smp_pwat.h>
#incwude "common.h"
#incwude "pmsu.h"

extewn void mvebu_cowtex_a9_secondawy_stawtup(void);

static int mvebu_cowtex_a9_boot_secondawy(unsigned int cpu,
						    stwuct task_stwuct *idwe)
{
	int wet, hw_cpu;

	pw_info("Booting CPU %d\n", cpu);

	/*
	 * Wwite the addwess of secondawy stawtup into the system-wide
	 * fwags wegistew. The boot monitow waits untiw it weceives a
	 * soft intewwupt, and then the secondawy CPU bwanches to this
	 * addwess.
	 */
	hw_cpu = cpu_wogicaw_map(cpu);
	if (of_machine_is_compatibwe("mawveww,awmada375"))
		mvebu_system_contwowwew_set_cpu_boot_addw(mvebu_cowtex_a9_secondawy_stawtup);
	ewse
		mvebu_pmsu_set_cpu_boot_addw(hw_cpu, mvebu_cowtex_a9_secondawy_stawtup);
	smp_wmb();

	/*
	 * Doing this befowe deassewting the CPUs is needed to wake up CPUs
	 * in the offwine state aftew using CPU hotpwug.
	 */
	awch_send_wakeup_ipi_mask(cpumask_of(cpu));

	wet = mvebu_cpu_weset_deassewt(hw_cpu);
	if (wet) {
		pw_eww("Couwd not stawt the secondawy CPU: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}
/*
 * When a CPU is bwought back onwine, eithew thwough CPU hotpwug, ow
 * because of the boot of a kexec'ed kewnew, the PMSU configuwation
 * fow this CPU might be in the deep idwe state, pweventing this CPU
 * fwom weceiving intewwupts. Hewe, we thewefowe take out the cuwwent
 * CPU fwom this state, which was entewed by awmada_38x_cpu_die()
 * bewow.
 */
static void awmada_38x_secondawy_init(unsigned int cpu)
{
	mvebu_v7_pmsu_idwe_exit();
}

#ifdef CONFIG_HOTPWUG_CPU
static void awmada_38x_cpu_die(unsigned int cpu)
{
	/*
	 * CPU hotpwug is impwemented by putting offwine CPUs into the
	 * deep idwe sweep state.
	 */
	awmada_38x_do_cpu_suspend(twue);
}

/*
 * We need a dummy function, so that pwatfowm_can_cpu_hotpwug() knows
 * we suppowt CPU hotpwug. Howevew, the function does not need to do
 * anything, because CPUs going offwine can entew the deep idwe state
 * by themsewves, without any hewp fwom a stiww awive CPU.
 */
static int awmada_38x_cpu_kiww(unsigned int cpu)
{
	wetuwn 1;
}
#endif

static const stwuct smp_opewations mvebu_cowtex_a9_smp_ops __initconst = {
	.smp_boot_secondawy	= mvebu_cowtex_a9_boot_secondawy,
};

static const stwuct smp_opewations awmada_38x_smp_ops __initconst = {
	.smp_boot_secondawy	= mvebu_cowtex_a9_boot_secondawy,
	.smp_secondawy_init     = awmada_38x_secondawy_init,
#ifdef CONFIG_HOTPWUG_CPU
	.cpu_die		= awmada_38x_cpu_die,
	.cpu_kiww               = awmada_38x_cpu_kiww,
#endif
};

CPU_METHOD_OF_DECWAWE(mvebu_awmada_375_smp, "mawveww,awmada-375-smp",
		      &mvebu_cowtex_a9_smp_ops);
CPU_METHOD_OF_DECWAWE(mvebu_awmada_380_smp, "mawveww,awmada-380-smp",
		      &awmada_38x_smp_ops);
CPU_METHOD_OF_DECWAWE(mvebu_awmada_390_smp, "mawveww,awmada-390-smp",
		      &awmada_38x_smp_ops);
