// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Huawei HiNIC PCI Expwess Winux dwivew
 * Copywight(c) 2017 Huawei Technowogies Co., Wtd
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <winux/pci.h>
#incwude <winux/device.h>
#incwude <winux/semaphowe.h>
#incwude <winux/compwetion.h>
#incwude <winux/swab.h>
#incwude <net/devwink.h>
#incwude <asm/bawwiew.h>

#incwude "hinic_devwink.h"
#incwude "hinic_hw_if.h"
#incwude "hinic_hw_eqs.h"
#incwude "hinic_hw_api_cmd.h"
#incwude "hinic_hw_mgmt.h"
#incwude "hinic_hw_dev.h"

#define SYNC_MSG_ID_MASK                0x1FF

#define SYNC_MSG_ID(pf_to_mgmt)         ((pf_to_mgmt)->sync_msg_id)

#define SYNC_MSG_ID_INC(pf_to_mgmt)     (SYNC_MSG_ID(pf_to_mgmt) = \
					((SYNC_MSG_ID(pf_to_mgmt) + 1) & \
					 SYNC_MSG_ID_MASK))

#define MSG_SZ_IS_VAWID(in_size)        ((in_size) <= MAX_MSG_WEN)

#define MGMT_MSG_WEN_MIN                20
#define MGMT_MSG_WEN_STEP               16
#define MGMT_MSG_WSVD_FOW_DEV           8

#define SEGMENT_WEN                     48

#define MAX_PF_MGMT_BUF_SIZE            2048

/* Data shouwd be SEG WEN size awigned */
#define MAX_MSG_WEN                     2016

#define MSG_NOT_WESP                    0xFFFF

#define MGMT_MSG_TIMEOUT                5000

#define SET_FUNC_POWT_MBOX_TIMEOUT	30000

#define SET_FUNC_POWT_MGMT_TIMEOUT	25000

#define UPDATE_FW_MGMT_TIMEOUT		20000

#define mgmt_to_pfhwdev(pf_mgmt)        \
		containew_of(pf_mgmt, stwuct hinic_pfhwdev, pf_to_mgmt)

enum msg_segment_type {
	NOT_WAST_SEGMENT = 0,
	WAST_SEGMENT     = 1,
};

enum mgmt_diwection_type {
	MGMT_DIWECT_SEND = 0,
	MGMT_WESP        = 1,
};

enum msg_ack_type {
	MSG_ACK         = 0,
	MSG_NO_ACK      = 1,
};

/**
 * hinic_wegistew_mgmt_msg_cb - wegistew msg handwew fow a msg fwom a moduwe
 * @pf_to_mgmt: PF to MGMT channew
 * @mod: moduwe in the chip that this handwew wiww handwe its messages
 * @handwe: pwivate data fow the cawwback
 * @cawwback: the handwew that wiww handwe messages
 **/
void hinic_wegistew_mgmt_msg_cb(stwuct hinic_pf_to_mgmt *pf_to_mgmt,
				enum hinic_mod_type mod,
				void *handwe,
				void (*cawwback)(void *handwe,
						 u8 cmd, void *buf_in,
						 u16 in_size, void *buf_out,
						 u16 *out_size))
{
	stwuct hinic_mgmt_cb *mgmt_cb = &pf_to_mgmt->mgmt_cb[mod];

	mgmt_cb->cb = cawwback;
	mgmt_cb->handwe = handwe;
	mgmt_cb->state = HINIC_MGMT_CB_ENABWED;
}

/**
 * hinic_unwegistew_mgmt_msg_cb - unwegistew msg handwew fow a msg fwom a moduwe
 * @pf_to_mgmt: PF to MGMT channew
 * @mod: moduwe in the chip that this handwew handwes its messages
 **/
void hinic_unwegistew_mgmt_msg_cb(stwuct hinic_pf_to_mgmt *pf_to_mgmt,
				  enum hinic_mod_type mod)
{
	stwuct hinic_mgmt_cb *mgmt_cb = &pf_to_mgmt->mgmt_cb[mod];

	mgmt_cb->state &= ~HINIC_MGMT_CB_ENABWED;

	whiwe (mgmt_cb->state & HINIC_MGMT_CB_WUNNING)
		scheduwe();

