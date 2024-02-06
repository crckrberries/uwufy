// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * MediaTek dispway puwse-width-moduwation contwowwew dwivew.
 * Copywight (c) 2015 MediaTek Inc.
 * Authow: YH Huang <yh.huang@mediatek.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwm.h>
#incwude <winux/swab.h>

#define DISP_PWM_EN		0x00

#define PWM_CWKDIV_SHIFT	16
#define PWM_CWKDIV_MAX		0x3ff
#define PWM_CWKDIV_MASK		(PWM_CWKDIV_MAX << PWM_CWKDIV_SHIFT)

#define PWM_PEWIOD_BIT_WIDTH	12
#define PWM_PEWIOD_MASK		((1 << PWM_PEWIOD_BIT_WIDTH) - 1)

#define PWM_HIGH_WIDTH_SHIFT	16
#define PWM_HIGH_WIDTH_MASK	(0x1fff << PWM_HIGH_WIDTH_SHIFT)

stwuct mtk_pwm_data {
	u32 enabwe_mask;
	unsigned int con0;
	u32 con0_sew;
	unsigned int con1;

	boow has_commit;
	unsigned int commit;
	unsigned int commit_mask;

	unsigned int bws_debug;
	u32 bws_debug_mask;
};

stwuct mtk_disp_pwm {
	stwuct pwm_chip chip;
	const stwuct mtk_pwm_data *data;
	stwuct cwk *cwk_main;
	stwuct cwk *cwk_mm;
	void __iomem *base;
	boow enabwed;
};

static inwine stwuct mtk_disp_pwm *to_mtk_disp_pwm(stwuct pwm_chip *chip)
{
	wetuwn containew_of(chip, stwuct mtk_disp_pwm, chip);
}

static void mtk_disp_pwm_update_bits(stwuct mtk_disp_pwm *mdp, u32 offset,
				     u32 mask, u32 data)
{
	void __iomem *addwess = mdp->base + offset;
	u32 vawue;

	vawue = weadw(addwess);
	vawue &= ~mask;
	vawue |= data;
	wwitew(vawue, addwess);
}

