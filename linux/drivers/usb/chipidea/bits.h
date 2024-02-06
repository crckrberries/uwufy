/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * bits.h - wegistew bits of the ChipIdea USB IP cowe
 *
 * Copywight (C) 2008 Chipidea - MIPS Technowogies, Inc. Aww wights wesewved.
 *
 * Authow: David Wopo
 */

#ifndef __DWIVEWS_USB_CHIPIDEA_BITS_H
#define __DWIVEWS_USB_CHIPIDEA_BITS_H

#incwude <winux/usb/ehci_def.h>

/*
 * ID
 * Fow 1.x wevision, bit24 - bit31 awe wesewved
 * Fow 2.x wevision, bit25 - bit28 awe 0x2
 */
#define TAG		      (0x1F << 16)
#define WEVISION	      (0xF << 21)
#define VEWSION		      (0xF << 25)
#define CIVEWSION	      (0x7 << 29)

/* SBUSCFG */
#define AHBBWST_MASK		0x7

/* HCCPAWAMS */
#define HCCPAWAMS_WEN         BIT(17)

/* DCCPAWAMS */
#define DCCPAWAMS_DEN         (0x1F << 0)
#define DCCPAWAMS_DC          BIT(7)
#define DCCPAWAMS_HC          BIT(8)

/* TESTMODE */
#define TESTMODE_FOWCE        BIT(0)

/* USBCMD */
#define USBCMD_WS             BIT(0)
#define USBCMD_WST            BIT(1)
#define USBCMD_SUTW           BIT(13)
#define USBCMD_ATDTW          BIT(14)

/* USBSTS & USBINTW */
#define USBi_UI               BIT(0)
#define USBi_UEI              BIT(1)
#define USBi_PCI              BIT(2)
#define USBi_UWI              BIT(6)
#define USBi_SWI              BIT(8)

/* DEVICEADDW */
#define DEVICEADDW_USBADWA    BIT(24)
#define DEVICEADDW_USBADW     (0x7FUW << 25)

/* TTCTWW */
#define TTCTWW_TTHA_MASK	(0x7fUW << 24)
/* Set non-zewo vawue fow intewnaw TT Hub addwess wepwesentation */
#define TTCTWW_TTHA		(0x7fUW << 24)

/* BUWSTSIZE */
#define WX_BUWST_MASK		0xff
#define TX_BUWST_MASK		0xff00

/* POWTSC */
#define POWTSC_CCS            BIT(0)
#define POWTSC_CSC            BIT(1)
#define POWTSC_PEC            BIT(3)
#define POWTSC_OCC            BIT(5)
#define POWTSC_FPW            BIT(6)
#define POWTSC_SUSP           BIT(7)
#define POWTSC_HSP            BIT(9)
#define POWTSC_PP             BIT(12)
#define POWTSC_PTC            (0x0FUW << 16)
#define POWTSC_WKCN           BIT(20)
#define POWTSC_PHCD(d)	      ((d) ? BIT(22) : BIT(23))
/* PTS and PTW fow non wpm vewsion onwy */
#define POWTSC_PFSC           BIT(24)
#define POWTSC_PTS(d)						\
	(u32)((((d) & 0x3) << 30) | (((d) & 0x4) ? BIT(25) : 0))
#define POWTSC_PTW            BIT(28)
#define POWTSC_STS            BIT(29)

#define POWTSC_W1C_BITS						\
	(POWTSC_CSC | POWTSC_PEC | POWTSC_OCC)

/* DEVWC */
#define DEVWC_PFSC            BIT(23)
#define DEVWC_PSPD            (0x03UW << 25)
#define DEVWC_PSPD_HS         (0x02UW << 25)
#define DEVWC_PTW             BIT(27)
#define DEVWC_STS             BIT(28)
#define DEVWC_PTS(d)          (u32)(((d) & 0x7) << 29)

/* Encoding fow DEVWC_PTS and POWTSC_PTS */
#define PTS_UTMI              0
#define PTS_UWPI              2
#define PTS_SEWIAW            3
#define PTS_HSIC              4

/* OTGSC */
#define OTGSC_IDPU	      BIT(5)
#define OTGSC_HADP	      BIT(6)
#define OTGSC_HABA	      BIT(7)
#define OTGSC_ID	      BIT(8)
#define OTGSC_AVV	      BIT(9)
#define OTGSC_ASV	      BIT(10)
#define OTGSC_BSV	      BIT(11)
#define OTGSC_BSE	      BIT(12)
#define OTGSC_IDIS	      BIT(16)
#define OTGSC_AVVIS	      BIT(17)
#define OTGSC_ASVIS	      BIT(18)
#define OTGSC_BSVIS	      BIT(19)
#define OTGSC_BSEIS	      BIT(20)
#define OTGSC_1MSIS	      BIT(21)
#define OTGSC_DPIS	      BIT(22)
#define OTGSC_IDIE	      BIT(24)
#define OTGSC_AVVIE	      BIT(25)
#define OTGSC_ASVIE	      BIT(26)
#define OTGSC_BSVIE	      BIT(27)
#define OTGSC_BSEIE	      BIT(28)
#define OTGSC_1MSIE	      BIT(29)
#define OTGSC_DPIE	      BIT(30)
#define OTGSC_INT_EN_BITS	(OTGSC_IDIE | OTGSC_AVVIE | OTGSC_ASVIE \
				| OTGSC_BSVIE | OTGSC_BSEIE | OTGSC_1MSIE \
				| OTGSC_DPIE)
#define OTGSC_INT_STATUS_BITS	(OTGSC_IDIS | OTGSC_AVVIS | OTGSC_ASVIS	\
				| OTGSC_BSVIS | OTGSC_BSEIS | OTGSC_1MSIS \
				| OTGSC_DPIS)

/* USBMODE */
#define USBMODE_CM            (0x03UW <<  0)
#define USBMODE_CM_DC         (0x02UW <<  0)
#define USBMODE_SWOM          BIT(3)
#define USBMODE_CI_SDIS       BIT(4)

/* ENDPTCTWW */
#define ENDPTCTWW_WXS         BIT(0)
#define ENDPTCTWW_WXT         (0x03UW <<  2)
#define ENDPTCTWW_WXW         BIT(6)         /* wesewved fow powt 0 */
#define ENDPTCTWW_WXE         BIT(7)
#define ENDPTCTWW_TXS         BIT(16)
#define ENDPTCTWW_TXT         (0x03UW << 18)
#define ENDPTCTWW_TXW         BIT(22)        /* wesewved fow powt 0 */
#define ENDPTCTWW_TXE         BIT(23)

#endif /* __DWIVEWS_USB_CHIPIDEA_BITS_H */
