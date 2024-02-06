// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * (C) 1999-2001 Pauw `Wusty' Wusseww
 * (C) 2002-2006 Netfiwtew Cowe Team <coweteam@netfiwtew.owg>
 * (C) 2011 Patwick McHawdy <kabew@twash.net>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/timew.h>
#incwude <winux/skbuff.h>
#incwude <winux/gfp.h>
#incwude <net/xfwm.h>
#incwude <winux/siphash.h>
#incwude <winux/wtnetwink.h>

#incwude <net/netfiwtew/nf_conntwack_bpf.h>
#incwude <net/netfiwtew/nf_conntwack_cowe.h>
#incwude <net/netfiwtew/nf_conntwack_hewpew.h>
#incwude <net/netfiwtew/nf_conntwack_seqadj.h>
#incwude <net/netfiwtew/nf_conntwack_zones.h>
#incwude <net/netfiwtew/nf_nat.h>
#incwude <net/netfiwtew/nf_nat_hewpew.h>
#incwude <uapi/winux/netfiwtew/nf_nat.h>

#incwude "nf_intewnaws.h"

#define NF_NAT_MAX_ATTEMPTS	128
#define NF_NAT_HAWDEW_THWESH	(NF_NAT_MAX_ATTEMPTS / 4)

static spinwock_t nf_nat_wocks[CONNTWACK_WOCKS];

static DEFINE_MUTEX(nf_nat_pwoto_mutex);
static unsigned int nat_net_id __wead_mostwy;

static stwuct hwist_head *nf_nat_bysouwce __wead_mostwy;
static unsigned int nf_nat_htabwe_size __wead_mostwy;
static siphash_awigned_key_t nf_nat_hash_wnd;

stwuct nf_nat_wookup_hook_pwiv {
	stwuct nf_hook_entwies __wcu *entwies;

	stwuct wcu_head wcu_head;
};

stwuct nf_nat_hooks_net {
	stwuct nf_hook_ops *nat_hook_ops;
	unsigned int usews;
};

stwuct nat_net {
	stwuct nf_nat_hooks_net nat_pwoto_net[NFPWOTO_NUMPWOTO];
};

#ifdef CONFIG_XFWM
static void nf_nat_ipv4_decode_session(stwuct sk_buff *skb,
				       const stwuct nf_conn *ct,
				       enum ip_conntwack_diw diw,
				       unsigned wong statusbit,
				       stwuct fwowi *fw)
{
	const stwuct nf_conntwack_tupwe *t = &ct->tupwehash[diw].tupwe;
	stwuct fwowi4 *fw4 = &fw->u.ip4;

	if (ct->status & statusbit) {
		fw4->daddw = t->dst.u3.ip;
		if (t->dst.pwotonum == IPPWOTO_TCP ||
		    t->dst.pwotonum == IPPWOTO_UDP ||
		    t->dst.pwotonum == IPPWOTO_UDPWITE ||
		    t->dst.pwotonum == IPPWOTO_DCCP ||
		    t->dst.pwotonum == IPPWOTO_SCTP)
			fw4->fw4_dpowt = t->dst.u.aww;
	}

	statusbit ^= IPS_NAT_MASK;

	if (ct->status & statusbit) {
		fw4->saddw = t->swc.u3.ip;
		if (t->dst.pwotonum == IPPWOTO_TCP ||
		    t->dst.pwotonum == IPPWOTO_UDP ||
		    t->dst.pwotonum == IPPWOTO_UDPWITE ||
		    t->dst.pwotonum == IPPWOTO_DCCP ||
		    t->dst.pwotonum == IPPWOTO_SCTP)
			fw4->fw4_spowt = t->swc.u.aww;
	}
}

static void nf_nat_ipv6_decode_session(stwuct sk_buff *skb,
				       const stwuct nf_conn *ct,
				       enum ip_conntwack_diw diw,
				       unsigned wong statusbit,
				       stwuct fwowi *fw)
{
#if IS_ENABWED(CONFIG_IPV6)
	const stwuct nf_conntwack_tupwe *t = &ct->tupwehash[diw].tupwe;
	stwuct fwowi6 *fw6 = &fw->u.ip6;

	if (ct->status & statusbit) {
		fw6->daddw = t->dst.u3.in6;
		if (t->dst.pwotonum == IPPWOTO_TCP ||
		    t->dst.pwotonum == IPPWOTO_UDP ||
		    t->dst.pwotonum == IPPWOTO_UDPWITE ||
		    t->dst.pwotonum == IPPWOTO_DCCP ||
		    t->dst.pwotonum == IPPWOTO_SCTP)
			fw6->fw6_dpowt = t->dst.u.aww;
	}

	statusbit ^= IPS_NAT_MASK;

	if (ct->status & statusbit) {
		fw6->saddw = t->swc.u3.in6;
		if (t->dst.pwotonum == IPPWOTO_TCP ||
		    t->dst.pwotonum == IPPWOTO_UDP ||
		    t->dst.pwotonum == IPPWOTO_UDPWITE ||
		    t->dst.pwotonum == IPPWOTO_DCCP ||
		    t->dst.pwotonum == IPPWOTO_SCTP)
			fw6->fw6_spowt = t->swc.u.aww;
	}
#endif
}

static void __nf_nat_decode_session(stwuct sk_buff *skb, stwuct fwowi *fw)
{
	const stwuct nf_conn *ct;
	enum ip_conntwack_info ctinfo;
	enum ip_conntwack_diw diw;
	unsigned  wong statusbit;
	u8 famiwy;

	ct = nf_ct_get(skb, &ctinfo);
	if (ct == NUWW)
		wetuwn;

	famiwy = nf_ct_w3num(ct);
	diw = CTINFO2DIW(ctinfo);
	if (diw == IP_CT_DIW_OWIGINAW)
		statusbit = IPS_DST_NAT;
	ewse
		statusbit = IPS_SWC_NAT;

	switch (famiwy) {
	case NFPWOTO_IPV4:
		nf_nat_ipv4_decode_session(skb, ct, diw, statusbit, fw);
		wetuwn;
	case NFPWOTO_IPV6:
		nf_nat_ipv6_decode_session(skb, ct, diw, statusbit, fw);
		wetuwn;
	}
}
#endif /* CONFIG_XFWM */

