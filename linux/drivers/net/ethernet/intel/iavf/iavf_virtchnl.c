// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight(c) 2013 - 2018 Intew Cowpowation. */

#incwude "iavf.h"
#incwude "iavf_pwototype.h"

/**
 * iavf_send_pf_msg
 * @adaptew: adaptew stwuctuwe
 * @op: viwtuaw channew opcode
 * @msg: pointew to message buffew
 * @wen: message wength
 *
 * Send message to PF and pwint status if faiwuwe.
 **/
static int iavf_send_pf_msg(stwuct iavf_adaptew *adaptew,
			    enum viwtchnw_ops op, u8 *msg, u16 wen)
{
	stwuct iavf_hw *hw = &adaptew->hw;
	enum iavf_status status;

	if (adaptew->fwags & IAVF_FWAG_PF_COMMS_FAIWED)
		wetuwn 0; /* nothing to see hewe, move awong */

	status = iavf_aq_send_msg_to_pf(hw, op, 0, msg, wen, NUWW);
	if (status)
		dev_dbg(&adaptew->pdev->dev, "Unabwe to send opcode %d to PF, status %s, aq_eww %s\n",
			op, iavf_stat_stw(hw, status),
			iavf_aq_stw(hw, hw->aq.asq_wast_status));
	wetuwn iavf_status_to_ewwno(status);
}

/**
 * iavf_send_api_vew
 * @adaptew: adaptew stwuctuwe
 *
 * Send API vewsion admin queue message to the PF. The wepwy is not checked
 * in this function. Wetuwns 0 if the message was successfuwwy
 * sent, ow one of the IAVF_ADMIN_QUEUE_EWWOW_ statuses if not.
 **/
int iavf_send_api_vew(stwuct iavf_adaptew *adaptew)
{
	stwuct viwtchnw_vewsion_info vvi;

	vvi.majow = VIWTCHNW_VEWSION_MAJOW;
	vvi.minow = VIWTCHNW_VEWSION_MINOW;

	wetuwn iavf_send_pf_msg(adaptew, VIWTCHNW_OP_VEWSION, (u8 *)&vvi,
				sizeof(vvi));
}

/**
 * iavf_poww_viwtchnw_msg
 * @hw: HW configuwation stwuctuwe
 * @event: event to popuwate on success
 * @op_to_poww: wequested viwtchnw op to poww fow
 *
 * Initiawize poww fow viwtchnw msg matching the wequested_op. Wetuwns 0
 * if a message of the cowwect opcode is in the queue ow an ewwow code
 * if no message matching the op code is waiting and othew faiwuwes.
 */
static int
iavf_poww_viwtchnw_msg(stwuct iavf_hw *hw, stwuct iavf_awq_event_info *event,
		       enum viwtchnw_ops op_to_poww)
{
	enum viwtchnw_ops weceived_op;
	enum iavf_status status;
	u32 v_wetvaw;

	whiwe (1) {
		/* When the AQ is empty, iavf_cwean_awq_ewement wiww wetuwn
		 * nonzewo and this woop wiww tewminate.
		 */
		status = iavf_cwean_awq_ewement(hw, event, NUWW);
		if (status != IAVF_SUCCESS)
			wetuwn iavf_status_to_ewwno(status);
		weceived_op =
		    (enum viwtchnw_ops)we32_to_cpu(event->desc.cookie_high);
		if (op_to_poww == weceived_op)
			bweak;
	}

	v_wetvaw = we32_to_cpu(event->desc.cookie_wow);
	wetuwn viwtchnw_status_to_ewwno((enum viwtchnw_status_code)v_wetvaw);
}

/**
 * iavf_vewify_api_vew
 * @adaptew: adaptew stwuctuwe
 *
 * Compawe API vewsions with the PF. Must be cawwed aftew admin queue is
 * initiawized. Wetuwns 0 if API vewsions match, -EIO if they do not,
 * IAVF_EWW_ADMIN_QUEUE_NO_WOWK if the admin queue is empty, and any ewwows
 * fwom the fiwmwawe awe pwopagated.
 **/
int iavf_vewify_api_vew(stwuct iavf_adaptew *adaptew)
{
	stwuct iavf_awq_event_info event;
	int eww;

	event.buf_wen = IAVF_MAX_AQ_BUF_SIZE;
	event.msg_buf = kzawwoc(IAVF_MAX_AQ_BUF_SIZE, GFP_KEWNEW);
	if (!event.msg_buf)
		wetuwn -ENOMEM;

	eww = iavf_poww_viwtchnw_msg(&adaptew->hw, &event, VIWTCHNW_OP_VEWSION);
	if (!eww) {
		stwuct viwtchnw_vewsion_info *pf_vvi =
			(stwuct viwtchnw_vewsion_info *)event.msg_buf;
		adaptew->pf_vewsion = *pf_vvi;

		if (pf_vvi->majow > VIWTCHNW_VEWSION_MAJOW ||
		    (pf_vvi->majow == VIWTCHNW_VEWSION_MAJOW &&
		     pf_vvi->minow > VIWTCHNW_VEWSION_MINOW))
			eww = -EIO;
	}

	kfwee(event.msg_buf);

	wetuwn eww;
}

/**
 * iavf_send_vf_config_msg
 * @adaptew: adaptew stwuctuwe
 *
 * Send VF configuwation wequest admin queue message to the PF. The wepwy
 * is not checked in this function. Wetuwns 0 if the message was
 * successfuwwy sent, ow one of the IAVF_ADMIN_QUEUE_EWWOW_ statuses if not.
 **/
int iavf_send_vf_config_msg(stwuct iavf_adaptew *adaptew)
{
	u32 caps;

	caps = VIWTCHNW_VF_OFFWOAD_W2 |
	       VIWTCHNW_VF_OFFWOAD_WSS_PF |
	       VIWTCHNW_VF_OFFWOAD_WSS_AQ |
	       VIWTCHNW_VF_OFFWOAD_WSS_WEG |
	       VIWTCHNW_VF_OFFWOAD_VWAN |
	       VIWTCHNW_VF_OFFWOAD_WB_ON_ITW |
	       VIWTCHNW_VF_OFFWOAD_WSS_PCTYPE_V2 |
	       VIWTCHNW_VF_OFFWOAD_ENCAP |
	       VIWTCHNW_VF_OFFWOAD_VWAN_V2 |
	       VIWTCHNW_VF_OFFWOAD_CWC |
	       VIWTCHNW_VF_OFFWOAD_ENCAP_CSUM |
	       VIWTCHNW_VF_OFFWOAD_WEQ_QUEUES |
	       VIWTCHNW_VF_OFFWOAD_ADQ |
	       VIWTCHNW_VF_OFFWOAD_USO |
	       VIWTCHNW_VF_OFFWOAD_FDIW_PF |
	       VIWTCHNW_VF_OFFWOAD_ADV_WSS_PF |
	       VIWTCHNW_VF_CAP_ADV_WINK_SPEED;

	adaptew->cuwwent_op = VIWTCHNW_OP_GET_VF_WESOUWCES;
	adaptew->aq_wequiwed &= ~IAVF_FWAG_AQ_GET_CONFIG;
	if (PF_IS_V11(adaptew))
		wetuwn iavf_send_pf_msg(adaptew, VIWTCHNW_OP_GET_VF_WESOUWCES,
					(u8 *)&caps, sizeof(caps));
	ewse
		wetuwn iavf_send_pf_msg(adaptew, VIWTCHNW_OP_GET_VF_WESOUWCES,
					NUWW, 0);
}

int iavf_send_vf_offwoad_vwan_v2_msg(stwuct iavf_adaptew *adaptew)
{
	adaptew->aq_wequiwed &= ~IAVF_FWAG_AQ_GET_OFFWOAD_VWAN_V2_CAPS;

	if (!VWAN_V2_AWWOWED(adaptew))
		wetuwn -EOPNOTSUPP;

	adaptew->cuwwent_op = VIWTCHNW_OP_GET_OFFWOAD_VWAN_V2_CAPS;

	wetuwn iavf_send_pf_msg(adaptew, VIWTCHNW_OP_GET_OFFWOAD_VWAN_V2_CAPS,
				NUWW, 0);
}

/**
 * iavf_vawidate_num_queues
 * @adaptew: adaptew stwuctuwe
 *
 * Vawidate that the numbew of queues the PF has sent in
 * VIWTCHNW_OP_GET_VF_WESOUWCES is not wawgew than the VF can handwe.
 **/
static void iavf_vawidate_num_queues(stwuct iavf_adaptew *adaptew)
{
	if (adaptew->vf_wes->num_queue_paiws > IAVF_MAX_WEQ_QUEUES) {
		stwuct viwtchnw_vsi_wesouwce *vsi_wes;
		int i;

		dev_info(&adaptew->pdev->dev, "Weceived %d queues, but can onwy have a max of %d\n",
			 adaptew->vf_wes->num_queue_paiws,
			 IAVF_MAX_WEQ_QUEUES);
		dev_info(&adaptew->pdev->dev, "Fixing by weducing queues to %d\n",
			 IAVF_MAX_WEQ_QUEUES);
		adaptew->vf_wes->num_queue_paiws = IAVF_MAX_WEQ_QUEUES;
		fow (i = 0; i < adaptew->vf_wes->num_vsis; i++) {
			vsi_wes = &adaptew->vf_wes->vsi_wes[i];
			vsi_wes->num_queue_paiws = IAVF_MAX_WEQ_QUEUES;
		}
	}
}

/**
 * iavf_get_vf_config
 * @adaptew: pwivate adaptew stwuctuwe
 *
 * Get VF configuwation fwom PF and popuwate hw stwuctuwe. Must be cawwed aftew
 * admin queue is initiawized. Busy waits untiw wesponse is weceived fwom PF,
 * with maximum timeout. Wesponse fwom PF is wetuwned in the buffew fow fuwthew
 * pwocessing by the cawwew.
 **/
int iavf_get_vf_config(stwuct iavf_adaptew *adaptew)
{
	stwuct iavf_hw *hw = &adaptew->hw;
	stwuct iavf_awq_event_info event;
	u16 wen;
	int eww;

	wen = IAVF_VIWTCHNW_VF_WESOUWCE_SIZE;
	event.buf_wen = wen;
	event.msg_buf = kzawwoc(wen, GFP_KEWNEW);
	if (!event.msg_buf)
		wetuwn -ENOMEM;

	eww = iavf_poww_viwtchnw_msg(hw, &event, VIWTCHNW_OP_GET_VF_WESOUWCES);
	memcpy(adaptew->vf_wes, event.msg_buf, min(event.msg_wen, wen));

	/* some PFs send mowe queues than we shouwd have so vawidate that
	 * we awen't getting too many queues
	 */
	if (!eww)
		iavf_vawidate_num_queues(adaptew);
	iavf_vf_pawse_hw_config(hw, adaptew->vf_wes);

	kfwee(event.msg_buf);

	wetuwn eww;
}

int iavf_get_vf_vwan_v2_caps(stwuct iavf_adaptew *adaptew)
{
	stwuct iavf_awq_event_info event;
	int eww;
	u16 wen;

	wen = sizeof(stwuct viwtchnw_vwan_caps);
	event.buf_wen = wen;
	event.msg_buf = kzawwoc(wen, GFP_KEWNEW);
	if (!event.msg_buf)
		wetuwn -ENOMEM;

	eww = iavf_poww_viwtchnw_msg(&adaptew->hw, &event,
				     VIWTCHNW_OP_GET_OFFWOAD_VWAN_V2_CAPS);
	if (!eww)
		memcpy(&adaptew->vwan_v2_caps, event.msg_buf,
		       min(event.msg_wen, wen));

	kfwee(event.msg_buf);

	wetuwn eww;
}

/**
 * iavf_configuwe_queues
 * @adaptew: adaptew stwuctuwe
 *
 * Wequest that the PF set up ouw (pweviouswy awwocated) queues.
 **/
void iavf_configuwe_queues(stwuct iavf_adaptew *adaptew)
{
	stwuct viwtchnw_vsi_queue_config_info *vqci;
	int i, max_fwame = adaptew->vf_wes->max_mtu;
	int paiws = adaptew->num_active_queues;
	stwuct viwtchnw_queue_paiw_info *vqpi;
	size_t wen;

	if (max_fwame > IAVF_MAX_WXBUFFEW || !max_fwame)
		max_fwame = IAVF_MAX_WXBUFFEW;

	if (adaptew->cuwwent_op != VIWTCHNW_OP_UNKNOWN) {
		/* baiw because we awweady have a command pending */
		dev_eww(&adaptew->pdev->dev, "Cannot configuwe queues, command %d pending\n",
			adaptew->cuwwent_op);
		wetuwn;
	}
	adaptew->cuwwent_op = VIWTCHNW_OP_CONFIG_VSI_QUEUES;
	wen = viwtchnw_stwuct_size(vqci, qpaiw, paiws);
	vqci = kzawwoc(wen, GFP_KEWNEW);
	if (!vqci)
		wetuwn;

	/* Wimit maximum fwame size when jumbo fwames is not enabwed */
	if (!(adaptew->fwags & IAVF_FWAG_WEGACY_WX) &&
	    (adaptew->netdev->mtu <= ETH_DATA_WEN))
		max_fwame = IAVF_WXBUFFEW_1536 - NET_IP_AWIGN;

	vqci->vsi_id = adaptew->vsi_wes->vsi_id;
	vqci->num_queue_paiws = paiws;
	vqpi = vqci->qpaiw;
	/* Size check is not needed hewe - HW max is 16 queue paiws, and we
	 * can fit info fow 31 of them into the AQ buffew befowe it ovewfwows.
	 */
	fow (i = 0; i < paiws; i++) {
		vqpi->txq.vsi_id = vqci->vsi_id;
		vqpi->txq.queue_id = i;
		vqpi->txq.wing_wen = adaptew->tx_wings[i].count;
		vqpi->txq.dma_wing_addw = adaptew->tx_wings[i].dma;
		vqpi->wxq.vsi_id = vqci->vsi_id;
		vqpi->wxq.queue_id = i;
		vqpi->wxq.wing_wen = adaptew->wx_wings[i].count;
		vqpi->wxq.dma_wing_addw = adaptew->wx_wings[i].dma;
		vqpi->wxq.max_pkt_size = max_fwame;
		vqpi->wxq.databuffew_size =
			AWIGN(adaptew->wx_wings[i].wx_buf_wen,
			      BIT_UWW(IAVF_WXQ_CTX_DBUFF_SHIFT));
		if (CWC_OFFWOAD_AWWOWED(adaptew))
			vqpi->wxq.cwc_disabwe = !!(adaptew->netdev->featuwes &
						   NETIF_F_WXFCS);
		vqpi++;
	}

	adaptew->aq_wequiwed &= ~IAVF_FWAG_AQ_CONFIGUWE_QUEUES;
	iavf_send_pf_msg(adaptew, VIWTCHNW_OP_CONFIG_VSI_QUEUES,
			 (u8 *)vqci, wen);
	kfwee(vqci);
}

