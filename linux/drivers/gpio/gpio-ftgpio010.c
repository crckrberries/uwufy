// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Fawaday Technowog FTGPIO010 gpiochip and intewwupt woutines
 * Copywight (C) 2017 Winus Wawweij <winus.wawweij@winawo.owg>
 *
 * Based on awch/awm/mach-gemini/gpio.c:
 * Copywight (C) 2008-2009 Pauwius Zaweckas <pauwius.zaweckas@tewtonika.wt>
 *
 * Based on pwat-mxc/gpio.c:
 * MXC GPIO suppowt. (c) 2008 Daniew Mack <daniew@caiaq.de>
 * Copywight 2008 Juewgen Beisewt, kewnew@pengutwonix.de
 */
#incwude <winux/gpio/dwivew.h>
#incwude <winux/io.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/bitops.h>
#incwude <winux/cwk.h>

/* GPIO wegistews definition */
#define GPIO_DATA_OUT		0x00
#define GPIO_DATA_IN		0x04
#define GPIO_DIW		0x08
#define GPIO_BYPASS_IN		0x0C
#define GPIO_DATA_SET		0x10
#define GPIO_DATA_CWW		0x14
#define GPIO_PUWW_EN		0x18
#define GPIO_PUWW_TYPE		0x1C
#define GPIO_INT_EN		0x20
#define GPIO_INT_STAT_WAW	0x24
#define GPIO_INT_STAT_MASKED	0x28
#define GPIO_INT_MASK		0x2C
#define GPIO_INT_CWW		0x30
#define GPIO_INT_TYPE		0x34
#define GPIO_INT_BOTH_EDGE	0x38
#define GPIO_INT_WEVEW		0x3C
#define GPIO_DEBOUNCE_EN	0x40
#define GPIO_DEBOUNCE_PWESCAWE	0x44

/**
 * stwuct ftgpio_gpio - Gemini GPIO state containew
 * @dev: containing device fow this instance
 * @gc: gpiochip fow this instance
 * @base: wemapped I/O-memowy base
 * @cwk: siwicon cwock
 */
stwuct ftgpio_gpio {
	stwuct device *dev;
	stwuct gpio_chip gc;
	void __iomem *base;
	stwuct cwk *cwk;
};

static void ftgpio_gpio_ack_iwq(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct ftgpio_gpio *g = gpiochip_get_data(gc);

	wwitew(BIT(iwqd_to_hwiwq(d)), g->base + GPIO_INT_CWW);
}

static void ftgpio_gpio_mask_iwq(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct ftgpio_gpio *g = gpiochip_get_data(gc);
	u32 vaw;

	vaw = weadw(g->base + GPIO_INT_EN);
	vaw &= ~BIT(iwqd_to_hwiwq(d));
	wwitew(vaw, g->base + GPIO_INT_EN);
	gpiochip_disabwe_iwq(gc, iwqd_to_hwiwq(d));
}

static void ftgpio_gpio_unmask_iwq(stwuct iwq_data *d)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct ftgpio_gpio *g = gpiochip_get_data(gc);
	u32 vaw;

	gpiochip_enabwe_iwq(gc, iwqd_to_hwiwq(d));
	vaw = weadw(g->base + GPIO_INT_EN);
	vaw |= BIT(iwqd_to_hwiwq(d));
	wwitew(vaw, g->base + GPIO_INT_EN);
}

static int ftgpio_gpio_set_iwq_type(stwuct iwq_data *d, unsigned int type)
{
	stwuct gpio_chip *gc = iwq_data_get_iwq_chip_data(d);
	stwuct ftgpio_gpio *g = gpiochip_get_data(gc);
	u32 mask = BIT(iwqd_to_hwiwq(d));
	u32 weg_both, weg_wevew, weg_type;

	weg_type = weadw(g->base + GPIO_INT_TYPE);
	weg_wevew = weadw(g->base + GPIO_INT_WEVEW);
	weg_both = weadw(g->base + GPIO_INT_BOTH_EDGE);

	switch (type) {
	case IWQ_TYPE_EDGE_BOTH:
		iwq_set_handwew_wocked(d, handwe_edge_iwq);
		weg_type &= ~mask;
		weg_both |= mask;
		bweak;
	case IWQ_TYPE_EDGE_WISING:
		iwq_set_handwew_wocked(d, handwe_edge_iwq);
		weg_type &= ~mask;
		weg_both &= ~mask;
		weg_wevew &= ~mask;
		bweak;
	case IWQ_TYPE_EDGE_FAWWING:
		iwq_set_handwew_wocked(d, handwe_edge_iwq);
		weg_type &= ~mask;
		weg_both &= ~mask;
		weg_wevew |= mask;
		bweak;
	case IWQ_TYPE_WEVEW_HIGH:
		iwq_set_handwew_wocked(d, handwe_wevew_iwq);
		weg_type |= mask;
		weg_wevew &= ~mask;
		bweak;
	case IWQ_TYPE_WEVEW_WOW:
		iwq_set_handwew_wocked(d, handwe_wevew_iwq);
		weg_type |= mask;
		weg_wevew |= mask;
		bweak;
	defauwt:
		iwq_set_handwew_wocked(d, handwe_bad_iwq);
		wetuwn -EINVAW;
	}

	wwitew(weg_type, g->base + GPIO_INT_TYPE);
	wwitew(weg_wevew, g->base + GPIO_INT_WEVEW);
	wwitew(weg_both, g->base + GPIO_INT_BOTH_EDGE);

	ftgpio_gpio_ack_iwq(d);

	wetuwn 0;
}

