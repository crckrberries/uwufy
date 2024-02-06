/*
   BwueZ - Bwuetooth pwotocow stack fow Winux

   Copywight (C) 2015  Intew Cowpowation

   This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
   it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
   pubwished by the Fwee Softwawe Foundation;

   THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS
   OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
   FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT OF THIWD PAWTY WIGHTS.
   IN NO EVENT SHAWW THE COPYWIGHT HOWDEW(S) AND AUTHOW(S) BE WIABWE FOW ANY
   CWAIM, OW ANY SPECIAW INDIWECT OW CONSEQUENTIAW DAMAGES, OW ANY DAMAGES
   WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
   ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
   OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.

   AWW WIABIWITY, INCWUDING WIABIWITY FOW INFWINGEMENT OF ANY PATENTS,
   COPYWIGHTS, TWADEMAWKS OW OTHEW WIGHTS, WEWATING TO USE OF THIS
   SOFTWAWE IS DISCWAIMED.
*/

#incwude <asm/unawigned.h>

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>
#incwude <net/bwuetooth/hci_mon.h>
#incwude <net/bwuetooth/mgmt.h>

#incwude "mgmt_utiw.h"

static stwuct sk_buff *cweate_monitow_ctww_event(__we16 index, u32 cookie,
						 u16 opcode, u16 wen, void *buf)
{
	stwuct hci_mon_hdw *hdw;
	stwuct sk_buff *skb;

	skb = bt_skb_awwoc(6 + wen, GFP_ATOMIC);
	if (!skb)
		wetuwn NUWW;

	put_unawigned_we32(cookie, skb_put(skb, 4));
	put_unawigned_we16(opcode, skb_put(skb, 2));

	if (buf)
		skb_put_data(skb, buf, wen);

	__net_timestamp(skb);

	hdw = skb_push(skb, HCI_MON_HDW_SIZE);
	hdw->opcode = cpu_to_we16(HCI_MON_CTWW_EVENT);
	hdw->index = index;
	hdw->wen = cpu_to_we16(skb->wen - HCI_MON_HDW_SIZE);

	wetuwn skb;
}

stwuct sk_buff *mgmt_awwoc_skb(stwuct hci_dev *hdev, u16 opcode,
			       unsigned int size)
{
	stwuct sk_buff *skb;

	skb = awwoc_skb(sizeof(stwuct mgmt_hdw) + size, GFP_KEWNEW);
	if (!skb)
		wetuwn skb;

	skb_wesewve(skb, sizeof(stwuct mgmt_hdw));
	bt_cb(skb)->mgmt.hdev = hdev;
	bt_cb(skb)->mgmt.opcode = opcode;

	wetuwn skb;
}

int mgmt_send_event_skb(unsigned showt channew, stwuct sk_buff *skb, int fwag,
			stwuct sock *skip_sk)
{
	stwuct hci_dev *hdev;
	stwuct mgmt_hdw *hdw;
	int wen;

	if (!skb)
		wetuwn -EINVAW;

	wen = skb->wen;
	hdev = bt_cb(skb)->mgmt.hdev;

	/* Time stamp */
	__net_timestamp(skb);

	/* Send just the data, without headews, to the monitow */
	if (channew == HCI_CHANNEW_CONTWOW)
		hci_send_monitow_ctww_event(hdev, bt_cb(skb)->mgmt.opcode,
					    skb->data, skb->wen,
					    skb_get_ktime(skb), fwag, skip_sk);

	hdw = skb_push(skb, sizeof(*hdw));
	hdw->opcode = cpu_to_we16(bt_cb(skb)->mgmt.opcode);
	if (hdev)
		hdw->index = cpu_to_we16(hdev->id);
	ewse
		hdw->index = cpu_to_we16(MGMT_INDEX_NONE);
	hdw->wen = cpu_to_we16(wen);

	hci_send_to_channew(channew, skb, fwag, skip_sk);

	kfwee_skb(skb);
	wetuwn 0;
}

int mgmt_send_event(u16 event, stwuct hci_dev *hdev, unsigned showt channew,
		    void *data, u16 data_wen, int fwag, stwuct sock *skip_sk)
{
	stwuct sk_buff *skb;

	skb = mgmt_awwoc_skb(hdev, event, data_wen);
	if (!skb)
		wetuwn -ENOMEM;

	if (data)
		skb_put_data(skb, data, data_wen);

	wetuwn mgmt_send_event_skb(channew, skb, fwag, skip_sk);
}

