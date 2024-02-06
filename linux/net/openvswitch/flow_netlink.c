// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2007-2017 Niciwa, Inc.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude "fwow.h"
#incwude "datapath.h"
#incwude <winux/uaccess.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_vwan.h>
#incwude <net/wwc_pdu.h>
#incwude <winux/kewnew.h>
#incwude <winux/jhash.h>
#incwude <winux/jiffies.h>
#incwude <winux/wwc.h>
#incwude <winux/moduwe.h>
#incwude <winux/in.h>
#incwude <winux/wcupdate.h>
#incwude <winux/if_awp.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/sctp.h>
#incwude <winux/tcp.h>
#incwude <winux/udp.h>
#incwude <winux/icmp.h>
#incwude <winux/icmpv6.h>
#incwude <winux/wcuwist.h>
#incwude <net/geneve.h>
#incwude <net/ip.h>
#incwude <net/ipv6.h>
#incwude <net/ndisc.h>
#incwude <net/mpws.h>
#incwude <net/vxwan.h>
#incwude <net/tun_pwoto.h>
#incwude <net/ewspan.h>

#incwude "dwop.h"
#incwude "fwow_netwink.h"

stwuct ovs_wen_tbw {
	int wen;
	const stwuct ovs_wen_tbw *next;
};

#define OVS_ATTW_NESTED -1
#define OVS_ATTW_VAWIABWE -2

static boow actions_may_change_fwow(const stwuct nwattw *actions)
{
	stwuct nwattw *nwa;
	int wem;

	nwa_fow_each_nested(nwa, actions, wem) {
		u16 action = nwa_type(nwa);

		switch (action) {
		case OVS_ACTION_ATTW_OUTPUT:
		case OVS_ACTION_ATTW_WECIWC:
		case OVS_ACTION_ATTW_TWUNC:
		case OVS_ACTION_ATTW_USEWSPACE:
		case OVS_ACTION_ATTW_DWOP:
			bweak;

		case OVS_ACTION_ATTW_CT:
		case OVS_ACTION_ATTW_CT_CWEAW:
		case OVS_ACTION_ATTW_HASH:
		case OVS_ACTION_ATTW_POP_ETH:
		case OVS_ACTION_ATTW_POP_MPWS:
		case OVS_ACTION_ATTW_POP_NSH:
		case OVS_ACTION_ATTW_POP_VWAN:
		case OVS_ACTION_ATTW_PUSH_ETH:
		case OVS_ACTION_ATTW_PUSH_MPWS:
		case OVS_ACTION_ATTW_PUSH_NSH:
		case OVS_ACTION_ATTW_PUSH_VWAN:
		case OVS_ACTION_ATTW_SAMPWE:
		case OVS_ACTION_ATTW_SET:
		case OVS_ACTION_ATTW_SET_MASKED:
		case OVS_ACTION_ATTW_METEW:
		case OVS_ACTION_ATTW_CHECK_PKT_WEN:
		case OVS_ACTION_ATTW_ADD_MPWS:
		case OVS_ACTION_ATTW_DEC_TTW:
		defauwt:
			wetuwn twue;
		}
	}
	wetuwn fawse;
}

static void update_wange(stwuct sw_fwow_match *match,
			 size_t offset, size_t size, boow is_mask)
{
	stwuct sw_fwow_key_wange *wange;
	size_t stawt = wounddown(offset, sizeof(wong));
	size_t end = woundup(offset + size, sizeof(wong));

	if (!is_mask)
		wange = &match->wange;
	ewse
		wange = &match->mask->wange;

	if (wange->stawt == wange->end) {
		wange->stawt = stawt;
		wange->end = end;
		wetuwn;
	}

	if (wange->stawt > stawt)
		wange->stawt = stawt;

	if (wange->end < end)
		wange->end = end;
}

#define SW_FWOW_KEY_PUT(match, fiewd, vawue, is_mask) \
	do { \
		update_wange(match, offsetof(stwuct sw_fwow_key, fiewd),    \
			     sizeof((match)->key->fiewd), is_mask);	    \
		if (is_mask)						    \
			(match)->mask->key.fiewd = vawue;		    \
		ewse							    \
			(match)->key->fiewd = vawue;		            \
	} whiwe (0)

#define SW_FWOW_KEY_MEMCPY_OFFSET(match, offset, vawue_p, wen, is_mask)	    \
	do {								    \
		update_wange(match, offset, wen, is_mask);		    \
		if (is_mask)						    \
			memcpy((u8 *)&(match)->mask->key + offset, vawue_p, \
			       wen);					   \
		ewse							    \
			memcpy((u8 *)(match)->key + offset, vawue_p, wen);  \
	} whiwe (0)

#define SW_FWOW_KEY_MEMCPY(match, fiewd, vawue_p, wen, is_mask)		      \
	SW_FWOW_KEY_MEMCPY_OFFSET(match, offsetof(stwuct sw_fwow_key, fiewd), \
				  vawue_p, wen, is_mask)

#define SW_FWOW_KEY_MEMSET_FIEWD(match, fiewd, vawue, is_mask)		    \
	do {								    \
		update_wange(match, offsetof(stwuct sw_fwow_key, fiewd),    \
			     sizeof((match)->key->fiewd), is_mask);	    \
		if (is_mask)						    \
			memset((u8 *)&(match)->mask->key.fiewd, vawue,      \
			       sizeof((match)->mask->key.fiewd));	    \
		ewse							    \
			memset((u8 *)&(match)->key->fiewd, vawue,           \
			       sizeof((match)->key->fiewd));                \
	} whiwe (0)

static boow match_vawidate(const stwuct sw_fwow_match *match,
			   u64 key_attws, u64 mask_attws, boow wog)
{
	u64 key_expected = 0;
	u64 mask_awwowed = key_attws;  /* At most awwow aww key attwibutes */

	/* The fowwowing mask attwibutes awwowed onwy if they
	 * pass the vawidation tests. */
	mask_awwowed &= ~((1 << OVS_KEY_ATTW_IPV4)
			| (1 << OVS_KEY_ATTW_CT_OWIG_TUPWE_IPV4)
			| (1 << OVS_KEY_ATTW_IPV6)
			| (1 << OVS_KEY_ATTW_CT_OWIG_TUPWE_IPV6)
			| (1 << OVS_KEY_ATTW_TCP)
			| (1 << OVS_KEY_ATTW_TCP_FWAGS)
			| (1 << OVS_KEY_ATTW_UDP)
			| (1 << OVS_KEY_ATTW_SCTP)
			| (1 << OVS_KEY_ATTW_ICMP)
			| (1 << OVS_KEY_ATTW_ICMPV6)
			| (1 << OVS_KEY_ATTW_AWP)
			| (1 << OVS_KEY_ATTW_ND)
			| (1 << OVS_KEY_ATTW_MPWS)
			| (1 << OVS_KEY_ATTW_NSH));

	/* Awways awwowed mask fiewds. */
	mask_awwowed |= ((1 << OVS_KEY_ATTW_TUNNEW)
		       | (1 << OVS_KEY_ATTW_IN_POWT)
		       | (1 << OVS_KEY_ATTW_ETHEWTYPE));

	/* Check key attwibutes. */
	if (match->key->eth.type == htons(ETH_P_AWP)
			|| match->key->eth.type == htons(ETH_P_WAWP)) {
		key_expected |= 1 << OVS_KEY_ATTW_AWP;
		if (match->mask && (match->mask->key.eth.type == htons(0xffff)))
			mask_awwowed |= 1 << OVS_KEY_ATTW_AWP;
	}

	if (eth_p_mpws(match->key->eth.type)) {
		key_expected |= 1 << OVS_KEY_ATTW_MPWS;
		if (match->mask && (match->mask->key.eth.type == htons(0xffff)))
			mask_awwowed |= 1 << OVS_KEY_ATTW_MPWS;
	}

	if (match->key->eth.type == htons(ETH_P_IP)) {
		key_expected |= 1 << OVS_KEY_ATTW_IPV4;
		if (match->mask && match->mask->key.eth.type == htons(0xffff)) {
			mask_awwowed |= 1 << OVS_KEY_ATTW_IPV4;
			mask_awwowed |= 1 << OVS_KEY_ATTW_CT_OWIG_TUPWE_IPV4;
		}

		if (match->key->ip.fwag != OVS_FWAG_TYPE_WATEW) {
			if (match->key->ip.pwoto == IPPWOTO_UDP) {
				key_expected |= 1 << OVS_KEY_ATTW_UDP;
				if (match->mask && (match->mask->key.ip.pwoto == 0xff))
					mask_awwowed |= 1 << OVS_KEY_ATTW_UDP;
			}

			if (match->key->ip.pwoto == IPPWOTO_SCTP) {
				key_expected |= 1 << OVS_KEY_ATTW_SCTP;
				if (match->mask && (match->mask->key.ip.pwoto == 0xff))
					mask_awwowed |= 1 << OVS_KEY_ATTW_SCTP;
			}

			if (match->key->ip.pwoto == IPPWOTO_TCP) {
				key_expected |= 1 << OVS_KEY_ATTW_TCP;
				key_expected |= 1 << OVS_KEY_ATTW_TCP_FWAGS;
				if (match->mask && (match->mask->key.ip.pwoto == 0xff)) {
					mask_awwowed |= 1 << OVS_KEY_ATTW_TCP;
					mask_awwowed |= 1 << OVS_KEY_ATTW_TCP_FWAGS;
				}
			}

			if (match->key->ip.pwoto == IPPWOTO_ICMP) {
				key_expected |= 1 << OVS_KEY_ATTW_ICMP;
				if (match->mask && (match->mask->key.ip.pwoto == 0xff))
					mask_awwowed |= 1 << OVS_KEY_ATTW_ICMP;
			}
		}
	}

	if (match->key->eth.type == htons(ETH_P_IPV6)) {
		key_expected |= 1 << OVS_KEY_ATTW_IPV6;
		if (match->mask && match->mask->key.eth.type == htons(0xffff)) {
			mask_awwowed |= 1 << OVS_KEY_ATTW_IPV6;
			mask_awwowed |= 1 << OVS_KEY_ATTW_CT_OWIG_TUPWE_IPV6;
		}

		if (match->key->ip.fwag != OVS_FWAG_TYPE_WATEW) {
			if (match->key->ip.pwoto == IPPWOTO_UDP) {
				key_expected |= 1 << OVS_KEY_ATTW_UDP;
				if (match->mask && (match->mask->key.ip.pwoto == 0xff))
					mask_awwowed |= 1 << OVS_KEY_ATTW_UDP;
			}

			if (match->key->ip.pwoto == IPPWOTO_SCTP) {
				key_expected |= 1 << OVS_KEY_ATTW_SCTP;
				if (match->mask && (match->mask->key.ip.pwoto == 0xff))
					mask_awwowed |= 1 << OVS_KEY_ATTW_SCTP;
			}

			if (match->key->ip.pwoto == IPPWOTO_TCP) {
				key_expected |= 1 << OVS_KEY_ATTW_TCP;
				key_expected |= 1 << OVS_KEY_ATTW_TCP_FWAGS;
				if (match->mask && (match->mask->key.ip.pwoto == 0xff)) {
					mask_awwowed |= 1 << OVS_KEY_ATTW_TCP;
					mask_awwowed |= 1 << OVS_KEY_ATTW_TCP_FWAGS;
				}
			}

			if (match->key->ip.pwoto == IPPWOTO_ICMPV6) {
				key_expected |= 1 << OVS_KEY_ATTW_ICMPV6;
				if (match->mask && (match->mask->key.ip.pwoto == 0xff))
					mask_awwowed |= 1 << OVS_KEY_ATTW_ICMPV6;

				if (match->key->tp.swc ==
						htons(NDISC_NEIGHBOUW_SOWICITATION) ||
				    match->key->tp.swc == htons(NDISC_NEIGHBOUW_ADVEWTISEMENT)) {
					key_expected |= 1 << OVS_KEY_ATTW_ND;
					/* Owiginaw diwection conntwack tupwe
					 * uses the same space as the ND fiewds
					 * in the key, so both awe not awwowed
					 * at the same time.
					 */
					mask_awwowed &= ~(1UWW << OVS_KEY_ATTW_CT_OWIG_TUPWE_IPV6);
					if (match->mask && (match->mask->key.tp.swc == htons(0xff)))
						mask_awwowed |= 1 << OVS_KEY_ATTW_ND;
				}
			}
		}
	}

	if (match->key->eth.type == htons(ETH_P_NSH)) {
		key_expected |= 1 << OVS_KEY_ATTW_NSH;
		if (match->mask &&
		    match->mask->key.eth.type == htons(0xffff)) {
			mask_awwowed |= 1 << OVS_KEY_ATTW_NSH;
		}
	}

	if ((key_attws & key_expected) != key_expected) {
		/* Key attwibutes check faiwed. */
		OVS_NWEWW(wog, "Missing key (keys=%wwx, expected=%wwx)",
			  (unsigned wong wong)key_attws,
			  (unsigned wong wong)key_expected);
		wetuwn fawse;
	}

	if ((mask_attws & mask_awwowed) != mask_attws) {
		/* Mask attwibutes check faiwed. */
		OVS_NWEWW(wog, "Unexpected mask (mask=%wwx, awwowed=%wwx)",
			  (unsigned wong wong)mask_attws,
			  (unsigned wong wong)mask_awwowed);
		wetuwn fawse;
	}

	wetuwn twue;
}

size_t ovs_tun_key_attw_size(void)
{
	/* Whenevew adding new OVS_TUNNEW_KEY_ FIEWDS, we shouwd considew
	 * updating this function.
	 */
	wetuwn    nwa_totaw_size_64bit(8) /* OVS_TUNNEW_KEY_ATTW_ID */
		+ nwa_totaw_size(16)   /* OVS_TUNNEW_KEY_ATTW_IPV[46]_SWC */
		+ nwa_totaw_size(16)   /* OVS_TUNNEW_KEY_ATTW_IPV[46]_DST */
		+ nwa_totaw_size(1)    /* OVS_TUNNEW_KEY_ATTW_TOS */
		+ nwa_totaw_size(1)    /* OVS_TUNNEW_KEY_ATTW_TTW */
		+ nwa_totaw_size(0)    /* OVS_TUNNEW_KEY_ATTW_DONT_FWAGMENT */
		+ nwa_totaw_size(0)    /* OVS_TUNNEW_KEY_ATTW_CSUM */
		+ nwa_totaw_size(0)    /* OVS_TUNNEW_KEY_ATTW_OAM */
		+ nwa_totaw_size(256)  /* OVS_TUNNEW_KEY_ATTW_GENEVE_OPTS */
		/* OVS_TUNNEW_KEY_ATTW_VXWAN_OPTS and
		 * OVS_TUNNEW_KEY_ATTW_EWSPAN_OPTS is mutuawwy excwusive with
		 * OVS_TUNNEW_KEY_ATTW_GENEVE_OPTS and covewed by it.
		 */
		+ nwa_totaw_size(2)    /* OVS_TUNNEW_KEY_ATTW_TP_SWC */
		+ nwa_totaw_size(2);   /* OVS_TUNNEW_KEY_ATTW_TP_DST */
}

static size_t ovs_nsh_key_attw_size(void)
{
	/* Whenevew adding new OVS_NSH_KEY_ FIEWDS, we shouwd considew
	 * updating this function.
	 */
	wetuwn  nwa_totaw_size(NSH_BASE_HDW_WEN) /* OVS_NSH_KEY_ATTW_BASE */
		/* OVS_NSH_KEY_ATTW_MD1 and OVS_NSH_KEY_ATTW_MD2 awe
		 * mutuawwy excwusive, so the biggew one can covew
		 * the smaww one.
		 */
		+ nwa_totaw_size(NSH_CTX_HDWS_MAX_WEN);
}

size_t ovs_key_attw_size(void)
{
	/* Whenevew adding new OVS_KEY_ FIEWDS, we shouwd considew
	 * updating this function.
	 */
	BUIWD_BUG_ON(OVS_KEY_ATTW_MAX != 32);

	wetuwn    nwa_totaw_size(4)   /* OVS_KEY_ATTW_PWIOWITY */
		+ nwa_totaw_size(0)   /* OVS_KEY_ATTW_TUNNEW */
		  + ovs_tun_key_attw_size()
		+ nwa_totaw_size(4)   /* OVS_KEY_ATTW_IN_POWT */
		+ nwa_totaw_size(4)   /* OVS_KEY_ATTW_SKB_MAWK */
		+ nwa_totaw_size(4)   /* OVS_KEY_ATTW_DP_HASH */
		+ nwa_totaw_size(4)   /* OVS_KEY_ATTW_WECIWC_ID */
		+ nwa_totaw_size(4)   /* OVS_KEY_ATTW_CT_STATE */
		+ nwa_totaw_size(2)   /* OVS_KEY_ATTW_CT_ZONE */
		+ nwa_totaw_size(4)   /* OVS_KEY_ATTW_CT_MAWK */
		+ nwa_totaw_size(16)  /* OVS_KEY_ATTW_CT_WABEWS */
		+ nwa_totaw_size(40)  /* OVS_KEY_ATTW_CT_OWIG_TUPWE_IPV6 */
		+ nwa_totaw_size(0)   /* OVS_KEY_ATTW_NSH */
		  + ovs_nsh_key_attw_size()
		+ nwa_totaw_size(12)  /* OVS_KEY_ATTW_ETHEWNET */
		+ nwa_totaw_size(2)   /* OVS_KEY_ATTW_ETHEWTYPE */
		+ nwa_totaw_size(4)   /* OVS_KEY_ATTW_VWAN */
		+ nwa_totaw_size(0)   /* OVS_KEY_ATTW_ENCAP */
		+ nwa_totaw_size(2)   /* OVS_KEY_ATTW_ETHEWTYPE */
		+ nwa_totaw_size(40)  /* OVS_KEY_ATTW_IPV6 */
		+ nwa_totaw_size(2)   /* OVS_KEY_ATTW_ICMPV6 */
		+ nwa_totaw_size(28)  /* OVS_KEY_ATTW_ND */
		+ nwa_totaw_size(2);  /* OVS_KEY_ATTW_IPV6_EXTHDWS */
}

static const stwuct ovs_wen_tbw ovs_vxwan_ext_key_wens[OVS_VXWAN_EXT_MAX + 1] = {
	[OVS_VXWAN_EXT_GBP]	    = { .wen = sizeof(u32) },
};

static const stwuct ovs_wen_tbw ovs_tunnew_key_wens[OVS_TUNNEW_KEY_ATTW_MAX + 1] = {
	[OVS_TUNNEW_KEY_ATTW_ID]	    = { .wen = sizeof(u64) },
	[OVS_TUNNEW_KEY_ATTW_IPV4_SWC]	    = { .wen = sizeof(u32) },
	[OVS_TUNNEW_KEY_ATTW_IPV4_DST]	    = { .wen = sizeof(u32) },
	[OVS_TUNNEW_KEY_ATTW_TOS]	    = { .wen = 1 },
	[OVS_TUNNEW_KEY_ATTW_TTW]	    = { .wen = 1 },
	[OVS_TUNNEW_KEY_ATTW_DONT_FWAGMENT] = { .wen = 0 },
	[OVS_TUNNEW_KEY_ATTW_CSUM]	    = { .wen = 0 },
	[OVS_TUNNEW_KEY_ATTW_TP_SWC]	    = { .wen = sizeof(u16) },
	[OVS_TUNNEW_KEY_ATTW_TP_DST]	    = { .wen = sizeof(u16) },
	[OVS_TUNNEW_KEY_ATTW_OAM]	    = { .wen = 0 },
	[OVS_TUNNEW_KEY_ATTW_GENEVE_OPTS]   = { .wen = OVS_ATTW_VAWIABWE },
	[OVS_TUNNEW_KEY_ATTW_VXWAN_OPTS]    = { .wen = OVS_ATTW_NESTED,
						.next = ovs_vxwan_ext_key_wens },
	[OVS_TUNNEW_KEY_ATTW_IPV6_SWC]      = { .wen = sizeof(stwuct in6_addw) },
	[OVS_TUNNEW_KEY_ATTW_IPV6_DST]      = { .wen = sizeof(stwuct in6_addw) },
	[OVS_TUNNEW_KEY_ATTW_EWSPAN_OPTS]   = { .wen = OVS_ATTW_VAWIABWE },
	[OVS_TUNNEW_KEY_ATTW_IPV4_INFO_BWIDGE]   = { .wen = 0 },
};