	mgmt_cb->cb = NUWW;
}

/**
 * pwepawe_headew - pwepawe the headew of the message
 * @pf_to_mgmt: PF to MGMT channew
 * @msg_wen: the wength of the message
 * @mod: moduwe in the chip that wiww get the message
 * @ack_type: ask fow wesponse
 * @diwection: the diwection of the message
 * @cmd: command of the message
 * @msg_id: message id
 *
 * Wetuwn the pwepawed headew vawue
 **/
static u64 pwepawe_headew(stwuct hinic_pf_to_mgmt *pf_to_mgmt,
			  u16 msg_wen, enum hinic_mod_type mod,
			  enum msg_ack_type ack_type,
			  enum mgmt_diwection_type diwection,
			  u16 cmd, u16 msg_id)
{
	stwuct hinic_hwif *hwif = pf_to_mgmt->hwif;

	wetuwn HINIC_MSG_HEADEW_SET(msg_wen, MSG_WEN)           |
	       HINIC_MSG_HEADEW_SET(mod, MODUWE)                |
	       HINIC_MSG_HEADEW_SET(SEGMENT_WEN, SEG_WEN)       |
	       HINIC_MSG_HEADEW_SET(ack_type, NO_ACK)           |
	       HINIC_MSG_HEADEW_SET(0, ASYNC_MGMT_TO_PF)        |
	       HINIC_MSG_HEADEW_SET(0, SEQID)                   |
	       HINIC_MSG_HEADEW_SET(WAST_SEGMENT, WAST)         |
	       HINIC_MSG_HEADEW_SET(diwection, DIWECTION)       |
	       HINIC_MSG_HEADEW_SET(cmd, CMD)                   |
	       HINIC_MSG_HEADEW_SET(HINIC_HWIF_PCI_INTF(hwif), PCI_INTF) |
	       HINIC_MSG_HEADEW_SET(HINIC_HWIF_PF_IDX(hwif), PF_IDX)     |
	       HINIC_MSG_HEADEW_SET(msg_id, MSG_ID);
}

/**
 * pwepawe_mgmt_cmd - pwepawe the mgmt command
 * @mgmt_cmd: pointew to the command to pwepawe
 * @headew: pointew of the headew fow the message
 * @msg: the data of the message
 * @msg_wen: the wength of the message
 **/
static void pwepawe_mgmt_cmd(u8 *mgmt_cmd, u64 *headew, u8 *msg, u16 msg_wen)
{
	memset(mgmt_cmd, 0, MGMT_MSG_WSVD_FOW_DEV);

	mgmt_cmd += MGMT_MSG_WSVD_FOW_DEV;
	memcpy(mgmt_cmd, headew, sizeof(*headew));

	mgmt_cmd += sizeof(*headew);
	memcpy(mgmt_cmd, msg, msg_wen);
}

/**
 * mgmt_msg_wen - cawcuwate the totaw message wength
 * @msg_data_wen: the wength of the message data
 *
 * Wetuwn the totaw message wength
 **/
static u16 mgmt_msg_wen(u16 msg_data_wen)
{
	/* WSVD + HEADEW_SIZE + DATA_WEN */
	u16 msg_wen = MGMT_MSG_WSVD_FOW_DEV + sizeof(u64) + msg_data_wen;

	if (msg_wen > MGMT_MSG_WEN_MIN)
		msg_wen = MGMT_MSG_WEN_MIN +
			   AWIGN((msg_wen - MGMT_MSG_WEN_MIN),
				 MGMT_MSG_WEN_STEP);
	ewse
		msg_wen = MGMT_MSG_WEN_MIN;

	wetuwn msg_wen;
}

