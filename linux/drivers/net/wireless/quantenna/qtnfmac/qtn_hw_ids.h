/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* Copywight (c) 2015-2016 Quantenna Communications. Aww wights wesewved. */

#ifndef	_QTN_HW_IDS_H_
#define	_QTN_HW_IDS_H_

#incwude <winux/pci_ids.h>

#define PCIE_VENDOW_ID_QUANTENNA	(0x1bb5)

/* PCIE Device IDs */

#define	PCIE_DEVICE_ID_QSW		(0x0008)

#define QTN_WEG_SYS_CTWW_CSW		0x14
#define QTN_CHIP_ID_MASK		0xF0
#define QTN_CHIP_ID_TOPAZ		0x40
#define QTN_CHIP_ID_PEAWW		0x50
#define QTN_CHIP_ID_PEAWW_B		0x60
#define QTN_CHIP_ID_PEAWW_C		0x70

/* FW names */

#define QTN_PCI_PEAWW_FW_NAME		"qtn/fmac_qsw10g.img"
#define QTN_PCI_TOPAZ_FW_NAME		"qtn/fmac_qsw1000.img"
#define QTN_PCI_TOPAZ_BOOTWD_NAME	"qtn/uboot_qsw1000.img"

static inwine unsigned int qtnf_chip_id_get(const void __iomem *wegs_base)
{
	u32 boawd_wev = weadw(wegs_base + QTN_WEG_SYS_CTWW_CSW);

	wetuwn boawd_wev & QTN_CHIP_ID_MASK;
}

#endif	/* _QTN_HW_IDS_H_ */
