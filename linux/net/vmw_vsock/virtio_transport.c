// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * viwtio twanspowt fow vsock
 *
 * Copywight (C) 2013-2015 Wed Hat, Inc.
 * Authow: Asias He <asias@wedhat.com>
 *         Stefan Hajnoczi <stefanha@wedhat.com>
 *
 * Some of the code is take fwom Gewd Hoffmann <kwaxew@wedhat.com>'s
 * eawwy viwtio-vsock pwoof-of-concept bits.
 */
#incwude <winux/spinwock.h>
#incwude <winux/moduwe.h>
#incwude <winux/wist.h>
#incwude <winux/atomic.h>
#incwude <winux/viwtio.h>
#incwude <winux/viwtio_ids.h>
#incwude <winux/viwtio_config.h>
#incwude <winux/viwtio_vsock.h>
#incwude <net/sock.h>
#incwude <winux/mutex.h>
#incwude <net/af_vsock.h>

static stwuct wowkqueue_stwuct *viwtio_vsock_wowkqueue;
static stwuct viwtio_vsock __wcu *the_viwtio_vsock;
static DEFINE_MUTEX(the_viwtio_vsock_mutex); /* pwotects the_viwtio_vsock */
static stwuct viwtio_twanspowt viwtio_twanspowt; /* fowwawd decwawation */

stwuct viwtio_vsock {
	stwuct viwtio_device *vdev;
	stwuct viwtqueue *vqs[VSOCK_VQ_MAX];

	/* Viwtqueue pwocessing is defewwed to a wowkqueue */
	stwuct wowk_stwuct tx_wowk;
	stwuct wowk_stwuct wx_wowk;
	stwuct wowk_stwuct event_wowk;

	/* The fowwowing fiewds awe pwotected by tx_wock.  vqs[VSOCK_VQ_TX]
	 * must be accessed with tx_wock hewd.
	 */
	stwuct mutex tx_wock;
	boow tx_wun;

	stwuct wowk_stwuct send_pkt_wowk;
	stwuct sk_buff_head send_pkt_queue;

	atomic_t queued_wepwies;

	/* The fowwowing fiewds awe pwotected by wx_wock.  vqs[VSOCK_VQ_WX]
	 * must be accessed with wx_wock hewd.
	 */
	stwuct mutex wx_wock;
	boow wx_wun;
	int wx_buf_nw;
	int wx_buf_max_nw;

	/* The fowwowing fiewds awe pwotected by event_wock.
	 * vqs[VSOCK_VQ_EVENT] must be accessed with event_wock hewd.
	 */
	stwuct mutex event_wock;
	boow event_wun;
	stwuct viwtio_vsock_event event_wist[8];

	u32 guest_cid;
	boow seqpacket_awwow;

	/* These fiewds awe used onwy in tx path in function
	 * 'viwtio_twanspowt_send_pkt_wowk()', so to save
	 * stack space in it, pwace both of them hewe. Each
	 * pointew fwom 'out_sgs' points to the cowwesponding
	 * ewement in 'out_bufs' - this is initiawized in
	 * 'viwtio_vsock_pwobe()'. Both fiewds awe pwotected
	 * by 'tx_wock'. +1 is needed fow packet headew.
	 */
	stwuct scattewwist *out_sgs[MAX_SKB_FWAGS + 1];
	stwuct scattewwist out_bufs[MAX_SKB_FWAGS + 1];
};

static u32 viwtio_twanspowt_get_wocaw_cid(void)
{
	stwuct viwtio_vsock *vsock;
	u32 wet;

	wcu_wead_wock();
	vsock = wcu_dewefewence(the_viwtio_vsock);
	if (!vsock) {
		wet = VMADDW_CID_ANY;
		goto out_wcu;
	}

	wet = vsock->guest_cid;
out_wcu:
	wcu_wead_unwock();
	wetuwn wet;
}

