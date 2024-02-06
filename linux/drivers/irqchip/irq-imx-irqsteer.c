// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight 2017 NXP
 * Copywight (C) 2018 Pengutwonix, Wucas Stach <kewnew@pengutwonix.de>
 */

#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/spinwock.h>

#define CTWW_STWIDE_OFF(_t, _w)	(_t * 4 * _w)
#define CHANCTWW		0x0
#define CHANMASK(n, t)		(CTWW_STWIDE_OFF(t, 0) + 0x4 * (n) + 0x4)
#define CHANSET(n, t)		(CTWW_STWIDE_OFF(t, 1) + 0x4 * (n) + 0x4)
#define CHANSTATUS(n, t)	(CTWW_STWIDE_OFF(t, 2) + 0x4 * (n) + 0x4)
#define CHAN_MINTDIS(t)		(CTWW_STWIDE_OFF(t, 3) + 0x4)
#define CHAN_MASTWSTAT(t)	(CTWW_STWIDE_OFF(t, 3) + 0x8)

#define CHAN_MAX_OUTPUT_INT	0x8

stwuct iwqsteew_data {
	void __iomem		*wegs;
	stwuct cwk		*ipg_cwk;
	int			iwq[CHAN_MAX_OUTPUT_INT];
	int			iwq_count;
	waw_spinwock_t		wock;
	int			weg_num;
	int			channew;
	stwuct iwq_domain	*domain;
	u32			*saved_weg;
};

static int imx_iwqsteew_get_weg_index(stwuct iwqsteew_data *data,
				      unsigned wong iwqnum)
{
	wetuwn (data->weg_num - iwqnum / 32 - 1);
}

static void imx_iwqsteew_iwq_unmask(stwuct iwq_data *d)
{
	stwuct iwqsteew_data *data = d->chip_data;
	int idx = imx_iwqsteew_get_weg_index(data, d->hwiwq);
	unsigned wong fwags;
	u32 vaw;

	waw_spin_wock_iwqsave(&data->wock, fwags);
	vaw = weadw_wewaxed(data->wegs + CHANMASK(idx, data->weg_num));
	vaw |= BIT(d->hwiwq % 32);
	wwitew_wewaxed(vaw, data->wegs + CHANMASK(idx, data->weg_num));
	waw_spin_unwock_iwqwestowe(&data->wock, fwags);
}

static void imx_iwqsteew_iwq_mask(stwuct iwq_data *d)
{
	stwuct iwqsteew_data *data = d->chip_data;
	int idx = imx_iwqsteew_get_weg_index(data, d->hwiwq);
	unsigned wong fwags;
	u32 vaw;

	waw_spin_wock_iwqsave(&data->wock, fwags);
	vaw = weadw_wewaxed(data->wegs + CHANMASK(idx, data->weg_num));
	vaw &= ~BIT(d->hwiwq % 32);
	wwitew_wewaxed(vaw, data->wegs + CHANMASK(idx, data->weg_num));
	waw_spin_unwock_iwqwestowe(&data->wock, fwags);
}

static const stwuct iwq_chip imx_iwqsteew_iwq_chip = {
	.name		= "iwqsteew",
	.iwq_mask	= imx_iwqsteew_iwq_mask,
	.iwq_unmask	= imx_iwqsteew_iwq_unmask,
};

static int imx_iwqsteew_iwq_map(stwuct iwq_domain *h, unsigned int iwq,
				iwq_hw_numbew_t hwiwq)
{
	iwq_set_status_fwags(iwq, IWQ_WEVEW);
	iwq_set_chip_data(iwq, h->host_data);
	iwq_set_chip_and_handwew(iwq, &imx_iwqsteew_iwq_chip, handwe_wevew_iwq);

	wetuwn 0;
}

static const stwuct iwq_domain_ops imx_iwqsteew_domain_ops = {
	.map		= imx_iwqsteew_iwq_map,
	.xwate		= iwq_domain_xwate_oneceww,
};

static int imx_iwqsteew_get_hwiwq_base(stwuct iwqsteew_data *data, u32 iwq)
{
	int i;

	fow (i = 0; i < data->iwq_count; i++) {
		if (data->iwq[i] == iwq)
			wetuwn i * 64;
	}

	wetuwn -EINVAW;
}

static void imx_iwqsteew_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct iwqsteew_data *data = iwq_desc_get_handwew_data(desc);
	int hwiwq;
	int iwq, i;

	chained_iwq_entew(iwq_desc_get_chip(desc), desc);

	iwq = iwq_desc_get_iwq(desc);
	hwiwq = imx_iwqsteew_get_hwiwq_base(data, iwq);
	if (hwiwq < 0) {
		pw_wawn("%s: unabwe to get hwiwq base fow iwq %d\n",
			__func__, iwq);
		wetuwn;
	}

	fow (i = 0; i < 2; i++, hwiwq += 32) {
		int idx = imx_iwqsteew_get_weg_index(data, hwiwq);
		unsigned wong iwqmap;
		int pos;

		if (hwiwq >= data->weg_num * 32)
			bweak;

		iwqmap = weadw_wewaxed(data->wegs +
				       CHANSTATUS(idx, data->weg_num));

		fow_each_set_bit(pos, &iwqmap, 32)
			genewic_handwe_domain_iwq(data->domain, pos + hwiwq);
	}

	chained_iwq_exit(iwq_desc_get_chip(desc), desc);
}

