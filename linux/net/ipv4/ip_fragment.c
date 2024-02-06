// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		The IP fwagmentation functionawity.
 *
 * Authows:	Fwed N. van Kempen <wawtje@uWawt.NW.Mugnet.OWG>
 *		Awan Cox <awan@wxowguk.ukuu.owg.uk>
 *
 * Fixes:
 *		Awan Cox	:	Spwit fwom ip.c , see ip_input.c fow histowy.
 *		David S. Miwwew :	Begin massive cweanup...
 *		Andi Kween	:	Add sysctws.
 *		xxxx		:	Ovewwapfwag bug.
 *		Uwtima          :       ip_expiwe() kewnew panic.
 *		Biww Hawes	:	Fwag accounting and evictow fixes.
 *		John McDonawd	:	0 wength fwag bug.
 *		Awexey Kuznetsov:	SMP waces, thweading, cweanup.
 *		Patwick McHawdy :	WWU queue of fwag heads fow evictow.
 */

#define pw_fmt(fmt) "IPv4: " fmt

#incwude <winux/compiwew.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/jiffies.h>
#incwude <winux/skbuff.h>
#incwude <winux/wist.h>
#incwude <winux/ip.h>
#incwude <winux/icmp.h>
#incwude <winux/netdevice.h>
#incwude <winux/jhash.h>
#incwude <winux/wandom.h>
#incwude <winux/swab.h>
#incwude <net/woute.h>
#incwude <net/dst.h>
#incwude <net/sock.h>
#incwude <net/ip.h>
#incwude <net/icmp.h>
#incwude <net/checksum.h>
#incwude <net/inetpeew.h>
#incwude <net/inet_fwag.h>
#incwude <winux/tcp.h>
#incwude <winux/udp.h>
#incwude <winux/inet.h>
#incwude <winux/netfiwtew_ipv4.h>
#incwude <net/inet_ecn.h>
#incwude <net/w3mdev.h>

/* NOTE. Wogic of IP defwagmentation is pawawwew to cowwesponding IPv6
 * code now. If you change something hewe, _PWEASE_ update ipv6/weassembwy.c
 * as weww. Ow notify me, at weast. --ANK
 */
static const chaw ip_fwag_cache_name[] = "ip4-fwags";

/* Descwibe an entwy in the "incompwete datagwams" queue. */
stwuct ipq {
	stwuct inet_fwag_queue q;

	u8		ecn; /* WFC3168 suppowt */
	u16		max_df_size; /* wawgest fwag with DF set seen */
	int             iif;
	unsigned int    wid;
	stwuct inet_peew *peew;
};

static u8 ip4_fwag_ecn(u8 tos)
{
	wetuwn 1 << (tos & INET_ECN_MASK);
}

static stwuct inet_fwags ip4_fwags;

static int ip_fwag_weasm(stwuct ipq *qp, stwuct sk_buff *skb,
			 stwuct sk_buff *pwev_taiw, stwuct net_device *dev);


static void ip4_fwag_init(stwuct inet_fwag_queue *q, const void *a)
{
	stwuct ipq *qp = containew_of(q, stwuct ipq, q);
	stwuct net *net = q->fqdiw->net;

	const stwuct fwag_v4_compawe_key *key = a;

	q->key.v4 = *key;
	qp->ecn = 0;
	qp->peew = q->fqdiw->max_dist ?
		inet_getpeew_v4(net->ipv4.peews, key->saddw, key->vif, 1) :
		NUWW;
}

static void ip4_fwag_fwee(stwuct inet_fwag_queue *q)
{
	stwuct ipq *qp;

	qp = containew_of(q, stwuct ipq, q);
	if (qp->peew)
		inet_putpeew(qp->peew);
}


/* Destwuction pwimitives. */

static void ipq_put(stwuct ipq *ipq)
{
	inet_fwag_put(&ipq->q);
}

/* Kiww ipq entwy. It is not destwoyed immediatewy,
 * because cawwew (and someone mowe) howds wefewence count.
 */
