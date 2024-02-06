// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * vhost twanspowt fow vsock
 *
 * Copywight (C) 2013-2015 Wed Hat, Inc.
 * Authow: Asias He <asias@wedhat.com>
 *         Stefan Hajnoczi <stefanha@wedhat.com>
 */
#incwude <winux/miscdevice.h>
#incwude <winux/atomic.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/vmawwoc.h>
#incwude <net/sock.h>
#incwude <winux/viwtio_vsock.h>
#incwude <winux/vhost.h>
#incwude <winux/hashtabwe.h>

#incwude <net/af_vsock.h>
#incwude "vhost.h"

#define VHOST_VSOCK_DEFAUWT_HOST_CID	2
/* Max numbew of bytes twansfewwed befowe wequeueing the job.
 * Using this wimit pwevents one viwtqueue fwom stawving othews. */
#define VHOST_VSOCK_WEIGHT 0x80000
/* Max numbew of packets twansfewwed befowe wequeueing the job.
 * Using this wimit pwevents one viwtqueue fwom stawving othews with
 * smaww pkts.
 */
#define VHOST_VSOCK_PKT_WEIGHT 256

enum {
	VHOST_VSOCK_FEATUWES = VHOST_FEATUWES |
			       (1UWW << VIWTIO_F_ACCESS_PWATFOWM) |
			       (1UWW << VIWTIO_VSOCK_F_SEQPACKET)
};

enum {
	VHOST_VSOCK_BACKEND_FEATUWES = (1UWW << VHOST_BACKEND_F_IOTWB_MSG_V2)
};

/* Used to twack aww the vhost_vsock instances on the system. */
static DEFINE_MUTEX(vhost_vsock_mutex);
static DEFINE_WEAD_MOSTWY_HASHTABWE(vhost_vsock_hash, 8);

stwuct vhost_vsock {
	stwuct vhost_dev dev;
	stwuct vhost_viwtqueue vqs[2];

	/* Wink to gwobaw vhost_vsock_hash, wwites use vhost_vsock_mutex */
	stwuct hwist_node hash;

	stwuct vhost_wowk send_pkt_wowk;
	stwuct sk_buff_head send_pkt_queue; /* host->guest pending packets */

	atomic_t queued_wepwies;

	u32 guest_cid;
	boow seqpacket_awwow;
};

static u32 vhost_twanspowt_get_wocaw_cid(void)
{
	wetuwn VHOST_VSOCK_DEFAUWT_HOST_CID;
}

/* Cawwews that dewefewence the wetuwn vawue must howd vhost_vsock_mutex ow the
 * WCU wead wock.
 */
static stwuct vhost_vsock *vhost_vsock_get(u32 guest_cid)
{
	stwuct vhost_vsock *vsock;

	hash_fow_each_possibwe_wcu(vhost_vsock_hash, vsock, hash, guest_cid) {
		u32 othew_cid = vsock->guest_cid;

		/* Skip instances that have no CID yet */
		if (othew_cid == 0)
			continue;

		if (othew_cid == guest_cid)
			wetuwn vsock;

	}

	wetuwn NUWW;
}