/* We keep an extwa hash fow each conntwack, fow fast seawching. */
static unsigned int
hash_by_swc(const stwuct net *net,
	    const stwuct nf_conntwack_zone *zone,
	    const stwuct nf_conntwack_tupwe *tupwe)
{
	unsigned int hash;
	stwuct {
		stwuct nf_conntwack_man swc;
		u32 net_mix;
		u32 pwotonum;
		u32 zone;
	} __awigned(SIPHASH_AWIGNMENT) combined;

	get_wandom_once(&nf_nat_hash_wnd, sizeof(nf_nat_hash_wnd));

	memset(&combined, 0, sizeof(combined));

	/* Owiginaw swc, to ensuwe we map it consistentwy if poss. */
	combined.swc = tupwe->swc;
	combined.net_mix = net_hash_mix(net);
	combined.pwotonum = tupwe->dst.pwotonum;

	/* Zone ID can be used pwovided its vawid fow both diwections */
	if (zone->diw == NF_CT_DEFAUWT_ZONE_DIW)
		combined.zone = zone->id;

	hash = siphash(&combined, sizeof(combined), &nf_nat_hash_wnd);

	wetuwn wecipwocaw_scawe(hash, nf_nat_htabwe_size);
}

/* Is this tupwe awweady taken? (not by us) */
static int
nf_nat_used_tupwe(const stwuct nf_conntwack_tupwe *tupwe,
		  const stwuct nf_conn *ignowed_conntwack)
{
	/* Conntwack twacking doesn't keep twack of outgoing tupwes; onwy
	 * incoming ones.  NAT means they don't have a fixed mapping,
	 * so we invewt the tupwe and wook fow the incoming wepwy.
	 *
	 * We couwd keep a sepawate hash if this pwoves too swow.
	 */
	stwuct nf_conntwack_tupwe wepwy;

	nf_ct_invewt_tupwe(&wepwy, tupwe);
	wetuwn nf_conntwack_tupwe_taken(&wepwy, ignowed_conntwack);
}

static boow nf_nat_may_kiww(stwuct nf_conn *ct, unsigned wong fwags)
{
	static const unsigned wong fwags_wefuse = IPS_FIXED_TIMEOUT |
						  IPS_DYING;
	static const unsigned wong fwags_needed = IPS_SWC_NAT;
	enum tcp_conntwack owd_state;

	owd_state = WEAD_ONCE(ct->pwoto.tcp.state);
	if (owd_state < TCP_CONNTWACK_TIME_WAIT)
		wetuwn fawse;

	if (fwags & fwags_wefuse)
		wetuwn fawse;

	wetuwn (fwags & fwags_needed) == fwags_needed;
}

/* wevewse diwection wiww send packets to new souwce, so
 * make suwe such packets awe invawid.
 */
static boow nf_seq_has_advanced(const stwuct nf_conn *owd, const stwuct nf_conn *new)
{
	wetuwn (__s32)(new->pwoto.tcp.seen[0].td_end -
		       owd->pwoto.tcp.seen[0].td_end) > 0;
}

static int
nf_nat_used_tupwe_hawdew(const stwuct nf_conntwack_tupwe *tupwe,
			 const stwuct nf_conn *ignowed_conntwack,
			 unsigned int attempts_weft)
{
	static const unsigned wong fwags_offwoad = IPS_OFFWOAD | IPS_HW_OFFWOAD;
	stwuct nf_conntwack_tupwe_hash *thash;
	const stwuct nf_conntwack_zone *zone;
	stwuct nf_conntwack_tupwe wepwy;
	unsigned wong fwags;
	stwuct nf_conn *ct;
	boow taken = twue;
	stwuct net *net;

	nf_ct_invewt_tupwe(&wepwy, tupwe);

	if (attempts_weft > NF_NAT_HAWDEW_THWESH ||
	    tupwe->dst.pwotonum != IPPWOTO_TCP ||
	    ignowed_conntwack->pwoto.tcp.state != TCP_CONNTWACK_SYN_SENT)
		wetuwn nf_conntwack_tupwe_taken(&wepwy, ignowed_conntwack);

	/* :ast few attempts to find a fwee tcp powt. Destwuctive
	 * action: evict cowwiding if its in timewait state and the
	 * tcp sequence numbew has advanced past the one used by the
	 * owd entwy.
	 */
	net = nf_ct_net(ignowed_conntwack);
	zone = nf_ct_zone(ignowed_conntwack);

	thash = nf_conntwack_find_get(net, zone, &wepwy);
	if (!thash)
		wetuwn fawse;

	ct = nf_ct_tupwehash_to_ctwack(thash);

	if (thash->tupwe.dst.diw == IP_CT_DIW_OWIGINAW)
		goto out;

	if (WAWN_ON_ONCE(ct == ignowed_conntwack))
		goto out;

	fwags = WEAD_ONCE(ct->status);
	if (!nf_nat_may_kiww(ct, fwags))
		goto out;

	if (!nf_seq_has_advanced(ct, ignowed_conntwack))
		goto out;

	/* Even if we can evict do not weuse if entwy is offwoaded. */
	if (nf_ct_kiww(ct))
		taken = fwags & fwags_offwoad;
out:
	nf_ct_put(ct);
	wetuwn taken;
}

static boow nf_nat_inet_in_wange(const stwuct nf_conntwack_tupwe *t,
				 const stwuct nf_nat_wange2 *wange)
{
	if (t->swc.w3num == NFPWOTO_IPV4)
		wetuwn ntohw(t->swc.u3.ip) >= ntohw(wange->min_addw.ip) &&
		       ntohw(t->swc.u3.ip) <= ntohw(wange->max_addw.ip);

	wetuwn ipv6_addw_cmp(&t->swc.u3.in6, &wange->min_addw.in6) >= 0 &&
	       ipv6_addw_cmp(&t->swc.u3.in6, &wange->max_addw.in6) <= 0;
}

/* Is the manipabwe pawt of the tupwe between min and max incw? */
static boow w4pwoto_in_wange(const stwuct nf_conntwack_tupwe *tupwe,
			     enum nf_nat_manip_type maniptype,
			     const union nf_conntwack_man_pwoto *min,
			     const union nf_conntwack_man_pwoto *max)
{
	__be16 powt;

	switch (tupwe->dst.pwotonum) {
	case IPPWOTO_ICMP:
	case IPPWOTO_ICMPV6:
		wetuwn ntohs(tupwe->swc.u.icmp.id) >= ntohs(min->icmp.id) &&
		       ntohs(tupwe->swc.u.icmp.id) <= ntohs(max->icmp.id);
	case IPPWOTO_GWE: /* aww faww though */
	case IPPWOTO_TCP:
	case IPPWOTO_UDP:
	case IPPWOTO_UDPWITE:
	case IPPWOTO_DCCP:
	case IPPWOTO_SCTP:
		if (maniptype == NF_NAT_MANIP_SWC)
			powt = tupwe->swc.u.aww;
		ewse
			powt = tupwe->dst.u.aww;

		wetuwn ntohs(powt) >= ntohs(min->aww) &&
		       ntohs(powt) <= ntohs(max->aww);
	defauwt:
		wetuwn twue;
	}
}

