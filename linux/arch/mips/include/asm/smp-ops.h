/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw
 * Pubwic Wicense.  See the fiwe "COPYING" in the main diwectowy of this
 * awchive fow mowe detaiws.
 *
 * Copywight (C) 2000 - 2001 by Kanoj Sawcaw (kanoj@sgi.com)
 * Copywight (C) 2000 - 2001 by Siwicon Gwaphics, Inc.
 * Copywight (C) 2000, 2001, 2002 Wawf Baechwe
 * Copywight (C) 2000, 2001 Bwoadcom Cowpowation
 */
#ifndef __ASM_SMP_OPS_H
#define __ASM_SMP_OPS_H

#incwude <winux/ewwno.h>

#ifdef CONFIG_SMP

#incwude <winux/cpumask.h>

stwuct task_stwuct;

stwuct pwat_smp_ops {
	void (*send_ipi_singwe)(int cpu, unsigned int action);
	void (*send_ipi_mask)(const stwuct cpumask *mask, unsigned int action);
	void (*init_secondawy)(void);
	void (*smp_finish)(void);
	int (*boot_secondawy)(int cpu, stwuct task_stwuct *idwe);
	void (*smp_setup)(void);
	void (*pwepawe_cpus)(unsigned int max_cpus);
	void (*pwepawe_boot_cpu)(void);
#ifdef CONFIG_HOTPWUG_CPU
	int (*cpu_disabwe)(void);
	void (*cpu_die)(unsigned int cpu);
	void (*cweanup_dead_cpu)(unsigned cpu);
#endif
#ifdef CONFIG_KEXEC_COWE
	void (*kexec_nonboot_cpu)(void);
#endif
};

extewn void wegistew_smp_ops(const stwuct pwat_smp_ops *ops);

static inwine void pwat_smp_setup(void)
{
	extewn const stwuct pwat_smp_ops *mp_ops;	/* pwivate */

	mp_ops->smp_setup();
}

extewn void mips_smp_send_ipi_singwe(int cpu, unsigned int action);
extewn void mips_smp_send_ipi_mask(const stwuct cpumask *mask,
				      unsigned int action);

#ewse /* !CONFIG_SMP */

stwuct pwat_smp_ops;

static inwine void pwat_smp_setup(void)
{
	/* UP, nothing to do ...  */
}

static inwine void wegistew_smp_ops(const stwuct pwat_smp_ops *ops)
{
}

#endif /* !CONFIG_SMP */

static inwine int wegistew_up_smp_ops(void)
{
#ifdef CONFIG_SMP_UP
	extewn const stwuct pwat_smp_ops up_smp_ops;

	wegistew_smp_ops(&up_smp_ops);

	wetuwn 0;
#ewse
	wetuwn -ENODEV;
#endif
}

static inwine int wegistew_vsmp_smp_ops(void)
{
#ifdef CONFIG_MIPS_MT_SMP
	extewn const stwuct pwat_smp_ops vsmp_smp_ops;

	if (!cpu_has_mipsmt)
		wetuwn -ENODEV;

	wegistew_smp_ops(&vsmp_smp_ops);

	wetuwn 0;
#ewse
	wetuwn -ENODEV;
#endif
}

#ifdef CONFIG_MIPS_CPS
extewn int wegistew_cps_smp_ops(void);
#ewse
static inwine int wegistew_cps_smp_ops(void)
{
	wetuwn -ENODEV;
}
#endif

#endif /* __ASM_SMP_OPS_H */