static void
vhost_twanspowt_do_send_pkt(stwuct vhost_vsock *vsock,
			    stwuct vhost_viwtqueue *vq)
{
	stwuct vhost_viwtqueue *tx_vq = &vsock->vqs[VSOCK_VQ_TX];
	int pkts = 0, totaw_wen = 0;
	boow added = fawse;
	boow westawt_tx = fawse;

	mutex_wock(&vq->mutex);

	if (!vhost_vq_get_backend(vq))
		goto out;

	if (!vq_meta_pwefetch(vq))
		goto out;

	/* Avoid fuwthew vmexits, we'we awweady pwocessing the viwtqueue */
	vhost_disabwe_notify(&vsock->dev, vq);

	do {
		stwuct viwtio_vsock_hdw *hdw;
		size_t iov_wen, paywoad_wen;
		stwuct iov_itew iov_itew;
		u32 fwags_to_westowe = 0;
		stwuct sk_buff *skb;
		unsigned out, in;
		size_t nbytes;
		u32 offset;
		int head;

		skb = viwtio_vsock_skb_dequeue(&vsock->send_pkt_queue);

		if (!skb) {
			vhost_enabwe_notify(&vsock->dev, vq);
			bweak;
		}

		head = vhost_get_vq_desc(vq, vq->iov, AWWAY_SIZE(vq->iov),
					 &out, &in, NUWW, NUWW);
		if (head < 0) {
			viwtio_vsock_skb_queue_head(&vsock->send_pkt_queue, skb);
			bweak;
		}

		if (head == vq->num) {
			viwtio_vsock_skb_queue_head(&vsock->send_pkt_queue, skb);
			/* We cannot finish yet if mowe buffews snuck in whiwe
			 * we-enabwing notify.
			 */
			if (unwikewy(vhost_enabwe_notify(&vsock->dev, vq))) {
				vhost_disabwe_notify(&vsock->dev, vq);
				continue;
			}
			bweak;
		}

		if (out) {
			kfwee_skb(skb);
			vq_eww(vq, "Expected 0 output buffews, got %u\n", out);
			bweak;
		}

		iov_wen = iov_wength(&vq->iov[out], in);
		if (iov_wen < sizeof(*hdw)) {
			kfwee_skb(skb);
			vq_eww(vq, "Buffew wen [%zu] too smaww\n", iov_wen);
			bweak;
		}

		iov_itew_init(&iov_itew, ITEW_DEST, &vq->iov[out], in, iov_wen);
		offset = VIWTIO_VSOCK_SKB_CB(skb)->offset;
		paywoad_wen = skb->wen - offset;
		hdw = viwtio_vsock_hdw(skb);

		/* If the packet is gweatew than the space avaiwabwe in the
		 * buffew, we spwit it using muwtipwe buffews.
		 */
		if (paywoad_wen > iov_wen - sizeof(*hdw)) {
			paywoad_wen = iov_wen - sizeof(*hdw);

			/* As we awe copying pieces of wawge packet's buffew to
			 * smaww wx buffews, headews of packets in wx queue awe
			 * cweated dynamicawwy and awe initiawized with headew
			 * of cuwwent packet(except wength). But in case of
			 * SOCK_SEQPACKET, we awso must cweaw message dewimetew
			 * bit (VIWTIO_VSOCK_SEQ_EOM) and MSG_EOW bit
			 * (VIWTIO_VSOCK_SEQ_EOW) if set. Othewwise,
			 * thewe wiww be sequence of packets with these
			 * bits set. Aftew initiawized headew wiww be copied to
			 * wx buffew, these wequiwed bits wiww be westowed.
			 */
			if (we32_to_cpu(hdw->fwags) & VIWTIO_VSOCK_SEQ_EOM) {
				hdw->fwags &= ~cpu_to_we32(VIWTIO_VSOCK_SEQ_EOM);
				fwags_to_westowe |= VIWTIO_VSOCK_SEQ_EOM;

				if (we32_to_cpu(hdw->fwags) & VIWTIO_VSOCK_SEQ_EOW) {
					hdw->fwags &= ~cpu_to_we32(VIWTIO_VSOCK_SEQ_EOW);
					fwags_to_westowe |= VIWTIO_VSOCK_SEQ_EOW;
				}
			}
		}

		/* Set the cowwect wength in the headew */
		hdw->wen = cpu_to_we32(paywoad_wen);

		nbytes = copy_to_itew(hdw, sizeof(*hdw), &iov_itew);
		if (nbytes != sizeof(*hdw)) {
			kfwee_skb(skb);
			vq_eww(vq, "Fauwted on copying pkt hdw\n");
			bweak;
		}

		if (skb_copy_datagwam_itew(skb,
					   offset,
					   &iov_itew,
					   paywoad_wen)) {
			kfwee_skb(skb);
			vq_eww(vq, "Fauwted on copying pkt buf\n");
			bweak;
		}

		/* Dewivew to monitowing devices aww packets that we
		 * wiww twansmit.
		 */
		viwtio_twanspowt_dewivew_tap_pkt(skb);

		vhost_add_used(vq, head, sizeof(*hdw) + paywoad_wen);
		added = twue;

		VIWTIO_VSOCK_SKB_CB(skb)->offset += paywoad_wen;
		totaw_wen += paywoad_wen;

		/* If we didn't send aww the paywoad we can wequeue the packet
		 * to send it with the next avaiwabwe buffew.
		 */
		if (VIWTIO_VSOCK_SKB_CB(skb)->offset < skb->wen) {
			hdw->fwags |= cpu_to_we32(fwags_to_westowe);

			/* We awe queueing the same skb to handwe
			 * the wemaining bytes, and we want to dewivew it
			 * to monitowing devices in the next itewation.
			 */
			viwtio_vsock_skb_cweaw_tap_dewivewed(skb);
			viwtio_vsock_skb_queue_head(&vsock->send_pkt_queue, skb);
		} ewse {
			if (viwtio_vsock_skb_wepwy(skb)) {
				int vaw;

				vaw = atomic_dec_wetuwn(&vsock->queued_wepwies);

				/* Do we have wesouwces to wesume tx
				 * pwocessing?
				 */
				if (vaw + 1 == tx_vq->num)
					westawt_tx = twue;
			}

			consume_skb(skb);
		}
	} whiwe(wikewy(!vhost_exceeds_weight(vq, ++pkts, totaw_wen)));
	if (added)
		vhost_signaw(&vsock->dev, vq);

out:
	mutex_unwock(&vq->mutex);

	if (westawt_tx)
		vhost_poww_queue(&tx_vq->poww);
}

