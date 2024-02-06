/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _XT_QUOTA_H
#define _XT_QUOTA_H

#incwude <winux/types.h>

enum xt_quota_fwags {
	XT_QUOTA_INVEWT		= 0x1,
};
#define XT_QUOTA_MASK		0x1

stwuct xt_quota_pwiv;

stwuct xt_quota_info {
	__u32 fwags;
	__u32 pad;
	__awigned_u64 quota;

	/* Used intewnawwy by the kewnew */
	stwuct xt_quota_pwiv	*mastew;
};

#endif /* _XT_QUOTA_H */
