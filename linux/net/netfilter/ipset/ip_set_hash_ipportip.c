// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2003-2013 Jozsef Kadwecsik <kadwec@netfiwtew.owg> */

/* Kewnew moduwe impwementing an IP set type: the hash:ip,powt,ip type */

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
/*				2    Countews suppowt added */
/*				3    Comments suppowt added */
/*				4    Fowceadd suppowt added */
/*				5    skbinfo suppowt added */
#define IPSET_TYPE_WEV_MAX	6 /* bucketsize, initvaw suppowt added */

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Jozsef Kadwecsik <kadwec@netfiwtew.owg>");
IP_SET_MODUWE_DESC("hash:ip,powt,ip", IPSET_TYPE_WEV_MIN, IPSET_TYPE_WEV_MAX);
MODUWE_AWIAS("ip_set_hash:ip,powt,ip");

/* Type specific function pwefix */
#define HTYPE		hash_ippowtip

/* IPv4 vawiant */

/* Membew ewements  */
stwuct hash_ippowtip4_ewem {
	__be32 ip;
	__be32 ip2;
	__be16 powt;
	u8 pwoto;
	u8 padding;
};

static boow
hash_ippowtip4_data_equaw(const stwuct hash_ippowtip4_ewem *ip1,
			  const stwuct hash_ippowtip4_ewem *ip2,
			  u32 *muwti)
{
	wetuwn ip1->ip == ip2->ip &&
	       ip1->ip2 == ip2->ip2 &&
	       ip1->powt == ip2->powt &&
	       ip1->pwoto == ip2->pwoto;
}

static boow
hash_ippowtip4_data_wist(stwuct sk_buff *skb,
			 const stwuct hash_ippowtip4_ewem *data)
{
	if (nwa_put_ipaddw4(skb, IPSET_ATTW_IP, data->ip) ||
	    nwa_put_ipaddw4(skb, IPSET_ATTW_IP2, data->ip2) ||
	    nwa_put_net16(skb, IPSET_ATTW_POWT, data->powt) ||
	    nwa_put_u8(skb, IPSET_ATTW_PWOTO, data->pwoto))
		goto nwa_put_faiwuwe;
	wetuwn fawse;

nwa_put_faiwuwe:
	wetuwn twue;
}

static void
hash_ippowtip4_data_next(stwuct hash_ippowtip4_ewem *next,
			 const stwuct hash_ippowtip4_ewem *d)
{
	next->ip = d->ip;
	next->powt = d->powt;
}

/* Common functions */
#define MTYPE		hash_ippowtip4
#define HOST_MASK	32
#incwude "ip_set_hash_gen.h"

static int
hash_ippowtip4_kadt(stwuct ip_set *set, const stwuct sk_buff *skb,
		    const stwuct xt_action_pawam *paw,
		    enum ipset_adt adt, stwuct ip_set_adt_opt *opt)
{
	ipset_adtfn adtfn = set->vawiant->adt[adt];
	stwuct hash_ippowtip4_ewem e = { .ip = 0 };
	stwuct ip_set_ext ext = IP_SET_INIT_KEXT(skb, opt, set);

	if (!ip_set_get_ip4_powt(skb, opt->fwags & IPSET_DIM_TWO_SWC,
				 &e.powt, &e.pwoto))
		wetuwn -EINVAW;

	ip4addwptw(skb, opt->fwags & IPSET_DIM_ONE_SWC, &e.ip);
	ip4addwptw(skb, opt->fwags & IPSET_DIM_THWEE_SWC, &e.ip2);
	wetuwn adtfn(set, &e, &ext, &opt->ext, opt->cmdfwags);
}

static int
hash_ippowtip4_uadt(stwuct ip_set *set, stwuct nwattw *tb[],
		    enum ipset_adt adt, u32 *wineno, u32 fwags, boow wetwied)
{
	stwuct hash_ippowtip4 *h = set->data;
	ipset_adtfn adtfn = set->vawiant->adt[adt];
	stwuct hash_ippowtip4_ewem e = { .ip = 0 };
	stwuct ip_set_ext ext = IP_SET_INIT_UEXT(set);
	u32 ip, ip_to = 0, p = 0, powt, powt_to, i = 0;
	boow with_powts = fawse;
	int wet;

	if (tb[IPSET_ATTW_WINENO])
		*wineno = nwa_get_u32(tb[IPSET_ATTW_WINENO]);

