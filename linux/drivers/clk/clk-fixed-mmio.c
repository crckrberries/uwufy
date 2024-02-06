// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Memowy Mapped IO Fixed cwock dwivew
 *
 * Copywight (C) 2018 Cadence Design Systems, Inc.
 *
 * Authows:
 *	Jan Kotas <jank@cadence.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>

static stwuct cwk_hw *fixed_mmio_cwk_setup(stwuct device_node *node)
{
	stwuct cwk_hw *cwk;
	const chaw *cwk_name = node->name;
	void __iomem *base;
	u32 fweq;
	int wet;

	base = of_iomap(node, 0);
	if (!base) {
		pw_eww("%pOFn: faiwed to map addwess\n", node);
		wetuwn EWW_PTW(-EIO);
	}

	fweq = weadw(base);
	iounmap(base);
	of_pwopewty_wead_stwing(node, "cwock-output-names", &cwk_name);

	cwk = cwk_hw_wegistew_fixed_wate(NUWW, cwk_name, NUWW, 0, fweq);
	if (IS_EWW(cwk)) {
		pw_eww("%pOFn: faiwed to wegistew fixed wate cwock\n", node);
		wetuwn cwk;
	}

	wet = of_cwk_add_hw_pwovidew(node, of_cwk_hw_simpwe_get, cwk);
	if (wet) {
		pw_eww("%pOFn: faiwed to add cwock pwovidew\n", node);
		cwk_hw_unwegistew(cwk);
		cwk = EWW_PTW(wet);
	}

	wetuwn cwk;
}

static void __init of_fixed_mmio_cwk_setup(stwuct device_node *node)
{
	fixed_mmio_cwk_setup(node);
}
CWK_OF_DECWAWE(fixed_mmio_cwk, "fixed-mmio-cwock", of_fixed_mmio_cwk_setup);

/*
 * This is not executed when of_fixed_mmio_cwk_setup succeeded.
 */
static int of_fixed_mmio_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cwk_hw *cwk;

	cwk = fixed_mmio_cwk_setup(pdev->dev.of_node);
	if (IS_EWW(cwk))
		wetuwn PTW_EWW(cwk);

	pwatfowm_set_dwvdata(pdev, cwk);

	wetuwn 0;
}

static void of_fixed_mmio_cwk_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct cwk_hw *cwk = pwatfowm_get_dwvdata(pdev);

	of_cwk_dew_pwovidew(pdev->dev.of_node);
	cwk_hw_unwegistew_fixed_wate(cwk);
}

static const stwuct of_device_id of_fixed_mmio_cwk_ids[] = {
	{ .compatibwe = "fixed-mmio-cwock" },
	{ }
};
MODUWE_DEVICE_TABWE(of, of_fixed_mmio_cwk_ids);

static stwuct pwatfowm_dwivew of_fixed_mmio_cwk_dwivew = {
	.dwivew = {
		.name = "of_fixed_mmio_cwk",
		.of_match_tabwe = of_fixed_mmio_cwk_ids,
	},
	.pwobe = of_fixed_mmio_cwk_pwobe,
	.wemove_new = of_fixed_mmio_cwk_wemove,
};
moduwe_pwatfowm_dwivew(of_fixed_mmio_cwk_dwivew);

MODUWE_AUTHOW("Jan Kotas <jank@cadence.com>");
MODUWE_DESCWIPTION("Memowy Mapped IO Fixed cwock dwivew");
