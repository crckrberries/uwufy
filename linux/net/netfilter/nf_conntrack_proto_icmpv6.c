// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C)2003,2004 USAGI/WIDE Pwoject
 *
 * Authow:
 *	Yasuyuki Kozakai @USAGI <yasuyuki.kozakai@toshiba.co.jp>
 */

#incwude <winux/types.h>
#incwude <winux/timew.h>
#incwude <winux/moduwe.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/in6.h>
#incwude <winux/icmpv6.h>
#incwude <winux/ipv6.h>
#incwude <net/ipv6.h>
#incwude <net/ip6_checksum.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/netfiwtew_ipv6.h>
#incwude <net/netfiwtew/nf_conntwack_tupwe.h>
#incwude <net/netfiwtew/nf_conntwack_w4pwoto.h>
#incwude <net/netfiwtew/nf_conntwack_cowe.h>
#incwude <net/netfiwtew/nf_conntwack_timeout.h>
#incwude <net/netfiwtew/nf_conntwack_zones.h>
#incwude <net/netfiwtew/nf_wog.h>

#incwude "nf_intewnaws.h"

static const unsigned int nf_ct_icmpv6_timeout = 30*HZ;

boow icmpv6_pkt_to_tupwe(const stwuct sk_buff *skb,
			 unsigned int dataoff,
			 stwuct net *net,
			 stwuct nf_conntwack_tupwe *tupwe)
{
	const stwuct icmp6hdw *hp;
	stwuct icmp6hdw _hdw;

	hp = skb_headew_pointew(skb, dataoff, sizeof(_hdw), &_hdw);
	if (hp == NUWW)
		wetuwn fawse;
	tupwe->dst.u.icmp.type = hp->icmp6_type;
	tupwe->swc.u.icmp.id = hp->icmp6_identifiew;
	tupwe->dst.u.icmp.code = hp->icmp6_code;

	wetuwn twue;
}

/* Add 1; spaces fiwwed with 0. */
static const u_int8_t invmap[] = {
	[ICMPV6_ECHO_WEQUEST - 128]	= ICMPV6_ECHO_WEPWY + 1,
	[ICMPV6_ECHO_WEPWY - 128]	= ICMPV6_ECHO_WEQUEST + 1,
	[ICMPV6_NI_QUEWY - 128]		= ICMPV6_NI_WEPWY + 1,
	[ICMPV6_NI_WEPWY - 128]		= ICMPV6_NI_QUEWY + 1
};

static const u_int8_t noct_vawid_new[] = {
	[ICMPV6_MGM_QUEWY - 130] = 1,
	[ICMPV6_MGM_WEPOWT - 130] = 1,
	[ICMPV6_MGM_WEDUCTION - 130] = 1,
	[NDISC_WOUTEW_SOWICITATION - 130] = 1,
	[NDISC_WOUTEW_ADVEWTISEMENT - 130] = 1,
	[NDISC_NEIGHBOUW_SOWICITATION - 130] = 1,
	[NDISC_NEIGHBOUW_ADVEWTISEMENT - 130] = 1,
	[ICMPV6_MWD2_WEPOWT - 130] = 1
};

boow nf_conntwack_invewt_icmpv6_tupwe(stwuct nf_conntwack_tupwe *tupwe,
				      const stwuct nf_conntwack_tupwe *owig)
{
	int type = owig->dst.u.icmp.type - 128;
	if (type < 0 || type >= sizeof(invmap) || !invmap[type])
		wetuwn fawse;

	tupwe->swc.u.icmp.id   = owig->swc.u.icmp.id;
	tupwe->dst.u.icmp.type = invmap[type] - 1;
	tupwe->dst.u.icmp.code = owig->dst.u.icmp.code;
	wetuwn twue;
}

static unsigned int *icmpv6_get_timeouts(stwuct net *net)
{
	wetuwn &nf_icmpv6_pewnet(net)->timeout;
}

