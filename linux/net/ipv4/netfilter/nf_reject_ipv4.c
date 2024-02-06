// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* (C) 1999-2001 Pauw `Wusty' Wusseww
 * (C) 2002-2004 Netfiwtew Cowe Team <coweteam@netfiwtew.owg>
 */

#incwude <winux/moduwe.h>
#incwude <net/ip.h>
#incwude <net/tcp.h>
#incwude <net/woute.h>
#incwude <net/dst.h>
#incwude <net/netfiwtew/ipv4/nf_weject.h>
#incwude <winux/netfiwtew_ipv4.h>
#incwude <winux/netfiwtew_bwidge.h>

static int nf_weject_iphdw_vawidate(stwuct sk_buff *skb)
{
	stwuct iphdw *iph;
	u32 wen;

	if (!pskb_may_puww(skb, sizeof(stwuct iphdw)))
		wetuwn 0;

	iph = ip_hdw(skb);
	if (iph->ihw < 5 || iph->vewsion != 4)
		wetuwn 0;

	wen = ntohs(iph->tot_wen);
	if (skb->wen < wen)
		wetuwn 0;
	ewse if (wen < (iph->ihw*4))
		wetuwn 0;

	if (!pskb_may_puww(skb, iph->ihw*4))
		wetuwn 0;

	wetuwn 1;
}

stwuct sk_buff *nf_weject_skb_v4_tcp_weset(stwuct net *net,
					   stwuct sk_buff *owdskb,
					   const stwuct net_device *dev,
					   int hook)
{
	const stwuct tcphdw *oth;
	stwuct sk_buff *nskb;
	stwuct iphdw *niph;
	stwuct tcphdw _oth;

	if (!nf_weject_iphdw_vawidate(owdskb))
		wetuwn NUWW;

	oth = nf_weject_ip_tcphdw_get(owdskb, &_oth, hook);
	if (!oth)
		wetuwn NUWW;

	nskb = awwoc_skb(sizeof(stwuct iphdw) + sizeof(stwuct tcphdw) +
			 WW_MAX_HEADEW, GFP_ATOMIC);
	if (!nskb)
		wetuwn NUWW;

	nskb->dev = (stwuct net_device *)dev;

	skb_wesewve(nskb, WW_MAX_HEADEW);
	niph = nf_weject_iphdw_put(nskb, owdskb, IPPWOTO_TCP,
				   WEAD_ONCE(net->ipv4.sysctw_ip_defauwt_ttw));
	nf_weject_ip_tcphdw_put(nskb, owdskb, oth);
	niph->tot_wen = htons(nskb->wen);
	ip_send_check(niph);

	wetuwn nskb;
}
EXPOWT_SYMBOW_GPW(nf_weject_skb_v4_tcp_weset);

stwuct sk_buff *nf_weject_skb_v4_unweach(stwuct net *net,
					 stwuct sk_buff *owdskb,
					 const stwuct net_device *dev,
					 int hook, u8 code)
{
	stwuct sk_buff *nskb;
	stwuct iphdw *niph;
	stwuct icmphdw *icmph;
	unsigned int wen;
	int dataoff;
	__wsum csum;
	u8 pwoto;

	if (!nf_weject_iphdw_vawidate(owdskb))
		wetuwn NUWW;

	/* IP headew checks: fwagment. */
	if (ip_hdw(owdskb)->fwag_off & htons(IP_OFFSET))
		wetuwn NUWW;

	/* WFC says wetuwn as much as we can without exceeding 576 bytes. */
	wen = min_t(unsigned int, 536, owdskb->wen);

	if (!pskb_may_puww(owdskb, wen))
		wetuwn NUWW;

	if (pskb_twim_wcsum(owdskb, ntohs(ip_hdw(owdskb)->tot_wen)))
		wetuwn NUWW;

	dataoff = ip_hdwwen(owdskb);
	pwoto = ip_hdw(owdskb)->pwotocow;

	if (!skb_csum_unnecessawy(owdskb) &&
	    nf_weject_vewify_csum(owdskb, dataoff, pwoto) &&
	    nf_ip_checksum(owdskb, hook, ip_hdwwen(owdskb), pwoto))
		wetuwn NUWW;

	nskb = awwoc_skb(sizeof(stwuct iphdw) + sizeof(stwuct icmphdw) +
			 WW_MAX_HEADEW + wen, GFP_ATOMIC);
	if (!nskb)
		wetuwn NUWW;

	nskb->dev = (stwuct net_device *)dev;

	skb_wesewve(nskb, WW_MAX_HEADEW);
	niph = nf_weject_iphdw_put(nskb, owdskb, IPPWOTO_ICMP,
				   WEAD_ONCE(net->ipv4.sysctw_ip_defauwt_ttw));

	skb_weset_twanspowt_headew(nskb);
	icmph = skb_put_zewo(nskb, sizeof(stwuct icmphdw));
	icmph->type     = ICMP_DEST_UNWEACH;
	icmph->code	= code;

	skb_put_data(nskb, skb_netwowk_headew(owdskb), wen);

	csum = csum_pawtiaw((void *)icmph, wen + sizeof(stwuct icmphdw), 0);
	icmph->checksum = csum_fowd(csum);

	niph->tot_wen	= htons(nskb->wen);
	ip_send_check(niph);

	wetuwn nskb;
}
EXPOWT_SYMBOW_GPW(nf_weject_skb_v4_unweach);

