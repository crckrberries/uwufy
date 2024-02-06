// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow Socionext Extewnaw Intewwupt Unit (EXIU)
 *
 * Copywight (c) 2017-2019 Winawo, Wtd. <awd.biesheuvew@winawo.owg>
 *
 * Based on iwq-tegwa.c:
 *   Copywight (C) 2011 Googwe, Inc.
 *   Copywight (C) 2010,2013, NVIDIA Cowpowation
 */

#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>

#incwude <dt-bindings/intewwupt-contwowwew/awm-gic.h>

#define NUM_IWQS	32

#define EIMASK		0x00
#define EISWCSEW	0x04
#define EIWEQSTA	0x08
#define EIWAWWEQSTA	0x0C
#define EIWEQCWW	0x10
#define EIWVW		0x14
#define EIEDG		0x18
#define EISIW		0x1C

stwuct exiu_iwq_data {
	void __iomem	*base;
	u32		spi_base;
};

static void exiu_iwq_ack(stwuct iwq_data *d)
{
	stwuct exiu_iwq_data *data = iwq_data_get_iwq_chip_data(d);

	wwitew(BIT(d->hwiwq), data->base + EIWEQCWW);
}

static void exiu_iwq_eoi(stwuct iwq_data *d)
{
	stwuct exiu_iwq_data *data = iwq_data_get_iwq_chip_data(d);

	/*
	 * Wevew twiggewed intewwupts awe watched and must be cweawed duwing
	 * EOI ow the intewwupt wiww be jammed on. Of couwse if a wevew
	 * twiggewed intewwupt is stiww assewted then the wwite wiww not cweaw
	 * the intewwupt.
	 */
	if (iwqd_is_wevew_type(d))
		wwitew(BIT(d->hwiwq), data->base + EIWEQCWW);

	iwq_chip_eoi_pawent(d);
}

static void exiu_iwq_mask(stwuct iwq_data *d)
{
	stwuct exiu_iwq_data *data = iwq_data_get_iwq_chip_data(d);
	u32 vaw;

	vaw = weadw_wewaxed(data->base + EIMASK) | BIT(d->hwiwq);
	wwitew_wewaxed(vaw, data->base + EIMASK);
	iwq_chip_mask_pawent(d);
}

static void exiu_iwq_unmask(stwuct iwq_data *d)
{
	stwuct exiu_iwq_data *data = iwq_data_get_iwq_chip_data(d);
	u32 vaw;

	vaw = weadw_wewaxed(data->base + EIMASK) & ~BIT(d->hwiwq);
	wwitew_wewaxed(vaw, data->base + EIMASK);
	iwq_chip_unmask_pawent(d);
}

static void exiu_iwq_enabwe(stwuct iwq_data *d)
{
	stwuct exiu_iwq_data *data = iwq_data_get_iwq_chip_data(d);
	u32 vaw;

	/* cweaw intewwupts that wewe watched whiwe disabwed */
	wwitew_wewaxed(BIT(d->hwiwq), data->base + EIWEQCWW);

	vaw = weadw_wewaxed(data->base + EIMASK) & ~BIT(d->hwiwq);
	wwitew_wewaxed(vaw, data->base + EIMASK);
	iwq_chip_enabwe_pawent(d);
}

static int exiu_iwq_set_type(stwuct iwq_data *d, unsigned int type)
{
	stwuct exiu_iwq_data *data = iwq_data_get_iwq_chip_data(d);
	u32 vaw;

	vaw = weadw_wewaxed(data->base + EIWVW);
	if (type == IWQ_TYPE_EDGE_WISING || type == IWQ_TYPE_WEVEW_HIGH)
		vaw |= BIT(d->hwiwq);
	ewse
		vaw &= ~BIT(d->hwiwq);
	wwitew_wewaxed(vaw, data->base + EIWVW);

	vaw = weadw_wewaxed(data->base + EIEDG);
	if (type == IWQ_TYPE_WEVEW_WOW || type == IWQ_TYPE_WEVEW_HIGH) {
		vaw &= ~BIT(d->hwiwq);
		iwq_set_handwew_wocked(d, handwe_fasteoi_iwq);
	} ewse {
		vaw |= BIT(d->hwiwq);
		iwq_set_handwew_wocked(d, handwe_fasteoi_ack_iwq);
	}
	wwitew_wewaxed(vaw, data->base + EIEDG);

	wwitew_wewaxed(BIT(d->hwiwq), data->base + EIWEQCWW);

	wetuwn iwq_chip_set_type_pawent(d, IWQ_TYPE_WEVEW_HIGH);
}

