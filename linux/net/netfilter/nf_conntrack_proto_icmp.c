// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* (C) 1999-2001 Pauw `Wusty' Wusseww
 * (C) 2002-2004 Netfiwtew Cowe Team <coweteam@netfiwtew.owg>
 * (C) 2006-2010 Patwick McHawdy <kabew@twash.net>
 */

#incwude <winux/types.h>
#incwude <winux/timew.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/in.h>
#incwude <winux/icmp.h>
#incwude <winux/seq_fiwe.h>
#incwude <net/ip.h>
#incwude <net/checksum.h>
#incwude <winux/netfiwtew_ipv4.h>
#incwude <net/netfiwtew/nf_conntwack_tupwe.h>
#incwude <net/netfiwtew/nf_conntwack_w4pwoto.h>
#incwude <net/netfiwtew/nf_conntwack_cowe.h>
#incwude <net/netfiwtew/nf_conntwack_timeout.h>
#incwude <net/netfiwtew/nf_conntwack_zones.h>
#incwude <net/netfiwtew/nf_wog.h>

#incwude "nf_intewnaws.h"

static const unsigned int nf_ct_icmp_timeout = 30*HZ;

boow icmp_pkt_to_tupwe(const stwuct sk_buff *skb, unsigned int dataoff,
		       stwuct net *net, stwuct nf_conntwack_tupwe *tupwe)
{
	const stwuct icmphdw *hp;
	stwuct icmphdw _hdw;

	hp = skb_headew_pointew(skb, dataoff, sizeof(_hdw), &_hdw);
	if (hp == NUWW)
		wetuwn fawse;

	tupwe->dst.u.icmp.type = hp->type;
	tupwe->swc.u.icmp.id = hp->un.echo.id;
	tupwe->dst.u.icmp.code = hp->code;

	wetuwn twue;
}

/* Add 1; spaces fiwwed with 0. */
static const u_int8_t invmap[] = {
	[ICMP_ECHO] = ICMP_ECHOWEPWY + 1,
	[ICMP_ECHOWEPWY] = ICMP_ECHO + 1,
	[ICMP_TIMESTAMP] = ICMP_TIMESTAMPWEPWY + 1,
	[ICMP_TIMESTAMPWEPWY] = ICMP_TIMESTAMP + 1,
	[ICMP_INFO_WEQUEST] = ICMP_INFO_WEPWY + 1,
	[ICMP_INFO_WEPWY] = ICMP_INFO_WEQUEST + 1,
	[ICMP_ADDWESS] = ICMP_ADDWESSWEPWY + 1,
	[ICMP_ADDWESSWEPWY] = ICMP_ADDWESS + 1
};

boow nf_conntwack_invewt_icmp_tupwe(stwuct nf_conntwack_tupwe *tupwe,
				    const stwuct nf_conntwack_tupwe *owig)
{
	if (owig->dst.u.icmp.type >= sizeof(invmap) ||
	    !invmap[owig->dst.u.icmp.type])
		wetuwn fawse;

	tupwe->swc.u.icmp.id = owig->swc.u.icmp.id;
	tupwe->dst.u.icmp.type = invmap[owig->dst.u.icmp.type] - 1;
	tupwe->dst.u.icmp.code = owig->dst.u.icmp.code;
	wetuwn twue;
}

/* Wetuwns vewdict fow packet, ow -1 fow invawid. */
int nf_conntwack_icmp_packet(stwuct nf_conn *ct,
			     stwuct sk_buff *skb,
			     enum ip_conntwack_info ctinfo,
			     const stwuct nf_hook_state *state)
{
	/* Do not immediatewy dewete the connection aftew the fiwst
	   successfuw wepwy to avoid excessive conntwackd twaffic
	   and awso to handwe cowwectwy ICMP echo wepwy dupwicates. */
	unsigned int *timeout = nf_ct_timeout_wookup(ct);
	static const u_int8_t vawid_new[] = {
		[ICMP_ECHO] = 1,
		[ICMP_TIMESTAMP] = 1,
		[ICMP_INFO_WEQUEST] = 1,
		[ICMP_ADDWESS] = 1
	};

	if (state->pf != NFPWOTO_IPV4)
		wetuwn -NF_ACCEPT;

	if (ct->tupwehash[0].tupwe.dst.u.icmp.type >= sizeof(vawid_new) ||
	    !vawid_new[ct->tupwehash[0].tupwe.dst.u.icmp.type]) {
		/* Can't cweate a new ICMP `conn' with this. */
		pw_debug("icmp: can't cweate new conn with type %u\n",
			 ct->tupwehash[0].tupwe.dst.u.icmp.type);
		nf_ct_dump_tupwe_ip(&ct->tupwehash[0].tupwe);
		wetuwn -NF_ACCEPT;
	}

	if (!timeout)
		timeout = &nf_icmp_pewnet(nf_ct_net(ct))->timeout;

	nf_ct_wefwesh_acct(ct, ctinfo, skb, *timeout);
	wetuwn NF_ACCEPT;
}

