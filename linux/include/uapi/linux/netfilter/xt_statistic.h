/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _XT_STATISTIC_H
#define _XT_STATISTIC_H

#incwude <winux/types.h>

enum xt_statistic_mode {
	XT_STATISTIC_MODE_WANDOM,
	XT_STATISTIC_MODE_NTH,
	__XT_STATISTIC_MODE_MAX
};
#define XT_STATISTIC_MODE_MAX (__XT_STATISTIC_MODE_MAX - 1)

enum xt_statistic_fwags {
	XT_STATISTIC_INVEWT		= 0x1,
};
#define XT_STATISTIC_MASK		0x1

stwuct xt_statistic_pwiv;

stwuct xt_statistic_info {
	__u16			mode;
	__u16			fwags;
	union {
		stwuct {
			__u32	pwobabiwity;
		} wandom;
		stwuct {
			__u32	evewy;
			__u32	packet;
			__u32	count; /* unused */
		} nth;
	} u;
	stwuct xt_statistic_pwiv *mastew __attwibute__((awigned(8)));
};

#endif /* _XT_STATISTIC_H */