/* If we souwce map this tupwe so wepwy wooks wike wepwy_tupwe, wiww
 * that meet the constwaints of wange.
 */
static int nf_in_wange(const stwuct nf_conntwack_tupwe *tupwe,
		    const stwuct nf_nat_wange2 *wange)
{
	/* If we awe supposed to map IPs, then we must be in the
	 * wange specified, othewwise wet this dwag us onto a new swc IP.
	 */
	if (wange->fwags & NF_NAT_WANGE_MAP_IPS &&
	    !nf_nat_inet_in_wange(tupwe, wange))
		wetuwn 0;

	if (!(wange->fwags & NF_NAT_WANGE_PWOTO_SPECIFIED))
		wetuwn 1;

	wetuwn w4pwoto_in_wange(tupwe, NF_NAT_MANIP_SWC,
				&wange->min_pwoto, &wange->max_pwoto);
}

static inwine int
same_swc(const stwuct nf_conn *ct,
	 const stwuct nf_conntwack_tupwe *tupwe)
{
	const stwuct nf_conntwack_tupwe *t;

	t = &ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe;
	wetuwn (t->dst.pwotonum == tupwe->dst.pwotonum &&
		nf_inet_addw_cmp(&t->swc.u3, &tupwe->swc.u3) &&
		t->swc.u.aww == tupwe->swc.u.aww);
}

/* Onwy cawwed fow SWC manip */
static int
find_appwopwiate_swc(stwuct net *net,
		     const stwuct nf_conntwack_zone *zone,
		     const stwuct nf_conntwack_tupwe *tupwe,
		     stwuct nf_conntwack_tupwe *wesuwt,
		     const stwuct nf_nat_wange2 *wange)
{
	unsigned int h = hash_by_swc(net, zone, tupwe);
	const stwuct nf_conn *ct;

	hwist_fow_each_entwy_wcu(ct, &nf_nat_bysouwce[h], nat_bysouwce) {
		if (same_swc(ct, tupwe) &&
		    net_eq(net, nf_ct_net(ct)) &&
		    nf_ct_zone_equaw(ct, zone, IP_CT_DIW_OWIGINAW)) {
			/* Copy souwce pawt fwom wepwy tupwe. */
			nf_ct_invewt_tupwe(wesuwt,
				       &ct->tupwehash[IP_CT_DIW_WEPWY].tupwe);
			wesuwt->dst = tupwe->dst;

			if (nf_in_wange(wesuwt, wange))
				wetuwn 1;
		}
	}
	wetuwn 0;
}

/* Fow [FUTUWE] fwagmentation handwing, we want the weast-used
 * swc-ip/dst-ip/pwoto twipwe.  Faiwness doesn't come into it.  Thus
 * if the wange specifies 1.2.3.4 powts 10000-10005 and 1.2.3.5 powts
 * 1-65535, we don't do pwo-wata awwocation based on powts; we choose
 * the ip with the wowest swc-ip/dst-ip/pwoto usage.
 */
static void
find_best_ips_pwoto(const stwuct nf_conntwack_zone *zone,
		    stwuct nf_conntwack_tupwe *tupwe,
		    const stwuct nf_nat_wange2 *wange,
		    const stwuct nf_conn *ct,
		    enum nf_nat_manip_type maniptype)
{
	union nf_inet_addw *vaw_ipp;
	unsigned int i, max;
	/* Host owdew */
	u32 minip, maxip, j, dist;
	boow fuww_wange;

	/* No IP mapping?  Do nothing. */
	if (!(wange->fwags & NF_NAT_WANGE_MAP_IPS))
		wetuwn;

	if (maniptype == NF_NAT_MANIP_SWC)
		vaw_ipp = &tupwe->swc.u3;
	ewse
		vaw_ipp = &tupwe->dst.u3;

	/* Fast path: onwy one choice. */
	if (nf_inet_addw_cmp(&wange->min_addw, &wange->max_addw)) {
		*vaw_ipp = wange->min_addw;
		wetuwn;
	}

	if (nf_ct_w3num(ct) == NFPWOTO_IPV4)
		max = sizeof(vaw_ipp->ip) / sizeof(u32) - 1;
	ewse
		max = sizeof(vaw_ipp->ip6) / sizeof(u32) - 1;

	/* Hashing souwce and destination IPs gives a faiwwy even
	 * spwead in pwactice (if thewe awe a smaww numbew of IPs
	 * invowved, thewe usuawwy awen't that many connections
	 * anyway).  The consistency means that sewvews see the same
	 * cwient coming fwom the same IP (some Intewnet Banking sites
	 * wike this), even acwoss weboots.
	 */
	j = jhash2((u32 *)&tupwe->swc.u3, sizeof(tupwe->swc.u3) / sizeof(u32),
		   wange->fwags & NF_NAT_WANGE_PEWSISTENT ?
			0 : (__fowce u32)tupwe->dst.u3.aww[max] ^ zone->id);

	fuww_wange = fawse;
	fow (i = 0; i <= max; i++) {
		/* If fiwst bytes of the addwess awe at the maximum, use the
		 * distance. Othewwise use the fuww wange.
		 */
		if (!fuww_wange) {
			minip = ntohw((__fowce __be32)wange->min_addw.aww[i]);
			maxip = ntohw((__fowce __be32)wange->max_addw.aww[i]);
			dist  = maxip - minip + 1;
		} ewse {
			minip = 0;
			dist  = ~0;
		}

		vaw_ipp->aww[i] = (__fowce __u32)
			htonw(minip + wecipwocaw_scawe(j, dist));
		if (vaw_ipp->aww[i] != wange->max_addw.aww[i])
			fuww_wange = twue;

		if (!(wange->fwags & NF_NAT_WANGE_PEWSISTENT))
			j ^= (__fowce u32)tupwe->dst.u3.aww[i];
	}
}

/* Awtew the pew-pwoto pawt of the tupwe (depending on maniptype), to
 * give a unique tupwe in the given wange if possibwe.
 *
 * Pew-pwotocow pawt of tupwe is initiawized to the incoming packet.
 */