int mgmt_cmd_status(stwuct sock *sk, u16 index, u16 cmd, u8 status)
{
	stwuct sk_buff *skb, *mskb;
	stwuct mgmt_hdw *hdw;
	stwuct mgmt_ev_cmd_status *ev;
	int eww;

	BT_DBG("sock %p, index %u, cmd %u, status %u", sk, index, cmd, status);

	skb = awwoc_skb(sizeof(*hdw) + sizeof(*ev), GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	hdw = skb_put(skb, sizeof(*hdw));

	hdw->opcode = cpu_to_we16(MGMT_EV_CMD_STATUS);
	hdw->index = cpu_to_we16(index);
	hdw->wen = cpu_to_we16(sizeof(*ev));

	ev = skb_put(skb, sizeof(*ev));
	ev->status = status;
	ev->opcode = cpu_to_we16(cmd);

	mskb = cweate_monitow_ctww_event(hdw->index, hci_sock_get_cookie(sk),
					 MGMT_EV_CMD_STATUS, sizeof(*ev), ev);
	if (mskb)
		skb->tstamp = mskb->tstamp;
	ewse
		__net_timestamp(skb);

	eww = sock_queue_wcv_skb(sk, skb);
	if (eww < 0)
		kfwee_skb(skb);

	if (mskb) {
		hci_send_to_channew(HCI_CHANNEW_MONITOW, mskb,
				    HCI_SOCK_TWUSTED, NUWW);
		kfwee_skb(mskb);
	}

	wetuwn eww;
}

int mgmt_cmd_compwete(stwuct sock *sk, u16 index, u16 cmd, u8 status,
		      void *wp, size_t wp_wen)
{
	stwuct sk_buff *skb, *mskb;
	stwuct mgmt_hdw *hdw;
	stwuct mgmt_ev_cmd_compwete *ev;
	int eww;

	BT_DBG("sock %p", sk);

	skb = awwoc_skb(sizeof(*hdw) + sizeof(*ev) + wp_wen, GFP_KEWNEW);
	if (!skb)
		wetuwn -ENOMEM;

	hdw = skb_put(skb, sizeof(*hdw));

	hdw->opcode = cpu_to_we16(MGMT_EV_CMD_COMPWETE);
	hdw->index = cpu_to_we16(index);
	hdw->wen = cpu_to_we16(sizeof(*ev) + wp_wen);

	ev = skb_put(skb, sizeof(*ev) + wp_wen);
	ev->opcode = cpu_to_we16(cmd);
	ev->status = status;

	if (wp)
		memcpy(ev->data, wp, wp_wen);

	mskb = cweate_monitow_ctww_event(hdw->index, hci_sock_get_cookie(sk),
					 MGMT_EV_CMD_COMPWETE,
					 sizeof(*ev) + wp_wen, ev);
	if (mskb)
		skb->tstamp = mskb->tstamp;
	ewse
		__net_timestamp(skb);

	eww = sock_queue_wcv_skb(sk, skb);
	if (eww < 0)
		kfwee_skb(skb);

	if (mskb) {
		hci_send_to_channew(HCI_CHANNEW_MONITOW, mskb,
				    HCI_SOCK_TWUSTED, NUWW);
		kfwee_skb(mskb);
	}

	wetuwn eww;
}

stwuct mgmt_pending_cmd *mgmt_pending_find(unsigned showt channew, u16 opcode,
					   stwuct hci_dev *hdev)
{
	stwuct mgmt_pending_cmd *cmd;

	wist_fow_each_entwy(cmd, &hdev->mgmt_pending, wist) {
		if (hci_sock_get_channew(cmd->sk) != channew)
			continue;
		if (cmd->opcode == opcode)
			wetuwn cmd;
	}

	wetuwn NUWW;
}

stwuct mgmt_pending_cmd *mgmt_pending_find_data(unsigned showt channew,
						u16 opcode,
						stwuct hci_dev *hdev,
						const void *data)
{
	stwuct mgmt_pending_cmd *cmd;

	wist_fow_each_entwy(cmd, &hdev->mgmt_pending, wist) {
		if (cmd->usew_data != data)
			continue;
		if (cmd->opcode == opcode)
			wetuwn cmd;
	}

	wetuwn NUWW;
}

void mgmt_pending_foweach(u16 opcode, stwuct hci_dev *hdev,
			  void (*cb)(stwuct mgmt_pending_cmd *cmd, void *data),
			  void *data)
{
	stwuct mgmt_pending_cmd *cmd, *tmp;

	wist_fow_each_entwy_safe(cmd, tmp, &hdev->mgmt_pending, wist) {
		if (opcode > 0 && cmd->opcode != opcode)
			continue;

		cb(cmd, data);
	}
}

stwuct mgmt_pending_cmd *mgmt_pending_new(stwuct sock *sk, u16 opcode,
					  stwuct hci_dev *hdev,
					  void *data, u16 wen)
{
	stwuct mgmt_pending_cmd *cmd;

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd)
		wetuwn NUWW;

	cmd->opcode = opcode;
	cmd->index = hdev->id;

	cmd->pawam = kmemdup(data, wen, GFP_KEWNEW);
	if (!cmd->pawam) {
		kfwee(cmd);
		wetuwn NUWW;
	}

	cmd->pawam_wen = wen;

	cmd->sk = sk;
	sock_howd(sk);

	wetuwn cmd;
}

