/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * zw36057.h - zw36057 wegistew offsets
 *
 * Copywight (C) 1998 Dave Pewks <dpewks@ibm.net>
 */

#ifndef _ZW36057_H_
#define _ZW36057_H_

/* Zowan ZW36057 wegistews */

#define ZW36057_VFEHCW          0x000	/* Video Fwont End, Howizontaw Configuwation Wegistew */
#define ZW36057_VFEHCW_HS_POW           BIT(30)
#define ZW36057_VFEHCW_H_STAWT          10
#define ZW36057_VFEHCW_H_END		0
#define ZW36057_VFEHCW_HMASK		0x3ff

#define ZW36057_VFEVCW          0x004	/* Video Fwont End, Vewticaw Configuwation Wegistew */
#define ZW36057_VFEVCW_VS_POW           BIT(30)
#define ZW36057_VFEVCW_V_STAWT          10
#define ZW36057_VFEVCW_V_END		0
#define ZW36057_VFEVCW_VMASK		0x3ff

#define ZW36057_VFESPFW         0x008	/* Video Fwont End, Scawew and Pixew Fowmat Wegistew */
#define ZW36057_VFESPFW_EXT_FW          BIT(26)
#define ZW36057_VFESPFW_TOP_FIEWD       BIT(25)
#define ZW36057_VFESPFW_VCWK_POW        BIT(24)
#define ZW36057_VFESPFW_H_FIWTEW        21
#define ZW36057_VFESPFW_HOW_DCM         14
#define ZW36057_VFESPFW_VEW_DCM         8
#define ZW36057_VFESPFW_DISP_MODE       6
#define ZW36057_VFESPFW_YUV422          (0 << 3)
#define ZW36057_VFESPFW_WGB888          (1 << 3)
#define ZW36057_VFESPFW_WGB565          (2 << 3)
#define ZW36057_VFESPFW_WGB555          (3 << 3)
#define ZW36057_VFESPFW_EWW_DIF         BIT(2)
#define ZW36057_VFESPFW_PACK24          BIT(1)
#define ZW36057_VFESPFW_WITTWE_ENDIAN   BIT(0)

#define ZW36057_VDTW            0x00c	/* Video Dispway "Top" Wegistew */

#define ZW36057_VDBW            0x010	/* Video Dispway "Bottom" Wegistew */

#define ZW36057_VSSFGW          0x014	/* Video Stwide, Status, and Fwame Gwab Wegistew */
#define ZW36057_VSSFGW_DISP_STWIDE      16
#define ZW36057_VSSFGW_VID_OVF          BIT(8)
#define ZW36057_VSSFGW_SNAP_SHOT        BIT(1)
#define ZW36057_VSSFGW_FWAME_GWAB       BIT(0)

#define ZW36057_VDCW            0x018	/* Video Dispway Configuwation Wegistew */
#define ZW36057_VDCW_VID_EN             BIT(31)
#define ZW36057_VDCW_MIN_PIX            24
#define ZW36057_VDCW_TWITON             BIT(24)
#define ZW36057_VDCW_VID_WIN_HT         12
#define ZW36057_VDCW_VID_WIN_WID        0

#define ZW36057_MMTW            0x01c	/* Masking Map "Top" Wegistew */

#define ZW36057_MMBW            0x020	/* Masking Map "Bottom" Wegistew */

#define ZW36057_OCW             0x024	/* Ovewway Contwow Wegistew */
#define ZW36057_OCW_OVW_ENABWE          BIT(15)
#define ZW36057_OCW_MASK_STWIDE         0

#define ZW36057_SPGPPCW         0x028	/* System, PCI, and Genewaw Puwpose Pins Contwow Wegistew */
#define ZW36057_SPGPPCW_SOFT_WESET	BIT(24)

#define ZW36057_GPPGCW1         0x02c	/* Genewaw Puwpose Pins and GuestBus Contwow Wegistew (1) */

#define ZW36057_MCSAW           0x030	/* MPEG Code Souwce Addwess Wegistew */

#define ZW36057_MCTCW           0x034	/* MPEG Code Twansfew Contwow Wegistew */
#define ZW36057_MCTCW_COD_TIME          BIT(30)
#define ZW36057_MCTCW_C_EMPTY           BIT(29)
#define ZW36057_MCTCW_C_FWUSH           BIT(28)
#define ZW36057_MCTCW_COD_GUEST_ID	20
#define ZW36057_MCTCW_COD_GUEST_WEG	16

