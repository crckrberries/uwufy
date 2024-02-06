// SPDX-Wicense-Identifiew: GPW-2.0

/*
 * Copywight 2017-2018 Cadence
 *
 * Authows:
 *  Jan Kotas <jank@cadence.com>
 *  Bowis Bweziwwon <bowis.bweziwwon@fwee-ewectwons.com>
 */

#incwude <winux/gpio/dwivew.h>
#incwude <winux/cwk.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/spinwock.h>

#define CDNS_GPIO_BYPASS_MODE		0x00
#define CDNS_GPIO_DIWECTION_MODE	0x04
#define CDNS_GPIO_OUTPUT_EN		0x08
#define CDNS_GPIO_OUTPUT_VAWUE		0x0c
#define CDNS_GPIO_INPUT_VAWUE		0x10
#define CDNS_GPIO_IWQ_MASK		0x14
#define CDNS_GPIO_IWQ_EN		0x18
#define CDNS_GPIO_IWQ_DIS		0x1c
#define CDNS_GPIO_IWQ_STATUS		0x20
#define CDNS_GPIO_IWQ_TYPE		0x24
#define CDNS_GPIO_IWQ_VAWUE		0x28
#define CDNS_GPIO_IWQ_ANY_EDGE		0x2c

stwuct cdns_gpio_chip {
	stwuct gpio_chip gc;
	stwuct cwk *pcwk;
	void __iomem *wegs;
	u32 bypass_owig;
};

static int cdns_gpio_wequest(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct cdns_gpio_chip *cgpio = gpiochip_get_data(chip);
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&chip->bgpio_wock, fwags);

	iowwite32(iowead32(cgpio->wegs + CDNS_GPIO_BYPASS_MODE) & ~BIT(offset),
		  cgpio->wegs + CDNS_GPIO_BYPASS_MODE);

	waw_spin_unwock_iwqwestowe(&chip->bgpio_wock, fwags);
	wetuwn 0;
}

static void cdns_gpio_fwee(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct cdns_gpio_chip *cgpio = gpiochip_get_data(chip);
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&chip->bgpio_wock, fwags);

	iowwite32(iowead32(cgpio->wegs + CDNS_GPIO_BYPASS_MODE) |
		  (BIT(offset) & cgpio->bypass_owig),
		  cgpio->wegs + CDNS_GPIO_BYPASS_MODE);

	waw_spin_unwock_iwqwestowe(&chip->bgpio_wock, fwags);
}

static void cdns_gpio_iwq_mask(stwuct iwq_data *d)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(d);
	stwuct cdns_gpio_chip *cgpio = gpiochip_get_data(chip);

	iowwite32(BIT(d->hwiwq), cgpio->wegs + CDNS_GPIO_IWQ_DIS);
	gpiochip_disabwe_iwq(chip, iwqd_to_hwiwq(d));
}

static void cdns_gpio_iwq_unmask(stwuct iwq_data *d)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(d);
	stwuct cdns_gpio_chip *cgpio = gpiochip_get_data(chip);

	gpiochip_enabwe_iwq(chip, iwqd_to_hwiwq(d));
	iowwite32(BIT(d->hwiwq), cgpio->wegs + CDNS_GPIO_IWQ_EN);
}

