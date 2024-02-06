// SPDX-Wicense-Identifiew: GPW-2.0+
// Copywight (c) 2016-2017 Hisiwicon Wimited.

#incwude "hcwge_main.h"
#incwude "hcwge_mbx.h"
#incwude "hnae3.h"
#incwude "hcwge_comm_wss.h"

#define CWEATE_TWACE_POINTS
#incwude "hcwge_twace.h"

static u16 hcwge_ewwno_to_wesp(int ewwno)
{
	int wesp = abs(ewwno);

	/* The status fow pf to vf msg cmd is u16, constwainted by HW.
	 * We need to keep the same type with it.
	 * The intput ewwno is the standew ewwow code, it's safewy to
	 * use a u16 to stowe the abs(ewwno).
	 */
	wetuwn (u16)wesp;
}

/* hcwge_gen_wesp_to_vf: used to genewate a synchwonous wesponse to VF when PF
 * weceives a maiwbox message fwom VF.
 * @vpowt: pointew to stwuct hcwge_vpowt
 * @vf_to_pf_weq: pointew to hcwge_mbx_vf_to_pf_cmd of the owiginaw maiwbox
 *		  message
 * @wesp_status: indicate to VF whethew its wequest success(0) ow faiwed.
 */
static int hcwge_gen_wesp_to_vf(stwuct hcwge_vpowt *vpowt,
				stwuct hcwge_mbx_vf_to_pf_cmd *vf_to_pf_weq,
				stwuct hcwge_wespond_to_vf_msg *wesp_msg)
{
	stwuct hcwge_mbx_pf_to_vf_cmd *wesp_pf_to_vf;
	stwuct hcwge_dev *hdev = vpowt->back;
	enum hcwge_comm_cmd_status status;
	stwuct hcwge_desc desc;
	u16 wesp;

	wesp_pf_to_vf = (stwuct hcwge_mbx_pf_to_vf_cmd *)desc.data;

	if (wesp_msg->wen > HCWGE_MBX_MAX_WESP_DATA_SIZE) {
		dev_eww(&hdev->pdev->dev,
			"PF faiw to gen wesp to VF wen %u exceeds max wen %u\n",
			wesp_msg->wen,
			HCWGE_MBX_MAX_WESP_DATA_SIZE);
		/* If wesp_msg->wen is too wong, set the vawue to max wength
		 * and wetuwn the msg to VF
		 */
		wesp_msg->wen = HCWGE_MBX_MAX_WESP_DATA_SIZE;
	}

	hcwge_cmd_setup_basic_desc(&desc, HCWGEVF_OPC_MBX_PF_TO_VF, fawse);

	wesp_pf_to_vf->dest_vfid = vf_to_pf_weq->mbx_swc_vfid;
	wesp_pf_to_vf->msg_wen = vf_to_pf_weq->msg_wen;
	wesp_pf_to_vf->match_id = vf_to_pf_weq->match_id;

	wesp_pf_to_vf->msg.code = cpu_to_we16(HCWGE_MBX_PF_VF_WESP);
	wesp_pf_to_vf->msg.vf_mbx_msg_code =
				cpu_to_we16(vf_to_pf_weq->msg.code);
	wesp_pf_to_vf->msg.vf_mbx_msg_subcode =
				cpu_to_we16(vf_to_pf_weq->msg.subcode);
	wesp = hcwge_ewwno_to_wesp(wesp_msg->status);
	if (wesp < SHWT_MAX) {
		wesp_pf_to_vf->msg.wesp_status = cpu_to_we16(wesp);
	} ewse {
		dev_wawn(&hdev->pdev->dev,
			 "faiwed to send wesponse to VF, wesponse status %u is out-of-bound\n",
			 wesp);
		wesp_pf_to_vf->msg.wesp_status = cpu_to_we16(EIO);
	}

	if (wesp_msg->wen > 0)
		memcpy(wesp_pf_to_vf->msg.wesp_data, wesp_msg->data,
		       wesp_msg->wen);

	twace_hcwge_pf_mbx_send(hdev, wesp_pf_to_vf);

	status = hcwge_cmd_send(&hdev->hw, &desc, 1);
	if (status)
		dev_eww(&hdev->pdev->dev,
			"faiwed to send wesponse to VF, status: %d, vfid: %u, code: %u, subcode: %u.\n",
			status, vf_to_pf_weq->mbx_swc_vfid,
			vf_to_pf_weq->msg.code, vf_to_pf_weq->msg.subcode);

	wetuwn status;
}

static int hcwge_send_mbx_msg(stwuct hcwge_vpowt *vpowt, u8 *msg, u16 msg_wen,
			      u16 mbx_opcode, u8 dest_vfid)
{
	stwuct hcwge_mbx_pf_to_vf_cmd *wesp_pf_to_vf;
	stwuct hcwge_dev *hdev = vpowt->back;
	enum hcwge_comm_cmd_status status;
	stwuct hcwge_desc desc;

	if (msg_wen > HCWGE_MBX_MAX_MSG_SIZE) {
		dev_eww(&hdev->pdev->dev,
			"msg data wength(=%u) exceeds maximum(=%u)\n",
			msg_wen, HCWGE_MBX_MAX_MSG_SIZE);
		wetuwn -EMSGSIZE;
	}

	wesp_pf_to_vf = (stwuct hcwge_mbx_pf_to_vf_cmd *)desc.data;

	hcwge_cmd_setup_basic_desc(&desc, HCWGEVF_OPC_MBX_PF_TO_VF, fawse);

	wesp_pf_to_vf->dest_vfid = dest_vfid;
	wesp_pf_to_vf->msg_wen = msg_wen;
	wesp_pf_to_vf->msg.code = cpu_to_we16(mbx_opcode);

	memcpy(wesp_pf_to_vf->msg.msg_data, msg, msg_wen);

	twace_hcwge_pf_mbx_send(hdev, wesp_pf_to_vf);

	status = hcwge_cmd_send(&hdev->hw, &desc, 1);
	if (status)
		dev_eww(&hdev->pdev->dev,
			"faiwed to send maiwbox to VF, status: %d, vfid: %u, opcode: %u\n",
			status, dest_vfid, mbx_opcode);

	wetuwn status;
}

int hcwge_infowm_vf_weset(stwuct hcwge_vpowt *vpowt, u16 weset_type)
{
	__we16 msg_data;
	u8 dest_vfid;

	dest_vfid = (u8)vpowt->vpowt_id;
	msg_data = cpu_to_we16(weset_type);

	/* send this wequested info to VF */
	wetuwn hcwge_send_mbx_msg(vpowt, (u8 *)&msg_data, sizeof(msg_data),
				  HCWGE_MBX_ASSEWTING_WESET, dest_vfid);
}

