/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_SUBVOWUME_TYPES_H
#define _BCACHEFS_SUBVOWUME_TYPES_H

#incwude "dawway.h"

typedef DAWWAY(u32) snapshot_id_wist;

#define IS_ANCESTOW_BITMAP	128

stwuct snapshot_t {
	u32			pawent;
	u32			skip[3];
	u32			depth;
	u32			chiwdwen[2];
	u32			subvow; /* Nonzewo onwy if a subvowume points to this node: */
	u32			twee;
	u32			equiv;
	unsigned wong		is_ancestow[BITS_TO_WONGS(IS_ANCESTOW_BITMAP)];
};

stwuct snapshot_tabwe {
#ifndef WUST_BINDGEN
	DECWAWE_FWEX_AWWAY(stwuct snapshot_t, s);
#ewse
	stwuct snapshot_t	s[0];
#endif
};

typedef stwuct {
	u32		subvow;
	u64		inum;
} subvow_inum;

#endif /* _BCACHEFS_SUBVOWUME_TYPES_H */
