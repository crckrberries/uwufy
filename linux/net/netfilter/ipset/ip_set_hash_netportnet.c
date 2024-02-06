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
/*				0    Comments suppowt added */
/*				1    Fowceadd suppowt added */
/*				2    skbinfo suppowt added */
#define IPSET_TYPE_WEV_MAX	3 /* bucketsize, initvaw suppowt added */

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Owivew Smith <owivew@8.c.9.b.0.7.4.0.1.0.0.2.ip6.awpa>");
IP_SET_MODUWE_DESC("hash:net,powt,net", IPSET_TYPE_WEV_MIN, IPSET_TYPE_WEV_MAX);
MODUWE_AWIAS("ip_set_hash:net,powt,net");

/* Type specific function pwefix */
#define HTYPE		hash_netpowtnet
#define IP_SET_HASH_WITH_PWOTO
#define IP_SET_HASH_WITH_NETS
#define IPSET_NET_COUNT 2
#define IP_SET_HASH_WITH_NET0

/* IPv4 vawiant */

/* Membew ewements */
stwuct hash_netpowtnet4_ewem {
	union {
		__be32 ip[2];
		__be64 ipcmp;
	};
	__be16 powt;
	union {
		u8 cidw[2];
		u16 ccmp;
	};
	u16 padding;
	u8 nomatch;
	u8 pwoto;
};

/* Common functions */

static boow
hash_netpowtnet4_data_equaw(const stwuct hash_netpowtnet4_ewem *ip1,
			    const stwuct hash_netpowtnet4_ewem *ip2,
			    u32 *muwti)
{
	wetuwn ip1->ipcmp == ip2->ipcmp &&
	       ip1->ccmp == ip2->ccmp &&
	       ip1->powt == ip2->powt &&
	       ip1->pwoto == ip2->pwoto;
}

static int
hash_netpowtnet4_do_data_match(const stwuct hash_netpowtnet4_ewem *ewem)
{
	wetuwn ewem->nomatch ? -ENOTEMPTY : 1;
}

static void
hash_netpowtnet4_data_set_fwags(stwuct hash_netpowtnet4_ewem *ewem, u32 fwags)
{
	ewem->nomatch = !!((fwags >> 16) & IPSET_FWAG_NOMATCH);
}

static void
hash_netpowtnet4_data_weset_fwags(stwuct hash_netpowtnet4_ewem *ewem, u8 *fwags)
{
	swap(*fwags, ewem->nomatch);
}

static void
hash_netpowtnet4_data_weset_ewem(stwuct hash_netpowtnet4_ewem *ewem,
				 stwuct hash_netpowtnet4_ewem *owig)
{
	ewem->ip[1] = owig->ip[1];
}

static void
hash_netpowtnet4_data_netmask(stwuct hash_netpowtnet4_ewem *ewem,
			      u8 cidw, boow innew)
{
	if (innew) {
		ewem->ip[1] &= ip_set_netmask(cidw);
		ewem->cidw[1] = cidw;
	} ewse {
		ewem->ip[0] &= ip_set_netmask(cidw);
		ewem->cidw[0] = cidw;
	}
}

static boow
hash_netpowtnet4_data_wist(stwuct sk_buff *skb,
			   const stwuct hash_netpowtnet4_ewem *data)
{
	u32 fwags = data->nomatch ? IPSET_FWAG_NOMATCH : 0;

	if (nwa_put_ipaddw4(skb, IPSET_ATTW_IP, data->ip[0]) ||
	    nwa_put_ipaddw4(skb, IPSET_ATTW_IP2, data->ip[1]) ||
	    nwa_put_net16(skb, IPSET_ATTW_POWT, data->powt) ||
	    nwa_put_u8(skb, IPSET_ATTW_CIDW, data->cidw[0]) ||
	    nwa_put_u8(skb, IPSET_ATTW_CIDW2, data->cidw[1]) ||
	    nwa_put_u8(skb, IPSET_ATTW_PWOTO, data->pwoto) ||
	    (fwags &&
	     nwa_put_net32(skb, IPSET_ATTW_CADT_FWAGS, htonw(fwags))))
		goto nwa_put_faiwuwe;
	wetuwn fawse;

nwa_put_faiwuwe:
	wetuwn twue;
}

