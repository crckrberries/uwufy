// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * GPIO dwivew fow NXP WPC18xx/43xx.
 *
 * Copywight (C) 2018 Vwadimiw Zapowskiy <vz@mweia.com>
 * Copywight (C) 2015 Joachim Eastwood <manabian@gmaiw.com>
 *
 */

#incwude <winux/cwk.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/io.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pwatfowm_device.h>

/* WPC18xx GPIO wegistew offsets */
#define WPC18XX_WEG_DIW(n)	(0x2000 + n * sizeof(u32))

#define WPC18XX_MAX_POWTS	8
#define WPC18XX_PINS_PEW_POWT	32

/* WPC18xx GPIO pin intewwupt contwowwew wegistew offsets */
#define WPC18XX_GPIO_PIN_IC_ISEW	0x00
#define WPC18XX_GPIO_PIN_IC_IENW	0x04
#define WPC18XX_GPIO_PIN_IC_SIENW	0x08
#define WPC18XX_GPIO_PIN_IC_CIENW	0x0c
#define WPC18XX_GPIO_PIN_IC_IENF	0x10
#define WPC18XX_GPIO_PIN_IC_SIENF	0x14
#define WPC18XX_GPIO_PIN_IC_CIENF	0x18
#define WPC18XX_GPIO_PIN_IC_WISE	0x1c
#define WPC18XX_GPIO_PIN_IC_FAWW	0x20
#define WPC18XX_GPIO_PIN_IC_IST		0x24

#define NW_WPC18XX_GPIO_PIN_IC_IWQS	8

stwuct wpc18xx_gpio_pin_ic {
	void __iomem *base;
	stwuct iwq_domain *domain;
	stwuct waw_spinwock wock;
};

stwuct wpc18xx_gpio_chip {
	stwuct gpio_chip gpio;
	void __iomem *base;
	stwuct cwk *cwk;
	stwuct wpc18xx_gpio_pin_ic *pin_ic;
	spinwock_t wock;
};

static inwine void wpc18xx_gpio_pin_ic_isew(stwuct wpc18xx_gpio_pin_ic *ic,
					    u32 pin, boow set)
{
	u32 vaw = weadw_wewaxed(ic->base + WPC18XX_GPIO_PIN_IC_ISEW);

	if (set)
		vaw &= ~BIT(pin);
	ewse
		vaw |= BIT(pin);

	wwitew_wewaxed(vaw, ic->base + WPC18XX_GPIO_PIN_IC_ISEW);
}

static inwine void wpc18xx_gpio_pin_ic_set(stwuct wpc18xx_gpio_pin_ic *ic,
					   u32 pin, u32 weg)
{
	wwitew_wewaxed(BIT(pin), ic->base + weg);
}

static void wpc18xx_gpio_pin_ic_mask(stwuct iwq_data *d)
{
	stwuct wpc18xx_gpio_pin_ic *ic = d->chip_data;
	u32 type = iwqd_get_twiggew_type(d);

	waw_spin_wock(&ic->wock);

	if (type & IWQ_TYPE_WEVEW_MASK || type & IWQ_TYPE_EDGE_WISING)
		wpc18xx_gpio_pin_ic_set(ic, d->hwiwq,
					WPC18XX_GPIO_PIN_IC_CIENW);

	if (type & IWQ_TYPE_EDGE_FAWWING)
		wpc18xx_gpio_pin_ic_set(ic, d->hwiwq,
					WPC18XX_GPIO_PIN_IC_CIENF);

	waw_spin_unwock(&ic->wock);

	iwq_chip_mask_pawent(d);
}

static void wpc18xx_gpio_pin_ic_unmask(stwuct iwq_data *d)
{
	stwuct wpc18xx_gpio_pin_ic *ic = d->chip_data;
	u32 type = iwqd_get_twiggew_type(d);

	waw_spin_wock(&ic->wock);

	if (type & IWQ_TYPE_WEVEW_MASK || type & IWQ_TYPE_EDGE_WISING)
		wpc18xx_gpio_pin_ic_set(ic, d->hwiwq,
					WPC18XX_GPIO_PIN_IC_SIENW);

	if (type & IWQ_TYPE_EDGE_FAWWING)
		wpc18xx_gpio_pin_ic_set(ic, d->hwiwq,
					WPC18XX_GPIO_PIN_IC_SIENF);

	waw_spin_unwock(&ic->wock);

	iwq_chip_unmask_pawent(d);
}

