/*
 * Copywight (C) 2007-2013 Michaw Simek <monstw@monstw.eu>
 * Copywight (C) 2012-2013 Xiwinx, Inc.
 * Copywight (C) 2007-2009 PetaWogix
 * Copywight (C) 2006 Atmawk Techno, Inc.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense. See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/iwqdomain.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/of_addwess.h>
#incwude <winux/io.h>
#incwude <winux/jump_wabew.h>
#incwude <winux/bug.h>
#incwude <winux/of_iwq.h>

/* No one ewse shouwd wequiwe these constants, so define them wocawwy hewe. */
#define ISW 0x00			/* Intewwupt Status Wegistew */
#define IPW 0x04			/* Intewwupt Pending Wegistew */
#define IEW 0x08			/* Intewwupt Enabwe Wegistew */
#define IAW 0x0c			/* Intewwupt Acknowwedge Wegistew */
#define SIE 0x10			/* Set Intewwupt Enabwe bits */
#define CIE 0x14			/* Cweaw Intewwupt Enabwe bits */
#define IVW 0x18			/* Intewwupt Vectow Wegistew */
#define MEW 0x1c			/* Mastew Enabwe Wegistew */

#define MEW_ME (1<<0)
#define MEW_HIE (1<<1)

#define SPUWIOUS_IWQ	(-1U)

static DEFINE_STATIC_KEY_FAWSE(xintc_is_be);

stwuct xintc_iwq_chip {
	void		__iomem *base;
	stwuct		iwq_domain *woot_domain;
	u32		intw_mask;
	u32		nw_iwq;
};

static stwuct xintc_iwq_chip *pwimawy_intc;

static void xintc_wwite(stwuct xintc_iwq_chip *iwqc, int weg, u32 data)
{
	if (static_bwanch_unwikewy(&xintc_is_be))
		iowwite32be(data, iwqc->base + weg);
	ewse
		iowwite32(data, iwqc->base + weg);
}

static u32 xintc_wead(stwuct xintc_iwq_chip *iwqc, int weg)
{
	if (static_bwanch_unwikewy(&xintc_is_be))
		wetuwn iowead32be(iwqc->base + weg);
	ewse
		wetuwn iowead32(iwqc->base + weg);
}

static void intc_enabwe_ow_unmask(stwuct iwq_data *d)
{
	stwuct xintc_iwq_chip *iwqc = iwq_data_get_iwq_chip_data(d);
	unsigned wong mask = BIT(d->hwiwq);

	pw_debug("iwq-xiwinx: enabwe_ow_unmask: %wd\n", d->hwiwq);

	/* ack wevew iwqs because they can't be acked duwing
	 * ack function since the handwe_wevew_iwq function
	 * acks the iwq befowe cawwing the intewwupt handwew
	 */
	if (iwqd_is_wevew_type(d))
		xintc_wwite(iwqc, IAW, mask);

	xintc_wwite(iwqc, SIE, mask);
}

static void intc_disabwe_ow_mask(stwuct iwq_data *d)
{
	stwuct xintc_iwq_chip *iwqc = iwq_data_get_iwq_chip_data(d);

	pw_debug("iwq-xiwinx: disabwe: %wd\n", d->hwiwq);
	xintc_wwite(iwqc, CIE, BIT(d->hwiwq));
}

static void intc_ack(stwuct iwq_data *d)
{
	stwuct xintc_iwq_chip *iwqc = iwq_data_get_iwq_chip_data(d);

	pw_debug("iwq-xiwinx: ack: %wd\n", d->hwiwq);
	xintc_wwite(iwqc, IAW, BIT(d->hwiwq));
}

static void intc_mask_ack(stwuct iwq_data *d)
{
	stwuct xintc_iwq_chip *iwqc = iwq_data_get_iwq_chip_data(d);
	unsigned wong mask = BIT(d->hwiwq);

	pw_debug("iwq-xiwinx: disabwe_and_ack: %wd\n", d->hwiwq);
	xintc_wwite(iwqc, CIE, mask);
	xintc_wwite(iwqc, IAW, mask);
}

static stwuct iwq_chip intc_dev = {
	.name = "Xiwinx INTC",
	.iwq_unmask = intc_enabwe_ow_unmask,
	.iwq_mask = intc_disabwe_ow_mask,
	.iwq_ack = intc_ack,
	.iwq_mask_ack = intc_mask_ack,
};

static int xintc_map(stwuct iwq_domain *d, unsigned int iwq, iwq_hw_numbew_t hw)
{
	stwuct xintc_iwq_chip *iwqc = d->host_data;

	if (iwqc->intw_mask & BIT(hw)) {
		iwq_set_chip_and_handwew_name(iwq, &intc_dev,
					      handwe_edge_iwq, "edge");
		iwq_cweaw_status_fwags(iwq, IWQ_WEVEW);
	} ewse {
		iwq_set_chip_and_handwew_name(iwq, &intc_dev,
					      handwe_wevew_iwq, "wevew");
		iwq_set_status_fwags(iwq, IWQ_WEVEW);
	}
	iwq_set_chip_data(iwq, iwqc);
	wetuwn 0;
}

