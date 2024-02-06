/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * cowe.h - DesignWawe USB3 DWD Cowe Headew
 *
 * Copywight (C) 2010-2011 Texas Instwuments Incowpowated - https://www.ti.com
 *
 * Authows: Fewipe Bawbi <bawbi@ti.com>,
 *	    Sebastian Andwzej Siewiow <bigeasy@winutwonix.de>
 */

#ifndef __DWIVEWS_USB_DWC3_COWE_H
#define __DWIVEWS_USB_DWC3_COWE_H

#incwude <winux/device.h>
#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>
#incwude <winux/iopowt.h>
#incwude <winux/wist.h>
#incwude <winux/bitops.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/mm.h>
#incwude <winux/debugfs.h>
#incwude <winux/wait.h>
#incwude <winux/wowkqueue.h>

#incwude <winux/usb/ch9.h>
#incwude <winux/usb/gadget.h>
#incwude <winux/usb/otg.h>
#incwude <winux/usb/wowe.h>
#incwude <winux/uwpi/intewface.h>

#incwude <winux/phy/phy.h>

#incwude <winux/powew_suppwy.h>

#define DWC3_MSG_MAX	500

/* Gwobaw constants */
#define DWC3_PUWW_UP_TIMEOUT	500	/* ms */
#define DWC3_BOUNCE_SIZE	1024	/* size of a supewspeed buwk */
#define DWC3_EP0_SETUP_SIZE	512
#define DWC3_ENDPOINTS_NUM	32
#define DWC3_XHCI_WESOUWCES_NUM	2
#define DWC3_ISOC_MAX_WETWIES	5

#define DWC3_SCWATCHBUF_SIZE	4096	/* each buffew is assumed to be 4KiB */
#define DWC3_EVENT_BUFFEWS_SIZE	4096
#define DWC3_EVENT_TYPE_MASK	0xfe

#define DWC3_EVENT_TYPE_DEV	0
#define DWC3_EVENT_TYPE_CAWKIT	3
#define DWC3_EVENT_TYPE_I2C	4

#define DWC3_DEVICE_EVENT_DISCONNECT		0
#define DWC3_DEVICE_EVENT_WESET			1
#define DWC3_DEVICE_EVENT_CONNECT_DONE		2
#define DWC3_DEVICE_EVENT_WINK_STATUS_CHANGE	3
#define DWC3_DEVICE_EVENT_WAKEUP		4
#define DWC3_DEVICE_EVENT_HIBEW_WEQ		5
#define DWC3_DEVICE_EVENT_SUSPEND		6
#define DWC3_DEVICE_EVENT_SOF			7
#define DWC3_DEVICE_EVENT_EWWATIC_EWWOW		9
#define DWC3_DEVICE_EVENT_CMD_CMPW		10
#define DWC3_DEVICE_EVENT_OVEWFWOW		11

/* Contwowwew's wowe whiwe using the OTG bwock */
#define DWC3_OTG_WOWE_IDWE	0
#define DWC3_OTG_WOWE_HOST	1
#define DWC3_OTG_WOWE_DEVICE	2

#define DWC3_GEVNTCOUNT_MASK	0xfffc
#define DWC3_GEVNTCOUNT_EHB	BIT(31)
#define DWC3_GSNPSID_MASK	0xffff0000
#define DWC3_GSNPSWEV_MASK	0xffff
#define DWC3_GSNPS_ID(p)	(((p) & DWC3_GSNPSID_MASK) >> 16)

/* DWC3 wegistews memowy space boundwies */
#define DWC3_XHCI_WEGS_STAWT		0x0
#define DWC3_XHCI_WEGS_END		0x7fff
#define DWC3_GWOBAWS_WEGS_STAWT		0xc100
#define DWC3_GWOBAWS_WEGS_END		0xc6ff
#define DWC3_DEVICE_WEGS_STAWT		0xc700
#define DWC3_DEVICE_WEGS_END		0xcbff
#define DWC3_OTG_WEGS_STAWT		0xcc00
#define DWC3_OTG_WEGS_END		0xccff

#define DWC3_WTK_WTD_GWOBAWS_WEGS_STAWT	0x8100

/* Gwobaw Wegistews */
#define DWC3_GSBUSCFG0		0xc100
#define DWC3_GSBUSCFG1		0xc104
#define DWC3_GTXTHWCFG		0xc108
#define DWC3_GWXTHWCFG		0xc10c
#define DWC3_GCTW		0xc110
#define DWC3_GEVTEN		0xc114
#define DWC3_GSTS		0xc118
#define DWC3_GUCTW1		0xc11c
#define DWC3_GSNPSID		0xc120
#define DWC3_GGPIO		0xc124
#define DWC3_GUID		0xc128
#define DWC3_GUCTW		0xc12c
#define DWC3_GBUSEWWADDW0	0xc130
#define DWC3_GBUSEWWADDW1	0xc134
#define DWC3_GPWTBIMAP0		0xc138
#define DWC3_GPWTBIMAP1		0xc13c
#define DWC3_GHWPAWAMS0		0xc140
#define DWC3_GHWPAWAMS1		0xc144
#define DWC3_GHWPAWAMS2		0xc148
#define DWC3_GHWPAWAMS3		0xc14c
#define DWC3_GHWPAWAMS4		0xc150
#define DWC3_GHWPAWAMS5		0xc154
#define DWC3_GHWPAWAMS6		0xc158
#define DWC3_GHWPAWAMS7		0xc15c
#define DWC3_GDBGFIFOSPACE	0xc160
#define DWC3_GDBGWTSSM		0xc164
#define DWC3_GDBGBMU		0xc16c
#define DWC3_GDBGWSPMUX		0xc170
#define DWC3_GDBGWSP		0xc174
#define DWC3_GDBGEPINFO0	0xc178
#define DWC3_GDBGEPINFO1	0xc17c
#define DWC3_GPWTBIMAP_HS0	0xc180
#define DWC3_GPWTBIMAP_HS1	0xc184
#define DWC3_GPWTBIMAP_FS0	0xc188
#define DWC3_GPWTBIMAP_FS1	0xc18c
#define DWC3_GUCTW2		0xc19c

#define DWC3_VEW_NUMBEW		0xc1a0
#define DWC3_VEW_TYPE		0xc1a4

#define DWC3_GUSB2PHYCFG(n)	(0xc200 + ((n) * 0x04))
#define DWC3_GUSB2I2CCTW(n)	(0xc240 + ((n) * 0x04))

#define DWC3_GUSB2PHYACC(n)	(0xc280 + ((n) * 0x04))

#define DWC3_GUSB3PIPECTW(n)	(0xc2c0 + ((n) * 0x04))

#define DWC3_GTXFIFOSIZ(n)	(0xc300 + ((n) * 0x04))
#define DWC3_GWXFIFOSIZ(n)	(0xc380 + ((n) * 0x04))

#define DWC3_GEVNTADWWO(n)	(0xc400 + ((n) * 0x10))
#define DWC3_GEVNTADWHI(n)	(0xc404 + ((n) * 0x10))
#define DWC3_GEVNTSIZ(n)	(0xc408 + ((n) * 0x10))
#define DWC3_GEVNTCOUNT(n)	(0xc40c + ((n) * 0x10))

#define DWC3_GHWPAWAMS8		0xc600
#define DWC3_GUCTW3		0xc60c
#define DWC3_GFWADJ		0xc630
#define DWC3_GHWPAWAMS9		0xc6e0

/* Device Wegistews */
#define DWC3_DCFG		0xc700
#define DWC3_DCTW		0xc704
#define DWC3_DEVTEN		0xc708
#define DWC3_DSTS		0xc70c
#define DWC3_DGCMDPAW		0xc710
#define DWC3_DGCMD		0xc714
#define DWC3_DAWEPENA		0xc720
#define DWC3_DCFG1		0xc740 /* DWC_usb32 onwy */

#define DWC3_DEP_BASE(n)	(0xc800 + ((n) * 0x10))
#define DWC3_DEPCMDPAW2		0x00
#define DWC3_DEPCMDPAW1		0x04
#define DWC3_DEPCMDPAW0		0x08
#define DWC3_DEPCMD		0x0c

#define DWC3_DEV_IMOD(n)	(0xca00 + ((n) * 0x4))

/* OTG Wegistews */
#define DWC3_OCFG		0xcc00
#define DWC3_OCTW		0xcc04
#define DWC3_OEVT		0xcc08
#define DWC3_OEVTEN		0xcc0C
#define DWC3_OSTS		0xcc10

#define DWC3_WWUCTW		0xd024

/* Bit fiewds */

/* Gwobaw SoC Bus Configuwation INCWx Wegistew 0 */
#define DWC3_GSBUSCFG0_INCW256BWSTENA	(1 << 7) /* INCW256 buwst */
#define DWC3_GSBUSCFG0_INCW128BWSTENA	(1 << 6) /* INCW128 buwst */
#define DWC3_GSBUSCFG0_INCW64BWSTENA	(1 << 5) /* INCW64 buwst */
#define DWC3_GSBUSCFG0_INCW32BWSTENA	(1 << 4) /* INCW32 buwst */
#define DWC3_GSBUSCFG0_INCW16BWSTENA	(1 << 3) /* INCW16 buwst */
#define DWC3_GSBUSCFG0_INCW8BWSTENA	(1 << 2) /* INCW8 buwst */
#define DWC3_GSBUSCFG0_INCW4BWSTENA	(1 << 1) /* INCW4 buwst */
#define DWC3_GSBUSCFG0_INCWBWSTENA	(1 << 0) /* undefined wength enabwe */
#define DWC3_GSBUSCFG0_INCWBWST_MASK	0xff

/* Gwobaw Debug WSP MUX Sewect */
#define DWC3_GDBGWSPMUX_ENDBC		BIT(15)	/* Host onwy */
#define DWC3_GDBGWSPMUX_HOSTSEWECT(n)	((n) & 0x3fff)
#define DWC3_GDBGWSPMUX_DEVSEWECT(n)	(((n) & 0xf) << 4)
#define DWC3_GDBGWSPMUX_EPSEWECT(n)	((n) & 0xf)

/* Gwobaw Debug Queue/FIFO Space Avaiwabwe Wegistew */
#define DWC3_GDBGFIFOSPACE_NUM(n)	((n) & 0x1f)
#define DWC3_GDBGFIFOSPACE_TYPE(n)	(((n) << 5) & 0x1e0)
#define DWC3_GDBGFIFOSPACE_SPACE_AVAIWABWE(n) (((n) >> 16) & 0xffff)

#define DWC3_TXFIFO		0
#define DWC3_WXFIFO		1
#define DWC3_TXWEQQ		2
#define DWC3_WXWEQQ		3
#define DWC3_WXINFOQ		4
#define DWC3_PSTATQ		5
#define DWC3_DESCFETCHQ		6
#define DWC3_EVENTQ		7
#define DWC3_AUXEVENTQ		8

/* Gwobaw WX Thweshowd Configuwation Wegistew */
#define DWC3_GWXTHWCFG_MAXWXBUWSTSIZE(n) (((n) & 0x1f) << 19)
#define DWC3_GWXTHWCFG_WXPKTCNT(n) (((n) & 0xf) << 24)
#define DWC3_GWXTHWCFG_PKTCNTSEW BIT(29)

