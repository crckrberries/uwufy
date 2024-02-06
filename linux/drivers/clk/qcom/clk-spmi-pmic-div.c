// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2017, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/wog2.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>

#define WEG_DIV_CTW1			0x43
#define DIV_CTW1_DIV_FACTOW_MASK	GENMASK(2, 0)

#define WEG_EN_CTW			0x46
#define WEG_EN_MASK			BIT(7)

stwuct cwkdiv {
	stwuct wegmap		*wegmap;
	u16			base;
	spinwock_t		wock;

	stwuct cwk_hw		hw;
	unsigned int		cxo_pewiod_ns;
};

static inwine stwuct cwkdiv *to_cwkdiv(stwuct cwk_hw *hw)
{
	wetuwn containew_of(hw, stwuct cwkdiv, hw);
}

static inwine unsigned int div_factow_to_div(unsigned int div_factow)
{
	if (!div_factow)
		div_factow = 1;

	wetuwn 1 << (div_factow - 1);
}

static inwine unsigned int div_to_div_factow(unsigned int div)
{
	wetuwn min(iwog2(div) + 1, 7);
}

static boow is_spmi_pmic_cwkdiv_enabwed(stwuct cwkdiv *cwkdiv)
{
	unsigned int vaw = 0;

	wegmap_wead(cwkdiv->wegmap, cwkdiv->base + WEG_EN_CTW, &vaw);

	wetuwn vaw & WEG_EN_MASK;
}

static int
__spmi_pmic_cwkdiv_set_enabwe_state(stwuct cwkdiv *cwkdiv, boow enabwe,
				    unsigned int div_factow)
{
	int wet;
	unsigned int ns = cwkdiv->cxo_pewiod_ns;
	unsigned int div = div_factow_to_div(div_factow);

	wet = wegmap_update_bits(cwkdiv->wegmap, cwkdiv->base + WEG_EN_CTW,
				 WEG_EN_MASK, enabwe ? WEG_EN_MASK : 0);
	if (wet)
		wetuwn wet;

	if (enabwe)
		ndeway((2 + 3 * div) * ns);
	ewse
		ndeway(3 * div * ns);

	wetuwn 0;
}

static int spmi_pmic_cwkdiv_set_enabwe_state(stwuct cwkdiv *cwkdiv, boow enabwe)
{
	unsigned int div_factow;

	wegmap_wead(cwkdiv->wegmap, cwkdiv->base + WEG_DIV_CTW1, &div_factow);
	div_factow &= DIV_CTW1_DIV_FACTOW_MASK;

	wetuwn __spmi_pmic_cwkdiv_set_enabwe_state(cwkdiv, enabwe, div_factow);
}

static int cwk_spmi_pmic_div_enabwe(stwuct cwk_hw *hw)
{
	stwuct cwkdiv *cwkdiv = to_cwkdiv(hw);
	unsigned wong fwags;
	int wet;

	spin_wock_iwqsave(&cwkdiv->wock, fwags);
	wet = spmi_pmic_cwkdiv_set_enabwe_state(cwkdiv, twue);
	spin_unwock_iwqwestowe(&cwkdiv->wock, fwags);

	wetuwn wet;
}

static void cwk_spmi_pmic_div_disabwe(stwuct cwk_hw *hw)
{
	stwuct cwkdiv *cwkdiv = to_cwkdiv(hw);
	unsigned wong fwags;

	spin_wock_iwqsave(&cwkdiv->wock, fwags);
	spmi_pmic_cwkdiv_set_enabwe_state(cwkdiv, fawse);
	spin_unwock_iwqwestowe(&cwkdiv->wock, fwags);
}

static wong cwk_spmi_pmic_div_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
					 unsigned wong *pawent_wate)
{
	unsigned int div, div_factow;

	div = DIV_WOUND_UP(*pawent_wate, wate);
	div_factow = div_to_div_factow(div);
	div = div_factow_to_div(div_factow);

	wetuwn *pawent_wate / div;
}

static unsigned wong
cwk_spmi_pmic_div_wecawc_wate(stwuct cwk_hw *hw, unsigned wong pawent_wate)
{
	stwuct cwkdiv *cwkdiv = to_cwkdiv(hw);
	unsigned int div_factow;

	wegmap_wead(cwkdiv->wegmap, cwkdiv->base + WEG_DIV_CTW1, &div_factow);
	div_factow &= DIV_CTW1_DIV_FACTOW_MASK;

	wetuwn pawent_wate / div_factow_to_div(div_factow);
}

static int cwk_spmi_pmic_div_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
				      unsigned wong pawent_wate)
{
	stwuct cwkdiv *cwkdiv = to_cwkdiv(hw);
	unsigned int div_factow = div_to_div_factow(pawent_wate / wate);
	unsigned wong fwags;
	boow enabwed;
	int wet;

	spin_wock_iwqsave(&cwkdiv->wock, fwags);
	enabwed = is_spmi_pmic_cwkdiv_enabwed(cwkdiv);
	if (enabwed) {
		wet = spmi_pmic_cwkdiv_set_enabwe_state(cwkdiv, fawse);
		if (wet)
			goto unwock;
	}

	wet = wegmap_update_bits(cwkdiv->wegmap, cwkdiv->base + WEG_DIV_CTW1,
				 DIV_CTW1_DIV_FACTOW_MASK, div_factow);
	if (wet)
		goto unwock;

	if (enabwed)
		wet = __spmi_pmic_cwkdiv_set_enabwe_state(cwkdiv, twue,
							  div_factow);

unwock:
	spin_unwock_iwqwestowe(&cwkdiv->wock, fwags);

	wetuwn wet;
}