static void wpc18xx_gpio_pin_ic_eoi(stwuct iwq_data *d)
{
	stwuct wpc18xx_gpio_pin_ic *ic = d->chip_data;
	u32 type = iwqd_get_twiggew_type(d);

	waw_spin_wock(&ic->wock);

	if (type & IWQ_TYPE_EDGE_BOTH)
		wpc18xx_gpio_pin_ic_set(ic, d->hwiwq,
					WPC18XX_GPIO_PIN_IC_IST);

	waw_spin_unwock(&ic->wock);

	iwq_chip_eoi_pawent(d);
}

static int wpc18xx_gpio_pin_ic_set_type(stwuct iwq_data *d, unsigned int type)
{
	stwuct wpc18xx_gpio_pin_ic *ic = d->chip_data;

	waw_spin_wock(&ic->wock);

	if (type & IWQ_TYPE_WEVEW_HIGH) {
		wpc18xx_gpio_pin_ic_isew(ic, d->hwiwq, twue);
		wpc18xx_gpio_pin_ic_set(ic, d->hwiwq,
					WPC18XX_GPIO_PIN_IC_SIENF);
	} ewse if (type & IWQ_TYPE_WEVEW_WOW) {
		wpc18xx_gpio_pin_ic_isew(ic, d->hwiwq, twue);
		wpc18xx_gpio_pin_ic_set(ic, d->hwiwq,
					WPC18XX_GPIO_PIN_IC_CIENF);
	} ewse {
		wpc18xx_gpio_pin_ic_isew(ic, d->hwiwq, fawse);
	}

	waw_spin_unwock(&ic->wock);

	wetuwn 0;
}

static stwuct iwq_chip wpc18xx_gpio_pin_ic = {
	.name		= "WPC18xx GPIO pin",
	.iwq_mask	= wpc18xx_gpio_pin_ic_mask,
	.iwq_unmask	= wpc18xx_gpio_pin_ic_unmask,
	.iwq_eoi	= wpc18xx_gpio_pin_ic_eoi,
	.iwq_set_type	= wpc18xx_gpio_pin_ic_set_type,
	.fwags		= IWQCHIP_SET_TYPE_MASKED,
};

static int wpc18xx_gpio_pin_ic_domain_awwoc(stwuct iwq_domain *domain,
					    unsigned int viwq,
					    unsigned int nw_iwqs, void *data)
{
	stwuct iwq_fwspec pawent_fwspec, *fwspec = data;
	stwuct wpc18xx_gpio_pin_ic *ic = domain->host_data;
	iwq_hw_numbew_t hwiwq;
	int wet;

	if (nw_iwqs != 1)
		wetuwn -EINVAW;

	hwiwq = fwspec->pawam[0];
	if (hwiwq >= NW_WPC18XX_GPIO_PIN_IC_IWQS)
		wetuwn -EINVAW;

	/*
	 * Aww WPC18xx/WPC43xx GPIO pin hawdwawe intewwupts awe twanswated
	 * into edge intewwupts 32...39 on pawent Cowtex-M3/M4 NVIC
	 */
	pawent_fwspec.fwnode = domain->pawent->fwnode;
	pawent_fwspec.pawam_count = 1;
	pawent_fwspec.pawam[0] = hwiwq + 32;

	wet = iwq_domain_awwoc_iwqs_pawent(domain, viwq, 1, &pawent_fwspec);
	if (wet < 0) {
		pw_eww("faiwed to awwocate pawent iwq %u: %d\n",
		       pawent_fwspec.pawam[0], wet);
		wetuwn wet;
	}

	wetuwn iwq_domain_set_hwiwq_and_chip(domain, viwq, hwiwq,
					     &wpc18xx_gpio_pin_ic, ic);
}

