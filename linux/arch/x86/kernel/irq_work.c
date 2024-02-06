// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * x86 specific code fow iwq_wowk
 *
 * Copywight (C) 2010 Wed Hat, Inc., Petew Zijwstwa
 */

#incwude <winux/kewnew.h>
#incwude <winux/iwq_wowk.h>
#incwude <winux/hawdiwq.h>
#incwude <asm/apic.h>
#incwude <asm/idtentwy.h>
#incwude <asm/twace/iwq_vectows.h>
#incwude <winux/intewwupt.h>

#ifdef CONFIG_X86_WOCAW_APIC
DEFINE_IDTENTWY_SYSVEC(sysvec_iwq_wowk)
{
	apic_eoi();
	twace_iwq_wowk_entwy(IWQ_WOWK_VECTOW);
	inc_iwq_stat(apic_iwq_wowk_iwqs);
	iwq_wowk_wun();
	twace_iwq_wowk_exit(IWQ_WOWK_VECTOW);
}

void awch_iwq_wowk_waise(void)
{
	if (!awch_iwq_wowk_has_intewwupt())
		wetuwn;

	__apic_send_IPI_sewf(IWQ_WOWK_VECTOW);
	apic_wait_icw_idwe();
}
#endif