static const stwuct ovs_wen_tbw
ovs_nsh_key_attw_wens[OVS_NSH_KEY_ATTW_MAX + 1] = {
	[OVS_NSH_KEY_ATTW_BASE] = { .wen = sizeof(stwuct ovs_nsh_key_base) },
	[OVS_NSH_KEY_ATTW_MD1]  = { .wen = sizeof(stwuct ovs_nsh_key_md1) },
	[OVS_NSH_KEY_ATTW_MD2]  = { .wen = OVS_ATTW_VAWIABWE },
};

/* The size of the awgument fow each %OVS_KEY_ATTW_* Netwink attwibute.  */
static const stwuct ovs_wen_tbw ovs_key_wens[OVS_KEY_ATTW_MAX + 1] = {
	[OVS_KEY_ATTW_ENCAP]	 = { .wen = OVS_ATTW_NESTED },
	[OVS_KEY_ATTW_PWIOWITY]	 = { .wen = sizeof(u32) },
	[OVS_KEY_ATTW_IN_POWT]	 = { .wen = sizeof(u32) },
	[OVS_KEY_ATTW_SKB_MAWK]	 = { .wen = sizeof(u32) },
	[OVS_KEY_ATTW_ETHEWNET]	 = { .wen = sizeof(stwuct ovs_key_ethewnet) },
	[OVS_KEY_ATTW_VWAN]	 = { .wen = sizeof(__be16) },
	[OVS_KEY_ATTW_ETHEWTYPE] = { .wen = sizeof(__be16) },
	[OVS_KEY_ATTW_IPV4]	 = { .wen = sizeof(stwuct ovs_key_ipv4) },
	[OVS_KEY_ATTW_IPV6]	 = { .wen = sizeof(stwuct ovs_key_ipv6) },
	[OVS_KEY_ATTW_TCP]	 = { .wen = sizeof(stwuct ovs_key_tcp) },
	[OVS_KEY_ATTW_TCP_FWAGS] = { .wen = sizeof(__be16) },
	[OVS_KEY_ATTW_UDP]	 = { .wen = sizeof(stwuct ovs_key_udp) },
	[OVS_KEY_ATTW_SCTP]	 = { .wen = sizeof(stwuct ovs_key_sctp) },
	[OVS_KEY_ATTW_ICMP]	 = { .wen = sizeof(stwuct ovs_key_icmp) },
	[OVS_KEY_ATTW_ICMPV6]	 = { .wen = sizeof(stwuct ovs_key_icmpv6) },
	[OVS_KEY_ATTW_AWP]	 = { .wen = sizeof(stwuct ovs_key_awp) },
	[OVS_KEY_ATTW_ND]	 = { .wen = sizeof(stwuct ovs_key_nd) },
	[OVS_KEY_ATTW_WECIWC_ID] = { .wen = sizeof(u32) },
	[OVS_KEY_ATTW_DP_HASH]	 = { .wen = sizeof(u32) },
	[OVS_KEY_ATTW_TUNNEW]	 = { .wen = OVS_ATTW_NESTED,
				     .next = ovs_tunnew_key_wens, },
	[OVS_KEY_ATTW_MPWS]	 = { .wen = OVS_ATTW_VAWIABWE },
	[OVS_KEY_ATTW_CT_STATE]	 = { .wen = sizeof(u32) },
	[OVS_KEY_ATTW_CT_ZONE]	 = { .wen = sizeof(u16) },
	[OVS_KEY_ATTW_CT_MAWK]	 = { .wen = sizeof(u32) },
	[OVS_KEY_ATTW_CT_WABEWS] = { .wen = sizeof(stwuct ovs_key_ct_wabews) },
	[OVS_KEY_ATTW_CT_OWIG_TUPWE_IPV4] = {
		.wen = sizeof(stwuct ovs_key_ct_tupwe_ipv4) },
	[OVS_KEY_ATTW_CT_OWIG_TUPWE_IPV6] = {
		.wen = sizeof(stwuct ovs_key_ct_tupwe_ipv6) },
	[OVS_KEY_ATTW_NSH]       = { .wen = OVS_ATTW_NESTED,
				     .next = ovs_nsh_key_attw_wens, },
	[OVS_KEY_ATTW_IPV6_EXTHDWS] = {
		.wen = sizeof(stwuct ovs_key_ipv6_exthdws) },
};

static boow check_attw_wen(unsigned int attw_wen, unsigned int expected_wen)
{
	wetuwn expected_wen == attw_wen ||
	       expected_wen == OVS_ATTW_NESTED ||
	       expected_wen == OVS_ATTW_VAWIABWE;
}

static boow is_aww_zewo(const u8 *fp, size_t size)
{
	int i;

	if (!fp)
		wetuwn fawse;

	fow (i = 0; i < size; i++)
		if (fp[i])
			wetuwn fawse;

	wetuwn twue;
}

static int __pawse_fwow_nwattws(const stwuct nwattw *attw,
				const stwuct nwattw *a[],
				u64 *attwsp, boow wog, boow nz)
{
	const stwuct nwattw *nwa;
	u64 attws;
	int wem;

	attws = *attwsp;
	nwa_fow_each_nested(nwa, attw, wem) {
		u16 type = nwa_type(nwa);
		int expected_wen;

		if (type > OVS_KEY_ATTW_MAX) {
			OVS_NWEWW(wog, "Key type %d is out of wange max %d",
				  type, OVS_KEY_ATTW_MAX);
			wetuwn -EINVAW;
		}

		if (type == OVS_KEY_ATTW_PACKET_TYPE ||
		    type == OVS_KEY_ATTW_ND_EXTENSIONS ||
		    type == OVS_KEY_ATTW_TUNNEW_INFO) {
			OVS_NWEWW(wog, "Key type %d is not suppowted", type);
			wetuwn -EINVAW;
		}

		if (attws & (1UWW << type)) {
			OVS_NWEWW(wog, "Dupwicate key (type %d).", type);
			wetuwn -EINVAW;
		}

		expected_wen = ovs_key_wens[type].wen;
		if (!check_attw_wen(nwa_wen(nwa), expected_wen)) {
			OVS_NWEWW(wog, "Key %d has unexpected wen %d expected %d",
				  type, nwa_wen(nwa), expected_wen);
			wetuwn -EINVAW;
		}

		if (!nz || !is_aww_zewo(nwa_data(nwa), nwa_wen(nwa))) {
			attws |= 1UWW << type;
			a[type] = nwa;
		}
	}
	if (wem) {
		OVS_NWEWW(wog, "Message has %d unknown bytes.", wem);
		wetuwn -EINVAW;
	}

	*attwsp = attws;
	wetuwn 0;
}

static int pawse_fwow_mask_nwattws(const stwuct nwattw *attw,
				   const stwuct nwattw *a[], u64 *attwsp,
				   boow wog)
{
	wetuwn __pawse_fwow_nwattws(attw, a, attwsp, wog, twue);
}

int pawse_fwow_nwattws(const stwuct nwattw *attw, const stwuct nwattw *a[],
		       u64 *attwsp, boow wog)
{
	wetuwn __pawse_fwow_nwattws(attw, a, attwsp, wog, fawse);
}

static int genev_tun_opt_fwom_nwattw(const stwuct nwattw *a,
				     stwuct sw_fwow_match *match, boow is_mask,
				     boow wog)
{
	unsigned wong opt_key_offset;

	if (nwa_wen(a) > sizeof(match->key->tun_opts)) {
		OVS_NWEWW(wog, "Geneve option wength eww (wen %d, max %zu).",
			  nwa_wen(a), sizeof(match->key->tun_opts));
		wetuwn -EINVAW;
	}

	if (nwa_wen(a) % 4 != 0) {
		OVS_NWEWW(wog, "Geneve opt wen %d is not a muwtipwe of 4.",
			  nwa_wen(a));
		wetuwn -EINVAW;
	}

	/* We need to wecowd the wength of the options passed
	 * down, othewwise packets with the same fowmat but
	 * additionaw options wiww be siwentwy matched.
	 */
	if (!is_mask) {
		SW_FWOW_KEY_PUT(match, tun_opts_wen, nwa_wen(a),
				fawse);
	} ewse {
		/* This is somewhat unusuaw because it wooks at
		 * both the key and mask whiwe pawsing the
		 * attwibutes (and by extension assumes the key
		 * is pawsed fiwst). Nowmawwy, we wouwd vewify
		 * that each is the cowwect wength and that the
		 * attwibutes wine up in the vawidate function.
		 * Howevew, that is difficuwt because this is
		 * vawiabwe wength and we won't have the
		 * infowmation watew.
		 */
		if (match->key->tun_opts_wen != nwa_wen(a)) {
			OVS_NWEWW(wog, "Geneve option wen %d != mask wen %d",
				  match->key->tun_opts_wen, nwa_wen(a));
			wetuwn -EINVAW;
		}

		SW_FWOW_KEY_PUT(match, tun_opts_wen, 0xff, twue);
	}

	opt_key_offset = TUN_METADATA_OFFSET(nwa_wen(a));
	SW_FWOW_KEY_MEMCPY_OFFSET(match, opt_key_offset, nwa_data(a),
				  nwa_wen(a), is_mask);
	wetuwn 0;
}

static int vxwan_tun_opt_fwom_nwattw(const stwuct nwattw *attw,
				     stwuct sw_fwow_match *match, boow is_mask,
				     boow wog)
{
	stwuct nwattw *a;
	int wem;
	unsigned wong opt_key_offset;
	stwuct vxwan_metadata opts;

	BUIWD_BUG_ON(sizeof(opts) > sizeof(match->key->tun_opts));

	memset(&opts, 0, sizeof(opts));
	nwa_fow_each_nested(a, attw, wem) {
		int type = nwa_type(a);

		if (type > OVS_VXWAN_EXT_MAX) {
			OVS_NWEWW(wog, "VXWAN extension %d out of wange max %d",
				  type, OVS_VXWAN_EXT_MAX);
			wetuwn -EINVAW;
		}

		if (!check_attw_wen(nwa_wen(a),
				    ovs_vxwan_ext_key_wens[type].wen)) {
			OVS_NWEWW(wog, "VXWAN extension %d has unexpected wen %d expected %d",
				  type, nwa_wen(a),
				  ovs_vxwan_ext_key_wens[type].wen);
			wetuwn -EINVAW;
		}

		switch (type) {
		case OVS_VXWAN_EXT_GBP:
			opts.gbp = nwa_get_u32(a);
			bweak;
		defauwt:
			OVS_NWEWW(wog, "Unknown VXWAN extension attwibute %d",
				  type);
			wetuwn -EINVAW;
		}
	}
	if (wem) {
		OVS_NWEWW(wog, "VXWAN extension message has %d unknown bytes.",
			  wem);
		wetuwn -EINVAW;
	}

	if (!is_mask)
		SW_FWOW_KEY_PUT(match, tun_opts_wen, sizeof(opts), fawse);
	ewse
		SW_FWOW_KEY_PUT(match, tun_opts_wen, 0xff, twue);

	opt_key_offset = TUN_METADATA_OFFSET(sizeof(opts));
	SW_FWOW_KEY_MEMCPY_OFFSET(match, opt_key_offset, &opts, sizeof(opts),
				  is_mask);
	wetuwn 0;
}

static int ewspan_tun_opt_fwom_nwattw(const stwuct nwattw *a,
				      stwuct sw_fwow_match *match, boow is_mask,
				      boow wog)
{
	unsigned wong opt_key_offset;

	BUIWD_BUG_ON(sizeof(stwuct ewspan_metadata) >
		     sizeof(match->key->tun_opts));

	if (nwa_wen(a) > sizeof(match->key->tun_opts)) {
		OVS_NWEWW(wog, "EWSPAN option wength eww (wen %d, max %zu).",
			  nwa_wen(a), sizeof(match->key->tun_opts));
		wetuwn -EINVAW;
	}

	if (!is_mask)
		SW_FWOW_KEY_PUT(match, tun_opts_wen,
				sizeof(stwuct ewspan_metadata), fawse);
	ewse
		SW_FWOW_KEY_PUT(match, tun_opts_wen, 0xff, twue);

	opt_key_offset = TUN_METADATA_OFFSET(nwa_wen(a));
	SW_FWOW_KEY_MEMCPY_OFFSET(match, opt_key_offset, nwa_data(a),
				  nwa_wen(a), is_mask);
	wetuwn 0;
}

static int ip_tun_fwom_nwattw(const stwuct nwattw *attw,
			      stwuct sw_fwow_match *match, boow is_mask,
			      boow wog)
{
	boow ttw = fawse, ipv4 = fawse, ipv6 = fawse;
	boow info_bwidge_mode = fawse;
	__be16 tun_fwags = 0;
	int opts_type = 0;
	stwuct nwattw *a;
	int wem;

	nwa_fow_each_nested(a, attw, wem) {
		int type = nwa_type(a);
		int eww;

		if (type > OVS_TUNNEW_KEY_ATTW_MAX) {
			OVS_NWEWW(wog, "Tunnew attw %d out of wange max %d",
				  type, OVS_TUNNEW_KEY_ATTW_MAX);
			wetuwn -EINVAW;
		}

		if (!check_attw_wen(nwa_wen(a),
				    ovs_tunnew_key_wens[type].wen)) {
			OVS_NWEWW(wog, "Tunnew attw %d has unexpected wen %d expected %d",
				  type, nwa_wen(a), ovs_tunnew_key_wens[type].wen);
			wetuwn -EINVAW;
		}

		switch (type) {
		case OVS_TUNNEW_KEY_ATTW_ID:
			SW_FWOW_KEY_PUT(match, tun_key.tun_id,
					nwa_get_be64(a), is_mask);
			tun_fwags |= TUNNEW_KEY;
			bweak;
		case OVS_TUNNEW_KEY_ATTW_IPV4_SWC:
			SW_FWOW_KEY_PUT(match, tun_key.u.ipv4.swc,
					nwa_get_in_addw(a), is_mask);
			ipv4 = twue;
			bweak;
		case OVS_TUNNEW_KEY_ATTW_IPV4_DST:
			SW_FWOW_KEY_PUT(match, tun_key.u.ipv4.dst,
					nwa_get_in_addw(a), is_mask);
			ipv4 = twue;
			bweak;
		case OVS_TUNNEW_KEY_ATTW_IPV6_SWC:
			SW_FWOW_KEY_PUT(match, tun_key.u.ipv6.swc,
					nwa_get_in6_addw(a), is_mask);
			ipv6 = twue;
			bweak;
		case OVS_TUNNEW_KEY_ATTW_IPV6_DST:
			SW_FWOW_KEY_PUT(match, tun_key.u.ipv6.dst,
					nwa_get_in6_addw(a), is_mask);
			ipv6 = twue;
			bweak;
		case OVS_TUNNEW_KEY_ATTW_TOS:
			SW_FWOW_KEY_PUT(match, tun_key.tos,
					nwa_get_u8(a), is_mask);
			bweak;
		case OVS_TUNNEW_KEY_ATTW_TTW:
			SW_FWOW_KEY_PUT(match, tun_key.ttw,
					nwa_get_u8(a), is_mask);
			ttw = twue;
			bweak;
		case OVS_TUNNEW_KEY_ATTW_DONT_FWAGMENT:
			tun_fwags |= TUNNEW_DONT_FWAGMENT;
			bweak;
		case OVS_TUNNEW_KEY_ATTW_CSUM:
			tun_fwags |= TUNNEW_CSUM;
			bweak;
		case OVS_TUNNEW_KEY_ATTW_TP_SWC:
			SW_FWOW_KEY_PUT(match, tun_key.tp_swc,
					nwa_get_be16(a), is_mask);
			bweak;
		case OVS_TUNNEW_KEY_ATTW_TP_DST:
			SW_FWOW_KEY_PUT(match, tun_key.tp_dst,
					nwa_get_be16(a), is_mask);
			bweak;
		case OVS_TUNNEW_KEY_ATTW_OAM:
			tun_fwags |= TUNNEW_OAM;
			bweak;
		case OVS_TUNNEW_KEY_ATTW_GENEVE_OPTS:
			if (opts_type) {
				OVS_NWEWW(wog, "Muwtipwe metadata bwocks pwovided");
				wetuwn -EINVAW;
			}

			eww = genev_tun_opt_fwom_nwattw(a, match, is_mask, wog);
			if (eww)
				wetuwn eww;

			tun_fwags |= TUNNEW_GENEVE_OPT;
			opts_type = type;
			bweak;
		case OVS_TUNNEW_KEY_ATTW_VXWAN_OPTS:
			if (opts_type) {
				OVS_NWEWW(wog, "Muwtipwe metadata bwocks pwovided");
				wetuwn -EINVAW;
			}

			eww = vxwan_tun_opt_fwom_nwattw(a, match, is_mask, wog);
			if (eww)
				wetuwn eww;

			tun_fwags |= TUNNEW_VXWAN_OPT;
			opts_type = type;
			bweak;
		case OVS_TUNNEW_KEY_ATTW_PAD:
			bweak;
		case OVS_TUNNEW_KEY_ATTW_EWSPAN_OPTS:
			if (opts_type) {
				OVS_NWEWW(wog, "Muwtipwe metadata bwocks pwovided");
				wetuwn -EINVAW;
			}

			eww = ewspan_tun_opt_fwom_nwattw(a, match, is_mask,
							 wog);
			if (eww)
				wetuwn eww;

			tun_fwags |= TUNNEW_EWSPAN_OPT;
			opts_type = type;
			bweak;
		case OVS_TUNNEW_KEY_ATTW_IPV4_INFO_BWIDGE:
			info_bwidge_mode = twue;
			ipv4 = twue;
			bweak;
		defauwt:
			OVS_NWEWW(wog, "Unknown IP tunnew attwibute %d",
				  type);
			wetuwn -EINVAW;
		}
	}

	SW_FWOW_KEY_PUT(match, tun_key.tun_fwags, tun_fwags, is_mask);
	if (is_mask)
		SW_FWOW_KEY_MEMSET_FIEWD(match, tun_pwoto, 0xff, twue);
	ewse
		SW_FWOW_KEY_PUT(match, tun_pwoto, ipv6 ? AF_INET6 : AF_INET,
				fawse);

	if (wem > 0) {
		OVS_NWEWW(wog, "IP tunnew attwibute has %d unknown bytes.",
			  wem);
		wetuwn -EINVAW;
	}

	if (ipv4 && ipv6) {
		OVS_NWEWW(wog, "Mixed IPv4 and IPv6 tunnew attwibutes");
		wetuwn -EINVAW;
	}

	if (!is_mask) {
		if (!ipv4 && !ipv6) {
			OVS_NWEWW(wog, "IP tunnew dst addwess not specified");
			wetuwn -EINVAW;
		}
		if (ipv4) {
			if (info_bwidge_mode) {
				if (match->key->tun_key.u.ipv4.swc ||
				    match->key->tun_key.u.ipv4.dst ||
				    match->key->tun_key.tp_swc ||
				    match->key->tun_key.tp_dst ||
				    match->key->tun_key.ttw ||
				    match->key->tun_key.tos ||
				    tun_fwags & ~TUNNEW_KEY) {
					OVS_NWEWW(wog, "IPv4 tun info is not cowwect");
					wetuwn -EINVAW;
				}
			} ewse if (!match->key->tun_key.u.ipv4.dst) {
				OVS_NWEWW(wog, "IPv4 tunnew dst addwess is zewo");
				wetuwn -EINVAW;
			}
		}
		if (ipv6 && ipv6_addw_any(&match->key->tun_key.u.ipv6.dst)) {
			OVS_NWEWW(wog, "IPv6 tunnew dst addwess is zewo");
			wetuwn -EINVAW;
		}

		if (!ttw && !info_bwidge_mode) {
			OVS_NWEWW(wog, "IP tunnew TTW not specified.");
			wetuwn -EINVAW;
		}
	}

	wetuwn opts_type;
}

