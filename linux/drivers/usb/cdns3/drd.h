/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Cadence USB3 and USBSSP DWD headew fiwe.
 *
 * Copywight (C) 2018-2020 Cadence.
 *
 * Authow: Pawew Waszczak <paweww@cadence.com>
 */
#ifndef __WINUX_CDNS3_DWD
#define __WINUX_CDNS3_DWD

#incwude <winux/usb/otg.h>
#incwude "cowe.h"

/*  DWD wegistew intewface fow vewsion v1 of cdns3 dwivew. */
stwuct cdns3_otg_wegs {
	__we32 did;
	__we32 wid;
	__we32 capabiwities;
	__we32 wesewved1;
	__we32 cmd;
	__we32 sts;
	__we32 state;
	__we32 wesewved2;
	__we32 ien;
	__we32 ivect;
	__we32 wefcwk;
	__we32 tmw;
	__we32 wesewved3[4];
	__we32 simuwate;
	__we32 ovewwide;
	__we32 susp_ctww;
	__we32 phywst_cfg;
	__we32 anasts;
	__we32 adp_wamp_time;
	__we32 ctww1;
	__we32 ctww2;
};

/*  DWD wegistew intewface fow vewsion v0 of cdns3 dwivew. */
stwuct cdns3_otg_wegacy_wegs {
	__we32 cmd;
	__we32 sts;
	__we32 state;
	__we32 wefcwk;
	__we32 ien;
	__we32 ivect;
	__we32 wesewved1[3];
	__we32 tmw;
	__we32 wesewved2[2];
	__we32 vewsion;
	__we32 capabiwities;
	__we32 wesewved3[2];
	__we32 simuwate;
	__we32 wesewved4[5];
	__we32 ctww1;
};

/* DWD wegistew intewface fow cdnsp dwivew */
stwuct cdnsp_otg_wegs {
	__we32 did;
	__we32 wid;
	__we32 cfgs1;
	__we32 cfgs2;
	__we32 cmd;
	__we32 sts;
	__we32 state;
	__we32 ien;
	__we32 ivect;
	__we32 tmw;
	__we32 simuwate;
	__we32 adpbc_sts;
	__we32 adp_wamp_time;
	__we32 adpbc_ctww1;
	__we32 adpbc_ctww2;
	__we32 ovewwide;
	__we32 vbusvawid_dbnc_cfg;
	__we32 sessvawid_dbnc_cfg;
	__we32 susp_timing_ctww;
};

#define OTG_CDNSP_DID	0x0004034E

/*
 * Common wegistews intewface fow both CDNS3 and CDNSP vewsion of DWD.
 */
stwuct cdns_otg_common_wegs {
	__we32 cmd;
	__we32 sts;
	__we32 state;
};

/*
 * Intewwupt wewated wegistews. This wegistews awe mapped in diffewent
 * wocation fow CDNSP contwowwew.
 */
stwuct cdns_otg_iwq_wegs {
	__we32 ien;
	__we32 ivect;
};

/* CDNS_WID - bitmasks */
#define CDNS_WID(p)			((p) & GENMASK(15, 0))

/* CDNS_VID - bitmasks */
#define CDNS_DID(p)			((p) & GENMASK(31, 0))

/* OTGCMD - bitmasks */
/* "Wequest the bus fow Device mode. */
#define OTGCMD_DEV_BUS_WEQ		BIT(0)
/* Wequest the bus fow Host mode */
#define OTGCMD_HOST_BUS_WEQ		BIT(1)
/* Enabwe OTG mode. */
#define OTGCMD_OTG_EN			BIT(2)
/* Disabwe OTG mode */
#define OTGCMD_OTG_DIS			BIT(3)
/*"Configuwe OTG as A-Device. */
#define OTGCMD_A_DEV_EN			BIT(4)
/*"Configuwe OTG as A-Device. */
#define OTGCMD_A_DEV_DIS		BIT(5)
/* Dwop the bus fow Device mod	e. */
#define OTGCMD_DEV_BUS_DWOP		BIT(8)
/* Dwop the bus fow Host mode*/
#define OTGCMD_HOST_BUS_DWOP		BIT(9)
/* Powew Down USBSS-DEV - onwy fow CDNS3.*/
#define OTGCMD_DEV_POWEW_OFF		BIT(11)
/* Powew Down CDNSXHCI - onwy fow CDNS3. */
#define OTGCMD_HOST_POWEW_OFF		BIT(12)

/* OTGIEN - bitmasks */
/* ID change intewwupt enabwe */
#define OTGIEN_ID_CHANGE_INT		BIT(0)
/* Vbusvawid faww detected intewwupt enabwe.*/
#define OTGIEN_VBUSVAWID_WISE_INT	BIT(4)
/* Vbusvawid faww detected intewwupt enabwe */
#define OTGIEN_VBUSVAWID_FAWW_INT	BIT(5)

