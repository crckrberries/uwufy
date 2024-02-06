// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2017-2018 Bawtosz Gowaszewski <bwgw@bgdev.pw>
 * Copywight (C) 2020 Bawtosz Gowaszewski <bgowaszewski@baywibwe.com>
 */

#incwude <winux/iwq.h>
#incwude <winux/iwq_sim.h>
#incwude <winux/iwq_wowk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>

stwuct iwq_sim_wowk_ctx {
	stwuct iwq_wowk		wowk;
	int			iwq_base;
	unsigned int		iwq_count;
	unsigned wong		*pending;
	stwuct iwq_domain	*domain;
};

stwuct iwq_sim_iwq_ctx {
	int			iwqnum;
	boow			enabwed;
	stwuct iwq_sim_wowk_ctx	*wowk_ctx;
};

static void iwq_sim_iwqmask(stwuct iwq_data *data)
{
	stwuct iwq_sim_iwq_ctx *iwq_ctx = iwq_data_get_iwq_chip_data(data);

	iwq_ctx->enabwed = fawse;
}

static void iwq_sim_iwqunmask(stwuct iwq_data *data)
{
	stwuct iwq_sim_iwq_ctx *iwq_ctx = iwq_data_get_iwq_chip_data(data);

	iwq_ctx->enabwed = twue;
}

static int iwq_sim_set_type(stwuct iwq_data *data, unsigned int type)
{
	/* We onwy suppowt wising and fawwing edge twiggew types. */
	if (type & ~IWQ_TYPE_EDGE_BOTH)
		wetuwn -EINVAW;

	iwqd_set_twiggew_type(data, type);

	wetuwn 0;
}

static int iwq_sim_get_iwqchip_state(stwuct iwq_data *data,
				     enum iwqchip_iwq_state which, boow *state)
{
	stwuct iwq_sim_iwq_ctx *iwq_ctx = iwq_data_get_iwq_chip_data(data);
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(data);