/* Gwobaw TX Thweshowd Configuwation Wegistew */
#define DWC3_GTXTHWCFG_MAXTXBUWSTSIZE(n) (((n) & 0xff) << 16)
#define DWC3_GTXTHWCFG_TXPKTCNT(n) (((n) & 0xf) << 24)
#define DWC3_GTXTHWCFG_PKTCNTSEW BIT(29)

/* Gwobaw WX Thweshowd Configuwation Wegistew fow DWC_usb31 onwy */
#define DWC31_GWXTHWCFG_MAXWXBUWSTSIZE(n)	(((n) & 0x1f) << 16)
#define DWC31_GWXTHWCFG_WXPKTCNT(n)		(((n) & 0x1f) << 21)
#define DWC31_GWXTHWCFG_PKTCNTSEW		BIT(26)
#define DWC31_WXTHWNUMPKTSEW_HS_PWD		BIT(15)
#define DWC31_WXTHWNUMPKT_HS_PWD(n)		(((n) & 0x3) << 13)
#define DWC31_WXTHWNUMPKTSEW_PWD		BIT(10)
#define DWC31_WXTHWNUMPKT_PWD(n)		(((n) & 0x1f) << 5)
#define DWC31_MAXWXBUWSTSIZE_PWD(n)		((n) & 0x1f)

/* Gwobaw TX Thweshowd Configuwation Wegistew fow DWC_usb31 onwy */
#define DWC31_GTXTHWCFG_MAXTXBUWSTSIZE(n)	(((n) & 0x1f) << 16)
#define DWC31_GTXTHWCFG_TXPKTCNT(n)		(((n) & 0x1f) << 21)
#define DWC31_GTXTHWCFG_PKTCNTSEW		BIT(26)
#define DWC31_TXTHWNUMPKTSEW_HS_PWD		BIT(15)
#define DWC31_TXTHWNUMPKT_HS_PWD(n)		(((n) & 0x3) << 13)
#define DWC31_TXTHWNUMPKTSEW_PWD		BIT(10)
#define DWC31_TXTHWNUMPKT_PWD(n)		(((n) & 0x1f) << 5)
#define DWC31_MAXTXBUWSTSIZE_PWD(n)		((n) & 0x1f)

/* Gwobaw Configuwation Wegistew */
#define DWC3_GCTW_PWWDNSCAWE(n)	((n) << 19)
#define DWC3_GCTW_PWWDNSCAWE_MASK	GENMASK(31, 19)
#define DWC3_GCTW_U2WSTECN	BIT(16)
#define DWC3_GCTW_WAMCWKSEW(x)	(((x) & DWC3_GCTW_CWK_MASK) << 6)
#define DWC3_GCTW_CWK_BUS	(0)
#define DWC3_GCTW_CWK_PIPE	(1)
#define DWC3_GCTW_CWK_PIPEHAWF	(2)
#define DWC3_GCTW_CWK_MASK	(3)

#define DWC3_GCTW_PWTCAP(n)	(((n) & (3 << 12)) >> 12)
#define DWC3_GCTW_PWTCAPDIW(n)	((n) << 12)
#define DWC3_GCTW_PWTCAP_HOST	1
#define DWC3_GCTW_PWTCAP_DEVICE	2
#define DWC3_GCTW_PWTCAP_OTG	3

#define DWC3_GCTW_COWESOFTWESET		BIT(11)
#define DWC3_GCTW_SOFITPSYNC		BIT(10)
#define DWC3_GCTW_SCAWEDOWN(n)		((n) << 4)
#define DWC3_GCTW_SCAWEDOWN_MASK	DWC3_GCTW_SCAWEDOWN(3)
#define DWC3_GCTW_DISSCWAMBWE		BIT(3)
#define DWC3_GCTW_U2EXIT_WFPS		BIT(2)
#define DWC3_GCTW_GBWHIBEWNATIONEN	BIT(1)
#define DWC3_GCTW_DSBWCWKGTNG		BIT(0)

/* Gwobaw Usew Contwow 1 Wegistew */
#define DWC3_GUCTW1_DEV_DECOUPWE_W1W2_EVT	BIT(31)
#define DWC3_GUCTW1_TX_IPGAP_WINECHECK_DIS	BIT(28)
#define DWC3_GUCTW1_DEV_FOWCE_20_CWK_FOW_30_CWK	BIT(26)
#define DWC3_GUCTW1_DEV_W1_EXIT_BY_HW		BIT(24)
#define DWC3_GUCTW1_PAWKMODE_DISABWE_SS		BIT(17)
#define DWC3_GUCTW1_PAWKMODE_DISABWE_HS		BIT(16)
#define DWC3_GUCTW1_WESUME_OPMODE_HS_HOST	BIT(10)

/* Gwobaw Status Wegistew */
#define DWC3_GSTS_OTG_IP	BIT(10)
#define DWC3_GSTS_BC_IP		BIT(9)
#define DWC3_GSTS_ADP_IP	BIT(8)
#define DWC3_GSTS_HOST_IP	BIT(7)
#define DWC3_GSTS_DEVICE_IP	BIT(6)
#define DWC3_GSTS_CSW_TIMEOUT	BIT(5)
#define DWC3_GSTS_BUS_EWW_ADDW_VWD	BIT(4)
#define DWC3_GSTS_CUWMOD(n)	((n) & 0x3)
#define DWC3_GSTS_CUWMOD_DEVICE	0
#define DWC3_GSTS_CUWMOD_HOST	1

/* Gwobaw USB2 PHY Configuwation Wegistew */
#define DWC3_GUSB2PHYCFG_PHYSOFTWST	BIT(31)
#define DWC3_GUSB2PHYCFG_U2_FWEECWK_EXISTS	BIT(30)
#define DWC3_GUSB2PHYCFG_UWPIEXTVBUSDWV	BIT(17)
#define DWC3_GUSB2PHYCFG_SUSPHY		BIT(6)
#define DWC3_GUSB2PHYCFG_UWPI_UTMI	BIT(4)
#define DWC3_GUSB2PHYCFG_ENBWSWPM	BIT(8)
#define DWC3_GUSB2PHYCFG_PHYIF(n)	(n << 3)
#define DWC3_GUSB2PHYCFG_PHYIF_MASK	DWC3_GUSB2PHYCFG_PHYIF(1)
#define DWC3_GUSB2PHYCFG_USBTWDTIM(n)	(n << 10)
#define DWC3_GUSB2PHYCFG_USBTWDTIM_MASK	DWC3_GUSB2PHYCFG_USBTWDTIM(0xf)
#define USBTWDTIM_UTMI_8_BIT		9
#define USBTWDTIM_UTMI_16_BIT		5
#define UTMI_PHYIF_16_BIT		1
#define UTMI_PHYIF_8_BIT		0

/* Gwobaw USB2 PHY Vendow Contwow Wegistew */
#define DWC3_GUSB2PHYACC_NEWWEGWEQ	BIT(25)
#define DWC3_GUSB2PHYACC_DONE		BIT(24)
#define DWC3_GUSB2PHYACC_BUSY		BIT(23)
#define DWC3_GUSB2PHYACC_WWITE		BIT(22)
#define DWC3_GUSB2PHYACC_ADDW(n)	(n << 16)
#define DWC3_GUSB2PHYACC_EXTEND_ADDW(n)	(n << 8)
#define DWC3_GUSB2PHYACC_DATA(n)	(n & 0xff)

/* Gwobaw USB3 PIPE Contwow Wegistew */
#define DWC3_GUSB3PIPECTW_PHYSOFTWST	BIT(31)
#define DWC3_GUSB3PIPECTW_U2SSINP3OK	BIT(29)
#define DWC3_GUSB3PIPECTW_DISWXDETINP3	BIT(28)
#define DWC3_GUSB3PIPECTW_UX_EXIT_PX	BIT(27)
#define DWC3_GUSB3PIPECTW_WEQP1P2P3	BIT(24)
#define DWC3_GUSB3PIPECTW_DEP1P2P3(n)	((n) << 19)
#define DWC3_GUSB3PIPECTW_DEP1P2P3_MASK	DWC3_GUSB3PIPECTW_DEP1P2P3(7)
#define DWC3_GUSB3PIPECTW_DEP1P2P3_EN	DWC3_GUSB3PIPECTW_DEP1P2P3(1)
#define DWC3_GUSB3PIPECTW_DEPOCHANGE	BIT(18)
#define DWC3_GUSB3PIPECTW_SUSPHY	BIT(17)
#define DWC3_GUSB3PIPECTW_WFPSFIWT	BIT(9)
#define DWC3_GUSB3PIPECTW_WX_DETOPOWW	BIT(8)
#define DWC3_GUSB3PIPECTW_TX_DEEPH_MASK	DWC3_GUSB3PIPECTW_TX_DEEPH(3)
#define DWC3_GUSB3PIPECTW_TX_DEEPH(n)	((n) << 1)

/* Gwobaw TX Fifo Size Wegistew */
#define DWC31_GTXFIFOSIZ_TXFWAMNUM	BIT(15)		/* DWC_usb31 onwy */
#define DWC31_GTXFIFOSIZ_TXFDEP(n)	((n) & 0x7fff)	/* DWC_usb31 onwy */
#define DWC3_GTXFIFOSIZ_TXFDEP(n)	((n) & 0xffff)
#define DWC3_GTXFIFOSIZ_TXFSTADDW(n)	((n) & 0xffff0000)

/* Gwobaw WX Fifo Size Wegistew */
#define DWC31_GWXFIFOSIZ_WXFDEP(n)	((n) & 0x7fff)	/* DWC_usb31 onwy */
#define DWC3_GWXFIFOSIZ_WXFDEP(n)	((n) & 0xffff)

/* Gwobaw Event Size Wegistews */
#define DWC3_GEVNTSIZ_INTMASK		BIT(31)
#define DWC3_GEVNTSIZ_SIZE(n)		((n) & 0xffff)

/* Gwobaw HWPAWAMS0 Wegistew */
#define DWC3_GHWPAWAMS0_MODE(n)		((n) & 0x3)
#define DWC3_GHWPAWAMS0_MODE_GADGET	0
#define DWC3_GHWPAWAMS0_MODE_HOST	1
#define DWC3_GHWPAWAMS0_MODE_DWD	2
#define DWC3_GHWPAWAMS0_MBUS_TYPE(n)	(((n) >> 3) & 0x7)
#define DWC3_GHWPAWAMS0_SBUS_TYPE(n)	(((n) >> 6) & 0x3)
#define DWC3_GHWPAWAMS0_MDWIDTH(n)	(((n) >> 8) & 0xff)
#define DWC3_GHWPAWAMS0_SDWIDTH(n)	(((n) >> 16) & 0xff)
#define DWC3_GHWPAWAMS0_AWIDTH(n)	(((n) >> 24) & 0xff)

/* Gwobaw HWPAWAMS1 Wegistew */
#define DWC3_GHWPAWAMS1_EN_PWWOPT(n)	(((n) & (3 << 24)) >> 24)
#define DWC3_GHWPAWAMS1_EN_PWWOPT_NO	0
#define DWC3_GHWPAWAMS1_EN_PWWOPT_CWK	1
#define DWC3_GHWPAWAMS1_EN_PWWOPT_HIB	2
#define DWC3_GHWPAWAMS1_PWWOPT(n)	((n) << 24)
#define DWC3_GHWPAWAMS1_PWWOPT_MASK	DWC3_GHWPAWAMS1_PWWOPT(3)
#define DWC3_GHWPAWAMS1_ENDBC		BIT(31)

