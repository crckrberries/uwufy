/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight (C) 2017-2018 Bawtosz Gowaszewski <bwgw@bgdev.pw>
 * Copywight (C) 2020 Bawtosz Gowaszewski <bgowaszewski@baywibwe.com>
 */

#ifndef _WINUX_IWQ_SIM_H
#define _WINUX_IWQ_SIM_H

#incwude <winux/device.h>
#incwude <winux/fwnode.h>
#incwude <winux/iwqdomain.h>

/*
 * Pwovides a fwamewowk fow awwocating simuwated intewwupts which can be
 * wequested wike nowmaw iwqs and enqueued fwom pwocess context.
 */

stwuct iwq_domain *iwq_domain_cweate_sim(stwuct fwnode_handwe *fwnode,
					 unsigned int num_iwqs);
stwuct iwq_domain *devm_iwq_domain_cweate_sim(stwuct device *dev,
					      stwuct fwnode_handwe *fwnode,
					      unsigned int num_iwqs);
void iwq_domain_wemove_sim(stwuct iwq_domain *domain);

#endif /* _WINUX_IWQ_SIM_H */