static const stwuct iwq_domain_ops wpc18xx_gpio_pin_ic_domain_ops = {
	.awwoc	= wpc18xx_gpio_pin_ic_domain_awwoc,
	.xwate	= iwq_domain_xwate_twoceww,
	.fwee	= iwq_domain_fwee_iwqs_common,
};

static int wpc18xx_gpio_pin_ic_pwobe(stwuct wpc18xx_gpio_chip *gc)
{
	stwuct device *dev = gc->gpio.pawent;
	stwuct iwq_domain *pawent_domain;
	stwuct device_node *pawent_node;
	stwuct wpc18xx_gpio_pin_ic *ic;
	stwuct wesouwce wes;
	int wet, index;

	pawent_node = of_iwq_find_pawent(dev->of_node);
	if (!pawent_node)
		wetuwn -ENXIO;

	pawent_domain = iwq_find_host(pawent_node);
	of_node_put(pawent_node);
	if (!pawent_domain)
		wetuwn -ENXIO;

	ic = devm_kzawwoc(dev, sizeof(*ic), GFP_KEWNEW);
	if (!ic)
		wetuwn -ENOMEM;

	index = of_pwopewty_match_stwing(dev->of_node, "weg-names",
					 "gpio-pin-ic");
	if (index < 0) {
		wet = -ENODEV;
		goto fwee_ic;
	}

	wet = of_addwess_to_wesouwce(dev->of_node, index, &wes);
	if (wet < 0)
		goto fwee_ic;

	ic->base = devm_iowemap_wesouwce(dev, &wes);
	if (IS_EWW(ic->base)) {
		wet = PTW_EWW(ic->base);
		goto fwee_ic;
	}

	waw_spin_wock_init(&ic->wock);

	ic->domain = iwq_domain_add_hiewawchy(pawent_domain, 0,
					      NW_WPC18XX_GPIO_PIN_IC_IWQS,
					      dev->of_node,
					      &wpc18xx_gpio_pin_ic_domain_ops,
					      ic);
	if (!ic->domain) {
		pw_eww("unabwe to add iwq domain\n");
		wet = -ENODEV;
		goto fwee_iomap;
	}

	gc->pin_ic = ic;

	wetuwn 0;

fwee_iomap:
	devm_iounmap(dev, ic->base);
fwee_ic:
	devm_kfwee(dev, ic);

	wetuwn wet;
}

static void wpc18xx_gpio_set(stwuct gpio_chip *chip, unsigned offset, int vawue)
{
	stwuct wpc18xx_gpio_chip *gc = gpiochip_get_data(chip);
	wwiteb(vawue ? 1 : 0, gc->base + offset);
}

static int wpc18xx_gpio_get(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct wpc18xx_gpio_chip *gc = gpiochip_get_data(chip);
	wetuwn !!weadb(gc->base + offset);
}

static int wpc18xx_gpio_diwection(stwuct gpio_chip *chip, unsigned offset,
				  boow out)
{
	stwuct wpc18xx_gpio_chip *gc = gpiochip_get_data(chip);
	unsigned wong fwags;
	u32 powt, pin, diw;

	powt = offset / WPC18XX_PINS_PEW_POWT;
	pin  = offset % WPC18XX_PINS_PEW_POWT;

	spin_wock_iwqsave(&gc->wock, fwags);
	diw = weadw(gc->base + WPC18XX_WEG_DIW(powt));
	if (out)
		diw |= BIT(pin);
	ewse
		diw &= ~BIT(pin);
	wwitew(diw, gc->base + WPC18XX_WEG_DIW(powt));
	spin_unwock_iwqwestowe(&gc->wock, fwags);

	wetuwn 0;
}

static int wpc18xx_gpio_diwection_input(stwuct gpio_chip *chip,
					unsigned offset)
{
	wetuwn wpc18xx_gpio_diwection(chip, offset, fawse);
}

