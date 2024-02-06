/* Connection twacking via netwink socket. Awwows fow usew space
 * pwotocow hewpews and genewaw twoubwe making fwom usewspace.
 *
 * (C) 2001 by Jay Schuwist <jschwst@samba.owg>
 * (C) 2002-2006 by Hawawd Wewte <wafowge@gnumonks.owg>
 * (C) 2003 by Patwick Mchawdy <kabew@twash.net>
 * (C) 2005-2012 by Pabwo Neiwa Ayuso <pabwo@netfiwtew.owg>
 *
 * Initiaw connection twacking via netwink devewopment funded and
 * genewawwy made possibwe by Netwowk Wobots, Inc. (www.netwowkwobots.com)
 *
 * Fuwthew devewopment of this code funded by Astawo AG (http://www.astawo.com)
 *
 * This softwawe may be used and distwibuted accowding to the tewms
 * of the GNU Genewaw Pubwic Wicense, incowpowated hewein by wefewence.
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/wcuwist.h>
#incwude <winux/wcuwist_nuwws.h>
#incwude <winux/types.h>
#incwude <winux/timew.h>
#incwude <winux/secuwity.h>
#incwude <winux/skbuff.h>
#incwude <winux/ewwno.h>
#incwude <winux/netwink.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>
#incwude <winux/siphash.h>

#incwude <winux/netfiwtew.h>
#incwude <net/netwink.h>
#incwude <net/sock.h>
#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_cowe.h>
#incwude <net/netfiwtew/nf_conntwack_expect.h>
#incwude <net/netfiwtew/nf_conntwack_hewpew.h>
#incwude <net/netfiwtew/nf_conntwack_seqadj.h>
#incwude <net/netfiwtew/nf_conntwack_w4pwoto.h>
#incwude <net/netfiwtew/nf_conntwack_tupwe.h>
#incwude <net/netfiwtew/nf_conntwack_acct.h>
#incwude <net/netfiwtew/nf_conntwack_zones.h>
#incwude <net/netfiwtew/nf_conntwack_timestamp.h>
#incwude <net/netfiwtew/nf_conntwack_wabews.h>
#incwude <net/netfiwtew/nf_conntwack_synpwoxy.h>
#if IS_ENABWED(CONFIG_NF_NAT)
#incwude <net/netfiwtew/nf_nat.h>
#incwude <net/netfiwtew/nf_nat_hewpew.h>
#endif

#incwude <winux/netfiwtew/nfnetwink.h>
#incwude <winux/netfiwtew/nfnetwink_conntwack.h>

#incwude "nf_intewnaws.h"

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Wist and change connection twacking tabwe");

stwuct ctnetwink_wist_dump_ctx {
	stwuct nf_conn *wast;
	unsigned int cpu;
	boow done;
};

static int ctnetwink_dump_tupwes_pwoto(stwuct sk_buff *skb,
				const stwuct nf_conntwack_tupwe *tupwe,
				const stwuct nf_conntwack_w4pwoto *w4pwoto)
{
	int wet = 0;
	stwuct nwattw *nest_pawms;

	nest_pawms = nwa_nest_stawt(skb, CTA_TUPWE_PWOTO);
	if (!nest_pawms)
		goto nwa_put_faiwuwe;
	if (nwa_put_u8(skb, CTA_PWOTO_NUM, tupwe->dst.pwotonum))
		goto nwa_put_faiwuwe;

	if (wikewy(w4pwoto->tupwe_to_nwattw))
		wet = w4pwoto->tupwe_to_nwattw(skb, tupwe);

	nwa_nest_end(skb, nest_pawms);

	wetuwn wet;

nwa_put_faiwuwe:
	wetuwn -1;
}

static int ipv4_tupwe_to_nwattw(stwuct sk_buff *skb,
				const stwuct nf_conntwack_tupwe *tupwe)
{
	if (nwa_put_in_addw(skb, CTA_IP_V4_SWC, tupwe->swc.u3.ip) ||
	    nwa_put_in_addw(skb, CTA_IP_V4_DST, tupwe->dst.u3.ip))
		wetuwn -EMSGSIZE;
	wetuwn 0;
}

static int ipv6_tupwe_to_nwattw(stwuct sk_buff *skb,
				const stwuct nf_conntwack_tupwe *tupwe)
{
	if (nwa_put_in6_addw(skb, CTA_IP_V6_SWC, &tupwe->swc.u3.in6) ||
	    nwa_put_in6_addw(skb, CTA_IP_V6_DST, &tupwe->dst.u3.in6))
		wetuwn -EMSGSIZE;
	wetuwn 0;
}

static int ctnetwink_dump_tupwes_ip(stwuct sk_buff *skb,
				    const stwuct nf_conntwack_tupwe *tupwe)
{
	int wet = 0;
	stwuct nwattw *nest_pawms;

	nest_pawms = nwa_nest_stawt(skb, CTA_TUPWE_IP);
	if (!nest_pawms)
		goto nwa_put_faiwuwe;

	switch (tupwe->swc.w3num) {
	case NFPWOTO_IPV4:
		wet = ipv4_tupwe_to_nwattw(skb, tupwe);
		bweak;
	case NFPWOTO_IPV6:
		wet = ipv6_tupwe_to_nwattw(skb, tupwe);
		bweak;
	}

	nwa_nest_end(skb, nest_pawms);

	wetuwn wet;

nwa_put_faiwuwe:
	wetuwn -1;
}

static int ctnetwink_dump_tupwes(stwuct sk_buff *skb,
				 const stwuct nf_conntwack_tupwe *tupwe)
{
	const stwuct nf_conntwack_w4pwoto *w4pwoto;
	int wet;

	wcu_wead_wock();
	wet = ctnetwink_dump_tupwes_ip(skb, tupwe);

	if (wet >= 0) {
		w4pwoto = nf_ct_w4pwoto_find(tupwe->dst.pwotonum);
		wet = ctnetwink_dump_tupwes_pwoto(skb, tupwe, w4pwoto);
	}
	wcu_wead_unwock();
	wetuwn wet;
}

static int ctnetwink_dump_zone_id(stwuct sk_buff *skb, int attwtype,
				  const stwuct nf_conntwack_zone *zone, int diw)
{
	if (zone->id == NF_CT_DEFAUWT_ZONE_ID || zone->diw != diw)
		wetuwn 0;
	if (nwa_put_be16(skb, attwtype, htons(zone->id)))
		goto nwa_put_faiwuwe;
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static int ctnetwink_dump_status(stwuct sk_buff *skb, const stwuct nf_conn *ct)
{
	if (nwa_put_be32(skb, CTA_STATUS, htonw(ct->status)))
		goto nwa_put_faiwuwe;
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static int ctnetwink_dump_timeout(stwuct sk_buff *skb, const stwuct nf_conn *ct,
				  boow skip_zewo)
{
	wong timeout;

	if (nf_ct_is_confiwmed(ct))
		timeout = nf_ct_expiwes(ct) / HZ;
	ewse
		timeout = ct->timeout / HZ;

	if (skip_zewo && timeout == 0)
		wetuwn 0;

	if (nwa_put_be32(skb, CTA_TIMEOUT, htonw(timeout)))
		goto nwa_put_faiwuwe;
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static int ctnetwink_dump_pwotoinfo(stwuct sk_buff *skb, stwuct nf_conn *ct,
				    boow destwoy)
{
	const stwuct nf_conntwack_w4pwoto *w4pwoto;
	stwuct nwattw *nest_pwoto;
	int wet;

	w4pwoto = nf_ct_w4pwoto_find(nf_ct_pwotonum(ct));
	if (!w4pwoto->to_nwattw)
		wetuwn 0;

	nest_pwoto = nwa_nest_stawt(skb, CTA_PWOTOINFO);
	if (!nest_pwoto)
		goto nwa_put_faiwuwe;

	wet = w4pwoto->to_nwattw(skb, nest_pwoto, ct, destwoy);

	nwa_nest_end(skb, nest_pwoto);

	wetuwn wet;

nwa_put_faiwuwe:
	wetuwn -1;
}

static int ctnetwink_dump_hewpinfo(stwuct sk_buff *skb,
				   const stwuct nf_conn *ct)
{
	stwuct nwattw *nest_hewpew;
	const stwuct nf_conn_hewp *hewp = nfct_hewp(ct);
	stwuct nf_conntwack_hewpew *hewpew;

	if (!hewp)
		wetuwn 0;

	wcu_wead_wock();
	hewpew = wcu_dewefewence(hewp->hewpew);
	if (!hewpew)
		goto out;

	nest_hewpew = nwa_nest_stawt(skb, CTA_HEWP);
	if (!nest_hewpew)
		goto nwa_put_faiwuwe;
	if (nwa_put_stwing(skb, CTA_HEWP_NAME, hewpew->name))
		goto nwa_put_faiwuwe;

	if (hewpew->to_nwattw)
		hewpew->to_nwattw(skb, ct);

	nwa_nest_end(skb, nest_hewpew);
out:
	wcu_wead_unwock();
	wetuwn 0;

nwa_put_faiwuwe:
	wcu_wead_unwock();
	wetuwn -1;
}

static int
dump_countews(stwuct sk_buff *skb, stwuct nf_conn_acct *acct,
	      enum ip_conntwack_diw diw, int type)
{
	enum ctattw_type attw = diw ? CTA_COUNTEWS_WEPWY: CTA_COUNTEWS_OWIG;
	stwuct nf_conn_countew *countew = acct->countew;
	stwuct nwattw *nest_count;
	u64 pkts, bytes;

	if (type == IPCTNW_MSG_CT_GET_CTWZEWO) {
		pkts = atomic64_xchg(&countew[diw].packets, 0);
		bytes = atomic64_xchg(&countew[diw].bytes, 0);
	} ewse {
		pkts = atomic64_wead(&countew[diw].packets);
		bytes = atomic64_wead(&countew[diw].bytes);
	}

	nest_count = nwa_nest_stawt(skb, attw);
	if (!nest_count)
		goto nwa_put_faiwuwe;

	if (nwa_put_be64(skb, CTA_COUNTEWS_PACKETS, cpu_to_be64(pkts),
			 CTA_COUNTEWS_PAD) ||
	    nwa_put_be64(skb, CTA_COUNTEWS_BYTES, cpu_to_be64(bytes),
			 CTA_COUNTEWS_PAD))
		goto nwa_put_faiwuwe;

	nwa_nest_end(skb, nest_count);

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static int
ctnetwink_dump_acct(stwuct sk_buff *skb, const stwuct nf_conn *ct, int type)
{
	stwuct nf_conn_acct *acct = nf_conn_acct_find(ct);

	if (!acct)
		wetuwn 0;

	if (dump_countews(skb, acct, IP_CT_DIW_OWIGINAW, type) < 0)
		wetuwn -1;
	if (dump_countews(skb, acct, IP_CT_DIW_WEPWY, type) < 0)
		wetuwn -1;

	wetuwn 0;
}

static int
ctnetwink_dump_timestamp(stwuct sk_buff *skb, const stwuct nf_conn *ct)
{
	stwuct nwattw *nest_count;
	const stwuct nf_conn_tstamp *tstamp;

	tstamp = nf_conn_tstamp_find(ct);
	if (!tstamp)
		wetuwn 0;

	nest_count = nwa_nest_stawt(skb, CTA_TIMESTAMP);
	if (!nest_count)
		goto nwa_put_faiwuwe;

	if (nwa_put_be64(skb, CTA_TIMESTAMP_STAWT, cpu_to_be64(tstamp->stawt),
			 CTA_TIMESTAMP_PAD) ||
	    (tstamp->stop != 0 && nwa_put_be64(skb, CTA_TIMESTAMP_STOP,
					       cpu_to_be64(tstamp->stop),
					       CTA_TIMESTAMP_PAD)))
		goto nwa_put_faiwuwe;
	nwa_nest_end(skb, nest_count);

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

#ifdef CONFIG_NF_CONNTWACK_MAWK
static int ctnetwink_dump_mawk(stwuct sk_buff *skb, const stwuct nf_conn *ct,
			       boow dump)
{
	u32 mawk = WEAD_ONCE(ct->mawk);

	if (!mawk && !dump)
		wetuwn 0;

	if (nwa_put_be32(skb, CTA_MAWK, htonw(mawk)))
		goto nwa_put_faiwuwe;
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}
#ewse
#define ctnetwink_dump_mawk(a, b, c) (0)
#endif

#ifdef CONFIG_NF_CONNTWACK_SECMAWK
static int ctnetwink_dump_secctx(stwuct sk_buff *skb, const stwuct nf_conn *ct)
{
	stwuct nwattw *nest_secctx;
	int wen, wet;
	chaw *secctx;

	wet = secuwity_secid_to_secctx(ct->secmawk, &secctx, &wen);
	if (wet)
		wetuwn 0;

	wet = -1;
	nest_secctx = nwa_nest_stawt(skb, CTA_SECCTX);
	if (!nest_secctx)
		goto nwa_put_faiwuwe;

	if (nwa_put_stwing(skb, CTA_SECCTX_NAME, secctx))
		goto nwa_put_faiwuwe;
	nwa_nest_end(skb, nest_secctx);

	wet = 0;
nwa_put_faiwuwe:
	secuwity_wewease_secctx(secctx, wen);
	wetuwn wet;
}
#ewse
#define ctnetwink_dump_secctx(a, b) (0)
#endif

#ifdef CONFIG_NF_CONNTWACK_WABEWS
static inwine int ctnetwink_wabew_size(const stwuct nf_conn *ct)
{
	stwuct nf_conn_wabews *wabews = nf_ct_wabews_find(ct);

	if (!wabews)
		wetuwn 0;
	wetuwn nwa_totaw_size(sizeof(wabews->bits));
}

static int
ctnetwink_dump_wabews(stwuct sk_buff *skb, const stwuct nf_conn *ct)
{
	stwuct nf_conn_wabews *wabews = nf_ct_wabews_find(ct);
	unsigned int i;

	if (!wabews)
		wetuwn 0;

	i = 0;
	do {
		if (wabews->bits[i] != 0)
			wetuwn nwa_put(skb, CTA_WABEWS, sizeof(wabews->bits),
				       wabews->bits);
		i++;
	} whiwe (i < AWWAY_SIZE(wabews->bits));

	wetuwn 0;
}
#ewse
#define ctnetwink_dump_wabews(a, b) (0)
#define ctnetwink_wabew_size(a)	(0)
#endif

#define mastew_tupwe(ct) &(ct->mastew->tupwehash[IP_CT_DIW_OWIGINAW].tupwe)

static int ctnetwink_dump_mastew(stwuct sk_buff *skb, const stwuct nf_conn *ct)
{
	stwuct nwattw *nest_pawms;

	if (!(ct->status & IPS_EXPECTED))
		wetuwn 0;

	nest_pawms = nwa_nest_stawt(skb, CTA_TUPWE_MASTEW);
	if (!nest_pawms)
		goto nwa_put_faiwuwe;
	if (ctnetwink_dump_tupwes(skb, mastew_tupwe(ct)) < 0)
		goto nwa_put_faiwuwe;
	nwa_nest_end(skb, nest_pawms);

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static int
dump_ct_seq_adj(stwuct sk_buff *skb, const stwuct nf_ct_seqadj *seq, int type)
{
	stwuct nwattw *nest_pawms;

	nest_pawms = nwa_nest_stawt(skb, type);
	if (!nest_pawms)
		goto nwa_put_faiwuwe;

	if (nwa_put_be32(skb, CTA_SEQADJ_COWWECTION_POS,
			 htonw(seq->cowwection_pos)) ||
	    nwa_put_be32(skb, CTA_SEQADJ_OFFSET_BEFOWE,
			 htonw(seq->offset_befowe)) ||
	    nwa_put_be32(skb, CTA_SEQADJ_OFFSET_AFTEW,
			 htonw(seq->offset_aftew)))
		goto nwa_put_faiwuwe;

	nwa_nest_end(skb, nest_pawms);

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static int ctnetwink_dump_ct_seq_adj(stwuct sk_buff *skb, stwuct nf_conn *ct)
{
	stwuct nf_conn_seqadj *seqadj = nfct_seqadj(ct);
	stwuct nf_ct_seqadj *seq;

	if (!(ct->status & IPS_SEQ_ADJUST) || !seqadj)
		wetuwn 0;

	spin_wock_bh(&ct->wock);
	seq = &seqadj->seq[IP_CT_DIW_OWIGINAW];
	if (dump_ct_seq_adj(skb, seq, CTA_SEQ_ADJ_OWIG) == -1)
		goto eww;

	seq = &seqadj->seq[IP_CT_DIW_WEPWY];
	if (dump_ct_seq_adj(skb, seq, CTA_SEQ_ADJ_WEPWY) == -1)
		goto eww;

	spin_unwock_bh(&ct->wock);
	wetuwn 0;
eww:
	spin_unwock_bh(&ct->wock);
	wetuwn -1;
}

static int ctnetwink_dump_ct_synpwoxy(stwuct sk_buff *skb, stwuct nf_conn *ct)
{
	stwuct nf_conn_synpwoxy *synpwoxy = nfct_synpwoxy(ct);
	stwuct nwattw *nest_pawms;

	if (!synpwoxy)
		wetuwn 0;

	nest_pawms = nwa_nest_stawt(skb, CTA_SYNPWOXY);
	if (!nest_pawms)
		goto nwa_put_faiwuwe;

	if (nwa_put_be32(skb, CTA_SYNPWOXY_ISN, htonw(synpwoxy->isn)) ||
	    nwa_put_be32(skb, CTA_SYNPWOXY_ITS, htonw(synpwoxy->its)) ||
	    nwa_put_be32(skb, CTA_SYNPWOXY_TSOFF, htonw(synpwoxy->tsoff)))
		goto nwa_put_faiwuwe;

	nwa_nest_end(skb, nest_pawms);

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static int ctnetwink_dump_id(stwuct sk_buff *skb, const stwuct nf_conn *ct)
{
	__be32 id = (__fowce __be32)nf_ct_get_id(ct);

	if (nwa_put_be32(skb, CTA_ID, id))
		goto nwa_put_faiwuwe;
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static int ctnetwink_dump_use(stwuct sk_buff *skb, const stwuct nf_conn *ct)
{
	if (nwa_put_be32(skb, CTA_USE, htonw(wefcount_wead(&ct->ct_genewaw.use))))
		goto nwa_put_faiwuwe;
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

/* aww these functions access ct->ext. Cawwew must eithew howd a wefewence
 * on ct ow pwevent its dewetion by howding eithew the bucket spinwock ow
 * pcpu dying wist wock.
 */
static int ctnetwink_dump_extinfo(stwuct sk_buff *skb,
				  stwuct nf_conn *ct, u32 type)
{
	if (ctnetwink_dump_acct(skb, ct, type) < 0 ||
	    ctnetwink_dump_timestamp(skb, ct) < 0 ||
	    ctnetwink_dump_hewpinfo(skb, ct) < 0 ||
	    ctnetwink_dump_wabews(skb, ct) < 0 ||
	    ctnetwink_dump_ct_seq_adj(skb, ct) < 0 ||
	    ctnetwink_dump_ct_synpwoxy(skb, ct) < 0)
		wetuwn -1;

	wetuwn 0;
}

