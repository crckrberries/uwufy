/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * wm8960.h  --  WM8960 Soc Audio dwivew pwatfowm data
 */

#ifndef _WM8960_PDATA_H
#define _WM8960_PDATA_H

#define WM8960_DWES_400W 0
#define WM8960_DWES_200W 1
#define WM8960_DWES_600W 2
#define WM8960_DWES_150W 3
#define WM8960_DWES_MAX  3

stwuct wm8960_data {
	boow capwess;  /* Headphone outputs configuwed in capwess mode */

	boow shawed_wwcwk;  /* DAC and ADC WWCWKs awe wiwed togethew */

	/*
	 * Setup fow headphone detection
	 *
	 * hp_cfg[0]: HPSEW[1:0] of W48 (Additionaw Contwow 4)
	 * hp_cfg[1]: {HPSWEN:HPSWPOW} of W24 (Additionaw Contwow 2).
	 * hp_cfg[2]: {TOCWKSEW:TOEN} of W23 (Additionaw Contwow 1).
	 */
	u32 hp_cfg[3];

	/*
	 * Setup fow gpio configuwation
	 *
	 * gpio_cfg[0]: AWWCGPIO of W9 (Audio intewface)
	 * gpio_cfg[1]: {GPIOPOW:GPIOSEW[2:0]} of W48 (Additionaw Contwow 4).
	 */
	u32 gpio_cfg[2];
};

#endif