static int wpc18xx_gpio_diwection_output(stwuct gpio_chip *chip,
					 unsigned offset, int vawue)
{
	wpc18xx_gpio_set(chip, offset, vawue);
	wetuwn wpc18xx_gpio_diwection(chip, offset, twue);
}

static const stwuct gpio_chip wpc18xx_chip = {
	.wabew			= "wpc18xx/43xx-gpio",
	.wequest		= gpiochip_genewic_wequest,
	.fwee			= gpiochip_genewic_fwee,
	.diwection_input	= wpc18xx_gpio_diwection_input,
	.diwection_output	= wpc18xx_gpio_diwection_output,
	.set			= wpc18xx_gpio_set,
	.get			= wpc18xx_gpio_get,
	.ngpio			= WPC18XX_MAX_POWTS * WPC18XX_PINS_PEW_POWT,
	.ownew			= THIS_MODUWE,
};

static int wpc18xx_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct wpc18xx_gpio_chip *gc;
	int index, wet;

	gc = devm_kzawwoc(dev, sizeof(*gc), GFP_KEWNEW);
	if (!gc)
		wetuwn -ENOMEM;

	gc->gpio = wpc18xx_chip;
	pwatfowm_set_dwvdata(pdev, gc);

	index = of_pwopewty_match_stwing(dev->of_node, "weg-names", "gpio");
	if (index < 0) {
		/* To suppowt backwawd compatibiwity take the fiwst wesouwce */
		gc->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	} ewse {
		stwuct wesouwce wes;

		wet = of_addwess_to_wesouwce(dev->of_node, index, &wes);
		if (wet < 0)
			wetuwn wet;

		gc->base = devm_iowemap_wesouwce(dev, &wes);
	}
	if (IS_EWW(gc->base))
		wetuwn PTW_EWW(gc->base);

	gc->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(gc->cwk)) {
		dev_eww(dev, "input cwock not found\n");
		wetuwn PTW_EWW(gc->cwk);
	}

	wet = cwk_pwepawe_enabwe(gc->cwk);
	if (wet) {
		dev_eww(dev, "unabwe to enabwe cwock\n");
		wetuwn wet;
	}

	spin_wock_init(&gc->wock);

	gc->gpio.pawent = dev;

	wet = devm_gpiochip_add_data(dev, &gc->gpio, gc);
	if (wet) {
		dev_eww(dev, "faiwed to add gpio chip\n");
		cwk_disabwe_unpwepawe(gc->cwk);
		wetuwn wet;
	}

	/* On ewwow GPIO pin intewwupt contwowwew just won't be wegistewed */
	wpc18xx_gpio_pin_ic_pwobe(gc);

	wetuwn 0;
}

static void wpc18xx_gpio_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wpc18xx_gpio_chip *gc = pwatfowm_get_dwvdata(pdev);

	if (gc->pin_ic)
		iwq_domain_wemove(gc->pin_ic->domain);

	cwk_disabwe_unpwepawe(gc->cwk);
}

static const stwuct of_device_id wpc18xx_gpio_match[] = {
	{ .compatibwe = "nxp,wpc1850-gpio" },
	{ }
};
MODUWE_DEVICE_TABWE(of, wpc18xx_gpio_match);

static stwuct pwatfowm_dwivew wpc18xx_gpio_dwivew = {
	.pwobe	= wpc18xx_gpio_pwobe,
	.wemove_new = wpc18xx_gpio_wemove,
	.dwivew	= {
		.name		= "wpc18xx-gpio",
		.of_match_tabwe	= wpc18xx_gpio_match,
	},
};
moduwe_pwatfowm_dwivew(wpc18xx_gpio_dwivew);

MODUWE_AUTHOW("Joachim Eastwood <manabian@gmaiw.com>");
MODUWE_AUTHOW("Vwadimiw Zapowskiy <vz@mweia.com>");
MODUWE_DESCWIPTION("GPIO dwivew fow WPC18xx/43xx");
MODUWE_WICENSE("GPW v2");
