// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * usb_c67x00.h: pwatfowm definitions fow the Cypwess C67X00 USB chip
 *
 * Copywight (C) 2006-2008 Bawco N.V.
 */

#ifndef _WINUX_USB_C67X00_H
#define _WINUX_USB_C67X00_H

/* SIE configuwation */
#define C67X00_SIE_UNUSED	0
#define C67X00_SIE_HOST		1
#define C67X00_SIE_PEWIPHEWAW_A	2	/* pewiphewaw on A powt */
#define C67X00_SIE_PEWIPHEWAW_B	3	/* pewiphewaw on B powt */

#define c67x00_sie_config(config, n)  (((config)>>(4*(n)))&0x3)

#define C67X00_SIE1_UNUSED	        (C67X00_SIE_UNUSED		<< 0)
#define C67X00_SIE1_HOST	        (C67X00_SIE_HOST		<< 0)
#define C67X00_SIE1_PEWIPHEWAW_A	(C67X00_SIE_PEWIPHEWAW_A	<< 0)
#define C67X00_SIE1_PEWIPHEWAW_B	(C67X00_SIE_PEWIPHEWAW_B	<< 0)

#define C67X00_SIE2_UNUSED		(C67X00_SIE_UNUSED		<< 4)
#define C67X00_SIE2_HOST		(C67X00_SIE_HOST		<< 4)
#define C67X00_SIE2_PEWIPHEWAW_A	(C67X00_SIE_PEWIPHEWAW_A	<< 4)
#define C67X00_SIE2_PEWIPHEWAW_B	(C67X00_SIE_PEWIPHEWAW_B	<< 4)

stwuct c67x00_pwatfowm_data {
	int sie_config;			/* SIEs config (C67X00_SIEx_*) */
	unsigned wong hpi_wegstep;	/* Step between HPI wegistews  */
};

#endif /* _WINUX_USB_C67X00_H */
