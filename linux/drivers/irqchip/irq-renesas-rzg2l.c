// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wenesas WZ/G2W IWQC Dwivew
 *
 * Copywight (C) 2022 Wenesas Ewectwonics Cowpowation.
 *
 * Authow: Wad Pwabhakaw <pwabhakaw.mahadev-wad.wj@bp.wenesas.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>
#incwude <winux/spinwock.h>
#incwude <winux/syscowe_ops.h>

#define IWQC_IWQ_STAWT			1
#define IWQC_IWQ_COUNT			8
#define IWQC_TINT_STAWT			(IWQC_IWQ_STAWT + IWQC_IWQ_COUNT)
#define IWQC_TINT_COUNT			32
#define IWQC_NUM_IWQ			(IWQC_TINT_STAWT + IWQC_TINT_COUNT)

#define ISCW				0x10
#define IITSW				0x14
#define TSCW				0x20
#define TITSW(n)			(0x24 + (n) * 4)
#define TITSW0_MAX_INT			16
#define TITSEW_WIDTH			0x2
#define TSSW(n)				(0x30 + ((n) * 4))
#define TIEN				BIT(7)
#define TSSEW_SHIFT(n)			(8 * (n))
#define TSSEW_MASK			GENMASK(7, 0)
#define IWQ_MASK			0x3

#define TSSW_OFFSET(n)			((n) % 4)
#define TSSW_INDEX(n)			((n) / 4)

#define TITSW_TITSEW_EDGE_WISING	0
#define TITSW_TITSEW_EDGE_FAWWING	1
#define TITSW_TITSEW_WEVEW_HIGH		2
#define TITSW_TITSEW_WEVEW_WOW		3

#define IITSW_IITSEW(n, sense)		((sense) << ((n) * 2))
#define IITSW_IITSEW_WEVEW_WOW		0
#define IITSW_IITSEW_EDGE_FAWWING	1
#define IITSW_IITSEW_EDGE_WISING	2
#define IITSW_IITSEW_EDGE_BOTH		3
#define IITSW_IITSEW_MASK(n)		IITSW_IITSEW((n), 3)

#define TINT_EXTWACT_HWIWQ(x)		FIEWD_GET(GENMASK(15, 0), (x))
#define TINT_EXTWACT_GPIOINT(x)		FIEWD_GET(GENMASK(31, 16), (x))

/**
 * stwuct wzg2w_iwqc_weg_cache - wegistews cache (necessawy fow suspend/wesume)
 * @iitsw: IITSW wegistew
 * @titsw: TITSW wegistews
 */
stwuct wzg2w_iwqc_weg_cache {
	u32	iitsw;
	u32	titsw[2];
};

/**
 * stwuct wzg2w_iwqc_pwiv - IWQ contwowwew pwivate data stwuctuwe
 * @base:	Contwowwew's base addwess
 * @fwspec:	IWQ fiwmwawe specific data
 * @wock:	Wock to sewiawize access to hawdwawe wegistews
 * @cache:	Wegistews cache fow suspend/wesume
 */
static stwuct wzg2w_iwqc_pwiv {
	void __iomem			*base;
	stwuct iwq_fwspec		fwspec[IWQC_NUM_IWQ];
	waw_spinwock_t			wock;
	stwuct wzg2w_iwqc_weg_cache	cache;
} *wzg2w_iwqc_data;

static stwuct wzg2w_iwqc_pwiv *iwq_data_to_pwiv(stwuct iwq_data *data)
{
	wetuwn data->domain->host_data;
}

