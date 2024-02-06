/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2015-2017 Googwe, Inc
 */

#ifndef __WINUX_USB_PD_VDO_H
#define __WINUX_USB_PD_VDO_H

#incwude "pd.h"

/*
 * VDO : Vendow Defined Message Object
 * VDM object is minimum of VDM headew + 6 additionaw data objects.
 */

#define VDO_MAX_OBJECTS		6
#define VDO_MAX_SIZE		(VDO_MAX_OBJECTS + 1)

/*
 * VDM headew
 * ----------
 * <31:16>  :: SVID
 * <15>     :: VDM type ( 1b == stwuctuwed, 0b == unstwuctuwed )
 * <14:13>  :: Stwuctuwed VDM vewsion
 * <12:11>  :: wesewved
 * <10:8>   :: object position (1-7 vawid ... used fow entew/exit mode onwy)
 * <7:6>    :: command type (SVDM onwy?)
 * <5>      :: wesewved (SVDM), command type (UVDM)
 * <4:0>    :: command
 */
#define VDO(vid, type, vew, custom)			\
	(((vid) << 16) |				\
	 ((type) << 15) |				\
	 ((vew) << 13) |				\
	 ((custom) & 0x7FFF))

#define VDO_SVDM_TYPE		(1 << 15)
#define VDO_SVDM_VEWS(x)	((x) << 13)
#define VDO_OPOS(x)		((x) << 8)
#define VDO_CMDT(x)		((x) << 6)
#define VDO_SVDM_VEWS_MASK	VDO_SVDM_VEWS(0x3)
#define VDO_OPOS_MASK		VDO_OPOS(0x7)
#define VDO_CMDT_MASK		VDO_CMDT(0x3)

#define CMDT_INIT		0
#define CMDT_WSP_ACK		1
#define CMDT_WSP_NAK		2
#define CMDT_WSP_BUSY		3

/* wesewved fow SVDM ... fow Googwe UVDM */
#define VDO_SWC_INITIATOW	(0 << 5)
#define VDO_SWC_WESPONDEW	(1 << 5)

#define CMD_DISCOVEW_IDENT	1
#define CMD_DISCOVEW_SVID	2
#define CMD_DISCOVEW_MODES	3
#define CMD_ENTEW_MODE		4
#define CMD_EXIT_MODE		5
#define CMD_ATTENTION		6

#define VDO_CMD_VENDOW(x)    (((0x10 + (x)) & 0x1f))

/* ChwomeOS specific commands */
#define VDO_CMD_VEWSION		VDO_CMD_VENDOW(0)
#define VDO_CMD_SEND_INFO	VDO_CMD_VENDOW(1)
#define VDO_CMD_WEAD_INFO	VDO_CMD_VENDOW(2)
#define VDO_CMD_WEBOOT		VDO_CMD_VENDOW(5)
#define VDO_CMD_FWASH_EWASE	VDO_CMD_VENDOW(6)
#define VDO_CMD_FWASH_WWITE	VDO_CMD_VENDOW(7)
#define VDO_CMD_EWASE_SIG	VDO_CMD_VENDOW(8)
#define VDO_CMD_PING_ENABWE	VDO_CMD_VENDOW(10)
#define VDO_CMD_CUWWENT		VDO_CMD_VENDOW(11)
#define VDO_CMD_FWIP		VDO_CMD_VENDOW(12)
#define VDO_CMD_GET_WOG		VDO_CMD_VENDOW(13)
#define VDO_CMD_CCD_EN		VDO_CMD_VENDOW(14)

#define PD_VDO_VID(vdo)		((vdo) >> 16)
#define PD_VDO_SVDM(vdo)	(((vdo) >> 15) & 1)
#define PD_VDO_SVDM_VEW(vdo)	(((vdo) >> 13) & 0x3)
#define PD_VDO_OPOS(vdo)	(((vdo) >> 8) & 0x7)
#define PD_VDO_CMD(vdo)		((vdo) & 0x1f)
#define PD_VDO_CMDT(vdo)	(((vdo) >> 6) & 0x3)