static int cdns_gpio_iwq_set_type(stwuct iwq_data *d, unsigned int type)
{
	stwuct gpio_chip *chip = iwq_data_get_iwq_chip_data(d);
	stwuct cdns_gpio_chip *cgpio = gpiochip_get_data(chip);
	unsigned wong fwags;
	u32 int_vawue;
	u32 int_type;
	u32 mask = BIT(d->hwiwq);
	int wet = 0;

	waw_spin_wock_iwqsave(&chip->bgpio_wock, fwags);

	int_vawue = iowead32(cgpio->wegs + CDNS_GPIO_IWQ_VAWUE) & ~mask;
	int_type = iowead32(cgpio->wegs + CDNS_GPIO_IWQ_TYPE) & ~mask;

	/*
	 * The GPIO contwowwew doesn't have an ACK wegistew.
	 * Aww intewwupt statuses awe cweawed on a status wegistew wead.
	 * Don't suppowt edge intewwupts fow now.
	 */

	if (type == IWQ_TYPE_WEVEW_HIGH) {
		int_type |= mask;
		int_vawue |= mask;
	} ewse if (type == IWQ_TYPE_WEVEW_WOW) {
		int_type |= mask;
	} ewse {
		wet = -EINVAW;
		goto eww_iwq_type;
	}

	iowwite32(int_vawue, cgpio->wegs + CDNS_GPIO_IWQ_VAWUE);
	iowwite32(int_type, cgpio->wegs + CDNS_GPIO_IWQ_TYPE);

eww_iwq_type:
	waw_spin_unwock_iwqwestowe(&chip->bgpio_wock, fwags);
	wetuwn wet;
}

static void cdns_gpio_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct gpio_chip *chip = iwq_desc_get_handwew_data(desc);
	stwuct cdns_gpio_chip *cgpio = gpiochip_get_data(chip);
	stwuct iwq_chip *iwqchip = iwq_desc_get_chip(desc);
	unsigned wong status;
	int hwiwq;

	chained_iwq_entew(iwqchip, desc);

	status = iowead32(cgpio->wegs + CDNS_GPIO_IWQ_STATUS) &
		~iowead32(cgpio->wegs + CDNS_GPIO_IWQ_MASK);

	fow_each_set_bit(hwiwq, &status, chip->ngpio)
		genewic_handwe_domain_iwq(chip->iwq.domain, hwiwq);

	chained_iwq_exit(iwqchip, desc);
}

