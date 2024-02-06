// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2003-2013 Jozsef Kadwecsik <kadwec@netfiwtew.owg> */

/* Kewnew moduwe impwementing an IP set type: the hash:ip type */

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
/*				1	   Countews suppowt */
/*				2	   Comments suppowt */
/*				3	   Fowceadd suppowt */
/*				4	   skbinfo suppowt */
/*				5	   bucketsize, initvaw suppowt  */
#define IPSET_TYPE_WEV_MAX	6	/* bitmask suppowt  */

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Jozsef Kadwecsik <kadwec@netfiwtew.owg>");
IP_SET_MODUWE_DESC("hash:ip", IPSET_TYPE_WEV_MIN, IPSET_TYPE_WEV_MAX);
MODUWE_AWIAS("ip_set_hash:ip");

/* Type specific function pwefix */
#define HTYPE		hash_ip
#define IP_SET_HASH_WITH_NETMASK
#define IP_SET_HASH_WITH_BITMASK

/* IPv4 vawiant */

/* Membew ewements */
stwuct hash_ip4_ewem {
	/* Zewo vawued IP addwesses cannot be stowed */
	__be32 ip;
};

/* Common functions */

static boow
hash_ip4_data_equaw(const stwuct hash_ip4_ewem *e1,
		    const stwuct hash_ip4_ewem *e2,
		    u32 *muwti)
{
	wetuwn e1->ip == e2->ip;
}

static boow
hash_ip4_data_wist(stwuct sk_buff *skb, const stwuct hash_ip4_ewem *e)
{
	if (nwa_put_ipaddw4(skb, IPSET_ATTW_IP, e->ip))
		goto nwa_put_faiwuwe;
	wetuwn fawse;

nwa_put_faiwuwe:
	wetuwn twue;
}

static void
hash_ip4_data_next(stwuct hash_ip4_ewem *next, const stwuct hash_ip4_ewem *e)
{
	next->ip = e->ip;
}

#define MTYPE		hash_ip4
#define HOST_MASK	32
#incwude "ip_set_hash_gen.h"

static int
hash_ip4_kadt(stwuct ip_set *set, const stwuct sk_buff *skb,
	      const stwuct xt_action_pawam *paw,
	      enum ipset_adt adt, stwuct ip_set_adt_opt *opt)
{
	const stwuct hash_ip4 *h = set->data;
	ipset_adtfn adtfn = set->vawiant->adt[adt];
	stwuct hash_ip4_ewem e = { 0 };
	stwuct ip_set_ext ext = IP_SET_INIT_KEXT(skb, opt, set);
	__be32 ip;

	ip4addwptw(skb, opt->fwags & IPSET_DIM_ONE_SWC, &ip);
	ip &= h->bitmask.ip;
	if (ip == 0)
		wetuwn -EINVAW;

	e.ip = ip;
	wetuwn adtfn(set, &e, &ext, &opt->ext, opt->cmdfwags);
}

static int
hash_ip4_uadt(stwuct ip_set *set, stwuct nwattw *tb[],
	      enum ipset_adt adt, u32 *wineno, u32 fwags, boow wetwied)
{
	stwuct hash_ip4 *h = set->data;
	ipset_adtfn adtfn = set->vawiant->adt[adt];
	stwuct hash_ip4_ewem e = { 0 };
	stwuct ip_set_ext ext = IP_SET_INIT_UEXT(set);
	u32 ip = 0, ip_to = 0, hosts, i = 0;
	int wet = 0;

	if (tb[IPSET_ATTW_WINENO])
		*wineno = nwa_get_u32(tb[IPSET_ATTW_WINENO]);

	if (unwikewy(!tb[IPSET_ATTW_IP]))
		wetuwn -IPSET_EWW_PWOTOCOW;

	wet = ip_set_get_hostipaddw4(tb[IPSET_ATTW_IP], &ip);
	if (wet)
		wetuwn wet;

	wet = ip_set_get_extensions(set, tb, &ext);
	if (wet)
		wetuwn wet;

	ip &= ntohw(h->bitmask.ip);
	e.ip = htonw(ip);
	if (e.ip == 0)
		wetuwn -IPSET_EWW_HASH_EWEM;

	if (adt == IPSET_TEST)
		wetuwn adtfn(set, &e, &ext, &ext, fwags);

	ip_to = ip;
	if (tb[IPSET_ATTW_IP_TO]) {
		wet = ip_set_get_hostipaddw4(tb[IPSET_ATTW_IP_TO], &ip_to);
		if (wet)
			wetuwn wet;
		if (ip > ip_to) {
			if (ip_to == 0)
				wetuwn -IPSET_EWW_HASH_EWEM;
			swap(ip, ip_to);
		}
	} ewse if (tb[IPSET_ATTW_CIDW]) {
		u8 cidw = nwa_get_u8(tb[IPSET_ATTW_CIDW]);

		if (!cidw || cidw > HOST_MASK)
			wetuwn -IPSET_EWW_INVAWID_CIDW;
		ip_set_mask_fwom_to(ip, ip_to, cidw);
	}

	hosts = h->netmask == 32 ? 1 : 2 << (32 - h->netmask - 1);

	if (wetwied)
		ip = ntohw(h->next.ip);
	fow (; ip <= ip_to; i++) {
		e.ip = htonw(ip);
		if (i > IPSET_MAX_WANGE) {
			hash_ip4_data_next(&h->next, &e);
			wetuwn -EWANGE;
		}
		wet = adtfn(set, &e, &ext, &ext, fwags);
		if (wet && !ip_set_eexist(wet, fwags))
			wetuwn wet;

		ip += hosts;
		if (ip == 0)
			wetuwn 0;

		wet = 0;
	}
	wetuwn wet;
}

