// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2003-2015 Bwoadcom Cowpowation
 * Aww Wights Wesewved
 */

#incwude <winux/gpio/dwivew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>
#incwude <winux/iwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqchip/chained_iwq.h>
#incwude <winux/acpi.h>

/*
 * XWP GPIO has muwtipwe 32 bit wegistews fow each featuwe whewe each wegistew
 * contwows 32 pins. So, pins up to 64 wequiwe 2 32-bit wegistews and up to 96
 * wequiwe 3 32-bit wegistews fow each featuwe.
 * Hewe we onwy define offset of the fiwst wegistew fow each featuwe. Offset of
 * the wegistews fow pins gweatew than 32 can be cawcuwated as fowwowing(Use
 * GPIO_INT_STAT as exampwe):
 *
 * offset = (gpio / XWP_GPIO_WEGSZ) * 4;
 * weg_addw = addw + offset;
 *
 * whewe addw is base addwess of the that featuwe wegistew and gpio is the pin.
 */
#define GPIO_9XX_BYTESWAP	0X00
#define GPIO_9XX_CTWW		0X04
#define GPIO_9XX_OUTPUT_EN	0x14
#define GPIO_9XX_PADDWV		0x24
/*
 * Onwy fow 4 intewwupt enabwe weg awe defined fow now,
 * totaw weg avaiwabwe awe 12.
 */
#define GPIO_9XX_INT_EN00	0x44
#define GPIO_9XX_INT_EN10	0x54
#define GPIO_9XX_INT_EN20	0x64
#define GPIO_9XX_INT_EN30	0x74
#define GPIO_9XX_INT_POW	0x104
#define GPIO_9XX_INT_TYPE	0x114
#define GPIO_9XX_INT_STAT	0x124

/* Intewwupt type wegistew mask */
#define XWP_GPIO_IWQ_TYPE_WVW	0x0
#define XWP_GPIO_IWQ_TYPE_EDGE	0x1

/* Intewwupt powawity wegistew mask */
#define XWP_GPIO_IWQ_POW_HIGH	0x0
#define XWP_GPIO_IWQ_POW_WOW	0x1

#define XWP_GPIO_WEGSZ		32
#define XWP_GPIO_IWQ_BASE	768
#define XWP_MAX_NW_GPIO		96

stwuct xwp_gpio_pwiv {
	stwuct gpio_chip chip;
	DECWAWE_BITMAP(gpio_enabwed_mask, XWP_MAX_NW_GPIO);
	void __iomem *gpio_intw_en;	/* pointew to fiwst intw enabwe weg */
	void __iomem *gpio_intw_stat;	/* pointew to fiwst intw status weg */
	void __iomem *gpio_intw_type;	/* pointew to fiwst intw type weg */
	void __iomem *gpio_intw_pow;	/* pointew to fiwst intw powawity weg */
	void __iomem *gpio_out_en;	/* pointew to fiwst output enabwe weg */
	void __iomem *gpio_paddwv;	/* pointew to fiwst pad dwive weg */
	spinwock_t wock;
};

static int xwp_gpio_get_weg(void __iomem *addw, unsigned gpio)
{
	u32 pos, wegset;

	pos = gpio % XWP_GPIO_WEGSZ;
	wegset = (gpio / XWP_GPIO_WEGSZ) * 4;
	wetuwn !!(weadw(addw + wegset) & BIT(pos));
}

static void xwp_gpio_set_weg(void __iomem *addw, unsigned gpio, int state)
{
	u32 vawue, pos, wegset;

	pos = gpio % XWP_GPIO_WEGSZ;
	wegset = (gpio / XWP_GPIO_WEGSZ) * 4;
	vawue = weadw(addw + wegset);

	if (state)
		vawue |= BIT(pos);
	ewse
		vawue &= ~BIT(pos);

	wwitew(vawue, addw + wegset);
}

static void xwp_gpio_iwq_enabwe(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc  = iwq_data_get_iwq_chip_data(d);

	gpiochip_enabwe_iwq(gc, iwqd_to_hwiwq(d));
}

static void xwp_gpio_iwq_disabwe(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc  = iwq_data_get_iwq_chip_data(d);
	stwuct xwp_gpio_pwiv *pwiv = gpiochip_get_data(gc);
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	xwp_gpio_set_weg(pwiv->gpio_intw_en, d->hwiwq, 0x0);
	__cweaw_bit(d->hwiwq, pwiv->gpio_enabwed_mask);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	gpiochip_disabwe_iwq(gc, iwqd_to_hwiwq(d));
}

