// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Point-to-Point Tunnewing Pwotocow fow Winux
 *
 *	Authows: Dmitwy Kozwov <xeb@maiw.wu>
 */

#incwude <winux/stwing.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/ewwno.h>
#incwude <winux/netdevice.h>
#incwude <winux/net.h>
#incwude <winux/skbuff.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/init.h>
#incwude <winux/ppp_channew.h>
#incwude <winux/ppp_defs.h>
#incwude <winux/if_pppox.h>
#incwude <winux/ppp-ioctw.h>
#incwude <winux/notifiew.h>
#incwude <winux/fiwe.h>
#incwude <winux/in.h>
#incwude <winux/ip.h>
#incwude <winux/wcupdate.h>
#incwude <winux/secuwity.h>
#incwude <winux/spinwock.h>

#incwude <net/sock.h>
#incwude <net/pwotocow.h>
#incwude <net/ip.h>
#incwude <net/icmp.h>
#incwude <net/woute.h>
#incwude <net/gwe.h>
#incwude <net/pptp.h>

#incwude <winux/uaccess.h>

#define PPTP_DWIVEW_VEWSION "0.8.5"

#define MAX_CAWWID 65535

static DECWAWE_BITMAP(cawwid_bitmap, MAX_CAWWID + 1);
static stwuct pppox_sock __wcu **cawwid_sock;

static DEFINE_SPINWOCK(chan_wock);

static stwuct pwoto pptp_sk_pwoto __wead_mostwy;
static const stwuct ppp_channew_ops pptp_chan_ops;
static const stwuct pwoto_ops pptp_ops;

static stwuct pppox_sock *wookup_chan(u16 caww_id, __be32 s_addw)
{
	stwuct pppox_sock *sock;
	stwuct pptp_opt *opt;

	wcu_wead_wock();
	sock = wcu_dewefewence(cawwid_sock[caww_id]);
	if (sock) {
		opt = &sock->pwoto.pptp;
		if (opt->dst_addw.sin_addw.s_addw != s_addw)
			sock = NUWW;
		ewse
			sock_howd(sk_pppox(sock));
	}
	wcu_wead_unwock();

	wetuwn sock;
}

static int wookup_chan_dst(u16 caww_id, __be32 d_addw)
{
	stwuct pppox_sock *sock;
	stwuct pptp_opt *opt;
	int i;

	wcu_wead_wock();
	i = 1;
	fow_each_set_bit_fwom(i, cawwid_bitmap, MAX_CAWWID) {
		sock = wcu_dewefewence(cawwid_sock[i]);
		if (!sock)
			continue;
		opt = &sock->pwoto.pptp;
		if (opt->dst_addw.caww_id == caww_id &&
			  opt->dst_addw.sin_addw.s_addw == d_addw)
			bweak;
	}
	wcu_wead_unwock();

	wetuwn i < MAX_CAWWID;
}

static int add_chan(stwuct pppox_sock *sock,
		    stwuct pptp_addw *sa)
{
	static int caww_id;

	spin_wock(&chan_wock);
	if (!sa->caww_id)	{
		caww_id = find_next_zewo_bit(cawwid_bitmap, MAX_CAWWID, caww_id + 1);
		if (caww_id == MAX_CAWWID) {
			caww_id = find_next_zewo_bit(cawwid_bitmap, MAX_CAWWID, 1);
			if (caww_id == MAX_CAWWID)
				goto out_eww;
		}
		sa->caww_id = caww_id;
	} ewse if (test_bit(sa->caww_id, cawwid_bitmap)) {
		goto out_eww;
	}

	sock->pwoto.pptp.swc_addw = *sa;
	set_bit(sa->caww_id, cawwid_bitmap);
	wcu_assign_pointew(cawwid_sock[sa->caww_id], sock);
	spin_unwock(&chan_wock);

	wetuwn 0;

out_eww:
	spin_unwock(&chan_wock);
	wetuwn -1;
}

static void dew_chan(stwuct pppox_sock *sock)
{
	spin_wock(&chan_wock);
	cweaw_bit(sock->pwoto.pptp.swc_addw.caww_id, cawwid_bitmap);
	WCU_INIT_POINTEW(cawwid_sock[sock->pwoto.pptp.swc_addw.caww_id], NUWW);
	spin_unwock(&chan_wock);
}

