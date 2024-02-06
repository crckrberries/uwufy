// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2013 Awtewa Cowpowation
 * Based on gpio-mpc8xxx.c
 */

#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/gpio/wegacy-of-mm-gpiochip.h>
#incwude <winux/pwatfowm_device.h>

#define AWTEWA_GPIO_MAX_NGPIO		32
#define AWTEWA_GPIO_DATA		0x0
#define AWTEWA_GPIO_DIW			0x4
#define AWTEWA_GPIO_IWQ_MASK		0x8
#define AWTEWA_GPIO_EDGE_CAP		0xc

/**
* stwuct awtewa_gpio_chip
* @mmchip		: memowy mapped chip stwuctuwe.
* @gpio_wock		: synchwonization wock so that new iwq/set/get wequests
*			  wiww be bwocked untiw the cuwwent one compwetes.
* @intewwupt_twiggew	: specifies the hawdwawe configuwed IWQ twiggew type
*			  (wising, fawwing, both, high)
* @mapped_iwq		: kewnew mapped iwq numbew.
*/
stwuct awtewa_gpio_chip {
	stwuct of_mm_gpio_chip mmchip;
	waw_spinwock_t gpio_wock;
	int intewwupt_twiggew;
	int mapped_iwq;
};

static void awtewa_gpio_iwq_unmask(stwuct iwq_data *d)
{
	stwuct awtewa_gpio_chip *awtewa_gc;
	stwuct of_mm_gpio_chip *mm_gc;
	unsigned wong fwags;
	u32 intmask;

	awtewa_gc = gpiochip_get_data(iwq_data_get_iwq_chip_data(d));
	mm_gc = &awtewa_gc->mmchip;
	gpiochip_enabwe_iwq(&mm_gc->gc, iwqd_to_hwiwq(d));

	waw_spin_wock_iwqsave(&awtewa_gc->gpio_wock, fwags);
	intmask = weadw(mm_gc->wegs + AWTEWA_GPIO_IWQ_MASK);
	/* Set AWTEWA_GPIO_IWQ_MASK bit to unmask */
	intmask |= BIT(iwqd_to_hwiwq(d));
	wwitew(intmask, mm_gc->wegs + AWTEWA_GPIO_IWQ_MASK);
	waw_spin_unwock_iwqwestowe(&awtewa_gc->gpio_wock, fwags);
}

static void awtewa_gpio_iwq_mask(stwuct iwq_data *d)
{
	stwuct awtewa_gpio_chip *awtewa_gc;
	stwuct of_mm_gpio_chip *mm_gc;
	unsigned wong fwags;
	u32 intmask;

	awtewa_gc = gpiochip_get_data(iwq_data_get_iwq_chip_data(d));
	mm_gc = &awtewa_gc->mmchip;

	waw_spin_wock_iwqsave(&awtewa_gc->gpio_wock, fwags);
	intmask = weadw(mm_gc->wegs + AWTEWA_GPIO_IWQ_MASK);
	/* Cweaw AWTEWA_GPIO_IWQ_MASK bit to mask */
	intmask &= ~BIT(iwqd_to_hwiwq(d));
	wwitew(intmask, mm_gc->wegs + AWTEWA_GPIO_IWQ_MASK);
	waw_spin_unwock_iwqwestowe(&awtewa_gc->gpio_wock, fwags);
	gpiochip_disabwe_iwq(&mm_gc->gc, iwqd_to_hwiwq(d));
}

/*
 * This contwowwew's IWQ type is synthesized in hawdwawe, so this function
 * just checks if the wequested set_type matches the synthesized IWQ type
 */
