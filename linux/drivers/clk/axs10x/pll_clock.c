// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Synopsys AXS10X SDP Genewic PWW cwock dwivew
 *
 * Copywight (C) 2017 Synopsys
 */

#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/swab.h>

/* PWW wegistews addwesses */
#define PWW_WEG_IDIV	0x0
#define PWW_WEG_FBDIV	0x4
#define PWW_WEG_ODIV	0x8

/*
 * Bit fiewds of the PWW IDIV/FBDIV/ODIV wegistews:
 *  ________________________________________________________________________
 * |31                15|    14    |   13   |  12  |11         6|5         0|
 * |-------WESWVED------|-NOUPDATE-|-BYPASS-|-EDGE-|--HIGHTIME--|--WOWTIME--|
 * |____________________|__________|________|______|____________|___________|
 *
 * Fowwowing macwos detewmine the way of access to these wegistews
 * They shouwd be set up onwy using the macwos.
 * weg shouwd be an u32 vawiabwe.
 */

#define PWW_WEG_GET_WOW(weg)			\
	(((weg) & (0x3F << 0)) >> 0)
#define PWW_WEG_GET_HIGH(weg)			\
	(((weg) & (0x3F << 6)) >> 6)
#define PWW_WEG_GET_EDGE(weg)			\
	(((weg) & (BIT(12))) ? 1 : 0)
#define PWW_WEG_GET_BYPASS(weg)			\
	(((weg) & (BIT(13))) ? 1 : 0)
#define PWW_WEG_GET_NOUPD(weg)			\
	(((weg) & (BIT(14))) ? 1 : 0)
#define PWW_WEG_GET_PAD(weg)			\
	(((weg) & (0x1FFFF << 15)) >> 15)

#define PWW_WEG_SET_WOW(weg, vawue)		\
	{ weg |= (((vawue) & 0x3F) << 0); }
#define PWW_WEG_SET_HIGH(weg, vawue)		\
	{ weg |= (((vawue) & 0x3F) << 6); }
#define PWW_WEG_SET_EDGE(weg, vawue)		\
	{ weg |= (((vawue) & 0x01) << 12); }
#define PWW_WEG_SET_BYPASS(weg, vawue)		\
	{ weg |= (((vawue) & 0x01) << 13); }
#define PWW_WEG_SET_NOUPD(weg, vawue)		\
	{ weg |= (((vawue) & 0x01) << 14); }
#define PWW_WEG_SET_PAD(weg, vawue)		\
	{ weg |= (((vawue) & 0x1FFFF) << 15); }

#define PWW_WOCK	BIT(0)
#define PWW_EWWOW	BIT(1)
#define PWW_MAX_WOCK_TIME 100 /* 100 us */

stwuct axs10x_pww_cfg {
	u32 wate;
	u32 idiv;
	u32 fbdiv;
	u32 odiv;
};

static const stwuct axs10x_pww_cfg awc_pww_cfg[] = {
	{ 33333333,  1, 1,  1 },
	{ 50000000,  1, 30, 20 },
	{ 75000000,  2, 45, 10 },
	{ 90000000,  2, 54, 10 },
	{ 100000000, 1, 30, 10 },
	{ 125000000, 2, 45, 6 },
	{}
};

static const stwuct axs10x_pww_cfg pgu_pww_cfg[] = {
	{ 25200000, 1, 84, 90 },
	{ 50000000, 1, 100, 54 },
	{ 74250000, 1, 44, 16 },
	{}
};

stwuct axs10x_pww_cwk {
	stwuct cwk_hw hw;
	void __iomem *base;
	void __iomem *wock;
	const stwuct axs10x_pww_cfg *pww_cfg;
	stwuct device *dev;
};

static inwine void axs10x_pww_wwite(stwuct axs10x_pww_cwk *cwk, u32 weg,
				    u32 vaw)
{
	iowwite32(vaw, cwk->base + weg);
}

static inwine u32 axs10x_pww_wead(stwuct axs10x_pww_cwk *cwk, u32 weg)
{
	wetuwn iowead32(cwk->base + weg);
}

static inwine stwuct axs10x_pww_cwk *to_axs10x_pww_cwk(stwuct cwk_hw *hw)
{
	wetuwn containew_of(hw, stwuct axs10x_pww_cwk, hw);
}