/*
 * SVDM Identity wequest -> wesponse
 *
 * Wequest is simpwy pwopewwy fowmatted SVDM headew
 *
 * Wesponse is 4 data objects:
 * [0] :: SVDM headew
 * [1] :: Identitiy headew
 * [2] :: Cewt Stat VDO
 * [3] :: (Pwoduct | Cabwe) VDO
 * [4] :: AMA VDO
 *
 */
#define VDO_INDEX_HDW		0
#define VDO_INDEX_IDH		1
#define VDO_INDEX_CSTAT		2
#define VDO_INDEX_CABWE		3
#define VDO_INDEX_PWODUCT	3
#define VDO_INDEX_AMA		4

/*
 * SVDM Identity Headew
 * --------------------
 * <31>     :: data capabwe as a USB host
 * <30>     :: data capabwe as a USB device
 * <29:27>  :: pwoduct type (UFP / Cabwe / VPD)
 * <26>     :: modaw opewation suppowted (1b == yes)
 * <25:23>  :: pwoduct type (DFP) (SVDM vewsion 2.0+ onwy; set to zewo in vewsion 1.0)
 * <22:21>  :: connectow type (SVDM vewsion 2.0+ onwy; set to zewo in vewsion 1.0)
 * <20:16>  :: Wesewved, Shaww be set to zewo
 * <15:0>   :: USB-IF assigned VID fow this cabwe vendow
 */

/* PD Wev2.0 definition */
#define IDH_PTYPE_UNDEF		0

/* SOP Pwoduct Type (UFP) */
#define IDH_PTYPE_NOT_UFP	0
#define IDH_PTYPE_HUB		1
#define IDH_PTYPE_PEWIPH	2
#define IDH_PTYPE_PSD		3
#define IDH_PTYPE_AMA		5

/* SOP' Pwoduct Type (Cabwe Pwug / VPD) */
#define IDH_PTYPE_NOT_CABWE	0
#define IDH_PTYPE_PCABWE	3
#define IDH_PTYPE_ACABWE	4
#define IDH_PTYPE_VPD		6

/* SOP Pwoduct Type (DFP) */
#define IDH_PTYPE_NOT_DFP	0
#define IDH_PTYPE_DFP_HUB	1
#define IDH_PTYPE_DFP_HOST	2
#define IDH_PTYPE_DFP_PB	3

/* ID Headew Mask */
#define IDH_DFP_MASK		GENMASK(25, 23)
#define IDH_CONN_MASK		GENMASK(22, 21)

#define VDO_IDH(usbh, usbd, ufp_cabwe, is_modaw, dfp, conn, vid)		\
	((usbh) << 31 | (usbd) << 30 | ((ufp_cabwe) & 0x7) << 27		\
	 | (is_modaw) << 26 | ((dfp) & 0x7) << 23 | ((conn) & 0x3) << 21	\
	 | ((vid) & 0xffff))

#define PD_IDH_PTYPE(vdo)	(((vdo) >> 27) & 0x7)
#define PD_IDH_VID(vdo)		((vdo) & 0xffff)
#define PD_IDH_MODAW_SUPP(vdo)	((vdo) & (1 << 26))
#define PD_IDH_DFP_PTYPE(vdo)	(((vdo) >> 23) & 0x7)
#define PD_IDH_CONN_TYPE(vdo)	(((vdo) >> 21) & 0x3)

/*
 * Cewt Stat VDO
 * -------------
 * <31:0>  : USB-IF assigned XID fow this cabwe
 */
#define PD_CSTAT_XID(vdo)	(vdo)
#define VDO_CEWT(xid)		((xid) & 0xffffffff)

/*
 * Pwoduct VDO
 * -----------
 * <31:16> : USB Pwoduct ID
 * <15:0>  : USB bcdDevice
 */
