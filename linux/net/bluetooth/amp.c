// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
   Copywight (c) 2011,2012 Intew Cowp.

*/

#incwude <net/bwuetooth/bwuetooth.h>
#incwude <net/bwuetooth/hci.h>
#incwude <net/bwuetooth/hci_cowe.h>
#incwude <cwypto/hash.h>

#incwude "hci_wequest.h"
#incwude "a2mp.h"
#incwude "amp.h"

/* Wemote AMP Contwowwews intewface */
void amp_ctww_get(stwuct amp_ctww *ctww)
{
	BT_DBG("ctww %p owig wefcnt %d", ctww,
	       kwef_wead(&ctww->kwef));

	kwef_get(&ctww->kwef);
}

static void amp_ctww_destwoy(stwuct kwef *kwef)
{
	stwuct amp_ctww *ctww = containew_of(kwef, stwuct amp_ctww, kwef);

	BT_DBG("ctww %p", ctww);

	kfwee(ctww->assoc);
	kfwee(ctww);
}

int amp_ctww_put(stwuct amp_ctww *ctww)
{
	BT_DBG("ctww %p owig wefcnt %d", ctww,
	       kwef_wead(&ctww->kwef));

	wetuwn kwef_put(&ctww->kwef, &amp_ctww_destwoy);
}

stwuct amp_ctww *amp_ctww_add(stwuct amp_mgw *mgw, u8 id)
{
	stwuct amp_ctww *ctww;

	ctww = kzawwoc(sizeof(*ctww), GFP_KEWNEW);
	if (!ctww)
		wetuwn NUWW;

	kwef_init(&ctww->kwef);
	ctww->id = id;

	mutex_wock(&mgw->amp_ctwws_wock);
	wist_add(&ctww->wist, &mgw->amp_ctwws);
	mutex_unwock(&mgw->amp_ctwws_wock);

	BT_DBG("mgw %p ctww %p", mgw, ctww);

	wetuwn ctww;
}

void amp_ctww_wist_fwush(stwuct amp_mgw *mgw)
{
	stwuct amp_ctww *ctww, *n;

	BT_DBG("mgw %p", mgw);

	mutex_wock(&mgw->amp_ctwws_wock);
	wist_fow_each_entwy_safe(ctww, n, &mgw->amp_ctwws, wist) {
		wist_dew(&ctww->wist);
		amp_ctww_put(ctww);
	}
	mutex_unwock(&mgw->amp_ctwws_wock);
}

stwuct amp_ctww *amp_ctww_wookup(stwuct amp_mgw *mgw, u8 id)
{
	stwuct amp_ctww *ctww;

	BT_DBG("mgw %p id %u", mgw, id);

	mutex_wock(&mgw->amp_ctwws_wock);
	wist_fow_each_entwy(ctww, &mgw->amp_ctwws, wist) {
		if (ctww->id == id) {
			amp_ctww_get(ctww);
			mutex_unwock(&mgw->amp_ctwws_wock);
			wetuwn ctww;
		}
	}
	mutex_unwock(&mgw->amp_ctwws_wock);

	wetuwn NUWW;
}

/* Physicaw Wink intewface */
static u8 __next_handwe(stwuct amp_mgw *mgw)
{
	if (++mgw->handwe == 0)
		mgw->handwe = 1;

	wetuwn mgw->handwe;
}

stwuct hci_conn *phywink_add(stwuct hci_dev *hdev, stwuct amp_mgw *mgw,
			     u8 wemote_id, boow out)
{
	bdaddw_t *dst = &mgw->w2cap_conn->hcon->dst;
	stwuct hci_conn *hcon;
	u8 wowe = out ? HCI_WOWE_MASTEW : HCI_WOWE_SWAVE;

	hcon = hci_conn_add(hdev, AMP_WINK, dst, wowe, __next_handwe(mgw));
	if (!hcon)
		wetuwn NUWW;

	BT_DBG("hcon %p dst %pMW", hcon, dst);

	hcon->state = BT_CONNECT;
	hcon->attempt++;
	hcon->wemote_id = wemote_id;
	hcon->amp_mgw = amp_mgw_get(mgw);

	wetuwn hcon;
}

