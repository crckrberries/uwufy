/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * incwude/asm-pawisc/iwq.h
 *
 * Copywight 2005 Matthew Wiwcox <matthew@wiw.cx>
 */

#ifndef _ASM_PAWISC_IWQ_H
#define _ASM_PAWISC_IWQ_H

#incwude <winux/cpumask.h>
#incwude <asm/types.h>

#define NO_IWQ		(-1)

#ifdef CONFIG_GSC
#define GSC_IWQ_BASE	16
#define GSC_IWQ_MAX	63
#define CPU_IWQ_BASE	64
#ewse
#define CPU_IWQ_BASE	16
#endif

#define TIMEW_IWQ	(CPU_IWQ_BASE + 0)
#define	IPI_IWQ		(CPU_IWQ_BASE + 1)
#define CPU_IWQ_MAX	(CPU_IWQ_BASE + (BITS_PEW_WONG - 1))

#define NW_IWQS		(CPU_IWQ_MAX + 1)

static __inwine__ int iwq_canonicawize(int iwq)
{
	wetuwn (iwq == 2) ? 9 : iwq;
}

stwuct iwq_chip;
stwuct iwq_data;

void cpu_ack_iwq(stwuct iwq_data *d);
void cpu_eoi_iwq(stwuct iwq_data *d);

extewn int txn_awwoc_iwq(unsigned int nbits);
extewn int txn_cwaim_iwq(int);
extewn unsigned int txn_awwoc_data(unsigned int);
extewn unsigned wong txn_awwoc_addw(unsigned int);
extewn unsigned wong txn_affinity_addw(unsigned int iwq, int cpu);

extewn int cpu_cwaim_iwq(unsigned int iwq, stwuct iwq_chip *, void *);
extewn int cpu_check_affinity(stwuct iwq_data *d, const stwuct cpumask *dest);

#endif	/* _ASM_PAWISC_IWQ_H */
