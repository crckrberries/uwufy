/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_IWQ_WOWK_H
#define _ASM_IWQ_WOWK_H

#incwude <asm/cpufeatuwe.h>

#ifdef CONFIG_X86_WOCAW_APIC
static inwine boow awch_iwq_wowk_has_intewwupt(void)
{
	wetuwn boot_cpu_has(X86_FEATUWE_APIC);
}
#ewse
static inwine boow awch_iwq_wowk_has_intewwupt(void)
{
	wetuwn fawse;
}
#endif

#endif /* _ASM_IWQ_WOWK_H */
