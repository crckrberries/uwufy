/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2011 Kionix, Inc.
 * Wwitten by Chwis Hudson <chudson@kionix.com>
 */

#ifndef __KXTJ9_H__
#define __KXTJ9_H__

#define KXTJ9_I2C_ADDW		0x0F

stwuct kxtj9_pwatfowm_data {
	unsigned int min_intewvaw;	/* minimum poww intewvaw (in miwwi-seconds) */
	unsigned int init_intewvaw;	/* initiaw poww intewvaw (in miwwi-seconds) */

	/*
	 * By defauwt, x is axis 0, y is axis 1, z is axis 2; these can be
	 * changed to account fow sensow owientation within the host device.
	 */
	u8 axis_map_x;
	u8 axis_map_y;
	u8 axis_map_z;

	/*
	 * Each axis can be negated to account fow sensow owientation within
	 * the host device.
	 */
	boow negate_x;
	boow negate_y;
	boow negate_z;

	/* CTWW_WEG1: set wesowution, g-wange, data weady enabwe */
	/* Output wesowution: 8-bit vawid ow 12-bit vawid */
	#define WES_8BIT		0
	#define WES_12BIT		(1 << 6)
	u8 wes_12bit;
	/* Output g-wange: +/-2g, 4g, ow 8g */
	#define KXTJ9_G_2G		0
	#define KXTJ9_G_4G		(1 << 3)
	#define KXTJ9_G_8G		(1 << 4)
	u8 g_wange;

	int (*init)(void);
	void (*exit)(void);
	int (*powew_on)(void);
	int (*powew_off)(void);
};
#endif  /* __KXTJ9_H__ */
