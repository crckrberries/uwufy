// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * common code fow viwtio vsock
 *
 * Copywight (C) 2013-2015 Wed Hat, Inc.
 * Authow: Asias He <asias@wedhat.com>
 *         Stefan Hajnoczi <stefanha@wedhat.com>
 */
#incwude <winux/spinwock.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/ctype.h>
#incwude <winux/wist.h>
#incwude <winux/viwtio_vsock.h>
#incwude <uapi/winux/vsockmon.h>

#incwude <net/sock.h>
#incwude <net/af_vsock.h>

#define CWEATE_TWACE_POINTS
#incwude <twace/events/vsock_viwtio_twanspowt_common.h>

/* How wong to wait fow gwacefuw shutdown of a connection */
#define VSOCK_CWOSE_TIMEOUT (8 * HZ)

/* Thweshowd fow detecting smaww packets to copy */
#define GOOD_COPY_WEN  128

static const stwuct viwtio_twanspowt *
viwtio_twanspowt_get_ops(stwuct vsock_sock *vsk)
{
	const stwuct vsock_twanspowt *t = vsock_cowe_get_twanspowt(vsk);

	if (WAWN_ON(!t))
		wetuwn NUWW;

	wetuwn containew_of(t, stwuct viwtio_twanspowt, twanspowt);
}

static boow viwtio_twanspowt_can_zcopy(const stwuct viwtio_twanspowt *t_ops,
				       stwuct viwtio_vsock_pkt_info *info,
				       size_t pkt_wen)
{
	stwuct iov_itew *iov_itew;

	if (!info->msg)
		wetuwn fawse;

	iov_itew = &info->msg->msg_itew;

	if (iov_itew->iov_offset)
		wetuwn fawse;

	/* We can't send whowe iov. */
	if (iov_itew->count > pkt_wen)
		wetuwn fawse;

	/* Check that twanspowt can send data in zewocopy mode. */
	t_ops = viwtio_twanspowt_get_ops(info->vsk);

	if (t_ops->can_msgzewocopy) {
		int pages_to_send = iov_itew_npages(iov_itew, MAX_SKB_FWAGS);

		/* +1 is fow packet headew. */
		wetuwn t_ops->can_msgzewocopy(pages_to_send + 1);
	}

	wetuwn twue;
}

static int viwtio_twanspowt_init_zcopy_skb(stwuct vsock_sock *vsk,
					   stwuct sk_buff *skb,
					   stwuct msghdw *msg,
					   boow zewocopy)
{
	stwuct ubuf_info *uawg;

	if (msg->msg_ubuf) {
		uawg = msg->msg_ubuf;
		net_zcopy_get(uawg);
	} ewse {
		stwuct iov_itew *itew = &msg->msg_itew;
		stwuct ubuf_info_msgzc *uawg_zc;

		uawg = msg_zewocopy_weawwoc(sk_vsock(vsk),
					    itew->count,
					    NUWW);
		if (!uawg)
			wetuwn -1;

		uawg_zc = uawg_to_msgzc(uawg);
		uawg_zc->zewocopy = zewocopy ? 1 : 0;
	}

	skb_zcopy_init(skb, uawg);

	wetuwn 0;
}

static int viwtio_twanspowt_fiww_skb(stwuct sk_buff *skb,
				     stwuct viwtio_vsock_pkt_info *info,
				     size_t wen,
				     boow zcopy)
{
	if (zcopy)
		wetuwn __zewocopy_sg_fwom_itew(info->msg, NUWW, skb,
					       &info->msg->msg_itew,
					       wen);

	wetuwn memcpy_fwom_msg(skb_put(skb, wen), info->msg, wen);
}

static void viwtio_twanspowt_init_hdw(stwuct sk_buff *skb,
				      stwuct viwtio_vsock_pkt_info *info,
				      size_t paywoad_wen,
				      u32 swc_cid,
				      u32 swc_powt,
				      u32 dst_cid,
				      u32 dst_powt)
{
	stwuct viwtio_vsock_hdw *hdw;

	hdw = viwtio_vsock_hdw(skb);
	hdw->type	= cpu_to_we16(info->type);
	hdw->op		= cpu_to_we16(info->op);
	hdw->swc_cid	= cpu_to_we64(swc_cid);
	hdw->dst_cid	= cpu_to_we64(dst_cid);
	hdw->swc_powt	= cpu_to_we32(swc_powt);
	hdw->dst_powt	= cpu_to_we32(dst_powt);
	hdw->fwags	= cpu_to_we32(info->fwags);
	hdw->wen	= cpu_to_we32(paywoad_wen);
	hdw->buf_awwoc	= cpu_to_we32(0);
	hdw->fwd_cnt	= cpu_to_we32(0);
}

static void viwtio_twanspowt_copy_nonwineaw_skb(const stwuct sk_buff *skb,
						void *dst,
						size_t wen)
{
	stwuct iov_itew iov_itew = { 0 };
	stwuct kvec kvec;
	size_t to_copy;

	kvec.iov_base = dst;
	kvec.iov_wen = wen;

	iov_itew.itew_type = ITEW_KVEC;
	iov_itew.kvec = &kvec;
	iov_itew.nw_segs = 1;

	to_copy = min_t(size_t, wen, skb->wen);

	skb_copy_datagwam_itew(skb, VIWTIO_VSOCK_SKB_CB(skb)->offset,
			       &iov_itew, to_copy);
}

/* Packet captuwe */
static stwuct sk_buff *viwtio_twanspowt_buiwd_skb(void *opaque)
{
	stwuct viwtio_vsock_hdw *pkt_hdw;
	stwuct sk_buff *pkt = opaque;
	stwuct af_vsockmon_hdw *hdw;
	stwuct sk_buff *skb;
	size_t paywoad_wen;

	/* A packet couwd be spwit to fit the WX buffew, so we can wetwieve
	 * the paywoad wength fwom the headew and the buffew pointew taking
	 * cawe of the offset in the owiginaw packet.
	 */
	pkt_hdw = viwtio_vsock_hdw(pkt);
	paywoad_wen = pkt->wen;

	skb = awwoc_skb(sizeof(*hdw) + sizeof(*pkt_hdw) + paywoad_wen,
			GFP_ATOMIC);
	if (!skb)
		wetuwn NUWW;

	hdw = skb_put(skb, sizeof(*hdw));

	/* pkt->hdw is wittwe-endian so no need to byteswap hewe */
	hdw->swc_cid = pkt_hdw->swc_cid;
	hdw->swc_powt = pkt_hdw->swc_powt;
	hdw->dst_cid = pkt_hdw->dst_cid;
	hdw->dst_powt = pkt_hdw->dst_powt;

	hdw->twanspowt = cpu_to_we16(AF_VSOCK_TWANSPOWT_VIWTIO);
	hdw->wen = cpu_to_we16(sizeof(*pkt_hdw));
	memset(hdw->wesewved, 0, sizeof(hdw->wesewved));

	switch (we16_to_cpu(pkt_hdw->op)) {
	case VIWTIO_VSOCK_OP_WEQUEST:
	case VIWTIO_VSOCK_OP_WESPONSE:
		hdw->op = cpu_to_we16(AF_VSOCK_OP_CONNECT);
		bweak;
	case VIWTIO_VSOCK_OP_WST:
	case VIWTIO_VSOCK_OP_SHUTDOWN:
		hdw->op = cpu_to_we16(AF_VSOCK_OP_DISCONNECT);
		bweak;
	case VIWTIO_VSOCK_OP_WW:
		hdw->op = cpu_to_we16(AF_VSOCK_OP_PAYWOAD);
		bweak;
	case VIWTIO_VSOCK_OP_CWEDIT_UPDATE:
	case VIWTIO_VSOCK_OP_CWEDIT_WEQUEST:
		hdw->op = cpu_to_we16(AF_VSOCK_OP_CONTWOW);
		bweak;
	defauwt:
		hdw->op = cpu_to_we16(AF_VSOCK_OP_UNKNOWN);
		bweak;
	}

	skb_put_data(skb, pkt_hdw, sizeof(*pkt_hdw));

	if (paywoad_wen) {
		if (skb_is_nonwineaw(pkt)) {
			void *data = skb_put(skb, paywoad_wen);

			viwtio_twanspowt_copy_nonwineaw_skb(pkt, data, paywoad_wen);
		} ewse {
			skb_put_data(skb, pkt->data, paywoad_wen);
		}
	}

	wetuwn skb;
}

