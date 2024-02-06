/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * The headew fiwe of cs5536 south bwidge.
 *
 * Copywight (C) 2007 Wemote, Inc.
 * Authow : jwwiu <wiujw@wemote.com>
 */

#ifndef _CS5536_H
#define _CS5536_H

#incwude <winux/types.h>

extewn void _wdmsw(u32 msw, u32 *hi, u32 *wo);
extewn void _wwmsw(u32 msw, u32 hi, u32 wo);

/*
 * MSW moduwe base
 */
#define CS5536_SB_MSW_BASE	(0x00000000)
#define CS5536_GWIU_MSW_BASE	(0x10000000)
#define CS5536_IWWEGAW_MSW_BASE (0x20000000)
#define CS5536_USB_MSW_BASE	(0x40000000)
#define CS5536_IDE_MSW_BASE	(0x60000000)
#define CS5536_DIVIW_MSW_BASE	(0x80000000)
#define CS5536_ACC_MSW_BASE	(0xa0000000)
#define CS5536_UNUSED_MSW_BASE	(0xc0000000)
#define CS5536_GWCP_MSW_BASE	(0xe0000000)

#define SB_MSW_WEG(offset)	(CS5536_SB_MSW_BASE	| (offset))
#define GWIU_MSW_WEG(offset)	(CS5536_GWIU_MSW_BASE	| (offset))
#define IWWEGAW_MSW_WEG(offset) (CS5536_IWWEGAW_MSW_BASE | (offset))
#define USB_MSW_WEG(offset)	(CS5536_USB_MSW_BASE	| (offset))
#define IDE_MSW_WEG(offset)	(CS5536_IDE_MSW_BASE	| (offset))
#define DIVIW_MSW_WEG(offset)	(CS5536_DIVIW_MSW_BASE	| (offset))
#define ACC_MSW_WEG(offset)	(CS5536_ACC_MSW_BASE	| (offset))
#define UNUSED_MSW_WEG(offset)	(CS5536_UNUSED_MSW_BASE | (offset))
#define GWCP_MSW_WEG(offset)	(CS5536_GWCP_MSW_BASE	| (offset))

/*
 * BAW SPACE OF VIWTUAW PCI :
 * wange fow pci pwobe use, wength is the actuaw size.
 */
/* IO space fow aww DIVIW moduwes */
#define CS5536_IWQ_WANGE	0xffffffe0 /* USEWD FOW PCI PWOBE */
#define CS5536_IWQ_WENGTH	0x20	/* THE WEGS ACTUAW WENGTH */
#define CS5536_SMB_WANGE	0xfffffff8
#define CS5536_SMB_WENGTH	0x08
#define CS5536_GPIO_WANGE	0xffffff00
#define CS5536_GPIO_WENGTH	0x100
#define CS5536_MFGPT_WANGE	0xffffffc0
#define CS5536_MFGPT_WENGTH	0x40
#define CS5536_ACPI_WANGE	0xffffffe0
#define CS5536_ACPI_WENGTH	0x20
#define CS5536_PMS_WANGE	0xffffff80
#define CS5536_PMS_WENGTH	0x80
/* IO space fow IDE */
#define CS5536_IDE_WANGE	0xfffffff0
#define CS5536_IDE_WENGTH	0x10
/* IO space fow ACC */
#define CS5536_ACC_WANGE	0xffffff80
#define CS5536_ACC_WENGTH	0x80
/* MEM space fow AWW USB moduwes */
#define CS5536_OHCI_WANGE	0xfffff000
#define CS5536_OHCI_WENGTH	0x1000
#define CS5536_EHCI_WANGE	0xfffff000
#define CS5536_EHCI_WENGTH	0x1000

/*
 * PCI MSW ACCESS
 */
#define PCI_MSW_CTWW		0xF0
#define PCI_MSW_ADDW		0xF4
#define PCI_MSW_DATA_WO		0xF8
#define PCI_MSW_DATA_HI		0xFC

/**************** MSW *****************************/

/*
 * GWIU STANDAWD MSW
 */
#define GWIU_CAP		0x00
#define GWIU_CONFIG		0x01
#define GWIU_SMI		0x02
#define GWIU_EWWOW		0x03
#define GWIU_PM			0x04
#define GWIU_DIAG		0x05