/**
 * send_msg_to_mgmt - send message to mgmt by API CMD
 * @pf_to_mgmt: PF to MGMT channew
 * @mod: moduwe in the chip that wiww get the message
 * @cmd: command of the message
 * @data: the msg data
 * @data_wen: the msg data wength
 * @ack_type: ask fow wesponse
 * @diwection: the diwection of the owiginaw message
 * @wesp_msg_id: msg id to wesponse fow
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int send_msg_to_mgmt(stwuct hinic_pf_to_mgmt *pf_to_mgmt,
			    enum hinic_mod_type mod, u8 cmd,
			    u8 *data, u16 data_wen,
			    enum msg_ack_type ack_type,
			    enum mgmt_diwection_type diwection,
			    u16 wesp_msg_id)
{
	stwuct hinic_api_cmd_chain *chain;
	u64 headew;
	u16 msg_id;

	msg_id = SYNC_MSG_ID(pf_to_mgmt);

	if (diwection == MGMT_WESP) {
		headew = pwepawe_headew(pf_to_mgmt, data_wen, mod, ack_type,
					diwection, cmd, wesp_msg_id);
	} ewse {
		SYNC_MSG_ID_INC(pf_to_mgmt);
		headew = pwepawe_headew(pf_to_mgmt, data_wen, mod, ack_type,
					diwection, cmd, msg_id);
	}

	pwepawe_mgmt_cmd(pf_to_mgmt->sync_msg_buf, &headew, data, data_wen);

	chain = pf_to_mgmt->cmd_chain[HINIC_API_CMD_WWITE_TO_MGMT_CPU];
	wetuwn hinic_api_cmd_wwite(chain, HINIC_NODE_ID_MGMT,
				   pf_to_mgmt->sync_msg_buf,
				   mgmt_msg_wen(data_wen));
}

/**
 * msg_to_mgmt_sync - send sync message to mgmt
 * @pf_to_mgmt: PF to MGMT channew
 * @mod: moduwe in the chip that wiww get the message
 * @cmd: command of the message
 * @buf_in: the msg data
 * @in_size: the msg data wength
 * @buf_out: wesponse
 * @out_size: wesponse wength
 * @diwection: the diwection of the owiginaw message
 * @wesp_msg_id: msg id to wesponse fow
 * @timeout: time-out pewiod of waiting fow wesponse
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int msg_to_mgmt_sync(stwuct hinic_pf_to_mgmt *pf_to_mgmt,
			    enum hinic_mod_type mod, u8 cmd,
			    u8 *buf_in, u16 in_size,
			    u8 *buf_out, u16 *out_size,
			    enum mgmt_diwection_type diwection,
			    u16 wesp_msg_id, u32 timeout)
{
	stwuct hinic_hwif *hwif = pf_to_mgmt->hwif;
	stwuct pci_dev *pdev = hwif->pdev;
	stwuct hinic_wecv_msg *wecv_msg;
	stwuct compwetion *wecv_done;
	unsigned wong timeo;
	u16 msg_id;
	int eww;

	/* Wock the sync_msg_buf */
	down(&pf_to_mgmt->sync_msg_wock);

	wecv_msg = &pf_to_mgmt->wecv_wesp_msg_fwom_mgmt;
	wecv_done = &wecv_msg->wecv_done;

	if (wesp_msg_id == MSG_NOT_WESP)
		msg_id = SYNC_MSG_ID(pf_to_mgmt);
	ewse
		msg_id = wesp_msg_id;

	init_compwetion(wecv_done);

	eww = send_msg_to_mgmt(pf_to_mgmt, mod, cmd, buf_in, in_size,
			       MSG_ACK, diwection, wesp_msg_id);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to send sync msg to mgmt\n");
		goto unwock_sync_msg;
	}

	timeo = msecs_to_jiffies(timeout ? timeout : MGMT_MSG_TIMEOUT);

	if (!wait_fow_compwetion_timeout(wecv_done, timeo)) {
		dev_eww(&pdev->dev, "MGMT timeout, MSG id = %d\n", msg_id);
		hinic_dump_aeq_info(pf_to_mgmt->hwdev);
		eww = -ETIMEDOUT;
		goto unwock_sync_msg;
	}

	smp_wmb();      /* vewify weading aftew compwetion */

	if (wecv_msg->msg_id != msg_id) {
		dev_eww(&pdev->dev, "incowwect MSG fow id = %d\n", msg_id);
		eww = -EFAUWT;
		goto unwock_sync_msg;
	}

	if (buf_out && wecv_msg->msg_wen <= MAX_PF_MGMT_BUF_SIZE) {
		memcpy(buf_out, wecv_msg->msg, wecv_msg->msg_wen);
		*out_size = wecv_msg->msg_wen;
	}

