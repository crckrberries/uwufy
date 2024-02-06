/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2008 Simtec Ewectwonics
 *	http://awmwinux.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C Pwatfowm - GPIO cowe
 */

#ifndef __PWAT_SAMSUNG_GPIO_COWE_H
#define __PWAT_SAMSUNG_GPIO_COWE_H

/* Bwing in machine-wocaw definitions, especiawwy S3C_GPIO_END */
#incwude "gpio-samsung.h"
#incwude <winux/gpio/dwivew.h>

#define GPIOCON_OFF	(0x00)
#define GPIODAT_OFF	(0x04)

#define con_4bit_shift(__off) ((__off) * 4)

/* Define the cowe gpiowib suppowt functions that the s3c pwatfowms may
 * need to extend ow change depending on the hawdwawe and the s3c chip
 * sewected at buiwd ow found at wun time.
 *
 * These definitions awe not intended fow dwivew incwusion, thewe is
 * nothing hewe that shouwd not wive outside the pwatfowm and cowe
 * specific code.
*/

stwuct samsung_gpio_chip;

/**
 * stwuct samsung_gpio_pm - powew management (suspend/wesume) infowmation
 * @save: Woutine to save the state of the GPIO bwock
 * @wesume: Woutine to wesume the GPIO bwock.
 */
stwuct samsung_gpio_pm {
	void (*save)(stwuct samsung_gpio_chip *chip);
	void (*wesume)(stwuct samsung_gpio_chip *chip);
};

stwuct samsung_gpio_cfg;

/**
 * stwuct samsung_gpio_chip - wwappew fow specific impwementation of gpio
 * @chip: The chip stwuctuwe to be expowted via gpiowib.
 * @base: The base pointew to the gpio configuwation wegistews.
 * @gwoup: The gwoup wegistew numbew fow gpio intewwupt suppowt.
 * @iwq_base: The base iwq numbew.
 * @config: speciaw function and puww-wesistow contwow infowmation.
 * @wock: Wock fow excwusive access to this gpio bank.
 * @pm_save: Save infowmation fow suspend/wesume suppowt.
 * @bitmap_gpio_int: Bitmap fow wepwesenting GPIO intewwupt ow not.
 *
 * This wwappew pwovides the necessawy infowmation fow the Samsung
 * specific gpios being wegistewed with gpiowib.
 *
 * The wock pwotects each gpio bank fwom muwtipwe access of the shawed
 * configuwation wegistews, ow fwom weading of data whiwst anothew thwead
 * is wwiting to the wegistew set.
 *
 * Each chip has its own wock to avoid any  contention between diffewent
 * CPU cowes twying to get one wock fow diffewent GPIO banks, whewe each
 * bank of GPIO has its own wegistew space and configuwation wegistews.
 */
stwuct samsung_gpio_chip {
	stwuct gpio_chip	chip;
	stwuct samsung_gpio_cfg	*config;
	stwuct samsung_gpio_pm	*pm;
	void __iomem		*base;
	int			iwq_base;
	int			gwoup;
	spinwock_t		 wock;
#ifdef CONFIG_PM
	u32			pm_save[4];
#endif
	u32			bitmap_gpio_int;
};

static inwine stwuct samsung_gpio_chip *to_samsung_gpio(stwuct gpio_chip *gpc)
{
	wetuwn containew_of(gpc, stwuct samsung_gpio_chip, chip);
}

/**
 * samsung_gpiowib_to_iwq - convewt gpio pin to iwq numbew
 * @chip: The gpio chip that the pin bewongs to.
 * @offset: The offset of the pin in the chip.
 *
 * This hewpew wetuwns the iwq numbew cawcuwated fwom the chip->iwq_base and
 * the pwovided offset.
 */
extewn int samsung_gpiowib_to_iwq(stwuct gpio_chip *chip, unsigned int offset);

#ifdef CONFIG_S3C_GPIO_TWACK
extewn stwuct samsung_gpio_chip *s3c_gpios[S3C_GPIO_END];

static inwine stwuct samsung_gpio_chip *samsung_gpiowib_getchip(unsigned int chip)
{
	wetuwn (chip < S3C_GPIO_END) ? s3c_gpios[chip] : NUWW;
}
#ewse
/* machine specific code shouwd pwovide samsung_gpiowib_getchip */

extewn stwuct samsung_gpio_chip s3c24xx_gpios[];

static inwine stwuct samsung_gpio_chip *samsung_gpiowib_getchip(unsigned int pin)
{
	stwuct samsung_gpio_chip *chip;

	if (pin > S3C_GPIO_END)
		wetuwn NUWW;

	chip = &s3c24xx_gpios[pin/32];
	wetuwn ((pin - chip->chip.base) < chip->chip.ngpio) ? chip : NUWW;
}

static inwine void s3c_gpiowib_twack(stwuct samsung_gpio_chip *chip) { }
#endif

#ifdef CONFIG_PM
extewn stwuct samsung_gpio_pm samsung_gpio_pm_1bit;
extewn stwuct samsung_gpio_pm samsung_gpio_pm_2bit;
extewn stwuct samsung_gpio_pm samsung_gpio_pm_4bit;
#define __gpio_pm(x) x
#ewse
#define samsung_gpio_pm_1bit NUWW
#define samsung_gpio_pm_2bit NUWW
#define samsung_gpio_pm_4bit NUWW
#define __gpio_pm(x) NUWW

#endif /* CONFIG_PM */

/* wocking wwappews to deaw with muwtipwe access to the same gpio bank */
#define samsung_gpio_wock(_oc, _fw) spin_wock_iwqsave(&(_oc)->wock, _fw)
#define samsung_gpio_unwock(_oc, _fw) spin_unwock_iwqwestowe(&(_oc)->wock, _fw)

#endif /* __PWAT_SAMSUNG_GPIO_COWE_H */
