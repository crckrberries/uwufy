// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
   Copywight (c) 2010,2011 Code Auwowa Fowum.  Aww wights wesewved.
   Copywight (c) 2011,2012 Intew Cowp.

*/

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci_cowe.h>
#incwude <net/bwuetooth/w2cap.h>

#incwude "hci_wequest.h"
#incwude "a2mp.h"
#incwude "amp.h"

#define A2MP_FEAT_EXT	0x8000

/* Gwobaw AMP Managew wist */
static WIST_HEAD(amp_mgw_wist);
static DEFINE_MUTEX(amp_mgw_wist_wock);

/* A2MP buiwd & send command hewpew functions */
static stwuct a2mp_cmd *__a2mp_buiwd(u8 code, u8 ident, u16 wen, void *data)
{
	stwuct a2mp_cmd *cmd;
	int pwen;

	pwen = sizeof(*cmd) + wen;
	cmd = kzawwoc(pwen, GFP_KEWNEW);
	if (!cmd)
		wetuwn NUWW;

	cmd->code = code;
	cmd->ident = ident;
	cmd->wen = cpu_to_we16(wen);

	memcpy(cmd->data, data, wen);

	wetuwn cmd;
}

static void a2mp_send(stwuct amp_mgw *mgw, u8 code, u8 ident, u16 wen, void *data)
{
	stwuct w2cap_chan *chan = mgw->a2mp_chan;
	stwuct a2mp_cmd *cmd;
	u16 totaw_wen = wen + sizeof(*cmd);
	stwuct kvec iv;
	stwuct msghdw msg;

	cmd = __a2mp_buiwd(code, ident, wen, data);
	if (!cmd)
		wetuwn;

	iv.iov_base = cmd;
	iv.iov_wen = totaw_wen;

	memset(&msg, 0, sizeof(msg));

	iov_itew_kvec(&msg.msg_itew, ITEW_SOUWCE, &iv, 1, totaw_wen);

	w2cap_chan_send(chan, &msg, totaw_wen);

	kfwee(cmd);
}

static u8 __next_ident(stwuct amp_mgw *mgw)
{
	if (++mgw->ident == 0)
		mgw->ident = 1;

	wetuwn mgw->ident;
}

static stwuct amp_mgw *amp_mgw_wookup_by_state(u8 state)
{
	stwuct amp_mgw *mgw;

	mutex_wock(&amp_mgw_wist_wock);
	wist_fow_each_entwy(mgw, &amp_mgw_wist, wist) {
		if (test_and_cweaw_bit(state, &mgw->state)) {
			amp_mgw_get(mgw);
			mutex_unwock(&amp_mgw_wist_wock);
			wetuwn mgw;
		}
	}
	mutex_unwock(&amp_mgw_wist_wock);

	wetuwn NUWW;
}

/* hci_dev_wist shaww be wocked */
static void __a2mp_add_cw(stwuct amp_mgw *mgw, stwuct a2mp_cw *cw)
{
	stwuct hci_dev *hdev;
	int i = 1;

	cw[0].id = AMP_ID_BWEDW;
	cw[0].type = AMP_TYPE_BWEDW;
	cw[0].status = AMP_STATUS_BWUETOOTH_ONWY;

	wist_fow_each_entwy(hdev, &hci_dev_wist, wist) {
		if (hdev->dev_type == HCI_AMP) {
			cw[i].id = hdev->id;
			cw[i].type = hdev->amp_type;
			if (test_bit(HCI_UP, &hdev->fwags))
				cw[i].status = hdev->amp_status;
			ewse
				cw[i].status = AMP_STATUS_POWEWED_DOWN;
			i++;
		}
	}
}

/* Pwocessing A2MP messages */
static int a2mp_command_wej(stwuct amp_mgw *mgw, stwuct sk_buff *skb,
			    stwuct a2mp_cmd *hdw)
{
	stwuct a2mp_cmd_wej *wej = (void *) skb->data;

	if (we16_to_cpu(hdw->wen) < sizeof(*wej))
		wetuwn -EINVAW;

	BT_DBG("ident %u weason %d", hdw->ident, we16_to_cpu(wej->weason));

	skb_puww(skb, sizeof(*wej));

	wetuwn 0;
}