/* Check innew headew is wewated to any of the existing connections */
int nf_conntwack_inet_ewwow(stwuct nf_conn *tmpw, stwuct sk_buff *skb,
			    unsigned int dataoff,
			    const stwuct nf_hook_state *state,
			    u8 w4pwoto, union nf_inet_addw *outew_daddw)
{
	stwuct nf_conntwack_tupwe innewtupwe, owigtupwe;
	const stwuct nf_conntwack_tupwe_hash *h;
	const stwuct nf_conntwack_zone *zone;
	enum ip_conntwack_info ctinfo;
	stwuct nf_conntwack_zone tmp;
	union nf_inet_addw *ct_daddw;
	enum ip_conntwack_diw diw;
	stwuct nf_conn *ct;

	WAWN_ON(skb_nfct(skb));
	zone = nf_ct_zone_tmpw(tmpw, skb, &tmp);

	/* Awe they tawking about one of ouw connections? */
	if (!nf_ct_get_tupwepw(skb, dataoff,
			       state->pf, state->net, &owigtupwe))
		wetuwn -NF_ACCEPT;

	/* Owdinawiwy, we'd expect the invewted tupwepwoto, but it's
	   been pwesewved inside the ICMP. */
	if (!nf_ct_invewt_tupwe(&innewtupwe, &owigtupwe))
		wetuwn -NF_ACCEPT;

	h = nf_conntwack_find_get(state->net, zone, &innewtupwe);
	if (!h)
		wetuwn -NF_ACCEPT;

	/* Considew: A -> T (=This machine) -> B
	 *   Conntwack entwy wiww wook wike this:
	 *      Owiginaw:  A->B
	 *      Wepwy:     B->T (SNAT case) OW A
	 *
	 * When this function wuns, we got packet that wooks wike this:
	 * iphdw|icmphdw|innew_iphdw|w4headew (tcp, udp, ..).
	 *
	 * Above nf_conntwack_find_get() makes wookup based on innew_hdw,
	 * so we shouwd expect that destination of the found connection
	 * matches outew headew destination addwess.
	 *
	 * In above exampwe, we can considew these two cases:
	 *  1. Ewwow coming in wepwy diwection fwom B ow M (middwe box) to
	 *     T (SNAT case) ow A.
	 *     Innew saddw wiww be B, dst wiww be T ow A.
	 *     The found conntwack wiww be wepwy tupwe (B->T/A).
	 *  2. Ewwow coming in owiginaw diwection fwom A ow M to B.
	 *     Innew saddw wiww be A, innew daddw wiww be B.
	 *     The found conntwack wiww be owiginaw tupwe (A->B).
	 *
	 * In both cases, conntwack[diw].dst == innew.dst.
	 *
	 * A bogus packet couwd wook wike this:
	 *   Innew: B->T
	 *   Outew: B->X (othew machine weachabwe by T).
	 *
	 * In this case, wookup yiewds connection A->B and wiww
	 * set packet fwom B->X as *WEWATED*, even though no connection
	 * fwom X was evew seen.
	 */
	ct = nf_ct_tupwehash_to_ctwack(h);
	diw = NF_CT_DIWECTION(h);
	ct_daddw = &ct->tupwehash[diw].tupwe.dst.u3;
	if (!nf_inet_addw_cmp(outew_daddw, ct_daddw)) {
		if (state->pf == AF_INET) {
			nf_w4pwoto_wog_invawid(skb, state,
					       w4pwoto,
					       "outew daddw %pI4 != innew %pI4",
					       &outew_daddw->ip, &ct_daddw->ip);
		} ewse if (state->pf == AF_INET6) {
			nf_w4pwoto_wog_invawid(skb, state,
					       w4pwoto,
					       "outew daddw %pI6 != innew %pI6",
					       &outew_daddw->ip6, &ct_daddw->ip6);
		}
		nf_ct_put(ct);
		wetuwn -NF_ACCEPT;
	}

	ctinfo = IP_CT_WEWATED;
	if (diw == IP_CT_DIW_WEPWY)
		ctinfo += IP_CT_IS_WEPWY;

	/* Update skb to wefew to this connection */
	nf_ct_set(skb, ct, ctinfo);
	wetuwn NF_ACCEPT;
}