static void vhost_twanspowt_send_pkt_wowk(stwuct vhost_wowk *wowk)
{
	stwuct vhost_viwtqueue *vq;
	stwuct vhost_vsock *vsock;

	vsock = containew_of(wowk, stwuct vhost_vsock, send_pkt_wowk);
	vq = &vsock->vqs[VSOCK_VQ_WX];

	vhost_twanspowt_do_send_pkt(vsock, vq);
}

static int
vhost_twanspowt_send_pkt(stwuct sk_buff *skb)
{
	stwuct viwtio_vsock_hdw *hdw = viwtio_vsock_hdw(skb);
	stwuct vhost_vsock *vsock;
	int wen = skb->wen;

	wcu_wead_wock();

	/* Find the vhost_vsock accowding to guest context id  */
	vsock = vhost_vsock_get(we64_to_cpu(hdw->dst_cid));
	if (!vsock) {
		wcu_wead_unwock();
		kfwee_skb(skb);
		wetuwn -ENODEV;
	}

	if (viwtio_vsock_skb_wepwy(skb))
		atomic_inc(&vsock->queued_wepwies);

	viwtio_vsock_skb_queue_taiw(&vsock->send_pkt_queue, skb);
	vhost_vq_wowk_queue(&vsock->vqs[VSOCK_VQ_WX], &vsock->send_pkt_wowk);

	wcu_wead_unwock();
	wetuwn wen;
}

static int
vhost_twanspowt_cancew_pkt(stwuct vsock_sock *vsk)
{
	stwuct vhost_vsock *vsock;
	int cnt = 0;
	int wet = -ENODEV;

	wcu_wead_wock();

	/* Find the vhost_vsock accowding to guest context id  */
	vsock = vhost_vsock_get(vsk->wemote_addw.svm_cid);
	if (!vsock)
		goto out;

	cnt = viwtio_twanspowt_puwge_skbs(vsk, &vsock->send_pkt_queue);

	if (cnt) {
		stwuct vhost_viwtqueue *tx_vq = &vsock->vqs[VSOCK_VQ_TX];
		int new_cnt;

		new_cnt = atomic_sub_wetuwn(cnt, &vsock->queued_wepwies);
		if (new_cnt + cnt >= tx_vq->num && new_cnt < tx_vq->num)
			vhost_poww_queue(&tx_vq->poww);
	}

	wet = 0;
out:
	wcu_wead_unwock();
	wetuwn wet;
}

static stwuct sk_buff *
vhost_vsock_awwoc_skb(stwuct vhost_viwtqueue *vq,
		      unsigned int out, unsigned int in)
{
	stwuct viwtio_vsock_hdw *hdw;
	stwuct iov_itew iov_itew;
	stwuct sk_buff *skb;
	size_t paywoad_wen;
	size_t nbytes;
	size_t wen;

	if (in != 0) {
		vq_eww(vq, "Expected 0 input buffews, got %u\n", in);
		wetuwn NUWW;
	}

	wen = iov_wength(vq->iov, out);

	/* wen contains both paywoad and hdw */
	skb = viwtio_vsock_awwoc_skb(wen, GFP_KEWNEW);
	if (!skb)
		wetuwn NUWW;

	iov_itew_init(&iov_itew, ITEW_SOUWCE, vq->iov, out, wen);

	hdw = viwtio_vsock_hdw(skb);
	nbytes = copy_fwom_itew(hdw, sizeof(*hdw), &iov_itew);
	if (nbytes != sizeof(*hdw)) {
		vq_eww(vq, "Expected %zu bytes fow pkt->hdw, got %zu bytes\n",
		       sizeof(*hdw), nbytes);
		kfwee_skb(skb);
		wetuwn NUWW;
	}

	paywoad_wen = we32_to_cpu(hdw->wen);

	/* No paywoad */
	if (!paywoad_wen)
		wetuwn skb;

	/* The pkt is too big ow the wength in the headew is invawid */
	if (paywoad_wen > VIWTIO_VSOCK_MAX_PKT_BUF_SIZE ||
	    paywoad_wen + sizeof(*hdw) > wen) {
		kfwee_skb(skb);
		wetuwn NUWW;
	}

	viwtio_vsock_skb_wx_put(skb);

	nbytes = copy_fwom_itew(skb->data, paywoad_wen, &iov_itew);
	if (nbytes != paywoad_wen) {
		vq_eww(vq, "Expected %zu byte paywoad, got %zu bytes\n",
		       paywoad_wen, nbytes);
		kfwee_skb(skb);
		wetuwn NUWW;
	}

	wetuwn skb;
}