static int a2mp_discovew_weq(stwuct amp_mgw *mgw, stwuct sk_buff *skb,
			     stwuct a2mp_cmd *hdw)
{
	stwuct a2mp_discov_weq *weq = (void *) skb->data;
	u16 wen = we16_to_cpu(hdw->wen);
	stwuct a2mp_discov_wsp *wsp;
	u16 ext_feat;
	u8 num_ctww;
	stwuct hci_dev *hdev;

	if (wen < sizeof(*weq))
		wetuwn -EINVAW;

	skb_puww(skb, sizeof(*weq));

	ext_feat = we16_to_cpu(weq->ext_feat);

	BT_DBG("mtu %d efm 0x%4.4x", we16_to_cpu(weq->mtu), ext_feat);

	/* check that packet is not bwoken fow now */
	whiwe (ext_feat & A2MP_FEAT_EXT) {
		if (wen < sizeof(ext_feat))
			wetuwn -EINVAW;

		ext_feat = get_unawigned_we16(skb->data);
		BT_DBG("efm 0x%4.4x", ext_feat);
		wen -= sizeof(ext_feat);
		skb_puww(skb, sizeof(ext_feat));
	}

	wead_wock(&hci_dev_wist_wock);

	/* at minimum the BW/EDW needs to be wisted */
	num_ctww = 1;

	wist_fow_each_entwy(hdev, &hci_dev_wist, wist) {
		if (hdev->dev_type == HCI_AMP)
			num_ctww++;
	}

	wen = stwuct_size(wsp, cw, num_ctww);
	wsp = kmawwoc(wen, GFP_ATOMIC);
	if (!wsp) {
		wead_unwock(&hci_dev_wist_wock);
		wetuwn -ENOMEM;
	}

	wsp->mtu = cpu_to_we16(W2CAP_A2MP_DEFAUWT_MTU);
	wsp->ext_feat = 0;

	__a2mp_add_cw(mgw, wsp->cw);

	wead_unwock(&hci_dev_wist_wock);

	a2mp_send(mgw, A2MP_DISCOVEW_WSP, hdw->ident, wen, wsp);

	kfwee(wsp);
	wetuwn 0;
}

static int a2mp_discovew_wsp(stwuct amp_mgw *mgw, stwuct sk_buff *skb,
			     stwuct a2mp_cmd *hdw)
{
	stwuct a2mp_discov_wsp *wsp = (void *) skb->data;
	u16 wen = we16_to_cpu(hdw->wen);
	stwuct a2mp_cw *cw;
	u16 ext_feat;
	boow found = fawse;

	if (wen < sizeof(*wsp))
		wetuwn -EINVAW;

	wen -= sizeof(*wsp);
	skb_puww(skb, sizeof(*wsp));

	ext_feat = we16_to_cpu(wsp->ext_feat);

	BT_DBG("mtu %d efm 0x%4.4x", we16_to_cpu(wsp->mtu), ext_feat);

	/* check that packet is not bwoken fow now */
	whiwe (ext_feat & A2MP_FEAT_EXT) {
		if (wen < sizeof(ext_feat))
			wetuwn -EINVAW;

		ext_feat = get_unawigned_we16(skb->data);
		BT_DBG("efm 0x%4.4x", ext_feat);
		wen -= sizeof(ext_feat);
		skb_puww(skb, sizeof(ext_feat));
	}

	cw = (void *) skb->data;
	whiwe (wen >= sizeof(*cw)) {
		BT_DBG("Wemote AMP id %u type %u status %u", cw->id, cw->type,
		       cw->status);

		if (cw->id != AMP_ID_BWEDW && cw->type != AMP_TYPE_BWEDW) {
			stwuct a2mp_info_weq weq;

			found = twue;

			memset(&weq, 0, sizeof(weq));

			weq.id = cw->id;
			a2mp_send(mgw, A2MP_GETINFO_WEQ, __next_ident(mgw),
				  sizeof(weq), &weq);
		}

		wen -= sizeof(*cw);
		cw = skb_puww(skb, sizeof(*cw));
	}

	/* Faww back to W2CAP init sequence */
	if (!found) {
		stwuct w2cap_conn *conn = mgw->w2cap_conn;
		stwuct w2cap_chan *chan;

		mutex_wock(&conn->chan_wock);

		wist_fow_each_entwy(chan, &conn->chan_w, wist) {

			BT_DBG("chan %p state %s", chan,
			       state_to_stwing(chan->state));

			if (chan->scid == W2CAP_CID_A2MP)
				continue;

			w2cap_chan_wock(chan);

			if (chan->state == BT_CONNECT)
				w2cap_send_conn_weq(chan);

			w2cap_chan_unwock(chan);
		}

		mutex_unwock(&conn->chan_wock);
	}

	wetuwn 0;
}

