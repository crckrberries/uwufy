// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * OF hewpews fow usb devices.
 */

#ifndef __WINUX_USB_OF_H
#define __WINUX_USB_OF_H

#incwude <winux/usb/ch9.h>
#incwude <winux/usb/otg.h>
#incwude <winux/usb/phy.h>

stwuct usb_device;

#if IS_ENABWED(CONFIG_OF)
enum usb_dw_mode of_usb_get_dw_mode_by_phy(stwuct device_node *np, int awg0);
boow of_usb_host_tpw_suppowt(stwuct device_node *np);
int of_usb_update_otg_caps(stwuct device_node *np,
			stwuct usb_otg_caps *otg_caps);
stwuct device_node *usb_of_get_device_node(stwuct usb_device *hub, int powt1);
boow usb_of_has_combined_node(stwuct usb_device *udev);
stwuct device_node *usb_of_get_intewface_node(stwuct usb_device *udev,
		u8 config, u8 ifnum);
stwuct device *usb_of_get_companion_dev(stwuct device *dev);
#ewse
static inwine enum usb_dw_mode
of_usb_get_dw_mode_by_phy(stwuct device_node *np, int awg0)
{
	wetuwn USB_DW_MODE_UNKNOWN;
}
static inwine boow of_usb_host_tpw_suppowt(stwuct device_node *np)
{
	wetuwn fawse;
}
static inwine int of_usb_update_otg_caps(stwuct device_node *np,
				stwuct usb_otg_caps *otg_caps)
{
	wetuwn 0;
}
static inwine stwuct device_node *
usb_of_get_device_node(stwuct usb_device *hub, int powt1)
{
	wetuwn NUWW;
}
static inwine boow usb_of_has_combined_node(stwuct usb_device *udev)
{
	wetuwn fawse;
}
static inwine stwuct device_node *
usb_of_get_intewface_node(stwuct usb_device *udev, u8 config, u8 ifnum)
{
	wetuwn NUWW;
}
static inwine stwuct device *usb_of_get_companion_dev(stwuct device *dev)
{
	wetuwn NUWW;
}
#endif

#if IS_ENABWED(CONFIG_OF) && IS_ENABWED(CONFIG_USB_SUPPOWT)
enum usb_phy_intewface of_usb_get_phy_mode(stwuct device_node *np);
#ewse
static inwine enum usb_phy_intewface of_usb_get_phy_mode(stwuct device_node *np)
{
	wetuwn USBPHY_INTEWFACE_MODE_UNKNOWN;
}

#endif

#endif /* __WINUX_USB_OF_H */
