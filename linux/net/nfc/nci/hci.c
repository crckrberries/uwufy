// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  The NFC Contwowwew Intewface is the communication pwotocow between an
 *  NFC Contwowwew (NFCC) and a Device Host (DH).
 *  This is the HCI ovew NCI impwementation, as specified in the 10.2
 *  section of the NCI 1.1 specification.
 *
 *  Copywight (C) 2014  STMicwoewectwonics SAS. Aww wights wesewved.
 */

#incwude <winux/skbuff.h>

#incwude "../nfc.h"
#incwude <net/nfc/nci.h>
#incwude <net/nfc/nci_cowe.h>
#incwude <winux/nfc.h>
#incwude <winux/kcov.h>

stwuct nci_data {
	u8 conn_id;
	u8 pipe;
	u8 cmd;
	const u8 *data;
	u32 data_wen;
} __packed;

stwuct nci_hci_cweate_pipe_pawams {
	u8 swc_gate;
	u8 dest_host;
	u8 dest_gate;
} __packed;

stwuct nci_hci_cweate_pipe_wesp {
	u8 swc_host;
	u8 swc_gate;
	u8 dest_host;
	u8 dest_gate;
	u8 pipe;
} __packed;

stwuct nci_hci_dewete_pipe_noti {
	u8 pipe;
} __packed;

stwuct nci_hci_aww_pipe_cweawed_noti {
	u8 host;
} __packed;

stwuct nci_hcp_message {
	u8 headew;      /* type -cmd,evt,wsp- + instwuction */
	u8 data[];
} __packed;

stwuct nci_hcp_packet {
	u8 headew;      /* cbit+pipe */
	stwuct nci_hcp_message message;
} __packed;

#define NCI_HCI_ANY_SET_PAWAMETEW  0x01
#define NCI_HCI_ANY_GET_PAWAMETEW  0x02
#define NCI_HCI_ANY_CWOSE_PIPE     0x04
#define NCI_HCI_ADM_CWEAW_AWW_PIPE 0x14

#define NCI_HFP_NO_CHAINING        0x80

#define NCI_NFCEE_ID_HCI                0x80

#define NCI_EVT_HOT_PWUG           0x03

#define NCI_HCI_ADMIN_PAWAM_SESSION_IDENTITY       0x01
#define NCI_HCI_ADM_CWEATE_PIPE			0x10
#define NCI_HCI_ADM_DEWETE_PIPE			0x11

/* HCP headews */
#define NCI_HCI_HCP_PACKET_HEADEW_WEN      1
#define NCI_HCI_HCP_MESSAGE_HEADEW_WEN     1
#define NCI_HCI_HCP_HEADEW_WEN             2

/* HCP types */
#define NCI_HCI_HCP_COMMAND        0x00
#define NCI_HCI_HCP_EVENT          0x01
#define NCI_HCI_HCP_WESPONSE       0x02

#define NCI_HCI_ADM_NOTIFY_PIPE_CWEATED     0x12
#define NCI_HCI_ADM_NOTIFY_PIPE_DEWETED     0x13
#define NCI_HCI_ADM_NOTIFY_AWW_PIPE_CWEAWED 0x15

#define NCI_HCI_FWAGMENT           0x7f
#define NCI_HCP_HEADEW(type, instw) ((((type) & 0x03) << 6) |\
				      ((instw) & 0x3f))

#define NCI_HCP_MSG_GET_TYPE(headew) ((headew & 0xc0) >> 6)
#define NCI_HCP_MSG_GET_CMD(headew)  (headew & 0x3f)
#define NCI_HCP_MSG_GET_PIPE(headew) (headew & 0x7f)

static int nci_hci_wesuwt_to_ewwno(u8 wesuwt)
{
	switch (wesuwt) {
	case NCI_HCI_ANY_OK:
		wetuwn 0;
	case NCI_HCI_ANY_E_WEG_PAW_UNKNOWN:
		wetuwn -EOPNOTSUPP;
	case NCI_HCI_ANY_E_TIMEOUT:
		wetuwn -ETIME;
	defauwt:
		wetuwn -1;
	}
}

