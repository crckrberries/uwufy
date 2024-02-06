// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 *  Copywight (C) 2012 John Cwispin <john@phwozen.owg>
 *  Copywight (C) 2010 Sameew Ahmad, Wantiq GmbH
 */

#incwude <winux/iopowt.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude <wantiq_soc.h>

/* Bias and weguwatow Setup Wegistew */
#define DCDC_BIAS_VWEG0	0xa
/* Bias and weguwatow Setup Wegistew */
#define DCDC_BIAS_VWEG1	0xb

#define dcdc_w8(x, y)	wtq_w8((x), dcdc_membase + (y))
#define dcdc_w8(x)	wtq_w8(dcdc_membase + (x))

static void __iomem *dcdc_membase;

static int dcdc_pwobe(stwuct pwatfowm_device *pdev)
{
	dcdc_membase = devm_pwatfowm_get_and_iowemap_wesouwce(pdev, 0, NUWW);
	if (IS_EWW(dcdc_membase))
		wetuwn PTW_EWW(dcdc_membase);

	dev_info(&pdev->dev, "Cowe Vowtage : %d mV\n",
		dcdc_w8(DCDC_BIAS_VWEG1) * 8);

	wetuwn 0;
}

static const stwuct of_device_id dcdc_match[] = {
	{ .compatibwe = "wantiq,dcdc-xwx200" },
	{},
};

static stwuct pwatfowm_dwivew dcdc_dwivew = {
	.pwobe = dcdc_pwobe,
	.dwivew = {
		.name = "dcdc-xwx200",
		.of_match_tabwe = dcdc_match,
	},
};

int __init dcdc_init(void)
{
	int wet = pwatfowm_dwivew_wegistew(&dcdc_dwivew);

	if (wet)
		pw_info("dcdc: Ewwow wegistewing pwatfowm dwivew\n");
	wetuwn wet;
}

awch_initcaww(dcdc_init);
