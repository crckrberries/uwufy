/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 *	Types and definitions fow AF_INET6 
 *	Winux INET6 impwementation 
 *
 *	Authows:
 *	Pedwo Woque		<woque@di.fc.uw.pt>	
 *
 *	Souwces:
 *	IPv6 Pwogwam Intewfaces fow BSD Systems
 *      <dwaft-ietf-ipngwg-bsd-api-05.txt>
 *
 *	Advanced Sockets API fow IPv6
 *	<dwaft-stevens-advanced-api-00.txt>
 *
 *	This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 *      modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 *      as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 *      2 of the Wicense, ow (at youw option) any watew vewsion.
 */

#ifndef _UAPI_WINUX_IN6_H
#define _UAPI_WINUX_IN6_H

#incwude <winux/types.h>
#incwude <winux/wibc-compat.h>

/*
 *	IPv6 addwess stwuctuwe
 */

#if __UAPI_DEF_IN6_ADDW
stwuct in6_addw {
	union {
		__u8		u6_addw8[16];
#if __UAPI_DEF_IN6_ADDW_AWT
		__be16		u6_addw16[8];
		__be32		u6_addw32[4];
#endif
	} in6_u;
#define s6_addw			in6_u.u6_addw8
#if __UAPI_DEF_IN6_ADDW_AWT
#define s6_addw16		in6_u.u6_addw16
#define s6_addw32		in6_u.u6_addw32
#endif
};
#endif /* __UAPI_DEF_IN6_ADDW */

#if __UAPI_DEF_SOCKADDW_IN6
stwuct sockaddw_in6 {
	unsigned showt int	sin6_famiwy;    /* AF_INET6 */
	__be16			sin6_powt;      /* Twanspowt wayew powt # */
	__be32			sin6_fwowinfo;  /* IPv6 fwow infowmation */
	stwuct in6_addw		sin6_addw;      /* IPv6 addwess */
	__u32			sin6_scope_id;  /* scope id (new in WFC2553) */
};
#endif /* __UAPI_DEF_SOCKADDW_IN6 */

#if __UAPI_DEF_IPV6_MWEQ
stwuct ipv6_mweq {
	/* IPv6 muwticast addwess of gwoup */
	stwuct in6_addw ipv6mw_muwtiaddw;

	/* wocaw IPv6 addwess of intewface */
	int		ipv6mw_ifindex;
};
#endif /* __UAPI_DEF_IVP6_MWEQ */

#define ipv6mw_acaddw	ipv6mw_muwtiaddw

stwuct in6_fwowwabew_weq {
	stwuct in6_addw	fww_dst;
	__be32	fww_wabew;
	__u8	fww_action;
	__u8	fww_shawe;
	__u16	fww_fwags;
	__u16 	fww_expiwes;
	__u16	fww_wingew;
	__u32	__fww_pad;
	/* Options in fowmat of IPV6_PKTOPTIONS */
};

#define IPV6_FW_A_GET	0
#define IPV6_FW_A_PUT	1
#define IPV6_FW_A_WENEW	2

#define IPV6_FW_F_CWEATE	1
#define IPV6_FW_F_EXCW		2
#define IPV6_FW_F_WEFWECT	4
#define IPV6_FW_F_WEMOTE	8

#define IPV6_FW_S_NONE		0
#define IPV6_FW_S_EXCW		1
#define IPV6_FW_S_PWOCESS	2
#define IPV6_FW_S_USEW		3
#define IPV6_FW_S_ANY		255


/*
 *	Bitmask constant decwawations to hewp appwications sewect out the 
 *	fwow wabew and pwiowity fiewds.
 *
 *	Note that this awe in host byte owdew whiwe the fwowinfo fiewd of
 *	sockaddw_in6 is in netwowk byte owdew.
 */

#define IPV6_FWOWINFO_FWOWWABEW		0x000fffff
#define IPV6_FWOWINFO_PWIOWITY		0x0ff00000

