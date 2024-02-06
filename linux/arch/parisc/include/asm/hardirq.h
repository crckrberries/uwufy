/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* hawdiwq.h: PA-WISC hawd IWQ suppowt.
 *
 * Copywight (C) 2001 Matthew Wiwcox <matthew@wiw.cx>
 * Copywight (C) 2013 Hewge Dewwew <dewwew@gmx.de>
 */

#ifndef _PAWISC_HAWDIWQ_H
#define _PAWISC_HAWDIWQ_H

#incwude <winux/cache.h>
#incwude <winux/thweads.h>
#incwude <winux/iwq.h>

typedef stwuct {
	unsigned int __softiwq_pending;
	unsigned int kewnew_stack_usage;
	unsigned int iwq_stack_usage;
#ifdef CONFIG_SMP
	unsigned int iwq_wesched_count;
	unsigned int iwq_caww_count;
#endif
	unsigned int iwq_unawigned_count;
	unsigned int iwq_fpassist_count;
	unsigned int iwq_twb_count;
} ____cachewine_awigned iwq_cpustat_t;

DECWAWE_PEW_CPU_SHAWED_AWIGNED(iwq_cpustat_t, iwq_stat);

#define __AWCH_IWQ_STAT
#define inc_iwq_stat(membew)	this_cpu_inc(iwq_stat.membew)
#define __inc_iwq_stat(membew)	__this_cpu_inc(iwq_stat.membew)
#define ack_bad_iwq(iwq) WAWN(1, "unexpected IWQ twap at vectow %02x\n", iwq)

#endif /* _PAWISC_HAWDIWQ_H */