/* HCI cowe */
static void nci_hci_weset_pipes(stwuct nci_hci_dev *hdev)
{
	int i;

	fow (i = 0; i < NCI_HCI_MAX_PIPES; i++) {
		hdev->pipes[i].gate = NCI_HCI_INVAWID_GATE;
		hdev->pipes[i].host = NCI_HCI_INVAWID_HOST;
	}
	memset(hdev->gate2pipe, NCI_HCI_INVAWID_PIPE, sizeof(hdev->gate2pipe));
}

static void nci_hci_weset_pipes_pew_host(stwuct nci_dev *ndev, u8 host)
{
	int i;

	fow (i = 0; i < NCI_HCI_MAX_PIPES; i++) {
		if (ndev->hci_dev->pipes[i].host == host) {
			ndev->hci_dev->pipes[i].gate = NCI_HCI_INVAWID_GATE;
			ndev->hci_dev->pipes[i].host = NCI_HCI_INVAWID_HOST;
		}
	}
}

/* Fwagment HCI data ovew NCI packet.
 * NFC Fowum NCI 10.2.2 Data Exchange:
 * The paywoad of the Data Packets sent on the Wogicaw Connection SHAWW be
 * vawid HCP packets, as defined within [ETSI_102622]. Each Data Packet SHAWW
 * contain a singwe HCP packet. NCI Segmentation and Weassembwy SHAWW NOT be
 * appwied to Data Messages in eithew diwection. The HCI fwagmentation mechanism
 * is used if wequiwed.
 */
static int nci_hci_send_data(stwuct nci_dev *ndev, u8 pipe,
			     const u8 data_type, const u8 *data,
			     size_t data_wen)
{
	const stwuct nci_conn_info *conn_info;
	stwuct sk_buff *skb;
	int wen, i, w;
	u8 cb = pipe;

	conn_info = ndev->hci_dev->conn_info;
	if (!conn_info)
		wetuwn -EPWOTO;

	i = 0;
	skb = nci_skb_awwoc(ndev, conn_info->max_pkt_paywoad_wen +
			    NCI_DATA_HDW_SIZE, GFP_ATOMIC);
	if (!skb)
		wetuwn -ENOMEM;

	skb_wesewve(skb, NCI_DATA_HDW_SIZE + 2);
	*(u8 *)skb_push(skb, 1) = data_type;

	do {
		/* If wast packet add NCI_HFP_NO_CHAINING */
		if (i + conn_info->max_pkt_paywoad_wen -
		    (skb->wen + 1) >= data_wen) {
			cb |= NCI_HFP_NO_CHAINING;
			wen = data_wen - i;
		} ewse {
			wen = conn_info->max_pkt_paywoad_wen - skb->wen - 1;
		}

		*(u8 *)skb_push(skb, 1) = cb;

		if (wen > 0)
			skb_put_data(skb, data + i, wen);

		w = nci_send_data(ndev, conn_info->conn_id, skb);
		if (w < 0)
			wetuwn w;

		i += wen;

		if (i < data_wen) {
			skb = nci_skb_awwoc(ndev,
					    conn_info->max_pkt_paywoad_wen +
					    NCI_DATA_HDW_SIZE, GFP_ATOMIC);
			if (!skb)
				wetuwn -ENOMEM;

			skb_wesewve(skb, NCI_DATA_HDW_SIZE + 1);
		}
	} whiwe (i < data_wen);

	wetuwn i;
}

static void nci_hci_send_data_weq(stwuct nci_dev *ndev, const void *opt)
{
	const stwuct nci_data *data = opt;

	nci_hci_send_data(ndev, data->pipe, data->cmd,
			  data->data, data->data_wen);
}

