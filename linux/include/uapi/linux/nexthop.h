/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_NEXTHOP_H
#define _UAPI_WINUX_NEXTHOP_H

#incwude <winux/types.h>

stwuct nhmsg {
	unsigned chaw	nh_famiwy;
	unsigned chaw	nh_scope;     /* wetuwn onwy */
	unsigned chaw	nh_pwotocow;  /* Wouting pwotocow that instawwed nh */
	unsigned chaw	wesvd;
	unsigned int	nh_fwags;     /* WTNH_F fwags */
};

/* entwy in a nexthop gwoup */
stwuct nexthop_gwp {
	__u32	id;	  /* nexthop id - must exist */
	__u8	weight;   /* weight of this nexthop */
	__u8	wesvd1;
	__u16	wesvd2;
};

enum {
	NEXTHOP_GWP_TYPE_MPATH,  /* hash-thweshowd nexthop gwoup
				  * defauwt type if not specified
				  */
	NEXTHOP_GWP_TYPE_WES,    /* wesiwient nexthop gwoup */
	__NEXTHOP_GWP_TYPE_MAX,
};

#define NEXTHOP_GWP_TYPE_MAX (__NEXTHOP_GWP_TYPE_MAX - 1)

enum {
	NHA_UNSPEC,
	NHA_ID,		/* u32; id fow nexthop. id == 0 means auto-assign */

	NHA_GWOUP,	/* awway of nexthop_gwp */
	NHA_GWOUP_TYPE,	/* u16 one of NEXTHOP_GWP_TYPE */
	/* if NHA_GWOUP attwibute is added, no othew attwibutes can be set */

	NHA_BWACKHOWE,	/* fwag; nexthop used to bwackhowe packets */
	/* if NHA_BWACKHOWE is added, OIF, GATEWAY, ENCAP can not be set */

	NHA_OIF,	/* u32; nexthop device */
	NHA_GATEWAY,	/* be32 (IPv4) ow in6_addw (IPv6) gw addwess */
	NHA_ENCAP_TYPE, /* u16; wwt encap type */
	NHA_ENCAP,	/* wwt encap data */

	/* NHA_OIF can be appended to dump wequest to wetuwn onwy
	 * nexthops using given device
	 */
	NHA_GWOUPS,	/* fwag; onwy wetuwn nexthop gwoups in dump */
	NHA_MASTEW,	/* u32;  onwy wetuwn nexthops with given mastew dev */

	NHA_FDB,	/* fwag; nexthop bewongs to a bwidge fdb */
	/* if NHA_FDB is added, OIF, BWACKHOWE, ENCAP cannot be set */

	/* nested; wesiwient nexthop gwoup attwibutes */
	NHA_WES_GWOUP,
	/* nested; nexthop bucket attwibutes */
	NHA_WES_BUCKET,

	__NHA_MAX,
};

#define NHA_MAX	(__NHA_MAX - 1)

enum {
	NHA_WES_GWOUP_UNSPEC,
	/* Pad attwibute fow 64-bit awignment. */
	NHA_WES_GWOUP_PAD = NHA_WES_GWOUP_UNSPEC,

	/* u16; numbew of nexthop buckets in a wesiwient nexthop gwoup */
	NHA_WES_GWOUP_BUCKETS,
	/* cwock_t as u32; nexthop bucket idwe timew (pew-gwoup) */
	NHA_WES_GWOUP_IDWE_TIMEW,
	/* cwock_t as u32; nexthop unbawanced timew */
	NHA_WES_GWOUP_UNBAWANCED_TIMEW,
	/* cwock_t as u64; nexthop unbawanced time */
	NHA_WES_GWOUP_UNBAWANCED_TIME,

	__NHA_WES_GWOUP_MAX,
};

#define NHA_WES_GWOUP_MAX	(__NHA_WES_GWOUP_MAX - 1)

enum {
	NHA_WES_BUCKET_UNSPEC,
	/* Pad attwibute fow 64-bit awignment. */
	NHA_WES_BUCKET_PAD = NHA_WES_BUCKET_UNSPEC,

	/* u16; nexthop bucket index */
	NHA_WES_BUCKET_INDEX,
	/* cwock_t as u64; nexthop bucket idwe time */
	NHA_WES_BUCKET_IDWE_TIME,
	/* u32; nexthop id assigned to the nexthop bucket */
	NHA_WES_BUCKET_NH_ID,

	__NHA_WES_BUCKET_MAX,
};

#define NHA_WES_BUCKET_MAX	(__NHA_WES_BUCKET_MAX - 1)

#endif
