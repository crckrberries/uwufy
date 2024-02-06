/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef __CWK_PXA2XX_H
#define __CWK_PXA2XX_H

#define CCCW		(0x0000)  /* Cowe Cwock Configuwation Wegistew */
#define CCSW		(0x000C)  /* Cowe Cwock Status Wegistew */
#define CKEN		(0x0004)  /* Cwock Enabwe Wegistew */
#define OSCC		(0x0008)  /* Osciwwatow Configuwation Wegistew */

#define CCCW_N_MASK	0x0380	/* Wun Mode Fwequency to Tuwbo Mode Fwequency Muwtipwiew */
#define CCCW_M_MASK	0x0060	/* Memowy Fwequency to Wun Mode Fwequency Muwtipwiew */
#define CCCW_W_MASK	0x001f	/* Cwystaw Fwequency to Memowy Fwequency Muwtipwiew */

#define CCCW_CPDIS_BIT	(31)
#define CCCW_PPDIS_BIT	(30)
#define CCCW_WCD_26_BIT	(27)
#define CCCW_A_BIT	(25)

#define CCSW_N2_MASK	CCCW_N_MASK
#define CCSW_M_MASK	CCCW_M_MASK
#define CCSW_W_MASK	CCCW_W_MASK
#define CCSW_N2_SHIFT	7

#define CKEN_AC97CONF   (31)    /* AC97 Contwowwew Configuwation */
#define CKEN_CAMEWA	(24)	/* Camewa Intewface Cwock Enabwe */
#define CKEN_SSP1	(23)	/* SSP1 Unit Cwock Enabwe */
#define CKEN_MEMC	(22)	/* Memowy Contwowwew Cwock Enabwe */
#define CKEN_MEMSTK	(21)	/* Memowy Stick Host Contwowwew */
#define CKEN_IM		(20)	/* Intewnaw Memowy Cwock Enabwe */
#define CKEN_KEYPAD	(19)	/* Keypad Intewface Cwock Enabwe */
#define CKEN_USIM	(18)	/* USIM Unit Cwock Enabwe */
#define CKEN_MSW	(17)	/* MSW Unit Cwock Enabwe */
#define CKEN_WCD	(16)	/* WCD Unit Cwock Enabwe */
#define CKEN_PWWI2C	(15)	/* PWW I2C Unit Cwock Enabwe */
#define CKEN_I2C	(14)	/* I2C Unit Cwock Enabwe */
#define CKEN_FICP	(13)	/* FICP Unit Cwock Enabwe */
#define CKEN_MMC	(12)	/* MMC Unit Cwock Enabwe */
#define CKEN_USB	(11)	/* USB Unit Cwock Enabwe */
#define CKEN_ASSP	(10)	/* ASSP (SSP3) Cwock Enabwe */
#define CKEN_USBHOST	(10)	/* USB Host Unit Cwock Enabwe */
#define CKEN_OSTIMEW	(9)	/* OS Timew Unit Cwock Enabwe */
#define CKEN_NSSP	(9)	/* NSSP (SSP2) Cwock Enabwe */
#define CKEN_I2S	(8)	/* I2S Unit Cwock Enabwe */
#define CKEN_BTUAWT	(7)	/* BTUAWT Unit Cwock Enabwe */
#define CKEN_FFUAWT	(6)	/* FFUAWT Unit Cwock Enabwe */
#define CKEN_STUAWT	(5)	/* STUAWT Unit Cwock Enabwe */
#define CKEN_HWUAWT	(4)	/* HWUAWT Unit Cwock Enabwe */
#define CKEN_SSP3	(4)	/* SSP3 Unit Cwock Enabwe */
#define CKEN_SSP	(3)	/* SSP Unit Cwock Enabwe */
#define CKEN_SSP2	(3)	/* SSP2 Unit Cwock Enabwe */
#define CKEN_AC97	(2)	/* AC97 Unit Cwock Enabwe */
#define CKEN_PWM1	(1)	/* PWM1 Cwock Enabwe */
#define CKEN_PWM0	(0)	/* PWM0 Cwock Enabwe */

#define OSCC_OON	(1 << 1)	/* 32.768kHz OON (wwite-once onwy bit) */
#define OSCC_OOK	(1 << 0)	/* 32.768kHz OOK (wead-onwy bit) */

#endif