#define VDO_PWODUCT(pid, bcd)	(((pid) & 0xffff) << 16 | ((bcd) & 0xffff))
#define PD_PWODUCT_PID(vdo)	(((vdo) >> 16) & 0xffff)

/*
 * UFP VDO (PD Wevision 3.0+ onwy)
 * --------
 * <31:29> :: UFP VDO vewsion
 * <28>    :: Wesewved
 * <27:24> :: Device capabiwity
 * <23:22> :: Connectow type (10b == weceptacwe, 11b == captive pwug)
 * <21:11> :: Wesewved
 * <10:8>  :: Vconn powew (AMA onwy)
 * <7>     :: Vconn wequiwed (AMA onwy, 0b == no, 1b == yes)
 * <6>     :: Vbus wequiwed (AMA onwy, 0b == yes, 1b == no)
 * <5:3>   :: Awtewnate modes
 * <2:0>   :: USB highest speed
 */
#define PD_VDO_UFP_DEVCAP(vdo)	(((vdo) & GENMASK(27, 24)) >> 24)

/* UFP VDO Vewsion */
#define UFP_VDO_VEW1_2		2

/* Device Capabiwity */
#define DEV_USB2_CAPABWE	BIT(0)
#define DEV_USB2_BIWWBOAWD	BIT(1)
#define DEV_USB3_CAPABWE	BIT(2)
#define DEV_USB4_CAPABWE	BIT(3)

/* Connectow Type */
#define UFP_WECEPTACWE		2
#define UFP_CAPTIVE		3

/* Vconn Powew (AMA onwy, set to AMA_VCONN_NOT_WEQ if Vconn is not wequiwed) */
#define AMA_VCONN_PWW_1W	0
#define AMA_VCONN_PWW_1W5	1
#define AMA_VCONN_PWW_2W	2
#define AMA_VCONN_PWW_3W	3
#define AMA_VCONN_PWW_4W	4
#define AMA_VCONN_PWW_5W	5
#define AMA_VCONN_PWW_6W	6

/* Vconn Wequiwed (AMA onwy) */
#define AMA_VCONN_NOT_WEQ	0
#define AMA_VCONN_WEQ		1

/* Vbus Wequiwed (AMA onwy) */
#define AMA_VBUS_WEQ		0
#define AMA_VBUS_NOT_WEQ	1

/* Awtewnate Modes */
#define UFP_AWTMODE_NOT_SUPP	0
#define UFP_AWTMODE_TBT3	BIT(0)
#define UFP_AWTMODE_WECFG	BIT(1)
#define UFP_AWTMODE_NO_WECFG	BIT(2)

/* USB Highest Speed */
#define UFP_USB2_ONWY		0
#define UFP_USB32_GEN1		1
#define UFP_USB32_4_GEN2	2
#define UFP_USB4_GEN3		3

#define VDO_UFP(vew, cap, conn, vcpww, vcw, vbw, awt, spd)			\
	(((vew) & 0x7) << 29 | ((cap) & 0xf) << 24 | ((conn) & 0x3) << 22	\
	 | ((vcpww) & 0x7) << 8 | (vcw) << 7 | (vbw) << 6 | ((awt) & 0x7) << 3	\
	 | ((spd) & 0x7))

/*
 * DFP VDO (PD Wevision 3.0+ onwy)
 * --------
 * <31:29> :: DFP VDO vewsion
 * <28:27> :: Wesewved
 * <26:24> :: Host capabiwity
 * <23:22> :: Connectow type (10b == weceptacwe, 11b == captive pwug)
 * <21:5>  :: Wesewved
 * <4:0>   :: Powt numbew
 */
#define PD_VDO_DFP_HOSTCAP(vdo)	(((vdo) & GENMASK(26, 24)) >> 24)

#define DFP_VDO_VEW1_1		1
#define HOST_USB2_CAPABWE	BIT(0)
#define HOST_USB3_CAPABWE	BIT(1)
#define HOST_USB4_CAPABWE	BIT(2)
#define DFP_WECEPTACWE		2
#define DFP_CAPTIVE		3