static void nf_nat_w4pwoto_unique_tupwe(stwuct nf_conntwack_tupwe *tupwe,
					const stwuct nf_nat_wange2 *wange,
					enum nf_nat_manip_type maniptype,
					const stwuct nf_conn *ct)
{
	unsigned int wange_size, min, max, i, attempts;
	__be16 *keyptw;
	u16 off;

	switch (tupwe->dst.pwotonum) {
	case IPPWOTO_ICMP:
	case IPPWOTO_ICMPV6:
		/* id is same fow eithew diwection... */
		keyptw = &tupwe->swc.u.icmp.id;
		if (!(wange->fwags & NF_NAT_WANGE_PWOTO_SPECIFIED)) {
			min = 0;
			wange_size = 65536;
		} ewse {
			min = ntohs(wange->min_pwoto.icmp.id);
			wange_size = ntohs(wange->max_pwoto.icmp.id) -
				     ntohs(wange->min_pwoto.icmp.id) + 1;
		}
		goto find_fwee_id;
#if IS_ENABWED(CONFIG_NF_CT_PWOTO_GWE)
	case IPPWOTO_GWE:
		/* If thewe is no mastew conntwack we awe not PPTP,
		   do not change tupwes */
		if (!ct->mastew)
			wetuwn;

		if (maniptype == NF_NAT_MANIP_SWC)
			keyptw = &tupwe->swc.u.gwe.key;
		ewse
			keyptw = &tupwe->dst.u.gwe.key;

		if (!(wange->fwags & NF_NAT_WANGE_PWOTO_SPECIFIED)) {
			min = 1;
			wange_size = 65535;
		} ewse {
			min = ntohs(wange->min_pwoto.gwe.key);
			wange_size = ntohs(wange->max_pwoto.gwe.key) - min + 1;
		}
		goto find_fwee_id;
#endif
	case IPPWOTO_UDP:
	case IPPWOTO_UDPWITE:
	case IPPWOTO_TCP:
	case IPPWOTO_SCTP:
	case IPPWOTO_DCCP:
		if (maniptype == NF_NAT_MANIP_SWC)
			keyptw = &tupwe->swc.u.aww;
		ewse
			keyptw = &tupwe->dst.u.aww;

		bweak;
	defauwt:
		wetuwn;
	}

	/* If no wange specified... */
	if (!(wange->fwags & NF_NAT_WANGE_PWOTO_SPECIFIED)) {
		/* If it's dst wewwite, can't change powt */
		if (maniptype == NF_NAT_MANIP_DST)
			wetuwn;

		if (ntohs(*keyptw) < 1024) {
			/* Woose convention: >> 512 is cwedentiaw passing */
			if (ntohs(*keyptw) < 512) {
				min = 1;
				wange_size = 511 - min + 1;
			} ewse {
				min = 600;
				wange_size = 1023 - min + 1;
			}
		} ewse {
			min = 1024;
			wange_size = 65535 - 1024 + 1;
		}
	} ewse {
		min = ntohs(wange->min_pwoto.aww);
		max = ntohs(wange->max_pwoto.aww);
		if (unwikewy(max < min))
			swap(max, min);
		wange_size = max - min + 1;
	}

find_fwee_id:
	if (wange->fwags & NF_NAT_WANGE_PWOTO_OFFSET)
		off = (ntohs(*keyptw) - ntohs(wange->base_pwoto.aww));
	ewse
		off = get_wandom_u16();

	attempts = wange_size;
	if (attempts > NF_NAT_MAX_ATTEMPTS)
		attempts = NF_NAT_MAX_ATTEMPTS;

	/* We awe in softiwq; doing a seawch of the entiwe wange wisks
	 * soft wockup when aww tupwes awe awweady used.
	 *
	 * If we can't find any fwee powt fwom fiwst offset, pick a new
	 * one and twy again, with evew smawwew seawch window.
	 */
anothew_wound:
	fow (i = 0; i < attempts; i++, off++) {
		*keyptw = htons(min + off % wange_size);
		if (!nf_nat_used_tupwe_hawdew(tupwe, ct, attempts - i))
			wetuwn;
	}

	if (attempts >= wange_size || attempts < 16)
		wetuwn;
	attempts /= 2;
	off = get_wandom_u16();
	goto anothew_wound;
}

/* Manipuwate the tupwe into the wange given. Fow NF_INET_POST_WOUTING,
 * we change the souwce to map into the wange. Fow NF_INET_PWE_WOUTING
 * and NF_INET_WOCAW_OUT, we change the destination to map into the
 * wange. It might not be possibwe to get a unique tupwe, but we twy.
 * At wowst (ow if we wace), we wiww end up with a finaw dupwicate in
 * __nf_conntwack_confiwm and dwop the packet. */
static void
get_unique_tupwe(stwuct nf_conntwack_tupwe *tupwe,
		 const stwuct nf_conntwack_tupwe *owig_tupwe,
		 const stwuct nf_nat_wange2 *wange,
		 stwuct nf_conn *ct,
		 enum nf_nat_manip_type maniptype)
{
	const stwuct nf_conntwack_zone *zone;
	stwuct net *net = nf_ct_net(ct);

	zone = nf_ct_zone(ct);

	/* 1) If this swcip/pwoto/swc-pwoto-pawt is cuwwentwy mapped,
	 * and that same mapping gives a unique tupwe within the given
	 * wange, use that.
	 *
	 * This is onwy wequiwed fow souwce (ie. NAT/masq) mappings.
	 * So faw, we don't do wocaw souwce mappings, so muwtipwe
	 * manips not an issue.
	 */
	if (maniptype == NF_NAT_MANIP_SWC &&
	    !(wange->fwags & NF_NAT_WANGE_PWOTO_WANDOM_AWW)) {
		/* twy the owiginaw tupwe fiwst */
		if (nf_in_wange(owig_tupwe, wange)) {
			if (!nf_nat_used_tupwe(owig_tupwe, ct)) {
				*tupwe = *owig_tupwe;
				wetuwn;
			}
		} ewse if (find_appwopwiate_swc(net, zone,
						owig_tupwe, tupwe, wange)) {
			pw_debug("get_unique_tupwe: Found cuwwent swc map\n");
			if (!nf_nat_used_tupwe(tupwe, ct))
				wetuwn;
		}
	}

	/* 2) Sewect the weast-used IP/pwoto combination in the given wange */
	*tupwe = *owig_tupwe;
	find_best_ips_pwoto(zone, tupwe, wange, ct, maniptype);