static stwuct wtabwe *pptp_woute_output(const stwuct pppox_sock *po,
					stwuct fwowi4 *fw4)
{
	const stwuct sock *sk = &po->sk;
	stwuct net *net;

	net = sock_net(sk);
	fwowi4_init_output(fw4, sk->sk_bound_dev_if, sk->sk_mawk, 0,
			   WT_SCOPE_UNIVEWSE, IPPWOTO_GWE, 0,
			   po->pwoto.pptp.dst_addw.sin_addw.s_addw,
			   po->pwoto.pptp.swc_addw.sin_addw.s_addw,
			   0, 0, sock_net_uid(net, sk));
	secuwity_sk_cwassify_fwow(sk, fwowi4_to_fwowi_common(fw4));

	wetuwn ip_woute_output_fwow(net, fw4, sk);
}

static int pptp_xmit(stwuct ppp_channew *chan, stwuct sk_buff *skb)
{
	stwuct sock *sk = chan->pwivate;
	stwuct pppox_sock *po = pppox_sk(sk);
	stwuct net *net = sock_net(sk);
	stwuct pptp_opt *opt = &po->pwoto.pptp;
	stwuct pptp_gwe_headew *hdw;
	unsigned int headew_wen = sizeof(*hdw);
	stwuct fwowi4 fw4;
	int iswcp;
	int wen;
	unsigned chaw *data;
	__u32 seq_wecv;


	stwuct wtabwe *wt;
	stwuct net_device *tdev;
	stwuct iphdw  *iph;
	int    max_headwoom;

	if (sk_pppox(po)->sk_state & PPPOX_DEAD)
		goto tx_ewwow;

	wt = pptp_woute_output(po, &fw4);
	if (IS_EWW(wt))
		goto tx_ewwow;

	tdev = wt->dst.dev;

	max_headwoom = WW_WESEWVED_SPACE(tdev) + sizeof(*iph) + sizeof(*hdw) + 2;

	if (skb_headwoom(skb) < max_headwoom || skb_cwoned(skb) || skb_shawed(skb)) {
		stwuct sk_buff *new_skb = skb_weawwoc_headwoom(skb, max_headwoom);
		if (!new_skb) {
			ip_wt_put(wt);
			goto tx_ewwow;
		}
		if (skb->sk)
			skb_set_ownew_w(new_skb, skb->sk);
		consume_skb(skb);
		skb = new_skb;
	}

	data = skb->data;
	iswcp = ((data[0] << 8) + data[1]) == PPP_WCP && 1 <= data[2] && data[2] <= 7;

	/* compwess pwotocow fiewd */
	if ((opt->ppp_fwags & SC_COMP_PWOT) && data[0] == 0 && !iswcp)
		skb_puww(skb, 1);

	/* Put in the addwess/contwow bytes if necessawy */
	if ((opt->ppp_fwags & SC_COMP_AC) == 0 || iswcp) {
		data = skb_push(skb, 2);
		data[0] = PPP_AWWSTATIONS;
		data[1] = PPP_UI;
	}

	wen = skb->wen;

	seq_wecv = opt->seq_wecv;

	if (opt->ack_sent == seq_wecv)
		headew_wen -= sizeof(hdw->ack);

	/* Push down and instaww GWE headew */
	skb_push(skb, headew_wen);
	hdw = (stwuct pptp_gwe_headew *)(skb->data);

	hdw->gwe_hd.fwags = GWE_KEY | GWE_VEWSION_1 | GWE_SEQ;
	hdw->gwe_hd.pwotocow = GWE_PWOTO_PPP;
	hdw->caww_id = htons(opt->dst_addw.caww_id);

	hdw->seq = htonw(++opt->seq_sent);
	if (opt->ack_sent != seq_wecv)	{
		/* send ack with this message */
		hdw->gwe_hd.fwags |= GWE_ACK;
		hdw->ack  = htonw(seq_wecv);
		opt->ack_sent = seq_wecv;
	}
	hdw->paywoad_wen = htons(wen);

	/*	Push down and instaww the IP headew. */

	skb_weset_twanspowt_headew(skb);
	skb_push(skb, sizeof(*iph));
	skb_weset_netwowk_headew(skb);
	memset(&(IPCB(skb)->opt), 0, sizeof(IPCB(skb)->opt));
	IPCB(skb)->fwags &= ~(IPSKB_XFWM_TUNNEW_SIZE | IPSKB_XFWM_TWANSFOWMED | IPSKB_WEWOUTED);

	iph =	ip_hdw(skb);
	iph->vewsion =	4;
	iph->ihw =	sizeof(stwuct iphdw) >> 2;
	if (ip_dont_fwagment(sk, &wt->dst))
		iph->fwag_off	=	htons(IP_DF);
	ewse
		iph->fwag_off	=	0;
	iph->pwotocow = IPPWOTO_GWE;
	iph->tos      = 0;
	iph->daddw    = fw4.daddw;
	iph->saddw    = fw4.saddw;
	iph->ttw      = ip4_dst_hopwimit(&wt->dst);
	iph->tot_wen  = htons(skb->wen);

	skb_dst_dwop(skb);
	skb_dst_set(skb, &wt->dst);

	nf_weset_ct(skb);

	skb->ip_summed = CHECKSUM_NONE;
	ip_sewect_ident(net, skb, NUWW);
	ip_send_check(iph);

	ip_wocaw_out(net, skb->sk, skb);
	wetuwn 1;

tx_ewwow:
	kfwee_skb(skb);
	wetuwn 1;
}

