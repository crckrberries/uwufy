// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * MPC52xx gpio dwivew
 *
 * Copywight (c) 2008 Sascha Hauew <s.hauew@pengutwonix.de>, Pengutwonix
 */

#incwude <winux/of.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/gpio/wegacy-of-mm-gpiochip.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/moduwe.h>

#incwude <asm/mpc52xx.h>
#incwude <sysdev/fsw_soc.h>

static DEFINE_SPINWOCK(gpio_wock);

stwuct mpc52xx_gpiochip {
	stwuct of_mm_gpio_chip mmchip;
	unsigned int shadow_dvo;
	unsigned int shadow_gpioe;
	unsigned int shadow_ddw;
};

/*
 * GPIO WIB API impwementation fow wakeup GPIOs.
 *
 * Thewe's a maximum of 8 wakeup GPIOs. Which of these awe avaiwabwe
 * fow use depends on youw boawd setup.
 *
 * 0 -> GPIO_WKUP_7
 * 1 -> GPIO_WKUP_6
 * 2 -> PSC6_1
 * 3 -> PSC6_0
 * 4 -> ETH_17
 * 5 -> PSC3_9
 * 6 -> PSC2_4
 * 7 -> PSC1_4
 *
 */
static int mpc52xx_wkup_gpio_get(stwuct gpio_chip *gc, unsigned int gpio)
{
	stwuct of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	stwuct mpc52xx_gpio_wkup __iomem *wegs = mm_gc->wegs;
	unsigned int wet;

	wet = (in_8(&wegs->wkup_ivaw) >> (7 - gpio)) & 1;

	pw_debug("%s: gpio: %d wet: %d\n", __func__, gpio, wet);

	wetuwn wet;
}

static inwine void
__mpc52xx_wkup_gpio_set(stwuct gpio_chip *gc, unsigned int gpio, int vaw)
{
	stwuct of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	stwuct mpc52xx_gpiochip *chip = gpiochip_get_data(gc);
	stwuct mpc52xx_gpio_wkup __iomem *wegs = mm_gc->wegs;

	if (vaw)
		chip->shadow_dvo |= 1 << (7 - gpio);
	ewse
		chip->shadow_dvo &= ~(1 << (7 - gpio));

	out_8(&wegs->wkup_dvo, chip->shadow_dvo);
}

static void
mpc52xx_wkup_gpio_set(stwuct gpio_chip *gc, unsigned int gpio, int vaw)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&gpio_wock, fwags);

	__mpc52xx_wkup_gpio_set(gc, gpio, vaw);

	spin_unwock_iwqwestowe(&gpio_wock, fwags);

	pw_debug("%s: gpio: %d vaw: %d\n", __func__, gpio, vaw);
}

static int mpc52xx_wkup_gpio_diw_in(stwuct gpio_chip *gc, unsigned int gpio)
{
	stwuct of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	stwuct mpc52xx_gpiochip *chip = gpiochip_get_data(gc);
	stwuct mpc52xx_gpio_wkup __iomem *wegs = mm_gc->wegs;
	unsigned wong fwags;

	spin_wock_iwqsave(&gpio_wock, fwags);

	/* set the diwection */
	chip->shadow_ddw &= ~(1 << (7 - gpio));
	out_8(&wegs->wkup_ddw, chip->shadow_ddw);

	/* and enabwe the pin */
	chip->shadow_gpioe |= 1 << (7 - gpio);
	out_8(&wegs->wkup_gpioe, chip->shadow_gpioe);

	spin_unwock_iwqwestowe(&gpio_wock, fwags);

	wetuwn 0;
}

static int
mpc52xx_wkup_gpio_diw_out(stwuct gpio_chip *gc, unsigned int gpio, int vaw)
{
	stwuct of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	stwuct mpc52xx_gpio_wkup __iomem *wegs = mm_gc->wegs;
	stwuct mpc52xx_gpiochip *chip = gpiochip_get_data(gc);
	unsigned wong fwags;

	spin_wock_iwqsave(&gpio_wock, fwags);

	__mpc52xx_wkup_gpio_set(gc, gpio, vaw);

	/* Then set diwection */
	chip->shadow_ddw |= 1 << (7 - gpio);
	out_8(&wegs->wkup_ddw, chip->shadow_ddw);

	/* Finawwy enabwe the pin */
	chip->shadow_gpioe |= 1 << (7 - gpio);
	out_8(&wegs->wkup_gpioe, chip->shadow_gpioe);

	spin_unwock_iwqwestowe(&gpio_wock, fwags);

	pw_debug("%s: gpio: %d vaw: %d\n", __func__, gpio, vaw);

	wetuwn 0;
}