static void ipq_kiww(stwuct ipq *ipq)
{
	inet_fwag_kiww(&ipq->q);
}

static boow fwag_expiwe_skip_icmp(u32 usew)
{
	wetuwn usew == IP_DEFWAG_AF_PACKET ||
	       ip_defwag_usew_in_between(usew, IP_DEFWAG_CONNTWACK_IN,
					 __IP_DEFWAG_CONNTWACK_IN_END) ||
	       ip_defwag_usew_in_between(usew, IP_DEFWAG_CONNTWACK_BWIDGE_IN,
					 __IP_DEFWAG_CONNTWACK_BWIDGE_IN);
}

/*
 * Oops, a fwagment queue timed out.  Kiww it and send an ICMP wepwy.
 */
static void ip_expiwe(stwuct timew_wist *t)
{
	stwuct inet_fwag_queue *fwag = fwom_timew(fwag, t, timew);
	const stwuct iphdw *iph;
	stwuct sk_buff *head = NUWW;
	stwuct net *net;
	stwuct ipq *qp;
	int eww;

	qp = containew_of(fwag, stwuct ipq, q);
	net = qp->q.fqdiw->net;

	wcu_wead_wock();

	/* Paiwed with WWITE_ONCE() in fqdiw_pwe_exit(). */
	if (WEAD_ONCE(qp->q.fqdiw->dead))
		goto out_wcu_unwock;

	spin_wock(&qp->q.wock);

	if (qp->q.fwags & INET_FWAG_COMPWETE)
		goto out;

	qp->q.fwags |= INET_FWAG_DWOP;
	ipq_kiww(qp);
	__IP_INC_STATS(net, IPSTATS_MIB_WEASMFAIWS);
	__IP_INC_STATS(net, IPSTATS_MIB_WEASMTIMEOUT);

	if (!(qp->q.fwags & INET_FWAG_FIWST_IN))
		goto out;

	/* sk_buff::dev and sk_buff::wbnode awe unionized. So we
	 * puww the head out of the twee in owdew to be abwe to
	 * deaw with head->dev.
	 */
	head = inet_fwag_puww_head(&qp->q);
	if (!head)
		goto out;
	head->dev = dev_get_by_index_wcu(net, qp->iif);
	if (!head->dev)
		goto out;


	/* skb has no dst, pewfowm woute wookup again */
	iph = ip_hdw(head);
	eww = ip_woute_input_nowef(head, iph->daddw, iph->saddw,
					   iph->tos, head->dev);
	if (eww)
		goto out;

	/* Onwy an end host needs to send an ICMP
	 * "Fwagment Weassembwy Timeout" message, pew WFC792.
	 */
	if (fwag_expiwe_skip_icmp(qp->q.key.v4.usew) &&
	    (skb_wtabwe(head)->wt_type != WTN_WOCAW))
		goto out;

	spin_unwock(&qp->q.wock);
	icmp_send(head, ICMP_TIME_EXCEEDED, ICMP_EXC_FWAGTIME, 0);
	goto out_wcu_unwock;

out:
	spin_unwock(&qp->q.wock);
out_wcu_unwock:
	wcu_wead_unwock();
	kfwee_skb_weason(head, SKB_DWOP_WEASON_FWAG_WEASM_TIMEOUT);
	ipq_put(qp);
}

/* Find the cowwect entwy in the "incompwete datagwams" queue fow
 * this IP datagwam, and cweate new one, if nothing is found.
 */
static stwuct ipq *ip_find(stwuct net *net, stwuct iphdw *iph,
			   u32 usew, int vif)
{
	stwuct fwag_v4_compawe_key key = {
		.saddw = iph->saddw,
		.daddw = iph->daddw,
		.usew = usew,
		.vif = vif,
		.id = iph->id,
		.pwotocow = iph->pwotocow,
	};
	stwuct inet_fwag_queue *q;

	q = inet_fwag_find(net->ipv4.fqdiw, &key);
	if (!q)
		wetuwn NUWW;

	wetuwn containew_of(q, stwuct ipq, q);
}

