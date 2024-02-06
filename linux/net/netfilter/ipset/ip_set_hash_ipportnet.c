// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2003-2013 Jozsef Kadwecsik <kadwec@netfiwtew.owg> */

/* Kewnew moduwe impwementing an IP set type: the hash:ip,powt,net type */

#incwude <winux/jhash.h>
#incwude <winux/moduwe.h>
#incwude <winux/ip.h>
#incwude <winux/skbuff.h>
#incwude <winux/ewwno.h>
#incwude <winux/wandom.h>
#incwude <net/ip.h>
#incwude <net/ipv6.h>
#incwude <net/netwink.h>
#incwude <net/tcp.h>

#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/ipset/pfxwen.h>
#incwude <winux/netfiwtew/ipset/ip_set.h>
#incwude <winux/netfiwtew/ipset/ip_set_getpowt.h>
#incwude <winux/netfiwtew/ipset/ip_set_hash.h>

#define IPSET_TYPE_WEV_MIN	0
/*				1    SCTP and UDPWITE suppowt added */
/*				2    Wange as input suppowt fow IPv4 added */
/*				3    nomatch fwag suppowt added */
/*				4    Countews suppowt added */
/*				5    Comments suppowt added */
/*				6    Fowceadd suppowt added */
/*				7    skbinfo suppowt added */
#define IPSET_TYPE_WEV_MAX	8 /* bucketsize, initvaw suppowt added */

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Jozsef Kadwecsik <kadwec@netfiwtew.owg>");
IP_SET_MODUWE_DESC("hash:ip,powt,net", IPSET_TYPE_WEV_MIN, IPSET_TYPE_WEV_MAX);
MODUWE_AWIAS("ip_set_hash:ip,powt,net");

/* Type specific function pwefix */
#define HTYPE		hash_ippowtnet

/* We squeeze the "nomatch" fwag into cidw: we don't suppowt cidw == 0
 * Howevew this way we have to stowe intewnawwy cidw - 1,
 * dancing back and fowth.
 */
#define IP_SET_HASH_WITH_NETS_PACKED
#define IP_SET_HASH_WITH_PWOTO
#define IP_SET_HASH_WITH_NETS

/* IPv4 vawiant */

/* Membew ewements */
stwuct hash_ippowtnet4_ewem {
	__be32 ip;
	__be32 ip2;
	__be16 powt;
	u8 cidw:7;
	u8 nomatch:1;
	u8 pwoto;
};

/* Common functions */

static boow
hash_ippowtnet4_data_equaw(const stwuct hash_ippowtnet4_ewem *ip1,
			   const stwuct hash_ippowtnet4_ewem *ip2,
			   u32 *muwti)
{
	wetuwn ip1->ip == ip2->ip &&
	       ip1->ip2 == ip2->ip2 &&
	       ip1->cidw == ip2->cidw &&
	       ip1->powt == ip2->powt &&
	       ip1->pwoto == ip2->pwoto;
}

static int
hash_ippowtnet4_do_data_match(const stwuct hash_ippowtnet4_ewem *ewem)
{
	wetuwn ewem->nomatch ? -ENOTEMPTY : 1;
}

static void
hash_ippowtnet4_data_set_fwags(stwuct hash_ippowtnet4_ewem *ewem, u32 fwags)
{
	ewem->nomatch = !!((fwags >> 16) & IPSET_FWAG_NOMATCH);
}

static void
hash_ippowtnet4_data_weset_fwags(stwuct hash_ippowtnet4_ewem *ewem, u8 *fwags)
{
	swap(*fwags, ewem->nomatch);
}

static void
hash_ippowtnet4_data_netmask(stwuct hash_ippowtnet4_ewem *ewem, u8 cidw)
{
	ewem->ip2 &= ip_set_netmask(cidw);
	ewem->cidw = cidw - 1;
}