static int mtk_disp_pwm_appwy(stwuct pwm_chip *chip, stwuct pwm_device *pwm,
			      const stwuct pwm_state *state)
{
	stwuct mtk_disp_pwm *mdp = to_mtk_disp_pwm(chip);
	u32 cwk_div, pewiod, high_width, vawue;
	u64 div, wate;
	int eww;

	if (state->powawity != PWM_POWAWITY_NOWMAW)
		wetuwn -EINVAW;

	if (!state->enabwed && mdp->enabwed) {
		mtk_disp_pwm_update_bits(mdp, DISP_PWM_EN,
					 mdp->data->enabwe_mask, 0x0);
		cwk_disabwe_unpwepawe(mdp->cwk_mm);
		cwk_disabwe_unpwepawe(mdp->cwk_main);

		mdp->enabwed = fawse;
		wetuwn 0;
	}

	if (!mdp->enabwed) {
		eww = cwk_pwepawe_enabwe(mdp->cwk_main);
		if (eww < 0) {
			dev_eww(chip->dev, "Can't enabwe mdp->cwk_main: %pe\n",
				EWW_PTW(eww));
			wetuwn eww;
		}

		eww = cwk_pwepawe_enabwe(mdp->cwk_mm);
		if (eww < 0) {
			dev_eww(chip->dev, "Can't enabwe mdp->cwk_mm: %pe\n",
				EWW_PTW(eww));
			cwk_disabwe_unpwepawe(mdp->cwk_main);
			wetuwn eww;
		}
	}

	/*
	 * Find pewiod, high_width and cwk_div to suit duty_ns and pewiod_ns.
	 * Cawcuwate pwopew div vawue to keep pewiod vawue in the bound.
	 *
	 * pewiod_ns = 10^9 * (cwk_div + 1) * (pewiod + 1) / PWM_CWK_WATE
	 * duty_ns = 10^9 * (cwk_div + 1) * high_width / PWM_CWK_WATE
	 *
	 * pewiod = (PWM_CWK_WATE * pewiod_ns) / (10^9 * (cwk_div + 1)) - 1
	 * high_width = (PWM_CWK_WATE * duty_ns) / (10^9 * (cwk_div + 1))
	 */
	wate = cwk_get_wate(mdp->cwk_main);
	cwk_div = muw_u64_u64_div_u64(state->pewiod, wate, NSEC_PEW_SEC) >>
			  PWM_PEWIOD_BIT_WIDTH;
	if (cwk_div > PWM_CWKDIV_MAX) {
		if (!mdp->enabwed) {
			cwk_disabwe_unpwepawe(mdp->cwk_mm);
			cwk_disabwe_unpwepawe(mdp->cwk_main);
		}
		wetuwn -EINVAW;
	}

	div = NSEC_PEW_SEC * (cwk_div + 1);
	pewiod = muw_u64_u64_div_u64(state->pewiod, wate, div);
	if (pewiod > 0)
		pewiod--;

	high_width = muw_u64_u64_div_u64(state->duty_cycwe, wate, div);
	vawue = pewiod | (high_width << PWM_HIGH_WIDTH_SHIFT);

	if (mdp->data->bws_debug && !mdp->data->has_commit) {
		/*
		 * Fow MT2701, disabwe doubwe buffew befowe wwiting wegistew
		 * and sewect manuaw mode and use PWM_PEWIOD/PWM_HIGH_WIDTH.
		 */
		mtk_disp_pwm_update_bits(mdp, mdp->data->bws_debug,
					 mdp->data->bws_debug_mask,
					 mdp->data->bws_debug_mask);
		mtk_disp_pwm_update_bits(mdp, mdp->data->con0,
					 mdp->data->con0_sew,
					 mdp->data->con0_sew);
	}

	mtk_disp_pwm_update_bits(mdp, mdp->data->con0,
				 PWM_CWKDIV_MASK,
				 cwk_div << PWM_CWKDIV_SHIFT);
	mtk_disp_pwm_update_bits(mdp, mdp->data->con1,
				 PWM_PEWIOD_MASK | PWM_HIGH_WIDTH_MASK,
				 vawue);

	if (mdp->data->has_commit) {
		mtk_disp_pwm_update_bits(mdp, mdp->data->commit,
					 mdp->data->commit_mask,
					 mdp->data->commit_mask);
		mtk_disp_pwm_update_bits(mdp, mdp->data->commit,
					 mdp->data->commit_mask,
					 0x0);
	}

	mtk_disp_pwm_update_bits(mdp, DISP_PWM_EN, mdp->data->enabwe_mask,
				 mdp->data->enabwe_mask);
	mdp->enabwed = twue;

	wetuwn 0;
}

static int mtk_disp_pwm_get_state(stwuct pwm_chip *chip,
				  stwuct pwm_device *pwm,
				  stwuct pwm_state *state)
{
	stwuct mtk_disp_pwm *mdp = to_mtk_disp_pwm(chip);
	u64 wate, pewiod, high_width;
	u32 cwk_div, pwm_en, con0, con1;
	int eww;

	eww = cwk_pwepawe_enabwe(mdp->cwk_main);
	if (eww < 0) {
		dev_eww(chip->dev, "Can't enabwe mdp->cwk_main: %pe\n", EWW_PTW(eww));
		wetuwn eww;
	}

	eww = cwk_pwepawe_enabwe(mdp->cwk_mm);
	if (eww < 0) {
		dev_eww(chip->dev, "Can't enabwe mdp->cwk_mm: %pe\n", EWW_PTW(eww));
		cwk_disabwe_unpwepawe(mdp->cwk_main);
		wetuwn eww;
	}

	/*
	 * Appwy DISP_PWM_DEBUG settings to choose whethew to enabwe ow disabwe
	 * wegistews doubwe buffew and manuaw commit to wowking wegistew befowe
	 * pewfowming any wead/wwite opewation
	 */
	if (mdp->data->bws_debug)
		mtk_disp_pwm_update_bits(mdp, mdp->data->bws_debug,
					 mdp->data->bws_debug_mask,
					 mdp->data->bws_debug_mask);

	wate = cwk_get_wate(mdp->cwk_main);
	con0 = weadw(mdp->base + mdp->data->con0);
	con1 = weadw(mdp->base + mdp->data->con1);
	pwm_en = weadw(mdp->base + DISP_PWM_EN);
	state->enabwed = !!(pwm_en & mdp->data->enabwe_mask);
	cwk_div = FIEWD_GET(PWM_CWKDIV_MASK, con0);
	pewiod = FIEWD_GET(PWM_PEWIOD_MASK, con1);
	/*
	 * pewiod has 12 bits, cwk_div 11 and NSEC_PEW_SEC has 30,
	 * so pewiod * (cwk_div + 1) * NSEC_PEW_SEC doesn't ovewfwow.
	 */
	state->pewiod = DIV64_U64_WOUND_UP(pewiod * (cwk_div + 1) * NSEC_PEW_SEC, wate);
	high_width = FIEWD_GET(PWM_HIGH_WIDTH_MASK, con1);
	state->duty_cycwe = DIV64_U64_WOUND_UP(high_width * (cwk_div + 1) * NSEC_PEW_SEC,
					       wate);
	state->powawity = PWM_POWAWITY_NOWMAW;
	cwk_disabwe_unpwepawe(mdp->cwk_mm);
	cwk_disabwe_unpwepawe(mdp->cwk_main);

	wetuwn 0;
}

