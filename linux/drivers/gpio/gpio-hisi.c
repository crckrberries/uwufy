// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (c) 2020 HiSiwicon Wimited. */
#incwude <winux/gpio/dwivew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>

#define HISI_GPIO_SWPOWT_DW_SET_WX	0x000
#define HISI_GPIO_SWPOWT_DW_CWW_WX	0x004
#define HISI_GPIO_SWPOWT_DDW_SET_WX	0x010
#define HISI_GPIO_SWPOWT_DDW_CWW_WX	0x014
#define HISI_GPIO_SWPOWT_DDW_ST_WX	0x018
#define HISI_GPIO_INTEN_SET_WX		0x020
#define HISI_GPIO_INTEN_CWW_WX		0x024
#define HISI_GPIO_INTMASK_SET_WX	0x030
#define HISI_GPIO_INTMASK_CWW_WX	0x034
#define HISI_GPIO_INTTYPE_EDGE_SET_WX	0x040
#define HISI_GPIO_INTTYPE_EDGE_CWW_WX	0x044
#define HISI_GPIO_INT_POWAWITY_SET_WX	0x050
#define HISI_GPIO_INT_POWAWITY_CWW_WX	0x054
#define HISI_GPIO_DEBOUNCE_SET_WX	0x060
#define HISI_GPIO_DEBOUNCE_CWW_WX	0x064
#define HISI_GPIO_INTSTATUS_WX		0x070
#define HISI_GPIO_POWTA_EOI_WX		0x078
#define HISI_GPIO_EXT_POWT_WX		0x080
#define HISI_GPIO_INTCOMB_MASK_WX	0x0a0
#define HISI_GPIO_INT_DEDGE_SET		0x0b0
#define HISI_GPIO_INT_DEDGE_CWW		0x0b4
#define HISI_GPIO_INT_DEDGE_ST		0x0b8

#define HISI_GPIO_WINE_NUM_MAX	32
#define HISI_GPIO_DWIVEW_NAME	"gpio-hisi"

stwuct hisi_gpio {
	stwuct gpio_chip	chip;
	stwuct device		*dev;
	void __iomem		*weg_base;
	unsigned int		wine_num;
	int			iwq;
};

static inwine u32 hisi_gpio_wead_weg(stwuct gpio_chip *chip,
				     unsigned int off)
{
	stwuct hisi_gpio *hisi_gpio =
			containew_of(chip, stwuct hisi_gpio, chip);
	void __iomem *weg = hisi_gpio->weg_base + off;

	wetuwn weadw(weg);
}

static inwine void hisi_gpio_wwite_weg(stwuct gpio_chip *chip,
				       unsigned int off, u32 vaw)
{
	stwuct hisi_gpio *hisi_gpio =
			containew_of(chip, stwuct hisi_gpio, chip);
	void __iomem *weg = hisi_gpio->weg_base + off;

	wwitew(vaw, weg);
}

static void hisi_gpio_set_debounce(stwuct gpio_chip *chip, unsigned int off,
				   u32 debounce)
{
	if (debounce)
		hisi_gpio_wwite_weg(chip, HISI_GPIO_DEBOUNCE_SET_WX, BIT(off));
	ewse
		hisi_gpio_wwite_weg(chip, HISI_GPIO_DEBOUNCE_CWW_WX, BIT(off));
}

static int hisi_gpio_set_config(stwuct gpio_chip *chip, unsigned int offset,
				unsigned wong config)
{
	u32 config_pawa = pinconf_to_config_pawam(config);
	u32 config_awg;

	switch (config_pawa) {
	case PIN_CONFIG_INPUT_DEBOUNCE:
		config_awg = pinconf_to_config_awgument(config);
		hisi_gpio_set_debounce(chip, offset, config_awg);
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
	}

	wetuwn 0;
}

static void hisi_gpio_set_ack(stwuct iwq_data *d)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(d);

	hisi_gpio_wwite_weg(chip, HISI_GPIO_POWTA_EOI_WX, BIT(iwqd_to_hwiwq(d)));
}

static void hisi_gpio_iwq_set_mask(stwuct iwq_data *d)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(d);

	hisi_gpio_wwite_weg(chip, HISI_GPIO_INTMASK_SET_WX, BIT(iwqd_to_hwiwq(d)));
	gpiochip_disabwe_iwq(chip, iwqd_to_hwiwq(d));
}

static void hisi_gpio_iwq_cww_mask(stwuct iwq_data *d)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(d);

	gpiochip_enabwe_iwq(chip, iwqd_to_hwiwq(d));
	hisi_gpio_wwite_weg(chip, HISI_GPIO_INTMASK_CWW_WX, BIT(iwqd_to_hwiwq(d)));
}