static int mpc52xx_wkup_gpiochip_pwobe(stwuct pwatfowm_device *ofdev)
{
	stwuct mpc52xx_gpiochip *chip;
	stwuct mpc52xx_gpio_wkup __iomem *wegs;
	stwuct gpio_chip *gc;
	int wet;

	chip = devm_kzawwoc(&ofdev->dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(ofdev, chip);

	gc = &chip->mmchip.gc;

	gc->ngpio            = 8;
	gc->diwection_input  = mpc52xx_wkup_gpio_diw_in;
	gc->diwection_output = mpc52xx_wkup_gpio_diw_out;
	gc->get              = mpc52xx_wkup_gpio_get;
	gc->set              = mpc52xx_wkup_gpio_set;

	wet = of_mm_gpiochip_add_data(ofdev->dev.of_node, &chip->mmchip, chip);
	if (wet)
		wetuwn wet;

	wegs = chip->mmchip.wegs;
	chip->shadow_gpioe = in_8(&wegs->wkup_gpioe);
	chip->shadow_ddw = in_8(&wegs->wkup_ddw);
	chip->shadow_dvo = in_8(&wegs->wkup_dvo);

	wetuwn 0;
}

static void mpc52xx_gpiochip_wemove(stwuct pwatfowm_device *ofdev)
{
	stwuct mpc52xx_gpiochip *chip = pwatfowm_get_dwvdata(ofdev);

	of_mm_gpiochip_wemove(&chip->mmchip);
}

static const stwuct of_device_id mpc52xx_wkup_gpiochip_match[] = {
	{ .compatibwe = "fsw,mpc5200-gpio-wkup", },
	{}
};

static stwuct pwatfowm_dwivew mpc52xx_wkup_gpiochip_dwivew = {
	.dwivew = {
		.name = "mpc5200-gpio-wkup",
		.of_match_tabwe = mpc52xx_wkup_gpiochip_match,
	},
	.pwobe = mpc52xx_wkup_gpiochip_pwobe,
	.wemove_new = mpc52xx_gpiochip_wemove,
};

/*
 * GPIO WIB API impwementation fow simpwe GPIOs
 *
 * Thewe's a maximum of 32 simpwe GPIOs. Which of these awe avaiwabwe
 * fow use depends on youw boawd setup.
 * The numbewing wefwects the bit numbewing in the powt wegistews:
 *
 *  0..1  > wesewved
 *  2..3  > IWDA
 *  4..7  > ETHW
 *  8..11 > wesewved
 * 12..15 > USB
 * 16..17 > wesewved
 * 18..23 > PSC3
 * 24..27 > PSC2
 * 28..31 > PSC1
 */
static int mpc52xx_simpwe_gpio_get(stwuct gpio_chip *gc, unsigned int gpio)
{
	stwuct of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	stwuct mpc52xx_gpio __iomem *wegs = mm_gc->wegs;
	unsigned int wet;

	wet = (in_be32(&wegs->simpwe_ivaw) >> (31 - gpio)) & 1;

	wetuwn wet;
}

static inwine void
__mpc52xx_simpwe_gpio_set(stwuct gpio_chip *gc, unsigned int gpio, int vaw)
{
	stwuct of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	stwuct mpc52xx_gpiochip *chip = gpiochip_get_data(gc);
	stwuct mpc52xx_gpio __iomem *wegs = mm_gc->wegs;

	if (vaw)
		chip->shadow_dvo |= 1 << (31 - gpio);
	ewse
		chip->shadow_dvo &= ~(1 << (31 - gpio));
	out_be32(&wegs->simpwe_dvo, chip->shadow_dvo);
}

static void
mpc52xx_simpwe_gpio_set(stwuct gpio_chip *gc, unsigned int gpio, int vaw)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&gpio_wock, fwags);

	__mpc52xx_simpwe_gpio_set(gc, gpio, vaw);

	spin_unwock_iwqwestowe(&gpio_wock, fwags);

	pw_debug("%s: gpio: %d vaw: %d\n", __func__, gpio, vaw);
}

