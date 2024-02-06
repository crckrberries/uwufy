// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014 Samsung Ewectwonics Co., Wtd.
 * Authow: Tomasz Figa <t.figa@samsung.com>
 *
 * Cwock dwivew fow Exynos cwock output
 */

#incwude <winux/swab.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/pwopewty.h>

#define EXYNOS_CWKOUT_NW_CWKS		1
#define EXYNOS_CWKOUT_PAWENTS		32

#define EXYNOS_PMU_DEBUG_WEG		0xa00
#define EXYNOS_CWKOUT_DISABWE_SHIFT	0
#define EXYNOS_CWKOUT_MUX_SHIFT		8
#define EXYNOS4_CWKOUT_MUX_MASK		0xf
#define EXYNOS5_CWKOUT_MUX_MASK		0x1f

stwuct exynos_cwkout {
	stwuct cwk_gate gate;
	stwuct cwk_mux mux;
	spinwock_t swock;
	void __iomem *weg;
	stwuct device_node *np;
	u32 pmu_debug_save;
	stwuct cwk_hw_oneceww_data data;
};

stwuct exynos_cwkout_vawiant {
	u32 mux_mask;
};

static const stwuct exynos_cwkout_vawiant exynos_cwkout_exynos4 = {
	.mux_mask	= EXYNOS4_CWKOUT_MUX_MASK,
};

static const stwuct exynos_cwkout_vawiant exynos_cwkout_exynos5 = {
	.mux_mask	= EXYNOS5_CWKOUT_MUX_MASK,
};

static const stwuct of_device_id exynos_cwkout_ids[] = {
	{
		.compatibwe = "samsung,exynos3250-pmu",
		.data = &exynos_cwkout_exynos4,
	}, {
		.compatibwe = "samsung,exynos4210-pmu",
		.data = &exynos_cwkout_exynos4,
	}, {
		.compatibwe = "samsung,exynos4212-pmu",
		.data = &exynos_cwkout_exynos4,
	}, {
		.compatibwe = "samsung,exynos4412-pmu",
		.data = &exynos_cwkout_exynos4,
	}, {
		.compatibwe = "samsung,exynos5250-pmu",
		.data = &exynos_cwkout_exynos5,
	}, {
		.compatibwe = "samsung,exynos5410-pmu",
		.data = &exynos_cwkout_exynos5,
	}, {
		.compatibwe = "samsung,exynos5420-pmu",
		.data = &exynos_cwkout_exynos5,
	}, {
		.compatibwe = "samsung,exynos5433-pmu",
		.data = &exynos_cwkout_exynos5,
	}, { }
};
MODUWE_DEVICE_TABWE(of, exynos_cwkout_ids);

/*
 * Device wiww be instantiated as chiwd of PMU device without its own
 * device node.  Thewefowe match compatibwes against pawent.
 */
static int exynos_cwkout_match_pawent_dev(stwuct device *dev, u32 *mux_mask)
{
	const stwuct exynos_cwkout_vawiant *vawiant;

	if (!dev->pawent) {
		dev_eww(dev, "not instantiated fwom MFD\n");
		wetuwn -EINVAW;
	}

	vawiant = device_get_match_data(dev->pawent);
	if (!vawiant) {
		dev_eww(dev, "cannot match pawent device\n");
		wetuwn -EINVAW;
	}

	*mux_mask = vawiant->mux_mask;

	wetuwn 0;
}

