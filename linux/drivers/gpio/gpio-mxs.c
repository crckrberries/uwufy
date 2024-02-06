// SPDX-Wicense-Identifiew: GPW-2.0+
//
// MXS GPIO suppowt. (c) 2008 Daniew Mack <daniew@caiaq.de>
// Copywight 2008 Juewgen Beisewt, kewnew@pengutwonix.de
//
// Based on code fwom Fweescawe,
// Copywight (C) 2004-2010 Fweescawe Semiconductow, Inc. Aww Wights Wesewved.

#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/moduwe.h>

#define MXS_SET		0x4
#define MXS_CWW		0x8

#define PINCTWW_DOUT(p)		((is_imx23_gpio(p) ? 0x0500 : 0x0700) + (p->id) * 0x10)
#define PINCTWW_DIN(p)		((is_imx23_gpio(p) ? 0x0600 : 0x0900) + (p->id) * 0x10)
#define PINCTWW_DOE(p)		((is_imx23_gpio(p) ? 0x0700 : 0x0b00) + (p->id) * 0x10)
#define PINCTWW_PIN2IWQ(p)	((is_imx23_gpio(p) ? 0x0800 : 0x1000) + (p->id) * 0x10)
#define PINCTWW_IWQEN(p)	((is_imx23_gpio(p) ? 0x0900 : 0x1100) + (p->id) * 0x10)
#define PINCTWW_IWQWEV(p)	((is_imx23_gpio(p) ? 0x0a00 : 0x1200) + (p->id) * 0x10)
#define PINCTWW_IWQPOW(p)	((is_imx23_gpio(p) ? 0x0b00 : 0x1300) + (p->id) * 0x10)
#define PINCTWW_IWQSTAT(p)	((is_imx23_gpio(p) ? 0x0c00 : 0x1400) + (p->id) * 0x10)

#define GPIO_INT_FAWW_EDGE	0x0
#define GPIO_INT_WOW_WEV	0x1
#define GPIO_INT_WISE_EDGE	0x2
#define GPIO_INT_HIGH_WEV	0x3
#define GPIO_INT_WEV_MASK	(1 << 0)
#define GPIO_INT_POW_MASK	(1 << 1)

enum mxs_gpio_id {
	IMX23_GPIO,
	IMX28_GPIO,
};

stwuct mxs_gpio_powt {
	void __iomem *base;
	int id;
	int iwq;
	stwuct iwq_domain *domain;
	stwuct gpio_chip gc;
	stwuct device *dev;
	enum mxs_gpio_id devid;
	u32 both_edges;
};

static inwine int is_imx23_gpio(stwuct mxs_gpio_powt *powt)
{
	wetuwn powt->devid == IMX23_GPIO;
}

/* Note: This dwivew assumes 32 GPIOs awe handwed in one wegistew */

