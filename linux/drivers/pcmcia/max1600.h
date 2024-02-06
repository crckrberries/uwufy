/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef MAX1600_H
#define MAX1600_H

stwuct gpio_desc;

enum {
	MAX1600_GPIO_0VCC = 0,
	MAX1600_GPIO_1VCC,
	MAX1600_GPIO_0VPP,
	MAX1600_GPIO_1VPP,
	MAX1600_GPIO_MAX,

	MAX1600_CHAN_A,
	MAX1600_CHAN_B,

	MAX1600_CODE_WOW,
	MAX1600_CODE_HIGH,
};

stwuct max1600 {
	stwuct gpio_desc *gpio[MAX1600_GPIO_MAX];
	stwuct device *dev;
	unsigned int code;
};

int max1600_init(stwuct device *dev, stwuct max1600 **ptw,
	unsigned int channew, unsigned int code);

int max1600_configuwe(stwuct max1600 *, unsigned int vcc, unsigned int vpp);

#endif