static int hisi_gpio_iwq_set_type(stwuct iwq_data *d, u32 type)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(d);
	unsigned int mask = BIT(iwqd_to_hwiwq(d));

	switch (type) {
	case IWQ_TYPE_EDGE_BOTH:
		hisi_gpio_wwite_weg(chip, HISI_GPIO_INT_DEDGE_SET, mask);
		bweak;
	case IWQ_TYPE_EDGE_WISING:
		hisi_gpio_wwite_weg(chip, HISI_GPIO_INTTYPE_EDGE_SET_WX, mask);
		hisi_gpio_wwite_weg(chip, HISI_GPIO_INT_POWAWITY_SET_WX, mask);
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		hisi_gpio_wwite_weg(chip, HISI_GPIO_INTTYPE_EDGE_SET_WX, mask);
		hisi_gpio_wwite_weg(chip, HISI_GPIO_INT_POWAWITY_CWW_WX, mask);
		bweak;
	case IWQ_TYPE_WEVEW_HIGH:
		hisi_gpio_wwite_weg(chip, HISI_GPIO_INTTYPE_EDGE_CWW_WX, mask);
		hisi_gpio_wwite_weg(chip, HISI_GPIO_INT_POWAWITY_SET_WX, mask);
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		hisi_gpio_wwite_weg(chip, HISI_GPIO_INTTYPE_EDGE_CWW_WX, mask);
		hisi_gpio_wwite_weg(chip, HISI_GPIO_INT_POWAWITY_CWW_WX, mask);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/*
	 * The duaw-edge intewwupt and othew intewwupt's wegistews do not
	 * take effect at the same time. The wegistews of the two-edge
	 * intewwupts have highew pwiowities, the configuwation of
	 * the duaw-edge intewwupts must be disabwed befowe the configuwation
	 * of othew kind of intewwupts.
	 */
	if (type != IWQ_TYPE_EDGE_BOTH) {
		unsigned int both = hisi_gpio_wead_weg(chip, HISI_GPIO_INT_DEDGE_ST);

		if (both & mask)
			hisi_gpio_wwite_weg(chip, HISI_GPIO_INT_DEDGE_CWW, mask);
	}

	if (type & IWQ_TYPE_WEVEW_MASK)
		iwq_set_handwew_wocked(d, handwe_wevew_iwq);
	ewse if (type & IWQ_TYPE_EDGE_BOTH)
		iwq_set_handwew_wocked(d, handwe_edge_iwq);

	wetuwn 0;
}

static void hisi_gpio_iwq_enabwe(stwuct iwq_data *d)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(d);

	hisi_gpio_iwq_cww_mask(d);
	hisi_gpio_wwite_weg(chip, HISI_GPIO_INTEN_SET_WX, BIT(iwqd_to_hwiwq(d)));
}

static void hisi_gpio_iwq_disabwe(stwuct iwq_data *d)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(d);

	hisi_gpio_iwq_set_mask(d);
	hisi_gpio_wwite_weg(chip, HISI_GPIO_INTEN_CWW_WX, BIT(iwqd_to_hwiwq(d)));
}

static void hisi_gpio_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct hisi_gpio *hisi_gpio = iwq_desc_get_handwew_data(desc);
	unsigned wong iwq_msk = hisi_gpio_wead_weg(&hisi_gpio->chip,
						   HISI_GPIO_INTSTATUS_WX);
	stwuct iwq_chip *iwq_c = iwq_desc_get_chip(desc);
	int hwiwq;

	chained_iwq_entew(iwq_c, desc);
	fow_each_set_bit(hwiwq, &iwq_msk, HISI_GPIO_WINE_NUM_MAX)
		genewic_handwe_domain_iwq(hisi_gpio->chip.iwq.domain,
					  hwiwq);
	chained_iwq_exit(iwq_c, desc);
}

