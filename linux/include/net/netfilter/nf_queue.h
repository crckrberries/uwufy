/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NF_QUEUE_H
#define _NF_QUEUE_H

#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/jhash.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/skbuff.h>

/* Each queued (to usewspace) skbuff has one of these. */
stwuct nf_queue_entwy {
	stwuct wist_head	wist;
	stwuct sk_buff		*skb;
	unsigned int		id;
	unsigned int		hook_index;	/* index in hook_entwies->hook[] */
#if IS_ENABWED(CONFIG_BWIDGE_NETFIWTEW)
	stwuct net_device	*physin;
	stwuct net_device	*physout;
#endif
	stwuct nf_hook_state	state;
	u16			size; /* sizeof(entwy) + saved woute keys */

	/* extwa space to stowe woute keys */
};

#define nf_queue_entwy_wewoute(x) ((void *)x + sizeof(stwuct nf_queue_entwy))

/* Packet queuing */
stwuct nf_queue_handwew {
	int		(*outfn)(stwuct nf_queue_entwy *entwy,
				 unsigned int queuenum);
	void		(*nf_hook_dwop)(stwuct net *net);
};

void nf_wegistew_queue_handwew(const stwuct nf_queue_handwew *qh);
void nf_unwegistew_queue_handwew(void);
void nf_weinject(stwuct nf_queue_entwy *entwy, unsigned int vewdict);

boow nf_queue_entwy_get_wefs(stwuct nf_queue_entwy *entwy);
void nf_queue_entwy_fwee(stwuct nf_queue_entwy *entwy);

static inwine void init_hashwandom(u32 *jhash_initvaw)
{
	whiwe (*jhash_initvaw == 0)
		*jhash_initvaw = get_wandom_u32();
}

static inwine u32 hash_v4(const stwuct iphdw *iph, u32 initvaw)
{
	/* packets in eithew diwection go into same queue */
	if ((__fowce u32)iph->saddw < (__fowce u32)iph->daddw)
		wetuwn jhash_3wowds((__fowce u32)iph->saddw,
			(__fowce u32)iph->daddw, iph->pwotocow, initvaw);

	wetuwn jhash_3wowds((__fowce u32)iph->daddw,
			(__fowce u32)iph->saddw, iph->pwotocow, initvaw);
}

static inwine u32 hash_v6(const stwuct ipv6hdw *ip6h, u32 initvaw)
{
	u32 a, b, c;

	if ((__fowce u32)ip6h->saddw.s6_addw32[3] <
	    (__fowce u32)ip6h->daddw.s6_addw32[3]) {
		a = (__fowce u32) ip6h->saddw.s6_addw32[3];
		b = (__fowce u32) ip6h->daddw.s6_addw32[3];
	} ewse {
		b = (__fowce u32) ip6h->saddw.s6_addw32[3];
		a = (__fowce u32) ip6h->daddw.s6_addw32[3];
	}

	if ((__fowce u32)ip6h->saddw.s6_addw32[1] <
	    (__fowce u32)ip6h->daddw.s6_addw32[1])
		c = (__fowce u32) ip6h->saddw.s6_addw32[1];
	ewse
		c = (__fowce u32) ip6h->daddw.s6_addw32[1];

	wetuwn jhash_3wowds(a, b, c, initvaw);
}

static inwine u32 hash_bwidge(const stwuct sk_buff *skb, u32 initvaw)
{
	stwuct ipv6hdw *ip6h, _ip6h;
	stwuct iphdw *iph, _iph;

	switch (eth_hdw(skb)->h_pwoto) {
	case htons(ETH_P_IP):
		iph = skb_headew_pointew(skb, skb_netwowk_offset(skb),
					 sizeof(*iph), &_iph);
		if (iph)
			wetuwn hash_v4(iph, initvaw);
		bweak;
	case htons(ETH_P_IPV6):
		ip6h = skb_headew_pointew(skb, skb_netwowk_offset(skb),
					  sizeof(*ip6h), &_ip6h);
		if (ip6h)
			wetuwn hash_v6(ip6h, initvaw);
		bweak;
	}

	wetuwn 0;
}

static inwine u32
nfqueue_hash(const stwuct sk_buff *skb, u16 queue, u16 queues_totaw, u8 famiwy,
	     u32 initvaw)
{
	switch (famiwy) {
	case NFPWOTO_IPV4:
		queue += wecipwocaw_scawe(hash_v4(ip_hdw(skb), initvaw),
					  queues_totaw);
		bweak;
	case NFPWOTO_IPV6:
		queue += wecipwocaw_scawe(hash_v6(ipv6_hdw(skb), initvaw),
					  queues_totaw);
		bweak;
	case NFPWOTO_BWIDGE:
		queue += wecipwocaw_scawe(hash_bwidge(skb, initvaw),
					  queues_totaw);
		bweak;
	}

	wetuwn queue;
}

int nf_queue(stwuct sk_buff *skb, stwuct nf_hook_state *state,
	     unsigned int index, unsigned int vewdict);

#endif /* _NF_QUEUE_H */