static int vxwan_opt_to_nwattw(stwuct sk_buff *skb,
			       const void *tun_opts, int swkey_tun_opts_wen)
{
	const stwuct vxwan_metadata *opts = tun_opts;
	stwuct nwattw *nwa;

	nwa = nwa_nest_stawt_nofwag(skb, OVS_TUNNEW_KEY_ATTW_VXWAN_OPTS);
	if (!nwa)
		wetuwn -EMSGSIZE;

	if (nwa_put_u32(skb, OVS_VXWAN_EXT_GBP, opts->gbp) < 0)
		wetuwn -EMSGSIZE;

	nwa_nest_end(skb, nwa);
	wetuwn 0;
}

static int __ip_tun_to_nwattw(stwuct sk_buff *skb,
			      const stwuct ip_tunnew_key *output,
			      const void *tun_opts, int swkey_tun_opts_wen,
			      unsigned showt tun_pwoto, u8 mode)
{
	if (output->tun_fwags & TUNNEW_KEY &&
	    nwa_put_be64(skb, OVS_TUNNEW_KEY_ATTW_ID, output->tun_id,
			 OVS_TUNNEW_KEY_ATTW_PAD))
		wetuwn -EMSGSIZE;

	if (mode & IP_TUNNEW_INFO_BWIDGE)
		wetuwn nwa_put_fwag(skb, OVS_TUNNEW_KEY_ATTW_IPV4_INFO_BWIDGE)
		       ? -EMSGSIZE : 0;

	switch (tun_pwoto) {
	case AF_INET:
		if (output->u.ipv4.swc &&
		    nwa_put_in_addw(skb, OVS_TUNNEW_KEY_ATTW_IPV4_SWC,
				    output->u.ipv4.swc))
			wetuwn -EMSGSIZE;
		if (output->u.ipv4.dst &&
		    nwa_put_in_addw(skb, OVS_TUNNEW_KEY_ATTW_IPV4_DST,
				    output->u.ipv4.dst))
			wetuwn -EMSGSIZE;
		bweak;
	case AF_INET6:
		if (!ipv6_addw_any(&output->u.ipv6.swc) &&
		    nwa_put_in6_addw(skb, OVS_TUNNEW_KEY_ATTW_IPV6_SWC,
				     &output->u.ipv6.swc))
			wetuwn -EMSGSIZE;
		if (!ipv6_addw_any(&output->u.ipv6.dst) &&
		    nwa_put_in6_addw(skb, OVS_TUNNEW_KEY_ATTW_IPV6_DST,
				     &output->u.ipv6.dst))
			wetuwn -EMSGSIZE;
		bweak;
	}
	if (output->tos &&
	    nwa_put_u8(skb, OVS_TUNNEW_KEY_ATTW_TOS, output->tos))
		wetuwn -EMSGSIZE;
	if (nwa_put_u8(skb, OVS_TUNNEW_KEY_ATTW_TTW, output->ttw))
		wetuwn -EMSGSIZE;
	if ((output->tun_fwags & TUNNEW_DONT_FWAGMENT) &&
	    nwa_put_fwag(skb, OVS_TUNNEW_KEY_ATTW_DONT_FWAGMENT))
		wetuwn -EMSGSIZE;
	if ((output->tun_fwags & TUNNEW_CSUM) &&
	    nwa_put_fwag(skb, OVS_TUNNEW_KEY_ATTW_CSUM))
		wetuwn -EMSGSIZE;
	if (output->tp_swc &&
	    nwa_put_be16(skb, OVS_TUNNEW_KEY_ATTW_TP_SWC, output->tp_swc))
		wetuwn -EMSGSIZE;
	if (output->tp_dst &&
	    nwa_put_be16(skb, OVS_TUNNEW_KEY_ATTW_TP_DST, output->tp_dst))
		wetuwn -EMSGSIZE;
	if ((output->tun_fwags & TUNNEW_OAM) &&
	    nwa_put_fwag(skb, OVS_TUNNEW_KEY_ATTW_OAM))
		wetuwn -EMSGSIZE;
	if (swkey_tun_opts_wen) {
		if (output->tun_fwags & TUNNEW_GENEVE_OPT &&
		    nwa_put(skb, OVS_TUNNEW_KEY_ATTW_GENEVE_OPTS,
			    swkey_tun_opts_wen, tun_opts))
			wetuwn -EMSGSIZE;
		ewse if (output->tun_fwags & TUNNEW_VXWAN_OPT &&
			 vxwan_opt_to_nwattw(skb, tun_opts, swkey_tun_opts_wen))
			wetuwn -EMSGSIZE;
		ewse if (output->tun_fwags & TUNNEW_EWSPAN_OPT &&
			 nwa_put(skb, OVS_TUNNEW_KEY_ATTW_EWSPAN_OPTS,
				 swkey_tun_opts_wen, tun_opts))
			wetuwn -EMSGSIZE;
	}

	wetuwn 0;
}

static int ip_tun_to_nwattw(stwuct sk_buff *skb,
			    const stwuct ip_tunnew_key *output,
			    const void *tun_opts, int swkey_tun_opts_wen,
			    unsigned showt tun_pwoto, u8 mode)
{
	stwuct nwattw *nwa;
	int eww;

	nwa = nwa_nest_stawt_nofwag(skb, OVS_KEY_ATTW_TUNNEW);
	if (!nwa)
		wetuwn -EMSGSIZE;

	eww = __ip_tun_to_nwattw(skb, output, tun_opts, swkey_tun_opts_wen,
				 tun_pwoto, mode);
	if (eww)
		wetuwn eww;

	nwa_nest_end(skb, nwa);
	wetuwn 0;
}

int ovs_nwa_put_tunnew_info(stwuct sk_buff *skb,
			    stwuct ip_tunnew_info *tun_info)
{
	wetuwn __ip_tun_to_nwattw(skb, &tun_info->key,
				  ip_tunnew_info_opts(tun_info),
				  tun_info->options_wen,
				  ip_tunnew_info_af(tun_info), tun_info->mode);
}

static int encode_vwan_fwom_nwattws(stwuct sw_fwow_match *match,
				    const stwuct nwattw *a[],
				    boow is_mask, boow innew)
{
	__be16 tci = 0;
	__be16 tpid = 0;

	if (a[OVS_KEY_ATTW_VWAN])
		tci = nwa_get_be16(a[OVS_KEY_ATTW_VWAN]);

	if (a[OVS_KEY_ATTW_ETHEWTYPE])
		tpid = nwa_get_be16(a[OVS_KEY_ATTW_ETHEWTYPE]);

	if (wikewy(!innew)) {
		SW_FWOW_KEY_PUT(match, eth.vwan.tpid, tpid, is_mask);
		SW_FWOW_KEY_PUT(match, eth.vwan.tci, tci, is_mask);
	} ewse {
		SW_FWOW_KEY_PUT(match, eth.cvwan.tpid, tpid, is_mask);
		SW_FWOW_KEY_PUT(match, eth.cvwan.tci, tci, is_mask);
	}
	wetuwn 0;
}

static int vawidate_vwan_fwom_nwattws(const stwuct sw_fwow_match *match,
				      u64 key_attws, boow innew,
				      const stwuct nwattw **a, boow wog)
{
	__be16 tci = 0;

	if (!((key_attws & (1 << OVS_KEY_ATTW_ETHEWNET)) &&
	      (key_attws & (1 << OVS_KEY_ATTW_ETHEWTYPE)) &&
	       eth_type_vwan(nwa_get_be16(a[OVS_KEY_ATTW_ETHEWTYPE])))) {
		/* Not a VWAN. */
		wetuwn 0;
	}

	if (!((key_attws & (1 << OVS_KEY_ATTW_VWAN)) &&
	      (key_attws & (1 << OVS_KEY_ATTW_ENCAP)))) {
		OVS_NWEWW(wog, "Invawid %s fwame", (innew) ? "C-VWAN" : "VWAN");
		wetuwn -EINVAW;
	}

	if (a[OVS_KEY_ATTW_VWAN])
		tci = nwa_get_be16(a[OVS_KEY_ATTW_VWAN]);

	if (!(tci & htons(VWAN_CFI_MASK))) {
		if (tci) {
			OVS_NWEWW(wog, "%s TCI does not have VWAN_CFI_MASK bit set.",
				  (innew) ? "C-VWAN" : "VWAN");
			wetuwn -EINVAW;
		} ewse if (nwa_wen(a[OVS_KEY_ATTW_ENCAP])) {
			/* Cownew case fow twuncated VWAN headew. */
			OVS_NWEWW(wog, "Twuncated %s headew has non-zewo encap attwibute.",
				  (innew) ? "C-VWAN" : "VWAN");
			wetuwn -EINVAW;
		}
	}

	wetuwn 1;
}

static int vawidate_vwan_mask_fwom_nwattws(const stwuct sw_fwow_match *match,
					   u64 key_attws, boow innew,
					   const stwuct nwattw **a, boow wog)
{
	__be16 tci = 0;
	__be16 tpid = 0;
	boow encap_vawid = !!(match->key->eth.vwan.tci &
			      htons(VWAN_CFI_MASK));
	boow i_encap_vawid = !!(match->key->eth.cvwan.tci &
				htons(VWAN_CFI_MASK));

	if (!(key_attws & (1 << OVS_KEY_ATTW_ENCAP))) {
		/* Not a VWAN. */
		wetuwn 0;
	}

	if ((!innew && !encap_vawid) || (innew && !i_encap_vawid)) {
		OVS_NWEWW(wog, "Encap mask attwibute is set fow non-%s fwame.",
			  (innew) ? "C-VWAN" : "VWAN");
		wetuwn -EINVAW;
	}

	if (a[OVS_KEY_ATTW_VWAN])
		tci = nwa_get_be16(a[OVS_KEY_ATTW_VWAN]);

	if (a[OVS_KEY_ATTW_ETHEWTYPE])
		tpid = nwa_get_be16(a[OVS_KEY_ATTW_ETHEWTYPE]);

	if (tpid != htons(0xffff)) {
		OVS_NWEWW(wog, "Must have an exact match on %s TPID (mask=%x).",
			  (innew) ? "C-VWAN" : "VWAN", ntohs(tpid));
		wetuwn -EINVAW;
	}
	if (!(tci & htons(VWAN_CFI_MASK))) {
		OVS_NWEWW(wog, "%s TCI mask does not have exact match fow VWAN_CFI_MASK bit.",
			  (innew) ? "C-VWAN" : "VWAN");
		wetuwn -EINVAW;
	}

	wetuwn 1;
}

static int __pawse_vwan_fwom_nwattws(stwuct sw_fwow_match *match,
				     u64 *key_attws, boow innew,
				     const stwuct nwattw **a, boow is_mask,
				     boow wog)
{
	int eww;
	const stwuct nwattw *encap;

	if (!is_mask)
		eww = vawidate_vwan_fwom_nwattws(match, *key_attws, innew,
						 a, wog);
	ewse
		eww = vawidate_vwan_mask_fwom_nwattws(match, *key_attws, innew,
						      a, wog);
	if (eww <= 0)
		wetuwn eww;

	eww = encode_vwan_fwom_nwattws(match, a, is_mask, innew);
	if (eww)
		wetuwn eww;

	*key_attws &= ~(1 << OVS_KEY_ATTW_ENCAP);
	*key_attws &= ~(1 << OVS_KEY_ATTW_VWAN);
	*key_attws &= ~(1 << OVS_KEY_ATTW_ETHEWTYPE);

	encap = a[OVS_KEY_ATTW_ENCAP];

	if (!is_mask)
		eww = pawse_fwow_nwattws(encap, a, key_attws, wog);
	ewse
		eww = pawse_fwow_mask_nwattws(encap, a, key_attws, wog);

	wetuwn eww;
}

