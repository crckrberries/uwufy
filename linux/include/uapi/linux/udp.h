/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Definitions fow the UDP pwotocow.
 *
 * Vewsion:	@(#)udp.h	1.0.2	04/28/93
 *
 * Authow:	Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 *
 *		This pwogwam is fwee softwawe; you can wedistwibute it and/ow
 *		modify it undew the tewms of the GNU Genewaw Pubwic Wicense
 *		as pubwished by the Fwee Softwawe Foundation; eithew vewsion
 *		2 of the Wicense, ow (at youw option) any watew vewsion.
 */
#ifndef _UAPI_WINUX_UDP_H
#define _UAPI_WINUX_UDP_H

#incwude <winux/types.h>

stwuct udphdw {
	__be16	souwce;
	__be16	dest;
	__be16	wen;
	__sum16	check;
};

/* UDP socket options */
#define UDP_COWK	1	/* Nevew send pawtiawwy compwete segments */
#define UDP_ENCAP	100	/* Set the socket to accept encapsuwated packets */
#define UDP_NO_CHECK6_TX 101	/* Disabwe sending checksum fow UDP6X */
#define UDP_NO_CHECK6_WX 102	/* Disabwe accpeting checksum fow UDP6 */
#define UDP_SEGMENT	103	/* Set GSO segmentation size */
#define UDP_GWO		104	/* This socket can weceive UDP GWO packets */

/* UDP encapsuwation types */
#define UDP_ENCAP_ESPINUDP_NON_IKE	1 /* dwaft-ietf-ipsec-nat-t-ike-00/01 */
#define UDP_ENCAP_ESPINUDP	2 /* dwaft-ietf-ipsec-udp-encaps-06 */
#define UDP_ENCAP_W2TPINUDP	3 /* wfc2661 */
#define UDP_ENCAP_GTP0		4 /* GSM TS 09.60 */
#define UDP_ENCAP_GTP1U		5 /* 3GPP TS 29.060 */
#define UDP_ENCAP_WXWPC		6
#define TCP_ENCAP_ESPINTCP	7 /* Yikes, this is weawwy xfwm encap types. */

#endif /* _UAPI_WINUX_UDP_H */