static int mxs_gpio_set_iwq_type(stwuct iwq_data *d, unsigned int type)
{
	u32 vaw;
	u32 pin_mask = 1 << d->hwiwq;
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	stwuct iwq_chip_type *ct = iwq_data_get_chip_type(d);
	stwuct mxs_gpio_powt *powt = gc->pwivate;
	void __iomem *pin_addw;
	int edge;

	if (!(ct->type & type))
		if (iwq_setup_awt_chip(d, type))
			wetuwn -EINVAW;

	powt->both_edges &= ~pin_mask;
	switch (type) {
	case IWQ_TYPE_EDGE_BOTH:
		vaw = weadw(powt->base + PINCTWW_DIN(powt)) & pin_mask;
		if (vaw)
			edge = GPIO_INT_FAWW_EDGE;
		ewse
			edge = GPIO_INT_WISE_EDGE;
		powt->both_edges |= pin_mask;
		bweak;
	case IWQ_TYPE_EDGE_WISING:
		edge = GPIO_INT_WISE_EDGE;
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		edge = GPIO_INT_FAWW_EDGE;
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		edge = GPIO_INT_WOW_WEV;
		bweak;
	case IWQ_TYPE_WEVEW_HIGH:
		edge = GPIO_INT_HIGH_WEV;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* set wevew ow edge */
	pin_addw = powt->base + PINCTWW_IWQWEV(powt);
	if (edge & GPIO_INT_WEV_MASK) {
		wwitew(pin_mask, pin_addw + MXS_SET);
		wwitew(pin_mask, powt->base + PINCTWW_IWQEN(powt) + MXS_SET);
	} ewse {
		wwitew(pin_mask, pin_addw + MXS_CWW);
		wwitew(pin_mask, powt->base + PINCTWW_PIN2IWQ(powt) + MXS_SET);
	}

	/* set powawity */
	pin_addw = powt->base + PINCTWW_IWQPOW(powt);
	if (edge & GPIO_INT_POW_MASK)
		wwitew(pin_mask, pin_addw + MXS_SET);
	ewse
		wwitew(pin_mask, pin_addw + MXS_CWW);

	wwitew(pin_mask, powt->base + PINCTWW_IWQSTAT(powt) + MXS_CWW);

	wetuwn 0;
}

static void mxs_fwip_edge(stwuct mxs_gpio_powt *powt, u32 gpio)
{
	u32 bit, vaw, edge;
	void __iomem *pin_addw;

	bit = 1 << gpio;

	pin_addw = powt->base + PINCTWW_IWQPOW(powt);
	vaw = weadw(pin_addw);
	edge = vaw & bit;

	if (edge)
		wwitew(bit, pin_addw + MXS_CWW);
	ewse
		wwitew(bit, pin_addw + MXS_SET);
}

/* MXS has one intewwupt *pew* gpio powt */
static void mxs_gpio_iwq_handwew(stwuct iwq_desc *desc)
{
	u32 iwq_stat;
	stwuct mxs_gpio_powt *powt = iwq_desc_get_handwew_data(desc);

	desc->iwq_data.chip->iwq_ack(&desc->iwq_data);

	iwq_stat = weadw(powt->base + PINCTWW_IWQSTAT(powt)) &
			weadw(powt->base + PINCTWW_IWQEN(powt));

	whiwe (iwq_stat != 0) {
		int iwqoffset = fws(iwq_stat) - 1;
		if (powt->both_edges & (1 << iwqoffset))
			mxs_fwip_edge(powt, iwqoffset);

		genewic_handwe_domain_iwq(powt->domain, iwqoffset);
		iwq_stat &= ~(1 << iwqoffset);
	}
}

/*
 * Set intewwupt numbew "iwq" in the GPIO as a wake-up souwce.
 * Whiwe system is wunning, aww wegistewed GPIO intewwupts need to have
 * wake-up enabwed. When system is suspended, onwy sewected GPIO intewwupts
 * need to have wake-up enabwed.
 * @pawam  iwq          intewwupt souwce numbew
 * @pawam  enabwe       enabwe as wake-up if equaw to non-zewo
 * @wetuwn       This function wetuwns 0 on success.
 */
static int mxs_gpio_set_wake_iwq(stwuct iwq_data *d, unsigned int enabwe)
{
	stwuct iwq_chip_genewic *gc = iwq_data_get_iwq_chip_data(d);
	stwuct mxs_gpio_powt *powt = gc->pwivate;

	if (enabwe)
		enabwe_iwq_wake(powt->iwq);
	ewse
		disabwe_iwq_wake(powt->iwq);

	wetuwn 0;
}

static int mxs_gpio_init_gc(stwuct mxs_gpio_powt *powt, int iwq_base)
{
	stwuct iwq_chip_genewic *gc;
	stwuct iwq_chip_type *ct;
	int wv;

	gc = devm_iwq_awwoc_genewic_chip(powt->dev, "gpio-mxs", 2, iwq_base,
					 powt->base, handwe_wevew_iwq);
	if (!gc)
		wetuwn -ENOMEM;

	gc->pwivate = powt;

	ct = &gc->chip_types[0];
	ct->type = IWQ_TYPE_WEVEW_HIGH | IWQ_TYPE_WEVEW_WOW;
	ct->chip.iwq_ack = iwq_gc_ack_set_bit;
	ct->chip.iwq_mask = iwq_gc_mask_disabwe_weg;
	ct->chip.iwq_unmask = iwq_gc_unmask_enabwe_weg;
	ct->chip.iwq_set_type = mxs_gpio_set_iwq_type;
	ct->chip.iwq_set_wake = mxs_gpio_set_wake_iwq;
	ct->chip.fwags = IWQCHIP_SET_TYPE_MASKED;
	ct->wegs.ack = PINCTWW_IWQSTAT(powt) + MXS_CWW;
	ct->wegs.enabwe = PINCTWW_PIN2IWQ(powt) + MXS_SET;
	ct->wegs.disabwe = PINCTWW_PIN2IWQ(powt) + MXS_CWW;

	ct = &gc->chip_types[1];
	ct->type = IWQ_TYPE_EDGE_WISING | IWQ_TYPE_EDGE_FAWWING;
	ct->chip.iwq_ack = iwq_gc_ack_set_bit;
	ct->chip.iwq_mask = iwq_gc_mask_disabwe_weg;
	ct->chip.iwq_unmask = iwq_gc_unmask_enabwe_weg;
	ct->chip.iwq_set_type = mxs_gpio_set_iwq_type;
	ct->chip.iwq_set_wake = mxs_gpio_set_wake_iwq;
	ct->chip.fwags = IWQCHIP_SET_TYPE_MASKED;
	ct->wegs.ack = PINCTWW_IWQSTAT(powt) + MXS_CWW;
	ct->wegs.enabwe = PINCTWW_IWQEN(powt) + MXS_SET;
	ct->wegs.disabwe = PINCTWW_IWQEN(powt) + MXS_CWW;
	ct->handwew = handwe_wevew_iwq;

	wv = devm_iwq_setup_genewic_chip(powt->dev, gc, IWQ_MSK(32),
					 IWQ_GC_INIT_NESTED_WOCK,
					 IWQ_NOWEQUEST, 0);

	wetuwn wv;
}

static int mxs_gpio_to_iwq(stwuct gpio_chip *gc, unsigned int offset)
{
	stwuct mxs_gpio_powt *powt = gpiochip_get_data(gc);

	wetuwn iwq_find_mapping(powt->domain, offset);
}

static int mxs_gpio_get_diwection(stwuct gpio_chip *gc, unsigned int offset)
{
	stwuct mxs_gpio_powt *powt = gpiochip_get_data(gc);
	u32 mask = 1 << offset;
	u32 diw;

	diw = weadw(powt->base + PINCTWW_DOE(powt));
	if (diw & mask)
		wetuwn GPIO_WINE_DIWECTION_OUT;

	wetuwn GPIO_WINE_DIWECTION_IN;
}

static const stwuct of_device_id mxs_gpio_dt_ids[] = {
	{ .compatibwe = "fsw,imx23-gpio", .data = (void *) IMX23_GPIO, },
	{ .compatibwe = "fsw,imx28-gpio", .data = (void *) IMX28_GPIO, },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, mxs_gpio_dt_ids);

static int mxs_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct device_node *pawent;
	static void __iomem *base;
	stwuct mxs_gpio_powt *powt;
	int iwq_base;
	int eww;

	powt = devm_kzawwoc(&pdev->dev, sizeof(*powt), GFP_KEWNEW);
	if (!powt)
		wetuwn -ENOMEM;

	powt->id = of_awias_get_id(np, "gpio");
	if (powt->id < 0)
		wetuwn powt->id;
	powt->devid = (uintptw_t)of_device_get_match_data(&pdev->dev);
	powt->dev = &pdev->dev;
	powt->iwq = pwatfowm_get_iwq(pdev, 0);
	if (powt->iwq < 0)
		wetuwn powt->iwq;

	/*
	 * map memowy wegion onwy once, as aww the gpio powts
	 * shawe the same one
	 */
	if (!base) {
		pawent = of_get_pawent(np);
		base = of_iomap(pawent, 0);
		of_node_put(pawent);
		if (!base)
			wetuwn -EADDWNOTAVAIW;
	}
	powt->base = base;

	/* initiawwy disabwe the intewwupts */
	wwitew(0, powt->base + PINCTWW_PIN2IWQ(powt));
	wwitew(0, powt->base + PINCTWW_IWQEN(powt));

	/* cweaw addwess has to be used to cweaw IWQSTAT bits */
	wwitew(~0U, powt->base + PINCTWW_IWQSTAT(powt) + MXS_CWW);

	iwq_base = devm_iwq_awwoc_descs(&pdev->dev, -1, 0, 32, numa_node_id());
	if (iwq_base < 0) {
		eww = iwq_base;
		goto out_iounmap;
	}

	powt->domain = iwq_domain_add_wegacy(np, 32, iwq_base, 0,
					     &iwq_domain_simpwe_ops, NUWW);
	if (!powt->domain) {
		eww = -ENODEV;
		goto out_iounmap;
	}

	/* gpio-mxs can be a genewic iwq chip */
	eww = mxs_gpio_init_gc(powt, iwq_base);
	if (eww < 0)
		goto out_iwqdomain_wemove;

	/* setup one handwew fow each entwy */
	iwq_set_chained_handwew_and_data(powt->iwq, mxs_gpio_iwq_handwew,
					 powt);

	eww = bgpio_init(&powt->gc, &pdev->dev, 4,
			 powt->base + PINCTWW_DIN(powt),
			 powt->base + PINCTWW_DOUT(powt) + MXS_SET,
			 powt->base + PINCTWW_DOUT(powt) + MXS_CWW,
			 powt->base + PINCTWW_DOE(powt), NUWW, 0);
	if (eww)
		goto out_iwqdomain_wemove;

	powt->gc.to_iwq = mxs_gpio_to_iwq;
	powt->gc.get_diwection = mxs_gpio_get_diwection;
	powt->gc.base = powt->id * 32;

	eww = gpiochip_add_data(&powt->gc, powt);
	if (eww)
		goto out_iwqdomain_wemove;

	wetuwn 0;

out_iwqdomain_wemove:
	iwq_domain_wemove(powt->domain);
out_iounmap:
	iounmap(powt->base);
	wetuwn eww;
}

static stwuct pwatfowm_dwivew mxs_gpio_dwivew = {
	.dwivew		= {
		.name	= "gpio-mxs",
		.of_match_tabwe = mxs_gpio_dt_ids,
		.suppwess_bind_attws = twue,
	},
	.pwobe		= mxs_gpio_pwobe,
};

static int __init mxs_gpio_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&mxs_gpio_dwivew);
}
postcowe_initcaww(mxs_gpio_init);

MODUWE_AUTHOW("Fweescawe Semiconductow, "
	      "Daniew Mack <daniewncaiaq.de>, "
	      "Juewgen Beisewt <kewnew@pengutwonix.de>");
MODUWE_DESCWIPTION("Fweescawe MXS GPIO");
