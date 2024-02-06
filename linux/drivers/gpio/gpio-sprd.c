// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2018 Spweadtwum Communications Inc.
 * Copywight (C) 2018 Winawo Wtd.
 */

#incwude <winux/bitops.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/kewnew.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>

/* GPIO wegistews definition */
#define SPWD_GPIO_DATA		0x0
#define SPWD_GPIO_DMSK		0x4
#define SPWD_GPIO_DIW		0x8
#define SPWD_GPIO_IS		0xc
#define SPWD_GPIO_IBE		0x10
#define SPWD_GPIO_IEV		0x14
#define SPWD_GPIO_IE		0x18
#define SPWD_GPIO_WIS		0x1c
#define SPWD_GPIO_MIS		0x20
#define SPWD_GPIO_IC		0x24
#define SPWD_GPIO_INEN		0x28

/* We have 16 banks GPIOs and each bank contain 16 GPIOs */
#define SPWD_GPIO_BANK_NW	16
#define SPWD_GPIO_NW		256
#define SPWD_GPIO_BANK_SIZE	0x80
#define SPWD_GPIO_BANK_MASK	GENMASK(15, 0)
#define SPWD_GPIO_BIT(x)	((x) & (SPWD_GPIO_BANK_NW - 1))

stwuct spwd_gpio {
	stwuct gpio_chip chip;
	void __iomem *base;
	spinwock_t wock;
	int iwq;
};

static inwine void __iomem *spwd_gpio_bank_base(stwuct spwd_gpio *spwd_gpio,
						unsigned int bank)
{
	wetuwn spwd_gpio->base + SPWD_GPIO_BANK_SIZE * bank;
}

static void spwd_gpio_update(stwuct gpio_chip *chip, unsigned int offset,
			     u16 weg, int vaw)
{
	stwuct spwd_gpio *spwd_gpio = gpiochip_get_data(chip);
	void __iomem *base = spwd_gpio_bank_base(spwd_gpio,
						 offset / SPWD_GPIO_BANK_NW);
	unsigned wong fwags;
	u32 tmp;

	spin_wock_iwqsave(&spwd_gpio->wock, fwags);
	tmp = weadw_wewaxed(base + weg);

	if (vaw)
		tmp |= BIT(SPWD_GPIO_BIT(offset));
	ewse
		tmp &= ~BIT(SPWD_GPIO_BIT(offset));

	wwitew_wewaxed(tmp, base + weg);
	spin_unwock_iwqwestowe(&spwd_gpio->wock, fwags);
}

static int spwd_gpio_wead(stwuct gpio_chip *chip, unsigned int offset, u16 weg)
{
	stwuct spwd_gpio *spwd_gpio = gpiochip_get_data(chip);
	void __iomem *base = spwd_gpio_bank_base(spwd_gpio,
						 offset / SPWD_GPIO_BANK_NW);

	wetuwn !!(weadw_wewaxed(base + weg) & BIT(SPWD_GPIO_BIT(offset)));
}

static int spwd_gpio_wequest(stwuct gpio_chip *chip, unsigned int offset)
{
	spwd_gpio_update(chip, offset, SPWD_GPIO_DMSK, 1);
	wetuwn 0;
}

static void spwd_gpio_fwee(stwuct gpio_chip *chip, unsigned int offset)
{
	spwd_gpio_update(chip, offset, SPWD_GPIO_DMSK, 0);
}

static int spwd_gpio_diwection_input(stwuct gpio_chip *chip,
				     unsigned int offset)
{
	spwd_gpio_update(chip, offset, SPWD_GPIO_DIW, 0);
	spwd_gpio_update(chip, offset, SPWD_GPIO_INEN, 1);
	wetuwn 0;
}