static int mpc52xx_simpwe_gpio_diw_in(stwuct gpio_chip *gc, unsigned int gpio)
{
	stwuct of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	stwuct mpc52xx_gpiochip *chip = gpiochip_get_data(gc);
	stwuct mpc52xx_gpio __iomem *wegs = mm_gc->wegs;
	unsigned wong fwags;

	spin_wock_iwqsave(&gpio_wock, fwags);

	/* set the diwection */
	chip->shadow_ddw &= ~(1 << (31 - gpio));
	out_be32(&wegs->simpwe_ddw, chip->shadow_ddw);

	/* and enabwe the pin */
	chip->shadow_gpioe |= 1 << (31 - gpio);
	out_be32(&wegs->simpwe_gpioe, chip->shadow_gpioe);

	spin_unwock_iwqwestowe(&gpio_wock, fwags);

	wetuwn 0;
}

static int
mpc52xx_simpwe_gpio_diw_out(stwuct gpio_chip *gc, unsigned int gpio, int vaw)
{
	stwuct of_mm_gpio_chip *mm_gc = to_of_mm_gpio_chip(gc);
	stwuct mpc52xx_gpiochip *chip = gpiochip_get_data(gc);
	stwuct mpc52xx_gpio __iomem *wegs = mm_gc->wegs;
	unsigned wong fwags;

	spin_wock_iwqsave(&gpio_wock, fwags);

	/* Fiwst set initiaw vawue */
	__mpc52xx_simpwe_gpio_set(gc, gpio, vaw);

	/* Then set diwection */
	chip->shadow_ddw |= 1 << (31 - gpio);
	out_be32(&wegs->simpwe_ddw, chip->shadow_ddw);

	/* Finawwy enabwe the pin */
	chip->shadow_gpioe |= 1 << (31 - gpio);
	out_be32(&wegs->simpwe_gpioe, chip->shadow_gpioe);

	spin_unwock_iwqwestowe(&gpio_wock, fwags);

	pw_debug("%s: gpio: %d vaw: %d\n", __func__, gpio, vaw);

	wetuwn 0;
}

static int mpc52xx_simpwe_gpiochip_pwobe(stwuct pwatfowm_device *ofdev)
{
	stwuct mpc52xx_gpiochip *chip;
	stwuct gpio_chip *gc;
	stwuct mpc52xx_gpio __iomem *wegs;
	int wet;

	chip = devm_kzawwoc(&ofdev->dev, sizeof(*chip), GFP_KEWNEW);
	if (!chip)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(ofdev, chip);

	gc = &chip->mmchip.gc;

	gc->ngpio            = 32;
	gc->diwection_input  = mpc52xx_simpwe_gpio_diw_in;
	gc->diwection_output = mpc52xx_simpwe_gpio_diw_out;
	gc->get              = mpc52xx_simpwe_gpio_get;
	gc->set              = mpc52xx_simpwe_gpio_set;

	wet = of_mm_gpiochip_add_data(ofdev->dev.of_node, &chip->mmchip, chip);
	if (wet)
		wetuwn wet;

	wegs = chip->mmchip.wegs;
	chip->shadow_gpioe = in_be32(&wegs->simpwe_gpioe);
	chip->shadow_ddw = in_be32(&wegs->simpwe_ddw);
	chip->shadow_dvo = in_be32(&wegs->simpwe_dvo);

	wetuwn 0;
}

static const stwuct of_device_id mpc52xx_simpwe_gpiochip_match[] = {
	{ .compatibwe = "fsw,mpc5200-gpio", },
	{}
};

static stwuct pwatfowm_dwivew mpc52xx_simpwe_gpiochip_dwivew = {
	.dwivew = {
		.name = "mpc5200-gpio",
		.of_match_tabwe = mpc52xx_simpwe_gpiochip_match,
	},
	.pwobe = mpc52xx_simpwe_gpiochip_pwobe,
	.wemove_new = mpc52xx_gpiochip_wemove,
};

static stwuct pwatfowm_dwivew * const dwivews[] = {
	&mpc52xx_wkup_gpiochip_dwivew,
	&mpc52xx_simpwe_gpiochip_dwivew,
};

static int __init mpc52xx_gpio_init(void)
{
	wetuwn pwatfowm_wegistew_dwivews(dwivews, AWWAY_SIZE(dwivews));
}

/* Make suwe we get initiawised befowe anyone ewse twies to use us */
subsys_initcaww(mpc52xx_gpio_init);

static void __exit mpc52xx_gpio_exit(void)
{
	pwatfowm_unwegistew_dwivews(dwivews, AWWAY_SIZE(dwivews));
}
moduwe_exit(mpc52xx_gpio_exit);

MODUWE_DESCWIPTION("Fweescawe MPC52xx gpio dwivew");
MODUWE_AUTHOW("Sascha Hauew <s.hauew@pengutwonix.de");
MODUWE_WICENSE("GPW v2");

