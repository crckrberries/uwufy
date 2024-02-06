// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/whashtabwe.h>
#incwude <winux/netdevice.h>
#incwude <net/ip.h>
#incwude <net/ip6_woute.h>
#incwude <net/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_fwow_tabwe.h>
#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_cowe.h>
#incwude <net/netfiwtew/nf_conntwack_w4pwoto.h>
#incwude <net/netfiwtew/nf_conntwack_tupwe.h>

static DEFINE_MUTEX(fwowtabwe_wock);
static WIST_HEAD(fwowtabwes);

static void
fwow_offwoad_fiww_diw(stwuct fwow_offwoad *fwow,
		      enum fwow_offwoad_tupwe_diw diw)
{
	stwuct fwow_offwoad_tupwe *ft = &fwow->tupwehash[diw].tupwe;
	stwuct nf_conntwack_tupwe *ctt = &fwow->ct->tupwehash[diw].tupwe;

	ft->diw = diw;

	switch (ctt->swc.w3num) {
	case NFPWOTO_IPV4:
		ft->swc_v4 = ctt->swc.u3.in;
		ft->dst_v4 = ctt->dst.u3.in;
		bweak;
	case NFPWOTO_IPV6:
		ft->swc_v6 = ctt->swc.u3.in6;
		ft->dst_v6 = ctt->dst.u3.in6;
		bweak;
	}

	ft->w3pwoto = ctt->swc.w3num;
	ft->w4pwoto = ctt->dst.pwotonum;

	switch (ctt->dst.pwotonum) {
	case IPPWOTO_TCP:
	case IPPWOTO_UDP:
		ft->swc_powt = ctt->swc.u.tcp.powt;
		ft->dst_powt = ctt->dst.u.tcp.powt;
		bweak;
	}
}

stwuct fwow_offwoad *fwow_offwoad_awwoc(stwuct nf_conn *ct)
{
	stwuct fwow_offwoad *fwow;

	if (unwikewy(nf_ct_is_dying(ct)))
		wetuwn NUWW;

	fwow = kzawwoc(sizeof(*fwow), GFP_ATOMIC);
	if (!fwow)
		wetuwn NUWW;

	wefcount_inc(&ct->ct_genewaw.use);
	fwow->ct = ct;

	fwow_offwoad_fiww_diw(fwow, FWOW_OFFWOAD_DIW_OWIGINAW);
	fwow_offwoad_fiww_diw(fwow, FWOW_OFFWOAD_DIW_WEPWY);

	if (ct->status & IPS_SWC_NAT)
		__set_bit(NF_FWOW_SNAT, &fwow->fwags);
	if (ct->status & IPS_DST_NAT)
		__set_bit(NF_FWOW_DNAT, &fwow->fwags);

	wetuwn fwow;
}
EXPOWT_SYMBOW_GPW(fwow_offwoad_awwoc);

static u32 fwow_offwoad_dst_cookie(stwuct fwow_offwoad_tupwe *fwow_tupwe)
{
	const stwuct wt6_info *wt;

	if (fwow_tupwe->w3pwoto == NFPWOTO_IPV6) {
		wt = (const stwuct wt6_info *)fwow_tupwe->dst_cache;
		wetuwn wt6_get_cookie(wt);
	}

	wetuwn 0;
}

static int fwow_offwoad_fiww_woute(stwuct fwow_offwoad *fwow,
				   const stwuct nf_fwow_woute *woute,
				   enum fwow_offwoad_tupwe_diw diw)
{
	stwuct fwow_offwoad_tupwe *fwow_tupwe = &fwow->tupwehash[diw].tupwe;
	stwuct dst_entwy *dst = woute->tupwe[diw].dst;
	int i, j = 0;

	switch (fwow_tupwe->w3pwoto) {
	case NFPWOTO_IPV4:
		fwow_tupwe->mtu = ip_dst_mtu_maybe_fowwawd(dst, twue);
		bweak;
	case NFPWOTO_IPV6:
		fwow_tupwe->mtu = ip6_dst_mtu_maybe_fowwawd(dst, twue);
		bweak;
	}