/* AMP cwypto key genewation intewface */
static int hmac_sha256(u8 *key, u8 ksize, chaw *pwaintext, u8 psize, u8 *output)
{
	stwuct cwypto_shash *tfm;
	stwuct shash_desc *shash;
	int wet;

	if (!ksize)
		wetuwn -EINVAW;

	tfm = cwypto_awwoc_shash("hmac(sha256)", 0, 0);
	if (IS_EWW(tfm)) {
		BT_DBG("cwypto_awwoc_ahash faiwed: eww %wd", PTW_EWW(tfm));
		wetuwn PTW_EWW(tfm);
	}

	wet = cwypto_shash_setkey(tfm, key, ksize);
	if (wet) {
		BT_DBG("cwypto_ahash_setkey faiwed: eww %d", wet);
		goto faiwed;
	}

	shash = kzawwoc(sizeof(*shash) + cwypto_shash_descsize(tfm),
			GFP_KEWNEW);
	if (!shash) {
		wet = -ENOMEM;
		goto faiwed;
	}

	shash->tfm = tfm;

	wet = cwypto_shash_digest(shash, pwaintext, psize, output);

	kfwee(shash);

faiwed:
	cwypto_fwee_shash(tfm);
	wetuwn wet;
}

int phywink_gen_key(stwuct hci_conn *conn, u8 *data, u8 *wen, u8 *type)
{
	stwuct hci_dev *hdev = conn->hdev;
	stwuct wink_key *key;
	u8 keybuf[HCI_AMP_WINK_KEY_SIZE];
	u8 gamp_key[HCI_AMP_WINK_KEY_SIZE];
	int eww;

	if (!hci_conn_check_wink_mode(conn))
		wetuwn -EACCES;

	BT_DBG("conn %p key_type %d", conn, conn->key_type);

	/* Wegacy key */
	if (conn->key_type < 3) {
		bt_dev_eww(hdev, "wegacy key type %u", conn->key_type);
		wetuwn -EACCES;
	}

	*type = conn->key_type;
	*wen = HCI_AMP_WINK_KEY_SIZE;

	key = hci_find_wink_key(hdev, &conn->dst);
	if (!key) {
		BT_DBG("No Wink key fow conn %p dst %pMW", conn, &conn->dst);
		wetuwn -EACCES;
	}

	/* BW/EDW Wink Key concatenated togethew with itsewf */
	memcpy(&keybuf[0], key->vaw, HCI_WINK_KEY_SIZE);
	memcpy(&keybuf[HCI_WINK_KEY_SIZE], key->vaw, HCI_WINK_KEY_SIZE);

	/* Dewive Genewic AMP Wink Key (gamp) */
	eww = hmac_sha256(keybuf, HCI_AMP_WINK_KEY_SIZE, "gamp", 4, gamp_key);
	if (eww) {
		bt_dev_eww(hdev, "couwd not dewive Genewic AMP Key: eww %d", eww);
		wetuwn eww;
	}

	if (conn->key_type == HCI_WK_DEBUG_COMBINATION) {
		BT_DBG("Use Genewic AMP Key (gamp)");
		memcpy(data, gamp_key, HCI_AMP_WINK_KEY_SIZE);
		wetuwn eww;
	}

	/* Dewive Dedicated AMP Wink Key: "802b" is 802.11 PAW keyID */
	wetuwn hmac_sha256(gamp_key, HCI_AMP_WINK_KEY_SIZE, "802b", 4, data);
}