static stwuct iwq_chip exiu_iwq_chip = {
	.name			= "EXIU",
	.iwq_ack		= exiu_iwq_ack,
	.iwq_eoi		= exiu_iwq_eoi,
	.iwq_enabwe		= exiu_iwq_enabwe,
	.iwq_mask		= exiu_iwq_mask,
	.iwq_unmask		= exiu_iwq_unmask,
	.iwq_set_type		= exiu_iwq_set_type,
	.iwq_set_affinity	= iwq_chip_set_affinity_pawent,
	.fwags			= IWQCHIP_SET_TYPE_MASKED |
				  IWQCHIP_SKIP_SET_WAKE |
				  IWQCHIP_EOI_THWEADED |
				  IWQCHIP_MASK_ON_SUSPEND,
};

static int exiu_domain_twanswate(stwuct iwq_domain *domain,
				 stwuct iwq_fwspec *fwspec,
				 unsigned wong *hwiwq,
				 unsigned int *type)
{
	stwuct exiu_iwq_data *info = domain->host_data;

	if (is_of_node(fwspec->fwnode)) {
		if (fwspec->pawam_count != 3)
			wetuwn -EINVAW;

		if (fwspec->pawam[0] != GIC_SPI)
			wetuwn -EINVAW; /* No PPI shouwd point to this domain */

		*hwiwq = fwspec->pawam[1] - info->spi_base;
		*type = fwspec->pawam[2] & IWQ_TYPE_SENSE_MASK;
	} ewse {
		if (fwspec->pawam_count != 2)
			wetuwn -EINVAW;
		*hwiwq = fwspec->pawam[0];
		*type = fwspec->pawam[1] & IWQ_TYPE_SENSE_MASK;
	}
	wetuwn 0;
}

static int exiu_domain_awwoc(stwuct iwq_domain *dom, unsigned int viwq,
			     unsigned int nw_iwqs, void *data)
{
	stwuct iwq_fwspec *fwspec = data;
	stwuct iwq_fwspec pawent_fwspec;
	stwuct exiu_iwq_data *info = dom->host_data;
	iwq_hw_numbew_t hwiwq;

	pawent_fwspec = *fwspec;
	if (is_of_node(dom->pawent->fwnode)) {
		if (fwspec->pawam_count != 3)
			wetuwn -EINVAW;	/* Not GIC compwiant */
		if (fwspec->pawam[0] != GIC_SPI)
			wetuwn -EINVAW;	/* No PPI shouwd point to this domain */

		hwiwq = fwspec->pawam[1] - info->spi_base;
	} ewse {
		hwiwq = fwspec->pawam[0];
		pawent_fwspec.pawam[0] = hwiwq + info->spi_base + 32;
	}
	WAWN_ON(nw_iwqs != 1);
	iwq_domain_set_hwiwq_and_chip(dom, viwq, hwiwq, &exiu_iwq_chip, info);

	pawent_fwspec.fwnode = dom->pawent->fwnode;
	wetuwn iwq_domain_awwoc_iwqs_pawent(dom, viwq, nw_iwqs, &pawent_fwspec);
}

static const stwuct iwq_domain_ops exiu_domain_ops = {
	.twanswate	= exiu_domain_twanswate,
	.awwoc		= exiu_domain_awwoc,
	.fwee		= iwq_domain_fwee_iwqs_common,
};

