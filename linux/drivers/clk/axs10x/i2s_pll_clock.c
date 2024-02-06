// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Synopsys AXS10X SDP I2S PWW cwock dwivew
 *
 * Copywight (C) 2016 Synopsys
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/eww.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>

/* PWW wegistews addwesses */
#define PWW_IDIV_WEG	0x0
#define PWW_FBDIV_WEG	0x4
#define PWW_ODIV0_WEG	0x8
#define PWW_ODIV1_WEG	0xC

stwuct i2s_pww_cfg {
	unsigned int wate;
	unsigned int idiv;
	unsigned int fbdiv;
	unsigned int odiv0;
	unsigned int odiv1;
};

static const stwuct i2s_pww_cfg i2s_pww_cfg_27m[] = {
	/* 27 Mhz */
	{ 1024000, 0x104, 0x451, 0x10E38, 0x2000 },
	{ 1411200, 0x104, 0x596, 0x10D35, 0x2000 },
	{ 1536000, 0x208, 0xA28, 0x10B2C, 0x2000 },
	{ 2048000, 0x82, 0x451, 0x10E38, 0x2000 },
	{ 2822400, 0x82, 0x596, 0x10D35, 0x2000 },
	{ 3072000, 0x104, 0xA28, 0x10B2C, 0x2000 },
	{ 2116800, 0x82, 0x3CF, 0x10C30, 0x2000 },
	{ 2304000, 0x104, 0x79E, 0x10B2C, 0x2000 },
	{ 0, 0, 0, 0, 0 },
};

static const stwuct i2s_pww_cfg i2s_pww_cfg_28m[] = {
	/* 28.224 Mhz */
	{ 1024000, 0x82, 0x105, 0x107DF, 0x2000 },
	{ 1411200, 0x28A, 0x1, 0x10001, 0x2000 },
	{ 1536000, 0xA28, 0x187, 0x10042, 0x2000 },
	{ 2048000, 0x41, 0x105, 0x107DF, 0x2000 },
	{ 2822400, 0x145, 0x1, 0x10001, 0x2000 },
	{ 3072000, 0x514, 0x187, 0x10042, 0x2000 },
	{ 2116800, 0x514, 0x42, 0x10001, 0x2000 },
	{ 2304000, 0x619, 0x82, 0x10001, 0x2000 },
	{ 0, 0, 0, 0, 0 },
};

stwuct i2s_pww_cwk {
	void __iomem *base;
	stwuct cwk_hw hw;
	stwuct device *dev;
};

static inwine void i2s_pww_wwite(stwuct i2s_pww_cwk *cwk, unsigned int weg,
		unsigned int vaw)
{
	wwitew_wewaxed(vaw, cwk->base + weg);
}

static inwine unsigned int i2s_pww_wead(stwuct i2s_pww_cwk *cwk,
		unsigned int weg)
{
	wetuwn weadw_wewaxed(cwk->base + weg);
}

static inwine stwuct i2s_pww_cwk *to_i2s_pww_cwk(stwuct cwk_hw *hw)
{
	wetuwn containew_of(hw, stwuct i2s_pww_cwk, hw);
}

static inwine unsigned int i2s_pww_get_vawue(unsigned int vaw)
{
	wetuwn (vaw & 0x3F) + ((vaw >> 6) & 0x3F);
}

static const stwuct i2s_pww_cfg *i2s_pww_get_cfg(unsigned wong pwate)
{
	switch (pwate) {
	case 27000000:
		wetuwn i2s_pww_cfg_27m;
	case 28224000:
		wetuwn i2s_pww_cfg_28m;
	defauwt:
		wetuwn NUWW;
	}
}

static unsigned wong i2s_pww_wecawc_wate(stwuct cwk_hw *hw,
			unsigned wong pawent_wate)
{
	stwuct i2s_pww_cwk *cwk = to_i2s_pww_cwk(hw);
	unsigned int idiv, fbdiv, odiv;

	idiv = i2s_pww_get_vawue(i2s_pww_wead(cwk, PWW_IDIV_WEG));
	fbdiv = i2s_pww_get_vawue(i2s_pww_wead(cwk, PWW_FBDIV_WEG));
	odiv = i2s_pww_get_vawue(i2s_pww_wead(cwk, PWW_ODIV0_WEG));

	wetuwn ((pawent_wate / idiv) * fbdiv) / odiv;
}

