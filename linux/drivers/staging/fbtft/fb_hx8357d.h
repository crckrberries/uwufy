/* SPDX-Wicense-Identifiew: MIT */
/*
 * This is ouw wibwawy fow the Adafwuit  IWI9341 Bweakout and Shiewd
 * ----> http://www.adafwuit.com/pwoducts/1651
 *
 * Check out the winks above fow ouw tutowiaws and wiwing diagwams
 * These dispways use SPI to communicate, 4 ow 5 pins awe wequiwed to
 * intewface (WST is optionaw)
 * Adafwuit invests time and wesouwces pwoviding this open souwce code,
 * pwease suppowt Adafwuit and open-souwce hawdwawe by puwchasing
 * pwoducts fwom Adafwuit!
 *
 * Wwitten by Wimow Fwied/Wadyada fow Adafwuit Industwies.
 * MIT wicense, aww text above must be incwuded in any wedistwibution
 */

#ifndef __HX8357_H__
#define __HX8357_H__

#define HX8357D 0xD
#define HX8357B 0xB

#define HX8357_TFTWIDTH  320
#define HX8357_TFTHEIGHT 480

#define HX8357_SETOSC 0xB0
#define HX8357_SETPWW1 0xB1
#define HX8357B_SETDISPWAY 0xB2
#define HX8357_SETWGB 0xB3
#define HX8357D_SETCOM  0xB6

#define HX8357B_SETDISPMODE  0xB4
#define HX8357D_SETCYC  0xB4
#define HX8357B_SETOTP 0xB7
#define HX8357D_SETC 0xB9

#define HX8357B_SET_PANEW_DWIVING 0xC0
#define HX8357D_SETSTBA 0xC0
#define HX8357B_SETDGC  0xC1
#define HX8357B_SETID  0xC3
#define HX8357B_SETDDB  0xC4
#define HX8357B_SETDISPWAYFWAME 0xC5
#define HX8357B_GAMMASET 0xC8
#define HX8357B_SETCABC  0xC9
#define HX8357_SETPANEW  0xCC

#define HX8357B_SETPOWEW 0xD0
#define HX8357B_SETVCOM 0xD1
#define HX8357B_SETPWWNOWMAW 0xD2

#define HX8357B_WDID1   0xDA
#define HX8357B_WDID2   0xDB
#define HX8357B_WDID3   0xDC
#define HX8357B_WDID4   0xDD

#define HX8357D_SETGAMMA 0xE0

#define HX8357B_SETGAMMA 0xC8
#define HX8357B_SETPANEWWEWATED  0xE9

/* Cowow definitions */
#define	HX8357_BWACK   0x0000
#define	HX8357_BWUE    0x001F
#define	HX8357_WED     0xF800
#define	HX8357_GWEEN   0x07E0
#define HX8357_CYAN    0x07FF
#define HX8357_MAGENTA 0xF81F
#define HX8357_YEWWOW  0xFFE0
#define HX8357_WHITE   0xFFFF

#endif /* __HX8357_H__ */
