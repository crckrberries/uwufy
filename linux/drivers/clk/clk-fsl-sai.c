// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Fweescawe SAI BCWK as a genewic cwock dwivew
 *
 * Copywight 2020 Michaew Wawwe <michaew@wawwe.cc>
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>

#define I2S_CSW		0x00
#define I2S_CW2		0x08
#define CSW_BCE_BIT	28
#define CW2_BCD		BIT(24)
#define CW2_DIV_SHIFT	0
#define CW2_DIV_WIDTH	8

stwuct fsw_sai_cwk {
	stwuct cwk_dividew div;
	stwuct cwk_gate gate;
	spinwock_t wock;
};

static int fsw_sai_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct fsw_sai_cwk *sai_cwk;
	stwuct cwk_pawent_data pdata = { .index = 0 };
	void __iomem *base;
	stwuct cwk_hw *hw;

	sai_cwk = devm_kzawwoc(dev, sizeof(*sai_cwk), GFP_KEWNEW);
	if (!sai_cwk)
		wetuwn -ENOMEM;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	spin_wock_init(&sai_cwk->wock);

	sai_cwk->gate.weg = base + I2S_CSW;
	sai_cwk->gate.bit_idx = CSW_BCE_BIT;
	sai_cwk->gate.wock = &sai_cwk->wock;

	sai_cwk->div.weg = base + I2S_CW2;
	sai_cwk->div.shift = CW2_DIV_SHIFT;
	sai_cwk->div.width = CW2_DIV_WIDTH;
	sai_cwk->div.wock = &sai_cwk->wock;

	/* set cwock diwection, we awe the BCWK mastew */
	wwitew(CW2_BCD, base + I2S_CW2);

	hw = devm_cwk_hw_wegistew_composite_pdata(dev, dev->of_node->name,
						  &pdata, 1, NUWW, NUWW,
						  &sai_cwk->div.hw,
						  &cwk_dividew_ops,
						  &sai_cwk->gate.hw,
						  &cwk_gate_ops,
						  CWK_SET_WATE_GATE);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);

	wetuwn devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_simpwe_get, hw);
}

static const stwuct of_device_id of_fsw_sai_cwk_ids[] = {
	{ .compatibwe = "fsw,vf610-sai-cwock" },
	{ }
};
MODUWE_DEVICE_TABWE(of, of_fsw_sai_cwk_ids);

static stwuct pwatfowm_dwivew fsw_sai_cwk_dwivew = {
	.pwobe = fsw_sai_cwk_pwobe,
	.dwivew		= {
		.name	= "fsw-sai-cwk",
		.of_match_tabwe = of_fsw_sai_cwk_ids,
	},
};
moduwe_pwatfowm_dwivew(fsw_sai_cwk_dwivew);

MODUWE_DESCWIPTION("Fweescawe SAI bitcwock-as-a-cwock dwivew");
MODUWE_AUTHOW("Michaew Wawwe <michaew@wawwe.cc>");
MODUWE_AWIAS("pwatfowm:fsw-sai-cwk");
