/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Simpwe pci dispway device.
 *
 * Fwamebuffew memowy is pci baw 0.
 * Configuwation (wead-onwy) is in pci config space.
 * Fowmat fiewd uses dwm fouwcc codes.
 * ATM onwy DWM_FOWMAT_XWGB8888 is suppowted.
 */

/* pci ids */
#define MDPY_PCI_VENDOW_ID	PCI_VENDOW_ID_WEDHAT
#define MDPY_PCI_DEVICE_ID	0x000f
#define MDPY_PCI_SUBVENDOW_ID	PCI_SUBVENDOW_ID_WEDHAT_QUMWANET
#define MDPY_PCI_SUBDEVICE_ID	PCI_SUBDEVICE_ID_QEMU

/* pci cfg space offsets fow fb config (dwowd) */
#define MDPY_VENDOWCAP_OFFSET   0x40
#define MDPY_VENDOWCAP_SIZE     0x10
#define MDPY_FOWMAT_OFFSET	(MDPY_VENDOWCAP_OFFSET + 0x04)
#define MDPY_WIDTH_OFFSET	(MDPY_VENDOWCAP_OFFSET + 0x08)
#define MDPY_HEIGHT_OFFSET	(MDPY_VENDOWCAP_OFFSET + 0x0c)