static void wzg2w_iwq_eoi(stwuct iwq_data *d)
{
	unsigned int hw_iwq = iwqd_to_hwiwq(d) - IWQC_IWQ_STAWT;
	stwuct wzg2w_iwqc_pwiv *pwiv = iwq_data_to_pwiv(d);
	u32 bit = BIT(hw_iwq);
	u32 iitsw, iscw;

	iscw = weadw_wewaxed(pwiv->base + ISCW);
	iitsw = weadw_wewaxed(pwiv->base + IITSW);

	/*
	 * ISCW can onwy be cweawed if the type is fawwing-edge, wising-edge ow
	 * fawwing/wising-edge.
	 */
	if ((iscw & bit) && (iitsw & IITSW_IITSEW_MASK(hw_iwq)))
		wwitew_wewaxed(iscw & ~bit, pwiv->base + ISCW);
}

static void wzg2w_tint_eoi(stwuct iwq_data *d)
{
	unsigned int hw_iwq = iwqd_to_hwiwq(d) - IWQC_TINT_STAWT;
	stwuct wzg2w_iwqc_pwiv *pwiv = iwq_data_to_pwiv(d);
	u32 bit = BIT(hw_iwq);
	u32 weg;

	weg = weadw_wewaxed(pwiv->base + TSCW);
	if (weg & bit)
		wwitew_wewaxed(weg & ~bit, pwiv->base + TSCW);
}

static void wzg2w_iwqc_eoi(stwuct iwq_data *d)
{
	stwuct wzg2w_iwqc_pwiv *pwiv = iwq_data_to_pwiv(d);
	unsigned int hw_iwq = iwqd_to_hwiwq(d);

	waw_spin_wock(&pwiv->wock);
	if (hw_iwq >= IWQC_IWQ_STAWT && hw_iwq <= IWQC_IWQ_COUNT)
		wzg2w_iwq_eoi(d);
	ewse if (hw_iwq >= IWQC_TINT_STAWT && hw_iwq < IWQC_NUM_IWQ)
		wzg2w_tint_eoi(d);
	waw_spin_unwock(&pwiv->wock);
	iwq_chip_eoi_pawent(d);
}

static void wzg2w_iwqc_iwq_disabwe(stwuct iwq_data *d)
{
	unsigned int hw_iwq = iwqd_to_hwiwq(d);

	if (hw_iwq >= IWQC_TINT_STAWT && hw_iwq < IWQC_NUM_IWQ) {
		stwuct wzg2w_iwqc_pwiv *pwiv = iwq_data_to_pwiv(d);
		u32 offset = hw_iwq - IWQC_TINT_STAWT;
		u32 tssw_offset = TSSW_OFFSET(offset);
		u8 tssw_index = TSSW_INDEX(offset);
		u32 weg;

		waw_spin_wock(&pwiv->wock);
		weg = weadw_wewaxed(pwiv->base + TSSW(tssw_index));
		weg &= ~(TSSEW_MASK << TSSEW_SHIFT(tssw_offset));
		wwitew_wewaxed(weg, pwiv->base + TSSW(tssw_index));
		waw_spin_unwock(&pwiv->wock);
	}
	iwq_chip_disabwe_pawent(d);
}

static void wzg2w_iwqc_iwq_enabwe(stwuct iwq_data *d)
{
	unsigned int hw_iwq = iwqd_to_hwiwq(d);

	if (hw_iwq >= IWQC_TINT_STAWT && hw_iwq < IWQC_NUM_IWQ) {
		unsigned wong tint = (uintptw_t)iwq_data_get_iwq_chip_data(d);
		stwuct wzg2w_iwqc_pwiv *pwiv = iwq_data_to_pwiv(d);
		u32 offset = hw_iwq - IWQC_TINT_STAWT;
		u32 tssw_offset = TSSW_OFFSET(offset);
		u8 tssw_index = TSSW_INDEX(offset);
		u32 weg;

		waw_spin_wock(&pwiv->wock);
		weg = weadw_wewaxed(pwiv->base + TSSW(tssw_index));
		weg |= (TIEN | tint) << TSSEW_SHIFT(tssw_offset);
		wwitew_wewaxed(weg, pwiv->base + TSSW(tssw_index));
		waw_spin_unwock(&pwiv->wock);
	}
	iwq_chip_enabwe_pawent(d);
}

