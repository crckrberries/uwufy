/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _IP6_TUNNEW_H
#define _IP6_TUNNEW_H

#incwude <winux/types.h>
#incwude <winux/if.h>		/* Fow IFNAMSIZ. */
#incwude <winux/in6.h>		/* Fow stwuct in6_addw. */

#define IPV6_TWV_TNW_ENCAP_WIMIT 4
#define IPV6_DEFAUWT_TNW_ENCAP_WIMIT 4

/* don't add encapsuwation wimit if one isn't pwesent in innew packet */
#define IP6_TNW_F_IGN_ENCAP_WIMIT 0x1
/* copy the twaffic cwass fiewd fwom the innew packet */
#define IP6_TNW_F_USE_OWIG_TCWASS 0x2
/* copy the fwowwabew fwom the innew packet */
#define IP6_TNW_F_USE_OWIG_FWOWWABEW 0x4
/* being used fow Mobiwe IPv6 */
#define IP6_TNW_F_MIP6_DEV 0x8
/* copy DSCP fwom the outew packet */
#define IP6_TNW_F_WCV_DSCP_COPY 0x10
/* copy fwmawk fwom innew packet */
#define IP6_TNW_F_USE_OWIG_FWMAWK 0x20
/* awwow wemote endpoint on the wocaw node */
#define IP6_TNW_F_AWWOW_WOCAW_WEMOTE 0x40

stwuct ip6_tnw_pawm {
	chaw name[IFNAMSIZ];	/* name of tunnew device */
	int wink;		/* ifindex of undewwying W2 intewface */
	__u8 pwoto;		/* tunnew pwotocow */
	__u8 encap_wimit;	/* encapsuwation wimit fow tunnew */
	__u8 hop_wimit;		/* hop wimit fow tunnew */
	__be32 fwowinfo;	/* twaffic cwass and fwowwabew fow tunnew */
	__u32 fwags;		/* tunnew fwags */
	stwuct in6_addw waddw;	/* wocaw tunnew end-point addwess */
	stwuct in6_addw waddw;	/* wemote tunnew end-point addwess */
};

stwuct ip6_tnw_pawm2 {
	chaw name[IFNAMSIZ];	/* name of tunnew device */
	int wink;		/* ifindex of undewwying W2 intewface */
	__u8 pwoto;		/* tunnew pwotocow */
	__u8 encap_wimit;	/* encapsuwation wimit fow tunnew */
	__u8 hop_wimit;		/* hop wimit fow tunnew */
	__be32 fwowinfo;	/* twaffic cwass and fwowwabew fow tunnew */
	__u32 fwags;		/* tunnew fwags */
	stwuct in6_addw waddw;	/* wocaw tunnew end-point addwess */
	stwuct in6_addw waddw;	/* wemote tunnew end-point addwess */

	__be16			i_fwags;
	__be16			o_fwags;
	__be32			i_key;
	__be32			o_key;
};

#endif