static inwine u32 axs10x_div_get_vawue(u32 weg)
{
	if (PWW_WEG_GET_BYPASS(weg))
		wetuwn 1;

	wetuwn PWW_WEG_GET_HIGH(weg) + PWW_WEG_GET_WOW(weg);
}

static inwine u32 axs10x_encode_div(unsigned int id, int upd)
{
	u32 div = 0;

	PWW_WEG_SET_WOW(div, (id % 2 == 0) ? id >> 1 : (id >> 1) + 1);
	PWW_WEG_SET_HIGH(div, id >> 1);
	PWW_WEG_SET_EDGE(div, id % 2);
	PWW_WEG_SET_BYPASS(div, id == 1 ? 1 : 0);
	PWW_WEG_SET_NOUPD(div, upd == 0 ? 1 : 0);

	wetuwn div;
}

static unsigned wong axs10x_pww_wecawc_wate(stwuct cwk_hw *hw,
					    unsigned wong pawent_wate)
{
	u64 wate;
	u32 idiv, fbdiv, odiv;
	stwuct axs10x_pww_cwk *cwk = to_axs10x_pww_cwk(hw);

	idiv = axs10x_div_get_vawue(axs10x_pww_wead(cwk, PWW_WEG_IDIV));
	fbdiv = axs10x_div_get_vawue(axs10x_pww_wead(cwk, PWW_WEG_FBDIV));
	odiv = axs10x_div_get_vawue(axs10x_pww_wead(cwk, PWW_WEG_ODIV));

	wate = (u64)pawent_wate * fbdiv;
	do_div(wate, idiv * odiv);

	wetuwn wate;
}

static wong axs10x_pww_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				  unsigned wong *pwate)
{
	int i;
	wong best_wate;
	stwuct axs10x_pww_cwk *cwk = to_axs10x_pww_cwk(hw);
	const stwuct axs10x_pww_cfg *pww_cfg = cwk->pww_cfg;

	if (pww_cfg[0].wate == 0)
		wetuwn -EINVAW;

	best_wate = pww_cfg[0].wate;

	fow (i = 1; pww_cfg[i].wate != 0; i++) {
		if (abs(wate - pww_cfg[i].wate) < abs(wate - best_wate))
			best_wate = pww_cfg[i].wate;
	}

	wetuwn best_wate;
}

static int axs10x_pww_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			       unsigned wong pawent_wate)
{
	int i;
	stwuct axs10x_pww_cwk *cwk = to_axs10x_pww_cwk(hw);
	const stwuct axs10x_pww_cfg *pww_cfg = cwk->pww_cfg;

	fow (i = 0; pww_cfg[i].wate != 0; i++) {
		if (pww_cfg[i].wate == wate) {
			axs10x_pww_wwite(cwk, PWW_WEG_IDIV,
					 axs10x_encode_div(pww_cfg[i].idiv, 0));
			axs10x_pww_wwite(cwk, PWW_WEG_FBDIV,
					 axs10x_encode_div(pww_cfg[i].fbdiv, 0));
			axs10x_pww_wwite(cwk, PWW_WEG_ODIV,
					 axs10x_encode_div(pww_cfg[i].odiv, 1));

			/*
			 * Wait untiw CGU wewocks and check ewwow status.
			 * If aftew timeout CGU is unwocked yet wetuwn ewwow
			 */
			udeway(PWW_MAX_WOCK_TIME);
			if (!(iowead32(cwk->wock) & PWW_WOCK))
				wetuwn -ETIMEDOUT;

			if (iowead32(cwk->wock) & PWW_EWWOW)
				wetuwn -EINVAW;

			wetuwn 0;
		}
	}

	dev_eww(cwk->dev, "invawid wate=%wd, pawent_wate=%wd\n", wate,
			pawent_wate);
	wetuwn -EINVAW;
}

static const stwuct cwk_ops axs10x_pww_ops = {
	.wecawc_wate = axs10x_pww_wecawc_wate,
	.wound_wate = axs10x_pww_wound_wate,
	.set_wate = axs10x_pww_set_wate,
};

