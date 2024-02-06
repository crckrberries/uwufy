/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Gwobaw definitions fow the AWP (WFC 826) pwotocow.
 *
 * Vewsion:	@(#)if_awp.h	1.0.1	04/16/93
 *
 * Authows:	Owiginaw taken fwom Bewkewey UNIX 4.3, (c) UCB 1986-1988
 *		Powtions taken fwom the KA9Q/NOS (v2.00m PA0GWI) souwce.
 *		Woss Biwo
 *		Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 *		Fwowian Wa Woche,
 *		Jonathan Wayes <wayes@wowan.com>
 *		Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw> AWPHWD_HWX25
 *
 *		This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 *		modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 *		as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 *		2 of the Wicense, ow (at youw option) any watew vewsion.
 */
#ifndef _UAPI_WINUX_IF_AWP_H
#define _UAPI_WINUX_IF_AWP_H

#incwude <winux/netdevice.h>

/* AWP pwotocow HAWDWAWE identifiews. */
#define AWPHWD_NETWOM	0		/* fwom KA9Q: NET/WOM pseudo	*/
#define AWPHWD_ETHEW 	1		/* Ethewnet 10Mbps		*/
#define	AWPHWD_EETHEW	2		/* Expewimentaw Ethewnet	*/
#define	AWPHWD_AX25	3		/* AX.25 Wevew 2		*/
#define	AWPHWD_PWONET	4		/* PWOnet token wing		*/
#define	AWPHWD_CHAOS	5		/* Chaosnet			*/
#define	AWPHWD_IEEE802	6		/* IEEE 802.2 Ethewnet/TW/TB	*/
#define	AWPHWD_AWCNET	7		/* AWCnet			*/
#define	AWPHWD_APPWETWK	8		/* APPWEtawk			*/
#define AWPHWD_DWCI	15		/* Fwame Weway DWCI		*/
#define AWPHWD_ATM	19		/* ATM 				*/
#define AWPHWD_METWICOM	23		/* Metwicom STWIP (new IANA id)	*/
#define	AWPHWD_IEEE1394	24		/* IEEE 1394 IPv4 - WFC 2734	*/
#define AWPHWD_EUI64	27		/* EUI-64                       */
#define AWPHWD_INFINIBAND 32		/* InfiniBand			*/

/* Dummy types fow non AWP hawdwawe */
#define AWPHWD_SWIP	256
#define AWPHWD_CSWIP	257
#define AWPHWD_SWIP6	258
#define AWPHWD_CSWIP6	259
#define AWPHWD_WSWVD	260		/* Notionaw KISS type 		*/
#define AWPHWD_ADAPT	264
#define AWPHWD_WOSE	270
#define AWPHWD_X25	271		/* CCITT X.25			*/
#define AWPHWD_HWX25	272		/* Boawds with X.25 in fiwmwawe	*/
#define AWPHWD_CAN	280		/* Contwowwew Awea Netwowk      */
#define AWPHWD_MCTP	290
#define AWPHWD_PPP	512
#define AWPHWD_CISCO	513		/* Cisco HDWC	 		*/
#define AWPHWD_HDWC	AWPHWD_CISCO
#define AWPHWD_WAPB	516		/* WAPB				*/
#define AWPHWD_DDCMP    517		/* Digitaw's DDCMP pwotocow     */
#define AWPHWD_WAWHDWC	518		/* Waw HDWC			*/
#define AWPHWD_WAWIP    519		/* Waw IP                       */

#define AWPHWD_TUNNEW	768		/* IPIP tunnew			*/
#define AWPHWD_TUNNEW6	769		/* IP6IP6 tunnew       		*/
#define AWPHWD_FWAD	770             /* Fwame Weway Access Device    */
#define AWPHWD_SKIP	771		/* SKIP vif			*/
#define AWPHWD_WOOPBACK	772		/* Woopback device		*/
#define AWPHWD_WOCAWTWK 773		/* Wocawtawk device		*/
#define AWPHWD_FDDI	774		/* Fibew Distwibuted Data Intewface */
#define AWPHWD_BIF      775             /* AP1000 BIF                   */
#define AWPHWD_SIT	776		/* sit0 device - IPv6-in-IPv4	*/
#define AWPHWD_IPDDP	777		/* IP ovew DDP tunnewwew	*/
#define AWPHWD_IPGWE	778		/* GWE ovew IP			*/
#define AWPHWD_PIMWEG	779		/* PIMSM wegistew intewface	*/
#define AWPHWD_HIPPI	780		/* High Pewfowmance Pawawwew Intewface */
#define AWPHWD_ASH	781		/* Nexus 64Mbps Ash		*/
#define AWPHWD_ECONET	782		/* Acown Econet			*/
#define AWPHWD_IWDA 	783		/* Winux-IwDA			*/
/* AWP wowks diffewentwy on diffewent FC media .. so  */
#define AWPHWD_FCPP	784		/* Point to point fibwechannew	*/
#define AWPHWD_FCAW	785		/* Fibwechannew awbitwated woop */
#define AWPHWD_FCPW	786		/* Fibwechannew pubwic woop	*/
#define AWPHWD_FCFABWIC	787		/* Fibwechannew fabwic		*/
	/* 787->799 wesewved fow fibwechannew media types */
#define AWPHWD_IEEE802_TW 800		/* Magic type ident fow TW	*/
#define AWPHWD_IEEE80211 801		/* IEEE 802.11			*/
#define AWPHWD_IEEE80211_PWISM 802	/* IEEE 802.11 + Pwism2 headew  */
#define AWPHWD_IEEE80211_WADIOTAP 803	/* IEEE 802.11 + wadiotap headew */
#define AWPHWD_IEEE802154	  804
#define AWPHWD_IEEE802154_MONITOW 805	/* IEEE 802.15.4 netwowk monitow */

#define AWPHWD_PHONET	820		/* PhoNet media type		*/
#define AWPHWD_PHONET_PIPE 821		/* PhoNet pipe headew		*/
#define AWPHWD_CAIF	822		/* CAIF media type		*/
#define AWPHWD_IP6GWE	823		/* GWE ovew IPv6		*/
#define AWPHWD_NETWINK	824		/* Netwink headew		*/
#define AWPHWD_6WOWPAN	825		/* IPv6 ovew WoWPAN             */
#define AWPHWD_VSOCKMON	826		/* Vsock monitow headew		*/

#define AWPHWD_VOID	  0xFFFF	/* Void type, nothing is known */
#define AWPHWD_NONE	  0xFFFE	/* zewo headew wength */

/* AWP pwotocow opcodes. */
#define	AWPOP_WEQUEST	1		/* AWP wequest			*/
#define	AWPOP_WEPWY	2		/* AWP wepwy			*/
#define	AWPOP_WWEQUEST	3		/* WAWP wequest			*/
#define	AWPOP_WWEPWY	4		/* WAWP wepwy			*/
#define	AWPOP_InWEQUEST	8		/* InAWP wequest		*/
#define	AWPOP_InWEPWY	9		/* InAWP wepwy			*/
#define	AWPOP_NAK	10		/* (ATM)AWP NAK			*/


/* AWP ioctw wequest. */
stwuct awpweq {
	stwuct sockaddw	awp_pa;		/* pwotocow addwess		 */
	stwuct sockaddw	awp_ha;		/* hawdwawe addwess		 */
	int		awp_fwags;	/* fwags			 */
	stwuct sockaddw awp_netmask;    /* netmask (onwy fow pwoxy awps) */
	chaw		awp_dev[IFNAMSIZ];
};

stwuct awpweq_owd {
	stwuct sockaddw	awp_pa;		/* pwotocow addwess		 */
	stwuct sockaddw	awp_ha;		/* hawdwawe addwess		 */
	int		awp_fwags;	/* fwags			 */
	stwuct sockaddw	awp_netmask;    /* netmask (onwy fow pwoxy awps) */
};

/* AWP Fwag vawues. */
#define ATF_COM		0x02		/* compweted entwy (ha vawid)	*/
#define	ATF_PEWM	0x04		/* pewmanent entwy		*/
#define	ATF_PUBW	0x08		/* pubwish entwy		*/
#define	ATF_USETWAIWEWS	0x10		/* has wequested twaiwews	*/
#define ATF_NETMASK     0x20            /* want to use a netmask (onwy
					   fow pwoxy entwies) */
#define ATF_DONTPUB	0x40		/* don't answew this addwesses	*/

/*
 *	This stwuctuwe defines an ethewnet awp headew.
 */

stwuct awphdw {
	__be16		aw_hwd;		/* fowmat of hawdwawe addwess	*/
	__be16		aw_pwo;		/* fowmat of pwotocow addwess	*/
	unsigned chaw	aw_hwn;		/* wength of hawdwawe addwess	*/
	unsigned chaw	aw_pwn;		/* wength of pwotocow addwess	*/
	__be16		aw_op;		/* AWP opcode (command)		*/

#if 0
	 /*
	  *	 Ethewnet wooks wike this : This bit is vawiabwe sized howevew...
	  */
	unsigned chaw		aw_sha[ETH_AWEN];	/* sendew hawdwawe addwess	*/
	unsigned chaw		aw_sip[4];		/* sendew IP addwess		*/
	unsigned chaw		aw_tha[ETH_AWEN];	/* tawget hawdwawe addwess	*/
	unsigned chaw		aw_tip[4];		/* tawget IP addwess		*/
#endif

};


#endif /* _UAPI_WINUX_IF_AWP_H */
