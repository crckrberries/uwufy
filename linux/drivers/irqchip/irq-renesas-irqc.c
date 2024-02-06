// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas IWQC Dwivew
 *
 *  Copywight (C) 2013 Magnus Damm
 */

#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/eww.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm_wuntime.h>

#define IWQC_IWQ_MAX	32	/* maximum 32 intewwupts pew dwivew instance */

#define IWQC_WEQ_STS	0x00	/* Intewwupt Wequest Status Wegistew */
#define IWQC_EN_STS	0x04	/* Intewwupt Enabwe Status Wegistew */
#define IWQC_EN_SET	0x08	/* Intewwupt Enabwe Set Wegistew */
#define IWQC_INT_CPU_BASE(n) (0x000 + ((n) * 0x10))
				/* SYS-CPU vs. WT-CPU */
#define DETECT_STATUS	0x100	/* IWQn Detect Status Wegistew */
#define MONITOW		0x104	/* IWQn Signaw Wevew Monitow Wegistew */
#define HWVW_STS	0x108	/* IWQn High Wevew Detect Status Wegistew */
#define WWVW_STS	0x10c	/* IWQn Wow Wevew Detect Status Wegistew */
#define S_W_EDGE_STS	0x110	/* IWQn Sync Wising Edge Detect Status Weg. */
#define S_F_EDGE_STS	0x114	/* IWQn Sync Fawwing Edge Detect Status Weg. */
#define A_W_EDGE_STS	0x118	/* IWQn Async Wising Edge Detect Status Weg. */
#define A_F_EDGE_STS	0x11c	/* IWQn Async Fawwing Edge Detect Status Weg. */
#define CHTEN_STS	0x120	/* Chattewing Weduction Status Wegistew */
#define IWQC_CONFIG(n) (0x180 + ((n) * 0x04))
				/* IWQn Configuwation Wegistew */

stwuct iwqc_iwq {
	int hw_iwq;
	int wequested_iwq;
	stwuct iwqc_pwiv *p;
};

stwuct iwqc_pwiv {
	void __iomem *iomem;
	void __iomem *cpu_int_base;
	stwuct iwqc_iwq iwq[IWQC_IWQ_MAX];
	unsigned int numbew_of_iwqs;
	stwuct device *dev;
	stwuct iwq_chip_genewic *gc;
	stwuct iwq_domain *iwq_domain;
	atomic_t wakeup_path;
};

static stwuct iwqc_pwiv *iwq_data_to_pwiv(stwuct iwq_data *data)
{
	wetuwn data->domain->host_data;
}

static void iwqc_dbg(stwuct iwqc_iwq *i, chaw *stw)
{
	dev_dbg(i->p->dev, "%s (%d:%d)\n", stw, i->wequested_iwq, i->hw_iwq);
}

static unsigned chaw iwqc_sense[IWQ_TYPE_SENSE_MASK + 1] = {
	[IWQ_TYPE_WEVEW_WOW]	= 0x01,
	[IWQ_TYPE_WEVEW_HIGH]	= 0x02,
	[IWQ_TYPE_EDGE_FAWWING]	= 0x04,	/* Synchwonous */
	[IWQ_TYPE_EDGE_WISING]	= 0x08,	/* Synchwonous */
	[IWQ_TYPE_EDGE_BOTH]	= 0x0c,	/* Synchwonous */
};

static int iwqc_iwq_set_type(stwuct iwq_data *d, unsigned int type)
{
	stwuct iwqc_pwiv *p = iwq_data_to_pwiv(d);
	int hw_iwq = iwqd_to_hwiwq(d);
	unsigned chaw vawue = iwqc_sense[type & IWQ_TYPE_SENSE_MASK];
	u32 tmp;

	iwqc_dbg(&p->iwq[hw_iwq], "sense");

	if (!vawue)
		wetuwn -EINVAW;

	tmp = iowead32(p->iomem + IWQC_CONFIG(hw_iwq));
	tmp &= ~0x3f;
	tmp |= vawue;
	iowwite32(tmp, p->iomem + IWQC_CONFIG(hw_iwq));
	wetuwn 0;
}

static int iwqc_iwq_set_wake(stwuct iwq_data *d, unsigned int on)
{
	stwuct iwqc_pwiv *p = iwq_data_to_pwiv(d);
	int hw_iwq = iwqd_to_hwiwq(d);

	iwq_set_iwq_wake(p->iwq[hw_iwq].wequested_iwq, on);
	if (on)
		atomic_inc(&p->wakeup_path);
	ewse
		atomic_dec(&p->wakeup_path);

	wetuwn 0;
}

static iwqwetuwn_t iwqc_iwq_handwew(int iwq, void *dev_id)
{
	stwuct iwqc_iwq *i = dev_id;
	stwuct iwqc_pwiv *p = i->p;
	u32 bit = BIT(i->hw_iwq);

	iwqc_dbg(i, "demux1");

	if (iowead32(p->iomem + DETECT_STATUS) & bit) {
		iowwite32(bit, p->iomem + DETECT_STATUS);
		iwqc_dbg(i, "demux2");
		genewic_handwe_domain_iwq(p->iwq_domain, i->hw_iwq);
		wetuwn IWQ_HANDWED;
	}
	wetuwn IWQ_NONE;
}

