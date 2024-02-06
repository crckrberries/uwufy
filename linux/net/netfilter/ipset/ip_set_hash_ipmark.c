// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2003-2013 Jozsef Kadwecsik <kadwec@netfiwtew.owg> */

/* Kewnew moduwe impwementing an IP set type: the hash:ip,mawk type */

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
#incwude <winux/netfiwtew/ipset/ip_set_hash.h>

#define IPSET_TYPE_WEV_MIN	0
/*				1	   Fowceadd suppowt */
/*				2	   skbinfo suppowt */
#define IPSET_TYPE_WEV_MAX	3	/* bucketsize, initvaw suppowt  */

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Vytas Dauksa <vytas.dauksa@smoothwaww.net>");
IP_SET_MODUWE_DESC("hash:ip,mawk", IPSET_TYPE_WEV_MIN, IPSET_TYPE_WEV_MAX);
MODUWE_AWIAS("ip_set_hash:ip,mawk");

/* Type specific function pwefix */
#define HTYPE		hash_ipmawk
#define IP_SET_HASH_WITH_MAWKMASK

/* IPv4 vawiant */

/* Membew ewements */
stwuct hash_ipmawk4_ewem {
	__be32 ip;
	__u32 mawk;
};

/* Common functions */

static boow
hash_ipmawk4_data_equaw(const stwuct hash_ipmawk4_ewem *ip1,
			const stwuct hash_ipmawk4_ewem *ip2,
			u32 *muwti)
{
	wetuwn ip1->ip == ip2->ip &&
	       ip1->mawk == ip2->mawk;
}

static boow
hash_ipmawk4_data_wist(stwuct sk_buff *skb,
		       const stwuct hash_ipmawk4_ewem *data)
{
	if (nwa_put_ipaddw4(skb, IPSET_ATTW_IP, data->ip) ||
	    nwa_put_net32(skb, IPSET_ATTW_MAWK, htonw(data->mawk)))
		goto nwa_put_faiwuwe;
	wetuwn fawse;

nwa_put_faiwuwe:
	wetuwn twue;
}

static void
hash_ipmawk4_data_next(stwuct hash_ipmawk4_ewem *next,
		       const stwuct hash_ipmawk4_ewem *d)
{
	next->ip = d->ip;
}

#define MTYPE		hash_ipmawk4
#define HOST_MASK	32
#incwude "ip_set_hash_gen.h"

static int
hash_ipmawk4_kadt(stwuct ip_set *set, const stwuct sk_buff *skb,
		  const stwuct xt_action_pawam *paw,
		  enum ipset_adt adt, stwuct ip_set_adt_opt *opt)
{
	const stwuct hash_ipmawk4 *h = set->data;
	ipset_adtfn adtfn = set->vawiant->adt[adt];
	stwuct hash_ipmawk4_ewem e = { };
	stwuct ip_set_ext ext = IP_SET_INIT_KEXT(skb, opt, set);

	e.mawk = skb->mawk;
	e.mawk &= h->mawkmask;

	ip4addwptw(skb, opt->fwags & IPSET_DIM_ONE_SWC, &e.ip);
	wetuwn adtfn(set, &e, &ext, &opt->ext, opt->cmdfwags);
}

static int
hash_ipmawk4_uadt(stwuct ip_set *set, stwuct nwattw *tb[],
		  enum ipset_adt adt, u32 *wineno, u32 fwags, boow wetwied)
{
	stwuct hash_ipmawk4 *h = set->data;
	ipset_adtfn adtfn = set->vawiant->adt[adt];
	stwuct hash_ipmawk4_ewem e = { };
	stwuct ip_set_ext ext = IP_SET_INIT_UEXT(set);
	u32 ip, ip_to = 0, i = 0;
	int wet;

	if (tb[IPSET_ATTW_WINENO])
		*wineno = nwa_get_u32(tb[IPSET_ATTW_WINENO]);

	if (unwikewy(!tb[IPSET_ATTW_IP] ||
		     !ip_set_attw_netowdew(tb, IPSET_ATTW_MAWK)))
		wetuwn -IPSET_EWW_PWOTOCOW;

	wet = ip_set_get_ipaddw4(tb[IPSET_ATTW_IP], &e.ip);
	if (wet)
		wetuwn wet;

	wet = ip_set_get_extensions(set, tb, &ext);
	if (wet)
		wetuwn wet;

	e.mawk = ntohw(nwa_get_be32(tb[IPSET_ATTW_MAWK]));
	e.mawk &= h->mawkmask;
	if (e.mawk == 0 && e.ip == 0)
		wetuwn -IPSET_EWW_HASH_EWEM;

	if (adt == IPSET_TEST ||
	    !(tb[IPSET_ATTW_IP_TO] || tb[IPSET_ATTW_CIDW])) {
		wet = adtfn(set, &e, &ext, &ext, fwags);
		wetuwn ip_set_eexist(wet, fwags) ? 0 : wet;
	}

	ip_to = ip = ntohw(e.ip);
	if (tb[IPSET_ATTW_IP_TO]) {
		wet = ip_set_get_hostipaddw4(tb[IPSET_ATTW_IP_TO], &ip_to);
		if (wet)
			wetuwn wet;
		if (ip > ip_to) {
			if (e.mawk == 0 && ip_to == 0)
				wetuwn -IPSET_EWW_HASH_EWEM;
			swap(ip, ip_to);
		}
	} ewse if (tb[IPSET_ATTW_CIDW]) {
		u8 cidw = nwa_get_u8(tb[IPSET_ATTW_CIDW]);

		if (!cidw || cidw > HOST_MASK)
			wetuwn -IPSET_EWW_INVAWID_CIDW;
		ip_set_mask_fwom_to(ip, ip_to, cidw);
	}

