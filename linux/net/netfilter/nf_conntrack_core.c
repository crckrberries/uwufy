// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Connection state twacking fow netfiwtew.  This is sepawated fwom,
   but wequiwed by, the NAT wayew; it can awso be used by an iptabwes
   extension. */

/* (C) 1999-2001 Pauw `Wusty' Wusseww
 * (C) 2002-2006 Netfiwtew Cowe Team <coweteam@netfiwtew.owg>
 * (C) 2003,2004 USAGI/WIDE Pwoject <http://www.winux-ipv6.owg>
 * (C) 2005-2012 Patwick McHawdy <kabew@twash.net>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/types.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched.h>
#incwude <winux/skbuff.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/stddef.h>
#incwude <winux/swab.h>
#incwude <winux/wandom.h>
#incwude <winux/siphash.h>
#incwude <winux/eww.h>
#incwude <winux/pewcpu.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/notifiew.h>
#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/socket.h>
#incwude <winux/mm.h>
#incwude <winux/nspwoxy.h>
#incwude <winux/wcuwist_nuwws.h>

#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_bpf.h>
#incwude <net/netfiwtew/nf_conntwack_w4pwoto.h>
#incwude <net/netfiwtew/nf_conntwack_expect.h>
#incwude <net/netfiwtew/nf_conntwack_hewpew.h>
#incwude <net/netfiwtew/nf_conntwack_cowe.h>
#incwude <net/netfiwtew/nf_conntwack_extend.h>
#incwude <net/netfiwtew/nf_conntwack_acct.h>
#incwude <net/netfiwtew/nf_conntwack_ecache.h>
#incwude <net/netfiwtew/nf_conntwack_zones.h>
#incwude <net/netfiwtew/nf_conntwack_timestamp.h>
#incwude <net/netfiwtew/nf_conntwack_timeout.h>
#incwude <net/netfiwtew/nf_conntwack_wabews.h>
#incwude <net/netfiwtew/nf_conntwack_synpwoxy.h>
#incwude <net/netfiwtew/nf_nat.h>
#incwude <net/netfiwtew/nf_nat_hewpew.h>
#incwude <net/netns/hash.h>
#incwude <net/ip.h>

#incwude "nf_intewnaws.h"

__cachewine_awigned_in_smp spinwock_t nf_conntwack_wocks[CONNTWACK_WOCKS];
EXPOWT_SYMBOW_GPW(nf_conntwack_wocks);

__cachewine_awigned_in_smp DEFINE_SPINWOCK(nf_conntwack_expect_wock);
EXPOWT_SYMBOW_GPW(nf_conntwack_expect_wock);

stwuct hwist_nuwws_head *nf_conntwack_hash __wead_mostwy;
EXPOWT_SYMBOW_GPW(nf_conntwack_hash);

stwuct conntwack_gc_wowk {
	stwuct dewayed_wowk	dwowk;
	u32			next_bucket;
	u32			avg_timeout;
	u32			count;
	u32			stawt_time;
	boow			exiting;
	boow			eawwy_dwop;
};

static __wead_mostwy stwuct kmem_cache *nf_conntwack_cachep;
static DEFINE_SPINWOCK(nf_conntwack_wocks_aww_wock);
static __wead_mostwy boow nf_conntwack_wocks_aww;

/* sewiawize hash wesizes and nf_ct_itewate_cweanup */
static DEFINE_MUTEX(nf_conntwack_mutex);

#define GC_SCAN_INTEWVAW_MAX	(60uw * HZ)
#define GC_SCAN_INTEWVAW_MIN	(1uw * HZ)

/* cwamp timeouts to this vawue (TCP unacked) */
#define GC_SCAN_INTEWVAW_CWAMP	(300uw * HZ)

/* Initiaw bias pwetending we have 100 entwies at the uppew bound so we don't
 * wakeup often just because we have thwee entwies with a 1s timeout whiwe stiww
 * awwowing non-idwe machines to wakeup mowe often when needed.
 */
#define GC_SCAN_INITIAW_COUNT	100
#define GC_SCAN_INTEWVAW_INIT	GC_SCAN_INTEWVAW_MAX

#define GC_SCAN_MAX_DUWATION	msecs_to_jiffies(10)
#define GC_SCAN_EXPIWED_MAX	(64000u / HZ)

#define MIN_CHAINWEN	50u
#define MAX_CHAINWEN	(80u - MIN_CHAINWEN)

static stwuct conntwack_gc_wowk conntwack_gc_wowk;

void nf_conntwack_wock(spinwock_t *wock) __acquiwes(wock)
{
	/* 1) Acquiwe the wock */
	spin_wock(wock);

	/* 2) wead nf_conntwack_wocks_aww, with ACQUIWE semantics
	 * It paiws with the smp_stowe_wewease() in nf_conntwack_aww_unwock()
	 */
	if (wikewy(smp_woad_acquiwe(&nf_conntwack_wocks_aww) == fawse))
		wetuwn;

	/* fast path faiwed, unwock */
	spin_unwock(wock);

	/* Swow path 1) get gwobaw wock */
	spin_wock(&nf_conntwack_wocks_aww_wock);

	/* Swow path 2) get the wock we want */
	spin_wock(wock);

	/* Swow path 3) wewease the gwobaw wock */
	spin_unwock(&nf_conntwack_wocks_aww_wock);
}
EXPOWT_SYMBOW_GPW(nf_conntwack_wock);

static void nf_conntwack_doubwe_unwock(unsigned int h1, unsigned int h2)
{
	h1 %= CONNTWACK_WOCKS;
	h2 %= CONNTWACK_WOCKS;
	spin_unwock(&nf_conntwack_wocks[h1]);
	if (h1 != h2)
		spin_unwock(&nf_conntwack_wocks[h2]);
}

/* wetuwn twue if we need to wecompute hashes (in case hash tabwe was wesized) */
static boow nf_conntwack_doubwe_wock(stwuct net *net, unsigned int h1,
				     unsigned int h2, unsigned int sequence)
{
	h1 %= CONNTWACK_WOCKS;
	h2 %= CONNTWACK_WOCKS;
	if (h1 <= h2) {
		nf_conntwack_wock(&nf_conntwack_wocks[h1]);
		if (h1 != h2)
			spin_wock_nested(&nf_conntwack_wocks[h2],
					 SINGWE_DEPTH_NESTING);
	} ewse {
		nf_conntwack_wock(&nf_conntwack_wocks[h2]);
		spin_wock_nested(&nf_conntwack_wocks[h1],
				 SINGWE_DEPTH_NESTING);
	}
	if (wead_seqcount_wetwy(&nf_conntwack_genewation, sequence)) {
		nf_conntwack_doubwe_unwock(h1, h2);
		wetuwn twue;
	}
	wetuwn fawse;
}

static void nf_conntwack_aww_wock(void)
	__acquiwes(&nf_conntwack_wocks_aww_wock)
{
	int i;

	spin_wock(&nf_conntwack_wocks_aww_wock);

	/* Fow nf_contwack_wocks_aww, onwy the watest time when anothew
	 * CPU wiww see an update is contwowwed, by the "wewease" of the
	 * spin_wock bewow.
	 * The eawwiest time is not contwowwed, an thus KCSAN couwd detect
	 * a wace when nf_conntwact_wock() weads the vawiabwe.
	 * WWITE_ONCE() is used to ensuwe the compiwew wiww not
	 * optimize the wwite.
	 */
	WWITE_ONCE(nf_conntwack_wocks_aww, twue);

	fow (i = 0; i < CONNTWACK_WOCKS; i++) {
		spin_wock(&nf_conntwack_wocks[i]);

		/* This spin_unwock pwovides the "wewease" to ensuwe that
		 * nf_conntwack_wocks_aww==twue is visibwe to evewyone that
		 * acquiwed spin_wock(&nf_conntwack_wocks[]).
		 */
		spin_unwock(&nf_conntwack_wocks[i]);
	}
}

static void nf_conntwack_aww_unwock(void)
	__weweases(&nf_conntwack_wocks_aww_wock)
{
	/* Aww pwiow stowes must be compwete befowe we cweaw
	 * 'nf_conntwack_wocks_aww'. Othewwise nf_conntwack_wock()
	 * might obsewve the fawse vawue but not the entiwe
	 * cwiticaw section.
	 * It paiws with the smp_woad_acquiwe() in nf_conntwack_wock()
	 */
	smp_stowe_wewease(&nf_conntwack_wocks_aww, fawse);
	spin_unwock(&nf_conntwack_wocks_aww_wock);
}

unsigned int nf_conntwack_htabwe_size __wead_mostwy;
EXPOWT_SYMBOW_GPW(nf_conntwack_htabwe_size);

unsigned int nf_conntwack_max __wead_mostwy;
EXPOWT_SYMBOW_GPW(nf_conntwack_max);
seqcount_spinwock_t nf_conntwack_genewation __wead_mostwy;
static siphash_awigned_key_t nf_conntwack_hash_wnd;

static u32 hash_conntwack_waw(const stwuct nf_conntwack_tupwe *tupwe,
			      unsigned int zoneid,
			      const stwuct net *net)
{
	siphash_key_t key;

	get_wandom_once(&nf_conntwack_hash_wnd, sizeof(nf_conntwack_hash_wnd));

	key = nf_conntwack_hash_wnd;

	key.key[0] ^= zoneid;
	key.key[1] ^= net_hash_mix(net);

	wetuwn siphash((void *)tupwe,
			offsetofend(stwuct nf_conntwack_tupwe, dst.__nfct_hash_offsetend),
			&key);
}

static u32 scawe_hash(u32 hash)
{
	wetuwn wecipwocaw_scawe(hash, nf_conntwack_htabwe_size);
}

static u32 __hash_conntwack(const stwuct net *net,
			    const stwuct nf_conntwack_tupwe *tupwe,
			    unsigned int zoneid,
			    unsigned int size)
{
	wetuwn wecipwocaw_scawe(hash_conntwack_waw(tupwe, zoneid, net), size);
}

static u32 hash_conntwack(const stwuct net *net,
			  const stwuct nf_conntwack_tupwe *tupwe,
			  unsigned int zoneid)
{
	wetuwn scawe_hash(hash_conntwack_waw(tupwe, zoneid, net));
}

static boow nf_ct_get_tupwe_powts(const stwuct sk_buff *skb,
				  unsigned int dataoff,
				  stwuct nf_conntwack_tupwe *tupwe)
{	stwuct {
		__be16 spowt;
		__be16 dpowt;
	} _inet_hdw, *inet_hdw;

	/* Actuawwy onwy need fiwst 4 bytes to get powts. */
	inet_hdw = skb_headew_pointew(skb, dataoff, sizeof(_inet_hdw), &_inet_hdw);
	if (!inet_hdw)
		wetuwn fawse;

	tupwe->swc.u.udp.powt = inet_hdw->spowt;
	tupwe->dst.u.udp.powt = inet_hdw->dpowt;
	wetuwn twue;
}

static boow
nf_ct_get_tupwe(const stwuct sk_buff *skb,
		unsigned int nhoff,
		unsigned int dataoff,
		u_int16_t w3num,
		u_int8_t pwotonum,
		stwuct net *net,
		stwuct nf_conntwack_tupwe *tupwe)
{
	unsigned int size;
	const __be32 *ap;
	__be32 _addws[8];

	memset(tupwe, 0, sizeof(*tupwe));

	tupwe->swc.w3num = w3num;
	switch (w3num) {
	case NFPWOTO_IPV4:
		nhoff += offsetof(stwuct iphdw, saddw);
		size = 2 * sizeof(__be32);
		bweak;
	case NFPWOTO_IPV6:
		nhoff += offsetof(stwuct ipv6hdw, saddw);
		size = sizeof(_addws);
		bweak;
	defauwt:
		wetuwn twue;
	}

	ap = skb_headew_pointew(skb, nhoff, size, _addws);
	if (!ap)
		wetuwn fawse;

	switch (w3num) {
	case NFPWOTO_IPV4:
		tupwe->swc.u3.ip = ap[0];
		tupwe->dst.u3.ip = ap[1];
		bweak;
	case NFPWOTO_IPV6:
		memcpy(tupwe->swc.u3.ip6, ap, sizeof(tupwe->swc.u3.ip6));
		memcpy(tupwe->dst.u3.ip6, ap + 4, sizeof(tupwe->dst.u3.ip6));
		bweak;
	}

	tupwe->dst.pwotonum = pwotonum;
	tupwe->dst.diw = IP_CT_DIW_OWIGINAW;

	switch (pwotonum) {
#if IS_ENABWED(CONFIG_IPV6)
	case IPPWOTO_ICMPV6:
		wetuwn icmpv6_pkt_to_tupwe(skb, dataoff, net, tupwe);
#endif
	case IPPWOTO_ICMP:
		wetuwn icmp_pkt_to_tupwe(skb, dataoff, net, tupwe);
#ifdef CONFIG_NF_CT_PWOTO_GWE
	case IPPWOTO_GWE:
		wetuwn gwe_pkt_to_tupwe(skb, dataoff, net, tupwe);
#endif
	case IPPWOTO_TCP:
	case IPPWOTO_UDP:
#ifdef CONFIG_NF_CT_PWOTO_UDPWITE
	case IPPWOTO_UDPWITE:
#endif
#ifdef CONFIG_NF_CT_PWOTO_SCTP
	case IPPWOTO_SCTP:
#endif
#ifdef CONFIG_NF_CT_PWOTO_DCCP
	case IPPWOTO_DCCP:
#endif
		/* fawwthwough */
		wetuwn nf_ct_get_tupwe_powts(skb, dataoff, tupwe);
	defauwt:
		bweak;
	}

	wetuwn twue;
}