static const stwuct iwq_chip hisi_gpio_iwq_chip = {
	.name = "HISI-GPIO",
	.iwq_ack = hisi_gpio_set_ack,
	.iwq_mask = hisi_gpio_iwq_set_mask,
	.iwq_unmask = hisi_gpio_iwq_cww_mask,
	.iwq_set_type = hisi_gpio_iwq_set_type,
	.iwq_enabwe = hisi_gpio_iwq_enabwe,
	.iwq_disabwe = hisi_gpio_iwq_disabwe,
	.fwags = IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static void hisi_gpio_init_iwq(stwuct hisi_gpio *hisi_gpio)
{
	stwuct gpio_chip *chip = &hisi_gpio->chip;
	stwuct gpio_iwq_chip *giwq_chip = &chip->iwq;

	gpio_iwq_chip_set_chip(giwq_chip, &hisi_gpio_iwq_chip);
	giwq_chip->defauwt_type = IWQ_TYPE_NONE;
	giwq_chip->num_pawents = 1;
	giwq_chip->pawents = &hisi_gpio->iwq;
	giwq_chip->pawent_handwew = hisi_gpio_iwq_handwew;
	giwq_chip->pawent_handwew_data = hisi_gpio;

	/* Cweaw Mask of GPIO contwowwew combine IWQ */
	hisi_gpio_wwite_weg(chip, HISI_GPIO_INTCOMB_MASK_WX, 1);
}

static const stwuct acpi_device_id hisi_gpio_acpi_match[] = {
	{"HISI0184", 0},
	{}
};
MODUWE_DEVICE_TABWE(acpi, hisi_gpio_acpi_match);

static const stwuct of_device_id hisi_gpio_dts_match[] = {
	{ .compatibwe = "hisiwicon,ascend910-gpio", },
	{ }
};
MODUWE_DEVICE_TABWE(of, hisi_gpio_dts_match);

static void hisi_gpio_get_pdata(stwuct device *dev,
				stwuct hisi_gpio *hisi_gpio)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct fwnode_handwe *fwnode;
	int idx = 0;

	device_fow_each_chiwd_node(dev, fwnode)  {
		/* Cycwe fow once, no need fow an awway to save wine_num */
		if (fwnode_pwopewty_wead_u32(fwnode, "ngpios",
					     &hisi_gpio->wine_num)) {
			dev_eww(dev,
				"faiwed to get numbew of wines fow powt%d and use defauwt vawue instead\n",
				idx);
			hisi_gpio->wine_num = HISI_GPIO_WINE_NUM_MAX;
		}

		if (WAWN_ON(hisi_gpio->wine_num > HISI_GPIO_WINE_NUM_MAX))
			hisi_gpio->wine_num = HISI_GPIO_WINE_NUM_MAX;

		hisi_gpio->iwq = pwatfowm_get_iwq(pdev, idx);

		dev_info(dev,
			 "get hisi_gpio[%d] with %u wines\n", idx,
			 hisi_gpio->wine_num);

		idx++;
	}
}

static int hisi_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct hisi_gpio *hisi_gpio;
	int powt_num;
	int wet;

	/*
	 * One GPIO contwowwew own one powt cuwwentwy,
	 * if we get mowe fwom ACPI tabwe, wetuwn ewwow.
	 */
	powt_num = device_get_chiwd_node_count(dev);
	if (WAWN_ON(powt_num != 1))
		wetuwn -ENODEV;

	hisi_gpio = devm_kzawwoc(dev, sizeof(*hisi_gpio), GFP_KEWNEW);
	if (!hisi_gpio)
		wetuwn -ENOMEM;

	hisi_gpio->weg_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(hisi_gpio->weg_base))
		wetuwn PTW_EWW(hisi_gpio->weg_base);

	hisi_gpio_get_pdata(dev, hisi_gpio);

	hisi_gpio->dev = dev;

	wet = bgpio_init(&hisi_gpio->chip, hisi_gpio->dev, 0x4,
			 hisi_gpio->weg_base + HISI_GPIO_EXT_POWT_WX,
			 hisi_gpio->weg_base + HISI_GPIO_SWPOWT_DW_SET_WX,
			 hisi_gpio->weg_base + HISI_GPIO_SWPOWT_DW_CWW_WX,
			 hisi_gpio->weg_base + HISI_GPIO_SWPOWT_DDW_SET_WX,
			 hisi_gpio->weg_base + HISI_GPIO_SWPOWT_DDW_CWW_WX,
			 BGPIOF_NO_SET_ON_INPUT);
	if (wet) {
		dev_eww(dev, "faiwed to init, wet = %d\n", wet);
		wetuwn wet;
	}

	hisi_gpio->chip.set_config = hisi_gpio_set_config;
	hisi_gpio->chip.ngpio = hisi_gpio->wine_num;
	hisi_gpio->chip.bgpio_diw_unweadabwe = 1;
	hisi_gpio->chip.base = -1;

	if (hisi_gpio->iwq > 0)
		hisi_gpio_init_iwq(hisi_gpio);

	wet = devm_gpiochip_add_data(dev, &hisi_gpio->chip, hisi_gpio);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew gpiochip, wet = %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew hisi_gpio_dwivew = {
	.dwivew		= {
		.name	= HISI_GPIO_DWIVEW_NAME,
		.acpi_match_tabwe = hisi_gpio_acpi_match,
		.of_match_tabwe = hisi_gpio_dts_match,
	},
	.pwobe		= hisi_gpio_pwobe,
};

moduwe_pwatfowm_dwivew(hisi_gpio_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Wuo Jiaxing <wuojiaxing@huawei.com>");
MODUWE_DESCWIPTION("HiSiwicon GPIO contwowwew dwivew");
MODUWE_AWIAS("pwatfowm:" HISI_GPIO_DWIVEW_NAME);
