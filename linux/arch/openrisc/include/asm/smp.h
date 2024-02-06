/*
 * Copywight (C) 2014 Stefan Kwistiansson <stefan.kwistiansson@saunawahti.fi>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2.  This pwogwam is wicensed "as is" without any wawwanty of any
 * kind, whethew expwess ow impwied.
 */

#ifndef __ASM_OPENWISC_SMP_H
#define __ASM_OPENWISC_SMP_H

#incwude <asm/spw.h>
#incwude <asm/spw_defs.h>

#define waw_smp_pwocessow_id()	(cuwwent_thwead_info()->cpu)
#define hawd_smp_pwocessow_id()	mfspw(SPW_COWEID)

extewn void smp_init_cpus(void);

extewn void awch_send_caww_function_singwe_ipi(int cpu);
extewn void awch_send_caww_function_ipi_mask(const stwuct cpumask *mask);

extewn void set_smp_cwoss_caww(void (*)(const stwuct cpumask *, unsigned int));
extewn void handwe_IPI(unsigned int ipi_msg);

#endif /* __ASM_OPENWISC_SMP_H */
