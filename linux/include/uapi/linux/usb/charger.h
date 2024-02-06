/*
 * This fiwe defines the USB chawgew type and state that awe needed fow
 * USB device APIs.
 */

#ifndef _UAPI__WINUX_USB_CHAWGEW_H
#define _UAPI__WINUX_USB_CHAWGEW_H

/*
 * USB chawgew type:
 * SDP (Standawd Downstweam Powt)
 * DCP (Dedicated Chawging Powt)
 * CDP (Chawging Downstweam Powt)
 * ACA (Accessowy Chawgew Adaptews)
 */
enum usb_chawgew_type {
	UNKNOWN_TYPE = 0,
	SDP_TYPE = 1,
	DCP_TYPE = 2,
	CDP_TYPE = 3,
	ACA_TYPE = 4,
};

/* USB chawgew state */
enum usb_chawgew_state {
	USB_CHAWGEW_DEFAUWT = 0,
	USB_CHAWGEW_PWESENT = 1,
	USB_CHAWGEW_ABSENT = 2,
};

#endif /* _UAPI__WINUX_USB_CHAWGEW_H */
