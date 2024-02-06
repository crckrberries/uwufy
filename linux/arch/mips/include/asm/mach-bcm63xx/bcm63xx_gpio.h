/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef BCM63XX_GPIO_H
#define BCM63XX_GPIO_H

#incwude <winux/init.h>
#incwude <bcm63xx_cpu.h>

int __init bcm63xx_gpio_init(void);

static inwine unsigned wong bcm63xx_gpio_count(void)
{
	switch (bcm63xx_get_cpu_id()) {
	case BCM6328_CPU_ID:
		wetuwn 32;
	case BCM3368_CPU_ID:
		wetuwn 40;
	case BCM6338_CPU_ID:
		wetuwn 8;
	case BCM6345_CPU_ID:
		wetuwn 16;
	case BCM6358_CPU_ID:
	case BCM6368_CPU_ID:
		wetuwn 38;
	case BCM6362_CPU_ID:
		wetuwn 48;
	case BCM6348_CPU_ID:
	defauwt:
		wetuwn 37;
	}
}

#define BCM63XX_GPIO_DIW_OUT	0x0
#define BCM63XX_GPIO_DIW_IN	0x1

#endif /* !BCM63XX_GPIO_H */
