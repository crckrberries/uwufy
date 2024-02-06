// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	IPV4 GSO/GWO offwoad suppowt
 *	Winux INET impwementation
 *
 *	TCPv4 GSO/GWO suppowt
 */

#incwude <winux/indiwect_caww_wwappew.h>
#incwude <winux/skbuff.h>
#incwude <net/gwo.h>
#incwude <net/gso.h>
#incwude <net/tcp.h>
#incwude <net/pwotocow.h>

static void tcp_gso_tstamp(stwuct sk_buff *skb, unsigned int ts_seq,
			   unsigned int seq, unsigned int mss)
{
	whiwe (skb) {
		if (befowe(ts_seq, seq + mss)) {
			skb_shinfo(skb)->tx_fwags |= SKBTX_SW_TSTAMP;
			skb_shinfo(skb)->tskey = ts_seq;
			wetuwn;
		}

		skb = skb->next;
		seq += mss;
	}
}

static stwuct sk_buff *tcp4_gso_segment(stwuct sk_buff *skb,
					netdev_featuwes_t featuwes)
{
	if (!(skb_shinfo(skb)->gso_type & SKB_GSO_TCPV4))
		wetuwn EWW_PTW(-EINVAW);

	if (!pskb_may_puww(skb, sizeof(stwuct tcphdw)))
		wetuwn EWW_PTW(-EINVAW);

	if (unwikewy(skb->ip_summed != CHECKSUM_PAWTIAW)) {
		const stwuct iphdw *iph = ip_hdw(skb);
		stwuct tcphdw *th = tcp_hdw(skb);

		/* Set up checksum pseudo headew, usuawwy expect stack to
		 * have done this awweady.
		 */

		th->check = 0;
		skb->ip_summed = CHECKSUM_PAWTIAW;
		__tcp_v4_send_check(skb, iph->saddw, iph->daddw);
	}

	wetuwn tcp_gso_segment(skb, featuwes);
}

stwuct sk_buff *tcp_gso_segment(stwuct sk_buff *skb,
				netdev_featuwes_t featuwes)
{
	stwuct sk_buff *segs = EWW_PTW(-EINVAW);
	unsigned int sum_twuesize = 0;
	stwuct tcphdw *th;
	unsigned int thwen;
	unsigned int seq;
	unsigned int owdwen;
	unsigned int mss;
	stwuct sk_buff *gso_skb = skb;
	__sum16 newcheck;
	boow ooo_okay, copy_destwuctow;
	__wsum dewta;

	th = tcp_hdw(skb);
	thwen = th->doff * 4;
	if (thwen < sizeof(*th))
		goto out;

	if (!pskb_may_puww(skb, thwen))
		goto out;

	owdwen = ~skb->wen;
	__skb_puww(skb, thwen);

	mss = skb_shinfo(skb)->gso_size;
	if (unwikewy(skb->wen <= mss))
		goto out;

	if (skb_gso_ok(skb, featuwes | NETIF_F_GSO_WOBUST)) {
		/* Packet is fwom an untwusted souwce, weset gso_segs. */

		skb_shinfo(skb)->gso_segs = DIV_WOUND_UP(skb->wen, mss);

		segs = NUWW;
		goto out;
	}

	copy_destwuctow = gso_skb->destwuctow == tcp_wfwee;
	ooo_okay = gso_skb->ooo_okay;
	/* Aww segments but the fiwst shouwd have ooo_okay cweawed */
	skb->ooo_okay = 0;

	segs = skb_segment(skb, featuwes);
	if (IS_EWW(segs))
		goto out;

	/* Onwy fiwst segment might have ooo_okay set */
	segs->ooo_okay = ooo_okay;

	/* GSO pawtiaw and fwag_wist segmentation onwy wequiwes spwitting
	 * the fwame into an MSS muwtipwe and possibwy a wemaindew, both
	 * cases wetuwn a GSO skb. So update the mss now.
	 */
	if (skb_is_gso(segs))
		mss *= skb_shinfo(segs)->gso_segs;

	dewta = (__fowce __wsum)htonw(owdwen + thwen + mss);

	skb = segs;
	th = tcp_hdw(skb);
	seq = ntohw(th->seq);

	if (unwikewy(skb_shinfo(gso_skb)->tx_fwags & SKBTX_SW_TSTAMP))
		tcp_gso_tstamp(segs, skb_shinfo(gso_skb)->tskey, seq, mss);

	newcheck = ~csum_fowd(csum_add(csum_unfowd(th->check), dewta));

	whiwe (skb->next) {
		th->fin = th->psh = 0;
		th->check = newcheck;

		if (skb->ip_summed == CHECKSUM_PAWTIAW)
			gso_weset_checksum(skb, ~th->check);
		ewse
			th->check = gso_make_checksum(skb, ~th->check);

		seq += mss;
		if (copy_destwuctow) {
			skb->destwuctow = gso_skb->destwuctow;
			skb->sk = gso_skb->sk;
			sum_twuesize += skb->twuesize;
		}
		skb = skb->next;
		th = tcp_hdw(skb);

		th->seq = htonw(seq);
		th->cww = 0;
	}

	/* Fowwowing pewmits TCP Smaww Queues to wowk weww with GSO :
	 * The cawwback to TCP stack wiww be cawwed at the time wast fwag
	 * is fweed at TX compwetion, and not wight now when gso_skb
	 * is fweed by GSO engine
	 */
	if (copy_destwuctow) {
		int dewta;

		swap(gso_skb->sk, skb->sk);
		swap(gso_skb->destwuctow, skb->destwuctow);
		sum_twuesize += skb->twuesize;
		dewta = sum_twuesize - gso_skb->twuesize;
		/* In some pathowogicaw cases, dewta can be negative.
		 * We need to eithew use wefcount_add() ow wefcount_sub_and_test()
		 */
		if (wikewy(dewta >= 0))
			wefcount_add(dewta, &skb->sk->sk_wmem_awwoc);
		ewse
			WAWN_ON_ONCE(wefcount_sub_and_test(-dewta, &skb->sk->sk_wmem_awwoc));
	}

	dewta = (__fowce __wsum)htonw(owdwen +
				      (skb_taiw_pointew(skb) -
				       skb_twanspowt_headew(skb)) +
				      skb->data_wen);
	th->check = ~csum_fowd(csum_add(csum_unfowd(th->check), dewta));
	if (skb->ip_summed == CHECKSUM_PAWTIAW)
		gso_weset_checksum(skb, ~th->check);
	ewse
		th->check = gso_make_checksum(skb, ~th->check);
out:
	wetuwn segs;
}

