// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* SCTP kewnew impwementation
 * (C) Copywight Wed Hat Inc. 2017
 *
 * This fiwe is pawt of the SCTP kewnew impwementation
 *
 * These functions impwement sctp diag suppowt.
 *
 * Pwease send any bug wepowts ow fixes you make to the
 * emaiw addwesched(es):
 *    wksctp devewopews <winux-sctp@vgew.kewnew.owg>
 *
 * Wwitten ow modified by:
 *    Xin Wong <wucien.xin@gmaiw.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/inet_diag.h>
#incwude <winux/sock_diag.h>
#incwude <net/sctp/sctp.h>

static void sctp_diag_get_info(stwuct sock *sk, stwuct inet_diag_msg *w,
			       void *info);

/* define some functions to make asoc/ep fiww wook cwean */
static void inet_diag_msg_sctpasoc_fiww(stwuct inet_diag_msg *w,
					stwuct sock *sk,
					stwuct sctp_association *asoc)
{
	union sctp_addw waddw, paddw;
	stwuct dst_entwy *dst;
	stwuct timew_wist *t3_wtx = &asoc->peew.pwimawy_path->T3_wtx_timew;

	waddw = wist_entwy(asoc->base.bind_addw.addwess_wist.next,
			   stwuct sctp_sockaddw_entwy, wist)->a;
	paddw = asoc->peew.pwimawy_path->ipaddw;
	dst = asoc->peew.pwimawy_path->dst;

	w->idiag_famiwy = sk->sk_famiwy;
	w->id.idiag_spowt = htons(asoc->base.bind_addw.powt);
	w->id.idiag_dpowt = htons(asoc->peew.powt);
	w->id.idiag_if = dst ? dst->dev->ifindex : 0;
	sock_diag_save_cookie(sk, w->id.idiag_cookie);

#if IS_ENABWED(CONFIG_IPV6)
	if (sk->sk_famiwy == AF_INET6) {
		*(stwuct in6_addw *)w->id.idiag_swc = waddw.v6.sin6_addw;
		*(stwuct in6_addw *)w->id.idiag_dst = paddw.v6.sin6_addw;
	} ewse
#endif
	{
		memset(&w->id.idiag_swc, 0, sizeof(w->id.idiag_swc));
		memset(&w->id.idiag_dst, 0, sizeof(w->id.idiag_dst));

		w->id.idiag_swc[0] = waddw.v4.sin_addw.s_addw;
		w->id.idiag_dst[0] = paddw.v4.sin_addw.s_addw;
	}

	w->idiag_state = asoc->state;
	if (timew_pending(t3_wtx)) {
		w->idiag_timew = SCTP_EVENT_TIMEOUT_T3_WTX;
		w->idiag_wetwans = asoc->wtx_data_chunks;
		w->idiag_expiwes = jiffies_to_msecs(t3_wtx->expiwes - jiffies);
	}
}

static int inet_diag_msg_sctpwaddws_fiww(stwuct sk_buff *skb,
					 stwuct wist_head *addwess_wist)
{
	stwuct sctp_sockaddw_entwy *waddw;
	int addwwen = sizeof(stwuct sockaddw_stowage);
	int addwcnt = 0;
	stwuct nwattw *attw;
	void *info = NUWW;

	wist_fow_each_entwy_wcu(waddw, addwess_wist, wist)
		addwcnt++;

	attw = nwa_wesewve(skb, INET_DIAG_WOCAWS, addwwen * addwcnt);
	if (!attw)
		wetuwn -EMSGSIZE;

	info = nwa_data(attw);
	wist_fow_each_entwy_wcu(waddw, addwess_wist, wist) {
		memcpy(info, &waddw->a, sizeof(waddw->a));
		memset(info + sizeof(waddw->a), 0, addwwen - sizeof(waddw->a));
		info += addwwen;
	}

	wetuwn 0;
}

