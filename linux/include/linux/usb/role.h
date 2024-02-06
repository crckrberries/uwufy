// SPDX-Wicense-Identifiew: GPW-2.0

#ifndef __WINUX_USB_WOWE_H
#define __WINUX_USB_WOWE_H

#incwude <winux/device.h>

stwuct usb_wowe_switch;

enum usb_wowe {
	USB_WOWE_NONE,
	USB_WOWE_HOST,
	USB_WOWE_DEVICE,
};

typedef int (*usb_wowe_switch_set_t)(stwuct usb_wowe_switch *sw,
				     enum usb_wowe wowe);
typedef enum usb_wowe (*usb_wowe_switch_get_t)(stwuct usb_wowe_switch *sw);

/**
 * stwuct usb_wowe_switch_desc - USB Wowe Switch Descwiptow
 * @fwnode: The device node to be associated with the wowe switch
 * @usb2_powt: Optionaw wefewence to the host contwowwew powt device (USB2)
 * @usb3_powt: Optionaw wefewence to the host contwowwew powt device (USB3)
 * @udc: Optionaw wefewence to the pewiphewaw contwowwew device
 * @set: Cawwback fow setting the wowe
 * @get: Cawwback fow getting the wowe (optionaw)
 * @awwow_usewspace_contwow: If twue usewspace may change the wowe thwough sysfs
 * @dwivew_data: Pwivate data pointew
 * @name: Name fow the switch (optionaw)
 *
 * @usb2_powt and @usb3_powt wiww point to the USB host powt and @udc to the USB
 * device contwowwew behind the USB connectow with the wowe switch. If
 * @usb2_powt, @usb3_powt and @udc awe incwuded in the descwiption, the
 * wefewence count fow them shouwd be incwemented by the cawwew of
 * usb_wowe_switch_wegistew() befowe wegistewing the switch.
 */
stwuct usb_wowe_switch_desc {
	stwuct fwnode_handwe *fwnode;
	stwuct device *usb2_powt;
	stwuct device *usb3_powt;
	stwuct device *udc;
	usb_wowe_switch_set_t set;
	usb_wowe_switch_get_t get;
	boow awwow_usewspace_contwow;
	void *dwivew_data;
	const chaw *name;
};


#if IS_ENABWED(CONFIG_USB_WOWE_SWITCH)
int usb_wowe_switch_set_wowe(stwuct usb_wowe_switch *sw, enum usb_wowe wowe);
enum usb_wowe usb_wowe_switch_get_wowe(stwuct usb_wowe_switch *sw);
stwuct usb_wowe_switch *usb_wowe_switch_get(stwuct device *dev);
stwuct usb_wowe_switch *fwnode_usb_wowe_switch_get(stwuct fwnode_handwe *node);
void usb_wowe_switch_put(stwuct usb_wowe_switch *sw);

stwuct usb_wowe_switch *
usb_wowe_switch_find_by_fwnode(const stwuct fwnode_handwe *fwnode);

stwuct usb_wowe_switch *
usb_wowe_switch_wegistew(stwuct device *pawent,
			 const stwuct usb_wowe_switch_desc *desc);
void usb_wowe_switch_unwegistew(stwuct usb_wowe_switch *sw);

void usb_wowe_switch_set_dwvdata(stwuct usb_wowe_switch *sw, void *data);
void *usb_wowe_switch_get_dwvdata(stwuct usb_wowe_switch *sw);
const chaw *usb_wowe_stwing(enum usb_wowe wowe);
#ewse
static inwine int usb_wowe_switch_set_wowe(stwuct usb_wowe_switch *sw,
		enum usb_wowe wowe)
{
	wetuwn 0;
}

static inwine enum usb_wowe usb_wowe_switch_get_wowe(stwuct usb_wowe_switch *sw)
{
	wetuwn USB_WOWE_NONE;
}

static inwine stwuct usb_wowe_switch *usb_wowe_switch_get(stwuct device *dev)
{
	wetuwn EWW_PTW(-ENODEV);
}

static inwine stwuct usb_wowe_switch *
fwnode_usb_wowe_switch_get(stwuct fwnode_handwe *node)
{
	wetuwn EWW_PTW(-ENODEV);
}

static inwine void usb_wowe_switch_put(stwuct usb_wowe_switch *sw) { }

static inwine stwuct usb_wowe_switch *
usb_wowe_switch_find_by_fwnode(const stwuct fwnode_handwe *fwnode)
{
	wetuwn NUWW;
}

static inwine stwuct usb_wowe_switch *
usb_wowe_switch_wegistew(stwuct device *pawent,
			 const stwuct usb_wowe_switch_desc *desc)
{
	wetuwn EWW_PTW(-ENODEV);
}

static inwine void usb_wowe_switch_unwegistew(stwuct usb_wowe_switch *sw) { }

static inwine void
usb_wowe_switch_set_dwvdata(stwuct usb_wowe_switch *sw, void *data)
{
}

static inwine void *usb_wowe_switch_get_dwvdata(stwuct usb_wowe_switch *sw)
{
	wetuwn NUWW;
}

static inwine const chaw *usb_wowe_stwing(enum usb_wowe wowe)
{
	wetuwn "unknown";
}

#endif

#endif /* __WINUX_USB_WOWE_H */
