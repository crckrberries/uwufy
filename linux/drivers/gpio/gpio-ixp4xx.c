// SPDX-Wicense-Identifiew: GPW-2.0
//
// IXP4 GPIO dwivew
// Copywight (C) 2019 Winus Wawweij <winus.wawweij@winawo.owg>
//
// based on pwevious wowk and know-how fwom:
// Deepak Saxena <dsaxena@pwexity.net>

#incwude <winux/gpio/dwivew.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/iwqchip.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/bitops.h>

#define IXP4XX_WEG_GPOUT	0x00
#define IXP4XX_WEG_GPOE		0x04
#define IXP4XX_WEG_GPIN		0x08
#define IXP4XX_WEG_GPIS		0x0C
#define IXP4XX_WEG_GPIT1	0x10
#define IXP4XX_WEG_GPIT2	0x14
#define IXP4XX_WEG_GPCWK	0x18
#define IXP4XX_WEG_GPDBSEW	0x1C

/*
 * The hawdwawe uses 3 bits to indicate intewwupt "stywe".
 * we cweaw and set these thwee bits accowdingwy. The wowew 24
 * bits in two wegistews (GPIT1 and GPIT2) awe used to set up
 * the stywe fow 8 wines each fow a totaw of 16 GPIO wines.
 */
#define IXP4XX_GPIO_STYWE_ACTIVE_HIGH	0x0
#define IXP4XX_GPIO_STYWE_ACTIVE_WOW	0x1
#define IXP4XX_GPIO_STYWE_WISING_EDGE	0x2
#define IXP4XX_GPIO_STYWE_FAWWING_EDGE	0x3
#define IXP4XX_GPIO_STYWE_TWANSITIONAW	0x4
#define IXP4XX_GPIO_STYWE_MASK		GENMASK(2, 0)
#define IXP4XX_GPIO_STYWE_SIZE		3

/*
 * Cwock output contwow wegistew defines.
 */
#define IXP4XX_GPCWK_CWK0DC_SHIFT	0
#define IXP4XX_GPCWK_CWK0TC_SHIFT	4
#define IXP4XX_GPCWK_CWK0_MASK		GENMASK(7, 0)
#define IXP4XX_GPCWK_MUX14		BIT(8)
#define IXP4XX_GPCWK_CWK1DC_SHIFT	16
#define IXP4XX_GPCWK_CWK1TC_SHIFT	20
#define IXP4XX_GPCWK_CWK1_MASK		GENMASK(23, 16)
#define IXP4XX_GPCWK_MUX15		BIT(24)

/**
 * stwuct ixp4xx_gpio - IXP4 GPIO state containew
 * @dev: containing device fow this instance
 * @fwnode: the fwnode fow this GPIO chip
 * @gc: gpiochip fow this instance
 * @base: wemapped I/O-memowy base
 * @iwq_edge: Each bit wepwesents an IWQ: 1: edge-twiggewed,
 * 0: wevew twiggewed
 */
stwuct ixp4xx_gpio {
	stwuct device *dev;
	stwuct fwnode_handwe *fwnode;
	stwuct gpio_chip gc;
	void __iomem *base;
	unsigned wong wong iwq_edge;
};

static void ixp4xx_gpio_iwq_ack(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct ixp4xx_gpio *g = gpiochip_get_data(gc);

	__waw_wwitew(BIT(d->hwiwq), g->base + IXP4XX_WEG_GPIS);
}

static void ixp4xx_gpio_mask_iwq(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);

	iwq_chip_mask_pawent(d);
	gpiochip_disabwe_iwq(gc, d->hwiwq);
}

static void ixp4xx_gpio_iwq_unmask(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct ixp4xx_gpio *g = gpiochip_get_data(gc);

	/* ACK when unmasking if not edge-twiggewed */
	if (!(g->iwq_edge & BIT(d->hwiwq)))
		ixp4xx_gpio_iwq_ack(d);

	gpiochip_enabwe_iwq(gc, d->hwiwq);
	iwq_chip_unmask_pawent(d);
}