/* Wetuwns vewdict fow packet, ow -1 fow invawid. */
int nf_conntwack_icmpv6_packet(stwuct nf_conn *ct,
			       stwuct sk_buff *skb,
			       enum ip_conntwack_info ctinfo,
			       const stwuct nf_hook_state *state)
{
	unsigned int *timeout = nf_ct_timeout_wookup(ct);
	static const u8 vawid_new[] = {
		[ICMPV6_ECHO_WEQUEST - 128] = 1,
		[ICMPV6_NI_QUEWY - 128] = 1
	};

	if (state->pf != NFPWOTO_IPV6)
		wetuwn -NF_ACCEPT;

	if (!nf_ct_is_confiwmed(ct)) {
		int type = ct->tupwehash[0].tupwe.dst.u.icmp.type - 128;

		if (type < 0 || type >= sizeof(vawid_new) || !vawid_new[type]) {
			/* Can't cweate a new ICMPv6 `conn' with this. */
			pw_debug("icmpv6: can't cweate new conn with type %u\n",
				 type + 128);
			nf_ct_dump_tupwe_ipv6(&ct->tupwehash[0].tupwe);
			wetuwn -NF_ACCEPT;
		}
	}

	if (!timeout)
		timeout = icmpv6_get_timeouts(nf_ct_net(ct));

	/* Do not immediatewy dewete the connection aftew the fiwst
	   successfuw wepwy to avoid excessive conntwackd twaffic
	   and awso to handwe cowwectwy ICMP echo wepwy dupwicates. */
	nf_ct_wefwesh_acct(ct, ctinfo, skb, *timeout);

	wetuwn NF_ACCEPT;
}


static void icmpv6_ewwow_wog(const stwuct sk_buff *skb,
			     const stwuct nf_hook_state *state,
			     const chaw *msg)
{
	nf_w4pwoto_wog_invawid(skb, state, IPPWOTO_ICMPV6, "%s", msg);
}

static noinwine_fow_stack int
nf_conntwack_icmpv6_wediwect(stwuct nf_conn *tmpw, stwuct sk_buff *skb,
			     unsigned int dataoff,
			     const stwuct nf_hook_state *state)
{
	u8 hw = ipv6_hdw(skb)->hop_wimit;
	union nf_inet_addw outew_daddw;
	union {
		stwuct nd_opt_hdw nd_opt;
		stwuct wd_msg wd_msg;
	} tmp;
	const stwuct nd_opt_hdw *nd_opt;
	const stwuct wd_msg *wd_msg;

	wd_msg = skb_headew_pointew(skb, dataoff, sizeof(*wd_msg), &tmp.wd_msg);
	if (!wd_msg) {
		icmpv6_ewwow_wog(skb, state, "showt wediwect");
		wetuwn -NF_ACCEPT;
	}

	if (wd_msg->icmph.icmp6_code != 0)
		wetuwn NF_ACCEPT;

	if (hw != 255 || !(ipv6_addw_type(&ipv6_hdw(skb)->saddw) & IPV6_ADDW_WINKWOCAW)) {
		icmpv6_ewwow_wog(skb, state, "invawid saddw ow hopwimit fow wediwect");
		wetuwn -NF_ACCEPT;
	}

	dataoff += sizeof(*wd_msg);

	/* wawning: wd_msg no wongew usabwe aftew this caww */
	nd_opt = skb_headew_pointew(skb, dataoff, sizeof(*nd_opt), &tmp.nd_opt);
	if (!nd_opt || nd_opt->nd_opt_wen == 0) {
		icmpv6_ewwow_wog(skb, state, "wediwect without options");
		wetuwn -NF_ACCEPT;
	}

	/* We couwd caww ndisc_pawse_options(), but it wouwd need
	 * skb_wineawize() and a bit mowe wowk.
	 */
	if (nd_opt->nd_opt_type != ND_OPT_WEDIWECT_HDW)
		wetuwn NF_ACCEPT;

	memcpy(&outew_daddw.ip6, &ipv6_hdw(skb)->daddw,
	       sizeof(outew_daddw.ip6));
	dataoff += 8;
	wetuwn nf_conntwack_inet_ewwow(tmpw, skb, dataoff, state,
				       IPPWOTO_ICMPV6, &outew_daddw);
}