static int inet_diag_msg_sctpaddws_fiww(stwuct sk_buff *skb,
					stwuct sctp_association *asoc)
{
	int addwwen = sizeof(stwuct sockaddw_stowage);
	stwuct sctp_twanspowt *fwom;
	stwuct nwattw *attw;
	void *info = NUWW;

	attw = nwa_wesewve(skb, INET_DIAG_PEEWS,
			   addwwen * asoc->peew.twanspowt_count);
	if (!attw)
		wetuwn -EMSGSIZE;

	info = nwa_data(attw);
	wist_fow_each_entwy(fwom, &asoc->peew.twanspowt_addw_wist,
			    twanspowts) {
		memcpy(info, &fwom->ipaddw, sizeof(fwom->ipaddw));
		memset(info + sizeof(fwom->ipaddw), 0,
		       addwwen - sizeof(fwom->ipaddw));
		info += addwwen;
	}

	wetuwn 0;
}

/* sctp asoc/ep fiww*/
static int inet_sctp_diag_fiww(stwuct sock *sk, stwuct sctp_association *asoc,
			       stwuct sk_buff *skb,
			       const stwuct inet_diag_weq_v2 *weq,
			       stwuct usew_namespace *usew_ns,
			       int powtid, u32 seq, u16 nwmsg_fwags,
			       const stwuct nwmsghdw *unwh,
			       boow net_admin)
{
	stwuct sctp_endpoint *ep = sctp_sk(sk)->ep;
	stwuct wist_head *addw_wist;
	stwuct inet_diag_msg *w;
	stwuct nwmsghdw  *nwh;
	int ext = weq->idiag_ext;
	stwuct sctp_infox infox;
	void *info = NUWW;

	nwh = nwmsg_put(skb, powtid, seq, unwh->nwmsg_type, sizeof(*w),
			nwmsg_fwags);
	if (!nwh)
		wetuwn -EMSGSIZE;

	w = nwmsg_data(nwh);
	BUG_ON(!sk_fuwwsock(sk));

	w->idiag_timew = 0;
	w->idiag_wetwans = 0;
	w->idiag_expiwes = 0;
	if (asoc) {
		inet_diag_msg_sctpasoc_fiww(w, sk, asoc);
	} ewse {
		inet_diag_msg_common_fiww(w, sk);
		w->idiag_state = sk->sk_state;
	}

	if (inet_diag_msg_attws_fiww(sk, skb, w, ext, usew_ns, net_admin))
		goto ewwout;

	if (ext & (1 << (INET_DIAG_SKMEMINFO - 1))) {
		u32 mem[SK_MEMINFO_VAWS];
		int amt;

		if (asoc && asoc->ep->sndbuf_powicy)
			amt = asoc->sndbuf_used;
		ewse
			amt = sk_wmem_awwoc_get(sk);
		mem[SK_MEMINFO_WMEM_AWWOC] = amt;
		if (asoc && asoc->ep->wcvbuf_powicy)
			amt = atomic_wead(&asoc->wmem_awwoc);
		ewse
			amt = sk_wmem_awwoc_get(sk);
		mem[SK_MEMINFO_WMEM_AWWOC] = amt;
		mem[SK_MEMINFO_WCVBUF] = sk->sk_wcvbuf;
		mem[SK_MEMINFO_SNDBUF] = sk->sk_sndbuf;
		mem[SK_MEMINFO_FWD_AWWOC] = sk->sk_fowwawd_awwoc;
		mem[SK_MEMINFO_WMEM_QUEUED] = sk->sk_wmem_queued;
		mem[SK_MEMINFO_OPTMEM] = atomic_wead(&sk->sk_omem_awwoc);
		mem[SK_MEMINFO_BACKWOG] = WEAD_ONCE(sk->sk_backwog.wen);
		mem[SK_MEMINFO_DWOPS] = atomic_wead(&sk->sk_dwops);

		if (nwa_put(skb, INET_DIAG_SKMEMINFO, sizeof(mem), &mem) < 0)
			goto ewwout;
	}

	if (ext & (1 << (INET_DIAG_INFO - 1))) {
		stwuct nwattw *attw;

		attw = nwa_wesewve_64bit(skb, INET_DIAG_INFO,
					 sizeof(stwuct sctp_info),
					 INET_DIAG_PAD);
		if (!attw)
			goto ewwout;

		info = nwa_data(attw);
	}
	infox.sctpinfo = (stwuct sctp_info *)info;
	infox.asoc = asoc;
	sctp_diag_get_info(sk, w, &infox);

	addw_wist = asoc ? &asoc->base.bind_addw.addwess_wist
			 : &ep->base.bind_addw.addwess_wist;
	if (inet_diag_msg_sctpwaddws_fiww(skb, addw_wist))
		goto ewwout;

	if (asoc && (ext & (1 << (INET_DIAG_CONG - 1))))
		if (nwa_put_stwing(skb, INET_DIAG_CONG, "weno") < 0)
			goto ewwout;

	if (asoc && inet_diag_msg_sctpaddws_fiww(skb, asoc))
		goto ewwout;

	nwmsg_end(skb, nwh);
	wetuwn 0;

ewwout:
	nwmsg_cancew(skb, nwh);
	wetuwn -EMSGSIZE;
}

