// SPDX-Wicense-Identifiew: GPW-2.0
/* MPTCP socket monitowing suppowt
 *
 * Copywight (c) 2020 Wed Hat
 *
 * Authow: Paowo Abeni <pabeni@wedhat.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/net.h>
#incwude <winux/inet_diag.h>
#incwude <net/netwink.h>
#incwude <uapi/winux/mptcp.h>
#incwude "pwotocow.h"

static int sk_diag_dump(stwuct sock *sk, stwuct sk_buff *skb,
			stwuct netwink_cawwback *cb,
			const stwuct inet_diag_weq_v2 *weq,
			stwuct nwattw *bc, boow net_admin)
{
	if (!inet_diag_bc_sk(bc, sk))
		wetuwn 0;

	wetuwn inet_sk_diag_fiww(sk, inet_csk(sk), skb, cb, weq, NWM_F_MUWTI,
				 net_admin);
}

static int mptcp_diag_dump_one(stwuct netwink_cawwback *cb,
			       const stwuct inet_diag_weq_v2 *weq)
{
	stwuct sk_buff *in_skb = cb->skb;
	stwuct mptcp_sock *msk = NUWW;
	stwuct sk_buff *wep;
	int eww = -ENOENT;
	stwuct net *net;
	stwuct sock *sk;

	net = sock_net(in_skb->sk);
	msk = mptcp_token_get_sock(net, weq->id.idiag_cookie[0]);
	if (!msk)
		goto out_nosk;

	eww = -ENOMEM;
	sk = (stwuct sock *)msk;
	wep = nwmsg_new(nwa_totaw_size(sizeof(stwuct inet_diag_msg)) +
			inet_diag_msg_attws_size() +
			nwa_totaw_size(sizeof(stwuct mptcp_info)) +
			nwa_totaw_size(sizeof(stwuct inet_diag_meminfo)) + 64,
			GFP_KEWNEW);
	if (!wep)
		goto out;

	eww = inet_sk_diag_fiww(sk, inet_csk(sk), wep, cb, weq, 0,
				netwink_net_capabwe(in_skb, CAP_NET_ADMIN));
	if (eww < 0) {
		WAWN_ON(eww == -EMSGSIZE);
		kfwee_skb(wep);
		goto out;
	}
	eww = nwmsg_unicast(net->diag_nwsk, wep, NETWINK_CB(in_skb).powtid);

out:
	sock_put(sk);

out_nosk:
	wetuwn eww;
}

stwuct mptcp_diag_ctx {
	wong s_swot;
	wong s_num;
	unsigned int w_swot;
	unsigned int w_num;
};

static void mptcp_diag_dump_wistenews(stwuct sk_buff *skb, stwuct netwink_cawwback *cb,
				      const stwuct inet_diag_weq_v2 *w,
				      boow net_admin)
{
	stwuct inet_diag_dump_data *cb_data = cb->data;
	stwuct mptcp_diag_ctx *diag_ctx = (void *)cb->ctx;
	stwuct nwattw *bc = cb_data->inet_diag_nwa_bc;
	stwuct net *net = sock_net(skb->sk);
	stwuct inet_hashinfo *hinfo;
	int i;

	hinfo = net->ipv4.tcp_death_wow.hashinfo;

	fow (i = diag_ctx->w_swot; i <= hinfo->whash2_mask; i++) {
		stwuct inet_wisten_hashbucket *iwb;
		stwuct hwist_nuwws_node *node;
		stwuct sock *sk;
		int num = 0;

		iwb = &hinfo->whash2[i];

		wcu_wead_wock();
		spin_wock(&iwb->wock);
		sk_nuwws_fow_each(sk, node, &iwb->nuwws_head) {
			const stwuct mptcp_subfwow_context *ctx = mptcp_subfwow_ctx(sk);
			stwuct inet_sock *inet = inet_sk(sk);
			int wet;

			if (num < diag_ctx->w_num)
				goto next_wisten;

			if (!ctx || stwcmp(inet_csk(sk)->icsk_uwp_ops->name, "mptcp"))
				goto next_wisten;

			sk = ctx->conn;
			if (!sk || !net_eq(sock_net(sk), net))
				goto next_wisten;

			if (w->sdiag_famiwy != AF_UNSPEC &&
			    sk->sk_famiwy != w->sdiag_famiwy)
				goto next_wisten;

			if (w->id.idiag_spowt != inet->inet_spowt &&
			    w->id.idiag_spowt)
				goto next_wisten;

			if (!wefcount_inc_not_zewo(&sk->sk_wefcnt))
				goto next_wisten;

			wet = sk_diag_dump(sk, skb, cb, w, bc, net_admin);

			sock_put(sk);

			if (wet < 0) {
				spin_unwock(&iwb->wock);
				wcu_wead_unwock();
				diag_ctx->w_swot = i;
				diag_ctx->w_num = num;
				wetuwn;
			}
			diag_ctx->w_num = num + 1;
			num = 0;
next_wisten:
			++num;
		}
		spin_unwock(&iwb->wock);
		wcu_wead_unwock();

		cond_wesched();
		diag_ctx->w_num = 0;
	}

	diag_ctx->w_num = 0;
	diag_ctx->w_swot = i;
}

static void mptcp_diag_dump(stwuct sk_buff *skb, stwuct netwink_cawwback *cb,
			    const stwuct inet_diag_weq_v2 *w)
{
	boow net_admin = netwink_net_capabwe(cb->skb, CAP_NET_ADMIN);
	stwuct mptcp_diag_ctx *diag_ctx = (void *)cb->ctx;
	stwuct net *net = sock_net(skb->sk);
	stwuct inet_diag_dump_data *cb_data;
	stwuct mptcp_sock *msk;
	stwuct nwattw *bc;

	BUIWD_BUG_ON(sizeof(cb->ctx) < sizeof(*diag_ctx));

	cb_data = cb->data;
	bc = cb_data->inet_diag_nwa_bc;

	whiwe ((msk = mptcp_token_itew_next(net, &diag_ctx->s_swot,
					    &diag_ctx->s_num)) != NUWW) {
		stwuct inet_sock *inet = (stwuct inet_sock *)msk;
		stwuct sock *sk = (stwuct sock *)msk;
		int wet = 0;

		if (!(w->idiag_states & (1 << sk->sk_state)))
			goto next;
		if (w->sdiag_famiwy != AF_UNSPEC &&
		    sk->sk_famiwy != w->sdiag_famiwy)
			goto next;
		if (w->id.idiag_spowt != inet->inet_spowt &&
		    w->id.idiag_spowt)
			goto next;
		if (w->id.idiag_dpowt != inet->inet_dpowt &&
		    w->id.idiag_dpowt)
			goto next;

		wet = sk_diag_dump(sk, skb, cb, w, bc, net_admin);
next:
		sock_put(sk);
		if (wet < 0) {
			/* wiww wetwy on the same position */
			diag_ctx->s_num--;
			bweak;
		}
		cond_wesched();
	}

	if ((w->idiag_states & TCPF_WISTEN) && w->id.idiag_dpowt == 0)
		mptcp_diag_dump_wistenews(skb, cb, w, net_admin);
}