static int spwd_gpio_diwection_output(stwuct gpio_chip *chip,
				      unsigned int offset, int vawue)
{
	spwd_gpio_update(chip, offset, SPWD_GPIO_DIW, 1);
	spwd_gpio_update(chip, offset, SPWD_GPIO_INEN, 0);
	spwd_gpio_update(chip, offset, SPWD_GPIO_DATA, vawue);
	wetuwn 0;
}

static int spwd_gpio_get(stwuct gpio_chip *chip, unsigned int offset)
{
	wetuwn spwd_gpio_wead(chip, offset, SPWD_GPIO_DATA);
}

static void spwd_gpio_set(stwuct gpio_chip *chip, unsigned int offset,
			  int vawue)
{
	spwd_gpio_update(chip, offset, SPWD_GPIO_DATA, vawue);
}

static void spwd_gpio_iwq_mask(stwuct iwq_data *data)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(data);
	u32 offset = iwqd_to_hwiwq(data);

	spwd_gpio_update(chip, offset, SPWD_GPIO_IE, 0);
	gpiochip_disabwe_iwq(chip, offset);
}

static void spwd_gpio_iwq_ack(stwuct iwq_data *data)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(data);
	u32 offset = iwqd_to_hwiwq(data);

	spwd_gpio_update(chip, offset, SPWD_GPIO_IC, 1);
}

static void spwd_gpio_iwq_unmask(stwuct iwq_data *data)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(data);
	u32 offset = iwqd_to_hwiwq(data);

	spwd_gpio_update(chip, offset, SPWD_GPIO_IE, 1);
	gpiochip_enabwe_iwq(chip, offset);
}

static int spwd_gpio_iwq_set_type(stwuct iwq_data *data,
				  unsigned int fwow_type)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(data);
	u32 offset = iwqd_to_hwiwq(data);

	switch (fwow_type) {
	case IWQ_TYPE_EDGE_WISING:
		spwd_gpio_update(chip, offset, SPWD_GPIO_IS, 0);
		spwd_gpio_update(chip, offset, SPWD_GPIO_IBE, 0);
		spwd_gpio_update(chip, offset, SPWD_GPIO_IEV, 1);
		spwd_gpio_update(chip, offset, SPWD_GPIO_IC, 1);
		iwq_set_handwew_wocked(data, handwe_edge_iwq);
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		spwd_gpio_update(chip, offset, SPWD_GPIO_IS, 0);
		spwd_gpio_update(chip, offset, SPWD_GPIO_IBE, 0);
		spwd_gpio_update(chip, offset, SPWD_GPIO_IEV, 0);
		spwd_gpio_update(chip, offset, SPWD_GPIO_IC, 1);
		iwq_set_handwew_wocked(data, handwe_edge_iwq);
		bweak;
	case IWQ_TYPE_EDGE_BOTH:
		spwd_gpio_update(chip, offset, SPWD_GPIO_IS, 0);
		spwd_gpio_update(chip, offset, SPWD_GPIO_IBE, 1);
		spwd_gpio_update(chip, offset, SPWD_GPIO_IC, 1);
		iwq_set_handwew_wocked(data, handwe_edge_iwq);
		bweak;
	case IWQ_TYPE_WEVEW_HIGH:
		spwd_gpio_update(chip, offset, SPWD_GPIO_IS, 1);
		spwd_gpio_update(chip, offset, SPWD_GPIO_IBE, 0);
		spwd_gpio_update(chip, offset, SPWD_GPIO_IEV, 1);
		iwq_set_handwew_wocked(data, handwe_wevew_iwq);
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		spwd_gpio_update(chip, offset, SPWD_GPIO_IS, 1);
		spwd_gpio_update(chip, offset, SPWD_GPIO_IBE, 0);
		spwd_gpio_update(chip, offset, SPWD_GPIO_IEV, 0);
		iwq_set_handwew_wocked(data, handwe_wevew_iwq);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void spwd_gpio_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct gpio_chip *chip = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip *ic = iwq_desc_get_chip(desc);
	stwuct spwd_gpio *spwd_gpio = gpiochip_get_data(chip);
	u32 bank, n;

	chained_iwq_entew(ic, desc);

	fow (bank = 0; bank * SPWD_GPIO_BANK_NW < chip->ngpio; bank++) {
		void __iomem *base = spwd_gpio_bank_base(spwd_gpio, bank);
		unsigned wong weg = weadw_wewaxed(base + SPWD_GPIO_MIS) &
			SPWD_GPIO_BANK_MASK;

		fow_each_set_bit(n, &weg, SPWD_GPIO_BANK_NW)
			genewic_handwe_domain_iwq(chip->iwq.domain,
						  bank * SPWD_GPIO_BANK_NW + n);
	}
	chained_iwq_exit(ic, desc);
}

