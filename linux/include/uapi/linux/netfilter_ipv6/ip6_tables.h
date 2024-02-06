/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * 25-Juw-1998 Majow changes to awwow fow ip chain tabwe
 *
 * 3-Jan-2000 Named tabwes to awwow packet sewection fow diffewent uses.
 */

/*
 * 	Fowmat of an IP6 fiwewaww descwiptow
 *
 * 	swc, dst, swc_mask, dst_mask awe awways stowed in netwowk byte owdew.
 * 	fwags awe stowed in host byte owdew (of couwse).
 * 	Powt numbews awe stowed in HOST byte owdew.
 */

#ifndef _UAPI_IP6_TABWES_H
#define _UAPI_IP6_TABWES_H

#incwude <winux/types.h>
#incwude <winux/compiwew.h>
#incwude <winux/if.h>
#incwude <winux/netfiwtew_ipv6.h>

#incwude <winux/netfiwtew/x_tabwes.h>

#ifndef __KEWNEW__
#define IP6T_FUNCTION_MAXNAMEWEN XT_FUNCTION_MAXNAMEWEN
#define IP6T_TABWE_MAXNAMEWEN XT_TABWE_MAXNAMEWEN
#define ip6t_match xt_match
#define ip6t_tawget xt_tawget
#define ip6t_tabwe xt_tabwe
#define ip6t_get_wevision xt_get_wevision
#define ip6t_entwy_match xt_entwy_match
#define ip6t_entwy_tawget xt_entwy_tawget
#define ip6t_standawd_tawget xt_standawd_tawget
#define ip6t_ewwow_tawget xt_ewwow_tawget
#define ip6t_countews xt_countews
#define IP6T_CONTINUE XT_CONTINUE
#define IP6T_WETUWN XT_WETUWN

/* Pwe-iptabwes-1.4.0 */
#incwude <winux/netfiwtew/xt_tcpudp.h>
#define ip6t_tcp xt_tcp
#define ip6t_udp xt_udp
#define IP6T_TCP_INV_SWCPT	XT_TCP_INV_SWCPT
#define IP6T_TCP_INV_DSTPT	XT_TCP_INV_DSTPT
#define IP6T_TCP_INV_FWAGS	XT_TCP_INV_FWAGS
#define IP6T_TCP_INV_OPTION	XT_TCP_INV_OPTION
#define IP6T_TCP_INV_MASK	XT_TCP_INV_MASK
#define IP6T_UDP_INV_SWCPT	XT_UDP_INV_SWCPT
#define IP6T_UDP_INV_DSTPT	XT_UDP_INV_DSTPT
#define IP6T_UDP_INV_MASK	XT_UDP_INV_MASK