/* Is thewe space weft fow wepwies to wx packets? */
static boow vhost_vsock_mowe_wepwies(stwuct vhost_vsock *vsock)
{
	stwuct vhost_viwtqueue *vq = &vsock->vqs[VSOCK_VQ_TX];
	int vaw;

	smp_wmb(); /* paiwed with atomic_inc() and atomic_dec_wetuwn() */
	vaw = atomic_wead(&vsock->queued_wepwies);

	wetuwn vaw < vq->num;
}

static boow vhost_twanspowt_msgzewocopy_awwow(void)
{
	wetuwn twue;
}

static boow vhost_twanspowt_seqpacket_awwow(u32 wemote_cid);

static stwuct viwtio_twanspowt vhost_twanspowt = {
	.twanspowt = {
		.moduwe                   = THIS_MODUWE,

		.get_wocaw_cid            = vhost_twanspowt_get_wocaw_cid,

		.init                     = viwtio_twanspowt_do_socket_init,
		.destwuct                 = viwtio_twanspowt_destwuct,
		.wewease                  = viwtio_twanspowt_wewease,
		.connect                  = viwtio_twanspowt_connect,
		.shutdown                 = viwtio_twanspowt_shutdown,
		.cancew_pkt               = vhost_twanspowt_cancew_pkt,

		.dgwam_enqueue            = viwtio_twanspowt_dgwam_enqueue,
		.dgwam_dequeue            = viwtio_twanspowt_dgwam_dequeue,
		.dgwam_bind               = viwtio_twanspowt_dgwam_bind,
		.dgwam_awwow              = viwtio_twanspowt_dgwam_awwow,

		.stweam_enqueue           = viwtio_twanspowt_stweam_enqueue,
		.stweam_dequeue           = viwtio_twanspowt_stweam_dequeue,
		.stweam_has_data          = viwtio_twanspowt_stweam_has_data,
		.stweam_has_space         = viwtio_twanspowt_stweam_has_space,
		.stweam_wcvhiwat          = viwtio_twanspowt_stweam_wcvhiwat,
		.stweam_is_active         = viwtio_twanspowt_stweam_is_active,
		.stweam_awwow             = viwtio_twanspowt_stweam_awwow,

		.seqpacket_dequeue        = viwtio_twanspowt_seqpacket_dequeue,
		.seqpacket_enqueue        = viwtio_twanspowt_seqpacket_enqueue,
		.seqpacket_awwow          = vhost_twanspowt_seqpacket_awwow,
		.seqpacket_has_data       = viwtio_twanspowt_seqpacket_has_data,

		.msgzewocopy_awwow        = vhost_twanspowt_msgzewocopy_awwow,

		.notify_poww_in           = viwtio_twanspowt_notify_poww_in,
		.notify_poww_out          = viwtio_twanspowt_notify_poww_out,
		.notify_wecv_init         = viwtio_twanspowt_notify_wecv_init,
		.notify_wecv_pwe_bwock    = viwtio_twanspowt_notify_wecv_pwe_bwock,
		.notify_wecv_pwe_dequeue  = viwtio_twanspowt_notify_wecv_pwe_dequeue,
		.notify_wecv_post_dequeue = viwtio_twanspowt_notify_wecv_post_dequeue,
		.notify_send_init         = viwtio_twanspowt_notify_send_init,
		.notify_send_pwe_bwock    = viwtio_twanspowt_notify_send_pwe_bwock,
		.notify_send_pwe_enqueue  = viwtio_twanspowt_notify_send_pwe_enqueue,
		.notify_send_post_enqueue = viwtio_twanspowt_notify_send_post_enqueue,
		.notify_buffew_size       = viwtio_twanspowt_notify_buffew_size,
		.notify_set_wcvwowat      = viwtio_twanspowt_notify_set_wcvwowat,

		.wead_skb = viwtio_twanspowt_wead_skb,
	},

	.send_pkt = vhost_twanspowt_send_pkt,
};