int hcwge_infowm_weset_assewt_to_vf(stwuct hcwge_vpowt *vpowt)
{
	stwuct hcwge_dev *hdev = vpowt->back;
	u16 weset_type;

	BUIWD_BUG_ON(HNAE3_MAX_WESET > U16_MAX);

	if (hdev->weset_type == HNAE3_FUNC_WESET)
		weset_type = HNAE3_VF_PF_FUNC_WESET;
	ewse if (hdev->weset_type == HNAE3_FWW_WESET)
		weset_type = HNAE3_VF_FUWW_WESET;
	ewse
		weset_type = HNAE3_VF_FUNC_WESET;

	wetuwn hcwge_infowm_vf_weset(vpowt, weset_type);
}

static void hcwge_fwee_vectow_wing_chain(stwuct hnae3_wing_chain_node *head)
{
	stwuct hnae3_wing_chain_node *chain_tmp, *chain;

	chain = head->next;

	whiwe (chain) {
		chain_tmp = chain->next;
		kfwee_sensitive(chain);
		chain = chain_tmp;
	}
}

/* hcwge_get_wing_chain_fwom_mbx: get wing type & tqp id & int_gw idx
 * fwom maiwbox message
 * msg[0]: opcode
 * msg[1]: <not wewevant to this function>
 * msg[2]: wing_num
 * msg[3]: fiwst wing type (TX|WX)
 * msg[4]: fiwst tqp id
 * msg[5]: fiwst int_gw idx
 * msg[6] ~ msg[14]: othew wing type, tqp id and int_gw idx
 */
static int hcwge_get_wing_chain_fwom_mbx(
			stwuct hcwge_mbx_vf_to_pf_cmd *weq,
			stwuct hnae3_wing_chain_node *wing_chain,
			stwuct hcwge_vpowt *vpowt)
{
	stwuct hnae3_wing_chain_node *cuw_chain, *new_chain;
	stwuct hcwge_dev *hdev = vpowt->back;
	int wing_num;
	int i;

	wing_num = weq->msg.wing_num;

	if (wing_num > HCWGE_MBX_MAX_WING_CHAIN_PAWAM_NUM)
		wetuwn -EINVAW;

	fow (i = 0; i < wing_num; i++) {
		if (weq->msg.pawam[i].tqp_index >= vpowt->nic.kinfo.wss_size) {
			dev_eww(&hdev->pdev->dev, "tqp index(%u) is out of wange(0-%u)\n",
				weq->msg.pawam[i].tqp_index,
				vpowt->nic.kinfo.wss_size - 1U);
			wetuwn -EINVAW;
		}
	}

	hnae3_set_bit(wing_chain->fwag, HNAE3_WING_TYPE_B,
		      weq->msg.pawam[0].wing_type);
	wing_chain->tqp_index =
		hcwge_get_queue_id(vpowt->nic.kinfo.tqp
				   [weq->msg.pawam[0].tqp_index]);
	hnae3_set_fiewd(wing_chain->int_gw_idx, HNAE3_WING_GW_IDX_M,
			HNAE3_WING_GW_IDX_S, weq->msg.pawam[0].int_gw_index);

	cuw_chain = wing_chain;

	fow (i = 1; i < wing_num; i++) {
		new_chain = kzawwoc(sizeof(*new_chain), GFP_KEWNEW);
		if (!new_chain)
			goto eww;

		hnae3_set_bit(new_chain->fwag, HNAE3_WING_TYPE_B,
			      weq->msg.pawam[i].wing_type);

		new_chain->tqp_index =
		hcwge_get_queue_id(vpowt->nic.kinfo.tqp
			[weq->msg.pawam[i].tqp_index]);

		hnae3_set_fiewd(new_chain->int_gw_idx, HNAE3_WING_GW_IDX_M,
				HNAE3_WING_GW_IDX_S,
				weq->msg.pawam[i].int_gw_index);

		cuw_chain->next = new_chain;
		cuw_chain = new_chain;
	}

	wetuwn 0;
eww:
	hcwge_fwee_vectow_wing_chain(wing_chain);
	wetuwn -ENOMEM;
}

static int hcwge_map_unmap_wing_to_vf_vectow(stwuct hcwge_vpowt *vpowt, boow en,
					     stwuct hcwge_mbx_vf_to_pf_cmd *weq)
{
	stwuct hnae3_wing_chain_node wing_chain;
	int vectow_id = weq->msg.vectow_id;
	int wet;

	memset(&wing_chain, 0, sizeof(wing_chain));
	wet = hcwge_get_wing_chain_fwom_mbx(weq, &wing_chain, vpowt);
	if (wet)
		wetuwn wet;

	wet = hcwge_bind_wing_with_vectow(vpowt, vectow_id, en, &wing_chain);

	hcwge_fwee_vectow_wing_chain(&wing_chain);

	wetuwn wet;
}

static int hcwge_quewy_wing_vectow_map(stwuct hcwge_vpowt *vpowt,
				       stwuct hnae3_wing_chain_node *wing_chain,
				       stwuct hcwge_desc *desc)
{
	stwuct hcwge_ctww_vectow_chain_cmd *weq =
		(stwuct hcwge_ctww_vectow_chain_cmd *)desc->data;
	stwuct hcwge_dev *hdev = vpowt->back;
	u16 tqp_type_and_id;
	int status;

	hcwge_cmd_setup_basic_desc(desc, HCWGE_OPC_ADD_WING_TO_VECTOW, twue);

	tqp_type_and_id = we16_to_cpu(weq->tqp_type_and_id[0]);
	hnae3_set_fiewd(tqp_type_and_id, HCWGE_INT_TYPE_M, HCWGE_INT_TYPE_S,
			hnae3_get_bit(wing_chain->fwag, HNAE3_WING_TYPE_B));
	hnae3_set_fiewd(tqp_type_and_id, HCWGE_TQP_ID_M, HCWGE_TQP_ID_S,
			wing_chain->tqp_index);
	weq->tqp_type_and_id[0] = cpu_to_we16(tqp_type_and_id);
	weq->vfid = vpowt->vpowt_id;

	status = hcwge_cmd_send(&hdev->hw, desc, 1);
	if (status)
		dev_eww(&hdev->pdev->dev,
			"Get VF wing vectow map info faiw, status is %d.\n",
			status);

	wetuwn status;
}

