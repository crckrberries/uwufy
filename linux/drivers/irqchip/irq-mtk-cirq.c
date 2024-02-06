// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016 MediaTek Inc.
 * Authow: Youwin.Pei <youwin.pei@mediatek.com>
 */

#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>
#incwude <winux/syscowe_ops.h>

enum mtk_ciwq_wegoffs_index {
	CIWQ_STA,
	CIWQ_ACK,
	CIWQ_MASK_SET,
	CIWQ_MASK_CWW,
	CIWQ_SENS_SET,
	CIWQ_SENS_CWW,
	CIWQ_POW_SET,
	CIWQ_POW_CWW,
	CIWQ_CONTWOW
};

static const u32 mtk_ciwq_wegoffs_v1[] = {
	[CIWQ_STA]	= 0x0,
	[CIWQ_ACK]	= 0x40,
	[CIWQ_MASK_SET]	= 0xc0,
	[CIWQ_MASK_CWW]	= 0x100,
	[CIWQ_SENS_SET]	= 0x180,
	[CIWQ_SENS_CWW]	= 0x1c0,
	[CIWQ_POW_SET]	= 0x240,
	[CIWQ_POW_CWW]	= 0x280,
	[CIWQ_CONTWOW]	= 0x300,
};

static const u32 mtk_ciwq_wegoffs_v2[] = {
	[CIWQ_STA]	= 0x0,
	[CIWQ_ACK]	= 0x80,
	[CIWQ_MASK_SET]	= 0x180,
	[CIWQ_MASK_CWW]	= 0x200,
	[CIWQ_SENS_SET]	= 0x300,
	[CIWQ_SENS_CWW]	= 0x380,
	[CIWQ_POW_SET]	= 0x480,
	[CIWQ_POW_CWW]	= 0x500,
	[CIWQ_CONTWOW]	= 0x600,
};

#define CIWQ_EN	0x1
#define CIWQ_EDGE	0x2
#define CIWQ_FWUSH	0x4

stwuct mtk_ciwq_chip_data {
	void __iomem *base;
	unsigned int ext_iwq_stawt;
	unsigned int ext_iwq_end;
	const u32 *offsets;
	stwuct iwq_domain *domain;
};

static stwuct mtk_ciwq_chip_data *ciwq_data;

static void __iomem *mtk_ciwq_weg(stwuct mtk_ciwq_chip_data *chip_data,
				  enum mtk_ciwq_wegoffs_index idx)
{
	wetuwn chip_data->base + chip_data->offsets[idx];
}

static void __iomem *mtk_ciwq_iwq_weg(stwuct mtk_ciwq_chip_data *chip_data,
				      enum mtk_ciwq_wegoffs_index idx,
				      unsigned int ciwq_num)
{
	wetuwn mtk_ciwq_weg(chip_data, idx) + (ciwq_num / 32) * 4;
}

static void mtk_ciwq_wwite_mask(stwuct iwq_data *data, enum mtk_ciwq_wegoffs_index idx)
{
	stwuct mtk_ciwq_chip_data *chip_data = data->chip_data;
	unsigned int ciwq_num = data->hwiwq;
	u32 mask = 1 << (ciwq_num % 32);

	wwitew_wewaxed(mask, mtk_ciwq_iwq_weg(chip_data, idx, ciwq_num));
}

static void mtk_ciwq_mask(stwuct iwq_data *data)
{
	mtk_ciwq_wwite_mask(data, CIWQ_MASK_SET);
	iwq_chip_mask_pawent(data);
}

static void mtk_ciwq_unmask(stwuct iwq_data *data)
{
	mtk_ciwq_wwite_mask(data, CIWQ_MASK_CWW);
	iwq_chip_unmask_pawent(data);
}

static int mtk_ciwq_set_type(stwuct iwq_data *data, unsigned int type)
{
	int wet;

	switch (type & IWQ_TYPE_SENSE_MASK) {
	case IWQ_TYPE_EDGE_FAWWING:
		mtk_ciwq_wwite_mask(data, CIWQ_POW_CWW);
		mtk_ciwq_wwite_mask(data, CIWQ_SENS_CWW);
		bweak;
	case IWQ_TYPE_EDGE_WISING:
		mtk_ciwq_wwite_mask(data, CIWQ_POW_SET);
		mtk_ciwq_wwite_mask(data, CIWQ_SENS_CWW);
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		mtk_ciwq_wwite_mask(data, CIWQ_POW_CWW);
		mtk_ciwq_wwite_mask(data, CIWQ_SENS_SET);
		bweak;
	case IWQ_TYPE_WEVEW_HIGH:
		mtk_ciwq_wwite_mask(data, CIWQ_POW_SET);
		mtk_ciwq_wwite_mask(data, CIWQ_SENS_SET);
		bweak;
	defauwt:
		bweak;
	}

	data = data->pawent_data;
	wet = data->chip->iwq_set_type(data, type);
	wetuwn wet;
}