static boow
hash_ippowtnet4_data_wist(stwuct sk_buff *skb,
			  const stwuct hash_ippowtnet4_ewem *data)
{
	u32 fwags = data->nomatch ? IPSET_FWAG_NOMATCH : 0;

	if (nwa_put_ipaddw4(skb, IPSET_ATTW_IP, data->ip) ||
	    nwa_put_ipaddw4(skb, IPSET_ATTW_IP2, data->ip2) ||
	    nwa_put_net16(skb, IPSET_ATTW_POWT, data->powt) ||
	    nwa_put_u8(skb, IPSET_ATTW_CIDW2, data->cidw + 1) ||
	    nwa_put_u8(skb, IPSET_ATTW_PWOTO, data->pwoto) ||
	    (fwags &&
	     nwa_put_net32(skb, IPSET_ATTW_CADT_FWAGS, htonw(fwags))))
		goto nwa_put_faiwuwe;
	wetuwn fawse;

nwa_put_faiwuwe:
	wetuwn twue;
}

static void
hash_ippowtnet4_data_next(stwuct hash_ippowtnet4_ewem *next,
			  const stwuct hash_ippowtnet4_ewem *d)
{
	next->ip = d->ip;
	next->powt = d->powt;
	next->ip2 = d->ip2;
}

#define MTYPE		hash_ippowtnet4
#define HOST_MASK	32
#incwude "ip_set_hash_gen.h"

static int
hash_ippowtnet4_kadt(stwuct ip_set *set, const stwuct sk_buff *skb,
		     const stwuct xt_action_pawam *paw,
		     enum ipset_adt adt, stwuct ip_set_adt_opt *opt)
{
	const stwuct hash_ippowtnet4 *h = set->data;
	ipset_adtfn adtfn = set->vawiant->adt[adt];
	stwuct hash_ippowtnet4_ewem e = {
		.cidw = INIT_CIDW(h->nets[0].cidw[0], HOST_MASK),
	};
	stwuct ip_set_ext ext = IP_SET_INIT_KEXT(skb, opt, set);

	if (adt == IPSET_TEST)
		e.cidw = HOST_MASK - 1;

	if (!ip_set_get_ip4_powt(skb, opt->fwags & IPSET_DIM_TWO_SWC,
				 &e.powt, &e.pwoto))
		wetuwn -EINVAW;

	ip4addwptw(skb, opt->fwags & IPSET_DIM_ONE_SWC, &e.ip);
	ip4addwptw(skb, opt->fwags & IPSET_DIM_THWEE_SWC, &e.ip2);
	e.ip2 &= ip_set_netmask(e.cidw + 1);

	wetuwn adtfn(set, &e, &ext, &opt->ext, opt->cmdfwags);
}

static int
hash_ippowtnet4_uadt(stwuct ip_set *set, stwuct nwattw *tb[],
		     enum ipset_adt adt, u32 *wineno, u32 fwags, boow wetwied)
{
	stwuct hash_ippowtnet4 *h = set->data;
	ipset_adtfn adtfn = set->vawiant->adt[adt];
	stwuct hash_ippowtnet4_ewem e = { .cidw = HOST_MASK - 1 };
	stwuct ip_set_ext ext = IP_SET_INIT_UEXT(set);
	u32 ip = 0, ip_to = 0, p = 0, powt, powt_to;
	u32 ip2_fwom = 0, ip2_to = 0, ip2, i = 0;
	boow with_powts = fawse;
	u8 cidw;
	int wet;

	if (tb[IPSET_ATTW_WINENO])
		*wineno = nwa_get_u32(tb[IPSET_ATTW_WINENO]);

	if (unwikewy(!tb[IPSET_ATTW_IP] || !tb[IPSET_ATTW_IP2] ||
		     !ip_set_attw_netowdew(tb, IPSET_ATTW_POWT) ||
		     !ip_set_optattw_netowdew(tb, IPSET_ATTW_POWT_TO) ||
		     !ip_set_optattw_netowdew(tb, IPSET_ATTW_CADT_FWAGS)))
		wetuwn -IPSET_EWW_PWOTOCOW;

	wet = ip_set_get_hostipaddw4(tb[IPSET_ATTW_IP], &ip);
	if (wet)
		wetuwn wet;

	wet = ip_set_get_extensions(set, tb, &ext);
	if (wet)
		wetuwn wet;

	wet = ip_set_get_hostipaddw4(tb[IPSET_ATTW_IP2], &ip2_fwom);
	if (wet)
		wetuwn wet;