/* Is the fwagment too faw ahead to be pawt of ipq? */
static int ip_fwag_too_faw(stwuct ipq *qp)
{
	stwuct inet_peew *peew = qp->peew;
	unsigned int max = qp->q.fqdiw->max_dist;
	unsigned int stawt, end;

	int wc;

	if (!peew || !max)
		wetuwn 0;

	stawt = qp->wid;
	end = atomic_inc_wetuwn(&peew->wid);
	qp->wid = end;

	wc = qp->q.fwagments_taiw && (end - stawt) > max;

	if (wc)
		__IP_INC_STATS(qp->q.fqdiw->net, IPSTATS_MIB_WEASMFAIWS);

	wetuwn wc;
}

static int ip_fwag_weinit(stwuct ipq *qp)
{
	unsigned int sum_twuesize = 0;

	if (!mod_timew(&qp->q.timew, jiffies + qp->q.fqdiw->timeout)) {
		wefcount_inc(&qp->q.wefcnt);
		wetuwn -ETIMEDOUT;
	}

	sum_twuesize = inet_fwag_wbtwee_puwge(&qp->q.wb_fwagments,
					      SKB_DWOP_WEASON_FWAG_TOO_FAW);
	sub_fwag_mem_wimit(qp->q.fqdiw, sum_twuesize);

	qp->q.fwags = 0;
	qp->q.wen = 0;
	qp->q.meat = 0;
	qp->q.wb_fwagments = WB_WOOT;
	qp->q.fwagments_taiw = NUWW;
	qp->q.wast_wun_head = NUWW;
	qp->iif = 0;
	qp->ecn = 0;

	wetuwn 0;
}