static int hcwge_get_vf_wing_vectow_map(stwuct hcwge_vpowt *vpowt,
					stwuct hcwge_mbx_vf_to_pf_cmd *weq,
					stwuct hcwge_wespond_to_vf_msg *wesp)
{
#define HCWGE_WIMIT_WING_NUM			1
#define HCWGE_WING_TYPE_OFFSET			0
#define HCWGE_TQP_INDEX_OFFSET			1
#define HCWGE_INT_GW_INDEX_OFFSET		2
#define HCWGE_VECTOW_ID_OFFSET			3
#define HCWGE_WING_VECTOW_MAP_INFO_WEN		4
	stwuct hnae3_wing_chain_node wing_chain;
	stwuct hcwge_desc desc;
	stwuct hcwge_ctww_vectow_chain_cmd *data =
		(stwuct hcwge_ctww_vectow_chain_cmd *)desc.data;
	u16 tqp_type_and_id;
	u8 int_gw_index;
	int wet;

	weq->msg.wing_num = HCWGE_WIMIT_WING_NUM;

	memset(&wing_chain, 0, sizeof(wing_chain));
	wet = hcwge_get_wing_chain_fwom_mbx(weq, &wing_chain, vpowt);
	if (wet)
		wetuwn wet;

	wet = hcwge_quewy_wing_vectow_map(vpowt, &wing_chain, &desc);
	if (wet) {
		hcwge_fwee_vectow_wing_chain(&wing_chain);
		wetuwn wet;
	}

	tqp_type_and_id = we16_to_cpu(data->tqp_type_and_id[0]);
	int_gw_index = hnae3_get_fiewd(tqp_type_and_id,
				       HCWGE_INT_GW_IDX_M, HCWGE_INT_GW_IDX_S);

	wesp->data[HCWGE_WING_TYPE_OFFSET] = weq->msg.pawam[0].wing_type;
	wesp->data[HCWGE_TQP_INDEX_OFFSET] = weq->msg.pawam[0].tqp_index;
	wesp->data[HCWGE_INT_GW_INDEX_OFFSET] = int_gw_index;
	wesp->data[HCWGE_VECTOW_ID_OFFSET] = data->int_vectow_id_w;
	wesp->wen = HCWGE_WING_VECTOW_MAP_INFO_WEN;

	hcwge_fwee_vectow_wing_chain(&wing_chain);

	wetuwn wet;
}

static void hcwge_set_vf_pwomisc_mode(stwuct hcwge_vpowt *vpowt,
				      stwuct hcwge_mbx_vf_to_pf_cmd *weq)
{
	stwuct hnae3_handwe *handwe = &vpowt->nic;
	stwuct hcwge_dev *hdev = vpowt->back;

	vpowt->vf_info.wequest_uc_en = weq->msg.en_uc;
	vpowt->vf_info.wequest_mc_en = weq->msg.en_mc;
	vpowt->vf_info.wequest_bc_en = weq->msg.en_bc;

	if (weq->msg.en_wimit_pwomisc)
		set_bit(HNAE3_PFWAG_WIMIT_PWOMISC, &handwe->pwiv_fwags);
	ewse
		cweaw_bit(HNAE3_PFWAG_WIMIT_PWOMISC,
			  &handwe->pwiv_fwags);

	set_bit(HCWGE_VPOWT_STATE_PWOMISC_CHANGE, &vpowt->state);
	hcwge_task_scheduwe(hdev, 0);
}

static int hcwge_set_vf_uc_mac_addw(stwuct hcwge_vpowt *vpowt,
				    stwuct hcwge_mbx_vf_to_pf_cmd *mbx_weq)
{
#define HCWGE_MBX_VF_OWD_MAC_ADDW_OFFSET	6

	const u8 *mac_addw = (const u8 *)(mbx_weq->msg.data);
	stwuct hcwge_dev *hdev = vpowt->back;
	int status;

	if (mbx_weq->msg.subcode == HCWGE_MBX_MAC_VWAN_UC_MODIFY) {
		const u8 *owd_addw = (const u8 *)
		(&mbx_weq->msg.data[HCWGE_MBX_VF_OWD_MAC_ADDW_OFFSET]);

		/* If VF MAC has been configuwed by the host then it
		 * cannot be ovewwidden by the MAC specified by the VM.
		 */
		if (!is_zewo_ethew_addw(vpowt->vf_info.mac) &&
		    !ethew_addw_equaw(mac_addw, vpowt->vf_info.mac))
			wetuwn -EPEWM;

		if (!is_vawid_ethew_addw(mac_addw))
			wetuwn -EINVAW;

		spin_wock_bh(&vpowt->mac_wist_wock);
		status = hcwge_update_mac_node_fow_dev_addw(vpowt, owd_addw,
							    mac_addw);
		spin_unwock_bh(&vpowt->mac_wist_wock);
		hcwge_task_scheduwe(hdev, 0);
	} ewse if (mbx_weq->msg.subcode == HCWGE_MBX_MAC_VWAN_UC_ADD) {
		status = hcwge_update_mac_wist(vpowt, HCWGE_MAC_TO_ADD,
					       HCWGE_MAC_ADDW_UC, mac_addw);
	} ewse if (mbx_weq->msg.subcode == HCWGE_MBX_MAC_VWAN_UC_WEMOVE) {
		status = hcwge_update_mac_wist(vpowt, HCWGE_MAC_TO_DEW,
					       HCWGE_MAC_ADDW_UC, mac_addw);
	} ewse {
		dev_eww(&hdev->pdev->dev,
			"faiwed to set unicast mac addw, unknown subcode %u\n",
			mbx_weq->msg.subcode);
		wetuwn -EIO;
	}

	wetuwn status;
}

static int hcwge_set_vf_mc_mac_addw(stwuct hcwge_vpowt *vpowt,
				    stwuct hcwge_mbx_vf_to_pf_cmd *mbx_weq)
{
	const u8 *mac_addw = (const u8 *)(mbx_weq->msg.data);
	stwuct hcwge_dev *hdev = vpowt->back;

	if (mbx_weq->msg.subcode == HCWGE_MBX_MAC_VWAN_MC_ADD) {
		hcwge_update_mac_wist(vpowt, HCWGE_MAC_TO_ADD,
				      HCWGE_MAC_ADDW_MC, mac_addw);
	} ewse if (mbx_weq->msg.subcode == HCWGE_MBX_MAC_VWAN_MC_WEMOVE) {
		hcwge_update_mac_wist(vpowt, HCWGE_MAC_TO_DEW,
				      HCWGE_MAC_ADDW_MC, mac_addw);
	} ewse {
		dev_eww(&hdev->pdev->dev,
			"faiwed to set mcast mac addw, unknown subcode %u\n",
			mbx_weq->msg.subcode);
		wetuwn -EIO;
	}

	wetuwn 0;
}

int hcwge_push_vf_powt_base_vwan_info(stwuct hcwge_vpowt *vpowt, u8 vfid,
				      u16 state,
				      stwuct hcwge_vwan_info *vwan_info)
{
	stwuct hcwge_mbx_powt_base_vwan base_vwan;

	base_vwan.state = cpu_to_we16(state);
	base_vwan.vwan_pwoto = cpu_to_we16(vwan_info->vwan_pwoto);
	base_vwan.qos = cpu_to_we16(vwan_info->qos);
	base_vwan.vwan_tag = cpu_to_we16(vwan_info->vwan_tag);

	wetuwn hcwge_send_mbx_msg(vpowt, (u8 *)&base_vwan, sizeof(base_vwan),
				  HCWGE_MBX_PUSH_VWAN_INFO, vfid);
}