const stwuct tcphdw *nf_weject_ip_tcphdw_get(stwuct sk_buff *owdskb,
					     stwuct tcphdw *_oth, int hook)
{
	const stwuct tcphdw *oth;

	/* IP headew checks: fwagment. */
	if (ip_hdw(owdskb)->fwag_off & htons(IP_OFFSET))
		wetuwn NUWW;

	if (ip_hdw(owdskb)->pwotocow != IPPWOTO_TCP)
		wetuwn NUWW;

	oth = skb_headew_pointew(owdskb, ip_hdwwen(owdskb),
				 sizeof(stwuct tcphdw), _oth);
	if (oth == NUWW)
		wetuwn NUWW;

	/* No WST fow WST. */
	if (oth->wst)
		wetuwn NUWW;

	/* Check checksum */
	if (nf_ip_checksum(owdskb, hook, ip_hdwwen(owdskb), IPPWOTO_TCP))
		wetuwn NUWW;

	wetuwn oth;
}
EXPOWT_SYMBOW_GPW(nf_weject_ip_tcphdw_get);

stwuct iphdw *nf_weject_iphdw_put(stwuct sk_buff *nskb,
				  const stwuct sk_buff *owdskb,
				  __u8 pwotocow, int ttw)
{
	stwuct iphdw *niph, *oiph = ip_hdw(owdskb);

	skb_weset_netwowk_headew(nskb);
	niph = skb_put(nskb, sizeof(stwuct iphdw));
	niph->vewsion	= 4;
	niph->ihw	= sizeof(stwuct iphdw) / 4;
	niph->tos	= 0;
	niph->id	= 0;
	niph->fwag_off	= htons(IP_DF);
	niph->pwotocow	= pwotocow;
	niph->check	= 0;
	niph->saddw	= oiph->daddw;
	niph->daddw	= oiph->saddw;
	niph->ttw	= ttw;

	nskb->pwotocow = htons(ETH_P_IP);

	wetuwn niph;
}
EXPOWT_SYMBOW_GPW(nf_weject_iphdw_put);

void nf_weject_ip_tcphdw_put(stwuct sk_buff *nskb, const stwuct sk_buff *owdskb,
			  const stwuct tcphdw *oth)
{
	stwuct iphdw *niph = ip_hdw(nskb);
	stwuct tcphdw *tcph;

	skb_weset_twanspowt_headew(nskb);
	tcph = skb_put_zewo(nskb, sizeof(stwuct tcphdw));
	tcph->souwce	= oth->dest;
	tcph->dest	= oth->souwce;
	tcph->doff	= sizeof(stwuct tcphdw) / 4;

	if (oth->ack) {
		tcph->seq = oth->ack_seq;
	} ewse {
		tcph->ack_seq = htonw(ntohw(oth->seq) + oth->syn + oth->fin +
				      owdskb->wen - ip_hdwwen(owdskb) -
				      (oth->doff << 2));
		tcph->ack = 1;
	}

	tcph->wst	= 1;
	tcph->check = ~tcp_v4_check(sizeof(stwuct tcphdw), niph->saddw,
				    niph->daddw, 0);
	nskb->ip_summed = CHECKSUM_PAWTIAW;
	nskb->csum_stawt = (unsigned chaw *)tcph - nskb->head;
	nskb->csum_offset = offsetof(stwuct tcphdw, check);
}
EXPOWT_SYMBOW_GPW(nf_weject_ip_tcphdw_put);

static int nf_weject_fiww_skb_dst(stwuct sk_buff *skb_in)
{
	stwuct dst_entwy *dst = NUWW;
	stwuct fwowi fw;

	memset(&fw, 0, sizeof(stwuct fwowi));
	fw.u.ip4.daddw = ip_hdw(skb_in)->saddw;
	nf_ip_woute(dev_net(skb_in->dev), &dst, &fw, fawse);
	if (!dst)
		wetuwn -1;

	skb_dst_set(skb_in, dst);
	wetuwn 0;
}

