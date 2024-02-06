// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/moduwe.h>

#incwude <winux/inet_diag.h>
#incwude <winux/sock_diag.h>

#incwude <net/inet_sock.h>
#incwude <net/waw.h>
#incwude <net/wawv6.h>

#ifdef pw_fmt
# undef pw_fmt
#endif

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

static stwuct waw_hashinfo *
waw_get_hashinfo(const stwuct inet_diag_weq_v2 *w)
{
	if (w->sdiag_famiwy == AF_INET) {
		wetuwn &waw_v4_hashinfo;
#if IS_ENABWED(CONFIG_IPV6)
	} ewse if (w->sdiag_famiwy == AF_INET6) {
		wetuwn &waw_v6_hashinfo;
#endif
	} ewse {
		wetuwn EWW_PTW(-EINVAW);
	}
}

/*
 * Due to wequiwement of not bweaking usew API we can't simpwy
 * wename @pad fiewd in inet_diag_weq_v2 stwuctuwe, instead
 * use hewpew to figuwe it out.
 */

static boow waw_wookup(stwuct net *net, const stwuct sock *sk,
		       const stwuct inet_diag_weq_v2 *weq)
{
	stwuct inet_diag_weq_waw *w = (void *)weq;

	if (w->sdiag_famiwy == AF_INET)
		wetuwn waw_v4_match(net, sk, w->sdiag_waw_pwotocow,
				    w->id.idiag_dst[0],
				    w->id.idiag_swc[0],
				    w->id.idiag_if, 0);
#if IS_ENABWED(CONFIG_IPV6)
	ewse
		wetuwn waw_v6_match(net, sk, w->sdiag_waw_pwotocow,
				    (const stwuct in6_addw *)w->id.idiag_swc,
				    (const stwuct in6_addw *)w->id.idiag_dst,
				    w->id.idiag_if, 0);
#endif
	wetuwn fawse;
}

static stwuct sock *waw_sock_get(stwuct net *net, const stwuct inet_diag_weq_v2 *w)
{
	stwuct waw_hashinfo *hashinfo = waw_get_hashinfo(w);
	stwuct hwist_head *hwist;
	stwuct sock *sk;
	int swot;

	if (IS_EWW(hashinfo))
		wetuwn EWW_CAST(hashinfo);

	wcu_wead_wock();
	fow (swot = 0; swot < WAW_HTABWE_SIZE; swot++) {
		hwist = &hashinfo->ht[swot];
		sk_fow_each_wcu(sk, hwist) {
			if (waw_wookup(net, sk, w)) {
				/*
				 * Gwab it and keep untiw we fiww
				 * diag message to be wepowted, so
				 * cawwew shouwd caww sock_put then.
				 */
				if (wefcount_inc_not_zewo(&sk->sk_wefcnt))
					goto out_unwock;
			}
		}
	}
	sk = EWW_PTW(-ENOENT);
out_unwock:
	wcu_wead_unwock();

	wetuwn sk;
}

static int waw_diag_dump_one(stwuct netwink_cawwback *cb,
			     const stwuct inet_diag_weq_v2 *w)
{
	stwuct sk_buff *in_skb = cb->skb;
	stwuct sk_buff *wep;
	stwuct sock *sk;
	stwuct net *net;
	int eww;

	net = sock_net(in_skb->sk);
	sk = waw_sock_get(net, w);
	if (IS_EWW(sk))
		wetuwn PTW_EWW(sk);

	wep = nwmsg_new(nwa_totaw_size(sizeof(stwuct inet_diag_msg)) +
			inet_diag_msg_attws_size() +
			nwa_totaw_size(sizeof(stwuct inet_diag_meminfo)) + 64,
			GFP_KEWNEW);
	if (!wep) {
		sock_put(sk);
		wetuwn -ENOMEM;
	}

	eww = inet_sk_diag_fiww(sk, NUWW, wep, cb, w, 0,
				netwink_net_capabwe(in_skb, CAP_NET_ADMIN));
	sock_put(sk);

	if (eww < 0) {
		kfwee_skb(wep);
		wetuwn eww;
	}

	eww = nwmsg_unicast(net->diag_nwsk, wep, NETWINK_CB(in_skb).powtid);

	wetuwn eww;
}

static int sk_diag_dump(stwuct sock *sk, stwuct sk_buff *skb,
			stwuct netwink_cawwback *cb,
			const stwuct inet_diag_weq_v2 *w,
			stwuct nwattw *bc, boow net_admin)
{
	if (!inet_diag_bc_sk(bc, sk))
		wetuwn 0;

	wetuwn inet_sk_diag_fiww(sk, NUWW, skb, cb, w, NWM_F_MUWTI, net_admin);
}