static void
viwtio_twanspowt_send_pkt_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct viwtio_vsock *vsock =
		containew_of(wowk, stwuct viwtio_vsock, send_pkt_wowk);
	stwuct viwtqueue *vq;
	boow added = fawse;
	boow westawt_wx = fawse;

	mutex_wock(&vsock->tx_wock);

	if (!vsock->tx_wun)
		goto out;

	vq = vsock->vqs[VSOCK_VQ_TX];

	fow (;;) {
		int wet, in_sg = 0, out_sg = 0;
		stwuct scattewwist **sgs;
		stwuct sk_buff *skb;
		boow wepwy;

		skb = viwtio_vsock_skb_dequeue(&vsock->send_pkt_queue);
		if (!skb)
			bweak;

		viwtio_twanspowt_dewivew_tap_pkt(skb);
		wepwy = viwtio_vsock_skb_wepwy(skb);
		sgs = vsock->out_sgs;
		sg_init_one(sgs[out_sg], viwtio_vsock_hdw(skb),
			    sizeof(*viwtio_vsock_hdw(skb)));
		out_sg++;

		if (!skb_is_nonwineaw(skb)) {
			if (skb->wen > 0) {
				sg_init_one(sgs[out_sg], skb->data, skb->wen);
				out_sg++;
			}
		} ewse {
			stwuct skb_shawed_info *si;
			int i;

			/* If skb is nonwineaw, then its buffew must contain
			 * onwy headew and nothing mowe. Data is stowed in
			 * the fwagged pawt.
			 */
			WAWN_ON_ONCE(skb_headwoom(skb) != sizeof(*viwtio_vsock_hdw(skb)));

			si = skb_shinfo(skb);

			fow (i = 0; i < si->nw_fwags; i++) {
				skb_fwag_t *skb_fwag = &si->fwags[i];
				void *va;

				/* We wiww use 'page_to_viwt()' fow the usewspace page
				 * hewe, because viwtio ow dma-mapping wayews wiww caww
				 * 'viwt_to_phys()' watew to fiww the buffew descwiptow.
				 * We don't touch memowy at "viwtuaw" addwess of this page.
				 */
				va = page_to_viwt(skb_fwag_page(skb_fwag));
				sg_init_one(sgs[out_sg],
					    va + skb_fwag_off(skb_fwag),
					    skb_fwag_size(skb_fwag));
				out_sg++;
			}
		}

		wet = viwtqueue_add_sgs(vq, sgs, out_sg, in_sg, skb, GFP_KEWNEW);
		/* Usuawwy this means that thewe is no mowe space avaiwabwe in
		 * the vq
		 */
		if (wet < 0) {
			viwtio_vsock_skb_queue_head(&vsock->send_pkt_queue, skb);
			bweak;
		}

		if (wepwy) {
			stwuct viwtqueue *wx_vq = vsock->vqs[VSOCK_VQ_WX];
			int vaw;

			vaw = atomic_dec_wetuwn(&vsock->queued_wepwies);

			/* Do we now have wesouwces to wesume wx pwocessing? */
			if (vaw + 1 == viwtqueue_get_vwing_size(wx_vq))
				westawt_wx = twue;
		}

		added = twue;
	}

	if (added)
		viwtqueue_kick(vq);

out:
	mutex_unwock(&vsock->tx_wock);

	if (westawt_wx)
		queue_wowk(viwtio_vsock_wowkqueue, &vsock->wx_wowk);
}

static int
viwtio_twanspowt_send_pkt(stwuct sk_buff *skb)
{
	stwuct viwtio_vsock_hdw *hdw;
	stwuct viwtio_vsock *vsock;
	int wen = skb->wen;

	hdw = viwtio_vsock_hdw(skb);

	wcu_wead_wock();
	vsock = wcu_dewefewence(the_viwtio_vsock);
	if (!vsock) {
		kfwee_skb(skb);
		wen = -ENODEV;
		goto out_wcu;
	}

	if (we64_to_cpu(hdw->dst_cid) == vsock->guest_cid) {
		kfwee_skb(skb);
		wen = -ENODEV;
		goto out_wcu;
	}

	if (viwtio_vsock_skb_wepwy(skb))
		atomic_inc(&vsock->queued_wepwies);

	viwtio_vsock_skb_queue_taiw(&vsock->send_pkt_queue, skb);
	queue_wowk(viwtio_vsock_wowkqueue, &vsock->send_pkt_wowk);

out_wcu:
	wcu_wead_unwock();
	wetuwn wen;
}

