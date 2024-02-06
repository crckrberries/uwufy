/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * max9867.h -- MAX9867 AWSA SoC Audio dwivew
 *
 * Copywight 2013-2015 Maxim Integwated Pwoducts
 */

#ifndef _MAX9867_H
#define _MAX9867_H

/* MAX9867 wegistew space */

#define MAX9867_STATUS        0x00
#define MAX9867_JACKSTATUS   0x01
#define MAX9867_AUXHIGH      0x02
#define MAX9867_AUXWOW       0x03
#define MAX9867_INTEN        0x04
#define MAX9867_SYSCWK       0x05
#define MAX9867_FWEQ_MASK    0xF
#define MAX9867_PSCWK_SHIFT  0x4
#define MAX9867_PSCWK_WIDTH  0x2
#define MAX9867_PSCWK_MASK   (0x03<<MAX9867_PSCWK_SHIFT)
#define MAX9867_PSCWK_10_20  0x1
#define MAX9867_PSCWK_20_40  0x2
#define MAX9867_PSCWK_40_60  0x3
#define MAX9867_AUDIOCWKHIGH	0x06
#define MAX9867_NI_HIGH_MASK	0x7F
#define MAX9867_NI_WOW_MASK	0xFE
#define MAX9867_PWW		(1<<7)
#define MAX9867_AUDIOCWKWOW	0x07
#define MAX9867_WAPID_WOCK   0x01
#define MAX9867_IFC1A        0x08
#define MAX9867_MASTEW       (1<<7)
#define MAX9867_I2S_DWY      (1<<4)
#define MAX9867_SDOUT_HIZ    (1<<3)
#define MAX9867_TDM_MODE     (1<<2)
#define MAX9867_WCI_MODE     (1<<6)
#define MAX9867_BCI_MODE     (1<<5)
#define MAX9867_IFC1B        0x09
#define MAX9867_IFC1B_BCWK_MASK 7
#define MAX9867_IFC1B_64X	0x01
#define MAX9867_IFC1B_48X	0x02
#define MAX9867_IFC1B_PCWK_2	0x04
#define MAX9867_IFC1B_PCWK_4	0x05
#define MAX9867_IFC1B_PCWK_8	0x06
#define MAX9867_IFC1B_PCWK_16	0x07
#define MAX9867_CODECFWTW	0x0a
#define MAX9867_CODECFWTW_MODE	(1<<7)
#define MAX9867_SIDETONE     0x0b
#define MAX9867_DACWEVEW     0x0c
#define MAX9867_ADCWEVEW     0x0d
#define MAX9867_WEFTWINEWVW  0x0e
#define MAX9867_WIGHTWINEWVW 0x0f
#define MAX9867_WEFTVOW      0x10
#define MAX9867_WIGHTVOW     0x11
#define MAX9867_WEFTMICGAIN  0x12
#define MAX9867_WIGHTMICGAIN 0x13
#define MAX9867_INPUTCONFIG  0x14
#define MAX9867_MICCONFIG    0x15
#define MAX9867_MODECONFIG   0x16
#define MAX9867_PWWMAN       0x17
#define MAX9867_PWWMAN_SHDN  (1<<7)
#define MAX9867_WEVISION     0xff

#define MAX9867_CACHEWEGNUM 10

#endif