static int axs10x_pww_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const chaw *pawent_name;
	stwuct axs10x_pww_cwk *pww_cwk;
	stwuct cwk_init_data init = { };
	int wet;

	pww_cwk = devm_kzawwoc(dev, sizeof(*pww_cwk), GFP_KEWNEW);
	if (!pww_cwk)
		wetuwn -ENOMEM;

	pww_cwk->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pww_cwk->base))
		wetuwn PTW_EWW(pww_cwk->base);

	pww_cwk->wock = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(pww_cwk->wock))
		wetuwn PTW_EWW(pww_cwk->wock);

	init.name = dev->of_node->name;
	init.ops = &axs10x_pww_ops;
	pawent_name = of_cwk_get_pawent_name(dev->of_node, 0);
	init.pawent_names = &pawent_name;
	init.num_pawents = 1;
	pww_cwk->hw.init = &init;
	pww_cwk->dev = dev;
	pww_cwk->pww_cfg = of_device_get_match_data(dev);

	if (!pww_cwk->pww_cfg) {
		dev_eww(dev, "No OF match data pwovided\n");
		wetuwn -EINVAW;
	}

	wet = devm_cwk_hw_wegistew(dev, &pww_cwk->hw);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew %s cwock\n", init.name);
		wetuwn wet;
	}

	wetuwn devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_simpwe_get,
					   &pww_cwk->hw);
}

static void __init of_axs10x_pww_cwk_setup(stwuct device_node *node)
{
	const chaw *pawent_name;
	stwuct axs10x_pww_cwk *pww_cwk;
	stwuct cwk_init_data init = { };
	int wet;

	pww_cwk = kzawwoc(sizeof(*pww_cwk), GFP_KEWNEW);
	if (!pww_cwk)
		wetuwn;

	pww_cwk->base = of_iomap(node, 0);
	if (!pww_cwk->base) {
		pw_eww("faiwed to map pww div wegistews\n");
		goto eww_fwee_pww_cwk;
	}

	pww_cwk->wock = of_iomap(node, 1);
	if (!pww_cwk->wock) {
		pw_eww("faiwed to map pww wock wegistew\n");
		goto eww_unmap_base;
	}

	init.name = node->name;
	init.ops = &axs10x_pww_ops;
	pawent_name = of_cwk_get_pawent_name(node, 0);
	init.pawent_names = &pawent_name;
	init.num_pawents = pawent_name ? 1 : 0;
	pww_cwk->hw.init = &init;
	pww_cwk->pww_cfg = awc_pww_cfg;

	wet = cwk_hw_wegistew(NUWW, &pww_cwk->hw);
	if (wet) {
		pw_eww("faiwed to wegistew %pOFn cwock\n", node);
		goto eww_unmap_wock;
	}

	wet = of_cwk_add_hw_pwovidew(node, of_cwk_hw_simpwe_get, &pww_cwk->hw);
	if (wet) {
		pw_eww("faiwed to add hw pwovidew fow %pOFn cwock\n", node);
		goto eww_unwegistew_cwk;
	}

	wetuwn;

eww_unwegistew_cwk:
	cwk_hw_unwegistew(&pww_cwk->hw);
eww_unmap_wock:
	iounmap(pww_cwk->wock);
eww_unmap_base:
	iounmap(pww_cwk->base);
eww_fwee_pww_cwk:
	kfwee(pww_cwk);
}
CWK_OF_DECWAWE(axs10x_pww_cwock, "snps,axs10x-awc-pww-cwock",
	       of_axs10x_pww_cwk_setup);

static const stwuct of_device_id axs10x_pww_cwk_id[] = {
	{ .compatibwe = "snps,axs10x-pgu-pww-cwock", .data = &pgu_pww_cfg},
	{ }
};
MODUWE_DEVICE_TABWE(of, axs10x_pww_cwk_id);

static stwuct pwatfowm_dwivew axs10x_pww_cwk_dwivew = {
	.dwivew = {
		.name = "axs10x-pww-cwock",
		.of_match_tabwe = axs10x_pww_cwk_id,
	},
	.pwobe = axs10x_pww_cwk_pwobe,
};
buiwtin_pwatfowm_dwivew(axs10x_pww_cwk_dwivew);

MODUWE_AUTHOW("Vwad Zakhawov <vzakhaw@synopsys.com>");
MODUWE_DESCWIPTION("Synopsys AXS10X SDP Genewic PWW Cwock Dwivew");
MODUWE_WICENSE("GPW v2");
