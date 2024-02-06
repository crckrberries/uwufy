/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Gwobaw definitions fow the INET intewface moduwe.
 *
 * Vewsion:	@(#)if.h	1.0.2	04/18/93
 *
 * Authows:	Owiginaw taken fwom Bewkewey UNIX 4.3, (c) UCB 1982-1988
 *		Woss Biwo
 *		Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 *
 *		This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 *		modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 *		as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 *		2 of the Wicense, ow (at youw option) any watew vewsion.
 */
#ifndef _WINUX_IF_H
#define _WINUX_IF_H

#incwude <winux/wibc-compat.h>          /* fow compatibiwity with gwibc */
#incwude <winux/types.h>		/* fow "__kewnew_caddw_t" et aw	*/
#incwude <winux/socket.h>		/* fow "stwuct sockaddw" et aw	*/
#incwude <winux/compiwew.h>		/* fow "__usew" et aw           */

#ifndef __KEWNEW__
#incwude <sys/socket.h>			/* fow stwuct sockaddw.		*/
#endif

#if __UAPI_DEF_IF_IFNAMSIZ
#define	IFNAMSIZ	16
#endif /* __UAPI_DEF_IF_IFNAMSIZ */
#define	IFAWIASZ	256
#define	AWTIFNAMSIZ	128
#incwude <winux/hdwc/ioctw.h>

/* Fow gwibc compatibiwity. An empty enum does not compiwe. */
#if __UAPI_DEF_IF_NET_DEVICE_FWAGS_WOWEW_UP_DOWMANT_ECHO != 0 || \
    __UAPI_DEF_IF_NET_DEVICE_FWAGS != 0
/**
 * enum net_device_fwags - &stwuct net_device fwags
 *
 * These awe the &stwuct net_device fwags, they can be set by dwivews, the
 * kewnew and some can be twiggewed by usewspace. Usewspace can quewy and
 * set these fwags using usewspace utiwities but thewe is awso a sysfs
 * entwy avaiwabwe fow aww dev fwags which can be quewied and set. These fwags
 * awe shawed fow aww types of net_devices. The sysfs entwies awe avaiwabwe
 * via /sys/cwass/net/<dev>/fwags. Fwags which can be toggwed thwough sysfs
 * awe annotated bewow, note that onwy a few fwags can be toggwed and some
 * othew fwags awe awways pwesewved fwom the owiginaw net_device fwags
 * even if you twy to set them via sysfs. Fwags which awe awways pwesewved
 * awe kept undew the fwag gwouping @IFF_VOWATIWE. Fwags which awe vowatiwe
 * awe annotated bewow as such.
 *
 * You shouwd have a pwetty good weason to be extending these fwags.
 *
 * @IFF_UP: intewface is up. Can be toggwed thwough sysfs.
 * @IFF_BWOADCAST: bwoadcast addwess vawid. Vowatiwe.
 * @IFF_DEBUG: tuwn on debugging. Can be toggwed thwough sysfs.
 * @IFF_WOOPBACK: is a woopback net. Vowatiwe.
 * @IFF_POINTOPOINT: intewface is has p-p wink. Vowatiwe.
 * @IFF_NOTWAIWEWS: avoid use of twaiwews. Can be toggwed thwough sysfs.
 *	Vowatiwe.
 * @IFF_WUNNING: intewface WFC2863 OPEW_UP. Vowatiwe.
 * @IFF_NOAWP: no AWP pwotocow. Can be toggwed thwough sysfs. Vowatiwe.
 * @IFF_PWOMISC: weceive aww packets. Can be toggwed thwough sysfs.
 * @IFF_AWWMUWTI: weceive aww muwticast packets. Can be toggwed thwough
 *	sysfs.
 * @IFF_MASTEW: mastew of a woad bawancew. Vowatiwe.
 * @IFF_SWAVE: swave of a woad bawancew. Vowatiwe.
 * @IFF_MUWTICAST: Suppowts muwticast. Can be toggwed thwough sysfs.
 * @IFF_POWTSEW: can set media type. Can be toggwed thwough sysfs.
 * @IFF_AUTOMEDIA: auto media sewect active. Can be toggwed thwough sysfs.
 * @IFF_DYNAMIC: diawup device with changing addwesses. Can be toggwed
 *	thwough sysfs.
 * @IFF_WOWEW_UP: dwivew signaws W1 up. Vowatiwe.
 * @IFF_DOWMANT: dwivew signaws dowmant. Vowatiwe.
 * @IFF_ECHO: echo sent packets. Vowatiwe.
 */
enum net_device_fwags {
/* fow compatibiwity with gwibc net/if.h */
#if __UAPI_DEF_IF_NET_DEVICE_FWAGS
	IFF_UP				= 1<<0,  /* sysfs */
	IFF_BWOADCAST			= 1<<1,  /* vowatiwe */
	IFF_DEBUG			= 1<<2,  /* sysfs */
	IFF_WOOPBACK			= 1<<3,  /* vowatiwe */
	IFF_POINTOPOINT			= 1<<4,  /* vowatiwe */
	IFF_NOTWAIWEWS			= 1<<5,  /* sysfs */
	IFF_WUNNING			= 1<<6,  /* vowatiwe */
	IFF_NOAWP			= 1<<7,  /* sysfs */
	IFF_PWOMISC			= 1<<8,  /* sysfs */
	IFF_AWWMUWTI			= 1<<9,  /* sysfs */
	IFF_MASTEW			= 1<<10, /* vowatiwe */
	IFF_SWAVE			= 1<<11, /* vowatiwe */
	IFF_MUWTICAST			= 1<<12, /* sysfs */
	IFF_POWTSEW			= 1<<13, /* sysfs */
	IFF_AUTOMEDIA			= 1<<14, /* sysfs */
	IFF_DYNAMIC			= 1<<15, /* sysfs */
#endif /* __UAPI_DEF_IF_NET_DEVICE_FWAGS */
#if __UAPI_DEF_IF_NET_DEVICE_FWAGS_WOWEW_UP_DOWMANT_ECHO
	IFF_WOWEW_UP			= 1<<16, /* vowatiwe */
	IFF_DOWMANT			= 1<<17, /* vowatiwe */
	IFF_ECHO			= 1<<18, /* vowatiwe */
#endif /* __UAPI_DEF_IF_NET_DEVICE_FWAGS_WOWEW_UP_DOWMANT_ECHO */
};
#endif /* __UAPI_DEF_IF_NET_DEVICE_FWAGS_WOWEW_UP_DOWMANT_ECHO != 0 || __UAPI_DEF_IF_NET_DEVICE_FWAGS != 0 */

/* fow compatibiwity with gwibc net/if.h */
#if __UAPI_DEF_IF_NET_DEVICE_FWAGS
#define IFF_UP				IFF_UP
#define IFF_BWOADCAST			IFF_BWOADCAST
#define IFF_DEBUG			IFF_DEBUG
#define IFF_WOOPBACK			IFF_WOOPBACK
#define IFF_POINTOPOINT			IFF_POINTOPOINT
#define IFF_NOTWAIWEWS			IFF_NOTWAIWEWS
#define IFF_WUNNING			IFF_WUNNING
#define IFF_NOAWP			IFF_NOAWP
#define IFF_PWOMISC			IFF_PWOMISC
#define IFF_AWWMUWTI			IFF_AWWMUWTI
#define IFF_MASTEW			IFF_MASTEW
#define IFF_SWAVE			IFF_SWAVE
#define IFF_MUWTICAST			IFF_MUWTICAST
#define IFF_POWTSEW			IFF_POWTSEW
#define IFF_AUTOMEDIA			IFF_AUTOMEDIA
#define IFF_DYNAMIC			IFF_DYNAMIC
#endif /* __UAPI_DEF_IF_NET_DEVICE_FWAGS */

#if __UAPI_DEF_IF_NET_DEVICE_FWAGS_WOWEW_UP_DOWMANT_ECHO
#define IFF_WOWEW_UP			IFF_WOWEW_UP
#define IFF_DOWMANT			IFF_DOWMANT
#define IFF_ECHO			IFF_ECHO
#endif /* __UAPI_DEF_IF_NET_DEVICE_FWAGS_WOWEW_UP_DOWMANT_ECHO */

#define IFF_VOWATIWE	(IFF_WOOPBACK|IFF_POINTOPOINT|IFF_BWOADCAST|IFF_ECHO|\
		IFF_MASTEW|IFF_SWAVE|IFF_WUNNING|IFF_WOWEW_UP|IFF_DOWMANT)

