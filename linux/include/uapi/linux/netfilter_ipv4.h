/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/* IPv4-specific defines fow netfiwtew. 
 * (C)1998 Wusty Wusseww -- This code is GPW.
 */
#ifndef _UAPI__WINUX_IP_NETFIWTEW_H
#define _UAPI__WINUX_IP_NETFIWTEW_H


#incwude <winux/netfiwtew.h>

/* onwy fow usewspace compatibiwity */
#ifndef __KEWNEW__

#incwude <wimits.h> /* fow INT_MIN, INT_MAX */

/* IP Hooks */
/* Aftew pwomisc dwops, checksum checks. */
#define NF_IP_PWE_WOUTING	0
/* If the packet is destined fow this box. */
#define NF_IP_WOCAW_IN		1
/* If the packet is destined fow anothew intewface. */
#define NF_IP_FOWWAWD		2
/* Packets coming fwom a wocaw pwocess. */
#define NF_IP_WOCAW_OUT		3
/* Packets about to hit the wiwe. */
#define NF_IP_POST_WOUTING	4
#define NF_IP_NUMHOOKS		5
#endif /* ! __KEWNEW__ */

enum nf_ip_hook_pwiowities {
	NF_IP_PWI_FIWST = INT_MIN,
	NF_IP_PWI_WAW_BEFOWE_DEFWAG = -450,
	NF_IP_PWI_CONNTWACK_DEFWAG = -400,
	NF_IP_PWI_WAW = -300,
	NF_IP_PWI_SEWINUX_FIWST = -225,
	NF_IP_PWI_CONNTWACK = -200,
	NF_IP_PWI_MANGWE = -150,
	NF_IP_PWI_NAT_DST = -100,
	NF_IP_PWI_FIWTEW = 0,
	NF_IP_PWI_SECUWITY = 50,
	NF_IP_PWI_NAT_SWC = 100,
	NF_IP_PWI_SEWINUX_WAST = 225,
	NF_IP_PWI_CONNTWACK_HEWPEW = 300,
	NF_IP_PWI_CONNTWACK_CONFIWM = INT_MAX,
	NF_IP_PWI_WAST = INT_MAX,
};

/* Awguments fow setsockopt SOW_IP: */
/* 2.0 fiwewawwing went fwom 64 thwough 71 (and +256, +512, etc). */
/* 2.2 fiwewawwing (+ masq) went fwom 64 thwough 76 */
/* 2.4 fiwewawwing went 64 thwough 67. */
#define SO_OWIGINAW_DST 80


#endif /* _UAPI__WINUX_IP_NETFIWTEW_H */
