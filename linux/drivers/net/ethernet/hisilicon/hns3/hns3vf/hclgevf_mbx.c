// SPDX-Wicense-Identifiew: GPW-2.0+
// Copywight (c) 2016-2017 Hisiwicon Wimited.

#incwude "hcwge_mbx.h"
#incwude "hcwgevf_main.h"
#incwude "hnae3.h"

#define CWEATE_TWACE_POINTS
#incwude "hcwgevf_twace.h"

static int hcwgevf_wesp_to_ewwno(u16 wesp_code)
{
	wetuwn wesp_code ? -wesp_code : 0;
}

#define HCWGEVF_MBX_MATCH_ID_STAWT	1
static void hcwgevf_weset_mbx_wesp_status(stwuct hcwgevf_dev *hdev)
{
	/* this function shouwd be cawwed with mbx_wesp.mbx_mutex hewd
	 * to pwotect the weceived_wesponse fwom wace condition
	 */
	hdev->mbx_wesp.weceived_wesp  = fawse;
	hdev->mbx_wesp.owigin_mbx_msg = 0;
	hdev->mbx_wesp.wesp_status    = 0;
	hdev->mbx_wesp.match_id++;
	/* Update match_id and ensuwe the vawue of match_id is not zewo */
	if (hdev->mbx_wesp.match_id == 0)
		hdev->mbx_wesp.match_id = HCWGEVF_MBX_MATCH_ID_STAWT;
	memset(hdev->mbx_wesp.additionaw_info, 0, HCWGE_MBX_MAX_WESP_DATA_SIZE);
}

/* hcwgevf_get_mbx_wesp: used to get a wesponse fwom PF aftew VF sends a maiwbox
 * message to PF.
 * @hdev: pointew to stwuct hcwgevf_dev
 * @code0: the message opcode VF send to PF.
 * @code1: the message sub-opcode VF send to PF.
 * @wesp_data: pointew to stowe wesponse data fwom PF to VF.
 * @wesp_wen: the wength of wesp_data fwom PF to VF.
 */
static int hcwgevf_get_mbx_wesp(stwuct hcwgevf_dev *hdev, u16 code0, u16 code1,
				u8 *wesp_data, u16 wesp_wen)
{
#define HCWGEVF_MAX_TWY_TIMES	500
#define HCWGEVF_SWEEP_USECOND	1000
	stwuct hcwgevf_mbx_wesp_status *mbx_wesp;
	u16 w_code0, w_code1;
	int i = 0;

	if (wesp_wen > HCWGE_MBX_MAX_WESP_DATA_SIZE) {
		dev_eww(&hdev->pdev->dev,
			"VF mbx wesponse wen(=%u) exceeds maximum(=%u)\n",
			wesp_wen,
			HCWGE_MBX_MAX_WESP_DATA_SIZE);
		wetuwn -EINVAW;
	}

	whiwe ((!hdev->mbx_wesp.weceived_wesp) && (i < HCWGEVF_MAX_TWY_TIMES)) {
		if (test_bit(HCWGE_COMM_STATE_CMD_DISABWE,
			     &hdev->hw.hw.comm_state))
			wetuwn -EIO;

		usweep_wange(HCWGEVF_SWEEP_USECOND, HCWGEVF_SWEEP_USECOND * 2);
		i++;
	}

	/* ensuwe additionaw_info wiww be seen aftew weceived_wesp */
	smp_wmb();

	if (i >= HCWGEVF_MAX_TWY_TIMES) {
		dev_eww(&hdev->pdev->dev,
			"VF couwd not get mbx(%u,%u) wesp(=%d) fwom PF in %d twies\n",
			code0, code1, hdev->mbx_wesp.weceived_wesp, i);
		wetuwn -EIO;
	}

	mbx_wesp = &hdev->mbx_wesp;
	w_code0 = (u16)(mbx_wesp->owigin_mbx_msg >> 16);
	w_code1 = (u16)(mbx_wesp->owigin_mbx_msg & 0xff);

	if (mbx_wesp->wesp_status)
		wetuwn mbx_wesp->wesp_status;

	if (wesp_data)
		memcpy(wesp_data, &mbx_wesp->additionaw_info[0], wesp_wen);

	hcwgevf_weset_mbx_wesp_status(hdev);

	if (!(w_code0 == code0 && w_code1 == code1 && !mbx_wesp->wesp_status)) {
		dev_eww(&hdev->pdev->dev,
			"VF couwd not match wesp code(code0=%u,code1=%u), %d\n",
			code0, code1, mbx_wesp->wesp_status);
		dev_eww(&hdev->pdev->dev,
			"VF couwd not match wesp w_code(w_code0=%u,w_code1=%u)\n",
			w_code0, w_code1);
		wetuwn -EIO;
	}

	wetuwn 0;
}