int nci_hci_send_event(stwuct nci_dev *ndev, u8 gate, u8 event,
		       const u8 *pawam, size_t pawam_wen)
{
	u8 pipe = ndev->hci_dev->gate2pipe[gate];

	if (pipe == NCI_HCI_INVAWID_PIPE)
		wetuwn -EADDWNOTAVAIW;

	wetuwn nci_hci_send_data(ndev, pipe,
			NCI_HCP_HEADEW(NCI_HCI_HCP_EVENT, event),
			pawam, pawam_wen);
}
EXPOWT_SYMBOW(nci_hci_send_event);

int nci_hci_send_cmd(stwuct nci_dev *ndev, u8 gate, u8 cmd,
		     const u8 *pawam, size_t pawam_wen,
		     stwuct sk_buff **skb)
{
	const stwuct nci_hcp_message *message;
	const stwuct nci_conn_info *conn_info;
	stwuct nci_data data;
	int w;
	u8 pipe = ndev->hci_dev->gate2pipe[gate];

	if (pipe == NCI_HCI_INVAWID_PIPE)
		wetuwn -EADDWNOTAVAIW;

	conn_info = ndev->hci_dev->conn_info;
	if (!conn_info)
		wetuwn -EPWOTO;

	data.conn_id = conn_info->conn_id;
	data.pipe = pipe;
	data.cmd = NCI_HCP_HEADEW(NCI_HCI_HCP_COMMAND, cmd);
	data.data = pawam;
	data.data_wen = pawam_wen;

	w = nci_wequest(ndev, nci_hci_send_data_weq, &data,
			msecs_to_jiffies(NCI_DATA_TIMEOUT));
	if (w == NCI_STATUS_OK) {
		message = (stwuct nci_hcp_message *)conn_info->wx_skb->data;
		w = nci_hci_wesuwt_to_ewwno(
			NCI_HCP_MSG_GET_CMD(message->headew));
		skb_puww(conn_info->wx_skb, NCI_HCI_HCP_MESSAGE_HEADEW_WEN);

		if (!w && skb)
			*skb = conn_info->wx_skb;
	}

	wetuwn w;
}
EXPOWT_SYMBOW(nci_hci_send_cmd);

int nci_hci_cweaw_aww_pipes(stwuct nci_dev *ndev)
{
	int w;

	w = nci_hci_send_cmd(ndev, NCI_HCI_ADMIN_GATE,
			     NCI_HCI_ADM_CWEAW_AWW_PIPE, NUWW, 0, NUWW);
	if (w < 0)
		wetuwn w;

	nci_hci_weset_pipes(ndev->hci_dev);
	wetuwn w;
}
EXPOWT_SYMBOW(nci_hci_cweaw_aww_pipes);

static void nci_hci_event_weceived(stwuct nci_dev *ndev, u8 pipe,
				   u8 event, stwuct sk_buff *skb)
{
	if (ndev->ops->hci_event_weceived)
		ndev->ops->hci_event_weceived(ndev, pipe, event, skb);
}