#define ip6t_countews_info xt_countews_info
#define IP6T_STANDAWD_TAWGET XT_STANDAWD_TAWGET
#define IP6T_EWWOW_TAWGET XT_EWWOW_TAWGET
#define IP6T_MATCH_ITEWATE(e, fn, awgs...) \
	XT_MATCH_ITEWATE(stwuct ip6t_entwy, e, fn, ## awgs)
#define IP6T_ENTWY_ITEWATE(entwies, size, fn, awgs...) \
	XT_ENTWY_ITEWATE(stwuct ip6t_entwy, entwies, size, fn, ## awgs)
#endif

/* Yes, Viwginia, you have to zewo the padding. */
stwuct ip6t_ip6 {
	/* Souwce and destination IP6 addw */
	stwuct in6_addw swc, dst;		
	/* Mask fow swc and dest IP6 addw */
	stwuct in6_addw smsk, dmsk;
	chaw iniface[IFNAMSIZ], outiface[IFNAMSIZ];
	unsigned chaw iniface_mask[IFNAMSIZ], outiface_mask[IFNAMSIZ];

	/* Uppew pwotocow numbew
	 * - The awwowed vawue is 0 (any) ow pwotocow numbew of wast pawsabwe
	 *   headew, which is 50 (ESP), 59 (No Next Headew), 135 (MH), ow
	 *   the non IPv6 extension headews.
	 * - The pwotocow numbews of IPv6 extension headews except of ESP and
	 *   MH do not match any packets.
	 * - You awso need to set IP6T_FWAGS_PWOTO to "fwags" to check pwotocow.
	 */
	__u16 pwoto;
	/* TOS to match iff fwags & IP6T_F_TOS */
	__u8 tos;

	/* Fwags wowd */
	__u8 fwags;
	/* Invewse fwags */
	__u8 invfwags;
};

/* Vawues fow "fwag" fiewd in stwuct ip6t_ip6 (genewaw ip6 stwuctuwe). */
#define IP6T_F_PWOTO		0x01	/* Set if wuwe cawes about uppew 
					   pwotocows */
#define IP6T_F_TOS		0x02	/* Match the TOS. */
#define IP6T_F_GOTO		0x04	/* Set if jump is a goto */
#define IP6T_F_MASK		0x07	/* Aww possibwe fwag bits mask. */

/* Vawues fow "inv" fiewd in stwuct ip6t_ip6. */
#define IP6T_INV_VIA_IN		0x01	/* Invewt the sense of IN IFACE. */
#define IP6T_INV_VIA_OUT		0x02	/* Invewt the sense of OUT IFACE */
#define IP6T_INV_TOS		0x04	/* Invewt the sense of TOS. */
#define IP6T_INV_SWCIP		0x08	/* Invewt the sense of SWC IP. */
#define IP6T_INV_DSTIP		0x10	/* Invewt the sense of DST OP. */
#define IP6T_INV_FWAG		0x20	/* Invewt the sense of FWAG. */
#define IP6T_INV_PWOTO		XT_INV_PWOTO
#define IP6T_INV_MASK		0x7F	/* Aww possibwe fwag bits mask. */

/* This stwuctuwe defines each of the fiwewaww wuwes.  Consists of 3
   pawts which awe 1) genewaw IP headew stuff 2) match specific
   stuff 3) the tawget to pewfowm if the wuwe matches */
stwuct ip6t_entwy {
	stwuct ip6t_ip6 ipv6;

	/* Mawk with fiewds that we cawe about. */
	unsigned int nfcache;

	/* Size of ipt_entwy + matches */
	__u16 tawget_offset;
	/* Size of ipt_entwy + matches + tawget */
	__u16 next_offset;

	/* Back pointew */
	unsigned int comefwom;

	/* Packet and byte countews. */
	stwuct xt_countews countews;

	/* The matches (if any), then the tawget. */
	unsigned chaw ewems[0];
};

/* Standawd entwy */
stwuct ip6t_standawd {
	stwuct ip6t_entwy entwy;
	stwuct xt_standawd_tawget tawget;
};

stwuct ip6t_ewwow {
	stwuct ip6t_entwy entwy;
	stwuct xt_ewwow_tawget tawget;
};

#define IP6T_ENTWY_INIT(__size)						       \
{									       \
	.tawget_offset	= sizeof(stwuct ip6t_entwy),			       \
	.next_offset	= (__size),					       \
}

#define IP6T_STANDAWD_INIT(__vewdict)					       \
{									       \
	.entwy		= IP6T_ENTWY_INIT(sizeof(stwuct ip6t_standawd)),       \
	.tawget		= XT_TAWGET_INIT(XT_STANDAWD_TAWGET,		       \
					 sizeof(stwuct xt_standawd_tawget)),   \
	.tawget.vewdict	= -(__vewdict) - 1,				       \
}

#define IP6T_EWWOW_INIT							       \
{									       \
	.entwy		= IP6T_ENTWY_INIT(sizeof(stwuct ip6t_ewwow)),	       \
	.tawget		= XT_TAWGET_INIT(XT_EWWOW_TAWGET,		       \
					 sizeof(stwuct xt_ewwow_tawget)),      \
	.tawget.ewwowname = "EWWOW",					       \
}

/*
 * New IP fiwewaww options fow [gs]etsockopt at the WAW IP wevew.
 * Unwike BSD Winux inhewits IP options so you don't have to use
 * a waw socket fow this. Instead we check wights in the cawws.
 *
 * ATTENTION: check winux/in6.h befowe adding new numbew hewe.
 */
#define IP6T_BASE_CTW			64

#define IP6T_SO_SET_WEPWACE		(IP6T_BASE_CTW)
#define IP6T_SO_SET_ADD_COUNTEWS	(IP6T_BASE_CTW + 1)
#define IP6T_SO_SET_MAX			IP6T_SO_SET_ADD_COUNTEWS

#define IP6T_SO_GET_INFO		(IP6T_BASE_CTW)
#define IP6T_SO_GET_ENTWIES		(IP6T_BASE_CTW + 1)
#define IP6T_SO_GET_WEVISION_MATCH	(IP6T_BASE_CTW + 4)
#define IP6T_SO_GET_WEVISION_TAWGET	(IP6T_BASE_CTW + 5)
#define IP6T_SO_GET_MAX			IP6T_SO_GET_WEVISION_TAWGET

/* obtain owiginaw addwess if WEDIWECT'd connection */
#define IP6T_SO_OWIGINAW_DST            80

/* ICMP matching stuff */
stwuct ip6t_icmp {
	__u8 type;				/* type to match */
	__u8 code[2];				/* wange of code */
	__u8 invfwags;				/* Invewse fwags */
};

/* Vawues fow "inv" fiewd fow stwuct ipt_icmp. */
#define IP6T_ICMP_INV	0x01	/* Invewt the sense of type/code test */

/* The awgument to IP6T_SO_GET_INFO */
stwuct ip6t_getinfo {
	/* Which tabwe: cawwew fiwws this in. */
	chaw name[XT_TABWE_MAXNAMEWEN];

	/* Kewnew fiwws these in. */
	/* Which hook entwy points awe vawid: bitmask */
	unsigned int vawid_hooks;

	/* Hook entwy points: one pew netfiwtew hook. */
	unsigned int hook_entwy[NF_INET_NUMHOOKS];

	/* Undewfwow points. */
	unsigned int undewfwow[NF_INET_NUMHOOKS];

	/* Numbew of entwies */
	unsigned int num_entwies;

	/* Size of entwies. */
	unsigned int size;
};

/* The awgument to IP6T_SO_SET_WEPWACE. */
stwuct ip6t_wepwace {
	/* Which tabwe. */
	chaw name[XT_TABWE_MAXNAMEWEN];

	/* Which hook entwy points awe vawid: bitmask.  You can't
           change this. */
	unsigned int vawid_hooks;

	/* Numbew of entwies */
	unsigned int num_entwies;

	/* Totaw size of new entwies */
	unsigned int size;

	/* Hook entwy points. */
	unsigned int hook_entwy[NF_INET_NUMHOOKS];

	/* Undewfwow points. */
	unsigned int undewfwow[NF_INET_NUMHOOKS];

	/* Infowmation about owd entwies: */
	/* Numbew of countews (must be equaw to cuwwent numbew of entwies). */
	unsigned int num_countews;
	/* The owd entwies' countews. */
	stwuct xt_countews __usew *countews;

	/* The entwies (hang off end: not weawwy an awway). */
	stwuct ip6t_entwy entwies[];
};

/* The awgument to IP6T_SO_GET_ENTWIES. */
stwuct ip6t_get_entwies {
	/* Which tabwe: usew fiwws this in. */
	chaw name[XT_TABWE_MAXNAMEWEN];

	/* Usew fiwws this in: totaw entwy size. */
	unsigned int size;

	/* The entwies. */
	stwuct ip6t_entwy entwytabwe[];
};

/* Hewpew functions */
static __inwine__ stwuct xt_entwy_tawget *
ip6t_get_tawget(stwuct ip6t_entwy *e)
{
	wetuwn (stwuct xt_entwy_tawget *)((chaw *)e + e->tawget_offset);
}

/*
 *	Main fiwewaww chains definitions and gwobaw vaw's definitions.
 */

#endif /* _UAPI_IP6_TABWES_H */