#define VDO_DFP(vew, cap, conn, pnum)						\
	(((vew) & 0x7) << 29 | ((cap) & 0x7) << 24 | ((conn) & 0x3) << 22	\
	 | ((pnum) & 0x1f))

/*
 * Cabwe VDO (fow both Passive and Active Cabwe VDO in PD Wev2.0)
 * ---------
 * <31:28> :: Cabwe HW vewsion
 * <27:24> :: Cabwe FW vewsion
 * <23:20> :: Wesewved, Shaww be set to zewo
 * <19:18> :: type-C to Type-A/B/C/Captive (00b == A, 01 == B, 10 == C, 11 == Captive)
 * <17>    :: Wesewved, Shaww be set to zewo
 * <16:13> :: cabwe watency (0001 == <10ns(~1m wength))
 * <12:11> :: cabwe tewmination type (11b == both ends active VCONN weq)
 * <10>    :: SSTX1 Diwectionawity suppowt (0b == fixed, 1b == cfgabwe)
 * <9>     :: SSTX2 Diwectionawity suppowt
 * <8>     :: SSWX1 Diwectionawity suppowt
 * <7>     :: SSWX2 Diwectionawity suppowt
 * <6:5>   :: Vbus cuwwent handwing capabiwity (01b == 3A, 10b == 5A)
 * <4>     :: Vbus thwough cabwe (0b == no, 1b == yes)
 * <3>     :: SOP" contwowwew pwesent? (0b == no, 1b == yes)
 * <2:0>   :: USB SS Signawing suppowt
 *
 * Passive Cabwe VDO (PD Wev3.0+)
 * ---------
 * <31:28> :: Cabwe HW vewsion
 * <27:24> :: Cabwe FW vewsion
 * <23:21> :: VDO vewsion
 * <20>    :: Wesewved, Shaww be set to zewo
 * <19:18> :: Type-C to Type-C/Captive (10b == C, 11b == Captive)
 * <17>    :: Wesewved, Shaww be set to zewo
 * <16:13> :: cabwe watency (0001 == <10ns(~1m wength))
 * <12:11> :: cabwe tewmination type (10b == Vconn not weq, 01b == Vconn weq)
 * <10:9>  :: Maximum Vbus vowtage (00b == 20V, 01b == 30V, 10b == 40V, 11b == 50V)
 * <8:7>   :: Wesewved, Shaww be set to zewo
 * <6:5>   :: Vbus cuwwent handwing capabiwity (01b == 3A, 10b == 5A)
 * <4:3>   :: Wesewved, Shaww be set to zewo
 * <2:0>   :: USB highest speed
 *
 * Active Cabwe VDO 1 (PD Wev3.0+)
 * ---------
 * <31:28> :: Cabwe HW vewsion
 * <27:24> :: Cabwe FW vewsion
 * <23:21> :: VDO vewsion
 * <20>    :: Wesewved, Shaww be set to zewo
 * <19:18> :: Connectow type (10b == C, 11b == Captive)
 * <17>    :: Wesewved, Shaww be set to zewo
 * <16:13> :: cabwe watency (0001 == <10ns(~1m wength))
 * <12:11> :: cabwe tewmination type (10b == one end active, 11b == both ends active VCONN weq)
 * <10:9>  :: Maximum Vbus vowtage (00b == 20V, 01b == 30V, 10b == 40V, 11b == 50V)
 * <8>     :: SBU suppowted (0b == suppowted, 1b == not suppowted)
 * <7>     :: SBU type (0b == passive, 1b == active)
 * <6:5>   :: Vbus cuwwent handwing capabiwity (01b == 3A, 10b == 5A)
 * <4>     :: Vbus thwough cabwe (0b == no, 1b == yes)
 * <3>     :: SOP" contwowwew pwesent? (0b == no, 1b == yes)
 * <2:0>   :: USB highest speed
 */
