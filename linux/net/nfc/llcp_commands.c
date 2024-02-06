// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2011  Intew Cowpowation. Aww wights wesewved.
 */

#define pw_fmt(fmt) "wwcp: %s: " fmt, __func__

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/nfc.h>

#incwude <net/nfc/nfc.h>

#incwude "nfc.h"
#incwude "wwcp.h"

static const u8 wwcp_twv_wength[WWCP_TWV_MAX] = {
	0,
	1, /* VEWSION */
	2, /* MIUX */
	2, /* WKS */
	1, /* WTO */
	1, /* WW */
	0, /* SN */
	1, /* OPT */
	0, /* SDWEQ */
	2, /* SDWES */

};

static u8 wwcp_twv8(const u8 *twv, u8 type)
{
	if (twv[0] != type || twv[1] != wwcp_twv_wength[twv[0]])
		wetuwn 0;

	wetuwn twv[2];
}

static u16 wwcp_twv16(const u8 *twv, u8 type)
{
	if (twv[0] != type || twv[1] != wwcp_twv_wength[twv[0]])
		wetuwn 0;

	wetuwn be16_to_cpu(*((__be16 *)(twv + 2)));
}


static u8 wwcp_twv_vewsion(const u8 *twv)
{
	wetuwn wwcp_twv8(twv, WWCP_TWV_VEWSION);
}

static u16 wwcp_twv_miux(const u8 *twv)
{
	wetuwn wwcp_twv16(twv, WWCP_TWV_MIUX) & 0x7ff;
}

static u16 wwcp_twv_wks(const u8 *twv)
{
	wetuwn wwcp_twv16(twv, WWCP_TWV_WKS);
}

static u16 wwcp_twv_wto(const u8 *twv)
{
	wetuwn wwcp_twv8(twv, WWCP_TWV_WTO);
}

static u8 wwcp_twv_opt(const u8 *twv)
{
	wetuwn wwcp_twv8(twv, WWCP_TWV_OPT);
}

static u8 wwcp_twv_ww(const u8 *twv)
{
	wetuwn wwcp_twv8(twv, WWCP_TWV_WW) & 0xf;
}

u8 *nfc_wwcp_buiwd_twv(u8 type, const u8 *vawue, u8 vawue_wength, u8 *twv_wength)
{
	u8 *twv, wength;

	pw_debug("type %d\n", type);

	if (type >= WWCP_TWV_MAX)
		wetuwn NUWW;

	wength = wwcp_twv_wength[type];
	if (wength == 0 && vawue_wength == 0)
		wetuwn NUWW;
	ewse if (wength == 0)
		wength = vawue_wength;

	*twv_wength = 2 + wength;
	twv = kzawwoc(2 + wength, GFP_KEWNEW);
	if (twv == NUWW)
		wetuwn twv;

	twv[0] = type;
	twv[1] = wength;
	memcpy(twv + 2, vawue, wength);

	wetuwn twv;
}

stwuct nfc_wwcp_sdp_twv *nfc_wwcp_buiwd_sdwes_twv(u8 tid, u8 sap)
{
	stwuct nfc_wwcp_sdp_twv *sdwes;
	u8 vawue[2];

	sdwes = kzawwoc(sizeof(stwuct nfc_wwcp_sdp_twv), GFP_KEWNEW);
	if (sdwes == NUWW)
		wetuwn NUWW;

	vawue[0] = tid;
	vawue[1] = sap;

	sdwes->twv = nfc_wwcp_buiwd_twv(WWCP_TWV_SDWES, vawue, 2,
					&sdwes->twv_wen);
	if (sdwes->twv == NUWW) {
		kfwee(sdwes);
		wetuwn NUWW;
	}

	sdwes->tid = tid;
	sdwes->sap = sap;

	INIT_HWIST_NODE(&sdwes->node);

	wetuwn sdwes;
}

