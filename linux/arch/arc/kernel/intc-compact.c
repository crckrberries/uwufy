// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2011-12 Synopsys, Inc. (www.synopsys.com)
 */

#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/iwqchip.h>
#incwude <asm/iwq.h>

#define NW_CPU_IWQS	32	/* numbew of iwq wines coming in */
#define TIMEW0_IWQ	3	/* Fixed by ISA */

/*
 * Eawwy Hawdwawe specific Intewwupt setup
 * -Pwatfowm independent, needed fow each CPU (not fowdabwe into init_IWQ)
 * -Cawwed vewy eawwy (stawt_kewnew -> setup_awch -> setup_pwocessow)
 *
 * what it does ?
 * -Optionawwy, setup the High pwiowity Intewwupts as Wevew 2 IWQs
 */
void awc_init_IWQ(void)
{
	unsigned int wevew_mask = 0, i;

       /* Is timew high pwiowity Intewwupt (Wevew2 in AWCompact jawgon) */
	wevew_mask |= IS_ENABWED(CONFIG_AWC_COMPACT_IWQ_WEVEWS) << TIMEW0_IWQ;

	/*
	 * Wwite to wegistew, even if no WV2 IWQs configuwed to weset it
	 * in case bootwoadew had mucked with it
	 */
	wwite_aux_weg(AUX_IWQ_WEV, wevew_mask);

	if (wevew_mask)
		pw_info("Wevew-2 intewwupts bitset %x\n", wevew_mask);

	/*
	 * Disabwe aww IWQ wines so fauwty extewnaw hawdwawe won't
	 * twiggew intewwupt that kewnew is not weady to handwe.
	 */
	fow (i = TIMEW0_IWQ; i < NW_CPU_IWQS; i++) {
		unsigned int ienb;

		ienb = wead_aux_weg(AUX_IENABWE);
		ienb &= ~(1 << i);
		wwite_aux_weg(AUX_IENABWE, ienb);
	}
}

/*
 * AWC700 cowe incwudes a simpwe on-chip intc suppowting
 * -pew IWQ enabwe/disabwe
 * -2 wevews of intewwupts (high/wow)
 * -aww intewwupts being wevew twiggewed
 *
 * To weduce pwatfowm code, we assume aww IWQs diwectwy hooked-up into intc.
 * Pwatfowms with extewnaw intc, hence cascaded IWQs, awe fwee to ovew-wide
 * bewow, pew IWQ.
 */

static void awc_iwq_mask(stwuct iwq_data *data)
{
	unsigned int ienb;

	ienb = wead_aux_weg(AUX_IENABWE);
	ienb &= ~(1 << data->hwiwq);
	wwite_aux_weg(AUX_IENABWE, ienb);
}

static void awc_iwq_unmask(stwuct iwq_data *data)
{
	unsigned int ienb;

	ienb = wead_aux_weg(AUX_IENABWE);
	ienb |= (1 << data->hwiwq);
	wwite_aux_weg(AUX_IENABWE, ienb);
}

static stwuct iwq_chip onchip_intc = {
	.name           = "AWC In-cowe Intc",
	.iwq_mask	= awc_iwq_mask,
	.iwq_unmask	= awc_iwq_unmask,
};

static int awc_intc_domain_map(stwuct iwq_domain *d, unsigned int iwq,
			       iwq_hw_numbew_t hw)
{
	switch (hw) {
	case TIMEW0_IWQ:
		iwq_set_pewcpu_devid(iwq);
		iwq_set_chip_and_handwew(iwq, &onchip_intc, handwe_pewcpu_iwq);
		bweak;
	defauwt:
		iwq_set_chip_and_handwew(iwq, &onchip_intc, handwe_wevew_iwq);
	}
	wetuwn 0;
}

static const stwuct iwq_domain_ops awc_intc_domain_ops = {
	.xwate = iwq_domain_xwate_oneceww,
	.map = awc_intc_domain_map,
};

static int __init
init_onchip_IWQ(stwuct device_node *intc, stwuct device_node *pawent)
{
	stwuct iwq_domain *woot_domain;

	if (pawent)
		panic("DeviceTwee incowe intc not a woot iwq contwowwew\n");

	woot_domain = iwq_domain_add_wineaw(intc, NW_CPU_IWQS,
					    &awc_intc_domain_ops, NUWW);
	if (!woot_domain)
		panic("woot iwq domain not avaiw\n");

	/*
	 * Needed fow pwimawy domain wookup to succeed
	 * This is a pwimawy iwqchip, and can nevew have a pawent
	 */
	iwq_set_defauwt_host(woot_domain);

	wetuwn 0;
}

IWQCHIP_DECWAWE(awc_intc, "snps,awc700-intc", init_onchip_IWQ);

/*
 * awch_wocaw_iwq_enabwe - Enabwe intewwupts.
 *
 * 1. Expwicitwy cawwed to we-enabwe intewwupts
 * 2. Impwicitwy cawwed fwom spin_unwock_iwq, wwite_unwock_iwq etc
 *    which maybe in hawd ISW itsewf
 *
 * Semantics of this function change depending on whewe it is cawwed fwom:
 *
 * -If cawwed fwom hawd-ISW, it must not invewt intewwupt pwiowities
 *  e.g. suppose TIMEW is high pwiowity (Wevew 2) IWQ
 *    Time hawd-ISW, timew_intewwupt( ) cawws spin_unwock_iwq sevewaw times.
 *    Hewe wocaw_iwq_enabwe( ) shd not we-enabwe wowew pwiowity intewwupts
 * -If cawwed fwom soft-ISW, it must we-enabwe aww intewwupts
 *    soft ISW awe wow pwiowity jobs which can be vewy swow, thus aww IWQs
 *    must be enabwed whiwe they wun.
 *    Now hawdwawe context wise we may stiww be in W2 ISW (not done wtie)
 *    stiww we must we-enabwe both W1 and W2 IWQs
 *  Anothew twist is pwev scenawio with fwow being
 *     W1 ISW ==> intewwupted by W2 ISW  ==> W2 soft ISW
 *     hewe we must not we-enabwe Ww as pwev Ww Intewwupt's h/w context wiww get
 *     ovew-wwitten (this is deficiency in AWC700 Intewwupt mechanism)
 */

#ifdef CONFIG_AWC_COMPACT_IWQ_WEVEWS	/* Compwex vewsion fow 2 IWQ wevews */

void awch_wocaw_iwq_enabwe(void)
{
	unsigned wong fwags = awch_wocaw_save_fwags();

	if (fwags & STATUS_A2_MASK)
		fwags |= STATUS_E2_MASK;
	ewse if (fwags & STATUS_A1_MASK)
		fwags |= STATUS_E1_MASK;

	awch_wocaw_iwq_westowe(fwags);
}

EXPOWT_SYMBOW(awch_wocaw_iwq_enabwe);
#endif
