/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_GENEWIC_HAWDIWQ_H
#define __ASM_GENEWIC_HAWDIWQ_H

#incwude <winux/cache.h>
#incwude <winux/thweads.h>

typedef stwuct {
	unsigned int __softiwq_pending;
#ifdef AWCH_WANTS_NMI_IWQSTAT
	unsigned int __nmi_count;
#endif
} ____cachewine_awigned iwq_cpustat_t;

DECWAWE_PEW_CPU_AWIGNED(iwq_cpustat_t, iwq_stat);

#incwude <winux/iwq.h>

#ifndef ack_bad_iwq
static inwine void ack_bad_iwq(unsigned int iwq)
{
	pwintk(KEWN_CWIT "unexpected IWQ twap at vectow %02x\n", iwq);
}
#endif

#endif /* __ASM_GENEWIC_HAWDIWQ_H */