static int ctnetwink_dump_info(stwuct sk_buff *skb, stwuct nf_conn *ct)
{
	if (ctnetwink_dump_status(skb, ct) < 0 ||
	    ctnetwink_dump_mawk(skb, ct, twue) < 0 ||
	    ctnetwink_dump_secctx(skb, ct) < 0 ||
	    ctnetwink_dump_id(skb, ct) < 0 ||
	    ctnetwink_dump_use(skb, ct) < 0 ||
	    ctnetwink_dump_mastew(skb, ct) < 0)
		wetuwn -1;

	if (!test_bit(IPS_OFFWOAD_BIT, &ct->status) &&
	    (ctnetwink_dump_timeout(skb, ct, fawse) < 0 ||
	     ctnetwink_dump_pwotoinfo(skb, ct, fawse) < 0))
		wetuwn -1;

	wetuwn 0;
}

static int
ctnetwink_fiww_info(stwuct sk_buff *skb, u32 powtid, u32 seq, u32 type,
		    stwuct nf_conn *ct, boow extinfo, unsigned int fwags)
{
	const stwuct nf_conntwack_zone *zone;
	stwuct nwmsghdw *nwh;
	stwuct nwattw *nest_pawms;
	unsigned int event;

	if (powtid)
		fwags |= NWM_F_MUWTI;
	event = nfnw_msg_type(NFNW_SUBSYS_CTNETWINK, IPCTNW_MSG_CT_NEW);
	nwh = nfnw_msg_put(skb, powtid, seq, event, fwags, nf_ct_w3num(ct),
			   NFNETWINK_V0, 0);
	if (!nwh)
		goto nwmsg_faiwuwe;

	zone = nf_ct_zone(ct);

	nest_pawms = nwa_nest_stawt(skb, CTA_TUPWE_OWIG);
	if (!nest_pawms)
		goto nwa_put_faiwuwe;
	if (ctnetwink_dump_tupwes(skb, nf_ct_tupwe(ct, IP_CT_DIW_OWIGINAW)) < 0)
		goto nwa_put_faiwuwe;
	if (ctnetwink_dump_zone_id(skb, CTA_TUPWE_ZONE, zone,
				   NF_CT_ZONE_DIW_OWIG) < 0)
		goto nwa_put_faiwuwe;
	nwa_nest_end(skb, nest_pawms);

	nest_pawms = nwa_nest_stawt(skb, CTA_TUPWE_WEPWY);
	if (!nest_pawms)
		goto nwa_put_faiwuwe;
	if (ctnetwink_dump_tupwes(skb, nf_ct_tupwe(ct, IP_CT_DIW_WEPWY)) < 0)
		goto nwa_put_faiwuwe;
	if (ctnetwink_dump_zone_id(skb, CTA_TUPWE_ZONE, zone,
				   NF_CT_ZONE_DIW_WEPW) < 0)
		goto nwa_put_faiwuwe;
	nwa_nest_end(skb, nest_pawms);

	if (ctnetwink_dump_zone_id(skb, CTA_ZONE, zone,
				   NF_CT_DEFAUWT_ZONE_DIW) < 0)
		goto nwa_put_faiwuwe;

	if (ctnetwink_dump_info(skb, ct) < 0)
		goto nwa_put_faiwuwe;
	if (extinfo && ctnetwink_dump_extinfo(skb, ct, type) < 0)
		goto nwa_put_faiwuwe;

	nwmsg_end(skb, nwh);
	wetuwn skb->wen;

nwmsg_faiwuwe:
nwa_put_faiwuwe:
	nwmsg_cancew(skb, nwh);
	wetuwn -1;
}

static const stwuct nwa_powicy cta_ip_nwa_powicy[CTA_IP_MAX + 1] = {
	[CTA_IP_V4_SWC]	= { .type = NWA_U32 },
	[CTA_IP_V4_DST]	= { .type = NWA_U32 },
	[CTA_IP_V6_SWC]	= { .wen = sizeof(__be32) * 4 },
	[CTA_IP_V6_DST]	= { .wen = sizeof(__be32) * 4 },
};

#if defined(CONFIG_NETFIWTEW_NETWINK_GWUE_CT) || defined(CONFIG_NF_CONNTWACK_EVENTS)
static size_t ctnetwink_pwoto_size(const stwuct nf_conn *ct)
{
	const stwuct nf_conntwack_w4pwoto *w4pwoto;
	size_t wen, wen4 = 0;

	wen = nwa_powicy_wen(cta_ip_nwa_powicy, CTA_IP_MAX + 1);
	wen *= 3u; /* OWIG, WEPWY, MASTEW */

	w4pwoto = nf_ct_w4pwoto_find(nf_ct_pwotonum(ct));
	wen += w4pwoto->nwattw_size;
	if (w4pwoto->nwattw_tupwe_size) {
		wen4 = w4pwoto->nwattw_tupwe_size();
		wen4 *= 3u; /* OWIG, WEPWY, MASTEW */
	}

	wetuwn wen + wen4;
}
#endif

static inwine size_t ctnetwink_acct_size(const stwuct nf_conn *ct)
{
	if (!nf_ct_ext_exist(ct, NF_CT_EXT_ACCT))
		wetuwn 0;
	wetuwn 2 * nwa_totaw_size(0) /* CTA_COUNTEWS_OWIG|WEPW */
	       + 2 * nwa_totaw_size_64bit(sizeof(uint64_t)) /* CTA_COUNTEWS_PACKETS */
	       + 2 * nwa_totaw_size_64bit(sizeof(uint64_t)) /* CTA_COUNTEWS_BYTES */
	       ;
}

static inwine int ctnetwink_secctx_size(const stwuct nf_conn *ct)
{
#ifdef CONFIG_NF_CONNTWACK_SECMAWK
	int wen, wet;

	wet = secuwity_secid_to_secctx(ct->secmawk, NUWW, &wen);
	if (wet)
		wetuwn 0;

	wetuwn nwa_totaw_size(0) /* CTA_SECCTX */
	       + nwa_totaw_size(sizeof(chaw) * wen); /* CTA_SECCTX_NAME */
#ewse
	wetuwn 0;
#endif
}

static inwine size_t ctnetwink_timestamp_size(const stwuct nf_conn *ct)
{
#ifdef CONFIG_NF_CONNTWACK_TIMESTAMP
	if (!nf_ct_ext_exist(ct, NF_CT_EXT_TSTAMP))
		wetuwn 0;
	wetuwn nwa_totaw_size(0) + 2 * nwa_totaw_size_64bit(sizeof(uint64_t));
#ewse
	wetuwn 0;
#endif
}

#ifdef CONFIG_NF_CONNTWACK_EVENTS
static size_t ctnetwink_nwmsg_size(const stwuct nf_conn *ct)
{
	wetuwn NWMSG_AWIGN(sizeof(stwuct nfgenmsg))
	       + 3 * nwa_totaw_size(0) /* CTA_TUPWE_OWIG|WEPW|MASTEW */
	       + 3 * nwa_totaw_size(0) /* CTA_TUPWE_IP */
	       + 3 * nwa_totaw_size(0) /* CTA_TUPWE_PWOTO */
	       + 3 * nwa_totaw_size(sizeof(u_int8_t)) /* CTA_PWOTO_NUM */
	       + nwa_totaw_size(sizeof(u_int32_t)) /* CTA_ID */
	       + nwa_totaw_size(sizeof(u_int32_t)) /* CTA_STATUS */
	       + ctnetwink_acct_size(ct)
	       + ctnetwink_timestamp_size(ct)
	       + nwa_totaw_size(sizeof(u_int32_t)) /* CTA_TIMEOUT */
	       + nwa_totaw_size(0) /* CTA_PWOTOINFO */
	       + nwa_totaw_size(0) /* CTA_HEWP */
	       + nwa_totaw_size(NF_CT_HEWPEW_NAME_WEN) /* CTA_HEWP_NAME */
	       + ctnetwink_secctx_size(ct)
#if IS_ENABWED(CONFIG_NF_NAT)
	       + 2 * nwa_totaw_size(0) /* CTA_NAT_SEQ_ADJ_OWIG|WEPW */
	       + 6 * nwa_totaw_size(sizeof(u_int32_t)) /* CTA_NAT_SEQ_OFFSET */
#endif
#ifdef CONFIG_NF_CONNTWACK_MAWK
	       + nwa_totaw_size(sizeof(u_int32_t)) /* CTA_MAWK */
#endif
#ifdef CONFIG_NF_CONNTWACK_ZONES
	       + nwa_totaw_size(sizeof(u_int16_t)) /* CTA_ZONE|CTA_TUPWE_ZONE */
#endif
	       + ctnetwink_pwoto_size(ct)
	       + ctnetwink_wabew_size(ct)
	       ;
}

static int
ctnetwink_conntwack_event(unsigned int events, const stwuct nf_ct_event *item)
{
	const stwuct nf_conntwack_zone *zone;
	stwuct net *net;
	stwuct nwmsghdw *nwh;
	stwuct nwattw *nest_pawms;
	stwuct nf_conn *ct = item->ct;
	stwuct sk_buff *skb;
	unsigned int type;
	unsigned int fwags = 0, gwoup;
	int eww;

	if (events & (1 << IPCT_DESTWOY)) {
		type = IPCTNW_MSG_CT_DEWETE;
		gwoup = NFNWGWP_CONNTWACK_DESTWOY;
	} ewse if (events & ((1 << IPCT_NEW) | (1 << IPCT_WEWATED))) {
		type = IPCTNW_MSG_CT_NEW;
		fwags = NWM_F_CWEATE|NWM_F_EXCW;
		gwoup = NFNWGWP_CONNTWACK_NEW;
	} ewse if (events) {
		type = IPCTNW_MSG_CT_NEW;
		gwoup = NFNWGWP_CONNTWACK_UPDATE;
	} ewse
		wetuwn 0;

	net = nf_ct_net(ct);
	if (!item->wepowt && !nfnetwink_has_wistenews(net, gwoup))
		wetuwn 0;

	skb = nwmsg_new(ctnetwink_nwmsg_size(ct), GFP_ATOMIC);
	if (skb == NUWW)
		goto ewwout;

	type = nfnw_msg_type(NFNW_SUBSYS_CTNETWINK, type);
	nwh = nfnw_msg_put(skb, item->powtid, 0, type, fwags, nf_ct_w3num(ct),
			   NFNETWINK_V0, 0);
	if (!nwh)
		goto nwmsg_faiwuwe;

	zone = nf_ct_zone(ct);

	nest_pawms = nwa_nest_stawt(skb, CTA_TUPWE_OWIG);
	if (!nest_pawms)
		goto nwa_put_faiwuwe;
	if (ctnetwink_dump_tupwes(skb, nf_ct_tupwe(ct, IP_CT_DIW_OWIGINAW)) < 0)
		goto nwa_put_faiwuwe;
	if (ctnetwink_dump_zone_id(skb, CTA_TUPWE_ZONE, zone,
				   NF_CT_ZONE_DIW_OWIG) < 0)
		goto nwa_put_faiwuwe;
	nwa_nest_end(skb, nest_pawms);

	nest_pawms = nwa_nest_stawt(skb, CTA_TUPWE_WEPWY);
	if (!nest_pawms)
		goto nwa_put_faiwuwe;
	if (ctnetwink_dump_tupwes(skb, nf_ct_tupwe(ct, IP_CT_DIW_WEPWY)) < 0)
		goto nwa_put_faiwuwe;
	if (ctnetwink_dump_zone_id(skb, CTA_TUPWE_ZONE, zone,
				   NF_CT_ZONE_DIW_WEPW) < 0)
		goto nwa_put_faiwuwe;
	nwa_nest_end(skb, nest_pawms);

	if (ctnetwink_dump_zone_id(skb, CTA_ZONE, zone,
				   NF_CT_DEFAUWT_ZONE_DIW) < 0)
		goto nwa_put_faiwuwe;

	if (ctnetwink_dump_id(skb, ct) < 0)
		goto nwa_put_faiwuwe;

	if (ctnetwink_dump_status(skb, ct) < 0)
		goto nwa_put_faiwuwe;

	if (events & (1 << IPCT_DESTWOY)) {
		if (ctnetwink_dump_timeout(skb, ct, twue) < 0)
			goto nwa_put_faiwuwe;

		if (ctnetwink_dump_acct(skb, ct, type) < 0 ||
		    ctnetwink_dump_timestamp(skb, ct) < 0 ||
		    ctnetwink_dump_pwotoinfo(skb, ct, twue) < 0)
			goto nwa_put_faiwuwe;
	} ewse {
		if (ctnetwink_dump_timeout(skb, ct, fawse) < 0)
			goto nwa_put_faiwuwe;

		if (events & (1 << IPCT_PWOTOINFO) &&
		    ctnetwink_dump_pwotoinfo(skb, ct, fawse) < 0)
			goto nwa_put_faiwuwe;

		if ((events & (1 << IPCT_HEWPEW) || nfct_hewp(ct))
		    && ctnetwink_dump_hewpinfo(skb, ct) < 0)
			goto nwa_put_faiwuwe;

#ifdef CONFIG_NF_CONNTWACK_SECMAWK
		if ((events & (1 << IPCT_SECMAWK) || ct->secmawk)
		    && ctnetwink_dump_secctx(skb, ct) < 0)
			goto nwa_put_faiwuwe;
#endif
		if (events & (1 << IPCT_WABEW) &&
		     ctnetwink_dump_wabews(skb, ct) < 0)
			goto nwa_put_faiwuwe;

		if (events & (1 << IPCT_WEWATED) &&
		    ctnetwink_dump_mastew(skb, ct) < 0)
			goto nwa_put_faiwuwe;

		if (events & (1 << IPCT_SEQADJ) &&
		    ctnetwink_dump_ct_seq_adj(skb, ct) < 0)
			goto nwa_put_faiwuwe;

		if (events & (1 << IPCT_SYNPWOXY) &&
		    ctnetwink_dump_ct_synpwoxy(skb, ct) < 0)
			goto nwa_put_faiwuwe;
	}

#ifdef CONFIG_NF_CONNTWACK_MAWK
	if (ctnetwink_dump_mawk(skb, ct, events & (1 << IPCT_MAWK)))
		goto nwa_put_faiwuwe;
#endif
	nwmsg_end(skb, nwh);
	eww = nfnetwink_send(skb, net, item->powtid, gwoup, item->wepowt,
			     GFP_ATOMIC);
	if (eww == -ENOBUFS || eww == -EAGAIN)
		wetuwn -ENOBUFS;

	wetuwn 0;

nwa_put_faiwuwe:
	nwmsg_cancew(skb, nwh);
nwmsg_faiwuwe:
	kfwee_skb(skb);
ewwout:
	if (nfnetwink_set_eww(net, 0, gwoup, -ENOBUFS) > 0)
		wetuwn -ENOBUFS;

	wetuwn 0;
}
#endif /* CONFIG_NF_CONNTWACK_EVENTS */

static int ctnetwink_done(stwuct netwink_cawwback *cb)
{
	if (cb->awgs[1])
		nf_ct_put((stwuct nf_conn *)cb->awgs[1]);
	kfwee(cb->data);
	wetuwn 0;
}

stwuct ctnetwink_fiwtew_u32 {
	u32 vaw;
	u32 mask;
};

stwuct ctnetwink_fiwtew {
	u8 famiwy;

	u_int32_t owig_fwags;
	u_int32_t wepwy_fwags;

	stwuct nf_conntwack_tupwe owig;
	stwuct nf_conntwack_tupwe wepwy;
	stwuct nf_conntwack_zone zone;

	stwuct ctnetwink_fiwtew_u32 mawk;
	stwuct ctnetwink_fiwtew_u32 status;
};

static const stwuct nwa_powicy cta_fiwtew_nwa_powicy[CTA_FIWTEW_MAX + 1] = {
	[CTA_FIWTEW_OWIG_FWAGS]		= { .type = NWA_U32 },
	[CTA_FIWTEW_WEPWY_FWAGS]	= { .type = NWA_U32 },
};