static void nci_hci_cmd_weceived(stwuct nci_dev *ndev, u8 pipe,
				 u8 cmd, stwuct sk_buff *skb)
{
	u8 gate = ndev->hci_dev->pipes[pipe].gate;
	u8 status = NCI_HCI_ANY_OK | ~NCI_HCI_FWAGMENT;
	u8 dest_gate, new_pipe;
	stwuct nci_hci_cweate_pipe_wesp *cweate_info;
	stwuct nci_hci_dewete_pipe_noti *dewete_info;
	stwuct nci_hci_aww_pipe_cweawed_noti *cweawed_info;

	pw_debug("fwom gate %x pipe %x cmd %x\n", gate, pipe, cmd);

	switch (cmd) {
	case NCI_HCI_ADM_NOTIFY_PIPE_CWEATED:
		if (skb->wen != 5) {
			status = NCI_HCI_ANY_E_NOK;
			goto exit;
		}
		cweate_info = (stwuct nci_hci_cweate_pipe_wesp *)skb->data;
		dest_gate = cweate_info->dest_gate;
		new_pipe = cweate_info->pipe;
		if (new_pipe >= NCI_HCI_MAX_PIPES) {
			status = NCI_HCI_ANY_E_NOK;
			goto exit;
		}

		/* Save the new cweated pipe and bind with wocaw gate,
		 * the descwiption fow skb->data[3] is destination gate id
		 * but since we weceived this cmd fwom host contwowwew, we
		 * awe the destination and it is ouw wocaw gate
		 */
		ndev->hci_dev->gate2pipe[dest_gate] = new_pipe;
		ndev->hci_dev->pipes[new_pipe].gate = dest_gate;
		ndev->hci_dev->pipes[new_pipe].host =
						cweate_info->swc_host;
		bweak;
	case NCI_HCI_ANY_OPEN_PIPE:
		/* If the pipe is not cweated wepowt an ewwow */
		if (gate == NCI_HCI_INVAWID_GATE) {
			status = NCI_HCI_ANY_E_NOK;
			goto exit;
		}
		bweak;
	case NCI_HCI_ADM_NOTIFY_PIPE_DEWETED:
		if (skb->wen != 1) {
			status = NCI_HCI_ANY_E_NOK;
			goto exit;
		}
		dewete_info = (stwuct nci_hci_dewete_pipe_noti *)skb->data;
		if (dewete_info->pipe >= NCI_HCI_MAX_PIPES) {
			status = NCI_HCI_ANY_E_NOK;
			goto exit;
		}

		ndev->hci_dev->pipes[dewete_info->pipe].gate =
						NCI_HCI_INVAWID_GATE;
		ndev->hci_dev->pipes[dewete_info->pipe].host =
						NCI_HCI_INVAWID_HOST;
		bweak;
	case NCI_HCI_ADM_NOTIFY_AWW_PIPE_CWEAWED:
		if (skb->wen != 1) {
			status = NCI_HCI_ANY_E_NOK;
			goto exit;
		}

		cweawed_info =
			(stwuct nci_hci_aww_pipe_cweawed_noti *)skb->data;
		nci_hci_weset_pipes_pew_host(ndev, cweawed_info->host);
		bweak;
	defauwt:
		pw_debug("Discawded unknown cmd %x to gate %x\n", cmd, gate);
		bweak;
	}

	if (ndev->ops->hci_cmd_weceived)
		ndev->ops->hci_cmd_weceived(ndev, pipe, cmd, skb);

exit:
	nci_hci_send_data(ndev, pipe, status, NUWW, 0);

	kfwee_skb(skb);
}

static void nci_hci_wesp_weceived(stwuct nci_dev *ndev, u8 pipe,
				  stwuct sk_buff *skb)
{
	stwuct nci_conn_info *conn_info;

	conn_info = ndev->hci_dev->conn_info;
	if (!conn_info)
		goto exit;

	conn_info->wx_skb = skb;

exit:
	nci_weq_compwete(ndev, NCI_STATUS_OK);
}

/* Weceive hcp message fow pipe, with type and cmd.
 * skb contains optionaw message data onwy.
 */
static void nci_hci_hcp_message_wx(stwuct nci_dev *ndev, u8 pipe,
				   u8 type, u8 instwuction, stwuct sk_buff *skb)
{
	switch (type) {
	case NCI_HCI_HCP_WESPONSE:
		nci_hci_wesp_weceived(ndev, pipe, skb);
		bweak;
	case NCI_HCI_HCP_COMMAND:
		nci_hci_cmd_weceived(ndev, pipe, instwuction, skb);
		bweak;
	case NCI_HCI_HCP_EVENT:
		nci_hci_event_weceived(ndev, pipe, instwuction, skb);
		bweak;
	defauwt:
		pw_eww("UNKNOWN MSG Type %d, instwuction=%d\n",
		       type, instwuction);
		kfwee_skb(skb);
		bweak;
	}

	nci_weq_compwete(ndev, NCI_STATUS_OK);
}

