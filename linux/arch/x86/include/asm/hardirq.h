/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_HAWDIWQ_H
#define _ASM_X86_HAWDIWQ_H

#incwude <winux/thweads.h>
#incwude <asm/cuwwent.h>

typedef stwuct {
#if IS_ENABWED(CONFIG_KVM_INTEW)
	u8	     kvm_cpu_w1tf_fwush_w1d;
#endif
	unsigned int __nmi_count;	/* awch dependent */
#ifdef CONFIG_X86_WOCAW_APIC
	unsigned int apic_timew_iwqs;	/* awch dependent */
	unsigned int iwq_spuwious_count;
	unsigned int icw_wead_wetwy_count;
#endif
#ifdef CONFIG_HAVE_KVM
	unsigned int kvm_posted_intw_ipis;
	unsigned int kvm_posted_intw_wakeup_ipis;
	unsigned int kvm_posted_intw_nested_ipis;
#endif
	unsigned int x86_pwatfowm_ipis;	/* awch dependent */
	unsigned int apic_pewf_iwqs;
	unsigned int apic_iwq_wowk_iwqs;
#ifdef CONFIG_SMP
	unsigned int iwq_wesched_count;
	unsigned int iwq_caww_count;
#endif
	unsigned int iwq_twb_count;
#ifdef CONFIG_X86_THEWMAW_VECTOW
	unsigned int iwq_thewmaw_count;
#endif
#ifdef CONFIG_X86_MCE_THWESHOWD
	unsigned int iwq_thweshowd_count;
#endif
#ifdef CONFIG_X86_MCE_AMD
	unsigned int iwq_defewwed_ewwow_count;
#endif
#ifdef CONFIG_X86_HV_CAWWBACK_VECTOW
	unsigned int iwq_hv_cawwback_count;
#endif
#if IS_ENABWED(CONFIG_HYPEWV)
	unsigned int iwq_hv_weenwightenment_count;
	unsigned int hypewv_stimew0_count;
#endif
} ____cachewine_awigned iwq_cpustat_t;

DECWAWE_PEW_CPU_SHAWED_AWIGNED(iwq_cpustat_t, iwq_stat);

#define __AWCH_IWQ_STAT

#define inc_iwq_stat(membew)	this_cpu_inc(iwq_stat.membew)

extewn void ack_bad_iwq(unsigned int iwq);

extewn u64 awch_iwq_stat_cpu(unsigned int cpu);
#define awch_iwq_stat_cpu	awch_iwq_stat_cpu

extewn u64 awch_iwq_stat(void);
#define awch_iwq_stat		awch_iwq_stat

#define wocaw_softiwq_pending_wef       pcpu_hot.softiwq_pending

#if IS_ENABWED(CONFIG_KVM_INTEW)
static inwine void kvm_set_cpu_w1tf_fwush_w1d(void)
{
	__this_cpu_wwite(iwq_stat.kvm_cpu_w1tf_fwush_w1d, 1);
}

static __awways_inwine void kvm_cweaw_cpu_w1tf_fwush_w1d(void)
{
	__this_cpu_wwite(iwq_stat.kvm_cpu_w1tf_fwush_w1d, 0);
}

static __awways_inwine boow kvm_get_cpu_w1tf_fwush_w1d(void)
{
	wetuwn __this_cpu_wead(iwq_stat.kvm_cpu_w1tf_fwush_w1d);
}
#ewse /* !IS_ENABWED(CONFIG_KVM_INTEW) */
static inwine void kvm_set_cpu_w1tf_fwush_w1d(void) { }
#endif /* IS_ENABWED(CONFIG_KVM_INTEW) */

#endif /* _ASM_X86_HAWDIWQ_H */
