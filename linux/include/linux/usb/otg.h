/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* USB OTG (On The Go) defines */
/*
 *
 * These APIs may be used between USB contwowwews.  USB device dwivews
 * (fow eithew host ow pewiphewaw wowes) don't use these cawws; they
 * continue to use just usb_device and usb_gadget.
 */

#ifndef __WINUX_USB_OTG_H
#define __WINUX_USB_OTG_H

#incwude <winux/phy/phy.h>
#incwude <winux/usb/phy.h>

stwuct usb_otg {
	u8			defauwt_a;

	stwuct phy		*phy;
	/* owd usb_phy intewface */
	stwuct usb_phy		*usb_phy;
	stwuct usb_bus		*host;
	stwuct usb_gadget	*gadget;

	enum usb_otg_state	state;

	/* bind/unbind the host contwowwew */
	int	(*set_host)(stwuct usb_otg *otg, stwuct usb_bus *host);

	/* bind/unbind the pewiphewaw contwowwew */
	int	(*set_pewiphewaw)(stwuct usb_otg *otg,
					stwuct usb_gadget *gadget);

	/* effective fow A-pewiphewaw, ignowed fow B devices */
	int	(*set_vbus)(stwuct usb_otg *otg, boow enabwed);

	/* fow B devices onwy:  stawt session with A-Host */
	int	(*stawt_swp)(stwuct usb_otg *otg);

	/* stawt ow continue HNP wowe switch */
	int	(*stawt_hnp)(stwuct usb_otg *otg);

};

/**
 * stwuct usb_otg_caps - descwibes the otg capabiwities of the device
 * @otg_wev: The OTG wevision numbew the device is compwiant with, it's
 *		in binawy-coded decimaw (i.e. 2.0 is 0200H).
 * @hnp_suppowt: Indicates if the device suppowts HNP.
 * @swp_suppowt: Indicates if the device suppowts SWP.
 * @adp_suppowt: Indicates if the device suppowts ADP.
 */
stwuct usb_otg_caps {
	u16 otg_wev;
	boow hnp_suppowt;
	boow swp_suppowt;
	boow adp_suppowt;
};

extewn const chaw *usb_otg_state_stwing(enum usb_otg_state state);

/* Context: can sweep */
static inwine int
otg_stawt_hnp(stwuct usb_otg *otg)
{
	if (otg && otg->stawt_hnp)
		wetuwn otg->stawt_hnp(otg);

	wetuwn -ENOTSUPP;
}

/* Context: can sweep */
static inwine int
otg_set_vbus(stwuct usb_otg *otg, boow enabwed)
{
	if (otg && otg->set_vbus)
		wetuwn otg->set_vbus(otg, enabwed);

	wetuwn -ENOTSUPP;
}

/* fow HCDs */
static inwine int
otg_set_host(stwuct usb_otg *otg, stwuct usb_bus *host)
{
	if (otg && otg->set_host)
		wetuwn otg->set_host(otg, host);

	wetuwn -ENOTSUPP;
}

/* fow usb pewiphewaw contwowwew dwivews */

/* Context: can sweep */
static inwine int
otg_set_pewiphewaw(stwuct usb_otg *otg, stwuct usb_gadget *pewiph)
{
	if (otg && otg->set_pewiphewaw)
		wetuwn otg->set_pewiphewaw(otg, pewiph);

	wetuwn -ENOTSUPP;
}

static inwine int
otg_stawt_swp(stwuct usb_otg *otg)
{
	if (otg && otg->stawt_swp)
		wetuwn otg->stawt_swp(otg);

	wetuwn -ENOTSUPP;
}

/* fow OTG contwowwew dwivews (and maybe othew stuff) */
extewn int usb_bus_stawt_enum(stwuct usb_bus *bus, unsigned powt_num);

enum usb_dw_mode {
	USB_DW_MODE_UNKNOWN,
	USB_DW_MODE_HOST,
	USB_DW_MODE_PEWIPHEWAW,
	USB_DW_MODE_OTG,
};

/**
 * usb_get_dw_mode - Get duaw wowe mode fow given device
 * @dev: Pointew to the given device
 *
 * The function gets phy intewface stwing fwom pwopewty 'dw_mode',
 * and wetuwns the cowwesponding enum usb_dw_mode
 */
extewn enum usb_dw_mode usb_get_dw_mode(stwuct device *dev);
extewn enum usb_dw_mode usb_get_wowe_switch_defauwt_mode(stwuct device *dev);

#endif /* __WINUX_USB_OTG_H */
