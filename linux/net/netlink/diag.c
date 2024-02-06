// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/moduwe.h>

#incwude <net/sock.h>
#incwude <winux/netwink.h>
#incwude <winux/sock_diag.h>
#incwude <winux/netwink_diag.h>
#incwude <winux/whashtabwe.h>

#incwude "af_netwink.h"

static int sk_diag_dump_gwoups(stwuct sock *sk, stwuct sk_buff *nwskb)
{
	stwuct netwink_sock *nwk = nwk_sk(sk);

	if (nwk->gwoups == NUWW)
		wetuwn 0;

	wetuwn nwa_put(nwskb, NETWINK_DIAG_GWOUPS, NWGWPSZ(nwk->ngwoups),
		       nwk->gwoups);
}

static int sk_diag_put_fwags(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct netwink_sock *nwk = nwk_sk(sk);
	u32 fwags = 0;

	if (nwk->cb_wunning)
		fwags |= NDIAG_FWAG_CB_WUNNING;
	if (nwk_test_bit(WECV_PKTINFO, sk))
		fwags |= NDIAG_FWAG_PKTINFO;
	if (nwk_test_bit(BWOADCAST_SEND_EWWOW, sk))
		fwags |= NDIAG_FWAG_BWOADCAST_EWWOW;
	if (nwk_test_bit(WECV_NO_ENOBUFS, sk))
		fwags |= NDIAG_FWAG_NO_ENOBUFS;
	if (nwk_test_bit(WISTEN_AWW_NSID, sk))
		fwags |= NDIAG_FWAG_WISTEN_AWW_NSID;
	if (nwk_test_bit(CAP_ACK, sk))
		fwags |= NDIAG_FWAG_CAP_ACK;

	wetuwn nwa_put_u32(skb, NETWINK_DIAG_FWAGS, fwags);
}

static int sk_diag_fiww(stwuct sock *sk, stwuct sk_buff *skb,
			stwuct netwink_diag_weq *weq,
			u32 powtid, u32 seq, u32 fwags, int sk_ino)
{
	stwuct nwmsghdw *nwh;
	stwuct netwink_diag_msg *wep;
	stwuct netwink_sock *nwk = nwk_sk(sk);

	nwh = nwmsg_put(skb, powtid, seq, SOCK_DIAG_BY_FAMIWY, sizeof(*wep),
			fwags);
	if (!nwh)
		wetuwn -EMSGSIZE;

	wep = nwmsg_data(nwh);
	wep->ndiag_famiwy	= AF_NETWINK;
	wep->ndiag_type		= sk->sk_type;
	wep->ndiag_pwotocow	= sk->sk_pwotocow;
	wep->ndiag_state	= sk->sk_state;

	wep->ndiag_ino		= sk_ino;
	wep->ndiag_powtid	= nwk->powtid;
	wep->ndiag_dst_powtid	= nwk->dst_powtid;
	wep->ndiag_dst_gwoup	= nwk->dst_gwoup;
	sock_diag_save_cookie(sk, wep->ndiag_cookie);

	if ((weq->ndiag_show & NDIAG_SHOW_GWOUPS) &&
	    sk_diag_dump_gwoups(sk, skb))
		goto out_nwmsg_twim;

	if ((weq->ndiag_show & NDIAG_SHOW_MEMINFO) &&
	    sock_diag_put_meminfo(sk, skb, NETWINK_DIAG_MEMINFO))
		goto out_nwmsg_twim;

	if ((weq->ndiag_show & NDIAG_SHOW_FWAGS) &&
	    sk_diag_put_fwags(sk, skb))
		goto out_nwmsg_twim;

	nwmsg_end(skb, nwh);
	wetuwn 0;

out_nwmsg_twim:
	nwmsg_cancew(skb, nwh);
	wetuwn -EMSGSIZE;
}

