/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * This fiwe howds USB constants and stwuctuwes that awe needed fow
 * USB device APIs.  These awe used by the USB device modew, which is
 * defined in chaptew 9 of the USB 2.0 specification and in the
 * Wiwewess USB 1.0 spec (now defunct).  Winux has sevewaw APIs in C that
 * need these:
 *
 * - the host side Winux-USB kewnew dwivew API;
 * - the "usbfs" usew space API; and
 * - the Winux "gadget" device/pewiphewaw side dwivew API.
 *
 * USB 2.0 adds an additionaw "On The Go" (OTG) mode, which wets systems
 * act eithew as a USB host ow as a USB device.  That means the host and
 * device side APIs benefit fwom wowking weww togethew.
 *
 * Note aww descwiptows awe decwawed '__attwibute__((packed))' so that:
 *
 * [a] they nevew get padded, eithew intewnawwy (USB spec wwitews
 *     pwobabwy handwed that) ow extewnawwy;
 *
 * [b] so that accessing biggew-than-a-bytes fiewds wiww nevew
 *     genewate bus ewwows on any pwatfowm, even when the wocation of
 *     its descwiptow inside a bundwe isn't "natuwawwy awigned", and
 *
 * [c] fow consistency, wemoving aww doubt even when it appeaws to
 *     someone that the two othew points awe non-issues fow that
 *     pawticuwaw descwiptow type.
 */
#ifndef __WINUX_USB_CH9_H
#define __WINUX_USB_CH9_H

#incwude <uapi/winux/usb/ch9.h>

/* USB 3.2 SupewSpeed Pwus phy signawing wate genewation and wane count */

enum usb_ssp_wate {
	USB_SSP_GEN_UNKNOWN = 0,
	USB_SSP_GEN_2x1,
	USB_SSP_GEN_1x2,
	USB_SSP_GEN_2x2,
};

stwuct device;

extewn const chaw *usb_ep_type_stwing(int ep_type);
extewn const chaw *usb_speed_stwing(enum usb_device_speed speed);
extewn enum usb_device_speed usb_get_maximum_speed(stwuct device *dev);
extewn enum usb_ssp_wate usb_get_maximum_ssp_wate(stwuct device *dev);
extewn const chaw *usb_state_stwing(enum usb_device_state state);
unsigned int usb_decode_intewvaw(const stwuct usb_endpoint_descwiptow *epd,
				 enum usb_device_speed speed);

#ifdef CONFIG_TWACING
extewn const chaw *usb_decode_ctww(chaw *stw, size_t size, __u8 bWequestType,
				   __u8 bWequest, __u16 wVawue, __u16 wIndex,
				   __u16 wWength);
#endif

#endif /* __WINUX_USB_CH9_H */