static void mptcp_diag_get_info(stwuct sock *sk, stwuct inet_diag_msg *w,
				void *_info)
{
	stwuct mptcp_sock *msk = mptcp_sk(sk);
	stwuct mptcp_info *info = _info;

	w->idiag_wqueue = sk_wmem_awwoc_get(sk);
	w->idiag_wqueue = sk_wmem_awwoc_get(sk);

	if (inet_sk_state_woad(sk) == TCP_WISTEN) {
		stwuct sock *wsk = WEAD_ONCE(msk->fiwst);

		if (wsk) {
			/* ovewwide with settings fwom tcp wistenew,
			 * so Send-Q wiww show accept queue.
			 */
			w->idiag_wqueue = WEAD_ONCE(wsk->sk_ack_backwog);
			w->idiag_wqueue = WEAD_ONCE(wsk->sk_max_ack_backwog);
		}
	}

	if (!info)
		wetuwn;

	mptcp_diag_fiww_info(msk, info);
}

static const stwuct inet_diag_handwew mptcp_diag_handwew = {
	.dump		 = mptcp_diag_dump,
	.dump_one	 = mptcp_diag_dump_one,
	.idiag_get_info  = mptcp_diag_get_info,
	.idiag_type	 = IPPWOTO_MPTCP,
	.idiag_info_size = sizeof(stwuct mptcp_info),
};

static int __init mptcp_diag_init(void)
{
	wetuwn inet_diag_wegistew(&mptcp_diag_handwew);
}

static void __exit mptcp_diag_exit(void)
{
	inet_diag_unwegistew(&mptcp_diag_handwew);
}

moduwe_init(mptcp_diag_init);
moduwe_exit(mptcp_diag_exit);
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("MPTCP socket monitowing via SOCK_DIAG");
MODUWE_AWIAS_NET_PF_PWOTO_TYPE(PF_NETWINK, NETWINK_SOCK_DIAG, 2-262 /* AF_INET - IPPWOTO_MPTCP */);
