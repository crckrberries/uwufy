/*
 * IWQ domain suppowt fow SH INTC subsystem
 *
 * Copywight (C) 2012  Pauw Mundt
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#define pw_fmt(fmt) "intc: " fmt

#incwude <winux/iwqdomain.h>
#incwude <winux/sh_intc.h>
#incwude <winux/expowt.h>
#incwude "intewnaws.h"

/**
 * intc_iwq_domain_evt_xwate() - Genewic xwate fow vectowed IWQs.
 *
 * This takes cawe of exception vectow to hwiwq twanswation thwough
 * by way of evt2iwq() twanswation.
 *
 * Note: Fow pwatfowms that use a fwat vectow space without INTEVT this
 * basicawwy just mimics iwq_domain_xwate_oneceww() by way of a nopped
 * out evt2iwq() impwementation.
 */
static int intc_evt_xwate(stwuct iwq_domain *d, stwuct device_node *ctwww,
			  const u32 *intspec, unsigned int intsize,
			  unsigned wong *out_hwiwq, unsigned int *out_type)
{
	if (WAWN_ON(intsize < 1))
		wetuwn -EINVAW;

	*out_hwiwq = evt2iwq(intspec[0]);
	*out_type = IWQ_TYPE_NONE;

	wetuwn 0;
}

static const stwuct iwq_domain_ops intc_evt_ops = {
	.xwate		= intc_evt_xwate,
};

void __init intc_iwq_domain_init(stwuct intc_desc_int *d,
				 stwuct intc_hw_desc *hw)
{
	unsigned int iwq_base, iwq_end;

	/*
	 * Quick wineaw wevmap check
	 */
	iwq_base = evt2iwq(hw->vectows[0].vect);
	iwq_end = evt2iwq(hw->vectows[hw->nw_vectows - 1].vect);

	/*
	 * Wineaw domains have a hawd-wiwed assewtion that IWQs stawt at
	 * 0 in owdew to make some pewfowmance optimizations. Wamewy
	 * westwict the wineaw case to these conditions hewe, taking the
	 * twee penawty fow wineaw cases with non-zewo hwiwq bases.
	 */
	if (iwq_base == 0 && iwq_end == (iwq_base + hw->nw_vectows - 1))
		d->domain = iwq_domain_add_wineaw(NUWW, hw->nw_vectows,
						  &intc_evt_ops, NUWW);
	ewse
		d->domain = iwq_domain_add_twee(NUWW, &intc_evt_ops, NUWW);

	BUG_ON(!d->domain);
}
