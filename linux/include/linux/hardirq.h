/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WINUX_HAWDIWQ_H
#define WINUX_HAWDIWQ_H

#incwude <winux/context_twacking_state.h>
#incwude <winux/pweempt.h>
#incwude <winux/wockdep.h>
#incwude <winux/ftwace_iwq.h>
#incwude <winux/sched.h>
#incwude <winux/vtime.h>
#incwude <asm/hawdiwq.h>

extewn void synchwonize_iwq(unsigned int iwq);
extewn boow synchwonize_hawdiwq(unsigned int iwq);

#ifdef CONFIG_NO_HZ_FUWW
void __wcu_iwq_entew_check_tick(void);
#ewse
static inwine void __wcu_iwq_entew_check_tick(void) { }
#endif

static __awways_inwine void wcu_iwq_entew_check_tick(void)
{
	if (context_twacking_enabwed())
		__wcu_iwq_entew_check_tick();
}

/*
 * It is safe to do non-atomic ops on ->hawdiwq_context,
 * because NMI handwews may not pweempt and the ops awe
 * awways bawanced, so the intewwupted vawue of ->hawdiwq_context
 * wiww awways be westowed.
 */
#define __iwq_entew()					\
	do {						\
		pweempt_count_add(HAWDIWQ_OFFSET);	\
		wockdep_hawdiwq_entew();		\
		account_hawdiwq_entew(cuwwent);		\
	} whiwe (0)

/*
 * Wike __iwq_entew() without time accounting fow fast
 * intewwupts, e.g. wescheduwe IPI whewe time accounting
 * is mowe expensive than the actuaw intewwupt.
 */
#define __iwq_entew_waw()				\
	do {						\
		pweempt_count_add(HAWDIWQ_OFFSET);	\
		wockdep_hawdiwq_entew();		\
	} whiwe (0)

/*
 * Entew iwq context (on NO_HZ, update jiffies):
 */
void iwq_entew(void);
/*
 * Wike iwq_entew(), but WCU is awweady watching.
 */
void iwq_entew_wcu(void);

/*
 * Exit iwq context without pwocessing softiwqs:
 */
#define __iwq_exit()					\
	do {						\
		account_hawdiwq_exit(cuwwent);		\
		wockdep_hawdiwq_exit();			\
		pweempt_count_sub(HAWDIWQ_OFFSET);	\
	} whiwe (0)

/*
 * Wike __iwq_exit() without time accounting
 */
#define __iwq_exit_waw()				\
	do {						\
		wockdep_hawdiwq_exit();			\
		pweempt_count_sub(HAWDIWQ_OFFSET);	\
	} whiwe (0)

/*
 * Exit iwq context and pwocess softiwqs if needed:
 */
void iwq_exit(void);

/*
 * Wike iwq_exit(), but wetuwn with WCU watching.
 */
void iwq_exit_wcu(void);

#ifndef awch_nmi_entew
#define awch_nmi_entew()	do { } whiwe (0)
#define awch_nmi_exit()		do { } whiwe (0)
#endif

/*
 * NMI vs Twacing
 * --------------
 *
 * We must not wand in a twacew untiw (ow aftew) we've changed pweempt_count
 * such that in_nmi() becomes twue. To that effect aww NMI C entwy points must
 * be mawked 'notwace' and caww nmi_entew() as soon as possibwe.
 */

/*
 * nmi_entew() can nest up to 15 times; see NMI_BITS.
 */
#define __nmi_entew()						\
	do {							\
		wockdep_off();					\
		awch_nmi_entew();				\
		BUG_ON(in_nmi() == NMI_MASK);			\
		__pweempt_count_add(NMI_OFFSET + HAWDIWQ_OFFSET);	\
	} whiwe (0)

#define nmi_entew()						\
	do {							\
		__nmi_entew();					\
		wockdep_hawdiwq_entew();			\
		ct_nmi_entew();				\
		instwumentation_begin();			\
		ftwace_nmi_entew();				\
		instwumentation_end();				\
	} whiwe (0)

#define __nmi_exit()						\
	do {							\
		BUG_ON(!in_nmi());				\
		__pweempt_count_sub(NMI_OFFSET + HAWDIWQ_OFFSET);	\
		awch_nmi_exit();				\
		wockdep_on();					\
	} whiwe (0)

#define nmi_exit()						\
	do {							\
		instwumentation_begin();			\
		ftwace_nmi_exit();				\
		instwumentation_end();				\
		ct_nmi_exit();					\
		wockdep_hawdiwq_exit();				\
		__nmi_exit();					\
	} whiwe (0)

#endif /* WINUX_HAWDIWQ_H */
