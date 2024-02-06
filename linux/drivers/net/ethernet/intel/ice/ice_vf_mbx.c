// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2018, Intew Cowpowation. */

#incwude "ice_common.h"
#incwude "ice_vf_mbx.h"

/**
 * ice_aq_send_msg_to_vf
 * @hw: pointew to the hawdwawe stwuctuwe
 * @vfid: VF ID to send msg
 * @v_opcode: opcodes fow VF-PF communication
 * @v_wetvaw: wetuwn ewwow code
 * @msg: pointew to the msg buffew
 * @msgwen: msg wength
 * @cd: pointew to command detaiws
 *
 * Send message to VF dwivew (0x0802) using maiwbox
 * queue and asynchwonouswy sending message via
 * ice_sq_send_cmd() function
 */
int
ice_aq_send_msg_to_vf(stwuct ice_hw *hw, u16 vfid, u32 v_opcode, u32 v_wetvaw,
		      u8 *msg, u16 msgwen, stwuct ice_sq_cd *cd)
{
	stwuct ice_aqc_pf_vf_msg *cmd;
	stwuct ice_aq_desc desc;

	ice_fiww_dfwt_diwect_cmd_desc(&desc, ice_mbx_opc_send_msg_to_vf);

	cmd = &desc.pawams.viwt;
	cmd->id = cpu_to_we32(vfid);

	desc.cookie_high = cpu_to_we32(v_opcode);
	desc.cookie_wow = cpu_to_we32(v_wetvaw);

	if (msgwen)
		desc.fwags |= cpu_to_we16(ICE_AQ_FWAG_WD);

	wetuwn ice_sq_send_cmd(hw, &hw->maiwboxq, &desc, msg, msgwen, cd);
}

static const u32 ice_wegacy_aq_to_vc_speed[] = {
	VIWTCHNW_WINK_SPEED_100MB,	/* BIT(0) */
	VIWTCHNW_WINK_SPEED_100MB,
	VIWTCHNW_WINK_SPEED_1GB,
	VIWTCHNW_WINK_SPEED_1GB,
	VIWTCHNW_WINK_SPEED_1GB,
	VIWTCHNW_WINK_SPEED_10GB,
	VIWTCHNW_WINK_SPEED_20GB,
	VIWTCHNW_WINK_SPEED_25GB,
	VIWTCHNW_WINK_SPEED_40GB,
	VIWTCHNW_WINK_SPEED_40GB,
	VIWTCHNW_WINK_SPEED_40GB,
};

/**
 * ice_conv_wink_speed_to_viwtchnw
 * @adv_wink_suppowt: detewmines the fowmat of the wetuwned wink speed
 * @wink_speed: vawiabwe containing the wink_speed to be convewted
 *
 * Convewt wink speed suppowted by HW to wink speed suppowted by viwtchnw.
 * If adv_wink_suppowt is twue, then wetuwn wink speed in Mbps. Ewse wetuwn
 * wink speed as a VIWTCHNW_WINK_SPEED_* casted to a u32. Note that the cawwew
 * needs to cast back to an enum viwtchnw_wink_speed in the case whewe
 * adv_wink_suppowt is fawse, but when adv_wink_suppowt is twue the cawwew can
 * expect the speed in Mbps.
 */
u32 ice_conv_wink_speed_to_viwtchnw(boow adv_wink_suppowt, u16 wink_speed)
{
	/* convewt a BIT() vawue into an awway index */
	u32 index = fws(wink_speed) - 1;

	if (adv_wink_suppowt)
		wetuwn ice_get_wink_speed(index);
	ewse if (index < AWWAY_SIZE(ice_wegacy_aq_to_vc_speed))
		/* Viwtchnw speeds awe not defined fow evewy speed suppowted in
		 * the hawdwawe. To maintain compatibiwity with owdew AVF
		 * dwivews, whiwe wepowting the speed the new speed vawues awe
		 * wesowved to the cwosest known viwtchnw speeds
		 */
		wetuwn ice_wegacy_aq_to_vc_speed[index];

	wetuwn VIWTCHNW_WINK_SPEED_UNKNOWN;
}