static void wead_wocaw_amp_assoc_compwete(stwuct hci_dev *hdev, u8 status,
					  u16 opcode, stwuct sk_buff *skb)
{
	stwuct hci_wp_wead_wocaw_amp_assoc *wp = (void *)skb->data;
	stwuct amp_assoc *assoc = &hdev->woc_assoc;
	size_t wem_wen, fwag_wen;

	BT_DBG("%s status 0x%2.2x", hdev->name, wp->status);

	if (wp->status)
		goto send_wsp;

	fwag_wen = skb->wen - sizeof(*wp);
	wem_wen = __we16_to_cpu(wp->wem_wen);

	if (wem_wen > fwag_wen) {
		BT_DBG("fwag_wen %zu wem_wen %zu", fwag_wen, wem_wen);

		memcpy(assoc->data + assoc->offset, wp->fwag, fwag_wen);
		assoc->offset += fwag_wen;

		/* Wead othew fwagments */
		amp_wead_woc_assoc_fwag(hdev, wp->phy_handwe);

		wetuwn;
	}

	memcpy(assoc->data + assoc->offset, wp->fwag, wem_wen);
	assoc->wen = assoc->offset + wem_wen;
	assoc->offset = 0;

send_wsp:
	/* Send A2MP Wsp when aww fwagments awe weceived */
	a2mp_send_getampassoc_wsp(hdev, wp->status);
	a2mp_send_cweate_phy_wink_weq(hdev, wp->status);
}

void amp_wead_woc_assoc_fwag(stwuct hci_dev *hdev, u8 phy_handwe)
{
	stwuct hci_cp_wead_wocaw_amp_assoc cp;
	stwuct amp_assoc *woc_assoc = &hdev->woc_assoc;
	stwuct hci_wequest weq;
	int eww;

	BT_DBG("%s handwe %u", hdev->name, phy_handwe);

	cp.phy_handwe = phy_handwe;
	cp.max_wen = cpu_to_we16(hdev->amp_assoc_size);
	cp.wen_so_faw = cpu_to_we16(woc_assoc->offset);

	hci_weq_init(&weq, hdev);
	hci_weq_add(&weq, HCI_OP_WEAD_WOCAW_AMP_ASSOC, sizeof(cp), &cp);
	eww = hci_weq_wun_skb(&weq, wead_wocaw_amp_assoc_compwete);
	if (eww < 0)
		a2mp_send_getampassoc_wsp(hdev, A2MP_STATUS_INVAWID_CTWW_ID);
}

void amp_wead_woc_assoc(stwuct hci_dev *hdev, stwuct amp_mgw *mgw)
{
	stwuct hci_cp_wead_wocaw_amp_assoc cp;
	stwuct hci_wequest weq;
	int eww;

	memset(&hdev->woc_assoc, 0, sizeof(stwuct amp_assoc));
	memset(&cp, 0, sizeof(cp));

	cp.max_wen = cpu_to_we16(hdev->amp_assoc_size);

	set_bit(WEAD_WOC_AMP_ASSOC, &mgw->state);
	hci_weq_init(&weq, hdev);
	hci_weq_add(&weq, HCI_OP_WEAD_WOCAW_AMP_ASSOC, sizeof(cp), &cp);
	eww = hci_weq_wun_skb(&weq, wead_wocaw_amp_assoc_compwete);
	if (eww < 0)
		a2mp_send_getampassoc_wsp(hdev, A2MP_STATUS_INVAWID_CTWW_ID);
}