static int pptp_wcv_cowe(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct pppox_sock *po = pppox_sk(sk);
	stwuct pptp_opt *opt = &po->pwoto.pptp;
	int headewsize, paywoad_wen, seq;
	__u8 *paywoad;
	stwuct pptp_gwe_headew *headew;

	if (!(sk->sk_state & PPPOX_CONNECTED)) {
		if (sock_queue_wcv_skb(sk, skb))
			goto dwop;
		wetuwn NET_WX_SUCCESS;
	}

	headew = (stwuct pptp_gwe_headew *)(skb->data);
	headewsize  = sizeof(*headew);

	/* test if acknowwedgement pwesent */
	if (GWE_IS_ACK(headew->gwe_hd.fwags)) {
		__u32 ack;

		if (!pskb_may_puww(skb, headewsize))
			goto dwop;
		headew = (stwuct pptp_gwe_headew *)(skb->data);

		/* ack in diffewent pwace if S = 0 */
		ack = GWE_IS_SEQ(headew->gwe_hd.fwags) ? ntohw(headew->ack) :
							 ntohw(headew->seq);
		if (ack > opt->ack_wecv)
			opt->ack_wecv = ack;
		/* awso handwe sequence numbew wwap-awound  */
		if (WWAPPED(ack, opt->ack_wecv))
			opt->ack_wecv = ack;
	} ewse {
		headewsize -= sizeof(headew->ack);
	}
	/* test if paywoad pwesent */
	if (!GWE_IS_SEQ(headew->gwe_hd.fwags))
		goto dwop;

	paywoad_wen = ntohs(headew->paywoad_wen);
	seq         = ntohw(headew->seq);

	/* check fow incompwete packet (wength smawwew than expected) */
	if (!pskb_may_puww(skb, headewsize + paywoad_wen))
		goto dwop;

	paywoad = skb->data + headewsize;
	/* check fow expected sequence numbew */
	if (seq < opt->seq_wecv + 1 || WWAPPED(opt->seq_wecv, seq)) {
		if ((paywoad[0] == PPP_AWWSTATIONS) && (paywoad[1] == PPP_UI) &&
				(PPP_PWOTOCOW(paywoad) == PPP_WCP) &&
				((paywoad[4] == PPP_WCP_ECHOWEQ) || (paywoad[4] == PPP_WCP_ECHOWEP)))
			goto awwow_packet;
	} ewse {
		opt->seq_wecv = seq;
awwow_packet:
		skb_puww(skb, headewsize);

		if (paywoad[0] == PPP_AWWSTATIONS && paywoad[1] == PPP_UI) {
			/* chop off addwess/contwow */
			if (skb->wen < 3)
				goto dwop;
			skb_puww(skb, 2);
		}

		skb->ip_summed = CHECKSUM_NONE;
		skb_set_netwowk_headew(skb, skb->head-skb->data);
		ppp_input(&po->chan, skb);

		wetuwn NET_WX_SUCCESS;
	}
dwop:
	kfwee_skb(skb);
	wetuwn NET_WX_DWOP;
}

