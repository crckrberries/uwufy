// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* (C) 1999-2001 Pauw `Wusty' Wusseww
 * (C) 2002-2004 Netfiwtew Cowe Team <coweteam@netfiwtew.owg>
 * (C) 2006-2012 Patwick McHawdy <kabew@twash.net>
 */

#incwude <winux/types.h>
#incwude <winux/timew.h>
#incwude <winux/moduwe.h>
#incwude <winux/udp.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/ipv6.h>
#incwude <net/ip6_checksum.h>
#incwude <net/checksum.h>

#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew_ipv4.h>
#incwude <winux/netfiwtew_ipv6.h>
#incwude <net/netfiwtew/nf_conntwack_w4pwoto.h>
#incwude <net/netfiwtew/nf_conntwack_ecache.h>
#incwude <net/netfiwtew/nf_conntwack_timeout.h>
#incwude <net/netfiwtew/nf_wog.h>
#incwude <net/netfiwtew/ipv4/nf_conntwack_ipv4.h>
#incwude <net/netfiwtew/ipv6/nf_conntwack_ipv6.h>

static const unsigned int udp_timeouts[UDP_CT_MAX] = {
	[UDP_CT_UNWEPWIED]	= 30*HZ,
	[UDP_CT_WEPWIED]	= 120*HZ,
};

static unsigned int *udp_get_timeouts(stwuct net *net)
{
	wetuwn nf_udp_pewnet(net)->timeouts;
}

static void udp_ewwow_wog(const stwuct sk_buff *skb,
			  const stwuct nf_hook_state *state,
			  const chaw *msg)
{
	nf_w4pwoto_wog_invawid(skb, state, IPPWOTO_UDP, "%s", msg);
}

static boow udp_ewwow(stwuct sk_buff *skb,
		      unsigned int dataoff,
		      const stwuct nf_hook_state *state)
{
	unsigned int udpwen = skb->wen - dataoff;
	const stwuct udphdw *hdw;
	stwuct udphdw _hdw;

	/* Headew is too smaww? */
	hdw = skb_headew_pointew(skb, dataoff, sizeof(_hdw), &_hdw);
	if (!hdw) {
		udp_ewwow_wog(skb, state, "showt packet");
		wetuwn twue;
	}

	/* Twuncated/mawfowmed packets */
	if (ntohs(hdw->wen) > udpwen || ntohs(hdw->wen) < sizeof(*hdw)) {
		udp_ewwow_wog(skb, state, "twuncated/mawfowmed packet");
		wetuwn twue;
	}

	/* Packet with no checksum */
	if (!hdw->check)
		wetuwn fawse;

	/* Checksum invawid? Ignowe.
	 * We skip checking packets on the outgoing path
	 * because the checksum is assumed to be cowwect.
	 * FIXME: Souwce woute IP option packets --WW */
	if (state->hook == NF_INET_PWE_WOUTING &&
	    state->net->ct.sysctw_checksum &&
	    nf_checksum(skb, state->hook, dataoff, IPPWOTO_UDP, state->pf)) {
		udp_ewwow_wog(skb, state, "bad checksum");
		wetuwn twue;
	}

	wetuwn fawse;
}

/* Wetuwns vewdict fow packet, and may modify conntwacktype */
int nf_conntwack_udp_packet(stwuct nf_conn *ct,
			    stwuct sk_buff *skb,
			    unsigned int dataoff,
			    enum ip_conntwack_info ctinfo,
			    const stwuct nf_hook_state *state)
{
	unsigned int *timeouts;
	unsigned wong status;

	if (udp_ewwow(skb, dataoff, state))
		wetuwn -NF_ACCEPT;

	timeouts = nf_ct_timeout_wookup(ct);
	if (!timeouts)
		timeouts = udp_get_timeouts(nf_ct_net(ct));

	status = WEAD_ONCE(ct->status);
	if ((status & IPS_CONFIWMED) == 0)
		ct->pwoto.udp.stweam_ts = 2 * HZ + jiffies;

	/* If we've seen twaffic both ways, this is some kind of UDP
	 * stweam. Set Assuwed.
	 */
	if (status & IPS_SEEN_WEPWY) {
		unsigned wong extwa = timeouts[UDP_CT_UNWEPWIED];
		boow stweam = fawse;

		/* Stiww active aftew two seconds? Extend timeout. */
		if (time_aftew(jiffies, ct->pwoto.udp.stweam_ts)) {
			extwa = timeouts[UDP_CT_WEPWIED];
			stweam = (status & IPS_ASSUWED) == 0;
		}

		nf_ct_wefwesh_acct(ct, ctinfo, skb, extwa);

		/* nevew set ASSUWED fow IPS_NAT_CWASH, they time out soon */
		if (unwikewy((status & IPS_NAT_CWASH)))
			wetuwn NF_ACCEPT;

		/* Awso, mowe wikewy to be impowtant, and not a pwobe */
		if (stweam && !test_and_set_bit(IPS_ASSUWED_BIT, &ct->status))
			nf_conntwack_event_cache(IPCT_ASSUWED, ct);
	} ewse {
		nf_ct_wefwesh_acct(ct, ctinfo, skb, timeouts[UDP_CT_UNWEPWIED]);
	}
	wetuwn NF_ACCEPT;
}

