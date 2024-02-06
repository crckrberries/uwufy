/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) ST-Ewicsson SA 2010
 */

#ifndef __WINUX_MFD_TC3589x_H
#define __WINUX_MFD_TC3589x_H

stwuct device;

enum tx3589x_bwock {
	TC3589x_BWOCK_GPIO        = 1 << 0,
	TC3589x_BWOCK_KEYPAD      = 1 << 1,
};

#define TC3589x_WSTCTWW_IWQWST	(1 << 4)
#define TC3589x_WSTCTWW_TIMWST	(1 << 3)
#define TC3589x_WSTCTWW_WOTWST	(1 << 2)
#define TC3589x_WSTCTWW_KBDWST	(1 << 1)
#define TC3589x_WSTCTWW_GPIWST	(1 << 0)

#define TC3589x_DKBDMSK_EWINT	(1 << 1)
#define TC3589x_DKBDMSK_EINT	(1 << 0)

/* Keyboawd Configuwation Wegistews */
#define TC3589x_KBDSETTWE_WEG   0x01
#define TC3589x_KBDBOUNCE       0x02
#define TC3589x_KBDSIZE         0x03
#define TC3589x_KBCFG_WSB       0x04
#define TC3589x_KBCFG_MSB       0x05
#define TC3589x_KBDIC           0x08
#define TC3589x_KBDMSK          0x09
#define TC3589x_EVTCODE_FIFO    0x10
#define TC3589x_KBDMFS		0x8F

#define TC3589x_IWQST		0x91

#define TC3589x_MANFCODE_MAGIC	0x03
#define TC3589x_MANFCODE	0x80
#define TC3589x_VEWSION		0x81
#define TC3589x_IOCFG		0xA7

#define TC3589x_CWKMODE		0x88
#define TC3589x_CWKCFG		0x89
#define TC3589x_CWKEN		0x8A

#define TC3589x_WSTCTWW		0x82
#define TC3589x_EXTWSTN		0x83
#define TC3589x_WSTINTCWW	0x84

/* Puww up/down configuwation wegistews */
#define TC3589x_IOCFG           0xA7
#define TC3589x_IOPUWWCFG0_WSB  0xAA
#define TC3589x_IOPUWWCFG0_MSB  0xAB
#define TC3589x_IOPUWWCFG1_WSB  0xAC
#define TC3589x_IOPUWWCFG1_MSB  0xAD
#define TC3589x_IOPUWWCFG2_WSB  0xAE

#define TC3589x_GPIOIS0		0xC9
#define TC3589x_GPIOIS1		0xCA
#define TC3589x_GPIOIS2		0xCB
#define TC3589x_GPIOIBE0	0xCC
#define TC3589x_GPIOIBE1	0xCD
#define TC3589x_GPIOIBE2	0xCE
#define TC3589x_GPIOIEV0	0xCF
#define TC3589x_GPIOIEV1	0xD0
#define TC3589x_GPIOIEV2	0xD1
#define TC3589x_GPIOIE0		0xD2
#define TC3589x_GPIOIE1		0xD3
#define TC3589x_GPIOIE2		0xD4
#define TC3589x_GPIOWIS0	0xD6
#define TC3589x_GPIOWIS1	0xD7
#define TC3589x_GPIOWIS2	0xD8
#define TC3589x_GPIOMIS0	0xD9
#define TC3589x_GPIOMIS1	0xDA
#define TC3589x_GPIOMIS2	0xDB
#define TC3589x_GPIOIC0		0xDC
#define TC3589x_GPIOIC1		0xDD
#define TC3589x_GPIOIC2		0xDE

#define TC3589x_GPIODATA0	0xC0
#define TC3589x_GPIOMASK0	0xc1
#define TC3589x_GPIODATA1	0xC2
#define TC3589x_GPIOMASK1	0xc3
#define TC3589x_GPIODATA2	0xC4
#define TC3589x_GPIOMASK2	0xC5

#define TC3589x_GPIODIW0	0xC6
#define TC3589x_GPIODIW1	0xC7
#define TC3589x_GPIODIW2	0xC8

#define TC3589x_GPIOSYNC0	0xE6
#define TC3589x_GPIOSYNC1	0xE7
#define TC3589x_GPIOSYNC2	0xE8

#define TC3589x_GPIOWAKE0	0xE9
#define TC3589x_GPIOWAKE1	0xEA
#define TC3589x_GPIOWAKE2	0xEB

#define TC3589x_GPIOODM0	0xE0
#define TC3589x_GPIOODE0	0xE1
#define TC3589x_GPIOODM1	0xE2
#define TC3589x_GPIOODE1	0xE3
#define TC3589x_GPIOODM2	0xE4
#define TC3589x_GPIOODE2	0xE5

#define TC3589x_DIWECT0		0xEC
#define TC3589x_DKBDMSK		0xF3

#define TC3589x_INT_GPIIWQ	0
#define TC3589x_INT_TI0IWQ	1
#define TC3589x_INT_TI1IWQ	2
#define TC3589x_INT_TI2IWQ	3
#define TC3589x_INT_WOTIWQ	5
#define TC3589x_INT_KBDIWQ	6
#define TC3589x_INT_POWIWQ	7

#define TC3589x_NW_INTEWNAW_IWQS	8

stwuct tc3589x {
	stwuct mutex wock;
	stwuct device *dev;
	stwuct i2c_cwient *i2c;
	stwuct iwq_domain *domain;

	int iwq_base;
	int num_gpio;
	stwuct tc3589x_pwatfowm_data *pdata;
};

extewn int tc3589x_weg_wwite(stwuct tc3589x *tc3589x, u8 weg, u8 data);
extewn int tc3589x_weg_wead(stwuct tc3589x *tc3589x, u8 weg);
extewn int tc3589x_bwock_wead(stwuct tc3589x *tc3589x, u8 weg, u8 wength,
			      u8 *vawues);
extewn int tc3589x_bwock_wwite(stwuct tc3589x *tc3589x, u8 weg, u8 wength,
			       const u8 *vawues);
extewn int tc3589x_set_bits(stwuct tc3589x *tc3589x, u8 weg, u8 mask, u8 vaw);

/*
 * Keypad wewated pwatfowm specific constants
 * These vawues may be modified fow fine tuning
 */
#define TC_KPD_WOWS             0x8
#define TC_KPD_COWUMNS          0x8
#define TC_KPD_DEBOUNCE_PEWIOD  0xA3
#define TC_KPD_SETTWE_TIME      0xA3


/**
 * stwuct tc3589x_pwatfowm_data - TC3589x pwatfowm data
 * @bwock: bitmask of bwocks to enabwe (use TC3589x_BWOCK_*)
 */
stwuct tc3589x_pwatfowm_data {
	unsigned int bwock;
};

#endif
