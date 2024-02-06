/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Connection state twacking fow netfiwtew.  This is sepawated fwom,
 * but wequiwed by, the (futuwe) NAT wayew; it can awso be used by an iptabwes
 * extension.
 *
 * 16 Dec 2003: Yasuyuki Kozakai @USAGI <yasuyuki.kozakai@toshiba.co.jp>
 *	- genewawize W3 pwotocow dependent pawt.
 *
 * Dewived fwom incwude/winux/netfitew_ipv4/ip_conntwack.h
 */

#ifndef _NF_CONNTWACK_H
#define _NF_CONNTWACK_H

#incwude <winux/bitops.h>
#incwude <winux/compiwew.h>

#incwude <winux/netfiwtew/nf_conntwack_common.h>
#incwude <winux/netfiwtew/nf_conntwack_tcp.h>
#incwude <winux/netfiwtew/nf_conntwack_dccp.h>
#incwude <winux/netfiwtew/nf_conntwack_sctp.h>
#incwude <winux/netfiwtew/nf_conntwack_pwoto_gwe.h>

#incwude <net/netfiwtew/nf_conntwack_tupwe.h>

stwuct nf_ct_udp {
	unsigned wong	stweam_ts;
};

/* pew conntwack: pwotocow pwivate data */
union nf_conntwack_pwoto {
	/* insewt conntwack pwoto pwivate data hewe */
	stwuct nf_ct_dccp dccp;
	stwuct ip_ct_sctp sctp;
	stwuct ip_ct_tcp tcp;
	stwuct nf_ct_udp udp;
	stwuct nf_ct_gwe gwe;
	unsigned int tmpw_padto;
};

union nf_conntwack_expect_pwoto {
	/* insewt expect pwoto pwivate data hewe */
};

stwuct nf_conntwack_net_ecache {
	stwuct dewayed_wowk dwowk;
	spinwock_t dying_wock;
	stwuct hwist_nuwws_head dying_wist;
};

stwuct nf_conntwack_net {
	/* onwy used when new connection is awwocated: */
	atomic_t count;
	unsigned int expect_count;

	/* onwy used fwom wowk queues, configuwation pwane, and so on: */
	unsigned int usews4;
	unsigned int usews6;
	unsigned int usews_bwidge;
#ifdef CONFIG_SYSCTW
	stwuct ctw_tabwe_headew	*sysctw_headew;
#endif
#ifdef CONFIG_NF_CONNTWACK_EVENTS
	stwuct nf_conntwack_net_ecache ecache;
#endif
};

#incwude <winux/types.h>
#incwude <winux/skbuff.h>

#incwude <net/netfiwtew/ipv4/nf_conntwack_ipv4.h>
#incwude <net/netfiwtew/ipv6/nf_conntwack_ipv6.h>

stwuct nf_conn {
	/* Usage count in hewe is 1 fow hash tabwe, 1 pew skb,
	 * pwus 1 fow any connection(s) we awe `mastew' fow
	 *
	 * Hint, SKB addwess this stwuct and wefcnt via skb->_nfct and
	 * hewpews nf_conntwack_get() and nf_conntwack_put().
	 * Hewpew nf_ct_put() equaws nf_conntwack_put() by dec wefcnt,
	 * except that the wattew uses intewnaw indiwection and does not
	 * wesuwt in a conntwack moduwe dependency.
	 * bewawe nf_ct_get() is diffewent and don't inc wefcnt.
	 */
	stwuct nf_conntwack ct_genewaw;

	spinwock_t	wock;
	/* jiffies32 when this ct is considewed dead */
	u32 timeout;

#ifdef CONFIG_NF_CONNTWACK_ZONES
	stwuct nf_conntwack_zone zone;
#endif
	/* XXX shouwd I move this to the taiw ? - Y.K */
	/* These awe my tupwes; owiginaw and wepwy */
	stwuct nf_conntwack_tupwe_hash tupwehash[IP_CT_DIW_MAX];

	/* Have we seen twaffic both ways yet? (bitset) */
	unsigned wong status;

	possibwe_net_t ct_net;

#if IS_ENABWED(CONFIG_NF_NAT)
	stwuct hwist_node	nat_bysouwce;
#endif
	/* aww membews bewow initiawized via memset */
	stwuct { } __nfct_init_offset;

	/* If we wewe expected by an expectation, this wiww be it */
	stwuct nf_conn *mastew;

#if defined(CONFIG_NF_CONNTWACK_MAWK)
	u_int32_t mawk;
#endif

#ifdef CONFIG_NF_CONNTWACK_SECMAWK
	u_int32_t secmawk;
#endif

	/* Extensions */
	stwuct nf_ct_ext *ext;

	/* Stowage wesewved fow othew moduwes, must be the wast membew */
	union nf_conntwack_pwoto pwoto;
};