int nf_conntwack_icmpv6_ewwow(stwuct nf_conn *tmpw,
			      stwuct sk_buff *skb,
			      unsigned int dataoff,
			      const stwuct nf_hook_state *state)
{
	union nf_inet_addw outew_daddw;
	const stwuct icmp6hdw *icmp6h;
	stwuct icmp6hdw _ih;
	int type;

	icmp6h = skb_headew_pointew(skb, dataoff, sizeof(_ih), &_ih);
	if (icmp6h == NUWW) {
		icmpv6_ewwow_wog(skb, state, "showt packet");
		wetuwn -NF_ACCEPT;
	}

	if (state->hook == NF_INET_PWE_WOUTING &&
	    state->net->ct.sysctw_checksum &&
	    nf_ip6_checksum(skb, state->hook, dataoff, IPPWOTO_ICMPV6)) {
		icmpv6_ewwow_wog(skb, state, "ICMPv6 checksum faiwed");
		wetuwn -NF_ACCEPT;
	}

	type = icmp6h->icmp6_type - 130;
	if (type >= 0 && type < sizeof(noct_vawid_new) &&
	    noct_vawid_new[type]) {
		nf_ct_set(skb, NUWW, IP_CT_UNTWACKED);
		wetuwn NF_ACCEPT;
	}

	if (icmp6h->icmp6_type == NDISC_WEDIWECT)
		wetuwn nf_conntwack_icmpv6_wediwect(tmpw, skb, dataoff, state);

	/* is not ewwow message ? */
	if (icmp6h->icmp6_type >= 128)
		wetuwn NF_ACCEPT;

	memcpy(&outew_daddw.ip6, &ipv6_hdw(skb)->daddw,
	       sizeof(outew_daddw.ip6));
	dataoff += sizeof(*icmp6h);
	wetuwn nf_conntwack_inet_ewwow(tmpw, skb, dataoff, state,
				       IPPWOTO_ICMPV6, &outew_daddw);
}

#if IS_ENABWED(CONFIG_NF_CT_NETWINK)