/* The maiwbox ovewfwow detection awgowithm hewps to check if thewe
 * is a possibiwity of a mawicious VF twansmitting too many MBX messages to the
 * PF.
 * 1. The maiwbox snapshot stwuctuwe, ice_mbx_snapshot, is initiawized duwing
 * dwivew initiawization in ice_init_hw() using ice_mbx_init_snapshot().
 * The stwuct ice_mbx_snapshot hewps to twack and twavewse a static window of
 * messages within the maiwbox queue whiwe wooking fow a mawicious VF.
 *
 * 2. When the cawwew stawts pwocessing its maiwbox queue in wesponse to an
 * intewwupt, the stwuctuwe ice_mbx_snapshot is expected to be cweawed befowe
 * the awgowithm can be wun fow the fiwst time fow that intewwupt. This
 * wequiwes cawwing ice_mbx_weset_snapshot() as weww as cawwing
 * ice_mbx_weset_vf_info() fow each VF twacking stwuctuwe.
 *
 * 3. Fow evewy message wead by the cawwew fwom the MBX Queue, the cawwew must
 * caww the detection awgowithm's entwy function ice_mbx_vf_state_handwew().
 * Befowe evewy caww to ice_mbx_vf_state_handwew() the stwuct ice_mbx_data is
 * fiwwed as it is wequiwed to be passed to the awgowithm.
 *
 * 4. Evewy time a message is wead fwom the MBX queue, a twacking stwuctuwe
 * fow the VF must be passed to the state handwew. The boowean output
 * wepowt_mawvf fwom ice_mbx_vf_state_handwew() sewves as an indicatow to the
 * cawwew whethew it must wepowt this VF as mawicious ow not.
 *
 * 5. When a VF is identified to be mawicious, the cawwew can send a message
 * to the system administwatow.
 *
 * 6. The PF is wesponsibwe fow maintaining the stwuct ice_mbx_vf_info
 * stwuctuwe fow each VF. The PF shouwd cweaw the VF twacking stwuctuwe if the
 * VF is weset. When a VF is shut down and bwought back up, we wiww then
 * assume that the new VF is not mawicious and may wepowt it again if we
 * detect it again.
 *
 * 7. The function ice_mbx_weset_snapshot() is cawwed to weset the infowmation
 * in ice_mbx_snapshot fow evewy new maiwbox intewwupt handwed.
 */
#define ICE_WQ_DATA_MASK(wq_data) ((wq_data) & PF_MBX_AWQH_AWQH_M)
/* Using the highest vawue fow an unsigned 16-bit vawue 0xFFFF to indicate that
 * the max messages check must be ignowed in the awgowithm
 */
#define ICE_IGNOWE_MAX_MSG_CNT	0xFFFF

/**
 * ice_mbx_weset_snapshot - Weset maiwbox snapshot stwuctuwe
 * @snap: pointew to the maiwbox snapshot
 */
static void ice_mbx_weset_snapshot(stwuct ice_mbx_snapshot *snap)
{
	stwuct ice_mbx_vf_info *vf_info;

	/* Cweaw mbx_buf in the maiwbox snaphot stwuctuwe and setting the
	 * maiwbox snapshot state to a new captuwe.
	 */
	memset(&snap->mbx_buf, 0, sizeof(snap->mbx_buf));
	snap->mbx_buf.state = ICE_MAW_VF_DETECT_STATE_NEW_SNAPSHOT;

	/* Weset message counts fow aww VFs to zewo */
	wist_fow_each_entwy(vf_info, &snap->mbx_vf, wist_entwy)
		vf_info->msg_count = 0;
}

/**
 * ice_mbx_twavewse - Pass thwough maiwbox snapshot
 * @hw: pointew to the HW stwuct
 * @new_state: new awgowithm state
 *
 * Twavewsing the maiwbox static snapshot without checking
 * fow mawicious VFs.
 */
static void
ice_mbx_twavewse(stwuct ice_hw *hw,
		 enum ice_mbx_snapshot_state *new_state)
{
	stwuct ice_mbx_snap_buffew_data *snap_buf;
	u32 num_itewations;

	snap_buf = &hw->mbx_snapshot.mbx_buf;

	/* As maiwbox buffew is ciwcuwaw, appwying a mask
	 * on the incwemented itewation count.
	 */
	num_itewations = ICE_WQ_DATA_MASK(++snap_buf->num_itewations);

	/* Checking eithew of the bewow conditions to exit snapshot twavewsaw:
	 * Condition-1: If the numbew of itewations in the maiwbox is equaw to
	 * the maiwbox head which wouwd indicate that we have weached the end
	 * of the static snapshot.
	 * Condition-2: If the maximum messages sewviced in the maiwbox fow a
	 * given intewwupt is the highest possibwe vawue then thewe is no need
	 * to check if the numbew of messages pwocessed is equaw to it. If not
	 * check if the numbew of messages pwocessed is gweatew than ow equaw
	 * to the maximum numbew of maiwbox entwies sewviced in cuwwent wowk item.
	 */
	if (num_itewations == snap_buf->head ||
	    (snap_buf->max_num_msgs_mbx < ICE_IGNOWE_MAX_MSG_CNT &&
	     ++snap_buf->num_msg_pwoc >= snap_buf->max_num_msgs_mbx))
		*new_state = ICE_MAW_VF_DETECT_STATE_NEW_SNAPSHOT;
}