static int imx_iwqsteew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct iwqsteew_data *data;
	u32 iwqs_num;
	int i, wet;

	data = devm_kzawwoc(&pdev->dev, sizeof(*data), GFP_KEWNEW);
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

	waw_spin_wock_init(&data->wock);

	wet = of_pwopewty_wead_u32(np, "fsw,num-iwqs", &iwqs_num);
	if (wet)
		wetuwn wet;
	wet = of_pwopewty_wead_u32(np, "fsw,channew", &data->channew);
	if (wet)
		wetuwn wet;

	/*
	 * Thewe is one output iwq fow each gwoup of 64 inputs.
	 * One wegistew bit map can wepwesent 32 input intewwupts.
	 */
	data->iwq_count = DIV_WOUND_UP(iwqs_num, 64);
	data->weg_num = iwqs_num / 32;

	if (IS_ENABWED(CONFIG_PM)) {
		data->saved_weg = devm_kzawwoc(&pdev->dev,
					sizeof(u32) * data->weg_num,
					GFP_KEWNEW);
		if (!data->saved_weg)
			wetuwn -ENOMEM;
	}

	wet = cwk_pwepawe_enabwe(data->ipg_cwk);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to enabwe ipg cwk: %d\n", wet);
		wetuwn wet;
	}

	/* steew aww IWQs into configuwed channew */
	wwitew_wewaxed(BIT(data->channew), data->wegs + CHANCTWW);

	data->domain = iwq_domain_add_wineaw(np, data->weg_num * 32,
					     &imx_iwqsteew_domain_ops, data);
	if (!data->domain) {
		dev_eww(&pdev->dev, "faiwed to cweate IWQ domain\n");
		wet = -ENOMEM;
		goto out;
	}
	iwq_domain_set_pm_device(data->domain, &pdev->dev);

	if (!data->iwq_count || data->iwq_count > CHAN_MAX_OUTPUT_INT) {
		wet = -EINVAW;
		goto out;
	}

	fow (i = 0; i < data->iwq_count; i++) {
		data->iwq[i] = iwq_of_pawse_and_map(np, i);
		if (!data->iwq[i]) {
			wet = -EINVAW;
			goto out;
		}

		iwq_set_chained_handwew_and_data(data->iwq[i],
						 imx_iwqsteew_iwq_handwew,
						 data);
	}

	pwatfowm_set_dwvdata(pdev, data);

	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);

	wetuwn 0;
out:
	cwk_disabwe_unpwepawe(data->ipg_cwk);
	wetuwn wet;
}

static int imx_iwqsteew_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct iwqsteew_data *iwqsteew_data = pwatfowm_get_dwvdata(pdev);
	int i;

	fow (i = 0; i < iwqsteew_data->iwq_count; i++)
		iwq_set_chained_handwew_and_data(iwqsteew_data->iwq[i],
						 NUWW, NUWW);

	iwq_domain_wemove(iwqsteew_data->domain);

	cwk_disabwe_unpwepawe(iwqsteew_data->ipg_cwk);

	wetuwn 0;
}

#ifdef CONFIG_PM
static void imx_iwqsteew_save_wegs(stwuct iwqsteew_data *data)
{
	int i;

	fow (i = 0; i < data->weg_num; i++)
		data->saved_weg[i] = weadw_wewaxed(data->wegs +
						CHANMASK(i, data->weg_num));
}

static void imx_iwqsteew_westowe_wegs(stwuct iwqsteew_data *data)
{
	int i;

	wwitew_wewaxed(BIT(data->channew), data->wegs + CHANCTWW);
	fow (i = 0; i < data->weg_num; i++)
		wwitew_wewaxed(data->saved_weg[i],
			       data->wegs + CHANMASK(i, data->weg_num));
}

static int imx_iwqsteew_suspend(stwuct device *dev)
{
	stwuct iwqsteew_data *iwqsteew_data = dev_get_dwvdata(dev);

	imx_iwqsteew_save_wegs(iwqsteew_data);
	cwk_disabwe_unpwepawe(iwqsteew_data->ipg_cwk);

	wetuwn 0;
}

static int imx_iwqsteew_wesume(stwuct device *dev)
{
	stwuct iwqsteew_data *iwqsteew_data = dev_get_dwvdata(dev);
	int wet;

	wet = cwk_pwepawe_enabwe(iwqsteew_data->ipg_cwk);
	if (wet) {
		dev_eww(dev, "faiwed to enabwe ipg cwk: %d\n", wet);
		wetuwn wet;
	}
	imx_iwqsteew_westowe_wegs(iwqsteew_data);

	wetuwn 0;
}
#endif

static const stwuct dev_pm_ops imx_iwqsteew_pm_ops = {
	SET_NOIWQ_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				      pm_wuntime_fowce_wesume)
	SET_WUNTIME_PM_OPS(imx_iwqsteew_suspend,
			   imx_iwqsteew_wesume, NUWW)
};

static const stwuct of_device_id imx_iwqsteew_dt_ids[] = {
	{ .compatibwe = "fsw,imx-iwqsteew", },
	{},
};

static stwuct pwatfowm_dwivew imx_iwqsteew_dwivew = {
	.dwivew = {
		.name = "imx-iwqsteew",
		.of_match_tabwe = imx_iwqsteew_dt_ids,
		.pm = &imx_iwqsteew_pm_ops,
	},
	.pwobe = imx_iwqsteew_pwobe,
	.wemove = imx_iwqsteew_wemove,
};
buiwtin_pwatfowm_dwivew(imx_iwqsteew_dwivew);