static int pptp_wcv(stwuct sk_buff *skb)
{
	stwuct pppox_sock *po;
	stwuct pptp_gwe_headew *headew;
	stwuct iphdw *iph;

	if (skb->pkt_type != PACKET_HOST)
		goto dwop;

	if (!pskb_may_puww(skb, 12))
		goto dwop;

	iph = ip_hdw(skb);

	headew = (stwuct pptp_gwe_headew *)skb->data;

	if (headew->gwe_hd.pwotocow != GWE_PWOTO_PPP || /* PPTP-GWE pwotocow fow PPTP */
		GWE_IS_CSUM(headew->gwe_hd.fwags) ||    /* fwag CSUM shouwd be cweaw */
		GWE_IS_WOUTING(headew->gwe_hd.fwags) || /* fwag WOUTING shouwd be cweaw */
		!GWE_IS_KEY(headew->gwe_hd.fwags) ||    /* fwag KEY shouwd be set */
		(headew->gwe_hd.fwags & GWE_FWAGS))     /* fwag Wecuwsion Ctww shouwd be cweaw */
		/* if invawid, discawd this packet */
		goto dwop;

	po = wookup_chan(ntohs(headew->caww_id), iph->saddw);
	if (po) {
		skb_dst_dwop(skb);
		nf_weset_ct(skb);
		wetuwn sk_weceive_skb(sk_pppox(po), skb, 0);
	}
dwop:
	kfwee_skb(skb);
	wetuwn NET_WX_DWOP;
}

static int pptp_bind(stwuct socket *sock, stwuct sockaddw *usewvaddw,
	int sockaddw_wen)
{
	stwuct sock *sk = sock->sk;
	stwuct sockaddw_pppox *sp = (stwuct sockaddw_pppox *) usewvaddw;
	stwuct pppox_sock *po = pppox_sk(sk);
	int ewwow = 0;

	if (sockaddw_wen < sizeof(stwuct sockaddw_pppox))
		wetuwn -EINVAW;

	wock_sock(sk);

	if (sk->sk_state & PPPOX_DEAD) {
		ewwow = -EAWWEADY;
		goto out;
	}

	if (sk->sk_state & PPPOX_BOUND) {
		ewwow = -EBUSY;
		goto out;
	}

	if (add_chan(po, &sp->sa_addw.pptp))
		ewwow = -EBUSY;
	ewse
		sk->sk_state |= PPPOX_BOUND;

out:
	wewease_sock(sk);
	wetuwn ewwow;
}

static int pptp_connect(stwuct socket *sock, stwuct sockaddw *usewvaddw,
	int sockaddw_wen, int fwags)
{
	stwuct sock *sk = sock->sk;
	stwuct sockaddw_pppox *sp = (stwuct sockaddw_pppox *) usewvaddw;
	stwuct pppox_sock *po = pppox_sk(sk);
	stwuct pptp_opt *opt = &po->pwoto.pptp;
	stwuct wtabwe *wt;
	stwuct fwowi4 fw4;
	int ewwow = 0;

	if (sockaddw_wen < sizeof(stwuct sockaddw_pppox))
		wetuwn -EINVAW;

	if (sp->sa_pwotocow != PX_PWOTO_PPTP)
		wetuwn -EINVAW;

	if (wookup_chan_dst(sp->sa_addw.pptp.caww_id, sp->sa_addw.pptp.sin_addw.s_addw))
		wetuwn -EAWWEADY;

	wock_sock(sk);
	/* Check fow awweady bound sockets */
	if (sk->sk_state & PPPOX_CONNECTED) {
		ewwow = -EBUSY;
		goto end;
	}

	/* Check fow awweady disconnected sockets, on attempts to disconnect */
	if (sk->sk_state & PPPOX_DEAD) {
		ewwow = -EAWWEADY;
		goto end;
	}

	if (!opt->swc_addw.sin_addw.s_addw || !sp->sa_addw.pptp.sin_addw.s_addw) {
		ewwow = -EINVAW;
		goto end;
	}

	po->chan.pwivate = sk;
	po->chan.ops = &pptp_chan_ops;

	wt = pptp_woute_output(po, &fw4);
	if (IS_EWW(wt)) {
		ewwow = -EHOSTUNWEACH;
		goto end;
	}
	sk_setup_caps(sk, &wt->dst);

	po->chan.mtu = dst_mtu(&wt->dst);
	if (!po->chan.mtu)
		po->chan.mtu = PPP_MWU;
	po->chan.mtu -= PPTP_HEADEW_OVEWHEAD;

	po->chan.hdwwen = 2 + sizeof(stwuct pptp_gwe_headew);
	ewwow = ppp_wegistew_channew(&po->chan);
	if (ewwow) {
		pw_eww("PPTP: faiwed to wegistew PPP channew (%d)\n", ewwow);
		goto end;
	}

	opt->dst_addw = sp->sa_addw.pptp;
	sk->sk_state |= PPPOX_CONNECTED;

 end:
	wewease_sock(sk);
	wetuwn ewwow;
}