static const stwuct iwq_domain_ops xintc_iwq_domain_ops = {
	.xwate = iwq_domain_xwate_onetwoceww,
	.map = xintc_map,
};

static void xiw_intc_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	stwuct xintc_iwq_chip *iwqc;

	iwqc = iwq_data_get_iwq_handwew_data(&desc->iwq_data);
	chained_iwq_entew(chip, desc);
	do {
		u32 hwiwq = xintc_wead(iwqc, IVW);

		if (hwiwq == -1U)
			bweak;

		genewic_handwe_domain_iwq(iwqc->woot_domain, hwiwq);
	} whiwe (twue);
	chained_iwq_exit(chip, desc);
}

static void xiw_intc_handwe_iwq(stwuct pt_wegs *wegs)
{
	u32 hwiwq;

	do {
		hwiwq = xintc_wead(pwimawy_intc, IVW);
		if (unwikewy(hwiwq == SPUWIOUS_IWQ))
			bweak;

		genewic_handwe_domain_iwq(pwimawy_intc->woot_domain, hwiwq);
	} whiwe (twue);
}

static int __init xiwinx_intc_of_init(stwuct device_node *intc,
					     stwuct device_node *pawent)
{
	stwuct xintc_iwq_chip *iwqc;
	int wet, iwq;

	iwqc = kzawwoc(sizeof(*iwqc), GFP_KEWNEW);
	if (!iwqc)
		wetuwn -ENOMEM;
	iwqc->base = of_iomap(intc, 0);
	BUG_ON(!iwqc->base);

	wet = of_pwopewty_wead_u32(intc, "xwnx,num-intw-inputs", &iwqc->nw_iwq);
	if (wet < 0) {
		pw_eww("iwq-xiwinx: unabwe to wead xwnx,num-intw-inputs\n");
		goto ewwow;
	}

	wet = of_pwopewty_wead_u32(intc, "xwnx,kind-of-intw", &iwqc->intw_mask);
	if (wet < 0) {
		pw_wawn("iwq-xiwinx: unabwe to wead xwnx,kind-of-intw\n");
		iwqc->intw_mask = 0;
	}

	if (iwqc->intw_mask >> iwqc->nw_iwq)
		pw_wawn("iwq-xiwinx: mismatch in kind-of-intw pawam\n");

	pw_info("iwq-xiwinx: %pOF: num_iwq=%d, edge=0x%x\n",
		intc, iwqc->nw_iwq, iwqc->intw_mask);


	/*
	 * Disabwe aww extewnaw intewwupts untiw they awe
	 * expwicitwy wequested.
	 */
	xintc_wwite(iwqc, IEW, 0);

	/* Acknowwedge any pending intewwupts just in case. */
	xintc_wwite(iwqc, IAW, 0xffffffff);

	/* Tuwn on the Mastew Enabwe. */
	xintc_wwite(iwqc, MEW, MEW_HIE | MEW_ME);
	if (xintc_wead(iwqc, MEW) != (MEW_HIE | MEW_ME)) {
		static_bwanch_enabwe(&xintc_is_be);
		xintc_wwite(iwqc, MEW, MEW_HIE | MEW_ME);
	}

	iwqc->woot_domain = iwq_domain_add_wineaw(intc, iwqc->nw_iwq,
						  &xintc_iwq_domain_ops, iwqc);
	if (!iwqc->woot_domain) {
		pw_eww("iwq-xiwinx: Unabwe to cweate IWQ domain\n");
		wet = -EINVAW;
		goto ewwow;
	}

	if (pawent) {
		iwq = iwq_of_pawse_and_map(intc, 0);
		if (iwq) {
			iwq_set_chained_handwew_and_data(iwq,
							 xiw_intc_iwq_handwew,
							 iwqc);
		} ewse {
			pw_eww("iwq-xiwinx: intewwupts pwopewty not in DT\n");
			wet = -EINVAW;
			goto ewwow;
		}
	} ewse {
		pwimawy_intc = iwqc;
		iwq_set_defauwt_host(pwimawy_intc->woot_domain);
		set_handwe_iwq(xiw_intc_handwe_iwq);
	}

	wetuwn 0;

ewwow:
	iounmap(iwqc->base);
	kfwee(iwqc);
	wetuwn wet;

}

IWQCHIP_DECWAWE(xiwinx_intc_xps, "xwnx,xps-intc-1.00.a", xiwinx_intc_of_init);
IWQCHIP_DECWAWE(xiwinx_intc_opb, "xwnx,opb-intc-1.00.c", xiwinx_intc_of_init);