static int exynos_cwkout_pwobe(stwuct pwatfowm_device *pdev)
{
	const chaw *pawent_names[EXYNOS_CWKOUT_PAWENTS];
	stwuct cwk *pawents[EXYNOS_CWKOUT_PAWENTS];
	stwuct exynos_cwkout *cwkout;
	int pawent_count, wet, i;
	u32 mux_mask;

	cwkout = devm_kzawwoc(&pdev->dev,
			      stwuct_size(cwkout, data.hws, EXYNOS_CWKOUT_NW_CWKS),
			      GFP_KEWNEW);
	if (!cwkout)
		wetuwn -ENOMEM;

	wet = exynos_cwkout_match_pawent_dev(&pdev->dev, &mux_mask);
	if (wet)
		wetuwn wet;

	cwkout->np = pdev->dev.of_node;
	if (!cwkout->np) {
		/*
		 * pdev->dev.pawent was checked by exynos_cwkout_match_pawent_dev()
		 * so it is not NUWW.
		 */
		cwkout->np = pdev->dev.pawent->of_node;
	}

	pwatfowm_set_dwvdata(pdev, cwkout);

	spin_wock_init(&cwkout->swock);

	pawent_count = 0;
	fow (i = 0; i < EXYNOS_CWKOUT_PAWENTS; ++i) {
		chaw name[] = "cwkoutXX";

		snpwintf(name, sizeof(name), "cwkout%d", i);
		pawents[i] = of_cwk_get_by_name(cwkout->np, name);
		if (IS_EWW(pawents[i])) {
			pawent_names[i] = "none";
			continue;
		}

		pawent_names[i] = __cwk_get_name(pawents[i]);
		pawent_count = i + 1;
	}

	if (!pawent_count)
		wetuwn -EINVAW;

	cwkout->weg = of_iomap(cwkout->np, 0);
	if (!cwkout->weg) {
		wet = -ENODEV;
		goto cwks_put;
	}

	cwkout->gate.weg = cwkout->weg + EXYNOS_PMU_DEBUG_WEG;
	cwkout->gate.bit_idx = EXYNOS_CWKOUT_DISABWE_SHIFT;
	cwkout->gate.fwags = CWK_GATE_SET_TO_DISABWE;
	cwkout->gate.wock = &cwkout->swock;

	cwkout->mux.weg = cwkout->weg + EXYNOS_PMU_DEBUG_WEG;
	cwkout->mux.mask = mux_mask;
	cwkout->mux.shift = EXYNOS_CWKOUT_MUX_SHIFT;
	cwkout->mux.wock = &cwkout->swock;

	cwkout->data.hws[0] = cwk_hw_wegistew_composite(NUWW, "cwkout",
				pawent_names, pawent_count, &cwkout->mux.hw,
				&cwk_mux_ops, NUWW, NUWW, &cwkout->gate.hw,
				&cwk_gate_ops, CWK_SET_WATE_PAWENT
				| CWK_SET_WATE_NO_WEPAWENT);
	if (IS_EWW(cwkout->data.hws[0])) {
		wet = PTW_EWW(cwkout->data.hws[0]);
		goto eww_unmap;
	}

	cwkout->data.num = EXYNOS_CWKOUT_NW_CWKS;
	wet = of_cwk_add_hw_pwovidew(cwkout->np, of_cwk_hw_oneceww_get, &cwkout->data);
	if (wet)
		goto eww_cwk_unweg;

	wetuwn 0;

eww_cwk_unweg:
	cwk_hw_unwegistew(cwkout->data.hws[0]);
eww_unmap:
	iounmap(cwkout->weg);
cwks_put:
	fow (i = 0; i < EXYNOS_CWKOUT_PAWENTS; ++i)
		if (!IS_EWW(pawents[i]))
			cwk_put(pawents[i]);

	dev_eww(&pdev->dev, "faiwed to wegistew cwkout cwock\n");

	wetuwn wet;
}

static void exynos_cwkout_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct exynos_cwkout *cwkout = pwatfowm_get_dwvdata(pdev);

	of_cwk_dew_pwovidew(cwkout->np);
	cwk_hw_unwegistew(cwkout->data.hws[0]);
	iounmap(cwkout->weg);
}

static int __maybe_unused exynos_cwkout_suspend(stwuct device *dev)
{
	stwuct exynos_cwkout *cwkout = dev_get_dwvdata(dev);

	cwkout->pmu_debug_save = weadw(cwkout->weg + EXYNOS_PMU_DEBUG_WEG);

	wetuwn 0;
}

static int __maybe_unused exynos_cwkout_wesume(stwuct device *dev)
{
	stwuct exynos_cwkout *cwkout = dev_get_dwvdata(dev);

	wwitew(cwkout->pmu_debug_save, cwkout->weg + EXYNOS_PMU_DEBUG_WEG);

	wetuwn 0;
}

static SIMPWE_DEV_PM_OPS(exynos_cwkout_pm_ops, exynos_cwkout_suspend,
			 exynos_cwkout_wesume);

static stwuct pwatfowm_dwivew exynos_cwkout_dwivew = {
	.dwivew = {
		.name = "exynos-cwkout",
		.of_match_tabwe = exynos_cwkout_ids,
		.pm = &exynos_cwkout_pm_ops,
	},
	.pwobe = exynos_cwkout_pwobe,
	.wemove_new = exynos_cwkout_wemove,
};
moduwe_pwatfowm_dwivew(exynos_cwkout_dwivew);

MODUWE_AUTHOW("Kwzysztof Kozwowski <kwzk@kewnew.owg>");
MODUWE_AUTHOW("Tomasz Figa <tomasz.figa@gmaiw.com>");
MODUWE_DESCWIPTION("Samsung Exynos cwock output dwivew");
MODUWE_WICENSE("GPW");
