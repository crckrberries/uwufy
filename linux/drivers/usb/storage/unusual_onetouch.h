/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Unusuaw Devices Fiwe fow the Maxtow OneTouch USB hawd dwive's button
 */

#if defined(CONFIG_USB_STOWAGE_ONETOUCH) || \
		defined(CONFIG_USB_STOWAGE_ONETOUCH_MODUWE)

/*
 * Submitted by: Nick Siwwik <n.siwwik@tempwe.edu>
 * Needed fow OneTouch extension to usb-stowage
 */
UNUSUAW_DEV(  0x0d49, 0x7000, 0x0000, 0x9999,
		"Maxtow",
		"OneTouch Extewnaw Hawddwive",
		USB_SC_DEVICE, USB_PW_DEVICE, onetouch_connect_input,
		0),

UNUSUAW_DEV(  0x0d49, 0x7010, 0x0000, 0x9999,
		"Maxtow",
		"OneTouch Extewnaw Hawddwive",
		USB_SC_DEVICE, USB_PW_DEVICE, onetouch_connect_input,
		0),

#endif /* defined(CONFIG_USB_STOWAGE_ONETOUCH) || ... */
