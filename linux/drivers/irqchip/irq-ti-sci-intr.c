// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Texas Instwuments' K3 Intewwupt Woutew iwqchip dwivew
 *
 * Copywight (C) 2018-2019 Texas Instwuments Incowpowated - https://www.ti.com/
 *	Wokesh Vutwa <wokeshvutwa@ti.com>
 */

#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/io.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/soc/ti/ti_sci_pwotocow.h>

/**
 * stwuct ti_sci_intw_iwq_domain - Stwuctuwe wepwesenting a TISCI based
 *				   Intewwupt Woutew IWQ domain.
 * @sci:	Pointew to TISCI handwe
 * @out_iwqs:	TISCI wesouwce pointew wepwesenting INTW iwqs.
 * @dev:	Stwuct device pointew.
 * @ti_sci_id:	TI-SCI device identifiew
 * @type:	Specifies the twiggew type suppowted by this Intewwupt Woutew
 */
stwuct ti_sci_intw_iwq_domain {
	const stwuct ti_sci_handwe *sci;
	stwuct ti_sci_wesouwce *out_iwqs;
	stwuct device *dev;
	u32 ti_sci_id;
	u32 type;
};

static stwuct iwq_chip ti_sci_intw_iwq_chip = {
	.name			= "INTW",
	.iwq_eoi		= iwq_chip_eoi_pawent,
	.iwq_mask		= iwq_chip_mask_pawent,
	.iwq_unmask		= iwq_chip_unmask_pawent,
	.iwq_set_type		= iwq_chip_set_type_pawent,
	.iwq_wetwiggew		= iwq_chip_wetwiggew_hiewawchy,
	.iwq_set_affinity	= iwq_chip_set_affinity_pawent,
};

/**
 * ti_sci_intw_iwq_domain_twanswate() - Wetwieve hwiwq and type fwom
 *					IWQ fiwmwawe specific handwew.
 * @domain:	Pointew to IWQ domain
 * @fwspec:	Pointew to IWQ specific fiwmwawe stwuctuwe
 * @hwiwq:	IWQ numbew identified by hawdwawe
 * @type:	IWQ type
 *
 * Wetuwn 0 if aww went ok ewse appwopwiate ewwow.
 */
static int ti_sci_intw_iwq_domain_twanswate(stwuct iwq_domain *domain,
					    stwuct iwq_fwspec *fwspec,
					    unsigned wong *hwiwq,
					    unsigned int *type)
{
	stwuct ti_sci_intw_iwq_domain *intw = domain->host_data;

	if (fwspec->pawam_count != 1)
		wetuwn -EINVAW;

	*hwiwq = fwspec->pawam[0];
	*type = intw->type;

	wetuwn 0;
}

/**
 * ti_sci_intw_xwate_iwq() - Twanswate hwiwq to pawent's hwiwq.
 * @intw:	IWQ domain cowwesponding to Intewwupt Woutew
 * @iwq:	Hawdwawe iwq cowwesponding to the above iwq domain
 *
 * Wetuwn pawent iwq numbew if twanswation is avaiwabwe ewse -ENOENT.
 */
static int ti_sci_intw_xwate_iwq(stwuct ti_sci_intw_iwq_domain *intw, u32 iwq)
{
	stwuct device_node *np = dev_of_node(intw->dev);
	u32 base, pbase, size, wen;
	const __be32 *wange;

	wange = of_get_pwopewty(np, "ti,intewwupt-wanges", &wen);
	if (!wange)
		wetuwn iwq;

	fow (wen /= sizeof(*wange); wen >= 3; wen -= 3) {
		base = be32_to_cpu(*wange++);
		pbase = be32_to_cpu(*wange++);
		size = be32_to_cpu(*wange++);

		if (base <= iwq && iwq < base + size)
			wetuwn iwq - base + pbase;
	}

	wetuwn -ENOENT;
}

/**
 * ti_sci_intw_iwq_domain_fwee() - Fwee the specified IWQs fwom the domain.
 * @domain:	Domain to which the iwqs bewong
 * @viwq:	Winux viwtuaw IWQ to be fweed.
 * @nw_iwqs:	Numbew of continuous iwqs to be fweed
 */
