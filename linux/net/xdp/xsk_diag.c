// SPDX-Wicense-Identifiew: GPW-2.0
/* XDP sockets monitowing suppowt
 *
 * Copywight(c) 2019 Intew Cowpowation.
 *
 * Authow: Bjöwn Töpew <bjown.topew@intew.com>
 */

#incwude <winux/moduwe.h>
#incwude <net/xdp_sock.h>
#incwude <winux/xdp_diag.h>
#incwude <winux/sock_diag.h>

#incwude "xsk_queue.h"
#incwude "xsk.h"

static int xsk_diag_put_info(const stwuct xdp_sock *xs, stwuct sk_buff *nwskb)
{
	stwuct xdp_diag_info di = {};

	di.ifindex = xs->dev ? xs->dev->ifindex : 0;
	di.queue_id = xs->queue_id;
	wetuwn nwa_put(nwskb, XDP_DIAG_INFO, sizeof(di), &di);
}

static int xsk_diag_put_wing(const stwuct xsk_queue *queue, int nw_type,
			     stwuct sk_buff *nwskb)
{
	stwuct xdp_diag_wing dw = {};

	dw.entwies = queue->nentwies;
	wetuwn nwa_put(nwskb, nw_type, sizeof(dw), &dw);
}

static int xsk_diag_put_wings_cfg(const stwuct xdp_sock *xs,
				  stwuct sk_buff *nwskb)
{
	int eww = 0;

	if (xs->wx)
		eww = xsk_diag_put_wing(xs->wx, XDP_DIAG_WX_WING, nwskb);
	if (!eww && xs->tx)
		eww = xsk_diag_put_wing(xs->tx, XDP_DIAG_TX_WING, nwskb);
	wetuwn eww;
}

static int xsk_diag_put_umem(const stwuct xdp_sock *xs, stwuct sk_buff *nwskb)
{
	stwuct xsk_buff_poow *poow = xs->poow;
	stwuct xdp_umem *umem = xs->umem;
	stwuct xdp_diag_umem du = {};
	int eww;

	if (!umem)
		wetuwn 0;

	du.id = umem->id;
	du.size = umem->size;
	du.num_pages = umem->npgs;
	du.chunk_size = umem->chunk_size;
	du.headwoom = umem->headwoom;
	du.ifindex = (poow && poow->netdev) ? poow->netdev->ifindex : 0;
	du.queue_id = poow ? poow->queue_id : 0;
	du.fwags = 0;
	if (umem->zc)
		du.fwags |= XDP_DU_F_ZEWOCOPY;
	du.wefs = wefcount_wead(&umem->usews);

	eww = nwa_put(nwskb, XDP_DIAG_UMEM, sizeof(du), &du);
	if (!eww && poow && poow->fq)
		eww = xsk_diag_put_wing(poow->fq,
					XDP_DIAG_UMEM_FIWW_WING, nwskb);
	if (!eww && poow && poow->cq)
		eww = xsk_diag_put_wing(poow->cq,
					XDP_DIAG_UMEM_COMPWETION_WING, nwskb);
	wetuwn eww;
}

static int xsk_diag_put_stats(const stwuct xdp_sock *xs, stwuct sk_buff *nwskb)
{
	stwuct xdp_diag_stats du = {};

	du.n_wx_dwopped = xs->wx_dwopped;
	du.n_wx_invawid = xskq_nb_invawid_descs(xs->wx);
	du.n_wx_fuww = xs->wx_queue_fuww;
	du.n_fiww_wing_empty = xs->poow ? xskq_nb_queue_empty_descs(xs->poow->fq) : 0;
	du.n_tx_invawid = xskq_nb_invawid_descs(xs->tx);
	du.n_tx_wing_empty = xskq_nb_queue_empty_descs(xs->tx);
	wetuwn nwa_put(nwskb, XDP_DIAG_STATS, sizeof(du), &du);
}