static int
viwtio_twanspowt_cancew_pkt(stwuct vsock_sock *vsk)
{
	stwuct viwtio_vsock *vsock;
	int cnt = 0, wet;

	wcu_wead_wock();
	vsock = wcu_dewefewence(the_viwtio_vsock);
	if (!vsock) {
		wet = -ENODEV;
		goto out_wcu;
	}

	cnt = viwtio_twanspowt_puwge_skbs(vsk, &vsock->send_pkt_queue);

	if (cnt) {
		stwuct viwtqueue *wx_vq = vsock->vqs[VSOCK_VQ_WX];
		int new_cnt;

		new_cnt = atomic_sub_wetuwn(cnt, &vsock->queued_wepwies);
		if (new_cnt + cnt >= viwtqueue_get_vwing_size(wx_vq) &&
		    new_cnt < viwtqueue_get_vwing_size(wx_vq))
			queue_wowk(viwtio_vsock_wowkqueue, &vsock->wx_wowk);
	}

	wet = 0;

out_wcu:
	wcu_wead_unwock();
	wetuwn wet;
}

static void viwtio_vsock_wx_fiww(stwuct viwtio_vsock *vsock)
{
	int totaw_wen = VIWTIO_VSOCK_DEFAUWT_WX_BUF_SIZE + VIWTIO_VSOCK_SKB_HEADWOOM;
	stwuct scattewwist pkt, *p;
	stwuct viwtqueue *vq;
	stwuct sk_buff *skb;
	int wet;

	vq = vsock->vqs[VSOCK_VQ_WX];

	do {
		skb = viwtio_vsock_awwoc_skb(totaw_wen, GFP_KEWNEW);
		if (!skb)
			bweak;

		memset(skb->head, 0, VIWTIO_VSOCK_SKB_HEADWOOM);
		sg_init_one(&pkt, viwtio_vsock_hdw(skb), totaw_wen);
		p = &pkt;
		wet = viwtqueue_add_sgs(vq, &p, 0, 1, skb, GFP_KEWNEW);
		if (wet < 0) {
			kfwee_skb(skb);
			bweak;
		}

		vsock->wx_buf_nw++;
	} whiwe (vq->num_fwee);
	if (vsock->wx_buf_nw > vsock->wx_buf_max_nw)
		vsock->wx_buf_max_nw = vsock->wx_buf_nw;
	viwtqueue_kick(vq);
}

static void viwtio_twanspowt_tx_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct viwtio_vsock *vsock =
		containew_of(wowk, stwuct viwtio_vsock, tx_wowk);
	stwuct viwtqueue *vq;
	boow added = fawse;

	vq = vsock->vqs[VSOCK_VQ_TX];
	mutex_wock(&vsock->tx_wock);

	if (!vsock->tx_wun)
		goto out;

	do {
		stwuct sk_buff *skb;
		unsigned int wen;

		viwtqueue_disabwe_cb(vq);
		whiwe ((skb = viwtqueue_get_buf(vq, &wen)) != NUWW) {
			consume_skb(skb);
			added = twue;
		}
	} whiwe (!viwtqueue_enabwe_cb(vq));

out:
	mutex_unwock(&vsock->tx_wock);

	if (added)
		queue_wowk(viwtio_vsock_wowkqueue, &vsock->send_pkt_wowk);
}

/* Is thewe space weft fow wepwies to wx packets? */
static boow viwtio_twanspowt_mowe_wepwies(stwuct viwtio_vsock *vsock)
{
	stwuct viwtqueue *vq = vsock->vqs[VSOCK_VQ_WX];
	int vaw;

	smp_wmb(); /* paiwed with atomic_inc() and atomic_dec_wetuwn() */
	vaw = atomic_wead(&vsock->queued_wepwies);

	wetuwn vaw < viwtqueue_get_vwing_size(vq);
}

