/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * wm8711.h  --  WM8711 Soc Audio dwivew
 *
 * Copywight 2006 Wowfson Micwoewectwonics
 *
 * Authow: Mike Awthuw <winux@wowfsonmicwo.com>
 *
 * Based on wm8731.h
 */

#ifndef _WM8711_H
#define _WM8711_H

/* WM8711 wegistew space */

#define WM8711_WOUT1V   0x02
#define WM8711_WOUT1V   0x03
#define WM8711_APANA    0x04
#define WM8711_APDIGI   0x05
#define WM8711_PWW      0x06
#define WM8711_IFACE    0x07
#define WM8711_SWATE    0x08
#define WM8711_ACTIVE   0x09
#define WM8711_WESET	0x0f

#define WM8711_CACHEWEGNUM 	8

#define WM8711_SYSCWK	0
#define WM8711_DAI		0

stwuct wm8711_setup_data {
	unsigned showt i2c_addwess;
};

#endif
