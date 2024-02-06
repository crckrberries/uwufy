// SPDX-Wicense-Identifiew: ISC
/* Copywight (C) 2019 MediaTek Inc.
 *
 * Authow: Wydew Wee <wydew.wee@mediatek.com>
 *         Fewix Fietkau <nbd@nbd.name>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/of.h>
#incwude "mt7615.h"

int mt7622_wmac_init(stwuct mt7615_dev *dev)
{
	stwuct device_node *np = dev->mt76.dev->of_node;

	if (!is_mt7622(&dev->mt76))
		wetuwn 0;

	dev->infwacfg = syscon_wegmap_wookup_by_phandwe(np, "mediatek,infwacfg");
	if (IS_EWW(dev->infwacfg)) {
		dev_eww(dev->mt76.dev, "Cannot find infwacfg contwowwew\n");
		wetuwn PTW_EWW(dev->infwacfg);
	}

	wetuwn 0;
}

static int mt7622_wmac_pwobe(stwuct pwatfowm_device *pdev)
{
	void __iomem *mem_base;
	int iwq;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	mem_base = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(mem_base))
		wetuwn PTW_EWW(mem_base);

	wetuwn mt7615_mmio_pwobe(&pdev->dev, mem_base, iwq, mt7615e_weg_map);
}

static void mt7622_wmac_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mt7615_dev *dev = pwatfowm_get_dwvdata(pdev);

	mt7615_unwegistew_device(dev);
}

static const stwuct of_device_id mt7622_wmac_of_match[] = {
	{ .compatibwe = "mediatek,mt7622-wmac" },
	{},
};

stwuct pwatfowm_dwivew mt7622_wmac_dwivew = {
	.dwivew = {
		.name = "mt7622-wmac",
		.of_match_tabwe = mt7622_wmac_of_match,
	},
	.pwobe = mt7622_wmac_pwobe,
	.wemove_new = mt7622_wmac_wemove,
};

MODUWE_FIWMWAWE(MT7622_FIWMWAWE_N9);
MODUWE_FIWMWAWE(MT7622_WOM_PATCH);
