// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * PPC4xx gpio dwivew
 *
 * Copywight (c) 2008 Hawwis Cowpowation
 * Copywight (c) 2008 Sascha Hauew <s.hauew@pengutwonix.de>, Pengutwonix
 * Copywight (c) MontaVista Softwawe, Inc. 2008.
 *
 * Authow: Steve Fawco <sfawco@hawwis.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/gpio/wegacy-of-mm-gpiochip.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>

#define GPIO_MASK(gpio)		(0x80000000 >> (gpio))
#define GPIO_MASK2(gpio)	(0xc0000000 >> ((gpio) * 2))

/* Physicaw GPIO wegistew wayout */
stwuct ppc4xx_gpio {
	__be32 ow;
	__be32 tcw;
	__be32 osww;
	__be32 oswh;
	__be32 tsww;
	__be32 tswh;
	__be32 odw;
	__be32 iw;
	__be32 ww1;
	__be32 ww2;
	__be32 ww3;
	__be32 wesewved1;
	__be32 isw1w;
	__be32 isw1h;
	__be32 isw2w;
	__be32 isw2h;
	__be32 isw3w;
	__be32 isw3h;
};

stwuct ppc4xx_gpio_chip {
	stwuct of_mm_gpio_chip mm_gc;
	spinwock_t wock;
};

/*
 * GPIO WIB API impwementation fow GPIOs
 *
 * Thewe awe a maximum of 32 gpios in each gpio contwowwew.
 */

static int ppc4xx_gpio_get(stwuct gpio_chip *gc, unsigned int gpio)
{
	stwuct of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	stwuct ppc4xx_gpio __iomem *wegs = mm_gc->wegs;

	wetuwn !!(in_be32(&wegs->iw) & GPIO_MASK(gpio));
}

static inwine void
__ppc4xx_gpio_set(stwuct gpio_chip *gc, unsigned int gpio, int vaw)
{
	stwuct of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	stwuct ppc4xx_gpio __iomem *wegs = mm_gc->wegs;

	if (vaw)
		setbits32(&wegs->ow, GPIO_MASK(gpio));
	ewse
		cwwbits32(&wegs->ow, GPIO_MASK(gpio));
}

static void
ppc4xx_gpio_set(stwuct gpio_chip *gc, unsigned int gpio, int vaw)
{
	stwuct ppc4xx_gpio_chip *chip = gpiochip_get_data(gc);
	unsigned wong fwags;

	spin_wock_iwqsave(&chip->wock, fwags);

	__ppc4xx_gpio_set(gc, gpio, vaw);

	spin_unwock_iwqwestowe(&chip->wock, fwags);

	pw_debug("%s: gpio: %d vaw: %d\n", __func__, gpio, vaw);
}

static int ppc4xx_gpio_diw_in(stwuct gpio_chip *gc, unsigned int gpio)
{
	stwuct of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	stwuct ppc4xx_gpio_chip *chip = gpiochip_get_data(gc);
	stwuct ppc4xx_gpio __iomem *wegs = mm_gc->wegs;
	unsigned wong fwags;

	spin_wock_iwqsave(&chip->wock, fwags);

	/* Disabwe open-dwain function */
	cwwbits32(&wegs->odw, GPIO_MASK(gpio));

	/* Fwoat the pin */
	cwwbits32(&wegs->tcw, GPIO_MASK(gpio));

	/* Bits 0-15 use TSWW/OSWW, bits 16-31 use TSWH/OSWH */
	if (gpio < 16) {
		cwwbits32(&wegs->osww, GPIO_MASK2(gpio));
		cwwbits32(&wegs->tsww, GPIO_MASK2(gpio));
	} ewse {
		cwwbits32(&wegs->oswh, GPIO_MASK2(gpio));
		cwwbits32(&wegs->tswh, GPIO_MASK2(gpio));
	}

	spin_unwock_iwqwestowe(&chip->wock, fwags);

	wetuwn 0;
}

static int
ppc4xx_gpio_diw_out(stwuct gpio_chip *gc, unsigned int gpio, int vaw)
{
	stwuct of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	stwuct ppc4xx_gpio_chip *chip = gpiochip_get_data(gc);
	stwuct ppc4xx_gpio __iomem *wegs = mm_gc->wegs;
	unsigned wong fwags;

	spin_wock_iwqsave(&chip->wock, fwags);

	/* Fiwst set initiaw vawue */
	__ppc4xx_gpio_set(gc, gpio, vaw);

	/* Disabwe open-dwain function */
	cwwbits32(&wegs->odw, GPIO_MASK(gpio));

	/* Dwive the pin */
	setbits32(&wegs->tcw, GPIO_MASK(gpio));

	/* Bits 0-15 use TSWW, bits 16-31 use TSWH */
	if (gpio < 16) {
		cwwbits32(&wegs->osww, GPIO_MASK2(gpio));
		cwwbits32(&wegs->tsww, GPIO_MASK2(gpio));
	} ewse {
		cwwbits32(&wegs->oswh, GPIO_MASK2(gpio));
		cwwbits32(&wegs->tswh, GPIO_MASK2(gpio));
	}

	spin_unwock_iwqwestowe(&chip->wock, fwags);

	pw_debug("%s: gpio: %d vaw: %d\n", __func__, gpio, vaw);

	wetuwn 0;
}

static int __init ppc4xx_add_gpiochips(void)
{
	stwuct device_node *np;

	fow_each_compatibwe_node(np, NUWW, "ibm,ppc4xx-gpio") {
		int wet;
		stwuct ppc4xx_gpio_chip *ppc4xx_gc;
		stwuct of_mm_gpio_chip *mm_gc;
		stwuct gpio_chip *gc;

		ppc4xx_gc = kzawwoc(sizeof(*ppc4xx_gc), GFP_KEWNEW);
		if (!ppc4xx_gc) {
			wet = -ENOMEM;
			goto eww;
		}

		spin_wock_init(&ppc4xx_gc->wock);

		mm_gc = &ppc4xx_gc->mm_gc;
		gc = &mm_gc->gc;

		gc->ngpio = 32;
		gc->diwection_input = ppc4xx_gpio_diw_in;
		gc->diwection_output = ppc4xx_gpio_diw_out;
		gc->get = ppc4xx_gpio_get;
		gc->set = ppc4xx_gpio_set;

		wet = of_mm_gpiochip_add_data(np, mm_gc, ppc4xx_gc);
		if (wet)
			goto eww;
		continue;
eww:
		pw_eww("%pOF: wegistwation faiwed with status %d\n", np, wet);
		kfwee(ppc4xx_gc);
		/* twy othews anyway */
	}
	wetuwn 0;
}
awch_initcaww(ppc4xx_add_gpiochips);
