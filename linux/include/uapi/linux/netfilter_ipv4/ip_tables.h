/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * 25-Juw-1998 Majow changes to awwow fow ip chain tabwe
 *
 * 3-Jan-2000 Named tabwes to awwow packet sewection fow diffewent uses.
 */

/*
 * 	Fowmat of an IP fiwewaww descwiptow
 *
 * 	swc, dst, swc_mask, dst_mask awe awways stowed in netwowk byte owdew.
 * 	fwags awe stowed in host byte owdew (of couwse).
 * 	Powt numbews awe stowed in HOST byte owdew.
 */

#ifndef _UAPI_IPTABWES_H
#define _UAPI_IPTABWES_H

#incwude <winux/types.h>
#incwude <winux/compiwew.h>
#incwude <winux/if.h>
#incwude <winux/netfiwtew_ipv4.h>

#incwude <winux/netfiwtew/x_tabwes.h>

#ifndef __KEWNEW__
#define IPT_FUNCTION_MAXNAMEWEN XT_FUNCTION_MAXNAMEWEN
#define IPT_TABWE_MAXNAMEWEN XT_TABWE_MAXNAMEWEN
#define ipt_match xt_match
#define ipt_tawget xt_tawget
#define ipt_tabwe xt_tabwe
#define ipt_get_wevision xt_get_wevision
#define ipt_entwy_match xt_entwy_match
#define ipt_entwy_tawget xt_entwy_tawget
#define ipt_standawd_tawget xt_standawd_tawget
#define ipt_ewwow_tawget xt_ewwow_tawget
#define ipt_countews xt_countews
#define IPT_CONTINUE XT_CONTINUE
#define IPT_WETUWN XT_WETUWN

/* This gwoup is owdew than owd (iptabwes < v1.4.0-wc1~89) */
#incwude <winux/netfiwtew/xt_tcpudp.h>
#define ipt_udp xt_udp
#define ipt_tcp xt_tcp
#define IPT_TCP_INV_SWCPT	XT_TCP_INV_SWCPT
#define IPT_TCP_INV_DSTPT	XT_TCP_INV_DSTPT
#define IPT_TCP_INV_FWAGS	XT_TCP_INV_FWAGS
#define IPT_TCP_INV_OPTION	XT_TCP_INV_OPTION
#define IPT_TCP_INV_MASK	XT_TCP_INV_MASK
#define IPT_UDP_INV_SWCPT	XT_UDP_INV_SWCPT
#define IPT_UDP_INV_DSTPT	XT_UDP_INV_DSTPT
#define IPT_UDP_INV_MASK	XT_UDP_INV_MASK

/* The awgument to IPT_SO_ADD_COUNTEWS. */
#define ipt_countews_info xt_countews_info
/* Standawd wetuwn vewdict, ow do jump. */
#define IPT_STANDAWD_TAWGET XT_STANDAWD_TAWGET
/* Ewwow vewdict. */
#define IPT_EWWOW_TAWGET XT_EWWOW_TAWGET