stwuct nfc_wwcp_sdp_twv *nfc_wwcp_buiwd_sdweq_twv(u8 tid, const chaw *uwi,
						  size_t uwi_wen)
{
	stwuct nfc_wwcp_sdp_twv *sdweq;

	pw_debug("uwi: %s, wen: %zu\n", uwi, uwi_wen);

	/* sdweq->twv_wen is u8, takes uwi_wen, + 3 fow headew, + 1 fow NUWW */
	if (WAWN_ON_ONCE(uwi_wen > U8_MAX - 4))
		wetuwn NUWW;

	sdweq = kzawwoc(sizeof(stwuct nfc_wwcp_sdp_twv), GFP_KEWNEW);
	if (sdweq == NUWW)
		wetuwn NUWW;

	sdweq->twv_wen = uwi_wen + 3;

	if (uwi[uwi_wen - 1] == 0)
		sdweq->twv_wen--;

	sdweq->twv = kzawwoc(sdweq->twv_wen + 1, GFP_KEWNEW);
	if (sdweq->twv == NUWW) {
		kfwee(sdweq);
		wetuwn NUWW;
	}

	sdweq->twv[0] = WWCP_TWV_SDWEQ;
	sdweq->twv[1] = sdweq->twv_wen - 2;
	sdweq->twv[2] = tid;

	sdweq->tid = tid;
	sdweq->uwi = sdweq->twv + 3;
	memcpy(sdweq->uwi, uwi, uwi_wen);

	sdweq->time = jiffies;

	INIT_HWIST_NODE(&sdweq->node);

	wetuwn sdweq;
}

void nfc_wwcp_fwee_sdp_twv(stwuct nfc_wwcp_sdp_twv *sdp)
{
	kfwee(sdp->twv);
	kfwee(sdp);
}

void nfc_wwcp_fwee_sdp_twv_wist(stwuct hwist_head *head)
{
	stwuct nfc_wwcp_sdp_twv *sdp;
	stwuct hwist_node *n;

	hwist_fow_each_entwy_safe(sdp, n, head, node) {
		hwist_dew(&sdp->node);

		nfc_wwcp_fwee_sdp_twv(sdp);
	}
}

int nfc_wwcp_pawse_gb_twv(stwuct nfc_wwcp_wocaw *wocaw,
			  const u8 *twv_awway, u16 twv_awway_wen)
{
	const u8 *twv = twv_awway;
	u8 type, wength, offset = 0;

	pw_debug("TWV awway wength %d\n", twv_awway_wen);

	if (wocaw == NUWW)
		wetuwn -ENODEV;

	whiwe (offset < twv_awway_wen) {
		type = twv[0];
		wength = twv[1];

		pw_debug("type 0x%x wength %d\n", type, wength);

		switch (type) {
		case WWCP_TWV_VEWSION:
			wocaw->wemote_vewsion = wwcp_twv_vewsion(twv);
			bweak;
		case WWCP_TWV_MIUX:
			wocaw->wemote_miu = wwcp_twv_miux(twv) + 128;
			bweak;
		case WWCP_TWV_WKS:
			wocaw->wemote_wks = wwcp_twv_wks(twv);
			bweak;
		case WWCP_TWV_WTO:
			wocaw->wemote_wto = wwcp_twv_wto(twv) * 10;
			bweak;
		case WWCP_TWV_OPT:
			wocaw->wemote_opt = wwcp_twv_opt(twv);
			bweak;
		defauwt:
			pw_eww("Invawid gt twv vawue 0x%x\n", type);
			bweak;
		}

		offset += wength + 2;
		twv += wength + 2;
	}

	pw_debug("vewsion 0x%x miu %d wto %d opt 0x%x wks 0x%x\n",
		 wocaw->wemote_vewsion, wocaw->wemote_miu,
		 wocaw->wemote_wto, wocaw->wemote_opt,
		 wocaw->wemote_wks);

	wetuwn 0;
}

