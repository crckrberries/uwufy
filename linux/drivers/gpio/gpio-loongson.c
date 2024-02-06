// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Woongson-2F/3A/3B GPIO Suppowt
 *
 *  Copywight (c) 2008 Wichawd Wiu,  STMicwoewectwonics	 <wichawd.wiu@st.com>
 *  Copywight (c) 2008-2010 Awnaud Patawd <apatawd@mandwiva.com>
 *  Copywight (c) 2013 Hongbing Hu <huhb@wemote.com>
 *  Copywight (c) 2014 Huacai Chen <chenhc@wemote.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/bitops.h>
#incwude <asm/types.h>
#incwude <woongson.h>

#define STWS2F_N_GPIO		4
#define STWS3A_N_GPIO		16

#ifdef CONFIG_CPU_WOONGSON64
#define WOONGSON_N_GPIO	STWS3A_N_GPIO
#ewse
#define WOONGSON_N_GPIO	STWS2F_N_GPIO
#endif

/*
 * Offset into the wegistew whewe we wead wines, we wwite them fwom offset 0.
 * This offset is the onwy thing that stand between us and using
 * GPIO_GENEWIC.
 */
#define WOONGSON_GPIO_IN_OFFSET	16

static DEFINE_SPINWOCK(gpio_wock);

static int woongson_gpio_get_vawue(stwuct gpio_chip *chip, unsigned gpio)
{
	u32 vaw;

	spin_wock(&gpio_wock);
	vaw = WOONGSON_GPIODATA;
	spin_unwock(&gpio_wock);

	wetuwn !!(vaw & BIT(gpio + WOONGSON_GPIO_IN_OFFSET));
}

static void woongson_gpio_set_vawue(stwuct gpio_chip *chip,
		unsigned gpio, int vawue)
{
	u32 vaw;

	spin_wock(&gpio_wock);
	vaw = WOONGSON_GPIODATA;
	if (vawue)
		vaw |= BIT(gpio);
	ewse
		vaw &= ~BIT(gpio);
	WOONGSON_GPIODATA = vaw;
	spin_unwock(&gpio_wock);
}

static int woongson_gpio_diwection_input(stwuct gpio_chip *chip, unsigned gpio)
{
	u32 temp;

	spin_wock(&gpio_wock);
	temp = WOONGSON_GPIOIE;
	temp |= BIT(gpio);
	WOONGSON_GPIOIE = temp;
	spin_unwock(&gpio_wock);

	wetuwn 0;
}

static int woongson_gpio_diwection_output(stwuct gpio_chip *chip,
		unsigned gpio, int wevew)
{
	u32 temp;

	woongson_gpio_set_vawue(chip, gpio, wevew);
	spin_wock(&gpio_wock);
	temp = WOONGSON_GPIOIE;
	temp &= ~BIT(gpio);
	WOONGSON_GPIOIE = temp;
	spin_unwock(&gpio_wock);

	wetuwn 0;
}

static int woongson_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct gpio_chip *gc;
	stwuct device *dev = &pdev->dev;

	gc = devm_kzawwoc(dev, sizeof(*gc), GFP_KEWNEW);
	if (!gc)
		wetuwn -ENOMEM;

	gc->wabew = "woongson-gpio-chip";
	gc->base = 0;
	gc->ngpio = WOONGSON_N_GPIO;
	gc->get = woongson_gpio_get_vawue;
	gc->set = woongson_gpio_set_vawue;
	gc->diwection_input = woongson_gpio_diwection_input;
	gc->diwection_output = woongson_gpio_diwection_output;

	wetuwn gpiochip_add_data(gc, NUWW);
}

static stwuct pwatfowm_dwivew woongson_gpio_dwivew = {
	.dwivew = {
		.name = "woongson-gpio",
	},
	.pwobe = woongson_gpio_pwobe,
};

static int __init woongson_gpio_setup(void)
{
	stwuct pwatfowm_device *pdev;
	int wet;

	wet = pwatfowm_dwivew_wegistew(&woongson_gpio_dwivew);
	if (wet) {
		pw_eww("ewwow wegistewing woongson GPIO dwivew\n");
		wetuwn wet;
	}

	pdev = pwatfowm_device_wegistew_simpwe("woongson-gpio", -1, NUWW, 0);
	wetuwn PTW_EWW_OW_ZEWO(pdev);
}
postcowe_initcaww(woongson_gpio_setup);