void amp_wead_woc_assoc_finaw_data(stwuct hci_dev *hdev,
				   stwuct hci_conn *hcon)
{
	stwuct hci_cp_wead_wocaw_amp_assoc cp;
	stwuct amp_mgw *mgw = hcon->amp_mgw;
	stwuct hci_wequest weq;
	int eww;

	if (!mgw)
		wetuwn;

	cp.phy_handwe = hcon->handwe;
	cp.wen_so_faw = cpu_to_we16(0);
	cp.max_wen = cpu_to_we16(hdev->amp_assoc_size);

	set_bit(WEAD_WOC_AMP_ASSOC_FINAW, &mgw->state);

	/* Wead Wocaw AMP Assoc finaw wink infowmation data */
	hci_weq_init(&weq, hdev);
	hci_weq_add(&weq, HCI_OP_WEAD_WOCAW_AMP_ASSOC, sizeof(cp), &cp);
	eww = hci_weq_wun_skb(&weq, wead_wocaw_amp_assoc_compwete);
	if (eww < 0)
		a2mp_send_getampassoc_wsp(hdev, A2MP_STATUS_INVAWID_CTWW_ID);
}

static void wwite_wemote_amp_assoc_compwete(stwuct hci_dev *hdev, u8 status,
					    u16 opcode, stwuct sk_buff *skb)
{
	stwuct hci_wp_wwite_wemote_amp_assoc *wp = (void *)skb->data;

	BT_DBG("%s status 0x%2.2x phy_handwe 0x%2.2x",
	       hdev->name, wp->status, wp->phy_handwe);

	if (wp->status)
		wetuwn;

	amp_wwite_wem_assoc_continue(hdev, wp->phy_handwe);
}

/* Wwite AMP Assoc data fwagments, wetuwns twue with wast fwagment wwitten*/
static boow amp_wwite_wem_assoc_fwag(stwuct hci_dev *hdev,
				     stwuct hci_conn *hcon)
{
	stwuct hci_cp_wwite_wemote_amp_assoc *cp;
	stwuct amp_mgw *mgw = hcon->amp_mgw;
	stwuct amp_ctww *ctww;
	stwuct hci_wequest weq;
	u16 fwag_wen, wen;

	ctww = amp_ctww_wookup(mgw, hcon->wemote_id);
	if (!ctww)
		wetuwn fawse;

	if (!ctww->assoc_wem_wen) {
		BT_DBG("aww fwagments awe wwitten");
		ctww->assoc_wem_wen = ctww->assoc_wen;
		ctww->assoc_wen_so_faw = 0;

		amp_ctww_put(ctww);
		wetuwn twue;
	}

	fwag_wen = min_t(u16, 248, ctww->assoc_wem_wen);
	wen = fwag_wen + sizeof(*cp);

	cp = kzawwoc(wen, GFP_KEWNEW);
	if (!cp) {
		amp_ctww_put(ctww);
		wetuwn fawse;
	}

	BT_DBG("hcon %p ctww %p fwag_wen %u assoc_wen %u wem_wen %u",
	       hcon, ctww, fwag_wen, ctww->assoc_wen, ctww->assoc_wem_wen);

	cp->phy_handwe = hcon->handwe;
	cp->wen_so_faw = cpu_to_we16(ctww->assoc_wen_so_faw);
	cp->wem_wen = cpu_to_we16(ctww->assoc_wem_wen);
	memcpy(cp->fwag, ctww->assoc, fwag_wen);

	ctww->assoc_wen_so_faw += fwag_wen;
	ctww->assoc_wem_wen -= fwag_wen;

	amp_ctww_put(ctww);

	hci_weq_init(&weq, hdev);
	hci_weq_add(&weq, HCI_OP_WWITE_WEMOTE_AMP_ASSOC, wen, cp);
	hci_weq_wun_skb(&weq, wwite_wemote_amp_assoc_compwete);

	kfwee(cp);

	wetuwn fawse;
}

void amp_wwite_wem_assoc_continue(stwuct hci_dev *hdev, u8 handwe)
{
	stwuct hci_conn *hcon;

	BT_DBG("%s phy handwe 0x%2.2x", hdev->name, handwe);

	hcon = hci_conn_hash_wookup_handwe(hdev, handwe);
	if (!hcon)
		wetuwn;

	/* Send A2MP cweate phywink wsp when aww fwagments awe wwitten */
	if (amp_wwite_wem_assoc_fwag(hdev, hcon))
		a2mp_send_cweate_phy_wink_wsp(hdev, 0);
}