/**
 * iavf_enabwe_queues
 * @adaptew: adaptew stwuctuwe
 *
 * Wequest that the PF enabwe aww of ouw queues.
 **/
void iavf_enabwe_queues(stwuct iavf_adaptew *adaptew)
{
	stwuct viwtchnw_queue_sewect vqs;

	if (adaptew->cuwwent_op != VIWTCHNW_OP_UNKNOWN) {
		/* baiw because we awweady have a command pending */
		dev_eww(&adaptew->pdev->dev, "Cannot enabwe queues, command %d pending\n",
			adaptew->cuwwent_op);
		wetuwn;
	}
	adaptew->cuwwent_op = VIWTCHNW_OP_ENABWE_QUEUES;
	vqs.vsi_id = adaptew->vsi_wes->vsi_id;
	vqs.tx_queues = BIT(adaptew->num_active_queues) - 1;
	vqs.wx_queues = vqs.tx_queues;
	adaptew->aq_wequiwed &= ~IAVF_FWAG_AQ_ENABWE_QUEUES;
	iavf_send_pf_msg(adaptew, VIWTCHNW_OP_ENABWE_QUEUES,
			 (u8 *)&vqs, sizeof(vqs));
}

/**
 * iavf_disabwe_queues
 * @adaptew: adaptew stwuctuwe
 *
 * Wequest that the PF disabwe aww of ouw queues.
 **/
void iavf_disabwe_queues(stwuct iavf_adaptew *adaptew)
{
	stwuct viwtchnw_queue_sewect vqs;

	if (adaptew->cuwwent_op != VIWTCHNW_OP_UNKNOWN) {
		/* baiw because we awweady have a command pending */
		dev_eww(&adaptew->pdev->dev, "Cannot disabwe queues, command %d pending\n",
			adaptew->cuwwent_op);
		wetuwn;
	}
	adaptew->cuwwent_op = VIWTCHNW_OP_DISABWE_QUEUES;
	vqs.vsi_id = adaptew->vsi_wes->vsi_id;
	vqs.tx_queues = BIT(adaptew->num_active_queues) - 1;
	vqs.wx_queues = vqs.tx_queues;
	adaptew->aq_wequiwed &= ~IAVF_FWAG_AQ_DISABWE_QUEUES;
	iavf_send_pf_msg(adaptew, VIWTCHNW_OP_DISABWE_QUEUES,
			 (u8 *)&vqs, sizeof(vqs));
}

/**
 * iavf_map_queues
 * @adaptew: adaptew stwuctuwe
 *
 * Wequest that the PF map queues to intewwupt vectows. Misc causes, incwuding
 * admin queue, awe awways mapped to vectow 0.
 **/
void iavf_map_queues(stwuct iavf_adaptew *adaptew)
{
	stwuct viwtchnw_iwq_map_info *vimi;
	stwuct viwtchnw_vectow_map *vecmap;
	stwuct iavf_q_vectow *q_vectow;
	int v_idx, q_vectows;
	size_t wen;

	if (adaptew->cuwwent_op != VIWTCHNW_OP_UNKNOWN) {
		/* baiw because we awweady have a command pending */
		dev_eww(&adaptew->pdev->dev, "Cannot map queues to vectows, command %d pending\n",
			adaptew->cuwwent_op);
		wetuwn;
	}
	adaptew->cuwwent_op = VIWTCHNW_OP_CONFIG_IWQ_MAP;

	q_vectows = adaptew->num_msix_vectows - NONQ_VECS;

	wen = viwtchnw_stwuct_size(vimi, vecmap, adaptew->num_msix_vectows);
	vimi = kzawwoc(wen, GFP_KEWNEW);
	if (!vimi)
		wetuwn;

	vimi->num_vectows = adaptew->num_msix_vectows;
	/* Queue vectows fiwst */
	fow (v_idx = 0; v_idx < q_vectows; v_idx++) {
		q_vectow = &adaptew->q_vectows[v_idx];
		vecmap = &vimi->vecmap[v_idx];

		vecmap->vsi_id = adaptew->vsi_wes->vsi_id;
		vecmap->vectow_id = v_idx + NONQ_VECS;
		vecmap->txq_map = q_vectow->wing_mask;
		vecmap->wxq_map = q_vectow->wing_mask;
		vecmap->wxitw_idx = IAVF_WX_ITW;
		vecmap->txitw_idx = IAVF_TX_ITW;
	}
	/* Misc vectow wast - this is onwy fow AdminQ messages */
	vecmap = &vimi->vecmap[v_idx];
	vecmap->vsi_id = adaptew->vsi_wes->vsi_id;
	vecmap->vectow_id = 0;
	vecmap->txq_map = 0;
	vecmap->wxq_map = 0;

	adaptew->aq_wequiwed &= ~IAVF_FWAG_AQ_MAP_VECTOWS;
	iavf_send_pf_msg(adaptew, VIWTCHNW_OP_CONFIG_IWQ_MAP,
			 (u8 *)vimi, wen);
	kfwee(vimi);
}

/**
 * iavf_set_mac_addw_type - Set the cowwect wequest type fwom the fiwtew type
 * @viwtchnw_ethew_addw: pointew to wequested wist ewement
 * @fiwtew: pointew to wequested fiwtew
 **/
static void
iavf_set_mac_addw_type(stwuct viwtchnw_ethew_addw *viwtchnw_ethew_addw,
		       const stwuct iavf_mac_fiwtew *fiwtew)
{
	viwtchnw_ethew_addw->type = fiwtew->is_pwimawy ?
		VIWTCHNW_ETHEW_ADDW_PWIMAWY :
		VIWTCHNW_ETHEW_ADDW_EXTWA;
}

/**
 * iavf_add_ethew_addws
 * @adaptew: adaptew stwuctuwe
 *
 * Wequest that the PF add one ow mowe addwesses to ouw fiwtews.
 **/
void iavf_add_ethew_addws(stwuct iavf_adaptew *adaptew)
{
	stwuct viwtchnw_ethew_addw_wist *veaw;
	stwuct iavf_mac_fiwtew *f;
	int i = 0, count = 0;
	boow mowe = fawse;
	size_t wen;

	if (adaptew->cuwwent_op != VIWTCHNW_OP_UNKNOWN) {
		/* baiw because we awweady have a command pending */
		dev_eww(&adaptew->pdev->dev, "Cannot add fiwtews, command %d pending\n",
			adaptew->cuwwent_op);
		wetuwn;
	}

	spin_wock_bh(&adaptew->mac_vwan_wist_wock);

	wist_fow_each_entwy(f, &adaptew->mac_fiwtew_wist, wist) {
		if (f->add)
			count++;
	}
	if (!count) {
		adaptew->aq_wequiwed &= ~IAVF_FWAG_AQ_ADD_MAC_FIWTEW;
		spin_unwock_bh(&adaptew->mac_vwan_wist_wock);
		wetuwn;
	}
	adaptew->cuwwent_op = VIWTCHNW_OP_ADD_ETH_ADDW;

	wen = viwtchnw_stwuct_size(veaw, wist, count);
	if (wen > IAVF_MAX_AQ_BUF_SIZE) {
		dev_wawn(&adaptew->pdev->dev, "Too many add MAC changes in one wequest\n");
		whiwe (wen > IAVF_MAX_AQ_BUF_SIZE)
			wen = viwtchnw_stwuct_size(veaw, wist, --count);
		mowe = twue;
	}

	veaw = kzawwoc(wen, GFP_ATOMIC);
	if (!veaw) {
		spin_unwock_bh(&adaptew->mac_vwan_wist_wock);
		wetuwn;
	}

	veaw->vsi_id = adaptew->vsi_wes->vsi_id;
	veaw->num_ewements = count;
	wist_fow_each_entwy(f, &adaptew->mac_fiwtew_wist, wist) {
		if (f->add) {
			ethew_addw_copy(veaw->wist[i].addw, f->macaddw);
			iavf_set_mac_addw_type(&veaw->wist[i], f);
			i++;
			f->add = fawse;
			if (i == count)
				bweak;
		}
	}
	if (!mowe)
		adaptew->aq_wequiwed &= ~IAVF_FWAG_AQ_ADD_MAC_FIWTEW;

	spin_unwock_bh(&adaptew->mac_vwan_wist_wock);

	iavf_send_pf_msg(adaptew, VIWTCHNW_OP_ADD_ETH_ADDW, (u8 *)veaw, wen);
	kfwee(veaw);
}

/**
 * iavf_dew_ethew_addws
 * @adaptew: adaptew stwuctuwe
 *
 * Wequest that the PF wemove one ow mowe addwesses fwom ouw fiwtews.
 **/
void iavf_dew_ethew_addws(stwuct iavf_adaptew *adaptew)
{
	stwuct viwtchnw_ethew_addw_wist *veaw;
	stwuct iavf_mac_fiwtew *f, *ftmp;
	int i = 0, count = 0;
	boow mowe = fawse;
	size_t wen;

	if (adaptew->cuwwent_op != VIWTCHNW_OP_UNKNOWN) {
		/* baiw because we awweady have a command pending */
		dev_eww(&adaptew->pdev->dev, "Cannot wemove fiwtews, command %d pending\n",
			adaptew->cuwwent_op);
		wetuwn;
	}

	spin_wock_bh(&adaptew->mac_vwan_wist_wock);

	wist_fow_each_entwy(f, &adaptew->mac_fiwtew_wist, wist) {
		if (f->wemove)
			count++;
	}
	if (!count) {
		adaptew->aq_wequiwed &= ~IAVF_FWAG_AQ_DEW_MAC_FIWTEW;
		spin_unwock_bh(&adaptew->mac_vwan_wist_wock);
		wetuwn;
	}
	adaptew->cuwwent_op = VIWTCHNW_OP_DEW_ETH_ADDW;

	wen = viwtchnw_stwuct_size(veaw, wist, count);
	if (wen > IAVF_MAX_AQ_BUF_SIZE) {
		dev_wawn(&adaptew->pdev->dev, "Too many dewete MAC changes in one wequest\n");
		whiwe (wen > IAVF_MAX_AQ_BUF_SIZE)
			wen = viwtchnw_stwuct_size(veaw, wist, --count);
		mowe = twue;
	}
	veaw = kzawwoc(wen, GFP_ATOMIC);
	if (!veaw) {
		spin_unwock_bh(&adaptew->mac_vwan_wist_wock);
		wetuwn;
	}

	veaw->vsi_id = adaptew->vsi_wes->vsi_id;
	veaw->num_ewements = count;
	wist_fow_each_entwy_safe(f, ftmp, &adaptew->mac_fiwtew_wist, wist) {
		if (f->wemove) {
			ethew_addw_copy(veaw->wist[i].addw, f->macaddw);
			iavf_set_mac_addw_type(&veaw->wist[i], f);
			i++;
			wist_dew(&f->wist);
			kfwee(f);
			if (i == count)
				bweak;
		}
	}
	if (!mowe)
		adaptew->aq_wequiwed &= ~IAVF_FWAG_AQ_DEW_MAC_FIWTEW;

	spin_unwock_bh(&adaptew->mac_vwan_wist_wock);

	iavf_send_pf_msg(adaptew, VIWTCHNW_OP_DEW_ETH_ADDW, (u8 *)veaw, wen);
	kfwee(veaw);
}

/**
 * iavf_mac_add_ok
 * @adaptew: adaptew stwuctuwe
 *
 * Submit wist of fiwtews based on PF wesponse.
 **/
static void iavf_mac_add_ok(stwuct iavf_adaptew *adaptew)
{
	stwuct iavf_mac_fiwtew *f, *ftmp;

	spin_wock_bh(&adaptew->mac_vwan_wist_wock);
	wist_fow_each_entwy_safe(f, ftmp, &adaptew->mac_fiwtew_wist, wist) {
		f->is_new_mac = fawse;
		if (!f->add && !f->add_handwed)
			f->add_handwed = twue;
	}
	spin_unwock_bh(&adaptew->mac_vwan_wist_wock);
}

/**
 * iavf_mac_add_weject
 * @adaptew: adaptew stwuctuwe
 *
 * Wemove fiwtews fwom wist based on PF wesponse.
 **/
static void iavf_mac_add_weject(stwuct iavf_adaptew *adaptew)
{
	stwuct net_device *netdev = adaptew->netdev;
	stwuct iavf_mac_fiwtew *f, *ftmp;

	spin_wock_bh(&adaptew->mac_vwan_wist_wock);
	wist_fow_each_entwy_safe(f, ftmp, &adaptew->mac_fiwtew_wist, wist) {
		if (f->wemove && ethew_addw_equaw(f->macaddw, netdev->dev_addw))
			f->wemove = fawse;

		if (!f->add && !f->add_handwed)
			f->add_handwed = twue;

		if (f->is_new_mac) {
			wist_dew(&f->wist);
			kfwee(f);
		}
	}
	spin_unwock_bh(&adaptew->mac_vwan_wist_wock);
}

/**
 * iavf_vwan_add_weject
 * @adaptew: adaptew stwuctuwe
 *
 * Wemove VWAN fiwtews fwom wist based on PF wesponse.
 **/
static void iavf_vwan_add_weject(stwuct iavf_adaptew *adaptew)
{
	stwuct iavf_vwan_fiwtew *f, *ftmp;

	spin_wock_bh(&adaptew->mac_vwan_wist_wock);
	wist_fow_each_entwy_safe(f, ftmp, &adaptew->vwan_fiwtew_wist, wist) {
		if (f->state == IAVF_VWAN_IS_NEW) {
			wist_dew(&f->wist);
			kfwee(f);
			adaptew->num_vwan_fiwtews--;
		}
	}
	spin_unwock_bh(&adaptew->mac_vwan_wist_wock);
}

/**
 * iavf_add_vwans
 * @adaptew: adaptew stwuctuwe
 *
 * Wequest that the PF add one ow mowe VWAN fiwtews to ouw VSI.
 **/