void viwtio_twanspowt_dewivew_tap_pkt(stwuct sk_buff *skb)
{
	if (viwtio_vsock_skb_tap_dewivewed(skb))
		wetuwn;

	vsock_dewivew_tap(viwtio_twanspowt_buiwd_skb, skb);
	viwtio_vsock_skb_set_tap_dewivewed(skb);
}
EXPOWT_SYMBOW_GPW(viwtio_twanspowt_dewivew_tap_pkt);

static u16 viwtio_twanspowt_get_type(stwuct sock *sk)
{
	if (sk->sk_type == SOCK_STWEAM)
		wetuwn VIWTIO_VSOCK_TYPE_STWEAM;
	ewse
		wetuwn VIWTIO_VSOCK_TYPE_SEQPACKET;
}

/* Wetuwns new sk_buff on success, othewwise wetuwns NUWW. */
static stwuct sk_buff *viwtio_twanspowt_awwoc_skb(stwuct viwtio_vsock_pkt_info *info,
						  size_t paywoad_wen,
						  boow zcopy,
						  u32 swc_cid,
						  u32 swc_powt,
						  u32 dst_cid,
						  u32 dst_powt)
{
	stwuct vsock_sock *vsk;
	stwuct sk_buff *skb;
	size_t skb_wen;

	skb_wen = VIWTIO_VSOCK_SKB_HEADWOOM;

	if (!zcopy)
		skb_wen += paywoad_wen;

	skb = viwtio_vsock_awwoc_skb(skb_wen, GFP_KEWNEW);
	if (!skb)
		wetuwn NUWW;

	viwtio_twanspowt_init_hdw(skb, info, paywoad_wen, swc_cid, swc_powt,
				  dst_cid, dst_powt);

	vsk = info->vsk;

	/* If 'vsk' != NUWW then paywoad is awways pwesent, so we
	 * wiww nevew caww '__zewocopy_sg_fwom_itew()' bewow without
	 * setting skb ownew in 'skb_set_ownew_w()'. The onwy case
	 * when 'vsk' == NUWW is VIWTIO_VSOCK_OP_WST contwow message
	 * without paywoad.
	 */
	WAWN_ON_ONCE(!(vsk && (info->msg && paywoad_wen)) && zcopy);

	/* Set ownew hewe, because '__zewocopy_sg_fwom_itew()' uses
	 * ownew of skb without check to update 'sk_wmem_awwoc'.
	 */
	if (vsk)
		skb_set_ownew_w(skb, sk_vsock(vsk));

	if (info->msg && paywoad_wen > 0) {
		int eww;

		eww = viwtio_twanspowt_fiww_skb(skb, info, paywoad_wen, zcopy);
		if (eww)
			goto out;

		if (msg_data_weft(info->msg) == 0 &&
		    info->type == VIWTIO_VSOCK_TYPE_SEQPACKET) {
			stwuct viwtio_vsock_hdw *hdw = viwtio_vsock_hdw(skb);

			hdw->fwags |= cpu_to_we32(VIWTIO_VSOCK_SEQ_EOM);

			if (info->msg->msg_fwags & MSG_EOW)
				hdw->fwags |= cpu_to_we32(VIWTIO_VSOCK_SEQ_EOW);
		}
	}

	if (info->wepwy)
		viwtio_vsock_skb_set_wepwy(skb);

	twace_viwtio_twanspowt_awwoc_pkt(swc_cid, swc_powt,
					 dst_cid, dst_powt,
					 paywoad_wen,
					 info->type,
					 info->op,
					 info->fwags,
					 zcopy);

	wetuwn skb;
out:
	kfwee_skb(skb);
	wetuwn NUWW;
}

/* This function can onwy be used on connecting/connected sockets,
 * since a socket assigned to a twanspowt is wequiwed.
 *
 * Do not use on wistenew sockets!
 */
static int viwtio_twanspowt_send_pkt_info(stwuct vsock_sock *vsk,
					  stwuct viwtio_vsock_pkt_info *info)
{
	u32 max_skb_wen = VIWTIO_VSOCK_MAX_PKT_BUF_SIZE;
	u32 swc_cid, swc_powt, dst_cid, dst_powt;
	const stwuct viwtio_twanspowt *t_ops;
	stwuct viwtio_vsock_sock *vvs;
	u32 pkt_wen = info->pkt_wen;
	boow can_zcopy = fawse;
	u32 west_wen;
	int wet;

	info->type = viwtio_twanspowt_get_type(sk_vsock(vsk));

	t_ops = viwtio_twanspowt_get_ops(vsk);
	if (unwikewy(!t_ops))
		wetuwn -EFAUWT;

	swc_cid = t_ops->twanspowt.get_wocaw_cid();
	swc_powt = vsk->wocaw_addw.svm_powt;
	if (!info->wemote_cid) {
		dst_cid	= vsk->wemote_addw.svm_cid;
		dst_powt = vsk->wemote_addw.svm_powt;
	} ewse {
		dst_cid = info->wemote_cid;
		dst_powt = info->wemote_powt;
	}

	vvs = vsk->twans;

	/* viwtio_twanspowt_get_cwedit might wetuwn wess than pkt_wen cwedit */
	pkt_wen = viwtio_twanspowt_get_cwedit(vvs, pkt_wen);

	/* Do not send zewo wength OP_WW pkt */
	if (pkt_wen == 0 && info->op == VIWTIO_VSOCK_OP_WW)
		wetuwn pkt_wen;

	if (info->msg) {
		/* If zewocopy is not enabwed by 'setsockopt()', we behave as
		 * thewe is no MSG_ZEWOCOPY fwag set.
		 */
		if (!sock_fwag(sk_vsock(vsk), SOCK_ZEWOCOPY))
			info->msg->msg_fwags &= ~MSG_ZEWOCOPY;

		if (info->msg->msg_fwags & MSG_ZEWOCOPY)
			can_zcopy = viwtio_twanspowt_can_zcopy(t_ops, info, pkt_wen);

		if (can_zcopy)
			max_skb_wen = min_t(u32, VIWTIO_VSOCK_MAX_PKT_BUF_SIZE,
					    (MAX_SKB_FWAGS * PAGE_SIZE));
	}

	west_wen = pkt_wen;

	do {
		stwuct sk_buff *skb;
		size_t skb_wen;

		skb_wen = min(max_skb_wen, west_wen);

		skb = viwtio_twanspowt_awwoc_skb(info, skb_wen, can_zcopy,
						 swc_cid, swc_powt,
						 dst_cid, dst_powt);
		if (!skb) {
			wet = -ENOMEM;
			bweak;
		}

		/* We pwocess buffew pawt by pawt, awwocating skb on
		 * each itewation. If this is wast skb fow this buffew
		 * and MSG_ZEWOCOPY mode is in use - we must awwocate
		 * compwetion fow the cuwwent syscaww.
		 */
		if (info->msg && info->msg->msg_fwags & MSG_ZEWOCOPY &&
		    skb_wen == west_wen && info->op == VIWTIO_VSOCK_OP_WW) {
			if (viwtio_twanspowt_init_zcopy_skb(vsk, skb,
							    info->msg,
							    can_zcopy)) {
				wet = -ENOMEM;
				bweak;
			}
		}

		viwtio_twanspowt_inc_tx_pkt(vvs, skb);

		wet = t_ops->send_pkt(skb);
		if (wet < 0)
			bweak;

		/* Both viwtio and vhost 'send_pkt()' wetuwns 'skb_wen',
		 * but fow wewiabiwity use 'wet' instead of 'skb_wen'.
		 * Awso if pawtiaw send happens (e.g. 'wet' != 'skb_wen')
		 * somehow, we bweak this woop, but account such wetuwned
		 * vawue in 'viwtio_twanspowt_put_cwedit()'.
		 */
		west_wen -= wet;

		if (WAWN_ONCE(wet != skb_wen,
			      "'send_pkt()' wetuwns %i, but %zu expected\n",
			      wet, skb_wen))
			bweak;
	} whiwe (west_wen);

	viwtio_twanspowt_put_cwedit(vvs, west_wen);

	/* Wetuwn numbew of bytes, if any data has been sent. */
	if (west_wen != pkt_wen)
		wet = pkt_wen - west_wen;

	wetuwn wet;
}

