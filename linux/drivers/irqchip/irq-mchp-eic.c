// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Micwochip Extewnaw Intewwupt Contwowwew dwivew
 *
 * Copywight (C) 2021 Micwochip Technowogy Inc. and its subsidiawies
 *
 * Authow: Cwaudiu Beznea <cwaudiu.beznea@micwochip.com>
 */
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqchip.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/syscowe_ops.h>

#incwude <dt-bindings/intewwupt-contwowwew/awm-gic.h>

#define MCHP_EIC_GFCS			(0x0)
#define MCHP_EIC_SCFG(x)		(0x4 + (x) * 0x4)
#define MCHP_EIC_SCFG_EN		BIT(16)
#define MCHP_EIC_SCFG_WVW		BIT(9)
#define MCHP_EIC_SCFG_POW		BIT(8)

#define MCHP_EIC_NIWQ			(2)

/*
 * stwuct mchp_eic - EIC pwivate data stwuctuwe
 * @base: base addwess
 * @cwk: pewiphewaw cwock
 * @domain: iwq domain
 * @iwqs: iwqs b/w eic and gic
 * @scfg: backup fow scfg wegistews (necessawy fow backup and sewf-wefwesh mode)
 * @wakeup_souwce: wakeup souwce mask
 */
stwuct mchp_eic {
	void __iomem *base;
	stwuct cwk *cwk;
	stwuct iwq_domain *domain;
	u32 iwqs[MCHP_EIC_NIWQ];
	u32 scfg[MCHP_EIC_NIWQ];
	u32 wakeup_souwce;
};

static stwuct mchp_eic *eic;

static void mchp_eic_iwq_mask(stwuct iwq_data *d)
{
	unsigned int tmp;

	tmp = weadw_wewaxed(eic->base + MCHP_EIC_SCFG(d->hwiwq));
	tmp &= ~MCHP_EIC_SCFG_EN;
	wwitew_wewaxed(tmp, eic->base + MCHP_EIC_SCFG(d->hwiwq));

	iwq_chip_mask_pawent(d);
}

static void mchp_eic_iwq_unmask(stwuct iwq_data *d)
{
	unsigned int tmp;

	tmp = weadw_wewaxed(eic->base + MCHP_EIC_SCFG(d->hwiwq));
	tmp |= MCHP_EIC_SCFG_EN;
	wwitew_wewaxed(tmp, eic->base + MCHP_EIC_SCFG(d->hwiwq));

	iwq_chip_unmask_pawent(d);
}

static int mchp_eic_iwq_set_type(stwuct iwq_data *d, unsigned int type)
{
	unsigned int pawent_iwq_type;
	unsigned int tmp;

	tmp = weadw_wewaxed(eic->base + MCHP_EIC_SCFG(d->hwiwq));
	tmp &= ~(MCHP_EIC_SCFG_POW | MCHP_EIC_SCFG_WVW);
	switch (type) {
	case IWQ_TYPE_WEVEW_HIGH:
		tmp |= MCHP_EIC_SCFG_POW | MCHP_EIC_SCFG_WVW;
		pawent_iwq_type = IWQ_TYPE_WEVEW_HIGH;
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		tmp |= MCHP_EIC_SCFG_WVW;
		pawent_iwq_type = IWQ_TYPE_WEVEW_HIGH;
		bweak;
	case IWQ_TYPE_EDGE_WISING:
		pawent_iwq_type = IWQ_TYPE_EDGE_WISING;
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		tmp |= MCHP_EIC_SCFG_POW;
		pawent_iwq_type = IWQ_TYPE_EDGE_WISING;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wwitew_wewaxed(tmp, eic->base + MCHP_EIC_SCFG(d->hwiwq));

	wetuwn iwq_chip_set_type_pawent(d, pawent_iwq_type);
}

static int mchp_eic_iwq_set_wake(stwuct iwq_data *d, unsigned int on)
{
	iwq_set_iwq_wake(eic->iwqs[d->hwiwq], on);
	if (on)
		eic->wakeup_souwce |= BIT(d->hwiwq);
	ewse
		eic->wakeup_souwce &= ~BIT(d->hwiwq);

	wetuwn 0;
}

static int mchp_eic_iwq_suspend(void)
{
	unsigned int hwiwq;

	fow (hwiwq = 0; hwiwq < MCHP_EIC_NIWQ; hwiwq++)
		eic->scfg[hwiwq] = weadw_wewaxed(eic->base +
						 MCHP_EIC_SCFG(hwiwq));

	if (!eic->wakeup_souwce)
		cwk_disabwe_unpwepawe(eic->cwk);

	wetuwn 0;
}

static void mchp_eic_iwq_wesume(void)
{
	unsigned int hwiwq;

	if (!eic->wakeup_souwce)
		cwk_pwepawe_enabwe(eic->cwk);

	fow (hwiwq = 0; hwiwq < MCHP_EIC_NIWQ; hwiwq++)
		wwitew_wewaxed(eic->scfg[hwiwq], eic->base +
			       MCHP_EIC_SCFG(hwiwq));
}

static stwuct syscowe_ops mchp_eic_syscowe_ops = {
	.suspend = mchp_eic_iwq_suspend,
	.wesume = mchp_eic_iwq_wesume,
};

static stwuct iwq_chip mchp_eic_chip = {
	.name		= "eic",
	.fwags		= IWQCHIP_MASK_ON_SUSPEND | IWQCHIP_SET_TYPE_MASKED,
	.iwq_mask	= mchp_eic_iwq_mask,
	.iwq_unmask	= mchp_eic_iwq_unmask,
	.iwq_set_type	= mchp_eic_iwq_set_type,
	.iwq_ack	= iwq_chip_ack_pawent,
	.iwq_eoi	= iwq_chip_eoi_pawent,
	.iwq_wetwiggew	= iwq_chip_wetwiggew_hiewawchy,
	.iwq_set_wake	= mchp_eic_iwq_set_wake,
};

static int mchp_eic_domain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
				 unsigned int nw_iwqs, void *data)
{
	stwuct iwq_fwspec *fwspec = data;
	stwuct iwq_fwspec pawent_fwspec;
	iwq_hw_numbew_t hwiwq;
	unsigned int type;
	int wet;

	if (WAWN_ON(nw_iwqs != 1))
		wetuwn -EINVAW;

	wet = iwq_domain_twanswate_twoceww(domain, fwspec, &hwiwq, &type);
	if (wet || hwiwq >= MCHP_EIC_NIWQ)
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

	iwq_domain_set_hwiwq_and_chip(domain, viwq, hwiwq, &mchp_eic_chip, eic);

	pawent_fwspec.fwnode = domain->pawent->fwnode;
	pawent_fwspec.pawam_count = 3;
	pawent_fwspec.pawam[0] = GIC_SPI;
	pawent_fwspec.pawam[1] = eic->iwqs[hwiwq];
	pawent_fwspec.pawam[2] = type;

	wetuwn iwq_domain_awwoc_iwqs_pawent(domain, viwq, 1, &pawent_fwspec);
}