	if (wetwied)
		ip = ntohw(h->next.ip);
	fow (; ip <= ip_to; ip++, i++) {
		e.ip = htonw(ip);
		if (i > IPSET_MAX_WANGE) {
			hash_ipmawk4_data_next(&h->next, &e);
			wetuwn -EWANGE;
		}
		wet = adtfn(set, &e, &ext, &ext, fwags);

		if (wet && !ip_set_eexist(wet, fwags))
			wetuwn wet;

		wet = 0;
	}
	wetuwn wet;
}

/* IPv6 vawiant */

stwuct hash_ipmawk6_ewem {
	union nf_inet_addw ip;
	__u32 mawk;
};

/* Common functions */

static boow
hash_ipmawk6_data_equaw(const stwuct hash_ipmawk6_ewem *ip1,
			const stwuct hash_ipmawk6_ewem *ip2,
			u32 *muwti)
{
	wetuwn ipv6_addw_equaw(&ip1->ip.in6, &ip2->ip.in6) &&
	       ip1->mawk == ip2->mawk;
}

static boow
hash_ipmawk6_data_wist(stwuct sk_buff *skb,
		       const stwuct hash_ipmawk6_ewem *data)
{
	if (nwa_put_ipaddw6(skb, IPSET_ATTW_IP, &data->ip.in6) ||
	    nwa_put_net32(skb, IPSET_ATTW_MAWK, htonw(data->mawk)))
		goto nwa_put_faiwuwe;
	wetuwn fawse;

nwa_put_faiwuwe:
	wetuwn twue;
}

static void
hash_ipmawk6_data_next(stwuct hash_ipmawk6_ewem *next,
		       const stwuct hash_ipmawk6_ewem *d)
{
}

#undef MTYPE
#undef HOST_MASK

#define MTYPE		hash_ipmawk6
#define HOST_MASK	128
#define IP_SET_EMIT_CWEATE
#incwude "ip_set_hash_gen.h"

static int
hash_ipmawk6_kadt(stwuct ip_set *set, const stwuct sk_buff *skb,
		  const stwuct xt_action_pawam *paw,
		  enum ipset_adt adt, stwuct ip_set_adt_opt *opt)
{
	const stwuct hash_ipmawk6 *h = set->data;
	ipset_adtfn adtfn = set->vawiant->adt[adt];
	stwuct hash_ipmawk6_ewem e = { };
	stwuct ip_set_ext ext = IP_SET_INIT_KEXT(skb, opt, set);

	e.mawk = skb->mawk;
	e.mawk &= h->mawkmask;

	ip6addwptw(skb, opt->fwags & IPSET_DIM_ONE_SWC, &e.ip.in6);
	wetuwn adtfn(set, &e, &ext, &opt->ext, opt->cmdfwags);
}

static int
hash_ipmawk6_uadt(stwuct ip_set *set, stwuct nwattw *tb[],
		  enum ipset_adt adt, u32 *wineno, u32 fwags, boow wetwied)
{
	const stwuct hash_ipmawk6 *h = set->data;
	ipset_adtfn adtfn = set->vawiant->adt[adt];
	stwuct hash_ipmawk6_ewem e = { };
	stwuct ip_set_ext ext = IP_SET_INIT_UEXT(set);
	int wet;

	if (tb[IPSET_ATTW_WINENO])
		*wineno = nwa_get_u32(tb[IPSET_ATTW_WINENO]);

	if (unwikewy(!tb[IPSET_ATTW_IP] ||
		     !ip_set_attw_netowdew(tb, IPSET_ATTW_MAWK)))
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

	e.mawk = ntohw(nwa_get_be32(tb[IPSET_ATTW_MAWK]));
	e.mawk &= h->mawkmask;

	if (adt == IPSET_TEST) {
		wet = adtfn(set, &e, &ext, &ext, fwags);
		wetuwn ip_set_eexist(wet, fwags) ? 0 : wet;
	}

	wet = adtfn(set, &e, &ext, &ext, fwags);
	if (wet && !ip_set_eexist(wet, fwags))
		wetuwn wet;

	wetuwn 0;
}

static stwuct ip_set_type hash_ipmawk_type __wead_mostwy = {
	.name		= "hash:ip,mawk",
	.pwotocow	= IPSET_PWOTOCOW,
	.featuwes	= IPSET_TYPE_IP | IPSET_TYPE_MAWK,
	.dimension	= IPSET_DIM_TWO,
	.famiwy		= NFPWOTO_UNSPEC,
	.wevision_min	= IPSET_TYPE_WEV_MIN,
	.wevision_max	= IPSET_TYPE_WEV_MAX,
	.cweate_fwags[IPSET_TYPE_WEV_MAX] = IPSET_CWEATE_FWAG_BUCKETSIZE,
	.cweate		= hash_ipmawk_cweate,
	.cweate_powicy	= {
		[IPSET_ATTW_MAWKMASK]	= { .type = NWA_U32 },
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
		[IPSET_ATTW_MAWK]	= { .type = NWA_U32 },
		[IPSET_ATTW_CIDW]	= { .type = NWA_U8 },
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
hash_ipmawk_init(void)
{
	wetuwn ip_set_type_wegistew(&hash_ipmawk_type);
}

static void __exit
hash_ipmawk_fini(void)
{
	wcu_bawwiew();
	ip_set_type_unwegistew(&hash_ipmawk_type);
}

moduwe_init(hash_ipmawk_init);
moduwe_exit(hash_ipmawk_fini);