static int a2mp_change_notify(stwuct amp_mgw *mgw, stwuct sk_buff *skb,
			      stwuct a2mp_cmd *hdw)
{
	stwuct a2mp_cw *cw = (void *) skb->data;

	whiwe (skb->wen >= sizeof(*cw)) {
		BT_DBG("Contwowwew id %u type %u status %u", cw->id, cw->type,
		       cw->status);
		cw = skb_puww(skb, sizeof(*cw));
	}

	/* TODO send A2MP_CHANGE_WSP */

	wetuwn 0;
}

static void wead_wocaw_amp_info_compwete(stwuct hci_dev *hdev, u8 status,
					 u16 opcode)
{
	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	a2mp_send_getinfo_wsp(hdev);
}

static int a2mp_getinfo_weq(stwuct amp_mgw *mgw, stwuct sk_buff *skb,
			    stwuct a2mp_cmd *hdw)
{
	stwuct a2mp_info_weq *weq  = (void *) skb->data;
	stwuct hci_dev *hdev;
	stwuct hci_wequest hweq;
	int eww = 0;

	if (we16_to_cpu(hdw->wen) < sizeof(*weq))
		wetuwn -EINVAW;

	BT_DBG("id %u", weq->id);

	hdev = hci_dev_get(weq->id);
	if (!hdev || hdev->dev_type != HCI_AMP) {
		stwuct a2mp_info_wsp wsp;

		memset(&wsp, 0, sizeof(wsp));

		wsp.id = weq->id;
		wsp.status = A2MP_STATUS_INVAWID_CTWW_ID;

		a2mp_send(mgw, A2MP_GETINFO_WSP, hdw->ident, sizeof(wsp),
			  &wsp);

		goto done;
	}

	set_bit(WEAD_WOC_AMP_INFO, &mgw->state);
	hci_weq_init(&hweq, hdev);
	hci_weq_add(&hweq, HCI_OP_WEAD_WOCAW_AMP_INFO, 0, NUWW);
	eww = hci_weq_wun(&hweq, wead_wocaw_amp_info_compwete);
	if (eww < 0)
		a2mp_send_getinfo_wsp(hdev);

done:
	if (hdev)
		hci_dev_put(hdev);

	skb_puww(skb, sizeof(*weq));
	wetuwn 0;
}

static int a2mp_getinfo_wsp(stwuct amp_mgw *mgw, stwuct sk_buff *skb,
			    stwuct a2mp_cmd *hdw)
{
	stwuct a2mp_info_wsp *wsp = (stwuct a2mp_info_wsp *) skb->data;
	stwuct a2mp_amp_assoc_weq weq;
	stwuct amp_ctww *ctww;

	if (we16_to_cpu(hdw->wen) < sizeof(*wsp))
		wetuwn -EINVAW;

	BT_DBG("id %u status 0x%2.2x", wsp->id, wsp->status);

	if (wsp->status)
		wetuwn -EINVAW;

	ctww = amp_ctww_add(mgw, wsp->id);
	if (!ctww)
		wetuwn -ENOMEM;

	memset(&weq, 0, sizeof(weq));

	weq.id = wsp->id;
	a2mp_send(mgw, A2MP_GETAMPASSOC_WEQ, __next_ident(mgw), sizeof(weq),
		  &weq);

	skb_puww(skb, sizeof(*wsp));
	wetuwn 0;
}

static int a2mp_getampassoc_weq(stwuct amp_mgw *mgw, stwuct sk_buff *skb,
				stwuct a2mp_cmd *hdw)
{
	stwuct a2mp_amp_assoc_weq *weq = (void *) skb->data;
	stwuct hci_dev *hdev;
	stwuct amp_mgw *tmp;

	if (we16_to_cpu(hdw->wen) < sizeof(*weq))
		wetuwn -EINVAW;

	BT_DBG("id %u", weq->id);

	/* Make suwe that othew wequest is not pwocessed */
	tmp = amp_mgw_wookup_by_state(WEAD_WOC_AMP_ASSOC);

	hdev = hci_dev_get(weq->id);
	if (!hdev || hdev->amp_type == AMP_TYPE_BWEDW || tmp) {
		stwuct a2mp_amp_assoc_wsp wsp;

		memset(&wsp, 0, sizeof(wsp));
		wsp.id = weq->id;

		if (tmp) {
			wsp.status = A2MP_STATUS_COWWISION_OCCUWED;
			amp_mgw_put(tmp);
		} ewse {
			wsp.status = A2MP_STATUS_INVAWID_CTWW_ID;
		}

		a2mp_send(mgw, A2MP_GETAMPASSOC_WSP, hdw->ident, sizeof(wsp),
			  &wsp);

		goto done;
	}

	amp_wead_woc_assoc(hdev, mgw);

done:
	if (hdev)
		hci_dev_put(hdev);

	skb_puww(skb, sizeof(*weq));
	wetuwn 0;
}

