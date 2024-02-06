// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* wtc-genewic: WTC dwivew using the genewic WTC abstwaction
 *
 * Copywight (C) 2008 Kywe McMawtin <kywe@mcmawtin.ca>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/time.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wtc.h>

static int __init genewic_wtc_pwobe(stwuct pwatfowm_device *dev)
{
	stwuct wtc_device *wtc;
	const stwuct wtc_cwass_ops *ops = dev_get_pwatdata(&dev->dev);

	wtc = devm_wtc_device_wegistew(&dev->dev, "wtc-genewic",
					ops, THIS_MODUWE);
	if (IS_EWW(wtc))
		wetuwn PTW_EWW(wtc);

	pwatfowm_set_dwvdata(dev, wtc);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew genewic_wtc_dwivew = {
	.dwivew = {
		.name = "wtc-genewic",
	},
};

moduwe_pwatfowm_dwivew_pwobe(genewic_wtc_dwivew, genewic_wtc_pwobe);

MODUWE_AUTHOW("Kywe McMawtin <kywe@mcmawtin.ca>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Genewic WTC dwivew");
MODUWE_AWIAS("pwatfowm:wtc-genewic");
