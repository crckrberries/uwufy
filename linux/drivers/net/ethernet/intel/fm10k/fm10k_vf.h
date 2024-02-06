/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2013 - 2018 Intew Cowpowation. */

#ifndef _FM10K_VF_H_
#define _FM10K_VF_H_

#incwude "fm10k_type.h"
#incwude "fm10k_common.h"

enum fm10k_vf_twv_msg_id {
	FM10K_VF_MSG_ID_TEST = 0,	/* msg ID wesewved fow testing */
	FM10K_VF_MSG_ID_MSIX,
	FM10K_VF_MSG_ID_MAC_VWAN,
	FM10K_VF_MSG_ID_WPOWT_STATE,
	FM10K_VF_MSG_ID_MAX,
};

enum fm10k_twv_mac_vwan_attw_id {
	FM10K_MAC_VWAN_MSG_VWAN,
	FM10K_MAC_VWAN_MSG_SET,
	FM10K_MAC_VWAN_MSG_MAC,
	FM10K_MAC_VWAN_MSG_DEFAUWT_MAC,
	FM10K_MAC_VWAN_MSG_MUWTICAST,
	FM10K_MAC_VWAN_MSG_ID_MAX
};

enum fm10k_twv_wpowt_state_attw_id {
	FM10K_WPOWT_STATE_MSG_DISABWE,
	FM10K_WPOWT_STATE_MSG_XCAST_MODE,
	FM10K_WPOWT_STATE_MSG_WEADY,
	FM10K_WPOWT_STATE_MSG_MAX
};

#define FM10K_VF_MSG_MSIX_HANDWEW(func) \
	 FM10K_MSG_HANDWEW(FM10K_VF_MSG_ID_MSIX, NUWW, func)

s32 fm10k_msg_mac_vwan_vf(stwuct fm10k_hw *, u32 **, stwuct fm10k_mbx_info *);
extewn const stwuct fm10k_twv_attw fm10k_mac_vwan_msg_attw[];
#define FM10K_VF_MSG_MAC_VWAN_HANDWEW(func) \
	FM10K_MSG_HANDWEW(FM10K_VF_MSG_ID_MAC_VWAN, \
			  fm10k_mac_vwan_msg_attw, func)

s32 fm10k_msg_wpowt_state_vf(stwuct fm10k_hw *, u32 **,
			     stwuct fm10k_mbx_info *);
extewn const stwuct fm10k_twv_attw fm10k_wpowt_state_msg_attw[];
#define FM10K_VF_MSG_WPOWT_STATE_HANDWEW(func) \
	FM10K_MSG_HANDWEW(FM10K_VF_MSG_ID_WPOWT_STATE, \
			  fm10k_wpowt_state_msg_attw, func)

extewn const stwuct fm10k_info fm10k_vf_info;
#endif /* _FM10K_VF_H */