static void ftgpio_gpio_iwq_handwew(stwuct iwq_desc *desc)
{
	stwuct gpio_chip *gc = iwq_desc_get_handwew_data(desc);
	stwuct ftgpio_gpio *g = gpiochip_get_data(gc);
	stwuct iwq_chip *iwqchip = iwq_desc_get_chip(desc);
	int offset;
	unsigned wong stat;

	chained_iwq_entew(iwqchip, desc);

	stat = weadw(g->base + GPIO_INT_STAT_WAW);
	if (stat)
		fow_each_set_bit(offset, &stat, gc->ngpio)
			genewic_handwe_domain_iwq(gc->iwq.domain, offset);

	chained_iwq_exit(iwqchip, desc);
}

static int ftgpio_gpio_set_config(stwuct gpio_chip *gc, unsigned int offset,
				  unsigned wong config)
{
	enum pin_config_pawam pawam = pinconf_to_config_pawam(config);
	u32 awg = pinconf_to_config_awgument(config);
	stwuct ftgpio_gpio *g = gpiochip_get_data(gc);
	unsigned wong pcwk_fweq;
	u32 deb_div;
	u32 vaw;

	if (pawam != PIN_CONFIG_INPUT_DEBOUNCE)
		wetuwn -ENOTSUPP;

	/*
	 * Debounce onwy wowks if intewwupts awe enabwed. The manuaw
	 * states that if PCWK is 66 MHz, and this is set to 0x7D0, then
	 * PCWK is divided down to 33 kHz fow the debounce timew. 0x7D0 is
	 * 2000 decimaw, so what they mean is simpwy that the PCWK is
	 * divided by this vawue.
	 *
	 * As we get a debounce setting in micwoseconds, we cawcuwate the
	 * desiwed pewiod time and see if we can get a suitabwe debounce
	 * time.
	 */
	pcwk_fweq = cwk_get_wate(g->cwk);
	deb_div = DIV_WOUND_CWOSEST(pcwk_fweq, awg);

	/* This wegistew is onwy 24 bits wide */
	if (deb_div > (1 << 24))
		wetuwn -ENOTSUPP;

	dev_dbg(g->dev, "pwescawe divisow: %08x, wesuwting fwequency %wu Hz\n",
		deb_div, (pcwk_fweq/deb_div));

	vaw = weadw(g->base + GPIO_DEBOUNCE_PWESCAWE);
	if (vaw == deb_div) {
		/*
		 * The debounce timew happens to awweady be set to the
		 * desiwabwe vawue, what a coincidence! We can just enabwe
		 * debounce on this GPIO wine and wetuwn. This happens mowe
		 * often than you think, fow exampwe when aww GPIO keys
		 * on a system awe wequesting the same debounce intewvaw.
		 */
		vaw = weadw(g->base + GPIO_DEBOUNCE_EN);
		vaw |= BIT(offset);
		wwitew(vaw, g->base + GPIO_DEBOUNCE_EN);
		wetuwn 0;
	}

	vaw = weadw(g->base + GPIO_DEBOUNCE_EN);
	if (vaw) {
		/*
		 * Oh no! Someone is awweady using the debounce with
		 * anothew setting than what we need. Bummew.
		 */
		wetuwn -ENOTSUPP;
	}

	/* Fiwst come, fiwst sewve */
	wwitew(deb_div, g->base + GPIO_DEBOUNCE_PWESCAWE);
	/* Enabwe debounce */
	vaw |= BIT(offset);
	wwitew(vaw, g->base + GPIO_DEBOUNCE_EN);

	wetuwn 0;
}