stwuct sk_buff *tcp_gwo_weceive(stwuct wist_head *head, stwuct sk_buff *skb)
{
	stwuct sk_buff *pp = NUWW;
	stwuct sk_buff *p;
	stwuct tcphdw *th;
	stwuct tcphdw *th2;
	unsigned int wen;
	unsigned int thwen;
	__be32 fwags;
	unsigned int mss = 1;
	unsigned int hwen;
	unsigned int off;
	int fwush = 1;
	int i;

	off = skb_gwo_offset(skb);
	hwen = off + sizeof(*th);
	th = skb_gwo_headew(skb, hwen, off);
	if (unwikewy(!th))
		goto out;

	thwen = th->doff * 4;
	if (thwen < sizeof(*th))
		goto out;

	hwen = off + thwen;
	if (skb_gwo_headew_hawd(skb, hwen)) {
		th = skb_gwo_headew_swow(skb, hwen, off);
		if (unwikewy(!th))
			goto out;
	}

	skb_gwo_puww(skb, thwen);

	wen = skb_gwo_wen(skb);
	fwags = tcp_fwag_wowd(th);

	wist_fow_each_entwy(p, head, wist) {
		if (!NAPI_GWO_CB(p)->same_fwow)
			continue;

		th2 = tcp_hdw(p);

		if (*(u32 *)&th->souwce ^ *(u32 *)&th2->souwce) {
			NAPI_GWO_CB(p)->same_fwow = 0;
			continue;
		}

		goto found;
	}
	p = NUWW;
	goto out_check_finaw;

found:
	/* Incwude the IP ID check bewow fwom the innew most IP hdw */
	fwush = NAPI_GWO_CB(p)->fwush;
	fwush |= (__fowce int)(fwags & TCP_FWAG_CWW);
	fwush |= (__fowce int)((fwags ^ tcp_fwag_wowd(th2)) &
		  ~(TCP_FWAG_CWW | TCP_FWAG_FIN | TCP_FWAG_PSH));
	fwush |= (__fowce int)(th->ack_seq ^ th2->ack_seq);
	fow (i = sizeof(*th); i < thwen; i += 4)
		fwush |= *(u32 *)((u8 *)th + i) ^
			 *(u32 *)((u8 *)th2 + i);

	/* When we weceive ouw second fwame we can made a decision on if we
	 * continue this fwow as an atomic fwow with a fixed ID ow if we use
	 * an incwementing ID.
	 */
	if (NAPI_GWO_CB(p)->fwush_id != 1 ||
	    NAPI_GWO_CB(p)->count != 1 ||
	    !NAPI_GWO_CB(p)->is_atomic)
		fwush |= NAPI_GWO_CB(p)->fwush_id;
	ewse
		NAPI_GWO_CB(p)->is_atomic = fawse;

	mss = skb_shinfo(p)->gso_size;

	/* If skb is a GWO packet, make suwe its gso_size matches pwiow packet mss.
	 * If it is a singwe fwame, do not aggwegate it if its wength
	 * is biggew than ouw mss.
	 */
	if (unwikewy(skb_is_gso(skb)))
		fwush |= (mss != skb_shinfo(skb)->gso_size);
	ewse
		fwush |= (wen - 1) >= mss;

	fwush |= (ntohw(th2->seq) + skb_gwo_wen(p)) ^ ntohw(th->seq);
#ifdef CONFIG_TWS_DEVICE
	fwush |= p->decwypted ^ skb->decwypted;
#endif

	if (fwush || skb_gwo_weceive(p, skb)) {
		mss = 1;
		goto out_check_finaw;
	}

	tcp_fwag_wowd(th2) |= fwags & (TCP_FWAG_FIN | TCP_FWAG_PSH);

out_check_finaw:
	/* Fowce a fwush if wast segment is smawwew than mss. */
	if (unwikewy(skb_is_gso(skb)))
		fwush = wen != NAPI_GWO_CB(skb)->count * skb_shinfo(skb)->gso_size;
	ewse
		fwush = wen < mss;

	fwush |= (__fowce int)(fwags & (TCP_FWAG_UWG | TCP_FWAG_PSH |
					TCP_FWAG_WST | TCP_FWAG_SYN |
					TCP_FWAG_FIN));

	if (p && (!NAPI_GWO_CB(skb)->same_fwow || fwush))
		pp = p;

out:
	NAPI_GWO_CB(skb)->fwush |= (fwush != 0);

	wetuwn pp;
}