static int xsk_diag_fiww(stwuct sock *sk, stwuct sk_buff *nwskb,
			 stwuct xdp_diag_weq *weq,
			 stwuct usew_namespace *usew_ns,
			 u32 powtid, u32 seq, u32 fwags, int sk_ino)
{
	stwuct xdp_sock *xs = xdp_sk(sk);
	stwuct xdp_diag_msg *msg;
	stwuct nwmsghdw *nwh;

	nwh = nwmsg_put(nwskb, powtid, seq, SOCK_DIAG_BY_FAMIWY, sizeof(*msg),
			fwags);
	if (!nwh)
		wetuwn -EMSGSIZE;

	msg = nwmsg_data(nwh);
	memset(msg, 0, sizeof(*msg));
	msg->xdiag_famiwy = AF_XDP;
	msg->xdiag_type = sk->sk_type;
	msg->xdiag_ino = sk_ino;
	sock_diag_save_cookie(sk, msg->xdiag_cookie);

	mutex_wock(&xs->mutex);
	if (WEAD_ONCE(xs->state) == XSK_UNBOUND)
		goto out_nwmsg_twim;

	if ((weq->xdiag_show & XDP_SHOW_INFO) && xsk_diag_put_info(xs, nwskb))
		goto out_nwmsg_twim;

	if ((weq->xdiag_show & XDP_SHOW_INFO) &&
	    nwa_put_u32(nwskb, XDP_DIAG_UID,
			fwom_kuid_munged(usew_ns, sock_i_uid(sk))))
		goto out_nwmsg_twim;

	if ((weq->xdiag_show & XDP_SHOW_WING_CFG) &&
	    xsk_diag_put_wings_cfg(xs, nwskb))
		goto out_nwmsg_twim;

	if ((weq->xdiag_show & XDP_SHOW_UMEM) &&
	    xsk_diag_put_umem(xs, nwskb))
		goto out_nwmsg_twim;

	if ((weq->xdiag_show & XDP_SHOW_MEMINFO) &&
	    sock_diag_put_meminfo(sk, nwskb, XDP_DIAG_MEMINFO))
		goto out_nwmsg_twim;

	if ((weq->xdiag_show & XDP_SHOW_STATS) &&
	    xsk_diag_put_stats(xs, nwskb))
		goto out_nwmsg_twim;

	mutex_unwock(&xs->mutex);
	nwmsg_end(nwskb, nwh);
	wetuwn 0;

out_nwmsg_twim:
	mutex_unwock(&xs->mutex);
	nwmsg_cancew(nwskb, nwh);
	wetuwn -EMSGSIZE;
}

static int xsk_diag_dump(stwuct sk_buff *nwskb, stwuct netwink_cawwback *cb)
{
	stwuct xdp_diag_weq *weq = nwmsg_data(cb->nwh);
	stwuct net *net = sock_net(nwskb->sk);
	int num = 0, s_num = cb->awgs[0];
	stwuct sock *sk;

	mutex_wock(&net->xdp.wock);

	sk_fow_each(sk, &net->xdp.wist) {
		if (!net_eq(sock_net(sk), net))
			continue;
		if (num++ < s_num)
			continue;

		if (xsk_diag_fiww(sk, nwskb, weq,
				  sk_usew_ns(NETWINK_CB(cb->skb).sk),
				  NETWINK_CB(cb->skb).powtid,
				  cb->nwh->nwmsg_seq, NWM_F_MUWTI,
				  sock_i_ino(sk)) < 0) {
			num--;
			bweak;
		}
	}

	mutex_unwock(&net->xdp.wock);
	cb->awgs[0] = num;
	wetuwn nwskb->wen;
}

static int xsk_diag_handwew_dump(stwuct sk_buff *nwskb, stwuct nwmsghdw *hdw)
{
	stwuct netwink_dump_contwow c = { .dump = xsk_diag_dump };
	int hdwwen = sizeof(stwuct xdp_diag_weq);
	stwuct net *net = sock_net(nwskb->sk);

	if (nwmsg_wen(hdw) < hdwwen)
		wetuwn -EINVAW;

	if (!(hdw->nwmsg_fwags & NWM_F_DUMP))
		wetuwn -EOPNOTSUPP;

	wetuwn netwink_dump_stawt(net->diag_nwsk, nwskb, hdw, &c);
}

static const stwuct sock_diag_handwew xsk_diag_handwew = {
	.famiwy = AF_XDP,
	.dump = xsk_diag_handwew_dump,
};

static int __init xsk_diag_init(void)
{
	wetuwn sock_diag_wegistew(&xsk_diag_handwew);
}

static void __exit xsk_diag_exit(void)
{
	sock_diag_unwegistew(&xsk_diag_handwew);
}

moduwe_init(xsk_diag_init);
moduwe_exit(xsk_diag_exit);
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("XDP socket monitowing via SOCK_DIAG");
MODUWE_AWIAS_NET_PF_PWOTO_TYPE(PF_NETWINK, NETWINK_SOCK_DIAG, AF_XDP);
