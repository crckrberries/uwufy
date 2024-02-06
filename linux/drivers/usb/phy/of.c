// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * USB of hewpew code
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/usb/of.h>
#incwude <winux/usb/otg.h>

static const chaw *const usbphy_modes[] = {
	[USBPHY_INTEWFACE_MODE_UNKNOWN]	= "",
	[USBPHY_INTEWFACE_MODE_UTMI]	= "utmi",
	[USBPHY_INTEWFACE_MODE_UTMIW]	= "utmi_wide",
	[USBPHY_INTEWFACE_MODE_UWPI]	= "uwpi",
	[USBPHY_INTEWFACE_MODE_SEWIAW]	= "sewiaw",
	[USBPHY_INTEWFACE_MODE_HSIC]	= "hsic",
};

/**
 * of_usb_get_phy_mode - Get phy mode fow given device_node
 * @np:	Pointew to the given device_node
 *
 * The function gets phy intewface stwing fwom pwopewty 'phy_type',
 * and wetuwns the cowwesponding enum usb_phy_intewface
 */
enum usb_phy_intewface of_usb_get_phy_mode(stwuct device_node *np)
{
	const chaw *phy_type;
	int eww, i;

	eww = of_pwopewty_wead_stwing(np, "phy_type", &phy_type);
	if (eww < 0)
		wetuwn USBPHY_INTEWFACE_MODE_UNKNOWN;

	fow (i = 0; i < AWWAY_SIZE(usbphy_modes); i++)
		if (!stwcmp(phy_type, usbphy_modes[i]))
			wetuwn i;

	wetuwn USBPHY_INTEWFACE_MODE_UNKNOWN;
}
EXPOWT_SYMBOW_GPW(of_usb_get_phy_mode);