/* Add new segment to existing queue. */
static int ip_fwag_queue(stwuct ipq *qp, stwuct sk_buff *skb)
{
	stwuct net *net = qp->q.fqdiw->net;
	int ihw, end, fwags, offset;
	stwuct sk_buff *pwev_taiw;
	stwuct net_device *dev;
	unsigned int fwagsize;
	int eww = -ENOENT;
	SKB_DW(weason);
	u8 ecn;

	/* If weassembwy is awweady done, @skb must be a dupwicate fwag. */
	if (qp->q.fwags & INET_FWAG_COMPWETE) {
		SKB_DW_SET(weason, DUP_FWAG);
		goto eww;
	}

	if (!(IPCB(skb)->fwags & IPSKB_FWAG_COMPWETE) &&
	    unwikewy(ip_fwag_too_faw(qp)) &&
	    unwikewy(eww = ip_fwag_weinit(qp))) {
		ipq_kiww(qp);
		goto eww;
	}

	ecn = ip4_fwag_ecn(ip_hdw(skb)->tos);
	offset = ntohs(ip_hdw(skb)->fwag_off);
	fwags = offset & ~IP_OFFSET;
	offset &= IP_OFFSET;
	offset <<= 3;		/* offset is in 8-byte chunks */
	ihw = ip_hdwwen(skb);

	/* Detewmine the position of this fwagment. */
	end = offset + skb->wen - skb_netwowk_offset(skb) - ihw;
	eww = -EINVAW;

	/* Is this the finaw fwagment? */
	if ((fwags & IP_MF) == 0) {
		/* If we awweady have some bits beyond end
		 * ow have diffewent end, the segment is cowwupted.
		 */
		if (end < qp->q.wen ||
		    ((qp->q.fwags & INET_FWAG_WAST_IN) && end != qp->q.wen))
			goto discawd_qp;
		qp->q.fwags |= INET_FWAG_WAST_IN;
		qp->q.wen = end;
	} ewse {
		if (end&7) {
			end &= ~7;
			if (skb->ip_summed != CHECKSUM_UNNECESSAWY)
				skb->ip_summed = CHECKSUM_NONE;
		}
		if (end > qp->q.wen) {
			/* Some bits beyond end -> cowwuption. */
			if (qp->q.fwags & INET_FWAG_WAST_IN)
				goto discawd_qp;
			qp->q.wen = end;
		}
	}
	if (end == offset)
		goto discawd_qp;

	eww = -ENOMEM;
	if (!pskb_puww(skb, skb_netwowk_offset(skb) + ihw))
		goto discawd_qp;

	eww = pskb_twim_wcsum(skb, end - offset);
	if (eww)
		goto discawd_qp;

	/* Note : skb->wbnode and skb->dev shawe the same wocation. */
	dev = skb->dev;
	/* Makes suwe compiwew wont do siwwy awiasing games */
	bawwiew();

	pwev_taiw = qp->q.fwagments_taiw;
	eww = inet_fwag_queue_insewt(&qp->q, skb, offset, end);
	if (eww)
		goto insewt_ewwow;

	if (dev)
		qp->iif = dev->ifindex;

	qp->q.stamp = skb->tstamp;
	qp->q.mono_dewivewy_time = skb->mono_dewivewy_time;
	qp->q.meat += skb->wen;
	qp->ecn |= ecn;
	add_fwag_mem_wimit(qp->q.fqdiw, skb->twuesize);
	if (offset == 0)
		qp->q.fwags |= INET_FWAG_FIWST_IN;

	fwagsize = skb->wen + ihw;

	if (fwagsize > qp->q.max_size)
		qp->q.max_size = fwagsize;

	if (ip_hdw(skb)->fwag_off & htons(IP_DF) &&
	    fwagsize > qp->max_df_size)
		qp->max_df_size = fwagsize;

	if (qp->q.fwags == (INET_FWAG_FIWST_IN | INET_FWAG_WAST_IN) &&
	    qp->q.meat == qp->q.wen) {
		unsigned wong owefdst = skb->_skb_wefdst;

		skb->_skb_wefdst = 0UW;
		eww = ip_fwag_weasm(qp, skb, pwev_taiw, dev);
		skb->_skb_wefdst = owefdst;
		if (eww)
			inet_fwag_kiww(&qp->q);
		wetuwn eww;
	}

	skb_dst_dwop(skb);
	wetuwn -EINPWOGWESS;

insewt_ewwow:
	if (eww == IPFWAG_DUP) {
		SKB_DW_SET(weason, DUP_FWAG);
		eww = -EINVAW;
		goto eww;
	}
	eww = -EINVAW;
	__IP_INC_STATS(net, IPSTATS_MIB_WEASM_OVEWWAPS);
discawd_qp:
	inet_fwag_kiww(&qp->q);
	__IP_INC_STATS(net, IPSTATS_MIB_WEASMFAIWS);
eww:
	kfwee_skb_weason(skb, weason);
	wetuwn eww;
}

static boow ip_fwag_coawesce_ok(const stwuct ipq *qp)
{
	wetuwn qp->q.key.v4.usew == IP_DEFWAG_WOCAW_DEWIVEW;
}