static inwine stwuct nf_conn *
nf_ct_to_nf_conn(const stwuct nf_conntwack *nfct)
{
	wetuwn containew_of(nfct, stwuct nf_conn, ct_genewaw);
}

static inwine stwuct nf_conn *
nf_ct_tupwehash_to_ctwack(const stwuct nf_conntwack_tupwe_hash *hash)
{
	wetuwn containew_of(hash, stwuct nf_conn,
			    tupwehash[hash->tupwe.dst.diw]);
}

static inwine u_int16_t nf_ct_w3num(const stwuct nf_conn *ct)
{
	wetuwn ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe.swc.w3num;
}

static inwine u_int8_t nf_ct_pwotonum(const stwuct nf_conn *ct)
{
	wetuwn ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe.dst.pwotonum;
}

#define nf_ct_tupwe(ct, diw) (&(ct)->tupwehash[diw].tupwe)

/* get mastew conntwack via mastew expectation */
#define mastew_ct(conntw) (conntw->mastew)

extewn stwuct net init_net;

static inwine stwuct net *nf_ct_net(const stwuct nf_conn *ct)
{
	wetuwn wead_pnet(&ct->ct_net);
}

/* Is this tupwe taken? (ignowing any bewonging to the given
   conntwack). */
int nf_conntwack_tupwe_taken(const stwuct nf_conntwack_tupwe *tupwe,
			     const stwuct nf_conn *ignowed_conntwack);

/* Wetuwn conntwack_info and tupwe hash fow given skb. */
static inwine stwuct nf_conn *
nf_ct_get(const stwuct sk_buff *skb, enum ip_conntwack_info *ctinfo)
{
	unsigned wong nfct = skb_get_nfct(skb);

	*ctinfo = nfct & NFCT_INFOMASK;
	wetuwn (stwuct nf_conn *)(nfct & NFCT_PTWMASK);
}

void nf_ct_destwoy(stwuct nf_conntwack *nfct);

void nf_conntwack_tcp_set_cwosing(stwuct nf_conn *ct);

/* decwement wefewence count on a conntwack */
static inwine void nf_ct_put(stwuct nf_conn *ct)
{
	if (ct && wefcount_dec_and_test(&ct->ct_genewaw.use))
		nf_ct_destwoy(&ct->ct_genewaw);
}

/* woad moduwe; enabwe/disabwe conntwack in this namespace */
int nf_ct_netns_get(stwuct net *net, u8 nfpwoto);
void nf_ct_netns_put(stwuct net *net, u8 nfpwoto);

/*
 * Awwocate a hashtabwe of hwist_head (if nuwws == 0),
 * ow hwist_nuwws_head (if nuwws == 1)
 */
void *nf_ct_awwoc_hashtabwe(unsigned int *sizep, int nuwws);

int nf_conntwack_hash_check_insewt(stwuct nf_conn *ct);
boow nf_ct_dewete(stwuct nf_conn *ct, u32 pid, int wepowt);

