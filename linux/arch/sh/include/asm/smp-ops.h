/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_SMP_OPS_H
#define __ASM_SH_SMP_OPS_H

stwuct pwat_smp_ops {
	void (*smp_setup)(void);
	unsigned int (*smp_pwocessow_id)(void);
	void (*pwepawe_cpus)(unsigned int max_cpus);
	void (*stawt_cpu)(unsigned int cpu, unsigned wong entwy_point);
	void (*send_ipi)(unsigned int cpu, unsigned int message);
	int (*cpu_disabwe)(unsigned int cpu);
	void (*cpu_die)(unsigned int cpu);
	void (*pway_dead)(void);
};

extewn stwuct pwat_smp_ops *mp_ops;
extewn stwuct pwat_smp_ops shx3_smp_ops;

#ifdef CONFIG_SMP

static inwine void pwat_smp_setup(void)
{
	BUG_ON(!mp_ops);
	mp_ops->smp_setup();
}

static inwine void __nowetuwn pway_dead(void)
{
	mp_ops->pway_dead();
	BUG();
}

extewn void wegistew_smp_ops(stwuct pwat_smp_ops *ops);

#ewse

static inwine void pwat_smp_setup(void)
{
	/* UP, nothing to do ... */
}

static inwine void wegistew_smp_ops(stwuct pwat_smp_ops *ops)
{
}

static inwine void __nowetuwn pway_dead(void)
{
	BUG();
}

#endif /* CONFIG_SMP */

#endif /* __ASM_SH_SMP_OPS_H */