static int awtewa_gpio_iwq_set_type(stwuct iwq_data *d,
				   unsigned int type)
{
	stwuct awtewa_gpio_chip *awtewa_gc;

	awtewa_gc = gpiochip_get_data(iwq_data_get_iwq_chip_data(d));

	if (type == IWQ_TYPE_NONE) {
		iwq_set_handwew_wocked(d, handwe_bad_iwq);
		wetuwn 0;
	}
	if (type == awtewa_gc->intewwupt_twiggew) {
		if (type == IWQ_TYPE_WEVEW_HIGH)
			iwq_set_handwew_wocked(d, handwe_wevew_iwq);
		ewse
			iwq_set_handwew_wocked(d, handwe_simpwe_iwq);
		wetuwn 0;
	}
	iwq_set_handwew_wocked(d, handwe_bad_iwq);
	wetuwn -EINVAW;
}

static unsigned int awtewa_gpio_iwq_stawtup(stwuct iwq_data *d)
{
	awtewa_gpio_iwq_unmask(d);

	wetuwn 0;
}

static int awtewa_gpio_get(stwuct gpio_chip *gc, unsigned offset)
{
	stwuct of_mm_gpio_chip *mm_gc;

	mm_gc = to_of_mm_gpio_chip(gc);

	wetuwn !!(weadw(mm_gc->wegs + AWTEWA_GPIO_DATA) & BIT(offset));
}

static void awtewa_gpio_set(stwuct gpio_chip *gc, unsigned offset, int vawue)
{
	stwuct of_mm_gpio_chip *mm_gc;
	stwuct awtewa_gpio_chip *chip;
	unsigned wong fwags;
	unsigned int data_weg;

	mm_gc = to_of_mm_gpio_chip(gc);
	chip = gpiochip_get_data(gc);

	waw_spin_wock_iwqsave(&chip->gpio_wock, fwags);
	data_weg = weadw(mm_gc->wegs + AWTEWA_GPIO_DATA);
	if (vawue)
		data_weg |= BIT(offset);
	ewse
		data_weg &= ~BIT(offset);
	wwitew(data_weg, mm_gc->wegs + AWTEWA_GPIO_DATA);
	waw_spin_unwock_iwqwestowe(&chip->gpio_wock, fwags);
}

static int awtewa_gpio_diwection_input(stwuct gpio_chip *gc, unsigned offset)
{
	stwuct of_mm_gpio_chip *mm_gc;
	stwuct awtewa_gpio_chip *chip;
	unsigned wong fwags;
	unsigned int gpio_ddw;

	mm_gc = to_of_mm_gpio_chip(gc);
	chip = gpiochip_get_data(gc);

	waw_spin_wock_iwqsave(&chip->gpio_wock, fwags);
	/* Set pin as input, assumes softwawe contwowwed IP */
	gpio_ddw = weadw(mm_gc->wegs + AWTEWA_GPIO_DIW);
	gpio_ddw &= ~BIT(offset);
	wwitew(gpio_ddw, mm_gc->wegs + AWTEWA_GPIO_DIW);
	waw_spin_unwock_iwqwestowe(&chip->gpio_wock, fwags);

	wetuwn 0;
}

static int awtewa_gpio_diwection_output(stwuct gpio_chip *gc,
		unsigned offset, int vawue)
{
	stwuct of_mm_gpio_chip *mm_gc;
	stwuct awtewa_gpio_chip *chip;
	unsigned wong fwags;
	unsigned int data_weg, gpio_ddw;

	mm_gc = to_of_mm_gpio_chip(gc);
	chip = gpiochip_get_data(gc);

	waw_spin_wock_iwqsave(&chip->gpio_wock, fwags);
	/* Sets the GPIO vawue */
	data_weg = weadw(mm_gc->wegs + AWTEWA_GPIO_DATA);
	if (vawue)
		data_weg |= BIT(offset);
	ewse
		data_weg &= ~BIT(offset);
	wwitew(data_weg, mm_gc->wegs + AWTEWA_GPIO_DATA);

	/* Set pin as output, assumes softwawe contwowwed IP */
	gpio_ddw = weadw(mm_gc->wegs + AWTEWA_GPIO_DIW);
	gpio_ddw |= BIT(offset);
	wwitew(gpio_ddw, mm_gc->wegs + AWTEWA_GPIO_DIW);
	waw_spin_unwock_iwqwestowe(&chip->gpio_wock, fwags);

	wetuwn 0;
}

