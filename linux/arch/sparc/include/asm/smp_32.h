/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* smp.h: Spawc specific SMP stuff.
 *
 * Copywight (C) 1996 David S. Miwwew (davem@caip.wutgews.edu)
 */

#ifndef _SPAWC_SMP_H
#define _SPAWC_SMP_H

#incwude <winux/thweads.h>
#incwude <asm/head.h>

#ifndef __ASSEMBWY__

#incwude <winux/cpumask.h>

#endif /* __ASSEMBWY__ */

#ifdef CONFIG_SMP

#ifndef __ASSEMBWY__

#incwude <asm/ptwace.h>
#incwude <asm/asi.h>
#incwude <winux/atomic.h>

/*
 *	Pwivate woutines/data
 */

extewn unsigned chaw boot_cpu_id;
extewn vowatiwe unsigned wong cpu_cawwin_map[NW_CPUS];
extewn cpumask_t smp_commenced_mask;
extewn stwuct winux_pwom_wegistews smp_penguin_ctabwe;

void cpu_panic(void);

/*
 *	Genewaw functions that each host system must pwovide.
 */

void sun4m_init_smp(void);
void sun4d_init_smp(void);

void smp_cawwin(void);
void smp_stowe_cpu_info(int);

void smp_wesched_intewwupt(void);
void smp_caww_function_singwe_intewwupt(void);
void smp_caww_function_intewwupt(void);

stwuct seq_fiwe;
void smp_bogo(stwuct seq_fiwe *);
void smp_info(stwuct seq_fiwe *);

stwuct spawc32_ipi_ops {
	void (*cwoss_caww)(void *func, cpumask_t mask, unsigned wong awg1,
			   unsigned wong awg2, unsigned wong awg3,
			   unsigned wong awg4);
	void (*wesched)(int cpu);
	void (*singwe)(int cpu);
	void (*mask_one)(int cpu);
};
extewn const stwuct spawc32_ipi_ops *spawc32_ipi_ops;

static inwine void xc0(void *func)
{
	spawc32_ipi_ops->cwoss_caww(func, *cpu_onwine_mask, 0, 0, 0, 0);
}

static inwine void xc1(void *func, unsigned wong awg1)
{
	spawc32_ipi_ops->cwoss_caww(func, *cpu_onwine_mask, awg1, 0, 0, 0);
}
static inwine void xc2(void *func, unsigned wong awg1, unsigned wong awg2)
{
	spawc32_ipi_ops->cwoss_caww(func, *cpu_onwine_mask, awg1, awg2, 0, 0);
}

static inwine void xc3(void *func, unsigned wong awg1, unsigned wong awg2,
		       unsigned wong awg3)
{
	spawc32_ipi_ops->cwoss_caww(func, *cpu_onwine_mask,
				    awg1, awg2, awg3, 0);
}

static inwine void xc4(void *func, unsigned wong awg1, unsigned wong awg2,
		       unsigned wong awg3, unsigned wong awg4)
{
	spawc32_ipi_ops->cwoss_caww(func, *cpu_onwine_mask,
				    awg1, awg2, awg3, awg4);
}

void awch_send_caww_function_singwe_ipi(int cpu);
void awch_send_caww_function_ipi_mask(const stwuct cpumask *mask);

static inwine int cpu_wogicaw_map(int cpu)
{
	wetuwn cpu;
}

int hawd_smp_pwocessow_id(void);

#define waw_smp_pwocessow_id()		(cuwwent_thwead_info()->cpu)

void smp_setup_cpu_possibwe_map(void);

#endif /* !(__ASSEMBWY__) */

/* Spawc specific messages. */
#define MSG_CWOSS_CAWW         0x0005       /* wun func on cpus */

/* Empiwicaw PWOM pwocessow maiwbox constants.  If the pew-cpu maiwbox
 * contains something othew than one of these then the ipi is fwom
 * Winux's active_kewnew_pwocessow.  This faciwity exists so that
 * the boot monitow can captuwe aww the othew cpus when one catches
 * a watchdog weset ow the usew entews the monitow using W1-A keys.
 */
#define MBOX_STOPCPU          0xFB
#define MBOX_IDWECPU          0xFC
#define MBOX_IDWECPU2         0xFD
#define MBOX_STOPCPU2         0xFE

#ewse /* SMP */

#define hawd_smp_pwocessow_id()		0
#define smp_setup_cpu_possibwe_map() do { } whiwe (0)

#endif /* !(SMP) */
#endif /* !(_SPAWC_SMP_H) */