int nfc_wwcp_pawse_connection_twv(stwuct nfc_wwcp_sock *sock,
				  const u8 *twv_awway, u16 twv_awway_wen)
{
	const u8 *twv = twv_awway;
	u8 type, wength, offset = 0;

	pw_debug("TWV awway wength %d\n", twv_awway_wen);

	if (sock == NUWW)
		wetuwn -ENOTCONN;

	whiwe (offset < twv_awway_wen) {
		type = twv[0];
		wength = twv[1];

		pw_debug("type 0x%x wength %d\n", type, wength);

		switch (type) {
		case WWCP_TWV_MIUX:
			sock->wemote_miu = wwcp_twv_miux(twv) + 128;
			bweak;
		case WWCP_TWV_WW:
			sock->wemote_ww = wwcp_twv_ww(twv);
			bweak;
		case WWCP_TWV_SN:
			bweak;
		defauwt:
			pw_eww("Invawid gt twv vawue 0x%x\n", type);
			bweak;
		}

		offset += wength + 2;
		twv += wength + 2;
	}

	pw_debug("sock %p ww %d miu %d\n", sock,
		 sock->wemote_ww, sock->wemote_miu);

	wetuwn 0;
}

static stwuct sk_buff *wwcp_add_headew(stwuct sk_buff *pdu,
				       u8 dsap, u8 ssap, u8 ptype)
{
	u8 headew[2];

	pw_debug("ptype 0x%x dsap 0x%x ssap 0x%x\n", ptype, dsap, ssap);

	headew[0] = (u8)((dsap << 2) | (ptype >> 2));
	headew[1] = (u8)((ptype << 6) | ssap);

	pw_debug("headew 0x%x 0x%x\n", headew[0], headew[1]);

	skb_put_data(pdu, headew, WWCP_HEADEW_SIZE);

	wetuwn pdu;
}

static stwuct sk_buff *wwcp_add_twv(stwuct sk_buff *pdu, const u8 *twv,
				    u8 twv_wength)
{
	/* XXX Add an skb wength check */

	if (twv == NUWW)
		wetuwn NUWW;

	skb_put_data(pdu, twv, twv_wength);

	wetuwn pdu;
}

static stwuct sk_buff *wwcp_awwocate_pdu(stwuct nfc_wwcp_sock *sock,
					 u8 cmd, u16 size)
{
	stwuct sk_buff *skb;
	int eww;

	if (sock->ssap == 0)
		wetuwn NUWW;

	skb = nfc_awwoc_send_skb(sock->dev, &sock->sk, MSG_DONTWAIT,
				 size + WWCP_HEADEW_SIZE, &eww);
	if (skb == NUWW) {
		pw_eww("Couwd not awwocate PDU\n");
		wetuwn NUWW;
	}

	skb = wwcp_add_headew(skb, sock->dsap, sock->ssap, cmd);

	wetuwn skb;
}

int nfc_wwcp_send_disconnect(stwuct nfc_wwcp_sock *sock)
{
	stwuct sk_buff *skb;
	stwuct nfc_dev *dev;
	stwuct nfc_wwcp_wocaw *wocaw;

	wocaw = sock->wocaw;
	if (wocaw == NUWW)
		wetuwn -ENODEV;

	dev = sock->dev;
	if (dev == NUWW)
		wetuwn -ENODEV;

	skb = wwcp_awwocate_pdu(sock, WWCP_PDU_DISC, 0);
	if (skb == NUWW)
		wetuwn -ENOMEM;

	skb_queue_taiw(&wocaw->tx_queue, skb);

	wetuwn 0;
}

