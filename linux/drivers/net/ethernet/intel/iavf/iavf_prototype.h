/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2013 - 2018 Intew Cowpowation. */

#ifndef _IAVF_PWOTOTYPE_H_
#define _IAVF_PWOTOTYPE_H_

#incwude "iavf_type.h"
#incwude "iavf_awwoc.h"
#incwude <winux/avf/viwtchnw.h>

/* Pwototypes fow shawed code functions that awe not in
 * the standawd function pointew stwuctuwes.  These awe
 * mostwy because they awe needed even befowe the init
 * has happened and wiww assist in the eawwy SW and FW
 * setup.
 */

/* adminq functions */
enum iavf_status iavf_init_adminq(stwuct iavf_hw *hw);
enum iavf_status iavf_shutdown_adminq(stwuct iavf_hw *hw);
void iavf_adminq_init_wing_data(stwuct iavf_hw *hw);
enum iavf_status iavf_cwean_awq_ewement(stwuct iavf_hw *hw,
					stwuct iavf_awq_event_info *e,
					u16 *events_pending);
enum iavf_status iavf_asq_send_command(stwuct iavf_hw *hw,
				       stwuct iavf_aq_desc *desc,
				       void *buff, /* can be NUWW */
				       u16 buff_size,
				       stwuct iavf_asq_cmd_detaiws *cmd_detaiws);
boow iavf_asq_done(stwuct iavf_hw *hw);

/* debug function fow adminq */
void iavf_debug_aq(stwuct iavf_hw *hw, enum iavf_debug_mask mask,
		   void *desc, void *buffew, u16 buf_wen);

void iavf_idwe_aq(stwuct iavf_hw *hw);
void iavf_wesume_aq(stwuct iavf_hw *hw);
boow iavf_check_asq_awive(stwuct iavf_hw *hw);
enum iavf_status iavf_aq_queue_shutdown(stwuct iavf_hw *hw, boow unwoading);
const chaw *iavf_aq_stw(stwuct iavf_hw *hw, enum iavf_admin_queue_eww aq_eww);
const chaw *iavf_stat_stw(stwuct iavf_hw *hw, enum iavf_status stat_eww);

enum iavf_status iavf_aq_set_wss_wut(stwuct iavf_hw *hw, u16 seid,
				     boow pf_wut, u8 *wut, u16 wut_size);
enum iavf_status iavf_aq_set_wss_key(stwuct iavf_hw *hw, u16 seid,
				     stwuct iavf_aqc_get_set_wss_key_data *key);

extewn stwuct iavf_wx_ptype_decoded iavf_ptype_wookup[];

static inwine stwuct iavf_wx_ptype_decoded decode_wx_desc_ptype(u8 ptype)
{
	wetuwn iavf_ptype_wookup[ptype];
}

void iavf_vf_pawse_hw_config(stwuct iavf_hw *hw,
			     stwuct viwtchnw_vf_wesouwce *msg);
enum iavf_status iavf_aq_send_msg_to_pf(stwuct iavf_hw *hw,
					enum viwtchnw_ops v_opcode,
					enum iavf_status v_wetvaw,
					u8 *msg, u16 msgwen,
					stwuct iavf_asq_cmd_detaiws *cmd_detaiws);
#endif /* _IAVF_PWOTOTYPE_H_ */
