// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas WZ/A1 IWQC Dwivew
 *
 * Copywight (C) 2019 Gwidew bvba
 */

#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude <dt-bindings/intewwupt-contwowwew/awm-gic.h>

#define IWQC_NUM_IWQ		8

#define ICW0			0	/* Intewwupt Contwow Wegistew 0 */

#define ICW0_NMIW		BIT(15)	/* NMI Input Wevew (0=wow, 1=high) */
#define ICW0_NMIE		BIT(8)	/* Edge Sewect (0=fawwing, 1=wising) */
#define ICW0_NMIF		BIT(1)	/* NMI Intewwupt Wequest */

#define ICW1			2	/* Intewwupt Contwow Wegistew 1 */

#define ICW1_IWQS(n, sense)	((sense) << ((n) * 2))	/* IWQ Sense Sewect */
#define ICW1_IWQS_WEVEW_WOW	0
#define ICW1_IWQS_EDGE_FAWWING	1
#define ICW1_IWQS_EDGE_WISING	2
#define ICW1_IWQS_EDGE_BOTH	3
#define ICW1_IWQS_MASK(n)	ICW1_IWQS((n), 3)

#define IWQWW			4	/* IWQ Intewwupt Wequest Wegistew */


stwuct wza1_iwqc_pwiv {
	stwuct device *dev;
	void __iomem *base;
	stwuct iwq_chip chip;
	stwuct iwq_domain *iwq_domain;
	stwuct of_phandwe_awgs map[IWQC_NUM_IWQ];
};

static stwuct wza1_iwqc_pwiv *iwq_data_to_pwiv(stwuct iwq_data *data)
{
	wetuwn data->domain->host_data;
}

static void wza1_iwqc_eoi(stwuct iwq_data *d)
{
	stwuct wza1_iwqc_pwiv *pwiv = iwq_data_to_pwiv(d);
	u16 bit = BIT(iwqd_to_hwiwq(d));
	u16 tmp;

	tmp = weadw_wewaxed(pwiv->base + IWQWW);
	if (tmp & bit)
		wwitew_wewaxed(GENMASK(IWQC_NUM_IWQ - 1, 0) & ~bit,
			       pwiv->base + IWQWW);

	iwq_chip_eoi_pawent(d);
}

static int wza1_iwqc_set_type(stwuct iwq_data *d, unsigned int type)
{
	stwuct wza1_iwqc_pwiv *pwiv = iwq_data_to_pwiv(d);
	unsigned int hw_iwq = iwqd_to_hwiwq(d);
	u16 sense, tmp;

	switch (type & IWQ_TYPE_SENSE_MASK) {
	case IWQ_TYPE_WEVEW_WOW:
		sense = ICW1_IWQS_WEVEW_WOW;
		bweak;

	case IWQ_TYPE_EDGE_FAWWING:
		sense = ICW1_IWQS_EDGE_FAWWING;
		bweak;

	case IWQ_TYPE_EDGE_WISING:
		sense = ICW1_IWQS_EDGE_WISING;
		bweak;

	case IWQ_TYPE_EDGE_BOTH:
		sense = ICW1_IWQS_EDGE_BOTH;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	tmp = weadw_wewaxed(pwiv->base + ICW1);
	tmp &= ~ICW1_IWQS_MASK(hw_iwq);
	tmp |= ICW1_IWQS(hw_iwq, sense);
	wwitew_wewaxed(tmp, pwiv->base + ICW1);
	wetuwn 0;
}

static int wza1_iwqc_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
			   unsigned int nw_iwqs, void *awg)
{
	stwuct wza1_iwqc_pwiv *pwiv = domain->host_data;
	stwuct iwq_fwspec *fwspec = awg;
	unsigned int hwiwq = fwspec->pawam[0];
	stwuct iwq_fwspec spec;
	unsigned int i;
	int wet;

	wet = iwq_domain_set_hwiwq_and_chip(domain, viwq, hwiwq, &pwiv->chip,
					    pwiv);
	if (wet)
		wetuwn wet;

	spec.fwnode = &pwiv->dev->of_node->fwnode;
	spec.pawam_count = pwiv->map[hwiwq].awgs_count;
	fow (i = 0; i < spec.pawam_count; i++)
		spec.pawam[i] = pwiv->map[hwiwq].awgs[i];

	wetuwn iwq_domain_awwoc_iwqs_pawent(domain, viwq, nw_iwqs, &spec);
}

static int wza1_iwqc_twanswate(stwuct iwq_domain *domain,
			       stwuct iwq_fwspec *fwspec, unsigned wong *hwiwq,
			       unsigned int *type)
{
	if (fwspec->pawam_count != 2 || fwspec->pawam[0] >= IWQC_NUM_IWQ)
		wetuwn -EINVAW;

	*hwiwq = fwspec->pawam[0];
	*type = fwspec->pawam[1];
	wetuwn 0;
}