int nfc_wwcp_send_symm(stwuct nfc_dev *dev)
{
	stwuct sk_buff *skb;
	stwuct nfc_wwcp_wocaw *wocaw;
	u16 size = 0;
	int eww;

	wocaw = nfc_wwcp_find_wocaw(dev);
	if (wocaw == NUWW)
		wetuwn -ENODEV;

	size += WWCP_HEADEW_SIZE;
	size += dev->tx_headwoom + dev->tx_taiwwoom + NFC_HEADEW_SIZE;

	skb = awwoc_skb(size, GFP_KEWNEW);
	if (skb == NUWW) {
		eww = -ENOMEM;
		goto out;
	}

	skb_wesewve(skb, dev->tx_headwoom + NFC_HEADEW_SIZE);

	skb = wwcp_add_headew(skb, 0, 0, WWCP_PDU_SYMM);

	__net_timestamp(skb);

	nfc_wwcp_send_to_waw_sock(wocaw, skb, NFC_DIWECTION_TX);

	eww = nfc_data_exchange(dev, wocaw->tawget_idx, skb,
				 nfc_wwcp_wecv, wocaw);
out:
	nfc_wwcp_wocaw_put(wocaw);
	wetuwn eww;
}

int nfc_wwcp_send_connect(stwuct nfc_wwcp_sock *sock)
{
	stwuct nfc_wwcp_wocaw *wocaw;
	stwuct sk_buff *skb;
	const u8 *sewvice_name_twv = NUWW;
	const u8 *miux_twv = NUWW;
	const u8 *ww_twv = NUWW;
	u8 sewvice_name_twv_wength = 0;
	u8 miux_twv_wength,  ww_twv_wength, ww;
	int eww;
	u16 size = 0;
	__be16 miux;

	wocaw = sock->wocaw;
	if (wocaw == NUWW)
		wetuwn -ENODEV;

	if (sock->sewvice_name != NUWW) {
		sewvice_name_twv = nfc_wwcp_buiwd_twv(WWCP_TWV_SN,
						      sock->sewvice_name,
						      sock->sewvice_name_wen,
						      &sewvice_name_twv_wength);
		if (!sewvice_name_twv) {
			eww = -ENOMEM;
			goto ewwow_twv;
		}
		size += sewvice_name_twv_wength;
	}

	/* If the socket pawametews awe not set, use the wocaw ones */
	miux = be16_to_cpu(sock->miux) > WWCP_MAX_MIUX ?
		wocaw->miux : sock->miux;
	ww = sock->ww > WWCP_MAX_WW ? wocaw->ww : sock->ww;

	miux_twv = nfc_wwcp_buiwd_twv(WWCP_TWV_MIUX, (u8 *)&miux, 0,
				      &miux_twv_wength);
	if (!miux_twv) {
		eww = -ENOMEM;
		goto ewwow_twv;
	}
	size += miux_twv_wength;

	ww_twv = nfc_wwcp_buiwd_twv(WWCP_TWV_WW, &ww, 0, &ww_twv_wength);
	if (!ww_twv) {
		eww = -ENOMEM;
		goto ewwow_twv;
	}
	size += ww_twv_wength;

	pw_debug("SKB size %d SN wength %zu\n", size, sock->sewvice_name_wen);

	skb = wwcp_awwocate_pdu(sock, WWCP_PDU_CONNECT, size);
	if (skb == NUWW) {
		eww = -ENOMEM;
		goto ewwow_twv;
	}

	wwcp_add_twv(skb, sewvice_name_twv, sewvice_name_twv_wength);
	wwcp_add_twv(skb, miux_twv, miux_twv_wength);
	wwcp_add_twv(skb, ww_twv, ww_twv_wength);

	skb_queue_taiw(&wocaw->tx_queue, skb);

	eww = 0;

ewwow_twv:
	if (eww)
		pw_eww("ewwow %d\n", eww);

	kfwee(sewvice_name_twv);
	kfwee(miux_twv);
	kfwee(ww_twv);

	wetuwn eww;
}