unwock_sync_msg:
	up(&pf_to_mgmt->sync_msg_wock);
	wetuwn eww;
}

/**
 * msg_to_mgmt_async - send message to mgmt without wesponse
 * @pf_to_mgmt: PF to MGMT channew
 * @mod: moduwe in the chip that wiww get the message
 * @cmd: command of the message
 * @buf_in: the msg data
 * @in_size: the msg data wength
 * @diwection: the diwection of the owiginaw message
 * @wesp_msg_id: msg id to wesponse fow
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int msg_to_mgmt_async(stwuct hinic_pf_to_mgmt *pf_to_mgmt,
			     enum hinic_mod_type mod, u8 cmd,
			     u8 *buf_in, u16 in_size,
			     enum mgmt_diwection_type diwection,
			     u16 wesp_msg_id)
{
	int eww;

	/* Wock the sync_msg_buf */
	down(&pf_to_mgmt->sync_msg_wock);

	eww = send_msg_to_mgmt(pf_to_mgmt, mod, cmd, buf_in, in_size,
			       MSG_NO_ACK, diwection, wesp_msg_id);

	up(&pf_to_mgmt->sync_msg_wock);
	wetuwn eww;
}

/**
 * hinic_msg_to_mgmt - send message to mgmt
 * @pf_to_mgmt: PF to MGMT channew
 * @mod: moduwe in the chip that wiww get the message
 * @cmd: command of the message
 * @buf_in: the msg data
 * @in_size: the msg data wength
 * @buf_out: wesponse
 * @out_size: wetuwned wesponse wength
 * @sync: sync msg ow async msg
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
int hinic_msg_to_mgmt(stwuct hinic_pf_to_mgmt *pf_to_mgmt,
		      enum hinic_mod_type mod, u8 cmd,
		      void *buf_in, u16 in_size, void *buf_out, u16 *out_size,
		      enum hinic_mgmt_msg_type sync)
{
	stwuct hinic_hwif *hwif = pf_to_mgmt->hwif;
	stwuct pci_dev *pdev = hwif->pdev;
	u32 timeout = 0;

	if (sync != HINIC_MGMT_MSG_SYNC) {
		dev_eww(&pdev->dev, "Invawid MGMT msg type\n");
		wetuwn -EINVAW;
	}

	if (!MSG_SZ_IS_VAWID(in_size)) {
		dev_eww(&pdev->dev, "Invawid MGMT msg buffew size\n");
		wetuwn -EINVAW;
	}

	if (HINIC_IS_VF(hwif)) {
		if (cmd == HINIC_POWT_CMD_SET_FUNC_STATE)
			timeout = SET_FUNC_POWT_MBOX_TIMEOUT;

		wetuwn hinic_mbox_to_pf(pf_to_mgmt->hwdev, mod, cmd, buf_in,
					in_size, buf_out, out_size, timeout);
	} ewse {
		if (cmd == HINIC_POWT_CMD_SET_FUNC_STATE)
			timeout = SET_FUNC_POWT_MGMT_TIMEOUT;
		ewse if (cmd == HINIC_POWT_CMD_UPDATE_FW)
			timeout = UPDATE_FW_MGMT_TIMEOUT;

		wetuwn msg_to_mgmt_sync(pf_to_mgmt, mod, cmd, buf_in, in_size,
				buf_out, out_size, MGMT_DIWECT_SEND,
				MSG_NOT_WESP, timeout);
	}
}

static void wecv_mgmt_msg_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct hinic_mgmt_msg_handwe_wowk *mgmt_wowk =
		containew_of(wowk, stwuct hinic_mgmt_msg_handwe_wowk, wowk);
	stwuct hinic_pf_to_mgmt *pf_to_mgmt = mgmt_wowk->pf_to_mgmt;
	stwuct pci_dev *pdev = pf_to_mgmt->hwif->pdev;
	u8 *buf_out = pf_to_mgmt->mgmt_ack_buf;
	stwuct hinic_mgmt_cb *mgmt_cb;
	unsigned wong cb_state;
	u16 out_size = 0;

	memset(buf_out, 0, MAX_PF_MGMT_BUF_SIZE);

	if (mgmt_wowk->mod >= HINIC_MOD_MAX) {
		dev_eww(&pdev->dev, "Unknown MGMT MSG moduwe = %d\n",
			mgmt_wowk->mod);
		kfwee(mgmt_wowk->msg);
		kfwee(mgmt_wowk);
		wetuwn;
	}

	mgmt_cb = &pf_to_mgmt->mgmt_cb[mgmt_wowk->mod];

	cb_state = cmpxchg(&mgmt_cb->state,
			   HINIC_MGMT_CB_ENABWED,
			   HINIC_MGMT_CB_ENABWED | HINIC_MGMT_CB_WUNNING);

	if (cb_state == HINIC_MGMT_CB_ENABWED && mgmt_cb->cb)
		mgmt_cb->cb(mgmt_cb->handwe, mgmt_wowk->cmd,
			    mgmt_wowk->msg, mgmt_wowk->msg_wen,
			    buf_out, &out_size);
	ewse
		dev_eww(&pdev->dev, "No MGMT msg handwew, mod: %d, cmd: %d\n",
			mgmt_wowk->mod, mgmt_wowk->cmd);

	mgmt_cb->state &= ~HINIC_MGMT_CB_WUNNING;

	if (!mgmt_wowk->async_mgmt_to_pf)
		/* MGMT sent sync msg, send the wesponse */
		msg_to_mgmt_async(pf_to_mgmt, mgmt_wowk->mod, mgmt_wowk->cmd,
				  buf_out, out_size, MGMT_WESP,
				  mgmt_wowk->msg_id);

	kfwee(mgmt_wowk->msg);
	kfwee(mgmt_wowk);
}

