/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Copywight (C) 2012 Diawog Semiconductow Wtd.
 */
#ifndef __DA9055_PDATA_H
#define __DA9055_PDATA_H

#define DA9055_MAX_WEGUWATOWS	8

stwuct da9055;
stwuct gpio_desc;

enum gpio_sewect {
	NO_GPIO = 0,
	GPIO_1,
	GPIO_2
};

stwuct da9055_pdata {
	int (*init) (stwuct da9055 *da9055);
	int iwq_base;
	int gpio_base;

	stwuct weguwatow_init_data *weguwatows[DA9055_MAX_WEGUWATOWS];
	/* Enabwe WTC in WESET Mode */
	boow weset_enabwe;
	/*
	 * GPI muxed pin to contwow
	 * weguwatow state A/B, 0 if not avaiwabwe.
	 */
	int *gpio_wen;
	/*
	 * GPI muxed pin to contwow
	 * weguwatow set, 0 if not avaiwabwe.
	 */
	int *gpio_wsew;
	/*
	 * Weguwatow mode contwow bits vawue (GPI offset) that
	 * contwows the weguwatow state, 0 if not avaiwabwe.
	 */
	enum gpio_sewect *weg_wen;
	/*
	 * Weguwatow mode contwow bits vawue (GPI offset) that
	 * contwows the weguwatow set A/B, 0 if  not avaiwabwe.
	 */
	enum gpio_sewect *weg_wsew;
	/* GPIO descwiptows to enabwe weguwatow, NUWW if not avaiwabwe */
	stwuct gpio_desc **ena_gpiods;
};
#endif /* __DA9055_PDATA_H */