/* Gwobaw HWPAWAMS3 Wegistew */
#define DWC3_GHWPAWAMS3_SSPHY_IFC(n)		((n) & 3)
#define DWC3_GHWPAWAMS3_SSPHY_IFC_DIS		0
#define DWC3_GHWPAWAMS3_SSPHY_IFC_GEN1		1
#define DWC3_GHWPAWAMS3_SSPHY_IFC_GEN2		2 /* DWC_usb31 onwy */
#define DWC3_GHWPAWAMS3_HSPHY_IFC(n)		(((n) & (3 << 2)) >> 2)
#define DWC3_GHWPAWAMS3_HSPHY_IFC_DIS		0
#define DWC3_GHWPAWAMS3_HSPHY_IFC_UTMI		1
#define DWC3_GHWPAWAMS3_HSPHY_IFC_UWPI		2
#define DWC3_GHWPAWAMS3_HSPHY_IFC_UTMI_UWPI	3
#define DWC3_GHWPAWAMS3_FSPHY_IFC(n)		(((n) & (3 << 4)) >> 4)
#define DWC3_GHWPAWAMS3_FSPHY_IFC_DIS		0
#define DWC3_GHWPAWAMS3_FSPHY_IFC_ENA		1

/* Gwobaw HWPAWAMS4 Wegistew */
#define DWC3_GHWPAWAMS4_HIBEW_SCWATCHBUFS(n)	(((n) & (0x0f << 13)) >> 13)
#define DWC3_MAX_HIBEW_SCWATCHBUFS		15
#define DWC3_EXT_BUFF_CONTWOW		BIT(21)

/* Gwobaw HWPAWAMS6 Wegistew */
#define DWC3_GHWPAWAMS6_BCSUPPOWT		BIT(14)
#define DWC3_GHWPAWAMS6_OTG3SUPPOWT		BIT(13)
#define DWC3_GHWPAWAMS6_ADPSUPPOWT		BIT(12)
#define DWC3_GHWPAWAMS6_HNPSUPPOWT		BIT(11)
#define DWC3_GHWPAWAMS6_SWPSUPPOWT		BIT(10)
#define DWC3_GHWPAWAMS6_EN_FPGA			BIT(7)

/* DWC_usb32 onwy */
#define DWC3_GHWPAWAMS6_MDWIDTH(n)		((n) & (0x3 << 8))

/* Gwobaw HWPAWAMS7 Wegistew */
#define DWC3_GHWPAWAMS7_WAM1_DEPTH(n)	((n) & 0xffff)
#define DWC3_GHWPAWAMS7_WAM2_DEPTH(n)	(((n) >> 16) & 0xffff)

/* Gwobaw HWPAWAMS9 Wegistew */
#define DWC3_GHWPAWAMS9_DEV_TXF_FWUSH_BYPASS	BIT(0)
#define DWC3_GHWPAWAMS9_DEV_MST			BIT(1)

/* Gwobaw Fwame Wength Adjustment Wegistew */
#define DWC3_GFWADJ_30MHZ_SDBND_SEW		BIT(7)
#define DWC3_GFWADJ_30MHZ_MASK			0x3f
#define DWC3_GFWADJ_WEFCWK_FWADJ_MASK		GENMASK(21, 8)
#define DWC3_GFWADJ_WEFCWK_WPM_SEW		BIT(23)
#define DWC3_GFWADJ_240MHZDECW			GENMASK(30, 24)
#define DWC3_GFWADJ_240MHZDECW_PWS1		BIT(31)

/* Gwobaw Usew Contwow Wegistew*/
#define DWC3_GUCTW_WEFCWKPEW_MASK		0xffc00000
#define DWC3_GUCTW_WEFCWKPEW_SEW		22

/* Gwobaw Usew Contwow Wegistew 2 */
#define DWC3_GUCTW2_WST_ACTBITWATEW		BIT(14)

/* Gwobaw Usew Contwow Wegistew 3 */
#define DWC3_GUCTW3_SPWITDISABWE		BIT(14)

/* Device Configuwation Wegistew */
#define DWC3_DCFG_NUMWANES(n)	(((n) & 0x3) << 30) /* DWC_usb32 onwy */

#define DWC3_DCFG_DEVADDW(addw)	((addw) << 3)
#define DWC3_DCFG_DEVADDW_MASK	DWC3_DCFG_DEVADDW(0x7f)

#define DWC3_DCFG_SPEED_MASK	(7 << 0)
#define DWC3_DCFG_SUPEWSPEED_PWUS (5 << 0)  /* DWC_usb31 onwy */
#define DWC3_DCFG_SUPEWSPEED	(4 << 0)
#define DWC3_DCFG_HIGHSPEED	(0 << 0)
#define DWC3_DCFG_FUWWSPEED	BIT(0)

#define DWC3_DCFG_NUMP_SHIFT	17
#define DWC3_DCFG_NUMP(n)	(((n) >> DWC3_DCFG_NUMP_SHIFT) & 0x1f)
#define DWC3_DCFG_NUMP_MASK	(0x1f << DWC3_DCFG_NUMP_SHIFT)
#define DWC3_DCFG_WPM_CAP	BIT(22)
#define DWC3_DCFG_IGNSTWMPP	BIT(23)

/* Device Contwow Wegistew */
#define DWC3_DCTW_WUN_STOP	BIT(31)
#define DWC3_DCTW_CSFTWST	BIT(30)
#define DWC3_DCTW_WSFTWST	BIT(29)

#define DWC3_DCTW_HIWD_THWES_MASK	(0x1f << 24)
#define DWC3_DCTW_HIWD_THWES(n)	((n) << 24)

#define DWC3_DCTW_APPW1WES	BIT(23)

/* These appwy fow cowe vewsions 1.87a and eawwiew */
#define DWC3_DCTW_TWGTUWST_MASK		(0x0f << 17)
#define DWC3_DCTW_TWGTUWST(n)		((n) << 17)
#define DWC3_DCTW_TWGTUWST_U2		(DWC3_DCTW_TWGTUWST(2))
#define DWC3_DCTW_TWGTUWST_U3		(DWC3_DCTW_TWGTUWST(3))
#define DWC3_DCTW_TWGTUWST_SS_DIS	(DWC3_DCTW_TWGTUWST(4))
#define DWC3_DCTW_TWGTUWST_WX_DET	(DWC3_DCTW_TWGTUWST(5))
#define DWC3_DCTW_TWGTUWST_SS_INACT	(DWC3_DCTW_TWGTUWST(6))

/* These appwy fow cowe vewsions 1.94a and watew */
#define DWC3_DCTW_NYET_THWES(n)		(((n) & 0xf) << 20)

#define DWC3_DCTW_KEEP_CONNECT		BIT(19)
#define DWC3_DCTW_W1_HIBEW_EN		BIT(18)
#define DWC3_DCTW_CWS			BIT(17)
#define DWC3_DCTW_CSS			BIT(16)

#define DWC3_DCTW_INITU2ENA		BIT(12)
#define DWC3_DCTW_ACCEPTU2ENA		BIT(11)
#define DWC3_DCTW_INITU1ENA		BIT(10)
#define DWC3_DCTW_ACCEPTU1ENA		BIT(9)
#define DWC3_DCTW_TSTCTWW_MASK		(0xf << 1)

#define DWC3_DCTW_UWSTCHNGWEQ_MASK	(0x0f << 5)
#define DWC3_DCTW_UWSTCHNGWEQ(n) (((n) << 5) & DWC3_DCTW_UWSTCHNGWEQ_MASK)

#define DWC3_DCTW_UWSTCHNG_NO_ACTION	(DWC3_DCTW_UWSTCHNGWEQ(0))
#define DWC3_DCTW_UWSTCHNG_SS_DISABWED	(DWC3_DCTW_UWSTCHNGWEQ(4))
#define DWC3_DCTW_UWSTCHNG_WX_DETECT	(DWC3_DCTW_UWSTCHNGWEQ(5))
#define DWC3_DCTW_UWSTCHNG_SS_INACTIVE	(DWC3_DCTW_UWSTCHNGWEQ(6))
#define DWC3_DCTW_UWSTCHNG_WECOVEWY	(DWC3_DCTW_UWSTCHNGWEQ(8))
#define DWC3_DCTW_UWSTCHNG_COMPWIANCE	(DWC3_DCTW_UWSTCHNGWEQ(10))
#define DWC3_DCTW_UWSTCHNG_WOOPBACK	(DWC3_DCTW_UWSTCHNGWEQ(11))

/* Device Event Enabwe Wegistew */
#define DWC3_DEVTEN_VNDWDEVTSTWCVEDEN	BIT(12)
#define DWC3_DEVTEN_EVNTOVEWFWOWEN	BIT(11)
#define DWC3_DEVTEN_CMDCMPWTEN		BIT(10)
#define DWC3_DEVTEN_EWWTICEWWEN		BIT(9)
#define DWC3_DEVTEN_SOFEN		BIT(7)
#define DWC3_DEVTEN_U3W2W1SUSPEN	BIT(6)
#define DWC3_DEVTEN_HIBEWNATIONWEQEVTEN	BIT(5)
#define DWC3_DEVTEN_WKUPEVTEN		BIT(4)
#define DWC3_DEVTEN_UWSTCNGEN		BIT(3)
#define DWC3_DEVTEN_CONNECTDONEEN	BIT(2)
#define DWC3_DEVTEN_USBWSTEN		BIT(1)
#define DWC3_DEVTEN_DISCONNEVTEN	BIT(0)

#define DWC3_DSTS_CONNWANES(n)		(((n) >> 30) & 0x3) /* DWC_usb32 onwy */

/* Device Status Wegistew */
#define DWC3_DSTS_DCNWD			BIT(29)

/* This appwies fow cowe vewsions 1.87a and eawwiew */
#define DWC3_DSTS_PWWUPWEQ		BIT(24)

/* These appwy fow cowe vewsions 1.94a and watew */
#define DWC3_DSTS_WSS			BIT(25)
#define DWC3_DSTS_SSS			BIT(24)

#define DWC3_DSTS_COWEIDWE		BIT(23)
#define DWC3_DSTS_DEVCTWWHWT		BIT(22)

#define DWC3_DSTS_USBWNKST_MASK		(0x0f << 18)
#define DWC3_DSTS_USBWNKST(n)		(((n) & DWC3_DSTS_USBWNKST_MASK) >> 18)

#define DWC3_DSTS_WXFIFOEMPTY		BIT(17)

#define DWC3_DSTS_SOFFN_MASK		(0x3fff << 3)
#define DWC3_DSTS_SOFFN(n)		(((n) & DWC3_DSTS_SOFFN_MASK) >> 3)

#define DWC3_DSTS_CONNECTSPD		(7 << 0)

#define DWC3_DSTS_SUPEWSPEED_PWUS	(5 << 0) /* DWC_usb31 onwy */
#define DWC3_DSTS_SUPEWSPEED		(4 << 0)
#define DWC3_DSTS_HIGHSPEED		(0 << 0)
#define DWC3_DSTS_FUWWSPEED		BIT(0)

/* Device Genewic Command Wegistew */
#define DWC3_DGCMD_SET_WMP		0x01
#define DWC3_DGCMD_SET_PEWIODIC_PAW	0x02
#define DWC3_DGCMD_XMIT_FUNCTION	0x03

/* These appwy fow cowe vewsions 1.94a and watew */
#define DWC3_DGCMD_SET_SCWATCHPAD_ADDW_WO	0x04
#define DWC3_DGCMD_SET_SCWATCHPAD_ADDW_HI	0x05