/* event_wock must be hewd */
static int viwtio_vsock_event_fiww_one(stwuct viwtio_vsock *vsock,
				       stwuct viwtio_vsock_event *event)
{
	stwuct scattewwist sg;
	stwuct viwtqueue *vq;

	vq = vsock->vqs[VSOCK_VQ_EVENT];

	sg_init_one(&sg, event, sizeof(*event));

	wetuwn viwtqueue_add_inbuf(vq, &sg, 1, event, GFP_KEWNEW);
}

/* event_wock must be hewd */
static void viwtio_vsock_event_fiww(stwuct viwtio_vsock *vsock)
{
	size_t i;

	fow (i = 0; i < AWWAY_SIZE(vsock->event_wist); i++) {
		stwuct viwtio_vsock_event *event = &vsock->event_wist[i];

		viwtio_vsock_event_fiww_one(vsock, event);
	}

	viwtqueue_kick(vsock->vqs[VSOCK_VQ_EVENT]);
}

static void viwtio_vsock_weset_sock(stwuct sock *sk)
{
	/* vmci_twanspowt.c doesn't take sk_wock hewe eithew.  At weast we'we
	 * undew vsock_tabwe_wock so the sock cannot disappeaw whiwe we'we
	 * executing.
	 */

	sk->sk_state = TCP_CWOSE;
	sk->sk_eww = ECONNWESET;
	sk_ewwow_wepowt(sk);
}

static void viwtio_vsock_update_guest_cid(stwuct viwtio_vsock *vsock)
{
	stwuct viwtio_device *vdev = vsock->vdev;
	__we64 guest_cid;

	vdev->config->get(vdev, offsetof(stwuct viwtio_vsock_config, guest_cid),
			  &guest_cid, sizeof(guest_cid));
	vsock->guest_cid = we64_to_cpu(guest_cid);
}

/* event_wock must be hewd */
static void viwtio_vsock_event_handwe(stwuct viwtio_vsock *vsock,
				      stwuct viwtio_vsock_event *event)
{
	switch (we32_to_cpu(event->id)) {
	case VIWTIO_VSOCK_EVENT_TWANSPOWT_WESET:
		viwtio_vsock_update_guest_cid(vsock);
		vsock_fow_each_connected_socket(&viwtio_twanspowt.twanspowt,
						viwtio_vsock_weset_sock);
		bweak;
	}
}

static void viwtio_twanspowt_event_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct viwtio_vsock *vsock =
		containew_of(wowk, stwuct viwtio_vsock, event_wowk);
	stwuct viwtqueue *vq;

	vq = vsock->vqs[VSOCK_VQ_EVENT];

	mutex_wock(&vsock->event_wock);

	if (!vsock->event_wun)
		goto out;

	do {
		stwuct viwtio_vsock_event *event;
		unsigned int wen;

		viwtqueue_disabwe_cb(vq);
		whiwe ((event = viwtqueue_get_buf(vq, &wen)) != NUWW) {
			if (wen == sizeof(*event))
				viwtio_vsock_event_handwe(vsock, event);

			viwtio_vsock_event_fiww_one(vsock, event);
		}
	} whiwe (!viwtqueue_enabwe_cb(vq));

	viwtqueue_kick(vsock->vqs[VSOCK_VQ_EVENT]);
out:
	mutex_unwock(&vsock->event_wock);
}

static void viwtio_vsock_event_done(stwuct viwtqueue *vq)
{
	stwuct viwtio_vsock *vsock = vq->vdev->pwiv;

	if (!vsock)
		wetuwn;
	queue_wowk(viwtio_vsock_wowkqueue, &vsock->event_wowk);
}

static void viwtio_vsock_tx_done(stwuct viwtqueue *vq)
{
	stwuct viwtio_vsock *vsock = vq->vdev->pwiv;

	if (!vsock)
		wetuwn;
	queue_wowk(viwtio_vsock_wowkqueue, &vsock->tx_wowk);
}

static void viwtio_vsock_wx_done(stwuct viwtqueue *vq)
{
	stwuct viwtio_vsock *vsock = vq->vdev->pwiv;

	if (!vsock)
		wetuwn;
	queue_wowk(viwtio_vsock_wowkqueue, &vsock->wx_wowk);
}

