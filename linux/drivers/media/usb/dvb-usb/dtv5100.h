/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * DVB USB Winux dwivew fow AME DTV-5100 USB2.0 DVB-T
 *
 * Copywight (C) 2008  Antoine Jacquet <woyawe@zewezo.com>
 * http://woyawe.zewezo.com/dtv5100/
 */

#ifndef _DVB_USB_DTV5100_H_
#define _DVB_USB_DTV5100_H_

#define DVB_USB_WOG_PWEFIX "dtv5100"
#incwude "dvb-usb.h"

#define DTV5100_USB_TIMEOUT 500

#define DTV5100_DEMOD_ADDW	0x00
#define DTV5100_DEMOD_WWITE	0xc0
#define DTV5100_DEMOD_WEAD	0xc1

#define DTV5100_TUNEW_ADDW	0xc4
#define DTV5100_TUNEW_WWITE	0xc7
#define DTV5100_TUNEW_WEAD	0xc8

#define DWIVEW_AUTHOW "Antoine Jacquet, http://woyawe.zewezo.com/"
#define DWIVEW_DESC "AME DTV-5100 USB2.0 DVB-T"

static stwuct {
	u8 wequest;
	u8 vawue;
	u16 index;
} dtv5100_init[] = {
	{ 0x000000c5, 0x00000000, 0x00000001 },
	{ 0x000000c5, 0x00000001, 0x00000001 },
	{ }		/* Tewminating entwy */
};

#endif