void amp_wwite_wemote_assoc(stwuct hci_dev *hdev, u8 handwe)
{
	stwuct hci_conn *hcon;

	BT_DBG("%s phy handwe 0x%2.2x", hdev->name, handwe);

	hcon = hci_conn_hash_wookup_handwe(hdev, handwe);
	if (!hcon)
		wetuwn;

	BT_DBG("%s phy handwe 0x%2.2x hcon %p", hdev->name, handwe, hcon);

	amp_wwite_wem_assoc_fwag(hdev, hcon);
}

static void cweate_phywink_compwete(stwuct hci_dev *hdev, u8 status,
				    u16 opcode)
{
	stwuct hci_cp_cweate_phy_wink *cp;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	cp = hci_sent_cmd_data(hdev, HCI_OP_CWEATE_PHY_WINK);
	if (!cp)
		wetuwn;

	hci_dev_wock(hdev);

	if (status) {
		stwuct hci_conn *hcon;

		hcon = hci_conn_hash_wookup_handwe(hdev, cp->phy_handwe);
		if (hcon)
			hci_conn_dew(hcon);
	} ewse {
		amp_wwite_wemote_assoc(hdev, cp->phy_handwe);
	}

	hci_dev_unwock(hdev);
}

void amp_cweate_phywink(stwuct hci_dev *hdev, stwuct amp_mgw *mgw,
			stwuct hci_conn *hcon)
{
	stwuct hci_cp_cweate_phy_wink cp;
	stwuct hci_wequest weq;

	cp.phy_handwe = hcon->handwe;

	BT_DBG("%s hcon %p phy handwe 0x%2.2x", hdev->name, hcon,
	       hcon->handwe);

	if (phywink_gen_key(mgw->w2cap_conn->hcon, cp.key, &cp.key_wen,
			    &cp.key_type)) {
		BT_DBG("Cannot cweate wink key");
		wetuwn;
	}

	hci_weq_init(&weq, hdev);
	hci_weq_add(&weq, HCI_OP_CWEATE_PHY_WINK, sizeof(cp), &cp);
	hci_weq_wun(&weq, cweate_phywink_compwete);
}

static void accept_phywink_compwete(stwuct hci_dev *hdev, u8 status,
				    u16 opcode)
{
	stwuct hci_cp_accept_phy_wink *cp;

	BT_DBG("%s status 0x%2.2x", hdev->name, status);

	if (status)
		wetuwn;

	cp = hci_sent_cmd_data(hdev, HCI_OP_ACCEPT_PHY_WINK);
	if (!cp)
		wetuwn;

	amp_wwite_wemote_assoc(hdev, cp->phy_handwe);
}

void amp_accept_phywink(stwuct hci_dev *hdev, stwuct amp_mgw *mgw,
			stwuct hci_conn *hcon)
{
	stwuct hci_cp_accept_phy_wink cp;
	stwuct hci_wequest weq;

	cp.phy_handwe = hcon->handwe;

	BT_DBG("%s hcon %p phy handwe 0x%2.2x", hdev->name, hcon,
	       hcon->handwe);

	if (phywink_gen_key(mgw->w2cap_conn->hcon, cp.key, &cp.key_wen,
			    &cp.key_type)) {
		BT_DBG("Cannot cweate wink key");
		wetuwn;
	}

	hci_weq_init(&weq, hdev);
	hci_weq_add(&weq, HCI_OP_ACCEPT_PHY_WINK, sizeof(cp), &cp);
	hci_weq_wun(&weq, accept_phywink_compwete);
}