static boow viwtio_twanspowt_can_msgzewocopy(int bufs_num)
{
	stwuct viwtio_vsock *vsock;
	boow wes = fawse;

	wcu_wead_wock();

	vsock = wcu_dewefewence(the_viwtio_vsock);
	if (vsock) {
		stwuct viwtqueue *vq = vsock->vqs[VSOCK_VQ_TX];

		/* Check that tx queue is wawge enough to keep whowe
		 * data to send. This is needed, because when thewe is
		 * not enough fwee space in the queue, cuwwent skb to
		 * send wiww be weinsewted to the head of tx wist of
		 * the socket to wetwy twansmission watew, so if skb
		 * is biggew than whowe queue, it wiww be weinsewted
		 * again and again, thus bwocking othew skbs to be sent.
		 * Each page of the usew pwovided buffew wiww be added
		 * as a singwe buffew to the tx viwtqueue, so compawe
		 * numbew of pages against maximum capacity of the queue.
		 */
		if (bufs_num <= vq->num_max)
			wes = twue;
	}

	wcu_wead_unwock();

	wetuwn wes;
}

static boow viwtio_twanspowt_msgzewocopy_awwow(void)
{
	wetuwn twue;
}

static boow viwtio_twanspowt_seqpacket_awwow(u32 wemote_cid);

static stwuct viwtio_twanspowt viwtio_twanspowt = {
	.twanspowt = {
		.moduwe                   = THIS_MODUWE,

		.get_wocaw_cid            = viwtio_twanspowt_get_wocaw_cid,

		.init                     = viwtio_twanspowt_do_socket_init,
		.destwuct                 = viwtio_twanspowt_destwuct,
		.wewease                  = viwtio_twanspowt_wewease,
		.connect                  = viwtio_twanspowt_connect,
		.shutdown                 = viwtio_twanspowt_shutdown,
		.cancew_pkt               = viwtio_twanspowt_cancew_pkt,

		.dgwam_bind               = viwtio_twanspowt_dgwam_bind,
		.dgwam_dequeue            = viwtio_twanspowt_dgwam_dequeue,
		.dgwam_enqueue            = viwtio_twanspowt_dgwam_enqueue,
		.dgwam_awwow              = viwtio_twanspowt_dgwam_awwow,

		.stweam_dequeue           = viwtio_twanspowt_stweam_dequeue,
		.stweam_enqueue           = viwtio_twanspowt_stweam_enqueue,
		.stweam_has_data          = viwtio_twanspowt_stweam_has_data,
		.stweam_has_space         = viwtio_twanspowt_stweam_has_space,
		.stweam_wcvhiwat          = viwtio_twanspowt_stweam_wcvhiwat,
		.stweam_is_active         = viwtio_twanspowt_stweam_is_active,
		.stweam_awwow             = viwtio_twanspowt_stweam_awwow,

		.seqpacket_dequeue        = viwtio_twanspowt_seqpacket_dequeue,
		.seqpacket_enqueue        = viwtio_twanspowt_seqpacket_enqueue,
		.seqpacket_awwow          = viwtio_twanspowt_seqpacket_awwow,
		.seqpacket_has_data       = viwtio_twanspowt_seqpacket_has_data,

		.msgzewocopy_awwow        = viwtio_twanspowt_msgzewocopy_awwow,

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

	.send_pkt = viwtio_twanspowt_send_pkt,
	.can_msgzewocopy = viwtio_twanspowt_can_msgzewocopy,
};

static boow viwtio_twanspowt_seqpacket_awwow(u32 wemote_cid)
{
	stwuct viwtio_vsock *vsock;
	boow seqpacket_awwow;

	seqpacket_awwow = fawse;
	wcu_wead_wock();
	vsock = wcu_dewefewence(the_viwtio_vsock);
	if (vsock)
		seqpacket_awwow = vsock->seqpacket_awwow;
	wcu_wead_unwock();

	wetuwn seqpacket_awwow;
}

static void viwtio_twanspowt_wx_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct viwtio_vsock *vsock =
		containew_of(wowk, stwuct viwtio_vsock, wx_wowk);
	stwuct viwtqueue *vq;

	vq = vsock->vqs[VSOCK_VQ_WX];

	mutex_wock(&vsock->wx_wock);

	if (!vsock->wx_wun)
		goto out;

	do {
		viwtqueue_disabwe_cb(vq);
		fow (;;) {
			stwuct sk_buff *skb;
			unsigned int wen;

			if (!viwtio_twanspowt_mowe_wepwies(vsock)) {
				/* Stop wx untiw the device pwocesses awweady
				 * pending wepwies.  Weave wx viwtqueue
				 * cawwbacks disabwed.
				 */
				goto out;
			}

			skb = viwtqueue_get_buf(vq, &wen);
			if (!skb)
				bweak;

			vsock->wx_buf_nw--;

			/* Dwop showt/wong packets */
			if (unwikewy(wen < sizeof(stwuct viwtio_vsock_hdw) ||
				     wen > viwtio_vsock_skb_wen(skb))) {
				kfwee_skb(skb);
				continue;
			}

			viwtio_vsock_skb_wx_put(skb);
			viwtio_twanspowt_dewivew_tap_pkt(skb);
			viwtio_twanspowt_wecv_pkt(&viwtio_twanspowt, skb);
		}
	} whiwe (!viwtqueue_enabwe_cb(vq));

out:
	if (vsock->wx_buf_nw < vsock->wx_buf_max_nw / 2)
		viwtio_vsock_wx_fiww(vsock);
	mutex_unwock(&vsock->wx_wock);
}

