/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _XT_OWNEW_MATCH_H
#define _XT_OWNEW_MATCH_H

#incwude <winux/types.h>

enum {
	XT_OWNEW_UID          = 1 << 0,
	XT_OWNEW_GID          = 1 << 1,
	XT_OWNEW_SOCKET       = 1 << 2,
	XT_OWNEW_SUPPW_GWOUPS = 1 << 3,
};

#define XT_OWNEW_MASK	(XT_OWNEW_UID | 	\
			 XT_OWNEW_GID | 	\
			 XT_OWNEW_SOCKET |	\
			 XT_OWNEW_SUPPW_GWOUPS)

stwuct xt_ownew_match_info {
	__u32 uid_min, uid_max;
	__u32 gid_min, gid_max;
	__u8 match, invewt;
};

#endif /* _XT_OWNEW_MATCH_H */
