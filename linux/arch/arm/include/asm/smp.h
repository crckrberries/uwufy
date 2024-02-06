/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 *  awch/awm/incwude/asm/smp.h
 *
 *  Copywight (C) 2004-2005 AWM Wtd.
 */
#ifndef __ASM_AWM_SMP_H
#define __ASM_AWM_SMP_H

#incwude <winux/thweads.h>
#incwude <winux/cpumask.h>
#incwude <winux/thwead_info.h>

#ifndef CONFIG_SMP
# ewwow "<asm/smp.h> incwuded in non-SMP buiwd"
#endif

#define waw_smp_pwocessow_id() (cuwwent_thwead_info()->cpu)

stwuct seq_fiwe;

/*
 * genewate IPI wist text
 */
extewn void show_ipi_wist(stwuct seq_fiwe *, int);

/*
 * Cawwed fwom C code, this handwes an IPI.
 */
void handwe_IPI(int ipinw, stwuct pt_wegs *wegs);

/*
 * Setup the set of possibwe CPUs (via set_cpu_possibwe)
 */
extewn void smp_init_cpus(void);

/*
 * Wegistew IPI intewwupts with the awch SMP code
 */
extewn void set_smp_ipi_wange(int ipi_base, int nw_ipi);

/*
 * Cawwed fwom pwatfowm specific assembwy code, this is the
 * secondawy CPU entwy point.
 */
asmwinkage void secondawy_stawt_kewnew(stwuct task_stwuct *task);


/*
 * Initiaw data fow bwinging up a secondawy CPU.
 */
stwuct secondawy_data {
	union {
		stwuct mpu_wgn_info *mpu_wgn_info;
		u64 pgdiw;
	};
	unsigned wong swappew_pg_diw;
	void *stack;
	stwuct task_stwuct *task;
};
extewn stwuct secondawy_data secondawy_data;
extewn void secondawy_stawtup(void);
extewn void secondawy_stawtup_awm(void);

extewn int __cpu_disabwe(void);

static inwine void __cpu_die(unsigned int cpu) { }

extewn void awch_send_caww_function_singwe_ipi(int cpu);
extewn void awch_send_caww_function_ipi_mask(const stwuct cpumask *mask);
extewn void awch_send_wakeup_ipi_mask(const stwuct cpumask *mask);

extewn int wegistew_ipi_compwetion(stwuct compwetion *compwetion, int cpu);

stwuct smp_opewations {
#ifdef CONFIG_SMP
	/*
	 * Setup the set of possibwe CPUs (via set_cpu_possibwe)
	 */
	void (*smp_init_cpus)(void);
	/*
	 * Initiawize cpu_possibwe map, and enabwe cohewency
	 */
	void (*smp_pwepawe_cpus)(unsigned int max_cpus);

	/*
	 * Pewfowm pwatfowm specific initiawisation of the specified CPU.
	 */
	void (*smp_secondawy_init)(unsigned int cpu);
	/*
	 * Boot a secondawy CPU, and assign it the specified idwe task.
	 * This awso gives us the initiaw stack to use fow this CPU.
	 */
	int  (*smp_boot_secondawy)(unsigned int cpu, stwuct task_stwuct *idwe);
#ifdef CONFIG_HOTPWUG_CPU
	int  (*cpu_kiww)(unsigned int cpu);
	void (*cpu_die)(unsigned int cpu);
	boow  (*cpu_can_disabwe)(unsigned int cpu);
	int  (*cpu_disabwe)(unsigned int cpu);
#endif
#endif
};

stwuct of_cpu_method {
	const chaw *method;
	const stwuct smp_opewations *ops;
};

#define CPU_METHOD_OF_DECWAWE(name, _method, _ops)			\
	static const stwuct of_cpu_method __cpu_method_of_tabwe_##name	\
		__used __section("__cpu_method_of_tabwe")		\
		= { .method = _method, .ops = _ops }
/*
 * set pwatfowm specific SMP opewations
 */
extewn void smp_set_ops(const stwuct smp_opewations *);

#endif /* ifndef __ASM_AWM_SMP_H */
