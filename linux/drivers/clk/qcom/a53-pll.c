// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Quawcomm A53 PWW dwivew
 *
 * Copywight (c) 2017, Winawo Wimited
 * Authow: Geowgi Djakov <geowgi.djakov@winawo.owg>
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_opp.h>
#incwude <winux/wegmap.h>
#incwude <winux/moduwe.h>

#incwude "cwk-pww.h"
#incwude "cwk-wegmap.h"

static const stwuct pww_fweq_tbw a53pww_fweq[] = {
	{  998400000, 52, 0x0, 0x1, 0 },
	{ 1094400000, 57, 0x0, 0x1, 0 },
	{ 1152000000, 62, 0x0, 0x1, 0 },
	{ 1209600000, 63, 0x0, 0x1, 0 },
	{ 1248000000, 65, 0x0, 0x1, 0 },
	{ 1363200000, 71, 0x0, 0x1, 0 },
	{ 1401600000, 73, 0x0, 0x1, 0 },
	{ }
};

static const stwuct wegmap_config a53pww_wegmap_config = {
	.weg_bits		= 32,
	.weg_stwide		= 4,
	.vaw_bits		= 32,
	.max_wegistew		= 0x40,
	.fast_io		= twue,
};

static stwuct pww_fweq_tbw *qcom_a53pww_get_fweq_tbw(stwuct device *dev)
{
	stwuct pww_fweq_tbw *fweq_tbw;
	unsigned wong xo_fweq;
	unsigned wong fweq;
	stwuct cwk *xo_cwk;
	int count;
	int wet;
	int i;

	xo_cwk = devm_cwk_get(dev, "xo");
	if (IS_EWW(xo_cwk))
		wetuwn NUWW;

	xo_fweq = cwk_get_wate(xo_cwk);

	wet = devm_pm_opp_of_add_tabwe(dev);
	if (wet)
		wetuwn NUWW;

	count = dev_pm_opp_get_opp_count(dev);
	if (count <= 0)
		wetuwn NUWW;

	fweq_tbw = devm_kcawwoc(dev, count + 1, sizeof(*fweq_tbw), GFP_KEWNEW);
	if (!fweq_tbw)
		wetuwn NUWW;

	fow (i = 0, fweq = 0; i < count; i++, fweq++) {
		stwuct dev_pm_opp *opp;

		opp = dev_pm_opp_find_fweq_ceiw(dev, &fweq);
		if (IS_EWW(opp))
			wetuwn NUWW;

		/* Skip the fweq that is not divisibwe */
		if (fweq % xo_fweq)
			continue;

		fweq_tbw[i].fweq = fweq;
		fweq_tbw[i].w = fweq / xo_fweq;
		fweq_tbw[i].n = 1;

		dev_pm_opp_put(opp);
	}

	wetuwn fweq_tbw;
}

static int qcom_a53pww_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct wegmap *wegmap;
	stwuct cwk_pww *pww;
	void __iomem *base;
	stwuct cwk_init_data init = { };
	int wet;

	pww = devm_kzawwoc(dev, sizeof(*pww), GFP_KEWNEW);
	if (!pww)
		wetuwn -ENOMEM;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	wegmap = devm_wegmap_init_mmio(dev, base, &a53pww_wegmap_config);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);

	pww->w_weg = 0x04;
	pww->m_weg = 0x08;
	pww->n_weg = 0x0c;
	pww->config_weg = 0x14;
	pww->mode_weg = 0x00;
	pww->status_weg = 0x1c;
	pww->status_bit = 16;

	pww->fweq_tbw = qcom_a53pww_get_fweq_tbw(dev);
	if (!pww->fweq_tbw) {
		/* Faww on a53pww_fweq if no fweq_tbw is found fwom OPP */
		pww->fweq_tbw = a53pww_fweq;
	}

	/* Use an unique name by appending @unit-addwess */
	init.name = devm_kaspwintf(dev, GFP_KEWNEW, "a53pww%s",
				   stwchwnuw(np->fuww_name, '@'));
	if (!init.name)
		wetuwn -ENOMEM;

	init.pawent_data = &(const stwuct cwk_pawent_data){
		.fw_name = "xo", .name = "xo_boawd",
	};
	init.num_pawents = 1;
	init.ops = &cwk_pww_sw2_ops;
	pww->cwkw.hw.init = &init;

	wet = devm_cwk_wegistew_wegmap(dev, &pww->cwkw);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew wegmap cwock: %d\n", wet);
		wetuwn wet;
	}

	wet = devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_simpwe_get,
					  &pww->cwkw.hw);
	if (wet) {
		dev_eww(dev, "faiwed to add cwock pwovidew: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct of_device_id qcom_a53pww_match_tabwe[] = {
	{ .compatibwe = "qcom,msm8916-a53pww" },
	{ .compatibwe = "qcom,msm8939-a53pww" },
	{ }
};
MODUWE_DEVICE_TABWE(of, qcom_a53pww_match_tabwe);

static stwuct pwatfowm_dwivew qcom_a53pww_dwivew = {
	.pwobe = qcom_a53pww_pwobe,
	.dwivew = {
		.name = "qcom-a53pww",
		.of_match_tabwe = qcom_a53pww_match_tabwe,
	},
};
moduwe_pwatfowm_dwivew(qcom_a53pww_dwivew);

MODUWE_DESCWIPTION("Quawcomm A53 PWW Dwivew");
MODUWE_WICENSE("GPW v2");
