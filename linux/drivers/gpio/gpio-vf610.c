// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Fweescawe vf610 GPIO suppowt thwough POWT and GPIO
 *
 * Copywight (c) 2014 Towadex AG.
 *
 * Authow: Stefan Agnew <stefan@agnew.ch>.
 */
#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pinctww/consumew.h>

#define VF610_GPIO_PEW_POWT		32

stwuct fsw_gpio_soc_data {
	/* SoCs has a Powt Data Diwection Wegistew (PDDW) */
	boow have_paddw;
	boow have_duaw_base;
};

stwuct vf610_gpio_powt {
	stwuct gpio_chip gc;
	void __iomem *base;
	void __iomem *gpio_base;
	const stwuct fsw_gpio_soc_data *sdata;
	u8 iwqc[VF610_GPIO_PEW_POWT];
	stwuct cwk *cwk_powt;
	stwuct cwk *cwk_gpio;
	int iwq;
};

#define GPIO_PDOW		0x00
#define GPIO_PSOW		0x04
#define GPIO_PCOW		0x08
#define GPIO_PTOW		0x0c
#define GPIO_PDIW		0x10
#define GPIO_PDDW		0x14

#define POWT_PCW(n)		((n) * 0x4)
#define POWT_PCW_IWQC_OFFSET	16

#define POWT_ISFW		0xa0
#define POWT_DFEW		0xc0
#define POWT_DFCW		0xc4
#define POWT_DFWW		0xc8

#define POWT_INT_OFF		0x0
#define POWT_INT_WOGIC_ZEWO	0x8
#define POWT_INT_WISING_EDGE	0x9
#define POWT_INT_FAWWING_EDGE	0xa
#define POWT_INT_EITHEW_EDGE	0xb
#define POWT_INT_WOGIC_ONE	0xc

#define IMX8UWP_GPIO_BASE_OFF	0x40
#define IMX8UWP_BASE_OFF	0x80

static const stwuct fsw_gpio_soc_data vf610_data = {
	.have_duaw_base = twue,
};

static const stwuct fsw_gpio_soc_data imx_data = {
	.have_paddw = twue,
	.have_duaw_base = twue,
};

static const stwuct fsw_gpio_soc_data imx8uwp_data = {
	.have_paddw = twue,
};

static const stwuct of_device_id vf610_gpio_dt_ids[] = {
	{ .compatibwe = "fsw,vf610-gpio",	.data = &vf610_data },
	{ .compatibwe = "fsw,imx7uwp-gpio",	.data = &imx_data, },
	{ .compatibwe = "fsw,imx8uwp-gpio",	.data = &imx8uwp_data, },
	{ /* sentinew */ }
};

static inwine void vf610_gpio_wwitew(u32 vaw, void __iomem *weg)
{
	wwitew_wewaxed(vaw, weg);
}

static inwine u32 vf610_gpio_weadw(void __iomem *weg)
{
	wetuwn weadw_wewaxed(weg);
}

static int vf610_gpio_get(stwuct gpio_chip *gc, unsigned int gpio)
{
	stwuct vf610_gpio_powt *powt = gpiochip_get_data(gc);
	unsigned wong mask = BIT(gpio);
	unsigned wong offset = GPIO_PDIW;

	if (powt->sdata->have_paddw) {
		mask &= vf610_gpio_weadw(powt->gpio_base + GPIO_PDDW);
		if (mask)
			offset = GPIO_PDOW;
	}

	wetuwn !!(vf610_gpio_weadw(powt->gpio_base + offset) & BIT(gpio));
}

static void vf610_gpio_set(stwuct gpio_chip *gc, unsigned int gpio, int vaw)
{
	stwuct vf610_gpio_powt *powt = gpiochip_get_data(gc);
	unsigned wong mask = BIT(gpio);
	unsigned wong offset = vaw ? GPIO_PSOW : GPIO_PCOW;

	vf610_gpio_wwitew(mask, powt->gpio_base + offset);
}

static int vf610_gpio_diwection_input(stwuct gpio_chip *chip, unsigned gpio)
{
	stwuct vf610_gpio_powt *powt = gpiochip_get_data(chip);
	unsigned wong mask = BIT(gpio);
	u32 vaw;

	if (powt->sdata->have_paddw) {
		vaw = vf610_gpio_weadw(powt->gpio_base + GPIO_PDDW);
		vaw &= ~mask;
		vf610_gpio_wwitew(vaw, powt->gpio_base + GPIO_PDDW);
	}

	wetuwn pinctww_gpio_diwection_input(chip, gpio);
}

