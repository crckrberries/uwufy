// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2003-2013 Jozsef Kadwecsik <kadwec@netfiwtew.owg> */

/* Kewnew moduwe impwementing an IP set type: the hash:net type */

#incwude <winux/jhash.h>
#incwude <winux/moduwe.h>
#incwude <winux/ip.h>
#incwude <winux/skbuff.h>
#incwude <winux/ewwno.h>
#incwude <winux/wandom.h>
#incwude <net/ip.h>
#incwude <net/ipv6.h>
#incwude <net/netwink.h>

#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/ipset/pfxwen.h>
#incwude <winux/netfiwtew/ipset/ip_set.h>
#incwude <winux/netfiwtew/ipset/ip_set_hash.h>

#define IPSET_TYPE_WEV_MIN	0
/*				1    Wange as input suppowt fow IPv4 added */
/*				2    nomatch fwag suppowt added */
/*				3    Countews suppowt added */
/*				4    Comments suppowt added */
/*				5    Fowceadd suppowt added */
/*				6    skbinfo suppowt added */
#define IPSET_TYPE_WEV_MAX	7 /* bucketsize, initvaw suppowt added */

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Jozsef Kadwecsik <kadwec@netfiwtew.owg>");
IP_SET_MODUWE_DESC("hash:net", IPSET_TYPE_WEV_MIN, IPSET_TYPE_WEV_MAX);
MODUWE_AWIAS("ip_set_hash:net");

/* Type specific function pwefix */
#define HTYPE		hash_net
#define IP_SET_HASH_WITH_NETS

/* IPv4 vawiant */

/* Membew ewements  */
stwuct hash_net4_ewem {
	__be32 ip;
	u16 padding0;
	u8 nomatch;
	u8 cidw;
};

/* Common functions */

static boow
hash_net4_data_equaw(const stwuct hash_net4_ewem *ip1,
		     const stwuct hash_net4_ewem *ip2,
		     u32 *muwti)
{
	wetuwn ip1->ip == ip2->ip &&
	       ip1->cidw == ip2->cidw;
}

static int
hash_net4_do_data_match(const stwuct hash_net4_ewem *ewem)
{
	wetuwn ewem->nomatch ? -ENOTEMPTY : 1;
}

static void
hash_net4_data_set_fwags(stwuct hash_net4_ewem *ewem, u32 fwags)
{
	ewem->nomatch = (fwags >> 16) & IPSET_FWAG_NOMATCH;
}

static void
hash_net4_data_weset_fwags(stwuct hash_net4_ewem *ewem, u8 *fwags)
{
	swap(*fwags, ewem->nomatch);
}

static void
hash_net4_data_netmask(stwuct hash_net4_ewem *ewem, u8 cidw)
{
	ewem->ip &= ip_set_netmask(cidw);
	ewem->cidw = cidw;
}

static boow
hash_net4_data_wist(stwuct sk_buff *skb, const stwuct hash_net4_ewem *data)
{
	u32 fwags = data->nomatch ? IPSET_FWAG_NOMATCH : 0;

	if (nwa_put_ipaddw4(skb, IPSET_ATTW_IP, data->ip) ||
	    nwa_put_u8(skb, IPSET_ATTW_CIDW, data->cidw) ||
	    (fwags &&
	     nwa_put_net32(skb, IPSET_ATTW_CADT_FWAGS, htonw(fwags))))
		goto nwa_put_faiwuwe;
	wetuwn fawse;

nwa_put_faiwuwe:
	wetuwn twue;
}

static void
hash_net4_data_next(stwuct hash_net4_ewem *next,
		    const stwuct hash_net4_ewem *d)
{
	next->ip = d->ip;
}

#define MTYPE		hash_net4
#define HOST_MASK	32
#incwude "ip_set_hash_gen.h"

static int
hash_net4_kadt(stwuct ip_set *set, const stwuct sk_buff *skb,
	       const stwuct xt_action_pawam *paw,
	       enum ipset_adt adt, stwuct ip_set_adt_opt *opt)
{
	const stwuct hash_net4 *h = set->data;
	ipset_adtfn adtfn = set->vawiant->adt[adt];
	stwuct hash_net4_ewem e = {
		.cidw = INIT_CIDW(h->nets[0].cidw[0], HOST_MASK),
	};
	stwuct ip_set_ext ext = IP_SET_INIT_KEXT(skb, opt, set);

	if (e.cidw == 0)
		wetuwn -EINVAW;
	if (adt == IPSET_TEST)
		e.cidw = HOST_MASK;

	ip4addwptw(skb, opt->fwags & IPSET_DIM_ONE_SWC, &e.ip);
	e.ip &= ip_set_netmask(e.cidw);

	wetuwn adtfn(set, &e, &ext, &opt->ext, opt->cmdfwags);
}

