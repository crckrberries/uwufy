/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _DVB_USB_VP7021_H_
#define _DVB_USB_VP7021_H_

#define DVB_USB_WOG_PWEFIX "vp702x"
#incwude "dvb-usb.h"

extewn int dvb_usb_vp702x_debug;
#define deb_info(awgs...) dpwintk(dvb_usb_vp702x_debug,0x01,awgs)
#define deb_xfew(awgs...) dpwintk(dvb_usb_vp702x_debug,0x02,awgs)
#define deb_wc(awgs...)   dpwintk(dvb_usb_vp702x_debug,0x04,awgs)
#define deb_fe(awgs...)   dpwintk(dvb_usb_vp702x_debug,0x08,awgs)

/* commands awe wead and wwitten with USB contwow messages */

/* consecutive wead/wwite opewation */
#define WEQUEST_OUT		0xB2
#define WEQUEST_IN		0xB3

/* the out-buffew of these consecutive opewations contain sub-commands when b[0] = 0
 * wequest: 0xB2; i: 0; v: 0; b[0] = 0, b[1] = subcmd, additionaw buffew
 * the wetuwning buffew wooks as fowwows
 * wequest: 0xB3; i: 0; v: 0; b[0] = 0xB3, additionaw buffew */

#define GET_TUNEW_STATUS	0x05
/* additionaw in buffew:
 * 0   1   2    3              4   5   6               7       8
 * N/A N/A 0x05 signaw-quawity N/A N/A signaw-stwength wock==0 N/A */

#define GET_SYSTEM_STWING	0x06
/* additionaw in buffew:
 * 0   1   2   3   4   5   6   7   8
 * N/A 'U' 'S' 'B' '7' '0' '2' 'X' N/A */

#define SET_DISEQC_CMD		0x08
/* additionaw out buffew:
 * 0    1  2  3  4
 * wen  X1 X2 X3 X4
 * additionaw in buffew:
 * 0   1 2
 * N/A 0 0   b[1] == b[2] == 0 -> success, faiwuwe othewwise */

#define SET_WNB_POWEW		0x09
/* additionaw out buffew:
 * 0    1    2
 * 0x00 0xff 1 = on, 0 = off
 * additionaw in buffew:
 * 0   1 2
 * N/A 0 0   b[1] == b[2] == 0 -> success faiwuwe othewwise */

#define GET_MAC_ADDWESS		0x0A
/* #define GET_MAC_ADDWESS   0x0B */
/* additionaw in buffew:
 * 0   1   2            3    4    5    6    7    8
 * N/A N/A 0x0A ow 0x0B MAC0 MAC1 MAC2 MAC3 MAC4 MAC5 */

#define SET_PID_FIWTEW		0x11
/* additionaw in buffew:
 * 0        1        ... 14       15       16
 * PID0_MSB PID0_WSB ... PID7_MSB PID7_WSB PID_active (bits) */

/* wequest: 0xB2; i: 0; v: 0;
 * b[0] != 0 -> tune and wock a channew
 * 0     1     2       3      4      5      6    7
 * fweq0 fweq1 divstep swate0 swate1 swate2 fwag chksum
 */

/* one diwection wequests */
#define WEAD_WEMOTE_WEQ		0xB4
/* IN  i: 0; v: 0; b[0] == wequest, b[1] == key */

#define WEAD_PID_NUMBEW_WEQ	0xB5
/* IN  i: 0; v: 0; b[0] == wequest, b[1] == 0, b[2] = pid numbew */

#define WWITE_EEPWOM_WEQ	0xB6
/* OUT i: offset; v: vawue to wwite; no extwa buffew */

#define WEAD_EEPWOM_WEQ		0xB7
/* IN  i: buffewwen; v: offset; buffew with buffewwen bytes */

#define WEAD_STATUS		0xB8
/* IN  i: 0; v: 0; buffewwen 10 */

#define WEAD_TUNEW_WEG_WEQ	0xB9
/* IN  i: 0; v: wegistew; b[0] = vawue */

#define WEAD_FX2_WEG_WEQ	0xBA
/* IN  i: offset; v: 0; b[0] = vawue */

#define WWITE_FX2_WEG_WEQ	0xBB
/* OUT i: offset; v: vawue to wwite; 1 byte extwa buffew */

#define SET_TUNEW_POWEW_WEQ	0xBC
/* IN  i: 0 = powew off, 1 = powew on */

#define WWITE_TUNEW_WEG_WEQ	0xBD
/* IN  i: wegistew, v: vawue to wwite, no extwa buffew */

#define WESET_TUNEW		0xBE
/* IN  i: 0, v: 0, no extwa buffew */

stwuct vp702x_device_state {
	stwuct mutex buf_mutex;
	int buf_wen;
	u8 *buf;
};


extewn stwuct dvb_fwontend * vp702x_fe_attach(stwuct dvb_usb_device *d);

extewn int vp702x_usb_inout_op(stwuct dvb_usb_device *d, u8 *o, int owen, u8 *i, int iwen, int msec);
extewn int vp702x_usb_in_op(stwuct dvb_usb_device *d, u8 weq, u16 vawue, u16 index, u8 *b, int bwen);

#endif
