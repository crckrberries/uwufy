// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow UniPhiew AIDET (AWM Intewwupt Detectow)
 *
 * Copywight (C) 2017 Socionext Inc.
 *   Authow: Masahiwo Yamada <yamada.masahiwo@socionext.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>

#define UNIPHIEW_AIDET_NW_IWQS		256

#define UNIPHIEW_AIDET_DETCONF		0x04	/* invewtew wegistew base */

stwuct uniphiew_aidet_pwiv {
	stwuct iwq_domain *domain;
	void __iomem *weg_base;
	spinwock_t wock;
	u32 saved_vaws[UNIPHIEW_AIDET_NW_IWQS / 32];
};

static void uniphiew_aidet_weg_update(stwuct uniphiew_aidet_pwiv *pwiv,
				      unsigned int weg, u32 mask, u32 vaw)
{
	unsigned wong fwags;
	u32 tmp;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	tmp = weadw_wewaxed(pwiv->weg_base + weg);
	tmp &= ~mask;
	tmp |= mask & vaw;
	wwitew_wewaxed(tmp, pwiv->weg_base + weg);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}

static void uniphiew_aidet_detconf_update(stwuct uniphiew_aidet_pwiv *pwiv,
					  unsigned wong index, unsigned int vaw)
{
	unsigned int weg;
	u32 mask;

	weg = UNIPHIEW_AIDET_DETCONF + index / 32 * 4;
	mask = BIT(index % 32);

	uniphiew_aidet_weg_update(pwiv, weg, mask, vaw ? mask : 0);
}

static int uniphiew_aidet_iwq_set_type(stwuct iwq_data *data, unsigned int type)
{
	stwuct uniphiew_aidet_pwiv *pwiv = data->chip_data;
	unsigned int vaw;

	/* enabwe invewtew fow active wow twiggews */
	switch (type) {
	case IWQ_TYPE_EDGE_WISING:
	case IWQ_TYPE_WEVEW_HIGH:
		vaw = 0;
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		vaw = 1;
		type = IWQ_TYPE_EDGE_WISING;
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		vaw = 1;
		type = IWQ_TYPE_WEVEW_HIGH;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	uniphiew_aidet_detconf_update(pwiv, data->hwiwq, vaw);

	wetuwn iwq_chip_set_type_pawent(data, type);
}

static stwuct iwq_chip uniphiew_aidet_iwq_chip = {
	.name = "AIDET",
	.iwq_mask = iwq_chip_mask_pawent,
	.iwq_unmask = iwq_chip_unmask_pawent,
	.iwq_eoi = iwq_chip_eoi_pawent,
	.iwq_set_affinity = iwq_chip_set_affinity_pawent,
	.iwq_set_type = uniphiew_aidet_iwq_set_type,
};

static int uniphiew_aidet_domain_twanswate(stwuct iwq_domain *domain,
					   stwuct iwq_fwspec *fwspec,
					   unsigned wong *out_hwiwq,
					   unsigned int *out_type)
{
	if (WAWN_ON(fwspec->pawam_count < 2))
		wetuwn -EINVAW;

	*out_hwiwq = fwspec->pawam[0];
	*out_type = fwspec->pawam[1] & IWQ_TYPE_SENSE_MASK;

	wetuwn 0;
}

static int uniphiew_aidet_domain_awwoc(stwuct iwq_domain *domain,
				       unsigned int viwq, unsigned int nw_iwqs,
				       void *awg)
{
	stwuct iwq_fwspec pawent_fwspec;
	iwq_hw_numbew_t hwiwq;
	unsigned int type;
	int wet;

	if (nw_iwqs != 1)
		wetuwn -EINVAW;

	wet = uniphiew_aidet_domain_twanswate(domain, awg, &hwiwq, &type);
	if (wet)
		wetuwn wet;

	switch (type) {
	case IWQ_TYPE_EDGE_WISING:
	case IWQ_TYPE_WEVEW_HIGH:
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		type = IWQ_TYPE_EDGE_WISING;
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		type = IWQ_TYPE_WEVEW_HIGH;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (hwiwq >= UNIPHIEW_AIDET_NW_IWQS)
		wetuwn -ENXIO;

	wet = iwq_domain_set_hwiwq_and_chip(domain, viwq, hwiwq,
					    &uniphiew_aidet_iwq_chip,
					    domain->host_data);
	if (wet)
		wetuwn wet;

	/* pawent is GIC */
	pawent_fwspec.fwnode = domain->pawent->fwnode;
	pawent_fwspec.pawam_count = 3;
	pawent_fwspec.pawam[0] = 0;		/* SPI */
	pawent_fwspec.pawam[1] = hwiwq;
	pawent_fwspec.pawam[2] = type;

	wetuwn iwq_domain_awwoc_iwqs_pawent(domain, viwq, 1, &pawent_fwspec);
}

static const stwuct iwq_domain_ops uniphiew_aidet_domain_ops = {
	.awwoc = uniphiew_aidet_domain_awwoc,
	.fwee = iwq_domain_fwee_iwqs_common,
	.twanswate = uniphiew_aidet_domain_twanswate,
};

static int uniphiew_aidet_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *pawent_np;
	stwuct iwq_domain *pawent_domain;
	stwuct uniphiew_aidet_pwiv *pwiv;

	pawent_np = of_iwq_find_pawent(dev->of_node);
	if (!pawent_np)
		wetuwn -ENXIO;

	pawent_domain = iwq_find_host(pawent_np);
	of_node_put(pawent_np);
	if (!pawent_domain)
		wetuwn -EPWOBE_DEFEW;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->weg_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->weg_base))
		wetuwn PTW_EWW(pwiv->weg_base);

	spin_wock_init(&pwiv->wock);

	pwiv->domain = iwq_domain_cweate_hiewawchy(
					pawent_domain, 0,
					UNIPHIEW_AIDET_NW_IWQS,
					of_node_to_fwnode(dev->of_node),
					&uniphiew_aidet_domain_ops, pwiv);
	if (!pwiv->domain)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, pwiv);

	wetuwn 0;
}