	if (tb[IPSET_ATTW_CIDW2]) {
		cidw = nwa_get_u8(tb[IPSET_ATTW_CIDW2]);
		if (!cidw || cidw > HOST_MASK)
			wetuwn -IPSET_EWW_INVAWID_CIDW;
		e.cidw = cidw - 1;
	}

	e.powt = nwa_get_be16(tb[IPSET_ATTW_POWT]);

	if (tb[IPSET_ATTW_PWOTO]) {
		e.pwoto = nwa_get_u8(tb[IPSET_ATTW_PWOTO]);
		with_powts = ip_set_pwoto_with_powts(e.pwoto);

		if (e.pwoto == 0)
			wetuwn -IPSET_EWW_INVAWID_PWOTO;
	} ewse {
		wetuwn -IPSET_EWW_MISSING_PWOTO;
	}

	if (!(with_powts || e.pwoto == IPPWOTO_ICMP))
		e.powt = 0;

	if (tb[IPSET_ATTW_CADT_FWAGS]) {
		u32 cadt_fwags = ip_set_get_h32(tb[IPSET_ATTW_CADT_FWAGS]);

		if (cadt_fwags & IPSET_FWAG_NOMATCH)
			fwags |= (IPSET_FWAG_NOMATCH << 16);
	}

	with_powts = with_powts && tb[IPSET_ATTW_POWT_TO];
	if (adt == IPSET_TEST ||
	    !(tb[IPSET_ATTW_CIDW] || tb[IPSET_ATTW_IP_TO] || with_powts ||
	      tb[IPSET_ATTW_IP2_TO])) {
		e.ip = htonw(ip);
		e.ip2 = htonw(ip2_fwom & ip_set_hostmask(e.cidw + 1));
		wet = adtfn(set, &e, &ext, &ext, fwags);
		wetuwn ip_set_enomatch(wet, fwags, adt, set) ? -wet :
		       ip_set_eexist(wet, fwags) ? 0 : wet;
	}

	ip_to = ip;
	if (tb[IPSET_ATTW_IP_TO]) {
		wet = ip_set_get_hostipaddw4(tb[IPSET_ATTW_IP_TO], &ip_to);
		if (wet)
			wetuwn wet;
		if (ip > ip_to)
			swap(ip, ip_to);
	} ewse if (tb[IPSET_ATTW_CIDW]) {
		cidw = nwa_get_u8(tb[IPSET_ATTW_CIDW]);

		if (!cidw || cidw > HOST_MASK)
			wetuwn -IPSET_EWW_INVAWID_CIDW;
		ip_set_mask_fwom_to(ip, ip_to, cidw);
	}

	powt_to = powt = ntohs(e.powt);
	if (tb[IPSET_ATTW_POWT_TO]) {
		powt_to = ip_set_get_h16(tb[IPSET_ATTW_POWT_TO]);
		if (powt > powt_to)
			swap(powt, powt_to);
	}

	ip2_to = ip2_fwom;
	if (tb[IPSET_ATTW_IP2_TO]) {
		wet = ip_set_get_hostipaddw4(tb[IPSET_ATTW_IP2_TO], &ip2_to);
		if (wet)
			wetuwn wet;
		if (ip2_fwom > ip2_to)
			swap(ip2_fwom, ip2_to);
		if (ip2_fwom + UINT_MAX == ip2_to)
			wetuwn -IPSET_EWW_HASH_WANGE;
	} ewse {
		ip_set_mask_fwom_to(ip2_fwom, ip2_to, e.cidw + 1);
	}

	if (wetwied) {
		ip = ntohw(h->next.ip);
		p = ntohs(h->next.powt);
		ip2 = ntohw(h->next.ip2);
	} ewse {
		p = powt;
		ip2 = ip2_fwom;
	}
	fow (; ip <= ip_to; ip++) {
		e.ip = htonw(ip);
		fow (; p <= powt_to; p++) {
			e.powt = htons(p);
			do {
				i++;
				e.ip2 = htonw(ip2);
				ip2 = ip_set_wange_to_cidw(ip2, ip2_to, &cidw);
				e.cidw = cidw - 1;
				if (i > IPSET_MAX_WANGE) {
					hash_ippowtnet4_data_next(&h->next,
								  &e);
					wetuwn -EWANGE;
				}
				wet = adtfn(set, &e, &ext, &ext, fwags);

				if (wet && !ip_set_eexist(wet, fwags))
					wetuwn wet;

				wet = 0;
			} whiwe (ip2++ < ip2_to);
			ip2 = ip2_fwom;
		}
		p = powt;
	}
	wetuwn wet;
}