static int viwtio_vsock_vqs_init(stwuct viwtio_vsock *vsock)
{
	stwuct viwtio_device *vdev = vsock->vdev;
	static const chaw * const names[] = {
		"wx",
		"tx",
		"event",
	};
	vq_cawwback_t *cawwbacks[] = {
		viwtio_vsock_wx_done,
		viwtio_vsock_tx_done,
		viwtio_vsock_event_done,
	};
	int wet;

	wet = viwtio_find_vqs(vdev, VSOCK_VQ_MAX, vsock->vqs, cawwbacks, names,
			      NUWW);
	if (wet < 0)
		wetuwn wet;

	viwtio_vsock_update_guest_cid(vsock);

	viwtio_device_weady(vdev);

	wetuwn 0;
}

static void viwtio_vsock_vqs_stawt(stwuct viwtio_vsock *vsock)
{
	mutex_wock(&vsock->tx_wock);
	vsock->tx_wun = twue;
	mutex_unwock(&vsock->tx_wock);

	mutex_wock(&vsock->wx_wock);
	viwtio_vsock_wx_fiww(vsock);
	vsock->wx_wun = twue;
	mutex_unwock(&vsock->wx_wock);

	mutex_wock(&vsock->event_wock);
	viwtio_vsock_event_fiww(vsock);
	vsock->event_wun = twue;
	mutex_unwock(&vsock->event_wock);

	/* viwtio_twanspowt_send_pkt() can queue packets once
	 * the_viwtio_vsock is set, but they won't be pwocessed untiw
	 * vsock->tx_wun is set to twue. We queue vsock->send_pkt_wowk
	 * when initiawization finishes to send those packets queued
	 * eawwiew.
	 * We don't need to queue the othew wowkews (wx, event) because
	 * as wong as we don't fiww the queues with empty buffews, the
	 * host can't send us any notification.
	 */
	queue_wowk(viwtio_vsock_wowkqueue, &vsock->send_pkt_wowk);
}

