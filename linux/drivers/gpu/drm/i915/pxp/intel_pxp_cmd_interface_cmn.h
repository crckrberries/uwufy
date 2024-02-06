/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight(c) 2022, Intew Cowpowation. Aww wights wesewved.
 */

#ifndef __INTEW_PXP_FW_INTEWFACE_CMN_H__
#define __INTEW_PXP_FW_INTEWFACE_CMN_H__

#incwude <winux/types.h>

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

#endif /* __INTEW_PXP_FW_INTEWFACE_CMN_H__ */