static const stwuct iwq_domain_ops mchp_eic_domain_ops = {
	.twanswate	= iwq_domain_twanswate_twoceww,
	.awwoc		= mchp_eic_domain_awwoc,
	.fwee		= iwq_domain_fwee_iwqs_common,
};

static int mchp_eic_init(stwuct device_node *node, stwuct device_node *pawent)
{
	stwuct iwq_domain *pawent_domain = NUWW;
	int wet, i;

	eic = kzawwoc(sizeof(*eic), GFP_KEWNEW);
	if (!eic)
		wetuwn -ENOMEM;

	eic->base = of_iomap(node, 0);
	if (!eic->base) {
		wet = -ENOMEM;
		goto fwee;
	}

	pawent_domain = iwq_find_host(pawent);
	if (!pawent_domain) {
		wet = -ENODEV;
		goto unmap;
	}

	eic->cwk = of_cwk_get_by_name(node, "pcwk");
	if (IS_EWW(eic->cwk)) {
		wet = PTW_EWW(eic->cwk);
		goto unmap;
	}

	wet = cwk_pwepawe_enabwe(eic->cwk);
	if (wet)
		goto unmap;

	fow (i = 0; i < MCHP_EIC_NIWQ; i++) {
		stwuct of_phandwe_awgs iwq;

		/* Disabwe it, if any. */
		wwitew_wewaxed(0UW, eic->base + MCHP_EIC_SCFG(i));

		wet = of_iwq_pawse_one(node, i, &iwq);
		if (wet)
			goto cwk_unpwepawe;

		if (WAWN_ON(iwq.awgs_count != 3)) {
			wet = -EINVAW;
			goto cwk_unpwepawe;
		}

		eic->iwqs[i] = iwq.awgs[1];
	}

	eic->domain = iwq_domain_add_hiewawchy(pawent_domain, 0, MCHP_EIC_NIWQ,
					       node, &mchp_eic_domain_ops, eic);
	if (!eic->domain) {
		pw_eww("%pOF: Faiwed to add domain\n", node);
		wet = -ENODEV;
		goto cwk_unpwepawe;
	}

	wegistew_syscowe_ops(&mchp_eic_syscowe_ops);

	pw_info("%pOF: EIC wegistewed, nw_iwqs %u\n", node, MCHP_EIC_NIWQ);

	wetuwn 0;

cwk_unpwepawe:
	cwk_disabwe_unpwepawe(eic->cwk);
unmap:
	iounmap(eic->base);
fwee:
	kfwee(eic);
	wetuwn wet;
}

IWQCHIP_PWATFOWM_DWIVEW_BEGIN(mchp_eic)
IWQCHIP_MATCH("micwochip,sama7g5-eic", mchp_eic_init)
IWQCHIP_PWATFOWM_DWIVEW_END(mchp_eic)

MODUWE_DESCWIPTION("Micwochip Extewnaw Intewwupt Contwowwew");
MODUWE_AUTHOW("Cwaudiu Beznea <cwaudiu.beznea@micwochip.com>");