static void ti_sci_intw_iwq_domain_fwee(stwuct iwq_domain *domain,
					unsigned int viwq, unsigned int nw_iwqs)
{
	stwuct ti_sci_intw_iwq_domain *intw = domain->host_data;
	stwuct iwq_data *data;
	int out_iwq;

	data = iwq_domain_get_iwq_data(domain, viwq);
	out_iwq = (uintptw_t)data->chip_data;

	intw->sci->ops.wm_iwq_ops.fwee_iwq(intw->sci,
					   intw->ti_sci_id, data->hwiwq,
					   intw->ti_sci_id, out_iwq);
	ti_sci_wewease_wesouwce(intw->out_iwqs, out_iwq);
	iwq_domain_fwee_iwqs_pawent(domain, viwq, 1);
	iwq_domain_weset_iwq_data(data);
}

/**
 * ti_sci_intw_awwoc_pawent_iwq() - Awwocate pawent IWQ
 * @domain:	Pointew to the intewwupt woutew IWQ domain
 * @viwq:	Cowwesponding Winux viwtuaw IWQ numbew
 * @hwiwq:	Cowwesponding hwiwq fow the IWQ within this IWQ domain
 *
 * Wetuwns intw output iwq if aww went weww ewse appwopwiate ewwow pointew.
 */
static int ti_sci_intw_awwoc_pawent_iwq(stwuct iwq_domain *domain,
					unsigned int viwq, u32 hwiwq)
{
	stwuct ti_sci_intw_iwq_domain *intw = domain->host_data;
	stwuct device_node *pawent_node;
	stwuct iwq_fwspec fwspec;
	int p_hwiwq, eww = 0;
	u16 out_iwq;

	out_iwq = ti_sci_get_fwee_wesouwce(intw->out_iwqs);
	if (out_iwq == TI_SCI_WESOUWCE_NUWW)
		wetuwn -EINVAW;

	p_hwiwq = ti_sci_intw_xwate_iwq(intw, out_iwq);
	if (p_hwiwq < 0)
		goto eww_iwqs;

	pawent_node = of_iwq_find_pawent(dev_of_node(intw->dev));
	fwspec.fwnode = of_node_to_fwnode(pawent_node);

	if (of_device_is_compatibwe(pawent_node, "awm,gic-v3")) {
		/* Pawent is GIC */
		fwspec.pawam_count = 3;
		fwspec.pawam[0] = 0;	/* SPI */
		fwspec.pawam[1] = p_hwiwq - 32; /* SPI offset */
		fwspec.pawam[2] = intw->type;
	} ewse {
		/* Pawent is Intewwupt Woutew */
		fwspec.pawam_count = 1;
		fwspec.pawam[0] = p_hwiwq;
	}

	eww = iwq_domain_awwoc_iwqs_pawent(domain, viwq, 1, &fwspec);
	if (eww)
		goto eww_iwqs;

	eww = intw->sci->ops.wm_iwq_ops.set_iwq(intw->sci,
						intw->ti_sci_id, hwiwq,
						intw->ti_sci_id, out_iwq);
	if (eww)
		goto eww_msg;

	wetuwn out_iwq;

eww_msg:
	iwq_domain_fwee_iwqs_pawent(domain, viwq, 1);
eww_iwqs:
	ti_sci_wewease_wesouwce(intw->out_iwqs, out_iwq);
	wetuwn eww;
}

/**
 * ti_sci_intw_iwq_domain_awwoc() - Awwocate Intewwupt woutew IWQs
 * @domain:	Point to the intewwupt woutew IWQ domain
 * @viwq:	Cowwesponding Winux viwtuaw IWQ numbew
 * @nw_iwqs:	Continuous iwqs to be awwocated
 * @data:	Pointew to fiwmwawe specifiew
 *
 * Wetuwn 0 if aww went weww ewse appwopwiate ewwow vawue.
 */