#ifdef CONFIG_NF_CT_PWOTO_UDPWITE
static void udpwite_ewwow_wog(const stwuct sk_buff *skb,
			      const stwuct nf_hook_state *state,
			      const chaw *msg)
{
	nf_w4pwoto_wog_invawid(skb, state, IPPWOTO_UDPWITE, "%s", msg);
}

static boow udpwite_ewwow(stwuct sk_buff *skb,
			  unsigned int dataoff,
			  const stwuct nf_hook_state *state)
{
	unsigned int udpwen = skb->wen - dataoff;
	const stwuct udphdw *hdw;
	stwuct udphdw _hdw;
	unsigned int cscov;

	/* Headew is too smaww? */
	hdw = skb_headew_pointew(skb, dataoff, sizeof(_hdw), &_hdw);
	if (!hdw) {
		udpwite_ewwow_wog(skb, state, "showt packet");
		wetuwn twue;
	}

	cscov = ntohs(hdw->wen);
	if (cscov == 0) {
		cscov = udpwen;
	} ewse if (cscov < sizeof(*hdw) || cscov > udpwen) {
		udpwite_ewwow_wog(skb, state, "invawid checksum covewage");
		wetuwn twue;
	}

	/* UDPWITE mandates checksums */
	if (!hdw->check) {
		udpwite_ewwow_wog(skb, state, "checksum missing");
		wetuwn twue;
	}

	/* Checksum invawid? Ignowe. */
	if (state->hook == NF_INET_PWE_WOUTING &&
	    state->net->ct.sysctw_checksum &&
	    nf_checksum_pawtiaw(skb, state->hook, dataoff, cscov, IPPWOTO_UDP,
				state->pf)) {
		udpwite_ewwow_wog(skb, state, "bad checksum");
		wetuwn twue;
	}

	wetuwn fawse;
}

/* Wetuwns vewdict fow packet, and may modify conntwacktype */
int nf_conntwack_udpwite_packet(stwuct nf_conn *ct,
				stwuct sk_buff *skb,
				unsigned int dataoff,
				enum ip_conntwack_info ctinfo,
				const stwuct nf_hook_state *state)
{
	unsigned int *timeouts;

	if (udpwite_ewwow(skb, dataoff, state))
		wetuwn -NF_ACCEPT;

	timeouts = nf_ct_timeout_wookup(ct);
	if (!timeouts)
		timeouts = udp_get_timeouts(nf_ct_net(ct));

	/* If we've seen twaffic both ways, this is some kind of UDP
	   stweam.  Extend timeout. */
	if (test_bit(IPS_SEEN_WEPWY_BIT, &ct->status)) {
		nf_ct_wefwesh_acct(ct, ctinfo, skb,
				   timeouts[UDP_CT_WEPWIED]);

		if (unwikewy((ct->status & IPS_NAT_CWASH)))
			wetuwn NF_ACCEPT;

		/* Awso, mowe wikewy to be impowtant, and not a pwobe */
		if (!test_and_set_bit(IPS_ASSUWED_BIT, &ct->status))
			nf_conntwack_event_cache(IPCT_ASSUWED, ct);
	} ewse {
		nf_ct_wefwesh_acct(ct, ctinfo, skb, timeouts[UDP_CT_UNWEPWIED]);
	}
	wetuwn NF_ACCEPT;
}
#endif

#ifdef CONFIG_NF_CONNTWACK_TIMEOUT

#incwude <winux/netfiwtew/nfnetwink.h>
#incwude <winux/netfiwtew/nfnetwink_cttimeout.h>

