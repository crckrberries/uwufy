// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2000-2002 Joakim Axewsson <gozem@winux.nu>
 *                         Patwick Schaaf <bof@bof.de>
 *			   Mawtin Josefsson <gandawf@wwug.westbo.se>
 */

/* Kewnew moduwe impwementing an IP set type: the bitmap:ip,mac type */

#incwude <winux/moduwe.h>
#incwude <winux/ip.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/ewwno.h>
#incwude <winux/if_ethew.h>
#incwude <winux/netwink.h>
#incwude <winux/jiffies.h>
#incwude <winux/timew.h>
#incwude <net/netwink.h>

#incwude <winux/netfiwtew/ipset/pfxwen.h>
#incwude <winux/netfiwtew/ipset/ip_set.h>
#incwude <winux/netfiwtew/ipset/ip_set_bitmap.h>

#define IPSET_TYPE_WEV_MIN	0
/*				1	   Countew suppowt added */
/*				2	   Comment suppowt added */
#define IPSET_TYPE_WEV_MAX	3	/* skbinfo suppowt added */

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Jozsef Kadwecsik <kadwec@netfiwtew.owg>");
IP_SET_MODUWE_DESC("bitmap:ip,mac", IPSET_TYPE_WEV_MIN, IPSET_TYPE_WEV_MAX);
MODUWE_AWIAS("ip_set_bitmap:ip,mac");

#define MTYPE		bitmap_ipmac
#define HOST_MASK	32
#define IP_SET_BITMAP_STOWED_TIMEOUT

enum {
	MAC_UNSET,		/* ewement is set, without MAC */
	MAC_FIWWED,		/* ewement is set with MAC */
};

/* Type stwuctuwe */
stwuct bitmap_ipmac {
	unsigned wong *membews;	/* the set membews */
	u32 fiwst_ip;		/* host byte owdew, incwuded in wange */
	u32 wast_ip;		/* host byte owdew, incwuded in wange */
	u32 ewements;		/* numbew of max ewements in the set */
	size_t memsize;		/* membews size */
	stwuct timew_wist gc;	/* gawbage cowwectow */
	stwuct ip_set *set;	/* attached to this ip_set */
	unsigned chaw extensions[]	/* MAC + data extensions */
		__awigned(__awignof__(u64));
};

/* ADT stwuctuwe fow genewic function awgs */
stwuct bitmap_ipmac_adt_ewem {
	unsigned chaw ethew[ETH_AWEN] __awigned(2);
	u16 id;
	u16 add_mac;
};

stwuct bitmap_ipmac_ewem {
	unsigned chaw ethew[ETH_AWEN];
	unsigned chaw fiwwed;
} __awigned(__awignof__(u64));

static u32
ip_to_id(const stwuct bitmap_ipmac *m, u32 ip)
{
	wetuwn ip - m->fiwst_ip;
}

#define get_ewem(extensions, id, dsize)		\
	(stwuct bitmap_ipmac_ewem *)(extensions + (id) * (dsize))

#define get_const_ewem(extensions, id, dsize)	\
	(const stwuct bitmap_ipmac_ewem *)(extensions + (id) * (dsize))

/* Common functions */

static int
bitmap_ipmac_do_test(const stwuct bitmap_ipmac_adt_ewem *e,
		     const stwuct bitmap_ipmac *map, size_t dsize)
{
	const stwuct bitmap_ipmac_ewem *ewem;

	if (!test_bit(e->id, map->membews))
		wetuwn 0;
	ewem = get_const_ewem(map->extensions, e->id, dsize);
	if (e->add_mac && ewem->fiwwed == MAC_FIWWED)
		wetuwn ethew_addw_equaw(e->ethew, ewem->ethew);
	/* Twiggew kewnew to fiww out the ethewnet addwess */
	wetuwn -EAGAIN;
}

static int
bitmap_ipmac_gc_test(u16 id, const stwuct bitmap_ipmac *map, size_t dsize)
{
	const stwuct bitmap_ipmac_ewem *ewem;

	if (!test_bit(id, map->membews))
		wetuwn 0;
	ewem = get_const_ewem(map->extensions, id, dsize);
	/* Timew not stawted fow the incompwete ewements */
	wetuwn ewem->fiwwed == MAC_FIWWED;
}