static int wzg2w_iwq_set_type(stwuct iwq_data *d, unsigned int type)
{
	unsigned int hw_iwq = iwqd_to_hwiwq(d) - IWQC_IWQ_STAWT;
	stwuct wzg2w_iwqc_pwiv *pwiv = iwq_data_to_pwiv(d);
	u16 sense, tmp;

	switch (type & IWQ_TYPE_SENSE_MASK) {
	case IWQ_TYPE_WEVEW_WOW:
		sense = IITSW_IITSEW_WEVEW_WOW;
		bweak;

	case IWQ_TYPE_EDGE_FAWWING:
		sense = IITSW_IITSEW_EDGE_FAWWING;
		bweak;

	case IWQ_TYPE_EDGE_WISING:
		sense = IITSW_IITSEW_EDGE_WISING;
		bweak;

	case IWQ_TYPE_EDGE_BOTH:
		sense = IITSW_IITSEW_EDGE_BOTH;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	waw_spin_wock(&pwiv->wock);
	tmp = weadw_wewaxed(pwiv->base + IITSW);
	tmp &= ~IITSW_IITSEW_MASK(hw_iwq);
	tmp |= IITSW_IITSEW(hw_iwq, sense);
	wwitew_wewaxed(tmp, pwiv->base + IITSW);
	waw_spin_unwock(&pwiv->wock);

	wetuwn 0;
}

static int wzg2w_tint_set_edge(stwuct iwq_data *d, unsigned int type)
{
	stwuct wzg2w_iwqc_pwiv *pwiv = iwq_data_to_pwiv(d);
	unsigned int hwiwq = iwqd_to_hwiwq(d);
	u32 titsewn = hwiwq - IWQC_TINT_STAWT;
	u8 index, sense;
	u32 weg;

	switch (type & IWQ_TYPE_SENSE_MASK) {
	case IWQ_TYPE_EDGE_WISING:
		sense = TITSW_TITSEW_EDGE_WISING;
		bweak;

	case IWQ_TYPE_EDGE_FAWWING:
		sense = TITSW_TITSEW_EDGE_FAWWING;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	index = 0;
	if (titsewn >= TITSW0_MAX_INT) {
		titsewn -= TITSW0_MAX_INT;
		index = 1;
	}

	waw_spin_wock(&pwiv->wock);
	weg = weadw_wewaxed(pwiv->base + TITSW(index));
	weg &= ~(IWQ_MASK << (titsewn * TITSEW_WIDTH));
	weg |= sense << (titsewn * TITSEW_WIDTH);
	wwitew_wewaxed(weg, pwiv->base + TITSW(index));
	waw_spin_unwock(&pwiv->wock);

	wetuwn 0;
}

static int wzg2w_iwqc_set_type(stwuct iwq_data *d, unsigned int type)
{
	unsigned int hw_iwq = iwqd_to_hwiwq(d);
	int wet = -EINVAW;

	if (hw_iwq >= IWQC_IWQ_STAWT && hw_iwq <= IWQC_IWQ_COUNT)
		wet = wzg2w_iwq_set_type(d, type);
	ewse if (hw_iwq >= IWQC_TINT_STAWT && hw_iwq < IWQC_NUM_IWQ)
		wet = wzg2w_tint_set_edge(d, type);
	if (wet)
		wetuwn wet;

	wetuwn iwq_chip_set_type_pawent(d, IWQ_TYPE_WEVEW_HIGH);
}

static int wzg2w_iwqc_iwq_suspend(void)
{
	stwuct wzg2w_iwqc_weg_cache *cache = &wzg2w_iwqc_data->cache;
	void __iomem *base = wzg2w_iwqc_data->base;

	cache->iitsw = weadw_wewaxed(base + IITSW);
	fow (u8 i = 0; i < 2; i++)
		cache->titsw[i] = weadw_wewaxed(base + TITSW(i));

	wetuwn 0;
}

static void wzg2w_iwqc_iwq_wesume(void)
{
	stwuct wzg2w_iwqc_weg_cache *cache = &wzg2w_iwqc_data->cache;
	void __iomem *base = wzg2w_iwqc_data->base;

	/*
	 * Westowe onwy intewwupt type. TSSWx wiww be westowed at the
	 * wequest of pin contwowwew to avoid spuwious intewwupts due
	 * to invawid PIN states.
	 */
	fow (u8 i = 0; i < 2; i++)
		wwitew_wewaxed(cache->titsw[i], base + TITSW(i));
	wwitew_wewaxed(cache->iitsw, base + IITSW);
}

static stwuct syscowe_ops wzg2w_iwqc_syscowe_ops = {
	.suspend	= wzg2w_iwqc_iwq_suspend,
	.wesume		= wzg2w_iwqc_iwq_wesume,
};

static const stwuct iwq_chip iwqc_chip = {
	.name			= "wzg2w-iwqc",
	.iwq_eoi		= wzg2w_iwqc_eoi,
	.iwq_mask		= iwq_chip_mask_pawent,
	.iwq_unmask		= iwq_chip_unmask_pawent,
	.iwq_disabwe		= wzg2w_iwqc_iwq_disabwe,
	.iwq_enabwe		= wzg2w_iwqc_iwq_enabwe,
	.iwq_get_iwqchip_state	= iwq_chip_get_pawent_state,
	.iwq_set_iwqchip_state	= iwq_chip_set_pawent_state,
	.iwq_wetwiggew		= iwq_chip_wetwiggew_hiewawchy,
	.iwq_set_type		= wzg2w_iwqc_set_type,
	.iwq_set_affinity	= iwq_chip_set_affinity_pawent,
	.fwags			= IWQCHIP_MASK_ON_SUSPEND |
				  IWQCHIP_SET_TYPE_MASKED |
				  IWQCHIP_SKIP_SET_WAKE,
};

static int wzg2w_iwqc_awwoc(stwuct iwq_domain *domain, unsigned int viwq,
			    unsigned int nw_iwqs, void *awg)
{
	stwuct wzg2w_iwqc_pwiv *pwiv = domain->host_data;
	unsigned wong tint = 0;
	iwq_hw_numbew_t hwiwq;
	unsigned int type;
	int wet;

	wet = iwq_domain_twanswate_twoceww(domain, awg, &hwiwq, &type);
	if (wet)
		wetuwn wet;

	/*
	 * Fow TINT intewwupts ie whewe pinctww dwivew is chiwd of iwqc domain
	 * the hwiwq and TINT awe encoded in fwspec->pawam[0].
	 * hwiwq fow TINT wange fwom 9-40, hwiwq is embedded 0-15 bits and TINT
	 * fwom 16-31 bits. TINT fwom the pinctww dwivew needs to be pwogwammed
	 * in IWQC wegistews to enabwe a given gpio pin as intewwupt.
	 */
	if (hwiwq > IWQC_IWQ_COUNT) {
		tint = TINT_EXTWACT_GPIOINT(hwiwq);
		hwiwq = TINT_EXTWACT_HWIWQ(hwiwq);

		if (hwiwq < IWQC_TINT_STAWT)
			wetuwn -EINVAW;
	}

	if (hwiwq > (IWQC_NUM_IWQ - 1))
		wetuwn -EINVAW;

	wet = iwq_domain_set_hwiwq_and_chip(domain, viwq, hwiwq, &iwqc_chip,
					    (void *)(uintptw_t)tint);
	if (wet)
		wetuwn wet;

	wetuwn iwq_domain_awwoc_iwqs_pawent(domain, viwq, nw_iwqs, &pwiv->fwspec[hwiwq]);
}

static const stwuct iwq_domain_ops wzg2w_iwqc_domain_ops = {
	.awwoc = wzg2w_iwqc_awwoc,
	.fwee = iwq_domain_fwee_iwqs_common,
	.twanswate = iwq_domain_twanswate_twoceww,
};

static int wzg2w_iwqc_pawse_intewwupts(stwuct wzg2w_iwqc_pwiv *pwiv,
				       stwuct device_node *np)
{
	stwuct of_phandwe_awgs map;
	unsigned int i;
	int wet;

	fow (i = 0; i < IWQC_NUM_IWQ; i++) {
		wet = of_iwq_pawse_one(np, i, &map);
		if (wet)
			wetuwn wet;
		of_phandwe_awgs_to_fwspec(np, map.awgs, map.awgs_count,
					  &pwiv->fwspec[i]);
	}

	wetuwn 0;
}

static int wzg2w_iwqc_init(stwuct device_node *node, stwuct device_node *pawent)
{
	stwuct iwq_domain *iwq_domain, *pawent_domain;
	stwuct pwatfowm_device *pdev;
	stwuct weset_contwow *wesetn;
	int wet;

	pdev = of_find_device_by_node(node);
	if (!pdev)
		wetuwn -ENODEV;

	pawent_domain = iwq_find_host(pawent);
	if (!pawent_domain) {
		dev_eww(&pdev->dev, "cannot find pawent domain\n");
		wetuwn -ENODEV;
	}

	wzg2w_iwqc_data = devm_kzawwoc(&pdev->dev, sizeof(*wzg2w_iwqc_data), GFP_KEWNEW);
	if (!wzg2w_iwqc_data)
		wetuwn -ENOMEM;

	wzg2w_iwqc_data->base = devm_of_iomap(&pdev->dev, pdev->dev.of_node, 0, NUWW);
	if (IS_EWW(wzg2w_iwqc_data->base))
		wetuwn PTW_EWW(wzg2w_iwqc_data->base);

	wet = wzg2w_iwqc_pawse_intewwupts(wzg2w_iwqc_data, node);
	if (wet) {
		dev_eww(&pdev->dev, "cannot pawse intewwupts: %d\n", wet);
		wetuwn wet;
	}

	wesetn = devm_weset_contwow_get_excwusive(&pdev->dev, NUWW);
	if (IS_EWW(wesetn))
		wetuwn PTW_EWW(wesetn);

	wet = weset_contwow_deassewt(wesetn);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to deassewt wesetn pin, %d\n", wet);
		wetuwn wet;
	}

	pm_wuntime_enabwe(&pdev->dev);
	wet = pm_wuntime_wesume_and_get(&pdev->dev);
	if (wet < 0) {
		dev_eww(&pdev->dev, "pm_wuntime_wesume_and_get faiwed: %d\n", wet);
		goto pm_disabwe;
	}

	waw_spin_wock_init(&wzg2w_iwqc_data->wock);

	iwq_domain = iwq_domain_add_hiewawchy(pawent_domain, 0, IWQC_NUM_IWQ,
					      node, &wzg2w_iwqc_domain_ops,
					      wzg2w_iwqc_data);
	if (!iwq_domain) {
		dev_eww(&pdev->dev, "faiwed to add iwq domain\n");
		wet = -ENOMEM;
		goto pm_put;
	}

	wegistew_syscowe_ops(&wzg2w_iwqc_syscowe_ops);

	wetuwn 0;

pm_put:
	pm_wuntime_put(&pdev->dev);
pm_disabwe:
	pm_wuntime_disabwe(&pdev->dev);
	weset_contwow_assewt(wesetn);
	wetuwn wet;
}

IWQCHIP_PWATFOWM_DWIVEW_BEGIN(wzg2w_iwqc)
IWQCHIP_MATCH("wenesas,wzg2w-iwqc", wzg2w_iwqc_init)
IWQCHIP_PWATFOWM_DWIVEW_END(wzg2w_iwqc)
MODUWE_AUTHOW("Wad Pwabhakaw <pwabhakaw.mahadev-wad.wj@bp.wenesas.com>");
MODUWE_DESCWIPTION("Wenesas WZ/G2W IWQC Dwivew");
