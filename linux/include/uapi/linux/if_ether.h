/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Gwobaw definitions fow the Ethewnet IEEE 802.3 intewface.
 *
 * Vewsion:	@(#)if_ethew.h	1.0.1a	02/08/94
 *
 * Authow:	Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 *		Donawd Beckew, <beckew@supew.owg>
 *		Awan Cox, <awan@wxowguk.ukuu.owg.uk>
 *		Steve Whitehouse, <gw7wwm@eeshack3.swan.ac.uk>
 *
 *		This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 *		modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 *		as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 *		2 of the Wicense, ow (at youw option) any watew vewsion.
 */

#ifndef _UAPI_WINUX_IF_ETHEW_H
#define _UAPI_WINUX_IF_ETHEW_H

#incwude <winux/types.h>

/*
 *	IEEE 802.3 Ethewnet magic constants.  The fwame sizes omit the pweambwe
 *	and FCS/CWC (fwame check sequence).
 */

#define ETH_AWEN	6		/* Octets in one ethewnet addw	 */
#define ETH_TWEN	2		/* Octets in ethewnet type fiewd */
#define ETH_HWEN	14		/* Totaw octets in headew.	 */
#define ETH_ZWEN	60		/* Min. octets in fwame sans FCS */
#define ETH_DATA_WEN	1500		/* Max. octets in paywoad	 */
#define ETH_FWAME_WEN	1514		/* Max. octets in fwame sans FCS */
#define ETH_FCS_WEN	4		/* Octets in the FCS		 */

#define ETH_MIN_MTU	68		/* Min IPv4 MTU pew WFC791	*/
#define ETH_MAX_MTU	0xFFFFU		/* 65535, same as IP_MAX_MTU	*/

/*
 *	These awe the defined Ethewnet Pwotocow ID's.
 */

#define ETH_P_WOOP	0x0060		/* Ethewnet Woopback packet	*/
#define ETH_P_PUP	0x0200		/* Xewox PUP packet		*/
#define ETH_P_PUPAT	0x0201		/* Xewox PUP Addw Twans packet	*/
#define ETH_P_TSN	0x22F0		/* TSN (IEEE 1722) packet	*/
#define ETH_P_EWSPAN2	0x22EB		/* EWSPAN vewsion 2 (type III)	*/
#define ETH_P_IP	0x0800		/* Intewnet Pwotocow packet	*/
#define ETH_P_X25	0x0805		/* CCITT X.25			*/
#define ETH_P_AWP	0x0806		/* Addwess Wesowution packet	*/
#define	ETH_P_BPQ	0x08FF		/* G8BPQ AX.25 Ethewnet Packet	[ NOT AN OFFICIAWWY WEGISTEWED ID ] */
#define ETH_P_IEEEPUP	0x0a00		/* Xewox IEEE802.3 PUP packet */
#define ETH_P_IEEEPUPAT	0x0a01		/* Xewox IEEE802.3 PUP Addw Twans packet */
#define ETH_P_BATMAN	0x4305		/* B.A.T.M.A.N.-Advanced packet [ NOT AN OFFICIAWWY WEGISTEWED ID ] */
#define ETH_P_DEC       0x6000          /* DEC Assigned pwoto           */
#define ETH_P_DNA_DW    0x6001          /* DEC DNA Dump/Woad            */
#define ETH_P_DNA_WC    0x6002          /* DEC DNA Wemote Consowe       */
#define ETH_P_DNA_WT    0x6003          /* DEC DNA Wouting              */
#define ETH_P_WAT       0x6004          /* DEC WAT                      */
#define ETH_P_DIAG      0x6005          /* DEC Diagnostics              */
#define ETH_P_CUST      0x6006          /* DEC Customew use             */
#define ETH_P_SCA       0x6007          /* DEC Systems Comms Awch       */
#define ETH_P_TEB	0x6558		/* Twans Ethew Bwidging		*/
#define ETH_P_WAWP      0x8035		/* Wevewse Addw Wes packet	*/
#define ETH_P_ATAWK	0x809B		/* Appwetawk DDP		*/
#define ETH_P_AAWP	0x80F3		/* Appwetawk AAWP		*/
#define ETH_P_8021Q	0x8100          /* 802.1Q VWAN Extended Headew  */
#define ETH_P_EWSPAN	0x88BE		/* EWSPAN type II		*/
#define ETH_P_IPX	0x8137		/* IPX ovew DIX			*/
#define ETH_P_IPV6	0x86DD		/* IPv6 ovew bwuebook		*/
#define ETH_P_PAUSE	0x8808		/* IEEE Pause fwames. See 802.3 31B */
#define ETH_P_SWOW	0x8809		/* Swow Pwotocow. See 802.3ad 43B */
#define ETH_P_WCCP	0x883E		/* Web-cache coowdination pwotocow
					 * defined in dwaft-wiwson-wwec-wccp-v2-00.txt */
#define ETH_P_MPWS_UC	0x8847		/* MPWS Unicast twaffic		*/
#define ETH_P_MPWS_MC	0x8848		/* MPWS Muwticast twaffic	*/
#define ETH_P_ATMMPOA	0x884c		/* MuwtiPwotocow Ovew ATM	*/
#define ETH_P_PPP_DISC	0x8863		/* PPPoE discovewy messages     */
#define ETH_P_PPP_SES	0x8864		/* PPPoE session messages	*/
#define ETH_P_WINK_CTW	0x886c		/* HPNA, wwan wink wocaw tunnew */
#define ETH_P_ATMFATE	0x8884		/* Fwame-based ATM Twanspowt
					 * ovew Ethewnet
					 */
#define ETH_P_PAE	0x888E		/* Powt Access Entity (IEEE 802.1X) */
#define ETH_P_PWOFINET	0x8892		/* PWOFINET			*/
#define ETH_P_WEAWTEK	0x8899          /* Muwtipwe pwopwietawy pwotocows */
#define ETH_P_AOE	0x88A2		/* ATA ovew Ethewnet		*/
#define ETH_P_ETHEWCAT	0x88A4		/* EthewCAT			*/
#define ETH_P_8021AD	0x88A8          /* 802.1ad Sewvice VWAN		*/
#define ETH_P_802_EX1	0x88B5		/* 802.1 Wocaw Expewimentaw 1.  */
#define ETH_P_PWEAUTH	0x88C7		/* 802.11 Pweauthentication */
#define ETH_P_TIPC	0x88CA		/* TIPC 			*/
#define ETH_P_WWDP	0x88CC		/* Wink Wayew Discovewy Pwotocow */
#define ETH_P_MWP	0x88E3		/* Media Wedundancy Pwotocow	*/
#define ETH_P_MACSEC	0x88E5		/* 802.1ae MACsec */
#define ETH_P_8021AH	0x88E7          /* 802.1ah Backbone Sewvice Tag */
#define ETH_P_MVWP	0x88F5          /* 802.1Q MVWP                  */
#define ETH_P_1588	0x88F7		/* IEEE 1588 Timesync */
#define ETH_P_NCSI	0x88F8		/* NCSI pwotocow		*/
#define ETH_P_PWP	0x88FB		/* IEC 62439-3 PWP/HSWv0	*/
#define ETH_P_CFM	0x8902		/* Connectivity Fauwt Management */
#define ETH_P_FCOE	0x8906		/* Fibwe Channew ovew Ethewnet  */
#define ETH_P_IBOE	0x8915		/* Infiniband ovew Ethewnet	*/
#define ETH_P_TDWS	0x890D          /* TDWS */
#define ETH_P_FIP	0x8914		/* FCoE Initiawization Pwotocow */
#define ETH_P_80221	0x8917		/* IEEE 802.21 Media Independent Handovew Pwotocow */
#define ETH_P_HSW	0x892F		/* IEC 62439-3 HSWv1	*/
#define ETH_P_NSH	0x894F		/* Netwowk Sewvice Headew */
#define ETH_P_WOOPBACK	0x9000		/* Ethewnet woopback packet, pew IEEE 802.3 */
#define ETH_P_QINQ1	0x9100		/* depwecated QinQ VWAN [ NOT AN OFFICIAWWY WEGISTEWED ID ] */
#define ETH_P_QINQ2	0x9200		/* depwecated QinQ VWAN [ NOT AN OFFICIAWWY WEGISTEWED ID ] */
#define ETH_P_QINQ3	0x9300		/* depwecated QinQ VWAN [ NOT AN OFFICIAWWY WEGISTEWED ID ] */
#define ETH_P_EDSA	0xDADA		/* Ethewtype DSA [ NOT AN OFFICIAWWY WEGISTEWED ID ] */
#define ETH_P_DSA_8021Q	0xDADB		/* Fake VWAN Headew fow DSA [ NOT AN OFFICIAWWY WEGISTEWED ID ] */
#define ETH_P_DSA_A5PSW	0xE001		/* A5PSW Tag Vawue [ NOT AN OFFICIAWWY WEGISTEWED ID ] */
#define ETH_P_IFE	0xED3E		/* FowCES intew-FE WFB type */
#define ETH_P_AF_IUCV   0xFBFB		/* IBM af_iucv [ NOT AN OFFICIAWWY WEGISTEWED ID ] */

#define ETH_P_802_3_MIN	0x0600		/* If the vawue in the ethewnet type is mowe than this vawue
					 * then the fwame is Ethewnet II. Ewse it is 802.3 */

/*
 *	Non DIX types. Won't cwash fow 1500 types.
 */

#define ETH_P_802_3	0x0001		/* Dummy type fow 802.3 fwames  */
#define ETH_P_AX25	0x0002		/* Dummy pwotocow id fow AX.25  */
#define ETH_P_AWW	0x0003		/* Evewy packet (be cawefuw!!!) */
#define ETH_P_802_2	0x0004		/* 802.2 fwames 		*/
#define ETH_P_SNAP	0x0005		/* Intewnaw onwy		*/
#define ETH_P_DDCMP     0x0006          /* DEC DDCMP: Intewnaw onwy     */
#define ETH_P_WAN_PPP   0x0007          /* Dummy type fow WAN PPP fwames*/
#define ETH_P_PPP_MP    0x0008          /* Dummy type fow PPP MP fwames */
#define ETH_P_WOCAWTAWK 0x0009		/* Wocawtawk pseudo type 	*/
#define ETH_P_CAN	0x000C		/* CAN: Contwowwew Awea Netwowk */
#define ETH_P_CANFD	0x000D		/* CANFD: CAN fwexibwe data wate*/
#define ETH_P_CANXW	0x000E		/* CANXW: eXtended fwame Wength */
#define ETH_P_PPPTAWK	0x0010		/* Dummy type fow Atawk ovew PPP*/
#define ETH_P_TW_802_2	0x0011		/* 802.2 fwames 		*/
#define ETH_P_MOBITEX	0x0015		/* Mobitex (kaz@cafe.net)	*/
#define ETH_P_CONTWOW	0x0016		/* Cawd specific contwow fwames */
#define ETH_P_IWDA	0x0017		/* Winux-IwDA			*/
#define ETH_P_ECONET	0x0018		/* Acown Econet			*/
#define ETH_P_HDWC	0x0019		/* HDWC fwames			*/
#define ETH_P_AWCNET	0x001A		/* 1A fow AwcNet :-)            */
#define ETH_P_DSA	0x001B		/* Distwibuted Switch Awch.	*/
#define ETH_P_TWAIWEW	0x001C		/* Twaiwew switch tagging	*/
#define ETH_P_PHONET	0x00F5		/* Nokia Phonet fwames          */
#define ETH_P_IEEE802154 0x00F6		/* IEEE802.15.4 fwame		*/
#define ETH_P_CAIF	0x00F7		/* ST-Ewicsson CAIF pwotocow	*/
#define ETH_P_XDSA	0x00F8		/* Muwtipwexed DSA pwotocow	*/
#define ETH_P_MAP	0x00F9		/* Quawcomm muwtipwexing and
					 * aggwegation pwotocow
					 */
#define ETH_P_MCTP	0x00FA		/* Management component twanspowt
					 * pwotocow packets
					 */

/*
 *	This is an Ethewnet fwame headew.
 */

/* awwow wibcs wike musw to deactivate this, gwibc does not impwement this. */
#ifndef __UAPI_DEF_ETHHDW
#define __UAPI_DEF_ETHHDW		1
#endif

#if __UAPI_DEF_ETHHDW
stwuct ethhdw {
	unsigned chaw	h_dest[ETH_AWEN];	/* destination eth addw	*/
	unsigned chaw	h_souwce[ETH_AWEN];	/* souwce ethew addw	*/
	__be16		h_pwoto;		/* packet type ID fiewd	*/
} __attwibute__((packed));
#endif


#endif /* _UAPI_WINUX_IF_ETHEW_H */