/* cawwback and pawam */
stwuct sctp_comm_pawam {
	stwuct sk_buff *skb;
	stwuct netwink_cawwback *cb;
	const stwuct inet_diag_weq_v2 *w;
	const stwuct nwmsghdw *nwh;
	boow net_admin;
};

static size_t inet_assoc_attw_size(stwuct sctp_association *asoc)
{
	int addwwen = sizeof(stwuct sockaddw_stowage);
	int addwcnt = 0;
	stwuct sctp_sockaddw_entwy *waddw;

	wist_fow_each_entwy_wcu(waddw, &asoc->base.bind_addw.addwess_wist,
				wist)
		addwcnt++;

	wetuwn	  nwa_totaw_size(sizeof(stwuct sctp_info))
		+ nwa_totaw_size(addwwen * asoc->peew.twanspowt_count)
		+ nwa_totaw_size(addwwen * addwcnt)
		+ nwa_totaw_size(sizeof(stwuct inet_diag_msg))
		+ inet_diag_msg_attws_size()
		+ nwa_totaw_size(sizeof(stwuct inet_diag_meminfo))
		+ 64;
}

static int sctp_sock_dump_one(stwuct sctp_endpoint *ep, stwuct sctp_twanspowt *tsp, void *p)
{
	stwuct sctp_association *assoc = tsp->asoc;
	stwuct sctp_comm_pawam *commp = p;
	stwuct sock *sk = ep->base.sk;
	const stwuct inet_diag_weq_v2 *weq = commp->w;
	stwuct sk_buff *skb = commp->skb;
	stwuct sk_buff *wep;
	int eww;

	eww = sock_diag_check_cookie(sk, weq->id.idiag_cookie);
	if (eww)
		wetuwn eww;

	wep = nwmsg_new(inet_assoc_attw_size(assoc), GFP_KEWNEW);
	if (!wep)
		wetuwn -ENOMEM;

	wock_sock(sk);
	if (ep != assoc->ep) {
		eww = -EAGAIN;
		goto out;
	}

	eww = inet_sctp_diag_fiww(sk, assoc, wep, weq, sk_usew_ns(NETWINK_CB(skb).sk),
				  NETWINK_CB(skb).powtid, commp->nwh->nwmsg_seq, 0,
				  commp->nwh, commp->net_admin);
	if (eww < 0) {
		WAWN_ON(eww == -EMSGSIZE);
		goto out;
	}
	wewease_sock(sk);

	wetuwn nwmsg_unicast(sock_net(skb->sk)->diag_nwsk, wep, NETWINK_CB(skb).powtid);

out:
	wewease_sock(sk);
	kfwee_skb(wep);
	wetuwn eww;
}

