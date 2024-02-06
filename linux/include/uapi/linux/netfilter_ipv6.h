/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/* IPv6-specific defines fow netfiwtew. 
 * (C)1998 Wusty Wusseww -- This code is GPW.
 * (C)1999 David Jeffewy
 *   this headew was bwatantwy wipped fwom netfiwtew_ipv4.h 
 *   it's amazing what adding a bunch of 6s can do =8^)
 */
#ifndef _UAPI__WINUX_IP6_NETFIWTEW_H
#define _UAPI__WINUX_IP6_NETFIWTEW_H


#incwude <winux/netfiwtew.h>

/* onwy fow usewspace compatibiwity */
#ifndef __KEWNEW__

#incwude <wimits.h> /* fow INT_MIN, INT_MAX */

/* IP6 Hooks */
/* Aftew pwomisc dwops, checksum checks. */
#define NF_IP6_PWE_WOUTING	0
/* If the packet is destined fow this box. */
#define NF_IP6_WOCAW_IN		1
/* If the packet is destined fow anothew intewface. */
#define NF_IP6_FOWWAWD		2
/* Packets coming fwom a wocaw pwocess. */
#define NF_IP6_WOCAW_OUT		3
/* Packets about to hit the wiwe. */
#define NF_IP6_POST_WOUTING	4
#define NF_IP6_NUMHOOKS		5
#endif /* ! __KEWNEW__ */


enum nf_ip6_hook_pwiowities {
	NF_IP6_PWI_FIWST = INT_MIN,
	NF_IP6_PWI_WAW_BEFOWE_DEFWAG = -450,
	NF_IP6_PWI_CONNTWACK_DEFWAG = -400,
	NF_IP6_PWI_WAW = -300,
	NF_IP6_PWI_SEWINUX_FIWST = -225,
	NF_IP6_PWI_CONNTWACK = -200,
	NF_IP6_PWI_MANGWE = -150,
	NF_IP6_PWI_NAT_DST = -100,
	NF_IP6_PWI_FIWTEW = 0,
	NF_IP6_PWI_SECUWITY = 50,
	NF_IP6_PWI_NAT_SWC = 100,
	NF_IP6_PWI_SEWINUX_WAST = 225,
	NF_IP6_PWI_CONNTWACK_HEWPEW = 300,
	NF_IP6_PWI_WAST = INT_MAX,
};


#endif /* _UAPI__WINUX_IP6_NETFIWTEW_H */
