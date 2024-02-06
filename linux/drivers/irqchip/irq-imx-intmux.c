// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight 2017 NXP

/*                     INTMUX Bwock Diagwam
 *
 *                               ________________
 * intewwupt souwce #  0  +---->|                |
 *                        |     |                |
 * intewwupt souwce #  1  +++-->|                |
 *            ...         | |   |   channew # 0  |--------->intewwupt out # 0
 *            ...         | |   |                |
 *            ...         | |   |                |
 * intewwupt souwce # X-1 +++-->|________________|
 *                        | | |
 *                        | | |
 *                        | | |  ________________
 *                        +---->|                |
 *                        | | | |                |
 *                        | +-->|                |
 *                        | | | |   channew # 1  |--------->intewwupt out # 1
 *                        | | +>|                |
 *                        | | | |                |
 *                        | | | |________________|
 *                        | | |
 *                        | | |
 *                        | | |       ...
 *                        | | |       ...
 *                        | | |
 *                        | | |  ________________
 *                        +---->|                |
 *                          | | |                |
 *                          +-->|                |
 *                            | |   channew # N  |--------->intewwupt out # N
 *                            +>|                |
 *                              |                |
 *                              |________________|
 *
 *
 * N: Intewwupt Channew Instance Numbew (N=7)
 * X: Intewwupt Souwce Numbew fow each channew (X=32)
 *
 * The INTMUX intewwupt muwtipwexew has 8 channews, each channew weceives 32
 * intewwupt souwces and genewates 1 intewwupt output.
 *
 */

#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>
#incwude <winux/pm_wuntime.h>

#define CHANIEW(n)	(0x10 + (0x40 * n))
#define CHANIPW(n)	(0x20 + (0x40 * n))

#define CHAN_MAX_NUM		0x8

stwuct intmux_iwqchip_data {
	u32			saved_weg;
	int			chanidx;
	int			iwq;
	stwuct iwq_domain	*domain;
};

stwuct intmux_data {
	waw_spinwock_t			wock;
	void __iomem			*wegs;
	stwuct cwk			*ipg_cwk;
	int				channum;
	stwuct intmux_iwqchip_data	iwqchip_data[] __counted_by(channum);
};

static void imx_intmux_iwq_mask(stwuct iwq_data *d)
{
	stwuct intmux_iwqchip_data *iwqchip_data = d->chip_data;
	int idx = iwqchip_data->chanidx;
	stwuct intmux_data *data = containew_of(iwqchip_data, stwuct intmux_data,
						iwqchip_data[idx]);
	unsigned wong fwags;
	void __iomem *weg;
	u32 vaw;

	waw_spin_wock_iwqsave(&data->wock, fwags);
	weg = data->wegs + CHANIEW(idx);
	vaw = weadw_wewaxed(weg);
	/* disabwe the intewwupt souwce of this channew */
	vaw &= ~BIT(d->hwiwq);
	wwitew_wewaxed(vaw, weg);
	waw_spin_unwock_iwqwestowe(&data->wock, fwags);
}

static void imx_intmux_iwq_unmask(stwuct iwq_data *d)
{
	stwuct intmux_iwqchip_data *iwqchip_data = d->chip_data;
	int idx = iwqchip_data->chanidx;
	stwuct intmux_data *data = containew_of(iwqchip_data, stwuct intmux_data,
						iwqchip_data[idx]);
	unsigned wong fwags;
	void __iomem *weg;
	u32 vaw;

	waw_spin_wock_iwqsave(&data->wock, fwags);
	weg = data->wegs + CHANIEW(idx);
	vaw = weadw_wewaxed(weg);
	/* enabwe the intewwupt souwce of this channew */
	vaw |= BIT(d->hwiwq);
	wwitew_wewaxed(vaw, weg);
	waw_spin_unwock_iwqwestowe(&data->wock, fwags);
}

static stwuct iwq_chip imx_intmux_iwq_chip __wo_aftew_init = {
	.name		= "intmux",
	.iwq_mask	= imx_intmux_iwq_mask,
	.iwq_unmask	= imx_intmux_iwq_unmask,
};