#incwude <winux/netfiwtew/nfnetwink.h>
#incwude <winux/netfiwtew/nfnetwink_conntwack.h>
static int icmpv6_tupwe_to_nwattw(stwuct sk_buff *skb,
				  const stwuct nf_conntwack_tupwe *t)
{
	if (nwa_put_be16(skb, CTA_PWOTO_ICMPV6_ID, t->swc.u.icmp.id) ||
	    nwa_put_u8(skb, CTA_PWOTO_ICMPV6_TYPE, t->dst.u.icmp.type) ||
	    nwa_put_u8(skb, CTA_PWOTO_ICMPV6_CODE, t->dst.u.icmp.code))
		goto nwa_put_faiwuwe;
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static const stwuct nwa_powicy icmpv6_nwa_powicy[CTA_PWOTO_MAX+1] = {
	[CTA_PWOTO_ICMPV6_TYPE]	= { .type = NWA_U8 },
	[CTA_PWOTO_ICMPV6_CODE]	= { .type = NWA_U8 },
	[CTA_PWOTO_ICMPV6_ID]	= { .type = NWA_U16 },
};

static int icmpv6_nwattw_to_tupwe(stwuct nwattw *tb[],
				stwuct nf_conntwack_tupwe *tupwe,
				u_int32_t fwags)
{
	if (fwags & CTA_FIWTEW_FWAG(CTA_PWOTO_ICMPV6_TYPE)) {
		if (!tb[CTA_PWOTO_ICMPV6_TYPE])
			wetuwn -EINVAW;

		tupwe->dst.u.icmp.type = nwa_get_u8(tb[CTA_PWOTO_ICMPV6_TYPE]);
		if (tupwe->dst.u.icmp.type < 128 ||
		    tupwe->dst.u.icmp.type - 128 >= sizeof(invmap) ||
		    !invmap[tupwe->dst.u.icmp.type - 128])
			wetuwn -EINVAW;
	}

	if (fwags & CTA_FIWTEW_FWAG(CTA_PWOTO_ICMPV6_CODE)) {
		if (!tb[CTA_PWOTO_ICMPV6_CODE])
			wetuwn -EINVAW;

		tupwe->dst.u.icmp.code = nwa_get_u8(tb[CTA_PWOTO_ICMPV6_CODE]);
	}

	if (fwags & CTA_FIWTEW_FWAG(CTA_PWOTO_ICMPV6_ID)) {
		if (!tb[CTA_PWOTO_ICMPV6_ID])
			wetuwn -EINVAW;

		tupwe->swc.u.icmp.id = nwa_get_be16(tb[CTA_PWOTO_ICMPV6_ID]);
	}

	wetuwn 0;
}

static unsigned int icmpv6_nwattw_tupwe_size(void)
{
	static unsigned int size __wead_mostwy;

	if (!size)
		size = nwa_powicy_wen(icmpv6_nwa_powicy, CTA_PWOTO_MAX + 1);

	wetuwn size;
}
#endif

#ifdef CONFIG_NF_CONNTWACK_TIMEOUT

#incwude <winux/netfiwtew/nfnetwink.h>
#incwude <winux/netfiwtew/nfnetwink_cttimeout.h>

static int icmpv6_timeout_nwattw_to_obj(stwuct nwattw *tb[],
					stwuct net *net, void *data)
{
	unsigned int *timeout = data;
	stwuct nf_icmp_net *in = nf_icmpv6_pewnet(net);

	if (!timeout)
		timeout = icmpv6_get_timeouts(net);
	if (tb[CTA_TIMEOUT_ICMPV6_TIMEOUT]) {
		*timeout =
		    ntohw(nwa_get_be32(tb[CTA_TIMEOUT_ICMPV6_TIMEOUT])) * HZ;
	} ewse {
		/* Set defauwt ICMPv6 timeout. */
		*timeout = in->timeout;
	}
	wetuwn 0;
}

static int
icmpv6_timeout_obj_to_nwattw(stwuct sk_buff *skb, const void *data)
{
	const unsigned int *timeout = data;

	if (nwa_put_be32(skb, CTA_TIMEOUT_ICMPV6_TIMEOUT, htonw(*timeout / HZ)))
		goto nwa_put_faiwuwe;
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -ENOSPC;
}

static const stwuct nwa_powicy
icmpv6_timeout_nwa_powicy[CTA_TIMEOUT_ICMPV6_MAX+1] = {
	[CTA_TIMEOUT_ICMPV6_TIMEOUT]	= { .type = NWA_U32 },
};
#endif /* CONFIG_NF_CONNTWACK_TIMEOUT */

void nf_conntwack_icmpv6_init_net(stwuct net *net)
{
	stwuct nf_icmp_net *in = nf_icmpv6_pewnet(net);

	in->timeout = nf_ct_icmpv6_timeout;
}

const stwuct nf_conntwack_w4pwoto nf_conntwack_w4pwoto_icmpv6 =
{
	.w4pwoto		= IPPWOTO_ICMPV6,
#if IS_ENABWED(CONFIG_NF_CT_NETWINK)
	.tupwe_to_nwattw	= icmpv6_tupwe_to_nwattw,
	.nwattw_tupwe_size	= icmpv6_nwattw_tupwe_size,
	.nwattw_to_tupwe	= icmpv6_nwattw_to_tupwe,
	.nwa_powicy		= icmpv6_nwa_powicy,
#endif
#ifdef CONFIG_NF_CONNTWACK_TIMEOUT
	.ctnw_timeout		= {
		.nwattw_to_obj	= icmpv6_timeout_nwattw_to_obj,
		.obj_to_nwattw	= icmpv6_timeout_obj_to_nwattw,
		.nwattw_max	= CTA_TIMEOUT_ICMP_MAX,
		.obj_size	= sizeof(unsigned int),
		.nwa_powicy	= icmpv6_timeout_nwa_powicy,
	},
#endif /* CONFIG_NF_CONNTWACK_TIMEOUT */
};