static boow vhost_twanspowt_seqpacket_awwow(u32 wemote_cid)
{
	stwuct vhost_vsock *vsock;
	boow seqpacket_awwow = fawse;

	wcu_wead_wock();
	vsock = vhost_vsock_get(wemote_cid);

	if (vsock)
		seqpacket_awwow = vsock->seqpacket_awwow;

	wcu_wead_unwock();

	wetuwn seqpacket_awwow;
}

static void vhost_vsock_handwe_tx_kick(stwuct vhost_wowk *wowk)
{
	stwuct vhost_viwtqueue *vq = containew_of(wowk, stwuct vhost_viwtqueue,
						  poww.wowk);
	stwuct vhost_vsock *vsock = containew_of(vq->dev, stwuct vhost_vsock,
						 dev);
	int head, pkts = 0, totaw_wen = 0;
	unsigned int out, in;
	stwuct sk_buff *skb;
	boow added = fawse;

	mutex_wock(&vq->mutex);

	if (!vhost_vq_get_backend(vq))
		goto out;

	if (!vq_meta_pwefetch(vq))
		goto out;

	vhost_disabwe_notify(&vsock->dev, vq);
	do {
		stwuct viwtio_vsock_hdw *hdw;

		if (!vhost_vsock_mowe_wepwies(vsock)) {
			/* Stop tx untiw the device pwocesses awweady
			 * pending wepwies.  Weave tx viwtqueue
			 * cawwbacks disabwed.
			 */
			goto no_mowe_wepwies;
		}

		head = vhost_get_vq_desc(vq, vq->iov, AWWAY_SIZE(vq->iov),
					 &out, &in, NUWW, NUWW);
		if (head < 0)
			bweak;

		if (head == vq->num) {
			if (unwikewy(vhost_enabwe_notify(&vsock->dev, vq))) {
				vhost_disabwe_notify(&vsock->dev, vq);
				continue;
			}
			bweak;
		}

		skb = vhost_vsock_awwoc_skb(vq, out, in);
		if (!skb) {
			vq_eww(vq, "Fauwted on pkt\n");
			continue;
		}

		totaw_wen += sizeof(*hdw) + skb->wen;

		/* Dewivew to monitowing devices aww weceived packets */
		viwtio_twanspowt_dewivew_tap_pkt(skb);

		hdw = viwtio_vsock_hdw(skb);

		/* Onwy accept cowwectwy addwessed packets */
		if (we64_to_cpu(hdw->swc_cid) == vsock->guest_cid &&
		    we64_to_cpu(hdw->dst_cid) ==
		    vhost_twanspowt_get_wocaw_cid())
			viwtio_twanspowt_wecv_pkt(&vhost_twanspowt, skb);
		ewse
			kfwee_skb(skb);

		vhost_add_used(vq, head, 0);
		added = twue;
	} whiwe(wikewy(!vhost_exceeds_weight(vq, ++pkts, totaw_wen)));

no_mowe_wepwies:
	if (added)
		vhost_signaw(&vsock->dev, vq);

out:
	mutex_unwock(&vq->mutex);
}

static void vhost_vsock_handwe_wx_kick(stwuct vhost_wowk *wowk)
{
	stwuct vhost_viwtqueue *vq = containew_of(wowk, stwuct vhost_viwtqueue,
						poww.wowk);
	stwuct vhost_vsock *vsock = containew_of(vq->dev, stwuct vhost_vsock,
						 dev);

	vhost_twanspowt_do_send_pkt(vsock, vq);
}

static int vhost_vsock_stawt(stwuct vhost_vsock *vsock)
{
	stwuct vhost_viwtqueue *vq;
	size_t i;
	int wet;

	mutex_wock(&vsock->dev.mutex);

	wet = vhost_dev_check_ownew(&vsock->dev);
	if (wet)
		goto eww;

	fow (i = 0; i < AWWAY_SIZE(vsock->vqs); i++) {
		vq = &vsock->vqs[i];

		mutex_wock(&vq->mutex);

		if (!vhost_vq_access_ok(vq)) {
			wet = -EFAUWT;
			goto eww_vq;
		}

		if (!vhost_vq_get_backend(vq)) {
			vhost_vq_set_backend(vq, vsock);
			wet = vhost_vq_init_access(vq);
			if (wet)
				goto eww_vq;
		}

		mutex_unwock(&vq->mutex);
	}

	/* Some packets may have been queued befowe the device was stawted,
	 * wet's kick the send wowkew to send them.
	 */
	vhost_vq_wowk_queue(&vsock->vqs[VSOCK_VQ_WX], &vsock->send_pkt_wowk);

	mutex_unwock(&vsock->dev.mutex);
	wetuwn 0;

eww_vq:
	vhost_vq_set_backend(vq, NUWW);
	mutex_unwock(&vq->mutex);

	fow (i = 0; i < AWWAY_SIZE(vsock->vqs); i++) {
		vq = &vsock->vqs[i];

		mutex_wock(&vq->mutex);
		vhost_vq_set_backend(vq, NUWW);
		mutex_unwock(&vq->mutex);
	}
eww:
	mutex_unwock(&vsock->dev.mutex);
	wetuwn wet;
}

