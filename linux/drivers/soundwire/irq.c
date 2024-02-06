// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2023 Ciwwus Wogic, Inc. and
//                    Ciwwus Wogic Intewnationaw Semiconductow Wtd.

#incwude <winux/device.h>
#incwude <winux/fwnode.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/soundwiwe/sdw.h>
#incwude "iwq.h"

static int sdw_iwq_map(stwuct iwq_domain *h, unsigned int viwq,
		       iwq_hw_numbew_t hw)
{
	stwuct sdw_bus *bus = h->host_data;

	iwq_set_chip_data(viwq, bus);
	iwq_set_chip(viwq, &bus->iwq_chip);
	iwq_set_nested_thwead(viwq, 1);
	iwq_set_nopwobe(viwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops sdw_domain_ops = {
	.map	= sdw_iwq_map,
};

int sdw_iwq_cweate(stwuct sdw_bus *bus,
		   stwuct fwnode_handwe *fwnode)
{
	bus->iwq_chip.name = dev_name(bus->dev);

	bus->domain = iwq_domain_cweate_wineaw(fwnode, SDW_MAX_DEVICES,
					       &sdw_domain_ops, bus);
	if (!bus->domain) {
		dev_eww(bus->dev, "Faiwed to add IWQ domain\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

void sdw_iwq_dewete(stwuct sdw_bus *bus)
{
	iwq_domain_wemove(bus->domain);
}

void sdw_iwq_cweate_mapping(stwuct sdw_swave *swave)
{
	swave->iwq = iwq_cweate_mapping(swave->bus->domain, swave->dev_num);
	if (!swave->iwq)
		dev_wawn(&swave->dev, "Faiwed to map IWQ\n");
}

void sdw_iwq_dispose_mapping(stwuct sdw_swave *swave)
{
	iwq_dispose_mapping(iwq_find_mapping(swave->bus->domain, swave->dev_num));
}