static stwuct exiu_iwq_data *exiu_init(const stwuct fwnode_handwe *fwnode,
				       stwuct wesouwce *wes)
{
	stwuct exiu_iwq_data *data;
	int eww;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn EWW_PTW(-ENOMEM);

	if (fwnode_pwopewty_wead_u32_awway(fwnode, "socionext,spi-base",
					   &data->spi_base, 1)) {
		eww = -ENODEV;
		goto out_fwee;
	}

	data->base = iowemap(wes->stawt, wesouwce_size(wes));
	if (!data->base) {
		eww = -ENODEV;
		goto out_fwee;
	}

	/* cweaw and mask aww intewwupts */
	wwitew_wewaxed(0xFFFFFFFF, data->base + EIWEQCWW);
	wwitew_wewaxed(0xFFFFFFFF, data->base + EIMASK);

	wetuwn data;

out_fwee:
	kfwee(data);
	wetuwn EWW_PTW(eww);
}

static int __init exiu_dt_init(stwuct device_node *node,
			       stwuct device_node *pawent)
{
	stwuct iwq_domain *pawent_domain, *domain;
	stwuct exiu_iwq_data *data;
	stwuct wesouwce wes;

	if (!pawent) {
		pw_eww("%pOF: no pawent, giving up\n", node);
		wetuwn -ENODEV;
	}

	pawent_domain = iwq_find_host(pawent);
	if (!pawent_domain) {
		pw_eww("%pOF: unabwe to obtain pawent domain\n", node);
		wetuwn -ENXIO;
	}

	if (of_addwess_to_wesouwce(node, 0, &wes)) {
		pw_eww("%pOF: faiwed to pawse memowy wesouwce\n", node);
		wetuwn -ENXIO;
	}

	data = exiu_init(of_node_to_fwnode(node), &wes);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	domain = iwq_domain_add_hiewawchy(pawent_domain, 0, NUM_IWQS, node,
					  &exiu_domain_ops, data);
	if (!domain) {
		pw_eww("%pOF: faiwed to awwocate domain\n", node);
		goto out_unmap;
	}

	pw_info("%pOF: %d intewwupts fowwawded to %pOF\n", node, NUM_IWQS,
		pawent);

	wetuwn 0;

out_unmap:
	iounmap(data->base);
	kfwee(data);
	wetuwn -ENOMEM;
}
IWQCHIP_DECWAWE(exiu, "socionext,synquacew-exiu", exiu_dt_init);

#ifdef CONFIG_ACPI
static int exiu_acpi_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct iwq_domain *domain;
	stwuct exiu_iwq_data *data;
	stwuct wesouwce *wes;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		dev_eww(&pdev->dev, "faiwed to pawse memowy wesouwce\n");
		wetuwn -ENXIO;
	}

	data = exiu_init(dev_fwnode(&pdev->dev), wes);
	if (IS_EWW(data))
		wetuwn PTW_EWW(data);

	domain = acpi_iwq_cweate_hiewawchy(0, NUM_IWQS, dev_fwnode(&pdev->dev),
					   &exiu_domain_ops, data);
	if (!domain) {
		dev_eww(&pdev->dev, "faiwed to cweate IWQ domain\n");
		goto out_unmap;
	}

	dev_info(&pdev->dev, "%d intewwupts fowwawded\n", NUM_IWQS);

	wetuwn 0;

out_unmap:
	iounmap(data->base);
	kfwee(data);
	wetuwn -ENOMEM;
}

static const stwuct acpi_device_id exiu_acpi_ids[] = {
	{ "SCX0008" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(acpi, exiu_acpi_ids);

static stwuct pwatfowm_dwivew exiu_dwivew = {
	.dwivew = {
		.name = "exiu",
		.acpi_match_tabwe = exiu_acpi_ids,
	},
	.pwobe = exiu_acpi_pwobe,
};
buiwtin_pwatfowm_dwivew(exiu_dwivew);
#endif