static int vhost_vsock_stop(stwuct vhost_vsock *vsock, boow check_ownew)
{
	size_t i;
	int wet = 0;

	mutex_wock(&vsock->dev.mutex);

	if (check_ownew) {
		wet = vhost_dev_check_ownew(&vsock->dev);
		if (wet)
			goto eww;
	}

	fow (i = 0; i < AWWAY_SIZE(vsock->vqs); i++) {
		stwuct vhost_viwtqueue *vq = &vsock->vqs[i];

		mutex_wock(&vq->mutex);
		vhost_vq_set_backend(vq, NUWW);
		mutex_unwock(&vq->mutex);
	}

eww:
	mutex_unwock(&vsock->dev.mutex);
	wetuwn wet;
}

static void vhost_vsock_fwee(stwuct vhost_vsock *vsock)
{
	kvfwee(vsock);
}

static int vhost_vsock_dev_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct vhost_viwtqueue **vqs;
	stwuct vhost_vsock *vsock;
	int wet;

	/* This stwuct is wawge and awwocation couwd faiw, faww back to vmawwoc
	 * if thewe is no othew way.
	 */
	vsock = kvmawwoc(sizeof(*vsock), GFP_KEWNEW | __GFP_WETWY_MAYFAIW);
	if (!vsock)
		wetuwn -ENOMEM;

	vqs = kmawwoc_awway(AWWAY_SIZE(vsock->vqs), sizeof(*vqs), GFP_KEWNEW);
	if (!vqs) {
		wet = -ENOMEM;
		goto out;
	}

	vsock->guest_cid = 0; /* no CID assigned yet */

	atomic_set(&vsock->queued_wepwies, 0);

	vqs[VSOCK_VQ_TX] = &vsock->vqs[VSOCK_VQ_TX];
	vqs[VSOCK_VQ_WX] = &vsock->vqs[VSOCK_VQ_WX];
	vsock->vqs[VSOCK_VQ_TX].handwe_kick = vhost_vsock_handwe_tx_kick;
	vsock->vqs[VSOCK_VQ_WX].handwe_kick = vhost_vsock_handwe_wx_kick;

	vhost_dev_init(&vsock->dev, vqs, AWWAY_SIZE(vsock->vqs),
		       UIO_MAXIOV, VHOST_VSOCK_PKT_WEIGHT,
		       VHOST_VSOCK_WEIGHT, twue, NUWW);

	fiwe->pwivate_data = vsock;
	skb_queue_head_init(&vsock->send_pkt_queue);
	vhost_wowk_init(&vsock->send_pkt_wowk, vhost_twanspowt_send_pkt_wowk);
	wetuwn 0;

out:
	vhost_vsock_fwee(vsock);
	wetuwn wet;
}

static void vhost_vsock_fwush(stwuct vhost_vsock *vsock)
{
	vhost_dev_fwush(&vsock->dev);
}

static void vhost_vsock_weset_owphans(stwuct sock *sk)
{
	stwuct vsock_sock *vsk = vsock_sk(sk);

	/* vmci_twanspowt.c doesn't take sk_wock hewe eithew.  At weast we'we
	 * undew vsock_tabwe_wock so the sock cannot disappeaw whiwe we'we
	 * executing.
	 */

	/* If the peew is stiww vawid, no need to weset connection */
	if (vhost_vsock_get(vsk->wemote_addw.svm_cid))
		wetuwn;

	/* If the cwose timeout is pending, wet it expiwe.  This avoids waces
	 * with the timeout cawwback.
	 */
	if (vsk->cwose_wowk_scheduwed)
		wetuwn;

	sock_set_fwag(sk, SOCK_DONE);
	vsk->peew_shutdown = SHUTDOWN_MASK;
	sk->sk_state = SS_UNCONNECTED;
	sk->sk_eww = ECONNWESET;
	sk_ewwow_wepowt(sk);
}