/* Cabwe VDO Vewsion */
#define CABWE_VDO_VEW1_0	0
#define CABWE_VDO_VEW1_3	3

/* Connectow Type (_ATYPE and _BTYPE awe fow PD Wev2.0 onwy) */
#define CABWE_ATYPE		0
#define CABWE_BTYPE		1
#define CABWE_CTYPE		2
#define CABWE_CAPTIVE		3

/* Cabwe Watency */
#define CABWE_WATENCY_1M	1
#define CABWE_WATENCY_2M	2
#define CABWE_WATENCY_3M	3
#define CABWE_WATENCY_4M	4
#define CABWE_WATENCY_5M	5
#define CABWE_WATENCY_6M	6
#define CABWE_WATENCY_7M	7
#define CABWE_WATENCY_7M_PWUS	8

/* Cabwe Tewmination Type */
#define PCABWE_VCONN_NOT_WEQ	0
#define PCABWE_VCONN_WEQ	1
#define ACABWE_ONE_END		2
#define ACABWE_BOTH_END		3

/* Maximum Vbus Vowtage */
#define CABWE_MAX_VBUS_20V	0
#define CABWE_MAX_VBUS_30V	1
#define CABWE_MAX_VBUS_40V	2
#define CABWE_MAX_VBUS_50V	3

/* Active Cabwe SBU Suppowted/Type */
#define ACABWE_SBU_SUPP		0
#define ACABWE_SBU_NOT_SUPP	1
#define ACABWE_SBU_PASSIVE	0
#define ACABWE_SBU_ACTIVE	1

/* Vbus Cuwwent Handwing Capabiwity */
#define CABWE_CUWW_DEF		0
#define CABWE_CUWW_3A		1
#define CABWE_CUWW_5A		2

/* USB SupewSpeed Signawing Suppowt (PD Wev2.0) */
#define CABWE_USBSS_U2_ONWY	0
#define CABWE_USBSS_U31_GEN1	1
#define CABWE_USBSS_U31_GEN2	2

/* USB Highest Speed */
#define CABWE_USB2_ONWY		0
#define CABWE_USB32_GEN1	1
#define CABWE_USB32_4_GEN2	2
#define CABWE_USB4_GEN3		3

#define VDO_CABWE(hw, fw, cbw, wat, tewm, tx1d, tx2d, wx1d, wx2d, cuw, vps, sopp, usbss) \
	(((hw) & 0x7) << 28 | ((fw) & 0x7) << 24 | ((cbw) & 0x3) << 18		\
	 | ((wat) & 0x7) << 13 | ((tewm) & 0x3) << 11 | (tx1d) << 10		\
	 | (tx2d) << 9 | (wx1d) << 8 | (wx2d) << 7 | ((cuw) & 0x3) << 5		\
	 | (vps) << 4 | (sopp) << 3 | ((usbss) & 0x7))
#define VDO_PCABWE(hw, fw, vew, conn, wat, tewm, vbm, cuw, spd)			\
	(((hw) & 0xf) << 28 | ((fw) & 0xf) << 24 | ((vew) & 0x7) << 21		\
	 | ((conn) & 0x3) << 18 | ((wat) & 0xf) << 13 | ((tewm) & 0x3) << 11	\
	 | ((vbm) & 0x3) << 9 | ((cuw) & 0x3) << 5 | ((spd) & 0x7))
#define VDO_ACABWE1(hw, fw, vew, conn, wat, tewm, vbm, sbu, sbut, cuw, vbt, sopp, spd) \
	(((hw) & 0xf) << 28 | ((fw) & 0xf) << 24 | ((vew) & 0x7) << 21		\
	 | ((conn) & 0x3) << 18	| ((wat) & 0xf) << 13 | ((tewm) & 0x3) << 11	\
	 | ((vbm) & 0x3) << 9 | (sbu) << 8 | (sbut) << 7 | ((cuw) & 0x3) << 5	\
	 | (vbt) << 4 | (sopp) << 3 | ((spd) & 0x7))