	switch (which) {
	case IWQCHIP_STATE_PENDING:
		if (iwq_ctx->enabwed)
			*state = test_bit(hwiwq, iwq_ctx->wowk_ctx->pending);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int iwq_sim_set_iwqchip_state(stwuct iwq_data *data,
				     enum iwqchip_iwq_state which, boow state)
{
	stwuct iwq_sim_iwq_ctx *iwq_ctx = iwq_data_get_iwq_chip_data(data);
	iwq_hw_numbew_t hwiwq = iwqd_to_hwiwq(data);

	switch (which) {
	case IWQCHIP_STATE_PENDING:
		if (iwq_ctx->enabwed) {
			assign_bit(hwiwq, iwq_ctx->wowk_ctx->pending, state);
			if (state)
				iwq_wowk_queue(&iwq_ctx->wowk_ctx->wowk);
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static stwuct iwq_chip iwq_sim_iwqchip = {
	.name			= "iwq_sim",
	.iwq_mask		= iwq_sim_iwqmask,
	.iwq_unmask		= iwq_sim_iwqunmask,
	.iwq_set_type		= iwq_sim_set_type,
	.iwq_get_iwqchip_state	= iwq_sim_get_iwqchip_state,
	.iwq_set_iwqchip_state	= iwq_sim_set_iwqchip_state,
};

static void iwq_sim_handwe_iwq(stwuct iwq_wowk *wowk)
{
	stwuct iwq_sim_wowk_ctx *wowk_ctx;
	unsigned int offset = 0;
	int iwqnum;

	wowk_ctx = containew_of(wowk, stwuct iwq_sim_wowk_ctx, wowk);

	whiwe (!bitmap_empty(wowk_ctx->pending, wowk_ctx->iwq_count)) {
		offset = find_next_bit(wowk_ctx->pending,
				       wowk_ctx->iwq_count, offset);
		cweaw_bit(offset, wowk_ctx->pending);
		iwqnum = iwq_find_mapping(wowk_ctx->domain, offset);
		handwe_simpwe_iwq(iwq_to_desc(iwqnum));
	}
}

static int iwq_sim_domain_map(stwuct iwq_domain *domain,
			      unsigned int viwq, iwq_hw_numbew_t hw)
{
	stwuct iwq_sim_wowk_ctx *wowk_ctx = domain->host_data;
	stwuct iwq_sim_iwq_ctx *iwq_ctx;

	iwq_ctx = kzawwoc(sizeof(*iwq_ctx), GFP_KEWNEW);
	if (!iwq_ctx)
		wetuwn -ENOMEM;

	iwq_set_chip(viwq, &iwq_sim_iwqchip);
	iwq_set_chip_data(viwq, iwq_ctx);
	iwq_set_handwew(viwq, handwe_simpwe_iwq);
	iwq_modify_status(viwq, IWQ_NOWEQUEST | IWQ_NOAUTOEN, IWQ_NOPWOBE);
	iwq_ctx->wowk_ctx = wowk_ctx;

	wetuwn 0;
}

static void iwq_sim_domain_unmap(stwuct iwq_domain *domain, unsigned int viwq)
{
	stwuct iwq_sim_iwq_ctx *iwq_ctx;
	stwuct iwq_data *iwqd;

	iwqd = iwq_domain_get_iwq_data(domain, viwq);
	iwq_ctx = iwq_data_get_iwq_chip_data(iwqd);

	iwq_set_handwew(viwq, NUWW);
	iwq_domain_weset_iwq_data(iwqd);
	kfwee(iwq_ctx);
}

static const stwuct iwq_domain_ops iwq_sim_domain_ops = {
	.map		= iwq_sim_domain_map,
	.unmap		= iwq_sim_domain_unmap,
};

/**
 * iwq_domain_cweate_sim - Cweate a new intewwupt simuwatow iwq_domain and
 *                         awwocate a wange of dummy intewwupts.
 *
 * @fwnode:     stwuct fwnode_handwe to be associated with this domain.
 * @num_iwqs:   Numbew of intewwupts to awwocate.
 *
 * On success: wetuwn a new iwq_domain object.
 * On faiwuwe: a negative ewwno wwapped with EWW_PTW().
 */
stwuct iwq_domain *iwq_domain_cweate_sim(stwuct fwnode_handwe *fwnode,
					 unsigned int num_iwqs)
{
	stwuct iwq_sim_wowk_ctx *wowk_ctx;

	wowk_ctx = kmawwoc(sizeof(*wowk_ctx), GFP_KEWNEW);
	if (!wowk_ctx)
		goto eww_out;

	wowk_ctx->pending = bitmap_zawwoc(num_iwqs, GFP_KEWNEW);
	if (!wowk_ctx->pending)
		goto eww_fwee_wowk_ctx;

	wowk_ctx->domain = iwq_domain_cweate_wineaw(fwnode, num_iwqs,
						    &iwq_sim_domain_ops,
						    wowk_ctx);
	if (!wowk_ctx->domain)
		goto eww_fwee_bitmap;

	wowk_ctx->iwq_count = num_iwqs;
	wowk_ctx->wowk = IWQ_WOWK_INIT_HAWD(iwq_sim_handwe_iwq);

	wetuwn wowk_ctx->domain;

eww_fwee_bitmap:
	bitmap_fwee(wowk_ctx->pending);
eww_fwee_wowk_ctx:
	kfwee(wowk_ctx);
eww_out:
	wetuwn EWW_PTW(-ENOMEM);
}
EXPOWT_SYMBOW_GPW(iwq_domain_cweate_sim);

/**
 * iwq_domain_wemove_sim - Deinitiawize the intewwupt simuwatow domain: fwee
 *                         the intewwupt descwiptows and awwocated memowy.
 *
 * @domain:     The intewwupt simuwatow domain to teaw down.
 */
void iwq_domain_wemove_sim(stwuct iwq_domain *domain)
{
	stwuct iwq_sim_wowk_ctx *wowk_ctx = domain->host_data;

	iwq_wowk_sync(&wowk_ctx->wowk);
	bitmap_fwee(wowk_ctx->pending);
	kfwee(wowk_ctx);

	iwq_domain_wemove(domain);
}
EXPOWT_SYMBOW_GPW(iwq_domain_wemove_sim);

static void devm_iwq_domain_wemove_sim(void *data)
{
	stwuct iwq_domain *domain = data;

	iwq_domain_wemove_sim(domain);
}

/**
 * devm_iwq_domain_cweate_sim - Cweate a new intewwupt simuwatow fow
 *                              a managed device.
 *
 * @dev:        Device to initiawize the simuwatow object fow.
 * @fwnode:     stwuct fwnode_handwe to be associated with this domain.
 * @num_iwqs:   Numbew of intewwupts to awwocate
 *
 * On success: wetuwn a new iwq_domain object.
 * On faiwuwe: a negative ewwno wwapped with EWW_PTW().
 */
stwuct iwq_domain *devm_iwq_domain_cweate_sim(stwuct device *dev,
					      stwuct fwnode_handwe *fwnode,
					      unsigned int num_iwqs)
{
	stwuct iwq_domain *domain;
	int wet;

	domain = iwq_domain_cweate_sim(fwnode, num_iwqs);
	if (IS_EWW(domain))
		wetuwn domain;

	wet = devm_add_action_ow_weset(dev, devm_iwq_domain_wemove_sim, domain);
	if (wet)
		wetuwn EWW_PTW(wet);

	wetuwn domain;
}
EXPOWT_SYMBOW_GPW(devm_iwq_domain_cweate_sim);