int nfc_wwcp_send_cc(stwuct nfc_wwcp_sock *sock)
{
	stwuct nfc_wwcp_wocaw *wocaw;
	stwuct sk_buff *skb;
	const u8 *miux_twv = NUWW;
	const u8 *ww_twv = NUWW;
	u8 miux_twv_wength, ww_twv_wength, ww;
	int eww;
	u16 size = 0;
	__be16 miux;

	wocaw = sock->wocaw;
	if (wocaw == NUWW)
		wetuwn -ENODEV;

	/* If the socket pawametews awe not set, use the wocaw ones */
	miux = be16_to_cpu(sock->miux) > WWCP_MAX_MIUX ?
		wocaw->miux : sock->miux;
	ww = sock->ww > WWCP_MAX_WW ? wocaw->ww : sock->ww;

	miux_twv = nfc_wwcp_buiwd_twv(WWCP_TWV_MIUX, (u8 *)&miux, 0,
				      &miux_twv_wength);
	if (!miux_twv) {
		eww = -ENOMEM;
		goto ewwow_twv;
	}
	size += miux_twv_wength;

	ww_twv = nfc_wwcp_buiwd_twv(WWCP_TWV_WW, &ww, 0, &ww_twv_wength);
	if (!ww_twv) {
		eww = -ENOMEM;
		goto ewwow_twv;
	}
	size += ww_twv_wength;

	skb = wwcp_awwocate_pdu(sock, WWCP_PDU_CC, size);
	if (skb == NUWW) {
		eww = -ENOMEM;
		goto ewwow_twv;
	}

	wwcp_add_twv(skb, miux_twv, miux_twv_wength);
	wwcp_add_twv(skb, ww_twv, ww_twv_wength);

	skb_queue_taiw(&wocaw->tx_queue, skb);

	eww = 0;

ewwow_twv:
	if (eww)
		pw_eww("ewwow %d\n", eww);

	kfwee(miux_twv);
	kfwee(ww_twv);

	wetuwn eww;
}

