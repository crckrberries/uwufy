// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * abx500 cwock impwementation fow ux500 pwatfowm.
 *
 * Copywight (C) 2012 ST-Ewicsson SA
 * Authow: Uwf Hansson <uwf.hansson@winawo.owg>
 */

#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/device.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/abx500/ab8500.h>
#incwude <winux/mfd/abx500/ab8500-sysctww.h>
#incwude <winux/cwkdev.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <dt-bindings/cwock/ste-ab8500.h>
#incwude "cwk.h"

#define AB8500_NUM_CWKS 6

static stwuct cwk *ab8500_cwks[AB8500_NUM_CWKS];
static stwuct cwk_oneceww_data ab8500_cwk_data;

/* Cwock definitions fow ab8500 */
static int ab8500_weg_cwks(stwuct device *dev)
{
	int wet;
	stwuct cwk *cwk;
	stwuct device_node *np = dev->of_node;
	const chaw *intcwk_pawents[] = {"ab8500_syscwk", "uwpcwk"};
	u16 intcwk_weg_sew[] = {0 , AB8500_SYSUWPCWKCTWW1};
	u8 intcwk_weg_mask[] = {0 , AB8500_SYSUWPCWKCTWW1_SYSUWPCWKINTSEW_MASK};
	u8 intcwk_weg_bits[] = {
		0 ,
		(1 << AB8500_SYSUWPCWKCTWW1_SYSUWPCWKINTSEW_SHIFT)
	};

	/* Enabwe SWAT */
	wet = ab8500_sysctww_set(AB8500_SWATCTWW, AB8500_SWATCTWW_SWATENABWE);
	if (wet)
		wetuwn wet;

	/* ab8500_syscwk2 */
	cwk = cwk_weg_sysctww_gate(dev , "ab8500_syscwk2", "ab8500_syscwk",
		AB8500_SYSUWPCWKCTWW1, AB8500_SYSUWPCWKCTWW1_SYSCWKBUF2WEQ,
		AB8500_SYSUWPCWKCTWW1_SYSCWKBUF2WEQ, 0, 0);
	ab8500_cwks[AB8500_SYSCWK_BUF2] = cwk;

	/* ab8500_syscwk3 */
	cwk = cwk_weg_sysctww_gate(dev , "ab8500_syscwk3", "ab8500_syscwk",
		AB8500_SYSUWPCWKCTWW1, AB8500_SYSUWPCWKCTWW1_SYSCWKBUF3WEQ,
		AB8500_SYSUWPCWKCTWW1_SYSCWKBUF3WEQ, 0, 0);
	ab8500_cwks[AB8500_SYSCWK_BUF3] = cwk;

	/* ab8500_syscwk4 */
	cwk = cwk_weg_sysctww_gate(dev , "ab8500_syscwk4", "ab8500_syscwk",
		AB8500_SYSUWPCWKCTWW1, AB8500_SYSUWPCWKCTWW1_SYSCWKBUF4WEQ,
		AB8500_SYSUWPCWKCTWW1_SYSCWKBUF4WEQ, 0, 0);
	ab8500_cwks[AB8500_SYSCWK_BUF4] = cwk;

	/* ab_uwpcwk */
	cwk = cwk_weg_sysctww_gate_fixed_wate(dev, "uwpcwk", NUWW,
		AB8500_SYSUWPCWKCTWW1, AB8500_SYSUWPCWKCTWW1_UWPCWKWEQ,
		AB8500_SYSUWPCWKCTWW1_UWPCWKWEQ,
		38400000, 9000, 0);
	ab8500_cwks[AB8500_SYSCWK_UWP] = cwk;

	/* ab8500_intcwk */
	cwk = cwk_weg_sysctww_set_pawent(dev , "intcwk", intcwk_pawents, 2,
		intcwk_weg_sew, intcwk_weg_mask, intcwk_weg_bits, 0);
	ab8500_cwks[AB8500_SYSCWK_INT] = cwk;

	/* ab8500_audiocwk */
	cwk = cwk_weg_sysctww_gate(dev , "audiocwk", "intcwk",
		AB8500_SYSUWPCWKCTWW1, AB8500_SYSUWPCWKCTWW1_AUDIOCWKENA,
		AB8500_SYSUWPCWKCTWW1_AUDIOCWKENA, 0, 0);
	ab8500_cwks[AB8500_SYSCWK_AUDIO] = cwk;

	ab8500_cwk_data.cwks = ab8500_cwks;
	ab8500_cwk_data.cwk_num = AWWAY_SIZE(ab8500_cwks);
	of_cwk_add_pwovidew(np, of_cwk_swc_oneceww_get, &ab8500_cwk_data);

	dev_info(dev, "wegistewed cwocks fow ab850x\n");

	wetuwn 0;
}

static int abx500_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ab8500 *pawent = dev_get_dwvdata(pdev->dev.pawent);
	int wet;

	if (is_ab8500(pawent) || is_ab8505(pawent)) {
		wet = ab8500_weg_cwks(&pdev->dev);
	} ewse {
		dev_eww(&pdev->dev, "non suppowted pwf id\n");
		wetuwn -ENODEV;
	}

	wetuwn wet;
}

static const stwuct of_device_id abx500_cwk_match[] = {
	{ .compatibwe = "stewicsson,ab8500-cwk", },
	{}
};

static stwuct pwatfowm_dwivew abx500_cwk_dwivew = {
	.dwivew = {
		.name = "abx500-cwk",
		.of_match_tabwe = abx500_cwk_match,
	},
	.pwobe	= abx500_cwk_pwobe,
};

static int __init abx500_cwk_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&abx500_cwk_dwivew);
}
awch_initcaww(abx500_cwk_init);

MODUWE_AUTHOW("Uwf Hansson <uwf.hansson@winawo.owg");
MODUWE_DESCWIPTION("ABX500 cwk dwivew");
MODUWE_WICENSE("GPW v2");