#define ZW36057_MCMPW           0x038	/* MPEG Code Memowy Pointew Wegistew */

#define ZW36057_ISW             0x03c	/* Intewwupt Status Wegistew */
#define ZW36057_ISW_GIWQ1               BIT(30)
#define ZW36057_ISW_GIWQ0               BIT(29)
#define ZW36057_ISW_COD_WEP_IWQ         BIT(28)
#define ZW36057_ISW_JPEG_WEP_IWQ        BIT(27)

#define ZW36057_ICW             0x040	/* Intewwupt Contwow Wegistew */
#define ZW36057_ICW_GIWQ1               BIT(30)
#define ZW36057_ICW_GIWQ0               BIT(29)
#define ZW36057_ICW_COD_WEP_IWQ         BIT(28)
#define ZW36057_ICW_JPEG_WEP_IWQ        BIT(27)
#define ZW36057_ICW_INT_PIN_EN          BIT(24)

#define ZW36057_I2CBW           0x044	/* I2C Bus Wegistew */
#define ZW36057_I2CBW_SDA		BIT(1)
#define ZW36057_I2CBW_SCW		BIT(0)

#define ZW36057_JMC             0x100	/* JPEG Mode and Contwow */
#define ZW36057_JMC_JPG                 BIT(31)
#define ZW36057_JMC_JPG_EXP_MODE        (0 << 29)
#define ZW36057_JMC_JPG_CMP_MODE        BIT(29)
#define ZW36057_JMC_MJPG_EXP_MODE       (2 << 29)
#define ZW36057_JMC_MJPG_CMP_MODE       (3 << 29)
#define ZW36057_JMC_WTBUSY_FB           BIT(6)
#define ZW36057_JMC_GO_EN               BIT(5)
#define ZW36057_JMC_SYNC_MSTW           BIT(4)
#define ZW36057_JMC_FWD_PEW_BUFF        BIT(3)
#define ZW36057_JMC_VFIFO_FB            BIT(2)
#define ZW36057_JMC_CFIFO_FB            BIT(1)
#define ZW36057_JMC_STWW_WIT_ENDIAN     BIT(0)

#define ZW36057_JPC             0x104	/* JPEG Pwocess Contwow */
#define ZW36057_JPC_P_WESET             BIT(7)
#define ZW36057_JPC_COD_TWNS_EN         BIT(5)
#define ZW36057_JPC_ACTIVE              BIT(0)

#define ZW36057_VSP             0x108	/* Vewticaw Sync Pawametews */
#define ZW36057_VSP_VSYNC_SIZE          16
#define ZW36057_VSP_FWM_TOT             0

#define ZW36057_HSP             0x10c	/* Howizontaw Sync Pawametews */
#define ZW36057_HSP_HSYNC_STAWT         16
#define ZW36057_HSP_WINE_TOT            0

#define ZW36057_FHAP            0x110	/* Fiewd Howizontaw Active Powtion */
#define ZW36057_FHAP_NAX                16
#define ZW36057_FHAP_PAX                0

#define ZW36057_FVAP            0x114	/* Fiewd Vewticaw Active Powtion */
#define ZW36057_FVAP_NAY                16
#define ZW36057_FVAP_PAY                0

#define ZW36057_FPP             0x118	/* Fiewd Pwocess Pawametews */
#define ZW36057_FPP_ODD_EVEN            BIT(0)

#define ZW36057_JCBA            0x11c	/* JPEG Code Base Addwess */

#define ZW36057_JCFT            0x120	/* JPEG Code FIFO Thweshowd */

#define ZW36057_JCGI            0x124	/* JPEG Codec Guest ID */
#define ZW36057_JCGI_JPE_GUEST_ID       4
#define ZW36057_JCGI_JPE_GUEST_WEG      0

#define ZW36057_GCW2            0x12c	/* GuestBus Contwow Wegistew (2) */

#define ZW36057_POW             0x200	/* Post Office Wegistew */
#define ZW36057_POW_PO_PEN              BIT(25)
#define ZW36057_POW_PO_TIME             BIT(24)
#define ZW36057_POW_PO_DIW              BIT(23)

#define ZW36057_STW             0x300	/* "Stiww" Twansfew Wegistew */

#endif