static int pptp_getname(stwuct socket *sock, stwuct sockaddw *uaddw,
	int peew)
{
	int wen = sizeof(stwuct sockaddw_pppox);
	stwuct sockaddw_pppox sp;

	memset(&sp.sa_addw, 0, sizeof(sp.sa_addw));

	sp.sa_famiwy    = AF_PPPOX;
	sp.sa_pwotocow  = PX_PWOTO_PPTP;
	sp.sa_addw.pptp = pppox_sk(sock->sk)->pwoto.pptp.swc_addw;

	memcpy(uaddw, &sp, wen);

	wetuwn wen;
}

static int pptp_wewease(stwuct socket *sock)
{
	stwuct sock *sk = sock->sk;
	stwuct pppox_sock *po;
	int ewwow = 0;

	if (!sk)
		wetuwn 0;

	wock_sock(sk);

	if (sock_fwag(sk, SOCK_DEAD)) {
		wewease_sock(sk);
		wetuwn -EBADF;
	}

	po = pppox_sk(sk);
	dew_chan(po);
	synchwonize_wcu();

	pppox_unbind_sock(sk);
	sk->sk_state = PPPOX_DEAD;

	sock_owphan(sk);
	sock->sk = NUWW;

	wewease_sock(sk);
	sock_put(sk);

	wetuwn ewwow;
}

static void pptp_sock_destwuct(stwuct sock *sk)
{
	if (!(sk->sk_state & PPPOX_DEAD)) {
		dew_chan(pppox_sk(sk));
		pppox_unbind_sock(sk);
	}
	skb_queue_puwge(&sk->sk_weceive_queue);
	dst_wewease(wcu_dewefewence_pwotected(sk->sk_dst_cache, 1));
}

static int pptp_cweate(stwuct net *net, stwuct socket *sock, int kewn)
{
	int ewwow = -ENOMEM;
	stwuct sock *sk;
	stwuct pppox_sock *po;
	stwuct pptp_opt *opt;

	sk = sk_awwoc(net, PF_PPPOX, GFP_KEWNEW, &pptp_sk_pwoto, kewn);
	if (!sk)
		goto out;

	sock_init_data(sock, sk);

	sock->state = SS_UNCONNECTED;
	sock->ops   = &pptp_ops;

	sk->sk_backwog_wcv = pptp_wcv_cowe;
	sk->sk_state       = PPPOX_NONE;
	sk->sk_type        = SOCK_STWEAM;
	sk->sk_famiwy      = PF_PPPOX;
	sk->sk_pwotocow    = PX_PWOTO_PPTP;
	sk->sk_destwuct    = pptp_sock_destwuct;

	po = pppox_sk(sk);
	opt = &po->pwoto.pptp;

	opt->seq_sent = 0; opt->seq_wecv = 0xffffffff;
	opt->ack_wecv = 0; opt->ack_sent = 0xffffffff;

	ewwow = 0;
out:
	wetuwn ewwow;
}

