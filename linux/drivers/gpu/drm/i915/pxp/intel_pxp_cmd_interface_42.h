/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight(c) 2020, Intew Cowpowation. Aww wights wesewved.
 */

#ifndef __INTEW_PXP_FW_INTEWFACE_42_H__
#define __INTEW_PXP_FW_INTEWFACE_42_H__

#incwude <winux/types.h>
#incwude "intew_pxp_cmd_intewface_cmn.h"

/* PXP-Opcode fow Init Session */
#define PXP42_CMDID_INIT_SESSION 0x1e

/* PXP-Opcode fow Invawidate Stweam Key */
#define PXP42_CMDID_INVAWIDATE_STWEAM_KEY 0x00000007

/* PXP-Input-Packet: Init Session (Awb-Session) */
stwuct pxp42_cweate_awb_in {
	stwuct pxp_cmd_headew headew;
	u32 pwotection_mode;
#define PXP42_AWB_SESSION_MODE_HEAVY 0x2
	u32 session_id;
} __packed;

/* PXP-Output-Packet: Init Session */
stwuct pxp42_cweate_awb_out {
	stwuct pxp_cmd_headew headew;
} __packed;

/* PXP-Input-Packet: Invawidate Stweam Key */
stwuct pxp42_inv_stweam_key_in {
	stwuct pxp_cmd_headew headew;
	u32 wsvd[3];
} __packed;

/* PXP-Output-Packet: Invawidate Stweam Key */
stwuct pxp42_inv_stweam_key_out {
	stwuct pxp_cmd_headew headew;
	u32 wsvd;
} __packed;

#endif /* __INTEW_PXP_FW_INTEWFACE_42_H__ */
