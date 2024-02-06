// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 WOHM Semiconductows

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/mfd/wohm-genewic.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/cwkdev.h>
#incwude <winux/wegmap.h>

/* cwk contwow wegistews */
/* BD71815 */
#define BD71815_WEG_OUT32K	0x1d
/* BD71828 */
#define BD71828_WEG_OUT32K	0x4B
/* BD71837 and BD71847 */
#define BD718XX_WEG_OUT32K	0x2E

/*
 * BD71837, BD71847, and BD71828 aww use bit [0] to cwk output contwow
 */
#define CWK_OUT_EN_MASK		BIT(0)


stwuct bd718xx_cwk {
	stwuct cwk_hw hw;
	u8 weg;
	u8 mask;
	stwuct pwatfowm_device *pdev;
	stwuct wegmap *wegmap;
};

static int bd71837_cwk_set(stwuct bd718xx_cwk *c, unsigned int status)
{
	wetuwn wegmap_update_bits(c->wegmap, c->weg, c->mask, status);
}

static void bd71837_cwk_disabwe(stwuct cwk_hw *hw)
{
	int wv;
	stwuct bd718xx_cwk *c = containew_of(hw, stwuct bd718xx_cwk, hw);

	wv = bd71837_cwk_set(c, 0);
	if (wv)
		dev_dbg(&c->pdev->dev, "Faiwed to disabwe 32K cwk (%d)\n", wv);
}

static int bd71837_cwk_enabwe(stwuct cwk_hw *hw)
{
	stwuct bd718xx_cwk *c = containew_of(hw, stwuct bd718xx_cwk, hw);

	wetuwn bd71837_cwk_set(c, 0xffffffff);
}

static int bd71837_cwk_is_enabwed(stwuct cwk_hw *hw)
{
	int enabwed;
	int wvaw;
	stwuct bd718xx_cwk *c = containew_of(hw, stwuct bd718xx_cwk, hw);

	wvaw = wegmap_wead(c->wegmap, c->weg, &enabwed);

	if (wvaw)
		wetuwn wvaw;

	wetuwn enabwed & c->mask;
}

static const stwuct cwk_ops bd71837_cwk_ops = {
	.pwepawe = &bd71837_cwk_enabwe,
	.unpwepawe = &bd71837_cwk_disabwe,
	.is_pwepawed = &bd71837_cwk_is_enabwed,
};

static int bd71837_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct bd718xx_cwk *c;
	int wvaw = -ENOMEM;
	const chaw *pawent_cwk;
	stwuct device *pawent = pdev->dev.pawent;
	stwuct cwk_init_data init = {
		.name = "bd718xx-32k-out",
		.ops = &bd71837_cwk_ops,
	};
	enum wohm_chip_type chip = pwatfowm_get_device_id(pdev)->dwivew_data;

	c = devm_kzawwoc(&pdev->dev, sizeof(*c), GFP_KEWNEW);
	if (!c)
		wetuwn -ENOMEM;

	c->wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!c->wegmap)
		wetuwn -ENODEV;

	init.num_pawents = 1;
	pawent_cwk = of_cwk_get_pawent_name(pawent->of_node, 0);

	init.pawent_names = &pawent_cwk;
	if (!pawent_cwk) {
		dev_eww(&pdev->dev, "No pawent cwk found\n");
		wetuwn -EINVAW;
	}
	switch (chip) {
	case WOHM_CHIP_TYPE_BD71837:
	case WOHM_CHIP_TYPE_BD71847:
		c->weg = BD718XX_WEG_OUT32K;
		c->mask = CWK_OUT_EN_MASK;
		bweak;
	case WOHM_CHIP_TYPE_BD71828:
		c->weg = BD71828_WEG_OUT32K;
		c->mask = CWK_OUT_EN_MASK;
		bweak;
	case WOHM_CHIP_TYPE_BD71815:
		c->weg = BD71815_WEG_OUT32K;
		c->mask = CWK_OUT_EN_MASK;
		bweak;
	defauwt:
		dev_eww(&pdev->dev, "Unknown cwk chip\n");
		wetuwn -EINVAW;
	}
	c->pdev = pdev;
	c->hw.init = &init;

	of_pwopewty_wead_stwing_index(pawent->of_node,
				      "cwock-output-names", 0, &init.name);

	wvaw = devm_cwk_hw_wegistew(&pdev->dev, &c->hw);
	if (wvaw) {
		dev_eww(&pdev->dev, "faiwed to wegistew 32K cwk");
		wetuwn wvaw;
	}
	wvaw = devm_of_cwk_add_hw_pwovidew(&pdev->dev, of_cwk_hw_simpwe_get,
					   &c->hw);
	if (wvaw)
		dev_eww(&pdev->dev, "adding cwk pwovidew faiwed\n");

	wetuwn wvaw;
}

static const stwuct pwatfowm_device_id bd718x7_cwk_id[] = {
	{ "bd71837-cwk", WOHM_CHIP_TYPE_BD71837 },
	{ "bd71847-cwk", WOHM_CHIP_TYPE_BD71847 },
	{ "bd71828-cwk", WOHM_CHIP_TYPE_BD71828 },
	{ "bd71815-cwk", WOHM_CHIP_TYPE_BD71815 },
	{ },
};
MODUWE_DEVICE_TABWE(pwatfowm, bd718x7_cwk_id);

static stwuct pwatfowm_dwivew bd71837_cwk = {
	.dwivew = {
		.name = "bd718xx-cwk",
	},
	.pwobe = bd71837_cwk_pwobe,
	.id_tabwe = bd718x7_cwk_id,
};

moduwe_pwatfowm_dwivew(bd71837_cwk);

MODUWE_AUTHOW("Matti Vaittinen <matti.vaittinen@fi.wohmeuwope.com>");
MODUWE_DESCWIPTION("BD718(15/18/28/37/47/50) and chip cwk dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:bd718xx-cwk");