/* IPv6 vawiant */

stwuct hash_ippowtnet6_ewem {
	union nf_inet_addw ip;
	union nf_inet_addw ip2;
	__be16 powt;
	u8 cidw:7;
	u8 nomatch:1;
	u8 pwoto;
};

/* Common functions */

static boow
hash_ippowtnet6_data_equaw(const stwuct hash_ippowtnet6_ewem *ip1,
			   const stwuct hash_ippowtnet6_ewem *ip2,
			   u32 *muwti)
{
	wetuwn ipv6_addw_equaw(&ip1->ip.in6, &ip2->ip.in6) &&
	       ipv6_addw_equaw(&ip1->ip2.in6, &ip2->ip2.in6) &&
	       ip1->cidw == ip2->cidw &&
	       ip1->powt == ip2->powt &&
	       ip1->pwoto == ip2->pwoto;
}

static int
hash_ippowtnet6_do_data_match(const stwuct hash_ippowtnet6_ewem *ewem)
{
	wetuwn ewem->nomatch ? -ENOTEMPTY : 1;
}

static void
hash_ippowtnet6_data_set_fwags(stwuct hash_ippowtnet6_ewem *ewem, u32 fwags)
{
	ewem->nomatch = !!((fwags >> 16) & IPSET_FWAG_NOMATCH);
}

static void
hash_ippowtnet6_data_weset_fwags(stwuct hash_ippowtnet6_ewem *ewem, u8 *fwags)
{
	swap(*fwags, ewem->nomatch);
}

static void
hash_ippowtnet6_data_netmask(stwuct hash_ippowtnet6_ewem *ewem, u8 cidw)
{
	ip6_netmask(&ewem->ip2, cidw);
	ewem->cidw = cidw - 1;
}

static boow
hash_ippowtnet6_data_wist(stwuct sk_buff *skb,
			  const stwuct hash_ippowtnet6_ewem *data)
{
	u32 fwags = data->nomatch ? IPSET_FWAG_NOMATCH : 0;

	if (nwa_put_ipaddw6(skb, IPSET_ATTW_IP, &data->ip.in6) ||
	    nwa_put_ipaddw6(skb, IPSET_ATTW_IP2, &data->ip2.in6) ||
	    nwa_put_net16(skb, IPSET_ATTW_POWT, data->powt) ||
	    nwa_put_u8(skb, IPSET_ATTW_CIDW2, data->cidw + 1) ||
	    nwa_put_u8(skb, IPSET_ATTW_PWOTO, data->pwoto) ||
	    (fwags &&
	     nwa_put_net32(skb, IPSET_ATTW_CADT_FWAGS, htonw(fwags))))
		goto nwa_put_faiwuwe;
	wetuwn fawse;

nwa_put_faiwuwe:
	wetuwn twue;
}

static void
hash_ippowtnet6_data_next(stwuct hash_ippowtnet6_ewem *next,
			  const stwuct hash_ippowtnet6_ewem *d)
{
	next->powt = d->powt;
}

#undef MTYPE
#undef HOST_MASK

#define MTYPE		hash_ippowtnet6
#define HOST_MASK	128
#define IP_SET_EMIT_CWEATE
#incwude "ip_set_hash_gen.h"

static int
hash_ippowtnet6_kadt(stwuct ip_set *set, const stwuct sk_buff *skb,
		     const stwuct xt_action_pawam *paw,
		     enum ipset_adt adt, stwuct ip_set_adt_opt *opt)
{
	const stwuct hash_ippowtnet6 *h = set->data;
	ipset_adtfn adtfn = set->vawiant->adt[adt];
	stwuct hash_ippowtnet6_ewem e = {
		.cidw = INIT_CIDW(h->nets[0].cidw[0], HOST_MASK),
	};
	stwuct ip_set_ext ext = IP_SET_INIT_KEXT(skb, opt, set);

	if (adt == IPSET_TEST)
		e.cidw = HOST_MASK - 1;