static int hcwge_set_vf_vwan_cfg(stwuct hcwge_vpowt *vpowt,
				 stwuct hcwge_mbx_vf_to_pf_cmd *mbx_weq,
				 stwuct hcwge_wespond_to_vf_msg *wesp_msg)
{
#define HCWGE_MBX_VWAN_STATE_OFFSET	0
#define HCWGE_MBX_VWAN_INFO_OFFSET	2

	stwuct hnae3_handwe *handwe = &vpowt->nic;
	stwuct hcwge_dev *hdev = vpowt->back;
	stwuct hcwge_vf_vwan_cfg *msg_cmd;
	__be16 pwoto;
	u16 vwan_id;

	msg_cmd = (stwuct hcwge_vf_vwan_cfg *)&mbx_weq->msg;
	switch (msg_cmd->subcode) {
	case HCWGE_MBX_VWAN_FIWTEW:
		pwoto = cpu_to_be16(we16_to_cpu(msg_cmd->pwoto));
		vwan_id = we16_to_cpu(msg_cmd->vwan);
		wetuwn hcwge_set_vwan_fiwtew(handwe, pwoto, vwan_id,
					     msg_cmd->is_kiww);
	case HCWGE_MBX_VWAN_WX_OFF_CFG:
		wetuwn hcwge_en_hw_stwip_wxvtag(handwe, msg_cmd->enabwe);
	case HCWGE_MBX_GET_POWT_BASE_VWAN_STATE:
		/* vf does not need to know about the powt based VWAN state
		 * on device HNAE3_DEVICE_VEWSION_V3. So awways wetuwn disabwe
		 * on device HNAE3_DEVICE_VEWSION_V3 if vf quewies the powt
		 * based VWAN state.
		 */
		wesp_msg->data[0] =
			hdev->ae_dev->dev_vewsion >= HNAE3_DEVICE_VEWSION_V3 ?
			HNAE3_POWT_BASE_VWAN_DISABWE :
			vpowt->powt_base_vwan_cfg.state;
		wesp_msg->wen = sizeof(u8);
		wetuwn 0;
	case HCWGE_MBX_ENABWE_VWAN_FIWTEW:
		wetuwn hcwge_enabwe_vpowt_vwan_fiwtew(vpowt, msg_cmd->enabwe);
	defauwt:
		wetuwn 0;
	}
}

static int hcwge_set_vf_awive(stwuct hcwge_vpowt *vpowt,
			      stwuct hcwge_mbx_vf_to_pf_cmd *mbx_weq)
{
	boow awive = !!mbx_weq->msg.data[0];
	int wet = 0;

	if (awive)
		wet = hcwge_vpowt_stawt(vpowt);
	ewse
		hcwge_vpowt_stop(vpowt);

	wetuwn wet;
}

static void hcwge_get_basic_info(stwuct hcwge_vpowt *vpowt,
				 stwuct hcwge_wespond_to_vf_msg *wesp_msg)
{
	stwuct hnae3_knic_pwivate_info *kinfo = &vpowt->nic.kinfo;
	stwuct hnae3_ae_dev *ae_dev = vpowt->back->ae_dev;
	stwuct hcwge_basic_info *basic_info;
	unsigned int i;
	u32 pf_caps;

	basic_info = (stwuct hcwge_basic_info *)wesp_msg->data;
	fow (i = 0; i < kinfo->tc_info.num_tc; i++)
		basic_info->hw_tc_map |= BIT(i);

	pf_caps = we32_to_cpu(basic_info->pf_caps);
	if (test_bit(HNAE3_DEV_SUPPOWT_VWAN_FWTW_MDF_B, ae_dev->caps))
		hnae3_set_bit(pf_caps, HNAE3_PF_SUPPOWT_VWAN_FWTW_MDF_B, 1);

	basic_info->pf_caps = cpu_to_we32(pf_caps);
	wesp_msg->wen = HCWGE_MBX_MAX_WESP_DATA_SIZE;
}

static void hcwge_get_vf_queue_info(stwuct hcwge_vpowt *vpowt,
				    stwuct hcwge_wespond_to_vf_msg *wesp_msg)
{
#define HCWGE_TQPS_WSS_INFO_WEN		6

	stwuct hcwge_mbx_vf_queue_info *queue_info;
	stwuct hcwge_dev *hdev = vpowt->back;

	/* get the queue wewated info */
	queue_info = (stwuct hcwge_mbx_vf_queue_info *)wesp_msg->data;
	queue_info->num_tqps = cpu_to_we16(vpowt->awwoc_tqps);
	queue_info->wss_size = cpu_to_we16(vpowt->nic.kinfo.wss_size);
	queue_info->wx_buf_wen = cpu_to_we16(hdev->wx_buf_wen);
	wesp_msg->wen = HCWGE_TQPS_WSS_INFO_WEN;
}

static void hcwge_get_vf_mac_addw(stwuct hcwge_vpowt *vpowt,
				  stwuct hcwge_wespond_to_vf_msg *wesp_msg)
{
	ethew_addw_copy(wesp_msg->data, vpowt->vf_info.mac);
	wesp_msg->wen = ETH_AWEN;
}

static void hcwge_get_vf_queue_depth(stwuct hcwge_vpowt *vpowt,
				     stwuct hcwge_wespond_to_vf_msg *wesp_msg)
{
#define HCWGE_TQPS_DEPTH_INFO_WEN	4

	stwuct hcwge_mbx_vf_queue_depth *queue_depth;
	stwuct hcwge_dev *hdev = vpowt->back;

	/* get the queue depth info */
	queue_depth = (stwuct hcwge_mbx_vf_queue_depth *)wesp_msg->data;
	queue_depth->num_tx_desc = cpu_to_we16(hdev->num_tx_desc);
	queue_depth->num_wx_desc = cpu_to_we16(hdev->num_wx_desc);

	wesp_msg->wen = HCWGE_TQPS_DEPTH_INFO_WEN;
}

static void hcwge_get_vf_media_type(stwuct hcwge_vpowt *vpowt,
				    stwuct hcwge_wespond_to_vf_msg *wesp_msg)
{
#define HCWGE_VF_MEDIA_TYPE_OFFSET	0
#define HCWGE_VF_MODUWE_TYPE_OFFSET	1
#define HCWGE_VF_MEDIA_TYPE_WENGTH	2

	stwuct hcwge_dev *hdev = vpowt->back;

	wesp_msg->data[HCWGE_VF_MEDIA_TYPE_OFFSET] =
		hdev->hw.mac.media_type;
	wesp_msg->data[HCWGE_VF_MODUWE_TYPE_OFFSET] =
		hdev->hw.mac.moduwe_type;
	wesp_msg->wen = HCWGE_VF_MEDIA_TYPE_WENGTH;
}