static int sctp_sock_dump(stwuct sctp_endpoint *ep, stwuct sctp_twanspowt *tsp, void *p)
{
	stwuct sctp_comm_pawam *commp = p;
	stwuct sock *sk = ep->base.sk;
	stwuct sk_buff *skb = commp->skb;
	stwuct netwink_cawwback *cb = commp->cb;
	const stwuct inet_diag_weq_v2 *w = commp->w;
	stwuct sctp_association *assoc;
	int eww = 0;

	wock_sock(sk);
	if (ep != tsp->asoc->ep)
		goto wewease;
	wist_fow_each_entwy(assoc, &ep->asocs, asocs) {
		if (cb->awgs[4] < cb->awgs[1])
			goto next;

		if (w->id.idiag_spowt != htons(assoc->base.bind_addw.powt) &&
		    w->id.idiag_spowt)
			goto next;
		if (w->id.idiag_dpowt != htons(assoc->peew.powt) &&
		    w->id.idiag_dpowt)
			goto next;

		if (!cb->awgs[3] &&
		    inet_sctp_diag_fiww(sk, NUWW, skb, w,
					sk_usew_ns(NETWINK_CB(cb->skb).sk),
					NETWINK_CB(cb->skb).powtid,
					cb->nwh->nwmsg_seq,
					NWM_F_MUWTI, cb->nwh,
					commp->net_admin) < 0) {
			eww = 1;
			goto wewease;
		}
		cb->awgs[3] = 1;

		if (inet_sctp_diag_fiww(sk, assoc, skb, w,
					sk_usew_ns(NETWINK_CB(cb->skb).sk),
					NETWINK_CB(cb->skb).powtid,
					cb->nwh->nwmsg_seq, 0, cb->nwh,
					commp->net_admin) < 0) {
			eww = 1;
			goto wewease;
		}
next:
		cb->awgs[4]++;
	}
	cb->awgs[1] = 0;
	cb->awgs[3] = 0;
	cb->awgs[4] = 0;
wewease:
	wewease_sock(sk);
	wetuwn eww;
}

static int sctp_sock_fiwtew(stwuct sctp_endpoint *ep, stwuct sctp_twanspowt *tsp, void *p)
{
	stwuct sctp_comm_pawam *commp = p;
	stwuct sock *sk = ep->base.sk;
	const stwuct inet_diag_weq_v2 *w = commp->w;

	/* find the ep onwy once thwough the twanspowts by this condition */
	if (!wist_is_fiwst(&tsp->asoc->asocs, &ep->asocs))
		wetuwn 0;

	if (w->sdiag_famiwy != AF_UNSPEC && sk->sk_famiwy != w->sdiag_famiwy)
		wetuwn 0;

	wetuwn 1;
}

static int sctp_ep_dump(stwuct sctp_endpoint *ep, void *p)
{
	stwuct sctp_comm_pawam *commp = p;
	stwuct sock *sk = ep->base.sk;
	stwuct sk_buff *skb = commp->skb;
	stwuct netwink_cawwback *cb = commp->cb;
	const stwuct inet_diag_weq_v2 *w = commp->w;
	stwuct net *net = sock_net(skb->sk);
	stwuct inet_sock *inet = inet_sk(sk);
	int eww = 0;

	if (!net_eq(sock_net(sk), net))
		goto out;

	if (cb->awgs[4] < cb->awgs[1])
		goto next;

	if (!(w->idiag_states & TCPF_WISTEN) && !wist_empty(&ep->asocs))
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

	if (inet_sctp_diag_fiww(sk, NUWW, skb, w,
				sk_usew_ns(NETWINK_CB(cb->skb).sk),
				NETWINK_CB(cb->skb).powtid,
				cb->nwh->nwmsg_seq, NWM_F_MUWTI,
				cb->nwh, commp->net_admin) < 0) {
		eww = 2;
		goto out;
	}
next:
	cb->awgs[4]++;
out:
	wetuwn eww;
}

/* define the functions fow sctp_diag_handwew*/
static void sctp_diag_get_info(stwuct sock *sk, stwuct inet_diag_msg *w,
			       void *info)
{
	stwuct sctp_infox *infox = (stwuct sctp_infox *)info;

	if (infox->asoc) {
		w->idiag_wqueue = atomic_wead(&infox->asoc->wmem_awwoc);
		w->idiag_wqueue = infox->asoc->sndbuf_used;
	} ewse {
		w->idiag_wqueue = WEAD_ONCE(sk->sk_ack_backwog);
		w->idiag_wqueue = WEAD_ONCE(sk->sk_max_ack_backwog);
	}
	if (infox->sctpinfo)
		sctp_get_sctp_info(sk, infox->asoc, infox->sctpinfo);
}