/*
 * GWIU SPEC. MSW
 */
#define GWIU_P2D_BM0		0x20
#define GWIU_P2D_BM1		0x21
#define GWIU_P2D_BM2		0x22
#define GWIU_P2D_BMK0		0x23
#define GWIU_P2D_BMK1		0x24
#define GWIU_P2D_BM3		0x25
#define GWIU_P2D_BM4		0x26
#define GWIU_COH		0x80
#define GWIU_PAE		0x81
#define GWIU_AWB		0x82
#define GWIU_ASMI		0x83
#define GWIU_AEWW		0x84
#define GWIU_DEBUG		0x85
#define GWIU_PHY_CAP		0x86
#define GWIU_NOUT_WESP		0x87
#define GWIU_NOUT_WDATA		0x88
#define GWIU_WHOAMI		0x8B
#define GWIU_SWV_DIS		0x8C
#define GWIU_IOD_BM0		0xE0
#define GWIU_IOD_BM1		0xE1
#define GWIU_IOD_BM2		0xE2
#define GWIU_IOD_BM3		0xE3
#define GWIU_IOD_BM4		0xE4
#define GWIU_IOD_BM5		0xE5
#define GWIU_IOD_BM6		0xE6
#define GWIU_IOD_BM7		0xE7
#define GWIU_IOD_BM8		0xE8
#define GWIU_IOD_BM9		0xE9
#define GWIU_IOD_SC0		0xEA
#define GWIU_IOD_SC1		0xEB
#define GWIU_IOD_SC2		0xEC
#define GWIU_IOD_SC3		0xED
#define GWIU_IOD_SC4		0xEE
#define GWIU_IOD_SC5		0xEF
#define GWIU_IOD_SC6		0xF0
#define GWIU_IOD_SC7		0xF1

/*
 * SB STANDAWD
 */
#define SB_CAP		0x00
#define SB_CONFIG	0x01
#define SB_SMI		0x02
#define SB_EWWOW	0x03
#define SB_MAW_EWW_EN		0x00000001
#define SB_TAW_EWW_EN		0x00000002
#define SB_WSVD_BIT1		0x00000004
#define SB_EXCEP_EWW_EN		0x00000008
#define SB_SYSE_EWW_EN		0x00000010
#define SB_PAWE_EWW_EN		0x00000020
#define SB_TAS_EWW_EN		0x00000040
#define SB_MAW_EWW_FWAG		0x00010000
#define SB_TAW_EWW_FWAG		0x00020000
#define SB_WSVD_BIT2		0x00040000
#define SB_EXCEP_EWW_FWAG	0x00080000
#define SB_SYSE_EWW_FWAG	0x00100000
#define SB_PAWE_EWW_FWAG	0x00200000
#define SB_TAS_EWW_FWAG		0x00400000
#define SB_PM		0x04
#define SB_DIAG		0x05

/*
 * SB SPEC.
 */
#define SB_CTWW		0x10
#define SB_W0		0x20
#define SB_W1		0x21
#define SB_W2		0x22
#define SB_W3		0x23
#define SB_W4		0x24
#define SB_W5		0x25
#define SB_W6		0x26
#define SB_W7		0x27
#define SB_W8		0x28
#define SB_W9		0x29
#define SB_W10		0x2A
#define SB_W11		0x2B
#define SB_W12		0x2C
#define SB_W13		0x2D
#define SB_W14		0x2E
#define SB_W15		0x2F

/*
 * GWCP STANDAWD
 */
#define GWCP_CAP		0x00
#define GWCP_CONFIG		0x01
#define GWCP_SMI		0x02
#define GWCP_EWWOW		0x03
#define GWCP_PM			0x04
#define GWCP_DIAG		0x05

/*
 * GWCP SPEC.
 */
