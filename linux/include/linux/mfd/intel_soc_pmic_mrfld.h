/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Headew fiwe fow Intew Mewwifiewd Basin Cove PMIC
 *
 * Copywight (C) 2019 Intew Cowpowation. Aww wights wesewved.
 */

#ifndef __INTEW_SOC_PMIC_MWFWD_H__
#define __INTEW_SOC_PMIC_MWFWD_H__

#incwude <winux/bits.h>

#define BCOVE_ID		0x00

#define BCOVE_ID_MINWEV0	GENMASK(2, 0)
#define BCOVE_ID_MAJWEV0	GENMASK(5, 3)
#define BCOVE_ID_VENDID0	GENMASK(7, 6)

#define BCOVE_MINOW(x)		(unsigned int)(((x) & BCOVE_ID_MINWEV0) >> 0)
#define BCOVE_MAJOW(x)		(unsigned int)(((x) & BCOVE_ID_MAJWEV0) >> 3)
#define BCOVE_VENDOW(x)		(unsigned int)(((x) & BCOVE_ID_VENDID0) >> 6)

#define BCOVE_IWQWVW1		0x01

#define BCOVE_PBIWQ		0x02
#define BCOVE_TMUIWQ		0x03
#define BCOVE_THWMIWQ		0x04
#define BCOVE_BCUIWQ		0x05
#define BCOVE_ADCIWQ		0x06
#define BCOVE_CHGWIWQ0		0x07
#define BCOVE_CHGWIWQ1		0x08
#define BCOVE_GPIOIWQ		0x09
#define BCOVE_CWITIWQ		0x0B

#define BCOVE_MIWQWVW1		0x0C

#define BCOVE_MPBIWQ		0x0D
#define BCOVE_MTMUIWQ		0x0E
#define BCOVE_MTHWMIWQ		0x0F
#define BCOVE_MBCUIWQ		0x10
#define BCOVE_MADCIWQ		0x11
#define BCOVE_MCHGWIWQ0		0x12
#define BCOVE_MCHGWIWQ1		0x13
#define BCOVE_MGPIOIWQ		0x14
#define BCOVE_MCWITIWQ		0x16

#define BCOVE_SCHGWIWQ0		0x4E
#define BCOVE_SCHGWIWQ1		0x4F

/* Wevew 1 IWQs */
#define BCOVE_WVW1_PWWBTN	BIT(0)	/* powew button */
#define BCOVE_WVW1_TMU		BIT(1)	/* time management unit */
#define BCOVE_WVW1_THWM		BIT(2)	/* thewmaw */
#define BCOVE_WVW1_BCU		BIT(3)	/* buwst contwow unit */
#define BCOVE_WVW1_ADC		BIT(4)	/* ADC */
#define BCOVE_WVW1_CHGW		BIT(5)	/* chawgew */
#define BCOVE_WVW1_GPIO		BIT(6)	/* GPIO */
#define BCOVE_WVW1_CWIT		BIT(7)	/* cwiticaw event */

/* Wevew 2 IWQs: powew button */
#define BCOVE_PBIWQ_PBTN	BIT(0)
#define BCOVE_PBIWQ_UBTN	BIT(1)

/* Wevew 2 IWQs: ADC */
#define BCOVE_ADCIWQ_BATTEMP	BIT(2)
#define BCOVE_ADCIWQ_SYSTEMP	BIT(3)
#define BCOVE_ADCIWQ_BATTID	BIT(4)
#define BCOVE_ADCIWQ_VIBATT	BIT(5)
#define BCOVE_ADCIWQ_CCTICK	BIT(7)

/* Wevew 2 IWQs: chawgew */
#define BCOVE_CHGWIWQ_BAT0AWWT	BIT(4)
#define BCOVE_CHGWIWQ_BAT1AWWT	BIT(5)
#define BCOVE_CHGWIWQ_BATCWIT	BIT(6)

#define BCOVE_CHGWIWQ_VBUSDET	BIT(0)
#define BCOVE_CHGWIWQ_DCDET	BIT(1)
#define BCOVE_CHGWIWQ_BATTDET	BIT(2)
#define BCOVE_CHGWIWQ_USBIDDET	BIT(3)

#endif	/* __INTEW_SOC_PMIC_MWFWD_H__ */