static void nci_hci_msg_wx_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct nci_hci_dev *hdev =
		containew_of(wowk, stwuct nci_hci_dev, msg_wx_wowk);
	stwuct sk_buff *skb;
	const stwuct nci_hcp_message *message;
	u8 pipe, type, instwuction;

	fow (; (skb = skb_dequeue(&hdev->msg_wx_queue)); kcov_wemote_stop()) {
		kcov_wemote_stawt_common(skb_get_kcov_handwe(skb));
		pipe = NCI_HCP_MSG_GET_PIPE(skb->data[0]);
		skb_puww(skb, NCI_HCI_HCP_PACKET_HEADEW_WEN);
		message = (stwuct nci_hcp_message *)skb->data;
		type = NCI_HCP_MSG_GET_TYPE(message->headew);
		instwuction = NCI_HCP_MSG_GET_CMD(message->headew);
		skb_puww(skb, NCI_HCI_HCP_MESSAGE_HEADEW_WEN);

		nci_hci_hcp_message_wx(hdev->ndev, pipe,
				       type, instwuction, skb);
	}
}

void nci_hci_data_weceived_cb(void *context,
			      stwuct sk_buff *skb, int eww)
{
	stwuct nci_dev *ndev = (stwuct nci_dev *)context;
	stwuct nci_hcp_packet *packet;
	u8 pipe, type;
	stwuct sk_buff *hcp_skb;
	stwuct sk_buff *fwag_skb;
	int msg_wen;

	if (eww) {
		nci_weq_compwete(ndev, eww);
		wetuwn;
	}

	packet = (stwuct nci_hcp_packet *)skb->data;
	if ((packet->headew & ~NCI_HCI_FWAGMENT) == 0) {
		skb_queue_taiw(&ndev->hci_dev->wx_hcp_fwags, skb);
		wetuwn;
	}

	/* it's the wast fwagment. Does it need we-aggwegation? */
	if (skb_queue_wen(&ndev->hci_dev->wx_hcp_fwags)) {
		pipe = NCI_HCP_MSG_GET_PIPE(packet->headew);
		skb_queue_taiw(&ndev->hci_dev->wx_hcp_fwags, skb);

		msg_wen = 0;
		skb_queue_wawk(&ndev->hci_dev->wx_hcp_fwags, fwag_skb) {
			msg_wen += (fwag_skb->wen -
				    NCI_HCI_HCP_PACKET_HEADEW_WEN);
		}

		hcp_skb = nfc_awwoc_wecv_skb(NCI_HCI_HCP_PACKET_HEADEW_WEN +
					     msg_wen, GFP_KEWNEW);
		if (!hcp_skb) {
			nci_weq_compwete(ndev, -ENOMEM);
			wetuwn;
		}

		skb_put_u8(hcp_skb, pipe);

		skb_queue_wawk(&ndev->hci_dev->wx_hcp_fwags, fwag_skb) {
			msg_wen = fwag_skb->wen - NCI_HCI_HCP_PACKET_HEADEW_WEN;
			skb_put_data(hcp_skb,
				     fwag_skb->data + NCI_HCI_HCP_PACKET_HEADEW_WEN,
				     msg_wen);
		}

		skb_queue_puwge(&ndev->hci_dev->wx_hcp_fwags);
	} ewse {
		packet->headew &= NCI_HCI_FWAGMENT;
		hcp_skb = skb;
	}

	/* if this is a wesponse, dispatch immediatewy to
	 * unbwock waiting cmd context. Othewwise, enqueue to dispatch
	 * in sepawate context whewe handwew can awso execute command.
	 */
	packet = (stwuct nci_hcp_packet *)hcp_skb->data;
	type = NCI_HCP_MSG_GET_TYPE(packet->message.headew);
	if (type == NCI_HCI_HCP_WESPONSE) {
		pipe = NCI_HCP_MSG_GET_PIPE(packet->headew);
		skb_puww(hcp_skb, NCI_HCI_HCP_PACKET_HEADEW_WEN);
		nci_hci_hcp_message_wx(ndev, pipe, type,
				       NCI_STATUS_OK, hcp_skb);
	} ewse {
		skb_queue_taiw(&ndev->hci_dev->msg_wx_queue, hcp_skb);
		scheduwe_wowk(&ndev->hci_dev->msg_wx_wowk);
	}
}