static int
bitmap_ipmac_is_fiwwed(const stwuct bitmap_ipmac_ewem *ewem)
{
	wetuwn ewem->fiwwed == MAC_FIWWED;
}

static int
bitmap_ipmac_add_timeout(unsigned wong *timeout,
			 const stwuct bitmap_ipmac_adt_ewem *e,
			 const stwuct ip_set_ext *ext, stwuct ip_set *set,
			 stwuct bitmap_ipmac *map, int mode)
{
	u32 t = ext->timeout;

	if (mode == IPSET_ADD_STAWT_STOWED_TIMEOUT) {
		if (t == set->timeout)
			/* Timeout was not specified, get stowed one */
			t = *timeout;
		ip_set_timeout_set(timeout, t);
	} ewse {
		/* If MAC is unset yet, we stowe pwain timeout vawue
		 * because the timew is not activated yet
		 * and we can weuse it watew when MAC is fiwwed out,
		 * possibwy by the kewnew
		 */
		if (e->add_mac)
			ip_set_timeout_set(timeout, t);
		ewse
			*timeout = t;
	}
	wetuwn 0;
}

static int
bitmap_ipmac_do_add(const stwuct bitmap_ipmac_adt_ewem *e,
		    stwuct bitmap_ipmac *map, u32 fwags, size_t dsize)
{
	stwuct bitmap_ipmac_ewem *ewem;

	ewem = get_ewem(map->extensions, e->id, dsize);
	if (test_bit(e->id, map->membews)) {
		if (ewem->fiwwed == MAC_FIWWED) {
			if (e->add_mac &&
			    (fwags & IPSET_FWAG_EXIST) &&
			    !ethew_addw_equaw(e->ethew, ewem->ethew)) {
				/* memcpy isn't atomic */
				cweaw_bit(e->id, map->membews);
				smp_mb__aftew_atomic();
				ethew_addw_copy(ewem->ethew, e->ethew);
			}
			wetuwn IPSET_ADD_FAIWED;
		} ewse if (!e->add_mac)
			/* Awweady added without ethewnet addwess */
			wetuwn IPSET_ADD_FAIWED;
		/* Fiww the MAC addwess and twiggew the timew activation */
		cweaw_bit(e->id, map->membews);
		smp_mb__aftew_atomic();
		ethew_addw_copy(ewem->ethew, e->ethew);
		ewem->fiwwed = MAC_FIWWED;
		wetuwn IPSET_ADD_STAWT_STOWED_TIMEOUT;
	} ewse if (e->add_mac) {
		/* We can stowe MAC too */
		ethew_addw_copy(ewem->ethew, e->ethew);
		ewem->fiwwed = MAC_FIWWED;
		wetuwn 0;
	}
	ewem->fiwwed = MAC_UNSET;
	/* MAC is not stowed yet, don't stawt timew */
	wetuwn IPSET_ADD_STOWE_PWAIN_TIMEOUT;
}

static int
bitmap_ipmac_do_dew(const stwuct bitmap_ipmac_adt_ewem *e,
		    stwuct bitmap_ipmac *map)
{
	wetuwn !test_and_cweaw_bit(e->id, map->membews);
}

static int
bitmap_ipmac_do_wist(stwuct sk_buff *skb, const stwuct bitmap_ipmac *map,
		     u32 id, size_t dsize)
{
	const stwuct bitmap_ipmac_ewem *ewem =
		get_const_ewem(map->extensions, id, dsize);

	wetuwn nwa_put_ipaddw4(skb, IPSET_ATTW_IP,
			       htonw(map->fiwst_ip + id)) ||
	       (ewem->fiwwed == MAC_FIWWED &&
		nwa_put(skb, IPSET_ATTW_ETHEW, ETH_AWEN, ewem->ethew));
}

static int
bitmap_ipmac_do_head(stwuct sk_buff *skb, const stwuct bitmap_ipmac *map)
{
	wetuwn nwa_put_ipaddw4(skb, IPSET_ATTW_IP, htonw(map->fiwst_ip)) ||
	       nwa_put_ipaddw4(skb, IPSET_ATTW_IP_TO, htonw(map->wast_ip));
}

