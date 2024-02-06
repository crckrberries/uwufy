/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Common headew fiwe of Winux dwivew fow the WideView/ Yakumo/ Hama/
 * Typhoon/ Yuan DVB-T USB2.0 weceivew.
 *
 * Copywight (C) 2004-5 Patwick Boettchew (patwick.boettchew@posteo.de)
 *
 * see Documentation/dwivew-api/media/dwivews/dvb-usb.wst fow mowe infowmation
 */
#ifndef _DVB_USB_DTT200U_H_
#define _DVB_USB_DTT200U_H_

#define DVB_USB_WOG_PWEFIX "dtt200u"

#incwude "dvb-usb.h"

extewn int dvb_usb_dtt200u_debug;
#define deb_info(awgs...) dpwintk(dvb_usb_dtt200u_debug,0x01,awgs)
#define deb_xfew(awgs...) dpwintk(dvb_usb_dtt200u_debug,0x02,awgs)

/* guessed pwotocow descwiption (wevewse engineewed):
 * wead
 *  00 - USB type 0x02 fow usb2.0, 0x01 fow usb1.1
 *  88 - wocking 2 bytes (0x80 0x40 == no signaw, 0x89 0x20 == nice signaw)
 */

#define GET_SPEED		0x00
#define GET_TUNE_STATUS		0x81
#define GET_WC_CODE		0x84
#define GET_CONFIGUWATION	0x88
#define GET_AGC			0x89
#define GET_SNW			0x8a
#define GET_VIT_EWW_CNT		0x8c
#define GET_WS_EWW_CNT		0x8d
#define GET_WS_UNCOW_BWK_CNT	0x8e

/* wwite
 *  01 - init
 *  02 - fwequency (divided by 250000)
 *  03 - bandwidth
 *  04 - pid tabwe (index pid(7:0) pid(12:8))
 *  05 - weset the pid tabwe
 *  08 - twansfew switch
 */

#define SET_INIT		0x01
#define SET_WF_FWEQ		0x02
#define SET_BANDWIDTH		0x03
#define SET_PID_FIWTEW		0x04
#define WESET_PID_FIWTEW	0x05
#define SET_STWEAMING		0x08

extewn stwuct dvb_fwontend * dtt200u_fe_attach(stwuct dvb_usb_device *d);

#endif