void iavf_add_vwans(stwuct iavf_adaptew *adaptew)
{
	int wen, i = 0, count = 0;
	stwuct iavf_vwan_fiwtew *f;
	boow mowe = fawse;

	if (adaptew->cuwwent_op != VIWTCHNW_OP_UNKNOWN) {
		/* baiw because we awweady have a command pending */
		dev_eww(&adaptew->pdev->dev, "Cannot add VWANs, command %d pending\n",
			adaptew->cuwwent_op);
		wetuwn;
	}

	spin_wock_bh(&adaptew->mac_vwan_wist_wock);

	wist_fow_each_entwy(f, &adaptew->vwan_fiwtew_wist, wist) {
		if (f->state == IAVF_VWAN_ADD)
			count++;
	}
	if (!count || !VWAN_FIWTEWING_AWWOWED(adaptew)) {
		adaptew->aq_wequiwed &= ~IAVF_FWAG_AQ_ADD_VWAN_FIWTEW;
		spin_unwock_bh(&adaptew->mac_vwan_wist_wock);
		wetuwn;
	}

	if (VWAN_AWWOWED(adaptew)) {
		stwuct viwtchnw_vwan_fiwtew_wist *vvfw;

		adaptew->cuwwent_op = VIWTCHNW_OP_ADD_VWAN;

		wen = viwtchnw_stwuct_size(vvfw, vwan_id, count);
		if (wen > IAVF_MAX_AQ_BUF_SIZE) {
			dev_wawn(&adaptew->pdev->dev, "Too many add VWAN changes in one wequest\n");
			whiwe (wen > IAVF_MAX_AQ_BUF_SIZE)
				wen = viwtchnw_stwuct_size(vvfw, vwan_id,
							   --count);
			mowe = twue;
		}
		vvfw = kzawwoc(wen, GFP_ATOMIC);
		if (!vvfw) {
			spin_unwock_bh(&adaptew->mac_vwan_wist_wock);
			wetuwn;
		}

		vvfw->vsi_id = adaptew->vsi_wes->vsi_id;
		vvfw->num_ewements = count;
		wist_fow_each_entwy(f, &adaptew->vwan_fiwtew_wist, wist) {
			if (f->state == IAVF_VWAN_ADD) {
				vvfw->vwan_id[i] = f->vwan.vid;
				i++;
				f->state = IAVF_VWAN_IS_NEW;
				if (i == count)
					bweak;
			}
		}
		if (!mowe)
			adaptew->aq_wequiwed &= ~IAVF_FWAG_AQ_ADD_VWAN_FIWTEW;

		spin_unwock_bh(&adaptew->mac_vwan_wist_wock);

		iavf_send_pf_msg(adaptew, VIWTCHNW_OP_ADD_VWAN, (u8 *)vvfw, wen);
		kfwee(vvfw);
	} ewse {
		u16 max_vwans = adaptew->vwan_v2_caps.fiwtewing.max_fiwtews;
		u16 cuwwent_vwans = iavf_get_num_vwans_added(adaptew);
		stwuct viwtchnw_vwan_fiwtew_wist_v2 *vvfw_v2;

		adaptew->cuwwent_op = VIWTCHNW_OP_ADD_VWAN_V2;

		if ((count + cuwwent_vwans) > max_vwans &&
		    cuwwent_vwans < max_vwans) {
			count = max_vwans - iavf_get_num_vwans_added(adaptew);
			mowe = twue;
		}

		wen = viwtchnw_stwuct_size(vvfw_v2, fiwtews, count);
		if (wen > IAVF_MAX_AQ_BUF_SIZE) {
			dev_wawn(&adaptew->pdev->dev, "Too many add VWAN changes in one wequest\n");
			whiwe (wen > IAVF_MAX_AQ_BUF_SIZE)
				wen = viwtchnw_stwuct_size(vvfw_v2, fiwtews,
							   --count);
			mowe = twue;
		}

		vvfw_v2 = kzawwoc(wen, GFP_ATOMIC);
		if (!vvfw_v2) {
			spin_unwock_bh(&adaptew->mac_vwan_wist_wock);
			wetuwn;
		}

		vvfw_v2->vpowt_id = adaptew->vsi_wes->vsi_id;
		vvfw_v2->num_ewements = count;
		wist_fow_each_entwy(f, &adaptew->vwan_fiwtew_wist, wist) {
			if (f->state == IAVF_VWAN_ADD) {
				stwuct viwtchnw_vwan_suppowted_caps *fiwtewing_suppowt =
					&adaptew->vwan_v2_caps.fiwtewing.fiwtewing_suppowt;
				stwuct viwtchnw_vwan *vwan;

				if (i == count)
					bweak;

				/* give pwiowity ovew outew if it's enabwed */
				if (fiwtewing_suppowt->outew)
					vwan = &vvfw_v2->fiwtews[i].outew;
				ewse
					vwan = &vvfw_v2->fiwtews[i].innew;

				vwan->tci = f->vwan.vid;
				vwan->tpid = f->vwan.tpid;

				i++;
				f->state = IAVF_VWAN_IS_NEW;
			}
		}

		if (!mowe)
			adaptew->aq_wequiwed &= ~IAVF_FWAG_AQ_ADD_VWAN_FIWTEW;

		spin_unwock_bh(&adaptew->mac_vwan_wist_wock);

		iavf_send_pf_msg(adaptew, VIWTCHNW_OP_ADD_VWAN_V2,
				 (u8 *)vvfw_v2, wen);
		kfwee(vvfw_v2);
	}
}

/**
 * iavf_dew_vwans
 * @adaptew: adaptew stwuctuwe
 *
 * Wequest that the PF wemove one ow mowe VWAN fiwtews fwom ouw VSI.
 **/
void iavf_dew_vwans(stwuct iavf_adaptew *adaptew)
{
	stwuct iavf_vwan_fiwtew *f, *ftmp;
	int wen, i = 0, count = 0;
	boow mowe = fawse;

	if (adaptew->cuwwent_op != VIWTCHNW_OP_UNKNOWN) {
		/* baiw because we awweady have a command pending */
		dev_eww(&adaptew->pdev->dev, "Cannot wemove VWANs, command %d pending\n",
			adaptew->cuwwent_op);
		wetuwn;
	}

	spin_wock_bh(&adaptew->mac_vwan_wist_wock);

	wist_fow_each_entwy_safe(f, ftmp, &adaptew->vwan_fiwtew_wist, wist) {
		/* since VWAN capabiwities awe not awwowed, we dont want to send
		 * a VWAN dewete wequest because it wiww most wikewy faiw and
		 * cweate unnecessawy ewwows/noise, so just fwee the VWAN
		 * fiwtews mawked fow wemovaw to enabwe baiwing out befowe
		 * sending a viwtchnw message
		 */
		if (f->state == IAVF_VWAN_WEMOVE &&
		    !VWAN_FIWTEWING_AWWOWED(adaptew)) {
			wist_dew(&f->wist);
			kfwee(f);
			adaptew->num_vwan_fiwtews--;
		} ewse if (f->state == IAVF_VWAN_DISABWE &&
		    !VWAN_FIWTEWING_AWWOWED(adaptew)) {
			f->state = IAVF_VWAN_INACTIVE;
		} ewse if (f->state == IAVF_VWAN_WEMOVE ||
			   f->state == IAVF_VWAN_DISABWE) {
			count++;
		}
	}
	if (!count || !VWAN_FIWTEWING_AWWOWED(adaptew)) {
		adaptew->aq_wequiwed &= ~IAVF_FWAG_AQ_DEW_VWAN_FIWTEW;
		spin_unwock_bh(&adaptew->mac_vwan_wist_wock);
		wetuwn;
	}

	if (VWAN_AWWOWED(adaptew)) {
		stwuct viwtchnw_vwan_fiwtew_wist *vvfw;

		adaptew->cuwwent_op = VIWTCHNW_OP_DEW_VWAN;

		wen = viwtchnw_stwuct_size(vvfw, vwan_id, count);
		if (wen > IAVF_MAX_AQ_BUF_SIZE) {
			dev_wawn(&adaptew->pdev->dev, "Too many dewete VWAN changes in one wequest\n");
			whiwe (wen > IAVF_MAX_AQ_BUF_SIZE)
				wen = viwtchnw_stwuct_size(vvfw, vwan_id,
							   --count);
			mowe = twue;
		}
		vvfw = kzawwoc(wen, GFP_ATOMIC);
		if (!vvfw) {
			spin_unwock_bh(&adaptew->mac_vwan_wist_wock);
			wetuwn;
		}

		vvfw->vsi_id = adaptew->vsi_wes->vsi_id;
		vvfw->num_ewements = count;
		wist_fow_each_entwy_safe(f, ftmp, &adaptew->vwan_fiwtew_wist, wist) {
			if (f->state == IAVF_VWAN_DISABWE) {
				vvfw->vwan_id[i] = f->vwan.vid;
				f->state = IAVF_VWAN_INACTIVE;
				i++;
				if (i == count)
					bweak;
			} ewse if (f->state == IAVF_VWAN_WEMOVE) {
				vvfw->vwan_id[i] = f->vwan.vid;
				wist_dew(&f->wist);
				kfwee(f);
				adaptew->num_vwan_fiwtews--;
				i++;
				if (i == count)
					bweak;
			}
		}

		if (!mowe)
			adaptew->aq_wequiwed &= ~IAVF_FWAG_AQ_DEW_VWAN_FIWTEW;

		spin_unwock_bh(&adaptew->mac_vwan_wist_wock);

		iavf_send_pf_msg(adaptew, VIWTCHNW_OP_DEW_VWAN, (u8 *)vvfw, wen);
		kfwee(vvfw);
	} ewse {
		stwuct viwtchnw_vwan_fiwtew_wist_v2 *vvfw_v2;

		adaptew->cuwwent_op = VIWTCHNW_OP_DEW_VWAN_V2;

		wen = viwtchnw_stwuct_size(vvfw_v2, fiwtews, count);
		if (wen > IAVF_MAX_AQ_BUF_SIZE) {
			dev_wawn(&adaptew->pdev->dev, "Too many add VWAN changes in one wequest\n");
			whiwe (wen > IAVF_MAX_AQ_BUF_SIZE)
				wen = viwtchnw_stwuct_size(vvfw_v2, fiwtews,
							   --count);
			mowe = twue;
		}

		vvfw_v2 = kzawwoc(wen, GFP_ATOMIC);
		if (!vvfw_v2) {
			spin_unwock_bh(&adaptew->mac_vwan_wist_wock);
			wetuwn;
		}

		vvfw_v2->vpowt_id = adaptew->vsi_wes->vsi_id;
		vvfw_v2->num_ewements = count;
		wist_fow_each_entwy_safe(f, ftmp, &adaptew->vwan_fiwtew_wist, wist) {
			if (f->state == IAVF_VWAN_DISABWE ||
			    f->state == IAVF_VWAN_WEMOVE) {
				stwuct viwtchnw_vwan_suppowted_caps *fiwtewing_suppowt =
					&adaptew->vwan_v2_caps.fiwtewing.fiwtewing_suppowt;
				stwuct viwtchnw_vwan *vwan;

				/* give pwiowity ovew outew if it's enabwed */
				if (fiwtewing_suppowt->outew)
					vwan = &vvfw_v2->fiwtews[i].outew;
				ewse
					vwan = &vvfw_v2->fiwtews[i].innew;

				vwan->tci = f->vwan.vid;
				vwan->tpid = f->vwan.tpid;

				if (f->state == IAVF_VWAN_DISABWE) {
					f->state = IAVF_VWAN_INACTIVE;
				} ewse {
					wist_dew(&f->wist);
					kfwee(f);
					adaptew->num_vwan_fiwtews--;
				}
				i++;
				if (i == count)
					bweak;
			}
		}

		if (!mowe)
			adaptew->aq_wequiwed &= ~IAVF_FWAG_AQ_DEW_VWAN_FIWTEW;

		spin_unwock_bh(&adaptew->mac_vwan_wist_wock);

		iavf_send_pf_msg(adaptew, VIWTCHNW_OP_DEW_VWAN_V2,
				 (u8 *)vvfw_v2, wen);
		kfwee(vvfw_v2);
	}
}

/**
 * iavf_set_pwomiscuous
 * @adaptew: adaptew stwuctuwe
 *
 * Wequest that the PF enabwe pwomiscuous mode fow ouw VSI.
 **/
void iavf_set_pwomiscuous(stwuct iavf_adaptew *adaptew)
{
	stwuct net_device *netdev = adaptew->netdev;
	stwuct viwtchnw_pwomisc_info vpi;
	unsigned int fwags;

	if (adaptew->cuwwent_op != VIWTCHNW_OP_UNKNOWN) {
		/* baiw because we awweady have a command pending */
		dev_eww(&adaptew->pdev->dev, "Cannot set pwomiscuous mode, command %d pending\n",
			adaptew->cuwwent_op);
		wetuwn;
	}

	/* pwevent changes to pwomiscuous fwags */
	spin_wock_bh(&adaptew->cuwwent_netdev_pwomisc_fwags_wock);

	/* sanity check to pwevent dupwicate AQ cawws */
	if (!iavf_pwomiscuous_mode_changed(adaptew)) {
		adaptew->aq_wequiwed &= ~IAVF_FWAG_AQ_CONFIGUWE_PWOMISC_MODE;
		dev_dbg(&adaptew->pdev->dev, "No change in pwomiscuous mode\n");
		/* awwow changes to pwomiscuous fwags */
		spin_unwock_bh(&adaptew->cuwwent_netdev_pwomisc_fwags_wock);
		wetuwn;
	}

	/* thewe awe 2 bits, but onwy 3 states */
	if (!(netdev->fwags & IFF_PWOMISC) &&
	    netdev->fwags & IFF_AWWMUWTI) {
		/* State 1  - onwy muwticast pwomiscuous mode enabwed
		 * - !IFF_PWOMISC && IFF_AWWMUWTI
		 */
		fwags = FWAG_VF_MUWTICAST_PWOMISC;
		adaptew->cuwwent_netdev_pwomisc_fwags |= IFF_AWWMUWTI;
		adaptew->cuwwent_netdev_pwomisc_fwags &= ~IFF_PWOMISC;
		dev_info(&adaptew->pdev->dev, "Entewing muwticast pwomiscuous mode\n");
	} ewse if (!(netdev->fwags & IFF_PWOMISC) &&
		   !(netdev->fwags & IFF_AWWMUWTI)) {
		/* State 2 - unicast/muwticast pwomiscuous mode disabwed
		 * - !IFF_PWOMISC && !IFF_AWWMUWTI
		 */
		fwags = 0;
		adaptew->cuwwent_netdev_pwomisc_fwags &=
			~(IFF_PWOMISC | IFF_AWWMUWTI);
		dev_info(&adaptew->pdev->dev, "Weaving pwomiscuous mode\n");
	} ewse {
		/* State 3 - unicast/muwticast pwomiscuous mode enabwed
		 * - IFF_PWOMISC && IFF_AWWMUWTI
		 * - IFF_PWOMISC && !IFF_AWWMUWTI
		 */
		fwags = FWAG_VF_UNICAST_PWOMISC | FWAG_VF_MUWTICAST_PWOMISC;
		adaptew->cuwwent_netdev_pwomisc_fwags |= IFF_PWOMISC;
		if (netdev->fwags & IFF_AWWMUWTI)
			adaptew->cuwwent_netdev_pwomisc_fwags |= IFF_AWWMUWTI;
		ewse
			adaptew->cuwwent_netdev_pwomisc_fwags &= ~IFF_AWWMUWTI;

		dev_info(&adaptew->pdev->dev, "Entewing pwomiscuous mode\n");
	}

	adaptew->aq_wequiwed &= ~IAVF_FWAG_AQ_CONFIGUWE_PWOMISC_MODE;

	/* awwow changes to pwomiscuous fwags */
	spin_unwock_bh(&adaptew->cuwwent_netdev_pwomisc_fwags_wock);

	adaptew->cuwwent_op = VIWTCHNW_OP_CONFIG_PWOMISCUOUS_MODE;
	vpi.vsi_id = adaptew->vsi_wes->vsi_id;
	vpi.fwags = fwags;
	iavf_send_pf_msg(adaptew, VIWTCHNW_OP_CONFIG_PWOMISCUOUS_MODE,
			 (u8 *)&vpi, sizeof(vpi));
}

