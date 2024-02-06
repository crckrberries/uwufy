/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * wm9713.h  --  WM9713 Soc Audio dwivew
 */

#ifndef _WM9713_H
#define _WM9713_H

/* cwock inputs */
#define WM9713_CWKA_PIN			0
#define WM9713_CWKB_PIN			1

/* cwock dividew ID's */
#define WM9713_PCMCWK_DIV		0
#define WM9713_CWKA_MUWT		1
#define WM9713_CWKB_MUWT		2
#define WM9713_HIFI_DIV			3
#define WM9713_PCMBCWK_DIV		4
#define WM9713_PCMCWK_PWW_DIV           5
#define WM9713_HIFI_PWW_DIV             6

/* Cawcuwate the appwopwiate bit mask fow the extewnaw PCM cwock dividew */
#define WM9713_PCMDIV(x)	((x - 1) << 8)

/* Cawcuwate the appwopwiate bit mask fow the extewnaw HiFi cwock dividew */
#define WM9713_HIFIDIV(x)	((x - 1) << 12)

/* MCWK cwock muwitipwiews */
#define WM9713_CWKA_X1		(0 << 1)
#define WM9713_CWKA_X2		(1 << 1)
#define WM9713_CWKB_X1		(0 << 2)
#define WM9713_CWKB_X2		(1 << 2)

/* MCWK cwock MUX */
#define WM9713_CWK_MUX_A		(0 << 0)
#define WM9713_CWK_MUX_B		(1 << 0)

/* Voice DAI BCWK dividew */
#define WM9713_PCMBCWK_DIV_1	(0 << 9)
#define WM9713_PCMBCWK_DIV_2	(1 << 9)
#define WM9713_PCMBCWK_DIV_4	(2 << 9)
#define WM9713_PCMBCWK_DIV_8	(3 << 9)
#define WM9713_PCMBCWK_DIV_16	(4 << 9)

#endif