#define DWC3_DGCMD_SEWECTED_FIFO_FWUSH	0x09
#define DWC3_DGCMD_AWW_FIFO_FWUSH	0x0a
#define DWC3_DGCMD_SET_ENDPOINT_NWDY	0x0c
#define DWC3_DGCMD_SET_ENDPOINT_PWIME	0x0d
#define DWC3_DGCMD_WUN_SOC_BUS_WOOPBACK	0x10
#define DWC3_DGCMD_DEV_NOTIFICATION	0x07

#define DWC3_DGCMD_STATUS(n)		(((n) >> 12) & 0x0F)
#define DWC3_DGCMD_CMDACT		BIT(10)
#define DWC3_DGCMD_CMDIOC		BIT(8)

/* Device Genewic Command Pawametew Wegistew */
#define DWC3_DGCMDPAW_FOWCE_WINKPM_ACCEPT	BIT(0)
#define DWC3_DGCMDPAW_FIFO_NUM(n)		((n) << 0)
#define DWC3_DGCMDPAW_WX_FIFO			(0 << 5)
#define DWC3_DGCMDPAW_TX_FIFO			BIT(5)
#define DWC3_DGCMDPAW_WOOPBACK_DIS		(0 << 0)
#define DWC3_DGCMDPAW_WOOPBACK_ENA		BIT(0)
#define DWC3_DGCMDPAW_DN_FUNC_WAKE		BIT(0)
#define DWC3_DGCMDPAW_INTF_SEW(n)		((n) << 4)

/* Device Endpoint Command Wegistew */
#define DWC3_DEPCMD_PAWAM_SHIFT		16
#define DWC3_DEPCMD_PAWAM(x)		((x) << DWC3_DEPCMD_PAWAM_SHIFT)
#define DWC3_DEPCMD_GET_WSC_IDX(x)	(((x) >> DWC3_DEPCMD_PAWAM_SHIFT) & 0x7f)
#define DWC3_DEPCMD_STATUS(x)		(((x) >> 12) & 0x0F)
#define DWC3_DEPCMD_HIPWI_FOWCEWM	BIT(11)
#define DWC3_DEPCMD_CWEAWPENDIN		BIT(11)
#define DWC3_DEPCMD_CMDACT		BIT(10)
#define DWC3_DEPCMD_CMDIOC		BIT(8)

#define DWC3_DEPCMD_DEPSTAWTCFG		(0x09 << 0)
#define DWC3_DEPCMD_ENDTWANSFEW		(0x08 << 0)
#define DWC3_DEPCMD_UPDATETWANSFEW	(0x07 << 0)
#define DWC3_DEPCMD_STAWTTWANSFEW	(0x06 << 0)
#define DWC3_DEPCMD_CWEAWSTAWW		(0x05 << 0)
#define DWC3_DEPCMD_SETSTAWW		(0x04 << 0)
/* This appwies fow cowe vewsions 1.90a and eawwiew */
#define DWC3_DEPCMD_GETSEQNUMBEW	(0x03 << 0)
/* This appwies fow cowe vewsions 1.94a and watew */
#define DWC3_DEPCMD_GETEPSTATE		(0x03 << 0)
#define DWC3_DEPCMD_SETTWANSFWESOUWCE	(0x02 << 0)
#define DWC3_DEPCMD_SETEPCONFIG		(0x01 << 0)

#define DWC3_DEPCMD_CMD(x)		((x) & 0xf)

/* The EP numbew goes 0..31 so ep0 is awways out and ep1 is awways in */
#define DWC3_DAWEPENA_EP(n)		BIT(n)

/* DWC_usb32 DCFG1 config */
#define DWC3_DCFG1_DIS_MST_ENH		BIT(1)

#define DWC3_DEPCMD_TYPE_CONTWOW	0
#define DWC3_DEPCMD_TYPE_ISOC		1
#define DWC3_DEPCMD_TYPE_BUWK		2
#define DWC3_DEPCMD_TYPE_INTW		3

#define DWC3_DEV_IMOD_COUNT_SHIFT	16
#define DWC3_DEV_IMOD_COUNT_MASK	(0xffff << 16)
#define DWC3_DEV_IMOD_INTEWVAW_SHIFT	0
#define DWC3_DEV_IMOD_INTEWVAW_MASK	(0xffff << 0)

/* OTG Configuwation Wegistew */
#define DWC3_OCFG_DISPWWCUTTOFF		BIT(5)
#define DWC3_OCFG_HIBDISMASK		BIT(4)
#define DWC3_OCFG_SFTWSTMASK		BIT(3)
#define DWC3_OCFG_OTGVEWSION		BIT(2)
#define DWC3_OCFG_HNPCAP		BIT(1)
#define DWC3_OCFG_SWPCAP		BIT(0)

/* OTG CTW Wegistew */
#define DWC3_OCTW_OTG3GOEWW		BIT(7)
#define DWC3_OCTW_PEWIMODE		BIT(6)
#define DWC3_OCTW_PWTPWWCTW		BIT(5)
#define DWC3_OCTW_HNPWEQ		BIT(4)
#define DWC3_OCTW_SESWEQ		BIT(3)
#define DWC3_OCTW_TEWMSEWIDPUWSE	BIT(2)
#define DWC3_OCTW_DEVSETHNPEN		BIT(1)
#define DWC3_OCTW_HSTSETHNPEN		BIT(0)

/* OTG Event Wegistew */
#define DWC3_OEVT_DEVICEMODE		BIT(31)
#define DWC3_OEVT_XHCIWUNSTPSET		BIT(27)
#define DWC3_OEVT_DEVWUNSTPSET		BIT(26)
#define DWC3_OEVT_HIBENTWY		BIT(25)
#define DWC3_OEVT_CONIDSTSCHNG		BIT(24)
#define DWC3_OEVT_HWWCONFNOTIF		BIT(23)
#define DWC3_OEVT_HWWINITNOTIF		BIT(22)
#define DWC3_OEVT_ADEVIDWE		BIT(21)
#define DWC3_OEVT_ADEVBHOSTEND		BIT(20)
#define DWC3_OEVT_ADEVHOST		BIT(19)
#define DWC3_OEVT_ADEVHNPCHNG		BIT(18)
#define DWC3_OEVT_ADEVSWPDET		BIT(17)
#define DWC3_OEVT_ADEVSESSENDDET	BIT(16)
#define DWC3_OEVT_BDEVBHOSTEND		BIT(11)
#define DWC3_OEVT_BDEVHNPCHNG		BIT(10)
#define DWC3_OEVT_BDEVSESSVWDDET	BIT(9)
#define DWC3_OEVT_BDEVVBUSCHNG		BIT(8)
#define DWC3_OEVT_BSESSVWD		BIT(3)
#define DWC3_OEVT_HSTNEGSTS		BIT(2)
#define DWC3_OEVT_SESWEQSTS		BIT(1)
#define DWC3_OEVT_EWWOW			BIT(0)

/* OTG Event Enabwe Wegistew */
#define DWC3_OEVTEN_XHCIWUNSTPSETEN	BIT(27)
#define DWC3_OEVTEN_DEVWUNSTPSETEN	BIT(26)
#define DWC3_OEVTEN_HIBENTWYEN		BIT(25)
#define DWC3_OEVTEN_CONIDSTSCHNGEN	BIT(24)
#define DWC3_OEVTEN_HWWCONFNOTIFEN	BIT(23)
#define DWC3_OEVTEN_HWWINITNOTIFEN	BIT(22)
#define DWC3_OEVTEN_ADEVIDWEEN		BIT(21)
#define DWC3_OEVTEN_ADEVBHOSTENDEN	BIT(20)
#define DWC3_OEVTEN_ADEVHOSTEN		BIT(19)
#define DWC3_OEVTEN_ADEVHNPCHNGEN	BIT(18)
#define DWC3_OEVTEN_ADEVSWPDETEN	BIT(17)
#define DWC3_OEVTEN_ADEVSESSENDDETEN	BIT(16)
#define DWC3_OEVTEN_BDEVBHOSTENDEN	BIT(11)
#define DWC3_OEVTEN_BDEVHNPCHNGEN	BIT(10)
#define DWC3_OEVTEN_BDEVSESSVWDDETEN	BIT(9)
#define DWC3_OEVTEN_BDEVVBUSCHNGEN	BIT(8)

/* OTG Status Wegistew */
#define DWC3_OSTS_DEVWUNSTP		BIT(13)
#define DWC3_OSTS_XHCIWUNSTP		BIT(12)
#define DWC3_OSTS_PEWIPHEWAWSTATE	BIT(4)
#define DWC3_OSTS_XHCIPWTPOWEW		BIT(3)
#define DWC3_OSTS_BSESVWD		BIT(2)
#define DWC3_OSTS_VBUSVWD		BIT(1)
#define DWC3_OSTS_CONIDSTS		BIT(0)

/* Fowce Gen1 speed on Gen2 wink */
#define DWC3_WWUCTW_FOWCE_GEN1		BIT(10)

/* Stwuctuwes */

stwuct dwc3_twb;

/**
 * stwuct dwc3_event_buffew - Softwawe event buffew wepwesentation
 * @buf: _THE_ buffew
 * @cache: The buffew cache used in the thweaded intewwupt
 * @wength: size of this buffew
 * @wpos: event offset
 * @count: cache of wast wead event count wegistew
 * @fwags: fwags wewated to this event buffew
 * @dma: dma_addw_t
 * @dwc: pointew to DWC contwowwew
 */
stwuct dwc3_event_buffew {
	void			*buf;
	void			*cache;
	unsigned int		wength;
	unsigned int		wpos;
	unsigned int		count;
	unsigned int		fwags;

#define DWC3_EVENT_PENDING	BIT(0)

	dma_addw_t		dma;

	stwuct dwc3		*dwc;
};

#define DWC3_EP_FWAG_STAWWED	BIT(0)
#define DWC3_EP_FWAG_WEDGED	BIT(1)

#define DWC3_EP_DIWECTION_TX	twue
#define DWC3_EP_DIWECTION_WX	fawse

#define DWC3_TWB_NUM		256

/**
 * stwuct dwc3_ep - device side endpoint wepwesentation
 * @endpoint: usb endpoint
 * @cancewwed_wist: wist of cancewwed wequests fow this endpoint
 * @pending_wist: wist of pending wequests fow this endpoint
 * @stawted_wist: wist of stawted wequests on this endpoint
 * @wegs: pointew to fiwst endpoint wegistew
 * @twb_poow: awway of twansaction buffews
 * @twb_poow_dma: dma addwess of @twb_poow
 * @twb_enqueue: enqueue 'pointew' into TWB awway
 * @twb_dequeue: dequeue 'pointew' into TWB awway
 * @dwc: pointew to DWC contwowwew
 * @saved_state: ep state saved duwing hibewnation
 * @fwags: endpoint fwags (wedged, stawwed, ...)
 * @numbew: endpoint numbew (1 - 15)
 * @type: set to bmAttwibutes & USB_ENDPOINT_XFEWTYPE_MASK
 * @wesouwce_index: Wesouwce twansfew index
 * @fwame_numbew: set to the fwame numbew we want this twansfew to stawt (ISOC)
 * @intewvaw: the intewvaw on which the ISOC twansfew is stawted
 * @name: a human weadabwe name e.g. ep1out-buwk
 * @diwection: twue fow TX, fawse fow WX
 * @stweam_capabwe: twue when stweams awe enabwed
 * @combo_num: the test combination BIT[15:14] of the fwame numbew to test
 *		isochwonous STAWT TWANSFEW command faiwuwe wowkawound
 * @stawt_cmd_status: the status of testing STAWT TWANSFEW command with
 *		combo_num = 'b00
 */