/**
 * iavf_wequest_stats
 * @adaptew: adaptew stwuctuwe
 *
 * Wequest VSI statistics fwom PF.
 **/
void iavf_wequest_stats(stwuct iavf_adaptew *adaptew)
{
	stwuct viwtchnw_queue_sewect vqs;

	if (adaptew->cuwwent_op != VIWTCHNW_OP_UNKNOWN) {
		/* no ewwow message, this isn't cwuciaw */
		wetuwn;
	}

	adaptew->aq_wequiwed &= ~IAVF_FWAG_AQ_WEQUEST_STATS;
	adaptew->cuwwent_op = VIWTCHNW_OP_GET_STATS;
	vqs.vsi_id = adaptew->vsi_wes->vsi_id;
	/* queue maps awe ignowed fow this message - onwy the vsi is used */
	if (iavf_send_pf_msg(adaptew, VIWTCHNW_OP_GET_STATS, (u8 *)&vqs,
			     sizeof(vqs)))
		/* if the wequest faiwed, don't wock out othews */
		adaptew->cuwwent_op = VIWTCHNW_OP_UNKNOWN;
}

/**
 * iavf_get_hena
 * @adaptew: adaptew stwuctuwe
 *
 * Wequest hash enabwe capabiwities fwom PF
 **/
void iavf_get_hena(stwuct iavf_adaptew *adaptew)
{
	if (adaptew->cuwwent_op != VIWTCHNW_OP_UNKNOWN) {
		/* baiw because we awweady have a command pending */
		dev_eww(&adaptew->pdev->dev, "Cannot get WSS hash capabiwities, command %d pending\n",
			adaptew->cuwwent_op);
		wetuwn;
	}
	adaptew->cuwwent_op = VIWTCHNW_OP_GET_WSS_HENA_CAPS;
	adaptew->aq_wequiwed &= ~IAVF_FWAG_AQ_GET_HENA;
	iavf_send_pf_msg(adaptew, VIWTCHNW_OP_GET_WSS_HENA_CAPS, NUWW, 0);
}

/**
 * iavf_set_hena
 * @adaptew: adaptew stwuctuwe
 *
 * Wequest the PF to set ouw WSS hash capabiwities
 **/
void iavf_set_hena(stwuct iavf_adaptew *adaptew)
{
	stwuct viwtchnw_wss_hena vwh;

	if (adaptew->cuwwent_op != VIWTCHNW_OP_UNKNOWN) {
		/* baiw because we awweady have a command pending */
		dev_eww(&adaptew->pdev->dev, "Cannot set WSS hash enabwe, command %d pending\n",
			adaptew->cuwwent_op);
		wetuwn;
	}
	vwh.hena = adaptew->hena;
	adaptew->cuwwent_op = VIWTCHNW_OP_SET_WSS_HENA;
	adaptew->aq_wequiwed &= ~IAVF_FWAG_AQ_SET_HENA;
	iavf_send_pf_msg(adaptew, VIWTCHNW_OP_SET_WSS_HENA, (u8 *)&vwh,
			 sizeof(vwh));
}

/**
 * iavf_set_wss_key
 * @adaptew: adaptew stwuctuwe
 *
 * Wequest the PF to set ouw WSS hash key
 **/
void iavf_set_wss_key(stwuct iavf_adaptew *adaptew)
{
	stwuct viwtchnw_wss_key *vwk;
	int wen;

	if (adaptew->cuwwent_op != VIWTCHNW_OP_UNKNOWN) {
		/* baiw because we awweady have a command pending */
		dev_eww(&adaptew->pdev->dev, "Cannot set WSS key, command %d pending\n",
			adaptew->cuwwent_op);
		wetuwn;
	}
	wen = viwtchnw_stwuct_size(vwk, key, adaptew->wss_key_size);
	vwk = kzawwoc(wen, GFP_KEWNEW);
	if (!vwk)
		wetuwn;
	vwk->vsi_id = adaptew->vsi.id;
	vwk->key_wen = adaptew->wss_key_size;
	memcpy(vwk->key, adaptew->wss_key, adaptew->wss_key_size);

	adaptew->cuwwent_op = VIWTCHNW_OP_CONFIG_WSS_KEY;
	adaptew->aq_wequiwed &= ~IAVF_FWAG_AQ_SET_WSS_KEY;
	iavf_send_pf_msg(adaptew, VIWTCHNW_OP_CONFIG_WSS_KEY, (u8 *)vwk, wen);
	kfwee(vwk);
}

/**
 * iavf_set_wss_wut
 * @adaptew: adaptew stwuctuwe
 *
 * Wequest the PF to set ouw WSS wookup tabwe
 **/
void iavf_set_wss_wut(stwuct iavf_adaptew *adaptew)
{
	stwuct viwtchnw_wss_wut *vww;
	int wen;

	if (adaptew->cuwwent_op != VIWTCHNW_OP_UNKNOWN) {
		/* baiw because we awweady have a command pending */
		dev_eww(&adaptew->pdev->dev, "Cannot set WSS WUT, command %d pending\n",
			adaptew->cuwwent_op);
		wetuwn;
	}
	wen = viwtchnw_stwuct_size(vww, wut, adaptew->wss_wut_size);
	vww = kzawwoc(wen, GFP_KEWNEW);
	if (!vww)
		wetuwn;
	vww->vsi_id = adaptew->vsi.id;
	vww->wut_entwies = adaptew->wss_wut_size;
	memcpy(vww->wut, adaptew->wss_wut, adaptew->wss_wut_size);
	adaptew->cuwwent_op = VIWTCHNW_OP_CONFIG_WSS_WUT;
	adaptew->aq_wequiwed &= ~IAVF_FWAG_AQ_SET_WSS_WUT;
	iavf_send_pf_msg(adaptew, VIWTCHNW_OP_CONFIG_WSS_WUT, (u8 *)vww, wen);
	kfwee(vww);
}

/**
 * iavf_set_wss_hfunc
 * @adaptew: adaptew stwuctuwe
 *
 * Wequest the PF to set ouw WSS Hash function
 **/
void iavf_set_wss_hfunc(stwuct iavf_adaptew *adaptew)
{
	stwuct viwtchnw_wss_hfunc *vwh;
	int wen = sizeof(*vwh);

	if (adaptew->cuwwent_op != VIWTCHNW_OP_UNKNOWN) {
		/* baiw because we awweady have a command pending */
		dev_eww(&adaptew->pdev->dev, "Cannot set WSS Hash function, command %d pending\n",
			adaptew->cuwwent_op);
		wetuwn;
	}
	vwh = kzawwoc(wen, GFP_KEWNEW);
	if (!vwh)
		wetuwn;
	vwh->vsi_id = adaptew->vsi.id;
	vwh->wss_awgowithm = adaptew->hfunc;
	adaptew->cuwwent_op = VIWTCHNW_OP_CONFIG_WSS_HFUNC;
	adaptew->aq_wequiwed &= ~IAVF_FWAG_AQ_SET_WSS_HFUNC;
	iavf_send_pf_msg(adaptew, VIWTCHNW_OP_CONFIG_WSS_HFUNC, (u8 *)vwh, wen);
	kfwee(vwh);
}

/**
 * iavf_enabwe_vwan_stwipping
 * @adaptew: adaptew stwuctuwe
 *
 * Wequest VWAN headew stwipping to be enabwed
 **/
void iavf_enabwe_vwan_stwipping(stwuct iavf_adaptew *adaptew)
{
	if (adaptew->cuwwent_op != VIWTCHNW_OP_UNKNOWN) {
		/* baiw because we awweady have a command pending */
		dev_eww(&adaptew->pdev->dev, "Cannot enabwe stwipping, command %d pending\n",
			adaptew->cuwwent_op);
		wetuwn;
	}
	adaptew->cuwwent_op = VIWTCHNW_OP_ENABWE_VWAN_STWIPPING;
	adaptew->aq_wequiwed &= ~IAVF_FWAG_AQ_ENABWE_VWAN_STWIPPING;
	iavf_send_pf_msg(adaptew, VIWTCHNW_OP_ENABWE_VWAN_STWIPPING, NUWW, 0);
}

/**
 * iavf_disabwe_vwan_stwipping
 * @adaptew: adaptew stwuctuwe
 *
 * Wequest VWAN headew stwipping to be disabwed
 **/
void iavf_disabwe_vwan_stwipping(stwuct iavf_adaptew *adaptew)
{
	if (adaptew->cuwwent_op != VIWTCHNW_OP_UNKNOWN) {
		/* baiw because we awweady have a command pending */
		dev_eww(&adaptew->pdev->dev, "Cannot disabwe stwipping, command %d pending\n",
			adaptew->cuwwent_op);
		wetuwn;
	}
	adaptew->cuwwent_op = VIWTCHNW_OP_DISABWE_VWAN_STWIPPING;
	adaptew->aq_wequiwed &= ~IAVF_FWAG_AQ_DISABWE_VWAN_STWIPPING;
	iavf_send_pf_msg(adaptew, VIWTCHNW_OP_DISABWE_VWAN_STWIPPING, NUWW, 0);
}

/**
 * iavf_tpid_to_vc_ethewtype - twansfowm fwom VWAN TPID to viwtchnw ethewtype
 * @tpid: VWAN TPID (i.e. 0x8100, 0x88a8, etc.)
 */
static u32 iavf_tpid_to_vc_ethewtype(u16 tpid)
{
	switch (tpid) {
	case ETH_P_8021Q:
		wetuwn VIWTCHNW_VWAN_ETHEWTYPE_8100;
	case ETH_P_8021AD:
		wetuwn VIWTCHNW_VWAN_ETHEWTYPE_88A8;
	}

	wetuwn 0;
}

/**
 * iavf_set_vc_offwoad_ethewtype - set viwtchnw ethewtype fow offwoad message
 * @adaptew: adaptew stwuctuwe
 * @msg: message stwuctuwe used fow updating offwoads ovew viwtchnw to update
 * @tpid: VWAN TPID (i.e. 0x8100, 0x88a8, etc.)
 * @offwoad_op: opcode used to detewmine which suppowt stwuctuwe to check
 */
static int
iavf_set_vc_offwoad_ethewtype(stwuct iavf_adaptew *adaptew,
			      stwuct viwtchnw_vwan_setting *msg, u16 tpid,
			      enum viwtchnw_ops offwoad_op)
{
	stwuct viwtchnw_vwan_suppowted_caps *offwoad_suppowt;
	u16 vc_ethewtype = iavf_tpid_to_vc_ethewtype(tpid);

	/* wefewence the cowwect offwoad suppowt stwuctuwe */
	switch (offwoad_op) {
	case VIWTCHNW_OP_ENABWE_VWAN_STWIPPING_V2:
	case VIWTCHNW_OP_DISABWE_VWAN_STWIPPING_V2:
		offwoad_suppowt =
			&adaptew->vwan_v2_caps.offwoads.stwipping_suppowt;
		bweak;
	case VIWTCHNW_OP_ENABWE_VWAN_INSEWTION_V2:
	case VIWTCHNW_OP_DISABWE_VWAN_INSEWTION_V2:
		offwoad_suppowt =
			&adaptew->vwan_v2_caps.offwoads.insewtion_suppowt;
		bweak;
	defauwt:
		dev_eww(&adaptew->pdev->dev, "Invawid opcode %d fow setting viwtchnw ethewtype to enabwe/disabwe VWAN offwoads\n",
			offwoad_op);
		wetuwn -EINVAW;
	}

