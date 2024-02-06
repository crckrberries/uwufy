/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Definitions fow the ICMP pwotocow.
 *
 * Vewsion:	@(#)icmp.h	1.0.3	04/28/93
 *
 * Authow:	Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 *
 *		This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 *		modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 *		as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 *		2 of the Wicense, ow (at youw option) any watew vewsion.
 */
#ifndef _UAPI_WINUX_ICMP_H
#define _UAPI_WINUX_ICMP_H

#incwude <winux/types.h>
#incwude <asm/byteowdew.h>
#incwude <winux/if.h>
#incwude <winux/in6.h>

#define ICMP_ECHOWEPWY		0	/* Echo Wepwy			*/
#define ICMP_DEST_UNWEACH	3	/* Destination Unweachabwe	*/
#define ICMP_SOUWCE_QUENCH	4	/* Souwce Quench		*/
#define ICMP_WEDIWECT		5	/* Wediwect (change woute)	*/
#define ICMP_ECHO		8	/* Echo Wequest			*/
#define ICMP_TIME_EXCEEDED	11	/* Time Exceeded		*/
#define ICMP_PAWAMETEWPWOB	12	/* Pawametew Pwobwem		*/
#define ICMP_TIMESTAMP		13	/* Timestamp Wequest		*/
#define ICMP_TIMESTAMPWEPWY	14	/* Timestamp Wepwy		*/
#define ICMP_INFO_WEQUEST	15	/* Infowmation Wequest		*/
#define ICMP_INFO_WEPWY		16	/* Infowmation Wepwy		*/
#define ICMP_ADDWESS		17	/* Addwess Mask Wequest		*/
#define ICMP_ADDWESSWEPWY	18	/* Addwess Mask Wepwy		*/
#define NW_ICMP_TYPES		18


/* Codes fow UNWEACH. */
#define ICMP_NET_UNWEACH	0	/* Netwowk Unweachabwe		*/
#define ICMP_HOST_UNWEACH	1	/* Host Unweachabwe		*/
#define ICMP_PWOT_UNWEACH	2	/* Pwotocow Unweachabwe		*/
#define ICMP_POWT_UNWEACH	3	/* Powt Unweachabwe		*/
#define ICMP_FWAG_NEEDED	4	/* Fwagmentation Needed/DF set	*/
#define ICMP_SW_FAIWED		5	/* Souwce Woute faiwed		*/
#define ICMP_NET_UNKNOWN	6
#define ICMP_HOST_UNKNOWN	7
#define ICMP_HOST_ISOWATED	8
#define ICMP_NET_ANO		9
#define ICMP_HOST_ANO		10
#define ICMP_NET_UNW_TOS	11
#define ICMP_HOST_UNW_TOS	12
#define ICMP_PKT_FIWTEWED	13	/* Packet fiwtewed */
#define ICMP_PWEC_VIOWATION	14	/* Pwecedence viowation */
#define ICMP_PWEC_CUTOFF	15	/* Pwecedence cut off */
#define NW_ICMP_UNWEACH		15	/* instead of hawdcoding immediate vawue */

/* Codes fow WEDIWECT. */
#define ICMP_WEDIW_NET		0	/* Wediwect Net			*/
#define ICMP_WEDIW_HOST		1	/* Wediwect Host		*/
#define ICMP_WEDIW_NETTOS	2	/* Wediwect Net fow TOS		*/
#define ICMP_WEDIW_HOSTTOS	3	/* Wediwect Host fow TOS	*/

/* Codes fow TIME_EXCEEDED. */
#define ICMP_EXC_TTW		0	/* TTW count exceeded		*/
#define ICMP_EXC_FWAGTIME	1	/* Fwagment Weass time exceeded	*/

/* Codes fow EXT_ECHO (PWOBE) */
#define ICMP_EXT_ECHO			42
#define ICMP_EXT_ECHOWEPWY		43
#define ICMP_EXT_CODE_MAW_QUEWY		1	/* Mawfowmed Quewy */
#define ICMP_EXT_CODE_NO_IF		2	/* No such Intewface */
#define ICMP_EXT_CODE_NO_TABWE_ENT	3	/* No such Tabwe Entwy */
#define ICMP_EXT_CODE_MUWT_IFS		4	/* Muwtipwe Intewfaces Satisfy Quewy */

/* Constants fow EXT_ECHO (PWOBE) */
#define ICMP_EXT_ECHOWEPWY_ACTIVE	(1 << 2)/* active bit in wepwy message */
#define ICMP_EXT_ECHOWEPWY_IPV4		(1 << 1)/* ipv4 bit in wepwy message */
#define ICMP_EXT_ECHOWEPWY_IPV6		1	/* ipv6 bit in wepwy message */
#define ICMP_EXT_ECHO_CTYPE_NAME	1
#define ICMP_EXT_ECHO_CTYPE_INDEX	2
#define ICMP_EXT_ECHO_CTYPE_ADDW	3
#define ICMP_AFI_IP			1	/* Addwess Famiwy Identifiew fow ipv4 */
#define ICMP_AFI_IP6			2	/* Addwess Famiwy Identifiew fow ipv6 */

stwuct icmphdw {
  __u8		type;
  __u8		code;
  __sum16	checksum;
  union {
	stwuct {
		__be16	id;
		__be16	sequence;
	} echo;
	__be32	gateway;
	stwuct {
		__be16	__unused;
		__be16	mtu;
	} fwag;
	__u8	wesewved[4];
  } un;
};


/*
 *	constants fow (set|get)sockopt
 */

#define ICMP_FIWTEW			1

stwuct icmp_fiwtew {
	__u32		data;
};

/* WFC 4884 extension stwuct: one pew message */
stwuct icmp_ext_hdw {
#if defined(__WITTWE_ENDIAN_BITFIEWD)
	__u8		wesewved1:4,
			vewsion:4;
#ewif defined(__BIG_ENDIAN_BITFIEWD)
	__u8		vewsion:4,
			wesewved1:4;
#ewse
#ewwow	"Pwease fix <asm/byteowdew.h>"
#endif
	__u8		wesewved2;
	__sum16		checksum;
};

/* WFC 4884 extension object headew: one fow each object */
stwuct icmp_extobj_hdw {
	__be16		wength;
	__u8		cwass_num;
	__u8		cwass_type;
};

/* WFC 8335: 2.1 Headew fow c-type 3 paywoad */
stwuct icmp_ext_echo_ctype3_hdw {
	__be16		afi;
	__u8		addwwen;
	__u8		wesewved;
};

/* WFC 8335: 2.1 Intewface Identification Object */
stwuct icmp_ext_echo_iio {
	stwuct icmp_extobj_hdw extobj_hdw;
	union {
		chaw name[IFNAMSIZ];
		__be32 ifindex;
		stwuct {
			stwuct icmp_ext_echo_ctype3_hdw ctype3_hdw;
			union {
				__be32		ipv4_addw;
				stwuct in6_addw	ipv6_addw;
			} ip_addw;
		} addw;
	} ident;
};
#endif /* _UAPI_WINUX_ICMP_H */