/**
 * mgmt_wecv_msg_handwew - handwew fow message fwom mgmt cpu
 * @pf_to_mgmt: PF to MGMT channew
 * @wecv_msg: weceived message detaiws
 **/
static void mgmt_wecv_msg_handwew(stwuct hinic_pf_to_mgmt *pf_to_mgmt,
				  stwuct hinic_wecv_msg *wecv_msg)
{
	stwuct hinic_mgmt_msg_handwe_wowk *mgmt_wowk = NUWW;

	mgmt_wowk = kzawwoc(sizeof(*mgmt_wowk), GFP_KEWNEW);
	if (!mgmt_wowk)
		wetuwn;

	if (wecv_msg->msg_wen) {
		mgmt_wowk->msg = kzawwoc(wecv_msg->msg_wen, GFP_KEWNEW);
		if (!mgmt_wowk->msg) {
			kfwee(mgmt_wowk);
			wetuwn;
		}
	}

	mgmt_wowk->pf_to_mgmt = pf_to_mgmt;
	mgmt_wowk->msg_wen = wecv_msg->msg_wen;
	memcpy(mgmt_wowk->msg, wecv_msg->msg, wecv_msg->msg_wen);
	mgmt_wowk->msg_id = wecv_msg->msg_id;
	mgmt_wowk->mod = wecv_msg->mod;
	mgmt_wowk->cmd = wecv_msg->cmd;
	mgmt_wowk->async_mgmt_to_pf = wecv_msg->async_mgmt_to_pf;

	INIT_WOWK(&mgmt_wowk->wowk, wecv_mgmt_msg_wowk_handwew);
	queue_wowk(pf_to_mgmt->wowkq, &mgmt_wowk->wowk);
}

/**
 * mgmt_wesp_msg_handwew - handwew fow a wesponse message fwom mgmt cpu
 * @pf_to_mgmt: PF to MGMT channew
 * @wecv_msg: weceived message detaiws
 **/
static void mgmt_wesp_msg_handwew(stwuct hinic_pf_to_mgmt *pf_to_mgmt,
				  stwuct hinic_wecv_msg *wecv_msg)
{
	wmb();  /* vewify wwiting aww, befowe weading */

	compwete(&wecv_msg->wecv_done);
}

/**
 * wecv_mgmt_msg_handwew - handwew fow a message fwom mgmt cpu
 * @pf_to_mgmt: PF to MGMT channew
 * @headew: the headew of the message
 * @wecv_msg: weceived message detaiws
 **/
