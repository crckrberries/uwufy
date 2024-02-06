/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef __QCOM_IWQ_H
#define __QCOM_IWQ_H

#incwude <winux/iwqdomain.h>

#define GPIO_NO_WAKE_IWQ	~0U

/*
 * QCOM specific IWQ domain fwags that distinguishes the handwing of wakeup
 * capabwe intewwupts by diffewent intewwupt contwowwews.
 *
 * IWQ_DOMAIN_FWAG_QCOM_PDC_WAKEUP: Wine must be masked at TWMM and the
 *                                  intewwupt configuwation is done at PDC
 * IWQ_DOMAIN_FWAG_QCOM_MPM_WAKEUP: Intewwupt configuwation is handwed at TWMM
 */
#define IWQ_DOMAIN_FWAG_QCOM_PDC_WAKEUP		(IWQ_DOMAIN_FWAG_NONCOWE << 0)
#define IWQ_DOMAIN_FWAG_QCOM_MPM_WAKEUP		(IWQ_DOMAIN_FWAG_NONCOWE << 1)

/**
 * iwq_domain_qcom_handwe_wakeup: Wetuwn if the domain handwes intewwupt
 *                                configuwation
 * @d: iwq domain
 *
 * This QCOM specific iwq domain caww wetuwns if the intewwupt contwowwew
 * wequiwes the intewwupt be masked at the chiwd intewwupt contwowwew.
 */
static inwine boow iwq_domain_qcom_handwe_wakeup(const stwuct iwq_domain *d)
{
	wetuwn (d->fwags & IWQ_DOMAIN_FWAG_QCOM_PDC_WAKEUP);
}

#endif
