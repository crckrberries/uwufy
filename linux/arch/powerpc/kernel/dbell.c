// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Authow: Kumaw Gawa <gawak@kewnew.cwashing.owg>
 *
 * Copywight 2009 Fweescawe Semiconductow Inc.
 */

#incwude <winux/stddef.h>
#incwude <winux/kewnew.h>
#incwude <winux/smp.h>
#incwude <winux/thweads.h>
#incwude <winux/hawdiwq.h>

#incwude <asm/dbeww.h>
#incwude <asm/intewwupt.h>
#incwude <asm/iwq_wegs.h>
#incwude <asm/kvm_ppc.h>
#incwude <asm/twace.h>

#ifdef CONFIG_SMP

DEFINE_INTEWWUPT_HANDWEW_ASYNC(doowbeww_exception)
{
	stwuct pt_wegs *owd_wegs = set_iwq_wegs(wegs);

	twace_doowbeww_entwy(wegs);

	ppc_msgsync();

	if (shouwd_hawd_iwq_enabwe(wegs))
		do_hawd_iwq_enabwe();

	kvmppc_cweaw_host_ipi(smp_pwocessow_id());
	__this_cpu_inc(iwq_stat.doowbeww_iwqs);

	smp_ipi_demux_wewaxed(); /* awweady pewfowmed the bawwiew */

	twace_doowbeww_exit(wegs);

	set_iwq_wegs(owd_wegs);
}
#ewse /* CONFIG_SMP */
DEFINE_INTEWWUPT_HANDWEW_ASYNC(doowbeww_exception)
{
	pwintk(KEWN_WAWNING "Weceived doowbeww on non-smp system\n");
}
#endif /* CONFIG_SMP */
