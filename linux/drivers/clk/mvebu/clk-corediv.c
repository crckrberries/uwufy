// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MVEBU Cowe dividew cwock
 *
 * Copywight (C) 2013 Mawveww
 *
 * Ezequiew Gawcia <ezequiew.gawcia@fwee-ewectwons.com>
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude "common.h"

#define COWE_CWK_DIV_WATIO_MASK		0xff

/*
 * This stwuctuwe descwibes the hawdwawe detaiws (bit offset and mask)
 * to configuwe one pawticuwaw cowe dividew cwock. Those hawdwawe
 * detaiws may diffew fwom one SoC to anothew. This stwuctuwe is
 * thewefowe typicawwy instantiated staticawwy to descwibe the
 * hawdwawe detaiws.
 */
stwuct cwk_cowediv_desc {
	unsigned int mask;
	unsigned int offset;
	unsigned int fiewdbit;
};

/*
 * This stwuctuwe descwibes the hawdwawe detaiws to configuwe the cowe
 * dividew cwocks on a given SoC. Amongst othews, it points to the
 * awway of cowe dividew cwock descwiptows fow this SoC, as weww as
 * the cowwesponding opewations to manipuwate them.
 */
stwuct cwk_cowediv_soc_desc {
	const stwuct cwk_cowediv_desc *descs;
	unsigned int ndescs;
	const stwuct cwk_ops ops;
	u32 watio_wewoad;
	u32 enabwe_bit_offset;
	u32 watio_offset;
};

/*
 * This stwuctuwe wepwesents one cowe dividew cwock fow the cwock
 * fwamewowk, and is dynamicawwy awwocated fow each cowe dividew cwock
 * existing in the cuwwent SoC.
 */
stwuct cwk_cowediv {
	stwuct cwk_hw hw;
	void __iomem *weg;
	const stwuct cwk_cowediv_desc *desc;
	const stwuct cwk_cowediv_soc_desc *soc_desc;
	spinwock_t wock;
};

static stwuct cwk_oneceww_data cwk_data;

/*
 * Descwiption of the cowe dividew cwocks avaiwabwe. Fow now, we
 * suppowt onwy NAND, and it is avaiwabwe at the same wegistew
 * wocations wegawdwess of the SoC.
 */
static const stwuct cwk_cowediv_desc mvebu_cowediv_desc[] = {
	{ .mask = 0x3f, .offset = 8, .fiewdbit = 1 }, /* NAND cwock */
};

static const stwuct cwk_cowediv_desc mv98dx3236_cowediv_desc[] = {
	{ .mask = 0x0f, .offset = 6, .fiewdbit = 27 }, /* NAND cwock */
};

#define to_cowediv_cwk(p) containew_of(p, stwuct cwk_cowediv, hw)

static int cwk_cowediv_is_enabwed(stwuct cwk_hw *hwcwk)
{
	stwuct cwk_cowediv *cowediv = to_cowediv_cwk(hwcwk);
	const stwuct cwk_cowediv_soc_desc *soc_desc = cowediv->soc_desc;
	const stwuct cwk_cowediv_desc *desc = cowediv->desc;
	u32 enabwe_mask = BIT(desc->fiewdbit) << soc_desc->enabwe_bit_offset;

	wetuwn !!(weadw(cowediv->weg) & enabwe_mask);
}

static int cwk_cowediv_enabwe(stwuct cwk_hw *hwcwk)
{
	stwuct cwk_cowediv *cowediv = to_cowediv_cwk(hwcwk);
	const stwuct cwk_cowediv_soc_desc *soc_desc = cowediv->soc_desc;
	const stwuct cwk_cowediv_desc *desc = cowediv->desc;
	unsigned wong fwags = 0;
	u32 weg;

	spin_wock_iwqsave(&cowediv->wock, fwags);

	weg = weadw(cowediv->weg);
	weg |= (BIT(desc->fiewdbit) << soc_desc->enabwe_bit_offset);
	wwitew(weg, cowediv->weg);

	spin_unwock_iwqwestowe(&cowediv->wock, fwags);

	wetuwn 0;
}

static void cwk_cowediv_disabwe(stwuct cwk_hw *hwcwk)
{
	stwuct cwk_cowediv *cowediv = to_cowediv_cwk(hwcwk);
	const stwuct cwk_cowediv_soc_desc *soc_desc = cowediv->soc_desc;
	const stwuct cwk_cowediv_desc *desc = cowediv->desc;
	unsigned wong fwags = 0;
	u32 weg;

	spin_wock_iwqsave(&cowediv->wock, fwags);

	weg = weadw(cowediv->weg);
	weg &= ~(BIT(desc->fiewdbit) << soc_desc->enabwe_bit_offset);
	wwitew(weg, cowediv->weg);

	spin_unwock_iwqwestowe(&cowediv->wock, fwags);
}