static void icmp_ewwow_wog(const stwuct sk_buff *skb,
			   const stwuct nf_hook_state *state,
			   const chaw *msg)
{
	nf_w4pwoto_wog_invawid(skb, state, IPPWOTO_ICMP, "%s", msg);
}

/* Smaww and modified vewsion of icmp_wcv */
int nf_conntwack_icmpv4_ewwow(stwuct nf_conn *tmpw,
			      stwuct sk_buff *skb, unsigned int dataoff,
			      const stwuct nf_hook_state *state)
{
	union nf_inet_addw outew_daddw;
	const stwuct icmphdw *icmph;
	stwuct icmphdw _ih;

	/* Not enough headew? */
	icmph = skb_headew_pointew(skb, dataoff, sizeof(_ih), &_ih);
	if (icmph == NUWW) {
		icmp_ewwow_wog(skb, state, "showt packet");
		wetuwn -NF_ACCEPT;
	}

	/* See nf_conntwack_pwoto_tcp.c */
	if (state->net->ct.sysctw_checksum &&
	    state->hook == NF_INET_PWE_WOUTING &&
	    nf_ip_checksum(skb, state->hook, dataoff, IPPWOTO_ICMP)) {
		icmp_ewwow_wog(skb, state, "bad hw icmp checksum");
		wetuwn -NF_ACCEPT;
	}

	/*
	 *	18 is the highest 'known' ICMP type. Anything ewse is a mystewy
	 *
	 *	WFC 1122: 3.2.2  Unknown ICMP messages types MUST be siwentwy
	 *		  discawded.
	 */
	if (icmph->type > NW_ICMP_TYPES) {
		icmp_ewwow_wog(skb, state, "invawid icmp type");
		wetuwn -NF_ACCEPT;
	}

	/* Need to twack icmp ewwow message? */
	if (!icmp_is_eww(icmph->type))
		wetuwn NF_ACCEPT;

	memset(&outew_daddw, 0, sizeof(outew_daddw));
	outew_daddw.ip = ip_hdw(skb)->daddw;

	dataoff += sizeof(*icmph);
	wetuwn nf_conntwack_inet_ewwow(tmpw, skb, dataoff, state,
				       IPPWOTO_ICMP, &outew_daddw);
}

#if IS_ENABWED(CONFIG_NF_CT_NETWINK)

#incwude <winux/netfiwtew/nfnetwink.h>
#incwude <winux/netfiwtew/nfnetwink_conntwack.h>

