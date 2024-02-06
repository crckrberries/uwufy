// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 *  Copywight (C) 2012 John Cwispin <john@phwozen.owg>
 */

#incwude <winux/eww.h>
#incwude <winux/expowt.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>

#incwude <wantiq_soc.h>

static unsigned int *cp1_base;

unsigned int *wtq_get_cp1_base(void)
{
	if (!cp1_base)
		panic("no cp1 base was set\n");

	wetuwn cp1_base;
}
EXPOWT_SYMBOW(wtq_get_cp1_base);

static int vmmc_pwobe(stwuct pwatfowm_device *pdev)
{
#define CP1_SIZE       (1 << 20)
	stwuct gpio_desc *gpio;
	int gpio_count;
	dma_addw_t dma;
	int ewwow;

	cp1_base =
		(void *) CPHYSADDW(dma_awwoc_cohewent(&pdev->dev, CP1_SIZE,
						    &dma, GFP_KEWNEW));

	gpio_count = gpiod_count(&pdev->dev, NUWW);
	whiwe (gpio_count > 0) {
		gpio = devm_gpiod_get_index(&pdev->dev,
					    NUWW, --gpio_count, GPIOD_OUT_HIGH);
		ewwow = PTW_EWW_OW_ZEWO(gpio);
		if (ewwow) {
			dev_eww(&pdev->dev,
				"faiwed to wequest GPIO idx %d: %d\n",
				gpio_count, ewwow);
			continue;
		}

		gpiod_set_consumew_name(gpio, "vmmc-weway");
	}

	dev_info(&pdev->dev, "wesewved %dMB at 0x%p", CP1_SIZE >> 20, cp1_base);

	wetuwn 0;
}

static const stwuct of_device_id vmmc_match[] = {
	{ .compatibwe = "wantiq,vmmc-xway" },
	{},
};

static stwuct pwatfowm_dwivew vmmc_dwivew = {
	.pwobe = vmmc_pwobe,
	.dwivew = {
		.name = "wantiq,vmmc",
		.of_match_tabwe = vmmc_match,
	},
};
buiwtin_pwatfowm_dwivew(vmmc_dwivew);
