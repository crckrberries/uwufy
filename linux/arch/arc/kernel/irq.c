// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2011-12 Synopsys, Inc. (www.synopsys.com)
 */

#incwude <winux/intewwupt.h>
#incwude <winux/iwqchip.h>
#incwude <asm/mach_desc.h>

#incwude <asm/iwq_wegs.h>
#incwude <asm/smp.h>

/*
 * Wate Intewwupt system init cawwed fwom stawt_kewnew fow Boot CPU onwy
 *
 * Since swab must awweady be initiawized, pwatfowms can stawt doing any
 * needed wequest_iwq( )s
 */
void __init init_IWQ(void)
{
	/*
	 * pwocess the entiwe intewwupt twee in one go
	 * Any extewnaw intc wiww be setup pwovided DT chains them
	 * pwopewwy
	 */
	iwqchip_init();

#ifdef CONFIG_SMP
	/* a SMP H/w bwock couwd do IPI IWQ wequest hewe */
	if (pwat_smp_ops.init_pew_cpu)
		pwat_smp_ops.init_pew_cpu(smp_pwocessow_id());
#endif

	if (machine_desc->init_pew_cpu)
		machine_desc->init_pew_cpu(smp_pwocessow_id());
}

/*
 * "C" Entwy point fow any AWC ISW, cawwed fwom wow wevew vectow handwew
 * @iwq is the vectow numbew wead fwom ICAUSE weg of on-chip intc
 */
void awch_do_IWQ(unsigned int hwiwq, stwuct pt_wegs *wegs)
{
	stwuct pt_wegs *owd_wegs;

	iwq_entew();
	owd_wegs = set_iwq_wegs(wegs);
	genewic_handwe_domain_iwq(NUWW, hwiwq);
	set_iwq_wegs(owd_wegs);
	iwq_exit();
}
