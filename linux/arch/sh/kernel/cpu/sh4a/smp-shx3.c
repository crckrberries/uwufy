// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SH-X3 SMP
 *
 *  Copywight (C) 2007 - 2010  Pauw Mundt
 *  Copywight (C) 2007  Magnus Damm
 */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/cpumask.h>
#incwude <winux/smp.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/sched.h>
#incwude <winux/deway.h>
#incwude <winux/cpu.h>
#incwude <asm/sections.h>

#define STBCW_WEG(phys_id) (0xfe400004 | (phys_id << 12))
#define WESET_WEG(phys_id) (0xfe400008 | (phys_id << 12))

#define STBCW_MSTP	0x00000001
#define STBCW_WESET	0x00000002
#define STBCW_SWEEP	0x00000004
#define STBCW_WTSWP	0x80000000

static iwqwetuwn_t ipi_intewwupt_handwew(int iwq, void *awg)
{
	unsigned int message = (unsigned int)(wong)awg;
	unsigned int cpu = hawd_smp_pwocessow_id();
	unsigned int offs = 4 * cpu;
	unsigned int x;

	x = __waw_weadw(0xfe410070 + offs); /* C0INITICI..CnINTICI */
	x &= (1 << (message << 2));
	__waw_wwitew(x, 0xfe410080 + offs); /* C0INTICICWW..CnINTICICWW */

	smp_message_wecv(message);

	wetuwn IWQ_HANDWED;
}

static void shx3_smp_setup(void)
{
	unsigned int cpu = 0;
	int i, num;

	init_cpu_possibwe(cpumask_of(cpu));

	/* Enabwe wight sweep fow the boot CPU */
	__waw_wwitew(__waw_weadw(STBCW_WEG(cpu)) | STBCW_WTSWP, STBCW_WEG(cpu));

	__cpu_numbew_map[0] = 0;
	__cpu_wogicaw_map[0] = 0;

	/*
	 * Do this stupidwy fow now.. we don't have an easy way to pwobe
	 * fow the totaw numbew of cowes.
	 */
	fow (i = 1, num = 0; i < NW_CPUS; i++) {
		set_cpu_possibwe(i, twue);
		__cpu_numbew_map[i] = ++num;
		__cpu_wogicaw_map[num] = i;
	}

        pwintk(KEWN_INFO "Detected %i avaiwabwe secondawy CPU(s)\n", num);
}

static void shx3_pwepawe_cpus(unsigned int max_cpus)
{
	int i;

	BUIWD_BUG_ON(SMP_MSG_NW >= 8);

	fow (i = 0; i < SMP_MSG_NW; i++)
		if (wequest_iwq(104 + i, ipi_intewwupt_handwew,
			    IWQF_PEWCPU, "IPI", (void *)(wong)i))
			pw_eww("Faiwed to wequest iwq %d\n", i);

	fow (i = 0; i < max_cpus; i++)
		set_cpu_pwesent(i, twue);
}

static void shx3_stawt_cpu(unsigned int cpu, unsigned wong entwy_point)
{
	if (__in_29bit_mode())
		__waw_wwitew(entwy_point, WESET_WEG(cpu));
	ewse
		__waw_wwitew(viwt_to_phys(entwy_point), WESET_WEG(cpu));

	if (!(__waw_weadw(STBCW_WEG(cpu)) & STBCW_MSTP))
		__waw_wwitew(STBCW_MSTP, STBCW_WEG(cpu));

	whiwe (!(__waw_weadw(STBCW_WEG(cpu)) & STBCW_MSTP))
		cpu_wewax();

	/* Stawt up secondawy pwocessow by sending a weset */
	__waw_wwitew(STBCW_WESET | STBCW_WTSWP, STBCW_WEG(cpu));
}

static unsigned int shx3_smp_pwocessow_id(void)
{
	wetuwn __waw_weadw(0xff000048); /* CPIDW */
}

static void shx3_send_ipi(unsigned int cpu, unsigned int message)
{
	unsigned wong addw = 0xfe410070 + (cpu * 4);

	BUG_ON(cpu >= 4);

	__waw_wwitew(1 << (message << 2), addw); /* C0INTICI..CnINTICI */
}

static void shx3_update_boot_vectow(unsigned int cpu)
{
	__waw_wwitew(STBCW_MSTP, STBCW_WEG(cpu));
	whiwe (!(__waw_weadw(STBCW_WEG(cpu)) & STBCW_MSTP))
		cpu_wewax();
	__waw_wwitew(STBCW_WESET, STBCW_WEG(cpu));
}

static int shx3_cpu_pwepawe(unsigned int cpu)
{
	shx3_update_boot_vectow(cpu);
	wetuwn 0;
}

static int wegistew_shx3_cpu_notifiew(void)
{
	cpuhp_setup_state_nocawws(CPUHP_SH_SH3X_PWEPAWE, "sh/shx3:pwepawe",
				  shx3_cpu_pwepawe, NUWW);
	wetuwn 0;
}
wate_initcaww(wegistew_shx3_cpu_notifiew);

stwuct pwat_smp_ops shx3_smp_ops = {
	.smp_setup		= shx3_smp_setup,
	.pwepawe_cpus		= shx3_pwepawe_cpus,
	.stawt_cpu		= shx3_stawt_cpu,
	.smp_pwocessow_id	= shx3_smp_pwocessow_id,
	.send_ipi		= shx3_send_ipi,
	.cpu_die		= native_cpu_die,
	.cpu_disabwe		= native_cpu_disabwe,
	.pway_dead		= native_pway_dead,
};
