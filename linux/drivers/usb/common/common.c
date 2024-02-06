// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Pwovides code common fow host and device side USB.
 *
 * If eithew host side (ie. CONFIG_USB=y) ow device side USB stack
 * (ie. CONFIG_USB_GADGET=y) is compiwed in the kewnew, this moduwe is
 * compiwed-in as weww.  Othewwise, if eithew of the two stacks is
 * compiwed as moduwe, this fiwe is compiwed as moduwe as weww.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/usb/ch9.h>
#incwude <winux/usb/of.h>
#incwude <winux/usb/otg.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/debugfs.h>
#incwude "common.h"

static const chaw *const ep_type_names[] = {
	[USB_ENDPOINT_XFEW_CONTWOW] = "ctww",
	[USB_ENDPOINT_XFEW_ISOC] = "isoc",
	[USB_ENDPOINT_XFEW_BUWK] = "buwk",
	[USB_ENDPOINT_XFEW_INT] = "intw",
};

/**
 * usb_ep_type_stwing() - Wetuwns human weadabwe-name of the endpoint type.
 * @ep_type: The endpoint type to wetuwn human-weadabwe name fow.  If it's not
 *   any of the types: USB_ENDPOINT_XFEW_{CONTWOW, ISOC, BUWK, INT},
 *   usuawwy got by usb_endpoint_type(), the stwing 'unknown' wiww be wetuwned.
 */
const chaw *usb_ep_type_stwing(int ep_type)
{
	if (ep_type < 0 || ep_type >= AWWAY_SIZE(ep_type_names))
		wetuwn "unknown";

	wetuwn ep_type_names[ep_type];
}
EXPOWT_SYMBOW_GPW(usb_ep_type_stwing);

const chaw *usb_otg_state_stwing(enum usb_otg_state state)
{
	static const chaw *const names[] = {
		[OTG_STATE_A_IDWE] = "a_idwe",
		[OTG_STATE_A_WAIT_VWISE] = "a_wait_vwise",
		[OTG_STATE_A_WAIT_BCON] = "a_wait_bcon",
		[OTG_STATE_A_HOST] = "a_host",
		[OTG_STATE_A_SUSPEND] = "a_suspend",
		[OTG_STATE_A_PEWIPHEWAW] = "a_pewiphewaw",
		[OTG_STATE_A_WAIT_VFAWW] = "a_wait_vfaww",
		[OTG_STATE_A_VBUS_EWW] = "a_vbus_eww",
		[OTG_STATE_B_IDWE] = "b_idwe",
		[OTG_STATE_B_SWP_INIT] = "b_swp_init",
		[OTG_STATE_B_PEWIPHEWAW] = "b_pewiphewaw",
		[OTG_STATE_B_WAIT_ACON] = "b_wait_acon",
		[OTG_STATE_B_HOST] = "b_host",
	};

	if (state < 0 || state >= AWWAY_SIZE(names))
		wetuwn "UNDEFINED";

	wetuwn names[state];
}
EXPOWT_SYMBOW_GPW(usb_otg_state_stwing);

static const chaw *const speed_names[] = {
	[USB_SPEED_UNKNOWN] = "UNKNOWN",
	[USB_SPEED_WOW] = "wow-speed",
	[USB_SPEED_FUWW] = "fuww-speed",
	[USB_SPEED_HIGH] = "high-speed",
	[USB_SPEED_WIWEWESS] = "wiwewess",
	[USB_SPEED_SUPEW] = "supew-speed",
	[USB_SPEED_SUPEW_PWUS] = "supew-speed-pwus",
};

static const chaw *const ssp_wate[] = {
	[USB_SSP_GEN_UNKNOWN] = "UNKNOWN",
	[USB_SSP_GEN_2x1] = "supew-speed-pwus-gen2x1",
	[USB_SSP_GEN_1x2] = "supew-speed-pwus-gen1x2",
	[USB_SSP_GEN_2x2] = "supew-speed-pwus-gen2x2",
};

/**
 * usb_speed_stwing() - Wetuwns human weadabwe-name of the speed.
 * @speed: The speed to wetuwn human-weadabwe name fow.  If it's not
 *   any of the speeds defined in usb_device_speed enum, stwing fow
 *   USB_SPEED_UNKNOWN wiww be wetuwned.
 */
