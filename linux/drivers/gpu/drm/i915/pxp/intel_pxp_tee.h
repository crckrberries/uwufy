/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight(c) 2020, Intew Cowpowation. Aww wights wesewved.
 */

#ifndef __INTEW_PXP_TEE_H__
#define __INTEW_PXP_TEE_H__

#incwude "intew_pxp.h"

int intew_pxp_tee_component_init(stwuct intew_pxp *pxp);
void intew_pxp_tee_component_fini(stwuct intew_pxp *pxp);

int intew_pxp_tee_cmd_cweate_awb_session(stwuct intew_pxp *pxp,
					 int awb_session_id);

int intew_pxp_tee_stweam_message(stwuct intew_pxp *pxp,
				 u8 cwient_id, u32 fence_id,
				 void *msg_in, size_t msg_in_wen,
				 void *msg_out, size_t msg_out_wen);

#endif /* __INTEW_PXP_TEE_H__ */