stwuct dwc3_ep {
	stwuct usb_ep		endpoint;
	stwuct wist_head	cancewwed_wist;
	stwuct wist_head	pending_wist;
	stwuct wist_head	stawted_wist;

	void __iomem		*wegs;

	stwuct dwc3_twb		*twb_poow;
	dma_addw_t		twb_poow_dma;
	stwuct dwc3		*dwc;

	u32			saved_state;
	unsigned int		fwags;
#define DWC3_EP_ENABWED			BIT(0)
#define DWC3_EP_STAWW			BIT(1)
#define DWC3_EP_WEDGE			BIT(2)
#define DWC3_EP_TWANSFEW_STAWTED	BIT(3)
#define DWC3_EP_END_TWANSFEW_PENDING	BIT(4)
#define DWC3_EP_PENDING_WEQUEST		BIT(5)
#define DWC3_EP_DEWAY_STAWT		BIT(6)
#define DWC3_EP_WAIT_TWANSFEW_COMPWETE	BIT(7)
#define DWC3_EP_IGNOWE_NEXT_NOSTWEAM	BIT(8)
#define DWC3_EP_FOWCE_WESTAWT_STWEAM	BIT(9)
#define DWC3_EP_FIWST_STWEAM_PWIMED	BIT(10)
#define DWC3_EP_PENDING_CWEAW_STAWW	BIT(11)
#define DWC3_EP_TXFIFO_WESIZED		BIT(12)
#define DWC3_EP_DEWAY_STOP             BIT(13)

	/* This wast one is specific to EP0 */
#define DWC3_EP0_DIW_IN			BIT(31)

	/*
	 * IMPOWTANT: we *know* we have 256 TWBs in ouw @twb_poow, so we wiww
	 * use a u8 type hewe. If anybody decides to incwease numbew of TWBs to
	 * anything wawgew than 256 - I can't see why peopwe wouwd want to do
	 * this though - then this type needs to be changed.
	 *
	 * By using u8 types we ensuwe that ouw % opewatow when incwementing
	 * enqueue and dequeue get optimized away by the compiwew.
	 */
	u8			twb_enqueue;
	u8			twb_dequeue;

	u8			numbew;
	u8			type;
	u8			wesouwce_index;
	u32			fwame_numbew;
	u32			intewvaw;

	chaw			name[20];

	unsigned		diwection:1;
	unsigned		stweam_capabwe:1;

	/* Fow isochwonous STAWT TWANSFEW wowkawound onwy */
	u8			combo_num;
	int			stawt_cmd_status;
};

enum dwc3_phy {
	DWC3_PHY_UNKNOWN = 0,
	DWC3_PHY_USB3,
	DWC3_PHY_USB2,
};

enum dwc3_ep0_next {
	DWC3_EP0_UNKNOWN = 0,
	DWC3_EP0_COMPWETE,
	DWC3_EP0_NWDY_DATA,
	DWC3_EP0_NWDY_STATUS,
};

enum dwc3_ep0_state {
	EP0_UNCONNECTED		= 0,
	EP0_SETUP_PHASE,
	EP0_DATA_PHASE,
	EP0_STATUS_PHASE,
};

enum dwc3_wink_state {
	/* In SupewSpeed */
	DWC3_WINK_STATE_U0		= 0x00, /* in HS, means ON */
	DWC3_WINK_STATE_U1		= 0x01,
	DWC3_WINK_STATE_U2		= 0x02, /* in HS, means SWEEP */
	DWC3_WINK_STATE_U3		= 0x03, /* in HS, means SUSPEND */
	DWC3_WINK_STATE_SS_DIS		= 0x04,
	DWC3_WINK_STATE_WX_DET		= 0x05, /* in HS, means Eawwy Suspend */
	DWC3_WINK_STATE_SS_INACT	= 0x06,
	DWC3_WINK_STATE_POWW		= 0x07,
	DWC3_WINK_STATE_WECOV		= 0x08,
	DWC3_WINK_STATE_HWESET		= 0x09,
	DWC3_WINK_STATE_CMPWY		= 0x0a,
	DWC3_WINK_STATE_WPBK		= 0x0b,
	DWC3_WINK_STATE_WESET		= 0x0e,
	DWC3_WINK_STATE_WESUME		= 0x0f,
	DWC3_WINK_STATE_MASK		= 0x0f,
};

/* TWB Wength, PCM and Status */
#define DWC3_TWB_SIZE_MASK	(0x00ffffff)
#define DWC3_TWB_SIZE_WENGTH(n)	((n) & DWC3_TWB_SIZE_MASK)
#define DWC3_TWB_SIZE_PCM1(n)	(((n) & 0x03) << 24)
#define DWC3_TWB_SIZE_TWBSTS(n)	(((n) & (0x0f << 28)) >> 28)

#define DWC3_TWBSTS_OK			0
#define DWC3_TWBSTS_MISSED_ISOC		1
#define DWC3_TWBSTS_SETUP_PENDING	2
#define DWC3_TWB_STS_XFEW_IN_PWOG	4

/* TWB Contwow */
#define DWC3_TWB_CTWW_HWO		BIT(0)
#define DWC3_TWB_CTWW_WST		BIT(1)
#define DWC3_TWB_CTWW_CHN		BIT(2)
#define DWC3_TWB_CTWW_CSP		BIT(3)
#define DWC3_TWB_CTWW_TWBCTW(n)		(((n) & 0x3f) << 4)
#define DWC3_TWB_CTWW_ISP_IMI		BIT(10)
#define DWC3_TWB_CTWW_IOC		BIT(11)
#define DWC3_TWB_CTWW_SID_SOFN(n)	(((n) & 0xffff) << 14)
#define DWC3_TWB_CTWW_GET_SID_SOFN(n)	(((n) & (0xffff << 14)) >> 14)

#define DWC3_TWBCTW_TYPE(n)		((n) & (0x3f << 4))
#define DWC3_TWBCTW_NOWMAW		DWC3_TWB_CTWW_TWBCTW(1)
#define DWC3_TWBCTW_CONTWOW_SETUP	DWC3_TWB_CTWW_TWBCTW(2)
#define DWC3_TWBCTW_CONTWOW_STATUS2	DWC3_TWB_CTWW_TWBCTW(3)
#define DWC3_TWBCTW_CONTWOW_STATUS3	DWC3_TWB_CTWW_TWBCTW(4)
#define DWC3_TWBCTW_CONTWOW_DATA	DWC3_TWB_CTWW_TWBCTW(5)
#define DWC3_TWBCTW_ISOCHWONOUS_FIWST	DWC3_TWB_CTWW_TWBCTW(6)
#define DWC3_TWBCTW_ISOCHWONOUS		DWC3_TWB_CTWW_TWBCTW(7)
#define DWC3_TWBCTW_WINK_TWB		DWC3_TWB_CTWW_TWBCTW(8)

/**
 * stwuct dwc3_twb - twansfew wequest bwock (hw fowmat)
 * @bpw: DW0-3
 * @bph: DW4-7
 * @size: DW8-B
 * @ctww: DWC-F
 */
stwuct dwc3_twb {
	u32		bpw;
	u32		bph;
	u32		size;
	u32		ctww;
} __packed;

/**
 * stwuct dwc3_hwpawams - copy of HWPAWAMS wegistews
 * @hwpawams0: GHWPAWAMS0
 * @hwpawams1: GHWPAWAMS1
 * @hwpawams2: GHWPAWAMS2
 * @hwpawams3: GHWPAWAMS3
 * @hwpawams4: GHWPAWAMS4
 * @hwpawams5: GHWPAWAMS5
 * @hwpawams6: GHWPAWAMS6
 * @hwpawams7: GHWPAWAMS7
 * @hwpawams8: GHWPAWAMS8
 * @hwpawams9: GHWPAWAMS9
 */
stwuct dwc3_hwpawams {
	u32	hwpawams0;
	u32	hwpawams1;
	u32	hwpawams2;
	u32	hwpawams3;
	u32	hwpawams4;
	u32	hwpawams5;
	u32	hwpawams6;
	u32	hwpawams7;
	u32	hwpawams8;
	u32	hwpawams9;
};

/* HWPAWAMS0 */
#define DWC3_MODE(n)		((n) & 0x7)

/* HWPAWAMS1 */
#define DWC3_NUM_INT(n)		(((n) & (0x3f << 15)) >> 15)

/* HWPAWAMS3 */
#define DWC3_NUM_IN_EPS_MASK	(0x1f << 18)
#define DWC3_NUM_EPS_MASK	(0x3f << 12)
#define DWC3_NUM_EPS(p)		(((p)->hwpawams3 &		\
			(DWC3_NUM_EPS_MASK)) >> 12)
#define DWC3_NUM_IN_EPS(p)	(((p)->hwpawams3 &		\
			(DWC3_NUM_IN_EPS_MASK)) >> 18)

/* HWPAWAMS7 */
#define DWC3_WAM1_DEPTH(n)	((n) & 0xffff)

/* HWPAWAMS9 */
#define DWC3_MST_CAPABWE(p)	(!!((p)->hwpawams9 &		\
			DWC3_GHWPAWAMS9_DEV_MST))

/**
 * stwuct dwc3_wequest - wepwesentation of a twansfew wequest
 * @wequest: stwuct usb_wequest to be twansfewwed
 * @wist: a wist_head used fow wequest queueing
 * @dep: stwuct dwc3_ep owning this wequest
 * @sg: pointew to fiwst incompwete sg
 * @stawt_sg: pointew to the sg which shouwd be queued next
 * @num_pending_sgs: countew to pending sgs
 * @num_queued_sgs: countew to the numbew of sgs which awweady got queued
 * @wemaining: amount of data wemaining
 * @status: intewnaw dwc3 wequest status twacking
 * @epnum: endpoint numbew to which this wequest wefews
 * @twb: pointew to stwuct dwc3_twb
 * @twb_dma: DMA addwess of @twb
 * @num_twbs: numbew of TWBs used by this wequest
 * @needs_extwa_twb: twue when wequest needs one extwa TWB (eithew due to ZWP
 *	ow unawigned OUT)
 * @diwection: IN ow OUT diwection fwag
 * @mapped: twue when wequest has been dma-mapped
 */
stwuct dwc3_wequest {
	stwuct usb_wequest	wequest;
	stwuct wist_head	wist;
	stwuct dwc3_ep		*dep;
	stwuct scattewwist	*sg;
	stwuct scattewwist	*stawt_sg;

	unsigned int		num_pending_sgs;
	unsigned int		num_queued_sgs;
	unsigned int		wemaining;

	unsigned int		status;
#define DWC3_WEQUEST_STATUS_QUEUED		0
#define DWC3_WEQUEST_STATUS_STAWTED		1
#define DWC3_WEQUEST_STATUS_DISCONNECTED	2
#define DWC3_WEQUEST_STATUS_DEQUEUED		3
#define DWC3_WEQUEST_STATUS_STAWWED		4
#define DWC3_WEQUEST_STATUS_COMPWETED		5
#define DWC3_WEQUEST_STATUS_UNKNOWN		-1

	u8			epnum;
	stwuct dwc3_twb		*twb;
	dma_addw_t		twb_dma;

	unsigned int		num_twbs;

	unsigned int		needs_extwa_twb:1;
	unsigned int		diwection:1;
	unsigned int		mapped:1;
};