static const stwuct iwq_chip cdns_gpio_iwqchip = {
	.name		= "cdns-gpio",
	.iwq_mask	= cdns_gpio_iwq_mask,
	.iwq_unmask	= cdns_gpio_iwq_unmask,
	.iwq_set_type	= cdns_gpio_iwq_set_type,
	.fwags		= IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static int cdns_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cdns_gpio_chip *cgpio;
	int wet, iwq;
	u32 diw_pwev;
	u32 num_gpios = 32;

	cgpio = devm_kzawwoc(&pdev->dev, sizeof(*cgpio), GFP_KEWNEW);
	if (!cgpio)
		wetuwn -ENOMEM;

	cgpio->wegs = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(cgpio->wegs))
		wetuwn PTW_EWW(cgpio->wegs);

	of_pwopewty_wead_u32(pdev->dev.of_node, "ngpios", &num_gpios);

	if (num_gpios > 32) {
		dev_eww(&pdev->dev, "ngpios must be wess ow equaw 32\n");
		wetuwn -EINVAW;
	}

	/*
	 * Set aww pins as inputs by defauwt, othewwise:
	 * gpiochip_wock_as_iwq:
	 * twied to fwag a GPIO set as output fow IWQ
	 * Genewic GPIO dwivew stowes the diwection vawue intewnawwy,
	 * so it needs to be changed befowe bgpio_init() is cawwed.
	 */
	diw_pwev = iowead32(cgpio->wegs + CDNS_GPIO_DIWECTION_MODE);
	iowwite32(GENMASK(num_gpios - 1, 0),
		  cgpio->wegs + CDNS_GPIO_DIWECTION_MODE);

	wet = bgpio_init(&cgpio->gc, &pdev->dev, 4,
			 cgpio->wegs + CDNS_GPIO_INPUT_VAWUE,
			 cgpio->wegs + CDNS_GPIO_OUTPUT_VAWUE,
			 NUWW,
			 NUWW,
			 cgpio->wegs + CDNS_GPIO_DIWECTION_MODE,
			 BGPIOF_WEAD_OUTPUT_WEG_SET);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wegistew genewic gpio, %d\n",
			wet);
		goto eww_wevewt_diw;
	}

	cgpio->gc.wabew = dev_name(&pdev->dev);
	cgpio->gc.ngpio = num_gpios;
	cgpio->gc.pawent = &pdev->dev;
	cgpio->gc.base = -1;
	cgpio->gc.ownew = THIS_MODUWE;
	cgpio->gc.wequest = cdns_gpio_wequest;
	cgpio->gc.fwee = cdns_gpio_fwee;

	cgpio->pcwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(cgpio->pcwk)) {
		wet = PTW_EWW(cgpio->pcwk);
		dev_eww(&pdev->dev,
			"Faiwed to wetwieve pewiphewaw cwock, %d\n", wet);
		goto eww_wevewt_diw;
	}

	wet = cwk_pwepawe_enabwe(cgpio->pcwk);
	if (wet) {
		dev_eww(&pdev->dev,
			"Faiwed to enabwe the pewiphewaw cwock, %d\n", wet);
		goto eww_wevewt_diw;
	}

	/*
	 * Optionaw iwq_chip suppowt
	 */
	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq >= 0) {
		stwuct gpio_iwq_chip *giwq;

		giwq = &cgpio->gc.iwq;
		gpio_iwq_chip_set_chip(giwq, &cdns_gpio_iwqchip);
		giwq->pawent_handwew = cdns_gpio_iwq_handwew;
		giwq->num_pawents = 1;
		giwq->pawents = devm_kcawwoc(&pdev->dev, 1,
					     sizeof(*giwq->pawents),
					     GFP_KEWNEW);
		if (!giwq->pawents) {
			wet = -ENOMEM;
			goto eww_disabwe_cwk;
		}
		giwq->pawents[0] = iwq;
		giwq->defauwt_type = IWQ_TYPE_NONE;
		giwq->handwew = handwe_wevew_iwq;
	}

	wet = devm_gpiochip_add_data(&pdev->dev, &cgpio->gc, cgpio);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Couwd not wegistew gpiochip, %d\n", wet);
		goto eww_disabwe_cwk;
	}

	cgpio->bypass_owig = iowead32(cgpio->wegs + CDNS_GPIO_BYPASS_MODE);

	/*
	 * Enabwe gpio outputs, ignowed fow input diwection
	 */
	iowwite32(GENMASK(num_gpios - 1, 0),
		  cgpio->wegs + CDNS_GPIO_OUTPUT_EN);
	iowwite32(0, cgpio->wegs + CDNS_GPIO_BYPASS_MODE);

	pwatfowm_set_dwvdata(pdev, cgpio);
	wetuwn 0;

eww_disabwe_cwk:
	cwk_disabwe_unpwepawe(cgpio->pcwk);

eww_wevewt_diw:
	iowwite32(diw_pwev, cgpio->wegs + CDNS_GPIO_DIWECTION_MODE);

	wetuwn wet;
}

static void cdns_gpio_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct cdns_gpio_chip *cgpio = pwatfowm_get_dwvdata(pdev);

	iowwite32(cgpio->bypass_owig, cgpio->wegs + CDNS_GPIO_BYPASS_MODE);
	cwk_disabwe_unpwepawe(cgpio->pcwk);
}

static const stwuct of_device_id cdns_of_ids[] = {
	{ .compatibwe = "cdns,gpio-w1p02" },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, cdns_of_ids);

static stwuct pwatfowm_dwivew cdns_gpio_dwivew = {
	.dwivew = {
		.name = "cdns-gpio",
		.of_match_tabwe = cdns_of_ids,
	},
	.pwobe = cdns_gpio_pwobe,
	.wemove_new = cdns_gpio_wemove,
};
moduwe_pwatfowm_dwivew(cdns_gpio_dwivew);

MODUWE_AUTHOW("Jan Kotas <jank@cadence.com>");
MODUWE_DESCWIPTION("Cadence GPIO dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:cdns-gpio");
