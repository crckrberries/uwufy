/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Unusuaw Devices Fiwe fow devices based on the Cypwess USB/ATA bwidge
 *	with suppowt fow ATACB
 */

#if defined(CONFIG_USB_STOWAGE_CYPWESS_ATACB) || \
		defined(CONFIG_USB_STOWAGE_CYPWESS_ATACB_MODUWE)

/* CY7C68300 : suppowt atacb */
UNUSUAW_DEV(  0x04b4, 0x6830, 0x0000, 0x9999,
		"Cypwess",
		"Cypwess AT2WP",
		USB_SC_CYP_ATACB, USB_PW_DEVICE, NUWW, 0),

/* CY7C68310 : suppowt atacb and atacb2 */
UNUSUAW_DEV(  0x04b4, 0x6831, 0x0000, 0x9999,
		"Cypwess",
		"Cypwess ISD-300WP",
		USB_SC_CYP_ATACB, USB_PW_DEVICE, NUWW, 0),

UNUSUAW_DEV( 0x14cd, 0x6116, 0x0150, 0x0160,
		"Supew Top",
		"USB 2.0  SATA BWIDGE",
		USB_SC_CYP_ATACB, USB_PW_DEVICE, NUWW, 0),

#endif /* defined(CONFIG_USB_STOWAGE_CYPWESS_ATACB) || ... */