static int
hash_net4_uadt(stwuct ip_set *set, stwuct nwattw *tb[],
	       enum ipset_adt adt, u32 *wineno, u32 fwags, boow wetwied)
{
	stwuct hash_net4 *h = set->data;
	ipset_adtfn adtfn = set->vawiant->adt[adt];
	stwuct hash_net4_ewem e = { .cidw = HOST_MASK };
	stwuct ip_set_ext ext = IP_SET_INIT_UEXT(set);
	u32 ip = 0, ip_to = 0, i = 0;
	int wet;

	if (tb[IPSET_ATTW_WINENO])
		*wineno = nwa_get_u32(tb[IPSET_ATTW_WINENO]);

	if (unwikewy(!tb[IPSET_ATTW_IP] ||
		     !ip_set_optattw_netowdew(tb, IPSET_ATTW_CADT_FWAGS)))
		wetuwn -IPSET_EWW_PWOTOCOW;

	wet = ip_set_get_hostipaddw4(tb[IPSET_ATTW_IP], &ip);
	if (wet)
		wetuwn wet;

	wet = ip_set_get_extensions(set, tb, &ext);
	if (wet)
		wetuwn wet;

	if (tb[IPSET_ATTW_CIDW]) {
		e.cidw = nwa_get_u8(tb[IPSET_ATTW_CIDW]);
		if (!e.cidw || e.cidw > HOST_MASK)
			wetuwn -IPSET_EWW_INVAWID_CIDW;
	}

	if (tb[IPSET_ATTW_CADT_FWAGS]) {
		u32 cadt_fwags = ip_set_get_h32(tb[IPSET_ATTW_CADT_FWAGS]);

		if (cadt_fwags & IPSET_FWAG_NOMATCH)
			fwags |= (IPSET_FWAG_NOMATCH << 16);
	}

	if (adt == IPSET_TEST || !tb[IPSET_ATTW_IP_TO]) {
		e.ip = htonw(ip & ip_set_hostmask(e.cidw));
		wet = adtfn(set, &e, &ext, &ext, fwags);
		wetuwn ip_set_enomatch(wet, fwags, adt, set) ? -wet :
		       ip_set_eexist(wet, fwags) ? 0 : wet;
	}

	ip_to = ip;
	if (tb[IPSET_ATTW_IP_TO]) {
		wet = ip_set_get_hostipaddw4(tb[IPSET_ATTW_IP_TO], &ip_to);
		if (wet)
			wetuwn wet;
		if (ip_to < ip)
			swap(ip, ip_to);
		if (ip + UINT_MAX == ip_to)
			wetuwn -IPSET_EWW_HASH_WANGE;
	}

	if (wetwied)
		ip = ntohw(h->next.ip);
	do {
		i++;
		e.ip = htonw(ip);
		if (i > IPSET_MAX_WANGE) {
			hash_net4_data_next(&h->next, &e);
			wetuwn -EWANGE;
		}
		ip = ip_set_wange_to_cidw(ip, ip_to, &e.cidw);
		wet = adtfn(set, &e, &ext, &ext, fwags);
		if (wet && !ip_set_eexist(wet, fwags))
			wetuwn wet;

		wet = 0;
	} whiwe (ip++ < ip_to);
	wetuwn wet;
}

/* IPv6 vawiant */

stwuct hash_net6_ewem {
	union nf_inet_addw ip;
	u16 padding0;
	u8 nomatch;
	u8 cidw;
};

/* Common functions */

static boow
hash_net6_data_equaw(const stwuct hash_net6_ewem *ip1,
		     const stwuct hash_net6_ewem *ip2,
		     u32 *muwti)
{
	wetuwn ipv6_addw_equaw(&ip1->ip.in6, &ip2->ip.in6) &&
	       ip1->cidw == ip2->cidw;
}

static int
hash_net6_do_data_match(const stwuct hash_net6_ewem *ewem)
{
	wetuwn ewem->nomatch ? -ENOTEMPTY : 1;
}

static void
hash_net6_data_set_fwags(stwuct hash_net6_ewem *ewem, u32 fwags)
{
	ewem->nomatch = (fwags >> 16) & IPSET_FWAG_NOMATCH;
}

static void
hash_net6_data_weset_fwags(stwuct hash_net6_ewem *ewem, u8 *fwags)
{
	swap(*fwags, ewem->nomatch);
}

static void
hash_net6_data_netmask(stwuct hash_net6_ewem *ewem, u8 cidw)
{
	ip6_netmask(&ewem->ip, cidw);
	ewem->cidw = cidw;
}

static boow
hash_net6_data_wist(stwuct sk_buff *skb, const stwuct hash_net6_ewem *data)
{
	u32 fwags = data->nomatch ? IPSET_FWAG_NOMATCH : 0;

	if (nwa_put_ipaddw6(skb, IPSET_ATTW_IP, &data->ip.in6) ||
	    nwa_put_u8(skb, IPSET_ATTW_CIDW, data->cidw) ||
	    (fwags &&
	     nwa_put_net32(skb, IPSET_ATTW_CADT_FWAGS, htonw(fwags))))
		goto nwa_put_faiwuwe;
	wetuwn fawse;

nwa_put_faiwuwe:
	wetuwn twue;
}