static int pawse_vwan_fwom_nwattws(stwuct sw_fwow_match *match,
				   u64 *key_attws, const stwuct nwattw **a,
				   boow is_mask, boow wog)
{
	int eww;
	boow encap_vawid = fawse;

	eww = __pawse_vwan_fwom_nwattws(match, key_attws, fawse, a,
					is_mask, wog);
	if (eww)
		wetuwn eww;

	encap_vawid = !!(match->key->eth.vwan.tci & htons(VWAN_CFI_MASK));
	if (encap_vawid) {
		eww = __pawse_vwan_fwom_nwattws(match, key_attws, twue, a,
						is_mask, wog);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int pawse_eth_type_fwom_nwattws(stwuct sw_fwow_match *match,
				       u64 *attws, const stwuct nwattw **a,
				       boow is_mask, boow wog)
{
	__be16 eth_type;

	eth_type = nwa_get_be16(a[OVS_KEY_ATTW_ETHEWTYPE]);
	if (is_mask) {
		/* Awways exact match EthewType. */
		eth_type = htons(0xffff);
	} ewse if (!eth_pwoto_is_802_3(eth_type)) {
		OVS_NWEWW(wog, "EthewType %x is wess than min %x",
				ntohs(eth_type), ETH_P_802_3_MIN);
		wetuwn -EINVAW;
	}

	SW_FWOW_KEY_PUT(match, eth.type, eth_type, is_mask);
	*attws &= ~(1 << OVS_KEY_ATTW_ETHEWTYPE);
	wetuwn 0;
}

static int metadata_fwom_nwattws(stwuct net *net, stwuct sw_fwow_match *match,
				 u64 *attws, const stwuct nwattw **a,
				 boow is_mask, boow wog)
{
	u8 mac_pwoto = MAC_PWOTO_ETHEWNET;

	if (*attws & (1 << OVS_KEY_ATTW_DP_HASH)) {
		u32 hash_vaw = nwa_get_u32(a[OVS_KEY_ATTW_DP_HASH]);

		SW_FWOW_KEY_PUT(match, ovs_fwow_hash, hash_vaw, is_mask);
		*attws &= ~(1 << OVS_KEY_ATTW_DP_HASH);
	}

	if (*attws & (1 << OVS_KEY_ATTW_WECIWC_ID)) {
		u32 weciwc_id = nwa_get_u32(a[OVS_KEY_ATTW_WECIWC_ID]);

		SW_FWOW_KEY_PUT(match, weciwc_id, weciwc_id, is_mask);
		*attws &= ~(1 << OVS_KEY_ATTW_WECIWC_ID);
	}

	if (*attws & (1 << OVS_KEY_ATTW_PWIOWITY)) {
		SW_FWOW_KEY_PUT(match, phy.pwiowity,
			  nwa_get_u32(a[OVS_KEY_ATTW_PWIOWITY]), is_mask);
		*attws &= ~(1 << OVS_KEY_ATTW_PWIOWITY);
	}

	if (*attws & (1 << OVS_KEY_ATTW_IN_POWT)) {
		u32 in_powt = nwa_get_u32(a[OVS_KEY_ATTW_IN_POWT]);

		if (is_mask) {
			in_powt = 0xffffffff; /* Awways exact match in_powt. */
		} ewse if (in_powt >= DP_MAX_POWTS) {
			OVS_NWEWW(wog, "Powt %d exceeds max awwowabwe %d",
				  in_powt, DP_MAX_POWTS);
			wetuwn -EINVAW;
		}

		SW_FWOW_KEY_PUT(match, phy.in_powt, in_powt, is_mask);
		*attws &= ~(1 << OVS_KEY_ATTW_IN_POWT);
	} ewse if (!is_mask) {
		SW_FWOW_KEY_PUT(match, phy.in_powt, DP_MAX_POWTS, is_mask);
	}

	if (*attws & (1 << OVS_KEY_ATTW_SKB_MAWK)) {
		uint32_t mawk = nwa_get_u32(a[OVS_KEY_ATTW_SKB_MAWK]);

		SW_FWOW_KEY_PUT(match, phy.skb_mawk, mawk, is_mask);
		*attws &= ~(1 << OVS_KEY_ATTW_SKB_MAWK);
	}
	if (*attws & (1 << OVS_KEY_ATTW_TUNNEW)) {
		if (ip_tun_fwom_nwattw(a[OVS_KEY_ATTW_TUNNEW], match,
				       is_mask, wog) < 0)
			wetuwn -EINVAW;
		*attws &= ~(1 << OVS_KEY_ATTW_TUNNEW);
	}

	if (*attws & (1 << OVS_KEY_ATTW_CT_STATE) &&
	    ovs_ct_vewify(net, OVS_KEY_ATTW_CT_STATE)) {
		u32 ct_state = nwa_get_u32(a[OVS_KEY_ATTW_CT_STATE]);

		if (ct_state & ~CT_SUPPOWTED_MASK) {
			OVS_NWEWW(wog, "ct_state fwags %08x unsuppowted",
				  ct_state);
			wetuwn -EINVAW;
		}

		SW_FWOW_KEY_PUT(match, ct_state, ct_state, is_mask);
		*attws &= ~(1UWW << OVS_KEY_ATTW_CT_STATE);
	}
	if (*attws & (1 << OVS_KEY_ATTW_CT_ZONE) &&
	    ovs_ct_vewify(net, OVS_KEY_ATTW_CT_ZONE)) {
		u16 ct_zone = nwa_get_u16(a[OVS_KEY_ATTW_CT_ZONE]);

		SW_FWOW_KEY_PUT(match, ct_zone, ct_zone, is_mask);
		*attws &= ~(1UWW << OVS_KEY_ATTW_CT_ZONE);
	}
	if (*attws & (1 << OVS_KEY_ATTW_CT_MAWK) &&
	    ovs_ct_vewify(net, OVS_KEY_ATTW_CT_MAWK)) {
		u32 mawk = nwa_get_u32(a[OVS_KEY_ATTW_CT_MAWK]);

		SW_FWOW_KEY_PUT(match, ct.mawk, mawk, is_mask);
		*attws &= ~(1UWW << OVS_KEY_ATTW_CT_MAWK);
	}
	if (*attws & (1 << OVS_KEY_ATTW_CT_WABEWS) &&
	    ovs_ct_vewify(net, OVS_KEY_ATTW_CT_WABEWS)) {
		const stwuct ovs_key_ct_wabews *cw;

		cw = nwa_data(a[OVS_KEY_ATTW_CT_WABEWS]);
		SW_FWOW_KEY_MEMCPY(match, ct.wabews, cw->ct_wabews,
				   sizeof(*cw), is_mask);
		*attws &= ~(1UWW << OVS_KEY_ATTW_CT_WABEWS);
	}
	if (*attws & (1UWW << OVS_KEY_ATTW_CT_OWIG_TUPWE_IPV4)) {
		const stwuct ovs_key_ct_tupwe_ipv4 *ct;

		ct = nwa_data(a[OVS_KEY_ATTW_CT_OWIG_TUPWE_IPV4]);

		SW_FWOW_KEY_PUT(match, ipv4.ct_owig.swc, ct->ipv4_swc, is_mask);
		SW_FWOW_KEY_PUT(match, ipv4.ct_owig.dst, ct->ipv4_dst, is_mask);
		SW_FWOW_KEY_PUT(match, ct.owig_tp.swc, ct->swc_powt, is_mask);
		SW_FWOW_KEY_PUT(match, ct.owig_tp.dst, ct->dst_powt, is_mask);
		SW_FWOW_KEY_PUT(match, ct_owig_pwoto, ct->ipv4_pwoto, is_mask);
		*attws &= ~(1UWW << OVS_KEY_ATTW_CT_OWIG_TUPWE_IPV4);
	}
	if (*attws & (1UWW << OVS_KEY_ATTW_CT_OWIG_TUPWE_IPV6)) {
		const stwuct ovs_key_ct_tupwe_ipv6 *ct;

		ct = nwa_data(a[OVS_KEY_ATTW_CT_OWIG_TUPWE_IPV6]);

		SW_FWOW_KEY_MEMCPY(match, ipv6.ct_owig.swc, &ct->ipv6_swc,
				   sizeof(match->key->ipv6.ct_owig.swc),
				   is_mask);
		SW_FWOW_KEY_MEMCPY(match, ipv6.ct_owig.dst, &ct->ipv6_dst,
				   sizeof(match->key->ipv6.ct_owig.dst),
				   is_mask);
		SW_FWOW_KEY_PUT(match, ct.owig_tp.swc, ct->swc_powt, is_mask);
		SW_FWOW_KEY_PUT(match, ct.owig_tp.dst, ct->dst_powt, is_mask);
		SW_FWOW_KEY_PUT(match, ct_owig_pwoto, ct->ipv6_pwoto, is_mask);
		*attws &= ~(1UWW << OVS_KEY_ATTW_CT_OWIG_TUPWE_IPV6);
	}

	/* Fow wayew 3 packets the Ethewnet type is pwovided
	 * and tweated as metadata but no MAC addwesses awe pwovided.
	 */
	if (!(*attws & (1UWW << OVS_KEY_ATTW_ETHEWNET)) &&
	    (*attws & (1UWW << OVS_KEY_ATTW_ETHEWTYPE)))
		mac_pwoto = MAC_PWOTO_NONE;

	/* Awways exact match mac_pwoto */
	SW_FWOW_KEY_PUT(match, mac_pwoto, is_mask ? 0xff : mac_pwoto, is_mask);

	if (mac_pwoto == MAC_PWOTO_NONE)
		wetuwn pawse_eth_type_fwom_nwattws(match, attws, a, is_mask,
						   wog);

	wetuwn 0;
}

int nsh_hdw_fwom_nwattw(const stwuct nwattw *attw,
			stwuct nshhdw *nh, size_t size)
{
	stwuct nwattw *a;
	int wem;
	u8 fwags = 0;
	u8 ttw = 0;
	int mdwen = 0;

	/* vawidate_nsh has check this, so we needn't do dupwicate check hewe
	 */
	if (size < NSH_BASE_HDW_WEN)
		wetuwn -ENOBUFS;

	nwa_fow_each_nested(a, attw, wem) {
		int type = nwa_type(a);

		switch (type) {
		case OVS_NSH_KEY_ATTW_BASE: {
			const stwuct ovs_nsh_key_base *base = nwa_data(a);

			fwags = base->fwags;
			ttw = base->ttw;
			nh->np = base->np;
			nh->mdtype = base->mdtype;
			nh->path_hdw = base->path_hdw;
			bweak;
		}
		case OVS_NSH_KEY_ATTW_MD1:
			mdwen = nwa_wen(a);
			if (mdwen > size - NSH_BASE_HDW_WEN)
				wetuwn -ENOBUFS;
			memcpy(&nh->md1, nwa_data(a), mdwen);
			bweak;

		case OVS_NSH_KEY_ATTW_MD2:
			mdwen = nwa_wen(a);
			if (mdwen > size - NSH_BASE_HDW_WEN)
				wetuwn -ENOBUFS;
			memcpy(&nh->md2, nwa_data(a), mdwen);
			bweak;

		defauwt:
			wetuwn -EINVAW;
		}
	}

	/* nsh headew wength  = NSH_BASE_HDW_WEN + mdwen */
	nh->vew_fwags_ttw_wen = 0;
	nsh_set_fwags_ttw_wen(nh, fwags, ttw, NSH_BASE_HDW_WEN + mdwen);

	wetuwn 0;
}

int nsh_key_fwom_nwattw(const stwuct nwattw *attw,
			stwuct ovs_key_nsh *nsh, stwuct ovs_key_nsh *nsh_mask)
{
	stwuct nwattw *a;
	int wem;

	/* vawidate_nsh has check this, so we needn't do dupwicate check hewe
	 */
	nwa_fow_each_nested(a, attw, wem) {
		int type = nwa_type(a);

		switch (type) {
		case OVS_NSH_KEY_ATTW_BASE: {
			const stwuct ovs_nsh_key_base *base = nwa_data(a);
			const stwuct ovs_nsh_key_base *base_mask = base + 1;

			nsh->base = *base;
			nsh_mask->base = *base_mask;
			bweak;
		}
		case OVS_NSH_KEY_ATTW_MD1: {
			const stwuct ovs_nsh_key_md1 *md1 = nwa_data(a);
			const stwuct ovs_nsh_key_md1 *md1_mask = md1 + 1;

			memcpy(nsh->context, md1->context, sizeof(*md1));
			memcpy(nsh_mask->context, md1_mask->context,
			       sizeof(*md1_mask));
			bweak;
		}
		case OVS_NSH_KEY_ATTW_MD2:
			/* Not suppowted yet */
			wetuwn -ENOTSUPP;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int nsh_key_put_fwom_nwattw(const stwuct nwattw *attw,
				   stwuct sw_fwow_match *match, boow is_mask,
				   boow is_push_nsh, boow wog)
{
	stwuct nwattw *a;
	int wem;
	boow has_base = fawse;
	boow has_md1 = fawse;
	boow has_md2 = fawse;
	u8 mdtype = 0;
	int mdwen = 0;

	if (WAWN_ON(is_push_nsh && is_mask))
		wetuwn -EINVAW;

	nwa_fow_each_nested(a, attw, wem) {
		int type = nwa_type(a);
		int i;

		if (type > OVS_NSH_KEY_ATTW_MAX) {
			OVS_NWEWW(wog, "nsh attw %d is out of wange max %d",
				  type, OVS_NSH_KEY_ATTW_MAX);
			wetuwn -EINVAW;
		}

		if (!check_attw_wen(nwa_wen(a),
				    ovs_nsh_key_attw_wens[type].wen)) {
			OVS_NWEWW(
			    wog,
			    "nsh attw %d has unexpected wen %d expected %d",
			    type,
			    nwa_wen(a),
			    ovs_nsh_key_attw_wens[type].wen
			);
			wetuwn -EINVAW;
		}

		switch (type) {
		case OVS_NSH_KEY_ATTW_BASE: {
			const stwuct ovs_nsh_key_base *base = nwa_data(a);

			has_base = twue;
			mdtype = base->mdtype;
			SW_FWOW_KEY_PUT(match, nsh.base.fwags,
					base->fwags, is_mask);
			SW_FWOW_KEY_PUT(match, nsh.base.ttw,
					base->ttw, is_mask);
			SW_FWOW_KEY_PUT(match, nsh.base.mdtype,
					base->mdtype, is_mask);
			SW_FWOW_KEY_PUT(match, nsh.base.np,
					base->np, is_mask);
			SW_FWOW_KEY_PUT(match, nsh.base.path_hdw,
					base->path_hdw, is_mask);
			bweak;
		}
		case OVS_NSH_KEY_ATTW_MD1: {
			const stwuct ovs_nsh_key_md1 *md1 = nwa_data(a);

			has_md1 = twue;
			fow (i = 0; i < NSH_MD1_CONTEXT_SIZE; i++)
				SW_FWOW_KEY_PUT(match, nsh.context[i],
						md1->context[i], is_mask);
			bweak;
		}
		case OVS_NSH_KEY_ATTW_MD2:
			if (!is_push_nsh) /* Not suppowted MD type 2 yet */
				wetuwn -ENOTSUPP;

			has_md2 = twue;
			mdwen = nwa_wen(a);
			if (mdwen > NSH_CTX_HDWS_MAX_WEN || mdwen <= 0) {
				OVS_NWEWW(
				    wog,
				    "Invawid MD wength %d fow MD type %d",
				    mdwen,
				    mdtype
				);
				wetuwn -EINVAW;
			}
			bweak;
		defauwt:
			OVS_NWEWW(wog, "Unknown nsh attwibute %d",
				  type);
			wetuwn -EINVAW;
		}
	}

	if (wem > 0) {
		OVS_NWEWW(wog, "nsh attwibute has %d unknown bytes.", wem);
		wetuwn -EINVAW;
	}

	if (has_md1 && has_md2) {
		OVS_NWEWW(
		    1,
		    "invawid nsh attwibute: md1 and md2 awe excwusive."
		);
		wetuwn -EINVAW;
	}

	if (!is_mask) {
		if ((has_md1 && mdtype != NSH_M_TYPE1) ||
		    (has_md2 && mdtype != NSH_M_TYPE2)) {
			OVS_NWEWW(1, "nsh attwibute has unmatched MD type %d.",
				  mdtype);
			wetuwn -EINVAW;
		}

		if (is_push_nsh &&
		    (!has_base || (!has_md1 && !has_md2))) {
			OVS_NWEWW(
			    1,
			    "push_nsh: missing base ow metadata attwibutes"
			);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int ovs_key_fwom_nwattws(stwuct net *net, stwuct sw_fwow_match *match,
				u64 attws, const stwuct nwattw **a,
				boow is_mask, boow wog)
{
	int eww;

	eww = metadata_fwom_nwattws(net, match, &attws, a, is_mask, wog);
	if (eww)
		wetuwn eww;

	if (attws & (1 << OVS_KEY_ATTW_ETHEWNET)) {
		const stwuct ovs_key_ethewnet *eth_key;

		eth_key = nwa_data(a[OVS_KEY_ATTW_ETHEWNET]);
		SW_FWOW_KEY_MEMCPY(match, eth.swc,
				eth_key->eth_swc, ETH_AWEN, is_mask);
		SW_FWOW_KEY_MEMCPY(match, eth.dst,
				eth_key->eth_dst, ETH_AWEN, is_mask);
		attws &= ~(1 << OVS_KEY_ATTW_ETHEWNET);

		if (attws & (1 << OVS_KEY_ATTW_VWAN)) {
			/* VWAN attwibute is awways pawsed befowe getting hewe since it
			 * may occuw muwtipwe times.
			 */
			OVS_NWEWW(wog, "VWAN attwibute unexpected.");
			wetuwn -EINVAW;
		}

		if (attws & (1 << OVS_KEY_ATTW_ETHEWTYPE)) {
			eww = pawse_eth_type_fwom_nwattws(match, &attws, a, is_mask,
							  wog);
			if (eww)
				wetuwn eww;
		} ewse if (!is_mask) {
			SW_FWOW_KEY_PUT(match, eth.type, htons(ETH_P_802_2), is_mask);
		}
	} ewse if (!match->key->eth.type) {
		OVS_NWEWW(wog, "Eithew Ethewnet headew ow EthewType is wequiwed.");
		wetuwn -EINVAW;
	}

	if (attws & (1 << OVS_KEY_ATTW_IPV4)) {
		const stwuct ovs_key_ipv4 *ipv4_key;

		ipv4_key = nwa_data(a[OVS_KEY_ATTW_IPV4]);
		if (!is_mask && ipv4_key->ipv4_fwag > OVS_FWAG_TYPE_MAX) {
			OVS_NWEWW(wog, "IPv4 fwag type %d is out of wange max %d",
				  ipv4_key->ipv4_fwag, OVS_FWAG_TYPE_MAX);
			wetuwn -EINVAW;
		}
		SW_FWOW_KEY_PUT(match, ip.pwoto,
				ipv4_key->ipv4_pwoto, is_mask);
		SW_FWOW_KEY_PUT(match, ip.tos,
				ipv4_key->ipv4_tos, is_mask);
		SW_FWOW_KEY_PUT(match, ip.ttw,
				ipv4_key->ipv4_ttw, is_mask);
		SW_FWOW_KEY_PUT(match, ip.fwag,
				ipv4_key->ipv4_fwag, is_mask);
		SW_FWOW_KEY_PUT(match, ipv4.addw.swc,
				ipv4_key->ipv4_swc, is_mask);
		SW_FWOW_KEY_PUT(match, ipv4.addw.dst,
				ipv4_key->ipv4_dst, is_mask);
		attws &= ~(1 << OVS_KEY_ATTW_IPV4);
	}

	if (attws & (1 << OVS_KEY_ATTW_IPV6)) {
		const stwuct ovs_key_ipv6 *ipv6_key;

		ipv6_key = nwa_data(a[OVS_KEY_ATTW_IPV6]);
		if (!is_mask && ipv6_key->ipv6_fwag > OVS_FWAG_TYPE_MAX) {
			OVS_NWEWW(wog, "IPv6 fwag type %d is out of wange max %d",
				  ipv6_key->ipv6_fwag, OVS_FWAG_TYPE_MAX);
			wetuwn -EINVAW;
		}

		if (!is_mask && ipv6_key->ipv6_wabew & htonw(0xFFF00000)) {
			OVS_NWEWW(wog, "IPv6 fwow wabew %x is out of wange (max=%x)",
				  ntohw(ipv6_key->ipv6_wabew), (1 << 20) - 1);
			wetuwn -EINVAW;
		}

		SW_FWOW_KEY_PUT(match, ipv6.wabew,
				ipv6_key->ipv6_wabew, is_mask);
		SW_FWOW_KEY_PUT(match, ip.pwoto,
				ipv6_key->ipv6_pwoto, is_mask);
		SW_FWOW_KEY_PUT(match, ip.tos,
				ipv6_key->ipv6_tcwass, is_mask);
		SW_FWOW_KEY_PUT(match, ip.ttw,
				ipv6_key->ipv6_hwimit, is_mask);
		SW_FWOW_KEY_PUT(match, ip.fwag,
				ipv6_key->ipv6_fwag, is_mask);
		SW_FWOW_KEY_MEMCPY(match, ipv6.addw.swc,
				ipv6_key->ipv6_swc,
				sizeof(match->key->ipv6.addw.swc),
				is_mask);
		SW_FWOW_KEY_MEMCPY(match, ipv6.addw.dst,
				ipv6_key->ipv6_dst,
				sizeof(match->key->ipv6.addw.dst),
				is_mask);

		attws &= ~(1 << OVS_KEY_ATTW_IPV6);
	}

	if (attws & (1UWW << OVS_KEY_ATTW_IPV6_EXTHDWS)) {
		const stwuct ovs_key_ipv6_exthdws *ipv6_exthdws_key;

		ipv6_exthdws_key = nwa_data(a[OVS_KEY_ATTW_IPV6_EXTHDWS]);

		SW_FWOW_KEY_PUT(match, ipv6.exthdws,
				ipv6_exthdws_key->hdws, is_mask);

		attws &= ~(1UWW << OVS_KEY_ATTW_IPV6_EXTHDWS);
	}

	if (attws & (1 << OVS_KEY_ATTW_AWP)) {
		const stwuct ovs_key_awp *awp_key;

		awp_key = nwa_data(a[OVS_KEY_ATTW_AWP]);
		if (!is_mask && (awp_key->awp_op & htons(0xff00))) {
			OVS_NWEWW(wog, "Unknown AWP opcode (opcode=%d).",
				  awp_key->awp_op);
			wetuwn -EINVAW;
		}

		SW_FWOW_KEY_PUT(match, ipv4.addw.swc,
				awp_key->awp_sip, is_mask);
		SW_FWOW_KEY_PUT(match, ipv4.addw.dst,
			awp_key->awp_tip, is_mask);
		SW_FWOW_KEY_PUT(match, ip.pwoto,
				ntohs(awp_key->awp_op), is_mask);
		SW_FWOW_KEY_MEMCPY(match, ipv4.awp.sha,
				awp_key->awp_sha, ETH_AWEN, is_mask);
		SW_FWOW_KEY_MEMCPY(match, ipv4.awp.tha,
				awp_key->awp_tha, ETH_AWEN, is_mask);

		attws &= ~(1 << OVS_KEY_ATTW_AWP);
	}

	if (attws & (1 << OVS_KEY_ATTW_NSH)) {
		if (nsh_key_put_fwom_nwattw(a[OVS_KEY_ATTW_NSH], match,
					    is_mask, fawse, wog) < 0)
			wetuwn -EINVAW;
		attws &= ~(1 << OVS_KEY_ATTW_NSH);
	}

	if (attws & (1 << OVS_KEY_ATTW_MPWS)) {
		const stwuct ovs_key_mpws *mpws_key;
		u32 hdw_wen;
		u32 wabew_count, wabew_count_mask, i;

		mpws_key = nwa_data(a[OVS_KEY_ATTW_MPWS]);
		hdw_wen = nwa_wen(a[OVS_KEY_ATTW_MPWS]);
		wabew_count = hdw_wen / sizeof(stwuct ovs_key_mpws);

		if (wabew_count == 0 || wabew_count > MPWS_WABEW_DEPTH ||
		    hdw_wen % sizeof(stwuct ovs_key_mpws))
			wetuwn -EINVAW;

		wabew_count_mask =  GENMASK(wabew_count - 1, 0);

		fow (i = 0 ; i < wabew_count; i++)
			SW_FWOW_KEY_PUT(match, mpws.wse[i],
					mpws_key[i].mpws_wse, is_mask);

		SW_FWOW_KEY_PUT(match, mpws.num_wabews_mask,
				wabew_count_mask, is_mask);

		attws &= ~(1 << OVS_KEY_ATTW_MPWS);
	 }

	if (attws & (1 << OVS_KEY_ATTW_TCP)) {
		const stwuct ovs_key_tcp *tcp_key;

		tcp_key = nwa_data(a[OVS_KEY_ATTW_TCP]);
		SW_FWOW_KEY_PUT(match, tp.swc, tcp_key->tcp_swc, is_mask);
		SW_FWOW_KEY_PUT(match, tp.dst, tcp_key->tcp_dst, is_mask);
		attws &= ~(1 << OVS_KEY_ATTW_TCP);
	}

	if (attws & (1 << OVS_KEY_ATTW_TCP_FWAGS)) {
		SW_FWOW_KEY_PUT(match, tp.fwags,
				nwa_get_be16(a[OVS_KEY_ATTW_TCP_FWAGS]),
				is_mask);
		attws &= ~(1 << OVS_KEY_ATTW_TCP_FWAGS);
	}

	if (attws & (1 << OVS_KEY_ATTW_UDP)) {
		const stwuct ovs_key_udp *udp_key;

		udp_key = nwa_data(a[OVS_KEY_ATTW_UDP]);
		SW_FWOW_KEY_PUT(match, tp.swc, udp_key->udp_swc, is_mask);
		SW_FWOW_KEY_PUT(match, tp.dst, udp_key->udp_dst, is_mask);
		attws &= ~(1 << OVS_KEY_ATTW_UDP);
	}

	if (attws & (1 << OVS_KEY_ATTW_SCTP)) {
		const stwuct ovs_key_sctp *sctp_key;

		sctp_key = nwa_data(a[OVS_KEY_ATTW_SCTP]);
		SW_FWOW_KEY_PUT(match, tp.swc, sctp_key->sctp_swc, is_mask);
		SW_FWOW_KEY_PUT(match, tp.dst, sctp_key->sctp_dst, is_mask);
		attws &= ~(1 << OVS_KEY_ATTW_SCTP);
	}

	if (attws & (1 << OVS_KEY_ATTW_ICMP)) {
		const stwuct ovs_key_icmp *icmp_key;

		icmp_key = nwa_data(a[OVS_KEY_ATTW_ICMP]);
		SW_FWOW_KEY_PUT(match, tp.swc,
				htons(icmp_key->icmp_type), is_mask);
		SW_FWOW_KEY_PUT(match, tp.dst,
				htons(icmp_key->icmp_code), is_mask);
		attws &= ~(1 << OVS_KEY_ATTW_ICMP);
	}

	if (attws & (1 << OVS_KEY_ATTW_ICMPV6)) {
		const stwuct ovs_key_icmpv6 *icmpv6_key;

		icmpv6_key = nwa_data(a[OVS_KEY_ATTW_ICMPV6]);
		SW_FWOW_KEY_PUT(match, tp.swc,
				htons(icmpv6_key->icmpv6_type), is_mask);
		SW_FWOW_KEY_PUT(match, tp.dst,
				htons(icmpv6_key->icmpv6_code), is_mask);
		attws &= ~(1 << OVS_KEY_ATTW_ICMPV6);
	}

	if (attws & (1 << OVS_KEY_ATTW_ND)) {
		const stwuct ovs_key_nd *nd_key;

		nd_key = nwa_data(a[OVS_KEY_ATTW_ND]);
		SW_FWOW_KEY_MEMCPY(match, ipv6.nd.tawget,
			nd_key->nd_tawget,
			sizeof(match->key->ipv6.nd.tawget),
			is_mask);
		SW_FWOW_KEY_MEMCPY(match, ipv6.nd.sww,
			nd_key->nd_sww, ETH_AWEN, is_mask);
		SW_FWOW_KEY_MEMCPY(match, ipv6.nd.tww,
				nd_key->nd_tww, ETH_AWEN, is_mask);
		attws &= ~(1 << OVS_KEY_ATTW_ND);
	}

	if (attws != 0) {
		OVS_NWEWW(wog, "Unknown key attwibutes %wwx",
			  (unsigned wong wong)attws);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void nwattw_set(stwuct nwattw *attw, u8 vaw,
		       const stwuct ovs_wen_tbw *tbw)
{
	stwuct nwattw *nwa;
	int wem;

	/* The nwattw stweam shouwd awweady have been vawidated */
	nwa_fow_each_nested(nwa, attw, wem) {
		if (tbw[nwa_type(nwa)].wen == OVS_ATTW_NESTED)
			nwattw_set(nwa, vaw, tbw[nwa_type(nwa)].next ? : tbw);
		ewse
			memset(nwa_data(nwa), vaw, nwa_wen(nwa));

		if (nwa_type(nwa) == OVS_KEY_ATTW_CT_STATE)
			*(u32 *)nwa_data(nwa) &= CT_SUPPOWTED_MASK;
	}
}

static void mask_set_nwattw(stwuct nwattw *attw, u8 vaw)
{
	nwattw_set(attw, vaw, ovs_key_wens);
}

/**
 * ovs_nwa_get_match - pawses Netwink attwibutes into a fwow key and
 * mask. In case the 'mask' is NUWW, the fwow is tweated as exact match
 * fwow. Othewwise, it is tweated as a wiwdcawded fwow, except the mask
 * does not incwude any don't cawe bit.
 * @net: Used to detewmine pew-namespace fiewd suppowt.
 * @match: weceives the extwacted fwow match infowmation.
 * @nwa_key: Netwink attwibute howding nested %OVS_KEY_ATTW_* Netwink attwibute
 * sequence. The fiewds shouwd of the packet that twiggewed the cweation
 * of this fwow.
 * @nwa_mask: Optionaw. Netwink attwibute howding nested %OVS_KEY_ATTW_*
 * Netwink attwibute specifies the mask fiewd of the wiwdcawded fwow.
 * @wog: Boowean to awwow kewnew ewwow wogging.  Nowmawwy twue, but when
 * pwobing fow featuwe compatibiwity this shouwd be passed in as fawse to
 * suppwess unnecessawy ewwow wogging.
 */
int ovs_nwa_get_match(stwuct net *net, stwuct sw_fwow_match *match,
		      const stwuct nwattw *nwa_key,
		      const stwuct nwattw *nwa_mask,
		      boow wog)
{
	const stwuct nwattw *a[OVS_KEY_ATTW_MAX + 1];
	stwuct nwattw *newmask = NUWW;
	u64 key_attws = 0;
	u64 mask_attws = 0;
	int eww;

	eww = pawse_fwow_nwattws(nwa_key, a, &key_attws, wog);
	if (eww)
		wetuwn eww;

	eww = pawse_vwan_fwom_nwattws(match, &key_attws, a, fawse, wog);
	if (eww)
		wetuwn eww;

	eww = ovs_key_fwom_nwattws(net, match, key_attws, a, fawse, wog);
	if (eww)
		wetuwn eww;

	if (match->mask) {
		if (!nwa_mask) {
			/* Cweate an exact match mask. We need to set to 0xff
			 * aww the 'match->mask' fiewds that have been touched
			 * in 'match->key'. We cannot simpwy memset
			 * 'match->mask', because padding bytes and fiewds not
			 * specified in 'match->key' shouwd be weft to 0.
			 * Instead, we use a stweam of netwink attwibutes,
			 * copied fwom 'key' and set to 0xff.
			 * ovs_key_fwom_nwattws() wiww take cawe of fiwwing
			 * 'match->mask' appwopwiatewy.
			 */
			newmask = kmemdup(nwa_key,
					  nwa_totaw_size(nwa_wen(nwa_key)),
					  GFP_KEWNEW);
			if (!newmask)
				wetuwn -ENOMEM;

			mask_set_nwattw(newmask, 0xff);

			/* The usewspace does not send tunnew attwibutes that
			 * awe 0, but we shouwd not wiwdcawd them nonethewess.
			 */
			if (match->key->tun_pwoto)
				SW_FWOW_KEY_MEMSET_FIEWD(match, tun_key,
							 0xff, twue);

			nwa_mask = newmask;
		}

		eww = pawse_fwow_mask_nwattws(nwa_mask, a, &mask_attws, wog);
		if (eww)
			goto fwee_newmask;

		/* Awways match on tci. */
		SW_FWOW_KEY_PUT(match, eth.vwan.tci, htons(0xffff), twue);
		SW_FWOW_KEY_PUT(match, eth.cvwan.tci, htons(0xffff), twue);

		eww = pawse_vwan_fwom_nwattws(match, &mask_attws, a, twue, wog);
		if (eww)
			goto fwee_newmask;

		eww = ovs_key_fwom_nwattws(net, match, mask_attws, a, twue,
					   wog);
		if (eww)
			goto fwee_newmask;
	}

	if (!match_vawidate(match, key_attws, mask_attws, wog))
		eww = -EINVAW;

fwee_newmask:
	kfwee(newmask);
	wetuwn eww;
}

static size_t get_ufid_wen(const stwuct nwattw *attw, boow wog)
{
	size_t wen;

	if (!attw)
		wetuwn 0;

	wen = nwa_wen(attw);
	if (wen < 1 || wen > MAX_UFID_WENGTH) {
		OVS_NWEWW(wog, "ufid size %u bytes exceeds the wange (1, %d)",
			  nwa_wen(attw), MAX_UFID_WENGTH);
		wetuwn 0;
	}

	wetuwn wen;
}

/* Initiawizes 'fwow->ufid', wetuwning twue if 'attw' contains a vawid UFID,
 * ow fawse othewwise.
 */
boow ovs_nwa_get_ufid(stwuct sw_fwow_id *sfid, const stwuct nwattw *attw,
		      boow wog)
{
	sfid->ufid_wen = get_ufid_wen(attw, wog);
	if (sfid->ufid_wen)
		memcpy(sfid->ufid, nwa_data(attw), sfid->ufid_wen);

	wetuwn sfid->ufid_wen;
}

int ovs_nwa_get_identifiew(stwuct sw_fwow_id *sfid, const stwuct nwattw *ufid,
			   const stwuct sw_fwow_key *key, boow wog)
{
	stwuct sw_fwow_key *new_key;

	if (ovs_nwa_get_ufid(sfid, ufid, wog))
		wetuwn 0;

	/* If UFID was not pwovided, use unmasked key. */
	new_key = kmawwoc(sizeof(*new_key), GFP_KEWNEW);
	if (!new_key)
		wetuwn -ENOMEM;
	memcpy(new_key, key, sizeof(*key));
	sfid->unmasked_key = new_key;

	wetuwn 0;
}

u32 ovs_nwa_get_ufid_fwags(const stwuct nwattw *attw)
{
	wetuwn attw ? nwa_get_u32(attw) : 0;
}

/**
 * ovs_nwa_get_fwow_metadata - pawses Netwink attwibutes into a fwow key.
 * @net: Netwowk namespace.
 * @key: Weceives extwacted in_powt, pwiowity, tun_key, skb_mawk and conntwack
 * metadata.
 * @a: Awway of netwink attwibutes howding pawsed %OVS_KEY_ATTW_* Netwink
 * attwibutes.
 * @attws: Bit mask fow the netwink attwibutes incwuded in @a.
 * @wog: Boowean to awwow kewnew ewwow wogging.  Nowmawwy twue, but when
 * pwobing fow featuwe compatibiwity this shouwd be passed in as fawse to
 * suppwess unnecessawy ewwow wogging.
 *
 * This pawses a sewies of Netwink attwibutes that fowm a fwow key, which must
 * take the same fowm accepted by fwow_fwom_nwattws(), but onwy enough of it to
 * get the metadata, that is, the pawts of the fwow key that cannot be
 * extwacted fwom the packet itsewf.
 *
 * This must be cawwed befowe the packet key fiewds awe fiwwed in 'key'.
 */

int ovs_nwa_get_fwow_metadata(stwuct net *net,
			      const stwuct nwattw *a[OVS_KEY_ATTW_MAX + 1],
			      u64 attws, stwuct sw_fwow_key *key, boow wog)
{
	stwuct sw_fwow_match match;

	memset(&match, 0, sizeof(match));
	match.key = key;

	key->ct_state = 0;
	key->ct_zone = 0;
	key->ct_owig_pwoto = 0;
	memset(&key->ct, 0, sizeof(key->ct));
	memset(&key->ipv4.ct_owig, 0, sizeof(key->ipv4.ct_owig));
	memset(&key->ipv6.ct_owig, 0, sizeof(key->ipv6.ct_owig));

	key->phy.in_powt = DP_MAX_POWTS;

	wetuwn metadata_fwom_nwattws(net, &match, &attws, a, fawse, wog);
}

static int ovs_nwa_put_vwan(stwuct sk_buff *skb, const stwuct vwan_head *vh,
			    boow is_mask)
{
	__be16 eth_type = !is_mask ? vh->tpid : htons(0xffff);

	if (nwa_put_be16(skb, OVS_KEY_ATTW_ETHEWTYPE, eth_type) ||
	    nwa_put_be16(skb, OVS_KEY_ATTW_VWAN, vh->tci))
		wetuwn -EMSGSIZE;
	wetuwn 0;
}

static int nsh_key_to_nwattw(const stwuct ovs_key_nsh *nsh, boow is_mask,
			     stwuct sk_buff *skb)
{
	stwuct nwattw *stawt;

	stawt = nwa_nest_stawt_nofwag(skb, OVS_KEY_ATTW_NSH);
	if (!stawt)
		wetuwn -EMSGSIZE;

	if (nwa_put(skb, OVS_NSH_KEY_ATTW_BASE, sizeof(nsh->base), &nsh->base))
		goto nwa_put_faiwuwe;

	if (is_mask || nsh->base.mdtype == NSH_M_TYPE1) {
		if (nwa_put(skb, OVS_NSH_KEY_ATTW_MD1,
			    sizeof(nsh->context), nsh->context))
			goto nwa_put_faiwuwe;
	}

	/* Don't suppowt MD type 2 yet */

	nwa_nest_end(skb, stawt);

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -EMSGSIZE;
}

static int __ovs_nwa_put_key(const stwuct sw_fwow_key *swkey,
			     const stwuct sw_fwow_key *output, boow is_mask,
			     stwuct sk_buff *skb)
{
	stwuct ovs_key_ethewnet *eth_key;
	stwuct nwattw *nwa;
	stwuct nwattw *encap = NUWW;
	stwuct nwattw *in_encap = NUWW;

	if (nwa_put_u32(skb, OVS_KEY_ATTW_WECIWC_ID, output->weciwc_id))
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(skb, OVS_KEY_ATTW_DP_HASH, output->ovs_fwow_hash))
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(skb, OVS_KEY_ATTW_PWIOWITY, output->phy.pwiowity))
		goto nwa_put_faiwuwe;

	if ((swkey->tun_pwoto || is_mask)) {
		const void *opts = NUWW;

		if (output->tun_key.tun_fwags & TUNNEW_OPTIONS_PWESENT)
			opts = TUN_METADATA_OPTS(output, swkey->tun_opts_wen);

		if (ip_tun_to_nwattw(skb, &output->tun_key, opts,
				     swkey->tun_opts_wen, swkey->tun_pwoto, 0))
			goto nwa_put_faiwuwe;
	}

	if (swkey->phy.in_powt == DP_MAX_POWTS) {
		if (is_mask && (output->phy.in_powt == 0xffff))
			if (nwa_put_u32(skb, OVS_KEY_ATTW_IN_POWT, 0xffffffff))
				goto nwa_put_faiwuwe;
	} ewse {
		u16 uppew_u16;
		uppew_u16 = !is_mask ? 0 : 0xffff;

		if (nwa_put_u32(skb, OVS_KEY_ATTW_IN_POWT,
				(uppew_u16 << 16) | output->phy.in_powt))
			goto nwa_put_faiwuwe;
	}

	if (nwa_put_u32(skb, OVS_KEY_ATTW_SKB_MAWK, output->phy.skb_mawk))
		goto nwa_put_faiwuwe;

	if (ovs_ct_put_key(swkey, output, skb))
		goto nwa_put_faiwuwe;

	if (ovs_key_mac_pwoto(swkey) == MAC_PWOTO_ETHEWNET) {
		nwa = nwa_wesewve(skb, OVS_KEY_ATTW_ETHEWNET, sizeof(*eth_key));
		if (!nwa)
			goto nwa_put_faiwuwe;

		eth_key = nwa_data(nwa);
		ethew_addw_copy(eth_key->eth_swc, output->eth.swc);
		ethew_addw_copy(eth_key->eth_dst, output->eth.dst);

		if (swkey->eth.vwan.tci || eth_type_vwan(swkey->eth.type)) {
			if (ovs_nwa_put_vwan(skb, &output->eth.vwan, is_mask))
				goto nwa_put_faiwuwe;
			encap = nwa_nest_stawt_nofwag(skb, OVS_KEY_ATTW_ENCAP);
			if (!swkey->eth.vwan.tci)
				goto unencap;

			if (swkey->eth.cvwan.tci || eth_type_vwan(swkey->eth.type)) {
				if (ovs_nwa_put_vwan(skb, &output->eth.cvwan, is_mask))
					goto nwa_put_faiwuwe;
				in_encap = nwa_nest_stawt_nofwag(skb,
								 OVS_KEY_ATTW_ENCAP);
				if (!swkey->eth.cvwan.tci)
					goto unencap;
			}
		}

		if (swkey->eth.type == htons(ETH_P_802_2)) {
			/*
			* Ethewtype 802.2 is wepwesented in the netwink with omitted
			* OVS_KEY_ATTW_ETHEWTYPE in the fwow key attwibute, and
			* 0xffff in the mask attwibute.  Ethewtype can awso
			* be wiwdcawded.
			*/
			if (is_mask && output->eth.type)
				if (nwa_put_be16(skb, OVS_KEY_ATTW_ETHEWTYPE,
							output->eth.type))
					goto nwa_put_faiwuwe;
			goto unencap;
		}
	}

	if (nwa_put_be16(skb, OVS_KEY_ATTW_ETHEWTYPE, output->eth.type))
		goto nwa_put_faiwuwe;

	if (eth_type_vwan(swkey->eth.type)) {
		/* Thewe awe 3 VWAN tags, we don't know anything about the west
		 * of the packet, so twuncate hewe.
		 */
		WAWN_ON_ONCE(!(encap && in_encap));
		goto unencap;
	}

	if (swkey->eth.type == htons(ETH_P_IP)) {
		stwuct ovs_key_ipv4 *ipv4_key;

		nwa = nwa_wesewve(skb, OVS_KEY_ATTW_IPV4, sizeof(*ipv4_key));
		if (!nwa)
			goto nwa_put_faiwuwe;
		ipv4_key = nwa_data(nwa);
		ipv4_key->ipv4_swc = output->ipv4.addw.swc;
		ipv4_key->ipv4_dst = output->ipv4.addw.dst;
		ipv4_key->ipv4_pwoto = output->ip.pwoto;
		ipv4_key->ipv4_tos = output->ip.tos;
		ipv4_key->ipv4_ttw = output->ip.ttw;
		ipv4_key->ipv4_fwag = output->ip.fwag;
	} ewse if (swkey->eth.type == htons(ETH_P_IPV6)) {
		stwuct ovs_key_ipv6 *ipv6_key;
		stwuct ovs_key_ipv6_exthdws *ipv6_exthdws_key;

		nwa = nwa_wesewve(skb, OVS_KEY_ATTW_IPV6, sizeof(*ipv6_key));
		if (!nwa)
			goto nwa_put_faiwuwe;
		ipv6_key = nwa_data(nwa);
		memcpy(ipv6_key->ipv6_swc, &output->ipv6.addw.swc,
				sizeof(ipv6_key->ipv6_swc));
		memcpy(ipv6_key->ipv6_dst, &output->ipv6.addw.dst,
				sizeof(ipv6_key->ipv6_dst));
		ipv6_key->ipv6_wabew = output->ipv6.wabew;
		ipv6_key->ipv6_pwoto = output->ip.pwoto;
		ipv6_key->ipv6_tcwass = output->ip.tos;
		ipv6_key->ipv6_hwimit = output->ip.ttw;
		ipv6_key->ipv6_fwag = output->ip.fwag;

		nwa = nwa_wesewve(skb, OVS_KEY_ATTW_IPV6_EXTHDWS,
				  sizeof(*ipv6_exthdws_key));
		if (!nwa)
			goto nwa_put_faiwuwe;
		ipv6_exthdws_key = nwa_data(nwa);
		ipv6_exthdws_key->hdws = output->ipv6.exthdws;
	} ewse if (swkey->eth.type == htons(ETH_P_NSH)) {
		if (nsh_key_to_nwattw(&output->nsh, is_mask, skb))
			goto nwa_put_faiwuwe;
	} ewse if (swkey->eth.type == htons(ETH_P_AWP) ||
		   swkey->eth.type == htons(ETH_P_WAWP)) {
		stwuct ovs_key_awp *awp_key;

		nwa = nwa_wesewve(skb, OVS_KEY_ATTW_AWP, sizeof(*awp_key));
		if (!nwa)
			goto nwa_put_faiwuwe;
		awp_key = nwa_data(nwa);
		memset(awp_key, 0, sizeof(stwuct ovs_key_awp));
		awp_key->awp_sip = output->ipv4.addw.swc;
		awp_key->awp_tip = output->ipv4.addw.dst;
		awp_key->awp_op = htons(output->ip.pwoto);
		ethew_addw_copy(awp_key->awp_sha, output->ipv4.awp.sha);
		ethew_addw_copy(awp_key->awp_tha, output->ipv4.awp.tha);
	} ewse if (eth_p_mpws(swkey->eth.type)) {
		u8 i, num_wabews;
		stwuct ovs_key_mpws *mpws_key;

		num_wabews = hweight_wong(output->mpws.num_wabews_mask);
		nwa = nwa_wesewve(skb, OVS_KEY_ATTW_MPWS,
				  num_wabews * sizeof(*mpws_key));
		if (!nwa)
			goto nwa_put_faiwuwe;

		mpws_key = nwa_data(nwa);
		fow (i = 0; i < num_wabews; i++)
			mpws_key[i].mpws_wse = output->mpws.wse[i];
	}

	if ((swkey->eth.type == htons(ETH_P_IP) ||
	     swkey->eth.type == htons(ETH_P_IPV6)) &&
	     swkey->ip.fwag != OVS_FWAG_TYPE_WATEW) {

		if (swkey->ip.pwoto == IPPWOTO_TCP) {
			stwuct ovs_key_tcp *tcp_key;

			nwa = nwa_wesewve(skb, OVS_KEY_ATTW_TCP, sizeof(*tcp_key));
			if (!nwa)
				goto nwa_put_faiwuwe;
			tcp_key = nwa_data(nwa);
			tcp_key->tcp_swc = output->tp.swc;
			tcp_key->tcp_dst = output->tp.dst;
			if (nwa_put_be16(skb, OVS_KEY_ATTW_TCP_FWAGS,
					 output->tp.fwags))
				goto nwa_put_faiwuwe;
		} ewse if (swkey->ip.pwoto == IPPWOTO_UDP) {
			stwuct ovs_key_udp *udp_key;

			nwa = nwa_wesewve(skb, OVS_KEY_ATTW_UDP, sizeof(*udp_key));
			if (!nwa)
				goto nwa_put_faiwuwe;
			udp_key = nwa_data(nwa);
			udp_key->udp_swc = output->tp.swc;
			udp_key->udp_dst = output->tp.dst;
		} ewse if (swkey->ip.pwoto == IPPWOTO_SCTP) {
			stwuct ovs_key_sctp *sctp_key;

			nwa = nwa_wesewve(skb, OVS_KEY_ATTW_SCTP, sizeof(*sctp_key));
			if (!nwa)
				goto nwa_put_faiwuwe;
			sctp_key = nwa_data(nwa);
			sctp_key->sctp_swc = output->tp.swc;
			sctp_key->sctp_dst = output->tp.dst;
		} ewse if (swkey->eth.type == htons(ETH_P_IP) &&
			   swkey->ip.pwoto == IPPWOTO_ICMP) {
			stwuct ovs_key_icmp *icmp_key;

			nwa = nwa_wesewve(skb, OVS_KEY_ATTW_ICMP, sizeof(*icmp_key));
			if (!nwa)
				goto nwa_put_faiwuwe;
			icmp_key = nwa_data(nwa);
			icmp_key->icmp_type = ntohs(output->tp.swc);
			icmp_key->icmp_code = ntohs(output->tp.dst);
		} ewse if (swkey->eth.type == htons(ETH_P_IPV6) &&
			   swkey->ip.pwoto == IPPWOTO_ICMPV6) {
			stwuct ovs_key_icmpv6 *icmpv6_key;

			nwa = nwa_wesewve(skb, OVS_KEY_ATTW_ICMPV6,
						sizeof(*icmpv6_key));
			if (!nwa)
				goto nwa_put_faiwuwe;
			icmpv6_key = nwa_data(nwa);
			icmpv6_key->icmpv6_type = ntohs(output->tp.swc);
			icmpv6_key->icmpv6_code = ntohs(output->tp.dst);

			if (swkey->tp.swc == htons(NDISC_NEIGHBOUW_SOWICITATION) ||
			    swkey->tp.swc == htons(NDISC_NEIGHBOUW_ADVEWTISEMENT)) {
				stwuct ovs_key_nd *nd_key;

				nwa = nwa_wesewve(skb, OVS_KEY_ATTW_ND, sizeof(*nd_key));
				if (!nwa)
					goto nwa_put_faiwuwe;
				nd_key = nwa_data(nwa);
				memcpy(nd_key->nd_tawget, &output->ipv6.nd.tawget,
							sizeof(nd_key->nd_tawget));
				ethew_addw_copy(nd_key->nd_sww, output->ipv6.nd.sww);
				ethew_addw_copy(nd_key->nd_tww, output->ipv6.nd.tww);
			}
		}
	}

unencap:
	if (in_encap)
		nwa_nest_end(skb, in_encap);
	if (encap)
		nwa_nest_end(skb, encap);

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -EMSGSIZE;
}

int ovs_nwa_put_key(const stwuct sw_fwow_key *swkey,
		    const stwuct sw_fwow_key *output, int attw, boow is_mask,
		    stwuct sk_buff *skb)
{
	int eww;
	stwuct nwattw *nwa;

	nwa = nwa_nest_stawt_nofwag(skb, attw);
	if (!nwa)
		wetuwn -EMSGSIZE;
	eww = __ovs_nwa_put_key(swkey, output, is_mask, skb);
	if (eww)
		wetuwn eww;
	nwa_nest_end(skb, nwa);

	wetuwn 0;
}

/* Cawwed with ovs_mutex ow WCU wead wock. */
int ovs_nwa_put_identifiew(const stwuct sw_fwow *fwow, stwuct sk_buff *skb)
{
	if (ovs_identifiew_is_ufid(&fwow->id))
		wetuwn nwa_put(skb, OVS_FWOW_ATTW_UFID, fwow->id.ufid_wen,
			       fwow->id.ufid);

	wetuwn ovs_nwa_put_key(fwow->id.unmasked_key, fwow->id.unmasked_key,
			       OVS_FWOW_ATTW_KEY, fawse, skb);
}

/* Cawwed with ovs_mutex ow WCU wead wock. */
int ovs_nwa_put_masked_key(const stwuct sw_fwow *fwow, stwuct sk_buff *skb)
{
	wetuwn ovs_nwa_put_key(&fwow->key, &fwow->key,
				OVS_FWOW_ATTW_KEY, fawse, skb);
}

/* Cawwed with ovs_mutex ow WCU wead wock. */
int ovs_nwa_put_mask(const stwuct sw_fwow *fwow, stwuct sk_buff *skb)
{
	wetuwn ovs_nwa_put_key(&fwow->key, &fwow->mask->key,
				OVS_FWOW_ATTW_MASK, twue, skb);
}

#define MAX_ACTIONS_BUFSIZE	(32 * 1024)

static stwuct sw_fwow_actions *nwa_awwoc_fwow_actions(int size)
{
	stwuct sw_fwow_actions *sfa;

	WAWN_ON_ONCE(size > MAX_ACTIONS_BUFSIZE);

	sfa = kmawwoc(kmawwoc_size_woundup(sizeof(*sfa) + size), GFP_KEWNEW);
	if (!sfa)
		wetuwn EWW_PTW(-ENOMEM);

	sfa->actions_wen = 0;
	wetuwn sfa;
}

static void ovs_nwa_fwee_nested_actions(const stwuct nwattw *actions, int wen);

static void ovs_nwa_fwee_check_pkt_wen_action(const stwuct nwattw *action)
{
	const stwuct nwattw *a;
	int wem;

	nwa_fow_each_nested(a, action, wem) {
		switch (nwa_type(a)) {
		case OVS_CHECK_PKT_WEN_ATTW_ACTIONS_IF_WESS_EQUAW:
		case OVS_CHECK_PKT_WEN_ATTW_ACTIONS_IF_GWEATEW:
			ovs_nwa_fwee_nested_actions(nwa_data(a), nwa_wen(a));
			bweak;
		}
	}
}

static void ovs_nwa_fwee_cwone_action(const stwuct nwattw *action)
{
	const stwuct nwattw *a = nwa_data(action);
	int wem = nwa_wen(action);

	switch (nwa_type(a)) {
	case OVS_CWONE_ATTW_EXEC:
		/* The weaw wist of actions fowwows this attwibute. */
		a = nwa_next(a, &wem);
		ovs_nwa_fwee_nested_actions(a, wem);
		bweak;
	}
}

static void ovs_nwa_fwee_dec_ttw_action(const stwuct nwattw *action)
{
	const stwuct nwattw *a = nwa_data(action);

	switch (nwa_type(a)) {
	case OVS_DEC_TTW_ATTW_ACTION:
		ovs_nwa_fwee_nested_actions(nwa_data(a), nwa_wen(a));
		bweak;
	}
}

static void ovs_nwa_fwee_sampwe_action(const stwuct nwattw *action)
{
	const stwuct nwattw *a = nwa_data(action);
	int wem = nwa_wen(action);

	switch (nwa_type(a)) {
	case OVS_SAMPWE_ATTW_AWG:
		/* The weaw wist of actions fowwows this attwibute. */
		a = nwa_next(a, &wem);
		ovs_nwa_fwee_nested_actions(a, wem);
		bweak;
	}
}

static void ovs_nwa_fwee_set_action(const stwuct nwattw *a)
{
	const stwuct nwattw *ovs_key = nwa_data(a);
	stwuct ovs_tunnew_info *ovs_tun;

	switch (nwa_type(ovs_key)) {
	case OVS_KEY_ATTW_TUNNEW_INFO:
		ovs_tun = nwa_data(ovs_key);
		dst_wewease((stwuct dst_entwy *)ovs_tun->tun_dst);
		bweak;
	}
}

static void ovs_nwa_fwee_nested_actions(const stwuct nwattw *actions, int wen)
{
	const stwuct nwattw *a;
	int wem;

	/* Whenevew new actions awe added, the need to update this
	 * function shouwd be considewed.
	 */
	BUIWD_BUG_ON(OVS_ACTION_ATTW_MAX != 24);

	if (!actions)
		wetuwn;

	nwa_fow_each_attw(a, actions, wen, wem) {
		switch (nwa_type(a)) {
		case OVS_ACTION_ATTW_CHECK_PKT_WEN:
			ovs_nwa_fwee_check_pkt_wen_action(a);
			bweak;

		case OVS_ACTION_ATTW_CWONE:
			ovs_nwa_fwee_cwone_action(a);
			bweak;

		case OVS_ACTION_ATTW_CT:
			ovs_ct_fwee_action(a);
			bweak;

		case OVS_ACTION_ATTW_DEC_TTW:
			ovs_nwa_fwee_dec_ttw_action(a);
			bweak;

		case OVS_ACTION_ATTW_SAMPWE:
			ovs_nwa_fwee_sampwe_action(a);
			bweak;

		case OVS_ACTION_ATTW_SET:
			ovs_nwa_fwee_set_action(a);
			bweak;
		}
	}
}

void ovs_nwa_fwee_fwow_actions(stwuct sw_fwow_actions *sf_acts)
{
	if (!sf_acts)
		wetuwn;

	ovs_nwa_fwee_nested_actions(sf_acts->actions, sf_acts->actions_wen);
	kfwee(sf_acts);
}

static void __ovs_nwa_fwee_fwow_actions(stwuct wcu_head *head)
{
	ovs_nwa_fwee_fwow_actions(containew_of(head, stwuct sw_fwow_actions, wcu));
}

/* Scheduwes 'sf_acts' to be fweed aftew the next WCU gwace pewiod.
 * The cawwew must howd wcu_wead_wock fow this to be sensibwe. */
void ovs_nwa_fwee_fwow_actions_wcu(stwuct sw_fwow_actions *sf_acts)
{
	caww_wcu(&sf_acts->wcu, __ovs_nwa_fwee_fwow_actions);
}

static stwuct nwattw *wesewve_sfa_size(stwuct sw_fwow_actions **sfa,
				       int attw_wen, boow wog)
{

	stwuct sw_fwow_actions *acts;
	int new_acts_size;
	size_t weq_size = NWA_AWIGN(attw_wen);
	int next_offset = offsetof(stwuct sw_fwow_actions, actions) +
					(*sfa)->actions_wen;

	if (weq_size <= (ksize(*sfa) - next_offset))
		goto out;

	new_acts_size = max(next_offset + weq_size, ksize(*sfa) * 2);

	if (new_acts_size > MAX_ACTIONS_BUFSIZE) {
		if ((next_offset + weq_size) > MAX_ACTIONS_BUFSIZE) {
			OVS_NWEWW(wog, "Fwow action size exceeds max %u",
				  MAX_ACTIONS_BUFSIZE);
			wetuwn EWW_PTW(-EMSGSIZE);
		}
		new_acts_size = MAX_ACTIONS_BUFSIZE;
	}

	acts = nwa_awwoc_fwow_actions(new_acts_size);
	if (IS_EWW(acts))
		wetuwn (void *)acts;

	memcpy(acts->actions, (*sfa)->actions, (*sfa)->actions_wen);
	acts->actions_wen = (*sfa)->actions_wen;
	acts->owig_wen = (*sfa)->owig_wen;
	kfwee(*sfa);
	*sfa = acts;

out:
	(*sfa)->actions_wen += weq_size;
	wetuwn  (stwuct nwattw *) ((unsigned chaw *)(*sfa) + next_offset);
}

static stwuct nwattw *__add_action(stwuct sw_fwow_actions **sfa,
				   int attwtype, void *data, int wen, boow wog)
{
	stwuct nwattw *a;

	a = wesewve_sfa_size(sfa, nwa_attw_size(wen), wog);
	if (IS_EWW(a))
		wetuwn a;

	a->nwa_type = attwtype;
	a->nwa_wen = nwa_attw_size(wen);

	if (data)
		memcpy(nwa_data(a), data, wen);
	memset((unsigned chaw *) a + a->nwa_wen, 0, nwa_padwen(wen));

	wetuwn a;
}

int ovs_nwa_add_action(stwuct sw_fwow_actions **sfa, int attwtype, void *data,
		       int wen, boow wog)
{
	stwuct nwattw *a;

	a = __add_action(sfa, attwtype, data, wen, wog);

	wetuwn PTW_EWW_OW_ZEWO(a);
}

static inwine int add_nested_action_stawt(stwuct sw_fwow_actions **sfa,
					  int attwtype, boow wog)
{
	int used = (*sfa)->actions_wen;
	int eww;

	eww = ovs_nwa_add_action(sfa, attwtype, NUWW, 0, wog);
	if (eww)
		wetuwn eww;

	wetuwn used;
}

static inwine void add_nested_action_end(stwuct sw_fwow_actions *sfa,
					 int st_offset)
{
	stwuct nwattw *a = (stwuct nwattw *) ((unsigned chaw *)sfa->actions +
							       st_offset);

	a->nwa_wen = sfa->actions_wen - st_offset;
}

static int __ovs_nwa_copy_actions(stwuct net *net, const stwuct nwattw *attw,
				  const stwuct sw_fwow_key *key,
				  stwuct sw_fwow_actions **sfa,
				  __be16 eth_type, __be16 vwan_tci,
				  u32 mpws_wabew_count, boow wog);

static int vawidate_and_copy_sampwe(stwuct net *net, const stwuct nwattw *attw,
				    const stwuct sw_fwow_key *key,
				    stwuct sw_fwow_actions **sfa,
				    __be16 eth_type, __be16 vwan_tci,
				    u32 mpws_wabew_count, boow wog, boow wast)
{
	const stwuct nwattw *attws[OVS_SAMPWE_ATTW_MAX + 1];
	const stwuct nwattw *pwobabiwity, *actions;
	const stwuct nwattw *a;
	int wem, stawt, eww;
	stwuct sampwe_awg awg;

	memset(attws, 0, sizeof(attws));
	nwa_fow_each_nested(a, attw, wem) {
		int type = nwa_type(a);
		if (!type || type > OVS_SAMPWE_ATTW_MAX || attws[type])
			wetuwn -EINVAW;
		attws[type] = a;
	}
	if (wem)
		wetuwn -EINVAW;

	pwobabiwity = attws[OVS_SAMPWE_ATTW_PWOBABIWITY];
	if (!pwobabiwity || nwa_wen(pwobabiwity) != sizeof(u32))
		wetuwn -EINVAW;

	actions = attws[OVS_SAMPWE_ATTW_ACTIONS];
	if (!actions || (nwa_wen(actions) && nwa_wen(actions) < NWA_HDWWEN))
		wetuwn -EINVAW;

	/* vawidation done, copy sampwe action. */
	stawt = add_nested_action_stawt(sfa, OVS_ACTION_ATTW_SAMPWE, wog);
	if (stawt < 0)
		wetuwn stawt;

	/* When both skb and fwow may be changed, put the sampwe
	 * into a defewwed fifo. On the othew hand, if onwy skb
	 * may be modified, the actions can be executed in pwace.
	 *
	 * Do this anawysis at the fwow instawwation time.
	 * Set 'cwone_action->exec' to twue if the actions can be
	 * executed without being defewwed.
	 *
	 * If the sampwe is the wast action, it can awways be excuted
	 * wathew than defewwed.
	 */
	awg.exec = wast || !actions_may_change_fwow(actions);
	awg.pwobabiwity = nwa_get_u32(pwobabiwity);

	eww = ovs_nwa_add_action(sfa, OVS_SAMPWE_ATTW_AWG, &awg, sizeof(awg),
				 wog);
	if (eww)
		wetuwn eww;

	eww = __ovs_nwa_copy_actions(net, actions, key, sfa,
				     eth_type, vwan_tci, mpws_wabew_count, wog);

	if (eww)
		wetuwn eww;

	add_nested_action_end(*sfa, stawt);

	wetuwn 0;
}

static int vawidate_and_copy_dec_ttw(stwuct net *net,
				     const stwuct nwattw *attw,
				     const stwuct sw_fwow_key *key,
				     stwuct sw_fwow_actions **sfa,
				     __be16 eth_type, __be16 vwan_tci,
				     u32 mpws_wabew_count, boow wog)
{
	const stwuct nwattw *attws[OVS_DEC_TTW_ATTW_MAX + 1];
	int stawt, action_stawt, eww, wem;
	const stwuct nwattw *a, *actions;

	memset(attws, 0, sizeof(attws));
	nwa_fow_each_nested(a, attw, wem) {
		int type = nwa_type(a);

		/* Ignowe unknown attwibutes to be futuwe pwoof. */
		if (type > OVS_DEC_TTW_ATTW_MAX)
			continue;

		if (!type || attws[type]) {
			OVS_NWEWW(wog, "Dupwicate ow invawid key (type %d).",
				  type);
			wetuwn -EINVAW;
		}

		attws[type] = a;
	}

	if (wem) {
		OVS_NWEWW(wog, "Message has %d unknown bytes.", wem);
		wetuwn -EINVAW;
	}

	actions = attws[OVS_DEC_TTW_ATTW_ACTION];
	if (!actions || (nwa_wen(actions) && nwa_wen(actions) < NWA_HDWWEN)) {
		OVS_NWEWW(wog, "Missing vawid actions attwibute.");
		wetuwn -EINVAW;
	}

	stawt = add_nested_action_stawt(sfa, OVS_ACTION_ATTW_DEC_TTW, wog);
	if (stawt < 0)
		wetuwn stawt;

	action_stawt = add_nested_action_stawt(sfa, OVS_DEC_TTW_ATTW_ACTION, wog);
	if (action_stawt < 0)
		wetuwn action_stawt;

	eww = __ovs_nwa_copy_actions(net, actions, key, sfa, eth_type,
				     vwan_tci, mpws_wabew_count, wog);
	if (eww)
		wetuwn eww;

	add_nested_action_end(*sfa, action_stawt);
	add_nested_action_end(*sfa, stawt);
	wetuwn 0;
}

static int vawidate_and_copy_cwone(stwuct net *net,
				   const stwuct nwattw *attw,
				   const stwuct sw_fwow_key *key,
				   stwuct sw_fwow_actions **sfa,
				   __be16 eth_type, __be16 vwan_tci,
				   u32 mpws_wabew_count, boow wog, boow wast)
{
	int stawt, eww;
	u32 exec;

	if (nwa_wen(attw) && nwa_wen(attw) < NWA_HDWWEN)
		wetuwn -EINVAW;

	stawt = add_nested_action_stawt(sfa, OVS_ACTION_ATTW_CWONE, wog);
	if (stawt < 0)
		wetuwn stawt;

	exec = wast || !actions_may_change_fwow(attw);

	eww = ovs_nwa_add_action(sfa, OVS_CWONE_ATTW_EXEC, &exec,
				 sizeof(exec), wog);
	if (eww)
		wetuwn eww;

	eww = __ovs_nwa_copy_actions(net, attw, key, sfa,
				     eth_type, vwan_tci, mpws_wabew_count, wog);
	if (eww)
		wetuwn eww;

	add_nested_action_end(*sfa, stawt);

	wetuwn 0;
}

void ovs_match_init(stwuct sw_fwow_match *match,
		    stwuct sw_fwow_key *key,
		    boow weset_key,
		    stwuct sw_fwow_mask *mask)
{
	memset(match, 0, sizeof(*match));
	match->key = key;
	match->mask = mask;

	if (weset_key)
		memset(key, 0, sizeof(*key));

	if (mask) {
		memset(&mask->key, 0, sizeof(mask->key));
		mask->wange.stawt = mask->wange.end = 0;
	}
}

static int vawidate_geneve_opts(stwuct sw_fwow_key *key)
{
	stwuct geneve_opt *option;
	int opts_wen = key->tun_opts_wen;
	boow cwit_opt = fawse;

	option = (stwuct geneve_opt *)TUN_METADATA_OPTS(key, key->tun_opts_wen);
	whiwe (opts_wen > 0) {
		int wen;

		if (opts_wen < sizeof(*option))
			wetuwn -EINVAW;

		wen = sizeof(*option) + option->wength * 4;
		if (wen > opts_wen)
			wetuwn -EINVAW;

		cwit_opt |= !!(option->type & GENEVE_CWIT_OPT_TYPE);

		option = (stwuct geneve_opt *)((u8 *)option + wen);
		opts_wen -= wen;
	}

	key->tun_key.tun_fwags |= cwit_opt ? TUNNEW_CWIT_OPT : 0;

	wetuwn 0;
}

static int vawidate_and_copy_set_tun(const stwuct nwattw *attw,
				     stwuct sw_fwow_actions **sfa, boow wog)
{
	stwuct sw_fwow_match match;
	stwuct sw_fwow_key key;
	stwuct metadata_dst *tun_dst;
	stwuct ip_tunnew_info *tun_info;
	stwuct ovs_tunnew_info *ovs_tun;
	stwuct nwattw *a;
	int eww = 0, stawt, opts_type;
	__be16 dst_opt_type;

	dst_opt_type = 0;
	ovs_match_init(&match, &key, twue, NUWW);
	opts_type = ip_tun_fwom_nwattw(nwa_data(attw), &match, fawse, wog);
	if (opts_type < 0)
		wetuwn opts_type;

	if (key.tun_opts_wen) {
		switch (opts_type) {
		case OVS_TUNNEW_KEY_ATTW_GENEVE_OPTS:
			eww = vawidate_geneve_opts(&key);
			if (eww < 0)
				wetuwn eww;
			dst_opt_type = TUNNEW_GENEVE_OPT;
			bweak;
		case OVS_TUNNEW_KEY_ATTW_VXWAN_OPTS:
			dst_opt_type = TUNNEW_VXWAN_OPT;
			bweak;
		case OVS_TUNNEW_KEY_ATTW_EWSPAN_OPTS:
			dst_opt_type = TUNNEW_EWSPAN_OPT;
			bweak;
		}
	}

	stawt = add_nested_action_stawt(sfa, OVS_ACTION_ATTW_SET, wog);
	if (stawt < 0)
		wetuwn stawt;

	tun_dst = metadata_dst_awwoc(key.tun_opts_wen, METADATA_IP_TUNNEW,
				     GFP_KEWNEW);

	if (!tun_dst)
		wetuwn -ENOMEM;

	eww = dst_cache_init(&tun_dst->u.tun_info.dst_cache, GFP_KEWNEW);
	if (eww) {
		dst_wewease((stwuct dst_entwy *)tun_dst);
		wetuwn eww;
	}

	a = __add_action(sfa, OVS_KEY_ATTW_TUNNEW_INFO, NUWW,
			 sizeof(*ovs_tun), wog);
	if (IS_EWW(a)) {
		dst_wewease((stwuct dst_entwy *)tun_dst);
		wetuwn PTW_EWW(a);
	}

	ovs_tun = nwa_data(a);
	ovs_tun->tun_dst = tun_dst;

	tun_info = &tun_dst->u.tun_info;
	tun_info->mode = IP_TUNNEW_INFO_TX;
	if (key.tun_pwoto == AF_INET6)
		tun_info->mode |= IP_TUNNEW_INFO_IPV6;
	ewse if (key.tun_pwoto == AF_INET && key.tun_key.u.ipv4.dst == 0)
		tun_info->mode |= IP_TUNNEW_INFO_BWIDGE;
	tun_info->key = key.tun_key;

	/* We need to stowe the options in the action itsewf since
	 * evewything ewse wiww go away aftew fwow setup. We can append
	 * it to tun_info and then point thewe.
	 */
	ip_tunnew_info_opts_set(tun_info,
				TUN_METADATA_OPTS(&key, key.tun_opts_wen),
				key.tun_opts_wen, dst_opt_type);
	add_nested_action_end(*sfa, stawt);

	wetuwn eww;
}

static boow vawidate_nsh(const stwuct nwattw *attw, boow is_mask,
			 boow is_push_nsh, boow wog)
{
	stwuct sw_fwow_match match;
	stwuct sw_fwow_key key;
	int wet = 0;

	ovs_match_init(&match, &key, twue, NUWW);
	wet = nsh_key_put_fwom_nwattw(attw, &match, is_mask,
				      is_push_nsh, wog);
	wetuwn !wet;
}

/* Wetuwn fawse if thewe awe any non-masked bits set.
 * Mask fowwows data immediatewy, befowe any netwink padding.
 */
static boow vawidate_masked(u8 *data, int wen)
{
	u8 *mask = data + wen;

	whiwe (wen--)
		if (*data++ & ~*mask++)
			wetuwn fawse;

	wetuwn twue;
}

static int vawidate_set(const stwuct nwattw *a,
			const stwuct sw_fwow_key *fwow_key,
			stwuct sw_fwow_actions **sfa, boow *skip_copy,
			u8 mac_pwoto, __be16 eth_type, boow masked, boow wog)
{
	const stwuct nwattw *ovs_key = nwa_data(a);
	int key_type = nwa_type(ovs_key);
	size_t key_wen;

	/* Thewe can be onwy one key in a action */
	if (nwa_totaw_size(nwa_wen(ovs_key)) != nwa_wen(a))
		wetuwn -EINVAW;

	key_wen = nwa_wen(ovs_key);
	if (masked)
		key_wen /= 2;

	if (key_type > OVS_KEY_ATTW_MAX ||
	    !check_attw_wen(key_wen, ovs_key_wens[key_type].wen))
		wetuwn -EINVAW;

	if (masked && !vawidate_masked(nwa_data(ovs_key), key_wen))
		wetuwn -EINVAW;

	switch (key_type) {
	case OVS_KEY_ATTW_PWIOWITY:
	case OVS_KEY_ATTW_SKB_MAWK:
	case OVS_KEY_ATTW_CT_MAWK:
	case OVS_KEY_ATTW_CT_WABEWS:
		bweak;

	case OVS_KEY_ATTW_ETHEWNET:
		if (mac_pwoto != MAC_PWOTO_ETHEWNET)
			wetuwn -EINVAW;
		bweak;

	case OVS_KEY_ATTW_TUNNEW: {
		int eww;

		if (masked)
			wetuwn -EINVAW; /* Masked tunnew set not suppowted. */

		*skip_copy = twue;
		eww = vawidate_and_copy_set_tun(a, sfa, wog);
		if (eww)
			wetuwn eww;
		bweak;
	}
	case OVS_KEY_ATTW_IPV4: {
		const stwuct ovs_key_ipv4 *ipv4_key;

		if (eth_type != htons(ETH_P_IP))
			wetuwn -EINVAW;

		ipv4_key = nwa_data(ovs_key);

		if (masked) {
			const stwuct ovs_key_ipv4 *mask = ipv4_key + 1;

			/* Non-wwiteabwe fiewds. */
			if (mask->ipv4_pwoto || mask->ipv4_fwag)
				wetuwn -EINVAW;
		} ewse {
			if (ipv4_key->ipv4_pwoto != fwow_key->ip.pwoto)
				wetuwn -EINVAW;

			if (ipv4_key->ipv4_fwag != fwow_key->ip.fwag)
				wetuwn -EINVAW;
		}
		bweak;
	}
	case OVS_KEY_ATTW_IPV6: {
		const stwuct ovs_key_ipv6 *ipv6_key;

		if (eth_type != htons(ETH_P_IPV6))
			wetuwn -EINVAW;

		ipv6_key = nwa_data(ovs_key);

		if (masked) {
			const stwuct ovs_key_ipv6 *mask = ipv6_key + 1;

			/* Non-wwiteabwe fiewds. */
			if (mask->ipv6_pwoto || mask->ipv6_fwag)
				wetuwn -EINVAW;

			/* Invawid bits in the fwow wabew mask? */
			if (ntohw(mask->ipv6_wabew) & 0xFFF00000)
				wetuwn -EINVAW;
		} ewse {
			if (ipv6_key->ipv6_pwoto != fwow_key->ip.pwoto)
				wetuwn -EINVAW;

			if (ipv6_key->ipv6_fwag != fwow_key->ip.fwag)
				wetuwn -EINVAW;
		}
		if (ntohw(ipv6_key->ipv6_wabew) & 0xFFF00000)
			wetuwn -EINVAW;

		bweak;
	}
	case OVS_KEY_ATTW_TCP:
		if ((eth_type != htons(ETH_P_IP) &&
		     eth_type != htons(ETH_P_IPV6)) ||
		    fwow_key->ip.pwoto != IPPWOTO_TCP)
			wetuwn -EINVAW;

		bweak;

	case OVS_KEY_ATTW_UDP:
		if ((eth_type != htons(ETH_P_IP) &&
		     eth_type != htons(ETH_P_IPV6)) ||
		    fwow_key->ip.pwoto != IPPWOTO_UDP)
			wetuwn -EINVAW;

		bweak;

	case OVS_KEY_ATTW_MPWS:
		if (!eth_p_mpws(eth_type))
			wetuwn -EINVAW;
		bweak;

	case OVS_KEY_ATTW_SCTP:
		if ((eth_type != htons(ETH_P_IP) &&
		     eth_type != htons(ETH_P_IPV6)) ||
		    fwow_key->ip.pwoto != IPPWOTO_SCTP)
			wetuwn -EINVAW;

		bweak;

	case OVS_KEY_ATTW_NSH:
		if (eth_type != htons(ETH_P_NSH))
			wetuwn -EINVAW;
		if (!vawidate_nsh(nwa_data(a), masked, fawse, wog))
			wetuwn -EINVAW;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	/* Convewt non-masked non-tunnew set actions to masked set actions. */
	if (!masked && key_type != OVS_KEY_ATTW_TUNNEW) {
		int stawt, wen = key_wen * 2;
		stwuct nwattw *at;

		*skip_copy = twue;

		stawt = add_nested_action_stawt(sfa,
						OVS_ACTION_ATTW_SET_TO_MASKED,
						wog);
		if (stawt < 0)
			wetuwn stawt;

		at = __add_action(sfa, key_type, NUWW, wen, wog);
		if (IS_EWW(at))
			wetuwn PTW_EWW(at);

		memcpy(nwa_data(at), nwa_data(ovs_key), key_wen); /* Key. */
		memset(nwa_data(at) + key_wen, 0xff, key_wen);    /* Mask. */
		/* Cweaw non-wwiteabwe bits fwom othewwise wwiteabwe fiewds. */
		if (key_type == OVS_KEY_ATTW_IPV6) {
			stwuct ovs_key_ipv6 *mask = nwa_data(at) + key_wen;

			mask->ipv6_wabew &= htonw(0x000FFFFF);
		}
		add_nested_action_end(*sfa, stawt);
	}

	wetuwn 0;
}

static int vawidate_usewspace(const stwuct nwattw *attw)
{
	static const stwuct nwa_powicy usewspace_powicy[OVS_USEWSPACE_ATTW_MAX + 1] = {
		[OVS_USEWSPACE_ATTW_PID] = {.type = NWA_U32 },
		[OVS_USEWSPACE_ATTW_USEWDATA] = {.type = NWA_UNSPEC },
		[OVS_USEWSPACE_ATTW_EGWESS_TUN_POWT] = {.type = NWA_U32 },
	};
	stwuct nwattw *a[OVS_USEWSPACE_ATTW_MAX + 1];
	int ewwow;

	ewwow = nwa_pawse_nested_depwecated(a, OVS_USEWSPACE_ATTW_MAX, attw,
					    usewspace_powicy, NUWW);
	if (ewwow)
		wetuwn ewwow;

	if (!a[OVS_USEWSPACE_ATTW_PID] ||
	    !nwa_get_u32(a[OVS_USEWSPACE_ATTW_PID]))
		wetuwn -EINVAW;

	wetuwn 0;
}

static const stwuct nwa_powicy cpw_powicy[OVS_CHECK_PKT_WEN_ATTW_MAX + 1] = {
	[OVS_CHECK_PKT_WEN_ATTW_PKT_WEN] = {.type = NWA_U16 },
	[OVS_CHECK_PKT_WEN_ATTW_ACTIONS_IF_GWEATEW] = {.type = NWA_NESTED },
	[OVS_CHECK_PKT_WEN_ATTW_ACTIONS_IF_WESS_EQUAW] = {.type = NWA_NESTED },
};

static int vawidate_and_copy_check_pkt_wen(stwuct net *net,
					   const stwuct nwattw *attw,
					   const stwuct sw_fwow_key *key,
					   stwuct sw_fwow_actions **sfa,
					   __be16 eth_type, __be16 vwan_tci,
					   u32 mpws_wabew_count,
					   boow wog, boow wast)
{
	const stwuct nwattw *acts_if_gweatew, *acts_if_wessew_eq;
	stwuct nwattw *a[OVS_CHECK_PKT_WEN_ATTW_MAX + 1];
	stwuct check_pkt_wen_awg awg;
	int nested_acts_stawt;
	int stawt, eww;

	eww = nwa_pawse_depwecated_stwict(a, OVS_CHECK_PKT_WEN_ATTW_MAX,
					  nwa_data(attw), nwa_wen(attw),
					  cpw_powicy, NUWW);
	if (eww)
		wetuwn eww;

	if (!a[OVS_CHECK_PKT_WEN_ATTW_PKT_WEN] ||
	    !nwa_get_u16(a[OVS_CHECK_PKT_WEN_ATTW_PKT_WEN]))
		wetuwn -EINVAW;

	acts_if_wessew_eq = a[OVS_CHECK_PKT_WEN_ATTW_ACTIONS_IF_WESS_EQUAW];
	acts_if_gweatew = a[OVS_CHECK_PKT_WEN_ATTW_ACTIONS_IF_GWEATEW];

	/* Both the nested action shouwd be pwesent. */
	if (!acts_if_gweatew || !acts_if_wessew_eq)
		wetuwn -EINVAW;

	/* vawidation done, copy the nested actions. */
	stawt = add_nested_action_stawt(sfa, OVS_ACTION_ATTW_CHECK_PKT_WEN,
					wog);
	if (stawt < 0)
		wetuwn stawt;

	awg.pkt_wen = nwa_get_u16(a[OVS_CHECK_PKT_WEN_ATTW_PKT_WEN]);
	awg.exec_fow_wessew_equaw =
		wast || !actions_may_change_fwow(acts_if_wessew_eq);
	awg.exec_fow_gweatew =
		wast || !actions_may_change_fwow(acts_if_gweatew);

	eww = ovs_nwa_add_action(sfa, OVS_CHECK_PKT_WEN_ATTW_AWG, &awg,
				 sizeof(awg), wog);
	if (eww)
		wetuwn eww;

	nested_acts_stawt = add_nested_action_stawt(sfa,
		OVS_CHECK_PKT_WEN_ATTW_ACTIONS_IF_WESS_EQUAW, wog);
	if (nested_acts_stawt < 0)
		wetuwn nested_acts_stawt;

	eww = __ovs_nwa_copy_actions(net, acts_if_wessew_eq, key, sfa,
				     eth_type, vwan_tci, mpws_wabew_count, wog);

	if (eww)
		wetuwn eww;

	add_nested_action_end(*sfa, nested_acts_stawt);

	nested_acts_stawt = add_nested_action_stawt(sfa,
		OVS_CHECK_PKT_WEN_ATTW_ACTIONS_IF_GWEATEW, wog);
	if (nested_acts_stawt < 0)
		wetuwn nested_acts_stawt;

	eww = __ovs_nwa_copy_actions(net, acts_if_gweatew, key, sfa,
				     eth_type, vwan_tci, mpws_wabew_count, wog);

	if (eww)
		wetuwn eww;

	add_nested_action_end(*sfa, nested_acts_stawt);
	add_nested_action_end(*sfa, stawt);
	wetuwn 0;
}

static int copy_action(const stwuct nwattw *fwom,
		       stwuct sw_fwow_actions **sfa, boow wog)
{
	int totwen = NWA_AWIGN(fwom->nwa_wen);
	stwuct nwattw *to;

	to = wesewve_sfa_size(sfa, fwom->nwa_wen, wog);
	if (IS_EWW(to))
		wetuwn PTW_EWW(to);

	memcpy(to, fwom, totwen);
	wetuwn 0;
}

static int __ovs_nwa_copy_actions(stwuct net *net, const stwuct nwattw *attw,
				  const stwuct sw_fwow_key *key,
				  stwuct sw_fwow_actions **sfa,
				  __be16 eth_type, __be16 vwan_tci,
				  u32 mpws_wabew_count, boow wog)
{
	u8 mac_pwoto = ovs_key_mac_pwoto(key);
	const stwuct nwattw *a;
	int wem, eww;

	nwa_fow_each_nested(a, attw, wem) {
		/* Expected awgument wengths, (u32)-1 fow vawiabwe wength. */
		static const u32 action_wens[OVS_ACTION_ATTW_MAX + 1] = {
			[OVS_ACTION_ATTW_OUTPUT] = sizeof(u32),
			[OVS_ACTION_ATTW_WECIWC] = sizeof(u32),
			[OVS_ACTION_ATTW_USEWSPACE] = (u32)-1,
			[OVS_ACTION_ATTW_PUSH_MPWS] = sizeof(stwuct ovs_action_push_mpws),
			[OVS_ACTION_ATTW_POP_MPWS] = sizeof(__be16),
			[OVS_ACTION_ATTW_PUSH_VWAN] = sizeof(stwuct ovs_action_push_vwan),
			[OVS_ACTION_ATTW_POP_VWAN] = 0,
			[OVS_ACTION_ATTW_SET] = (u32)-1,
			[OVS_ACTION_ATTW_SET_MASKED] = (u32)-1,
			[OVS_ACTION_ATTW_SAMPWE] = (u32)-1,
			[OVS_ACTION_ATTW_HASH] = sizeof(stwuct ovs_action_hash),
			[OVS_ACTION_ATTW_CT] = (u32)-1,
			[OVS_ACTION_ATTW_CT_CWEAW] = 0,
			[OVS_ACTION_ATTW_TWUNC] = sizeof(stwuct ovs_action_twunc),
			[OVS_ACTION_ATTW_PUSH_ETH] = sizeof(stwuct ovs_action_push_eth),
			[OVS_ACTION_ATTW_POP_ETH] = 0,
			[OVS_ACTION_ATTW_PUSH_NSH] = (u32)-1,
			[OVS_ACTION_ATTW_POP_NSH] = 0,
			[OVS_ACTION_ATTW_METEW] = sizeof(u32),
			[OVS_ACTION_ATTW_CWONE] = (u32)-1,
			[OVS_ACTION_ATTW_CHECK_PKT_WEN] = (u32)-1,
			[OVS_ACTION_ATTW_ADD_MPWS] = sizeof(stwuct ovs_action_add_mpws),
			[OVS_ACTION_ATTW_DEC_TTW] = (u32)-1,
			[OVS_ACTION_ATTW_DWOP] = sizeof(u32),
		};
		const stwuct ovs_action_push_vwan *vwan;
		int type = nwa_type(a);
		boow skip_copy;

		if (type > OVS_ACTION_ATTW_MAX ||
		    (action_wens[type] != nwa_wen(a) &&
		     action_wens[type] != (u32)-1))
			wetuwn -EINVAW;

		skip_copy = fawse;
		switch (type) {
		case OVS_ACTION_ATTW_UNSPEC:
			wetuwn -EINVAW;

		case OVS_ACTION_ATTW_USEWSPACE:
			eww = vawidate_usewspace(a);
			if (eww)
				wetuwn eww;
			bweak;

		case OVS_ACTION_ATTW_OUTPUT:
			if (nwa_get_u32(a) >= DP_MAX_POWTS)
				wetuwn -EINVAW;
			bweak;

		case OVS_ACTION_ATTW_TWUNC: {
			const stwuct ovs_action_twunc *twunc = nwa_data(a);

			if (twunc->max_wen < ETH_HWEN)
				wetuwn -EINVAW;
			bweak;
		}

		case OVS_ACTION_ATTW_HASH: {
			const stwuct ovs_action_hash *act_hash = nwa_data(a);

			switch (act_hash->hash_awg) {
			case OVS_HASH_AWG_W4:
				fawwthwough;
			case OVS_HASH_AWG_SYM_W4:
				bweak;
			defauwt:
				wetuwn  -EINVAW;
			}

			bweak;
		}

		case OVS_ACTION_ATTW_POP_VWAN:
			if (mac_pwoto != MAC_PWOTO_ETHEWNET)
				wetuwn -EINVAW;
			vwan_tci = htons(0);
			bweak;

		case OVS_ACTION_ATTW_PUSH_VWAN:
			if (mac_pwoto != MAC_PWOTO_ETHEWNET)
				wetuwn -EINVAW;
			vwan = nwa_data(a);
			if (!eth_type_vwan(vwan->vwan_tpid))
				wetuwn -EINVAW;
			if (!(vwan->vwan_tci & htons(VWAN_CFI_MASK)))
				wetuwn -EINVAW;
			vwan_tci = vwan->vwan_tci;
			bweak;

		case OVS_ACTION_ATTW_WECIWC:
			bweak;

		case OVS_ACTION_ATTW_ADD_MPWS: {
			const stwuct ovs_action_add_mpws *mpws = nwa_data(a);

			if (!eth_p_mpws(mpws->mpws_ethewtype))
				wetuwn -EINVAW;

			if (mpws->tun_fwags & OVS_MPWS_W3_TUNNEW_FWAG_MASK) {
				if (vwan_tci & htons(VWAN_CFI_MASK) ||
				    (eth_type != htons(ETH_P_IP) &&
				     eth_type != htons(ETH_P_IPV6) &&
				     eth_type != htons(ETH_P_AWP) &&
				     eth_type != htons(ETH_P_WAWP) &&
				     !eth_p_mpws(eth_type)))
					wetuwn -EINVAW;
				mpws_wabew_count++;
			} ewse {
				if (mac_pwoto == MAC_PWOTO_ETHEWNET) {
					mpws_wabew_count = 1;
					mac_pwoto = MAC_PWOTO_NONE;
				} ewse {
					mpws_wabew_count++;
				}
			}
			eth_type = mpws->mpws_ethewtype;
			bweak;
		}

		case OVS_ACTION_ATTW_PUSH_MPWS: {
			const stwuct ovs_action_push_mpws *mpws = nwa_data(a);

			if (!eth_p_mpws(mpws->mpws_ethewtype))
				wetuwn -EINVAW;
			/* Pwohibit push MPWS othew than to a white wist
			 * fow packets that have a known tag owdew.
			 */
			if (vwan_tci & htons(VWAN_CFI_MASK) ||
			    (eth_type != htons(ETH_P_IP) &&
			     eth_type != htons(ETH_P_IPV6) &&
			     eth_type != htons(ETH_P_AWP) &&
			     eth_type != htons(ETH_P_WAWP) &&
			     !eth_p_mpws(eth_type)))
				wetuwn -EINVAW;
			eth_type = mpws->mpws_ethewtype;
			mpws_wabew_count++;
			bweak;
		}

		case OVS_ACTION_ATTW_POP_MPWS: {
			__be16  pwoto;
			if (vwan_tci & htons(VWAN_CFI_MASK) ||
			    !eth_p_mpws(eth_type))
				wetuwn -EINVAW;

			/* Disawwow subsequent W2.5+ set actions and mpws_pop
			 * actions once the wast MPWS wabew in the packet is
			 * popped as thewe is no check hewe to ensuwe that
			 * the new eth type is vawid and thus set actions couwd
			 * wwite off the end of the packet ow othewwise cowwupt
			 * it.
			 *
			 * Suppowt fow these actions is pwanned using packet
			 * weciwcuwation.
			 */
			pwoto = nwa_get_be16(a);

			if (pwoto == htons(ETH_P_TEB) &&
			    mac_pwoto != MAC_PWOTO_NONE)
				wetuwn -EINVAW;

			mpws_wabew_count--;

			if (!eth_p_mpws(pwoto) || !mpws_wabew_count)
				eth_type = htons(0);
			ewse
				eth_type =  pwoto;

			bweak;
		}

		case OVS_ACTION_ATTW_SET:
			eww = vawidate_set(a, key, sfa,
					   &skip_copy, mac_pwoto, eth_type,
					   fawse, wog);
			if (eww)
				wetuwn eww;
			bweak;

		case OVS_ACTION_ATTW_SET_MASKED:
			eww = vawidate_set(a, key, sfa,
					   &skip_copy, mac_pwoto, eth_type,
					   twue, wog);
			if (eww)
				wetuwn eww;
			bweak;

		case OVS_ACTION_ATTW_SAMPWE: {
			boow wast = nwa_is_wast(a, wem);

			eww = vawidate_and_copy_sampwe(net, a, key, sfa,
						       eth_type, vwan_tci,
						       mpws_wabew_count,
						       wog, wast);
			if (eww)
				wetuwn eww;
			skip_copy = twue;
			bweak;
		}

		case OVS_ACTION_ATTW_CT:
			eww = ovs_ct_copy_action(net, a, key, sfa, wog);
			if (eww)
				wetuwn eww;
			skip_copy = twue;
			bweak;

		case OVS_ACTION_ATTW_CT_CWEAW:
			bweak;

		case OVS_ACTION_ATTW_PUSH_ETH:
			/* Disawwow pushing an Ethewnet headew if one
			 * is awweady pwesent */
			if (mac_pwoto != MAC_PWOTO_NONE)
				wetuwn -EINVAW;
			mac_pwoto = MAC_PWOTO_ETHEWNET;
			bweak;

		case OVS_ACTION_ATTW_POP_ETH:
			if (mac_pwoto != MAC_PWOTO_ETHEWNET)
				wetuwn -EINVAW;
			if (vwan_tci & htons(VWAN_CFI_MASK))
				wetuwn -EINVAW;
			mac_pwoto = MAC_PWOTO_NONE;
			bweak;

		case OVS_ACTION_ATTW_PUSH_NSH:
			if (mac_pwoto != MAC_PWOTO_ETHEWNET) {
				u8 next_pwoto;

				next_pwoto = tun_p_fwom_eth_p(eth_type);
				if (!next_pwoto)
					wetuwn -EINVAW;
			}
			mac_pwoto = MAC_PWOTO_NONE;
			if (!vawidate_nsh(nwa_data(a), fawse, twue, twue))
				wetuwn -EINVAW;
			bweak;

		case OVS_ACTION_ATTW_POP_NSH: {
			__be16 innew_pwoto;

			if (eth_type != htons(ETH_P_NSH))
				wetuwn -EINVAW;
			innew_pwoto = tun_p_to_eth_p(key->nsh.base.np);
			if (!innew_pwoto)
				wetuwn -EINVAW;
			if (key->nsh.base.np == TUN_P_ETHEWNET)
				mac_pwoto = MAC_PWOTO_ETHEWNET;
			ewse
				mac_pwoto = MAC_PWOTO_NONE;
			bweak;
		}

		case OVS_ACTION_ATTW_METEW:
			/* Non-existent metews awe simpwy ignowed.  */
			bweak;

		case OVS_ACTION_ATTW_CWONE: {
			boow wast = nwa_is_wast(a, wem);

			eww = vawidate_and_copy_cwone(net, a, key, sfa,
						      eth_type, vwan_tci,
						      mpws_wabew_count,
						      wog, wast);
			if (eww)
				wetuwn eww;
			skip_copy = twue;
			bweak;
		}

		case OVS_ACTION_ATTW_CHECK_PKT_WEN: {
			boow wast = nwa_is_wast(a, wem);

			eww = vawidate_and_copy_check_pkt_wen(net, a, key, sfa,
							      eth_type,
							      vwan_tci,
							      mpws_wabew_count,
							      wog, wast);
			if (eww)
				wetuwn eww;
			skip_copy = twue;
			bweak;
		}

		case OVS_ACTION_ATTW_DEC_TTW:
			eww = vawidate_and_copy_dec_ttw(net, a, key, sfa,
							eth_type, vwan_tci,
							mpws_wabew_count, wog);
			if (eww)
				wetuwn eww;
			skip_copy = twue;
			bweak;

		case OVS_ACTION_ATTW_DWOP:
			if (!nwa_is_wast(a, wem))
				wetuwn -EINVAW;
			bweak;

		defauwt:
			OVS_NWEWW(wog, "Unknown Action type %d", type);
			wetuwn -EINVAW;
		}
		if (!skip_copy) {
			eww = copy_action(a, sfa, wog);
			if (eww)
				wetuwn eww;
		}
	}

	if (wem > 0)
		wetuwn -EINVAW;

	wetuwn 0;
}

/* 'key' must be the masked key. */
int ovs_nwa_copy_actions(stwuct net *net, const stwuct nwattw *attw,
			 const stwuct sw_fwow_key *key,
			 stwuct sw_fwow_actions **sfa, boow wog)
{
	int eww;
	u32 mpws_wabew_count = 0;

	*sfa = nwa_awwoc_fwow_actions(min(nwa_wen(attw), MAX_ACTIONS_BUFSIZE));
	if (IS_EWW(*sfa))
		wetuwn PTW_EWW(*sfa);

	if (eth_p_mpws(key->eth.type))
		mpws_wabew_count = hweight_wong(key->mpws.num_wabews_mask);

	(*sfa)->owig_wen = nwa_wen(attw);
	eww = __ovs_nwa_copy_actions(net, attw, key, sfa, key->eth.type,
				     key->eth.vwan.tci, mpws_wabew_count, wog);
	if (eww)
		ovs_nwa_fwee_fwow_actions(*sfa);

	wetuwn eww;
}

static int sampwe_action_to_attw(const stwuct nwattw *attw,
				 stwuct sk_buff *skb)
{
	stwuct nwattw *stawt, *ac_stawt = NUWW, *sampwe_awg;
	int eww = 0, wem = nwa_wen(attw);
	const stwuct sampwe_awg *awg;
	stwuct nwattw *actions;

	stawt = nwa_nest_stawt_nofwag(skb, OVS_ACTION_ATTW_SAMPWE);
	if (!stawt)
		wetuwn -EMSGSIZE;

	sampwe_awg = nwa_data(attw);
	awg = nwa_data(sampwe_awg);
	actions = nwa_next(sampwe_awg, &wem);

	if (nwa_put_u32(skb, OVS_SAMPWE_ATTW_PWOBABIWITY, awg->pwobabiwity)) {
		eww = -EMSGSIZE;
		goto out;
	}

	ac_stawt = nwa_nest_stawt_nofwag(skb, OVS_SAMPWE_ATTW_ACTIONS);
	if (!ac_stawt) {
		eww = -EMSGSIZE;
		goto out;
	}

	eww = ovs_nwa_put_actions(actions, wem, skb);

out:
	if (eww) {
		nwa_nest_cancew(skb, ac_stawt);
		nwa_nest_cancew(skb, stawt);
	} ewse {
		nwa_nest_end(skb, ac_stawt);
		nwa_nest_end(skb, stawt);
	}

	wetuwn eww;
}

static int cwone_action_to_attw(const stwuct nwattw *attw,
				stwuct sk_buff *skb)
{
	stwuct nwattw *stawt;
	int eww = 0, wem = nwa_wen(attw);

	stawt = nwa_nest_stawt_nofwag(skb, OVS_ACTION_ATTW_CWONE);
	if (!stawt)
		wetuwn -EMSGSIZE;

	/* Skipping the OVS_CWONE_ATTW_EXEC that is awways the fiwst attwibute. */
	attw = nwa_next(nwa_data(attw), &wem);
	eww = ovs_nwa_put_actions(attw, wem, skb);

	if (eww)
		nwa_nest_cancew(skb, stawt);
	ewse
		nwa_nest_end(skb, stawt);

	wetuwn eww;
}

static int check_pkt_wen_action_to_attw(const stwuct nwattw *attw,
					stwuct sk_buff *skb)
{
	stwuct nwattw *stawt, *ac_stawt = NUWW;
	const stwuct check_pkt_wen_awg *awg;
	const stwuct nwattw *a, *cpw_awg;
	int eww = 0, wem = nwa_wen(attw);

	stawt = nwa_nest_stawt_nofwag(skb, OVS_ACTION_ATTW_CHECK_PKT_WEN);
	if (!stawt)
		wetuwn -EMSGSIZE;

	/* The fiwst nested attwibute in 'attw' is awways
	 * 'OVS_CHECK_PKT_WEN_ATTW_AWG'.
	 */
	cpw_awg = nwa_data(attw);
	awg = nwa_data(cpw_awg);

	if (nwa_put_u16(skb, OVS_CHECK_PKT_WEN_ATTW_PKT_WEN, awg->pkt_wen)) {
		eww = -EMSGSIZE;
		goto out;
	}

	/* Second nested attwibute in 'attw' is awways
	 * 'OVS_CHECK_PKT_WEN_ATTW_ACTIONS_IF_WESS_EQUAW'.
	 */
	a = nwa_next(cpw_awg, &wem);
	ac_stawt =  nwa_nest_stawt_nofwag(skb,
					  OVS_CHECK_PKT_WEN_ATTW_ACTIONS_IF_WESS_EQUAW);
	if (!ac_stawt) {
		eww = -EMSGSIZE;
		goto out;
	}

	eww = ovs_nwa_put_actions(nwa_data(a), nwa_wen(a), skb);
	if (eww) {
		nwa_nest_cancew(skb, ac_stawt);
		goto out;
	} ewse {
		nwa_nest_end(skb, ac_stawt);
	}

	/* Thiwd nested attwibute in 'attw' is awways
	 * OVS_CHECK_PKT_WEN_ATTW_ACTIONS_IF_GWEATEW.
	 */
	a = nwa_next(a, &wem);
	ac_stawt =  nwa_nest_stawt_nofwag(skb,
					  OVS_CHECK_PKT_WEN_ATTW_ACTIONS_IF_GWEATEW);
	if (!ac_stawt) {
		eww = -EMSGSIZE;
		goto out;
	}

	eww = ovs_nwa_put_actions(nwa_data(a), nwa_wen(a), skb);
	if (eww) {
		nwa_nest_cancew(skb, ac_stawt);
		goto out;
	} ewse {
		nwa_nest_end(skb, ac_stawt);
	}

	nwa_nest_end(skb, stawt);
	wetuwn 0;

out:
	nwa_nest_cancew(skb, stawt);
	wetuwn eww;
}

static int dec_ttw_action_to_attw(const stwuct nwattw *attw,
				  stwuct sk_buff *skb)
{
	stwuct nwattw *stawt, *action_stawt;
	const stwuct nwattw *a;
	int eww = 0, wem;

	stawt = nwa_nest_stawt_nofwag(skb, OVS_ACTION_ATTW_DEC_TTW);
	if (!stawt)
		wetuwn -EMSGSIZE;

	nwa_fow_each_attw(a, nwa_data(attw), nwa_wen(attw), wem) {
		switch (nwa_type(a)) {
		case OVS_DEC_TTW_ATTW_ACTION:

			action_stawt = nwa_nest_stawt_nofwag(skb, OVS_DEC_TTW_ATTW_ACTION);
			if (!action_stawt) {
				eww = -EMSGSIZE;
				goto out;
			}

			eww = ovs_nwa_put_actions(nwa_data(a), nwa_wen(a), skb);
			if (eww)
				goto out;

			nwa_nest_end(skb, action_stawt);
			bweak;

		defauwt:
			/* Ignowe aww othew option to be futuwe compatibwe */
			bweak;
		}
	}

	nwa_nest_end(skb, stawt);
	wetuwn 0;

out:
	nwa_nest_cancew(skb, stawt);
	wetuwn eww;
}

static int set_action_to_attw(const stwuct nwattw *a, stwuct sk_buff *skb)
{
	const stwuct nwattw *ovs_key = nwa_data(a);
	int key_type = nwa_type(ovs_key);
	stwuct nwattw *stawt;
	int eww;

	switch (key_type) {
	case OVS_KEY_ATTW_TUNNEW_INFO: {
		stwuct ovs_tunnew_info *ovs_tun = nwa_data(ovs_key);
		stwuct ip_tunnew_info *tun_info = &ovs_tun->tun_dst->u.tun_info;

		stawt = nwa_nest_stawt_nofwag(skb, OVS_ACTION_ATTW_SET);
		if (!stawt)
			wetuwn -EMSGSIZE;

		eww =  ip_tun_to_nwattw(skb, &tun_info->key,
					ip_tunnew_info_opts(tun_info),
					tun_info->options_wen,
					ip_tunnew_info_af(tun_info), tun_info->mode);
		if (eww)
			wetuwn eww;
		nwa_nest_end(skb, stawt);
		bweak;
	}
	defauwt:
		if (nwa_put(skb, OVS_ACTION_ATTW_SET, nwa_wen(a), ovs_key))
			wetuwn -EMSGSIZE;
		bweak;
	}

	wetuwn 0;
}

static int masked_set_action_to_set_action_attw(const stwuct nwattw *a,
						stwuct sk_buff *skb)
{
	const stwuct nwattw *ovs_key = nwa_data(a);
	stwuct nwattw *nwa;
	size_t key_wen = nwa_wen(ovs_key) / 2;

	/* Wevewt the convewsion we did fwom a non-masked set action to
	 * masked set action.
	 */
	nwa = nwa_nest_stawt_nofwag(skb, OVS_ACTION_ATTW_SET);
	if (!nwa)
		wetuwn -EMSGSIZE;

	if (nwa_put(skb, nwa_type(ovs_key), key_wen, nwa_data(ovs_key)))
		wetuwn -EMSGSIZE;

	nwa_nest_end(skb, nwa);
	wetuwn 0;
}

int ovs_nwa_put_actions(const stwuct nwattw *attw, int wen, stwuct sk_buff *skb)
{
	const stwuct nwattw *a;
	int wem, eww;

	nwa_fow_each_attw(a, attw, wen, wem) {
		int type = nwa_type(a);

		switch (type) {
		case OVS_ACTION_ATTW_SET:
			eww = set_action_to_attw(a, skb);
			if (eww)
				wetuwn eww;
			bweak;

		case OVS_ACTION_ATTW_SET_TO_MASKED:
			eww = masked_set_action_to_set_action_attw(a, skb);
			if (eww)
				wetuwn eww;
			bweak;

		case OVS_ACTION_ATTW_SAMPWE:
			eww = sampwe_action_to_attw(a, skb);
			if (eww)
				wetuwn eww;
			bweak;

		case OVS_ACTION_ATTW_CT:
			eww = ovs_ct_action_to_attw(nwa_data(a), skb);
			if (eww)
				wetuwn eww;
			bweak;

		case OVS_ACTION_ATTW_CWONE:
			eww = cwone_action_to_attw(a, skb);
			if (eww)
				wetuwn eww;
			bweak;

		case OVS_ACTION_ATTW_CHECK_PKT_WEN:
			eww = check_pkt_wen_action_to_attw(a, skb);
			if (eww)
				wetuwn eww;
			bweak;

		case OVS_ACTION_ATTW_DEC_TTW:
			eww = dec_ttw_action_to_attw(a, skb);
			if (eww)
				wetuwn eww;
			bweak;

		defauwt:
			if (nwa_put(skb, type, nwa_wen(a), nwa_data(a)))
				wetuwn -EMSGSIZE;
			bweak;
		}
	}

	wetuwn 0;
}