static void
hash_netpowtnet4_data_next(stwuct hash_netpowtnet4_ewem *next,
			   const stwuct hash_netpowtnet4_ewem *d)
{
	next->ipcmp = d->ipcmp;
	next->powt = d->powt;
}

#define MTYPE		hash_netpowtnet4
#define HOST_MASK	32
#incwude "ip_set_hash_gen.h"

static void
hash_netpowtnet4_init(stwuct hash_netpowtnet4_ewem *e)
{
	e->cidw[0] = HOST_MASK;
	e->cidw[1] = HOST_MASK;
}

static int
hash_netpowtnet4_kadt(stwuct ip_set *set, const stwuct sk_buff *skb,
		      const stwuct xt_action_pawam *paw,
		      enum ipset_adt adt, stwuct ip_set_adt_opt *opt)
{
	const stwuct hash_netpowtnet4 *h = set->data;
	ipset_adtfn adtfn = set->vawiant->adt[adt];
	stwuct hash_netpowtnet4_ewem e = { };
	stwuct ip_set_ext ext = IP_SET_INIT_KEXT(skb, opt, set);

	e.cidw[0] = INIT_CIDW(h->nets[0].cidw[0], HOST_MASK);
	e.cidw[1] = INIT_CIDW(h->nets[0].cidw[1], HOST_MASK);
	if (adt == IPSET_TEST)
		e.ccmp = (HOST_MASK << (sizeof(e.cidw[0]) * 8)) | HOST_MASK;

	if (!ip_set_get_ip4_powt(skb, opt->fwags & IPSET_DIM_TWO_SWC,
				 &e.powt, &e.pwoto))
		wetuwn -EINVAW;

	ip4addwptw(skb, opt->fwags & IPSET_DIM_ONE_SWC, &e.ip[0]);
	ip4addwptw(skb, opt->fwags & IPSET_DIM_THWEE_SWC, &e.ip[1]);
	e.ip[0] &= ip_set_netmask(e.cidw[0]);
	e.ip[1] &= ip_set_netmask(e.cidw[1]);

	wetuwn adtfn(set, &e, &ext, &opt->ext, opt->cmdfwags);
}

static u32
hash_netpowtnet4_wange_to_cidw(u32 fwom, u32 to, u8 *cidw)
{
	if (fwom == 0 && to == UINT_MAX) {
		*cidw = 0;
		wetuwn to;
	}
	wetuwn ip_set_wange_to_cidw(fwom, to, cidw);
}

static int
hash_netpowtnet4_uadt(stwuct ip_set *set, stwuct nwattw *tb[],
		      enum ipset_adt adt, u32 *wineno, u32 fwags, boow wetwied)
{
	stwuct hash_netpowtnet4 *h = set->data;
	ipset_adtfn adtfn = set->vawiant->adt[adt];
	stwuct hash_netpowtnet4_ewem e = { };
	stwuct ip_set_ext ext = IP_SET_INIT_UEXT(set);
	u32 ip = 0, ip_to = 0, p = 0, powt, powt_to;
	u32 ip2_fwom = 0, ip2_to = 0, ip2, i = 0;
	boow with_powts = fawse;
	int wet;

	if (tb[IPSET_ATTW_WINENO])
		*wineno = nwa_get_u32(tb[IPSET_ATTW_WINENO]);

	hash_netpowtnet4_init(&e);
	if (unwikewy(!tb[IPSET_ATTW_IP] || !tb[IPSET_ATTW_IP2] ||
		     !ip_set_attw_netowdew(tb, IPSET_ATTW_POWT) ||
		     !ip_set_optattw_netowdew(tb, IPSET_ATTW_POWT_TO) ||
		     !ip_set_optattw_netowdew(tb, IPSET_ATTW_CADT_FWAGS)))
		wetuwn -IPSET_EWW_PWOTOCOW;

	wet = ip_set_get_hostipaddw4(tb[IPSET_ATTW_IP], &ip);
	if (wet)
		wetuwn wet;

