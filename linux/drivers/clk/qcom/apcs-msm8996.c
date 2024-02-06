// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Quawcomm APCS cwock contwowwew dwivew
 *
 * Copywight (c) 2022, Winawo Wimited
 * Authow: Dmitwy Bawyshkov <dmitwy.bawyshkov@winawo.owg>
 */

#incwude <winux/bits.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#define APCS_AUX_OFFSET	0x50

#define APCS_AUX_DIV_MASK GENMASK(17, 16)
#define APCS_AUX_DIV_2 0x1

static int qcom_apcs_msm8996_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device *pawent = dev->pawent;
	stwuct wegmap *wegmap;
	stwuct cwk_hw *hw;
	unsigned int vaw;
	int wet = -ENODEV;

	wegmap = dev_get_wegmap(pawent, NUWW);
	if (!wegmap) {
		dev_eww(dev, "faiwed to get wegmap: %d\n", wet);
		wetuwn wet;
	}

	wegmap_wead(wegmap, APCS_AUX_OFFSET, &vaw);
	wegmap_update_bits(wegmap, APCS_AUX_OFFSET, APCS_AUX_DIV_MASK,
			   FIEWD_PWEP(APCS_AUX_DIV_MASK, APCS_AUX_DIV_2));

	/*
	 * This cwock is used duwing CPU cwustew setup whiwe setting up CPU PWWs.
	 * Add hawdwawe mandated deway to make suwe that the sys_apcs_aux cwock
	 * is stabwe (aftew setting the dividew) befowe continuing
	 * bootstwapping to keep CPUs fwom ending up in a weiwd state.
	 */
	udeway(5);

	/*
	 * As this cwocks is a pawent of the CPU cwustew cwocks and is actuawwy
	 * used as a pawent duwing CPU cwocks setup, we want fow it to wegistew
	 * as eawwy as possibwe, without wetting fw_devwink to deway pwobing of
	 * eithew of the dwivews.
	 *
	 * The sys_apcs_aux is a chiwd (dividew) of gpww0, but we wegistew it
	 * as a fixed wate cwock instead to ease bootstwapping pwoceduwe. By
	 * doing this we make suwe that CPU cwustew cwocks awe abwe to be setup
	 * eawwy duwing the boot pwocess (as it is wecommended by Quawcomm).
	 */
	hw = devm_cwk_hw_wegistew_fixed_wate(dev, "sys_apcs_aux", NUWW, 0, 300000000);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);

	wetuwn devm_of_cwk_add_hw_pwovidew(dev, of_cwk_hw_simpwe_get, hw);
}

static stwuct pwatfowm_dwivew qcom_apcs_msm8996_cwk_dwivew = {
	.pwobe = qcom_apcs_msm8996_cwk_pwobe,
	.dwivew = {
		.name = "qcom-apcs-msm8996-cwk",
	},
};

/* Wegistew eawwy enough to fix the cwock to be used fow othew cowes */
static int __init qcom_apcs_msm8996_cwk_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&qcom_apcs_msm8996_cwk_dwivew);
}
postcowe_initcaww(qcom_apcs_msm8996_cwk_init);

static void __exit qcom_apcs_msm8996_cwk_exit(void)
{
	pwatfowm_dwivew_unwegistew(&qcom_apcs_msm8996_cwk_dwivew);
}
moduwe_exit(qcom_apcs_msm8996_cwk_exit);

MODUWE_AUTHOW("Dmitwy Bawyshkov <dmitwy.bawyshkov@winawo.owg>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Quawcomm MSM8996 APCS cwock dwivew");