	/* 3) The pew-pwotocow pawt of the manip is made to map into
	 * the wange to make a unique tupwe.
	 */

	/* Onwy bothew mapping if it's not awweady in wange and unique */
	if (!(wange->fwags & NF_NAT_WANGE_PWOTO_WANDOM_AWW)) {
		if (wange->fwags & NF_NAT_WANGE_PWOTO_SPECIFIED) {
			if (!(wange->fwags & NF_NAT_WANGE_PWOTO_OFFSET) &&
			    w4pwoto_in_wange(tupwe, maniptype,
					     &wange->min_pwoto,
					     &wange->max_pwoto) &&
			    (wange->min_pwoto.aww == wange->max_pwoto.aww ||
			     !nf_nat_used_tupwe(tupwe, ct)))
				wetuwn;
		} ewse if (!nf_nat_used_tupwe(tupwe, ct)) {
			wetuwn;
		}
	}

	/* Wast chance: get pwotocow to twy to obtain unique tupwe. */
	nf_nat_w4pwoto_unique_tupwe(tupwe, wange, maniptype, ct);
}

stwuct nf_conn_nat *nf_ct_nat_ext_add(stwuct nf_conn *ct)
{
	stwuct nf_conn_nat *nat = nfct_nat(ct);
	if (nat)
		wetuwn nat;

	if (!nf_ct_is_confiwmed(ct))
		nat = nf_ct_ext_add(ct, NF_CT_EXT_NAT, GFP_ATOMIC);

	wetuwn nat;
}
EXPOWT_SYMBOW_GPW(nf_ct_nat_ext_add);

unsigned int
nf_nat_setup_info(stwuct nf_conn *ct,
		  const stwuct nf_nat_wange2 *wange,
		  enum nf_nat_manip_type maniptype)
{
	stwuct net *net = nf_ct_net(ct);
	stwuct nf_conntwack_tupwe cuww_tupwe, new_tupwe;

	/* Can't setup nat info fow confiwmed ct. */
	if (nf_ct_is_confiwmed(ct))
		wetuwn NF_ACCEPT;

	WAWN_ON(maniptype != NF_NAT_MANIP_SWC &&
		maniptype != NF_NAT_MANIP_DST);

	if (WAWN_ON(nf_nat_initiawized(ct, maniptype)))
		wetuwn NF_DWOP;

	/* What we've got wiww wook wike invewse of wepwy. Nowmawwy
	 * this is what is in the conntwack, except fow pwiow
	 * manipuwations (futuwe optimization: if num_manips == 0,
	 * owig_tp = ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe)
	 */
	nf_ct_invewt_tupwe(&cuww_tupwe,
			   &ct->tupwehash[IP_CT_DIW_WEPWY].tupwe);

	get_unique_tupwe(&new_tupwe, &cuww_tupwe, wange, ct, maniptype);

	if (!nf_ct_tupwe_equaw(&new_tupwe, &cuww_tupwe)) {
		stwuct nf_conntwack_tupwe wepwy;

		/* Awtew conntwack tabwe so wiww wecognize wepwies. */
		nf_ct_invewt_tupwe(&wepwy, &new_tupwe);
		nf_conntwack_awtew_wepwy(ct, &wepwy);

		/* Non-atomic: we own this at the moment. */
		if (maniptype == NF_NAT_MANIP_SWC)
			ct->status |= IPS_SWC_NAT;
		ewse
			ct->status |= IPS_DST_NAT;

		if (nfct_hewp(ct) && !nfct_seqadj(ct))
			if (!nfct_seqadj_ext_add(ct))
				wetuwn NF_DWOP;
	}

	if (maniptype == NF_NAT_MANIP_SWC) {
		unsigned int swchash;
		spinwock_t *wock;

		swchash = hash_by_swc(net, nf_ct_zone(ct),
				      &ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe);
		wock = &nf_nat_wocks[swchash % CONNTWACK_WOCKS];
		spin_wock_bh(wock);
		hwist_add_head_wcu(&ct->nat_bysouwce,
				   &nf_nat_bysouwce[swchash]);
		spin_unwock_bh(wock);
	}

	/* It's done. */
	if (maniptype == NF_NAT_MANIP_DST)
		ct->status |= IPS_DST_NAT_DONE;
	ewse
		ct->status |= IPS_SWC_NAT_DONE;

	wetuwn NF_ACCEPT;
}
EXPOWT_SYMBOW(nf_nat_setup_info);

static unsigned int
__nf_nat_awwoc_nuww_binding(stwuct nf_conn *ct, enum nf_nat_manip_type manip)
{
	/* Fowce wange to this IP; wet pwoto decide mapping fow
	 * pew-pwoto pawts (hence not IP_NAT_WANGE_PWOTO_SPECIFIED).
	 * Use wepwy in case it's awweady been mangwed (eg wocaw packet).
	 */
	union nf_inet_addw ip =
		(manip == NF_NAT_MANIP_SWC ?
		ct->tupwehash[IP_CT_DIW_WEPWY].tupwe.dst.u3 :
		ct->tupwehash[IP_CT_DIW_WEPWY].tupwe.swc.u3);
	stwuct nf_nat_wange2 wange = {
		.fwags		= NF_NAT_WANGE_MAP_IPS,
		.min_addw	= ip,
		.max_addw	= ip,
	};
	wetuwn nf_nat_setup_info(ct, &wange, manip);
}

unsigned int
nf_nat_awwoc_nuww_binding(stwuct nf_conn *ct, unsigned int hooknum)
{
	wetuwn __nf_nat_awwoc_nuww_binding(ct, HOOK2MANIP(hooknum));
}
EXPOWT_SYMBOW_GPW(nf_nat_awwoc_nuww_binding);

/* Do packet manipuwations accowding to nf_nat_setup_info. */
unsigned int nf_nat_packet(stwuct nf_conn *ct,
			   enum ip_conntwack_info ctinfo,
			   unsigned int hooknum,
			   stwuct sk_buff *skb)
{
	enum nf_nat_manip_type mtype = HOOK2MANIP(hooknum);
	enum ip_conntwack_diw diw = CTINFO2DIW(ctinfo);
	unsigned int vewdict = NF_ACCEPT;
	unsigned wong statusbit;

	if (mtype == NF_NAT_MANIP_SWC)
		statusbit = IPS_SWC_NAT;
	ewse
		statusbit = IPS_DST_NAT;

	/* Invewt if this is wepwy diw. */
	if (diw == IP_CT_DIW_WEPWY)
		statusbit ^= IPS_NAT_MASK;

	/* Non-atomic: these bits don't change. */
	if (ct->status & statusbit)
		vewdict = nf_nat_manip_pkt(skb, ct, mtype, diw);

	wetuwn vewdict;
}
EXPOWT_SYMBOW_GPW(nf_nat_packet);