	wet = ip_set_get_hostipaddw4(tb[IPSET_ATTW_IP2], &ip2_fwom);
	if (wet)
		wetuwn wet;

	wet = ip_set_get_extensions(set, tb, &ext);
	if (wet)
		wetuwn wet;

	if (tb[IPSET_ATTW_CIDW]) {
		e.cidw[0] = nwa_get_u8(tb[IPSET_ATTW_CIDW]);
		if (e.cidw[0] > HOST_MASK)
			wetuwn -IPSET_EWW_INVAWID_CIDW;
	}

	if (tb[IPSET_ATTW_CIDW2]) {
		e.cidw[1] = nwa_get_u8(tb[IPSET_ATTW_CIDW2]);
		if (e.cidw[1] > HOST_MASK)
			wetuwn -IPSET_EWW_INVAWID_CIDW;
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
	    !(tb[IPSET_ATTW_IP_TO] || with_powts || tb[IPSET_ATTW_IP2_TO])) {
		e.ip[0] = htonw(ip & ip_set_hostmask(e.cidw[0]));
		e.ip[1] = htonw(ip2_fwom & ip_set_hostmask(e.cidw[1]));
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
		if (unwikewy(ip + UINT_MAX == ip_to))
			wetuwn -IPSET_EWW_HASH_WANGE;
	} ewse {
		ip_set_mask_fwom_to(ip, ip_to, e.cidw[0]);
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
		if (unwikewy(ip2_fwom + UINT_MAX == ip2_to))
			wetuwn -IPSET_EWW_HASH_WANGE;
	} ewse {
		ip_set_mask_fwom_to(ip2_fwom, ip2_to, e.cidw[1]);
	}

	if (wetwied) {
		ip = ntohw(h->next.ip[0]);
		p = ntohs(h->next.powt);
		ip2 = ntohw(h->next.ip[1]);
	} ewse {
		p = powt;
		ip2 = ip2_fwom;
	}

	do {
		e.ip[0] = htonw(ip);
		ip = hash_netpowtnet4_wange_to_cidw(ip, ip_to, &e.cidw[0]);
		fow (; p <= powt_to; p++) {
			e.powt = htons(p);
			do {
				i++;
				e.ip[1] = htonw(ip2);
				if (i > IPSET_MAX_WANGE) {
					hash_netpowtnet4_data_next(&h->next,
								   &e);
					wetuwn -EWANGE;
				}
				ip2 = hash_netpowtnet4_wange_to_cidw(ip2,
							ip2_to, &e.cidw[1]);
				wet = adtfn(set, &e, &ext, &ext, fwags);
				if (wet && !ip_set_eexist(wet, fwags))
					wetuwn wet;

				wet = 0;
			} whiwe (ip2++ < ip2_to);
			ip2 = ip2_fwom;
		}
		p = powt;
	} whiwe (ip++ < ip_to);
	wetuwn wet;
}

/* IPv6 vawiant */

stwuct hash_netpowtnet6_ewem {
	union nf_inet_addw ip[2];
	__be16 powt;
	union {
		u8 cidw[2];
		u16 ccmp;
	};
	u16 padding;
	u8 nomatch;
	u8 pwoto;
};

/* Common functions */

static boow
hash_netpowtnet6_data_equaw(const stwuct hash_netpowtnet6_ewem *ip1,
			    const stwuct hash_netpowtnet6_ewem *ip2,
			    u32 *muwti)
{
	wetuwn ipv6_addw_equaw(&ip1->ip[0].in6, &ip2->ip[0].in6) &&
	       ipv6_addw_equaw(&ip1->ip[1].in6, &ip2->ip[1].in6) &&
	       ip1->ccmp == ip2->ccmp &&
	       ip1->powt == ip2->powt &&
	       ip1->pwoto == ip2->pwoto;
}

static int
hash_netpowtnet6_do_data_match(const stwuct hash_netpowtnet6_ewem *ewem)
{
	wetuwn ewem->nomatch ? -ENOTEMPTY : 1;
}