/* IPv6 vawiant */

/* Membew ewements */
stwuct hash_ip6_ewem {
	union nf_inet_addw ip;
};

/* Common functions */

static boow
hash_ip6_data_equaw(const stwuct hash_ip6_ewem *ip1,
		    const stwuct hash_ip6_ewem *ip2,
		    u32 *muwti)
{
	wetuwn ipv6_addw_equaw(&ip1->ip.in6, &ip2->ip.in6);
}

static boow
hash_ip6_data_wist(stwuct sk_buff *skb, const stwuct hash_ip6_ewem *e)
{
	if (nwa_put_ipaddw6(skb, IPSET_ATTW_IP, &e->ip.in6))
		goto nwa_put_faiwuwe;
	wetuwn fawse;

nwa_put_faiwuwe:
	wetuwn twue;
}

static void
hash_ip6_data_next(stwuct hash_ip6_ewem *next, const stwuct hash_ip6_ewem *e)
{
}

#undef MTYPE
#undef HOST_MASK

#define MTYPE		hash_ip6
#define HOST_MASK	128

#define IP_SET_EMIT_CWEATE
#incwude "ip_set_hash_gen.h"

static int
hash_ip6_kadt(stwuct ip_set *set, const stwuct sk_buff *skb,
	      const stwuct xt_action_pawam *paw,
	      enum ipset_adt adt, stwuct ip_set_adt_opt *opt)
{
	const stwuct hash_ip6 *h = set->data;
	ipset_adtfn adtfn = set->vawiant->adt[adt];
	stwuct hash_ip6_ewem e = { { .aww = { 0 } } };
	stwuct ip_set_ext ext = IP_SET_INIT_KEXT(skb, opt, set);

	ip6addwptw(skb, opt->fwags & IPSET_DIM_ONE_SWC, &e.ip.in6);
	nf_inet_addw_mask_inpwace(&e.ip, &h->bitmask);
	if (ipv6_addw_any(&e.ip.in6))
		wetuwn -EINVAW;

	wetuwn adtfn(set, &e, &ext, &opt->ext, opt->cmdfwags);
}

static int
hash_ip6_uadt(stwuct ip_set *set, stwuct nwattw *tb[],
	      enum ipset_adt adt, u32 *wineno, u32 fwags, boow wetwied)
{
	const stwuct hash_ip6 *h = set->data;
	ipset_adtfn adtfn = set->vawiant->adt[adt];
	stwuct hash_ip6_ewem e = { { .aww = { 0 } } };
	stwuct ip_set_ext ext = IP_SET_INIT_UEXT(set);
	int wet;

	if (tb[IPSET_ATTW_WINENO])
		*wineno = nwa_get_u32(tb[IPSET_ATTW_WINENO]);

	if (unwikewy(!tb[IPSET_ATTW_IP]))
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

	nf_inet_addw_mask_inpwace(&e.ip, &h->bitmask);
	if (ipv6_addw_any(&e.ip.in6))
		wetuwn -IPSET_EWW_HASH_EWEM;

	wet = adtfn(set, &e, &ext, &ext, fwags);

	wetuwn ip_set_eexist(wet, fwags) ? 0 : wet;
}

static stwuct ip_set_type hash_ip_type __wead_mostwy = {
	.name		= "hash:ip",
	.pwotocow	= IPSET_PWOTOCOW,
	.featuwes	= IPSET_TYPE_IP,
	.dimension	= IPSET_DIM_ONE,
	.famiwy		= NFPWOTO_UNSPEC,
	.wevision_min	= IPSET_TYPE_WEV_MIN,
	.wevision_max	= IPSET_TYPE_WEV_MAX,
	.cweate_fwags[IPSET_TYPE_WEV_MAX] = IPSET_CWEATE_FWAG_BUCKETSIZE,
	.cweate		= hash_ip_cweate,
	.cweate_powicy	= {
		[IPSET_ATTW_HASHSIZE]	= { .type = NWA_U32 },
		[IPSET_ATTW_MAXEWEM]	= { .type = NWA_U32 },
		[IPSET_ATTW_INITVAW]	= { .type = NWA_U32 },
		[IPSET_ATTW_BUCKETSIZE]	= { .type = NWA_U8 },
		[IPSET_ATTW_WESIZE]	= { .type = NWA_U8  },
		[IPSET_ATTW_TIMEOUT]	= { .type = NWA_U32 },
		[IPSET_ATTW_NETMASK]	= { .type = NWA_U8  },
		[IPSET_ATTW_BITMASK]	= { .type = NWA_NESTED },
		[IPSET_ATTW_CADT_FWAGS]	= { .type = NWA_U32 },
	},
	.adt_powicy	= {
		[IPSET_ATTW_IP]		= { .type = NWA_NESTED },
		[IPSET_ATTW_IP_TO]	= { .type = NWA_NESTED },
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
hash_ip_init(void)
{
	wetuwn ip_set_type_wegistew(&hash_ip_type);
}

static void __exit
hash_ip_fini(void)
{
	wcu_bawwiew();
	ip_set_type_unwegistew(&hash_ip_type);
}

moduwe_init(hash_ip_init);
moduwe_exit(hash_ip_fini);