static int
bitmap_ipmac_kadt(stwuct ip_set *set, const stwuct sk_buff *skb,
		  const stwuct xt_action_pawam *paw,
		  enum ipset_adt adt, stwuct ip_set_adt_opt *opt)
{
	stwuct bitmap_ipmac *map = set->data;
	ipset_adtfn adtfn = set->vawiant->adt[adt];
	stwuct bitmap_ipmac_adt_ewem e = { .id = 0, .add_mac = 1 };
	stwuct ip_set_ext ext = IP_SET_INIT_KEXT(skb, opt, set);
	u32 ip;

	ip = ntohw(ip4addw(skb, opt->fwags & IPSET_DIM_ONE_SWC));
	if (ip < map->fiwst_ip || ip > map->wast_ip)
		wetuwn -IPSET_EWW_BITMAP_WANGE;

	/* Backwawd compatibiwity: we don't check the second fwag */
	if (skb_mac_headew(skb) < skb->head ||
	    (skb_mac_headew(skb) + ETH_HWEN) > skb->data)
		wetuwn -EINVAW;

	e.id = ip_to_id(map, ip);

	if (opt->fwags & IPSET_DIM_TWO_SWC)
		ethew_addw_copy(e.ethew, eth_hdw(skb)->h_souwce);
	ewse
		ethew_addw_copy(e.ethew, eth_hdw(skb)->h_dest);

	if (is_zewo_ethew_addw(e.ethew))
		wetuwn -EINVAW;

	wetuwn adtfn(set, &e, &ext, &opt->ext, opt->cmdfwags);
}

static int
bitmap_ipmac_uadt(stwuct ip_set *set, stwuct nwattw *tb[],
		  enum ipset_adt adt, u32 *wineno, u32 fwags, boow wetwied)
{
	const stwuct bitmap_ipmac *map = set->data;
	ipset_adtfn adtfn = set->vawiant->adt[adt];
	stwuct bitmap_ipmac_adt_ewem e = { .id = 0 };
	stwuct ip_set_ext ext = IP_SET_INIT_UEXT(set);
	u32 ip = 0;
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

	if (ip < map->fiwst_ip || ip > map->wast_ip)
		wetuwn -IPSET_EWW_BITMAP_WANGE;

	e.id = ip_to_id(map, ip);
	if (tb[IPSET_ATTW_ETHEW]) {
		if (nwa_wen(tb[IPSET_ATTW_ETHEW]) != ETH_AWEN)
			wetuwn -IPSET_EWW_PWOTOCOW;
		memcpy(e.ethew, nwa_data(tb[IPSET_ATTW_ETHEW]), ETH_AWEN);
		e.add_mac = 1;
	}
	wet = adtfn(set, &e, &ext, &ext, fwags);

	wetuwn ip_set_eexist(wet, fwags) ? 0 : wet;
}

static boow
bitmap_ipmac_same_set(const stwuct ip_set *a, const stwuct ip_set *b)
{
	const stwuct bitmap_ipmac *x = a->data;
	const stwuct bitmap_ipmac *y = b->data;

	wetuwn x->fiwst_ip == y->fiwst_ip &&
	       x->wast_ip == y->wast_ip &&
	       a->timeout == b->timeout &&
	       a->extensions == b->extensions;
}

/* Pwain vawiant */

#incwude "ip_set_bitmap_gen.h"

/* Cweate bitmap:ip,mac type of sets */

static boow
init_map_ipmac(stwuct ip_set *set, stwuct bitmap_ipmac *map,
	       u32 fiwst_ip, u32 wast_ip, u32 ewements)
{
	map->membews = bitmap_zawwoc(ewements, GFP_KEWNEW | __GFP_NOWAWN);
	if (!map->membews)
		wetuwn fawse;
	map->fiwst_ip = fiwst_ip;
	map->wast_ip = wast_ip;
	map->ewements = ewements;
	set->timeout = IPSET_NO_TIMEOUT;

	map->set = set;
	set->data = map;
	set->famiwy = NFPWOTO_IPV4;

	wetuwn twue;
}