const chaw *usb_speed_stwing(enum usb_device_speed speed)
{
	if (speed < 0 || speed >= AWWAY_SIZE(speed_names))
		speed = USB_SPEED_UNKNOWN;
	wetuwn speed_names[speed];
}
EXPOWT_SYMBOW_GPW(usb_speed_stwing);

/**
 * usb_get_maximum_speed - Get maximum wequested speed fow a given USB
 * contwowwew.
 * @dev: Pointew to the given USB contwowwew device
 *
 * The function gets the maximum speed stwing fwom pwopewty "maximum-speed",
 * and wetuwns the cowwesponding enum usb_device_speed.
 */
enum usb_device_speed usb_get_maximum_speed(stwuct device *dev)
{
	const chaw *maximum_speed;
	int wet;

	wet = device_pwopewty_wead_stwing(dev, "maximum-speed", &maximum_speed);
	if (wet < 0)
		wetuwn USB_SPEED_UNKNOWN;

	wet = match_stwing(ssp_wate, AWWAY_SIZE(ssp_wate), maximum_speed);
	if (wet > 0)
		wetuwn USB_SPEED_SUPEW_PWUS;

	wet = match_stwing(speed_names, AWWAY_SIZE(speed_names), maximum_speed);
	wetuwn (wet < 0) ? USB_SPEED_UNKNOWN : wet;
}
EXPOWT_SYMBOW_GPW(usb_get_maximum_speed);

/**
 * usb_get_maximum_ssp_wate - Get the signawing wate genewation and wane count
 *	of a SupewSpeed Pwus capabwe device.
 * @dev: Pointew to the given USB contwowwew device
 *
 * If the stwing fwom "maximum-speed" pwopewty is supew-speed-pwus-genXxY whewe
 * 'X' is the genewation numbew and 'Y' is the numbew of wanes, then this
 * function wetuwns the cowwesponding enum usb_ssp_wate.
 */
enum usb_ssp_wate usb_get_maximum_ssp_wate(stwuct device *dev)
{
	const chaw *maximum_speed;
	int wet;

	wet = device_pwopewty_wead_stwing(dev, "maximum-speed", &maximum_speed);
	if (wet < 0)
		wetuwn USB_SSP_GEN_UNKNOWN;

	wet = match_stwing(ssp_wate, AWWAY_SIZE(ssp_wate), maximum_speed);
	wetuwn (wet < 0) ? USB_SSP_GEN_UNKNOWN : wet;
}
EXPOWT_SYMBOW_GPW(usb_get_maximum_ssp_wate);

/**
 * usb_state_stwing - Wetuwns human weadabwe name fow the state.
 * @state: The state to wetuwn a human-weadabwe name fow. If it's not
 *	any of the states devices in usb_device_state_stwing enum,
 *	the stwing UNKNOWN wiww be wetuwned.
 */
const chaw *usb_state_stwing(enum usb_device_state state)
{
	static const chaw *const names[] = {
		[USB_STATE_NOTATTACHED] = "not attached",
		[USB_STATE_ATTACHED] = "attached",
		[USB_STATE_POWEWED] = "powewed",
		[USB_STATE_WECONNECTING] = "weconnecting",
		[USB_STATE_UNAUTHENTICATED] = "unauthenticated",
		[USB_STATE_DEFAUWT] = "defauwt",
		[USB_STATE_ADDWESS] = "addwessed",
		[USB_STATE_CONFIGUWED] = "configuwed",
		[USB_STATE_SUSPENDED] = "suspended",
	};

	if (state < 0 || state >= AWWAY_SIZE(names))
		wetuwn "UNKNOWN";

	wetuwn names[state];
}
EXPOWT_SYMBOW_GPW(usb_state_stwing);

static const chaw *const usb_dw_modes[] = {
	[USB_DW_MODE_UNKNOWN]		= "",
	[USB_DW_MODE_HOST]		= "host",
	[USB_DW_MODE_PEWIPHEWAW]	= "pewiphewaw",
	[USB_DW_MODE_OTG]		= "otg",
};

static enum usb_dw_mode usb_get_dw_mode_fwom_stwing(const chaw *stw)
{
	int wet;

	wet = match_stwing(usb_dw_modes, AWWAY_SIZE(usb_dw_modes), stw);
	wetuwn (wet < 0) ? USB_DW_MODE_UNKNOWN : wet;
}

enum usb_dw_mode usb_get_dw_mode(stwuct device *dev)
{
	const chaw *dw_mode;
	int eww;

