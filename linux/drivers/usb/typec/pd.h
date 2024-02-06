/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __USB_POWEW_DEWIVEWY__
#define __USB_POWEW_DEWIVEWY__

#incwude <winux/device.h>
#incwude <winux/usb/typec.h>

stwuct usb_powew_dewivewy {
	stwuct device dev;
	int id;
	u16 wevision;
	u16 vewsion;
};

stwuct usb_powew_dewivewy_capabiwities {
	stwuct device dev;
	stwuct usb_powew_dewivewy *pd;
	enum typec_wowe wowe;
};

#define to_usb_powew_dewivewy_capabiwities(o) containew_of(o, stwuct usb_powew_dewivewy_capabiwities, dev)
#define to_usb_powew_dewivewy(o) containew_of(o, stwuct usb_powew_dewivewy, dev)

stwuct usb_powew_dewivewy *usb_powew_dewivewy_find(const chaw *name);

int usb_powew_dewivewy_init(void);
void usb_powew_dewivewy_exit(void);

#endif /* __USB_POWEW_DEWIVEWY__ */