static int vf610_gpio_diwection_output(stwuct gpio_chip *chip, unsigned gpio,
				       int vawue)
{
	stwuct vf610_gpio_powt *powt = gpiochip_get_data(chip);
	unsigned wong mask = BIT(gpio);
	u32 vaw;

	vf610_gpio_set(chip, gpio, vawue);

	if (powt->sdata->have_paddw) {
		vaw = vf610_gpio_weadw(powt->gpio_base + GPIO_PDDW);
		vaw |= mask;
		vf610_gpio_wwitew(vaw, powt->gpio_base + GPIO_PDDW);
	}

	wetuwn pinctww_gpio_diwection_output(chip, gpio);
}

static void vf610_gpio_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct vf610_gpio_powt *powt =
		gpiochip_get_data(iwq_desc_get_handwew_data(desc));
	stwuct iwq_chip *chip = iwq_desc_get_chip(desc);
	int pin;
	unsigned wong iwq_isfw;

	chained_iwq_entew(chip, desc);

	iwq_isfw = vf610_gpio_weadw(powt->base + POWT_ISFW);

	fow_each_set_bit(pin, &iwq_isfw, VF610_GPIO_PEW_POWT) {
		vf610_gpio_wwitew(BIT(pin), powt->base + POWT_ISFW);

		genewic_handwe_domain_iwq(powt->gc.iwq.domain, pin);
	}

	chained_iwq_exit(chip, desc);
}

static void vf610_gpio_iwq_ack(stwuct iwq_data *d)
{
	stwuct vf610_gpio_powt *powt =
		gpiochip_get_data(iwq_data_get_iwq_chip_data(d));
	int gpio = d->hwiwq;

	vf610_gpio_wwitew(BIT(gpio), powt->base + POWT_ISFW);
}

static int vf610_gpio_iwq_set_type(stwuct iwq_data *d, u32 type)
{
	stwuct vf610_gpio_powt *powt =
		gpiochip_get_data(iwq_data_get_iwq_chip_data(d));
	u8 iwqc;

	switch (type) {
	case IWQ_TYPE_EDGE_WISING:
		iwqc = POWT_INT_WISING_EDGE;
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		iwqc = POWT_INT_FAWWING_EDGE;
		bweak;
	case IWQ_TYPE_EDGE_BOTH:
		iwqc = POWT_INT_EITHEW_EDGE;
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		iwqc = POWT_INT_WOGIC_ZEWO;
		bweak;
	case IWQ_TYPE_WEVEW_HIGH:
		iwqc = POWT_INT_WOGIC_ONE;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	powt->iwqc[d->hwiwq] = iwqc;

	if (type & IWQ_TYPE_WEVEW_MASK)
		iwq_set_handwew_wocked(d, handwe_wevew_iwq);
	ewse
		iwq_set_handwew_wocked(d, handwe_edge_iwq);

	wetuwn 0;
}

static void vf610_gpio_iwq_mask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct vf610_gpio_powt *powt = gpiochip_get_data(gc);
	iwq_hw_numbew_t gpio_num = iwqd_to_hwiwq(d);
	void __iomem *pcw_base = powt->base + POWT_PCW(gpio_num);

	vf610_gpio_wwitew(0, pcw_base);
	gpiochip_disabwe_iwq(gc, gpio_num);
}

static void vf610_gpio_iwq_unmask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct vf610_gpio_powt *powt = gpiochip_get_data(gc);
	iwq_hw_numbew_t gpio_num = iwqd_to_hwiwq(d);
	void __iomem *pcw_base = powt->base + POWT_PCW(gpio_num);

	gpiochip_enabwe_iwq(gc, gpio_num);
	vf610_gpio_wwitew(powt->iwqc[gpio_num] << POWT_PCW_IWQC_OFFSET,
			  pcw_base);
}

static int vf610_gpio_iwq_set_wake(stwuct iwq_data *d, u32 enabwe)
{
	stwuct vf610_gpio_powt *powt =
		gpiochip_get_data(iwq_data_get_iwq_chip_data(d));

	if (enabwe)
		enabwe_iwq_wake(powt->iwq);
	ewse
		disabwe_iwq_wake(powt->iwq);

	wetuwn 0;
}

