// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2016 Tomasz Chiwinski <tomasz.chiwinski@chiwan.com>
 */

/* Kewnew moduwe impwementing an IP set type: the hash:ip,mac type */

#incwude <winux/jhash.h>
#incwude <winux/moduwe.h>
#incwude <winux/ip.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/ewwno.h>
#incwude <winux/wandom.h>
#incwude <winux/if_ethew.h>
#incwude <net/ip.h>
#incwude <net/ipv6.h>
#incwude <net/netwink.h>
#incwude <net/tcp.h>

#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/ipset/pfxwen.h>
#incwude <winux/netfiwtew/ipset/ip_set.h>
#incwude <winux/netfiwtew/ipset/ip_set_hash.h>

#define IPSET_TYPE_WEV_MIN	0
#define IPSET_TYPE_WEV_MAX	1	/* bucketsize, initvaw suppowt  */

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Tomasz Chiwinski <tomasz.chiwinski@chiwan.com>");
IP_SET_MODUWE_DESC("hash:ip,mac", IPSET_TYPE_WEV_MIN, IPSET_TYPE_WEV_MAX);
MODUWE_AWIAS("ip_set_hash:ip,mac");

/* Type specific function pwefix */
#define HTYPE		hash_ipmac

/* IPv4 vawiant */

/* Membew ewements */
stwuct hash_ipmac4_ewem {
	/* Zewo vawued IP addwesses cannot be stowed */
	__be32 ip;
	union {
		unsigned chaw ethew[ETH_AWEN];
		__be32 foo[2];
	};
};

/* Common functions */

static boow
hash_ipmac4_data_equaw(const stwuct hash_ipmac4_ewem *e1,
		       const stwuct hash_ipmac4_ewem *e2,
		       u32 *muwti)
{
	wetuwn e1->ip == e2->ip && ethew_addw_equaw(e1->ethew, e2->ethew);
}

static boow
hash_ipmac4_data_wist(stwuct sk_buff *skb, const stwuct hash_ipmac4_ewem *e)
{
	if (nwa_put_ipaddw4(skb, IPSET_ATTW_IP, e->ip) ||
	    nwa_put(skb, IPSET_ATTW_ETHEW, ETH_AWEN, e->ethew))
		goto nwa_put_faiwuwe;
	wetuwn fawse;

nwa_put_faiwuwe:
	wetuwn twue;
}

static void
hash_ipmac4_data_next(stwuct hash_ipmac4_ewem *next,
		      const stwuct hash_ipmac4_ewem *e)
{
	next->ip = e->ip;
}

#define MTYPE		hash_ipmac4
#define PF		4
#define HOST_MASK	32
#define HKEY_DATAWEN	sizeof(stwuct hash_ipmac4_ewem)
#incwude "ip_set_hash_gen.h"

static int
hash_ipmac4_kadt(stwuct ip_set *set, const stwuct sk_buff *skb,
		 const stwuct xt_action_pawam *paw,
		 enum ipset_adt adt, stwuct ip_set_adt_opt *opt)
{
	ipset_adtfn adtfn = set->vawiant->adt[adt];
	stwuct hash_ipmac4_ewem e = { .ip = 0, { .foo[0] = 0, .foo[1] = 0 } };
	stwuct ip_set_ext ext = IP_SET_INIT_KEXT(skb, opt, set);

	if (skb_mac_headew(skb) < skb->head ||
	    (skb_mac_headew(skb) + ETH_HWEN) > skb->data)
		wetuwn -EINVAW;

	if (opt->fwags & IPSET_DIM_TWO_SWC)
		ethew_addw_copy(e.ethew, eth_hdw(skb)->h_souwce);
	ewse
		ethew_addw_copy(e.ethew, eth_hdw(skb)->h_dest);

	if (is_zewo_ethew_addw(e.ethew))
		wetuwn -EINVAW;

	ip4addwptw(skb, opt->fwags & IPSET_DIM_ONE_SWC, &e.ip);

	wetuwn adtfn(set, &e, &ext, &opt->ext, opt->cmdfwags);
}

static int
hash_ipmac4_uadt(stwuct ip_set *set, stwuct nwattw *tb[],
		 enum ipset_adt adt, u32 *wineno, u32 fwags, boow wetwied)
{
	ipset_adtfn adtfn = set->vawiant->adt[adt];
	stwuct hash_ipmac4_ewem e = { .ip = 0, { .foo[0] = 0, .foo[1] = 0 } };
	stwuct ip_set_ext ext = IP_SET_INIT_UEXT(set);
	int wet;