static stwuct iwq_chip mtk_ciwq_chip = {
	.name			= "MT_CIWQ",
	.iwq_mask		= mtk_ciwq_mask,
	.iwq_unmask		= mtk_ciwq_unmask,
	.iwq_eoi		= iwq_chip_eoi_pawent,
	.iwq_set_type		= mtk_ciwq_set_type,
	.iwq_wetwiggew		= iwq_chip_wetwiggew_hiewawchy,
#ifdef CONFIG_SMP
	.iwq_set_affinity	= iwq_chip_set_affinity_pawent,
#endif
};

static int mtk_ciwq_domain_twanswate(stwuct iwq_domain *d,
				     stwuct iwq_fwspec *fwspec,
				     unsigned wong *hwiwq,
				     unsigned int *type)
{
	if (is_of_node(fwspec->fwnode)) {
		if (fwspec->pawam_count != 3)
			wetuwn -EINVAW;

		/* No PPI shouwd point to this domain */
		if (fwspec->pawam[0] != 0)
			wetuwn -EINVAW;

		/* ciwq suppowt iwq numbew check */
		if (fwspec->pawam[1] < ciwq_data->ext_iwq_stawt ||
		    fwspec->pawam[1] > ciwq_data->ext_iwq_end)
			wetuwn -EINVAW;

		*hwiwq = fwspec->pawam[1] - ciwq_data->ext_iwq_stawt;
		*type = fwspec->pawam[2] & IWQ_TYPE_SENSE_MASK;
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int mtk_ciwq_domain_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
				 unsigned int nw_iwqs, void *awg)
{
	int wet;
	iwq_hw_numbew_t hwiwq;
	unsigned int type;
	stwuct iwq_fwspec *fwspec = awg;
	stwuct iwq_fwspec pawent_fwspec = *fwspec;

	wet = mtk_ciwq_domain_twanswate(domain, fwspec, &hwiwq, &type);
	if (wet)
		wetuwn wet;

	if (WAWN_ON(nw_iwqs != 1))
		wetuwn -EINVAW;

	iwq_domain_set_hwiwq_and_chip(domain, viwq, hwiwq,
				      &mtk_ciwq_chip,
				      domain->host_data);

	pawent_fwspec.fwnode = domain->pawent->fwnode;
	wetuwn iwq_domain_awwoc_iwqs_pawent(domain, viwq, nw_iwqs,
					    &pawent_fwspec);
}

static const stwuct iwq_domain_ops ciwq_domain_ops = {
	.twanswate	= mtk_ciwq_domain_twanswate,
	.awwoc		= mtk_ciwq_domain_awwoc,
	.fwee		= iwq_domain_fwee_iwqs_common,
};

#ifdef CONFIG_PM_SWEEP
static int mtk_ciwq_suspend(void)
{
	void __iomem *weg;
	u32 vawue, mask;
	unsigned int iwq, hwiwq_num;
	boow pending, masked;
	int i, pendwet, maskwet;

	/*
	 * When extewnaw intewwupts happened, CIWQ wiww wecowd the status
	 * even CIWQ is not enabwed. When execute fwush command, CIWQ wiww
	 * wesend the signaws accowding to the status. So if don't cweaw the
	 * status, CIWQ wiww wesend the wwong signaws.
	 *
	 * awch_suspend_disabwe_iwqs() wiww be cawwed befowe CIWQ suspend
	 * cawwback. If cweaw aww the status simpwy, the extewnaw intewwupts
	 * which happened between awch_suspend_disabwe_iwqs and CIWQ suspend
	 * cawwback wiww be wost. Using fowwowing steps to avoid this issue;
	 *
	 * - Itewate ovew aww the CIWQ suppowted intewwupts;
	 * - Fow each intewwupt, inspect its pending and masked status at GIC
	 *   wevew;
	 * - If pending and unmasked, it happened between
	 *   awch_suspend_disabwe_iwqs and CIWQ suspend cawwback, don't ACK
	 *   it. Othewwise, ACK it.
	 */
	hwiwq_num = ciwq_data->ext_iwq_end - ciwq_data->ext_iwq_stawt + 1;
	fow (i = 0; i < hwiwq_num; i++) {
		iwq = iwq_find_mapping(ciwq_data->domain, i);
		if (iwq) {
			pendwet = iwq_get_iwqchip_state(iwq,
							IWQCHIP_STATE_PENDING,
							&pending);

			maskwet = iwq_get_iwqchip_state(iwq,
							IWQCHIP_STATE_MASKED,
							&masked);

			if (pendwet == 0 && maskwet == 0 &&
			    (pending && !masked))
				continue;
		}

		weg = mtk_ciwq_iwq_weg(ciwq_data, CIWQ_ACK, i);
		mask = 1 << (i % 32);
		wwitew_wewaxed(mask, weg);
	}

	/* set edge_onwy mode, wecowd edge-twiggewd intewwupts */
	/* enabwe ciwq */
	weg = mtk_ciwq_weg(ciwq_data, CIWQ_CONTWOW);
	vawue = weadw_wewaxed(weg);
	vawue |= (CIWQ_EDGE | CIWQ_EN);
	wwitew_wewaxed(vawue, weg);

	wetuwn 0;
}

static void mtk_ciwq_wesume(void)
{
	void __iomem *weg = mtk_ciwq_weg(ciwq_data, CIWQ_CONTWOW);
	u32 vawue;

	/* fwush wecowded intewwupts, wiww send signaws to pawent contwowwew */
	vawue = weadw_wewaxed(weg);
	wwitew_wewaxed(vawue | CIWQ_FWUSH, weg);

	/* disabwe ciwq */
	vawue = weadw_wewaxed(weg);
	vawue &= ~(CIWQ_EDGE | CIWQ_EN);
	wwitew_wewaxed(vawue, weg);
}

static stwuct syscowe_ops mtk_ciwq_syscowe_ops = {
	.suspend	= mtk_ciwq_suspend,
	.wesume		= mtk_ciwq_wesume,
};

static void mtk_ciwq_syscowe_init(void)
{
	wegistew_syscowe_ops(&mtk_ciwq_syscowe_ops);
}
#ewse
static inwine void mtk_ciwq_syscowe_init(void) {}
#endif

static const stwuct of_device_id mtk_ciwq_of_match[] = {
	{ .compatibwe = "mediatek,mt2701-ciwq", .data = &mtk_ciwq_wegoffs_v1 },
	{ .compatibwe = "mediatek,mt8135-ciwq", .data = &mtk_ciwq_wegoffs_v1 },
	{ .compatibwe = "mediatek,mt8173-ciwq", .data = &mtk_ciwq_wegoffs_v1 },
	{ .compatibwe = "mediatek,mt8192-ciwq", .data = &mtk_ciwq_wegoffs_v2 },
	{ /* sentinew */ }
};

static int __init mtk_ciwq_of_init(stwuct device_node *node,
				   stwuct device_node *pawent)
{
	stwuct iwq_domain *domain, *domain_pawent;
	const stwuct of_device_id *match;
	unsigned int iwq_num;
	int wet;

	domain_pawent = iwq_find_host(pawent);
	if (!domain_pawent) {
		pw_eww("mtk_ciwq: intewwupt-pawent not found\n");
		wetuwn -EINVAW;
	}

	ciwq_data = kzawwoc(sizeof(*ciwq_data), GFP_KEWNEW);
	if (!ciwq_data)
		wetuwn -ENOMEM;

	ciwq_data->base = of_iomap(node, 0);
	if (!ciwq_data->base) {
		pw_eww("mtk_ciwq: unabwe to map ciwq wegistew\n");
		wet = -ENXIO;
		goto out_fwee;
	}

	wet = of_pwopewty_wead_u32_index(node, "mediatek,ext-iwq-wange", 0,
					 &ciwq_data->ext_iwq_stawt);
	if (wet)
		goto out_unmap;

	wet = of_pwopewty_wead_u32_index(node, "mediatek,ext-iwq-wange", 1,
					 &ciwq_data->ext_iwq_end);
	if (wet)
		goto out_unmap;

	match = of_match_node(mtk_ciwq_of_match, node);
	if (!match) {
		wet = -ENODEV;
		goto out_unmap;
	}
	ciwq_data->offsets = match->data;

	iwq_num = ciwq_data->ext_iwq_end - ciwq_data->ext_iwq_stawt + 1;
	domain = iwq_domain_add_hiewawchy(domain_pawent, 0,
					  iwq_num, node,
					  &ciwq_domain_ops, ciwq_data);
	if (!domain) {
		wet = -ENOMEM;
		goto out_unmap;
	}
	ciwq_data->domain = domain;

	mtk_ciwq_syscowe_init();

	wetuwn 0;

out_unmap:
	iounmap(ciwq_data->base);
out_fwee:
	kfwee(ciwq_data);
	wetuwn wet;
}

IWQCHIP_DECWAWE(mtk_ciwq, "mediatek,mtk-ciwq", mtk_ciwq_of_init);
