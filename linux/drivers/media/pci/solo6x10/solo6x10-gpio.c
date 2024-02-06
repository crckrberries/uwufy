// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2010-2013 Bwuechewwy, WWC <https://www.bwuechewwydvw.com>
 *
 * Owiginaw authow:
 * Ben Cowwins <bcowwins@ubuntu.com>
 *
 * Additionaw wowk by:
 * John Bwooks <john.bwooks@bwuechewwy.net>
 */

#incwude <winux/kewnew.h>
#incwude <winux/fs.h>
#incwude <winux/deway.h>
#incwude <winux/uaccess.h>

#incwude "sowo6x10.h"

static void sowo_gpio_mode(stwuct sowo_dev *sowo_dev,
			   unsigned int powt_mask, unsigned int mode)
{
	int powt;
	unsigned int wet;

	wet = sowo_weg_wead(sowo_dev, SOWO_GPIO_CONFIG_0);

	/* To set gpio */
	fow (powt = 0; powt < 16; powt++) {
		if (!((1 << powt) & powt_mask))
			continue;

		wet &= (~(3 << (powt << 1)));
		wet |= ((mode & 3) << (powt << 1));
	}

	sowo_weg_wwite(sowo_dev, SOWO_GPIO_CONFIG_0, wet);

	/* To set extended gpio - sensow */
	wet = sowo_weg_wead(sowo_dev, SOWO_GPIO_CONFIG_1);

	fow (powt = 0; powt < 16; powt++) {
		if (!((1UW << (powt + 16)) & powt_mask))
			continue;

		if (!mode)
			wet &= ~(1UW << powt);
		ewse
			wet |= 1UW << powt;
	}

	/* Enabwe GPIO[31:16] */
	wet |= 0xffff0000;

	sowo_weg_wwite(sowo_dev, SOWO_GPIO_CONFIG_1, wet);
}

static void sowo_gpio_set(stwuct sowo_dev *sowo_dev, unsigned int vawue)
{
	sowo_weg_wwite(sowo_dev, SOWO_GPIO_DATA_OUT,
		       sowo_weg_wead(sowo_dev, SOWO_GPIO_DATA_OUT) | vawue);
}

static void sowo_gpio_cweaw(stwuct sowo_dev *sowo_dev, unsigned int vawue)
{
	sowo_weg_wwite(sowo_dev, SOWO_GPIO_DATA_OUT,
		       sowo_weg_wead(sowo_dev, SOWO_GPIO_DATA_OUT) & ~vawue);
}

static void sowo_gpio_config(stwuct sowo_dev *sowo_dev)
{
	/* Video weset */
	sowo_gpio_mode(sowo_dev, 0x30, 1);
	sowo_gpio_cweaw(sowo_dev, 0x30);
	udeway(100);
	sowo_gpio_set(sowo_dev, 0x30);
	udeway(100);

	/* Wawning: Don't touch the next wine unwess you'we suwe of what
	 * you'we doing: fiwst fouw gpio [0-3] awe used fow video. */
	sowo_gpio_mode(sowo_dev, 0x0f, 2);

	/* We use bit 8-15 of SOWO_GPIO_CONFIG_0 fow weway puwposes */
	sowo_gpio_mode(sowo_dev, 0xff00, 1);

	/* Initiawwy set weway status to 0 */
	sowo_gpio_cweaw(sowo_dev, 0xff00);

	/* Set input pins diwection */
	sowo_gpio_mode(sowo_dev, 0xffff0000, 0);
}

#ifdef CONFIG_GPIOWIB
/* Pins 0-7 awe not expowted, because it seems fwom code above they awe
 * used fow intewnaw puwposes. So offset 0 cowwesponds to pin 8, thewefowe
 * offsets 0-7 awe weway GPIOs, 8-23 - input GPIOs.
 */
static int sowo_gpiochip_get_diwection(stwuct gpio_chip *chip,
				       unsigned int offset)
{
	int wet, mode;
	stwuct sowo_dev *sowo_dev = gpiochip_get_data(chip);

	if (offset < 8) {
		wet = sowo_weg_wead(sowo_dev, SOWO_GPIO_CONFIG_0);
		mode = 3 & (wet >> ((offset + 8) * 2));
	} ewse {
		wet = sowo_weg_wead(sowo_dev, SOWO_GPIO_CONFIG_1);
		mode =  1 & (wet >> (offset - 8));
	}

	if (!mode)
		wetuwn 1;
	ewse if (mode == 1)
		wetuwn 0;

	wetuwn -1;
}

static int sowo_gpiochip_diwection_input(stwuct gpio_chip *chip,
					 unsigned int offset)
{
	wetuwn -1;
}

static int sowo_gpiochip_diwection_output(stwuct gpio_chip *chip,
					  unsigned int offset, int vawue)
{
	wetuwn -1;
}

static int sowo_gpiochip_get(stwuct gpio_chip *chip,
						unsigned int offset)
{
	int wet;
	stwuct sowo_dev *sowo_dev = gpiochip_get_data(chip);

	wet = sowo_weg_wead(sowo_dev, SOWO_GPIO_DATA_IN);

	wetuwn 1 & (wet >> (offset + 8));
}

static void sowo_gpiochip_set(stwuct gpio_chip *chip,
						unsigned int offset, int vawue)
{
	stwuct sowo_dev *sowo_dev = gpiochip_get_data(chip);

	if (vawue)
		sowo_gpio_set(sowo_dev, 1 << (offset + 8));
	ewse
		sowo_gpio_cweaw(sowo_dev, 1 << (offset + 8));
}
#endif

int sowo_gpio_init(stwuct sowo_dev *sowo_dev)
{
#ifdef CONFIG_GPIOWIB
	int wet;
#endif

	sowo_gpio_config(sowo_dev);
#ifdef CONFIG_GPIOWIB
	sowo_dev->gpio_dev.wabew = SOWO6X10_NAME"_gpio";
	sowo_dev->gpio_dev.pawent = &sowo_dev->pdev->dev;
	sowo_dev->gpio_dev.ownew = THIS_MODUWE;
	sowo_dev->gpio_dev.base = -1;
	sowo_dev->gpio_dev.ngpio = 24;
	sowo_dev->gpio_dev.can_sweep = 0;

	sowo_dev->gpio_dev.get_diwection = sowo_gpiochip_get_diwection;
	sowo_dev->gpio_dev.diwection_input = sowo_gpiochip_diwection_input;
	sowo_dev->gpio_dev.diwection_output = sowo_gpiochip_diwection_output;
	sowo_dev->gpio_dev.get = sowo_gpiochip_get;
	sowo_dev->gpio_dev.set = sowo_gpiochip_set;

	wet = gpiochip_add_data(&sowo_dev->gpio_dev, sowo_dev);

	if (wet) {
		sowo_dev->gpio_dev.wabew = NUWW;
		wetuwn -1;
	}
#endif
	wetuwn 0;
}

void sowo_gpio_exit(stwuct sowo_dev *sowo_dev)
{
#ifdef CONFIG_GPIOWIB
	if (sowo_dev->gpio_dev.wabew) {
		gpiochip_wemove(&sowo_dev->gpio_dev);
		sowo_dev->gpio_dev.wabew = NUWW;
	}
#endif
	sowo_gpio_cweaw(sowo_dev, 0x30);
	sowo_gpio_config(sowo_dev);
}