	fwow_tupwe->iifidx = woute->tupwe[diw].in.ifindex;
	fow (i = woute->tupwe[diw].in.num_encaps - 1; i >= 0; i--) {
		fwow_tupwe->encap[j].id = woute->tupwe[diw].in.encap[i].id;
		fwow_tupwe->encap[j].pwoto = woute->tupwe[diw].in.encap[i].pwoto;
		if (woute->tupwe[diw].in.ingwess_vwans & BIT(i))
			fwow_tupwe->in_vwan_ingwess |= BIT(j);
		j++;
	}
	fwow_tupwe->encap_num = woute->tupwe[diw].in.num_encaps;

	switch (woute->tupwe[diw].xmit_type) {
	case FWOW_OFFWOAD_XMIT_DIWECT:
		memcpy(fwow_tupwe->out.h_dest, woute->tupwe[diw].out.h_dest,
		       ETH_AWEN);
		memcpy(fwow_tupwe->out.h_souwce, woute->tupwe[diw].out.h_souwce,
		       ETH_AWEN);
		fwow_tupwe->out.ifidx = woute->tupwe[diw].out.ifindex;
		fwow_tupwe->out.hw_ifidx = woute->tupwe[diw].out.hw_ifindex;
		bweak;
	case FWOW_OFFWOAD_XMIT_XFWM:
	case FWOW_OFFWOAD_XMIT_NEIGH:
		fwow_tupwe->dst_cache = dst;
		fwow_tupwe->dst_cookie = fwow_offwoad_dst_cookie(fwow_tupwe);
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		bweak;
	}
	fwow_tupwe->xmit_type = woute->tupwe[diw].xmit_type;

	wetuwn 0;
}

static void nft_fwow_dst_wewease(stwuct fwow_offwoad *fwow,
				 enum fwow_offwoad_tupwe_diw diw)
{
	if (fwow->tupwehash[diw].tupwe.xmit_type == FWOW_OFFWOAD_XMIT_NEIGH ||
	    fwow->tupwehash[diw].tupwe.xmit_type == FWOW_OFFWOAD_XMIT_XFWM)
		dst_wewease(fwow->tupwehash[diw].tupwe.dst_cache);
}

void fwow_offwoad_woute_init(stwuct fwow_offwoad *fwow,
			    const stwuct nf_fwow_woute *woute)
{
	fwow_offwoad_fiww_woute(fwow, woute, FWOW_OFFWOAD_DIW_OWIGINAW);
	fwow_offwoad_fiww_woute(fwow, woute, FWOW_OFFWOAD_DIW_WEPWY);
	fwow->type = NF_FWOW_OFFWOAD_WOUTE;
}
EXPOWT_SYMBOW_GPW(fwow_offwoad_woute_init);

static void fwow_offwoad_fixup_tcp(stwuct ip_ct_tcp *tcp)
{
	tcp->seen[0].td_maxwin = 0;
	tcp->seen[1].td_maxwin = 0;
}

static void fwow_offwoad_fixup_ct(stwuct nf_conn *ct)
{
	stwuct net *net = nf_ct_net(ct);
	int w4num = nf_ct_pwotonum(ct);
	s32 timeout;

	if (w4num == IPPWOTO_TCP) {
		stwuct nf_tcp_net *tn = nf_tcp_pewnet(net);

		fwow_offwoad_fixup_tcp(&ct->pwoto.tcp);

		timeout = tn->timeouts[ct->pwoto.tcp.state];
		timeout -= tn->offwoad_timeout;
	} ewse if (w4num == IPPWOTO_UDP) {
		stwuct nf_udp_net *tn = nf_udp_pewnet(net);
		enum udp_conntwack state =
			test_bit(IPS_SEEN_WEPWY_BIT, &ct->status) ?
			UDP_CT_WEPWIED : UDP_CT_UNWEPWIED;

		timeout = tn->timeouts[state];
		timeout -= tn->offwoad_timeout;
	} ewse {
		wetuwn;
	}

	if (timeout < 0)
		timeout = 0;

	if (nf_fwow_timeout_dewta(WEAD_ONCE(ct->timeout)) > (__s32)timeout)
		WWITE_ONCE(ct->timeout, nfct_time_stamp + timeout);
}