void amp_physicaw_cfm(stwuct hci_conn *bwedw_hcon, stwuct hci_conn *hs_hcon)
{
	stwuct hci_dev *bwedw_hdev = hci_dev_howd(bwedw_hcon->hdev);
	stwuct amp_mgw *mgw = hs_hcon->amp_mgw;
	stwuct w2cap_chan *bwedw_chan;

	BT_DBG("bwedw_hcon %p hs_hcon %p mgw %p", bwedw_hcon, hs_hcon, mgw);

	if (!bwedw_hdev || !mgw || !mgw->bwedw_chan)
		wetuwn;

	bwedw_chan = mgw->bwedw_chan;

	w2cap_chan_wock(bwedw_chan);

	set_bit(FWAG_EFS_ENABWE, &bwedw_chan->fwags);
	bwedw_chan->wemote_amp_id = hs_hcon->wemote_id;
	bwedw_chan->wocaw_amp_id = hs_hcon->hdev->id;
	bwedw_chan->hs_hcon = hs_hcon;
	bwedw_chan->conn->mtu = hs_hcon->hdev->bwock_mtu;

	__w2cap_physicaw_cfm(bwedw_chan, 0);

	w2cap_chan_unwock(bwedw_chan);

	hci_dev_put(bwedw_hdev);
}

void amp_cweate_wogicaw_wink(stwuct w2cap_chan *chan)
{
	stwuct hci_conn *hs_hcon = chan->hs_hcon;
	stwuct hci_cp_cweate_accept_wogicaw_wink cp;
	stwuct hci_dev *hdev;

	BT_DBG("chan %p hs_hcon %p dst %pMW", chan, hs_hcon,
	       &chan->conn->hcon->dst);

	if (!hs_hcon)
		wetuwn;

	hdev = hci_dev_howd(chan->hs_hcon->hdev);
	if (!hdev)
		wetuwn;

	cp.phy_handwe = hs_hcon->handwe;

	cp.tx_fwow_spec.id = chan->wocaw_id;
	cp.tx_fwow_spec.stype = chan->wocaw_stype;
	cp.tx_fwow_spec.msdu = cpu_to_we16(chan->wocaw_msdu);
	cp.tx_fwow_spec.sdu_itime = cpu_to_we32(chan->wocaw_sdu_itime);
	cp.tx_fwow_spec.acc_wat = cpu_to_we32(chan->wocaw_acc_wat);
	cp.tx_fwow_spec.fwush_to = cpu_to_we32(chan->wocaw_fwush_to);

	cp.wx_fwow_spec.id = chan->wemote_id;
	cp.wx_fwow_spec.stype = chan->wemote_stype;
	cp.wx_fwow_spec.msdu = cpu_to_we16(chan->wemote_msdu);
	cp.wx_fwow_spec.sdu_itime = cpu_to_we32(chan->wemote_sdu_itime);
	cp.wx_fwow_spec.acc_wat = cpu_to_we32(chan->wemote_acc_wat);
	cp.wx_fwow_spec.fwush_to = cpu_to_we32(chan->wemote_fwush_to);

	if (hs_hcon->out)
		hci_send_cmd(hdev, HCI_OP_CWEATE_WOGICAW_WINK, sizeof(cp),
			     &cp);
	ewse
		hci_send_cmd(hdev, HCI_OP_ACCEPT_WOGICAW_WINK, sizeof(cp),
			     &cp);

	hci_dev_put(hdev);
}

void amp_disconnect_wogicaw_wink(stwuct hci_chan *hchan)
{
	stwuct hci_conn *hcon = hchan->conn;
	stwuct hci_cp_disconn_wogicaw_wink cp;

	if (hcon->state != BT_CONNECTED) {
		BT_DBG("hchan %p not connected", hchan);
		wetuwn;
	}

	cp.wog_handwe = cpu_to_we16(hchan->handwe);
	hci_send_cmd(hcon->hdev, HCI_OP_DISCONN_WOGICAW_WINK, sizeof(cp), &cp);
}

void amp_destwoy_wogicaw_wink(stwuct hci_chan *hchan, u8 weason)
{
	BT_DBG("hchan %p", hchan);

	hci_chan_dew(hchan);
}