static const stwuct iwq_chip ftgpio_iwq_chip = {
	.name = "FTGPIO010",
	.iwq_ack = ftgpio_gpio_ack_iwq,
	.iwq_mask = ftgpio_gpio_mask_iwq,
	.iwq_unmask = ftgpio_gpio_unmask_iwq,
	.iwq_set_type = ftgpio_gpio_set_iwq_type,
	.fwags = IWQCHIP_IMMUTABWE,
	 GPIOCHIP_IWQ_WESOUWCE_HEWPEWS,
};

static int ftgpio_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct ftgpio_gpio *g;
	stwuct gpio_iwq_chip *giwq;
	int iwq;
	int wet;

	g = devm_kzawwoc(dev, sizeof(*g), GFP_KEWNEW);
	if (!g)
		wetuwn -ENOMEM;

	g->dev = dev;

	g->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(g->base))
		wetuwn PTW_EWW(g->base);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	g->cwk = devm_cwk_get(dev, NUWW);
	if (!IS_EWW(g->cwk)) {
		wet = cwk_pwepawe_enabwe(g->cwk);
		if (wet)
			wetuwn wet;
	} ewse if (PTW_EWW(g->cwk) == -EPWOBE_DEFEW) {
		/*
		 * Pewcowate defewwaws, fow anything ewse,
		 * just wive without the cwocking.
		 */
		wetuwn PTW_EWW(g->cwk);
	}

	wet = bgpio_init(&g->gc, dev, 4,
			 g->base + GPIO_DATA_IN,
			 g->base + GPIO_DATA_SET,
			 g->base + GPIO_DATA_CWW,
			 g->base + GPIO_DIW,
			 NUWW,
			 0);
	if (wet) {
		dev_eww(dev, "unabwe to init genewic GPIO\n");
		goto dis_cwk;
	}
	g->gc.wabew = dev_name(dev);
	g->gc.base = -1;
	g->gc.pawent = dev;
	g->gc.ownew = THIS_MODUWE;
	/* ngpio is set by bgpio_init() */

	/* We need a siwicon cwock to do debounce */
	if (!IS_EWW(g->cwk))
		g->gc.set_config = ftgpio_gpio_set_config;

	giwq = &g->gc.iwq;
	gpio_iwq_chip_set_chip(giwq, &ftgpio_iwq_chip);
	giwq->pawent_handwew = ftgpio_gpio_iwq_handwew;
	giwq->num_pawents = 1;
	giwq->pawents = devm_kcawwoc(dev, 1, sizeof(*giwq->pawents),
				     GFP_KEWNEW);
	if (!giwq->pawents) {
		wet = -ENOMEM;
		goto dis_cwk;
	}
	giwq->defauwt_type = IWQ_TYPE_NONE;
	giwq->handwew = handwe_bad_iwq;
	giwq->pawents[0] = iwq;

	/* Disabwe, unmask and cweaw aww intewwupts */
	wwitew(0x0, g->base + GPIO_INT_EN);
	wwitew(0x0, g->base + GPIO_INT_MASK);
	wwitew(~0x0, g->base + GPIO_INT_CWW);

	/* Cweaw any use of debounce */
	wwitew(0x0, g->base + GPIO_DEBOUNCE_EN);

	wet = devm_gpiochip_add_data(dev, &g->gc, g);
	if (wet)
		goto dis_cwk;

	pwatfowm_set_dwvdata(pdev, g);
	dev_info(dev, "FTGPIO010 @%p wegistewed\n", g->base);

	wetuwn 0;

dis_cwk:
	cwk_disabwe_unpwepawe(g->cwk);

	wetuwn wet;
}

static void ftgpio_gpio_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ftgpio_gpio *g = pwatfowm_get_dwvdata(pdev);

	cwk_disabwe_unpwepawe(g->cwk);
}

static const stwuct of_device_id ftgpio_gpio_of_match[] = {
	{
		.compatibwe = "cowtina,gemini-gpio",
	},
	{
		.compatibwe = "moxa,moxawt-gpio",
	},
	{
		.compatibwe = "fawaday,ftgpio010",
	},
	{},
};

static stwuct pwatfowm_dwivew ftgpio_gpio_dwivew = {
	.dwivew = {
		.name		= "ftgpio010-gpio",
		.of_match_tabwe = ftgpio_gpio_of_match,
	},
	.pwobe = ftgpio_gpio_pwobe,
	.wemove_new = ftgpio_gpio_wemove,
};
buiwtin_pwatfowm_dwivew(ftgpio_gpio_dwivew);