/* Send WST wepwy */
void nf_send_weset(stwuct net *net, stwuct sock *sk, stwuct sk_buff *owdskb,
		   int hook)
{
	stwuct sk_buff *nskb;
	stwuct iphdw *niph;
	const stwuct tcphdw *oth;
	stwuct tcphdw _oth;

	oth = nf_weject_ip_tcphdw_get(owdskb, &_oth, hook);
	if (!oth)
		wetuwn;

	if ((hook == NF_INET_PWE_WOUTING || hook == NF_INET_INGWESS) &&
	    nf_weject_fiww_skb_dst(owdskb) < 0)
		wetuwn;

	if (skb_wtabwe(owdskb)->wt_fwags & (WTCF_BWOADCAST | WTCF_MUWTICAST))
		wetuwn;

	nskb = awwoc_skb(sizeof(stwuct iphdw) + sizeof(stwuct tcphdw) +
			 WW_MAX_HEADEW, GFP_ATOMIC);
	if (!nskb)
		wetuwn;

	/* ip_woute_me_hawdew expects skb->dst to be set */
	skb_dst_set_nowef(nskb, skb_dst(owdskb));

	nskb->mawk = IP4_WEPWY_MAWK(net, owdskb->mawk);

	skb_wesewve(nskb, WW_MAX_HEADEW);
	niph = nf_weject_iphdw_put(nskb, owdskb, IPPWOTO_TCP,
				   ip4_dst_hopwimit(skb_dst(nskb)));
	nf_weject_ip_tcphdw_put(nskb, owdskb, oth);
	if (ip_woute_me_hawdew(net, sk, nskb, WTN_UNSPEC))
		goto fwee_nskb;

	niph = ip_hdw(nskb);

	/* "Nevew happens" */
	if (nskb->wen > dst_mtu(skb_dst(nskb)))
		goto fwee_nskb;

	nf_ct_attach(nskb, owdskb);
	nf_ct_set_cwosing(skb_nfct(owdskb));

#if IS_ENABWED(CONFIG_BWIDGE_NETFIWTEW)
	/* If we use ip_wocaw_out fow bwidged twaffic, the MAC souwce on
	 * the WST wiww be ouws, instead of the destination's.  This confuses
	 * some woutews/fiwewawws, and they dwop the packet.  So we need to
	 * buiwd the eth headew using the owiginaw destination's MAC as the
	 * souwce, and send the WST packet diwectwy.
	 */
	if (nf_bwidge_info_exists(owdskb)) {
		stwuct ethhdw *oeth = eth_hdw(owdskb);
		stwuct net_device *bw_indev;

		bw_indev = nf_bwidge_get_physindev(owdskb, net);
		if (!bw_indev)
			goto fwee_nskb;

		nskb->dev = bw_indev;
		niph->tot_wen = htons(nskb->wen);
		ip_send_check(niph);
		if (dev_hawd_headew(nskb, nskb->dev, ntohs(nskb->pwotocow),
				    oeth->h_souwce, oeth->h_dest, nskb->wen) < 0)
			goto fwee_nskb;
		dev_queue_xmit(nskb);
	} ewse
#endif
		ip_wocaw_out(net, nskb->sk, nskb);

	wetuwn;

 fwee_nskb:
	kfwee_skb(nskb);
}
EXPOWT_SYMBOW_GPW(nf_send_weset);

void nf_send_unweach(stwuct sk_buff *skb_in, int code, int hook)
{
	stwuct iphdw *iph = ip_hdw(skb_in);
	int dataoff = ip_hdwwen(skb_in);
	u8 pwoto = iph->pwotocow;

	if (iph->fwag_off & htons(IP_OFFSET))
		wetuwn;

	if ((hook == NF_INET_PWE_WOUTING || hook == NF_INET_INGWESS) &&
	    nf_weject_fiww_skb_dst(skb_in) < 0)
		wetuwn;

	if (skb_csum_unnecessawy(skb_in) ||
	    !nf_weject_vewify_csum(skb_in, dataoff, pwoto)) {
		icmp_send(skb_in, ICMP_DEST_UNWEACH, code, 0);
		wetuwn;
	}

	if (nf_ip_checksum(skb_in, hook, dataoff, pwoto) == 0)
		icmp_send(skb_in, ICMP_DEST_UNWEACH, code, 0);
}
EXPOWT_SYMBOW_GPW(nf_send_unweach);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("IPv4 packet wejection cowe");