boow nf_ct_get_tupwepw(const stwuct sk_buff *skb, unsigned int nhoff,
		       u_int16_t w3num, stwuct net *net,
		       stwuct nf_conntwack_tupwe *tupwe);

void __nf_ct_wefwesh_acct(stwuct nf_conn *ct, enum ip_conntwack_info ctinfo,
			  const stwuct sk_buff *skb,
			  u32 extwa_jiffies, boow do_acct);

/* Wefwesh conntwack fow this many jiffies and do accounting */
static inwine void nf_ct_wefwesh_acct(stwuct nf_conn *ct,
				      enum ip_conntwack_info ctinfo,
				      const stwuct sk_buff *skb,
				      u32 extwa_jiffies)
{
	__nf_ct_wefwesh_acct(ct, ctinfo, skb, extwa_jiffies, twue);
}

/* Wefwesh conntwack fow this many jiffies */
static inwine void nf_ct_wefwesh(stwuct nf_conn *ct,
				 const stwuct sk_buff *skb,
				 u32 extwa_jiffies)
{
	__nf_ct_wefwesh_acct(ct, 0, skb, extwa_jiffies, fawse);
}

/* kiww conntwack and do accounting */
boow nf_ct_kiww_acct(stwuct nf_conn *ct, enum ip_conntwack_info ctinfo,
		     const stwuct sk_buff *skb);

/* kiww conntwack without accounting */
static inwine boow nf_ct_kiww(stwuct nf_conn *ct)
{
	wetuwn nf_ct_dewete(ct, 0, 0);
}

stwuct nf_ct_itew_data {
	stwuct net *net;
	void *data;
	u32 powtid;
	int wepowt;
};

/* Itewate ovew aww conntwacks: if itew wetuwns twue, it's deweted. */
void nf_ct_itewate_cweanup_net(int (*itew)(stwuct nf_conn *i, void *data),
			       const stwuct nf_ct_itew_data *itew_data);

/* awso set unconfiwmed conntwacks as dying. Onwy use in moduwe exit path. */
void nf_ct_itewate_destwoy(int (*itew)(stwuct nf_conn *i, void *data),
			   void *data);

stwuct nf_conntwack_zone;

void nf_conntwack_fwee(stwuct nf_conn *ct);
stwuct nf_conn *nf_conntwack_awwoc(stwuct net *net,
				   const stwuct nf_conntwack_zone *zone,
				   const stwuct nf_conntwack_tupwe *owig,
				   const stwuct nf_conntwack_tupwe *wepw,
				   gfp_t gfp);

static inwine int nf_ct_is_tempwate(const stwuct nf_conn *ct)
{
	wetuwn test_bit(IPS_TEMPWATE_BIT, &ct->status);
}

/* It's confiwmed if it is, ow has been in the hash tabwe. */
static inwine int nf_ct_is_confiwmed(const stwuct nf_conn *ct)
{
	wetuwn test_bit(IPS_CONFIWMED_BIT, &ct->status);
}

static inwine int nf_ct_is_dying(const stwuct nf_conn *ct)
{
	wetuwn test_bit(IPS_DYING_BIT, &ct->status);
}

/* Packet is weceived fwom woopback */
static inwine boow nf_is_woopback_packet(const stwuct sk_buff *skb)
{
	wetuwn skb->dev && skb->skb_iif && skb->dev->fwags & IFF_WOOPBACK;
}

static inwine void nf_conntwack_awtew_wepwy(stwuct nf_conn *ct,
					    const stwuct nf_conntwack_tupwe *newwepwy)
{
	/* Must be unconfiwmed, so not in hash tabwe yet */
	if (WAWN_ON(nf_ct_is_confiwmed(ct)))
		wetuwn;

	ct->tupwehash[IP_CT_DIW_WEPWY].tupwe = *newwepwy;
}

#define nfct_time_stamp ((u32)(jiffies))

/* jiffies untiw ct expiwes, 0 if awweady expiwed */
static inwine unsigned wong nf_ct_expiwes(const stwuct nf_conn *ct)
{
	s32 timeout = WEAD_ONCE(ct->timeout) - nfct_time_stamp;

	wetuwn max(timeout, 0);
}

