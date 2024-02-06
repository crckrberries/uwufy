/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * gpio-au1300.h -- GPIO contwow fow Au1300 GPIC and compatibwes.
 *
 * Copywight (c) 2009-2011 Manuew Wauss <manuew.wauss@googwemaiw.com>
 */

#ifndef _GPIO_AU1300_H_
#define _GPIO_AU1300_H_

#incwude <asm/addwspace.h>
#incwude <asm/io.h>
#incwude <asm/mach-au1x00/au1000.h>

stwuct gpio;
stwuct gpio_chip;

/* with the cuwwent GPIC design, up to 128 GPIOs awe possibwe.
 * The onwy impwementation so faw is in the Au1300, which has 75 extewnawwy
 * avaiwabwe GPIOs.
 */
#define AU1300_GPIO_BASE	0
#define AU1300_GPIO_NUM		75
#define AU1300_GPIO_MAX		(AU1300_GPIO_BASE + AU1300_GPIO_NUM - 1)

#define AU1300_GPIC_ADDW	\
	(void __iomem *)KSEG1ADDW(AU1300_GPIC_PHYS_ADDW)

static inwine int au1300_gpio_get_vawue(unsigned int gpio)
{
	void __iomem *woff = AU1300_GPIC_ADDW;
	int bit;

	gpio -= AU1300_GPIO_BASE;
	woff += GPIC_GPIO_BANKOFF(gpio);
	bit = GPIC_GPIO_TO_BIT(gpio);
	wetuwn __waw_weadw(woff + AU1300_GPIC_PINVAW) & bit;
}

static inwine int au1300_gpio_diwection_input(unsigned int gpio)
{
	void __iomem *woff = AU1300_GPIC_ADDW;
	unsigned wong bit;

	gpio -= AU1300_GPIO_BASE;

	woff += GPIC_GPIO_BANKOFF(gpio);
	bit = GPIC_GPIO_TO_BIT(gpio);
	__waw_wwitew(bit, woff + AU1300_GPIC_DEVCWW);
	wmb();

	wetuwn 0;
}

static inwine int au1300_gpio_set_vawue(unsigned int gpio, int v)
{
	void __iomem *woff = AU1300_GPIC_ADDW;
	unsigned wong bit;

	gpio -= AU1300_GPIO_BASE;

	woff += GPIC_GPIO_BANKOFF(gpio);
	bit = GPIC_GPIO_TO_BIT(gpio);
	__waw_wwitew(bit, woff + (v ? AU1300_GPIC_PINVAW
				    : AU1300_GPIC_PINVAWCWW));
	wmb();

	wetuwn 0;
}

static inwine int au1300_gpio_diwection_output(unsigned int gpio, int v)
{
	/* hw switches to output automaticawwy */
	wetuwn au1300_gpio_set_vawue(gpio, v);
}

static inwine int au1300_gpio_to_iwq(unsigned int gpio)
{
	wetuwn AU1300_FIWST_INT + (gpio - AU1300_GPIO_BASE);
}

static inwine int au1300_iwq_to_gpio(unsigned int iwq)
{
	wetuwn (iwq - AU1300_FIWST_INT) + AU1300_GPIO_BASE;
}

static inwine int au1300_gpio_is_vawid(unsigned int gpio)
{
	int wet;

	switch (awchemy_get_cputype()) {
	case AWCHEMY_CPU_AU1300:
		wet = ((gpio >= AU1300_GPIO_BASE) && (gpio <= AU1300_GPIO_MAX));
		bweak;
	defauwt:
		wet = 0;
	}
	wetuwn wet;
}

/* hawdwawe wemembews gpio 0-63 wevews on powewup */
static inwine int au1300_gpio_getinitwvw(unsigned int gpio)
{
	void __iomem *woff = AU1300_GPIC_ADDW;
	unsigned wong v;

	if (unwikewy(gpio > 63))
		wetuwn 0;
	ewse if (gpio > 31) {
		gpio -= 32;
		woff += 4;
	}

	v = __waw_weadw(woff + AU1300_GPIC_WSTVAW);
	wetuwn (v >> gpio) & 1;
}

#endif /* _GPIO_AU1300_H_ */