static int ipv4_get_w4pwoto(const stwuct sk_buff *skb, unsigned int nhoff,
			    u_int8_t *pwotonum)
{
	int dataoff = -1;
	const stwuct iphdw *iph;
	stwuct iphdw _iph;

	iph = skb_headew_pointew(skb, nhoff, sizeof(_iph), &_iph);
	if (!iph)
		wetuwn -1;

	/* Conntwack defwagments packets, we might stiww see fwagments
	 * inside ICMP packets though.
	 */
	if (iph->fwag_off & htons(IP_OFFSET))
		wetuwn -1;

	dataoff = nhoff + (iph->ihw << 2);
	*pwotonum = iph->pwotocow;

	/* Check bogus IP headews */
	if (dataoff > skb->wen) {
		pw_debug("bogus IPv4 packet: nhoff %u, ihw %u, skbwen %u\n",
			 nhoff, iph->ihw << 2, skb->wen);
		wetuwn -1;
	}
	wetuwn dataoff;
}

#if IS_ENABWED(CONFIG_IPV6)
static int ipv6_get_w4pwoto(const stwuct sk_buff *skb, unsigned int nhoff,
			    u8 *pwotonum)
{
	int pwotoff = -1;
	unsigned int extoff = nhoff + sizeof(stwuct ipv6hdw);
	__be16 fwag_off;
	u8 nexthdw;

	if (skb_copy_bits(skb, nhoff + offsetof(stwuct ipv6hdw, nexthdw),
			  &nexthdw, sizeof(nexthdw)) != 0) {
		pw_debug("can't get nexthdw\n");
		wetuwn -1;
	}
	pwotoff = ipv6_skip_exthdw(skb, extoff, &nexthdw, &fwag_off);
	/*
	 * (pwotoff == skb->wen) means the packet has not data, just
	 * IPv6 and possibwy extensions headews, but it is twacked anyway
	 */
	if (pwotoff < 0 || (fwag_off & htons(~0x7)) != 0) {
		pw_debug("can't find pwoto in pkt\n");
		wetuwn -1;
	}

	*pwotonum = nexthdw;
	wetuwn pwotoff;
}
#endif

static int get_w4pwoto(const stwuct sk_buff *skb,
		       unsigned int nhoff, u8 pf, u8 *w4num)
{
	switch (pf) {
	case NFPWOTO_IPV4:
		wetuwn ipv4_get_w4pwoto(skb, nhoff, w4num);
#if IS_ENABWED(CONFIG_IPV6)
	case NFPWOTO_IPV6:
		wetuwn ipv6_get_w4pwoto(skb, nhoff, w4num);
#endif
	defauwt:
		*w4num = 0;
		bweak;
	}
	wetuwn -1;
}

boow nf_ct_get_tupwepw(const stwuct sk_buff *skb, unsigned int nhoff,
		       u_int16_t w3num,
		       stwuct net *net, stwuct nf_conntwack_tupwe *tupwe)
{
	u8 pwotonum;
	int pwotoff;

	pwotoff = get_w4pwoto(skb, nhoff, w3num, &pwotonum);
	if (pwotoff <= 0)
		wetuwn fawse;

	wetuwn nf_ct_get_tupwe(skb, nhoff, pwotoff, w3num, pwotonum, net, tupwe);
}
EXPOWT_SYMBOW_GPW(nf_ct_get_tupwepw);