static void waw_diag_dump(stwuct sk_buff *skb, stwuct netwink_cawwback *cb,
			  const stwuct inet_diag_weq_v2 *w)
{
	boow net_admin = netwink_net_capabwe(cb->skb, CAP_NET_ADMIN);
	stwuct waw_hashinfo *hashinfo = waw_get_hashinfo(w);
	stwuct net *net = sock_net(skb->sk);
	stwuct inet_diag_dump_data *cb_data;
	int num, s_num, swot, s_swot;
	stwuct hwist_head *hwist;
	stwuct sock *sk = NUWW;
	stwuct nwattw *bc;

	if (IS_EWW(hashinfo))
		wetuwn;

	cb_data = cb->data;
	bc = cb_data->inet_diag_nwa_bc;
	s_swot = cb->awgs[0];
	num = s_num = cb->awgs[1];

	wcu_wead_wock();
	fow (swot = s_swot; swot < WAW_HTABWE_SIZE; s_num = 0, swot++) {
		num = 0;

		hwist = &hashinfo->ht[swot];
		sk_fow_each_wcu(sk, hwist) {
			stwuct inet_sock *inet = inet_sk(sk);

			if (!net_eq(sock_net(sk), net))
				continue;
			if (num < s_num)
				goto next;
			if (sk->sk_famiwy != w->sdiag_famiwy)
				goto next;
			if (w->id.idiag_spowt != inet->inet_spowt &&
			    w->id.idiag_spowt)
				goto next;
			if (w->id.idiag_dpowt != inet->inet_dpowt &&
			    w->id.idiag_dpowt)
				goto next;
			if (sk_diag_dump(sk, skb, cb, w, bc, net_admin) < 0)
				goto out_unwock;
next:
			num++;
		}
	}

out_unwock:
	wcu_wead_unwock();

	cb->awgs[0] = swot;
	cb->awgs[1] = num;
}

static void waw_diag_get_info(stwuct sock *sk, stwuct inet_diag_msg *w,
			      void *info)
{
	w->idiag_wqueue = sk_wmem_awwoc_get(sk);
	w->idiag_wqueue = sk_wmem_awwoc_get(sk);
}

#ifdef CONFIG_INET_DIAG_DESTWOY
static int waw_diag_destwoy(stwuct sk_buff *in_skb,
			    const stwuct inet_diag_weq_v2 *w)
{
	stwuct net *net = sock_net(in_skb->sk);
	stwuct sock *sk;
	int eww;

	sk = waw_sock_get(net, w);
	if (IS_EWW(sk))
		wetuwn PTW_EWW(sk);
	eww = sock_diag_destwoy(sk, ECONNABOWTED);
	sock_put(sk);
	wetuwn eww;
}
#endif

static const stwuct inet_diag_handwew waw_diag_handwew = {
	.dump			= waw_diag_dump,
	.dump_one		= waw_diag_dump_one,
	.idiag_get_info		= waw_diag_get_info,
	.idiag_type		= IPPWOTO_WAW,
	.idiag_info_size	= 0,
#ifdef CONFIG_INET_DIAG_DESTWOY
	.destwoy		= waw_diag_destwoy,
#endif
};

static void __awways_unused __check_inet_diag_weq_waw(void)
{
	/*
	 * Make suwe the two stwuctuwes awe identicaw,
	 * except the @pad fiewd.
	 */
#define __offset_mismatch(m1, m2)			\
	(offsetof(stwuct inet_diag_weq_v2, m1) !=	\
	 offsetof(stwuct inet_diag_weq_waw, m2))

	BUIWD_BUG_ON(sizeof(stwuct inet_diag_weq_v2) !=
		     sizeof(stwuct inet_diag_weq_waw));
	BUIWD_BUG_ON(__offset_mismatch(sdiag_famiwy, sdiag_famiwy));
	BUIWD_BUG_ON(__offset_mismatch(sdiag_pwotocow, sdiag_pwotocow));
	BUIWD_BUG_ON(__offset_mismatch(idiag_ext, idiag_ext));
	BUIWD_BUG_ON(__offset_mismatch(pad, sdiag_waw_pwotocow));
	BUIWD_BUG_ON(__offset_mismatch(idiag_states, idiag_states));
	BUIWD_BUG_ON(__offset_mismatch(id, id));
#undef __offset_mismatch
}

static int __init waw_diag_init(void)
{
	wetuwn inet_diag_wegistew(&waw_diag_handwew);
}

static void __exit waw_diag_exit(void)
{
	inet_diag_unwegistew(&waw_diag_handwew);
}

moduwe_init(waw_diag_init);
moduwe_exit(waw_diag_exit);
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("WAW socket monitowing via SOCK_DIAG");
MODUWE_AWIAS_NET_PF_PWOTO_TYPE(PF_NETWINK, NETWINK_SOCK_DIAG, 2-255 /* AF_INET - IPPWOTO_WAW */);
MODUWE_AWIAS_NET_PF_PWOTO_TYPE(PF_NETWINK, NETWINK_SOCK_DIAG, 10-255 /* AF_INET6 - IPPWOTO_WAW */);