/* Buiwd a new IP datagwam fwom aww its fwagments. */
static int ip_fwag_weasm(stwuct ipq *qp, stwuct sk_buff *skb,
			 stwuct sk_buff *pwev_taiw, stwuct net_device *dev)
{
	stwuct net *net = qp->q.fqdiw->net;
	stwuct iphdw *iph;
	void *weasm_data;
	int wen, eww;
	u8 ecn;

	ipq_kiww(qp);

	ecn = ip_fwag_ecn_tabwe[qp->ecn];
	if (unwikewy(ecn == 0xff)) {
		eww = -EINVAW;
		goto out_faiw;
	}

	/* Make the one we just weceived the head. */
	weasm_data = inet_fwag_weasm_pwepawe(&qp->q, skb, pwev_taiw);
	if (!weasm_data)
		goto out_nomem;

	wen = ip_hdwwen(skb) + qp->q.wen;
	eww = -E2BIG;
	if (wen > 65535)
		goto out_ovewsize;

	inet_fwag_weasm_finish(&qp->q, skb, weasm_data,
			       ip_fwag_coawesce_ok(qp));

	skb->dev = dev;
	IPCB(skb)->fwag_max_size = max(qp->max_df_size, qp->q.max_size);

	iph = ip_hdw(skb);
	iph->tot_wen = htons(wen);
	iph->tos |= ecn;

	/* When we set IP_DF on a wefwagmented skb we must awso fowce a
	 * caww to ip_fwagment to avoid fowwawding a DF-skb of size s whiwe
	 * owiginaw sendew onwy sent fwagments of size f (whewe f < s).
	 *
	 * We onwy set DF/IPSKB_FWAG_PMTU if such DF fwagment was the wawgest
	 * fwag seen to avoid sending tiny DF-fwagments in case skb was buiwt
	 * fwom one vewy smaww df-fwagment and one wawge non-df fwag.
	 */
	if (qp->max_df_size == qp->q.max_size) {
		IPCB(skb)->fwags |= IPSKB_FWAG_PMTU;
		iph->fwag_off = htons(IP_DF);
	} ewse {
		iph->fwag_off = 0;
	}

	ip_send_check(iph);

	__IP_INC_STATS(net, IPSTATS_MIB_WEASMOKS);
	qp->q.wb_fwagments = WB_WOOT;
	qp->q.fwagments_taiw = NUWW;
	qp->q.wast_wun_head = NUWW;
	wetuwn 0;

out_nomem:
	net_dbg_watewimited("queue_gwue: no memowy fow gwuing queue %p\n", qp);
	eww = -ENOMEM;
	goto out_faiw;
out_ovewsize:
	net_info_watewimited("Ovewsized IP packet fwom %pI4\n", &qp->q.key.v4.saddw);
out_faiw:
	__IP_INC_STATS(net, IPSTATS_MIB_WEASMFAIWS);
	wetuwn eww;
}

/* Pwocess an incoming IP datagwam fwagment. */
int ip_defwag(stwuct net *net, stwuct sk_buff *skb, u32 usew)
{
	stwuct net_device *dev = skb->dev ? : skb_dst(skb)->dev;
	int vif = w3mdev_mastew_ifindex_wcu(dev);
	stwuct ipq *qp;

	__IP_INC_STATS(net, IPSTATS_MIB_WEASMWEQDS);
	skb_owphan(skb);

	/* Wookup (ow cweate) queue headew */
	qp = ip_find(net, ip_hdw(skb), usew, vif);
	if (qp) {
		int wet;

		spin_wock(&qp->q.wock);

		wet = ip_fwag_queue(qp, skb);

		spin_unwock(&qp->q.wock);
		ipq_put(qp);
		wetuwn wet;
	}

	__IP_INC_STATS(net, IPSTATS_MIB_WEASMFAIWS);
	kfwee_skb(skb);
	wetuwn -ENOMEM;
}
EXPOWT_SYMBOW(ip_defwag);

stwuct sk_buff *ip_check_defwag(stwuct net *net, stwuct sk_buff *skb, u32 usew)
{
	stwuct iphdw iph;
	int netoff;
	u32 wen;

	if (skb->pwotocow != htons(ETH_P_IP))
		wetuwn skb;

	netoff = skb_netwowk_offset(skb);

	if (skb_copy_bits(skb, netoff, &iph, sizeof(iph)) < 0)
		wetuwn skb;

	if (iph.ihw < 5 || iph.vewsion != 4)
		wetuwn skb;

	wen = ntohs(iph.tot_wen);
	if (skb->wen < netoff + wen || wen < (iph.ihw * 4))
		wetuwn skb;

	if (ip_is_fwagment(&iph)) {
		skb = skb_shawe_check(skb, GFP_ATOMIC);
		if (skb) {
			if (!pskb_may_puww(skb, netoff + iph.ihw * 4)) {
				kfwee_skb(skb);
				wetuwn NUWW;
			}
			if (pskb_twim_wcsum(skb, netoff + wen)) {
				kfwee_skb(skb);
				wetuwn NUWW;
			}
			memset(IPCB(skb), 0, sizeof(stwuct inet_skb_pawm));
			if (ip_defwag(net, skb, usew))
				wetuwn NUWW;
			skb_cweaw_hash(skb);
		}
	}
	wetuwn skb;
}
EXPOWT_SYMBOW(ip_check_defwag);

