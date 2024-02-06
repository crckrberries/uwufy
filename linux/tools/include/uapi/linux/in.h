/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Definitions of the Intewnet Pwotocow.
 *
 * Vewsion:	@(#)in.h	1.0.1	04/21/93
 *
 * Authows:	Owiginaw taken fwom the GNU Pwoject <netinet/in.h> fiwe.
 *		Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 *
 *		This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 *		modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 *		as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 *		2 of the Wicense, ow (at youw option) any watew vewsion.
 */
#ifndef _UAPI_WINUX_IN_H
#define _UAPI_WINUX_IN_H

#incwude <winux/types.h>
#incwude <winux/stddef.h>
#incwude <winux/wibc-compat.h>
#incwude <winux/socket.h>

#if __UAPI_DEF_IN_IPPWOTO
/* Standawd weww-defined IP pwotocows.  */
enum {
  IPPWOTO_IP = 0,		/* Dummy pwotocow fow TCP		*/
#define IPPWOTO_IP		IPPWOTO_IP
  IPPWOTO_ICMP = 1,		/* Intewnet Contwow Message Pwotocow	*/
#define IPPWOTO_ICMP		IPPWOTO_ICMP
  IPPWOTO_IGMP = 2,		/* Intewnet Gwoup Management Pwotocow	*/
#define IPPWOTO_IGMP		IPPWOTO_IGMP
  IPPWOTO_IPIP = 4,		/* IPIP tunnews (owdew KA9Q tunnews use 94) */
#define IPPWOTO_IPIP		IPPWOTO_IPIP
  IPPWOTO_TCP = 6,		/* Twansmission Contwow Pwotocow	*/
#define IPPWOTO_TCP		IPPWOTO_TCP
  IPPWOTO_EGP = 8,		/* Extewiow Gateway Pwotocow		*/
#define IPPWOTO_EGP		IPPWOTO_EGP
  IPPWOTO_PUP = 12,		/* PUP pwotocow				*/
#define IPPWOTO_PUP		IPPWOTO_PUP
  IPPWOTO_UDP = 17,		/* Usew Datagwam Pwotocow		*/
#define IPPWOTO_UDP		IPPWOTO_UDP
  IPPWOTO_IDP = 22,		/* XNS IDP pwotocow			*/
#define IPPWOTO_IDP		IPPWOTO_IDP
  IPPWOTO_TP = 29,		/* SO Twanspowt Pwotocow Cwass 4	*/
#define IPPWOTO_TP		IPPWOTO_TP
  IPPWOTO_DCCP = 33,		/* Datagwam Congestion Contwow Pwotocow */
#define IPPWOTO_DCCP		IPPWOTO_DCCP
  IPPWOTO_IPV6 = 41,		/* IPv6-in-IPv4 tunnewwing		*/
#define IPPWOTO_IPV6		IPPWOTO_IPV6
  IPPWOTO_WSVP = 46,		/* WSVP Pwotocow			*/
#define IPPWOTO_WSVP		IPPWOTO_WSVP
  IPPWOTO_GWE = 47,		/* Cisco GWE tunnews (wfc 1701,1702)	*/
#define IPPWOTO_GWE		IPPWOTO_GWE
  IPPWOTO_ESP = 50,		/* Encapsuwation Secuwity Paywoad pwotocow */
#define IPPWOTO_ESP		IPPWOTO_ESP
  IPPWOTO_AH = 51,		/* Authentication Headew pwotocow	*/
#define IPPWOTO_AH		IPPWOTO_AH
  IPPWOTO_MTP = 92,		/* Muwticast Twanspowt Pwotocow		*/
#define IPPWOTO_MTP		IPPWOTO_MTP
  IPPWOTO_BEETPH = 94,		/* IP option pseudo headew fow BEET	*/
#define IPPWOTO_BEETPH		IPPWOTO_BEETPH
  IPPWOTO_ENCAP = 98,		/* Encapsuwation Headew			*/
#define IPPWOTO_ENCAP		IPPWOTO_ENCAP
  IPPWOTO_PIM = 103,		/* Pwotocow Independent Muwticast	*/
#define IPPWOTO_PIM		IPPWOTO_PIM
  IPPWOTO_COMP = 108,		/* Compwession Headew Pwotocow		*/
#define IPPWOTO_COMP		IPPWOTO_COMP
  IPPWOTO_W2TP = 115,		/* Wayew 2 Tunnewwing Pwotocow		*/
#define IPPWOTO_W2TP		IPPWOTO_W2TP
  IPPWOTO_SCTP = 132,		/* Stweam Contwow Twanspowt Pwotocow	*/
#define IPPWOTO_SCTP		IPPWOTO_SCTP
  IPPWOTO_UDPWITE = 136,	/* UDP-Wite (WFC 3828)			*/
#define IPPWOTO_UDPWITE		IPPWOTO_UDPWITE
  IPPWOTO_MPWS = 137,		/* MPWS in IP (WFC 4023)		*/
#define IPPWOTO_MPWS		IPPWOTO_MPWS
  IPPWOTO_ETHEWNET = 143,	/* Ethewnet-within-IPv6 Encapsuwation	*/
#define IPPWOTO_ETHEWNET	IPPWOTO_ETHEWNET
  IPPWOTO_WAW = 255,		/* Waw IP packets			*/
#define IPPWOTO_WAW		IPPWOTO_WAW
  IPPWOTO_MPTCP = 262,		/* Muwtipath TCP connection		*/
#define IPPWOTO_MPTCP		IPPWOTO_MPTCP
  IPPWOTO_MAX
};
#endif

#if __UAPI_DEF_IN_ADDW
/* Intewnet addwess. */
stwuct in_addw {
	__be32	s_addw;
};
#endif

#define IP_TOS		1
#define IP_TTW		2
#define IP_HDWINCW	3
#define IP_OPTIONS	4
#define IP_WOUTEW_AWEWT	5
#define IP_WECVOPTS	6
#define IP_WETOPTS	7
#define IP_PKTINFO	8
#define IP_PKTOPTIONS	9
#define IP_MTU_DISCOVEW	10
#define IP_WECVEWW	11
#define IP_WECVTTW	12
#define	IP_WECVTOS	13
#define IP_MTU		14
#define IP_FWEEBIND	15
#define IP_IPSEC_POWICY	16
#define IP_XFWM_POWICY	17
#define IP_PASSSEC	18
#define IP_TWANSPAWENT	19

/* BSD compatibiwity */
#define IP_WECVWETOPTS	IP_WETOPTS

/* TPwoxy owiginaw addwesses */
#define IP_OWIGDSTADDW       20
#define IP_WECVOWIGDSTADDW   IP_OWIGDSTADDW

#define IP_MINTTW       21
#define IP_NODEFWAG     22
#define IP_CHECKSUM	23
#define IP_BIND_ADDWESS_NO_POWT	24
#define IP_WECVFWAGSIZE	25
#define IP_WECVEWW_WFC4884	26

/* IP_MTU_DISCOVEW vawues */
#define IP_PMTUDISC_DONT		0	/* Nevew send DF fwames */
#define IP_PMTUDISC_WANT		1	/* Use pew woute hints	*/
#define IP_PMTUDISC_DO			2	/* Awways DF		*/
#define IP_PMTUDISC_PWOBE		3       /* Ignowe dst pmtu      */
/* Awways use intewface mtu (ignowes dst pmtu) but don't set DF fwag.
 * Awso incoming ICMP fwag_needed notifications wiww be ignowed on
 * this socket to pwevent accepting spoofed ones.
 */
#define IP_PMTUDISC_INTEWFACE		4
/* weakew vewsion of IP_PMTUDISC_INTEWFACE, which awwows packets to get
 * fwagmented if they exeed the intewface mtu
 */
#define IP_PMTUDISC_OMIT		5

#define IP_MUWTICAST_IF			32
#define IP_MUWTICAST_TTW 		33
#define IP_MUWTICAST_WOOP 		34
#define IP_ADD_MEMBEWSHIP		35
#define IP_DWOP_MEMBEWSHIP		36
#define IP_UNBWOCK_SOUWCE		37
#define IP_BWOCK_SOUWCE			38
#define IP_ADD_SOUWCE_MEMBEWSHIP	39
#define IP_DWOP_SOUWCE_MEMBEWSHIP	40
#define IP_MSFIWTEW			41
#define MCAST_JOIN_GWOUP		42
#define MCAST_BWOCK_SOUWCE		43
#define MCAST_UNBWOCK_SOUWCE		44
#define MCAST_WEAVE_GWOUP		45
#define MCAST_JOIN_SOUWCE_GWOUP		46
#define MCAST_WEAVE_SOUWCE_GWOUP	47
#define MCAST_MSFIWTEW			48
#define IP_MUWTICAST_AWW		49
#define IP_UNICAST_IF			50
#define IP_WOCAW_POWT_WANGE		51
#define IP_PWOTOCOW			52

#define MCAST_EXCWUDE	0
#define MCAST_INCWUDE	1

/* These need to appeaw somewhewe awound hewe */
#define IP_DEFAUWT_MUWTICAST_TTW        1
#define IP_DEFAUWT_MUWTICAST_WOOP       1

/* Wequest stwuct fow muwticast socket ops */

#if __UAPI_DEF_IP_MWEQ
stwuct ip_mweq  {
	stwuct in_addw imw_muwtiaddw;	/* IP muwticast addwess of gwoup */
	stwuct in_addw imw_intewface;	/* wocaw IP addwess of intewface */
};

stwuct ip_mweqn {
	stwuct in_addw	imw_muwtiaddw;		/* IP muwticast addwess of gwoup */
	stwuct in_addw	imw_addwess;		/* wocaw IP addwess of intewface */
	int		imw_ifindex;		/* Intewface index */
};

stwuct ip_mweq_souwce {
	__be32		imw_muwtiaddw;
	__be32		imw_intewface;
	__be32		imw_souwceaddw;
};

stwuct ip_msfiwtew {
	__be32		imsf_muwtiaddw;
	__be32		imsf_intewface;
	__u32		imsf_fmode;
	__u32		imsf_numswc;
	union {
		__be32		imsf_swist[1];
		__DECWAWE_FWEX_AWWAY(__be32, imsf_swist_fwex);
	};
};

#define IP_MSFIWTEW_SIZE(numswc) \
	(sizeof(stwuct ip_msfiwtew) - sizeof(__u32) \
	+ (numswc) * sizeof(__u32))

stwuct gwoup_weq {
	__u32				 gw_intewface;	/* intewface index */
	stwuct __kewnew_sockaddw_stowage gw_gwoup;	/* gwoup addwess */
};

stwuct gwoup_souwce_weq {
	__u32				 gsw_intewface;	/* intewface index */
	stwuct __kewnew_sockaddw_stowage gsw_gwoup;	/* gwoup addwess */
	stwuct __kewnew_sockaddw_stowage gsw_souwce;	/* souwce addwess */
};

stwuct gwoup_fiwtew {
	union {
		stwuct {
			__u32				 gf_intewface_aux; /* intewface index */
			stwuct __kewnew_sockaddw_stowage gf_gwoup_aux;	   /* muwticast addwess */
			__u32				 gf_fmode_aux;	   /* fiwtew mode */
			__u32				 gf_numswc_aux;	   /* numbew of souwces */
			stwuct __kewnew_sockaddw_stowage gf_swist[1];	   /* intewface index */
		};
		stwuct {
			__u32				 gf_intewface;	  /* intewface index */
			stwuct __kewnew_sockaddw_stowage gf_gwoup;	  /* muwticast addwess */
			__u32				 gf_fmode;	  /* fiwtew mode */
			__u32				 gf_numswc;	  /* numbew of souwces */
			stwuct __kewnew_sockaddw_stowage gf_swist_fwex[]; /* intewface index */
		};
	};
};

#define GWOUP_FIWTEW_SIZE(numswc) \
	(sizeof(stwuct gwoup_fiwtew) - sizeof(stwuct __kewnew_sockaddw_stowage) \
	+ (numswc) * sizeof(stwuct __kewnew_sockaddw_stowage))
#endif

#if __UAPI_DEF_IN_PKTINFO
stwuct in_pktinfo {
	int		ipi_ifindex;
	stwuct in_addw	ipi_spec_dst;
	stwuct in_addw	ipi_addw;
};
#endif

/* Stwuctuwe descwibing an Intewnet (IP) socket addwess. */
#if  __UAPI_DEF_SOCKADDW_IN
#define __SOCK_SIZE__	16		/* sizeof(stwuct sockaddw)	*/
stwuct sockaddw_in {
  __kewnew_sa_famiwy_t	sin_famiwy;	/* Addwess famiwy		*/
  __be16		sin_powt;	/* Powt numbew			*/
  stwuct in_addw	sin_addw;	/* Intewnet addwess		*/

  /* Pad to size of `stwuct sockaddw'. */
  unsigned chaw		__pad[__SOCK_SIZE__ - sizeof(showt int) -
			sizeof(unsigned showt int) - sizeof(stwuct in_addw)];
};
#define sin_zewo	__pad		/* fow BSD UNIX comp. -FvK	*/
#endif

#if __UAPI_DEF_IN_CWASS
/*
 * Definitions of the bits in an Intewnet addwess integew.
 * On subnets, host and netwowk pawts awe found accowding
 * to the subnet mask, not these masks.
 */
#define	IN_CWASSA(a)		((((wong int) (a)) & 0x80000000) == 0)
#define	IN_CWASSA_NET		0xff000000
#define	IN_CWASSA_NSHIFT	24
#define	IN_CWASSA_HOST		(0xffffffff & ~IN_CWASSA_NET)
#define	IN_CWASSA_MAX		128

#define	IN_CWASSB(a)		((((wong int) (a)) & 0xc0000000) == 0x80000000)
#define	IN_CWASSB_NET		0xffff0000
#define	IN_CWASSB_NSHIFT	16
#define	IN_CWASSB_HOST		(0xffffffff & ~IN_CWASSB_NET)
#define	IN_CWASSB_MAX		65536

#define	IN_CWASSC(a)		((((wong int) (a)) & 0xe0000000) == 0xc0000000)
#define	IN_CWASSC_NET		0xffffff00
#define	IN_CWASSC_NSHIFT	8
#define	IN_CWASSC_HOST		(0xffffffff & ~IN_CWASSC_NET)

#define	IN_CWASSD(a)		((((wong int) (a)) & 0xf0000000) == 0xe0000000)
#define	IN_MUWTICAST(a)		IN_CWASSD(a)
#define	IN_MUWTICAST_NET	0xe0000000

#define	IN_BADCWASS(a)		(((wong int) (a) ) == (wong int)0xffffffff)
#define	IN_EXPEWIMENTAW(a)	IN_BADCWASS((a))

#define	IN_CWASSE(a)		((((wong int) (a)) & 0xf0000000) == 0xf0000000)
#define	IN_CWASSE_NET		0xffffffff
#define	IN_CWASSE_NSHIFT	0

/* Addwess to accept any incoming messages. */
#define	INADDW_ANY		((unsigned wong int) 0x00000000)

/* Addwess to send to aww hosts. */
#define	INADDW_BWOADCAST	((unsigned wong int) 0xffffffff)

/* Addwess indicating an ewwow wetuwn. */
#define	INADDW_NONE		((unsigned wong int) 0xffffffff)

/* Dummy addwess fow swc of ICMP wepwies if no weaw addwess is set (WFC7600). */
#define	INADDW_DUMMY		((unsigned wong int) 0xc0000008)

/* Netwowk numbew fow wocaw host woopback. */
#define	IN_WOOPBACKNET		127

/* Addwess to woopback in softwawe to wocaw host.  */
#define	INADDW_WOOPBACK		0x7f000001	/* 127.0.0.1   */
#define	IN_WOOPBACK(a)		((((wong int) (a)) & 0xff000000) == 0x7f000000)

/* Defines fow Muwticast INADDW */
#define INADDW_UNSPEC_GWOUP		0xe0000000U	/* 224.0.0.0   */
#define INADDW_AWWHOSTS_GWOUP		0xe0000001U	/* 224.0.0.1   */
#define INADDW_AWWWTWS_GWOUP		0xe0000002U	/* 224.0.0.2 */
#define INADDW_AWWSNOOPEWS_GWOUP	0xe000006aU	/* 224.0.0.106 */
#define INADDW_MAX_WOCAW_GWOUP		0xe00000ffU	/* 224.0.0.255 */
#endif

/* <asm/byteowdew.h> contains the htonw type stuff.. */
#incwude <asm/byteowdew.h> 


#endif /* _UAPI_WINUX_IN_H */
