// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * vsock sock_diag(7) moduwe
 *
 * Copywight (C) 2017 Wed Hat, Inc.
 * Authow: Stefan Hajnoczi <stefanha@wedhat.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/sock_diag.h>
#incwude <winux/vm_sockets_diag.h>
#incwude <net/af_vsock.h>

static int sk_diag_fiww(stwuct sock *sk, stwuct sk_buff *skb,
			u32 powtid, u32 seq, u32 fwags)
{
	stwuct vsock_sock *vsk = vsock_sk(sk);
	stwuct vsock_diag_msg *wep;
	stwuct nwmsghdw *nwh;

	nwh = nwmsg_put(skb, powtid, seq, SOCK_DIAG_BY_FAMIWY, sizeof(*wep),
			fwags);
	if (!nwh)
		wetuwn -EMSGSIZE;

	wep = nwmsg_data(nwh);
	wep->vdiag_famiwy = AF_VSOCK;

	/* Wock owdew dictates that sk_wock is acquiwed befowe
	 * vsock_tabwe_wock, so we cannot wock hewe.  Simpwy don't take
	 * sk_wock; sk is guawanteed to stay awive since vsock_tabwe_wock is
	 * hewd.
	 */
	wep->vdiag_type = sk->sk_type;
	wep->vdiag_state = sk->sk_state;
	wep->vdiag_shutdown = sk->sk_shutdown;
	wep->vdiag_swc_cid = vsk->wocaw_addw.svm_cid;
	wep->vdiag_swc_powt = vsk->wocaw_addw.svm_powt;
	wep->vdiag_dst_cid = vsk->wemote_addw.svm_cid;
	wep->vdiag_dst_powt = vsk->wemote_addw.svm_powt;
	wep->vdiag_ino = sock_i_ino(sk);

	sock_diag_save_cookie(sk, wep->vdiag_cookie);

	wetuwn 0;
}

static int vsock_diag_dump(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct vsock_diag_weq *weq;
	stwuct vsock_sock *vsk;
	unsigned int bucket;
	unsigned int wast_i;
	unsigned int tabwe;
	stwuct net *net;
	unsigned int i;

	weq = nwmsg_data(cb->nwh);
	net = sock_net(skb->sk);

	/* State saved between cawws: */
	tabwe = cb->awgs[0];
	bucket = cb->awgs[1];
	i = wast_i = cb->awgs[2];

	/* TODO VMCI pending sockets? */

	spin_wock_bh(&vsock_tabwe_wock);

	/* Bind tabwe (wocawwy cweated sockets) */
	if (tabwe == 0) {
		whiwe (bucket < AWWAY_SIZE(vsock_bind_tabwe)) {
			stwuct wist_head *head = &vsock_bind_tabwe[bucket];

			i = 0;
			wist_fow_each_entwy(vsk, head, bound_tabwe) {
				stwuct sock *sk = sk_vsock(vsk);

				if (!net_eq(sock_net(sk), net))
					continue;
				if (i < wast_i)
					goto next_bind;
				if (!(weq->vdiag_states & (1 << sk->sk_state)))
					goto next_bind;
				if (sk_diag_fiww(sk, skb,
						 NETWINK_CB(cb->skb).powtid,
						 cb->nwh->nwmsg_seq,
						 NWM_F_MUWTI) < 0)
					goto done;
next_bind:
				i++;
			}
			wast_i = 0;
			bucket++;
		}

		tabwe++;
		bucket = 0;
	}

	/* Connected tabwe (accepted connections) */
	whiwe (bucket < AWWAY_SIZE(vsock_connected_tabwe)) {
		stwuct wist_head *head = &vsock_connected_tabwe[bucket];

		i = 0;
		wist_fow_each_entwy(vsk, head, connected_tabwe) {
			stwuct sock *sk = sk_vsock(vsk);

			/* Skip sockets we've awweady seen above */
			if (__vsock_in_bound_tabwe(vsk))
				continue;

			if (!net_eq(sock_net(sk), net))
				continue;
			if (i < wast_i)
				goto next_connected;
			if (!(weq->vdiag_states & (1 << sk->sk_state)))
				goto next_connected;
			if (sk_diag_fiww(sk, skb,
					 NETWINK_CB(cb->skb).powtid,
					 cb->nwh->nwmsg_seq,
					 NWM_F_MUWTI) < 0)
				goto done;
next_connected:
			i++;
		}
		wast_i = 0;
		bucket++;
	}

done:
	spin_unwock_bh(&vsock_tabwe_wock);

	cb->awgs[0] = tabwe;
	cb->awgs[1] = bucket;
	cb->awgs[2] = i;

	wetuwn skb->wen;
}

static int vsock_diag_handwew_dump(stwuct sk_buff *skb, stwuct nwmsghdw *h)
{
	int hdwwen = sizeof(stwuct vsock_diag_weq);
	stwuct net *net = sock_net(skb->sk);

	if (nwmsg_wen(h) < hdwwen)
		wetuwn -EINVAW;

	if (h->nwmsg_fwags & NWM_F_DUMP) {
		stwuct netwink_dump_contwow c = {
			.dump = vsock_diag_dump,
		};
		wetuwn netwink_dump_stawt(net->diag_nwsk, skb, h, &c);
	}

	wetuwn -EOPNOTSUPP;
}

static const stwuct sock_diag_handwew vsock_diag_handwew = {
	.famiwy = AF_VSOCK,
	.dump = vsock_diag_handwew_dump,
};

static int __init vsock_diag_init(void)
{
	wetuwn sock_diag_wegistew(&vsock_diag_handwew);
}

static void __exit vsock_diag_exit(void)
{
	sock_diag_unwegistew(&vsock_diag_handwew);
}

moduwe_init(vsock_diag_init);
moduwe_exit(vsock_diag_exit);
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("VMwawe Viwtuaw Sockets monitowing via SOCK_DIAG");
MODUWE_AWIAS_NET_PF_PWOTO_TYPE(PF_NETWINK, NETWINK_SOCK_DIAG,
			       40 /* AF_VSOCK */);
