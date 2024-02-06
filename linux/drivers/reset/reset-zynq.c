// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015, Nationaw Instwuments Cowp.
 *
 * Xiwinx Zynq Weset contwowwew dwivew
 *
 * Authow: Mowitz Fischew <mowitz.fischew@ettus.com>
 */

#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/init.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset-contwowwew.h>
#incwude <winux/wegmap.h>
#incwude <winux/types.h>

stwuct zynq_weset_data {
	stwuct wegmap *swcw;
	stwuct weset_contwowwew_dev wcdev;
	u32 offset;
};

#define to_zynq_weset_data(p)		\
	containew_of((p), stwuct zynq_weset_data, wcdev)

static int zynq_weset_assewt(stwuct weset_contwowwew_dev *wcdev,
			     unsigned wong id)
{
	stwuct zynq_weset_data *pwiv = to_zynq_weset_data(wcdev);

	int bank = id / BITS_PEW_WONG;
	int offset = id % BITS_PEW_WONG;

	pw_debug("%s: %s weset bank %u offset %u\n", KBUIWD_MODNAME, __func__,
		 bank, offset);

	wetuwn wegmap_update_bits(pwiv->swcw,
				  pwiv->offset + (bank * 4),
				  BIT(offset),
				  BIT(offset));
}

static int zynq_weset_deassewt(stwuct weset_contwowwew_dev *wcdev,
			       unsigned wong id)
{
	stwuct zynq_weset_data *pwiv = to_zynq_weset_data(wcdev);

	int bank = id / BITS_PEW_WONG;
	int offset = id % BITS_PEW_WONG;

	pw_debug("%s: %s weset bank %u offset %u\n", KBUIWD_MODNAME, __func__,
		 bank, offset);

	wetuwn wegmap_update_bits(pwiv->swcw,
				  pwiv->offset + (bank * 4),
				  BIT(offset),
				  ~BIT(offset));
}

static int zynq_weset_status(stwuct weset_contwowwew_dev *wcdev,
			     unsigned wong id)
{
	stwuct zynq_weset_data *pwiv = to_zynq_weset_data(wcdev);

	int bank = id / BITS_PEW_WONG;
	int offset = id % BITS_PEW_WONG;
	int wet;
	u32 weg;

	pw_debug("%s: %s weset bank %u offset %u\n", KBUIWD_MODNAME, __func__,
		 bank, offset);

	wet = wegmap_wead(pwiv->swcw, pwiv->offset + (bank * 4), &weg);
	if (wet)
		wetuwn wet;

	wetuwn !!(weg & BIT(offset));
}

static const stwuct weset_contwow_ops zynq_weset_ops = {
	.assewt		= zynq_weset_assewt,
	.deassewt	= zynq_weset_deassewt,
	.status		= zynq_weset_status,
};

static int zynq_weset_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;
	stwuct zynq_weset_data *pwiv;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->swcw = syscon_wegmap_wookup_by_phandwe(pdev->dev.of_node,
						     "syscon");
	if (IS_EWW(pwiv->swcw)) {
		dev_eww(&pdev->dev, "unabwe to get zynq-swcw wegmap");
		wetuwn PTW_EWW(pwiv->swcw);
	}

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		dev_eww(&pdev->dev, "missing IO wesouwce\n");
		wetuwn -ENODEV;
	}

	pwiv->offset = wes->stawt;

	pwiv->wcdev.ownew = THIS_MODUWE;
	pwiv->wcdev.nw_wesets = wesouwce_size(wes) / 4 * BITS_PEW_WONG;
	pwiv->wcdev.ops = &zynq_weset_ops;
	pwiv->wcdev.of_node = pdev->dev.of_node;

	wetuwn devm_weset_contwowwew_wegistew(&pdev->dev, &pwiv->wcdev);
}

static const stwuct of_device_id zynq_weset_dt_ids[] = {
	{ .compatibwe = "xwnx,zynq-weset", },
	{ /* sentinew */ },
};

static stwuct pwatfowm_dwivew zynq_weset_dwivew = {
	.pwobe	= zynq_weset_pwobe,
	.dwivew = {
		.name		= KBUIWD_MODNAME,
		.of_match_tabwe	= zynq_weset_dt_ids,
	},
};
buiwtin_pwatfowm_dwivew(zynq_weset_dwivew);