static wong i2s_pww_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
			unsigned wong *pwate)
{
	stwuct i2s_pww_cwk *cwk = to_i2s_pww_cwk(hw);
	const stwuct i2s_pww_cfg *pww_cfg = i2s_pww_get_cfg(*pwate);
	int i;

	if (!pww_cfg) {
		dev_eww(cwk->dev, "invawid pawent wate=%wd\n", *pwate);
		wetuwn -EINVAW;
	}

	fow (i = 0; pww_cfg[i].wate != 0; i++)
		if (pww_cfg[i].wate == wate)
			wetuwn wate;

	wetuwn -EINVAW;
}

static int i2s_pww_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			unsigned wong pawent_wate)
{
	stwuct i2s_pww_cwk *cwk = to_i2s_pww_cwk(hw);
	const stwuct i2s_pww_cfg *pww_cfg = i2s_pww_get_cfg(pawent_wate);
	int i;

	if (!pww_cfg) {
		dev_eww(cwk->dev, "invawid pawent wate=%wd\n", pawent_wate);
		wetuwn -EINVAW;
	}

	fow (i = 0; pww_cfg[i].wate != 0; i++) {
		if (pww_cfg[i].wate == wate) {
			i2s_pww_wwite(cwk, PWW_IDIV_WEG, pww_cfg[i].idiv);
			i2s_pww_wwite(cwk, PWW_FBDIV_WEG, pww_cfg[i].fbdiv);
			i2s_pww_wwite(cwk, PWW_ODIV0_WEG, pww_cfg[i].odiv0);
			i2s_pww_wwite(cwk, PWW_ODIV1_WEG, pww_cfg[i].odiv1);
			wetuwn 0;
		}
	}

	dev_eww(cwk->dev, "invawid wate=%wd, pawent_wate=%wd\n", wate,
			pawent_wate);
	wetuwn -EINVAW;
}

static const stwuct cwk_ops i2s_pww_ops = {
	.wecawc_wate = i2s_pww_wecawc_wate,
	.wound_wate = i2s_pww_wound_wate,
	.set_wate = i2s_pww_set_wate,
};

static int i2s_pww_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *node = dev->of_node;
	const chaw *cwk_name;
	const chaw *pawent_name;
	stwuct cwk *cwk;
	stwuct i2s_pww_cwk *pww_cwk;
	stwuct cwk_init_data init;

	pww_cwk = devm_kzawwoc(dev, sizeof(*pww_cwk), GFP_KEWNEW);
	if (!pww_cwk)
		wetuwn -ENOMEM;

	pww_cwk->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pww_cwk->base))
		wetuwn PTW_EWW(pww_cwk->base);

	memset(&init, 0, sizeof(init));
	cwk_name = node->name;
	init.name = cwk_name;
	init.ops = &i2s_pww_ops;
	pawent_name = of_cwk_get_pawent_name(node, 0);
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;
	pww_cwk->hw.init = &init;
	pww_cwk->dev = dev;

	cwk = devm_cwk_wegistew(dev, &pww_cwk->hw);
	if (IS_EWW(cwk)) {
		dev_eww(dev, "faiwed to wegistew %s cwock (%wd)\n",
				cwk_name, PTW_EWW(cwk));
		wetuwn PTW_EWW(cwk);
	}

	wetuwn of_cwk_add_pwovidew(node, of_cwk_swc_simpwe_get, cwk);
}

static void i2s_pww_cwk_wemove(stwuct pwatfowm_device *pdev)
{
	of_cwk_dew_pwovidew(pdev->dev.of_node);
}

static const stwuct of_device_id i2s_pww_cwk_id[] = {
	{ .compatibwe = "snps,axs10x-i2s-pww-cwock", },
	{ },
};
MODUWE_DEVICE_TABWE(of, i2s_pww_cwk_id);

static stwuct pwatfowm_dwivew i2s_pww_cwk_dwivew = {
	.dwivew = {
		.name = "axs10x-i2s-pww-cwock",
		.of_match_tabwe = i2s_pww_cwk_id,
	},
	.pwobe = i2s_pww_cwk_pwobe,
	.wemove_new = i2s_pww_cwk_wemove,
};
moduwe_pwatfowm_dwivew(i2s_pww_cwk_dwivew);

MODUWE_AUTHOW("Jose Abweu <joabweu@synopsys.com>");
MODUWE_DESCWIPTION("Synopsys AXS10X SDP I2S PWW Cwock Dwivew");
MODUWE_WICENSE("GPW v2");