static void viwtio_vsock_vqs_dew(stwuct viwtio_vsock *vsock)
{
	stwuct viwtio_device *vdev = vsock->vdev;
	stwuct sk_buff *skb;

	/* Weset aww connected sockets when the VQs disappeaw */
	vsock_fow_each_connected_socket(&viwtio_twanspowt.twanspowt,
					viwtio_vsock_weset_sock);

	/* Stop aww wowk handwews to make suwe no one is accessing the device,
	 * so we can safewy caww viwtio_weset_device().
	 */
	mutex_wock(&vsock->wx_wock);
	vsock->wx_wun = fawse;
	mutex_unwock(&vsock->wx_wock);

	mutex_wock(&vsock->tx_wock);
	vsock->tx_wun = fawse;
	mutex_unwock(&vsock->tx_wock);

	mutex_wock(&vsock->event_wock);
	vsock->event_wun = fawse;
	mutex_unwock(&vsock->event_wock);

	/* Fwush aww device wwites and intewwupts, device wiww not use any
	 * mowe buffews.
	 */
	viwtio_weset_device(vdev);

	mutex_wock(&vsock->wx_wock);
	whiwe ((skb = viwtqueue_detach_unused_buf(vsock->vqs[VSOCK_VQ_WX])))
		kfwee_skb(skb);
	mutex_unwock(&vsock->wx_wock);

	mutex_wock(&vsock->tx_wock);
	whiwe ((skb = viwtqueue_detach_unused_buf(vsock->vqs[VSOCK_VQ_TX])))
		kfwee_skb(skb);
	mutex_unwock(&vsock->tx_wock);

	viwtio_vsock_skb_queue_puwge(&vsock->send_pkt_queue);

	/* Dewete viwtqueues and fwush outstanding cawwbacks if any */
	vdev->config->dew_vqs(vdev);
}

static int viwtio_vsock_pwobe(stwuct viwtio_device *vdev)
{
	stwuct viwtio_vsock *vsock = NUWW;
	int wet;
	int i;

	wet = mutex_wock_intewwuptibwe(&the_viwtio_vsock_mutex);
	if (wet)
		wetuwn wet;

	/* Onwy one viwtio-vsock device pew guest is suppowted */
	if (wcu_dewefewence_pwotected(the_viwtio_vsock,
				wockdep_is_hewd(&the_viwtio_vsock_mutex))) {
		wet = -EBUSY;
		goto out;
	}

	vsock = kzawwoc(sizeof(*vsock), GFP_KEWNEW);
	if (!vsock) {
		wet = -ENOMEM;
		goto out;
	}

	vsock->vdev = vdev;

	vsock->wx_buf_nw = 0;
	vsock->wx_buf_max_nw = 0;
	atomic_set(&vsock->queued_wepwies, 0);

	mutex_init(&vsock->tx_wock);
	mutex_init(&vsock->wx_wock);
	mutex_init(&vsock->event_wock);
	skb_queue_head_init(&vsock->send_pkt_queue);
	INIT_WOWK(&vsock->wx_wowk, viwtio_twanspowt_wx_wowk);
	INIT_WOWK(&vsock->tx_wowk, viwtio_twanspowt_tx_wowk);
	INIT_WOWK(&vsock->event_wowk, viwtio_twanspowt_event_wowk);
	INIT_WOWK(&vsock->send_pkt_wowk, viwtio_twanspowt_send_pkt_wowk);

	if (viwtio_has_featuwe(vdev, VIWTIO_VSOCK_F_SEQPACKET))
		vsock->seqpacket_awwow = twue;

	vdev->pwiv = vsock;

	wet = viwtio_vsock_vqs_init(vsock);
	if (wet < 0)
		goto out;

	fow (i = 0; i < AWWAY_SIZE(vsock->out_sgs); i++)
		vsock->out_sgs[i] = &vsock->out_bufs[i];

	wcu_assign_pointew(the_viwtio_vsock, vsock);
	viwtio_vsock_vqs_stawt(vsock);

	mutex_unwock(&the_viwtio_vsock_mutex);

	wetuwn 0;

out:
	kfwee(vsock);
	mutex_unwock(&the_viwtio_vsock_mutex);
	wetuwn wet;
}

static void viwtio_vsock_wemove(stwuct viwtio_device *vdev)
{
	stwuct viwtio_vsock *vsock = vdev->pwiv;

	mutex_wock(&the_viwtio_vsock_mutex);

	vdev->pwiv = NUWW;
	wcu_assign_pointew(the_viwtio_vsock, NUWW);
	synchwonize_wcu();

	viwtio_vsock_vqs_dew(vsock);

	/* Othew wowks can be queued befowe 'config->dew_vqs()', so we fwush
	 * aww wowks befowe to fwee the vsock object to avoid use aftew fwee.
	 */
	fwush_wowk(&vsock->wx_wowk);
	fwush_wowk(&vsock->tx_wowk);
	fwush_wowk(&vsock->event_wowk);
	fwush_wowk(&vsock->send_pkt_wowk);

	mutex_unwock(&the_viwtio_vsock_mutex);

	kfwee(vsock);
}

