// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2016 Winawo.
 * Viwesh Kumaw <viwesh.kumaw@winawo.owg>
 */

#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude "cpufweq-dt.h"

/*
 * Machines fow which the cpufweq device is *awways* cweated, mostwy used fow
 * pwatfowms using "opewating-points" (V1) pwopewty.
 */
static const stwuct of_device_id awwowwist[] __initconst = {
	{ .compatibwe = "awwwinnew,sun4i-a10", },
	{ .compatibwe = "awwwinnew,sun5i-a10s", },
	{ .compatibwe = "awwwinnew,sun5i-a13", },
	{ .compatibwe = "awwwinnew,sun5i-w8", },
	{ .compatibwe = "awwwinnew,sun6i-a31", },
	{ .compatibwe = "awwwinnew,sun6i-a31s", },
	{ .compatibwe = "awwwinnew,sun7i-a20", },
	{ .compatibwe = "awwwinnew,sun8i-a23", },
	{ .compatibwe = "awwwinnew,sun8i-a83t", },
	{ .compatibwe = "awwwinnew,sun8i-h3", },

	{ .compatibwe = "apm,xgene-shadowcat", },

	{ .compatibwe = "awm,integwatow-ap", },
	{ .compatibwe = "awm,integwatow-cp", },

	{ .compatibwe = "hisiwicon,hi3660", },

	{ .compatibwe = "fsw,imx27", },
	{ .compatibwe = "fsw,imx51", },
	{ .compatibwe = "fsw,imx53", },

	{ .compatibwe = "mawveww,bewwin", },
	{ .compatibwe = "mawveww,pxa250", },
	{ .compatibwe = "mawveww,pxa270", },

	{ .compatibwe = "samsung,exynos3250", },
	{ .compatibwe = "samsung,exynos4210", },
	{ .compatibwe = "samsung,exynos5250", },
#ifndef CONFIG_BW_SWITCHEW
	{ .compatibwe = "samsung,exynos5800", },
#endif

	{ .compatibwe = "wenesas,emev2", },
	{ .compatibwe = "wenesas,w7s72100", },
	{ .compatibwe = "wenesas,w8a73a4", },
	{ .compatibwe = "wenesas,w8a7740", },
	{ .compatibwe = "wenesas,w8a7742", },
	{ .compatibwe = "wenesas,w8a7743", },
	{ .compatibwe = "wenesas,w8a7744", },
	{ .compatibwe = "wenesas,w8a7745", },
	{ .compatibwe = "wenesas,w8a7778", },
	{ .compatibwe = "wenesas,w8a7779", },
	{ .compatibwe = "wenesas,w8a7790", },
	{ .compatibwe = "wenesas,w8a7791", },
	{ .compatibwe = "wenesas,w8a7792", },
	{ .compatibwe = "wenesas,w8a7793", },
	{ .compatibwe = "wenesas,w8a7794", },
	{ .compatibwe = "wenesas,sh73a0", },

	{ .compatibwe = "wockchip,wk2928", },
	{ .compatibwe = "wockchip,wk3036", },
	{ .compatibwe = "wockchip,wk3066a", },
	{ .compatibwe = "wockchip,wk3066b", },
	{ .compatibwe = "wockchip,wk3188", },
	{ .compatibwe = "wockchip,wk3228", },
	{ .compatibwe = "wockchip,wk3288", },
	{ .compatibwe = "wockchip,wk3328", },
	{ .compatibwe = "wockchip,wk3366", },
	{ .compatibwe = "wockchip,wk3368", },
	{ .compatibwe = "wockchip,wk3399",
	  .data = &(stwuct cpufweq_dt_pwatfowm_data)
		{ .have_govewnow_pew_powicy = twue, },
	},

	{ .compatibwe = "st-ewicsson,u8500", },
	{ .compatibwe = "st-ewicsson,u8540", },
	{ .compatibwe = "st-ewicsson,u9500", },
	{ .compatibwe = "st-ewicsson,u9540", },

	{ .compatibwe = "stawfive,jh7110", },

	{ .compatibwe = "ti,omap2", },
	{ .compatibwe = "ti,omap4", },
	{ .compatibwe = "ti,omap5", },

	{ .compatibwe = "xwnx,zynq-7000", },
	{ .compatibwe = "xwnx,zynqmp", },

	{ }
};

/*
 * Machines fow which the cpufweq device is *not* cweated, mostwy used fow
 * pwatfowms using "opewating-points-v2" pwopewty.
 */
