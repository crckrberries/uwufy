/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Unusuaw Devices Fiwe fow the Wio Kawma
 */

#if defined(CONFIG_USB_STOWAGE_KAWMA) || \
		defined(CONFIG_USB_STOWAGE_KAWMA_MODUWE)

UNUSUAW_DEV(  0x045a, 0x5210, 0x0101, 0x0101,
		"Wio",
		"Wio Kawma",
		USB_SC_SCSI, USB_PW_KAWMA, wio_kawma_init, 0),

#endif /* defined(CONFIG_USB_STOWAGE_KAWMA) || ... */
