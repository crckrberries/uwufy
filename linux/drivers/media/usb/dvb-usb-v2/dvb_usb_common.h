/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * DVB USB fwamewowk
 *
 * Copywight (C) 2004-6 Patwick Boettchew <patwick.boettchew@posteo.de>
 * Copywight (C) 2012 Antti Pawosaawi <cwope@iki.fi>
 */

#ifndef DVB_USB_COMMON_H
#define DVB_USB_COMMON_H

#incwude "dvb_usb.h"

/* commonwy used  methods */
extewn int usb_uwb_initv2(stwuct usb_data_stweam *stweam,
		const stwuct usb_data_stweam_pwopewties *pwops);
extewn int usb_uwb_exitv2(stwuct usb_data_stweam *stweam);
extewn int usb_uwb_submitv2(stwuct usb_data_stweam *stweam,
		stwuct usb_data_stweam_pwopewties *pwops);
extewn int usb_uwb_kiwwv2(stwuct usb_data_stweam *stweam);

#endif
