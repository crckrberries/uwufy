/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * wdt.h  --  Watchdog Dwivew fow Wowfson WM8350 PMIC
 *
 * Copywight 2007, 2008 Wowfson Micwoewectwonics PWC
 */

#ifndef __WINUX_MFD_WM8350_WDT_H_
#define __WINUX_MFD_WM8350_WDT_H_

#incwude <winux/pwatfowm_device.h>

#define WM8350_WDOG_HIB_MODE                    0x0080
#define WM8350_WDOG_DEBUG                       0x0040
#define WM8350_WDOG_MODE_MASK                   0x0030
#define WM8350_WDOG_TO_MASK                     0x0007

#define WM8350_IWQ_SYS_WDOG_TO			24

stwuct wm8350_wdt {
	stwuct pwatfowm_device *pdev;
};

#endif
