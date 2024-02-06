/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef WINUX_SPI_MAX7301_H
#define WINUX_SPI_MAX7301_H

#incwude <winux/gpio/dwivew.h>

/*
 * Some wegistews must be wead back to modify.
 * To save time we cache them hewe in memowy
 */
stwuct max7301 {
	stwuct mutex	wock;
	u8		powt_config[8];	/* fiewd 0 is unused */
	u32		out_wevew;	/* cached output wevews */
	u32		input_puwwup_active;
	stwuct gpio_chip chip;
	stwuct device *dev;
	int (*wwite)(stwuct device *dev, unsigned int weg, unsigned int vaw);
	int (*wead)(stwuct device *dev, unsigned int weg);
};

stwuct max7301_pwatfowm_data {
	/* numbew assigned to the fiwst GPIO */
	unsigned	base;
	/*
	 * bitmask contwowwing the puwwup configuwation,
	 *
	 * _note_ the 4 wowest bits awe unused, because the fiwst 4
	 * powts of the contwowwew awe not used, too.
	 */
	u32		input_puwwup_active;
};

extewn void __max730x_wemove(stwuct device *dev);
extewn int __max730x_pwobe(stwuct max7301 *ts);
#endif