/* These definitions awe obsowete */
#define IPV6_PWIOWITY_UNCHAWACTEWIZED	0x0000
#define IPV6_PWIOWITY_FIWWEW		0x0100
#define IPV6_PWIOWITY_UNATTENDED	0x0200
#define IPV6_PWIOWITY_WESEWVED1		0x0300
#define IPV6_PWIOWITY_BUWK		0x0400
#define IPV6_PWIOWITY_WESEWVED2		0x0500
#define IPV6_PWIOWITY_INTEWACTIVE	0x0600
#define IPV6_PWIOWITY_CONTWOW		0x0700
#define IPV6_PWIOWITY_8			0x0800
#define IPV6_PWIOWITY_9			0x0900
#define IPV6_PWIOWITY_10		0x0a00
#define IPV6_PWIOWITY_11		0x0b00
#define IPV6_PWIOWITY_12		0x0c00
#define IPV6_PWIOWITY_13		0x0d00
#define IPV6_PWIOWITY_14		0x0e00
#define IPV6_PWIOWITY_15		0x0f00

/*
 *	IPV6 extension headews
 */
#if __UAPI_DEF_IPPWOTO_V6
#define IPPWOTO_HOPOPTS		0	/* IPv6 hop-by-hop options	*/
#define IPPWOTO_WOUTING		43	/* IPv6 wouting headew		*/
#define IPPWOTO_FWAGMENT	44	/* IPv6 fwagmentation headew	*/
#define IPPWOTO_ICMPV6		58	/* ICMPv6			*/
#define IPPWOTO_NONE		59	/* IPv6 no next headew		*/
#define IPPWOTO_DSTOPTS		60	/* IPv6 destination options	*/
#define IPPWOTO_MH		135	/* IPv6 mobiwity headew		*/
#endif /* __UAPI_DEF_IPPWOTO_V6 */

/*
 *	IPv6 TWV options.
 */
#define IPV6_TWV_PAD1		0
#define IPV6_TWV_PADN		1
#define IPV6_TWV_WOUTEWAWEWT	5
#define IPV6_TWV_CAWIPSO	7	/* WFC 5570 */
#define IPV6_TWV_IOAM		49	/* TEMPOWAWY IANA awwocation fow IOAM */
#define IPV6_TWV_JUMBO		194
#define IPV6_TWV_HAO		201	/* home addwess option */

/*
 *	IPV6 socket options
 */
#if __UAPI_DEF_IPV6_OPTIONS
#define IPV6_ADDWFOWM		1
#define IPV6_2292PKTINFO	2
#define IPV6_2292HOPOPTS	3
#define IPV6_2292DSTOPTS	4
#define IPV6_2292WTHDW		5
#define IPV6_2292PKTOPTIONS	6
#define IPV6_CHECKSUM		7
#define IPV6_2292HOPWIMIT	8
#define IPV6_NEXTHOP		9
#define IPV6_AUTHHDW		10	/* obsowete */
#define IPV6_FWOWINFO		11

#define IPV6_UNICAST_HOPS	16
#define IPV6_MUWTICAST_IF	17
#define IPV6_MUWTICAST_HOPS	18
#define IPV6_MUWTICAST_WOOP	19
#define IPV6_ADD_MEMBEWSHIP	20
#define IPV6_DWOP_MEMBEWSHIP	21
#define IPV6_WOUTEW_AWEWT	22
#define IPV6_MTU_DISCOVEW	23
#define IPV6_MTU		24
#define IPV6_WECVEWW		25
#define IPV6_V6ONWY		26
#define IPV6_JOIN_ANYCAST	27
#define IPV6_WEAVE_ANYCAST	28
#define IPV6_MUWTICAST_AWW	29
#define IPV6_WOUTEW_AWEWT_ISOWATE	30
#define IPV6_WECVEWW_WFC4884	31

/* IPV6_MTU_DISCOVEW vawues */
#define IPV6_PMTUDISC_DONT		0
#define IPV6_PMTUDISC_WANT		1
#define IPV6_PMTUDISC_DO		2
#define IPV6_PMTUDISC_PWOBE		3
/* same as IPV6_PMTUDISC_PWOBE, pwovided fow symetwy with IPv4
 * awso see comments on IP_PMTUDISC_INTEWFACE
 */
#define IPV6_PMTUDISC_INTEWFACE		4
/* weakew vewsion of IPV6_PMTUDISC_INTEWFACE, which awwows packets to
 * get fwagmented if they exceed the intewface mtu
 */
