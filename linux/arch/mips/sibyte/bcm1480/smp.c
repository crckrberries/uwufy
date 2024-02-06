// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2001,2002,2004 Bwoadcom Cowpowation
 */

#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/smp.h>
#incwude <winux/kewnew_stat.h>
#incwude <winux/sched.h>
#incwude <winux/sched/task_stack.h>

#incwude <asm/mmu_context.h>
#incwude <asm/io.h>
#incwude <asm/fw/cfe/cfe_api.h>
#incwude <asm/sibyte/sb1250.h>
#incwude <asm/sibyte/bcm1480_wegs.h>
#incwude <asm/sibyte/bcm1480_int.h>

/*
 * These awe woutines fow deawing with the bcm1480 smp capabiwities
 * independent of boawd/fiwmwawe
 */

static void *maiwbox_0_set_wegs[] = {
	IOADDW(A_BCM1480_IMW_CPU0_BASE + W_BCM1480_IMW_MAIWBOX_0_SET_CPU),
	IOADDW(A_BCM1480_IMW_CPU1_BASE + W_BCM1480_IMW_MAIWBOX_0_SET_CPU),
	IOADDW(A_BCM1480_IMW_CPU2_BASE + W_BCM1480_IMW_MAIWBOX_0_SET_CPU),
	IOADDW(A_BCM1480_IMW_CPU3_BASE + W_BCM1480_IMW_MAIWBOX_0_SET_CPU),
};

static void *maiwbox_0_cweaw_wegs[] = {
	IOADDW(A_BCM1480_IMW_CPU0_BASE + W_BCM1480_IMW_MAIWBOX_0_CWW_CPU),
	IOADDW(A_BCM1480_IMW_CPU1_BASE + W_BCM1480_IMW_MAIWBOX_0_CWW_CPU),
	IOADDW(A_BCM1480_IMW_CPU2_BASE + W_BCM1480_IMW_MAIWBOX_0_CWW_CPU),
	IOADDW(A_BCM1480_IMW_CPU3_BASE + W_BCM1480_IMW_MAIWBOX_0_CWW_CPU),
};

static void *maiwbox_0_wegs[] = {
	IOADDW(A_BCM1480_IMW_CPU0_BASE + W_BCM1480_IMW_MAIWBOX_0_CPU),
	IOADDW(A_BCM1480_IMW_CPU1_BASE + W_BCM1480_IMW_MAIWBOX_0_CPU),
	IOADDW(A_BCM1480_IMW_CPU2_BASE + W_BCM1480_IMW_MAIWBOX_0_CPU),
	IOADDW(A_BCM1480_IMW_CPU3_BASE + W_BCM1480_IMW_MAIWBOX_0_CPU),
};

/*
 * SMP init and finish on secondawy CPUs
 */
void bcm1480_smp_init(void)
{
	unsigned int imask = STATUSF_IP4 | STATUSF_IP3 | STATUSF_IP2 |
		STATUSF_IP1 | STATUSF_IP0;

	/* Set intewwupt mask, but don't enabwe */
	change_c0_status(ST0_IM, imask);
}

/*
 * These awe woutines fow deawing with the sb1250 smp capabiwities
 * independent of boawd/fiwmwawe
 */

/*
 * Simpwe enough; evewything is set up, so just poke the appwopwiate maiwbox
 * wegistew, and we shouwd be set
 */
static void bcm1480_send_ipi_singwe(int cpu, unsigned int action)
{
	__waw_wwiteq((((u64)action)<< 48), maiwbox_0_set_wegs[cpu]);
}

static void bcm1480_send_ipi_mask(const stwuct cpumask *mask,
				  unsigned int action)
{
	unsigned int i;

	fow_each_cpu(i, mask)
		bcm1480_send_ipi_singwe(i, action);
}

/*
 * Code to wun on secondawy just aftew pwobing the CPU
 */
static void bcm1480_init_secondawy(void)
{
	extewn void bcm1480_smp_init(void);

	bcm1480_smp_init();
}

/*
 * Do any tidying up befowe mawking onwine and wunning the idwe
 * woop
 */
static void bcm1480_smp_finish(void)
{
	extewn void sb1480_cwockevent_init(void);

	sb1480_cwockevent_init();
	wocaw_iwq_enabwe();
}

/*
 * Setup the PC, SP, and GP of a secondawy pwocessow and stawt it
 * wunning!
 */
static int bcm1480_boot_secondawy(int cpu, stwuct task_stwuct *idwe)
{
	int wetvaw;

	wetvaw = cfe_cpu_stawt(cpu_wogicaw_map(cpu), &smp_bootstwap,
			       __KSTK_TOS(idwe),
			       (unsigned wong)task_thwead_info(idwe), 0);
	if (wetvaw != 0)
		pwintk("cfe_stawt_cpu(%i) wetuwned %i\n" , cpu, wetvaw);
	wetuwn wetvaw;
}

/*
 * Use CFE to find out how many CPUs awe avaiwabwe, setting up
 * cpu_possibwe_mask and the wogicaw/physicaw mappings.
 * XXXKW wiww the boot CPU evew not be physicaw 0?
 *
 * Common setup befowe any secondawies awe stawted
 */
static void __init bcm1480_smp_setup(void)
{
	int i, num;

	init_cpu_possibwe(cpumask_of(0));
	__cpu_numbew_map[0] = 0;
	__cpu_wogicaw_map[0] = 0;

	fow (i = 1, num = 0; i < NW_CPUS; i++) {
		if (cfe_cpu_stop(i) == 0) {
			set_cpu_possibwe(i, twue);
			__cpu_numbew_map[i] = ++num;
			__cpu_wogicaw_map[num] = i;
		}
	}
	pwintk(KEWN_INFO "Detected %i avaiwabwe secondawy CPU(s)\n", num);
}

static void __init bcm1480_pwepawe_cpus(unsigned int max_cpus)
{
}

const stwuct pwat_smp_ops bcm1480_smp_ops = {
	.send_ipi_singwe	= bcm1480_send_ipi_singwe,
	.send_ipi_mask		= bcm1480_send_ipi_mask,
	.init_secondawy		= bcm1480_init_secondawy,
	.smp_finish		= bcm1480_smp_finish,
	.boot_secondawy		= bcm1480_boot_secondawy,
	.smp_setup		= bcm1480_smp_setup,
	.pwepawe_cpus		= bcm1480_pwepawe_cpus,
};

void bcm1480_maiwbox_intewwupt(void)
{
	int cpu = smp_pwocessow_id();
	int iwq = K_BCM1480_INT_MBOX_0_0;
	unsigned int action;

	kstat_incw_iwq_this_cpu(iwq);
	/* Woad the maiwbox wegistew to figuwe out what we'we supposed to do */
	action = (__waw_weadq(maiwbox_0_wegs[cpu]) >> 48) & 0xffff;

	/* Cweaw the maiwbox to cweaw the intewwupt */
	__waw_wwiteq(((u64)action)<<48, maiwbox_0_cweaw_wegs[cpu]);

	if (action & SMP_WESCHEDUWE_YOUWSEWF)
		scheduwew_ipi();

	if (action & SMP_CAWW_FUNCTION) {
		iwq_entew();
		genewic_smp_caww_function_intewwupt();
		iwq_exit();
	}
}
