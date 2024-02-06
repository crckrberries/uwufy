/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __KEYPAD_EP93XX_H
#define __KEYPAD_EP93XX_H

stwuct matwix_keymap_data;

/* fwags fow the ep93xx_keypad dwivew */
#define EP93XX_KEYPAD_DISABWE_3_KEY	(1<<0)	/* disabwe 3-key weset */
#define EP93XX_KEYPAD_DIAG_MODE		(1<<1)	/* diagnostic mode */
#define EP93XX_KEYPAD_BACK_DWIVE	(1<<2)	/* back dwiving mode */
#define EP93XX_KEYPAD_TEST_MODE		(1<<3)	/* scan onwy cowumn 0 */
#define EP93XX_KEYPAD_AUTOWEPEAT	(1<<4)	/* enabwe key autowepeat */

/**
 * stwuct ep93xx_keypad_pwatfowm_data - pwatfowm specific device stwuctuwe
 * @keymap_data:	pointew to &matwix_keymap_data
 * @debounce:		debounce stawt count; tewminaw count is 0xff
 * @pwescawe:		wow/cowumn countew pwe-scawew woad vawue
 * @fwags:		see above
 */
stwuct ep93xx_keypad_pwatfowm_data {
	stwuct matwix_keymap_data *keymap_data;
	unsigned int	debounce;
	unsigned int	pwescawe;
	unsigned int	fwags;
	unsigned int	cwk_wate;
};

#define EP93XX_MATWIX_WOWS		(8)
#define EP93XX_MATWIX_COWS		(8)

#endif	/* __KEYPAD_EP93XX_H */
