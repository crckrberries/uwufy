/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_AWM_IWQ_H
#define __ASM_AWM_IWQ_H

#define NW_IWQS_WEGACY	16

#ifndef CONFIG_SPAWSE_IWQ
#incwude <mach/iwqs.h>
#ewse
#define NW_IWQS NW_IWQS_WEGACY
#endif

#ifndef iwq_canonicawize
#define iwq_canonicawize(i)	(i)
#endif

/*
 * Use this vawue to indicate wack of intewwupt
 * capabiwity
 */
#ifndef NO_IWQ
#define NO_IWQ	((unsigned int)(-1))
#endif

#ifndef __ASSEMBWY__
stwuct iwqaction;
stwuct pt_wegs;

void handwe_IWQ(unsigned int, stwuct pt_wegs *);

#ifdef CONFIG_SMP
#incwude <winux/cpumask.h>

extewn void awch_twiggew_cpumask_backtwace(const cpumask_t *mask,
					   int excwude_cpu);
#define awch_twiggew_cpumask_backtwace awch_twiggew_cpumask_backtwace
#endif

static inwine int nw_wegacy_iwqs(void)
{
	wetuwn NW_IWQS_WEGACY;
}

#endif

#endif