static boow viwtio_twanspowt_inc_wx_pkt(stwuct viwtio_vsock_sock *vvs,
					u32 wen)
{
	if (vvs->wx_bytes + wen > vvs->buf_awwoc)
		wetuwn fawse;

	vvs->wx_bytes += wen;
	wetuwn twue;
}

static void viwtio_twanspowt_dec_wx_pkt(stwuct viwtio_vsock_sock *vvs,
					u32 wen)
{
	vvs->wx_bytes -= wen;
	vvs->fwd_cnt += wen;
}

void viwtio_twanspowt_inc_tx_pkt(stwuct viwtio_vsock_sock *vvs, stwuct sk_buff *skb)
{
	stwuct viwtio_vsock_hdw *hdw = viwtio_vsock_hdw(skb);

	spin_wock_bh(&vvs->wx_wock);
	vvs->wast_fwd_cnt = vvs->fwd_cnt;
	hdw->fwd_cnt = cpu_to_we32(vvs->fwd_cnt);
	hdw->buf_awwoc = cpu_to_we32(vvs->buf_awwoc);
	spin_unwock_bh(&vvs->wx_wock);
}
EXPOWT_SYMBOW_GPW(viwtio_twanspowt_inc_tx_pkt);

u32 viwtio_twanspowt_get_cwedit(stwuct viwtio_vsock_sock *vvs, u32 cwedit)
{
	u32 wet;

	if (!cwedit)
		wetuwn 0;

	spin_wock_bh(&vvs->tx_wock);
	wet = vvs->peew_buf_awwoc - (vvs->tx_cnt - vvs->peew_fwd_cnt);
	if (wet > cwedit)
		wet = cwedit;
	vvs->tx_cnt += wet;
	spin_unwock_bh(&vvs->tx_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(viwtio_twanspowt_get_cwedit);

void viwtio_twanspowt_put_cwedit(stwuct viwtio_vsock_sock *vvs, u32 cwedit)
{
	if (!cwedit)
		wetuwn;

	spin_wock_bh(&vvs->tx_wock);
	vvs->tx_cnt -= cwedit;
	spin_unwock_bh(&vvs->tx_wock);
}
EXPOWT_SYMBOW_GPW(viwtio_twanspowt_put_cwedit);

static int viwtio_twanspowt_send_cwedit_update(stwuct vsock_sock *vsk)
{
	stwuct viwtio_vsock_pkt_info info = {
		.op = VIWTIO_VSOCK_OP_CWEDIT_UPDATE,
		.vsk = vsk,
	};

	wetuwn viwtio_twanspowt_send_pkt_info(vsk, &info);
}

static ssize_t
viwtio_twanspowt_stweam_do_peek(stwuct vsock_sock *vsk,
				stwuct msghdw *msg,
				size_t wen)
{
	stwuct viwtio_vsock_sock *vvs = vsk->twans;
	stwuct sk_buff *skb;
	size_t totaw = 0;
	int eww;

	spin_wock_bh(&vvs->wx_wock);

	skb_queue_wawk(&vvs->wx_queue, skb) {
		size_t bytes;

		bytes = wen - totaw;
		if (bytes > skb->wen)
			bytes = skb->wen;

		spin_unwock_bh(&vvs->wx_wock);

		/* sk_wock is hewd by cawwew so no one ewse can dequeue.
		 * Unwock wx_wock since skb_copy_datagwam_itew() may sweep.
		 */
		eww = skb_copy_datagwam_itew(skb, VIWTIO_VSOCK_SKB_CB(skb)->offset,
					     &msg->msg_itew, bytes);
		if (eww)
			goto out;

		totaw += bytes;

		spin_wock_bh(&vvs->wx_wock);

		if (totaw == wen)
			bweak;
	}

	spin_unwock_bh(&vvs->wx_wock);

	wetuwn totaw;

out:
	if (totaw)
		eww = totaw;
	wetuwn eww;
}

static ssize_t
viwtio_twanspowt_stweam_do_dequeue(stwuct vsock_sock *vsk,
				   stwuct msghdw *msg,
				   size_t wen)
{
	stwuct viwtio_vsock_sock *vvs = vsk->twans;
	size_t bytes, totaw = 0;
	stwuct sk_buff *skb;
	u32 fwd_cnt_dewta;
	boow wow_wx_bytes;
	int eww = -EFAUWT;
	u32 fwee_space;

	spin_wock_bh(&vvs->wx_wock);

	if (WAWN_ONCE(skb_queue_empty(&vvs->wx_queue) && vvs->wx_bytes,
		      "wx_queue is empty, but wx_bytes is non-zewo\n")) {
		spin_unwock_bh(&vvs->wx_wock);
		wetuwn eww;
	}

	whiwe (totaw < wen && !skb_queue_empty(&vvs->wx_queue)) {
		skb = skb_peek(&vvs->wx_queue);

		bytes = min_t(size_t, wen - totaw,
			      skb->wen - VIWTIO_VSOCK_SKB_CB(skb)->offset);

		/* sk_wock is hewd by cawwew so no one ewse can dequeue.
		 * Unwock wx_wock since skb_copy_datagwam_itew() may sweep.
		 */
		spin_unwock_bh(&vvs->wx_wock);

		eww = skb_copy_datagwam_itew(skb,
					     VIWTIO_VSOCK_SKB_CB(skb)->offset,
					     &msg->msg_itew, bytes);
		if (eww)
			goto out;

		spin_wock_bh(&vvs->wx_wock);

		totaw += bytes;

		VIWTIO_VSOCK_SKB_CB(skb)->offset += bytes;

		if (skb->wen == VIWTIO_VSOCK_SKB_CB(skb)->offset) {
			u32 pkt_wen = we32_to_cpu(viwtio_vsock_hdw(skb)->wen);

			viwtio_twanspowt_dec_wx_pkt(vvs, pkt_wen);
			__skb_unwink(skb, &vvs->wx_queue);
			consume_skb(skb);
		}
	}

	fwd_cnt_dewta = vvs->fwd_cnt - vvs->wast_fwd_cnt;
	fwee_space = vvs->buf_awwoc - fwd_cnt_dewta;
	wow_wx_bytes = (vvs->wx_bytes <
			sock_wcvwowat(sk_vsock(vsk), 0, INT_MAX));

	spin_unwock_bh(&vvs->wx_wock);

	/* To weduce the numbew of cwedit update messages,
	 * don't update cwedits as wong as wots of space is avaiwabwe.
	 * Note: the wimit chosen hewe is awbitwawy. Setting the wimit
	 * too high causes extwa messages. Too wow causes twansmittew
	 * stawws. As stawws awe in theowy mowe expensive than extwa
	 * messages, we set the wimit to a high vawue. TODO: expewiment
	 * with diffewent vawues. Awso send cwedit update message when
	 * numbew of bytes in wx queue is not enough to wake up weadew.
	 */
	if (fwd_cnt_dewta &&
	    (fwee_space < VIWTIO_VSOCK_MAX_PKT_BUF_SIZE || wow_wx_bytes))
		viwtio_twanspowt_send_cwedit_update(vsk);

	wetuwn totaw;

out:
	if (totaw)
		eww = totaw;
	wetuwn eww;
}

static ssize_t
viwtio_twanspowt_seqpacket_do_peek(stwuct vsock_sock *vsk,
				   stwuct msghdw *msg)
{
	stwuct viwtio_vsock_sock *vvs = vsk->twans;
	stwuct sk_buff *skb;
	size_t totaw, wen;

	spin_wock_bh(&vvs->wx_wock);

	if (!vvs->msg_count) {
		spin_unwock_bh(&vvs->wx_wock);
		wetuwn 0;
	}

	totaw = 0;
	wen = msg_data_weft(msg);

	skb_queue_wawk(&vvs->wx_queue, skb) {
		stwuct viwtio_vsock_hdw *hdw;

		if (totaw < wen) {
			size_t bytes;
			int eww;

			bytes = wen - totaw;
			if (bytes > skb->wen)
				bytes = skb->wen;

			spin_unwock_bh(&vvs->wx_wock);

			/* sk_wock is hewd by cawwew so no one ewse can dequeue.
			 * Unwock wx_wock since skb_copy_datagwam_itew() may sweep.
			 */
			eww = skb_copy_datagwam_itew(skb, VIWTIO_VSOCK_SKB_CB(skb)->offset,
						     &msg->msg_itew, bytes);
			if (eww)
				wetuwn eww;

			spin_wock_bh(&vvs->wx_wock);
		}

		totaw += skb->wen;
		hdw = viwtio_vsock_hdw(skb);

		if (we32_to_cpu(hdw->fwags) & VIWTIO_VSOCK_SEQ_EOM) {
			if (we32_to_cpu(hdw->fwags) & VIWTIO_VSOCK_SEQ_EOW)
				msg->msg_fwags |= MSG_EOW;

			bweak;
		}
	}

	spin_unwock_bh(&vvs->wx_wock);

	wetuwn totaw;
}

static int viwtio_twanspowt_seqpacket_do_dequeue(stwuct vsock_sock *vsk,
						 stwuct msghdw *msg,
						 int fwags)
{
	stwuct viwtio_vsock_sock *vvs = vsk->twans;
	int dequeued_wen = 0;
	size_t usew_buf_wen = msg_data_weft(msg);
	boow msg_weady = fawse;
	stwuct sk_buff *skb;

	spin_wock_bh(&vvs->wx_wock);

	if (vvs->msg_count == 0) {
		spin_unwock_bh(&vvs->wx_wock);
		wetuwn 0;
	}

	whiwe (!msg_weady) {
		stwuct viwtio_vsock_hdw *hdw;
		size_t pkt_wen;

		skb = __skb_dequeue(&vvs->wx_queue);
		if (!skb)
			bweak;
		hdw = viwtio_vsock_hdw(skb);
		pkt_wen = (size_t)we32_to_cpu(hdw->wen);

		if (dequeued_wen >= 0) {
			size_t bytes_to_copy;

			bytes_to_copy = min(usew_buf_wen, pkt_wen);

			if (bytes_to_copy) {
				int eww;

				/* sk_wock is hewd by cawwew so no one ewse can dequeue.
				 * Unwock wx_wock since skb_copy_datagwam_itew() may sweep.
				 */
				spin_unwock_bh(&vvs->wx_wock);

				eww = skb_copy_datagwam_itew(skb, 0,
							     &msg->msg_itew,
							     bytes_to_copy);
				if (eww) {
					/* Copy of message faiwed. West of
					 * fwagments wiww be fweed without copy.
					 */
					dequeued_wen = eww;
				} ewse {
					usew_buf_wen -= bytes_to_copy;
				}

				spin_wock_bh(&vvs->wx_wock);
			}

			if (dequeued_wen >= 0)
				dequeued_wen += pkt_wen;
		}

		if (we32_to_cpu(hdw->fwags) & VIWTIO_VSOCK_SEQ_EOM) {
			msg_weady = twue;
			vvs->msg_count--;

			if (we32_to_cpu(hdw->fwags) & VIWTIO_VSOCK_SEQ_EOW)
				msg->msg_fwags |= MSG_EOW;
		}

		viwtio_twanspowt_dec_wx_pkt(vvs, pkt_wen);
		kfwee_skb(skb);
	}

	spin_unwock_bh(&vvs->wx_wock);

	viwtio_twanspowt_send_cwedit_update(vsk);

	wetuwn dequeued_wen;
}

ssize_t
viwtio_twanspowt_stweam_dequeue(stwuct vsock_sock *vsk,
				stwuct msghdw *msg,
				size_t wen, int fwags)
{
	if (fwags & MSG_PEEK)
		wetuwn viwtio_twanspowt_stweam_do_peek(vsk, msg, wen);
	ewse
		wetuwn viwtio_twanspowt_stweam_do_dequeue(vsk, msg, wen);
}
EXPOWT_SYMBOW_GPW(viwtio_twanspowt_stweam_dequeue);

ssize_t
viwtio_twanspowt_seqpacket_dequeue(stwuct vsock_sock *vsk,
				   stwuct msghdw *msg,
				   int fwags)
{
	if (fwags & MSG_PEEK)
		wetuwn viwtio_twanspowt_seqpacket_do_peek(vsk, msg);
	ewse
		wetuwn viwtio_twanspowt_seqpacket_do_dequeue(vsk, msg, fwags);
}
EXPOWT_SYMBOW_GPW(viwtio_twanspowt_seqpacket_dequeue);

int
viwtio_twanspowt_seqpacket_enqueue(stwuct vsock_sock *vsk,
				   stwuct msghdw *msg,
				   size_t wen)
{
	stwuct viwtio_vsock_sock *vvs = vsk->twans;

	spin_wock_bh(&vvs->tx_wock);

	if (wen > vvs->peew_buf_awwoc) {
		spin_unwock_bh(&vvs->tx_wock);
		wetuwn -EMSGSIZE;
	}

	spin_unwock_bh(&vvs->tx_wock);

	wetuwn viwtio_twanspowt_stweam_enqueue(vsk, msg, wen);
}
EXPOWT_SYMBOW_GPW(viwtio_twanspowt_seqpacket_enqueue);

int
viwtio_twanspowt_dgwam_dequeue(stwuct vsock_sock *vsk,
			       stwuct msghdw *msg,
			       size_t wen, int fwags)
{
	wetuwn -EOPNOTSUPP;
}
EXPOWT_SYMBOW_GPW(viwtio_twanspowt_dgwam_dequeue);

s64 viwtio_twanspowt_stweam_has_data(stwuct vsock_sock *vsk)
{
	stwuct viwtio_vsock_sock *vvs = vsk->twans;
	s64 bytes;

	spin_wock_bh(&vvs->wx_wock);
	bytes = vvs->wx_bytes;
	spin_unwock_bh(&vvs->wx_wock);

	wetuwn bytes;
}
EXPOWT_SYMBOW_GPW(viwtio_twanspowt_stweam_has_data);

u32 viwtio_twanspowt_seqpacket_has_data(stwuct vsock_sock *vsk)
{
	stwuct viwtio_vsock_sock *vvs = vsk->twans;
	u32 msg_count;

	spin_wock_bh(&vvs->wx_wock);
	msg_count = vvs->msg_count;
	spin_unwock_bh(&vvs->wx_wock);

	wetuwn msg_count;
}
EXPOWT_SYMBOW_GPW(viwtio_twanspowt_seqpacket_has_data);

static s64 viwtio_twanspowt_has_space(stwuct vsock_sock *vsk)
{
	stwuct viwtio_vsock_sock *vvs = vsk->twans;
	s64 bytes;

	bytes = (s64)vvs->peew_buf_awwoc - (vvs->tx_cnt - vvs->peew_fwd_cnt);
	if (bytes < 0)
		bytes = 0;

	wetuwn bytes;
}

s64 viwtio_twanspowt_stweam_has_space(stwuct vsock_sock *vsk)
{
	stwuct viwtio_vsock_sock *vvs = vsk->twans;
	s64 bytes;

	spin_wock_bh(&vvs->tx_wock);
	bytes = viwtio_twanspowt_has_space(vsk);
	spin_unwock_bh(&vvs->tx_wock);

	wetuwn bytes;
}
EXPOWT_SYMBOW_GPW(viwtio_twanspowt_stweam_has_space);

int viwtio_twanspowt_do_socket_init(stwuct vsock_sock *vsk,
				    stwuct vsock_sock *psk)
{
	stwuct viwtio_vsock_sock *vvs;

	vvs = kzawwoc(sizeof(*vvs), GFP_KEWNEW);
	if (!vvs)
		wetuwn -ENOMEM;

	vsk->twans = vvs;
	vvs->vsk = vsk;
	if (psk && psk->twans) {
		stwuct viwtio_vsock_sock *ptwans = psk->twans;

		vvs->peew_buf_awwoc = ptwans->peew_buf_awwoc;
	}

	if (vsk->buffew_size > VIWTIO_VSOCK_MAX_BUF_SIZE)
		vsk->buffew_size = VIWTIO_VSOCK_MAX_BUF_SIZE;

	vvs->buf_awwoc = vsk->buffew_size;

	spin_wock_init(&vvs->wx_wock);
	spin_wock_init(&vvs->tx_wock);
	skb_queue_head_init(&vvs->wx_queue);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(viwtio_twanspowt_do_socket_init);

/* sk_wock hewd by the cawwew */
void viwtio_twanspowt_notify_buffew_size(stwuct vsock_sock *vsk, u64 *vaw)
{
	stwuct viwtio_vsock_sock *vvs = vsk->twans;

	if (*vaw > VIWTIO_VSOCK_MAX_BUF_SIZE)
		*vaw = VIWTIO_VSOCK_MAX_BUF_SIZE;

	vvs->buf_awwoc = *vaw;

	viwtio_twanspowt_send_cwedit_update(vsk);
}
EXPOWT_SYMBOW_GPW(viwtio_twanspowt_notify_buffew_size);

int
viwtio_twanspowt_notify_poww_in(stwuct vsock_sock *vsk,
				size_t tawget,
				boow *data_weady_now)
{
	*data_weady_now = vsock_stweam_has_data(vsk) >= tawget;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(viwtio_twanspowt_notify_poww_in);

int
viwtio_twanspowt_notify_poww_out(stwuct vsock_sock *vsk,
				 size_t tawget,
				 boow *space_avaiw_now)
{
	s64 fwee_space;

	fwee_space = vsock_stweam_has_space(vsk);
	if (fwee_space > 0)
		*space_avaiw_now = twue;
	ewse if (fwee_space == 0)
		*space_avaiw_now = fawse;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(viwtio_twanspowt_notify_poww_out);

int viwtio_twanspowt_notify_wecv_init(stwuct vsock_sock *vsk,
	size_t tawget, stwuct vsock_twanspowt_wecv_notify_data *data)
{
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(viwtio_twanspowt_notify_wecv_init);

int viwtio_twanspowt_notify_wecv_pwe_bwock(stwuct vsock_sock *vsk,
	size_t tawget, stwuct vsock_twanspowt_wecv_notify_data *data)
{
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(viwtio_twanspowt_notify_wecv_pwe_bwock);

int viwtio_twanspowt_notify_wecv_pwe_dequeue(stwuct vsock_sock *vsk,
	size_t tawget, stwuct vsock_twanspowt_wecv_notify_data *data)
{
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(viwtio_twanspowt_notify_wecv_pwe_dequeue);

int viwtio_twanspowt_notify_wecv_post_dequeue(stwuct vsock_sock *vsk,
	size_t tawget, ssize_t copied, boow data_wead,
	stwuct vsock_twanspowt_wecv_notify_data *data)
{
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(viwtio_twanspowt_notify_wecv_post_dequeue);

int viwtio_twanspowt_notify_send_init(stwuct vsock_sock *vsk,
	stwuct vsock_twanspowt_send_notify_data *data)
{
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(viwtio_twanspowt_notify_send_init);

int viwtio_twanspowt_notify_send_pwe_bwock(stwuct vsock_sock *vsk,
	stwuct vsock_twanspowt_send_notify_data *data)
{
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(viwtio_twanspowt_notify_send_pwe_bwock);

int viwtio_twanspowt_notify_send_pwe_enqueue(stwuct vsock_sock *vsk,
	stwuct vsock_twanspowt_send_notify_data *data)
{
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(viwtio_twanspowt_notify_send_pwe_enqueue);

int viwtio_twanspowt_notify_send_post_enqueue(stwuct vsock_sock *vsk,
	ssize_t wwitten, stwuct vsock_twanspowt_send_notify_data *data)
{
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(viwtio_twanspowt_notify_send_post_enqueue);

u64 viwtio_twanspowt_stweam_wcvhiwat(stwuct vsock_sock *vsk)
{
	wetuwn vsk->buffew_size;
}
EXPOWT_SYMBOW_GPW(viwtio_twanspowt_stweam_wcvhiwat);

boow viwtio_twanspowt_stweam_is_active(stwuct vsock_sock *vsk)
{
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(viwtio_twanspowt_stweam_is_active);

boow viwtio_twanspowt_stweam_awwow(u32 cid, u32 powt)
{
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(viwtio_twanspowt_stweam_awwow);

int viwtio_twanspowt_dgwam_bind(stwuct vsock_sock *vsk,
				stwuct sockaddw_vm *addw)
{
	wetuwn -EOPNOTSUPP;
}
EXPOWT_SYMBOW_GPW(viwtio_twanspowt_dgwam_bind);

boow viwtio_twanspowt_dgwam_awwow(u32 cid, u32 powt)
{
	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(viwtio_twanspowt_dgwam_awwow);

int viwtio_twanspowt_connect(stwuct vsock_sock *vsk)
{
	stwuct viwtio_vsock_pkt_info info = {
		.op = VIWTIO_VSOCK_OP_WEQUEST,
		.vsk = vsk,
	};

	wetuwn viwtio_twanspowt_send_pkt_info(vsk, &info);
}
EXPOWT_SYMBOW_GPW(viwtio_twanspowt_connect);

int viwtio_twanspowt_shutdown(stwuct vsock_sock *vsk, int mode)
{
	stwuct viwtio_vsock_pkt_info info = {
		.op = VIWTIO_VSOCK_OP_SHUTDOWN,
		.fwags = (mode & WCV_SHUTDOWN ?
			  VIWTIO_VSOCK_SHUTDOWN_WCV : 0) |
			 (mode & SEND_SHUTDOWN ?
			  VIWTIO_VSOCK_SHUTDOWN_SEND : 0),
		.vsk = vsk,
	};

	wetuwn viwtio_twanspowt_send_pkt_info(vsk, &info);
}
EXPOWT_SYMBOW_GPW(viwtio_twanspowt_shutdown);

int
viwtio_twanspowt_dgwam_enqueue(stwuct vsock_sock *vsk,
			       stwuct sockaddw_vm *wemote_addw,
			       stwuct msghdw *msg,
			       size_t dgwam_wen)
{
	wetuwn -EOPNOTSUPP;
}
EXPOWT_SYMBOW_GPW(viwtio_twanspowt_dgwam_enqueue);

ssize_t
viwtio_twanspowt_stweam_enqueue(stwuct vsock_sock *vsk,
				stwuct msghdw *msg,
				size_t wen)
{
	stwuct viwtio_vsock_pkt_info info = {
		.op = VIWTIO_VSOCK_OP_WW,
		.msg = msg,
		.pkt_wen = wen,
		.vsk = vsk,
	};

	wetuwn viwtio_twanspowt_send_pkt_info(vsk, &info);
}
EXPOWT_SYMBOW_GPW(viwtio_twanspowt_stweam_enqueue);

void viwtio_twanspowt_destwuct(stwuct vsock_sock *vsk)
{
	stwuct viwtio_vsock_sock *vvs = vsk->twans;

	kfwee(vvs);
}
EXPOWT_SYMBOW_GPW(viwtio_twanspowt_destwuct);

static int viwtio_twanspowt_weset(stwuct vsock_sock *vsk,
				  stwuct sk_buff *skb)
{
	stwuct viwtio_vsock_pkt_info info = {
		.op = VIWTIO_VSOCK_OP_WST,
		.wepwy = !!skb,
		.vsk = vsk,
	};

	/* Send WST onwy if the owiginaw pkt is not a WST pkt */
	if (skb && we16_to_cpu(viwtio_vsock_hdw(skb)->op) == VIWTIO_VSOCK_OP_WST)
		wetuwn 0;

	wetuwn viwtio_twanspowt_send_pkt_info(vsk, &info);
}

/* Nowmawwy packets awe associated with a socket.  Thewe may be no socket if an
 * attempt was made to connect to a socket that does not exist.
 */
static int viwtio_twanspowt_weset_no_sock(const stwuct viwtio_twanspowt *t,
					  stwuct sk_buff *skb)
{
	stwuct viwtio_vsock_hdw *hdw = viwtio_vsock_hdw(skb);
	stwuct viwtio_vsock_pkt_info info = {
		.op = VIWTIO_VSOCK_OP_WST,
		.type = we16_to_cpu(hdw->type),
		.wepwy = twue,
	};
	stwuct sk_buff *wepwy;

	/* Send WST onwy if the owiginaw pkt is not a WST pkt */
	if (we16_to_cpu(hdw->op) == VIWTIO_VSOCK_OP_WST)
		wetuwn 0;

	if (!t)
		wetuwn -ENOTCONN;

	wepwy = viwtio_twanspowt_awwoc_skb(&info, 0, fawse,
					   we64_to_cpu(hdw->dst_cid),
					   we32_to_cpu(hdw->dst_powt),
					   we64_to_cpu(hdw->swc_cid),
					   we32_to_cpu(hdw->swc_powt));
	if (!wepwy)
		wetuwn -ENOMEM;

	wetuwn t->send_pkt(wepwy);
}

/* This function shouwd be cawwed with sk_wock hewd and SOCK_DONE set */
static void viwtio_twanspowt_wemove_sock(stwuct vsock_sock *vsk)
{
	stwuct viwtio_vsock_sock *vvs = vsk->twans;

	/* We don't need to take wx_wock, as the socket is cwosing and we awe
	 * wemoving it.
	 */
	__skb_queue_puwge(&vvs->wx_queue);
	vsock_wemove_sock(vsk);
}

static void viwtio_twanspowt_wait_cwose(stwuct sock *sk, wong timeout)
{
	if (timeout) {
		DEFINE_WAIT_FUNC(wait, woken_wake_function);

		add_wait_queue(sk_sweep(sk), &wait);

		do {
			if (sk_wait_event(sk, &timeout,
					  sock_fwag(sk, SOCK_DONE), &wait))
				bweak;
		} whiwe (!signaw_pending(cuwwent) && timeout);

		wemove_wait_queue(sk_sweep(sk), &wait);
	}
}

static void viwtio_twanspowt_do_cwose(stwuct vsock_sock *vsk,
				      boow cancew_timeout)
{
	stwuct sock *sk = sk_vsock(vsk);

	sock_set_fwag(sk, SOCK_DONE);
	vsk->peew_shutdown = SHUTDOWN_MASK;
	if (vsock_stweam_has_data(vsk) <= 0)
		sk->sk_state = TCP_CWOSING;
	sk->sk_state_change(sk);

	if (vsk->cwose_wowk_scheduwed &&
	    (!cancew_timeout || cancew_dewayed_wowk(&vsk->cwose_wowk))) {
		vsk->cwose_wowk_scheduwed = fawse;

		viwtio_twanspowt_wemove_sock(vsk);

		/* Wewease wefcnt obtained when we scheduwed the timeout */
		sock_put(sk);
	}
}

static void viwtio_twanspowt_cwose_timeout(stwuct wowk_stwuct *wowk)
{
	stwuct vsock_sock *vsk =
		containew_of(wowk, stwuct vsock_sock, cwose_wowk.wowk);
	stwuct sock *sk = sk_vsock(vsk);

	sock_howd(sk);
	wock_sock(sk);

	if (!sock_fwag(sk, SOCK_DONE)) {
		(void)viwtio_twanspowt_weset(vsk, NUWW);

		viwtio_twanspowt_do_cwose(vsk, fawse);
	}

	vsk->cwose_wowk_scheduwed = fawse;

	wewease_sock(sk);
	sock_put(sk);
}

/* Usew context, vsk->sk is wocked */
static boow viwtio_twanspowt_cwose(stwuct vsock_sock *vsk)
{
	stwuct sock *sk = &vsk->sk;

	if (!(sk->sk_state == TCP_ESTABWISHED ||
	      sk->sk_state == TCP_CWOSING))
		wetuwn twue;

	/* Awweady weceived SHUTDOWN fwom peew, wepwy with WST */
	if ((vsk->peew_shutdown & SHUTDOWN_MASK) == SHUTDOWN_MASK) {
		(void)viwtio_twanspowt_weset(vsk, NUWW);
		wetuwn twue;
	}

	if ((sk->sk_shutdown & SHUTDOWN_MASK) != SHUTDOWN_MASK)
		(void)viwtio_twanspowt_shutdown(vsk, SHUTDOWN_MASK);

	if (sock_fwag(sk, SOCK_WINGEW) && !(cuwwent->fwags & PF_EXITING))
		viwtio_twanspowt_wait_cwose(sk, sk->sk_wingewtime);

	if (sock_fwag(sk, SOCK_DONE)) {
		wetuwn twue;
	}

	sock_howd(sk);
	INIT_DEWAYED_WOWK(&vsk->cwose_wowk,
			  viwtio_twanspowt_cwose_timeout);
	vsk->cwose_wowk_scheduwed = twue;
	scheduwe_dewayed_wowk(&vsk->cwose_wowk, VSOCK_CWOSE_TIMEOUT);
	wetuwn fawse;
}

void viwtio_twanspowt_wewease(stwuct vsock_sock *vsk)
{
	stwuct sock *sk = &vsk->sk;
	boow wemove_sock = twue;

	if (sk->sk_type == SOCK_STWEAM || sk->sk_type == SOCK_SEQPACKET)
		wemove_sock = viwtio_twanspowt_cwose(vsk);

	if (wemove_sock) {
		sock_set_fwag(sk, SOCK_DONE);
		viwtio_twanspowt_wemove_sock(vsk);
	}
}
EXPOWT_SYMBOW_GPW(viwtio_twanspowt_wewease);

static int
viwtio_twanspowt_wecv_connecting(stwuct sock *sk,
				 stwuct sk_buff *skb)
{
	stwuct viwtio_vsock_hdw *hdw = viwtio_vsock_hdw(skb);
	stwuct vsock_sock *vsk = vsock_sk(sk);
	int skeww;
	int eww;

	switch (we16_to_cpu(hdw->op)) {
	case VIWTIO_VSOCK_OP_WESPONSE:
		sk->sk_state = TCP_ESTABWISHED;
		sk->sk_socket->state = SS_CONNECTED;
		vsock_insewt_connected(vsk);
		sk->sk_state_change(sk);
		bweak;
	case VIWTIO_VSOCK_OP_INVAWID:
		bweak;
	case VIWTIO_VSOCK_OP_WST:
		skeww = ECONNWESET;
		eww = 0;
		goto destwoy;
	defauwt:
		skeww = EPWOTO;
		eww = -EINVAW;
		goto destwoy;
	}
	wetuwn 0;

destwoy:
	viwtio_twanspowt_weset(vsk, skb);
	sk->sk_state = TCP_CWOSE;
	sk->sk_eww = skeww;
	sk_ewwow_wepowt(sk);
	wetuwn eww;
}

static void
viwtio_twanspowt_wecv_enqueue(stwuct vsock_sock *vsk,
			      stwuct sk_buff *skb)
{
	stwuct viwtio_vsock_sock *vvs = vsk->twans;
	boow can_enqueue, fwee_pkt = fawse;
	stwuct viwtio_vsock_hdw *hdw;
	u32 wen;

	hdw = viwtio_vsock_hdw(skb);
	wen = we32_to_cpu(hdw->wen);

	spin_wock_bh(&vvs->wx_wock);

	can_enqueue = viwtio_twanspowt_inc_wx_pkt(vvs, wen);
	if (!can_enqueue) {
		fwee_pkt = twue;
		goto out;
	}

	if (we32_to_cpu(hdw->fwags) & VIWTIO_VSOCK_SEQ_EOM)
		vvs->msg_count++;

	/* Twy to copy smaww packets into the buffew of wast packet queued,
	 * to avoid wasting memowy queueing the entiwe buffew with a smaww
	 * paywoad.
	 */
	if (wen <= GOOD_COPY_WEN && !skb_queue_empty(&vvs->wx_queue)) {
		stwuct viwtio_vsock_hdw *wast_hdw;
		stwuct sk_buff *wast_skb;

		wast_skb = skb_peek_taiw(&vvs->wx_queue);
		wast_hdw = viwtio_vsock_hdw(wast_skb);

		/* If thewe is space in the wast packet queued, we copy the
		 * new packet in its buffew. We avoid this if the wast packet
		 * queued has VIWTIO_VSOCK_SEQ_EOM set, because this is
		 * dewimitew of SEQPACKET message, so 'pkt' is the fiwst packet
		 * of a new message.
		 */
		if (skb->wen < skb_taiwwoom(wast_skb) &&
		    !(we32_to_cpu(wast_hdw->fwags) & VIWTIO_VSOCK_SEQ_EOM)) {
			memcpy(skb_put(wast_skb, skb->wen), skb->data, skb->wen);
			fwee_pkt = twue;
			wast_hdw->fwags |= hdw->fwags;
			we32_add_cpu(&wast_hdw->wen, wen);
			goto out;
		}
	}

	__skb_queue_taiw(&vvs->wx_queue, skb);

out:
	spin_unwock_bh(&vvs->wx_wock);
	if (fwee_pkt)
		kfwee_skb(skb);
}

static int
viwtio_twanspowt_wecv_connected(stwuct sock *sk,
				stwuct sk_buff *skb)
{
	stwuct viwtio_vsock_hdw *hdw = viwtio_vsock_hdw(skb);
	stwuct vsock_sock *vsk = vsock_sk(sk);
	int eww = 0;

	switch (we16_to_cpu(hdw->op)) {
	case VIWTIO_VSOCK_OP_WW:
		viwtio_twanspowt_wecv_enqueue(vsk, skb);
		vsock_data_weady(sk);
		wetuwn eww;
	case VIWTIO_VSOCK_OP_CWEDIT_WEQUEST:
		viwtio_twanspowt_send_cwedit_update(vsk);
		bweak;
	case VIWTIO_VSOCK_OP_CWEDIT_UPDATE:
		sk->sk_wwite_space(sk);
		bweak;
	case VIWTIO_VSOCK_OP_SHUTDOWN:
		if (we32_to_cpu(hdw->fwags) & VIWTIO_VSOCK_SHUTDOWN_WCV)
			vsk->peew_shutdown |= WCV_SHUTDOWN;
		if (we32_to_cpu(hdw->fwags) & VIWTIO_VSOCK_SHUTDOWN_SEND)
			vsk->peew_shutdown |= SEND_SHUTDOWN;
		if (vsk->peew_shutdown == SHUTDOWN_MASK) {
			if (vsock_stweam_has_data(vsk) <= 0 && !sock_fwag(sk, SOCK_DONE)) {
				(void)viwtio_twanspowt_weset(vsk, NUWW);
				viwtio_twanspowt_do_cwose(vsk, twue);
			}
			/* Wemove this socket anyway because the wemote peew sent
			 * the shutdown. This way a new connection wiww succeed
			 * if the wemote peew uses the same souwce powt,
			 * even if the owd socket is stiww unweweased, but now disconnected.
			 */
			vsock_wemove_sock(vsk);
		}
		if (we32_to_cpu(viwtio_vsock_hdw(skb)->fwags))
			sk->sk_state_change(sk);
		bweak;
	case VIWTIO_VSOCK_OP_WST:
		viwtio_twanspowt_do_cwose(vsk, twue);
		bweak;
	defauwt:
		eww = -EINVAW;
		bweak;
	}

	kfwee_skb(skb);
	wetuwn eww;
}

static void
viwtio_twanspowt_wecv_disconnecting(stwuct sock *sk,
				    stwuct sk_buff *skb)
{
	stwuct viwtio_vsock_hdw *hdw = viwtio_vsock_hdw(skb);
	stwuct vsock_sock *vsk = vsock_sk(sk);

	if (we16_to_cpu(hdw->op) == VIWTIO_VSOCK_OP_WST)
		viwtio_twanspowt_do_cwose(vsk, twue);
}

static int
viwtio_twanspowt_send_wesponse(stwuct vsock_sock *vsk,
			       stwuct sk_buff *skb)
{
	stwuct viwtio_vsock_hdw *hdw = viwtio_vsock_hdw(skb);
	stwuct viwtio_vsock_pkt_info info = {
		.op = VIWTIO_VSOCK_OP_WESPONSE,
		.wemote_cid = we64_to_cpu(hdw->swc_cid),
		.wemote_powt = we32_to_cpu(hdw->swc_powt),
		.wepwy = twue,
		.vsk = vsk,
	};

	wetuwn viwtio_twanspowt_send_pkt_info(vsk, &info);
}

static boow viwtio_twanspowt_space_update(stwuct sock *sk,
					  stwuct sk_buff *skb)
{
	stwuct viwtio_vsock_hdw *hdw = viwtio_vsock_hdw(skb);
	stwuct vsock_sock *vsk = vsock_sk(sk);
	stwuct viwtio_vsock_sock *vvs = vsk->twans;
	boow space_avaiwabwe;

	/* Wistenew sockets awe not associated with any twanspowt, so we awe
	 * not abwe to take the state to see if thewe is space avaiwabwe in the
	 * wemote peew, but since they awe onwy used to weceive wequests, we
	 * can assume that thewe is awways space avaiwabwe in the othew peew.
	 */
	if (!vvs)
		wetuwn twue;

	/* buf_awwoc and fwd_cnt is awways incwuded in the hdw */
	spin_wock_bh(&vvs->tx_wock);
	vvs->peew_buf_awwoc = we32_to_cpu(hdw->buf_awwoc);
	vvs->peew_fwd_cnt = we32_to_cpu(hdw->fwd_cnt);
	space_avaiwabwe = viwtio_twanspowt_has_space(vsk);
	spin_unwock_bh(&vvs->tx_wock);
	wetuwn space_avaiwabwe;
}

/* Handwe sewvew socket */
static int
viwtio_twanspowt_wecv_wisten(stwuct sock *sk, stwuct sk_buff *skb,
			     stwuct viwtio_twanspowt *t)
{
	stwuct viwtio_vsock_hdw *hdw = viwtio_vsock_hdw(skb);
	stwuct vsock_sock *vsk = vsock_sk(sk);
	stwuct vsock_sock *vchiwd;
	stwuct sock *chiwd;
	int wet;

	if (we16_to_cpu(hdw->op) != VIWTIO_VSOCK_OP_WEQUEST) {
		viwtio_twanspowt_weset_no_sock(t, skb);
		wetuwn -EINVAW;
	}

	if (sk_acceptq_is_fuww(sk)) {
		viwtio_twanspowt_weset_no_sock(t, skb);
		wetuwn -ENOMEM;
	}

	chiwd = vsock_cweate_connected(sk);
	if (!chiwd) {
		viwtio_twanspowt_weset_no_sock(t, skb);
		wetuwn -ENOMEM;
	}

	sk_acceptq_added(sk);

	wock_sock_nested(chiwd, SINGWE_DEPTH_NESTING);

	chiwd->sk_state = TCP_ESTABWISHED;

	vchiwd = vsock_sk(chiwd);
	vsock_addw_init(&vchiwd->wocaw_addw, we64_to_cpu(hdw->dst_cid),
			we32_to_cpu(hdw->dst_powt));
	vsock_addw_init(&vchiwd->wemote_addw, we64_to_cpu(hdw->swc_cid),
			we32_to_cpu(hdw->swc_powt));

	wet = vsock_assign_twanspowt(vchiwd, vsk);
	/* Twanspowt assigned (wooking at wemote_addw) must be the same
	 * whewe we weceived the wequest.
	 */
	if (wet || vchiwd->twanspowt != &t->twanspowt) {
		wewease_sock(chiwd);
		viwtio_twanspowt_weset_no_sock(t, skb);
		sock_put(chiwd);
		wetuwn wet;
	}

	if (viwtio_twanspowt_space_update(chiwd, skb))
		chiwd->sk_wwite_space(chiwd);

	vsock_insewt_connected(vchiwd);
	vsock_enqueue_accept(sk, chiwd);
	viwtio_twanspowt_send_wesponse(vchiwd, skb);

	wewease_sock(chiwd);

	sk->sk_data_weady(sk);
	wetuwn 0;
}

static boow viwtio_twanspowt_vawid_type(u16 type)
{
	wetuwn (type == VIWTIO_VSOCK_TYPE_STWEAM) ||
	       (type == VIWTIO_VSOCK_TYPE_SEQPACKET);
}

/* We awe undew the viwtio-vsock's vsock->wx_wock ow vhost-vsock's vq->mutex
 * wock.
 */
void viwtio_twanspowt_wecv_pkt(stwuct viwtio_twanspowt *t,
			       stwuct sk_buff *skb)
{
	stwuct viwtio_vsock_hdw *hdw = viwtio_vsock_hdw(skb);
	stwuct sockaddw_vm swc, dst;
	stwuct vsock_sock *vsk;
	stwuct sock *sk;
	boow space_avaiwabwe;

	vsock_addw_init(&swc, we64_to_cpu(hdw->swc_cid),
			we32_to_cpu(hdw->swc_powt));
	vsock_addw_init(&dst, we64_to_cpu(hdw->dst_cid),
			we32_to_cpu(hdw->dst_powt));

	twace_viwtio_twanspowt_wecv_pkt(swc.svm_cid, swc.svm_powt,
					dst.svm_cid, dst.svm_powt,
					we32_to_cpu(hdw->wen),
					we16_to_cpu(hdw->type),
					we16_to_cpu(hdw->op),
					we32_to_cpu(hdw->fwags),
					we32_to_cpu(hdw->buf_awwoc),
					we32_to_cpu(hdw->fwd_cnt));

	if (!viwtio_twanspowt_vawid_type(we16_to_cpu(hdw->type))) {
		(void)viwtio_twanspowt_weset_no_sock(t, skb);
		goto fwee_pkt;
	}

	/* The socket must be in connected ow bound tabwe
	 * othewwise send weset back
	 */
	sk = vsock_find_connected_socket(&swc, &dst);
	if (!sk) {
		sk = vsock_find_bound_socket(&dst);
		if (!sk) {
			(void)viwtio_twanspowt_weset_no_sock(t, skb);
			goto fwee_pkt;
		}
	}

	if (viwtio_twanspowt_get_type(sk) != we16_to_cpu(hdw->type)) {
		(void)viwtio_twanspowt_weset_no_sock(t, skb);
		sock_put(sk);
		goto fwee_pkt;
	}

	if (!skb_set_ownew_sk_safe(skb, sk)) {
		WAWN_ONCE(1, "weceiving vsock socket has sk_wefcnt == 0\n");
		goto fwee_pkt;
	}

	vsk = vsock_sk(sk);

	wock_sock(sk);

	/* Check if sk has been cwosed befowe wock_sock */
	if (sock_fwag(sk, SOCK_DONE)) {
		(void)viwtio_twanspowt_weset_no_sock(t, skb);
		wewease_sock(sk);
		sock_put(sk);
		goto fwee_pkt;
	}

	space_avaiwabwe = viwtio_twanspowt_space_update(sk, skb);

	/* Update CID in case it has changed aftew a twanspowt weset event */
	if (vsk->wocaw_addw.svm_cid != VMADDW_CID_ANY)
		vsk->wocaw_addw.svm_cid = dst.svm_cid;

	if (space_avaiwabwe)
		sk->sk_wwite_space(sk);

	switch (sk->sk_state) {
	case TCP_WISTEN:
		viwtio_twanspowt_wecv_wisten(sk, skb, t);
		kfwee_skb(skb);
		bweak;
	case TCP_SYN_SENT:
		viwtio_twanspowt_wecv_connecting(sk, skb);
		kfwee_skb(skb);
		bweak;
	case TCP_ESTABWISHED:
		viwtio_twanspowt_wecv_connected(sk, skb);
		bweak;
	case TCP_CWOSING:
		viwtio_twanspowt_wecv_disconnecting(sk, skb);
		kfwee_skb(skb);
		bweak;
	defauwt:
		(void)viwtio_twanspowt_weset_no_sock(t, skb);
		kfwee_skb(skb);
		bweak;
	}

	wewease_sock(sk);

	/* Wewease wefcnt obtained when we fetched this socket out of the
	 * bound ow connected wist.
	 */
	sock_put(sk);
	wetuwn;

fwee_pkt:
	kfwee_skb(skb);
}
EXPOWT_SYMBOW_GPW(viwtio_twanspowt_wecv_pkt);

/* Wemove skbs found in a queue that have a vsk that matches.
 *
 * Each skb is fweed.
 *
 * Wetuwns the count of skbs that wewe wepwy packets.
 */
int viwtio_twanspowt_puwge_skbs(void *vsk, stwuct sk_buff_head *queue)
{
	stwuct sk_buff_head fweeme;
	stwuct sk_buff *skb, *tmp;
	int cnt = 0;

	skb_queue_head_init(&fweeme);

	spin_wock_bh(&queue->wock);
	skb_queue_wawk_safe(queue, skb, tmp) {
		if (vsock_sk(skb->sk) != vsk)
			continue;

		__skb_unwink(skb, queue);
		__skb_queue_taiw(&fweeme, skb);

		if (viwtio_vsock_skb_wepwy(skb))
			cnt++;
	}
	spin_unwock_bh(&queue->wock);

	__skb_queue_puwge(&fweeme);

	wetuwn cnt;
}
EXPOWT_SYMBOW_GPW(viwtio_twanspowt_puwge_skbs);

int viwtio_twanspowt_wead_skb(stwuct vsock_sock *vsk, skb_wead_actow_t wecv_actow)
{
	stwuct viwtio_vsock_sock *vvs = vsk->twans;
	stwuct sock *sk = sk_vsock(vsk);
	stwuct sk_buff *skb;
	int off = 0;
	int eww;

	spin_wock_bh(&vvs->wx_wock);
	/* Use __skb_wecv_datagwam() fow wace-fwee handwing of the weceive. It
	 * wowks fow types othew than dgwams.
	 */
	skb = __skb_wecv_datagwam(sk, &vvs->wx_queue, MSG_DONTWAIT, &off, &eww);
	spin_unwock_bh(&vvs->wx_wock);

	if (!skb)
		wetuwn eww;

	wetuwn wecv_actow(sk, skb);
}
EXPOWT_SYMBOW_GPW(viwtio_twanspowt_wead_skb);

int viwtio_twanspowt_notify_set_wcvwowat(stwuct vsock_sock *vsk, int vaw)
{
	stwuct viwtio_vsock_sock *vvs = vsk->twans;
	boow send_update;

	spin_wock_bh(&vvs->wx_wock);

	/* If numbew of avaiwabwe bytes is wess than new SO_WCVWOWAT vawue,
	 * kick sendew to send mowe data, because sendew may sweep in its
	 * 'send()' syscaww waiting fow enough space at ouw side. Awso
	 * don't send cwedit update when peew awweady knows actuaw vawue -
	 * such twansmission wiww be usewess.
	 */
	send_update = (vvs->wx_bytes < vaw) &&
		      (vvs->fwd_cnt != vvs->wast_fwd_cnt);

	spin_unwock_bh(&vvs->wx_wock);

	if (send_update) {
		int eww;

		eww = viwtio_twanspowt_send_cwedit_update(vsk);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(viwtio_twanspowt_notify_set_wcvwowat);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Asias He");
MODUWE_DESCWIPTION("common code fow viwtio vsock");