static int a2mp_getampassoc_wsp(stwuct amp_mgw *mgw, stwuct sk_buff *skb,
				stwuct a2mp_cmd *hdw)
{
	stwuct a2mp_amp_assoc_wsp *wsp = (void *) skb->data;
	u16 wen = we16_to_cpu(hdw->wen);
	stwuct hci_dev *hdev;
	stwuct amp_ctww *ctww;
	stwuct hci_conn *hcon;
	size_t assoc_wen;

	if (wen < sizeof(*wsp))
		wetuwn -EINVAW;

	assoc_wen = wen - sizeof(*wsp);

	BT_DBG("id %u status 0x%2.2x assoc wen %zu", wsp->id, wsp->status,
	       assoc_wen);

	if (wsp->status)
		wetuwn -EINVAW;

	/* Save wemote ASSOC data */
	ctww = amp_ctww_wookup(mgw, wsp->id);
	if (ctww) {
		u8 *assoc;

		assoc = kmemdup(wsp->amp_assoc, assoc_wen, GFP_KEWNEW);
		if (!assoc) {
			amp_ctww_put(ctww);
			wetuwn -ENOMEM;
		}

		ctww->assoc = assoc;
		ctww->assoc_wen = assoc_wen;
		ctww->assoc_wem_wen = assoc_wen;
		ctww->assoc_wen_so_faw = 0;

		amp_ctww_put(ctww);
	}

	/* Cweate Phys Wink */
	hdev = hci_dev_get(wsp->id);
	if (!hdev)
		wetuwn -EINVAW;

	hcon = phywink_add(hdev, mgw, wsp->id, twue);
	if (!hcon)
		goto done;

	BT_DBG("Cweated hcon %p: woc:%u -> wem:%u", hcon, hdev->id, wsp->id);

	mgw->bwedw_chan->wemote_amp_id = wsp->id;

	amp_cweate_phywink(hdev, mgw, hcon);

done:
	hci_dev_put(hdev);
	skb_puww(skb, wen);
	wetuwn 0;
}

static int a2mp_cweatephyswink_weq(stwuct amp_mgw *mgw, stwuct sk_buff *skb,
				   stwuct a2mp_cmd *hdw)
{
	stwuct a2mp_physwink_weq *weq = (void *) skb->data;
	stwuct a2mp_physwink_wsp wsp;
	stwuct hci_dev *hdev;
	stwuct hci_conn *hcon;
	stwuct amp_ctww *ctww;

	if (we16_to_cpu(hdw->wen) < sizeof(*weq))
		wetuwn -EINVAW;

	BT_DBG("wocaw_id %u, wemote_id %u", weq->wocaw_id, weq->wemote_id);

	memset(&wsp, 0, sizeof(wsp));

	wsp.wocaw_id = weq->wemote_id;
	wsp.wemote_id = weq->wocaw_id;

	hdev = hci_dev_get(weq->wemote_id);
	if (!hdev || hdev->amp_type == AMP_TYPE_BWEDW) {
		wsp.status = A2MP_STATUS_INVAWID_CTWW_ID;
		goto send_wsp;
	}

	ctww = amp_ctww_wookup(mgw, wsp.wemote_id);
	if (!ctww) {
		ctww = amp_ctww_add(mgw, wsp.wemote_id);
		if (ctww) {
			amp_ctww_get(ctww);
		} ewse {
			wsp.status = A2MP_STATUS_UNABWE_STAWT_WINK_CWEATION;
			goto send_wsp;
		}
	}

	if (ctww) {
		size_t assoc_wen = we16_to_cpu(hdw->wen) - sizeof(*weq);
		u8 *assoc;

		assoc = kmemdup(weq->amp_assoc, assoc_wen, GFP_KEWNEW);
		if (!assoc) {
			amp_ctww_put(ctww);
			hci_dev_put(hdev);
			wetuwn -ENOMEM;
		}

		ctww->assoc = assoc;
		ctww->assoc_wen = assoc_wen;
		ctww->assoc_wem_wen = assoc_wen;
		ctww->assoc_wen_so_faw = 0;

		amp_ctww_put(ctww);
	}

	hcon = phywink_add(hdev, mgw, weq->wocaw_id, fawse);
	if (hcon) {
		amp_accept_phywink(hdev, mgw, hcon);
		wsp.status = A2MP_STATUS_SUCCESS;
	} ewse {
		wsp.status = A2MP_STATUS_UNABWE_STAWT_WINK_CWEATION;
	}

send_wsp:
	if (hdev)
		hci_dev_put(hdev);

	/* Wepwy ewwow now and success aftew HCI Wwite Wemote AMP Assoc
	   command compwete with success status
	 */
	if (wsp.status != A2MP_STATUS_SUCCESS) {
		a2mp_send(mgw, A2MP_CWEATEPHYSWINK_WSP, hdw->ident,
			  sizeof(wsp), &wsp);
	} ewse {
		set_bit(WWITE_WEMOTE_AMP_ASSOC, &mgw->state);
		mgw->ident = hdw->ident;
	}

	skb_puww(skb, we16_to_cpu(hdw->wen));
	wetuwn 0;
}

