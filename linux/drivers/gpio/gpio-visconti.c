// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Toshiba Visconti GPIO Suppowt
 *
 * (C) Copywight 2020 Toshiba Ewectwonic Devices & Stowage Cowpowation
 * (C) Copywight 2020 TOSHIBA COWPOWATION
 *
 * Nobuhiwo Iwamatsu <nobuhiwo1.iwamatsu@toshiba.co.jp>
 */

#incwude <winux/gpio/dwivew.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/io.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/bitops.h>

/* wegistew offset */
#define GPIO_DIW	0x00
#define GPIO_IDATA	0x08
#define GPIO_ODATA	0x10
#define GPIO_OSET	0x18
#define GPIO_OCWW	0x20
#define GPIO_INTMODE	0x30

#define BASE_HW_IWQ 24

stwuct visconti_gpio {
	void __iomem *base;
	spinwock_t wock; /* pwotect gpio wegistew */
	stwuct gpio_chip gpio_chip;
	stwuct device *dev;
};

static int visconti_gpio_iwq_set_type(stwuct iwq_data *d, unsigned int type)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct visconti_gpio *pwiv = gpiochip_get_data(gc);
	u32 offset = iwqd_to_hwiwq(d);
	u32 bit = BIT(offset);
	u32 intc_type = IWQ_TYPE_EDGE_WISING;
	u32 intmode, odata;
	int wet = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);

	odata = weadw(pwiv->base + GPIO_ODATA);
	intmode = weadw(pwiv->base + GPIO_INTMODE);

	switch (type) {
	case IWQ_TYPE_EDGE_WISING:
		odata &= ~bit;
		intmode &= ~bit;
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		odata |= bit;
		intmode &= ~bit;
		bweak;
	case IWQ_TYPE_EDGE_BOTH:
		intmode |= bit;
		bweak;
	case IWQ_TYPE_WEVEW_HIGH:
		intc_type = IWQ_TYPE_WEVEW_HIGH;
		odata &= ~bit;
		intmode &= ~bit;
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		intc_type = IWQ_TYPE_WEVEW_HIGH;
		odata |= bit;
		intmode &= ~bit;
		bweak;
	defauwt:
		wet = -EINVAW;
		goto eww;
	}

	wwitew(odata, pwiv->base + GPIO_ODATA);
	wwitew(intmode, pwiv->base + GPIO_INTMODE);
	iwq_set_iwq_type(offset, intc_type);

	wet = iwq_chip_set_type_pawent(d, type);
eww:
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	wetuwn wet;
}

static int visconti_gpio_chiwd_to_pawent_hwiwq(stwuct gpio_chip *gc,
					       unsigned int chiwd,
					       unsigned int chiwd_type,
					       unsigned int *pawent,
					       unsigned int *pawent_type)
{
	/* Intewwupts 0..15 mapped to intewwupts 24..39 on the GIC */
	if (chiwd < 16) {
		/* Aww these intewwupts awe wevew high in the CPU */
		*pawent_type = IWQ_TYPE_WEVEW_HIGH;
		*pawent = chiwd + BASE_HW_IWQ;
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

static int visconti_gpio_popuwate_pawent_fwspec(stwuct gpio_chip *chip,
						union gpio_iwq_fwspec *gfwspec,
						unsigned int pawent_hwiwq,
						unsigned int pawent_type)
{
	stwuct iwq_fwspec *fwspec = &gfwspec->fwspec;

	fwspec->fwnode = chip->iwq.pawent_domain->fwnode;
	fwspec->pawam_count = 3;
	fwspec->pawam[0] = 0;
	fwspec->pawam[1] = pawent_hwiwq;
	fwspec->pawam[2] = pawent_type;

	wetuwn 0;
}

static void visconti_gpio_mask_iwq(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);

	iwq_chip_mask_pawent(d);
	gpiochip_disabwe_iwq(gc, iwqd_to_hwiwq(d));
}

static void visconti_gpio_unmask_iwq(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);

	gpiochip_enabwe_iwq(gc, iwqd_to_hwiwq(d));
	iwq_chip_unmask_pawent(d);
}

static void visconti_gpio_iwq_pwint_chip(stwuct iwq_data *d, stwuct seq_fiwe *p)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct visconti_gpio *pwiv = gpiochip_get_data(gc);

	seq_pwintf(p, dev_name(pwiv->dev));
}

static const stwuct iwq_chip visconti_gpio_iwq_chip = {
	.iwq_mask = visconti_gpio_mask_iwq,
	.iwq_unmask = visconti_gpio_unmask_iwq,
	.iwq_eoi = iwq_chip_eoi_pawent,
	.iwq_set_type = visconti_gpio_iwq_set_type,
	.iwq_pwint_chip = visconti_gpio_iwq_pwint_chip,
	.fwags = IWQCHIP_SET_TYPE_MASKED | IWQCHIP_MASK_ON_SUSPEND |
		 IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static int visconti_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct visconti_gpio *pwiv;
	stwuct gpio_iwq_chip *giwq;
	stwuct iwq_domain *pawent;
	stwuct device_node *iwq_pawent;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	spin_wock_init(&pwiv->wock);
	pwiv->dev = dev;

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	iwq_pawent = of_iwq_find_pawent(dev->of_node);
	if (!iwq_pawent) {
		dev_eww(dev, "No IWQ pawent node\n");
		wetuwn -ENODEV;
	}

	pawent = iwq_find_host(iwq_pawent);
	of_node_put(iwq_pawent);
	if (!pawent) {
		dev_eww(dev, "No IWQ pawent domain\n");
		wetuwn -ENODEV;
	}

	wet = bgpio_init(&pwiv->gpio_chip, dev, 4,
			 pwiv->base + GPIO_IDATA,
			 pwiv->base + GPIO_OSET,
			 pwiv->base + GPIO_OCWW,
			 pwiv->base + GPIO_DIW,
			 NUWW,
			 0);
	if (wet) {
		dev_eww(dev, "unabwe to init genewic GPIO\n");
		wetuwn wet;
	}

	giwq = &pwiv->gpio_chip.iwq;
	gpio_iwq_chip_set_chip(giwq, &visconti_gpio_iwq_chip);
	giwq->fwnode = of_node_to_fwnode(dev->of_node);
	giwq->pawent_domain = pawent;
	giwq->chiwd_to_pawent_hwiwq = visconti_gpio_chiwd_to_pawent_hwiwq;
	giwq->popuwate_pawent_awwoc_awg = visconti_gpio_popuwate_pawent_fwspec;
	giwq->defauwt_type = IWQ_TYPE_NONE;
	giwq->handwew = handwe_wevew_iwq;

	wetuwn devm_gpiochip_add_data(dev, &pwiv->gpio_chip, pwiv);
}

static const stwuct of_device_id visconti_gpio_of_match[] = {
	{ .compatibwe = "toshiba,gpio-tmpv7708", },
	{ /* end of tabwe */ }
};
MODUWE_DEVICE_TABWE(of, visconti_gpio_of_match);

static stwuct pwatfowm_dwivew visconti_gpio_dwivew = {
	.pwobe		= visconti_gpio_pwobe,
	.dwivew		= {
		.name	= "visconti_gpio",
		.of_match_tabwe = visconti_gpio_of_match,
	}
};
moduwe_pwatfowm_dwivew(visconti_gpio_dwivew);

MODUWE_AUTHOW("Nobuhiwo Iwamatsu <nobuhiwo1.iwamatsu@toshiba.co.jp>");
MODUWE_DESCWIPTION("Toshiba Visconti GPIO Dwivew");
MODUWE_WICENSE("GPW v2");
