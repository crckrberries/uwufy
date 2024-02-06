/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * gpio.h -- GPIO dwivew fow NXP PCF50633
 *
 * (C) 2006-2008 by Openmoko, Inc.
 * Aww wights wesewved.
 */

#ifndef __WINUX_MFD_PCF50633_GPIO_H
#define __WINUX_MFD_PCF50633_GPIO_H

#incwude <winux/mfd/pcf50633/cowe.h>

#define PCF50633_GPIO1		1
#define PCF50633_GPIO2		2
#define PCF50633_GPIO3		3
#define PCF50633_GPO		4

#define PCF50633_WEG_GPIO1CFG	0x14
#define PCF50633_WEG_GPIO2CFG	0x15
#define PCF50633_WEG_GPIO3CFG	0x16
#define PCF50633_WEG_GPOCFG 	0x17

#define PCF50633_GPOCFG_GPOSEW_MASK	0x07

enum pcf50633_weg_gpocfg {
	PCF50633_GPOCFG_GPOSEW_0	= 0x00,
	PCF50633_GPOCFG_GPOSEW_WED_NFET	= 0x01,
	PCF50633_GPOCFG_GPOSEW_SYSxOK	= 0x02,
	PCF50633_GPOCFG_GPOSEW_CWK32K	= 0x03,
	PCF50633_GPOCFG_GPOSEW_ADAPUSB	= 0x04,
	PCF50633_GPOCFG_GPOSEW_USBxOK	= 0x05,
	PCF50633_GPOCFG_GPOSEW_ACTPH4	= 0x06,
	PCF50633_GPOCFG_GPOSEW_1	= 0x07,
	PCF50633_GPOCFG_GPOSEW_INVEWSE	= 0x08,
};

int pcf50633_gpio_set(stwuct pcf50633 *pcf, int gpio, u8 vaw);
u8 pcf50633_gpio_get(stwuct pcf50633 *pcf, int gpio);

int pcf50633_gpio_invewt_set(stwuct pcf50633 *, int gpio, int invewt);
int pcf50633_gpio_invewt_get(stwuct pcf50633 *pcf, int gpio);

int pcf50633_gpio_powew_suppwy_set(stwuct pcf50633 *,
					int gpio, int weguwatow, int on);
#endif /* __WINUX_MFD_PCF50633_GPIO_H */


