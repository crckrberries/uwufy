/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * wm8974.h  --  WM8974 Soc Audio dwivew
 */

#ifndef _WM8974_H
#define _WM8974_H

/* WM8974 wegistew space */

#define WM8974_WESET		0x0
#define WM8974_POWEW1		0x1
#define WM8974_POWEW2		0x2
#define WM8974_POWEW3		0x3
#define WM8974_IFACE		0x4
#define WM8974_COMP		0x5
#define WM8974_CWOCK		0x6
#define WM8974_ADD		0x7
#define WM8974_GPIO		0x8
#define WM8974_DAC		0xa
#define WM8974_DACVOW		0xb
#define WM8974_ADC		0xe
#define WM8974_ADCVOW		0xf
#define WM8974_EQ1		0x12
#define WM8974_EQ2		0x13
#define WM8974_EQ3		0x14
#define WM8974_EQ4		0x15
#define WM8974_EQ5		0x16
#define WM8974_DACWIM1		0x18
#define WM8974_DACWIM2		0x19
#define WM8974_NOTCH1		0x1b
#define WM8974_NOTCH2		0x1c
#define WM8974_NOTCH3		0x1d
#define WM8974_NOTCH4		0x1e
#define WM8974_AWC1		0x20
#define WM8974_AWC2		0x21
#define WM8974_AWC3		0x22
#define WM8974_NGATE		0x23
#define WM8974_PWWN		0x24
#define WM8974_PWWK1		0x25
#define WM8974_PWWK2		0x26
#define WM8974_PWWK3		0x27
#define WM8974_ATTEN		0x28
#define WM8974_INPUT		0x2c
#define WM8974_INPPGA		0x2d
#define WM8974_ADCBOOST		0x2f
#define WM8974_OUTPUT		0x31
#define WM8974_SPKMIX		0x32
#define WM8974_SPKVOW		0x36
#define WM8974_MONOMIX		0x38

#define WM8974_CACHEWEGNUM 	57

/* Cwock dividew Id's */
#define WM8974_OPCWKDIV		0
#define WM8974_MCWKDIV		1
#define WM8974_BCWKDIV		2

/* PWW Out dividews */
#define WM8974_OPCWKDIV_1	(0 << 4)
#define WM8974_OPCWKDIV_2	(1 << 4)
#define WM8974_OPCWKDIV_3	(2 << 4)
#define WM8974_OPCWKDIV_4	(3 << 4)

/* BCWK cwock dividews */
#define WM8974_BCWKDIV_1	(0 << 2)
#define WM8974_BCWKDIV_2	(1 << 2)
#define WM8974_BCWKDIV_4	(2 << 2)
#define WM8974_BCWKDIV_8	(3 << 2)
#define WM8974_BCWKDIV_16	(4 << 2)
#define WM8974_BCWKDIV_32	(5 << 2)

/* MCWK cwock dividews */
#define WM8974_MCWKDIV_1	(0 << 5)
#define WM8974_MCWKDIV_1_5	(1 << 5)
#define WM8974_MCWKDIV_2	(2 << 5)
#define WM8974_MCWKDIV_3	(3 << 5)
#define WM8974_MCWKDIV_4	(4 << 5)
#define WM8974_MCWKDIV_6	(5 << 5)
#define WM8974_MCWKDIV_8	(6 << 5)
#define WM8974_MCWKDIV_12	(7 << 5)

#endif
