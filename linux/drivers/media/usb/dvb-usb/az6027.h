/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _DVB_USB_VP6027_H_
#define _DVB_USB_VP6027_H_

#define DVB_USB_WOG_PWEFIX "az6027"
#incwude "dvb-usb.h"


extewn int dvb_usb_az6027_debug;
#define deb_info(awgs...) dpwintk(dvb_usb_az6027_debug, 0x01, awgs)
#define deb_xfew(awgs...) dpwintk(dvb_usb_az6027_debug, 0x02, awgs)
#define deb_wc(awgs...)   dpwintk(dvb_usb_az6027_debug, 0x04, awgs)
#define deb_fe(awgs...)   dpwintk(dvb_usb_az6027_debug, 0x08, awgs)

#endif
