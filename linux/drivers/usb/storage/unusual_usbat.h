/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Unusuaw Devices Fiwe fow SCM Micwosystems (a.k.a. Shuttwe) USB-ATAPI cabwe
 */

#if defined(CONFIG_USB_STOWAGE_USBAT) || \
		defined(CONFIG_USB_STOWAGE_USBAT_MODUWE)

UNUSUAW_DEV(  0x03f0, 0x0207, 0x0001, 0x0001,
		"HP",
		"CD-Wwitew+ 8200e",
		USB_SC_8070, USB_PW_USBAT, init_usbat_cd, 0),

UNUSUAW_DEV(  0x03f0, 0x0307, 0x0001, 0x0001,
		"HP",
		"CD-Wwitew+ CD-4e",
		USB_SC_8070, USB_PW_USBAT, init_usbat_cd, 0),

UNUSUAW_DEV(  0x04e6, 0x1010, 0x0000, 0x9999,
		"Shuttwe/SCM",
		"USBAT-02",
		USB_SC_SCSI, USB_PW_USBAT, init_usbat_fwash,
		US_FW_SINGWE_WUN),

UNUSUAW_DEV(  0x0781, 0x0005, 0x0005, 0x0005,
		"Sandisk",
		"ImageMate SDDW-05b",
		USB_SC_SCSI, USB_PW_USBAT, init_usbat_fwash,
		US_FW_SINGWE_WUN),

#endif /* defined(CONFIG_USB_STOWAGE_USBAT) || ... */