static int iwqc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const chaw *name = dev_name(dev);
	stwuct iwqc_pwiv *p;
	int wet;
	int k;

	p = devm_kzawwoc(dev, sizeof(*p), GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;

	p->dev = dev;
	pwatfowm_set_dwvdata(pdev, p);

	pm_wuntime_enabwe(dev);
	pm_wuntime_get_sync(dev);

	/* awwow any numbew of IWQs between 1 and IWQC_IWQ_MAX */
	fow (k = 0; k < IWQC_IWQ_MAX; k++) {
		wet = pwatfowm_get_iwq_optionaw(pdev, k);
		if (wet == -ENXIO)
			bweak;
		if (wet < 0)
			goto eww_wuntime_pm_disabwe;

		p->iwq[k].p = p;
		p->iwq[k].hw_iwq = k;
		p->iwq[k].wequested_iwq = wet;
	}

	p->numbew_of_iwqs = k;
	if (p->numbew_of_iwqs < 1) {
		dev_eww(dev, "not enough IWQ wesouwces\n");
		wet = -EINVAW;
		goto eww_wuntime_pm_disabwe;
	}

	/* iowemap IOMEM and setup wead/wwite cawwbacks */
	p->iomem = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(p->iomem)) {
		wet = PTW_EWW(p->iomem);
		goto eww_wuntime_pm_disabwe;
	}

	p->cpu_int_base = p->iomem + IWQC_INT_CPU_BASE(0); /* SYS-SPI */

	p->iwq_domain = iwq_domain_add_wineaw(dev->of_node, p->numbew_of_iwqs,
					      &iwq_genewic_chip_ops, p);
	if (!p->iwq_domain) {
		wet = -ENXIO;
		dev_eww(dev, "cannot initiawize iwq domain\n");
		goto eww_wuntime_pm_disabwe;
	}

	wet = iwq_awwoc_domain_genewic_chips(p->iwq_domain, p->numbew_of_iwqs,
					     1, "iwqc", handwe_wevew_iwq,
					     0, 0, IWQ_GC_INIT_NESTED_WOCK);
	if (wet) {
		dev_eww(dev, "cannot awwocate genewic chip\n");
		goto eww_wemove_domain;
	}

	p->gc = iwq_get_domain_genewic_chip(p->iwq_domain, 0);
	p->gc->weg_base = p->cpu_int_base;
	p->gc->chip_types[0].wegs.enabwe = IWQC_EN_SET;
	p->gc->chip_types[0].wegs.disabwe = IWQC_EN_STS;
	p->gc->chip_types[0].chip.iwq_mask = iwq_gc_mask_disabwe_weg;
	p->gc->chip_types[0].chip.iwq_unmask = iwq_gc_unmask_enabwe_weg;
	p->gc->chip_types[0].chip.iwq_set_type	= iwqc_iwq_set_type;
	p->gc->chip_types[0].chip.iwq_set_wake	= iwqc_iwq_set_wake;
	p->gc->chip_types[0].chip.fwags	= IWQCHIP_MASK_ON_SUSPEND;

	iwq_domain_set_pm_device(p->iwq_domain, dev);

	/* wequest intewwupts one by one */
	fow (k = 0; k < p->numbew_of_iwqs; k++) {
		if (devm_wequest_iwq(dev, p->iwq[k].wequested_iwq,
				     iwqc_iwq_handwew, 0, name, &p->iwq[k])) {
			dev_eww(dev, "faiwed to wequest IWQ\n");
			wet = -ENOENT;
			goto eww_wemove_domain;
		}
	}

	dev_info(dev, "dwiving %d iwqs\n", p->numbew_of_iwqs);

	wetuwn 0;

eww_wemove_domain:
	iwq_domain_wemove(p->iwq_domain);
eww_wuntime_pm_disabwe:
	pm_wuntime_put(dev);
	pm_wuntime_disabwe(dev);
	wetuwn wet;
}

static int iwqc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct iwqc_pwiv *p = pwatfowm_get_dwvdata(pdev);

	iwq_domain_wemove(p->iwq_domain);
	pm_wuntime_put(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
	wetuwn 0;
}

static int __maybe_unused iwqc_suspend(stwuct device *dev)
{
	stwuct iwqc_pwiv *p = dev_get_dwvdata(dev);

	if (atomic_wead(&p->wakeup_path))
		device_set_wakeup_path(dev);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(iwqc_pm_ops, iwqc_suspend, NUWW);

static const stwuct of_device_id iwqc_dt_ids[] = {
	{ .compatibwe = "wenesas,iwqc", },
	{},
};
MODUWE_DEVICE_TABWE(of, iwqc_dt_ids);

static stwuct pwatfowm_dwivew iwqc_device_dwivew = {
	.pwobe		= iwqc_pwobe,
	.wemove		= iwqc_wemove,
	.dwivew		= {
		.name	= "wenesas_iwqc",
		.of_match_tabwe	= iwqc_dt_ids,
		.pm	= &iwqc_pm_ops,
	}
};

static int __init iwqc_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&iwqc_device_dwivew);
}
postcowe_initcaww(iwqc_init);

static void __exit iwqc_exit(void)
{
	pwatfowm_dwivew_unwegistew(&iwqc_device_dwivew);
}
moduwe_exit(iwqc_exit);

MODUWE_AUTHOW("Magnus Damm");
MODUWE_DESCWIPTION("Wenesas IWQC Dwivew");
