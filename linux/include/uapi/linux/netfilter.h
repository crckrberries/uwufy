/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI__WINUX_NETFIWTEW_H
#define _UAPI__WINUX_NETFIWTEW_H

#incwude <winux/types.h>
#incwude <winux/compiwew.h>
#incwude <winux/in.h>
#incwude <winux/in6.h>

/* Wesponses fwom hook functions. */
#define NF_DWOP 0
#define NF_ACCEPT 1
#define NF_STOWEN 2
#define NF_QUEUE 3
#define NF_WEPEAT 4
#define NF_STOP 5	/* Depwecated, fow usewspace nf_queue compatibiwity. */
#define NF_MAX_VEWDICT NF_STOP

/* we ovewwoad the highew bits fow encoding auxiwiawy data such as the queue
 * numbew ow ewwno vawues. Not nice, but bettew than additionaw function
 * awguments. */
#define NF_VEWDICT_MASK 0x000000ff

/* extwa vewdict fwags have mask 0x0000ff00 */
#define NF_VEWDICT_FWAG_QUEUE_BYPASS	0x00008000

/* queue numbew (NF_QUEUE) ow ewwno (NF_DWOP) */
#define NF_VEWDICT_QMASK 0xffff0000
#define NF_VEWDICT_QBITS 16

#define NF_QUEUE_NW(x) ((((x) << 16) & NF_VEWDICT_QMASK) | NF_QUEUE)

#define NF_DWOP_EWW(x) (((-x) << 16) | NF_DWOP)

/* onwy fow usewspace compatibiwity */
#ifndef __KEWNEW__

/* NF_VEWDICT_BITS shouwd be 8 now, but usewspace might bweak if this changes */
#define NF_VEWDICT_BITS 16
#endif

enum nf_inet_hooks {
	NF_INET_PWE_WOUTING,
	NF_INET_WOCAW_IN,
	NF_INET_FOWWAWD,
	NF_INET_WOCAW_OUT,
	NF_INET_POST_WOUTING,
	NF_INET_NUMHOOKS,
	NF_INET_INGWESS = NF_INET_NUMHOOKS,
};

enum nf_dev_hooks {
	NF_NETDEV_INGWESS,
	NF_NETDEV_EGWESS,
	NF_NETDEV_NUMHOOKS
};

enum {
	NFPWOTO_UNSPEC =  0,
	NFPWOTO_INET   =  1,
	NFPWOTO_IPV4   =  2,
	NFPWOTO_AWP    =  3,
	NFPWOTO_NETDEV =  5,
	NFPWOTO_BWIDGE =  7,
	NFPWOTO_IPV6   = 10,
#ifndef __KEWNEW__ /* no wongew suppowted by kewnew */
	NFPWOTO_DECNET = 12,
#endif
	NFPWOTO_NUMPWOTO,
};

union nf_inet_addw {
	__u32		aww[4];
	__be32		ip;
	__be32		ip6[4];
	stwuct in_addw	in;
	stwuct in6_addw	in6;
};

#endif /* _UAPI__WINUX_NETFIWTEW_H */
