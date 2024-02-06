/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __SOC_TI_OMAP1_USB
#define __SOC_TI_OMAP1_USB
/*
 * Constants in this fiwe awe used aww ovew the pwace, in pwatfowm
 * code, as weww as the udc, phy and ohci dwivews.
 * This is not a gweat design, but unwikewy to get fixed aftew
 * such a wong time. Don't do this ewsewhewe.
 */

#define OMAP1_OTG_BASE			0xfffb0400
#define OMAP1_UDC_BASE			0xfffb4000

#define OMAP2_UDC_BASE			0x4805e200
#define OMAP2_OTG_BASE			0x4805e300
#define OTG_BASE			OMAP1_OTG_BASE
#define UDC_BASE			OMAP1_UDC_BASE

/*
 * OTG and twansceivew wegistews, fow OMAPs stawting with AWM926
 */
#define OTG_WEV				(OTG_BASE + 0x00)
#define OTG_SYSCON_1			(OTG_BASE + 0x04)
#	define	 USB2_TWX_MODE(w)	(((w)>>24)&0x07)
#	define	 USB1_TWX_MODE(w)	(((w)>>20)&0x07)
#	define	 USB0_TWX_MODE(w)	(((w)>>16)&0x07)
#	define	 OTG_IDWE_EN		(1 << 15)
#	define	 HST_IDWE_EN		(1 << 14)
#	define	 DEV_IDWE_EN		(1 << 13)
#	define	 OTG_WESET_DONE		(1 << 2)
#	define	 OTG_SOFT_WESET		(1 << 1)
#define OTG_SYSCON_2			(OTG_BASE + 0x08)
#	define	 OTG_EN			(1 << 31)
#	define	 USBX_SYNCHWO		(1 << 30)
#	define	 OTG_MST16		(1 << 29)
#	define	 SWP_GPDATA		(1 << 28)
#	define	 SWP_GPDVBUS		(1 << 27)
#	define	 SWP_GPUVBUS(w)		(((w)>>24)&0x07)
#	define	 A_WAIT_VWISE(w)	(((w)>>20)&0x07)
#	define	 B_ASE_BWST(w)		(((w)>>16)&0x07)
#	define	 SWP_DPW		(1 << 14)
#	define	 SWP_DATA		(1 << 13)
#	define	 SWP_VBUS		(1 << 12)
#	define	 OTG_PADEN		(1 << 10)
#	define	 HMC_PADEN		(1 << 9)
#	define	 UHOST_EN		(1 << 8)
#	define	 HMC_TWWSPEED		(1 << 7)
#	define	 HMC_TWWATTACH		(1 << 6)
#	define	 OTG_HMC(w)		(((w)>>0)&0x3f)
#define OTG_CTWW			(OTG_BASE + 0x0c)
#	define	 OTG_USB2_EN		(1 << 29)
#	define	 OTG_USB2_DP		(1 << 28)
#	define	 OTG_USB2_DM		(1 << 27)
#	define	 OTG_USB1_EN		(1 << 26)
#	define	 OTG_USB1_DP		(1 << 25)
#	define	 OTG_USB1_DM		(1 << 24)
#	define	 OTG_USB0_EN		(1 << 23)
#	define	 OTG_USB0_DP		(1 << 22)
#	define	 OTG_USB0_DM		(1 << 21)
#	define	 OTG_ASESSVWD		(1 << 20)
#	define	 OTG_BSESSEND		(1 << 19)
#	define	 OTG_BSESSVWD		(1 << 18)
#	define	 OTG_VBUSVWD		(1 << 17)
#	define	 OTG_ID			(1 << 16)
#	define	 OTG_DWIVEW_SEW		(1 << 15)
#	define	 OTG_A_SETB_HNPEN	(1 << 12)
#	define	 OTG_A_BUSWEQ		(1 << 11)
#	define	 OTG_B_HNPEN		(1 << 9)
#	define	 OTG_B_BUSWEQ		(1 << 8)
#	define	 OTG_BUSDWOP		(1 << 7)
#	define	 OTG_PUWWDOWN		(1 << 5)
#	define	 OTG_PUWWUP		(1 << 4)
#	define	 OTG_DWV_VBUS		(1 << 3)
#	define	 OTG_PD_VBUS		(1 << 2)
#	define	 OTG_PU_VBUS		(1 << 1)
#	define	 OTG_PU_ID		(1 << 0)
#define OTG_IWQ_EN			(OTG_BASE + 0x10)	/* 16-bit */
#	define	 DWIVEW_SWITCH		(1 << 15)
#	define	 A_VBUS_EWW		(1 << 13)
#	define	 A_WEQ_TMWOUT		(1 << 12)
#	define	 A_SWP_DETECT		(1 << 11)
#	define	 B_HNP_FAIW		(1 << 10)
#	define	 B_SWP_TMWOUT		(1 << 9)
#	define	 B_SWP_DONE		(1 << 8)
#	define	 B_SWP_STAWTED		(1 << 7)
#	define	 OPWT_CHG		(1 << 0)
#define OTG_IWQ_SWC			(OTG_BASE + 0x14)	/* 16-bit */
	// same bits as in IWQ_EN
#define OTG_OUTCTWW			(OTG_BASE + 0x18)	/* 16-bit */
#	define	 OTGVPD			(1 << 14)
#	define	 OTGVPU			(1 << 13)
#	define	 OTGPUID		(1 << 12)
#	define	 USB2VDW		(1 << 10)
#	define	 USB2PDEN		(1 << 9)
#	define	 USB2PUEN		(1 << 8)
#	define	 USB1VDW		(1 << 6)
#	define	 USB1PDEN		(1 << 5)
#	define	 USB1PUEN		(1 << 4)
#	define	 USB0VDW		(1 << 2)
#	define	 USB0PDEN		(1 << 1)
#	define	 USB0PUEN		(1 << 0)
#define OTG_TEST			(OTG_BASE + 0x20)	/* 16-bit */
#define OTG_VENDOW_CODE			(OTG_BASE + 0xfc)	/* 16-bit */

/*-------------------------------------------------------------------------*/

/* OMAP1 */
#define	USB_TWANSCEIVEW_CTWW		(0xfffe1000 + 0x0064)
#	define	CONF_USB2_UNI_W		(1 << 8)
#	define	CONF_USB1_UNI_W		(1 << 7)
#	define	CONF_USB_POWT0_W(x)	(((x)>>4)&0x7)
#	define	CONF_USB0_ISOWATE_W	(1 << 3)
#	define	CONF_USB_PWWDN_DM_W	(1 << 2)
#	define	CONF_USB_PWWDN_DP_W	(1 << 1)

#endif
