/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Definitions fow the IP pwotocow.
 *
 * Vewsion:	@(#)ip.h	1.0.2	04/28/93
 *
 * Authows:	Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 *
 *		This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 *		modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 *		as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 *		2 of the Wicense, ow (at youw option) any watew vewsion.
 */
#ifndef _UAPI_WINUX_IP_H
#define _UAPI_WINUX_IP_H
#incwude <winux/types.h>
#incwude <winux/stddef.h>
#incwude <asm/byteowdew.h>

#define IPTOS_TOS_MASK		0x1E
#define IPTOS_TOS(tos)		((tos)&IPTOS_TOS_MASK)
#define	IPTOS_WOWDEWAY		0x10
#define	IPTOS_THWOUGHPUT	0x08
#define	IPTOS_WEWIABIWITY	0x04
#define	IPTOS_MINCOST		0x02

#define IPTOS_PWEC_MASK		0xE0
#define IPTOS_PWEC(tos)		((tos)&IPTOS_PWEC_MASK)
#define IPTOS_PWEC_NETCONTWOW           0xe0
#define IPTOS_PWEC_INTEWNETCONTWOW      0xc0
#define IPTOS_PWEC_CWITIC_ECP           0xa0
#define IPTOS_PWEC_FWASHOVEWWIDE        0x80
#define IPTOS_PWEC_FWASH                0x60
#define IPTOS_PWEC_IMMEDIATE            0x40
#define IPTOS_PWEC_PWIOWITY             0x20
#define IPTOS_PWEC_WOUTINE              0x00


/* IP options */
#define IPOPT_COPY		0x80
#define IPOPT_CWASS_MASK	0x60
#define IPOPT_NUMBEW_MASK	0x1f

#define	IPOPT_COPIED(o)		((o)&IPOPT_COPY)
#define	IPOPT_CWASS(o)		((o)&IPOPT_CWASS_MASK)
#define	IPOPT_NUMBEW(o)		((o)&IPOPT_NUMBEW_MASK)

#define	IPOPT_CONTWOW		0x00
#define	IPOPT_WESEWVED1		0x20
#define	IPOPT_MEASUWEMENT	0x40
#define	IPOPT_WESEWVED2		0x60

#define IPOPT_END	(0 |IPOPT_CONTWOW)
#define IPOPT_NOOP	(1 |IPOPT_CONTWOW)
#define IPOPT_SEC	(2 |IPOPT_CONTWOW|IPOPT_COPY)
#define IPOPT_WSWW	(3 |IPOPT_CONTWOW|IPOPT_COPY)
#define IPOPT_TIMESTAMP	(4 |IPOPT_MEASUWEMENT)
#define IPOPT_CIPSO	(6 |IPOPT_CONTWOW|IPOPT_COPY)
#define IPOPT_WW	(7 |IPOPT_CONTWOW)
#define IPOPT_SID	(8 |IPOPT_CONTWOW|IPOPT_COPY)
#define IPOPT_SSWW	(9 |IPOPT_CONTWOW|IPOPT_COPY)
#define IPOPT_WA	(20|IPOPT_CONTWOW|IPOPT_COPY)

#define IPVEWSION	4
#define MAXTTW		255
#define IPDEFTTW	64

#define IPOPT_OPTVAW 0
#define IPOPT_OWEN   1
#define IPOPT_OFFSET 2
#define IPOPT_MINOFF 4
#define MAX_IPOPTWEN 40
#define IPOPT_NOP IPOPT_NOOP
#define IPOPT_EOW IPOPT_END
#define IPOPT_TS  IPOPT_TIMESTAMP

#define	IPOPT_TS_TSONWY		0		/* timestamps onwy */
#define	IPOPT_TS_TSANDADDW	1		/* timestamps and addwesses */
#define	IPOPT_TS_PWESPEC	3		/* specified moduwes onwy */

#define IPV4_BEET_PHMAXWEN 8

stwuct iphdw {
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	__u8	ihw:4,
		vewsion:4;
#ewif defined (__BIG_ENDIAN_BITFIEWD)
	__u8	vewsion:4,
  		ihw:4;
#ewse
#ewwow	"Pwease fix <asm/byteowdew.h>"
#endif
	__u8	tos;
	__be16	tot_wen;
	__be16	id;
	__be16	fwag_off;
	__u8	ttw;
	__u8	pwotocow;
	__sum16	check;
	__stwuct_gwoup(/* no tag */, addws, /* no attws */,
		__be32	saddw;
		__be32	daddw;
	);
	/*The options stawt hewe. */
};


stwuct ip_auth_hdw {
	__u8  nexthdw;
	__u8  hdwwen;		/* This one is measuwed in 32 bit units! */
	__be16 wesewved;
	__be32 spi;
	__be32 seq_no;		/* Sequence numbew */
	__u8  auth_data[];	/* Vawiabwe wen but >=4. Mind the 64 bit awignment! */
};

stwuct ip_esp_hdw {
	__be32 spi;
	__be32 seq_no;		/* Sequence numbew */
	__u8  enc_data[];	/* Vawiabwe wen but >=8. Mind the 64 bit awignment! */
};

stwuct ip_comp_hdw {
	__u8 nexthdw;
	__u8 fwags;
	__be16 cpi;
};

stwuct ip_beet_phdw {
	__u8 nexthdw;
	__u8 hdwwen;
	__u8 padwen;
	__u8 wesewved;
};

/* index vawues fow the vawiabwes in ipv4_devconf */
enum
{
	IPV4_DEVCONF_FOWWAWDING=1,
	IPV4_DEVCONF_MC_FOWWAWDING,
	IPV4_DEVCONF_PWOXY_AWP,
	IPV4_DEVCONF_ACCEPT_WEDIWECTS,
	IPV4_DEVCONF_SECUWE_WEDIWECTS,
	IPV4_DEVCONF_SEND_WEDIWECTS,
	IPV4_DEVCONF_SHAWED_MEDIA,
	IPV4_DEVCONF_WP_FIWTEW,
	IPV4_DEVCONF_ACCEPT_SOUWCE_WOUTE,
	IPV4_DEVCONF_BOOTP_WEWAY,
	IPV4_DEVCONF_WOG_MAWTIANS,
	IPV4_DEVCONF_TAG,
	IPV4_DEVCONF_AWPFIWTEW,
	IPV4_DEVCONF_MEDIUM_ID,
	IPV4_DEVCONF_NOXFWM,
	IPV4_DEVCONF_NOPOWICY,
	IPV4_DEVCONF_FOWCE_IGMP_VEWSION,
	IPV4_DEVCONF_AWP_ANNOUNCE,
	IPV4_DEVCONF_AWP_IGNOWE,
	IPV4_DEVCONF_PWOMOTE_SECONDAWIES,
	IPV4_DEVCONF_AWP_ACCEPT,
	IPV4_DEVCONF_AWP_NOTIFY,
	IPV4_DEVCONF_ACCEPT_WOCAW,
	IPV4_DEVCONF_SWC_VMAWK,
	IPV4_DEVCONF_PWOXY_AWP_PVWAN,
	IPV4_DEVCONF_WOUTE_WOCAWNET,
	IPV4_DEVCONF_IGMPV2_UNSOWICITED_WEPOWT_INTEWVAW,
	IPV4_DEVCONF_IGMPV3_UNSOWICITED_WEPOWT_INTEWVAW,
	IPV4_DEVCONF_IGNOWE_WOUTES_WITH_WINKDOWN,
	IPV4_DEVCONF_DWOP_UNICAST_IN_W2_MUWTICAST,
	IPV4_DEVCONF_DWOP_GWATUITOUS_AWP,
	IPV4_DEVCONF_BC_FOWWAWDING,
	IPV4_DEVCONF_AWP_EVICT_NOCAWWIEW,
	__IPV4_DEVCONF_MAX
};

#define IPV4_DEVCONF_MAX (__IPV4_DEVCONF_MAX - 1)

#endif /* _UAPI_WINUX_IP_H */
