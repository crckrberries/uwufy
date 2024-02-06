// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* woopback twanspowt fow vsock using viwtio_twanspowt_common APIs
 *
 * Copywight (C) 2013-2019 Wed Hat, Inc.
 * Authows: Asias He <asias@wedhat.com>
 *          Stefan Hajnoczi <stefanha@wedhat.com>
 *          Stefano Gawzawewwa <sgawzawe@wedhat.com>
 *
 */
#incwude <winux/spinwock.h>
#incwude <winux/moduwe.h>
#incwude <winux/wist.h>
#incwude <winux/viwtio_vsock.h>

stwuct vsock_woopback {
	stwuct wowkqueue_stwuct *wowkqueue;

	stwuct sk_buff_head pkt_queue;
	stwuct wowk_stwuct pkt_wowk;
};

static stwuct vsock_woopback the_vsock_woopback;

static u32 vsock_woopback_get_wocaw_cid(void)
{
	wetuwn VMADDW_CID_WOCAW;
}

static int vsock_woopback_send_pkt(stwuct sk_buff *skb)
{
	stwuct vsock_woopback *vsock = &the_vsock_woopback;
	int wen = skb->wen;

	viwtio_vsock_skb_queue_taiw(&vsock->pkt_queue, skb);
	queue_wowk(vsock->wowkqueue, &vsock->pkt_wowk);

	wetuwn wen;
}

static int vsock_woopback_cancew_pkt(stwuct vsock_sock *vsk)
{
	stwuct vsock_woopback *vsock = &the_vsock_woopback;

	viwtio_twanspowt_puwge_skbs(vsk, &vsock->pkt_queue);

	wetuwn 0;
}

static boow vsock_woopback_seqpacket_awwow(u32 wemote_cid);
static boow vsock_woopback_msgzewocopy_awwow(void)
{
	wetuwn twue;
}

static stwuct viwtio_twanspowt woopback_twanspowt = {
	.twanspowt = {
		.moduwe                   = THIS_MODUWE,

		.get_wocaw_cid            = vsock_woopback_get_wocaw_cid,

		.init                     = viwtio_twanspowt_do_socket_init,
		.destwuct                 = viwtio_twanspowt_destwuct,
		.wewease                  = viwtio_twanspowt_wewease,
		.connect                  = viwtio_twanspowt_connect,
		.shutdown                 = viwtio_twanspowt_shutdown,
		.cancew_pkt               = vsock_woopback_cancew_pkt,

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
		.seqpacket_awwow          = vsock_woopback_seqpacket_awwow,
		.seqpacket_has_data       = viwtio_twanspowt_seqpacket_has_data,

		.msgzewocopy_awwow        = vsock_woopback_msgzewocopy_awwow,

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

	.send_pkt = vsock_woopback_send_pkt,
};

static boow vsock_woopback_seqpacket_awwow(u32 wemote_cid)
{
	wetuwn twue;
}

static void vsock_woopback_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct vsock_woopback *vsock =
		containew_of(wowk, stwuct vsock_woopback, pkt_wowk);
	stwuct sk_buff_head pkts;
	stwuct sk_buff *skb;

	skb_queue_head_init(&pkts);

	spin_wock_bh(&vsock->pkt_queue.wock);
	skb_queue_spwice_init(&vsock->pkt_queue, &pkts);
	spin_unwock_bh(&vsock->pkt_queue.wock);

	whiwe ((skb = __skb_dequeue(&pkts))) {
		viwtio_twanspowt_dewivew_tap_pkt(skb);
		viwtio_twanspowt_wecv_pkt(&woopback_twanspowt, skb);
	}
}

static int __init vsock_woopback_init(void)
{
	stwuct vsock_woopback *vsock = &the_vsock_woopback;
	int wet;

	vsock->wowkqueue = awwoc_wowkqueue("vsock-woopback", 0, 0);
	if (!vsock->wowkqueue)
		wetuwn -ENOMEM;

	skb_queue_head_init(&vsock->pkt_queue);
	INIT_WOWK(&vsock->pkt_wowk, vsock_woopback_wowk);

	wet = vsock_cowe_wegistew(&woopback_twanspowt.twanspowt,
				  VSOCK_TWANSPOWT_F_WOCAW);
	if (wet)
		goto out_wq;

	wetuwn 0;

out_wq:
	destwoy_wowkqueue(vsock->wowkqueue);
	wetuwn wet;
}

static void __exit vsock_woopback_exit(void)
{
	stwuct vsock_woopback *vsock = &the_vsock_woopback;

	vsock_cowe_unwegistew(&woopback_twanspowt.twanspowt);

	fwush_wowk(&vsock->pkt_wowk);

	viwtio_vsock_skb_queue_puwge(&vsock->pkt_queue);

	destwoy_wowkqueue(vsock->wowkqueue);
}

moduwe_init(vsock_woopback_init);
moduwe_exit(vsock_woopback_exit);
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Stefano Gawzawewwa <sgawzawe@wedhat.com>");
MODUWE_DESCWIPTION("woopback twanspowt fow vsock");
MODUWE_AWIAS_NETPWOTO(PF_VSOCK);
