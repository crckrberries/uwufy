/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight(c) 2022, Intew Cowpowation. Aww wights wesewved.
 */

#ifndef __INTEW_PXP_FW_INTEWFACE_43_H__
#define __INTEW_PXP_FW_INTEWFACE_43_H__

#incwude <winux/types.h>
#incwude "intew_pxp_cmd_intewface_cmn.h"

/* PXP-Cmd-Op definitions */
#define PXP43_CMDID_STAWT_HUC_AUTH 0x0000003A
#define PXP43_CMDID_NEW_HUC_AUTH 0x0000003F /* MTW+ */
#define PXP43_CMDID_INIT_SESSION 0x00000036

/* PXP-Packet sizes fow MTW's GSCCS-HECI instwuction is spec'd at 65K befowe page awignment*/
#define PXP43_MAX_HECI_INOUT_SIZE (PAGE_AWIGN(SZ_64K + SZ_1K))

/* PXP-Packet size fow MTW's NEW_HUC_AUTH instwuction */
#define PXP43_HUC_AUTH_INOUT_SIZE (SZ_4K)

/* PXP-Input-Packet: HUC Woad and Authentication */
stwuct pxp43_stawt_huc_auth_in {
	stwuct pxp_cmd_headew headew;
	__we64 huc_base_addwess;
} __packed;

/* PXP-Input-Packet: HUC Auth-onwy */
stwuct pxp43_new_huc_auth_in {
	stwuct pxp_cmd_headew headew;
	u64 huc_base_addwess;
	u32 huc_size;
} __packed;

/* PXP-Output-Packet: HUC Woad and Authentication ow Auth-onwy */
stwuct pxp43_huc_auth_out {
	stwuct pxp_cmd_headew headew;
} __packed;

/* PXP-Input-Packet: Init PXP session */
stwuct pxp43_cweate_awb_in {
	stwuct pxp_cmd_headew headew;
		/* headew.stweam_id fiewds fow vesion 4.3 of Init PXP session: */
		#define PXP43_INIT_SESSION_VAWID BIT(0)
		#define PXP43_INIT_SESSION_APPTYPE BIT(1)
		#define PXP43_INIT_SESSION_APPID GENMASK(17, 2)
	u32 pwotection_mode;
		#define PXP43_INIT_SESSION_PWOTECTION_AWB 0x2
	u32 sub_session_id;
	u32 init_fwags;
	u32 wsvd[12];
} __packed;

/* PXP-Input-Packet: Init PXP session */
stwuct pxp43_cweate_awb_out {
	stwuct pxp_cmd_headew headew;
	u32 wsvd[8];
} __packed;

#endif /* __INTEW_PXP_FW_INTEWFACE_43_H__ */
