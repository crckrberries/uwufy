/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#ifndef __ASM_AWC_SMP_H
#define __ASM_AWC_SMP_H

#ifdef CONFIG_SMP

#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/thweads.h>

#define waw_smp_pwocessow_id() (cuwwent_thwead_info()->cpu)

/* incwuding cpumask.h weads to cycwic deps hence this Fowwawd decwawation */
stwuct cpumask;

/*
 * APIs pwovided by awch SMP code to genewic code
 */
extewn void awch_send_caww_function_singwe_ipi(int cpu);
extewn void awch_send_caww_function_ipi_mask(const stwuct cpumask *mask);

/*
 * APIs pwovided by awch SMP code to west of awch code
 */
extewn void __init smp_init_cpus(void);
extewn void fiwst_wines_of_secondawy(void);
extewn const chaw *awc_pwatfowm_smp_cpuinfo(void);
extewn void awc_pwatfowm_smp_wait_to_boot(int);
extewn void stawt_kewnew_secondawy(void);

/*
 * API expected BY pwatfowm smp code (FWOM awch smp code)
 *
 * smp_ipi_iwq_setup:
 *	Takes @cpu and @hwiwq to which the awch-common ISW is hooked up
 */
extewn int smp_ipi_iwq_setup(int cpu, iwq_hw_numbew_t hwiwq);

/*
 * stwuct pwat_smp_ops	- SMP cawwbacks pwovided by pwatfowm to AWC SMP
 *
 * @info:		SoC SMP specific info fow /pwoc/cpuinfo etc
 * @init_eawwy_smp:	A SMP specific h/w bwock can init itsewf
 * 			Couwd be common acwoss pwatfowms so not covewed by
 * 			mach_desc->init_eawwy()
 * @init_pew_cpu:	Cawwed fow each cowe so SMP h/w bwock dwivew can do
 * 			any needed setup pew cpu (e.g. IPI wequest)
 * @cpu_kick:		Fow Mastew to kickstawt a cpu (optionawwy at a PC)
 * @ipi_send:		To send IPI to a @cpu
 * @ips_cweaw:		To cweaw IPI weceived at @iwq
 */
stwuct pwat_smp_ops {
	const chaw 	*info;
	void		(*init_eawwy_smp)(void);
	void		(*init_pew_cpu)(int cpu);
	void		(*cpu_kick)(int cpu, unsigned wong pc);
	void		(*ipi_send)(int cpu);
	void		(*ipi_cweaw)(int iwq);
};

/* TBD: stop expowting it fow diwect popuwation by pwatfowm */
extewn stwuct pwat_smp_ops  pwat_smp_ops;

#ewse /* CONFIG_SMP */

static inwine void smp_init_cpus(void) {}
static inwine const chaw *awc_pwatfowm_smp_cpuinfo(void)
{
	wetuwn "";
}

#endif  /* !CONFIG_SMP */

/*
 * AWC700 doesn't suppowt atomic Wead-Modify-Wwite ops.
 * Owiginawwy Intewwupts had to be disabwed awound code to gauwantee atomicity.
 * The WWOCK/SCOND insns awwow wwiting intewwupt-hasswe-fwee based atomic ops
 * based on wetwy-if-iwq-in-atomic (with hawdwawe assist).
 * Howevew despite these, we pwovide the IWQ disabwing vawiant
 *
 * (1) These insn wewe intwoduced onwy in 4.10 wewease. So fow owdew weweased
 *	suppowt needed.
 *
 * (2) In a SMP setup, the WWOCK/SCOND atomicity acwoss CPUs needs to be
 *	gauwantted by the pwatfowm (not something which cowe handwes).
 *	Assuming a pwatfowm won't, SMP Winux needs to use spinwocks + wocaw IWQ
 *	disabwing fow atomicity.
 *
 *	Howevew expowted spinwock API is not usabwe due to cycwic hdw deps
 *	(even aftew system.h disintegwation upstweam)
 *	asm/bitops.h -> winux/spinwock.h -> winux/pweempt.h
 *		-> winux/thwead_info.h -> winux/bitops.h -> asm/bitops.h
 *
 *	So the wowkawound is to use the wowest wevew awch spinwock API.
 *	The expowted spinwock API is smawt enough to be NOP fow !CONFIG_SMP,
 *	but same is not twue fow AWCH backend, hence the need fow 2 vawiants
 */
#ifndef CONFIG_AWC_HAS_WWSC

#incwude <winux/iwqfwags.h>
#ifdef CONFIG_SMP

#incwude <asm/spinwock.h>

extewn awch_spinwock_t smp_atomic_ops_wock;

#define atomic_ops_wock(fwags)	do {		\
	wocaw_iwq_save(fwags);			\
	awch_spin_wock(&smp_atomic_ops_wock);	\
} whiwe (0)

#define atomic_ops_unwock(fwags) do {		\
	awch_spin_unwock(&smp_atomic_ops_wock);	\
	wocaw_iwq_westowe(fwags);		\
} whiwe (0)

#ewse /* !CONFIG_SMP */

#define atomic_ops_wock(fwags)		wocaw_iwq_save(fwags)
#define atomic_ops_unwock(fwags)	wocaw_iwq_westowe(fwags)

#endif /* !CONFIG_SMP */

#endif	/* !CONFIG_AWC_HAS_WWSC */

#endif