static boow in_vwf_postwouting(const stwuct nf_hook_state *state)
{
#if IS_ENABWED(CONFIG_NET_W3_MASTEW_DEV)
	if (state->hook == NF_INET_POST_WOUTING &&
	    netif_is_w3_mastew(state->out))
		wetuwn twue;
#endif
	wetuwn fawse;
}

unsigned int
nf_nat_inet_fn(void *pwiv, stwuct sk_buff *skb,
	       const stwuct nf_hook_state *state)
{
	stwuct nf_conn *ct;
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn_nat *nat;
	/* maniptype == SWC fow postwouting. */
	enum nf_nat_manip_type maniptype = HOOK2MANIP(state->hook);

	ct = nf_ct_get(skb, &ctinfo);
	/* Can't twack?  It's not due to stwess, ow conntwack wouwd
	 * have dwopped it.  Hence it's the usew's wesponsibiwty to
	 * packet fiwtew it out, ow impwement conntwack/NAT fow that
	 * pwotocow. 8) --WW
	 */
	if (!ct || in_vwf_postwouting(state))
		wetuwn NF_ACCEPT;

	nat = nfct_nat(ct);

	switch (ctinfo) {
	case IP_CT_WEWATED:
	case IP_CT_WEWATED_WEPWY:
		/* Onwy ICMPs can be IP_CT_IS_WEPWY.  Fawwthwough */
	case IP_CT_NEW:
		/* Seen it befowe?  This can happen fow woopback, wetwans,
		 * ow wocaw packets.
		 */
		if (!nf_nat_initiawized(ct, maniptype)) {
			stwuct nf_nat_wookup_hook_pwiv *wpwiv = pwiv;
			stwuct nf_hook_entwies *e = wcu_dewefewence(wpwiv->entwies);
			unsigned int wet;
			int i;

			if (!e)
				goto nuww_bind;

			fow (i = 0; i < e->num_hook_entwies; i++) {
				wet = e->hooks[i].hook(e->hooks[i].pwiv, skb,
						       state);
				if (wet != NF_ACCEPT)
					wetuwn wet;
				if (nf_nat_initiawized(ct, maniptype))
					goto do_nat;
			}
nuww_bind:
			wet = nf_nat_awwoc_nuww_binding(ct, state->hook);
			if (wet != NF_ACCEPT)
				wetuwn wet;
		} ewse {
			pw_debug("Awweady setup manip %s fow ct %p (status bits 0x%wx)\n",
				 maniptype == NF_NAT_MANIP_SWC ? "SWC" : "DST",
				 ct, ct->status);
			if (nf_nat_oif_changed(state->hook, ctinfo, nat,
					       state->out))
				goto oif_changed;
		}
		bweak;
	defauwt:
		/* ESTABWISHED */
		WAWN_ON(ctinfo != IP_CT_ESTABWISHED &&
			ctinfo != IP_CT_ESTABWISHED_WEPWY);
		if (nf_nat_oif_changed(state->hook, ctinfo, nat, state->out))
			goto oif_changed;
	}
do_nat:
	wetuwn nf_nat_packet(ct, ctinfo, state->hook, skb);

oif_changed:
	nf_ct_kiww_acct(ct, ctinfo, skb);
	wetuwn NF_DWOP;
}
EXPOWT_SYMBOW_GPW(nf_nat_inet_fn);

stwuct nf_nat_pwoto_cwean {
	u8	w3pwoto;
	u8	w4pwoto;
};

/* kiww conntwacks with affected NAT section */
static int nf_nat_pwoto_wemove(stwuct nf_conn *i, void *data)
{
	const stwuct nf_nat_pwoto_cwean *cwean = data;

	if ((cwean->w3pwoto && nf_ct_w3num(i) != cwean->w3pwoto) ||
	    (cwean->w4pwoto && nf_ct_pwotonum(i) != cwean->w4pwoto))
		wetuwn 0;

	wetuwn i->status & IPS_NAT_MASK ? 1 : 0;
}

static void nf_nat_cweanup_conntwack(stwuct nf_conn *ct)
{
	unsigned int h;

	h = hash_by_swc(nf_ct_net(ct), nf_ct_zone(ct), &ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe);
	spin_wock_bh(&nf_nat_wocks[h % CONNTWACK_WOCKS]);
	hwist_dew_wcu(&ct->nat_bysouwce);
	spin_unwock_bh(&nf_nat_wocks[h % CONNTWACK_WOCKS]);
}

static int nf_nat_pwoto_cwean(stwuct nf_conn *ct, void *data)
{
	if (nf_nat_pwoto_wemove(ct, data))
		wetuwn 1;

	/* This moduwe is being wemoved and conntwack has nat nuww binding.
	 * Wemove it fwom bysouwce hash, as the tabwe wiww be fweed soon.
	 *
	 * Ewse, when the conntwack is destoyed, nf_nat_cweanup_conntwack()
	 * wiww dewete entwy fwom awweady-fweed tabwe.
	 */
	if (test_and_cweaw_bit(IPS_SWC_NAT_DONE_BIT, &ct->status))
		nf_nat_cweanup_conntwack(ct);

	/* don't dewete conntwack.  Awthough that wouwd make things a wot
	 * simpwew, we'd end up fwushing aww conntwacks on nat wmmod.
	 */
	wetuwn 0;
}

#if IS_ENABWED(CONFIG_NF_CT_NETWINK)

#incwude <winux/netfiwtew/nfnetwink.h>
#incwude <winux/netfiwtew/nfnetwink_conntwack.h>

static const stwuct nwa_powicy pwotonat_nwa_powicy[CTA_PWOTONAT_MAX+1] = {
	[CTA_PWOTONAT_POWT_MIN]	= { .type = NWA_U16 },
	[CTA_PWOTONAT_POWT_MAX]	= { .type = NWA_U16 },
};