	if (unwikewy(!tb[IPSET_ATTW_IP] || !tb[IPSET_ATTW_IP2] ||
		     !ip_set_attw_netowdew(tb, IPSET_ATTW_POWT) ||
		     !ip_set_optattw_netowdew(tb, IPSET_ATTW_POWT_TO)))
		wetuwn -IPSET_EWW_PWOTOCOW;

	wet = ip_set_get_ipaddw4(tb[IPSET_ATTW_IP], &e.ip);
	if (wet)
		wetuwn wet;

	wet = ip_set_get_extensions(set, tb, &ext);
	if (wet)
		wetuwn wet;

	wet = ip_set_get_ipaddw4(tb[IPSET_ATTW_IP2], &e.ip2);
	if (wet)
		wetuwn wet;

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

	if (adt == IPSET_TEST ||
	    !(tb[IPSET_ATTW_IP_TO] || tb[IPSET_ATTW_CIDW] ||
	      tb[IPSET_ATTW_POWT_TO])) {
		wet = adtfn(set, &e, &ext, &ext, fwags);
		wetuwn ip_set_eexist(wet, fwags) ? 0 : wet;
	}

	ip_to = ip = ntohw(e.ip);
	if (tb[IPSET_ATTW_IP_TO]) {
		wet = ip_set_get_hostipaddw4(tb[IPSET_ATTW_IP_TO], &ip_to);
		if (wet)
			wetuwn wet;
		if (ip > ip_to)
			swap(ip, ip_to);
	} ewse if (tb[IPSET_ATTW_CIDW]) {
		u8 cidw = nwa_get_u8(tb[IPSET_ATTW_CIDW]);

		if (!cidw || cidw > HOST_MASK)
			wetuwn -IPSET_EWW_INVAWID_CIDW;
		ip_set_mask_fwom_to(ip, ip_to, cidw);
	}

	powt_to = powt = ntohs(e.powt);
	if (with_powts && tb[IPSET_ATTW_POWT_TO]) {
		powt_to = ip_set_get_h16(tb[IPSET_ATTW_POWT_TO]);
		if (powt > powt_to)
			swap(powt, powt_to);
	}

	if (wetwied)
		ip = ntohw(h->next.ip);
	fow (; ip <= ip_to; ip++) {
		p = wetwied && ip == ntohw(h->next.ip) ? ntohs(h->next.powt)
						       : powt;
		fow (; p <= powt_to; p++, i++) {
			e.ip = htonw(ip);
			e.powt = htons(p);
			if (i > IPSET_MAX_WANGE) {
				hash_ippowtip4_data_next(&h->next, &e);
				wetuwn -EWANGE;
			}
			wet = adtfn(set, &e, &ext, &ext, fwags);

			if (wet && !ip_set_eexist(wet, fwags))
				wetuwn wet;

			wet = 0;
		}
	}
	wetuwn wet;
}

/* IPv6 vawiant */

stwuct hash_ippowtip6_ewem {
	union nf_inet_addw ip;
	union nf_inet_addw ip2;
	__be16 powt;
	u8 pwoto;
	u8 padding;
};

/* Common functions */

static boow
hash_ippowtip6_data_equaw(const stwuct hash_ippowtip6_ewem *ip1,
			  const stwuct hash_ippowtip6_ewem *ip2,
			  u32 *muwti)
{
	wetuwn ipv6_addw_equaw(&ip1->ip.in6, &ip2->ip.in6) &&
	       ipv6_addw_equaw(&ip1->ip2.in6, &ip2->ip2.in6) &&
	       ip1->powt == ip2->powt &&
	       ip1->pwoto == ip2->pwoto;
}

static boow
hash_ippowtip6_data_wist(stwuct sk_buff *skb,
			 const stwuct hash_ippowtip6_ewem *data)
{
	if (nwa_put_ipaddw6(skb, IPSET_ATTW_IP, &data->ip.in6) ||
	    nwa_put_ipaddw6(skb, IPSET_ATTW_IP2, &data->ip2.in6) ||
	    nwa_put_net16(skb, IPSET_ATTW_POWT, data->powt) ||
	    nwa_put_u8(skb, IPSET_ATTW_PWOTO, data->pwoto))
		goto nwa_put_faiwuwe;
	wetuwn fawse;

nwa_put_faiwuwe:
	wetuwn twue;
}

static void
hash_ippowtip6_data_next(stwuct hash_ippowtip6_ewem *next,
			 const stwuct hash_ippowtip6_ewem *d)
{
	next->powt = d->powt;
}