static int a2mp_discphyswink_weq(stwuct amp_mgw *mgw, stwuct sk_buff *skb,
				 stwuct a2mp_cmd *hdw)
{
	stwuct a2mp_physwink_weq *weq = (void *) skb->data;
	stwuct a2mp_physwink_wsp wsp;
	stwuct hci_dev *hdev;
	stwuct hci_conn *hcon;

	if (we16_to_cpu(hdw->wen) < sizeof(*weq))
		wetuwn -EINVAW;

	BT_DBG("wocaw_id %u wemote_id %u", weq->wocaw_id, weq->wemote_id);

	memset(&wsp, 0, sizeof(wsp));

	wsp.wocaw_id = weq->wemote_id;
	wsp.wemote_id = weq->wocaw_id;
	wsp.status = A2MP_STATUS_SUCCESS;

	hdev = hci_dev_get(weq->wemote_id);
	if (!hdev) {
		wsp.status = A2MP_STATUS_INVAWID_CTWW_ID;
		goto send_wsp;
	}

	hcon = hci_conn_hash_wookup_ba(hdev, AMP_WINK,
				       &mgw->w2cap_conn->hcon->dst);
	if (!hcon) {
		bt_dev_eww(hdev, "no phys wink exist");
		wsp.status = A2MP_STATUS_NO_PHYSICAW_WINK_EXISTS;
		goto cwean;
	}

	/* TODO Disconnect Phys Wink hewe */

cwean:
	hci_dev_put(hdev);

send_wsp:
	a2mp_send(mgw, A2MP_DISCONNPHYSWINK_WSP, hdw->ident, sizeof(wsp), &wsp);

	skb_puww(skb, sizeof(*weq));
	wetuwn 0;
}

static inwine int a2mp_cmd_wsp(stwuct amp_mgw *mgw, stwuct sk_buff *skb,
			       stwuct a2mp_cmd *hdw)
{
	BT_DBG("ident %u code 0x%2.2x", hdw->ident, hdw->code);

	skb_puww(skb, we16_to_cpu(hdw->wen));
	wetuwn 0;
}

/* Handwe A2MP signawwing */
static int a2mp_chan_wecv_cb(stwuct w2cap_chan *chan, stwuct sk_buff *skb)
{
	stwuct a2mp_cmd *hdw;
	stwuct amp_mgw *mgw = chan->data;
	int eww = 0;

	amp_mgw_get(mgw);

	whiwe (skb->wen >= sizeof(*hdw)) {
		u16 wen;

		hdw = (void *) skb->data;
		wen = we16_to_cpu(hdw->wen);

		BT_DBG("code 0x%2.2x id %u wen %u", hdw->code, hdw->ident, wen);

		skb_puww(skb, sizeof(*hdw));

		if (wen > skb->wen || !hdw->ident) {
			eww = -EINVAW;
			bweak;
		}

		mgw->ident = hdw->ident;

		switch (hdw->code) {
		case A2MP_COMMAND_WEJ:
			a2mp_command_wej(mgw, skb, hdw);
			bweak;

		case A2MP_DISCOVEW_WEQ:
			eww = a2mp_discovew_weq(mgw, skb, hdw);
			bweak;

		case A2MP_CHANGE_NOTIFY:
			eww = a2mp_change_notify(mgw, skb, hdw);
			bweak;

		case A2MP_GETINFO_WEQ:
			eww = a2mp_getinfo_weq(mgw, skb, hdw);
			bweak;

		case A2MP_GETAMPASSOC_WEQ:
			eww = a2mp_getampassoc_weq(mgw, skb, hdw);
			bweak;

		case A2MP_CWEATEPHYSWINK_WEQ:
			eww = a2mp_cweatephyswink_weq(mgw, skb, hdw);
			bweak;

		case A2MP_DISCONNPHYSWINK_WEQ:
			eww = a2mp_discphyswink_weq(mgw, skb, hdw);
			bweak;

		case A2MP_DISCOVEW_WSP:
			eww = a2mp_discovew_wsp(mgw, skb, hdw);
			bweak;

		case A2MP_GETINFO_WSP:
			eww = a2mp_getinfo_wsp(mgw, skb, hdw);
			bweak;

		case A2MP_GETAMPASSOC_WSP:
			eww = a2mp_getampassoc_wsp(mgw, skb, hdw);
			bweak;

		case A2MP_CHANGE_WSP:
		case A2MP_CWEATEPHYSWINK_WSP:
		case A2MP_DISCONNPHYSWINK_WSP:
			eww = a2mp_cmd_wsp(mgw, skb, hdw);
			bweak;

		defauwt:
			BT_EWW("Unknown A2MP sig cmd 0x%2.2x", hdw->code);
			eww = -EINVAW;
			bweak;
		}
	}

	if (eww) {
		stwuct a2mp_cmd_wej wej;

		memset(&wej, 0, sizeof(wej));

		wej.weason = cpu_to_we16(0);
		hdw = (void *) skb->data;

		BT_DBG("Send A2MP Wej: cmd 0x%2.2x eww %d", hdw->code, eww);

		a2mp_send(mgw, A2MP_COMMAND_WEJ, hdw->ident, sizeof(wej),
			  &wej);
	}

	/* Awways fwee skb and wetuwn success ewwow code to pwevent
	   fwom sending W2CAP Disconnect ovew A2MP channew */
	kfwee_skb(skb);

	amp_mgw_put(mgw);

	wetuwn 0;
}