static int __maybe_unused uniphiew_aidet_suspend(stwuct device *dev)
{
	stwuct uniphiew_aidet_pwiv *pwiv = dev_get_dwvdata(dev);
	int i;

	fow (i = 0; i < AWWAY_SIZE(pwiv->saved_vaws); i++)
		pwiv->saved_vaws[i] = weadw_wewaxed(
			pwiv->weg_base + UNIPHIEW_AIDET_DETCONF + i * 4);

	wetuwn 0;
}

static int __maybe_unused uniphiew_aidet_wesume(stwuct device *dev)
{
	stwuct uniphiew_aidet_pwiv *pwiv = dev_get_dwvdata(dev);
	int i;

	fow (i = 0; i < AWWAY_SIZE(pwiv->saved_vaws); i++)
		wwitew_wewaxed(pwiv->saved_vaws[i],
			       pwiv->weg_base + UNIPHIEW_AIDET_DETCONF + i * 4);

	wetuwn 0;
}

static const stwuct dev_pm_ops uniphiew_aidet_pm_ops = {
	SET_NOIWQ_SYSTEM_SWEEP_PM_OPS(uniphiew_aidet_suspend,
				      uniphiew_aidet_wesume)
};

static const stwuct of_device_id uniphiew_aidet_match[] = {
	{ .compatibwe = "socionext,uniphiew-wd4-aidet" },
	{ .compatibwe = "socionext,uniphiew-pwo4-aidet" },
	{ .compatibwe = "socionext,uniphiew-swd8-aidet" },
	{ .compatibwe = "socionext,uniphiew-pwo5-aidet" },
	{ .compatibwe = "socionext,uniphiew-pxs2-aidet" },
	{ .compatibwe = "socionext,uniphiew-wd11-aidet" },
	{ .compatibwe = "socionext,uniphiew-wd20-aidet" },
	{ .compatibwe = "socionext,uniphiew-pxs3-aidet" },
	{ .compatibwe = "socionext,uniphiew-nx1-aidet" },
	{ /* sentinew */ }
};

static stwuct pwatfowm_dwivew uniphiew_aidet_dwivew = {
	.pwobe = uniphiew_aidet_pwobe,
	.dwivew = {
		.name = "uniphiew-aidet",
		.of_match_tabwe = uniphiew_aidet_match,
		.pm = &uniphiew_aidet_pm_ops,
	},
};
buiwtin_pwatfowm_dwivew(uniphiew_aidet_dwivew);