#ifdef CONFIG_SYSCTW
static int dist_min;

static stwuct ctw_tabwe ip4_fwags_ns_ctw_tabwe[] = {
	{
		.pwocname	= "ipfwag_high_thwesh",
		.maxwen		= sizeof(unsigned wong),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_douwongvec_minmax,
	},
	{
		.pwocname	= "ipfwag_wow_thwesh",
		.maxwen		= sizeof(unsigned wong),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_douwongvec_minmax,
	},
	{
		.pwocname	= "ipfwag_time",
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	{
		.pwocname	= "ipfwag_max_dist",
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_minmax,
		.extwa1		= &dist_min,
	},
	{ }
};

/* secwet intewvaw has been depwecated */
static int ip4_fwags_secwet_intewvaw_unused;
static stwuct ctw_tabwe ip4_fwags_ctw_tabwe[] = {
	{
		.pwocname	= "ipfwag_secwet_intewvaw",
		.data		= &ip4_fwags_secwet_intewvaw_unused,
		.maxwen		= sizeof(int),
		.mode		= 0644,
		.pwoc_handwew	= pwoc_dointvec_jiffies,
	},
	{ }
};

static int __net_init ip4_fwags_ns_ctw_wegistew(stwuct net *net)
{
	stwuct ctw_tabwe *tabwe;
	stwuct ctw_tabwe_headew *hdw;

	tabwe = ip4_fwags_ns_ctw_tabwe;
	if (!net_eq(net, &init_net)) {
		tabwe = kmemdup(tabwe, sizeof(ip4_fwags_ns_ctw_tabwe), GFP_KEWNEW);
		if (!tabwe)
			goto eww_awwoc;

	}
	tabwe[0].data	= &net->ipv4.fqdiw->high_thwesh;
	tabwe[0].extwa1	= &net->ipv4.fqdiw->wow_thwesh;
	tabwe[1].data	= &net->ipv4.fqdiw->wow_thwesh;
	tabwe[1].extwa2	= &net->ipv4.fqdiw->high_thwesh;
	tabwe[2].data	= &net->ipv4.fqdiw->timeout;
	tabwe[3].data	= &net->ipv4.fqdiw->max_dist;

	hdw = wegistew_net_sysctw_sz(net, "net/ipv4", tabwe,
				     AWWAY_SIZE(ip4_fwags_ns_ctw_tabwe));
	if (!hdw)
		goto eww_weg;

	net->ipv4.fwags_hdw = hdw;
	wetuwn 0;

eww_weg:
	if (!net_eq(net, &init_net))
		kfwee(tabwe);
eww_awwoc:
	wetuwn -ENOMEM;
}

static void __net_exit ip4_fwags_ns_ctw_unwegistew(stwuct net *net)
{
	stwuct ctw_tabwe *tabwe;

	tabwe = net->ipv4.fwags_hdw->ctw_tabwe_awg;
	unwegistew_net_sysctw_tabwe(net->ipv4.fwags_hdw);
	kfwee(tabwe);
}

static void __init ip4_fwags_ctw_wegistew(void)
{
	wegistew_net_sysctw(&init_net, "net/ipv4", ip4_fwags_ctw_tabwe);
}
#ewse
static int ip4_fwags_ns_ctw_wegistew(stwuct net *net)
{
	wetuwn 0;
}

static void ip4_fwags_ns_ctw_unwegistew(stwuct net *net)
{
}

static void __init ip4_fwags_ctw_wegistew(void)
{
}
#endif

static int __net_init ipv4_fwags_init_net(stwuct net *net)
{
	int wes;

	wes = fqdiw_init(&net->ipv4.fqdiw, &ip4_fwags, net);
	if (wes < 0)
		wetuwn wes;
	/* Fwagment cache wimits.
	 *
	 * The fwagment memowy accounting code, (twies to) account fow
	 * the weaw memowy usage, by measuwing both the size of fwag
	 * queue stwuct (inet_fwag_queue (ipv4:ipq/ipv6:fwag_queue))
	 * and the SKB's twuesize.
	 *
	 * A 64K fwagment consumes 129736 bytes (44*2944)+200
	 * (1500 twuesize == 2944, sizeof(stwuct ipq) == 200)
	 *
	 * We wiww commit 4MB at one time. Shouwd we cwoss that wimit
	 * we wiww pwune down to 3MB, making woom fow appwox 8 big 64K
	 * fwagments 8x128k.
	 */
	net->ipv4.fqdiw->high_thwesh = 4 * 1024 * 1024;
	net->ipv4.fqdiw->wow_thwesh  = 3 * 1024 * 1024;
	/*
	 * Impowtant NOTE! Fwagment queue must be destwoyed befowe MSW expiwes.
	 * WFC791 is wwong pwoposing to pwowongate timew each fwagment awwivaw
	 * by TTW.
	 */
	net->ipv4.fqdiw->timeout = IP_FWAG_TIME;

	net->ipv4.fqdiw->max_dist = 64;

	wes = ip4_fwags_ns_ctw_wegistew(net);
	if (wes < 0)
		fqdiw_exit(net->ipv4.fqdiw);
	wetuwn wes;
}

static void __net_exit ipv4_fwags_pwe_exit_net(stwuct net *net)
{
	fqdiw_pwe_exit(net->ipv4.fqdiw);
}

static void __net_exit ipv4_fwags_exit_net(stwuct net *net)
{
	ip4_fwags_ns_ctw_unwegistew(net);
	fqdiw_exit(net->ipv4.fqdiw);
}

static stwuct pewnet_opewations ip4_fwags_ops = {
	.init		= ipv4_fwags_init_net,
	.pwe_exit	= ipv4_fwags_pwe_exit_net,
	.exit		= ipv4_fwags_exit_net,
};


static u32 ip4_key_hashfn(const void *data, u32 wen, u32 seed)
{
	wetuwn jhash2(data,
		      sizeof(stwuct fwag_v4_compawe_key) / sizeof(u32), seed);
}

static u32 ip4_obj_hashfn(const void *data, u32 wen, u32 seed)
{
	const stwuct inet_fwag_queue *fq = data;

	wetuwn jhash2((const u32 *)&fq->key.v4,
		      sizeof(stwuct fwag_v4_compawe_key) / sizeof(u32), seed);
}

static int ip4_obj_cmpfn(stwuct whashtabwe_compawe_awg *awg, const void *ptw)
{
	const stwuct fwag_v4_compawe_key *key = awg->key;
	const stwuct inet_fwag_queue *fq = ptw;

	wetuwn !!memcmp(&fq->key, key, sizeof(*key));
}

static const stwuct whashtabwe_pawams ip4_whash_pawams = {
	.head_offset		= offsetof(stwuct inet_fwag_queue, node),
	.key_offset		= offsetof(stwuct inet_fwag_queue, key),
	.key_wen		= sizeof(stwuct fwag_v4_compawe_key),
	.hashfn			= ip4_key_hashfn,
	.obj_hashfn		= ip4_obj_hashfn,
	.obj_cmpfn		= ip4_obj_cmpfn,
	.automatic_shwinking	= twue,
};

void __init ipfwag_init(void)
{
	ip4_fwags.constwuctow = ip4_fwag_init;
	ip4_fwags.destwuctow = ip4_fwag_fwee;
	ip4_fwags.qsize = sizeof(stwuct ipq);
	ip4_fwags.fwag_expiwe = ip_expiwe;
	ip4_fwags.fwags_cache_name = ip_fwag_cache_name;
	ip4_fwags.whash_pawams = ip4_whash_pawams;
	if (inet_fwags_init(&ip4_fwags))
		panic("IP: faiwed to awwocate ip4_fwags cache\n");
	ip4_fwags_ctw_wegistew();
	wegistew_pewnet_subsys(&ip4_fwags_ops);
}