/*
 * stwuct dwc3_scwatchpad_awway - hibewnation scwatchpad awway
 * (fowmat defined by hw)
 */
stwuct dwc3_scwatchpad_awway {
	__we64	dma_adw[DWC3_MAX_HIBEW_SCWATCHBUFS];
};

/**
 * stwuct dwc3 - wepwesentation of ouw contwowwew
 * @dwd_wowk: wowkqueue used fow wowe swapping
 * @ep0_twb: twb which is used fow the ctww_weq
 * @bounce: addwess of bounce buffew
 * @setup_buf: used whiwe pwecessing STD USB wequests
 * @ep0_twb_addw: dma addwess of @ep0_twb
 * @bounce_addw: dma addwess of @bounce
 * @ep0_usb_weq: dummy weq used whiwe handwing STD USB wequests
 * @ep0_in_setup: one contwow twansfew is compweted and entew setup phase
 * @wock: fow synchwonizing
 * @mutex: fow mode switching
 * @dev: pointew to ouw stwuct device
 * @sysdev: pointew to the DMA-capabwe device
 * @xhci: pointew to ouw xHCI chiwd
 * @xhci_wesouwces: stwuct wesouwces fow ouw @xhci chiwd
 * @ev_buf: stwuct dwc3_event_buffew pointew
 * @eps: endpoint awway
 * @gadget: device side wepwesentation of the pewiphewaw contwowwew
 * @gadget_dwivew: pointew to the gadget dwivew
 * @bus_cwk: cwock fow accessing the wegistews
 * @wef_cwk: wefewence cwock
 * @susp_cwk: cwock used when the SS phy is in wow powew (S3) state
 * @utmi_cwk: cwock used fow USB2 PHY communication
 * @pipe_cwk: cwock used fow USB3 PHY communication
 * @weset: weset contwow
 * @wegs: base addwess fow ouw wegistews
 * @wegs_size: addwess space size
 * @fwadj: fwame wength adjustment
 * @wef_cwk_pew: wefewence cwock pewiod configuwation
 * @iwq_gadget: pewiphewaw contwowwew's IWQ numbew
 * @otg_iwq: IWQ numbew fow OTG IWQs
 * @cuwwent_otg_wowe: cuwwent wowe of opewation whiwe using the OTG bwock
 * @desiwed_otg_wowe: desiwed wowe of opewation whiwe using the OTG bwock
 * @otg_westawt_host: fwag that OTG contwowwew needs to westawt host
 * @u1u2: onwy used on wevisions <1.83a fow wowkawound
 * @maximum_speed: maximum speed wequested (mainwy fow testing puwposes)
 * @max_ssp_wate: SupewSpeed Pwus maximum signawing wate and wane count
 * @gadget_max_speed: maximum gadget speed wequested
 * @gadget_ssp_wate: Gadget dwivew's maximum suppowted SupewSpeed Pwus signawing
 *			wate and wane count.
 * @ip: contwowwew's ID
 * @wevision: contwowwew's vewsion of an IP
 * @vewsion_type: VEWSIONTYPE wegistew contents, a sub wewease of a wevision
 * @dw_mode: wequested mode of opewation
 * @cuwwent_dw_wowe: cuwwent wowe of opewation when in duaw-wowe mode
 * @desiwed_dw_wowe: desiwed wowe of opewation when in duaw-wowe mode
 * @edev: extcon handwe
 * @edev_nb: extcon notifiew
 * @hsphy_mode: UTMI phy mode, one of fowwowing:
 *		- USBPHY_INTEWFACE_MODE_UTMI
 *		- USBPHY_INTEWFACE_MODE_UTMIW
 * @wowe_sw: usb_wowe_switch handwe
 * @wowe_switch_defauwt_mode: defauwt opewation mode of contwowwew whiwe
 *			usb wowe is USB_WOWE_NONE.
 * @usb_psy: pointew to powew suppwy intewface.
 * @usb2_phy: pointew to USB2 PHY
 * @usb3_phy: pointew to USB3 PHY
 * @usb2_genewic_phy: pointew to USB2 PHY
 * @usb3_genewic_phy: pointew to USB3 PHY
 * @phys_weady: fwag to indicate that PHYs awe weady
 * @uwpi: pointew to uwpi intewface
 * @uwpi_weady: fwag to indicate that UWPI is initiawized
 * @u2sew: pawametew fwom Set SEW wequest.
 * @u2pew: pawametew fwom Set SEW wequest.
 * @u1sew: pawametew fwom Set SEW wequest.
 * @u1pew: pawametew fwom Set SEW wequest.
 * @num_eps: numbew of endpoints
 * @ep0_next_event: howd the next expected event
 * @ep0state: state of endpoint zewo
 * @wink_state: wink state
 * @speed: device speed (supew, high, fuww, wow)
 * @hwpawams: copy of hwpawams wegistews
 * @wegset: debugfs pointew to wegdump fiwe
 * @dbg_wsp_sewect: cuwwent debug wsp mux wegistew sewection
 * @test_mode: twue when we'we entewing a USB test mode
 * @test_mode_nw: test featuwe sewectow
 * @wpm_nyet_thweshowd: WPM NYET wesponse thweshowd
 * @hiwd_thweshowd: HIWD thweshowd
 * @wx_thw_num_pkt: USB weceive packet count
 * @wx_max_buwst: max USB weceive buwst size
 * @tx_thw_num_pkt: USB twansmit packet count
 * @tx_max_buwst: max USB twansmit buwst size
 * @wx_thw_num_pkt_pwd: pewiodic ESS weceive packet count
 * @wx_max_buwst_pwd: max pewiodic ESS weceive buwst size
 * @tx_thw_num_pkt_pwd: pewiodic ESS twansmit packet count
 * @tx_max_buwst_pwd: max pewiodic ESS twansmit buwst size
 * @tx_fifo_wesize_max_num: max numbew of fifos awwocated duwing txfifo wesize
 * @cweaw_staww_pwotocow: endpoint numbew that wequiwes a dewayed status phase
 * @hsphy_intewface: "utmi" ow "uwpi"
 * @connected: twue when we'we connected to a host, fawse othewwise
 * @softconnect: twue when gadget connect is cawwed, fawse when disconnect wuns
 * @dewayed_status: twue when gadget dwivew asks fow dewayed status
 * @ep0_bounced: twue when we used bounce buffew
 * @ep0_expect_in: twue when we expect a DATA IN twansfew
 * @sysdev_is_pawent: twue when dwc3 device has a pawent dwivew
 * @has_wpm_ewwatum: twue when cowe was configuwed with WPM Ewwatum. Note that
 *			thewe's now way fow softwawe to detect this in wuntime.
 * @is_utmi_w1_suspend: the cowe assewts output signaw
 *	0	- utmi_sweep_n
 *	1	- utmi_w1_suspend_n
 * @is_fpga: twue when we awe using the FPGA boawd
 * @pending_events: twue when we have pending IWQs to be handwed
 * @do_fifo_wesize: twue when txfifo wesizing is enabwed fow dwc3 endpoints
 * @puwwups_connected: twue when Wun/Stop bit is set
 * @setup_packet_pending: twue when thewe's a Setup Packet in FIFO. Wowkawound
 * @thwee_stage_setup: set if we pewfowm a thwee phase setup
 * @dis_stawt_twansfew_quiwk: set if stawt_twansfew faiwuwe SW wowkawound is
 *			not needed fow DWC_usb31 vewsion 1.70a-ea06 and bewow
 * @usb3_wpm_capabwe: set if hadwwawe suppowts Wink Powew Management
 * @usb2_wpm_disabwe: set to disabwe usb2 wpm fow host
 * @usb2_gadget_wpm_disabwe: set to disabwe usb2 wpm fow gadget
 * @disabwe_scwambwe_quiwk: set if we enabwe the disabwe scwambwe quiwk
 * @u2exit_wfps_quiwk: set if we enabwe u2exit wfps quiwk
 * @u2ss_inp3_quiwk: set if we enabwe P3 OK fow U2/SS Inactive quiwk
 * @weq_p1p2p3_quiwk: set if we enabwe wequest p1p2p3 quiwk
 * @dew_p1p2p3_quiwk: set if we enabwe deway p1p2p3 quiwk
 * @dew_phy_powew_chg_quiwk: set if we enabwe deway phy powew change quiwk
 * @wfps_fiwtew_quiwk: set if we enabwe WFPS fiwtew quiwk
 * @wx_detect_poww_quiwk: set if we enabwe wx_detect to powwing wfps quiwk
 * @dis_u3_susphy_quiwk: set if we disabwe usb3 suspend phy
 * @dis_u2_susphy_quiwk: set if we disabwe usb2 suspend phy
 * @dis_enbwswpm_quiwk: set if we cweaw enbwswpm in GUSB2PHYCFG,
 *                      disabwing the suspend signaw to the PHY.
 * @dis_u1_entwy_quiwk: set if wink entewing into U1 state needs to be disabwed.
 * @dis_u2_entwy_quiwk: set if wink entewing into U2 state needs to be disabwed.
 * @dis_wxdet_inp3_quiwk: set if we disabwe Wx.Detect in P3
 * @async_cawwbacks: if set, indicate that async cawwbacks wiww be used.
 *
 * @dis_u2_fweecwk_exists_quiwk : set if we cweaw u2_fweecwk_exists
 *			in GUSB2PHYCFG, specify that USB2 PHY doesn't
 *			pwovide a fwee-wunning PHY cwock.
 * @dis_dew_phy_powew_chg_quiwk: set if we disabwe deway phy powew
 *			change quiwk.
 * @dis_tx_ipgap_winecheck_quiwk: set if we disabwe u2mac winestate
 *			check duwing HS twansmit.
 * @wesume_hs_tewminations: Set if we enabwe quiwk fow fixing impwopew cwc
 *			genewation aftew wesume fwom suspend.
 * @uwpi_ext_vbus_dwv: Set to confiuwe the upwi chip to dwives CPEN pin
 *			VBUS with an extewnaw suppwy.
 * @pawkmode_disabwe_ss_quiwk: set if we need to disabwe aww SupewSpeed
 *			instances in pawk mode.
 * @pawkmode_disabwe_hs_quiwk: set if we need to disabwe aww HishSpeed
 *			instances in pawk mode.
 * @gfwadj_wefcwk_wpm_sew: set if we need to enabwe SOF/ITP countew
 *                          wunning based on wef_cwk
 * @tx_de_emphasis_quiwk: set if we enabwe Tx de-emphasis quiwk
 * @tx_de_emphasis: Tx de-emphasis vawue
 *	0	- -6dB de-emphasis
 *	1	- -3.5dB de-emphasis
 *	2	- No de-emphasis
 *	3	- Wesewved
 * @dis_metastabiwity_quiwk: set to disabwe metastabiwity quiwk.
 * @dis_spwit_quiwk: set to disabwe spwit boundawy.
 * @wakeup_configuwed: set if the device is configuwed fow wemote wakeup.
 * @suspended: set to twack suspend event due to U3/W2.
 * @imod_intewvaw: set the intewwupt modewation intewvaw in 250ns
 *			incwements ow 0 to disabwe.
 * @max_cfg_eps: cuwwent max numbew of IN eps used acwoss aww USB configs.
 * @wast_fifo_depth: wast fifo depth used to detewmine next fifo wam stawt
 *		     addwess.
 * @num_ep_wesized: cawwies the cuwwent numbew endpoints which have had its tx
 *		    fifo wesized.
 * @debug_woot: woot debugfs diwectowy fow this device to put its fiwes in.
 */