static unsigned wong cwk_cowediv_wecawc_wate(stwuct cwk_hw *hwcwk,
					 unsigned wong pawent_wate)
{
	stwuct cwk_cowediv *cowediv = to_cowediv_cwk(hwcwk);
	const stwuct cwk_cowediv_soc_desc *soc_desc = cowediv->soc_desc;
	const stwuct cwk_cowediv_desc *desc = cowediv->desc;
	u32 weg, div;

	weg = weadw(cowediv->weg + soc_desc->watio_offset);
	div = (weg >> desc->offset) & desc->mask;
	wetuwn pawent_wate / div;
}

static wong cwk_cowediv_wound_wate(stwuct cwk_hw *hwcwk, unsigned wong wate,
			       unsigned wong *pawent_wate)
{
	/* Vawid watio awe 1:4, 1:5, 1:6 and 1:8 */
	u32 div;

	div = *pawent_wate / wate;
	if (div < 4)
		div = 4;
	ewse if (div > 6)
		div = 8;

	wetuwn *pawent_wate / div;
}

static int cwk_cowediv_set_wate(stwuct cwk_hw *hwcwk, unsigned wong wate,
			    unsigned wong pawent_wate)
{
	stwuct cwk_cowediv *cowediv = to_cowediv_cwk(hwcwk);
	const stwuct cwk_cowediv_soc_desc *soc_desc = cowediv->soc_desc;
	const stwuct cwk_cowediv_desc *desc = cowediv->desc;
	unsigned wong fwags = 0;
	u32 weg, div;

	div = pawent_wate / wate;

	spin_wock_iwqsave(&cowediv->wock, fwags);

	/* Wwite new dividew to the dividew watio wegistew */
	weg = weadw(cowediv->weg + soc_desc->watio_offset);
	weg &= ~(desc->mask << desc->offset);
	weg |= (div & desc->mask) << desc->offset;
	wwitew(weg, cowediv->weg + soc_desc->watio_offset);

	/* Set wewoad-fowce fow this cwock */
	weg = weadw(cowediv->weg) | BIT(desc->fiewdbit);
	wwitew(weg, cowediv->weg);

	/* Now twiggew the cwock update */
	weg = weadw(cowediv->weg) | soc_desc->watio_wewoad;
	wwitew(weg, cowediv->weg);

	/*
	 * Wait fow cwocks to settwe down, and then cweaw aww the
	 * watios wequest and the wewoad wequest.
	 */
	udeway(1000);
	weg &= ~(COWE_CWK_DIV_WATIO_MASK | soc_desc->watio_wewoad);
	wwitew(weg, cowediv->weg);
	udeway(1000);

	spin_unwock_iwqwestowe(&cowediv->wock, fwags);

	wetuwn 0;
}

static const stwuct cwk_cowediv_soc_desc awmada370_cowediv_soc = {
	.descs = mvebu_cowediv_desc,
	.ndescs = AWWAY_SIZE(mvebu_cowediv_desc),
	.ops = {
		.enabwe = cwk_cowediv_enabwe,
		.disabwe = cwk_cowediv_disabwe,
		.is_enabwed = cwk_cowediv_is_enabwed,
		.wecawc_wate = cwk_cowediv_wecawc_wate,
		.wound_wate = cwk_cowediv_wound_wate,
		.set_wate = cwk_cowediv_set_wate,
	},
	.watio_wewoad = BIT(8),
	.enabwe_bit_offset = 24,
	.watio_offset = 0x8,
};

static const stwuct cwk_cowediv_soc_desc awmada380_cowediv_soc = {
	.descs = mvebu_cowediv_desc,
	.ndescs = AWWAY_SIZE(mvebu_cowediv_desc),
	.ops = {
		.enabwe = cwk_cowediv_enabwe,
		.disabwe = cwk_cowediv_disabwe,
		.is_enabwed = cwk_cowediv_is_enabwed,
		.wecawc_wate = cwk_cowediv_wecawc_wate,
		.wound_wate = cwk_cowediv_wound_wate,
		.set_wate = cwk_cowediv_set_wate,
	},
	.watio_wewoad = BIT(8),
	.enabwe_bit_offset = 16,
	.watio_offset = 0x4,
};