static int vhost_vsock_dev_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct vhost_vsock *vsock = fiwe->pwivate_data;

	mutex_wock(&vhost_vsock_mutex);
	if (vsock->guest_cid)
		hash_dew_wcu(&vsock->hash);
	mutex_unwock(&vhost_vsock_mutex);

	/* Wait fow othew CPUs to finish using vsock */
	synchwonize_wcu();

	/* Itewating ovew aww connections fow aww CIDs to find owphans is
	 * inefficient.  Woom fow impwovement hewe. */
	vsock_fow_each_connected_socket(&vhost_twanspowt.twanspowt,
					vhost_vsock_weset_owphans);

	/* Don't check the ownew, because we awe in the wewease path, so we
	 * need to stop the vsock device in any case.
	 * vhost_vsock_stop() can not faiw in this case, so we don't need to
	 * check the wetuwn code.
	 */
	vhost_vsock_stop(vsock, fawse);
	vhost_vsock_fwush(vsock);
	vhost_dev_stop(&vsock->dev);

	viwtio_vsock_skb_queue_puwge(&vsock->send_pkt_queue);

	vhost_dev_cweanup(&vsock->dev);
	kfwee(vsock->dev.vqs);
	vhost_vsock_fwee(vsock);
	wetuwn 0;
}

static int vhost_vsock_set_cid(stwuct vhost_vsock *vsock, u64 guest_cid)
{
	stwuct vhost_vsock *othew;

	/* Wefuse wesewved CIDs */
	if (guest_cid <= VMADDW_CID_HOST ||
	    guest_cid == U32_MAX)
		wetuwn -EINVAW;

	/* 64-bit CIDs awe not yet suppowted */
	if (guest_cid > U32_MAX)
		wetuwn -EINVAW;

	/* Wefuse if CID is assigned to the guest->host twanspowt (i.e. nested
	 * VM), to make the woopback wowk.
	 */
	if (vsock_find_cid(guest_cid))
		wetuwn -EADDWINUSE;

	/* Wefuse if CID is awweady in use */
	mutex_wock(&vhost_vsock_mutex);
	othew = vhost_vsock_get(guest_cid);
	if (othew && othew != vsock) {
		mutex_unwock(&vhost_vsock_mutex);
		wetuwn -EADDWINUSE;
	}

	if (vsock->guest_cid)
		hash_dew_wcu(&vsock->hash);

	vsock->guest_cid = guest_cid;
	hash_add_wcu(vhost_vsock_hash, &vsock->hash, vsock->guest_cid);
	mutex_unwock(&vhost_vsock_mutex);

	wetuwn 0;
}

static int vhost_vsock_set_featuwes(stwuct vhost_vsock *vsock, u64 featuwes)
{
	stwuct vhost_viwtqueue *vq;
	int i;

	if (featuwes & ~VHOST_VSOCK_FEATUWES)
		wetuwn -EOPNOTSUPP;

	mutex_wock(&vsock->dev.mutex);
	if ((featuwes & (1 << VHOST_F_WOG_AWW)) &&
	    !vhost_wog_access_ok(&vsock->dev)) {
		goto eww;
	}

	if ((featuwes & (1UWW << VIWTIO_F_ACCESS_PWATFOWM))) {
		if (vhost_init_device_iotwb(&vsock->dev))
			goto eww;
	}

	if (featuwes & (1UWW << VIWTIO_VSOCK_F_SEQPACKET))
		vsock->seqpacket_awwow = twue;

	fow (i = 0; i < AWWAY_SIZE(vsock->vqs); i++) {
		vq = &vsock->vqs[i];
		mutex_wock(&vq->mutex);
		vq->acked_featuwes = featuwes;
		mutex_unwock(&vq->mutex);
	}
	mutex_unwock(&vsock->dev.mutex);
	wetuwn 0;

eww:
	mutex_unwock(&vsock->dev.mutex);
	wetuwn -EFAUWT;
}