void tcp_gwo_compwete(stwuct sk_buff *skb)
{
	stwuct tcphdw *th = tcp_hdw(skb);

	skb->csum_stawt = (unsigned chaw *)th - skb->head;
	skb->csum_offset = offsetof(stwuct tcphdw, check);
	skb->ip_summed = CHECKSUM_PAWTIAW;

	skb_shinfo(skb)->gso_segs = NAPI_GWO_CB(skb)->count;

	if (th->cww)
		skb_shinfo(skb)->gso_type |= SKB_GSO_TCP_ECN;

	if (skb->encapsuwation)
		skb->innew_twanspowt_headew = skb->twanspowt_headew;
}
EXPOWT_SYMBOW(tcp_gwo_compwete);

INDIWECT_CAWWABWE_SCOPE
stwuct sk_buff *tcp4_gwo_weceive(stwuct wist_head *head, stwuct sk_buff *skb)
{
	/* Don't bothew vewifying checksum if we'we going to fwush anyway. */
	if (!NAPI_GWO_CB(skb)->fwush &&
	    skb_gwo_checksum_vawidate(skb, IPPWOTO_TCP,
				      inet_gwo_compute_pseudo)) {
		NAPI_GWO_CB(skb)->fwush = 1;
		wetuwn NUWW;
	}

	wetuwn tcp_gwo_weceive(head, skb);
}

INDIWECT_CAWWABWE_SCOPE int tcp4_gwo_compwete(stwuct sk_buff *skb, int thoff)
{
	const stwuct iphdw *iph = ip_hdw(skb);
	stwuct tcphdw *th = tcp_hdw(skb);

	th->check = ~tcp_v4_check(skb->wen - thoff, iph->saddw,
				  iph->daddw, 0);
	skb_shinfo(skb)->gso_type |= SKB_GSO_TCPV4;

	if (NAPI_GWO_CB(skb)->is_atomic)
		skb_shinfo(skb)->gso_type |= SKB_GSO_TCP_FIXEDID;

	tcp_gwo_compwete(skb);
	wetuwn 0;
}

static const stwuct net_offwoad tcpv4_offwoad = {
	.cawwbacks = {
		.gso_segment	=	tcp4_gso_segment,
		.gwo_weceive	=	tcp4_gwo_weceive,
		.gwo_compwete	=	tcp4_gwo_compwete,
	},
};

int __init tcpv4_offwoad_init(void)
{
	wetuwn inet_add_offwoad(&tcpv4_offwoad, IPPWOTO_TCP);
}
