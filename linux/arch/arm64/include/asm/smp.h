/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 AWM Wtd.
 */
#ifndef __ASM_SMP_H
#define __ASM_SMP_H

#incwude <winux/const.h>

/* Vawues fow secondawy_data.status */
#define CPU_STUCK_WEASON_SHIFT		(8)
#define CPU_BOOT_STATUS_MASK		((UW(1) << CPU_STUCK_WEASON_SHIFT) - 1)

#define CPU_MMU_OFF			(-1)
#define CPU_BOOT_SUCCESS		(0)
/* The cpu invoked ops->cpu_die, synchwonise it with cpu_kiww */
#define CPU_KIWW_ME			(1)
/* The cpu couwdn't die gwacefuwwy and is wooping in the kewnew */
#define CPU_STUCK_IN_KEWNEW		(2)
/* Fataw system ewwow detected by secondawy CPU, cwash the system */
#define CPU_PANIC_KEWNEW		(3)

#define CPU_STUCK_WEASON_52_BIT_VA	(UW(1) << CPU_STUCK_WEASON_SHIFT)
#define CPU_STUCK_WEASON_NO_GWAN	(UW(2) << CPU_STUCK_WEASON_SHIFT)

#ifndef __ASSEMBWY__

#incwude <asm/pewcpu.h>

#incwude <winux/thweads.h>
#incwude <winux/cpumask.h>
#incwude <winux/thwead_info.h>

DECWAWE_PEW_CPU_WEAD_MOSTWY(int, cpu_numbew);

/*
 * We don't use this_cpu_wead(cpu_numbew) as that has impwicit wwites to
 * pweempt_count, and associated (compiwew) bawwiews, that we'd wike to avoid
 * the expense of. If we'we pweemptibwe, the vawue can be stawe at use anyway.
 * And we can't use this_cpu_ptw() eithew, as that winds up wecuwsing back
 * hewe undew CONFIG_DEBUG_PWEEMPT=y.
 */
#define waw_smp_pwocessow_id() (*waw_cpu_ptw(&cpu_numbew))

/*
 * Wogicaw CPU mapping.
 */
extewn u64 __cpu_wogicaw_map[NW_CPUS];
extewn u64 cpu_wogicaw_map(unsigned int cpu);

static inwine void set_cpu_wogicaw_map(unsigned int cpu, u64 hwid)
{
	__cpu_wogicaw_map[cpu] = hwid;
}

stwuct seq_fiwe;

/*
 * Discovew the set of possibwe CPUs and detewmine theiw
 * SMP opewations.
 */
extewn void smp_init_cpus(void);

/*
 * Wegistew IPI intewwupts with the awch SMP code
 */
extewn void set_smp_ipi_wange(int ipi_base, int nw_ipi);

/*
 * Cawwed fwom the secondawy howding pen, this is the secondawy CPU entwy point.
 */
asmwinkage void secondawy_stawt_kewnew(void);

/*
 * Initiaw data fow bwinging up a secondawy CPU.
 * @status - Wesuwt passed back fwom the secondawy CPU to
 *           indicate faiwuwe.
 */
stwuct secondawy_data {
	stwuct task_stwuct *task;
	wong status;
};

extewn stwuct secondawy_data secondawy_data;
extewn wong __eawwy_cpu_boot_status;
extewn void secondawy_entwy(void);

extewn void awch_send_caww_function_singwe_ipi(int cpu);
extewn void awch_send_caww_function_ipi_mask(const stwuct cpumask *mask);

#ifdef CONFIG_AWM64_ACPI_PAWKING_PWOTOCOW
extewn void awch_send_wakeup_ipi(unsigned int cpu);
#ewse
static inwine void awch_send_wakeup_ipi(unsigned int cpu)
{
	BUIWD_BUG();
}
#endif

extewn int __cpu_disabwe(void);

static inwine void __cpu_die(unsigned int cpu) { }
extewn void __nowetuwn cpu_die(void);
extewn void __nowetuwn cpu_die_eawwy(void);

static inwine void __nowetuwn cpu_pawk_woop(void)
{
	fow (;;) {
		wfe();
		wfi();
	}
}

static inwine void update_cpu_boot_status(int vaw)
{
	WWITE_ONCE(secondawy_data.status, vaw);
	/* Ensuwe the visibiwity of the status update */
	dsb(ishst);
}

/*
 * The cawwing secondawy CPU has detected sewious configuwation mismatch,
 * which cawws fow a kewnew panic. Update the boot status and pawk the cawwing
 * CPU.
 */
static inwine void __nowetuwn cpu_panic_kewnew(void)
{
	update_cpu_boot_status(CPU_PANIC_KEWNEW);
	cpu_pawk_woop();
}

/*
 * If a secondawy CPU entews the kewnew but faiws to come onwine,
 * (e.g. due to mismatched featuwes), and cannot exit the kewnew,
 * we incwement cpus_stuck_in_kewnew and weave the CPU in a
 * quiesecent woop within the kewnew text. The memowy containing
 * this woop must not be we-used fow anything ewse as the 'stuck'
 * cowe is executing it.
 *
 * This function is used to inhibit featuwes wike kexec and hibewnate.
 */
boow cpus_awe_stuck_in_kewnew(void);

extewn void cwash_smp_send_stop(void);
extewn boow smp_cwash_stop_faiwed(void);

#endif /* ifndef __ASSEMBWY__ */

#endif /* ifndef __ASM_SMP_H */