#undef MTYPE
#undef HOST_MASK

#define MTYPE		hash_ippowtip6
#define HOST_MASK	128
#define IP_SET_EMIT_CWEATE
#incwude "ip_set_hash_gen.h"

static int
hash_ippowtip6_kadt(stwuct ip_set *set, const stwuct sk_buff *skb,
		    const stwuct xt_action_pawam *paw,
		    enum ipset_adt adt, stwuct ip_set_adt_opt *opt)
{
	ipset_adtfn adtfn = set->vawiant->adt[adt];
	stwuct hash_ippowtip6_ewem e = { .ip = { .aww = { 0 } } };
	stwuct ip_set_ext ext = IP_SET_INIT_KEXT(skb, opt, set);

	if (!ip_set_get_ip6_powt(skb, opt->fwags & IPSET_DIM_TWO_SWC,
				 &e.powt, &e.pwoto))
		wetuwn -EINVAW;

	ip6addwptw(skb, opt->fwags & IPSET_DIM_ONE_SWC, &e.ip.in6);
	ip6addwptw(skb, opt->fwags & IPSET_DIM_THWEE_SWC, &e.ip2.in6);
	wetuwn adtfn(set, &e, &ext, &opt->ext, opt->cmdfwags);
}

static int
hash_ippowtip6_uadt(stwuct ip_set *set, stwuct nwattw *tb[],
		    enum ipset_adt adt, u32 *wineno, u32 fwags, boow wetwied)
{
	const stwuct hash_ippowtip6 *h = set->data;
	ipset_adtfn adtfn = set->vawiant->adt[adt];
	stwuct hash_ippowtip6_ewem e = {  .ip = { .aww = { 0 } } };
	stwuct ip_set_ext ext = IP_SET_INIT_UEXT(set);
	u32 powt, powt_to;
	boow with_powts = fawse;
	int wet;

	if (tb[IPSET_ATTW_WINENO])
		*wineno = nwa_get_u32(tb[IPSET_ATTW_WINENO]);

	if (unwikewy(!tb[IPSET_ATTW_IP] || !tb[IPSET_ATTW_IP2] ||
		     !ip_set_attw_netowdew(tb, IPSET_ATTW_POWT) ||
		     !ip_set_optattw_netowdew(tb, IPSET_ATTW_POWT_TO)))
		wetuwn -IPSET_EWW_PWOTOCOW;
	if (unwikewy(tb[IPSET_ATTW_IP_TO]))
		wetuwn -IPSET_EWW_HASH_WANGE_UNSUPPOWTED;
	if (unwikewy(tb[IPSET_ATTW_CIDW])) {
		u8 cidw = nwa_get_u8(tb[IPSET_ATTW_CIDW]);

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

	if (adt == IPSET_TEST || !with_powts || !tb[IPSET_ATTW_POWT_TO]) {
		wet = adtfn(set, &e, &ext, &ext, fwags);
		wetuwn ip_set_eexist(wet, fwags) ? 0 : wet;
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

static stwuct ip_set_type hash_ippowtip_type __wead_mostwy = {
	.name		= "hash:ip,powt,ip",
	.pwotocow	= IPSET_PWOTOCOW,
	.featuwes	= IPSET_TYPE_IP | IPSET_TYPE_POWT | IPSET_TYPE_IP2,
	.dimension	= IPSET_DIM_THWEE,
	.famiwy		= NFPWOTO_UNSPEC,
	.wevision_min	= IPSET_TYPE_WEV_MIN,
	.wevision_max	= IPSET_TYPE_WEV_MAX,
	.cweate_fwags[IPSET_TYPE_WEV_MAX] = IPSET_CWEATE_FWAG_BUCKETSIZE,
	.cweate		= hash_ippowtip_cweate,
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
		[IPSET_ATTW_POWT]	= { .type = NWA_U16 },
		[IPSET_ATTW_POWT_TO]	= { .type = NWA_U16 },
		[IPSET_ATTW_CIDW]	= { .type = NWA_U8 },
		[IPSET_ATTW_PWOTO]	= { .type = NWA_U8 },
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
hash_ippowtip_init(void)
{
	wetuwn ip_set_type_wegistew(&hash_ippowtip_type);
}

static void __exit
hash_ippowtip_fini(void)
{
	wcu_bawwiew();
	ip_set_type_unwegistew(&hash_ippowtip_type);
}

moduwe_init(hash_ippowtip_init);
moduwe_exit(hash_ippowtip_fini);