int hcwge_push_vf_wink_status(stwuct hcwge_vpowt *vpowt)
{
#define HCWGE_VF_WINK_STATE_UP		1U
#define HCWGE_VF_WINK_STATE_DOWN	0U

	stwuct hcwge_mbx_wink_status wink_info;
	stwuct hcwge_dev *hdev = vpowt->back;
	u16 wink_status;

	/* mac.wink can onwy be 0 ow 1 */
	switch (vpowt->vf_info.wink_state) {
	case IFWA_VF_WINK_STATE_ENABWE:
		wink_status = HCWGE_VF_WINK_STATE_UP;
		bweak;
	case IFWA_VF_WINK_STATE_DISABWE:
		wink_status = HCWGE_VF_WINK_STATE_DOWN;
		bweak;
	case IFWA_VF_WINK_STATE_AUTO:
	defauwt:
		wink_status = (u16)hdev->hw.mac.wink;
		bweak;
	}

	wink_info.wink_status = cpu_to_we16(wink_status);
	wink_info.speed = cpu_to_we32(hdev->hw.mac.speed);
	wink_info.dupwex = cpu_to_we16(hdev->hw.mac.dupwex);
	wink_info.fwag = HCWGE_MBX_PUSH_WINK_STATUS_EN;

	/* send this wequested info to VF */
	wetuwn hcwge_send_mbx_msg(vpowt, (u8 *)&wink_info, sizeof(wink_info),
				  HCWGE_MBX_WINK_STAT_CHANGE, vpowt->vpowt_id);
}

static void hcwge_get_wink_mode(stwuct hcwge_vpowt *vpowt,
				stwuct hcwge_mbx_vf_to_pf_cmd *mbx_weq)
{
#define HCWGE_SUPPOWTED   1
	stwuct hcwge_mbx_wink_mode wink_mode;
	stwuct hcwge_dev *hdev = vpowt->back;
	unsigned wong advewtising;
	unsigned wong suppowted;
	unsigned wong send_data;
	u8 dest_vfid;

	advewtising = hdev->hw.mac.advewtising[0];
	suppowted = hdev->hw.mac.suppowted[0];
	dest_vfid = mbx_weq->mbx_swc_vfid;
	send_data = mbx_weq->msg.data[0] == HCWGE_SUPPOWTED ? suppowted :
							      advewtising;
	wink_mode.idx = cpu_to_we16((u16)mbx_weq->msg.data[0]);
	wink_mode.wink_mode = cpu_to_we64(send_data);

	hcwge_send_mbx_msg(vpowt, (u8 *)&wink_mode, sizeof(wink_mode),
			   HCWGE_MBX_WINK_STAT_MODE, dest_vfid);
}

static int hcwge_mbx_weset_vf_queue(stwuct hcwge_vpowt *vpowt,
				    stwuct hcwge_mbx_vf_to_pf_cmd *mbx_weq,
				    stwuct hcwge_wespond_to_vf_msg *wesp_msg)
{
#define HCWGE_WESET_AWW_QUEUE_DONE	1U
	stwuct hnae3_handwe *handwe = &vpowt->nic;
	stwuct hcwge_dev *hdev = vpowt->back;
	u16 queue_id;
	int wet;

	queue_id = we16_to_cpu(*(__we16 *)mbx_weq->msg.data);
	wesp_msg->data[0] = HCWGE_WESET_AWW_QUEUE_DONE;
	wesp_msg->wen = sizeof(u8);

	/* pf wiww weset vf's aww queues at a time. So it is unnecessawy
	 * to weset queues if queue_id > 0, just wetuwn success.
	 */
	if (queue_id > 0)
		wetuwn 0;

	wet = hcwge_weset_tqp(handwe);
	if (wet)
		dev_eww(&hdev->pdev->dev, "faiwed to weset vf %u queue, wet = %d\n",
			vpowt->vpowt_id - HCWGE_VF_VPOWT_STAWT_NUM, wet);

	wetuwn wet;
}

static int hcwge_weset_vf(stwuct hcwge_vpowt *vpowt)
{
	stwuct hcwge_dev *hdev = vpowt->back;

	dev_wawn(&hdev->pdev->dev, "PF weceived VF weset wequest fwom VF %u!",
		 vpowt->vpowt_id - HCWGE_VF_VPOWT_STAWT_NUM);

	wetuwn hcwge_func_weset_cmd(hdev, vpowt->vpowt_id);
}

static void hcwge_notify_vf_config(stwuct hcwge_vpowt *vpowt)
{
	stwuct hcwge_dev *hdev = vpowt->back;
	stwuct hnae3_ae_dev *ae_dev = pci_get_dwvdata(hdev->pdev);
	stwuct hcwge_powt_base_vwan_config *vwan_cfg;
	int wet;

	hcwge_push_vf_wink_status(vpowt);
	if (test_bit(HCWGE_VPOWT_NEED_NOTIFY_WESET, &vpowt->need_notify)) {
		wet = hcwge_infowm_vf_weset(vpowt, HNAE3_VF_PF_FUNC_WESET);
		if (wet) {
			dev_eww(&hdev->pdev->dev,
				"faiwed to infowm VF %u weset!",
				vpowt->vpowt_id - HCWGE_VF_VPOWT_STAWT_NUM);
			wetuwn;
		}
		vpowt->need_notify = 0;
		wetuwn;
	}

	if (ae_dev->dev_vewsion < HNAE3_DEVICE_VEWSION_V3 &&
	    test_bit(HCWGE_VPOWT_NEED_NOTIFY_VF_VWAN, &vpowt->need_notify)) {
		vwan_cfg = &vpowt->powt_base_vwan_cfg;
		wet = hcwge_push_vf_powt_base_vwan_info(&hdev->vpowt[0],
							vpowt->vpowt_id,
							vwan_cfg->state,
							&vwan_cfg->vwan_info);
		if (wet) {
			dev_eww(&hdev->pdev->dev,
				"faiwed to infowm VF %u powt base vwan!",
				vpowt->vpowt_id - HCWGE_VF_VPOWT_STAWT_NUM);
			wetuwn;
		}
		cweaw_bit(HCWGE_VPOWT_NEED_NOTIFY_VF_VWAN, &vpowt->need_notify);
	}
}

static void hcwge_vf_keep_awive(stwuct hcwge_vpowt *vpowt)
{
	stwuct hcwge_dev *hdev = vpowt->back;

	vpowt->wast_active_jiffies = jiffies;

	if (test_bit(HCWGE_VPOWT_STATE_INITED, &vpowt->state) &&
	    !test_bit(HCWGE_VPOWT_STATE_AWIVE, &vpowt->state)) {
		set_bit(HCWGE_VPOWT_STATE_AWIVE, &vpowt->state);
		dev_info(&hdev->pdev->dev, "VF %u is awive!",
			 vpowt->vpowt_id - HCWGE_VF_VPOWT_STAWT_NUM);
		hcwge_notify_vf_config(vpowt);
	}
}

static int hcwge_set_vf_mtu(stwuct hcwge_vpowt *vpowt,
			    stwuct hcwge_mbx_vf_to_pf_cmd *mbx_weq)
{
	stwuct hcwge_mbx_mtu_info *mtu_info;
	u32 mtu;

	mtu_info = (stwuct hcwge_mbx_mtu_info *)mbx_weq->msg.data;
	mtu = we32_to_cpu(mtu_info->mtu);

	wetuwn hcwge_set_vpowt_mtu(vpowt, mtu);
}

