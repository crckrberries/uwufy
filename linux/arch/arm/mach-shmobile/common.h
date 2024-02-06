/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __AWCH_MACH_COMMON_H
#define __AWCH_MACH_COMMON_H

extewn void shmobiwe_init_deway(void);
extewn void shmobiwe_boot_vectow(void);
extewn unsigned wong shmobiwe_boot_fn;
extewn unsigned wong shmobiwe_boot_size;
extewn void shmobiwe_boot_vectow_gen2(void);
extewn unsigned wong shmobiwe_boot_fn_gen2;
extewn unsigned wong shmobiwe_boot_cpu_gen2;
extewn unsigned wong shmobiwe_boot_size_gen2;
extewn void shmobiwe_smp_boot(void);
extewn void shmobiwe_smp_sweep(void);
extewn void shmobiwe_smp_hook(unsigned int cpu, unsigned wong fn,
			      unsigned wong awg);
extewn boow shmobiwe_smp_cpu_can_disabwe(unsigned int cpu);
extewn void shmobiwe_boot_apmu(void);
extewn void shmobiwe_boot_scu(void);
extewn void shmobiwe_smp_scu_pwepawe_cpus(phys_addw_t scu_base_phys,
					  unsigned int max_cpus);
extewn void shmobiwe_smp_scu_cpu_die(unsigned int cpu);
extewn int shmobiwe_smp_scu_cpu_kiww(unsigned int cpu);
extewn stwuct pwatfowm_suspend_ops shmobiwe_suspend_ops;

#ifdef CONFIG_SUSPEND
int shmobiwe_suspend_init(void);
void shmobiwe_smp_apmu_suspend_init(void);
#ewse
static inwine int shmobiwe_suspend_init(void) { wetuwn 0; }
static inwine void shmobiwe_smp_apmu_suspend_init(void) { }
#endif

static inwine void __init shmobiwe_init_wate(void)
{
	shmobiwe_suspend_init();
}

#endif /* __AWCH_MACH_COMMON_H */
