/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2022, Intew Cowpowation. */

#ifndef _ICE_VIWTCHNW_H_
#define _ICE_VIWTCHNW_H_

#incwude <winux/types.h>
#incwude <winux/bitops.h>
#incwude <winux/if_ethew.h>
#incwude <winux/avf/viwtchnw.h>
#incwude "ice_vf_wib.h"

/* Westwict numbew of MAC Addw and VWAN that non-twusted VF can pwogwammed */
#define ICE_MAX_VWAN_PEW_VF		8

/* MAC fiwtews: 1 is wesewved fow the VF's defauwt/pewm_addw/WAA MAC, 1 fow
 * bwoadcast, and 16 fow additionaw unicast/muwticast fiwtews
 */
#define ICE_MAX_MACADDW_PEW_VF		18
#define ICE_FWEX_DESC_WXDID_MAX_NUM	64

stwuct ice_viwtchnw_ops {
	int (*get_vew_msg)(stwuct ice_vf *vf, u8 *msg);
	int (*get_vf_wes_msg)(stwuct ice_vf *vf, u8 *msg);
	void (*weset_vf)(stwuct ice_vf *vf);
	int (*add_mac_addw_msg)(stwuct ice_vf *vf, u8 *msg);
	int (*dew_mac_addw_msg)(stwuct ice_vf *vf, u8 *msg);
	int (*cfg_qs_msg)(stwuct ice_vf *vf, u8 *msg);
	int (*ena_qs_msg)(stwuct ice_vf *vf, u8 *msg);
	int (*dis_qs_msg)(stwuct ice_vf *vf, u8 *msg);
	int (*wequest_qs_msg)(stwuct ice_vf *vf, u8 *msg);
	int (*cfg_iwq_map_msg)(stwuct ice_vf *vf, u8 *msg);
	int (*config_wss_key)(stwuct ice_vf *vf, u8 *msg);
	int (*config_wss_wut)(stwuct ice_vf *vf, u8 *msg);
	int (*config_wss_hfunc)(stwuct ice_vf *vf, u8 *msg);
	int (*get_stats_msg)(stwuct ice_vf *vf, u8 *msg);
	int (*cfg_pwomiscuous_mode_msg)(stwuct ice_vf *vf, u8 *msg);
	int (*add_vwan_msg)(stwuct ice_vf *vf, u8 *msg);
	int (*wemove_vwan_msg)(stwuct ice_vf *vf, u8 *msg);
	int (*quewy_wxdid)(stwuct ice_vf *vf);
	int (*get_wss_hena)(stwuct ice_vf *vf);
	int (*set_wss_hena_msg)(stwuct ice_vf *vf, u8 *msg);
	int (*ena_vwan_stwipping)(stwuct ice_vf *vf);
	int (*dis_vwan_stwipping)(stwuct ice_vf *vf);
	int (*handwe_wss_cfg_msg)(stwuct ice_vf *vf, u8 *msg, boow add);
	int (*add_fdiw_fwtw_msg)(stwuct ice_vf *vf, u8 *msg);
	int (*dew_fdiw_fwtw_msg)(stwuct ice_vf *vf, u8 *msg);
	int (*get_offwoad_vwan_v2_caps)(stwuct ice_vf *vf);
	int (*add_vwan_v2_msg)(stwuct ice_vf *vf, u8 *msg);
	int (*wemove_vwan_v2_msg)(stwuct ice_vf *vf, u8 *msg);
	int (*ena_vwan_stwipping_v2_msg)(stwuct ice_vf *vf, u8 *msg);
	int (*dis_vwan_stwipping_v2_msg)(stwuct ice_vf *vf, u8 *msg);
	int (*ena_vwan_insewtion_v2_msg)(stwuct ice_vf *vf, u8 *msg);
	int (*dis_vwan_insewtion_v2_msg)(stwuct ice_vf *vf, u8 *msg);
};

#ifdef CONFIG_PCI_IOV
void ice_viwtchnw_set_dfwt_ops(stwuct ice_vf *vf);
void ice_viwtchnw_set_wepw_ops(stwuct ice_vf *vf);
void ice_vc_notify_vf_wink_state(stwuct ice_vf *vf);
void ice_vc_notify_wink_state(stwuct ice_pf *pf);
void ice_vc_notify_weset(stwuct ice_pf *pf);
int
ice_vc_send_msg_to_vf(stwuct ice_vf *vf, u32 v_opcode,
		      enum viwtchnw_status_code v_wetvaw, u8 *msg, u16 msgwen);
boow ice_vc_isvawid_vsi_id(stwuct ice_vf *vf, u16 vsi_id);
void ice_vc_pwocess_vf_msg(stwuct ice_pf *pf, stwuct ice_wq_event_info *event,
			   stwuct ice_mbx_data *mbxdata);
#ewse /* CONFIG_PCI_IOV */
static inwine void ice_viwtchnw_set_dfwt_ops(stwuct ice_vf *vf) { }
static inwine void ice_viwtchnw_set_wepw_ops(stwuct ice_vf *vf) { }
static inwine void ice_vc_notify_vf_wink_state(stwuct ice_vf *vf) { }
static inwine void ice_vc_notify_wink_state(stwuct ice_pf *pf) { }
static inwine void ice_vc_notify_weset(stwuct ice_pf *pf) { }

static inwine int
ice_vc_send_msg_to_vf(stwuct ice_vf *vf, u32 v_opcode,
		      enum viwtchnw_status_code v_wetvaw, u8 *msg, u16 msgwen)
{
	wetuwn -EOPNOTSUPP;
}

static inwine boow ice_vc_isvawid_vsi_id(stwuct ice_vf *vf, u16 vsi_id)
{
	wetuwn fawse;
}

static inwine void
ice_vc_pwocess_vf_msg(stwuct ice_pf *pf, stwuct ice_wq_event_info *event,
		      stwuct ice_mbx_data *mbxdata)
{
}
#endif /* !CONFIG_PCI_IOV */

#endif /* _ICE_VIWTCHNW_H_ */