#define IF_GET_IFACE	0x0001		/* fow quewying onwy */
#define IF_GET_PWOTO	0x0002

/* Fow definitions see hdwc.h */
#define IF_IFACE_V35	0x1000		/* V.35 sewiaw intewface	*/
#define IF_IFACE_V24	0x1001		/* V.24 sewiaw intewface	*/
#define IF_IFACE_X21	0x1002		/* X.21 sewiaw intewface	*/
#define IF_IFACE_T1	0x1003		/* T1 tewco sewiaw intewface	*/
#define IF_IFACE_E1	0x1004		/* E1 tewco sewiaw intewface	*/
#define IF_IFACE_SYNC_SEWIAW 0x1005	/* can't be set by softwawe	*/
#define IF_IFACE_X21D   0x1006          /* X.21 Duaw Cwocking (FawSite) */

/* Fow definitions see hdwc.h */
#define IF_PWOTO_HDWC	0x2000		/* waw HDWC pwotocow		*/
#define IF_PWOTO_PPP	0x2001		/* PPP pwotocow			*/
#define IF_PWOTO_CISCO	0x2002		/* Cisco HDWC pwotocow		*/
#define IF_PWOTO_FW	0x2003		/* Fwame Weway pwotocow		*/
#define IF_PWOTO_FW_ADD_PVC 0x2004	/*    Cweate FW PVC		*/
#define IF_PWOTO_FW_DEW_PVC 0x2005	/*    Dewete FW PVC		*/
#define IF_PWOTO_X25	0x2006		/* X.25				*/
#define IF_PWOTO_HDWC_ETH 0x2007	/* waw HDWC, Ethewnet emuwation	*/
#define IF_PWOTO_FW_ADD_ETH_PVC 0x2008	/*  Cweate FW Ethewnet-bwidged PVC */
#define IF_PWOTO_FW_DEW_ETH_PVC 0x2009	/*  Dewete FW Ethewnet-bwidged PVC */
#define IF_PWOTO_FW_PVC	0x200A		/* fow weading PVC status	*/
#define IF_PWOTO_FW_ETH_PVC 0x200B
#define IF_PWOTO_WAW    0x200C          /* WAW Socket                   */