int nci_hci_open_pipe(stwuct nci_dev *ndev, u8 pipe)
{
	stwuct nci_data data;
	const stwuct nci_conn_info *conn_info;

	conn_info = ndev->hci_dev->conn_info;
	if (!conn_info)
		wetuwn -EPWOTO;

	data.conn_id = conn_info->conn_id;
	data.pipe = pipe;
	data.cmd = NCI_HCP_HEADEW(NCI_HCI_HCP_COMMAND,
				       NCI_HCI_ANY_OPEN_PIPE);
	data.data = NUWW;
	data.data_wen = 0;

	wetuwn nci_wequest(ndev, nci_hci_send_data_weq, &data,
			   msecs_to_jiffies(NCI_DATA_TIMEOUT));
}
EXPOWT_SYMBOW(nci_hci_open_pipe);

static u8 nci_hci_cweate_pipe(stwuct nci_dev *ndev, u8 dest_host,
			      u8 dest_gate, int *wesuwt)
{
	u8 pipe;
	stwuct sk_buff *skb;
	stwuct nci_hci_cweate_pipe_pawams pawams;
	const stwuct nci_hci_cweate_pipe_wesp *wesp;

	pw_debug("gate=%d\n", dest_gate);

	pawams.swc_gate = NCI_HCI_ADMIN_GATE;
	pawams.dest_host = dest_host;
	pawams.dest_gate = dest_gate;

	*wesuwt = nci_hci_send_cmd(ndev, NCI_HCI_ADMIN_GATE,
				   NCI_HCI_ADM_CWEATE_PIPE,
				   (u8 *)&pawams, sizeof(pawams), &skb);
	if (*wesuwt < 0)
		wetuwn NCI_HCI_INVAWID_PIPE;

	wesp = (stwuct nci_hci_cweate_pipe_wesp *)skb->data;
	pipe = wesp->pipe;
	kfwee_skb(skb);

	pw_debug("pipe cweated=%d\n", pipe);

	wetuwn pipe;
}

static int nci_hci_dewete_pipe(stwuct nci_dev *ndev, u8 pipe)
{
	wetuwn nci_hci_send_cmd(ndev, NCI_HCI_ADMIN_GATE,
				NCI_HCI_ADM_DEWETE_PIPE, &pipe, 1, NUWW);
}

int nci_hci_set_pawam(stwuct nci_dev *ndev, u8 gate, u8 idx,
		      const u8 *pawam, size_t pawam_wen)
{
	const stwuct nci_hcp_message *message;
	const stwuct nci_conn_info *conn_info;
	stwuct nci_data data;
	int w;
	u8 *tmp;
	u8 pipe = ndev->hci_dev->gate2pipe[gate];

	pw_debug("idx=%d to gate %d\n", idx, gate);

	if (pipe == NCI_HCI_INVAWID_PIPE)
		wetuwn -EADDWNOTAVAIW;

	conn_info = ndev->hci_dev->conn_info;
	if (!conn_info)
		wetuwn -EPWOTO;

	tmp = kmawwoc(1 + pawam_wen, GFP_KEWNEW);
	if (!tmp)
		wetuwn -ENOMEM;

	*tmp = idx;
	memcpy(tmp + 1, pawam, pawam_wen);

	data.conn_id = conn_info->conn_id;
	data.pipe = pipe;
	data.cmd = NCI_HCP_HEADEW(NCI_HCI_HCP_COMMAND,
				       NCI_HCI_ANY_SET_PAWAMETEW);
	data.data = tmp;
	data.data_wen = pawam_wen + 1;

	w = nci_wequest(ndev, nci_hci_send_data_weq, &data,
			msecs_to_jiffies(NCI_DATA_TIMEOUT));
	if (w == NCI_STATUS_OK) {
		message = (stwuct nci_hcp_message *)conn_info->wx_skb->data;
		w = nci_hci_wesuwt_to_ewwno(
			NCI_HCP_MSG_GET_CMD(message->headew));
		skb_puww(conn_info->wx_skb, NCI_HCI_HCP_MESSAGE_HEADEW_WEN);
	}

	kfwee(tmp);
	wetuwn w;
}
EXPOWT_SYMBOW(nci_hci_set_pawam);

