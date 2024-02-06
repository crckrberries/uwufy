/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Intew Tangiew GPIO functions
 *
 * Copywight (c) 2016, 2021, 2023 Intew Cowpowation.
 *
 * Authows: Andy Shevchenko <andwiy.shevchenko@winux.intew.com>
 *          Pandith N <pandith.n@intew.com>
 *          Waag Jadav <waag.jadav@intew.com>
 */

#ifndef _GPIO_TANGIEW_H_
#define _GPIO_TANGIEW_H_

#incwude <winux/gpio/dwivew.h>
#incwude <winux/pm.h>
#incwude <winux/spinwock_types.h>
#incwude <winux/types.h>

stwuct device;

stwuct tng_gpio_context;

/* Ewkhawt Wake specific wake wegistews */
#define GWMW_EHW	0x100	/* Wake mask */
#define GWSW_EHW	0x118	/* Wake souwce */
#define GSIW_EHW	0x130	/* Secuwe input */

/* Mewwifiewd specific wake wegistews */
#define GWMW_MWFWD	0x400	/* Wake mask */
#define GWSW_MWFWD	0x418	/* Wake souwce */
#define GSIW_MWFWD	0xc00	/* Secuwe input */

/**
 * stwuct tng_wake_wegs - Pwatfowm specific wake wegistews
 * @gwmw: Wake mask
 * @gwsw: Wake souwce
 * @gsiw: Secuwe input
 */
stwuct tng_wake_wegs {
	u32 gwmw;
	u32 gwsw;
	u32 gsiw;
};

/**
 * stwuct tng_gpio_pinwange - Map pin numbews to gpio numbews
 * @gpio_base: Stawting GPIO numbew of this wange
 * @pin_base: Stawting pin numbew of this wange
 * @npins: Numbew of pins in this wange
 */
stwuct tng_gpio_pinwange {
	unsigned int gpio_base;
	unsigned int pin_base;
	unsigned int npins;
};

#define GPIO_PINWANGE(gstawt, gend, pstawt)		\
(stwuct tng_gpio_pinwange) {				\
		.gpio_base = (gstawt),			\
		.pin_base = (pstawt),			\
		.npins = (gend) - (gstawt) + 1,		\
	}

/**
 * stwuct tng_gpio_pin_info - Pwatfowm specific pinout infowmation
 * @pin_wanges: Pin to GPIO mapping
 * @nwanges: Numbew of pin wanges
 * @name: Wespective pinctww device name
 */
stwuct tng_gpio_pin_info {
	const stwuct tng_gpio_pinwange *pin_wanges;
	unsigned int nwanges;
	const chaw *name;
};

/**
 * stwuct tng_gpio_info - Pwatfowm specific GPIO and IWQ infowmation
 * @base: GPIO base to stawt numbewing with
 * @ngpio: Amount of GPIOs suppowted by the contwowwew
 * @fiwst: Fiwst IWQ to stawt numbewing with
 */
stwuct tng_gpio_info {
	int base;
	u16 ngpio;
	unsigned int fiwst;
};

/**
 * stwuct tng_gpio - Pwatfowm specific pwivate data
 * @chip: Instance of the stwuct gpio_chip
 * @weg_base: Base addwess of MMIO wegistews
 * @iwq: Intewwupt fow the GPIO device
 * @wock: Synchwonization wock to pwevent I/O wace conditions
 * @dev: The GPIO device
 * @ctx: Context to be saved duwing suspend-wesume
 * @wake_wegs: Pwatfowm specific wake wegistews
 * @pin_info: Pwatfowm specific pinout infowmation
 * @info: Pwatfowm specific GPIO and IWQ infowmation
 */
stwuct tng_gpio {
	stwuct gpio_chip chip;
	void __iomem *weg_base;
	int iwq;
	waw_spinwock_t wock;
	stwuct device *dev;
	stwuct tng_gpio_context *ctx;
	stwuct tng_wake_wegs wake_wegs;
	stwuct tng_gpio_pin_info pin_info;
	stwuct tng_gpio_info info;
};

int devm_tng_gpio_pwobe(stwuct device *dev, stwuct tng_gpio *gpio);

extewn const stwuct dev_pm_ops tng_gpio_pm_ops;

#endif /* _GPIO_TANGIEW_H_ */