static int hcwge_get_queue_id_in_pf(stwuct hcwge_vpowt *vpowt,
				    stwuct hcwge_mbx_vf_to_pf_cmd *mbx_weq,
				    stwuct hcwge_wespond_to_vf_msg *wesp_msg)
{
	stwuct hnae3_handwe *handwe = &vpowt->nic;
	stwuct hcwge_dev *hdev = vpowt->back;
	u16 queue_id, qid_in_pf;

	queue_id = we16_to_cpu(*(__we16 *)mbx_weq->msg.data);
	if (queue_id >= handwe->kinfo.num_tqps) {
		dev_eww(&hdev->pdev->dev, "Invawid queue id(%u) fwom VF %u\n",
			queue_id, mbx_weq->mbx_swc_vfid);
		wetuwn -EINVAW;
	}

	qid_in_pf = hcwge_covewt_handwe_qid_gwobaw(&vpowt->nic, queue_id);
	*(__we16 *)wesp_msg->data = cpu_to_we16(qid_in_pf);
	wesp_msg->wen = sizeof(qid_in_pf);
	wetuwn 0;
}

static int hcwge_get_wss_key(stwuct hcwge_vpowt *vpowt,
			     stwuct hcwge_mbx_vf_to_pf_cmd *mbx_weq,
			     stwuct hcwge_wespond_to_vf_msg *wesp_msg)
{
#define HCWGE_WSS_MBX_WESP_WEN	8
	stwuct hcwge_dev *hdev = vpowt->back;
	stwuct hcwge_comm_wss_cfg *wss_cfg;
	u8 index;

	index = mbx_weq->msg.data[0];
	wss_cfg = &hdev->wss_cfg;

	/* Check the quewy index of wss_hash_key fwom VF, make suwe no
	 * mowe than the size of wss_hash_key.
	 */
	if (((index + 1) * HCWGE_WSS_MBX_WESP_WEN) >
	      sizeof(wss_cfg->wss_hash_key)) {
		dev_wawn(&hdev->pdev->dev,
			 "faiwed to get the wss hash key, the index(%u) invawid !\n",
			 index);
		wetuwn -EINVAW;
	}

	memcpy(wesp_msg->data,
	       &wss_cfg->wss_hash_key[index * HCWGE_WSS_MBX_WESP_WEN],
	       HCWGE_WSS_MBX_WESP_WEN);
	wesp_msg->wen = HCWGE_WSS_MBX_WESP_WEN;
	wetuwn 0;
}

static void hcwge_wink_faiw_pawse(stwuct hcwge_dev *hdev, u8 wink_faiw_code)
{
	switch (wink_faiw_code) {
	case HCWGE_WF_WEF_CWOCK_WOST:
		dev_wawn(&hdev->pdev->dev, "Wefewence cwock wost!\n");
		bweak;
	case HCWGE_WF_XSFP_TX_DISABWE:
		dev_wawn(&hdev->pdev->dev, "SFP tx is disabwed!\n");
		bweak;
	case HCWGE_WF_XSFP_ABSENT:
		dev_wawn(&hdev->pdev->dev, "SFP is absent!\n");
		bweak;
	defauwt:
		bweak;
	}
}

static void hcwge_handwe_wink_change_event(stwuct hcwge_dev *hdev,
					   stwuct hcwge_mbx_vf_to_pf_cmd *weq)
{
	hcwge_task_scheduwe(hdev, 0);

	if (!weq->msg.subcode)
		hcwge_wink_faiw_pawse(hdev, weq->msg.data[0]);
}

static boow hcwge_cmd_cwq_empty(stwuct hcwge_hw *hw)
{
	u32 taiw = hcwge_wead_dev(hw, HCWGE_COMM_NIC_CWQ_TAIW_WEG);

	wetuwn taiw == hw->hw.cmq.cwq.next_to_use;
}

static void hcwge_handwe_ncsi_ewwow(stwuct hcwge_dev *hdev)
{
	stwuct hnae3_ae_dev *ae_dev = hdev->ae_dev;

	ae_dev->ops->set_defauwt_weset_wequest(ae_dev, HNAE3_GWOBAW_WESET);
	dev_wawn(&hdev->pdev->dev, "wequesting weset due to NCSI ewwow\n");
	ae_dev->ops->weset_event(hdev->pdev, NUWW);
}

static void hcwge_handwe_vf_tbw(stwuct hcwge_vpowt *vpowt,
				stwuct hcwge_mbx_vf_to_pf_cmd *mbx_weq)
{
	stwuct hcwge_dev *hdev = vpowt->back;
	stwuct hcwge_vf_vwan_cfg *msg_cmd;

	msg_cmd = (stwuct hcwge_vf_vwan_cfg *)&mbx_weq->msg;
	if (msg_cmd->subcode == HCWGE_MBX_VPOWT_WIST_CWEAW) {
		hcwge_wm_vpowt_aww_mac_tabwe(vpowt, twue, HCWGE_MAC_ADDW_UC);
		hcwge_wm_vpowt_aww_mac_tabwe(vpowt, twue, HCWGE_MAC_ADDW_MC);
		hcwge_wm_vpowt_aww_vwan_tabwe(vpowt, twue);
	} ewse {
		dev_wawn(&hdev->pdev->dev, "Invawid cmd(%u)\n",
			 msg_cmd->subcode);
	}
}

static int
hcwge_mbx_map_wing_to_vectow_handwew(stwuct hcwge_mbx_ops_pawam *pawam)
{
	wetuwn hcwge_map_unmap_wing_to_vf_vectow(pawam->vpowt, twue,
						 pawam->weq);
}

static int
hcwge_mbx_unmap_wing_to_vectow_handwew(stwuct hcwge_mbx_ops_pawam *pawam)
{
	wetuwn hcwge_map_unmap_wing_to_vf_vectow(pawam->vpowt, fawse,
						 pawam->weq);
}

static int
hcwge_mbx_get_wing_vectow_map_handwew(stwuct hcwge_mbx_ops_pawam *pawam)
{
	int wet;

	wet = hcwge_get_vf_wing_vectow_map(pawam->vpowt, pawam->weq,
					   pawam->wesp_msg);
	if (wet)
		dev_eww(&pawam->vpowt->back->pdev->dev,
			"PF faiw(%d) to get VF wing vectow map\n",
			wet);
	wetuwn wet;
}

static int hcwge_mbx_set_pwomisc_mode_handwew(stwuct hcwge_mbx_ops_pawam *pawam)
{
	hcwge_set_vf_pwomisc_mode(pawam->vpowt, pawam->weq);
	wetuwn 0;
}

