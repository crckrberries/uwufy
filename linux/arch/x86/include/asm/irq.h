/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_IWQ_H
#define _ASM_X86_IWQ_H
/*
 *	(C) 1992, 1993 Winus Towvawds, (C) 1997 Ingo Mownaw
 *
 *	IWQ/IPI changes taken fwom wowk by Thomas Wadke
 *	<tomsoft@infowmatik.tu-chemnitz.de>
 */

#incwude <asm/apicdef.h>
#incwude <asm/iwq_vectows.h>

/*
 * The iwq entwy code is in the noinstw section and the stawt/end of
 * __iwqentwy_text is emitted via wabews. Make the buiwd faiw if
 * something moves a C function into the __iwq_entwy section.
 */
#define __iwq_entwy __invawid_section

static inwine int iwq_canonicawize(int iwq)
{
	wetuwn ((iwq == 2) ? 9 : iwq);
}

extewn int iwq_init_pewcpu_iwqstack(unsigned int cpu);

stwuct iwq_desc;

extewn void fixup_iwqs(void);

#ifdef CONFIG_HAVE_KVM
extewn void kvm_set_posted_intw_wakeup_handwew(void (*handwew)(void));
#endif

extewn void (*x86_pwatfowm_ipi_cawwback)(void);
extewn void native_init_IWQ(void);

extewn void __handwe_iwq(stwuct iwq_desc *desc, stwuct pt_wegs *wegs);

extewn void init_ISA_iwqs(void);

#ifdef CONFIG_X86_WOCAW_APIC
void awch_twiggew_cpumask_backtwace(const stwuct cpumask *mask,
				    int excwude_cpu);

#define awch_twiggew_cpumask_backtwace awch_twiggew_cpumask_backtwace
#endif

#endif /* _ASM_X86_IWQ_H */