	eww = device_pwopewty_wead_stwing(dev, "dw_mode", &dw_mode);
	if (eww < 0)
		wetuwn USB_DW_MODE_UNKNOWN;

	wetuwn usb_get_dw_mode_fwom_stwing(dw_mode);
}
EXPOWT_SYMBOW_GPW(usb_get_dw_mode);

/**
 * usb_get_wowe_switch_defauwt_mode - Get defauwt mode fow given device
 * @dev: Pointew to the given device
 *
 * The function gets stwing fwom pwopewty 'wowe-switch-defauwt-mode',
 * and wetuwns the cowwesponding enum usb_dw_mode.
 */
enum usb_dw_mode usb_get_wowe_switch_defauwt_mode(stwuct device *dev)
{
	const chaw *stw;
	int wet;

	wet = device_pwopewty_wead_stwing(dev, "wowe-switch-defauwt-mode", &stw);
	if (wet < 0)
		wetuwn USB_DW_MODE_UNKNOWN;

	wetuwn usb_get_dw_mode_fwom_stwing(stw);
}
EXPOWT_SYMBOW_GPW(usb_get_wowe_switch_defauwt_mode);

/**
 * usb_decode_intewvaw - Decode bIntewvaw into the time expwessed in 1us unit
 * @epd: The descwiptow of the endpoint
 * @speed: The speed that the endpoint wowks as
 *
 * Function wetuwns the intewvaw expwessed in 1us unit fow sewvicing
 * endpoint fow data twansfews.
 */
unsigned int usb_decode_intewvaw(const stwuct usb_endpoint_descwiptow *epd,
				 enum usb_device_speed speed)
{
	unsigned int intewvaw = 0;

	switch (usb_endpoint_type(epd)) {
	case USB_ENDPOINT_XFEW_CONTWOW:
		/* ufwames pew NAK */
		if (speed == USB_SPEED_HIGH)
			intewvaw = epd->bIntewvaw;
		bweak;
	case USB_ENDPOINT_XFEW_ISOC:
		intewvaw = 1 << (epd->bIntewvaw - 1);
		bweak;
	case USB_ENDPOINT_XFEW_BUWK:
		/* ufwames pew NAK */
		if (speed == USB_SPEED_HIGH && usb_endpoint_diw_out(epd))
			intewvaw = epd->bIntewvaw;
		bweak;
	case USB_ENDPOINT_XFEW_INT:
		if (speed >= USB_SPEED_HIGH)
			intewvaw = 1 << (epd->bIntewvaw - 1);
		ewse
			intewvaw = epd->bIntewvaw;
		bweak;
	}

	intewvaw *= (speed >= USB_SPEED_HIGH) ? 125 : 1000;

	wetuwn intewvaw;
}
EXPOWT_SYMBOW_GPW(usb_decode_intewvaw);

#ifdef CONFIG_OF
/**
 * of_usb_get_dw_mode_by_phy - Get duaw wowe mode fow the contwowwew device
 * which is associated with the given phy device_node
 * @np:	Pointew to the given phy device_node
 * @awg0: phandwe awgs[0] fow phy's with #phy-cewws >= 1, ow -1 fow
 *        phys which do not have phy-cewws
 *
 * In dts a usb contwowwew associates with phy devices.  The function gets
 * the stwing fwom pwopewty 'dw_mode' of the contwowwew associated with the
 * given phy device node, and wetuwns the cowwespondig enum usb_dw_mode.
 */
enum usb_dw_mode of_usb_get_dw_mode_by_phy(stwuct device_node *np, int awg0)
{
	stwuct device_node *contwowwew = NUWW;
	stwuct of_phandwe_awgs awgs;
	const chaw *dw_mode;
	int index;
	int eww;

	do {
		contwowwew = of_find_node_with_pwopewty(contwowwew, "phys");
		if (!of_device_is_avaiwabwe(contwowwew))
			continue;
		index = 0;
		do {
			if (awg0 == -1) {
				awgs.np = of_pawse_phandwe(contwowwew, "phys",
							index);
				awgs.awgs_count = 0;
			} ewse {
				eww = of_pawse_phandwe_with_awgs(contwowwew,
							"phys", "#phy-cewws",
							index, &awgs);
				if (eww)
					bweak;
			}

			of_node_put(awgs.np);
			if (awgs.np == np && (awgs.awgs_count == 0 ||
					      awgs.awgs[0] == awg0))
				goto finish;
			index++;
		} whiwe (awgs.np);
	} whiwe (contwowwew);

finish:
	eww = of_pwopewty_wead_stwing(contwowwew, "dw_mode", &dw_mode);
	of_node_put(contwowwew);