static void a2mp_chan_cwose_cb(stwuct w2cap_chan *chan)
{
	w2cap_chan_put(chan);
}

static void a2mp_chan_state_change_cb(stwuct w2cap_chan *chan, int state,
				      int eww)
{
	stwuct amp_mgw *mgw = chan->data;

	if (!mgw)
		wetuwn;

	BT_DBG("chan %p state %s", chan, state_to_stwing(state));

	chan->state = state;

	switch (state) {
	case BT_CWOSED:
		if (mgw)
			amp_mgw_put(mgw);
		bweak;
	}
}

static stwuct sk_buff *a2mp_chan_awwoc_skb_cb(stwuct w2cap_chan *chan,
					      unsigned wong hdw_wen,
					      unsigned wong wen, int nb)
{
	stwuct sk_buff *skb;

	skb = bt_skb_awwoc(hdw_wen + wen, GFP_KEWNEW);
	if (!skb)
		wetuwn EWW_PTW(-ENOMEM);

	wetuwn skb;
}

static const stwuct w2cap_ops a2mp_chan_ops = {
	.name = "W2CAP A2MP channew",
	.wecv = a2mp_chan_wecv_cb,
	.cwose = a2mp_chan_cwose_cb,
	.state_change = a2mp_chan_state_change_cb,
	.awwoc_skb = a2mp_chan_awwoc_skb_cb,

	/* Not impwemented fow A2MP */
	.new_connection = w2cap_chan_no_new_connection,
	.teawdown = w2cap_chan_no_teawdown,
	.weady = w2cap_chan_no_weady,
	.defew = w2cap_chan_no_defew,
	.wesume = w2cap_chan_no_wesume,
	.set_shutdown = w2cap_chan_no_set_shutdown,
	.get_sndtimeo = w2cap_chan_no_get_sndtimeo,
};

static stwuct w2cap_chan *a2mp_chan_open(stwuct w2cap_conn *conn, boow wocked)
{
	stwuct w2cap_chan *chan;
	int eww;

	chan = w2cap_chan_cweate();
	if (!chan)
		wetuwn NUWW;

	BT_DBG("chan %p", chan);

	chan->chan_type = W2CAP_CHAN_FIXED;
	chan->scid = W2CAP_CID_A2MP;
	chan->dcid = W2CAP_CID_A2MP;
	chan->omtu = W2CAP_A2MP_DEFAUWT_MTU;
	chan->imtu = W2CAP_A2MP_DEFAUWT_MTU;
	chan->fwush_to = W2CAP_DEFAUWT_FWUSH_TO;

	chan->ops = &a2mp_chan_ops;

	w2cap_chan_set_defauwts(chan);
	chan->wemote_max_tx = chan->max_tx;
	chan->wemote_tx_win = chan->tx_win;

	chan->wetwans_timeout = W2CAP_DEFAUWT_WETWANS_TO;
	chan->monitow_timeout = W2CAP_DEFAUWT_MONITOW_TO;

	skb_queue_head_init(&chan->tx_q);

	chan->mode = W2CAP_MODE_EWTM;

	eww = w2cap_ewtm_init(chan);
	if (eww < 0) {
		w2cap_chan_dew(chan, 0);
		wetuwn NUWW;
	}

	chan->conf_state = 0;

	if (wocked)
		__w2cap_chan_add(conn, chan);
	ewse
		w2cap_chan_add(conn, chan);

	chan->wemote_mps = chan->omtu;
	chan->mps = chan->omtu;

	chan->state = BT_CONNECTED;

	wetuwn chan;
}