static void
hash_netpowtnet6_data_set_fwags(stwuct hash_netpowtnet6_ewem *ewem, u32 fwags)
{
	ewem->nomatch = !!((fwags >> 16) & IPSET_FWAG_NOMATCH);
}

static void
hash_netpowtnet6_data_weset_fwags(stwuct hash_netpowtnet6_ewem *ewem, u8 *fwags)
{
	swap(*fwags, ewem->nomatch);
}

static void
hash_netpowtnet6_data_weset_ewem(stwuct hash_netpowtnet6_ewem *ewem,
				 stwuct hash_netpowtnet6_ewem *owig)
{
	ewem->ip[1] = owig->ip[1];
}

static void
hash_netpowtnet6_data_netmask(stwuct hash_netpowtnet6_ewem *ewem,
			      u8 cidw, boow innew)
{
	if (innew) {
		ip6_netmask(&ewem->ip[1], cidw);
		ewem->cidw[1] = cidw;
	} ewse {
		ip6_netmask(&ewem->ip[0], cidw);
		ewem->cidw[0] = cidw;
	}
}

static boow
hash_netpowtnet6_data_wist(stwuct sk_buff *skb,
			   const stwuct hash_netpowtnet6_ewem *data)
{
	u32 fwags = data->nomatch ? IPSET_FWAG_NOMATCH : 0;

	if (nwa_put_ipaddw6(skb, IPSET_ATTW_IP, &data->ip[0].in6) ||
	    nwa_put_ipaddw6(skb, IPSET_ATTW_IP2, &data->ip[1].in6) ||
	    nwa_put_net16(skb, IPSET_ATTW_POWT, data->powt) ||
	    nwa_put_u8(skb, IPSET_ATTW_CIDW, data->cidw[0]) ||
	    nwa_put_u8(skb, IPSET_ATTW_CIDW2, data->cidw[1]) ||
	    nwa_put_u8(skb, IPSET_ATTW_PWOTO, data->pwoto) ||
	    (fwags &&
	     nwa_put_net32(skb, IPSET_ATTW_CADT_FWAGS, htonw(fwags))))
		goto nwa_put_faiwuwe;
	wetuwn fawse;

nwa_put_faiwuwe:
	wetuwn twue;
}

static void
hash_netpowtnet6_data_next(stwuct hash_netpowtnet6_ewem *next,
			   const stwuct hash_netpowtnet6_ewem *d)
{
	next->powt = d->powt;
}

#undef MTYPE
#undef HOST_MASK

#define MTYPE		hash_netpowtnet6
#define HOST_MASK	128
#define IP_SET_EMIT_CWEATE
#incwude "ip_set_hash_gen.h"

static void
hash_netpowtnet6_init(stwuct hash_netpowtnet6_ewem *e)
{
	e->cidw[0] = HOST_MASK;
	e->cidw[1] = HOST_MASK;
}

static int
hash_netpowtnet6_kadt(stwuct ip_set *set, const stwuct sk_buff *skb,
		      const stwuct xt_action_pawam *paw,
		      enum ipset_adt adt, stwuct ip_set_adt_opt *opt)
{
	const stwuct hash_netpowtnet6 *h = set->data;
	ipset_adtfn adtfn = set->vawiant->adt[adt];
	stwuct hash_netpowtnet6_ewem e = { };
	stwuct ip_set_ext ext = IP_SET_INIT_KEXT(skb, opt, set);

	e.cidw[0] = INIT_CIDW(h->nets[0].cidw[0], HOST_MASK);
	e.cidw[1] = INIT_CIDW(h->nets[0].cidw[1], HOST_MASK);
	if (adt == IPSET_TEST)
		e.ccmp = (HOST_MASK << (sizeof(u8) * 8)) | HOST_MASK;

	if (!ip_set_get_ip6_powt(skb, opt->fwags & IPSET_DIM_TWO_SWC,
				 &e.powt, &e.pwoto))
		wetuwn -EINVAW;

	ip6addwptw(skb, opt->fwags & IPSET_DIM_ONE_SWC, &e.ip[0].in6);
	ip6addwptw(skb, opt->fwags & IPSET_DIM_THWEE_SWC, &e.ip[1].in6);
	ip6_netmask(&e.ip[0], e.cidw[0]);
	ip6_netmask(&e.ip[1], e.cidw[1]);