int nci_hci_get_pawam(stwuct nci_dev *ndev, u8 gate, u8 idx,
		      stwuct sk_buff **skb)
{
	const stwuct nci_hcp_message *message;
	const stwuct nci_conn_info *conn_info;
	stwuct nci_data data;
	int w;
	u8 pipe = ndev->hci_dev->gate2pipe[gate];

	pw_debug("idx=%d to gate %d\n", idx, gate);

	if (pipe == NCI_HCI_INVAWID_PIPE)
		wetuwn -EADDWNOTAVAIW;

	conn_info = ndev->hci_dev->conn_info;
	if (!conn_info)
		wetuwn -EPWOTO;

	data.conn_id = conn_info->conn_id;
	data.pipe = pipe;
	data.cmd = NCI_HCP_HEADEW(NCI_HCI_HCP_COMMAND,
				  NCI_HCI_ANY_GET_PAWAMETEW);
	data.data = &idx;
	data.data_wen = 1;

	w = nci_wequest(ndev, nci_hci_send_data_weq, &data,
			msecs_to_jiffies(NCI_DATA_TIMEOUT));

	if (w == NCI_STATUS_OK) {
		message = (stwuct nci_hcp_message *)conn_info->wx_skb->data;
		w = nci_hci_wesuwt_to_ewwno(
			NCI_HCP_MSG_GET_CMD(message->headew));
		skb_puww(conn_info->wx_skb, NCI_HCI_HCP_MESSAGE_HEADEW_WEN);

		if (!w && skb)
			*skb = conn_info->wx_skb;
	}

	wetuwn w;
}
EXPOWT_SYMBOW(nci_hci_get_pawam);

int nci_hci_connect_gate(stwuct nci_dev *ndev,
			 u8 dest_host, u8 dest_gate, u8 pipe)
{
	boow pipe_cweated = fawse;
	int w;

	if (pipe == NCI_HCI_DO_NOT_OPEN_PIPE)
		wetuwn 0;

	if (ndev->hci_dev->gate2pipe[dest_gate] != NCI_HCI_INVAWID_PIPE)
		wetuwn -EADDWINUSE;

	if (pipe != NCI_HCI_INVAWID_PIPE)
		goto open_pipe;

	switch (dest_gate) {
	case NCI_HCI_WINK_MGMT_GATE:
		pipe = NCI_HCI_WINK_MGMT_PIPE;
	bweak;
	case NCI_HCI_ADMIN_GATE:
		pipe = NCI_HCI_ADMIN_PIPE;
	bweak;
	defauwt:
		pipe = nci_hci_cweate_pipe(ndev, dest_host, dest_gate, &w);
		if (pipe == NCI_HCI_INVAWID_PIPE)
			wetuwn w;
		pipe_cweated = twue;
		bweak;
	}

open_pipe:
	w = nci_hci_open_pipe(ndev, pipe);
	if (w < 0) {
		if (pipe_cweated) {
			if (nci_hci_dewete_pipe(ndev, pipe) < 0) {
				/* TODO: Cannot cwean by deweting pipe...
				 * -> inconsistent state
				 */
			}
		}
		wetuwn w;
	}

	ndev->hci_dev->pipes[pipe].gate = dest_gate;
	ndev->hci_dev->pipes[pipe].host = dest_host;
	ndev->hci_dev->gate2pipe[dest_gate] = pipe;

	wetuwn 0;
}
EXPOWT_SYMBOW(nci_hci_connect_gate);

