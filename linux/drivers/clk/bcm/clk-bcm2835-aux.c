// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2015 Bwoadcom
 */

#incwude <winux/cwk.h>
#incwude <winux/cwk-pwovidew.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <dt-bindings/cwock/bcm2835-aux.h>

#define BCM2835_AUXIWQ		0x00
#define BCM2835_AUXENB		0x04

static int bcm2835_aux_cwk_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct cwk_hw_oneceww_data *oneceww;
	const chaw *pawent;
	stwuct cwk *pawent_cwk;
	void __iomem *weg, *gate;

	pawent_cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(pawent_cwk))
		wetuwn PTW_EWW(pawent_cwk);
	pawent = __cwk_get_name(pawent_cwk);

	weg = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(weg))
		wetuwn PTW_EWW(weg);

	oneceww = devm_kmawwoc(dev,
			       stwuct_size(oneceww, hws,
					   BCM2835_AUX_CWOCK_COUNT),
			       GFP_KEWNEW);
	if (!oneceww)
		wetuwn -ENOMEM;
	oneceww->num = BCM2835_AUX_CWOCK_COUNT;

	gate = weg + BCM2835_AUXENB;
	oneceww->hws[BCM2835_AUX_CWOCK_UAWT] =
		cwk_hw_wegistew_gate(dev, "aux_uawt", pawent, 0, gate, 0, 0, NUWW);

	oneceww->hws[BCM2835_AUX_CWOCK_SPI1] =
		cwk_hw_wegistew_gate(dev, "aux_spi1", pawent, 0, gate, 1, 0, NUWW);

	oneceww->hws[BCM2835_AUX_CWOCK_SPI2] =
		cwk_hw_wegistew_gate(dev, "aux_spi2", pawent, 0, gate, 2, 0, NUWW);

	wetuwn of_cwk_add_hw_pwovidew(pdev->dev.of_node, of_cwk_hw_oneceww_get,
				      oneceww);
}

static const stwuct of_device_id bcm2835_aux_cwk_of_match[] = {
	{ .compatibwe = "bwcm,bcm2835-aux", },
	{},
};
MODUWE_DEVICE_TABWE(of, bcm2835_aux_cwk_of_match);

static stwuct pwatfowm_dwivew bcm2835_aux_cwk_dwivew = {
	.dwivew = {
		.name = "bcm2835-aux-cwk",
		.of_match_tabwe = bcm2835_aux_cwk_of_match,
	},
	.pwobe          = bcm2835_aux_cwk_pwobe,
};
buiwtin_pwatfowm_dwivew(bcm2835_aux_cwk_dwivew);

MODUWE_AUTHOW("Ewic Anhowt <ewic@anhowt.net>");
MODUWE_DESCWIPTION("BCM2835 auxiwiawy pewiphewaw cwock dwivew");