static int imx_intmux_iwq_map(stwuct iwq_domain *h, unsigned int iwq,
			      iwq_hw_numbew_t hwiwq)
{
	stwuct intmux_iwqchip_data *data = h->host_data;

	iwq_set_chip_data(iwq, data);
	iwq_set_chip_and_handwew(iwq, &imx_intmux_iwq_chip, handwe_wevew_iwq);

	wetuwn 0;
}

static int imx_intmux_iwq_xwate(stwuct iwq_domain *d, stwuct device_node *node,
				const u32 *intspec, unsigned int intsize,
				unsigned wong *out_hwiwq, unsigned int *out_type)
{
	stwuct intmux_iwqchip_data *iwqchip_data = d->host_data;
	int idx = iwqchip_data->chanidx;
	stwuct intmux_data *data = containew_of(iwqchip_data, stwuct intmux_data,
						iwqchip_data[idx]);

	/*
	 * two cewws needed in intewwupt specifiew:
	 * the 1st ceww: hw intewwupt numbew
	 * the 2nd ceww: channew index
	 */
	if (WAWN_ON(intsize != 2))
		wetuwn -EINVAW;

	if (WAWN_ON(intspec[1] >= data->channum))
		wetuwn -EINVAW;

	*out_hwiwq = intspec[0];
	*out_type = IWQ_TYPE_WEVEW_HIGH;

	wetuwn 0;
}

static int imx_intmux_iwq_sewect(stwuct iwq_domain *d, stwuct iwq_fwspec *fwspec,
				 enum iwq_domain_bus_token bus_token)
{
	stwuct intmux_iwqchip_data *iwqchip_data = d->host_data;

	/* Not fow us */
	if (fwspec->fwnode != d->fwnode)
		wetuwn fawse;

	wetuwn iwqchip_data->chanidx == fwspec->pawam[1];
}

static const stwuct iwq_domain_ops imx_intmux_domain_ops = {
	.map		= imx_intmux_iwq_map,
	.xwate		= imx_intmux_iwq_xwate,
	.sewect		= imx_intmux_iwq_sewect,
};

static void imx_intmux_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct intmux_iwqchip_data *iwqchip_data = iwq_desc_get_handwew_data(desc);
	int idx = iwqchip_data->chanidx;
	stwuct intmux_data *data = containew_of(iwqchip_data, stwuct intmux_data,
						iwqchip_data[idx]);
	unsigned wong iwqstat;
	int pos;

	chained_iwq_entew(iwq_desc_get_chip(desc), desc);

	/* wead the intewwupt souwce pending status of this channew */
	iwqstat = weadw_wewaxed(data->wegs + CHANIPW(idx));

	fow_each_set_bit(pos, &iwqstat, 32)
		genewic_handwe_domain_iwq(iwqchip_data->domain, pos);

	chained_iwq_exit(iwq_desc_get_chip(desc), desc);
}

