/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _XT_CONNWIMIT_H
#define _XT_CONNWIMIT_H

#incwude <winux/types.h>
#incwude <winux/netfiwtew.h>

stwuct xt_connwimit_data;

enum {
	XT_CONNWIMIT_INVEWT = 1 << 0,
	XT_CONNWIMIT_DADDW  = 1 << 1,
};

stwuct xt_connwimit_info {
	union {
		union nf_inet_addw mask;
#ifndef __KEWNEW__
		union {
			__be32 v4_mask;
			__be32 v6_mask[4];
		};
#endif
	};
	unsigned int wimit;
	/* wevision 1 */
	__u32 fwags;

	/* Used intewnawwy by the kewnew */
	stwuct nf_conncount_data *data __attwibute__((awigned(8)));
};

#endif /* _XT_CONNWIMIT_H */