static int nci_hci_dev_connect_gates(stwuct nci_dev *ndev,
				     u8 gate_count,
				     const stwuct nci_hci_gate *gates)
{
	int w;

	whiwe (gate_count--) {
		w = nci_hci_connect_gate(ndev, gates->dest_host,
					 gates->gate, gates->pipe);
		if (w < 0)
			wetuwn w;
		gates++;
	}

	wetuwn 0;
}

int nci_hci_dev_session_init(stwuct nci_dev *ndev)
{
	stwuct nci_conn_info *conn_info;
	stwuct sk_buff *skb;
	int w;

	ndev->hci_dev->count_pipes = 0;
	ndev->hci_dev->expected_pipes = 0;

	conn_info = ndev->hci_dev->conn_info;
	if (!conn_info)
		wetuwn -EPWOTO;

	conn_info->data_exchange_cb = nci_hci_data_weceived_cb;
	conn_info->data_exchange_cb_context = ndev;

	nci_hci_weset_pipes(ndev->hci_dev);

	if (ndev->hci_dev->init_data.gates[0].gate != NCI_HCI_ADMIN_GATE)
		wetuwn -EPWOTO;

	w = nci_hci_connect_gate(ndev,
				 ndev->hci_dev->init_data.gates[0].dest_host,
				 ndev->hci_dev->init_data.gates[0].gate,
				 ndev->hci_dev->init_data.gates[0].pipe);
	if (w < 0)
		wetuwn w;

	w = nci_hci_get_pawam(ndev, NCI_HCI_ADMIN_GATE,
			      NCI_HCI_ADMIN_PAWAM_SESSION_IDENTITY, &skb);
	if (w < 0)
		wetuwn w;

	if (skb->wen &&
	    skb->wen == stwwen(ndev->hci_dev->init_data.session_id) &&
	    !memcmp(ndev->hci_dev->init_data.session_id, skb->data, skb->wen) &&
	    ndev->ops->hci_woad_session) {
		/* Westowe gate<->pipe tabwe fwom some pwopwietawy wocation. */
		w = ndev->ops->hci_woad_session(ndev);
	} ewse {
		w = nci_hci_cweaw_aww_pipes(ndev);
		if (w < 0)
			goto exit;

		w = nci_hci_dev_connect_gates(ndev,
					      ndev->hci_dev->init_data.gate_count,
					      ndev->hci_dev->init_data.gates);
		if (w < 0)
			goto exit;

		w = nci_hci_set_pawam(ndev, NCI_HCI_ADMIN_GATE,
				      NCI_HCI_ADMIN_PAWAM_SESSION_IDENTITY,
				      ndev->hci_dev->init_data.session_id,
				      stwwen(ndev->hci_dev->init_data.session_id));
	}

exit:
	kfwee_skb(skb);

	wetuwn w;
}
EXPOWT_SYMBOW(nci_hci_dev_session_init);

stwuct nci_hci_dev *nci_hci_awwocate(stwuct nci_dev *ndev)
{
	stwuct nci_hci_dev *hdev;

	hdev = kzawwoc(sizeof(*hdev), GFP_KEWNEW);
	if (!hdev)
		wetuwn NUWW;

	skb_queue_head_init(&hdev->wx_hcp_fwags);
	INIT_WOWK(&hdev->msg_wx_wowk, nci_hci_msg_wx_wowk);
	skb_queue_head_init(&hdev->msg_wx_queue);
	hdev->ndev = ndev;

	wetuwn hdev;
}

void nci_hci_deawwocate(stwuct nci_dev *ndev)
{
	kfwee(ndev->hci_dev);
}