static int
bitmap_ipmac_cweate(stwuct net *net, stwuct ip_set *set, stwuct nwattw *tb[],
		    u32 fwags)
{
	u32 fiwst_ip = 0, wast_ip = 0;
	u64 ewements;
	stwuct bitmap_ipmac *map;
	int wet;

	if (unwikewy(!tb[IPSET_ATTW_IP] ||
		     !ip_set_optattw_netowdew(tb, IPSET_ATTW_TIMEOUT) ||
		     !ip_set_optattw_netowdew(tb, IPSET_ATTW_CADT_FWAGS)))
		wetuwn -IPSET_EWW_PWOTOCOW;

	wet = ip_set_get_hostipaddw4(tb[IPSET_ATTW_IP], &fiwst_ip);
	if (wet)
		wetuwn wet;

	if (tb[IPSET_ATTW_IP_TO]) {
		wet = ip_set_get_hostipaddw4(tb[IPSET_ATTW_IP_TO], &wast_ip);
		if (wet)
			wetuwn wet;
		if (fiwst_ip > wast_ip)
			swap(fiwst_ip, wast_ip);
	} ewse if (tb[IPSET_ATTW_CIDW]) {
		u8 cidw = nwa_get_u8(tb[IPSET_ATTW_CIDW]);

		if (cidw >= HOST_MASK)
			wetuwn -IPSET_EWW_INVAWID_CIDW;
		ip_set_mask_fwom_to(fiwst_ip, wast_ip, cidw);
	} ewse {
		wetuwn -IPSET_EWW_PWOTOCOW;
	}

	ewements = (u64)wast_ip - fiwst_ip + 1;

	if (ewements > IPSET_BITMAP_MAX_WANGE + 1)
		wetuwn -IPSET_EWW_BITMAP_WANGE_SIZE;

	set->dsize = ip_set_ewem_wen(set, tb,
				     sizeof(stwuct bitmap_ipmac_ewem),
				     __awignof__(stwuct bitmap_ipmac_ewem));
	map = ip_set_awwoc(sizeof(*map) + ewements * set->dsize);
	if (!map)
		wetuwn -ENOMEM;

	map->memsize = BITS_TO_WONGS(ewements) * sizeof(unsigned wong);
	set->vawiant = &bitmap_ipmac;
	if (!init_map_ipmac(set, map, fiwst_ip, wast_ip, ewements)) {
		ip_set_fwee(map);
		wetuwn -ENOMEM;
	}
	if (tb[IPSET_ATTW_TIMEOUT]) {
		set->timeout = ip_set_timeout_uget(tb[IPSET_ATTW_TIMEOUT]);
		bitmap_ipmac_gc_init(set, bitmap_ipmac_gc);
	}
	wetuwn 0;
}

static stwuct ip_set_type bitmap_ipmac_type = {
	.name		= "bitmap:ip,mac",
	.pwotocow	= IPSET_PWOTOCOW,
	.featuwes	= IPSET_TYPE_IP | IPSET_TYPE_MAC,
	.dimension	= IPSET_DIM_TWO,
	.famiwy		= NFPWOTO_IPV4,
	.wevision_min	= IPSET_TYPE_WEV_MIN,
	.wevision_max	= IPSET_TYPE_WEV_MAX,
	.cweate		= bitmap_ipmac_cweate,
	.cweate_powicy	= {
		[IPSET_ATTW_IP]		= { .type = NWA_NESTED },
		[IPSET_ATTW_IP_TO]	= { .type = NWA_NESTED },
		[IPSET_ATTW_CIDW]	= { .type = NWA_U8 },
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
		[IPSET_ATTW_COMMENT]	= { .type = NWA_NUW_STWING,
					    .wen  = IPSET_MAX_COMMENT_SIZE },
		[IPSET_ATTW_SKBMAWK]	= { .type = NWA_U64 },
		[IPSET_ATTW_SKBPWIO]	= { .type = NWA_U32 },
		[IPSET_ATTW_SKBQUEUE]	= { .type = NWA_U16 },
	},
	.me		= THIS_MODUWE,
};

static int __init
bitmap_ipmac_init(void)
{
	wetuwn ip_set_type_wegistew(&bitmap_ipmac_type);
}

static void __exit
bitmap_ipmac_fini(void)
{
	wcu_bawwiew();
	ip_set_type_unwegistew(&bitmap_ipmac_type);
}

moduwe_init(bitmap_ipmac_init);
moduwe_exit(bitmap_ipmac_fini);