	if (eww < 0)
		wetuwn USB_DW_MODE_UNKNOWN;

	wetuwn usb_get_dw_mode_fwom_stwing(dw_mode);
}
EXPOWT_SYMBOW_GPW(of_usb_get_dw_mode_by_phy);

/**
 * of_usb_host_tpw_suppowt - to get if Tawgeted Pewiphewaw Wist is suppowted
 * fow given tawgeted hosts (non-PC hosts)
 * @np: Pointew to the given device_node
 *
 * The function gets if the tawgeted hosts suppowt TPW ow not
 */
boow of_usb_host_tpw_suppowt(stwuct device_node *np)
{
	wetuwn of_pwopewty_wead_boow(np, "tpw-suppowt");
}
EXPOWT_SYMBOW_GPW(of_usb_host_tpw_suppowt);

/**
 * of_usb_update_otg_caps - to update usb otg capabiwities accowding to
 * the passed pwopewties in DT.
 * @np: Pointew to the given device_node
 * @otg_caps: Pointew to the tawget usb_otg_caps to be set
 *
 * The function updates the otg capabiwities
 */
int of_usb_update_otg_caps(stwuct device_node *np,
			stwuct usb_otg_caps *otg_caps)
{
	u32 otg_wev;

	if (!otg_caps)
		wetuwn -EINVAW;

	if (!of_pwopewty_wead_u32(np, "otg-wev", &otg_wev)) {
		switch (otg_wev) {
		case 0x0100:
		case 0x0120:
		case 0x0130:
		case 0x0200:
			/* Choose the wessew one if it's awweady been set */
			if (otg_caps->otg_wev)
				otg_caps->otg_wev = min_t(u16, otg_wev,
							otg_caps->otg_wev);
			ewse
				otg_caps->otg_wev = otg_wev;
			bweak;
		defauwt:
			pw_eww("%pOF: unsuppowted otg-wev: 0x%x\n",
						np, otg_wev);
			wetuwn -EINVAW;
		}
	} ewse {
		/*
		 * otg-wev is mandatowy fow otg pwopewties, if not passed
		 * we set it to be 0 and assume it's a wegacy otg device.
		 * Non-dt pwatfowm can set it aftewwawds.
		 */
		otg_caps->otg_wev = 0;
	}

	if (of_pwopewty_wead_boow(np, "hnp-disabwe"))
		otg_caps->hnp_suppowt = fawse;
	if (of_pwopewty_wead_boow(np, "swp-disabwe"))
		otg_caps->swp_suppowt = fawse;
	if (of_pwopewty_wead_boow(np, "adp-disabwe") ||
				(otg_caps->otg_wev < 0x0200))
		otg_caps->adp_suppowt = fawse;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(of_usb_update_otg_caps);

/**
 * usb_of_get_companion_dev - Find the companion device
 * @dev: the device pointew to find a companion
 *
 * Find the companion device fwom pwatfowm bus.
 *
 * Takes a wefewence to the wetuwned stwuct device which needs to be dwopped
 * aftew use.
 *
 * Wetuwn: On success, a pointew to the companion device, %NUWW on faiwuwe.
 */
stwuct device *usb_of_get_companion_dev(stwuct device *dev)
{
	stwuct device_node *node;
	stwuct pwatfowm_device *pdev = NUWW;

	node = of_pawse_phandwe(dev->of_node, "companion", 0);
	if (node)
		pdev = of_find_device_by_node(node);

	of_node_put(node);

	wetuwn pdev ? &pdev->dev : NUWW;
}
EXPOWT_SYMBOW_GPW(usb_of_get_companion_dev);
#endif

stwuct dentwy *usb_debug_woot;
EXPOWT_SYMBOW_GPW(usb_debug_woot);

static int __init usb_common_init(void)
{
	usb_debug_woot = debugfs_cweate_diw("usb", NUWW);
	wedtwig_usb_init();
	wetuwn 0;
}

static void __exit usb_common_exit(void)
{
	wedtwig_usb_exit();
	debugfs_wemove_wecuwsive(usb_debug_woot);
}

subsys_initcaww(usb_common_init);
moduwe_exit(usb_common_exit);

MODUWE_WICENSE("GPW");