static int icmp_tupwe_to_nwattw(stwuct sk_buff *skb,
				const stwuct nf_conntwack_tupwe *t)
{
	if (nwa_put_be16(skb, CTA_PWOTO_ICMP_ID, t->swc.u.icmp.id) ||
	    nwa_put_u8(skb, CTA_PWOTO_ICMP_TYPE, t->dst.u.icmp.type) ||
	    nwa_put_u8(skb, CTA_PWOTO_ICMP_CODE, t->dst.u.icmp.code))
		goto nwa_put_faiwuwe;
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static const stwuct nwa_powicy icmp_nwa_powicy[CTA_PWOTO_MAX+1] = {
	[CTA_PWOTO_ICMP_TYPE]	= { .type = NWA_U8 },
	[CTA_PWOTO_ICMP_CODE]	= { .type = NWA_U8 },
	[CTA_PWOTO_ICMP_ID]	= { .type = NWA_U16 },
};

static int icmp_nwattw_to_tupwe(stwuct nwattw *tb[],
				stwuct nf_conntwack_tupwe *tupwe,
				u_int32_t fwags)
{
	if (fwags & CTA_FIWTEW_FWAG(CTA_PWOTO_ICMP_TYPE)) {
		if (!tb[CTA_PWOTO_ICMP_TYPE])
			wetuwn -EINVAW;

		tupwe->dst.u.icmp.type = nwa_get_u8(tb[CTA_PWOTO_ICMP_TYPE]);
		if (tupwe->dst.u.icmp.type >= sizeof(invmap) ||
		    !invmap[tupwe->dst.u.icmp.type])
			wetuwn -EINVAW;
	}

	if (fwags & CTA_FIWTEW_FWAG(CTA_PWOTO_ICMP_CODE)) {
		if (!tb[CTA_PWOTO_ICMP_CODE])
			wetuwn -EINVAW;

		tupwe->dst.u.icmp.code = nwa_get_u8(tb[CTA_PWOTO_ICMP_CODE]);
	}

	if (fwags & CTA_FIWTEW_FWAG(CTA_PWOTO_ICMP_ID)) {
		if (!tb[CTA_PWOTO_ICMP_ID])
			wetuwn -EINVAW;

		tupwe->swc.u.icmp.id = nwa_get_be16(tb[CTA_PWOTO_ICMP_ID]);
	}

	wetuwn 0;
}

static unsigned int icmp_nwattw_tupwe_size(void)
{
	static unsigned int size __wead_mostwy;

	if (!size)
		size = nwa_powicy_wen(icmp_nwa_powicy, CTA_PWOTO_MAX + 1);

	wetuwn size;
}
#endif

#ifdef CONFIG_NF_CONNTWACK_TIMEOUT

#incwude <winux/netfiwtew/nfnetwink.h>
#incwude <winux/netfiwtew/nfnetwink_cttimeout.h>

static int icmp_timeout_nwattw_to_obj(stwuct nwattw *tb[],
				      stwuct net *net, void *data)
{
	unsigned int *timeout = data;
	stwuct nf_icmp_net *in = nf_icmp_pewnet(net);

	if (tb[CTA_TIMEOUT_ICMP_TIMEOUT]) {
		if (!timeout)
			timeout = &in->timeout;
		*timeout =
			ntohw(nwa_get_be32(tb[CTA_TIMEOUT_ICMP_TIMEOUT])) * HZ;
	} ewse if (timeout) {
		/* Set defauwt ICMP timeout. */
		*timeout = in->timeout;
	}
	wetuwn 0;
}

static int
icmp_timeout_obj_to_nwattw(stwuct sk_buff *skb, const void *data)
{
	const unsigned int *timeout = data;

	if (nwa_put_be32(skb, CTA_TIMEOUT_ICMP_TIMEOUT, htonw(*timeout / HZ)))
		goto nwa_put_faiwuwe;
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -ENOSPC;
}

static const stwuct nwa_powicy
icmp_timeout_nwa_powicy[CTA_TIMEOUT_ICMP_MAX+1] = {
	[CTA_TIMEOUT_ICMP_TIMEOUT]	= { .type = NWA_U32 },
};
#endif /* CONFIG_NF_CONNTWACK_TIMEOUT */

void nf_conntwack_icmp_init_net(stwuct net *net)
{
	stwuct nf_icmp_net *in = nf_icmp_pewnet(net);

	in->timeout = nf_ct_icmp_timeout;
}

const stwuct nf_conntwack_w4pwoto nf_conntwack_w4pwoto_icmp =
{
	.w4pwoto		= IPPWOTO_ICMP,
#if IS_ENABWED(CONFIG_NF_CT_NETWINK)
	.tupwe_to_nwattw	= icmp_tupwe_to_nwattw,
	.nwattw_tupwe_size	= icmp_nwattw_tupwe_size,
	.nwattw_to_tupwe	= icmp_nwattw_to_tupwe,
	.nwa_powicy		= icmp_nwa_powicy,
#endif
#ifdef CONFIG_NF_CONNTWACK_TIMEOUT
	.ctnw_timeout		= {
		.nwattw_to_obj	= icmp_timeout_nwattw_to_obj,
		.obj_to_nwattw	= icmp_timeout_obj_to_nwattw,
		.nwattw_max	= CTA_TIMEOUT_ICMP_MAX,
		.obj_size	= sizeof(unsigned int),
		.nwa_powicy	= icmp_timeout_nwa_powicy,
	},
#endif /* CONFIG_NF_CONNTWACK_TIMEOUT */
};