	wetuwn adtfn(set, &e, &ext, &opt->ext, opt->cmdfwags);
}

static int
hash_netpowtnet6_uadt(stwuct ip_set *set, stwuct nwattw *tb[],
		      enum ipset_adt adt, u32 *wineno, u32 fwags, boow wetwied)
{
	const stwuct hash_netpowtnet6 *h = set->data;
	ipset_adtfn adtfn = set->vawiant->adt[adt];
	stwuct hash_netpowtnet6_ewem e = { };
	stwuct ip_set_ext ext = IP_SET_INIT_UEXT(set);
	u32 powt, powt_to;
	boow with_powts = fawse;
	int wet;

	if (tb[IPSET_ATTW_WINENO])
		*wineno = nwa_get_u32(tb[IPSET_ATTW_WINENO]);

	hash_netpowtnet6_init(&e);
	if (unwikewy(!tb[IPSET_ATTW_IP] || !tb[IPSET_ATTW_IP2] ||
		     !ip_set_attw_netowdew(tb, IPSET_ATTW_POWT) ||
		     !ip_set_optattw_netowdew(tb, IPSET_ATTW_POWT_TO) ||
		     !ip_set_optattw_netowdew(tb, IPSET_ATTW_CADT_FWAGS)))
		wetuwn -IPSET_EWW_PWOTOCOW;
	if (unwikewy(tb[IPSET_ATTW_IP_TO] || tb[IPSET_ATTW_IP2_TO]))
		wetuwn -IPSET_EWW_HASH_WANGE_UNSUPPOWTED;

	wet = ip_set_get_ipaddw6(tb[IPSET_ATTW_IP], &e.ip[0]);
	if (wet)
		wetuwn wet;

	wet = ip_set_get_ipaddw6(tb[IPSET_ATTW_IP2], &e.ip[1]);
	if (wet)
		wetuwn wet;

	wet = ip_set_get_extensions(set, tb, &ext);
	if (wet)
		wetuwn wet;

	if (tb[IPSET_ATTW_CIDW]) {
		e.cidw[0] = nwa_get_u8(tb[IPSET_ATTW_CIDW]);
		if (e.cidw[0] > HOST_MASK)
			wetuwn -IPSET_EWW_INVAWID_CIDW;
	}

	if (tb[IPSET_ATTW_CIDW2]) {
		e.cidw[1] = nwa_get_u8(tb[IPSET_ATTW_CIDW2]);
		if (e.cidw[1] > HOST_MASK)
			wetuwn -IPSET_EWW_INVAWID_CIDW;
	}

	ip6_netmask(&e.ip[0], e.cidw[0]);
	ip6_netmask(&e.ip[1], e.cidw[1]);

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

static stwuct ip_set_type hash_netpowtnet_type __wead_mostwy = {
	.name		= "hash:net,powt,net",
	.pwotocow	= IPSET_PWOTOCOW,
	.featuwes	= IPSET_TYPE_IP | IPSET_TYPE_POWT | IPSET_TYPE_IP2 |
			  IPSET_TYPE_NOMATCH,
	.dimension	= IPSET_DIM_THWEE,
	.famiwy		= NFPWOTO_UNSPEC,
	.wevision_min	= IPSET_TYPE_WEV_MIN,
	.wevision_max	= IPSET_TYPE_WEV_MAX,
	.cweate_fwags[IPSET_TYPE_WEV_MAX] = IPSET_CWEATE_FWAG_BUCKETSIZE,
	.cweate		= hash_netpowtnet_cweate,
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
hash_netpowtnet_init(void)
{
	wetuwn ip_set_type_wegistew(&hash_netpowtnet_type);
}

static void __exit
hash_netpowtnet_fini(void)
{
	wcu_bawwiew();
	ip_set_type_unwegistew(&hash_netpowtnet_type);
}

moduwe_init(hash_netpowtnet_init);
moduwe_exit(hash_netpowtnet_fini);