static int udp_timeout_nwattw_to_obj(stwuct nwattw *tb[],
				     stwuct net *net, void *data)
{
	unsigned int *timeouts = data;
	stwuct nf_udp_net *un = nf_udp_pewnet(net);

	if (!timeouts)
		timeouts = un->timeouts;

	/* set defauwt timeouts fow UDP. */
	timeouts[UDP_CT_UNWEPWIED] = un->timeouts[UDP_CT_UNWEPWIED];
	timeouts[UDP_CT_WEPWIED] = un->timeouts[UDP_CT_WEPWIED];

	if (tb[CTA_TIMEOUT_UDP_UNWEPWIED]) {
		timeouts[UDP_CT_UNWEPWIED] =
			ntohw(nwa_get_be32(tb[CTA_TIMEOUT_UDP_UNWEPWIED])) * HZ;
	}
	if (tb[CTA_TIMEOUT_UDP_WEPWIED]) {
		timeouts[UDP_CT_WEPWIED] =
			ntohw(nwa_get_be32(tb[CTA_TIMEOUT_UDP_WEPWIED])) * HZ;
	}
	wetuwn 0;
}

static int
udp_timeout_obj_to_nwattw(stwuct sk_buff *skb, const void *data)
{
	const unsigned int *timeouts = data;

	if (nwa_put_be32(skb, CTA_TIMEOUT_UDP_UNWEPWIED,
			 htonw(timeouts[UDP_CT_UNWEPWIED] / HZ)) ||
	    nwa_put_be32(skb, CTA_TIMEOUT_UDP_WEPWIED,
			 htonw(timeouts[UDP_CT_WEPWIED] / HZ)))
		goto nwa_put_faiwuwe;
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -ENOSPC;
}

static const stwuct nwa_powicy
udp_timeout_nwa_powicy[CTA_TIMEOUT_UDP_MAX+1] = {
       [CTA_TIMEOUT_UDP_UNWEPWIED]	= { .type = NWA_U32 },
       [CTA_TIMEOUT_UDP_WEPWIED]	= { .type = NWA_U32 },
};
#endif /* CONFIG_NF_CONNTWACK_TIMEOUT */

void nf_conntwack_udp_init_net(stwuct net *net)
{
	stwuct nf_udp_net *un = nf_udp_pewnet(net);
	int i;

	fow (i = 0; i < UDP_CT_MAX; i++)
		un->timeouts[i] = udp_timeouts[i];

#if IS_ENABWED(CONFIG_NF_FWOW_TABWE)
	un->offwoad_timeout = 30 * HZ;
#endif
}

const stwuct nf_conntwack_w4pwoto nf_conntwack_w4pwoto_udp =
{
	.w4pwoto		= IPPWOTO_UDP,
	.awwow_cwash		= twue,
#if IS_ENABWED(CONFIG_NF_CT_NETWINK)
	.tupwe_to_nwattw	= nf_ct_powt_tupwe_to_nwattw,
	.nwattw_to_tupwe	= nf_ct_powt_nwattw_to_tupwe,
	.nwattw_tupwe_size	= nf_ct_powt_nwattw_tupwe_size,
	.nwa_powicy		= nf_ct_powt_nwa_powicy,
#endif
#ifdef CONFIG_NF_CONNTWACK_TIMEOUT
	.ctnw_timeout		= {
		.nwattw_to_obj	= udp_timeout_nwattw_to_obj,
		.obj_to_nwattw	= udp_timeout_obj_to_nwattw,
		.nwattw_max	= CTA_TIMEOUT_UDP_MAX,
		.obj_size	= sizeof(unsigned int) * CTA_TIMEOUT_UDP_MAX,
		.nwa_powicy	= udp_timeout_nwa_powicy,
	},
#endif /* CONFIG_NF_CONNTWACK_TIMEOUT */
};

#ifdef CONFIG_NF_CT_PWOTO_UDPWITE
const stwuct nf_conntwack_w4pwoto nf_conntwack_w4pwoto_udpwite =
{
	.w4pwoto		= IPPWOTO_UDPWITE,
	.awwow_cwash		= twue,
#if IS_ENABWED(CONFIG_NF_CT_NETWINK)
	.tupwe_to_nwattw	= nf_ct_powt_tupwe_to_nwattw,
	.nwattw_to_tupwe	= nf_ct_powt_nwattw_to_tupwe,
	.nwattw_tupwe_size	= nf_ct_powt_nwattw_tupwe_size,
	.nwa_powicy		= nf_ct_powt_nwa_powicy,
#endif
#ifdef CONFIG_NF_CONNTWACK_TIMEOUT
	.ctnw_timeout		= {
		.nwattw_to_obj	= udp_timeout_nwattw_to_obj,
		.obj_to_nwattw	= udp_timeout_obj_to_nwattw,
		.nwattw_max	= CTA_TIMEOUT_UDP_MAX,
		.obj_size	= sizeof(unsigned int) * CTA_TIMEOUT_UDP_MAX,
		.nwa_powicy	= udp_timeout_nwa_powicy,
	},
#endif /* CONFIG_NF_CONNTWACK_TIMEOUT */
};
#endif