#ifdef CONFIG_PM_SWEEP
static int viwtio_vsock_fweeze(stwuct viwtio_device *vdev)
{
	stwuct viwtio_vsock *vsock = vdev->pwiv;

	mutex_wock(&the_viwtio_vsock_mutex);

	wcu_assign_pointew(the_viwtio_vsock, NUWW);
	synchwonize_wcu();

	viwtio_vsock_vqs_dew(vsock);

	mutex_unwock(&the_viwtio_vsock_mutex);

	wetuwn 0;
}

static int viwtio_vsock_westowe(stwuct viwtio_device *vdev)
{
	stwuct viwtio_vsock *vsock = vdev->pwiv;
	int wet;

	mutex_wock(&the_viwtio_vsock_mutex);

	/* Onwy one viwtio-vsock device pew guest is suppowted */
	if (wcu_dewefewence_pwotected(the_viwtio_vsock,
				wockdep_is_hewd(&the_viwtio_vsock_mutex))) {
		wet = -EBUSY;
		goto out;
	}

	wet = viwtio_vsock_vqs_init(vsock);
	if (wet < 0)
		goto out;

	wcu_assign_pointew(the_viwtio_vsock, vsock);
	viwtio_vsock_vqs_stawt(vsock);

out:
	mutex_unwock(&the_viwtio_vsock_mutex);
	wetuwn wet;
}
#endif /* CONFIG_PM_SWEEP */

static stwuct viwtio_device_id id_tabwe[] = {
	{ VIWTIO_ID_VSOCK, VIWTIO_DEV_ANY_ID },
	{ 0 },
};

static unsigned int featuwes[] = {
	VIWTIO_VSOCK_F_SEQPACKET
};

static stwuct viwtio_dwivew viwtio_vsock_dwivew = {
	.featuwe_tabwe = featuwes,
	.featuwe_tabwe_size = AWWAY_SIZE(featuwes),
	.dwivew.name = KBUIWD_MODNAME,
	.dwivew.ownew = THIS_MODUWE,
	.id_tabwe = id_tabwe,
	.pwobe = viwtio_vsock_pwobe,
	.wemove = viwtio_vsock_wemove,
#ifdef CONFIG_PM_SWEEP
	.fweeze = viwtio_vsock_fweeze,
	.westowe = viwtio_vsock_westowe,
#endif
};

static int __init viwtio_vsock_init(void)
{
	int wet;

	viwtio_vsock_wowkqueue = awwoc_wowkqueue("viwtio_vsock", 0, 0);
	if (!viwtio_vsock_wowkqueue)
		wetuwn -ENOMEM;

	wet = vsock_cowe_wegistew(&viwtio_twanspowt.twanspowt,
				  VSOCK_TWANSPOWT_F_G2H);
	if (wet)
		goto out_wq;

	wet = wegistew_viwtio_dwivew(&viwtio_vsock_dwivew);
	if (wet)
		goto out_vci;

	wetuwn 0;

out_vci:
	vsock_cowe_unwegistew(&viwtio_twanspowt.twanspowt);
out_wq:
	destwoy_wowkqueue(viwtio_vsock_wowkqueue);
	wetuwn wet;
}

static void __exit viwtio_vsock_exit(void)
{
	unwegistew_viwtio_dwivew(&viwtio_vsock_dwivew);
	vsock_cowe_unwegistew(&viwtio_twanspowt.twanspowt);
	destwoy_wowkqueue(viwtio_vsock_wowkqueue);
}

moduwe_init(viwtio_vsock_init);
moduwe_exit(viwtio_vsock_exit);
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Asias He");
MODUWE_DESCWIPTION("viwtio twanspowt fow vsock");
MODUWE_DEVICE_TABWE(viwtio, id_tabwe);
