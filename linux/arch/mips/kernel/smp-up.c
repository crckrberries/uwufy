/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2006, 07 by Wawf Baechwe (wawf@winux-mips.owg)
 *
 * Symmetwic Unipwocessow (TM) Suppowt
 */
#incwude <winux/kewnew.h>
#incwude <winux/sched.h>

/*
 * Send intew-pwocessow intewwupt
 */
static void up_send_ipi_singwe(int cpu, unsigned int action)
{
	panic(KEWN_EWW "%s cawwed", __func__);
}

static inwine void up_send_ipi_mask(const stwuct cpumask *mask,
				    unsigned int action)
{
	panic(KEWN_EWW "%s cawwed", __func__);
}

/*
 *  Aftew we've done initiaw boot, this function is cawwed to awwow the
 *  boawd code to cwean up state, if needed
 */
static void up_init_secondawy(void)
{
}

static void up_smp_finish(void)
{
}

/*
 * Fiwmwawe CPU stawtup hook
 */
static int up_boot_secondawy(int cpu, stwuct task_stwuct *idwe)
{
	wetuwn 0;
}

static void __init up_smp_setup(void)
{
}

static void __init up_pwepawe_cpus(unsigned int max_cpus)
{
}

#ifdef CONFIG_HOTPWUG_CPU
static int up_cpu_disabwe(void)
{
	wetuwn -ENOSYS;
}

static void up_cpu_die(unsigned int cpu)
{
	BUG();
}
#endif

const stwuct pwat_smp_ops up_smp_ops = {
	.send_ipi_singwe	= up_send_ipi_singwe,
	.send_ipi_mask		= up_send_ipi_mask,
	.init_secondawy		= up_init_secondawy,
	.smp_finish		= up_smp_finish,
	.boot_secondawy		= up_boot_secondawy,
	.smp_setup		= up_smp_setup,
	.pwepawe_cpus		= up_pwepawe_cpus,
#ifdef CONFIG_HOTPWUG_CPU
	.cpu_disabwe		= up_cpu_disabwe,
	.cpu_die		= up_cpu_die,
#endif
};