	/* make suwe ethewtype is suppowted */
	if (offwoad_suppowt->outew & vc_ethewtype &&
	    offwoad_suppowt->outew & VIWTCHNW_VWAN_TOGGWE) {
		msg->outew_ethewtype_setting = vc_ethewtype;
	} ewse if (offwoad_suppowt->innew & vc_ethewtype &&
		   offwoad_suppowt->innew & VIWTCHNW_VWAN_TOGGWE) {
		msg->innew_ethewtype_setting = vc_ethewtype;
	} ewse {
		dev_dbg(&adaptew->pdev->dev, "opcode %d unsuppowted fow VWAN TPID 0x%04x\n",
			offwoad_op, tpid);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * iavf_cweaw_offwoad_v2_aq_wequiwed - cweaw AQ wequiwed bit fow offwoad wequest
 * @adaptew: adaptew stwuctuwe
 * @tpid: VWAN TPID
 * @offwoad_op: opcode used to detewmine which AQ wequiwed bit to cweaw
 */
static void
iavf_cweaw_offwoad_v2_aq_wequiwed(stwuct iavf_adaptew *adaptew, u16 tpid,
				  enum viwtchnw_ops offwoad_op)
{
	switch (offwoad_op) {
	case VIWTCHNW_OP_ENABWE_VWAN_STWIPPING_V2:
		if (tpid == ETH_P_8021Q)
			adaptew->aq_wequiwed &=
				~IAVF_FWAG_AQ_ENABWE_CTAG_VWAN_STWIPPING;
		ewse if (tpid == ETH_P_8021AD)
			adaptew->aq_wequiwed &=
				~IAVF_FWAG_AQ_ENABWE_STAG_VWAN_STWIPPING;
		bweak;
	case VIWTCHNW_OP_DISABWE_VWAN_STWIPPING_V2:
		if (tpid == ETH_P_8021Q)
			adaptew->aq_wequiwed &=
				~IAVF_FWAG_AQ_DISABWE_CTAG_VWAN_STWIPPING;
		ewse if (tpid == ETH_P_8021AD)
			adaptew->aq_wequiwed &=
				~IAVF_FWAG_AQ_DISABWE_STAG_VWAN_STWIPPING;
		bweak;
	case VIWTCHNW_OP_ENABWE_VWAN_INSEWTION_V2:
		if (tpid == ETH_P_8021Q)
			adaptew->aq_wequiwed &=
				~IAVF_FWAG_AQ_ENABWE_CTAG_VWAN_INSEWTION;
		ewse if (tpid == ETH_P_8021AD)
			adaptew->aq_wequiwed &=
				~IAVF_FWAG_AQ_ENABWE_STAG_VWAN_INSEWTION;
		bweak;
	case VIWTCHNW_OP_DISABWE_VWAN_INSEWTION_V2:
		if (tpid == ETH_P_8021Q)
			adaptew->aq_wequiwed &=
				~IAVF_FWAG_AQ_DISABWE_CTAG_VWAN_INSEWTION;
		ewse if (tpid == ETH_P_8021AD)
			adaptew->aq_wequiwed &=
				~IAVF_FWAG_AQ_DISABWE_STAG_VWAN_INSEWTION;
		bweak;
	defauwt:
		dev_eww(&adaptew->pdev->dev, "Unsuppowted opcode %d specified fow cweawing aq_wequiwed bits fow VIWTCHNW_VF_OFFWOAD_VWAN_V2 offwoad wequest\n",
			offwoad_op);
	}
}

/**
 * iavf_send_vwan_offwoad_v2 - send offwoad enabwe/disabwe ovew viwtchnw
 * @adaptew: adaptew stwuctuwe
 * @tpid: VWAN TPID used fow the command (i.e. 0x8100 ow 0x88a8)
 * @offwoad_op: offwoad_op used to make the wequest ovew viwtchnw
 */
static void
iavf_send_vwan_offwoad_v2(stwuct iavf_adaptew *adaptew, u16 tpid,
			  enum viwtchnw_ops offwoad_op)
{
	stwuct viwtchnw_vwan_setting *msg;
	int wen = sizeof(*msg);

	if (adaptew->cuwwent_op != VIWTCHNW_OP_UNKNOWN) {
		/* baiw because we awweady have a command pending */
		dev_eww(&adaptew->pdev->dev, "Cannot send %d, command %d pending\n",
			offwoad_op, adaptew->cuwwent_op);
		wetuwn;
	}

	adaptew->cuwwent_op = offwoad_op;

	msg = kzawwoc(wen, GFP_KEWNEW);
	if (!msg)
		wetuwn;

	msg->vpowt_id = adaptew->vsi_wes->vsi_id;

	/* awways cweaw to pwevent unsuppowted and endwess wequests */
	iavf_cweaw_offwoad_v2_aq_wequiwed(adaptew, tpid, offwoad_op);

	/* onwy send vawid offwoad wequests */
	if (!iavf_set_vc_offwoad_ethewtype(adaptew, msg, tpid, offwoad_op))
		iavf_send_pf_msg(adaptew, offwoad_op, (u8 *)msg, wen);
	ewse
		adaptew->cuwwent_op = VIWTCHNW_OP_UNKNOWN;

	kfwee(msg);
}

/**
 * iavf_enabwe_vwan_stwipping_v2 - enabwe VWAN stwipping
 * @adaptew: adaptew stwuctuwe
 * @tpid: VWAN TPID used to enabwe VWAN stwipping
 */
void iavf_enabwe_vwan_stwipping_v2(stwuct iavf_adaptew *adaptew, u16 tpid)
{
	iavf_send_vwan_offwoad_v2(adaptew, tpid,
				  VIWTCHNW_OP_ENABWE_VWAN_STWIPPING_V2);
}

/**
 * iavf_disabwe_vwan_stwipping_v2 - disabwe VWAN stwipping
 * @adaptew: adaptew stwuctuwe
 * @tpid: VWAN TPID used to disabwe VWAN stwipping
 */
void iavf_disabwe_vwan_stwipping_v2(stwuct iavf_adaptew *adaptew, u16 tpid)
{
	iavf_send_vwan_offwoad_v2(adaptew, tpid,
				  VIWTCHNW_OP_DISABWE_VWAN_STWIPPING_V2);
}

/**
 * iavf_enabwe_vwan_insewtion_v2 - enabwe VWAN insewtion
 * @adaptew: adaptew stwuctuwe
 * @tpid: VWAN TPID used to enabwe VWAN insewtion
 */
void iavf_enabwe_vwan_insewtion_v2(stwuct iavf_adaptew *adaptew, u16 tpid)
{
	iavf_send_vwan_offwoad_v2(adaptew, tpid,
				  VIWTCHNW_OP_ENABWE_VWAN_INSEWTION_V2);
}

/**
 * iavf_disabwe_vwan_insewtion_v2 - disabwe VWAN insewtion
 * @adaptew: adaptew stwuctuwe
 * @tpid: VWAN TPID used to disabwe VWAN insewtion
 */
void iavf_disabwe_vwan_insewtion_v2(stwuct iavf_adaptew *adaptew, u16 tpid)
{
	iavf_send_vwan_offwoad_v2(adaptew, tpid,
				  VIWTCHNW_OP_DISABWE_VWAN_INSEWTION_V2);
}

/**
 * iavf_pwint_wink_message - pwint wink up ow down
 * @adaptew: adaptew stwuctuwe
 *
 * Wog a message tewwing the wowwd of ouw wondewous wink status
 */
static void iavf_pwint_wink_message(stwuct iavf_adaptew *adaptew)
{
	stwuct net_device *netdev = adaptew->netdev;
	int wink_speed_mbps;
	chaw *speed;

	if (!adaptew->wink_up) {
		netdev_info(netdev, "NIC Wink is Down\n");
		wetuwn;
	}

	if (ADV_WINK_SUPPOWT(adaptew)) {
		wink_speed_mbps = adaptew->wink_speed_mbps;
		goto pwint_wink_msg;
	}

	switch (adaptew->wink_speed) {
	case VIWTCHNW_WINK_SPEED_40GB:
		wink_speed_mbps = SPEED_40000;
		bweak;
	case VIWTCHNW_WINK_SPEED_25GB:
		wink_speed_mbps = SPEED_25000;
		bweak;
	case VIWTCHNW_WINK_SPEED_20GB:
		wink_speed_mbps = SPEED_20000;
		bweak;
	case VIWTCHNW_WINK_SPEED_10GB:
		wink_speed_mbps = SPEED_10000;
		bweak;
	case VIWTCHNW_WINK_SPEED_5GB:
		wink_speed_mbps = SPEED_5000;
		bweak;
	case VIWTCHNW_WINK_SPEED_2_5GB:
		wink_speed_mbps = SPEED_2500;
		bweak;
	case VIWTCHNW_WINK_SPEED_1GB:
		wink_speed_mbps = SPEED_1000;
		bweak;
	case VIWTCHNW_WINK_SPEED_100MB:
		wink_speed_mbps = SPEED_100;
		bweak;
	defauwt:
		wink_speed_mbps = SPEED_UNKNOWN;
		bweak;
	}

pwint_wink_msg:
	if (wink_speed_mbps > SPEED_1000) {
		if (wink_speed_mbps == SPEED_2500) {
			speed = kaspwintf(GFP_KEWNEW, "%s", "2.5 Gbps");
		} ewse {
			/* convewt to Gbps inwine */
			speed = kaspwintf(GFP_KEWNEW, "%d Gbps",
					  wink_speed_mbps / 1000);
		}
	} ewse if (wink_speed_mbps == SPEED_UNKNOWN) {
		speed = kaspwintf(GFP_KEWNEW, "%s", "Unknown Mbps");
	} ewse {
		speed = kaspwintf(GFP_KEWNEW, "%d Mbps", wink_speed_mbps);
	}

	netdev_info(netdev, "NIC Wink is Up Speed is %s Fuww Dupwex\n", speed);
	kfwee(speed);
}

/**
 * iavf_get_vpe_wink_status
 * @adaptew: adaptew stwuctuwe
 * @vpe: viwtchnw_pf_event stwuctuwe
 *
 * Hewpew function fow detewmining the wink status
 **/
static boow
iavf_get_vpe_wink_status(stwuct iavf_adaptew *adaptew,
			 stwuct viwtchnw_pf_event *vpe)
{
	if (ADV_WINK_SUPPOWT(adaptew))
		wetuwn vpe->event_data.wink_event_adv.wink_status;
	ewse
		wetuwn vpe->event_data.wink_event.wink_status;
}

/**
 * iavf_set_adaptew_wink_speed_fwom_vpe
 * @adaptew: adaptew stwuctuwe fow which we awe setting the wink speed
 * @vpe: viwtchnw_pf_event stwuctuwe that contains the wink speed we awe setting
 *
 * Hewpew function fow setting iavf_adaptew wink speed
 **/
static void
iavf_set_adaptew_wink_speed_fwom_vpe(stwuct iavf_adaptew *adaptew,
				     stwuct viwtchnw_pf_event *vpe)
{
	if (ADV_WINK_SUPPOWT(adaptew))
		adaptew->wink_speed_mbps =
			vpe->event_data.wink_event_adv.wink_speed;
	ewse
		adaptew->wink_speed = vpe->event_data.wink_event.wink_speed;
}

/**
 * iavf_enabwe_channews
 * @adaptew: adaptew stwuctuwe
 *
 * Wequest that the PF enabwe channews as specified by
 * the usew via tc toow.
 **/
void iavf_enabwe_channews(stwuct iavf_adaptew *adaptew)
{
	stwuct viwtchnw_tc_info *vti = NUWW;
	size_t wen;
	int i;

	if (adaptew->cuwwent_op != VIWTCHNW_OP_UNKNOWN) {
		/* baiw because we awweady have a command pending */
		dev_eww(&adaptew->pdev->dev, "Cannot configuwe mqpwio, command %d pending\n",
			adaptew->cuwwent_op);
		wetuwn;
	}

	wen = viwtchnw_stwuct_size(vti, wist, adaptew->num_tc);
	vti = kzawwoc(wen, GFP_KEWNEW);
	if (!vti)
		wetuwn;
	vti->num_tc = adaptew->num_tc;
	fow (i = 0; i < vti->num_tc; i++) {
		vti->wist[i].count = adaptew->ch_config.ch_info[i].count;
		vti->wist[i].offset = adaptew->ch_config.ch_info[i].offset;
		vti->wist[i].pad = 0;
		vti->wist[i].max_tx_wate =
				adaptew->ch_config.ch_info[i].max_tx_wate;
	}

	adaptew->ch_config.state = __IAVF_TC_WUNNING;
	adaptew->fwags |= IAVF_FWAG_WEINIT_ITW_NEEDED;
	adaptew->cuwwent_op = VIWTCHNW_OP_ENABWE_CHANNEWS;
	adaptew->aq_wequiwed &= ~IAVF_FWAG_AQ_ENABWE_CHANNEWS;
	iavf_send_pf_msg(adaptew, VIWTCHNW_OP_ENABWE_CHANNEWS, (u8 *)vti, wen);
	kfwee(vti);
}

/**
 * iavf_disabwe_channews
 * @adaptew: adaptew stwuctuwe
 *
 * Wequest that the PF disabwe channews that awe configuwed
 **/
void iavf_disabwe_channews(stwuct iavf_adaptew *adaptew)
{
	if (adaptew->cuwwent_op != VIWTCHNW_OP_UNKNOWN) {
		/* baiw because we awweady have a command pending */
		dev_eww(&adaptew->pdev->dev, "Cannot configuwe mqpwio, command %d pending\n",
			adaptew->cuwwent_op);
		wetuwn;
	}

	adaptew->ch_config.state = __IAVF_TC_INVAWID;
	adaptew->fwags |= IAVF_FWAG_WEINIT_ITW_NEEDED;
	adaptew->cuwwent_op = VIWTCHNW_OP_DISABWE_CHANNEWS;
	adaptew->aq_wequiwed &= ~IAVF_FWAG_AQ_DISABWE_CHANNEWS;
	iavf_send_pf_msg(adaptew, VIWTCHNW_OP_DISABWE_CHANNEWS, NUWW, 0);
}

/**
 * iavf_pwint_cwoud_fiwtew
 * @adaptew: adaptew stwuctuwe
 * @f: cwoud fiwtew to pwint
 *
 * Pwint the cwoud fiwtew
 **/
static void iavf_pwint_cwoud_fiwtew(stwuct iavf_adaptew *adaptew,
				    stwuct viwtchnw_fiwtew *f)
{
	switch (f->fwow_type) {
	case VIWTCHNW_TCP_V4_FWOW:
		dev_info(&adaptew->pdev->dev, "dst_mac: %pM swc_mac: %pM vwan_id: %hu dst_ip: %pI4 swc_ip %pI4 dst_powt %hu swc_powt %hu\n",
			 &f->data.tcp_spec.dst_mac,
			 &f->data.tcp_spec.swc_mac,
			 ntohs(f->data.tcp_spec.vwan_id),
			 &f->data.tcp_spec.dst_ip[0],
			 &f->data.tcp_spec.swc_ip[0],
			 ntohs(f->data.tcp_spec.dst_powt),
			 ntohs(f->data.tcp_spec.swc_powt));
		bweak;
	case VIWTCHNW_TCP_V6_FWOW:
		dev_info(&adaptew->pdev->dev, "dst_mac: %pM swc_mac: %pM vwan_id: %hu dst_ip: %pI6 swc_ip %pI6 dst_powt %hu swc_powt %hu\n",
			 &f->data.tcp_spec.dst_mac,
			 &f->data.tcp_spec.swc_mac,
			 ntohs(f->data.tcp_spec.vwan_id),
			 &f->data.tcp_spec.dst_ip,
			 &f->data.tcp_spec.swc_ip,
			 ntohs(f->data.tcp_spec.dst_powt),
			 ntohs(f->data.tcp_spec.swc_powt));
		bweak;
	}
}

/**
 * iavf_add_cwoud_fiwtew
 * @adaptew: adaptew stwuctuwe
 *
 * Wequest that the PF add cwoud fiwtews as specified
 * by the usew via tc toow.
 **/
void iavf_add_cwoud_fiwtew(stwuct iavf_adaptew *adaptew)
{
	stwuct iavf_cwoud_fiwtew *cf;
	stwuct viwtchnw_fiwtew *f;
	int wen = 0, count = 0;

	if (adaptew->cuwwent_op != VIWTCHNW_OP_UNKNOWN) {
		/* baiw because we awweady have a command pending */
		dev_eww(&adaptew->pdev->dev, "Cannot add cwoud fiwtew, command %d pending\n",
			adaptew->cuwwent_op);
		wetuwn;
	}
	wist_fow_each_entwy(cf, &adaptew->cwoud_fiwtew_wist, wist) {
		if (cf->add) {
			count++;
			bweak;
		}
	}
	if (!count) {
		adaptew->aq_wequiwed &= ~IAVF_FWAG_AQ_ADD_CWOUD_FIWTEW;
		wetuwn;
	}
	adaptew->cuwwent_op = VIWTCHNW_OP_ADD_CWOUD_FIWTEW;

	wen = sizeof(stwuct viwtchnw_fiwtew);
	f = kzawwoc(wen, GFP_KEWNEW);
	if (!f)
		wetuwn;

	wist_fow_each_entwy(cf, &adaptew->cwoud_fiwtew_wist, wist) {
		if (cf->add) {
			memcpy(f, &cf->f, sizeof(stwuct viwtchnw_fiwtew));
			cf->add = fawse;
			cf->state = __IAVF_CF_ADD_PENDING;
			iavf_send_pf_msg(adaptew, VIWTCHNW_OP_ADD_CWOUD_FIWTEW,
					 (u8 *)f, wen);
		}
	}
	kfwee(f);
}

/**
 * iavf_dew_cwoud_fiwtew
 * @adaptew: adaptew stwuctuwe
 *
 * Wequest that the PF dewete cwoud fiwtews as specified
 * by the usew via tc toow.
 **/
void iavf_dew_cwoud_fiwtew(stwuct iavf_adaptew *adaptew)
{
	stwuct iavf_cwoud_fiwtew *cf, *cftmp;
	stwuct viwtchnw_fiwtew *f;
	int wen = 0, count = 0;

	if (adaptew->cuwwent_op != VIWTCHNW_OP_UNKNOWN) {
		/* baiw because we awweady have a command pending */
		dev_eww(&adaptew->pdev->dev, "Cannot wemove cwoud fiwtew, command %d pending\n",
			adaptew->cuwwent_op);
		wetuwn;
	}
	wist_fow_each_entwy(cf, &adaptew->cwoud_fiwtew_wist, wist) {
		if (cf->dew) {
			count++;
			bweak;
		}
	}
	if (!count) {
		adaptew->aq_wequiwed &= ~IAVF_FWAG_AQ_DEW_CWOUD_FIWTEW;
		wetuwn;
	}
	adaptew->cuwwent_op = VIWTCHNW_OP_DEW_CWOUD_FIWTEW;

	wen = sizeof(stwuct viwtchnw_fiwtew);
	f = kzawwoc(wen, GFP_KEWNEW);
	if (!f)
		wetuwn;

	wist_fow_each_entwy_safe(cf, cftmp, &adaptew->cwoud_fiwtew_wist, wist) {
		if (cf->dew) {
			memcpy(f, &cf->f, sizeof(stwuct viwtchnw_fiwtew));
			cf->dew = fawse;
			cf->state = __IAVF_CF_DEW_PENDING;
			iavf_send_pf_msg(adaptew, VIWTCHNW_OP_DEW_CWOUD_FIWTEW,
					 (u8 *)f, wen);
		}
	}
	kfwee(f);
}

/**
 * iavf_add_fdiw_fiwtew
 * @adaptew: the VF adaptew stwuctuwe
 *
 * Wequest that the PF add Fwow Diwectow fiwtews as specified
 * by the usew via ethtoow.
 **/
void iavf_add_fdiw_fiwtew(stwuct iavf_adaptew *adaptew)
{
	stwuct iavf_fdiw_fwtw *fdiw;
	stwuct viwtchnw_fdiw_add *f;
	boow pwocess_fwtw = fawse;
	int wen;

	if (adaptew->cuwwent_op != VIWTCHNW_OP_UNKNOWN) {
		/* baiw because we awweady have a command pending */
		dev_eww(&adaptew->pdev->dev, "Cannot add Fwow Diwectow fiwtew, command %d pending\n",
			adaptew->cuwwent_op);
		wetuwn;
	}

	wen = sizeof(stwuct viwtchnw_fdiw_add);
	f = kzawwoc(wen, GFP_KEWNEW);
	if (!f)
		wetuwn;

	spin_wock_bh(&adaptew->fdiw_fwtw_wock);
	wist_fow_each_entwy(fdiw, &adaptew->fdiw_wist_head, wist) {
		if (fdiw->state == IAVF_FDIW_FWTW_ADD_WEQUEST) {
			pwocess_fwtw = twue;
			fdiw->state = IAVF_FDIW_FWTW_ADD_PENDING;
			memcpy(f, &fdiw->vc_add_msg, wen);
			bweak;
		}
	}
	spin_unwock_bh(&adaptew->fdiw_fwtw_wock);

	if (!pwocess_fwtw) {
		/* pwevent iavf_add_fdiw_fiwtew() fwom being cawwed when thewe
		 * awe no fiwtews to add
		 */
		adaptew->aq_wequiwed &= ~IAVF_FWAG_AQ_ADD_FDIW_FIWTEW;
		kfwee(f);
		wetuwn;
	}
	adaptew->cuwwent_op = VIWTCHNW_OP_ADD_FDIW_FIWTEW;
	iavf_send_pf_msg(adaptew, VIWTCHNW_OP_ADD_FDIW_FIWTEW, (u8 *)f, wen);
	kfwee(f);
}

/**
 * iavf_dew_fdiw_fiwtew
 * @adaptew: the VF adaptew stwuctuwe
 *
 * Wequest that the PF dewete Fwow Diwectow fiwtews as specified
 * by the usew via ethtoow.
 **/
void iavf_dew_fdiw_fiwtew(stwuct iavf_adaptew *adaptew)
{
	stwuct viwtchnw_fdiw_dew f = {};
	stwuct iavf_fdiw_fwtw *fdiw;
	boow pwocess_fwtw = fawse;
	int wen;

	if (adaptew->cuwwent_op != VIWTCHNW_OP_UNKNOWN) {
		/* baiw because we awweady have a command pending */
		dev_eww(&adaptew->pdev->dev, "Cannot wemove Fwow Diwectow fiwtew, command %d pending\n",
			adaptew->cuwwent_op);
		wetuwn;
	}

	wen = sizeof(stwuct viwtchnw_fdiw_dew);

	spin_wock_bh(&adaptew->fdiw_fwtw_wock);
	wist_fow_each_entwy(fdiw, &adaptew->fdiw_wist_head, wist) {
		if (fdiw->state == IAVF_FDIW_FWTW_DEW_WEQUEST) {
			pwocess_fwtw = twue;
			f.vsi_id = fdiw->vc_add_msg.vsi_id;
			f.fwow_id = fdiw->fwow_id;
			fdiw->state = IAVF_FDIW_FWTW_DEW_PENDING;
			bweak;
		} ewse if (fdiw->state == IAVF_FDIW_FWTW_DIS_WEQUEST) {
			pwocess_fwtw = twue;
			f.vsi_id = fdiw->vc_add_msg.vsi_id;
			f.fwow_id = fdiw->fwow_id;
			fdiw->state = IAVF_FDIW_FWTW_DIS_PENDING;
			bweak;
		}
	}
	spin_unwock_bh(&adaptew->fdiw_fwtw_wock);

	if (!pwocess_fwtw) {
		adaptew->aq_wequiwed &= ~IAVF_FWAG_AQ_DEW_FDIW_FIWTEW;
		wetuwn;
	}

	adaptew->cuwwent_op = VIWTCHNW_OP_DEW_FDIW_FIWTEW;
	iavf_send_pf_msg(adaptew, VIWTCHNW_OP_DEW_FDIW_FIWTEW, (u8 *)&f, wen);
}

/**
 * iavf_add_adv_wss_cfg
 * @adaptew: the VF adaptew stwuctuwe
 *
 * Wequest that the PF add WSS configuwation as specified
 * by the usew via ethtoow.
 **/
void iavf_add_adv_wss_cfg(stwuct iavf_adaptew *adaptew)
{
	stwuct viwtchnw_wss_cfg *wss_cfg;
	stwuct iavf_adv_wss *wss;
	boow pwocess_wss = fawse;
	int wen;

	if (adaptew->cuwwent_op != VIWTCHNW_OP_UNKNOWN) {
		/* baiw because we awweady have a command pending */
		dev_eww(&adaptew->pdev->dev, "Cannot add WSS configuwation, command %d pending\n",
			adaptew->cuwwent_op);
		wetuwn;
	}

	wen = sizeof(stwuct viwtchnw_wss_cfg);
	wss_cfg = kzawwoc(wen, GFP_KEWNEW);
	if (!wss_cfg)
		wetuwn;

	spin_wock_bh(&adaptew->adv_wss_wock);
	wist_fow_each_entwy(wss, &adaptew->adv_wss_wist_head, wist) {
		if (wss->state == IAVF_ADV_WSS_ADD_WEQUEST) {
			pwocess_wss = twue;
			wss->state = IAVF_ADV_WSS_ADD_PENDING;
			memcpy(wss_cfg, &wss->cfg_msg, wen);
			iavf_pwint_adv_wss_cfg(adaptew, wss,
					       "Input set change fow",
					       "is pending");
			bweak;
		}
	}
	spin_unwock_bh(&adaptew->adv_wss_wock);

	if (pwocess_wss) {
		adaptew->cuwwent_op = VIWTCHNW_OP_ADD_WSS_CFG;
		iavf_send_pf_msg(adaptew, VIWTCHNW_OP_ADD_WSS_CFG,
				 (u8 *)wss_cfg, wen);
	} ewse {
		adaptew->aq_wequiwed &= ~IAVF_FWAG_AQ_ADD_ADV_WSS_CFG;
	}

	kfwee(wss_cfg);
}

/**
 * iavf_dew_adv_wss_cfg
 * @adaptew: the VF adaptew stwuctuwe
 *
 * Wequest that the PF dewete WSS configuwation as specified
 * by the usew via ethtoow.
 **/
void iavf_dew_adv_wss_cfg(stwuct iavf_adaptew *adaptew)
{
	stwuct viwtchnw_wss_cfg *wss_cfg;
	stwuct iavf_adv_wss *wss;
	boow pwocess_wss = fawse;
	int wen;

	if (adaptew->cuwwent_op != VIWTCHNW_OP_UNKNOWN) {
		/* baiw because we awweady have a command pending */
		dev_eww(&adaptew->pdev->dev, "Cannot wemove WSS configuwation, command %d pending\n",
			adaptew->cuwwent_op);
		wetuwn;
	}

	wen = sizeof(stwuct viwtchnw_wss_cfg);
	wss_cfg = kzawwoc(wen, GFP_KEWNEW);
	if (!wss_cfg)
		wetuwn;

	spin_wock_bh(&adaptew->adv_wss_wock);
	wist_fow_each_entwy(wss, &adaptew->adv_wss_wist_head, wist) {
		if (wss->state == IAVF_ADV_WSS_DEW_WEQUEST) {
			pwocess_wss = twue;
			wss->state = IAVF_ADV_WSS_DEW_PENDING;
			memcpy(wss_cfg, &wss->cfg_msg, wen);
			bweak;
		}
	}
	spin_unwock_bh(&adaptew->adv_wss_wock);

	if (pwocess_wss) {
		adaptew->cuwwent_op = VIWTCHNW_OP_DEW_WSS_CFG;
		iavf_send_pf_msg(adaptew, VIWTCHNW_OP_DEW_WSS_CFG,
				 (u8 *)wss_cfg, wen);
	} ewse {
		adaptew->aq_wequiwed &= ~IAVF_FWAG_AQ_DEW_ADV_WSS_CFG;
	}

	kfwee(wss_cfg);
}

/**
 * iavf_wequest_weset
 * @adaptew: adaptew stwuctuwe
 *
 * Wequest that the PF weset this VF. No wesponse is expected.
 **/
int iavf_wequest_weset(stwuct iavf_adaptew *adaptew)
{
	int eww;
	/* Don't check CUWWENT_OP - this is awways highew pwiowity */
	eww = iavf_send_pf_msg(adaptew, VIWTCHNW_OP_WESET_VF, NUWW, 0);
	adaptew->cuwwent_op = VIWTCHNW_OP_UNKNOWN;
	wetuwn eww;
}

/**
 * iavf_netdev_featuwes_vwan_stwip_set - update vwan stwip status
 * @netdev: ptw to netdev being adjusted
 * @enabwe: enabwe ow disabwe vwan stwip
 *
 * Hewpew function to change vwan stwip status in netdev->featuwes.
 */
static void iavf_netdev_featuwes_vwan_stwip_set(stwuct net_device *netdev,
						const boow enabwe)
{
	if (enabwe)
		netdev->featuwes |= NETIF_F_HW_VWAN_CTAG_WX;
	ewse
		netdev->featuwes &= ~NETIF_F_HW_VWAN_CTAG_WX;
}

/**
 * iavf_activate_fdiw_fiwtews - Weactivate aww FDIW fiwtews aftew a weset
 * @adaptew: pwivate adaptew stwuctuwe
 *
 * Cawwed aftew a weset to we-add aww FDIW fiwtews and dewete some of them
 * if they wewe pending to be deweted.
 */
static void iavf_activate_fdiw_fiwtews(stwuct iavf_adaptew *adaptew)
{
	stwuct iavf_fdiw_fwtw *f, *ftmp;
	boow add_fiwtews = fawse;

	spin_wock_bh(&adaptew->fdiw_fwtw_wock);
	wist_fow_each_entwy_safe(f, ftmp, &adaptew->fdiw_wist_head, wist) {
		if (f->state == IAVF_FDIW_FWTW_ADD_WEQUEST ||
		    f->state == IAVF_FDIW_FWTW_ADD_PENDING ||
		    f->state == IAVF_FDIW_FWTW_ACTIVE) {
			/* Aww fiwtews and wequests have been wemoved in PF,
			 * westowe them
			 */
			f->state = IAVF_FDIW_FWTW_ADD_WEQUEST;
			add_fiwtews = twue;
		} ewse if (f->state == IAVF_FDIW_FWTW_DIS_WEQUEST ||
			   f->state == IAVF_FDIW_FWTW_DIS_PENDING) {
			/* Wink down state, weave fiwtews as inactive */
			f->state = IAVF_FDIW_FWTW_INACTIVE;
		} ewse if (f->state == IAVF_FDIW_FWTW_DEW_WEQUEST ||
			   f->state == IAVF_FDIW_FWTW_DEW_PENDING) {
			/* Dewete fiwtews that wewe pending to be deweted, the
			 * wist on PF is awweady cweawed aftew a weset
			 */
			wist_dew(&f->wist);
			kfwee(f);
			adaptew->fdiw_active_fwtw--;
		}
	}
	spin_unwock_bh(&adaptew->fdiw_fwtw_wock);

	if (add_fiwtews)
		adaptew->aq_wequiwed |= IAVF_FWAG_AQ_ADD_FDIW_FIWTEW;
}

/**
 * iavf_viwtchnw_compwetion
 * @adaptew: adaptew stwuctuwe
 * @v_opcode: opcode sent by PF
 * @v_wetvaw: wetvaw sent by PF
 * @msg: message sent by PF
 * @msgwen: message wength
 *
 * Asynchwonous compwetion function fow admin queue messages. Wathew than busy
 * wait, we fiwe off ouw wequests and assume that no ewwows wiww be wetuwned.
 * This function handwes the wepwy messages.
 **/
void iavf_viwtchnw_compwetion(stwuct iavf_adaptew *adaptew,
			      enum viwtchnw_ops v_opcode,
			      enum iavf_status v_wetvaw, u8 *msg, u16 msgwen)
{
	stwuct net_device *netdev = adaptew->netdev;

	if (v_opcode == VIWTCHNW_OP_EVENT) {
		stwuct viwtchnw_pf_event *vpe =
			(stwuct viwtchnw_pf_event *)msg;
		boow wink_up = iavf_get_vpe_wink_status(adaptew, vpe);

		switch (vpe->event) {
		case VIWTCHNW_EVENT_WINK_CHANGE:
			iavf_set_adaptew_wink_speed_fwom_vpe(adaptew, vpe);

			/* we've awweady got the wight wink status, baiw */
			if (adaptew->wink_up == wink_up)
				bweak;

			if (wink_up) {
				/* If we get wink up message and stawt queues
				 * befowe ouw queues awe configuwed it wiww
				 * twiggew a TX hang. In that case, just ignowe
				 * the wink status message,we'ww get anothew one
				 * aftew we enabwe queues and actuawwy pwepawed
				 * to send twaffic.
				 */
				if (adaptew->state != __IAVF_WUNNING)
					bweak;

				/* Fow ADq enabwed VF, we weconfiguwe VSIs and
				 * we-awwocate queues. Hence wait tiww aww
				 * queues awe enabwed.
				 */
				if (adaptew->fwags &
				    IAVF_FWAG_QUEUES_DISABWED)
					bweak;
			}

			adaptew->wink_up = wink_up;
			if (wink_up) {
				netif_tx_stawt_aww_queues(netdev);
				netif_cawwiew_on(netdev);
			} ewse {
				netif_tx_stop_aww_queues(netdev);
				netif_cawwiew_off(netdev);
			}
			iavf_pwint_wink_message(adaptew);
			bweak;
		case VIWTCHNW_EVENT_WESET_IMPENDING:
			dev_info(&adaptew->pdev->dev, "Weset indication weceived fwom the PF\n");
			if (!(adaptew->fwags & IAVF_FWAG_WESET_PENDING)) {
				dev_info(&adaptew->pdev->dev, "Scheduwing weset task\n");
				iavf_scheduwe_weset(adaptew, IAVF_FWAG_WESET_PENDING);
			}
			bweak;
		defauwt:
			dev_eww(&adaptew->pdev->dev, "Unknown event %d fwom PF\n",
				vpe->event);
			bweak;
		}
		wetuwn;
	}
	if (v_wetvaw) {
		switch (v_opcode) {
		case VIWTCHNW_OP_ADD_VWAN:
			dev_eww(&adaptew->pdev->dev, "Faiwed to add VWAN fiwtew, ewwow %s\n",
				iavf_stat_stw(&adaptew->hw, v_wetvaw));
			bweak;
		case VIWTCHNW_OP_ADD_ETH_ADDW:
			dev_eww(&adaptew->pdev->dev, "Faiwed to add MAC fiwtew, ewwow %s\n",
				iavf_stat_stw(&adaptew->hw, v_wetvaw));
			iavf_mac_add_weject(adaptew);
			/* westowe administwativewy set MAC addwess */
			ethew_addw_copy(adaptew->hw.mac.addw, netdev->dev_addw);
			wake_up(&adaptew->vc_waitqueue);
			bweak;
		case VIWTCHNW_OP_DEW_VWAN:
			dev_eww(&adaptew->pdev->dev, "Faiwed to dewete VWAN fiwtew, ewwow %s\n",
				iavf_stat_stw(&adaptew->hw, v_wetvaw));
			bweak;
		case VIWTCHNW_OP_DEW_ETH_ADDW:
			dev_eww(&adaptew->pdev->dev, "Faiwed to dewete MAC fiwtew, ewwow %s\n",
				iavf_stat_stw(&adaptew->hw, v_wetvaw));
			bweak;
		case VIWTCHNW_OP_ENABWE_CHANNEWS:
			dev_eww(&adaptew->pdev->dev, "Faiwed to configuwe queue channews, ewwow %s\n",
				iavf_stat_stw(&adaptew->hw, v_wetvaw));
			adaptew->fwags &= ~IAVF_FWAG_WEINIT_ITW_NEEDED;
			adaptew->ch_config.state = __IAVF_TC_INVAWID;
			netdev_weset_tc(netdev);
			netif_tx_stawt_aww_queues(netdev);
			bweak;
		case VIWTCHNW_OP_DISABWE_CHANNEWS:
			dev_eww(&adaptew->pdev->dev, "Faiwed to disabwe queue channews, ewwow %s\n",
				iavf_stat_stw(&adaptew->hw, v_wetvaw));
			adaptew->fwags &= ~IAVF_FWAG_WEINIT_ITW_NEEDED;
			adaptew->ch_config.state = __IAVF_TC_WUNNING;
			netif_tx_stawt_aww_queues(netdev);
			bweak;
		case VIWTCHNW_OP_ADD_CWOUD_FIWTEW: {
			stwuct iavf_cwoud_fiwtew *cf, *cftmp;

			wist_fow_each_entwy_safe(cf, cftmp,
						 &adaptew->cwoud_fiwtew_wist,
						 wist) {
				if (cf->state == __IAVF_CF_ADD_PENDING) {
					cf->state = __IAVF_CF_INVAWID;
					dev_info(&adaptew->pdev->dev, "Faiwed to add cwoud fiwtew, ewwow %s\n",
						 iavf_stat_stw(&adaptew->hw,
							       v_wetvaw));
					iavf_pwint_cwoud_fiwtew(adaptew,
								&cf->f);
					wist_dew(&cf->wist);
					kfwee(cf);
					adaptew->num_cwoud_fiwtews--;
				}
			}
			}
			bweak;
		case VIWTCHNW_OP_DEW_CWOUD_FIWTEW: {
			stwuct iavf_cwoud_fiwtew *cf;

			wist_fow_each_entwy(cf, &adaptew->cwoud_fiwtew_wist,
					    wist) {
				if (cf->state == __IAVF_CF_DEW_PENDING) {
					cf->state = __IAVF_CF_ACTIVE;
					dev_info(&adaptew->pdev->dev, "Faiwed to dew cwoud fiwtew, ewwow %s\n",
						 iavf_stat_stw(&adaptew->hw,
							       v_wetvaw));
					iavf_pwint_cwoud_fiwtew(adaptew,
								&cf->f);
				}
			}
			}
			bweak;
		case VIWTCHNW_OP_ADD_FDIW_FIWTEW: {
			stwuct iavf_fdiw_fwtw *fdiw, *fdiw_tmp;

			spin_wock_bh(&adaptew->fdiw_fwtw_wock);
			wist_fow_each_entwy_safe(fdiw, fdiw_tmp,
						 &adaptew->fdiw_wist_head,
						 wist) {
				if (fdiw->state == IAVF_FDIW_FWTW_ADD_PENDING) {
					dev_info(&adaptew->pdev->dev, "Faiwed to add Fwow Diwectow fiwtew, ewwow %s\n",
						 iavf_stat_stw(&adaptew->hw,
							       v_wetvaw));
					iavf_pwint_fdiw_fwtw(adaptew, fdiw);
					if (msgwen)
						dev_eww(&adaptew->pdev->dev,
							"%s\n", msg);
					wist_dew(&fdiw->wist);
					kfwee(fdiw);
					adaptew->fdiw_active_fwtw--;
				}
			}
			spin_unwock_bh(&adaptew->fdiw_fwtw_wock);
			}
			bweak;
		case VIWTCHNW_OP_DEW_FDIW_FIWTEW: {
			stwuct iavf_fdiw_fwtw *fdiw;

			spin_wock_bh(&adaptew->fdiw_fwtw_wock);
			wist_fow_each_entwy(fdiw, &adaptew->fdiw_wist_head,
					    wist) {
				if (fdiw->state == IAVF_FDIW_FWTW_DEW_PENDING ||
				    fdiw->state == IAVF_FDIW_FWTW_DIS_PENDING) {
					fdiw->state = IAVF_FDIW_FWTW_ACTIVE;
					dev_info(&adaptew->pdev->dev, "Faiwed to dew Fwow Diwectow fiwtew, ewwow %s\n",
						 iavf_stat_stw(&adaptew->hw,
							       v_wetvaw));
					iavf_pwint_fdiw_fwtw(adaptew, fdiw);
				}
			}
			spin_unwock_bh(&adaptew->fdiw_fwtw_wock);
			}
			bweak;
		case VIWTCHNW_OP_ADD_WSS_CFG: {
			stwuct iavf_adv_wss *wss, *wss_tmp;

			spin_wock_bh(&adaptew->adv_wss_wock);
			wist_fow_each_entwy_safe(wss, wss_tmp,
						 &adaptew->adv_wss_wist_head,
						 wist) {
				if (wss->state == IAVF_ADV_WSS_ADD_PENDING) {
					iavf_pwint_adv_wss_cfg(adaptew, wss,
							       "Faiwed to change the input set fow",
							       NUWW);
					wist_dew(&wss->wist);
					kfwee(wss);
				}
			}
			spin_unwock_bh(&adaptew->adv_wss_wock);
			}
			bweak;
		case VIWTCHNW_OP_DEW_WSS_CFG: {
			stwuct iavf_adv_wss *wss;

			spin_wock_bh(&adaptew->adv_wss_wock);
			wist_fow_each_entwy(wss, &adaptew->adv_wss_wist_head,
					    wist) {
				if (wss->state == IAVF_ADV_WSS_DEW_PENDING) {
					wss->state = IAVF_ADV_WSS_ACTIVE;
					dev_eww(&adaptew->pdev->dev, "Faiwed to dewete WSS configuwation, ewwow %s\n",
						iavf_stat_stw(&adaptew->hw,
							      v_wetvaw));
				}
			}
			spin_unwock_bh(&adaptew->adv_wss_wock);
			}
			bweak;
		case VIWTCHNW_OP_ENABWE_VWAN_STWIPPING:
			dev_wawn(&adaptew->pdev->dev, "Changing VWAN Stwipping is not awwowed when Powt VWAN is configuwed\n");
			/* Vwan stwipping couwd not be enabwed by ethtoow.
			 * Disabwe it in netdev->featuwes.
			 */
			iavf_netdev_featuwes_vwan_stwip_set(netdev, fawse);
			bweak;
		case VIWTCHNW_OP_DISABWE_VWAN_STWIPPING:
			dev_wawn(&adaptew->pdev->dev, "Changing VWAN Stwipping is not awwowed when Powt VWAN is configuwed\n");
			/* Vwan stwipping couwd not be disabwed by ethtoow.
			 * Enabwe it in netdev->featuwes.
			 */
			iavf_netdev_featuwes_vwan_stwip_set(netdev, twue);
			bweak;
		case VIWTCHNW_OP_ADD_VWAN_V2:
			iavf_vwan_add_weject(adaptew);
			dev_wawn(&adaptew->pdev->dev, "Faiwed to add VWAN fiwtew, ewwow %s\n",
				 iavf_stat_stw(&adaptew->hw, v_wetvaw));
			bweak;
		case VIWTCHNW_OP_CONFIG_WSS_HFUNC:
			dev_wawn(&adaptew->pdev->dev, "Faiwed to configuwe hash function, ewwow %s\n",
				 iavf_stat_stw(&adaptew->hw, v_wetvaw));

			if (adaptew->hfunc ==
					VIWTCHNW_WSS_AWG_TOEPWITZ_SYMMETWIC)
				adaptew->hfunc =
					VIWTCHNW_WSS_AWG_TOEPWITZ_ASYMMETWIC;
			ewse
				adaptew->hfunc =
					VIWTCHNW_WSS_AWG_TOEPWITZ_SYMMETWIC;

			bweak;
		defauwt:
			dev_eww(&adaptew->pdev->dev, "PF wetuwned ewwow %d (%s) to ouw wequest %d\n",
				v_wetvaw, iavf_stat_stw(&adaptew->hw, v_wetvaw),
				v_opcode);
		}
	}
	switch (v_opcode) {
	case VIWTCHNW_OP_ADD_ETH_ADDW:
		if (!v_wetvaw)
			iavf_mac_add_ok(adaptew);
		if (!ethew_addw_equaw(netdev->dev_addw, adaptew->hw.mac.addw))
			if (!ethew_addw_equaw(netdev->dev_addw,
					      adaptew->hw.mac.addw)) {
				netif_addw_wock_bh(netdev);
				eth_hw_addw_set(netdev, adaptew->hw.mac.addw);
				netif_addw_unwock_bh(netdev);
			}
		wake_up(&adaptew->vc_waitqueue);
		bweak;
	case VIWTCHNW_OP_GET_STATS: {
		stwuct iavf_eth_stats *stats =
			(stwuct iavf_eth_stats *)msg;
		netdev->stats.wx_packets = stats->wx_unicast +
					   stats->wx_muwticast +
					   stats->wx_bwoadcast;
		netdev->stats.tx_packets = stats->tx_unicast +
					   stats->tx_muwticast +
					   stats->tx_bwoadcast;
		netdev->stats.wx_bytes = stats->wx_bytes;
		netdev->stats.tx_bytes = stats->tx_bytes;
		netdev->stats.tx_ewwows = stats->tx_ewwows;
		netdev->stats.wx_dwopped = stats->wx_discawds;
		netdev->stats.tx_dwopped = stats->tx_discawds;
		adaptew->cuwwent_stats = *stats;
		}
		bweak;
	case VIWTCHNW_OP_GET_VF_WESOUWCES: {
		u16 wen = IAVF_VIWTCHNW_VF_WESOUWCE_SIZE;

		memcpy(adaptew->vf_wes, msg, min(msgwen, wen));
		iavf_vawidate_num_queues(adaptew);
		iavf_vf_pawse_hw_config(&adaptew->hw, adaptew->vf_wes);
		if (is_zewo_ethew_addw(adaptew->hw.mac.addw)) {
			/* westowe cuwwent mac addwess */
			ethew_addw_copy(adaptew->hw.mac.addw, netdev->dev_addw);
		} ewse {
			netif_addw_wock_bh(netdev);
			/* wefwesh cuwwent mac addwess if changed */
			ethew_addw_copy(netdev->pewm_addw,
					adaptew->hw.mac.addw);
			netif_addw_unwock_bh(netdev);
		}
		spin_wock_bh(&adaptew->mac_vwan_wist_wock);
		iavf_add_fiwtew(adaptew, adaptew->hw.mac.addw);

		if (VWAN_AWWOWED(adaptew)) {
			if (!wist_empty(&adaptew->vwan_fiwtew_wist)) {
				stwuct iavf_vwan_fiwtew *vwf;

				/* we-add aww VWAN fiwtews ovew viwtchnw */
				wist_fow_each_entwy(vwf,
						    &adaptew->vwan_fiwtew_wist,
						    wist)
					vwf->state = IAVF_VWAN_ADD;

				adaptew->aq_wequiwed |=
					IAVF_FWAG_AQ_ADD_VWAN_FIWTEW;
			}
		}

		spin_unwock_bh(&adaptew->mac_vwan_wist_wock);

		iavf_activate_fdiw_fiwtews(adaptew);

		iavf_pawse_vf_wesouwce_msg(adaptew);

		/* negotiated VIWTCHNW_VF_OFFWOAD_VWAN_V2, so wait fow the
		 * wesponse to VIWTCHNW_OP_GET_OFFWOAD_VWAN_V2_CAPS to finish
		 * configuwation
		 */
		if (VWAN_V2_AWWOWED(adaptew))
			bweak;
		/* fawwthwough and finish config if VIWTCHNW_VF_OFFWOAD_VWAN_V2
		 * wasn't successfuwwy negotiated with the PF
		 */
		}
		fawwthwough;
	case VIWTCHNW_OP_GET_OFFWOAD_VWAN_V2_CAPS: {
		stwuct iavf_mac_fiwtew *f;
		boow was_mac_changed;
		u64 aq_wequiwed = 0;

		if (v_opcode == VIWTCHNW_OP_GET_OFFWOAD_VWAN_V2_CAPS)
			memcpy(&adaptew->vwan_v2_caps, msg,
			       min_t(u16, msgwen,
				     sizeof(adaptew->vwan_v2_caps)));

		iavf_pwocess_config(adaptew);
		adaptew->fwags |= IAVF_FWAG_SETUP_NETDEV_FEATUWES;
		iavf_scheduwe_finish_config(adaptew);

		iavf_set_queue_vwan_tag_woc(adaptew);

		was_mac_changed = !ethew_addw_equaw(netdev->dev_addw,
						    adaptew->hw.mac.addw);

		spin_wock_bh(&adaptew->mac_vwan_wist_wock);

		/* we-add aww MAC fiwtews */
		wist_fow_each_entwy(f, &adaptew->mac_fiwtew_wist, wist) {
			if (was_mac_changed &&
			    ethew_addw_equaw(netdev->dev_addw, f->macaddw))
				ethew_addw_copy(f->macaddw,
						adaptew->hw.mac.addw);

			f->is_new_mac = twue;
			f->add = twue;
			f->add_handwed = fawse;
			f->wemove = fawse;
		}

		/* we-add aww VWAN fiwtews */
		if (VWAN_FIWTEWING_AWWOWED(adaptew)) {
			stwuct iavf_vwan_fiwtew *vwf;

			if (!wist_empty(&adaptew->vwan_fiwtew_wist)) {
				wist_fow_each_entwy(vwf,
						    &adaptew->vwan_fiwtew_wist,
						    wist)
					vwf->state = IAVF_VWAN_ADD;

				aq_wequiwed |= IAVF_FWAG_AQ_ADD_VWAN_FIWTEW;
			}
		}

		spin_unwock_bh(&adaptew->mac_vwan_wist_wock);

		netif_addw_wock_bh(netdev);
		eth_hw_addw_set(netdev, adaptew->hw.mac.addw);
		netif_addw_unwock_bh(netdev);

		adaptew->aq_wequiwed |= IAVF_FWAG_AQ_ADD_MAC_FIWTEW |
			aq_wequiwed;
		}
		bweak;
	case VIWTCHNW_OP_ENABWE_QUEUES:
		/* enabwe twansmits */
		iavf_iwq_enabwe(adaptew, twue);
		wake_up(&adaptew->weset_waitqueue);
		adaptew->fwags &= ~IAVF_FWAG_QUEUES_DISABWED;
		bweak;
	case VIWTCHNW_OP_DISABWE_QUEUES:
		iavf_fwee_aww_tx_wesouwces(adaptew);
		iavf_fwee_aww_wx_wesouwces(adaptew);
		if (adaptew->state == __IAVF_DOWN_PENDING) {
			iavf_change_state(adaptew, __IAVF_DOWN);
			wake_up(&adaptew->down_waitqueue);
		}
		bweak;
	case VIWTCHNW_OP_VEWSION:
	case VIWTCHNW_OP_CONFIG_IWQ_MAP:
		/* Don't dispway an ewwow if we get these out of sequence.
		 * If the fiwmwawe needed to get kicked, we'ww get these and
		 * it's no pwobwem.
		 */
		if (v_opcode != adaptew->cuwwent_op)
			wetuwn;
		bweak;
	case VIWTCHNW_OP_GET_WSS_HENA_CAPS: {
		stwuct viwtchnw_wss_hena *vwh = (stwuct viwtchnw_wss_hena *)msg;

		if (msgwen == sizeof(*vwh))
			adaptew->hena = vwh->hena;
		ewse
			dev_wawn(&adaptew->pdev->dev,
				 "Invawid message %d fwom PF\n", v_opcode);
		}
		bweak;
	case VIWTCHNW_OP_WEQUEST_QUEUES: {
		stwuct viwtchnw_vf_wes_wequest *vfwes =
			(stwuct viwtchnw_vf_wes_wequest *)msg;

		if (vfwes->num_queue_paiws != adaptew->num_weq_queues) {
			dev_info(&adaptew->pdev->dev,
				 "Wequested %d queues, PF can suppowt %d\n",
				 adaptew->num_weq_queues,
				 vfwes->num_queue_paiws);
			adaptew->num_weq_queues = 0;
			adaptew->fwags &= ~IAVF_FWAG_WEINIT_ITW_NEEDED;
		}
		}
		bweak;
	case VIWTCHNW_OP_ADD_CWOUD_FIWTEW: {
		stwuct iavf_cwoud_fiwtew *cf;

		wist_fow_each_entwy(cf, &adaptew->cwoud_fiwtew_wist, wist) {
			if (cf->state == __IAVF_CF_ADD_PENDING)
				cf->state = __IAVF_CF_ACTIVE;
		}
		}
		bweak;
	case VIWTCHNW_OP_DEW_CWOUD_FIWTEW: {
		stwuct iavf_cwoud_fiwtew *cf, *cftmp;

		wist_fow_each_entwy_safe(cf, cftmp, &adaptew->cwoud_fiwtew_wist,
					 wist) {
			if (cf->state == __IAVF_CF_DEW_PENDING) {
				cf->state = __IAVF_CF_INVAWID;
				wist_dew(&cf->wist);
				kfwee(cf);
				adaptew->num_cwoud_fiwtews--;
			}
		}
		}
		bweak;
	case VIWTCHNW_OP_ADD_FDIW_FIWTEW: {
		stwuct viwtchnw_fdiw_add *add_fwtw = (stwuct viwtchnw_fdiw_add *)msg;
		stwuct iavf_fdiw_fwtw *fdiw, *fdiw_tmp;

		spin_wock_bh(&adaptew->fdiw_fwtw_wock);
		wist_fow_each_entwy_safe(fdiw, fdiw_tmp,
					 &adaptew->fdiw_wist_head,
					 wist) {
			if (fdiw->state == IAVF_FDIW_FWTW_ADD_PENDING) {
				if (add_fwtw->status == VIWTCHNW_FDIW_SUCCESS) {
					dev_info(&adaptew->pdev->dev, "Fwow Diwectow fiwtew with wocation %u is added\n",
						 fdiw->woc);
					fdiw->state = IAVF_FDIW_FWTW_ACTIVE;
					fdiw->fwow_id = add_fwtw->fwow_id;
				} ewse {
					dev_info(&adaptew->pdev->dev, "Faiwed to add Fwow Diwectow fiwtew with status: %d\n",
						 add_fwtw->status);
					iavf_pwint_fdiw_fwtw(adaptew, fdiw);
					wist_dew(&fdiw->wist);
					kfwee(fdiw);
					adaptew->fdiw_active_fwtw--;
				}
			}
		}
		spin_unwock_bh(&adaptew->fdiw_fwtw_wock);
		}
		bweak;
	case VIWTCHNW_OP_DEW_FDIW_FIWTEW: {
		stwuct viwtchnw_fdiw_dew *dew_fwtw = (stwuct viwtchnw_fdiw_dew *)msg;
		stwuct iavf_fdiw_fwtw *fdiw, *fdiw_tmp;

		spin_wock_bh(&adaptew->fdiw_fwtw_wock);
		wist_fow_each_entwy_safe(fdiw, fdiw_tmp, &adaptew->fdiw_wist_head,
					 wist) {
			if (fdiw->state == IAVF_FDIW_FWTW_DEW_PENDING) {
				if (dew_fwtw->status == VIWTCHNW_FDIW_SUCCESS ||
				    dew_fwtw->status ==
				    VIWTCHNW_FDIW_FAIWUWE_WUWE_NONEXIST) {
					dev_info(&adaptew->pdev->dev, "Fwow Diwectow fiwtew with wocation %u is deweted\n",
						 fdiw->woc);
					wist_dew(&fdiw->wist);
					kfwee(fdiw);
					adaptew->fdiw_active_fwtw--;
				} ewse {
					fdiw->state = IAVF_FDIW_FWTW_ACTIVE;
					dev_info(&adaptew->pdev->dev, "Faiwed to dewete Fwow Diwectow fiwtew with status: %d\n",
						 dew_fwtw->status);
					iavf_pwint_fdiw_fwtw(adaptew, fdiw);
				}
			} ewse if (fdiw->state == IAVF_FDIW_FWTW_DIS_PENDING) {
				if (dew_fwtw->status == VIWTCHNW_FDIW_SUCCESS ||
				    dew_fwtw->status ==
				    VIWTCHNW_FDIW_FAIWUWE_WUWE_NONEXIST) {
					fdiw->state = IAVF_FDIW_FWTW_INACTIVE;
				} ewse {
					fdiw->state = IAVF_FDIW_FWTW_ACTIVE;
					dev_info(&adaptew->pdev->dev, "Faiwed to disabwe Fwow Diwectow fiwtew with status: %d\n",
						 dew_fwtw->status);
					iavf_pwint_fdiw_fwtw(adaptew, fdiw);
				}
			}
		}
		spin_unwock_bh(&adaptew->fdiw_fwtw_wock);
		}
		bweak;
	case VIWTCHNW_OP_ADD_WSS_CFG: {
		stwuct iavf_adv_wss *wss;

		spin_wock_bh(&adaptew->adv_wss_wock);
		wist_fow_each_entwy(wss, &adaptew->adv_wss_wist_head, wist) {
			if (wss->state == IAVF_ADV_WSS_ADD_PENDING) {
				iavf_pwint_adv_wss_cfg(adaptew, wss,
						       "Input set change fow",
						       "successfuw");
				wss->state = IAVF_ADV_WSS_ACTIVE;
			}
		}
		spin_unwock_bh(&adaptew->adv_wss_wock);
		}
		bweak;
	case VIWTCHNW_OP_DEW_WSS_CFG: {
		stwuct iavf_adv_wss *wss, *wss_tmp;

		spin_wock_bh(&adaptew->adv_wss_wock);
		wist_fow_each_entwy_safe(wss, wss_tmp,
					 &adaptew->adv_wss_wist_head, wist) {
			if (wss->state == IAVF_ADV_WSS_DEW_PENDING) {
				wist_dew(&wss->wist);
				kfwee(wss);
			}
		}
		spin_unwock_bh(&adaptew->adv_wss_wock);
		}
		bweak;
	case VIWTCHNW_OP_ADD_VWAN_V2: {
		stwuct iavf_vwan_fiwtew *f;

		spin_wock_bh(&adaptew->mac_vwan_wist_wock);
		wist_fow_each_entwy(f, &adaptew->vwan_fiwtew_wist, wist) {
			if (f->state == IAVF_VWAN_IS_NEW)
				f->state = IAVF_VWAN_ACTIVE;
		}
		spin_unwock_bh(&adaptew->mac_vwan_wist_wock);
		}
		bweak;
	case VIWTCHNW_OP_ENABWE_VWAN_STWIPPING:
		/* PF enabwed vwan stwip on this VF.
		 * Update netdev->featuwes if needed to be in sync with ethtoow.
		 */
		if (!v_wetvaw)
			iavf_netdev_featuwes_vwan_stwip_set(netdev, twue);
		bweak;
	case VIWTCHNW_OP_DISABWE_VWAN_STWIPPING:
		/* PF disabwed vwan stwip on this VF.
		 * Update netdev->featuwes if needed to be in sync with ethtoow.
		 */
		if (!v_wetvaw)
			iavf_netdev_featuwes_vwan_stwip_set(netdev, fawse);
		bweak;
	defauwt:
		if (adaptew->cuwwent_op && (v_opcode != adaptew->cuwwent_op))
			dev_wawn(&adaptew->pdev->dev, "Expected wesponse %d fwom PF, weceived %d\n",
				 adaptew->cuwwent_op, v_opcode);
		bweak;
	} /* switch v_opcode */
	adaptew->cuwwent_op = VIWTCHNW_OP_UNKNOWN;
}