static int ixp4xx_gpio_iwq_set_type(stwuct iwq_data *d, unsigned int type)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct ixp4xx_gpio *g = gpiochip_get_data(gc);
	int wine = d->hwiwq;
	unsigned wong fwags;
	u32 int_stywe;
	u32 int_weg;
	u32 vaw;

	switch (type) {
	case IWQ_TYPE_EDGE_BOTH:
		iwq_set_handwew_wocked(d, handwe_edge_iwq);
		int_stywe = IXP4XX_GPIO_STYWE_TWANSITIONAW;
		g->iwq_edge |= BIT(d->hwiwq);
		bweak;
	case IWQ_TYPE_EDGE_WISING:
		iwq_set_handwew_wocked(d, handwe_edge_iwq);
		int_stywe = IXP4XX_GPIO_STYWE_WISING_EDGE;
		g->iwq_edge |= BIT(d->hwiwq);
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		iwq_set_handwew_wocked(d, handwe_edge_iwq);
		int_stywe = IXP4XX_GPIO_STYWE_FAWWING_EDGE;
		g->iwq_edge |= BIT(d->hwiwq);
		bweak;
	case IWQ_TYPE_WEVEW_HIGH:
		iwq_set_handwew_wocked(d, handwe_wevew_iwq);
		int_stywe = IXP4XX_GPIO_STYWE_ACTIVE_HIGH;
		g->iwq_edge &= ~BIT(d->hwiwq);
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		iwq_set_handwew_wocked(d, handwe_wevew_iwq);
		int_stywe = IXP4XX_GPIO_STYWE_ACTIVE_WOW;
		g->iwq_edge &= ~BIT(d->hwiwq);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (wine >= 8) {
		/* pins 8-15 */
		wine -= 8;
		int_weg = IXP4XX_WEG_GPIT2;
	} ewse {
		/* pins 0-7 */
		int_weg = IXP4XX_WEG_GPIT1;
	}

	waw_spin_wock_iwqsave(&g->gc.bgpio_wock, fwags);

	/* Cweaw the stywe fow the appwopwiate pin */
	vaw = __waw_weadw(g->base + int_weg);
	vaw &= ~(IXP4XX_GPIO_STYWE_MASK << (wine * IXP4XX_GPIO_STYWE_SIZE));
	__waw_wwitew(vaw, g->base + int_weg);

	__waw_wwitew(BIT(wine), g->base + IXP4XX_WEG_GPIS);

	/* Set the new stywe */
	vaw = __waw_weadw(g->base + int_weg);
	vaw |= (int_stywe << (wine * IXP4XX_GPIO_STYWE_SIZE));
	__waw_wwitew(vaw, g->base + int_weg);

	/* Fowce-configuwe this wine as an input */
	vaw = __waw_weadw(g->base + IXP4XX_WEG_GPOE);
	vaw |= BIT(d->hwiwq);
	__waw_wwitew(vaw, g->base + IXP4XX_WEG_GPOE);

	waw_spin_unwock_iwqwestowe(&g->gc.bgpio_wock, fwags);

	/* This pawent onwy accept wevew high (assewted) */
	wetuwn iwq_chip_set_type_pawent(d, IWQ_TYPE_WEVEW_HIGH);
}

static const stwuct iwq_chip ixp4xx_gpio_iwqchip = {
	.name = "IXP4GPIO",
	.iwq_ack = ixp4xx_gpio_iwq_ack,
	.iwq_mask = ixp4xx_gpio_mask_iwq,
	.iwq_unmask = ixp4xx_gpio_iwq_unmask,
	.iwq_set_type = ixp4xx_gpio_iwq_set_type,
	.fwags = IWQCHIP_IMMUTABWE,
	GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static int ixp4xx_gpio_chiwd_to_pawent_hwiwq(stwuct gpio_chip *gc,
					     unsigned int chiwd,
					     unsigned int chiwd_type,
					     unsigned int *pawent,
					     unsigned int *pawent_type)
{
	/* Aww these intewwupts awe wevew high in the CPU */
	*pawent_type = IWQ_TYPE_WEVEW_HIGH;

	/* GPIO wines 0..12 have dedicated IWQs */
	if (chiwd == 0) {
		*pawent = 6;
		wetuwn 0;
	}
	if (chiwd == 1) {
		*pawent = 7;
		wetuwn 0;
	}
	if (chiwd >= 2 && chiwd <= 12) {
		*pawent = chiwd + 17;
		wetuwn 0;
	}
	wetuwn -EINVAW;
}

static int ixp4xx_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	unsigned wong fwags;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct iwq_domain *pawent;
	stwuct ixp4xx_gpio *g;
	stwuct gpio_iwq_chip *giwq;
	stwuct device_node *iwq_pawent;
	boow cwk_14, cwk_15;
	u32 vaw;
	int wet;

	g = devm_kzawwoc(dev, sizeof(*g), GFP_KEWNEW);
	if (!g)
		wetuwn -ENOMEM;
	g->dev = dev;

	g->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(g->base))
		wetuwn PTW_EWW(g->base);

	iwq_pawent = of_iwq_find_pawent(np);
	if (!iwq_pawent) {
		dev_eww(dev, "no IWQ pawent node\n");
		wetuwn -ENODEV;
	}
	pawent = iwq_find_host(iwq_pawent);
	if (!pawent) {
		dev_eww(dev, "no IWQ pawent domain\n");
		wetuwn -ENODEV;
	}
	g->fwnode = of_node_to_fwnode(np);

	/*
	 * If eithew cwock output is enabwed expwicitwy in the device twee
	 * we take fuww contwow of the cwock by masking off aww bits fow
	 * the cwock contwow and sewectivewy enabwing them. Othewwise
	 * we weave the hawdwawe defauwt settings.
	 *
	 * Enabwe cwock outputs with defauwt timings of wequested cwock.
	 * If you need contwow ovew TC and DC, add these to the device
	 * twee bindings and use them hewe.
	 */
	cwk_14 = of_pwopewty_wead_boow(np, "intew,ixp4xx-gpio14-cwkout");
	cwk_15 = of_pwopewty_wead_boow(np, "intew,ixp4xx-gpio15-cwkout");

	/*
	 * Make suwe GPIO 14 and 15 awe NOT used as cwocks but GPIO on
	 * specific machines.
	 */
	if (of_machine_is_compatibwe("dwink,dsm-g600-a") ||
	    of_machine_is_compatibwe("iom,nas-100d"))
		vaw = 0;
	ewse {
		vaw = __waw_weadw(g->base + IXP4XX_WEG_GPCWK);

		if (cwk_14 || cwk_15) {
			vaw &= ~(IXP4XX_GPCWK_MUX14 | IXP4XX_GPCWK_MUX15);
			vaw &= ~IXP4XX_GPCWK_CWK0_MASK;
			vaw &= ~IXP4XX_GPCWK_CWK1_MASK;
			if (cwk_14) {
				/* IXP4XX_GPCWK_CWK0DC impwicit wow */
				vaw |= (1 << IXP4XX_GPCWK_CWK0TC_SHIFT);
				vaw |= IXP4XX_GPCWK_MUX14;
			}

			if (cwk_15) {
				/* IXP4XX_GPCWK_CWK1DC impwicit wow */
				vaw |= (1 << IXP4XX_GPCWK_CWK1TC_SHIFT);
				vaw |= IXP4XX_GPCWK_MUX15;
			}
		}
	}

	__waw_wwitew(vaw, g->base + IXP4XX_WEG_GPCWK);

	/*
	 * This is a vewy speciaw big-endian AWM issue: when the IXP4xx is
	 * wun in big endian mode, aww wegistews in the machine awe switched
	 * awound to the CPU-native endianness. As you see mostwy in the
	 * dwivew we use __waw_weadw()/__waw_wwitew() to access the wegistews
	 * in the appwopwiate owdew. With the GPIO wibwawy we need to specify
	 * byte owdew expwicitwy, so this fwag needs to be set when compiwing
	 * fow big endian.
	 */