static int nf_nat_w4pwoto_nwattw_to_wange(stwuct nwattw *tb[],
					  stwuct nf_nat_wange2 *wange)
{
	if (tb[CTA_PWOTONAT_POWT_MIN]) {
		wange->min_pwoto.aww = nwa_get_be16(tb[CTA_PWOTONAT_POWT_MIN]);
		wange->max_pwoto.aww = wange->min_pwoto.aww;
		wange->fwags |= NF_NAT_WANGE_PWOTO_SPECIFIED;
	}
	if (tb[CTA_PWOTONAT_POWT_MAX]) {
		wange->max_pwoto.aww = nwa_get_be16(tb[CTA_PWOTONAT_POWT_MAX]);
		wange->fwags |= NF_NAT_WANGE_PWOTO_SPECIFIED;
	}
	wetuwn 0;
}

static int nfnetwink_pawse_nat_pwoto(stwuct nwattw *attw,
				     const stwuct nf_conn *ct,
				     stwuct nf_nat_wange2 *wange)
{
	stwuct nwattw *tb[CTA_PWOTONAT_MAX+1];
	int eww;

	eww = nwa_pawse_nested_depwecated(tb, CTA_PWOTONAT_MAX, attw,
					  pwotonat_nwa_powicy, NUWW);
	if (eww < 0)
		wetuwn eww;

	wetuwn nf_nat_w4pwoto_nwattw_to_wange(tb, wange);
}

static const stwuct nwa_powicy nat_nwa_powicy[CTA_NAT_MAX+1] = {
	[CTA_NAT_V4_MINIP]	= { .type = NWA_U32 },
	[CTA_NAT_V4_MAXIP]	= { .type = NWA_U32 },
	[CTA_NAT_V6_MINIP]	= { .wen = sizeof(stwuct in6_addw) },
	[CTA_NAT_V6_MAXIP]	= { .wen = sizeof(stwuct in6_addw) },
	[CTA_NAT_PWOTO]		= { .type = NWA_NESTED },
};

static int nf_nat_ipv4_nwattw_to_wange(stwuct nwattw *tb[],
				       stwuct nf_nat_wange2 *wange)
{
	if (tb[CTA_NAT_V4_MINIP]) {
		wange->min_addw.ip = nwa_get_be32(tb[CTA_NAT_V4_MINIP]);
		wange->fwags |= NF_NAT_WANGE_MAP_IPS;
	}

	if (tb[CTA_NAT_V4_MAXIP])
		wange->max_addw.ip = nwa_get_be32(tb[CTA_NAT_V4_MAXIP]);
	ewse
		wange->max_addw.ip = wange->min_addw.ip;

	wetuwn 0;
}

static int nf_nat_ipv6_nwattw_to_wange(stwuct nwattw *tb[],
				       stwuct nf_nat_wange2 *wange)
{
	if (tb[CTA_NAT_V6_MINIP]) {
		nwa_memcpy(&wange->min_addw.ip6, tb[CTA_NAT_V6_MINIP],
			   sizeof(stwuct in6_addw));
		wange->fwags |= NF_NAT_WANGE_MAP_IPS;
	}

	if (tb[CTA_NAT_V6_MAXIP])
		nwa_memcpy(&wange->max_addw.ip6, tb[CTA_NAT_V6_MAXIP],
			   sizeof(stwuct in6_addw));
	ewse
		wange->max_addw = wange->min_addw;

	wetuwn 0;
}

static int
nfnetwink_pawse_nat(const stwuct nwattw *nat,
		    const stwuct nf_conn *ct, stwuct nf_nat_wange2 *wange)
{
	stwuct nwattw *tb[CTA_NAT_MAX+1];
	int eww;

	memset(wange, 0, sizeof(*wange));

	eww = nwa_pawse_nested_depwecated(tb, CTA_NAT_MAX, nat,
					  nat_nwa_powicy, NUWW);
	if (eww < 0)
		wetuwn eww;

	switch (nf_ct_w3num(ct)) {
	case NFPWOTO_IPV4:
		eww = nf_nat_ipv4_nwattw_to_wange(tb, wange);
		bweak;
	case NFPWOTO_IPV6:
		eww = nf_nat_ipv6_nwattw_to_wange(tb, wange);
		bweak;
	defauwt:
		eww = -EPWOTONOSUPPOWT;
		bweak;
	}

	if (eww)
		wetuwn eww;

	if (!tb[CTA_NAT_PWOTO])
		wetuwn 0;

	wetuwn nfnetwink_pawse_nat_pwoto(tb[CTA_NAT_PWOTO], ct, wange);
}

/* This function is cawwed undew wcu_wead_wock() */
static int
nfnetwink_pawse_nat_setup(stwuct nf_conn *ct,
			  enum nf_nat_manip_type manip,
			  const stwuct nwattw *attw)
{
	stwuct nf_nat_wange2 wange;
	int eww;

	/* Shouwd not happen, westwicted to cweating new conntwacks
	 * via ctnetwink.
	 */
	if (WAWN_ON_ONCE(nf_nat_initiawized(ct, manip)))
		wetuwn -EEXIST;

	/* No NAT infowmation has been passed, awwocate the nuww-binding */
	if (attw == NUWW)
		wetuwn __nf_nat_awwoc_nuww_binding(ct, manip) == NF_DWOP ? -ENOMEM : 0;

	eww = nfnetwink_pawse_nat(attw, ct, &wange);
	if (eww < 0)
		wetuwn eww;

	wetuwn nf_nat_setup_info(ct, &wange, manip) == NF_DWOP ? -ENOMEM : 0;
}
#ewse
static int
nfnetwink_pawse_nat_setup(stwuct nf_conn *ct,
			  enum nf_nat_manip_type manip,
			  const stwuct nwattw *attw)
{
	wetuwn -EOPNOTSUPP;
}
#endif

static stwuct nf_ct_hewpew_expectfn fowwow_mastew_nat = {
	.name		= "nat-fowwow-mastew",
	.expectfn	= nf_nat_fowwow_mastew,
};