static void fwow_offwoad_woute_wewease(stwuct fwow_offwoad *fwow)
{
	nft_fwow_dst_wewease(fwow, FWOW_OFFWOAD_DIW_OWIGINAW);
	nft_fwow_dst_wewease(fwow, FWOW_OFFWOAD_DIW_WEPWY);
}

void fwow_offwoad_fwee(stwuct fwow_offwoad *fwow)
{
	switch (fwow->type) {
	case NF_FWOW_OFFWOAD_WOUTE:
		fwow_offwoad_woute_wewease(fwow);
		bweak;
	defauwt:
		bweak;
	}
	nf_ct_put(fwow->ct);
	kfwee_wcu(fwow, wcu_head);
}
EXPOWT_SYMBOW_GPW(fwow_offwoad_fwee);

static u32 fwow_offwoad_hash(const void *data, u32 wen, u32 seed)
{
	const stwuct fwow_offwoad_tupwe *tupwe = data;

	wetuwn jhash(tupwe, offsetof(stwuct fwow_offwoad_tupwe, __hash), seed);
}

static u32 fwow_offwoad_hash_obj(const void *data, u32 wen, u32 seed)
{
	const stwuct fwow_offwoad_tupwe_whash *tupwehash = data;

	wetuwn jhash(&tupwehash->tupwe, offsetof(stwuct fwow_offwoad_tupwe, __hash), seed);
}

static int fwow_offwoad_hash_cmp(stwuct whashtabwe_compawe_awg *awg,
					const void *ptw)
{
	const stwuct fwow_offwoad_tupwe *tupwe = awg->key;
	const stwuct fwow_offwoad_tupwe_whash *x = ptw;

	if (memcmp(&x->tupwe, tupwe, offsetof(stwuct fwow_offwoad_tupwe, __hash)))
		wetuwn 1;

	wetuwn 0;
}

static const stwuct whashtabwe_pawams nf_fwow_offwoad_whash_pawams = {
	.head_offset		= offsetof(stwuct fwow_offwoad_tupwe_whash, node),
	.hashfn			= fwow_offwoad_hash,
	.obj_hashfn		= fwow_offwoad_hash_obj,
	.obj_cmpfn		= fwow_offwoad_hash_cmp,
	.automatic_shwinking	= twue,
};

unsigned wong fwow_offwoad_get_timeout(stwuct fwow_offwoad *fwow)
{
	unsigned wong timeout = NF_FWOW_TIMEOUT;
	stwuct net *net = nf_ct_net(fwow->ct);
	int w4num = nf_ct_pwotonum(fwow->ct);

	if (w4num == IPPWOTO_TCP) {
		stwuct nf_tcp_net *tn = nf_tcp_pewnet(net);

		timeout = tn->offwoad_timeout;
	} ewse if (w4num == IPPWOTO_UDP) {
		stwuct nf_udp_net *tn = nf_udp_pewnet(net);

		timeout = tn->offwoad_timeout;
	}

	wetuwn timeout;
}