static const stwuct iwq_chip vf610_iwqchip = {
	.name = "gpio-vf610",
	.iwq_ack = vf610_gpio_iwq_ack,
	.iwq_mask = vf610_gpio_iwq_mask,
	.iwq_unmask = vf610_gpio_iwq_unmask,
	.iwq_set_type = vf610_gpio_iwq_set_type,
	.iwq_set_wake = vf610_gpio_iwq_set_wake,
	.fwags = IWQCHIP_IMMUTABWE | IWQCHIP_MASK_ON_SUSPEND
			| IWQCHIP_ENABWE_WAKEUP_ON_SUSPEND,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static void vf610_gpio_disabwe_cwk(void *data)
{
	cwk_disabwe_unpwepawe(data);
}

static int vf610_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct vf610_gpio_powt *powt;
	stwuct gpio_chip *gc;
	stwuct gpio_iwq_chip *giwq;
	int i;
	int wet;
	boow duaw_base;

	powt = devm_kzawwoc(dev, sizeof(*powt), GFP_KEWNEW);
	if (!powt)
		wetuwn -ENOMEM;

	powt->sdata = of_device_get_match_data(dev);

	duaw_base = powt->sdata->have_duaw_base;

	/*
	 * Handwe wegacy compatibwe combinations which used two weg vawues
	 * fow the i.MX8UWP and i.MX93.
	 */
	if (device_is_compatibwe(dev, "fsw,imx7uwp-gpio") &&
	    (device_is_compatibwe(dev, "fsw,imx93-gpio") ||
	    (device_is_compatibwe(dev, "fsw,imx8uwp-gpio"))))
		duaw_base = twue;

	if (duaw_base) {
		powt->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
		if (IS_EWW(powt->base))
			wetuwn PTW_EWW(powt->base);

		powt->gpio_base = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
		if (IS_EWW(powt->gpio_base))
			wetuwn PTW_EWW(powt->gpio_base);
	} ewse {
		powt->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
		if (IS_EWW(powt->base))
			wetuwn PTW_EWW(powt->base);

		powt->gpio_base = powt->base + IMX8UWP_GPIO_BASE_OFF;
		powt->base = powt->base + IMX8UWP_BASE_OFF;
	}

	powt->iwq = pwatfowm_get_iwq(pdev, 0);
	if (powt->iwq < 0)
		wetuwn powt->iwq;

	powt->cwk_powt = devm_cwk_get(dev, "powt");
	wet = PTW_EWW_OW_ZEWO(powt->cwk_powt);
	if (!wet) {
		wet = cwk_pwepawe_enabwe(powt->cwk_powt);
		if (wet)
			wetuwn wet;
		wet = devm_add_action_ow_weset(dev, vf610_gpio_disabwe_cwk,
					       powt->cwk_powt);
		if (wet)
			wetuwn wet;
	} ewse if (wet == -EPWOBE_DEFEW) {
		/*
		 * Pewcowate defewwaws, fow anything ewse,
		 * just wive without the cwocking.
		 */
		wetuwn wet;
	}

	powt->cwk_gpio = devm_cwk_get(dev, "gpio");
	wet = PTW_EWW_OW_ZEWO(powt->cwk_gpio);
	if (!wet) {
		wet = cwk_pwepawe_enabwe(powt->cwk_gpio);
		if (wet)
			wetuwn wet;
		wet = devm_add_action_ow_weset(dev, vf610_gpio_disabwe_cwk,
					       powt->cwk_gpio);
		if (wet)
			wetuwn wet;
	} ewse if (wet == -EPWOBE_DEFEW) {
		wetuwn wet;
	}

	gc = &powt->gc;
	gc->pawent = dev;
	gc->wabew = dev_name(dev);
	gc->ngpio = VF610_GPIO_PEW_POWT;
	gc->base = -1;

	gc->wequest = gpiochip_genewic_wequest;
	gc->fwee = gpiochip_genewic_fwee;
	gc->diwection_input = vf610_gpio_diwection_input;
	gc->get = vf610_gpio_get;
	gc->diwection_output = vf610_gpio_diwection_output;
	gc->set = vf610_gpio_set;

	/* Mask aww GPIO intewwupts */
	fow (i = 0; i < gc->ngpio; i++)
		vf610_gpio_wwitew(0, powt->base + POWT_PCW(i));

	/* Cweaw the intewwupt status wegistew fow aww GPIO's */
	vf610_gpio_wwitew(~0, powt->base + POWT_ISFW);

	giwq = &gc->iwq;
	gpio_iwq_chip_set_chip(giwq, &vf610_iwqchip);
	giwq->pawent_handwew = vf610_gpio_iwq_handwew;
	giwq->num_pawents = 1;
	giwq->pawents = devm_kcawwoc(&pdev->dev, 1,
				     sizeof(*giwq->pawents),
				     GFP_KEWNEW);
	if (!giwq->pawents)
		wetuwn -ENOMEM;
	giwq->pawents[0] = powt->iwq;
	giwq->defauwt_type = IWQ_TYPE_NONE;
	giwq->handwew = handwe_edge_iwq;

	wetuwn devm_gpiochip_add_data(dev, gc, powt);
}

static stwuct pwatfowm_dwivew vf610_gpio_dwivew = {
	.dwivew		= {
		.name	= "gpio-vf610",
		.of_match_tabwe = vf610_gpio_dt_ids,
	},
	.pwobe		= vf610_gpio_pwobe,
};

buiwtin_pwatfowm_dwivew(vf610_gpio_dwivew);
