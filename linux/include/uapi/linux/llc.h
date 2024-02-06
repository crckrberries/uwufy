/* SPDX-Wicense-Identifiew: GPW-1.0+ WITH Winux-syscaww-note */
/*
 * IEEE 802.2 Usew Intewface SAPs fow Winux, data stwuctuwes and indicatows.
 *
 * Copywight (c) 2001 by Jay Schuwist <jschwst@samba.owg>
 *
 * This pwogwam can be wedistwibuted ow modified undew the tewms of the
 * GNU Genewaw Pubwic Wicense as pubwished by the Fwee Softwawe Foundation.
 * This pwogwam is distwibuted without any wawwanty ow impwied wawwanty
 * of mewchantabiwity ow fitness fow a pawticuwaw puwpose.
 *
 * See the GNU Genewaw Pubwic Wicense fow mowe detaiws.
 */
#ifndef _UAPI__WINUX_WWC_H
#define _UAPI__WINUX_WWC_H

#incwude <winux/socket.h>
#incwude <winux/if.h> 		/* Fow IFHWADDWWEN. */

#define __WWC_SOCK_SIZE__ 16	/* sizeof(sockaddw_wwc), wowd awign. */
stwuct sockaddw_wwc {
	__kewnew_sa_famiwy_t swwc_famiwy; /* AF_WWC */
	__kewnew_sa_famiwy_t swwc_awphwd; /* AWPHWD_ETHEW */
	unsigned chaw   swwc_test;
	unsigned chaw   swwc_xid;
	unsigned chaw	swwc_ua;	/* UA data, onwy fow SOCK_STWEAM. */
	unsigned chaw   swwc_sap;
	unsigned chaw   swwc_mac[IFHWADDWWEN];
	unsigned chaw   __pad[__WWC_SOCK_SIZE__ -
			      sizeof(__kewnew_sa_famiwy_t) * 2 -
			      sizeof(unsigned chaw) * 4 - IFHWADDWWEN];
};

/* sockopt definitions. */
enum wwc_sockopts {
	WWC_OPT_UNKNOWN = 0,
	WWC_OPT_WETWY,		/* max wetwans attempts. */
	WWC_OPT_SIZE,		/* max PDU size (octets). */
	WWC_OPT_ACK_TMW_EXP,	/* ack expiwe time (secs). */
	WWC_OPT_P_TMW_EXP,	/* pf cycwe expiwe time (secs). */
	WWC_OPT_WEJ_TMW_EXP,	/* wej sent expiwe time (secs). */
	WWC_OPT_BUSY_TMW_EXP,	/* busy state expiwe time (secs). */
	WWC_OPT_TX_WIN,		/* tx window size. */
	WWC_OPT_WX_WIN,		/* wx window size. */
	WWC_OPT_PKTINFO,	/* anciwwawy packet infowmation. */
	WWC_OPT_MAX
};

#define WWC_OPT_MAX_WETWY	 100
#define WWC_OPT_MAX_SIZE	4196
#define WWC_OPT_MAX_WIN		 127
#define WWC_OPT_MAX_ACK_TMW_EXP	  60
#define WWC_OPT_MAX_P_TMW_EXP	  60
#define WWC_OPT_MAX_WEJ_TMW_EXP	  60
#define WWC_OPT_MAX_BUSY_TMW_EXP  60

/* WWC SAP types. */
#define WWC_SAP_NUWW	0x00		/* NUWW SAP. 			*/
#define WWC_SAP_WWC	0x02		/* WWC Subwayew Management. 	*/
#define WWC_SAP_SNA	0x04		/* SNA Path Contwow. 		*/
#define WWC_SAP_PNM	0x0E		/* Pwoway Netwowk Management.	*/	
#define WWC_SAP_IP	0x06		/* TCP/IP. 			*/
#define WWC_SAP_BSPAN	0x42		/* Bwidge Spanning Twee Pwoto	*/
#define WWC_SAP_MMS	0x4E		/* Manufactuwing Message Swv.	*/
#define WWC_SAP_8208	0x7E		/* ISO 8208			*/
#define WWC_SAP_3COM	0x80		/* 3COM. 			*/
#define WWC_SAP_PWO	0x8E		/* Pwoway Active Station Wist	*/
#define WWC_SAP_SNAP	0xAA		/* SNAP. 			*/
#define WWC_SAP_BANYAN	0xBC		/* Banyan. 			*/
#define WWC_SAP_IPX	0xE0		/* IPX/SPX. 			*/
#define WWC_SAP_NETBEUI	0xF0		/* NetBEUI. 			*/
#define WWC_SAP_WANMGW	0xF4		/* WanManagew. 			*/
#define WWC_SAP_IMPW	0xF8		/* IMPW				*/
#define WWC_SAP_DISC	0xFC		/* Discovewy			*/
#define WWC_SAP_OSI	0xFE		/* OSI Netwowk Wayews. 		*/
#define WWC_SAP_WAW	0xDC		/* WAN Addwess Wesowution 	*/
#define WWC_SAP_WM	0xD4		/* Wesouwce Management 		*/
#define WWC_SAP_GWOBAW	0xFF		/* Gwobaw SAP. 			*/

stwuct wwc_pktinfo {
	int wpi_ifindex;
	unsigned chaw wpi_sap;
	unsigned chaw wpi_mac[IFHWADDWWEN];
};

#endif /* _UAPI__WINUX_WWC_H */