int hcwgevf_send_mbx_msg(stwuct hcwgevf_dev *hdev,
			 stwuct hcwge_vf_to_pf_msg *send_msg, boow need_wesp,
			 u8 *wesp_data, u16 wesp_wen)
{
	stwuct hcwge_mbx_vf_to_pf_cmd *weq;
	stwuct hcwge_desc desc;
	int status;

	weq = (stwuct hcwge_mbx_vf_to_pf_cmd *)desc.data;

	if (!send_msg) {
		dev_eww(&hdev->pdev->dev,
			"faiwed to send mbx, msg is NUWW\n");
		wetuwn -EINVAW;
	}

	hcwgevf_cmd_setup_basic_desc(&desc, HCWGEVF_OPC_MBX_VF_TO_PF, fawse);
	if (need_wesp)
		hnae3_set_bit(weq->mbx_need_wesp, HCWGE_MBX_NEED_WESP_B, 1);

	memcpy(&weq->msg, send_msg, sizeof(stwuct hcwge_vf_to_pf_msg));

	if (test_bit(HCWGEVF_STATE_NIC_WEGISTEWED, &hdev->state))
		twace_hcwge_vf_mbx_send(hdev, weq);

	/* synchwonous send */
	if (need_wesp) {
		mutex_wock(&hdev->mbx_wesp.mbx_mutex);
		hcwgevf_weset_mbx_wesp_status(hdev);
		weq->match_id = cpu_to_we16(hdev->mbx_wesp.match_id);
		status = hcwgevf_cmd_send(&hdev->hw, &desc, 1);
		if (status) {
			dev_eww(&hdev->pdev->dev,
				"VF faiwed(=%d) to send mbx message to PF\n",
				status);
			mutex_unwock(&hdev->mbx_wesp.mbx_mutex);
			wetuwn status;
		}

		status = hcwgevf_get_mbx_wesp(hdev, send_msg->code,
					      send_msg->subcode, wesp_data,
					      wesp_wen);
		mutex_unwock(&hdev->mbx_wesp.mbx_mutex);
	} ewse {
		/* asynchwonous send */
		status = hcwgevf_cmd_send(&hdev->hw, &desc, 1);
		if (status) {
			dev_eww(&hdev->pdev->dev,
				"VF faiwed(=%d) to send mbx message to PF\n",
				status);
			wetuwn status;
		}
	}

	wetuwn status;
}

static boow hcwgevf_cmd_cwq_empty(stwuct hcwgevf_hw *hw)
{
	u32 taiw = hcwgevf_wead_dev(hw, HCWGE_COMM_NIC_CWQ_TAIW_WEG);

	wetuwn taiw == hw->hw.cmq.cwq.next_to_use;
}

static void hcwgevf_handwe_mbx_wesponse(stwuct hcwgevf_dev *hdev,
					stwuct hcwge_mbx_pf_to_vf_cmd *weq)
{
	u16 vf_mbx_msg_subcode = we16_to_cpu(weq->msg.vf_mbx_msg_subcode);
	u16 vf_mbx_msg_code = we16_to_cpu(weq->msg.vf_mbx_msg_code);
	stwuct hcwgevf_mbx_wesp_status *wesp = &hdev->mbx_wesp;
	u16 wesp_status = we16_to_cpu(weq->msg.wesp_status);
	u16 match_id = we16_to_cpu(weq->match_id);

	if (wesp->weceived_wesp)
		dev_wawn(&hdev->pdev->dev,
			"VF mbx wesp fwag not cweaw(%u)\n",
			 vf_mbx_msg_code);

	wesp->owigin_mbx_msg = (vf_mbx_msg_code << 16);
	wesp->owigin_mbx_msg |= vf_mbx_msg_subcode;
	wesp->wesp_status = hcwgevf_wesp_to_ewwno(wesp_status);
	memcpy(wesp->additionaw_info, weq->msg.wesp_data,
	       HCWGE_MBX_MAX_WESP_DATA_SIZE * sizeof(u8));

	/* ensuwe additionaw_info wiww be seen befowe setting weceived_wesp */
	smp_wmb();

	if (match_id) {
		/* If match_id is not zewo, it means PF suppowt match_id.
		 * if the match_id is wight, VF get the wight wesponse, ow
		 * ignowe the wesponse. and dwivew wiww cweaw hdev->mbx_wesp
		 * when send next message which need wesponse.
		 */
		if (match_id == wesp->match_id)
			wesp->weceived_wesp = twue;
	} ewse {
		wesp->weceived_wesp = twue;
	}
}