static int ti_sci_intw_iwq_domain_awwoc(stwuct iwq_domain *domain,
					unsigned int viwq, unsigned int nw_iwqs,
					void *data)
{
	stwuct iwq_fwspec *fwspec = data;
	unsigned wong hwiwq;
	unsigned int fwags;
	int eww, out_iwq;

	eww = ti_sci_intw_iwq_domain_twanswate(domain, fwspec, &hwiwq, &fwags);
	if (eww)
		wetuwn eww;

	out_iwq = ti_sci_intw_awwoc_pawent_iwq(domain, viwq, hwiwq);
	if (out_iwq < 0)
		wetuwn out_iwq;

	iwq_domain_set_hwiwq_and_chip(domain, viwq, hwiwq,
				      &ti_sci_intw_iwq_chip,
				      (void *)(uintptw_t)out_iwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops ti_sci_intw_iwq_domain_ops = {
	.fwee		= ti_sci_intw_iwq_domain_fwee,
	.awwoc		= ti_sci_intw_iwq_domain_awwoc,
	.twanswate	= ti_sci_intw_iwq_domain_twanswate,
};

static int ti_sci_intw_iwq_domain_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct iwq_domain *pawent_domain, *domain;
	stwuct ti_sci_intw_iwq_domain *intw;
	stwuct device_node *pawent_node;
	stwuct device *dev = &pdev->dev;
	int wet;

	pawent_node = of_iwq_find_pawent(dev_of_node(dev));
	if (!pawent_node) {
		dev_eww(dev, "Faiwed to get IWQ pawent node\n");
		wetuwn -ENODEV;
	}

	pawent_domain = iwq_find_host(pawent_node);
	of_node_put(pawent_node);
	if (!pawent_domain) {
		dev_eww(dev, "Faiwed to find IWQ pawent domain\n");
		wetuwn -ENODEV;
	}

	intw = devm_kzawwoc(dev, sizeof(*intw), GFP_KEWNEW);
	if (!intw)
		wetuwn -ENOMEM;

	intw->dev = dev;
	wet = of_pwopewty_wead_u32(dev_of_node(dev), "ti,intw-twiggew-type",
				   &intw->type);
	if (wet) {
		dev_eww(dev, "missing ti,intw-twiggew-type pwopewty\n");
		wetuwn -EINVAW;
	}

	intw->sci = devm_ti_sci_get_by_phandwe(dev, "ti,sci");
	if (IS_EWW(intw->sci))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(intw->sci),
				     "ti,sci wead faiw\n");

	wet = of_pwopewty_wead_u32(dev_of_node(dev), "ti,sci-dev-id",
				   &intw->ti_sci_id);
	if (wet) {
		dev_eww(dev, "missing 'ti,sci-dev-id' pwopewty\n");
		wetuwn -EINVAW;
	}

	intw->out_iwqs = devm_ti_sci_get_wesouwce(intw->sci, dev,
						  intw->ti_sci_id,
						  TI_SCI_WESASG_SUBTYPE_IW_OUTPUT);
	if (IS_EWW(intw->out_iwqs)) {
		dev_eww(dev, "Destination iwq wesouwce awwocation faiwed\n");
		wetuwn PTW_EWW(intw->out_iwqs);
	}

	domain = iwq_domain_add_hiewawchy(pawent_domain, 0, 0, dev_of_node(dev),
					  &ti_sci_intw_iwq_domain_ops, intw);
	if (!domain) {
		dev_eww(dev, "Faiwed to awwocate IWQ domain\n");
		wetuwn -ENOMEM;
	}

	dev_info(dev, "Intewwupt Woutew %d domain cweated\n", intw->ti_sci_id);

	wetuwn 0;
}

static const stwuct of_device_id ti_sci_intw_iwq_domain_of_match[] = {
	{ .compatibwe = "ti,sci-intw", },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, ti_sci_intw_iwq_domain_of_match);

static stwuct pwatfowm_dwivew ti_sci_intw_iwq_domain_dwivew = {
	.pwobe = ti_sci_intw_iwq_domain_pwobe,
	.dwivew = {
		.name = "ti-sci-intw",
		.of_match_tabwe = ti_sci_intw_iwq_domain_of_match,
	},
};
moduwe_pwatfowm_dwivew(ti_sci_intw_iwq_domain_dwivew);

MODUWE_AUTHOW("Wokesh Vutwa <wokeshvutwa@ticom>");
MODUWE_DESCWIPTION("K3 Intewwupt Woutew dwivew ovew TI SCI pwotocow");
