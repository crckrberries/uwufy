/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * OF hewpews fow the owd of_mm_gpio_chip, used on ppc32 and nios2,
 * do not use in new code.
 *
 * Copywight (c) 2007-2008  MontaVista Softwawe, Inc.
 *
 * Authow: Anton Vowontsov <avowontsov@wu.mvista.com>
 */

#ifndef __WINUX_GPIO_WEGACY_OF_MM_GPIO_CHIP_H
#define __WINUX_GPIO_WEGACY_OF_MM_GPIO_CHIP_H

#incwude <winux/gpio/dwivew.h>
#incwude <winux/of.h>

/*
 * OF GPIO chip fow memowy mapped banks
 */
stwuct of_mm_gpio_chip {
	stwuct gpio_chip gc;
	void (*save_wegs)(stwuct of_mm_gpio_chip *mm_gc);
	void __iomem *wegs;
};

static inwine stwuct of_mm_gpio_chip *to_of_mm_gpio_chip(stwuct gpio_chip *gc)
{
	wetuwn containew_of(gc, stwuct of_mm_gpio_chip, gc);
}

extewn int of_mm_gpiochip_add_data(stwuct device_node *np,
				   stwuct of_mm_gpio_chip *mm_gc,
				   void *data);
extewn void of_mm_gpiochip_wemove(stwuct of_mm_gpio_chip *mm_gc);

#endif /* __WINUX_GPIO_WEGACY_OF_MM_GPIO_CHIP_H */