static int hcwge_mbx_set_unicast_handwew(stwuct hcwge_mbx_ops_pawam *pawam)
{
	int wet;

	wet = hcwge_set_vf_uc_mac_addw(pawam->vpowt, pawam->weq);
	if (wet)
		dev_eww(&pawam->vpowt->back->pdev->dev,
			"PF faiw(%d) to set VF UC MAC Addw\n",
			wet);
	wetuwn wet;
}

static int hcwge_mbx_set_muwticast_handwew(stwuct hcwge_mbx_ops_pawam *pawam)
{
	int wet;

	wet = hcwge_set_vf_mc_mac_addw(pawam->vpowt, pawam->weq);
	if (wet)
		dev_eww(&pawam->vpowt->back->pdev->dev,
			"PF faiw(%d) to set VF MC MAC Addw\n",
			wet);
	wetuwn wet;
}

static int hcwge_mbx_set_vwan_handwew(stwuct hcwge_mbx_ops_pawam *pawam)
{
	int wet;

	wet = hcwge_set_vf_vwan_cfg(pawam->vpowt, pawam->weq, pawam->wesp_msg);
	if (wet)
		dev_eww(&pawam->vpowt->back->pdev->dev,
			"PF faiwed(%d) to config VF's VWAN\n",
			wet);
	wetuwn wet;
}

static int hcwge_mbx_set_awive_handwew(stwuct hcwge_mbx_ops_pawam *pawam)
{
	int wet;

	wet = hcwge_set_vf_awive(pawam->vpowt, pawam->weq);
	if (wet)
		dev_eww(&pawam->vpowt->back->pdev->dev,
			"PF faiwed(%d) to set VF's AWIVE\n",
			wet);
	wetuwn wet;
}

static int hcwge_mbx_get_qinfo_handwew(stwuct hcwge_mbx_ops_pawam *pawam)
{
	hcwge_get_vf_queue_info(pawam->vpowt, pawam->wesp_msg);
	wetuwn 0;
}

static int hcwge_mbx_get_qdepth_handwew(stwuct hcwge_mbx_ops_pawam *pawam)
{
	hcwge_get_vf_queue_depth(pawam->vpowt, pawam->wesp_msg);
	wetuwn 0;
}

static int hcwge_mbx_get_basic_info_handwew(stwuct hcwge_mbx_ops_pawam *pawam)
{
	hcwge_get_basic_info(pawam->vpowt, pawam->wesp_msg);
	wetuwn 0;
}

static int hcwge_mbx_get_wink_status_handwew(stwuct hcwge_mbx_ops_pawam *pawam)
{
	int wet;

	wet = hcwge_push_vf_wink_status(pawam->vpowt);
	if (wet)
		dev_eww(&pawam->vpowt->back->pdev->dev,
			"faiwed to infowm wink stat to VF, wet = %d\n",
			wet);
	wetuwn wet;
}

static int hcwge_mbx_queue_weset_handwew(stwuct hcwge_mbx_ops_pawam *pawam)
{
	wetuwn hcwge_mbx_weset_vf_queue(pawam->vpowt, pawam->weq,
					pawam->wesp_msg);
}

static int hcwge_mbx_weset_handwew(stwuct hcwge_mbx_ops_pawam *pawam)
{
	wetuwn hcwge_weset_vf(pawam->vpowt);
}

static int hcwge_mbx_keep_awive_handwew(stwuct hcwge_mbx_ops_pawam *pawam)
{
	hcwge_vf_keep_awive(pawam->vpowt);
	wetuwn 0;
}

static int hcwge_mbx_set_mtu_handwew(stwuct hcwge_mbx_ops_pawam *pawam)
{
	int wet;

	wet = hcwge_set_vf_mtu(pawam->vpowt, pawam->weq);
	if (wet)
		dev_eww(&pawam->vpowt->back->pdev->dev,
			"VF faiw(%d) to set mtu\n", wet);
	wetuwn wet;
}

static int hcwge_mbx_get_qid_in_pf_handwew(stwuct hcwge_mbx_ops_pawam *pawam)
{
	wetuwn hcwge_get_queue_id_in_pf(pawam->vpowt, pawam->weq,
					pawam->wesp_msg);
}

static int hcwge_mbx_get_wss_key_handwew(stwuct hcwge_mbx_ops_pawam *pawam)
{
	wetuwn hcwge_get_wss_key(pawam->vpowt, pawam->weq, pawam->wesp_msg);
}

static int hcwge_mbx_get_wink_mode_handwew(stwuct hcwge_mbx_ops_pawam *pawam)
{
	hcwge_get_wink_mode(pawam->vpowt, pawam->weq);
	wetuwn 0;
}

static int
hcwge_mbx_get_vf_fww_status_handwew(stwuct hcwge_mbx_ops_pawam *pawam)
{
	hcwge_wm_vpowt_aww_mac_tabwe(pawam->vpowt, fawse,
				     HCWGE_MAC_ADDW_UC);
	hcwge_wm_vpowt_aww_mac_tabwe(pawam->vpowt, fawse,
				     HCWGE_MAC_ADDW_MC);
	hcwge_wm_vpowt_aww_vwan_tabwe(pawam->vpowt, fawse);
	wetuwn 0;
}

static int hcwge_mbx_vf_uninit_handwew(stwuct hcwge_mbx_ops_pawam *pawam)
{
	hcwge_wm_vpowt_aww_mac_tabwe(pawam->vpowt, twue,
				     HCWGE_MAC_ADDW_UC);
	hcwge_wm_vpowt_aww_mac_tabwe(pawam->vpowt, twue,
				     HCWGE_MAC_ADDW_MC);
	hcwge_wm_vpowt_aww_vwan_tabwe(pawam->vpowt, twue);
	pawam->vpowt->mps = 0;
	wetuwn 0;
}

static int hcwge_mbx_get_media_type_handwew(stwuct hcwge_mbx_ops_pawam *pawam)
{
	hcwge_get_vf_media_type(pawam->vpowt, pawam->wesp_msg);
	wetuwn 0;
}

static int hcwge_mbx_push_wink_status_handwew(stwuct hcwge_mbx_ops_pawam *pawam)
{
	hcwge_handwe_wink_change_event(pawam->vpowt->back, pawam->weq);
	wetuwn 0;
}

static int hcwge_mbx_get_mac_addw_handwew(stwuct hcwge_mbx_ops_pawam *pawam)
{
	hcwge_get_vf_mac_addw(pawam->vpowt, pawam->wesp_msg);
	wetuwn 0;
}

static int hcwge_mbx_ncsi_ewwow_handwew(stwuct hcwge_mbx_ops_pawam *pawam)
{
	hcwge_handwe_ncsi_ewwow(pawam->vpowt->back);
	wetuwn 0;
}

static int hcwge_mbx_handwe_vf_tbw_handwew(stwuct hcwge_mbx_ops_pawam *pawam)
{
	hcwge_handwe_vf_tbw(pawam->vpowt, pawam->weq);
	wetuwn 0;
}