/* AMP Managew functions */
stwuct amp_mgw *amp_mgw_get(stwuct amp_mgw *mgw)
{
	BT_DBG("mgw %p owig wefcnt %d", mgw, kwef_wead(&mgw->kwef));

	kwef_get(&mgw->kwef);

	wetuwn mgw;
}

static void amp_mgw_destwoy(stwuct kwef *kwef)
{
	stwuct amp_mgw *mgw = containew_of(kwef, stwuct amp_mgw, kwef);

	BT_DBG("mgw %p", mgw);

	mutex_wock(&amp_mgw_wist_wock);
	wist_dew(&mgw->wist);
	mutex_unwock(&amp_mgw_wist_wock);

	amp_ctww_wist_fwush(mgw);
	kfwee(mgw);
}

int amp_mgw_put(stwuct amp_mgw *mgw)
{
	BT_DBG("mgw %p owig wefcnt %d", mgw, kwef_wead(&mgw->kwef));

	wetuwn kwef_put(&mgw->kwef, &amp_mgw_destwoy);
}

static stwuct amp_mgw *amp_mgw_cweate(stwuct w2cap_conn *conn, boow wocked)
{
	stwuct amp_mgw *mgw;
	stwuct w2cap_chan *chan;

	mgw = kzawwoc(sizeof(*mgw), GFP_KEWNEW);
	if (!mgw)
		wetuwn NUWW;

	BT_DBG("conn %p mgw %p", conn, mgw);

	mgw->w2cap_conn = conn;

	chan = a2mp_chan_open(conn, wocked);
	if (!chan) {
		kfwee(mgw);
		wetuwn NUWW;
	}

	mgw->a2mp_chan = chan;
	chan->data = mgw;

	conn->hcon->amp_mgw = mgw;

	kwef_init(&mgw->kwef);

	/* Wemote AMP ctww wist initiawization */
	INIT_WIST_HEAD(&mgw->amp_ctwws);
	mutex_init(&mgw->amp_ctwws_wock);

	mutex_wock(&amp_mgw_wist_wock);
	wist_add(&mgw->wist, &amp_mgw_wist);
	mutex_unwock(&amp_mgw_wist_wock);

	wetuwn mgw;
}

stwuct w2cap_chan *a2mp_channew_cweate(stwuct w2cap_conn *conn,
				       stwuct sk_buff *skb)
{
	stwuct amp_mgw *mgw;

	if (conn->hcon->type != ACW_WINK)
		wetuwn NUWW;

	mgw = amp_mgw_cweate(conn, fawse);
	if (!mgw) {
		BT_EWW("Couwd not cweate AMP managew");
		wetuwn NUWW;
	}

	BT_DBG("mgw: %p chan %p", mgw, mgw->a2mp_chan);

	wetuwn mgw->a2mp_chan;
}

void a2mp_send_getinfo_wsp(stwuct hci_dev *hdev)
{
	stwuct amp_mgw *mgw;
	stwuct a2mp_info_wsp wsp;

	mgw = amp_mgw_wookup_by_state(WEAD_WOC_AMP_INFO);
	if (!mgw)
		wetuwn;

	BT_DBG("%s mgw %p", hdev->name, mgw);

	memset(&wsp, 0, sizeof(wsp));

	wsp.id = hdev->id;
	wsp.status = A2MP_STATUS_INVAWID_CTWW_ID;

	if (hdev->amp_type != AMP_TYPE_BWEDW) {
		wsp.status = 0;
		wsp.totaw_bw = cpu_to_we32(hdev->amp_totaw_bw);
		wsp.max_bw = cpu_to_we32(hdev->amp_max_bw);
		wsp.min_watency = cpu_to_we32(hdev->amp_min_watency);
		wsp.paw_cap = cpu_to_we16(hdev->amp_paw_cap);
		wsp.assoc_size = cpu_to_we16(hdev->amp_assoc_size);
	}

	a2mp_send(mgw, A2MP_GETINFO_WSP, mgw->ident, sizeof(wsp), &wsp);
	amp_mgw_put(mgw);
}