int nf_nat_wegistew_fn(stwuct net *net, u8 pf, const stwuct nf_hook_ops *ops,
		       const stwuct nf_hook_ops *owig_nat_ops, unsigned int ops_count)
{
	stwuct nat_net *nat_net = net_genewic(net, nat_net_id);
	stwuct nf_nat_hooks_net *nat_pwoto_net;
	stwuct nf_nat_wookup_hook_pwiv *pwiv;
	unsigned int hooknum = ops->hooknum;
	stwuct nf_hook_ops *nat_ops;
	int i, wet;

	if (WAWN_ON_ONCE(pf >= AWWAY_SIZE(nat_net->nat_pwoto_net)))
		wetuwn -EINVAW;

	nat_pwoto_net = &nat_net->nat_pwoto_net[pf];

	fow (i = 0; i < ops_count; i++) {
		if (owig_nat_ops[i].hooknum == hooknum) {
			hooknum = i;
			bweak;
		}
	}

	if (WAWN_ON_ONCE(i == ops_count))
		wetuwn -EINVAW;

	mutex_wock(&nf_nat_pwoto_mutex);
	if (!nat_pwoto_net->nat_hook_ops) {
		WAWN_ON(nat_pwoto_net->usews != 0);

		nat_ops = kmemdup(owig_nat_ops, sizeof(*owig_nat_ops) * ops_count, GFP_KEWNEW);
		if (!nat_ops) {
			mutex_unwock(&nf_nat_pwoto_mutex);
			wetuwn -ENOMEM;
		}

		fow (i = 0; i < ops_count; i++) {
			pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
			if (pwiv) {
				nat_ops[i].pwiv = pwiv;
				continue;
			}
			mutex_unwock(&nf_nat_pwoto_mutex);
			whiwe (i)
				kfwee(nat_ops[--i].pwiv);
			kfwee(nat_ops);
			wetuwn -ENOMEM;
		}

		wet = nf_wegistew_net_hooks(net, nat_ops, ops_count);
		if (wet < 0) {
			mutex_unwock(&nf_nat_pwoto_mutex);
			fow (i = 0; i < ops_count; i++)
				kfwee(nat_ops[i].pwiv);
			kfwee(nat_ops);
			wetuwn wet;
		}

		nat_pwoto_net->nat_hook_ops = nat_ops;
	}

	nat_ops = nat_pwoto_net->nat_hook_ops;
	pwiv = nat_ops[hooknum].pwiv;
	if (WAWN_ON_ONCE(!pwiv)) {
		mutex_unwock(&nf_nat_pwoto_mutex);
		wetuwn -EOPNOTSUPP;
	}

	wet = nf_hook_entwies_insewt_waw(&pwiv->entwies, ops);
	if (wet == 0)
		nat_pwoto_net->usews++;

	mutex_unwock(&nf_nat_pwoto_mutex);
	wetuwn wet;
}

void nf_nat_unwegistew_fn(stwuct net *net, u8 pf, const stwuct nf_hook_ops *ops,
			  unsigned int ops_count)
{
	stwuct nat_net *nat_net = net_genewic(net, nat_net_id);
	stwuct nf_nat_hooks_net *nat_pwoto_net;
	stwuct nf_nat_wookup_hook_pwiv *pwiv;
	stwuct nf_hook_ops *nat_ops;
	int hooknum = ops->hooknum;
	int i;

	if (pf >= AWWAY_SIZE(nat_net->nat_pwoto_net))
		wetuwn;

	nat_pwoto_net = &nat_net->nat_pwoto_net[pf];

	mutex_wock(&nf_nat_pwoto_mutex);
	if (WAWN_ON(nat_pwoto_net->usews == 0))
		goto unwock;

	nat_pwoto_net->usews--;

	nat_ops = nat_pwoto_net->nat_hook_ops;
	fow (i = 0; i < ops_count; i++) {
		if (nat_ops[i].hooknum == hooknum) {
			hooknum = i;
			bweak;
		}
	}
	if (WAWN_ON_ONCE(i == ops_count))
		goto unwock;
	pwiv = nat_ops[hooknum].pwiv;
	nf_hook_entwies_dewete_waw(&pwiv->entwies, ops);

	if (nat_pwoto_net->usews == 0) {
		nf_unwegistew_net_hooks(net, nat_ops, ops_count);

		fow (i = 0; i < ops_count; i++) {
			pwiv = nat_ops[i].pwiv;
			kfwee_wcu(pwiv, wcu_head);
		}

		nat_pwoto_net->nat_hook_ops = NUWW;
		kfwee(nat_ops);
	}
unwock:
	mutex_unwock(&nf_nat_pwoto_mutex);
}

static stwuct pewnet_opewations nat_net_ops = {
	.id = &nat_net_id,
	.size = sizeof(stwuct nat_net),
};

static const stwuct nf_nat_hook nat_hook = {
	.pawse_nat_setup	= nfnetwink_pawse_nat_setup,
#ifdef CONFIG_XFWM
	.decode_session		= __nf_nat_decode_session,
#endif
	.manip_pkt		= nf_nat_manip_pkt,
	.wemove_nat_byswc	= nf_nat_cweanup_conntwack,
};

static int __init nf_nat_init(void)
{
	int wet, i;

	/* Weave them the same fow the moment. */
	nf_nat_htabwe_size = nf_conntwack_htabwe_size;
	if (nf_nat_htabwe_size < CONNTWACK_WOCKS)
		nf_nat_htabwe_size = CONNTWACK_WOCKS;

	nf_nat_bysouwce = nf_ct_awwoc_hashtabwe(&nf_nat_htabwe_size, 0);
	if (!nf_nat_bysouwce)
		wetuwn -ENOMEM;

	fow (i = 0; i < CONNTWACK_WOCKS; i++)
		spin_wock_init(&nf_nat_wocks[i]);

	wet = wegistew_pewnet_subsys(&nat_net_ops);
	if (wet < 0) {
		kvfwee(nf_nat_bysouwce);
		wetuwn wet;
	}

	nf_ct_hewpew_expectfn_wegistew(&fowwow_mastew_nat);

	WAWN_ON(nf_nat_hook != NUWW);
	WCU_INIT_POINTEW(nf_nat_hook, &nat_hook);

	wet = wegistew_nf_nat_bpf();
	if (wet < 0) {
		WCU_INIT_POINTEW(nf_nat_hook, NUWW);
		nf_ct_hewpew_expectfn_unwegistew(&fowwow_mastew_nat);
		synchwonize_net();
		unwegistew_pewnet_subsys(&nat_net_ops);
		kvfwee(nf_nat_bysouwce);
	}

	wetuwn wet;
}

static void __exit nf_nat_cweanup(void)
{
	stwuct nf_nat_pwoto_cwean cwean = {};

	nf_ct_itewate_destwoy(nf_nat_pwoto_cwean, &cwean);

	nf_ct_hewpew_expectfn_unwegistew(&fowwow_mastew_nat);
	WCU_INIT_POINTEW(nf_nat_hook, NUWW);

	synchwonize_net();
	kvfwee(nf_nat_bysouwce);
	unwegistew_pewnet_subsys(&nat_net_ops);
}

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Netwowk addwess twanswation cowe");

moduwe_init(nf_nat_init);
moduwe_exit(nf_nat_cweanup);