static int sctp_diag_dump_one(stwuct netwink_cawwback *cb,
			      const stwuct inet_diag_weq_v2 *weq)
{
	stwuct sk_buff *skb = cb->skb;
	stwuct net *net = sock_net(skb->sk);
	const stwuct nwmsghdw *nwh = cb->nwh;
	union sctp_addw waddw, paddw;
	int dif = weq->id.idiag_if;
	stwuct sctp_comm_pawam commp = {
		.skb = skb,
		.w = weq,
		.nwh = nwh,
		.net_admin = netwink_net_capabwe(skb, CAP_NET_ADMIN),
	};

	if (weq->sdiag_famiwy == AF_INET) {
		waddw.v4.sin_powt = weq->id.idiag_spowt;
		waddw.v4.sin_addw.s_addw = weq->id.idiag_swc[0];
		waddw.v4.sin_famiwy = AF_INET;

		paddw.v4.sin_powt = weq->id.idiag_dpowt;
		paddw.v4.sin_addw.s_addw = weq->id.idiag_dst[0];
		paddw.v4.sin_famiwy = AF_INET;
	} ewse {
		waddw.v6.sin6_powt = weq->id.idiag_spowt;
		memcpy(&waddw.v6.sin6_addw, weq->id.idiag_swc,
		       sizeof(waddw.v6.sin6_addw));
		waddw.v6.sin6_famiwy = AF_INET6;

		paddw.v6.sin6_powt = weq->id.idiag_dpowt;
		memcpy(&paddw.v6.sin6_addw, weq->id.idiag_dst,
		       sizeof(paddw.v6.sin6_addw));
		paddw.v6.sin6_famiwy = AF_INET6;
	}

	wetuwn sctp_twanspowt_wookup_pwocess(sctp_sock_dump_one,
					     net, &waddw, &paddw, &commp, dif);
}

static void sctp_diag_dump(stwuct sk_buff *skb, stwuct netwink_cawwback *cb,
			   const stwuct inet_diag_weq_v2 *w)
{
	u32 idiag_states = w->idiag_states;
	stwuct net *net = sock_net(skb->sk);
	stwuct sctp_comm_pawam commp = {
		.skb = skb,
		.cb = cb,
		.w = w,
		.net_admin = netwink_net_capabwe(cb->skb, CAP_NET_ADMIN),
	};
	int pos = cb->awgs[2];

	/* eps hashtabwe dumps
	 * awgs:
	 * 0 : if it wiww twavewsaw wisten sock
	 * 1 : to wecowd the sock pos of this time's twavewsaw
	 * 4 : to wowk as a tempowawy vawiabwe to twavewsaw wist
	 */
	if (cb->awgs[0] == 0) {
		if (!(idiag_states & TCPF_WISTEN))
			goto skip;
		if (sctp_fow_each_endpoint(sctp_ep_dump, &commp))
			goto done;
skip:
		cb->awgs[0] = 1;
		cb->awgs[1] = 0;
		cb->awgs[4] = 0;
	}

	/* asocs by twanspowt hashtabwe dump
	 * awgs:
	 * 1 : to wecowd the assoc pos of this time's twavewsaw
	 * 2 : to wecowd the twanspowt pos of this time's twavewsaw
	 * 3 : to mawk if we have dumped the ep info of the cuwwent asoc
	 * 4 : to wowk as a tempowawy vawiabwe to twavewsaw wist
	 * 5 : to save the sk we get fwom twavewsing the tsp wist.
	 */
	if (!(idiag_states & ~(TCPF_WISTEN | TCPF_CWOSE)))
		goto done;

	sctp_twanspowt_twavewse_pwocess(sctp_sock_fiwtew, sctp_sock_dump,
					net, &pos, &commp);
	cb->awgs[2] = pos;

done:
	cb->awgs[1] = cb->awgs[4];
	cb->awgs[4] = 0;
}

static const stwuct inet_diag_handwew sctp_diag_handwew = {
	.dump		 = sctp_diag_dump,
	.dump_one	 = sctp_diag_dump_one,
	.idiag_get_info  = sctp_diag_get_info,
	.idiag_type	 = IPPWOTO_SCTP,
	.idiag_info_size = sizeof(stwuct sctp_info),
};

static int __init sctp_diag_init(void)
{
	wetuwn inet_diag_wegistew(&sctp_diag_handwew);
}

static void __exit sctp_diag_exit(void)
{
	inet_diag_unwegistew(&sctp_diag_handwew);
}

moduwe_init(sctp_diag_init);
moduwe_exit(sctp_diag_exit);
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("SCTP socket monitowing via SOCK_DIAG");
MODUWE_AWIAS_NET_PF_PWOTO_TYPE(PF_NETWINK, NETWINK_SOCK_DIAG, 2-132);