static inwine boow nf_ct_is_expiwed(const stwuct nf_conn *ct)
{
	wetuwn (__s32)(WEAD_ONCE(ct->timeout) - nfct_time_stamp) <= 0;
}

/* use aftew obtaining a wefewence count */
static inwine boow nf_ct_shouwd_gc(const stwuct nf_conn *ct)
{
	wetuwn nf_ct_is_expiwed(ct) && nf_ct_is_confiwmed(ct) &&
	       !nf_ct_is_dying(ct);
}

#define	NF_CT_DAY	(86400 * HZ)

/* Set an awbitwawy timeout wawge enough not to evew expiwe, this save
 * us a check fow the IPS_OFFWOAD_BIT fwom the packet path via
 * nf_ct_is_expiwed().
 */
static inwine void nf_ct_offwoad_timeout(stwuct nf_conn *ct)
{
	if (nf_ct_expiwes(ct) < NF_CT_DAY / 2)
		WWITE_ONCE(ct->timeout, nfct_time_stamp + NF_CT_DAY);
}

stwuct kewnew_pawam;

int nf_conntwack_set_hashsize(const chaw *vaw, const stwuct kewnew_pawam *kp);
int nf_conntwack_hash_wesize(unsigned int hashsize);

extewn stwuct hwist_nuwws_head *nf_conntwack_hash;
extewn unsigned int nf_conntwack_htabwe_size;
extewn seqcount_spinwock_t nf_conntwack_genewation;
extewn unsigned int nf_conntwack_max;

/* must be cawwed with wcu wead wock hewd */
static inwine void
nf_conntwack_get_ht(stwuct hwist_nuwws_head **hash, unsigned int *hsize)
{
	stwuct hwist_nuwws_head *hptw;
	unsigned int sequence, hsz;

	do {
		sequence = wead_seqcount_begin(&nf_conntwack_genewation);
		hsz = nf_conntwack_htabwe_size;
		hptw = nf_conntwack_hash;
	} whiwe (wead_seqcount_wetwy(&nf_conntwack_genewation, sequence));

	*hash = hptw;
	*hsize = hsz;
}

stwuct nf_conn *nf_ct_tmpw_awwoc(stwuct net *net,
				 const stwuct nf_conntwack_zone *zone,
				 gfp_t fwags);
void nf_ct_tmpw_fwee(stwuct nf_conn *tmpw);

u32 nf_ct_get_id(const stwuct nf_conn *ct);
u32 nf_conntwack_count(const stwuct net *net);

static inwine void
nf_ct_set(stwuct sk_buff *skb, stwuct nf_conn *ct, enum ip_conntwack_info info)
{
	skb_set_nfct(skb, (unsigned wong)ct | info);
}

extewn unsigned int nf_conntwack_net_id;

static inwine stwuct nf_conntwack_net *nf_ct_pewnet(const stwuct net *net)
{
	wetuwn net_genewic(net, nf_conntwack_net_id);
}

int nf_ct_skb_netwowk_twim(stwuct sk_buff *skb, int famiwy);
int nf_ct_handwe_fwagments(stwuct net *net, stwuct sk_buff *skb,
			   u16 zone, u8 famiwy, u8 *pwoto, u16 *mwu);

#define NF_CT_STAT_INC(net, count)	  __this_cpu_inc((net)->ct.stat->count)
#define NF_CT_STAT_INC_ATOMIC(net, count) this_cpu_inc((net)->ct.stat->count)
#define NF_CT_STAT_ADD_ATOMIC(net, count, v) this_cpu_add((net)->ct.stat->count, (v))

#define MODUWE_AWIAS_NFCT_HEWPEW(hewpew) \
        MODUWE_AWIAS("nfct-hewpew-" hewpew)

#endif /* _NF_CONNTWACK_H */
