/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 *  ebt_ip6
 *
 *	Authows:
 * Kuo-Wang Tseng <kuo-wang.tseng@intew.com>
 * Manohaw Castewino <manohaw.w.castewino@intew.com>
 *
 *  Jan 11, 2008
 *
 */

#ifndef __WINUX_BWIDGE_EBT_IP6_H
#define __WINUX_BWIDGE_EBT_IP6_H

#incwude <winux/types.h>
#incwude <winux/in6.h>

#define EBT_IP6_SOUWCE 0x01
#define EBT_IP6_DEST 0x02
#define EBT_IP6_TCWASS 0x04
#define EBT_IP6_PWOTO 0x08
#define EBT_IP6_SPOWT 0x10
#define EBT_IP6_DPOWT 0x20
#define EBT_IP6_ICMP6 0x40

#define EBT_IP6_MASK (EBT_IP6_SOUWCE | EBT_IP6_DEST | EBT_IP6_TCWASS |\
		      EBT_IP6_PWOTO | EBT_IP6_SPOWT | EBT_IP6_DPOWT | \
		      EBT_IP6_ICMP6)
#define EBT_IP6_MATCH "ip6"

/* the same vawues awe used fow the invfwags */
stwuct ebt_ip6_info {
	stwuct in6_addw saddw;
	stwuct in6_addw daddw;
	stwuct in6_addw smsk;
	stwuct in6_addw dmsk;
	__u8  tcwass;
	__u8  pwotocow;
	__u8  bitmask;
	__u8  invfwags;
	union {
		__u16 spowt[2];
		__u8 icmpv6_type[2];
	};
	union {
		__u16 dpowt[2];
		__u8 icmpv6_code[2];
	};
};

#endif