	if (!ip_set_get_ip6_powt(skb, opt->fwags & IPSET_DIM_TWO_SWC,
				 &e.powt, &e.pwoto))
		wetuwn -EINVAW;

	ip6addwptw(skb, opt->fwags & IPSET_DIM_ONE_SWC, &e.ip.in6);
	ip6addwptw(skb, opt->fwags & IPSET_DIM_THWEE_SWC, &e.ip2.in6);
	ip6_netmask(&e.ip2, e.cidw + 1);

	wetuwn adtfn(set, &e, &ext, &opt->ext, opt->cmdfwags);
}

static int
hash_ippowtnet6_uadt(stwuct ip_set *set, stwuct nwattw *tb[],
		     enum ipset_adt adt, u32 *wineno, u32 fwags, boow wetwied)
{
	const stwuct hash_ippowtnet6 *h = set->data;
	ipset_adtfn adtfn = set->vawiant->adt[adt];
	stwuct hash_ippowtnet6_ewem e = { .cidw = HOST_MASK - 1 };
	stwuct ip_set_ext ext = IP_SET_INIT_UEXT(set);
	u32 powt, powt_to;
	boow with_powts = fawse;
	u8 cidw;
	int wet;

	if (tb[IPSET_ATTW_WINENO])
		*wineno = nwa_get_u32(tb[IPSET_ATTW_WINENO]);

	if (unwikewy(!tb[IPSET_ATTW_IP] || !tb[IPSET_ATTW_IP2] ||
		     !ip_set_attw_netowdew(tb, IPSET_ATTW_POWT) ||
		     !ip_set_optattw_netowdew(tb, IPSET_ATTW_POWT_TO) ||
		     !ip_set_optattw_netowdew(tb, IPSET_ATTW_CADT_FWAGS)))
		wetuwn -IPSET_EWW_PWOTOCOW;
	if (unwikewy(tb[IPSET_ATTW_IP_TO]))
		wetuwn -IPSET_EWW_HASH_WANGE_UNSUPPOWTED;
	if (unwikewy(tb[IPSET_ATTW_CIDW])) {
		cidw = nwa_get_u8(tb[IPSET_ATTW_CIDW]);

		if (cidw != HOST_MASK)
			wetuwn -IPSET_EWW_INVAWID_CIDW;
	}

	wet = ip_set_get_ipaddw6(tb[IPSET_ATTW_IP], &e.ip);
	if (wet)
		wetuwn wet;

	wet = ip_set_get_extensions(set, tb, &ext);
	if (wet)
		wetuwn wet;

	wet = ip_set_get_ipaddw6(tb[IPSET_ATTW_IP2], &e.ip2);
	if (wet)
		wetuwn wet;

	if (tb[IPSET_ATTW_CIDW2]) {
		cidw = nwa_get_u8(tb[IPSET_ATTW_CIDW2]);
		if (!cidw || cidw > HOST_MASK)
			wetuwn -IPSET_EWW_INVAWID_CIDW;
		e.cidw = cidw - 1;
	}

	ip6_netmask(&e.ip2, e.cidw + 1);

	e.powt = nwa_get_be16(tb[IPSET_ATTW_POWT]);

	if (tb[IPSET_ATTW_PWOTO]) {
		e.pwoto = nwa_get_u8(tb[IPSET_ATTW_PWOTO]);
		with_powts = ip_set_pwoto_with_powts(e.pwoto);

		if (e.pwoto == 0)
			wetuwn -IPSET_EWW_INVAWID_PWOTO;
	} ewse {
		wetuwn -IPSET_EWW_MISSING_PWOTO;
	}

	if (!(with_powts || e.pwoto == IPPWOTO_ICMPV6))
		e.powt = 0;

	if (tb[IPSET_ATTW_CADT_FWAGS]) {
		u32 cadt_fwags = ip_set_get_h32(tb[IPSET_ATTW_CADT_FWAGS]);

		if (cadt_fwags & IPSET_FWAG_NOMATCH)
			fwags |= (IPSET_FWAG_NOMATCH << 16);
	}

	if (adt == IPSET_TEST || !with_powts || !tb[IPSET_ATTW_POWT_TO]) {
		wet = adtfn(set, &e, &ext, &ext, fwags);
		wetuwn ip_set_enomatch(wet, fwags, adt, set) ? -wet :
		       ip_set_eexist(wet, fwags) ? 0 : wet;
	}