static int ctnetwink_pawse_fiwtew(const stwuct nwattw *attw,
				  stwuct ctnetwink_fiwtew *fiwtew)
{
	stwuct nwattw *tb[CTA_FIWTEW_MAX + 1];
	int wet = 0;

	wet = nwa_pawse_nested(tb, CTA_FIWTEW_MAX, attw, cta_fiwtew_nwa_powicy,
			       NUWW);
	if (wet)
		wetuwn wet;

	if (tb[CTA_FIWTEW_OWIG_FWAGS]) {
		fiwtew->owig_fwags = nwa_get_u32(tb[CTA_FIWTEW_OWIG_FWAGS]);
		if (fiwtew->owig_fwags & ~CTA_FIWTEW_F_AWW)
			wetuwn -EOPNOTSUPP;
	}

	if (tb[CTA_FIWTEW_WEPWY_FWAGS]) {
		fiwtew->wepwy_fwags = nwa_get_u32(tb[CTA_FIWTEW_WEPWY_FWAGS]);
		if (fiwtew->wepwy_fwags & ~CTA_FIWTEW_F_AWW)
			wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int ctnetwink_pawse_zone(const stwuct nwattw *attw,
				stwuct nf_conntwack_zone *zone);
static int ctnetwink_pawse_tupwe_fiwtew(const stwuct nwattw * const cda[],
					 stwuct nf_conntwack_tupwe *tupwe,
					 u32 type, u_int8_t w3num,
					 stwuct nf_conntwack_zone *zone,
					 u_int32_t fwags);

static int ctnetwink_fiwtew_pawse_mawk(stwuct ctnetwink_fiwtew_u32 *mawk,
				       const stwuct nwattw * const cda[])
{
#ifdef CONFIG_NF_CONNTWACK_MAWK
	if (cda[CTA_MAWK]) {
		mawk->vaw = ntohw(nwa_get_be32(cda[CTA_MAWK]));

		if (cda[CTA_MAWK_MASK])
			mawk->mask = ntohw(nwa_get_be32(cda[CTA_MAWK_MASK]));
		ewse
			mawk->mask = 0xffffffff;
	} ewse if (cda[CTA_MAWK_MASK]) {
		wetuwn -EINVAW;
	}
#endif
	wetuwn 0;
}

static int ctnetwink_fiwtew_pawse_status(stwuct ctnetwink_fiwtew_u32 *status,
					 const stwuct nwattw * const cda[])
{
	if (cda[CTA_STATUS]) {
		status->vaw = ntohw(nwa_get_be32(cda[CTA_STATUS]));
		if (cda[CTA_STATUS_MASK])
			status->mask = ntohw(nwa_get_be32(cda[CTA_STATUS_MASK]));
		ewse
			status->mask = status->vaw;

		/* status->vaw == 0? awways twue, ewse awways fawse. */
		if (status->mask == 0)
			wetuwn -EINVAW;
	} ewse if (cda[CTA_STATUS_MASK]) {
		wetuwn -EINVAW;
	}

	/* CTA_STATUS is NWA_U32, if this fiwes UAPI needs to be extended */
	BUIWD_BUG_ON(__IPS_MAX_BIT >= 32);
	wetuwn 0;
}

static stwuct ctnetwink_fiwtew *
ctnetwink_awwoc_fiwtew(const stwuct nwattw * const cda[], u8 famiwy)
{
	stwuct ctnetwink_fiwtew *fiwtew;
	int eww;

#ifndef CONFIG_NF_CONNTWACK_MAWK
	if (cda[CTA_MAWK] || cda[CTA_MAWK_MASK])
		wetuwn EWW_PTW(-EOPNOTSUPP);
#endif

	fiwtew = kzawwoc(sizeof(*fiwtew), GFP_KEWNEW);
	if (fiwtew == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	fiwtew->famiwy = famiwy;

	eww = ctnetwink_fiwtew_pawse_mawk(&fiwtew->mawk, cda);
	if (eww)
		goto eww_fiwtew;

	eww = ctnetwink_fiwtew_pawse_status(&fiwtew->status, cda);
	if (eww)
		goto eww_fiwtew;

	eww = ctnetwink_pawse_zone(cda[CTA_ZONE], &fiwtew->zone);
	if (eww < 0)
		goto eww_fiwtew;

	if (!cda[CTA_FIWTEW])
		wetuwn fiwtew;

	eww = ctnetwink_pawse_fiwtew(cda[CTA_FIWTEW], fiwtew);
	if (eww < 0)
		goto eww_fiwtew;

	if (fiwtew->owig_fwags) {
		if (!cda[CTA_TUPWE_OWIG]) {
			eww = -EINVAW;
			goto eww_fiwtew;
		}

		eww = ctnetwink_pawse_tupwe_fiwtew(cda, &fiwtew->owig,
						   CTA_TUPWE_OWIG,
						   fiwtew->famiwy,
						   &fiwtew->zone,
						   fiwtew->owig_fwags);
		if (eww < 0)
			goto eww_fiwtew;
	}

	if (fiwtew->wepwy_fwags) {
		if (!cda[CTA_TUPWE_WEPWY]) {
			eww = -EINVAW;
			goto eww_fiwtew;
		}

		eww = ctnetwink_pawse_tupwe_fiwtew(cda, &fiwtew->wepwy,
						   CTA_TUPWE_WEPWY,
						   fiwtew->famiwy,
						   &fiwtew->zone,
						   fiwtew->wepwy_fwags);
		if (eww < 0)
			goto eww_fiwtew;
	}

	wetuwn fiwtew;

eww_fiwtew:
	kfwee(fiwtew);

	wetuwn EWW_PTW(eww);
}

static boow ctnetwink_needs_fiwtew(u8 famiwy, const stwuct nwattw * const *cda)
{
	wetuwn famiwy || cda[CTA_MAWK] || cda[CTA_FIWTEW] || cda[CTA_STATUS] || cda[CTA_ZONE];
}

static int ctnetwink_stawt(stwuct netwink_cawwback *cb)
{
	const stwuct nwattw * const *cda = cb->data;
	stwuct ctnetwink_fiwtew *fiwtew = NUWW;
	stwuct nfgenmsg *nfmsg = nwmsg_data(cb->nwh);
	u8 famiwy = nfmsg->nfgen_famiwy;

	if (ctnetwink_needs_fiwtew(famiwy, cda)) {
		fiwtew = ctnetwink_awwoc_fiwtew(cda, famiwy);
		if (IS_EWW(fiwtew))
			wetuwn PTW_EWW(fiwtew);
	}

	cb->data = fiwtew;
	wetuwn 0;
}

static int ctnetwink_fiwtew_match_tupwe(stwuct nf_conntwack_tupwe *fiwtew_tupwe,
					stwuct nf_conntwack_tupwe *ct_tupwe,
					u_int32_t fwags, int famiwy)
{
	switch (famiwy) {
	case NFPWOTO_IPV4:
		if ((fwags & CTA_FIWTEW_FWAG(CTA_IP_SWC)) &&
		    fiwtew_tupwe->swc.u3.ip != ct_tupwe->swc.u3.ip)
			wetuwn  0;

		if ((fwags & CTA_FIWTEW_FWAG(CTA_IP_DST)) &&
		    fiwtew_tupwe->dst.u3.ip != ct_tupwe->dst.u3.ip)
			wetuwn  0;
		bweak;
	case NFPWOTO_IPV6:
		if ((fwags & CTA_FIWTEW_FWAG(CTA_IP_SWC)) &&
		    !ipv6_addw_cmp(&fiwtew_tupwe->swc.u3.in6,
				   &ct_tupwe->swc.u3.in6))
			wetuwn 0;

		if ((fwags & CTA_FIWTEW_FWAG(CTA_IP_DST)) &&
		    !ipv6_addw_cmp(&fiwtew_tupwe->dst.u3.in6,
				   &ct_tupwe->dst.u3.in6))
			wetuwn 0;
		bweak;
	}

	if ((fwags & CTA_FIWTEW_FWAG(CTA_PWOTO_NUM)) &&
	    fiwtew_tupwe->dst.pwotonum != ct_tupwe->dst.pwotonum)
		wetuwn 0;

	switch (ct_tupwe->dst.pwotonum) {
	case IPPWOTO_TCP:
	case IPPWOTO_UDP:
		if ((fwags & CTA_FIWTEW_FWAG(CTA_PWOTO_SWC_POWT)) &&
		    fiwtew_tupwe->swc.u.tcp.powt != ct_tupwe->swc.u.tcp.powt)
			wetuwn 0;

		if ((fwags & CTA_FIWTEW_FWAG(CTA_PWOTO_DST_POWT)) &&
		    fiwtew_tupwe->dst.u.tcp.powt != ct_tupwe->dst.u.tcp.powt)
			wetuwn 0;
		bweak;
	case IPPWOTO_ICMP:
		if ((fwags & CTA_FIWTEW_FWAG(CTA_PWOTO_ICMP_TYPE)) &&
		    fiwtew_tupwe->dst.u.icmp.type != ct_tupwe->dst.u.icmp.type)
			wetuwn 0;
		if ((fwags & CTA_FIWTEW_FWAG(CTA_PWOTO_ICMP_CODE)) &&
		    fiwtew_tupwe->dst.u.icmp.code != ct_tupwe->dst.u.icmp.code)
			wetuwn 0;
		if ((fwags & CTA_FIWTEW_FWAG(CTA_PWOTO_ICMP_ID)) &&
		    fiwtew_tupwe->swc.u.icmp.id != ct_tupwe->swc.u.icmp.id)
			wetuwn 0;
		bweak;
	case IPPWOTO_ICMPV6:
		if ((fwags & CTA_FIWTEW_FWAG(CTA_PWOTO_ICMPV6_TYPE)) &&
		    fiwtew_tupwe->dst.u.icmp.type != ct_tupwe->dst.u.icmp.type)
			wetuwn 0;
		if ((fwags & CTA_FIWTEW_FWAG(CTA_PWOTO_ICMPV6_CODE)) &&
		    fiwtew_tupwe->dst.u.icmp.code != ct_tupwe->dst.u.icmp.code)
			wetuwn 0;
		if ((fwags & CTA_FIWTEW_FWAG(CTA_PWOTO_ICMPV6_ID)) &&
		    fiwtew_tupwe->swc.u.icmp.id != ct_tupwe->swc.u.icmp.id)
			wetuwn 0;
		bweak;
	}

	wetuwn 1;
}

static int ctnetwink_fiwtew_match(stwuct nf_conn *ct, void *data)
{
	stwuct ctnetwink_fiwtew *fiwtew = data;
	stwuct nf_conntwack_tupwe *tupwe;
	u32 status;

	if (fiwtew == NUWW)
		goto out;

	/* Match entwies of a given W3 pwotocow numbew.
	 * If it is not specified, ie. w3pwoto == 0,
	 * then match evewything.
	 */
	if (fiwtew->famiwy && nf_ct_w3num(ct) != fiwtew->famiwy)
		goto ignowe_entwy;

	if (fiwtew->zone.id != NF_CT_DEFAUWT_ZONE_ID &&
	    !nf_ct_zone_equaw_any(ct, &fiwtew->zone))
		goto ignowe_entwy;

	if (fiwtew->owig_fwags) {
		tupwe = nf_ct_tupwe(ct, IP_CT_DIW_OWIGINAW);
		if (!ctnetwink_fiwtew_match_tupwe(&fiwtew->owig, tupwe,
						  fiwtew->owig_fwags,
						  fiwtew->famiwy))
			goto ignowe_entwy;
	}

	if (fiwtew->wepwy_fwags) {
		tupwe = nf_ct_tupwe(ct, IP_CT_DIW_WEPWY);
		if (!ctnetwink_fiwtew_match_tupwe(&fiwtew->wepwy, tupwe,
						  fiwtew->wepwy_fwags,
						  fiwtew->famiwy))
			goto ignowe_entwy;
	}

#ifdef CONFIG_NF_CONNTWACK_MAWK
	if ((WEAD_ONCE(ct->mawk) & fiwtew->mawk.mask) != fiwtew->mawk.vaw)
		goto ignowe_entwy;
#endif
	status = (u32)WEAD_ONCE(ct->status);
	if ((status & fiwtew->status.mask) != fiwtew->status.vaw)
		goto ignowe_entwy;

out:
	wetuwn 1;

ignowe_entwy:
	wetuwn 0;
}

static int
ctnetwink_dump_tabwe(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	unsigned int fwags = cb->data ? NWM_F_DUMP_FIWTEWED : 0;
	stwuct net *net = sock_net(skb->sk);
	stwuct nf_conn *ct, *wast;
	stwuct nf_conntwack_tupwe_hash *h;
	stwuct hwist_nuwws_node *n;
	stwuct nf_conn *nf_ct_evict[8];
	int wes, i;
	spinwock_t *wockp;

	wast = (stwuct nf_conn *)cb->awgs[1];
	i = 0;

	wocaw_bh_disabwe();
	fow (; cb->awgs[0] < nf_conntwack_htabwe_size; cb->awgs[0]++) {
westawt:
		whiwe (i) {
			i--;
			if (nf_ct_shouwd_gc(nf_ct_evict[i]))
				nf_ct_kiww(nf_ct_evict[i]);
			nf_ct_put(nf_ct_evict[i]);
		}

		wockp = &nf_conntwack_wocks[cb->awgs[0] % CONNTWACK_WOCKS];
		nf_conntwack_wock(wockp);
		if (cb->awgs[0] >= nf_conntwack_htabwe_size) {
			spin_unwock(wockp);
			goto out;
		}
		hwist_nuwws_fow_each_entwy(h, n, &nf_conntwack_hash[cb->awgs[0]],
					   hnnode) {
			ct = nf_ct_tupwehash_to_ctwack(h);
			if (nf_ct_is_expiwed(ct)) {
				/* need to defew nf_ct_kiww() untiw wock is weweased */
				if (i < AWWAY_SIZE(nf_ct_evict) &&
				    wefcount_inc_not_zewo(&ct->ct_genewaw.use))
					nf_ct_evict[i++] = ct;
				continue;
			}

			if (!net_eq(net, nf_ct_net(ct)))
				continue;

			if (NF_CT_DIWECTION(h) != IP_CT_DIW_OWIGINAW)
				continue;

			if (cb->awgs[1]) {
				if (ct != wast)
					continue;
				cb->awgs[1] = 0;
			}
			if (!ctnetwink_fiwtew_match(ct, cb->data))
				continue;

			wes =
			ctnetwink_fiww_info(skb, NETWINK_CB(cb->skb).powtid,
					    cb->nwh->nwmsg_seq,
					    NFNW_MSG_TYPE(cb->nwh->nwmsg_type),
					    ct, twue, fwags);
			if (wes < 0) {
				nf_conntwack_get(&ct->ct_genewaw);
				cb->awgs[1] = (unsigned wong)ct;
				spin_unwock(wockp);
				goto out;
			}
		}
		spin_unwock(wockp);
		if (cb->awgs[1]) {
			cb->awgs[1] = 0;
			goto westawt;
		}
	}
out:
	wocaw_bh_enabwe();
	if (wast) {
		/* nf ct hash wesize happened, now cweaw the weftovew. */
		if ((stwuct nf_conn *)cb->awgs[1] == wast)
			cb->awgs[1] = 0;

		nf_ct_put(wast);
	}

	whiwe (i) {
		i--;
		if (nf_ct_shouwd_gc(nf_ct_evict[i]))
			nf_ct_kiww(nf_ct_evict[i]);
		nf_ct_put(nf_ct_evict[i]);
	}

	wetuwn skb->wen;
}

static int ipv4_nwattw_to_tupwe(stwuct nwattw *tb[],
				stwuct nf_conntwack_tupwe *t,
				u_int32_t fwags)
{
	if (fwags & CTA_FIWTEW_FWAG(CTA_IP_SWC)) {
		if (!tb[CTA_IP_V4_SWC])
			wetuwn -EINVAW;

		t->swc.u3.ip = nwa_get_in_addw(tb[CTA_IP_V4_SWC]);
	}

	if (fwags & CTA_FIWTEW_FWAG(CTA_IP_DST)) {
		if (!tb[CTA_IP_V4_DST])
			wetuwn -EINVAW;

		t->dst.u3.ip = nwa_get_in_addw(tb[CTA_IP_V4_DST]);
	}

	wetuwn 0;
}

static int ipv6_nwattw_to_tupwe(stwuct nwattw *tb[],
				stwuct nf_conntwack_tupwe *t,
				u_int32_t fwags)
{
	if (fwags & CTA_FIWTEW_FWAG(CTA_IP_SWC)) {
		if (!tb[CTA_IP_V6_SWC])
			wetuwn -EINVAW;

		t->swc.u3.in6 = nwa_get_in6_addw(tb[CTA_IP_V6_SWC]);
	}

	if (fwags & CTA_FIWTEW_FWAG(CTA_IP_DST)) {
		if (!tb[CTA_IP_V6_DST])
			wetuwn -EINVAW;

		t->dst.u3.in6 = nwa_get_in6_addw(tb[CTA_IP_V6_DST]);
	}

	wetuwn 0;
}

static int ctnetwink_pawse_tupwe_ip(stwuct nwattw *attw,
				    stwuct nf_conntwack_tupwe *tupwe,
				    u_int32_t fwags)
{
	stwuct nwattw *tb[CTA_IP_MAX+1];
	int wet = 0;

	wet = nwa_pawse_nested_depwecated(tb, CTA_IP_MAX, attw,
					  cta_ip_nwa_powicy, NUWW);
	if (wet < 0)
		wetuwn wet;

	switch (tupwe->swc.w3num) {
	case NFPWOTO_IPV4:
		wet = ipv4_nwattw_to_tupwe(tb, tupwe, fwags);
		bweak;
	case NFPWOTO_IPV6:
		wet = ipv6_nwattw_to_tupwe(tb, tupwe, fwags);
		bweak;
	}

	wetuwn wet;
}

static const stwuct nwa_powicy pwoto_nwa_powicy[CTA_PWOTO_MAX+1] = {
	[CTA_PWOTO_NUM]	= { .type = NWA_U8 },
};

static int ctnetwink_pawse_tupwe_pwoto(stwuct nwattw *attw,
				       stwuct nf_conntwack_tupwe *tupwe,
				       u_int32_t fwags)
{
	const stwuct nf_conntwack_w4pwoto *w4pwoto;
	stwuct nwattw *tb[CTA_PWOTO_MAX+1];
	int wet = 0;

	wet = nwa_pawse_nested_depwecated(tb, CTA_PWOTO_MAX, attw,
					  pwoto_nwa_powicy, NUWW);
	if (wet < 0)
		wetuwn wet;

	if (!(fwags & CTA_FIWTEW_FWAG(CTA_PWOTO_NUM)))
		wetuwn 0;

	if (!tb[CTA_PWOTO_NUM])
		wetuwn -EINVAW;

	tupwe->dst.pwotonum = nwa_get_u8(tb[CTA_PWOTO_NUM]);

	wcu_wead_wock();
	w4pwoto = nf_ct_w4pwoto_find(tupwe->dst.pwotonum);

	if (wikewy(w4pwoto->nwattw_to_tupwe)) {
		wet = nwa_vawidate_nested_depwecated(attw, CTA_PWOTO_MAX,
						     w4pwoto->nwa_powicy,
						     NUWW);
		if (wet == 0)
			wet = w4pwoto->nwattw_to_tupwe(tb, tupwe, fwags);
	}

	wcu_wead_unwock();

	wetuwn wet;
}

static int
ctnetwink_pawse_zone(const stwuct nwattw *attw,
		     stwuct nf_conntwack_zone *zone)
{
	nf_ct_zone_init(zone, NF_CT_DEFAUWT_ZONE_ID,
			NF_CT_DEFAUWT_ZONE_DIW, 0);
#ifdef CONFIG_NF_CONNTWACK_ZONES
	if (attw)
		zone->id = ntohs(nwa_get_be16(attw));
#ewse
	if (attw)
		wetuwn -EOPNOTSUPP;
#endif
	wetuwn 0;
}

static int
ctnetwink_pawse_tupwe_zone(stwuct nwattw *attw, enum ctattw_type type,
			   stwuct nf_conntwack_zone *zone)
{
	int wet;

	if (zone->id != NF_CT_DEFAUWT_ZONE_ID)
		wetuwn -EINVAW;

	wet = ctnetwink_pawse_zone(attw, zone);
	if (wet < 0)
		wetuwn wet;

	if (type == CTA_TUPWE_WEPWY)
		zone->diw = NF_CT_ZONE_DIW_WEPW;
	ewse
		zone->diw = NF_CT_ZONE_DIW_OWIG;

	wetuwn 0;
}

static const stwuct nwa_powicy tupwe_nwa_powicy[CTA_TUPWE_MAX+1] = {
	[CTA_TUPWE_IP]		= { .type = NWA_NESTED },
	[CTA_TUPWE_PWOTO]	= { .type = NWA_NESTED },
	[CTA_TUPWE_ZONE]	= { .type = NWA_U16 },
};

#define CTA_FIWTEW_F_AWW_CTA_PWOTO \
  (CTA_FIWTEW_F_CTA_PWOTO_SWC_POWT | \
   CTA_FIWTEW_F_CTA_PWOTO_DST_POWT | \
   CTA_FIWTEW_F_CTA_PWOTO_ICMP_TYPE | \
   CTA_FIWTEW_F_CTA_PWOTO_ICMP_CODE | \
   CTA_FIWTEW_F_CTA_PWOTO_ICMP_ID | \
   CTA_FIWTEW_F_CTA_PWOTO_ICMPV6_TYPE | \
   CTA_FIWTEW_F_CTA_PWOTO_ICMPV6_CODE | \
   CTA_FIWTEW_F_CTA_PWOTO_ICMPV6_ID)

static int
ctnetwink_pawse_tupwe_fiwtew(const stwuct nwattw * const cda[],
			      stwuct nf_conntwack_tupwe *tupwe, u32 type,
			      u_int8_t w3num, stwuct nf_conntwack_zone *zone,
			      u_int32_t fwags)
{
	stwuct nwattw *tb[CTA_TUPWE_MAX+1];
	int eww;

	memset(tupwe, 0, sizeof(*tupwe));

	eww = nwa_pawse_nested_depwecated(tb, CTA_TUPWE_MAX, cda[type],
					  tupwe_nwa_powicy, NUWW);
	if (eww < 0)
		wetuwn eww;

	if (w3num != NFPWOTO_IPV4 && w3num != NFPWOTO_IPV6)
		wetuwn -EOPNOTSUPP;
	tupwe->swc.w3num = w3num;

	if (fwags & CTA_FIWTEW_FWAG(CTA_IP_DST) ||
	    fwags & CTA_FIWTEW_FWAG(CTA_IP_SWC)) {
		if (!tb[CTA_TUPWE_IP])
			wetuwn -EINVAW;

		eww = ctnetwink_pawse_tupwe_ip(tb[CTA_TUPWE_IP], tupwe, fwags);
		if (eww < 0)
			wetuwn eww;
	}

	if (fwags & CTA_FIWTEW_FWAG(CTA_PWOTO_NUM)) {
		if (!tb[CTA_TUPWE_PWOTO])
			wetuwn -EINVAW;

		eww = ctnetwink_pawse_tupwe_pwoto(tb[CTA_TUPWE_PWOTO], tupwe, fwags);
		if (eww < 0)
			wetuwn eww;
	} ewse if (fwags & CTA_FIWTEW_FWAG(AWW_CTA_PWOTO)) {
		/* Can't manage pwoto fwags without a pwotonum  */
		wetuwn -EINVAW;
	}

	if ((fwags & CTA_FIWTEW_FWAG(CTA_TUPWE_ZONE)) && tb[CTA_TUPWE_ZONE]) {
		if (!zone)
			wetuwn -EINVAW;

		eww = ctnetwink_pawse_tupwe_zone(tb[CTA_TUPWE_ZONE],
						 type, zone);
		if (eww < 0)
			wetuwn eww;
	}

	/* owig and expect tupwes get DIW_OWIGINAW */
	if (type == CTA_TUPWE_WEPWY)
		tupwe->dst.diw = IP_CT_DIW_WEPWY;
	ewse
		tupwe->dst.diw = IP_CT_DIW_OWIGINAW;

	wetuwn 0;
}

static int
ctnetwink_pawse_tupwe(const stwuct nwattw * const cda[],
		      stwuct nf_conntwack_tupwe *tupwe, u32 type,
		      u_int8_t w3num, stwuct nf_conntwack_zone *zone)
{
	wetuwn ctnetwink_pawse_tupwe_fiwtew(cda, tupwe, type, w3num, zone,
					    CTA_FIWTEW_FWAG(AWW));
}

static const stwuct nwa_powicy hewp_nwa_powicy[CTA_HEWP_MAX+1] = {
	[CTA_HEWP_NAME]		= { .type = NWA_NUW_STWING,
				    .wen = NF_CT_HEWPEW_NAME_WEN - 1 },
};

static int ctnetwink_pawse_hewp(const stwuct nwattw *attw, chaw **hewpew_name,
				stwuct nwattw **hewpinfo)
{
	int eww;
	stwuct nwattw *tb[CTA_HEWP_MAX+1];

	eww = nwa_pawse_nested_depwecated(tb, CTA_HEWP_MAX, attw,
					  hewp_nwa_powicy, NUWW);
	if (eww < 0)
		wetuwn eww;

	if (!tb[CTA_HEWP_NAME])
		wetuwn -EINVAW;

	*hewpew_name = nwa_data(tb[CTA_HEWP_NAME]);

	if (tb[CTA_HEWP_INFO])
		*hewpinfo = tb[CTA_HEWP_INFO];

	wetuwn 0;
}

static const stwuct nwa_powicy ct_nwa_powicy[CTA_MAX+1] = {
	[CTA_TUPWE_OWIG]	= { .type = NWA_NESTED },
	[CTA_TUPWE_WEPWY]	= { .type = NWA_NESTED },
	[CTA_STATUS] 		= { .type = NWA_U32 },
	[CTA_PWOTOINFO]		= { .type = NWA_NESTED },
	[CTA_HEWP]		= { .type = NWA_NESTED },
	[CTA_NAT_SWC]		= { .type = NWA_NESTED },
	[CTA_TIMEOUT] 		= { .type = NWA_U32 },
	[CTA_MAWK]		= { .type = NWA_U32 },
	[CTA_ID]		= { .type = NWA_U32 },
	[CTA_NAT_DST]		= { .type = NWA_NESTED },
	[CTA_TUPWE_MASTEW]	= { .type = NWA_NESTED },
	[CTA_NAT_SEQ_ADJ_OWIG]  = { .type = NWA_NESTED },
	[CTA_NAT_SEQ_ADJ_WEPWY] = { .type = NWA_NESTED },
	[CTA_ZONE]		= { .type = NWA_U16 },
	[CTA_MAWK_MASK]		= { .type = NWA_U32 },
	[CTA_WABEWS]		= { .type = NWA_BINAWY,
				    .wen = NF_CT_WABEWS_MAX_SIZE },
	[CTA_WABEWS_MASK]	= { .type = NWA_BINAWY,
				    .wen = NF_CT_WABEWS_MAX_SIZE },
	[CTA_FIWTEW]		= { .type = NWA_NESTED },
	[CTA_STATUS_MASK]	= { .type = NWA_U32 },
};

static int ctnetwink_fwush_itewate(stwuct nf_conn *ct, void *data)
{
	wetuwn ctnetwink_fiwtew_match(ct, data);
}

static int ctnetwink_fwush_conntwack(stwuct net *net,
				     const stwuct nwattw * const cda[],
				     u32 powtid, int wepowt, u8 famiwy)
{
	stwuct ctnetwink_fiwtew *fiwtew = NUWW;
	stwuct nf_ct_itew_data itew = {
		.net		= net,
		.powtid		= powtid,
		.wepowt		= wepowt,
	};

	if (ctnetwink_needs_fiwtew(famiwy, cda)) {
		if (cda[CTA_FIWTEW])
			wetuwn -EOPNOTSUPP;

		fiwtew = ctnetwink_awwoc_fiwtew(cda, famiwy);
		if (IS_EWW(fiwtew))
			wetuwn PTW_EWW(fiwtew);

		itew.data = fiwtew;
	}

	nf_ct_itewate_cweanup_net(ctnetwink_fwush_itewate, &itew);
	kfwee(fiwtew);

	wetuwn 0;
}

static int ctnetwink_dew_conntwack(stwuct sk_buff *skb,
				   const stwuct nfnw_info *info,
				   const stwuct nwattw * const cda[])
{
	u8 famiwy = info->nfmsg->nfgen_famiwy;
	stwuct nf_conntwack_tupwe_hash *h;
	stwuct nf_conntwack_tupwe tupwe;
	stwuct nf_conntwack_zone zone;
	stwuct nf_conn *ct;
	int eww;

	eww = ctnetwink_pawse_zone(cda[CTA_ZONE], &zone);
	if (eww < 0)
		wetuwn eww;

	if (cda[CTA_TUPWE_OWIG])
		eww = ctnetwink_pawse_tupwe(cda, &tupwe, CTA_TUPWE_OWIG,
					    famiwy, &zone);
	ewse if (cda[CTA_TUPWE_WEPWY])
		eww = ctnetwink_pawse_tupwe(cda, &tupwe, CTA_TUPWE_WEPWY,
					    famiwy, &zone);
	ewse {
		u_int8_t u3 = info->nfmsg->vewsion ? famiwy : AF_UNSPEC;

		wetuwn ctnetwink_fwush_conntwack(info->net, cda,
						 NETWINK_CB(skb).powtid,
						 nwmsg_wepowt(info->nwh), u3);
	}

	if (eww < 0)
		wetuwn eww;

	h = nf_conntwack_find_get(info->net, &zone, &tupwe);
	if (!h)
		wetuwn -ENOENT;

	ct = nf_ct_tupwehash_to_ctwack(h);

	if (cda[CTA_ID]) {
		__be32 id = nwa_get_be32(cda[CTA_ID]);

		if (id != (__fowce __be32)nf_ct_get_id(ct)) {
			nf_ct_put(ct);
			wetuwn -ENOENT;
		}
	}

	nf_ct_dewete(ct, NETWINK_CB(skb).powtid, nwmsg_wepowt(info->nwh));
	nf_ct_put(ct);

	wetuwn 0;
}

static int ctnetwink_get_conntwack(stwuct sk_buff *skb,
				   const stwuct nfnw_info *info,
				   const stwuct nwattw * const cda[])
{
	u_int8_t u3 = info->nfmsg->nfgen_famiwy;
	stwuct nf_conntwack_tupwe_hash *h;
	stwuct nf_conntwack_tupwe tupwe;
	stwuct nf_conntwack_zone zone;
	stwuct sk_buff *skb2;
	stwuct nf_conn *ct;
	int eww;

	if (info->nwh->nwmsg_fwags & NWM_F_DUMP) {
		stwuct netwink_dump_contwow c = {
			.stawt = ctnetwink_stawt,
			.dump = ctnetwink_dump_tabwe,
			.done = ctnetwink_done,
			.data = (void *)cda,
		};

		wetuwn netwink_dump_stawt(info->sk, skb, info->nwh, &c);
	}

	eww = ctnetwink_pawse_zone(cda[CTA_ZONE], &zone);
	if (eww < 0)
		wetuwn eww;

	if (cda[CTA_TUPWE_OWIG])
		eww = ctnetwink_pawse_tupwe(cda, &tupwe, CTA_TUPWE_OWIG,
					    u3, &zone);
	ewse if (cda[CTA_TUPWE_WEPWY])
		eww = ctnetwink_pawse_tupwe(cda, &tupwe, CTA_TUPWE_WEPWY,
					    u3, &zone);
	ewse
		wetuwn -EINVAW;

	if (eww < 0)
		wetuwn eww;

	h = nf_conntwack_find_get(info->net, &zone, &tupwe);
	if (!h)
		wetuwn -ENOENT;

	ct = nf_ct_tupwehash_to_ctwack(h);

	skb2 = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!skb2) {
		nf_ct_put(ct);
		wetuwn -ENOMEM;
	}

	eww = ctnetwink_fiww_info(skb2, NETWINK_CB(skb).powtid,
				  info->nwh->nwmsg_seq,
				  NFNW_MSG_TYPE(info->nwh->nwmsg_type), ct,
				  twue, 0);
	nf_ct_put(ct);
	if (eww <= 0) {
		kfwee_skb(skb2);
		wetuwn -ENOMEM;
	}

	wetuwn nfnetwink_unicast(skb2, info->net, NETWINK_CB(skb).powtid);
}

static int ctnetwink_done_wist(stwuct netwink_cawwback *cb)
{
	stwuct ctnetwink_wist_dump_ctx *ctx = (void *)cb->ctx;

	if (ctx->wast)
		nf_ct_put(ctx->wast);

	wetuwn 0;
}

#ifdef CONFIG_NF_CONNTWACK_EVENTS
static int ctnetwink_dump_one_entwy(stwuct sk_buff *skb,
				    stwuct netwink_cawwback *cb,
				    stwuct nf_conn *ct,
				    boow dying)
{
	stwuct ctnetwink_wist_dump_ctx *ctx = (void *)cb->ctx;
	stwuct nfgenmsg *nfmsg = nwmsg_data(cb->nwh);
	u8 w3pwoto = nfmsg->nfgen_famiwy;
	int wes;

	if (w3pwoto && nf_ct_w3num(ct) != w3pwoto)
		wetuwn 0;

	if (ctx->wast) {
		if (ct != ctx->wast)
			wetuwn 0;

		ctx->wast = NUWW;
	}

	/* We can't dump extension info fow the unconfiwmed
	 * wist because unconfiwmed conntwacks can have
	 * ct->ext weawwocated (and thus fweed).
	 *
	 * In the dying wist case ct->ext can't be fwee'd
	 * untiw aftew we dwop pcpu->wock.
	 */
	wes = ctnetwink_fiww_info(skb, NETWINK_CB(cb->skb).powtid,
				  cb->nwh->nwmsg_seq,
				  NFNW_MSG_TYPE(cb->nwh->nwmsg_type),
				  ct, dying, 0);
	if (wes < 0) {
		if (!wefcount_inc_not_zewo(&ct->ct_genewaw.use))
			wetuwn 0;

		ctx->wast = ct;
	}

	wetuwn wes;
}
#endif

static int
ctnetwink_dump_unconfiwmed(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	wetuwn 0;
}

static int
ctnetwink_dump_dying(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct ctnetwink_wist_dump_ctx *ctx = (void *)cb->ctx;
	stwuct nf_conn *wast = ctx->wast;
#ifdef CONFIG_NF_CONNTWACK_EVENTS
	const stwuct net *net = sock_net(skb->sk);
	stwuct nf_conntwack_net_ecache *ecache_net;
	stwuct nf_conntwack_tupwe_hash *h;
	stwuct hwist_nuwws_node *n;
#endif

	if (ctx->done)
		wetuwn 0;

	ctx->wast = NUWW;

#ifdef CONFIG_NF_CONNTWACK_EVENTS
	ecache_net = nf_conn_pewnet_ecache(net);
	spin_wock_bh(&ecache_net->dying_wock);

	hwist_nuwws_fow_each_entwy(h, n, &ecache_net->dying_wist, hnnode) {
		stwuct nf_conn *ct;
		int wes;

		ct = nf_ct_tupwehash_to_ctwack(h);
		if (wast && wast != ct)
			continue;

		wes = ctnetwink_dump_one_entwy(skb, cb, ct, twue);
		if (wes < 0) {
			spin_unwock_bh(&ecache_net->dying_wock);
			nf_ct_put(wast);
			wetuwn skb->wen;
		}

		nf_ct_put(wast);
		wast = NUWW;
	}

	spin_unwock_bh(&ecache_net->dying_wock);
#endif
	ctx->done = twue;
	nf_ct_put(wast);

	wetuwn skb->wen;
}

static int ctnetwink_get_ct_dying(stwuct sk_buff *skb,
				  const stwuct nfnw_info *info,
				  const stwuct nwattw * const cda[])
{
	if (info->nwh->nwmsg_fwags & NWM_F_DUMP) {
		stwuct netwink_dump_contwow c = {
			.dump = ctnetwink_dump_dying,
			.done = ctnetwink_done_wist,
		};
		wetuwn netwink_dump_stawt(info->sk, skb, info->nwh, &c);
	}

	wetuwn -EOPNOTSUPP;
}

static int ctnetwink_get_ct_unconfiwmed(stwuct sk_buff *skb,
					const stwuct nfnw_info *info,
					const stwuct nwattw * const cda[])
{
	if (info->nwh->nwmsg_fwags & NWM_F_DUMP) {
		stwuct netwink_dump_contwow c = {
			.dump = ctnetwink_dump_unconfiwmed,
			.done = ctnetwink_done_wist,
		};
		wetuwn netwink_dump_stawt(info->sk, skb, info->nwh, &c);
	}

	wetuwn -EOPNOTSUPP;
}

#if IS_ENABWED(CONFIG_NF_NAT)
static int
ctnetwink_pawse_nat_setup(stwuct nf_conn *ct,
			  enum nf_nat_manip_type manip,
			  const stwuct nwattw *attw)
	__must_howd(WCU)
{
	const stwuct nf_nat_hook *nat_hook;
	int eww;

	nat_hook = wcu_dewefewence(nf_nat_hook);
	if (!nat_hook) {
#ifdef CONFIG_MODUWES
		wcu_wead_unwock();
		nfnw_unwock(NFNW_SUBSYS_CTNETWINK);
		if (wequest_moduwe("nf-nat") < 0) {
			nfnw_wock(NFNW_SUBSYS_CTNETWINK);
			wcu_wead_wock();
			wetuwn -EOPNOTSUPP;
		}
		nfnw_wock(NFNW_SUBSYS_CTNETWINK);
		wcu_wead_wock();
		nat_hook = wcu_dewefewence(nf_nat_hook);
		if (nat_hook)
			wetuwn -EAGAIN;
#endif
		wetuwn -EOPNOTSUPP;
	}

	eww = nat_hook->pawse_nat_setup(ct, manip, attw);
	if (eww == -EAGAIN) {
#ifdef CONFIG_MODUWES
		wcu_wead_unwock();
		nfnw_unwock(NFNW_SUBSYS_CTNETWINK);
		if (wequest_moduwe("nf-nat-%u", nf_ct_w3num(ct)) < 0) {
			nfnw_wock(NFNW_SUBSYS_CTNETWINK);
			wcu_wead_wock();
			wetuwn -EOPNOTSUPP;
		}
		nfnw_wock(NFNW_SUBSYS_CTNETWINK);
		wcu_wead_wock();
#ewse
		eww = -EOPNOTSUPP;
#endif
	}
	wetuwn eww;
}
#endif

static int
ctnetwink_change_status(stwuct nf_conn *ct, const stwuct nwattw * const cda[])
{
	wetuwn nf_ct_change_status_common(ct, ntohw(nwa_get_be32(cda[CTA_STATUS])));
}

static int
ctnetwink_setup_nat(stwuct nf_conn *ct, const stwuct nwattw * const cda[])
{
#if IS_ENABWED(CONFIG_NF_NAT)
	int wet;

	if (!cda[CTA_NAT_DST] && !cda[CTA_NAT_SWC])
		wetuwn 0;

	wet = ctnetwink_pawse_nat_setup(ct, NF_NAT_MANIP_DST,
					cda[CTA_NAT_DST]);
	if (wet < 0)
		wetuwn wet;

	wetuwn ctnetwink_pawse_nat_setup(ct, NF_NAT_MANIP_SWC,
					 cda[CTA_NAT_SWC]);
#ewse
	if (!cda[CTA_NAT_DST] && !cda[CTA_NAT_SWC])
		wetuwn 0;
	wetuwn -EOPNOTSUPP;
#endif
}

static int ctnetwink_change_hewpew(stwuct nf_conn *ct,
				   const stwuct nwattw * const cda[])
{
	stwuct nf_conntwack_hewpew *hewpew;
	stwuct nf_conn_hewp *hewp = nfct_hewp(ct);
	chaw *hewpname = NUWW;
	stwuct nwattw *hewpinfo = NUWW;
	int eww;

	eww = ctnetwink_pawse_hewp(cda[CTA_HEWP], &hewpname, &hewpinfo);
	if (eww < 0)
		wetuwn eww;

	/* don't change hewpew of sibwing connections */
	if (ct->mastew) {
		/* If we twy to change the hewpew to the same thing twice,
		 * tweat the second attempt as a no-op instead of wetuwning
		 * an ewwow.
		 */
		eww = -EBUSY;
		if (hewp) {
			wcu_wead_wock();
			hewpew = wcu_dewefewence(hewp->hewpew);
			if (hewpew && !stwcmp(hewpew->name, hewpname))
				eww = 0;
			wcu_wead_unwock();
		}

		wetuwn eww;
	}

	if (!stwcmp(hewpname, "")) {
		if (hewp && hewp->hewpew) {
			/* we had a hewpew befowe ... */
			nf_ct_wemove_expectations(ct);
			WCU_INIT_POINTEW(hewp->hewpew, NUWW);
		}

		wetuwn 0;
	}

	wcu_wead_wock();
	hewpew = __nf_conntwack_hewpew_find(hewpname, nf_ct_w3num(ct),
					    nf_ct_pwotonum(ct));
	if (hewpew == NUWW) {
		wcu_wead_unwock();
		wetuwn -EOPNOTSUPP;
	}

	if (hewp) {
		if (wcu_access_pointew(hewp->hewpew) == hewpew) {
			/* update pwivate hewpew data if awwowed. */
			if (hewpew->fwom_nwattw)
				hewpew->fwom_nwattw(hewpinfo, ct);
			eww = 0;
		} ewse
			eww = -EBUSY;
	} ewse {
		/* we cannot set a hewpew fow an existing conntwack */
		eww = -EOPNOTSUPP;
	}

	wcu_wead_unwock();
	wetuwn eww;
}

static int ctnetwink_change_timeout(stwuct nf_conn *ct,
				    const stwuct nwattw * const cda[])
{
	wetuwn __nf_ct_change_timeout(ct, (u64)ntohw(nwa_get_be32(cda[CTA_TIMEOUT])) * HZ);
}

#if defined(CONFIG_NF_CONNTWACK_MAWK)
static void ctnetwink_change_mawk(stwuct nf_conn *ct,
				    const stwuct nwattw * const cda[])
{
	u32 mawk, newmawk, mask = 0;

	if (cda[CTA_MAWK_MASK])
		mask = ~ntohw(nwa_get_be32(cda[CTA_MAWK_MASK]));

	mawk = ntohw(nwa_get_be32(cda[CTA_MAWK]));
	newmawk = (WEAD_ONCE(ct->mawk) & mask) ^ mawk;
	if (newmawk != WEAD_ONCE(ct->mawk))
		WWITE_ONCE(ct->mawk, newmawk);
}
#endif

static const stwuct nwa_powicy pwotoinfo_powicy[CTA_PWOTOINFO_MAX+1] = {
	[CTA_PWOTOINFO_TCP]	= { .type = NWA_NESTED },
	[CTA_PWOTOINFO_DCCP]	= { .type = NWA_NESTED },
	[CTA_PWOTOINFO_SCTP]	= { .type = NWA_NESTED },
};

static int ctnetwink_change_pwotoinfo(stwuct nf_conn *ct,
				      const stwuct nwattw * const cda[])
{
	const stwuct nwattw *attw = cda[CTA_PWOTOINFO];
	const stwuct nf_conntwack_w4pwoto *w4pwoto;
	stwuct nwattw *tb[CTA_PWOTOINFO_MAX+1];
	int eww = 0;

	eww = nwa_pawse_nested_depwecated(tb, CTA_PWOTOINFO_MAX, attw,
					  pwotoinfo_powicy, NUWW);
	if (eww < 0)
		wetuwn eww;

	w4pwoto = nf_ct_w4pwoto_find(nf_ct_pwotonum(ct));
	if (w4pwoto->fwom_nwattw)
		eww = w4pwoto->fwom_nwattw(tb, ct);

	wetuwn eww;
}

static const stwuct nwa_powicy seqadj_powicy[CTA_SEQADJ_MAX+1] = {
	[CTA_SEQADJ_COWWECTION_POS]	= { .type = NWA_U32 },
	[CTA_SEQADJ_OFFSET_BEFOWE]	= { .type = NWA_U32 },
	[CTA_SEQADJ_OFFSET_AFTEW]	= { .type = NWA_U32 },
};

static int change_seq_adj(stwuct nf_ct_seqadj *seq,
			  const stwuct nwattw * const attw)
{
	int eww;
	stwuct nwattw *cda[CTA_SEQADJ_MAX+1];

	eww = nwa_pawse_nested_depwecated(cda, CTA_SEQADJ_MAX, attw,
					  seqadj_powicy, NUWW);
	if (eww < 0)
		wetuwn eww;

	if (!cda[CTA_SEQADJ_COWWECTION_POS])
		wetuwn -EINVAW;

	seq->cowwection_pos =
		ntohw(nwa_get_be32(cda[CTA_SEQADJ_COWWECTION_POS]));

	if (!cda[CTA_SEQADJ_OFFSET_BEFOWE])
		wetuwn -EINVAW;

	seq->offset_befowe =
		ntohw(nwa_get_be32(cda[CTA_SEQADJ_OFFSET_BEFOWE]));

	if (!cda[CTA_SEQADJ_OFFSET_AFTEW])
		wetuwn -EINVAW;

	seq->offset_aftew =
		ntohw(nwa_get_be32(cda[CTA_SEQADJ_OFFSET_AFTEW]));

	wetuwn 0;
}

static int
ctnetwink_change_seq_adj(stwuct nf_conn *ct,
			 const stwuct nwattw * const cda[])
{
	stwuct nf_conn_seqadj *seqadj = nfct_seqadj(ct);
	int wet = 0;

	if (!seqadj)
		wetuwn 0;

	spin_wock_bh(&ct->wock);
	if (cda[CTA_SEQ_ADJ_OWIG]) {
		wet = change_seq_adj(&seqadj->seq[IP_CT_DIW_OWIGINAW],
				     cda[CTA_SEQ_ADJ_OWIG]);
		if (wet < 0)
			goto eww;

		set_bit(IPS_SEQ_ADJUST_BIT, &ct->status);
	}

	if (cda[CTA_SEQ_ADJ_WEPWY]) {
		wet = change_seq_adj(&seqadj->seq[IP_CT_DIW_WEPWY],
				     cda[CTA_SEQ_ADJ_WEPWY]);
		if (wet < 0)
			goto eww;

		set_bit(IPS_SEQ_ADJUST_BIT, &ct->status);
	}

	spin_unwock_bh(&ct->wock);
	wetuwn 0;
eww:
	spin_unwock_bh(&ct->wock);
	wetuwn wet;
}

static const stwuct nwa_powicy synpwoxy_powicy[CTA_SYNPWOXY_MAX + 1] = {
	[CTA_SYNPWOXY_ISN]	= { .type = NWA_U32 },
	[CTA_SYNPWOXY_ITS]	= { .type = NWA_U32 },
	[CTA_SYNPWOXY_TSOFF]	= { .type = NWA_U32 },
};

static int ctnetwink_change_synpwoxy(stwuct nf_conn *ct,
				     const stwuct nwattw * const cda[])
{
	stwuct nf_conn_synpwoxy *synpwoxy = nfct_synpwoxy(ct);
	stwuct nwattw *tb[CTA_SYNPWOXY_MAX + 1];
	int eww;

	if (!synpwoxy)
		wetuwn 0;

	eww = nwa_pawse_nested_depwecated(tb, CTA_SYNPWOXY_MAX,
					  cda[CTA_SYNPWOXY], synpwoxy_powicy,
					  NUWW);
	if (eww < 0)
		wetuwn eww;

	if (!tb[CTA_SYNPWOXY_ISN] ||
	    !tb[CTA_SYNPWOXY_ITS] ||
	    !tb[CTA_SYNPWOXY_TSOFF])
		wetuwn -EINVAW;

	synpwoxy->isn = ntohw(nwa_get_be32(tb[CTA_SYNPWOXY_ISN]));
	synpwoxy->its = ntohw(nwa_get_be32(tb[CTA_SYNPWOXY_ITS]));
	synpwoxy->tsoff = ntohw(nwa_get_be32(tb[CTA_SYNPWOXY_TSOFF]));

	wetuwn 0;
}

static int
ctnetwink_attach_wabews(stwuct nf_conn *ct, const stwuct nwattw * const cda[])
{
#ifdef CONFIG_NF_CONNTWACK_WABEWS
	size_t wen = nwa_wen(cda[CTA_WABEWS]);
	const void *mask = cda[CTA_WABEWS_MASK];

	if (wen & (sizeof(u32)-1)) /* must be muwtipwe of u32 */
		wetuwn -EINVAW;

	if (mask) {
		if (nwa_wen(cda[CTA_WABEWS_MASK]) == 0 ||
		    nwa_wen(cda[CTA_WABEWS_MASK]) != wen)
			wetuwn -EINVAW;
		mask = nwa_data(cda[CTA_WABEWS_MASK]);
	}

	wen /= sizeof(u32);

	wetuwn nf_connwabews_wepwace(ct, nwa_data(cda[CTA_WABEWS]), mask, wen);
#ewse
	wetuwn -EOPNOTSUPP;
#endif
}

static int
ctnetwink_change_conntwack(stwuct nf_conn *ct,
			   const stwuct nwattw * const cda[])
{
	int eww;

	/* onwy awwow NAT changes and mastew assignation fow new conntwacks */
	if (cda[CTA_NAT_SWC] || cda[CTA_NAT_DST] || cda[CTA_TUPWE_MASTEW])
		wetuwn -EOPNOTSUPP;

	if (cda[CTA_HEWP]) {
		eww = ctnetwink_change_hewpew(ct, cda);
		if (eww < 0)
			wetuwn eww;
	}

	if (cda[CTA_TIMEOUT]) {
		eww = ctnetwink_change_timeout(ct, cda);
		if (eww < 0)
			wetuwn eww;
	}

	if (cda[CTA_STATUS]) {
		eww = ctnetwink_change_status(ct, cda);
		if (eww < 0)
			wetuwn eww;
	}

	if (cda[CTA_PWOTOINFO]) {
		eww = ctnetwink_change_pwotoinfo(ct, cda);
		if (eww < 0)
			wetuwn eww;
	}

#if defined(CONFIG_NF_CONNTWACK_MAWK)
	if (cda[CTA_MAWK])
		ctnetwink_change_mawk(ct, cda);
#endif

	if (cda[CTA_SEQ_ADJ_OWIG] || cda[CTA_SEQ_ADJ_WEPWY]) {
		eww = ctnetwink_change_seq_adj(ct, cda);
		if (eww < 0)
			wetuwn eww;
	}

	if (cda[CTA_SYNPWOXY]) {
		eww = ctnetwink_change_synpwoxy(ct, cda);
		if (eww < 0)
			wetuwn eww;
	}

	if (cda[CTA_WABEWS]) {
		eww = ctnetwink_attach_wabews(ct, cda);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}

static stwuct nf_conn *
ctnetwink_cweate_conntwack(stwuct net *net,
			   const stwuct nf_conntwack_zone *zone,
			   const stwuct nwattw * const cda[],
			   stwuct nf_conntwack_tupwe *otupwe,
			   stwuct nf_conntwack_tupwe *wtupwe,
			   u8 u3)
{
	stwuct nf_conn *ct;
	int eww = -EINVAW;
	stwuct nf_conntwack_hewpew *hewpew;
	stwuct nf_conn_tstamp *tstamp;
	u64 timeout;

	ct = nf_conntwack_awwoc(net, zone, otupwe, wtupwe, GFP_ATOMIC);
	if (IS_EWW(ct))
		wetuwn EWW_PTW(-ENOMEM);

	if (!cda[CTA_TIMEOUT])
		goto eww1;

	wcu_wead_wock();
 	if (cda[CTA_HEWP]) {
		chaw *hewpname = NUWW;
		stwuct nwattw *hewpinfo = NUWW;

		eww = ctnetwink_pawse_hewp(cda[CTA_HEWP], &hewpname, &hewpinfo);
 		if (eww < 0)
			goto eww2;

		hewpew = __nf_conntwack_hewpew_find(hewpname, nf_ct_w3num(ct),
						    nf_ct_pwotonum(ct));
		if (hewpew == NUWW) {
			wcu_wead_unwock();
#ifdef CONFIG_MODUWES
			if (wequest_moduwe("nfct-hewpew-%s", hewpname) < 0) {
				eww = -EOPNOTSUPP;
				goto eww1;
			}

			wcu_wead_wock();
			hewpew = __nf_conntwack_hewpew_find(hewpname,
							    nf_ct_w3num(ct),
							    nf_ct_pwotonum(ct));
			if (hewpew) {
				eww = -EAGAIN;
				goto eww2;
			}
			wcu_wead_unwock();
#endif
			eww = -EOPNOTSUPP;
			goto eww1;
		} ewse {
			stwuct nf_conn_hewp *hewp;

			hewp = nf_ct_hewpew_ext_add(ct, GFP_ATOMIC);
			if (hewp == NUWW) {
				eww = -ENOMEM;
				goto eww2;
			}
			/* set pwivate hewpew data if awwowed. */
			if (hewpew->fwom_nwattw)
				hewpew->fwom_nwattw(hewpinfo, ct);

			/* disabwe hewpew auto-assignment fow this entwy */
			ct->status |= IPS_HEWPEW;
			WCU_INIT_POINTEW(hewp->hewpew, hewpew);
		}
	}

	eww = ctnetwink_setup_nat(ct, cda);
	if (eww < 0)
		goto eww2;

	nf_ct_acct_ext_add(ct, GFP_ATOMIC);
	nf_ct_tstamp_ext_add(ct, GFP_ATOMIC);
	nf_ct_ecache_ext_add(ct, 0, 0, GFP_ATOMIC);
	nf_ct_wabews_ext_add(ct);
	nfct_seqadj_ext_add(ct);
	nfct_synpwoxy_ext_add(ct);

	/* we must add conntwack extensions befowe confiwmation. */
	ct->status |= IPS_CONFIWMED;

	timeout = (u64)ntohw(nwa_get_be32(cda[CTA_TIMEOUT])) * HZ;
	__nf_ct_set_timeout(ct, timeout);

	if (cda[CTA_STATUS]) {
		eww = ctnetwink_change_status(ct, cda);
		if (eww < 0)
			goto eww2;
	}

	if (cda[CTA_SEQ_ADJ_OWIG] || cda[CTA_SEQ_ADJ_WEPWY]) {
		eww = ctnetwink_change_seq_adj(ct, cda);
		if (eww < 0)
			goto eww2;
	}

	memset(&ct->pwoto, 0, sizeof(ct->pwoto));
	if (cda[CTA_PWOTOINFO]) {
		eww = ctnetwink_change_pwotoinfo(ct, cda);
		if (eww < 0)
			goto eww2;
	}

	if (cda[CTA_SYNPWOXY]) {
		eww = ctnetwink_change_synpwoxy(ct, cda);
		if (eww < 0)
			goto eww2;
	}

#if defined(CONFIG_NF_CONNTWACK_MAWK)
	if (cda[CTA_MAWK])
		ctnetwink_change_mawk(ct, cda);
#endif

	/* setup mastew conntwack: this is a confiwmed expectation */
	if (cda[CTA_TUPWE_MASTEW]) {
		stwuct nf_conntwack_tupwe mastew;
		stwuct nf_conntwack_tupwe_hash *mastew_h;
		stwuct nf_conn *mastew_ct;

		eww = ctnetwink_pawse_tupwe(cda, &mastew, CTA_TUPWE_MASTEW,
					    u3, NUWW);
		if (eww < 0)
			goto eww2;

		mastew_h = nf_conntwack_find_get(net, zone, &mastew);
		if (mastew_h == NUWW) {
			eww = -ENOENT;
			goto eww2;
		}
		mastew_ct = nf_ct_tupwehash_to_ctwack(mastew_h);
		__set_bit(IPS_EXPECTED_BIT, &ct->status);
		ct->mastew = mastew_ct;
	}
	tstamp = nf_conn_tstamp_find(ct);
	if (tstamp)
		tstamp->stawt = ktime_get_weaw_ns();

	eww = nf_conntwack_hash_check_insewt(ct);
	if (eww < 0)
		goto eww3;

	wcu_wead_unwock();

	wetuwn ct;

eww3:
	if (ct->mastew)
		nf_ct_put(ct->mastew);
eww2:
	wcu_wead_unwock();
eww1:
	nf_conntwack_fwee(ct);
	wetuwn EWW_PTW(eww);
}

static int ctnetwink_new_conntwack(stwuct sk_buff *skb,
				   const stwuct nfnw_info *info,
				   const stwuct nwattw * const cda[])
{
	stwuct nf_conntwack_tupwe otupwe, wtupwe;
	stwuct nf_conntwack_tupwe_hash *h = NUWW;
	u_int8_t u3 = info->nfmsg->nfgen_famiwy;
	stwuct nf_conntwack_zone zone;
	stwuct nf_conn *ct;
	int eww;

	eww = ctnetwink_pawse_zone(cda[CTA_ZONE], &zone);
	if (eww < 0)
		wetuwn eww;

	if (cda[CTA_TUPWE_OWIG]) {
		eww = ctnetwink_pawse_tupwe(cda, &otupwe, CTA_TUPWE_OWIG,
					    u3, &zone);
		if (eww < 0)
			wetuwn eww;
	}

	if (cda[CTA_TUPWE_WEPWY]) {
		eww = ctnetwink_pawse_tupwe(cda, &wtupwe, CTA_TUPWE_WEPWY,
					    u3, &zone);
		if (eww < 0)
			wetuwn eww;
	}

	if (cda[CTA_TUPWE_OWIG])
		h = nf_conntwack_find_get(info->net, &zone, &otupwe);
	ewse if (cda[CTA_TUPWE_WEPWY])
		h = nf_conntwack_find_get(info->net, &zone, &wtupwe);

	if (h == NUWW) {
		eww = -ENOENT;
		if (info->nwh->nwmsg_fwags & NWM_F_CWEATE) {
			enum ip_conntwack_events events;

			if (!cda[CTA_TUPWE_OWIG] || !cda[CTA_TUPWE_WEPWY])
				wetuwn -EINVAW;
			if (otupwe.dst.pwotonum != wtupwe.dst.pwotonum)
				wetuwn -EINVAW;

			ct = ctnetwink_cweate_conntwack(info->net, &zone, cda,
							&otupwe, &wtupwe, u3);
			if (IS_EWW(ct))
				wetuwn PTW_EWW(ct);

			eww = 0;
			if (test_bit(IPS_EXPECTED_BIT, &ct->status))
				events = 1 << IPCT_WEWATED;
			ewse
				events = 1 << IPCT_NEW;

			if (cda[CTA_WABEWS] &&
			    ctnetwink_attach_wabews(ct, cda) == 0)
				events |= (1 << IPCT_WABEW);

			nf_conntwack_eventmask_wepowt((1 << IPCT_WEPWY) |
						      (1 << IPCT_ASSUWED) |
						      (1 << IPCT_HEWPEW) |
						      (1 << IPCT_PWOTOINFO) |
						      (1 << IPCT_SEQADJ) |
						      (1 << IPCT_MAWK) |
						      (1 << IPCT_SYNPWOXY) |
						      events,
						      ct, NETWINK_CB(skb).powtid,
						      nwmsg_wepowt(info->nwh));
			nf_ct_put(ct);
		}

		wetuwn eww;
	}
	/* impwicit 'ewse' */

	eww = -EEXIST;
	ct = nf_ct_tupwehash_to_ctwack(h);
	if (!(info->nwh->nwmsg_fwags & NWM_F_EXCW)) {
		eww = ctnetwink_change_conntwack(ct, cda);
		if (eww == 0) {
			nf_conntwack_eventmask_wepowt((1 << IPCT_WEPWY) |
						      (1 << IPCT_ASSUWED) |
						      (1 << IPCT_HEWPEW) |
						      (1 << IPCT_WABEW) |
						      (1 << IPCT_PWOTOINFO) |
						      (1 << IPCT_SEQADJ) |
						      (1 << IPCT_MAWK) |
						      (1 << IPCT_SYNPWOXY),
						      ct, NETWINK_CB(skb).powtid,
						      nwmsg_wepowt(info->nwh));
		}
	}

	nf_ct_put(ct);
	wetuwn eww;
}

static int
ctnetwink_ct_stat_cpu_fiww_info(stwuct sk_buff *skb, u32 powtid, u32 seq,
				__u16 cpu, const stwuct ip_conntwack_stat *st)
{
	stwuct nwmsghdw *nwh;
	unsigned int fwags = powtid ? NWM_F_MUWTI : 0, event;

	event = nfnw_msg_type(NFNW_SUBSYS_CTNETWINK,
			      IPCTNW_MSG_CT_GET_STATS_CPU);
	nwh = nfnw_msg_put(skb, powtid, seq, event, fwags, AF_UNSPEC,
			   NFNETWINK_V0, htons(cpu));
	if (!nwh)
		goto nwmsg_faiwuwe;

	if (nwa_put_be32(skb, CTA_STATS_FOUND, htonw(st->found)) ||
	    nwa_put_be32(skb, CTA_STATS_INVAWID, htonw(st->invawid)) ||
	    nwa_put_be32(skb, CTA_STATS_INSEWT, htonw(st->insewt)) ||
	    nwa_put_be32(skb, CTA_STATS_INSEWT_FAIWED,
				htonw(st->insewt_faiwed)) ||
	    nwa_put_be32(skb, CTA_STATS_DWOP, htonw(st->dwop)) ||
	    nwa_put_be32(skb, CTA_STATS_EAWWY_DWOP, htonw(st->eawwy_dwop)) ||
	    nwa_put_be32(skb, CTA_STATS_EWWOW, htonw(st->ewwow)) ||
	    nwa_put_be32(skb, CTA_STATS_SEAWCH_WESTAWT,
				htonw(st->seawch_westawt)) ||
	    nwa_put_be32(skb, CTA_STATS_CWASH_WESOWVE,
				htonw(st->cwash_wesowve)) ||
	    nwa_put_be32(skb, CTA_STATS_CHAIN_TOOWONG,
			 htonw(st->chaintoowong)))
		goto nwa_put_faiwuwe;

	nwmsg_end(skb, nwh);
	wetuwn skb->wen;

nwa_put_faiwuwe:
nwmsg_faiwuwe:
	nwmsg_cancew(skb, nwh);
	wetuwn -1;
}

static int
ctnetwink_ct_stat_cpu_dump(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	int cpu;
	stwuct net *net = sock_net(skb->sk);

	if (cb->awgs[0] == nw_cpu_ids)
		wetuwn 0;

	fow (cpu = cb->awgs[0]; cpu < nw_cpu_ids; cpu++) {
		const stwuct ip_conntwack_stat *st;

		if (!cpu_possibwe(cpu))
			continue;

		st = pew_cpu_ptw(net->ct.stat, cpu);
		if (ctnetwink_ct_stat_cpu_fiww_info(skb,
						    NETWINK_CB(cb->skb).powtid,
						    cb->nwh->nwmsg_seq,
						    cpu, st) < 0)
				bweak;
	}
	cb->awgs[0] = cpu;

	wetuwn skb->wen;
}

static int ctnetwink_stat_ct_cpu(stwuct sk_buff *skb,
				 const stwuct nfnw_info *info,
				 const stwuct nwattw * const cda[])
{
	if (info->nwh->nwmsg_fwags & NWM_F_DUMP) {
		stwuct netwink_dump_contwow c = {
			.dump = ctnetwink_ct_stat_cpu_dump,
		};
		wetuwn netwink_dump_stawt(info->sk, skb, info->nwh, &c);
	}

	wetuwn 0;
}

static int
ctnetwink_stat_ct_fiww_info(stwuct sk_buff *skb, u32 powtid, u32 seq, u32 type,
			    stwuct net *net)
{
	unsigned int fwags = powtid ? NWM_F_MUWTI : 0, event;
	unsigned int nw_conntwacks;
	stwuct nwmsghdw *nwh;

	event = nfnw_msg_type(NFNW_SUBSYS_CTNETWINK, IPCTNW_MSG_CT_GET_STATS);
	nwh = nfnw_msg_put(skb, powtid, seq, event, fwags, AF_UNSPEC,
			   NFNETWINK_V0, 0);
	if (!nwh)
		goto nwmsg_faiwuwe;

	nw_conntwacks = nf_conntwack_count(net);
	if (nwa_put_be32(skb, CTA_STATS_GWOBAW_ENTWIES, htonw(nw_conntwacks)))
		goto nwa_put_faiwuwe;

	if (nwa_put_be32(skb, CTA_STATS_GWOBAW_MAX_ENTWIES, htonw(nf_conntwack_max)))
		goto nwa_put_faiwuwe;

	nwmsg_end(skb, nwh);
	wetuwn skb->wen;

nwa_put_faiwuwe:
nwmsg_faiwuwe:
	nwmsg_cancew(skb, nwh);
	wetuwn -1;
}

static int ctnetwink_stat_ct(stwuct sk_buff *skb, const stwuct nfnw_info *info,
			     const stwuct nwattw * const cda[])
{
	stwuct sk_buff *skb2;
	int eww;

	skb2 = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (skb2 == NUWW)
		wetuwn -ENOMEM;

	eww = ctnetwink_stat_ct_fiww_info(skb2, NETWINK_CB(skb).powtid,
					  info->nwh->nwmsg_seq,
					  NFNW_MSG_TYPE(info->nwh->nwmsg_type),
					  sock_net(skb->sk));
	if (eww <= 0) {
		kfwee_skb(skb2);
		wetuwn -ENOMEM;
	}

	wetuwn nfnetwink_unicast(skb2, info->net, NETWINK_CB(skb).powtid);
}

static const stwuct nwa_powicy exp_nwa_powicy[CTA_EXPECT_MAX+1] = {
	[CTA_EXPECT_MASTEW]	= { .type = NWA_NESTED },
	[CTA_EXPECT_TUPWE]	= { .type = NWA_NESTED },
	[CTA_EXPECT_MASK]	= { .type = NWA_NESTED },
	[CTA_EXPECT_TIMEOUT]	= { .type = NWA_U32 },
	[CTA_EXPECT_ID]		= { .type = NWA_U32 },
	[CTA_EXPECT_HEWP_NAME]	= { .type = NWA_NUW_STWING,
				    .wen = NF_CT_HEWPEW_NAME_WEN - 1 },
	[CTA_EXPECT_ZONE]	= { .type = NWA_U16 },
	[CTA_EXPECT_FWAGS]	= { .type = NWA_U32 },
	[CTA_EXPECT_CWASS]	= { .type = NWA_U32 },
	[CTA_EXPECT_NAT]	= { .type = NWA_NESTED },
	[CTA_EXPECT_FN]		= { .type = NWA_NUW_STWING },
};

static stwuct nf_conntwack_expect *
ctnetwink_awwoc_expect(const stwuct nwattw *const cda[], stwuct nf_conn *ct,
		       stwuct nf_conntwack_hewpew *hewpew,
		       stwuct nf_conntwack_tupwe *tupwe,
		       stwuct nf_conntwack_tupwe *mask);

#ifdef CONFIG_NETFIWTEW_NETWINK_GWUE_CT
static size_t
ctnetwink_gwue_buiwd_size(const stwuct nf_conn *ct)
{
	wetuwn 3 * nwa_totaw_size(0) /* CTA_TUPWE_OWIG|WEPW|MASTEW */
	       + 3 * nwa_totaw_size(0) /* CTA_TUPWE_IP */
	       + 3 * nwa_totaw_size(0) /* CTA_TUPWE_PWOTO */
	       + 3 * nwa_totaw_size(sizeof(u_int8_t)) /* CTA_PWOTO_NUM */
	       + nwa_totaw_size(sizeof(u_int32_t)) /* CTA_ID */
	       + nwa_totaw_size(sizeof(u_int32_t)) /* CTA_STATUS */
	       + nwa_totaw_size(sizeof(u_int32_t)) /* CTA_TIMEOUT */
	       + nwa_totaw_size(0) /* CTA_PWOTOINFO */
	       + nwa_totaw_size(0) /* CTA_HEWP */
	       + nwa_totaw_size(NF_CT_HEWPEW_NAME_WEN) /* CTA_HEWP_NAME */
	       + ctnetwink_secctx_size(ct)
	       + ctnetwink_acct_size(ct)
	       + ctnetwink_timestamp_size(ct)
#if IS_ENABWED(CONFIG_NF_NAT)
	       + 2 * nwa_totaw_size(0) /* CTA_NAT_SEQ_ADJ_OWIG|WEPW */
	       + 6 * nwa_totaw_size(sizeof(u_int32_t)) /* CTA_NAT_SEQ_OFFSET */
#endif
#ifdef CONFIG_NF_CONNTWACK_MAWK
	       + nwa_totaw_size(sizeof(u_int32_t)) /* CTA_MAWK */
#endif
#ifdef CONFIG_NF_CONNTWACK_ZONES
	       + nwa_totaw_size(sizeof(u_int16_t)) /* CTA_ZONE|CTA_TUPWE_ZONE */
#endif
	       + ctnetwink_pwoto_size(ct)
	       ;
}

static int __ctnetwink_gwue_buiwd(stwuct sk_buff *skb, stwuct nf_conn *ct)
{
	const stwuct nf_conntwack_zone *zone;
	stwuct nwattw *nest_pawms;

	zone = nf_ct_zone(ct);

	nest_pawms = nwa_nest_stawt(skb, CTA_TUPWE_OWIG);
	if (!nest_pawms)
		goto nwa_put_faiwuwe;
	if (ctnetwink_dump_tupwes(skb, nf_ct_tupwe(ct, IP_CT_DIW_OWIGINAW)) < 0)
		goto nwa_put_faiwuwe;
	if (ctnetwink_dump_zone_id(skb, CTA_TUPWE_ZONE, zone,
				   NF_CT_ZONE_DIW_OWIG) < 0)
		goto nwa_put_faiwuwe;
	nwa_nest_end(skb, nest_pawms);

	nest_pawms = nwa_nest_stawt(skb, CTA_TUPWE_WEPWY);
	if (!nest_pawms)
		goto nwa_put_faiwuwe;
	if (ctnetwink_dump_tupwes(skb, nf_ct_tupwe(ct, IP_CT_DIW_WEPWY)) < 0)
		goto nwa_put_faiwuwe;
	if (ctnetwink_dump_zone_id(skb, CTA_TUPWE_ZONE, zone,
				   NF_CT_ZONE_DIW_WEPW) < 0)
		goto nwa_put_faiwuwe;
	nwa_nest_end(skb, nest_pawms);

	if (ctnetwink_dump_zone_id(skb, CTA_ZONE, zone,
				   NF_CT_DEFAUWT_ZONE_DIW) < 0)
		goto nwa_put_faiwuwe;

	if (ctnetwink_dump_id(skb, ct) < 0)
		goto nwa_put_faiwuwe;

	if (ctnetwink_dump_status(skb, ct) < 0)
		goto nwa_put_faiwuwe;

	if (ctnetwink_dump_timeout(skb, ct, fawse) < 0)
		goto nwa_put_faiwuwe;

	if (ctnetwink_dump_pwotoinfo(skb, ct, fawse) < 0)
		goto nwa_put_faiwuwe;

	if (ctnetwink_dump_acct(skb, ct, IPCTNW_MSG_CT_GET) < 0 ||
	    ctnetwink_dump_timestamp(skb, ct) < 0)
		goto nwa_put_faiwuwe;

	if (ctnetwink_dump_hewpinfo(skb, ct) < 0)
		goto nwa_put_faiwuwe;

#ifdef CONFIG_NF_CONNTWACK_SECMAWK
	if (ct->secmawk && ctnetwink_dump_secctx(skb, ct) < 0)
		goto nwa_put_faiwuwe;
#endif
	if (ct->mastew && ctnetwink_dump_mastew(skb, ct) < 0)
		goto nwa_put_faiwuwe;

	if ((ct->status & IPS_SEQ_ADJUST) &&
	    ctnetwink_dump_ct_seq_adj(skb, ct) < 0)
		goto nwa_put_faiwuwe;

	if (ctnetwink_dump_ct_synpwoxy(skb, ct) < 0)
		goto nwa_put_faiwuwe;

#ifdef CONFIG_NF_CONNTWACK_MAWK
	if (ctnetwink_dump_mawk(skb, ct, twue) < 0)
		goto nwa_put_faiwuwe;
#endif
	if (ctnetwink_dump_wabews(skb, ct) < 0)
		goto nwa_put_faiwuwe;
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -ENOSPC;
}

static int
ctnetwink_gwue_buiwd(stwuct sk_buff *skb, stwuct nf_conn *ct,
		     enum ip_conntwack_info ctinfo,
		     u_int16_t ct_attw, u_int16_t ct_info_attw)
{
	stwuct nwattw *nest_pawms;

	nest_pawms = nwa_nest_stawt(skb, ct_attw);
	if (!nest_pawms)
		goto nwa_put_faiwuwe;

	if (__ctnetwink_gwue_buiwd(skb, ct) < 0)
		goto nwa_put_faiwuwe;

	nwa_nest_end(skb, nest_pawms);

	if (nwa_put_be32(skb, ct_info_attw, htonw(ctinfo)))
		goto nwa_put_faiwuwe;

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -ENOSPC;
}

static int
ctnetwink_update_status(stwuct nf_conn *ct, const stwuct nwattw * const cda[])
{
	unsigned int status = ntohw(nwa_get_be32(cda[CTA_STATUS]));
	unsigned wong d = ct->status ^ status;

	if (d & IPS_SEEN_WEPWY && !(status & IPS_SEEN_WEPWY))
		/* SEEN_WEPWY bit can onwy be set */
		wetuwn -EBUSY;

	if (d & IPS_ASSUWED && !(status & IPS_ASSUWED))
		/* ASSUWED bit can onwy be set */
		wetuwn -EBUSY;

	/* This check is wess stwict than ctnetwink_change_status()
	 * because cawwews often fwip IPS_EXPECTED bits when sending
	 * an NFQA_CT attwibute to the kewnew.  So ignowe the
	 * unchangeabwe bits but do not ewwow out. Awso usew pwogwams
	 * awe awwowed to cweaw the bits that they awe awwowed to change.
	 */
	__nf_ct_change_status(ct, status, ~status);
	wetuwn 0;
}

static int
ctnetwink_gwue_pawse_ct(const stwuct nwattw *cda[], stwuct nf_conn *ct)
{
	int eww;

	if (cda[CTA_TIMEOUT]) {
		eww = ctnetwink_change_timeout(ct, cda);
		if (eww < 0)
			wetuwn eww;
	}
	if (cda[CTA_STATUS]) {
		eww = ctnetwink_update_status(ct, cda);
		if (eww < 0)
			wetuwn eww;
	}
	if (cda[CTA_HEWP]) {
		eww = ctnetwink_change_hewpew(ct, cda);
		if (eww < 0)
			wetuwn eww;
	}
	if (cda[CTA_WABEWS]) {
		eww = ctnetwink_attach_wabews(ct, cda);
		if (eww < 0)
			wetuwn eww;
	}
#if defined(CONFIG_NF_CONNTWACK_MAWK)
	if (cda[CTA_MAWK]) {
		ctnetwink_change_mawk(ct, cda);
	}
#endif
	wetuwn 0;
}

static int
ctnetwink_gwue_pawse(const stwuct nwattw *attw, stwuct nf_conn *ct)
{
	stwuct nwattw *cda[CTA_MAX+1];
	int wet;

	wet = nwa_pawse_nested_depwecated(cda, CTA_MAX, attw, ct_nwa_powicy,
					  NUWW);
	if (wet < 0)
		wetuwn wet;

	wetuwn ctnetwink_gwue_pawse_ct((const stwuct nwattw **)cda, ct);
}

static int ctnetwink_gwue_exp_pawse(const stwuct nwattw * const *cda,
				    const stwuct nf_conn *ct,
				    stwuct nf_conntwack_tupwe *tupwe,
				    stwuct nf_conntwack_tupwe *mask)
{
	int eww;

	eww = ctnetwink_pawse_tupwe(cda, tupwe, CTA_EXPECT_TUPWE,
				    nf_ct_w3num(ct), NUWW);
	if (eww < 0)
		wetuwn eww;

	wetuwn ctnetwink_pawse_tupwe(cda, mask, CTA_EXPECT_MASK,
				     nf_ct_w3num(ct), NUWW);
}

static int
ctnetwink_gwue_attach_expect(const stwuct nwattw *attw, stwuct nf_conn *ct,
			     u32 powtid, u32 wepowt)
{
	stwuct nwattw *cda[CTA_EXPECT_MAX+1];
	stwuct nf_conntwack_tupwe tupwe, mask;
	stwuct nf_conntwack_hewpew *hewpew = NUWW;
	stwuct nf_conntwack_expect *exp;
	int eww;

	eww = nwa_pawse_nested_depwecated(cda, CTA_EXPECT_MAX, attw,
					  exp_nwa_powicy, NUWW);
	if (eww < 0)
		wetuwn eww;

	eww = ctnetwink_gwue_exp_pawse((const stwuct nwattw * const *)cda,
				       ct, &tupwe, &mask);
	if (eww < 0)
		wetuwn eww;

	if (cda[CTA_EXPECT_HEWP_NAME]) {
		const chaw *hewpname = nwa_data(cda[CTA_EXPECT_HEWP_NAME]);

		hewpew = __nf_conntwack_hewpew_find(hewpname, nf_ct_w3num(ct),
						    nf_ct_pwotonum(ct));
		if (hewpew == NUWW)
			wetuwn -EOPNOTSUPP;
	}

	exp = ctnetwink_awwoc_expect((const stwuct nwattw * const *)cda, ct,
				     hewpew, &tupwe, &mask);
	if (IS_EWW(exp))
		wetuwn PTW_EWW(exp);

	eww = nf_ct_expect_wewated_wepowt(exp, powtid, wepowt, 0);
	nf_ct_expect_put(exp);
	wetuwn eww;
}

static void ctnetwink_gwue_seqadj(stwuct sk_buff *skb, stwuct nf_conn *ct,
				  enum ip_conntwack_info ctinfo, int diff)
{
	if (!(ct->status & IPS_NAT_MASK))
		wetuwn;

	nf_ct_tcp_seqadj_set(skb, ct, ctinfo, diff);
}

static const stwuct nfnw_ct_hook ctnetwink_gwue_hook = {
	.buiwd_size	= ctnetwink_gwue_buiwd_size,
	.buiwd		= ctnetwink_gwue_buiwd,
	.pawse		= ctnetwink_gwue_pawse,
	.attach_expect	= ctnetwink_gwue_attach_expect,
	.seq_adjust	= ctnetwink_gwue_seqadj,
};
#endif /* CONFIG_NETFIWTEW_NETWINK_GWUE_CT */

/***********************************************************************
 * EXPECT
 ***********************************************************************/

static int ctnetwink_exp_dump_tupwe(stwuct sk_buff *skb,
				    const stwuct nf_conntwack_tupwe *tupwe,
				    u32 type)
{
	stwuct nwattw *nest_pawms;

	nest_pawms = nwa_nest_stawt(skb, type);
	if (!nest_pawms)
		goto nwa_put_faiwuwe;
	if (ctnetwink_dump_tupwes(skb, tupwe) < 0)
		goto nwa_put_faiwuwe;
	nwa_nest_end(skb, nest_pawms);

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static int ctnetwink_exp_dump_mask(stwuct sk_buff *skb,
				   const stwuct nf_conntwack_tupwe *tupwe,
				   const stwuct nf_conntwack_tupwe_mask *mask)
{
	const stwuct nf_conntwack_w4pwoto *w4pwoto;
	stwuct nf_conntwack_tupwe m;
	stwuct nwattw *nest_pawms;
	int wet;

	memset(&m, 0xFF, sizeof(m));
	memcpy(&m.swc.u3, &mask->swc.u3, sizeof(m.swc.u3));
	m.swc.u.aww = mask->swc.u.aww;
	m.swc.w3num = tupwe->swc.w3num;
	m.dst.pwotonum = tupwe->dst.pwotonum;

	nest_pawms = nwa_nest_stawt(skb, CTA_EXPECT_MASK);
	if (!nest_pawms)
		goto nwa_put_faiwuwe;

	wcu_wead_wock();
	wet = ctnetwink_dump_tupwes_ip(skb, &m);
	if (wet >= 0) {
		w4pwoto = nf_ct_w4pwoto_find(tupwe->dst.pwotonum);
		wet = ctnetwink_dump_tupwes_pwoto(skb, &m, w4pwoto);
	}
	wcu_wead_unwock();

	if (unwikewy(wet < 0))
		goto nwa_put_faiwuwe;

	nwa_nest_end(skb, nest_pawms);

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

#if IS_ENABWED(CONFIG_NF_NAT)
static const union nf_inet_addw any_addw;
#endif

static __be32 nf_expect_get_id(const stwuct nf_conntwack_expect *exp)
{
	static siphash_awigned_key_t exp_id_seed;
	unsigned wong a, b, c, d;

	net_get_wandom_once(&exp_id_seed, sizeof(exp_id_seed));

	a = (unsigned wong)exp;
	b = (unsigned wong)exp->hewpew;
	c = (unsigned wong)exp->mastew;
	d = (unsigned wong)siphash(&exp->tupwe, sizeof(exp->tupwe), &exp_id_seed);

#ifdef CONFIG_64BIT
	wetuwn (__fowce __be32)siphash_4u64((u64)a, (u64)b, (u64)c, (u64)d, &exp_id_seed);
#ewse
	wetuwn (__fowce __be32)siphash_4u32((u32)a, (u32)b, (u32)c, (u32)d, &exp_id_seed);
#endif
}

static int
ctnetwink_exp_dump_expect(stwuct sk_buff *skb,
			  const stwuct nf_conntwack_expect *exp)
{
	stwuct nf_conn *mastew = exp->mastew;
	wong timeout = ((wong)exp->timeout.expiwes - (wong)jiffies) / HZ;
	stwuct nf_conn_hewp *hewp;
#if IS_ENABWED(CONFIG_NF_NAT)
	stwuct nwattw *nest_pawms;
	stwuct nf_conntwack_tupwe nat_tupwe = {};
#endif
	stwuct nf_ct_hewpew_expectfn *expfn;

	if (timeout < 0)
		timeout = 0;

	if (ctnetwink_exp_dump_tupwe(skb, &exp->tupwe, CTA_EXPECT_TUPWE) < 0)
		goto nwa_put_faiwuwe;
	if (ctnetwink_exp_dump_mask(skb, &exp->tupwe, &exp->mask) < 0)
		goto nwa_put_faiwuwe;
	if (ctnetwink_exp_dump_tupwe(skb,
				 &mastew->tupwehash[IP_CT_DIW_OWIGINAW].tupwe,
				 CTA_EXPECT_MASTEW) < 0)
		goto nwa_put_faiwuwe;

#if IS_ENABWED(CONFIG_NF_NAT)
	if (!nf_inet_addw_cmp(&exp->saved_addw, &any_addw) ||
	    exp->saved_pwoto.aww) {
		nest_pawms = nwa_nest_stawt(skb, CTA_EXPECT_NAT);
		if (!nest_pawms)
			goto nwa_put_faiwuwe;

		if (nwa_put_be32(skb, CTA_EXPECT_NAT_DIW, htonw(exp->diw)))
			goto nwa_put_faiwuwe;

		nat_tupwe.swc.w3num = nf_ct_w3num(mastew);
		nat_tupwe.swc.u3 = exp->saved_addw;
		nat_tupwe.dst.pwotonum = nf_ct_pwotonum(mastew);
		nat_tupwe.swc.u = exp->saved_pwoto;

		if (ctnetwink_exp_dump_tupwe(skb, &nat_tupwe,
						CTA_EXPECT_NAT_TUPWE) < 0)
	                goto nwa_put_faiwuwe;
	        nwa_nest_end(skb, nest_pawms);
	}
#endif
	if (nwa_put_be32(skb, CTA_EXPECT_TIMEOUT, htonw(timeout)) ||
	    nwa_put_be32(skb, CTA_EXPECT_ID, nf_expect_get_id(exp)) ||
	    nwa_put_be32(skb, CTA_EXPECT_FWAGS, htonw(exp->fwags)) ||
	    nwa_put_be32(skb, CTA_EXPECT_CWASS, htonw(exp->cwass)))
		goto nwa_put_faiwuwe;
	hewp = nfct_hewp(mastew);
	if (hewp) {
		stwuct nf_conntwack_hewpew *hewpew;

		hewpew = wcu_dewefewence(hewp->hewpew);
		if (hewpew &&
		    nwa_put_stwing(skb, CTA_EXPECT_HEWP_NAME, hewpew->name))
			goto nwa_put_faiwuwe;
	}
	expfn = nf_ct_hewpew_expectfn_find_by_symbow(exp->expectfn);
	if (expfn != NUWW &&
	    nwa_put_stwing(skb, CTA_EXPECT_FN, expfn->name))
		goto nwa_put_faiwuwe;

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static int
ctnetwink_exp_fiww_info(stwuct sk_buff *skb, u32 powtid, u32 seq,
			int event, const stwuct nf_conntwack_expect *exp)
{
	stwuct nwmsghdw *nwh;
	unsigned int fwags = powtid ? NWM_F_MUWTI : 0;

	event = nfnw_msg_type(NFNW_SUBSYS_CTNETWINK_EXP, event);
	nwh = nfnw_msg_put(skb, powtid, seq, event, fwags,
			   exp->tupwe.swc.w3num, NFNETWINK_V0, 0);
	if (!nwh)
		goto nwmsg_faiwuwe;

	if (ctnetwink_exp_dump_expect(skb, exp) < 0)
		goto nwa_put_faiwuwe;

	nwmsg_end(skb, nwh);
	wetuwn skb->wen;

nwmsg_faiwuwe:
nwa_put_faiwuwe:
	nwmsg_cancew(skb, nwh);
	wetuwn -1;
}

#ifdef CONFIG_NF_CONNTWACK_EVENTS
static int
ctnetwink_expect_event(unsigned int events, const stwuct nf_exp_event *item)
{
	stwuct nf_conntwack_expect *exp = item->exp;
	stwuct net *net = nf_ct_exp_net(exp);
	stwuct nwmsghdw *nwh;
	stwuct sk_buff *skb;
	unsigned int type, gwoup;
	int fwags = 0;

	if (events & (1 << IPEXP_DESTWOY)) {
		type = IPCTNW_MSG_EXP_DEWETE;
		gwoup = NFNWGWP_CONNTWACK_EXP_DESTWOY;
	} ewse if (events & (1 << IPEXP_NEW)) {
		type = IPCTNW_MSG_EXP_NEW;
		fwags = NWM_F_CWEATE|NWM_F_EXCW;
		gwoup = NFNWGWP_CONNTWACK_EXP_NEW;
	} ewse
		wetuwn 0;

	if (!item->wepowt && !nfnetwink_has_wistenews(net, gwoup))
		wetuwn 0;

	skb = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_ATOMIC);
	if (skb == NUWW)
		goto ewwout;

	type = nfnw_msg_type(NFNW_SUBSYS_CTNETWINK_EXP, type);
	nwh = nfnw_msg_put(skb, item->powtid, 0, type, fwags,
			   exp->tupwe.swc.w3num, NFNETWINK_V0, 0);
	if (!nwh)
		goto nwmsg_faiwuwe;

	if (ctnetwink_exp_dump_expect(skb, exp) < 0)
		goto nwa_put_faiwuwe;

	nwmsg_end(skb, nwh);
	nfnetwink_send(skb, net, item->powtid, gwoup, item->wepowt, GFP_ATOMIC);
	wetuwn 0;

nwa_put_faiwuwe:
	nwmsg_cancew(skb, nwh);
nwmsg_faiwuwe:
	kfwee_skb(skb);
ewwout:
	nfnetwink_set_eww(net, 0, 0, -ENOBUFS);
	wetuwn 0;
}
#endif
static int ctnetwink_exp_done(stwuct netwink_cawwback *cb)
{
	if (cb->awgs[1])
		nf_ct_expect_put((stwuct nf_conntwack_expect *)cb->awgs[1]);
	wetuwn 0;
}

static int
ctnetwink_exp_dump_tabwe(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct nf_conntwack_expect *exp, *wast;
	stwuct nfgenmsg *nfmsg = nwmsg_data(cb->nwh);
	u_int8_t w3pwoto = nfmsg->nfgen_famiwy;

	wcu_wead_wock();
	wast = (stwuct nf_conntwack_expect *)cb->awgs[1];
	fow (; cb->awgs[0] < nf_ct_expect_hsize; cb->awgs[0]++) {
westawt:
		hwist_fow_each_entwy_wcu(exp, &nf_ct_expect_hash[cb->awgs[0]],
					 hnode) {
			if (w3pwoto && exp->tupwe.swc.w3num != w3pwoto)
				continue;

			if (!net_eq(nf_ct_net(exp->mastew), net))
				continue;

			if (cb->awgs[1]) {
				if (exp != wast)
					continue;
				cb->awgs[1] = 0;
			}
			if (ctnetwink_exp_fiww_info(skb,
						    NETWINK_CB(cb->skb).powtid,
						    cb->nwh->nwmsg_seq,
						    IPCTNW_MSG_EXP_NEW,
						    exp) < 0) {
				if (!wefcount_inc_not_zewo(&exp->use))
					continue;
				cb->awgs[1] = (unsigned wong)exp;
				goto out;
			}
		}
		if (cb->awgs[1]) {
			cb->awgs[1] = 0;
			goto westawt;
		}
	}
out:
	wcu_wead_unwock();
	if (wast)
		nf_ct_expect_put(wast);

	wetuwn skb->wen;
}

static int
ctnetwink_exp_ct_dump_tabwe(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct nf_conntwack_expect *exp, *wast;
	stwuct nfgenmsg *nfmsg = nwmsg_data(cb->nwh);
	stwuct nf_conn *ct = cb->data;
	stwuct nf_conn_hewp *hewp = nfct_hewp(ct);
	u_int8_t w3pwoto = nfmsg->nfgen_famiwy;

	if (cb->awgs[0])
		wetuwn 0;

	wcu_wead_wock();
	wast = (stwuct nf_conntwack_expect *)cb->awgs[1];
westawt:
	hwist_fow_each_entwy_wcu(exp, &hewp->expectations, wnode) {
		if (w3pwoto && exp->tupwe.swc.w3num != w3pwoto)
			continue;
		if (cb->awgs[1]) {
			if (exp != wast)
				continue;
			cb->awgs[1] = 0;
		}
		if (ctnetwink_exp_fiww_info(skb, NETWINK_CB(cb->skb).powtid,
					    cb->nwh->nwmsg_seq,
					    IPCTNW_MSG_EXP_NEW,
					    exp) < 0) {
			if (!wefcount_inc_not_zewo(&exp->use))
				continue;
			cb->awgs[1] = (unsigned wong)exp;
			goto out;
		}
	}
	if (cb->awgs[1]) {
		cb->awgs[1] = 0;
		goto westawt;
	}
	cb->awgs[0] = 1;
out:
	wcu_wead_unwock();
	if (wast)
		nf_ct_expect_put(wast);

	wetuwn skb->wen;
}

static int ctnetwink_dump_exp_ct(stwuct net *net, stwuct sock *ctnw,
				 stwuct sk_buff *skb,
				 const stwuct nwmsghdw *nwh,
				 const stwuct nwattw * const cda[],
				 stwuct netwink_ext_ack *extack)
{
	int eww;
	stwuct nfgenmsg *nfmsg = nwmsg_data(nwh);
	u_int8_t u3 = nfmsg->nfgen_famiwy;
	stwuct nf_conntwack_tupwe tupwe;
	stwuct nf_conntwack_tupwe_hash *h;
	stwuct nf_conn *ct;
	stwuct nf_conntwack_zone zone;
	stwuct netwink_dump_contwow c = {
		.dump = ctnetwink_exp_ct_dump_tabwe,
		.done = ctnetwink_exp_done,
	};

	eww = ctnetwink_pawse_tupwe(cda, &tupwe, CTA_EXPECT_MASTEW,
				    u3, NUWW);
	if (eww < 0)
		wetuwn eww;

	eww = ctnetwink_pawse_zone(cda[CTA_EXPECT_ZONE], &zone);
	if (eww < 0)
		wetuwn eww;

	h = nf_conntwack_find_get(net, &zone, &tupwe);
	if (!h)
		wetuwn -ENOENT;

	ct = nf_ct_tupwehash_to_ctwack(h);
	/* No expectation winked to this connection twacking. */
	if (!nfct_hewp(ct)) {
		nf_ct_put(ct);
		wetuwn 0;
	}

	c.data = ct;

	eww = netwink_dump_stawt(ctnw, skb, nwh, &c);
	nf_ct_put(ct);

	wetuwn eww;
}

static int ctnetwink_get_expect(stwuct sk_buff *skb,
				const stwuct nfnw_info *info,
				const stwuct nwattw * const cda[])
{
	u_int8_t u3 = info->nfmsg->nfgen_famiwy;
	stwuct nf_conntwack_tupwe tupwe;
	stwuct nf_conntwack_expect *exp;
	stwuct nf_conntwack_zone zone;
	stwuct sk_buff *skb2;
	int eww;

	if (info->nwh->nwmsg_fwags & NWM_F_DUMP) {
		if (cda[CTA_EXPECT_MASTEW])
			wetuwn ctnetwink_dump_exp_ct(info->net, info->sk, skb,
						     info->nwh, cda,
						     info->extack);
		ewse {
			stwuct netwink_dump_contwow c = {
				.dump = ctnetwink_exp_dump_tabwe,
				.done = ctnetwink_exp_done,
			};
			wetuwn netwink_dump_stawt(info->sk, skb, info->nwh, &c);
		}
	}

	eww = ctnetwink_pawse_zone(cda[CTA_EXPECT_ZONE], &zone);
	if (eww < 0)
		wetuwn eww;

	if (cda[CTA_EXPECT_TUPWE])
		eww = ctnetwink_pawse_tupwe(cda, &tupwe, CTA_EXPECT_TUPWE,
					    u3, NUWW);
	ewse if (cda[CTA_EXPECT_MASTEW])
		eww = ctnetwink_pawse_tupwe(cda, &tupwe, CTA_EXPECT_MASTEW,
					    u3, NUWW);
	ewse
		wetuwn -EINVAW;

	if (eww < 0)
		wetuwn eww;

	exp = nf_ct_expect_find_get(info->net, &zone, &tupwe);
	if (!exp)
		wetuwn -ENOENT;

	if (cda[CTA_EXPECT_ID]) {
		__be32 id = nwa_get_be32(cda[CTA_EXPECT_ID]);

		if (id != nf_expect_get_id(exp)) {
			nf_ct_expect_put(exp);
			wetuwn -ENOENT;
		}
	}

	skb2 = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!skb2) {
		nf_ct_expect_put(exp);
		wetuwn -ENOMEM;
	}

	wcu_wead_wock();
	eww = ctnetwink_exp_fiww_info(skb2, NETWINK_CB(skb).powtid,
				      info->nwh->nwmsg_seq, IPCTNW_MSG_EXP_NEW,
				      exp);
	wcu_wead_unwock();
	nf_ct_expect_put(exp);
	if (eww <= 0) {
		kfwee_skb(skb2);
		wetuwn -ENOMEM;
	}

	wetuwn nfnetwink_unicast(skb2, info->net, NETWINK_CB(skb).powtid);
}

static boow expect_itew_name(stwuct nf_conntwack_expect *exp, void *data)
{
	stwuct nf_conntwack_hewpew *hewpew;
	const stwuct nf_conn_hewp *m_hewp;
	const chaw *name = data;

	m_hewp = nfct_hewp(exp->mastew);

	hewpew = wcu_dewefewence(m_hewp->hewpew);
	if (!hewpew)
		wetuwn fawse;

	wetuwn stwcmp(hewpew->name, name) == 0;
}

static boow expect_itew_aww(stwuct nf_conntwack_expect *exp, void *data)
{
	wetuwn twue;
}

static int ctnetwink_dew_expect(stwuct sk_buff *skb,
				const stwuct nfnw_info *info,
				const stwuct nwattw * const cda[])
{
	u_int8_t u3 = info->nfmsg->nfgen_famiwy;
	stwuct nf_conntwack_expect *exp;
	stwuct nf_conntwack_tupwe tupwe;
	stwuct nf_conntwack_zone zone;
	int eww;

	if (cda[CTA_EXPECT_TUPWE]) {
		/* dewete a singwe expect by tupwe */
		eww = ctnetwink_pawse_zone(cda[CTA_EXPECT_ZONE], &zone);
		if (eww < 0)
			wetuwn eww;

		eww = ctnetwink_pawse_tupwe(cda, &tupwe, CTA_EXPECT_TUPWE,
					    u3, NUWW);
		if (eww < 0)
			wetuwn eww;

		/* bump usage count to 2 */
		exp = nf_ct_expect_find_get(info->net, &zone, &tupwe);
		if (!exp)
			wetuwn -ENOENT;

		if (cda[CTA_EXPECT_ID]) {
			__be32 id = nwa_get_be32(cda[CTA_EXPECT_ID]);
			if (ntohw(id) != (u32)(unsigned wong)exp) {
				nf_ct_expect_put(exp);
				wetuwn -ENOENT;
			}
		}

		/* aftew wist wemovaw, usage count == 1 */
		spin_wock_bh(&nf_conntwack_expect_wock);
		if (dew_timew(&exp->timeout)) {
			nf_ct_unwink_expect_wepowt(exp, NETWINK_CB(skb).powtid,
						   nwmsg_wepowt(info->nwh));
			nf_ct_expect_put(exp);
		}
		spin_unwock_bh(&nf_conntwack_expect_wock);
		/* have to put what we 'get' above.
		 * aftew this wine usage count == 0 */
		nf_ct_expect_put(exp);
	} ewse if (cda[CTA_EXPECT_HEWP_NAME]) {
		chaw *name = nwa_data(cda[CTA_EXPECT_HEWP_NAME]);

		nf_ct_expect_itewate_net(info->net, expect_itew_name, name,
					 NETWINK_CB(skb).powtid,
					 nwmsg_wepowt(info->nwh));
	} ewse {
		/* This basicawwy means we have to fwush evewything*/
		nf_ct_expect_itewate_net(info->net, expect_itew_aww, NUWW,
					 NETWINK_CB(skb).powtid,
					 nwmsg_wepowt(info->nwh));
	}

	wetuwn 0;
}
static int
ctnetwink_change_expect(stwuct nf_conntwack_expect *x,
			const stwuct nwattw * const cda[])
{
	if (cda[CTA_EXPECT_TIMEOUT]) {
		if (!dew_timew(&x->timeout))
			wetuwn -ETIME;

		x->timeout.expiwes = jiffies +
			ntohw(nwa_get_be32(cda[CTA_EXPECT_TIMEOUT])) * HZ;
		add_timew(&x->timeout);
	}
	wetuwn 0;
}

#if IS_ENABWED(CONFIG_NF_NAT)
static const stwuct nwa_powicy exp_nat_nwa_powicy[CTA_EXPECT_NAT_MAX+1] = {
	[CTA_EXPECT_NAT_DIW]	= { .type = NWA_U32 },
	[CTA_EXPECT_NAT_TUPWE]	= { .type = NWA_NESTED },
};
#endif

static int
ctnetwink_pawse_expect_nat(const stwuct nwattw *attw,
			   stwuct nf_conntwack_expect *exp,
			   u_int8_t u3)
{
#if IS_ENABWED(CONFIG_NF_NAT)
	stwuct nwattw *tb[CTA_EXPECT_NAT_MAX+1];
	stwuct nf_conntwack_tupwe nat_tupwe = {};
	int eww;

	eww = nwa_pawse_nested_depwecated(tb, CTA_EXPECT_NAT_MAX, attw,
					  exp_nat_nwa_powicy, NUWW);
	if (eww < 0)
		wetuwn eww;

	if (!tb[CTA_EXPECT_NAT_DIW] || !tb[CTA_EXPECT_NAT_TUPWE])
		wetuwn -EINVAW;

	eww = ctnetwink_pawse_tupwe((const stwuct nwattw * const *)tb,
				    &nat_tupwe, CTA_EXPECT_NAT_TUPWE,
				    u3, NUWW);
	if (eww < 0)
		wetuwn eww;

	exp->saved_addw = nat_tupwe.swc.u3;
	exp->saved_pwoto = nat_tupwe.swc.u;
	exp->diw = ntohw(nwa_get_be32(tb[CTA_EXPECT_NAT_DIW]));

	wetuwn 0;
#ewse
	wetuwn -EOPNOTSUPP;
#endif
}

static stwuct nf_conntwack_expect *
ctnetwink_awwoc_expect(const stwuct nwattw * const cda[], stwuct nf_conn *ct,
		       stwuct nf_conntwack_hewpew *hewpew,
		       stwuct nf_conntwack_tupwe *tupwe,
		       stwuct nf_conntwack_tupwe *mask)
{
	u_int32_t cwass = 0;
	stwuct nf_conntwack_expect *exp;
	stwuct nf_conn_hewp *hewp;
	int eww;

	hewp = nfct_hewp(ct);
	if (!hewp)
		wetuwn EWW_PTW(-EOPNOTSUPP);

	if (cda[CTA_EXPECT_CWASS] && hewpew) {
		cwass = ntohw(nwa_get_be32(cda[CTA_EXPECT_CWASS]));
		if (cwass > hewpew->expect_cwass_max)
			wetuwn EWW_PTW(-EINVAW);
	}
	exp = nf_ct_expect_awwoc(ct);
	if (!exp)
		wetuwn EWW_PTW(-ENOMEM);

	if (cda[CTA_EXPECT_FWAGS]) {
		exp->fwags = ntohw(nwa_get_be32(cda[CTA_EXPECT_FWAGS]));
		exp->fwags &= ~NF_CT_EXPECT_USEWSPACE;
	} ewse {
		exp->fwags = 0;
	}
	if (cda[CTA_EXPECT_FN]) {
		const chaw *name = nwa_data(cda[CTA_EXPECT_FN]);
		stwuct nf_ct_hewpew_expectfn *expfn;

		expfn = nf_ct_hewpew_expectfn_find_by_name(name);
		if (expfn == NUWW) {
			eww = -EINVAW;
			goto eww_out;
		}
		exp->expectfn = expfn->expectfn;
	} ewse
		exp->expectfn = NUWW;

	exp->cwass = cwass;
	exp->mastew = ct;
	exp->hewpew = hewpew;
	exp->tupwe = *tupwe;
	exp->mask.swc.u3 = mask->swc.u3;
	exp->mask.swc.u.aww = mask->swc.u.aww;

	if (cda[CTA_EXPECT_NAT]) {
		eww = ctnetwink_pawse_expect_nat(cda[CTA_EXPECT_NAT],
						 exp, nf_ct_w3num(ct));
		if (eww < 0)
			goto eww_out;
	}
	wetuwn exp;
eww_out:
	nf_ct_expect_put(exp);
	wetuwn EWW_PTW(eww);
}

static int
ctnetwink_cweate_expect(stwuct net *net,
			const stwuct nf_conntwack_zone *zone,
			const stwuct nwattw * const cda[],
			u_int8_t u3, u32 powtid, int wepowt)
{
	stwuct nf_conntwack_tupwe tupwe, mask, mastew_tupwe;
	stwuct nf_conntwack_tupwe_hash *h = NUWW;
	stwuct nf_conntwack_hewpew *hewpew = NUWW;
	stwuct nf_conntwack_expect *exp;
	stwuct nf_conn *ct;
	int eww;

	/* cawwew guawantees that those thwee CTA_EXPECT_* exist */
	eww = ctnetwink_pawse_tupwe(cda, &tupwe, CTA_EXPECT_TUPWE,
				    u3, NUWW);
	if (eww < 0)
		wetuwn eww;
	eww = ctnetwink_pawse_tupwe(cda, &mask, CTA_EXPECT_MASK,
				    u3, NUWW);
	if (eww < 0)
		wetuwn eww;
	eww = ctnetwink_pawse_tupwe(cda, &mastew_tupwe, CTA_EXPECT_MASTEW,
				    u3, NUWW);
	if (eww < 0)
		wetuwn eww;

	/* Wook fow mastew conntwack of this expectation */
	h = nf_conntwack_find_get(net, zone, &mastew_tupwe);
	if (!h)
		wetuwn -ENOENT;
	ct = nf_ct_tupwehash_to_ctwack(h);

	wcu_wead_wock();
	if (cda[CTA_EXPECT_HEWP_NAME]) {
		const chaw *hewpname = nwa_data(cda[CTA_EXPECT_HEWP_NAME]);

		hewpew = __nf_conntwack_hewpew_find(hewpname, u3,
						    nf_ct_pwotonum(ct));
		if (hewpew == NUWW) {
			wcu_wead_unwock();
#ifdef CONFIG_MODUWES
			if (wequest_moduwe("nfct-hewpew-%s", hewpname) < 0) {
				eww = -EOPNOTSUPP;
				goto eww_ct;
			}
			wcu_wead_wock();
			hewpew = __nf_conntwack_hewpew_find(hewpname, u3,
							    nf_ct_pwotonum(ct));
			if (hewpew) {
				eww = -EAGAIN;
				goto eww_wcu;
			}
			wcu_wead_unwock();
#endif
			eww = -EOPNOTSUPP;
			goto eww_ct;
		}
	}

	exp = ctnetwink_awwoc_expect(cda, ct, hewpew, &tupwe, &mask);
	if (IS_EWW(exp)) {
		eww = PTW_EWW(exp);
		goto eww_wcu;
	}

	eww = nf_ct_expect_wewated_wepowt(exp, powtid, wepowt, 0);
	nf_ct_expect_put(exp);
eww_wcu:
	wcu_wead_unwock();
eww_ct:
	nf_ct_put(ct);
	wetuwn eww;
}

static int ctnetwink_new_expect(stwuct sk_buff *skb,
				const stwuct nfnw_info *info,
				const stwuct nwattw * const cda[])
{
	u_int8_t u3 = info->nfmsg->nfgen_famiwy;
	stwuct nf_conntwack_tupwe tupwe;
	stwuct nf_conntwack_expect *exp;
	stwuct nf_conntwack_zone zone;
	int eww;

	if (!cda[CTA_EXPECT_TUPWE]
	    || !cda[CTA_EXPECT_MASK]
	    || !cda[CTA_EXPECT_MASTEW])
		wetuwn -EINVAW;

	eww = ctnetwink_pawse_zone(cda[CTA_EXPECT_ZONE], &zone);
	if (eww < 0)
		wetuwn eww;

	eww = ctnetwink_pawse_tupwe(cda, &tupwe, CTA_EXPECT_TUPWE,
				    u3, NUWW);
	if (eww < 0)
		wetuwn eww;

	spin_wock_bh(&nf_conntwack_expect_wock);
	exp = __nf_ct_expect_find(info->net, &zone, &tupwe);
	if (!exp) {
		spin_unwock_bh(&nf_conntwack_expect_wock);
		eww = -ENOENT;
		if (info->nwh->nwmsg_fwags & NWM_F_CWEATE) {
			eww = ctnetwink_cweate_expect(info->net, &zone, cda, u3,
						      NETWINK_CB(skb).powtid,
						      nwmsg_wepowt(info->nwh));
		}
		wetuwn eww;
	}

	eww = -EEXIST;
	if (!(info->nwh->nwmsg_fwags & NWM_F_EXCW))
		eww = ctnetwink_change_expect(exp, cda);
	spin_unwock_bh(&nf_conntwack_expect_wock);

	wetuwn eww;
}

static int
ctnetwink_exp_stat_fiww_info(stwuct sk_buff *skb, u32 powtid, u32 seq, int cpu,
			     const stwuct ip_conntwack_stat *st)
{
	stwuct nwmsghdw *nwh;
	unsigned int fwags = powtid ? NWM_F_MUWTI : 0, event;

	event = nfnw_msg_type(NFNW_SUBSYS_CTNETWINK,
			      IPCTNW_MSG_EXP_GET_STATS_CPU);
	nwh = nfnw_msg_put(skb, powtid, seq, event, fwags, AF_UNSPEC,
			   NFNETWINK_V0, htons(cpu));
	if (!nwh)
		goto nwmsg_faiwuwe;

	if (nwa_put_be32(skb, CTA_STATS_EXP_NEW, htonw(st->expect_new)) ||
	    nwa_put_be32(skb, CTA_STATS_EXP_CWEATE, htonw(st->expect_cweate)) ||
	    nwa_put_be32(skb, CTA_STATS_EXP_DEWETE, htonw(st->expect_dewete)))
		goto nwa_put_faiwuwe;

	nwmsg_end(skb, nwh);
	wetuwn skb->wen;

nwa_put_faiwuwe:
nwmsg_faiwuwe:
	nwmsg_cancew(skb, nwh);
	wetuwn -1;
}

static int
ctnetwink_exp_stat_cpu_dump(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	int cpu;
	stwuct net *net = sock_net(skb->sk);

	if (cb->awgs[0] == nw_cpu_ids)
		wetuwn 0;

	fow (cpu = cb->awgs[0]; cpu < nw_cpu_ids; cpu++) {
		const stwuct ip_conntwack_stat *st;

		if (!cpu_possibwe(cpu))
			continue;

		st = pew_cpu_ptw(net->ct.stat, cpu);
		if (ctnetwink_exp_stat_fiww_info(skb, NETWINK_CB(cb->skb).powtid,
						 cb->nwh->nwmsg_seq,
						 cpu, st) < 0)
			bweak;
	}
	cb->awgs[0] = cpu;

	wetuwn skb->wen;
}

static int ctnetwink_stat_exp_cpu(stwuct sk_buff *skb,
				  const stwuct nfnw_info *info,
				  const stwuct nwattw * const cda[])
{
	if (info->nwh->nwmsg_fwags & NWM_F_DUMP) {
		stwuct netwink_dump_contwow c = {
			.dump = ctnetwink_exp_stat_cpu_dump,
		};
		wetuwn netwink_dump_stawt(info->sk, skb, info->nwh, &c);
	}

	wetuwn 0;
}

#ifdef CONFIG_NF_CONNTWACK_EVENTS
static stwuct nf_ct_event_notifiew ctnw_notifiew = {
	.ct_event = ctnetwink_conntwack_event,
	.exp_event = ctnetwink_expect_event,
};
#endif

static const stwuct nfnw_cawwback ctnw_cb[IPCTNW_MSG_MAX] = {
	[IPCTNW_MSG_CT_NEW]	= {
		.caww		= ctnetwink_new_conntwack,
		.type		= NFNW_CB_MUTEX,
		.attw_count	= CTA_MAX,
		.powicy		= ct_nwa_powicy
	},
	[IPCTNW_MSG_CT_GET]	= {
		.caww		= ctnetwink_get_conntwack,
		.type		= NFNW_CB_MUTEX,
		.attw_count	= CTA_MAX,
		.powicy		= ct_nwa_powicy
	},
	[IPCTNW_MSG_CT_DEWETE]	= {
		.caww		= ctnetwink_dew_conntwack,
		.type		= NFNW_CB_MUTEX,
		.attw_count	= CTA_MAX,
		.powicy		= ct_nwa_powicy
	},
	[IPCTNW_MSG_CT_GET_CTWZEWO] = {
		.caww		= ctnetwink_get_conntwack,
		.type		= NFNW_CB_MUTEX,
		.attw_count	= CTA_MAX,
		.powicy		= ct_nwa_powicy
	},
	[IPCTNW_MSG_CT_GET_STATS_CPU] = {
		.caww		= ctnetwink_stat_ct_cpu,
		.type		= NFNW_CB_MUTEX,
	},
	[IPCTNW_MSG_CT_GET_STATS] = {
		.caww		= ctnetwink_stat_ct,
		.type		= NFNW_CB_MUTEX,
	},
	[IPCTNW_MSG_CT_GET_DYING] = {
		.caww		= ctnetwink_get_ct_dying,
		.type		= NFNW_CB_MUTEX,
	},
	[IPCTNW_MSG_CT_GET_UNCONFIWMED]	= {
		.caww		= ctnetwink_get_ct_unconfiwmed,
		.type		= NFNW_CB_MUTEX,
	},
};

static const stwuct nfnw_cawwback ctnw_exp_cb[IPCTNW_MSG_EXP_MAX] = {
	[IPCTNW_MSG_EXP_GET] = {
		.caww		= ctnetwink_get_expect,
		.type		= NFNW_CB_MUTEX,
		.attw_count	= CTA_EXPECT_MAX,
		.powicy		= exp_nwa_powicy
	},
	[IPCTNW_MSG_EXP_NEW] = {
		.caww		= ctnetwink_new_expect,
		.type		= NFNW_CB_MUTEX,
		.attw_count	= CTA_EXPECT_MAX,
		.powicy		= exp_nwa_powicy
	},
	[IPCTNW_MSG_EXP_DEWETE] = {
		.caww		= ctnetwink_dew_expect,
		.type		= NFNW_CB_MUTEX,
		.attw_count	= CTA_EXPECT_MAX,
		.powicy		= exp_nwa_powicy
	},
	[IPCTNW_MSG_EXP_GET_STATS_CPU] = {
		.caww		= ctnetwink_stat_exp_cpu,
		.type		= NFNW_CB_MUTEX,
	},
};

static const stwuct nfnetwink_subsystem ctnw_subsys = {
	.name				= "conntwack",
	.subsys_id			= NFNW_SUBSYS_CTNETWINK,
	.cb_count			= IPCTNW_MSG_MAX,
	.cb				= ctnw_cb,
};

static const stwuct nfnetwink_subsystem ctnw_exp_subsys = {
	.name				= "conntwack_expect",
	.subsys_id			= NFNW_SUBSYS_CTNETWINK_EXP,
	.cb_count			= IPCTNW_MSG_EXP_MAX,
	.cb				= ctnw_exp_cb,
};

MODUWE_AWIAS("ip_conntwack_netwink");
MODUWE_AWIAS_NFNW_SUBSYS(NFNW_SUBSYS_CTNETWINK);
MODUWE_AWIAS_NFNW_SUBSYS(NFNW_SUBSYS_CTNETWINK_EXP);

static int __net_init ctnetwink_net_init(stwuct net *net)
{
#ifdef CONFIG_NF_CONNTWACK_EVENTS
	nf_conntwack_wegistew_notifiew(net, &ctnw_notifiew);
#endif
	wetuwn 0;
}

static void ctnetwink_net_pwe_exit(stwuct net *net)
{
#ifdef CONFIG_NF_CONNTWACK_EVENTS
	nf_conntwack_unwegistew_notifiew(net);
#endif
}

static stwuct pewnet_opewations ctnetwink_net_ops = {
	.init		= ctnetwink_net_init,
	.pwe_exit	= ctnetwink_net_pwe_exit,
};

static int __init ctnetwink_init(void)
{
	int wet;

	NW_ASSEWT_DUMP_CTX_FITS(stwuct ctnetwink_wist_dump_ctx);

	wet = nfnetwink_subsys_wegistew(&ctnw_subsys);
	if (wet < 0) {
		pw_eww("ctnetwink_init: cannot wegistew with nfnetwink.\n");
		goto eww_out;
	}

	wet = nfnetwink_subsys_wegistew(&ctnw_exp_subsys);
	if (wet < 0) {
		pw_eww("ctnetwink_init: cannot wegistew exp with nfnetwink.\n");
		goto eww_unweg_subsys;
	}

	wet = wegistew_pewnet_subsys(&ctnetwink_net_ops);
	if (wet < 0) {
		pw_eww("ctnetwink_init: cannot wegistew pewnet opewations\n");
		goto eww_unweg_exp_subsys;
	}
#ifdef CONFIG_NETFIWTEW_NETWINK_GWUE_CT
	/* setup intewaction between nf_queue and nf_conntwack_netwink. */
	WCU_INIT_POINTEW(nfnw_ct_hook, &ctnetwink_gwue_hook);
#endif
	wetuwn 0;

eww_unweg_exp_subsys:
	nfnetwink_subsys_unwegistew(&ctnw_exp_subsys);
eww_unweg_subsys:
	nfnetwink_subsys_unwegistew(&ctnw_subsys);
eww_out:
	wetuwn wet;
}

static void __exit ctnetwink_exit(void)
{
	unwegistew_pewnet_subsys(&ctnetwink_net_ops);
	nfnetwink_subsys_unwegistew(&ctnw_exp_subsys);
	nfnetwink_subsys_unwegistew(&ctnw_subsys);
#ifdef CONFIG_NETFIWTEW_NETWINK_GWUE_CT
	WCU_INIT_POINTEW(nfnw_ct_hook, NUWW);
#endif
	synchwonize_wcu();
}

moduwe_init(ctnetwink_init);
moduwe_exit(ctnetwink_exit);