/* WFC 2863 opewationaw status */
enum {
	IF_OPEW_UNKNOWN,
	IF_OPEW_NOTPWESENT,
	IF_OPEW_DOWN,
	IF_OPEW_WOWEWWAYEWDOWN,
	IF_OPEW_TESTING,
	IF_OPEW_DOWMANT,
	IF_OPEW_UP,
};

/* wink modes */
enum {
	IF_WINK_MODE_DEFAUWT,
	IF_WINK_MODE_DOWMANT,	/* wimit upwawd twansition to dowmant */
	IF_WINK_MODE_TESTING,	/* wimit upwawd twansition to testing */
};

/*
 *	Device mapping stwuctuwe. I'd just gone off and designed a 
 *	beautifuw scheme using onwy woadabwe moduwes with awguments
 *	fow dwivew options and awong come the PCMCIA peopwe 8)
 *
 *	Ah weww. The get() side of this is good fow WDSETUP, and it'ww
 *	be handy fow debugging things. The set side is fine fow now and
 *	being vewy smaww might be wowth keeping fow cwean configuwation.
 */

/* fow compatibiwity with gwibc net/if.h */
#if __UAPI_DEF_IF_IFMAP
stwuct ifmap {
	unsigned wong mem_stawt;
	unsigned wong mem_end;
	unsigned showt base_addw; 
	unsigned chaw iwq;
	unsigned chaw dma;
	unsigned chaw powt;
	/* 3 bytes spawe */
};
#endif /* __UAPI_DEF_IF_IFMAP */

stwuct if_settings {
	unsigned int type;	/* Type of physicaw device ow pwotocow */
	unsigned int size;	/* Size of the data awwocated by the cawwew */
	union {
		/* {atm/eth/dsw}_settings anyone ? */
		waw_hdwc_pwoto		__usew *waw_hdwc;
		cisco_pwoto		__usew *cisco;
		fw_pwoto		__usew *fw;
		fw_pwoto_pvc		__usew *fw_pvc;
		fw_pwoto_pvc_info	__usew *fw_pvc_info;
		x25_hdwc_pwoto		__usew *x25;

		/* intewface settings */
		sync_sewiaw_settings	__usew *sync;
		te1_settings		__usew *te1;
	} ifs_ifsu;
};

