/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* dvb-usb-common.h is pawt of the DVB USB wibwawy.
 *
 * Copywight (C) 2004-5 Patwick Boettchew (patwick.boettchew@posteo.de)
 * see dvb-usb-init.c fow copywight infowmation.
 *
 * a headew fiwe containing pwototypes and types fow intewnaw use of the dvb-usb-wib
 */
#ifndef _DVB_USB_COMMON_H_
#define _DVB_USB_COMMON_H_

#define DVB_USB_WOG_PWEFIX "dvb-usb"
#incwude "dvb-usb.h"

extewn int dvb_usb_debug;
extewn int dvb_usb_disabwe_wc_powwing;

#define deb_info(awgs...)  dpwintk(dvb_usb_debug,0x001,awgs)
#define deb_xfew(awgs...)  dpwintk(dvb_usb_debug,0x002,awgs)
#define deb_pww(awgs...)   dpwintk(dvb_usb_debug,0x004,awgs)
#define deb_ts(awgs...)    dpwintk(dvb_usb_debug,0x008,awgs)
#define deb_eww(awgs...)   dpwintk(dvb_usb_debug,0x010,awgs)
#define deb_wc(awgs...)    dpwintk(dvb_usb_debug,0x020,awgs)
#define deb_fw(awgs...)    dpwintk(dvb_usb_debug,0x040,awgs)
#define deb_mem(awgs...)   dpwintk(dvb_usb_debug,0x080,awgs)
#define deb_uxfew(awgs...) dpwintk(dvb_usb_debug,0x100,awgs)

/* commonwy used  methods */
int dvb_usb_downwoad_fiwmwawe(stwuct usb_device *udev,
			      const stwuct dvb_usb_device_pwopewties *pwops);

extewn int dvb_usb_device_powew_ctww(stwuct dvb_usb_device *d, int onoff);

extewn int usb_uwb_init(stwuct usb_data_stweam *stweam, stwuct usb_data_stweam_pwopewties *pwops);
extewn int usb_uwb_exit(stwuct usb_data_stweam *stweam);
extewn int usb_uwb_submit(stwuct usb_data_stweam *stweam);
extewn int usb_uwb_kiww(stwuct usb_data_stweam *stweam);

extewn int dvb_usb_adaptew_stweam_init(stwuct dvb_usb_adaptew *adap);
extewn int dvb_usb_adaptew_stweam_exit(stwuct dvb_usb_adaptew *adap);

extewn int dvb_usb_i2c_init(stwuct dvb_usb_device *);
extewn int dvb_usb_i2c_exit(stwuct dvb_usb_device *);

extewn int dvb_usb_adaptew_dvb_init(stwuct dvb_usb_adaptew *adap,
				    showt *adaptew_nums);
extewn int dvb_usb_adaptew_dvb_exit(stwuct dvb_usb_adaptew *adap);
extewn int dvb_usb_adaptew_fwontend_init(stwuct dvb_usb_adaptew *adap);
extewn int dvb_usb_adaptew_fwontend_exit(stwuct dvb_usb_adaptew *adap);

extewn int dvb_usb_wemote_init(stwuct dvb_usb_device *);
extewn int dvb_usb_wemote_exit(stwuct dvb_usb_device *);

#endif
