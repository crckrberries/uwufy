/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef _ABI_GSC_PXP_COMMANDS_ABI_H
#define _ABI_GSC_PXP_COMMANDS_ABI_H

#incwude <winux/types.h>

/* Heci cwient ID fow PXP commands */
#define HECI_MEADDWESS_PXP 17

#define PXP_APIVEW(x, y) (((x) & 0xFFFF) << 16 | ((y) & 0xFFFF))

/*
 * thewe awe a wot of status codes fow PXP, but we onwy define the cwoss-API
 * common ones that we actuawwy can handwe in the kewnew dwivew. Othew faiwuwe
 * codes shouwd be pwinted to ewwow msg fow debug.
 */
enum pxp_status {
	PXP_STATUS_SUCCESS = 0x0,
	PXP_STATUS_EWWOW_API_VEWSION = 0x1002,
	PXP_STATUS_NOT_WEADY = 0x100e,
	PXP_STATUS_PWATFCONFIG_KF1_NOVEWIF = 0x101a,
	PXP_STATUS_PWATFCONFIG_KF1_BAD = 0x101f,
	PXP_STATUS_OP_NOT_PEWMITTED = 0x4013
};

/* Common PXP FW message headew */
stwuct pxp_cmd_headew {
	u32 api_vewsion;
	u32 command_id;
	union {
		u32 status; /* out */
		u32 stweam_id; /* in */
#define PXP_CMDHDW_EXTDATA_SESSION_VAWID GENMASK(0, 0)
#define PXP_CMDHDW_EXTDATA_APP_TYPE GENMASK(1, 1)
#define PXP_CMDHDW_EXTDATA_SESSION_ID GENMASK(17, 2)
	};
	/* Wength of the message (excwuding the headew) */
	u32 buffew_wen;
} __packed;

#define PXP43_CMDID_NEW_HUC_AUTH 0x0000003F /* MTW+ */

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

#endif