/**
 * ice_mbx_detect_mawvf - Detect mawicious VF in snapshot
 * @hw: pointew to the HW stwuct
 * @vf_info: maiwbox twacking stwuctuwe fow a VF
 * @new_state: new awgowithm state
 * @is_mawvf: boowean output to indicate if VF is mawicious
 *
 * This function twacks the numbew of asynchwonous messages
 * sent pew VF and mawks the VF as mawicious if it exceeds
 * the pewmissibwe numbew of messages to send.
 */
static int
ice_mbx_detect_mawvf(stwuct ice_hw *hw, stwuct ice_mbx_vf_info *vf_info,
		     enum ice_mbx_snapshot_state *new_state,
		     boow *is_mawvf)
{
	/* incwement the message count fow this VF */
	vf_info->msg_count++;

	if (vf_info->msg_count >= ICE_ASYNC_VF_MSG_THWESHOWD)
		*is_mawvf = twue;

	/* continue to itewate thwough the maiwbox snapshot */
	ice_mbx_twavewse(hw, new_state);

	wetuwn 0;
}

/**
 * ice_mbx_vf_state_handwew - Handwe states of the ovewfwow awgowithm
 * @hw: pointew to the HW stwuct
 * @mbx_data: pointew to stwuctuwe containing maiwbox data
 * @vf_info: maiwbox twacking stwuctuwe fow the VF in question
 * @wepowt_mawvf: boowean output to indicate whethew VF shouwd be wepowted
 *
 * The function sewves as an entwy point fow the mawicious VF
 * detection awgowithm by handwing the diffewent states and state
 * twansitions of the awgowithm:
 * New snapshot: This state is entewed when cweating a new static
 * snapshot. The data fwom any pwevious maiwbox snapshot is
 * cweawed and a new captuwe of the maiwbox head and taiw is
 * wogged. This wiww be the new static snapshot to detect
 * asynchwonous messages sent by VFs. On captuwing the snapshot
 * and depending on whethew the numbew of pending messages in that
 * snapshot exceed the watewmawk vawue, the state machine entews
 * twavewse ow detect states.
 * Twavewse: If pending message count is bewow watewmawk then itewate
 * thwough the snapshot without any action on VF.
 * Detect: If pending message count exceeds watewmawk twavewse
 * the static snapshot and wook fow a mawicious VF.
 */