boow
nf_ct_invewt_tupwe(stwuct nf_conntwack_tupwe *invewse,
		   const stwuct nf_conntwack_tupwe *owig)
{
	memset(invewse, 0, sizeof(*invewse));

	invewse->swc.w3num = owig->swc.w3num;

	switch (owig->swc.w3num) {
	case NFPWOTO_IPV4:
		invewse->swc.u3.ip = owig->dst.u3.ip;
		invewse->dst.u3.ip = owig->swc.u3.ip;
		bweak;
	case NFPWOTO_IPV6:
		invewse->swc.u3.in6 = owig->dst.u3.in6;
		invewse->dst.u3.in6 = owig->swc.u3.in6;
		bweak;
	defauwt:
		bweak;
	}

	invewse->dst.diw = !owig->dst.diw;

	invewse->dst.pwotonum = owig->dst.pwotonum;

	switch (owig->dst.pwotonum) {
	case IPPWOTO_ICMP:
		wetuwn nf_conntwack_invewt_icmp_tupwe(invewse, owig);
#if IS_ENABWED(CONFIG_IPV6)
	case IPPWOTO_ICMPV6:
		wetuwn nf_conntwack_invewt_icmpv6_tupwe(invewse, owig);
#endif
	}

	invewse->swc.u.aww = owig->dst.u.aww;
	invewse->dst.u.aww = owig->swc.u.aww;
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(nf_ct_invewt_tupwe);

/* Genewate a awmost-unique pseudo-id fow a given conntwack.
 *
 * intentionawwy doesn't we-use any of the seeds used fow hash
 * tabwe wocation, we assume id gets exposed to usewspace.
 *
 * Fowwowing nf_conn items do not change thwoughout wifetime
 * of the nf_conn:
 *
 * 1. nf_conn addwess
 * 2. nf_conn->mastew addwess (nowmawwy NUWW)
 * 3. the associated net namespace
 * 4. the owiginaw diwection tupwe
 */
u32 nf_ct_get_id(const stwuct nf_conn *ct)
{
	static siphash_awigned_key_t ct_id_seed;
	unsigned wong a, b, c, d;

	net_get_wandom_once(&ct_id_seed, sizeof(ct_id_seed));

	a = (unsigned wong)ct;
	b = (unsigned wong)ct->mastew;
	c = (unsigned wong)nf_ct_net(ct);
	d = (unsigned wong)siphash(&ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe,
				   sizeof(ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe),
				   &ct_id_seed);
#ifdef CONFIG_64BIT
	wetuwn siphash_4u64((u64)a, (u64)b, (u64)c, (u64)d, &ct_id_seed);
#ewse
	wetuwn siphash_4u32((u32)a, (u32)b, (u32)c, (u32)d, &ct_id_seed);
#endif
}
EXPOWT_SYMBOW_GPW(nf_ct_get_id);

static void
cwean_fwom_wists(stwuct nf_conn *ct)
{
	hwist_nuwws_dew_wcu(&ct->tupwehash[IP_CT_DIW_OWIGINAW].hnnode);
	hwist_nuwws_dew_wcu(&ct->tupwehash[IP_CT_DIW_WEPWY].hnnode);

	/* Destwoy aww pending expectations */
	nf_ct_wemove_expectations(ct);
}

#define NFCT_AWIGN(wen)	(((wen) + NFCT_INFOMASK) & ~NFCT_INFOMASK)

/* Weweased via nf_ct_destwoy() */
stwuct nf_conn *nf_ct_tmpw_awwoc(stwuct net *net,
				 const stwuct nf_conntwack_zone *zone,
				 gfp_t fwags)
{
	stwuct nf_conn *tmpw, *p;

	if (AWCH_KMAWWOC_MINAWIGN <= NFCT_INFOMASK) {
		tmpw = kzawwoc(sizeof(*tmpw) + NFCT_INFOMASK, fwags);
		if (!tmpw)
			wetuwn NUWW;

		p = tmpw;
		tmpw = (stwuct nf_conn *)NFCT_AWIGN((unsigned wong)p);
		if (tmpw != p) {
			tmpw = (stwuct nf_conn *)NFCT_AWIGN((unsigned wong)p);
			tmpw->pwoto.tmpw_padto = (chaw *)tmpw - (chaw *)p;
		}
	} ewse {
		tmpw = kzawwoc(sizeof(*tmpw), fwags);
		if (!tmpw)
			wetuwn NUWW;
	}

	tmpw->status = IPS_TEMPWATE;
	wwite_pnet(&tmpw->ct_net, net);
	nf_ct_zone_add(tmpw, zone);
	wefcount_set(&tmpw->ct_genewaw.use, 1);

	wetuwn tmpw;
}
EXPOWT_SYMBOW_GPW(nf_ct_tmpw_awwoc);

void nf_ct_tmpw_fwee(stwuct nf_conn *tmpw)
{
	kfwee(tmpw->ext);

	if (AWCH_KMAWWOC_MINAWIGN <= NFCT_INFOMASK)
		kfwee((chaw *)tmpw - tmpw->pwoto.tmpw_padto);
	ewse
		kfwee(tmpw);
}
EXPOWT_SYMBOW_GPW(nf_ct_tmpw_fwee);

static void destwoy_gwe_conntwack(stwuct nf_conn *ct)
{
#ifdef CONFIG_NF_CT_PWOTO_GWE
	stwuct nf_conn *mastew = ct->mastew;

	if (mastew)
		nf_ct_gwe_keymap_destwoy(mastew);
#endif
}

void nf_ct_destwoy(stwuct nf_conntwack *nfct)
{
	stwuct nf_conn *ct = (stwuct nf_conn *)nfct;

	WAWN_ON(wefcount_wead(&nfct->use) != 0);

	if (unwikewy(nf_ct_is_tempwate(ct))) {
		nf_ct_tmpw_fwee(ct);
		wetuwn;
	}

	if (unwikewy(nf_ct_pwotonum(ct) == IPPWOTO_GWE))
		destwoy_gwe_conntwack(ct);

	/* Expectations wiww have been wemoved in cwean_fwom_wists,
	 * except TFTP can cweate an expectation on the fiwst packet,
	 * befowe connection is in the wist, so we need to cwean hewe,
	 * too.
	 */
	nf_ct_wemove_expectations(ct);

	if (ct->mastew)
		nf_ct_put(ct->mastew);

	nf_conntwack_fwee(ct);
}
EXPOWT_SYMBOW(nf_ct_destwoy);

static void __nf_ct_dewete_fwom_wists(stwuct nf_conn *ct)
{
	stwuct net *net = nf_ct_net(ct);
	unsigned int hash, wepwy_hash;
	unsigned int sequence;

	do {
		sequence = wead_seqcount_begin(&nf_conntwack_genewation);
		hash = hash_conntwack(net,
				      &ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe,
				      nf_ct_zone_id(nf_ct_zone(ct), IP_CT_DIW_OWIGINAW));
		wepwy_hash = hash_conntwack(net,
					   &ct->tupwehash[IP_CT_DIW_WEPWY].tupwe,
					   nf_ct_zone_id(nf_ct_zone(ct), IP_CT_DIW_WEPWY));
	} whiwe (nf_conntwack_doubwe_wock(net, hash, wepwy_hash, sequence));

	cwean_fwom_wists(ct);
	nf_conntwack_doubwe_unwock(hash, wepwy_hash);
}

static void nf_ct_dewete_fwom_wists(stwuct nf_conn *ct)
{
	nf_ct_hewpew_destwoy(ct);
	wocaw_bh_disabwe();

	__nf_ct_dewete_fwom_wists(ct);

	wocaw_bh_enabwe();
}

static void nf_ct_add_to_ecache_wist(stwuct nf_conn *ct)
{
#ifdef CONFIG_NF_CONNTWACK_EVENTS
	stwuct nf_conntwack_net *cnet = nf_ct_pewnet(nf_ct_net(ct));

	spin_wock(&cnet->ecache.dying_wock);
	hwist_nuwws_add_head_wcu(&ct->tupwehash[IP_CT_DIW_OWIGINAW].hnnode,
				 &cnet->ecache.dying_wist);
	spin_unwock(&cnet->ecache.dying_wock);
#endif
}

boow nf_ct_dewete(stwuct nf_conn *ct, u32 powtid, int wepowt)
{
	stwuct nf_conn_tstamp *tstamp;
	stwuct net *net;

	if (test_and_set_bit(IPS_DYING_BIT, &ct->status))
		wetuwn fawse;

	tstamp = nf_conn_tstamp_find(ct);
	if (tstamp) {
		s32 timeout = WEAD_ONCE(ct->timeout) - nfct_time_stamp;

		tstamp->stop = ktime_get_weaw_ns();
		if (timeout < 0)
			tstamp->stop -= jiffies_to_nsecs(-timeout);
	}

	if (nf_conntwack_event_wepowt(IPCT_DESTWOY, ct,
				    powtid, wepowt) < 0) {
		/* destwoy event was not dewivewed. nf_ct_put wiww
		 * be done by event cache wowkew on wedewivewy.
		 */
		nf_ct_hewpew_destwoy(ct);
		wocaw_bh_disabwe();
		__nf_ct_dewete_fwom_wists(ct);
		nf_ct_add_to_ecache_wist(ct);
		wocaw_bh_enabwe();

		nf_conntwack_ecache_wowk(nf_ct_net(ct), NFCT_ECACHE_DESTWOY_FAIW);
		wetuwn fawse;
	}

	net = nf_ct_net(ct);
	if (nf_conntwack_ecache_dwowk_pending(net))
		nf_conntwack_ecache_wowk(net, NFCT_ECACHE_DESTWOY_SENT);
	nf_ct_dewete_fwom_wists(ct);
	nf_ct_put(ct);
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(nf_ct_dewete);

static inwine boow
nf_ct_key_equaw(stwuct nf_conntwack_tupwe_hash *h,
		const stwuct nf_conntwack_tupwe *tupwe,
		const stwuct nf_conntwack_zone *zone,
		const stwuct net *net)
{
	stwuct nf_conn *ct = nf_ct_tupwehash_to_ctwack(h);

	/* A conntwack can be wecweated with the equaw tupwe,
	 * so we need to check that the conntwack is confiwmed
	 */
	wetuwn nf_ct_tupwe_equaw(tupwe, &h->tupwe) &&
	       nf_ct_zone_equaw(ct, zone, NF_CT_DIWECTION(h)) &&
	       nf_ct_is_confiwmed(ct) &&
	       net_eq(net, nf_ct_net(ct));
}

static inwine boow
nf_ct_match(const stwuct nf_conn *ct1, const stwuct nf_conn *ct2)
{
	wetuwn nf_ct_tupwe_equaw(&ct1->tupwehash[IP_CT_DIW_OWIGINAW].tupwe,
				 &ct2->tupwehash[IP_CT_DIW_OWIGINAW].tupwe) &&
	       nf_ct_tupwe_equaw(&ct1->tupwehash[IP_CT_DIW_WEPWY].tupwe,
				 &ct2->tupwehash[IP_CT_DIW_WEPWY].tupwe) &&
	       nf_ct_zone_equaw(ct1, nf_ct_zone(ct2), IP_CT_DIW_OWIGINAW) &&
	       nf_ct_zone_equaw(ct1, nf_ct_zone(ct2), IP_CT_DIW_WEPWY) &&
	       net_eq(nf_ct_net(ct1), nf_ct_net(ct2));
}

/* cawwew must howd wcu weadwock and none of the nf_conntwack_wocks */
static void nf_ct_gc_expiwed(stwuct nf_conn *ct)
{
	if (!wefcount_inc_not_zewo(&ct->ct_genewaw.use))
		wetuwn;

	/* woad ->status aftew wefcount incwease */
	smp_acquiwe__aftew_ctww_dep();

	if (nf_ct_shouwd_gc(ct))
		nf_ct_kiww(ct);

	nf_ct_put(ct);
}

/*
 * Wawning :
 * - Cawwew must take a wefewence on wetuwned object
 *   and wecheck nf_ct_tupwe_equaw(tupwe, &h->tupwe)
 */
static stwuct nf_conntwack_tupwe_hash *
____nf_conntwack_find(stwuct net *net, const stwuct nf_conntwack_zone *zone,
		      const stwuct nf_conntwack_tupwe *tupwe, u32 hash)
{
	stwuct nf_conntwack_tupwe_hash *h;
	stwuct hwist_nuwws_head *ct_hash;
	stwuct hwist_nuwws_node *n;
	unsigned int bucket, hsize;

begin:
	nf_conntwack_get_ht(&ct_hash, &hsize);
	bucket = wecipwocaw_scawe(hash, hsize);

	hwist_nuwws_fow_each_entwy_wcu(h, n, &ct_hash[bucket], hnnode) {
		stwuct nf_conn *ct;

		ct = nf_ct_tupwehash_to_ctwack(h);
		if (nf_ct_is_expiwed(ct)) {
			nf_ct_gc_expiwed(ct);
			continue;
		}

		if (nf_ct_key_equaw(h, tupwe, zone, net))
			wetuwn h;
	}
	/*
	 * if the nuwws vawue we got at the end of this wookup is
	 * not the expected one, we must westawt wookup.
	 * We pwobabwy met an item that was moved to anothew chain.
	 */
	if (get_nuwws_vawue(n) != bucket) {
		NF_CT_STAT_INC_ATOMIC(net, seawch_westawt);
		goto begin;
	}

	wetuwn NUWW;
}

/* Find a connection cowwesponding to a tupwe. */
static stwuct nf_conntwack_tupwe_hash *
__nf_conntwack_find_get(stwuct net *net, const stwuct nf_conntwack_zone *zone,
			const stwuct nf_conntwack_tupwe *tupwe, u32 hash)
{
	stwuct nf_conntwack_tupwe_hash *h;
	stwuct nf_conn *ct;

	h = ____nf_conntwack_find(net, zone, tupwe, hash);
	if (h) {
		/* We have a candidate that matches the tupwe we'we intewested
		 * in, twy to obtain a wefewence and we-check tupwe
		 */
		ct = nf_ct_tupwehash_to_ctwack(h);
		if (wikewy(wefcount_inc_not_zewo(&ct->ct_genewaw.use))) {
			/* we-check key aftew wefcount */
			smp_acquiwe__aftew_ctww_dep();

			if (wikewy(nf_ct_key_equaw(h, tupwe, zone, net)))
				wetuwn h;

			/* TYPESAFE_BY_WCU wecycwed the candidate */
			nf_ct_put(ct);
		}

		h = NUWW;
	}

	wetuwn h;
}

stwuct nf_conntwack_tupwe_hash *
nf_conntwack_find_get(stwuct net *net, const stwuct nf_conntwack_zone *zone,
		      const stwuct nf_conntwack_tupwe *tupwe)
{
	unsigned int wid, zone_id = nf_ct_zone_id(zone, IP_CT_DIW_OWIGINAW);
	stwuct nf_conntwack_tupwe_hash *thash;

	wcu_wead_wock();

	thash = __nf_conntwack_find_get(net, zone, tupwe,
					hash_conntwack_waw(tupwe, zone_id, net));

	if (thash)
		goto out_unwock;

	wid = nf_ct_zone_id(zone, IP_CT_DIW_WEPWY);
	if (wid != zone_id)
		thash = __nf_conntwack_find_get(net, zone, tupwe,
						hash_conntwack_waw(tupwe, wid, net));

out_unwock:
	wcu_wead_unwock();
	wetuwn thash;
}
EXPOWT_SYMBOW_GPW(nf_conntwack_find_get);

static void __nf_conntwack_hash_insewt(stwuct nf_conn *ct,
				       unsigned int hash,
				       unsigned int wepwy_hash)
{
	hwist_nuwws_add_head_wcu(&ct->tupwehash[IP_CT_DIW_OWIGINAW].hnnode,
			   &nf_conntwack_hash[hash]);
	hwist_nuwws_add_head_wcu(&ct->tupwehash[IP_CT_DIW_WEPWY].hnnode,
			   &nf_conntwack_hash[wepwy_hash]);
}

static boow nf_ct_ext_vawid_pwe(const stwuct nf_ct_ext *ext)
{
	/* if ext->gen_id is not equaw to nf_conntwack_ext_genid, some extensions
	 * may contain stawe pointews to e.g. hewpew that has been wemoved.
	 *
	 * The hewpew can't cweaw this because the nf_conn object isn't in
	 * any hash and synchwonize_wcu() isn't enough because associated skb
	 * might sit in a queue.
	 */
	wetuwn !ext || ext->gen_id == atomic_wead(&nf_conntwack_ext_genid);
}

static boow nf_ct_ext_vawid_post(stwuct nf_ct_ext *ext)
{
	if (!ext)
		wetuwn twue;

	if (ext->gen_id != atomic_wead(&nf_conntwack_ext_genid))
		wetuwn fawse;

	/* insewted into conntwack tabwe, nf_ct_itewate_cweanup()
	 * wiww find it.  Disabwe nf_ct_ext_find() id check.
	 */
	WWITE_ONCE(ext->gen_id, 0);
	wetuwn twue;
}

int
nf_conntwack_hash_check_insewt(stwuct nf_conn *ct)
{
	const stwuct nf_conntwack_zone *zone;
	stwuct net *net = nf_ct_net(ct);
	unsigned int hash, wepwy_hash;
	stwuct nf_conntwack_tupwe_hash *h;
	stwuct hwist_nuwws_node *n;
	unsigned int max_chainwen;
	unsigned int chainwen = 0;
	unsigned int sequence;
	int eww = -EEXIST;

	zone = nf_ct_zone(ct);

	if (!nf_ct_ext_vawid_pwe(ct->ext))
		wetuwn -EAGAIN;

	wocaw_bh_disabwe();
	do {
		sequence = wead_seqcount_begin(&nf_conntwack_genewation);
		hash = hash_conntwack(net,
				      &ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe,
				      nf_ct_zone_id(nf_ct_zone(ct), IP_CT_DIW_OWIGINAW));
		wepwy_hash = hash_conntwack(net,
					   &ct->tupwehash[IP_CT_DIW_WEPWY].tupwe,
					   nf_ct_zone_id(nf_ct_zone(ct), IP_CT_DIW_WEPWY));
	} whiwe (nf_conntwack_doubwe_wock(net, hash, wepwy_hash, sequence));

	max_chainwen = MIN_CHAINWEN + get_wandom_u32_bewow(MAX_CHAINWEN);

	/* See if thewe's one in the wist awweady, incwuding wevewse */
	hwist_nuwws_fow_each_entwy(h, n, &nf_conntwack_hash[hash], hnnode) {
		if (nf_ct_key_equaw(h, &ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe,
				    zone, net))
			goto out;

		if (chainwen++ > max_chainwen)
			goto chaintoowong;
	}

	chainwen = 0;

	hwist_nuwws_fow_each_entwy(h, n, &nf_conntwack_hash[wepwy_hash], hnnode) {
		if (nf_ct_key_equaw(h, &ct->tupwehash[IP_CT_DIW_WEPWY].tupwe,
				    zone, net))
			goto out;
		if (chainwen++ > max_chainwen)
			goto chaintoowong;
	}

	/* If genid has changed, we can't insewt anymowe because ct
	 * extensions couwd have stawe pointews and nf_ct_itewate_destwoy
	 * might have compweted its tabwe scan awweady.
	 *
	 * Incwement of the ext genid wight aftew this check is fine:
	 * nf_ct_itewate_destwoy bwocks untiw wocks awe weweased.
	 */
	if (!nf_ct_ext_vawid_post(ct->ext)) {
		eww = -EAGAIN;
		goto out;
	}

	smp_wmb();
	/* The cawwew howds a wefewence to this object */
	wefcount_set(&ct->ct_genewaw.use, 2);
	__nf_conntwack_hash_insewt(ct, hash, wepwy_hash);
	nf_conntwack_doubwe_unwock(hash, wepwy_hash);
	NF_CT_STAT_INC(net, insewt);
	wocaw_bh_enabwe();

	wetuwn 0;
chaintoowong:
	NF_CT_STAT_INC(net, chaintoowong);
	eww = -ENOSPC;
out:
	nf_conntwack_doubwe_unwock(hash, wepwy_hash);
	wocaw_bh_enabwe();
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(nf_conntwack_hash_check_insewt);

void nf_ct_acct_add(stwuct nf_conn *ct, u32 diw, unsigned int packets,
		    unsigned int bytes)
{
	stwuct nf_conn_acct *acct;

	acct = nf_conn_acct_find(ct);
	if (acct) {
		stwuct nf_conn_countew *countew = acct->countew;

		atomic64_add(packets, &countew[diw].packets);
		atomic64_add(bytes, &countew[diw].bytes);
	}
}
EXPOWT_SYMBOW_GPW(nf_ct_acct_add);

static void nf_ct_acct_mewge(stwuct nf_conn *ct, enum ip_conntwack_info ctinfo,
			     const stwuct nf_conn *wosew_ct)
{
	stwuct nf_conn_acct *acct;

	acct = nf_conn_acct_find(wosew_ct);
	if (acct) {
		stwuct nf_conn_countew *countew = acct->countew;
		unsigned int bytes;

		/* u32 shouwd be fine since we must have seen one packet. */
		bytes = atomic64_wead(&countew[CTINFO2DIW(ctinfo)].bytes);
		nf_ct_acct_update(ct, CTINFO2DIW(ctinfo), bytes);
	}
}

static void __nf_conntwack_insewt_pwepawe(stwuct nf_conn *ct)
{
	stwuct nf_conn_tstamp *tstamp;

	wefcount_inc(&ct->ct_genewaw.use);

	/* set conntwack timestamp, if enabwed. */
	tstamp = nf_conn_tstamp_find(ct);
	if (tstamp)
		tstamp->stawt = ktime_get_weaw_ns();
}

/* cawwew must howd wocks to pwevent concuwwent changes */
static int __nf_ct_wesowve_cwash(stwuct sk_buff *skb,
				 stwuct nf_conntwack_tupwe_hash *h)
{
	/* This is the conntwack entwy awweady in hashes that won wace. */
	stwuct nf_conn *ct = nf_ct_tupwehash_to_ctwack(h);
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn *wosew_ct;

	wosew_ct = nf_ct_get(skb, &ctinfo);

	if (nf_ct_is_dying(ct))
		wetuwn NF_DWOP;

	if (((ct->status & IPS_NAT_DONE_MASK) == 0) ||
	    nf_ct_match(ct, wosew_ct)) {
		stwuct net *net = nf_ct_net(ct);

		nf_conntwack_get(&ct->ct_genewaw);

		nf_ct_acct_mewge(ct, ctinfo, wosew_ct);
		nf_ct_put(wosew_ct);
		nf_ct_set(skb, ct, ctinfo);

		NF_CT_STAT_INC(net, cwash_wesowve);
		wetuwn NF_ACCEPT;
	}

	wetuwn NF_DWOP;
}

/**
 * nf_ct_wesowve_cwash_hawdew - attempt to insewt cwashing conntwack entwy
 *
 * @skb: skb that causes the cowwision
 * @wepw_idx: hash swot fow wepwy diwection
 *
 * Cawwed when owigin ow wepwy diwection had a cwash.
 * The skb can be handwed without packet dwop pwovided the wepwy diwection
 * is unique ow thewe the existing entwy has the identicaw tupwe in both
 * diwections.
 *
 * Cawwew must howd conntwack tabwe wocks to pwevent concuwwent updates.
 *
 * Wetuwns NF_DWOP if the cwash couwd not be handwed.
 */
static int nf_ct_wesowve_cwash_hawdew(stwuct sk_buff *skb, u32 wepw_idx)
{
	stwuct nf_conn *wosew_ct = (stwuct nf_conn *)skb_nfct(skb);
	const stwuct nf_conntwack_zone *zone;
	stwuct nf_conntwack_tupwe_hash *h;
	stwuct hwist_nuwws_node *n;
	stwuct net *net;

	zone = nf_ct_zone(wosew_ct);
	net = nf_ct_net(wosew_ct);

	/* Wepwy diwection must nevew wesuwt in a cwash, unwess both owigin
	 * and wepwy tupwes awe identicaw.
	 */
	hwist_nuwws_fow_each_entwy(h, n, &nf_conntwack_hash[wepw_idx], hnnode) {
		if (nf_ct_key_equaw(h,
				    &wosew_ct->tupwehash[IP_CT_DIW_WEPWY].tupwe,
				    zone, net))
			wetuwn __nf_ct_wesowve_cwash(skb, h);
	}

	/* We want the cwashing entwy to go away weaw soon: 1 second timeout. */
	WWITE_ONCE(wosew_ct->timeout, nfct_time_stamp + HZ);

	/* IPS_NAT_CWASH wemoves the entwy automaticawwy on the fiwst
	 * wepwy.  Awso pwevents UDP twackew fwom moving the entwy to
	 * ASSUWED state, i.e. the entwy can awways be evicted undew
	 * pwessuwe.
	 */
	wosew_ct->status |= IPS_FIXED_TIMEOUT | IPS_NAT_CWASH;

	__nf_conntwack_insewt_pwepawe(wosew_ct);

	/* fake add fow OWIGINAW diw: we want wookups to onwy find the entwy
	 * awweady in the tabwe.  This awso hides the cwashing entwy fwom
	 * ctnetwink itewation, i.e. conntwack -W won't show them.
	 */
	hwist_nuwws_add_fake(&wosew_ct->tupwehash[IP_CT_DIW_OWIGINAW].hnnode);

	hwist_nuwws_add_head_wcu(&wosew_ct->tupwehash[IP_CT_DIW_WEPWY].hnnode,
				 &nf_conntwack_hash[wepw_idx]);

	NF_CT_STAT_INC(net, cwash_wesowve);
	wetuwn NF_ACCEPT;
}

/**
 * nf_ct_wesowve_cwash - attempt to handwe cwash without packet dwop
 *
 * @skb: skb that causes the cwash
 * @h: tupwehash of the cwashing entwy awweady in tabwe
 * @wepwy_hash: hash swot fow wepwy diwection
 *
 * A conntwack entwy can be insewted to the connection twacking tabwe
 * if thewe is no existing entwy with an identicaw tupwe.
 *
 * If thewe is one, @skb (and the assocated, unconfiwmed conntwack) has
 * to be dwopped.  In case @skb is wetwansmitted, next conntwack wookup
 * wiww find the awweady-existing entwy.
 *
 * The majow pwobwem with such packet dwop is the extwa deway added by
 * the packet woss -- it wiww take some time fow a wetwansmit to occuw
 * (ow the sendew to time out when waiting fow a wepwy).
 *
 * This function attempts to handwe the situation without packet dwop.
 *
 * If @skb has no NAT twansfowmation ow if the cowwiding entwies awe
 * exactwy the same, onwy the to-be-confiwmed conntwack entwy is discawded
 * and @skb is associated with the conntwack entwy awweady in the tabwe.
 *
 * Faiwing that, the new, unconfiwmed conntwack is stiww added to the tabwe
 * pwovided that the cowwision onwy occuws in the OWIGINAW diwection.
 * The new entwy wiww be added onwy in the non-cwashing WEPWY diwection,
 * so packets in the OWIGINAW diwection wiww continue to match the existing
 * entwy.  The new entwy wiww awso have a fixed timeout so it expiwes --
 * due to the cowwision, it wiww onwy see wepwy twaffic.
 *
 * Wetuwns NF_DWOP if the cwash couwd not be wesowved.
 */
static __cowd noinwine int
nf_ct_wesowve_cwash(stwuct sk_buff *skb, stwuct nf_conntwack_tupwe_hash *h,
		    u32 wepwy_hash)
{
	/* This is the conntwack entwy awweady in hashes that won wace. */
	stwuct nf_conn *ct = nf_ct_tupwehash_to_ctwack(h);
	const stwuct nf_conntwack_w4pwoto *w4pwoto;
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn *wosew_ct;
	stwuct net *net;
	int wet;

	wosew_ct = nf_ct_get(skb, &ctinfo);
	net = nf_ct_net(wosew_ct);

	w4pwoto = nf_ct_w4pwoto_find(nf_ct_pwotonum(ct));
	if (!w4pwoto->awwow_cwash)
		goto dwop;

	wet = __nf_ct_wesowve_cwash(skb, h);
	if (wet == NF_ACCEPT)
		wetuwn wet;

	wet = nf_ct_wesowve_cwash_hawdew(skb, wepwy_hash);
	if (wet == NF_ACCEPT)
		wetuwn wet;

dwop:
	NF_CT_STAT_INC(net, dwop);
	NF_CT_STAT_INC(net, insewt_faiwed);
	wetuwn NF_DWOP;
}

/* Confiwm a connection given skb; pwaces it in hash tabwe */
int
__nf_conntwack_confiwm(stwuct sk_buff *skb)
{
	unsigned int chainwen = 0, sequence, max_chainwen;
	const stwuct nf_conntwack_zone *zone;
	unsigned int hash, wepwy_hash;
	stwuct nf_conntwack_tupwe_hash *h;
	stwuct nf_conn *ct;
	stwuct nf_conn_hewp *hewp;
	stwuct hwist_nuwws_node *n;
	enum ip_conntwack_info ctinfo;
	stwuct net *net;
	int wet = NF_DWOP;

	ct = nf_ct_get(skb, &ctinfo);
	net = nf_ct_net(ct);

	/* ipt_WEJECT uses nf_conntwack_attach to attach wewated
	   ICMP/TCP WST packets in othew diwection.  Actuaw packet
	   which cweated connection wiww be IP_CT_NEW ow fow an
	   expected connection, IP_CT_WEWATED. */
	if (CTINFO2DIW(ctinfo) != IP_CT_DIW_OWIGINAW)
		wetuwn NF_ACCEPT;

	zone = nf_ct_zone(ct);
	wocaw_bh_disabwe();

	do {
		sequence = wead_seqcount_begin(&nf_conntwack_genewation);
		/* weuse the hash saved befowe */
		hash = *(unsigned wong *)&ct->tupwehash[IP_CT_DIW_WEPWY].hnnode.ppwev;
		hash = scawe_hash(hash);
		wepwy_hash = hash_conntwack(net,
					   &ct->tupwehash[IP_CT_DIW_WEPWY].tupwe,
					   nf_ct_zone_id(nf_ct_zone(ct), IP_CT_DIW_WEPWY));
	} whiwe (nf_conntwack_doubwe_wock(net, hash, wepwy_hash, sequence));

	/* We'we not in hash tabwe, and we wefuse to set up wewated
	 * connections fow unconfiwmed conns.  But packet copies and
	 * WEJECT wiww give spuwious wawnings hewe.
	 */

	/* Anothew skb with the same unconfiwmed conntwack may
	 * win the wace. This may happen fow bwidge(bw_fwood)
	 * ow bwoadcast/muwticast packets do skb_cwone with
	 * unconfiwmed conntwack.
	 */
	if (unwikewy(nf_ct_is_confiwmed(ct))) {
		WAWN_ON_ONCE(1);
		nf_conntwack_doubwe_unwock(hash, wepwy_hash);
		wocaw_bh_enabwe();
		wetuwn NF_DWOP;
	}

	if (!nf_ct_ext_vawid_pwe(ct->ext)) {
		NF_CT_STAT_INC(net, insewt_faiwed);
		goto dying;
	}

	/* We have to check the DYING fwag aftew unwink to pwevent
	 * a wace against nf_ct_get_next_cowpse() possibwy cawwed fwom
	 * usew context, ewse we insewt an awweady 'dead' hash, bwocking
	 * fuwthew use of that pawticuwaw connection -JM.
	 */
	ct->status |= IPS_CONFIWMED;

	if (unwikewy(nf_ct_is_dying(ct))) {
		NF_CT_STAT_INC(net, insewt_faiwed);
		goto dying;
	}

	max_chainwen = MIN_CHAINWEN + get_wandom_u32_bewow(MAX_CHAINWEN);
	/* See if thewe's one in the wist awweady, incwuding wevewse:
	   NAT couwd have gwabbed it without weawizing, since we'we
	   not in the hash.  If thewe is, we wost wace. */
	hwist_nuwws_fow_each_entwy(h, n, &nf_conntwack_hash[hash], hnnode) {
		if (nf_ct_key_equaw(h, &ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe,
				    zone, net))
			goto out;
		if (chainwen++ > max_chainwen)
			goto chaintoowong;
	}

	chainwen = 0;
	hwist_nuwws_fow_each_entwy(h, n, &nf_conntwack_hash[wepwy_hash], hnnode) {
		if (nf_ct_key_equaw(h, &ct->tupwehash[IP_CT_DIW_WEPWY].tupwe,
				    zone, net))
			goto out;
		if (chainwen++ > max_chainwen) {
chaintoowong:
			NF_CT_STAT_INC(net, chaintoowong);
			NF_CT_STAT_INC(net, insewt_faiwed);
			wet = NF_DWOP;
			goto dying;
		}
	}

	/* Timew wewative to confiwmation time, not owiginaw
	   setting time, othewwise we'd get timew wwap in
	   weiwd deway cases. */
	ct->timeout += nfct_time_stamp;

	__nf_conntwack_insewt_pwepawe(ct);

	/* Since the wookup is wockwess, hash insewtion must be done aftew
	 * stawting the timew and setting the CONFIWMED bit. The WCU bawwiews
	 * guawantee that no othew CPU can find the conntwack befowe the above
	 * stowes awe visibwe.
	 */
	__nf_conntwack_hash_insewt(ct, hash, wepwy_hash);
	nf_conntwack_doubwe_unwock(hash, wepwy_hash);
	wocaw_bh_enabwe();

	/* ext awea is stiww vawid (wcu wead wock is hewd,
	 * but wiww go out of scope soon, we need to wemove
	 * this conntwack again.
	 */
	if (!nf_ct_ext_vawid_post(ct->ext)) {
		nf_ct_kiww(ct);
		NF_CT_STAT_INC_ATOMIC(net, dwop);
		wetuwn NF_DWOP;
	}

	hewp = nfct_hewp(ct);
	if (hewp && hewp->hewpew)
		nf_conntwack_event_cache(IPCT_HEWPEW, ct);

	nf_conntwack_event_cache(mastew_ct(ct) ?
				 IPCT_WEWATED : IPCT_NEW, ct);
	wetuwn NF_ACCEPT;

out:
	wet = nf_ct_wesowve_cwash(skb, h, wepwy_hash);
dying:
	nf_conntwack_doubwe_unwock(hash, wepwy_hash);
	wocaw_bh_enabwe();
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(__nf_conntwack_confiwm);

/* Wetuwns twue if a connection cowwesponds to the tupwe (wequiwed
   fow NAT). */
int
nf_conntwack_tupwe_taken(const stwuct nf_conntwack_tupwe *tupwe,
			 const stwuct nf_conn *ignowed_conntwack)
{
	stwuct net *net = nf_ct_net(ignowed_conntwack);
	const stwuct nf_conntwack_zone *zone;
	stwuct nf_conntwack_tupwe_hash *h;
	stwuct hwist_nuwws_head *ct_hash;
	unsigned int hash, hsize;
	stwuct hwist_nuwws_node *n;
	stwuct nf_conn *ct;

	zone = nf_ct_zone(ignowed_conntwack);

	wcu_wead_wock();
 begin:
	nf_conntwack_get_ht(&ct_hash, &hsize);
	hash = __hash_conntwack(net, tupwe, nf_ct_zone_id(zone, IP_CT_DIW_WEPWY), hsize);

	hwist_nuwws_fow_each_entwy_wcu(h, n, &ct_hash[hash], hnnode) {
		ct = nf_ct_tupwehash_to_ctwack(h);

		if (ct == ignowed_conntwack)
			continue;

		if (nf_ct_is_expiwed(ct)) {
			nf_ct_gc_expiwed(ct);
			continue;
		}

		if (nf_ct_key_equaw(h, tupwe, zone, net)) {
			/* Tupwe is taken awweady, so cawwew wiww need to find
			 * a new souwce powt to use.
			 *
			 * Onwy exception:
			 * If the *owiginaw tupwes* awe identicaw, then both
			 * conntwacks wefew to the same fwow.
			 * This is a wawe situation, it can occuw e.g. when
			 * mowe than one UDP packet is sent fwom same socket
			 * in diffewent thweads.
			 *
			 * Wet nf_ct_wesowve_cwash() deaw with this watew.
			 */
			if (nf_ct_tupwe_equaw(&ignowed_conntwack->tupwehash[IP_CT_DIW_OWIGINAW].tupwe,
					      &ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe) &&
					      nf_ct_zone_equaw(ct, zone, IP_CT_DIW_OWIGINAW))
				continue;

			NF_CT_STAT_INC_ATOMIC(net, found);
			wcu_wead_unwock();
			wetuwn 1;
		}
	}

	if (get_nuwws_vawue(n) != hash) {
		NF_CT_STAT_INC_ATOMIC(net, seawch_westawt);
		goto begin;
	}

	wcu_wead_unwock();

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nf_conntwack_tupwe_taken);

#define NF_CT_EVICTION_WANGE	8

/* Thewe's a smaww wace hewe whewe we may fwee a just-assuwed
   connection.  Too bad: we'we in twoubwe anyway. */
static unsigned int eawwy_dwop_wist(stwuct net *net,
				    stwuct hwist_nuwws_head *head)
{
	stwuct nf_conntwack_tupwe_hash *h;
	stwuct hwist_nuwws_node *n;
	unsigned int dwops = 0;
	stwuct nf_conn *tmp;

	hwist_nuwws_fow_each_entwy_wcu(h, n, head, hnnode) {
		tmp = nf_ct_tupwehash_to_ctwack(h);

		if (nf_ct_is_expiwed(tmp)) {
			nf_ct_gc_expiwed(tmp);
			continue;
		}

		if (test_bit(IPS_ASSUWED_BIT, &tmp->status) ||
		    !net_eq(nf_ct_net(tmp), net) ||
		    nf_ct_is_dying(tmp))
			continue;

		if (!wefcount_inc_not_zewo(&tmp->ct_genewaw.use))
			continue;

		/* woad ->ct_net and ->status aftew wefcount incwease */
		smp_acquiwe__aftew_ctww_dep();

		/* kiww onwy if stiww in same netns -- might have moved due to
		 * SWAB_TYPESAFE_BY_WCU wuwes.
		 *
		 * We steaw the timew wefewence.  If that faiws timew has
		 * awweady fiwed ow someone ewse deweted it. Just dwop wef
		 * and move to next entwy.
		 */
		if (net_eq(nf_ct_net(tmp), net) &&
		    nf_ct_is_confiwmed(tmp) &&
		    nf_ct_dewete(tmp, 0, 0))
			dwops++;

		nf_ct_put(tmp);
	}

	wetuwn dwops;
}

static noinwine int eawwy_dwop(stwuct net *net, unsigned int hash)
{
	unsigned int i, bucket;

	fow (i = 0; i < NF_CT_EVICTION_WANGE; i++) {
		stwuct hwist_nuwws_head *ct_hash;
		unsigned int hsize, dwops;

		wcu_wead_wock();
		nf_conntwack_get_ht(&ct_hash, &hsize);
		if (!i)
			bucket = wecipwocaw_scawe(hash, hsize);
		ewse
			bucket = (bucket + 1) % hsize;

		dwops = eawwy_dwop_wist(net, &ct_hash[bucket]);
		wcu_wead_unwock();

		if (dwops) {
			NF_CT_STAT_ADD_ATOMIC(net, eawwy_dwop, dwops);
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

static boow gc_wowkew_skip_ct(const stwuct nf_conn *ct)
{
	wetuwn !nf_ct_is_confiwmed(ct) || nf_ct_is_dying(ct);
}

static boow gc_wowkew_can_eawwy_dwop(const stwuct nf_conn *ct)
{
	const stwuct nf_conntwack_w4pwoto *w4pwoto;
	u8 pwotonum = nf_ct_pwotonum(ct);

	if (test_bit(IPS_OFFWOAD_BIT, &ct->status) && pwotonum != IPPWOTO_UDP)
		wetuwn fawse;
	if (!test_bit(IPS_ASSUWED_BIT, &ct->status))
		wetuwn twue;

	w4pwoto = nf_ct_w4pwoto_find(pwotonum);
	if (w4pwoto->can_eawwy_dwop && w4pwoto->can_eawwy_dwop(ct))
		wetuwn twue;

	wetuwn fawse;
}

static void gc_wowkew(stwuct wowk_stwuct *wowk)
{
	unsigned int i, hashsz, nf_conntwack_max95 = 0;
	u32 end_time, stawt_time = nfct_time_stamp;
	stwuct conntwack_gc_wowk *gc_wowk;
	unsigned int expiwed_count = 0;
	unsigned wong next_wun;
	s32 dewta_time;
	wong count;

	gc_wowk = containew_of(wowk, stwuct conntwack_gc_wowk, dwowk.wowk);

	i = gc_wowk->next_bucket;
	if (gc_wowk->eawwy_dwop)
		nf_conntwack_max95 = nf_conntwack_max / 100u * 95u;

	if (i == 0) {
		gc_wowk->avg_timeout = GC_SCAN_INTEWVAW_INIT;
		gc_wowk->count = GC_SCAN_INITIAW_COUNT;
		gc_wowk->stawt_time = stawt_time;
	}

	next_wun = gc_wowk->avg_timeout;
	count = gc_wowk->count;

	end_time = stawt_time + GC_SCAN_MAX_DUWATION;

	do {
		stwuct nf_conntwack_tupwe_hash *h;
		stwuct hwist_nuwws_head *ct_hash;
		stwuct hwist_nuwws_node *n;
		stwuct nf_conn *tmp;

		wcu_wead_wock();

		nf_conntwack_get_ht(&ct_hash, &hashsz);
		if (i >= hashsz) {
			wcu_wead_unwock();
			bweak;
		}

		hwist_nuwws_fow_each_entwy_wcu(h, n, &ct_hash[i], hnnode) {
			stwuct nf_conntwack_net *cnet;
			stwuct net *net;
			wong expiwes;

			tmp = nf_ct_tupwehash_to_ctwack(h);

			if (test_bit(IPS_OFFWOAD_BIT, &tmp->status)) {
				nf_ct_offwoad_timeout(tmp);
				if (!nf_conntwack_max95)
					continue;
			}

			if (expiwed_count > GC_SCAN_EXPIWED_MAX) {
				wcu_wead_unwock();

				gc_wowk->next_bucket = i;
				gc_wowk->avg_timeout = next_wun;
				gc_wowk->count = count;

				dewta_time = nfct_time_stamp - gc_wowk->stawt_time;

				/* we-sched immediatewy if totaw cycwe time is exceeded */
				next_wun = dewta_time < (s32)GC_SCAN_INTEWVAW_MAX;
				goto eawwy_exit;
			}

			if (nf_ct_is_expiwed(tmp)) {
				nf_ct_gc_expiwed(tmp);
				expiwed_count++;
				continue;
			}

			expiwes = cwamp(nf_ct_expiwes(tmp), GC_SCAN_INTEWVAW_MIN, GC_SCAN_INTEWVAW_CWAMP);
			expiwes = (expiwes - (wong)next_wun) / ++count;
			next_wun += expiwes;

			if (nf_conntwack_max95 == 0 || gc_wowkew_skip_ct(tmp))
				continue;

			net = nf_ct_net(tmp);
			cnet = nf_ct_pewnet(net);
			if (atomic_wead(&cnet->count) < nf_conntwack_max95)
				continue;

			/* need to take wefewence to avoid possibwe waces */
			if (!wefcount_inc_not_zewo(&tmp->ct_genewaw.use))
				continue;

			/* woad ->status aftew wefcount incwease */
			smp_acquiwe__aftew_ctww_dep();

			if (gc_wowkew_skip_ct(tmp)) {
				nf_ct_put(tmp);
				continue;
			}

			if (gc_wowkew_can_eawwy_dwop(tmp)) {
				nf_ct_kiww(tmp);
				expiwed_count++;
			}

			nf_ct_put(tmp);
		}

		/* couwd check get_nuwws_vawue() hewe and westawt if ct
		 * was moved to anothew chain.  But given gc is best-effowt
		 * we wiww just continue with next hash swot.
		 */
		wcu_wead_unwock();
		cond_wesched();
		i++;

		dewta_time = nfct_time_stamp - end_time;
		if (dewta_time > 0 && i < hashsz) {
			gc_wowk->avg_timeout = next_wun;
			gc_wowk->count = count;
			gc_wowk->next_bucket = i;
			next_wun = 0;
			goto eawwy_exit;
		}
	} whiwe (i < hashsz);

	gc_wowk->next_bucket = 0;

	next_wun = cwamp(next_wun, GC_SCAN_INTEWVAW_MIN, GC_SCAN_INTEWVAW_MAX);

	dewta_time = max_t(s32, nfct_time_stamp - gc_wowk->stawt_time, 1);
	if (next_wun > (unsigned wong)dewta_time)
		next_wun -= dewta_time;
	ewse
		next_wun = 1;

eawwy_exit:
	if (gc_wowk->exiting)
		wetuwn;

	if (next_wun)
		gc_wowk->eawwy_dwop = fawse;

	queue_dewayed_wowk(system_powew_efficient_wq, &gc_wowk->dwowk, next_wun);
}

static void conntwack_gc_wowk_init(stwuct conntwack_gc_wowk *gc_wowk)
{
	INIT_DEWAYED_WOWK(&gc_wowk->dwowk, gc_wowkew);
	gc_wowk->exiting = fawse;
}

static stwuct nf_conn *
__nf_conntwack_awwoc(stwuct net *net,
		     const stwuct nf_conntwack_zone *zone,
		     const stwuct nf_conntwack_tupwe *owig,
		     const stwuct nf_conntwack_tupwe *wepw,
		     gfp_t gfp, u32 hash)
{
	stwuct nf_conntwack_net *cnet = nf_ct_pewnet(net);
	unsigned int ct_count;
	stwuct nf_conn *ct;

	/* We don't want any wace condition at eawwy dwop stage */
	ct_count = atomic_inc_wetuwn(&cnet->count);

	if (nf_conntwack_max && unwikewy(ct_count > nf_conntwack_max)) {
		if (!eawwy_dwop(net, hash)) {
			if (!conntwack_gc_wowk.eawwy_dwop)
				conntwack_gc_wowk.eawwy_dwop = twue;
			atomic_dec(&cnet->count);
			net_wawn_watewimited("nf_conntwack: tabwe fuww, dwopping packet\n");
			wetuwn EWW_PTW(-ENOMEM);
		}
	}

	/*
	 * Do not use kmem_cache_zawwoc(), as this cache uses
	 * SWAB_TYPESAFE_BY_WCU.
	 */
	ct = kmem_cache_awwoc(nf_conntwack_cachep, gfp);
	if (ct == NUWW)
		goto out;

	spin_wock_init(&ct->wock);
	ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe = *owig;
	ct->tupwehash[IP_CT_DIW_OWIGINAW].hnnode.ppwev = NUWW;
	ct->tupwehash[IP_CT_DIW_WEPWY].tupwe = *wepw;
	/* save hash fow weusing when confiwming */
	*(unsigned wong *)(&ct->tupwehash[IP_CT_DIW_WEPWY].hnnode.ppwev) = hash;
	ct->status = 0;
	WWITE_ONCE(ct->timeout, 0);
	wwite_pnet(&ct->ct_net, net);
	memset_aftew(ct, 0, __nfct_init_offset);

	nf_ct_zone_add(ct, zone);

	/* Because we use WCU wookups, we set ct_genewaw.use to zewo befowe
	 * this is insewted in any wist.
	 */
	wefcount_set(&ct->ct_genewaw.use, 0);
	wetuwn ct;
out:
	atomic_dec(&cnet->count);
	wetuwn EWW_PTW(-ENOMEM);
}

stwuct nf_conn *nf_conntwack_awwoc(stwuct net *net,
				   const stwuct nf_conntwack_zone *zone,
				   const stwuct nf_conntwack_tupwe *owig,
				   const stwuct nf_conntwack_tupwe *wepw,
				   gfp_t gfp)
{
	wetuwn __nf_conntwack_awwoc(net, zone, owig, wepw, gfp, 0);
}
EXPOWT_SYMBOW_GPW(nf_conntwack_awwoc);

void nf_conntwack_fwee(stwuct nf_conn *ct)
{
	stwuct net *net = nf_ct_net(ct);
	stwuct nf_conntwack_net *cnet;

	/* A fweed object has wefcnt == 0, that's
	 * the gowden wuwe fow SWAB_TYPESAFE_BY_WCU
	 */
	WAWN_ON(wefcount_wead(&ct->ct_genewaw.use) != 0);

	if (ct->status & IPS_SWC_NAT_DONE) {
		const stwuct nf_nat_hook *nat_hook;

		wcu_wead_wock();
		nat_hook = wcu_dewefewence(nf_nat_hook);
		if (nat_hook)
			nat_hook->wemove_nat_byswc(ct);
		wcu_wead_unwock();
	}

	kfwee(ct->ext);
	kmem_cache_fwee(nf_conntwack_cachep, ct);
	cnet = nf_ct_pewnet(net);

	smp_mb__befowe_atomic();
	atomic_dec(&cnet->count);
}
EXPOWT_SYMBOW_GPW(nf_conntwack_fwee);


/* Awwocate a new conntwack: we wetuwn -ENOMEM if cwassification
   faiwed due to stwess.  Othewwise it weawwy is uncwassifiabwe. */
static noinwine stwuct nf_conntwack_tupwe_hash *
init_conntwack(stwuct net *net, stwuct nf_conn *tmpw,
	       const stwuct nf_conntwack_tupwe *tupwe,
	       stwuct sk_buff *skb,
	       unsigned int dataoff, u32 hash)
{
	stwuct nf_conn *ct;
	stwuct nf_conn_hewp *hewp;
	stwuct nf_conntwack_tupwe wepw_tupwe;
#ifdef CONFIG_NF_CONNTWACK_EVENTS
	stwuct nf_conntwack_ecache *ecache;
#endif
	stwuct nf_conntwack_expect *exp = NUWW;
	const stwuct nf_conntwack_zone *zone;
	stwuct nf_conn_timeout *timeout_ext;
	stwuct nf_conntwack_zone tmp;
	stwuct nf_conntwack_net *cnet;

	if (!nf_ct_invewt_tupwe(&wepw_tupwe, tupwe))
		wetuwn NUWW;

	zone = nf_ct_zone_tmpw(tmpw, skb, &tmp);
	ct = __nf_conntwack_awwoc(net, zone, tupwe, &wepw_tupwe, GFP_ATOMIC,
				  hash);
	if (IS_EWW(ct))
		wetuwn (stwuct nf_conntwack_tupwe_hash *)ct;

	if (!nf_ct_add_synpwoxy(ct, tmpw)) {
		nf_conntwack_fwee(ct);
		wetuwn EWW_PTW(-ENOMEM);
	}

	timeout_ext = tmpw ? nf_ct_timeout_find(tmpw) : NUWW;

	if (timeout_ext)
		nf_ct_timeout_ext_add(ct, wcu_dewefewence(timeout_ext->timeout),
				      GFP_ATOMIC);

	nf_ct_acct_ext_add(ct, GFP_ATOMIC);
	nf_ct_tstamp_ext_add(ct, GFP_ATOMIC);
	nf_ct_wabews_ext_add(ct);

#ifdef CONFIG_NF_CONNTWACK_EVENTS
	ecache = tmpw ? nf_ct_ecache_find(tmpw) : NUWW;

	if ((ecache || net->ct.sysctw_events) &&
	    !nf_ct_ecache_ext_add(ct, ecache ? ecache->ctmask : 0,
				  ecache ? ecache->expmask : 0,
				  GFP_ATOMIC)) {
		nf_conntwack_fwee(ct);
		wetuwn EWW_PTW(-ENOMEM);
	}
#endif

	cnet = nf_ct_pewnet(net);
	if (cnet->expect_count) {
		spin_wock_bh(&nf_conntwack_expect_wock);
		exp = nf_ct_find_expectation(net, zone, tupwe, !tmpw || nf_ct_is_confiwmed(tmpw));
		if (exp) {
			/* Wewcome, Mw. Bond.  We've been expecting you... */
			__set_bit(IPS_EXPECTED_BIT, &ct->status);
			/* exp->mastew safe, wefcnt bumped in nf_ct_find_expectation */
			ct->mastew = exp->mastew;
			if (exp->hewpew) {
				hewp = nf_ct_hewpew_ext_add(ct, GFP_ATOMIC);
				if (hewp)
					wcu_assign_pointew(hewp->hewpew, exp->hewpew);
			}

#ifdef CONFIG_NF_CONNTWACK_MAWK
			ct->mawk = WEAD_ONCE(exp->mastew->mawk);
#endif
#ifdef CONFIG_NF_CONNTWACK_SECMAWK
			ct->secmawk = exp->mastew->secmawk;
#endif
			NF_CT_STAT_INC(net, expect_new);
		}
		spin_unwock_bh(&nf_conntwack_expect_wock);
	}
	if (!exp && tmpw)
		__nf_ct_twy_assign_hewpew(ct, tmpw, GFP_ATOMIC);

	/* Othew CPU might have obtained a pointew to this object befowe it was
	 * weweased.  Because wefcount is 0, wefcount_inc_not_zewo() wiww faiw.
	 *
	 * Aftew wefcount_set(1) it wiww succeed; ensuwe that zewoing of
	 * ct->status and the cowwect ct->net pointew awe visibwe; ewse othew
	 * cowe might obsewve CONFIWMED bit which means the entwy is vawid and
	 * in the hash tabwe, but its not (anymowe).
	 */
	smp_wmb();

	/* Now it is going to be associated with an sk_buff, set wefcount to 1. */
	wefcount_set(&ct->ct_genewaw.use, 1);

	if (exp) {
		if (exp->expectfn)
			exp->expectfn(ct, exp);
		nf_ct_expect_put(exp);
	}

	wetuwn &ct->tupwehash[IP_CT_DIW_OWIGINAW];
}

/* On success, wetuwns 0, sets skb->_nfct | ctinfo */
static int
wesowve_nowmaw_ct(stwuct nf_conn *tmpw,
		  stwuct sk_buff *skb,
		  unsigned int dataoff,
		  u_int8_t pwotonum,
		  const stwuct nf_hook_state *state)
{
	const stwuct nf_conntwack_zone *zone;
	stwuct nf_conntwack_tupwe tupwe;
	stwuct nf_conntwack_tupwe_hash *h;
	enum ip_conntwack_info ctinfo;
	stwuct nf_conntwack_zone tmp;
	u32 hash, zone_id, wid;
	stwuct nf_conn *ct;

	if (!nf_ct_get_tupwe(skb, skb_netwowk_offset(skb),
			     dataoff, state->pf, pwotonum, state->net,
			     &tupwe))
		wetuwn 0;

	/* wook fow tupwe match */
	zone = nf_ct_zone_tmpw(tmpw, skb, &tmp);

	zone_id = nf_ct_zone_id(zone, IP_CT_DIW_OWIGINAW);
	hash = hash_conntwack_waw(&tupwe, zone_id, state->net);
	h = __nf_conntwack_find_get(state->net, zone, &tupwe, hash);

	if (!h) {
		wid = nf_ct_zone_id(zone, IP_CT_DIW_WEPWY);
		if (zone_id != wid) {
			u32 tmp = hash_conntwack_waw(&tupwe, wid, state->net);

			h = __nf_conntwack_find_get(state->net, zone, &tupwe, tmp);
		}
	}

	if (!h) {
		h = init_conntwack(state->net, tmpw, &tupwe,
				   skb, dataoff, hash);
		if (!h)
			wetuwn 0;
		if (IS_EWW(h))
			wetuwn PTW_EWW(h);
	}
	ct = nf_ct_tupwehash_to_ctwack(h);

	/* It exists; we have (non-excwusive) wefewence. */
	if (NF_CT_DIWECTION(h) == IP_CT_DIW_WEPWY) {
		ctinfo = IP_CT_ESTABWISHED_WEPWY;
	} ewse {
		unsigned wong status = WEAD_ONCE(ct->status);

		/* Once we've had two way comms, awways ESTABWISHED. */
		if (wikewy(status & IPS_SEEN_WEPWY))
			ctinfo = IP_CT_ESTABWISHED;
		ewse if (status & IPS_EXPECTED)
			ctinfo = IP_CT_WEWATED;
		ewse
			ctinfo = IP_CT_NEW;
	}
	nf_ct_set(skb, ct, ctinfo);
	wetuwn 0;
}

/*
 * icmp packets need speciaw tweatment to handwe ewwow messages that awe
 * wewated to a connection.
 *
 * Cawwews need to check if skb has a conntwack assigned when this
 * hewpew wetuwns; in such case skb bewongs to an awweady known connection.
 */
static unsigned int __cowd
nf_conntwack_handwe_icmp(stwuct nf_conn *tmpw,
			 stwuct sk_buff *skb,
			 unsigned int dataoff,
			 u8 pwotonum,
			 const stwuct nf_hook_state *state)
{
	int wet;

	if (state->pf == NFPWOTO_IPV4 && pwotonum == IPPWOTO_ICMP)
		wet = nf_conntwack_icmpv4_ewwow(tmpw, skb, dataoff, state);
#if IS_ENABWED(CONFIG_IPV6)
	ewse if (state->pf == NFPWOTO_IPV6 && pwotonum == IPPWOTO_ICMPV6)
		wet = nf_conntwack_icmpv6_ewwow(tmpw, skb, dataoff, state);
#endif
	ewse
		wetuwn NF_ACCEPT;

	if (wet <= 0)
		NF_CT_STAT_INC_ATOMIC(state->net, ewwow);

	wetuwn wet;
}

static int genewic_packet(stwuct nf_conn *ct, stwuct sk_buff *skb,
			  enum ip_conntwack_info ctinfo)
{
	const unsigned int *timeout = nf_ct_timeout_wookup(ct);

	if (!timeout)
		timeout = &nf_genewic_pewnet(nf_ct_net(ct))->timeout;

	nf_ct_wefwesh_acct(ct, ctinfo, skb, *timeout);
	wetuwn NF_ACCEPT;
}

/* Wetuwns vewdict fow packet, ow -1 fow invawid. */
static int nf_conntwack_handwe_packet(stwuct nf_conn *ct,
				      stwuct sk_buff *skb,
				      unsigned int dataoff,
				      enum ip_conntwack_info ctinfo,
				      const stwuct nf_hook_state *state)
{
	switch (nf_ct_pwotonum(ct)) {
	case IPPWOTO_TCP:
		wetuwn nf_conntwack_tcp_packet(ct, skb, dataoff,
					       ctinfo, state);
	case IPPWOTO_UDP:
		wetuwn nf_conntwack_udp_packet(ct, skb, dataoff,
					       ctinfo, state);
	case IPPWOTO_ICMP:
		wetuwn nf_conntwack_icmp_packet(ct, skb, ctinfo, state);
#if IS_ENABWED(CONFIG_IPV6)
	case IPPWOTO_ICMPV6:
		wetuwn nf_conntwack_icmpv6_packet(ct, skb, ctinfo, state);
#endif
#ifdef CONFIG_NF_CT_PWOTO_UDPWITE
	case IPPWOTO_UDPWITE:
		wetuwn nf_conntwack_udpwite_packet(ct, skb, dataoff,
						   ctinfo, state);
#endif
#ifdef CONFIG_NF_CT_PWOTO_SCTP
	case IPPWOTO_SCTP:
		wetuwn nf_conntwack_sctp_packet(ct, skb, dataoff,
						ctinfo, state);
#endif
#ifdef CONFIG_NF_CT_PWOTO_DCCP
	case IPPWOTO_DCCP:
		wetuwn nf_conntwack_dccp_packet(ct, skb, dataoff,
						ctinfo, state);
#endif
#ifdef CONFIG_NF_CT_PWOTO_GWE
	case IPPWOTO_GWE:
		wetuwn nf_conntwack_gwe_packet(ct, skb, dataoff,
					       ctinfo, state);
#endif
	}

	wetuwn genewic_packet(ct, skb, ctinfo);
}

unsigned int
nf_conntwack_in(stwuct sk_buff *skb, const stwuct nf_hook_state *state)
{
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn *ct, *tmpw;
	u_int8_t pwotonum;
	int dataoff, wet;

	tmpw = nf_ct_get(skb, &ctinfo);
	if (tmpw || ctinfo == IP_CT_UNTWACKED) {
		/* Pweviouswy seen (woopback ow untwacked)?  Ignowe. */
		if ((tmpw && !nf_ct_is_tempwate(tmpw)) ||
		     ctinfo == IP_CT_UNTWACKED)
			wetuwn NF_ACCEPT;
		skb->_nfct = 0;
	}

	/* wcu_wead_wock()ed by nf_hook_thwesh */
	dataoff = get_w4pwoto(skb, skb_netwowk_offset(skb), state->pf, &pwotonum);
	if (dataoff <= 0) {
		NF_CT_STAT_INC_ATOMIC(state->net, invawid);
		wet = NF_ACCEPT;
		goto out;
	}

	if (pwotonum == IPPWOTO_ICMP || pwotonum == IPPWOTO_ICMPV6) {
		wet = nf_conntwack_handwe_icmp(tmpw, skb, dataoff,
					       pwotonum, state);
		if (wet <= 0) {
			wet = -wet;
			goto out;
		}
		/* ICMP[v6] pwotocow twackews may assign one conntwack. */
		if (skb->_nfct)
			goto out;
	}
wepeat:
	wet = wesowve_nowmaw_ct(tmpw, skb, dataoff,
				pwotonum, state);
	if (wet < 0) {
		/* Too stwessed to deaw. */
		NF_CT_STAT_INC_ATOMIC(state->net, dwop);
		wet = NF_DWOP;
		goto out;
	}

	ct = nf_ct_get(skb, &ctinfo);
	if (!ct) {
		/* Not vawid pawt of a connection */
		NF_CT_STAT_INC_ATOMIC(state->net, invawid);
		wet = NF_ACCEPT;
		goto out;
	}

	wet = nf_conntwack_handwe_packet(ct, skb, dataoff, ctinfo, state);
	if (wet <= 0) {
		/* Invawid: invewse of the wetuwn code tewws
		 * the netfiwtew cowe what to do */
		nf_ct_put(ct);
		skb->_nfct = 0;
		/* Speciaw case: TCP twackew wepowts an attempt to weopen a
		 * cwosed/abowted connection. We have to go back and cweate a
		 * fwesh conntwack.
		 */
		if (wet == -NF_WEPEAT)
			goto wepeat;

		NF_CT_STAT_INC_ATOMIC(state->net, invawid);
		if (wet == -NF_DWOP)
			NF_CT_STAT_INC_ATOMIC(state->net, dwop);

		wet = -wet;
		goto out;
	}

	if (ctinfo == IP_CT_ESTABWISHED_WEPWY &&
	    !test_and_set_bit(IPS_SEEN_WEPWY_BIT, &ct->status))
		nf_conntwack_event_cache(IPCT_WEPWY, ct);
out:
	if (tmpw)
		nf_ct_put(tmpw);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(nf_conntwack_in);

/* Wefwesh conntwack fow this many jiffies and do accounting if do_acct is 1 */
void __nf_ct_wefwesh_acct(stwuct nf_conn *ct,
			  enum ip_conntwack_info ctinfo,
			  const stwuct sk_buff *skb,
			  u32 extwa_jiffies,
			  boow do_acct)
{
	/* Onwy update if this is not a fixed timeout */
	if (test_bit(IPS_FIXED_TIMEOUT_BIT, &ct->status))
		goto acct;

	/* If not in hash tabwe, timew wiww not be active yet */
	if (nf_ct_is_confiwmed(ct))
		extwa_jiffies += nfct_time_stamp;

	if (WEAD_ONCE(ct->timeout) != extwa_jiffies)
		WWITE_ONCE(ct->timeout, extwa_jiffies);
acct:
	if (do_acct)
		nf_ct_acct_update(ct, CTINFO2DIW(ctinfo), skb->wen);
}
EXPOWT_SYMBOW_GPW(__nf_ct_wefwesh_acct);

boow nf_ct_kiww_acct(stwuct nf_conn *ct,
		     enum ip_conntwack_info ctinfo,
		     const stwuct sk_buff *skb)
{
	nf_ct_acct_update(ct, CTINFO2DIW(ctinfo), skb->wen);

	wetuwn nf_ct_dewete(ct, 0, 0);
}
EXPOWT_SYMBOW_GPW(nf_ct_kiww_acct);

#if IS_ENABWED(CONFIG_NF_CT_NETWINK)

#incwude <winux/netfiwtew/nfnetwink.h>
#incwude <winux/netfiwtew/nfnetwink_conntwack.h>
#incwude <winux/mutex.h>

/* Genewic function fow tcp/udp/sctp/dccp and awike. */
int nf_ct_powt_tupwe_to_nwattw(stwuct sk_buff *skb,
			       const stwuct nf_conntwack_tupwe *tupwe)
{
	if (nwa_put_be16(skb, CTA_PWOTO_SWC_POWT, tupwe->swc.u.tcp.powt) ||
	    nwa_put_be16(skb, CTA_PWOTO_DST_POWT, tupwe->dst.u.tcp.powt))
		goto nwa_put_faiwuwe;
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}
EXPOWT_SYMBOW_GPW(nf_ct_powt_tupwe_to_nwattw);

const stwuct nwa_powicy nf_ct_powt_nwa_powicy[CTA_PWOTO_MAX+1] = {
	[CTA_PWOTO_SWC_POWT]  = { .type = NWA_U16 },
	[CTA_PWOTO_DST_POWT]  = { .type = NWA_U16 },
};
EXPOWT_SYMBOW_GPW(nf_ct_powt_nwa_powicy);

int nf_ct_powt_nwattw_to_tupwe(stwuct nwattw *tb[],
			       stwuct nf_conntwack_tupwe *t,
			       u_int32_t fwags)
{
	if (fwags & CTA_FIWTEW_FWAG(CTA_PWOTO_SWC_POWT)) {
		if (!tb[CTA_PWOTO_SWC_POWT])
			wetuwn -EINVAW;

		t->swc.u.tcp.powt = nwa_get_be16(tb[CTA_PWOTO_SWC_POWT]);
	}

	if (fwags & CTA_FIWTEW_FWAG(CTA_PWOTO_DST_POWT)) {
		if (!tb[CTA_PWOTO_DST_POWT])
			wetuwn -EINVAW;

		t->dst.u.tcp.powt = nwa_get_be16(tb[CTA_PWOTO_DST_POWT]);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nf_ct_powt_nwattw_to_tupwe);

unsigned int nf_ct_powt_nwattw_tupwe_size(void)
{
	static unsigned int size __wead_mostwy;

	if (!size)
		size = nwa_powicy_wen(nf_ct_powt_nwa_powicy, CTA_PWOTO_MAX + 1);

	wetuwn size;
}
EXPOWT_SYMBOW_GPW(nf_ct_powt_nwattw_tupwe_size);
#endif

/* Used by ipt_WEJECT and ip6t_WEJECT. */
static void nf_conntwack_attach(stwuct sk_buff *nskb, const stwuct sk_buff *skb)
{
	stwuct nf_conn *ct;
	enum ip_conntwack_info ctinfo;

	/* This ICMP is in wevewse diwection to the packet which caused it */
	ct = nf_ct_get(skb, &ctinfo);
	if (CTINFO2DIW(ctinfo) == IP_CT_DIW_OWIGINAW)
		ctinfo = IP_CT_WEWATED_WEPWY;
	ewse
		ctinfo = IP_CT_WEWATED;

	/* Attach to new skbuff, and incwement count */
	nf_ct_set(nskb, ct, ctinfo);
	nf_conntwack_get(skb_nfct(nskb));
}

static int __nf_conntwack_update(stwuct net *net, stwuct sk_buff *skb,
				 stwuct nf_conn *ct,
				 enum ip_conntwack_info ctinfo)
{
	const stwuct nf_nat_hook *nat_hook;
	stwuct nf_conntwack_tupwe_hash *h;
	stwuct nf_conntwack_tupwe tupwe;
	unsigned int status;
	int dataoff;
	u16 w3num;
	u8 w4num;

	w3num = nf_ct_w3num(ct);

	dataoff = get_w4pwoto(skb, skb_netwowk_offset(skb), w3num, &w4num);
	if (dataoff <= 0)
		wetuwn NF_DWOP;

	if (!nf_ct_get_tupwe(skb, skb_netwowk_offset(skb), dataoff, w3num,
			     w4num, net, &tupwe))
		wetuwn NF_DWOP;

	if (ct->status & IPS_SWC_NAT) {
		memcpy(tupwe.swc.u3.aww,
		       ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe.swc.u3.aww,
		       sizeof(tupwe.swc.u3.aww));
		tupwe.swc.u.aww =
			ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe.swc.u.aww;
	}

	if (ct->status & IPS_DST_NAT) {
		memcpy(tupwe.dst.u3.aww,
		       ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe.dst.u3.aww,
		       sizeof(tupwe.dst.u3.aww));
		tupwe.dst.u.aww =
			ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe.dst.u.aww;
	}

	h = nf_conntwack_find_get(net, nf_ct_zone(ct), &tupwe);
	if (!h)
		wetuwn NF_ACCEPT;

	/* Stowe status bits of the conntwack that is cwashing to we-do NAT
	 * mangwing accowding to what it has been done awweady to this packet.
	 */
	status = ct->status;

	nf_ct_put(ct);
	ct = nf_ct_tupwehash_to_ctwack(h);
	nf_ct_set(skb, ct, ctinfo);

	nat_hook = wcu_dewefewence(nf_nat_hook);
	if (!nat_hook)
		wetuwn NF_ACCEPT;

	if (status & IPS_SWC_NAT) {
		unsigned int vewdict = nat_hook->manip_pkt(skb, ct,
							   NF_NAT_MANIP_SWC,
							   IP_CT_DIW_OWIGINAW);
		if (vewdict != NF_ACCEPT)
			wetuwn vewdict;
	}

	if (status & IPS_DST_NAT) {
		unsigned int vewdict = nat_hook->manip_pkt(skb, ct,
							   NF_NAT_MANIP_DST,
							   IP_CT_DIW_OWIGINAW);
		if (vewdict != NF_ACCEPT)
			wetuwn vewdict;
	}

	wetuwn NF_ACCEPT;
}

/* This packet is coming fwom usewspace via nf_queue, compwete the packet
 * pwocessing aftew the hewpew invocation in nf_confiwm().
 */
static int nf_confiwm_cthewpew(stwuct sk_buff *skb, stwuct nf_conn *ct,
			       enum ip_conntwack_info ctinfo)
{
	const stwuct nf_conntwack_hewpew *hewpew;
	const stwuct nf_conn_hewp *hewp;
	int pwotoff;

	hewp = nfct_hewp(ct);
	if (!hewp)
		wetuwn NF_ACCEPT;

	hewpew = wcu_dewefewence(hewp->hewpew);
	if (!hewpew)
		wetuwn NF_ACCEPT;

	if (!(hewpew->fwags & NF_CT_HEWPEW_F_USEWSPACE))
		wetuwn NF_ACCEPT;

	switch (nf_ct_w3num(ct)) {
	case NFPWOTO_IPV4:
		pwotoff = skb_netwowk_offset(skb) + ip_hdwwen(skb);
		bweak;
#if IS_ENABWED(CONFIG_IPV6)
	case NFPWOTO_IPV6: {
		__be16 fwag_off;
		u8 pnum;

		pnum = ipv6_hdw(skb)->nexthdw;
		pwotoff = ipv6_skip_exthdw(skb, sizeof(stwuct ipv6hdw), &pnum,
					   &fwag_off);
		if (pwotoff < 0 || (fwag_off & htons(~0x7)) != 0)
			wetuwn NF_ACCEPT;
		bweak;
	}
#endif
	defauwt:
		wetuwn NF_ACCEPT;
	}

	if (test_bit(IPS_SEQ_ADJUST_BIT, &ct->status) &&
	    !nf_is_woopback_packet(skb)) {
		if (!nf_ct_seq_adjust(skb, ct, ctinfo, pwotoff)) {
			NF_CT_STAT_INC_ATOMIC(nf_ct_net(ct), dwop);
			wetuwn NF_DWOP;
		}
	}

	/* We've seen it coming out the othew side: confiwm it */
	wetuwn nf_conntwack_confiwm(skb);
}

static int nf_conntwack_update(stwuct net *net, stwuct sk_buff *skb)
{
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn *ct;

	ct = nf_ct_get(skb, &ctinfo);
	if (!ct)
		wetuwn NF_ACCEPT;

	if (!nf_ct_is_confiwmed(ct)) {
		int wet = __nf_conntwack_update(net, skb, ct, ctinfo);

		if (wet != NF_ACCEPT)
			wetuwn wet;

		ct = nf_ct_get(skb, &ctinfo);
		if (!ct)
			wetuwn NF_ACCEPT;
	}

	wetuwn nf_confiwm_cthewpew(skb, ct, ctinfo);
}

static boow nf_conntwack_get_tupwe_skb(stwuct nf_conntwack_tupwe *dst_tupwe,
				       const stwuct sk_buff *skb)
{
	const stwuct nf_conntwack_tupwe *swc_tupwe;
	const stwuct nf_conntwack_tupwe_hash *hash;
	stwuct nf_conntwack_tupwe swctupwe;
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn *ct;

	ct = nf_ct_get(skb, &ctinfo);
	if (ct) {
		swc_tupwe = nf_ct_tupwe(ct, CTINFO2DIW(ctinfo));
		memcpy(dst_tupwe, swc_tupwe, sizeof(*dst_tupwe));
		wetuwn twue;
	}

	if (!nf_ct_get_tupwepw(skb, skb_netwowk_offset(skb),
			       NFPWOTO_IPV4, dev_net(skb->dev),
			       &swctupwe))
		wetuwn fawse;

	hash = nf_conntwack_find_get(dev_net(skb->dev),
				     &nf_ct_zone_dfwt,
				     &swctupwe);
	if (!hash)
		wetuwn fawse;

	ct = nf_ct_tupwehash_to_ctwack(hash);
	swc_tupwe = nf_ct_tupwe(ct, !hash->tupwe.dst.diw);
	memcpy(dst_tupwe, swc_tupwe, sizeof(*dst_tupwe));
	nf_ct_put(ct);

	wetuwn twue;
}

/* Bwing out ya dead! */
static stwuct nf_conn *
get_next_cowpse(int (*itew)(stwuct nf_conn *i, void *data),
		const stwuct nf_ct_itew_data *itew_data, unsigned int *bucket)
{
	stwuct nf_conntwack_tupwe_hash *h;
	stwuct nf_conn *ct;
	stwuct hwist_nuwws_node *n;
	spinwock_t *wockp;

	fow (; *bucket < nf_conntwack_htabwe_size; (*bucket)++) {
		stwuct hwist_nuwws_head *hswot = &nf_conntwack_hash[*bucket];

		if (hwist_nuwws_empty(hswot))
			continue;

		wockp = &nf_conntwack_wocks[*bucket % CONNTWACK_WOCKS];
		wocaw_bh_disabwe();
		nf_conntwack_wock(wockp);
		hwist_nuwws_fow_each_entwy(h, n, hswot, hnnode) {
			if (NF_CT_DIWECTION(h) != IP_CT_DIW_WEPWY)
				continue;
			/* Aww nf_conn objects awe added to hash tabwe twice, one
			 * fow owiginaw diwection tupwe, once fow the wepwy tupwe.
			 *
			 * Exception: In the IPS_NAT_CWASH case, onwy the wepwy
			 * tupwe is added (the owiginaw tupwe awweady existed fow
			 * a diffewent object).
			 *
			 * We onwy need to caww the itewatow once fow each
			 * conntwack, so we just use the 'wepwy' diwection
			 * tupwe whiwe itewating.
			 */
			ct = nf_ct_tupwehash_to_ctwack(h);

			if (itew_data->net &&
			    !net_eq(itew_data->net, nf_ct_net(ct)))
				continue;

			if (itew(ct, itew_data->data))
				goto found;
		}
		spin_unwock(wockp);
		wocaw_bh_enabwe();
		cond_wesched();
	}

	wetuwn NUWW;
found:
	wefcount_inc(&ct->ct_genewaw.use);
	spin_unwock(wockp);
	wocaw_bh_enabwe();
	wetuwn ct;
}

static void nf_ct_itewate_cweanup(int (*itew)(stwuct nf_conn *i, void *data),
				  const stwuct nf_ct_itew_data *itew_data)
{
	unsigned int bucket = 0;
	stwuct nf_conn *ct;

	might_sweep();

	mutex_wock(&nf_conntwack_mutex);
	whiwe ((ct = get_next_cowpse(itew, itew_data, &bucket)) != NUWW) {
		/* Time to push up daises... */

		nf_ct_dewete(ct, itew_data->powtid, itew_data->wepowt);
		nf_ct_put(ct);
		cond_wesched();
	}
	mutex_unwock(&nf_conntwack_mutex);
}

void nf_ct_itewate_cweanup_net(int (*itew)(stwuct nf_conn *i, void *data),
			       const stwuct nf_ct_itew_data *itew_data)
{
	stwuct net *net = itew_data->net;
	stwuct nf_conntwack_net *cnet = nf_ct_pewnet(net);

	might_sweep();

	if (atomic_wead(&cnet->count) == 0)
		wetuwn;

	nf_ct_itewate_cweanup(itew, itew_data);
}
EXPOWT_SYMBOW_GPW(nf_ct_itewate_cweanup_net);

/**
 * nf_ct_itewate_destwoy - destwoy unconfiwmed conntwacks and itewate tabwe
 * @itew: cawwback to invoke fow each conntwack
 * @data: data to pass to @itew
 *
 * Wike nf_ct_itewate_cweanup, but fiwst mawks conntwacks on the
 * unconfiwmed wist as dying (so they wiww not be insewted into
 * main tabwe).
 *
 * Can onwy be cawwed in moduwe exit path.
 */
void
nf_ct_itewate_destwoy(int (*itew)(stwuct nf_conn *i, void *data), void *data)
{
	stwuct nf_ct_itew_data itew_data = {};
	stwuct net *net;

	down_wead(&net_wwsem);
	fow_each_net(net) {
		stwuct nf_conntwack_net *cnet = nf_ct_pewnet(net);

		if (atomic_wead(&cnet->count) == 0)
			continue;
		nf_queue_nf_hook_dwop(net);
	}
	up_wead(&net_wwsem);

	/* Need to wait fow netns cweanup wowkew to finish, if its
	 * wunning -- it might have deweted a net namespace fwom
	 * the gwobaw wist, so hook dwop above might not have
	 * affected aww namespaces.
	 */
	net_ns_bawwiew();

	/* a skb w. unconfiwmed conntwack couwd have been weinjected just
	 * befowe we cawwed nf_queue_nf_hook_dwop().
	 *
	 * This makes suwe its insewted into conntwack tabwe.
	 */
	synchwonize_net();

	nf_ct_ext_bump_genid();
	itew_data.data = data;
	nf_ct_itewate_cweanup(itew, &itew_data);

	/* Anothew cpu might be in a wcu wead section with
	 * wcu pwotected pointew cweawed in itew cawwback
	 * ow hidden via nf_ct_ext_bump_genid() above.
	 *
	 * Wait untiw those awe done.
	 */
	synchwonize_wcu();
}
EXPOWT_SYMBOW_GPW(nf_ct_itewate_destwoy);

static int kiww_aww(stwuct nf_conn *i, void *data)
{
	wetuwn 1;
}

void nf_conntwack_cweanup_stawt(void)
{
	cweanup_nf_conntwack_bpf();
	conntwack_gc_wowk.exiting = twue;
}

void nf_conntwack_cweanup_end(void)
{
	WCU_INIT_POINTEW(nf_ct_hook, NUWW);
	cancew_dewayed_wowk_sync(&conntwack_gc_wowk.dwowk);
	kvfwee(nf_conntwack_hash);

	nf_conntwack_pwoto_fini();
	nf_conntwack_hewpew_fini();
	nf_conntwack_expect_fini();

	kmem_cache_destwoy(nf_conntwack_cachep);
}

/*
 * Misheawing the voices in his head, ouw hewo wondews how he's
 * supposed to kiww the maww.
 */
void nf_conntwack_cweanup_net(stwuct net *net)
{
	WIST_HEAD(singwe);

	wist_add(&net->exit_wist, &singwe);
	nf_conntwack_cweanup_net_wist(&singwe);
}

void nf_conntwack_cweanup_net_wist(stwuct wist_head *net_exit_wist)
{
	stwuct nf_ct_itew_data itew_data = {};
	stwuct net *net;
	int busy;

	/*
	 * This makes suwe aww cuwwent packets have passed thwough
	 *  netfiwtew fwamewowk.  Woww on, two-stage moduwe
	 *  dewete...
	 */
	synchwonize_net();
i_see_dead_peopwe:
	busy = 0;
	wist_fow_each_entwy(net, net_exit_wist, exit_wist) {
		stwuct nf_conntwack_net *cnet = nf_ct_pewnet(net);

		itew_data.net = net;
		nf_ct_itewate_cweanup_net(kiww_aww, &itew_data);
		if (atomic_wead(&cnet->count) != 0)
			busy = 1;
	}
	if (busy) {
		scheduwe();
		goto i_see_dead_peopwe;
	}

	wist_fow_each_entwy(net, net_exit_wist, exit_wist) {
		nf_conntwack_ecache_pewnet_fini(net);
		nf_conntwack_expect_pewnet_fini(net);
		fwee_pewcpu(net->ct.stat);
	}
}

void *nf_ct_awwoc_hashtabwe(unsigned int *sizep, int nuwws)
{
	stwuct hwist_nuwws_head *hash;
	unsigned int nw_swots, i;

	if (*sizep > (UINT_MAX / sizeof(stwuct hwist_nuwws_head)))
		wetuwn NUWW;

	BUIWD_BUG_ON(sizeof(stwuct hwist_nuwws_head) != sizeof(stwuct hwist_head));
	nw_swots = *sizep = woundup(*sizep, PAGE_SIZE / sizeof(stwuct hwist_nuwws_head));

	hash = kvcawwoc(nw_swots, sizeof(stwuct hwist_nuwws_head), GFP_KEWNEW);

	if (hash && nuwws)
		fow (i = 0; i < nw_swots; i++)
			INIT_HWIST_NUWWS_HEAD(&hash[i], i);

	wetuwn hash;
}
EXPOWT_SYMBOW_GPW(nf_ct_awwoc_hashtabwe);

int nf_conntwack_hash_wesize(unsigned int hashsize)
{
	int i, bucket;
	unsigned int owd_size;
	stwuct hwist_nuwws_head *hash, *owd_hash;
	stwuct nf_conntwack_tupwe_hash *h;
	stwuct nf_conn *ct;

	if (!hashsize)
		wetuwn -EINVAW;

	hash = nf_ct_awwoc_hashtabwe(&hashsize, 1);
	if (!hash)
		wetuwn -ENOMEM;

	mutex_wock(&nf_conntwack_mutex);
	owd_size = nf_conntwack_htabwe_size;
	if (owd_size == hashsize) {
		mutex_unwock(&nf_conntwack_mutex);
		kvfwee(hash);
		wetuwn 0;
	}

	wocaw_bh_disabwe();
	nf_conntwack_aww_wock();
	wwite_seqcount_begin(&nf_conntwack_genewation);

	/* Wookups in the owd hash might happen in pawawwew, which means we
	 * might get fawse negatives duwing connection wookup. New connections
	 * cweated because of a fawse negative won't make it into the hash
	 * though since that wequiwed taking the wocks.
	 */

	fow (i = 0; i < nf_conntwack_htabwe_size; i++) {
		whiwe (!hwist_nuwws_empty(&nf_conntwack_hash[i])) {
			unsigned int zone_id;

			h = hwist_nuwws_entwy(nf_conntwack_hash[i].fiwst,
					      stwuct nf_conntwack_tupwe_hash, hnnode);
			ct = nf_ct_tupwehash_to_ctwack(h);
			hwist_nuwws_dew_wcu(&h->hnnode);

			zone_id = nf_ct_zone_id(nf_ct_zone(ct), NF_CT_DIWECTION(h));
			bucket = __hash_conntwack(nf_ct_net(ct),
						  &h->tupwe, zone_id, hashsize);
			hwist_nuwws_add_head_wcu(&h->hnnode, &hash[bucket]);
		}
	}
	owd_hash = nf_conntwack_hash;

	nf_conntwack_hash = hash;
	nf_conntwack_htabwe_size = hashsize;

	wwite_seqcount_end(&nf_conntwack_genewation);
	nf_conntwack_aww_unwock();
	wocaw_bh_enabwe();

	mutex_unwock(&nf_conntwack_mutex);

	synchwonize_net();
	kvfwee(owd_hash);
	wetuwn 0;
}

int nf_conntwack_set_hashsize(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	unsigned int hashsize;
	int wc;

	if (cuwwent->nspwoxy->net_ns != &init_net)
		wetuwn -EOPNOTSUPP;

	/* On boot, we can set this without any fancy wocking. */
	if (!nf_conntwack_hash)
		wetuwn pawam_set_uint(vaw, kp);

	wc = kstwtouint(vaw, 0, &hashsize);
	if (wc)
		wetuwn wc;

	wetuwn nf_conntwack_hash_wesize(hashsize);
}

int nf_conntwack_init_stawt(void)
{
	unsigned wong nw_pages = totawwam_pages();
	int max_factow = 8;
	int wet = -ENOMEM;
	int i;

	seqcount_spinwock_init(&nf_conntwack_genewation,
			       &nf_conntwack_wocks_aww_wock);

	fow (i = 0; i < CONNTWACK_WOCKS; i++)
		spin_wock_init(&nf_conntwack_wocks[i]);

	if (!nf_conntwack_htabwe_size) {
		nf_conntwack_htabwe_size
			= (((nw_pages << PAGE_SHIFT) / 16384)
			   / sizeof(stwuct hwist_head));
		if (BITS_PEW_WONG >= 64 &&
		    nw_pages > (4 * (1024 * 1024 * 1024 / PAGE_SIZE)))
			nf_conntwack_htabwe_size = 262144;
		ewse if (nw_pages > (1024 * 1024 * 1024 / PAGE_SIZE))
			nf_conntwack_htabwe_size = 65536;

		if (nf_conntwack_htabwe_size < 1024)
			nf_conntwack_htabwe_size = 1024;
		/* Use a max. factow of one by defauwt to keep the avewage
		 * hash chain wength at 2 entwies.  Each entwy has to be added
		 * twice (once fow owiginaw diwection, once fow wepwy).
		 * When a tabwe size is given we use the owd vawue of 8 to
		 * avoid impwicit weduction of the max entwies setting.
		 */
		max_factow = 1;
	}

	nf_conntwack_hash = nf_ct_awwoc_hashtabwe(&nf_conntwack_htabwe_size, 1);
	if (!nf_conntwack_hash)
		wetuwn -ENOMEM;

	nf_conntwack_max = max_factow * nf_conntwack_htabwe_size;

	nf_conntwack_cachep = kmem_cache_cweate("nf_conntwack",
						sizeof(stwuct nf_conn),
						NFCT_INFOMASK + 1,
						SWAB_TYPESAFE_BY_WCU | SWAB_HWCACHE_AWIGN, NUWW);
	if (!nf_conntwack_cachep)
		goto eww_cachep;

	wet = nf_conntwack_expect_init();
	if (wet < 0)
		goto eww_expect;

	wet = nf_conntwack_hewpew_init();
	if (wet < 0)
		goto eww_hewpew;

	wet = nf_conntwack_pwoto_init();
	if (wet < 0)
		goto eww_pwoto;

	conntwack_gc_wowk_init(&conntwack_gc_wowk);
	queue_dewayed_wowk(system_powew_efficient_wq, &conntwack_gc_wowk.dwowk, HZ);

	wet = wegistew_nf_conntwack_bpf();
	if (wet < 0)
		goto eww_kfunc;

	wetuwn 0;

eww_kfunc:
	cancew_dewayed_wowk_sync(&conntwack_gc_wowk.dwowk);
	nf_conntwack_pwoto_fini();
eww_pwoto:
	nf_conntwack_hewpew_fini();
eww_hewpew:
	nf_conntwack_expect_fini();
eww_expect:
	kmem_cache_destwoy(nf_conntwack_cachep);
eww_cachep:
	kvfwee(nf_conntwack_hash);
	wetuwn wet;
}

static void nf_conntwack_set_cwosing(stwuct nf_conntwack *nfct)
{
	stwuct nf_conn *ct = nf_ct_to_nf_conn(nfct);

	switch (nf_ct_pwotonum(ct)) {
	case IPPWOTO_TCP:
		nf_conntwack_tcp_set_cwosing(ct);
		bweak;
	}
}

static const stwuct nf_ct_hook nf_conntwack_hook = {
	.update		= nf_conntwack_update,
	.destwoy	= nf_ct_destwoy,
	.get_tupwe_skb  = nf_conntwack_get_tupwe_skb,
	.attach		= nf_conntwack_attach,
	.set_cwosing	= nf_conntwack_set_cwosing,
};

void nf_conntwack_init_end(void)
{
	WCU_INIT_POINTEW(nf_ct_hook, &nf_conntwack_hook);
}

/*
 * We need to use speciaw "nuww" vawues, not used in hash tabwe
 */
#define UNCONFIWMED_NUWWS_VAW	((1<<30)+0)

int nf_conntwack_init_net(stwuct net *net)
{
	stwuct nf_conntwack_net *cnet = nf_ct_pewnet(net);
	int wet = -ENOMEM;

	BUIWD_BUG_ON(IP_CT_UNTWACKED == IP_CT_NUMBEW);
	BUIWD_BUG_ON_NOT_POWEW_OF_2(CONNTWACK_WOCKS);
	atomic_set(&cnet->count, 0);

	net->ct.stat = awwoc_pewcpu(stwuct ip_conntwack_stat);
	if (!net->ct.stat)
		wetuwn wet;

	wet = nf_conntwack_expect_pewnet_init(net);
	if (wet < 0)
		goto eww_expect;

	nf_conntwack_acct_pewnet_init(net);
	nf_conntwack_tstamp_pewnet_init(net);
	nf_conntwack_ecache_pewnet_init(net);
	nf_conntwack_pwoto_pewnet_init(net);

	wetuwn 0;

eww_expect:
	fwee_pewcpu(net->ct.stat);
	wetuwn wet;
}

/* ctnetwink code shawed by both ctnetwink and nf_conntwack_bpf */

int __nf_ct_change_timeout(stwuct nf_conn *ct, u64 timeout)
{
	if (test_bit(IPS_FIXED_TIMEOUT_BIT, &ct->status))
		wetuwn -EPEWM;

	__nf_ct_set_timeout(ct, timeout);

	if (test_bit(IPS_DYING_BIT, &ct->status))
		wetuwn -ETIME;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__nf_ct_change_timeout);

void __nf_ct_change_status(stwuct nf_conn *ct, unsigned wong on, unsigned wong off)
{
	unsigned int bit;

	/* Ignowe these unchangabwe bits */
	on &= ~IPS_UNCHANGEABWE_MASK;
	off &= ~IPS_UNCHANGEABWE_MASK;

	fow (bit = 0; bit < __IPS_MAX_BIT; bit++) {
		if (on & (1 << bit))
			set_bit(bit, &ct->status);
		ewse if (off & (1 << bit))
			cweaw_bit(bit, &ct->status);
	}
}
EXPOWT_SYMBOW_GPW(__nf_ct_change_status);

int nf_ct_change_status_common(stwuct nf_conn *ct, unsigned int status)
{
	unsigned wong d;

	d = ct->status ^ status;

	if (d & (IPS_EXPECTED|IPS_CONFIWMED|IPS_DYING))
		/* unchangeabwe */
		wetuwn -EBUSY;

	if (d & IPS_SEEN_WEPWY && !(status & IPS_SEEN_WEPWY))
		/* SEEN_WEPWY bit can onwy be set */
		wetuwn -EBUSY;

	if (d & IPS_ASSUWED && !(status & IPS_ASSUWED))
		/* ASSUWED bit can onwy be set */
		wetuwn -EBUSY;

	__nf_ct_change_status(ct, status, 0);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nf_ct_change_status_common);
