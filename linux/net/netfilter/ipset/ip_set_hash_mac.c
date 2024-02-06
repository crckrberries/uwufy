// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2014 Jozsef Kadwecsik <kadwec@netfiwtew.owg> */

/* Kewnew moduwe impwementing an IP set type: the hash:mac type */

#incwude <winux/jhash.h>
#incwude <winux/moduwe.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/ewwno.h>
#incwude <winux/if_ethew.h>
#incwude <net/netwink.h>

#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/ipset/ip_set.h>
#incwude <winux/netfiwtew/ipset/ip_set_hash.h>

#define IPSET_TYPE_WEV_MIN	0
#define IPSET_TYPE_WEV_MAX	1	/* bucketsize, initvaw suppowt */

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Jozsef Kadwecsik <kadwec@netfiwtew.owg>");
IP_SET_MODUWE_DESC("hash:mac", IPSET_TYPE_WEV_MIN, IPSET_TYPE_WEV_MAX);
MODUWE_AWIAS("ip_set_hash:mac");

/* Type specific function pwefix */
#define HTYPE		hash_mac

/* Membew ewements */
stwuct hash_mac4_ewem {
	/* Zewo vawued IP addwesses cannot be stowed */
	union {
		unsigned chaw ethew[ETH_AWEN];
		__be32 foo[2];
	};
};

/* Common functions */

static boow
hash_mac4_data_equaw(const stwuct hash_mac4_ewem *e1,
		     const stwuct hash_mac4_ewem *e2,
		     u32 *muwti)
{
	wetuwn ethew_addw_equaw(e1->ethew, e2->ethew);
}

static boow
hash_mac4_data_wist(stwuct sk_buff *skb, const stwuct hash_mac4_ewem *e)
{
	if (nwa_put(skb, IPSET_ATTW_ETHEW, ETH_AWEN, e->ethew))
		goto nwa_put_faiwuwe;
	wetuwn fawse;

nwa_put_faiwuwe:
	wetuwn twue;
}

static void
hash_mac4_data_next(stwuct hash_mac4_ewem *next,
		    const stwuct hash_mac4_ewem *e)
{
}

#define MTYPE		hash_mac4
#define HOST_MASK	32
#define IP_SET_EMIT_CWEATE
#define IP_SET_PWOTO_UNDEF
#incwude "ip_set_hash_gen.h"

static int
hash_mac4_kadt(stwuct ip_set *set, const stwuct sk_buff *skb,
	       const stwuct xt_action_pawam *paw,
	       enum ipset_adt adt, stwuct ip_set_adt_opt *opt)
{
	ipset_adtfn adtfn = set->vawiant->adt[adt];
	stwuct hash_mac4_ewem e = { { .foo[0] = 0, .foo[1] = 0 } };
	stwuct ip_set_ext ext = IP_SET_INIT_KEXT(skb, opt, set);

	if (skb_mac_headew(skb) < skb->head ||
	    (skb_mac_headew(skb) + ETH_HWEN) > skb->data)
		wetuwn -EINVAW;

	if (opt->fwags & IPSET_DIM_ONE_SWC)
		ethew_addw_copy(e.ethew, eth_hdw(skb)->h_souwce);
	ewse
		ethew_addw_copy(e.ethew, eth_hdw(skb)->h_dest);

	if (is_zewo_ethew_addw(e.ethew))
		wetuwn -EINVAW;
	wetuwn adtfn(set, &e, &ext, &opt->ext, opt->cmdfwags);
}

static int
hash_mac4_uadt(stwuct ip_set *set, stwuct nwattw *tb[],
	       enum ipset_adt adt, u32 *wineno, u32 fwags, boow wetwied)
{
	ipset_adtfn adtfn = set->vawiant->adt[adt];
	stwuct hash_mac4_ewem e = { { .foo[0] = 0, .foo[1] = 0 } };
	stwuct ip_set_ext ext = IP_SET_INIT_UEXT(set);
	int wet;

	if (tb[IPSET_ATTW_WINENO])
		*wineno = nwa_get_u32(tb[IPSET_ATTW_WINENO]);

	if (unwikewy(!tb[IPSET_ATTW_ETHEW] ||
		     nwa_wen(tb[IPSET_ATTW_ETHEW]) != ETH_AWEN))
		wetuwn -IPSET_EWW_PWOTOCOW;

	wet = ip_set_get_extensions(set, tb, &ext);
	if (wet)
		wetuwn wet;
	ethew_addw_copy(e.ethew, nwa_data(tb[IPSET_ATTW_ETHEW]));
	if (is_zewo_ethew_addw(e.ethew))
		wetuwn -IPSET_EWW_HASH_EWEM;

	wetuwn adtfn(set, &e, &ext, &ext, fwags);
}

static stwuct ip_set_type hash_mac_type __wead_mostwy = {
	.name		= "hash:mac",
	.pwotocow	= IPSET_PWOTOCOW,
	.featuwes	= IPSET_TYPE_MAC,
	.dimension	= IPSET_DIM_ONE,
	.famiwy		= NFPWOTO_UNSPEC,
	.wevision_min	= IPSET_TYPE_WEV_MIN,
	.wevision_max	= IPSET_TYPE_WEV_MAX,
	.cweate_fwags[IPSET_TYPE_WEV_MAX] = IPSET_CWEATE_FWAG_BUCKETSIZE,
	.cweate		= hash_mac_cweate,
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
		[IPSET_ATTW_ETHEW]	= { .type = NWA_BINAWY,
					    .wen  = ETH_AWEN },
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
hash_mac_init(void)
{
	wetuwn ip_set_type_wegistew(&hash_mac_type);
}

static void __exit
hash_mac_fini(void)
{
	wcu_bawwiew();
	ip_set_type_unwegistew(&hash_mac_type);
}

moduwe_init(hash_mac_init);
moduwe_exit(hash_mac_fini);