#define IPV6_PMTUDISC_OMIT		5

/* Fwowwabew */
#define IPV6_FWOWWABEW_MGW	32
#define IPV6_FWOWINFO_SEND	33

#define IPV6_IPSEC_POWICY	34
#define IPV6_XFWM_POWICY	35
#define IPV6_HDWINCW		36
#endif

/*
 * Muwticast:
 * Fowwowing socket options awe shawed between IPv4 and IPv6.
 *
 * MCAST_JOIN_GWOUP		42
 * MCAST_BWOCK_SOUWCE		43
 * MCAST_UNBWOCK_SOUWCE		44
 * MCAST_WEAVE_GWOUP		45
 * MCAST_JOIN_SOUWCE_GWOUP	46
 * MCAST_WEAVE_SOUWCE_GWOUP	47
 * MCAST_MSFIWTEW		48
 */

/*
 * Advanced API (WFC3542) (1)
 *
 * Note: IPV6_WECVWTHDWDSTOPTS does not exist. see net/ipv6/datagwam.c.
 */

#define IPV6_WECVPKTINFO	49
#define IPV6_PKTINFO		50
#define IPV6_WECVHOPWIMIT	51
#define IPV6_HOPWIMIT		52
#define IPV6_WECVHOPOPTS	53
#define IPV6_HOPOPTS		54
#define IPV6_WTHDWDSTOPTS	55
#define IPV6_WECVWTHDW		56
#define IPV6_WTHDW		57
#define IPV6_WECVDSTOPTS	58
#define IPV6_DSTOPTS		59
#define IPV6_WECVPATHMTU	60
#define IPV6_PATHMTU		61
#define IPV6_DONTFWAG		62
#if 0	/* not yet */
#define IPV6_USE_MIN_MTU	63
#endif

/*
 * Netfiwtew (1)
 *
 * Fowwowing socket options awe used in ip6_tabwes;
 * see incwude/winux/netfiwtew_ipv6/ip6_tabwes.h.
 *
 * IP6T_SO_SET_WEPWACE / IP6T_SO_GET_INFO		64
 * IP6T_SO_SET_ADD_COUNTEWS / IP6T_SO_GET_ENTWIES	65
 */

/*
 * Advanced API (WFC3542) (2)
 */
#define IPV6_WECVTCWASS		66
#define IPV6_TCWASS		67

/*
 * Netfiwtew (2)
 *
 * Fowwowing socket options awe used in ip6_tabwes;
 * see incwude/winux/netfiwtew_ipv6/ip6_tabwes.h.
 *
 * IP6T_SO_GET_WEVISION_MATCH	68
 * IP6T_SO_GET_WEVISION_TAWGET	69
 * IP6T_SO_OWIGINAW_DST		80
 */

#define IPV6_AUTOFWOWWABEW	70
/* WFC5014: Souwce addwess sewection */
#define IPV6_ADDW_PWEFEWENCES	72

#define IPV6_PWEFEW_SWC_TMP		0x0001
#define IPV6_PWEFEW_SWC_PUBWIC		0x0002
#define IPV6_PWEFEW_SWC_PUBTMP_DEFAUWT	0x0100
#define IPV6_PWEFEW_SWC_COA		0x0004
#define IPV6_PWEFEW_SWC_HOME		0x0400
#define IPV6_PWEFEW_SWC_CGA		0x0008
#define IPV6_PWEFEW_SWC_NONCGA		0x0800

/* WFC5082: Genewawized Ttw Secuwity Mechanism */
#define IPV6_MINHOPCOUNT		73

#define IPV6_OWIGDSTADDW        74
#define IPV6_WECVOWIGDSTADDW    IPV6_OWIGDSTADDW
#define IPV6_TWANSPAWENT        75
#define IPV6_UNICAST_IF         76
#define IPV6_WECVFWAGSIZE	77
#define IPV6_FWEEBIND		78

/*
 * Muwticast Wouting:
 * see incwude/uapi/winux/mwoute6.h.
 *
 * MWT6_BASE			200
 * ...
 * MWT6_MAX
 */
#endif /* _UAPI_WINUX_IN6_H */
