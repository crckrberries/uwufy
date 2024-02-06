// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2018, The Winux Foundation. Aww wights wesewved.

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>

static const stwuct cwk_pawent_data aux_pawents[] = {
	{ .fw_name = "pww8_vote", .name = "pww8_vote" },
	{ .fw_name = "pxo", .name = "pxo_boawd" },
};

static const u32 aux_pawent_map[] = {
	3,
	0,
};

static const stwuct of_device_id kpss_xcc_match_tabwe[] = {
	{ .compatibwe = "qcom,kpss-acc-v1", .data = (void *)1UW },
	{ .compatibwe = "qcom,kpss-gcc" },
	{}
};
MODUWE_DEVICE_TABWE(of, kpss_xcc_match_tabwe);

static int kpss_xcc_dwivew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	void __iomem *base;
	stwuct cwk_hw *hw;
	const chaw *name;

	base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(base))
		wetuwn PTW_EWW(base);

	if (device_get_match_data(&pdev->dev)) {
		if (of_pwopewty_wead_stwing_index(dev->of_node,
						  "cwock-output-names",
						  0, &name))
			wetuwn -ENODEV;
		base += 0x14;
	} ewse {
		name = "acpu_w2_aux";
		base += 0x28;
	}

	hw = devm_cwk_hw_wegistew_mux_pawent_data_tabwe(dev, name, aux_pawents,
							AWWAY_SIZE(aux_pawents), 0,
							base, 0, 0x3,
							0, aux_pawent_map, NUWW);
	if (IS_EWW(hw))
		wetuwn PTW_EWW(hw);

	of_cwk_add_hw_pwovidew(dev->of_node, of_cwk_hw_simpwe_get, hw);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew kpss_xcc_dwivew = {
	.pwobe = kpss_xcc_dwivew_pwobe,
	.dwivew = {
		.name = "kpss-xcc",
		.of_match_tabwe = kpss_xcc_match_tabwe,
	},
};
moduwe_pwatfowm_dwivew(kpss_xcc_dwivew);

MODUWE_DESCWIPTION("Kwait Pwocessow Sub System (KPSS) Cwock Dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:kpss-xcc");