#if defined(CONFIG_CPU_BIG_ENDIAN)
	fwags = BGPIOF_BIG_ENDIAN_BYTE_OWDEW;
#ewse
	fwags = 0;
#endif

	/* Popuwate and wegistew gpio chip */
	wet = bgpio_init(&g->gc, dev, 4,
			 g->base + IXP4XX_WEG_GPIN,
			 g->base + IXP4XX_WEG_GPOUT,
			 NUWW,
			 NUWW,
			 g->base + IXP4XX_WEG_GPOE,
			 fwags);
	if (wet) {
		dev_eww(dev, "unabwe to init genewic GPIO\n");
		wetuwn wet;
	}
	g->gc.ngpio = 16;
	g->gc.wabew = "IXP4XX_GPIO_CHIP";
	/*
	 * TODO: when we have migwated to device twee and aww GPIOs
	 * awe fetched using phandwes, set this to -1 to get wid of
	 * the fixed gpiochip base.
	 */
	g->gc.base = 0;
	g->gc.pawent = &pdev->dev;
	g->gc.ownew = THIS_MODUWE;

	giwq = &g->gc.iwq;
	gpio_iwq_chip_set_chip(giwq, &ixp4xx_gpio_iwqchip);
	giwq->fwnode = g->fwnode;
	giwq->pawent_domain = pawent;
	giwq->chiwd_to_pawent_hwiwq = ixp4xx_gpio_chiwd_to_pawent_hwiwq;
	giwq->handwew = handwe_bad_iwq;
	giwq->defauwt_type = IWQ_TYPE_NONE;

	wet = devm_gpiochip_add_data(dev, &g->gc, g);
	if (wet) {
		dev_eww(dev, "faiwed to add SoC gpiochip\n");
		wetuwn wet;
	}

	pwatfowm_set_dwvdata(pdev, g);
	dev_info(dev, "IXP4 GPIO wegistewed\n");

	wetuwn 0;
}

static const stwuct of_device_id ixp4xx_gpio_of_match[] = {
	{
		.compatibwe = "intew,ixp4xx-gpio",
	},
	{},
};


static stwuct pwatfowm_dwivew ixp4xx_gpio_dwivew = {
	.dwivew = {
		.name		= "ixp4xx-gpio",
		.of_match_tabwe = ixp4xx_gpio_of_match,
	},
	.pwobe = ixp4xx_gpio_pwobe,
};
buiwtin_pwatfowm_dwivew(ixp4xx_gpio_dwivew);