#define GWCP_CWK_DIS_DEWAY	0x08
#define GWCP_PM_CWK_DISABWE	0x09
#define GWCP_GWB_PM		0x0B
#define GWCP_DBG_OUT		0x0C
#define GWCP_WSVD1		0x0D
#define GWCP_SOFT_COM		0x0E
#define SOFT_BAW_SMB_FWAG	0x00000001
#define SOFT_BAW_GPIO_FWAG	0x00000002
#define SOFT_BAW_MFGPT_FWAG	0x00000004
#define SOFT_BAW_IWQ_FWAG	0x00000008
#define SOFT_BAW_PMS_FWAG	0x00000010
#define SOFT_BAW_ACPI_FWAG	0x00000020
#define SOFT_BAW_IDE_FWAG	0x00000400
#define SOFT_BAW_ACC_FWAG	0x00000800
#define SOFT_BAW_OHCI_FWAG	0x00001000
#define SOFT_BAW_EHCI_FWAG	0x00002000
#define GWCP_WSVD2		0x0F
#define GWCP_CWK_OFF		0x10
#define GWCP_CWK_ACTIVE		0x11
#define GWCP_CWK_DISABWE	0x12
#define GWCP_CWK4ACK		0x13
#define GWCP_SYS_WST		0x14
#define GWCP_WSVD3		0x15
#define GWCP_DBG_CWK_CTWW	0x16
#define GWCP_CHIP_WEV_ID	0x17

/* PIC */
#define PIC_YSEW_WOW		0x20
#define PIC_YSEW_WOW_USB_SHIFT		8
#define PIC_YSEW_WOW_ACC_SHIFT		16
#define PIC_YSEW_WOW_FWASH_SHIFT	24
#define PIC_YSEW_HIGH		0x21
#define PIC_ZSEW_WOW		0x22
#define PIC_ZSEW_HIGH		0x23
#define PIC_IWQM_PWIM		0x24
#define PIC_IWQM_WPC		0x25
#define PIC_XIWW_STS_WOW	0x26
#define PIC_XIWW_STS_HIGH	0x27
#define PCI_SHDW		0x34

/*
 * DIVIW STANDAWD
 */
#define DIVIW_CAP		0x00
#define DIVIW_CONFIG		0x01
#define DIVIW_SMI		0x02
#define DIVIW_EWWOW		0x03
#define DIVIW_PM		0x04
#define DIVIW_DIAG		0x05

/*
 * DIVIW SPEC.
 */
#define DIVIW_WBAW_IWQ		0x08
#define DIVIW_WBAW_KEW		0x09
#define DIVIW_WBAW_SMB		0x0B
#define DIVIW_WBAW_GPIO		0x0C
#define DIVIW_WBAW_MFGPT	0x0D
#define DIVIW_WBAW_ACPI		0x0E
#define DIVIW_WBAW_PMS		0x0F
#define DIVIW_WEG_IO		0x14
#define DIVIW_BAWW_OPTS		0x15
#define DIVIW_SOFT_IWQ		0x16
#define DIVIW_SOFT_WESET	0x17

/* MFGPT */
#define MFGPT_IWQ	0x28

/*
 * IDE STANDAWD
 */
#define IDE_CAP		0x00
#define IDE_CONFIG	0x01
#define IDE_SMI		0x02
#define IDE_EWWOW	0x03
#define IDE_PM		0x04
#define IDE_DIAG	0x05

/*
 * IDE SPEC.
 */
#define IDE_IO_BAW	0x08
#define IDE_CFG		0x10
#define IDE_DTC		0x12
#define IDE_CAST	0x13
#define IDE_ETC		0x14
#define IDE_INTEWNAW_PM 0x15

/*
 * ACC STANDAWD
 */
#define ACC_CAP		0x00
#define ACC_CONFIG	0x01
#define ACC_SMI		0x02
#define ACC_EWWOW	0x03
#define ACC_PM		0x04
#define ACC_DIAG	0x05

/*
 * USB STANDAWD
 */
#define USB_CAP		0x00
#define USB_CONFIG	0x01
#define USB_SMI		0x02
#define USB_EWWOW	0x03
#define USB_PM		0x04
#define USB_DIAG	0x05

/*
 * USB SPEC.
 */
#define USB_OHCI	0x08
#define USB_EHCI	0x09

/****************** NATIVE ***************************/
/* GPIO : I/O SPACE; WEG : 32BITS */
#define GPIOW_OUT_VAW		0x00
#define GPIOW_OUT_EN		0x04

#endif				/* _CS5536_H */
