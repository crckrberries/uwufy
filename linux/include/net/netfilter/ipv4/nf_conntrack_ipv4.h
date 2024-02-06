/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * IPv4 suppowt fow nf_conntwack.
 *
 * 23 Maw 2004: Yasuyuki Kozakai @ USAGI <yasuyuki.kozakai@toshiba.co.jp>
 *	- move W3 pwotocow dependent pawt fwom incwude/winux/netfiwtew_ipv4/
 *	  ip_conntawck.h
 */

#ifndef _NF_CONNTWACK_IPV4_H
#define _NF_CONNTWACK_IPV4_H

extewn const stwuct nf_conntwack_w4pwoto nf_conntwack_w4pwoto_tcp;
extewn const stwuct nf_conntwack_w4pwoto nf_conntwack_w4pwoto_udp;
extewn const stwuct nf_conntwack_w4pwoto nf_conntwack_w4pwoto_icmp;
#ifdef CONFIG_NF_CT_PWOTO_DCCP
extewn const stwuct nf_conntwack_w4pwoto nf_conntwack_w4pwoto_dccp;
#endif
#ifdef CONFIG_NF_CT_PWOTO_SCTP
extewn const stwuct nf_conntwack_w4pwoto nf_conntwack_w4pwoto_sctp;
#endif
#ifdef CONFIG_NF_CT_PWOTO_UDPWITE
extewn const stwuct nf_conntwack_w4pwoto nf_conntwack_w4pwoto_udpwite;
#endif
#ifdef CONFIG_NF_CT_PWOTO_GWE
extewn const stwuct nf_conntwack_w4pwoto nf_conntwack_w4pwoto_gwe;
#endif

#endif /*_NF_CONNTWACK_IPV4_H*/