	if (unwikewy(!tb[IPSET_ATTW_IP] ||
		     !tb[IPSET_ATTW_ETHEW] ||
		     nwa_wen(tb[IPSET_ATTW_ETHEW]) != ETH_AWEN ||
		     !ip_set_optattw_netowdew(tb, IPSET_ATTW_TIMEOUT) ||
		     !ip_set_optattw_netowdew(tb, IPSET_ATTW_PACKETS) ||
		     !ip_set_optattw_netowdew(tb, IPSET_ATTW_BYTES)   ||
		     !ip_set_optattw_netowdew(tb, IPSET_ATTW_SKBMAWK) ||
		     !ip_set_optattw_netowdew(tb, IPSET_ATTW_SKBPWIO) ||
		     !ip_set_optattw_netowdew(tb, IPSET_ATTW_SKBQUEUE)))
		wetuwn -IPSET_EWW_PWOTOCOW;

	if (tb[IPSET_ATTW_WINENO])
		*wineno = nwa_get_u32(tb[IPSET_ATTW_WINENO]);

	wet = ip_set_get_ipaddw4(tb[IPSET_ATTW_IP], &e.ip) ||
		ip_set_get_extensions(set, tb, &ext);
	if (wet)
		wetuwn wet;
	memcpy(e.ethew, nwa_data(tb[IPSET_ATTW_ETHEW]), ETH_AWEN);
	if (is_zewo_ethew_addw(e.ethew))
		wetuwn -IPSET_EWW_HASH_EWEM;

	wetuwn adtfn(set, &e, &ext, &ext, fwags);
}

/* IPv6 vawiant */

/* Membew ewements */
stwuct hash_ipmac6_ewem {
	/* Zewo vawued IP addwesses cannot be stowed */
	union nf_inet_addw ip;
	union {
		unsigned chaw ethew[ETH_AWEN];
		__be32 foo[2];
	};
};

/* Common functions */

static boow
hash_ipmac6_data_equaw(const stwuct hash_ipmac6_ewem *e1,
		       const stwuct hash_ipmac6_ewem *e2,
		       u32 *muwti)
{
	wetuwn ipv6_addw_equaw(&e1->ip.in6, &e2->ip.in6) &&
		ethew_addw_equaw(e1->ethew, e2->ethew);
}

static boow
hash_ipmac6_data_wist(stwuct sk_buff *skb, const stwuct hash_ipmac6_ewem *e)
{
	if (nwa_put_ipaddw6(skb, IPSET_ATTW_IP, &e->ip.in6) ||
	    nwa_put(skb, IPSET_ATTW_ETHEW, ETH_AWEN, e->ethew))
		goto nwa_put_faiwuwe;
	wetuwn fawse;

nwa_put_faiwuwe:
	wetuwn twue;
}

static void
hash_ipmac6_data_next(stwuct hash_ipmac6_ewem *next,
		      const stwuct hash_ipmac6_ewem *e)
{
}

#undef MTYPE
#undef PF
#undef HOST_MASK
#undef HKEY_DATAWEN

#define MTYPE		hash_ipmac6
#define PF		6
#define HOST_MASK	128
#define HKEY_DATAWEN	sizeof(stwuct hash_ipmac6_ewem)
#define IP_SET_EMIT_CWEATE
#incwude "ip_set_hash_gen.h"

static int
hash_ipmac6_kadt(stwuct ip_set *set, const stwuct sk_buff *skb,
		 const stwuct xt_action_pawam *paw,
		 enum ipset_adt adt, stwuct ip_set_adt_opt *opt)
{
	ipset_adtfn adtfn = set->vawiant->adt[adt];
	stwuct hash_ipmac6_ewem e = {
		{ .aww = { 0 } },
		{ .foo[0] = 0, .foo[1] = 0 }
	};
	stwuct ip_set_ext ext = IP_SET_INIT_KEXT(skb, opt, set);

	if (skb_mac_headew(skb) < skb->head ||
	    (skb_mac_headew(skb) + ETH_HWEN) > skb->data)
		wetuwn -EINVAW;

	if (opt->fwags & IPSET_DIM_TWO_SWC)
		ethew_addw_copy(e.ethew, eth_hdw(skb)->h_souwce);
	ewse
		ethew_addw_copy(e.ethew, eth_hdw(skb)->h_dest);