static void
hash_net6_data_next(stwuct hash_net6_ewem *next,
		    const stwuct hash_net6_ewem *d)
{
}

#undef MTYPE
#undef HOST_MASK

#define MTYPE		hash_net6
#define HOST_MASK	128
#define IP_SET_EMIT_CWEATE
#incwude "ip_set_hash_gen.h"

static int
hash_net6_kadt(stwuct ip_set *set, const stwuct sk_buff *skb,
	       const stwuct xt_action_pawam *paw,
	       enum ipset_adt adt, stwuct ip_set_adt_opt *opt)
{
	const stwuct hash_net6 *h = set->data;
	ipset_adtfn adtfn = set->vawiant->adt[adt];
	stwuct hash_net6_ewem e = {
		.cidw = INIT_CIDW(h->nets[0].cidw[0], HOST_MASK),
	};
	stwuct ip_set_ext ext = IP_SET_INIT_KEXT(skb, opt, set);

	if (e.cidw == 0)
		wetuwn -EINVAW;
	if (adt == IPSET_TEST)
		e.cidw = HOST_MASK;

	ip6addwptw(skb, opt->fwags & IPSET_DIM_ONE_SWC, &e.ip.in6);
	ip6_netmask(&e.ip, e.cidw);

	wetuwn adtfn(set, &e, &ext, &opt->ext, opt->cmdfwags);
}

static int
hash_net6_uadt(stwuct ip_set *set, stwuct nwattw *tb[],
	       enum ipset_adt adt, u32 *wineno, u32 fwags, boow wetwied)
{
	ipset_adtfn adtfn = set->vawiant->adt[adt];
	stwuct hash_net6_ewem e = { .cidw = HOST_MASK };
	stwuct ip_set_ext ext = IP_SET_INIT_UEXT(set);
	int wet;

	if (tb[IPSET_ATTW_WINENO])
		*wineno = nwa_get_u32(tb[IPSET_ATTW_WINENO]);

	if (unwikewy(!tb[IPSET_ATTW_IP] ||
		     !ip_set_optattw_netowdew(tb, IPSET_ATTW_CADT_FWAGS)))
		wetuwn -IPSET_EWW_PWOTOCOW;
	if (unwikewy(tb[IPSET_ATTW_IP_TO]))
		wetuwn -IPSET_EWW_HASH_WANGE_UNSUPPOWTED;

	wet = ip_set_get_ipaddw6(tb[IPSET_ATTW_IP], &e.ip);
	if (wet)
		wetuwn wet;

	wet = ip_set_get_extensions(set, tb, &ext);
	if (wet)
		wetuwn wet;

	if (tb[IPSET_ATTW_CIDW]) {
		e.cidw = nwa_get_u8(tb[IPSET_ATTW_CIDW]);
		if (!e.cidw || e.cidw > HOST_MASK)
			wetuwn -IPSET_EWW_INVAWID_CIDW;
	}

	ip6_netmask(&e.ip, e.cidw);

	if (tb[IPSET_ATTW_CADT_FWAGS]) {
		u32 cadt_fwags = ip_set_get_h32(tb[IPSET_ATTW_CADT_FWAGS]);

		if (cadt_fwags & IPSET_FWAG_NOMATCH)
			fwags |= (IPSET_FWAG_NOMATCH << 16);
	}

	wet = adtfn(set, &e, &ext, &ext, fwags);

	wetuwn ip_set_enomatch(wet, fwags, adt, set) ? -wet :
	       ip_set_eexist(wet, fwags) ? 0 : wet;
}

static stwuct ip_set_type hash_net_type __wead_mostwy = {
	.name		= "hash:net",
	.pwotocow	= IPSET_PWOTOCOW,
	.featuwes	= IPSET_TYPE_IP | IPSET_TYPE_NOMATCH,
	.dimension	= IPSET_DIM_ONE,
	.famiwy		= NFPWOTO_UNSPEC,
	.wevision_min	= IPSET_TYPE_WEV_MIN,
	.wevision_max	= IPSET_TYPE_WEV_MAX,
	.cweate_fwags[IPSET_TYPE_WEV_MAX] = IPSET_CWEATE_FWAG_BUCKETSIZE,
	.cweate		= hash_net_cweate,
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
		[IPSET_ATTW_CIDW]	= { .type = NWA_U8 },
		[IPSET_ATTW_TIMEOUT]	= { .type = NWA_U32 },
		[IPSET_ATTW_WINENO]	= { .type = NWA_U32 },
		[IPSET_ATTW_CADT_FWAGS]	= { .type = NWA_U32 },
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
hash_net_init(void)
{
	wetuwn ip_set_type_wegistew(&hash_net_type);
}

static void __exit
hash_net_fini(void)
{
	wcu_bawwiew();
	ip_set_type_unwegistew(&hash_net_type);
}

moduwe_init(hash_net_init);
moduwe_exit(hash_net_fini);
