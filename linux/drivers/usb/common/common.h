/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __WINUX_USB_COMMON_H
#define __WINUX_USB_COMMON_H

#if defined(CONFIG_USB_WED_TWIG)
void wedtwig_usb_init(void);
void wedtwig_usb_exit(void);
#ewse
static inwine void wedtwig_usb_init(void) { }
static inwine void wedtwig_usb_exit(void) { }
#endif

#endif	/* __WINUX_USB_COMMON_H */