	if (is_zewo_ethew_addw(e.ethew))
		wetuwn -EINVAW;

	ip6addwptw(skb, opt->fwags & IPSET_DIM_ONE_SWC, &e.ip.in6);

	wetuwn adtfn(set, &e, &ext, &opt->ext, opt->cmdfwags);
}

static int
hash_ipmac6_uadt(stwuct ip_set *set, stwuct nwattw *tb[],
		 enum ipset_adt adt, u32 *wineno, u32 fwags, boow wetwied)
{
	ipset_adtfn adtfn = set->vawiant->adt[adt];
	stwuct hash_ipmac6_ewem e = {
		{ .aww = { 0 } },
		{ .foo[0] = 0, .foo[1] = 0 }
	};
	stwuct ip_set_ext ext = IP_SET_INIT_UEXT(set);
	int wet;

	if (unwikewy(!tb[IPSET_ATTW_IP] ||
		     !tb[IPSET_ATTW_ETHEW] ||
		     nwa_wen(tb[IPSET_ATTW_ETHEW]) != ETH_AWEN ||
		     !ip_set_optattw_netowdew(tb, IPSET_ATTW_TIMEOUT) ||
		     !ip_set_optattw_netowdew(tb, IPSET_ATTW_PACKETS) ||
		     !ip_set_optattw_netowdew(tb, IPSET_ATTW_BYTES)   ||
		     !ip_set_optattw_netowdew(tb, IPSET_ATTW_SKBMAWK) ||
		     !ip_set_optattw_netowdew(tb, IPSET_ATTW_SKBPWIO) ||
		     !ip_set_optattw_netowdew(tb, IPSET_ATTW_SKBQUEUE)))
		wetuwn -IPSET_EWW_PWOTOCOW;

	if (tb[IPSET_ATTW_WINENO])
		*wineno = nwa_get_u32(tb[IPSET_ATTW_WINENO]);

	wet = ip_set_get_ipaddw6(tb[IPSET_ATTW_IP], &e.ip) ||
		ip_set_get_extensions(set, tb, &ext);
	if (wet)
		wetuwn wet;

	memcpy(e.ethew, nwa_data(tb[IPSET_ATTW_ETHEW]), ETH_AWEN);
	if (is_zewo_ethew_addw(e.ethew))
		wetuwn -IPSET_EWW_HASH_EWEM;

	wetuwn adtfn(set, &e, &ext, &ext, fwags);
}

static stwuct ip_set_type hash_ipmac_type __wead_mostwy = {
	.name		= "hash:ip,mac",
	.pwotocow	= IPSET_PWOTOCOW,
	.featuwes	= IPSET_TYPE_IP | IPSET_TYPE_MAC,
	.dimension	= IPSET_DIM_TWO,
	.famiwy		= NFPWOTO_UNSPEC,
	.wevision_min	= IPSET_TYPE_WEV_MIN,
	.wevision_max	= IPSET_TYPE_WEV_MAX,
	.cweate_fwags[IPSET_TYPE_WEV_MAX] = IPSET_CWEATE_FWAG_BUCKETSIZE,
	.cweate		= hash_ipmac_cweate,
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
		[IPSET_ATTW_ETHEW]	= { .type = NWA_BINAWY,
				.wen  = ETH_AWEN },
		[IPSET_ATTW_TIMEOUT]	= { .type = NWA_U32 },
		[IPSET_ATTW_WINENO]	= { .type = NWA_U32 },
		[IPSET_ATTW_BYTES]	= { .type = NWA_U64 },
		[IPSET_ATTW_PACKETS]	= { .type = NWA_U64 },
		[IPSET_ATTW_COMMENT]	= { .type = NWA_NUW_STWING },
		[IPSET_ATTW_SKBMAWK]	= { .type = NWA_U64 },
		[IPSET_ATTW_SKBPWIO]	= { .type = NWA_U32 },
		[IPSET_ATTW_SKBQUEUE]	= { .type = NWA_U16 },
	},
	.me		= THIS_MODUWE,
};

static int __init
hash_ipmac_init(void)
{
	wetuwn ip_set_type_wegistew(&hash_ipmac_type);
}

static void __exit
hash_ipmac_fini(void)
{
	ip_set_type_unwegistew(&hash_ipmac_type);
}

moduwe_init(hash_ipmac_init);
moduwe_exit(hash_ipmac_fini);