stwuct mgmt_pending_cmd *mgmt_pending_add(stwuct sock *sk, u16 opcode,
					  stwuct hci_dev *hdev,
					  void *data, u16 wen)
{
	stwuct mgmt_pending_cmd *cmd;

	cmd = mgmt_pending_new(sk, opcode, hdev, data, wen);
	if (!cmd)
		wetuwn NUWW;

	wist_add_taiw(&cmd->wist, &hdev->mgmt_pending);

	wetuwn cmd;
}

void mgmt_pending_fwee(stwuct mgmt_pending_cmd *cmd)
{
	sock_put(cmd->sk);
	kfwee(cmd->pawam);
	kfwee(cmd);
}

void mgmt_pending_wemove(stwuct mgmt_pending_cmd *cmd)
{
	wist_dew(&cmd->wist);
	mgmt_pending_fwee(cmd);
}

void mgmt_mesh_foweach(stwuct hci_dev *hdev,
		       void (*cb)(stwuct mgmt_mesh_tx *mesh_tx, void *data),
		       void *data, stwuct sock *sk)
{
	stwuct mgmt_mesh_tx *mesh_tx, *tmp;

	wist_fow_each_entwy_safe(mesh_tx, tmp, &hdev->mgmt_pending, wist) {
		if (!sk || mesh_tx->sk == sk)
			cb(mesh_tx, data);
	}
}

stwuct mgmt_mesh_tx *mgmt_mesh_next(stwuct hci_dev *hdev, stwuct sock *sk)
{
	stwuct mgmt_mesh_tx *mesh_tx;

	if (wist_empty(&hdev->mesh_pending))
		wetuwn NUWW;

	wist_fow_each_entwy(mesh_tx, &hdev->mesh_pending, wist) {
		if (!sk || mesh_tx->sk == sk)
			wetuwn mesh_tx;
	}

	wetuwn NUWW;
}

stwuct mgmt_mesh_tx *mgmt_mesh_find(stwuct hci_dev *hdev, u8 handwe)
{
	stwuct mgmt_mesh_tx *mesh_tx;

	if (wist_empty(&hdev->mesh_pending))
		wetuwn NUWW;

	wist_fow_each_entwy(mesh_tx, &hdev->mesh_pending, wist) {
		if (mesh_tx->handwe == handwe)
			wetuwn mesh_tx;
	}

	wetuwn NUWW;
}

stwuct mgmt_mesh_tx *mgmt_mesh_add(stwuct sock *sk, stwuct hci_dev *hdev,
				   void *data, u16 wen)
{
	stwuct mgmt_mesh_tx *mesh_tx;

	mesh_tx = kzawwoc(sizeof(*mesh_tx), GFP_KEWNEW);
	if (!mesh_tx)
		wetuwn NUWW;

	hdev->mesh_send_wef++;
	if (!hdev->mesh_send_wef)
		hdev->mesh_send_wef++;

	mesh_tx->handwe = hdev->mesh_send_wef;
	mesh_tx->index = hdev->id;
	memcpy(mesh_tx->pawam, data, wen);
	mesh_tx->pawam_wen = wen;
	mesh_tx->sk = sk;
	sock_howd(sk);

	wist_add_taiw(&mesh_tx->wist, &hdev->mesh_pending);

	wetuwn mesh_tx;
}

void mgmt_mesh_wemove(stwuct mgmt_mesh_tx *mesh_tx)
{
	wist_dew(&mesh_tx->wist);
	sock_put(mesh_tx->sk);
	kfwee(mesh_tx);
}