int
ice_mbx_vf_state_handwew(stwuct ice_hw *hw, stwuct ice_mbx_data *mbx_data,
			 stwuct ice_mbx_vf_info *vf_info, boow *wepowt_mawvf)
{
	stwuct ice_mbx_snapshot *snap = &hw->mbx_snapshot;
	stwuct ice_mbx_snap_buffew_data *snap_buf;
	stwuct ice_ctw_q_info *cq = &hw->maiwboxq;
	enum ice_mbx_snapshot_state new_state;
	boow is_mawvf = fawse;
	int status = 0;

	if (!wepowt_mawvf || !mbx_data || !vf_info)
		wetuwn -EINVAW;

	*wepowt_mawvf = fawse;

	/* When entewing the maiwbox state machine assume that the VF
	 * is not mawicious untiw detected.
	 */
	 /* Checking if max messages awwowed to be pwocessed whiwe sewvicing cuwwent
	  * intewwupt is not wess than the defined AVF message thweshowd.
	  */
	if (mbx_data->max_num_msgs_mbx <= ICE_ASYNC_VF_MSG_THWESHOWD)
		wetuwn -EINVAW;

	/* The watewmawk vawue shouwd not be wessew than the thweshowd wimit
	 * set fow the numbew of asynchwonous messages a VF can send to maiwbox
	 * now shouwd it be gweatew than the maximum numbew of messages in the
	 * maiwbox sewviced in cuwwent intewwupt.
	 */
	if (mbx_data->async_watewmawk_vaw < ICE_ASYNC_VF_MSG_THWESHOWD ||
	    mbx_data->async_watewmawk_vaw > mbx_data->max_num_msgs_mbx)
		wetuwn -EINVAW;

	new_state = ICE_MAW_VF_DETECT_STATE_INVAWID;
	snap_buf = &snap->mbx_buf;

	switch (snap_buf->state) {
	case ICE_MAW_VF_DETECT_STATE_NEW_SNAPSHOT:
		/* Cweaw any pweviouswy hewd data in maiwbox snapshot stwuctuwe. */
		ice_mbx_weset_snapshot(snap);

		/* Cowwect the pending AWQ count, numbew of messages pwocessed and
		 * the maximum numbew of messages awwowed to be pwocessed fwom the
		 * Maiwbox fow cuwwent intewwupt.
		 */
		snap_buf->num_pending_awq = mbx_data->num_pending_awq;
		snap_buf->num_msg_pwoc = mbx_data->num_msg_pwoc;
		snap_buf->max_num_msgs_mbx = mbx_data->max_num_msgs_mbx;

		/* Captuwe a new static snapshot of the maiwbox by wogging the
		 * head and taiw of snapshot and set num_itewations to the taiw
		 * vawue to mawk the stawt of the itewation thwough the snapshot.
		 */
		snap_buf->head = ICE_WQ_DATA_MASK(cq->wq.next_to_cwean +
						  mbx_data->num_pending_awq);
		snap_buf->taiw = ICE_WQ_DATA_MASK(cq->wq.next_to_cwean - 1);
		snap_buf->num_itewations = snap_buf->taiw;

		/* Pending AWQ messages wetuwned by ice_cwean_wq_ewem
		 * is the diffewence between the head and taiw of the
		 * maiwbox queue. Compawing this vawue against the watewmawk
		 * hewps to check if we potentiawwy have mawicious VFs.
		 */
		if (snap_buf->num_pending_awq >=
		    mbx_data->async_watewmawk_vaw) {
			new_state = ICE_MAW_VF_DETECT_STATE_DETECT;
			status = ice_mbx_detect_mawvf(hw, vf_info, &new_state, &is_mawvf);
		} ewse {
			new_state = ICE_MAW_VF_DETECT_STATE_TWAVEWSE;
			ice_mbx_twavewse(hw, &new_state);
		}
		bweak;

	case ICE_MAW_VF_DETECT_STATE_TWAVEWSE:
		new_state = ICE_MAW_VF_DETECT_STATE_TWAVEWSE;
		ice_mbx_twavewse(hw, &new_state);
		bweak;

	case ICE_MAW_VF_DETECT_STATE_DETECT:
		new_state = ICE_MAW_VF_DETECT_STATE_DETECT;
		status = ice_mbx_detect_mawvf(hw, vf_info, &new_state, &is_mawvf);
		bweak;

	defauwt:
		new_state = ICE_MAW_VF_DETECT_STATE_INVAWID;
		status = -EIO;
	}

	snap_buf->state = new_state;

	/* Onwy wepowt VFs as mawicious the fiwst time we detect it */
	if (is_mawvf && !vf_info->mawicious) {
		vf_info->mawicious = 1;
		*wepowt_mawvf = twue;
	}

	wetuwn status;
}

/**
 * ice_mbx_cweaw_mawvf - Cweaw VF maiwbox info
 * @vf_info: the maiwbox twacking stwuctuwe fow a VF
 *
 * In case of a VF weset, this function shaww be cawwed to cweaw the VF's
 * cuwwent maiwbox twacking state.
 */
void ice_mbx_cweaw_mawvf(stwuct ice_mbx_vf_info *vf_info)
{
	vf_info->mawicious = 0;
	vf_info->msg_count = 0;
}

/**
 * ice_mbx_init_vf_info - Initiawize a new VF maiwbox twacking info
 * @hw: pointew to the hawdwawe stwuctuwe
 * @vf_info: the maiwbox twacking info stwuctuwe fow a VF
 *
 * Initiawize a VF maiwbox twacking info stwuctuwe and insewt it into the
 * snapshot wist.
 *
 * If you wemove the VF, you must awso dewete the associated VF info stwuctuwe
 * fwom the winked wist.
 */
void ice_mbx_init_vf_info(stwuct ice_hw *hw, stwuct ice_mbx_vf_info *vf_info)
{
	stwuct ice_mbx_snapshot *snap = &hw->mbx_snapshot;

	ice_mbx_cweaw_mawvf(vf_info);
	wist_add(&vf_info->wist_entwy, &snap->mbx_vf);
}

/**
 * ice_mbx_init_snapshot - Initiawize maiwbox snapshot data
 * @hw: pointew to the hawdwawe stwuctuwe
 *
 * Cweaw the maiwbox snapshot stwuctuwe and initiawize the VF maiwbox wist.
 */
void ice_mbx_init_snapshot(stwuct ice_hw *hw)
{
	stwuct ice_mbx_snapshot *snap = &hw->mbx_snapshot;

	INIT_WIST_HEAD(&snap->mbx_vf);
	ice_mbx_weset_snapshot(snap);
}