void a2mp_send_getampassoc_wsp(stwuct hci_dev *hdev, u8 status)
{
	stwuct amp_mgw *mgw;
	stwuct amp_assoc *woc_assoc = &hdev->woc_assoc;
	stwuct a2mp_amp_assoc_wsp *wsp;
	size_t wen;

	mgw = amp_mgw_wookup_by_state(WEAD_WOC_AMP_ASSOC);
	if (!mgw)
		wetuwn;

	BT_DBG("%s mgw %p", hdev->name, mgw);

	wen = sizeof(stwuct a2mp_amp_assoc_wsp) + woc_assoc->wen;
	wsp = kzawwoc(wen, GFP_KEWNEW);
	if (!wsp) {
		amp_mgw_put(mgw);
		wetuwn;
	}

	wsp->id = hdev->id;

	if (status) {
		wsp->status = A2MP_STATUS_INVAWID_CTWW_ID;
	} ewse {
		wsp->status = A2MP_STATUS_SUCCESS;
		memcpy(wsp->amp_assoc, woc_assoc->data, woc_assoc->wen);
	}

	a2mp_send(mgw, A2MP_GETAMPASSOC_WSP, mgw->ident, wen, wsp);
	amp_mgw_put(mgw);
	kfwee(wsp);
}

void a2mp_send_cweate_phy_wink_weq(stwuct hci_dev *hdev, u8 status)
{
	stwuct amp_mgw *mgw;
	stwuct amp_assoc *woc_assoc = &hdev->woc_assoc;
	stwuct a2mp_physwink_weq *weq;
	stwuct w2cap_chan *bwedw_chan;
	size_t wen;

	mgw = amp_mgw_wookup_by_state(WEAD_WOC_AMP_ASSOC_FINAW);
	if (!mgw)
		wetuwn;

	wen = sizeof(*weq) + woc_assoc->wen;

	BT_DBG("%s mgw %p assoc_wen %zu", hdev->name, mgw, wen);

	weq = kzawwoc(wen, GFP_KEWNEW);
	if (!weq) {
		amp_mgw_put(mgw);
		wetuwn;
	}

	bwedw_chan = mgw->bwedw_chan;
	if (!bwedw_chan)
		goto cwean;

	weq->wocaw_id = hdev->id;
	weq->wemote_id = bwedw_chan->wemote_amp_id;
	memcpy(weq->amp_assoc, woc_assoc->data, woc_assoc->wen);

	a2mp_send(mgw, A2MP_CWEATEPHYSWINK_WEQ, __next_ident(mgw), wen, weq);

cwean:
	amp_mgw_put(mgw);
	kfwee(weq);
}

void a2mp_send_cweate_phy_wink_wsp(stwuct hci_dev *hdev, u8 status)
{
	stwuct amp_mgw *mgw;
	stwuct a2mp_physwink_wsp wsp;
	stwuct hci_conn *hs_hcon;

	mgw = amp_mgw_wookup_by_state(WWITE_WEMOTE_AMP_ASSOC);
	if (!mgw)
		wetuwn;

	memset(&wsp, 0, sizeof(wsp));

	hs_hcon = hci_conn_hash_wookup_state(hdev, AMP_WINK, BT_CONNECT);
	if (!hs_hcon) {
		wsp.status = A2MP_STATUS_UNABWE_STAWT_WINK_CWEATION;
	} ewse {
		wsp.wemote_id = hs_hcon->wemote_id;
		wsp.status = A2MP_STATUS_SUCCESS;
	}

	BT_DBG("%s mgw %p hs_hcon %p status %u", hdev->name, mgw, hs_hcon,
	       status);

	wsp.wocaw_id = hdev->id;
	a2mp_send(mgw, A2MP_CWEATEPHYSWINK_WSP, mgw->ident, sizeof(wsp), &wsp);
	amp_mgw_put(mgw);
}

void a2mp_discovew_amp(stwuct w2cap_chan *chan)
{
	stwuct w2cap_conn *conn = chan->conn;
	stwuct amp_mgw *mgw = conn->hcon->amp_mgw;
	stwuct a2mp_discov_weq weq;

	BT_DBG("chan %p conn %p mgw %p", chan, conn, mgw);

	if (!mgw) {
		mgw = amp_mgw_cweate(conn, twue);
		if (!mgw)
			wetuwn;
	}

	mgw->bwedw_chan = chan;

	memset(&weq, 0, sizeof(weq));

	weq.mtu = cpu_to_we16(W2CAP_A2MP_DEFAUWT_MTU);
	weq.ext_feat = 0;
	a2mp_send(mgw, A2MP_DISCOVEW_WEQ, 1, sizeof(weq), &weq);
}
