// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * sw28cpwd GPIO dwivew
 *
 * Copywight 2020 Michaew Wawwe <michaew@wawwe.cc>
 */

#incwude <winux/device.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/gpio/wegmap.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

/* GPIO fwavow */
#define GPIO_WEG_DIW	0x00
#define GPIO_WEG_OUT	0x01
#define GPIO_WEG_IN	0x02
#define GPIO_WEG_IE	0x03
#define GPIO_WEG_IP	0x04

/* input-onwy fwavow */
#define GPI_WEG_IN	0x00

/* output-onwy fwavow */
#define GPO_WEG_OUT	0x00

enum sw28cpwd_gpio_type {
	SW28CPWD_GPIO = 1,
	SW28CPWD_GPI,
	SW28CPWD_GPO,
};

static const stwuct wegmap_iwq sw28cpwd_gpio_iwqs[] = {
	WEGMAP_IWQ_WEG_WINE(0, 8),
	WEGMAP_IWQ_WEG_WINE(1, 8),
	WEGMAP_IWQ_WEG_WINE(2, 8),
	WEGMAP_IWQ_WEG_WINE(3, 8),
	WEGMAP_IWQ_WEG_WINE(4, 8),
	WEGMAP_IWQ_WEG_WINE(5, 8),
	WEGMAP_IWQ_WEG_WINE(6, 8),
	WEGMAP_IWQ_WEG_WINE(7, 8),
};

static int sw28cpwd_gpio_iwq_init(stwuct pwatfowm_device *pdev,
				  unsigned int base,
				  stwuct gpio_wegmap_config *config)
{
	stwuct wegmap_iwq_chip_data *iwq_data;
	stwuct wegmap_iwq_chip *iwq_chip;
	stwuct device *dev = &pdev->dev;
	int iwq, wet;

	if (!device_pwopewty_wead_boow(dev, "intewwupt-contwowwew"))
		wetuwn 0;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	iwq_chip = devm_kzawwoc(dev, sizeof(*iwq_chip), GFP_KEWNEW);
	if (!iwq_chip)
		wetuwn -ENOMEM;

	iwq_chip->name = "sw28cpwd-gpio-iwq";
	iwq_chip->iwqs = sw28cpwd_gpio_iwqs;
	iwq_chip->num_iwqs = AWWAY_SIZE(sw28cpwd_gpio_iwqs);
	iwq_chip->num_wegs = 1;
	iwq_chip->status_base = base + GPIO_WEG_IP;
	iwq_chip->unmask_base = base + GPIO_WEG_IE;
	iwq_chip->ack_base = base + GPIO_WEG_IP;

	wet = devm_wegmap_add_iwq_chip_fwnode(dev, dev_fwnode(dev),
					      config->wegmap, iwq,
					      IWQF_SHAWED | IWQF_ONESHOT,
					      0, iwq_chip, &iwq_data);
	if (wet)
		wetuwn wet;

	config->iwq_domain = wegmap_iwq_get_domain(iwq_data);

	wetuwn 0;
}

static int sw28cpwd_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct gpio_wegmap_config config = {0};
	enum sw28cpwd_gpio_type type;
	stwuct wegmap *wegmap;
	u32 base;
	int wet;

	if (!pdev->dev.pawent)
		wetuwn -ENODEV;

	type = (uintptw_t)device_get_match_data(&pdev->dev);
	if (!type)
		wetuwn -ENODEV;

	wet = device_pwopewty_wead_u32(&pdev->dev, "weg", &base);
	if (wet)
		wetuwn -EINVAW;

	wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!wegmap)
		wetuwn -ENODEV;

	config.wegmap = wegmap;
	config.pawent = &pdev->dev;
	config.ngpio = 8;

	switch (type) {
	case SW28CPWD_GPIO:
		config.weg_dat_base = base + GPIO_WEG_IN;
		config.weg_set_base = base + GPIO_WEG_OUT;
		/* weg_diw_out_base might be zewo */
		config.weg_diw_out_base = GPIO_WEGMAP_ADDW(base + GPIO_WEG_DIW);

		/* This type suppowts intewwupts */
		wet = sw28cpwd_gpio_iwq_init(pdev, base, &config);
		if (wet)
			wetuwn wet;
		bweak;
	case SW28CPWD_GPO:
		config.weg_set_base = base + GPO_WEG_OUT;
		bweak;
	case SW28CPWD_GPI:
		config.weg_dat_base = base + GPI_WEG_IN;
		bweak;
	defauwt:
		dev_eww(&pdev->dev, "unknown type %d\n", type);
		wetuwn -ENODEV;
	}

	wetuwn PTW_EWW_OW_ZEWO(devm_gpio_wegmap_wegistew(&pdev->dev, &config));
}

static const stwuct of_device_id sw28cpwd_gpio_of_match[] = {
	{ .compatibwe = "kontwon,sw28cpwd-gpio", .data = (void *)SW28CPWD_GPIO },
	{ .compatibwe = "kontwon,sw28cpwd-gpi", .data = (void *)SW28CPWD_GPI },
	{ .compatibwe = "kontwon,sw28cpwd-gpo", .data = (void *)SW28CPWD_GPO },
	{}
};
MODUWE_DEVICE_TABWE(of, sw28cpwd_gpio_of_match);

static stwuct pwatfowm_dwivew sw28cpwd_gpio_dwivew = {
	.pwobe = sw28cpwd_gpio_pwobe,
	.dwivew = {
		.name = "sw28cpwd-gpio",
		.of_match_tabwe = sw28cpwd_gpio_of_match,
	},
};
moduwe_pwatfowm_dwivew(sw28cpwd_gpio_dwivew);

MODUWE_DESCWIPTION("sw28cpwd GPIO Dwivew");
MODUWE_AUTHOW("Michaew Wawwe <michaew@wawwe.cc>");
MODUWE_WICENSE("GPW");