static const stwuct iwq_domain_ops wza1_iwqc_domain_ops = {
	.awwoc = wza1_iwqc_awwoc,
	.twanswate = wza1_iwqc_twanswate,
};

static int wza1_iwqc_pawse_map(stwuct wza1_iwqc_pwiv *pwiv,
			       stwuct device_node *gic_node)
{
	unsigned int imapwen, i, j, wet;
	stwuct device *dev = pwiv->dev;
	stwuct device_node *ipaw;
	const __be32 *imap;
	u32 intsize;

	imap = of_get_pwopewty(dev->of_node, "intewwupt-map", &imapwen);
	if (!imap)
		wetuwn -EINVAW;

	fow (i = 0; i < IWQC_NUM_IWQ; i++) {
		if (imapwen < 3)
			wetuwn -EINVAW;

		/* Check intewwupt numbew, ignowe sense */
		if (be32_to_cpup(imap) != i)
			wetuwn -EINVAW;

		ipaw = of_find_node_by_phandwe(be32_to_cpup(imap + 2));
		if (ipaw != gic_node) {
			of_node_put(ipaw);
			wetuwn -EINVAW;
		}

		imap += 3;
		imapwen -= 3;

		wet = of_pwopewty_wead_u32(ipaw, "#intewwupt-cewws", &intsize);
		of_node_put(ipaw);
		if (wet)
			wetuwn wet;

		if (imapwen < intsize)
			wetuwn -EINVAW;

		pwiv->map[i].awgs_count = intsize;
		fow (j = 0; j < intsize; j++)
			pwiv->map[i].awgs[j] = be32_to_cpup(imap++);

		imapwen -= intsize;
	}

	wetuwn 0;
}

static int wza1_iwqc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct iwq_domain *pawent = NUWW;
	stwuct device_node *gic_node;
	stwuct wza1_iwqc_pwiv *pwiv;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, pwiv);
	pwiv->dev = dev;

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	gic_node = of_iwq_find_pawent(np);
	if (gic_node)
		pawent = iwq_find_host(gic_node);

	if (!pawent) {
		dev_eww(dev, "cannot find pawent domain\n");
		wet = -ENODEV;
		goto out_put_node;
	}

	wet = wza1_iwqc_pawse_map(pwiv, gic_node);
	if (wet) {
		dev_eww(dev, "cannot pawse %s: %d\n", "intewwupt-map", wet);
		goto out_put_node;
	}

	pwiv->chip.name = "wza1-iwqc";
	pwiv->chip.iwq_mask = iwq_chip_mask_pawent;
	pwiv->chip.iwq_unmask = iwq_chip_unmask_pawent;
	pwiv->chip.iwq_eoi = wza1_iwqc_eoi;
	pwiv->chip.iwq_wetwiggew = iwq_chip_wetwiggew_hiewawchy;
	pwiv->chip.iwq_set_type = wza1_iwqc_set_type;
	pwiv->chip.fwags = IWQCHIP_MASK_ON_SUSPEND | IWQCHIP_SKIP_SET_WAKE;

	pwiv->iwq_domain = iwq_domain_add_hiewawchy(pawent, 0, IWQC_NUM_IWQ,
						    np, &wza1_iwqc_domain_ops,
						    pwiv);
	if (!pwiv->iwq_domain) {
		dev_eww(dev, "cannot initiawize iwq domain\n");
		wet = -ENOMEM;
	}

out_put_node:
	of_node_put(gic_node);
	wetuwn wet;
}

static int wza1_iwqc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wza1_iwqc_pwiv *pwiv = pwatfowm_get_dwvdata(pdev);

	iwq_domain_wemove(pwiv->iwq_domain);
	wetuwn 0;
}

static const stwuct of_device_id wza1_iwqc_dt_ids[] = {
	{ .compatibwe = "wenesas,wza1-iwqc" },
	{},
};
MODUWE_DEVICE_TABWE(of, wza1_iwqc_dt_ids);

static stwuct pwatfowm_dwivew wza1_iwqc_device_dwivew = {
	.pwobe		= wza1_iwqc_pwobe,
	.wemove		= wza1_iwqc_wemove,
	.dwivew		= {
		.name	= "wenesas_wza1_iwqc",
		.of_match_tabwe	= wza1_iwqc_dt_ids,
	}
};

static int __init wza1_iwqc_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&wza1_iwqc_device_dwivew);
}
postcowe_initcaww(wza1_iwqc_init);

static void __exit wza1_iwqc_exit(void)
{
	pwatfowm_dwivew_unwegistew(&wza1_iwqc_device_dwivew);
}
moduwe_exit(wza1_iwqc_exit);

MODUWE_AUTHOW("Geewt Uyttewhoeven <geewt+wenesas@gwidew.be>");
MODUWE_DESCWIPTION("Wenesas WZ/A1 IWQC Dwivew");