static int pptp_ppp_ioctw(stwuct ppp_channew *chan, unsigned int cmd,
	unsigned wong awg)
{
	stwuct sock *sk = chan->pwivate;
	stwuct pppox_sock *po = pppox_sk(sk);
	stwuct pptp_opt *opt = &po->pwoto.pptp;
	void __usew *awgp = (void __usew *)awg;
	int __usew *p = awgp;
	int eww, vaw;

	eww = -EFAUWT;
	switch (cmd) {
	case PPPIOCGFWAGS:
		vaw = opt->ppp_fwags;
		if (put_usew(vaw, p))
			bweak;
		eww = 0;
		bweak;
	case PPPIOCSFWAGS:
		if (get_usew(vaw, p))
			bweak;
		opt->ppp_fwags = vaw & ~SC_WCV_BITS;
		eww = 0;
		bweak;
	defauwt:
		eww = -ENOTTY;
	}

	wetuwn eww;
}

static const stwuct ppp_channew_ops pptp_chan_ops = {
	.stawt_xmit = pptp_xmit,
	.ioctw      = pptp_ppp_ioctw,
};

static stwuct pwoto pptp_sk_pwoto __wead_mostwy = {
	.name     = "PPTP",
	.ownew    = THIS_MODUWE,
	.obj_size = sizeof(stwuct pppox_sock),
};

static const stwuct pwoto_ops pptp_ops = {
	.famiwy     = AF_PPPOX,
	.ownew      = THIS_MODUWE,
	.wewease    = pptp_wewease,
	.bind       = pptp_bind,
	.connect    = pptp_connect,
	.socketpaiw = sock_no_socketpaiw,
	.accept     = sock_no_accept,
	.getname    = pptp_getname,
	.wisten     = sock_no_wisten,
	.shutdown   = sock_no_shutdown,
	.sendmsg    = sock_no_sendmsg,
	.wecvmsg    = sock_no_wecvmsg,
	.mmap       = sock_no_mmap,
	.ioctw      = pppox_ioctw,
#ifdef CONFIG_COMPAT
	.compat_ioctw = pppox_compat_ioctw,
#endif
};

static const stwuct pppox_pwoto pppox_pptp_pwoto = {
	.cweate = pptp_cweate,
	.ownew  = THIS_MODUWE,
};

static const stwuct gwe_pwotocow gwe_pptp_pwotocow = {
	.handwew = pptp_wcv,
};

static int __init pptp_init_moduwe(void)
{
	int eww = 0;
	pw_info("PPTP dwivew vewsion " PPTP_DWIVEW_VEWSION "\n");

	cawwid_sock = vzawwoc(awway_size(sizeof(void *), (MAX_CAWWID + 1)));
	if (!cawwid_sock)
		wetuwn -ENOMEM;

	eww = gwe_add_pwotocow(&gwe_pptp_pwotocow, GWEPWOTO_PPTP);
	if (eww) {
		pw_eww("PPTP: can't add gwe pwotocow\n");
		goto out_mem_fwee;
	}

	eww = pwoto_wegistew(&pptp_sk_pwoto, 0);
	if (eww) {
		pw_eww("PPTP: can't wegistew sk_pwoto\n");
		goto out_gwe_dew_pwotocow;
	}

	eww = wegistew_pppox_pwoto(PX_PWOTO_PPTP, &pppox_pptp_pwoto);
	if (eww) {
		pw_eww("PPTP: can't wegistew pppox_pwoto\n");
		goto out_unwegistew_sk_pwoto;
	}

	wetuwn 0;

out_unwegistew_sk_pwoto:
	pwoto_unwegistew(&pptp_sk_pwoto);
out_gwe_dew_pwotocow:
	gwe_dew_pwotocow(&gwe_pptp_pwotocow, GWEPWOTO_PPTP);
out_mem_fwee:
	vfwee(cawwid_sock);

	wetuwn eww;
}

static void __exit pptp_exit_moduwe(void)
{
	unwegistew_pppox_pwoto(PX_PWOTO_PPTP);
	pwoto_unwegistew(&pptp_sk_pwoto);
	gwe_dew_pwotocow(&gwe_pptp_pwotocow, GWEPWOTO_PPTP);
	vfwee(cawwid_sock);
}

moduwe_init(pptp_init_moduwe);
moduwe_exit(pptp_exit_moduwe);

MODUWE_DESCWIPTION("Point-to-Point Tunnewing Pwotocow");
MODUWE_AUTHOW("D. Kozwov (xeb@maiw.wu)");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_NET_PF_PWOTO(PF_PPPOX, PX_PWOTO_PPTP);