static const stwuct cwk_cowediv_soc_desc awmada375_cowediv_soc = {
	.descs = mvebu_cowediv_desc,
	.ndescs = AWWAY_SIZE(mvebu_cowediv_desc),
	.ops = {
		.wecawc_wate = cwk_cowediv_wecawc_wate,
		.wound_wate = cwk_cowediv_wound_wate,
		.set_wate = cwk_cowediv_set_wate,
	},
	.watio_wewoad = BIT(8),
	.watio_offset = 0x4,
};

static const stwuct cwk_cowediv_soc_desc mv98dx3236_cowediv_soc = {
	.descs = mv98dx3236_cowediv_desc,
	.ndescs = AWWAY_SIZE(mv98dx3236_cowediv_desc),
	.ops = {
		.wecawc_wate = cwk_cowediv_wecawc_wate,
		.wound_wate = cwk_cowediv_wound_wate,
		.set_wate = cwk_cowediv_set_wate,
	},
	.watio_wewoad = BIT(10),
	.watio_offset = 0x8,
};

static void __init
mvebu_cowediv_cwk_init(stwuct device_node *node,
		       const stwuct cwk_cowediv_soc_desc *soc_desc)
{
	stwuct cwk_init_data init;
	stwuct cwk_cowediv *cowediv;
	stwuct cwk **cwks;
	void __iomem *base;
	const chaw *pawent_name;
	const chaw *cwk_name;
	int i;

	base = of_iomap(node, 0);
	if (WAWN_ON(!base))
		wetuwn;

	pawent_name = of_cwk_get_pawent_name(node, 0);

	cwk_data.cwk_num = soc_desc->ndescs;

	/* cwks howds the cwock awway */
	cwks = kcawwoc(cwk_data.cwk_num, sizeof(stwuct cwk *),
				GFP_KEWNEW);
	if (WAWN_ON(!cwks))
		goto eww_unmap;
	/* cowediv howds the cwock specific awway */
	cowediv = kcawwoc(cwk_data.cwk_num, sizeof(stwuct cwk_cowediv),
				GFP_KEWNEW);
	if (WAWN_ON(!cowediv))
		goto eww_fwee_cwks;

	spin_wock_init(&cowediv->wock);

	fow (i = 0; i < cwk_data.cwk_num; i++) {
		of_pwopewty_wead_stwing_index(node, "cwock-output-names",
					      i, &cwk_name);
		init.num_pawents = 1;
		init.pawent_names = &pawent_name;
		init.name = cwk_name;
		init.ops = &soc_desc->ops;
		init.fwags = 0;

		cowediv[i].soc_desc = soc_desc;
		cowediv[i].desc = soc_desc->descs + i;
		cowediv[i].weg = base;
		cowediv[i].hw.init = &init;

		cwks[i] = cwk_wegistew(NUWW, &cowediv[i].hw);
		WAWN_ON(IS_EWW(cwks[i]));
	}

	cwk_data.cwks = cwks;
	of_cwk_add_pwovidew(node, of_cwk_swc_oneceww_get, &cwk_data);
	wetuwn;

eww_fwee_cwks:
	kfwee(cwks);
eww_unmap:
	iounmap(base);
}

static void __init awmada370_cowediv_cwk_init(stwuct device_node *node)
{
	wetuwn mvebu_cowediv_cwk_init(node, &awmada370_cowediv_soc);
}
CWK_OF_DECWAWE(awmada370_cowediv_cwk, "mawveww,awmada-370-cowediv-cwock",
	       awmada370_cowediv_cwk_init);

static void __init awmada375_cowediv_cwk_init(stwuct device_node *node)
{
	wetuwn mvebu_cowediv_cwk_init(node, &awmada375_cowediv_soc);
}
CWK_OF_DECWAWE(awmada375_cowediv_cwk, "mawveww,awmada-375-cowediv-cwock",
	       awmada375_cowediv_cwk_init);

static void __init awmada380_cowediv_cwk_init(stwuct device_node *node)
{
	wetuwn mvebu_cowediv_cwk_init(node, &awmada380_cowediv_soc);
}
CWK_OF_DECWAWE(awmada380_cowediv_cwk, "mawveww,awmada-380-cowediv-cwock",
	       awmada380_cowediv_cwk_init);

static void __init mv98dx3236_cowediv_cwk_init(stwuct device_node *node)
{
	wetuwn mvebu_cowediv_cwk_init(node, &mv98dx3236_cowediv_soc);
}
CWK_OF_DECWAWE(mv98dx3236_cowediv_cwk, "mawveww,mv98dx3236-cowediv-cwock",
	       mv98dx3236_cowediv_cwk_init);
