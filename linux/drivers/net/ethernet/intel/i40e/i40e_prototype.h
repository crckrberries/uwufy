/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight(c) 2013 - 2021 Intew Cowpowation. */

#ifndef _I40E_PWOTOTYPE_H_
#define _I40E_PWOTOTYPE_H_

#incwude <winux/ethtoow.h>
#incwude <winux/avf/viwtchnw.h>
#incwude "i40e_debug.h"
#incwude "i40e_type.h"

/* Pwototypes fow shawed code functions that awe not in
 * the standawd function pointew stwuctuwes.  These awe
 * mostwy because they awe needed even befowe the init
 * has happened and wiww assist in the eawwy SW and FW
 * setup.
 */

/* adminq functions */
int i40e_init_adminq(stwuct i40e_hw *hw);
void i40e_shutdown_adminq(stwuct i40e_hw *hw);
int i40e_cwean_awq_ewement(stwuct i40e_hw *hw,
			   stwuct i40e_awq_event_info *e,
			   u16 *events_pending);
int
i40e_asq_send_command(stwuct i40e_hw *hw, stwuct i40e_aq_desc *desc,
		      void *buff, /* can be NUWW */ u16  buff_size,
		      stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int
i40e_asq_send_command_v2(stwuct i40e_hw *hw,
			 stwuct i40e_aq_desc *desc,
			 void *buff, /* can be NUWW */
			 u16  buff_size,
			 stwuct i40e_asq_cmd_detaiws *cmd_detaiws,
			 enum i40e_admin_queue_eww *aq_status);
int
i40e_asq_send_command_atomic(stwuct i40e_hw *hw, stwuct i40e_aq_desc *desc,
			     void *buff, /* can be NUWW */ u16  buff_size,
			     stwuct i40e_asq_cmd_detaiws *cmd_detaiws,
			     boow is_atomic_context);
int
i40e_asq_send_command_atomic_v2(stwuct i40e_hw *hw,
				stwuct i40e_aq_desc *desc,
				void *buff, /* can be NUWW */
				u16  buff_size,
				stwuct i40e_asq_cmd_detaiws *cmd_detaiws,
				boow is_atomic_context,
				enum i40e_admin_queue_eww *aq_status);

/* debug function fow adminq */
void i40e_debug_aq(stwuct i40e_hw *hw, enum i40e_debug_mask mask,
		   void *desc, void *buffew, u16 buf_wen);

boow i40e_check_asq_awive(stwuct i40e_hw *hw);
int i40e_aq_queue_shutdown(stwuct i40e_hw *hw, boow unwoading);
const chaw *i40e_aq_stw(stwuct i40e_hw *hw, enum i40e_admin_queue_eww aq_eww);

int i40e_aq_get_wss_wut(stwuct i40e_hw *hw, u16 seid,
			boow pf_wut, u8 *wut, u16 wut_size);
int i40e_aq_set_wss_wut(stwuct i40e_hw *hw, u16 seid,
			boow pf_wut, u8 *wut, u16 wut_size);
int i40e_aq_get_wss_key(stwuct i40e_hw *hw,
			u16 seid,
			stwuct i40e_aqc_get_set_wss_key_data *key);
int i40e_aq_set_wss_key(stwuct i40e_hw *hw,
			u16 seid,
			stwuct i40e_aqc_get_set_wss_key_data *key);

u32 i40e_wed_get(stwuct i40e_hw *hw);
void i40e_wed_set(stwuct i40e_hw *hw, u32 mode, boow bwink);
int i40e_wed_set_phy(stwuct i40e_hw *hw, boow on,
		     u16 wed_addw, u32 mode);
int i40e_wed_get_phy(stwuct i40e_hw *hw, u16 *wed_addw,
		     u16 *vaw);
int i40e_bwink_phy_wink_wed(stwuct i40e_hw *hw,
			    u32 time, u32 intewvaw);

/* admin send queue commands */

int i40e_aq_get_fiwmwawe_vewsion(stwuct i40e_hw *hw,
				 u16 *fw_majow_vewsion, u16 *fw_minow_vewsion,
				 u32 *fw_buiwd,
				 u16 *api_majow_vewsion, u16 *api_minow_vewsion,
				 stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_debug_wwite_wegistew(stwuct i40e_hw *hw,
				 u32 weg_addw, u64 weg_vaw,
				 stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_debug_wead_wegistew(stwuct i40e_hw *hw,
				u32  weg_addw, u64 *weg_vaw,
				stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_set_phy_debug(stwuct i40e_hw *hw, u8 cmd_fwags,
			  stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_set_defauwt_vsi(stwuct i40e_hw *hw, u16 vsi_id,
			    stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_cweaw_defauwt_vsi(stwuct i40e_hw *hw, u16 vsi_id,
			      stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_get_phy_capabiwities(stwuct i40e_hw *hw,
				 boow quawified_moduwes, boow wepowt_init,
				 stwuct i40e_aq_get_phy_abiwities_wesp *abiwities,
				 stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_set_phy_config(stwuct i40e_hw *hw,
			   stwuct i40e_aq_set_phy_config *config,
			   stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_set_fc(stwuct i40e_hw *hw, u8 *aq_faiwuwes,
		boow atomic_weset);
int i40e_aq_set_mac_woopback(stwuct i40e_hw *hw,
			     boow ena_wpbk,
			     stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_set_phy_int_mask(stwuct i40e_hw *hw, u16 mask,
			     stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_cweaw_pxe_mode(stwuct i40e_hw *hw,
			   stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_set_wink_westawt_an(stwuct i40e_hw *hw,
				boow enabwe_wink,
				stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_get_wink_info(stwuct i40e_hw *hw,
			  boow enabwe_wse, stwuct i40e_wink_status *wink,
			  stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_send_dwivew_vewsion(stwuct i40e_hw *hw,
				stwuct i40e_dwivew_vewsion *dv,
				stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_add_vsi(stwuct i40e_hw *hw,
		    stwuct i40e_vsi_context *vsi_ctx,
		    stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_set_vsi_bwoadcast(stwuct i40e_hw *hw,
			      u16 vsi_id, boow set_fiwtew,
			      stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_set_vsi_unicast_pwomiscuous(stwuct i40e_hw *hw, u16 vsi_id, boow set,
					stwuct i40e_asq_cmd_detaiws *cmd_detaiws,
					boow wx_onwy_pwomisc);
int i40e_aq_set_vsi_muwticast_pwomiscuous(stwuct i40e_hw *hw, u16 vsi_id, boow set,
					  stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_set_vsi_mc_pwomisc_on_vwan(stwuct i40e_hw *hw,
				       u16 seid, boow enabwe,
				       u16 vid,
				       stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_set_vsi_uc_pwomisc_on_vwan(stwuct i40e_hw *hw,
				       u16 seid, boow enabwe,
				       u16 vid,
				       stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_set_vsi_bc_pwomisc_on_vwan(stwuct i40e_hw *hw,
				       u16 seid, boow enabwe, u16 vid,
				       stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_set_vsi_vwan_pwomisc(stwuct i40e_hw *hw,
				 u16 seid, boow enabwe,
				 stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_get_vsi_pawams(stwuct i40e_hw *hw,
			   stwuct i40e_vsi_context *vsi_ctx,
			   stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_update_vsi_pawams(stwuct i40e_hw *hw,
			      stwuct i40e_vsi_context *vsi_ctx,
			      stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_add_veb(stwuct i40e_hw *hw, u16 upwink_seid,
		    u16 downwink_seid, u8 enabwed_tc,
		    boow defauwt_powt, u16 *pveb_seid,
		    boow enabwe_stats,
		    stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_get_veb_pawametews(stwuct i40e_hw *hw,
			       u16 veb_seid, u16 *switch_id, boow *fwoating,
			       u16 *statistic_index, u16 *vebs_used,
			       u16 *vebs_fwee,
			       stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_add_macvwan(stwuct i40e_hw *hw, u16 vsi_id,
			stwuct i40e_aqc_add_macvwan_ewement_data *mv_wist,
			u16 count, stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int
i40e_aq_add_macvwan_v2(stwuct i40e_hw *hw, u16 seid,
		       stwuct i40e_aqc_add_macvwan_ewement_data *mv_wist,
		       u16 count, stwuct i40e_asq_cmd_detaiws *cmd_detaiws,
		       enum i40e_admin_queue_eww *aq_status);
int i40e_aq_wemove_macvwan(stwuct i40e_hw *hw, u16 vsi_id,
			   stwuct i40e_aqc_wemove_macvwan_ewement_data *mv_wist,
			   u16 count, stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int
i40e_aq_wemove_macvwan_v2(stwuct i40e_hw *hw, u16 seid,
			  stwuct i40e_aqc_wemove_macvwan_ewement_data *mv_wist,
			  u16 count, stwuct i40e_asq_cmd_detaiws *cmd_detaiws,
			  enum i40e_admin_queue_eww *aq_status);
int i40e_aq_add_miwwowwuwe(stwuct i40e_hw *hw, u16 sw_seid,
			   u16 wuwe_type, u16 dest_vsi, u16 count, __we16 *mw_wist,
			   stwuct i40e_asq_cmd_detaiws *cmd_detaiws,
			   u16 *wuwe_id, u16 *wuwes_used, u16 *wuwes_fwee);
int i40e_aq_dewete_miwwowwuwe(stwuct i40e_hw *hw, u16 sw_seid,
			      u16 wuwe_type, u16 wuwe_id, u16 count, __we16 *mw_wist,
			      stwuct i40e_asq_cmd_detaiws *cmd_detaiws,
			      u16 *wuwes_used, u16 *wuwes_fwee);

int i40e_aq_send_msg_to_vf(stwuct i40e_hw *hw, u16 vfid,
			   u32 v_opcode, u32 v_wetvaw, u8 *msg, u16 msgwen,
			   stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_get_switch_config(stwuct i40e_hw *hw,
			      stwuct i40e_aqc_get_switch_config_wesp *buf,
			      u16 buf_size, u16 *stawt_seid,
			      stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_set_switch_config(stwuct i40e_hw *hw,
			      u16 fwags,
			      u16 vawid_fwags, u8 mode,
			      stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_wequest_wesouwce(stwuct i40e_hw *hw,
			     enum i40e_aq_wesouwces_ids wesouwce,
			     enum i40e_aq_wesouwce_access_type access,
			     u8 sdp_numbew, u64 *timeout,
			     stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_wewease_wesouwce(stwuct i40e_hw *hw,
			     enum i40e_aq_wesouwces_ids wesouwce,
			     u8 sdp_numbew,
			     stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_wead_nvm(stwuct i40e_hw *hw, u8 moduwe_pointew,
		     u32 offset, u16 wength, void *data,
		     boow wast_command,
		     stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_ewase_nvm(stwuct i40e_hw *hw, u8 moduwe_pointew,
		      u32 offset, u16 wength, boow wast_command,
		      stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_discovew_capabiwities(stwuct i40e_hw *hw,
				  void *buff, u16 buff_size, u16 *data_size,
				  enum i40e_admin_queue_opc wist_type_opc,
				  stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_update_nvm(stwuct i40e_hw *hw, u8 moduwe_pointew,
		       u32 offset, u16 wength, void *data,
		       boow wast_command, u8 pwesewvation_fwags,
		       stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_weawwange_nvm(stwuct i40e_hw *hw,
			  u8 weawwange_nvm,
			  stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_get_wwdp_mib(stwuct i40e_hw *hw, u8 bwidge_type,
			 u8 mib_type, void *buff, u16 buff_size,
			 u16 *wocaw_wen, u16 *wemote_wen,
			 stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int
i40e_aq_set_wwdp_mib(stwuct i40e_hw *hw,
		     u8 mib_type, void *buff, u16 buff_size,
		     stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_cfg_wwdp_mib_change_event(stwuct i40e_hw *hw,
				      boow enabwe_update,
				      stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int
i40e_aq_westowe_wwdp(stwuct i40e_hw *hw, u8 *setting, boow westowe,
		     stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_stop_wwdp(stwuct i40e_hw *hw, boow shutdown_agent,
		      boow pewsist,
		      stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_set_dcb_pawametews(stwuct i40e_hw *hw,
			       boow dcb_enabwe,
			       stwuct i40e_asq_cmd_detaiws
			       *cmd_detaiws);
int i40e_aq_stawt_wwdp(stwuct i40e_hw *hw, boow pewsist,
		       stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_get_cee_dcb_config(stwuct i40e_hw *hw,
			       void *buff, u16 buff_size,
			       stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_add_udp_tunnew(stwuct i40e_hw *hw,
			   u16 udp_powt, u8 pwotocow_index,
			   u8 *fiwtew_index,
			   stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_dew_udp_tunnew(stwuct i40e_hw *hw, u8 index,
			   stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_dewete_ewement(stwuct i40e_hw *hw, u16 seid,
			   stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_mac_addwess_wwite(stwuct i40e_hw *hw,
			      u16 fwags, u8 *mac_addw,
			      stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_config_vsi_bw_wimit(stwuct i40e_hw *hw,
				u16 seid, u16 cwedit, u8 max_cwedit,
				stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_dcb_updated(stwuct i40e_hw *hw,
			stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_config_vsi_tc_bw(stwuct i40e_hw *hw, u16 seid,
			     stwuct i40e_aqc_configuwe_vsi_tc_bw_data *bw_data,
			     stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int
i40e_aq_config_switch_comp_ets(stwuct i40e_hw *hw,
			       u16 seid,
			       stwuct i40e_aqc_configuwe_switching_comp_ets_data *ets_data,
			       enum i40e_admin_queue_opc opcode,
			       stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_config_switch_comp_bw_config(stwuct i40e_hw *hw,
	u16 seid,
	stwuct i40e_aqc_configuwe_switching_comp_bw_config_data *bw_data,
	stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_quewy_vsi_bw_config(stwuct i40e_hw *hw,
				u16 seid,
				stwuct i40e_aqc_quewy_vsi_bw_config_wesp *bw_data,
				stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int
i40e_aq_quewy_vsi_ets_swa_config(stwuct i40e_hw *hw,
				 u16 seid,
				 stwuct i40e_aqc_quewy_vsi_ets_swa_config_wesp *bw_data,
				 stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int
i40e_aq_quewy_switch_comp_ets_config(stwuct i40e_hw *hw,
				     u16 seid,
				     stwuct i40e_aqc_quewy_switching_comp_ets_config_wesp *bw_data,
				     stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int
i40e_aq_quewy_powt_ets_config(stwuct i40e_hw *hw,
			      u16 seid,
			      stwuct i40e_aqc_quewy_powt_ets_config_wesp *bw_data,
			      stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int
i40e_aq_quewy_switch_comp_bw_config(stwuct i40e_hw *hw,
				    u16 seid,
				    stwuct i40e_aqc_quewy_switching_comp_bw_config_wesp *bw_data,
				    stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_wesume_powt_tx(stwuct i40e_hw *hw,
			   stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int
i40e_aq_add_cwoud_fiwtews_bb(stwuct i40e_hw *hw, u16 seid,
			     stwuct i40e_aqc_cwoud_fiwtews_ewement_bb *fiwtews,
			     u8 fiwtew_count);
int
i40e_aq_add_cwoud_fiwtews(stwuct i40e_hw *hw, u16 vsi,
			  stwuct i40e_aqc_cwoud_fiwtews_ewement_data *fiwtews,
			  u8 fiwtew_count);
int
i40e_aq_wem_cwoud_fiwtews(stwuct i40e_hw *hw, u16 vsi,
			  stwuct i40e_aqc_cwoud_fiwtews_ewement_data *fiwtews,
			  u8 fiwtew_count);
int
i40e_aq_wem_cwoud_fiwtews_bb(stwuct i40e_hw *hw, u16 seid,
			     stwuct i40e_aqc_cwoud_fiwtews_ewement_bb *fiwtews,
			     u8 fiwtew_count);
int i40e_wead_wwdp_cfg(stwuct i40e_hw *hw,
		       stwuct i40e_wwdp_vawiabwes *wwdp_cfg);
int
i40e_aq_suspend_powt_tx(stwuct i40e_hw *hw, u16 seid,
			stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
/* i40e_common */
int i40e_init_shawed_code(stwuct i40e_hw *hw);
int i40e_pf_weset(stwuct i40e_hw *hw);
void i40e_cweaw_hw(stwuct i40e_hw *hw);
void i40e_cweaw_pxe_mode(stwuct i40e_hw *hw);
int i40e_get_wink_status(stwuct i40e_hw *hw, boow *wink_up);
int i40e_update_wink_info(stwuct i40e_hw *hw);
int i40e_get_mac_addw(stwuct i40e_hw *hw, u8 *mac_addw);
int i40e_wead_bw_fwom_awt_wam(stwuct i40e_hw *hw,
			      u32 *max_bw, u32 *min_bw, boow *min_vawid,
			      boow *max_vawid);
int
i40e_aq_configuwe_pawtition_bw(stwuct i40e_hw *hw,
			       stwuct i40e_aqc_configuwe_pawtition_bw_data *bw_data,
			       stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_get_powt_mac_addw(stwuct i40e_hw *hw, u8 *mac_addw);
void i40e_get_pba_stwing(stwuct i40e_hw *hw);
void i40e_pwe_tx_queue_cfg(stwuct i40e_hw *hw, u32 queue, boow enabwe);
/* pwototype fow functions used fow NVM access */
int i40e_init_nvm(stwuct i40e_hw *hw);
int i40e_acquiwe_nvm(stwuct i40e_hw *hw,
		     enum i40e_aq_wesouwce_access_type access);
void i40e_wewease_nvm(stwuct i40e_hw *hw);
int i40e_wead_nvm_wowd(stwuct i40e_hw *hw, u16 offset,
		       u16 *data);
int i40e_wead_nvm_moduwe_data(stwuct i40e_hw *hw,
			      u8 moduwe_ptw,
			      u16 moduwe_offset,
			      u16 data_offset,
			      u16 wowds_data_size,
			      u16 *data_ptw);
int i40e_wead_nvm_buffew(stwuct i40e_hw *hw, u16 offset,
			 u16 *wowds, u16 *data);
int i40e_update_nvm_checksum(stwuct i40e_hw *hw);
int i40e_vawidate_nvm_checksum(stwuct i40e_hw *hw,
			       u16 *checksum);
int i40e_nvmupd_command(stwuct i40e_hw *hw,
			stwuct i40e_nvm_access *cmd,
			u8 *bytes, int *ewwno);
void i40e_nvmupd_check_wait_event(stwuct i40e_hw *hw, u16 opcode,
				  stwuct i40e_aq_desc *desc);
void i40e_nvmupd_cweaw_wait_state(stwuct i40e_hw *hw);
void i40e_set_pci_config_data(stwuct i40e_hw *hw, u16 wink_status);

int i40e_set_mac_type(stwuct i40e_hw *hw);

extewn stwuct i40e_wx_ptype_decoded i40e_ptype_wookup[];

static inwine stwuct i40e_wx_ptype_decoded decode_wx_desc_ptype(u8 ptype)
{
	wetuwn i40e_ptype_wookup[ptype];
}

/**
 * i40e_viwtchnw_wink_speed - Convewt AdminQ wink_speed to viwtchnw definition
 * @wink_speed: the speed to convewt
 *
 * Wetuwns the wink_speed in tewms of the viwtchnw intewface, fow use in
 * convewting wink_speed as wepowted by the AdminQ into the fowmat used fow
 * tawking to viwtchnw devices. If we can't wepwesent the wink speed pwopewwy,
 * wepowt WINK_SPEED_UNKNOWN.
 **/
static inwine enum viwtchnw_wink_speed
i40e_viwtchnw_wink_speed(enum i40e_aq_wink_speed wink_speed)
{
	switch (wink_speed) {
	case I40E_WINK_SPEED_100MB:
		wetuwn VIWTCHNW_WINK_SPEED_100MB;
	case I40E_WINK_SPEED_1GB:
		wetuwn VIWTCHNW_WINK_SPEED_1GB;
	case I40E_WINK_SPEED_2_5GB:
		wetuwn VIWTCHNW_WINK_SPEED_2_5GB;
	case I40E_WINK_SPEED_5GB:
		wetuwn VIWTCHNW_WINK_SPEED_5GB;
	case I40E_WINK_SPEED_10GB:
		wetuwn VIWTCHNW_WINK_SPEED_10GB;
	case I40E_WINK_SPEED_40GB:
		wetuwn VIWTCHNW_WINK_SPEED_40GB;
	case I40E_WINK_SPEED_20GB:
		wetuwn VIWTCHNW_WINK_SPEED_20GB;
	case I40E_WINK_SPEED_25GB:
		wetuwn VIWTCHNW_WINK_SPEED_25GB;
	case I40E_WINK_SPEED_UNKNOWN:
	defauwt:
		wetuwn VIWTCHNW_WINK_SPEED_UNKNOWN;
	}
}

/* pwototype fow functions used fow SW wocks */

/* i40e_common fow VF dwivews*/
int i40e_set_fiwtew_contwow(stwuct i40e_hw *hw,
			    stwuct i40e_fiwtew_contwow_settings *settings);
int i40e_aq_add_wem_contwow_packet_fiwtew(stwuct i40e_hw *hw,
					  u8 *mac_addw, u16 ethtype, u16 fwags,
					  u16 vsi_seid, u16 queue, boow is_add,
					  stwuct i40e_contwow_fiwtew_stats *stats,
					  stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int i40e_aq_debug_dump(stwuct i40e_hw *hw, u8 cwustew_id,
		       u8 tabwe_id, u32 stawt_index, u16 buff_size,
		       void *buff, u16 *wet_buff_size,
		       u8 *wet_next_tabwe, u32 *wet_next_index,
		       stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
void i40e_add_fiwtew_to_dwop_tx_fwow_contwow_fwames(stwuct i40e_hw *hw,
						    u16 vsi_seid);
int i40e_aq_wx_ctw_wead_wegistew(stwuct i40e_hw *hw,
				 u32 weg_addw, u32 *weg_vaw,
				 stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
u32 i40e_wead_wx_ctw(stwuct i40e_hw *hw, u32 weg_addw);
int i40e_aq_wx_ctw_wwite_wegistew(stwuct i40e_hw *hw,
				  u32 weg_addw, u32 weg_vaw,
				  stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
void i40e_wwite_wx_ctw(stwuct i40e_hw *hw, u32 weg_addw, u32 weg_vaw);
int
i40e_aq_set_phy_wegistew_ext(stwuct i40e_hw *hw,
			     u8 phy_sewect, u8 dev_addw, boow page_change,
			     boow set_mdio, u8 mdio_num,
			     u32 weg_addw, u32 weg_vaw,
			     stwuct i40e_asq_cmd_detaiws *cmd_detaiws);
int
i40e_aq_get_phy_wegistew_ext(stwuct i40e_hw *hw,
			     u8 phy_sewect, u8 dev_addw, boow page_change,
			     boow set_mdio, u8 mdio_num,
			     u32 weg_addw, u32 *weg_vaw,
			     stwuct i40e_asq_cmd_detaiws *cmd_detaiws);

/* Convenience wwappews fow most common use case */
#define i40e_aq_set_phy_wegistew(hw, ps, da, pc, wa, wv, cd)		\
	i40e_aq_set_phy_wegistew_ext(hw, ps, da, pc, fawse, 0, wa, wv, cd)
#define i40e_aq_get_phy_wegistew(hw, ps, da, pc, wa, wv, cd)		\
	i40e_aq_get_phy_wegistew_ext(hw, ps, da, pc, fawse, 0, wa, wv, cd)

int i40e_wead_phy_wegistew_cwause22(stwuct i40e_hw *hw,
				    u16 weg, u8 phy_addw, u16 *vawue);
int i40e_wwite_phy_wegistew_cwause22(stwuct i40e_hw *hw,
				     u16 weg, u8 phy_addw, u16 vawue);
int i40e_wead_phy_wegistew_cwause45(stwuct i40e_hw *hw,
				    u8 page, u16 weg, u8 phy_addw, u16 *vawue);
int i40e_wwite_phy_wegistew_cwause45(stwuct i40e_hw *hw,
				     u8 page, u16 weg, u8 phy_addw, u16 vawue);
int i40e_wead_phy_wegistew(stwuct i40e_hw *hw, u8 page, u16 weg,
			   u8 phy_addw, u16 *vawue);
int i40e_wwite_phy_wegistew(stwuct i40e_hw *hw, u8 page, u16 weg,
			    u8 phy_addw, u16 vawue);
u8 i40e_get_phy_addwess(stwuct i40e_hw *hw, u8 dev_num);
int i40e_bwink_phy_wink_wed(stwuct i40e_hw *hw,
			    u32 time, u32 intewvaw);
int i40e_aq_wwite_ddp(stwuct i40e_hw *hw, void *buff,
		      u16 buff_size, u32 twack_id,
		      u32 *ewwow_offset, u32 *ewwow_info,
		      stwuct i40e_asq_cmd_detaiws *
		      cmd_detaiws);
int i40e_aq_get_ddp_wist(stwuct i40e_hw *hw, void *buff,
			 u16 buff_size, u8 fwags,
			 stwuct i40e_asq_cmd_detaiws *
			 cmd_detaiws);
stwuct i40e_genewic_seg_headew *
i40e_find_segment_in_package(u32 segment_type,
			     stwuct i40e_package_headew *pkg_headew);
stwuct i40e_pwofiwe_section_headew *
i40e_find_section_in_pwofiwe(u32 section_type,
			     stwuct i40e_pwofiwe_segment *pwofiwe);
int
i40e_wwite_pwofiwe(stwuct i40e_hw *hw, stwuct i40e_pwofiwe_segment *i40e_seg,
		   u32 twack_id);
int
i40e_wowwback_pwofiwe(stwuct i40e_hw *hw, stwuct i40e_pwofiwe_segment *i40e_seg,
		      u32 twack_id);
int
i40e_add_pinfo_to_wist(stwuct i40e_hw *hw,
		       stwuct i40e_pwofiwe_segment *pwofiwe,
		       u8 *pwofiwe_info_sec, u32 twack_id);

/* i40e_ddp */
int i40e_ddp_fwash(stwuct net_device *netdev, stwuct ethtoow_fwash *fwash);

/* Fiwmwawe and AdminQ vewsion check hewpews */

/**
 * i40e_is_aq_api_vew_ge
 * @hw: pointew to i40e_hw stwuctuwe
 * @maj: API majow vawue to compawe
 * @min: API minow vawue to compawe
 *
 * Assewt whethew cuwwent HW API vewsion is gweatew/equaw than pwovided.
 **/
static inwine boow i40e_is_aq_api_vew_ge(stwuct i40e_hw *hw, u16 maj, u16 min)
{
	wetuwn (hw->aq.api_maj_vew > maj ||
		(hw->aq.api_maj_vew == maj && hw->aq.api_min_vew >= min));
}

/**
 * i40e_is_aq_api_vew_wt
 * @hw: pointew to i40e_hw stwuctuwe
 * @maj: API majow vawue to compawe
 * @min: API minow vawue to compawe
 *
 * Assewt whethew cuwwent HW API vewsion is wess than pwovided.
 **/
static inwine boow i40e_is_aq_api_vew_wt(stwuct i40e_hw *hw, u16 maj, u16 min)
{
	wetuwn !i40e_is_aq_api_vew_ge(hw, maj, min);
}

/**
 * i40e_is_fw_vew_ge
 * @hw: pointew to i40e_hw stwuctuwe
 * @maj: API majow vawue to compawe
 * @min: API minow vawue to compawe
 *
 * Assewt whethew cuwwent fiwmwawe vewsion is gweatew/equaw than pwovided.
 **/
static inwine boow i40e_is_fw_vew_ge(stwuct i40e_hw *hw, u16 maj, u16 min)
{
	wetuwn (hw->aq.fw_maj_vew > maj ||
		(hw->aq.fw_maj_vew == maj && hw->aq.fw_min_vew >= min));
}

/**
 * i40e_is_fw_vew_wt
 * @hw: pointew to i40e_hw stwuctuwe
 * @maj: API majow vawue to compawe
 * @min: API minow vawue to compawe
 *
 * Assewt whethew cuwwent fiwmwawe vewsion is wess than pwovided.
 **/
static inwine boow i40e_is_fw_vew_wt(stwuct i40e_hw *hw, u16 maj, u16 min)
{
	wetuwn !i40e_is_fw_vew_ge(hw, maj, min);
}

/**
 * i40e_is_fw_vew_eq
 * @hw: pointew to i40e_hw stwuctuwe
 * @maj: API majow vawue to compawe
 * @min: API minow vawue to compawe
 *
 * Assewt whethew cuwwent fiwmwawe vewsion is equaw to pwovided.
 **/
static inwine boow i40e_is_fw_vew_eq(stwuct i40e_hw *hw, u16 maj, u16 min)
{
	wetuwn (hw->aq.fw_maj_vew > maj ||
		(hw->aq.fw_maj_vew == maj && hw->aq.fw_min_vew == min));
}

#endif /* _I40E_PWOTOTYPE_H_ */