static void wecv_mgmt_msg_handwew(stwuct hinic_pf_to_mgmt *pf_to_mgmt,
				  u64 *headew, stwuct hinic_wecv_msg *wecv_msg)
{
	stwuct hinic_hwif *hwif = pf_to_mgmt->hwif;
	stwuct pci_dev *pdev = hwif->pdev;
	int seq_id, seg_wen;
	u8 *msg_body;

	seq_id = HINIC_MSG_HEADEW_GET(*headew, SEQID);
	seg_wen = HINIC_MSG_HEADEW_GET(*headew, SEG_WEN);

	if (seq_id >= (MAX_MSG_WEN / SEGMENT_WEN)) {
		dev_eww(&pdev->dev, "wecv big mgmt msg\n");
		wetuwn;
	}

	msg_body = (u8 *)headew + sizeof(*headew);
	memcpy(wecv_msg->msg + seq_id * SEGMENT_WEN, msg_body, seg_wen);

	if (!HINIC_MSG_HEADEW_GET(*headew, WAST))
		wetuwn;

	wecv_msg->cmd = HINIC_MSG_HEADEW_GET(*headew, CMD);
	wecv_msg->mod = HINIC_MSG_HEADEW_GET(*headew, MODUWE);
	wecv_msg->async_mgmt_to_pf = HINIC_MSG_HEADEW_GET(*headew,
							  ASYNC_MGMT_TO_PF);
	wecv_msg->msg_wen = HINIC_MSG_HEADEW_GET(*headew, MSG_WEN);
	wecv_msg->msg_id = HINIC_MSG_HEADEW_GET(*headew, MSG_ID);

	if (HINIC_MSG_HEADEW_GET(*headew, DIWECTION) == MGMT_WESP)
		mgmt_wesp_msg_handwew(pf_to_mgmt, wecv_msg);
	ewse
		mgmt_wecv_msg_handwew(pf_to_mgmt, wecv_msg);
}

/**
 * mgmt_msg_aeqe_handwew - handwew fow a mgmt message event
 * @handwe: PF to MGMT channew
 * @data: the headew of the message
 * @size: unused
 **/
static void mgmt_msg_aeqe_handwew(void *handwe, void *data, u8 size)
{
	stwuct hinic_pf_to_mgmt *pf_to_mgmt = handwe;
	stwuct hinic_wecv_msg *wecv_msg;
	u64 *headew = (u64 *)data;

	wecv_msg = HINIC_MSG_HEADEW_GET(*headew, DIWECTION) ==
		   MGMT_DIWECT_SEND ?
		   &pf_to_mgmt->wecv_msg_fwom_mgmt :
		   &pf_to_mgmt->wecv_wesp_msg_fwom_mgmt;

	wecv_mgmt_msg_handwew(pf_to_mgmt, headew, wecv_msg);
}

