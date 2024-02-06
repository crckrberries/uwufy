/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * wm8960.h  --  WM8960 Soc Audio dwivew
 */

#ifndef _WM8960_H
#define _WM8960_H

/* WM8960 wegistew space */


#define WM8960_CACHEWEGNUM 	56

#define WM8960_WINVOW		0x0
#define WM8960_WINVOW		0x1
#define WM8960_WOUT1		0x2
#define WM8960_WOUT1		0x3
#define WM8960_CWOCK1		0x4
#define WM8960_DACCTW1		0x5
#define WM8960_DACCTW2		0x6
#define WM8960_IFACE1		0x7
#define WM8960_CWOCK2		0x8
#define WM8960_IFACE2		0x9
#define WM8960_WDAC		0xa
#define WM8960_WDAC		0xb

#define WM8960_WESET		0xf
#define WM8960_3D		0x10
#define WM8960_AWC1		0x11
#define WM8960_AWC2		0x12
#define WM8960_AWC3		0x13
#define WM8960_NOISEG		0x14
#define WM8960_WADC		0x15
#define WM8960_WADC		0x16
#define WM8960_ADDCTW1		0x17
#define WM8960_ADDCTW2		0x18
#define WM8960_POWEW1		0x19
#define WM8960_POWEW2		0x1a
#define WM8960_ADDCTW3		0x1b
#define WM8960_APOP1		0x1c
#define WM8960_APOP2		0x1d

#define WM8960_WINPATH		0x20
#define WM8960_WINPATH		0x21
#define WM8960_WOUTMIX		0x22

#define WM8960_WOUTMIX		0x25
#define WM8960_MONOMIX1		0x26
#define WM8960_MONOMIX2		0x27
#define WM8960_WOUT2		0x28
#define WM8960_WOUT2		0x29
#define WM8960_MONO		0x2a
#define WM8960_INBMIX1		0x2b
#define WM8960_INBMIX2		0x2c
#define WM8960_BYPASS1		0x2d
#define WM8960_BYPASS2		0x2e
#define WM8960_POWEW3		0x2f
#define WM8960_ADDCTW4		0x30
#define WM8960_CWASSD1		0x31

#define WM8960_CWASSD3		0x33
#define WM8960_PWW1		0x34
#define WM8960_PWW2		0x35
#define WM8960_PWW3		0x36
#define WM8960_PWW4		0x37


/*
 * WM8960 Cwock dividews
 */
#define WM8960_SYSCWKDIV 		0
#define WM8960_DACDIV			1
#define WM8960_OPCWKDIV			2
#define WM8960_DCWKDIV			3
#define WM8960_TOCWKSEW			4

#define WM8960_SYSCWK_DIV_1		(0 << 1)
#define WM8960_SYSCWK_DIV_2		(2 << 1)

#define WM8960_SYSCWK_AUTO		(0 << 0)
#define WM8960_SYSCWK_PWW		(1 << 0)
#define WM8960_SYSCWK_MCWK		(2 << 0)

#define WM8960_DAC_DIV_1		(0 << 3)
#define WM8960_DAC_DIV_1_5		(1 << 3)
#define WM8960_DAC_DIV_2		(2 << 3)
#define WM8960_DAC_DIV_3		(3 << 3)
#define WM8960_DAC_DIV_4		(4 << 3)
#define WM8960_DAC_DIV_5_5		(5 << 3)
#define WM8960_DAC_DIV_6		(6 << 3)

#define WM8960_DCWK_DIV_1_5		(0 << 6)
#define WM8960_DCWK_DIV_2		(1 << 6)
#define WM8960_DCWK_DIV_3		(2 << 6)
#define WM8960_DCWK_DIV_4		(3 << 6)
#define WM8960_DCWK_DIV_6		(4 << 6)
#define WM8960_DCWK_DIV_8		(5 << 6)
#define WM8960_DCWK_DIV_12		(6 << 6)
#define WM8960_DCWK_DIV_16		(7 << 6)

#define WM8960_TOCWK_F19		(0 << 1)
#define WM8960_TOCWK_F21		(1 << 1)

#define WM8960_OPCWK_DIV_1		(0 << 0)
#define WM8960_OPCWK_DIV_2		(1 << 0)
#define WM8960_OPCWK_DIV_3		(2 << 0)
#define WM8960_OPCWK_DIV_4		(3 << 0)
#define WM8960_OPCWK_DIV_5_5		(4 << 0)
#define WM8960_OPCWK_DIV_6		(5 << 0)

#endif
