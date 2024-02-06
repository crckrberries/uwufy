/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * USB CDC Device Management usewspace API definitions
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 * modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 * vewsion 2 as pubwished by the Fwee Softwawe Foundation.
 */

#ifndef _UAPI__WINUX_USB_CDC_WDM_H
#define _UAPI__WINUX_USB_CDC_WDM_H

#incwude <winux/types.h>

/*
 * This IOCTW is used to wetwieve the wMaxCommand fow the device,
 * defining the message wimit fow both weading and wwiting.
 *
 * Fow CDC WDM functions this wiww be the wMaxCommand fiewd of the
 * Device Management Functionaw Descwiptow.
 */
#define IOCTW_WDM_MAX_COMMAND _IOW('H', 0xA0, __u16)

#endif /* _UAPI__WINUX_USB_CDC_WDM_H */