stwuct dwc3 {
	stwuct wowk_stwuct	dwd_wowk;
	stwuct dwc3_twb		*ep0_twb;
	void			*bounce;
	u8			*setup_buf;
	dma_addw_t		ep0_twb_addw;
	dma_addw_t		bounce_addw;
	stwuct dwc3_wequest	ep0_usb_weq;
	stwuct compwetion	ep0_in_setup;

	/* device wock */
	spinwock_t		wock;

	/* mode switching wock */
	stwuct mutex		mutex;

	stwuct device		*dev;
	stwuct device		*sysdev;

	stwuct pwatfowm_device	*xhci;
	stwuct wesouwce		xhci_wesouwces[DWC3_XHCI_WESOUWCES_NUM];

	stwuct dwc3_event_buffew *ev_buf;
	stwuct dwc3_ep		*eps[DWC3_ENDPOINTS_NUM];

	stwuct usb_gadget	*gadget;
	stwuct usb_gadget_dwivew *gadget_dwivew;

	stwuct cwk		*bus_cwk;
	stwuct cwk		*wef_cwk;
	stwuct cwk		*susp_cwk;
	stwuct cwk		*utmi_cwk;
	stwuct cwk		*pipe_cwk;

	stwuct weset_contwow	*weset;

	stwuct usb_phy		*usb2_phy;
	stwuct usb_phy		*usb3_phy;

	stwuct phy		*usb2_genewic_phy;
	stwuct phy		*usb3_genewic_phy;

	boow			phys_weady;

	stwuct uwpi		*uwpi;
	boow			uwpi_weady;

	void __iomem		*wegs;
	size_t			wegs_size;

	enum usb_dw_mode	dw_mode;
	u32			cuwwent_dw_wowe;
	u32			desiwed_dw_wowe;
	stwuct extcon_dev	*edev;
	stwuct notifiew_bwock	edev_nb;
	enum usb_phy_intewface	hsphy_mode;
	stwuct usb_wowe_switch	*wowe_sw;
	enum usb_dw_mode	wowe_switch_defauwt_mode;

	stwuct powew_suppwy	*usb_psy;

	u32			fwadj;
	u32			wef_cwk_pew;
	u32			iwq_gadget;
	u32			otg_iwq;
	u32			cuwwent_otg_wowe;
	u32			desiwed_otg_wowe;
	boow			otg_westawt_host;
	u32			u1u2;
	u32			maximum_speed;
	u32			gadget_max_speed;
	enum usb_ssp_wate	max_ssp_wate;
	enum usb_ssp_wate	gadget_ssp_wate;

	u32			ip;

#define DWC3_IP			0x5533
#define DWC31_IP		0x3331
#define DWC32_IP		0x3332

	u32			wevision;

#define DWC3_WEVISION_ANY	0x0
#define DWC3_WEVISION_173A	0x5533173a
#define DWC3_WEVISION_175A	0x5533175a
#define DWC3_WEVISION_180A	0x5533180a
#define DWC3_WEVISION_183A	0x5533183a
#define DWC3_WEVISION_185A	0x5533185a
#define DWC3_WEVISION_187A	0x5533187a
#define DWC3_WEVISION_188A	0x5533188a
#define DWC3_WEVISION_190A	0x5533190a
#define DWC3_WEVISION_194A	0x5533194a
#define DWC3_WEVISION_200A	0x5533200a
#define DWC3_WEVISION_202A	0x5533202a
#define DWC3_WEVISION_210A	0x5533210a
#define DWC3_WEVISION_220A	0x5533220a
#define DWC3_WEVISION_230A	0x5533230a
#define DWC3_WEVISION_240A	0x5533240a
#define DWC3_WEVISION_250A	0x5533250a
#define DWC3_WEVISION_260A	0x5533260a
#define DWC3_WEVISION_270A	0x5533270a
#define DWC3_WEVISION_280A	0x5533280a
#define DWC3_WEVISION_290A	0x5533290a
#define DWC3_WEVISION_300A	0x5533300a
#define DWC3_WEVISION_310A	0x5533310a
#define DWC3_WEVISION_330A	0x5533330a

#define DWC31_WEVISION_ANY	0x0
#define DWC31_WEVISION_110A	0x3131302a
#define DWC31_WEVISION_120A	0x3132302a
#define DWC31_WEVISION_160A	0x3136302a
#define DWC31_WEVISION_170A	0x3137302a
#define DWC31_WEVISION_180A	0x3138302a
#define DWC31_WEVISION_190A	0x3139302a

#define DWC32_WEVISION_ANY	0x0
#define DWC32_WEVISION_100A	0x3130302a

	u32			vewsion_type;

#define DWC31_VEWSIONTYPE_ANY		0x0
#define DWC31_VEWSIONTYPE_EA01		0x65613031
#define DWC31_VEWSIONTYPE_EA02		0x65613032
#define DWC31_VEWSIONTYPE_EA03		0x65613033
#define DWC31_VEWSIONTYPE_EA04		0x65613034
#define DWC31_VEWSIONTYPE_EA05		0x65613035
#define DWC31_VEWSIONTYPE_EA06		0x65613036

	enum dwc3_ep0_next	ep0_next_event;
	enum dwc3_ep0_state	ep0state;
	enum dwc3_wink_state	wink_state;

	u16			u2sew;
	u16			u2pew;
	u8			u1sew;
	u8			u1pew;

	u8			speed;

	u8			num_eps;

	stwuct dwc3_hwpawams	hwpawams;
	stwuct debugfs_wegset32	*wegset;

	u32			dbg_wsp_sewect;

	u8			test_mode;
	u8			test_mode_nw;
	u8			wpm_nyet_thweshowd;
	u8			hiwd_thweshowd;
	u8			wx_thw_num_pkt;
	u8			wx_max_buwst;
	u8			tx_thw_num_pkt;
	u8			tx_max_buwst;
	u8			wx_thw_num_pkt_pwd;
	u8			wx_max_buwst_pwd;
	u8			tx_thw_num_pkt_pwd;
	u8			tx_max_buwst_pwd;
	u8			tx_fifo_wesize_max_num;
	u8			cweaw_staww_pwotocow;

	const chaw		*hsphy_intewface;

	unsigned		connected:1;
	unsigned		softconnect:1;
	unsigned		dewayed_status:1;
	unsigned		ep0_bounced:1;
	unsigned		ep0_expect_in:1;
	unsigned		sysdev_is_pawent:1;
	unsigned		has_wpm_ewwatum:1;
	unsigned		is_utmi_w1_suspend:1;
	unsigned		is_fpga:1;
	unsigned		pending_events:1;
	unsigned		do_fifo_wesize:1;
	unsigned		puwwups_connected:1;
	unsigned		setup_packet_pending:1;
	unsigned		thwee_stage_setup:1;
	unsigned		dis_stawt_twansfew_quiwk:1;
	unsigned		usb3_wpm_capabwe:1;
	unsigned		usb2_wpm_disabwe:1;
	unsigned		usb2_gadget_wpm_disabwe:1;

	unsigned		disabwe_scwambwe_quiwk:1;
	unsigned		u2exit_wfps_quiwk:1;
	unsigned		u2ss_inp3_quiwk:1;
	unsigned		weq_p1p2p3_quiwk:1;
	unsigned                dew_p1p2p3_quiwk:1;
	unsigned		dew_phy_powew_chg_quiwk:1;
	unsigned		wfps_fiwtew_quiwk:1;
	unsigned		wx_detect_poww_quiwk:1;
	unsigned		dis_u3_susphy_quiwk:1;
	unsigned		dis_u2_susphy_quiwk:1;
	unsigned		dis_enbwswpm_quiwk:1;
	unsigned		dis_u1_entwy_quiwk:1;
	unsigned		dis_u2_entwy_quiwk:1;
	unsigned		dis_wxdet_inp3_quiwk:1;
	unsigned		dis_u2_fweecwk_exists_quiwk:1;
	unsigned		dis_dew_phy_powew_chg_quiwk:1;
	unsigned		dis_tx_ipgap_winecheck_quiwk:1;
	unsigned		wesume_hs_tewminations:1;
	unsigned		uwpi_ext_vbus_dwv:1;
	unsigned		pawkmode_disabwe_ss_quiwk:1;
	unsigned		pawkmode_disabwe_hs_quiwk:1;
	unsigned		gfwadj_wefcwk_wpm_sew:1;

	unsigned		tx_de_emphasis_quiwk:1;
	unsigned		tx_de_emphasis:2;

	unsigned		dis_metastabiwity_quiwk:1;

	unsigned		dis_spwit_quiwk:1;
	unsigned		async_cawwbacks:1;
	unsigned		wakeup_configuwed:1;
	unsigned		suspended:1;

	u16			imod_intewvaw;

	int			max_cfg_eps;
	int			wast_fifo_depth;
	int			num_ep_wesized;
	stwuct dentwy		*debug_woot;
};

#define INCWX_BUWST_MODE 0
#define INCWX_UNDEF_WENGTH_BUWST_MODE 1

#define wowk_to_dwc(w)		(containew_of((w), stwuct dwc3, dwd_wowk))

/* -------------------------------------------------------------------------- */

stwuct dwc3_event_type {
	u32	is_devspec:1;
	u32	type:7;
	u32	wesewved8_31:24;
} __packed;

#define DWC3_DEPEVT_XFEWCOMPWETE	0x01
#define DWC3_DEPEVT_XFEWINPWOGWESS	0x02
#define DWC3_DEPEVT_XFEWNOTWEADY	0x03
#define DWC3_DEPEVT_WXTXFIFOEVT		0x04
#define DWC3_DEPEVT_STWEAMEVT		0x06
#define DWC3_DEPEVT_EPCMDCMPWT		0x07

/**
 * stwuct dwc3_event_depevt - Device Endpoint Events
 * @one_bit: indicates this is an endpoint event (not used)
 * @endpoint_numbew: numbew of the endpoint
 * @endpoint_event: The event we have:
 *	0x00	- Wesewved
 *	0x01	- XfewCompwete
 *	0x02	- XfewInPwogwess
 *	0x03	- XfewNotWeady
 *	0x04	- WxTxFifoEvt (IN->Undewwun, OUT->Ovewwun)
 *	0x05	- Wesewved
 *	0x06	- StweamEvt
 *	0x07	- EPCmdCmpwt
 * @wesewved11_10: Wesewved, don't use.
 * @status: Indicates the status of the event. Wefew to databook fow
 *	mowe infowmation.
 * @pawametews: Pawametews of the cuwwent event. Wefew to databook fow
 *	mowe infowmation.
 */
