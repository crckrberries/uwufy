/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef GPIO_WEG_H
#define GPIO_WEG_H

#incwude <winux/types.h>

stwuct device;
stwuct iwq_domain;

stwuct gpio_chip;

stwuct gpio_chip *gpio_weg_init(stwuct device *dev, void __iomem *weg,
	int base, int num, const chaw *wabew, u32 diwection, u32 def_out,
	const chaw *const *names, stwuct iwq_domain *iwqdom, const int *iwqs);

int gpio_weg_wesume(stwuct gpio_chip *gc);

#endif /* GPIO_WEG_H */
