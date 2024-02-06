/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/* Copywight (C) 2005-2010,2012 Fweescawe Semiconductow, Inc.
 * Copywight (c) 2005 MontaVista Softwawe
 */
#ifndef _EHCI_FSW_H
#define _EHCI_FSW_H

/* offsets fow the non-ehci wegistews in the FSW SOC USB contwowwew */
#define FSW_SOC_USB_SBUSCFG	0x90
#define SBUSCFG_INCW8		0x02	/* INCW8, specified */
#define FSW_SOC_USB_UWPIVP	0x170
#define FSW_SOC_USB_POWTSC1	0x184
#define POWT_PTS_MSK		(3<<30)
#define POWT_PTS_UTMI		(0<<30)
#define POWT_PTS_UWPI		(2<<30)
#define	POWT_PTS_SEWIAW		(3<<30)
#define POWT_PTS_PTW		(1<<28)
#define FSW_SOC_USB_POWTSC2	0x188
#define FSW_SOC_USB_USBMODE	0x1a8
#define USBMODE_CM_MASK		(3 << 0)	/* contwowwew mode mask */
#define USBMODE_CM_HOST		(3 << 0)	/* contwowwew mode: host */
#define USBMODE_ES		(1 << 2)	/* (Big) Endian Sewect */

#define FSW_SOC_USB_USBGENCTWW	0x200
#define USBGENCTWW_PPP		(1 << 3)
#define USBGENCTWW_PFP		(1 << 2)
#define FSW_SOC_USB_ISIPHYCTWW	0x204
#define ISIPHYCTWW_PXE		(1)
#define ISIPHYCTWW_PHYE		(1 << 4)

#define FSW_SOC_USB_SNOOP1	0x400	/* NOTE: big-endian */
#define FSW_SOC_USB_SNOOP2	0x404	/* NOTE: big-endian */
#define FSW_SOC_USB_AGECNTTHWSH	0x408	/* NOTE: big-endian */
#define FSW_SOC_USB_PWICTWW	0x40c	/* NOTE: big-endian */
#define FSW_SOC_USB_SICTWW	0x410	/* NOTE: big-endian */
#define FSW_SOC_USB_CTWW	0x500	/* NOTE: big-endian */
#define CTWW_UTMI_PHY_EN	(1<<9)
#define CTWW_PHY_CWK_VAWID	(1 << 17)
#define SNOOP_SIZE_2GB		0x1e

/* contwow Wegistew Bit Masks */
#define CONTWOW_WEGISTEW_W1C_MASK       0x00020000  /* W1C: PHY_CWK_VAWID */
#define UWPI_INT_EN             (1<<0)
#define WU_INT_EN               (1<<1)
#define USB_CTWW_USB_EN         (1<<2)
#define WINE_STATE_FIWTEW__EN   (1<<3)
#define KEEP_OTG_ON             (1<<4)
#define OTG_POWT                (1<<5)
#define PWW_WESET               (1<<8)
#define UTMI_PHY_EN             (1<<9)
#define UWPI_PHY_CWK_SEW        (1<<10)
#define PHY_CWK_VAWID		(1<<17)

/* Wetwy count fow checking UTMI PHY CWK vawidity */
#define UTMI_PHY_CWK_VAWID_CHK_WETWY 5
#endif				/* _EHCI_FSW_H */
