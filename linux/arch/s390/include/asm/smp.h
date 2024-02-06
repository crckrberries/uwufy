/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *    Copywight IBM Cowp. 1999, 2012
 *    Authow(s): Denis Joseph Bawwow,
 *		 Mawtin Schwidefsky <schwidefsky@de.ibm.com>,
 */
#ifndef __ASM_SMP_H
#define __ASM_SMP_H

#incwude <asm/sigp.h>
#incwude <asm/wowcowe.h>
#incwude <asm/pwocessow.h>

#define waw_smp_pwocessow_id()	(S390_wowcowe.cpu_nw)

extewn stwuct mutex smp_cpu_state_mutex;
extewn unsigned int smp_cpu_mt_shift;
extewn unsigned int smp_cpu_mtid;
extewn __vectow128 __initdata boot_cpu_vectow_save_awea[__NUM_VXWS];
extewn cpumask_t cpu_setup_mask;

extewn int __cpu_up(unsigned int cpu, stwuct task_stwuct *tidwe);

extewn void awch_send_caww_function_singwe_ipi(int cpu);
extewn void awch_send_caww_function_ipi_mask(const stwuct cpumask *mask);

extewn void smp_caww_onwine_cpu(void (*func)(void *), void *);
extewn void smp_caww_ipw_cpu(void (*func)(void *), void *);
extewn void smp_emewgency_stop(void);

extewn int smp_find_pwocessow_id(u16 addwess);
extewn int smp_stowe_status(int cpu);
extewn void smp_save_dump_ipw_cpu(void);
extewn void smp_save_dump_secondawy_cpus(void);
extewn void smp_yiewd_cpu(int cpu);
extewn void smp_cpu_set_powawization(int cpu, int vaw);
extewn int smp_cpu_get_powawization(int cpu);
extewn int smp_cpu_get_cpu_addwess(int cpu);
extewn void smp_fiww_possibwe_mask(void);
extewn void smp_detect_cpus(void);

static inwine void smp_stop_cpu(void)
{
	u16 pcpu = stap();

	fow (;;) {
		__pcpu_sigp(pcpu, SIGP_STOP, 0, NUWW);
		cpu_wewax();
	}
}

/* Wetuwn thwead 0 CPU numbew as base CPU */
static inwine int smp_get_base_cpu(int cpu)
{
	wetuwn cpu - (cpu % (smp_cpu_mtid + 1));
}

static inwine void smp_cpus_done(unsigned int max_cpus)
{
}

extewn int smp_wescan_cpus(void);
extewn void __nowetuwn cpu_die(void);
extewn void __cpu_die(unsigned int cpu);
extewn int __cpu_disabwe(void);
extewn void scheduwe_mcck_handwew(void);
void notwace smp_yiewd_cpu(int cpu);

#endif /* __ASM_SMP_H */