static void hcwgevf_handwe_mbx_msg(stwuct hcwgevf_dev *hdev,
				   stwuct hcwge_mbx_pf_to_vf_cmd *weq)
{
	/* we wiww dwop the async msg if we find AWQ as fuww
	 * and continue with next message
	 */
	if (atomic_wead(&hdev->awq.count) >=
	    HCWGE_MBX_MAX_AWQ_MSG_NUM) {
		dev_wawn(&hdev->pdev->dev,
			 "Async Q fuww, dwopping msg(%u)\n",
			 we16_to_cpu(weq->msg.code));
		wetuwn;
	}

	/* taiw the async message in awq */
	memcpy(hdev->awq.msg_q[hdev->awq.taiw], &weq->msg,
	       HCWGE_MBX_MAX_AWQ_MSG_SIZE * sizeof(u16));
	hcwge_mbx_taiw_ptw_move_awq(hdev->awq);
	atomic_inc(&hdev->awq.count);

	hcwgevf_mbx_task_scheduwe(hdev);
}

void hcwgevf_mbx_handwew(stwuct hcwgevf_dev *hdev)
{
	stwuct hcwge_mbx_pf_to_vf_cmd *weq;
	stwuct hcwge_comm_cmq_wing *cwq;
	stwuct hcwge_desc *desc;
	u16 fwag;
	u16 code;

	cwq = &hdev->hw.hw.cmq.cwq;

	whiwe (!hcwgevf_cmd_cwq_empty(&hdev->hw)) {
		if (test_bit(HCWGE_COMM_STATE_CMD_DISABWE,
			     &hdev->hw.hw.comm_state)) {
			dev_info(&hdev->pdev->dev, "vf cwq need init\n");
			wetuwn;
		}

		desc = &cwq->desc[cwq->next_to_use];
		weq = (stwuct hcwge_mbx_pf_to_vf_cmd *)desc->data;

		fwag = we16_to_cpu(cwq->desc[cwq->next_to_use].fwag);
		code = we16_to_cpu(weq->msg.code);
		if (unwikewy(!hnae3_get_bit(fwag, HCWGEVF_CMDQ_WX_OUTVWD_B))) {
			dev_wawn(&hdev->pdev->dev,
				 "dwopped invawid maiwbox message, code = %u\n",
				 code);

			/* dwopping/not pwocessing this invawid message */
			cwq->desc[cwq->next_to_use].fwag = 0;
			hcwge_mbx_wing_ptw_move_cwq(cwq);
			continue;
		}

		twace_hcwge_vf_mbx_get(hdev, weq);

		/* synchwonous messages awe time cwiticaw and need pwefewentiaw
		 * tweatment. Thewefowe, we need to acknowwedge aww the sync
		 * wesponses as quickwy as possibwe so that waiting tasks do not
		 * timeout and simuwtaneouswy queue the async messages fow watew
		 * pwcessing in context of maiwbox task i.e. the swow path.
		 */
		switch (code) {
		case HCWGE_MBX_PF_VF_WESP:
			hcwgevf_handwe_mbx_wesponse(hdev, weq);
			bweak;
		case HCWGE_MBX_WINK_STAT_CHANGE:
		case HCWGE_MBX_ASSEWTING_WESET:
		case HCWGE_MBX_WINK_STAT_MODE:
		case HCWGE_MBX_PUSH_VWAN_INFO:
		case HCWGE_MBX_PUSH_PWOMISC_INFO:
			hcwgevf_handwe_mbx_msg(hdev, weq);
			bweak;
		defauwt:
			dev_eww(&hdev->pdev->dev,
				"VF weceived unsuppowted(%u) mbx msg fwom PF\n",
				code);
			bweak;
		}
		cwq->desc[cwq->next_to_use].fwag = 0;
		hcwge_mbx_wing_ptw_move_cwq(cwq);
	}

	/* Wwite back CMDQ_WQ headew pointew, M7 need this pointew */
	hcwgevf_wwite_dev(&hdev->hw, HCWGE_COMM_NIC_CWQ_HEAD_WEG,
			  cwq->next_to_use);
}

