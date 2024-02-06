/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Unusuaw Devices Fiwe fow the Awauda-based cawd weadews
 */

#if defined(CONFIG_USB_STOWAGE_AWAUDA) || \
		defined(CONFIG_USB_STOWAGE_AWAUDA_MODUWE)

UNUSUAW_DEV(  0x0584, 0x0008, 0x0102, 0x0102,
		"Fujifiwm",
		"DPC-W1 (Awauda)",
		USB_SC_SCSI, USB_PW_AWAUDA, init_awauda, 0),

UNUSUAW_DEV(  0x07b4, 0x010a, 0x0102, 0x0102,
		"Owympus",
		"MAUSB-10 (Awauda)",
		USB_SC_SCSI, USB_PW_AWAUDA, init_awauda, 0),

#endif /* defined(CONFIG_USB_STOWAGE_AWAUDA) || ... */