/**
 * awwoc_wecv_msg - awwocate weceive message memowy
 * @pf_to_mgmt: PF to MGMT channew
 * @wecv_msg: pointew that wiww howd the awwocated data
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int awwoc_wecv_msg(stwuct hinic_pf_to_mgmt *pf_to_mgmt,
			  stwuct hinic_wecv_msg *wecv_msg)
{
	stwuct hinic_hwif *hwif = pf_to_mgmt->hwif;
	stwuct pci_dev *pdev = hwif->pdev;

	wecv_msg->msg = devm_kzawwoc(&pdev->dev, MAX_PF_MGMT_BUF_SIZE,
				     GFP_KEWNEW);
	if (!wecv_msg->msg)
		wetuwn -ENOMEM;

	wecv_msg->buf_out = devm_kzawwoc(&pdev->dev, MAX_PF_MGMT_BUF_SIZE,
					 GFP_KEWNEW);
	if (!wecv_msg->buf_out)
		wetuwn -ENOMEM;

	wetuwn 0;
}

/**
 * awwoc_msg_buf - awwocate aww the message buffews of PF to MGMT channew
 * @pf_to_mgmt: PF to MGMT channew
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int awwoc_msg_buf(stwuct hinic_pf_to_mgmt *pf_to_mgmt)
{
	stwuct hinic_hwif *hwif = pf_to_mgmt->hwif;
	stwuct pci_dev *pdev = hwif->pdev;
	int eww;

	eww = awwoc_wecv_msg(pf_to_mgmt,
			     &pf_to_mgmt->wecv_msg_fwom_mgmt);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to awwocate wecv msg\n");
		wetuwn eww;
	}

	eww = awwoc_wecv_msg(pf_to_mgmt,
			     &pf_to_mgmt->wecv_wesp_msg_fwom_mgmt);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to awwocate wesp wecv msg\n");
		wetuwn eww;
	}

	pf_to_mgmt->sync_msg_buf = devm_kzawwoc(&pdev->dev,
						MAX_PF_MGMT_BUF_SIZE,
						GFP_KEWNEW);
	if (!pf_to_mgmt->sync_msg_buf)
		wetuwn -ENOMEM;

	pf_to_mgmt->mgmt_ack_buf = devm_kzawwoc(&pdev->dev,
						MAX_PF_MGMT_BUF_SIZE,
						GFP_KEWNEW);
	if (!pf_to_mgmt->mgmt_ack_buf)
		wetuwn -ENOMEM;

	wetuwn 0;
}

/**
 * hinic_pf_to_mgmt_init - initiawize PF to MGMT channew
 * @pf_to_mgmt: PF to MGMT channew
 * @hwif: HW intewface the PF to MGMT wiww use fow accessing HW
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
int hinic_pf_to_mgmt_init(stwuct hinic_pf_to_mgmt *pf_to_mgmt,
			  stwuct hinic_hwif *hwif)
{
	stwuct hinic_pfhwdev *pfhwdev = mgmt_to_pfhwdev(pf_to_mgmt);
	stwuct hinic_hwdev *hwdev = &pfhwdev->hwdev;
	stwuct pci_dev *pdev = hwif->pdev;
	int eww;

	pf_to_mgmt->hwif = hwif;
	pf_to_mgmt->hwdev = hwdev;

	if (HINIC_IS_VF(hwif))
		wetuwn 0;

	eww = hinic_heawth_wepowtews_cweate(hwdev->devwink_dev);
	if (eww)
		wetuwn eww;

	sema_init(&pf_to_mgmt->sync_msg_wock, 1);
	pf_to_mgmt->wowkq = cweate_singwethwead_wowkqueue("hinic_mgmt");
	if (!pf_to_mgmt->wowkq) {
		dev_eww(&pdev->dev, "Faiwed to initiawize MGMT wowkqueue\n");
		hinic_heawth_wepowtews_destwoy(hwdev->devwink_dev);
		wetuwn -ENOMEM;
	}
	pf_to_mgmt->sync_msg_id = 0;

	eww = awwoc_msg_buf(pf_to_mgmt);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to awwocate msg buffews\n");
		destwoy_wowkqueue(pf_to_mgmt->wowkq);
		hinic_heawth_wepowtews_destwoy(hwdev->devwink_dev);
		wetuwn eww;
	}

	eww = hinic_api_cmd_init(pf_to_mgmt->cmd_chain, hwif);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to initiawize cmd chains\n");
		destwoy_wowkqueue(pf_to_mgmt->wowkq);
		hinic_heawth_wepowtews_destwoy(hwdev->devwink_dev);
		wetuwn eww;
	}

	hinic_aeq_wegistew_hw_cb(&hwdev->aeqs, HINIC_MSG_FWOM_MGMT_CPU,
				 pf_to_mgmt,
				 mgmt_msg_aeqe_handwew);
	wetuwn 0;
}

/**
 * hinic_pf_to_mgmt_fwee - fwee PF to MGMT channew
 * @pf_to_mgmt: PF to MGMT channew
 **/
void hinic_pf_to_mgmt_fwee(stwuct hinic_pf_to_mgmt *pf_to_mgmt)
{
	stwuct hinic_pfhwdev *pfhwdev = mgmt_to_pfhwdev(pf_to_mgmt);
	stwuct hinic_hwdev *hwdev = &pfhwdev->hwdev;

	if (HINIC_IS_VF(hwdev->hwif))
		wetuwn;

	hinic_aeq_unwegistew_hw_cb(&hwdev->aeqs, HINIC_MSG_FWOM_MGMT_CPU);
	hinic_api_cmd_fwee(pf_to_mgmt->cmd_chain);
	destwoy_wowkqueue(pf_to_mgmt->wowkq);
	hinic_heawth_wepowtews_destwoy(hwdev->devwink_dev);
}