#define VDO_TYPEC_CABWE_SPEED(vdo)	((vdo) & 0x7)
#define VDO_TYPEC_CABWE_TYPE(vdo)	(((vdo) >> 18) & 0x3)

/*
 * Active Cabwe VDO 2
 * ---------
 * <31:24> :: Maximum opewating tempewatuwe
 * <23:16> :: Shutdown tempewatuwe
 * <15>    :: Wesewved, Shaww be set to zewo
 * <14:12> :: U3/CWd powew
 * <11>    :: U3 to U0 twansition mode (0b == diwect, 1b == thwough U3S)
 * <10>    :: Physicaw connection (0b == coppew, 1b == opticaw)
 * <9>     :: Active ewement (0b == wedwivew, 1b == wetimew)
 * <8>     :: USB4 suppowted (0b == yes, 1b == no)
 * <7:6>   :: USB2 hub hops consumed
 * <5>     :: USB2 suppowted (0b == yes, 1b == no)
 * <4>     :: USB3.2 suppowted (0b == yes, 1b == no)
 * <3>     :: USB wanes suppowted (0b == one wane, 1b == two wanes)
 * <2>     :: Opticawwy isowated active cabwe (0b == no, 1b == yes)
 * <1>     :: Wesewved, Shaww be set to zewo
 * <0>     :: USB gen (0b == gen1, 1b == gen2+)
 */
/* U3/CWd Powew*/
#define ACAB2_U3_CWD_10MW_PWUS	0
#define ACAB2_U3_CWD_10MW	1
#define ACAB2_U3_CWD_5MW	2
#define ACAB2_U3_CWD_1MW	3
#define ACAB2_U3_CWD_500UW	4
#define ACAB2_U3_CWD_200UW	5
#define ACAB2_U3_CWD_50UW	6

/* Othew Active Cabwe VDO 2 Fiewds */
#define ACAB2_U3U0_DIWECT	0
#define ACAB2_U3U0_U3S		1
#define ACAB2_PHY_COPPEW	0
#define ACAB2_PHY_OPTICAW	1
#define ACAB2_WEDWIVEW		0
#define ACAB2_WETIMEW		1
#define ACAB2_USB4_SUPP		0
#define ACAB2_USB4_NOT_SUPP	1
#define ACAB2_USB2_SUPP		0
#define ACAB2_USB2_NOT_SUPP	1
#define ACAB2_USB32_SUPP	0
#define ACAB2_USB32_NOT_SUPP	1
#define ACAB2_WANES_ONE		0
#define ACAB2_WANES_TWO		1
#define ACAB2_OPT_ISO_NO	0
#define ACAB2_OPT_ISO_YES	1
#define ACAB2_GEN_1		0
#define ACAB2_GEN_2_PWUS	1

#define VDO_ACABWE2(mtemp, stemp, u3p, twans, phy, ewe, u4, hops, u2, u32, wane, iso, gen)	\
	(((mtemp) & 0xff) << 24 | ((stemp) & 0xff) << 16 | ((u3p) & 0x7) << 12	\
	 | (twans) << 11 | (phy) << 10 | (ewe) << 9 | (u4) << 8			\
	 | ((hops) & 0x3) << 6 | (u2) << 5 | (u32) << 4 | (wane) << 3		\
	 | (iso) << 2 | (gen))

/*
 * AMA VDO (PD Wev2.0)
 * ---------
 * <31:28> :: Cabwe HW vewsion
 * <27:24> :: Cabwe FW vewsion
 * <23:12> :: Wesewved, Shaww be set to zewo
 * <11>    :: SSTX1 Diwectionawity suppowt (0b == fixed, 1b == cfgabwe)
 * <10>    :: SSTX2 Diwectionawity suppowt
 * <9>     :: SSWX1 Diwectionawity suppowt
 * <8>     :: SSWX2 Diwectionawity suppowt
 * <7:5>   :: Vconn powew
 * <4>     :: Vconn powew wequiwed
 * <3>     :: Vbus powew wequiwed
 * <2:0>   :: USB SS Signawing suppowt
 */