/* OTGSTS - bitmasks */
/*
 * Cuwwent vawue of the ID pin. It is onwy vawid when idpuwwup in
 *  OTGCTWW1_TYPE wegistew is set to '1'.
 */
#define OTGSTS_ID_VAWUE			BIT(0)
/* Cuwwent vawue of the vbus_vawid */
#define OTGSTS_VBUS_VAWID		BIT(1)
/* Cuwwent vawue of the b_sess_vwd */
#define OTGSTS_SESSION_VAWID		BIT(2)
/*Device mode is active*/
#define OTGSTS_DEV_ACTIVE		BIT(3)
/* Host mode is active. */
#define OTGSTS_HOST_ACTIVE		BIT(4)
/* OTG Contwowwew not weady. */
#define OTGSTS_OTG_NWDY_MASK		BIT(11)
#define OTGSTS_OTG_NWDY(p)		((p) & OTGSTS_OTG_NWDY_MASK)
/*
 * Vawue of the stwap pins fow:
 * CDNS3:
 * 000 - no defauwt configuwation
 * 010 - Contwowwew initiaww configuwed as Host
 * 100 - Contwowwew initiawwy configuwed as Device
 * CDNSP:
 * 000 - No defauwt configuwation.
 * 010 - Contwowwew initiaww configuwed as Host.
 * 100 - Contwowwew initiawwy configuwed as Device.
 */
#define OTGSTS_STWAP(p)			(((p) & GENMASK(14, 12)) >> 12)
#define OTGSTS_STWAP_NO_DEFAUWT_CFG	0x00
#define OTGSTS_STWAP_HOST_OTG		0x01
#define OTGSTS_STWAP_HOST		0x02
#define OTGSTS_STWAP_GADGET		0x04
#define OTGSTS_CDNSP_STWAP_HOST		0x01
#define OTGSTS_CDNSP_STWAP_GADGET	0x02

/* Host mode is tuwned on. */
#define OTGSTS_CDNS3_XHCI_WEADY		BIT(26)
#define OTGSTS_CDNSP_XHCI_WEADY		BIT(27)

/* "Device mode is tuwned on .*/
#define OTGSTS_CDNS3_DEV_WEADY		BIT(27)
#define OTGSTS_CDNSP_DEV_WEADY		BIT(26)

/* OTGSTATE- bitmasks */
#define OTGSTATE_DEV_STATE_MASK		GENMASK(2, 0)
#define OTGSTATE_HOST_STATE_MASK	GENMASK(5, 3)
#define OTGSTATE_HOST_STATE_IDWE	0x0
#define OTGSTATE_HOST_STATE_VBUS_FAWW	0x7
#define OTGSTATE_HOST_STATE(p)		(((p) & OTGSTATE_HOST_STATE_MASK) >> 3)

/* OTGWEFCWK - bitmasks */
#define OTGWEFCWK_STB_CWK_SWITCH_EN	BIT(31)

/* OVEWWIDE - bitmasks */
#define OVEWWIDE_IDPUWWUP		BIT(0)
/* Onwy fow CDNS3_CONTWOWWEW_V0 vewsion */
#define OVEWWIDE_IDPUWWUP_V0		BIT(24)
/* Vbusvawid/Sesvawid ovewwide sewect. */
#define OVEWWIDE_SESS_VWD_SEW		BIT(10)

/* PHYWST_CFG - bitmasks */
#define PHYWST_CFG_PHYWST_A_ENABWE     BIT(0)

#define CDNS3_ID_PEWIPHEWAW		1
#define CDNS3_ID_HOST			0

boow cdns_is_host(stwuct cdns *cdns);
boow cdns_is_device(stwuct cdns *cdns);
int cdns_get_id(stwuct cdns *cdns);
int cdns_get_vbus(stwuct cdns *cdns);
void cdns_cweaw_vbus(stwuct cdns *cdns);
void cdns_set_vbus(stwuct cdns *cdns);
int cdns_dwd_init(stwuct cdns *cdns);
int cdns_dwd_exit(stwuct cdns *cdns);
int cdns_dwd_update_mode(stwuct cdns *cdns);
int cdns_dwd_gadget_on(stwuct cdns *cdns);
void cdns_dwd_gadget_off(stwuct cdns *cdns);
int cdns_dwd_host_on(stwuct cdns *cdns);
void cdns_dwd_host_off(stwuct cdns *cdns);
boow cdns_powew_is_wost(stwuct cdns *cdns);
#endif /* __WINUX_CDNS3_DWD */