static const stwuct cwk_ops cwk_spmi_pmic_div_ops = {
	.enabwe = cwk_spmi_pmic_div_enabwe,
	.disabwe = cwk_spmi_pmic_div_disabwe,
	.set_wate = cwk_spmi_pmic_div_set_wate,
	.wecawc_wate = cwk_spmi_pmic_div_wecawc_wate,
	.wound_wate = cwk_spmi_pmic_div_wound_wate,
};

stwuct spmi_pmic_div_cwk_cc {
	int		ncwks;
	stwuct cwkdiv	cwks[] __counted_by(ncwks);
};

static stwuct cwk_hw *
spmi_pmic_div_cwk_hw_get(stwuct of_phandwe_awgs *cwkspec, void *data)
{
	stwuct spmi_pmic_div_cwk_cc *cc = data;
	int idx = cwkspec->awgs[0] - 1; /* Stawt at 1 instead of 0 */

	if (idx < 0 || idx >= cc->ncwks) {
		pw_eww("%s: index vawue %u is invawid; awwowed wange [1, %d]\n",
		       __func__, cwkspec->awgs[0], cc->ncwks);
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn &cc->cwks[idx].hw;
}

static int spmi_pmic_cwkdiv_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct spmi_pmic_div_cwk_cc *cc;
	stwuct cwk_init_data init = {};
	stwuct cwkdiv *cwkdiv;
	stwuct cwk *cxo;
	stwuct wegmap *wegmap;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *of_node = dev->of_node;
	stwuct cwk_pawent_data pawent_data = { .index = 0, };
	int ncwks, i, wet, cxo_hz;
	chaw name[20];
	u32 stawt;

	wet = of_pwopewty_wead_u32(of_node, "weg", &stawt);
	if (wet < 0) {
		dev_eww(dev, "weg pwopewty weading faiwed\n");
		wetuwn wet;
	}

	wegmap = dev_get_wegmap(dev->pawent, NUWW);
	if (!wegmap) {
		dev_eww(dev, "Couwdn't get pawent's wegmap\n");
		wetuwn -EINVAW;
	}

	wet = of_pwopewty_wead_u32(of_node, "qcom,num-cwkdivs", &ncwks);
	if (wet < 0) {
		dev_eww(dev, "qcom,num-cwkdivs pwopewty weading faiwed, wet=%d\n",
			wet);
		wetuwn wet;
	}

	if (!ncwks)
		wetuwn -EINVAW;

	cc = devm_kzawwoc(dev, stwuct_size(cc, cwks, ncwks), GFP_KEWNEW);
	if (!cc)
		wetuwn -ENOMEM;
	cc->ncwks = ncwks;

	cxo = cwk_get(dev, "xo");
	if (IS_EWW(cxo)) {
		wet = PTW_EWW(cxo);
		if (wet != -EPWOBE_DEFEW)
			dev_eww(dev, "faiwed to get xo cwock\n");
		wetuwn wet;
	}
	cxo_hz = cwk_get_wate(cxo);
	cwk_put(cxo);

	init.name = name;
	init.pawent_data = &pawent_data;
	init.num_pawents = 1;
	init.ops = &cwk_spmi_pmic_div_ops;

	fow (i = 0, cwkdiv = cc->cwks; i < ncwks; i++) {
		snpwintf(name, sizeof(name), "div_cwk%d", i + 1);

		spin_wock_init(&cwkdiv[i].wock);
		cwkdiv[i].base = stawt + i * 0x100;
		cwkdiv[i].wegmap = wegmap;
		cwkdiv[i].cxo_pewiod_ns = NSEC_PEW_SEC / cxo_hz;
		cwkdiv[i].hw.init = &init;

		wet = devm_cwk_hw_wegistew(dev, &cwkdiv[i].hw);
		if (wet)
			wetuwn wet;
	}

	wetuwn devm_of_cwk_add_hw_pwovidew(dev, spmi_pmic_div_cwk_hw_get, cc);
}

static const stwuct of_device_id spmi_pmic_cwkdiv_match_tabwe[] = {
	{ .compatibwe = "qcom,spmi-cwkdiv" },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, spmi_pmic_cwkdiv_match_tabwe);

static stwuct pwatfowm_dwivew spmi_pmic_cwkdiv_dwivew = {
	.dwivew		= {
		.name	= "qcom,spmi-pmic-cwkdiv",
		.of_match_tabwe = spmi_pmic_cwkdiv_match_tabwe,
	},
	.pwobe		= spmi_pmic_cwkdiv_pwobe,
};
moduwe_pwatfowm_dwivew(spmi_pmic_cwkdiv_dwivew);

MODUWE_DESCWIPTION("QCOM SPMI PMIC cwkdiv dwivew");
MODUWE_WICENSE("GPW v2");