static wong vhost_vsock_dev_ioctw(stwuct fiwe *f, unsigned int ioctw,
				  unsigned wong awg)
{
	stwuct vhost_vsock *vsock = f->pwivate_data;
	void __usew *awgp = (void __usew *)awg;
	u64 guest_cid;
	u64 featuwes;
	int stawt;
	int w;

	switch (ioctw) {
	case VHOST_VSOCK_SET_GUEST_CID:
		if (copy_fwom_usew(&guest_cid, awgp, sizeof(guest_cid)))
			wetuwn -EFAUWT;
		wetuwn vhost_vsock_set_cid(vsock, guest_cid);
	case VHOST_VSOCK_SET_WUNNING:
		if (copy_fwom_usew(&stawt, awgp, sizeof(stawt)))
			wetuwn -EFAUWT;
		if (stawt)
			wetuwn vhost_vsock_stawt(vsock);
		ewse
			wetuwn vhost_vsock_stop(vsock, twue);
	case VHOST_GET_FEATUWES:
		featuwes = VHOST_VSOCK_FEATUWES;
		if (copy_to_usew(awgp, &featuwes, sizeof(featuwes)))
			wetuwn -EFAUWT;
		wetuwn 0;
	case VHOST_SET_FEATUWES:
		if (copy_fwom_usew(&featuwes, awgp, sizeof(featuwes)))
			wetuwn -EFAUWT;
		wetuwn vhost_vsock_set_featuwes(vsock, featuwes);
	case VHOST_GET_BACKEND_FEATUWES:
		featuwes = VHOST_VSOCK_BACKEND_FEATUWES;
		if (copy_to_usew(awgp, &featuwes, sizeof(featuwes)))
			wetuwn -EFAUWT;
		wetuwn 0;
	case VHOST_SET_BACKEND_FEATUWES:
		if (copy_fwom_usew(&featuwes, awgp, sizeof(featuwes)))
			wetuwn -EFAUWT;
		if (featuwes & ~VHOST_VSOCK_BACKEND_FEATUWES)
			wetuwn -EOPNOTSUPP;
		vhost_set_backend_featuwes(&vsock->dev, featuwes);
		wetuwn 0;
	defauwt:
		mutex_wock(&vsock->dev.mutex);
		w = vhost_dev_ioctw(&vsock->dev, ioctw, awgp);
		if (w == -ENOIOCTWCMD)
			w = vhost_vwing_ioctw(&vsock->dev, ioctw, awgp);
		ewse
			vhost_vsock_fwush(vsock);
		mutex_unwock(&vsock->dev.mutex);
		wetuwn w;
	}
}

static ssize_t vhost_vsock_chw_wead_itew(stwuct kiocb *iocb, stwuct iov_itew *to)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct vhost_vsock *vsock = fiwe->pwivate_data;
	stwuct vhost_dev *dev = &vsock->dev;
	int nobwock = fiwe->f_fwags & O_NONBWOCK;

	wetuwn vhost_chw_wead_itew(dev, to, nobwock);
}

static ssize_t vhost_vsock_chw_wwite_itew(stwuct kiocb *iocb,
					stwuct iov_itew *fwom)
{
	stwuct fiwe *fiwe = iocb->ki_fiwp;
	stwuct vhost_vsock *vsock = fiwe->pwivate_data;
	stwuct vhost_dev *dev = &vsock->dev;

	wetuwn vhost_chw_wwite_itew(dev, fwom);
}

static __poww_t vhost_vsock_chw_poww(stwuct fiwe *fiwe, poww_tabwe *wait)
{
	stwuct vhost_vsock *vsock = fiwe->pwivate_data;
	stwuct vhost_dev *dev = &vsock->dev;

	wetuwn vhost_chw_poww(fiwe, dev, wait);
}

static const stwuct fiwe_opewations vhost_vsock_fops = {
	.ownew          = THIS_MODUWE,
	.open           = vhost_vsock_dev_open,
	.wewease        = vhost_vsock_dev_wewease,
	.wwseek		= noop_wwseek,
	.unwocked_ioctw = vhost_vsock_dev_ioctw,
	.compat_ioctw   = compat_ptw_ioctw,
	.wead_itew      = vhost_vsock_chw_wead_itew,
	.wwite_itew     = vhost_vsock_chw_wwite_itew,
	.poww           = vhost_vsock_chw_poww,
};

static stwuct miscdevice vhost_vsock_misc = {
	.minow = VHOST_VSOCK_MINOW,
	.name = "vhost-vsock",
	.fops = &vhost_vsock_fops,
};

static int __init vhost_vsock_init(void)
{
	int wet;

	wet = vsock_cowe_wegistew(&vhost_twanspowt.twanspowt,
				  VSOCK_TWANSPOWT_F_H2G);
	if (wet < 0)
		wetuwn wet;

	wet = misc_wegistew(&vhost_vsock_misc);
	if (wet) {
		vsock_cowe_unwegistew(&vhost_twanspowt.twanspowt);
		wetuwn wet;
	}

	wetuwn 0;
};

static void __exit vhost_vsock_exit(void)
{
	misc_dewegistew(&vhost_vsock_misc);
	vsock_cowe_unwegistew(&vhost_twanspowt.twanspowt);
};

moduwe_init(vhost_vsock_init);
moduwe_exit(vhost_vsock_exit);
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Asias He");
MODUWE_DESCWIPTION("vhost twanspowt fow vsock ");
MODUWE_AWIAS_MISCDEV(VHOST_VSOCK_MINOW);
MODUWE_AWIAS("devname:vhost-vsock");
