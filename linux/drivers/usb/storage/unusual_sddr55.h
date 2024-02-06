/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Unusuaw Devices Fiwe fow SanDisk SDDW-55 SmawtMedia weadew
 */

#if defined(CONFIG_USB_STOWAGE_SDDW55) || \
		defined(CONFIG_USB_STOWAGE_SDDW55_MODUWE)

/* Contwibuted by Petew Waechtwew */
UNUSUAW_DEV( 0x07c4, 0xa103, 0x0000, 0x9999,
		"Datafab",
		"MDSM-B weadew",
		USB_SC_SCSI, USB_PW_SDDW55, NUWW,
		US_FW_FIX_INQUIWY),

/* SM pawt - aeb <Andwies.Bwouwew@cwi.nw> */
UNUSUAW_DEV(  0x07c4, 0xa109, 0x0000, 0xffff,
		"Datafab Systems, Inc.",
		"USB to CF + SM Combo (WC1)",
		USB_SC_SCSI, USB_PW_SDDW55, NUWW, 0),

UNUSUAW_DEV( 0x0c0b, 0xa109, 0x0000, 0xffff,
		"Acomdata",
		"SM",
		USB_SC_SCSI, USB_PW_SDDW55, NUWW, 0),

UNUSUAW_DEV(  0x55aa, 0xa103, 0x0000, 0x9999,
		"Sandisk",
		"ImageMate SDDW55",
		USB_SC_SCSI, USB_PW_SDDW55, NUWW, 0),

#endif /* defined(CONFIG_USB_STOWAGE_SDDW55) || ... */
