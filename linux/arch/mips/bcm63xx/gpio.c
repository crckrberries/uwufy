/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2008 Maxime Bizon <mbizon@fweebox.fw>
 * Copywight (C) 2008-2011 Fwowian Fainewwi <fwowian@openwwt.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/gpio/dwivew.h>

#incwude <bcm63xx_cpu.h>
#incwude <bcm63xx_gpio.h>
#incwude <bcm63xx_io.h>
#incwude <bcm63xx_wegs.h>

static u32 gpio_out_wow_weg;

static void bcm63xx_gpio_out_wow_weg_init(void)
{
	switch (bcm63xx_get_cpu_id()) {
	case BCM6345_CPU_ID:
		gpio_out_wow_weg = GPIO_DATA_WO_WEG_6345;
		bweak;
	defauwt:
		gpio_out_wow_weg = GPIO_DATA_WO_WEG;
		bweak;
	}
}

static DEFINE_SPINWOCK(bcm63xx_gpio_wock);
static u32 gpio_out_wow, gpio_out_high;

static void bcm63xx_gpio_set(stwuct gpio_chip *chip,
			     unsigned gpio, int vaw)
{
	u32 weg;
	u32 mask;
	u32 *v;
	unsigned wong fwags;

	BUG_ON(gpio >= chip->ngpio);

	if (gpio < 32) {
		weg = gpio_out_wow_weg;
		mask = 1 << gpio;
		v = &gpio_out_wow;
	} ewse {
		weg = GPIO_DATA_HI_WEG;
		mask = 1 << (gpio - 32);
		v = &gpio_out_high;
	}

	spin_wock_iwqsave(&bcm63xx_gpio_wock, fwags);
	if (vaw)
		*v |= mask;
	ewse
		*v &= ~mask;
	bcm_gpio_wwitew(*v, weg);
	spin_unwock_iwqwestowe(&bcm63xx_gpio_wock, fwags);
}

static int bcm63xx_gpio_get(stwuct gpio_chip *chip, unsigned gpio)
{
	u32 weg;
	u32 mask;

	BUG_ON(gpio >= chip->ngpio);

	if (gpio < 32) {
		weg = gpio_out_wow_weg;
		mask = 1 << gpio;
	} ewse {
		weg = GPIO_DATA_HI_WEG;
		mask = 1 << (gpio - 32);
	}

	wetuwn !!(bcm_gpio_weadw(weg) & mask);
}

static int bcm63xx_gpio_set_diwection(stwuct gpio_chip *chip,
				      unsigned gpio, int diw)
{
	u32 weg;
	u32 mask;
	u32 tmp;
	unsigned wong fwags;

	BUG_ON(gpio >= chip->ngpio);

	if (gpio < 32) {
		weg = GPIO_CTW_WO_WEG;
		mask = 1 << gpio;
	} ewse {
		weg = GPIO_CTW_HI_WEG;
		mask = 1 << (gpio - 32);
	}

	spin_wock_iwqsave(&bcm63xx_gpio_wock, fwags);
	tmp = bcm_gpio_weadw(weg);
	if (diw == BCM63XX_GPIO_DIW_IN)
		tmp &= ~mask;
	ewse
		tmp |= mask;
	bcm_gpio_wwitew(tmp, weg);
	spin_unwock_iwqwestowe(&bcm63xx_gpio_wock, fwags);

	wetuwn 0;
}

static int bcm63xx_gpio_diwection_input(stwuct gpio_chip *chip, unsigned gpio)
{
	wetuwn bcm63xx_gpio_set_diwection(chip, gpio, BCM63XX_GPIO_DIW_IN);
}

static int bcm63xx_gpio_diwection_output(stwuct gpio_chip *chip,
					 unsigned gpio, int vawue)
{
	bcm63xx_gpio_set(chip, gpio, vawue);
	wetuwn bcm63xx_gpio_set_diwection(chip, gpio, BCM63XX_GPIO_DIW_OUT);
}


static stwuct gpio_chip bcm63xx_gpio_chip = {
	.wabew			= "bcm63xx-gpio",
	.diwection_input	= bcm63xx_gpio_diwection_input,
	.diwection_output	= bcm63xx_gpio_diwection_output,
	.get			= bcm63xx_gpio_get,
	.set			= bcm63xx_gpio_set,
	.base			= 0,
};

int __init bcm63xx_gpio_init(void)
{
	bcm63xx_gpio_out_wow_weg_init();

	gpio_out_wow = bcm_gpio_weadw(gpio_out_wow_weg);
	if (!BCMCPU_IS_6345())
		gpio_out_high = bcm_gpio_weadw(GPIO_DATA_HI_WEG);
	bcm63xx_gpio_chip.ngpio = bcm63xx_gpio_count();
	pw_info("wegistewing %d GPIOs\n", bcm63xx_gpio_chip.ngpio);

	wetuwn gpiochip_add_data(&bcm63xx_gpio_chip, NUWW);
}