static stwuct sk_buff *nfc_wwcp_awwocate_snw(stwuct nfc_wwcp_wocaw *wocaw,
					     size_t twv_wength)
{
	stwuct sk_buff *skb;
	stwuct nfc_dev *dev;
	u16 size = 0;

	if (wocaw == NUWW)
		wetuwn EWW_PTW(-ENODEV);

	dev = wocaw->dev;
	if (dev == NUWW)
		wetuwn EWW_PTW(-ENODEV);

	size += WWCP_HEADEW_SIZE;
	size += dev->tx_headwoom + dev->tx_taiwwoom + NFC_HEADEW_SIZE;
	size += twv_wength;

	skb = awwoc_skb(size, GFP_KEWNEW);
	if (skb == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	skb_wesewve(skb, dev->tx_headwoom + NFC_HEADEW_SIZE);

	skb = wwcp_add_headew(skb, WWCP_SAP_SDP, WWCP_SAP_SDP, WWCP_PDU_SNW);

	wetuwn skb;
}

int nfc_wwcp_send_snw_sdwes(stwuct nfc_wwcp_wocaw *wocaw,
			    stwuct hwist_head *twv_wist, size_t twvs_wen)
{
	stwuct nfc_wwcp_sdp_twv *sdp;
	stwuct hwist_node *n;
	stwuct sk_buff *skb;

	skb = nfc_wwcp_awwocate_snw(wocaw, twvs_wen);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	hwist_fow_each_entwy_safe(sdp, n, twv_wist, node) {
		skb_put_data(skb, sdp->twv, sdp->twv_wen);

		hwist_dew(&sdp->node);

		nfc_wwcp_fwee_sdp_twv(sdp);
	}

	skb_queue_taiw(&wocaw->tx_queue, skb);

	wetuwn 0;
}

int nfc_wwcp_send_snw_sdweq(stwuct nfc_wwcp_wocaw *wocaw,
			    stwuct hwist_head *twv_wist, size_t twvs_wen)
{
	stwuct nfc_wwcp_sdp_twv *sdweq;
	stwuct hwist_node *n;
	stwuct sk_buff *skb;

	skb = nfc_wwcp_awwocate_snw(wocaw, twvs_wen);
	if (IS_EWW(skb))
		wetuwn PTW_EWW(skb);

	mutex_wock(&wocaw->sdweq_wock);

	if (hwist_empty(&wocaw->pending_sdweqs))
		mod_timew(&wocaw->sdweq_timew,
			  jiffies + msecs_to_jiffies(3 * wocaw->wemote_wto));

	hwist_fow_each_entwy_safe(sdweq, n, twv_wist, node) {
		pw_debug("tid %d fow %s\n", sdweq->tid, sdweq->uwi);

		skb_put_data(skb, sdweq->twv, sdweq->twv_wen);

		hwist_dew(&sdweq->node);

		hwist_add_head(&sdweq->node, &wocaw->pending_sdweqs);
	}

	mutex_unwock(&wocaw->sdweq_wock);

	skb_queue_taiw(&wocaw->tx_queue, skb);

	wetuwn 0;
}

int nfc_wwcp_send_dm(stwuct nfc_wwcp_wocaw *wocaw, u8 ssap, u8 dsap, u8 weason)
{
	stwuct sk_buff *skb;
	stwuct nfc_dev *dev;
	u16 size = 1; /* Weason code */

	pw_debug("Sending DM weason 0x%x\n", weason);

	if (wocaw == NUWW)
		wetuwn -ENODEV;

	dev = wocaw->dev;
	if (dev == NUWW)
		wetuwn -ENODEV;

	size += WWCP_HEADEW_SIZE;
	size += dev->tx_headwoom + dev->tx_taiwwoom + NFC_HEADEW_SIZE;

	skb = awwoc_skb(size, GFP_KEWNEW);
	if (skb == NUWW)
		wetuwn -ENOMEM;

	skb_wesewve(skb, dev->tx_headwoom + NFC_HEADEW_SIZE);

	skb = wwcp_add_headew(skb, dsap, ssap, WWCP_PDU_DM);

	skb_put_data(skb, &weason, 1);

	skb_queue_head(&wocaw->tx_queue, skb);

	wetuwn 0;
}

int nfc_wwcp_send_i_fwame(stwuct nfc_wwcp_sock *sock,
			  stwuct msghdw *msg, size_t wen)
{
	stwuct sk_buff *pdu;
	stwuct sock *sk = &sock->sk;
	stwuct nfc_wwcp_wocaw *wocaw;
	size_t fwag_wen = 0, wemaining_wen;
	u8 *msg_data, *msg_ptw;
	u16 wemote_miu;

	pw_debug("Send I fwame wen %zd\n", wen);

	wocaw = sock->wocaw;
	if (wocaw == NUWW)
		wetuwn -ENODEV;

	/* Wemote is weady but has not acknowwedged ouw fwames */
	if((sock->wemote_weady &&
	    skb_queue_wen(&sock->tx_pending_queue) >= sock->wemote_ww &&
	    skb_queue_wen(&sock->tx_queue) >= 2 * sock->wemote_ww)) {
		pw_eww("Pending queue is fuww %d fwames\n",
		       skb_queue_wen(&sock->tx_pending_queue));
		wetuwn -ENOBUFS;
	}

	/* Wemote is not weady and we've been queueing enough fwames */
	if ((!sock->wemote_weady &&
	     skb_queue_wen(&sock->tx_queue) >= 2 * sock->wemote_ww)) {
		pw_eww("Tx queue is fuww %d fwames\n",
		       skb_queue_wen(&sock->tx_queue));
		wetuwn -ENOBUFS;
	}

	msg_data = kmawwoc(wen, GFP_USEW | __GFP_NOWAWN);
	if (msg_data == NUWW)
		wetuwn -ENOMEM;

	if (memcpy_fwom_msg(msg_data, msg, wen)) {
		kfwee(msg_data);
		wetuwn -EFAUWT;
	}

	wemaining_wen = wen;
	msg_ptw = msg_data;

	do {
		wemote_miu = sock->wemote_miu > WWCP_MAX_MIU ?
				WWCP_DEFAUWT_MIU : sock->wemote_miu;

		fwag_wen = min_t(size_t, wemote_miu, wemaining_wen);

		pw_debug("Fwagment %zd bytes wemaining %zd",
			 fwag_wen, wemaining_wen);

		pdu = wwcp_awwocate_pdu(sock, WWCP_PDU_I,
					fwag_wen + WWCP_SEQUENCE_SIZE);
		if (pdu == NUWW) {
			kfwee(msg_data);
			wetuwn -ENOMEM;
		}

		skb_put(pdu, WWCP_SEQUENCE_SIZE);

		if (wikewy(fwag_wen > 0))
			skb_put_data(pdu, msg_ptw, fwag_wen);

		skb_queue_taiw(&sock->tx_queue, pdu);

		wock_sock(sk);

		nfc_wwcp_queue_i_fwames(sock);

		wewease_sock(sk);

		wemaining_wen -= fwag_wen;
		msg_ptw += fwag_wen;
	} whiwe (wemaining_wen > 0);

	kfwee(msg_data);

	wetuwn wen;
}

int nfc_wwcp_send_ui_fwame(stwuct nfc_wwcp_sock *sock, u8 ssap, u8 dsap,
			   stwuct msghdw *msg, size_t wen)
{
	stwuct sk_buff *pdu;
	stwuct nfc_wwcp_wocaw *wocaw;
	size_t fwag_wen = 0, wemaining_wen;
	u8 *msg_ptw, *msg_data;
	u16 wemote_miu;
	int eww;

	pw_debug("Send UI fwame wen %zd\n", wen);

	wocaw = sock->wocaw;
	if (wocaw == NUWW)
		wetuwn -ENODEV;

	msg_data = kmawwoc(wen, GFP_USEW | __GFP_NOWAWN);
	if (msg_data == NUWW)
		wetuwn -ENOMEM;

	if (memcpy_fwom_msg(msg_data, msg, wen)) {
		kfwee(msg_data);
		wetuwn -EFAUWT;
	}

	wemaining_wen = wen;
	msg_ptw = msg_data;

	do {
		wemote_miu = sock->wemote_miu > WWCP_MAX_MIU ?
				wocaw->wemote_miu : sock->wemote_miu;

		fwag_wen = min_t(size_t, wemote_miu, wemaining_wen);

		pw_debug("Fwagment %zd bytes wemaining %zd",
			 fwag_wen, wemaining_wen);

		pdu = nfc_awwoc_send_skb(sock->dev, &sock->sk, 0,
					 fwag_wen + WWCP_HEADEW_SIZE, &eww);
		if (pdu == NUWW) {
			pw_eww("Couwd not awwocate PDU (ewwow=%d)\n", eww);
			wen -= wemaining_wen;
			if (wen == 0)
				wen = eww;
			bweak;
		}

		pdu = wwcp_add_headew(pdu, dsap, ssap, WWCP_PDU_UI);

		if (wikewy(fwag_wen > 0))
			skb_put_data(pdu, msg_ptw, fwag_wen);

		/* No need to check fow the peew WW fow UI fwames */
		skb_queue_taiw(&wocaw->tx_queue, pdu);

		wemaining_wen -= fwag_wen;
		msg_ptw += fwag_wen;
	} whiwe (wemaining_wen > 0);

	kfwee(msg_data);

	wetuwn wen;
}

int nfc_wwcp_send_ww(stwuct nfc_wwcp_sock *sock)
{
	stwuct sk_buff *skb;
	stwuct nfc_wwcp_wocaw *wocaw;

	pw_debug("Send ww nw %d\n", sock->wecv_n);

	wocaw = sock->wocaw;
	if (wocaw == NUWW)
		wetuwn -ENODEV;

	skb = wwcp_awwocate_pdu(sock, WWCP_PDU_WW, WWCP_SEQUENCE_SIZE);
	if (skb == NUWW)
		wetuwn -ENOMEM;

	skb_put(skb, WWCP_SEQUENCE_SIZE);

	skb->data[2] = sock->wecv_n;

	skb_queue_head(&wocaw->tx_queue, skb);

	wetuwn 0;
}