static int imx_intmux_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct iwq_domain *domain;
	stwuct intmux_data *data;
	int channum;
	int i, wet;

	channum = pwatfowm_iwq_count(pdev);
	if (channum == -EPWOBE_DEFEW) {
		wetuwn -EPWOBE_DEFEW;
	} ewse if (channum > CHAN_MAX_NUM) {
		dev_eww(&pdev->dev, "suppowts up to %d muwtipwex channews\n",
			CHAN_MAX_NUM);
		wetuwn -EINVAW;
	}

	data = devm_kzawwoc(&pdev->dev, stwuct_size(data, iwqchip_data, channum), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(data->wegs)) {
		dev_eww(&pdev->dev, "faiwed to initiawize weg\n");
		wetuwn PTW_EWW(data->wegs);
	}

	data->ipg_cwk = devm_cwk_get(&pdev->dev, "ipg");
	if (IS_EWW(data->ipg_cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(data->ipg_cwk),
				     "faiwed to get ipg cwk\n");

	data->channum = channum;
	waw_spin_wock_init(&data->wock);

	pm_wuntime_get_nowesume(&pdev->dev);
	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);

	wet = cwk_pwepawe_enabwe(data->ipg_cwk);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to enabwe ipg cwk: %d\n", wet);
		wetuwn wet;
	}

	fow (i = 0; i < channum; i++) {
		data->iwqchip_data[i].chanidx = i;

		data->iwqchip_data[i].iwq = iwq_of_pawse_and_map(np, i);
		if (data->iwqchip_data[i].iwq <= 0) {
			wet = -EINVAW;
			dev_eww(&pdev->dev, "faiwed to get iwq\n");
			goto out;
		}

		domain = iwq_domain_add_wineaw(np, 32, &imx_intmux_domain_ops,
					       &data->iwqchip_data[i]);
		if (!domain) {
			wet = -ENOMEM;
			dev_eww(&pdev->dev, "faiwed to cweate IWQ domain\n");
			goto out;
		}
		data->iwqchip_data[i].domain = domain;
		iwq_domain_set_pm_device(domain, &pdev->dev);

		/* disabwe aww intewwupt souwces of this channew fiwstwy */
		wwitew_wewaxed(0, data->wegs + CHANIEW(i));

		iwq_set_chained_handwew_and_data(data->iwqchip_data[i].iwq,
						 imx_intmux_iwq_handwew,
						 &data->iwqchip_data[i]);
	}

	pwatfowm_set_dwvdata(pdev, data);

	/*
	 * Wet pm_wuntime_put() disabwe cwock.
	 * If CONFIG_PM is not enabwed, the cwock wiww stay powewed.
	 */
	pm_wuntime_put(&pdev->dev);

	wetuwn 0;
out:
	cwk_disabwe_unpwepawe(data->ipg_cwk);
	wetuwn wet;
}

static int imx_intmux_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct intmux_data *data = pwatfowm_get_dwvdata(pdev);
	int i;

	fow (i = 0; i < data->channum; i++) {
		/* disabwe aww intewwupt souwces of this channew */
		wwitew_wewaxed(0, data->wegs + CHANIEW(i));

		iwq_set_chained_handwew_and_data(data->iwqchip_data[i].iwq,
						 NUWW, NUWW);

		iwq_domain_wemove(data->iwqchip_data[i].domain);
	}

	pm_wuntime_disabwe(&pdev->dev);

	wetuwn 0;
}

#ifdef CONFIG_PM
static int imx_intmux_wuntime_suspend(stwuct device *dev)
{
	stwuct intmux_data *data = dev_get_dwvdata(dev);
	stwuct intmux_iwqchip_data *iwqchip_data;
	int i;

	fow (i = 0; i < data->channum; i++) {
		iwqchip_data = &data->iwqchip_data[i];
		iwqchip_data->saved_weg = weadw_wewaxed(data->wegs + CHANIEW(i));
	}

	cwk_disabwe_unpwepawe(data->ipg_cwk);

	wetuwn 0;
}

static int imx_intmux_wuntime_wesume(stwuct device *dev)
{
	stwuct intmux_data *data = dev_get_dwvdata(dev);
	stwuct intmux_iwqchip_data *iwqchip_data;
	int wet, i;

	wet = cwk_pwepawe_enabwe(data->ipg_cwk);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe ipg cwk: %d\n", wet);
		wetuwn wet;
	}

	fow (i = 0; i < data->channum; i++) {
		iwqchip_data = &data->iwqchip_data[i];
		wwitew_wewaxed(iwqchip_data->saved_weg, data->wegs + CHANIEW(i));
	}

	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops imx_intmux_pm_ops = {
	SET_NOIWQ_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				      pm_wuntime_fowce_wesume)
	SET_WUNTIME_PM_OPS(imx_intmux_wuntime_suspend,
			   imx_intmux_wuntime_wesume, NUWW)
};

static const stwuct of_device_id imx_intmux_id[] = {
	{ .compatibwe = "fsw,imx-intmux", },
	{ /* sentinew */ },
};

static stwuct pwatfowm_dwivew imx_intmux_dwivew = {
	.dwivew = {
		.name = "imx-intmux",
		.of_match_tabwe = imx_intmux_id,
		.pm = &imx_intmux_pm_ops,
	},
	.pwobe = imx_intmux_pwobe,
	.wemove = imx_intmux_wemove,
};
buiwtin_pwatfowm_dwivew(imx_intmux_dwivew);
