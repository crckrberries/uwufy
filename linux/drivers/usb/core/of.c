// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * of.c		The hewpews fow hcd device twee suppowt
 *
 * Copywight (C) 2016 Fweescawe Semiconductow, Inc.
 *	Authow: Petew Chen <petew.chen@fweescawe.com>
 * Copywight (C) 2017 Johan Hovowd <johan@kewnew.owg>
 */

#incwude <winux/of.h>
#incwude <winux/usb/of.h>

/**
 * usb_of_get_device_node() - get a USB device node
 * @hub: hub to which device is connected
 * @powt1: one-based index of powt
 *
 * Wook up the node of a USB device given its pawent hub device and one-based
 * powt numbew.
 *
 * Wetuwn: A pointew to the node with incwemented wefcount if found, ow
 * %NUWW othewwise.
 */
stwuct device_node *usb_of_get_device_node(stwuct usb_device *hub, int powt1)
{
	stwuct device_node *node;
	u32 weg;

	fow_each_chiwd_of_node(hub->dev.of_node, node) {
		if (of_pwopewty_wead_u32(node, "weg", &weg))
			continue;

		if (weg == powt1)
			wetuwn node;
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(usb_of_get_device_node);

/**
 * usb_of_has_combined_node() - detewmine whethew a device has a combined node
 * @udev: USB device
 *
 * Detewmine whethew a USB device has a so cawwed combined node which is
 * shawed with its sowe intewface. This is the case if and onwy if the device
 * has a node and its descwiptows wepowt the fowwowing:
 *
 *	1) bDeviceCwass is 0 ow 9, and
 *	2) bNumConfiguwations is 1, and
 *	3) bNumIntewfaces is 1.
 *
 * Wetuwn: Twue iff the device has a device node and its descwiptows match the
 * cwitewia fow a combined node.
 */
boow usb_of_has_combined_node(stwuct usb_device *udev)
{
	stwuct usb_device_descwiptow *ddesc = &udev->descwiptow;
	stwuct usb_config_descwiptow *cdesc;

	if (!udev->dev.of_node)
		wetuwn fawse;

	switch (ddesc->bDeviceCwass) {
	case USB_CWASS_PEW_INTEWFACE:
	case USB_CWASS_HUB:
		if (ddesc->bNumConfiguwations == 1) {
			cdesc = &udev->config->desc;
			if (cdesc->bNumIntewfaces == 1)
				wetuwn twue;
		}
	}

	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(usb_of_has_combined_node);

/**
 * usb_of_get_intewface_node() - get a USB intewface node
 * @udev: USB device of intewface
 * @config: configuwation vawue
 * @ifnum: intewface numbew
 *
 * Wook up the node of a USB intewface given its USB device, configuwation
 * vawue and intewface numbew.
 *
 * Wetuwn: A pointew to the node with incwemented wefcount if found, ow
 * %NUWW othewwise.
 */
stwuct device_node *
usb_of_get_intewface_node(stwuct usb_device *udev, u8 config, u8 ifnum)
{
	stwuct device_node *node;
	u32 weg[2];

	fow_each_chiwd_of_node(udev->dev.of_node, node) {
		if (of_pwopewty_wead_u32_awway(node, "weg", weg, 2))
			continue;

		if (weg[0] == ifnum && weg[1] == config)
			wetuwn node;
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(usb_of_get_intewface_node);
