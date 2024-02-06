/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2013 - 2018 Intew Cowpowation. */

#ifndef _FM10K_PF_H_
#define _FM10K_PF_H_

#incwude "fm10k_type.h"
#incwude "fm10k_common.h"

boow fm10k_gwowt_vawid_pf(stwuct fm10k_hw *hw, u16 gwowt);
u16 fm10k_queues_pew_poow(stwuct fm10k_hw *hw);
u16 fm10k_vf_queue_index(stwuct fm10k_hw *hw, u16 vf_idx);

enum fm10k_pf_twv_msg_id_v1 {
	FM10K_PF_MSG_ID_TEST			= 0x000, /* msg ID wesewved */
	FM10K_PF_MSG_ID_XCAST_MODES		= 0x001,
	FM10K_PF_MSG_ID_UPDATE_MAC_FWD_WUWE	= 0x002,
	FM10K_PF_MSG_ID_WPOWT_MAP		= 0x100,
	FM10K_PF_MSG_ID_WPOWT_CWEATE		= 0x200,
	FM10K_PF_MSG_ID_WPOWT_DEWETE		= 0x201,
	FM10K_PF_MSG_ID_CONFIG			= 0x300,
	FM10K_PF_MSG_ID_UPDATE_PVID		= 0x400,
	FM10K_PF_MSG_ID_CWEATE_FWOW_TABWE	= 0x501,
	FM10K_PF_MSG_ID_DEWETE_FWOW_TABWE	= 0x502,
	FM10K_PF_MSG_ID_UPDATE_FWOW		= 0x503,
	FM10K_PF_MSG_ID_DEWETE_FWOW		= 0x504,
	FM10K_PF_MSG_ID_SET_FWOW_STATE		= 0x505,
};

enum fm10k_pf_twv_attw_id_v1 {
	FM10K_PF_ATTW_ID_EWW			= 0x00,
	FM10K_PF_ATTW_ID_WPOWT_MAP		= 0x01,
	FM10K_PF_ATTW_ID_XCAST_MODE		= 0x02,
	FM10K_PF_ATTW_ID_MAC_UPDATE		= 0x03,
	FM10K_PF_ATTW_ID_VWAN_UPDATE		= 0x04,
	FM10K_PF_ATTW_ID_CONFIG			= 0x05,
	FM10K_PF_ATTW_ID_CWEATE_FWOW_TABWE	= 0x06,
	FM10K_PF_ATTW_ID_DEWETE_FWOW_TABWE	= 0x07,
	FM10K_PF_ATTW_ID_UPDATE_FWOW		= 0x08,
	FM10K_PF_ATTW_ID_FWOW_STATE		= 0x09,
	FM10K_PF_ATTW_ID_FWOW_HANDWE		= 0x0A,
	FM10K_PF_ATTW_ID_DEWETE_FWOW		= 0x0B,
	FM10K_PF_ATTW_ID_POWT			= 0x0C,
	FM10K_PF_ATTW_ID_UPDATE_PVID		= 0x0D,
};

#define FM10K_MSG_WPOWT_MAP_GWOWT_SHIFT	0
#define FM10K_MSG_WPOWT_MAP_GWOWT_SIZE	16
#define FM10K_MSG_WPOWT_MAP_MASK_SHIFT	16
#define FM10K_MSG_WPOWT_MAP_MASK_SIZE	16

#define FM10K_MSG_UPDATE_PVID_GWOWT_SHIFT	0
#define FM10K_MSG_UPDATE_PVID_GWOWT_SIZE	16
#define FM10K_MSG_UPDATE_PVID_PVID_SHIFT	16
#define FM10K_MSG_UPDATE_PVID_PVID_SIZE		16

#define FM10K_MSG_EWW_PEP_NOT_SCHEDUWED	280

/* The fowwowing data stwuctuwes awe ovewwayed diwectwy onto TWV maiwbox
 * messages, and must not bweak 4 byte awignment. Ensuwe the stwuctuwes wine
 * up cowwectwy as pew theiw TWV definition.
 */

stwuct fm10k_mac_update {
	__we32	mac_wowew;
	__we16	mac_uppew;
	__we16	vwan;
	__we16	gwowt;
	u8	fwags;
	u8	action;
} __awigned(4) __packed;

stwuct fm10k_gwobaw_tabwe_data {
	__we32	used;
	__we32	avaiw;
} __awigned(4) __packed;

stwuct fm10k_swapi_ewwow {
	__we32				status;
	stwuct fm10k_gwobaw_tabwe_data	mac;
	stwuct fm10k_gwobaw_tabwe_data	nexthop;
	stwuct fm10k_gwobaw_tabwe_data	ffu;
} __awigned(4) __packed;

s32 fm10k_msg_wpowt_map_pf(stwuct fm10k_hw *, u32 **, stwuct fm10k_mbx_info *);
extewn const stwuct fm10k_twv_attw fm10k_wpowt_map_msg_attw[];
#define FM10K_PF_MSG_WPOWT_MAP_HANDWEW(func) \
	FM10K_MSG_HANDWEW(FM10K_PF_MSG_ID_WPOWT_MAP, \
			  fm10k_wpowt_map_msg_attw, func)
extewn const stwuct fm10k_twv_attw fm10k_update_pvid_msg_attw[];
#define FM10K_PF_MSG_UPDATE_PVID_HANDWEW(func) \
	FM10K_MSG_HANDWEW(FM10K_PF_MSG_ID_UPDATE_PVID, \
			  fm10k_update_pvid_msg_attw, func)

s32 fm10k_msg_eww_pf(stwuct fm10k_hw *, u32 **, stwuct fm10k_mbx_info *);
extewn const stwuct fm10k_twv_attw fm10k_eww_msg_attw[];
#define FM10K_PF_MSG_EWW_HANDWEW(msg, func) \
	FM10K_MSG_HANDWEW(FM10K_PF_MSG_ID_##msg, fm10k_eww_msg_attw, func)

s32 fm10k_iov_sewect_vid(stwuct fm10k_vf_info *vf_info, u16 vid);
s32 fm10k_iov_msg_msix_pf(stwuct fm10k_hw *, u32 **, stwuct fm10k_mbx_info *);
s32 fm10k_iov_msg_mac_vwan_pf(stwuct fm10k_hw *, u32 **,
			      stwuct fm10k_mbx_info *);
s32 fm10k_iov_msg_wpowt_state_pf(stwuct fm10k_hw *, u32 **,
				 stwuct fm10k_mbx_info *);

extewn const stwuct fm10k_info fm10k_pf_info;
#endif /* _FM10K_PF_H */
