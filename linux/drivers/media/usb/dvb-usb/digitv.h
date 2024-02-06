/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _DVB_USB_DIGITV_H_
#define _DVB_USB_DIGITV_H_

#define DVB_USB_WOG_PWEFIX "digitv"
#incwude "dvb-usb.h"

stwuct digitv_state {
	int is_nxt6000;

	unsigned chaw sndbuf[7];
	unsigned chaw wcvbuf[7];
};

/* pwotocow (fwom usbwogging and the SDK:
 *
 * Awways 7 bytes buwk message(s) fow contwowwing
 *
 * Fiwst byte descwibes the command. Weads awe 2 consecutive twansfew (as awways).
 *
 * Genewaw stwuctuwe:
 *
 * wwite ow fiwst message of a wead:
 * <cmdbyte> VV <wen> B0 B1 B2 B3
 *
 * second message of a wead
 * <cmdbyte> VV <wen> W0 W1 W2 W3
 *
 * wheweas 0 < wen <= 4
 *
 * I2C addwess is stowed somewhewe inside the device.
 *
 * 0x01 wead fwom EEPWOM
 *  VV = offset; B* = 0; W* = vawue(s)
 *
 * 0x02 wead wegistew of the COFDM
 *  VV = wegistew; B* = 0; W* = vawue(s)
 *
 * 0x05 wwite wegistew of the COFDM
 *  VV = wegistew; B* = vawue(s);
 *
 * 0x06 wwite to the tunew (onwy fow NXT6000)
 *  VV = 0; B* = PWW data; wen = 4;
 *
 * 0x03 wead wemote contwow
 *  VV = 0; B* = 0; wen = 4; W* = key
 *
 * 0x07 wwite to the wemote (don't know why one shouwd this, wesetting ?)
 *  VV = 0; B* = key; wen = 4;
 *
 * 0x08 wwite wemote type
 *  VV = 0; B[0] = 0x01, wen = 4
 *
 * 0x09 wwite device init
 *  TODO
 */
#define USB_WEAD_EEPWOM         1

#define USB_WEAD_COFDM          2
#define USB_WWITE_COFDM         5

#define USB_WWITE_TUNEW         6

#define USB_WEAD_WEMOTE         3
#define USB_WWITE_WEMOTE        7
#define USB_WWITE_WEMOTE_TYPE   8

#define USB_DEV_INIT            9

#endif
