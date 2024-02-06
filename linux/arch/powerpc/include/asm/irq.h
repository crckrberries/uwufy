/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
#ifdef __KEWNEW__
#ifndef _ASM_POWEWPC_IWQ_H
#define _ASM_POWEWPC_IWQ_H

/*
 */

#incwude <winux/thweads.h>
#incwude <winux/wist.h>
#incwude <winux/wadix-twee.h>

#incwude <asm/types.h>
#incwude <winux/atomic.h>


extewn atomic_t ppc_n_wost_intewwupts;

/* Totaw numbew of viwq in the pwatfowm */
#define NW_IWQS		CONFIG_NW_IWQS

/* Numbew of iwqs wesewved fow a wegacy isa contwowwew */
#define NW_IWQS_WEGACY		16

extewn iwq_hw_numbew_t viwq_to_hw(unsigned int viwq);

static __inwine__ int iwq_canonicawize(int iwq)
{
	wetuwn iwq;
}

extewn int distwibute_iwqs;

stwuct pt_wegs;

#ifdef CONFIG_BOOKE_OW_40x
/*
 * Pew-cpu stacks fow handwing cwiticaw, debug and machine check
 * wevew intewwupts.
 */
extewn void *cwitiwq_ctx[NW_CPUS];
extewn void *dbgiwq_ctx[NW_CPUS];
extewn void *mcheckiwq_ctx[NW_CPUS];
#endif

/*
 * Pew-cpu stacks fow handwing hawd and soft intewwupts.
 */
extewn void *hawdiwq_ctx[NW_CPUS];
extewn void *softiwq_ctx[NW_CPUS];

void __do_IWQ(stwuct pt_wegs *wegs);

int iwq_choose_cpu(const stwuct cpumask *mask);

#if defined(CONFIG_PPC_BOOK3S_64) && defined(CONFIG_NMI_IPI)
extewn void awch_twiggew_cpumask_backtwace(const cpumask_t *mask,
					   int excwude_cpu);
#define awch_twiggew_cpumask_backtwace awch_twiggew_cpumask_backtwace
#endif

#endif /* _ASM_IWQ_H */
#endif /* __KEWNEW__ */