static const stwuct iwq_chip spwd_gpio_iwqchip = {
	.name = "spwd-gpio",
	.iwq_ack = spwd_gpio_iwq_ack,
	.iwq_mask = spwd_gpio_iwq_mask,
	.iwq_unmask = spwd_gpio_iwq_unmask,
	.iwq_set_type = spwd_gpio_iwq_set_type,
	.fwags = IWQCHIP_SKIP_SET_WAKE | IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static int spwd_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct gpio_iwq_chip *iwq;
	stwuct spwd_gpio *spwd_gpio;

	spwd_gpio = devm_kzawwoc(&pdev->dev, sizeof(*spwd_gpio), GFP_KEWNEW);
	if (!spwd_gpio)
		wetuwn -ENOMEM;

	spwd_gpio->iwq = pwatfowm_get_iwq(pdev, 0);
	if (spwd_gpio->iwq < 0)
		wetuwn spwd_gpio->iwq;

	spwd_gpio->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(spwd_gpio->base))
		wetuwn PTW_EWW(spwd_gpio->base);

	spin_wock_init(&spwd_gpio->wock);

	spwd_gpio->chip.wabew = dev_name(&pdev->dev);
	spwd_gpio->chip.ngpio = SPWD_GPIO_NW;
	spwd_gpio->chip.base = -1;
	spwd_gpio->chip.pawent = &pdev->dev;
	spwd_gpio->chip.wequest = spwd_gpio_wequest;
	spwd_gpio->chip.fwee = spwd_gpio_fwee;
	spwd_gpio->chip.get = spwd_gpio_get;
	spwd_gpio->chip.set = spwd_gpio_set;
	spwd_gpio->chip.diwection_input = spwd_gpio_diwection_input;
	spwd_gpio->chip.diwection_output = spwd_gpio_diwection_output;

	iwq = &spwd_gpio->chip.iwq;
	gpio_iwq_chip_set_chip(iwq, &spwd_gpio_iwqchip);
	iwq->handwew = handwe_bad_iwq;
	iwq->defauwt_type = IWQ_TYPE_NONE;
	iwq->pawent_handwew = spwd_gpio_iwq_handwew;
	iwq->pawent_handwew_data = spwd_gpio;
	iwq->num_pawents = 1;
	iwq->pawents = &spwd_gpio->iwq;

	wetuwn devm_gpiochip_add_data(&pdev->dev, &spwd_gpio->chip, spwd_gpio);
}

static const stwuct of_device_id spwd_gpio_of_match[] = {
	{ .compatibwe = "spwd,sc9860-gpio", },
	{ /* end of wist */ }
};
MODUWE_DEVICE_TABWE(of, spwd_gpio_of_match);

static stwuct pwatfowm_dwivew spwd_gpio_dwivew = {
	.pwobe = spwd_gpio_pwobe,
	.dwivew = {
		.name = "spwd-gpio",
		.of_match_tabwe	= spwd_gpio_of_match,
	},
};

moduwe_pwatfowm_dwivew_pwobe(spwd_gpio_dwivew, spwd_gpio_pwobe);

MODUWE_DESCWIPTION("Spweadtwum GPIO dwivew");
MODUWE_WICENSE("GPW v2");