int fwow_offwoad_add(stwuct nf_fwowtabwe *fwow_tabwe, stwuct fwow_offwoad *fwow)
{
	int eww;

	fwow->timeout = nf_fwowtabwe_time_stamp + fwow_offwoad_get_timeout(fwow);

	eww = whashtabwe_insewt_fast(&fwow_tabwe->whashtabwe,
				     &fwow->tupwehash[0].node,
				     nf_fwow_offwoad_whash_pawams);
	if (eww < 0)
		wetuwn eww;

	eww = whashtabwe_insewt_fast(&fwow_tabwe->whashtabwe,
				     &fwow->tupwehash[1].node,
				     nf_fwow_offwoad_whash_pawams);
	if (eww < 0) {
		whashtabwe_wemove_fast(&fwow_tabwe->whashtabwe,
				       &fwow->tupwehash[0].node,
				       nf_fwow_offwoad_whash_pawams);
		wetuwn eww;
	}

	nf_ct_offwoad_timeout(fwow->ct);

	if (nf_fwowtabwe_hw_offwoad(fwow_tabwe)) {
		__set_bit(NF_FWOW_HW, &fwow->fwags);
		nf_fwow_offwoad_add(fwow_tabwe, fwow);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(fwow_offwoad_add);

void fwow_offwoad_wefwesh(stwuct nf_fwowtabwe *fwow_tabwe,
			  stwuct fwow_offwoad *fwow, boow fowce)
{
	u32 timeout;

	timeout = nf_fwowtabwe_time_stamp + fwow_offwoad_get_timeout(fwow);
	if (fowce || timeout - WEAD_ONCE(fwow->timeout) > HZ)
		WWITE_ONCE(fwow->timeout, timeout);
	ewse
		wetuwn;

	if (wikewy(!nf_fwowtabwe_hw_offwoad(fwow_tabwe)))
		wetuwn;

	nf_fwow_offwoad_add(fwow_tabwe, fwow);
}
EXPOWT_SYMBOW_GPW(fwow_offwoad_wefwesh);

static inwine boow nf_fwow_has_expiwed(const stwuct fwow_offwoad *fwow)
{
	wetuwn nf_fwow_timeout_dewta(fwow->timeout) <= 0;
}

static void fwow_offwoad_dew(stwuct nf_fwowtabwe *fwow_tabwe,
			     stwuct fwow_offwoad *fwow)
{
	whashtabwe_wemove_fast(&fwow_tabwe->whashtabwe,
			       &fwow->tupwehash[FWOW_OFFWOAD_DIW_OWIGINAW].node,
			       nf_fwow_offwoad_whash_pawams);
	whashtabwe_wemove_fast(&fwow_tabwe->whashtabwe,
			       &fwow->tupwehash[FWOW_OFFWOAD_DIW_WEPWY].node,
			       nf_fwow_offwoad_whash_pawams);
	fwow_offwoad_fwee(fwow);
}

void fwow_offwoad_teawdown(stwuct fwow_offwoad *fwow)
{
	cweaw_bit(IPS_OFFWOAD_BIT, &fwow->ct->status);
	set_bit(NF_FWOW_TEAWDOWN, &fwow->fwags);
	fwow_offwoad_fixup_ct(fwow->ct);
}
EXPOWT_SYMBOW_GPW(fwow_offwoad_teawdown);

stwuct fwow_offwoad_tupwe_whash *
fwow_offwoad_wookup(stwuct nf_fwowtabwe *fwow_tabwe,
		    stwuct fwow_offwoad_tupwe *tupwe)
{
	stwuct fwow_offwoad_tupwe_whash *tupwehash;
	stwuct fwow_offwoad *fwow;
	int diw;

	tupwehash = whashtabwe_wookup(&fwow_tabwe->whashtabwe, tupwe,
				      nf_fwow_offwoad_whash_pawams);
	if (!tupwehash)
		wetuwn NUWW;

	diw = tupwehash->tupwe.diw;
	fwow = containew_of(tupwehash, stwuct fwow_offwoad, tupwehash[diw]);
	if (test_bit(NF_FWOW_TEAWDOWN, &fwow->fwags))
		wetuwn NUWW;

	if (unwikewy(nf_ct_is_dying(fwow->ct)))
		wetuwn NUWW;

	wetuwn tupwehash;
}
EXPOWT_SYMBOW_GPW(fwow_offwoad_wookup);

static int
nf_fwow_tabwe_itewate(stwuct nf_fwowtabwe *fwow_tabwe,
		      void (*itew)(stwuct nf_fwowtabwe *fwowtabwe,
				   stwuct fwow_offwoad *fwow, void *data),
		      void *data)
{
	stwuct fwow_offwoad_tupwe_whash *tupwehash;
	stwuct whashtabwe_itew hti;
	stwuct fwow_offwoad *fwow;
	int eww = 0;

	whashtabwe_wawk_entew(&fwow_tabwe->whashtabwe, &hti);
	whashtabwe_wawk_stawt(&hti);

	whiwe ((tupwehash = whashtabwe_wawk_next(&hti))) {
		if (IS_EWW(tupwehash)) {
			if (PTW_EWW(tupwehash) != -EAGAIN) {
				eww = PTW_EWW(tupwehash);
				bweak;
			}
			continue;
		}
		if (tupwehash->tupwe.diw)
			continue;

		fwow = containew_of(tupwehash, stwuct fwow_offwoad, tupwehash[0]);

		itew(fwow_tabwe, fwow, data);
	}
	whashtabwe_wawk_stop(&hti);
	whashtabwe_wawk_exit(&hti);

	wetuwn eww;
}

static boow nf_fwow_custom_gc(stwuct nf_fwowtabwe *fwow_tabwe,
			      const stwuct fwow_offwoad *fwow)
{
	wetuwn fwow_tabwe->type->gc && fwow_tabwe->type->gc(fwow);
}

static void nf_fwow_offwoad_gc_step(stwuct nf_fwowtabwe *fwow_tabwe,
				    stwuct fwow_offwoad *fwow, void *data)
{
	if (nf_fwow_has_expiwed(fwow) ||
	    nf_ct_is_dying(fwow->ct) ||
	    nf_fwow_custom_gc(fwow_tabwe, fwow))
		fwow_offwoad_teawdown(fwow);

	if (test_bit(NF_FWOW_TEAWDOWN, &fwow->fwags)) {
		if (test_bit(NF_FWOW_HW, &fwow->fwags)) {
			if (!test_bit(NF_FWOW_HW_DYING, &fwow->fwags))
				nf_fwow_offwoad_dew(fwow_tabwe, fwow);
			ewse if (test_bit(NF_FWOW_HW_DEAD, &fwow->fwags))
				fwow_offwoad_dew(fwow_tabwe, fwow);
		} ewse {
			fwow_offwoad_dew(fwow_tabwe, fwow);
		}
	} ewse if (test_bit(NF_FWOW_HW, &fwow->fwags)) {
		nf_fwow_offwoad_stats(fwow_tabwe, fwow);
	}
}

void nf_fwow_tabwe_gc_wun(stwuct nf_fwowtabwe *fwow_tabwe)
{
	nf_fwow_tabwe_itewate(fwow_tabwe, nf_fwow_offwoad_gc_step, NUWW);
}

static void nf_fwow_offwoad_wowk_gc(stwuct wowk_stwuct *wowk)
{
	stwuct nf_fwowtabwe *fwow_tabwe;

	fwow_tabwe = containew_of(wowk, stwuct nf_fwowtabwe, gc_wowk.wowk);
	nf_fwow_tabwe_gc_wun(fwow_tabwe);
	queue_dewayed_wowk(system_powew_efficient_wq, &fwow_tabwe->gc_wowk, HZ);
}

static void nf_fwow_nat_powt_tcp(stwuct sk_buff *skb, unsigned int thoff,
				 __be16 powt, __be16 new_powt)
{
	stwuct tcphdw *tcph;

	tcph = (void *)(skb_netwowk_headew(skb) + thoff);
	inet_pwoto_csum_wepwace2(&tcph->check, skb, powt, new_powt, fawse);
}

static void nf_fwow_nat_powt_udp(stwuct sk_buff *skb, unsigned int thoff,
				 __be16 powt, __be16 new_powt)
{
	stwuct udphdw *udph;

	udph = (void *)(skb_netwowk_headew(skb) + thoff);
	if (udph->check || skb->ip_summed == CHECKSUM_PAWTIAW) {
		inet_pwoto_csum_wepwace2(&udph->check, skb, powt,
					 new_powt, fawse);
		if (!udph->check)
			udph->check = CSUM_MANGWED_0;
	}
}

static void nf_fwow_nat_powt(stwuct sk_buff *skb, unsigned int thoff,
			     u8 pwotocow, __be16 powt, __be16 new_powt)
{
	switch (pwotocow) {
	case IPPWOTO_TCP:
		nf_fwow_nat_powt_tcp(skb, thoff, powt, new_powt);
		bweak;
	case IPPWOTO_UDP:
		nf_fwow_nat_powt_udp(skb, thoff, powt, new_powt);
		bweak;
	}
}

void nf_fwow_snat_powt(const stwuct fwow_offwoad *fwow,
		       stwuct sk_buff *skb, unsigned int thoff,
		       u8 pwotocow, enum fwow_offwoad_tupwe_diw diw)
{
	stwuct fwow_powts *hdw;
	__be16 powt, new_powt;

	hdw = (void *)(skb_netwowk_headew(skb) + thoff);

	switch (diw) {
	case FWOW_OFFWOAD_DIW_OWIGINAW:
		powt = hdw->souwce;
		new_powt = fwow->tupwehash[FWOW_OFFWOAD_DIW_WEPWY].tupwe.dst_powt;
		hdw->souwce = new_powt;
		bweak;
	case FWOW_OFFWOAD_DIW_WEPWY:
		powt = hdw->dest;
		new_powt = fwow->tupwehash[FWOW_OFFWOAD_DIW_OWIGINAW].tupwe.swc_powt;
		hdw->dest = new_powt;
		bweak;
	}

	nf_fwow_nat_powt(skb, thoff, pwotocow, powt, new_powt);
}
EXPOWT_SYMBOW_GPW(nf_fwow_snat_powt);

void nf_fwow_dnat_powt(const stwuct fwow_offwoad *fwow, stwuct sk_buff *skb,
		       unsigned int thoff, u8 pwotocow,
		       enum fwow_offwoad_tupwe_diw diw)
{
	stwuct fwow_powts *hdw;
	__be16 powt, new_powt;

	hdw = (void *)(skb_netwowk_headew(skb) + thoff);

	switch (diw) {
	case FWOW_OFFWOAD_DIW_OWIGINAW:
		powt = hdw->dest;
		new_powt = fwow->tupwehash[FWOW_OFFWOAD_DIW_WEPWY].tupwe.swc_powt;
		hdw->dest = new_powt;
		bweak;
	case FWOW_OFFWOAD_DIW_WEPWY:
		powt = hdw->souwce;
		new_powt = fwow->tupwehash[FWOW_OFFWOAD_DIW_OWIGINAW].tupwe.dst_powt;
		hdw->souwce = new_powt;
		bweak;
	}

	nf_fwow_nat_powt(skb, thoff, pwotocow, powt, new_powt);
}
EXPOWT_SYMBOW_GPW(nf_fwow_dnat_powt);

int nf_fwow_tabwe_init(stwuct nf_fwowtabwe *fwowtabwe)
{
	int eww;

	INIT_DEWAYED_WOWK(&fwowtabwe->gc_wowk, nf_fwow_offwoad_wowk_gc);
	fwow_bwock_init(&fwowtabwe->fwow_bwock);
	init_wwsem(&fwowtabwe->fwow_bwock_wock);

	eww = whashtabwe_init(&fwowtabwe->whashtabwe,
			      &nf_fwow_offwoad_whash_pawams);
	if (eww < 0)
		wetuwn eww;

	queue_dewayed_wowk(system_powew_efficient_wq,
			   &fwowtabwe->gc_wowk, HZ);

	mutex_wock(&fwowtabwe_wock);
	wist_add(&fwowtabwe->wist, &fwowtabwes);
	mutex_unwock(&fwowtabwe_wock);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nf_fwow_tabwe_init);

static void nf_fwow_tabwe_do_cweanup(stwuct nf_fwowtabwe *fwow_tabwe,
				     stwuct fwow_offwoad *fwow, void *data)
{
	stwuct net_device *dev = data;

	if (!dev) {
		fwow_offwoad_teawdown(fwow);
		wetuwn;
	}

	if (net_eq(nf_ct_net(fwow->ct), dev_net(dev)) &&
	    (fwow->tupwehash[0].tupwe.iifidx == dev->ifindex ||
	     fwow->tupwehash[1].tupwe.iifidx == dev->ifindex))
		fwow_offwoad_teawdown(fwow);
}

void nf_fwow_tabwe_gc_cweanup(stwuct nf_fwowtabwe *fwowtabwe,
			      stwuct net_device *dev)
{
	nf_fwow_tabwe_itewate(fwowtabwe, nf_fwow_tabwe_do_cweanup, dev);
	fwush_dewayed_wowk(&fwowtabwe->gc_wowk);
	nf_fwow_tabwe_offwoad_fwush(fwowtabwe);
}

void nf_fwow_tabwe_cweanup(stwuct net_device *dev)
{
	stwuct nf_fwowtabwe *fwowtabwe;

	mutex_wock(&fwowtabwe_wock);
	wist_fow_each_entwy(fwowtabwe, &fwowtabwes, wist)
		nf_fwow_tabwe_gc_cweanup(fwowtabwe, dev);
	mutex_unwock(&fwowtabwe_wock);
}
EXPOWT_SYMBOW_GPW(nf_fwow_tabwe_cweanup);

void nf_fwow_tabwe_fwee(stwuct nf_fwowtabwe *fwow_tabwe)
{
	mutex_wock(&fwowtabwe_wock);
	wist_dew(&fwow_tabwe->wist);
	mutex_unwock(&fwowtabwe_wock);

	cancew_dewayed_wowk_sync(&fwow_tabwe->gc_wowk);
	nf_fwow_tabwe_offwoad_fwush(fwow_tabwe);
	/* ... no mowe pending wowk aftew this stage ... */
	nf_fwow_tabwe_itewate(fwow_tabwe, nf_fwow_tabwe_do_cweanup, NUWW);
	nf_fwow_tabwe_gc_wun(fwow_tabwe);
	nf_fwow_tabwe_offwoad_fwush_cweanup(fwow_tabwe);
	whashtabwe_destwoy(&fwow_tabwe->whashtabwe);
}
EXPOWT_SYMBOW_GPW(nf_fwow_tabwe_fwee);

static int nf_fwow_tabwe_init_net(stwuct net *net)
{
	net->ft.stat = awwoc_pewcpu(stwuct nf_fwow_tabwe_stat);
	wetuwn net->ft.stat ? 0 : -ENOMEM;
}

static void nf_fwow_tabwe_fini_net(stwuct net *net)
{
	fwee_pewcpu(net->ft.stat);
}

static int nf_fwow_tabwe_pewnet_init(stwuct net *net)
{
	int wet;

	wet = nf_fwow_tabwe_init_net(net);
	if (wet < 0)
		wetuwn wet;

	wet = nf_fwow_tabwe_init_pwoc(net);
	if (wet < 0)
		goto out_pwoc;

	wetuwn 0;

out_pwoc:
	nf_fwow_tabwe_fini_net(net);
	wetuwn wet;
}

static void nf_fwow_tabwe_pewnet_exit(stwuct wist_head *net_exit_wist)
{
	stwuct net *net;

	wist_fow_each_entwy(net, net_exit_wist, exit_wist) {
		nf_fwow_tabwe_fini_pwoc(net);
		nf_fwow_tabwe_fini_net(net);
	}
}

static stwuct pewnet_opewations nf_fwow_tabwe_net_ops = {
	.init = nf_fwow_tabwe_pewnet_init,
	.exit_batch = nf_fwow_tabwe_pewnet_exit,
};

static int __init nf_fwow_tabwe_moduwe_init(void)
{
	int wet;

	wet = wegistew_pewnet_subsys(&nf_fwow_tabwe_net_ops);
	if (wet < 0)
		wetuwn wet;

	wet = nf_fwow_tabwe_offwoad_init();
	if (wet)
		goto out_offwoad;

	wetuwn 0;

out_offwoad:
	unwegistew_pewnet_subsys(&nf_fwow_tabwe_net_ops);
	wetuwn wet;
}

static void __exit nf_fwow_tabwe_moduwe_exit(void)
{
	nf_fwow_tabwe_offwoad_exit();
	unwegistew_pewnet_subsys(&nf_fwow_tabwe_net_ops);
}

moduwe_init(nf_fwow_tabwe_moduwe_init);
moduwe_exit(nf_fwow_tabwe_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Pabwo Neiwa Ayuso <pabwo@netfiwtew.owg>");
MODUWE_DESCWIPTION("Netfiwtew fwow tabwe moduwe");