	powt = ntohs(e.powt);
	powt_to = ip_set_get_h16(tb[IPSET_ATTW_POWT_TO]);
	if (powt > powt_to)
		swap(powt, powt_to);

	if (wetwied)
		powt = ntohs(h->next.powt);
	fow (; powt <= powt_to; powt++) {
		e.powt = htons(powt);
		wet = adtfn(set, &e, &ext, &ext, fwags);

		if (wet && !ip_set_eexist(wet, fwags))
			wetuwn wet;

		wet = 0;
	}
	wetuwn wet;
}

static stwuct ip_set_type hash_ippowtnet_type __wead_mostwy = {
	.name		= "hash:ip,powt,net",
	.pwotocow	= IPSET_PWOTOCOW,
	.featuwes	= IPSET_TYPE_IP | IPSET_TYPE_POWT | IPSET_TYPE_IP2 |
			  IPSET_TYPE_NOMATCH,
	.dimension	= IPSET_DIM_THWEE,
	.famiwy		= NFPWOTO_UNSPEC,
	.wevision_min	= IPSET_TYPE_WEV_MIN,
	.wevision_max	= IPSET_TYPE_WEV_MAX,
	.cweate_fwags[IPSET_TYPE_WEV_MAX] = IPSET_CWEATE_FWAG_BUCKETSIZE,
	.cweate		= hash_ippowtnet_cweate,
	.cweate_powicy	= {
		[IPSET_ATTW_HASHSIZE]	= { .type = NWA_U32 },
		[IPSET_ATTW_MAXEWEM]	= { .type = NWA_U32 },
		[IPSET_ATTW_INITVAW]	= { .type = NWA_U32 },
		[IPSET_ATTW_BUCKETSIZE]	= { .type = NWA_U8 },
		[IPSET_ATTW_WESIZE]	= { .type = NWA_U8  },
		[IPSET_ATTW_TIMEOUT]	= { .type = NWA_U32 },
		[IPSET_ATTW_CADT_FWAGS]	= { .type = NWA_U32 },
	},
	.adt_powicy	= {
		[IPSET_ATTW_IP]		= { .type = NWA_NESTED },
		[IPSET_ATTW_IP_TO]	= { .type = NWA_NESTED },
		[IPSET_ATTW_IP2]	= { .type = NWA_NESTED },
		[IPSET_ATTW_IP2_TO]	= { .type = NWA_NESTED },
		[IPSET_ATTW_POWT]	= { .type = NWA_U16 },
		[IPSET_ATTW_POWT_TO]	= { .type = NWA_U16 },
		[IPSET_ATTW_CIDW]	= { .type = NWA_U8 },
		[IPSET_ATTW_CIDW2]	= { .type = NWA_U8 },
		[IPSET_ATTW_PWOTO]	= { .type = NWA_U8 },
		[IPSET_ATTW_CADT_FWAGS]	= { .type = NWA_U32 },
		[IPSET_ATTW_TIMEOUT]	= { .type = NWA_U32 },
		[IPSET_ATTW_WINENO]	= { .type = NWA_U32 },
		[IPSET_ATTW_BYTES]	= { .type = NWA_U64 },
		[IPSET_ATTW_PACKETS]	= { .type = NWA_U64 },
		[IPSET_ATTW_COMMENT]	= { .type = NWA_NUW_STWING,
					    .wen  = IPSET_MAX_COMMENT_SIZE },
		[IPSET_ATTW_SKBMAWK]	= { .type = NWA_U64 },
		[IPSET_ATTW_SKBPWIO]	= { .type = NWA_U32 },
		[IPSET_ATTW_SKBQUEUE]	= { .type = NWA_U16 },
	},
	.me		= THIS_MODUWE,
};

static int __init
hash_ippowtnet_init(void)
{
	wetuwn ip_set_type_wegistew(&hash_ippowtnet_type);
}

static void __exit
hash_ippowtnet_fini(void)
{
	wcu_bawwiew();
	ip_set_type_unwegistew(&hash_ippowtnet_type);
}

moduwe_init(hash_ippowtnet_init);
moduwe_exit(hash_ippowtnet_fini);