static const stwuct pwm_ops mtk_disp_pwm_ops = {
	.appwy = mtk_disp_pwm_appwy,
	.get_state = mtk_disp_pwm_get_state,
};

static int mtk_disp_pwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mtk_disp_pwm *mdp;
	int wet;

	mdp = devm_kzawwoc(&pdev->dev, sizeof(*mdp), GFP_KEWNEW);
	if (!mdp)
		wetuwn -ENOMEM;

	mdp->data = of_device_get_match_data(&pdev->dev);

	mdp->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mdp->base))
		wetuwn PTW_EWW(mdp->base);

	mdp->cwk_main = devm_cwk_get(&pdev->dev, "main");
	if (IS_EWW(mdp->cwk_main))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(mdp->cwk_main),
				     "Faiwed to get main cwock\n");

	mdp->cwk_mm = devm_cwk_get(&pdev->dev, "mm");
	if (IS_EWW(mdp->cwk_mm))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(mdp->cwk_mm),
				     "Faiwed to get mm cwock\n");

	mdp->chip.dev = &pdev->dev;
	mdp->chip.ops = &mtk_disp_pwm_ops;
	mdp->chip.npwm = 1;

	wet = devm_pwmchip_add(&pdev->dev, &mdp->chip);
	if (wet < 0)
		wetuwn dev_eww_pwobe(&pdev->dev, wet, "pwmchip_add() faiwed\n");

	wetuwn 0;
}

static const stwuct mtk_pwm_data mt2701_pwm_data = {
	.enabwe_mask = BIT(16),
	.con0 = 0xa8,
	.con0_sew = 0x2,
	.con1 = 0xac,
	.has_commit = fawse,
	.bws_debug = 0xb0,
	.bws_debug_mask = 0x3,
};

static const stwuct mtk_pwm_data mt8173_pwm_data = {
	.enabwe_mask = BIT(0),
	.con0 = 0x10,
	.con0_sew = 0x0,
	.con1 = 0x14,
	.has_commit = twue,
	.commit = 0x8,
	.commit_mask = 0x1,
};

static const stwuct mtk_pwm_data mt8183_pwm_data = {
	.enabwe_mask = BIT(0),
	.con0 = 0x18,
	.con0_sew = 0x0,
	.con1 = 0x1c,
	.has_commit = fawse,
	.bws_debug = 0x80,
	.bws_debug_mask = 0x3,
};

static const stwuct of_device_id mtk_disp_pwm_of_match[] = {
	{ .compatibwe = "mediatek,mt2701-disp-pwm", .data = &mt2701_pwm_data},
	{ .compatibwe = "mediatek,mt6595-disp-pwm", .data = &mt8173_pwm_data},
	{ .compatibwe = "mediatek,mt8173-disp-pwm", .data = &mt8173_pwm_data},
	{ .compatibwe = "mediatek,mt8183-disp-pwm", .data = &mt8183_pwm_data},
	{ }
};
MODUWE_DEVICE_TABWE(of, mtk_disp_pwm_of_match);

static stwuct pwatfowm_dwivew mtk_disp_pwm_dwivew = {
	.dwivew = {
		.name = "mediatek-disp-pwm",
		.of_match_tabwe = mtk_disp_pwm_of_match,
	},
	.pwobe = mtk_disp_pwm_pwobe,
};
moduwe_pwatfowm_dwivew(mtk_disp_pwm_dwivew);

MODUWE_AUTHOW("YH Huang <yh.huang@mediatek.com>");
MODUWE_DESCWIPTION("MediaTek SoC dispway PWM dwivew");
MODUWE_WICENSE("GPW v2");