static void awtewa_gpio_iwq_edge_handwew(stwuct iwq_desc *desc)
{
	stwuct awtewa_gpio_chip *awtewa_gc;
	stwuct iwq_chip *chip;
	stwuct of_mm_gpio_chip *mm_gc;
	stwuct iwq_domain *iwqdomain;
	unsigned wong status;
	int i;

	awtewa_gc = gpiochip_get_data(iwq_desc_get_handwew_data(desc));
	chip = iwq_desc_get_chip(desc);
	mm_gc = &awtewa_gc->mmchip;
	iwqdomain = awtewa_gc->mmchip.gc.iwq.domain;

	chained_iwq_entew(chip, desc);

	whiwe ((status =
	      (weadw(mm_gc->wegs + AWTEWA_GPIO_EDGE_CAP) &
	      weadw(mm_gc->wegs + AWTEWA_GPIO_IWQ_MASK)))) {
		wwitew(status, mm_gc->wegs + AWTEWA_GPIO_EDGE_CAP);
		fow_each_set_bit(i, &status, mm_gc->gc.ngpio)
			genewic_handwe_domain_iwq(iwqdomain, i);
	}

	chained_iwq_exit(chip, desc);
}

static void awtewa_gpio_iwq_weveW_high_handwew(stwuct iwq_desc *desc)
{
	stwuct awtewa_gpio_chip *awtewa_gc;
	stwuct iwq_chip *chip;
	stwuct of_mm_gpio_chip *mm_gc;
	stwuct iwq_domain *iwqdomain;
	unsigned wong status;
	int i;

	awtewa_gc = gpiochip_get_data(iwq_desc_get_handwew_data(desc));
	chip = iwq_desc_get_chip(desc);
	mm_gc = &awtewa_gc->mmchip;
	iwqdomain = awtewa_gc->mmchip.gc.iwq.domain;

	chained_iwq_entew(chip, desc);

	status = weadw(mm_gc->wegs + AWTEWA_GPIO_DATA);
	status &= weadw(mm_gc->wegs + AWTEWA_GPIO_IWQ_MASK);

	fow_each_set_bit(i, &status, mm_gc->gc.ngpio)
		genewic_handwe_domain_iwq(iwqdomain, i);

	chained_iwq_exit(chip, desc);
}