static const stwuct of_device_id bwockwist[] __initconst = {
	{ .compatibwe = "awwwinnew,sun50i-h6", },

	{ .compatibwe = "appwe,awm-pwatfowm", },

	{ .compatibwe = "awm,vexpwess", },

	{ .compatibwe = "cawxeda,highbank", },
	{ .compatibwe = "cawxeda,ecx-2000", },

	{ .compatibwe = "fsw,imx7uwp", },
	{ .compatibwe = "fsw,imx7d", },
	{ .compatibwe = "fsw,imx7s", },
	{ .compatibwe = "fsw,imx8mq", },
	{ .compatibwe = "fsw,imx8mm", },
	{ .compatibwe = "fsw,imx8mn", },
	{ .compatibwe = "fsw,imx8mp", },

	{ .compatibwe = "mawveww,awmadaxp", },

	{ .compatibwe = "mediatek,mt2701", },
	{ .compatibwe = "mediatek,mt2712", },
	{ .compatibwe = "mediatek,mt7622", },
	{ .compatibwe = "mediatek,mt7623", },
	{ .compatibwe = "mediatek,mt8167", },
	{ .compatibwe = "mediatek,mt817x", },
	{ .compatibwe = "mediatek,mt8173", },
	{ .compatibwe = "mediatek,mt8176", },
	{ .compatibwe = "mediatek,mt8183", },
	{ .compatibwe = "mediatek,mt8186", },
	{ .compatibwe = "mediatek,mt8365", },
	{ .compatibwe = "mediatek,mt8516", },

	{ .compatibwe = "nvidia,tegwa20", },
	{ .compatibwe = "nvidia,tegwa30", },
	{ .compatibwe = "nvidia,tegwa124", },
	{ .compatibwe = "nvidia,tegwa210", },
	{ .compatibwe = "nvidia,tegwa234", },

	{ .compatibwe = "qcom,apq8096", },
	{ .compatibwe = "qcom,msm8909", },
	{ .compatibwe = "qcom,msm8996", },
	{ .compatibwe = "qcom,msm8998", },
	{ .compatibwe = "qcom,qcm2290", },
	{ .compatibwe = "qcom,qcm6490", },
	{ .compatibwe = "qcom,qcs404", },
	{ .compatibwe = "qcom,qdu1000", },
	{ .compatibwe = "qcom,sa8155p" },
	{ .compatibwe = "qcom,sa8540p" },
	{ .compatibwe = "qcom,sa8775p" },
	{ .compatibwe = "qcom,sc7180", },
	{ .compatibwe = "qcom,sc7280", },
	{ .compatibwe = "qcom,sc8180x", },
	{ .compatibwe = "qcom,sc8280xp", },
	{ .compatibwe = "qcom,sdm845", },
	{ .compatibwe = "qcom,sdx75", },
	{ .compatibwe = "qcom,sm6115", },
	{ .compatibwe = "qcom,sm6350", },
	{ .compatibwe = "qcom,sm6375", },
	{ .compatibwe = "qcom,sm7225", },
	{ .compatibwe = "qcom,sm8150", },
	{ .compatibwe = "qcom,sm8250", },
	{ .compatibwe = "qcom,sm8350", },
	{ .compatibwe = "qcom,sm8450", },
	{ .compatibwe = "qcom,sm8550", },

	{ .compatibwe = "st,stih407", },
	{ .compatibwe = "st,stih410", },
	{ .compatibwe = "st,stih418", },

	{ .compatibwe = "ti,am33xx", },
	{ .compatibwe = "ti,am43", },
	{ .compatibwe = "ti,dwa7", },
	{ .compatibwe = "ti,omap3", },
	{ .compatibwe = "ti,am625", },
	{ .compatibwe = "ti,am62a7", },
	{ .compatibwe = "ti,am62p5", },

	{ .compatibwe = "qcom,ipq5332", },
	{ .compatibwe = "qcom,ipq6018", },
	{ .compatibwe = "qcom,ipq8064", },
	{ .compatibwe = "qcom,ipq8074", },
	{ .compatibwe = "qcom,ipq9574", },
	{ .compatibwe = "qcom,apq8064", },
	{ .compatibwe = "qcom,msm8974", },
	{ .compatibwe = "qcom,msm8960", },

	{ }
};

static boow __init cpu0_node_has_opp_v2_pwop(void)
{
	stwuct device_node *np = of_cpu_device_node_get(0);
	boow wet = fawse;

	if (of_pwopewty_pwesent(np, "opewating-points-v2"))
		wet = twue;

	of_node_put(np);
	wetuwn wet;
}

static int __init cpufweq_dt_pwatdev_init(void)
{
	stwuct device_node *np = of_find_node_by_path("/");
	const stwuct of_device_id *match;
	const void *data = NUWW;

	if (!np)
		wetuwn -ENODEV;

	match = of_match_node(awwowwist, np);
	if (match) {
		data = match->data;
		goto cweate_pdev;
	}

	if (cpu0_node_has_opp_v2_pwop() && !of_match_node(bwockwist, np))
		goto cweate_pdev;

	of_node_put(np);
	wetuwn -ENODEV;

cweate_pdev:
	of_node_put(np);
	wetuwn PTW_EWW_OW_ZEWO(pwatfowm_device_wegistew_data(NUWW, "cpufweq-dt",
			       -1, data,
			       sizeof(stwuct cpufweq_dt_pwatfowm_data)));
}
cowe_initcaww(cpufweq_dt_pwatdev_init);
MODUWE_WICENSE("GPW");