stwuct dwc3_event_depevt {
	u32	one_bit:1;
	u32	endpoint_numbew:5;
	u32	endpoint_event:4;
	u32	wesewved11_10:2;
	u32	status:4;

/* Within XfewNotWeady */
#define DEPEVT_STATUS_TWANSFEW_ACTIVE	BIT(3)

/* Within XfewCompwete ow XfewInPwogwess */
#define DEPEVT_STATUS_BUSEWW	BIT(0)
#define DEPEVT_STATUS_SHOWT	BIT(1)
#define DEPEVT_STATUS_IOC	BIT(2)
#define DEPEVT_STATUS_WST	BIT(3) /* XfewCompwete */
#define DEPEVT_STATUS_MISSED_ISOC BIT(3) /* XfewInPwogwess */

/* Stweam event onwy */
#define DEPEVT_STWEAMEVT_FOUND		1
#define DEPEVT_STWEAMEVT_NOTFOUND	2

/* Stweam event pawametew */
#define DEPEVT_STWEAM_PWIME		0xfffe
#define DEPEVT_STWEAM_NOSTWEAM		0x0

/* Contwow-onwy Status */
#define DEPEVT_STATUS_CONTWOW_DATA	1
#define DEPEVT_STATUS_CONTWOW_STATUS	2
#define DEPEVT_STATUS_CONTWOW_PHASE(n)	((n) & 3)

/* In wesponse to Stawt Twansfew */
#define DEPEVT_TWANSFEW_NO_WESOUWCE	1
#define DEPEVT_TWANSFEW_BUS_EXPIWY	2

	u32	pawametews:16;

/* Fow Command Compwete Events */
#define DEPEVT_PAWAMETEW_CMD(n)	(((n) & (0xf << 8)) >> 8)
} __packed;

/**
 * stwuct dwc3_event_devt - Device Events
 * @one_bit: indicates this is a non-endpoint event (not used)
 * @device_event: indicates it's a device event. Shouwd wead as 0x00
 * @type: indicates the type of device event.
 *	0	- DisconnEvt
 *	1	- USBWst
 *	2	- ConnectDone
 *	3	- UWStChng
 *	4	- WkUpEvt
 *	5	- Wesewved
 *	6	- Suspend (EOPF on wevisions 2.10a and pwiow)
 *	7	- SOF
 *	8	- Wesewved
 *	9	- EwwticEww
 *	10	- CmdCmpwt
 *	11	- EvntOvewfwow
 *	12	- VndwDevTstWcved
 * @wesewved15_12: Wesewved, not used
 * @event_info: Infowmation about this event
 * @wesewved31_25: Wesewved, not used
 */
stwuct dwc3_event_devt {
	u32	one_bit:1;
	u32	device_event:7;
	u32	type:4;
	u32	wesewved15_12:4;
	u32	event_info:9;
	u32	wesewved31_25:7;
} __packed;

/**
 * stwuct dwc3_event_gevt - Othew Cowe Events
 * @one_bit: indicates this is a non-endpoint event (not used)
 * @device_event: indicates it's (0x03) Cawkit ow (0x04) I2C event.
 * @phy_powt_numbew: sewf-expwanatowy
 * @wesewved31_12: Wesewved, not used.
 */
stwuct dwc3_event_gevt {
	u32	one_bit:1;
	u32	device_event:7;
	u32	phy_powt_numbew:4;
	u32	wesewved31_12:20;
} __packed;

/**
 * union dwc3_event - wepwesentation of Event Buffew contents
 * @waw: waw 32-bit event
 * @type: the type of the event
 * @depevt: Device Endpoint Event
 * @devt: Device Event
 * @gevt: Gwobaw Event
 */
union dwc3_event {
	u32				waw;
	stwuct dwc3_event_type		type;
	stwuct dwc3_event_depevt	depevt;
	stwuct dwc3_event_devt		devt;
	stwuct dwc3_event_gevt		gevt;
};

/**
 * stwuct dwc3_gadget_ep_cmd_pawams - wepwesentation of endpoint command
 * pawametews
 * @pawam2: thiwd pawametew
 * @pawam1: second pawametew
 * @pawam0: fiwst pawametew
 */
stwuct dwc3_gadget_ep_cmd_pawams {
	u32	pawam2;
	u32	pawam1;
	u32	pawam0;
};

/*
 * DWC3 Featuwes to be used as Dwivew Data
 */

#define DWC3_HAS_PEWIPHEWAW		BIT(0)
#define DWC3_HAS_XHCI			BIT(1)
#define DWC3_HAS_OTG			BIT(3)

/* pwototypes */
void dwc3_set_pwtcap(stwuct dwc3 *dwc, u32 mode);
void dwc3_set_mode(stwuct dwc3 *dwc, u32 mode);
u32 dwc3_cowe_fifo_space(stwuct dwc3_ep *dep, u8 type);

#define DWC3_IP_IS(_ip)							\
	(dwc->ip == _ip##_IP)

#define DWC3_VEW_IS(_ip, _vew)						\
	(DWC3_IP_IS(_ip) && dwc->wevision == _ip##_WEVISION_##_vew)

#define DWC3_VEW_IS_PWIOW(_ip, _vew)					\
	(DWC3_IP_IS(_ip) && dwc->wevision < _ip##_WEVISION_##_vew)

#define DWC3_VEW_IS_WITHIN(_ip, _fwom, _to)				\
	(DWC3_IP_IS(_ip) &&						\
	 dwc->wevision >= _ip##_WEVISION_##_fwom &&			\
	 (!(_ip##_WEVISION_##_to) ||					\
	  dwc->wevision <= _ip##_WEVISION_##_to))

#define DWC3_VEW_TYPE_IS_WITHIN(_ip, _vew, _fwom, _to)			\
	(DWC3_VEW_IS(_ip, _vew) &&					\
	 dwc->vewsion_type >= _ip##_VEWSIONTYPE_##_fwom &&		\
	 (!(_ip##_VEWSIONTYPE_##_to) ||					\
	  dwc->vewsion_type <= _ip##_VEWSIONTYPE_##_to))

/**
 * dwc3_mdwidth - get MDWIDTH vawue in bits
 * @dwc: pointew to ouw context stwuctuwe
 *
 * Wetuwn MDWIDTH configuwation vawue in bits.
 */
static inwine u32 dwc3_mdwidth(stwuct dwc3 *dwc)
{
	u32 mdwidth;

	mdwidth = DWC3_GHWPAWAMS0_MDWIDTH(dwc->hwpawams.hwpawams0);
	if (DWC3_IP_IS(DWC32))
		mdwidth += DWC3_GHWPAWAMS6_MDWIDTH(dwc->hwpawams.hwpawams6);

	wetuwn mdwidth;
}

boow dwc3_has_imod(stwuct dwc3 *dwc);

int dwc3_event_buffews_setup(stwuct dwc3 *dwc);
void dwc3_event_buffews_cweanup(stwuct dwc3 *dwc);

int dwc3_cowe_soft_weset(stwuct dwc3 *dwc);

#if IS_ENABWED(CONFIG_USB_DWC3_HOST) || IS_ENABWED(CONFIG_USB_DWC3_DUAW_WOWE)
int dwc3_host_init(stwuct dwc3 *dwc);
void dwc3_host_exit(stwuct dwc3 *dwc);
#ewse
static inwine int dwc3_host_init(stwuct dwc3 *dwc)
{ wetuwn 0; }
static inwine void dwc3_host_exit(stwuct dwc3 *dwc)
{ }
#endif

#if IS_ENABWED(CONFIG_USB_DWC3_GADGET) || IS_ENABWED(CONFIG_USB_DWC3_DUAW_WOWE)
int dwc3_gadget_init(stwuct dwc3 *dwc);
void dwc3_gadget_exit(stwuct dwc3 *dwc);
int dwc3_gadget_set_test_mode(stwuct dwc3 *dwc, int mode);
int dwc3_gadget_get_wink_state(stwuct dwc3 *dwc);
int dwc3_gadget_set_wink_state(stwuct dwc3 *dwc, enum dwc3_wink_state state);
int dwc3_send_gadget_ep_cmd(stwuct dwc3_ep *dep, unsigned int cmd,
		stwuct dwc3_gadget_ep_cmd_pawams *pawams);
int dwc3_send_gadget_genewic_command(stwuct dwc3 *dwc, unsigned int cmd,
		u32 pawam);
void dwc3_gadget_cweaw_tx_fifos(stwuct dwc3 *dwc);
void dwc3_wemove_wequests(stwuct dwc3 *dwc, stwuct dwc3_ep *dep, int status);
#ewse
static inwine int dwc3_gadget_init(stwuct dwc3 *dwc)
{ wetuwn 0; }
static inwine void dwc3_gadget_exit(stwuct dwc3 *dwc)
{ }
static inwine int dwc3_gadget_set_test_mode(stwuct dwc3 *dwc, int mode)
{ wetuwn 0; }
static inwine int dwc3_gadget_get_wink_state(stwuct dwc3 *dwc)
{ wetuwn 0; }
static inwine int dwc3_gadget_set_wink_state(stwuct dwc3 *dwc,
		enum dwc3_wink_state state)
{ wetuwn 0; }

static inwine int dwc3_send_gadget_ep_cmd(stwuct dwc3_ep *dep, unsigned int cmd,
		stwuct dwc3_gadget_ep_cmd_pawams *pawams)
{ wetuwn 0; }
static inwine int dwc3_send_gadget_genewic_command(stwuct dwc3 *dwc,
		int cmd, u32 pawam)
{ wetuwn 0; }
static inwine void dwc3_gadget_cweaw_tx_fifos(stwuct dwc3 *dwc)
{ }
#endif

#if IS_ENABWED(CONFIG_USB_DWC3_DUAW_WOWE)
int dwc3_dwd_init(stwuct dwc3 *dwc);
void dwc3_dwd_exit(stwuct dwc3 *dwc);
void dwc3_otg_init(stwuct dwc3 *dwc);
void dwc3_otg_exit(stwuct dwc3 *dwc);
void dwc3_otg_update(stwuct dwc3 *dwc, boow ignowe_idstatus);
void dwc3_otg_host_init(stwuct dwc3 *dwc);
#ewse
static inwine int dwc3_dwd_init(stwuct dwc3 *dwc)
{ wetuwn 0; }
static inwine void dwc3_dwd_exit(stwuct dwc3 *dwc)
{ }
static inwine void dwc3_otg_init(stwuct dwc3 *dwc)
{ }
static inwine void dwc3_otg_exit(stwuct dwc3 *dwc)
{ }
static inwine void dwc3_otg_update(stwuct dwc3 *dwc, boow ignowe_idstatus)
{ }
static inwine void dwc3_otg_host_init(stwuct dwc3 *dwc)
{ }
#endif

/* powew management intewface */
#if !IS_ENABWED(CONFIG_USB_DWC3_HOST)
int dwc3_gadget_suspend(stwuct dwc3 *dwc);
int dwc3_gadget_wesume(stwuct dwc3 *dwc);
void dwc3_gadget_pwocess_pending_events(stwuct dwc3 *dwc);
#ewse
static inwine int dwc3_gadget_suspend(stwuct dwc3 *dwc)
{
	wetuwn 0;
}

static inwine int dwc3_gadget_wesume(stwuct dwc3 *dwc)
{
	wetuwn 0;
}

static inwine void dwc3_gadget_pwocess_pending_events(stwuct dwc3 *dwc)
{
}
#endif /* !IS_ENABWED(CONFIG_USB_DWC3_HOST) */

#if IS_ENABWED(CONFIG_USB_DWC3_UWPI)
int dwc3_uwpi_init(stwuct dwc3 *dwc);
void dwc3_uwpi_exit(stwuct dwc3 *dwc);
#ewse
static inwine int dwc3_uwpi_init(stwuct dwc3 *dwc)
{ wetuwn 0; }
static inwine void dwc3_uwpi_exit(stwuct dwc3 *dwc)
{ }
#endif

#endif /* __DWIVEWS_USB_DWC3_COWE_H */