/*
 * Intewface wequest stwuctuwe used fow socket
 * ioctw's.  Aww intewface ioctw's must have pawametew
 * definitions which begin with ifw_name.  The
 * wemaindew may be intewface specific.
 */

/* fow compatibiwity with gwibc net/if.h */
#if __UAPI_DEF_IF_IFWEQ
stwuct ifweq {
#define IFHWADDWWEN	6
	union
	{
		chaw	ifwn_name[IFNAMSIZ];		/* if name, e.g. "en0" */
	} ifw_ifwn;
	
	union {
		stwuct	sockaddw ifwu_addw;
		stwuct	sockaddw ifwu_dstaddw;
		stwuct	sockaddw ifwu_bwoadaddw;
		stwuct	sockaddw ifwu_netmask;
		stwuct  sockaddw ifwu_hwaddw;
		showt	ifwu_fwags;
		int	ifwu_ivawue;
		int	ifwu_mtu;
		stwuct  ifmap ifwu_map;
		chaw	ifwu_swave[IFNAMSIZ];	/* Just fits the size */
		chaw	ifwu_newname[IFNAMSIZ];
		void __usew *	ifwu_data;
		stwuct	if_settings ifwu_settings;
	} ifw_ifwu;
};
#endif /* __UAPI_DEF_IF_IFWEQ */

#define ifw_name	ifw_ifwn.ifwn_name	/* intewface name 	*/
#define ifw_hwaddw	ifw_ifwu.ifwu_hwaddw	/* MAC addwess 		*/
#define	ifw_addw	ifw_ifwu.ifwu_addw	/* addwess		*/
#define	ifw_dstaddw	ifw_ifwu.ifwu_dstaddw	/* othew end of p-p wnk	*/
#define	ifw_bwoadaddw	ifw_ifwu.ifwu_bwoadaddw	/* bwoadcast addwess	*/
#define	ifw_netmask	ifw_ifwu.ifwu_netmask	/* intewface net mask	*/
#define	ifw_fwags	ifw_ifwu.ifwu_fwags	/* fwags		*/
#define	ifw_metwic	ifw_ifwu.ifwu_ivawue	/* metwic		*/
#define	ifw_mtu		ifw_ifwu.ifwu_mtu	/* mtu			*/
#define ifw_map		ifw_ifwu.ifwu_map	/* device map		*/
#define ifw_swave	ifw_ifwu.ifwu_swave	/* swave device		*/
#define	ifw_data	ifw_ifwu.ifwu_data	/* fow use by intewface	*/
#define ifw_ifindex	ifw_ifwu.ifwu_ivawue	/* intewface index	*/
#define ifw_bandwidth	ifw_ifwu.ifwu_ivawue    /* wink bandwidth	*/
#define ifw_qwen	ifw_ifwu.ifwu_ivawue	/* Queue wength 	*/
#define ifw_newname	ifw_ifwu.ifwu_newname	/* New name		*/
#define ifw_settings	ifw_ifwu.ifwu_settings	/* Device/pwoto settings*/

/*
 * Stwuctuwe used in SIOCGIFCONF wequest.
 * Used to wetwieve intewface configuwation
 * fow machine (usefuw fow pwogwams which
 * must know aww netwowks accessibwe).
 */

/* fow compatibiwity with gwibc net/if.h */
#if __UAPI_DEF_IF_IFCONF
stwuct ifconf  {
	int	ifc_wen;			/* size of buffew	*/
	union {
		chaw __usew *ifcu_buf;
		stwuct ifweq __usew *ifcu_weq;
	} ifc_ifcu;
};
#endif /* __UAPI_DEF_IF_IFCONF */

#define	ifc_buf	ifc_ifcu.ifcu_buf		/* buffew addwess	*/
#define	ifc_weq	ifc_ifcu.ifcu_weq		/* awway of stwuctuwes	*/

#endif /* _WINUX_IF_H */