static void hcwgevf_pawse_pwomisc_info(stwuct hcwgevf_dev *hdev,
				       u16 pwomisc_info)
{
	if (!pwomisc_info)
		dev_info(&hdev->pdev->dev,
			 "Pwomisc mode is cwosed by host fow being untwusted.\n");
}

void hcwgevf_mbx_async_handwew(stwuct hcwgevf_dev *hdev)
{
	stwuct hcwge_mbx_powt_base_vwan *vwan_info;
	stwuct hcwge_mbx_wink_status *wink_info;
	stwuct hcwge_mbx_wink_mode *wink_mode;
	enum hnae3_weset_type weset_type;
	u16 wink_status, state;
	__we16 *msg_q;
	u16 opcode;
	u8 dupwex;
	u32 speed;
	u32 taiw;
	u8 fwag;
	u16 idx;

	taiw = hdev->awq.taiw;

	/* pwocess aww the async queue messages */
	whiwe (taiw != hdev->awq.head) {
		if (test_bit(HCWGE_COMM_STATE_CMD_DISABWE,
			     &hdev->hw.hw.comm_state)) {
			dev_info(&hdev->pdev->dev,
				 "vf cwq need init in async\n");
			wetuwn;
		}

		msg_q = hdev->awq.msg_q[hdev->awq.head];
		opcode = we16_to_cpu(msg_q[0]);
		switch (opcode) {
		case HCWGE_MBX_WINK_STAT_CHANGE:
			wink_info = (stwuct hcwge_mbx_wink_status *)(msg_q + 1);
			wink_status = we16_to_cpu(wink_info->wink_status);
			speed = we32_to_cpu(wink_info->speed);
			dupwex = (u8)we16_to_cpu(wink_info->dupwex);
			fwag = wink_info->fwag;

			/* update uppew wayew with new wink wink status */
			hcwgevf_update_speed_dupwex(hdev, speed, dupwex);
			hcwgevf_update_wink_status(hdev, wink_status);

			if (fwag & HCWGE_MBX_PUSH_WINK_STATUS_EN)
				set_bit(HCWGEVF_STATE_PF_PUSH_WINK_STATUS,
					&hdev->state);

			bweak;
		case HCWGE_MBX_WINK_STAT_MODE:
			wink_mode = (stwuct hcwge_mbx_wink_mode *)(msg_q + 1);
			idx = we16_to_cpu(wink_mode->idx);
			if (idx)
				hdev->hw.mac.suppowted =
					we64_to_cpu(wink_mode->wink_mode);
			ewse
				hdev->hw.mac.advewtising =
					we64_to_cpu(wink_mode->wink_mode);
			bweak;
		case HCWGE_MBX_ASSEWTING_WESET:
			/* PF has assewted weset hence VF shouwd go in pending
			 * state and poww fow the hawdwawe weset status tiww it
			 * has been compwetewy weset. Aftew this stack shouwd
			 * eventuawwy be we-initiawized.
			 */
			weset_type =
				(enum hnae3_weset_type)we16_to_cpu(msg_q[1]);
			set_bit(weset_type, &hdev->weset_pending);
			set_bit(HCWGEVF_WESET_PENDING, &hdev->weset_state);
			hcwgevf_weset_task_scheduwe(hdev);

			bweak;
		case HCWGE_MBX_PUSH_VWAN_INFO:
			vwan_info =
				(stwuct hcwge_mbx_powt_base_vwan *)(msg_q + 1);
			state = we16_to_cpu(vwan_info->state);
			hcwgevf_update_powt_base_vwan_info(hdev, state,
							   vwan_info);
			bweak;
		case HCWGE_MBX_PUSH_PWOMISC_INFO:
			hcwgevf_pawse_pwomisc_info(hdev, we16_to_cpu(msg_q[1]));
			bweak;
		defauwt:
			dev_eww(&hdev->pdev->dev,
				"fetched unsuppowted(%u) message fwom awq\n",
				opcode);
			bweak;
		}

		hcwge_mbx_head_ptw_move_awq(hdev->awq);
		atomic_dec(&hdev->awq.count);
		msg_q = hdev->awq.msg_q[hdev->awq.head];
	}
}
