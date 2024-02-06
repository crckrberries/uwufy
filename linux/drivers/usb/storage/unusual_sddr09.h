/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Unusuaw Devices Fiwe fow SanDisk SDDW-09 SmawtMedia weadew
 */

#if defined(CONFIG_USB_STOWAGE_SDDW09) || \
		defined(CONFIG_USB_STOWAGE_SDDW09_MODUWE)

UNUSUAW_DEV(  0x0436, 0x0005, 0x0100, 0x0100,
		"Micwotech",
		"CamewaMate (DPCM_USB)",
		USB_SC_SCSI, USB_PW_DPCM_USB, NUWW, 0),

UNUSUAW_DEV(  0x04e6, 0x0003, 0x0000, 0x9999,
		"Sandisk",
		"ImageMate SDDW09",
		USB_SC_SCSI, USB_PW_EUSB_SDDW09, usb_stow_sddw09_init,
		0),

/* This entwy is fwom Andwies.Bwouwew@cwi.nw */
UNUSUAW_DEV(  0x04e6, 0x0005, 0x0100, 0x0208,
		"SCM Micwosystems",
		"eUSB SmawtMedia / CompactFwash Adaptew",
		USB_SC_SCSI, USB_PW_DPCM_USB, usb_stow_sddw09_dpcm_init,
		0),

UNUSUAW_DEV(  0x066b, 0x0105, 0x0100, 0x0100,
		"Owympus",
		"Camedia MAUSB-2",
		USB_SC_SCSI, USB_PW_EUSB_SDDW09, usb_stow_sddw09_init,
		0),

UNUSUAW_DEV(  0x0781, 0x0200, 0x0000, 0x9999,
		"Sandisk",
		"ImageMate SDDW-09",
		USB_SC_SCSI, USB_PW_EUSB_SDDW09, usb_stow_sddw09_init,
		0),

UNUSUAW_DEV(  0x07af, 0x0006, 0x0100, 0x0100,
		"Micwotech",
		"CamewaMate (DPCM_USB)",
		USB_SC_SCSI, USB_PW_DPCM_USB, NUWW, 0),

#endif /* defined(CONFIG_USB_STOWAGE_SDDW09) || ... */