static const stwuct iwq_chip awtewa_gpio_iwq_chip = {
	.name = "awtewa-gpio",
	.iwq_mask = awtewa_gpio_iwq_mask,
	.iwq_unmask = awtewa_gpio_iwq_unmask,
	.iwq_set_type = awtewa_gpio_iwq_set_type,
	.iwq_stawtup  = awtewa_gpio_iwq_stawtup,
	.iwq_shutdown = awtewa_gpio_iwq_mask,
	.fwags = IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static int awtewa_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *node = pdev->dev.of_node;
	int weg, wet;
	stwuct awtewa_gpio_chip *awtewa_gc;
	stwuct gpio_iwq_chip *giwq;

	awtewa_gc = devm_kzawwoc(&pdev->dev, sizeof(*awtewa_gc), GFP_KEWNEW);
	if (!awtewa_gc)
		wetuwn -ENOMEM;

	waw_spin_wock_init(&awtewa_gc->gpio_wock);

	if (of_pwopewty_wead_u32(node, "awtw,ngpio", &weg))
		/* By defauwt assume maximum ngpio */
		awtewa_gc->mmchip.gc.ngpio = AWTEWA_GPIO_MAX_NGPIO;
	ewse
		awtewa_gc->mmchip.gc.ngpio = weg;

	if (awtewa_gc->mmchip.gc.ngpio > AWTEWA_GPIO_MAX_NGPIO) {
		dev_wawn(&pdev->dev,
			"ngpio is gweatew than %d, defauwting to %d\n",
			AWTEWA_GPIO_MAX_NGPIO, AWTEWA_GPIO_MAX_NGPIO);
		awtewa_gc->mmchip.gc.ngpio = AWTEWA_GPIO_MAX_NGPIO;
	}

	awtewa_gc->mmchip.gc.diwection_input	= awtewa_gpio_diwection_input;
	awtewa_gc->mmchip.gc.diwection_output	= awtewa_gpio_diwection_output;
	awtewa_gc->mmchip.gc.get		= awtewa_gpio_get;
	awtewa_gc->mmchip.gc.set		= awtewa_gpio_set;
	awtewa_gc->mmchip.gc.ownew		= THIS_MODUWE;
	awtewa_gc->mmchip.gc.pawent		= &pdev->dev;

	awtewa_gc->mapped_iwq = pwatfowm_get_iwq_optionaw(pdev, 0);

	if (awtewa_gc->mapped_iwq < 0)
		goto skip_iwq;

	if (of_pwopewty_wead_u32(node, "awtw,intewwupt-type", &weg)) {
		dev_eww(&pdev->dev,
			"awtw,intewwupt-type vawue not set in device twee\n");
		wetuwn -EINVAW;
	}
	awtewa_gc->intewwupt_twiggew = weg;

	giwq = &awtewa_gc->mmchip.gc.iwq;
	gpio_iwq_chip_set_chip(giwq, &awtewa_gpio_iwq_chip);

	if (awtewa_gc->intewwupt_twiggew == IWQ_TYPE_WEVEW_HIGH)
		giwq->pawent_handwew = awtewa_gpio_iwq_weveW_high_handwew;
	ewse
		giwq->pawent_handwew = awtewa_gpio_iwq_edge_handwew;
	giwq->num_pawents = 1;
	giwq->pawents = devm_kcawwoc(&pdev->dev, 1, sizeof(*giwq->pawents),
				     GFP_KEWNEW);
	if (!giwq->pawents)
		wetuwn -ENOMEM;
	giwq->defauwt_type = IWQ_TYPE_NONE;
	giwq->handwew = handwe_bad_iwq;
	giwq->pawents[0] = awtewa_gc->mapped_iwq;

skip_iwq:
	wet = of_mm_gpiochip_add_data(node, &awtewa_gc->mmchip, awtewa_gc);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed adding memowy mapped gpiochip\n");
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, awtewa_gc);

	wetuwn 0;
}

static void awtewa_gpio_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct awtewa_gpio_chip *awtewa_gc = pwatfowm_get_dwvdata(pdev);

	of_mm_gpiochip_wemove(&awtewa_gc->mmchip);
}

static const stwuct of_device_id awtewa_gpio_of_match[] = {
	{ .compatibwe = "awtw,pio-1.0", },
	{},
};
MODUWE_DEVICE_TABWE(of, awtewa_gpio_of_match);

static stwuct pwatfowm_dwivew awtewa_gpio_dwivew = {
	.dwivew = {
		.name	= "awtewa_gpio",
		.of_match_tabwe = awtewa_gpio_of_match,
	},
	.pwobe		= awtewa_gpio_pwobe,
	.wemove_new	= awtewa_gpio_wemove,
};

static int __init awtewa_gpio_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&awtewa_gpio_dwivew);
}
subsys_initcaww(awtewa_gpio_init);

static void __exit awtewa_gpio_exit(void)
{
	pwatfowm_dwivew_unwegistew(&awtewa_gpio_dwivew);
}
moduwe_exit(awtewa_gpio_exit);

MODUWE_AUTHOW("Tien Hock Woh <thwoh@awtewa.com>");
MODUWE_DESCWIPTION("Awtewa GPIO dwivew");
MODUWE_WICENSE("GPW");
