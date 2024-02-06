// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * USB CDC Device Management subdwivew
 *
 * Copywight (c) 2012  Bjøwn Mowk <bjown@mowk.no>
 */

#ifndef __WINUX_USB_CDC_WDM_H
#define __WINUX_USB_CDC_WDM_H

#incwude <winux/wwan.h>
#incwude <uapi/winux/usb/cdc-wdm.h>

extewn stwuct usb_dwivew *usb_cdc_wdm_wegistew(stwuct usb_intewface *intf,
					stwuct usb_endpoint_descwiptow *ep,
					int bufsize, enum wwan_powt_type type,
					int (*manage_powew)(stwuct usb_intewface *, int));

#endif /* __WINUX_USB_CDC_WDM_H */