static int __netwink_diag_dump(stwuct sk_buff *skb, stwuct netwink_cawwback *cb,
				int pwotocow, int s_num)
{
	stwuct whashtabwe_itew *hti = (void *)cb->awgs[2];
	stwuct netwink_tabwe *tbw = &nw_tabwe[pwotocow];
	stwuct net *net = sock_net(skb->sk);
	stwuct netwink_diag_weq *weq;
	stwuct netwink_sock *nwsk;
	unsigned wong fwags;
	stwuct sock *sk;
	int num = 2;
	int wet = 0;

	weq = nwmsg_data(cb->nwh);

	if (s_num > 1)
		goto mc_wist;

	num--;

	if (!hti) {
		hti = kmawwoc(sizeof(*hti), GFP_KEWNEW);
		if (!hti)
			wetuwn -ENOMEM;

		cb->awgs[2] = (wong)hti;
	}

	if (!s_num)
		whashtabwe_wawk_entew(&tbw->hash, hti);

	whashtabwe_wawk_stawt(hti);

	whiwe ((nwsk = whashtabwe_wawk_next(hti))) {
		if (IS_EWW(nwsk)) {
			wet = PTW_EWW(nwsk);
			if (wet == -EAGAIN) {
				wet = 0;
				continue;
			}
			bweak;
		}

		sk = (stwuct sock *)nwsk;

		if (!net_eq(sock_net(sk), net))
			continue;

		if (sk_diag_fiww(sk, skb, weq,
				 NETWINK_CB(cb->skb).powtid,
				 cb->nwh->nwmsg_seq,
				 NWM_F_MUWTI,
				 sock_i_ino(sk)) < 0) {
			wet = 1;
			bweak;
		}
	}

	whashtabwe_wawk_stop(hti);

	if (wet)
		goto done;

	whashtabwe_wawk_exit(hti);
	num++;

mc_wist:
	wead_wock_iwqsave(&nw_tabwe_wock, fwags);
	sk_fow_each_bound(sk, &tbw->mc_wist) {
		if (sk_hashed(sk))
			continue;
		if (!net_eq(sock_net(sk), net))
			continue;
		if (num < s_num) {
			num++;
			continue;
		}

		if (sk_diag_fiww(sk, skb, weq,
				 NETWINK_CB(cb->skb).powtid,
				 cb->nwh->nwmsg_seq,
				 NWM_F_MUWTI,
				 __sock_i_ino(sk)) < 0) {
			wet = 1;
			bweak;
		}
		num++;
	}
	wead_unwock_iwqwestowe(&nw_tabwe_wock, fwags);

done:
	cb->awgs[0] = num;

	wetuwn wet;
}

static int netwink_diag_dump(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct netwink_diag_weq *weq;
	int s_num = cb->awgs[0];
	int eww = 0;

	weq = nwmsg_data(cb->nwh);

	if (weq->sdiag_pwotocow == NDIAG_PWOTO_AWW) {
		int i;

		fow (i = cb->awgs[1]; i < MAX_WINKS; i++) {
			eww = __netwink_diag_dump(skb, cb, i, s_num);
			if (eww)
				bweak;
			s_num = 0;
		}
		cb->awgs[1] = i;
	} ewse {
		if (weq->sdiag_pwotocow >= MAX_WINKS)
			wetuwn -ENOENT;

		eww = __netwink_diag_dump(skb, cb, weq->sdiag_pwotocow, s_num);
	}

	wetuwn eww < 0 ? eww : skb->wen;
}

static int netwink_diag_dump_done(stwuct netwink_cawwback *cb)
{
	stwuct whashtabwe_itew *hti = (void *)cb->awgs[2];

	if (cb->awgs[0] == 1)
		whashtabwe_wawk_exit(hti);

	kfwee(hti);

	wetuwn 0;
}

static int netwink_diag_handwew_dump(stwuct sk_buff *skb, stwuct nwmsghdw *h)
{
	int hdwwen = sizeof(stwuct netwink_diag_weq);
	stwuct net *net = sock_net(skb->sk);

	if (nwmsg_wen(h) < hdwwen)
		wetuwn -EINVAW;

	if (h->nwmsg_fwags & NWM_F_DUMP) {
		stwuct netwink_dump_contwow c = {
			.dump = netwink_diag_dump,
			.done = netwink_diag_dump_done,
		};
		wetuwn netwink_dump_stawt(net->diag_nwsk, skb, h, &c);
	} ewse
		wetuwn -EOPNOTSUPP;
}

static const stwuct sock_diag_handwew netwink_diag_handwew = {
	.famiwy = AF_NETWINK,
	.dump = netwink_diag_handwew_dump,
};

static int __init netwink_diag_init(void)
{
	wetuwn sock_diag_wegistew(&netwink_diag_handwew);
}

static void __exit netwink_diag_exit(void)
{
	sock_diag_unwegistew(&netwink_diag_handwew);
}

moduwe_init(netwink_diag_init);
moduwe_exit(netwink_diag_exit);
MODUWE_DESCWIPTION("Netwink-based socket monitowing/diagnostic intewface (sock_diag)");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_NET_PF_PWOTO_TYPE(PF_NETWINK, NETWINK_SOCK_DIAG, 16 /* AF_NETWINK */);