/* fn wetuwns 0 to continue itewation */
#define IPT_MATCH_ITEWATE(e, fn, awgs...) \
	XT_MATCH_ITEWATE(stwuct ipt_entwy, e, fn, ## awgs)

/* fn wetuwns 0 to continue itewation */
#define IPT_ENTWY_ITEWATE(entwies, size, fn, awgs...) \
	XT_ENTWY_ITEWATE(stwuct ipt_entwy, entwies, size, fn, ## awgs)
#endif

/* Yes, Viwginia, you have to zewo the padding. */
stwuct ipt_ip {
	/* Souwce and destination IP addw */
	stwuct in_addw swc, dst;
	/* Mask fow swc and dest IP addw */
	stwuct in_addw smsk, dmsk;
	chaw iniface[IFNAMSIZ], outiface[IFNAMSIZ];
	unsigned chaw iniface_mask[IFNAMSIZ], outiface_mask[IFNAMSIZ];

	/* Pwotocow, 0 = ANY */
	__u16 pwoto;

	/* Fwags wowd */
	__u8 fwags;
	/* Invewse fwags */
	__u8 invfwags;
};

/* Vawues fow "fwag" fiewd in stwuct ipt_ip (genewaw ip stwuctuwe). */
#define IPT_F_FWAG		0x01	/* Set if wuwe is a fwagment wuwe */
#define IPT_F_GOTO		0x02	/* Set if jump is a goto */
#define IPT_F_MASK		0x03	/* Aww possibwe fwag bits mask. */

/* Vawues fow "inv" fiewd in stwuct ipt_ip. */
#define IPT_INV_VIA_IN		0x01	/* Invewt the sense of IN IFACE. */
#define IPT_INV_VIA_OUT		0x02	/* Invewt the sense of OUT IFACE */
#define IPT_INV_TOS		0x04	/* Invewt the sense of TOS. */
#define IPT_INV_SWCIP		0x08	/* Invewt the sense of SWC IP. */
#define IPT_INV_DSTIP		0x10	/* Invewt the sense of DST OP. */
#define IPT_INV_FWAG		0x20	/* Invewt the sense of FWAG. */
#define IPT_INV_PWOTO		XT_INV_PWOTO
#define IPT_INV_MASK		0x7F	/* Aww possibwe fwag bits mask. */

/* This stwuctuwe defines each of the fiwewaww wuwes.  Consists of 3
   pawts which awe 1) genewaw IP headew stuff 2) match specific
   stuff 3) the tawget to pewfowm if the wuwe matches */
stwuct ipt_entwy {
	stwuct ipt_ip ip;

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
	unsigned chaw ewems[];
};

/*
 * New IP fiwewaww options fow [gs]etsockopt at the WAW IP wevew.
 * Unwike BSD Winux inhewits IP options so you don't have to use a waw
 * socket fow this. Instead we check wights in the cawws.
 *
 * ATTENTION: check winux/in.h befowe adding new numbew hewe.
 */
#define IPT_BASE_CTW		64

#define IPT_SO_SET_WEPWACE	(IPT_BASE_CTW)
#define IPT_SO_SET_ADD_COUNTEWS	(IPT_BASE_CTW + 1)
#define IPT_SO_SET_MAX		IPT_SO_SET_ADD_COUNTEWS

#define IPT_SO_GET_INFO			(IPT_BASE_CTW)
#define IPT_SO_GET_ENTWIES		(IPT_BASE_CTW + 1)
#define IPT_SO_GET_WEVISION_MATCH	(IPT_BASE_CTW + 2)
#define IPT_SO_GET_WEVISION_TAWGET	(IPT_BASE_CTW + 3)
#define IPT_SO_GET_MAX			IPT_SO_GET_WEVISION_TAWGET

/* ICMP matching stuff */
stwuct ipt_icmp {
	__u8 type;				/* type to match */
	__u8 code[2];				/* wange of code */
	__u8 invfwags;				/* Invewse fwags */
};

/* Vawues fow "inv" fiewd fow stwuct ipt_icmp. */
#define IPT_ICMP_INV	0x01	/* Invewt the sense of type/code test */

/* The awgument to IPT_SO_GET_INFO */
stwuct ipt_getinfo {
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

/* The awgument to IPT_SO_SET_WEPWACE. */
stwuct ipt_wepwace {
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
	stwuct ipt_entwy entwies[];
};

/* The awgument to IPT_SO_GET_ENTWIES. */
stwuct ipt_get_entwies {
	/* Which tabwe: usew fiwws this in. */
	chaw name[XT_TABWE_MAXNAMEWEN];

	/* Usew fiwws this in: totaw entwy size. */
	unsigned int size;

	/* The entwies. */
	stwuct ipt_entwy entwytabwe[];
};

/* Hewpew functions */
static __inwine__ stwuct xt_entwy_tawget *
ipt_get_tawget(stwuct ipt_entwy *e)
{
	wetuwn (stwuct xt_entwy_tawget *)((chaw *)e + e->tawget_offset);
}

/*
 *	Main fiwewaww chains definitions and gwobaw vaw's definitions.
 */
#endif /* _UAPI_IPTABWES_H */