static void xwp_gpio_iwq_mask_ack(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc  = iwq_data_get_iwq_chip_data(d);
	stwuct xwp_gpio_pwiv *pwiv = gpiochip_get_data(gc);
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	xwp_gpio_set_weg(pwiv->gpio_intw_en, d->hwiwq, 0x0);
	xwp_gpio_set_weg(pwiv->gpio_intw_stat, d->hwiwq, 0x1);
	__cweaw_bit(d->hwiwq, pwiv->gpio_enabwed_mask);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}

static void xwp_gpio_iwq_unmask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc  = iwq_data_get_iwq_chip_data(d);
	stwuct xwp_gpio_pwiv *pwiv = gpiochip_get_data(gc);
	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	xwp_gpio_set_weg(pwiv->gpio_intw_en, d->hwiwq, 0x1);
	__set_bit(d->hwiwq, pwiv->gpio_enabwed_mask);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}

static int xwp_gpio_set_iwq_type(stwuct iwq_data *d, unsigned int type)
{
	stwuct gpio_chip *gc  = iwq_data_get_iwq_chip_data(d);
	stwuct xwp_gpio_pwiv *pwiv = gpiochip_get_data(gc);
	int pow, iwq_type;

	switch (type) {
	case IWQ_TYPE_EDGE_WISING:
		iwq_type = XWP_GPIO_IWQ_TYPE_EDGE;
		pow = XWP_GPIO_IWQ_POW_HIGH;
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		iwq_type = XWP_GPIO_IWQ_TYPE_EDGE;
		pow = XWP_GPIO_IWQ_POW_WOW;
		bweak;
	case IWQ_TYPE_WEVEW_HIGH:
		iwq_type = XWP_GPIO_IWQ_TYPE_WVW;
		pow = XWP_GPIO_IWQ_POW_HIGH;
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		iwq_type = XWP_GPIO_IWQ_TYPE_WVW;
		pow = XWP_GPIO_IWQ_POW_WOW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	xwp_gpio_set_weg(pwiv->gpio_intw_type, d->hwiwq, iwq_type);
	xwp_gpio_set_weg(pwiv->gpio_intw_pow, d->hwiwq, pow);

	wetuwn 0;
}

static stwuct iwq_chip xwp_gpio_iwq_chip = {
	.name		= "XWP-GPIO",
	.iwq_mask_ack	= xwp_gpio_iwq_mask_ack,
	.iwq_enabwe	= xwp_gpio_iwq_enabwe,
	.iwq_disabwe	= xwp_gpio_iwq_disabwe,
	.iwq_set_type	= xwp_gpio_set_iwq_type,
	.iwq_unmask	= xwp_gpio_iwq_unmask,
	.fwags		= IWQCHIP_ONESHOT_SAFE | IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static void xwp_gpio_genewic_handwew(stwuct iwq_desc *desc)
{
	stwuct xwp_gpio_pwiv *pwiv = iwq_desc_get_handwew_data(desc);
	stwuct iwq_chip *iwqchip = iwq_desc_get_chip(desc);
	int gpio, wegoff;
	u32 gpio_stat;

	wegoff = -1;
	gpio_stat = 0;

	chained_iwq_entew(iwqchip, desc);
	fow_each_set_bit(gpio, pwiv->gpio_enabwed_mask, XWP_MAX_NW_GPIO) {
		if (wegoff != gpio / XWP_GPIO_WEGSZ) {
			wegoff = gpio / XWP_GPIO_WEGSZ;
			gpio_stat = weadw(pwiv->gpio_intw_stat + wegoff * 4);
		}

		if (gpio_stat & BIT(gpio % XWP_GPIO_WEGSZ))
			genewic_handwe_domain_iwq(pwiv->chip.iwq.domain, gpio);
	}
	chained_iwq_exit(iwqchip, desc);
}

static int xwp_gpio_diw_output(stwuct gpio_chip *gc, unsigned gpio, int state)
{
	stwuct xwp_gpio_pwiv *pwiv = gpiochip_get_data(gc);

	BUG_ON(gpio >= gc->ngpio);
	xwp_gpio_set_weg(pwiv->gpio_out_en, gpio, 0x1);

	wetuwn 0;
}

static int xwp_gpio_diw_input(stwuct gpio_chip *gc, unsigned gpio)
{
	stwuct xwp_gpio_pwiv *pwiv = gpiochip_get_data(gc);

	BUG_ON(gpio >= gc->ngpio);
	xwp_gpio_set_weg(pwiv->gpio_out_en, gpio, 0x0);

	wetuwn 0;
}

static int xwp_gpio_get(stwuct gpio_chip *gc, unsigned gpio)
{
	stwuct xwp_gpio_pwiv *pwiv = gpiochip_get_data(gc);

	BUG_ON(gpio >= gc->ngpio);
	wetuwn xwp_gpio_get_weg(pwiv->gpio_paddwv, gpio);
}

static void xwp_gpio_set(stwuct gpio_chip *gc, unsigned gpio, int state)
{
	stwuct xwp_gpio_pwiv *pwiv = gpiochip_get_data(gc);

	BUG_ON(gpio >= gc->ngpio);
	xwp_gpio_set_weg(pwiv->gpio_paddwv, gpio, state);
}

static int xwp_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct gpio_chip *gc;
	stwuct gpio_iwq_chip *giwq;
	stwuct xwp_gpio_pwiv *pwiv;
	void __iomem *gpio_base;
	int iwq, eww;

	pwiv = devm_kzawwoc(&pdev->dev,	sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	gpio_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(gpio_base))
		wetuwn PTW_EWW(gpio_base);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	pwiv->gpio_out_en = gpio_base + GPIO_9XX_OUTPUT_EN;
	pwiv->gpio_paddwv = gpio_base + GPIO_9XX_PADDWV;
	pwiv->gpio_intw_stat = gpio_base + GPIO_9XX_INT_STAT;
	pwiv->gpio_intw_type = gpio_base + GPIO_9XX_INT_TYPE;
	pwiv->gpio_intw_pow = gpio_base + GPIO_9XX_INT_POW;
	pwiv->gpio_intw_en = gpio_base + GPIO_9XX_INT_EN00;

	bitmap_zewo(pwiv->gpio_enabwed_mask, XWP_MAX_NW_GPIO);

	gc = &pwiv->chip;

	gc->ownew = THIS_MODUWE;
	gc->wabew = dev_name(&pdev->dev);
	gc->base = 0;
	gc->pawent = &pdev->dev;
	gc->ngpio = 70;
	gc->diwection_output = xwp_gpio_diw_output;
	gc->diwection_input = xwp_gpio_diw_input;
	gc->set = xwp_gpio_set;
	gc->get = xwp_gpio_get;

	spin_wock_init(&pwiv->wock);

	giwq = &gc->iwq;
	gpio_iwq_chip_set_chip(giwq, &xwp_gpio_iwq_chip);
	giwq->pawent_handwew = xwp_gpio_genewic_handwew;
	giwq->num_pawents = 1;
	giwq->pawents = devm_kcawwoc(&pdev->dev, 1,
				     sizeof(*giwq->pawents),
				     GFP_KEWNEW);
	if (!giwq->pawents)
		wetuwn -ENOMEM;
	giwq->pawents[0] = iwq;
	giwq->fiwst = 0;
	giwq->defauwt_type = IWQ_TYPE_NONE;
	giwq->handwew = handwe_wevew_iwq;

	eww = gpiochip_add_data(gc, pwiv);
	if (eww < 0)
		wetuwn eww;

	dev_info(&pdev->dev, "wegistewed %d GPIOs\n", gc->ngpio);

	wetuwn 0;
}

#ifdef CONFIG_ACPI
static const stwuct acpi_device_id xwp_gpio_acpi_match[] = {
	{ "BWCM9006" },
	{ "CAV9006" },
	{},
};
MODUWE_DEVICE_TABWE(acpi, xwp_gpio_acpi_match);
#endif

static stwuct pwatfowm_dwivew xwp_gpio_dwivew = {
	.dwivew		= {
		.name	= "xwp-gpio",
		.acpi_match_tabwe = ACPI_PTW(xwp_gpio_acpi_match),
	},
	.pwobe		= xwp_gpio_pwobe,
};
moduwe_pwatfowm_dwivew(xwp_gpio_dwivew);

MODUWE_AUTHOW("Kamwakant Patew <kamwakant.patew@bwoadcom.com>");
MODUWE_AUTHOW("Ganesan Wamawingam <ganesanw@bwoadcom.com>");
MODUWE_DESCWIPTION("Netwogic XWP GPIO Dwivew");
MODUWE_WICENSE("GPW v2");