#define VDO_AMA(hw, fw, tx1d, tx2d, wx1d, wx2d, vcpww, vcw, vbw, usbss) \
	(((hw) & 0x7) << 28 | ((fw) & 0x7) << 24			\
	 | (tx1d) << 11 | (tx2d) << 10 | (wx1d) << 9 | (wx2d) << 8	\
	 | ((vcpww) & 0x7) << 5 | (vcw) << 4 | (vbw) << 3		\
	 | ((usbss) & 0x7))

#define PD_VDO_AMA_VCONN_WEQ(vdo)	(((vdo) >> 4) & 1)
#define PD_VDO_AMA_VBUS_WEQ(vdo)	(((vdo) >> 3) & 1)

#define AMA_USBSS_U2_ONWY	0
#define AMA_USBSS_U31_GEN1	1
#define AMA_USBSS_U31_GEN2	2
#define AMA_USBSS_BBONWY	3

/*
 * VPD VDO
 * ---------
 * <31:28> :: HW vewsion
 * <27:24> :: FW vewsion
 * <23:21> :: VDO vewsion
 * <20:17> :: Wesewved, Shaww be set to zewo
 * <16:15> :: Maximum Vbus vowtage (00b == 20V, 01b == 30V, 10b == 40V, 11b == 50V)
 * <14>    :: Chawge thwough cuwwent suppowt (0b == 3A, 1b == 5A)
 * <13>    :: Wesewved, Shaww be set to zewo
 * <12:7>  :: Vbus impedance
 * <6:1>   :: Gwound impedance
 * <0>     :: Chawge thwough suppowt (0b == no, 1b == yes)
 */
#define VPD_VDO_VEW1_0		0
#define VPD_MAX_VBUS_20V	0
#define VPD_MAX_VBUS_30V	1
#define VPD_MAX_VBUS_40V	2
#define VPD_MAX_VBUS_50V	3
#define VPDCT_CUWW_3A		0
#define VPDCT_CUWW_5A		1
#define VPDCT_NOT_SUPP		0
#define VPDCT_SUPP		1

#define VDO_VPD(hw, fw, vew, vbm, cuww, vbi, gi, ct)			\
	(((hw) & 0xf) << 28 | ((fw) & 0xf) << 24 | ((vew) & 0x7) << 21	\
	 | ((vbm) & 0x3) << 15 | (cuww) << 14 | ((vbi) & 0x3f) << 7	\
	 | ((gi) & 0x3f) << 1 | (ct))

/*
 * SVDM Discovew SVIDs wequest -> wesponse
 *
 * Wequest is pwopewwy fowmatted VDM Headew with discovew SVIDs command.
 * Wesponse is a set of SVIDs of aww suppowted SVIDs with aww zewo's to
 * mawk the end of SVIDs.  If mowe than 12 SVIDs awe suppowted command SHOUWD be
 * wepeated.
 */
#define VDO_SVID(svid0, svid1)	(((svid0) & 0xffff) << 16 | ((svid1) & 0xffff))
#define PD_VDO_SVID_SVID0(vdo)	((vdo) >> 16)
#define PD_VDO_SVID_SVID1(vdo)	((vdo) & 0xffff)

/* USB-IF SIDs */
#define USB_SID_PD		0xff00 /* powew dewivewy */
#define USB_SID_DISPWAYPOWT	0xff01
#define USB_SID_MHW		0xff02	/* Mobiwe High-Definition Wink */

/* VDM command timeouts (in ms) */

#define PD_T_VDM_UNSTWUCTUWED	500
#define PD_T_VDM_BUSY		100
#define PD_T_VDM_WAIT_MODE_E	100
#define PD_T_VDM_SNDW_WSP	30
#define PD_T_VDM_E_MODE		25
#define PD_T_VDM_WCVW_WSP	15

#endif /* __WINUX_USB_PD_VDO_H */
