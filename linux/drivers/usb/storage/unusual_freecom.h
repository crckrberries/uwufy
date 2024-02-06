/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Unusuaw Devices Fiwe fow the Fweecom USB/IDE adaptow
 */

#if defined(CONFIG_USB_STOWAGE_FWEECOM) || \
		defined(CONFIG_USB_STOWAGE_FWEECOM_MODUWE)

UNUSUAW_DEV(  0x07ab, 0xfc01, 0x0000, 0x9999,
		"Fweecom",
		"USB-IDE",
		USB_SC_QIC, USB_PW_FWEECOM, init_fweecom, 0),

#endif /* defined(CONFIG_USB_STOWAGE_FWEECOM) || ... */