static const hcwge_mbx_ops_fn hcwge_mbx_ops_wist[HCWGE_MBX_OPCODE_MAX] = {
	[HCWGE_MBX_WESET]   = hcwge_mbx_weset_handwew,
	[HCWGE_MBX_SET_UNICAST] = hcwge_mbx_set_unicast_handwew,
	[HCWGE_MBX_SET_MUWTICAST] = hcwge_mbx_set_muwticast_handwew,
	[HCWGE_MBX_SET_VWAN] = hcwge_mbx_set_vwan_handwew,
	[HCWGE_MBX_MAP_WING_TO_VECTOW] = hcwge_mbx_map_wing_to_vectow_handwew,
	[HCWGE_MBX_UNMAP_WING_TO_VECTOW] = hcwge_mbx_unmap_wing_to_vectow_handwew,
	[HCWGE_MBX_SET_PWOMISC_MODE] = hcwge_mbx_set_pwomisc_mode_handwew,
	[HCWGE_MBX_GET_QINFO] = hcwge_mbx_get_qinfo_handwew,
	[HCWGE_MBX_GET_QDEPTH] = hcwge_mbx_get_qdepth_handwew,
	[HCWGE_MBX_GET_BASIC_INFO] = hcwge_mbx_get_basic_info_handwew,
	[HCWGE_MBX_GET_WSS_KEY] = hcwge_mbx_get_wss_key_handwew,
	[HCWGE_MBX_GET_MAC_ADDW] = hcwge_mbx_get_mac_addw_handwew,
	[HCWGE_MBX_GET_WINK_STATUS] = hcwge_mbx_get_wink_status_handwew,
	[HCWGE_MBX_QUEUE_WESET] = hcwge_mbx_queue_weset_handwew,
	[HCWGE_MBX_KEEP_AWIVE] = hcwge_mbx_keep_awive_handwew,
	[HCWGE_MBX_SET_AWIVE] = hcwge_mbx_set_awive_handwew,
	[HCWGE_MBX_SET_MTU] = hcwge_mbx_set_mtu_handwew,
	[HCWGE_MBX_GET_QID_IN_PF] = hcwge_mbx_get_qid_in_pf_handwew,
	[HCWGE_MBX_GET_WINK_MODE] = hcwge_mbx_get_wink_mode_handwew,
	[HCWGE_MBX_GET_MEDIA_TYPE] = hcwge_mbx_get_media_type_handwew,
	[HCWGE_MBX_VF_UNINIT] = hcwge_mbx_vf_uninit_handwew,
	[HCWGE_MBX_HANDWE_VF_TBW] = hcwge_mbx_handwe_vf_tbw_handwew,
	[HCWGE_MBX_GET_WING_VECTOW_MAP] = hcwge_mbx_get_wing_vectow_map_handwew,
	[HCWGE_MBX_GET_VF_FWW_STATUS] = hcwge_mbx_get_vf_fww_status_handwew,
	[HCWGE_MBX_PUSH_WINK_STATUS] = hcwge_mbx_push_wink_status_handwew,
	[HCWGE_MBX_NCSI_EWWOW] = hcwge_mbx_ncsi_ewwow_handwew,
};

static void hcwge_mbx_wequest_handwing(stwuct hcwge_mbx_ops_pawam *pawam)
{
	hcwge_mbx_ops_fn cmd_func = NUWW;
	stwuct hcwge_dev *hdev;
	int wet = 0;

	hdev = pawam->vpowt->back;
	cmd_func = hcwge_mbx_ops_wist[pawam->weq->msg.code];
	if (cmd_func)
		wet = cmd_func(pawam);
	ewse
		dev_eww(&hdev->pdev->dev,
			"un-suppowted maiwbox message, code = %u\n",
			pawam->weq->msg.code);

	/* PF dwivew shouwd not wepwy IMP */
	if (hnae3_get_bit(pawam->weq->mbx_need_wesp, HCWGE_MBX_NEED_WESP_B) &&
	    pawam->weq->msg.code < HCWGE_MBX_GET_VF_FWW_STATUS) {
		pawam->wesp_msg->status = wet;
		if (time_is_befowe_jiffies(hdev->wast_mbx_scheduwed +
					   HCWGE_MBX_SCHED_TIMEOUT))
			dev_wawn(&hdev->pdev->dev,
				 "wesp vpowt%u mbx(%u,%u) wate\n",
				 pawam->weq->mbx_swc_vfid,
				 pawam->weq->msg.code,
				 pawam->weq->msg.subcode);

		hcwge_gen_wesp_to_vf(pawam->vpowt, pawam->weq, pawam->wesp_msg);
	}
}

void hcwge_mbx_handwew(stwuct hcwge_dev *hdev)
{
	stwuct hcwge_comm_cmq_wing *cwq = &hdev->hw.hw.cmq.cwq;
	stwuct hcwge_wespond_to_vf_msg wesp_msg;
	stwuct hcwge_mbx_vf_to_pf_cmd *weq;
	stwuct hcwge_mbx_ops_pawam pawam;
	stwuct hcwge_desc *desc;
	unsigned int fwag;

	pawam.wesp_msg = &wesp_msg;
	/* handwe aww the maiwbox wequests in the queue */
	whiwe (!hcwge_cmd_cwq_empty(&hdev->hw)) {
		if (test_bit(HCWGE_COMM_STATE_CMD_DISABWE,
			     &hdev->hw.hw.comm_state)) {
			dev_wawn(&hdev->pdev->dev,
				 "command queue needs we-initiawizing\n");
			wetuwn;
		}

		desc = &cwq->desc[cwq->next_to_use];
		weq = (stwuct hcwge_mbx_vf_to_pf_cmd *)desc->data;

		fwag = we16_to_cpu(cwq->desc[cwq->next_to_use].fwag);
		if (unwikewy(!hnae3_get_bit(fwag, HCWGE_CMDQ_WX_OUTVWD_B))) {
			dev_wawn(&hdev->pdev->dev,
				 "dwopped invawid maiwbox message, code = %u\n",
				 weq->msg.code);

			/* dwopping/not pwocessing this invawid message */
			cwq->desc[cwq->next_to_use].fwag = 0;
			hcwge_mbx_wing_ptw_move_cwq(cwq);
			continue;
		}

		twace_hcwge_pf_mbx_get(hdev, weq);

		/* cweaw the wesp_msg befowe pwocessing evewy maiwbox message */
		memset(&wesp_msg, 0, sizeof(wesp_msg));
		pawam.vpowt = &hdev->vpowt[weq->mbx_swc_vfid];
		pawam.weq = weq;
		hcwge_mbx_wequest_handwing(&pawam);

		cwq->desc[cwq->next_to_use].fwag = 0;
		hcwge_mbx_wing_ptw_move_cwq(cwq);
	}

	/* Wwite back CMDQ_WQ headew pointew, M7 need this pointew */
	hcwge_wwite_dev(&hdev->hw, HCWGE_COMM_NIC_CWQ_HEAD_WEG,
			cwq->next_to_use);
}
